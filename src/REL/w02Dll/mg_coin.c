#include "REL/w02Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/objsub.h"
#include "game/pad.h"

#include "ext_math.h"

#include "game/minigame_seq.h"

s16 lbl_1_bss_C2[3];
s16 lbl_1_bss_BC[3];
float lbl_1_bss_B0[3];
omObjData *lbl_1_bss_AC;
omObjData *lbl_1_bss_A8;
omObjData *lbl_1_bss_A4;
u16 lbl_1_bss_A0;
Vec lbl_1_bss_94;
Vec lbl_1_bss_88;
s16 lbl_1_bss_86;
s16 lbl_1_bss_84;
s16 lbl_1_bss_5C[20];
s32 lbl_1_bss_58;

Vec lbl_1_data_378[3] = { { -45, 155, 108 }, { 0, 155, 108 }, { 45, 155, 108 } };

Vec lbl_1_data_39C[3] = { { -45, 25, 200 }, { 0, 25, 200 }, { 45, 25, 200 } };

s32 lbl_1_data_3C0[9] = { 5, 10, 20, 5, 10, 20, 5, 10, 20 };

s32 lbl_1_data_3E4[8] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x08), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x08), DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x08),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x08), DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x08), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x08),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x08), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x08) };

s32 lbl_1_data_404[8] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x0A), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x0A), DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x0A),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x0A), DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x0A), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x0A),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x0A), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x0A) };

void fn_1_51B4(Vec *arg0);

void fn_1_39F4(void)
{
    Vec sp8;
    s32 temp_r31;
    BoardModelVisibilitySet(lbl_1_bss_30[7], 1);
    BoardModelVisibilitySet(lbl_1_bss_30[8], 1);
    BoardModelVisibilitySet(lbl_1_bss_30[9], 0);
    BoardModelAttrSet(lbl_1_bss_30[8], 0x40000002);
    BoardModelAttrSet(lbl_1_bss_30[9], 0x40000003);
    BoardModelAttrSet(lbl_1_bss_30[7], 0x40000001);
    BoardModelPosGet(lbl_1_bss_30[8], &lbl_1_bss_94);
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        lbl_1_bss_C2[temp_r31] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x13), NULL, 1);
        lbl_1_bss_BC[temp_r31] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x14), NULL, 1);
        BoardModelAttrSet(lbl_1_bss_BC[temp_r31], 0x40000002);
        lbl_1_bss_B0[temp_r31] = (s32)frandmod(9) * 40.0f;
        sp8.x = lbl_1_bss_B0[temp_r31];
        sp8.y = sp8.z = 0;
        BoardModelRotSetV(lbl_1_bss_C2[temp_r31], &sp8);
    }
    BoardModelPosSetV(lbl_1_bss_30[7], &lbl_1_bss_94);
    fn_1_51B4(&lbl_1_bss_94);
}

void fn_1_3F0C(omObjData *object);
void fn_1_4050(omObjData *object);

typedef struct work_mgcoin_player {
    float unk0[3];
    float unkC[3];
    float unk18[3];
    s16 unk24[3];
} WorkMGCoinPlayer;

typedef struct work_mgcoin {
    float unk0;
    float unk4;
    s16 unk8;
    Vec unkC;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
} WorkMGCoin;

void fn_1_3BF4(void)
{
    Vec sp8;

    s32 temp_r31;
    WorkMGCoinPlayer *temp_r30;
    lbl_1_bss_86 = GWSystem.player_curr;
    lbl_1_bss_AC = omAddObjEx(boardObjMan, 257, 0, 0, -1, fn_1_3F0C);
    lbl_1_bss_A4 = omAddObjEx(boardObjMan, 257, 0, 0, -1, fn_1_4050);
    lbl_1_bss_A8 = omAddObjEx(boardObjMan, 257, 0, 2, -1, NULL);
    lbl_1_bss_A8->motion[0] = BoardPlayerMotionCreate(lbl_1_bss_86, lbl_1_data_3E4[GWPlayer[lbl_1_bss_86].character]);
    lbl_1_bss_A8->motion[1] = BoardPlayerMotionCreate(lbl_1_bss_86, lbl_1_data_404[GWPlayer[lbl_1_bss_86].character]);
    lbl_1_bss_A4->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkMGCoinPlayer), MEMORY_DEFAULT_NUM);
    temp_r30 = lbl_1_bss_A4->data;
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        temp_r30->unk0[temp_r31] = lbl_1_bss_B0[temp_r31];
        temp_r30->unkC[temp_r31] = 0;
        temp_r30->unk18[temp_r31] = 0;
        temp_r30->unk24[temp_r31] = 0;
    }
    lbl_1_bss_A8->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkMGCoin), MEMORY_DEFAULT_NUM);
    BoardPlayerPosGet(lbl_1_bss_86, &sp8);
    lbl_1_bss_A8->trans.x = sp8.x;
    lbl_1_bss_A8->trans.y = sp8.y;
    lbl_1_bss_A8->trans.z = sp8.z;
    for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
        lbl_1_bss_5C[temp_r31] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x0A), NULL, 1);
        BoardModelVisibilitySet(lbl_1_bss_5C[temp_r31], 0);
    }
    lbl_1_bss_A0 = 0;
}

void fn_1_3F94(void);

void fn_1_3F0C(omObjData *object)
{
    if (lbl_1_bss_A0 && BoardMGDoneFlagGet() == 1) {
        fn_1_3F94();
        omDelObjEx(boardObjMan, object);
    }
}

void fn_1_3F64(void)
{
    lbl_1_bss_A0 = 1;
    BoardMGExit();
}

void fn_1_3F94(void)
{
    s32 temp_r31;
    BoardPlayerMotionKill(lbl_1_bss_86, lbl_1_bss_A8->motion[0]);
    BoardPlayerMotionKill(lbl_1_bss_86, lbl_1_bss_A8->motion[1]);
    omDelObjEx(boardObjMan, lbl_1_bss_A8);
    for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
        BoardModelKill(lbl_1_bss_5C[temp_r31]);
    }
    BoardMGDoneFlagSet(0);
}

void fn_1_4100(omObjData *object);

void fn_1_4050(omObjData *object)
{
    if (object->work[0] == 0) {
        object->work[0] = MGSeqStartCreate();
        return;
    }
    if (MGSeqStatGet(object->work[0])) {
        return;
    }
    object->func = fn_1_4100;
    BoardModelMotionTimeSet(lbl_1_bss_30[8], 0);
    BoardModelAttrReset(lbl_1_bss_30[8], 0x40000006);
    HuAudFXPlay(1062);
}

void fn_1_41B8(omObjData *object);

void fn_1_4100(omObjData *object)
{
    if (BoardModelMotionTimeGet(lbl_1_bss_30[8]) >= BoardModelMotionMaxTimeGet(lbl_1_bss_30[8])) {
        object->work[0] = 0;
        object->work[1] = 0;
        object->work[2] = 1;
        object->work[3] = 0;
        object->func = fn_1_41B8;
        BoardModelAttrSet(lbl_1_bss_30[8], 0x40000004);
        lbl_1_bss_58 = HuAudFXPlay(1063);
    }
}

void fn_1_4378(omObjData *object);
void fn_1_5290(omObjData *object);

void fn_1_41B8(omObjData *object)
{
    Vec sp8;
    WorkMGCoinPlayer *temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    u32 temp_r27;
    temp_r30 = object->data;
    if (object->work[1] == 0) {
        object->work[0] |= object->work[2];
        object->work[1] = 12;
        object->work[2] <<= 1;
    }
    else {
        object->work[1]--;
    }
    sp8.y = sp8.z = 0;
    temp_r28 = 0;
    for (temp_r29 = 0; temp_r29 < 3; temp_r29++) {
        temp_r27 = 1 << temp_r29;
        if (object->work[0] & temp_r27) {
            temp_r30->unkC[temp_r29] += 0.25f;
            if (temp_r30->unkC[temp_r29] > 5.0f) {
                temp_r30->unkC[temp_r29] = 5.0f;
                temp_r28++;
            }
            temp_r30->unk0[temp_r29] += temp_r30->unkC[temp_r29];
            if (temp_r30->unk0[temp_r29] >= 360.0f) {
                temp_r30->unk0[temp_r29] -= 360.0f;
            }
            sp8.x = temp_r30->unk0[temp_r29];
            BoardModelRotSetV(lbl_1_bss_C2[temp_r29], &sp8);
        }
    }
    if (temp_r28 == 3) {
        object->func = fn_1_4378;
        lbl_1_bss_A8->func = fn_1_5290;
    }
}

void fn_1_4698(omObjData *object);

void fn_1_46E8(void);

void fn_1_4378(omObjData *object)
{
    Vec sp8;
    float temp_f31;
    WorkMGCoinPlayer *temp_r31;
    s32 temp_r30;
    s32 temp_r28;
    Process *temp_r27;
    temp_r31 = object->data;
    sp8.y = sp8.z = 0;
    for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
        temp_r28 = 1 << temp_r30;
        if (object->work[0] & temp_r28) {
            if (object->work[3] & temp_r28) {
                temp_r31->unk18[temp_r30] = 360;
                temp_r31->unk24[temp_r30] = 1;
                object->work[3] &= ~temp_r28;
            }
            if (temp_r31->unk24[temp_r30]) {
                if (0.0f == temp_r31->unk18[temp_r30]) {
                    temp_f31 = fmod(temp_r31->unk0[temp_r30], 40.0);
                    if (temp_f31 + temp_r31->unkC[temp_r30] >= 40.0f) {
                        temp_r31->unk0[temp_r30] += (temp_f31 + temp_r31->unkC[temp_r30]) - 40.0f;
                        temp_f31 = 0;
                    }
                    if (0.0f == temp_f31) {
                        HuAudFXPlay(1067);
                        object->work[0] &= ~temp_r28;
                        temp_r31->unkC[temp_r30] = 0;
                        lbl_1_bss_A8->work[2] = 60;
                        if (temp_r30 != 2) {
                            lbl_1_bss_A8->func = fn_1_5290;
                        }
                        else {
                            BoardAudSeqFadeOut(1, 100);
                            temp_r27 = HuPrcCreate(fn_1_46E8, 8196, 6144, 0);
                            temp_r27->user_data = object;
                            HuAudFXStop(lbl_1_bss_58);
                            object->func = fn_1_4698;
                        }
                    }
                }
                else {
                    temp_r31->unk18[temp_r30] -= temp_r31->unkC[temp_r30];
                    if (temp_r31->unk18[temp_r30] < 0.0f) {
                        temp_r31->unk18[temp_r30] = 0.0f;
                    }
                }
            }
            temp_r31->unk0[temp_r30] += temp_r31->unkC[temp_r30];
            if (temp_r31->unk0[temp_r30] >= 360.0f) {
                temp_r31->unk0[temp_r30] -= 360.0f;
            }
        }
        sp8.x = temp_r31->unk0[temp_r30];
        BoardModelRotSetV(lbl_1_bss_C2[temp_r30], &sp8);
    }
}

void fn_1_4698(omObjData *object)
{
    if (msmMusGetStatus(1) == 0) {
        BoardAudSeqPause(0, 0, 1000);
        object->func = NULL;
    }
}

void fn_1_511C(omObjData *object);

void fn_1_46E8(void)
{
    Vec sp21C[20];
    Vec sp12C[20];
    Vec sp3C[20];
    s32 sp30[3];
    Vec sp24;
    Vec sp18;
    Vec spC;
    char sp8[4];
    float temp_f31;
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    omObjData *temp_r27;
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        BoardModelRotGet(lbl_1_bss_C2[temp_r31], &sp24);
        sp30[temp_r31] = lbl_1_data_3C0[(int)(sp24.x / 40.0f)];
    }
    if (sp30[0] == sp30[1] && sp30[0] == sp30[2]) {
        lbl_1_bss_84 = sp30[0];
    }
    else {
        lbl_1_bss_84 = 1;
    }
    if (lbl_1_bss_84 != 1) {
        BoardModelVisibilitySet(lbl_1_bss_30[9], 1);
        BoardModelAttrReset(lbl_1_bss_30[9], 0x40000002);
    }
    sprintf(sp8, "%d", lbl_1_bss_84);
    BoardWinCreate(2, MAKE_MESSID(19, 19), 4);
    BoardWinInsertMesSet((u32)sp8, 0);
    BoardWinWait();
    BoardWinKill();
    BoardCameraTargetModelSet(-1);
    temp_r30 = 0;
    temp_r29 = 45;
    temp_f31 = 0;
    sp18 = lbl_1_bss_94;
    HuAudFXPlay(1065);
    while (1) {
        temp_r28 = 0;
        if (temp_r29 == 0 && temp_r30 < lbl_1_bss_84) {
            HuAudFXPlay(18);
            BoardModelVisibilitySet(lbl_1_bss_5C[temp_r30], 1);
            sp21C[temp_r30].x = -5.0f + ((1.0f / 255.0f) * (10.0f * frand8()));
            sp21C[temp_r30].y = 212.5f;
            sp21C[temp_r30].z = 130.0f;
            VECAdd(&sp21C[temp_r30], &sp18, &sp21C[temp_r30]);
            BoardModelPosSetV(lbl_1_bss_5C[temp_r30], &sp21C[temp_r30]);
            sp12C[temp_r30].x = -1.0f + ((1.0f / 255.0f) * (2.0f * frand8()));
            sp12C[temp_r30].y = 18.0f;
            sp12C[temp_r30].z = 0.0f;
            temp_r29 = frandmod(3) + 5;
            temp_r30++;
        }
        else {
            temp_r29--;
        }
        for (temp_r31 = 0; temp_r31 < temp_r30; temp_r31++) {
            if (sp21C[temp_r31].y >= 500.0f) {
                BoardModelVisibilitySet(lbl_1_bss_5C[temp_r31], 0);
                temp_r28++;
            }
            else {
                VECAdd(&sp21C[temp_r31], &sp12C[temp_r31], &sp21C[temp_r31]);
            }
            BoardModelPosSetV(lbl_1_bss_5C[temp_r31], &sp21C[temp_r31]);
        }
        sp18.y += 0.8f * sind(temp_f31);
        temp_f31 += 45.0f;
        if (temp_f31 >= 360.0f) {
            temp_f31 -= 360.0f;
        }
        fn_1_51B4(&sp18);
        if (temp_r28 == lbl_1_bss_84) {
            break;
        }
        HuPrcVSleep();
    }
    fn_1_51B4(&lbl_1_bss_94);
    BoardModelAttrSet(lbl_1_bss_30[9], 0x40000002);
    BoardModelMotionTimeSet(lbl_1_bss_30[9], 0);
    BoardModelVisibilitySet(lbl_1_bss_30[9], 0);
    BoardPlayerPosGet(lbl_1_bss_86, &sp18);
    for (temp_r31 = 0; temp_r31 < lbl_1_bss_84; temp_r31++) {
        BoardModelVisibilitySet(lbl_1_bss_5C[temp_r31], 1);
        sp21C[temp_r31] = sp18;
        sp21C[temp_r31].y += (temp_r31 * 120) + 600.0f;
        sp21C[temp_r31].x += -25.0f + ((1.0f / 255.0f) * (50.0f * frand8()));
        sp21C[temp_r31].z += -25.0f + ((1.0f / 255.0f) * (50.0f * frand8()));
        sp3C[temp_r31].x = sp3C[temp_r31].z = 0;
        sp3C[temp_r31].y = ((1.0f / 255.0f) * (360.0f * frand8()));
        BoardModelPosSetV(lbl_1_bss_5C[temp_r31], &sp21C[temp_r31]);
        BoardModelRotSetV(lbl_1_bss_5C[temp_r31], &sp3C[temp_r31]);
    }
    temp_f31 = -1;
    temp_r30 = 0;
    while (1) {
        for (temp_r31 = 0; temp_r31 < lbl_1_bss_84; temp_r31++) {
            if (temp_r31 < temp_r30) {
                continue;
            }
            sp21C[temp_r31].y += temp_f31;
            BoardModelPosSetV(lbl_1_bss_5C[temp_r31], &sp21C[temp_r31]);
            sp3C[temp_r31].y += 45.0f;
            if (sp3C[temp_r31].y >= 360.0f) {
                sp3C[temp_r31].y -= 360.0f;
            }
            BoardModelRotSetV(lbl_1_bss_5C[temp_r31], &sp3C[temp_r31]);
            if (sp21C[temp_r31].y <= 80.0f + sp18.y) {
                spC = sp21C[temp_r31];
                CharModelCoinEffectCreate(1, &spC);
                BoardModelVisibilitySet(lbl_1_bss_5C[temp_r31], 0);
                temp_r30++;
                BoardPlayerCoinsAdd(lbl_1_bss_86, 1);
                HuAudFXPlay(7);
                omVibrate(lbl_1_bss_86, 12, 6, 6);
            }
        }
        temp_f31 *= 1.05f;
        if (temp_f31 < -20.0f) {
            temp_f31 = -20.0f;
        }
        if (temp_r30 == lbl_1_bss_84) {
            BoardPlayerMotionShiftSet(lbl_1_bss_86, 7, 0, 10, 0);
            break;
        }
        HuPrcVSleep();
    }
    while (!BoardPlayerMotionEndCheck(lbl_1_bss_86)) {
        HuPrcVSleep();
    }
    fn_1_121C(MAKE_MESSID(0x13, 0x14));
    temp_r27 = HuPrcCurrentGet()->user_data;
    temp_r27->func = fn_1_511C;
    HuPrcEnd();
}

void fn_1_511C(omObjData *object)
{
    Vec spC;
    s32 temp_r31;
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        BoardModelRotGet(lbl_1_bss_C2[temp_r31], &spC);
        lbl_1_bss_B0[temp_r31] = spC.x;
    }
    fn_1_3F64();
    omDelObjEx(boardObjMan, object);
}

void fn_1_51B4(Vec *arg0)
{
    s32 temp_r31;
    Vec sp8;
    BoardModelPosSetV(lbl_1_bss_30[8], arg0);
    BoardModelPosSetV(lbl_1_bss_30[9], arg0);
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        VECAdd(arg0, &lbl_1_data_378[temp_r31], &sp8);
        BoardModelPosSetV(lbl_1_bss_C2[temp_r31], &sp8);
        VECAdd(arg0, &lbl_1_data_39C[temp_r31], &sp8);
        BoardModelPosSetV(lbl_1_bss_BC[temp_r31], &sp8);
    }
}

void fn_1_53B8(omObjData *object);

void fn_1_5290(omObjData *object)
{
    WorkMGCoin *temp_r31;
    float sp8[2];
    if (object->work[2] == 0) {
        temp_r31 = object->data;
        temp_r31->unk18 = 5;
        temp_r31->unk1A = 60;
        temp_r31->unk1C = MGSeqTimerCreateXY(temp_r31->unk18, 288, 64);
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x13, 0x15));
        temp_r31->unk1E = HuWinCreate(-10000, 400, sp8[0], sp8[1], 0);
        HuWinMesSet(temp_r31->unk1E, MAKE_MESSID(0x13, 0x15));
        HuWinBGTPLvlSet(temp_r31->unk1E, 0);
        HuWinMesSpeedSet(temp_r31->unk1E, 0);
        temp_r31->unk20 = frandmod(100) + 20;
        object->func = fn_1_53B8;
    }
    else {
        object->work[2]--;
    }
}

void fn_1_5634(omObjData *object);

void fn_1_53B8(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    WorkMGCoin *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    temp_r31 = object->data;
    temp_r28 = GWPlayer[lbl_1_bss_86].port;
    if (--temp_r31->unk1A == 0) {
        temp_r31->unk1A = 60;
        if (--temp_r31->unk18 >= 0) {
            MGSeqParamSet(temp_r31->unk1C, 1, temp_r31->unk18);
        }
    }
    if (!GWPlayer[lbl_1_bss_86].com) {
        temp_r29 = HuPadBtnDown[temp_r28];
    }
    else {
        if (--temp_r31->unk20 == 0) {
            temp_r29 = PAD_BUTTON_A;
        }
    }
    if ((temp_r29 & PAD_BUTTON_A) || temp_r31->unk18 < 0) {
        MGSeqParamSet(temp_r31->unk1C, 2, -1);
        HuWinKill(temp_r31->unk1E);
        BoardPlayerMotionShiftSet(lbl_1_bss_86, 4, 0, 5, 0);
        temp_r31->unk0 = 10;
        temp_r31->unk4 = 0;
        if (lbl_1_bss_A4->work[0] & 0x1) {
            temp_r31->unk8 = 0;
        }
        else {
            if (lbl_1_bss_A4->work[0] & 0x2) {
                temp_r31->unk8 = 1;
            }
            else {
                temp_r31->unk8 = 2;
            }
        }
        BoardPlayerPosGet(lbl_1_bss_86, &sp14);
        sp8 = lbl_1_bss_94;
        VECAdd(&sp8, &lbl_1_data_39C[temp_r31->unk8], &sp8);
        VECSubtract(&sp8, &sp14, &temp_r31->unkC);
        VECScale(&temp_r31->unkC, &temp_r31->unkC, 0.05f);
        object->work[0] = 1;
        object->func = fn_1_5634;
    }
}

void fn_1_5868(omObjData *object);

void fn_1_5634(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    float temp_f31;
    WorkMGCoin *temp_r31;
    temp_r31 = object->data;
    if (object->work[0] == 1) {
        BoardPlayerPosGet(lbl_1_bss_86, &sp14);
        temp_r31->unkC.y = temp_r31->unk0 - (0.075f * (0.25f * (temp_r31->unk4 * temp_r31->unk4)));
        temp_r31->unk4++;
        VECAdd(&sp14, &temp_r31->unkC, &sp14);
        if (sp14.y <= lbl_1_bss_94.y) {
            sp14.y = lbl_1_bss_94.y;
        }
        BoardPlayerPosSetV(lbl_1_bss_86, &sp14);
        sp8 = lbl_1_bss_94;
        VECAdd(&sp8, &lbl_1_data_39C[temp_r31->unk8], &sp8);
        sp8.y = sp14.y = 0;
        VECSubtract(&sp8, &sp14, &sp14);
        temp_f31 = VECMag(&sp14);
        if (temp_f31 <= 1.0f) {
            BoardPlayerMotionStart(lbl_1_bss_86, object->motion[0], 0);
            object->work[0] = 0;
        }
    }
    else {
        if (BoardPlayerMotionTimeGet(lbl_1_bss_86) >= BoardPlayerMotionMaxTimeGet(lbl_1_bss_86)) {
            temp_r31->unk0 = -5;
            temp_r31->unk4 = 0;
            temp_r31->unkC.x = temp_r31->unkC.z = 0;
            object->func = fn_1_5868;
        }
    }
}

void fn_1_5AC0(omObjData *object);

void fn_1_5868(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    WorkMGCoin *temp_r31;
    temp_r31 = object->data;
    BoardPlayerPosGet(lbl_1_bss_86, &sp14);
    temp_r31->unkC.y = temp_r31->unk0 - (0.075f * (0.25f * (temp_r31->unk4 * temp_r31->unk4)));
    temp_r31->unk4++;
    VECAdd(&sp14, &temp_r31->unkC, &sp14);
    sp8 = lbl_1_bss_94;
    VECAdd(&sp8, &lbl_1_data_39C[temp_r31->unk8], &sp8);
    sp8.y += 16.0f;
    if (sp14.y <= sp8.y) {
        sp14.y = sp8.y;
    }
    BoardPlayerPosSetV(lbl_1_bss_86, &sp14);
    if (sp14.y == sp8.y) {
        BoardModelMotionTimeSet(lbl_1_bss_BC[temp_r31->unk8], 0);
        BoardModelAttrReset(lbl_1_bss_BC[temp_r31->unk8], 0x40000002);
        BoardPlayerMotionShiftSet(lbl_1_bss_86, object->motion[1], 0, 5, 0);
        lbl_1_bss_A4->work[3] |= 1 << temp_r31->unk8;
        temp_r31->unk0 = 5;
        temp_r31->unk4 = 0;
        sp8.x = object->trans.x;
        sp8.y = object->trans.y;
        sp8.z = object->trans.z;
        VECSubtract(&sp8, &sp14, &temp_r31->unkC);
        VECScale(&temp_r31->unkC, &temp_r31->unkC, 0.03f);
        HuAudFXPlay(1064);
        object->func = fn_1_5AC0;
    }
}

void fn_1_5C84(omObjData *object);

void fn_1_5AC0(omObjData *object)
{
    float temp_f31;
    float temp_f30;
    Vec sp14;
    Vec sp8;
    WorkMGCoin *temp_r30;
    temp_r30 = object->data;
    BoardPlayerPosGet(lbl_1_bss_86, &sp14);
    temp_r30->unkC.y = temp_r30->unk0 - (0.075f * (0.25f * (temp_r30->unk4 * temp_r30->unk4)));
    temp_r30->unk4++;
    VECAdd(&sp14, &temp_r30->unkC, &sp14);
    sp8.x = object->trans.x;
    sp8.y = 0;
    sp8.z = object->trans.z;
    temp_f30 = sp14.y;
    sp14.y = 0;
    VECSubtract(&sp8, &sp14, &sp8);
    sp14.y = temp_f30;
    temp_f31 = VECMag(&sp8);
    if (temp_f31 <= 1.0f) {
        temp_r30->unkC.x = temp_r30->unkC.z = 0;
    }
    if (sp14.y <= object->trans.y) {
        sp14.x = object->trans.x;
        sp14.y = object->trans.y;
        sp14.z = object->trans.z;
        BoardPlayerIdleSet(lbl_1_bss_86);
        if (temp_r30->unk8 != 2) {
            object->func = NULL;
        }
        else {
            object->work[1] = 8;
            object->func = fn_1_5C84;
        }
    }
    BoardPlayerPosSetV(lbl_1_bss_86, &sp14);
}

void fn_1_5C84(omObjData *object)
{
    WorkMGCoin *sp8;
    sp8 = object->data;
    if (object->work[1] != 0) {
        if (--object->work[1] == 0) {
            BoardPlayerMotBlendSet(lbl_1_bss_86, 0, 15);
            object->func = NULL;
        }
        (void)object;
    }
    else {
        (void)object;
    }
}
