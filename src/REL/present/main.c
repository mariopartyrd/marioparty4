#include "game/audio.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/present.h"

typedef struct StateWork {
    /* 0x00 */ PresentWindow *window;
    /* 0x04 */ s32 quitTimer;
} StateWork; /* size = 0x08 */

typedef struct UnkShadowDataStruct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec up;
    /* 0x18 */ Vec target;
} UnkShadowDataStruct; /* size = 0x24 */

omObjData *presentGuide;

static UnkShadowDataStruct shadowPosTbl = {
    { 0.0f, 3000.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};

static void ExecPresentView(omObjData *object);
static void ExecPresentGet(omObjData *object);
void PresentWinDispOff(PresentWindow *work);
void PresentWinChoiceSet(PresentWindow *work, s32 choice);
static void ExecWindow(void);

omObjData *PresentStateCreate(void)
{
    omObjData *object = omAddObjEx(presentObjMan, 1000, 0, 0, 4, NULL);
    StateWork *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(StateWork), MEMORY_DEFAULT_NUM);
    object->data = work;

    work->quitTimer = 0;
    presentCamera = PresentCameraCreate();
    present = PresentCreate();
    presentGuide = PresentGuideCreate();
    work->window = PresentWinCreate(0);
    Hu3DShadowCreate(30.0f, 20.0f, 5000.0f);
    Hu3DShadowTPLvlSet(0.45f);
    Hu3DShadowPosSet(&shadowPosTbl.pos, &shadowPosTbl.up, &shadowPosTbl.target);

    if (omovlevtno > 0) {
        OSReport("*** PRESENTROOM ( PRESENT GET MODE ) ***\n");
        object->func = ExecPresentGet;
        object->unk10 = 0;
    }
    else {
        OSReport("*** PRESENTROOM ( PRESENT VIEW MODE ) ***\n");
        object->func = ExecPresentView;
        object->unk10 = 0;
    }

    return object;
}

void PresentStateKill(omObjData *object)
{
    PresentWindow **var_r31 = object->data;

    PresentCameraKill(presentCamera);
    PresentKill(present);
    PresentGuideKill(presentGuide);
    PresentWinKill(*var_r31);
    HuMemDirectFree(var_r31);
}

static void ExecPresentView(omObjData *object)
{
    StateWork *work = object->data;

    switch (object->unk10) {
        case 0:
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            object->unk10 = 1;
        case 1:
            if (WipeStatGet()) {
                return;
            }
            object->unk10 = 2;
        case 2:
            PresentExecModeSet(present, 1);
            object->unk10 = 3;
        case 3:
            if (PresentExecModeGet(present)) {
                return;
            }
            object->unk10 = 4;
        case 4:
            PresentGuideExecModeSet(presentGuide, PRESENT_GUIDE_MODE_ENTER);
            object->unk10 = 5;
        case 5:
            if (PresentGuideExecModeGet(presentGuide)) {
                return;
            }
            object->unk10 = 6;
        case 6:
            HuAudFXPlay(66);
            PresentWinAnimIn(work->window);
            PresentWinMesSet(work->window, MAKE_MESSID(0x32, 0x02));
            object->unk10 = 7;
        case 7:
            if (work->window->state) {
                return;
            }
            PresentWinChoiceSet(work->window, 1);
            object->unk10 = 8;
        case 8:
            if (work->window->state) {
                return;
            }
            PresentWinAnimOut(work->window);
            if (!work->window->choice) {
                work->quitTimer = 0;
                object->unk10 = 11;
                return;
            }
            else {
                object->unk10 = 9;
                return;
            }
        case 9:
            PresentGuideExecModeSet(presentGuide, PRESENT_GUIDE_MODE_LEAVE);
            object->unk10 = 10;
            return;
        case 10:
            if (PresentGuideExecModeGet(presentGuide)) {
                return;
            }
            object->unk10 = 2;
            return;
        case 11:
            object->unk10 = 12;
            work->quitTimer = 0;
        case 12:
            if (work->window->state) {
                return;
            }
            if (work->quitTimer++ >= 60) {
                omSysExitReq = 1;
                object->func = NULL;
                object->unk10 = 0;
            }
        default:
            break;
    }
}

static void ExecPresentGet(omObjData *object)
{
    void *sp8 = object->data;

    switch (object->unk10) {
        case 0:
            PresentSelectedIDSet(present, omovlevtno - 1);
            object->unk10 = 1;
        case 1:
            PresentExecModeSet(present, PRESENT_MODE_GET);
            object->unk10 = 2;
        case 2:
            if (PresentExecModeGet(present) == PRESENT_MODE_NONE) {
                object->unk10 = 3;
            }
            else {
                break;
            }
        case 3:
            object->unk10 = 4;
        case 4:
            omSysExitReq = 1;
            object->func = NULL;
            object->unk10 = 0;
            break;
        default:
            break;
    }
}

PresentWindow *PresentWinCreate(s32 id)
{
    PresentWindow *var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(PresentWindow), MEMORY_DEFAULT_NUM);

    var_r31->messToBeSet = 0;
    var_r31->messWaitSignal = 0;
    var_r31->choiceSignal = 0;
    var_r31->state = 0;
    var_r31->process = HuPrcChildCreate(ExecWindow, 1000, 8192, 0, presentObjMan);
    var_r31->process->user_data = var_r31;
    var_r31->id = id;
    switch (id) {
        case 0:
            var_r31->window = HuWinExCreateStyled(-10000.0f, 360.0f, 480, 80, -1, 1);
            HuWinBGTPLvlSet(var_r31->window, 0.8f);
            HuWinMesSpeedSet(var_r31->window, 0);
            HuWinMesPalSet(var_r31->window, 7, 0, 0, 0);
            break;
        case 1:
            var_r31->window = HuWinExCreateStyled(-10000.0f, 326.0f, 500, 40, -1, 0);
            HuWinAttrSet(var_r31->window, 2048);
            HuWinBGTPLvlSet(var_r31->window, 0.0f);
            HuWinMesSpeedSet(var_r31->window, 0);
            break;
    }
    HuWinDrawNoSet(var_r31->window, 63);
    PresentWinDispOff(var_r31);
    HuSprExecLayerSet(63, 2);
    return var_r31;
}

void PresentWinKill(PresentWindow *work)
{
    HuWinExCleanup(work->window);
    HuPrcKill(work->process);
    HuMemDirectFree(work);
}

void PresentWinAnimIn(PresentWindow *work)
{
    if (!work->visible) {
        work->state = 1;
    }
}

void PresentWinAnimOut(PresentWindow *work)
{
    if (work->visible) {
        work->state = 2;
    }
}

void PresentWinMesSet(PresentWindow *work, u32 mess)
{
    if (!work->state) {
        HuWinMesSet(work->window, mess);
        return;
    }
    work->messToBeSet = mess;
}

void PresentWinInsertMesSet(PresentWindow *work, u32 mess, s16 index)
{
    HuWinInsertMesSet(work->window, mess, index);
}

void PresentWinPosSet(PresentWindow *work, float x, float y)
{
    HuWinPosSet(work->window, x, y);
}

void PresentWinDispOn(PresentWindow *work)
{
    work->visible = TRUE;
}

void PresentWinDispOff(PresentWindow *work)
{
    work->visible = FALSE;
}

void PresentWinMesWait(PresentWindow *work)
{
    if (!work->state) {
        work->state = 3;
    }
    work->messWaitSignal = 1;
}

void PresentWinChoiceSet(PresentWindow *work, s32 choice)
{
    if (!work->state) {
        work->state = 4;
    }
    work->choiceSignal = 1;
    work->choice = choice;
}

static void ExecWindow(void)
{
    PresentWindow *work = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        switch (work->state) {
            case 1:
                work->visible = 1;
                HuWinExAnimIn(work->window);
                break;
            case 2:
                HuWinExAnimOut(work->window);
                work->visible = 0;
                break;
            case 3:
                winData[work->window].active_pad = 1;
                HuWinMesWait(work->window);
                work->messWaitSignal = 0;
                break;
            case 4:
                work->choice = HuWinChoiceGet(work->window, work->choice);
                work->choiceSignal = 0;
                break;
        }
        if (work->messToBeSet != 0) {
            HuWinMesSet(work->window, work->messToBeSet);
            work->messToBeSet = 0;
        }
        work->state = 0;
        if (work->messWaitSignal != 0) {
            work->state = 3;
        }
        if (work->choiceSignal != 0) {
            work->state = 4;
        }
        HuPrcVSleep();
    }
}
