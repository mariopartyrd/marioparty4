#include <dolphin/dvd.h>
#include <dolphin/os.h>
#include <dolphin/os/OSBootInfo.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSPriv.h>

typedef struct ApploaderHeader {
    // total size: 0x20
    char date[16]; // offset 0x0, size 0x10
    u32 entry; // offset 0x10, size 0x4
    u32 size; // offset 0x14, size 0x4
    u32 rebootSize; // offset 0x18, size 0x4
    u32 reserved2; // offset 0x1C, size 0x4
} ApploaderHeader;

static ApploaderHeader Header ATTRIBUTE_ALIGN(32);

extern void *__OSSavedRegionStart;
extern void *__OSSavedRegionEnd;

static void *SaveStart = NULL;
static void *SaveEnd = NULL;

volatile u8 DAT_800030e2 : 0x800030e2;

extern void *BOOT_REGION_START AT_ADDRESS(0x812FDFF0); //(*(u32 *)0x812fdff0)
extern void *BOOT_REGION_END AT_ADDRESS(0x812FDFEC); //(*(u32 *)0x812fdfec)
extern u32 UNK_HOT_RESET1 AT_ADDRESS(0x817ffff8);
extern u32 UNK_HOT_RESET2 AT_ADDRESS(0x817ffffc);
extern u32 OS_RESET_CODE AT_ADDRESS(0x800030F0);
extern u8 OS_REBOOT_BOOL AT_ADDRESS(0x800030E2); // unknown function, set to true by __OSReboot
extern u32 UNK_817FFFF8 AT_ADDRESS(0x817FFFF8);
extern u32 UNK_817FFFFC AT_ADDRESS(0x817FFFFC);

static volatile BOOL Prepared = FALSE;

extern void __DVDPrepareResetAsync(DVDCBCallback callback);
extern BOOL DVDCheckDisk(void);
extern BOOL DVDReadAbsAsyncForBS(DVDCommandBlock *block, void *addr, s32 length, s32 offset, DVDCBCallback callback);

#pragma dont_inline on
// peephole bug with mwcc
static asm void myFunc() { }
static void Run(register void (*addr)())
{
    OSDisableInterrupts();
    ICFlashInvalidate();
    // clang-format off
	asm {
	    sync
	    isync
	    mtlr addr
	    blr
	}
    // clang-format on
}
#pragma dont_inline reset

static void Callback()
{
    Prepared = TRUE;
}

inline void ReadApploader(DVDCommandBlock *dvdCmd, void *addr, u32 offset, u32 numBytes)
{
    /* Not sure if this inline is correct - might need to call other inlines */
    while (Prepared == FALSE) { }
    DVDReadAbsAsyncForBS(dvdCmd, addr, numBytes, offset + 0x2440, NULL);

    while (TRUE) {
        switch (dvdCmd->state) {
            case 0:
                break;
            case 1:
            default:
                continue;
            case -1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                __OSDoHotReset(UNK_817FFFFC);
                continue;
        }
        break;
    }
}

void __OSReboot(u32 resetCode, u32 bootDol)
{
    OSContext exceptionContext;
    DVDCommandBlock dvdCmd;
    DVDCommandBlock dvdCmd2;
    u32 numBytes;
    u32 offset;

    OSDisableInterrupts();

    UNK_817FFFFC = 0;
    UNK_817FFFF8 = 0;
    OS_REBOOT_BOOL = TRUE;
    BOOT_REGION_START = SaveStart;
    BOOT_REGION_END = SaveEnd;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    DVDInit();
    DVDSetAutoInvalidation(TRUE);

    __DVDPrepareResetAsync(Callback);

    if (!DVDCheckDisk()) {
        __OSDoHotReset(UNK_817FFFFC);
    }

    __OSMaskInterrupts(0xffffffe0);
    __OSUnmaskInterrupts(0x400);

    OSEnableInterrupts();

    offset = 0;
    numBytes = 32;
    ReadApploader(&dvdCmd, (void *)&Header, offset, numBytes);

    offset = Header.size + 0x20;
    numBytes = OSRoundUp32B(Header.rebootSize);
    ReadApploader(&dvdCmd2, OS_BOOTROM_ADDR, offset, numBytes);

    ICInvalidateRange(OS_BOOTROM_ADDR, numBytes);
    Run(OS_BOOTROM_ADDR);
}
