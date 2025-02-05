#include "game/board/main.h"
#include "REL/board_executor.h"
#include "REL/w01Dll.h"
#include "game/audio.h"
#include "game/board/audio.h"
#include "game/board/boo_house.h"
#include "game/board/com.h"
#include "game/board/lottery.h"
#include "game/board/map_object.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/shop.h"
#include "game/board/space.h"
#include "game/board/star.h"
#include "game/board/ui.h"
#include "game/board/view.h"
#include "game/board/window.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    struct {
        u8 killF : 1;
    };
} CoasterCameraWork;

typedef struct {
    struct {
        u8 killF : 1;
        u8 mode : 3;
        u8 stopF : 1;
        u8 decaF : 1;
    };
    u8 time;
    u8 delay;
    s16 dishMdlId;
    float dishSpeed;
} CupObjWork;

typedef struct {
    s8 mode;
    s8 playerNo;
    s16 delay;
    s16 pathMdlId;
    s16 endSpace;
    float speed;
    float unk0C;
    float time;
    Vec pos;
    Mtx matrix;
} CoasterPlayerWork; // Size 0x50

typedef struct {
    struct {
        u8 killF : 1;
    };
    s8 playerNum;
    CoasterPlayerWork *player;
} CoasterPlayerManWork;

typedef struct {
    /* 0x00 */ s16 time;
    /* 0x02 */ s16 mdlId;
    /* 0x04 */ float scale;
    /* 0x08 */ Vec pos;
    /* 0x14 */ Vec vel;
} CoasterEffData; // Size 0x20

typedef struct {
    struct {
        u8 killF : 1;
    };
    u8 delay;
    CoasterEffData *data;
} CoasterEffWork;

static void LightSetHook(void);
static void LightResetHook(void);
static s32 LandEvent(void);
static s32 WalkEvent(void);
static void MapObjDispSet(void);
static void fn_1_D00(void);
static void RoundItemMain(void);
static void RoundItemDestroy(void);
static void RoundItemEvent(void);
static void SpaceAmidaEvent(void);
static s32 WalkMiniEvent(void);
static void UpdateHostDisp(void);
static void CoasterInit(void);
static void CoasterPathUpdate(void);
static void CoasterPosCalc(BoardCameraData *camera);
static void CoasterCameraUpdate(void);
static void CoasterCameraObjKill(void);
static void CoasterCameraObjMain(omObjData *obj);
static void CoasterCameraObjUpdate(void);
static float CoasterStickRotGet(void);
static void CoasterRotUpdate(void);
static void CoasterCoinCheck(void);
static void CoasterPathMotUpdate(void);
static void CoasterMotCreate(s32 playerNo);
static void CoasterMotKill(s32 playerNo);
static void CoasterExec(void);
static void CoasterExit(void);
static void CoasterWinCreate(void);
static void CoasterWinKill(void);
static s32 CoasterHostExec(void);
static void CoasterMain(void);
static void CoasterDestroy(void);
static void CoasterEvent(void);
static void CoasterCoinCreate(void);
static void CoasterCoinKill(void);
static void CupInit(void);
static void CupMotOnSet(s32 stopF);
static void CupEvent(s32 side, s32 spaceStart);
static void CupMain(void);
static void CupDestroy(void);
static void CupExec(void);
static BOOL CupObjCheck(void);
static void CupObjCreate(void);
static void CupObjMain(omObjData *obj);
static void CupObjInit(CupObjWork *work, omObjData *obj);
static void CupObjJumpWait(CupObjWork *work, omObjData *obj);
static void CupObjHookReset(CupObjWork *work, omObjData *obj);
static void CupObjStop(CupObjWork *work, omObjData *obj);
static void CupObjRotate(CupObjWork *work, omObjData *obj);
static void CupLandEvent(s32 playerNo, s32 spaceId);
static void CoasterLandEvent(s32 playerNo, s32 spaceId);
static void CoasterLandMain(void);
static void CoasterLandExec(void);
static void CoasterPlayerManCreate(void);
static void CoasterPlayerManKill(void);
static void CoasterPlayerManUpdate(omObjData *obj);
static void CoasterPlayerWait(CoasterPlayerWork *work, omObjData *obj);
static void CoasterPlayerChaseBegin(CoasterPlayerWork *work, omObjData *obj);
static void CoasterPlayerChasePathSet(CoasterPlayerWork *work, omObjData *obj);
static void CoasterPlayerChase(CoasterPlayerWork *work, omObjData *obj);
static void CoasterPlayerStop(CoasterPlayerWork *work, omObjData *obj);
static void CoasterPlayerEnd(CoasterPlayerWork *work, omObjData *obj);
static void CoasterPlayerEndSet(CoasterPlayerWork *work);
static s32 CoasterPlayerLoopCheck(CoasterPlayerWork *work);
static void CoasterPlayerTimeInit(CoasterPlayerWork *work);
static void CoasterEffCreate(void);
static void CoasterEffKill(void);
static void CoasterEffUpdate(omObjData *obj);
static void CoasterEffAdd(CoasterEffWork *work);
static void CoasterEffModelUpdate(CoasterEffWork *work);
extern void CoasterHostComKeySet(s32 playerNo);

static BoardMapObject mapObjData[MAPOBJ_MAX]
    = { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 8) },
          { { 0.0f, 700.0f, 300.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 9) },
          { { -2025.0f, 100.0f, 1950.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 0) },
          { { 1725.0f, 200.0f, -1650.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 0) },
          { { 2757.974f, 200.0f, -536.781f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 0) },
          { { -2750.0f, 300.0f, -2150.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 0) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 12) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 13) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 14) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 15) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 16) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 16) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 16) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 17) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 18) },
          { { -2550.0f, 300.0f, -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 18) },
          { { 3000.0f, 200.0f, -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 21) },
          { { 3000.0f, 200.0f, -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 22) },
          { { 3000.0f, 200.0f, -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 23) },
          { { 3000.0f, 200.0f, -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 24) },
          { { 3000.0f, 200.0f, -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 25) },
          { { 3000.0f, 200.0f, -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 26) },
          { { 3000.0f, 200.0f, -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 27) },
          { { 1200.0f, 0.0f, 1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 3) },
          { { 1200.0f, 0.0f, 1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4) },
          { { 1200.0f, 0.0f, 1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4) },
          { { 1200.0f, 0.0f, 1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4) },
          { { 1200.0f, 0.0f, 1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 5) },
          { { -1800.0f, 200.0f, -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 3) },
          { { -1800.0f, 200.0f, -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4) },
          { { -1800.0f, 200.0f, -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4) },
          { { -1800.0f, 200.0f, -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4) },
          { { -1800.0f, 200.0f, -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 5) } };

s16 mapObjMdlId[MAPOBJ_MAX];

static s32 *mapObjMotTbl;
static s16 roundItemTbl[5];
static s8 eventPlayer;
static s8 coasterLoopF;
static s8 coasterDoneF;
static s8 coasterLandF;
static s8 coasterType;
static s16 coasterPathMdlId;
static s16 coasterStartSpace;
static float lbl_1_bss_6A8;
static Mtx coasterMtx;
static float coasterAccel;
static float coasterSpeed;
static float coasterCamSpeed;
static Vec coasterRot;
static Vec coasterPos;
static Vec coasterPosOld;
static float coasterMaxTime;
static float coasterTime;
static float coasterBaseRotY;
static Vec coasterCameraPos;
static Vec coasterCameraUp;
static Vec coasterCameraTarget;
static s8 coasterCoinF[24];
static s16 coasterCoinMdlId[24];
static s16 coasterMotId[2];
static s8 lbl_1_bss_2C[1440];
static s8 lbl_1_bss_2A[2]; // padding
static s8 cupSide;
static s8 cupHookNo;
static s16 cupSpaceStart;
static s16 cupSpaceEnd;
static omObjData *coasterEffObj;
static s8 coasterPlayerChaseNum;
static omObjData *cupObj;
static Process *cupProc;
static omObjData *coasterCameraObj;
static omObjData *coasterPlayerManObj;
static Process *coasterProc;
static Process *roundItemProc;
W01BoardWork *boardWork;

static s16 bgMdl = -1;
static s16 fgMdl = -1;
static s16 starHostMdl = -1;
static s16 hostMdl = -1;
static s16 syuppouMdl = -1;

static s32 starHostMotTbl[] = { DATA_MAKE_NUM(DATADIR_W01, 30), -1 };

static s32 hostMotTbl[] = { DATA_MAKE_NUM(DATADIR_BGUEST, 1), -1 };

void BoardCreate(void)
{
    BoardMapObject *mapObj;
    s32 boardNo;
    s32 i;

    boardNo = GWBoardGet();
    boardWork = (W01BoardWork *)GWSystem.board_data;
    BoardSpaceInit(DATA_MAKE_NUM(DATADIR_W01, 0));
    bgMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 1), NULL, 0);
    fn_8006DDE8(bgMdl, -1.0f);
    BoardModelPosSet(bgMdl, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(bgMdl, 0, HU3D_MOTATTR_LOOP);
    fgMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 2), NULL, 0);
    fn_8006DDE8(fgMdl, -1.0f);
    BoardModelPosSet(fgMdl, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(fgMdl, 0, HU3D_MOTATTR_LOOP);
    starHostMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 29), starHostMotTbl, 0);
    BoardModelPosSet(starHostMdl, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(starHostMdl, 1, HU3D_MOTATTR_LOOP);
    hostMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 0), hostMotTbl, 0);
    BoardModelPosSet(hostMdl, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(hostMdl, 1, HU3D_MOTATTR_LOOP);
    syuppouMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 11), NULL, 0);
    BoardModelMotionStart(syuppouMdl, 0, HU3D_MOTATTR_LOOP);
    BoardLightHookSet(LightSetHook, LightResetHook);
    for (i = 0; i < MAPOBJ_MAX; i++) {
        mapObj = &mapObjData[i];
        if (mapObj->data_num != -1) {
            if (i == MAPOBJ_HOST1 || i == MAPOBJ_HOST2 || i == MAPOBJ_HOST3 || i == MAPOBJ_HOST4) {
                mapObjMotTbl = hostMotTbl;
            }
            else {
                mapObjMotTbl = NULL;
            }
            mapObjMdlId[i] = BoardModelCreate(mapObj->data_num, mapObjMotTbl, 0);
            BoardModelPosSetV(mapObjMdlId[i], &mapObj->pos);
            BoardModelRotSetV(mapObjMdlId[i], &mapObj->rot);
            BoardModelScaleSetV(mapObjMdlId[i], &mapObj->scale);
            BoardModelVisibilitySet(mapObjMdlId[i], 1);
        }
    }
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_HOST1], 1, HU3D_MOTATTR_LOOP);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_HOST2], 1, HU3D_MOTATTR_LOOP);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_HOST3], 1, HU3D_MOTATTR_LOOP);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_HOST4], 1, HU3D_MOTATTR_LOOP);
    CupInit();
    MapObjDispSet();
    CoasterInit();
    BoardSpaceWalkEventFuncSet(WalkEvent);
    BoardSpaceWalkMiniEventFuncSet(WalkMiniEvent);
    BoardSpaceLandEventFuncSet(LandEvent);
    BoardStarHostSet(starHostMdl);
    BoardBooHouseHostSet(hostMdl);
    BoardLotteryHostSet(hostMdl);
    BoardShopHostSet(hostMdl);
    BoardJunctionMaskSet(0xC000);
    BoardJunctionMaskSet(0x3000);
}

void BoardDestroy(void)
{
    s32 i;

    CoasterWinKill();
    fn_1_D00();
    for (i = 0; i < MAPOBJ_MAX; i++) {
        if (mapObjMdlId[i] != 0) {
            BoardModelKill(mapObjMdlId[i]);
            mapObjMdlId[i] = 0;
        }
    }
    if (syuppouMdl != -1) {
        BoardModelKill(syuppouMdl);
        syuppouMdl = -1;
    }
    if (hostMdl != -1) {
        BoardModelKill(hostMdl);
        hostMdl = -1;
    }
    if (starHostMdl != -1) {
        BoardModelKill(starHostMdl);
        starHostMdl = -1;
    }
    if (bgMdl != -1) {
        BoardModelKill(bgMdl);
        bgMdl = -1;
    }
    if (fgMdl != -1) {
        BoardModelKill(fgMdl);
        fgMdl = -1;
    }
    BoardSpaceDestroy();
}

static void LightSetHook(void)
{
    s16 modelId;

    modelId = BoardModelIDGet(bgMdl);
    Hu3DModelLightInfoSet(modelId, 1);
}

static void LightResetHook(void) { }

static s32 LandEvent(void)
{
    s32 playerNo;
    s32 spaceId;
    u32 flag;

    playerNo = GWSystem.player_curr;
    spaceId = GWPlayer[playerNo].space_curr;
    flag = BoardSpaceFlagGet(0, spaceId);
    if (flag & 0x800) {
        CoasterLandEvent(playerNo, spaceId);
    }
    else if (flag & 0x400) {
        CupLandEvent(playerNo, spaceId);
    }
}

static s32 WalkEvent(void)
{
    s32 playerNo;
    s32 i;
    s32 type;
    s32 spaceLinkId;
    BoardSpace *space;
    BoardSpace *spaceLink;

    playerNo = GWSystem.player_curr;
    space = BoardSpaceGet(0, GWPlayer[playerNo].space_curr);
    if (space->flag & 0x3000) {
        if (BoardPlayerSizeGet(playerNo) == 2 || GWPlayer[playerNo].bowser_suit) {
            return 0;
        }
        if (space->flag & 0x2000) {
            if (boardWork->hostSide != 0) {
                return 0;
            }
        }
        else if (space->flag & 0x1000) {
            if (boardWork->hostSide != 1) {
                return 0;
            }
        }
        CoasterEvent();
        return 1;
    }
    type = -1;
    for (i = 0; i < space->link_cnt; i++) {
        if (space->link[i] != -1) {
            spaceLink = BoardSpaceGet(0, space->link[i]);
            if (spaceLink->flag & 0x8000) {
                type = 0;
                spaceLinkId = space->link[i];
                break;
            }
            else if (spaceLink->flag & 0x4000) {
                type = 1;
                spaceLinkId = space->link[i];
                break;
            }
        }
    }
    if (type != -1) {
        CupEvent(type, spaceLinkId);
        return 1;
    }
    return 0;
}

static void MapObjDispSet(void)
{
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA], 1);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA_MAP1], 0);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA_MAP2], 0);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA_MAP3], 0);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA_ROCKET1], 0);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA_ROCKET2], 0);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA_ROCKET3], 0);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA_LIGHTEFF], 0);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA_LAMP1], 1);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_SPACEAMIDA_LAMP2], 1);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_SPACEAMIDA], 0, 0);
    BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_SPACEAMIDA], 0.0f);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_SPACEAMIDA_LAMP1], 0, HU3D_MOTATTR_LOOP);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_SPACEAMIDA_LAMP2], 0, HU3D_MOTATTR_LOOP);
    BoardModelHookSet(mapObjMdlId[MAPOBJ_SPACEAMIDA], "amida_ban_07-sirenr", mapObjMdlId[MAPOBJ_SPACEAMIDA_LAMP1]);
    BoardModelHookSet(mapObjMdlId[MAPOBJ_SPACEAMIDA], "amida_ban_07-sirenl", mapObjMdlId[MAPOBJ_SPACEAMIDA_LAMP2]);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM], 1);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA], 1);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], 1);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM], 0);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_LIGHT], 0);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], 1);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_DENSYOKU], 1);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], 0, 0);
    BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], 0.0f);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], 0, 0);
    BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], 0.0f);
    BoardModelExistDupe(mapObjMdlId[MAPOBJ_ROUNDITEM], 0);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_ROUNDITEM], 0, HU3D_MOTATTR_LOOP);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA], 0, HU3D_MOTATTR_LOOP);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_DENSYOKU], 0, HU3D_MOTATTR_LOOP);
    BoardModelHookSet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], "m_goraund_01-flag1", mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_DENSYOKU]);
}

static void fn_1_D00(void) { }

static void RoundItemMain(void)
{
    Vec spacePos;
    s8 comItem[4];
    s32 spaceStart;
    s32 spaceEnd;
    s32 comPlayF;
    s32 choice;
    s32 playerNo;
    s32 i;
    s32 j;

    playerNo = GWSystem.player_curr;
    comPlayF = FALSE;
    if (BoardPlayerItemCount(playerNo) == 3) {
        BoardWinCreate(0, MAKE_MESSID(10, 9), 0);
        BoardWinWait();
        BoardWinKill();
        HuPrcEnd();
    }
    roundItemTbl[0] = 0;
    i = 1;
    while (i < 4) {
        roundItemTbl[i] = frandmod(14);
        if (roundItemTbl[i] != 10 && roundItemTbl[i] != 13) {
            for (j = 0; j < i; j++) {
                if (roundItemTbl[i] == roundItemTbl[j]) {
                    roundItemTbl[i] = -1;
                }
            }
            if (roundItemTbl[i] != -1) {
                i++;
            }
        }
    }
    RoundItemInit(roundItemTbl);
    for (i = 0; i < 4; i++) {
        comItem[i] = roundItemTbl[i];
    }
    if (BoardComPreferItemGet(playerNo, comItem, 4) != -1) {
        comPlayF = TRUE;
    }
    HuAudFXPlay(0x40D);
    HuAudFXPlay(0x40E);
    BoardModelAttrReset(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], HU3D_MOTATTR_REV);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], 0, 0);
    spaceStart = GWPlayer[playerNo].space_curr;
    spaceEnd = BoardSpaceLinkFlagSearch(0, spaceStart, 0x02000000);
    BoardSpacePosGet(0, spaceEnd, &spacePos);
    {
        Vec cameraOfs;
        Vec cameraRot;
        cameraOfs.x = 150.0f;
        cameraOfs.y = 0.0f;
        cameraOfs.z = 0.0f;
        cameraRot.x = -45.0f;
        cameraRot.y = 0.0f;
        cameraRot.z = 0.0f;
        BoardCameraMotionStartEx(mapObjMdlId[MAPOBJ_HOST3], &cameraRot, &cameraOfs, 1880.0f, -1.0f, 21);
    }
    BoardCameraMotionWait();
    BoardWinCreateChoice(2, MAKE_MESSID(10, 0), 0, 0);
    if (GWPlayer[playerNo].com) {
        if (comPlayF != 0) {
            BoardComKeySetLeft();
        }
        else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    choice = BoardWinChoiceGet();
    if (choice != 0) {
        BoardWinCreate(2, MAKE_MESSID(10, 4), 0);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        HuAudFXPlay(0x40F);
        BoardModelMotionStart(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], 0, HU3D_MOTATTR_REV);
        while (!BoardModelMotionEndCheck(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP])) {
            HuPrcVSleep();
        }
        BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], 0.0f);
        BoardModelAttrReset(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], HU3D_MOTATTR_REV);
        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        RoundItemKill();
        HuPrcEnd();
    }
    BoardPlayerMoveBetween(playerNo, spaceStart, spaceEnd);
    while (GWPlayer[playerNo].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(playerNo, 1, HU3D_MOTATTR_LOOP);
    {
        Vec cameraOfs;
        Vec cameraRot;
        cameraOfs.x = 0.0f;
        cameraOfs.y = 0.0f;
        cameraOfs.z = 0.0f;
        cameraRot.x = -45.0f;
        cameraRot.y = 0.0f;
        cameraRot.z = 0.0f;
        BoardCameraMotionStartEx(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], &cameraRot, &cameraOfs, 1200.0f, -1.0f, 21);
    }
    BoardCameraMotionWait();
    RoundItemEventStart();
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    BoardAudSeqPause(0, 0, 1000);
    while (GWPlayer[playerNo].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(playerNo, 1, HU3D_MOTATTR_LOOP);
    HuPrcEnd();
}

static void RoundItemDestroy(void)
{
    BoardWinKill();
    CharModelDataClose(-1);
    roundItemProc = NULL;
}

static void RoundItemEvent(void)
{
    roundItemProc = HuPrcChildCreate(RoundItemMain, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(roundItemProc, RoundItemDestroy);
    while (roundItemProc) {
        HuPrcVSleep();
    }
}

static void SpaceAmidaEvent(void)
{
    Vec spacePos;
    s32 playerNo;
    s32 choice;
    s32 spaceStart;
    s32 spaceEnd;

    playerNo = GWSystem.player_curr;
    BoardWinCreateChoice(2, MAKE_MESSID(11, 0), 0, 0);
    if (GWPlayer[playerNo].com) {
        BoardComKeySetLeft();
    }
    BoardWinWait();
    BoardWinKill();
    choice = BoardWinChoiceGet();
    if (choice != 0) {
        BoardWinCreate(2, MAKE_MESSID(11, 4), 0);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        return;
    }
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_SPACEAMIDA], 0, 0);
    {
        Vec cameraOfs;
        Vec cameraRot;
        cameraOfs.x = 0.0f;
        cameraOfs.y = 0.0f;
        cameraOfs.z = 0.0f;
        cameraRot.x = 0.0f;
        cameraRot.y = 170.0f;
        cameraRot.z = 0.0f;
        BoardCameraMotionStartEx(mapObjMdlId[MAPOBJ_SPACEAMIDA], &cameraOfs, &cameraRot, 1200.0f, 25.0f, 21);
    }
    
    spaceStart = GWPlayer[playerNo].space_curr;
    spaceEnd = BoardSpaceLinkFlagSearch(0, spaceStart, 0x02000000);
    BoardSpacePosGet(0, spaceEnd, &spacePos);
    BoardPlayerMoveBetween(playerNo, spaceStart, spaceEnd);
    BoardPlayerMotionStart(playerNo, 1, HU3D_MOTATTR_LOOP);
    BoardAudSeqPause(0, 1, 1000);
    SpaceAmidaExec();
    while (GWPlayer[playerNo].moving) {
        HuPrcVSleep();
    }
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 1000);
    while (GWPlayer[playerNo].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(playerNo, 1, HU3D_MOTATTR_LOOP);
}

static s32 WalkMiniEvent(void)
{
    s32 flag;
    s16 spaceId;

    spaceId = GWPlayer[GWSystem.player_curr].space_curr;
    flag = BoardSpaceFlagGet(0, spaceId) & 0x600000;
    BoardRollDispSet(0);
    if (flag == 0x200000) {
        SpaceAmidaEvent();
    }
    else if (flag == 0x400000) {
        RoundItemEvent();
    }
    BoardRollDispSet(1);
}

static void UpdateHostDisp(void)
{
    if (boardWork->hostSide == 0) {
        BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_HOST1], 1);
        BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_HOST2], 0);
    }
    else {
        BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_HOST1], 0);
        BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_HOST2], 1);
    }
}

static void CoasterInit(void)
{
    Vec pos;
    Mtx matrix;

    coasterLandF = 0;
    coasterPathMdlId = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 10), NULL, 0);
    coasterMaxTime = BoardModelMotionMaxTimeGet(coasterPathMdlId);
    BoardModelVisibilitySet(coasterPathMdlId, 0);
    memset(lbl_1_bss_2C, 0, sizeof(lbl_1_bss_2C));
    if (BoardSpaceRead(1, DATA_MAKE_NUM(DATADIR_W01, 6)) == 0) {
        if (boardWork->hostSide == 0) {
            BoardSpaceFlagPosGet(1, 0x2000, &pos);
            BoardModelMotionTimeSet(coasterPathMdlId, coasterMaxTime);
            coasterBaseRotY = -90.0f;
        }
        else {
            BoardSpaceFlagPosGet(1, 0x1000, &pos);
            BoardModelMotionTimeSet(coasterPathMdlId, 0.0f);
            coasterBaseRotY = 90.0f;
        }
        coasterPos = pos;
        BoardModelPosSetV(mapObjMdlId[MAPOBJ_COASTER], &pos);
        BoardModelRotSet(mapObjMdlId[MAPOBJ_COASTER], 0.0f, coasterBaseRotY, 0.0f);
        BoardModelExistDupe(mapObjMdlId[MAPOBJ_COASTER], 1);
        BoardModelExistDupe(mapObjMdlId[MAPOBJ_COASTER_RAIL], 1);
        fn_8006DDE8(mapObjMdlId[MAPOBJ_COASTER_RAIL], 500.0f);
        MTXIdentity(matrix);
        BoardModelMtxSet(mapObjMdlId[MAPOBJ_COASTER], &matrix);
        UpdateHostDisp();
    }
}

static void CoasterPathUpdate(void)
{
    Vec diff;
    float time;
    s32 spaceId;
    s32 spaceIdLink;
    s16 linkTbl[3];
    BoardSpace *space;
    BoardSpace *spaceLink;

    spaceId = coasterStartSpace;
    time = 0.0f;
    while (TRUE) {
        space = BoardSpaceGet(1, spaceId);
        if (boardWork->hostSide == 0) {
            spaceIdLink = space->link[0];
        }
        else {
            BoardSpaceLinkTargetListGet(1, spaceId, linkTbl);
            spaceIdLink = linkTbl[0];
        }
        if (spaceIdLink == 0) {
            break;
        }
        spaceLink = BoardSpaceGet(1, spaceIdLink);
        if (!spaceLink) {
            spaceLink = space;
            break;
        }
        VECSubtract(&spaceLink->pos, &space->pos, &diff);
        time += VECMag(&diff);
        if (time >= coasterTime) {
            break;
        }
        spaceId = spaceIdLink;
    }
    if (space->flag & 8) {
        coasterLoopF = 1;
    }
    else {
        coasterLoopF = 0;
    }
}

static void CoasterPosCalc(BoardCameraData *camera)
{
    camera->pos = coasterCameraPos;
    camera->up = coasterCameraUp;
    camera->target = coasterCameraTarget;
}

static void CoasterCameraUpdate(void)
{
    Vec modelPos;
    Vec diff;
    Vec target;
    Vec up;
    Vec pos;
    Mtx matrix;

    VECSubtract(&coasterPos, &coasterPosOld, &diff);
    if (coasterLoopF != 0) {
        BoardModelPosGet(mapObjMdlId[MAPOBJ_COASTER_RAIL], &modelPos);
        VECSubtract(&modelPos, &coasterPos, &up);
        VECNormalize(&up, &up);
        target = coasterPosOld;
        pos = coasterPos;
        BoardMTXCalcLookAt(matrix, &pos, &up, &target);
        MTXTranspose(matrix, coasterMtx);
        MTXRotRad(matrix, 'z', MTXDegToRad(coasterRot.z));
        MTXConcat(coasterMtx, matrix, coasterMtx);
    }
    else {
        if (diff.z != 0.0f || diff.x != 0.0f) {
            coasterRot.y = atan2d(diff.x, diff.z);
            coasterRot.x = -atan2d(diff.y, VECMagXZ(&diff));
        }
        else {
            coasterRot.x = coasterRot.y = 0.0f;
        }
        MTXRotRad(coasterMtx, 'z', MTXDegToRad(coasterRot.z));
        MTXRotRad(matrix, 'x', MTXDegToRad(coasterRot.x));
        MTXConcat(matrix, coasterMtx, coasterMtx);
        MTXRotRad(matrix, 'y', MTXDegToRad(coasterRot.y));
        MTXConcat(matrix, coasterMtx, coasterMtx);
    }
}

static void CoasterCameraObjKill(void)
{
    CoasterCameraWork *work;

    if (coasterCameraObj) {
        work = OM_GET_WORK_PTR(coasterCameraObj, CoasterCameraWork);
        work->killF = TRUE;
    }
}

static void CoasterCameraObjMain(omObjData *obj)
{
    CoasterCameraWork *work = OM_GET_WORK_PTR(obj, CoasterCameraWork);

    if (work->killF != 0 || BoardIsKill()) {
        omDelObjEx(HuPrcCurrentGet(), obj);
        coasterCameraObj = NULL;
        return;
    }
    CoasterCameraObjUpdate();
}

static void CoasterCameraObjUpdate(void)
{
    Vec modelPos;
    Vec pos;
    float angleY;
    float angleX;
    float radius;

    pos.x = coasterPosOld.x;
    pos.y = coasterPosOld.y + 200.0f;
    pos.z = coasterPosOld.z;
    VECSubtract(&pos, &coasterCameraTarget, &pos);
    VECScale(&pos, &pos, 0.08f);
    VECAdd(&pos, &coasterCameraTarget, &coasterCameraTarget);
    VECSubtract(&coasterPos, &coasterPosOld, &pos);
    if (pos.x != 0.0f || pos.z != 0.0f) {
        angleX = atan2f(pos.y, VECMagXZ(&pos));
        angleY = atan2f(-pos.x, -pos.z);
    }
    else {
        angleX = angleY = 0.0f;
        return;
    }
    angleX += -0.27925268f;
    if (coasterLoopF != 0) {
        if (coasterCamSpeed < 0.08f) {
            coasterCamSpeed -= 0.00033333333f;
        }
        BoardModelPosGet(mapObjMdlId[MAPOBJ_COASTER_RAIL], &modelPos);
        if (boardWork->hostSide == 0) {
            radius = -2500.0f;
        }
        else {
            radius = 2500.0f;
        }
        modelPos.x = modelPos.x + radius * sin(1.4137166738510132); // TODO: should be sind(81)
        modelPos.y = modelPos.y + -150.0f;
        modelPos.z = modelPos.z + radius * cos(1.4137166738510132); // TODO: should be cosd(81)
        VECSubtract(&modelPos, &coasterCameraPos, &pos);
        VECScale(&pos, &pos, coasterCamSpeed);
        VECAdd(&pos, &coasterCameraPos, &coasterCameraPos);
    }
    else {
        if (coasterCamSpeed < 0.08f) {
            coasterCamSpeed += 0.00066666666f;
        }
        pos.x = 400.0 * (sin(angleY) * cos(angleX));
        pos.y = 400.0 * -sin(angleX);
        pos.z = 400.0 * (cos(angleY) * cos(angleX));
        VECAdd(&coasterCameraTarget, &pos, &pos);
        VECSubtract(&pos, &coasterCameraPos, &pos);
        VECScale(&pos, &pos, coasterCamSpeed);
        VECAdd(&pos, &coasterCameraPos, &coasterCameraPos);
    }
}

static float CoasterStickRotGet(void)
{
    Vec basePos;
    Vec modelPos;
    Vec diff;
    float stickRot;
    s16 stkX;
    s32 padNo;
    s32 i;

    basePos = coasterPos;
    if (GWPlayer[eventPlayer].com) {
        if (coasterLoopF != 0) {
            return 0.0f;
        }
        for (i = 0; i < 24; i++) {
            if (coasterCoinF[i] == 0) {
                BoardModelPosGet(coasterCoinMdlId[i], &modelPos);
                VECSubtract(&modelPos, &basePos, &diff);
                if (!(VECMag(&diff) > 400.0f)) {
                    break;
                }
            }
        }
        if (i == 24) {
            return 0.0f;
        }
        VECSubtract(&modelPos, &basePos, &diff);
        stickRot = atan2d(diff.x, diff.z);
        if (stickRot > 0.0f) {
            stickRot = 45.0f;
        }
        else {
            stickRot = -45.0f;
        }
    }
    else {
        padNo = GWPlayer[eventPlayer].port;
        stkX = HuPadStkX[padNo];
        OSs16tof32(&stkX, &stickRot);
        stickRot = stickRot * 0.625f;
    }
    return stickRot;
}

static void CoasterRotUpdate(void)
{
    float motTime;
    float stickRot;
    Mtx sp70;

    CoasterCameraUpdate();
    if (coasterLandF != 0) {
        coasterRot.z = 0.0f;
        return;
    }
    stickRot = CoasterStickRotGet();
    BoardDAngleCalcRange(&coasterRot.z, stickRot, 5.0f);
    motTime = 6.0f + 6.0f * (coasterRot.z / 45.0f) - 1.0f;
    if (coasterRot.z > 22.5f) {
        BoardPlayerMotionStart(eventPlayer, coasterMotId[1], 0);
        BoardPlayerMotionTimeSet(eventPlayer, motTime);
    }
    else if (coasterRot.z < -22.5f) {
        BoardPlayerMotionStart(eventPlayer, coasterMotId[1], 0);
        BoardPlayerMotionTimeSet(eventPlayer, motTime);
    }
    else {
        BoardPlayerMotionShiftSet(eventPlayer, coasterMotId[0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    }
    CoasterCoinCheck();
}

static void CoasterCoinCheck(void)
{
    Vec coinPos;
    Vec ofs;
    Vec angle;
    Vec diff;
    Vec mdlCoasterPos;
    float rotZ;
    Mtx matrix;
    Mtx mtxRotX;
    Mtx mtxRotY;
    Mtx mtxRotZ;
    s32 i;

    if (coasterLoopF == 0) {
        rotZ = coasterRot.z;
        if (rotZ > 180.0f) {
            rotZ -= 360.0f;
        }
        BoardModelPosGet(mapObjMdlId[MAPOBJ_COASTER], &mdlCoasterPos);
        VECSubtract(&coasterPos, &coasterPosOld, &diff);
        if (diff.z != 0.0f || diff.x != 0.0f) {
            angle.y = atan2d(diff.x, diff.z);
            angle.x = -atan2d(diff.y, VECMagXZ(&diff));
        }
        else {
            angle.x = angle.y = 0.0f;
        }
        MTXTrans(matrix, 0.0f, 180.0f, 0.0f);
        MTXRotRad(mtxRotX, 'x', MTXDegToRad(angle.x));
        MTXRotRad(mtxRotY, 'y', MTXDegToRad(angle.y));
        MTXRotRad(mtxRotZ, 'z', MTXDegToRad(rotZ));
        MTXConcat(mtxRotX, mtxRotZ, mtxRotZ);
        MTXConcat(mtxRotY, mtxRotZ, mtxRotZ);
        MTXConcat(mtxRotZ, matrix, matrix);
        ofs.x = matrix[0][3];
        ofs.y = matrix[1][3];
        ofs.z = matrix[2][3];
        VECAdd(&ofs, &mdlCoasterPos, &ofs);
        if (rotZ < 27.000002f && rotZ > -27.000002f) {
            return;
        }
        for (i = 0; i < 24; i++) {
            if (coasterCoinF[i] == 0) {
                BoardModelPosGet(coasterCoinMdlId[i], &coinPos);
                if (BoardVecMaxDistXZCheck(&coinPos, &ofs, 180.0f)) {
                    CharModelLayerSetAll(2);
                    CharModelCoinEffectCreate(1, &coinPos);
                    BoardModelVisibilitySet(coasterCoinMdlId[i], 0);
                    BoardPlayerCoinsAdd(eventPlayer, 1);
                    HuAudFXPlay(7);
                    coasterCoinF[i] = 1;
                    break;
                }
            }
        }
    }
}

static s16 coasterWinId = -1;

static void CoasterPathMotUpdate(void)
{
    Vec diff;
    s16 modelId;
    ModelData *modelP;
    HsfObject *obj;

    coasterAccel += 0.002f;
    if (coasterSpeed > 0.18f) {
        coasterSpeed = 0.18f;
    }
    else if (coasterSpeed < 0.18f) {
        coasterSpeed += coasterAccel;
    }
    modelId = BoardModelIDGet(coasterPathMdlId);
    modelP = &Hu3DData[modelId];
    Hu3DMotionExec(modelId, modelP->unk_08, modelP->unk_64, 0);
    obj = Hu3DModelObjPtrGet(modelId, "looppath-cube1");
    coasterPosOld = coasterPos;
    coasterPos.x = obj->data.curr.pos.x;
    coasterPos.y = obj->data.curr.pos.y;
    coasterPos.z = obj->data.curr.pos.z;
    VECSubtract(&coasterPosOld, &coasterPos, &diff);
    coasterTime += VECMag(&diff);
}

static s32 coasterMotTbl[8][2]
    = { { DATA_MAKE_NUM(DATADIR_W01, 34), DATA_MAKE_NUM(DATADIR_W01, 42) }, { DATA_MAKE_NUM(DATADIR_W01, 35), DATA_MAKE_NUM(DATADIR_W01, 43) },
          { DATA_MAKE_NUM(DATADIR_W01, 36), DATA_MAKE_NUM(DATADIR_W01, 44) }, { DATA_MAKE_NUM(DATADIR_W01, 37), DATA_MAKE_NUM(DATADIR_W01, 45) },
          { DATA_MAKE_NUM(DATADIR_W01, 38), DATA_MAKE_NUM(DATADIR_W01, 46) }, { DATA_MAKE_NUM(DATADIR_W01, 39), DATA_MAKE_NUM(DATADIR_W01, 47) },
          { DATA_MAKE_NUM(DATADIR_W01, 40), DATA_MAKE_NUM(DATADIR_W01, 48) }, { DATA_MAKE_NUM(DATADIR_W01, 41), DATA_MAKE_NUM(DATADIR_W01, 49) } };

static void CoasterMotCreate(s32 playerNo)
{
    s32 charNo;
    s32 i;

    charNo = GWPlayer[playerNo].character;
    for (i = 0; i < 2; i++) {
        coasterMotId[i] = BoardPlayerMotionCreate(playerNo, coasterMotTbl[charNo][i]);
    }
}

static void CoasterMotKill(s32 playerNo)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        BoardPlayerMotionKill(playerNo, coasterMotId[i]);
        coasterMotId[i] = -1;
    }
}

static void CoasterExec(void)
{
    Mtx playerMtx;
    Vec spacePos;
    Vec cameraRot;
    float coasterRotSpeed;
    float coasterRotDir;
    float coasterMotSpeed;
    s32 seNo;
    CoasterCameraWork *camWork;
    s16 endSpace;
    s16 i;

    coasterAccel = coasterSpeed = 0.0f;
    coasterTime = 0.0f;
    coasterRot.x = 0.0f;
    coasterRot.y = 0.0f;
    coasterRot.z = 0.0f;
    lbl_1_bss_6A8 = 0.0f;
    coasterLoopF = 0;
    coasterCameraUp.x = 0.0f;
    coasterCameraUp.z = 0.0f;
    coasterCameraUp.y = 1.0f;
    coasterCamSpeed = 0.08f;
    CoasterMotCreate(eventPlayer);
    BoardPlayerMotionStart(eventPlayer, coasterMotId[0], HU3D_MOTATTR_LOOP);
    BoardSpaceAttrSet(0, 1);
    CoasterEffCreate();
    BoardModelMotionStart(coasterPathMdlId, 0, 0);
    if (boardWork->hostSide == 0) {
        BoardModelMotionTimeSet(coasterPathMdlId, coasterMaxTime);
        coasterBaseRotY = -90.0f;
        coasterStartSpace = BoardSpaceFlagPosGet(1, 0x2000, &spacePos);
        endSpace = BoardSpaceFlagSearch(0, 0x1000);
        coasterRotDir = -1.0f;
    }
    else {
        BoardModelMotionTimeSet(coasterPathMdlId, 0.0f);
        coasterBaseRotY = 90.0f;
        coasterStartSpace = BoardSpaceFlagPosGet(1, 0x1000, &spacePos);
        endSpace = BoardSpaceFlagSearch(0, 0x2000);
        coasterRotDir = 1.0f;
    }
    coasterPos = spacePos;
    coasterPosOld = coasterPos;
    BoardModelMotionSpeedSet(coasterPathMdlId, coasterSpeed);
    BoardPlayerPosSetV(eventPlayer, &coasterPos);
    BoardCameraPosCalcFuncSet(CoasterPosCalc);
    coasterCameraObj = omAddObjEx(boardObjMan, 0x7E02, 0, 0, -1, CoasterCameraObjMain);
    camWork = OM_GET_WORK_PTR(coasterCameraObj, CoasterCameraWork);
    camWork->killF = FALSE;
    cameraRot.x = -40.0f;
    cameraRot.z = 0.0f;
    cameraRot.y = -coasterBaseRotY;
    BoardCameraMotionStartEx(mapObjMdlId[MAPOBJ_COASTER], &cameraRot, NULL, 150.0f, -1.0f, 2);
    BoardCameraMotionWait();
    BoardModelPosGet(mapObjMdlId[MAPOBJ_COASTER], &coasterCameraTarget);
    coasterCameraPos.x = coasterCameraTarget.x + 1000.0 * (sind(cameraRot.y) * cosd(cameraRot.x));
    coasterCameraPos.y = coasterCameraTarget.y + 1000.0 * -sind(cameraRot.x);
    coasterCameraPos.z = coasterCameraTarget.z + 1000.0 * (cosd(cameraRot.y) * cosd(cameraRot.x));
    MTXRotRad(coasterMtx, 'y', MTXDegToRad(coasterBaseRotY));
    BoardModelMtxSet(mapObjMdlId[MAPOBJ_COASTER], &coasterMtx);
    BoardPlayerMtxSet(eventPlayer, &coasterMtx);
    BoardModelRotSet(mapObjMdlId[MAPOBJ_COASTER], 0.0f, 0.0f, 0.0f);
    BoardPlayerRotSet(eventPlayer, 0.0f, 0.0f, 0.0f);
    BoardPlayerExistCheck(eventPlayer, 0);
    BoardMusStart(1, 0x10, 0x7F, 0);
    CoasterCoinCreate();
    BoardStatusShowSetForce(eventPlayer);
    BoardStatusShowSet(eventPlayer, 1);
    while (!BoardStatusStopCheck(eventPlayer)) {
        HuPrcVSleep();
    }
    seNo = HuAudFXPlay(0x40C);
    CoasterWinCreate();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    coasterType = 1;
    HuAudFXPlay(0x413);
    while (TRUE) {
        CoasterPathUpdate();
        CoasterPathMotUpdate();
        CoasterRotUpdate();
        BoardModelPosSetV(mapObjMdlId[MAPOBJ_COASTER], &coasterPos);
        BoardPlayerPosSetV(eventPlayer, &coasterPos);
        if (BoardPlayerSizeGet(eventPlayer) != 1) {
            MTXTrans(playerMtx, 0.0f, 30.0f, 0.0f);
        }
        else {
            MTXTrans(playerMtx, 0.0f, 400.0f, 250.0f);
        }
        BoardModelMtxSet(mapObjMdlId[MAPOBJ_COASTER], &coasterMtx);
        MTXConcat(coasterMtx, playerMtx, playerMtx);
        BoardPlayerMtxSet(eventPlayer, &playerMtx);
        if (boardWork->hostSide == 0) {
            coasterMotSpeed = -coasterSpeed;
        }
        else {
            coasterMotSpeed = coasterSpeed;
        }
        BoardModelMotionSpeedSet(coasterPathMdlId, coasterMotSpeed);
        if (boardWork->hostSide == 0) {
            if (BoardModelMotionTimeGet(coasterPathMdlId) <= 0.0f) {
                break;
            }
        }
        else {
            if (BoardModelMotionTimeGet(coasterPathMdlId) >= coasterMaxTime) {
                break;
            }
        }
        HuPrcVSleep();
    }
    MTXIdentity(coasterMtx);
    CoasterWinKill();
    HuAudFXStop(seNo);
    CoasterCameraObjKill();
    CoasterEffKill();
    if (BoardPlayerSizeGet(eventPlayer) == 1) {
        MTXTrans(playerMtx, 0.0f, 400.0f, 250.0f);
    }
    else {
        MTXTrans(playerMtx, 0.0f, 30.0f, 0.0f);
    }
    BoardModelMtxSet(mapObjMdlId[MAPOBJ_COASTER], &coasterMtx);
    BoardPlayerMtxSet(eventPlayer, &playerMtx);
    coasterRot.x = coasterRot.z = 0.0f;
    BoardAudSeqFadeOut(1, 1000);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    HuAudFXPlay(0x401);
    coasterRotSpeed = (-coasterBaseRotY - coasterRot.y) / 30.0f;
    for (i = 0; i < 30; i++) {
        BoardModelRotSetV(mapObjMdlId[MAPOBJ_COASTER], &coasterRot);
        BoardPlayerRotSetV(eventPlayer, &coasterRot);
        coasterRot.y += coasterRotSpeed * coasterRotDir;
        HuPrcVSleep();
    }
    coasterRot.y = -coasterBaseRotY;
    BoardModelRotSetV(mapObjMdlId[MAPOBJ_COASTER], &coasterRot);
    BoardPlayerRotSetV(eventPlayer, &coasterRot);
    BoardStatusShowSet(eventPlayer, 0);
    BoardSpaceAttrReset(0, 1);
    CoasterCoinKill();
    BoardCameraMoveSet(0);
    BoardCameraTargetPlayerSet(eventPlayer);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    do {
        HuPrcVSleep();
    } while (WipeStatGet() != 0);
    BoardPlayerIdleSet(eventPlayer);
    BoardPlayerMtxSet(eventPlayer, &coasterMtx);
    BoardCameraPosCalcFuncSet(NULL);
    BoardPlayerExistCheck(eventPlayer, 1);
    BoardSpacePosGet(0, endSpace, &spacePos);
    GWPlayer[eventPlayer].space_curr = endSpace;
    BoardPlayerPosSetV(eventPlayer, &spacePos);
    CoasterMotKill(eventPlayer);
    coasterDoneF = 1;
}

static void CoasterExit(void)
{
    if (coasterDoneF != 0) {
        if (boardWork->hostSide == 0) {
            boardWork->hostSide = 1;
        }
        else {
            boardWork->hostSide = 0;
        }
        coasterDoneF = 0;
        UpdateHostDisp();
    }
    CoasterPlayerManKill();
    while (coasterPlayerManObj) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 1000);
    BoardCameraMoveSet(1);
    BoardCameraMotionWait();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardStatusShowSetAll(1);
}

static void CoasterWinCreate(void)
{
    float winSize[2];
    float winX;
    float winY;

    HuWinMesMaxSizeGet(1, winSize, MAKE_MESSID(13, 5));
    winX = -10000.0f;
    winY = 352.0f;
    coasterWinId = HuWinCreate(winX, winY, winSize[0], winSize[1], 0);
    HuWinBGTPLvlSet(coasterWinId, 0.0f);
    HuWinMesSpeedSet(coasterWinId, 0);
    HuWinMesSet(coasterWinId, MAKE_MESSID(13, 5));
}

static void CoasterWinKill(void)
{
    if (coasterWinId != -1) {
        HuWinKill(coasterWinId);
        coasterWinId = -1;
    }
}

static s32 CoasterHostExec(void)
{
    Vec startPos;
    Vec endPos;
    Vec dir;
    float angle;
    u32 mess;
    s32 i;
    s32 spaceEnd;
    s32 spaceStart;

    mess = 0;
    coasterType = 0;
    coasterLandF = 0;
    coasterDoneF = 0;
    eventPlayer = GWSystem.player_curr;
    spaceStart = GWPlayer[eventPlayer].space_curr;
    BoardPlayerMotionShiftSet(eventPlayer, 1, 0.0f, 14.0f, HU3D_MOTATTR_LOOP);
    BoardWinCreateChoice(0, MAKE_MESSID(13, 0), -1, 0);
    if (GWPlayer[eventPlayer].com) {
        CoasterHostComKeySet(eventPlayer);
    }
    BoardWinWait();
    if (BoardWinChoiceGet() != 0) {
        return 0;
    }
    BoardWinCreate(2, 0xD0006, 0);
    BoardWinWait();
    spaceEnd = BoardSpaceLinkFlagSearch(0, spaceStart, 0x02000000);
    BoardSpacePosGet(0, spaceStart, &startPos);
    BoardSpacePosGet(0, spaceEnd, &endPos);
    VECSubtract(&endPos, &startPos, &dir);
    VECNormalize(&dir, &dir);
    angle = atan2d(-dir.x, -dir.z);
    BoardPlayerRotSet(eventPlayer, 0.0f, angle, 0.0f);
    BoardPlayerMoveBetween(eventPlayer, spaceStart, spaceEnd);
    while (GWPlayer[eventPlayer].moving) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(eventPlayer);
    while (TRUE) {
        BoardWinCreateChoice(1, MAKE_MESSID(13, 1), 0, 0);
        BoardWinAttrSet(0x10);
        if (GWPlayer[eventPlayer].com) {
            if (BoardPlayerCoinsGet(eventPlayer) >= 5) {
                BoardComKeySetUp();
            }
            else {
                BoardComKeySetDown();
            }
        }
        BoardWinWait();
        if (BoardWinChoiceGet() == 1) {
            mess = MAKE_MESSID(13, 3);
            break;
        }
        if (BoardWinChoiceGet() == 2) {
            BoardViewMapExec(eventPlayer);
            continue;
        }
        if (BoardPlayerCoinsGet(eventPlayer) < 5) {
            mess = MAKE_MESSID(13, 4);
            break;
        }
        for (i = 0; i < 5; i++) {
            BoardPlayerCoinsAdd(eventPlayer, -1);
            HuAudFXPlay(0xE);
            HuPrcSleep(6);
        }
        HuAudFXPlay(0xF);
        BoardWinCreate(2, MAKE_MESSID(13, 2), 0);
        BoardWinWait();
        BoardWinKill();
        BoardAudSeqPause(0, 1, 1000);
        HuAudFXPlay(0x402);
        BoardStatusShowSetAll(0);
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        CoasterPlayerManCreate();
        return TRUE;
    }
    if (mess != 0) {
        BoardWinCreate(1, mess, 0);
        BoardWinWait();
        BoardWinKill();
    }
    BoardCameraTargetPlayerSet(eventPlayer);
    VECSubtract(&startPos, &endPos, &dir);
    VECNormalize(&dir, &dir);
    angle = atan2d(-dir.x, -dir.z);
    BoardPlayerRotSet(eventPlayer, 0.0f, angle, 0.0f);
    BoardPlayerMoveBetween(eventPlayer, spaceEnd, spaceStart);
    while (GWPlayer[eventPlayer].moving) {
        HuPrcVSleep();
    }
    return FALSE;
}

static void CoasterMain(void)
{
    if (CoasterHostExec() != 0) {
        CoasterExec();
        CoasterExit();
    }
    HuPrcEnd();
}

static void CoasterDestroy(void)
{
    BoardWinKill();
    coasterProc = NULL;
}

static void CoasterEvent(void)
{
    eventPlayer = GWSystem.player_curr;
    BoardRollDispSet(0);
    if (BoardPlayerSizeGet(eventPlayer) == 2 || GWPlayer[eventPlayer].bowser_suit) {
        return;
    }
    coasterProc = HuPrcChildCreate(CoasterMain, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(coasterProc, CoasterDestroy);
    while (coasterProc) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

static void CoasterCoinCreate(void)
{
    Vec pos;
    Vec posSpace;
    Vec dir;
    float radius;
    float angle;
    BoardSpace *space;
    s32 side;
    s32 newSide;
    s32 coinNum;
    s32 spaceId;
    s32 i;

    for (i = 0; i < 24; i++) {
        coasterCoinMdlId[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 9), NULL, 0);
        BoardModelVisibilitySet(coasterCoinMdlId[i], 0);
        BoardModelMotionStart(coasterCoinMdlId[i], 0, HU3D_MOTATTR_LOOP);
        coasterCoinF[i] = 0;
    }
    radius = 180.0f;
    spaceId = BoardSpaceFlagPosGet(1, 0x2000, &pos);
    side = BoardRand() & 1;
    coinNum = i = 0;
    while (i < 24) {
        space = BoardSpaceGet(1, spaceId);
        spaceId = space->link[0];
        if (spaceId == -1 || space->link_cnt == 0) {
            break;
        }
        if (!(space->flag & 0x80)) {
            posSpace = space->pos;
        }
        else {
            if (coinNum >= 3) {
                if (BoardRandFloat() < 0.5f) {
                    newSide = 1;
                }
                else {
                    newSide = 0;
                }
                side = newSide;
                coinNum = 0;
            }
            VECSubtract(&posSpace, &space->pos, &dir);
            VECNormalize(&dir, &dir);
            angle = atan2d(dir.z, dir.x);
            if (side != 0) {
                angle += 180.0f;
            }
            pos.x = space->pos.x + radius * sind(angle);
            pos.y = space->pos.y + 80.0f;
            pos.z = space->pos.z + radius * cosd(angle);
            BoardModelPosSetV(coasterCoinMdlId[i], &pos);
            BoardModelVisibilitySet(coasterCoinMdlId[i], 1);
            posSpace = space->pos;
            i++;
            coinNum++;
        }
    }
}

static void CoasterCoinKill(void)
{
    s32 i;

    for (i = 0; i < 24; i++) {
        if (coasterCoinMdlId[i] != -1) {
            BoardModelKill(coasterCoinMdlId[i]);
            coasterCoinMdlId[i] = -1;
        }
    }
}

static s32 cupMoveSeNo = -1;
static s32 decaStompSeNo = -1;

static s16 cupMapObj[2][4] = {
    { MAPOBJ_CUPR1, MAPOBJ_CUPR2, MAPOBJ_CUPR3, MAPOBJ_CUPR_ARROW },
    { MAPOBJ_CUPL1, MAPOBJ_CUPL2, MAPOBJ_CUPL3, MAPOBJ_CUPL_ARROW }
};

static char *cupHookTbl[] = { "chara1", "chara2", "chara3" };

static float cupArrowRot[2][2] = { { 90.0f, 0.0f }, { 0.0f, 270.0f } };

static void CupInit(void)
{
    float rotY;
    s16 mdlIdDish;
    s16 mdlId;
    s32 i;
    s32 j;
    char *hookName[] = { "cup1", "cup2", "cup3", "ya1" };
    s32 dishMapObj[] = { MAPOBJ_CUPR_DISH, MAPOBJ_CUPL_DISH };

    for (i = 0; i < 2; i++) {
        mdlIdDish = mapObjMdlId[dishMapObj[i]];
        BoardModelMotionStart(mdlIdDish, 0, HU3D_MOTATTR_LOOP);
        BoardModelExistDupe(mdlIdDish, 0);
        for (j = 0; j < 4; j++) {
            mdlId = mapObjMdlId[cupMapObj[i][j]];
            BoardModelExistDupe(mdlId, 1);
            BoardModelHookSet(mdlIdDish, hookName[j], mdlId);
            BoardModelMotionStart(mdlId, 0, HU3D_MOTATTR_LOOP);
            BoardModelRotSet(mdlId, 0.0f, 360.0f * BoardRandFloat(), 0.0f);
        }
    }
    if (boardWork->cupDir[0] != 0) {
        rotY = 0.0f;
    }
    else {
        rotY = 90.0f;
    }
    BoardModelRotSet(mapObjMdlId[MAPOBJ_CUPR_ARROW], 0.0f, rotY, 0.0f);
    if (boardWork->cupDir[1] != 0) {
        rotY = -90.0f;
    }
    else {
        rotY = 0.0f;
    }
    BoardModelRotSet(mapObjMdlId[MAPOBJ_CUPL_ARROW], 0.0f, rotY, 0.0f);
}

static void CupMotOnSet(s32 stopF)
{
    s16 dishMdlId;
    s16 cupMdlId;
    s16 i;
    s32 dishMapObj[] = { MAPOBJ_CUPR_DISH, MAPOBJ_CUPL_DISH };

    dishMdlId = mapObjMdlId[dishMapObj[cupSide]];
    if (stopF != 0) {
        BoardModelMotionSpeedSet(dishMdlId, 1.0f);
        BoardModelAttrReset(dishMdlId, HU3D_MOTATTR_PAUSE);
        for (i = 0; i < 3; i++) {
            cupMdlId = mapObjMdlId[cupMapObj[cupSide][i]];
            BoardModelMotionSpeedSet(cupMdlId, 1.0f);
            BoardModelAttrReset(cupMdlId, HU3D_MOTATTR_PAUSE);
        }
    }
    else {
        BoardModelMotionSpeedSet(dishMdlId, 0.0f);
        BoardModelAttrSet(dishMdlId, HU3D_MOTATTR_PAUSE);
        for (i = 0; i < 3; i++) {
            cupMdlId = mapObjMdlId[cupMapObj[cupSide][i]];
            BoardModelMotionSpeedSet(cupMdlId, 0.0f);
            BoardModelAttrSet(cupMdlId, HU3D_MOTATTR_PAUSE);
        }
    }
}

static void CupEvent(s32 side, s32 spaceStart)
{
    cupSide = side;
    cupSpaceStart = spaceStart;
    BoardRollDispSet(0);
    cupProc = HuPrcChildCreate(CupMain, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(cupProc, CupDestroy);
    while (cupProc) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

static void CupMain(void)
{
    s16 dishMdlId;

    cupMoveSeNo = -1;
    decaStompSeNo = -1;
    BoardPlayerIdleSet(GWSystem.player_curr);
    if (cupSide == 0) {
        dishMdlId = mapObjMdlId[MAPOBJ_CUPR_DISH];
    }
    else {
        dishMdlId = mapObjMdlId[MAPOBJ_CUPL_DISH];
    }
    BoardCameraTargetModelSet(dishMdlId);
    BoardCameraOffsetSet(0.0f, 0.0f, 0.0f);
    CupObjCreate();
    while (!CupObjCheck()) {
        HuPrcVSleep();
    }
    CupExec();
    CupMotOnSet(1);
    BoardCameraTargetPlayerSet(GWSystem.player_curr);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    HuPrcEnd();
}

static void CupDestroy(void)
{
    cupProc = NULL;
}

static void CupExec(void)
{
    s16 cupArrowMapObj[] = { MAPOBJ_CUPR_ARROW, MAPOBJ_CUPL_ARROW };
    s16 cupArrowMdlId;
    s32 cupDir;
    float rotY;
    float rotYNew;

    cupDir = boardWork->cupDir[cupSide];
    boardWork->cupDir[cupSide] ^= 1;
    cupArrowMdlId = mapObjMdlId[cupArrowMapObj[cupSide]];
    rotY = cupArrowRot[cupSide][cupDir];
    rotYNew = cupArrowRot[cupSide][cupDir ^ 1];
    HuAudFXPlay(0x403);
    while (TRUE) {
        HuPrcVSleep();
        if (BoardDAngleCalcRange(&rotY, rotYNew, 3.0f) != 0) {
            break;
        }
        BoardModelRotSet(cupArrowMdlId, 0.0f, rotY, 0.0f);
    }
}

static BOOL CupObjCheck(void)
{
    return cupObj ? FALSE : TRUE;
}

static void CupObjCreate(void)
{
    CupObjWork *work;
    float time;
    float speed;
    s16 dishMdlId;
    s16 cupMdlId;
    s32 i;

    if (cupSide == 0) {
        dishMdlId = mapObjMdlId[MAPOBJ_CUPR_DISH];
    }
    else {
        dishMdlId = mapObjMdlId[MAPOBJ_CUPL_DISH];
    }
    while (TRUE) {
        time = BoardModelMotionTimeGet(dishMdlId);
        if (time >= 209.0f && time <= 211.0f) {
            break;
        }
        if (time >= 129.0f && time <= 131.0f) {
            break;
        }
        if (time >= 49.0f && time <= 51.0f) {
            break;
        }
        HuPrcVSleep();
    }
    speed = 1.0f;
    while (speed > 0.01f) {
        speed *= 0.9f;
        if (speed <= 0.01f) {
            speed = 0.0f;
        }
        BoardModelMotionSpeedSet(dishMdlId, speed);
        for (i = 0; i < 3; i++) {
            cupMdlId = mapObjMdlId[cupMapObj[cupSide][i]];
            BoardModelMotionSpeedSet(cupMdlId, speed);
        }
        HuPrcVSleep();
    }
    CupMotOnSet(0);
    cupObj = omAddObjEx(boardObjMan, 0x103, 0, 0, -1, CupObjMain);
    work = OM_GET_WORK_PTR(cupObj, CupObjWork);
    work->killF = 0;
    work->time = 0;
    work->delay = 0;
    work->stopF = 0;
    work->dishMdlId = dishMdlId;
    if (BoardPlayerSizeGet(GWSystem.player_curr) == 2) {
        work->decaF = TRUE;
    }
    else {
        work->decaF = FALSE;
    }
}

static void CupObjMain(omObjData *obj)
{
    CupObjWork *work = OM_GET_WORK_PTR(obj, CupObjWork);

    if (work->killF != 0 || BoardIsKill()) {
        cupObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), obj);
        return;
    }
    if (work->delay != 0) {
        work->delay--;
        return;
    }
    switch (work->mode) {
        case 0:
            CupObjInit(work, obj);
            break;
        case 2:
            CupObjJumpWait(work, obj);
            break;
        case 3:
            CupObjStop(work, obj);
            break;
        case 1:
            CupObjRotate(work, obj);
            break;
    }
}

static void CupObjInit(CupObjWork *work, omObjData *obj)
{
    Mtx objMtx;
    Vec objPosPrev;
    Vec playerPos;
    Vec objRot;
    Vec objPos;
    float temp_f31;
    float var_f30;
    s32 var_r28;
    s32 i;

    BoardPlayerPosGet(GWSystem.player_curr, &playerPos);
    var_f30 = 1000000.0f;
    for (i = 0; i < 3; i++) {
        Hu3DModelObjPosGet(BoardModelIDGet(work->dishMdlId), cupHookTbl[i], &objPos);
        temp_f31 = VECSquareDistance(&objPos, &playerPos);
        if (temp_f31 < var_f30) {
            var_f30 = temp_f31;
            cupHookNo = i;
            objPosPrev = objPos;
        }
    }
    Hu3DModelObjMtxGet(BoardModelIDGet(work->dishMdlId), cupHookTbl[cupHookNo], objMtx);
    Hu3DMtxRotGet(&objMtx, &objRot);
    objRot.y = 180.0f;
    VECSubtract(&objPosPrev, &playerPos, &objPos);
    obj->trans.x = objPos.x / 25.0f;
    obj->trans.z = objPos.z / 25.0f;
    var_r28 = BoardPlayerRotYGet(GWSystem.player_curr);
    obj->trans.y = BoardDAngleCalc(objRot.y - var_r28) / 25.0f;
    obj->scale.x = objPosPrev.x;
    obj->scale.y = objPosPrev.y;
    obj->scale.z = objPosPrev.z;
    BoardPlayerMotionShiftSet(GWSystem.player_curr, 4, 15.0f, 5.0f, HU3D_MOTATTR_NONE);
    work->mode = 2;
    work->time = 0;
}

static void CupObjJumpWait(CupObjWork *work, omObjData *obj)
{
    Vec pos;
    float time;
    float rotY;
    float scaleY;
    s16 var_r24;

    if (work->time >= 55) {
        BoardPlayerRotSet(GWSystem.player_curr, 0.0f, 0.0f, 0.0f);
        BoardPlayerIdleSet(GWSystem.player_curr);
        if (GWPlayer[GWSystem.player_curr].bowser_suit) {
            BoardModelHookSet(work->dishMdlId, cupHookTbl[cupHookNo], BoardBowserSuitModelGet());
        }
        else {
            BoardModelHookSet(work->dishMdlId, cupHookTbl[cupHookNo], BoardPlayerModelGet(GWSystem.player_curr));
        }
        var_r24 = mapObjMdlId[cupMapObj[cupSide][cupHookNo]];
        if (work->decaF != 0) {
            BoardModelScaleSet(var_r24, 1.0f, 0.1f, 1.0f);
        }
        CupMotOnSet(1);
        cupMoveSeNo = HuAudFXPlay(0x410);
        work->time = 0;
        work->mode = 1;
        return;
    }
    if (work->time == 25) {
        BoardPlayerPosSet(GWSystem.player_curr, obj->scale.x, obj->scale.y, obj->scale.z);
        BoardPlayerMotionShiftSet(GWSystem.player_curr, 5, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    }
    if (work->time < 25) {
        OSu8tof32(&work->time, &time);
        BoardPlayerPosGet(GWSystem.player_curr, &pos);
        pos.x += obj->trans.x;
        pos.z += obj->trans.z;
        pos.y += 15.0f + -0.08166667f * time * time;
        if (pos.y <= obj->scale.y) {
            pos.y = obj->scale.y;
        }
        rotY = obj->trans.y + BoardPlayerRotYGet(GWSystem.player_curr);
        BoardPlayerRotYSet(GWSystem.player_curr, rotY);
        BoardPlayerPosSetV(GWSystem.player_curr, &pos);
        if (work->time > 12 && work->decaF != 0) {
            if (decaStompSeNo == -1) {
                decaStompSeNo = HuAudFXPlay(0x411);
            }
            OSu8tof32(&work->time, &time);
            time -= 12.0f;
            time = 90.0f * (time / 12.5f);
            scaleY = cosd(time);
            if (scaleY < 0.1f) {
                scaleY = 0.1f;
            }
            var_r24 = mapObjMdlId[cupMapObj[cupSide][cupHookNo]];
            BoardModelScaleSet(var_r24, 1.0f, scaleY, 1.0f);
        }
    }
    work->time++;
}

static void CupObjHookReset(CupObjWork *work, omObjData *obj)
{
    Vec endPos;
    Vec startPos;
    Vec diff;

    BoardModelHookObjReset(work->dishMdlId, cupHookTbl[cupHookNo]);
    Hu3DModelObjPosGet(BoardModelIDGet(work->dishMdlId), cupHookTbl[cupHookNo], &startPos);
    BoardPlayerPosSetV(GWSystem.player_curr, &startPos);
    BoardSpacePosGet(0, cupSpaceEnd, &endPos);
    VECSubtract(&endPos, &startPos, &diff);
    obj->trans.x = diff.x / 25.0f;
    obj->trans.z = diff.z / 25.0f;
    obj->scale.x = endPos.x;
    obj->scale.y = endPos.y;
    obj->scale.z = endPos.z;
    BoardPlayerMotionShiftSet(GWSystem.player_curr, 4, 15.0f, 5.0f, HU3D_MOTATTR_NONE);
    BoardPlayerRotYSet(GWSystem.player_curr, atan2d(diff.x, diff.z));
    work->mode = 3;
    work->time = 0;
}

static void CupObjStop(CupObjWork *work, omObjData *obj)
{
    Vec pos;
    Vec spacePos;
    float angle;
    float time;
    s16 mdlId;

    if (work->time >= 55) {
        BoardSpacePosGet(0, cupSpaceEnd, &spacePos);
        GWPlayer[GWSystem.player_curr].space_curr = cupSpaceEnd;
        BoardPlayerPosSetV(GWSystem.player_curr, &spacePos);
        BoardPlayerIdleSet(GWSystem.player_curr);
        mdlId = mapObjMdlId[cupMapObj[cupSide][cupHookNo]];
        if (work->decaF != 0) {
            BoardModelScaleSet(mdlId, 1.0f, 1.0f, 1.0f);
        }
        work->killF = 1;
    }
    if (work->time == 25) {
        BoardPlayerPosSet(GWSystem.player_curr, obj->scale.x, obj->scale.y, obj->scale.z);
        BoardPlayerMotionShiftSet(GWSystem.player_curr, 5, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    }
    if (work->time < 25) {
        OSu8tof32(&work->time, &time);
        BoardPlayerPosGet(GWSystem.player_curr, &pos);
        pos.x += obj->trans.x;
        pos.z += obj->trans.z;
        pos.y += 15.0f + -0.08166667f * time * time;
        if (pos.y <= obj->scale.y) {
            pos.y = obj->scale.y;
        }
        BoardPlayerPosSetV(GWSystem.player_curr, &pos);
        if (work->time > 12 && work->decaF != 0) {
            OSu8tof32(&work->time, &time);
            time -= 12.0f;
            time = 90.0f * (time / 12.5f);
            angle = sind(time);
            if (angle < 0.1f) {
                angle = 0.1f;
            }
            mdlId = mapObjMdlId[cupMapObj[cupSide][cupHookNo]];
            BoardModelScaleSet(mdlId, 1.0f, angle, 1.0f);
        }
    }
    work->time++;
}

static void CupObjRotate(CupObjWork *work, omObjData *obj)
{
    Vec spacePos;
    Vec objPos;

    float dist;
    BoardSpace *space;
    s16 mdlId;
    u32 flag;
    s32 cupDir;
    s32 i;

    if (work->stopF != 0) {
        work->dishSpeed *= 0.9f;
        if (work->dishSpeed <= 0.01f) {
            work->dishSpeed = 0.0f;
            CupMotOnSet(0);
            if (cupMoveSeNo != -1) {
                HuAudFXStop(cupMoveSeNo);
                cupMoveSeNo = -1;
            }
            CupObjHookReset(work, obj);
        }
        BoardModelMotionSpeedSet(work->dishMdlId, work->dishSpeed);
        for (i = 0; i < 3; i++) {
            mdlId = mapObjMdlId[cupMapObj[cupSide][i]];
            BoardModelMotionSpeedSet(mdlId, work->dishSpeed);
        }
        return;
    }
    if (cupSide == 0) {
        cupDir = boardWork->cupDir[cupSide] ^ 1;
    }
    else {
        cupDir = boardWork->cupDir[cupSide];
    }
    space = BoardSpaceGet(0, cupSpaceStart);
    cupSpaceEnd = -1;
    for (i = 0; i < space->link_cnt; i++) {
        if (space->link[i] != -1) {
            flag = BoardSpaceFlagGet(0, space->link[i]);
            if ((flag & 0x200) && cupDir == 0) {
                cupSpaceEnd = space->link[i];
            }
            if ((flag & 0x100) && cupDir != 0) {
                cupSpaceEnd = space->link[i];
            }
        }
    }
    BoardSpacePosGet(0, cupSpaceEnd, &spacePos);
    Hu3DModelObjPosGet(BoardModelIDGet(work->dishMdlId), cupHookTbl[cupHookNo], &objPos);
    dist = BoardVecDistXZCalc(&spacePos, &objPos);
    if (dist <= 300.0f) {
        work->stopF = TRUE;
        work->dishSpeed = 1.0f;
    }
}

static void CupLandEvent(s32 playerNo, s32 spaceId)
{
    Vec spacePos;
    Vec cupRPos;
    Vec cupLPos;
    float cupRDist;
    float cupLDist;
    s16 sp14[] = { MAPOBJ_CUPR_DISH, MAPOBJ_CUPL_DISH };

    BoardPlayerIdleSet(GWSystem.player_curr);
    BoardSpacePosGet(0, spaceId, &spacePos);
    BoardModelPosGet(mapObjMdlId[MAPOBJ_CUPR_DISH], &cupRPos);
    BoardModelPosGet(mapObjMdlId[MAPOBJ_CUPL_DISH], &cupLPos);
    cupRDist = VECDistance(&cupRPos, &spacePos);
    cupLDist = VECDistance(&cupLPos, &spacePos);
    if (cupRDist < cupLDist) {
        cupSide = 0;
    }
    else {
        cupSide = 1;
    }
    BoardCameraTargetModelSet(mapObjMdlId[sp14[cupSide]]);
    BoardCameraMotionWait();
    HuPrcSleep(42);
    CupExec();
    BoardCameraTargetPlayerSet(GWSystem.player_curr);
    BoardCameraMotionWait();
    HuPrcSleep(12);
}

static void CoasterLandEvent(s32 playerNo, s32 spaceId)
{
    eventPlayer = playerNo;
    coasterType = 0;
    coasterProc = HuPrcChildCreate(CoasterLandMain, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(coasterProc, CoasterDestroy);
    while (coasterProc) {
        HuPrcVSleep();
    }
}

static void CoasterLandMain(void)
{
    coasterLandF = 1;
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    CoasterLandExec();
    CoasterExit();
    HuPrcEnd();
}

static void CoasterLandExec(void)
{
    Vec spacePos;
    float motSpeed;
    s16 spaceId;
    s32 seNo;
    s32 endF;

    endF = 0;
    coasterAccel = coasterSpeed = 0.18f;
    coasterTime = 0.0f;
    coasterRot.x = 0.0f;
    coasterRot.y = 0.0f;
    coasterRot.z = 0.0f;
    lbl_1_bss_6A8 = 0.0f;
    coasterLoopF = 0;
    coasterCameraUp.x = 0.0f;
    coasterCameraUp.z = 0.0f;
    coasterCameraUp.y = 1.0f;
    coasterCamSpeed = 0.04f;
    BoardSpaceAttrSet(0, 1);
    CoasterEffCreate();
    BoardModelMotionStart(coasterPathMdlId, 0, 0);
    if (boardWork->hostSide == 0) {
        BoardModelMotionTimeSet(coasterPathMdlId, coasterMaxTime);
        coasterBaseRotY = -90.0f;
        coasterStartSpace = BoardSpaceFlagPosGet(1, 0x2000, &spacePos);
        spaceId = BoardSpaceFlagSearch(1, 0x1000);
    }
    else {
        BoardModelMotionTimeSet(coasterPathMdlId, 0.0f);
        coasterBaseRotY = 90.0f;
        coasterStartSpace = BoardSpaceFlagPosGet(1, 0x1000, &spacePos);
        spaceId = BoardSpaceFlagSearch(1, 0x2000);
    }
    coasterPos = spacePos;
    BoardCameraMotionStartEx(mapObjMdlId[MAPOBJ_COASTER], NULL, NULL, 2400.0f, -1.0f, 2);
    MTXRotRad(coasterMtx, 'y', MTXDegToRad(coasterBaseRotY));
    BoardModelMtxSet(mapObjMdlId[MAPOBJ_COASTER], &coasterMtx);
    BoardModelRotSet(mapObjMdlId[MAPOBJ_COASTER], 0.0f, 0.0f, 0.0f);
    CoasterPathMotUpdate();
    coasterPosOld = coasterPos;
    coasterCameraTarget = coasterPos;
    coasterCameraPos = coasterPos;
    CoasterPlayerManCreate();
    BoardModelMotionSpeedSet(coasterPathMdlId, coasterSpeed);
    BoardCameraMotionWait();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    coasterType = 1;
    seNo = HuAudFXPlay(0x412);
    while (TRUE) {
        CoasterPathUpdate();
        CoasterPathMotUpdate();
        CoasterRotUpdate();
        BoardModelPosSetV(mapObjMdlId[MAPOBJ_COASTER], &coasterPos);
        BoardModelMtxSet(mapObjMdlId[MAPOBJ_COASTER], &coasterMtx);
        if (boardWork->hostSide == 0) {
            motSpeed = -coasterSpeed;
        }
        else {
            motSpeed = coasterSpeed;
        }
        BoardModelMotionSpeedSet(coasterPathMdlId, motSpeed);
        if (boardWork->hostSide == 0) {
            if (BoardModelMotionTimeGet(coasterPathMdlId) <= 20.0f && endF == 0) {
                WipeColorSet(0, 0, 0);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
                endF = 1;
            }
        }
        else {
            if (BoardModelMotionTimeGet(coasterPathMdlId) >= coasterMaxTime - 20.0f && endF == 0) {
                WipeColorSet(0, 0, 0);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
                endF = 1;
            }
        }
        if (endF != 0 && WipeStatGet() == 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuAudFXStop(seNo);
    CoasterEffKill();
    CoasterPlayerManKill();
    while (coasterPlayerManObj) {
        HuPrcVSleep();
    }
    MTXIdentity(coasterMtx);
    BoardModelMtxSet(mapObjMdlId[MAPOBJ_COASTER], &coasterMtx);
    coasterRot.x = 0.0f;
    coasterRot.z = 0.0f;
    coasterRot.y = -coasterBaseRotY;
    BoardModelRotSetV(mapObjMdlId[MAPOBJ_COASTER], &coasterRot);
    BoardSpacePosGet(1, spaceId, &spacePos);
    BoardModelPosSetV(mapObjMdlId[MAPOBJ_COASTER], &spacePos);
    BoardSpaceAttrReset(0, 1);
    BoardCameraMoveSet(0);
    BoardCameraTargetPlayerSet(eventPlayer);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    coasterDoneF = 1;
}

static s8 coasterChasePlayer = -1;

static void CoasterPlayerManCreate(void)
{
    CoasterPlayerManWork *work;
    CoasterPlayerWork *workPlayer;
    Vec playerPos;
    float motTime;
    s16 charNo;
    s16 spaceId;
    s16 i;
    u32 spaceFlag;

    coasterPlayerManObj = omAddObjEx(boardObjMan, 0x103, 0, 0, -1, CoasterPlayerManUpdate);
    work = OM_GET_WORK_PTR(coasterPlayerManObj, CoasterPlayerManWork);
    work->killF = 0;
    work->player = HuMemDirectMallocNum(HEAP_SYSTEM, 4 * sizeof(CoasterPlayerWork), MEMORY_DEFAULT_NUM);
    memset(work->player, 0, 4 * sizeof(CoasterPlayerWork));
    coasterChasePlayer = -1;
    coasterPlayerChaseNum = 0;
    for (work->playerNum = i = 0; i < 4; i++) {
        workPlayer = &work->player[work->playerNum];
        spaceId = GWPlayer[i].space_curr;
        charNo = GWPlayer[i].character;
        spaceFlag = BoardSpaceFlagGet(0, spaceId);
        if (!(spaceFlag & 1)) {
            workPlayer->mode = -1;
            continue;
        }
        workPlayer->mode = 0;
        workPlayer->playerNo = i;
        workPlayer->delay = 0;
        BoardPlayerPosGet(workPlayer->playerNo, &playerPos);
        workPlayer->pathMdlId = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 10), NULL, 0);
        motTime = BoardModelMotionMaxTimeGet(workPlayer->pathMdlId);
        BoardModelVisibilitySet(workPlayer->pathMdlId, 0);
        CoasterPlayerTimeInit(workPlayer);
        BoardModelMotionStart(workPlayer->pathMdlId, 0, 0);
        BoardModelMotionSpeedSet(workPlayer->pathMdlId, 0.0f);
        if (boardWork->hostSide == 0) {
            workPlayer->speed = -0.18f;
            BoardModelMotionTimeSet(workPlayer->pathMdlId, motTime);
        }
        else {
            workPlayer->speed = 0.18f;
            BoardModelMotionTimeSet(workPlayer->pathMdlId, 0.0f);
        }
        CoasterPlayerEndSet(workPlayer);
        work->playerNum++;
    }
    BoardCameraMoveSet(1);
    BoardCameraTargetModelSet(mapObjMdlId[MAPOBJ_COASTER]);
}

static void CoasterPlayerManKill(void)
{
    if (coasterPlayerManObj) {
        OM_GET_WORK_PTR(coasterPlayerManObj, CoasterPlayerManWork)->killF = 1;
    }
}

static void CoasterPlayerManUpdate(omObjData *obj)
{
    CoasterPlayerManWork *work = OM_GET_WORK_PTR(obj, CoasterPlayerManWork);
    CoasterPlayerWork *workPlayer;
    s32 i;

    if (work->killF != 0 || BoardIsKill()) {
        for (i = 0; i < work->playerNum; i++) {
            workPlayer = &work->player[i];
        }
        HuMemDirectFree(work->player);
        coasterPlayerManObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), obj);
        return;
    }
    if (coasterType == 0) {
        return;
    }
    for (i = 0; i < work->playerNum; i++) {
        workPlayer = &work->player[i];
        if (workPlayer->delay != 0) {
            workPlayer->delay--;
        }
        else {
            switch (workPlayer->mode) {
                case 0:
                    CoasterPlayerWait(workPlayer, obj);
                    break;
                case 1:
                    CoasterPlayerChaseBegin(workPlayer, obj);
                    break;
                case 2:
                    CoasterPlayerChasePathSet(workPlayer, obj);
                    break;
                case 3:
                    CoasterPlayerChase(workPlayer, obj);
                    break;
                case 4:
                    CoasterPlayerStop(workPlayer, obj);
                    break;
                case 5:
                    CoasterPlayerEnd(workPlayer, obj);
                    break;
            }
        }
    }
}

static void CoasterPlayerWait(CoasterPlayerWork *work, omObjData *obj)
{
    Vec mdlCoasterPos;
    Vec playerPos;
    Vec dir;

    if (work->time - coasterTime > 900.0f) {
        return;
    }
    BoardModelPosGet(mapObjMdlId[MAPOBJ_COASTER], &mdlCoasterPos);
    BoardPlayerPosGet(work->playerNo, &playerPos);
    VECSubtract(&mdlCoasterPos, &playerPos, &dir);
    BoardPlayerRotYSet(work->playerNo, atan2d(dir.x, dir.z));
    work->mode = 1;
}

static s32 coasterChaseSe[8] = { 0x00000123, 0x00000163, 0x000001A3, 0x000001E3, 0x00000223, 0x00000263, 0x000002A3, 0x000002E3 };

static void CoasterPlayerChaseBegin(CoasterPlayerWork *work, omObjData *obj)
{
    if (coasterChasePlayer == -1) {
        BoardCameraTargetPlayerSet(work->playerNo);
        coasterChasePlayer = work->playerNo;
    }
    HuAudFXPlay(coasterChaseSe[GWPlayer[work->playerNo].character]);
    BoardPlayerMotionStart(work->playerNo, 9, 0);
    BoardPlayerMotionSpeedSet(work->playerNo, 2.0f);
    work->delay = coasterPlayerChaseNum * 3 + 9;
    work->mode = 2;
    coasterPlayerChaseNum++;
    omVibrate(work->playerNo, 12, 4, 2);
}

static void CoasterPlayerChasePathSet(CoasterPlayerWork *work, omObjData *obj)
{
    ModelData *modelP;
    HsfObject *modelObj;
    Vec mdlCoasterPos;
    Vec dir;
    Vec objPos;
    float motTime;
    float time;
    s16 modelId;

    BoardPlayerPosGet(work->playerNo, &work->pos);
    BoardModelPosGet(mapObjMdlId[MAPOBJ_COASTER], &mdlCoasterPos);
    VECSubtract(&mdlCoasterPos, &work->pos, &dir);
    BoardPlayerRotYSet(work->playerNo, -atan2d(dir.x, dir.z));
    BoardPlayerMotionStart(work->playerNo, 3, HU3D_MOTATTR_LOOP);
    BoardPlayerMotionSpeedSet(work->playerNo, 2.0f);
    motTime = BoardModelMotionTimeGet(coasterPathMdlId);
    modelId = BoardModelIDGet(coasterPathMdlId);
    modelP = &Hu3DData[modelId];
    Hu3DMotionExec(modelId, modelP->unk_08, modelP->unk_64, 0);
    modelObj = Hu3DModelObjPtrGet(modelId, "looppath-cube1");
    objPos.x = modelObj->data.curr.pos.x;
    objPos.y = modelObj->data.curr.pos.y;
    objPos.z = modelObj->data.curr.pos.z;
    time = coasterTime;
    while (TRUE) {
        Hu3DMotionExec(modelId, modelP->unk_08, modelP->unk_64, 0);
        modelObj = Hu3DModelObjPtrGet(modelId, "looppath-cube1");
        dir.x = objPos.x - modelObj->data.curr.pos.x;
        dir.y = objPos.y - modelObj->data.curr.pos.y;
        dir.z = objPos.z - modelObj->data.curr.pos.z;
        time += VECMag(&dir);
        if (time >= work->time) {
            break;
        }
        objPos.x = modelObj->data.curr.pos.x;
        objPos.y = modelObj->data.curr.pos.y;
        objPos.z = modelObj->data.curr.pos.z;
        modelP->unk_64 += work->speed;
    }
    BoardModelMotionStart(work->pathMdlId, 0, 0);
    BoardModelMotionTimeSet(work->pathMdlId, modelP->unk_64);
    BoardModelMotionSpeedSet(work->pathMdlId, modelP->unk_68);
    work->mode = 3;
    BoardModelMotionTimeSet(coasterPathMdlId, motTime);
}

static void CoasterPlayerChase(CoasterPlayerWork *work, omObjData *obj)
{
    ModelData *modelP;
    HsfObject *modelObj;
    Vec *pos;
    Vec *target;
    Vec up;
    Vec rot;
    Vec objPos;
    Vec diff;
    Vec railPos;
    Vec spacePos;
    Mtx matrix;
    s16 modelId;

    modelId = BoardModelIDGet(work->pathMdlId);
    modelP = &Hu3DData[modelId];
    Hu3DMotionExec(modelId, modelP->unk_08, modelP->unk_64, 0);
    modelObj = Hu3DModelObjPtrGet(modelId, "looppath-cube1");
    objPos.x = modelObj->data.curr.pos.x;
    objPos.y = modelObj->data.curr.pos.y;
    objPos.z = modelObj->data.curr.pos.z;
    VECSubtract(&objPos, &work->pos, &diff);
    if (CoasterPlayerLoopCheck(work) != 0) {
        BoardModelPosGet(mapObjMdlId[MAPOBJ_COASTER_RAIL], &railPos);
        VECSubtract(&railPos, &objPos, &up);
        VECNormalize(&up, &up);
        pos = &work->pos;
        target = &objPos;
        BoardMTXCalcLookAt(matrix, target, &up, pos);
        MTXTranspose(matrix, work->matrix);
    }
    else {
        if (diff.z != 0.0f || diff.x != 0.0f) {
            rot.y = atan2d(diff.x, diff.z);
            rot.x = -atan2d(diff.y, VECMagXZ(&diff));
        }
        else {
            rot.x = rot.y = 0.0f;
        }
        MTXRotRad(matrix, 'x', MTXDegToRad(rot.x));
        MTXRotRad(work->matrix, 'y', MTXDegToRad(rot.y));
        MTXConcat(work->matrix, matrix, work->matrix);
    }
    BoardPlayerPosSetV(work->playerNo, &objPos);
    BoardPlayerRotSet(work->playerNo, 0.0f, 0.0f, 0.0f);
    BoardPlayerMtxSet(work->playerNo, &work->matrix);
    work->pos = objPos;
    BoardSpacePosGet(0, work->endSpace, &spacePos);
    if (BoardVecMaxDistXZCheck(&spacePos, &objPos, 200.0f)) {
        work->mode = 4;
    }
}

static void CoasterPlayerStop(CoasterPlayerWork *work, omObjData *obj)
{
    Vec spacePos;
    Vec playerPos;
    Vec dir;
    s32 spaceEnd;

    MTXIdentity(work->matrix);
    spaceEnd = BoardSpaceLinkFlagSearch(0, work->endSpace, 0x40);
    BoardSpacePosGet(0, spaceEnd, &spacePos);
    BoardPlayerPosGet(work->playerNo, &playerPos);
    BoardPlayerMtxSet(work->playerNo, &work->matrix);
    VECSubtract(&spacePos, &playerPos, &dir);
    BoardPlayerRotYSet(work->playerNo, atan2d(-dir.z, -dir.x));
    BoardPlayerPosLerpStart(work->playerNo, &playerPos, &spacePos, 20);
    work->mode = 5;
}

static void CoasterPlayerEnd(CoasterPlayerWork *work, omObjData *obj)
{
    s32 spaceEnd;

    if (!GWPlayer[work->playerNo].moving) {
        BoardPlayerIdleSet(work->playerNo);
        spaceEnd = BoardSpaceLinkFlagSearch(0, work->endSpace, 0x40);
        GWPlayer[work->playerNo].space_curr = spaceEnd;
        work->mode = -1;
        BoardPlayerMoveAwayStartCurr(spaceEnd, 0);
    }
}

static void CoasterPlayerEndSet(CoasterPlayerWork *work)
{
    BoardSpace *space;
    BoardSpace *linkSpace;
    Vec spacePos[2];
    Vec beginPos;
    float spaceDist[2];
    s16 spaceId[2];
    s32 j;
    s32 no;
    s32 i;

    for (no = i = 0; i < BoardSpaceCountGet(0); i++) {
        space = BoardSpaceGet(0, i + 1);
        for (j = 0; j < space->link_cnt; j++) {
            linkSpace = BoardSpaceGet(0, space->link[j]);
            if (linkSpace->flag & 0x40) {
                spaceId[no] = i + 1;
                BoardSpacePosGet(0, space->link[j], &spacePos[no]);
                no++;
            }
        }
        if (no >= 2) {
            break;
        }
    }
    if (boardWork->hostSide == 0) {
        BoardSpaceFlagPosGet(0, 0x1000, &beginPos);
    }
    else {
        BoardSpaceFlagPosGet(0, 0x2000, &beginPos);
    }
    for (i = 0; i < 2; i++) {
        spaceDist[i] = VECSquareDistance(&beginPos, &spacePos[i]);
    }
    if (spaceDist[0] < spaceDist[1]) {
        work->endSpace = spaceId[0];
    }
    else {
        work->endSpace = spaceId[1];
    }
}

static s32 CoasterPlayerLoopCheck(CoasterPlayerWork *arg0)
{
    Vec playerPos;
    s16 linkTbl[4];
    float sp8;
    s32 spaceId;
    s32 spaceIdLink;
    s32 spaceIdPrev;
    BoardSpace *space;
    BoardSpace *spaceLink;
    BoardSpace *spacePrev;

    BoardPlayerPosGet(arg0->playerNo, &playerPos);
    spacePrev = NULL;
    spaceIdPrev = -1;
    spaceId = coasterStartSpace;
    sp8 = 0.0f;
    while (TRUE) {
        space = BoardSpaceGet(1, spaceId);
        if (boardWork->hostSide == 0) {
            spaceIdLink = space->link[0];
        }
        else {
            BoardSpaceLinkTargetListGet(1, spaceId, linkTbl);
            spaceIdLink = linkTbl[0];
        }
        spaceLink = BoardSpaceGet(1, spaceIdLink);
        if (!spaceLink) {
            spaceLink = space;
            break;
        }
        if (BoardVecMaxDistXZCheck(&space->pos, &playerPos, 200.0f)) {
            if (BoardVecMaxDistXZCheck(&space->pos, &playerPos, 100.0f)) {
                break;
            }
            if (spacePrev) {
                space = spacePrev;
                break;
            }
            else {
                spacePrev = space;
            }
        }
        spaceIdPrev = spaceId;
        spaceId = spaceIdLink;
    }
    if (space->flag & 8) {
        return 1;
    }
    else {
        return 0;
    }
}

static void CoasterPlayerTimeInit(CoasterPlayerWork *work)
{
    HsfObject *modelObj;
    ModelData *modelP;
    Vec pos;
    Vec prevPos;
    Vec playerPos;
    Vec diff;
    float maxTime;
    float time;
    s16 modelId;

    maxTime = BoardModelMotionMaxTimeGet(work->pathMdlId);
    if (boardWork->hostSide == 0) {
        BoardModelMotionTimeSet(work->pathMdlId, maxTime);
        BoardModelMotionSpeedSet(work->pathMdlId, -0.18f);
    }
    else {
        BoardModelMotionTimeSet(work->pathMdlId, 0.0f);
        BoardModelMotionSpeedSet(work->pathMdlId, 0.18f);
    }
    BoardPlayerPosGet(work->playerNo, &playerPos);
    modelId = BoardModelIDGet(work->pathMdlId);
    modelP = &Hu3DData[modelId];
    Hu3DMotionExec(modelId, modelP->unk_08, modelP->unk_64, 0);
    modelObj = Hu3DModelObjPtrGet(modelId, "looppath-cube1");
    prevPos.x = modelObj->data.curr.pos.x;
    prevPos.y = modelObj->data.curr.pos.y;
    prevPos.z = modelObj->data.curr.pos.z;
    time = 0.0f;
    while (TRUE) {
        Hu3DMotionExec(modelId, modelP->unk_08, modelP->unk_64, 0);
        modelObj = Hu3DModelObjPtrGet(modelId, "looppath-cube1");
        pos.x = modelObj->data.curr.pos.x;
        pos.y = modelObj->data.curr.pos.y;
        pos.z = modelObj->data.curr.pos.z;
        VECSubtract(&pos, &prevPos, &diff);
        time += VECMag(&diff);
        if (BoardVecMinDistCheck(&playerPos, &pos, 150.0f)) {
            break;
        }
        prevPos = pos;
        modelP->unk_64 += modelP->unk_68;
    }
    work->time = time;
}

static void CoasterEffCreate(void)
{
    CoasterEffWork *work;
    CoasterEffData *data;
    s32 i;

    if (coasterEffObj) {
        return;
    }
    coasterEffObj = omAddObjEx(boardObjMan, 0x101, 1, 0, -1, CoasterEffUpdate);
    work = OM_GET_WORK_PTR(coasterEffObj, CoasterEffWork);
    work->killF = 0;
    work->data = HuMemDirectMallocNum(HEAP_SYSTEM, 20 * sizeof(CoasterEffData), MEMORY_DEFAULT_NUM);
    data = work->data;
    for (i = 0; i < 20; data++, i++) {
        data->time = -1;
        data->mdlId = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 7), NULL, 0);
        BoardModelVisibilitySet(data->mdlId, 0);
    }
}

static void CoasterEffKill(void)
{
    if (coasterEffObj) {
        OM_GET_WORK_PTR(coasterEffObj, CoasterEffWork)->killF = TRUE;
    }
}

static void CoasterEffUpdate(omObjData *obj)
{
    CoasterEffWork *work;
    s32 i;

    work = OM_GET_WORK_PTR(coasterEffObj, CoasterEffWork);
    if (work->killF != 0 || BoardIsKill()) {
        for (i = 0; i < 20; i++) {
            BoardModelKill(work->data[i].mdlId);
        }
        HuMemDirectFree(work->data);
        coasterEffObj = 0;
        omDelObjEx(HuPrcCurrentGet(), obj);
        return;
    }
    if (coasterTime < 10.0f) {
        return;
    }
    if (work->delay != 0) {
        work->delay--;
    }
    else {
        work->delay = 2;
        CoasterEffAdd(work);
    }
    CoasterEffModelUpdate(work);
}

static void CoasterEffAdd(CoasterEffWork *work)
{
    CoasterEffData *data;
    Mtx matrix;
    s32 i;
    s32 j;

    if (coasterLandF != 0) {
        MTXTrans(matrix, 0.0f, 50.0f, -100.0f);
    }
    else {
        MTXTrans(matrix, 0.0f, 70.0f, -100.0f);
    }
    MTXConcat(coasterMtx, matrix, matrix);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 20; j++) {
            data = &work->data[j];
            if (data->time == -1) {
                data->time = 10;
                Hu3DMtxTransGet(matrix, &data->pos);
                VECAdd(&coasterPos, &data->pos, &data->pos);
                data->vel.x = 0.0f;
                data->vel.y = 0.0f;
                data->vel.z = 0.001f;
                data->scale = 1.0f;
                BoardModelVisibilitySet(data->mdlId, 1);
                BoardModelLayerSet(data->mdlId, 2);
                BoardModelPosSetV(data->mdlId, &data->pos);
                break;
            }
        }
    }
}

static void CoasterEffModelUpdate(CoasterEffWork *work)
{
    CoasterEffData *data;
    s32 i;

    for (i = 0; i < 20; i++) {
        data = &work->data[i];
        if (data->time == -1) {
            continue;
        }
        data->time--;
        if (data->time == 0) {
            data->time = -1;
            BoardModelVisibilitySet(data->mdlId, 0);
        }
        else {
            if (data->time <= 3) {
                data->scale = sind(30.0f * data->time);
            }
            VECAdd(&data->pos, &data->vel, &data->pos);
            BoardModelMtxSet(data->mdlId, &coasterMtx);
            BoardModelPosSetV(data->mdlId, &data->pos);
            BoardModelScaleSet(data->mdlId, data->scale, data->scale, data->scale);
        }
    }
}

static void CoasterHostComKeySet(s32 playerNo)
{
    s32 starPos;
    s32 yesF;

    starPos = GWSystem.star_pos;
    yesF = 0;
    if (boardWork->hostSide != 0) {
        if (starPos == 0 || starPos == 1 || starPos == 7) {
            yesF = 0;
        }
        else {
            yesF = 1;
        }
    }
    else if (starPos == 0 || starPos == 1 || starPos == 7) {
        yesF = 1;
    }
    else {
        yesF = 0;
    }
    if (BoardPlayerCoinsGet(playerNo) < 5) {
        yesF = 0;
    }
    if (yesF != 0) {
        BoardComKeySetLeft();
    }
    else {
        BoardComKeySetRight();
    }
}