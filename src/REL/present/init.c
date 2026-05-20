#include "game/audio.h"
#include "game/esprite.h"
#include "game/hsfman.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/wipe.h"

#ifndef __MWERKS__
#include "game/window.h"
#endif
#include "math.h"

#include "REL/present.h"

typedef struct FaderWork {
    /* 0x00 */ s16 id;
    /* 0x04 */ float tplvl;
    /* 0x08 */ float speed;
} FaderWork; /* size 0x0C */ // same as in option/scene.c

typedef struct FaderWork2 {
    /* 0x00 */ s16 id;
    /* 0x04 */ float tpMultiplier;
    /* 0x08 */ float tplvl;
    /* 0x0C */ float speed;
} FaderWork2; /* size = 0x10 */

omObjData *presentState;
omObjData *lbl_1_bss_14;
omObjData *present;
omObjData *lbl_1_bss_C;
omObjData *presentCamera;
Process *presentObjMan;
static omObjData *scene;

static void FadeSprite(void);
static void FadeModel(void);
static void SceneMain(omObjData *object);

void ObjectSetup(void)
{
    presentObjMan = omInitObjMan(150, 8192);
    omGameSysInit(presentObjMan);
    HuWinInit(1);
    scene = omAddObjEx(presentObjMan, 1000, 0, 0, 0, SceneMain);
    scene->unk10 = 0;
    presentState = PresentStateCreate();
}

void PresentFadeSprite(s16 sprite, BOOL inF, s32 duration)
{
    Process *process;

    FaderWork *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(FaderWork), MEMORY_DEFAULT_NUM);
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
    process = HuPrcChildCreate(FadeSprite, 100, 5376, 0, HuPrcCurrentGet());
    process->user_data = work;
}

static void FadeSprite(void)
{
    FaderWork *work = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        work->tplvl = work->tplvl + work->speed;
        if (work->tplvl > 1.0f) {
            work->tplvl = 1.0f;
            break;
        }
        else if (work->tplvl < 0.0f) {
            work->tplvl = 0.0f;
            break;
        }
        else {
            espTPLvlSet(work->id, work->tplvl);
            HuPrcVSleep();
        }
    }
    espTPLvlSet(work->id, work->tplvl);
    if (work->speed < 0.0f) {
        espDispOff(work->id);
    }
    HuMemDirectFree(work);
    HuPrcEnd();
}

void FadeSpriteWithMultiplier(s16 model, BOOL inF, float tpMultiplier, s32 duration)
{
    Process *process;
    //  bug: wrong struct in sizeof
    FaderWork2 *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(FaderWork), MEMORY_DEFAULT_NUM);
    work->id = model;
    work->speed = 1.0f / duration;
    work->tpMultiplier = tpMultiplier;

    if (inF) {
        work->speed = work->speed;
        work->tplvl = 0.0f;
    }
    else {
        work->speed = -work->speed;
        work->tplvl = 1.0f;
    }
    Hu3DModelTPLvlSet(work->id, work->tplvl * work->tpMultiplier);
    Hu3DModelAttrReset(work->id, HU3D_ATTR_DISPOFF);
    process = HuPrcChildCreate(FadeModel, 100, 5376, 0, HuPrcCurrentGet());
    process->user_data = work;
}

static void FadeModel(void)
{
    FaderWork2 *var_r31 = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        var_r31->tplvl += var_r31->speed;
        if (var_r31->tplvl > 1.0f) {
            var_r31->tplvl = 1.0f;
            break;
        }
        else if (var_r31->tplvl < 0.0f) {
            var_r31->tplvl = 0.0f;
            break;
        }
        else {
            Hu3DModelTPLvlSet(var_r31->id, var_r31->tplvl * var_r31->tpMultiplier);
            HuPrcVSleep();
        }
    }
    Hu3DModelTPLvlSet(var_r31->id, var_r31->tplvl * var_r31->tpMultiplier);
    if (var_r31->speed < 0.0f) {
        Hu3DModelAttrSet(var_r31->id, HU3D_ATTR_DISPOFF);
    }
    HuMemDirectFree(var_r31);
    HuPrcEnd();
}

BOOL PresentPadCheck(u16 btn)
{
    u32 pressed = HuPadBtnDown[0] & btn;
    return pressed != 0;
}

BOOL PresentPadDStkRepCheck(u16 dir)
{
    u32 pressed = HuPadDStkRep[0] & dir;
    return pressed != 0;
}

BOOL PresentPadDStkCheck(u16 dir)
{
    u32 pressed = HuPadDStk[0] & dir;
    return pressed != 0;
}

static void SceneMain(omObjData *object)
{
    switch (object->unk10) {
        case 0:
            object->unk10 = 1;
        case 1:
            if (!omSysExitReq) {
                break;
            }
            object->unk10 = 2;
        case 2:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            object->unk10 = 3;
            break;
        case 3:
            if (!WipeStatGet()) {
                PresentStateKill(presentState);
                omOvlReturnEx(1, 1);
            }
            break;
        default:
            break;
    }
}
