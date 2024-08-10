#include "REL/w06Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 4;
        u8 unk00_field2 : 1;
    };
    u8 unk01;
    u8 unk02;
    char unk03[1];
    s16 unk04;
} Bss4CWork;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 2;
        u8 unk00_field2 : 4;
    };
    u8 unk01;
    s16 unk02;
    s16 unk04;
} Bss50Work;

// Seems to be the same struct used in w03Dll/mg_coin (unkTemp)
typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ float unk04;
    /* 0x08 */ Vec unk08;
} Bss54WorkData; // Size 0x14

// Seems to be the same struct used in w03Dll/mg_coin (unkTemp2)
typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    char unk01[3];
    s8 unk04;
    char unk05[3];
    float unk08;
    Bss54WorkData *unk0C;
} Bss54Work;

static void fn_1_4B00(void);
static void fn_1_4BA0(void);
static s32 fn_1_4BF8(s32 arg0);
static void fn_1_4FB8(s32 arg0);
static void fn_1_519C(s32 arg0);
static void fn_1_53A0(void);
static void fn_1_5490(s32 arg0);
static void fn_1_56CC(omObjData *arg0);
static void fn_1_57DC(omObjData *arg0, Bss4CWork *arg1);
static void fn_1_587C(omObjData *arg0, Bss4CWork *arg1);
static void fn_1_58FC(omObjData *arg0, Bss4CWork *arg1);
static void fn_1_5968(Vec *arg0);
static void fn_1_59D0(s32 arg0);
static s32 fn_1_5B0C(void);
static void fn_1_5B54(s32 arg0);
static void fn_1_5CE4(s32 arg0);
static s32 fn_1_5EBC(void);
static void fn_1_5EFC(Vec *arg0);
static void fn_1_5F58(s32 arg0, u32 *arg1);
static void fn_1_606C(omObjData *arg0);
static void fn_1_6A0C(omObjData *arg0);
static void fn_1_6C4C(s32 arg0);
static void fn_1_6E90(Bss54Work *arg0);

static s32 lbl_1_bss_8C;
static char lbl_1_bss_5B[49];
static s8 lbl_1_bss_5A;
static s8 lbl_1_bss_59;
static s8 lbl_1_bss_58;
static omObjData *lbl_1_bss_54;
static omObjData *lbl_1_bss_50;
static omObjData *lbl_1_bss_4C;
static Process *lbl_1_bss_48;

static const u8 lbl_1_rodata_F0[] = {
    20, 15, 10, 5, 1
};

static const u8 lbl_1_rodata_F5[] = {
    10, 7, 5, 3, 0, 0, 0
};

static s16 lbl_1_data_1D8 = -1;
static s16 lbl_1_data_1DA = -1;
static s16 lbl_1_data_1DC = -1;

void fn_1_4878(void) {
    Vec sp8;
    float temp_f31;

    lbl_1_data_1DC = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 7), NULL, 0);
    temp_f31 = 0.3f;
    BoardModelPosGet(lbl_1_bss_C[0], &sp8);
    sp8.x += 115.0 * sin(M_PI);
    sp8.z += 115.0 * cos(M_PI);
    sp8.x -= 225.0f;
    BoardModelPosSetV(lbl_1_data_1DC, &sp8);
    BoardModelRotYSet(lbl_1_data_1DC, 90.0f);
    BoardModelScaleSet(lbl_1_data_1DC, temp_f31, temp_f31, temp_f31);
    BoardModelMotionStart(lbl_1_data_1DC, 0, 0);
    BoardModelMotionSpeedSet(lbl_1_data_1DC, 0.0f);
    BoardModelMotionStart(lbl_1_bss_C[0], 0, 0);
    BoardModelMotionSpeedSet(lbl_1_bss_C[0], 0.0f);
}

void fn_1_4A10(void) {
    if (lbl_1_data_1DC != -1) {
        BoardModelKill(lbl_1_data_1DC);
        lbl_1_data_1DC = -1;
    }
}

void fn_1_4A60(void) {
    lbl_1_bss_8C = 0;
    BoardRollDispSet(0);
    lbl_1_bss_48 = HuPrcChildCreate(fn_1_4BA0, 0x2003, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_48, fn_1_4B00);
    while (lbl_1_bss_48) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

static void fn_1_4B00(void) {
    if (lbl_1_data_1DA != -1) {
        BoardModelMotionKill(lbl_1_bss_C[5], lbl_1_data_1DA);
        lbl_1_data_1DA = -1;
    }
    if (lbl_1_data_1D8 != -1) {
        HuWinKill(lbl_1_data_1D8);
        lbl_1_data_1D8 = -1;
    }
    lbl_1_bss_48 = NULL;
}

static void fn_1_4BA0(void) {
    s32 temp_r31;

    temp_r31 = GWSystem.player_curr;
    if (fn_1_4BF8(temp_r31) != 0) {
        fn_1_4FB8(temp_r31);
    }
    fn_1_519C(temp_r31);
    HuPrcEnd();
}

static s32 fn_1_4BF8(s32 arg0) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    BoardWinCreateChoice(2, MAKE_MESSID(48, 26), 6, 0);
    if (GWPlayer[arg0].com) {
        BoardComKeySetLeft();
    }
    BoardWinWait();
    if (BoardWinChoiceGet() != 0) {
        BoardWinCreate(2, MAKE_MESSID(48, 27), 6);
        BoardWinWait();
        BoardWinKill();
        lbl_1_bss_8C = 1;
        return 0;
    }
    BoardWinKill();
    sp14.x = 0.0f;
    sp14.y = 120.0f;
    sp14.z = 0.0f;
    sp8.x = -32.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_C[0], &sp8, &sp14, 1330.0f, -1.0f, 21);
    lbl_1_data_1DA = BoardModelMotionCreate(lbl_1_bss_C[5], DATA_MAKE_NUM(DATADIR_W06, 22));
    BoardCameraMotionWait();
    BoardPlayerPosGet(arg0, &sp2C);
    BoardModelPosGet(lbl_1_bss_C[0], &sp38);
    sp38.x += 115.0 * sin(M_PI);
    sp38.z += 115.0 * cos(M_PI);
    VECSubtract(&sp38, &sp2C, &sp20);
    VECNormalize(&sp20, &sp20);
    BoardPlayerRotYSet(arg0, atan2d(-sp20.x, -sp20.z));
    BoardPlayerPosLerpStart(arg0, &sp2C, &sp38, 40);
    BoardModelPosGet(lbl_1_bss_C[5], &sp2C);
    BoardModelMotionShiftSet(lbl_1_bss_C[5], lbl_1_data_1DA, 0.0f, 8.0f, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_bss_C[5], 2.0f);
    while (GWPlayer[arg0].moving) {
        BoardPlayerPosGet(arg0, &sp38);
        VECSubtract(&sp38, &sp2C, &sp20);
        BoardModelRotYSet(lbl_1_bss_C[5], atan2d(sp20.x, sp20.z));
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_bss_C[5], 1, 0.0f, 8.0f, 0x40000001);
    BoardPlayerIdleSet(arg0);
    BoardPlayerRotYSet(arg0, -90.0f);
    BoardAudSeqPause(0, 1, 1000);
    HuPrcSleep(60);
    return 1;
}

static void fn_1_4FB8(s32 arg0) {
    s16 temp_r30;

    BoardMusStart(1, 0x27, 0x7F, 0);
    temp_r30 = MGSeqCreate(3, 0);
    while (MGSeqStatGet(temp_r30) != 0) {
        HuPrcVSleep();
    }
    fn_1_53A0();
    fn_1_5490(arg0);
    fn_1_5B54(arg0);
    while (TRUE) {
        if (fn_1_5EBC() == 4 && fn_1_5B0C() == 4) {
            break;
        }
        HuPrcVSleep();
    }
    HuWinDispOff(lbl_1_data_1D8);
    BoardAudSeqFadeOut(1, 1000);
    HuPrcSleep(30);
    lbl_1_bss_58 = lbl_1_rodata_F0[lbl_1_bss_5A - 1];
    sprintf(lbl_1_bss_5B, "%d", lbl_1_bss_58);
    BoardAudSeqPause(0, 0, 1000);
    BoardWinCreate(2, MAKE_MESSID(48, 28), 6);
    BoardWinInsertMesSet(MAKE_MESSID_PTR(lbl_1_bss_5B), 0);
    BoardWinWait();
    BoardWinKill();
    fn_1_6C4C(arg0);
    while (lbl_1_bss_54) {
        HuPrcVSleep();
    }
    BoardPlayerMotionShiftSet(arg0, 7, 0.0f, 8.0f, 0);
    HuPrcSleep(8);
    while (!BoardPlayerMotionEndCheck(arg0)) {
        HuPrcVSleep();
    }
    BoardWinCreate(2, MAKE_MESSID(48, 29), 6);
    BoardWinWait();
    BoardWinKill();
}

static void fn_1_519C(s32 arg0) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s16 temp_r30;

    if (lbl_1_bss_8C == 0) {
        temp_r30 = GWPlayer[arg0].space_curr;
        BoardPlayerPosGet(arg0, &sp20);
        BoardSpacePosGet(0, temp_r30, &sp14);
    }
    BoardCameraTargetPlayerSet(arg0);
    BoardCameraViewSet(1);
    if (lbl_1_bss_8C == 0) {
        BoardPlayerPosLerpStart(arg0, &sp20, &sp14, 40);
        BoardModelPosGet(lbl_1_bss_C[5], &sp20);
        BoardModelMotionShiftSet(lbl_1_bss_C[5], lbl_1_data_1DA, 0.0f, 8.0f, 0x40000001);
        BoardModelMotionSpeedSet(lbl_1_bss_C[5], 2.0f);
        while (GWPlayer[arg0].moving) {
            BoardPlayerPosGet(arg0, &sp14);
            VECSubtract(&sp14, &sp20, &sp8);
            BoardModelRotYSet(lbl_1_bss_C[5], atan2d(sp8.x, sp8.z));
            HuPrcVSleep();
        }
        BoardModelMotionShiftSet(lbl_1_bss_C[5], 1, 0.0f, 8.0f, 0x40000001);
    }
    BoardModelRotYSet(lbl_1_bss_C[5], 0.0f);
    BoardCameraMotionWait();
    fn_1_59D0(5);
    fn_1_5CE4(5);
}

static void fn_1_53A0(void) {
    float sp8[2];
    float var_f31;
    float var_f30;

    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(48, 30));
    var_f31 = -10000.0f;
    var_f30 = 328.0f;
    lbl_1_data_1D8 = HuWinCreate(var_f31, var_f30, sp8[0], sp8[1], 0);
    HuWinBGTPLvlSet(lbl_1_data_1D8, 0.0f);
    HuWinMesSpeedSet(lbl_1_data_1D8, 0);
    HuWinMesSet(lbl_1_data_1D8, MAKE_MESSID(48, 30));
}

static void fn_1_5490(s32 arg0) {
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    float temp_f31;
    omObjData *temp_r3;
    Bss4CWork *temp_r31;
    s32 spC[] = {
        DATA_MAKE_NUM(DATADIR_W06, 28),
        DATA_MAKE_NUM(DATADIR_W06, 29),
        -1
    };

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_56CC);
    lbl_1_bss_4C = temp_r3;
    temp_r31 = OM_GET_WORK_PTR(temp_r3, Bss4CWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk02 = 0;
    temp_r31->unk00_field2 = 0;
    temp_r31->unk00_field1 = 2;
    BoardModelPosGet(lbl_1_data_1DC, &sp3C);
    sp3C.x += 50.0f;
    BoardPlayerPosGet(arg0, &sp30);
    sp30.x -= 10.0f;
    VECSubtract(&sp30, &sp3C, &sp24);
    VECNormalize(&sp24, &sp18);
    temp_r3->trans.x = sp24.x / 60.0f;
    temp_r3->trans.y = sp24.y / 60.0f;
    temp_r3->trans.z = sp24.z / 60.0f;
    temp_r31->unk04 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 27), spC, 0);
    temp_f31 = 0.3f;
    BoardModelPosSetV(temp_r31->unk04, &sp3C);
    BoardModelScaleSet(temp_r31->unk04, temp_f31, temp_f31, temp_f31);
    BoardModelVisibilitySet(temp_r31->unk04, 0);
    BoardModelRotYSet(temp_r31->unk04, atan2d(sp18.x, sp18.z));
    BoardModelMotionStart(temp_r31->unk04, 1, 0x40000001);
    BoardModelMotionStart(lbl_1_data_1DC, 0, 0);
}

static void fn_1_56CC(omObjData *arg0) {
    Bss4CWork *temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, Bss4CWork);
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        BoardModelKill(temp_r31->unk04);
        lbl_1_bss_4C = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r31->unk02 != 0) {
        temp_r31->unk02--;
        return;
    }
    switch (temp_r31->unk00_field1) {
        case 0:
            break;
        case 1:
            fn_1_57DC(arg0, temp_r31);
            break;
        case 4:
            fn_1_58FC(arg0, temp_r31);
            break;
        case 2:
            fn_1_587C(arg0, temp_r31);
            break;
        case 5:
            temp_r31->unk00_field0 = 1;
            break;
    }
}

static void fn_1_57DC(omObjData *arg0, Bss4CWork *arg1) {
    Vec sp8;

    if (arg1->unk01 == 0) {
        fn_1_59D0(3);
        return;
    }
    BoardModelPosGet(arg1->unk04, &sp8);
    sp8.x += arg0->trans.x;
    sp8.y += arg0->trans.y;
    sp8.z += arg0->trans.z;
    BoardModelPosSetV(arg1->unk04, &sp8);
    arg1->unk01--;
}

static void fn_1_587C(omObjData *arg0, Bss4CWork *arg1) {
    if (BoardModelMotionTimeGet(lbl_1_data_1DC) < 32.0f) {
        return;
    }
    arg1->unk00_field1 = 1;
    arg1->unk01 = 60;
    HuAudFXPlayVolPan(0x49E, 0x7F, 0x20);
    BoardModelVisibilitySet(arg1->unk04, 1);
}

static void fn_1_58FC(omObjData *arg0, Bss4CWork *arg1) {
    if (arg1->unk00_field2 == 0) {
        HuAudFXPlay(0x49F);
        arg1->unk00_field2 = 1;
    }
    if (BoardModelMotionEndCheck(arg1->unk04)) {
        fn_1_59D0(0);
    }
}

static void fn_1_5968(Vec *arg0) {
    Bss4CWork *temp_r31;

    if (lbl_1_bss_4C && arg0) {
        temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_4C, Bss4CWork);
        BoardModelPosGet(temp_r31->unk04, arg0);
    }
}

static void fn_1_59D0(s32 arg0) {
    Bss4CWork *temp_r31;

    if (!lbl_1_bss_4C) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_4C, Bss4CWork);
    temp_r31->unk00_field1 = arg0;
    if (arg0 == 1) {
        lbl_1_bss_4C->trans.x = 0.96666666f * sind(90);
        lbl_1_bss_4C->trans.z = 0.96666666f * cosd(90);
        temp_r31->unk01 = 60;
        return;
    }
    if (arg0 == 0) {
        BoardPlayerMotionSpeedSet(temp_r31->unk04, 1.0f);
        return;
    }
    if (arg0 == 4) {
        BoardModelMotionShiftSet(temp_r31->unk04, 2, 0.0f, 8.0f, 0);
        temp_r31->unk02 = 10;
        return;
    }
}

static s32 fn_1_5B0C(void) {
    Bss4CWork *temp_r31;

    if (lbl_1_bss_4C) {
        temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_4C, Bss4CWork);
        return temp_r31->unk00_field1;
    }
    return -1;
}

static s32 lbl_1_data_1E4[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 126),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 126),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 126),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 126),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 126),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 126),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 126),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 126)
};

static void fn_1_5B54(s32 arg0) {
    Vec sp8;
    float var_f31;
    omObjData *temp_r3;
    Bss50Work *temp_r31;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_606C);
    lbl_1_bss_50 = temp_r3;
    temp_r31 = OM_GET_WORK_PTR(temp_r3, Bss50Work);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field1 = arg0;
    temp_r31->unk01 = 0;
    temp_r31->unk00_field2 = 1;
    temp_r31->unk04 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 13), NULL, 0);
    temp_r31->unk02 = BoardPlayerMotionCreate(arg0, lbl_1_data_1E4[GWPlayer[arg0].character]);
    var_f31 = 0.3f;
    BoardModelScaleSet(temp_r31->unk04, var_f31, var_f31, var_f31);
    BoardPlayerPosGet(temp_r31->unk00_field1, &sp8);
    BoardModelPosSetV(temp_r31->unk04, &sp8);
    BoardModelVisibilitySet(temp_r31->unk04, 0);
    temp_r3->trans.x = sp8.x;
    temp_r3->trans.y = sp8.y;
    temp_r3->trans.z = sp8.z;
    lbl_1_bss_59 = 0;
    lbl_1_bss_5A = 0;
}

static void fn_1_5CE4(s32 arg0) {
    Vec sp14;
    Vec sp8;
    Bss50Work *temp_r31;

    if (!lbl_1_bss_50) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_50, Bss50Work);
    temp_r31->unk00_field2 = arg0;
    if (arg0 == 2) {
        temp_r31->unk01 = 60;
        BoardPlayerPosGet(temp_r31->unk00_field1, &sp8);
        if (lbl_1_bss_5A >= 1) {
            BoardModelVisibilitySet(temp_r31->unk04, 1);
        }
        BoardModelMotionStart(temp_r31->unk04, 0, 0x40000001);
        BoardPlayerMotionStart(temp_r31->unk00_field1, temp_r31->unk02, 0x40000001);
        omVibrate(temp_r31->unk00_field1, 12, 4, 2);
        fn_1_5968(&sp14);
        sp8.x = sp14.x + 18.0 * sind(90);
        sp8.z = sp14.z + 18.0 * cosd(90);
        BoardPlayerPosSetV(temp_r31->unk00_field1, &sp8);
        BoardModelPosSetV(temp_r31->unk04, &sp8);
        return;
    }
    if (arg0 == 3) {
        BoardModelVisibilitySet(temp_r31->unk04, 0);
        BoardPlayerMotionStart(temp_r31->unk00_field1, temp_r31->unk02, 0x40000001);
        return;
    }
}

static s32 fn_1_5EBC(void) {
    Bss50Work *temp_r31;

    if (!lbl_1_bss_50) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_50, Bss50Work);
    return temp_r31->unk00_field2;
}

static void fn_1_5EFC(Vec *arg0) {
    Bss50Work *temp_r31;

    if (lbl_1_bss_50) {
        temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_50, Bss50Work);
        BoardPlayerPosGet(temp_r31->unk00_field1, arg0);
    }
}

static void fn_1_5F58(s32 arg0, u32 *arg1) {
    u32 var_r31;
    s32 var_r28;
    s32 temp_r30;

    var_r31 = 0;
    var_r28 = GWPlayer[arg0].port;
    if (GWPlayer[arg0].com) {
        temp_r30 = BoardRandMod(100);
        switch (GWPlayer[arg0].diff) {
            case 0:
                if (temp_r30 < 12) {
                    var_r31 = 0x100;
                }
                break;
            case 1:
                if (temp_r30 < 22) {
                    var_r31 = 0x100;
                }
                break;
            case 2:
                if (temp_r30 < 50) {
                    var_r31 = 0x100;
                }
                break;
            case 3:
                var_r31 = 0x100;
                break;
        }
    } else {
        var_r31 = HuPadBtnDown[var_r28] & 0x100;
    }
    *arg1 = var_r31;
}

static void fn_1_606C(omObjData *arg0) {
    Vec sp64;
    Vec sp58;
    u32 var_r18;
    Bss50Work *temp_r31;

    var_r18 = 0;
    temp_r31 = OM_GET_WORK_PTR(arg0, Bss50Work);
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        BoardPlayerMotionKill(temp_r31->unk00_field1, temp_r31->unk02);
        BoardModelKill(temp_r31->unk04);
        lbl_1_bss_50 = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    switch (temp_r31->unk00_field2) {
        case 0:
            break;
        case 1:
            if (fn_1_5B0C() == 3) {
                fn_1_5CE4(2);
            }
            break;
        case 2:
            if (temp_r31->unk01 == 0) {
                if (lbl_1_bss_5A >= 5) {
                    fn_1_5CE4(4);
                    fn_1_59D0(4);
                } else {
                    fn_1_5CE4(3);
                    fn_1_59D0(1);
                    lbl_1_bss_59 = 0;
                    lbl_1_bss_5A++;
                }
            } else {
                fn_1_5F58(temp_r31->unk00_field1, &var_r18);
                if (var_r18 == 0x100) {
                    lbl_1_bss_59++;
                    if (lbl_1_bss_5A != 0 && lbl_1_bss_59 >= lbl_1_rodata_F5[lbl_1_bss_5A - 1]) {
                        fn_1_5CE4(4);
                        fn_1_59D0(4);
                    }
                    BoardPlayerMotionStart(temp_r31->unk00_field1, temp_r31->unk02, 0x40000001);
                }
                temp_r31->unk01--;
            }
            break;
        case 3:
            if (fn_1_5B0C() == 3) {
                fn_1_5CE4(2);
                return;
            }
            fn_1_5968(&sp64);
            BoardPlayerPosGet(temp_r31->unk00_field1, &sp58);
            sp58.x = sp64.x + 18.0 * sind(90);
            sp58.z = sp64.z + 18.0 * cosd(90);
            BoardPlayerPosSetV(temp_r31->unk00_field1, &sp58);
            BoardModelPosSetV(temp_r31->unk04, &sp58);
            BoardModelRotYSet(temp_r31->unk04, BoardPlayerRotYGet(temp_r31->unk00_field1));
            break;
        case 5:
            temp_r31->unk00_field0 = 1;
            /* fallthrough */
        case 4:
            BoardPlayerIdleSet(temp_r31->unk00_field1);
            BoardPlayerRotYSet(temp_r31->unk00_field1, 0.0f);
            BoardModelVisibilitySet(temp_r31->unk04, 0);
            fn_1_5CE4(0);
            break;
    }
}

static void fn_1_6A0C(omObjData *arg0) {
    float temp_f31;
    Bss54Work *temp_r29;
    Bss54WorkData *var_r30;
    s32 var_r26;
    s32 var_r27;
    s32 i;

    temp_r29 = OM_GET_WORK_PTR(arg0, Bss54Work);
    if (temp_r29->unk00_field0 != 0 || BoardIsKill()) {
        fn_1_6E90(temp_r29);
        HuMemDirectFree(temp_r29->unk0C);
        lbl_1_bss_54 = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    var_r30 = temp_r29->unk0C;
    for (var_r27 = i = 0; i < 20; i++, var_r30++) {
        if (var_r30->unk00 == 0) {
            var_r27++;
        }
    }
    if (var_r27 == 20) {
        temp_r29->unk00_field0 = 1;
        return;
    }
    var_r26 = 0;
    for (i = 0; i < 20; i++) {
        var_r30 = &temp_r29->unk0C[i];
        if (var_r30->unk00 == 1 && var_r26 == 0) {
            var_r30->unk00 = 2;
            var_r26 = 1;
        }
        if (var_r30->unk00 == 2) {
            var_r30->unk01++;
            OSu8tof32(&var_r30->unk01, &temp_f31);
            var_r30->unk04 += 45.0f;
            var_r30->unk08.y += -0.08166667f * temp_f31 * temp_f31 * 0.75f;
            if (var_r30->unk08.y < temp_r29->unk08) {
                var_r30->unk08.y = temp_r29->unk08;
                CharModelCoinEffectCreate(1, &var_r30->unk08);
                BoardModelVisibilitySet(var_r30->unk02, 0);
                HuAudFXPlay(7);
                BoardPlayerCoinsAdd(temp_r29->unk04, 1);
                omVibrate(temp_r29->unk04, 12, 6, 6);
                var_r30->unk00 = 0;
            }
            BoardModelPosSetV(var_r30->unk02, &var_r30->unk08);
            BoardModelRotYSet(var_r30->unk02, var_r30->unk04);
        }
    }
}

static void fn_1_6C4C(s32 arg0) {
    Vec sp8;
    float var_f31;
    omObjData *temp_r3;
    Bss54Work *temp_r30;
    Bss54WorkData *temp_r31;
    s32 i;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_6A0C);
    lbl_1_bss_54 = temp_r3;
    temp_r30 = OM_GET_WORK_PTR(temp_r3, Bss54Work);
    temp_r30->unk00_field0 = 0;
    temp_r30->unk04 = arg0;
    temp_r30->unk0C = HuMemDirectMallocNum(HEAP_SYSTEM, 20 * sizeof(Bss54WorkData), MEMORY_DEFAULT_NUM);
    BoardPlayerPosGet(arg0, &sp8);
    temp_r30->unk08 = sp8.y + 80.0f;
    memset(temp_r30->unk0C, 0, 20 * sizeof(Bss54WorkData));
    for (i = 0; i < lbl_1_bss_58; i++) {
        if (i == 0) {
            var_f31 = 0.0f;
        } else {
            var_f31 = BoardRandFloat();
        }
        temp_r31 = &temp_r30->unk0C[i];
        temp_r31->unk00 = 1;
        temp_r31->unk08.x = sp8.x + 50.0 * sind(360.0f * var_f31);
        temp_r31->unk08.z = sp8.z + 50.0 * cosd(360.0f * var_f31);
        temp_r31->unk08.y = sp8.y + 600.0f + 500.0f * BoardRandFloat();
        temp_r31->unk01 = 0;
        temp_r31->unk04 = 360.0f * BoardRandFloat();
        temp_r31->unk02 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 1);
    }
}

static void fn_1_6E90(Bss54Work *arg0) {
    Bss54WorkData *var_r30;
    s32 i;

    for (i = 0; i < 20; i++) {
        var_r30 = &arg0->unk0C[i];
        BoardModelKill(var_r30->unk02);
    }
}
