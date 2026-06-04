#include "REL/option.h"
#include "game/audio.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/window.h"

typedef struct {
    /* 0x00 */ OMOBJ *background;
    /* 0x04 */ OMOBJ *rumbleArrow;
    /* 0x08 */ OMOBJ *soundArrow;
    /* 0x0C */ OMOBJ *recordArrow;
    /* 0x10 */ OptionWindow *optionDescWindow;
    /* 0x14 */ OptionWindow *btnLegendWindow;
    /* 0x18 */ s32 optionIdx;
    /* 0x1C */ s32 execMode;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[6];
    /* 0x28 */ BOOL cameraDoneF;
} RoomWork; // Size 0x2C

#define MODE_DISABLED 0
#define MODE_HANDLE_ROOM 1


static void MoveOption(OMOBJ *object, BOOL rightF);
static void ExecRoom(OMOBJ *object);
static OMOBJ *CreateRoomBG(void);
static void KillRoomBG(OMOBJ *background);
static OMOBJ *CreateArrow(void);
static void KillArrow(OMOBJ *arrow);

OMOBJ *optionRoom;

static OMOBJFUNC execModeTbl[] = { NULL, ExecRoom };

OMOBJ *OptionRoomCreate(void)
{
    OMOBJ *object;
    RoomWork *work;

    object = omAddObjEx(optionObjMan, 1003, 0, 0, 1, NULL);
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(RoomWork), HU_MEMNUM_OVL);
    object->data = work;
    work->optionIdx = 0;
    work->unk20 = -1;
    work->cameraDoneF = 0;
    OptionCameraViewSet(optionCamera, 600.0f, 60.0f, 120.0f, 1);
    OptionCameraTargetSet(optionCamera, 0.0f, 120.0f, 0.0f, 1);
    work->background = CreateRoomBG();
    optionSound = OptionSoundCreate();
    optionRecord = OptionRecordCreate();
    optionRumble = OptionRumbleCreate();
    optionGuide = OptionGuideCreate();
    work->rumbleArrow = CreateArrow();
    work->soundArrow = CreateArrow();
    work->recordArrow = CreateArrow();
    omSetRot(work->rumbleArrow, 0.0f, 0.0f, 0.0f);
    omSetRot(work->soundArrow, 0.0f, 120.0f, 0.0f);
    omSetRot(work->recordArrow, 0.0f, 240.0f, 0.0f);
    work->optionDescWindow = OptionWinCreate(0);
    work->btnLegendWindow = OptionWinCreate(1);
    return object;
}

void OptionRoomKill(OMOBJ *object)
{
    RoomWork *work = object->data;

    KillRoomBG(work->background);
    OptionSoundKill(optionSound);
    OptionRumbleKill(optionRumble);
    OptionRecordKill(optionRecord);
    OptionGuideKill(optionGuide);
    KillArrow(work->rumbleArrow);
    KillArrow(work->soundArrow);
    KillArrow(work->recordArrow);
    OptionWinKill(work->optionDescWindow);
    OptionWinKill(work->btnLegendWindow);
    HuMemDirectFree(work);
}

static const float guideAngleTbl[3] = { 45.0f, 165.0f, 285.0f };

static void MoveOption(OMOBJ *object, BOOL rightF)
{
    RoomWork *work = object->data;
    float x;
    float y;
    float z;
    float guideAngle;

    work->optionIdx += (rightF == FALSE) ? -1 : 1;
    if (work->optionIdx < 0) {
        work->optionIdx = 2;
    }
    else if (work->optionIdx >= 3) {
        work->optionIdx = 0;
    }
    OptionCameraTargetGet(optionCamera, &x, &y, &z);
    OptionCameraViewSet(optionCamera, OptionCameraZoomGet(optionCamera), OptionCameraRotGet(optionCamera) + (rightF == FALSE ? -120.0f : 120.0f), y, 96);
    if (work->optionIdx == 2 && rightF == FALSE) {
        guideAngle = guideAngleTbl[2] - 360.0f;
    }
    else if (work->optionIdx == 0 && rightF == TRUE) {
        guideAngle = 360.0f + guideAngleTbl[0];
    }
    else {
        guideAngle = guideAngleTbl[work->optionIdx];
    }
    OptionGuideWalkExec(optionGuide, guideAngle, 430.0f, 96);
}

void OptionRoomExecModeSet(OMOBJ *object, s32 execMode)
{
    RoomWork *work = object->data;

    work->execMode = execMode;
    object->objFunc = execModeTbl[execMode];
    object->mode = 0;
    object->mode = 0;
}

s32 OptionRoomExecModeGet(OMOBJ *object)
{
    RoomWork *work = object->data;

    return work->execMode;
}

static const s32 optionDescTbl[] = { MAKE_MESSID(47, 1), MAKE_MESSID(47, 7), MAKE_MESSID(47, 4) };

static void ExecRoom(OMOBJ *object)
{
    RoomWork *work = object->data;

    switch (object->mode) {
        case 0:
            if (!work->cameraDoneF) {
                OptionCameraViewSet(optionCamera, 600.0f, 60.0f, 120.0f, 1);
                OptionCameraTargetSet(optionCamera, 0.0f, 120.0f, 0.0f, 1);
                work->cameraDoneF = TRUE;
            }
            object->mode = 1;
            /* fallthrough */
        case 1:
            if (OptionCameraDoneCheck(optionCamera) != 0) {
                break;
            }
            OptionWinAnimIn(work->optionDescWindow);
            OptionWinMesSet(work->optionDescWindow, optionDescTbl[work->optionIdx]);
            OptionWinAnimIn(work->btnLegendWindow);
            OptionWinMesSet(work->btnLegendWindow, MAKE_MESSID(47, 14));
            object->mode = 2;
            /* fallthrough */
        case 2:
            if (work->optionDescWindow->state == 0 && work->btnLegendWindow->state == 0) {
                if (OptionPadCheck(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    object->mode = 7;
                }
                else if (OptionPadDStkRepCheck(1)) {
                    MoveOption(object, FALSE);
                    OptionWinAnimOut(work->optionDescWindow);
                    OptionWinAnimOut(work->btnLegendWindow);
                    HuAudFXPlay(0);
                    object->mode = 1;
                }
                else if (OptionPadDStkRepCheck(2)) {
                    MoveOption(object, TRUE);
                    OptionWinAnimOut(work->optionDescWindow);
                    OptionWinAnimOut(work->btnLegendWindow);
                    HuAudFXPlay(0);
                    object->mode = 1;
                }
                else if (OptionPadCheck(PAD_BUTTON_A)) {
                    OptionWinAnimOut(work->optionDescWindow);
                    OptionWinAnimOut(work->btnLegendWindow);
                    HuAudFXPlay(2);
                    object->mode = 3;
                }
            }
            break;
        case 3:
            if (work->optionDescWindow->state == 0 && work->btnLegendWindow->state == 0) {
                switch (work->optionIdx) {
                    case 0:
                        OptionRumbleExecModeSet(optionRumble, 1);
                        object->mode = 4;
                        break;
                    case 1:
                        OptionSoundExecModeSet(optionSound, 1);
                        object->mode = 5;
                        break;
                    case 2:
                        OptionRecordExecModeSet(optionRecord, 1);
                        object->mode = 6;
                        break;
                }
            }
            break;
        case 4:
            if (OptionRumbleExecModeGet(optionRumble) == 0) {
                object->mode = 1;
            }
            break;
        case 5:
            if (OptionSoundExecModeGet(optionSound) == 0) {
                object->mode = 1;
            }
            break;
        case 6:
            if (OptionRecordExecModeGet(optionRecord) == 0) {
                object->mode = 1;
            }
            break;
        case 7:
            OptionWinAnimOut(work->optionDescWindow);
            OptionWinAnimOut(work->btnLegendWindow);
            object->mode = 8;
            /* fallthrough */
        case 8:
            if (work->optionDescWindow->state == 0 && work->btnLegendWindow->state == 0) {
                OptionRoomExecModeSet(object, MODE_DISABLED);
            }
            break;
    }
}

static OMOBJ *CreateRoomBG(void)
{
    OMOBJ *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 0));
    Hu3DModelLayerSet(object->mdlId[0], 0);
    Hu3DModelShadowMapSet(object->mdlId[0]);
    return object;
}

static void KillRoomBG(OMOBJ *object)
{
    Hu3DModelKill(object->mdlId[0]);
}

static OMOBJ *CreateArrow(void)
{
    OMOBJ *arrow;

    arrow = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    Hu3DModelLayerSet(arrow->mdlId[0], 0);
    arrow->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 6));
    return arrow;
}

static void KillArrow(OMOBJ *arrow)
{
    Hu3DModelKill(arrow->mdlId[0]);
}
