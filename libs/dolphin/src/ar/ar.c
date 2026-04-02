#include "dolphin/ar.h"

#include "dolphin/hw_regs.h"
#include "dolphin/os.h"
#include "dolphin/os/OSCache.h"

static ARCallback __AR_Callback;
static u32 __AR_Size;
static u32 __AR_InternalSize;
static u32 __AR_ExpansionSize;

static u32 __AR_StackPointer;
static u32 __AR_FreeBlocks;
static u32 *__AR_BlockLength;

static volatile BOOL __AR_init_flag = FALSE;

static void __ARHandler(__OSInterrupt interrupt, OSContext *context);
static void __ARChecksize(void);
static void __ARClearArea(u32 start_addr, u32 length);

// TODO import defines for magic numbers from other repos

ARCallback ARRegisterDMACallback(ARCallback callback)
{
    ARCallback oldCb;
    BOOL enabled;
    oldCb = __AR_Callback;
    enabled = OSDisableInterrupts();
    __AR_Callback = callback;
    OSRestoreInterrupts(enabled);
    return oldCb;
}

u32 ARGetDMAStatus()
{
    BOOL enabled;
    u32 val;
    enabled = OSDisableInterrupts();
    val = __DSPRegs[5] & 0x0200;
    OSRestoreInterrupts(enabled);
    return val;
}

void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();

    __DSPRegs[16] = (u16)(__DSPRegs[16] & ~0x3ff) | (u16)(mainmem_addr >> 16);
    __DSPRegs[17] = (u16)(__DSPRegs[17] & ~0xffe0) | (u16)(mainmem_addr & 0xffff);
    __DSPRegs[18] = (u16)(__DSPRegs[18] & ~0x3ff) | (u16)(aram_addr >> 16);
    __DSPRegs[19] = (u16)(__DSPRegs[19] & ~0xffe0) | (u16)(aram_addr & 0xffff);
    __DSPRegs[20] = (u16)((__DSPRegs[20] & ~0x8000) | (type << 15));
    __DSPRegs[20] = (u16)(__DSPRegs[20] & ~0x3ff) | (u16)(length >> 16);
    __DSPRegs[21] = (u16)(__DSPRegs[21] & ~0xffe0) | (u16)(length & 0xffff);
    OSRestoreInterrupts(enabled);
}

u32 ARAlloc(u32 length)
{
    u32 tmp;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    tmp = __AR_StackPointer;
    __AR_StackPointer += length;
    *__AR_BlockLength = length;
    __AR_BlockLength++;
    __AR_FreeBlocks--;
    OSRestoreInterrupts(enabled);

    return tmp;
}

u32 ARFree(u32 *length)
{
    BOOL old;

    old = OSDisableInterrupts();

    __AR_BlockLength--;

    if (length) {
        *length = *__AR_BlockLength;
    }

    __AR_StackPointer -= *__AR_BlockLength;

    __AR_FreeBlocks++;

    OSRestoreInterrupts(old);

    return __AR_StackPointer;
}

BOOL ARCheckInit()
{
    return __AR_init_flag;
}

u32 ARInit(u32 *stack_index_addr, u32 num_entries)
{

    BOOL old;
    u16 refresh;

    if (__AR_init_flag == TRUE) {
        return 0x4000;
    }

    old = OSDisableInterrupts();

    __AR_Callback = NULL;

    __OSSetInterruptHandler(__OS_INTERRUPT_DSP_ARAM, __ARHandler);
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_DSP_ARAM);

    __AR_StackPointer = 0x4000;
    __AR_FreeBlocks = num_entries;
    __AR_BlockLength = stack_index_addr;

    refresh = (u16)(__DSPRegs[13] & 0x000000ff);

    __DSPRegs[13] = (u16)((__DSPRegs[13] & ~0x000000ff) | (refresh & 0x000000ff));

    __ARChecksize();

    __AR_init_flag = TRUE;

    OSRestoreInterrupts(old);

    return __AR_StackPointer;
}

void ARSetSize(void) { }

u32 ARGetBaseAddress(void)
{
    return 0x4000;
}

u32 ARGetSize()
{
    return __AR_Size;
}

static void __ARHandler(__OSInterrupt interrupt, OSContext *context)
{

    OSContext exceptionContext;
    u16 tmp;

    tmp = __DSPRegs[5];
    tmp = (u16)((tmp & ~0x00000088) | 0x20);
    __DSPRegs[5] = tmp;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (__AR_Callback) {
        (*__AR_Callback)();
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

#define RoundUP32(x) (((u32)(x) + 32 - 1) & ~(32 - 1))

void __ARClearInterrupt(void)
{

    u16 tmp;
    tmp = __DSPRegs[5];
    tmp = (u16)((tmp & ~(0x00000080 | 0x00000008)) | 0x00000020);
    __DSPRegs[5] = tmp;
}
u16 __ARGetInterruptStatus(void)
{
    return ((u16)(__DSPRegs[5] & 0x0200));
}

static void __ARWaitForDMA(void)
{

    while (__DSPRegs[5] & 0x0200) { }
}

static void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{

    __DSPRegs[16] = (u16)((__DSPRegs[16] & ~0x03ff) | (u16)(mmem_addr >> 16));
    __DSPRegs[16 + 1] = (u16)((__DSPRegs[16 + 1] & ~0xffe0) | (u16)(mmem_addr & 0xffff));

    __DSPRegs[18] = (u16)((__DSPRegs[18] & ~0x03ff) | (u16)(aram_addr >> 16));
    __DSPRegs[18 + 1] = (u16)((__DSPRegs[18 + 1] & ~0xffe0) | (u16)(aram_addr & 0xffff));

    __DSPRegs[20] = (u16)(__DSPRegs[20] & ~0x8000);

    __DSPRegs[20] = (u16)((__DSPRegs[20] & ~0x03ff) | (u16)(length >> 16));
    __DSPRegs[20 + 1] = (u16)((__DSPRegs[20 + 1] & ~0xffe0) | (u16)(length & 0xffff));

    __ARWaitForDMA();

    __ARClearInterrupt();
}

static void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{

    __DSPRegs[16] = (u16)((__DSPRegs[16] & ~0x03ff) | (u16)(mmem_addr >> 16));
    __DSPRegs[16 + 1] = (u16)((__DSPRegs[16 + 1] & ~0xffe0) | (u16)(mmem_addr & 0xffff));

    __DSPRegs[18] = (u16)((__DSPRegs[18] & ~0x03ff) | (u16)(aram_addr >> 16));
    __DSPRegs[18 + 1] = (u16)((__DSPRegs[18 + 1] & ~0xffe0) | (u16)(aram_addr & 0xffff));

    __DSPRegs[20] = (u16)(__DSPRegs[20] | 0x8000);

    __DSPRegs[20] = (u16)((__DSPRegs[20] & ~0x03ff) | (u16)(length >> 16));
    __DSPRegs[20 + 1] = (u16)((__DSPRegs[20 + 1] & ~0xffe0) | (u16)(length & 0xffff));

    __ARWaitForDMA();

    __ARClearInterrupt();
}

void __ARChecksize(void)
{
    u8 test_data_pad[0x20 + 31];
    u8 dummy_data_pad[0x20 + 31];
    u8 buffer_pad[0x20 + 31];

    u32 *test_data;
    u32 *dummy_data;
    u32 *buffer;

    u16 ARAM_mode;
    u32 ARAM_size;

    u32 i;

    while (!(__DSPRegs[11] & 1))
        ;

    ARAM_mode = 3;
    ARAM_size = __AR_InternalSize = 0x1000000;
    __DSPRegs[9] = (u16)((__DSPRegs[9] & ~(0x00000007 | 0x00000038)) | 0x20 | 2 | 1);

    test_data = (u32 *)(RoundUP32((u32)(test_data_pad)));
    dummy_data = (u32 *)(RoundUP32((u32)(dummy_data_pad)));
    buffer = (u32 *)(RoundUP32((u32)(buffer_pad)));

    for (i = 0; i < 8; i++) {
        *(test_data + i) = 0xdeadbeef;
        *(dummy_data + i) = 0xbad0bad0;
    }

    DCFlushRange((void *)test_data, 0x20);
    DCFlushRange((void *)dummy_data, 0x20);

    __AR_ExpansionSize = 0;

    __ARWriteDMA((u32)dummy_data, ARAM_size, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x200000, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x01000000, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x200, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x400000, 0x20U);

    memset((void *)buffer, 0, 0x20);
    DCFlushRange((void *)buffer, 0x20);

    __ARWriteDMA((u32)test_data, ARAM_size + 0x0000000, 0x20);

    DCInvalidateRange((void *)buffer, 0x20);

    __ARReadDMA((u32)buffer, ARAM_size + 0x0000000, 0x20);
    PPCSync();

    if (buffer[0] == test_data[0]) {
        memset((void *)buffer, 0, 0x20);
        DCFlushRange((void *)buffer, 0x20);

        __ARReadDMA((u32)buffer, ARAM_size + 0x0200000, 0x20);
        PPCSync();

        if (buffer[0] == test_data[0]) {
            ARAM_mode |= 0 << 1;
            ARAM_size += 0x0200000;
            __AR_ExpansionSize = 0x0200000;
        }
        else {
            memset((void *)buffer, 0, 0x20);
            DCFlushRange((void *)buffer, 0x20);

            __ARReadDMA((u32)buffer, ARAM_size + 0x1000000, 0x20);
            PPCSync();

            if (buffer[0] == test_data[0]) {
                ARAM_mode |= 4 << 1;
                ARAM_size += 0x0400000;
                __AR_ExpansionSize = 0x0400000;
            }
            else {
                memset((void *)buffer, 0, 0x20);
                DCFlushRange((void *)buffer, 0x20);

                __ARReadDMA((u32)buffer, ARAM_size + 0x0000200, 0x20);
                PPCSync();

                if (buffer[0] == test_data[0]) {
                    ARAM_mode |= 8 << 1;
                    ARAM_size += 0x800000;
                    __AR_ExpansionSize = 0x0800000;
                }
                else {
                    memset((void *)buffer, 0, 0x20);
                    DCFlushRange((void *)buffer, 0x20);

                    __ARReadDMA((u32)buffer, ARAM_size + 0x0400000, 0x20);
                    PPCSync();

                    if (buffer[0] == test_data[0]) {
                        ARAM_mode |= 12 << 1;
                        ARAM_size += 0x1000000;
                        __AR_ExpansionSize = 0x1000000;
                    }
                    else {
                        ARAM_mode |= 16 << 1;
                        ARAM_size += 0x2000000;
                        __AR_ExpansionSize = 0x2000000;
                    }
                }
            }
        }
        __DSPRegs[9] = (u16)((__DSPRegs[9] & ~(0x07 | 0x38)) | ARAM_mode);
    }

    *(u32 *)OSPhysicalToUncached(0x00D0) = ARAM_size;

    __AR_Size = ARAM_size;
}
