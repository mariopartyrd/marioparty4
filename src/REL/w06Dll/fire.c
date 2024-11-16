#include "REL/w06Dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/objsub.h"
#include "game/process.h"
#include "game/window.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "ext_math.h"

static void fn_1_6F80(void);
static void fn_1_7210(void);
static s32 fn_1_72A4(void);
static void fn_1_72CC(s32 arg0);
static void fn_1_73EC(float arg0);
static void fn_1_74BC(s32 arg0);
static void fn_1_7574(void);
static void fn_1_7674(s32 arg0);
static void fn_1_7760(s32 arg0);
static s32 fn_1_7944(s32 arg0);

static s8 lbl_1_bss_C6;
static s8 lbl_1_bss_C2[4];
static s16 lbl_1_bss_C0;
static s32 lbl_1_bss_BC;
static s32 lbl_1_bss_B8;
static u8 lbl_1_bss_94_gap[0x24];
static Process *lbl_1_bss_90;

static s32 lbl_1_data_208[8] = {
    0x00000123,
    0x00000163,
    0x000001A3,
    0x000001E3,
    0x00000223,
    0x00000263,
    0x000002A3,
    0x000002E3
};

static s8 lbl_1_data_228 = -1;
static s16 lbl_1_data_22A = -1;
static s16 lbl_1_data_22C = -1;
static s16 lbl_1_data_22E = -1;

#if VERSION_PAL
static s32 lbl_1_data_230[] = {
    MAKE_MESSID(8, 0),
    MAKE_MESSID(8, 1),
    MAKE_MESSID(8, 2),
    MAKE_MESSID(8, 3),
    MAKE_MESSID(8, 4),
    MAKE_MESSID(8, 5),
    MAKE_MESSID(8, 6),
    MAKE_MESSID(8, 7),
    MAKE_MESSID(8, 8),
    MAKE_MESSID(8, 9),
    MAKE_MESSID(8, 10),
    MAKE_MESSID(8, 11),
    MAKE_MESSID(8, 12),
    MAKE_MESSID(8, 13)
};
#else
static s32 lbl_1_data_230[] = {
    MAKE_MESSID(8, 14),
    MAKE_MESSID(8, 15),
    MAKE_MESSID(8, 16),
    MAKE_MESSID(8, 17),
    MAKE_MESSID(8, 18),
    MAKE_MESSID(8, 19),
    MAKE_MESSID(8, 20),
    MAKE_MESSID(8, 21),
    MAKE_MESSID(8, 22),
    MAKE_MESSID(8, 23),
    MAKE_MESSID(8, 24),
    MAKE_MESSID(8, 25),
    MAKE_MESSID(8, 26),
    MAKE_MESSID(8, 27)
};
#endif
void fn_1_6EF0(void) {
    BoardRollDispSet(0);
    lbl_1_bss_90 = HuPrcChildCreate(fn_1_6F80, 0x2003, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_90, fn_1_7210);
    while (lbl_1_bss_90) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

static void fn_1_6F80(void) {
    s32 temp_r31;
    s32 sp8;

    lbl_1_bss_B8 = -1;
    temp_r31 = GWSystem.player_curr;
    sp8 = GWPlayer[temp_r31].space_curr;
    if (BoardSpaceFlagGet(0, GWPlayer[temp_r31].space_curr) & 0x2000) {
        lbl_1_bss_C6 = 0;
        lbl_1_bss_C0 = lbl_1_bss_C[2];
        lbl_1_bss_BC = 0x4A6;
    } else {
        lbl_1_bss_C6 = 1;
        lbl_1_bss_C0 = lbl_1_bss_C[3];
        lbl_1_bss_BC = 0x49B;
    }
    fn_1_72CC(temp_r31);
    fn_1_7760(temp_r31);
    BoardCameraMotionWait();
    BoardModelMotionShiftSet(lbl_1_bss_C0, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    HuPrcSleep(8);
    while (BoardModelMotionTimeGet(lbl_1_bss_C0) < 22.0f) {
        HuPrcVSleep();
    }
    fn_1_7674(temp_r31);
    BoardModelMotionStartEndSet(lbl_1_bss_C0, 30, 60);
    lbl_1_data_228 = 2;
    HuPrcSleep(30);
    fn_1_74BC(1);
    while (!BoardModelMotionEndCheck(lbl_1_data_22C)) {
        HuPrcVSleep();
    }
    lbl_1_data_228 = 3;
    BoardModelHookReset(lbl_1_bss_C0);
    if (lbl_1_bss_B8 != -1) {
        HuAudFXStop(lbl_1_bss_B8);
    }
    BoardModelMotionShiftSet(lbl_1_bss_C0, 0, 60.0f, 8.0f, HU3D_MOTATTR_NONE);
    fn_1_73EC(0.0f);
    fn_1_7574();
    while (!BoardModelMotionEndCheck(lbl_1_bss_C0)) {
        HuPrcVSleep();
    }
    BoardPlayerPostTurnHookSet(temp_r31, fn_1_72A4);
    HuPrcEnd();
}

static void fn_1_7210(void) {
    if (lbl_1_data_22C != -1) {
        BoardModelKill(lbl_1_data_22C);
        lbl_1_data_22C = -1;
    }
    if (lbl_1_data_22A != -1) {
        BoardModelKill(lbl_1_data_22A);
        lbl_1_data_22A = -1;
    }
    lbl_1_bss_90 = NULL;
}

static s32 fn_1_72A4(void) {
    fn_1_74BC(0);
    return 1;
}

static void fn_1_72CC(s32 arg0) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    s32 var_r30;
    s32 i;

    if (lbl_1_bss_C6 == 0) {
        var_r30 = 0x2000;
    } else {
        var_r30 = 0x1000;
    }
    BoardPlayerPosGet(arg0, &sp18);
    BoardModelPosGet(lbl_1_bss_C0, &sp24);
    VECSubtract(&sp24, &sp18, &spC);
    for (i = 0; i < 4; i++) {
        if (var_r30 & BoardSpaceFlagGet(0, GWPlayer[i].space_curr)) {
            lbl_1_bss_C2[i] = 1;
        } else {
            lbl_1_bss_C2[i] = 0;
        }
    }
    fn_1_73EC(atan2d(spC.x, spC.z));
}

static void fn_1_73EC(float arg0) {
    s32 var_r30;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_C2[i] != 0) {
            BoardPlayerMotBlendSet(i, arg0, 15);
        }
    }
    do {
        var_r30 = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_C2[i] != 0 && !BoardPlayerMotBlendCheck(i)) {
                var_r30 = 1;
            }
        }
        HuPrcVSleep();
    } while (var_r30 != 0);
}

static void fn_1_74BC(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_C2[i] == 0) {
            continue;
        }
        if (arg0 != 0) {
            omVibrate(i, 12, 4, 2);
            HuAudFXPlay(lbl_1_data_208[GWPlayer[i].character]);
        }
        BoardPlayerCopyEyeMat(i, arg0);
    }
}

static void fn_1_7574(void) {
    s32 temp_r3;
    s32 temp_r29;
    #if VERSION_PAL
    s32 playerNo = GWSystem.player_curr;
    #endif
    s32 temp_r28;
    s32 i;
    
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_C2[i] == 0) {
            continue;
        }
        temp_r3 = fn_1_7944(i);
        if (temp_r3 != -1) {
            temp_r29 = GWPlayer[i].items[temp_r3];
            BoardPlayerItemRemove(i, temp_r3);
            temp_r28 = BoardPlayerGetCharMess(i);
            BoardWinCreate(0, MAKE_MESSID(48, 16), -1);
            BoardWinInsertMesSet(temp_r28, 0);
            BoardWinInsertMesSet(lbl_1_data_230[temp_r29], 1);
            #if VERSION_PAL
            GWSystem.player_curr = i;
            #endif
            BoardWinPlayerSet(i);
            BoardWinWait();
            BoardWinKill();
        }
    }
    #if VERSION_PAL
    GWSystem.player_curr = playerNo;
    #endif
}

static void fn_1_7674(s32 arg0) {
    Vec sp8;
    float var_f31;

    if (lbl_1_bss_C6 == 0) {
        var_f31 = -90.0f;
    } else {
        var_f31 = 90.0f;
    }
    lbl_1_data_22C = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 15), NULL, 0);
    BoardModelPosGet(lbl_1_bss_C0, &sp8);
    BoardModelMotionStart(lbl_1_data_22C, 0, 0);
    BoardModelHookSet(lbl_1_bss_C0, "fire", lbl_1_data_22C);
    lbl_1_bss_B8 = HuAudFXPlay(lbl_1_bss_BC);
}

static void fn_1_7760(s32 arg0) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    u32 var_r30;
    u32 var_r28;
    s16 var_r29;
    s32 i;

    if (lbl_1_bss_C6 == 0) {
        var_r30 = 0x6000;
    } else {
        var_r30 = 0x5000;
    }
    for (var_r29 = i = 0; i < BoardSpaceCountGet(0); i++) {
        var_r28 = BoardSpaceFlagGet(0, i + 1);
        if (var_r30 == (var_r28 & var_r30)) {
            var_r29 = i + 1;
            break;
        }
    }
    BoardModelPosGet(lbl_1_bss_C0, &sp20);
    BoardSpacePosGet(0, var_r29, &sp2C);
    VECSubtract(&sp2C, &sp20, &sp8);
    sp8.x *= 0.4f;
    sp8.y *= 0.4f;
    sp8.z *= 0.4f;
    VECAdd(&sp20, &sp8, &sp2C);
    lbl_1_data_22A = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 0);
    BoardModelVisibilitySet(lbl_1_data_22A, 0);
    BoardModelPosSetV(lbl_1_data_22A, &sp2C);
    sp14.x = 0.0f;
    sp14.y = 200.0f;
    sp14.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_data_22A, 0, &sp14, 2500.0f, -1.0f, 21);
    BoardCameraMotionWait();
}

static s8 lbl_1_data_26D[] = {
    0, 0, 1, 1, 0,
    0, 1, 1, 1, 1,
    2, 2, 2, 2
};

static s8 lbl_1_data_27B[] = { 40, 30, 20, 10 };

static s8 lbl_1_data_27F[4][2] = {
    { 35, 80 }, { 30, 70 },
    { 20, 60 }, { 10, 50 }
};

static s32 fn_1_7944(s32 arg0) {
    s8 spB[3];
    s8 sp8[3];
    s32 var_r25;
    s32 temp_r26;
    s32 var_r30;
    s32 temp_r27;
    s32 var_r31;
    s32 i;

    var_r25 = BoardPlayerItemCount(arg0);
    if (var_r25 == 0) {
        return -1;
    }
    for (var_r30 = i = 0; i < 3; i++) {
        temp_r26 = GWPlayer[arg0].items[i];
        if (temp_r26 != -1) {
            spB[var_r30] = temp_r26;
            sp8[var_r30] = i;
            var_r30++;
        }
    }
    if (var_r30 == 0) {
        return -1;
    }
    if (var_r30 == 1) {
        return 0;
    }
    temp_r27 = BoardRandMod(100);
    if (lbl_1_data_26D[spB[0]] > lbl_1_data_26D[spB[1]]) {
        if (lbl_1_data_27B[GWPlayer[arg0].rank] > temp_r27) {
            var_r31 = 1;
        } else {
            var_r31 = 0;
        }
    } else if (lbl_1_data_27B[GWPlayer[arg0].rank] > temp_r27) {
        var_r31 = 0;
    } else {
        var_r31 = 1;
    }
    if (var_r30 == 3) {
        if (lbl_1_data_26D[spB[var_r31]] > lbl_1_data_26D[spB[2]]) {
            if (lbl_1_data_27F[GWPlayer[arg0].rank][1] > temp_r27) {
                var_r31 = 2;
            }
        } else if (lbl_1_data_27F[GWPlayer[arg0].rank][1] < temp_r27) {
            var_r31 = 2;
        }
    }
    var_r31 = sp8[var_r31];
    return var_r31;
}

static char *lbl_1_data_394[] = {
    "01 : CHIBI KINOKO",
    "02 : DEKA KINOKO",
    "03 : SUPER CHIBI KINOKO",
    "04 : SUPER DEKA KINOKO",
    "05 : DEKACHIBI HAMMER",
    "06 : WARP DOKAN",
    "07 : TRADE CARD",
    "08 : BIRI-Q SEAL",
    "09 : TERE-YOKE LIGHT",
    "10 : WAN-WAN WHISTLE",
    "11 : KOOPA SUIT",
    "12 : TERESA SUISYO",
    "13 : MAJIN NO LAMP",
    "14 : ITEM BUKURO"
};

static u8 lbl_1_data_3CC[0x4C] = { 0 };
