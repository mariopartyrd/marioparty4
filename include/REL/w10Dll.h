#ifndef REL_W10_H
#define REL_W10_H

#include "game/gamework_data.h"
#include "dolphin.h"
#include "REL/executor.h"
#include "game/process.h"
#include "game/window.h"

enum {
    MAPOBJ_MELON = 0,
    MAPOBJ_MAX
};

typedef struct w10_board_work {
/* 0x00 */ s32 scene;
/* 0x04 */ u16 dice;
/* 0x06 */ u16 msg;
/* 0x08 */ s16 focus_mdl;
} W10BoardWork;

typedef void (*TutorialSceneFunc)(void);

typedef struct tutorial_scene {
    s16 cue;
    TutorialSceneFunc func;
} TutorialScene;

extern s32 boardTutorialData[4];

void HostPosSet(s16);
void fn_1_1FB0(void);
void fn_1_1E3C(s16, s16, s16);
void HostWinExec(s32);
void fn_1_6D8(void);
void fn_1_E0(void);
void TutorialSprCreate(void);
void TutorialSprKill(void);
void HostCreate(void);
int TutorialHookExec(s16, s32);

void TutorialStartExec(void);
void TutorialPreRollExec(void);
void TutorialOrderExec(void);
void TutorialP1StartExec(void);
void TutorialP2StartExec(void);
void TutorialP3StartExec(void);
void TutorialP4StartExec(void);
void TutorialGameStartExec(void);
void TutorialRollExec(void);
void TutorialMoveExec(void);
void TutorialLandExec(void);
void TutorialLandBlueExec(void);
void TutorialLandRedExec(void);
void TutorialLandHappenExec(void);
void TutorialLandFortuneExec(void);
void TutorialLandBowserExec(void);
void TutorialLandMushroomExec(void);
void TutorialMushroomMegaExec(void);
void TutorialMushroomMiniExec(void);
void TutorialLandBattleExec(void);
void TutorialLandWarpExec(void);
void TutorialWarpDecideExec(void);
void TutorialBlockStarExec(void);
void TutorialBlockCoinExec(void);
void TutorialMiniMegaExec(void);
void TutorialMiniUseExec(void);
void TutorialMiniStopExec(void);
void TutorialMegaUseExec(void);
void TutorialMegaDiceExec(void);
void TutorialMegaStompExec(void);
void TutorialMegaEventExec(void);
void TutorialMegaStopExec(void);
void TutorialEndExec(void);
void TutorialMGStatusExec(void);
void TutorialMG4PExec(void);
void TutorialMG2Vs2Exec(void);
void TutorialMG1Vs3Exec(void);
void TutorialMG1Vs3AltExec(void);
void TutorialShopExec(void);
void TutorialLotteryExec(void);
void TutorialBooHouseExec(void);

extern W10BoardWork *boardWork;
extern s16 boardMapObjMdl[MAPOBJ_MAX];
extern s16 tutorialDoneF;
extern s16 tutorialExitWin;

extern s16 boardStarHostMdl;
extern s16 boardShopHostMdl;
extern s16 boardLotteryHostMdl;
extern s16 boardBooHouseHostMdl;

#endif
