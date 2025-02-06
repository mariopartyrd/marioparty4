#include "game/board/battle.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/board/audio.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/tutorial.h"
#include "game/board/ui.h"
#include "game/board/window.h"

#include "ext_math.h"

typedef struct {
    struct {
        u8 isBoardVisible : 1;
        u8 state : 2;
    };
    s8 delay;
    s16 bombModel;
    s16 expModels[4];
} ExplodeWork;

typedef struct {
    struct {
        u8 isBoardVisible : 1;
        u8 state : 4;
        u8 hasExploded : 1;
        u8 unk00_field3 : 1;
    };
    u8 scale;
    s8 unk02;
    s8 unk03;
    s8 unk04;
    s16 unk08;
} BattleWork;

extern s32 BoardMGSetupPlaySearch(s32, s16);
extern void BoardMGSetupPlayPush(s32, s16);

static void DestroyBattle(void);
static void ExecBattle(void);
static void TakeCoins(void);
static void InitExplode(void);
static s32 CheckExplode(void);
static void UpdateExplode(omObjData *arg0);
static void CreateBattleMain(void);
static void UpdateBattleMain(omObjData *arg0);
static void DescendBattleBomb(BattleWork *arg0, omObjData *arg1);
static void EndBattle(BattleWork *arg0, omObjData *arg1);
static void ShowBattleGame(BattleWork *arg0, omObjData *arg1);
static void RaiseBattleGame(BattleWork *arg0, omObjData *arg1);
static void UpdateBattleCoin(BattleWork *arg0, omObjData *arg1);
static void ShowBattleCoin(BattleWork *arg0, omObjData *arg1);
static void InitBattleGameSpr(BattleWork *arg0, omObjData *arg1);
static void HideBattleSpr(void);
static void VibratePad(BattleWork *arg0, omObjData *arg1);
static void StopBattleBomb(void);
static s32 GetBattleBombState(void);
static void SetBattleBombState(s32 arg0);
static void SetBattleCoinValue(void);

static s16 battleMGList[8];

static s8 currPlayer;
static s8 coinTakeMax;
static u8 mgChoice;
static s16 currSpace;
static s8 battleCoinIdx;
static s8 battleMGIdx[2];
static char totalCoinStr[8];
static float battleCoinSpeed;
static float battleCoinPosF;
static omObjData *explodeObj;
static omObjData *battleObj;
static Process *battleProc;

static const s8 battleCoinTbl[] = {
    5, 10, 20, 30, 50
};

static float battleCursorPosTbl[] = {
    144.0f, 330.0f, 0.0f,
    432.0f, 330.0f, 0.0f
};

static s32 bombFXTbl[] = {
    0x00000123,
    0x00000163,
    0x000001A3,
    0x000001E3,
    0x00000223,
    0x00000263,
    0x000002A3,
    0x000002E3
};

static s16 battleSprPrioTbl[] = {
    1000, 990, 1000, 980,
     980, 970,  970, 970,
     970, 970,  970
};

void BoardBattleExec(s32 player, s32 space) {
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        HuAudFXPlay(0x34A);
        BoardCameraViewSet(2);
        BoardPlayerMotBlendSet(player, 0, 0xF);
        while (!BoardPlayerMotBlendCheck(player)) {
            HuPrcVSleep();
        }
        BoardCameraMotionWait();
        BoardTutorialHookExec(0xF, 0);
        GWPlayer[player].color = 3;
        return;
    }
    currPlayer = player;
    currSpace = space;
    battleProc = HuPrcChildCreate(ExecBattle, 0x2004, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(battleProc, DestroyBattle);
    while (battleProc) {
        HuPrcVSleep();
    }
    GWPlayer[player].color = 3;
}

static void DestroyBattle(void) {
    HuDataDirClose(DATADIR_BBATTLE);
    battleProc = NULL;
}

static void ExecBattle(void) {
    s16 temp_r28;
    s16 var_r26;
    s32 temp_r22;
    s32 var_r21;
    s32 var_r30;
    s32 var_r31;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    MgInfo *var_r29;
    s32 var_r27 = 0;
    s32 sp8[] = {
        DATADIR_W01,
        DATADIR_W02,
        DATADIR_W03,
        DATADIR_W04,
        DATADIR_W05,
        DATADIR_W06,
        DATADIR_W10,
        DATADIR_W20,
        DATADIR_W21
    };

    var_r29 = mgInfoTbl;
    for (var_r31 = var_r30 = 0; var_r29->ovl != (u16) OVL_INVALID; var_r29++, var_r31++) {
        if (var_r29->type == 4) {
            battleMGList[var_r30] = var_r31 + 401;
            var_r30++;
        }
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        while (1) {
            var_r31 = BoardRandMod(6);
            temp_r28 = battleMGList[var_r31];
            if (GWMGListGet() == 2) {
                if (GWMGCustomGet(temp_r28) == 0) {
                    continue;
                }
            } else {
                if (GWMGListGet() == 1) {
                    var_r29 = &mgInfoTbl[temp_r28 - 401];
                    if (!(var_r29->flag & 1)) {
                        continue;
                    }
                } else if (BoardMGSetupPlaySearch(4, temp_r28) != 0) {
                    continue;
                }
            }
            if (var_r30 == 1 && var_r31 == battleMGIdx[var_r30 - 1]) {
                continue;
            }
            break;
        }
        battleMGIdx[var_r30] = var_r31;
        BoardMGSetupPlayPush(4, temp_r28);
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 4))) {
        BoardStatusItemSet(1);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        _ClearFlag(FLAG_ID_MAKE(1, 28));
        HuPrcSleep(60);
        HuPrcEnd();
    }
    HuAudFXPlay(0x34A);
    omVibrate(GWSystem.player_curr, 12, 6, 6);
    BoardAudSeqPause(0, 1, 500);
    temp_r22 = BoardDataDirReadAsync(DATADIR_BBATTLE);
    BoardCameraViewSet(3);
    BoardCameraMotionWait();
    BoardPlayerMotBlendSet(currPlayer, 0, 0xF);
    while (!BoardPlayerMotBlendCheck(currPlayer)) {
        HuPrcVSleep();
    }
    BoardDataAsyncWait(temp_r22);
    SetBattleCoinValue();
    BoardMusStart(1, 4, 0x7F, 0);
    omVibrate(GWSystem.player_curr, 12, 6, 6);
    InitExplode();
    while (CheckExplode() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    CreateBattleMain();
    while (GetBattleBombState() != 8) {
        HuPrcVSleep();
    }
    var_r26 = 0;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (BoardPlayerCoinsGet(var_r31) >= 10) {
            var_r26 = 1;
            break;
        }
    }
    if (var_r26 == 0) {
        BoardWinCreate(2, MAKE_MESSID(2, 1), 1);
        BoardWinWait();
        BoardWinKill();
        var_r27 = 1;
    } else {
        HuAudFXPlay(0x4F);
        BoardWinCreate(2, MAKE_MESSID(2, 0), 1);
        BoardWinWait();
        BoardWinKill();
        SetBattleBombState(3);
        while (GetBattleBombState() != 8) {
            HuPrcVSleep();
        }
        SetBattleBombState(4);
        while (GetBattleBombState() != 8) {
            HuPrcVSleep();
        }
        TakeCoins();
        if (GWPlayer[currPlayer].com) {
            if (BoardRandFloat() < 0.5f) {
                var_r23 = 0;
            } else {
                var_r23 = 1;
            }
            var_r25 = var_r23;
            HuPrcSleep(60);
        } else {
            var_r25 = -1;
        }
        SetBattleBombState(5);
        BoardPickerCreate(currPlayer, 2, battleCursorPosTbl, var_r25);
        BoardPickerBackFlagSet(0);
        while (!BoardPickerDoneCheck()) {
            HuPrcVSleep();
        }
        mgChoice = BoardPickerChoiceGet();
        SetBattleBombState(6);
        while (GetBattleBombState() != 8) {
            HuPrcVSleep();
        }
        BoardAudSeqFadeOut(1, 1000);
        BoardMusVolPanSet(0, 0, 1);
        BoardAudSeqPause(0, 0, 1);
        if (var_r27 == 0) {
            HuDataDirClose(DATADIR_BOARD);
            HuDataDirClose(DATADIR_BGUEST);
            HuDataDirClose(sp8[GWBoardGet()]);
            HuPrcSleep(2);
            temp_r28 = battleMGList[battleMGIdx[mgChoice]];
            GWMGAvailSet(temp_r28);
            GWSystem.mg_next = temp_r28 - 401;
            if (_CheckFlag(FLAG_ID_MAKE(0, 11))) {
                var_r24 = DATADIR_INST;
            } else {
                var_r24 = mgInfoTbl[temp_r28 - 401].data_dir;
            }
            var_r21 = BoardDataDirReadAsync(var_r24);
        }
        _SetFlag(FLAG_ID_MAKE(1, 14));
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        HuAudFXAllStop();
        _SetFlag(FLAG_ID_MAKE(1, 28));
        HideBattleSpr();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            BoardPlayerMotionStart(var_r31, 1, 0x40000001);
        }
        BoardDataAsyncWait(var_r21);
        if (var_r27 == 0) {
            _SetFlag(FLAG_ID_MAKE(1, 4));
            BoardNextOvlSet(OVL_INST);
            BoardFilterFadeOut(30);
            StopBattleBomb();
            HuPrcEnd();
        }
    }
    BoardAudSeqFadeOut(1, 1000);
    SetBattleBombState(1);
    while (GetBattleBombState() != 8) {
        HuPrcVSleep();
    }
    StopBattleBomb();
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        BoardPlayerIdleSet(var_r31);
        BoardPlayerVoiceEnableSet(var_r31, 6, 1);
    }
    BoardAudSeqPause(0, 0, 1000);
    HuPrcEnd();
}

static void TakeCoins(void) {
    u16 var_r30;
    s32 temp_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 i;

    for (var_r30 = i = 0; i < 4; i++) {
        temp_r26 = BoardPlayerCoinsGet(i);
        if (temp_r26 >= coinTakeMax) {
            var_r30 += coinTakeMax;
        } else {
            var_r30 += temp_r26;
        }
    }
    if (coinTakeMax >= 50) {
        var_r27 = 1;
    } else if (coinTakeMax >= 20) {
        var_r27 = 3;
    } else {
        var_r27 = 6;
    }
    for (i = 0; i < 4; i++) {
        if (BoardPlayerCoinsGet(i) < coinTakeMax) {
            var_r25 = BoardPlayerCoinsGet(i);
        } else {
            var_r25 = coinTakeMax;
        }
        GWPlayer[i].coins_battle = var_r25;
    }
    for (var_r29 = 0; var_r29 < coinTakeMax; var_r29++) {
        for (var_r28 = i = 0; i < 4; i++) {
            BoardPlayerCoinsAdd(i, -1);
            var_r28 += BoardPlayerCoinsGet(i);
        }
        if (var_r28 <= 0) {
            break;
        }
        HuAudFXPlay(0xE);
        HuPrcSleep(var_r27);
    }
    HuAudFXPlay(0xF);
    sprintf(totalCoinStr, "%d", var_r30);
    if (var_r30 != coinTakeMax * 4) {
        var_r24 = MAKE_MESSID(2, 3);
    } else {
        var_r24 = MAKE_MESSID(2, 2);
    }
    BoardWinCreate(2, var_r24, 1);
    BoardWinInsertMesSet(MAKE_MESSID_PTR(totalCoinStr), 0);
    BoardWinWait();
    BoardWinKill();
}

static void InitExplode(void) {
    Vec sp14;
    Vec sp8;
    s32 i;
    ExplodeWork *temp_r31;
    float sp20[4][2] = {
        { -50.0f, -50.0f },
        {  50.0f, -50.0f },
        { -50.0f,  50.0f },
        {  50.0f,  50.0f }
    };

    BoardPlayerPosGet(currPlayer, &sp14);
    explodeObj = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, UpdateExplode);
    temp_r31 = OM_GET_WORK_PTR(explodeObj, ExplodeWork);
    temp_r31->isBoardVisible = 0;
    temp_r31->state = 0;
    temp_r31->delay = 0x10;
    temp_r31->bombModel = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 38), NULL, 0);
    BoardModelLayerSet(temp_r31->bombModel, 2);
    explodeObj->trans.x = sp14.x;
    explodeObj->trans.y = sp14.y - 100.0f;
    explodeObj->trans.z = sp14.z;
    BoardModelPosSet(temp_r31->bombModel, explodeObj->trans.x, explodeObj->trans.y, explodeObj->trans.z);
    BoardModelMotionStart(temp_r31->bombModel, 0, 0x40000001);
    for (i = 0; i < 4; i++) {
        temp_r31->expModels[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 102), NULL, 0);
        sp8.x = sp14.x + sp20[i][0];
        sp8.y = sp14.y;
        sp8.z = sp14.z + sp20[i][1];
        BoardModelPosSetV(temp_r31->expModels[i], &sp8);
        BoardModelLayerSet(temp_r31->expModels[i], 2);
    }
    HuAudFXPlay(0x33C);
}

static s32 CheckExplode(void) {
    ExplodeWork *temp_r31 = OM_GET_WORK_PTR(explodeObj, ExplodeWork);

    return temp_r31->state;
}

static void UpdateExplode(omObjData *arg0) {
    Vec sp14;
    Vec sp8;
    float temp_f31;
    ExplodeWork *temp_r30;
    Mtx sp20;
    s32 i;

    (void) 1000.0f; // TODO: 1000.0f needs to appear right before 20.0f in sdata2 to match.
    temp_r30 = OM_GET_WORK_PTR(arg0, ExplodeWork);
    if (temp_r30->isBoardVisible != 0 || BoardIsKill()) {
        BoardModelKill(temp_r30->bombModel);
        for (i = 0; i < 4; i++) {
            BoardModelKill(temp_r30->expModels[i]);
        }
        explodeObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    switch (temp_r30->state) {
        case 0:
            if (temp_r30->delay == 0) {
                for (i = 0; i < 4; i++) {
                    if (currSpace == GWPlayer[i].space_curr) {
                        temp_f31 = 20.0f * BoardRandFloat();
                        HuAudFXPlay(bombFXTbl[GWPlayer[i].character]);
                        BoardPlayerMotionShiftSet(i, 6, temp_f31, 8.0f, HU3D_MOTATTR_LOOP);
                    }
                }
                CharModelLayerSetAll(2);
            }
            if (temp_r30->delay-- <= 0) {
                arg0->trans.y += 50.0f;
                if (arg0->trans.y >= 800.0f) {
                    arg0->scale.x = 288.0f;
                    arg0->scale.y = -128.0f;
                    arg0->scale.z = 1000.0f;
                    for (i = 0; i < 4; i++) {
                        BoardModelVisibilitySet(temp_r30->expModels[i], 0);
                    }
                    temp_r30->state = 2;
                }
            }
            break;
        case 3:
            BoardModelVisibilitySet(temp_r30->bombModel, 0);
            temp_r30->isBoardVisible = 1;
            break;
        case 2:
            BoardCameraRotGet(&sp8);
            PSMTXRotRad(sp20, 'x', MTXDegToRad(sp8.x + 10.0f));
            BoardModelMtxSet(temp_r30->bombModel, &sp20);
            BoardModelRotSet(temp_r30->bombModel, 0.0f, 0.0f, 0.0f);
            sp14.x = arg0->scale.x;
            sp14.y = arg0->scale.y;
            sp14.z = arg0->scale.z;
            Hu3D2Dto3D(&sp14, 1, &sp14);
            arg0->trans.x = sp14.x;
            arg0->trans.y = sp14.y;
            arg0->trans.z = sp14.z;
            break;
    }
    BoardModelPosSet(temp_r30->bombModel, arg0->trans.x, arg0->trans.y, arg0->trans.z);
}

static void CreateBattleMain(void) {
    s16 sp8;
    s32 var_r29;
    s32 i;
    BattleWork *temp_r31;
    s32 spC[] = {
        DATA_MAKE_NUM(DATADIR_BBATTLE, 0),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 1),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 2),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 3),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 3),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 4),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 5),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 6),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 7),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 8),
        DATA_MAKE_NUM(DATADIR_BBATTLE, 9)
    };

    battleObj = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, UpdateBattleMain);
    temp_r31 = OM_GET_WORK_PTR(battleObj, BattleWork);
    temp_r31->isBoardVisible = 0;
    temp_r31->hasExploded = 0;
    temp_r31->scale = 0;
    temp_r31->unk02 = 2;
    temp_r31->unk03 = 2;
    temp_r31->unk04 = 0;
    temp_r31->unk00_field3 = 0;
    temp_r31->state = 0;
    battleCoinSpeed = 1.0f;
    battleCoinPosF = 5.0f * BoardRandFloat();
    coinTakeMax = 0;
    temp_r31->unk08 = HuSprGrpCreate(11);
    for (i = 0; i < 11; i++) {
        var_r29 = spC[i];
        BoardSpriteCreate(var_r29, battleSprPrioTbl[i], 0, &sp8);
        HuSprGrpMemberSet(temp_r31->unk08, i, sp8);
        HuSprAttrSet(temp_r31->unk08, i, 9);
        HuSprAttrSet(temp_r31->unk08, i, 4);
    }
    HuSprGrpPosSet(temp_r31->unk08, 288.0f, 240.0f);
    battleObj->trans.x = -308.0f;
    BoardFilterFadeInit(30, 0xA0);
}

static void UpdateBattleMain(omObjData *arg0) {
    BattleWork *temp_r30;
    ExplodeWork *temp_r29;
    float var_f31;

    temp_r30 = OM_GET_WORK_PTR(arg0, BattleWork);
    if (temp_r30->isBoardVisible != 0 || BoardIsKill()) {
        HuSprGrpKill(temp_r30->unk08);
        battleObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    switch (temp_r30->state) {
        case 0:
            DescendBattleBomb(temp_r30, arg0);
            break;
        case 1:
            EndBattle(temp_r30, arg0);
            break;
        case 2:
            ShowBattleGame(temp_r30, arg0);
            break;
        case 3:
            RaiseBattleGame(temp_r30, arg0);
            break;
        case 4:
            UpdateBattleCoin(temp_r30, arg0);
            break;
        case 5:
            InitBattleGameSpr(temp_r30, arg0);
            break;
        case 6:
            VibratePad(temp_r30, arg0);
            break;
        case 7:
            ShowBattleCoin(temp_r30, arg0);
            break;
        case 8:
            break;
    }
    var_f31 = arg0->trans.x + 240.0f;
    temp_r29 = OM_GET_WORK_PTR(explodeObj, ExplodeWork);
    if (temp_r29->state == 2) {
        explodeObj->scale.x = 288.0f;
        explodeObj->scale.y = var_f31;
        explodeObj->scale.z = 1000.0f;
    }
    HuSprPosSet(temp_r30->unk08, 0, 0.0f, arg0->trans.y);
    HuSprScaleSet(temp_r30->unk08, 0, arg0->trans.z, arg0->trans.z);
}

static void DescendBattleBomb(BattleWork *arg0, omObjData *arg1) {
    float temp_f31 = -132.0f - arg1->trans.x;

    if (temp_f31 < 0.1f) {
        arg1->trans.x = -132.0f;
        arg0->state = 2;
    } else {
        arg1->trans.x += 0.3f * temp_f31;
    }
}

static void EndBattle(BattleWork *arg0, omObjData *arg1) {
    float temp_f31 = 548.0f - arg1->trans.x;

    if (temp_f31 < 0.1f) {
        BoardFilterFadeOut(30);
        arg0->state = 8;
    } else {
        arg1->trans.x += 0.3f * temp_f31;
    }
}

static void ShowBattleGame(BattleWork *arg0, omObjData *arg1) {
    float var_r29;

    if (arg0->scale == 0) {
        if (BoardFilterFadePauseCheck()) {
            arg0->scale = 1;
            arg1->trans.z = 0.01f;
            arg1->trans.y = 0.0f;
            HuSprAttrReset(arg0->unk08, 0, HUSPR_ATTR_DISPOFF);
            HuSprPosSet(arg0->unk08, 0, 0.0f, 0.0f);
        } else {
            return;
        }
    }
    if (arg0->scale >= 90) {
        arg0->state = 8;
        arg0->scale = 90;
    }
    OSs8tof32((s8*) &arg0->scale, &var_r29);
    arg1->trans.z = sind(var_r29);
    arg0->scale += 4;
}

static void RaiseBattleGame(BattleWork *arg0, omObjData *arg1) {
    float temp_f31 = -60.0f - arg1->trans.y;

    if (ABS(temp_f31) < 0.1f) {
        arg1->trans.y = -60.0f;
        arg0->state = 8;
    } else {
        arg1->trans.y += 0.2f * temp_f31;
    }
}

static void UpdateBattleCoin(BattleWork *arg0, omObjData *arg1) {
    s8 temp_r28;

    if (arg0->hasExploded != 0) {
        if (arg0->unk03++ < arg0->unk02) {
            arg0->unk04++;
            if (arg0->unk04 > 20) {
                arg0->unk04 = 20;
            }
            return;
        }
        if (arg0->unk00_field3 == 0 && arg0->unk04 >= 20 && BoardRandMod(100) > 50) {
            arg0->unk00_field3 = 1;
        }
        arg0->unk03 = 0;
        if (arg0->unk00_field3 != 0) {
            arg0->unk02 += 4;
            if (arg0->unk02 > 30) {
                arg0->unk02 = 30;
            }
        }
        OSf32tos8(&battleCoinPosF, &temp_r28);
        if (arg0->unk02 >= 30 && temp_r28 == battleCoinIdx) {
            arg0->state = 7;
            arg0->scale = 0;
            coinTakeMax = battleCoinTbl[temp_r28];
            HuAudFXPlay(0x305);
        } else {
            battleCoinPosF += 1.0f;
            HuAudFXPlay(0x304);
            if (battleCoinPosF >= 5.0f) {
                battleCoinPosF = 0.0f;
            }
        }
        HuSprBankSet(arg0->unk08, 1, temp_r28);
        return;
    }
    HuSprAttrReset(arg0->unk08, 2, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(arg0->unk08, 1, HUSPR_ATTR_NOANIM | HUSPR_ATTR_DISPOFF);
    HuSprPosSet(arg0->unk08, 2, 0.0f, 40.0f);
    HuSprPosSet(arg0->unk08, 1, 34.0f, 40.0f);
    HuSprScaleSet(arg0->unk08, 1, 0.9f, 0.9f);
    arg0->hasExploded = 1;
    arg0->scale = 0;
    arg1->rot.x = 50.0f;
}

static void ShowBattleCoin(BattleWork *arg0, omObjData *arg1) {
    float scale2;
    float scale;

    if (arg0->scale >= 90) {
        arg0->scale = 0;
        arg0->state = 8;
        scale = 90.0f;
    } else {
        arg0->scale++;
        OSu8tof32(&arg0->scale, &scale);
    }
    if (coinTakeMax != 50) {
        scale *= 6.0f;
    } else {
        scale *= 10.0f;
    }
    while (scale > 180.0f) {
        scale -= 180.0f;
    }
    scale2 = 0.9f + sind(scale);
    HuSprScaleSet(arg0->unk08, 1, scale2, scale2);
}

static void InitBattleGameSpr(BattleWork *arg0, omObjData *arg1) {
    s8 temp_r30;
    s8 temp_r29;
    float sp8[2][2] = {
        { -130.0f, 30.0f },
        {  130.0f, 30.0f }
    };

    temp_r30 = battleMGIdx[0];
    temp_r29 = battleMGIdx[1];
    HuSprAttrReset(arg0->unk08, 3, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(arg0->unk08, 4, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(arg0->unk08, temp_r30 + 5, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(arg0->unk08, temp_r29 + 5, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(arg0->unk08, 3, sp8[0][0], sp8[0][1]);
    HuSprPosSet(arg0->unk08, 4, sp8[1][0], sp8[1][1]);
    HuSprPosSet(arg0->unk08, temp_r30 + 5, sp8[0][0], sp8[0][1]);
    HuSprPosSet(arg0->unk08, temp_r29 + 5, sp8[1][0], sp8[1][1]);
    arg0->state = 8;
}

static void HideBattleSpr(void) {
    BattleWork *temp_r30 = OM_GET_WORK_PTR(battleObj, BattleWork);
    s32 i;

    for (i = 0; i < 11; i++) {
        HuSprAttrSet(temp_r30->unk08, i, 4);
    }
}


static void VibratePad(BattleWork *arg0, omObjData *arg1) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omVibrate(i, 12, 0xC, 0);
    }
    arg0->state = 8;
}

static void StopBattleBomb(void) {
    if (battleObj) {
        OM_GET_WORK_PTR(battleObj, BattleWork)->isBoardVisible = 1;
    }
}

static s32 GetBattleBombState(void) {
    return OM_GET_WORK_PTR(battleObj, BattleWork)->state;
}

static void SetBattleBombState(s32 arg0) {
    BattleWork *var_r31 = OM_GET_WORK_PTR(battleObj, BattleWork);

    var_r31->state = arg0;
    var_r31->scale = 0;
}

static s8 battleChanceTbl[][3][5] = {
    {
        { 10, 85,  5, 0, 0 },
        { 10, 75, 15, 0, 0 },
        { 10, 65, 25, 0, 0 },
    },
    {
        { 5, 70, 20,  5, 0 },
        { 5, 60, 25, 10, 0 },
        { 5, 50, 30, 10, 0 },
    },
    {
        { 5, 60, 20, 10,  5 },
        { 5, 45, 30, 15,  5 },
        { 5, 35, 30, 20, 10 },
    },
    {
        { 5, 45, 30, 15,  5 },
        { 5, 30, 35, 20, 10 },
        { 5, 20, 35, 25, 15 }
    }
};

static void SetBattleCoinValue(void) {
    s32 temp_r26;
    s32 temp_r25;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    s32 var_r27;
    s32 i;

    var_r30 = -1;
    for (i = 0; i < 4; i++) {
        if (BoardPlayerCoinsGet(i) > var_r30) {
            var_r30 = BoardPlayerCoinsGet(i);
        }
    }
    if (var_r30 >= 50) {
        var_r29 = 3;
    } else if (var_r30 >= 30) {
        var_r29 = 2;
    } else if (var_r30 >= 20) {
        var_r29 = 1;
    } else {
        var_r29 = 0;
    }
    temp_r25 = 3.0f * ((float) GWSystem.turn / GWSystem.max_turn);
    temp_r26 = BoardRandMod(100);
    var_r27 = var_r28 = 0;
    for (i = 4; i >= 0; i--) {
        var_r28 += battleChanceTbl[var_r29][temp_r25][i];
        if (temp_r26 < var_r28) {
            var_r27 = i;
            break;
        }
    }
    battleCoinIdx = var_r27;
}
