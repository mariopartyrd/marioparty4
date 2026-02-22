#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXVert.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/init.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "string.h"

#include "REL/m428Dll.h"

#ifndef __MWERKS__
#include "game/ClusterExec.h"
#include "game/EnvelopeExec.h"
#include "game/ShapeExec.h"
#include "game/frand.h"
#endif

typedef struct M428DllData0Struct {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ float unk_18;
} M428DllData0Struct; /* size = 0x1C */

typedef struct M428DllUnkStruct2 {
    s16 unk_00[0x10];
    float unk_20[0x10];
    s32 unk_60;
} M428DllUnkStruct2; /* size = 0x64 */

typedef struct M428DllUnkStruct {
    M428DllUnkStruct2 unk_00[0x10];
    ShadowData unk_640[0x10];
    ShadowData unk_FC0;
} M428DllUnkStruct; /* size = 0x1058 */

void fn_1_478(omObjData *);
void fn_1_25CC(omObjData *object);
void fn_1_261C(omObjData *arg0);
void fn_1_29E8(omObjData *object);
void fn_1_2ACC(s32 arg0);
void fn_1_2B8(omObjData *object);
void fn_1_2C90(ModelData *, float[3][4]);
void fn_1_2E2C(s32 arg0);
void fn_1_40A4(void);

M428DllData0Struct lbl_1_data_0[3] = {
    { 65.0f, 0.0f, 0.0f, 0.0f, 400.0f, 0.0f, 2000.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f, 400.0f, 0.0f, 2000.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f, 400.0f, 0.0f, 1575.0f },
};

Vec lbl_1_data_54 = { -1000.0f, 2000.0f, 1000.0f };
Vec lbl_1_data_60 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_6C = { 0.0f, 0.0f, -450.0f };

Process *lbl_1_bss_88;
s32 lbl_1_bss_84;
s32 lbl_1_bss_80;
u32 lbl_1_bss_7C;
s32 lbl_1_bss_78;
s32 lbl_1_bss_74;
s32 lbl_1_bss_70;
s32 lbl_1_bss_6C;
s32 lbl_1_bss_68;
s32 lbl_1_bss_64;
s32 lbl_1_bss_60;
float lbl_1_bss_58[2];
s16 lbl_1_bss_50[4];
s16 lbl_1_bss_48[4];
s32 lbl_1_bss_38[4];
float lbl_1_bss_28[4];
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
omObjData *lbl_1_bss_1C;
s32 lbl_1_bss_18;
omObjData *lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
char lbl_1_bss_4[8];
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    s32 var_r31;
    Process *var_r30;
    s32 var_r29;

    OSReport("******* M428ObjectSetup *********\n");
    var_r30 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_88 = var_r30;
    omGameSysInit(var_r30);
    Hu3DLightAllKill();
    Hu3DLighInit();
    lbl_1_bss_1C = omAddObjEx(var_r30, 0xFF, 2, 0, -1, fn_1_2B8);
    lbl_1_bss_84 = lbl_1_bss_80 = -1;
    HuAudSndGrpSet(0x35);
    lbl_1_bss_7C = 0;
    lbl_1_bss_78 = 0;
    lbl_1_bss_68 = 0;
    lbl_1_bss_64 = -1;
    lbl_1_bss_60 = 0;
    lbl_1_bss_24 = -1;
    lbl_1_bss_20 = 0;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_50[var_r31] = -1;
        lbl_1_bss_48[var_r31] = -1;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_38[var_r31] = -1;
    }
    var_r29 = GWGameStat.rumble;
    lbl_1_bss_18 = var_r29;
    Hu3DShadowCreate(45.0f, 1000.0f, 250000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_data_54, &lbl_1_data_60, &lbl_1_data_6C);
    fn_1_2ACC(3);
}

Vec lbl_1_data_9C = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_A8 = { -1.0f, -2.0f, -1.0f };
GXColor lbl_1_data_B4 = { 0xFF, 0xFF, 0xFF, 0xFF };

void fn_1_2B8(omObjData *var_r27)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = Hu3DGLightCreateV(&lbl_1_data_9C, &lbl_1_data_A8, &lbl_1_data_B4);
    Hu3DGLightStaticSet(var_r28, 1);
    Hu3DGLightInfinitytSet(var_r28);
    for (var_r31 = 0, var_r30 = 0, var_r29 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayerCfg[var_r31].group == 0) {
            lbl_1_bss_50[var_r30] = var_r31;
            lbl_1_bss_48[var_r30] = GWPlayerCfg[var_r31].character;
            var_r30++;
        }
        else {
            lbl_1_bss_50[var_r29 + 2] = var_r31;
            lbl_1_bss_48[var_r29 + 2] = GWPlayerCfg[var_r31].character;
            var_r29++;
        }
    }
    if ((var_r30 != 2) || (var_r29 != 2)) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            lbl_1_bss_50[var_r31] = var_r31;
            lbl_1_bss_48[var_r31] = GWPlayerCfg[var_r31].character;
        }
    }
    fn_1_43C8(lbl_1_bss_88);
    fn_1_9F5C(lbl_1_bss_88);
    var_r27->func = fn_1_478;
}

void fn_1_478(omObjData *object)
{
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    switch (lbl_1_bss_7C) {
        case 0:
            lbl_1_bss_78++;
            Hu3DCamera->fov = -1.0f;
            Hu3DCamera[1].fov = -1.0f;
            if (lbl_1_bss_78 > 3) {
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                lbl_1_bss_20 = 0;
                fn_1_11798(1);
                lbl_1_bss_38[0] = HuAudFXPlay(0x65F);
                if ((lbl_1_bss_38[1] = HuAudFXPlay(0x660)) != -1) {
                    lbl_1_bss_28[1] = 0.0f;
                    HuAudFXVolSet(lbl_1_bss_38[1], (s32)(127.0f * lbl_1_bss_28[1]));
                    HuAudFXPitchSet(lbl_1_bss_38[1], (s32)(8191.0f * lbl_1_bss_28[1]));
                }
                if ((lbl_1_bss_38[2] = HuAudFXPlay(0x661)) != -1) {
                    lbl_1_bss_28[2] = 0.0f;
                    HuAudFXVolSet(lbl_1_bss_38[2], (s32)(127.0f * lbl_1_bss_28[2]));
                    HuAudFXPitchSet(lbl_1_bss_38[2], (s32)(8191.0f * lbl_1_bss_28[2]));
                }
                Hu3DCamera->fov = 45.0f;
                Hu3DCamera[1].fov = 45.0f;
                lbl_1_bss_7C = 1;
                lbl_1_bss_78 = 0;
            }
            break;
        case 1:
            if (WipeStatGet() == 0) {
                lbl_1_bss_7C = 2;
                lbl_1_bss_78 = 0;
            }
            else {
                sp2C.x = lbl_1_data_0->unk_00.x;
                sp2C.y = lbl_1_data_0->unk_00.y;
                sp2C.z = lbl_1_data_0->unk_00.z;
                sp38.x = lbl_1_data_0->unk_0C.x;
                sp38.y = lbl_1_data_0->unk_0C.y;
                sp38.z = lbl_1_data_0->unk_0C.z;
                fn_1_9A30(0, 1.0f, &sp38, &sp2C, lbl_1_data_0->unk_18);
                fn_1_9A30(1, 1.0f, &sp38, &sp2C, lbl_1_data_0->unk_18);
            }
            break;
        case 2:
            if (++lbl_1_bss_78 == 0x78) {
                sp2C.x = lbl_1_data_0[2].unk_00.x;
                sp2C.y = lbl_1_data_0[2].unk_00.y;
                sp2C.z = lbl_1_data_0[2].unk_00.z;
                sp38.x = lbl_1_data_0[2].unk_0C.x;
                sp38.y = lbl_1_data_0[2].unk_0C.y;
                sp38.z = lbl_1_data_0[2].unk_0C.z;
                fn_1_9A30(0, 300.0f, &sp38, &sp2C, lbl_1_data_0[2].unk_18);
                fn_1_9A30(1, 300.0f, &sp38, &sp2C, lbl_1_data_0[2].unk_18);
            }
            if ((fn_1_F354() != 0) && (lbl_1_bss_78 >= 0x78)) {
                sp2C.x = lbl_1_data_0[1].unk_00.x;
                sp2C.y = lbl_1_data_0[1].unk_00.y;
                sp2C.z = lbl_1_data_0[1].unk_00.z;
                sp38.x = lbl_1_data_0[1].unk_0C.x;
                sp38.y = lbl_1_data_0[1].unk_0C.y;
                sp38.z = lbl_1_data_0[1].unk_0C.z;
                fn_1_9A30(0, 42.0f, &sp38, &sp2C, lbl_1_data_0[1].unk_18);
                fn_1_9A30(1, 42.0f, &sp38, &sp2C, lbl_1_data_0[1].unk_18);
                lbl_1_bss_84 = MGSeqCreate(3, 0);
                lbl_1_bss_7C = 3;
                lbl_1_bss_78 = 0;
                lbl_1_bss_68 = 0;
            }
            break;
        case 3:
            if (lbl_1_bss_84 != -1) {
                var_r27 = MGSeqStatGet(lbl_1_bss_84);
                if (((var_r27 & 0x10) != 0) && (lbl_1_bss_24 == -1)) {
                    lbl_1_bss_24 = HuAudSeqPlay(0x4B);
                }
            }
            else {
                var_r27 = 0;
            }
            if ((lbl_1_bss_84 == -1) || (var_r27 == 0)) {
                lbl_1_bss_84 = -1;
                lbl_1_bss_7C = 4;
                lbl_1_bss_78 = 0;
                lbl_1_bss_74 = 180.0f + 120.0f * (0.007874016f * (frand() & 0x7F));
                lbl_1_bss_70 = 90.0f + 60.0f * (0.007874016f * (frand() & 0x7F));
                lbl_1_bss_6C = 45.0f + (120.0f * (0.007874016f * (frand() & 0x7F)));
                lbl_1_bss_58[0] = 15.0f;
                lbl_1_bss_58[1] = 15.0f;
                lbl_1_bss_68 = 0x4650;
            }
            break;
        case 4:
            if (++lbl_1_bss_78 >= lbl_1_bss_74) {
                var_r29 = lbl_1_bss_78 - lbl_1_bss_74;
                for (var_r31 = 0; var_r31 < 2; var_r31++) {
                    if (lbl_1_bss_58[var_r31] < 60.0f) {
                        var_r30 = 0;
                    }
                    else {
                        var_r30 = 1;
                    }
                    if (var_r29 <= (15.0f + (21.0f + lbl_1_bss_6C))) {
                        fn_1_9DE8(var_r31, 15.0f, 1);
                        fn_1_11754(var_r31, 0.05f);
                        if (var_r29 == 0) {
                            fn_1_F46C(var_r31, 0);
                        }
                        else if (var_r29 < lbl_1_bss_6C) {
                            fn_1_F454(var_r31, 1);
                            if ((var_r30 == 1) && (fn_1_F4E8(var_r31) == 0)) {
                                lbl_1_bss_58[var_r31] = 15.0f;
                            }
                        }
                        else if (var_r29 == lbl_1_bss_6C) {
                            if (var_r30 == 1) {
                                fn_1_F46C(var_r31, var_r30);
                            }
                        }
                        else if (var_r29 == (21.0f + lbl_1_bss_6C)) {
                            if (var_r30 == 0) {
                                fn_1_F454(var_r31, 2);
                            }
                            else {
                                fn_1_F454(var_r31, 3);
                                if (lbl_1_bss_18 == 0) {
                                    fn_1_116C4(var_r31, 1);
                                }
                                if (var_r30 != 0) {
                                    fn_1_F4B4(var_r31, lbl_1_bss_70, 3.125f);
                                }
                            }
                        }
                    }
                    else {
                        fn_1_9DE8(var_r31, lbl_1_bss_58[var_r31], 1);
                        if ((var_r29 < ((15.0f + lbl_1_bss_6C + lbl_1_bss_70) - 6.0f)) && (var_r30 == 1)) {
                            var_f31 = 0.10000000149011612 * sind((20.0f * var_r29));
                            fn_1_11754(var_r31, 0.3f + var_f31);
                        }
                        if (var_r30 == 0) {
                            fn_1_F454(var_r31, 4);
                        }
                        else {
                            fn_1_F454(var_r31, 5);
                        }
                    }
                }
                if (var_r29 == (15.0f + lbl_1_bss_6C + lbl_1_bss_70)) {
                    fn_1_F454(0, 6);
                    fn_1_F454(1, 6);
                }
                else if (var_r29 > (15.0f + lbl_1_bss_6C + lbl_1_bss_70)) {
                    fn_1_9EA8(0);
                    fn_1_9EA8(1);
                    fn_1_11754(0, 0.0f);
                    fn_1_11754(1, 0.0f);
                    fn_1_F46C(0, -1);
                    fn_1_F46C(1, -1);
                    fn_1_F454(0, 0);
                    fn_1_F454(1, 0);
                    if ((frand() & 3) == 0) {
                        lbl_1_bss_58[0] = lbl_1_bss_58[1] = 15.0f;
                    }
                    else {
                        lbl_1_bss_58[0] = lbl_1_bss_58[1] = 60.0f;
                    }
                    lbl_1_bss_78 = 0;
                    lbl_1_bss_74 = 180.0f + 120.0f * (0.007874016f * (frand() & 0x7F));
                    lbl_1_bss_70 = 90.0f + 60.0f * (0.007874016f * (frand() & 0x7F));
                    lbl_1_bss_6C = 45.0f + (120.0f * (0.007874016f * (frand() & 0x7F)));
                }
                for (var_r31 = 0; var_r31 < 2; var_r31++) {
                    if (lbl_1_bss_58[var_r31] < 60.0f) {
                        var_r30 = 0;
                    }
                    else {
                        var_r30 = 1;
                    }
                    if ((var_r29 <= (15.0f + (21.0f + lbl_1_bss_6C))) || (var_r30 < 1)) {
                        if (lbl_1_bss_28[var_r31 + 1] < 0.5f) {
                            lbl_1_bss_28[var_r31 + 1] += 0.1f;
                        }
                        if (lbl_1_bss_28[var_r31 + 1] > 0.5f) {
                            lbl_1_bss_28[var_r31 + 1] -= 0.1f;
                        }
                    }
                    else {
                        if (lbl_1_bss_28[var_r31 + 1] < 1.0f) {
                            lbl_1_bss_28[var_r31 + 1] += 0.1f;
                        }
                        if (lbl_1_bss_28[var_r31 + 1] > 1.0f) {
                            lbl_1_bss_28[var_r31 + 1] = 1.0f;
                        }
                    }
                }
            }
            else {
                if (lbl_1_bss_28[1] > 0.0f) {
                    lbl_1_bss_28[1] -= 0.01f;
                }
                if (lbl_1_bss_28[1] < 0.0f) {
                    lbl_1_bss_28[1] = 0.0f;
                }
                if (lbl_1_bss_28[2] > 0.0f) {
                    lbl_1_bss_28[2] -= 0.01f;
                }
                if (lbl_1_bss_28[2] < 0.0f) {
                    lbl_1_bss_28[2] = 0.0f;
                }
            }
            if (lbl_1_bss_38[1] != -1) {
                HuAudFXVolSet(lbl_1_bss_38[1], (s32)(127.0f * lbl_1_bss_28[1]));
                HuAudFXPitchSet(lbl_1_bss_38[1], (s32)(8191.0f * lbl_1_bss_28[1]));
            }
            if (lbl_1_bss_38[2] != -1) {
                HuAudFXVolSet(lbl_1_bss_38[2], (s32)(127.0f * lbl_1_bss_28[2]));
                HuAudFXPitchSet(lbl_1_bss_38[2], (s32)(8191.0f * lbl_1_bss_28[2]));
            }
            if ((lbl_1_bss_68 <= 1800.0f) && (lbl_1_bss_80 == -1)) {
                lbl_1_bss_80 = MGSeqCreate(1, lbl_1_bss_68 / 60, -1, -1);
            }
            if (lbl_1_bss_80 != -1) {
                var_r28 = (lbl_1_bss_68 + 0x3B) / 60;
                if (var_r28 < 0) {
                    var_r28 = 0;
                }
                MGSeqParamSet(lbl_1_bss_80, 1, var_r28);
            }
            var_r26 = fn_1_F3BC(0);
            var_r25 = fn_1_F3BC(1);
            if ((--lbl_1_bss_68 < -1) || (var_r26 != 0) || (var_r25 != 0)) {
                if (lbl_1_bss_80 != -1) {
                    MGSeqParamSet(lbl_1_bss_80, 2, -1);
                }
                lbl_1_bss_80 = -1;
                lbl_1_bss_84 = MGSeqCreate(3, 1);
                fn_1_9EA8(0);
                fn_1_9EA8(1);
                fn_1_11754(0, 0.0f);
                fn_1_11754(1, 0.0f);
                fn_1_F46C(0, -1);
                fn_1_F46C(1, -1);
                fn_1_F454(0, 0);
                fn_1_F454(1, 0);
                if (lbl_1_bss_38[0] != -1) {
                    HuAudFXFadeOut(lbl_1_bss_38[0], 0x64);
                }
                if (lbl_1_bss_38[1] != -1) {
                    HuAudFXFadeOut(lbl_1_bss_38[1], 0x64);
                }
                if (lbl_1_bss_38[2] != -1) {
                    HuAudFXFadeOut(lbl_1_bss_38[2], 0x64);
                }
                if (lbl_1_bss_24 != -1) {
                    HuAudSeqFadeOut(lbl_1_bss_24, 0x64);
                }
                if ((var_r26 != 0) && (var_r25 != 0)) {
                    if ((frand() & 1) != 0) {
                        lbl_1_bss_64 = 0;
                    }
                    else {
                        lbl_1_bss_64 = 1;
                    }
                }
                else if (var_r26 != 0) {
                    lbl_1_bss_64 = 0;
                }
                else if (var_r25 != 0) {
                    lbl_1_bss_64 = 1;
                }
                lbl_1_bss_7C = 6;
                lbl_1_bss_78 = 0;
            }
            break;
        case 6:
            if ((lbl_1_bss_64 == -1) || (lbl_1_bss_84 == -1) || (MGSeqStatGet(lbl_1_bss_84) == 0)) {
                if (lbl_1_bss_64 != -1) {
                    lbl_1_bss_84 = -1;
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x1E);
                    WipeColorSet(0xFF, 0xFF, 0xFF);
                    lbl_1_bss_20 = 1;
                }
                lbl_1_bss_7C = 5;
                lbl_1_bss_78 = 0;
            }
            break;
        case 5:
            if (lbl_1_bss_64 != -1) {
                if (WipeStatGet() == 0) {
                    lbl_1_bss_7C = 7;
                    lbl_1_bss_78 = 0;
                }
            }
            else if ((lbl_1_bss_84 == -1) || (MGSeqStatGet(lbl_1_bss_84) == 0)) {
                lbl_1_bss_84 = -1;
                lbl_1_bss_7C = 8;
                lbl_1_bss_78 = 0;
            }
            break;
        case 7:
            lbl_1_bss_78++;
            if (lbl_1_bss_78 == 1) {
                if (lbl_1_bss_64 == 0) {
                    fn_1_9ADC(0);
                    fn_1_F414(0);
                    lbl_1_bss_60 = 1;
                    fn_1_11798(0);
                }
                else if (lbl_1_bss_64 == 1) {
                    fn_1_9ADC(1);
                    fn_1_F414(1);
                    lbl_1_bss_60 = 1;
                    fn_1_11798(0);
                }
            }
            else if (lbl_1_bss_78 >= 0xA) {
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 0x3C);
                WipeColorSet(0xFF, 0xFF, 0xFF);
                lbl_1_bss_20 = 0;
                lbl_1_bss_38[3] = HuAudFXPlay(0x662);
                lbl_1_bss_7C = 8;
                lbl_1_bss_78 = 0;
            }
            break;
        case 8:
            if (lbl_1_bss_64 == 0) {
                if (++lbl_1_bss_78 >= 120.0f) {
                    lbl_1_bss_7C = 9;
                    lbl_1_bss_78 = 0;
                }
            }
            else if (lbl_1_bss_64 == 1) {
                if (++lbl_1_bss_78 >= 120.0f) {
                    lbl_1_bss_7C = 9;
                    lbl_1_bss_78 = 0;
                }
            }
            else {
                if (++lbl_1_bss_78 >= 60.0f) {
                    lbl_1_bss_7C = 9;
                    lbl_1_bss_78 = 0;
                }
            }
            break;
        case 9:
            if (lbl_1_bss_64 == 0) {
                lbl_1_bss_84 = MGSeqCreate(5, 3, lbl_1_bss_48[0], lbl_1_bss_48[1], -1, -1);
                GWPlayerCoinWinAdd(lbl_1_bss_50[0], 10);
                GWPlayerCoinWinAdd(lbl_1_bss_50[1], 10);
                HuAudSStreamPlay(1);
                lbl_1_bss_7C = 0xA;
                lbl_1_bss_68 = 0;
            }
            else if (lbl_1_bss_64 == 1) {
                lbl_1_bss_84 = MGSeqCreate(5, 3, lbl_1_bss_48[2], lbl_1_bss_48[3], -1, -1);
                GWPlayerCoinWinAdd(lbl_1_bss_50[2], 10);
                GWPlayerCoinWinAdd(lbl_1_bss_50[3], 10);
                HuAudSStreamPlay(1);
                lbl_1_bss_7C = 0xA;
                lbl_1_bss_68 = 0;
            }
            else {
                lbl_1_bss_84 = MGSeqCreate(3, 2);
                lbl_1_bss_7C = 0xA;
                lbl_1_bss_68 = 0;
                HuAudSStreamPlay(4);
            }
            break;
        case 10:
            if (++lbl_1_bss_68 >= 210.0f) {
                lbl_1_bss_84 = -1;
                lbl_1_bss_7C = 0xB;
                lbl_1_bss_68 = 0;
            }
            break;
        case 11:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
            lbl_1_bss_20 = 1;
            if (lbl_1_bss_38[3] != -1) {
                HuAudFXStop(lbl_1_bss_38[3]);
            }
            object->func = fn_1_25CC;
            break;
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        sp50.x = CenterM[var_r31].x;
        sp50.y = CenterM[var_r31].y;
        sp50.z = CenterM[var_r31].z;
        if (lbl_1_bss_60 == 0) {
            sp5C.x = CenterM[var_r31].x - 1200.0f;
            sp5C.y = 1200.0f + CenterM[var_r31].y;
            sp5C.z = 1200.0f + CenterM[var_r31].z;
        }
        else {
            sp5C.x = CenterM[var_r31].x - 600.0f;
            sp5C.y = 1000.0f + CenterM[var_r31].y;
            sp5C.z = 600.0f + CenterM[var_r31].z;
        }
        sp44.x = 0.0f;
        sp44.y = 1.0f;
        sp44.z = 0.0f;
        fn_1_4324(var_r31, &sp5C, &sp44, &sp50);
    }
    fn_1_261C(object);
}

void fn_1_25CC(omObjData *object)
{
    if (WipeStatGet() == 0) {
        fn_1_4630();
        fn_1_A0B0();
        fn_1_40A4();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_261C(omObjData *object)
{
    s32 var_r30 = 0;
    if ((WipeStatGet() != 0) || (object->func == fn_1_25CC)) {
        return;
    }
    if (omSysExitReq != 0) {
        var_r30 = 1;
    }
    if (var_r30 != 0) {
        if (lbl_1_bss_20 == 0) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        }
        lbl_1_bss_20 = 1;
        HuAudSeqAllFadeOut(0x64);
        object->func = fn_1_25CC;
    }
}

s32 fn_1_26E0(void)
{
    return lbl_1_bss_7C;
}

void fn_1_26F0(void)
{
    s32 var_r31;
    omObjData *object;

    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 50.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 0x140, 0x1E0);
    Hu3DCameraCreate(2);
    Hu3DCameraPerspectiveSet(2, 45.0f, 50.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(2, 0.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 0, 0, 0x140, 0x1E0);
    object = lbl_1_bss_14 = omAddObjEx(lbl_1_bss_88, 0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        CRotM[var_r31].x = lbl_1_data_0->unk_00.x;
        CRotM[var_r31].y = lbl_1_data_0->unk_00.y;
        CRotM[var_r31].z = lbl_1_data_0->unk_00.z;
        CenterM[var_r31].x = lbl_1_data_0->unk_0C.x;
        CenterM[var_r31].y = lbl_1_data_0->unk_0C.y;
        CenterM[var_r31].z = lbl_1_data_0->unk_0C.z;
        CZoomM[var_r31] = lbl_1_data_0->unk_18;
    }
    lbl_1_bss_C = 0;
    lbl_1_bss_10 = -1;
    omAddObjEx(lbl_1_bss_88, 0xFE, 0, 0, -1, fn_1_29E8);
}

void fn_1_29E8(omObjData *object) { }

void fn_1_29EC(void) { }

s32 fn_1_29F0(void)
{
    return lbl_1_bss_C;
}

void fn_1_2A00(s32 arg0, s32 arg1, float arg8)
{
    M428DllData0Struct *var_r31;
    M428DllData0Struct *var_r30;

    var_r31 = &lbl_1_data_0[arg0];
    var_r30 = &lbl_1_data_0[arg1];
    Center.x = var_r31->unk_0C.x + (arg8 * (var_r30->unk_0C.x - var_r31->unk_0C.x));
    Center.y = var_r31->unk_0C.y + (arg8 * (var_r30->unk_0C.y - var_r31->unk_0C.y));
    Center.z = var_r31->unk_0C.z + (arg8 * (var_r30->unk_0C.z - var_r31->unk_0C.z));
    CZoom = var_r31->unk_18 + (arg8 * (var_r30->unk_18 - var_r31->unk_18));
}

void fn_1_2ACC(s32 arg0)
{
    ShadowData *var_r31;
    s32 var_r30;
    M428DllUnkStruct2 *var_r29;
    ModelData *var_r28;
    M428DllUnkStruct *var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    u32 var_r23;

    lbl_1_bss_0 = var_r24 = Hu3DHookFuncCreate(fn_1_2C90);
    var_r28 = &Hu3DData[var_r24];
    Hu3DModelLayerSet(var_r24, 0);
    var_r27 = var_r28->unk_120 = HuMemDirectMallocNum(HEAP_DATA, sizeof(M428DllUnkStruct), var_r28->unk_48);
    memset(var_r27, 0, sizeof(M428DllUnkStruct));
    var_r27->unk_FC0 = Hu3DShadowData;
    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        var_r29 = &var_r27->unk_00[var_r30];
        var_r31 = &var_r27->unk_640[var_r30];
        var_r23 = 1 << var_r30;

        *var_r31 = Hu3DShadowData;
        for (var_r26 = 0; var_r26 < 0x10; var_r26++) {
            var_r29->unk_00[var_r26] = -1;
            var_r29->unk_20[var_r26] = 1.0f;
        }
        var_r29->unk_60 = 0;
        if ((var_r23 & arg0) != 0) {
            if (var_r30 == 0) {
                var_r31->unk_04 = Hu3DShadowData.unk_04;
            }
            else {
                var_r25 = var_r31->unk_02;
                var_r31->unk_04 = HuMemDirectMallocNum(HEAP_DATA, var_r25 * var_r25, var_r28->unk_48);
            }
        }
        else {
            var_r31->unk_04 = NULL;
        }
    }
    Hu3DShadowCamBit++;
}

void fn_1_2C90(ModelData *model, Mtx matrix)
{
    ShadowData *var_r31;
    s32 var_r30;
    M428DllUnkStruct *var_r29;
    M428DllUnkStruct2 *var_r28;

    var_r29 = model->unk_120;
    if (Hu3DCameraNo == 0) {
        for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
            var_r28 = &var_r29->unk_00[var_r30];
            var_r31 = &var_r29->unk_640[var_r30];
            if ((var_r31->unk_04 != NULL) && !(var_r31->unk_08.x <= 0.0f) && (var_r28->unk_60 > 0)) {
                Hu3DShadowData = *var_r31;
                fn_1_2E2C(var_r30);
                *var_r31 = Hu3DShadowData;
            }
        }
        HuSprDispInit();
        HuSprExec(0x7F);
    }
    var_r28 = &var_r29->unk_00[Hu3DCameraNo];
    var_r31 = &var_r29->unk_640[Hu3DCameraNo];
    if ((var_r31->unk_04 == NULL) || (var_r31->unk_08.x <= 0.0f)) {
        return;
    }
    Hu3DShadowData = *var_r31;
}

GXColor lbl_1_data_E8 = { 0, 0, 0, 0 };

void fn_1_2E2C(s32 var_r26)
{
    Mtx spBC;
    Mtx sp8C;
    Mtx sp5C;
    Mtx44 sp1C;
    ShadowData *sp18;
    ModelData *var_r31;
    s16 var_r30;
    M428DllUnkStruct2 *var_r29;
    M428DllUnkStruct *var_r28;
    s32 var_r27;
    s32 var_r25;
    u32 var_r24;

    var_r31 = &Hu3DData[lbl_1_bss_0];
    var_r28 = var_r31->unk_120;
    var_r29 = &var_r28->unk_00[var_r26];
    sp18 = &var_r28->unk_640[var_r26];
    var_r24 = Hu3DShadowData.unk_00;
    if (var_r26 == 0) {
        GXSetViewport(0.0f, 0.0f, RenderMode->fbWidth, RenderMode->xfbHeight, 0.0f, 1.0f);
        GXSetScissor(0, 0, RenderMode->fbWidth, RenderMode->efbHeight);
        C_MTXOrtho(sp1C, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        GXSetProjection(sp1C, GX_ORTHOGRAPHIC);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_U8, 0);
        GXSetTevColor(GX_TEVREG0, BGColor);
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumChans(0);
        MTXIdentity(sp8C);
        GXLoadPosMtxImm(sp8C, 0);
        GXSetZMode(0, GX_ALWAYS, GX_TRUE);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition1x8(0);
        GXPosition1x8(0);
        GXPosition1x8(0);
        GXPosition1x8(1);
        GXPosition1x8(0);
        GXPosition1x8(0);
        GXPosition1x8(1);
        GXPosition1x8(1);
        GXPosition1x8(0);
        GXPosition1x8(0);
        GXPosition1x8(1);
        GXPosition1x8(0);
        GXEnd();
    }
    Hu3DDrawPreInit();
    GXSetCopyClear(lbl_1_data_E8, 0xFFFFFF);
    C_MTXPerspective(sp1C, Hu3DShadowData.unk_08.x, 1.2f, Hu3DShadowData.unk_08.y, Hu3DShadowData.unk_08.z);
    GXSetProjection(sp1C, GX_PERSPECTIVE);
    if (Hu3DShadowData.unk_02 <= 0xF0) {
        GXSetScissor(2, 2, (Hu3DShadowData.unk_02 * 2) - 4, (Hu3DShadowData.unk_02 * 2) - 4);
        GXSetViewport(0.0f, 0.0f, Hu3DShadowData.unk_02 * 2, Hu3DShadowData.unk_02 * 2, 0.0f, 1.0f);
        var_r25 = (Hu3DShadowData.unk_02 / 2) * (Hu3DShadowData.unk_02 / 2);
    }
    else {
        GXSetScissor(1, 1, Hu3DShadowData.unk_02 - 2, Hu3DShadowData.unk_02 - 2);
        GXSetViewport(0.0f, 0.0f, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, 0.0f, 1.0f);
        var_r25 = Hu3DShadowData.unk_02 * Hu3DShadowData.unk_02;
    }
    C_MTXLookAt(Hu3DCameraMtx, &Hu3DShadowData.unk_14, &Hu3DShadowData.unk_2C, &Hu3DShadowData.unk_20);
    MTXCopy(Hu3DCameraMtx, Hu3DShadowData.unk_38);
    shadowModelDrawF = 1;
    GXInvalidateTexAll();
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, BGColor);
    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        if (var_r29->unk_00[var_r30] != -1) {
            var_r31 = &Hu3DData[var_r29->unk_00[var_r30]];
            if (((var_r31->attr & 1) == 0) && ((var_r31->attr & 0x8000) == 0)) {
                if ((var_r31->attr & 8) != 0) {
                    var_r27 = 0;
                    if (var_r31->unk_08 != -1) {
                        Hu3DMotionExec(var_r30, var_r31->unk_08, var_r31->unk_64, 0);
                    }
                    if (var_r31->unk_0C != -1) {
                        Hu3DSubMotionExec(var_r30);
                    }
                    if (var_r31->unk_0A != -1) {
                        Hu3DMotionExec(var_r30, var_r31->unk_0A, var_r31->unk_74, 1);
                    }
                    if ((var_r31->attr & 0x400) != 0) {
                        ClusterMotionExec(var_r31);
                        var_r27 = 1;
                    }
                    if (var_r31->unk_0E != -1) {
                        if (var_r31->unk_08 == -1) {
                            Hu3DMotionExec(var_r30, var_r31->unk_0E, var_r31->unk_94, 0);
                        }
                        else {
                            Hu3DMotionExec(var_r30, var_r31->unk_0E, var_r31->unk_94, 1);
                        }
                    }
                    if (((var_r31->attr & 0x90) == 0) || ((var_r31->motion_attr & 0x40000002) == 0)) {
                        var_r27 = 1;
                        InitVtxParm(var_r31->hsfData);
                        if (var_r31->unk_0E != -1) {
                            ShapeProc(var_r31->hsfData);
                        }
                        if ((var_r31->attr & 0x400) != 0) {
                            ClusterProc(var_r31);
                        }
                        if (var_r31->hsfData->cenvCnt != 0) {
                            EnvelopeProc(var_r31->hsfData);
                        }
                        PPCSync();
                    }
                    var_r31->attr |= 0x800;
                }
                Hu3DModelShadowSet(var_r29->unk_00[var_r30]);
                Hu3DShadowData.unk_00 = (s8)(var_r29->unk_20[var_r30] * var_r24);
                mtxRot(sp5C, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
                MTXScale(spBC, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
                MTXConcat(sp5C, spBC, spBC);
                mtxTransCat(spBC, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
                MTXConcat(Hu3DCameraMtx, spBC, sp8C);
                MTXConcat(sp8C, var_r31->unk_F0, sp8C);
                Hu3DDraw(var_r31, sp8C, &var_r31->scale);
                Hu3DModelShadowReset(var_r29->unk_00[var_r30]);
            }
        }
    }
    Hu3DDrawPost();
    GXDrawDone();
    shadowModelDrawF = 0;
    if (Hu3DShadowData.unk_02 <= 0xF0) {
        GXSetTexCopySrc(0, 0, Hu3DShadowData.unk_02 * 2, Hu3DShadowData.unk_02 * 2);
        GXSetTexCopyDst(Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, GX_CTF_R8, 1);
    }
    else {
        GXSetTexCopySrc(0, 0, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02);
        GXSetTexCopyDst(Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, GX_CTF_R8, 0);
    }
    GXCopyTex(Hu3DShadowData.unk_04, 1);
    GXSetViewport(0.0f, 0.0f, RenderMode->fbWidth, RenderMode->xfbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, RenderMode->fbWidth, RenderMode->efbHeight);
    C_MTXOrtho(sp1C, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    GXSetProjection(sp1C, GX_ORTHOGRAPHIC);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_U8, 0);
    GXSetTevColor(GX_TEVREG0, BGColor);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(0);
    MTXIdentity(sp8C);
    GXLoadPosMtxImm(sp8C, 0);
    GXSetZMode(0, GX_ALWAYS, 1);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition1x8(0);
    GXPosition1x8(0);
    GXPosition1x8(0);
    GXPosition1x8(1);
    GXPosition1x8(0);
    GXPosition1x8(0);
    GXPosition1x8(1);
    GXPosition1x8(1);
    GXPosition1x8(0);
    GXPosition1x8(0);
    GXPosition1x8(1);
    GXPosition1x8(0);
    GXEnd();
}

void fn_1_3B64(void)
{
    Mtx44 sp64;
    Mtx sp34;
    GXTexObj sp14;
    ShadowData *sp10;
    GXColor spC;
    M428DllUnkStruct *var_r31;
    M428DllUnkStruct2 *var_r30;
    ModelData *var_r29;
    u8 *var_r28;

    if (lbl_1_bss_0 != -1) {
        var_r29 = &Hu3DData[lbl_1_bss_0];
        var_r31 = var_r29->unk_120;
        var_r30 = &var_r31->unk_00[Hu3DCameraNo];
        sp10 = &var_r31->unk_640[Hu3DCameraNo];
        if (var_r30->unk_60 > 0) {
            GXInitTexObj(&sp14, Hu3DShadowData.unk_04, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, GX_TF_I8, GX_CLAMP, GX_CLAMP, 0);
            GXInitTexObjLOD(&sp14, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&sp14, GX_TEXMAP0);
            C_MTXOrtho(sp64, 0.0f, 480.0f, 0.0f, 320.0f, 0.0f, 10.0f);
            GXSetProjection(sp64, GX_ORTHOGRAPHIC);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
            spC.a = 0x80;
            GXSetTevColor(GX_TEVREG0, spC);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetNumTexGens(1);
            GXSetNumTevStages(1);
            MTXIdentity(sp34);
            GXLoadPosMtxImm(sp34, 0);
            GXSetZMode(0, GX_LEQUAL, GX_FALSE);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(Hu3DShadowData.unk_02, 0.0f, 0.0f);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, 0.0f);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(0.0f, Hu3DShadowData.unk_02, 0.0f);
            GXTexCoord2f32(0.0f, 1.0f);
            GXEnd();
        }
    }
#ifdef TARGET_PC
    GXDestroyTexObj(&sp14);
#endif
}

s32 lbl_1_data_EC[] = {
    0,
    0,
    0x45ABE000,
    0xC576E000,
    0,
    0xBF333333,
    0x3F19999A,
    0xFFFFFFFF,
    0,
    0x45ABE000,
    0xC576E000,
    0,
    0x3F800000,
    0,
    0,
    0,
    0,
};

void fn_1_40A4(void)
{
    M428DllUnkStruct *var_r31;
    ModelData *var_r30;

    var_r30 = &Hu3DData[lbl_1_bss_0];
    var_r31 = var_r30->unk_120;
    Hu3DShadowData = var_r31->unk_FC0;
    Hu3DModelKill(lbl_1_bss_0);
    lbl_1_bss_0 = -1;
    if (Hu3DShadowCamBit > 0) {
        Hu3DShadowCamBit--;
    }
}

void fn_1_4170(s16 arg0, s32 arg1)
{
    ShadowData *sp8;
    M428DllUnkStruct2 *var_r31;
    s32 var_r30;
    s32 var_r29;
    M428DllUnkStruct *var_r28;
    ModelData *var_r27;
    u32 var_r26;

    var_r27 = &Hu3DData[lbl_1_bss_0];
    var_r28 = var_r27->unk_120;
    for (var_r29 = 0; var_r29 < 0x10; var_r29++) {
        var_r31 = &var_r28->unk_00[var_r29];
        sp8 = &var_r28->unk_640[var_r29];
        var_r26 = 1 << var_r29;
        if ((var_r26 & arg1) != 0) {
            for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
                if (arg0 != var_r31->unk_00[var_r30]) {
                    if (var_r31->unk_00[var_r30] == -1) {
                        var_r31->unk_00[var_r30] = arg0;
                        var_r31->unk_20[var_r30] = 1.0f;
                        var_r31->unk_60++;
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
    }
}

void fn_1_4264(s16 arg0, s32 arg1, float arg8)
{
    ShadowData *sp8;
    s32 var_r31;
    s32 var_r30;
    M428DllUnkStruct2 *var_r29;
    M428DllUnkStruct *var_r28;
    ModelData *var_r27;
    u32 var_r26;

    var_r27 = &Hu3DData[lbl_1_bss_0];
    var_r28 = var_r27->unk_120;
    for (var_r31 = 0; var_r31 < 0x10; var_r31++) {
        var_r29 = &var_r28->unk_00[var_r31];
        sp8 = &var_r28->unk_640[var_r31];
        var_r26 = 1 << var_r31;
        if ((var_r26 & arg1) != 0) {
            for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
                if (arg0 == var_r29->unk_00[var_r30]) {
                    var_r29->unk_20[var_r30] = arg8;
                }
            }
        }
    }
}

void fn_1_4324(s32 arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    M428DllUnkStruct2 *sp8;
    ShadowData *var_r31;
    M428DllUnkStruct *var_r30;
    ModelData *var_r29;

    var_r29 = &Hu3DData[lbl_1_bss_0];
    var_r30 = var_r29->unk_120;
    sp8 = &var_r30->unk_00[arg0];
    var_r31 = &var_r30->unk_640[arg0];
    var_r31->unk_14 = *arg1;
    var_r31->unk_20 = *arg3;
    var_r31->unk_2C = *arg2;
}
