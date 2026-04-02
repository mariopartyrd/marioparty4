#include <dolphin/os.h>
#include <dolphin/hw_regs.h>

#define TRUNC(n, a) (((u32)(n)) & ~((a)-1))
#define ROUND(n, a) (((u32)(n) + (a)-1) & ~((a)-1))

extern OSErrorHandler __OSErrorTable[16];

static BOOL OnReset(BOOL final);

static OSResetFunctionInfo ResetFunctionInfo = {
    OnReset,
    127,
};
u32 OSGetPhysicalMemSize()
{
    return *(u32 *)(OSPhysicalToCached(0x0028));
}

u32 OSGetConsoleSimulatedMemSize()
{
    return *(u32 *)(OSPhysicalToCached(0x00F0));
}

static BOOL OnReset(BOOL final)
{
    if (final != FALSE) {
        __MEMRegs[8] = 0xFF;
        __OSMaskInterrupts(0xf0000000);
    }
    return TRUE;
}

static void MEMIntrruptHandler(__OSInterrupt interrupt, OSContext *context)
{
    u32 addr;
    u32 cause;

    cause = __MEMRegs[0xf];
    addr = (((u32)__MEMRegs[0x12] & 0x3ff) << 16) | __MEMRegs[0x11];
    __MEMRegs[0x10] = 0;

    if (__OSErrorTable[OS_ERROR_PROTECTION]) {
        __OSErrorTable[OS_ERROR_PROTECTION](OS_ERROR_PROTECTION, context, cause, addr);
        return;
    }

    __OSUnhandledException(OS_ERROR_PROTECTION, context, cause, addr);
}

void OSProtectRange(u32 chan, void *addr, u32 nBytes, u32 control)
{
    BOOL enabled;
    u32 start;
    u32 end;
    u16 reg;
    if (4 <= chan) {
        return;
    }

    control &= OS_PROTECT_CONTROL_RDWR;

    end = (u32)addr + nBytes;
    start = TRUNC(addr, 1u << 10);
    end = ROUND(end, 1u << 10);

    DCFlushRange((void *)start, end - start);

    enabled = OSDisableInterrupts();

    __OSMaskInterrupts(OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_0 + chan));

    __MEMRegs[0 + 2 * chan] = (u16)(start >> 10);
    __MEMRegs[1 + 2 * chan] = (u16)(end >> 10);

    reg = __MEMRegs[8];
    reg &= ~(OS_PROTECT_CONTROL_RDWR << 2 * chan);
    reg |= control << 2 * chan;
    __MEMRegs[8] = reg;

    if (control != OS_PROTECT_CONTROL_RDWR) {
        __OSUnmaskInterrupts(OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_0 + chan));
    }

    OSRestoreInterrupts(enabled);
}

asm void Config24MB()
{
    // clang-format off
  nofralloc

  addi    r7,r0,0

  addis   r4,r0,0x00000002@ha
  addi    r4,r4,0x00000002@l
  addis   r3,r0,0x800001ff@ha
  addi    r3,r3,0x800001ff@l

  addis   r6,r0,0x01000002@ha
  addi    r6,r6,0x01000002@l
  addis   r5,r0,0x810000ff@ha
  addi    r5,r5,0x810000ff@l

  isync

  mtspr   dbat0u,r7
  mtspr   dbat0l,r4
  mtspr   dbat0u,r3
  isync

  mtspr   ibat0u,r7
  mtspr   ibat0l,r4
  mtspr   ibat0u,r3
  isync

  mtspr   dbat2u,r7
  mtspr   dbat2l,r6
  mtspr   dbat2u,r5
  isync

  mtspr   ibat2u,r7
  mtspr   ibat2l,r6
  mtspr   ibat2u,r5
  isync

  mfmsr   r3
  ori     r3, r3, 0x30
  mtsrr1  r3

  mflr    r3
  mtsrr0  r3
  rfi
    // clang-format on
}

asm void Config48MB()
{
    // clang-format off
  nofralloc

  addi    r7,r0,0x0000

  addis   r4,r0,0x00000002@ha
  addi    r4,r4,0x00000002@l
  addis   r3,r0,0x800003ff@ha
  addi    r3,r3,0x800003ff@l

  addis   r6,r0,0x02000002@ha
  addi    r6,r6,0x02000002@l
  addis   r5,r0,0x820001ff@ha
  addi    r5,r5,0x820001ff@l

  isync

  mtspr   dbat0u,r7
  mtspr   dbat0l,r4
  mtspr   dbat0u,r3
  isync

  mtspr   ibat0u,r7
  mtspr   ibat0l,r4
  mtspr   ibat0u,r3
  isync

  mtspr   dbat2u,r7
  mtspr   dbat2l,r6
  mtspr   dbat2u,r5
  isync

  mtspr   ibat2u,r7
  mtspr   ibat2l,r6
  mtspr   ibat2u,r5
  isync

  mfmsr   r3
  ori     r3, r3, 0x30
  mtsrr1  r3

  mflr    r3
  mtsrr0  r3
  rfi
    // clang-format on
}

asm void RealMode(register u32 addr)
{
    // clang-format off
  nofralloc
  clrlwi r3, r3, 2
  mtsrr0 r3
  mfmsr r3
  rlwinm r3, r3, 0, 28, 25
  mtsrr1 r3
  rfi
    // clang-format on
}

void __OSInitMemoryProtection()
{
    u32 padding[8];
    u32 simulatedSize;
    BOOL enabled;
    simulatedSize = OSGetConsoleSimulatedMemSize();
    enabled = OSDisableInterrupts();
    if (simulatedSize <= 0x1800000) {
        RealMode((u32)&Config24MB);
    }
    else if (simulatedSize <= 0x3000000) {
        RealMode((u32)&Config48MB);
    }

    __MEMRegs[16] = 0;
    __MEMRegs[8] = 0xFF;

    __OSMaskInterrupts(OS_INTERRUPTMASK_MEM_0 | OS_INTERRUPTMASK_MEM_1 | OS_INTERRUPTMASK_MEM_2 | OS_INTERRUPTMASK_MEM_3);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_0, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_1, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_2, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_3, MEMIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_MEM_ADDRESS, MEMIntrruptHandler);
    OSRegisterResetFunction(&ResetFunctionInfo);

    if (OSGetConsoleSimulatedMemSize() < OSGetPhysicalMemSize() && OSGetConsoleSimulatedMemSize() == 0x1800000) {
        __MEMRegs[20] = 2;
    }

    __OSUnmaskInterrupts(OS_INTERRUPTMASK_MEM_ADDRESS);
    OSRestoreInterrupts(enabled);
}
