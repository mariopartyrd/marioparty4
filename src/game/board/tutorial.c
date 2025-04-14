#include "game/board/tutorial.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/flag.h"
#include "game/gamework_data.h"
#include "game/process.h"

#include <game/board/space.h>

SHARED_SYM s32 boardTutorialData[4]; // maybe a single s32 + padding?
static void (*tutorialHook)(s16, s32);
s8 boardTutorialDirInputX;
s8 boardTutorialDirInputY;
s16 boardTutorialDirInputTime;
s32 boardTutorialBlockPos;
s8 boardTutorialBlockItem;
s8 boardTutorialBlockF;
s8 boardTutorialUseItem;
static s16 hostMdl;
SHARED_SYM s8 boardTutorialF;
static Process *tutorialProcess;
static void *playerCfgCopy;
static void *playerCopy;
static void *systemCopy;
static void *gameStatCopy;

static void TutorialProcFunc(void) {
    while (1) {
        if (_CheckFlag(FLAG_ID_MAKE(1, 16))) {
            BoardTutorialHookExec(0x1E, 0);
        }
        HuPrcVSleep();
    }
}

void BoardTutorialInit(void) {
    boardTutorialDirInputTime = -1;
    boardTutorialBlockF = 0;
    boardTutorialUseItem = -1;
    tutorialHook = NULL;
    tutorialProcess = NULL;
    boardTutorialF = 0;
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        tutorialProcess = HuPrcChildCreate(TutorialProcFunc, 0x2002, 0x2000, 0, boardMainProc);
    }
}

void BoardTutorialKill(void) {
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        if (tutorialProcess) {
            HuPrcKill(tutorialProcess);
        }
        boardTutorialF = 0;
    }
}

void BoardTutorialHookSet(void *arg0) {
    tutorialHook = arg0;
}

void BoardTutorialHookExec(s16 arg0, s32 arg1) {
    if (tutorialHook) {
        tutorialHook(arg0, arg1);
    }
}

void BoardTutorialPlayerInit(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        GWPlayer[i].com = 1;
        GWPlayerCfg[i].iscom = 1;
    }
    GWSystem.board = BOARD_ID_TUTORIAL;
}

void BoardTutorialWorkSave(void) {
    OSReport("-O-O-O-O-O-O-O  Tutorial Save Work\n");
    if (gameStatCopy) {
        HuMemDirectFree(gameStatCopy);
    }
    if (systemCopy) {
        HuMemDirectFree(systemCopy);
    }
    if (playerCopy) {
        HuMemDirectFree(playerCopy);
    }
    if (playerCfgCopy) {
        HuMemDirectFree(playerCfgCopy);
    }
    gameStatCopy = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(GWGameStat));
    systemCopy = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(GWSystem));
    playerCopy = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(GWPlayer));
    playerCfgCopy = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(GWPlayerCfg));
    memcpy(gameStatCopy, &GWGameStat, sizeof(GWGameStat));
    memcpy(systemCopy, &GWSystem, sizeof(GWSystem));
    memcpy(playerCopy, GWPlayer, sizeof(GWPlayer));
    memcpy(playerCfgCopy, GWPlayerCfg, sizeof(GWPlayerCfg));
}

void BoardTutorialWorkRestore(void) {
    OSReport("-O-O-O-O-O-O-O  Tutorial Load Work\n");
    memcpy(&GWGameStat, gameStatCopy, sizeof(GWGameStat));
    memcpy(&GWSystem, systemCopy, sizeof(GWSystem));
    memcpy(GWPlayer, playerCopy, sizeof(GWPlayer));
    memcpy(GWPlayerCfg, playerCfgCopy, sizeof(GWPlayerCfg));
    HuMemDirectFree(gameStatCopy);
    HuMemDirectFree(systemCopy);
    HuMemDirectFree(playerCopy);
    HuMemDirectFree(playerCfgCopy);
    gameStatCopy = NULL;
    systemCopy = NULL;
    playerCopy = NULL;
    playerCfgCopy = NULL;
}

void BoardTutorialDirInputSet(s8 arg0, s8 arg1, s16 arg2) {
    boardTutorialDirInputX = arg0;
    boardTutorialDirInputY = arg1;
    boardTutorialDirInputTime = arg2;
}

void BoardTutorialBlockSetPos(s32 arg0, s8 arg1) {
    boardTutorialBlockF = 1;
    boardTutorialBlockPos = arg0;
    boardTutorialBlockItem = arg1;
    BoardSpaceBlockPosSet();
}

void BoardTutorialItemSet(s8 arg0) {
    boardTutorialUseItem = arg0;
}

void BoardTutorialHostSet(s16 arg0) {
    hostMdl = arg0;
}

void BoardTutorialHostHide(s8 arg0) {
    BoardModelVisibilitySet(hostMdl, arg0);
}
