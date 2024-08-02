#include "REL/w04Dll.h"
#include "REL/board_executor.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/process.h"
#include "game/window.h"
#include "game/board/boo_house.h"
#include "game/board/com.h"
#include "game/board/lottery.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/shop.h"
#include "game/board/space.h"
#include "game/board/star.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "math.h"

static void fn_1_750(void);
static void fn_1_794(void);
static s32 fn_1_798(void);
static s32 fn_1_7FC(void);
static void fn_1_930(void);
static void fn_1_954(void);
static void fn_1_958(void);
static void fn_1_CF8(void);
static void fn_1_D30(void);
static void fn_1_DB0(void);
static s32 fn_1_103C(void);

s16 lbl_1_bss_14[MAPOBJ_MAX];

BoardMapObject lbl_1_data_0[MAPOBJ_MAX] = {
    { {   750.0f,  0.0f,   1500.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 5) },
    { { -1500.0f,  0.0f,    150.0f }, { 0.0f,  89.999985f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 5) },
    { {  1200.0f,  0.0f,  -1650.0f }, { 0.0f, -89.999985f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 5) },
    { { -1950.0f,  0.0f,  -2100.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 4) },
    { {  2100.0f,  0.0f,  -2100.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 18) },
    { {  -150.0f,  0.0f,   -150.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 23) },
    { {  3000.0f,  0.0f,   -600.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 12) },
    { { -1500.0f,  0.0f,   -900.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 15) },
    { { -1950.0f,  0.0f,  -2000.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 34) },
    { { -1350.0f, 50.0f,   -900.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 34) },
    { {  2750.0f,  0.0f,   -600.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 34) },
    { {  -150.0f,  0.0f,   -100.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 29) },
    { {  2850.0f,  0.0f,  -1500.0f }, { 0.0f, -89.999985f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 17) },
    { { -3150.0f,  0.0f,    300.0f }, { 0.0f,  89.999985f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 17) },
    { {  2850.0f,  0.0f, 0.000003f }, { 0.0f, -89.999985f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 17) },
    { {   900.0f,  0.0f,   2250.0f }, { 0.0f,  180.00001f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W04, 17) }
};

static s32 *lbl_1_bss_10;
static s16 lbl_1_bss_8[4];
static Process *lbl_1_bss_4;
UnkW04BoardData *lbl_1_bss_0;

static s16 lbl_1_data_280 = -1;
static s16 lbl_1_data_282 = -1;
static s16 lbl_1_data_284 = -1;
static s16 lbl_1_data_286 = -1;

static s32 lbl_1_data_288[] = {
    DATA_MAKE_NUM(DATADIR_W04, 8),
    -1
};

static s32 lbl_1_data_290[] = {
    DATA_MAKE_NUM(DATADIR_BGUEST, 24),
    -1
};

void BoardCreate(void) {
    BoardMapObject *temp_r30;
    s32 sp8;
    s32 i;

    omDBGMenuButton = 1;
    sp8 = GWBoardGet();
    lbl_1_bss_0 = (UnkW04BoardData*) GWSystem.board_data;
    BoardSpaceInit(DATA_MAKE_NUM(DATADIR_W04, 0));
    lbl_1_data_280 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 1), NULL, 0);
    fn_8006DDE8(lbl_1_data_280, -1.0f);
    BoardModelPosSet(lbl_1_data_280, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_280, 0, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_data_280, 1.0f);
    lbl_1_data_282 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 2), NULL, 0);
    fn_8006DDE8(lbl_1_data_282, -1.0f);
    BoardModelPosSet(lbl_1_data_282, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_282, 0, 0x40000001);
    lbl_1_data_284 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 7), lbl_1_data_288, 0);
    BoardModelPosSet(lbl_1_data_284, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_284, 1, 0x40000001);
    lbl_1_data_286 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 18), lbl_1_data_290, 0);
    BoardModelMotionStart(lbl_1_data_286, 1, 0x40000001);
    BoardLightHookSet(fn_1_750, fn_1_794);
    for (i = 0; i < 16; i++) {
        temp_r30 = &lbl_1_data_0[i];
        if (temp_r30->data_num != -1) {
            if (i == 8 || i == 9 || i == 10 || i == 11) {
                lbl_1_bss_10 = lbl_1_data_290;
            } else {
                lbl_1_bss_10 = NULL;
            }
            lbl_1_bss_14[i] = BoardModelCreate(temp_r30->data_num, lbl_1_bss_10, 0);
            BoardModelPosSetV(lbl_1_bss_14[i], &temp_r30->pos);
            BoardModelRotSetV(lbl_1_bss_14[i], &temp_r30->rot);
            BoardModelScaleSetV(lbl_1_bss_14[i], &temp_r30->scale);
            BoardModelVisibilitySet(lbl_1_bss_14[i], 1);
            if (lbl_1_bss_10 != NULL) {
                BoardModelMotionStart(lbl_1_bss_14[i], 1, 0x40000001);
            }
        }
    }
    BoardModelAlphaSet(lbl_1_bss_14[8], 0);
    BoardModelVisibilitySet(lbl_1_bss_14[8], 0);
    BoardModelMotionStartEndSet(lbl_1_bss_14[5], 0, 60);
    BoardModelAttrSet(lbl_1_bss_14[5], 0x40000001);
    BoardModelAttrSet(lbl_1_bss_14[4], 0x40000001);
    fn_1_930();
    fn_1_12FC();
    fn_1_6024();
    BoardModelAttrSet(lbl_1_bss_14[0], 0x40000001);
    BoardModelAttrSet(lbl_1_bss_14[1], 0x40000001);
    BoardModelAttrSet(lbl_1_bss_14[2], 0x40000001);
    BoardModelAttrSet(lbl_1_bss_14[3], 0x40000001);
    BoardSpaceWalkEventFuncSet(fn_1_7FC);
    BoardSpaceWalkMiniEventFuncSet(fn_1_103C);
    BoardSpaceLandEventFuncSet(fn_1_798);
    BoardStarHostSet(lbl_1_data_284);
    BoardBooHouseHostSet(lbl_1_data_286);
    BoardShopHostSet(lbl_1_data_286);
    BoardLotteryHostSet(lbl_1_data_286);
    BoardJunctionMaskSet(0x100);
    BoardJunctionMaskSet(0x40);
}

void BoardDestroy(void) {
    s32 i;

    fn_1_15C8();
    for (i = 0; i < MAPOBJ_MAX; i++) {
        if (lbl_1_bss_14[i] != 0) {
            BoardModelKill(lbl_1_bss_14[i]);
            lbl_1_bss_14[i] = 0;
        }
    }
    if (lbl_1_data_286 != -1) {
        BoardModelKill(lbl_1_data_286);
        lbl_1_data_286 = -1;
    }
    if (lbl_1_data_284 != -1) {
        BoardModelKill(lbl_1_data_284);
        lbl_1_data_284 = -1;
    }
    if (lbl_1_data_280 != -1) {
        BoardModelKill(lbl_1_data_280);
        lbl_1_data_280 = -1;
    }
    if (lbl_1_data_282 != -1) {
        BoardModelKill(lbl_1_data_282);
        lbl_1_data_282 = -1;
    }
    BoardSpaceDestroy();
}

static void fn_1_750(void) {
    s16 var_r31;

    var_r31 = BoardModelIDGet(lbl_1_data_280);
    Hu3DModelLightInfoSet(var_r31, 1);
}

static void fn_1_794(void) {
}

static s32 fn_1_798(void) {
    s32 var_r31;
    s32 var_r30;
    s32 sp8;

    var_r31 = GWSystem.player_curr;
    var_r30 = GWPlayer[var_r31].space_curr;
    sp8 = BoardSpaceFlagGet(0, var_r30);
    fn_1_9EBC();
}

static s32 fn_1_7FC(void) {
    s32 temp_r31;
    BoardSpace *temp_r3;

    temp_r31 = GWSystem.player_curr;
    if (BoardPlayerSizeGet(temp_r31) == 2) {
        return 0;
    }
    if (GWPlayer[temp_r31].bowser_suit) {
        return 0;
    }
    temp_r3 = BoardSpaceGet(0, GWPlayer[temp_r31].space_curr);
    if (temp_r3->flag & 0x80) {
        fn_1_2058();
        return 1;
    }
    if (temp_r3->flag & 0x100) {
        if (lbl_1_bss_0->unk00 & 1) {
            fn_1_55B4();
        } else {
            BoardRollDispSet(0);
            BoardPlayerIdleSet(temp_r31);
            BoardWinCreate(0, MAKE_MESSID(32, 25), -1);
            BoardWinWait();
            BoardWinKill();
            BoardRollDispSet(1);
        }
        return 1;
    }
    return 0;
}

static void fn_1_930(void) {
    fn_1_A0F8();
    fn_1_C7A0();
}

static void fn_1_954(void) {
}

static void fn_1_958(void) {
    Vec sp8;
    u32 temp_r3;
    s32 temp_r27;
    s32 temp_r31;
    s32 var_r26;
    s32 var_r30;
    s32 var_r29;

    temp_r31 = GWSystem.player_curr;
    if (BoardPlayerItemCount(temp_r31) == 3) {
        BoardWinCreate(2, MAKE_MESSID(32, 12), 3);
        BoardWinWait();
        BoardWinKill();
        HuPrcEnd();
    }
    lbl_1_bss_8[0] = 0;
    var_r30 = 1;
    while (var_r30 < 3) {
        lbl_1_bss_8[var_r30] = frandmod(14);
        if (lbl_1_bss_8[var_r30] != 10 && lbl_1_bss_8[var_r30] != 13) {
            for (var_r29 = 0; var_r29 < var_r30; var_r29++) {
                if (lbl_1_bss_8[var_r30] == lbl_1_bss_8[var_r29]) {
                    lbl_1_bss_8[var_r30] = -1;
                }
            }
            if (lbl_1_bss_8[var_r30] != -1) {
                var_r30++;
            }
        }
    }
    fn_1_BB00(lbl_1_bss_8);
    BoardWinCreateChoice(2, MAKE_MESSID(32, 13), 3, 0);
    if (GWPlayer[temp_r31].com) {
        if (BoardComPreferItemCheck(temp_r31, lbl_1_bss_8[0], lbl_1_bss_8[1], lbl_1_bss_8[2]) != -1) {
            BoardComKeySetLeft();
        } else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    temp_r3 = BoardWinChoiceGet();
    if (temp_r3 == 1 || temp_r3 == -1) {
        BoardWinCreate(2, MAKE_MESSID(32, 14), 3);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        fn_1_C2BC();
        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        fn_1_BA7C();
        HuPrcEnd();
    }
    temp_r27 = GWPlayer[temp_r31].space_curr;
    var_r26 = BoardSpaceLinkFlagSearch(0, temp_r27, 0x02000000);
    BoardPlayerMoveBetween(temp_r31, temp_r27, var_r26);
    while (GWPlayer[temp_r31].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r31, 1, 0x40000001);
    BoardPlayerPosGet(temp_r31, &sp8);
    sp8.y += 5.0f;
    BoardPlayerPosSetV(temp_r31, &sp8);
    BoardCameraViewSet(2);
    BoardPlayerMotBlendSet(temp_r31, 180, 15);
    while (!BoardPlayerMotBlendCheck(temp_r31)) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    fn_1_A1F0();
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    while (GWPlayer[temp_r31].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r31, 1, 0x40000001);
    HuPrcEnd();
}

static void fn_1_CF8(void) {
    BoardWinKill();
    CharModelDataClose(-1);
    lbl_1_bss_4 = NULL;
}

static void fn_1_D30(void) {
    lbl_1_bss_4 = HuPrcChildCreate(fn_1_958, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_4, fn_1_CF8);
    while (lbl_1_bss_4) {
        HuPrcVSleep();
    }
}

static void fn_1_DB0(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r29;
    s32 temp_r3_2;

    temp_r31 = GWSystem.player_curr;
    BoardWinCreateChoice(2, MAKE_MESSID(32, 17), 3, 0);
    if (GWPlayer[temp_r31].com) {
        if (frand() & 1) {
            BoardComKeySetLeft();
        } else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    temp_r3 = BoardWinChoiceGet();
    if (temp_r3 == 1 || temp_r3 == -1) {
        BoardWinCreate(2, MAKE_MESSID(32, 18), 3);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        return;
    }
    sp20.x = -45.0f;
    sp20.y = sp20.z = 0.0f;
    sp14.y = 50.0f;
    sp14.x = sp14.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_14[7], &sp20, &sp14, 1200.0f, 25.0f, 21);
    temp_r29 = GWPlayer[temp_r31].space_curr;
    temp_r3_2 = BoardSpaceLinkFlagSearch(0, temp_r29, 0x02000000);
    BoardSpacePosGet(0, temp_r3_2, &sp8);
    BoardPlayerMoveBetween(temp_r31, temp_r29, temp_r3_2);
    while (GWPlayer[temp_r31].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r31, 1, 0x40000001);
    fn_1_C7D4();
    while (GWPlayer[temp_r31].moving) {
        HuPrcVSleep();
    }
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    while (GWPlayer[temp_r31].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r31, 1, 0x40000001);
}

static s32 fn_1_103C(void) {
    s16 var_r30;
    u32 temp_r31;

    var_r30 = GWPlayer[GWSystem.player_curr].space_curr;
    temp_r31 = BoardSpaceFlagGet(0, var_r30) & 0x600000;
    BoardRollDispSet(0);
    if (temp_r31 & 0x200000) {
        lbl_1_bss_4 = HuPrcChildCreate(fn_1_958, 0x2003, 0x2000, 0, boardMainProc);
        HuPrcDestructorSet2(lbl_1_bss_4, fn_1_CF8);
        while (lbl_1_bss_4) {
            HuPrcVSleep();
        }
    } else if (temp_r31 & 0x400000) {
        fn_1_DB0();
    }
    BoardRollDispSet(1);
}

s32 fn_1_1130(s16 arg0, float arg1, float arg2) {
    float var_f29;
    float var_f31;
    s32 var_r31;

    var_r31 = 0;
    var_f31 = BoardModelRotYGet(arg0);
    arg1 = fmod(arg1, 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (arg1 < 0.0f) {
        arg1 += 360.0f;
    }
    if (var_f31 != arg1) {
        var_f29 = arg1 - var_f31;
        if (var_f29 < 0.0f) {
            var_f29 += 360.0f;
        }
        if (var_f29 < 180.0f) {
            if (var_f29 > arg2) {
                var_f31 += arg2;
            } else {
                var_f31 = arg1;
            }
        } else if (360.0f - var_f29 > arg2) {
            var_f31 -= arg2;
        } else {
            var_f31 = arg1;
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
