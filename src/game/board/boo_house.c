#include "game/board/boo_house.h"

#include "game/board/audio.h"
#include "game/board/boo.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/star.h"
#include "game/board/ui.h"
#include "game/board/view.h"
#include "game/board/window.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/msm.h"

#include "ext_math.h"

// bss
static s16 houseMdl[6];

// data
static s32 hostMesTbl[6][6] = {
    {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x0C),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x0D),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x0E),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x0F),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x10),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x11),
    },
    {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x12),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x13),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x14),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x15),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x16),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x17),
    },
    {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x18),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x19),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x1A),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x1B),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x1C),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x1D),
    },
    {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x1E),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x1F),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x20),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x21),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x22),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x23),
    },
    {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x24),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x25),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x26),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x27),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x28),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x29),
    },
    {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2A),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2B),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2C),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2D),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2E),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2F),
    },
};
static BoardModelParam houseMdlTbl[6] = {
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x00), { 0, 1, 0, 0, 0 }, 0xFFFF },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x01), { 1, 1, 0, 0, 0 }, 0xFFFF },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x03), { 1, 1, 0, 0, 0 }, 0xFFFF },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x04), { 1, 1, 0, 0, 0 }, 0xFFFF },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x04), { 1, 1, 0, 0, 0 }, 0xFFFF },
    { DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x07), { 0, 1, 0, 0, 0 }, 0xFFFF },
};
static s32 booMotTbl[3] = {
    DATA_MAKE_NUM(DATADIR_BGUEST, 0x13),
    DATA_MAKE_NUM(DATADIR_BGUEST, 0x16),
    DATA_NUM_LISTEND,
};
static s32 hostMotTbl[9][3] = {
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x01), DATA_MAKE_NUM(DATADIR_BGUEST, 0x03), DATA_MAKE_NUM(DATADIR_BGUEST, 0x04) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x09), DATA_MAKE_NUM(DATADIR_BGUEST, 0x0B), DATA_MAKE_NUM(DATADIR_BGUEST, 0x0C) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x0E), DATA_MAKE_NUM(DATADIR_BGUEST, 0x10), DATA_MAKE_NUM(DATADIR_BGUEST, 0x11) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x18), DATA_MAKE_NUM(DATADIR_BGUEST, 0x1A), DATA_MAKE_NUM(DATADIR_BGUEST, 0x1B) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x1D), DATA_MAKE_NUM(DATADIR_BGUEST, 0x1F), DATA_MAKE_NUM(DATADIR_BGUEST, 0x20) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x22), DATA_MAKE_NUM(DATADIR_BGUEST, 0x24), DATA_MAKE_NUM(DATADIR_BGUEST, 0x25) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x18), DATA_MAKE_NUM(DATADIR_BGUEST, 0x1A), DATA_MAKE_NUM(DATADIR_BGUEST, 0x1B) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x01), DATA_MAKE_NUM(DATADIR_BGUEST, 0x03), DATA_MAKE_NUM(DATADIR_BGUEST, 0x04) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x01), DATA_MAKE_NUM(DATADIR_BGUEST, 0x03), DATA_MAKE_NUM(DATADIR_BGUEST, 0x04) },
};

// sbss
static s8 currPlayer;
static s8 stealTarget;
static s8 comStarStealTarget;
static s32 comCoinStealTarget;
static s8 stealAmountStr[8];
static Process *houseProc;

// sdata
static s16 houseShowMot = 0xFFFF;
static s16 houseHideMot = 0xFFFF;
static s16 ballMdl = 0xFFFF;
static s16 booMdl = 0xFFFF;
static s16 smokeMdl = 0xFFFF;
static s16 hostMdl = 0xFFFF;
static s16 hostMot[3] = { 0xFFFF, 0xFFFF, 0xFFFF };

// determined functions
static void ExecBooHouse(void);
static void DestroyBooHouse(void);
static void PickComStealType(s32);
static void OpenBooHouse(void);
static void CloseBooHouse(void);
static void CreateBooHouseModel(void);
static void KillBooHouseModel(void);
static void ExecNullSteal(void);
static void ExecStarSteal(void);
static void ExecCoinSteal(void);
static void ApplySteal(void);
static void ApplyCoinSteal(s16 arg0, s16 arg1);
static void ApplyStarSteal(void);
static void ApplyBooLight(void);
static void SetBooBallPos(void);

// FUNCTIONS //
void BoardBooHouseHostSet(s16 arg0)
{
    hostMdl = arg0;
}

s16 BoardBooHouseHostGet(void)
{
    return hostMdl;
}

void BoardBooHouseCreate(void)
{
    Vec sp14;
    Vec sp8;

    if ((GWBoardGet() == BOARD_ID_EXTRA1) || (GWBoardGet() == BOARD_ID_EXTRA2)) {
        return;
    }
    BoardSpaceLinkTransformGet(0x08000000, &sp14, &sp8, 0);
    houseMdl[0] = BoardModelCreateParam(&houseMdlTbl[0], &sp14, &sp8);
    if (hostMdl != -1) {
        BoardModelVisibilitySet(hostMdl, 0);
    }
    HuDataDirClose(DATADIR_BYOKODORI);
}

void BoardBooHouseKill(void)
{
    if (houseMdl[0] != -1) {
        BoardModelKill(houseMdl[0]);
        houseMdl[0] = -1;
    }
}

void BoardBooHouseExec(s32 arg0)
{
    currPlayer = arg0;
    if (BoardPlayerSizeGet(currPlayer) != 2) {
        BoardRollDispSet(0);
        houseProc = HuPrcChildCreate(&ExecBooHouse, 0x2003, 0x3800, 0, boardMainProc);
        HuPrcDestructorSet2(houseProc, &DestroyBooHouse);
        while (houseProc != 0U) {
            HuPrcVSleep();
        }
        BoardRollDispSet(1);
    }
}

static void ExecBooHouse(void)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    s16 temp_r29;
    s32 var_r31;
    s16 var_r30;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    _SetFlag(0x10018);
    var_r28 = BoardDataDirReadAsync(DATADIR_BYOKODORI);
    var_r30 = GWPlayer[currPlayer].space_curr;
    BoardPlayerIdleSet(currPlayer);
    if (BoardPlayerCoinsGet(currPlayer) < 5) {
        BoardWinCreate(0, MAKE_MESSID(7, 1), -1);
        BoardWinWait();
        BoardWinKill();
        BoardDataAsyncWait(var_r28);
        HuPrcEnd();
    }
    BoardWinCreateChoice(0, MAKE_MESSID(7, 0), -1, 0);
    if (GWPlayer[currPlayer].com != 0) {
        if (BoardBooComUseCheck(currPlayer) != 0) {
            BoardComKeySetLeft();
        }
        else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    if (BoardWinChoiceGet() != 0) {
        BoardDataAsyncWait(var_r28);
        HuPrcEnd();
    }

    for (var_r26 = var_r31 = 0; var_r31 < 4; var_r31++) {
        if (currPlayer != var_r31) {
            var_r26 += GWStarsGet(var_r31);
        }
    }

    for (var_r27 = var_r31 = 0; var_r31 < 4; var_r31++) {
        if (currPlayer != var_r31) {
            var_r27 += BoardPlayerCoinsGet(var_r31);
        }
    }
    BoardWinKill();
    BoardRollDispSet(0);
    BoardAudSeqPause(0, 1, 0x3E8);
    BoardDataAsyncWait(var_r28);
    temp_r29 = BoardSpaceLinkFlagSearch(0, var_r30, 0x02000000);
    BoardSpacePosGet(0, var_r30, &sp38);
    BoardSpacePosGet(0, temp_r29, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    VECNormalize(&sp20, &sp20);
    temp_f31 = atan2d(-sp20.x, -sp20.z);
    sp14.x = -15.0f;
    sp14.y = temp_f31;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 150.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(houseMdl[0], &sp14, &sp8, 1370.0f, -1.0f, 0x1B);
    CreateBooHouseModel();
    OpenBooHouse();
    BoardPlayerRotSet(currPlayer, 0.0f, temp_f31, 0.0f);
    BoardPlayerMoveBetween(currPlayer, var_r30, temp_r29);
    BoardPlayerIdleSet(currPlayer);
    BoardMusStart(1, 1, 0x7F, 0);
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), hostMot[0], 0.0f, 10.0f, 0x40000001);
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][0], BoardWinPortraitGet());
    BoardWinWait();

repeatWindowView:
    HuAudFXPlay(0x4C);
    BoardWinCreateChoice(1, hostMesTbl[GWBoardGet()][1], BoardWinPortraitGet(), 0);
    if (var_r27 == 0) {
        BoardWinChoiceDisable(0);
    }
    if ((BoardPlayerCoinsGet(currPlayer) < 0x32) || (var_r26 == 0)) {
        BoardWinChoiceDisable(1);
    }
    BoardWinAttrSet(0x10);
    if (GWPlayer[currPlayer].com != 0) {
        PickComStealType(currPlayer);
    }
    BoardWinWait();
    stealTarget = BoardWinChoiceGet();
    BoardWinKill();
    while (BoardStatusStopCheck(currPlayer) == 0) {
        HuPrcVSleep();
    }
    switch (stealTarget) {
        case 0:
            ExecCoinSteal();
            break;
        case 1:
            ExecStarSteal();
            break;
        case 2:
            ExecNullSteal();
            break;
        case 3:
            BoardViewMapExec(currPlayer);
            goto repeatWindowView;
    }
    if (stealTarget != 2) {
        ApplySteal();
        BoardStatusShowSet(currPlayer, 0);
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), hostMot[1], 0.0f, 10.0f, 0x40000001);
    CloseBooHouse();
    BoardCameraViewSet(1);
    BoardCameraRotSet(0.0f, 0.0f);
    BoardCameraTargetPlayerSet(currPlayer);
    BoardAudSeqPause(0, 0, 0x3E8);
    BoardPlayerRotSet(currPlayer, 0.0f, temp_f31, 0.0f);
    BoardPlayerMoveBetween(currPlayer, temp_r29, var_r30);
    KillBooHouseModel();
    BoardStatusShowSetAll(1);
    BoardPlayerIdleSet(currPlayer);
    HuPrcEnd();
}

static void DestroyBooHouse(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        if (hostMot[var_r31] != -1) {
            BoardModelMotionKill(BoardBooHouseHostGet(), hostMot[var_r31]);
            hostMot[var_r31] = -1;
        }
    }
    if (houseShowMot != -1) {
        BoardModelMotionKill(houseMdl[0], houseShowMot);
        houseShowMot = -1;
    }
    if (houseHideMot != -1) {
        BoardModelMotionKill(houseMdl[1], houseHideMot);
        houseHideMot = -1;
    }
    BoardWinKill();
    KillBooHouseModel();
    HuDataDirClose(DATADIR_BYOKODORI);
    _ClearFlag(0x10018);
    houseProc = 0;
}

static void PickComStealType(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r28;

    var_r30 = var_r28 = 0;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r31 != arg0) {
            var_r30 += BoardPlayerCoinsGet(var_r31);
            var_r28 += GWStarsGet(var_r31);
        }
    }
    if (BoardPlayerCoinsGet(arg0) >= 0x32) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if ((var_r31 != arg0) && (GWStarsGet(var_r31) != 0) && (((s32)GWSystem.team == 0) || (var_r31 != BoardPlayerSameTeamFind(arg0)))) {
                if (var_r30 != 0) {
                    BoardComKeySetDown();
                }
                else {
                    BoardComKeySetUp();
                }
                return;
            }
        }
    }
    BoardComKeySetUp();
}

static void OpenBooHouse(void)
{
    s16 temp_r31;
    s32 temp_r5;
    s32 var_r30;

    ballMdl = BoardBooCreate(currPlayer, 0);
    temp_r31 = BoardBooHouseHostGet();
    BoardModelMotionStart(temp_r31, 1, 0x40000001);

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        hostMot[var_r30] = BoardModelMotionCreate(temp_r31, hostMotTbl[GWBoardGet()][var_r30]);
    }
    BoardModelMotionStart(temp_r31, hostMot[0], 0x40000001);
    BoardModelVisibilitySet(temp_r31, 1);
    HuAudFXPlay(0x337);
    HuAudFXPlay(0x344);
    BoardModelMotionStart(houseMdl[0], 0, 0);
    BoardModelMotionSpeedSet(houseMdl[0], 1.0f);
    BoardModelHookSet(houseMdl[0], "yoko01", houseMdl[1]);
    BoardModelHookSet(houseMdl[0], "yoko02", ballMdl);
    BoardModelHookSet(houseMdl[0], "yoko03", houseMdl[2]);
    BoardModelHookSet(houseMdl[0], "yoko04", houseMdl[3]);
    BoardModelHookSet(houseMdl[0], "yoko05", houseMdl[4]);
    BoardModelHookSet(houseMdl[0], "yoko9", houseMdl[5]);
    BoardModelHookSet(houseMdl[0], "yoko06", temp_r31);
    if (GWBoardGet() == BOARD_ID_MAIN6) {
        BoardModelPosSet(temp_r31, 0.0f, 0.0f, -25.0f);
    }
    else {
        BoardModelPosSet(temp_r31, 0.0f, 0.0f, 0.0f);
    }
    BoardModelMotionStart(houseMdl[3], 0, 0x40000001);
    BoardModelMotionStart(houseMdl[4], 0, 0x40000001);
    booMdl = BoardModelCreate(0x20012, booMotTbl, 0);
    BoardModelMotionStart(booMdl, 1, 0x40000001);
    BoardModelVisibilitySet(booMdl, 1);
    BoardModelHookSet(houseMdl[0], "yoko8", booMdl);
    smokeMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x08), NULL, 0);
    BoardModelVisibilitySet(smokeMdl, 0);
    BoardModelLayerSet(smokeMdl, 2);
    BoardModelMotionStart(houseMdl[1], 0, 0x40000001);

    while (BoardModelMotionTimeGet(houseMdl[0]) < 90.0f) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(houseMdl[0], houseShowMot, 0.0f, 10.0f, 0x40000001);
    BoardModelMotionShiftSet(houseMdl[1], houseHideMot, 0.0f, 10.0f, 0x40000001);
    BoardModelHookObjReset(houseMdl[0], "yoko02");
    SetBooBallPos();
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), hostMot[2], 0.0f, 10.0f, 0);
}

static void CloseBooHouse(void)
{
    BoardModelPosSet(ballMdl, 0.0f, 0.0f, 0.0f);
    BoardModelHookSet(houseMdl[0], "yoko02", ballMdl);
    BoardModelMotionShiftSet(houseMdl[1], 0, 90.0f, 10.0f, 0);
    BoardModelMotionShiftSet(houseMdl[0], 0, 90.0f, 10.0f, 0);
    HuPrcSleep(0xA);

    while (BoardModelMotionShiftIDGet(houseMdl[0]) != -1) {
        HuPrcVSleep();
    }
    while (BoardModelMotionTimeGet(houseMdl[0]) < 165.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x336);
    BoardAudSeqFadeOut(1, 0x3E8);

    while (BoardModelMotionEndCheck(houseMdl[0]) == 0) {
        HuPrcVSleep();
    }
    BoardModelHookReset(houseMdl[0]);
    BoardBooKill();
    ballMdl = -1;
}

static void CreateBooHouseModel(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (var_r31 != 0) {
            houseMdl[var_r31] = BoardModelCreateParam(&houseMdlTbl[var_r31], 0, 0);
        }
    }
    houseShowMot = BoardModelMotionCreate(houseMdl[0], DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x09));
    houseHideMot = BoardModelMotionCreate(houseMdl[1], DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x0A));
}

static void KillBooHouseModel(void)
{
    s32 temp_r4;
    s32 var_r31;

    for (var_r31 = 1; var_r31 < 6; var_r31++) {
        if (houseMdl[var_r31] != -1) {
            BoardModelKill(houseMdl[var_r31]);
            houseMdl[var_r31] = -1;
        }
    }
    if (booMdl != -1) {
        BoardModelKill(booMdl);
        booMdl = -1;
    }
    if (smokeMdl != -1) {
        BoardModelKill(smokeMdl);
        smokeMdl = -1;
    }
    BoardModelVisibilitySet(BoardBooHouseHostGet(), 0);
}

static void ExecNullSteal(void)
{
    HuAudFXPlay(0x4C);
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][5], BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
}

static void ExecStarSteal(void)
{
    Vec sp14;
    Vec sp8;
    s32 temp_r29;
    s32 var_r30;
    s32 var_r31;

    for (var_r30 = 0; var_r30 < 0x32; var_r30++) {
        BoardPlayerCoinsAdd(currPlayer, -1);
        HuAudFXPlay(0xE);
        HuPrcSleep(1);
    }
    HuAudFXPlay(0xF);
    BoardBooStealTypeSet(1);
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][3], BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
    BoardStatusShowSetAll(0);

    while (BoardPickerDoneCheck() == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x4C);
    Hu3DModelObjPosGet(BoardModelIDGet(houseMdl[0]), "yoko8", &sp14);
    sp14.y += 20.0f;
    BoardModelMotionStart(smokeMdl, 0, 0);
    BoardModelVisibilitySet(smokeMdl, 1);
    BoardModelPosSetV(smokeMdl, &sp14);
    HuPrcSleep(5);

    for (var_r31 = 0xFF; var_r31 > 0; var_r31 -= 0x33) {
        if (var_r31 < 0) {
            var_r31 = 0;
        }
        BoardModelAlphaSet(booMdl, var_r31);
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(booMdl, 0);

    while (BoardModelMotionEndCheck(smokeMdl) == 0) {
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(smokeMdl, 0);
    BoardCameraMotionStartEx(ballMdl, NULL, NULL, 325.0f, -1.0f, 0x15);
    temp_r29 = BoardBooStealMain();
    sp8.x = 0.0f;
    sp8.y = 150.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(houseMdl[0], NULL, &sp8, 1370.0f, -1.0f, 0x15);
    BoardCameraMotionWait();
    if (temp_r29 == 0) {
        BoardModelMotionStart(booMdl, 2, 0x40000001);
    }
    BoardModelMotionStart(smokeMdl, 0, 0);
    BoardModelVisibilitySet(smokeMdl, 1);
    HuPrcSleep(0xB);
    BoardModelVisibilitySet(booMdl, 1);

    for (var_r31 = 0; var_r31 < 0xFF; var_r31 += 0x33) {
        if (var_r31 > 0xFF) {
            var_r31 = 0xFF;
        }
        BoardModelAlphaSet(booMdl, var_r31);
        HuPrcVSleep();
    }
    BoardModelAlphaSet(booMdl, -1);

    while (BoardModelMotionEndCheck(smokeMdl) == 0) {
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(smokeMdl, 0);
}

static void ExecCoinSteal(void)
{
    Vec sp14;
    Vec sp8;
    s32 temp_r29;
    s32 var_r30;
    s32 var_r31;

    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        BoardPlayerCoinsAdd(currPlayer, -1);
        HuAudFXPlay(0xE);
        HuPrcSleep(6);
    }
    HuAudFXPlay(0xF);
    BoardBooStealTypeSet(0);
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][3], BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
    BoardStatusShowSetAll(0);

    while (BoardPickerDoneCheck() == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x4C);
    Hu3DModelObjPosGet(BoardModelIDGet(houseMdl[0]), "yoko8", &sp14);
    sp14.y += 20.0f;
    BoardModelMotionStart(smokeMdl, 0, 0);
    BoardModelVisibilitySet(smokeMdl, 1);
    BoardModelPosSetV(smokeMdl, &sp14);
    HuPrcSleep(5);

    for (var_r31 = 0xFF; var_r31 > 0; var_r31 -= 0x33) {
        if (var_r31 < 0) {
            var_r31 = 0;
        }
        BoardModelAlphaSet(booMdl, var_r31);
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(booMdl, 0);

    while (BoardModelMotionEndCheck(smokeMdl) == 0) {
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(smokeMdl, 0);
    BoardCameraMotionStartEx(ballMdl, NULL, NULL, 325.0f, -1.0f, 0x15);
    temp_r29 = BoardBooStealMain();
    sp8.x = 0.0f;
    sp8.y = 150.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(houseMdl[0], NULL, &sp8, 1370.0f, -1.0f, 0x15);
    BoardCameraMotionWait();
    if (temp_r29 == 0) {
        BoardModelMotionStart(booMdl, 2, 0x40000001);
    }
    BoardModelMotionStart(smokeMdl, 0, 0);
    BoardModelVisibilitySet(smokeMdl, 1);
    HuPrcSleep(0xB);
    BoardModelVisibilitySet(booMdl, 1);

    for (var_r31 = 0; var_r31 < 0xFF; var_r31 += 0x33) {
        if (var_r31 > 0xFF) {
            var_r31 = 0xFF;
        }
        BoardModelAlphaSet(booMdl, var_r31);
        HuPrcVSleep();
    }
    BoardModelAlphaSet(booMdl, -1);

    while (BoardModelMotionEndCheck(smokeMdl) == 0) {
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(smokeMdl, 0);
}

void ApplySteal(void)
{
    s16 spA;
    s16 sp8;
    s32 temp_r30;
    s32 temp_r6;
    s32 var_r31;
    float var_f31;

    BoardModelHookSet(houseMdl[0], "yoko8", booMdl);
    BoardModelVisibilitySet(booMdl, 1);
    BoardModelPosSet(booMdl, 0.0f, 0.0f, 0.0f);
    BoardModelRotSet(booMdl, 0.0f, 0.0f, 0.0f);
    BoardModelScaleSet(booMdl, 1.0f, 1.0f, 1.0f);
    BoardModelAlphaSet(booMdl, 0xFF);
    var_f31 = BoardDAngleCalc(180.0f + BoardPlayerRotYGet(currPlayer));
    BoardPlayerMotBlendSet(currPlayer, var_f31, 0xF);

    while (BoardPlayerMotBlendCheck(currPlayer) == 0) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(currPlayer);
    var_r31 = BoardBooStealValueGet(&spA, &sp8);
    if (var_r31 == 0) {
        ApplyBooLight();
    }
    else if (stealTarget == 0) {
        ApplyCoinSteal(spA, sp8);
    }
    else {
        ApplyStarSteal();
    }
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][4], BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
}

void ApplyCoinSteal(s16 arg0, s16 arg1)
{
    u32 var_r31;
    s32 var_r30;

    if ((s16)arg1 == 0) {
        var_r31 = MAKE_MESSID(7, 9);
    }
    else if ((s16)arg1 < 3) {
        var_r31 = MAKE_MESSID(7, 8);
    }
    else if ((s16)arg1 < 6) {
        var_r31 = MAKE_MESSID(7, 7);
    }
    else if ((s16)arg1 < 8) {
        var_r31 = MAKE_MESSID(7, 6);
    }
    else {
        var_r31 = MAKE_MESSID(7, 5);
    }
    sprintf(&stealAmountStr, "%d", arg0);
    HuAudFXPlay(0x4B);
    BoardWinCreate(2, var_r31, 3);
    BoardWinInsertMesSet((s32)&stealAmountStr, 0);
    BoardWinWait();
    BoardWinKill();
    BoardStatusShowSetForce(currPlayer);
    BoardStatusShowSet(currPlayer, 1);
    BoardPlayerMotionShiftSet(currPlayer, 7, 0.0f, 8.0f, 0);

    for (var_r30 = 0; var_r30 < arg0; var_r30++) {
        BoardPlayerCoinsAdd(currPlayer, 1);
        HuAudFXPlay(0xE);
        HuPrcSleep(6);
    }
    HuAudFXPlay(0xF);
    BoardPlayerMotionEndWait(currPlayer);
}

void ApplyStarSteal(void)
{
    s32 temp_r31;

    HuAudFXPlay(0x4C);
    BoardWinCreate(2, MAKE_MESSID(7, 10), 3);
    BoardWinWait();
    BoardWinKill();
    BoardStatusShowSetForce(currPlayer);
    BoardStatusShowSet(currPlayer, 1);
    BoardAudSeqPause(1, 1, 0x3E8);
    HuPrcSleep(0x17);
    BoardPlayerVoiceEnableSet(currPlayer, 7, 0);
    BoardPlayerMotionShiftSet(currPlayer, 7, 0.0f, 8.0f, 0);
    HuAudFXPlay(boardStarSndTbl[GWPlayer[currPlayer].character]);
    BoardPlayerStarsAdd(currPlayer, 1);
    HuAudFXPlay(8);
    HuPrcSleep(0xA);
    temp_r31 = HuAudSStreamPlay(6);
    BoardPlayerMotionEndWait(currPlayer);

    while (msmStreamGetStatus(temp_r31) != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(1, 0, 0x3E8);
    BoardPlayerMotionEndWait(currPlayer);
    BoardPlayerVoiceEnableSet(currPlayer, 7, 1);
}

void ApplyBooLight(void)
{
    BoardWinCreate(2, MAKE_MESSID(7, 11), 3);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerMotionShiftSet(currPlayer, 8, 0.0f, 8.0f, 0);
    while (BoardPlayerMotionEndCheck(currPlayer) == 0) {
        HuPrcVSleep();
    }
}

void SetBooBallPos(void)
{
    Mtx sp14;
    Vec sp8;
    s16 var_r31;

    var_r31 = BoardModelIDGet(houseMdl[0]);
    Hu3DModelObjMtxGet(var_r31, "yoko02", sp14);
    Hu3DMtxTransGet(sp14, &sp8);
    BoardModelPosSetV(ballMdl, &sp8);
}

s32 BoardBooComUseCheck(s32 arg0)
{
    s32 var_r31;
    u32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r24;

    var_r24 = BoardPlayerCoinsGet(arg0);
    comStarStealTarget = comCoinStealTarget = -1;
    var_r26 = var_r27 = -1;
    switch (GWPlayer[arg0].diff) {
        case 0:
            var_r30 = 0x5F;
            break;
        case 1:
            var_r30 = 0x32;
            break;
        case 2:
            var_r30 = 5;
            break;
        case 3:
            var_r30 = 0;
            break;
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r31 != arg0) {
            if ((s32)GWSystem.team == 0 || var_r31 != BoardPlayerSameTeamFind(arg0)) {
                if (BoardPlayerItemFind(var_r31, 8) == -1 || BoardRandMod(0x64) < var_r30) {
                    var_r29 = BoardPlayerCoinsGet(var_r31);
                    var_r28 = GWStarsGet(var_r31);
                    if (var_r28 != 0 || var_r29 != 0) {
                        if (var_r28 != 0 || var_r29 >= 5 || var_r24 <= 10 || BoardRandMod(0x64) <= 0x32) {
                            if (var_r27 < var_r29) {
                                var_r27 = var_r29;
                                comCoinStealTarget = var_r31;
                            }
                            if (var_r26 < var_r28) {
                                var_r26 = var_r28;
                                comStarStealTarget = (s8)var_r31;
                            }
                        }
                    }
                }
            }
        }
    }
    if ((var_r26 <= 0) && (var_r27 <= 0)) {
        return 0;
    }
    return 1;
}

void BoardBooHouseTutorialExec(void)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    s16 temp_r28;
    s16 temp_r29;
    s32 temp_r27;
    s32 temp_r4;
    s32 var_r31;
    s32 var_r30;

    temp_r27 = BoardDataDirReadAsync(DATADIR_BYOKODORI);
    temp_r29 = BoardSpaceFlagSearch(0, 0x08000000);
    BoardDataAsyncWait(temp_r27);
    temp_r28 = BoardSpaceLinkFlagSearch(0, temp_r29, 0x02000000);
    BoardSpacePosGet(0, temp_r29, &sp38);
    BoardSpacePosGet(0, temp_r28, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    VECNormalize(&sp20, &sp20);
    temp_f31 = atan2d(-sp20.x, -sp20.z);
    sp14.x = -15.0f;
    sp14.y = temp_f31;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 150.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(houseMdl[0], &sp14, &sp8, 1370.0f, -1.0f, 0x15);

    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (var_r31 != 0) {
            houseMdl[var_r31] = BoardModelCreateParam(&houseMdlTbl[var_r31], NULL, NULL);
        }
    }
    houseShowMot = BoardModelMotionCreate(houseMdl[0], DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x09));
    houseHideMot = BoardModelMotionCreate(houseMdl[1], DATA_MAKE_NUM(DATADIR_BYOKODORI, 0x0A));
    OpenBooHouse();

    while (BoardModelMotionEndCheck(BoardBooHouseHostGet()) == 0) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), hostMot[0], 0.0f, 10.0f, 0x40000001);
    BoardTutorialHookExec(0x1C, 0);
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), hostMot[1], 0.0f, 10.0f, 0x40000001);
    BoardModelPosSet(ballMdl, 0.0f, 0.0f, 0.0f);
    BoardModelHookSet(houseMdl[0], "yoko02", ballMdl);
    BoardModelMotionShiftSet(houseMdl[1], 0, 90.0f, 10.0f, 0);
    BoardModelMotionShiftSet(houseMdl[0], 0, 90.0f, 10.0f, 0);
    HuPrcSleep(0xA);
    while (BoardModelMotionShiftIDGet(houseMdl[0]) != -1) {
        HuPrcVSleep();
    }
    while (BoardModelMotionTimeGet(houseMdl[0]) < 165.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x336);
    BoardAudSeqFadeOut(1, 0x3E8);
    while (BoardModelMotionEndCheck(houseMdl[0]) == 0) {
        HuPrcVSleep();
    }
    BoardModelHookReset(houseMdl[0]);
    BoardBooKill();
    ballMdl = -1;

    for (var_r30 = 1; var_r30 < 6; var_r30++) {
        if (houseMdl[var_r30] != -1) {
            BoardModelKill(houseMdl[var_r30]);
            houseMdl[var_r30] = -1;
        }
    }
    if (booMdl != -1) {
        BoardModelKill(booMdl);
        booMdl = -1;
    }
    if (smokeMdl != -1) {
        BoardModelKill(smokeMdl);
        smokeMdl = -1;
    }
    BoardModelVisibilitySet(BoardBooHouseHostGet(), 0);
}
