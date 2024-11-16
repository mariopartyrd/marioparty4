#include "game/window.h"
#include "REL/option.h"
#include "game/esprite.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/sprite.h"

#include "version.h"

static void ExecWindow(void);

OptionWindow *OptionWinCreate(s32 id)
{
    OptionWindow *work;

    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(OptionWindow), MEMORY_DEFAULT_NUM);
    work->messToBeSet = 0;
    work->messWaitSignal = 0;
    work->choiceSignal = 0;
    work->state = 0;
    work->process = HuPrcChildCreate(ExecWindow, 0x2000, 0x2000, 0, optionObjMan);
    work->process->user_data = work;
    work->id = id;
    switch (work->id) {
        case 0:
            work->window = HuWinExCreateStyled(-10000.0f, 360.0f, 480, 80, -1, 1);
            HuWinBGTPLvlSet(work->window, 0.8f);
            HuWinMesSpeedSet(work->window, 0);
            HuWinMesPalSet(work->window, 7, 0, 0, 0);
            break;
        case 1:
            work->window = HuWinExCreateStyled(-10000.0f, 326.0f, 480, 40, -1, 0);
            HuWinAttrSet(work->window, 0x800);
            HuWinBGTPLvlSet(work->window, 0.0f);
            HuWinMesSpeedSet(work->window, 0);
            break;
        case 2:
            work->window = HuWinExCreateStyled(-10000.0f, 88.0f, VERSION_NTSC ? 224 : 320, 34, -1, 0);
            HuWinAttrSet(work->window, 0x800);
            HuWinBGTPLvlSet(work->window, 0.0f);
            HuWinMesSpeedSet(work->window, 0);
            break;
        case 3:
            work->window = HuWinExCreateStyled(175.0f, 100.0f, VERSION_NTSC ? 300 : 320, 34, -1, 0);
            HuWinBGTPLvlSet(work->window, 0.0f);
            HuWinMesSpeedSet(work->window, 0);
            break;
    }
    HuWinDrawNoSet(work->window, 0x3F);
    OptionWinDispOff(work);
    HuSprExecLayerSet(0x3F, 2);
    return work;
}

void OptionWinKill(OptionWindow *work)
{
    HuWinExCleanup(work->window);
    HuPrcKill(work->process);
    HuMemDirectFree(work);
}

void OptionWinAnimIn(OptionWindow *work)
{
    if (!work->visible) {
        work->state = 1;
    }
}

void OptionWinAnimOut(OptionWindow *work)
{
    if (work->visible) {
        work->state = 2;
    }
}

void OptionWinMesSet(OptionWindow *work, s32 mess)
{
    if (work->state == 0) {
        HuWinMesSet(work->window, mess);
    }
    else {
        work->messToBeSet = mess;
    }
}

void OptionWinInsertMesSet(OptionWindow *work, s32 mess, s16 index)
{
    HuWinInsertMesSet(work->window, mess, index);
}

void OptionWinPosSet(OptionWindow *work, float x, float y)
{
    HuWinPosSet(work->window, x, y);
}

void OptionWinDispOn(OptionWindow *work)
{
    HuWinDispOn(work->window);
    work->visible = TRUE;
}

void OptionWinDispOff(OptionWindow *work)
{
    HuWinDispOff(work->window);
    work->visible = FALSE;
}

void OptionWinMesWait(OptionWindow *work)
{
    if (work->state == 0) {
        work->state = 3;
    }
    work->messWaitSignal = TRUE;
}

void OptionWinChoiceSet(OptionWindow *work, s32 choice)
{
    if (work->state == 0) {
        work->state = 4;
    }
    work->choiceSignal = TRUE;
    work->choice = choice;
}

static void ExecWindow(void)
{
    OptionWindow *work = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        switch (work->state) {
            case 1:
                OptionWinDispOn(work);
                HuWinExAnimIn(work->window);
                break;
            case 2:
                HuWinExAnimOut(work->window);
                OptionWinDispOff(work);
                break;
            case 3:
                HuWinMesWait(work->window);
                work->messWaitSignal = FALSE;
                break;
            case 4:
                work->choice = HuWinChoiceGet(work->window, work->choice);
                work->choiceSignal = FALSE;
                break;
        }
        if (work->messToBeSet != 0) {
            HuWinMesSet(work->window, work->messToBeSet);
            work->messToBeSet = 0;
        }
        work->state = 0;
        if (work->messWaitSignal) {
            work->state = 3;
        }
        if (work->choiceSignal) {
            work->state = 4;
        }
        HuPrcVSleep();
    }
}
