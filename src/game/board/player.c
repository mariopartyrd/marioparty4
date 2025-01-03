#include "game/board/player.h"

#include "ext_math.h"
#include "game/board/audio.h"
#include "game/board/basic_space.h"
#include "game/board/com.h"
#include "game/board/item.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/roll.h"
#include "game/board/space.h"
#include "game/board/tutorial.h"
#include "game/board/ui.h"
#include "game/board/view.h"
#include "game/chrman.h"
#include "game/disp.h"
#include "game/hsfman.h"
#include "game/objsub.h"
#include "game/pad.h"

#include "math.h"
#include "stdlib.h"

static void InitJunction(s32, s32, f32);
static void UpdateJunctionGfx(omObjData *);
static void StopJunctionPlayer(s32);
static void RestoreJunction(f32, s32);

static s32 GetDefaultDirection(f32, f32 *, s32);
static s32 DoDebugMove(s32, s16 *);
static s32 ExecJunction(s32, s16 *);

static void PlayerPosLerpFunc(omObjData *);
static void DiceJumpFunc(omObjData *);

static void UpdateRollSprite(omObjData *);
static void UpdateRoll(omObjData *);
static void MoveAwayObjFunc(omObjData *);

static void MoveAwayObjFunc(omObjData *);
static void UpdateBowserSuit(omObjData *);

static void MegaSquishFunc(omObjData *object);

static s32 DoSparkSpace(s32 player, s32 pause_cam);
static void RemoveSparkSpace(s32 player);
static void SetPlayerSizeAuto(s32 player);
static s32 MegaPlayerPassFunc(s32 player, s32 space);
static s32 MegaExecJump(s32 player, s32 space);

// TODO: Give better name
typedef struct bitcopy {
    struct {
        u8 field00_bit0 : 1;
        u8 field00_bit1 : 2;
        u8 field00_bit3 : 2;
        u8 field00_bit5 : 2;
        u8 field00_bit7 : 1;
    };
    u8 unk_01;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06[5];
} bitcopy;

static HsfMaterial *playerMatCopy[4];
static s32 (*postTurnHook[4])();
static s32 (*preTurnHook[4])();

s16 boardPlayerMdl[4];
static s16 playerMot[4];
static s8 itemPrev;
static s8 moveAwayPlayer[4];
static s16 junctionArrowRot[4];
static omObjData *moveAwayObj;
static omObjData *rollObj;
static omObjData *junctionObj;
static s32 junctionMask;
static omObjData *bowserSuitObj;
static s32 megaDoubleDiceF;

static s16 suitMdl = -1;
static s16 suitPlayerMdl = -1;
static s16 suitCurrMot = -1;

static omObjData *diceJumpObj[4] = { 0, 0, 0, 0 };
static omObjData *motDoneF[4] = { 0, 0, 0, 0 };
static s16 bowserSuitMot[5] = { -1, -1, -1, -1, -1 };
static char *eyeMatTbl[8][2]
    = { { "eye1", "eye2" }, { "eye1", "eye2" }, { "mat14", "mat16" }, { "eye1", "eye2" }, { "Clswario_eye_l1_AUTO14", "Clswario_eye_l1_AUTO15" },
          { "m_donkey_eye4", "m_donkey_eye5" }, { "mat65", "mat66" }, { "Clswaluigi_eye_l1_AUTO1", "Clswaluigi_eye_l1_AUTO2" } };

s32 lbl_8013997C[] = {
    0x10D,
    0x14D,
    0x18D,
    0x1CD,
    0x20D,
    0x24D,
    0x28D,
    0x2CD,
};

static s32 boardMotTbl[] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x35),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x35),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x35),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x35),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x35),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x35),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x35),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x35),
};

static s32 boardMotRevTbl[] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x36),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x36),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x36),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x36),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x36),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x36),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x36),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x36),
};

static s32 bowserSuitCharMdlTbl[] = {
    DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x00),
    DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x03),
    DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x06),
    DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x09),
    DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x0C),
    DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x0F),
    DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x12),
    DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x15),
};

static s32 bowserSuitMotTbl[] = { DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x19), DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x1A),
    DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x1B), DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x1E), DATA_MAKE_NUM(DATADIR_BKOOPASUIT, 0x1F) };

#if VERSION_JP
static s32 sparkMotTbl[] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x94),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x95),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x96),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x97),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x98),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x99),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x9A),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x9B),
};
#else
static s32 sparkMotTbl[] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x95),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x96),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x97),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x98),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x99),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x9A),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x9B),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x9C),
};
#endif

static s32 boardSparkSfxTbl[] = {
    0x128,
    0x168,
    0x1A8,
    0x1E8,
    0x228,
    0x268,
    0x2A8,
    0x2E8,
};

static s32 boardSparkSfxTblAlt[] = {
    0x123,
    0x163,
    0x1A3,
    0x1E3,
    0x223,
    0x263,
    0x2A3,
    0x2E3,
};

static omObjData *megaSquishObj[4] = {};

static s32 megaSquishSfxTbl[] = {
    0x128,
    0x168,
    0x1A8,
    0x1E8,
    0x228,
    0x268,
    0x2A8,
    0x2E8,
};

s32 BoardItemPrevGet(void)
{
    return itemPrev;
}

void BoardItemPrevSet(s32 type)
{
    itemPrev = type;
}

s32 BoardPlayerGetCharMess(s32 player)
{
    s32 charMess[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    return charMess[GWPlayer[player].character];
}

char *BoardPlayerGetCharName(s32 player)
{
    char *charNames[8] = { "Mario", "Luigi", "Peach", "Yoshi", "Wario", "Donky", "Daisy", "Waluigi" };
    return charNames[GWPlayer[player].character];
}

s32 BoardPlayerIsAllCom(void)
{
    if ((GWPlayer[0].com != 0) && (GWPlayer[1].com != 0) && (GWPlayer[2].com != 0) && (GWPlayer[3].com != 0)) {
        return 1;
    }
    return 0;
}

void BoardPlayerInit(void)
{
    s32 temp_r30;
    s32 var_r31;

    if (BoardStartCheck() == 0) {
        GWSystem.player_curr = 0;
        temp_r30 = BoardSpaceFlagPosGet(0, 0x80000000, 0);

        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            GWPlayer[var_r31].space_curr = temp_r30;
            BoardPlayerCornerPosSet(var_r31);
            BoardPlayerSizeSet(var_r31, 0);
            GWPlayer[var_r31].color = 0;
            GWPlayer[var_r31].bowser_suit = 0;
            GWPlayer[var_r31].draw_ticket = 0;
            GWPlayer[var_r31].jump = 0;
        }
        return;
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        BoardPlayerCornerPosSet(var_r31);
        if (BoardPlayerAutoSizeGet(var_r31) != 0) {
            BoardPlayerAutoSizeSet(var_r31, BoardPlayerAutoSizeGet(var_r31));
            BoardStatusHammerShowSet(var_r31, 0);
        }
    }
}

void BoardPlayerModelInit(void)
{
    s32 sp64[14];
    s32 var_r31;
    s32 var_r30;
    s32 temp_r29;
    s32 temp_r25;
    s32 temp_r24;
    s16 temp_r3;
    s32 temp_r4;
    PlayerState *temp_r27;

    s32 ro0[8] = { DATA_MAKE_NUM(DATADIR_MARIOMDL1, 0x00), DATA_MAKE_NUM(DATADIR_LUIGIMDL1, 0x00), DATA_MAKE_NUM(DATADIR_PEACHMDL1, 0x00),
        DATA_MAKE_NUM(DATADIR_YOSHIMDL1, 0x00), DATA_MAKE_NUM(DATADIR_WARIOMDL1, 0x00), DATA_MAKE_NUM(DATADIR_DONKEYMDL1, 0x00),
        DATA_MAKE_NUM(DATADIR_DAISYMDL1, 0), DATA_MAKE_NUM(DATADIR_WALUIGIMDL1, 0x00) };
    s32 ro1[8] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00), DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00), DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00) };
    u16 ro2[13] = { 0, 2, 3, 5, 6, 22, 23, 24, 27, 31, 47, 72, 73 };

    memset(&boardPlayerMdl, 0, 8);
    suitMdl = -1;
    suitPlayerMdl = -1;
    if ((_CheckFlag(FLAG_ID_MAKE(1, 5)) != 0) || (_CheckFlag(FLAG_ID_MAKE(1, 6)) && (GWBoardGet() == BOARD_ID_MAIN6))) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            temp_r25 = GWPlayer[var_r31].team_backup;
            GWPlayer[var_r31].team = temp_r25;
            GWPlayerCfg[var_r31].group = temp_r25;
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        preTurnHook[var_r31] = 0;
        postTurnHook[var_r31] = 0;
        motDoneF[var_r31] = 0;
        diceJumpObj[var_r31] = 0;
        temp_r27 = BoardPlayerGet(var_r31);
        temp_r29 = GWPlayerCfg[var_r31].character;
        temp_r27->player_idx = var_r31;
        GWPlayer[var_r31].character = temp_r29;
        GWPlayerCfg[var_r31].character = temp_r29;

        for (var_r30 = 0; var_r30 < 0xD; var_r30++) {
            sp64[var_r30] = ro1[temp_r29] | ro2[var_r30];
        }
        sp64[var_r30] = -1;
        temp_r3 = BoardModelCreateCharacter(temp_r29, ro0[temp_r29], sp64, 0);
        boardPlayerMdl[var_r31] = temp_r3;
        BoardPlayerCopyMat(var_r31);
        playerMot[var_r31] = 1;
        BoardModelMotionStart(temp_r3, playerMot[var_r31], 0x40000001);
        if (BoardStartCheck() == 0) {

            for (var_r30 = 0; var_r30 < 3; var_r30++) {
                temp_r27->items[var_r30] = -1;
            }
            temp_r24 = GWPlayerCfg[var_r31].group;
            GWPlayer[var_r31].team = temp_r24;
            GWPlayerCfg[var_r31].group = temp_r24;
        }
        GWPlayer[var_r31].show_next = 1;
        GWPlayer[var_r31].bowser_suit = 0;
        BoardModelExistDupe(temp_r3, 1);
        BoardModelExistCheck(temp_r3, 1);
        fn_8006DDE8(temp_r3, -1.0f);
        GWPlayer[var_r31].com = GWPlayerCfg[var_r31].iscom;
        GWPlayerCfg[var_r31].iscom = GWPlayerCfg[var_r31].iscom;
        GWPlayer[var_r31].port = GWPlayerCfg[var_r31].pad_idx;
        GWPlayerCfg[var_r31].pad_idx = GWPlayerCfg[var_r31].pad_idx;
        GWPlayer[var_r31].diff = GWPlayerCfg[var_r31].diff;
        GWPlayerCfg[var_r31].diff = GWPlayerCfg[var_r31].diff;
        temp_r27->space_prev = -1;
        CharModelDataClose(GWPlayer[var_r31].character);
    }
    CharModelLayerSetAll(2);
}

void BoardPlayerModelKill(void)
{
    s32 var_r31;
    PlayerState *temp_r30;
    PlayerState *temp_r29;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        temp_r30 = BoardPlayerGet(var_r31);
        if (boardPlayerMdl[temp_r30->player_idx] != -1) {
            BoardModelKill(boardPlayerMdl[temp_r30->player_idx]);
            boardPlayerMdl[temp_r30->player_idx] = -1;
        }
        if (playerMatCopy[var_r31] != 0) {
            HuMemDirectFree(playerMatCopy[var_r31]);
            playerMatCopy[var_r31] = 0;
        }
        BoardBowserSuitKill(var_r31);
    }
}

void BoardPlayerLayerSet(s32 arg0, s32 arg1)
{
    BoardModelLayerSet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerCameraSet(s32 arg0, u16 arg1)
{
    BoardModelCameraSet(BoardPlayerModelGet(arg0), arg1);
}

void fn_80062A40(s32 arg0, f32 arg8)
{
    fn_8006DDE8(BoardPlayerModelGet(arg0), arg8);
}

void BoardPlayerExistCheck(s32 arg0, s32 arg1)
{
    if (arg1 == 0) {
        BoardModelExistCheck(BoardPlayerModelGet(arg0), 0);
    }
    else {
        BoardModelExistCheck(BoardPlayerModelGet(arg0), 1);
    }
}

s32 BoardPlayerItemAdd(s32 arg0, s32 arg1)
{
    PlayerState *var_r30;
    s32 var_r29;
    s32 var_r31;

    var_r29 = -1;
    var_r30 = BoardPlayerGet(arg0);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        if (GWPlayer[arg0].items[var_r31] == -1) {
            HuAudFXPlay(0x360);
            var_r30->items[var_r31] = arg1;
            BoardItemStatusKill(arg0);
            var_r29 = var_r31;
            break;
        }
    }
    return var_r29;
}

s32 BoardPlayerItemRemove(s32 arg0, s32 arg1)
{
    s32 temp_r29;
    PlayerState *temp_r28;

    temp_r28 = BoardPlayerGet(arg0);
    temp_r29 = temp_r28->items[arg1];
    if (temp_r28->items[arg1] == -1) {
        return temp_r29;
    }
    if (arg1 == 0) {
        temp_r28->items[0] = temp_r28->items[1];
    }
    if ((arg1 == 1) || (arg1 == 0)) {
        temp_r28->items[1] = temp_r28->items[2];
    }
    temp_r28->items[2] = -1;
    HuAudFXPlay(0x363);
    BoardItemStatusKill(arg0);
    return temp_r29;
}

s32 BoardPlayerItemFind(s32 arg0, s32 arg1)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        if (arg1 == GWPlayer[arg0].items[var_r31]) {
            return var_r31;
        }
    }

    return -1;
}

s32 BoardPlayerItemCount(s32 arg0)
{
    s32 var_r30;
    s32 var_r31;

    for (var_r31 = 0, var_r30 = var_r31; var_r31 < 3; var_r31++) {
        if (GWPlayer[arg0].items[var_r31] != -1) {
            var_r30++;
        }
    }

    return var_r30;
}

void BoardPlayerCornerPosSet(s32 arg0)
{
    Vec sp8;

    BoardPlayerCornerPosGet(arg0, &sp8);
    BoardPlayerPosSetV(arg0, &sp8);
}

void BoardPlayerCornerPosGet(s32 arg0, Vec *arg1)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 temp_r28;

    if (arg1 != 0) {
        temp_r28 = GWPlayer[arg0].space_curr;
        var_r31 = GWSystem.player_curr;
        if (var_r31 == -1) {
            var_r31 = 0;
        }
        for (var_r30 = 0, var_r29 = var_r30; var_r30 < 4; var_r31 = (var_r31 + 1) & 3, var_r30++) {
            if (var_r31 == arg0)
                break;
            if (temp_r28 == GWPlayer[var_r31].space_curr) {
                var_r29 += 1;
            }
        }
        BoardSpaceCornerPosGet(temp_r28, var_r29, arg1);
    }
}

void BoardPlayerAmbSet(s32 arg0, f32 arg8, f32 arg9, f32 argA)
{
    BoardModelAmbSet(BoardPlayerModelGet(arg0), arg8, arg9, argA);
}

void BoardPlayerMtxSet(s32 arg0, Mtx *arg1)
{
    BoardModelMtxSet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerPosSetV(s32 arg0, Vec *arg1)
{
    BoardModelPosSetV(BoardPlayerModelGet(arg0), arg1);

    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelPosSetV(suitMdl, arg1);
    }
}

void BoardPlayerPosSet(s32 arg0, f32 arg8, f32 arg9, f32 argA)
{
    BoardModelPosSet(BoardPlayerModelGet(arg0), arg8, arg9, argA);

    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelPosSet(suitMdl, arg8, arg9, argA);
    }
}

void BoardPlayerPosGet(s32 arg0, Vec *arg1)
{
    BoardModelPosGet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerRotSetV(s32 arg0, Vec *arg1)
{
    BoardModelRotSetV(BoardPlayerModelGet(arg0), arg1);

    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelRotSetV(suitMdl, arg1);
    }
}

void BoardPlayerRotSet(s32 arg0, f32 arg8, f32 arg9, f32 argA)
{
    BoardModelRotSet(BoardPlayerModelGet(arg0), arg8, arg9, argA);

    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelRotSet(suitMdl, arg8, arg9, argA);
    }
}

void BoardPlayerRotGet(s32 arg0, Vec *arg1)
{
    BoardModelRotGet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerRotYSet(s32 arg0, f32 arg8)
{
    if (arg8 < 0.0f) {
        arg8 += 360.0f;
    }
    if (arg8 > 360.0f) {
        arg8 -= 360.0f;
    }
    BoardModelRotYSet(BoardPlayerModelGet(arg0), arg8);
    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelRotYSet(suitMdl, arg8);
    }
}

f32 BoardPlayerRotYGet(s32 arg0)
{
    f32 var_f31;

    if (GWPlayer[arg0].bowser_suit != 0) {
        var_f31 = BoardModelRotYGet(suitMdl);
    }
    else {
        var_f31 = BoardModelRotYGet(BoardPlayerModelGet(arg0));
    }
    return var_f31;
}

void BoardPlayerScaleSetV(s32 arg0, Vec *arg1)
{
    BoardModelScaleSetV(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerScaleSet(s32 arg0, f32 arg8, f32 arg9, f32 argA)
{
    BoardModelScaleSet(BoardPlayerModelGet(arg0), arg8, arg9, argA);
}

void BoardPlayerScaleGet(s32 arg0, Vec *arg1)
{
    BoardModelScaleGet(BoardPlayerModelGet(arg0), arg1);
}

s16 BoardPlayerCurrMotionGet(s32 arg0)
{
    PlayerState *player = BoardPlayerGet(arg0);

    return playerMot[player->player_idx];
}

void BoardPlayerVoiceEnableSet(s32 arg0, s32 arg1, s32 arg2)
{
    BoardModelVoiceEnableSet(BoardPlayerModelGet(arg0), arg1, arg2);
}

s32 BoardPlayerMotionCreate(s32 arg0, s32 arg1)
{
    return BoardModelMotionCreate(BoardPlayerModelGet(arg0), arg1);
}

s32 BoardPlayerMotionKill(s32 arg0, s32 arg1)
{
    return BoardModelMotionKill(BoardPlayerModelGet(arg0), arg1);
}

s32 BoardPlayerMotionEndCheck(s32 arg0)
{
    return BoardModelMotionEndCheck(BoardPlayerModelGet(arg0));
}

void BoardPlayerMotionEndWait(s32 arg0)
{
    while (BoardModelMotionEndCheck(BoardPlayerModelGet(arg0)) == 0) {
        HuPrcVSleep();
    }
}

void BoardPlayerMotionStart(s32 arg0, s32 arg1, s32 arg2)
{
    PlayerState *player;
    s32 temp_r29;

    player = BoardPlayerGet(arg0);
    if (arg1 == 0) { }
    if (arg1 != playerMot[player->player_idx]) {
        temp_r29 = BoardModelMotionStart(BoardPlayerModelGet(arg0), arg1, arg2);
        if (temp_r29 == 0) {
            playerMot[player->player_idx] = arg1;
        }
    }
}

void BoardPlayerMotionShiftSet(s32 arg0, s32 arg1, f32 arg8, f32 arg9, u32 arg2)
{
    s32 temp_r29;
    PlayerState *player;

    player = BoardPlayerGet(arg0);
    if (arg1 == 0) { }
    if (arg1 != playerMot[player->player_idx]) {
        temp_r29 = BoardModelMotionShiftSet(BoardPlayerModelGet(arg0), arg1, arg8, arg9, arg2);
        if (temp_r29 == 0) {
            playerMot[player->player_idx] = arg1;
        }
    }
}

void BoardPlayerMotionSpeedSet(s32 arg0, f32 arg8)
{
    BoardModelMotionSpeedSet(BoardPlayerModelGet(arg0), arg8);
}

void BoardPlayerMotionTimeSet(s32 arg0, f32 arg8)
{
    BoardModelMotionTimeSet(BoardPlayerModelGet(arg0), arg8);
}

f32 BoardPlayerMotionTimeGet(s32 arg0)
{
    return BoardModelMotionTimeGet(BoardPlayerModelGet(arg0));
}

f32 BoardPlayerMotionMaxTimeGet(s32 arg0)
{
    return BoardModelMotionMaxTimeGet(BoardPlayerModelGet(arg0));
}

void BoardPlayerMotionStartEndSet(s32 arg0, f32 arg8, f32 arg9)
{
    BoardModelMotionStartEndSet(BoardPlayerModelGet(arg0), arg8, arg9);
}

void BoardPlayerModelAttrSet(s32 arg0, s32 arg1)
{
    BoardModelAttrSet(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerModelAttrReset(s32 arg0, s32 arg1)
{
    BoardModelAttrReset(BoardPlayerModelGet(arg0), arg1);
}

void BoardPlayerCoinsSet(s32 arg0, s32 arg1)
{
    GWCoinsSet(arg0, arg1);
}

s32 BoardPlayerCoinsGet(s32 arg0)
{
    return GWCoinsGet(arg0);
}

void BoardPlayerCoinsAdd(s32 arg0, s32 arg1)
{
    PlayerState *player;
    s16 coins;

    player = BoardPlayerGet(arg0);
    if ((arg1 > 0) && (player->coins_total < 0x3E7)) {
        player->coins_total += arg1;
        if (player->coins_total > 0x3E7) {
            player->coins_total = 0x3E7;
        }
    }
    BoardPlayerCoinsSet(arg0, arg1 + BoardPlayerCoinsGet(arg0));
}

void BoardPlayerStarsAdd(s32 arg0, s32 arg1)
{
    GWStarsSet(arg0, (arg1 + GWStarsGet(arg0)));
}

void BoardPlayerSizeSet(s32 arg0, s32 arg1)
{
    PlayerState *temp_r27;
    Vec temp_r4[3] = { { 1, 1, 1 }, { 0.3, 0.3, 0.3 }, { 2.5, 2.5, 2.5 } };

    temp_r27 = BoardPlayerGet(arg0);
    temp_r27->size = arg1;
    if (arg1 == 2) {
        CharModelStepTypeSet(GWPlayer[arg0].character, 4);
    }
    else if (arg1 == 1) {
        CharModelStepTypeSet(GWPlayer[arg0].character, 5);
    }
    else {
        CharModelStepTypeSet(GWPlayer[arg0].character, 0);
    }
    BoardPlayerScaleSetV(arg0, &temp_r4[arg1]);
}

s32 BoardPlayerSizeGet(s32 idx)
{
    PlayerState *player;

    player = BoardPlayerGet(idx);
    if (!player) {
        return;
    }
    return player->size;
}

s32 BoardPlayerSameTeamFind(s32 arg0)
{
    s32 var_r31;
    s32 team2;
    s32 team;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r31 == arg0)
            continue;
        team2 = GWPlayer[var_r31].team;
        team = GWPlayer[arg0].team;
        if (team == team2)
            break;
    }
    return var_r31;
}

s32 BoardPlayerTeamFind(s32 arg0)
{
    s32 var_r31;
    s32 team2;
    s32 team;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r31 == arg0)
            continue;
        team2 = GWPlayer[var_r31].team;
        team = GWPlayer[arg0].team;
        if (team != team2)
            break;
    }
    return var_r31;
}

s32 BoardPlayerRankCalc(s32 player)
{
    s32 coins;
    s32 rank;
    s32 i;
    s32 score[4];

    for (i = 0; i < 4; i++) {
        coins = GWCoinsGet(i);
        score[i] = coins | (GWStarsGet(i) << 0xA);
    }
    for (rank = 0, i = 0; i < 4; i++) {
        if ((i != player) && (score[player] < score[i])) {
            rank++;
        }
    }
    return rank;
}

void BoardPlayerPreTurnHookSet(s32 arg0, s32 (*arg1)())
{
    preTurnHook[arg0] = arg1;
}

void BoardPlayerPostTurnHookSet(s32 arg0, s32 (*arg1)())
{
    postTurnHook[arg0] = arg1;
}

void BoardPlayerTurnExec(s32 arg0)
{
    BoardPauseDisableSet(1);
    BoardComUseItemSet(arg0, -1);
    GWSystem.bowser_event = 0xF;
    _ClearFlag(FLAG_ID_MAKE(1, 22));
    _ClearFlag(FLAG_ID_MAKE(1, 14));
    BoardCameraMoveSet(1);
    if (_CheckFlag(FLAG_ID_MAKE(1, 6)) == 0) {
        BoardCameraViewSet(2);
        omVibrate((s16)arg0, 0xC, 4, 2);
        BoardItemPrevSet(-1);
        BoardYourTurnExec(arg0);
        megaDoubleDiceF = 0;
        SetPlayerSizeAuto(arg0);
        if (preTurnHook[arg0] != 0U) {
            if (preTurnHook[arg0]() != 0) {
                preTurnHook[arg0] = 0;
            }
        }
        if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
            BoardTutorialHookExec(5, 0);
        }
        BoardPlayerTurnRollExec(arg0);
    }
    else {
        BoardCameraViewSet(1);
        BoardCameraMotionWait();
    }
    BoardPlayerTurnMoveExec(arg0);
}

void BoardPlayerTurnRollExec(s32 arg0)
{
    s32 temp_r28;
    s32 temp_r30;

    GWPlayer[arg0].roll = 0;
    GWPlayer[arg0].num_dice = 1;
    BoardPauseDisableSet(0);
    do {
        temp_r30 = BoardRollExec(arg0);
        switch (temp_r30) {
            case -2:
                BoardPauseDisableSet(1);
                BoardRollKill();
                BoardCameraTargetPlayerSet(arg0);
                BoardCameraMotionWait();
                BoardItemPrevSet(BoardItemUseExec(arg0));
                if (BoardItemPrevGet() == 0xC) {
                    _SetFlag(0x10016);
                    BoardSpaceLandExec(arg0, GWPlayer[arg0].space_curr);
                    BoardCameraMoveSet(1);
                    BoardCameraViewSet(2);
                    _ClearFlag(0x10016);
                }
                BoardPauseDisableSet(0);
                break;
            case -3:
                BoardRollKill();
                BoardViewMapExec(arg0);
                break;
            case -4:
                BoardRollKill();
                BoardViewOverheadExec(arg0);
                break;
        }
    } while (temp_r30 <= 0);
}

void BoardPlayerTurnMoveExec(s32 arg0)
{
    s16 sp8;
    u32 temp_r27;
    s32 temp_r30;
    s32 var_r29;
    s32 var_r28;
    s32 temp_r0;
    s32 temp_r1;

    BoardPauseDisableSet(1);
    var_r28 = 0;
    if (_CheckFlag(FLAG_ID_MAKE(1, 6)) == 0) {
        BoardCameraMoveSet(1);
        var_r29 = 1;
        BoardCameraViewSet(1);
        BoardCameraMotionWait();
        sp8 = -1;
        GWPlayer[arg0].space_next = -1;
        if (GWPlayer[arg0].bowser_suit != 0) {
            BoardCameraTargetModelSet(suitMdl);
            BoardCameraOffsetSet(0.0f, 100.0f, 0.0f);
        }
    }
    else {
        var_r29 = 0;
        var_r28 = 1;
        _ClearFlag(FLAG_ID_MAKE(1, 6));
        _ClearFlag(FLAG_ID_MAKE(1, 7));
        sp8 = GWPlayer[arg0].space_next;
        goto block_14;
    }
    do {
        BoardPauseDisableSet(1);
        GWPlayer[arg0].space_prev = GWPlayer[arg0].space_curr;
        if (_CheckFlag(FLAG_ID_MAKE(2, 1)) == 0) {
            if (ExecJunction(arg0, &sp8) != 0) {
                break;
            }
        }
        else if (DoDebugMove(arg0, &sp8) != 0) {
            break;
        }

        GWPlayer[arg0].space_next = sp8;
        StopJunctionPlayer(0);
        if (MegaPlayerPassFunc(arg0, sp8) == 0) {
            BoardPauseDisableSet(0);
            BoardPlayerMoveTo(arg0, sp8);
            BoardPauseDisableSet(1);
        }
        GWPlayer[arg0].space_prev = GWPlayer[arg0].space_curr;
        GWPlayer[arg0].space_curr = sp8;
        if (var_r29 != 0) {
            BoardPlayerMoveAwayStartCurr(GWPlayer[arg0].space_prev, 0);
            var_r29 = 0;
        }
        DoSparkSpace(arg0, 0);
        if (BoardSpaceWalkEventExec() != 0) {
            continue;
        }
        if (BoardSpaceWalkExec(arg0, sp8) != 0) {
            continue;
        }
    block_14:
        temp_r30 = BoardSpaceTypeGet(0, sp8);
        temp_r27 = BoardSpaceFlagGet(0, sp8);
        if ((temp_r30 == 0 || temp_r30 == 8 || temp_r30 == 10) && ((temp_r27 & 0x20000000) == 0) || var_r28 != 0) {
            var_r28 = 0;
            continue;
        }
        HuAudFXPlay(0x301);

        if (--GWPlayer[arg0].roll == 0)
            break;
    } while (1);
    BoardPauseDisableSet(1);
    BoardRollUpdateSet(arg0);
    BoardPlayerIdleSet(arg0);
    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardCameraTargetPlayerSet(arg0);
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        BoardTutorialHookExec(7, 0);
    }
    if (BoardItemPrevGet() != -1) {
        BoardItemPlayerRestore(arg0, BoardItemPrevGet());
        while (BoardItemDoneCheck() == 0) {
            HuPrcVSleep();
        }
        BoardItemPrevSet(-1);
    }
    BoardPlayerSizeRestore(arg0);
    megaDoubleDiceF = 0;
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        BoardTutorialHookExec(8, 0);
    }
    BoardSpaceBlockExec(arg0, sp8);
    BoardSpaceLandExec(arg0, sp8);
    _SetFlag(FLAG_ID_MAKE(1, 14));
    if (GWSystem.bowser_event != 1) {
        BoardCameraViewSet(2);
        BoardCameraMotionWait();
    }
    else {
        GWSystem.bowser_event = 0xF;
    }
    BoardPlayerZoomRestore(arg0);
    return;
}

void BoardPlayerPostTurnHookExec(s32 arg0)
{
    if (postTurnHook[arg0] != 0U) {
        if (postTurnHook[arg0]() != 0) {
            postTurnHook[arg0] = 0;
        }
    }
}

void BoardPlayerSizeRestore(s32 arg0)
{
    if (BoardPlayerSizeGet(arg0) != 0) {
        if (BoardPlayerSizeGet(arg0) == 1) {
            HuAudFXPlay(0x313);
        }
        else {
            HuAudFXPlay(0x311);
        }
        BoardPlayerResizeAnimExec(arg0, 0);
        BoardPlayerSizeSet(arg0, 0);

        while (BoardItemDoneCheck() == 0) {
            HuPrcVSleep();
        }
    }
}

void BoardPlayerZoomRestore(s32 arg0)
{
    PlayerState *sp8;
    s32 var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 temp_r27;
    Vec sp18;
    Vec spC;

    sp8 = BoardPlayerGet(arg0);
    BoardPlayerPosGet(arg0, &spC);
    temp_r27 = GWPlayer[arg0].space_curr;
    var_r31 = GWSystem.player_curr;
    if (var_r31 == -1) {
        var_r31 = 0;
    }
    for (var_r29 = var_r28 = 0; var_r28 < 4; var_r28++) {
        if (var_r31 == arg0)
            break;
        if (temp_r27 == GWPlayer[var_r31].space_curr) {
            var_r29++;
        }
        var_r31 = (var_r31 + 1) & 3;
    }
    BoardSpaceCornerPosGet(temp_r27, var_r29, &sp18);
    BoardPlayerMotBlendSet(arg0, 0, 0xF);

    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(arg0);
}

void BoardJunctionMaskSet(s32 arg0)
{
    junctionMask |= arg0;
}

void BoardJunctionMaskReset(s32 arg0)
{
    junctionMask &= ~arg0;
}

void BoardJunctionMaskZero(void)
{
    junctionMask = 0;
}

static inline u32 BoardJunctionMaskGet(void)
{
    return junctionMask;
}

static inline GetLinkCount(s32 playerIdx, s32 boardIdx)
{
    s32 i;
    s32 linkCount;
    BoardSpace *boardSpaceLink;
    BoardSpace *boardSpaceFlag;
    PlayerState *player;
    s32 color;
    s32 temp;

    linkCount = 0;
    boardSpaceLink = BoardSpaceGet(0, boardIdx);

    if (boardSpaceLink->link_cnt <= 1) {
        return 0;
    }
    linkCount = boardSpaceLink->link_cnt;
    for (i = 0; i < boardSpaceLink->link_cnt; i++) {
        boardSpaceFlag = BoardSpaceGet(0, boardSpaceLink->link[i]);
        if (((boardSpaceFlag->flag & 0x20000000) != 0 && (BoardPlayerSizeGet(playerIdx) != 1)) || ((boardSpaceFlag->flag & 0x02000000) != 0)
            || ((boardSpaceFlag->flag & 0x04000000) != 0) || ((boardSpaceFlag->flag & BoardJunctionMaskGet()) != 0)) {

            linkCount--;
        }
    }
    return linkCount;
}

static void InitJunction(s32 arg0, s32 arg1, f32 arg8)
{
    Vec sp68;
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    f32 sp3C[2];
    s32 sp38;
    s16 sp20;
    s16 spE;
    BoardSpace *temp_r26;
    BoardSpace *temp_r25;
    f32 var_f27;
    f32 var_f28;
    f32 var_f29;
    omObjData *var_r28;
    s32 var_r20;
    bitcopy *temp_r29;
    s32 var_r27;
    s32 var_r22;
    f32 angle;

    if (!junctionObj) {
        for (var_r20 = 0; var_r20 < 4; var_r20++) {
            junctionArrowRot[var_r20] = -1;
        }

        sp38 = GetLinkCount(arg0, arg1);
        if (sp38 > 1) {
            var_r28 = omAddObjEx(boardObjMan, 0x100, 0, 0, -1, UpdateJunctionGfx);
            junctionObj = var_r28;
            temp_r29 = OM_GET_WORK_PTR(var_r28, bitcopy);
            temp_r29->field00_bit0 = 0;
            temp_r29->field00_bit7 = 0;
            temp_r29->field00_bit1 = arg0;
            temp_r29->unk_02 = 0;
            temp_r29->field00_bit5 = 0;
            temp_r29->unk_01 = 0;
            var_r28->scale.x = var_r28->scale.y = var_r28->scale.z = 3.0f;
            HuWinMesMaxSizeGet(1, sp3C, MAKE_MESSID(0x9, 0x03));
            var_f27 = -10000.0f;
            var_f28 = 304.0f;
            temp_r29->unk_04 = HuWinCreate(var_f27, var_f28, sp3C[0], sp3C[1], 0);
            HuWinBGTPLvlSet(temp_r29->unk_04, 0.0f);
            HuWinMesSpeedSet(temp_r29->unk_04, 0);
            HuWinMesSet(temp_r29->unk_04, MAKE_MESSID(9, 3));
            if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
                HuWinDispOff(temp_r29->unk_04);
            }
            temp_r26 = BoardSpaceGet(0, arg1);
            BoardSpacePosGet(0, arg1, &sp68);
            spE = BoardPlayerSizeGet(arg0);

            for (var_r27 = 0, var_r22 = var_r27; var_r22 < temp_r26->link_cnt; var_r22++) {
                if (temp_r26->link[var_r22] != 0) {
                    temp_r25 = BoardSpaceGet(0, temp_r26->link[var_r22]);
                    if (((((temp_r25->flag & 0x20000000) == 0) != 0) || (spE == 1)) && ((temp_r25->flag & 0x02000000) == 0)
                        && ((temp_r25->flag & 0x04000000) == 0)) {
                        if ((temp_r25->flag & BoardJunctionMaskGet()) == 0) {
                            BoardSpacePosGet(0, temp_r26->link[var_r22], &sp50);
                            VECSubtract(&sp50, &sp68, &sp44);
                            VECNormalize(&sp44, &sp44);

                            angle = (180.0 * (atan2(sp44.x, sp44.z) / M_PI));
                            if (angle < 0.0f) {
                                angle += 360.0f;
                            }
                            if (angle > 360.0f) {
                                angle -= 360.0f;
                            }

                            OSf32tos16(&angle, &sp20);
                            sp20 = ((sp20 + 0x16) / 45) * 0x2D;
                            ;
                            junctionArrowRot[var_r27] = sp20;
                            var_f29 = 0.0f;
                            if (sp20 == 0) {
                                var_f29 = 100.0f;
                            }
                            else if ((sp20 == 0xB4) && ((spE == 2) || (GWPlayer[arg0].bowser_suit != 0))) {
                                var_f29 = -100.0f;
                            }
                            temp_r29->unk_06[var_r27] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0), NULL, 1);
                            BoardModelRotSet(temp_r29->unk_06[var_r27], 0.0f, angle, 0.0f);
                            BoardModelLayerSet(temp_r29->unk_06[var_r27], 6);
                            sp5C.x = sp68.x + (100.0 * sin((M_PI * angle) / 180.0));
                            sp5C.y = 300.0f + sp68.y;
                            sp5C.z = (var_f29 + (sp68.z + (100.0 * cosd(angle))));
                            BoardModelPosSetV(temp_r29->unk_06[var_r27], &sp5C);
                            BoardModelScaleSet(temp_r29->unk_06[var_r27], var_r28->scale.x, var_r28->scale.y, var_r28->scale.z);
                            var_r27++;
                        }
                    }
                }
            }
            temp_r29->field00_bit3 = var_r27;
            if (-1.0f != arg8) {
                RestoreJunction(arg8, 0);
            }
        }
    }
    return;
}

static void UpdateJunctionGfx(omObjData *arg0)
{
    s32 var_r28;
    bitcopy *temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0, bitcopy);
    if ((temp_r30->field00_bit0 != 0) || (BoardIsKill() != 0)) {
        for (var_r28 = 0; var_r28 < temp_r30->field00_bit3; var_r28++) {
            BoardModelKill(temp_r30->unk_06[var_r28]);
        }
        HuWinKill(temp_r30->unk_04);
        junctionObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r30->unk_01 != 0) {
        temp_r30->unk_01--;
    }
    else if (temp_r30->field00_bit7 != 0) {
        temp_r30->field00_bit0 = 1;
    }
    temp_r30->unk_02 += 8;
    if (temp_r30->unk_02 > 0xB4) {
        temp_r30->unk_02 -= 0xB4;
    }
    OSs16tof32(&temp_r30->unk_02, &arg0->scale.x);
    arg0->scale.x = 3.0 + sin((M_PI * arg0->scale.x) / 180.0);
    arg0->scale.y = arg0->scale.x;
    arg0->scale.z = arg0->scale.x;
    BoardModelScaleSet(temp_r30->unk_06[temp_r30->field00_bit5], arg0->scale.x, arg0->scale.y, arg0->scale.z);
}

static void StopJunctionPlayer(s32 arg0)
{
    bitcopy *temp_r31;

    if (junctionObj != 0) {
        temp_r31 = OM_GET_WORK_PTR(junctionObj, bitcopy);
        temp_r31->field00_bit7 = 1;
        temp_r31->unk_01 = 0;
        if (arg0 != 0) {
            HuAudFXPlay(2);
        }
        HuPrcSleep(0xA);
    }
}

static void RestoreJunction(f32 arg8, s32 arg0)
{
    Vec sp1C;
    f32 spC[4];
    s16 var_r30;
    s16 temp_r29;
    bitcopy *temp_r31;

    if (junctionObj != 0) {
        temp_r31 = OM_GET_WORK_PTR(junctionObj, bitcopy);
        if (temp_r31->unk_01 == 0) {
            arg8 = 90.0f * (((90.0f + arg8) - 1.0f) / 90.0f);

            for (var_r30 = 0; var_r30 < temp_r31->field00_bit3; var_r30++) {
                BoardModelRotGet(temp_r31->unk_06[var_r30], &sp1C);
                spC[var_r30] = 90.0f * (((90.0f + sp1C.y) - 1.0f) / 90.0f);
            }

            for (; var_r30 < 4; var_r30++) {
                spC[var_r30] = -999.0f;
            }

            temp_r29 = GetDefaultDirection(arg8, spC, temp_r31->field00_bit3);
            if ((temp_r29 != -1) && (temp_r31->field00_bit5 != temp_r29)) {
                temp_r31->field00_bit5 = temp_r29;
                if (arg0 != 0) {
                    HuAudFXPlay(0);
                }
                temp_r31->unk_01 = 0x14;
            }
        }
    }
}

static s32 GetDefaultDirection(f32 arg0, f32 *arg1, s32 arg2)
{
    f32 var_f27;
    f32 var_f28;
    f32 temp_f1;
    f32 temp_f30;
    s32 var_r30;
    s32 var_r31;

    temp_f30 = BoardDAngleCalc(arg0);
    var_f28 = 999.0f;

    for (var_r31 = 0, var_r30 = var_r31; var_r31 < arg2; var_r31++) {
        temp_f1 = BoardDAngleCalc(arg1[var_r31]);
        var_f27 = BOARD_FABS(BoardDAngleCalc(temp_f1 - temp_f30));

        if (var_f27 < var_f28) {
            var_f28 = var_f27;
            var_r30 = var_r31;
        }
    }
    return var_r30;
}

static inline s32 BoardPlayerMotGet(s32 player)
{
    PlayerState *player_ptr = BoardPlayerGet(player);
    return playerMot[player_ptr->player_idx];
}

static s32 DoDebugMove(s32 arg0, s16 *arg1)
{
    s16 spC0[10];
    s16 spAC[10];
    Vec spA0;
    Vec sp94;
    Vec sp88;
    Vec sp7C;
    BoardSpace *sp5C;
    s32 sp58;
    s32 sp54;
    BoardCameraData *sp50;
    f32 var_f30;
    s32 var_r29;
    s16 var_r26;
    PlayerState *sp28;
    BoardSpace *var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r18;
    bitcopy *var_r17;

    var_r18 = -1;

    memset(spC0, 0, 0x14);
    memset(spAC, 0, 0x14);
    while (1) {
    loop_1:
        sp28 = BoardPlayerGet(arg0);
        var_r23 = BoardSpaceGet(0, sp28->space_curr);
        sp58 = BoardSpaceCountGet(0);
        BoardPlayerPosGet(arg0, &sp88);
        var_r20 = GWPlayer[arg0].port;

        for (var_r22 = 0, var_r29 = var_r22; var_r29 < var_r23->link_cnt; var_r29++) {
            if ((BoardSpaceFlagGet(0, var_r23->link[var_r29]) & 0x06000000) == 0) {
                if ((BoardSpaceFlagGet(0, var_r23->link[var_r29]) & 0x20000000) == 0 || (BoardPlayerSizeGet(arg0) == 1)) {
                    spAC[var_r22++] = var_r23->link[var_r29];
                }
            }
        }
        var_r22 += BoardSpaceLinkTargetListGet(0, sp28->space_curr, &spAC[var_r22]);

        for (var_r29 = 0; var_r29 < var_r22; var_r29++) {
            sp5C = BoardSpaceGet(0, spAC[var_r29]);
            if (sp5C == 0) {
                spAC[var_r29] = 0;
            }
            else {
                VECSubtract(&sp5C->pos, &sp88, &sp94);
                var_f30 = 90.0 - (180.0 * (atan2(sp94.z, sp94.x) / M_PI));
                OSf32tos16(&var_f30, &var_r26);
                if (var_r26 < 0) {
                    var_r26 += 0x168;
                }
                if (var_r26 > 0x168) {
                    var_r26 -= 0x168;
                }

                spC0[var_r29] = var_r26 = var_r26 = (((var_r26 + 0x16) / 45) * 0x2D);
            }
        }
        sp54 = GWPlayer[arg0].space_curr;
        InitJunction(arg0, sp28->space_curr, -1.0f);
        do {
        loop_21:
            if (sp54 != GWPlayer[arg0].space_curr) {
                sp54 = GWPlayer[arg0].space_curr;
                goto loop_1;
            }
            spA0.x = HuPadStkX[var_r20];
            spA0.y = 0.0f;
            spA0.z = HuPadStkY[var_r20];
            if (HuPadBtnDown[var_r20] == 0x400) {
                StopJunctionPlayer(0);
                var_r18 = 1;
                goto end;
            }
            else {
                if (HuPadBtnDown[var_r20] == 0x10) {
                    BoardRollDispSet(0);
                    BoardPlayerIdleSet(arg0);
                    StopJunctionPlayer(0);
                    BoardViewMapExec(arg0);
                    InitJunction(arg0, sp28->space_curr, -1.0f);
                    BoardRollDispSet(1);
                    goto loop_21;
                }
                if ((0.0f != spA0.x) || (0.0f != spA0.z)) {
                    var_f30 = (90.0 + (180.0 * (atan2(spA0.z, spA0.x) / M_PI)));
                    if (var_f30 < 0.0f) {
                        var_f30 += 360.0f;
                    }
                    if (var_f30 > 360.0f) {
                        var_f30 -= 360.0f;
                    }
                    RestoreJunction(var_f30, 1);
                    sp50 = &boardCamera;
                    VECSubtract(&sp50->target, &sp50->pos, &sp7C);
                    var_f30 = (var_f30 + (90.0 - (180.0 * (atan2(-sp7C.z, -sp7C.x) / M_PI))));
                    if (var_f30 < 0.0f) {
                        var_f30 += 360.0f;
                    }
                    if (var_f30 > 360.0f) {
                        var_f30 -= 360.0f;
                    }
                    var_r21 = var_f30;

                    for (var_r29 = 0; var_r29 < var_r22; var_r29++) {
                        if ((spC0[var_r29] + 0x2D > var_r21) && (spC0[var_r29] - 0x2D < var_r21)) {
                            *arg1 = spAC[var_r29];
                            var_r18 = 0;
                            goto end;
                        }
                        else if ((var_r21 <= 0x168) && (var_r21 >= 0x13B) && ((s32)((&spC0[0])[var_r29] + 0x195) > var_r21)
                            && ((s32)((&spC0[0])[var_r29] + 0x13B) < var_r21)) {
                            *arg1 = spAC[var_r29];
                            var_r18 = 0;
                            goto end;
                        }
                    }
                }
                else {
                    if (BoardPlayerMotGet(arg0) != 1) {
                        BoardPlayerIdleSet(arg0);
                    }
                    if (GWPlayer[arg0].bowser_suit != 0) {
                        BoardBowserSuitMotionSetWait();
                        BoardBowserSuitPlayerModelKill();
                    }
                }
                HuPrcVSleep();
                goto loop_21;
            }
        } while (1);
    }
end:
    return var_r18;
}

static inline f32 JunctionArrowRotGetCurr(void)
{
    bitcopy *juncObj;
    f32 ret;

    if (!junctionObj) {
        return 0.0f;
    }
    else {
        juncObj = OM_GET_WORK_PTR(junctionObj, bitcopy);
        OSs16tof32(&(junctionArrowRot[juncObj->field00_bit5]), &ret);
        return ret;
    }
}

static inline s32 CheckArrowRot(float value)
{
    s32 sp58;
    bitcopy *sp5C;
    s16 spE;
    if (!junctionObj) {
        return 0;
    }
    else {
        sp5C = OM_GET_WORK_PTR(junctionObj, bitcopy);
        OSf32tos16(&value, &spE);
        if (spE > 0x15E) {
            spE = 0;
        }
        for (sp58 = 0; sp58 < sp5C->field00_bit3; sp58++) {
            if (abs(junctionArrowRot[sp58] - spE) <= 0x1E) {
                return 1;
            }
        }
        return 0;
    }
}

static s32 ExecJunction(s32 arg0, s16 *arg1)
{
    f32 spE4[10];
    s16 spD0[10];
    Vec spC4;
    Vec spB8;
    Vec spAC;
    s32 sp8C;
    BoardSpace *sp88;
    s32 sp84;
    PlayerState *sp30;
    s8 sp8;
    s32 var_r28;
    s32 var_r24;
    BoardSpace *var_r22;
    s32 var_r21;
    u32 var_r20;
    f32 var_f29;
    f32 var_f28;

    sp8C = -1;
    memset(spE4, 0, 40);
    memset(spD0, 0, 20);
    sp30 = BoardPlayerGet(arg0);
    var_r22 = BoardSpaceGet(0, sp30->space_curr);
    sp84 = BoardSpaceCountGet(0);
    BoardPlayerPosGet(arg0, &spAC);
    var_r24 = GWPlayer[arg0].port;

    for (var_r28 = var_r21 = 0; var_r28 < var_r22->link_cnt; var_r28++) {
        if ((BoardSpaceFlagGet(0, var_r22->link[var_r28]) & 0x06000000) == 0) {
            if ((BoardSpaceFlagGet(0, var_r22->link[var_r28]) & 0x20000000) == 0 || (BoardPlayerSizeGet(arg0) == 1)) {
                spD0[var_r21++] = var_r22->link[var_r28];
            }
        }
    }
    if (var_r21 == 1) {
        *arg1 = spD0[0];
        return 0;
    }
    if (var_r21 <= 0) {
        *arg1 = var_r22->link[0];
        return 0;
    }

    for (var_r28 = 0; var_r28 < var_r21; var_r28++) {
        sp88 = BoardSpaceGet(0, spD0[var_r28]);
        if (!sp88) {
            spD0[var_r28] = 0;
        }
        else {
            VECSubtract(&sp88->pos, &spAC, &spB8);
            var_f29 = (90.0 - (180.0 * (atan2(spB8.z, spB8.x) / M_PI)));
            if (var_f29 < 0.0f) {
                var_f29 += 360.0f;
            }
            if (var_f29 > 360.0f) {
                var_f29 -= 360.0f;
            }
            spE4[var_r28] = 45.0f * ((22.0f + var_f29) / 45.0f);
        }
    }
    var_f28 = -1.0f;
    sp8 = 0;
    InitJunction(arg0, sp30->space_curr, var_f28);
    BoardPlayerIdleSet(arg0);
    HuPrcSleep(10);
    while (1) {

        if ((_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) && (boardTutorialDirInputTime != -1)) {
            if (boardTutorialDirInputTime > 0) {
                spC4.x = boardTutorialDirInputX;
                spC4.z = boardTutorialDirInputY;
            }
            else {
                var_r20 = 0x100;
            }
            boardTutorialDirInputTime -= 1;
        }
        else if (GWPlayer[arg0].com != 0) {
            if (sp8 == 0) {
                BoardComJunctionInputGet(arg0, &spC4, var_r21, &spE4[0]);
                var_r20 = 0;
            }
            else if (sp8 > 6U) {
                var_r20 = 0x100;
            }
            sp8++;
        }
        else {
            if (abs(HuPadStkX[var_r24]) > 10) {
                spC4.x = HuPadStkX[var_r24];
            }
            else {
                spC4.x = 0.0f;
            }
            if (abs(HuPadStkY[var_r24]) > 10) {
                spC4.z = HuPadStkY[var_r24];
            }
            else {
                spC4.z = 0.0f;
            }
            var_r20 = HuPadBtnDown[var_r24];
        }
        if (var_r20 == 0x100) {
            var_f29 = JunctionArrowRotGetCurr();
            var_r28 = GetDefaultDirection(var_f29, spE4, var_r21);
            *arg1 = spD0[var_r28];
            StopJunctionPlayer(1);
            sp8C = 0;
            break;
        }
        else if (var_r20 == 0x20 || var_r20 == 0x10) {
            HuAudFXPlay(1);
            BoardRollDispSet(0);
            BoardPlayerIdleSet(arg0);
            StopJunctionPlayer(0);
            if (var_r20 == 0x10) {
                BoardViewMapExec(arg0);
            }
            else if (var_r20 == 0x20) {
                BoardViewOverheadExec(arg0);
            }
            InitJunction(arg0, sp30->space_curr, var_f28);
            BoardRollDispSet(1);
        }
        else {
            if ((0.0f != spC4.x) || (0.0f != spC4.z)) {
                var_f29 = (90.0 + (180.0 * (atan2(spC4.z, spC4.x) / M_PI)));
                if (var_f29 < 0.0f) {
                    var_f29 += 360.0f;
                }
                if (var_f29 > 360.0f) {
                    var_f29 -= 360.0f;
                }
                if (CheckArrowRot(var_f29) != 0) {
                    var_f28 = var_f29;
                    RestoreJunction(var_f29, 1);
                }

                for (var_r28 = 0; var_r28 < var_r21; var_r28++) {
                    if (((45.0f + spE4[var_r28]) > var_f29) && ((spE4[var_r28] - 45.0f) < var_f29)) {
                        *arg1 = (&spD0[0])[var_r28];
                    }
                    if (var_f29 <= 360.0f) {
                        if ((var_f29 >= 315.0f) && ((45.0f + (360.0f + spE4[var_r28])) > var_f29) && (((360.0f + spE4[var_r28]) - 45.0f) < var_f29)) {
                            *arg1 = spD0[var_r28];
                        }
                    }
                }
            }
            else {
                if (BoardPlayerMotGet(arg0) != 1) {
                    BoardPlayerIdleSet(arg0);
                }
                if (GWPlayer[arg0].bowser_suit != 0) {
                    BoardBowserSuitMotionSetWait();
                    BoardBowserSuitPlayerModelKill();
                }
            }
            HuPrcVSleep();
        }
    }
    return sp8C;
}

void BoardPlayerMoveTo(s32 arg0, s32 arg1)
{
    Vec sp18;
    Vec spC;
    PlayerState *player;

    BoardModelPosGet(BoardPlayerModelGet(arg0), &sp18);
    BoardSpacePosGet(0, arg1, &spC);
    BoardPlayerPosLerpStart(arg0, &sp18, &spC, 0x19);
    while (GWPlayer[arg0].moving != 0) {
        HuPrcVSleep();
    }
}

void BoardPlayerMoveBetween(s32 arg0, s32 arg1, s32 arg2)
{
    Vec sp1C;
    Vec sp10;
    s32 spC;
    s32 sp8;

    BoardSpacePosGet(0, arg1, &sp1C);
    BoardSpacePosGet(0, arg2, &sp10);
    BoardPlayerPosLerpStart(arg0, &sp1C, &sp10, 0x19);
    while (GWPlayer[arg0].moving != 0) {
        HuPrcVSleep();
    }
}

void BoardPlayerMoveToAsync(s32 arg0, s32 arg1)
{
    Vec sp18;
    Vec spC;
    s32 sp8;

    BoardModelPosGet(BoardPlayerModelGet(arg0), &sp18);
    BoardSpacePosGet(0, arg1, &spC);
    BoardPlayerPosLerpStart(arg0, &sp18, &spC, 0x19);
}

void BoardPlayerPosLerpStart(s32 arg0, Vec *arg1, Vec *arg2, s16 arg3)
{
    Vec sp18;
    f32 var_f28;
    f32 var_f27;
    f32 var_f26;
    f32 var_f29;
    f32 var_f30;
    omObjData *temp_r3;
    s32 var_r25;
    PlayerState *temp_r21;

    if ((arg1->x != arg2->x) || (arg1->y != arg2->y) || (arg1->z != arg2->z)) {
        var_f28 = BoardVecDistXZCalc(arg2, arg1);
        if (arg3 != 0) {
            if (GWPlayer[arg0].bowser_suit != 0) {
                arg3 *= 2;
            }

            OSs16tof32(&arg3, &var_f29);
            var_f27 = var_f28 / var_f29;
        }
        else {
            var_f27 = var_f28;
            var_f29 = 1.0f;
        }
        temp_r21 = BoardPlayerGet(arg0);

        if (playerMot[temp_r21->player_idx] != 3) {
            var_r25 = BoardModelMotionShiftSet(BoardPlayerModelGet(arg0), 3, 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            if (var_r25 == 0) {
                playerMot[temp_r21->player_idx] = 3;
            }
        }
        if (GWPlayer[arg0].bowser_suit != 0) {
            BoardBowserSuitMotionSetWalk();
            BoardModelMotionSpeedSet(suitMdl, 1.5f);
        }
        VECSubtract(arg2, arg1, &sp18);
        VECNormalize(&sp18, &sp18);
        var_f26 = 90.0 - (180.0 * (atan2(sp18.z, sp18.x) / M_PI));
        var_f30 = var_f26;
        if (var_f30 < 0.0f) {
            var_f30 += 360.0f;
        }
        if (var_f30 > 360.0f) {
            var_f30 -= 360.0f;
        }
        BoardModelRotYSet(BoardPlayerModelGet(arg0), var_f30);
        if (GWPlayer[arg0].bowser_suit != 0) {
            BoardModelRotYSet(suitMdl, var_f30);
        }
        temp_r3 = omAddObjEx(boardObjMan, 0x100, 0U, 0U, -1, &PlayerPosLerpFunc);
        temp_r3->trans.x = arg1->x;
        temp_r3->trans.y = arg1->y;
        temp_r3->trans.z = arg1->z;
        temp_r3->rot.x = arg2->x;
        temp_r3->rot.y = arg2->y;
        temp_r3->rot.z = arg2->z;
        temp_r3->scale.x = (arg2->x - arg1->x) / var_f29;
        temp_r3->scale.y = (arg2->y - arg1->y) / var_f29;
        temp_r3->scale.z = (arg2->z - arg1->z) / var_f29;
        BoardModelPosSetV(BoardPlayerModelGet(arg0), arg1);
        if (GWPlayer[arg0].bowser_suit != 0) {
            BoardModelPosSetV(suitMdl, arg1);
        }
        // TODO: Make work struct for this
        temp_r3->work[0] = arg0;
        *(f32 *)(&temp_r3->work[1]) = var_f27;
        temp_r3->work[2] = arg3;
        GWPlayer[arg0].moving = 1;
    }
}

static void PlayerPosLerpFunc(omObjData *arg0)
{
    f32 temp_f28;
    f32 temp_f27;
    f32 temp_f26;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    s32 temp_r30;

    temp_r30 = arg0->work[0];
    arg0->trans.x += arg0->scale.x;
    arg0->trans.y += arg0->scale.y;
    arg0->trans.z += arg0->scale.z;
    if (arg0->work[2] != 0U) {
        arg0->work[2] -= 1;
    }
    else {
        GWPlayer[temp_r30].moving = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        temp_f26 = arg0->rot.z;
        temp_f27 = arg0->rot.y;
        temp_f28 = arg0->rot.x;
        BoardPlayerPosSet(temp_r30, temp_f28, temp_f27, temp_f26);
        return;
    }
    temp_f29 = arg0->trans.z;
    temp_f30 = arg0->trans.y;
    temp_f31 = arg0->trans.x;
    BoardPlayerPosSet(temp_r30, temp_f31, temp_f30, temp_f29);
}

// TODO: Make this 2 structs and give better names
typedef struct bitcopy2 {
    struct {
        u8 field00_bit0 : 1;
        u8 field00_bit1 : 2;
        u8 field00_bit3 : 1;
        u8 field00_bit4 : 1;
        u8 field00_bit5 : 2;
        u8 field00_bit7 : 1;
    };
    s8 unk_01;
    s16 unk_02;
    union {
        struct {
            s32 unk_04;
            f32 unk_08;
            f32 unk_0C;
        };
        struct {
            s16 unk_04h;
            s16 unk_06h;
            s16 unk_08h;
            s16 unk_0Ah;
            s16 unk_0Ch;
            s16 unk_0Eh;
        };
    };
} bitcopy2;

void BoardPlayerDiceJumpStart(s32 arg0)
{
    Vec sp8;
    PlayerState *temp_r25;
    bitcopy2 *temp_r31;
    s32 var_r28;

    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardBowserSuitMotionSetJump();
    }
    temp_r25 = BoardPlayerGet(arg0);
    if (playerMot[temp_r25->player_idx] != 11) {
        var_r28 = BoardModelMotionStart(BoardPlayerModelGet(arg0), 11, 0);
        if (var_r28 == 0) {
            playerMot[temp_r25->player_idx] = 0xB;
        }
    }
    diceJumpObj[arg0] = omAddObjEx(boardObjMan, 0x100, 0, 0, -1, DiceJumpFunc);
    BoardModelPosGet(BoardPlayerModelGet(arg0), &sp8);
    temp_r31 = OM_GET_WORK_PTR(diceJumpObj[arg0], bitcopy2);
    temp_r31->field00_bit0 = 0;
    temp_r31->field00_bit1 = arg0;
    temp_r31->unk_04 = 0;
    temp_r31->field00_bit3 = 0;
    temp_r31->unk_08 = 0.0f;
    temp_r31->unk_0C = sp8.y;
    GWPlayer[arg0].jump = 1;
}

s32 BoardPlayerDiceJumpCheck(s32 arg0)
{
    if (!diceJumpObj[arg0]) {
        return 0;
    }
    if (OM_GET_WORK_PTR(diceJumpObj[arg0], bitcopy2)->unk_04 == 0) {
        return 0;
    }
    return 1;
}

static void DiceJumpFunc(omObjData *arg0)
{
    Vec sp38;
    f32 temp_f31;
    PlayerState *var_r30;
    bitcopy2 *temp_r31;
    s16 var_r28;
    s32 var_r23;
    s32 var_r17;

    temp_r31 = OM_GET_WORK_PTR(arg0, bitcopy2);
    if ((temp_r31->field00_bit0 != 0) || (BoardIsKill() != 0)) {
        GWPlayer[temp_r31->field00_bit1].jump = 0;
        BoardPlayerIdleSet(temp_r31->field00_bit1);
        diceJumpObj[temp_r31->field00_bit1] = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }

    if (BoardPlayerMotionEndCheck(temp_r31->field00_bit1)) {
        temp_r31->field00_bit0 = 1;
        return;
    }
    var_r28 = BoardModelIDGet(BoardPlayerModelGet(temp_r31->field00_bit1));
    if (Hu3DMotionShiftIDGet(var_r28) == -1) {
        temp_f31 = BoardPlayerMotionTimeGet(temp_r31->field00_bit1);
        if (BoardPlayerSizeGet(temp_r31->field00_bit1) == 1) {
            BoardPlayerPosGet(temp_r31->field00_bit1, &sp38);
            sp38.y += 10.0f + (-0.020416668f * temp_r31->unk_08 * temp_r31->unk_08);
            temp_r31->unk_08 += 1.0f;
            if (sp38.y < temp_r31->unk_0C) {
                sp38.y = temp_r31->unk_0C;
            }
            BoardPlayerPosSetV(temp_r31->field00_bit1, &sp38);
        }
        if (temp_r31->unk_04 != 0) {
            if (temp_f31 >= 35.0f) {
                temp_r31->unk_04 = 0;
                return;
            }
        }
        if (temp_r31->unk_04 == 0) {
            if (temp_f31 >= 30.0f) {
                temp_r31->unk_04 = 1;
                if (temp_r31->field00_bit3 == 0) {
                    omVibrate(temp_r31->field00_bit1, 0xC, 4, 2);
                    temp_r31->field00_bit3 = 1;
                }
                return;
            }
        }
    }
}

void BoardPlayerIdleSet(s32 arg0)
{
    if (GWPlayer[arg0].bowser_suit) {
        BoardBowserSuitMotionSetWait();
        BoardBowserSuitPlayerModelKill();
    }
    BoardPlayerMotionShiftSet(arg0, 1, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
}

static void ExecMotBlend(omObjData *arg0);

void BoardPlayerMotBlendSet(s32 arg0, s16 arg1, s16 arg2)
{
    s16 sp1C;
    f32 temp_f25;
    f32 temp_f26;
    f32 var_f24;
    f32 var_f27;
    f32 var_f22;
    f32 var_f21;
    f32 var_f19;
    omObjData *temp_r3;
    s32 var_r22;
    s32 var_r20;
    s16 var_r19;
    s16 var_r18;
    bitcopy2 *temp_r26;

    var_r20 = 0;
    if (motDoneF[arg0] != 0) {
        temp_r3 = motDoneF[arg0];
        temp_r26 = OM_GET_WORK_PTR(temp_r3, bitcopy2);
        temp_r26->field00_bit0 = 1;

        for (var_r19 = 0; var_r19 < 180U; var_r19++) {
            if (BoardPlayerMotBlendCheck(arg0) != 0)
                break;
            HuPrcVSleep();
        }
    }
    if (arg2 > 0) {
        var_r18 = GWPlayer[arg0].character;
        temp_r3 = omAddObjEx(boardObjMan, 0x100, 0, 0, -1, ExecMotBlend);
        temp_r26 = OM_GET_WORK_PTR(temp_r3, bitcopy2);
        temp_r26->field00_bit0 = 0;
        temp_r26->unk_02 = arg2;
        temp_r26->unk_01 = arg0;
        temp_r26->unk_04h = 0;
        OSs16tof32(&arg1, &temp_r26->unk_08);
        temp_r26->unk_08 = BoardDAngleCalc(temp_r26->unk_08);
        var_f22 = BoardDAngleCalc(BoardPlayerRotYGet(arg0));
        temp_f25 = BoardDAngleCalc(temp_r26->unk_08 - var_f22);
        OSf32tos16(&temp_f25, &sp1C);
        if (sp1C > 0) {
            var_f24 = 59.0f;
        }
        else {
            var_f24 = 0.0f;
        }

        if (abs(sp1C) == 0) {
            temp_r26->field00_bit0 = 1;
            return;
        }
        if (abs(sp1C) <= 90) {
            var_r20 = boardMotTbl[var_r18];
        }
        else if (abs(sp1C) <= 180) {
            var_r20 = boardMotRevTbl[var_r18];
        }
        else {
            temp_r26->field00_bit0 = 1;
            return;
        }
        temp_r26->unk_04h = BoardPlayerMotionCreate(arg0, var_r20);
        OSs16tof32(&arg2, &var_f27);
        temp_f26 = var_f27 / 59.0f;
        if (temp_f26 != 0.0f) {
            var_f27 = 1.0f / temp_f26;
        }
        else {
            var_f27 = 1.0f;
        }
        if (GWPlayer[arg0].bowser_suit != 0) {
            BoardBowserSuitMotionSetWalk();
            BoardModelMotionSpeedSet(BoardBowserSuitModelGet(), var_f27 / 2);
        }
        else if (var_f21 = 8.0f * temp_f26, abs(sp1C) > 45) {
            var_r22 = temp_r26->unk_04h;
            BoardPlayerMotionShiftSet(arg0, var_r22, var_f24, var_f21, HU3D_MOTATTR_NONE);
            BoardPlayerMotionSpeedSet(arg0, var_f27);
        }
        OSs16tof32(&arg2, &var_f27);
        temp_r26->unk_0C = temp_f25 / var_f27;
        motDoneF[arg0] = temp_r3;
    }
}

static void ExecMotBlend(omObjData *arg0)
{
    f32 sp48;
    f32 var_f27;
    bitcopy2 *temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0, bitcopy2);
    if ((temp_r30->field00_bit0 != 0) || (BoardIsKill() != 0)) {
        if (temp_r30->unk_04h > 0) {
            BoardPlayerMotionKill(temp_r30->unk_01, temp_r30->unk_04h);
        }
        BoardPlayerRotYSet(temp_r30->unk_01, temp_r30->unk_08);
        motDoneF[temp_r30->unk_01] = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r30->unk_02-- <= 0) {
        temp_r30->field00_bit0 = 1;
        BoardPlayerRotYSet(temp_r30->unk_01, temp_r30->unk_08);
        if (GWPlayer[temp_r30->unk_01].bowser_suit != 0) {
            BoardBowserSuitMotionSetWait();
            BoardBowserSuitPlayerModelKill();
        }
        else {
            BoardPlayerMotionStart(temp_r30->unk_01, 1, 0x40000001);
        }
        return;
    }
    var_f27 = BoardPlayerRotYGet(temp_r30->unk_01);
    OSs16tof32(&temp_r30->unk_08h, &sp48);
    var_f27 += temp_r30->unk_0C;
    BoardPlayerRotYSet(temp_r30->unk_01, var_f27);
}

s32 BoardPlayerMotBlendCheck(s32 arg0)
{
    if (motDoneF[arg0] != 0) {
        return 0;
    }
    return 1;
}

// TODO: Make this 3 structs and give better names

typedef struct bitcopy3 {
    struct {
        u8 field00_bit0 : 1;
        u8 field00_bit1 : 1;
        u8 field00_bit2 : 1;
        u8 field00_bit3 : 2;
        u8 field00_bit5 : 2;
        u8 field00_bit7 : 1;
    };
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s16 unk_04;
    s16 unk_06[5];
} bitcopy3;

void BoardRollCreate(s32 arg0, s32 arg1)
{
    omObjData *temp_r3;
    s32 var_r30;
    bitcopy3 *temp_r31;

    temp_r3 = omAddObjEx(boardObjMan, 0x105, 0, 0, -1, &UpdateRoll);
    temp_r31 = OM_GET_WORK_PTR(temp_r3, bitcopy3);
    temp_r31->field00_bit0 = 0;
    temp_r31->field00_bit1 = 1;
    temp_r31->unk_01 = 0;
    temp_r31->unk_02 = arg0;
    if (arg1 != 0) {
        temp_r31->unk_03 = 0;
    }
    else {
        temp_r31->unk_03 = 1;
    }
    temp_r31->unk_04 = HuSprGrpCreate(2);

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x2B), 0x4B0, 0, &temp_r31->unk_06[var_r30]);
        HuSprGrpMemberSet(temp_r31->unk_04, var_r30, temp_r31->unk_06[var_r30]);
        HuSprPosSet(temp_r31->unk_04, var_r30, HU_DISP_CENTERX, HU_DISP_CENTERY);
        HuSprAttrSet(temp_r31->unk_04, var_r30, 4);
    }
    rollObj = temp_r3;
}

void BoardRollUpdateSet(s32 arg0)
{
    bitcopy3 *temp_r31;

    if (rollObj != 0) {
        temp_r31 = OM_GET_WORK_PTR(rollObj, bitcopy3);
        temp_r31->field00_bit0 = 1;
    }
}

void BoardRollDispSet(s32 arg0)
{
    s32 var_r30;
    bitcopy3 *temp_r31;

    if (rollObj != 0) {
        temp_r31 = OM_GET_WORK_PTR(rollObj, bitcopy3);

        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            if (arg0 != 0) {
                temp_r31->field00_bit1 = 1;
                if ((var_r30 == 1) && (GWPlayer[temp_r31->unk_02].roll / 10 == 0)) {
                    HuSprAttrSet(temp_r31->unk_04, var_r30, HUSPR_ATTR_DISPOFF);
                }
                else {
                    HuSprAttrReset(temp_r31->unk_04, var_r30, HUSPR_ATTR_DISPOFF);
                }
            }
            else {
                temp_r31->field00_bit1 = 0;
                HuSprAttrSet(temp_r31->unk_04, var_r30, HUSPR_ATTR_DISPOFF);
            }
        }
        UpdateRollSprite(rollObj);
    }
}

static void UpdateRollSprite(omObjData *arg0)
{
    Vec sp1C;
    s32 sp14[2];
    f32 spC[2] = { HU_DISP_CENTERX + 32, HU_DISP_CENTERX - 32 };
    s32 var_r30;
    s32 temp_r29;
    bitcopy3 *temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, bitcopy3);
    temp_r29 = GWPlayer[temp_r31->unk_02].roll;
    if (temp_r29 != 0) {
        sp14[0] = temp_r29 % 10;
        sp14[1] = temp_r29 / 10;
    }
    else {
        temp_r31->field00_bit0 = 1;
    }

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        if (((var_r30 == 1) && (sp14[1] == 0)) || (temp_r31->field00_bit1 == 0)) {
            HuSprAttrSet(temp_r31->unk_04, var_r30, HUSPR_ATTR_DISPOFF);
        }
        else {
            if ((sp14[1] == 0) && (var_r30 == 0)) {
                sp1C.x = HU_DISP_CENTERX;
            }
            else {
                sp1C.x = spC[var_r30];
            }
            sp1C.y = (HU_DISP_HEIGHTF * 176) / 480;
            HuSprAttrReset(temp_r31->unk_04, var_r30, HUSPR_ATTR_DISPOFF);
            HuSprBankSet(temp_r31->unk_04, var_r30, sp14[var_r30]);
            HuSprPosSet(temp_r31->unk_04, var_r30, sp1C.x, sp1C.y);
        }
    }
}

static void UpdateRoll(omObjData *arg0)
{
    f32 var_f30;
    bitcopy3 *temp_r30;

    temp_r30 = OM_GET_WORK_PTR(rollObj, bitcopy3);
    if ((temp_r30->field00_bit0 != 0) || (BoardIsKill() != 0)) {
        if (temp_r30->unk_04 != -1) {
            HuSprGrpKill(temp_r30->unk_04);
            temp_r30->unk_04 = -1;
        }
        rollObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r30->unk_03 == 0) {
        temp_r30->unk_01 += 4;
        if (temp_r30->unk_01 >= 0x5A) {
            temp_r30->unk_03 = 1;
        }

        OSs8tof32(&temp_r30->unk_01, &var_f30);
        var_f30 *= 2.0f;
        if (var_f30 >= 90.0f) {
            var_f30 -= 90.0f;
        }
    }
    UpdateRollSprite(arg0);
}

void BoardPlayerBtnDownWait(s32 arg0, u32 arg1)
{
    s32 spC;
    s32 sp8;
    s32 temp_r31;

    temp_r31 = GWPlayer[arg0].port;
    while (1) {
        if ((HuPadBtnDown[temp_r31] & arg1) != 0)
            return;
        HuPrcVSleep();
    }
}

void BoardPlayerAutoSizeSet(s32 player, s32 value)
{
    PlayerState *temp_r28;

    temp_r28 = BoardPlayerGet(player);
    if ((temp_r28->auto_size != 0) || (value == 0)) {
        BoardStatusHammerKill(player);
    }
    temp_r28->auto_size = value;
    if (value != 0) {
        BoardStatusHammerCreate(player);
    }
}

s32 BoardPlayerAutoSizeGet(s32 arg0)
{
    PlayerState *player;

    player = BoardPlayerGet(arg0);
    if (!player) {
        return;
    }
    return player->auto_size;
}

u32 BoardPlayerMoveAwayIsDone(void)
{
    if (moveAwayObj) {
        return 0;
    }
    return 1;
}

void BoardPlayerMoveAwayStart(s32 arg0, s32 arg1, s32 arg2)
{
    bitcopy3 *temp_r25;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    s32 temp_r29;
    s32 var_r30;
    s32 var_r31;
    s32 var_r28;
    s32 var_r27;

    moveAwayPlayer[0] = moveAwayPlayer[1] = moveAwayPlayer[2] = moveAwayPlayer[3] = -1;
    var_r30 = arg0 + 1;

    var_r27 = 0;
    // hack
    for (var_r28 = var_r28 = var_r27; var_r27 < 4; var_r27++, var_r30++) {
        var_r30 &= 3;

        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if ((var_r31 == var_r30) && (arg1 == GWPlayer[var_r31].space_curr)) {
                moveAwayPlayer[var_r28++] = var_r31;
            }
        }
    }
    BoardSpaceRotGet(0, arg1, &sp28);

    for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
        BoardSpaceCornerPosGet(arg1, var_r31, &sp1C);
        temp_r29 = moveAwayPlayer[var_r31];
        if (arg2 != 0) {
            BoardPlayerPosSetV(temp_r29, &sp1C);
            moveAwayPlayer[var_r31] = -1;
        }
        else {
            BoardPlayerPosGet(temp_r29, &sp10);
            BoardPlayerPosLerpStart(temp_r29, &sp10, &sp1C, 0x19);
        }
    }
    if (arg2 == 0) {
        moveAwayObj = omAddObjEx(boardObjMan, 0x100, 0U, 0U, -1, &MoveAwayObjFunc);
        temp_r25 = OM_GET_WORK_PTR(moveAwayObj, bitcopy3);
        temp_r25->field00_bit0 = 0;
    }
}

void BoardPlayerMoveAwayStartCurr(s32 arg0, s32 arg1)
{
    BoardPlayerMoveAwayStart(GWSystem.player_curr, arg0, arg1);
}

static void MoveAwayObjFunc(omObjData *arg0)
{
    s32 var_r31;
    bitcopy3 *temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0, bitcopy3);
    if ((temp_r30->field00_bit0 != 0) || (BoardIsKill() != 0)) {
        moveAwayObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (moveAwayPlayer[var_r31] != -1) {
            if (GWPlayer[moveAwayPlayer[var_r31]].moving != 0)
                return;
            BoardPlayerMotBlendSet(moveAwayPlayer[var_r31], 0, 15);
            moveAwayPlayer[var_r31] = -1;
        }
    }
    temp_r30->field00_bit0 = 1;
}

void BoardBowserSuitInit(s32 arg0)
{
    omObjData *temp_r3;
    s32 temp_r27;
    s32 var_r29;
    s32 temp;
    bitcopy3 *temp_r31;

    for (var_r29 = 0; var_r29 < 4; var_r29++) { }
    temp_r27 = GWPlayer[arg0].character;
    temp = BoardDataDirReadAsync(0x40000);
    BoardDataAsyncWait(temp);
    suitMdl = BoardModelCreate(0x40018, NULL, 0);
    BoardModelScaleSet(suitMdl, 1.2f, 1.2f, 1.2f);
    suitPlayerMdl = BoardModelCreate(bowserSuitCharMdlTbl[temp_r27], NULL, 0);
    GWPlayer[arg0].bowser_suit = 1;
    temp_r3 = omAddObjEx(boardObjMan, 0x100, 0U, 0U, -1, &UpdateBowserSuit);
    bowserSuitObj = temp_r3;
    temp_r31 = OM_GET_WORK_PTR(temp_r3, bitcopy3);
    temp_r31->field00_bit0 = 0;
    temp_r31->unk_01 = arg0;
    temp_r31->unk_02 = 0;
    BoardPlayerVoiceEnableSet(arg0, 3, 0);
    BoardPlayerVoiceEnableSet(arg0, 4, 0);
}

void BoardBowserSuitKill(s32 arg0)
{
    bitcopy3 *temp;

    if (bowserSuitObj != 0) {
        OM_GET_WORK_PTR(bowserSuitObj, bitcopy3)->field00_bit0 = 1;
    }
    GWPlayer[arg0].bowser_suit = 0;
    BoardModelVoiceEnableSet(BoardPlayerModelGet(arg0), 3, 1);
    BoardModelVoiceEnableSet(BoardPlayerModelGet(arg0), 4, 1);
    if (suitMdl != -1) {
        BoardModelKill(suitMdl);
        suitMdl = -1;
    }
    if (suitPlayerMdl != -1) {
        BoardModelKill(suitPlayerMdl);
        suitPlayerMdl = -1;
    }
    HuDataDirClose(0x40000);
}

s16 BoardBowserSuitModelGet(void)
{
    return suitMdl;
}

s16 BoardBowserSuitPlayerModelGet(void)
{
    return suitPlayerMdl;
}

void BoardBowserSuitMotionCreate(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        bowserSuitMot[var_r31] = (s16)BoardModelMotionCreate(suitMdl, bowserSuitMotTbl[var_r31]);
    }
    suitCurrMot = -1;
}

void BoardBowserSuitMotionSetWait(void)
{
    if (suitCurrMot != 0) {
        BoardModelMotionShiftSet(suitMdl, bowserSuitMot[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
        suitCurrMot = 0;
    }
}

void BoardBowserSuitMotionSetWalk(void)
{
    if (suitCurrMot != 1) {
        BoardModelMotionStart(suitMdl, bowserSuitMot[1], 0x40000001);
        suitCurrMot = 1;
    }
}

void BoardBowserSuitMotionSetWin(void)
{
    BoardModelMotionShiftSet(suitMdl, bowserSuitMot[3], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
    suitCurrMot = 3;
}

void BoardBowserSuitMotionSetJump(void)
{
    BoardModelMotionShiftSet(suitMdl, bowserSuitMot[2], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
    suitCurrMot = 2;
}

void BoardBowserSuitPlayerModelKill(void)
{
    if (suitPlayerMdl != -1) {
        BoardModelMotionStart(suitPlayerMdl, 1, 0);
        BoardModelMotionSpeedSet(suitPlayerMdl, 0.0f);
    }
}

static void UpdateBowserSuit(omObjData *arg0)
{
    s16 temp_r30;
    bitcopy3 *temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, bitcopy3);
    if ((temp_r31->field00_bit0 != 0) || (BoardIsKill() != 0)) {
        bowserSuitObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if ((suitMdl != -1) && (suitCurrMot == 1)) {
        temp_r30 = BoardModelMotionTimeGet(suitMdl);
        if ((temp_r31->unk_02 == 0) && (((temp_r30 < 15.0f) && (temp_r30 >= 13.0f)) || ((temp_r30 < 40.0f) && (temp_r30 >= 38.0f)))) {
            HuAudFXPlay(0x328);
            temp_r31->unk_02 = 1;
        }
        if ((temp_r31->unk_02 != 0) && ((temp_r30 >= 20.0f) || (temp_r30 >= 49.0f))) {
            temp_r31->unk_02 = 0;
        }
    }
}

void BoardPlayerSparkSet(s32 arg0)
{
    s16 currSpace = GWPlayer[arg0].space_curr;

    GWPlayer[arg0].spark = 1;
    GWPlayer[arg0].space_shock = currSpace;
}

static s32 DoSparkSpace(s32 player, s32 pause_cam)
{
    s32 i;
    s16 temp_r28;
    s32 coin;
    s32 temp_r17;
    Vec pos, rot;
    Vec coin_pos;
    s16 sp15C[4] = { -1, -1, -1, -1 };
    s32 sp138;
    s32 sp134;
    s32 sp130;
    s32 sp12C;
    s32 sp128;
    s8 sp124[4] = { -1, -1, -1, -1 };
    s8 sp120[4] = { -1, -1, -1, -1 };
    s16 sp34;
    s16 sp32;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    sp30 = GWSystem.player_curr;
    sp138 = 0;
    sp34 = GWPlayer[player].space_curr;

    BoardSpacePosGet(0, sp34, &pos);
    BoardSpaceRotGet(0, sp34, &rot);
    for (i = 0; i < 4; i++) {
        if (GWPlayer[i].space_shock == sp34) {
            sp32 = i;
            sp138 = 1;
        }
    }
    if (!sp138) {
        return 0;
    }
    BoardRollDispSet(0);
    if (pause_cam) {
        BoardCameraMoveSet(0);
    }
    else {
        BoardCameraMoveSet(1);
    }
    BoardCameraMotionWait();
    BoardCameraTargetPlayerSet(player);
    BoardPlayerIdleSet(player);
    temp_r28 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, VERSION_JP ? 0x73 : 0x74), NULL, 0);
    BoardModelMotionStart(temp_r28, 0, 0x40000002);
    BoardModelMotionTimeSet(temp_r28, 30.0f);
    BoardModelAttrSet(temp_r28, 0x40000002);
    BoardModelRotSet(temp_r28, rot.x - 90.0f, rot.y, rot.z);
    BoardModelScaleSet(temp_r28, 2.0f, 2.0f, 2.0f);
    BoardModelVisibilitySet(temp_r28, 0);
    BoardModelLayerSet(temp_r28, 1);
    sp2E = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, VERSION_JP ? 0x66 : 0x67), NULL, 0);
    BoardModelLayerSet(sp2E, 1);
    BoardModelMotionStart(sp2E, 0, 0);
    HuAudFXPlay(796);
    HuPrcSleep(2);
    BoardModelAttrReset(temp_r28, 0x40000002);
    BoardModelVisibilitySet(temp_r28, 1);
    BoardModelPosSet(temp_r28, pos.x, 8.0f + pos.y, pos.z);
    BoardModelPosSetV(sp2E, &pos);
    sp128 = -1;
    for (sp134 = i = 0; i < 4; i++) {
        if (GWPlayer[i].space_curr == sp34) {
            sp124[sp134++] = i;
            sp15C[i] = BoardPlayerMotionCreate(i, sparkMotTbl[GWPlayer[i].character]);
            BoardPlayerMotionShiftSet(i, sp15C[i], 0, 8, HU3D_MOTATTR_NONE);
            HuAudFXPlay(boardSparkSfxTblAlt[GWPlayer[i].character]);
            if (GWPlayer[i].bowser_suit) {
                BoardModelMotionShiftSet(suitMdl, bowserSuitMot[4], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
                sp128 = i;
            }
        }
    }
    sp130 = sp134;
    HuPrcSleep(60);
    while (!BoardModelMotionEndCheck(sp2E)) {
        HuPrcVSleep();
    }
    sp2C = 255;
    for (i = 0; i < 45; i++) {
        sp2C -= 5;
        if (sp2C < 0) {
            sp2C = 0;
        }
        BoardModelAlphaSet(temp_r28, sp2C);
        BoardModelAlphaSet(sp2E, sp2C);
        HuPrcVSleep();
    }
    temp_r17 = BoardItemPrevGet();
    if (temp_r17 == 0 || temp_r17 == 1 || temp_r17 == 2 || temp_r17 == 3 || temp_r17 == 10) {
        BoardCameraTargetPlayerSet(player);
        BoardPlayerIdleSet(player);
        HuPrcSleep(12);
        BoardItemPlayerRestore(player, temp_r17);
        while (!BoardItemDoneCheck()) {
            HuPrcVSleep();
        }
        BoardItemPrevSet(-1);
    }
    if (megaDoubleDiceF) {
        BoardPlayerSizeRestore(player);
        megaDoubleDiceF = 0;
    }
    if (sp128 != -1) {
        HuAudFXPlay(boardSparkSfxTbl[GWPlayer[sp128].character]);
    }
    for (i = 0; i < sp130; i++) {
        coin = BoardPlayerCoinsGet(sp124[i]);
        if (coin > 10) {
            coin = 10;
        }
        if (coin > 0) {

            BoardPlayerPosGet(sp124[i], &coin_pos);
            coin_pos.y += 250.0f;
            sp120[i] = BoardCoinChgCreate(&coin_pos, -coin);
        }
    }
    for (sp12C = i = 0; i < sp130; i++) {
        sp12C += BoardPlayerCoinsGet(sp124[i]);
    }
    if (sp12C) {
        HuAudFXPlay(840);
        for (coin = 0; coin < 10; coin++) {
            for (i = 0; i < sp130; i++) {
                BoardPlayerCoinsAdd(sp124[i], -1);
            }
            HuAudFXPlay(14);
            HuPrcSleep(6);
        }
        HuAudFXPlay(15);
        HuPrcSleep(90);
    }
    BoardModelKill(temp_r28);
    BoardModelKill(sp2E);
    for (i = 0; i < 4; i++) {
        BoardPlayerIdleSet(sp124[i]);
    }
    HuPrcSleep(10);
    GWSystem.player_curr = -1;
    RemoveSparkSpace(sp32);
    GWSystem.player_curr = sp30;
    for (i = 0; i < 4; i++) {
        if (sp15C[i] != -1) {
            BoardPlayerMotionKill(i, sp15C[i]);
        }
    }
    if (pause_cam) {
        BoardCameraMoveSet(0);
        BoardCameraMotionWait();
    }

    BoardCameraTargetPlayerSet(sp30);
    BoardCameraMotionWait();
    BoardCameraMoveSet(1);
    BoardRollDispSet(1);
    return 1;
}

static void RemoveSparkSpace(s32 player)
{
    if (GWPlayer[player].spark) {
        BoardWinCreate(0, MAKE_MESSID(18, 28), -1);
        BoardWinWait();
        BoardWinKill();
        GWPlayer[player].spark = 0;
        GWPlayer[player].space_shock = 0;
    }
}

static void SetPlayerSizeAuto(s32 player)
{
    s32 auto_size = BoardPlayerAutoSizeGet(player);
    if (auto_size != 0) {
        BoardStatusHammerKill(player);
        BoardPlayerAutoSizeSet(player, 0);
        HuPrcSleep(30);
        omVibrate(player, 90, 6, 6);
        if (auto_size == 1) {
            HuAudFXPlay(788);
            HuAudFXPlay(787);
        }
        else if (auto_size == 2) {
            HuAudFXPlay(786);
            HuAudFXPlay(785);
        }
        BoardPlayerResizeAnimExec(player, auto_size);
        BoardPlayerSizeSet(player, auto_size);
        HuPrcSleep(30);
        megaDoubleDiceF = 1;
    }
}

s32 BoardMegaDoubleDiceCheck(void)
{
    return megaDoubleDiceF;
}

void BoardPlayerResizeAnimExec(s32 player, s32 size)
{
    s32 j;
    s32 i;
    s16 modelid;
    s32 frame;
    s16 model;
    float mdl_size;
    float frame_data[9];
    float steps[4];
    float player_sizes[] = { 1, 0.3, 2.5 };

    mdl_size = player_sizes[BoardPlayerSizeGet(player)];
    steps[0] = mdl_size;
    steps[1] = mdl_size + ((player_sizes[size] - mdl_size) / 3);
    steps[2] = mdl_size + ((player_sizes[size] - mdl_size) / 1.5f);
    steps[3] = player_sizes[size];
    frame_data[0] = steps[1];
    frame_data[1] = steps[0];
    frame_data[2] = steps[1];
    frame_data[3] = steps[2];
    frame_data[4] = steps[1];
    frame_data[5] = steps[2];
    frame_data[6] = steps[3];
    frame_data[7] = steps[2];
    frame_data[8] = steps[3];
    model = BoardPlayerModelGet(player);
    modelid = BoardModelIDGet(model);
    Hu3DModelAttrSet(modelid, HU3D_MOTATTR_PAUSE);
    frame = 0;
    for (j = 0; j < 9; j++) {
        float size_vel;
        size_vel = (frame_data[frame++] - mdl_size) / 10.0f;
        for (i = 0; i < 10; i++) {
            BoardPlayerScaleSet(player, mdl_size, mdl_size, mdl_size);
            mdl_size += size_vel;
            HuPrcVSleep();
        }
    }
    Hu3DModelAttrReset(modelid, HU3D_MOTATTR_PAUSE);
    BoardPlayerSizeSet(player, size);
}

typedef struct mega_squish_work {
    struct {
        u8 kill : 1;
        u8 no_coinchg : 1;
        u8 played_snd : 1;
        u8 gain_player : 2;
    };
    s8 player;
    s8 state;
    s8 coinchg;
    s8 loss;
    s8 disappear_time;
    s8 disappear_len;
    u16 hide_time;
} MegaSquishWork;

static void MegaSquishFunc(omObjData *object)
{
    MegaSquishWork *work = OM_GET_WORK_PTR(object, MegaSquishWork);
    Vec pos;
    if (work->kill || BoardIsKill()) {
        if (work->coinchg != -1) {
            BoardCoinChgHide(work->coinchg);
        }
        megaSquishObj[work->player] = NULL;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }
    if (work->hide_time != 0) {
        work->hide_time--;
        return;
    }
    switch (work->state) {
        case 1:
            if (!work->played_snd) {
                HuAudFXPlay(798);
                HuAudFXPlay(megaSquishSfxTbl[GWPlayer[work->player].character]);
                work->played_snd = 1;
            }
            BoardPlayerMotionStart(work->player, 10, 0);
            BoardPlayerMotionSpeedSet(work->player, 2.0f);
            work->state = 2;
            break;

        case 2: {
            if (!BoardModelMotionTimeGet(BoardPlayerModelGet(work->player) >= 50.0f)) {
                return;
            }
            BoardPlayerMotionSpeedSet(work->player, 0.0f);
            BoardPlayerPosGet(work->player, &pos);
            pos.y += 10.0f;
            BoardPlayerPosSetV(work->player, &pos);
            work->hide_time = 20;
            work->state = 3;
            work->coinchg = -1;
            work->disappear_time = 0;
        }

        break;

        case 3:
            if (work->coinchg == -1) {
                BoardPlayerPosGet(work->player, &pos);

                pos.y += 250.0f;
                if (!work->no_coinchg) {
                    work->coinchg = BoardCoinChgCreate(&pos, -work->loss);
                }
                else {
                    work->state = 4;
                    work->hide_time = work->disappear_len;
                }
            }
            if (work->disappear_time++ < work->disappear_len) {
                return;
            }
            work->disappear_time = 0;
            if (work->loss <= 0) {
                work->state = 4;
                HuAudFXPlay(15);
            }
            else {
                work->loss--;
                BoardPlayerCoinsAdd(work->player, -1);
                HuAudFXPlay(14);
                BoardPlayerCoinsAdd(work->gain_player, 1);
            }
            break;

        case 4:
            BoardPlayerMotionSpeedSet(work->player, 2.0f);
            BoardPlayerPosGet(work->player, &pos);
            pos.y -= 10.0f;
            BoardPlayerPosSetV(work->player, &pos);
            work->state = 5;
            break;

        case 5:
            if (!BoardPlayerMotionEndCheck(work->player)) {
                return;
            }
            BoardPlayerIdleSet(work->player);
            work->kill = 1;
            break;

        case 0:
            break;

        default:
            break;
    }
}

static s32 MegaPlayerPassFunc(s32 player, s32 space)
{
    float temp_f30;
    float temp_f29;
    MegaSquishWork *temp_r31;
    s32 temp_r29;
    MegaSquishWork *temp_r28;
    s32 temp_r27;
    s32 temp_r26;
    s32 temp_r24;
    omObjData *temp_r23;
    s32 spD0[4];
    Vec spC4;
    Vec spB8;
    Vec spAC;
    Vec spA0;
    float sp98[2];

    if (GWPlayer[player].bowser_suit) {
        return MegaExecJump(player, space);
    }
    if (BoardPlayerSizeGet(player) != 2) {
        return 0;
    }
    spD0[0] = spD0[1] = spD0[2] = -1;
    for (temp_r26 = temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        if (temp_r29 != player && GWPlayer[temp_r29].space_curr == space) {
            spD0[temp_r26++] = temp_r29;
            BoardPlayerPosGet(temp_r29, &spA0);
            temp_r23 = omAddObjEx(boardObjMan, 256, 0, 0, -1, MegaSquishFunc);
            megaSquishObj[temp_r29] = temp_r23;
            temp_r31 = OM_GET_WORK_PTR(temp_r23, MegaSquishWork);
            temp_r31->kill = 0;
            temp_r31->player = temp_r29;
            temp_r31->gain_player = player;
            temp_r31->state = 0;
            temp_r31->hide_time = 0;
            temp_r31->loss = 0;
            temp_r31->disappear_len = 3;
            temp_r31->disappear_time = 0;
            temp_r31->played_snd = 0;
            if (BoardPlayerCoinsGet(temp_r31->player) <= 0) {
                temp_r31->no_coinchg = 1;
            }
            else {
                temp_r31->no_coinchg = 0;
            }
            if (BoardPlayerCoinsGet(temp_r31->player) >= 10) {
                temp_r31->loss = 10;
            }
            else {
                temp_r31->loss = BoardPlayerCoinsGet(temp_r31->player);
            }
        }
    }
    if (temp_r26 == 0) {
        return 0;
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        BoardTutorialHookExec(24, 0);
    }
    BoardPlayerPosGet(player, &spB8);
    BoardSpacePosGet(0, space, &spC4);
    sp98[0] = spB8.y;
    if (spC4.y > spB8.y) {
        spB8.y += 300.0f;
    }
    else {
        spB8.y += 200.0f;
    }
    VECSubtract(&spC4, &spB8, &spAC);
    spAC.x /= 60.0f;
    spAC.z /= 60.0f;
    BoardPlayerRotYSet(player, 90.0 - (180.0 * (atan2(spAC.z, spAC.x) / M_PI)));
    sp98[1] = BoardVecDistXZCalc(&spC4, &spB8);
    BoardPlayerMotionShiftSet(player, 4, 0, 8, HU3D_MOTATTR_NONE);
    HuPrcSleep(8);
    temp_r24 = 0;
    for (temp_f30 = 0; temp_f30 < 60.0f; temp_f30++) {
        temp_f29 = spB8.y;
        spB8.x += spAC.x;
        spB8.z += spAC.z;
        spB8.y += 10.0f + (0.9f * (-0.020416668f * temp_f30 * temp_f30));
        if (temp_f29 > spB8.y) {
            temp_r24 = 1;
        }
        if (spB8.y <= 200.0f + spC4.y && temp_r24) {
            for (temp_r27 = 0; temp_r27 < 4; temp_r27++) {
                if (megaSquishObj[temp_r27]) {
                    temp_r28 = OM_GET_WORK_PTR(megaSquishObj[temp_r27], MegaSquishWork);
                    if ((s16)space == GWPlayer[temp_r28->player].space_curr && temp_r28->state != 1) {
                        temp_r28->state = 1;
                    }
                }
            }
        }
        if (spB8.y <= spC4.y) {
            spB8.y = spC4.y;
            BoardPlayerMotionShiftSet(player, 5, 0, 4, HU3D_MOTATTR_NONE);
        }
        BoardPlayerPosSetV(player, &spB8);
        HuPrcVSleep();
    }
    BoardCameraQuakeSet(30, 500.0f);
    omVibrate(0, 12, 4, 2);
    omVibrate(1, 12, 4, 2);
    omVibrate(2, 12, 4, 2);
    omVibrate(3, 12, 4, 2);
    BoardPlayerIdleSet(player);
    HuPrcSleep(30);
}

static s32 MegaExecJump(s32 player, s32 space)
{
    float temp_f30;
    float temp_f29;
    MegaSquishWork *temp_r31;
    s32 temp_r29;
    MegaSquishWork *temp_r28;
    s32 temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    s32 temp_r24;
    omObjData *temp_r23;
    s32 spD0[4];
    Vec spC4;
    Vec spB8;
    Vec spAC;
    Vec spA0;
    float sp90[2];
    spD0[0] = spD0[1] = spD0[2] = -1;
    for (temp_r26 = temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        if (temp_r29 != player && GWPlayer[temp_r29].space_curr == space) {
            spD0[temp_r26++] = temp_r29;
            BoardPlayerPosGet(temp_r29, &spA0);
            temp_r23 = omAddObjEx(boardObjMan, 256, 0, 0, -1, MegaSquishFunc);
            megaSquishObj[temp_r29] = temp_r23;
            temp_r31 = OM_GET_WORK_PTR(temp_r23, MegaSquishWork);
            temp_r31->kill = 0;
            temp_r31->player = temp_r29;
            temp_r31->gain_player = player;
            temp_r31->state = 0;
            temp_r31->hide_time = 0;
            temp_r31->loss = 0;
            temp_r31->disappear_len = 3;
            temp_r31->disappear_time = 0;
            if (BoardPlayerCoinsGet(temp_r31->player) <= 0) {
                temp_r31->no_coinchg = 1;
            }
            else {
                temp_r31->no_coinchg = 0;
            }
            if (BoardPlayerCoinsGet(temp_r31->player) >= 30) {
                temp_r31->loss = 30;
            }
            else {
                temp_r31->loss = BoardPlayerCoinsGet(temp_r31->player);
            }
        }
    }
    if (temp_r26 == 0) {
        return 0;
    }
    BoardPlayerPosGet(player, &spB8);
    BoardSpacePosGet(0, space, &spC4);
    sp90[0] = spB8.y;
    if (spC4.y > spB8.y) {
        spB8.y += 300.0f;
    }
    else {
        spB8.y += 200.0f;
    }
    VECSubtract(&spC4, &spB8, &spAC);
    spAC.x /= 60.0f;
    spAC.z /= 60.0f;
    BoardPlayerRotYSet(player, 90.0 - (180.0 * (atan2(spAC.z, spAC.x) / M_PI)));
    BoardPlayerIdleSet(player);
    HuPrcSleep(10);
    sp90[1] = BoardVecDistXZCalc(&spC4, &spB8);
    BoardModelMotionShiftSet(suitMdl, bowserSuitMot[3], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    BoardModelMotionSpeedSet(suitMdl, 2.0f);
    HuPrcSleep(8);
    HuAudFXPlay(809);
    temp_r24 = 0;
    temp_r25 = 0;
    for (temp_f30 = 0; temp_f30 < 60.0f; temp_f30++) {
        temp_f29 = spB8.y;
        spB8.x += spAC.x;
        spB8.z += spAC.z;
        spB8.y += 10.0f + (0.9f * (-0.020416668f * temp_f30 * temp_f30));
        if (temp_f29 > spB8.y) {
            temp_r25 = 1;
        }
        if (spB8.y <= 200.0f + spC4.y && temp_r25) {
            for (temp_r27 = 0; temp_r27 < 4; temp_r27++) {
                if (megaSquishObj[temp_r27]) {
                    temp_r28 = OM_GET_WORK_PTR(megaSquishObj[temp_r27], MegaSquishWork);
                    if ((s16)space == GWPlayer[temp_r28->player].space_curr && temp_r28->state != 1) {
                        temp_r28->state = 1;
                    }
                }
            }
        }
        if (spB8.y <= spC4.y) {
            spB8.y = spC4.y;
            if (!temp_r24) {
                BoardPlayerIdleSet(player);
                HuAudFXPlay(810);
                temp_r24 = 1;
            }
        }
        BoardPlayerPosSetV(player, &spB8);
        HuPrcVSleep();
    }
    BoardCameraQuakeSet(30, 500.0f);
    omVibrate(0, 12, 4, 2);
    omVibrate(1, 12, 4, 2);
    omVibrate(2, 12, 4, 2);
    omVibrate(3, 12, 4, 2);
    BoardPlayerIdleSet(player);
    HuPrcSleep(30);
}

void BoardPlayerCopyEyeMat(s32 arg0, s32 arg1)
{
    HsfMaterial *var_r29;
    s32 var_r24;
    s32 var_r25;
    u32 var_r27;
    HsfAttribute *temp_r26;
    char **temp_r28;
    HsfData *hsfData;
    HsfMaterial *material;
    ModelData *model;
    s16 modelId = BoardModelIDGet(BoardPlayerModelGet(arg0));
    model = &Hu3DData[modelId];
    hsfData = model->hsfData;
    material = hsfData->material;
    var_r29 = playerMatCopy[arg0];
    if (arg1 != 0) {
        temp_r28 = &eyeMatTbl[GWPlayer[arg0].character][0];
        (void)temp_r28;
        for (var_r25 = 0; var_r25 < hsfData->materialCnt; var_r25++, material++, var_r29++) {
            var_r24 = 1;

            for (var_r27 = 0; var_r27 < material->numAttrs; var_r27++) {
                temp_r26 = &hsfData->attribute[(s32)material->attrs[var_r27]];
                if ((strcmp(temp_r28[0], temp_r26->bitmap->name) == 0) || (strcmp(temp_r28[1], temp_r26->bitmap->name) == 0)) {
                    var_r24 = 0;
                }
            }
            if (var_r24) {
                if (arg1 != 0) {
                    material->color[0] *= 0.0f;
                    material->color[1] *= 0.0f;
                    material->color[2] *= 0.0f;
                }
                else {
                    material->color[0] = var_r29->color[0];
                    material->color[1] = var_r29->color[1];
                    material->color[2] = var_r29->color[2];
                }
            }
        }
    }
    else {
        memcpy(hsfData->material, var_r29, hsfData->materialCnt * 0x3C);
    }
    DCStoreRange(hsfData->material, hsfData->materialCnt * 0x3C);
}

void BoardPlayerCopyMat(s32 arg0)
{
    s16 modelID;
    ModelData *model;
    void *temp_r3;
    HsfData *temp_r31;

    modelID = BoardModelIDGet(BoardPlayerModelGet(arg0));
    model = &Hu3DData[modelID];
    temp_r31 = model->hsfData;
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, temp_r31->materialCnt * 0x3C, MEMORY_DEFAULT_NUM);
    memcpy(temp_r3, temp_r31->material, temp_r31->materialCnt * 0x3C);
    playerMatCopy[arg0] = temp_r3;
}
