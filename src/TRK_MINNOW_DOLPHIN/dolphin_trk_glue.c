#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.h"
#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"
#include "OdemuExi2/odemuexi/DebuggerDriver.h"
#include "amcstubs/AmcExi2Stubs.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"

#define BUFF_LEN 4362

u8 gWriteBuf[BUFF_LEN];
u8 gReadBuf[BUFF_LEN];
s32 _MetroTRK_Has_Framing;
s32 gReadCount;
s32 gReadPos;
s32 gWritePos;

DBCommTable gDBCommTable = {};

asm void TRKLoadContext(OSContext* ctx, u32)
{
#ifdef __MWERKS__ // clang-format off
    nofralloc
    lwz r0, OSContext.gpr[0](r3)
    lwz r1, OSContext.gpr[1](r3)
    lwz r2, OSContext.gpr[2](r3)
    lhz r5, OSContext.state(r3)
    rlwinm. r6, r5, 0, 0x1e, 0x1e
    beq lbl_80371C1C
    rlwinm r5, r5, 0, 0x1f, 0x1d
    sth r5, OSContext.state(r3)
    lmw r5, OSContext.gpr[5](r3)
    b lbl_80371C20
lbl_80371C1C:
    lmw r13, OSContext.gpr[13](r3)
lbl_80371C20:
    mr r31, r3
    mr r3, r4
    lwz r4, OSContext.cr(r31)
    mtcrf 0xff, r4
    lwz r4, OSContext.lr(r31)
    mtlr r4
    lwz r4, OSContext.ctr(r31)
    mtctr r4
    lwz r4, OSContext.xer(r31)
    mtxer r4
    mfmsr r4
    rlwinm r4, r4, 0, 0x11, 0xf //Turn off external exceptions
    rlwinm r4, r4, 0, 0x1f, 0x1d //Turn off recoverable exception flag
    mtmsr r4
    mtsprg 1, r2
    lwz r4, OSContext.gpr[3](r31)
    mtsprg 2, r4
    lwz r4, OSContext.gpr[4](r31)
    mtsprg 3, r4
    lwz r2, OSContext.srr0(r31)
    lwz r4, OSContext.srr1(r31)
    lwz r31, OSContext.gpr[31](r31)
    b TRKInterruptHandler
#endif // clang-format on
}

void TRKEXICallBack(__OSInterrupt param_0, OSContext* ctx)
{
    OSEnableScheduler();
    TRKLoadContext(ctx, 0x500);
}

int InitMetroTRKCommTable(int hwId)
{
    int result;

    if (hwId == HARDWARE_GDEV) {
        OSReport("MetroTRK : Set to GDEV hardware\n");
        result = Hu_IsStub();

        gDBCommTable.initialize_func      = DBInitComm;
        gDBCommTable.init_interrupts_func = DBInitInterrupts;
        gDBCommTable.peek_func            = DBQueryData;
        gDBCommTable.read_func            = DBRead;
        gDBCommTable.write_func           = DBWrite;
        gDBCommTable.open_func            = DBOpen;
        gDBCommTable.close_func           = DBClose;
    } else {
        OSReport("MetroTRK : Set to AMC DDH hardware\n");
        result = AMC_IsStub();

        gDBCommTable.initialize_func      = EXI2_Init;
        gDBCommTable.init_interrupts_func = EXI2_EnableInterrupts;
        gDBCommTable.peek_func            = EXI2_Poll;
        gDBCommTable.read_func            = EXI2_ReadN;
        gDBCommTable.write_func           = EXI2_WriteN;
        gDBCommTable.open_func            = EXI2_Reserve;
        gDBCommTable.close_func           = EXI2_Unreserve;
    }

    return result;
}

DSError TRKInitializeIntDrivenUART(u32 param_0, u32 param_1, u32 param_2,
                                   volatile u8** param_3)
{
    gDBCommTable.initialize_func(param_3, TRKEXICallBack);
    return DS_NoError;
}

void EnableEXI2Interrupts(void) { gDBCommTable.init_interrupts_func(); }

inline int TRKPollUART(void) { return gDBCommTable.peek_func(); }

inline UARTError TRKReadUARTN(void* bytes, u32 length)
{
    int readErr = gDBCommTable.read_func(bytes, length);
    return readErr == 0 ? 0 : -1;
}

inline UARTError TRKWriteUARTN(const void* bytes, u32 length)
{
    int writeErr = gDBCommTable.write_func(bytes, length);
    return writeErr == 0 ? 0 : -1;
}

UARTError WriteUARTFlush(void)
{
    UARTError readErr = 0;

    while (gWritePos < 0x800) {
        gWriteBuf[gWritePos] = 0;
        gWritePos++;
    }
    if (gWritePos != 0) {
        readErr = TRKWriteUARTN(gWriteBuf, gWritePos);
        gWritePos = 0;
    }
    return readErr;
}

UARTError WriteUART1(u8 arg0)
{
    gWriteBuf[gWritePos++] = arg0;
    return 0;
}

UARTError TRKReadUARTPoll(u8* arg0)
{
    UARTError readErr = 4;
    s32 cnt;

    if (gReadPos >= gReadCount) {
        gReadPos = 0;
        cnt = gReadCount = TRKPollUART();
        if (cnt > 0) {
            if (cnt > BUFF_LEN) {
                gReadCount = BUFF_LEN;
            }
            readErr = TRKReadUARTN(gReadBuf, gReadCount);
            if (readErr != 0) {
                gReadCount = 0;
            }
        }
    }
    if (gReadPos < gReadCount) {
        *arg0 = gReadBuf[gReadPos++];
        readErr = 0;
    }
    return readErr;
}

void ReserveEXI2Port(void) { gDBCommTable.open_func(); }

void UnreserveEXI2Port(void) { gDBCommTable.close_func(); }

void TRK_board_display(char* str) { OSReport(str); }

void TRKUARTInterruptHandler() { }
