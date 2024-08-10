#include "game/board/boo.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/window.h"

#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    s8 unk01;
    s8 unk02;
    char unk03[1];
    s16 unk04[2];
} BooEventWork;

typedef struct {
    struct {
        s8 unk00_field0 : 1;
    };
    s8 unk01;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    AnimData *unk08;
} BallWork;

typedef struct {
    struct {
        s8 unk00_field0 : 1;
    };
    char unk01[1];
    u16 unk02;
} BallCameraWork;

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04[6];
} BallPlayerData; // Size 0x10

typedef struct {
    struct {
        s8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
    };
    s8 unk01;
    u8 unk02;
} BallPlayerWork;

typedef struct {
    struct {
        s8 unk00_field0 : 1;
        u8 unk00_field1 : 4;
        u8 unk00_field2 : 1;
    };
    u8 unk01;
    u8 unk02;
    char unk03[1];
    s16 unk04;
    char unk06[2];
    float unk08;
} BallBooWork;

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ Vec unk04;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ char unk28[4];
} BallTakeCoinData; // Size 0x2C

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    u8 unk01;
    s16 unk02;
    float unk04;
} BallTakeCoinWork;

static void ComSetupStealPlayer(s32 arg0);
static void ComSetStealPlayerInput(s32 arg0, s32 arg1);
static void ExecCoinSteal(void);
static void ExecStarSteal(void);
static void ExecLightSteal(void);
static void SetBooMode(s32 arg0);
static void CreateBallMdl(s16 *arg0, Vec *arg1);
static void CreateBallView(void);
static void SetBallView(s32 arg0);
static void SetBallActive(s32 arg0);
static s32 CheckBallKill(void);
static void BallMain(omObjData *arg0);
static void BallRenderHook(void);
static void ExecBoo(omObjData *arg0);
static void UpdateBallCamera(omObjData *arg0);
static void CreateBallPlayer(void);
static s32 GetBallPlayerState(void);
static void SetBallPlayerState(s32 arg0);
static void ExecBallPlayer(omObjData *arg0);
static void BallPlayerZoomOut(omObjData *arg0, BallPlayerWork *arg1);
static void BallPlayerScare(omObjData *arg0, BallPlayerWork *arg1);
static void BallPlayerTurn(omObjData *arg0, BallPlayerWork *arg1);
static void BallPlayerPunch(omObjData *arg0, BallPlayerWork *arg1);
static void BallPlayerUseLight(omObjData *arg0, BallPlayerWork *arg1);
static void BallPlayerCatch(omObjData *arg0, BallPlayerWork *arg1);
static void BallBooCreate(void);
static void SetBallBooState(s32 arg0);
static s32 GetBallBooState(void);
static void ExecBallBoo(omObjData *arg0);
static void BallBooSpawn(omObjData *arg0, BallBooWork *arg1);
static void BallBooChase(omObjData *arg0, BallBooWork *arg1);
static void BallBooBattle(omObjData *arg0, BallBooWork *arg1);
static void BallBooAttack(omObjData *arg0, BallBooWork *arg1);
static void BallBooFlash(omObjData *arg0, BallBooWork *arg1);
static void TakeBallCoin(void);
static void ExecTakeBallCoin(omObjData *arg0);
static void TakeBallCoinPosSet(BallTakeCoinData *arg0, Vec *arg1);
static void UpdatePlayerCoins(void);

s8 lbl_801D41E2;
static s8 stealTarget;
static s8 stealType;
static s32 booKillF;
static u8 stealValue;
static u8 stealSuccess;
static u8 punchCount;
static s8 stealAvail[3];
static s8 starChoiceEnable[3];
static s32 battleTimer;
static s32 attackTimer;
static omObjData *ballTakeCoinObj;
static omObjData *ballPlayerObj;
static omObjData *ballBooObj;
static omObjData *ballCameraObj;
static omObjData *ballObj;
static omObjData *booEventObj;

static s32 booPlayerMotTbl[8][6] = {
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 11), DATA_MAKE_NUM(DATADIR_BYOKODORI, 19), DATA_MAKE_NUM(DATADIR_BYOKODORI, 27), DATA_MAKE_NUM(DATADIR_BYOKODORI, 35), DATA_MAKE_NUM(DATADIR_BYOKODORI, 43), DATA_MAKE_NUM(DATADIR_BYOKODORI, 51) },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 12), DATA_MAKE_NUM(DATADIR_BYOKODORI, 20), DATA_MAKE_NUM(DATADIR_BYOKODORI, 28), DATA_MAKE_NUM(DATADIR_BYOKODORI, 36), DATA_MAKE_NUM(DATADIR_BYOKODORI, 44), DATA_MAKE_NUM(DATADIR_BYOKODORI, 52) },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 13), DATA_MAKE_NUM(DATADIR_BYOKODORI, 21), DATA_MAKE_NUM(DATADIR_BYOKODORI, 29), DATA_MAKE_NUM(DATADIR_BYOKODORI, 37), DATA_MAKE_NUM(DATADIR_BYOKODORI, 45), DATA_MAKE_NUM(DATADIR_BYOKODORI, 53) },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 14), DATA_MAKE_NUM(DATADIR_BYOKODORI, 22), DATA_MAKE_NUM(DATADIR_BYOKODORI, 30), DATA_MAKE_NUM(DATADIR_BYOKODORI, 38), DATA_MAKE_NUM(DATADIR_BYOKODORI, 46), DATA_MAKE_NUM(DATADIR_BYOKODORI, 54) },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 15), DATA_MAKE_NUM(DATADIR_BYOKODORI, 23), DATA_MAKE_NUM(DATADIR_BYOKODORI, 31), DATA_MAKE_NUM(DATADIR_BYOKODORI, 39), DATA_MAKE_NUM(DATADIR_BYOKODORI, 47), DATA_MAKE_NUM(DATADIR_BYOKODORI, 55) },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 16), DATA_MAKE_NUM(DATADIR_BYOKODORI, 24), DATA_MAKE_NUM(DATADIR_BYOKODORI, 32), DATA_MAKE_NUM(DATADIR_BYOKODORI, 40), DATA_MAKE_NUM(DATADIR_BYOKODORI, 48), DATA_MAKE_NUM(DATADIR_BYOKODORI, 56) },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 17), DATA_MAKE_NUM(DATADIR_BYOKODORI, 25), DATA_MAKE_NUM(DATADIR_BYOKODORI, 33), DATA_MAKE_NUM(DATADIR_BYOKODORI, 41), DATA_MAKE_NUM(DATADIR_BYOKODORI, 49), DATA_MAKE_NUM(DATADIR_BYOKODORI, 57) },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 18), DATA_MAKE_NUM(DATADIR_BYOKODORI, 26), DATA_MAKE_NUM(DATADIR_BYOKODORI, 34), DATA_MAKE_NUM(DATADIR_BYOKODORI, 42), DATA_MAKE_NUM(DATADIR_BYOKODORI, 50), DATA_MAKE_NUM(DATADIR_BYOKODORI, 58) }
};

static s32 booSfxTbl[4][8] = {
    {
        0x0000012F, 0x0000016F, 0x000001AF, 0x000001EF,
        0x0000022F, 0x0000026F, 0x000002AF, 0x000002EF,
    },
    {
        0x00000130, 0x00000170, 0x000001B0, 0x000001F0,
        0x00000230, 0x00000270, 0x000002B0, 0x000002F0
    },
    {
        0x00000131, 0x00000171, 0x000001B1, 0x000001F1,
        0x00000231, 0x00000271, 0x000002B1, 0x000002F1,
    },
    {
        0x00000123, 0x00000163, 0x000001A3, 0x000001E3,
        0x00000223, 0x00000263, 0x000002A3, 0x000002E3
    }
};

static s32 hostMess[] = {
    MAKE_MESSID(7, 14),
    MAKE_MESSID(7, 20),
    MAKE_MESSID(7, 26),
    MAKE_MESSID(7, 32),
    MAKE_MESSID(7, 38),
    MAKE_MESSID(7, 44)
};

static s32 ballMdlTbl[] = {
    DATA_MAKE_NUM(DATADIR_BYOKODORI, 2),
    DATA_MAKE_NUM(DATADIR_BYOKODORI, 6)
};

s16 BoardBooCreate(s32 arg0, Vec *arg1) {
    BooEventWork *temp_r31;
    Vec spC;

    if (arg1) {
        spC = *arg1;
    } else {
        spC.x = spC.y = spC.z = 0.0f;
    }
    booEventObj = omAddObjEx(boardObjMan, 0x1000, 0, 0, -1, ExecBoo);
    temp_r31 = OM_GET_WORK_PTR(booEventObj, BooEventWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk01 = 0;
    temp_r31->unk02 = arg0;
    booKillF = 0;
    stealTarget = -1;
    lbl_801D41E2 = 0;
    punchCount = 0;
    stealValue = 0;
    stealSuccess = 0;
    booEventObj->trans.x = spC.x;
    booEventObj->trans.y = spC.y;
    booEventObj->trans.z = spC.z;
    CreateBallMdl(temp_r31->unk04, &spC);
    return temp_r31->unk04[0];
}

void BoardBooKill(void) {
    booKillF = 1;
    if (booEventObj) {
        OM_GET_WORK_PTR(booEventObj, BooEventWork)->unk00_field0 = 1;
    }
}

s32 BoardBooStealTypeSet(s32 arg0) {
    BooEventWork *temp_r29 = OM_GET_WORK_PTR(booEventObj, BooEventWork);
    s32 var_r25;
    s32 var_r27;
    s32 var_r26;
    s32 var_r28;
    s32 var_r30;
    s32 i;

    stealType = arg0;
    for (var_r26 = var_r30 = i = 0; i < 4; i++) {
        if (i != temp_r29->unk02) {
            var_r27 = i;
            stealAvail[var_r30] = var_r27;
            if ((stealType == 0 && BoardPlayerCoinsGet(var_r27) == 0) || (stealType == 1 && GWStarsGet(var_r27) == 0)) {
                starChoiceEnable[var_r30] = 0;
            } else {
                starChoiceEnable[var_r30] = 1;
                var_r26++;
            }
            var_r30++;
        }
    }
    if (var_r26 == 0) {
        stealType = -1;
        return 0;
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 24))) {
        var_r25 = BoardWinPortraitGet();
        var_r28 = hostMess[GWBoardGet()];
    } else {
        var_r25 = 3;
        var_r28 = MAKE_MESSID(18, 25);
    }
    BoardWinCreateChoice(1, var_r28, var_r25, 0);
    BoardWinAttrSet(0x10);
    if (stealType == 0) {
        var_r28 = MAKE_MESSID(7, 48);
    } else {
        var_r28 = MAKE_MESSID(7, 49);
    }
    BoardWinInsertMesSet(var_r28, 0);
    for (i = 0; i < 3; i++) {
        BoardWinInsertMesSet(BoardPlayerGetCharMess(stealAvail[i]), i + 1);
        if (starChoiceEnable[i] == 0) {
            BoardWinChoiceDisable(i);
        }
    }
    if (GWPlayer[temp_r29->unk02].com) {
        ComSetupStealPlayer(temp_r29->unk02);
    }
    BoardWinWait();
    stealTarget = BoardWinChoiceGet();
    if (stealTarget == 3) {
        stealTarget = -1;
        while (stealTarget == -1) {
            var_r30 = BoardRandMod(3);
            if (starChoiceEnable[var_r30] != 0) {
                stealTarget = stealAvail[var_r30];
            }
        }
    } else {
        stealTarget = stealAvail[stealTarget];
    }
    BoardWinKill();
    CreateBallView();
    SetBallView(1);
}

static void ComSetupStealPlayer(s32 arg0) {
    s32 var_r25;
    s32 var_r26;
    s32 var_r29;
    s32 temp_r28;
    s32 var_r27;
    s32 var_r30;
    s32 var_r24;
    s32 var_r22;
    s32 i;
    s16 sp8[3];

    switch (GWPlayer[arg0].diff) {
        case 0:
            var_r29 = 95;
            break;
        case 1:
            var_r29 = 50;
            break;
        case 2:
            var_r29 = 5;
            break;
        case 3:
            var_r29 = 0;
            break;
    }
    var_r22 = BoardRandMod(100);
    if (var_r22 >= var_r29) {
        var_r24 = 1;
    } else {
        var_r24 = 0;
    }
    for (i = 0; i < 3; i++) {
        temp_r28 = stealAvail[i];
        if (stealType == 1) {
            var_r30 = GWStarsGet(temp_r28);
        } else {
            var_r30 = BoardPlayerCoinsGet(temp_r28);
        }
        if (starChoiceEnable[i] == 0) {
            var_r30 = -1;
        }
        if ((s32) GWSystem.team != 0 && temp_r28 == BoardPlayerSameTeamFind(arg0)) {
            var_r30 = 0;
        }
        if (BoardPlayerItemFind(temp_r28, 8) != -1 && var_r24 != 0) {
            var_r30 = 0;
        }
        sp8[i] = var_r30;
    }
    var_r25 = var_r27 = -1;
    for (var_r26 = i = 0; i < 3; i++) {
        var_r30 = sp8[i];
        if (var_r30 != -1) {
            if (var_r30 > 0 && var_r30 >= var_r25) {
                var_r25 = var_r30;
                var_r27 = var_r26;
            }
            var_r26++;
        }
    }
    if (var_r27 == -1) {
        var_r27 = 0;
    }
    ComSetStealPlayerInput(arg0, var_r27);
}

static void ComSetStealPlayerInput(s32 arg0, s32 arg1) {
    s32 spC[4];
    s32 temp_r30;
    s32 i;
    s16 temp_r29;

    spC[0] = spC[1] = spC[2] = spC[3] = 0;
    temp_r30 = GWPlayer[arg0].port;
    temp_r29 = GWMessDelayGet();
    spC[temp_r30] = 4;
    if (arg1 != 0) {
        for (i = 0; i < arg1; i++) {
            HuWinComKeyWait(spC[0], spC[1], spC[2], spC[3], temp_r29);
        }
    }
    spC[temp_r30] = 0x100;
    HuWinComKeyWait(spC[0], spC[1], spC[2], spC[3], temp_r29);
}

s32 BoardBooStealMain(void) {
    BooEventWork *sp8;
    s32 var_r31;
    s32 var_r30;

    stealType == -1;
    sp8 = OM_GET_WORK_PTR(booEventObj, BooEventWork);
    if (stealType == 0) {
        SetBooMode(2);
    } else {
        SetBooMode(1);
    }
    var_r31 = BoardPlayerItemFind(stealTarget, 8);
    if (var_r31 != -1) {
        stealType = 2;
        BoardPlayerItemRemove(stealTarget, var_r31);
        var_r30 = MAKE_MESSID(7, 4);
    } else {
        var_r30 = MAKE_MESSID(7, 3);
    }
    BoardCameraMotionWait();
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (stealTarget != var_r31) {
            BoardModelVisibilitySet(BoardPlayerModelGet(var_r31), 0);
        }
    }
    CreateBallPlayer();
    omVibrate(stealTarget, 12, 4, 2);
    SetBallActive(1);
    while (!CheckBallKill()) {
        HuPrcVSleep();
    }
    if (stealType == 0) {
        BoardWinCreate(2, var_r30, -1);
        BoardWinInsertMesSet(BoardPlayerGetCharMess(stealTarget), 0);
        BoardWinPause();
    }
    switch (stealType) {
        case 0:
            ExecCoinSteal();
            break;
        case 1:
            ExecStarSteal();
            break;
        case 2:
            ExecLightSteal();
            break;
    }
    BoardWinKill();
    SetBallActive(-1);
    while (!CheckBallKill()) {
        HuPrcVSleep();
    }
    booKillF = 1;
    SetBallView(0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (stealTarget != var_r31) {
            BoardModelVisibilitySet(BoardPlayerModelGet(var_r31), 1);
        }
    }
    HuPrcSleep(2);
    if (stealType == 2) {
        return 0;
    } else {
        return 1;
    }
}

static void ExecCoinSteal(void) {
    while (GetBallPlayerState() != 2) {
        HuPrcVSleep();
    }
    BallBooCreate();
    while (GetBallBooState() != 0) {
        HuPrcVSleep();
    }
    while (GetBallPlayerState() != 0) {
        HuPrcVSleep();
    }
    SetBallBooState(2);
    while (GetBallBooState() != 0) {
        HuPrcVSleep();
    }
    SetBallPlayerState(4);
    SetBallBooState(3);
    punchCount = 0;
    HuPrcSleep(120);
    while (GetBallBooState() != 0) {
        HuPrcVSleep();
    }
    while (GetBallPlayerState() != 0) {
        HuPrcVSleep();
    }
}

static void ExecStarSteal(void) {
    while (GetBallPlayerState() != 2) {
        HuPrcVSleep();
    }
    BallBooCreate();
    while (GetBallBooState() != 0) {
        HuPrcVSleep();
    }
    while (GetBallPlayerState() != 0) {
        HuPrcVSleep();
    }
    SetBallBooState(2);
    while (GetBallBooState() != 0) {
        HuPrcVSleep();
    }
    SetBallBooState(4);
    while (GetBallBooState() != 0) {
        HuPrcVSleep();
    }
    while (GetBallPlayerState() != 0) {
        HuPrcVSleep();
    }
}

static void ExecLightSteal(void) {
    while (GetBallPlayerState() != 0) {
        HuPrcVSleep();
    }
    BallBooCreate();
    while (GetBallBooState() != 0) {
        HuPrcVSleep();
    }
    SetBallBooState(2);
    while (GetBallBooState() != 0) {
        HuPrcVSleep();
    }
    SetBallPlayerState(6);
    while (GetBallPlayerState() != 0) {
        HuPrcVSleep();
    }
    while (GetBallBooState() != 0) {
        HuPrcVSleep();
    }
}

static void SetBooMode(s32 arg0) {
    OM_GET_WORK_PTR(booEventObj, BooEventWork)->unk01 = arg0;
}

static void CreateBallMdl(s16 *arg0, Vec *arg1) {
    s32 i;

    for (i = 0; i < 2; i++) {
        arg0[i] = BoardModelCreate(ballMdlTbl[i], NULL, 0);
        BoardModelPosSetV(arg0[i], arg1);
    }
    BoardModelMotionStart(arg0[0], 0, 0x40000001);
    BoardModelHookSet(arg0[0], "sui", arg0[1]);
    BoardModelPosSet(arg0[1], 0.0f, 0.0f, 0.0f);
    BoardModelVisibilitySet(arg0[1], 1);
}

static void CreateBallView(void) {
    AnimBmpData *temp_r29;
    BooEventWork *temp_r28;
    BallWork *temp_r31;
    BallCameraWork *temp_r30;

    temp_r28 = OM_GET_WORK_PTR(booEventObj, BooEventWork);
    ballObj = omAddObjEx(boardObjMan, 0x1001, 0, 0, -1, BallMain);
    temp_r31 = OM_GET_WORK_PTR(ballObj, BallWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk08 = HuSprAnimMake(80, 80, 2);
    temp_r29 = temp_r31->unk08->bmp;
    temp_r29->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x3200, MEMORY_DEFAULT_NUM);
    memset(temp_r29->data, 0, 0x3200);
    temp_r31->unk04 = Hu3DHookFuncCreate((void*) BallRenderHook);
    Hu3DModelLayerSet(temp_r31->unk04, 3);
    Hu3DModelCameraSet(temp_r31->unk04, 1);
    temp_r31->unk06 = Hu3DProjectionCreate(temp_r31->unk08, 25.0f, 100.0f, 13000.0f);
    Hu3DModelProjectionSet(BoardModelIDGet(temp_r28->unk04[1]), temp_r31->unk06);
    Hu3DProjectionTPLvlSet(temp_r31->unk06, 0.0f);
    ballCameraObj = omAddObjEx(boardObjMan, 0x7E03, 0, 0, -1, UpdateBallCamera);
    temp_r30 = OM_GET_WORK_PTR(ballCameraObj, BallCameraWork);
    temp_r30->unk00_field0 = 0;
    temp_r30->unk02 = 1;
    ballCameraObj->rot.x = -8.0f;
    ballCameraObj->rot.y = 80.0f;
    ballCameraObj->rot.z = 300.0f;
    Hu3DCameraPerspectiveSet(temp_r30->unk02, 25.0f, 10.0f, 2000.0f, 1.2f);
    Hu3DCameraScissorSet(temp_r30->unk02, 0, 0, 0xA0, 0xA0);
    Hu3DCameraViewportSet(temp_r30->unk02, 0.0f, 0.0f, 160.0f, 160.0f, 0.0f, 1.0f);
}

static void SetBallView(s32 arg0) {
    u16 var_r31;
    s32 i;

    if (arg0 != 0) {
        var_r31 = 2;
    } else {
        Hu3DCameraPerspectiveSet(2, -1.0f, 0.0f, 0.0f, 0.0f);
        var_r31 = 1;
    }
    for (i = 0; i < 4; i++) {
        BoardPlayerCameraSet(i, var_r31);
    }
    BoardSpaceCameraSet(var_r31);
    BoardModelCameraSetAll(var_r31);
    BoardCameraMaskSet((u16) var_r31);
    BoardCameraScissorSet(0, 0, 640, 480);
}

static void SetBallActive(s32 arg0) {
    BallWork *temp_r31 = OM_GET_WORK_PTR(ballObj, BallWork);

    temp_r31->unk01 = arg0 * 8;
}

static s32 CheckBallKill(void) {
    BallWork *temp_r31;

    if (!ballObj) {
        return 1;
    }
    temp_r31 = OM_GET_WORK_PTR(ballObj, BallWork);
    if (temp_r31->unk01 != 0) {
        return 0;
    } else {
        return 1;
    }
}

static void BallMain(omObjData *arg0) {
    BallWork *temp_r30 = OM_GET_WORK_PTR(arg0, BallWork);
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f30;
    float var_f29;
    s16 *temp_r29;

    if (booKillF != 0 || BoardIsKill() != 0) {
        temp_r29 = OM_GET_WORK_PTR(booEventObj, BooEventWork)->unk04;
        Hu3DModelProjectionReset(BoardModelIDGet(temp_r29[1]), temp_r30->unk06);
        Hu3DProjectionKill(temp_r30->unk06);
        Hu3DModelKill(temp_r30->unk04);
        ballObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    temp_f30 = 240.0f;
    BoardCameraRotGet(&sp20);
    BoardCameraTargetGet(&sp2C);
    sp8.x = sp2C.x + sind(sp20.y) * cosd(sp20.x) * temp_f30;
    sp8.y = sp2C.y + -sind(sp20.x) * temp_f30;
    sp8.z = sp2C.z + cosd(sp20.y) * cosd(sp20.x) * temp_f30;
    sp14.x = sind(sp20.y) * sind(sp20.x);
    sp14.y = cosd(sp20.x);
    sp14.z = cosd(sp20.y) * sind(sp20.x);
    if (temp_r30->unk01 != 0) {
        temp_r30->unk02 += temp_r30->unk01;
        if (temp_r30->unk02 > 255) {
            temp_r30->unk02 = 255;
            temp_r30->unk01 = 0;
        } else if (temp_r30->unk02 < 0) {
            temp_r30->unk02 = 0;
            temp_r30->unk01 = 0;
        }
    }
    Hu3DProjectionPosSet(temp_r30->unk06, &sp8, &sp14, &sp2C);
    OSs16tof32(&temp_r30->unk02, &var_f29);
    var_f29 = var_f29 * 0.003921569f;
    Hu3DProjectionTPLvlSet(temp_r30->unk06, var_f29);
}

static void BallRenderHook(void) {
    BallWork *temp_r31;
    GXColor sp10;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Mtx44 sp68;
    Mtx sp38;

    if (!ballObj) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(ballObj, BallWork);
    sp10.a = sp10.r = sp10.g = sp10.b = 0;
    GXSetCopyClear(sp10, -1);
    GXSetTexCopySrc(0, 0, 160, 160);
    GXSetTexCopyDst(80, 80, GX_TF_RGB5A3, GX_TRUE);
    GXCopyTex(temp_r31->unk08->bmp->data, GX_TRUE);
    DCFlushRange(temp_r31->unk08->bmp->data, 12800);
    GXPixModeSync();
    C_MTXPerspective(sp68, 25.0f, 1.2f, 100.0f, 13000.0f);
    GXSetProjection(sp68, GX_PERSPECTIVE);
    GXSetViewport(0.0f, 0.0f, 160.0f, 160.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 160, 160);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
    sp10.r = 0;
    sp10.g = 0;
    sp10.b = 0;
    sp10.a = 0xFF;
    GXSetTevColor(GX_TEVREG0, sp10);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    sp2C.x = 0.0f;
    sp2C.y = 0.0f;
    sp2C.z = 100.0f;
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = 0.0f;
    sp20.x = 0.0f;
    sp20.y = 1.0f;
    sp20.z = 0.0f;
    C_MTXLookAt(sp38, &sp2C, &sp20, &sp14);
    GXLoadPosMtxImm(sp38, GX_PNMTX0);
    sp2C.x = sind(12.5) * 20000.0 * 1.2f;
    sp2C.y = sind(12.5) * 20000.0 * 0.8333333f;
    sp2C.z = -9000.0f;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-sp2C.x, -sp2C.y, sp2C.z);
    GXPosition3f32(sp2C.x, -sp2C.y, sp2C.z);
    GXPosition3f32(sp2C.x, sp2C.y, sp2C.z);
    GXPosition3f32(-sp2C.x, sp2C.y, sp2C.z);
    GXEnd();
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
}

static void ExecBoo(omObjData *arg0) {
    BooEventWork *temp_r30 = OM_GET_WORK_PTR(arg0, BooEventWork);
    s32 i;

    if (temp_r30->unk00_field0 != 0 || BoardIsKill()) {
        for (i = 0; i < 2; i++) {
            BoardModelKill(((s16*) temp_r30->unk04)[i]);
        }
        BoardWinKill();
        booEventObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
}

static void UpdateBallCamera(omObjData *arg0) {
    BallCameraWork *var_r30 = OM_GET_WORK_PTR(arg0, BallCameraWork);
    Vec sp20;
    Vec sp14;
    Vec sp8;

    if (booKillF != 0 || BoardIsKill()) {
        ballCameraObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    sp20.x = arg0->trans.x;
    sp20.y = arg0->trans.y + arg0->rot.y;
    sp20.z = arg0->trans.z;
    sp14.x = sp20.x + sin(0.0) * cosd(arg0->rot.x) * arg0->rot.z;
    sp14.y = sp20.y + -sind(arg0->rot.x) * arg0->rot.z;
    sp14.z = sp20.z + cos(0.0) * cosd(arg0->rot.x) * arg0->rot.z;
    sp8.x = sin(0.0) * sind(arg0->rot.x);
    sp8.y = cosd(arg0->rot.x);
    sp8.z = cos(0.0) * sind(arg0->rot.x);
    Hu3DCameraPosSetV(var_r30->unk02, &sp14, &sp8, &sp20);
}

static inline void CreateBallPlayerInlineFunc(float x, float y, float z) {
    if (ballCameraObj) {
        ballCameraObj->trans.x = x;
        ballCameraObj->trans.y = y;
        ballCameraObj->trans.z = z;
    }
}

static void CreateBallPlayer(void) {
    char *temp_r27;
    Vec sp8;
    s32 temp_r28;
    s32 var_r26;
    s32 i;
    omObjData *temp_r31;
    BallPlayerData *temp_r30;
    BallPlayerWork *temp_r25;

    ballPlayerObj = temp_r31 = omAddObjEx(boardObjMan, 0x1005, 0, 0, -1, ExecBallPlayer);
    temp_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(BallPlayerData), MEMORY_DEFAULT_NUM);
    temp_r25 = OM_GET_WORK_PTR(temp_r31, BallPlayerWork);
    temp_r25->unk00_field0 = 0;
    SetBallPlayerState(1);
    temp_r31->trans.x = 0.0f;
    temp_r31->trans.y = 0.0f;
    temp_r31->trans.z = 0.0f;
    BoardPlayerPosGet(stealTarget, &sp8);
    temp_r31->scale.x = sp8.x;
    temp_r31->scale.y = sp8.y;
    temp_r31->scale.z = sp8.z;
    temp_r31->rot.x = 300.0f;
    temp_r31->rot.y = 750.0f;
    temp_r28 = GWPlayer[stealTarget].character;
    temp_r30 = temp_r31->data;
    for (i = 0; i < 6; i++) {
        var_r26 = booPlayerMotTbl[temp_r28][i];
        temp_r30->unk04[i] = BoardPlayerMotionCreate(stealTarget, var_r26);
    }
    if (stealType == 2) {
        temp_r30->unk00 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 118), 0, 0);
        temp_r30->unk02 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 130), 0, 0);
        BoardModelLayerSet(temp_r30->unk00, 0);
        BoardModelLayerSet(temp_r30->unk02, 0);
        BoardModelCameraSet(temp_r30->unk00, 1);
        BoardModelCameraSet(temp_r30->unk02, 1);
        BoardModelScaleSet(temp_r30->unk00, 0.4f, 0.4f, 0.4f);
        temp_r27 = CharModelHookNameGet(temp_r28, 2, 0);
        BoardModelHookSet(temp_r30->unk00, "b00p_item30", temp_r30->unk02);
        BoardModelHookSet(BoardPlayerModelGet(stealTarget), temp_r27, temp_r30->unk00);
    } else {
        temp_r30->unk00 = -1;
        temp_r30->unk02 = -1;
    }
    if (stealType != 2) {
        BoardPlayerMotionStart(stealTarget, temp_r30->unk04[1], 0x40000001);
    } else {
        BoardPlayerMotionStart(stealTarget, temp_r30->unk04[3], 0x40000001);
    }
    BoardPlayerPosSet(stealTarget, temp_r31->trans.x, temp_r31->trans.y, temp_r31->trans.z);
    BoardPlayerLayerSet(stealTarget, 0);
    BoardPlayerCameraSet(stealTarget, 1);
    if (ballCameraObj) {
        ballCameraObj->rot.x = -8.0f;
        ballCameraObj->rot.y = 80.0f;
        ballCameraObj->rot.z = 300.0f;
    }
    CreateBallPlayerInlineFunc(temp_r31->trans.x, temp_r31->trans.y, temp_r31->trans.z);
}

static s32 GetBallPlayerState(void) {
    BallPlayerWork *temp_r31 = OM_GET_WORK_PTR(ballPlayerObj, BallPlayerWork);

    return temp_r31->unk01;
}

static void SetBallPlayerState(s32 arg0) {
    BallPlayerWork *temp_r31 = OM_GET_WORK_PTR(ballPlayerObj, BallPlayerWork);

    temp_r31->unk01 = arg0;
    temp_r31->unk02 = 0;
}

static void ExecBallPlayer(omObjData *arg0) {
    BallPlayerWork *temp_r30 = OM_GET_WORK_PTR(arg0, BallPlayerWork);
    BallPlayerData *temp_r29 = arg0->data;
    BallWork *temp_r27;
    s32 i;

    if (booKillF != 0 || BoardIsKill()) {
        BoardPlayerPosSet(stealTarget, arg0->scale.x, arg0->scale.y, arg0->scale.z);
        BoardPlayerRotYSet(stealTarget, 0.0f);
        BoardPlayerLayerSet(stealTarget, 0);
        BoardPlayerCameraSet(stealTarget, 1);
        BoardModelHookReset(temp_r29->unk00);
        BoardModelHookReset(BoardPlayerModelGet(stealTarget));
        BoardModelKill(temp_r29->unk00);
        BoardModelKill(temp_r29->unk02);
        BoardPlayerMotionStart(stealTarget, 1, 0x40000001);
        for (i = 0; i < 6; i++) {
            BoardPlayerMotionKill(stealTarget, temp_r29->unk04[i]);
        }
        if (arg0->data) {
            HuMemDirectFree(arg0->data);
            arg0->data = NULL;
        }
        ballPlayerObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    temp_r27 = OM_GET_WORK_PTR(ballObj, BallWork);
    if (temp_r27->unk01 == 0) {
        switch (temp_r30->unk01) {
            case 1:
                BallPlayerZoomOut(arg0, temp_r30);
                break;
            case 3:
                BallPlayerScare(arg0, temp_r30);
                break;
            case 2:
                BallPlayerTurn(arg0, temp_r30);
                break;
            case 4:
                BallPlayerPunch(arg0, temp_r30);
                break;
            case 6:
                BallPlayerUseLight(arg0, temp_r30);
                break;
            case 5:
                BallPlayerCatch(arg0, temp_r30);
                break;
        }
    }
}

static void BallPlayerZoomOut(omObjData *arg0, BallPlayerWork *arg1) {
    Vec sp14;
    Vec sp8;
    float temp_f31;
    s32 var_r29;

    arg0->rot.x += 8.0f;
    if (arg0->rot.y < arg0->rot.x) {
        arg0->rot.x = arg0->rot.y;
        sp14.x = arg0->trans.x;
        sp14.y = arg0->trans.y;
        sp14.z = arg0->trans.z;
        sp8.x = sp14.x + 120.0 * sind(-90);
        sp8.y = sp14.y;
        sp8.z = sp14.z + 120.0 * cosd(-90);
        BoardPlayerPosLerpStart(stealTarget, &sp14, &sp8, 20);
        var_r29 = GWPlayer[stealTarget].character;
        HuAudFXPlay(booSfxTbl[0][var_r29]);
        SetBallPlayerState(3);
    }
    temp_f31 = arg0->rot.x;
    if (ballCameraObj && temp_f31 != -1.0f) {
        ballCameraObj->rot.z = temp_f31;
    }
}

static void BallPlayerScare(omObjData *arg0, BallPlayerWork *arg1) {
    BallPlayerData *temp_r29;
    float temp_f31;

    if (!GWPlayer[stealTarget].moving) {
        temp_r29 = arg0->data;
        temp_f31 = -BoardPlayerRotYGet(stealTarget);
        if (stealType == 2) {
            BoardPlayerMotionShiftSet(stealTarget, temp_r29->unk04[3], 0.0f, 10.0f, 0x40000001);
            SetBallPlayerState(0);
        } else {
            BoardPlayerMotBlendSet(stealTarget, temp_f31, 15);
            SetBallPlayerState(2);
        }
    }
}

static void BallPlayerTurn(omObjData *arg0, BallPlayerWork *arg1) {
    if (BoardPlayerMotBlendCheck(stealTarget)) {
        SetBallPlayerState(0);
        arg1->unk00_field1 = 0;
    }
}

static void BallPlayerPunch(omObjData *arg0, BallPlayerWork *arg1) {
    BallPlayerData *temp_r29;
    s32 temp_r30;
    u32 var_r31;

    var_r31 = 0;
    temp_r29 = arg0->data;
    if (GWPlayer[stealTarget].com) {
        temp_r30 = BoardRandMod(100);
        switch (GWPlayer[stealTarget].diff) {
            case 0:
                if (temp_r30 > 90) {
                    var_r31 = 0x100;
                }
                break;
            case 1:
                if (temp_r30 > 83) {
                    var_r31 = 0x100;
                }
                break;
            case 2:
                if (temp_r30 > 75) {
                    var_r31 = 0x100;
                }
                break;
            case 3:
                if (temp_r30 > 68) {
                    var_r31 = 0x100;
                }
                break;
        }
    } else {
        var_r31 = HuPadBtnDown[GWPlayer[stealTarget].port] & 0x100;
    }
    if ((var_r31 & 0x100) && GetBallBooState() == 3 && battleTimer < 120) {
        punchCount++;
    }
    if (arg1->unk00_field1 != 0) {
        if (BoardPlayerMotionEndCheck(stealTarget)) {
            arg1->unk00_field1 = 0;
            BoardPlayerMotionStart(stealTarget, 1, 0x40000001);
        }
    } else {
        if (var_r31 & 0x100) {
            arg1->unk00_field1 = 1;
            BoardPlayerMotionStart(stealTarget, temp_r29->unk04[2], 0);
        }
    }
}

static void BallPlayerUseLight(omObjData *arg0, BallPlayerWork *arg1) {
    BallPlayerData *temp_r31 = arg0->data;

    switch (arg1->unk02) {
        case 0:
            BoardModelScaleSet(temp_r31->unk02, 2.5f, 2.5f, 2.5f);
            BoardPlayerMotionStart(stealTarget, temp_r31->unk04[4], 0);
            arg1->unk02 = 1;
            break;
        case 1:
            if (BoardPlayerMotionEndCheck(stealTarget)) {
                SetBallBooState(7);
                BoardPlayerMotionStart(stealTarget, temp_r31->unk04[5], 0);
                arg1->unk02 = 2;
            }
            break;
        case 2:
            if (BoardPlayerMotionEndCheck(stealTarget)) {
                SetBallPlayerState(0);
            }
            break;
    }
}

static void BallPlayerCatch(omObjData *arg0, BallPlayerWork *arg1) {
    s32 temp_r28;
    BallPlayerData *temp_r27 = arg0->data;

    temp_r28 = GWPlayer[stealTarget].character;
    if (arg1->unk02 == 0) {
        if (stealType == 0) {
            UpdatePlayerCoins();
            HuAudFXPlay(booSfxTbl[2][temp_r28]);
            omVibrate(stealTarget, 12, 4, 2);
            TakeBallCoin();
        }
        if (stealType == 1) {
            BoardPlayerStarsAdd(stealTarget, -1);
            HuAudFXPlay(booSfxTbl[2][temp_r28]);
            omVibrate(stealTarget, 12, 4, 2);
            TakeBallStar();
        }
        BoardPlayerMotionShiftSet(stealTarget, temp_r27->unk04[0], 0.0f, 10.0f, 0);
        arg1->unk02 = 1;
    }
    if (stealType == 0) {
        if (CheckBallCoinDone()) {
            SetBallPlayerState(0);
        }
    } else {
        if (stealType == 1 && CheckTakeBallStarDone()) {
            SetBallPlayerState(0);
        }
    }
}

static s32 ballBooMdl[] = {
    DATA_MAKE_NUM(DATADIR_BGUEST, 19),
    DATA_MAKE_NUM(DATADIR_BGUEST, 20),
    DATA_MAKE_NUM(DATADIR_BGUEST, 21),
    DATA_MAKE_NUM(DATADIR_BGUEST, 22),
    DATA_MAKE_NUM(DATADIR_BGUEST, 23),
    -1
};

static void BallBooCreate(void) {
    BallBooWork *temp_r31;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    float var_f30;
    float var_f29;

    ballBooObj = omAddObjEx(boardObjMan, 0x1004, 0, 0, -1, ExecBallBoo);
    temp_r31 = OM_GET_WORK_PTR(ballBooObj, BallBooWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field2 = 0;
    temp_r31->unk01 = 0;
    SetBallBooState(1);
    temp_r31->unk04 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 18), ballBooMdl, 0);
    BoardModelAlphaSet(temp_r31->unk04, 0xFF);
    BoardModelLayerSet(temp_r31->unk04, 0);
    BoardModelCameraSet(temp_r31->unk04, 1);
    temp_f31 = BoardPlayerRotYGet(stealTarget);
    BoardPlayerPosGet(stealTarget, &sp14);
    ballBooObj->trans.x = sp14.x + 240.0 * sind(-temp_f31);
    ballBooObj->trans.y = sp14.y + 160.0f;
    ballBooObj->trans.z = sp14.z + 240.0 * cosd(-temp_f31);
    BoardModelPosSet(temp_r31->unk04, ballBooObj->trans.x, ballBooObj->trans.y, ballBooObj->trans.z);
    if (stealType == 2) {
        var_f30 = 126.0f;
        var_f29 = 80.0f;
    } else {
        var_f30 = 90.0f;
        var_f29 = 100.0f;
    }
    sp8.x = sp14.x + var_f30 * sind(-temp_f31);
    sp8.y = sp14.y + var_f29;
    sp8.z = sp14.z + var_f30 * cosd(-temp_f31);
    ballBooObj->rot.x = (sp8.x - ballBooObj->trans.x) / 60.0f;
    ballBooObj->rot.y = (sp8.y - ballBooObj->trans.y) / 60.0f;
    ballBooObj->rot.z = (sp8.z - ballBooObj->trans.z) / 60.0f;
    temp_r31->unk02 = 60;
    ballBooObj->scale.x = 1.0f;
    ballBooObj->scale.z = 1.0f;
    sp8.x = sp14.x - ballBooObj->trans.x;
    sp8.z = sp14.z - ballBooObj->trans.z;
    ballBooObj->scale.y = atan2d(sp8.x, sp8.z);
    BoardModelRotYSet(temp_r31->unk04, ballBooObj->scale.y);
    BoardModelMotionStart(temp_r31->unk04, 1, 0x40000001);
}

static void SetBallBooState(s32 arg0) {
    BallBooWork *temp_r31 = OM_GET_WORK_PTR(ballBooObj, BallBooWork);
    Vec sp8;

    temp_r31->unk00_field1 = arg0;
    if (arg0 == 2) {
        HuAudFXPlay(0x64);
    }
    if (arg0 == 4) {
        BoardPlayerPosGet(stealTarget, &sp8);
        sp8.y += 100.0f;
        ballBooObj->rot.x = (sp8.x - ballBooObj->trans.x) / 30.0f;
        ballBooObj->rot.y = (sp8.y - ballBooObj->trans.y) / 30.0f;
        ballBooObj->rot.z = (sp8.z - ballBooObj->trans.z) / 30.0f;
        temp_r31->unk02 = 30;
        BoardModelMotionShiftSet(temp_r31->unk04, 1, 0.0f, 10.0f, 0x40000001);
    }
    if (arg0 == 5) {
        HuAudFXPlay(0x64);
        temp_r31->unk02 = 0;
    }
    if (arg0 == 7) {
        temp_r31->unk08 = -ballBooObj->scale.y;
        HuAudFXPlay(0x64);
        BoardModelMotionShiftSet(temp_r31->unk04, 5, 0.0f, 10.0f, 0x40000001);
    }
    if (arg0 == 3) {
        battleTimer = 0;
        attackTimer = 0;
    }
}

static s32 GetBallBooState(void) {
    BallBooWork *temp_r31 = OM_GET_WORK_PTR(ballBooObj, BallBooWork);

    return temp_r31->unk00_field1;
}

static void ExecBallBoo(omObjData *arg0) {
    BallBooWork *temp_r30 = OM_GET_WORK_PTR(arg0, BallBooWork);

    if (booKillF != 0 || BoardIsKill()) {
        BoardModelKill(temp_r30->unk04);
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r30->unk01 != 0) {
        temp_r30->unk01--;
        return;
    }
    switch (temp_r30->unk00_field1) {
        case 1:
            BallBooSpawn(arg0, temp_r30);
            break;
        case 2:
        case 4:
        case 6:
            BallBooChase(arg0, temp_r30);
            break;
        case 3:
            BallBooBattle(arg0, temp_r30);
            break;
        case 5:
            BallBooAttack(arg0, temp_r30);
            break;
        case 7:
            BallBooFlash(arg0, temp_r30);
            break;
    }
    BoardModelRotYSet(temp_r30->unk04, arg0->scale.y);
    BoardModelPosSet(temp_r30->unk04, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelScaleSet(temp_r30->unk04, arg0->scale.z, arg0->scale.z, arg0->scale.z);
}

static void BallBooSpawn(omObjData *arg0, BallBooWork *arg1) {
    BoardModelAlphaSet(arg1->unk04, 0xFF);
    SetBallBooState(0);
}

static void BallBooChase(omObjData *arg0, BallBooWork *arg1) {
    if (arg1->unk02 != 0) {
        arg1->unk02--;
        arg0->trans.x += arg0->rot.x;
        arg0->trans.y += arg0->rot.y;
        arg0->trans.z += arg0->rot.z;
    } else {
        if (arg1->unk00_field1 == 4) {
            SetBallBooState(5);
        } else {
            SetBallBooState(0);
        }
        BoardModelMotionShiftSet(arg1->unk04, 1, 0.0f, 10.0f, 0x40000001);
    }
}

static void BallBooBattle(omObjData *arg0, BallBooWork *arg1) {
    s32 temp_r29;

    battleTimer++;
    if (attackTimer != 0) {
        attackTimer--;
    }
    if (battleTimer >= 120) {
        SetBallBooState(4);
        return;
    }
    if (arg1->unk00_field2 != 0) {
        if (BoardModelMotionEndCheck(arg1->unk04)) {
            arg1->unk00_field2 = 0;
            BoardModelMotionStart(arg1->unk04, 1, 0x40000001);
        }
        return;
    }
    if (BoardRandMod(100) <= 70) {
        BoardModelMotionStart(arg1->unk04, 2, 0);
        arg1->unk00_field2 = 1;
        if (BoardRandMod(100) > 50 && attackTimer == 0) {
            temp_r29 = GWPlayer[stealTarget].character;
            HuAudFXPlay(booSfxTbl[1][temp_r29]);
            omVibrate(stealTarget, 12, 6, 6);
            attackTimer = 48;
        }
    }
}

static void BallBooAttack(omObjData *arg0, BallBooWork *arg1) {
    float var_f29;

    if (arg1->unk02 < 90) {
        arg1->unk02 += 6;
        if (arg1->unk02 >= 90) {
            arg1->unk02 = 90;
            SetBallBooState(0);
            SetBallPlayerState(5);
        }
    }
    OSu8tof32(&arg1->unk02, &var_f29);
    arg0->scale.z = 1.0 + sind(var_f29);
}

static void BallBooFlash(omObjData *arg0, BallBooWork *arg1) {
    Vec sp8;
    float temp_f31;

    if (BoardDAngleCalcRange(&arg0->scale.y, arg1->unk08, 8.0f) != 0) {
        SetBallBooState(6);
        BoardModelMotionShiftSet(arg1->unk04, 3, 0.0f, 10.0f, 0x40000001);
        temp_f31 = BoardPlayerRotYGet(stealTarget);
        BoardPlayerPosGet(stealTarget, &sp8);
        sp8.x += 500.0 * sind(-temp_f31);
        sp8.y = sp8.y + 160.0f;
        sp8.z += 500.0 * cosd(-temp_f31);
        arg0->rot.x = (sp8.x - arg0->trans.x) / 72.0f;
        arg0->rot.y = (sp8.y - arg0->trans.y) / 72.0f;
        arg0->rot.z = (sp8.z - arg0->trans.z) / 72.0f;
        arg1->unk02 = 72;
    }
}

static void TakeBallCoin(void) {
    BallTakeCoinData *var_r31;
    Vec sp8;
    s32 i;

    ballTakeCoinObj = omAddObjEx(boardObjMan, 0x1002, 0, 0, -1, ExecTakeBallCoin);
    ballTakeCoinObj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(BallTakeCoinData) * 10, MEMORY_DEFAULT_NUM);
    memset(ballTakeCoinObj->data, 0, sizeof(BallTakeCoinData) * 10);
    BoardPlayerPosGet(stealTarget, &sp8);
    ballTakeCoinObj->trans.x = sp8.x;
    ballTakeCoinObj->trans.y = sp8.y;
    ballTakeCoinObj->trans.z = sp8.z;
    var_r31 = ballTakeCoinObj->data;
    for (i = 0; i < 10; i++, var_r31++) {
        var_r31->unk00 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 1);
        BoardModelCameraSet(var_r31->unk00, 1);
        fn_8006DDE8(var_r31->unk00, -1.0f);
        BoardModelScaleSet(var_r31->unk00, 0.5f, 0.5f, 0.5f);
        var_r31->unk04.x = sp8.x;
        var_r31->unk04.y = sp8.y + 100.0f;
        var_r31->unk04.z = sp8.z;
        var_r31->unk1C.x = 3.0f * (BoardRandFloat() - 0.5f);
        var_r31->unk1C.y = 3.0 * sin(BoardRandFloat());
        var_r31->unk1C.z = 3.0f * (BoardRandFloat() - 0.5f);
        PSVECScale(&var_r31->unk1C, &var_r31->unk1C, 4.0f);
        BoardModelPosSetV(var_r31->unk00, &var_r31->unk04);
        var_r31->unk10 = var_r31->unk1C;
    }
}

static void ExecTakeBallCoin(omObjData *arg0) {
    BallTakeCoinData *var_r30;
    Vec sp8;
    s32 i;

    if (CheckBallCoinDone() || booKillF != 0 || BoardIsKill()) {
        if (arg0->data) {
            HuMemDirectFree(arg0->data);
            arg0->data = NULL;
        }
        ballTakeCoinObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    sp8.x = arg0->trans.x;
    sp8.y = arg0->trans.y;
    sp8.z = arg0->trans.z;
    var_r30 = arg0->data;
    for (i = 0; i < 10; i++, var_r30++) {
        if (var_r30->unk00 != -1) {
            TakeBallCoinPosSet(var_r30, &sp8);
        }
    }
}

static void TakeBallCoinPosSet(BallTakeCoinData *arg0, Vec *arg1) {
    if (arg1->y > arg0->unk04.y + 50.0f) {
        BoardModelKill(arg0->unk00);
        arg0->unk00 = -1;
        return;
    }
    PSVECAdd(&arg0->unk04, &arg0->unk10, &arg0->unk04);
    PSVECAdd(&arg0->unk04, &arg0->unk1C, &arg0->unk04);
    arg0->unk10.y += -0.98f;
    BoardModelPosSetV(arg0->unk00, &arg0->unk04);
}

BOOL CheckBallCoinDone(void) {
    BallTakeCoinData *var_r31;
    s32 i;

    if (!ballTakeCoinObj) {
        return TRUE;
    }
    var_r31 = ballTakeCoinObj->data;
    for (i = 0; i < 10; i++, var_r31++) {
        if (var_r31->unk00 > 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void TakeBallStar(void) {
    BallTakeCoinWork *temp_r31;
    Vec sp8;

    ballTakeCoinObj = omAddObjEx(boardObjMan, 0x1003, 0, 0, -1, ExecTakeBallStar);
    temp_r31 = OM_GET_WORK_PTR(ballTakeCoinObj, BallTakeCoinWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk01 = 0;
    temp_r31->unk02 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 11), 0, 0);
    BoardPlayerPosGet(stealTarget, &sp8);
    ballTakeCoinObj->trans.x = sp8.x;
    ballTakeCoinObj->trans.y = sp8.y + 150.0f;
    ballTakeCoinObj->trans.z = sp8.z;
    temp_r31->unk04 = sp8.y;
    ballTakeCoinObj->rot.x = 3.0 * sind(80);
    ballTakeCoinObj->rot.z = 3.0 * cosd(80);
    ballTakeCoinObj->rot.y = 0.0f;
    BoardModelPosSet(temp_r31->unk02, ballTakeCoinObj->trans.x, ballTakeCoinObj->trans.y, ballTakeCoinObj->trans.z);
    BoardModelVisibilitySet(temp_r31->unk02, 1);
    BoardModelCameraSet(temp_r31->unk02, 1);
    fn_8006DDE8(temp_r31->unk02, -1.0f);
    BoardModelScaleSet(temp_r31->unk02, 0.5f, 0.5f, 0.5f);
    HuAudFXPlay(0x361);
}

void ExecTakeBallStar(omObjData *arg0) {
    BallTakeCoinWork *temp_r29 = OM_GET_WORK_PTR(arg0, BallTakeCoinWork);
    Vec sp8;
    float var_f30;

    if (temp_r29->unk00_field0 != 0) {
        if (arg0->data) {
            HuMemDirectFree(arg0->data);
            arg0->data = NULL;
        }
        BoardModelKill(temp_r29->unk02);
        ballTakeCoinObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    BoardPlayerPosGet(stealTarget, &sp8);
    temp_r29->unk01++;
    OSu8tof32(&temp_r29->unk01, &var_f30);
    arg0->trans.x += arg0->rot.x;
    arg0->trans.z += arg0->rot.z;
    arg0->trans.y += 20.0f + var_f30 * var_f30 * -0.08166667f * 0.3f;
    arg0->rot.y = BoardDAngleCalc(arg0->rot.y + 24.0f);
    if (temp_r29->unk04 > arg0->trans.y) {
        temp_r29->unk00_field0 = 1;
    }
    BoardModelPosSet(temp_r29->unk02, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotYSet(temp_r29->unk02, arg0->rot.y);
}

BOOL CheckTakeBallStarDone(void) {
    if (ballTakeCoinObj) {
        return FALSE;
    } else {
        return TRUE;
    }
}

s32 BoardBooStealValueGet(s16 *arg0, s16 *arg1) {
    if (stealType == 2) {
        return 0;
    }
    *arg0 = stealValue;
    *arg1 = stealSuccess;
    return 1;
}

BOOL BoardBooStealLightCheck(void) {
    if (stealType == 2) {
        return FALSE;
    } else {
        return TRUE;
    }
}

static s8 stealSuccessTbl[][3] = {
    {  0,  0, 0 },
    {  1,  6, 1 },
    {  7,  7, 3 },
    {  8, 12, 2 },
    { 13, 15, 3 },
    { 16, 18, 4 },
    { 19, 20, 6 },
    { 21, 23, 5 },
    { 24, 26, 6 },
    { 27, 28, 7 },
    { 29, 29, 8 },
    { 30, 99, 9 }
};

static s8 stealTbl[][3] = {
    {  1,  5, 15 },
    {  6, 15, 25 },
    { 16, 25, 27 },
    { 26, 35, 30 },
    { 36, 45, 32 },
    { 46, 50, 35 }
};

static void UpdatePlayerCoins(void) {
    s32 sp8;
    s32 var_r29;
    s32 var_r30;
    s32 i;

    sp8 = punchCount;
    if (punchCount > 99) {
        punchCount = 99;
    }
    var_r30 = GWSystem.turn;
    if (var_r30 > 50) {
        var_r30 = 50;
    }
    for (stealSuccess = i = 0; i < 12; i++) {
        if (punchCount >= stealSuccessTbl[i][0] && punchCount <= stealSuccessTbl[i][1]) {
            stealSuccess = stealSuccessTbl[i][2];
            break;
        }
    }
    for (var_r29 = i = 0; i < 6; i++) {
        if (var_r30 >= stealTbl[i][0] && var_r30 <= stealTbl[i][1]) {
            var_r29 = stealTbl[i][2];
            break;
        }
    }
    stealValue = var_r29 - stealSuccess;
    if (BoardPlayerCoinsGet(stealTarget) < stealValue) {
        stealValue = BoardPlayerCoinsGet(stealTarget);
    }
    BoardPlayerCoinsAdd(stealTarget, -stealValue);
}
