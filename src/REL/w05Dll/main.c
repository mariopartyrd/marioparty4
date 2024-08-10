#include "REL/w05Dll.h"

#include "game/chrman.h"
#include "game/frand.h"
#include "game/gamework_data.h"


#include "game/board/audio.h"
#include "game/board/boo_house.h"
#include "game/board/com.h"
#include "game/board/lottery.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/shop.h"
#include "game/board/space.h"
#include "game/board/star.h"
#include "game/board/window.h"

// data
BoardMapObject lbl_1_data_0[7] = {
    { { 3300.0f, 100.0f, -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W05, 0x11) },
    { { -2550.0f, 0.0f, 1350.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W05, 0x14) },
    { { -3000.0f, 100.0f, -1050.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W05, 0x1A) },
    { { 2100.0f, 100.0f, -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W05, 0x1B) },
    { { -450.0f, 100.0f, -750.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W05, 0x0A) },
    { { -2710.0f, 0.0f, 1315.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W05, 0x0A) },
    { { 3055.0f, 100.0f, -815.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W05, 0x0A) },
};
s16 lbl_1_data_118 = 0xFFFF;
s16 lbl_1_data_11A = 0xFFFF;
s16 lbl_1_data_11C = 0xFFFF;
s16 lbl_1_data_11E = 0xFFFF;
s16 lbl_1_data_120 = 0xFFFF;
s32 lbl_1_data_124[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
};
s32 lbl_1_data_144[2] = { DATA_MAKE_NUM(DATADIR_W05, 0x06), DATA_NUM_LISTEND };
s32 lbl_1_data_14C = 0xFFFFFFFF;

// bss
s16 lbl_1_bss_14[7];
s32 *lbl_1_bss_10;
s16 lbl_1_bss_8[4];
Process *lbl_1_bss_4;
bitcopy *lbl_1_bss_0;

void BoardCreate(void)
{
    s32 sp8;
    s32 var_r31;
    BoardMapObject *temp_r30;

    sp8 = GWBoardGet();
    lbl_1_bss_0 = (bitcopy *)GWSystem.board_data;
    BoardSpaceInit(DATA_MAKE_NUM(DATADIR_W05, 0x00));
    lbl_1_data_118 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x01), NULL, 0);
    lbl_1_data_120 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x02), NULL, 0);
    fn_8006DDE8(lbl_1_data_118, -1.0f);
    BoardModelPosSet(lbl_1_data_118, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_118, 0, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_data_118, 1.0f);
    fn_8006DDE8(lbl_1_data_120, -1.0f);
    BoardModelPosSet(lbl_1_data_120, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_120, 0, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_data_120, 1.0f);
    BoardModelLayerSet(lbl_1_data_120, 1);
    lbl_1_data_11A = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x03), NULL, 0);
    fn_8006DDE8(lbl_1_data_11A, -1.0f);
    BoardModelPosSet(lbl_1_data_11A, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_11A, 0, 0x40000001);
    lbl_1_data_11C = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x05), lbl_1_data_144, 0);
    BoardModelPosSet(lbl_1_data_11C, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_11C, 1, 0x40000001);
    lbl_1_data_11E = BoardModelCreate(0x2001C, &lbl_1_data_14C, 0);
    BoardModelMotionStart(lbl_1_data_11E, 1, 0x40000001);
    BoardLightHookSet(&fn_1_744, &fn_1_788);

    for (var_r31 = 0; var_r31 < 7; var_r31++) {
        temp_r30 = &lbl_1_data_0[var_r31];
        if (temp_r30->data_num != -1) {
            if ((var_r31 == 4) || (var_r31 == 5) || (var_r31 == 6)) {
                lbl_1_bss_10 = &lbl_1_data_14C;
            }
            else {
                lbl_1_bss_10 = NULL;
            }
            lbl_1_bss_14[var_r31] = BoardModelCreate(temp_r30->data_num, lbl_1_bss_10, 0);
            BoardModelPosSetV(lbl_1_bss_14[var_r31], &temp_r30->pos);
            BoardModelRotSetV(lbl_1_bss_14[var_r31], &temp_r30->rot);
            BoardModelScaleSetV(lbl_1_bss_14[var_r31], &temp_r30->scale);
            BoardModelVisibilitySet(lbl_1_bss_14[var_r31], 1);
            if (lbl_1_bss_10 != NULL) {
                BoardModelMotionStart(lbl_1_bss_14[var_r31], 0, 0x40000001);
            }
        }
    }
    fn_1_92C();
    fn_1_13D4();
    fn_1_2B40();
    BoardSpaceWalkEventFuncSet(&fn_1_82C);
    BoardSpaceWalkMiniEventFuncSet(&fn_1_1114);
    BoardSpaceLandEventFuncSet(&fn_1_78C);
    BoardStarHostSet(lbl_1_data_11C);
    BoardBooHouseHostSet(lbl_1_data_11E);
    BoardShopHostSet(lbl_1_data_11E);
    BoardLotteryHostSet(lbl_1_data_11E);
}

void BoardDestroy(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 7; var_r31++) {
        if (lbl_1_bss_14[var_r31] != 0) {
            BoardModelKill(lbl_1_bss_14[var_r31]);
            lbl_1_bss_14[var_r31] = 0;
        }
    }
    if (lbl_1_data_11E != -1) {
        BoardModelKill(lbl_1_data_11E);
        lbl_1_data_11E = -1;
    }
    if (lbl_1_data_11C != -1) {
        BoardModelKill(lbl_1_data_11C);
        lbl_1_data_11C = -1;
    }
    if (lbl_1_data_118 != -1) {
        BoardModelKill(lbl_1_data_118);
        lbl_1_data_118 = -1;
    }
    if (lbl_1_data_120 != -1) {
        BoardModelKill(lbl_1_data_120);
        lbl_1_data_120 = -1;
    }
    if (lbl_1_data_11A != -1) {
        BoardModelKill(lbl_1_data_11A);
        lbl_1_data_11A = -1;
    }
    BoardSpaceDestroy();
}

void fn_1_744(void)
{
    s16 var_r31 = BoardModelIDGet(lbl_1_data_118);
    Hu3DModelLightInfoSet(var_r31, 1);
}

void fn_1_788(void) { }

s32 fn_1_78C(void)
{
    s32 var_r30 = GWSystem.player_curr;
    s32 var_r29 = GWPlayer[var_r30].space_curr;
    s32 var_r28;
    u32 temp_r3;

    temp_r3 = BoardSpaceFlagGet(0, var_r29);
    if ((temp_r3 & 2) != 0) {
        fn_1_1E44();
        return;
    }
    if ((temp_r3 & 0x40) != 0) {
        var_r28 = (temp_r3 & 0x38) >> 3;
        fn_1_4034(var_r28);
    }
}

s32 fn_1_82C(void)
{
    s32 temp_r30;
    BoardSpace *temp_r3;

    temp_r30 = GWSystem.player_curr;
    temp_r3 = BoardSpaceGet(0, GWPlayer[temp_r30].space_curr);
    if ((temp_r3->flag & 1) != 0) {
        fn_1_2C7C(0);
        return 1;
    }
    if ((temp_r3->flag & 0x800) != 0) {
        fn_1_2C7C(1);
        return 1;
    }
    if (BoardPlayerSizeGet(temp_r30) == 2) {
        return 0;
    }
    if (GWPlayer[temp_r30].bowser_suit != 0) {
        return 0;
    }
    if ((temp_r3->flag & 4) != 0) {
        fn_1_155C();
        return 1;
    }
    return 0;
}

void fn_1_92C(void)
{
    fn_1_6B28();
    fn_1_9680();
}

void fn_1_950(void) { }

void fn_1_954(void)
{
    Vec sp14;
    Vec sp8;
    s32 var_r26;
    u32 var_r28;
    s32 temp_r27;
    s32 var_r29;
    s32 var_r31;
    s32 temp_r30;

    temp_r30 = GWSystem.player_curr;
    if (BoardPlayerItemCount(temp_r30) == 3) {
        BoardWinCreate(2, MAKE_MESSID(39, 9), 7);
        BoardWinWait();
        BoardWinKill();
        HuPrcEnd();
    }
    lbl_1_bss_8[0] = 0;

    for (var_r31 = 1; var_r31 < 3;) {
        lbl_1_bss_8[var_r31] = (u32)frandmod(0xE);
        if ((lbl_1_bss_8[var_r31] == 0xA) || (lbl_1_bss_8[var_r31] == 0xD)) {
            continue;
        }
        for (var_r29 = 0; var_r29 < var_r31; var_r29++) {
            if (lbl_1_bss_8[var_r31] == lbl_1_bss_8[var_r29]) {
                lbl_1_bss_8[var_r31] = -1;
            }
        }
        if (lbl_1_bss_8[var_r31] == -1) {
            continue;
        }
        var_r31++;
    }
    fn_1_74D0(lbl_1_bss_8);
    BoardWinCreateChoice(2, MAKE_MESSID(39, 10), 7, 0);
    if (GWPlayer[temp_r30].com != 0) {
        if (BoardComPreferItemCheck(temp_r30, lbl_1_bss_8[0], lbl_1_bss_8[1], lbl_1_bss_8[2]) != -1) {
            BoardComKeySetLeft();
        }
        else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    var_r28 = BoardWinChoiceGet();
    if (var_r28 == 1 || var_r28 == -1) {
        while (((u32)fn_1_8884() & 0x10) == 0) {
            HuPrcVSleep();
        }
        BoardWinCreate(2, MAKE_MESSID(39, 11), 7);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        fn_1_88B8();
        fn_1_77B0();
        fn_1_7314();
        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        HuPrcEnd();
    }
    sp14.x = -30.0f;
    sp14.y = sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_14[0], &sp14, &sp8, 1250.0f, 25.0f, 0x15);

    while (((u32)fn_1_8884() & 0x10) == 0) {
        HuPrcVSleep();
    }
    temp_r27 = GWPlayer[temp_r30].space_curr;
    var_r26 = BoardSpaceLinkFlagSearch(0, temp_r27, 0x02000000);
    BoardPlayerMoveBetween(temp_r30, temp_r27, var_r26);

    while (GWPlayer[temp_r30].moving != 0) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r30, 1, 0x40000001);
    fn_1_6B7C();

    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    while ((GWPlayer[temp_r30].moving) != 0) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r30, 1, 0x40000001);
    HuPrcEnd();
}

void fn_1_D4C(void)
{
    BoardWinKill();
    CharModelDataClose(-1);
    lbl_1_bss_4 = NULL;
}

void fn_1_D84(void)
{
    lbl_1_bss_4 = HuPrcChildCreate(fn_1_954, 0x2003U, 0x3000U, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_4, fn_1_D4C);

    while (lbl_1_bss_4 != 0) {
        HuPrcVSleep();
    }
}

void fn_1_E04(void)
{
    HuPrcSleep(0x3C);
    BoardMusStart(1, 0x23, 0x7F, 0);
    HuPrcEnd();
}

void fn_1_E40(void)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r3_2;
    s32 temp_r31;

    temp_r31 = GWSystem.player_curr;
    fn_1_96B4();
    BoardWinCreateChoice(2, MAKE_MESSID(39, 15), 7, 0);
    if (GWPlayer[temp_r31].com != 0) {
        if (frandBool() != 0) {
            BoardComKeySetLeft();
        }
        else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    temp_r30 = BoardWinChoiceGet();
    if ((temp_r30 == 1) || (temp_r30 == -1)) {
        fn_1_9760();
        BoardWinCreate(2, MAKE_MESSID(39, 16), 7);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();

        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        return;
    }
    BoardAudSeqPause(0, 1, 0x3E8);
    HuPrcChildCreate(fn_1_E04, 0x2003, 0x1000, 0, boardMainProc);
    sp20.x = -35.0f;
    sp20.y = sp20.z = 0.0f;
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = -250.0f;
    BoardCameraMotionStartEx(lbl_1_bss_14[1], &sp20, &sp14, 1550.0f, 25.0f, 0x15);
    temp_r29 = GWPlayer[temp_r31].space_curr;
    temp_r3_2 = BoardSpaceLinkFlagSearch(0, temp_r29, 0x02000000);
    BoardSpacePosGet(0, temp_r3_2, &sp8);
    BoardPlayerMoveBetween(temp_r31, temp_r29, temp_r3_2);
    while (GWPlayer[temp_r31].moving != 0) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r31, 1, 0x40000001);
    fn_1_97AC();
    while (GWPlayer[temp_r31].moving != 0) {
        HuPrcVSleep();
    }
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    while (GWPlayer[temp_r31].moving != 0) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r31, 1, 0x40000001);
}

s32 fn_1_1114(void)
{
    u32 temp_r31;
    s16 var_r30 = GWPlayer[GWSystem.player_curr].space_curr;

    temp_r31 = BoardSpaceFlagGet(0, var_r30) & 0x600000;
    BoardRollDispSet(0);
    if ((temp_r31 & 0x200000) != 0) {
        lbl_1_bss_4 = HuPrcChildCreate(fn_1_954, 0x2003, 0x3000, 0, boardMainProc);
        HuPrcDestructorSet2(lbl_1_bss_4, fn_1_D4C);

        while (lbl_1_bss_4 != 0) {
            HuPrcVSleep();
        }
    }
    else if ((temp_r31 & 0x400000) != 0) {
        fn_1_E40();
    }
    BoardRollDispSet(1);
}

s32 fn_1_1208(s16 arg0, f32 arg8, f32 arg9)
{
    f32 var_f29;
    f32 var_f31;
    s32 var_r31;

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
            }
            else {
                var_f31 = arg8;
            }
        }
        else if ((360.0f - var_f29) > arg9) {
            var_f31 = var_f31 - arg9;
        }
        else {
            var_f31 = arg8;
        }
        if (var_f31 < 0.0f) {
            var_f31 += 360.0f;
        }
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        BoardModelRotYSet(arg0, var_f31);
    }
    else {
        var_r31 = 1;
    }
    return var_r31;
}
