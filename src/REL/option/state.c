#include "REL/option.h"
#include "game/hsfman.h"
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
    /* 0x00 */ Vec src;
    /* 0x0C */ Vec dest;
    /* 0x18 */ GXColor color;
} UnkLightDataStruct; /* size = 0x1C */ // TODO same as m446Dll::unkStruct10 and present::UnkPresentStruct3

typedef struct UnkShadowDataStruct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec up;
    /* 0x18 */ Vec target;
} UnkShadowDataStruct; /* size = 0x24 */

static void ExecState(omObjData *object);

omObjData *optionState;

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

omObjData *OptionStateCreate(void)
{
    LightData *lightData;

    omObjData *object = omAddObjEx(optionObjMan, 1000, 0, 0, 4, ExecState);
    StateWork *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(StateWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    optionCamera = OptionCameraCreate();
    optionRoom = OptionRoomCreate();
    work->window = OptionWinCreate(0);
    Hu3DLighInit();
    work->light = Hu3DGLightCreateV(&lightTbl.src, &lightTbl.dest, &lightTbl.color);
    Hu3DGLightInfinitytSet(work->light);
    lightData = &Hu3DGlobalLight[work->light];
    Hu3DShadowCreate(30.0f, 20.0f, 5000.0f);
    Hu3DShadowTPLvlSet(0.45f);
    Hu3DShadowPosSet(&shadowPosTbl.pos, &shadowPosTbl.up, &shadowPosTbl.target);
    return object;
}

void OptionStateKill(omObjData *object)
{
    StateWork *work = object->data;

    OptionCameraKill(optionCamera);
    OptionRoomKill(optionRoom);
    OptionWinKill(work->window);
    HuMemDirectFree(work);
}

static void ExecState(omObjData *object)
{
    StateWork *work = object->data;

    switch (object->unk10) {
        case 0:
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            WipeCreate(WIPE_MODE_IN, -1, 60);
            object->unk10 = 2;
            break;
        case 2:
            if (WipeStatGet() != 0 || work->window->state != 0) {
                break;
            }
            OptionRoomExecModeSet(optionRoom, 1);
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            if (OptionRoomExecModeGet(optionRoom) != 0) {
                break;
            }
            object->unk10 = 4;
            /* fallthrough */
        case 4:
            OptionWinAnimIn(work->window);
            OptionWinMesSet(work->window, MAKE_MESSID(47, 167)); // Would you like to leave?
            object->unk10 = 5;
            /* fallthrough */
        case 5:
            if (work->window->state != 0) {
                break;
            }
            OptionWinChoiceSet(work->window, 1);
            object->unk10 = 6;
            /* fallthrough */
        case 6:
            if (work->window->state != 0) {
                break;
            }
            OptionWinAnimOut(work->window);
            if (work->window->choice == 0) {
                work->quitTimer = 0;
                object->unk10 = 7;
            }
            else {
                object->unk10 = 2;
            }
            break;
        case 7:
            object->unk10 = 8;
            work->quitTimer = 0;
            /* fallthrough */
        case 8:
            if (work->window->state == 0 && work->quitTimer++ >= 60) {
                omSysExitReq = 1;
            }
            break;
    }
}
