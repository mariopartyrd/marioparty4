#include "game/gamework_data.h"
#include "game/dvd.h"
#include "game/printfunc.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/init.h"
#include "game/process.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/sprite.h"
#include "game/hsfformat.h"
#include "game/hsfman.h"
#include "game/perf.h"
#include "game/gamework.h"

extern FileListEntry _ovltbl[];
u32 GlobalCounter;
static u32 vcheck;
static u32 vmiss;
static u32 vstall;
static u32 top_pixels_in;
static u32 top_pixels_out;
static u32 bot_pixels_in;
static u32 bot_pixels_out;
static u32 clr_pixels_in;
static u32 total_copy_clks;
static u32 cp_req;
static u32 tc_req;
static u32 cpu_rd_req;
static u32 cpu_wr_req;
static u32 dsp_req;
static u32 io_req;
static u32 vi_req;
static u32 pe_req;
static u32 rf_req;
static u32 fi_req;
s32 HuDvdErrWait;
s32 SystemInitF;

void main(void)
{
    u32 met0;
    u32 met1;
    s16 i;
    s32 retrace;
    #if VERSION_PAL
    s16 temp = 0;
    #endif
    
    HuDvdErrWait = 0;
    SystemInitF = 0;
    #if VERSION_NTSC
    HuSysInit(&GXNtsc480IntDf);
    #else
    HuSysInit(&GXPal528IntDf);
    #endif
    HuPrcInit();
    HuPadInit();
    GWInit();
    pfInit();
    GlobalCounter = 0;
    HuSprInit();
    Hu3DInit();
    HuDataInit();
    HuPerfInit();
    HuPerfCreate("USR0", 0xFF, 0xFF, 0xFF, 0xFF);
    HuPerfCreate("USR1", 0, 0xFF, 0xFF, 0xFF);
    WipeInit(RenderMode);
    
    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].character = -1;
    }
    
    omMasterInit(0, _ovltbl, OVL_COUNT, OVL_BOOT);
    VIWaitForRetrace();
    
    if (VIGetNextField() == 0) {
        OSReport("VI_FIELD_BELOW\n");
        VIWaitForRetrace();
    }
    while (1) {
        retrace = VIGetRetraceCount();
        if (HuSoftResetButtonCheck() != 0 || HuDvdErrWait != 0) {
            continue;
        }
        HuPerfZero();
        HuPerfBegin(2);
        HuSysBeforeRender();
        GXSetGPMetric(GX_PERF0_CLIP_VTX, GX_PERF1_VERTICES);
        GXClearGPMetric();
        GXSetVCacheMetric(GX_VC_ALL);
        GXClearVCacheMetric();
        GXClearPixMetric();
        GXClearMemMetric();
        HuPerfBegin(0);
        Hu3DPreProc();
        HuPadRead();
        pfClsScr();
        HuPrcCall(1);
        MGSeqMain();
        HuPerfBegin(1);
        Hu3DExec();
        HuDvdErrorWatch();
        WipeExecAlways();
        HuPerfEnd(0);
        pfDrawFonts();
        HuPerfEnd(1);
        msmMusFdoutEnd();
        HuSysDoneRender(retrace);
        GXReadGPMetric(&met0, &met1);
        GXReadVCacheMetric(&vcheck, &vmiss, &vstall);
        GXReadPixMetric(&top_pixels_in, &top_pixels_out, &bot_pixels_in, &bot_pixels_out, &clr_pixels_in, &total_copy_clks);
        GXReadMemMetric(&cp_req, &tc_req, &cpu_rd_req, &cpu_wr_req, &dsp_req, &io_req, &vi_req, &pe_req, &rf_req, &fi_req);
        HuPerfEnd(2);
        GlobalCounter++;
    }
}

void HuSysVWaitSet(s16 vcount)
{
    minimumVcount = vcount;
    minimumVcountf = vcount;
}

s16 HuSysVWaitGet(s16 param)
{
    return (s16) minimumVcount;
}

s32 rnd_seed = 0x0000D9ED;

s32 rand8(void)
{
    rnd_seed = (rnd_seed * 0x41C64E6D) + 0x3039;
    return (u8)(((rnd_seed + 1) >> 16) & 0xFF);
}
