#include "REL/executor.h"
#include "REL/option.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "math.h"

typedef struct {
    /* 0x00 */ s16 id;
    /* 0x04 */ float tplvl;
    /* 0x08 */ float speed;
} FaderWork; // Size 0xC

static void FadeSprite(void);
static void fn_1_354(s16 arg0, s32 arg1, s32 arg2);
static void FadeModel(void);
static void SceneMain(omObjData *arg0);
static void KillScene(void);

Process *optionObjMan;
static omObjData *scene;
static s32 rumbleF;

void ObjectSetup(void)
{
    optionObjMan = omInitObjMan(0x40, 0x2000);
    omGameSysInit(optionObjMan);
    HuWinInit(1);
    rumbleF = GWGameStat.rumble;
    scene = omAddObjEx(optionObjMan, 1000, 0, 0, 0, SceneMain);
    scene->unk10 = 0;
    optionState = OptionStateCreate();
}

void OptionFadeSprite(s16 sprite, BOOL inF, s32 duration)
{
    FaderWork *work;
    Process *process;

    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(FaderWork), MEMORY_DEFAULT_NUM);
    work->id = sprite;
    work->speed = 1.0f / duration;
    if (inF) {
        work->speed = work->speed;
        work->tplvl = 0.0f;
    }
    else {
        work->speed = -work->speed;
        work->tplvl = 1.0f;
    }
    espDispOn(work->id);
    espTPLvlSet(work->id, work->tplvl);
    process = HuPrcChildCreate(FadeSprite, 0x3000, 0x1500, 0, HuPrcCurrentGet());
    process->user_data = work;
}

static void FadeSprite(void)
{
    FaderWork *work = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        work->tplvl += work->speed;
        if (work->tplvl > 1.0f) {
            work->tplvl = 1.0f;
            break;
        }
        if (work->tplvl < 0.0f) {
            work->tplvl = 0.0f;
            break;
        }
        espTPLvlSet(work->id, work->tplvl);
        HuPrcVSleep();
    }
    espTPLvlSet(work->id, work->tplvl);
    if (work->tplvl <= 0.0f) {
        espDispOff(work->id);
    }
    HuMemDirectFree(work);
    HuPrcEnd();
}

void OptionFadeModel(s16 model, BOOL inF, s32 duration)
{
    FaderWork *work;
    Process *process;

    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(FaderWork), MEMORY_DEFAULT_NUM);
    work->id = model;
    work->speed = 1.0f / duration;
    if (inF) {
        work->speed = work->speed;
        work->tplvl = 0.0f;
    }
    else {
        work->speed = -work->speed;
        work->tplvl = 1.0f;
    }
    Hu3DModelAttrReset(work->id, HU3D_ATTR_DISPOFF);
    Hu3DModelTPLvlSet(work->id, work->tplvl);
    process = HuPrcChildCreate(FadeModel, 0x3000, 0x1500, 0, HuPrcCurrentGet());
    process->user_data = work;
}

static void FadeModel(void)
{
    FaderWork *work = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        work->tplvl += work->speed;
        if (work->tplvl > 1.0f) {
            work->tplvl = 1.0f;
            break;
        }
        if (work->tplvl < 0.0f) {
            work->tplvl = 0.0f;
            break;
        }
        Hu3DModelTPLvlSet(work->id, work->tplvl);
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(work->id, work->tplvl);
    if (work->tplvl <= 0.0f) {
        Hu3DModelAttrSet(work->id, HU3D_ATTR_DISPOFF);
    }
    HuMemDirectFree(work);
    HuPrcEnd();
}

BOOL OptionPadCheck(u16 btn)
{
    u32 temp_r31 = HuPadBtnDown[0] & btn;

    return (temp_r31 != 0);
}

BOOL OptionPadDStkRepCheck(u16 dir)
{
    u32 temp_r31 = HuPadDStkRep[0] & dir;

    return (temp_r31 != 0);
}

BOOL OptionPadDStkCheck(u16 dir)
{
    u32 temp_r31 = HuPadDStk[0] & dir;

    return (temp_r31 != 0);
}

static void SceneMain(omObjData *object)
{
    switch (object->unk10) {
        case 0:
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            if (!omSysExitReq) {
                break;
            }
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            if (WipeStatGet() == 0) {
                OptionStateKill(optionState);
                if (rumbleF != GWGameStat.rumble) {
                    omSysExitReq = 0;
                    KillScene();
                }
                omOvlReturnEx(1, 1);
            }
            break;
    }
}

static void KillScene(void)
{
    s16 sprite;

    if (SLSaveFlagGet() == 0) {
        return;
    }
    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    espInit();
    HuPrcVSleep();
    sprite = espEntry(0x860020, 0x1388, 0);
    espPosSet(sprite, 288.0f, 240.0f);
    espAttrReset(sprite, HUSPR_ATTR_DISPOFF);
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    SLCommonSet();
    if (SLSave() == 0) {
        GWSaveModeSet(1);
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
}
