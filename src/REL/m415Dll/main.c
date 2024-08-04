#include "REL/m415Dll.h"

#include "rel_sqrt_consts.h"
#include "game/audio.h"
#include "game/EnvelopeExec.h"
#include "game/esprite.h"
#include "game/frand.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/sprite.h"
#include "game/wipe.h"

// bss
omObjData* lbl_1_bss_368;
omObjData* lbl_1_bss_364;
omObjData* lbl_1_bss_360;
omObjData* lbl_1_bss_35C;
omObjData* lbl_1_bss_34C[4];
u16 lbl_1_bss_34A;
s16 lbl_1_bss_348;
s16 lbl_1_bss_346;
s16 lbl_1_bss_344;
s16 lbl_1_bss_342;
s16 lbl_1_bss_33A[4];
s16 lbl_1_bss_338;
s32 (*lbl_1_bss_334)[4][4];
s32 lbl_1_bss_234[4][4][4];
unkStruct lbl_1_bss_4[4];

// data
Vec lbl_1_data_0 = { 0.0f, 3000.0f, 2000.0f };
Vec lbl_1_data_C = { 0.0f, -0.7f, -0.6f };
GXColor lbl_1_data_18 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_1C = { 0.0f, 3000.0f, -2000.0f };
Vec lbl_1_data_28 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_34 = { 0.0f, 0.0f, 0.0f };

void ObjectSetup(void) {
    s32 var_r31;
    Process* temp_r30;
    omObjData* var_r29;
    LightData* var_r28;
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

void fn_1_43C(omObjData* object) {
    CameraData* var_r31;

    var_r31 = &Hu3DCamera[0];
    lbl_1_bss_34A = 0;
    WipeCreate(1, 0, 0x3C);
    var_r31->fov = 45.0f;
    object->func = fn_1_4B0;
}

void fn_1_4B0(omObjData* object) {
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
            var_f31 = 1.0f;
            fn_1_2E88(1500.0f, &sp14, &sp8, var_f31);
            fn_1_A94C(0x2E000D, 0, 0);
            HuDataDirClose(0x2E000D);
            fn_1_A94C(0x2E000C, 0x40, 0x40);
            HuDataDirClose(0x2E000C);
            lbl_1_bss_342 = 0x78;
            HuAudFXPlay(0x5AE);
            lbl_1_bss_34A++;
            break;
        case 1:
            if (72.0f == lbl_1_bss_342) {
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
                lbl_1_bss_342 = 90;
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
        WipeCreate(2, 0, 0x3C);
        object->func = fn_1_14C0;
    }
}

extern s32 lbl_1_data_64 = -1;

void fn_1_7D8(omObjData* object) {
    GXColor sp18[4] = {
        { 0xF0, 0x00, 0x00, 0xFF },
        { 0x30, 0x60, 0xF0, 0xFF },
        { 0xE0, 0xE0, 0x00, 0xFF },
        { 0xFF, 0x80, 0x80, 0xFF }
    };
    s32 sp8[4];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    unkStruct2* var_r25;
    s16 temp_r24;
    s16 temp_r23;
    s16 var_r22;

    switch (lbl_1_bss_34A) {
        case 4:
            if (lbl_1_bss_346 == -1) {
                lbl_1_bss_344 = 0x708;
                lbl_1_bss_346 = MGSeqCreate(3, 0);
                MGSeqPosSet(lbl_1_bss_346, 320.0f, 240.0f);
            } else {
                if (MGSeqStatGet(lbl_1_bss_346) == 0) {
                    lbl_1_bss_346 = -1;
                    lbl_1_bss_34A++;
                    lbl_1_bss_342 = 0;
                    lbl_1_bss_348 = MGSeqCreate(1, lbl_1_bss_344 / 60, -1, -1);
                }
            }
            if ((lbl_1_data_64 == -1) && ((MGSeqStatGet(lbl_1_bss_346) & 0x10) != 0)) {
                lbl_1_data_64 = HuAudSeqPlay(0x45);
            }
            break;
        case 5:
            var_r27 = 0;
            lbl_1_bss_344--;
            MGSeqParamSet(lbl_1_bss_348, 1, ((lbl_1_bss_344 + 0x3B) / 60));
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
            } else if (MGSeqStatGet(lbl_1_bss_346) == 0) {
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
                    espPosSet(lbl_1_bss_4[var_r31].unk8,
                        144.0f * (((var_r31 & 1) * 2) + 1),
                        120.0f * (((s16)(((var_r31 < 0) + var_r31) >> 1) << 1) + 1)
                    );
                    lbl_1_bss_4[var_r31].unk6 = espEntry(0x2E000F, 10, 0);
                    espPosSet(lbl_1_bss_4[var_r31].unk6,
                        144.0f * (((var_r31 & 1) * 2) + 1),
                        120.0f * (((s16)(((var_r31 < 0) + var_r31) >> 1) << 1) + 1)
                    );
                    for (var_r30 = 0; var_r30 < 3; var_r30++) {
                        lbl_1_bss_4[var_r31].unk0[var_r30] = espEntry(0x2E0011, 10, 0);
                        espPosSet(lbl_1_bss_4[var_r31].unk0[var_r30],
                            (32.0f * var_r30) + ((144.0f * (((var_r31 & 1) * 2) + 1)) - 32.0f),
                            (120.0f * (((s16)(((var_r31 < 0) + var_r31) >> 1) << 1) + 1))
                        );
                        espColorSet(lbl_1_bss_4[var_r31].unk0[var_r30], sp18[var_r31].r, sp18[var_r31].g, sp18[var_r31].b);
                    }
                    espBankSet(lbl_1_bss_4[var_r31].unk0[2], 10);
                }
                lbl_1_bss_342 = 0x3C;
                HuAudFXPlay(0x5B4);
            } else {
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
                    for (;var_r31 < 4; var_r31++) {
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
                    lbl_1_bss_342 = 0x3C;
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
                    } else {
                        lbl_1_bss_346 = MGSeqCreate(5, 3, lbl_1_bss_33A[0], lbl_1_bss_33A[1], lbl_1_bss_33A[2], lbl_1_bss_33A[3]);
                        HuAudSStreamPlay(1);
                    }
                    lbl_1_bss_346 = -1;
                    lbl_1_bss_34A++;
                    lbl_1_bss_342 = 0xD2;
                }
            }
            break;
        case 9:
            if (--lbl_1_bss_342 == 0) {
                WipeCreate(2, 0, 0x3C);
                object->func = fn_1_14C0;
            }
            break;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(2, 0, 0x3C);
        object->func = fn_1_14C0;
    }
}

void fn_1_14C0(omObjData* object) {
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

void fn_1_1524(s16 arg0, char* arg1, f32 arg8, Mtx arg2) {
    ModelData* temp_r31;

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

void fn_1_15D0(omObjData* object) {
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    s32 var_r28;
    s32 var_r27;
    ModelData* var_r29;
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
    lbl_1_bss_334 = HuMemDirectMallocNum(HEAP_DATA, var_r28, 0x10000000);
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

void fn_1_1960(omObjData* object) {
    u32 temp_r29;
    AnimData** temp_r3;

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

void fn_1_1A60(void* arg0) {
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    Vec spAC;
    Vec spA0;
    Vec sp94;
    Vec sp88;
    GXColor sp68[8] = {
        { 0xF0, 0x00, 0x00, 0xFF },
        { 0x00, 0x00, 0xF0, 0xFF },
        { 0xFF, 0x80, 0x80, 0xFF },
        { 0x00, 0xFF, 0x00, 0xFF },
        { 0x80, 0x00, 0xC0, 0xFF },
        { 0x80, 0x40, 0x00, 0xFF },
        { 0xE0, 0xE0, 0x00, 0xFF },
        { 0x00, 0x00, 0x00, 0xFF }
    };
    GXColor sp48[8] = {
        { 0xFF, 0x60, 0x60, 0xFF },
        { 0x60, 0x60, 0xFF, 0xFF },
        { 0xFF, 0xC0, 0xC0, 0xFF },
        { 0x40, 0xFF, 0x40, 0xFF },
        { 0xC0, 0x40, 0xFF, 0xFF },
        { 0xD0, 0x80, 0x40, 0xFF },
        { 0xFF, 0xFF, 0x20, 0xFF },
        { 0x80, 0x80, 0x80, 0xFF }
    };
    GXColor sp38[4] = {
        { 0xF0, 0x00, 0x00, 0xFF },
        { 0x00, 0x00, 0xF0, 0xFF },
        { 0xE0, 0xE0, 0x00, 0xFF },
        { 0xFF, 0x80, 0x80, 0xFF }
    };
    GXColor sp28[4] = {
        { 0xFF, 0x60, 0x60, 0xFF },
        { 0x60, 0x60, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0x20, 0xFF },
        { 0xFF, 0xC0, 0xC0, 0xFF }
    };
    f32 sp24;
    s32 sp20;
    f32 sp1C;
    s32 sp18;
    s16 sp14;
    s16 sp12;
    s16 sp10;
    s16 spE;
    s16 spC;
    s16 spA;
    u8 sp8;
    f32 temp_f2;
    f32 temp_f30;
    f32 var_f28;
    f32 var_f29;
    s16 temp_r18;
    s16 temp_r19;
    s16 temp_r3;
    s16 temp_r4;
    s32 temp_r0;
    s32 temp_r17;
    s32 temp_r26;
    s32 temp_r26_2;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r4_4;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    s32 temp_r8;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r31;
    s32 var_r31_2;
    s32* temp_r3_6;
    s32* temp_r4_5;
    u32 temp_r3_2;
    u32 temp_r3_3;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u8 temp_r21;
    u8 temp_r28;
    void* temp_r22;

}