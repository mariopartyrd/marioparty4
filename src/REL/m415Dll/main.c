#include "REL/m415Dll.h"

#include "ext_math.h"
#include "game/EnvelopeExec.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/frand.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "math.h"
#include "version.h"

// bss
unkStruct5 lbl_1_bss_36C;
omObjData *lbl_1_bss_368;
omObjData *lbl_1_bss_364;
omObjData *lbl_1_bss_360;
omObjData *lbl_1_bss_35C;
omObjData *lbl_1_bss_34C[4];
u16 lbl_1_bss_34A;
s16 lbl_1_bss_348;
s16 lbl_1_bss_346;
s16 lbl_1_bss_344;
s16 lbl_1_bss_342;
s16 lbl_1_bss_33A[4];
s16 lbl_1_bss_338;
u8 *lbl_1_bss_334;
s32 lbl_1_bss_234[4][4][4];
void *lbl_1_bss_34[0x80];
s32 lbl_1_bss_2C[2];
unkStruct lbl_1_bss_4[4];
static s32 pad_05_00000000_bss;

// data
Vec lbl_1_data_0 = { 0.0f, 3000.0f, 2000.0f };
Vec lbl_1_data_C = { 0.0f, -0.7f, -0.6f };
GXColor lbl_1_data_18 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_1C = { 0.0f, 3000.0f, -2000.0f };
Vec lbl_1_data_28 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_34 = { 0.0f, 0.0f, 0.0f };

void ObjectSetup(void)
{
    s32 var_r31;
    Process *temp_r30;
    omObjData *var_r29;
    LightData *var_r28;
    s32 temp_r27;
    s32 var_r26;

    OSReport("******* M415ObjectSetup *********\n");
    Hu3DLighInit();
    var_r26 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_18);
    Hu3DGLightInfinitytSet(var_r26);
    var_r28 = &Hu3DGlobalLight[0];
    var_r28->unk_00 |= 0x8000;
    temp_r30 = omInitObjMan(0x32, 0x2000);
    temp_r27 = frand() & 0x1F;

    for (var_r31 = 0; var_r31 < temp_r27; var_r31++) {
        fn_1_679C();
    }

    CRot.x = -55.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 200.0f;
    CZoom = 1500.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, -1.0f, 5.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lbl_1_bss_364 = omAddObjEx(temp_r30, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_368 = omAddObjEx(temp_r30, 0x10, 8, 0, -1, fn_1_43C);
    lbl_1_bss_35C = omAddObjEx(temp_r30, 0x20, 0x10, 0, -1, fn_1_15D0);
    lbl_1_bss_360 = omAddObjEx(temp_r30, 0x50, 0x10, 0, -1, fn_1_2B18);
    omAddObjEx(temp_r30, 0x60, 0, 0, -1, fn_1_6304);
    omMakeGroupEx(temp_r30, 0, 4);
    omGetGroupMemberListEx(temp_r30, 0);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_34C[var_r31] = var_r29 = omAddObjEx(temp_r30, 0x30, 6, 0xA, 0, fn_1_3208);
        var_r29->work[0] = var_r31;
        var_r29->work[1] = var_r31;
    }
    Hu3DShadowCreate(30.0f, 100.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.4f);
    Hu3DShadowPosSet(&lbl_1_data_1C, &lbl_1_data_28, &lbl_1_data_34);
    omGameSysInit(temp_r30);
    HuAudSndGrpSet(0x28);
    fn_1_6368();
    fn_1_8780(0x40, 0x40);
}

void fn_1_43C(omObjData *object)
{
    CameraData *var_r31;

    var_r31 = &Hu3DCamera[0];
    lbl_1_bss_34A = 0;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    var_r31->fov = 45.0f;
    object->func = fn_1_4B0;
}

void fn_1_4B0(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    s32 var_r31;
    f32 var_f31;

    switch (lbl_1_bss_34A) {
        case 0:
            sp14.x = 0.0f;
            sp14.y = 200.0f;
            sp14.z = 200.0f;
            sp8.x = -55.0f;
            sp8.y = 0.0f;
            sp8.z = 0.0f;
            var_f31 = 1500.0f;
            fn_1_2E88(1.0f, &sp14, &sp8, var_f31);
            fn_1_A94C(0x2E000D, 0, 0);
            HuDataDirClose(0x2E000D);
            fn_1_A94C(0x2E000C, 0x40, 0x40);
            HuDataDirClose(0x2E000C);
            lbl_1_bss_342 = REFRESH_RATE * 2;
            HuAudFXPlay(0x5AE);
            lbl_1_bss_34A++;
            break;
        case 1:
            if (REFRESH_RATE_F * 1.2f == lbl_1_bss_342) {
                HuAudFXPlay(0x5AF);
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    omVibrate(var_r31, 0xC, 4, 2);
                }
            }
            if (--lbl_1_bss_342 == 0) {
                lbl_1_bss_34A++;
            }
            break;
        case 2:
            if (lbl_1_bss_342 == 0) {
                lbl_1_bss_342 = REFRESH_RATE * 1.5;
            }
            if (--lbl_1_bss_342 == 0) {
                lbl_1_bss_34A++;
            }
            break;
        case 3:
            lbl_1_bss_34A = 4;
            lbl_1_bss_348 = lbl_1_bss_346 = -1;
            object->func = fn_1_7D8;
            HuSprAnimRead(HuDataReadNum(0x2E000D, 0x10000000));
            break;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_14C0;
    }
}

extern s32 lbl_1_data_64 = -1;

void fn_1_7D8(omObjData *object)
{
    GXColor sp18[4] = { { 0xF0, 0x00, 0x00, 0xFF }, { 0x30, 0x60, 0xF0, 0xFF }, { 0xE0, 0xE0, 0x00, 0xFF }, { 0xFF, 0x80, 0x80, 0xFF } };
    s32 sp8[4];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    unkStruct2 *var_r25;
    s16 temp_r24;
    s16 temp_r23;
    s16 var_r22;

    switch (lbl_1_bss_34A) {
        case 4:
            if (lbl_1_bss_346 == -1) {
                lbl_1_bss_344 = 30 * REFRESH_RATE;
                lbl_1_bss_346 = MGSeqCreate(3, 0);
                MGSeqPosSet(lbl_1_bss_346, 320.0f, 240.0f);
            }
            else {
                if (MGSeqStatGet(lbl_1_bss_346) == 0) {
                    lbl_1_bss_346 = -1;
                    lbl_1_bss_34A++;
                    lbl_1_bss_342 = 0;
                    lbl_1_bss_348 = MGSeqCreate(1, lbl_1_bss_344 / REFRESH_RATE, -1, -1);
                }
            }
            if ((lbl_1_data_64 == -1) && ((MGSeqStatGet(lbl_1_bss_346) & 0x10) != 0)) {
                lbl_1_data_64 = HuAudSeqPlay(0x45);
            }
            break;
        case 5:
            var_r27 = 0;
            lbl_1_bss_344--;
            MGSeqParamSet(lbl_1_bss_348, 1, ((lbl_1_bss_344 + REFRESH_RATE - 1) / REFRESH_RATE));
            if (lbl_1_bss_344 == 0) {
                var_r27++;
            }
            if (var_r27 != 0) {
                lbl_1_bss_34A += 1;
            }
            break;
        case 6:
            if (lbl_1_bss_346 == -1) {
                lbl_1_bss_346 = MGSeqCreate(3, 1);
                MGSeqPosSet(lbl_1_bss_346, 320.0f, 240.0f);
                MGSeqParamSet(lbl_1_bss_348, 2, -1);
                HuAudSeqFadeOut(lbl_1_data_64, 0x64);
            }
            else if (MGSeqStatGet(lbl_1_bss_346) == 0) {
                lbl_1_bss_346 = -1;
                lbl_1_bss_34A++;
                lbl_1_bss_342 = 0;
            }
            break;
        case 7:
            if (lbl_1_bss_342 == 0) {
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    lbl_1_bss_4[var_r31].unk8 = espEntry(0x2E0010, 10, 0);
                    espColorSet(lbl_1_bss_4[var_r31].unk8, 0, 0, 0);
                    espTPLvlSet(lbl_1_bss_4[var_r31].unk8, 0.5f);
                    espPosSet(
                        lbl_1_bss_4[var_r31].unk8, 144.0f * (((var_r31 & 1) * 2) + 1), 120.0f * (((s16)(((var_r31 < 0) + var_r31) >> 1) << 1) + 1));
                    lbl_1_bss_4[var_r31].unk6 = espEntry(0x2E000F, 10, 0);
                    espPosSet(
                        lbl_1_bss_4[var_r31].unk6, 144.0f * (((var_r31 & 1) * 2) + 1), 120.0f * (((s16)(((var_r31 < 0) + var_r31) >> 1) << 1) + 1));
                    for (var_r30 = 0; var_r30 < 3; var_r30++) {
                        lbl_1_bss_4[var_r31].unk0[var_r30] = espEntry(0x2E0011, 10, 0);
                        espPosSet(lbl_1_bss_4[var_r31].unk0[var_r30], (32.0f * var_r30) + ((144.0f * (((var_r31 & 1) * 2) + 1)) - 32.0f),
                            (120.0f * (((s16)(((var_r31 < 0) + var_r31) >> 1) << 1) + 1)));
                        espColorSet(lbl_1_bss_4[var_r31].unk0[var_r30], sp18[var_r31].r, sp18[var_r31].g, sp18[var_r31].b);
                    }
                    espBankSet(lbl_1_bss_4[var_r31].unk0[2], 10);
                }
                lbl_1_bss_342 = REFRESH_RATE;
                HuAudFXPlay(0x5B4);
            }
            else {
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    for (var_r30 = 0; var_r30 < 2; var_r30++) {
                        espBankSet(lbl_1_bss_4[var_r31].unk0[var_r30], (s32)((fn_1_679C() / 65536.0f) * 10.0f));
                    }
                }
                if (--lbl_1_bss_342 == 0) {
                    HuAudFXPlay(0x5B5);
                    var_r28 = 6;
                    for (var_r29 = 0; var_r29 < 4; var_r29++) {
                        sp8[var_r29] = 0;
                        for (var_r31 = 0; var_r31 < 4; var_r31++) {
                            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                                sp8[var_r29] += lbl_1_bss_234[var_r29][var_r31][var_r30];
                            }
                        }
                        sp8[var_r29] = (0.99f + ((100.0f * sp8[var_r29]) / 360000.0f));
                        if (var_r28 < sp8[var_r29]) {
                            var_r28 = sp8[var_r29];
                        }
                    }
                    for (var_r31 = 0; var_r31 < 4; var_r31++) {
                        temp_r24 = sp8[var_r31];
                        espBankSet(lbl_1_bss_4[var_r31].unk0[0], temp_r24 / 10);
                        espBankSet(lbl_1_bss_4[var_r31].unk0[1], temp_r24 % 10);
                    }
                    for (var_r31 = 0; var_r31 < 4; var_r31++) {
                        lbl_1_bss_33A[var_r31] = -1;
                    }

                    var_r31 = 0;
                    var_r30 = 0;
                    for (; var_r31 < 4; var_r31++) {
                        if (sp8[var_r31] >= var_r28) {
                            var_r22 = GWPlayer[var_r31].coin_win;
                            temp_r23 = var_r22 + 10;
                            if (_CheckFlag(0x1000CU) == 0) {
                                GWPlayer[var_r31].coin_win = temp_r23;
                            }
                            lbl_1_bss_33A[var_r30++] = GWPlayerCfg[var_r31].character;
                            var_r25 = lbl_1_bss_34C[var_r31]->data;
                            var_r25->unkE = 1;
                        }
                    }
                    lbl_1_bss_342 = REFRESH_RATE;
                    lbl_1_bss_34A++;
                }
            }
            break;
        case 8:
            if (lbl_1_bss_346 == -1) {
                if (--lbl_1_bss_342 == 0) {
                    if (lbl_1_bss_33A[0] == -1) {
                        lbl_1_bss_346 = MGSeqCreate(3, 2);
                        HuAudSStreamPlay(4);
                    }
                    else {
                        lbl_1_bss_346 = MGSeqCreate(5, 3, lbl_1_bss_33A[0], lbl_1_bss_33A[1], lbl_1_bss_33A[2], lbl_1_bss_33A[3]);
                        HuAudSStreamPlay(1);
                    }
                    lbl_1_bss_346 = -1;
                    lbl_1_bss_34A++;
                    lbl_1_bss_342 = REFRESH_RATE * 3.5;
                }
            }
            break;
        case 9:
            if (--lbl_1_bss_342 == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                object->func = fn_1_14C0;
            }
            break;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_14C0;
    }
}

void fn_1_14C0(omObjData *object)
{
    if (WipeStatGet() == 0) {
        CharModelKill(-1);
        fn_1_B634();
        fn_1_64DC();
        MGSeqKill(lbl_1_bss_348);
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_1524(s16 arg0, char *arg1, f32 arg8, Mtx arg2)
{
    ModelData *temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if (temp_r31->unk_08 != -1) {
        Hu3DMotionExec(arg0, temp_r31->unk_08, arg8, 0);
    }
    if (temp_r31->unk_0C != -1) {
        Hu3DSubMotionExec(arg0);
    }
    if (temp_r31->hsfData->cenvCnt != 0) {
        EnvelopeProc(temp_r31->hsfData);
    }
    Hu3DModelObjMtxGet(arg0, arg1, arg2);
}

void fn_1_15D0(omObjData *object)
{
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    s32 var_r28;
    s32 var_r27;
    ModelData *var_r29;
    f32 temp_f31;
    s32 var_r31;

    object->model[0] = var_r31 = Hu3DModelCreateFile(0x2E0000);
    Hu3DModelShadowSet(var_r31);
    temp_f31 = Hu3DMotionMaxTimeGet(var_r31);
    fn_1_1524(var_r31, "oekaki", temp_f31, sp20);
    sp14.x = -sp20[0][3];
    sp14.y = -sp20[1][3];
    sp14.z = -sp20[2][3];
    fn_1_6A78(sp20, &sp8);
    sp8.x = -(sp8.x - 90.0f);
    sp8.y = -(sp8.y - 90.0f);
    sp8.z = -(sp8.z - 90.0f);
    Hu3DMotionTimeSet(var_r31, 0.0f);
    Hu3DMotionSpeedSet(var_r31, 2.0f);
    omSetTra(object, sp14.x, sp14.y, sp14.z);
    omSetRot(object, sp8.x, sp8.y, sp8.z);
    Hu3DModelPosSetV(var_r31, &sp14);
    Hu3DModelRotSetV(var_r31, &sp8);
    lbl_1_bss_338 = Hu3DAnimCreate(HuDataReadNum(0x2E000A, 0x10000000), var_r31, "dummy");
    var_r28 = 0x57E40;
    lbl_1_bss_334 = HuMemDirectMallocNum(HEAP_DATA, var_r28, MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_334, 0, var_r28);
    (void)var_r28;
    memset(&lbl_1_bss_234, 0, 0x100);
    var_r31 = fn_1_A2D0(1, 2);
    object->model[1] = var_r31;
    fn_1_AFC8(var_r31, 0, 0x2E000B, 0x200, 0x200);
    fn_1_B864(var_r31, 0.0f, -50.0f, 0.0f);
    fn_1_BB4C(var_r31, -90.0f, 0.0f, 0.0f);
    fn_1_BC9C(var_r31, 5.0f, 5.0f, 1.0f);
    fn_1_C2D0(var_r31, 0, 0);
    var_r27 = fn_1_66AC();
    object->model[2] = var_r27;
    fn_1_C81C(var_r27, 4);
    fn_1_B0B8(var_r31, 1, var_r27);
    var_r31 = Hu3DModelCreateFile(0x2E0002);
    object->model[3] = var_r31;
    Hu3DModelShadowSet(var_r31);
    Hu3DMotionSpeedSet(var_r31, 2.0f);
    object->func = fn_1_1960;
}

void fn_1_1960(omObjData *object)
{
    u32 temp_r29;
    AnimData **temp_r3;

    switch (lbl_1_bss_34A) {
        case 0:
            break;
        case 1:
            GXDrawDone();
            temp_r3 = fn_1_9734(object->model[2]);
            temp_r29 = Hu3DShadowData.unk_02 * Hu3DShadowData.unk_02;
            memcpy((*temp_r3)->bmp->data, OSCachedToUncached(Hu3DShadowData.unk_04), temp_r29);
            DCStoreRangeNoSync((*temp_r3)->bmp->data, temp_r29);
            break;
        case 2:
            Hu3DModelShadowMapObjSet(object->model[0], "kyanbasu");
            Hu3DModelShadowReset(object->model[0]);
            Hu3DModelShadowReset(object->model[3]);
            break;
        case 3:
        case 4:
        case 5:
            break;
    }
    return;
}

void fn_1_1A60(unkStruct3 *arg0)
{
    Mtx sp118;
    Mtx spE8;
    Vec spB8[4];
    Vec sp88[4];
    GXColor sp68[8] = { { 0xF0, 0x00, 0x00, 0xFF }, { 0x00, 0x00, 0xF0, 0xFF }, { 0xFF, 0x80, 0x80, 0xFF }, { 0x00, 0xFF, 0x00, 0xFF },
        { 0x80, 0x00, 0xC0, 0xFF }, { 0x80, 0x40, 0x00, 0xFF }, { 0xE0, 0xE0, 0x00, 0xFF }, { 0x00, 0x00, 0x00, 0xFF } };
    GXColor sp48[8] = { { 0xFF, 0x60, 0x60, 0xFF }, { 0x60, 0x60, 0xFF, 0xFF }, { 0xFF, 0xC0, 0xC0, 0xFF }, { 0x40, 0xFF, 0x40, 0xFF },
        { 0xC0, 0x40, 0xFF, 0xFF }, { 0xD0, 0x80, 0x40, 0xFF }, { 0xFF, 0xFF, 0x20, 0xFF }, { 0x80, 0x80, 0x80, 0xFF } };
    GXColor sp38[4] = { { 0xF0, 0x00, 0x00, 0xFF }, { 0x00, 0x00, 0xF0, 0xFF }, { 0xE0, 0xE0, 0x00, 0xFF }, { 0xFF, 0x80, 0x80, 0xFF } };
    GXColor sp28[4] = { { 0xFF, 0x60, 0x60, 0xFF }, { 0x60, 0x60, 0xFF, 0xFF }, { 0xFF, 0xFF, 0x20, 0xFF }, { 0xFF, 0xC0, 0xC0, 0xFF } };
    Vec sp1C;
    s32 sp18;
    s16 sp14;
    s16 sp12;
    s16 sp10;
    s16 spE;
    s16 spC;
    s16 spA;
    u8 sp8;
    f32 var_f31;
    f32 temp_f30;
    f32 var_f29;
    f32 var_f28;
    s32 var_r31;
    s16 var_r30;
    s32 var_r29;
    u8 temp_r28;
    s16 var_r27;
    s32 temp_r26;
    s16 var_r24;
    s16 var_r23;
    u16 *temp_r22;
    u8 temp_r21;
    AnimBmpData *var_r20;
    s16 temp_r19;
    s16 temp_r18;
    s32 temp_r17;

    sp1C = arg0->unk2C;
    temp_f30 = arg0->unk20;
    sp8 = arg0->unk1;
    temp_r28 = arg0->unk0;
    sp14 = 0.5f * (600.0f + sp1C.x);
    sp12 = 0.5f * (600.0f + sp1C.z);
    var_r20 = fn_1_668C(lbl_1_bss_338);
    temp_r22 = (u16 *)var_r20->data;
    var_r27 = 0x32;
    var_r30 = var_r27 >> 1;
    spC = 0x96;
    spA = 0;
    if ((s16)temp_f30 == ((s16)(temp_f30 / 90.0f) * 90)) {
        spB8[0].x = -var_r30;
        spB8[0].y = -var_r30;
        spB8[1].x = -var_r30;
        spB8[1].y = var_r30;
        spB8[2].x = var_r30;
        spB8[2].y = -var_r30;
        spB8[3].x = var_r30;
        spB8[3].y = var_r30;
        spB8[0].z = spB8[1].z = spB8[2].z = spB8[3].z = 0.0f;
    }
    else {
        spB8[0].x = var_r27;
        spB8[0].y = var_r27;
        spB8[1].x = var_r27;
        spB8[1].y = -var_r27;
        spB8[2].x = -var_r27;
        spB8[2].y = var_r27;
        spB8[3].x = -var_r27;
        spB8[3].y = -var_r27;
        spB8[0].z = spB8[1].z = spB8[2].z = spB8[3].z = 0.0f;
        for (var_r31 = -1; var_r31 < 2; var_r31 += 2) {
            for (var_r29 = -1; var_r29 < 2; var_r29 += 2) {
                MTXRotDeg(sp118, 0x59, temp_f30);
                MTXTrans(spE8, (var_r30 * var_r31), 0.0f, (var_r30 * var_r29));
                MTXConcat(sp118, spE8, spE8);
                if ((spB8[0].y > spE8[2][3]) || ((spB8[0].y == spE8[2][3]) && (spB8[0].x > spE8[0][3]))) {
                    spB8[0].x = spE8[0][3];
                    spB8[0].y = spE8[2][3];
                }
                if ((spB8[1].x > spE8[0][3]) || (spB8[1].x >= spE8[0][3]) && (spB8[1].y < spE8[2][3])) {
                    spB8[1].x = spE8[0][3];
                    spB8[1].y = spE8[2][3];
                }
                if ((spB8[2].x < spE8[0][3]) || (spB8[2].x <= spE8[0][3]) && (spB8[2].y > spE8[2][3])) {
                    spB8[2].x = spE8[0][3];
                    spB8[2].y = spE8[2][3];
                }
                if ((spB8[3].y <= spE8[2][3]) || (spB8[3].y <= spE8[2][3]) && (spB8[3].x < spE8[0][3])) {
                    spB8[3].x = spE8[0][3];
                    spB8[3].y = spE8[2][3];
                }
            }
        }
    }
    VECSubtract(&spB8[1], &spB8[0], &sp88[0]);
    VECSubtract(&spB8[2], &spB8[0], &sp88[1]);
    VECSubtract(&spB8[3], &spB8[1], &sp88[2]);
    VECSubtract(&spB8[3], &spB8[2], &sp88[3]);
    temp_r17 = (1.5 * (var_r30 * var_r30));
    for (var_r31 = spB8[0].y; var_r31 < spB8[3].y; var_r31++) {
        var_r23 = sp12 + var_r31;
        if (var_r23 >= 0 && (!(var_r23 >= 600.0f))) {
            temp_r18 = (var_r23 / 150.0f);
            if (var_r31 <= spB8[1].y) {
                var_f31 = ((var_r31 - spB8[0].y) / sp88[0].y);
                var_f29 = var_f31 * sp88[0].x + spB8[0].x;
            }
            else {
                var_f31 = ((var_r31 - spB8[1].y) / sp88[2].y);
                var_f29 = var_f31 * sp88[2].x + spB8[1].x;
            }
            if (var_r31 <= spB8[2].y) {
                var_f31 = ((var_r31 - spB8[0].y) / sp88[1].y);
                var_f28 = var_f31 * sp88[1].x + spB8[0].x;
            }
            else {
                var_f31 = ((var_r31 - spB8[2].y) / sp88[3].y);
                var_f28 = var_f31 * sp88[3].x + spB8[2].x;
            }

            for (var_r29 = var_f29; var_r29 < var_f28; var_r29++) {
                var_r24 = sp14 + var_r29;
                if (var_r24 >= 0 && (!(var_r24 >= 600.0f))) {
                    temp_r19 = (var_r24 / 150.0f);
                    temp_r26 = (600.0f * var_r23 + var_r24);
                    temp_r21 = lbl_1_bss_334[temp_r26];
                    lbl_1_bss_334[temp_r26] = temp_r28 + 1;
                    sp10 = (var_r24 >> 2);
                    spE = (var_r23 >> 2);
                    temp_r26 = ((var_r23 % 4) * 4) + ((sp10 * 0x10) + (var_r24 % 4) + spE * ((spC * 0x10) + (spA * 4)));
                    sp18 = ((fn_1_679C() / 65536.0f) * (1.0f + ((6.0f * (temp_r17 - ((var_r31 * var_r31) + (var_r29 * var_r29)))) / temp_r17)));
                    if (sp18 == 0) {
                        if (temp_r21 != (temp_r28 + 1)) {
                            temp_r22[temp_r26] = ((sp28[temp_r28].r >> 3) << 10) | ((sp28[temp_r28].g >> 3) << 5) | (sp28[temp_r28].b >> 3) | 0x8000;
                        }
                    }
                    else {
                        temp_r22[temp_r26] = ((sp38[temp_r28].r >> 3) << 10) | ((sp38[temp_r28].g >> 3) << 5) | (sp38[temp_r28].b >> 3) | 0x8000;
                    }
                    if (temp_r21 != (temp_r28 + 1)) {
                        lbl_1_bss_234[temp_r28][temp_r19][temp_r18]++;
                        if (temp_r21 != 0) {
                            lbl_1_bss_234[temp_r21 - 1][temp_r19][temp_r18]--;
                        }
                    }
                }
            }
        }
    }
    DCStoreRange(temp_r22, 0xAFC80);
}

void fn_1_2B18(omObjData *object)
{
    unkStruct4 *var_r31;

    var_r31 = fn_1_63A8(0x14C);
    object->data = var_r31;
    var_r31->unk148 = var_r31->unk144 = 0.0f;
    var_r31->unk140 = 1.0f;
    var_r31->unk10.x = var_r31->unk28.x = -55.0f;
    var_r31->unk10.y = var_r31->unk28.y = 0.0f;
    var_r31->unk10.z = var_r31->unk28.z = 0.0f;
    var_r31->unk4.x = var_r31->unk1C.x = 0.0f;
    var_r31->unk4.y = var_r31->unk1C.y = 200.0f;
    var_r31->unk4.z = var_r31->unk1C.z = 200.0f;
    var_r31->unk130 = var_r31->unk134 = 1500.0f;
    object->func = fn_1_2C14;
}

void fn_1_2C14(omObjData *object)
{
    f32 temp_f31;
    unkStruct4 *temp_r31;

    temp_r31 = (unkStruct4 *)object->data;
    if (temp_r31->unk148 > 0.0f) {
        temp_r31->unk148 -= temp_r31->unk140;
        temp_f31 = ((temp_r31->unk144 - temp_r31->unk148) / temp_r31->unk144);
        temp_f31 = sind(90.0f * temp_f31);
        if (temp_r31->unk0 == 0) {
            temp_r31->unk4.x = (temp_r31->unk1C.x + (temp_f31 * (temp_r31->unk34.x - temp_r31->unk1C.x)));
            temp_r31->unk4.y = (temp_r31->unk1C.y + (temp_f31 * (temp_r31->unk34.y - temp_r31->unk1C.y)));
            temp_r31->unk4.z = (temp_r31->unk1C.z + (temp_f31 * (temp_r31->unk34.z - temp_r31->unk1C.z)));
            temp_r31->unk10.x = (temp_r31->unk28.x + (temp_f31 * (temp_r31->unk40.x - temp_r31->unk28.x)));
            temp_r31->unk10.y = (temp_r31->unk28.y + (temp_f31 * (temp_r31->unk40.y - temp_r31->unk28.y)));
            temp_r31->unk10.z = (temp_r31->unk28.z + (temp_f31 * (temp_r31->unk40.z - temp_r31->unk28.z)));
            temp_r31->unk130 = (temp_r31->unk134 + (temp_f31 * (temp_r31->unk138 - temp_r31->unk134)));
        }
        else {
            fn_1_7A54(2.0f * temp_f31, &temp_r31->unk4, temp_r31->unkF4, temp_r31->unk64, temp_r31->unk88, 3);
            fn_1_7A54(2.0f * temp_f31, &temp_r31->unk10, temp_r31->unk100, temp_r31->unkAC, temp_r31->unkD0, 3);
            temp_r31->unk130 = fn_1_7520(2.0f * temp_f31, temp_r31->unk124, temp_r31->unk10C, temp_r31->unk118, 3);
        }
    }
    CRot.x = temp_r31->unk10.x;
    CRot.y = temp_r31->unk10.y;
    CRot.z = temp_r31->unk10.z;
    Center.x = temp_r31->unk4.x;
    Center.y = temp_r31->unk4.y;
    Center.z = temp_r31->unk4.z;
    CZoom = temp_r31->unk130;
}

void fn_1_2E88(f32 arg0, Vec *arg1, Vec *arg2, f32 arg3)
{
    unkStruct4 *temp_r31;

    temp_r31 = lbl_1_bss_360->data;
    temp_r31->unk0 = 0;
    temp_r31->unk144 = arg0;
    temp_r31->unk148 = arg0;
    temp_r31->unk1C = temp_r31->unk4;
    temp_r31->unk34.x = arg1->x;
    temp_r31->unk34.y = arg1->y;
    temp_r31->unk34.z = arg1->z;
    temp_r31->unk28 = temp_r31->unk10;
    temp_r31->unk40.x = arg2->x;
    temp_r31->unk40.y = arg2->y;
    temp_r31->unk40.z = arg2->z;
    temp_r31->unk134 = temp_r31->unk130;
    temp_r31->unk138 = arg3;
}

void fn_1_2F28(f32 arg8, Vec *arg0, Vec *arg1, f32 arg9, Vec *arg2, Vec *arg3, f32 argA)
{
    unkStruct4 *temp_r31;

    temp_r31 = lbl_1_bss_360->data;
    temp_r31->unk0 = 1;
    temp_r31->unk148 = temp_r31->unk144 = arg8;
    temp_r31->unk1C = temp_r31->unk4;
    temp_r31->unk34.x = arg0->x;
    temp_r31->unk34.y = arg0->y;
    temp_r31->unk34.z = arg0->z;
    temp_r31->unk4C.x = arg2->x;
    temp_r31->unk4C.y = arg2->y;
    temp_r31->unk4C.z = arg2->z;
    temp_r31->unk28 = temp_r31->unk10;
    temp_r31->unk40.x = arg1->x;
    temp_r31->unk40.y = arg1->y;
    temp_r31->unk40.z = arg1->z;
    temp_r31->unk58.x = arg3->x;
    temp_r31->unk58.y = arg3->y;
    temp_r31->unk58.z = arg3->z;
    temp_r31->unk134 = temp_r31->unk130;
    temp_r31->unk138 = arg9;
    temp_r31->unk13C = argA;
    temp_r31->unk64[0] = temp_r31->unk1C;
    temp_r31->unk64[1] = temp_r31->unk4C;
    temp_r31->unk64[2] = temp_r31->unk34;
    temp_r31->unkAC[0] = temp_r31->unk28;
    temp_r31->unkAC[1] = temp_r31->unk58;
    temp_r31->unkAC[2] = temp_r31->unk40;
    temp_r31->unk10C[0] = temp_r31->unk134;
    temp_r31->unk10C[1] = temp_r31->unk13C;
    temp_r31->unk10C[2] = temp_r31->unk138;
    temp_r31->unk124[0] = 0.0f;
    temp_r31->unk124[1] = ABS(temp_r31->unk10C[1] - temp_r31->unk10C[0]);
    temp_r31->unk124[2] = (temp_r31->unk124[1] + ABS(temp_r31->unk10C[2] - temp_r31->unk10C[1]));
    fn_1_7674(temp_r31->unkF4, temp_r31->unk64, temp_r31->unk88, 3);
    fn_1_7674(temp_r31->unk100, temp_r31->unkAC, temp_r31->unkD0, 3);
    fn_1_7268(temp_r31->unk124, temp_r31->unk10C, temp_r31->unk118, 3);
}

void fn_1_31E0(f32 arg8)
{
    unkStruct4 *data;

    data = (unkStruct4 *)lbl_1_bss_360->data;
    data->unk140 = arg8;
}

s32 lbl_1_data_80[10] = { 0, 3, 5, 6, 0x2E0012, 0x2E001A, 0x2E0022, 0x2E001A, 0x17, 0x72 };

Vec lbl_1_data_A8[4] = { { -200.0f, 1600.0f, -200.0f }, { 200.0f, 1600.0f, -200.0f }, { -200.0f, 1600.0f, 200.0f }, { 200.0f, 1600.0f, 200.0f } };

void fn_1_3208(omObjData *object)
{
    s32 var_r29;
    s32 var_r28;
    u32 temp_r27;
    unkStruct3 *var_r31;

    object->data = var_r31 = fn_1_63A8(0xA0);
    var_r31->unk0 = object->work[0];
    var_r31->unk1 = GWPlayerCfg[var_r31->unk0].character;
    var_r31->unk2 = (var_r31->unk0 >> 1);
    var_r31->unk3 = (var_r31->unk0 & 1);
    var_r31->unk4 = GWPlayerCfg[var_r31->unk0].pad_idx;
    var_r31->unk5 = GWPlayerCfg[var_r31->unk0].iscom;
    var_r31->unk6 = GWPlayerCfg[var_r31->unk0].diff;
    var_r31->unk18 = var_r31->unk1A = 4;
    var_r31->unk7 = 1;
    var_r31->unkC = 1;
    var_r31->unkD = 0;
    var_r31->unkA = 0;
    var_r31->unk5D = 0;
    var_r31->unk5C = 0;
    var_r31->unkE = 0;

    temp_r27 = object->work[1];
    var_r31->unk2C.x = lbl_1_data_A8[temp_r27].x;
    var_r31->unk2C.y = lbl_1_data_A8[temp_r27].y + (400.0f * ((fn_1_679C() - 0x8000) / 32768.0f));
    var_r31->unk2C.z = lbl_1_data_A8[temp_r27].z;
    var_r31->unk44.x = var_r31->unk44.y = var_r31->unk44.z = 0.0f;
    var_r31->unk38.x = var_r31->unk38.y = var_r31->unk38.z = 0.0f;
    var_r31->unk20 = var_r31->unk38.y;
    var_r31->unk24 = 0.0f;
    var_r31->unk1C = 0.0f;
    var_r31->unk28 = 1.0f;
    memset(&var_r31->unk60, 0, 0x40);
    var_r29 = CharModelCreate(var_r31->unk1, 4);
    object->model[0] = var_r29;
    Hu3DModelAttrSet(var_r29, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r29);

    for (var_r28 = 0; var_r28 < 10; var_r28++) {
        if ((lbl_1_data_80[var_r28] & 0xFFFF0000) != 0) {
            object->motion[var_r28] = CharModelMotionCreate(var_r31->unk1, var_r31->unk1 + lbl_1_data_80[var_r28]);
        }
        else {
            object->motion[var_r28] = CharModelMotionCreate(var_r31->unk1, lbl_1_data_80[var_r28]);
        }
    }
    CharModelMotionDataClose(var_r31->unk1);
    CharModelMotionSet(var_r31->unk1, object->motion[var_r31->unk18]);
    CharModelStepTypeSet(var_r31->unk1, 1);
    CharModelVoiceEnableSet(var_r31->unk1, object->motion[2], 0);
    object->model[2] = var_r29 = Hu3DModelCreateFile(var_r31->unk0 + 0x2E0003);
    object->model[3] = Hu3DJointMotion(var_r29, HuDataSelHeapReadNum(0x2E0007, 0x10000000, HEAP_DATA));
    object->model[4] = Hu3DJointMotion(var_r29, HuDataSelHeapReadNum(0x2E0008, 0x10000000, HEAP_DATA));
    object->model[5] = Hu3DJointMotion(var_r29, HuDataSelHeapReadNum(0x2E0009, 0x10000000, HEAP_DATA));
    Hu3DModelPosSet(var_r29, var_r31->unk2C.x, var_r31->unk2C.y, var_r31->unk2C.z);
    Hu3DModelHookSet(var_r29, "stamp00", object->model[0]);
    Hu3DMotionSet(object->model[2], object->model[4]);
    Hu3DModelShadowSet(var_r29);
    object->func = fn_1_3640;
}

void fn_1_3640(omObjData *object)
{
    s32 sp8;
    unkStruct3 *temp_r31;

    sp8 = object->model[0];
    temp_r31 = (unkStruct3 *)object->data;

    temp_r31->unk10 = temp_r31->unk12 = 0;
    temp_r31->unk14 = temp_r31->unk16 = 0;
    switch (lbl_1_bss_34A) {
        case 1:
            break;
        case 2:
            if (lbl_1_bss_342 == 0) {
                temp_r31->unk18 = 6;
                temp_r31->unk44.y = 0.0f;
                temp_r31->unkC = 0;
            }
            break;
        case 4:
            object->func = fn_1_3764;
            break;
    }
    if (temp_r31->unk2C.y < 0.0f) {
        omVibrate(temp_r31->unk0, 0xC, 6, 6);
        HuAudFXPlay(0x5B0);
        temp_r31->unk2C.y = 0.0f;
        temp_r31->unkC = 1;
    }
    fn_1_3B44(object);
}

void fn_1_3764(omObjData *object)
{
    s32 spC;
    s32 sp8;
    unkStruct3 *temp_r31;

    spC = object->model[0];
    temp_r31 = (unkStruct3 *)object->data;
    if (temp_r31->unk7 != 0) {
        if ((lbl_1_bss_34A == 5) && ((temp_r31->unk7 & 2) == 0)) {
            if (temp_r31->unk5 != 0) {
                fn_1_4660(object);
            }
            else {
                temp_r31->unk10 = HuPadStkX[temp_r31->unk4];
                temp_r31->unk12 = HuPadStkY[temp_r31->unk4];
                temp_r31->unk14 = HuPadBtnDown[temp_r31->unk4];
                temp_r31->unk16 = HuPadBtn[temp_r31->unk4];
            }
        }
        else {
            temp_r31->unk10 = temp_r31->unk12 = 0;
            temp_r31->unk14 = temp_r31->unk16 = 0;
        }
        switch (lbl_1_bss_34A) {
            case 4:
            case 5:
                break;
            case 6:
                if ((Hu3DModelAttrGet(object->model[2]) & 1) == 0) {
                    Hu3DModelHookReset(object->model[2]);
                    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
                    omSetTra(object, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
                    omSetRot(object, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
                    sp8 = fn_1_A2D0(1, 1);
                    fn_1_B038(lbl_1_bss_36C.unk36, 0, 0x2E000C);
                    fn_1_B8D0(lbl_1_bss_36C.unk36, lbl_1_bss_36C.unk38, temp_r31->unk2C.x, 50.0f + temp_r31->unk2C.y, temp_r31->unk2C.z);
                    fn_1_BD08(lbl_1_bss_36C.unk36, lbl_1_bss_36C.unk38, 3.0f, 3.0f, 1.0f);
                    fn_1_BE30(lbl_1_bss_36C.unk36, lbl_1_bss_36C.unk38, 0x80000000);
                    fn_1_C110(lbl_1_bss_36C.unk36, lbl_1_bss_36C.unk38, 0xFF, 0xFF, 0xFF, 0xFF);
                    fn_1_C410(lbl_1_bss_36C.unk36, lbl_1_bss_36C.unk38, lbl_1_bss_36C.unk3A, 0x11);
                    fn_1_C58C(lbl_1_bss_36C.unk36, lbl_1_bss_36C.unk38, lbl_1_bss_36C.unk3A, 0.5f);
                    if (temp_r31->unkC != 0) {
                        temp_r31->unkC = 0;
                        temp_r31->unkB = 1;
    #if VERSION_PAL // technically 1606.0f / REFRESH_RATE_F, but i can't get the float errors
                        temp_r31->unk44.y = 32.120003f;
    #else
                        temp_r31->unk44.y = 26.766666f;
    #endif
                    }
                    temp_r31->unk18 = 2;
                    temp_r31->unk2C.y += 100.65;
                }
                break;
            case 7:
                temp_r31->unk20 = fn_1_67F0(temp_r31->unk20, 0.0f, 0.9f);
                break;
            case 9:
                if (temp_r31->unkE != 0) {
                    temp_r31->unk18 = 8;
                }
                else {
                    temp_r31->unk18 = 9;
                }
                break;
        }
        if (temp_r31->unk2C.y <= 0.0f) {
            temp_r31->unk2C.y = 0.0f;
            temp_r31->unkC = 1;
        }
        fn_1_3B44(object);
    }
}

void fn_1_3B44(omObjData *object)
{
    s16 sp8;
    unkStruct3 *temp_r31;
    s16 var_r29;
    s16 var_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 var_r25;
    s16 temp_r24;
    s32 temp_r23;
    s32 var_r22;

    var_r25 = 0;
    temp_r23 = object->model[0];
    temp_r31 = (unkStruct3 *)object->data;
    temp_r27 = temp_r31->unk10;
    temp_r26 = temp_r31->unk12;
    sp8 = temp_r31->unk14;
    temp_r24 = temp_r31->unk16;
    temp_r31->unk50 = temp_r31->unk2C;
    var_r29 = temp_r31->unk18;
    var_r28 = 0;
    switch (temp_r31->unk18) {
        case 0:
            var_r28 = 1;
            break;
        case 1:
            if (temp_r31->unk1C > 0.1f) {
                var_r29 = 1;
                var_r28 = 1;
                temp_r31->unk20 = temp_r31->unk38.y;
                temp_r31->unk24++;
                if (temp_r31->unk24 >= (0.5f * temp_r31->unk28)) {
                    temp_r31->unk24 -= 0.5f * temp_r31->unk28;
                }
                temp_r31->unk1C *= 1.0 + (0.25 * cosd(90.0f * (temp_r31->unk24 / (0.5f * temp_r31->unk28))));
            }
            else {
                temp_r31->unk24 = 0.0f;
                temp_r31->unk1C = 0.0f;
                var_r29 = 0;
                var_r28 = 1;
            }
            break;
        case 2:
            temp_r31->unk44.y += -146.0f / REFRESH_RATE;
            if (temp_r31->unkC != 0) {
                var_r29 = 3;
                var_r28 = 0;
                temp_r31->unk44.y = 0.0f;
            }
            break;
        case 3:
            if (CharModelMotionEndCheck(temp_r31->unk1) != 0) {
                var_r29 = 0;
                var_r28 = 1;
            }
            break;
        case 4:
            temp_r31->unk44.y = -146.0f / REFRESH_RATE;
            if (FABS(temp_r27) + FABS(temp_r26) > 8) {
                temp_r31->unk20 = atan2d(temp_r27, -temp_r26);
            }
            if ((temp_r24 & 0x100) != 0) {
                temp_r31->unkB = 0U;
                var_r29 = 5;
                var_r28 = 0;
                var_r25 = 3;
                if (FABS(temp_r27) + FABS(temp_r26) > 8) {
                    temp_r31->unk20 = atan2d(temp_r27, -temp_r26);
                    temp_r31->unk1C = 6.0f;
                }
            }
            break;
        case 5:
            if (temp_r31->unkB < 0x20) {
                temp_r31->unkB++;
            }
            if (FABS(temp_r27) + FABS(temp_r26) > 8) {
                temp_r31->unk20 = atan2d(temp_r27, -temp_r26);
                temp_r31->unk1C = 6.0f;
            }
            else {
                temp_r31->unk1C = 0.0f;
            }
            if ((temp_r24 & 0x100) == 0) {
                temp_r31->unk44.y = (146.0f / REFRESH_RATE * (2.5f + (0.009f * temp_r31->unkB * temp_r31->unkB)));
                var_r29 = 6;
                var_r28 = 0;
                var_r25 = 4;
                if (temp_r31->unkB < 0xC) {
                    HuAudFXPlay(0x5B1);
                }
                else if (temp_r31->unkB < 0x18) {
                    HuAudFXPlay(0x5B2);
                }
                else {
                    HuAudFXPlay(0x5B3);
                }
            }
            break;
        case 6:
            if ((Hu3DMotionEndCheck(object->model[2]) == 0) && (Hu3DMotionShiftIDGet(object->model[2]) >= 0)) {
                temp_r31->unkC = 1;
            }
            else {
                if (temp_r31->unk44.y >= 0.0f) {
                    temp_r31->unkC = 0U;
                }
                temp_r31->unk44.y += -146.0f / REFRESH_RATE;
                if (temp_r31->unkC != 0) {
                    if ((temp_r24 & 0x100) != 0) {
                        var_r29 = 4;
                        var_r28 = 1;
                    }
                    else {
                        var_r29 = 7;
                        var_r28 = 0;
                    }
                    temp_r31->unk1C = 0.0f;
                    temp_r31->unk44.y = 0.0f;
                    var_r25 = 5;
                    fn_1_1A60(temp_r31);
                    var_r22 = fn_1_A2D0(0x28, 1);
                    fn_1_B038(var_r22, 0, 0x2E000D);
                    lbl_1_bss_36C.unk40[var_r22].unk30 = &fn_1_5B20;
                    fn_1_B864(var_r22, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
                    fn_1_C264(var_r22, 1);
                }
            }
            break;
        case 7:
            if ((temp_r24 & 0x100) != 0) {
                var_r29 = 4;
                var_r28 = 1;
            }
            else {
                if (Hu3DMotionTimeGet(temp_r23) <= 0.0f) {
                    var_r29 = 4;
                    var_r28 = 1;
                }
                else {
                    if ((Hu3DMotionTimeGet(temp_r23) >= 10.0f) && (Hu3DMotionShiftIDGet(temp_r23) < 0)) {
                        Hu3DModelAttrSet(temp_r23, HU3D_MOTATTR_REV);
                    }
                }
            }
            break;
        case 8:
        case 9:
            var_r28 = 0;
            temp_r31->unk44.y = -146.0f / REFRESH_RATE;
            break;
    }
    temp_r31->unk38.y = fn_1_67F0(temp_r31->unk38.y, temp_r31->unk20, 0.75f);
    temp_r31->unk44.x = (temp_r31->unk1C * sind(temp_r31->unk20));
    temp_r31->unk44.z = (temp_r31->unk1C * cosd(temp_r31->unk20));
    if ((temp_r31->unkC == 0) || (var_r29 == 1)) {
        temp_r31->unk2C.x += temp_r31->unk44.x;
        temp_r31->unk2C.y += temp_r31->unk44.y;
        temp_r31->unk2C.z += temp_r31->unk44.z;
    }
    temp_r31->unk18 = var_r29;
    if (var_r29 != temp_r31->unk1A) {
        temp_r31->unk1A = var_r29;
        CharModelMotionShiftSet(temp_r31->unk1, object->motion[temp_r31->unk18], 0.0f, 8.0f, var_r28);
        temp_r31->unk28 = CharModelMotionMaxTimeGet(temp_r31->unk1);
        if (var_r25 != 0) {
            Hu3DMotionShiftSet(object->model[2], object->model[var_r25], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
        }
    }
    if ((Hu3DModelAttrGet(object->model[2]) & 1) != 0) {
        omSetTra(object, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
        omSetRot(object, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
    }
    else {
        omSetTra(object, 0.0f, 0.0f, 0.0f);
        omSetRot(object, 0.0f, 0.0f, 0.0f);
        Hu3DModelPosSet(object->model[2], temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
        Hu3DModelRotSet(object->model[2], temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
    }
}

void fn_1_4660(omObjData *object)
{
    s16 sp3C[3][3];
    Vec sp30;
    Vec sp24;
    Vec sp18;
    s32 sp14;
    s32 sp10;
    s16 spC;
    f32 var_f31;
    f32 temp_f30;
    f32 var_f29;
    unkStruct3 *temp_r31;
    s32 var_r30;
    s32 var_r29;
    u8 temp_r28;
    u8 temp_r27;
    s32 var_r26;
    s32 var_r25;
    s16 var_r24;
    s16 var_r23;
    unkStruct3 *temp_r22;
    u8 var_r21;
    u8 var_r20;
    s16 var_r19;
    s16 var_r18;
    s16 temp_r17;

    temp_r31 = (unkStruct3 *)object->data;
    sp14 = object->model[0];
    spC = temp_r31->unk18;
    temp_r17 = temp_r31->unk6;
    var_r24 = var_r23 = var_r19 = var_r18 = 0;
    switch (temp_r31->unk5D) {
        case 0:
            temp_r28 = ((0.5f * (600.0f + temp_r31->unk2C.x)) / 150.0f);
            temp_r27 = ((0.5f * (600.0f + temp_r31->unk2C.z)) / 150.0f);
            if (lbl_1_bss_234[temp_r31->unk0][temp_r28][temp_r27] < 16875.0f) {
                temp_r31->unk60s = temp_r28;
                temp_r31->unk62s = temp_r27;
                temp_r31->unk5D++;
            }
            else {
                var_r26 = 0x57E4;
                for (var_r30 = temp_r28 - 1; var_r30 <= (temp_r28 + 1); var_r30++) {
                    if ((var_r30 >= 0) && (var_r30 < 4)) {
                        for (var_r29 = temp_r27 - 1; var_r29 <= (temp_r27 + 1); var_r29++) {
                            if ((var_r29 >= 0) && (var_r29 < 4) && (lbl_1_bss_234[temp_r31->unk0][var_r30][var_r29] <= var_r26)
                                && ((var_r26 != lbl_1_bss_234[temp_r31->unk0][var_r30][var_r29]) || ((fn_1_679C() & 1) == 0))) {

                                var_r21 = var_r30;
                                var_r20 = var_r29;
                                var_r26 = lbl_1_bss_234[temp_r31->unk0][var_r30][var_r29];
                            }
                        }
                    }
                }
                if (var_r26 < 16875.0f) {
                    temp_r31->unk60s = var_r21;
                    temp_r31->unk62s = var_r20;
                    temp_r31->unk5D++;
                }
                else {
                    var_r26 = 0x57E4;
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        for (var_r29 = 0; var_r29 < 4; var_r29++) {
                            if (lbl_1_bss_234[temp_r31->unk0][var_r30][var_r29] <= var_r26) {
                                var_r21 = var_r30;
                                var_r20 = var_r29;
                                var_r26 = lbl_1_bss_234[temp_r31->unk0][var_r30][var_r29];
                            }
                        }
                    }
                    temp_r31->unk60s = var_r21;
                    temp_r31->unk62s = var_r20;
                    temp_r31->unk5D++;
                }
            }
            break;
        case 1:
            var_f29 = 360000.0f;
            sp18 = temp_r31->unk2C;
            sp18.x += 50.0f * sind(temp_r31->unk38.y);
            sp18.z += 50.0f * cosd(temp_r31->unk38.y);

            for (var_r30 = 0; var_r30 < 3.0f; var_r30++) {
                for (var_r29 = 0; var_r29 < 3.0f; var_r29++) {
                    sp3C[var_r30][var_r29] = 0;
                }
            }

            for (var_r30 = 0; var_r30 < 150.0f; var_r30++) {
                for (var_r29 = 0; var_r29 < 150.0f; var_r29++) {
                    sp30.x = (150.0f * temp_r31->unk60s) + var_r30;
                    sp30.z = (150.0f * temp_r31->unk62s) + var_r29;
                    sp10 = (sp30.x + (600.0f * sp30.z));
                    if ((temp_r31->unk0 + 1) != lbl_1_bss_334[sp10]) {
                        sp3C[(s16)(var_r30 / 50.0f)][(s16)(var_r29 / 50.0f)]++;
                    }
                }
            }
            temp_r28 = (((0.5f * (600.0f + temp_r31->unk2C.x)) - (150.0f * temp_r31->unk60s)) / 50.0f);
            temp_r27 = (((0.5f * (600.0f + temp_r31->unk2C.x)) - (150.0f * temp_r31->unk62s)) / 50.0f);
            var_r25 = 0;
            for (var_r30 = temp_r28 - 1; var_r30 <= (temp_r28 + 1); var_r30++) {
                if (var_r30 >= 0) {
                    if (var_r30 >= 3.0f)
                        continue;
                    for (var_r29 = temp_r27 - 1; var_r29 <= (temp_r27 + 1); var_r29++) {
                        if (var_r29 >= 0) {
                            if (var_r29 >= 3.0f)
                                continue;
                            if (sp3C[var_r30][var_r29] < 1250.0f)
                                continue;
                            if (sp3C[var_r30][var_r29] < var_r25)
                                continue;
                            if ((var_r25 != sp3C[var_r30][var_r29]) || ((fn_1_679C() & 1) == 0)) {
                                var_r25 = sp3C[var_r30][var_r29];
                                sp30.x = 25.0f + ((150.0f * temp_r31->unk60s) + (50.0f * var_r30));
                                sp30.z = 25.0f + ((150.0f * temp_r31->unk62s) + (50.0f * var_r29));
                                sp30.x = (2.0f * sp30.x) - 600.0f;
                                sp30.z = (2.0f * sp30.z) - 600.0f;
                                sp30.y = 0.0f;
                                temp_r31->unk6C.x = sp30.x;
                                temp_r31->unk6C.y = sp30.y;
                                temp_r31->unk6C.z = sp30.z;
                            }
                        }
                    }
                }
            }
            if (var_r25 == 0) {
                var_r25 = 0;

                for (var_r30 = 0; var_r30 < 3.0f; var_r30++) {
                    for (var_r29 = 0; var_r29 < 3.0f; var_r29++) {
                        if (sp3C[var_r30][var_r29] >= var_r25) {
                            sp30.x = 25.0f + ((150.0f * temp_r31->unk60s) + (50.0f * var_r30));
                            sp30.z = 25.0f + ((150.0f * temp_r31->unk62s) + (50.0f * var_r29));
                            sp30.x = (2.0f * sp30.x) - 600.0f;
                            sp30.z = (2.0f * sp30.z) - 600.0f;
                            sp30.y = 0.0f;
                            VECSubtract(&sp18, &sp30, &sp24);
                            temp_f30 = VECMag(&sp24);
                            if ((var_r25 != sp3C[var_r30][var_r29]) || !(temp_f30 > var_f29)) {
                                if (!(temp_f30 > var_f29) || !(sp3C[var_r30][var_r29] < (1.5f * var_r25))) {
                                    temp_r31->unk6C.x = sp30.x;
                                    temp_r31->unk6C.y = sp30.y;
                                    temp_r31->unk6C.z = sp30.z;
                                    var_r25 = sp3C[var_r30][var_r29];
                                    var_f29 = temp_f30;
                                }
                            }
                        }
                    }
                }
            }
            temp_r31->unk64 = (1.0f + ((5 - temp_r17) * (fn_1_679C() / 65536.0f)));
            temp_r31->unk68 = (1.0f + ((0x32 - (temp_r17 * 0x10)) * (fn_1_679C() / 65536.0f)));
            temp_r31->unk5D++;
            break;
        case 2:
            if (--temp_r31->unk68 == 0) {
                VECSubtract(&temp_r31->unk6C, &temp_r31->unk2C, &sp24);
                VECNormalize(&sp24, &sp24);
                var_r24 = (32.0f * sp24.x);
                var_r23 = (32.0f * -sp24.z);
                var_r19 = var_r18 = 0x100;
                temp_r31->unk66 = 0x18 + (s32)(((20 - (temp_r17 * 6)) * ((fn_1_679C() - 0x8000) / 32768.0f)));
                temp_r31->unk5D++;
            }
            break;
        case 3:
            var_r24 = temp_r31->unk10;
            var_r23 = temp_r31->unk12;
            var_r19 = var_r18 = 0x100;
            if (--temp_r31->unk66 == 0) {
                temp_r31->unk5D++;
            }
            break;
        case 4:
            if (spC != 7) {
                var_r24 = temp_r31->unk10;
                var_r23 = temp_r31->unk12;
            }
            else {
                for (var_r30 = 0; var_r30 < 4; var_r30++) {
                    temp_r22 = lbl_1_bss_34C[var_r30]->data;
                    if (temp_r22 == temp_r31)
                        continue;
                    temp_r28 = ((0.5f * (600.0f + temp_r22->unk2C.x)) / 150.0f);
                    temp_r27 = ((0.5f * (600.0f + temp_r22->unk2C.z)) / 150.0f);
                    if (temp_r31->unk60s == temp_r28 && temp_r31->unk62s == temp_r27)
                        break;
                }
                if (var_r30 != 4) {
                    var_r26 = 0x57E4;
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        for (var_r29 = 0; var_r29 < 4; var_r29++) {
                            if ((lbl_1_bss_234[temp_r31->unk0][var_r30][var_r29] <= var_r26)
                                && ((temp_r31->unk60s != var_r30) || (temp_r31->unk62s != var_r29))) {
                                var_r21 = var_r30;
                                var_r20 = var_r29;
                                var_r26 = lbl_1_bss_234[temp_r31->unk0][var_r30][var_r29];
                            }
                        }
                    }
                    temp_r31->unk60s = var_r21;
                    temp_r31->unk62s = var_r20;
                    temp_r31->unk5D = 1;
                }
                else {
                    var_r24 = (32.0 * sind(temp_r31->unk38.y));
                    var_r23 = (32.0 * -cosd(temp_r31->unk38.y));
                    var_f31 = 517.5f;
                    if ((temp_r31->unk2C.x > var_f31) || (temp_r31->unk2C.x < -var_f31)) {
                        var_r24 = -var_r24;
                    }
                    var_f31 = 517.5f;
                    if ((temp_r31->unk2C.z > var_f31) || (temp_r31->unk2C.z < -var_f31)) {
                        var_r23 = -var_r23;
                    }
                    if (--temp_r31->unk64 != 0) {
                        var_r19 = var_r18 = 0x100;
                        temp_r31->unk66 = 0x18 + (s32)(((20 - (temp_r17 * 6)) * ((fn_1_679C() - 0x8000) / 32768.0f)));
                        temp_r31->unk5D = 3;
                    }
                    else {
                        temp_r28 = temp_r31->unk60s;
                        temp_r27 = temp_r31->unk62s;
                        if (lbl_1_bss_234[temp_r31->unk0][temp_r28][temp_r27] > 16875.0f) {
                            temp_r31->unk5D = 0;
                        }
                        else {
                            temp_r31->unk5D = 1;
                        }
                    }
                }
            }
            break;
    }
    temp_r31->unk10 = var_r24;
    temp_r31->unk12 = var_r23;
    temp_r31->unk14 = var_r19;
    temp_r31->unk16 = var_r18;
}

void fn_1_5B20(unkSubStruct2 *arg0)
{
    s16 sp8;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;
    s32 var_r29;
    unkSubStruct *var_r31;

    sp8 = 0;
    switch (arg0->unk60) {
        case 0:
            temp_f28 = 360.0f / arg0->unk2;
            var_r31 = arg0->unk3C;
            for (var_r29 = 0; var_r29 < arg0->unk2; var_r29++, var_r31++) {
                var_r31->unk68.x = sind(temp_f28 * var_r29) * (0.5f + (0.1f * (1.2f * ((fn_1_679C() - 0x8000) / 32768.0f))));
                var_r31->unk68.y = 0.0f;
                var_r31->unk68.z = cosd(temp_f28 * var_r29) * (0.5f + (0.1f * (1.2f * ((fn_1_679C() - 0x8000) / 32768.0f))));
                var_r31->unk0.x = 65.0f * var_r31->unk68.x;
                var_r31->unk0.y = 6.0f;
                var_r31->unk0.z = 65.0f * var_r31->unk68.z;
            }
            arg0->unk7Cs = REFRESH_RATE / 2;
            arg0->unk60++;
        case 1:
            arg0->unk7Cs--;
            temp_f31 = ((REFRESH_RATE_F / 2) - arg0->unk7Cs) / (REFRESH_RATE_F / 2);
            temp_f29 = arg0->unk7Cs / (REFRESH_RATE_F / 2);
            var_r31 = arg0->unk3C;
            for (var_r29 = 0; var_r29 < arg0->unk2; var_r29++, var_r31++) {
                var_r31->unk0.x += 5.0f * temp_f29 * var_r31->unk68.x;
                var_r31->unk0.z += 5.0f * temp_f29 * var_r31->unk68.z;
                temp_f30 = 0.4f + (1.2f * temp_f31);
                var_r31->unk18.x = temp_f30;
                var_r31->unk18.y = temp_f30;
                var_r31->unk18.z = temp_f30;
                var_r31->unk50.r = 0xFF;
                var_r31->unk50.g = 0xFF;
                var_r31->unk50.b = 0xFF;
                var_r31->unk50.a = 96.0f * (1.0f - (temp_f31 * temp_f31));
            }
            if (arg0->unk7Cs == 0) {
                arg0->unk60++;
            }
            break;
        case 2:
            fn_1_A800(arg0->unk0);
            return;
    }
}

void fn_1_5FB0(omObjData *arg0)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 temp_f31;
    f32 var_f30;
    f32 temp_f29;
    f32 var_f28;
    f32 temp_f27;
    s32 var_r29;
    unkStruct3 *temp_r30;
    unkStruct3 *temp_r31;

    temp_r31 = (unkStruct3 *)arg0->data;
    if (temp_r31->unk7 != 0) {
        VECSubtract(&temp_r31->unk2C, &temp_r31->unk50, &sp2C);
        var_f28 = VECMag(&sp2C);
        if (var_f28 != 0.0f) {
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                if (var_r29 != temp_r31->unk0) {
                    temp_r30 = (unkStruct3 *)lbl_1_bss_34C[var_r29]->data;
                    if (temp_r30->unk7 != 0) {
                        sp14.x = temp_r31->unk2C.x;
                        sp14.y = temp_r31->unk2C.y;
                        sp14.z = temp_r31->unk2C.z;
                        sp14.y = 0.0f;
                        sp8.x = temp_r30->unk2C.x;
                        sp8.y = temp_r30->unk2C.y;
                        sp8.z = temp_r30->unk2C.z;
                        sp8.y = 0.0f;
                        VECSubtract(&sp14, &sp8, &sp2C);
                        temp_f31 = VECMag(&sp2C);
                        if (temp_f31 >= 109.45f)
                            continue;
                        VECSubtract(&temp_r30->unk2C, &temp_r30->unk50, &sp2C);
                        temp_f27 = VECMag(&sp2C);
                        VECSubtract(&sp14, &sp8, &sp20);
                        VECNormalize(&sp20, &sp20);
                        temp_f31 = 110.0f - temp_f31;
                        temp_f29 = ((0.6f * temp_f27) + (0.4f * var_f28)) / (var_f28 + temp_f27);
                        temp_r31->unk2C.x += temp_f29 * (temp_f31 * sp20.x);
                        temp_r31->unk2C.y += temp_f29 * (temp_f31 * sp20.y);
                        temp_r31->unk2C.z += temp_f29 * (temp_f31 * sp20.z);
                        temp_f29 = ((0.6f * var_f28) + (0.4f * var_f28)) / (var_f28 + temp_f27);
                        temp_r30->unk2C.x += temp_f29 * (temp_f31 * -sp20.x);
                        temp_r30->unk2C.y += temp_f29 * (temp_f31 * -sp20.y);
                        temp_r30->unk2C.z += temp_f29 * (temp_f31 * -sp20.z);
                        fn_1_5FB0(lbl_1_bss_34C[var_r29]);
                    }
                }
            }
            var_f30 = 555.0f;
            if (temp_r31->unk2C.x > var_f30) {
                temp_r31->unk2C.x = var_f30;
            }
            if (temp_r31->unk2C.x < -var_f30) {
                temp_r31->unk2C.x = -var_f30;
            }

            var_f30 = 555.0f;
            if (temp_r31->unk2C.z > var_f30) {
                temp_r31->unk2C.z = var_f30;
            }
            if (temp_r31->unk2C.z < -var_f30) {
                temp_r31->unk2C.z = -var_f30;
            }
        }
    }
}

void fn_1_6304(omObjData *object)
{
    s32 var_r31;

    if (lbl_1_bss_34A >= 5) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            fn_1_5FB0(lbl_1_bss_34C[var_r31]);
        }
    }
}

void fn_1_6368(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x80; var_r31++) {
        lbl_1_bss_34[var_r31] = NULL;
    }
}

void *fn_1_63A8(s32 arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x80; var_r31++) {
        if (!lbl_1_bss_34[var_r31])
            break;
    }
    if (var_r31 == 0x80) {
        return NULL;
    }
    lbl_1_bss_34[var_r31] = HuMemDirectMallocNum(HEAP_SYSTEM, arg0, MEMORY_DEFAULT_NUM);
    return lbl_1_bss_34[var_r31];
}

void fn_1_6448(void *arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x80; var_r31++) {
        if (lbl_1_bss_34[var_r31] == arg0)
            break;
    }
    if (var_r31 != 0x80) {
        HuMemDirectFree(lbl_1_bss_34[var_r31]);
        lbl_1_bss_34[var_r31] = NULL;
    }
}

void fn_1_64DC(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x80; var_r31++) {
        if (lbl_1_bss_34[var_r31]) {
            OSReport("adr %x\n", lbl_1_bss_34[var_r31]);
            HuMemDirectFree(lbl_1_bss_34[var_r31]);
            lbl_1_bss_34[var_r31] = NULL;
        }
    }
}

void fn_1_6584(s16 arg0, char *arg1, u8 arg2, u8 arg3, u8 arg4)
{
    char sp13[0x100];
    HsfObject *var_r31;
    HsfMaterial *temp_r30;
    HsfData *temp_r29;
    HsfBuffer *temp_r28;
    HsfObject *var_r26;
    s32 var_r25;
    s32 var_r27;

    temp_r29 = Hu3DData[arg0].hsfData;
    var_r26 = temp_r29->object;
    strcpy(&sp13, MakeObjectName(arg1));

    for (var_r25 = 0; var_r25 < temp_r29->objectCnt; var_r25++, var_r26++) {
        var_r31 = var_r26;
        temp_r28 = var_r31->data.face;
        if (var_r31->constData && strcmp(&sp13, var_r31->name) == 0) {

            for (var_r27 = 0; var_r27 < temp_r28->count; var_r27++) {
                temp_r30 = &var_r31->data.material[((HsfFace *)temp_r28->data)[var_r27].mat & 0xFFF];
                temp_r30->color[0] = arg2;
                temp_r30->color[1] = arg3;
                temp_r30->color[2] = arg4;
            }
            return;
        }
    }
}

AnimBmpData *fn_1_668C(s16 arg0)
{
    return Hu3DTexAnimData[arg0].unk10->bmp;
}

s16 fn_1_66AC(void)
{
    AnimBmpData *temp_r31;
    s32 var_r30;
    AnimData **var_r29;
    s32 var_r28;

    var_r30 = fn_1_A94C(0xFFFF0000, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02);
    fn_1_ACF4(var_r30, 7, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02);
    var_r29 = fn_1_9734(var_r30);
    temp_r31 = (*var_r29)->bmp;
    var_r28 = temp_r31->sizeX * temp_r31->sizeY;
    memcpy(temp_r31->data, Hu3DShadowData.unk_04, var_r28);
    return var_r30;
}

u32 lbl_1_data_110 = 0x41C64E6D;

s32 fn_1_679C(void)
{
    lbl_1_data_110 *= 0x41C64E6D;
    lbl_1_data_110 += 0x3039;
    return lbl_1_data_110 >> 0x10;
}

f32 fn_1_67F0(f32 arg0, f32 arg1, f32 arg2)
{
    f32 var_f31;

    if (arg0 > 180.0f) {
        arg0 -= 360.0f;
    }
    else if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    }
    if (arg1 > 180.0f) {
        arg1 -= 360.0f;
    }
    else if (arg1 <= -180.0f) {
        arg1 += 360.0f;
    }
    var_f31 = arg0 - arg1;
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    else if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    }
    arg0 = arg1 + (var_f31 * arg2);
    if (arg0 > 180.0f) {
        return arg0 - 360.0f;
    }
    if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    }
    return arg0;
}

void fn_1_6958(Mtx arg0, f32 arg8, f32 arg9, f32 argA)
{
    Mtx sp38;
    Mtx sp8;

    if (argA != 0.0f) {
        MTXRotDeg(arg0, 0x5A, argA);
    }
    else {
        MTXIdentity(arg0);
    }
    if (arg8 != 0.0f) {
        MTXRotDeg(sp38, 0x58, arg8);
        MTXConcat(sp38, arg0, arg0);
    }
    if (arg9 != 0.0f) {
        MTXRotDeg(sp8, 0x59, arg9);
        MTXConcat(sp8, arg0, arg0);
    }
}

void fn_1_6A78(Mtx arg0, Vec *arg1)
{
    f32 temp_f29;
    f32 var_f28;

    arg1->x = atan2d(arg0[2][2], arg0[1][2]);
    arg1->z = atan2d(arg0[0][0], arg0[0][1]);
    temp_f29 = -arg0[0][2];
    var_f28 = sqrtf(ABS(1.0 - (temp_f29 * temp_f29)));
    if ((arg1->x > 90.0f) && (arg1->x < 270.0f) && (arg1->z > 90.0f) && (arg1->z < 270.0f)) {
        arg1->x = fmod((180.0f + arg1->x), 360.0);
        arg1->z = fmod((180.0f + arg1->z), 360.0);
        var_f28 = -var_f28;
    }
    arg1->y = atan2d(var_f28, temp_f29);
}

f32 fn_1_6D84(f32 arg8, f32 arg9, f32 argA, f32 argB)
{
    f32 temp_f31;
    f32 var_f30;

    temp_f31 = (1.0 - arg8);
    var_f30 = (argB * (arg8 * arg8)) + ((arg9 * (temp_f31 * temp_f31)) + (2.0 * (argA * (temp_f31 * arg8))));
    return var_f30;
}

void fn_1_6DFC(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg8)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        *arg3++ = fn_1_6D84(arg8, *arg0++, *arg1++, *arg2++);
    }
}

f32 fn_1_6F18(f32 arg8, f32 arg9, f32 argA, f32 argB)
{
    f32 var_f31;

    var_f31 = (2.0 * ((arg8 * argB) + (((arg8 - 1.0) * arg9) + ((1.0 - (2.0 * arg8)) * argA))));
    return var_f31;
}

void fn_1_6F90(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg8)
{
    f32 spC[3];
    f32 var_f29;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        spC[var_r31] = fn_1_6F18(arg8, *arg0++, *arg1++, *arg2++);
    }
    var_f29 = sqrtf((spC[2] * spC[2]) + ((spC[0] * spC[0]) + (spC[1] * spC[1])));
    if (var_f29) {
        var_f29 = (1.0 / var_f29);
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            *arg3++ = var_f29 * spC[var_r31];
        }
        return;
    }
    *arg3++ = 0.0f;
    *arg3++ = 0.0f;
    *arg3++ = 1.0f;
}

void fn_1_7268(f32 *arg0, f32 *arg1, f32 *arg2, s32 arg3)
{
    f32 sp48[0x10];
    f32 sp8[0x10];
    f32 temp_f31;
    s32 var_r31;

    arg2[0] = 0.0f;
    arg2[arg3 - 1] = 0.0f;

    for (var_r31 = 0; var_r31 < arg3 - 1; var_r31++) {
        sp48[var_r31] = arg0[var_r31 + 1] - arg0[var_r31];
        if (sp48[var_r31] == 0.0f) {
            sp8[var_r31 + 1] = 0.0f;
        }
        else {
            sp8[var_r31 + 1] = (arg1[var_r31 + 1] - arg1[var_r31]) / sp48[var_r31];
        }
    }
    arg2[1] = (sp8[2] - sp8[1]);
    sp8[1] = 2.0f * (arg0[2] - arg0[0]);

    for (var_r31 = 1; var_r31 < arg3 - 2; var_r31++) {
        temp_f31 = sp48[var_r31] / sp8[var_r31];
        arg2[var_r31 + 1] = ((sp8[var_r31 + 2] - sp8[var_r31 + 1]) - (temp_f31 * (f64)arg2[var_r31]));
        sp8[var_r31 + 1] = ((2.0f * (arg0[var_r31 + 2] - arg0[var_r31])) - (temp_f31 * (f64)sp48[var_r31]));
    }

    arg2[arg3 - 2] -= sp48[arg3 - 2] * arg2[arg3 - 1];

    for (var_r31 = arg3 - 2; var_r31 > 0; var_r31--) {
        if (0.0f == sp8[var_r31]) {
            arg2[var_r31] = 0.0f;
        }
        else {
            arg2[var_r31] = (arg2[var_r31] - (sp48[var_r31] * arg2[var_r31 + 1])) / sp8[var_r31];
        }
    }
}

f32 fn_1_7520(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, s32 arg4)
{
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f29;
    s32 temp_r31;

    temp_r31 = (s32)arg0;
    arg0 -= temp_r31;
    temp_f31 = arg1[temp_r31 + 1] - arg1[temp_r31];
    temp_f30 = temp_f31 * arg0;
    var_f29 = arg2[temp_r31]
        + (temp_f30
            * ((temp_f30 * ((3.0f * arg3[temp_r31]) + ((temp_f30 * (arg3[temp_r31 + 1] - arg3[temp_r31])) / temp_f31)))
                + (((arg2[temp_r31 + 1] - arg2[temp_r31]) / temp_f31) - (temp_f31 * (2.0f * arg3[temp_r31] + arg3[temp_r31 + 1])))));
    if (temp_f31 == 0.0f) {
        var_f29 = arg2[temp_r31];
    }
    return var_f29;
}

void fn_1_7674(f32 *arg0, Vec *arg1, Vec *arg2, s32 arg3)
{
    f32 spD4[0x10];
    f32 sp94[0x10];
    f32 sp54[0x10];
    f32 sp14[0x10];
    Vec sp8;
    f32 temp_f31;
    s32 var_r27;
    s32 var_r30;
    s32 var_r31;

    arg0[0] = 0.0f;

    for (var_r30 = 1; var_r30 < arg3; var_r30++) {
        VECSubtract(&arg1[var_r30], &arg1[var_r30 - 1], &sp8);
        arg0[var_r30] = arg0[var_r30 - 1] + VECMag(&sp8);
    }

    for (var_r27 = 0; var_r27 < 3; var_r27++) {
        for (var_r30 = 0; var_r30 < arg3; var_r30++) {
            spD4[var_r30] = ((f32(*)[3])arg1)[var_r30][var_r27];
        }
        sp94[0] = 0.0f;
        sp94[arg3 - 1] = 0.0f;

        for (var_r31 = 0; var_r31 < (arg3 - 1); var_r31++) {
            sp14[var_r31] = arg0[var_r31 + 1] - arg0[var_r31];
            if (sp14[var_r31] == 0.0f) {
                sp54[var_r31 + 1] = 0.0f;
            }
            else {
                sp54[var_r31 + 1] = (spD4[var_r31 + 1] - spD4[var_r31]) / sp14[var_r31];
            }
        }
        sp94[1] = sp54[2] - sp54[1];
        sp54[1] = 2.0f * (arg0[2] - arg0[0]);

        for (var_r31 = 1; var_r31 < (arg3 - 2); var_r31++) {
            temp_f31 = sp14[var_r31] / sp54[var_r31];
            sp94[var_r31 + 1] = ((sp54[var_r31 + 2] - sp54[var_r31 + 1]) - (temp_f31 * (f64)sp94[var_r31]));
            sp54[var_r31 + 1] = ((2.0f * (arg0[var_r31 + 2] - arg0[var_r31])) - (temp_f31 * (f64)sp14[var_r31]));
        }
        sp94[arg3 - 2] -= sp14[arg3 - 2] * sp94[arg3 - 1];
        for (var_r31 = arg3 - 2; var_r31 > 0; var_r31--) {
            if (sp54[var_r31] == 0.0f) {
                sp94[var_r31] = 0.0f;
            }
            else {
                sp94[var_r31] = (sp94[var_r31] - (sp14[var_r31] * sp94[var_r31 + 1])) / sp54[var_r31];
            }
        }

        for (var_r30 = 0; var_r30 < arg3; var_r30++) {
            ((f32(*)[3])arg2)[var_r30][var_r27] = sp94[var_r30];
            (void)arg2;
        }
    }
}

void fn_1_7A54(f32 arg0, Vec *arg1, f32 *arg2, Vec *arg3, Vec *arg4, s32 arg5)
{
    f32 sp48[0x10];
    f32 sp8[0x10];
    f32 temp_f29;
    f32 temp_f31;
    f32 var_f28;
    s32 temp_r31;
    s32 var_r29;
    s32 var_r30;

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        for (var_r30 = 0; var_r30 < arg5; var_r30++) {
            sp48[var_r30] = ((f32(*)[3])arg3)[var_r30][var_r29];
            sp8[var_r30] = ((f32(*)[3])arg4)[var_r30][var_r29];
        }

        ((f32(*)[3])arg1)[0][var_r29] = fn_1_7520(arg0, arg2, sp48, sp8, 0);
    }
}

f32 fn_1_7C68(Vec *arg0)
{
    f32 temp_f29;
    f32 temp_f30;

    temp_f30 = (arg0->z * arg0->z) + ((arg0->x * arg0->x) + (arg0->y * arg0->y));
    temp_f30 = sqrtf(temp_f30);

    if (temp_f30 != 0.0f) {
        temp_f29 = 1.0f / temp_f30;
        arg0->x *= temp_f29;
        arg0->y *= temp_f29;
        arg0->z *= temp_f29;
    }
    else {
        arg0->x = arg0->y = arg0->z = 0.0f;
    }
    return temp_f30;
}

f32 fn_1_7E00(Vec arg0, Vec arg1, Vec *arg2, f32 arg8)
{
    if (arg8 <= 0.0f) {
        arg2->x = arg0.x;
        arg2->y = arg0.y;
        arg2->z = arg0.z;
        arg8 = 0.0f;
    }
    else if (arg8 >= 1.0f) {
        arg2->x = arg0.x + arg1.x;
        arg2->y = arg0.y + arg1.y;
        arg2->z = arg0.z + arg1.z;
        arg8 = 1.0f;
    }
    else {
        arg2->x = arg0.x + (arg8 * arg1.x);
        arg2->y = arg0.y + (arg8 * arg1.y);
        arg2->z = arg0.z + (arg8 * arg1.z);
    }
    return arg8;
}

f32 fn_1_7ED8(Vec arg0, Vec arg1, Vec arg2)
{
    f32 temp_f30;
    f32 var_f31;

    var_f31 = (arg2.z * (arg1.z - arg0.z)) + ((arg2.x * (arg1.x - arg0.x)) + (arg2.y * (arg1.y - arg0.y)));
    temp_f30 = -((arg2.z * arg2.z) + ((arg2.x * arg2.x) + (arg2.y * arg2.y)));
    if (temp_f30 != 0.0f) {
        var_f31 /= temp_f30;
    }
    return var_f31;
}

f32 fn_1_7F94(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Vec sp44;
    f32 var_f30;

    if (0.0f == ((arg2->z * arg2->z) + ((arg2->x * arg2->x) + (arg2->y * arg2->y)))) {
        return ((arg0->z - arg1->z) * (arg0->z - arg1->z))
            + (((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)));
    }

    var_f30 = fn_1_7ED8(*arg0, *arg1, *arg2);
    fn_1_7E00(*arg1, *arg2, &sp44, var_f30);
    return ((arg0->z - sp44.z) * (arg0->z - sp44.z)) + (((arg0->x - sp44.x) * (arg0->x - sp44.x)) + ((arg0->y - sp44.y) * (arg0->y - sp44.y)));
}

f32 fn_1_82D0(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4)
{
    f32 var_f31;
    f32 var_f30;

    if (0.0f == ((arg2->z * arg2->z) + ((arg2->x * arg2->x) + (arg2->y * arg2->y)))) {
        return ((arg0->z - arg1->z) * (arg0->z - arg1->z))
            + (((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)));
    }
    else {
        var_f30 = fn_1_7ED8(*arg0, *arg1, *arg2);
        fn_1_7E00(*arg1, *arg2, arg3, var_f30);
    }

    arg4->x = arg3->x - arg0->x;
    arg4->y = arg3->y - arg0->y;
    arg4->z = arg3->z - arg0->z;

    return fn_1_7C68(arg4);
}
