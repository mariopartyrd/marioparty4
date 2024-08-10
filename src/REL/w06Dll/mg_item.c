#include "REL/w06Dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/frand.h"
#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 2;
        u8 unk00_field2 : 2;
        u8 unk00_field3 : 1;
        u8 unk00_field4 : 1;
    };
    u8 unk01;
    s8 unk02;
    s8 unk03;
    char unk04[2];
    s16 unk06;
    s16 unk08;
    char unk0A[2];
    s32 unk0C;
} Data1B4Work;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 2;
        u8 unk00_field2 : 1;
    };
    s8 unk01;
    s8 unk02;
    s8 unk03;
} Bss24Work;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 3;
        u8 unk00_field2 : 1;
        u8 unk00_field3 : 1;
    };
    s8 unk01[2];
    s8 unk03;
    u8 unk04;
    char unk05[1];
    s16 unk06;
    s16 unk08;
    s16 unk0A;
} Bss28Work;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    u8 unk01;
    u8 unk02;
    char unk03[1];
    s16 unk04;
} Bss2CWork;

static void fn_1_10E4(void);
static void fn_1_1148(void);
static void fn_1_11B0(void);
static s32 fn_1_12A0(s32 arg0);
static void fn_1_15CC(s32 arg0);
static void fn_1_1BE0(s32 arg0, s32 arg1);
static void fn_1_1CB0(s32 arg0);
static void fn_1_1D5C(s32 arg0);
static void fn_1_1E30(s32 arg0);
static void fn_1_1F08(s32 arg0);
static void fn_1_2048(s32 arg0, s32 arg1);
static void fn_1_20CC(s32 arg0);
static s32 fn_1_2174(s32 arg0);
static s16 fn_1_21CC(s32 arg0);
static void fn_1_2220(s32 arg0, s32 arg1, s32 arg2);
static void fn_1_243C(omObjData *arg0);
static s32 fn_1_2A1C(s32 arg0);
static void fn_1_2B60(s32 arg0);
static void fn_1_2C18(void);
static void fn_1_2D90(s32 arg0);
static s32 fn_1_2DD0(void);
static u32 fn_1_2E18(Bss24Work *arg0);
static void fn_1_2EF4(omObjData *arg0);
static void fn_1_3470(void);
static void fn_1_3560(s32 arg0);
static s32 fn_1_35BC(void);
static void fn_1_3604(s32 arg0);
static void fn_1_3698(s8 arg0);
static void fn_1_3974(omObjData *arg0);
static void fn_1_4070(void);
static void fn_1_4124(void);
static void fn_1_4194(omObjData *arg0);
static void fn_1_42AC(s16 arg0);
static void fn_1_43DC(void);
static void fn_1_4460(ModelData *model, ParticleData *particle, Mtx matrix);

static s16 lbl_1_bss_3C[3];
static s16 lbl_1_bss_36[3];
static s16 lbl_1_bss_34;
static s8 lbl_1_bss_33;
static s8 lbl_1_bss_30[3];
static omObjData *lbl_1_bss_2C;
static omObjData *lbl_1_bss_28;
static omObjData *lbl_1_bss_24;
static AnimData *lbl_1_bss_20;
static s8 lbl_1_bss_1C;
static Process *lbl_1_bss_18;

static s16 lbl_1_data_1A8 = -1;
static s8 lbl_1_data_1AA[3] = { -1, -1, -1 };
static s8 lbl_1_data_1AD[3] = { 0, 0, 0 };
static s16 lbl_1_data_1B0 = -1;
static omObjData *lbl_1_data_1B4[3] = { NULL, NULL, NULL };

void fn_1_D70(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 i;

    BoardModelPosGet(lbl_1_bss_C[1], &sp20);
    sp8.x = sp20.x;
    sp8.y = sp20.y + 60.0f;
    sp8.z = sp20.z + -50.0f;
    BoardModelPosSetV(lbl_1_bss_C[4], &sp8);
    for (i = 0; i < 3; i++) {
        lbl_1_bss_3C[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 9), NULL, 0);
        sp14.x = sp20.x + 150.0f * (i - 1.0f);
        sp14.y = sp20.y;
        sp14.z = sp20.z + 100.0f;
        BoardModelPosSetV(lbl_1_bss_3C[i], &sp14);
        BoardModelMotionSpeedSet(lbl_1_bss_3C[i], 0.0f);
        lbl_1_data_1AD[i] = 0;
        lbl_1_bss_36[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 10), NULL, 0);
        BoardModelVisibilitySet(lbl_1_bss_36[i], 0);
        BoardModelHookSet(lbl_1_bss_3C[i], "batu", lbl_1_bss_36[i]);
    }
}

void fn_1_F6C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        BoardModelHookReset(lbl_1_bss_3C[i]);
        if (lbl_1_bss_3C[i] != -1) {
            BoardModelKill(lbl_1_bss_3C[i]);
            lbl_1_bss_3C[i] = -1;
        }
        if (lbl_1_bss_36[i] != -1) {
            BoardModelKill(lbl_1_bss_36[i]);
            lbl_1_bss_36[i] = -1;
        }
    }
}

void fn_1_1054(void) {
    BoardRollDispSet(0);
    lbl_1_bss_18 = HuPrcChildCreate(fn_1_1148, 0x2003, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_18, fn_1_10E4);
    while (lbl_1_bss_18) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

static void fn_1_10E4(void) {
    fn_1_43DC();
    if (lbl_1_data_1A8 != -1) {
        HuWinKill(lbl_1_data_1A8);
        lbl_1_data_1A8 = -1;
    }
    lbl_1_bss_18 = NULL;
}

static void fn_1_1148(void) {
    s32 temp_r3;
    s32 temp_r31;

    temp_r31 = GWSystem.player_curr;
    temp_r3 = fn_1_12A0(temp_r31);
    if (temp_r3 != 0) {
        fn_1_15CC(temp_r31);
    }
    fn_1_1BE0(temp_r31, temp_r3);
    HuPrcEnd();
}

static void fn_1_11B0(void) {
    float sp8[2];
    float var_f31;
    float var_f30;

    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(48, 25));
    var_f31 = -10000.0f;
    var_f30 = 352.0f;
    lbl_1_data_1A8 = HuWinCreate(var_f31, var_f30, sp8[0], sp8[1], 0);
    HuWinBGTPLvlSet(lbl_1_data_1A8, 0.0f);
    HuWinMesSpeedSet(lbl_1_data_1A8, 0);
    HuWinMesSet(lbl_1_data_1A8, MAKE_MESSID(48, 25));
}

static s32 fn_1_12A0(s32 arg0) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s16 var_r30;

    if (BoardPlayerItemCount(arg0) == 3) {
        BoardWinCreate(2, MAKE_MESSID(48, 17), 6);
        BoardWinWait();
        BoardWinKill();
        return 0;
    }
    HuAudFXPlay(0x362);
    fn_1_1D5C(0);
    fn_1_1D5C(2);
    fn_1_1D5C(1);
    fn_1_1CB0(0);
    fn_1_1CB0(1);
    fn_1_1CB0(2);
    lbl_1_bss_30[0] = lbl_1_bss_30[1] = lbl_1_bss_30[2] = 0;
    fn_1_1F08(arg0);
    BoardWinCreateChoice(2, MAKE_MESSID(48, 18), 6, 0);
    if (GWPlayer[arg0].com) {
        BoardComKeySetLeft();
    }
    BoardWinWait();
    if (BoardWinChoiceGet() != 0) {
        BoardWinCreate(2, MAKE_MESSID(48, 19), 6);
        BoardWinWait();
        BoardWinKill();
        fn_1_2048(-1, 1);
        while (fn_1_2174(0) != 0) {
            HuPrcVSleep();
        }
        fn_1_1E30(0);
        fn_1_1E30(2);
        fn_1_1E30(1);
        return 0;
    }
    BoardWinKill();
    BoardAudSeqPause(0, 1, 1000);
    sp14.x = 0.0f;
    sp14.y = 100.0f;
    sp14.z = 0.0f;
    sp8.x = -20.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_C[1], &sp8, &sp14, 1600.0f, -1.0f, 21);
    var_r30 = GWPlayer[arg0].space_curr;
    lbl_1_bss_34 = BoardSpaceLinkFlagSearch(0, var_r30, 0x02000000);
    BoardPlayerPosGet(arg0, &sp2C);
    BoardSpacePosGet(0, lbl_1_bss_34, &sp38);
    PSVECSubtract(&sp38, &sp2C, &sp20);
    PSVECNormalize(&sp20, &sp20);
    BoardPlayerRotYSet(arg0, atan2d(-sp20.x, -sp20.z));
    BoardPlayerPosLerpStart(arg0, &sp2C, &sp38, 20);
    while (GWPlayer[arg0].moving) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(arg0);
    HuPrcSleep(60);
    return 1;
}

static void fn_1_15CC(s32 arg0) {
    s8 sp8[] = { 80, 50 };
    s32 var_r28;
    s16 temp_r26;
    s32 temp_r25;
    s32 var_r30;
    s32 var_r31;

    BoardMusStart(1, 0x26, 0x7F, 0);
    temp_r26 = MGSeqStartCreate();
    while (MGSeqStatGet(temp_r26) != 0) {
        HuPrcVSleep();
    }
    fn_1_2048(-1, 1);
    while (fn_1_2174(0) != 0) {
        HuPrcVSleep();
    }
    fn_1_1E30(0);
    fn_1_1E30(2);
    fn_1_1E30(1);
    fn_1_1CB0(0);
    fn_1_1CB0(1);
    fn_1_1CB0(2);
    lbl_1_bss_30[0] = lbl_1_bss_30[1] = lbl_1_bss_30[2] = 0;
    fn_1_3470();
    fn_1_2B60(arg0);
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        fn_1_4070();
        fn_1_11B0();
        fn_1_2D90(2);
        fn_1_2C18();
        while (fn_1_2DD0() != 3) {
            HuPrcVSleep();
        }
        fn_1_4124();
        HuWinDispOff(lbl_1_data_1A8);
        fn_1_3560(1);
        fn_1_3698(lbl_1_bss_33);
        while (fn_1_35BC() != 0) {
            HuPrcVSleep();
        }
        BoardWinCreate(2, MAKE_MESSID(48, 20), 6);
        BoardWinWait();
        var_r28 = (BoardRandMod(100) >= sp8[var_r30]) ? 1 : 0;
        HuPrcSleep(60);
        if (var_r28 != 0) {
            break;
        }
        BoardWinCreate(2, MAKE_MESSID(48, 21), 6);
        BoardWinWait();
        lbl_1_bss_30[lbl_1_bss_33] = 1;
        BoardModelVisibilitySet(lbl_1_bss_36[lbl_1_bss_33], 1);
        HuAudFXPlay(0xB);
        HuPrcSleep(60);
        if (var_r30 == 0) {
            BoardWinCreate(2, MAKE_MESSID(48, 41), 6);
            BoardWinWait();
            BoardWinKill();
        } else {
            for (var_r31 = 0; var_r31 < 3; var_r31++) {
                if (lbl_1_bss_30[var_r31] == 0) {
                    lbl_1_bss_33 = var_r31;
                    break;
                }
            }
            fn_1_3560(1);
            fn_1_3698(lbl_1_bss_33);
            while (fn_1_35BC() != 0) {
                HuPrcVSleep();
            }
            break;
        }
    }
    fn_1_2D90(4);
    BoardAudSeqFadeOut(1, 1000);
    fn_1_1D5C(lbl_1_bss_33);
    fn_1_42AC(fn_1_21CC(lbl_1_bss_33));
    fn_1_1CB0(lbl_1_bss_33);
    fn_1_20CC(lbl_1_bss_33);
    fn_1_2048(lbl_1_bss_33, 2);
    BoardWinCreate(2, MAKE_MESSID(48, 23), 6);
    BoardWinInsertMesSet(MAKE_MESSID(8, lbl_1_data_1AA[lbl_1_bss_33]), 0);
    BoardWinWait();
    BoardWinKill();
    fn_1_3560(1);
    fn_1_3698(1);
    BoardPlayerMotBlendSet(arg0, 0, 0xF);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    fn_1_2048(lbl_1_bss_33, 3);
    temp_r25 = HuAudSStreamPlay(2);
    BoardPlayerMotionShiftSet(arg0, 7, 0.0f, 8.0f, 0);
    HuPrcSleep(8);
    while (!BoardPlayerMotionEndCheck(arg0)) {
        HuPrcVSleep();
    }
    while (HuAudSStreamStatGet(temp_r25) != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 1000);
    BoardPlayerItemAdd(arg0, lbl_1_data_1AA[lbl_1_bss_33]);
    while (fn_1_35BC() != 0) {
        HuPrcVSleep();
    }
    BoardWinCreate(2, MAKE_MESSID(48, 24), 6);
    BoardWinWait();
    BoardWinKill();
    fn_1_1E30(lbl_1_bss_33);
    fn_1_1CB0(lbl_1_bss_33);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        BoardModelVisibilitySet(lbl_1_bss_36[var_r31], 0);
    }
}

static void fn_1_1BE0(s32 arg0, s32 arg1) {
    Vec sp18;
    Vec spC;
    s16 temp_r30;

    temp_r30 = GWPlayer[arg0].space_curr;
    BoardPlayerPosGet(arg0, &sp18);
    BoardSpacePosGet(0, temp_r30, &spC);
    BoardCameraTargetPlayerSet(arg0);
    BoardCameraViewSet(1);
    if (arg1 != 0) {
        BoardPlayerPosLerpStart(arg0, &sp18, &spC, 40);
        while (GWPlayer[arg0].moving) {
            HuPrcVSleep();
        }
    }
    BoardCameraMotionWait();
    fn_1_2048(-1, 4);
}

static void fn_1_1CB0(s32 arg0) {
    while (!BoardModelMotionEndCheck(lbl_1_bss_3C[arg0])) {
        HuPrcVSleep();
    }
    if (lbl_1_data_1AD[arg0] == 0) {
        BoardModelAttrReset(lbl_1_bss_3C[arg0], 0x40000004);
        BoardModelAttrSet(lbl_1_bss_3C[arg0], 0x40000002);
    }
}

static void fn_1_1D5C(s32 arg0) {
    s8 spC[] = { 0x20, 0x40, 0x60 };
    s16 sp10[] = { -100, 0, 100 };
    s32 sp8;

    if (lbl_1_data_1AD[arg0] == 0) {
        sp8 = HuAudFXPlayVolPan(0x4A4, 0x7F, spC[arg0]);
        BoardModelMotionStart(lbl_1_bss_3C[arg0], 0, 0);
        lbl_1_data_1AD[arg0] = 1;
    }
}

static void fn_1_1E30(s32 arg0) {
    s8 spC[] = { 0x20, 0x40, 0x60 };
    s16 sp10[] = { -100, 0, 100 };
    s32 sp8;

    if (lbl_1_data_1AD[arg0] != 0) {
        sp8 = HuAudFXPlayVolPan(0x4A5, 0x7F, spC[arg0]);
        BoardModelMotionStart(lbl_1_bss_3C[arg0], 0, 0x40000004);
        lbl_1_data_1AD[arg0] = 0;
    }
}

static void fn_1_1F08(s32 arg0) {
    s32 i;
    s32 j;

    i = 0;
    while (i < 3) {
        lbl_1_data_1AA[i] = frandmod(14);
        if (lbl_1_data_1AA[i] != 10 && lbl_1_data_1AA[i] != 13) {
            for (j = 0; j < i; j++) {
                if (lbl_1_data_1AA[i] == lbl_1_data_1AA[j]) {
                    lbl_1_data_1AA[i] = -1;
                }
            }
            if (lbl_1_data_1AA[i] != -1) {
                i++;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        fn_1_2220(arg0, i, lbl_1_data_1AA[i]);
    }
}

static void fn_1_2048(s32 arg0, s32 arg1) {
    Data1B4Work *temp_r30;
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((arg0 == i || arg0 == -1) && lbl_1_data_1B4[i]) {
            temp_r30 = OM_GET_WORK_PTR(lbl_1_data_1B4[i], Data1B4Work);
            temp_r30->unk02 = arg1;
            temp_r30->unk08 = 0;
        }
    }
}

static void fn_1_20CC(s32 arg0) {
    Data1B4Work *temp_r30;
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((arg0 == i || arg0 == -1) && lbl_1_data_1B4[i]) {
            temp_r30 = OM_GET_WORK_PTR(lbl_1_data_1B4[i], Data1B4Work);
            if (temp_r30->unk0C == -1) {
                temp_r30->unk0C = HuAudFXPlay(0x35F);
            }
        }
    }
}

static s32 fn_1_2174(s32 arg0) {
    Data1B4Work *temp_r31;

    if (!lbl_1_data_1B4[arg0]) {
        return -1;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_data_1B4[arg0], Data1B4Work);
    return temp_r31->unk02;
}

static s16 fn_1_21CC(s32 arg0) {
    Data1B4Work *temp_r31;

    if (!lbl_1_data_1B4[arg0]) {
        return -1;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_data_1B4[arg0], Data1B4Work);
    return temp_r31->unk06;
}

static void fn_1_2220(s32 arg0, s32 arg1, s32 arg2) {
    Mtx sp18;
    Vec spC;
    omObjData *temp_r3;
    Data1B4Work *temp_r31;
    s32 var_r28;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_243C);
    lbl_1_data_1B4[arg1] = temp_r3;
    temp_r31 = OM_GET_WORK_PTR(temp_r3, Data1B4Work);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk02 = 2;
    temp_r31->unk03 = 0;
    temp_r31->unk00_field2 = arg1;
    temp_r31->unk08 = 0;
    temp_r31->unk01 = 0;
    temp_r31->unk00_field4 = 0;
    temp_r31->unk00_field3 = 0;
    temp_r31->unk00_field1 = arg0;
    temp_r31->unk0C = -1;
    var_r28 = BoardItemModelGet(arg2);
    temp_r31->unk06 = BoardModelCreate(var_r28, NULL, 0);
    BoardModelMotionSpeedSet(temp_r31->unk06, 0.0f);
    BoardModelPosGet(lbl_1_bss_3C[arg1], &spC);
    temp_r3->trans.x = spC.x;
    temp_r3->trans.y = spC.y;
    temp_r3->trans.z = spC.z;
    temp_r3->rot.x = 0.0f;
    temp_r3->rot.y = 0.0f;
    temp_r3->rot.z = 0.0f;
    if (arg2 == 5) {
        PSMTXTrans(sp18, 0.0f, -50.0f, 0.0f);
        BoardModelMtxSet(temp_r31->unk06, &sp18);
    }
    BoardModelPosSet(temp_r31->unk06, temp_r3->trans.x, temp_r3->trans.y, temp_r3->trans.z);
    BoardModelScaleSet(temp_r31->unk06, 0.1f, 0.1f, 0.1f);
    BoardModelLayerSet(temp_r31->unk06, 2);
}

static void fn_1_243C(omObjData *arg0) {
    Vec sp14;
    Vec sp8;
    Data1B4Work *temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, Data1B4Work);
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        if (temp_r31->unk0C != -1) {
            HuAudFXStop(temp_r31->unk0C);
            temp_r31->unk0C = -1;
        }
        BoardModelKill(temp_r31->unk06);
        lbl_1_data_1B4[temp_r31->unk00_field2] = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r31->unk01 != 0) {
        temp_r31->unk01--;
        return;
    }
    switch (temp_r31->unk02) {
        case 2:
            if (temp_r31->unk00_field3 == 0) {
                BoardModelPosGet(temp_r31->unk06, &sp14);
                if (temp_r31->unk08 == 0) {
                    BoardModelPosGet(lbl_1_bss_3C[temp_r31->unk00_field2], &sp8);
                    sp8.y += 200.0f;
                    arg0->trans.y = (sp8.y - sp14.y) / 30.0f;
                    arg0->rot.z = 0.01f;
                } else {
                    arg0->rot.z += 0.033333335f;
                    if (arg0->rot.z > 1.0f) {
                        arg0->rot.z = 1.0f;
                    }
                    sp14.y += arg0->trans.y;
                }
                BoardModelPosSetV(temp_r31->unk06, &sp14);
                BoardModelScaleSet(temp_r31->unk06, arg0->rot.z, arg0->rot.z, arg0->rot.z);
                temp_r31->unk08++;
                if (temp_r31->unk08 >= 31) {
                    temp_r31->unk00_field3 = 1;
                }
                return;
            }
            fn_1_2048(temp_r31->unk00_field2, 0);
            break;
        case 1:
            if (temp_r31->unk00_field3 != 0) {
                BoardModelPosGet(temp_r31->unk06, &sp14);
                if (temp_r31->unk08 == 0) {
                    HuAudFXPlay(0x30D);
                    BoardModelPosGet(lbl_1_bss_3C[temp_r31->unk00_field2], &sp8);
                    arg0->trans.y = (sp8.y - sp14.y) / 30.0f;
                    arg0->rot.z = 1.0f;
                } else {
                    arg0->rot.z -= 0.033333335f;
                    if (arg0->rot.z < 0.001f) {
                        arg0->rot.z = 0.001f;
                    }
                    sp14.y += arg0->trans.y;
                }
                BoardModelPosSetV(temp_r31->unk06, &sp14);
                BoardModelScaleSet(temp_r31->unk06, arg0->rot.z, arg0->rot.z, arg0->rot.z);
                temp_r31->unk08++;
                if (temp_r31->unk08 >= 31) {
                    if (temp_r31->unk0C != -1) {
                        HuAudFXStop(temp_r31->unk0C);
                        temp_r31->unk0C = -1;
                    }
                    temp_r31->unk00_field3 = 0;
                }
                return;
            }
            fn_1_2048(temp_r31->unk00_field2, 0);
            break;
        case 3:
            BoardModelPosGet(temp_r31->unk06, &sp14);
            if (temp_r31->unk08 == 0) {
                BoardPlayerPosGet(temp_r31->unk00_field1, &sp8);
                arg0->rot.x = (sp8.x - sp14.x) / 30.0f;
                arg0->rot.z = (sp8.z - sp14.z) / 30.0f;
            } else if (temp_r31->unk08 < 30) {
                sp14.x += arg0->rot.x;
                sp14.z += arg0->rot.z;
                BoardModelPosSetV(temp_r31->unk06, &sp14);
            } else {
                BoardPlayerPosGet(temp_r31->unk00_field1, &sp8);
                arg0->trans.x = sp8.x;
                arg0->trans.y = sp8.y;
                arg0->trans.z = sp8.z;
                temp_r31->unk01 = 30;
                temp_r31->unk08 = 0;
                arg0->rot.z = 1.0f;
                fn_1_2048(temp_r31->unk00_field2, 1);
                break;
            }
            temp_r31->unk08++;
            break;
        case 4:
            temp_r31->unk00_field0 = 1;
            break;
        case 0:
            break;
    }
}

static s8 lbl_1_data_1C5[14] = {
    1, 1, 3, 3, 2,
    2, 2, 1, 2, 3,
    0, 4, 5, 0
};

static s32 fn_1_2A1C(s32 arg0) {
    s32 var_r29;
    s32 var_r28;
    s32 var_r30;
    s32 var_r31;

    var_r29 = lbl_1_data_1C5[lbl_1_data_1AA[0]];
    var_r28 = lbl_1_data_1C5[lbl_1_data_1AA[1]];
    var_r30 = lbl_1_data_1C5[lbl_1_data_1AA[2]];
    if (lbl_1_bss_30[0] != 0) {
        var_r29 = 0;
    }
    if (lbl_1_bss_30[1] != 0) {
        var_r28 = 0;
    }
    if (lbl_1_bss_30[2] != 0) {
        var_r30 = 0;
    }
    if (var_r29 > var_r28) {
        if (var_r29 > var_r30) {
            var_r31 = 0;
        } else if (var_r30 > var_r28) {
            var_r31 = 2;
        } else {
            var_r31 = 1;
        }
    } else {
        if (var_r28 > var_r30) {
            var_r31 = 1;
        } else if (var_r30 > var_r29) {
            var_r31 = 2;
        } else {
            var_r31 = 0;
        }
    }
    return var_r31;
}

static void fn_1_2B60(s32 arg0) {
    omObjData *temp_r3;
    Bss24Work *temp_r31;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_2EF4);
    lbl_1_bss_24 = temp_r3;
    temp_r31 = OM_GET_WORK_PTR(temp_r3, Bss24Work);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field2 = 0;
    temp_r31->unk00_field1 = arg0;
    temp_r31->unk01 = 0;
    temp_r31->unk03 = 0;
    temp_r31->unk02 = 1;
}

static void fn_1_2C18(void) {
    Bss24Work *var_r27;

    if (lbl_1_bss_24) {
        var_r27 = OM_GET_WORK_PTR(lbl_1_bss_24, Bss24Work);
        var_r27->unk03 = fn_1_2A1C(var_r27->unk00_field1);
    }
}

static void fn_1_2D90(s32 arg0) {
    Bss24Work *var_r31;

    if (lbl_1_bss_24) {
        var_r31 = OM_GET_WORK_PTR(lbl_1_bss_24, Bss24Work);
        var_r31->unk01 = arg0;
    }
}

static s32 fn_1_2DD0(void) {
    Bss24Work *var_r31;

    if (!lbl_1_bss_24) {
        return 4;
    }
    var_r31 = OM_GET_WORK_PTR(lbl_1_bss_24, Bss24Work);
    return var_r31->unk01;
}

static u32 fn_1_2E18(Bss24Work *arg0) {
    s32 temp_r31;
    s32 var_r30;

    if (GWPlayer[arg0->unk00_field1].com) {
        if (arg0->unk02 == arg0->unk03) {
            return 0x100;
        }
        if (arg0->unk02 > arg0->unk03) {
            return 1;
        }
        return 2;
    }
    temp_r31 = GWPlayer[arg0->unk00_field1].port;
    var_r30 = HuPadDStk[temp_r31] | HuPadBtnDown[temp_r31];
    return var_r30;
}

static void fn_1_2EF4(omObjData *arg0) {
    Vec sp14;
    Vec sp8;
    float var_f30;
    s32 var_r28;
    s32 temp_r19;
    s32 var_r26;
    s32 var_r25;
    u32 var_r29;
    Bss24Work *temp_r30;

    var_r29 = 0;
    temp_r30 = OM_GET_WORK_PTR(arg0, Bss24Work);
    if (temp_r30->unk00_field0 != 0 || BoardIsKill()) {
        lbl_1_bss_24 = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (lbl_1_bss_30[0] != 0) {
        var_r25 = 1;
    } else {
        var_r25 = 0;
    }
    if (lbl_1_bss_30[2] != 0) {
        var_r26 = 1;
    } else {
        var_r26 = 2;
    }
    switch (temp_r30->unk01) {
        case 2:
            var_r29 = fn_1_2E18(temp_r30);
            if (var_r29 == 0x100 || lbl_1_bss_1C != 0) {
                if (lbl_1_bss_30[temp_r30->unk02] == 0) {
                    HuAudFXPlay(2);
                    lbl_1_bss_33 = temp_r30->unk02;
                    fn_1_2D90(3);
                    return;
                }
                if (lbl_1_bss_1C == 0) {
                    HuAudFXPlay(4);
                    break;
                }
                if (temp_r30->unk02 == 1) {
                    if (lbl_1_bss_30[0] == 0 && lbl_1_bss_30[1] == 0) {
                        if (BoardRandMod(100) < 50) {
                            var_r29 = 1;
                        } else {
                            var_r29 = 2;
                        }
                    } else {
                        if (lbl_1_bss_30[0] == 0) {
                            var_r29 = 2;
                        } else if (lbl_1_bss_30[1] == 0) {
                            var_r29 = 1;
                        }
                    }
                }
                if (temp_r30->unk02 == 0) {
                    var_r29 = 2;
                }
                if (temp_r30->unk02 == 2) {
                    var_r29 = 1;
                }
            }
            temp_r19 = temp_r30->unk02;
            var_r28 = 0;
            if (var_r29 & 1) {
                var_r28 = -1;
            }
            if (var_r29 & 2) {
                var_r28 = 1;
            }
            temp_r30->unk02 += var_r28;
            if (temp_r30->unk02 == 1 && lbl_1_bss_30[1] != 0) {
                temp_r30->unk02 += var_r28;
            }
            if (temp_r30->unk02 > var_r26) {
                temp_r30->unk02 = var_r26;
            }
            if (temp_r30->unk02 < var_r25) {
                temp_r30->unk02 = var_r25;
            }
            if (temp_r30->unk02 == temp_r19) {
                break;
            }
            fn_1_2D90(1);
            BoardSpacePosGet(0, lbl_1_bss_34, &sp8);
            BoardPlayerPosGet(temp_r30->unk00_field1, &sp14);
            OSs8tof32(&temp_r30->unk02, &var_f30);
            sp8.x += 150.0f * (var_f30 - 1.0f);
            BoardPlayerPosLerpStart(temp_r30->unk00_field1, &sp14, &sp8, 20);
            break;
        case 0:
            break;
        case 1:
            if (!GWPlayer[temp_r30->unk00_field1].moving) {
                fn_1_2D90(2);
                BoardPlayerRotYSet(temp_r30->unk00_field1, 180.0f);
                BoardPlayerIdleSet(temp_r30->unk00_field1);
            }
            break;
        case 3:
            fn_1_2D90(0);
            break;
        case 4:
            temp_r30->unk00_field0 = 1;
            break;
    }
}

static void fn_1_3470(void) {
    omObjData *temp_r3;
    Bss28Work *temp_r31;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_3974);
    lbl_1_bss_28 = temp_r3;
    temp_r31 = OM_GET_WORK_PTR(temp_r3, Bss28Work);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field1 = 0;
    temp_r31->unk03 = 0;
    temp_r31->unk00_field2 = 0;
    temp_r31->unk04 = 0;
    temp_r31->unk06 = 0;
    temp_r31->unk08 = BoardModelMotionCreate(lbl_1_bss_C[4], DATA_MAKE_NUM(DATADIR_W06, 22));
    temp_r31->unk0A = BoardModelMotionCreate(lbl_1_bss_C[4], DATA_MAKE_NUM(DATADIR_W06, 23));
}

static void fn_1_3560(s32 arg0) {
    Bss28Work *temp_r31;

    if (!lbl_1_bss_28) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_28, Bss28Work);
    temp_r31->unk00_field1 = arg0;
    if (arg0 != 1) {
        (void) 0;
    } else {
        temp_r31->unk06 = 20;
    }
}

static s32 fn_1_35BC(void) {
    Bss28Work *temp_r31;

    if (!lbl_1_bss_28) {
        return 5;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_28, Bss28Work);
    return temp_r31->unk00_field1;
}

static void fn_1_3604(s32 arg0) {
    Bss28Work *temp_r31;

    if (!lbl_1_bss_28) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_28, Bss28Work);
    switch (arg0) {
        case 0:
            temp_r31->unk01[0] = 1;
            temp_r31->unk01[1] = 2;
            break;
        case 2:
            temp_r31->unk01[0] = 1;
            temp_r31->unk01[1] = 0;
            break;
        default:
            temp_r31->unk01[0] = 0;
            temp_r31->unk01[1] = 2;
            break;
    }
}

static void fn_1_3698(s8 arg0) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f31;
    float var_f30;
    Bss28Work *temp_r31;

    if (!lbl_1_bss_28) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_28, Bss28Work);
    BoardModelPosGet(lbl_1_bss_C[4], &sp24);
    BoardModelPosGet(lbl_1_bss_3C[1], &sp18);
    lbl_1_bss_28->trans.x = arg0 - 1;
    sp18.x += 150.0f * lbl_1_bss_28->trans.x;
    sp18.y = sp24.y;
    sp18.z = sp24.z;
    temp_f31 = sp18.x - sp24.x;
    if (ABS(temp_f31) < 1.0f) {
        BoardModelMotionShiftSet(lbl_1_bss_C[4], 1, 0.0f, 8.0f, 0x40000001);
        lbl_1_bss_28->trans.y = 0.0f;
        return;
    }
    if (ABS(temp_f31) >= 300.0f) {
        var_f30 = 40.0f;
        temp_r31->unk06 *= 2;
    } else {
        var_f30 = 20.0f;
    }
    PSVECSubtract(&sp18, &sp24, &spC);
    lbl_1_bss_28->trans.y = temp_f31 / var_f30;
    BoardModelRotYSet(lbl_1_bss_C[4], atan2d(spC.x, spC.z));
    BoardModelMotionShiftSet(lbl_1_bss_C[4], temp_r31->unk08, 0.0f, 8.0f, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_bss_C[4], 2.0f);
}

static void fn_1_3974(omObjData *arg0) {
    Vec sp30;
    Vec sp24;
    s32 sp8;
    Bss28Work *temp_r31;

    sp8 = 0;
    temp_r31 = OM_GET_WORK_PTR(arg0, Bss28Work);
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        lbl_1_bss_28 = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r31->unk04 != 0) {
        temp_r31->unk04--;
        return;
    }
    switch (temp_r31->unk00_field1) {
        case 0:
            break;
        case 3:
            if (temp_r31->unk03 >= 2) {
                if (BoardRandMod(100) < 60) {
                    fn_1_3560(4);
                    return;
                }
            } else {
                temp_r31->unk03++;
            }
            fn_1_3560(1);
            temp_r31->unk00_field2 ^= 1;
            fn_1_3698(temp_r31->unk01[temp_r31->unk00_field2]);
            temp_r31->unk00_field3 = 1;
            break;
        case 1:
            if (temp_r31->unk06 != 0) {
                BoardModelPosGet(lbl_1_bss_C[4], &sp30);
                sp30.x += arg0->trans.y;
                BoardModelPosSetV(lbl_1_bss_C[4], &sp30);
                temp_r31->unk06--;
                break;
            }
            if (temp_r31->unk00_field3 != 0) {
                fn_1_3560(2);
                temp_r31->unk06 = 0;
                temp_r31->unk04 = 10;
                break;
            }
            fn_1_3560(0);
            temp_r31->unk06 = 0;
            BoardModelRotYSet(lbl_1_bss_C[4], 0.0f);
            BoardModelMotionShiftSet(lbl_1_bss_C[4], 1, 0.0f, 10.0f, 0x40000001);
            break;
        case 2:
            if (temp_r31->unk06++ == 0) {
                BoardModelMotionShiftSet(lbl_1_bss_C[4], temp_r31->unk0A, 0.0f, 10.0f, 0x40000001);
                break;
            }
            if (temp_r31->unk06 < 50) {
                BoardModelRotYSet(lbl_1_bss_C[4], 0.0f);
                break;
            }
            fn_1_3560(3);
            break;
        case 4:
            temp_r31->unk00_field3 = 0;
            lbl_1_bss_33 = temp_r31->unk01[temp_r31->unk00_field2];
            BoardModelMotionShiftSet(lbl_1_bss_C[4], 1, 0.0f, 10.0f, 0x40000001);
            fn_1_3560(0);
            break;
        case 5:
            temp_r31->unk00_field0 = 1;
            break;
    }
}

static void fn_1_4070(void) {
    Bss2CWork *temp_r31;

    lbl_1_bss_1C = 0;
    lbl_1_bss_2C = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_4194);
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_2C, Bss2CWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk01 = 5;
    temp_r31->unk02 = 60;
    temp_r31->unk04 = MGSeqTimerCreateXY(temp_r31->unk01, 288, 64);
}

static void fn_1_4124(void) {
    Bss2CWork *temp_r31;

    if (!lbl_1_bss_2C) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_2C, Bss2CWork);
    MGSeqParamSet(temp_r31->unk04, 2, -1);
    temp_r31->unk04 = -1;
    temp_r31->unk00_field0 = 1;
}

static void fn_1_4194(omObjData *arg0) {
    Bss2CWork *temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, Bss2CWork);
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        if (temp_r31->unk04 != -1) {
            MGSeqParamSet(temp_r31->unk04, 2, -1);
        }
        lbl_1_bss_2C = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r31->unk04 == -1) {
        return;
    }
    if (temp_r31->unk02 != 0) {
        temp_r31->unk02--;
        return;
    }
    if (temp_r31->unk01 != 0) {
        temp_r31->unk01--;
    } else {
        MGSeqParamSet(temp_r31->unk04, 2, -1);
        temp_r31->unk04 = -1;
        lbl_1_bss_1C = 1;
        return;
    }
    MGSeqParamSet(temp_r31->unk04, 1, temp_r31->unk01);
    temp_r31->unk02 = 60;
}

static void fn_1_42AC(s16 arg0) {
    ParticleData *var_r31;

    lbl_1_bss_20 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 0));
    HuSprAnimLock(lbl_1_bss_20);
    lbl_1_data_1B0 = Hu3DParticleCreate(lbl_1_bss_20, 100);
    Hu3DParticleHookSet(lbl_1_data_1B0, fn_1_4460);
    Hu3DParticleColSet(lbl_1_data_1B0, 0xFF, 0xFF, 0);
    Hu3DModelPosSet(lbl_1_data_1B0, 0.0f, 0.0f, 0.0f);
    Hu3DParticleBlendModeSet(lbl_1_data_1B0, 1);
    Hu3DModelLayerSet(lbl_1_data_1B0, 2);
    var_r31 = Hu3DData[lbl_1_data_1B0].unk_120;
    var_r31->unk_02 = arg0;
}

static void fn_1_43DC(void) {
    if (lbl_1_data_1B0 != -1) {
        Hu3DModelKill(lbl_1_data_1B0);
        lbl_1_data_1B0 = -1;
    }
    if (lbl_1_bss_20) {
        HuSprAnimKill(lbl_1_bss_20);
        lbl_1_bss_20 = NULL;
    }
}

static void fn_1_4460(ModelData *model, ParticleData *particle, Mtx matrix) {
    HsfanimStruct01 *var_r31;
    Vec sp8;
    float var_f31;
    float temp_f30;
    float temp_f29;
    s32 i;
    s32 j;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
        particle->unk_00 = 0;
    }
    BoardModelScaleGet(particle->unk_02, &sp8);
    var_f31 = sp8.x;
    BoardModelPosGet(particle->unk_02, &sp8);
    for (i = 0; i < 22; i++) {
        var_r31 = particle->unk_48;
        for (j = 0; j < particle->unk_30; j++, var_r31++) {
            if (var_r31->unk2C == 0.0f) {
                break;
            }
        }
        if (j != particle->unk_30) {
            temp_f30 = 0.003921569f * frand8() * 360.0f;
            temp_f29 = var_f31 * (20.0f + 0.003921569f * frand8() * 60.0f);
            var_r31->unk34.x = sp8.x + temp_f29 * sind(temp_f30);
            var_r31->unk34.z = sp8.z + temp_f29 * cosd(temp_f30);
            var_r31->unk34.y = sp8.y + var_f31 * (-30.0f + 0.003921569f * frand8() * 40.0f);
            var_r31->unk08.x = 0.5f + 0.003921569f * frand8() * 3.0f;
            var_r31->unk08.y = 0.3f + 0.003921569f * frand8() * 2.0f;
            var_r31->unk40.a = 0xB4;
            var_r31->unk2C = 15.0f * var_f31;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (var_r31->unk2C != 0.0f) {
            var_r31->unk34.y -= var_r31->unk08.x;
            var_r31->unk2C -= var_r31->unk08.y;
            if (var_r31->unk2C <= 0.0f) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}
