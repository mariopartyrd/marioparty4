#include <dolphin.h>
#include <stdarg.h>
#include <stdio.h>
#include <types.h>

#include <game/dvd.h>
#include <game/msm.h>
#include <game/object.h>

// Credits: Super Monkey Ball

static VIRetraceCallback sVIRetraceCallback = NULL;

void OSReport(const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    fflush(stdout);
    va_end(args);
}

u32 OSGetConsoleType()
{
    return OS_CONSOLE_RETAIL1;
}

u32 OSGetSoundMode()
{
    return 2;
}

void DCFlushRange(void *addr, u32 nBytes)
{
    //puts("DCFlushRange is a stub");
}

void DCFlushRangeNoSync(void *addr, u32 nBytes)
{
    //puts("DCFlushRangeNoSync is a stub");
}

void DCInvalidateRange(void *addr, u32 nBytes)
{
    //puts("DCInvalidateRange is a stub");
}

void DCStoreRange(void *addr, u32 nBytes)
{
    //puts("DCStoreRange is a stub");
}

void DCStoreRangeNoSync(void *addr, u32 nBytes)
{
    //puts("DCStoreRangeNoSync is a stub");
}

void DEMOUpdateStats(unsigned char inc)
{
    puts("DEMOUpdateStats is a stub");
}

void DEMOPrintStats(void)
{
    puts("DEMOPrintStats is a stub");
}

s32 DVDCancel(volatile DVDCommandBlock *block)
{
    puts("DVDCancel is a stub");
    return 0;
}

int DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback)
{
    puts("DVDReadAbsAsyncForBS is a stub");
    return 0;
}

int DVDReadDiskID(DVDCommandBlock* block, DVDDiskID* diskID, DVDCBCallback callback)
{
    puts("DVDReadDiskID is a stub");
    return 0;
}

void DVDReset()
{
    puts("DVDReset is a stub");
}

BOOL EXIDeselect(s32 chan)
{
    puts("EXIDeselect is a stub");
    return FALSE;
}

BOOL EXIDma(s32 chan, void *buffer, s32 size, u32 d, EXICallback e)
{
    puts("EXIDma is a stub");
    return FALSE;
}

BOOL EXIImm(s32 chan, u32 *b, s32 c, u32 d, EXICallback e)
{
    puts("EXIImm is a stub");
    return FALSE;
}

BOOL EXILock(s32 chan, u32 b, EXICallback c)
{
    puts("EXILock is a stub");
    return FALSE;
}

BOOL EXISelect(s32 chan, u32 b, u32 c)
{
    puts("EXISelect is a stub");
    return FALSE;
}

BOOL EXISync(s32 chan)
{
    puts("EXISync is a stub");
    return FALSE;
}

BOOL EXIUnlock(s32 chan)
{
    puts("EXIUnlock is a stub");
    return FALSE;
}

void LCEnable()
{
    puts("LCEnable is a stub");
}

void OSClearContext(OSContext *context)
{
    puts("OSClearContext is a stub");
}

BOOL OSDisableInterrupts()
{
    puts("OSDisableInterrupts is a stub");
    return FALSE;
}

void OSDumpContext(OSContext *context)
{
    puts("OSDumpContext is a stub");
}

OSThread *OSGetCurrentThread()
{
    puts("OSGetCurrentThread is a stub");
    return 0;
}

u16 OSGetFontEncode()
{
    puts("OSGetFontEncode is a stub");
    return 0;
}

char *OSGetFontTexture(const char *string, void **image, s32 *x, s32 *y, s32 *width)
{
    puts("OSGetFontTexture is a stub");
    return 0;
}

char *OSGetFontWidth(const char *string, s32 *width)
{
    puts("OSGetFontWidth is a stub");
    return 0;
}

BOOL OSGetResetButtonState()
{
    puts("OSGetResetButtonState is a stub");
    return FALSE;
}

u32 OSGetStackPointer()
{
    puts("OSGetStackPointer is a stub");
    return 0;
}

BOOL OSInitFont(OSFontHeader *fontData)
{
    puts("OSInitFont is a stub");
    return FALSE;
}

BOOL OSLink(OSModuleInfo *newModule, void *bss)
{
    puts("OSLink is a stub");
    return TRUE;
}

void OSLoadContext(OSContext *context)
{
    puts("OSLoadContext is a stub");
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu)
{
    puts("OSResetSystem is a stub");
}

BOOL OSRestoreInterrupts(BOOL level)
{
    puts("OSRestoreInterrupts is a stub");
    return FALSE;
}

s32 OSResumeThread(OSThread *thread)
{
    puts("OSResumeThread is a stub");
    return 0;
}

void OSSetCurrentContext(OSContext *context)
{
    puts("OSSetCurrentContext is a stub");
}

void OSSetStringTable(const void *stringTable)
{
    puts("OSSetStringTable is a stub");
}

s32 OSSuspendThread(OSThread *thread)
{
    puts("OSSuspendThread is a stub");
    return 0;
}

BOOL OSUnlink(OSModuleInfo *oldModule)
{
    puts("OSUnlink is a stub");
    return FALSE;
}

void OSWakeupThread(OSThreadQueue *queue)
{
    puts("OSWakeupThread is a stub");
}

void PPCHalt()
{
    puts("PPCHalt is a stub");
}

void SoundChoID(int a, int b)
{
    puts("SoundChoID is a stub");
}

void SoundPan(int a, int b, int c)
{
    puts("SoundPan is a stub");
}

void SoundPitch(u16 a, int b)
{
    puts("SoundPitch is a stub");
}

void SoundRevID(int a, int b)
{
    puts("SoundRevID is a stub");
}

void VIConfigure(const GXRenderModeObj *rm)
{
    puts("VIConfigure is a stub");
}

void VIConfigurePan(u16 xOrg, u16 yOrg, u16 width, u16 height)
{
    puts("VIConfigurePan is a stub");
}

u32 VIGetRetraceCount()
{
    // puts("VIGetRetraceCount is a stub");
    return 0; // TODO this might be important
}

u32 VIGetNextField()
{
    puts("VIGetNextField is a stub");
    return 0;
}

void VISetBlack(BOOL black)
{
    puts("VISetBlack is a stub");
}

void VISetNextFrameBuffer(void *fb)
{
    // puts("VISetNextFrameBuffer is a stub");
}

void VIWaitForRetrace()
{
if (sVIRetraceCallback)
{
    sVIRetraceCallback(0);
}
}

void __GXSetSUTexSize()
{
    puts("__GXSetSUTexSize is a stub");
}

u32 __OSGetDIConfig()
{
    puts("__OSGetDIConfig is a stub");
    return 0;
}

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt interrupt, __OSInterruptHandler handler)
{
    puts("__OSSetInterruptHandler is a stub");
    return 0;
}

OSInterruptMask __OSUnmaskInterrupts(OSInterruptMask mask)
{
    puts("__OSUnmaskInterrupts is a stub");
    return 0;
}

void SISetSamplingRate(u32 msec)
{
    // Maybe we could include SI later
    puts("SISetSamplingRate is a stub");
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback)
{
sVIRetraceCallback = callback;
    return callback;
}

void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1)
{
    // puts("GXSetGPMetric is a stub");
}

void GXReadGPMetric(u32 *cnt0, u32 *cnt1)
{
    // puts("GXReadGPMetric is a stub");
}

void GXClearGPMetric(void)
{
    // puts("GXClearGPMetric is a stub");
}

void GXReadMemMetric(
    u32 *cp_req, u32 *tc_req, u32 *cpu_rd_req, u32 *cpu_wr_req, u32 *dsp_req, u32 *io_req, u32 *vi_req, u32 *pe_req, u32 *rf_req, u32 *fi_req)
{
    // puts("GXReadMemMetric is a stub");
}

void GXClearMemMetric(void)
{
    // puts("GXClearMemMetric is a stub");
}

void GXClearVCacheMetric(void)
{
    // puts("GXClearVCacheMetric is a stub");
}

void GXReadPixMetric(u32 *top_pixels_in, u32 *top_pixels_out, u32 *bot_pixels_in, u32 *bot_pixels_out, u32 *clr_pixels_in, u32 *copy_clks)
{
    // puts("GXReadPixMetric is a stub");
}

void GXClearPixMetric(void)
{
    // puts("GXClearPixMetric is a stub");
}

void GXSetVCacheMetric(GXVCachePerf attr)
{
    // puts("GXSetVCacheMetric is a stub");
}

void GXReadVCacheMetric(u32 *check, u32 *miss, u32 *stall)
{
    // puts("GXReadVCacheMetric is a stub");
}

void GXSetDrawSync(u16 token)
{
    // puts("GXSetDrawSync is a stub");
}

GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback cb)
{
    puts("GXSetDrawSyncCallback is a stub");
    // TODO
    return cb;
}

void PPCSync(void)
{
    //puts("PPCSync is a stub");
}

void GXUnknownu16(const u16 x)
{
    puts("GXUnknownu16 is a stub");
}

void GXWaitDrawDone(void)
{
    // puts("GXWaitDrawDone is a stub");
}

void GXResetWriteGatherPipe(void)
{
    // puts("GXResetWriteGatherPipe is a stub");
}

// Hudson
void HuDvdErrDispInit(GXRenderModeObj *rmode, void *xfb1, void *xfb2) { }

void msmSysRegularProc(void)
{
}

void msmMusFdoutEnd(void)
{
}

int msmMusPlay(int musId, MSM_MUSPARAM *musParam)
{
    // TODO
    return 0;
}

s32 msmMusGetStatus(int musNo)
{
    // TODO
    return 0;
}

s32 msmStreamGetStatus(int streamNo)
{
    // TODO
    return 0;
}

s32 msmSeSetParam(int seNo, MSM_SEPARAM* param)
{
    return 0;
}

s32 msmMusSetParam(s32 arg0, MSM_MUSPARAM* arg1)
{
    return 0;
}

void msmMusSetMasterVolume(s32 vol)
{
}

s32 msmSysGetOutputMode(void)
{
    return 0;
}

s32 msmSeSetListener(Vec* pos, Vec* heading, float sndDist, float sndSpeed, MSM_SELISTENER* listener)
{
    return 0;
}

void msmSeStopAll(BOOL checkGrp, s32 speed)
{
}

BOOL msmSysSetOutputMode(SND_OUTPUTMODE mode)
{
    return TRUE;
}

void OSSetSoundMode(u32 mode)
{
}

s32 HuSoftResetButtonCheck(void)
{
    //puts("HuSoftResetButtonCheck is a stub");
    return 0;
}

s16 HuTHPSprCreateVol(char *path, s16 loop, s16 prio, float volume)
{
    return 0;
}

s16 HuTHPSprCreate(char *path, s16 loop, s16 prio)
{
    return 0;
}

s16 HuTHP3DCreateVol(char *path, s16 loop, float volume)
{
    return 0;
}

s16 HuTHP3DCreate(char *path, s16 loop)
{
    return 0;
}

void HuTHPStop(void)
{
}

void HuTHPClose(void)
{
}

void HuTHPRestart(void)
{
}

BOOL HuTHPEndCheck(void)
{
    return TRUE;
}

s32 HuTHPFrameGet(void)
{
    return 0;
}

s32 HuTHPTotalFrameGet(void)
{
    return 0;
}

void HuTHPSetVolume(s32 left, s32 right)
{
}
