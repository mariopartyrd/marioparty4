#include "REL/w06Dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/object.h"
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

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        u8 unk00_field2 : 1;
        u8 unk00_field3 : 1;
        u8 unk00_field4 : 1;
    };
    u8 unk01;
    s8 unk02;
    s8 unk03;
    s16 unk04;
    char unk06[2];
    float unk08;
} BssCCWork;

static void fn_1_8320(void);
static void fn_1_8420(void);
static s32 fn_1_8490(s32 arg0, s8 arg1);
static void fn_1_8A58(omObjData *arg0);

static s8 lbl_1_bss_E6;
static s16 lbl_1_bss_E4;
static s16 lbl_1_bss_E2;
static s16 lbl_1_bss_D6[3][2];
static s16 lbl_1_bss_D0[3];
static omObjData *lbl_1_bss_CC;
static Process *lbl_1_bss_C8;

static s16 lbl_1_data_418 = -1;

static float lbl_1_data_41C[][2] = {
    {  90.0f, 180.0f },
    { -90.0f,   0.0f },
    { 180.0f,   0.0f }
};

static s32 lbl_1_data_434[][2] = {
    { 0x00000200, 0x00000100 },
    { 0x00000080, 0x00000040 },
    { 0x00000800, 0x00000400 }
};

static s32 lbl_1_data_44C[] = {
    DATA_MAKE_NUM(DATADIR_W06, 3),
    DATA_MAKE_NUM(DATADIR_W06, 3),
    DATA_MAKE_NUM(DATADIR_W06, 4)
};

static s32 lbl_1_data_458[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 26),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 26),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 26),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 26),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 26),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 26),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 26),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 26),
};

static s32 lbl_1_data_478[8] = {
    DATA_MAKE_NUM(DATADIR_W06, 30),
    DATA_MAKE_NUM(DATADIR_W06, 31),
    DATA_MAKE_NUM(DATADIR_W06, 32),
    DATA_MAKE_NUM(DATADIR_W06, 33),
    DATA_MAKE_NUM(DATADIR_W06, 34),
    DATA_MAKE_NUM(DATADIR_W06, 35),
    DATA_MAKE_NUM(DATADIR_W06, 36),
    DATA_MAKE_NUM(DATADIR_W06, 37)
};

void fn_1_7BB0(void) {
    Vec sp8;
    float var_f29;
    BoardSpace *var_r26;
    s16 temp_r27;
    s32 var_r28;
    s32 i;

    if (GWSystem.star_pos < 4) {
        lbl_1_bss_0->unk00_field2 = 0;
    } else {
        lbl_1_bss_0->unk00_field2 = 1;
    }
    for (i = 0; i < 3; i++) {
        lbl_1_bss_D0[i] = BoardModelCreate(lbl_1_data_44C[i], NULL, 0);
        switch (i) {
            case 0:
                var_r28 = (lbl_1_bss_0->unk00_field0 != 0) ? 1 : 0;
                OSs8tof32(&lbl_1_bss_0->unk01, &var_f29);
                break;
            case 1:
                var_r28 = (lbl_1_bss_0->unk00_field1 != 0) ? 1 : 0;
                OSs8tof32(&lbl_1_bss_0->unk02, &var_f29);
                break;
            case 2:
                var_r28 = (lbl_1_bss_0->unk00_field2 != 0) ? 1 : 0;
                var_f29 = 0.0f;
                break;
        }
        temp_r27 = BoardSpaceFlagPosGet(0, lbl_1_data_434[i][var_r28], &sp8);
        BoardModelPosSetV(lbl_1_bss_D0[i], &sp8);
        BoardModelRotYSet(lbl_1_bss_D0[i], lbl_1_data_41C[i][var_r28]);
        BoardModelMotionShiftSet(lbl_1_bss_D0[i], 0, 60.0f * var_f29, 0.0f, 0);
        HuPrcSleep(2);
        BoardModelMotionSpeedSet(lbl_1_bss_D0[i], 0.0f);
        lbl_1_bss_D6[i][var_r28] = temp_r27;
        temp_r27 = BoardSpaceFlagSearch(0, lbl_1_data_434[i][var_r28 ^ 1]);
        var_r26 = BoardSpaceGet(0, temp_r27);
        var_r26->flag |= 0x04000000;
        lbl_1_bss_D6[i][var_r28 ^ 1] = temp_r27;
    }
}

void fn_1_7F3C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        BoardModelKill(lbl_1_bss_D0[i]);
        lbl_1_bss_D0[i] = -1;
    }
}

void fn_1_7FA4(void) {
    Vec sp8;
    float temp_f31;
    BoardSpace *temp_r3;
    s16 temp_r30;
    s16 temp_r29;
    s16 var_r31;

    if (GWSystem.star_pos < 4) {
        lbl_1_bss_0->unk00_field2 = 0;
    } else {
        lbl_1_bss_0->unk00_field2 = 1;
    }
    var_r31 = 2;
    temp_r30 = (lbl_1_bss_0->unk00_field2 != 0) ? 1 : 0;
    temp_f31 = 0.0f;
    temp_r29 = BoardSpaceFlagPosGet(0, lbl_1_data_434[var_r31][temp_r30], &sp8);
    BoardModelPosSetV(lbl_1_bss_D0[var_r31], &sp8);
    BoardModelRotYSet(lbl_1_bss_D0[var_r31], lbl_1_data_41C[var_r31][temp_r30]);
    BoardModelMotionShiftSet(lbl_1_bss_D0[var_r31], 0, 60.0f * temp_f31, 0.0f, 0);
    HuPrcSleep(2);
    BoardModelMotionSpeedSet(lbl_1_bss_D0[var_r31], 0.0f);
    lbl_1_bss_D6[var_r31][temp_r30] = temp_r29;
    temp_r29 = BoardSpaceFlagSearch(0, lbl_1_data_434[var_r31][temp_r30]);
    temp_r3 = BoardSpaceGet(0, temp_r29);
    temp_r3->flag &= ~0x04000000;
    temp_r29 = BoardSpaceFlagSearch(0, lbl_1_data_434[var_r31][temp_r30 ^ 1]);
    temp_r3 = BoardSpaceGet(0, temp_r29);
    temp_r3->flag |= 0x04000000;
    lbl_1_bss_D6[var_r31][temp_r30 ^ 1] = temp_r29;
}

void fn_1_8264(s32 arg0, s16 arg1) {
    BoardRollDispSet(0);
    lbl_1_bss_E6 = arg0;
    lbl_1_bss_E4 = arg1;
    lbl_1_bss_C8 = HuPrcChildCreate(fn_1_8320, 0x2003, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_C8, fn_1_8420);
    while (lbl_1_bss_C8) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

static void fn_1_8320(void) {
    s32 temp_r30;
    s8 *var_r31;
    BoardSpace *var_r29;

    temp_r30 = GWSystem.player_curr;
    if (lbl_1_bss_E6 != 0) {
        var_r31 = &lbl_1_bss_0->unk02;
    } else {
        var_r31 = &lbl_1_bss_0->unk01;
    }
    var_r29 = BoardSpaceGet(0, lbl_1_bss_E4);
    lbl_1_bss_E2 = var_r29->link[0];
    GWPlayer[temp_r30].space_curr = lbl_1_bss_E2;
    fn_1_8490(temp_r30, *var_r31);
    (*var_r31)++;
    if (*var_r31 >= 3) {
        *var_r31 = 0;
    }
    HuPrcEnd();
}

static void fn_1_8420(void) {
    if (lbl_1_data_418 != -1) {
        BoardPlayerMotionKill(GWSystem.player_curr, lbl_1_data_418);
        lbl_1_data_418 = -1;
    }
    lbl_1_bss_C8 = NULL;
}

static s32 fn_1_8490(s32 arg0, s8 arg1) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f30;
    float var_f29;
    float var_f28;
    s32 temp_r27;
    omObjData *var_r26;
    BssCCWork *temp_r29;
    s8 var_r28;

    BoardPlayerPosGet(arg0, &sp18);
    BoardSpacePosGet(0, lbl_1_bss_E2, &sp24);
    VECSubtract(&sp24, &sp18, &spC);
    temp_f30 = atan2d(spC.x, spC.z);
    BoardPlayerMotBlendSet(arg0, temp_f30, 0xF);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(arg0);
    HuPrcSleep(11);
    temp_r27 = GWPlayer[arg0].character;
    switch (arg1) {
        case 0:
            lbl_1_data_418 = -1;
            var_f29 = 60.0f;
            var_f28 = 1.0f;
            break;
        case 1:
            lbl_1_data_418 = BoardPlayerMotionCreate(arg0, lbl_1_data_478[temp_r27]);
            var_f29 = 50.0f;
            var_f28 = 2.5f;
            if (GWPlayer[arg0].bowser_suit) {
                BoardPlayerIdleSet(arg0);
                HuPrcSleep(30);
            } else {
                BoardPlayerMotionShiftSet(arg0, lbl_1_data_418, 0.0f, 6.0f, 0);
                BoardPlayerMotionSpeedSet(arg0, 1.5f);
                HuPrcSleep(60);
            }
            break;
        case 2:
            lbl_1_data_418 = BoardPlayerMotionCreate(arg0, lbl_1_data_458[temp_r27]);
            var_f29 = 40.0f;
            var_f28 = 2.0f;
            if (GWPlayer[arg0].bowser_suit) {
                BoardPlayerIdleSet(arg0);
                HuPrcSleep(30);
            } else {
                BoardPlayerMotionShiftSet(arg0, lbl_1_data_418, 0.0f, 6.0f, 0x40000001);
                BoardPlayerMotionSpeedSet(arg0, 3.0f);
                HuPrcSleep(60);
            }
            break;
    }
    var_r26 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_8A58);
    lbl_1_bss_CC = var_r26;
    temp_r29 = OM_GET_WORK_PTR(var_r26, BssCCWork);
    temp_r29->unk00_field0 = 0;
    temp_r29->unk00_field1 = 0;
    temp_r29->unk00_field2 = 0;
    temp_r29->unk00_field3 = 0;
    temp_r29->unk00_field4 = 0;
    temp_r29->unk01 = 0;
    temp_r29->unk03 = arg1;
    temp_r29->unk02 = 0;
    temp_r29->unk04 = lbl_1_bss_D0[lbl_1_bss_E6];
    OSs8tof32(&arg1, &temp_r29->unk08);
    temp_r29->unk08 = 60.0f * (temp_r29->unk08 + 1.0f);
    BoardPlayerPosLerpStart(arg0, &sp18, &sp24, var_f29);
    BoardPlayerMotionSpeedSet(arg0, var_f28);
    for (var_r28 = 0; GWPlayer[arg0].moving; var_r28++) {
        if (!(var_r28 & 0xF)) {
            omVibrate(arg0, 12, 6, 6);
        }
        HuPrcVSleep();
    }
    temp_f30 -= 180.0f;
    BoardPlayerMotBlendSet(arg0, temp_f30, 0xF);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    while (lbl_1_bss_CC) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    if (arg1 == 2) {
        BoardWinCreate(0, MAKE_MESSID(48, 40), -1);
        BoardWinWait();
        BoardWinKill();
    }
    BoardCameraTargetPlayerSet(arg0);
    BoardCameraViewSet(1);
    temp_f30 += 180.0f;
    BoardPlayerMotBlendSet(arg0, temp_f30, 0xF);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    if (arg1 == 1) {
        BoardWinCreate(0, MAKE_MESSID(48, 15), -1);
        BoardWinWait();
        BoardWinKill();
    }
    return 0;
}

static void fn_1_8A58(omObjData *arg0) {
    Vec sp8;
    u8 var_r30;
    BoardSpace *var_r29;
    BssCCWork *temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, BssCCWork);
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        lbl_1_bss_CC = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r31->unk01 != 0) {
        temp_r31->unk01--;
        return;
    }
    if (temp_r31->unk00_field1 != 0 && temp_r31->unk00_field4 == 0) {
        BoardModelMotionStart(temp_r31->unk04, 0, 0);
        BoardModelMotionTimeSet(temp_r31->unk04, temp_r31->unk08 - 60.0f);
        BoardModelMotionSpeedSet(temp_r31->unk04, 1.0f);
        temp_r31->unk00_field4 = 1;
    }
    if (temp_r31->unk00_field2 != 0) {
        HuAudFXPlay(0x49C);
        temp_r31->unk00_field2 = 0;
    }
    if (temp_r31->unk00_field3 != 0) {
        HuAudFXPlay(0x49D);
        temp_r31->unk00_field3 = 0;
    }
    switch (temp_r31->unk02) {
        case 0:
            if (temp_r31->unk00_field1 == 0) {
                if (GWPlayer[GWSystem.player_curr].bowser_suit != 0) {
                    temp_r31->unk01 = 72;
                } else {
                    temp_r31->unk01 = 30;
                }
                temp_r31->unk00_field2 = 1;
                temp_r31->unk00_field1 = 1;
                break;
            }
            if (BoardModelMotionTimeGet(temp_r31->unk04) >= temp_r31->unk08) {
                BoardModelMotionTimeSet(temp_r31->unk04, temp_r31->unk08);
                BoardModelMotionSpeedSet(temp_r31->unk04, 0.0f);
                if (temp_r31->unk03 == 2) {
                    temp_r31->unk01 = 30;
                    temp_r31->unk02 = 1;
                    temp_r31->unk00_field3 = 1;
                } else {
                    temp_r31->unk00_field0 = 1;
                }
            }
            break;
        case 1:
            if (lbl_1_bss_E6 == 0) {
                var_r30 = lbl_1_bss_0->unk00_field0;
                lbl_1_bss_0->unk00_field0 ^= 1;
            } else {
                var_r30 = lbl_1_bss_0->unk00_field1;
                lbl_1_bss_0->unk00_field1 ^= 1;
            }
            var_r29 = BoardSpaceGet(0, lbl_1_bss_D6[lbl_1_bss_E6][var_r30]);
            var_r29->flag |= 0x04000000;
            var_r29 = BoardSpaceGet(0, lbl_1_bss_D6[lbl_1_bss_E6][var_r30 ^ 1]);
            var_r29->flag &= ~0x04000000;
            BoardSpacePosGet(0, lbl_1_bss_D6[lbl_1_bss_E6][var_r30 ^ 1], &sp8);
            BoardModelMotionStart(temp_r31->unk04, 0, 0);
            BoardModelMotionTimeSet(temp_r31->unk04, 180.0f);
            BoardModelPosSetV(temp_r31->unk04, &sp8);
            BoardModelRotYSet(temp_r31->unk04, lbl_1_data_41C[lbl_1_bss_E6][var_r30 ^ 1]);
            BoardCameraTargetModelSet(temp_r31->unk04);
            temp_r31->unk02 = 2;
            break;
        case 2:
            if (BoardModelMotionEndCheck(temp_r31->unk04) && BoardCameraMotionIsDone()) {
                temp_r31->unk00_field0 = 1;
            }
            break;
    }
}
