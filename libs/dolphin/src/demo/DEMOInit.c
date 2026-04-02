#include <dolphin.h>
#include <dolphin/demo.h>
#include <dolphin/gx.h>
#include <dolphin/pad.h>
#include <dolphin/vi.h>
#include "game/init.h"

#include <dolphin/demoPriv.h>

extern unsigned char DemoStatEnable; // size: 0x1, address: 0x0

// .bss
static struct _GXRenderModeObj rmodeobj; // size: 0x3C, address: 0x0

// .sdata
static unsigned char DemoFirstFrame = 1; // size: 0x1, address: 0x0

// .sbss
static void *DefaultFifo = NULL; // size: 0x4, address: 0x0
static GXFifoObj *DefaultFifoObj = NULL; // size: 0x4, address: 0x4
static struct _GXRenderModeObj *rmode; // size: 0x4, address: 0x8
static int BypassWorkaround; // size: 0x4, address: 0xC
static unsigned long FrameCount; // size: 0x4, address: 0x10
static unsigned long FrameMissThreshold; // size: 0x4, address: 0x14

// functions
static void __DEMOInitRenderMode(struct _GXRenderModeObj *mode);
static void __DEMOInitMem();
static void __DEMOInitGX();
static void __DEMOInitVI();
static void __DEMOInitForEmu();
static void __BypassRetraceCallback();
static void LoadMemInfo();

void DEMOInit(struct _GXRenderModeObj *mode)
{
    OSInit();
    DVDInit();
    VIInit();
    DEMOPadInit();
    __DEMOInitRenderMode(mode);
    __DEMOInitMem();
    VIConfigure(rmode);
    DefaultFifo = OSAllocFromHeap(__OSCurrHeap, 0x40000);
    DefaultFifoObj = GXInit(DefaultFifo, 0x40000);
    __DEMOInitGX();
    __DEMOInitVI();
}

static void __DEMOInitRenderMode(struct _GXRenderModeObj *mode)
{
    if (mode != NULL) {
        rmode = mode;
        return;
    }
    switch (VIGetTvFormat()) {
        case VI_NTSC:
            rmode = &GXNtsc480IntDf;
            break;
        case VI_PAL:
            rmode = &GXPal528IntDf;
            break;
        case VI_MPAL:
            rmode = &GXMpal480IntDf;
            break;
        default:
            OSPanic(__FILE__, 0x1A6, "DEMOInit: invalid TV format\n");
            break;
    }
    GXAdjustForOverscan(rmode, &rmodeobj, 0, 0x10);
    rmode = &rmodeobj;
}

static void __DEMOInitMem()
{
    void *arenaLo = OSGetArenaLo();
    void *arenaHi = OSGetArenaHi();
    unsigned long fbSize = ((u16)(rmode->fbWidth + 15) & 0xFFF0) * rmode->xfbHeight * 2;

    DemoFrameBuffer1 = (void *)(((uintptr_t)arenaLo + 0x1F) & ~0x1F);
    DemoFrameBuffer2 = (void *)(((uintptr_t)DemoFrameBuffer1 + fbSize + 0x1F) & ~0x1F);
    DemoCurrentBuffer = DemoFrameBuffer2;
    arenaLo = (void *)(((uintptr_t)DemoFrameBuffer2 + fbSize + 0x1F) & ~0x1F);
    OSSetArenaLo(arenaLo);
    if (((OSGetConsoleType() + 0xF0000000) == 4U) && ((OSGetPhysicalMemSize() + 0xFFC00000) != 0U)
        && (OSGetConsoleSimulatedMemSize() < 0x01800000U)) {
        LoadMemInfo();
        return;
    }
    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
    OSSetArenaLo(arenaLo);
    arenaLo = (void *)(((uintptr_t)arenaLo + 0x1F) & ~0x1F);
    arenaHi = (void *)((uintptr_t)arenaHi & ~0x1F);
    OSSetCurrentHeap(OSCreateHeap((void *)(((uintptr_t)arenaLo)), arenaHi));
    OSSetArenaLo((arenaLo = arenaHi));
}

static void __DEMOInitGX()
{
    GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->xfbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopySrc(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyDst(rmode->fbWidth, rmode->xfbHeight);
    GXSetDispCopyYScale(((f32)rmode->xfbHeight / (f32)rmode->efbHeight));
    GXSetCopyFilter(rmode->aa, rmode->sample_pattern, 1, rmode->vfilter);
    if (rmode->aa != 0) {
        GXSetPixelFmt(2, 0);
    }
    else {
        GXSetPixelFmt(0, 0);
    }
    GXCopyDisp(DemoCurrentBuffer, 1);
    GXSetDispCopyGamma(0);
}

static void __DEMOInitVI()
{
    unsigned long nin;

    VISetNextFrameBuffer(DemoFrameBuffer1);
    DemoCurrentBuffer = DemoFrameBuffer2;
    VIFlush();
    VIWaitForRetrace();
    nin = rmode->viTVmode & 1;
    if (nin != 0) {
        VIWaitForRetrace();
    }
}

static void __DEMOInitForEmu() { }

void DEMOBeforeRender()
{
    if (BypassWorkaround != 0) {
        GXSetDrawSync(0xFEEB);
    }
    if (rmode->field_rendering != 0) {
        GXSetViewportJitter(0.0f, 0.0f, rmode->fbWidth, rmode->xfbHeight, 0.0f, 1.0f, VIGetNextField());
    }
    else {
        GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->xfbHeight, 0.0f, 1.0f);
    }
    GXInvalidateVtxCache();
    GXInvalidateTexAll();
}

void DEMOSwapBuffers()
{
    VISetNextFrameBuffer(DemoCurrentBuffer);
    if (DemoFirstFrame != 0) {
        VISetBlack(0);
        DemoFirstFrame = 0;
    }
    VIFlush();
    VIWaitForRetrace();
    if ((u32)DemoCurrentBuffer == (u32)DemoFrameBuffer1) {
        DemoCurrentBuffer = DemoFrameBuffer2;
        return;
    }
    DemoCurrentBuffer = DemoFrameBuffer1;
}

struct _GXRenderModeObj *DEMOGetRenderModeObj()
{
    return rmode;
}

u32 DEMOGetCurrentBuffer(void)
{
    return (u32)DemoCurrentBuffer;
}

void DEMOEnableBypassWorkaround(unsigned long timeoutFrames)
{
    BypassWorkaround = 1;
    FrameMissThreshold = timeoutFrames;
    VISetPreRetraceCallback(__BypassRetraceCallback);
}

static void __BypassRetraceCallback()
{
    FrameCount += 1;
}

static void LoadMemInfo()
{
    void *arenaHiOld;
    void *arenaLo;
    void *arenaHi;
    void *simMemEnd;
    struct DVDFileInfo fileInfo;
    unsigned long length;
    unsigned long transferLength;
    long offset;
    unsigned long i;
    unsigned long indexMax;
    char *buf[63];
    struct {
        void *start;
        void *end;
    } *memEntry;

    OSReport("\nNow, try to find memory info file...\n\n");
    if (!DVDOpen("/meminfo.bin", &fileInfo)) {
        OSReport("\nCan't find memory info file. Use /XXX toolname/ to maximize available\n");
        OSReport("memory space. For now, we only use the first %dMB.\n", OSGetConsoleSimulatedMemSize() >> 0x14);
        arenaLo = OSGetArenaLo();
        arenaHi = OSGetArenaHi();
        arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
        OSSetArenaLo(arenaLo);
        arenaLo = (void *)(((uintptr_t)arenaLo + 0x1F) & ~0x1F);
        arenaHi = (void *)((uintptr_t)arenaHi & ~0x1F);
        OSSetCurrentHeap(OSCreateHeap((void *)(((u32)arenaLo)), arenaHi));
        OSSetArenaLo((arenaLo = arenaHi));
        return;
    }
    memEntry = (void *)((uintptr_t)buf + 0x1F & ~0x1F);
    arenaHiOld = OSGetArenaHi();
    simMemEnd = OSPhysicalToCached(OSGetConsoleSimulatedMemSize());
    OSSetArenaHi(OSPhysicalToCached(OSGetPhysicalMemSize()));
    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
    OSSetArenaLo(arenaLo);
    arenaLo = (void *)(((uintptr_t)arenaLo + 0x1F) & ~0x1F);
    arenaHi = (void *)((uintptr_t)arenaHi & ~0x1F);
    OSSetCurrentHeap(OSCreateHeap((void *)(arenaLo), arenaHi));
    OSSetArenaLo((arenaLo = arenaHi));
    OSAllocFixed(&arenaHiOld, &simMemEnd);
    length = fileInfo.length;
    offset = 0;
    while (length) {
        OSReport("loop\n");
        transferLength = (length < 0x20) ? length : 0x20;
        if (DVDReadPrio(&fileInfo, memEntry, (transferLength + 0x1F) & ~0x1F, offset, 2) < 0) {
            OSPanic(__FILE__, 0x49F, "An error occurred when issuing read to /meminfo.bin\n");
        }
        indexMax = (transferLength / 8);
        for (i = 0; i < indexMax; i++) {
            OSReport("start: 0x%08x, end: 0x%08x\n", memEntry[i].start, memEntry[i].end);
            OSAllocFixed(&memEntry[i].start, &memEntry[i].end);
            OSReport("Removed 0x%08x - 0x%08x from the current heap\n", memEntry[i].start, (char *)memEntry[i].end - 1);
        }
        length -= transferLength;
        offset += transferLength;
    }
    DVDClose(&fileInfo);
    OSDumpHeap(__OSCurrHeap);
}
