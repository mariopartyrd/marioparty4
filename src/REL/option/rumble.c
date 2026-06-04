#include "REL/option.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/window.h"

typedef struct {
    /* 0x00 */ OMOBJ *system;
    /* 0x04 */ OMOBJ *pad;
    /* 0x08 */ OMOBJ *padFilter;
    /* 0x0C */ OMOBJ *hand;
    /* 0x10 */ OMOBJ *hiliteOn;
    /* 0x14 */ OptionWindow *window[2];
    /* 0x20 */ s32 execMode;
    /* 0x20 */ BOOL rumbleF;
    /* 0x24 */ BOOL cameraDoneF;
    /* 0x28 */ s32 changeTimer;
} RumbleWork; // Size 0x2C

#define MODE_DISABLED 0
#define MODE_HANDLE_RUMBLE 1 // TODO room.c should have access to this

static void ExecRumble(OMOBJ *object);
static OMOBJ *CreateHand(void);
static void KillHand(OMOBJ *hand);
static OMOBJ *CreateSystem(void);
static void KillSystem(OMOBJ *system);
static void StartSystemMotion(OMOBJ *system, s32 rumbleF, BOOL slowF);
static OMOBJ *CreatePad(void);
static void KillPad(OMOBJ *pad);
static void ShakePad(OMOBJ *pad, BOOL on);
static OMOBJ *CreatePadFilter(void);
static void KillPadFilter(OMOBJ *object);
static OMOBJ *CreateHiliteOn(void);
static void KillHiliteOn(OMOBJ *object);

OMOBJ *optionRumble;

static OMOBJFUNC execModeTbl[] = { NULL, ExecRumble };

OMOBJ *OptionRumbleCreate(void)
{
    OMOBJ *object;
    RumbleWork *work;

    object = omAddObjEx(optionObjMan, 1003, 0, 0, 1, NULL);
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(RumbleWork), HU_MEMNUM_OVL);
    object->data = work;
    work->rumbleF = GWGameStat.rumble;
    work->system = CreateSystem();
    StartSystemMotion(work->system, work->rumbleF, 0);
    work->pad = CreatePad();
    ShakePad(work->pad, work->rumbleF);
    work->padFilter = CreatePadFilter();
    work->hiliteOn = CreateHiliteOn();
    work->hand = CreateHand();
    OptionRumbleExecModeSet(object, MODE_DISABLED);

    return object;
}

void OptionRumbleKill(OMOBJ *object)
{
    RumbleWork *work = object->data;

    KillHand(work->hand);
    KillSystem(work->system);
    KillPad(work->pad);
    KillHiliteOn(work->hiliteOn);
    KillPadFilter(work->padFilter);
    HuMemDirectFree(work);
}

void OptionRumbleExecModeSet(OMOBJ *object, s32 execMode)
{
    RumbleWork *work = object->data;

    work->execMode = execMode;
    object->objFunc = execModeTbl[execMode];
    object->mode = 0;
    object->mode = 0;
}

s32 OptionRumbleExecModeGet(OMOBJ *object)
{
    RumbleWork *work = object->data;

    return work->execMode;
}

static void ExecRumble(OMOBJ *object)
{
    RumbleWork *work = object->data;
    s32 i;

    switch (object->mode) {
        case 0:
            work->window[0] = OptionWinCreate(0);
            work->window[1] = OptionWinCreate(1);
            OptionCameraFocusSet(optionCamera, -519.62f, 135.0f, 300.0f, 0x28);
            OptionCameraTargetSet(optionCamera, -315.64f, 135.0f, 182.25f, 0x28);
            OptionRumbleMotionShowStart(object);
            Hu3DModelLayerSet(work->padFilter->mdlId[0], 1);
            work->cameraDoneF = FALSE;
            object->mode = 1;
            /* fallthrough */
        case 1:
            if (OptionCameraDoneCheck(optionCamera) != 0) {
                break;
            }
            if (!work->cameraDoneF) {
                Hu3DModelAttrReset(work->hand->mdlId[0], HU3D_ATTR_DISPOFF);
                work->cameraDoneF = TRUE;
                Hu3DModelHookSet(work->system->mdlId[0], "target", work->hand->mdlId[0]);
            }
            OptionWinAnimIn(work->window[1]);
            OptionWinMesSet(work->window[1], MAKE_MESSID(47, 15));
            OptionWinAnimIn(work->window[0]);
            if (work->rumbleF) {
                OptionWinMesSet(work->window[0], MAKE_MESSID(47, 2));
            }
            else {
                OptionWinMesSet(work->window[0], MAKE_MESSID(47, 3));
            }
            object->mode = 2;
            /* fallthrough */
        case 2:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (OptionPadCheck(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    object->mode = 4;
                }
                else if (OptionPadDStkRepCheck(8) && !work->rumbleF) {
                    StartSystemMotion(work->system, 1, TRUE);
                    work->rumbleF = TRUE;
                    work->changeTimer = 0;
                    GWRumbleSet(1);
                    object->mode = 3;
                }
                else if (OptionPadDStkRepCheck(4) && work->rumbleF) {
                    StartSystemMotion(work->system, 0, TRUE);
                    work->rumbleF = FALSE;
                    work->changeTimer = 0;
                    GWRumbleSet(0);
                    object->mode = 3;
                }
            }
            break;
        case 3:
            if (work->changeTimer++ >= 60) {
                HuAudFXPlay(0x83C);
                ShakePad(work->pad, work->rumbleF);
                if (work->rumbleF) {
                    HuPadRumbleSet(0, 60, 10, 5);
                    Hu3DMotionTimeSet(work->hiliteOn->mdlId[0], 0.0f);
                    Hu3DModelAttrReset(work->hiliteOn->mdlId[0], HU3D_ATTR_DISPOFF);
                }
                else {
                    Hu3DModelAttrSet(work->hiliteOn->mdlId[0], HU3D_ATTR_DISPOFF);
                }
                object->mode = 1;
            }
            break;
        case 4:
            OptionWinAnimOut(work->window[1]);
            OptionWinAnimOut(work->window[0]);
            Hu3DModelAttrSet(work->hand->mdlId[0], HU3D_ATTR_DISPOFF);
            OptionRumbleMotionHideStart(object);
            object->mode = 5;
            /* fallthrough */
        case 5:
            if (work->window[1]->state == 0 && work->window[0]->state == 0 && !OptionRumbleMotionCheck(optionRumble)) {
                for (i = 0; i < 2; i++) {
                    OptionWinKill(work->window[i]);
                }
                Hu3DModelHookReset(work->system->mdlId[0]);
                OptionCameraFocusSet(optionCamera, -519.62f, 120.0f, 300.0f, 0x28);
                OptionCameraTargetSet(optionCamera, 0.0f, 120.0f, 0.0f, 0x28);
                OptionRumbleExecModeSet(object, MODE_DISABLED);
            }
            break;
    }
}

static OMOBJ *CreateHand(void)
{
    OMOBJ *hand;

    hand = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    hand->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 15));
    Hu3DModelLayerSet(hand->mdlId[0], 3);
    omSetRot(hand, 0.0f, 180.0f, 0.0f);
    Hu3DModelAttrSet(hand->mdlId[0], HU3D_ATTR_DISPOFF);
    return hand;
}

static void KillHand(OMOBJ *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->mdlId[i]);
    }
}

static OMOBJ *CreateSystem(void)
{
    OMOBJ *system;

    system = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    system->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 2));
    Hu3DModelAttrSet(system->mdlId[0], HU3D_MOTATTR_PAUSE);
    if (GWRumbleGet()) {
        Hu3DMotionTimeSet(system->mdlId[0], 60.0f);
    }
    else {
        Hu3DMotionTimeSet(system->mdlId[0], 0.0f);
    }
    return system;
}

static void KillSystem(OMOBJ *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->mdlId[i]);
    }
}

static void StartSystemMotion(OMOBJ *object, s32 rumbleF, BOOL slowF)
{
    s16 model = object->mdlId[0];

    Hu3DModelAttrReset(object->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(object->mdlId[0], HU3D_MOTATTR_LOOP);
    if (rumbleF) {
        Hu3DMotionStartEndSet(model, 60.0f, 120.0f);
        if (slowF) {
            Hu3DMotionTimeSet(model, 60.0f);
        }
        else {
            Hu3DMotionTimeSet(model, 119.0f);
        }
    }
    else {
        Hu3DMotionStartEndSet(model, 0.0f, 60.0f);
        if (slowF) {
            Hu3DMotionTimeSet(model, 0.0f);
        }
        else {
            Hu3DMotionTimeSet(model, 59.0f);
        }
    }
}

static OMOBJ *CreatePad(void)
{
    OMOBJ *pad;

    pad = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    pad->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 9));
    Hu3DModelAttrSet(pad->mdlId[0], HU3D_MOTATTR_LOOP);
    return pad;
}

static void KillPad(OMOBJ *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->mdlId[i]);
    }
}

static void ShakePad(OMOBJ *object, BOOL on)
{
    if (on) {
        Hu3DModelAttrReset(object->mdlId[0], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
    }
    else {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(object->mdlId[0], HU3D_MOTATTR_LOOP);
    }
}

static OMOBJ *CreatePadFilter(void)
{
    OMOBJ *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 10));
    Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(object->mdlId[0], 2);

    return object;
}

static void KillPadFilter(OMOBJ *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->mdlId[i]);
    }
}

void OptionRumbleMotionShowStart(OMOBJ *object)
{
    RumbleWork *work = object->data;
    s16 model = work->padFilter->mdlId[0];

    Hu3DMotionStartEndSet(model, 0.0f, 40.0f);
    Hu3DMotionTimeSet(model, 0.0f);
    Hu3DModelAttrReset(work->padFilter->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(work->padFilter->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(work->padFilter->mdlId[0], 2);
    HuAudFXPlay(0x83D);
}

void OptionRumbleMotionHideStart(OMOBJ *object)
{
    RumbleWork *work = object->data;
    s16 model = work->padFilter->mdlId[0];

    Hu3DMotionStartEndSet(model, 40.0f, 80.0f);
    Hu3DMotionTimeSet(model, 40.0f);
    Hu3DModelAttrReset(work->padFilter->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(work->padFilter->mdlId[0], HU3D_MOTATTR_LOOP);
    HuAudFXPlay(0x83E);
}

BOOL OptionRumbleMotionCheck(OMOBJ *object)
{
    RumbleWork *work = object->data;
    s16 padFilterModel = work->padFilter->mdlId[0];

    return !Hu3DMotionEndCheck(padFilterModel);
}

static OMOBJ *CreateHiliteOn(void)
{
    OMOBJ *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 11));
    if (GWRumbleGet()) {
        Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    }
    return object;
}

static void KillHiliteOn(OMOBJ *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->mdlId[i]);
    }
}
