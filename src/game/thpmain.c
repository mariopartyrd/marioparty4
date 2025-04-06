#include "game/thpmain.h"
#include "game/THPSimple.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/init.h"
#include "game/process.h"
#include "game/sprite.h"

#include "string.h"

#define THP_DECODE_STACK_SIZE 0x2000

static void THPTestProc(void);
static void THPViewFunc(ModelData *arg0, Mtx arg1);
static void THPViewSprFunc(HuSprite *arg0);
static void THPDecodeFunc(void *param);

static char THPFileName[64];

static UnkThpStruct04 audioTrack;
static s32 decodeRate;
static u8 *decodeStackP;
static OSThread *decodeThread;
static s16 THPLoopF;
static s16 THPStat;
static u32 THPFrame;
static s16 THPStart;
Process *THPProc;

s16 HuTHPSprCreateVol(char *path, s16 loop, s16 prio, float volume)
{
    s16 temp_r31;

    if (THPProc) {
        return -1;
    }
    THPStart = 0;
    THPProc = HuPrcCreate(THPTestProc, 0x64, 0x3000, 0);
    if (THPProc == 0) {
        return -1;
    }
    temp_r31 = HuSprFuncCreate(THPViewSprFunc, prio);
    if (temp_r31 == -1) {
        return -1;
    }
    THPSimpleInit(2);
    SimpleControl.unk19C = 0;
    SimpleControl.unk19E = temp_r31;
    SimpleControl.unkBC = volume;
    strcpy(THPFileName, path);
    THPLoopF = loop;
    THPStat = 0;
    THPFrame = 0;
    return temp_r31;
}

s16 HuTHPSprCreate(char *path, s16 loop, s16 prio)
{
    return HuTHPSprCreateVol(path, loop, prio, 110.0f);
}

s16 HuTHP3DCreateVol(char *path, s16 loop, float volume)
{
    s16 temp_r31;

    if (THPProc) {
        return;
    }
    THPStart = 0;
    THPProc = HuPrcCreate(THPTestProc, 0x64, 0x3000, 0);
    if (THPProc == 0) {
        return -1;
    }
    THPSimpleInit(2);
    SimpleControl.unk19C = 1;
    temp_r31 = Hu3DHookFuncCreate(&THPViewFunc);
    SimpleControl.unk19E = temp_r31;
    SimpleControl.unkBC = volume;
    strcpy(THPFileName, path);
    THPLoopF = loop;
    THPStat = 0;
    THPFrame = 0;
    Hu3DModelAttrSet(SimpleControl.unk19E, HU3D_ATTR_DISPOFF);
    return temp_r31;
}

s16 HuTHP3DCreate(char *path, s16 loop)
{
    return HuTHP3DCreateVol(path, loop, 110.0f);
}

void HuTHPStop(void)
{
    THPStat = 1;
}

void HuTHPClose(void)
{
    THPStat = 2;
}

void HuTHPRestart(void)
{
    THPStat = 3;
}

BOOL HuTHPEndCheck(void)
{
    s32 temp_r31;

    temp_r31 = THPSimpleGetTotalFrame() - 1;
    if (temp_r31 <= 0) {
        return FALSE;
    }
    return (temp_r31 <= THPFrame);
}

s32 HuTHPFrameGet(void)
{
    return THPFrame;
}

s32 HuTHPTotalFrameGet(void)
{
    return THPSimpleGetTotalFrame();
}

void HuTHPSetVolume(s32 left, s32 right)
{
    THPSimpleSetVolume(left, right);
}

static void THPTestProc(void)
{
    s32 temp_r29;
    u32 var_r28;
    void *temp_r30;

    while (THPSimpleOpen(THPFileName) == 0) {
        OSReport("THPSimpleOpen fail");
        HuPrcVSleep();
    }
    THPSimpleGetVideoInfo(&audioTrack);
    temp_r29 = THPSimpleCalcNeedMemory();
    OSReport("Size %x\n", temp_r29);
    temp_r30 = HuMemDirectMalloc(HEAP_DATA, temp_r29);
    memset(temp_r30, 0, temp_r29);
    DCFlushRange(temp_r30, temp_r29);
    if (temp_r30 == 0) {
        OSReport("Can't allocate the memory\n");
    }
    THPSimpleSetBuffer(temp_r30);
    while (THPSimplePreLoad(THPLoopF) == 0) {
        OSReport("THPSimplePreLoad fail");
        HuPrcVSleep();
    }
    HuPrcVSleep();
    decodeStackP = HuMemDirectMalloc(HEAP_SYSTEM, THP_DECODE_STACK_SIZE);
    decodeThread = OSSetIdleFunction(THPDecodeFunc, NULL, (decodeStackP + THP_DECODE_STACK_SIZE), THP_DECODE_STACK_SIZE);
    decodeRate = 0;
    THPStart = 1;
    if (SimpleControl.unk19C == 1) {
        Hu3DModelAttrReset(SimpleControl.unk19E, HU3D_ATTR_DISPOFF);
    }
    else {
        HuSprAttrReset(SimpleControl.unk19E, 0, HUSPR_ATTR_DISPOFF);
    }
    while (1) {
        if (THPStat == 2) {
            break;
        }
        switch (THPStat) {
            case 0:
                var_r28 = 1;
                THPStat = 4;
                break;
            case 1:
                THPSimpleAudioStop();
                THPSimpleLoadStop();
                break;
            case 3:
                THPSimpleAudioStop();
                THPSimpleLoadStop();
                while (THPSimplePreLoad(THPLoopF) == 0) {
                    OSReport("THPSimplePreLoad fail");
                    HuPrcVSleep();
                }
                THPStat = 0;
                var_r28 = 1;
                break;
        }
        if (var_r28 != 0) {
            THPSimpleAudioStart();
            var_r28 = 0;
        }
        HuPrcVSleep();
    }
    if (SimpleControl.unk19C == 1) {
        Hu3DModelKill(SimpleControl.unk19E);
    }
    else {
        HuSprKill(SimpleControl.unk19E);
    }
    OSCancelThread(decodeThread);
    HuMemDirectFree(decodeStackP);
    THPSimpleAudioStop();
    THPSimpleLoadStop();
    THPSimpleClose();
    HuMemDirectFree(temp_r30);
    THPSimpleQuit();
    THPProc = NULL;
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

static void THPViewFunc(ModelData *arg0, Mtx arg1)
{
    GXColor spC = { 0xFF, 0xFF, 0xFF, 0xFF };

    if (THPStart != 0) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXSetCullMode(GX_CULL_NONE);
        THPFrame
            = THPSimpleDrawCurrentFrame(RenderMode, &spC, arg1, -audioTrack.unk00 / 2, audioTrack.unk04 / 2, audioTrack.unk00, -audioTrack.unk04);
        THPSimpleAudioStart();
    }
}

static void THPViewSprFunc(HuSprite *arg0)
{
    Vec spC = { 0.0f, 0.0f, 1.0f };
    GXColor sp8;
    s32 temp_r30;
    s32 temp_r29;
    Mtx sp48;
    Mtx sp18;

    if (THPStart != 0) {
        sp8.r = arg0->r;
        sp8.g = arg0->g;
        sp8.b = arg0->b;
        sp8.a = arg0->a;
        if (arg0->z_rot != 0.0f) {
            PSMTXRotAxisRad(sp18, &spC, MTXDegToRad(arg0->z_rot));
            PSMTXScale(sp48, arg0->scale_x, arg0->scale_y, 1.0f);
            PSMTXConcat(sp18, sp48, sp48);
        }
        else {
            PSMTXScale(sp48, arg0->scale_x, arg0->scale_y, 1.0f);
        }
        mtxTransCat(sp48, arg0->x, arg0->y, 0.0f);
        PSMTXConcat(*arg0->group_mtx, sp48, sp48);
        temp_r30 = -((s32)audioTrack.unk00 / 2);
        temp_r29 = -((s32)audioTrack.unk04 / 2);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        THPFrame = THPSimpleDrawCurrentFrame(RenderMode, &sp8, sp48, temp_r30, temp_r29, audioTrack.unk00, audioTrack.unk04);
    }
}

static void THPDecodeFunc(void *param)
{
    while (1) {
        if (THPStat == 2) {
            break;
        }
        if (THPSimpleDecode() == 1) {
            OSReport("Fail to decode video data");
        }
        VIWaitForRetrace();
    }
}
