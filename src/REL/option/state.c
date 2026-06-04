#include "REL/option.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/window.h"
#include "game/wipe.h"

#include "dolphin.h"

typedef struct {
    /* 0x00 */ OptionWindow *window;
    /* 0x04 */ s32 quitTimer;
    /* 0x08 */ s16 light;
} StateWork; /* size = 0x0C */

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec dest;
    /* 0x18 */ GXColor color;
} UnkLightDataStruct; /* size = 0x1C */ // TODO same as m446Dll::unkStruct10 and present::UnkPresentStruct3

typedef struct UnkShadowDataStruct {
    /* 0x00 */ Vec camPos;
    /* 0x0C */ Vec camUp;
    /* 0x18 */ Vec camTarget;
} UnkShadowDataStruct; /* size = 0x24 */

static void ExecState(OMOBJ *object);

OMOBJ *optionState;

static UnkLightDataStruct lightTbl = {
    { 0.0f, 300.0f, 0.0f },
    { 0.0f, -300.0f, -600.0f },
    { 0xFF, 0xFF, 0xFF, 0xFF },
};

static UnkShadowDataStruct shadowPosTbl = {
    { 0.0f, 3000.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};

OMOBJ *OptionStateCreate(void)
{
    HU3DLIGHT *lightData;

    OMOBJ *object = omAddObjEx(optionObjMan, 1000, 0, 0, 4, ExecState);
    StateWork *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(StateWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    optionCamera = OptionCameraCreate();
    optionRoom = OptionRoomCreate();
    work->window = OptionWinCreate(0);
    Hu3DLighInit();
    work->light = Hu3DGLightCreateV(&lightTbl.pos, &lightTbl.dest, &lightTbl.color);
    Hu3DGLightInfinitytSet(work->light);
    lightData = &Hu3DGlobalLight[work->light];
    Hu3DShadowCreate(30.0f, 20.0f, 5000.0f);
    Hu3DShadowTPLvlSet(0.45f);
    Hu3DShadowPosSet(&shadowPosTbl.camPos, &shadowPosTbl.camUp, &shadowPosTbl.camTarget);
    return object;
}

void OptionStateKill(OMOBJ *object)
{
    StateWork *work = object->data;

    OptionCameraKill(optionCamera);
    OptionRoomKill(optionRoom);
    OptionWinKill(work->window);
    HuMemDirectFree(work);
}

static void ExecState(OMOBJ *object)
{
    StateWork *work = object->data;

    switch (object->mode) {
        case 0:
            object->mode = 1;
            /* fallthrough */
        case 1:
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREV, 60);
            object->mode = 2;
            break;
        case 2:
            if (WipeStatGet() != 0 || work->window->state != 0) {
                break;
            }
            OptionRoomExecModeSet(optionRoom, 1);
            object->mode = 3;
            /* fallthrough */
        case 3:
            if (OptionRoomExecModeGet(optionRoom) != 0) {
                break;
            }
            object->mode = 4;
            /* fallthrough */
        case 4:
            OptionWinAnimIn(work->window);
            OptionWinMesSet(work->window, MAKE_MESSID(47, 167)); // Would you like to leave?
            object->mode = 5;
            /* fallthrough */
        case 5:
            if (work->window->state != 0) {
                break;
            }
            OptionWinChoiceSet(work->window, 1);
            object->mode = 6;
            /* fallthrough */
        case 6:
            if (work->window->state != 0) {
                break;
            }
            OptionWinAnimOut(work->window);
            if (work->window->choice == 0) {
                work->quitTimer = 0;
                object->mode = 7;
            }
            else {
                object->mode = 2;
            }
            break;
        case 7:
            object->mode = 8;
            work->quitTimer = 0;
            /* fallthrough */
        case 8:
            if (work->window->state == 0 && work->quitTimer++ >= 60) {
                omSysExitReq = 1;
            }
            break;
    }
}
