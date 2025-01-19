#include "REL/option.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/window.h"

typedef struct {
    /* 0x00 */ omObjData *system;
    /* 0x04 */ omObjData *pad;
    /* 0x08 */ omObjData *padFilter;
    /* 0x0C */ omObjData *hand;
    /* 0x10 */ omObjData *hiliteOn;
    /* 0x14 */ OptionWindow *window[2];
    /* 0x20 */ s32 execMode;
    /* 0x20 */ BOOL rumbleF;
    /* 0x24 */ BOOL cameraDoneF;
    /* 0x28 */ s32 changeTimer;
} RumbleWork; // Size 0x2C

#define MODE_DISABLED 0
#define MODE_HANDLE_RUMBLE 1 // TODO room.c should have access to this

static void ExecRumble(omObjData *object);
static omObjData *CreateHand(void);
static void KillHand(omObjData *hand);
static omObjData *CreateSystem(void);
static void KillSystem(omObjData *system);
static void StartSystemMotion(omObjData *system, s32 rumbleF, BOOL slowF);
static omObjData *CreatePad(void);
static void KillPad(omObjData *pad);
static void ShakePad(omObjData *pad, BOOL on);
static omObjData *CreatePadFilter(void);
static void KillPadFilter(omObjData *object);
static omObjData *CreateHiliteOn(void);
static void KillHiliteOn(omObjData *object);

omObjData *optionRumble;

static omObjFunc execModeTbl[] = { NULL, ExecRumble };

omObjData *OptionRumbleCreate(void)
{
    omObjData *object;
    RumbleWork *work;

    object = omAddObjEx(optionObjMan, 1003, 0, 0, 1, NULL);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(RumbleWork), MEMORY_DEFAULT_NUM);
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

void OptionRumbleKill(omObjData *object)
{
    RumbleWork *work = object->data;

    KillHand(work->hand);
    KillSystem(work->system);
    KillPad(work->pad);
    KillHiliteOn(work->hiliteOn);
    KillPadFilter(work->padFilter);
    HuMemDirectFree(work);
}

void OptionRumbleExecModeSet(omObjData *object, s32 execMode)
{
    RumbleWork *work = object->data;

    work->execMode = execMode;
    object->func = execModeTbl[execMode];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 OptionRumbleExecModeGet(omObjData *object)
{
    RumbleWork *work = object->data;

    return work->execMode;
}

static void ExecRumble(omObjData *object)
{
    RumbleWork *work = object->data;
    s32 i;

    switch (object->unk10) {
        case 0:
            work->window[0] = OptionWinCreate(0);
            work->window[1] = OptionWinCreate(1);
            OptionCameraFocusSet(optionCamera, -519.62f, 135.0f, 300.0f, 0x28);
            OptionCameraTargetSet(optionCamera, -315.64f, 135.0f, 182.25f, 0x28);
            OptionRumbleMotionShowStart(object);
            Hu3DModelLayerSet(work->padFilter->model[0], 1);
            work->cameraDoneF = FALSE;
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            if (OptionCameraDoneCheck(optionCamera) != 0) {
                break;
            }
            if (!work->cameraDoneF) {
                Hu3DModelAttrReset(work->hand->model[0], HU3D_ATTR_DISPOFF);
                work->cameraDoneF = TRUE;
                Hu3DModelHookSet(work->system->model[0], "target", work->hand->model[0]);
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
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (OptionPadCheck(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    object->unk10 = 4;
                }
                else if (OptionPadDStkRepCheck(8) && !work->rumbleF) {
                    StartSystemMotion(work->system, 1, TRUE);
                    work->rumbleF = TRUE;
                    work->changeTimer = 0;
                    GWRumbleSet(1);
                    object->unk10 = 3;
                }
                else if (OptionPadDStkRepCheck(4) && work->rumbleF) {
                    StartSystemMotion(work->system, 0, TRUE);
                    work->rumbleF = FALSE;
                    work->changeTimer = 0;
                    GWRumbleSet(0);
                    object->unk10 = 3;
                }
            }
            break;
        case 3:
            if (work->changeTimer++ >= 60) {
                HuAudFXPlay(0x83C);
                ShakePad(work->pad, work->rumbleF);
                if (work->rumbleF) {
                    HuPadRumbleSet(0, 60, 10, 5);
                    Hu3DMotionTimeSet(work->hiliteOn->model[0], 0.0f);
                    Hu3DModelAttrReset(work->hiliteOn->model[0], HU3D_ATTR_DISPOFF);
                }
                else {
                    Hu3DModelAttrSet(work->hiliteOn->model[0], HU3D_ATTR_DISPOFF);
                }
                object->unk10 = 1;
            }
            break;
        case 4:
            OptionWinAnimOut(work->window[1]);
            OptionWinAnimOut(work->window[0]);
            Hu3DModelAttrSet(work->hand->model[0], HU3D_ATTR_DISPOFF);
            OptionRumbleMotionHideStart(object);
            object->unk10 = 5;
            /* fallthrough */
        case 5:
            if (work->window[1]->state == 0 && work->window[0]->state == 0 && !OptionRumbleMotionCheck(optionRumble)) {
                for (i = 0; i < 2; i++) {
                    OptionWinKill(work->window[i]);
                }
                Hu3DModelHookReset(work->system->model[0]);
                OptionCameraFocusSet(optionCamera, -519.62f, 120.0f, 300.0f, 0x28);
                OptionCameraTargetSet(optionCamera, 0.0f, 120.0f, 0.0f, 0x28);
                OptionRumbleExecModeSet(object, MODE_DISABLED);
            }
            break;
    }
}

static omObjData *CreateHand(void)
{
    omObjData *hand;

    hand = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    hand->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 15));
    Hu3DModelLayerSet(hand->model[0], 3);
    omSetRot(hand, 0.0f, 180.0f, 0.0f);
    Hu3DModelAttrSet(hand->model[0], HU3D_ATTR_DISPOFF);
    return hand;
}

static void KillHand(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}

static omObjData *CreateSystem(void)
{
    omObjData *system;

    system = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    system->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 2));
    Hu3DModelAttrSet(system->model[0], HU3D_MOTATTR_PAUSE);
    if (GWRumbleGet()) {
        Hu3DMotionTimeSet(system->model[0], 60.0f);
    }
    else {
        Hu3DMotionTimeSet(system->model[0], 0.0f);
    }
    return system;
}

static void KillSystem(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}

static void StartSystemMotion(omObjData *object, s32 rumbleF, BOOL slowF)
{
    s16 model = object->model[0];

    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
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

static omObjData *CreatePad(void)
{
    omObjData *pad;

    pad = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    pad->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 9));
    Hu3DModelAttrSet(pad->model[0], HU3D_MOTATTR_LOOP);
    return pad;
}

static void KillPad(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}

static void ShakePad(omObjData *object, BOOL on)
{
    if (on) {
        Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    }
    else {
        Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
    }
}

static omObjData *CreatePadFilter(void)
{
    omObjData *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 10));
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(object->model[0], 2);

    return object;
}

static void KillPadFilter(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}

void OptionRumbleMotionShowStart(omObjData *object)
{
    RumbleWork *work = object->data;
    s16 model = work->padFilter->model[0];

    Hu3DMotionStartEndSet(model, 0.0f, 40.0f);
    Hu3DMotionTimeSet(model, 0.0f);
    Hu3DModelAttrReset(work->padFilter->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(work->padFilter->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(work->padFilter->model[0], 2);
    HuAudFXPlay(0x83D);
}

void OptionRumbleMotionHideStart(omObjData *object)
{
    RumbleWork *work = object->data;
    s16 model = work->padFilter->model[0];

    Hu3DMotionStartEndSet(model, 40.0f, 80.0f);
    Hu3DMotionTimeSet(model, 40.0f);
    Hu3DModelAttrReset(work->padFilter->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(work->padFilter->model[0], HU3D_MOTATTR_LOOP);
    HuAudFXPlay(0x83E);
}

BOOL OptionRumbleMotionCheck(omObjData *object)
{
    RumbleWork *work = object->data;
    s16 padFilterModel = work->padFilter->model[0];

    return !Hu3DMotionEndCheck(padFilterModel);
}

static omObjData *CreateHiliteOn(void)
{
    omObjData *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 11));
    if (GWRumbleGet()) {
        Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    }
    return object;
}

static void KillHiliteOn(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}
