#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/audio.h"
#include "game/board/window.h"
#include "game/board/ui.h"
#include "game/hsfdraw.h"

#include "game/objsub.h"
#include "game/sprite.h"
#include "game/audio.h"
#include "game/wipe.h"
#include "game/gamework.h"

#include "ext_math.h"
#include "string.h"

#include <game/board/tutorial.h>
#include <game/chrman.h>
#include <game/hsfex.h>

typedef struct bowser_event_data {
    s16 sprite[3];
    s16 delay[3];
    s16 angle[3];
    s16 group;
    s16 model;
} BowserEventData;

static BowserEventData bowserEvent;
static Vec playerPosTemp[4];

static s32 scareFxTbl[] = {
    0x128,
    0x168,
    0x1A8,
    0x1E8,
    0x228,
    0x268,
    0x2A8,
    0x2E8
};


static s8 eventPlayer;
static s8 eventType;
static s16 eventSpace;
static s16 playerMot[4];
static s16 fireParMan;
static AnimData *fireAnim;
static char coinStealStrAll[8];
static char coinStealStr[8];
static omObjData *suitGiveObj;
static omObjData *miniBowserBalloonObj;
static omObjData *bowserEventObj;
static omObjData *miniBowserObj;
static omObjData *bowserObj;
static Process *bowserProc;

static s16 jumpMot = -1;
static s16 scareMot = -1;
static s16 suitItemMdl = -1;
static s16 bowserMdl = -1;

static void ExecBowser(void);
static void ExecBowserMain(void);
static void ExecMGReturn(void);
static void DestroyBowser(void);

static void SquishPlayers(void);
static void ExecBowserSpecial(void);
static void ExecBowserGame(void);
static void DoMGReturnEffect(void);
static void ExecBowserShuffle(void);
static void ExecBowserRevo(void);
static void ExecBowserSuit(void);

static s32 CheckSuitGive(void);
static void StartSuitGive(void);
static void SuitGiveMain(omObjData *object);

static void CreateBowserObj(void);
static void ExecBowserObj(omObjData *object);
static void SetBowserState(s32 state);
static s32 CheckBowserIdle(void);

static void CreateBowserEvent(void);
static s32 CheckBowserEvent(void);
static void StopBowserEvent(void);
static void ExecBowserEvent(omObjData *object);
static void ConfigBowserEvent(void);

static void CreateMiniBowser(void);
static s32 CheckMiniBowser(void);
static void ExecMiniBowser(omObjData *object);


static void CreatePlayerMot(void);
static void KillPlayerMot(void);

static void InitBowserFire(void);
static void KillBowserFire(void);

static s32 ExecMiniBowserEvent(void);

s32 BoardBowserExec(s32 player, s32 space)
{
    if(_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        HuAudFXPlay(841);
        BoardCameraViewSet(2);
        BoardPlayerMotBlendSet(player, 0, 15);
        while(!BoardPlayerMotBlendCheck(player)) {
            HuPrcVSleep();
        }
        BoardCameraMotionWait();
        BoardTutorialHookExec(12, 0);
        GWPlayer[player].color = 2;
    } else {
        eventPlayer = player;
        eventSpace = space;
        playerMot[0] = playerMot[1] = playerMot[2] = playerMot[3] = -1;
        bowserProc = HuPrcChildCreate(ExecBowser, 8196, 14336, 0, boardMainProc);
        HuPrcDestructorSet2(bowserProc, DestroyBowser);
        while(bowserProc) {
            HuPrcVSleep();
        }
        GWPlayer[player].color = 2;
    }
}

typedef struct bowser_work {
    u8 kill : 1;
    u8 state : 3;
    u8 mot_active : 1;
    u8 fall_done : 1;
    u8 jump_done : 1;
    u8 jump_state;
    u8 idle_timer;
} BowserWork;

typedef struct mini_bowser_work {
    u8 kill : 1;
    s16 group;
    s16 sprite;
    s16 angle;
} MiniBowserWork;

typedef struct bowser_event_work {
    u8 kill : 1;
    s8 state;
    s16 timer;
} BowserEventWork;

static void ExecBowser(void)
{
    #define BOWSER_EVENT 0
    #define MINI_BOWSER_EVENT 1

    s32 i;
    s32 status;
    if(!_CheckFlag(FLAG_ID_MAKE(1, 3))) {
        HuAudFXPlay(841);
        omVibrate(eventPlayer, 12, 4, 2);
        if(GWBoardGet() == BOARD_ID_MAIN6 && boardBowserHook) {
            boardBowserHook(1);
        }
        BoardAudSeqPause(0, 1, 1000);
        //20% of bowser, 80% chance of koopa kid
        if(BoardRandMod(100) < 20) {
            eventType = BOWSER_EVENT;
        } else {
            eventType = MINI_BOWSER_EVENT;
        }
    } else {
        BoardMusStart(1, 6, 127, 0);
    }
    status = BoardDataDirReadAsync(DATADIR_BKOOPA);
    BoardDataAsyncWait(status);
    CreatePlayerMot();
    if(!_CheckFlag(FLAG_ID_MAKE(1, 3))) {
        ExecBowserMain();
    } else {
        ExecMGReturn();
    }
    for(i=0; i<4; i++) {
        if(eventSpace == GWPlayer[i].space_curr) {
            BoardPlayerMotionSpeedSet(i, 1.0f);
        }
    }
    BoardAudSeqPause(0, 0, 1000);
    if(bowserObj) {
        OM_GET_WORK_PTR(bowserObj, BowserWork)->kill = 1;
    }
    if(miniBowserObj) {
        OM_GET_WORK_PTR(miniBowserObj, MiniBowserWork)->kill = 1;
    }
    if(bowserEventObj) {
        OM_GET_WORK_PTR(bowserEventObj, BowserEventWork)->kill = 1;
    }
    GWPlayer[eventPlayer].show_next = 1;
    BoardCameraMotionStartEx(-1, NULL, NULL, 2100.0f, -1.0f, 21);
    HuPrcSleep(30);
    for(i=0; i<4; i++) {
        BoardPlayerIdleSet(i);
    }
    BoardCameraMotionWait();
    if(GWBoardGet() == BOARD_ID_MAIN6 && boardBowserHook) {
        boardBowserHook(0);
    } else {
        HuPrcSleep(30);
    }
    HuPrcEnd();
}

static void ExecBowserMain(void)
{
    s32 result = 0;
    BoardPlayerMotBlendSet(eventPlayer, 0, 15);
    while(!BoardPlayerMotBlendCheck(eventPlayer)) {
        HuPrcVSleep();
    }
    BoardMusStart(1, 5, 127, 0);
    BoardCameraViewSet(3);
    BoardFilterFadeInit(30, 160);
    BoardCameraMotionWait();
    BoardPlayerMotionShiftSet(eventPlayer, jumpMot, 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    BoardPlayerMotionSpeedSet(eventPlayer, 2.0f);
    HuPrcSleep(120);
    ConfigBowserEvent();
    HuAudFXPlay(scareFxTbl[GWPlayer[eventPlayer].character]);
    BoardPlayerMotionShiftSet(eventPlayer, scareMot, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    CreateMiniBowser();
    while(!CheckMiniBowser()) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(eventPlayer);
    if(eventType) {
        result = ExecMiniBowserEvent();
        if(!result) {
            return;
        }
        BoardAudSeqFadeOut(1, 1000);
        BoardFilterFadeInit(30, 160);
        HuPrcSleep(30);
    }
    ExecBowserSpecial();
    BoardModelMotionShiftSet(bowserMdl, 3, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(8);
    HuAudFXPlay(58);
    BoardWinCreate(2, MAKE_MESSID(3, 11), 5);
    BoardWinWait();
    BoardWinKill();
    BoardAudSeqFadeOut(1, 1000);
    while(!BoardModelMotionEndCheck(bowserMdl)) {
        HuPrcVSleep();
    }
    SetBowserState(6);
    while(!CheckBowserIdle()) {
        HuPrcVSleep();
    }
    BoardFilterFadeOut(30);
}

static void ExecMGReturn(void)
{
    s32 i;
    s32 player;
    BoardStatusItemSet(1);
    for(i=0; i<4; i++) {
        BoardPlayerPosSetV(i, &playerPosTemp[i]);
    }
    BoardCameraMoveSet(0);
    BoardCameraTargetPlayerSet(eventPlayer);
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    CreateBowserObj();
    SquishPlayers();
    BoardPlayerMotBlendSet(eventPlayer, 0, 15);
    BoardCameraViewSet(3);
    BoardFilterFadeInit(30, 160);
    BoardStatusItemSet(0);
    BoardCameraMotionWait();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    while(WipeStatGet()) {
        HuPrcVSleep();
    }
    _ClearFlag(0x1001C);
    BoardCameraMoveSet(1);
    player = GWSystem.player_curr;
    GWSystem.player_curr = -1;
    DoMGReturnEffect();
    GWSystem.player_curr = player;
    BoardStatusShowSetAll(1);
    BoardModelMotionShiftSet(bowserMdl, 3, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(8);
    HuAudFXPlay(58);
    BoardWinCreate(2, MAKE_MESSID(3, 11), 5);
    BoardWinWait();
    BoardWinKill();
    while(!BoardStatusStopCheck(0)) {
        HuPrcVSleep();
    }
    BoardAudSeqFadeOut(1, 1000);
    while(!BoardModelMotionEndCheck(bowserMdl)) {
        HuPrcVSleep();
    }
    SetBowserState(6);
    while(!CheckBowserIdle()) {
        HuPrcVSleep();
    }
    BoardFilterFadeOut(30);
    BoardMusStartBoard();
}

static void DestroyBowser(void)
{
    KillPlayerMot();
    HuDataDirClose(DATADIR_BKOOPA);
    bowserProc = NULL;
}

static void SquishPlayers(void)
{
    Vec pos;
    Vec pos_space;
    s32 i;
    BoardPlayerPosGet(eventPlayer, &pos);
    if(!_CheckFlag(FLAG_ID_MAKE(1, 3))) {
        HuAudFXPlay(798);
    }
    pos.y += 6.0f;
    BoardPlayerPosSetV(eventPlayer, &pos);
    GWPlayer[eventPlayer].show_next = 0;
    BoardPlayerMotionSpeedSet(eventPlayer, 0.0f);
    for(i=0; i<4; i++) {
        if(eventSpace == GWPlayer[i].space_curr) {
            BoardPlayerPosGet(i, &pos);
            BoardSpacePosGet(0, eventSpace, &pos_space);
            pos.y = pos_space.y+2.5f;
            BoardPlayerPosSetV(i, &pos);
            BoardPlayerMotionStart(i, playerMot[i], 0);
            BoardPlayerMotionTimeSet(i, 50.0f);
            BoardPlayerMotionSpeedSet(i, 0.0f);
        }
    }
}

static void ExecBowserSpecial(void)
{
    s32 i;
    CreateBowserObj();
    while(!CheckBowserIdle()) {
        HuPrcVSleep();
    }
    SetBowserState(2);
    HuAudFXPlay(58);
    BoardMusStart(1, 6, 127, 0);
    HuPrcSleep(120);
    BoardWinCreate(2, MAKE_MESSID(3, 7), 5);
    BoardWinWait();
    BoardWinKill();
    HuAudFXPlay(857);
    BoardModelMotionShiftSet(bowserMdl, 4, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    for(i=0; i<4; i++) {
        omVibrate(i, 12, 12, 0);
    }
    HuPrcSleep(11);
    while(!BoardModelMotionEndCheck(bowserMdl)) {
        HuPrcVSleep();
    }
    CreateBowserEvent();
    HuAudFXPlay(831);
    HuAudFXPlay(60);
    while(!CheckBowserEvent()) {
        HuPrcVSleep();
    }
    HuPrcSleep(60);
    BoardModelAttrSet(bowserMdl, 0x40000004);
    while(!BoardModelMotionEndCheck(bowserMdl)) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(bowserMdl, 1, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    StopBowserEvent();
    switch(GWSystem.bowser_event) {
        case 0:
            ExecBowserGame();
            break;

        case 2:
            ExecBowserRevo();
            break;

        case 1:
            ExecBowserShuffle();
            break;

        case 3:
            ExecBowserSuit();
            break;
    }
}

static void ExecBowserGame(void)
{
    s32 i;
    s16 mgTbl[3] = {
        435,
        436,
        437
    };
    s32 messLoss[3] = {
        MAKE_MESSID(3, 9),
        MAKE_MESSID(3, 12),
        MAKE_MESSID(3, 14)
    };
    s32 mg;
    s32 mess;
    s32 fx_stat;
    for(i=0; i<4; i++) {
        BoardPlayerPosGet(i, &playerPosTemp[i]);
    }
    BoardWinCreate(2, MAKE_MESSID(3, 8), 5);
    BoardWinWait();
    mess = messLoss[GWSystem.bowser_loss];
    BoardWinCreate(2, mess, 5);
    BoardWinWait();
    BoardWinKill();
    BoardModelMotionShiftSet(bowserMdl, 5, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(8);
    while(BoardModelMotionTimeGet(bowserMdl) < 80.0f) {
        HuPrcVSleep();
    }
    fx_stat = HuAudFXPlay(846);
    InitBowserFire();
    while(BoardModelMotionTimeGet(bowserMdl) < 200.0f) {
        HuPrcVSleep();
    }
    BoardAudSeqFadeOut(1, 1000);
    BoardMusVolPanSet(0, 0, 1);
    BoardAudSeqPause(0, 0, 1);
    _SetFlag(0x1000E);
    HuAudFXFadeOut(fx_stat, 500);
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while(WipeStatGet()) {
        HuPrcVSleep();
    }
    HuAudFXAllStop();
    _SetFlag(0x1001C);
    KillBowserFire();
    HuPrcSleep(60);
    BoardModelMotionStart(bowserMdl, 1, 0);
    mg = (s16)mgTbl[BoardRandMod(3)];
    GWMGAvailSet(mg);
    GWSystem.mg_next = mg-401;
    _SetFlag(0x10003);
    BoardNextOvlSet(OVL_INST);
    BoardFilterFadeOut(30);
    HuPrcEnd();
}

static void DoMGReturnEffect(void)
{
    s32 messTbl[3] = {
        MAKE_MESSID(3, 10),
        MAKE_MESSID(3, 13),
        MAKE_MESSID(3, 15)
    };
    s32 player;
    s32 coin;
    s32 item;
    s32 delay;
    s32 item_cnt;
    s32 mess;
    s32 mess_char;
    for(player=0; player<4; player++) {
        if(GWPlayerCoinWinGet(player) == 1) { 
            break;
        }
    }
    mess = messTbl[GWSystem.bowser_loss];
    mess_char = BoardPlayerGetCharMess(player);
    BoardStatusShowSetForce(player);
    BoardStatusShowSet(player, 1);
    BoardWinCreate(2, mess, 5);
    BoardWinInsertMesSet(mess_char, 1);
    BoardWinWait();
    while(!BoardStatusStopCheck(player)) {
        HuPrcVSleep();
    }
    omVibrate(player, 12, 4, 2);
    if(GWSystem.bowser_loss == 2) {
        item_cnt = BoardPlayerItemCount(player);
        for(item=0; item<item_cnt; item++) {
            BoardPlayerItemRemove(player, 0);
            HuPrcSleep(30);
        }
    } else {
        coin = BoardPlayerCoinsGet(player);
        if(GWSystem.bowser_loss == 1) {
            coin = BoardPlayerCoinsGet(player)-(coin >> 1);
        }
        if(coin >= 50 ) {
            delay = 1;
        } else if(coin >= 20) {
            delay = 3;
        } else {
            delay = 6;
        }
        while(coin != 0 && BoardPlayerCoinsGet(player) != 0) {
            BoardPlayerCoinsAdd(player, -1);
            HuAudFXPlay(14);
            HuPrcSleep(delay);
            coin--;
        }
        HuAudFXPlay(15);
    }
    BoardStatusShowSet(player, 0);
    while(!BoardStatusStopCheck(player)) {
        HuPrcVSleep();
    }
}

static void ExecBowserShuffle(void)
{
    Vec pos;
    Vec target;
    s16 space_old[4];
    s16 space[4];
    s32 i;
    s32 player;
    s32 player_new;
    s32 reset_cam;
    BoardWinCreate(2, MAKE_MESSID(3, 16), 5);
    BoardWinWait();
    BoardWinKill();
    for(i=0; i<4; i++) {
        space_old[i] = GWPlayer[i].space_curr;
    }
    player=0;
    while(player<4) {
        player_new = BoardRandMod(4);
        if(player_new == player || space_old[player_new] == -1) {
            continue;
        }
        space[player] = space_old[player_new];
        space_old[player_new] = -1;
        player++;
    }
    HuAudFXPlay(857);
    BoardModelMotionShiftSet(bowserMdl, 4, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    while(!BoardModelMotionEndCheck(bowserMdl)) {
        HuPrcVSleep();
    }
    SetBowserState(3);
    HuPrcSleep(60);
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while(WipeStatGet()) {
        HuPrcVSleep();
    }
    reset_cam = 0;
    for(i=0; i<4; i++) {
        GWPlayer[i].space_curr = space[i];
        if(eventSpace == space[i]) {
            BoardPlayerMotionStart(i, playerMot[i], 0);
            BoardPlayerMotionTimeSet(i, 50.0f);
            BoardPlayerMotionSpeedSet(i, 0.0f);
            reset_cam = 1;
        } else {
            BoardPlayerIdleSet(i);
        }
        BoardPlayerMoveAwayStart(i, GWPlayer[i].space_curr, 1);
    }
    if(reset_cam) {
        BoardCameraTargetGet(&target);
        BoardCameraPosGet(&pos);
        BoardCameraTargetModelSet(-1);
        BoardCameraTargetSet(target.x, target.y, target.z);
        BoardCameraPosSet(pos.x, pos.y, pos.z);
    }
    SetBowserState(4);
    HuPrcSleep(60);
    BoardModelMotionStart(bowserMdl, 1, 0x40000001);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    while(WipeStatGet()) {
        HuPrcVSleep();
    }
}

static void ExecBowserRevo(void)
{
    s32 i;
    s32 coin;
    BoardWinCreate(2, MAKE_MESSID(3, 17), 5);
    BoardWinWait();
    BoardWinKill();
    for(coin=i=0; i<4; i++) {
        coin += BoardPlayerCoinsGet(i);
    }
    coin /= 4;
    HuAudFXPlay(857);
    BoardModelMotionShiftSet(bowserMdl, 4, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    while(!BoardModelMotionEndCheck(bowserMdl)) {
        HuPrcVSleep();
    }
    SetBowserState(3);
    HuPrcSleep(60);
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while(WipeStatGet()) {
        HuPrcVSleep();
    }
    SetBowserState(4);
    for(i=0; i<4; i++) {
        BoardPlayerCoinsSet(i, coin);
    }
    HuPrcSleep(60);
    BoardModelMotionStart(bowserMdl, 1, 0x40000001);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    while(WipeStatGet()) {
        HuPrcVSleep();
    }
}

static void ExecBowserSuit(void)
{
    BoardModelMotionShiftSet(bowserMdl, 1, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    BoardWinCreate(2, MAKE_MESSID(3, 18), 5);
    BoardWinWait();
    HuAudFXPlay(857);
    BoardModelMotionShiftSet(bowserMdl, 4, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(10);
    StartSuitGive();
    while(!CheckSuitGive()) {
        HuPrcVSleep();
    }
    BoardWinKill();
    BoardModelAttrSet(bowserMdl, 0x40000004);
    while(!BoardModelMotionEndCheck(bowserMdl)) {
        HuPrcVSleep();
    }
}

typedef struct suit_give_work {
    u8 kill : 1;
    u8 state;
    u8 timer;
    u8 idle_timer;
    s16 model;
} SuitGiveWork;

static s32 CheckSuitGive(void)
{
    if(!suitGiveObj) {
        return 1;
    } else {
        return 0;
    }
}

static void StartSuitGive(void)
{
    omObjData *object;
    SuitGiveWork *work;
    Vec pos;
    object = omAddObjEx(boardObjMan, 258, 0, 0, -1, SuitGiveMain);
    suitGiveObj = object;
    work = OM_GET_WORK_PTR(suitGiveObj, SuitGiveWork);
    work->kill = 0;
    work->state = 0;
    work->idle_timer = 0;
    work->timer = 30;
    work->model = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 120), NULL, 0);
    BoardModelLayerSet(work->model, 7);
    BoardModelScaleSet(work->model, 0.16f, 0.16f, 0.16f);
    object->trans.x = 288.0f;
    object->trans.y = -64.0f;
    pos.x = 288.0f;
    pos.y = 240.0f;
    object->rot.x = (pos.x-object->trans.x)/30.0f;
    object->rot.y = (pos.y-object->trans.y)/30.0f;
    object->scale.x = 300.0f;
    pos.x = object->trans.x;
    pos.y = object->trans.y;
    pos.z = object->scale.x;
    Hu3D2Dto3D(&pos, 1, &pos);
    BoardModelPosSetV(work->model, &pos);
}

static void SuitGiveMain(omObjData *object)
{
    SuitGiveWork *work = OM_GET_WORK_PTR(object, SuitGiveWork);
    s32 effect_active;
    Vec pos;
    if(work->kill || BoardIsKill()) {
        BoardModelKill(work->model);
        suitGiveObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }
    if(work->idle_timer) {
        work->idle_timer--;
        return;
    }

    effect_active = 0;
    switch(work->state) {
        case 0:
            if(work->timer == 0) {
                work->state = 1;
                work->idle_timer = 30;
                work->timer = 30;
                BoardStatusPosGet(eventPlayer, &pos);
                object->rot.x = (pos.x-object->trans.x)/30.0f;
                object->rot.y = (pos.y-object->trans.y)/30.0f;
            } else {
                work->timer--;
            }
            break;

        case 1:
            if(work->timer == 0) {
                work->state = 2;
                work->idle_timer = 6;
                effect_active = 1;
            } else {
                work->timer--;
            }
            break;

        case 2:
            BoardPlayerItemAdd(eventPlayer, 10);
            BoardModelVisibilitySet(work->model, 0);
            work->kill = 1;
            return;

        default:
            break;
    }
    object->trans.x += object->rot.x;
    object->trans.y += object->rot.y;
    pos.x = object->trans.x;
    pos.y = object->trans.y;
    pos.z = object->scale.x;
    Hu3D2Dto3D(&pos, 1, &pos);
    BoardModelPosSetV(work->model, &pos);
    if(effect_active) {
        CharModelLayerSetAll(6);
        CharModelEffectCreate(1, &pos);
    }
}

static const s32 bowserMotTbl[] = {
    DATA_MAKE_NUM(DATADIR_BKOOPA, 8),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 10),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 11),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 12),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 13),
    DATA_NUM_LISTEND
};

static void CreateBowserObj(void)
{
    BowserWork *work;
    Vec pos;
    bowserObj = omAddObjEx(boardObjMan, 257, 0, 0, -1, ExecBowserObj);
    work = OM_GET_WORK_PTR(bowserObj, BowserWork);
    work->kill = 0;
    work->jump_state = 0;
    work->idle_timer = 0;
    work->mot_active = 0;
    work->fall_done = 0;
    work->jump_done = 0;
    if(!_CheckFlag(FLAG_ID_MAKE(1, 3))) {
        work->state = 1;
    } else {
        work->state = 0;
    }
    bowserMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BKOOPA, 7), (s32 *)bowserMotTbl, 0);
    BoardModelVisibilitySet(bowserMdl, 0);
    BoardModelScaleSet(bowserMdl, 2.0f, 2.0f, 2.0f);
    BoardPlayerPosGet(eventPlayer, &pos);
    BoardModelLayerSet(bowserMdl, 2);
    bowserObj->trans.x = pos.x;
    bowserObj->trans.y = pos.y;
    bowserObj->trans.z = pos.z;
    if(!_CheckFlag(FLAG_ID_MAKE(1, 3))) {
        suitItemMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 99), NULL, 0);
        BoardModelLayerSet(suitItemMdl, 2);
        BoardModelVisibilitySet(suitItemMdl, 0);
    } else {
        s32 space = GWPlayer[eventPlayer].space_curr;
        BoardSpacePosGet(0, space, &pos);
        bowserObj->trans.x = pos.x;
        bowserObj->trans.y = pos.y;
        bowserObj->trans.z = pos.z;
        BoardModelPosSetV(bowserMdl, &pos);
        BoardCameraTargetSpaceSet(space);
        BoardModelMotionStart(bowserMdl, 1, 0x40000001);
        BoardModelVisibilitySet(bowserMdl, 1);
    }
}

static void ExecBowserFall(BowserWork *work, omObjData *object);
static void ExecBowserLaugh(BowserWork *work, omObjData *object);
static void ExecBowserPowerUp(BowserWork *work, omObjData *object);
static void ExecBowserFire(BowserWork *work, omObjData *object);
static void ExecBowserJump(BowserWork *work, omObjData *object);

static void ExecBowserObj(omObjData *object)
{
    BowserWork *work = OM_GET_WORK_PTR(bowserObj, BowserWork);
    Vec pos;
    Vec rot;

    if(work->kill || BoardIsKill()) {
        BoardModelKill(bowserMdl);
        bowserMdl = -1;
        BoardModelKill(suitItemMdl);
        suitItemMdl = -1;
        omDelObjEx(HuPrcCurrentGet(), object);
        bowserObj = NULL;
        return;
    }
    if(work->idle_timer) {
        work->idle_timer--;
        return;
    }
    if(work->mot_active && BoardModelMotionEndCheck(bowserMdl)) {
        work->mot_active = 0;
        BoardModelMotionShiftSet(bowserMdl, 1, 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    }
    switch(work->state) {
        case 1:
            ExecBowserFall(work, object);
            break;

        case 2:
            ExecBowserLaugh(work, object);
            break;

        case 3:
            ExecBowserPowerUp(work, object);
            break;

        case 5:
            ExecBowserFire(work, object);
            break;

        case 6:
            ExecBowserJump(work, object);
            break;

        case 4:
            BoardModelVisibilitySet(suitItemMdl, 0);
            work->state = 0;
            break;

        case 0:
            break;
    }
    BoardModelPosSet(bowserMdl, object->trans.x, object->trans.y, object->trans.z);
    BoardCameraRotGet(&rot);
    pos.x = object->trans.x+(-100.0f*sind(BoardModelRotYGet(bowserMdl)));
    pos.z = object->trans.z+(-100.0f*cosd(BoardModelRotYGet(bowserMdl)));
    pos.y = object->trans.y+250.0f;
    BoardModelPosSetV(suitItemMdl, &pos);
}

static void ExecBowserFall(BowserWork *work, omObjData *object)
{
    Vec pos;
    Vec pos_space;
    Vec pos_player;
    s32 i;
    if(!work->jump_state) {
        BoardModelVisibilitySet(bowserMdl, 1);
        BoardModelMotionStart(bowserMdl, 2, 0);
        BoardModelMotionTimeSet(bowserMdl, 100.0f);
        work->jump_state = 1;
        return;
    }
    if(BoardModelMotionEndCheck(bowserMdl)) {
        work->state = 0;
        BoardModelMotionShiftSet(bowserMdl, 1, 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
        return;
    }
    if(!work->fall_done && !(BoardModelMotionTimeGet(bowserMdl) < 140.0f)) {
        BoardPlayerPosGet(eventPlayer, &pos);
        HuAudFXPlay(829);
        BoardCameraQuakeSet(60, 100.0f);
        object->trans.y = pos.y;
        BoardPlayerPosGet(eventPlayer, &pos_player);
        if(!_CheckFlag(FLAG_ID_MAKE(1, 3))) {
            HuAudFXPlay(798);
        }
        pos_player.y += 6.0f;
        BoardPlayerPosSetV(eventPlayer, &pos_player);
        GWPlayer[eventPlayer].show_next = 0;
        BoardPlayerMotionSpeedSet(eventPlayer, 0.0f);
        for(i=0; i<4; i++) {
            if(eventSpace != GWPlayer[i].space_curr) {
                continue;
            }
            BoardPlayerPosGet(i, &pos_player);
            BoardSpacePosGet(0, eventSpace, &pos_space);
            pos_player.y = 2.5f+pos_space.y;
            BoardPlayerPosSetV(i, &pos_player);
            BoardPlayerMotionStart(i, playerMot[i], 0);
            BoardPlayerMotionTimeSet(i, 50.0f);
            BoardPlayerMotionSpeedSet(i, 0.0f);
        }
        if(!work->fall_done) {
            work->fall_done = 1;
            omVibrate(eventPlayer, 12, 4, 2);
        }
    }

}

static void ExecBowserLaugh(BowserWork *work, omObjData *object)
{
    BoardModelMotionStart(bowserMdl, 3, 0);
    work->mot_active = 1;
    work->state = 0;
}

static void ExecBowserFire(BowserWork *work, omObjData *object)
{
    BoardModelMotionStart(bowserMdl, 5, 0);
    work->state = 0;
}

static void ExecBowserJump(BowserWork *work, omObjData *object)
{
    switch(work->jump_state) {
        case 0:
            BoardModelMotionShiftSet(bowserMdl, 2, 0.0f, 4.0f, HU3D_MOTATTR_NONE);
            work->jump_state = 1;
            break;

        case 1:
        {
            s16 model_id = BoardModelIDGet(bowserMdl);
            if(Hu3DMotionShiftIDGet(model_id) == -1) {
                work->jump_state = 2;
            }
        }
            break;

        case 2:
        {
            float time = BoardModelMotionTimeGet(bowserMdl);
            if(time < 60.0f) {
                break;
            }
            if(!work->jump_done) {
                omVibrate(eventPlayer, 12, 12, 0);
                HuAudFXPlay(61);
                work->jump_done = 1;
            }
            if(time >= 100.0f) {
                BoardModelVisibilitySet(bowserMdl, 0);
                work->state = 0;
                work->kill = 1;
            }
        }
            break;
    }
}

static void ExecBowserPowerUp(BowserWork *work, omObjData *object)
{
    Vec pos;
    if(work->jump_state == 0) {
        BoardModelVisibilitySet(suitItemMdl, 1);
        BoardModelMotionStart(suitItemMdl, 0, 0);
        BoardModelScaleSet(suitItemMdl, 10.0f, 10.0f, 10.0f);
        pos.x = object->trans.x+(-100.0f*sind(BoardModelRotYGet(bowserMdl)));
        pos.z = object->trans.z+(-100.0f*cosd(BoardModelRotYGet(bowserMdl)));
        pos.y = object->trans.y+250.0f;
        BoardModelPosSetV(suitItemMdl, &pos);
        HuAudFXPlay(850);
    } else {
        if(work->jump_state >= 100) {
            work->state = 0;
        }
    }
    work->jump_state++;
}

static void SetBowserState(s32 state)
{
    BowserWork *work = OM_GET_WORK_PTR(bowserObj, BowserWork);
    work->state = state;
    work->jump_state = 0;
}

static s32 CheckBowserIdle(void)
{
    BowserWork *work;
    if(!bowserObj) {
        return 1;
    }
    work = OM_GET_WORK_PTR(bowserObj, BowserWork);
    if(work->state != 0 || work->idle_timer != 0) {
        return 0;
    } else {
        return 1;
    }
}

static void CreateMiniBowser(void)
{
    omObjData *object;
    MiniBowserWork *work;
    object = omAddObjEx(boardObjMan, 257, 0, 0, -1, ExecMiniBowser);
    miniBowserObj = object;
    work = OM_GET_WORK_PTR(object, MiniBowserWork);
    work->kill = 0;
    work->angle = 0;
    work->group = HuSprGrpCreate(1);
    BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BKOOPA, 5), 100, NULL, &work->sprite);
    HuSprGrpMemberSet(work->group, 0, work->sprite);
    HuSprAttrSet(work->group, 0, HUSPR_ATTR_LINEAR);
    HuSprGrpPosSet(work->group, 288.0f, 240.0f);
    HuSprGrpScaleSet(work->group, 4.0f, 4.0f);
}

static s32 CheckMiniBowser(void)
{
    if(miniBowserObj) {
        return 0;
    } else {
        return 1;
    }
}

static void ExecMiniBowser(omObjData *object)
{
    MiniBowserWork *work = OM_GET_WORK_PTR(object, MiniBowserWork);
    float alpha;
    if(work->kill || BoardIsKill()) {
        HuSprGrpKill(work->group);
        miniBowserObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }
    OSs16tof32(&work->angle, &alpha);
    alpha = sind(BoardDAngleCalc(alpha));
    HuSprTPLvlSet(work->group, 0, ABS(alpha));
    if(work->angle == 60) {
        HuAudFXPlay(807);
    }
    work->angle += 2;
    if(work->angle == 90 || work->angle == 270 || work->angle == 450) {
        omVibrate(eventPlayer, 12, 4, 2);
    }
    if(work->angle >= 540) {
        work->kill =  1;
    }
}

static void CreateBowserEvent(void)
{
    Vec pos_2d;
    Vec pos_3d;
    s32 eventSpr[] = {
        DATA_MAKE_NUM(DATADIR_BKOOPA, 1),
        DATA_MAKE_NUM(DATADIR_BKOOPA, 2),
        DATA_MAKE_NUM(DATADIR_BKOOPA, 3),
        DATA_MAKE_NUM(DATADIR_BKOOPA, 4),
    };


    BowserEventData *data;
    s32 i;
    BowserEventWork *work;
    s32 sprite;
    bowserEventObj = omAddObjEx(boardObjMan, 257, 0, 0, -1, ExecBowserEvent);
    work = OM_GET_WORK_PTR(bowserEventObj, BowserEventWork);
    work->kill = 0;
    work->state = 0;
    work->timer = 0;
    memset(&bowserEvent, 0, sizeof(BowserEventData));
    data = &bowserEvent;
    data->group = HuSprGrpCreate(3);
    sprite = eventSpr[GWSystem.bowser_event];
    for(i=0; i<3; i++) {
        BoardSpriteCreate(sprite, 100, NULL, &data->sprite[i]);
        HuSprGrpMemberSet(data->group, i, data->sprite[i]);
        HuSprTPLvlSet(data->group, i, 0.0f);
        HuSprPosSet(data->group, i, 0.0f, 0.0f);
        data->delay[i] = i*2;
    }
    HuSprGrpPosSet(data->group, 288.0f, 240.0f);
    data->model = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 101), NULL, 0);
    pos_2d.x = 288.0f;
    pos_2d.y = 240.0f;
    pos_2d.z = 1000.0f;
    Hu3D2Dto3D(&pos_2d, 1, &pos_3d);
    BoardModelMotionStart(data->model, 0, 0x40000001);
    BoardModelPosSetV(data->model, &pos_3d);
    BoardModelLayerSet(data->model, 2);
}

static s32 CheckBowserEvent(void)
{
    BowserEventWork *work = OM_GET_WORK_PTR(bowserEventObj, BowserEventWork);

    if(work->state != 2) {
        return 0;
    } else {
        return 1;
    }
}

static void StopBowserEvent(void)
{
    BowserEventWork *work = OM_GET_WORK_PTR(bowserEventObj, BowserEventWork);
    work->state = 1;
}

static void ShowBowserEvent(BowserEventWork *work, omObjData *object);
static void HideBowserEvent(BowserEventWork *work, omObjData *object);

static void ExecBowserEvent(omObjData *object)
{
    BowserEventWork *work = OM_GET_WORK_PTR(object, BowserEventWork);
    BowserEventData *data = &bowserEvent;
    if(work->kill || BoardIsKill()) {
        HuSprGrpKill(data->group);
        BoardModelKill(data->model);
        bowserEventObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }
    if(work->timer) {
        work->timer--;
        return;
    }
    switch(work->state) {
        case 0:
            ShowBowserEvent(work, object);
            break;

        case 1:
            HideBowserEvent(work, object);
            break;

        case 2:
            break;
    }
}

static void ShowBowserEvent(BowserEventWork *work, omObjData *object)
{
    BowserEventData *data;
    s32 i;
    s32 count;
    float angle;
    float tplvl;
    float scale;
    data = &bowserEvent;
    for(count=i=0; i<3; i++) {
        if(data->delay[i]) {
            data->delay[i]--;
        } else {
            if(data->angle[i] > 90) {
                count++;
                continue;
            }
            OSs16tof32(&data->angle[i], &angle);
            tplvl = sind(angle);
            scale = sind(angle);
            HuSprTPLvlSet(data->group, i, tplvl);
            HuSprScaleSet(data->group, i, scale, scale);
            BoardModelAlphaSet(data->model, 255.0f*tplvl);
            data->angle[i] += 9;
            if(data->angle[i] > 90 && i != 0) {
                HuSprAttrSet(data->group, i, HUSPR_ATTR_DISPOFF);
            }
        }
    }
    if(count == 3) {
        work->state = 2;
        work->timer = 60;
    }
}

static void HideBowserEvent(BowserEventWork *work, omObjData *object)
{
    BowserEventData *data = &bowserEvent;
    float angle;
    float tplvl;
    OSs16tof32(&data->angle[0], &angle);
    tplvl = sind(angle);
    HuSprTPLvlSet(data->group, 0, tplvl);
    BoardModelAlphaSet(data->model, 255.0f*tplvl);
    data->angle[0] -= 10;
    if(data->angle[0] < 0) {
        work->kill = 1;
        HuSprAttrSet(data->group, 0, HUSPR_ATTR_DISPOFF);
    }
}


static void ConfigBowserEvent(void)
{
    s32 i;
    s32 chance;
    s32 coins;
    s32 item_full;
    item_full = 0;
    if(BoardPlayerItemCount(eventPlayer) == 3) {
        item_full = 1;
    }
    for(coins=i=0; i<4; i++) {
        coins += BoardPlayerCoinsGet(i);
    }
    while(1) {
        chance = BoardRandMod(100);
        if(chance >= 95) {
            if(item_full) {
                continue;
            }
            if(GWSystem.max_turn-GWSystem.turn == 0) {
                continue;
            }
            GWSystem.bowser_event = 3;
            break;
        } else if(chance >= 85) {
            GWSystem.bowser_event = 2;
            break;
        } else if(chance >= 70) {
            GWSystem.bowser_event = 1;
            break;
        } else {
            if(coins == 0) {
                continue;
            }
            GWSystem.bowser_event = 0;
            GWSystem.bowser_loss = BoardRandMod(3);
            break;
        }
    }
}

static void CreatePlayerMot(void)
{
    s32 scareMotTbl[] = {
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 27),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 27),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 27),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 27),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 27),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 27),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 27),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 27),
    };
    s32 jumpMotTbl[] = {
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 26),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 26),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 26),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 26),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 26),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 26),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 26),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 26),
    };
    s32 playerMotTbl[] = {
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 31),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 31),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 31),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 31),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 31),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 31),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 31),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 31),
    };
    s32 i;
    s32 character;
    character = GWPlayer[eventPlayer].character;
    scareMot = BoardPlayerMotionCreate(eventPlayer, scareMotTbl[character]);
    jumpMot = BoardPlayerMotionCreate(eventPlayer, jumpMotTbl[character]);
    for(i=0; i<4; i++) {
        character = GWPlayer[i].character;
        playerMot[i] = BoardPlayerMotionCreate(i, playerMotTbl[character]);
    }
}

static void KillPlayerMot(void)
{
    s32 i;
    if(scareMot > 0) {
        BoardPlayerMotionKill(eventPlayer, scareMot);
        scareMot = -1;
    }
    if(jumpMot > 0) {
        BoardPlayerMotionKill(eventPlayer, jumpMot);
        jumpMot = -1;
    }
    for(i=0; i<4; i++) {
        if(playerMot[i] > 0) {
            BoardPlayerMotionKill(i, playerMot[i]);
            playerMot[i] = -1;
        }
    }
}

static void BowserFireHook(ModelData *model, ParticleData *particle, Mtx matrix);

static void SpawnBowserFire(HsfanimStruct01 *arg0);
static s32 CheckBowserFire(HsfanimStruct01 *arg0);

static void InitBowserFire(void)
{
    fireAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_BOARD, 106));
    fireParMan = Hu3DParticleCreate(fireAnim, 30);
    Hu3DParticleColSet(fireParMan, 255, 255, 255);
    Hu3DParticleScaleSet(fireParMan, 10.0f);
    Hu3DParticleHookSet(fireParMan, BowserFireHook);
    Hu3DParticleBlendModeSet(fireParMan, 1);
    Hu3DModelLayerSet(fireParMan, 2);
}

static void BowserFireHook(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01* var_r30;
    s32 i;
    s32 var_r28;
    Vec pos;
    Hu3DModelObjPosGet(BoardModelIDGet(bowserMdl), "itemhook_M_1", &pos);
    if (particle->unk_34 == 0) {
        var_r30 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r30++) {
            var_r30->unk2C = 0.0f;
        }
        particle->unk_34 = 1;
        particle->unk_00 = 0;
    }
    if((particle->unk_34 & 0x3) == 0) {
        var_r30 = particle->unk_48;
        for(var_r28=0; var_r28<particle->unk_30; var_r28++, var_r30++) {
             if(var_r30->unk2C == 0.0f) {
                break; 
             }
        }
        if(var_r28 != particle->unk_30) {
            var_r30->unk34 = pos;
            particle->unk_00++;
            SpawnBowserFire(var_r30);
        }
    }
    var_r30 = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, var_r30++) {
        if(var_r30->unk2C != 0.0f && CheckBowserFire(var_r30)) {
            particle->unk_00--;
        }
    }
}

static void SpawnBowserFire(HsfanimStruct01 *arg0)
{
    Vec dir;
    BoardCameraDirGet(&dir);
    arg0->unk08.x = 0.0f;
    arg0->unk08.y = 0.0f;
    arg0->unk08.z = 0.0f;
    arg0->unk14.x = -dir.x*((0.5f*BoardRandFloat())+0.5f);
    arg0->unk14.y = -dir.y*((0.5f*BoardRandFloat())+0.5f);
    arg0->unk14.z = -dir.z*((0.5f*BoardRandFloat())+0.5f);
    arg0->unk24 = 1.025f;
    arg0->unk40.a = 254;
    arg0->unk40.r = 255;
    arg0->unk40.g = 255;
    arg0->unk40.b = 255;
    arg0->unk2C = 100.0f;
}

static s32 CheckBowserFire(HsfanimStruct01 *arg0)
{
    arg0->unk34.x += arg0->unk08.x;
    arg0->unk34.y += arg0->unk08.y;
    arg0->unk34.z += arg0->unk08.z;
    arg0->unk08.x += arg0->unk14.x;
    arg0->unk08.y += arg0->unk14.y;
    arg0->unk08.z += arg0->unk14.z;
    arg0->unk40.a -= 8;
    arg0->unk2C *= arg0->unk24;
    if(arg0->unk40.a == 0.0f) {
        arg0->unk40.a = 0;
        arg0->unk2C = 0.0f;
        return 1;
    }
    return 0;
}

static void KillBowserFire(void)
{
    if(fireParMan != -1) {
        Hu3DModelKill(fireParMan);
        fireParMan = -1;
        fireAnim = NULL;
    }
}

typedef struct mini_bowser_balloon_work {
    u8 kill : 1;
    u8 state;
    u16 timer;
    s16 angle;
    float offset;
    s16 *models;
} MiniBowserBalloonWork;

static void MiniBowserTake(void);
static void MiniBowserTakeAll(void);
static void MiniBowserBalloonStop(void);

static s32 GetMiniBowserBalloonState(void);
static void SetMiniBowserBalloonState(s32 state);
static void CreateMiniBowserBalloon(void);

static void ExecMiniBowserBalloon(omObjData *object);
static void MiniBowserBalloonHover(MiniBowserBalloonWork *work, omObjData *object);
static void MiniBowserBalloonFall(MiniBowserBalloonWork *work, omObjData *object);
static void MiniBowserBalloonRaise(MiniBowserBalloonWork *work, omObjData *object);


static void SetMiniBowserMotion(s32 mot, u8 end, s32 pause);
static void SetMiniBowserMotionPause(s32 flag);
static void WaitMiniBowserMotion(void);

static s32 ExecMiniBowserEvent(void)
{
    s32 doneF = 0;
    CreateMiniBowserBalloon();
    SetMiniBowserBalloonState(0);
    while(GetMiniBowserBalloonState() != 2) {
        HuPrcVSleep();
    }
    BoardFilterFadeOut(30);
    BoardAudSeqFadeOut(1, 1000);
    HuPrcSleep(30);
    BoardAudSeqFadeOutFast(1);
    BoardMusStart(1, 11, 127, 0);
    HuAudFXPlay(62);
    BoardWinCreate(2, MAKE_MESSID(3, 0), 6);
    BoardWinWait();
    if(BoardRandMod(100) < 70) {
        MiniBowserTake();
    } else {
        MiniBowserTakeAll();
    }
    //5% chance bowser will appear after baby bowser
    if(BoardRandMod(100) < 5) {
        doneF = 1;
    }
    if(doneF) {
        HuPrcSleep(60);
        BoardWinCreate(2, MAKE_MESSID(3, 6), 6);
        BoardWinWait();
        BoardWinKill();
        HuAudFXPlay(62);
        SetMiniBowserMotion(6, 10, 1);
        HuPrcSleep(60);
    } else {
        HuAudFXPlay(62);
        BoardWinCreate(2, MAKE_MESSID(3, 2), 6);
        BoardWinWait();
        BoardWinKill();
        BoardAudSeqFadeOut(1, 1000);
        SetMiniBowserMotion(4, 10, 1);
        HuPrcSleep(30);
    }
    SetMiniBowserBalloonState(1);
    while(GetMiniBowserBalloonState() != 2) {
        HuPrcVSleep();
    }
    MiniBowserBalloonStop();
    return doneF;
}

static void MiniBowserTake(void)
{
    u8 coinSteal[][3] = {
        20, 20, 30,
        20, 20, 30,
        10, 15, 20,
        10, 15, 20
    };
    s32 coin_inc;
    s32 game_part;
    u8 steal;
    s32 i;
    u32 mess;
    s32 delay;
    s32 turn;
    s32 turn_max;
    turn = GWSystem.turn-1;
    turn_max = GWSystem.max_turn;
    game_part = turn/(turn_max/3);
    if(game_part >= 3) {
        game_part = 2;
    }
    steal = (u8)coinSteal[GWPlayer[eventPlayer].rank][game_part];
    sprintf(coinStealStrAll, "%d", steal);
    SetMiniBowserMotion(2, 10, 0);
    if(steal >= 20) {
        delay = 3;
    } else {
        delay = 6;
    }
    if(BoardPlayerCoinsGet(eventPlayer) != 0) {
        mess = MAKE_MESSID(3, 1);
        coin_inc = -1;
    } else {
        mess = MAKE_MESSID(3, 3);
        steal = 10;
        coin_inc = 1;
    }
    HuAudFXPlay(62);
    BoardWinCreate(2, mess, 6);
    BoardWinInsertMesSet(MAKE_MESSID_PTR(coinStealStrAll), 0);
    BoardWinWait();
    if(coin_inc > 0) {
        SetMiniBowserMotion(5, 10, 0);
    } else {
        SetMiniBowserMotion(3, 10, 1);
    }
    if(coin_inc < 0) {
        omVibrate(eventPlayer, 12, 6, 6);
    }
    if(coin_inc < 0) {
        BoardPlayerMotionShiftSet(eventPlayer, 13, 0.0f, 4.0f, HU3D_MOTATTR_NONE);
    } else {
        BoardPlayerMotionShiftSet(eventPlayer, 12, 0.0f, 4.0f, HU3D_MOTATTR_NONE);
    }
    for(i=0; i<steal; i++) {
        BoardPlayerCoinsAdd(eventPlayer, coin_inc);
        if(coin_inc < 0) {
            HuAudFXPlay(14);
        } else {
            HuAudFXPlay(7);
        }
        HuPrcSleep(6);
        if(BoardPlayerCoinsGet(eventPlayer) <= 0) {
            break;
        }
    }
    HuAudFXPlay(15);
    HuPrcSleep(20);
    BoardPlayerIdleSet(eventPlayer);
    SetMiniBowserMotionPause(0);
    WaitMiniBowserMotion();
    SetMiniBowserMotion(1, 10, 1);
}

static void MiniBowserTakeAll(void)
{
    u8 coinSteal[] = {
        10, 20, 30,
    };
    s32 i;
    s32 j;
    s32 coin_total;
    s32 coin_inc;
    s32 game_part;
    u8 steal;
    u32 mess;
    s32 delay;
    s32 turn;
    s32 turn_max;
    turn = GWSystem.turn-1;
    turn_max = GWSystem.max_turn;
    game_part = turn/(turn_max/3);
    if(game_part >= 3) {
        game_part = 2;
    }
    steal = (u8)coinSteal[game_part];
    sprintf(coinStealStr, "%d", steal);
    SetMiniBowserMotion(2, 10, 0);
    for(coin_total=j=0; j<4; j++) {
        coin_total += BoardPlayerCoinsGet(j);
    }
    if(coin_total != 0) {
        mess = MAKE_MESSID(3, 4);
        coin_inc = -1;
    } else {
        mess = MAKE_MESSID(3, 5);
        steal = 10;
        coin_inc = 1;
    }
    HuAudFXPlay(62);
    BoardWinCreate(2, mess, 6);
    BoardWinInsertMesSet(MAKE_MESSID_PTR(coinStealStr), 0);
    BoardWinWait();
    if(coin_inc > 0) {
        SetMiniBowserMotion(5, 10, 0);
    } else {
        SetMiniBowserMotion(3, 10, 1);
    }
    if(coin_inc < 0) {
        for(i=0; i<4; i++) {
            omVibrate(i, 12, 6, 6);
        }
    }
    for(i=0; i<4; i++) {
        if(coin_inc < 0) {
            BoardPlayerMotionShiftSet(i, 13, 0.0f, 4.0f, HU3D_MOTATTR_NONE);
        } else {
            BoardPlayerMotionShiftSet(i, 12, 0.0f, 4.0f, HU3D_MOTATTR_NONE);
        }
    }
    if(steal >= 20) {
        delay = 3;
    } else {
        delay = 6;
    }
    for(i=0; i<steal; i++) {
        for(j=0; j<4; j++) {
            BoardPlayerCoinsAdd(j, coin_inc);
        }
        for(coin_total=j=0; j<4; j++) {
            coin_total += BoardPlayerCoinsGet(j);
        }
        if(coin_total == 0) {
            break;
        }
        if(coin_inc < 0) {
            HuAudFXPlay(14);
        } else {
            HuAudFXPlay(7);
        }
        HuPrcSleep(6);
    }
    HuAudFXPlay(15);
    HuPrcSleep(20);
    for(i=0; i<4; i++) {
        BoardPlayerIdleSet(i);
    }

    SetMiniBowserMotionPause(0);
    WaitMiniBowserMotion();
    SetMiniBowserMotion(1, 10, 1);
}

static const s32 miniBowserMotTbl[] = {
    DATA_MAKE_NUM(DATADIR_BKOOPA, 15),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 16),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 17),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 18),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 19),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 20),
    DATA_NUM_LISTEND
};

static void MiniBowserBalloonStop(void)
{
    if(miniBowserBalloonObj) {
        OM_GET_WORK_PTR(miniBowserBalloonObj, MiniBowserBalloonWork)->kill = 1;
    }
}

static s32 GetMiniBowserBalloonState(void)
{
    return OM_GET_WORK_PTR(miniBowserBalloonObj, MiniBowserBalloonWork)->state;
}

static void SetMiniBowserBalloonState(s32 state)
{
    OM_GET_WORK_PTR(miniBowserBalloonObj, MiniBowserBalloonWork)->state = state;
}

static void CreateMiniBowserBalloon(void)
{
    MiniBowserBalloonWork *work;
    s16 *models;
    Vec pos;
    miniBowserBalloonObj = omAddObjEx(boardObjMan, 257, 0, 0, -1, ExecMiniBowserBalloon);
    work = OM_GET_WORK_PTR(miniBowserBalloonObj, MiniBowserBalloonWork);
    work->kill = 0;
    work->state = 0;
    work->timer = 0;
    work->offset = 0;
    work->angle = 0;
    work->models = HuMemDirectMallocNum(HEAP_SYSTEM, 9*sizeof(s16), MEMORY_DEFAULT_NUM);
    models = work->models;
    models[0] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BKOOPA, 14), (s32 *)miniBowserMotTbl, 0);
    models[1] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BKOOPA, 0), NULL, 0);
    BoardPlayerPosGet(eventPlayer, &pos);
    miniBowserBalloonObj->trans.x = pos.x;
    miniBowserBalloonObj->trans.y = pos.y+800.0f;
    miniBowserBalloonObj->trans.z = pos.z;
    BoardModelHookSet(models[1], "minik01", models[0]);
    BoardModelPosSet(models[1], miniBowserBalloonObj->trans.x,
        miniBowserBalloonObj->trans.y,
        miniBowserBalloonObj->trans.z);
    SetMiniBowserMotion(1, 0, 1);
}

static void ExecMiniBowserBalloon(omObjData *object)
{
    MiniBowserBalloonWork *work;
    s16 *models;
    work = OM_GET_WORK_PTR(miniBowserBalloonObj, MiniBowserBalloonWork);
    models = work->models;
    if(work->kill || BoardIsKill()) {
        BoardModelKill(models[0]);
        BoardModelKill(models[1]);
        HuMemDirectFree(work->models);
        miniBowserBalloonObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }
    if(work->timer) {
        work->timer--;
    } else {
        switch(work->state) {
            case 0:
                MiniBowserBalloonFall(work, object);
                break;

            case 1:
                MiniBowserBalloonRaise(work, object);
                break;

            case 2:
                MiniBowserBalloonHover(work, object);
                break;
        }
    }
    BoardModelPosSet(models[1], object->trans.x, object->trans.y+work->offset, object->trans.z);
}

static void MiniBowserBalloonHover(MiniBowserBalloonWork *work, omObjData *object)
{
    float angle;
    work->angle++;
    if(work->angle >= 360) {
        work->angle = 0;
    }
    OSs16tof32(&work->angle, &angle);
    work->offset = 10.0*sind(angle);
}

static void MiniBowserBalloonFall(MiniBowserBalloonWork *work, omObjData *object)
{
    Vec pos;
    BoardPlayerPosGet(eventPlayer, &pos);
    pos.y += 250.0f;
    if(object->trans.y < pos.y) {
        object->trans.y = pos.y;
        work->state = 2;
    } else {
        object->trans.y += -10.0f;
    }
}

static void MiniBowserBalloonRaise(MiniBowserBalloonWork *work, omObjData *object)
{
    Vec pos;
    BoardPlayerPosGet(eventPlayer, &pos);
    pos.y += 800.0f;
    if(object->trans.y > pos.y) {
        work->state = 2;
    } else {
        object->trans.y += 10.0f;
    }
}

static void SetMiniBowserMotion(s32 mot, u8 end, s32 pause)
{
    s16 *models;
    u32 attr;
    float shift_end;
    MiniBowserBalloonWork *work;
    work = OM_GET_WORK_PTR(miniBowserBalloonObj, MiniBowserBalloonWork);
    models = work->models;
    if(pause) {
        attr = HU3D_MOTATTR_LOOP;
    } else {
        attr = HU3D_MOTATTR_NONE;
    }
    if(end) {
        OSu8tof32(&end, &shift_end);
        BoardModelMotionShiftSet(models[0], mot, 0, shift_end, attr);
    } else {
        BoardModelMotionStart(models[0], mot, attr);
    }
}

static void SetMiniBowserMotionPause(s32 flag)
{
    s16 *models;
    MiniBowserBalloonWork *work;
    work = OM_GET_WORK_PTR(miniBowserBalloonObj, MiniBowserBalloonWork);
    models = work->models;
    if(flag) {
        BoardModelAttrSet(models[0], 0x40000001);
    } else {
        BoardModelAttrReset(models[0], 0x40000001);
    }
}

static void WaitMiniBowserMotion(void)
{
    s16 *models;
    MiniBowserBalloonWork *work;
    work = OM_GET_WORK_PTR(miniBowserBalloonObj, MiniBowserBalloonWork);
    models = work->models;
    BoardModelAttrReset(models[0], 0x40000001);
    while(!BoardModelMotionEndCheck(models[0])) {
        HuPrcVSleep();
    }
}
