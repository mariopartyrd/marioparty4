#include "game/board/warp.h"
#include "game/audio.h"
#include "game/board/char_wheel.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/tutorial.h"
#include "game/wipe.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/objsub.h"
#include "game/disp.h"

#include "ext_math.h"

static void WarpInit(s32);
static void WarpLaunch(s32);
static void WarpStartImpact(s32);
static void WarpFall(s32);
static void WarpImpact(s32);

static Vec warpPos;

static s8 warpState;
static s8 warpTarget;
static s8 warpImpactCnt;
static s16 warpSpace;
static f32 warpYFloor;
static f32 warpYVel;
static Process* warpProcess;

static s16 warpSpringMdl = -1;
static s16 warpImpactMdl = -1;
static s8 warpImpactPlayer[4] = {-1, -1, -1, -1};

static void WarpProcess(void);
static void WarpKill(void);

void BoardWarpExec(s32 player, s32 space) {
    omVibrate(player, 12, 4, 2);
    warpProcess = HuPrcChildCreate(WarpProcess, 8195, 14336, 0, boardMainProc);
    HuPrcDestructorSet2(warpProcess, WarpKill);

    while (warpProcess != NULL) {
        HuPrcVSleep();
    }
    GWPlayer[player].color = 3;
}

void WarpProcess(void) {
    s32 curr_player;
    s32 warp_sound[8] = {291, 355, 419, 483, 547, 611, 675, 739};
    
    warpState = 0;
    curr_player = GWSystem.player_curr;
    HuAudFXPlay(842);
    BoardCameraViewSet(3);
    BoardCameraMotionWait();
    BoardPlayerMotBlendSet(curr_player, 0, 15);

    while (BoardPlayerMotBlendCheck(curr_player) == 0) {
        HuPrcVSleep();
    }
    
    BoardPlayerIdleSet(curr_player);
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        BoardTutorialHookExec(18, 0);
        boardTutorialData[0] = 0;
    }
    BoardCharWheelInit(curr_player, 3);
    BoardCharWheelSpeedSet(18.0f);
    BoardCharWheelWait();
    warpTarget = BoardCharWheelResultGet();
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    WarpInit(curr_player);

    while (1) {
        switch (warpState) {
            case 0:
                if (BoardModelMotionTimeGet(warpSpringMdl) < 15.0f) {
                    break;
                }
                BoardModelHookReset(warpSpringMdl);
                Hu3DModelObjPosGet(BoardModelIDGet(warpSpringMdl), "warp01", &warpPos);
                BoardSpacePosGet(0, GWPlayer[curr_player].space_curr, &warpPos);
                warpPos.y += 700.0f;
                BoardPlayerPosSetV(curr_player, &warpPos);
                warpState = 1;
                HuAudFXPlay(warp_sound[GWPlayer[curr_player].character]);
                break;
            case 1:
                WarpLaunch(curr_player);
                break;
            case 2:
                if (BoardModelMotionEndCheck(warpSpringMdl) == 0) break;
                warpState = 6;
                break;
            case 3:
                WarpStartImpact(curr_player);
                break;
            case 4:
                WarpFall(curr_player);
                break;
            case 5:
                WarpImpact(curr_player);
                break;
            case 6:
                HuPrcEnd();
                break;
        }
        HuPrcVSleep();
    }
}

void WarpKill(void) {
    if (warpSpringMdl != -1) {
        BoardModelKill(warpSpringMdl);
        warpSpringMdl = -1;
    }
    if (warpImpactMdl != -1) {
        BoardModelKill(warpImpactMdl);
        warpImpactMdl = -1;
    }
    warpProcess = NULL;
}

static void WarpInit(s32 player) {
    Vec pos;
    s16 player_mdl = BoardPlayerModelGet(player);

    warpSpringMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 1), NULL, 0);
    BoardSpacePosGet(0, GWPlayer[player].space_curr, &pos);
    warpYFloor = 1500.0f + pos.y;
    BoardModelLayerSet(warpSpringMdl, 2);
    BoardCameraTargetModelSet(warpSpringMdl);
    BoardModelMotionStart(warpSpringMdl, 0, 0);
    BoardModelHookSet(warpSpringMdl, "warp01", player_mdl);
    BoardModelPosSetV(warpSpringMdl, &pos);
    HuAudFXPlay(835);
    BoardPlayerRotYSet(player, 0.0f);
    BoardPlayerPosSet(player, 0.0f, 0.0f, 0.0f);
    BoardPlayerIdleSet(player);
}

static void WarpLaunch(s32 player) {

    warpPos.y += 20.0f;
    BoardPlayerPosSetV(player, &warpPos);
    if (!(warpPos.y < warpYFloor)) {
        WipeColorSet(0U, 0U, 0U);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
        
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        warpPos.y = warpYFloor;
        BoardModelVisibilitySet(warpSpringMdl, 0);
        warpState = 3;
    }
}

static void WarpStartImpact(s32 player) {
    s32 i;

    warpSpace = GWPlayer[warpTarget].space_curr;
    GWPlayer[player].space_curr = warpSpace;
    BoardSpacePosGet(0, warpSpace, &warpPos);
    warpYFloor = warpPos.y;
    warpPos.y += 1500.0f;
    BoardPlayerPosSetV(player, &warpPos);
    BoardPlayerRotSet(player, 180.0f, 180.0f, 0.0f);
    
    for (i = 0, warpImpactCnt = i; i < 4; i++) {
        if (warpSpace == GWPlayer[i].space_curr) {
            warpImpactPlayer[warpImpactCnt] = i;
            warpImpactCnt++;
        }
    }
    warpImpactMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 2), NULL, 0);
    BoardModelVisibilitySet(warpImpactMdl, 0);
    BoardModelMotionSpeedSet(warpImpactMdl, 0.0f);
    BoardCameraMoveSet(0);
    BoardCameraTargetSpaceSet(warpSpace);
    HuPrcSleep(1);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardCameraMoveSet(1);
    warpYVel = -10.0f;
    warpState = 4;
}

static void WarpFall(s32 player) {
    warpYVel += -2.0f;
    warpPos.y += warpYVel;
    if (warpPos.y <= (150.0f + warpYFloor)) {
        warpPos.y = warpYFloor;
        warpState = 5;
        HuAudFXPlay(837);
        HuAudFXPlay(829);
    }
    BoardPlayerPosSetV(player, &warpPos);
}

static void WarpImpact(s32 player) {
    Vec pos;
    Vec pos_player;
    s16 temp;
    f32 speed;
    f32 temp_f30;
    f32 angle;
    s16 i;

    pos.x = HU_DISP_CENTERX;
    pos.y = HU_DISP_CENTERY;
    pos.z = 700.0f;
    Hu3D2Dto3D(&pos, 1, &pos);
    BoardModelPosSetV(warpImpactMdl, &pos);
    BoardModelVisibilitySet(warpImpactMdl, 1);
    BoardModelMotionStart(warpImpactMdl, 0, 0x40000001);
    
    for (i = 0; i < warpImpactCnt; i++) {
        s16 player = warpImpactPlayer[i];
        omVibrate(player, 0xC, 4, 2);
        BoardPlayerMotionStart(player, 6, 0x40000001);
    }
    BoardPlayerRotSet(player, 0.0f, 0.0f, 0.0f);
    BoardPlayerPosGet(player, &pos_player);
    pos_player.y = warpYFloor;
    BoardPlayerPosSetV(player, &pos_player);
    speed = 4.0f;
    
    for (angle = 0.0f, temp = angle; angle < 180.0f; angle += speed) {
        temp_f30 = sind(angle);
        BoardModelScaleSet(warpImpactMdl, 0.5f + temp_f30, 0.5f + temp_f30, 0.5f + temp_f30);
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(warpImpactMdl, 0);
    HuPrcSleep(60);
    
    for (i = 0; i < warpImpactCnt; i++) {
        BoardPlayerIdleSet(warpImpactPlayer[i]);
    }
    warpState = 6;
}
