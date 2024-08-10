#include "REL/w04Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/msm.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/board/audio.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/window.h"

static void fn_1_CF8C(omObjData *arg0);
static void fn_1_D0AC(void);
static void fn_1_D0DC(void);
static void fn_1_D174(omObjData *arg0);
static void fn_1_D230(omObjData *arg0);
static void fn_1_D2A4(omObjData *arg0);
static void fn_1_D554(omObjData *arg0);
static void fn_1_D6A8(omObjData *arg0);
static void fn_1_D70C(omObjData *arg0);
static void fn_1_D770(void);
static void fn_1_E004(void);
static void fn_1_E144(omObjData *arg0);
static void fn_1_E18C(omObjData *arg0);
static void fn_1_E374(omObjData *arg0);
static void fn_1_E4C0(omObjData *arg0);
static void fn_1_E6AC(omObjData *arg0);
static s16 fn_1_E880(omObjData *arg0);

static u16 lbl_1_bss_326;
static s16 lbl_1_bss_324;
static omObjData *lbl_1_bss_320;
static omObjData *lbl_1_bss_31C;
static omObjData *lbl_1_bss_318;
static s16 lbl_1_bss_314;
static Vec lbl_1_bss_308;
static Vec lbl_1_bss_2FC;
static s16 lbl_1_bss_2FA;
static s16 lbl_1_bss_2F8;
static s16 lbl_1_bss_2D0[20];
static u16 lbl_1_bss_2C2[7];
static u16 lbl_1_bss_2B4[7];
static s32 lbl_1_bss_2B0;

static s32 lbl_1_data_588 = -1;

static char *lbl_1_data_5BC[] = {
    "pia1", "pia2", "pia3", "pia4",
    "pia5", "pia6", "pia7", "pia8",
    "pia9"
};

static u16 lbl_1_data_5E0[] = {
    0x0100, 0x0200, 0x0040, 0x0020,
    0x0800, 0x0400, 0x0010
};

static s32 lbl_1_data_5F0[] = {
    0x0000046D,
    0x0000046E,
    0x0000046F,
    0x00000470,
    0x00000471,
    0x00000472,
    0x00000473,
    0x00000474
};

void fn_1_C7A0(void) {
    BoardModelAttrSet(lbl_1_bss_14[7], 0x40000002);
}

void fn_1_C7D4(void) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f30;
    float var_f31;
    float var_f29;
    s16 temp_r30;
    s32 i;

    BoardModelLayerSet(lbl_1_bss_14[9], 1);
    lbl_1_bss_324 = GWSystem.player_curr;
    lbl_1_data_588 = -1;
    lbl_1_bss_2FA = 0;
    for (i = 0; i < 7; i++) {
        lbl_1_bss_2B4[i] = 0;
    }
    for (i = 0; i < 7; i++) {
        do {
            temp_r30 = frandmod(7);
        } while (lbl_1_bss_2B4[temp_r30] != 0);
        lbl_1_bss_2B4[temp_r30] = i + 1;
        lbl_1_bss_2C2[temp_r30] = lbl_1_data_5E0[i];
    }
    for (i = 0; i < 7; i++) {
        OSReport("%d: %d  %04X\n", i, lbl_1_bss_2B4[i], lbl_1_bss_2C2[i]);
    }
    lbl_1_bss_2F8 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 16), NULL, 0);
    BoardModelVisibilitySet(lbl_1_bss_2F8, 0);
    BoardModelAttrSet(lbl_1_bss_2F8, 0x40000002);
    for (i = 0; i < 20; i++) {
        lbl_1_bss_2D0[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 1);
        BoardModelVisibilitySet(lbl_1_bss_2D0[i], 0);
    }
    BoardPlayerMotBlendSet(lbl_1_bss_324, 0xB4, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_324)) {
        HuPrcVSleep();
    }
    BoardWinCreate(2, MAKE_MESSID(32, 19), 3);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerPosGet(lbl_1_bss_324, &lbl_1_bss_308);
    BoardModelPosGet(lbl_1_bss_14[9], &lbl_1_bss_2FC);
    BoardPlayerPosGet(lbl_1_bss_324, &sp38);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[7]), lbl_1_data_5BC[0], &sp2C);
    sp20 = sp2C;
    sp20.z = sp38.z;
    sp20.y = sp38.y;
    BoardPlayerPosLerpStart(lbl_1_bss_324, &sp38, &sp20, 0x3C);
    while (fn_1_1130(lbl_1_bss_14[9], 270.0f, 30.0f) == 0) {
        HuPrcVSleep();
    }
    BoardModelPosGet(lbl_1_bss_14[9], &sp8);
    sp14 = sp8;
    sp14.x = sp2C.x;
    VECSubtract(&sp14, &sp8, &sp38);
    VECScale(&sp38, &sp38, 0.022727273f);
    for (i = 0; i < 44; i++) {
        BoardModelPosGet(lbl_1_bss_14[9], &sp8);
        VECAdd(&sp8, &sp38, &sp8);
        BoardModelPosSetV(lbl_1_bss_14[9], &sp8);
        HuPrcVSleep();
    }
    BoardModelPosSetV(lbl_1_bss_14[9], &sp14);
    while (fn_1_1130(lbl_1_bss_14[9], 0.0f, 30.0f) == 0) {
        HuPrcVSleep();
    }
    while (GWPlayer[lbl_1_bss_324].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotBlendSet(lbl_1_bss_324, 0xB4, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_324)) {
        HuPrcVSleep();
    }
    BoardPlayerMotionShiftSet(lbl_1_bss_324, 4, 0.0f, 5.0f, 0);
    var_f31 = 0.0f;
    temp_f30 = 8.0f;
    VECSubtract(&sp2C, &sp20, &sp38);
    VECScale(&sp38, &sp38, 0.05f);
    while (TRUE) {
        BoardPlayerPosGet(lbl_1_bss_324, &sp20);
        sp38.y = temp_f30 - var_f31 * var_f31 * 0.25f * 0.075f;
        var_f31 += 1.0f;
        VECAdd(&sp38, &sp20, &sp20);
        sp14 = sp2C;
        sp14.y = sp20.y;
        VECSubtract(&sp14, &sp20, &sp14);
        var_f29 = VECMag(&sp14);
        if (var_f29 <= 1.0f) {
            sp38.x = sp38.z = 0.0f;
            sp20.x = sp2C.x;
            sp20.z = sp2C.z;
        }
        if (sp20.y <= sp2C.y && sp38.y < 0.0f) {
            sp20.y = sp2C.y;
            break;
        }
        BoardPlayerPosSetV(lbl_1_bss_324, &sp20);
        HuPrcVSleep();
    }
    BoardPlayerPosSetV(lbl_1_bss_324, &sp20);
    BoardPlayerMotBlendSet(lbl_1_bss_324, 0x5A, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_324)) {
        HuPrcVSleep();
    }
    HuPrcSleep(60);
    lbl_1_bss_320 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_CF8C);
    lbl_1_bss_318 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_D174);
    lbl_1_bss_31C = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, NULL);
    lbl_1_bss_318->scale.x = 255.0f;
    lbl_1_bss_314 = 0;
    lbl_1_bss_326 = 0;
}

static void fn_1_CF8C(omObjData *arg0) {
    s32 spC;

    if (lbl_1_data_588 != -1) {
        spC = HuAudSeqMidiCtrlGet(lbl_1_data_588, 0, 1);
        if (msmMusGetStatus(lbl_1_data_588) == 0) {
            HuAudSeqFadeOut(lbl_1_data_588, 100);
            lbl_1_bss_2FA = 1;
        }
        if (lbl_1_bss_2FA == 1 && msmMusGetStatus(lbl_1_data_588) == 0) {
            lbl_1_data_588 = -1;
            BoardAudSeqPause(0, 0, 1000);
            OSReport("BGM1 Restore\n");
        }
    }
    if (lbl_1_bss_326 != 0 && BoardMGDoneFlagGet() == 1) {
        fn_1_D0DC();
        omDelObjEx(boardObjMan, arg0);
    }
}

static void fn_1_D0AC(void) {
    lbl_1_bss_326 = 1;
    BoardMGExit();
}

static void fn_1_D0DC(void) {
    s32 i;

    omDelObjEx(boardObjMan, lbl_1_bss_31C);
    BoardModelKill(lbl_1_bss_2F8);
    for (i = 0; i < 20; i++) {
        BoardModelKill(lbl_1_bss_2D0[i]);
    }
    BoardModelLayerSet(lbl_1_bss_14[9], 0);
    BoardMGDoneFlagSet(0);
}

static void fn_1_D174(omObjData *arg0) {
    UnkMsmStruct_03 sp8;

    if (arg0->work[0] == 0) {
        arg0->work[0] = MGSeqCreate(3, 0);
        BoardAudSeqPause(0, 1, 1000);
        return;
    }
    if (MGSeqStatGet(arg0->work[0]) == 0) {
        sp8.unk00 = 1;
        sp8.unk06 = 0;
        sp8.unk05 = 0x7F;
        sp8.unk04 = 1;
        lbl_1_data_588 = msmMusPlay(0x1D, &sp8);
        arg0->func = fn_1_D230;
    }
}

static void fn_1_D230(omObjData *arg0) {
    s32 temp_r3;

    temp_r3 = HuAudSeqMidiCtrlGet(lbl_1_data_588, 0, 1);
    if (temp_r3 >= 10 && temp_r3 <= 19) {
        arg0->work[1]++;
        arg0->func = fn_1_D2A4;
    }
}

static void fn_1_D2A4(omObjData *arg0) {
    Vec sp18;
    Vec spC;
    float sp8;
    ModelData *temp_r30;
    s32 temp_r3;

    temp_r30 = &Hu3DData[BoardModelIDGet(lbl_1_bss_2F8)];
    sp8 = BoardModelRotYGet(lbl_1_bss_14[9]);
    BoardModelPosGet(lbl_1_bss_14[9], &spC);
    if (arg0->scale.x != 0.0f) {
        arg0->scale.x -= 8.5f;
        if (arg0->scale.x < 0.0f) {
            arg0->scale.x = 0.0f;
        }
        BoardModelAlphaSet(lbl_1_bss_14[9], arg0->scale.x);
        return;
    }
    temp_r3 = HuAudSeqMidiCtrlGet(lbl_1_data_588, 0, 1);
    if (temp_r3 >= 20 && temp_r3 <= 29) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[7]), lbl_1_data_5BC[arg0->work[1]], &sp18);
        spC.x = sp18.x;
        BoardModelPosSetV(lbl_1_bss_14[9], &spC);
        arg0->func = fn_1_D554;
        if (arg0->work[1] < 8) {
            BoardModelHookReset(lbl_1_bss_14[7]);
            BoardModelVisibilitySet(lbl_1_bss_2F8, 1);
            BoardModelMotionTimeSet(lbl_1_bss_2F8, lbl_1_bss_2B4[arg0->work[1] - 1]);
            BoardModelHookSet(lbl_1_bss_14[7], lbl_1_data_5BC[arg0->work[1]], lbl_1_bss_2F8);
            Hu3DMotionExec(BoardModelIDGet(lbl_1_bss_2F8), temp_r30->unk_08, temp_r30->unk_64, 0);
        }
        lbl_1_bss_31C->work[0] = 60;
        lbl_1_bss_31C->unk10 = frandmod(40) + 10;
        lbl_1_bss_31C->work[1] = arg0->work[1];
        lbl_1_bss_31C->func = fn_1_E18C;
    }
}

static void fn_1_D554(omObjData *arg0) {
    float sp8;

    sp8 = BoardModelRotYGet(lbl_1_bss_14[9]);
    arg0->scale.x += 8.5f;
    if (arg0->scale.x > 255.0f) {
        arg0->scale.x = 255.0f;
    }
    BoardModelAlphaSet(lbl_1_bss_14[9], arg0->scale.x);
    if (arg0->scale.x == 255.0f) {
        arg0->work[0] = 0;
        lbl_1_bss_31C->work[1] = arg0->work[1];
        arg0->scale.x = 255.0f;
        BoardModelAlphaSet(lbl_1_bss_14[9], arg0->scale.x);
        if (arg0->work[1] == 8) {
            arg0->func = fn_1_D70C;
            lbl_1_bss_31C->work[2] = 1;
            lbl_1_bss_31C->func = fn_1_E374;
        } else {
            arg0->func = fn_1_D6A8;
        }
    }
}

static void fn_1_D6A8(omObjData *arg0) {
    if (arg0->work[0] != 0) {
        BoardModelHookReset(lbl_1_bss_14[7]);
        BoardModelVisibilitySet(lbl_1_bss_2F8, 0);
        arg0->func = fn_1_D230;
    }
}

static void fn_1_D70C(omObjData *arg0) {
    Process *var_r30;

    if (arg0->work[0] == 1) {
        var_r30 = HuPrcCreate(fn_1_D770, 0x2004, 0x1800, 0);
        var_r30->user_data = arg0;
        arg0->func = NULL;
    }
}

s16 lbl_1_data_62C[] = {
     1, 3, 5, 7, 10, 14, 18, 20
};

static void fn_1_D770(void) {
    Vec sp114[20];
    Vec sp24[20];
    Vec sp18;
    Vec spC;
    float temp_f29;
    float var_f30;
    float var_f31;
    char sp8[4];
    Process *temp_r3;
    omObjData *var_r28;
    s32 var_r29;
    s32 i;

    lbl_1_bss_314 = lbl_1_data_62C[lbl_1_bss_314 - 1];
    sprintf(sp8, "%d", lbl_1_bss_314);
    BoardWinCreate(2, MAKE_MESSID(32, 20), 3);
    BoardWinInsertMesSet(MAKE_MESSID_PTR(sp8), 0);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerMotBlendSet(lbl_1_bss_324, 0, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_324)) {
        HuPrcVSleep();
    }
    BoardPlayerPosGet(lbl_1_bss_324, &sp18);
    for (i = 0; i < lbl_1_bss_314; i++) {
        BoardModelVisibilitySet(lbl_1_bss_2D0[i], 1);
        sp114[i] = sp18;
        sp114[i].y += 800.0f + i * 120;
        sp114[i].x += -25.0f + 50.0f * frand8() * 0.003921569f;
        sp114[i].z += -25.0f + 50.0f * frand8() * 0.003921569f;
        sp24[i].x = sp24[i].z = 0.0f;
        sp24[i].y = 360.0f * frand8() * 0.003921569f;
        BoardModelPosSetV(lbl_1_bss_2D0[i], &sp114[i]);
        BoardModelRotSetV(lbl_1_bss_2D0[i], &sp24[i]);
    }
    var_f31 = -1.0f;
    var_r29 = 0;
    while (TRUE) {
        for (i = 0; i < lbl_1_bss_314; i++) {
            if (i < var_r29) {
                continue;
            }
            sp114[i].y += var_f31;
            BoardModelPosSetV(lbl_1_bss_2D0[i], &sp114[i]);
            sp24[i].y += 45.0f;
            if (sp24[i].y >= 360.0f) {
                sp24[i].y -= 360.0f;
            }
            BoardModelRotSetV(lbl_1_bss_2D0[i], &sp24[i]);
            if (sp114[i].y <= sp18.y + 80.0f) {
                spC = sp114[i];
                CharModelCoinEffectCreate(1, &spC);
                BoardModelVisibilitySet(lbl_1_bss_2D0[i], 0);
                var_r29 += 1;
                BoardPlayerCoinsAdd(lbl_1_bss_324, 1);
                HuAudFXPlay(7);
                omVibrate(lbl_1_bss_324, 12, 6, 6);
            }
        }
        var_f31 *= 1.05f;
        if (var_f31 < -20.0f) {
            var_f31 = -20.0f;
        }
        if (var_r29 == lbl_1_bss_314) {
            BoardPlayerMotionShiftSet(lbl_1_bss_324, 7, 0.0f, 10.0f, 0);
            break;
        }
        HuPrcVSleep();
    }
    while (!BoardPlayerMotionEndCheck(lbl_1_bss_324)) {
        HuPrcVSleep();
    }
    BoardWinCreate(2, MAKE_MESSID(32, 21), 3);
    BoardWinWait();
    BoardWinKill();
    temp_r3 = HuPrcCreate(fn_1_E004, 0x2004, 0x1000, 0);
    temp_r3->user_data = NULL;
    BoardPlayerMotionShiftSet(lbl_1_bss_324, 4, 0.0f, 5.0f, 0);
    var_f30 = 0.0f;
    temp_f29 = 8.0f;
    lbl_1_bss_308.z = sp18.z + 100.0f;
    lbl_1_bss_308.x = sp18.x + 50.0f;
    VECSubtract(&lbl_1_bss_308, &sp18, &spC);
    VECScale(&spC, &spC, 0.04f);
    while (TRUE) {
        BoardPlayerPosGet(lbl_1_bss_324, &sp18);
        spC.y = temp_f29 - var_f30 * var_f30 * 0.25f * 0.075f;
        var_f30 += 1.0f;
        VECAdd(&spC, &sp18, &sp18);
        sp114[0] = lbl_1_bss_308;
        sp114[0].y = sp18.y;
        VECSubtract(&sp114[0], &sp18, &sp114[0]);
        var_f31 = VECMag(&sp114[0]);
        if (var_f31 <= 1.0f) {
            spC.x = spC.z = 0.0f;
            sp18.x = lbl_1_bss_308.x;
            sp18.z = lbl_1_bss_308.z;
        }
        if (sp18.y <= lbl_1_bss_308.y && spC.y < 0.0f) {
            sp18.y = lbl_1_bss_308.y;
            break;
        }
        BoardPlayerPosSetV(lbl_1_bss_324, &sp18);
        HuPrcVSleep();
    }
    BoardPlayerPosSetV(lbl_1_bss_324, &sp18);
    omVibrate(lbl_1_bss_324, 12, 6, 6);
    while (!temp_r3->user_data) {
        HuPrcVSleep();
    }
    HuPrcKill(temp_r3);
    var_r28 = HuPrcCurrentGet()->user_data;
    var_r28->func = fn_1_E144;
    HuPrcEnd();
}

static void fn_1_E004(void) {
    Vec sp14;
    Vec sp8;
    s32 i;

    while (fn_1_1130(lbl_1_bss_14[9], 90.0f, 30.0f) == 0) {
        HuPrcVSleep();
    }
    BoardModelPosGet(lbl_1_bss_14[9], &sp14);
    VECSubtract(&lbl_1_bss_2FC, &sp14, &sp8);
    VECScale(&sp8, &sp8, 0.1f);
    for (i = 0; i < 10; i++) {
        BoardModelPosGet(lbl_1_bss_14[9], &sp14);
        VECAdd(&sp14, &sp8, &sp14);
        BoardModelPosSetV(lbl_1_bss_14[9], &sp14);
        HuPrcVSleep();
    }
    BoardModelPosSetV(lbl_1_bss_14[9], &lbl_1_bss_2FC);
    while (fn_1_1130(lbl_1_bss_14[9], 0.0f, 30.0f) == 0) {
        HuPrcVSleep();
    }
    HuPrcCurrentGet()->user_data = (void*) 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void fn_1_E144(omObjData *arg0) {
    lbl_1_bss_326 = 1;
    BoardMGExit();
    omDelObjEx(boardObjMan, arg0);
}

static void fn_1_E18C(omObjData *arg0) {
    s32 var_r29;
    s16 var_r28;
    s16 var_r30;

    var_r29 = HuAudSeqMidiCtrlGet(lbl_1_data_588, 0, 1);
    if (var_r29 >= 20 && var_r29 <= 29) {
        var_r28 = GWPlayer[lbl_1_bss_324].port;
        var_r30 = 0;
        if (GWPlayer[lbl_1_bss_324].com) {
            if (--arg0->unk10 == 0) {
                var_r30 = fn_1_E880(arg0);
            }
        } else {
            var_r30 = HuPadBtnDown[var_r28];
        }
        if (var_r30 & 0xF70) {
            if ((var_r30 & lbl_1_bss_2C2[arg0->work[1] - 1]) && !(var_r30 & ~lbl_1_bss_2C2[arg0->work[1] - 1])) {
                arg0->work[2] = 1;
            } else {
                arg0->work[2] = 0;
            }
            BoardModelVisibilitySet(lbl_1_bss_2F8, 0);
            arg0->func = fn_1_E374;
        }
    } else {
        BoardModelVisibilitySet(lbl_1_bss_2F8, 0);
        arg0->work[2] = 0;
        arg0->func = fn_1_E374;
        lbl_1_bss_318->work[0] = 1;
        fn_1_E374(arg0);
    }
}

static void fn_1_E374(omObjData *arg0) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 temp_r3;

    temp_r3 = HuAudSeqMidiCtrlGet(lbl_1_data_588, 0, 1);
    if (temp_r3 >= 30 && temp_r3 <= 39) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[7]), lbl_1_data_5BC[arg0->work[1]], &sp14);
        BoardPlayerPosGet(lbl_1_bss_324, &sp20);
        VECSubtract(&sp14, &sp20, &sp8);
        VECScale(&sp8, &sp8, 0.04f);
        arg0->trans.x = sp8.x;
        arg0->trans.z = sp8.z;
        arg0->trans.y = 5.0f;
        arg0->rot.x = 0.0f;
        arg0->scale.x = sp14.x;
        arg0->scale.y = sp14.y;
        arg0->scale.z = sp14.z;
        BoardPlayerMotionShiftSet(lbl_1_bss_324, 4, 0.0f, 5.0f, 0);
        arg0->func = fn_1_E4C0;
    }
}

static void fn_1_E4C0(omObjData *arg0) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;

    BoardPlayerPosGet(lbl_1_bss_324, &sp2C);
    sp14.x = arg0->scale.x;
    sp14.y = arg0->scale.y;
    sp14.z = arg0->scale.z;
    sp20.x = arg0->trans.x;
    sp20.z = arg0->trans.z;
    sp20.y = arg0->trans.y - arg0->rot.x * arg0->rot.x * 0.25f * 0.075f;
    arg0->rot.x += 1.0f;
    VECAdd(&sp2C, &sp20, &sp2C);
    sp8 = sp2C;
    sp8.y = sp14.y;
    VECSubtract(&sp14, &sp8, &sp8);
    var_f31 = VECMag(&sp8);
    if (var_f31 <= 1.0f) {
        arg0->trans.x = arg0->trans.z = 0.0f;
        sp2C.x = sp14.x;
        sp2C.z = sp14.z;
    }
    if (sp2C.y <= sp14.y && sp20.y < 0.0f) {
        sp2C.y = sp14.y;
        BoardPlayerIdleSet(lbl_1_bss_324);
        arg0->work[3] = 0;
        if (arg0->work[2] != 0) {
            arg0->func = fn_1_E6AC;
        } else {
            lbl_1_bss_318->work[0] = 1;
            HuAudFXPlay(0x475);
            arg0->func = NULL;
        }
    }
    BoardPlayerPosSetV(lbl_1_bss_324, &sp2C);
}

static void fn_1_E6AC(omObjData *arg0) {
    Vec sp8;
    float var_f31;

    if (arg0->work[3] == 0) {
        lbl_1_bss_2B0 = -1;
        var_f31 = 4.0f + 20.0f * (arg0->work[1] - 1);
        BoardModelMotionTimeSet(lbl_1_bss_14[7], var_f31);
        BoardModelAttrReset(lbl_1_bss_14[7], 0x40000002);
        lbl_1_bss_314++;
        arg0->work[3] = 1;
        arg0->work[0] = 0x10;
        lbl_1_bss_2B0 = HuAudFXPlay(lbl_1_data_5F0[arg0->work[1] - 1]);
    }
    if (--arg0->work[0] != 0) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[7]), lbl_1_data_5BC[arg0->work[1]], &sp8);
        BoardPlayerPosSetV(lbl_1_bss_324, &sp8);
        return;
    }
    if (lbl_1_bss_2B0 >= 0) {
        HuAudFXStop(lbl_1_bss_2B0);
    }
    lbl_1_bss_318->work[0] = 1;
    BoardModelAttrSet(lbl_1_bss_14[7], 0x40000002);
    arg0->func = NULL;
}

static s16 fn_1_E880(omObjData *arg0) {
    s16 temp_r28;
    s16 var_r30;
    s32 temp_r29;

    temp_r28 = GWPlayer[lbl_1_bss_324].diff;
    var_r30 = 0;
    temp_r29 = frandmod(100);
    switch (temp_r28) {
        case 0:
            if (temp_r29 < 35) {
                var_r30 = lbl_1_bss_2C2[arg0->work[1] - 1];
            } else if (temp_r29 < 90) {
                var_r30 = -1;
            } else {
                arg0->unk10 = 100;
            }
            break;
        case 1:
            if (temp_r29 < 55) {
                var_r30 = lbl_1_bss_2C2[arg0->work[1] - 1];
            } else if (temp_r29 < 90) {
                var_r30 = -1;
            } else {
                arg0->unk10 = 100;
            }
            break;
        case 2:
            if (temp_r29 < 85) {
                var_r30 = lbl_1_bss_2C2[arg0->work[1] - 1];
            } else {
                var_r30 = -1;
            }
            break;
        case 3:
            var_r30 = lbl_1_bss_2C2[arg0->work[1] - 1];
            break;
    }
    return var_r30;
}
