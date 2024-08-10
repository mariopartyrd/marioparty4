#include "include/REL/w10Dll.h"
#include "game/data.h"
#include "game/hsfman.h"
#include "game/board/lottery.h"
#include "game/board/model.h"
#include "game/board/shop.h"
#include "game/board/space.h"
#include "game/board/star.h"
#include "game/board/tutorial.h"
#include "game/board/main.h"
#include "game/board/boo_house.h"
#include "game/board/map_object.h"

#include "math.h"

//Map Objects
static BoardMapObject mapObjTbl[MAPOBJ_MAX] = {
    3300.0f, 100.0f, -900.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    DATA_MAKE_NUM(DATADIR_W10, 3)
};

s16 boardMapObjMdl[MAPOBJ_MAX];

s16 tutorialExitWin;
s16 tutorialDoneF;
static s32 *motTbl;
s32 lbl_1_bss_4;
W10BoardWork *boardWork;

static s16 bgMdl = -1;
static s16 fgMdl = -1;
s16 boardStarHostMdl = -1;
s16 boardShopHostMdl = -1;
s16 boardLotteryHostMdl = -1;
s16 boardBooHouseHostMdl = -1;

static s32 charMotDirTbl[] = {
	DATADIR_MARIOMOT, DATADIR_LUIGIMOT,
	DATADIR_PEACHMOT, DATADIR_YOSHIMOT,
	DATADIR_WARIOMOT, DATADIR_DONKEYMOT,
	DATADIR_DAISYMOT, DATADIR_WALUIGIMOT,
};

static s32 starHostMot[2] = {
    DATA_MAKE_NUM(DATADIR_W10, 18),
    DATA_NUM_LISTEND
};

static s32 shopHostMot[2] = {
    DATA_MAKE_NUM(DATADIR_BGUEST, 9),
    DATA_NUM_LISTEND
};

static s32 lotteryHostMot[2] = {
    DATA_MAKE_NUM(DATADIR_BGUEST, 24),
    DATA_NUM_LISTEND
};

static s32 booHouseHostMot[2] = {
    DATA_MAKE_NUM(DATADIR_BGUEST, 14),
    DATA_NUM_LISTEND
};

static void LightSetHook(void);
static void LightResetHook(void);
static s32 WalkEvent(void);
static s32 WalkMiniEvent(void);
static s32 LandEvent(void);


void BoardCreate(void)
{
    float size[2];
    
    s32 i;
    BoardMapObject *temp_r30;
    s32 space;
    s32 board;

    board = GWBoardGet();
    boardWork = (W10BoardWork *)&GWSystem.board_data[0];
    boardWork->scene = 0;
    boardWork->dice = 0;
    boardWork->msg = 0;
    BoardTutorialHookSet(TutorialHookExec);
    HostCreate();
    TutorialSprCreate();
    tutorialDoneF = 0;
    BoardSpaceInit(DATA_MAKE_NUM(DATADIR_W10, 0));
    space = BoardSpaceFlagSearch(0, 1);
    BoardTutorialBlockSetPos(space, 1);
    bgMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W10, 1), NULL, 0);
    fn_8006DDE8(bgMdl, -1.0f);
    BoardModelPosSet(bgMdl, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(bgMdl, 0, 0x40000001);
    BoardModelMotionSpeedSet(bgMdl, 1.0f);
    fgMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W10, 2), NULL, 0);
    fn_8006DDE8(fgMdl, -1.0f);
    BoardModelPosSet(fgMdl, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(fgMdl, 0, 0x40000001);
    boardStarHostMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W10, 17), starHostMot, 0);
    BoardModelPosSet(boardStarHostMdl, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(boardStarHostMdl, 1, 0x40000001);
    boardShopHostMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 5), shopHostMot, 0);
    BoardModelMotionStart(boardShopHostMdl, 1, 0x40000001);
    boardBooHouseHostMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 18), lotteryHostMot, 0);
    BoardModelMotionStart(boardBooHouseHostMdl, 1, 0x40000001);
    boardLotteryHostMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 13), booHouseHostMot, 0);
    BoardModelMotionStart(boardLotteryHostMdl, 1, 0x40000001);
    BoardLightHookSet(LightSetHook, LightResetHook);
    for (i = 0; i < MAPOBJ_MAX; i++) {
        temp_r30 = &mapObjTbl[i];
        if (temp_r30->data_num != -1) {
            motTbl = NULL;
            boardMapObjMdl[i] = BoardModelCreate(temp_r30->data_num, motTbl, 0);
            BoardModelPosSetV(boardMapObjMdl[i], &temp_r30->pos);
            BoardModelRotSetV(boardMapObjMdl[i], &temp_r30->rot);
            BoardModelScaleSetV(boardMapObjMdl[i], &temp_r30->scale);
            BoardModelVisibilitySet(boardMapObjMdl[i], 1);
            if (motTbl != NULL) {
                BoardModelMotionStart(boardMapObjMdl[i], 0, 0x40000001);
            }
        }
    }
    BoardModelVisibilitySet(boardMapObjMdl[MAPOBJ_MELON], 0);
    boardWork->focus_mdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 0);
    BoardModelVisibilitySet(boardWork->focus_mdl, 0);
    BoardSpaceWalkEventFuncSet(WalkEvent);
    BoardSpaceWalkMiniEventFuncSet(WalkMiniEvent);
    BoardSpaceLandEventFuncSet(LandEvent);
    BoardStarHostSet(boardStarHostMdl);
    BoardBooHouseHostSet(boardBooHouseHostMdl);
    BoardShopHostSet(boardShopHostMdl);
    BoardLotteryHostSet(boardLotteryHostMdl);
    HuWinMesMaxSizeGet(1, size, 0x2E003A);
    tutorialExitWin = HuWinCreate(-10000.0f, 390.0f, size[0], size[1], 1);
    HuWinMesSet(tutorialExitWin, 0x2E003A);
    HuWinMesSpeedSet(tutorialExitWin, 0);
    HuWinPriSet(tutorialExitWin, 1);
    HuWinMesPalSet(tutorialExitWin, 7, 0, 0, 0);
}

void BoardDestroy(void)
{
    s32 i;
    for (i = 0; i < 1; i++) {
        if (boardMapObjMdl[i] != 0) {
            BoardModelKill(boardMapObjMdl[i]);
            boardMapObjMdl[i] = 0;
        }   
    }
    if (boardBooHouseHostMdl != -1) {
        BoardModelKill(boardBooHouseHostMdl);
        boardBooHouseHostMdl = -1;
    }
    if (boardShopHostMdl != -1) {
        BoardModelKill(boardShopHostMdl);
        boardShopHostMdl = -1;
    }
    if (boardLotteryHostMdl != -1) {
        BoardModelKill(boardLotteryHostMdl);
        boardLotteryHostMdl = -1;
    }
    if (boardStarHostMdl != -1) {
        BoardModelKill(boardStarHostMdl);
        boardStarHostMdl = -1;
    }
    if (bgMdl != -1) {
        BoardModelKill(bgMdl);
        bgMdl = -1;
    }
    if (fgMdl != -1) {
        BoardModelKill(fgMdl);
        fgMdl = -1;
    }
    BoardModelKill(boardWork->focus_mdl);
    TutorialSprKill();
    HuWinKill(tutorialExitWin);
    BoardSpaceDestroy();
}

static void LightSetHook(void)
{
    s16 id = BoardModelIDGet(bgMdl);
    Hu3DModelLightInfoSet(id, 1);
}

static void LightResetHook(void)
{
	
}

static s32 LandEvent(void)
{
	
}

static s32 WalkEvent(void)
{
    return 0;
}

void fn_1_914(void)
{
	
}

void fn_1_918(void)
{
	
}

static s32 WalkMiniEvent(void)
{
	
}

s32 fn_1_920(s16 arg0, f32 arg8, f32 arg9) {
    s32 var_r31;
    f32 var_f29;
    f32 var_f31;

    var_r31 = 0;
    var_f31 = BoardModelRotYGet(arg0);
    arg8 = fmod(arg8, 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (arg8 < 0.0f) {
        arg8 += 360.0f;
    }
    if (var_f31 != arg8) {
        var_f29 = arg8 - var_f31;
        if (var_f29 < 0.0f) {
            var_f29 += 360.0f;
        }
        if (var_f29 < 180.0f) {
            if (var_f29 > arg9) {
                var_f31 = var_f31 + arg9;
            } else {
                var_f31 = arg8;
            }
        } else if ((360.0f - var_f29) > arg9) {
            var_f31 = var_f31 - arg9;
        } else {
            var_f31 = arg8;
        }
        if (var_f31 < 0.0f) {
            var_f31 += 360.0f;
        }
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        BoardModelRotYSet(arg0, var_f31);
    } else {
        var_r31 = 1;
    }
    return var_r31;
}
