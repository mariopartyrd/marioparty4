#include "REL/w01Dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/frand.h"

#include "game/window.h"
#include "game/board/audio.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/ui.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "ext_math.h"

static void fn_1_E100(void);
static void fn_1_E154(void);
static void fn_1_E2B8(omObjData *arg0);
static void fn_1_E44C(omObjData *arg0);
static void fn_1_E914(omObjData *arg0);
static void fn_1_ECD4(omObjData *arg0);
static void fn_1_EEA0(omObjData *arg0, u16 *arg1);
static void fn_1_EED8(omObjData *arg0);
static void fn_1_F09C(omObjData *arg0);
static void fn_1_F348(omObjData *arg0);
static void fn_1_F3F8(omObjData *arg0);
static void fn_1_F6E8(omObjData *arg0);
static void fn_1_F890(omObjData *arg0);
static void fn_1_FA1C(omObjData *arg0);
static void fn_1_FABC(omObjData *arg0);
static void fn_1_FB58(void);
static void fn_1_FC3C(omObjData *arg0);
static void fn_1_FCEC(void);
static void fn_1_FD3C(omObjData *arg0);
static void fn_1_FE44(omObjData *arg0);
static void fn_1_FED0(omObjData *arg0);
static s16 fn_1_1001C(u32 arg0);
static void fn_1_101B8(s16 arg0);
static void fn_1_10664(omObjData *arg0);
static void fn_1_10820(omObjData *arg0);
static void fn_1_10AE8(omObjData *arg0);
static float fn_1_10BB0(u32 arg0);
static void fn_1_10CF0(u32 arg0);
static float fn_1_10EB8(Vec *arg0);
static void fn_1_11064(ModelData *model, ParticleData *particle, Mtx matrix);
static void fn_1_11484(ModelData *model, ParticleData *particle, Mtx matrix);

static void *lbl_1_bss_818;
static Vec lbl_1_bss_80C;
static omObjData *lbl_1_bss_7FC[4];
static omObjData *lbl_1_bss_7F8;
static omObjData *lbl_1_bss_7F4;
static omObjData *lbl_1_bss_7F0;
static float lbl_1_bss_7EC;
static float lbl_1_bss_7E8;
static s32 lbl_1_bss_7E4;
static Vec lbl_1_bss_7D8;
static s16 lbl_1_bss_7D6;
static s16 lbl_1_bss_7D4;
static s16 lbl_1_bss_7D2;
static s16 lbl_1_bss_7D0;
static Vec lbl_1_bss_7C4;
static s32 lbl_1_bss_7C0_pad;
static s32 lbl_1_bss_7BC;
static s32 lbl_1_bss_7B8;
static s16 lbl_1_bss_7B4;
static s32 lbl_1_bss_7B0_pad;
static s32 lbl_1_bss_7AC;
static s16 lbl_1_bss_7AA;
static s16 lbl_1_bss_7A8;
static s32 lbl_1_bss_7A4;
static AnimData *lbl_1_bss_7A0;

static s32 lbl_1_data_F08[] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 109),
    DATA_MAKE_NUM(DATADIR_BOARD, 110),
    DATA_MAKE_NUM(DATADIR_BOARD, 111),
    DATA_MAKE_NUM(DATADIR_BOARD, 112),
    DATA_MAKE_NUM(DATADIR_BOARD, 113),
    DATA_MAKE_NUM(DATADIR_BOARD, 114),
    DATA_MAKE_NUM(DATADIR_BOARD, 115),
    DATA_MAKE_NUM(DATADIR_BOARD, 116),
    DATA_MAKE_NUM(DATADIR_BOARD, 118),
    DATA_MAKE_NUM(DATADIR_BOARD, 119),
    DATA_MAKE_NUM(DATADIR_BOARD, 120),
    DATA_MAKE_NUM(DATADIR_BOARD, 121),
    DATA_MAKE_NUM(DATADIR_BOARD, 122),
    DATA_MAKE_NUM(DATADIR_BOARD, 123)
};

static s32 lbl_1_data_F40[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 23),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 23),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 23),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 23),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 23),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 23),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 23),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 23)
};

static s32 lbl_1_data_F60[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 64),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 64),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 64),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 64),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 64),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 64),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 64),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 64)
};

void fn_1_D740(s16 *arg0) {
    s16 sp10[14];
    s16 sp8[4];
    float temp_f30;
    float temp_f29;
    float var_f31;
    s32 var_r28;
    s32 var_r30;
    s32 i;
    s32 j;

    lbl_1_bss_818 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_W01, 28), MEMORY_DEFAULT_NUM, HEAP_DATA);
    BoardModelPosGet(lbl_1_bss_6C4[16], &lbl_1_bss_80C);
    sp8[0] = BoardModelIDGet(lbl_1_bss_6C4[19]);
    BoardModelVisibilitySet(lbl_1_bss_6C4[19], 1);
    for (i = 1; i < 4; i++) {
        sp8[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_W01, 24));
    }
    var_r30 = 0;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_7FC[i] = omAddObjEx(boardObjMan, 0x165, 2, 0, -1, NULL);
        if (arg0[i] != -1) {
            lbl_1_bss_7FC[var_r30++]->work[1] = arg0[i];
        }
    }
    while (var_r30 != 4) {
        var_r28 = 0;
        for (i = 0; i < 14; i++) {
            for (j = 0; j < var_r30; j++) {
                if (i == lbl_1_bss_7FC[j]->work[1]) {
                    break;
                }
            }
            if (j == var_r30) {
                sp10[var_r28++] = i;
            }
        }
        lbl_1_bss_7FC[var_r30++]->work[1] = sp10[rand8() % var_r28];
    }
    temp_f30 = BoardModelMotionTimeGet(lbl_1_bss_6C4[18]);
    temp_f29 = BoardModelMotionMaxTimeGet(lbl_1_bss_6C4[18]);
    for (i = 0; i < 4; i++) {
        lbl_1_bss_7FC[i]->model[0] = sp8[i];
        lbl_1_bss_7FC[i]->model[1] = Hu3DModelCreateFile(lbl_1_data_F08[lbl_1_bss_7FC[i]->work[1]]);
        if (lbl_1_bss_7FC[i]->work[1] == 5) {
            Hu3DData[lbl_1_bss_7FC[i]->model[1]].unk_F0[1][3] = -50.0f;
        }
        if (lbl_1_bss_7FC[i]->work[1] == 11) {
            Hu3DModelAttrSet(lbl_1_bss_7FC[i]->model[1], 0x40000001);
        }
        if (lbl_1_bss_7FC[i]->work[1] == 4) {
            Hu3DMotionSpeedSet(lbl_1_bss_7FC[i]->model[1], 0.0f);
        }
        Hu3DModelAttrReset(sp8[i], 1);
        Hu3DModelAttrSet(lbl_1_bss_7FC[i]->model[1], 1);
        Hu3DModelAttrSet(lbl_1_bss_7FC[i]->model[1], 0x40000002);
        omSetTra(lbl_1_bss_7FC[i], lbl_1_bss_80C.x, lbl_1_bss_80C.y + 66.0f, lbl_1_bss_80C.z);
        var_f31 = 90.0f - 90.0f * i + 360.0f * (temp_f30 / temp_f29);
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        if (var_f31 < 0.0f) {
            var_f31 += 360.0f;
        }
        omSetRot(lbl_1_bss_7FC[i], 0.0f, var_f31, 0.0f);
        lbl_1_bss_7FC[i]->work[0] = Hu3DAnimCreate(lbl_1_bss_818, lbl_1_bss_7FC[i]->model[0], "item01");
        Hu3DAnimAttrSet(lbl_1_bss_7FC[i]->work[0], 1);
        lbl_1_bss_7FC[i]->work[2] = i;
    }
    for (i = 0; i < 4; i++) {
        Hu3DAnmNoSet(lbl_1_bss_7FC[i]->work[0], lbl_1_bss_7FC[i]->work[1]);
    }
}

void fn_1_DD84(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i != 0) {
            Hu3DModelKill(lbl_1_bss_7FC[i]->model[0]);
        } else {
            BoardModelVisibilitySet(lbl_1_bss_6C4[19], 0);
            Hu3DAnimKill(lbl_1_bss_7FC[i]->work[0]);
        }
        Hu3DModelKill(lbl_1_bss_7FC[i]->model[1]);
        omDelObjEx(boardObjMan, lbl_1_bss_7FC[i]);
    }
    if (lbl_1_bss_7A0) {
        HuSprAnimKill(lbl_1_bss_7A0);
        lbl_1_bss_7A0 = NULL;
    }
}

void fn_1_DE94(void) {
    s32 i;

    BoardModelPosGet(lbl_1_bss_6C4[16], &lbl_1_bss_80C);
    for (i = 0; i < 4; i++) {
        lbl_1_bss_7FC[i]->func = fn_1_FED0;
    }
    lbl_1_bss_7F4 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_E2B8);
    lbl_1_bss_7F8 = omAddObjEx(boardObjMan, 0x133, 0, 0, -1, fn_1_E44C);
    lbl_1_bss_7F8->work[3] = rand8() % 200 + 10;
    lbl_1_bss_7E4 = GWSystem.player_curr;
    BoardPlayerPosGet(lbl_1_bss_7E4, &lbl_1_bss_7C4);
    lbl_1_bss_7EC = 1.0f;
    lbl_1_bss_7E8 = 1.0f;
    lbl_1_bss_7AA = 0;
    lbl_1_bss_7BC = BoardPlayerMotionCreate(lbl_1_bss_7E4, lbl_1_data_F40[GWPlayer[lbl_1_bss_7E4].character]);
    lbl_1_bss_7B8 = BoardPlayerMotionCreate(lbl_1_bss_7E4, lbl_1_data_F60[GWPlayer[lbl_1_bss_7E4].character]);
    lbl_1_bss_7A0 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 0));
    HuSprAnimLock(lbl_1_bss_7A0);
    lbl_1_bss_7B4 = 0;
}

static void fn_1_E100(void) {
    lbl_1_bss_7AA = 1;
    BoardMGExit();
    HuAudFXPlay(0x40F);
    BoardModelMotionStart(lbl_1_bss_6C4[21], 0, 0x40000004);
}

static void fn_1_E154(void) {
    fn_1_DD84();
    BoardPlayerMotionKill(lbl_1_bss_7E4, lbl_1_bss_7BC);
    BoardPlayerMotionKill(lbl_1_bss_7E4, lbl_1_bss_7B8);
    BoardModelVisibilitySet(lbl_1_bss_6C4[20], 0);
    BoardMGDoneFlagSet(0);
}

static void fn_1_E2B8(omObjData *arg0) {
    if (lbl_1_bss_7AA == 1 && BoardMGDoneFlagGet() == 1) {
        fn_1_E154();
        omDelObjEx(HuPrcCurrentGet(), arg0);
    }
}

static char *lbl_1_data_F9C[] = {
    "uma1", "uma2", "uma3", "uma4"
};

static void fn_1_E44C(omObjData *arg0) {
    Vec sp18;
    Vec spC;
    float temp_f27;
    float var_f29;
    float temp_f28;
    float var_f26;
    float var_f24;
    s32 i;

    temp_f28 = BoardModelMotionMaxTimeGet(lbl_1_bss_6C4[17]);
    var_f29 = BoardModelMotionTimeGet(lbl_1_bss_6C4[17]);
    if (var_f29 >= temp_f28) {
        var_f29 -= temp_f28;
    }
    var_f24 = fmod(var_f29, temp_f28 / 4);
    if (var_f24 >= temp_f28 / 4 - 30.0f && lbl_1_bss_7B4 == 0) {
        lbl_1_bss_7B4 = 1;
        lbl_1_bss_7A8 = 90;
    }
    if (lbl_1_bss_7B4 != 0) {
        lbl_1_bss_7EC *= 0.97f;
        lbl_1_bss_7A8--;
    }
    if (lbl_1_bss_7EC != 1.0f && lbl_1_bss_7A8 == 0) {
        lbl_1_bss_7EC = 0.0f;
        BoardAudSeqPause(0, 1, 1000);
        BoardPlayerPosGet(lbl_1_bss_7E4, &sp18);
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_6C4[17]), lbl_1_data_F9C[0], &spC);
        var_f26 = VECSquareDistance(&sp18, &spC);
        arg0->work[2] = 0;
        for (i = 1; i < 4; i++) {
            Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_6C4[17]), lbl_1_data_F9C[i], &spC);
            temp_f27 = VECSquareDistance(&sp18, &spC);
            if (temp_f27 < var_f26) {
                var_f26 = temp_f27;
                arg0->work[2] = i;
            }
        }
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_6C4[17]), lbl_1_data_F9C[arg0->work[2]], &lbl_1_bss_7D8);
        VECSubtract(&lbl_1_bss_7D8, &sp18, &spC);
        VECNormalize(&spC, &spC);
        arg0->trans.x = spC.x;
        arg0->trans.y = spC.y;
        arg0->trans.z = spC.z;
        arg0->rot.x = VECDistanceXZ(&lbl_1_bss_7D8, &sp18);
        arg0->rot.y = 10.0f;
        arg0->rot.z = sp18.y;
        arg0->scale.x = 0.0f;
        BoardPlayerMotionShiftSet(lbl_1_bss_7E4, 4, 0.0f, 5.0f, 0);
        arg0->func = fn_1_E914;
    }
    BoardModelMotionSpeedSet(lbl_1_bss_6C4[17], lbl_1_bss_7EC);
}

static void fn_1_E914(omObjData *arg0) {
    Vec spC;
    s32 i;

    BoardPlayerPosGet(lbl_1_bss_7E4, &spC);
    spC.x += arg0->trans.x * arg0->rot.x / 32.760002f;
    spC.z += arg0->trans.z * arg0->rot.x / 32.760002f;
    spC.y += arg0->rot.y - 0.016666668f * arg0->scale.x * arg0->scale.x;
    arg0->scale.x += 1.0f;
    if (VECDistanceXZ(&lbl_1_bss_7D8, &spC) < 2.0f) {
        spC = lbl_1_bss_7D8;
        BoardPlayerRotSet(lbl_1_bss_7E4, 0.0f, fn_1_10BB0(arg0->work[2]), 0.0f);
        lbl_1_bss_7EC = 0.05f;
        lbl_1_bss_7E8 = 0.05f;
        BoardModelAttrReset(lbl_1_bss_6C4[18], 0x40000002);
        BoardModelAttrSet(lbl_1_bss_6C4[18], 0x40000001);
        BoardModelMotionSpeedSet(lbl_1_bss_6C4[18], 0.0f);
        for (i = 0; i < 4; i++) {
            lbl_1_bss_7FC[i]->func = fn_1_FED0;
        }
        BoardPlayerMotionShiftSet(lbl_1_bss_7E4, lbl_1_bss_7B8, 0.0f, 5.0f, 0x40000001);
        lbl_1_bss_7D6 = MGSeqStartCreate();
        BoardMusStart(1, 0xE, 0x7F, 0);
        arg0->func = fn_1_ECD4;
    }
    BoardPlayerPosSetV(lbl_1_bss_7E4, &spC);
}

static void fn_1_ECD4(omObjData *arg0) {
    lbl_1_bss_7EC *= 1.05f;
    lbl_1_bss_7E8 *= 1.05f;
    if (lbl_1_bss_7EC > 2.0f) {
        lbl_1_bss_7EC = 2.0f;
    }
    if (lbl_1_bss_7E8 > 4.0f) {
        lbl_1_bss_7E8 = 4.0f;
    }
    if (MGSeqStatGet(lbl_1_bss_7D6) == 0) {
        lbl_1_bss_7EC = 2.0f;
        lbl_1_bss_7E8 = 4.0f;
        arg0->func = fn_1_EED8;
        lbl_1_bss_7D2 = 5;
        lbl_1_bss_7D0 = 60;
        lbl_1_bss_7D4 = MGSeqTimerCreateXY(lbl_1_bss_7D2, 288, 64);
    }
    BoardModelMotionSpeedSet(lbl_1_bss_6C4[17], lbl_1_bss_7EC);
    BoardModelMotionSpeedSet(lbl_1_bss_6C4[18], lbl_1_bss_7E8);
    fn_1_10CF0(arg0->work[2]);
}

static void fn_1_EEA0(omObjData *arg0, u16 *arg1) {
    *arg1 = 0;
    if (arg0->work[3] != 0) {
        arg0->work[3]--;
    } else {
        *arg1 |= 0x100;
    }
}

static void fn_1_EED8(omObjData *arg0) {
    s16 temp_r29;
    u16 var_r30;

    fn_1_10CF0(arg0->work[2]);
    temp_r29 = GWPlayer[lbl_1_bss_7E4].port;
    if ((lbl_1_bss_7D0 -= 1) == 0) {
        if ((lbl_1_bss_7D2 -= 1) >= 0) {
            MGSeqParamSet(lbl_1_bss_7D4, 1, lbl_1_bss_7D2);
        }
        lbl_1_bss_7D0 = 60;
    }
    if (GWPlayerCfg[lbl_1_bss_7E4].iscom == 1) {
        fn_1_EEA0(arg0, &var_r30);
    } else {
        var_r30 = HuPadBtnDown[temp_r29];
    }
    if (lbl_1_bss_7D2 < 0 || (var_r30 & 0x100)) {
        BoardModelMotionSpeedSet(lbl_1_bss_6C4[17], 0.0f);
        MGSeqParamSet(lbl_1_bss_7D4, 2, -1);
        arg0->scale.y = 0.0f;
        arg0->func = fn_1_F09C;
    }
}

static void fn_1_F09C(omObjData *arg0) {
    float temp_f31;
    float var_f30;

    temp_f31 = BoardModelMotionMaxTimeGet(lbl_1_bss_6C4[18]);
    arg0->scale.y += lbl_1_bss_7E8;
    if (arg0->scale.y >= temp_f31 - 150.0f) {
        lbl_1_bss_7E8 *= 0.9745f;
        if (lbl_1_bss_7E8 < 0.08f) {
            lbl_1_bss_7E8 = 0.08f;
        }
    }
    BoardModelMotionSpeedSet(lbl_1_bss_6C4[18], lbl_1_bss_7E8);
    if (arg0->scale.y >= temp_f31) {
        BoardModelMotionSpeedSet(lbl_1_bss_6C4[18], 0.0f);
        var_f30 = arg0->scale.y - temp_f31 + BoardModelMotionTimeGet(lbl_1_bss_6C4[18]);
        if (var_f30 > temp_f31) {
            var_f30 -= temp_f31;
        }
        BoardModelMotionTimeSet(lbl_1_bss_6C4[18], var_f30);
        arg0->work[0] = fn_1_1001C(arg0->work[2]);
        BoardModelVisibilitySet(lbl_1_bss_6C4[20], 1);
        BoardModelPosSet(lbl_1_bss_6C4[20], lbl_1_bss_7FC[arg0->work[0]]->trans.x, lbl_1_bss_7FC[arg0->work[0]]->trans.y + 1.0f, lbl_1_bss_7FC[arg0->work[0]]->trans.z);
        BoardModelRotSet(lbl_1_bss_6C4[20], lbl_1_bss_7FC[arg0->work[0]]->rot.x, lbl_1_bss_7FC[arg0->work[0]]->rot.y + 1.0f, lbl_1_bss_7FC[arg0->work[0]]->rot.z);
        arg0->work[1] = 60;
        BoardAudSeqFadeOut(1, 100);
        arg0->func = fn_1_F348;
        HuAudFXPlay(0x40A);
    }
}

static void fn_1_F348(omObjData *arg0) {
    if ((arg0->work[1] / 4) & 1) {
        BoardModelVisibilitySet(lbl_1_bss_6C4[20], 0);
    } else {
        BoardModelVisibilitySet(lbl_1_bss_6C4[20], 1);
    }
    if ((arg0->work[1] -= 1) == 0) {
        BoardModelVisibilitySet(lbl_1_bss_6C4[20], 0);
        fn_1_101B8(arg0->work[0]);
        HuAudFXPlay(0x310);
        arg0->func = fn_1_F3F8;
    }
}

static void fn_1_F3F8(omObjData *arg0) {
    Vec sp18;
    Vec spC;

    if (lbl_1_bss_7F0->work[0] != 1) {
        return;
    }
    BoardPlayerPosGet(lbl_1_bss_7E4, &sp18);
    VECSubtract(&lbl_1_bss_7C4, &sp18, &spC);
    VECNormalize(&spC, &spC);
    arg0->trans.x = spC.x;
    arg0->trans.y = spC.y;
    arg0->trans.z = spC.z;
    arg0->rot.x = VECDistanceXZ(&lbl_1_bss_7C4, &sp18);
    arg0->scale.y = 20.0f + 40.0f * (arg0->rot.x / 445.0f);
    arg0->rot.y = 0.016666668f * (arg0->scale.y / 2) * (arg0->scale.y / 2);
    arg0->rot.z = sp18.y;
    arg0->scale.x = 0.0f;
    BoardPlayerMotionShiftSet(lbl_1_bss_7E4, 4, 0.0f, 5.0f, 0);
    VECSubtract(&lbl_1_bss_7C4, &sp18, &spC);
    VECNormalize(&spC, &spC);
    BoardPlayerRotSet(lbl_1_bss_7E4, 0.0f, fn_1_10EB8(&spC), 0.0f);
    arg0->func = fn_1_F6E8;
}

static void fn_1_F6E8(omObjData *arg0) {
    Vec sp8;

    BoardPlayerPosGet(lbl_1_bss_7E4, &sp8);
    sp8.x += arg0->trans.x * arg0->rot.x / arg0->scale.y;
    sp8.z += arg0->trans.z * arg0->rot.x / arg0->scale.y;
    sp8.y += arg0->rot.y - 0.016666668f * arg0->scale.x * arg0->scale.x;
    arg0->scale.x += 1.0f;
    if (sp8.y < lbl_1_bss_80C.y || arg0->scale.x >= arg0->scale.y) {
        sp8.y = lbl_1_bss_80C.y;
        BoardCameraMotionStart(BoardPlayerModelGet(lbl_1_bss_7E4), NULL, 700.0f, -1.0f);
        BoardPlayerMotionStart(lbl_1_bss_7E4, 2, 0x40000001);
        arg0->func = fn_1_F890;
    }
    BoardPlayerPosSetV(lbl_1_bss_7E4, &sp8);
}

static void fn_1_F890(omObjData *arg0) {
    Vec sp8;

    BoardPlayerRotGet(lbl_1_bss_7E4, &sp8);
    if (sp8.y == 0.0f) {
        BoardPlayerMotionShiftSet(lbl_1_bss_7E4, 1, 0.0f, 10.0f, 0x40000001);
        lbl_1_bss_7F0->work[0] = 0;
        lbl_1_bss_7F0->func = fn_1_10820;
        arg0->func = fn_1_FA1C;
    } else if (sp8.y > 180.0f) {
        if (360.0f - sp8.y < 3.0f) {
            sp8.y = 0.0f;
        } else {
            sp8.y += 3.0f;
        }
    } else {
        if (sp8.y < 3.0f) {
            sp8.y = 0.0f;
        } else {
            sp8.y -= 3.0f;
        }
    }
    BoardPlayerRotSetV(lbl_1_bss_7E4, &sp8);
}

static void fn_1_FA1C(omObjData *arg0) {
    if (lbl_1_bss_7F0->work[0] == 1) {
        BoardPlayerMotionShiftSet(lbl_1_bss_7E4, lbl_1_bss_7BC, 0.0f, 10.0f, 0);
        arg0->work[0] = 30;
        lbl_1_bss_7A4 = HuAudSStreamPlay(2);
        arg0->func = fn_1_FABC;
    }
}

static void fn_1_FABC(omObjData *arg0) {
    Process *var_r30;

    if (arg0->work[0] == 0) {
        if (HuAudSStreamStatGet(lbl_1_bss_7A4) == 0) {
            var_r30 = HuPrcCreate(fn_1_FB58, 0x2004, 0x1000, 0);
            var_r30->user_data = arg0;
            BoardAudSeqPause(0, 0, 1000);
            arg0->func = NULL;
        }
    } else {
        arg0->work[0]--;
    }
}

static void fn_1_FB58(void) {
    omObjData *temp_r31;

    BoardWinCreate(2, MAKE_MESSID(10, 6), 0);
    BoardWinInsertMesSet(MAKE_MESSID(8, lbl_1_bss_7F0->work[1]), 0);
    BoardWinWait();
    BoardWinKill();
    temp_r31 = HuPrcCurrentGet()->user_data;
    BoardPlayerMotionShiftSet(lbl_1_bss_7E4, 1, 0.0f, 10.0f, 0);
    lbl_1_bss_7F0->work[0] = 0;
    HuAudFXPlay(0x30D);
    HuAudFXFadeOut(lbl_1_bss_7AC, 1000);
    lbl_1_bss_7F0->func = fn_1_10AE8;
    temp_r31->func = fn_1_FC3C;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void fn_1_FC3C(omObjData *arg0) {
    Process *var_r31;

    if (lbl_1_bss_7F0->work[0] == 1) {
        BoardPlayerItemAdd(lbl_1_bss_7E4, lbl_1_bss_7F0->work[1]);
        omVibrate(lbl_1_bss_7E4, 12, 6, 6);
        var_r31 = HuPrcCreate(fn_1_FCEC, 0x2004, 0x1000, 0);
        var_r31->user_data = arg0;
        arg0->func = NULL;
    }
}

static void fn_1_FCEC(void) {
    omObjData *var_r31;

    BoardWinCreate(2, MAKE_MESSID(10, 7), 0);
    BoardWinWait();
    BoardWinKill();
    var_r31 = HuPrcCurrentGet()->user_data;
    var_r31->func = fn_1_FD3C;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void fn_1_FD3C(omObjData *arg0) {
    BoardStatusShowSetAll(1);
    BoardCameraTargetModelSet(lbl_1_bss_6C4[21]);
    BoardCameraOffsetSet(0.0f, 0.0f, 0.0f);
    BoardCameraXRotZoomSet(1200.0f, -45.0f);
    BoardModelMotionSpeedSet(lbl_1_bss_6C4[17], 1.0f);
    Hu3DModelKill(lbl_1_bss_7F0->model[0]);
    Hu3DModelKill(lbl_1_bss_7F0->model[1]);
    Hu3DModelKill(lbl_1_bss_7F0->model[2]);
    omDelObjEx(HuPrcCurrentGet(), lbl_1_bss_7F0);
    arg0->func = fn_1_FE44;
}

static void fn_1_FE44(omObjData *arg0) {
    if (BoardStatusStopCheck(lbl_1_bss_7E4) && BoardCameraMotionIsDone()) {
        lbl_1_bss_7AA = 1;
        BoardMGExit();
        HuAudFXPlay(0x40F);
        BoardModelMotionStart(lbl_1_bss_6C4[21], 0, 0x40000004);
        arg0->func = NULL;
    }
}

static void fn_1_FED0(omObjData *arg0) {
    float temp_f30;
    float var_f31;
    float var_f29;

    temp_f30 = BoardModelMotionTimeGet(lbl_1_bss_6C4[18]);
    var_f29 = BoardModelMotionMaxTimeGet(lbl_1_bss_6C4[18]);
    var_f31 = 90.0f - 90.0f * arg0->work[2] + 360.0f * (temp_f30 / var_f29);
    if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    omSetRot(arg0, 0.0f, var_f31, 0.0f);
}

static s16 fn_1_1001C(u32 arg0) {
    float var_f29;
    float var_f28;
    float temp_f27;
    float temp_f26;
    float var_f31;
    float var_f30;

    temp_f26 = BoardModelMotionMaxTimeGet(lbl_1_bss_6C4[18]);
    temp_f27 = 360.0f - 360.0f * (BoardModelMotionTimeGet(lbl_1_bss_6C4[18]) / temp_f26);
    var_f30 = BoardModelMotionTimeGet(lbl_1_bss_6C4[17]);
    var_f29 = BoardModelMotionMaxTimeGet(lbl_1_bss_6C4[17]);
    var_f30 = var_f30 - (var_f29 / 4) * arg0;
    if (var_f30 < 0.0f) {
        var_f30 += var_f29;
    }
    var_f28 = 360.0f * (var_f30 / var_f29);
    var_f31 = var_f28 - temp_f27;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    var_f31 /= 90.0f;
    return var_f31;
}

static void fn_1_101B8(s16 arg0) {
    omObjData *var_r31;
    float *var_r30;
    float var_f27;
    float temp_f26;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float var_f31;

    var_r31 = lbl_1_bss_7F0 = omAddObjEx(boardObjMan, 0x165, 3, 0, -1, fn_1_10664);
    var_r31->model[0] = lbl_1_bss_7FC[arg0]->model[1];
    Hu3DModelAttrReset(var_r31->model[0], 1);
    lbl_1_bss_7F0->work[1] = lbl_1_bss_7FC[arg0]->work[1];
    lbl_1_bss_7F0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 3 * sizeof(float), MEMORY_DEFAULT_NUM);
    var_r30 = lbl_1_bss_7F0->data;
    omSetRot(var_r31, 0.0f, 0.0f, 0.0f);
    omSetSca(var_r31, 0.0f, 0.0f, 0.0f);
    temp_f26 = BoardModelMotionMaxTimeGet(lbl_1_bss_6C4[18]);
    var_f27 = 360.0f - 360.0f * (BoardModelMotionTimeGet(lbl_1_bss_6C4[18]) / temp_f26);
    var_f31 = 45.0f + var_f27 + 90.0f * arg0;
    if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    temp_f30 = lbl_1_bss_80C.x - 100.0 * cosd(var_f31);
    temp_f28 = lbl_1_bss_80C.z - 100.0 * sind(var_f31);
    temp_f29 = lbl_1_bss_80C.y + 66.0f + 1.0f;
    omSetTra(var_r31, temp_f30, temp_f29, temp_f28);
    var_r31->work[0] = 0;
    var_r30[0] = 0.1f;
    var_r30[2] = 20.0f;
    var_r30[1] = 0.0f;
    var_r31->model[1] = Hu3DParticleCreate(lbl_1_bss_7A0, 200);
    var_r31->model[2] = Hu3DParticleCreate(lbl_1_bss_7A0, 100);
    Hu3DParticleHookSet(var_r31->model[1], fn_1_11064);
    Hu3DParticleHookSet(var_r31->model[2], fn_1_11484);
    Hu3DParticleColSet(var_r31->model[1], 0xFF, 0xFF, 0);
    Hu3DParticleColSet(var_r31->model[2], 0xFF, 0xFF, 0);
    Hu3DModelPosSet(var_r31->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(var_r31->model[2], temp_f30, temp_f29, temp_f28);
    Hu3DParticleBlendModeSet(var_r31->model[1], 1);
    Hu3DParticleBlendModeSet(var_r31->model[2], 1);
    Hu3DModelLayerSet(var_r31->model[1], 3);
    Hu3DModelLayerSet(var_r31->model[2], 3);
    lbl_1_bss_7AC = HuAudFXPlay(0x35F);
}

static void fn_1_10664(omObjData *arg0) {
    float *temp_r31;
    float var_f31;

    temp_r31 = arg0->data;
    var_f31 = temp_r31[0];
    if (arg0->work[0] == 0) {
        if (var_f31 > 1.0f) {
            var_f31 = 1.0f;
        } else {
            temp_r31[0] += 0.025f;
        }
        arg0->trans.y += temp_r31[2];
        temp_r31[2] -= 1.0f;
        if (temp_r31[2] < 0.0f && arg0->trans.y < lbl_1_bss_80C.y + 66.0f + 1.0f + 90.0f) {
            arg0->work[0] = 1;
        }
        omSetSca(arg0, var_f31, var_f31, var_f31);
    } else {
        arg0->trans.y += sind(temp_r31[1]);
        temp_r31[1] += 4.0f;
        if (temp_r31[1] >= 360.0f) {
            temp_r31[1] -= 360.0f;
        }
    }
}

static void fn_1_10820(omObjData *arg0) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f28;
    float *temp_r30;

    temp_r30 = arg0->data;
    if (arg0->work[0] == 0) {
        BoardPlayerPosGet(lbl_1_bss_7E4, &sp24);
        sp18.x = arg0->trans.x;
        sp18.y = 0.0f;
        sp18.z = arg0->trans.z;
        sp24.y = 0.0f;
        VECSubtract(&sp24, &sp18, &spC);
        VECNormalize(&spC, &spC);
        var_f28 = VECDistanceXZ(&sp24, &sp18);
        if (var_f28 < 8.0f) {
            arg0->trans.x = sp24.x;
            arg0->trans.z = sp24.z;
            arg0->work[0] = 1;
        } else {
            arg0->trans.x += 8.0f * spC.x;
            arg0->trans.z += 8.0f * spC.z;
        }
    }
    arg0->trans.y += sind(temp_r30[1]);
    temp_r30[1] += 4.0f;
    if (temp_r30[1] >= 360.0f) {
        temp_r30[1] -= 360.0f;
    }
}

static void fn_1_10AE8(omObjData *arg0) {
    float *temp_r31;

    temp_r31 = arg0->data;
    if (arg0->work[0] == 0) {
        temp_r31[0] -= 0.016666668f;
        if (temp_r31[0] <= 0.0f) {
            temp_r31[0] = 0.0f;
            arg0->work[0] = 1;
            HuAudFXStop(lbl_1_bss_7AC);
        }
        arg0->trans.y -= 2.1666667f;
    }
    omSetSca(arg0, temp_r31[0], temp_r31[0], temp_r31[0]);
}

static float fn_1_10BB0(u32 arg0) {
    float var_f30;
    float temp_f29;
    float var_f31;

    var_f30 = BoardModelMotionTimeGet(lbl_1_bss_6C4[17]);
    temp_f29 = BoardModelMotionMaxTimeGet(lbl_1_bss_6C4[17]);
    var_f30 = var_f30 - (temp_f29 / 4) * arg0;
    if (var_f30 < 0.0f) {
        var_f30 += temp_f29;
    }
    var_f31 = 180.0f + -360.0f * (var_f30 / temp_f29);
    if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    return var_f31;
}

static void fn_1_10CF0(u32 arg0) {
    float var_f30;
    float temp_f29;
    float var_f31;
    float var_f28;

    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_6C4[17]), lbl_1_data_F9C[arg0], &lbl_1_bss_7D8);
    BoardPlayerPosSetV(lbl_1_bss_7E4, &lbl_1_bss_7D8);
    var_f30 = BoardModelMotionTimeGet(lbl_1_bss_6C4[17]);
    temp_f29 = BoardModelMotionMaxTimeGet(lbl_1_bss_6C4[17]);
    var_f30 = var_f30 - (temp_f29 / 4) * arg0;
    if (var_f30 < 0.0f) {
        var_f30 += temp_f29;
    }
    var_f31 = 180.0f + -360.0f * (var_f30 / temp_f29);
    if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    var_f28 = var_f31;
    BoardPlayerRotSet(lbl_1_bss_7E4, 0.0f, var_f28, 0.0f);
}

static float fn_1_10EB8(Vec *arg0) {
    float var_f31;

    if (arg0->x || arg0->z) {
        if (arg0->x == 0.0f) {
            if (arg0->z > 0.0f) {
                return 0.0f;
            } else {
                return 180.0f;
            }
        }
        if (arg0->z == 0.0f) {
            if (arg0->x > 0.0f) {
                return 90.0f;
            } else {
                return 270.0f;
            }
        }
        var_f31 = atan2d(arg0->z, arg0->x);
        if (arg0->z < 0.0f) {
            var_f31 = 90.0f - var_f31;
        } else {
            var_f31 = 90.0f - var_f31;
            if (var_f31 < 0.0f) {
                var_f31 += 360.0f;
            }
        }
        return var_f31;
    }
    return -1.0f;
}

static void fn_1_11064(ModelData *model, ParticleData *particle, Mtx matrix) {
    HsfanimStruct01 *var_r31;
    float temp_f30;
    float temp_f29;
    float temp_f31;
    s32 var_r28;
    s32 i;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
        particle->unk_00 = 0;
    }
    temp_f31 = lbl_1_bss_7F0->scale.x;
    for (i = 0; i < 30; i++) {
        var_r31 = particle->unk_48;
        for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
            if (var_r31->unk2C == 0.0f) {
                break;
            }
        }
        if (var_r28 != particle->unk_30) {
            temp_f30 = 0.003921569f * frand8() * 360.0f;
            temp_f29 = 0.003921569f * frand8() * 70.0f * temp_f31;
            var_r31->unk34.x = lbl_1_bss_7F0->trans.x + temp_f29 * sind(temp_f30);
            var_r31->unk34.z = lbl_1_bss_7F0->trans.z + temp_f29 * cosd(temp_f30);
            var_r31->unk34.y = lbl_1_bss_7F0->trans.y + temp_f31 * (-30.0f + 0.003921569f * frand8() * 60.0f);
            var_r31->unk08.x = 0.5f + 0.003921569f * frand8() * 3.0f;
            var_r31->unk08.y = 0.3f + 0.003921569f * frand8() * 2.0f;
            var_r31->unk40.a = 0xB4;
            var_r31->unk2C = 15.0f * temp_f31;
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

static void fn_1_11484(ModelData *model, ParticleData *particle, Mtx matrix) {
    HsfanimStruct01 *var_r31;
    float temp_f29;
    float temp_f30;
    float temp_f31;
    s32 var_r28;
    s32 var_r29;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
        particle->unk_00 = 0;
    }
    if (particle->unk_00 == 0) {
        var_r31 = particle->unk_48;
        for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
            temp_f30 = 0.003921569f * frand8() * 360.0f;
            temp_f31 = 0.003921569f * frand8() * 50.0f;
            var_r31->unk08.x = temp_f31 * cosd(temp_f30);
            var_r31->unk08.y = 2.0f + 0.003921569f * frand8() * 4.0f;
            var_r31->unk08.z = temp_f31 * sind(temp_f30);
            temp_f29 = 60.0f + 20.0f * frand8() * 0.003921569f;
            temp_f31 = 4.0f + 5.0f * frand8() * 0.003921569f;
            var_r31->unk14.x = temp_f31 * sind(temp_f30) * cosd(temp_f29);
            var_r31->unk14.y = temp_f31 * sind(temp_f29);
            var_r31->unk14.z = temp_f31 * cosd(temp_f30) * cosd(temp_f29);
            var_r31->unk20 = 1.0f;
            var_r31->unk40.a = 0xB4;
            var_r31->unk2C = 9.0f + 0.003921569f * frand8() * 4.0f;
        }
        particle->unk_00 = 1;
    }
    var_r31 = particle->unk_48;
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk2C != 0.0f) {
            var_r31->unk34.x = var_r31->unk08.x + var_r31->unk14.x * var_r31->unk20;
            var_r31->unk34.z = var_r31->unk08.z + var_r31->unk14.z * var_r31->unk20;
            var_r31->unk34.y = var_r31->unk08.y + var_r31->unk14.y * var_r31->unk20 - 0.2f * var_r31->unk20 * var_r31->unk20;
            var_r31->unk2C -= 0.25f;
            var_r31->unk20 += 1.0f;
            if (var_r31->unk2C <= 0.0f) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}
