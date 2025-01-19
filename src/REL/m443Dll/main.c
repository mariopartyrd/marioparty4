#include "dolphin/gx/GXVert.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "math.h"

#include "string.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/frand.h"
#endif

#include "REL/m443Dll.h"

typedef struct M443DllWork {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    char unk24[4];
    s32 unk_28;
    u32 unk_2C;
    s32 unk_30;
    s32 unk_34[4];
    float unk_44[4];
    u32 unk_54;
    u32 unk_58;
    s32 unk_5C;
} M443DllWork; /* size = 0x60 */

typedef struct M443DllData108Struct {
    u32 unk_00;
    s32 unk_04;
} M443DllData108Struct; /* size = 0x08 */

typedef struct M443DllUnkStruct {
    s32 unk_00;
    s32 unk_04;
    float unk_08;
    float unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    s16 unk_1C[0x10];
} M443DllUnkStruct; /* size = 0x3C */

void fn_1_1294(omObjData *);
void fn_1_17D8(omObjData *arg0);
omObjFunc fn_1_1C98(Process *arg0, omObjData *arg1);
void fn_1_1D8C(omObjData *);
omObjFunc fn_1_2490(Process *arg0, omObjData *arg1);
void fn_1_25A4(omObjData *);
void fn_1_2DD8(M443DllUnkStruct *arg0);
void fn_1_2F54(M443DllUnkStruct *arg0);
void fn_1_32C0(Process *arg0);
void fn_1_3370(omObjData *object);
void fn_1_3710(omObjData *);
void fn_1_3770(omObjData *object);
void fn_1_3D78(ModelData *, float[3][4]);
void fn_1_420(omObjData *object);
void fn_1_584(omObjData *arg0);
void fn_1_6D0(omObjData *);
void fn_1_9B0(omObjData *);
void fn_1_CE0(omObjData *);
void fn_1_ECC(omObjData *);

Vec lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };

Vec lbl_1_data_C = { 0.3f, -0.8f, 0.3f };

Vec lbl_1_data_18 = { 10.0f, 45.0f, 3500.0f };

GXColor lbl_1_data_24 = { 0xFF, 0xFF, 0xFF, 0xFF };

Vec lbl_1_data_28 = { 50.0f, 150000.0f, 50.0f };

Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };

Vec lbl_1_data_40 = { 0.0f, 0.0f, 0.0f };

Process *lbl_1_bss_74;
omObjData *lbl_1_bss_70;
omObjData *lbl_1_bss_6C;
omObjData *lbl_1_bss_68;
s16 lbl_1_bss_64;
s16 lbl_1_bss_5C[4];
s16 lbl_1_bss_5A;
s16 lbl_1_bss_58;
s16 lbl_1_bss_56;
s16 lbl_1_bss_54;
s32 lbl_1_bss_50;
M443DllUnkStruct lbl_1_bss_14;
s16 lbl_1_bss_10[1]; // why only 1 long?
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    Vec sp14;
    Vec sp8;
    Process *var_r31;
    LightData *var_r30;

    HuAudSndGrpSet(0x45);
    lbl_1_bss_C = lbl_1_bss_8 = -1;
    lbl_1_bss_4 = lbl_1_bss_0 = -1;
    lbl_1_bss_5C[0] = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_5C[0]);
    var_r30 = &Hu3DGlobalLight[lbl_1_bss_5C[0]];
    var_r30->unk_00 |= 0x8000;

    lbl_1_data_18.x = 55.74f;
    lbl_1_data_18.y = 0.0f;
    lbl_1_data_18.z = 3500.0f;

    sp14.x = sp14.y = sp14.z = 0.0f;
    sp8.x = sp8.z = 0.0f;
    sp8.y = lbl_1_data_18.z;
    sp8.x = 0.0f;
    sp8.y = 3480.0002f;
    sp8.z = 900.00006f;
    Hu3DGLightPosAimSetV(lbl_1_bss_5C[0], &sp8, &sp14);

    lbl_1_data_28.x = 100.0f;
    lbl_1_data_28.y = 2000.0f;
    lbl_1_data_28.z = 2000.0f;
    lbl_1_data_34.x = 0.0f;
    lbl_1_data_34.y = 1.0f;
    lbl_1_data_34.z = 0.0f;
    lbl_1_data_40.x = 0.0f;
    lbl_1_data_40.y = 0.0f;
    lbl_1_data_40.z = 700.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.625f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    lbl_1_bss_5A = lbl_1_bss_58 = lbl_1_bss_56 = lbl_1_bss_54 = -1;
    lbl_1_bss_50 = 0;
    var_r31 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_74 = var_r31;
    omGameSysInit(var_r31);
    fn_1_2DD8(&lbl_1_bss_14);
    fn_1_32C0(var_r31);
    lbl_1_bss_70 = omAddObjEx(var_r31, 0xA, 0, 0, -1, fn_1_420);
    fn_1_4A5C(var_r31);
    fn_1_5444(var_r31);
}

void fn_1_420(omObjData *object)
{
    M443DllWork *var_r31;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M443DllWork), MEMORY_DEFAULT_NUM);
    var_r31 = object->data;
    memset(var_r31, 0, sizeof(M443DllWork));
    var_r31->unk_00 = 0;
    var_r31->unk_04 = 0;
    var_r31->unk_0C = 0;
    var_r31->unk_10 = 0;
    var_r31->unk_14 = 0;
    var_r31->unk_18 = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_2C = 0;
    var_r31->unk_08 = 0;
    var_r31->unk_54 = 2;
    var_r31->unk_58 = 0;
    var_r31->unk_5C = 0;
    object->func = fn_1_6D0;
}

void fn_1_4E4(omObjData *object)
{
    M443DllWork *var_r31;

    var_r31 = object->data;
    var_r31->unk_04++;
    var_r31->unk_10++;
    var_r31->unk_18++;
    var_r31->unk_2C++;
    fn_1_2F54(&lbl_1_bss_14);
    if ((omSysExitReq != 0) && (var_r31->unk_00 != 5)) {
        var_r31->unk_00 = 4;
        fn_1_584(object);
    }
}

void fn_1_584(omObjData *object)
{
    M443DllWork *var_r31 = object->data;

    if (var_r31->unk_08 == 0) {
        switch (var_r31->unk_00) {
            case 0:
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                lbl_1_bss_14.unk_00 = 1;
                var_r31->unk_00 = 1;
                var_r31->unk_10 = 0;
                object->func = fn_1_1C98(lbl_1_bss_74, object);
                break;
            case 1:
                var_r31->unk_00 = 2;
                var_r31->unk_18 = 0;
                fn_1_3FE8(4);
                object->func = fn_1_ECC;
                break;
            case 2:
                var_r31->unk_00 = 3;
                var_r31->unk_2C = 0;
                object->func = fn_1_2490(lbl_1_bss_74, object);
                break;
            case 3:
            case 4:
                var_r31->unk_08 = 1;
                var_r31->unk_00 = 5;
                object->func = fn_1_9B0;
                break;
            case 5:
            default:
                var_r31->unk_00 = 5;
                object->func = fn_1_CE0;
                break;
        }
        var_r31->unk_04 = 0;
    }
}

void fn_1_6D0(omObjData *object)
{
    fn_1_4E4(object);
    fn_1_584(object);
}

void fn_1_9B0(omObjData *object)
{
    M443DllWork *var_r27 = object->data;

    fn_1_4E4(object);

    if (WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        if (lbl_1_bss_8 >= 0) {
            HuAudFXStop(lbl_1_bss_8);
            lbl_1_bss_8 = -1;
        }
        var_r27->unk_08 = 0;
        fn_1_584(object);
    }
}

void fn_1_CE0(omObjData *object)
{
    fn_1_4E4(object);

    if (WipeStatGet() == 0) {
        fn_1_565C();
        fn_1_4AB0();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_ECC(omObjData *object)
{
    M443DllWork *var_r29 = object->data;

    fn_1_4E4(object);
    switch (var_r29->unk_14) {
        case 0:
            var_r29->unk_1C = 0x12C;
            var_r29->unk_20 = 0x3C;
            lbl_1_bss_5A = MGSeqCreate(3, 0);
            MGSeqPosSet(lbl_1_bss_5A, 320.0f, 240.0f);
            lbl_1_bss_64 = -1;
            Center.x = 0.0f;
            Center.y = 200.0f;
            Center.z = 0.0f;
            CRot.x = -30.0f;
            CRot.y = 0.0f;
            CRot.z = 0.0f;
            CZoom = 1900.0f;
            lbl_1_bss_14.unk_00 = 1;
            var_r29->unk_14 = 1;
            var_r29->unk_18 = 0;
            break;
        case 1:
            if ((var_r29->unk_18 > 60.0f) && (lbl_1_bss_C >= 0)) {
                HuAudFXFadeOut(lbl_1_bss_C, 0x1E);
                lbl_1_bss_C = -1;
            }
            if ((MGSeqStatGet(lbl_1_bss_5A) == 0) && (var_r29->unk_08 == 0)) {
                var_r29->unk_14 = 2;
                var_r29->unk_18 = 0;
                object->func = fn_1_1294;
            }
            break;
    }
}

void fn_1_1294(omObjData *object)
{
    s32 sp8[4];

    float var_f31;

    s32 var_r30;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    M443DllWork *var_r31 = object->data;
    var_r25 = 0;
    fn_1_4E4(object);
    lbl_1_bss_14.unk_14++;
    if (--var_r31->unk_20 == 0) {
        var_r31->unk_20 = 0x3C;
        var_r31->unk_1C--;
        if (var_r31->unk_1C == 0) {
            var_r31->unk_54 = 0;
            var_r25 = 1;
        }
    }
    if (var_r31->unk_1C <= 5) {
        if (lbl_1_bss_64 < 0) {
            lbl_1_bss_64 = MGSeqCreate(1, var_r31->unk_1C, -1, -1);
        }
        MGSeqParamSet(lbl_1_bss_64, 1, var_r31->unk_1C);
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        if (var_r31->unk_44[var_r30] >= 40000.0f) {
            var_r31->unk_54 = 1;
        }
    }
    if (var_r31->unk_54 != 2) {
        var_r25 = 1;
    }
    if (var_r25 != 0) {
        if (var_r31->unk_54 == 1) {
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                sp8[var_r30] = var_r30;
            }
            for (var_r24 = 0; var_r24 < 0xA; var_r24++) {
                for (var_r30 = 0; var_r30 < 3; var_r30++) {
                    for (var_r26 = var_r30 + 1; var_r26 < 4; var_r26++) {
                        if ((var_r31->unk_44[var_r30] < var_r31->unk_44[var_r26])
                            || ((var_r31->unk_44[var_r30] == var_r31->unk_44[var_r26]) && (frandmod(0x3E8) < 0x2BC))) {
                            var_f31 = var_r31->unk_44[var_r30];
                            var_r31->unk_44[var_r30] = var_r31->unk_44[var_r26];
                            var_r31->unk_44[var_r26] = var_f31;
                            var_r23 = sp8[var_r30];
                            sp8[var_r30] = sp8[var_r26];
                            sp8[var_r26] = var_r23;
                        }
                    }
                }
            }
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                var_r31->unk_34[sp8[var_r30]] = var_r30;
            }
            var_r31->unk_30 = sp8[0];
        }
        lbl_1_bss_58 = MGSeqCreate(3, 1);
        MGSeqPosSet(lbl_1_bss_58, 320.0f, 240.0f);
        if (GWPlayerCfg[var_r31->unk_30].iscom == 0) {
            if (lbl_1_bss_14.unk_14 < lbl_1_bss_14.unk_10) {
                GWMGRecordSet(5, lbl_1_bss_14.unk_14);
                lbl_1_bss_50 = 1;
            }
            if (lbl_1_bss_14.unk_14 <= 0x258) {
                GWGameStat.present[0x39] = 1;
                OSReport("Present For You!!!\n");
            }
        }
        lbl_1_bss_8 = HuAudFXPlay(0x735);
        fn_1_3FE8(3);
        var_r31->unk_14 = 3;
        var_r31->unk_18 = 0;
        if (var_r31->unk_08 == 0) {
            object->func = fn_1_17D8;
        }
    }
}

void fn_1_17D8(omObjData *object)
{
    M443DllWork *var_r27 = object->data;
    s32 var_r25 = 0;

    if (lbl_1_bss_64 >= 0) {
        MGSeqParamSet(lbl_1_bss_64, 2, -1);
        lbl_1_bss_64 = -1;
    }
    fn_1_4E4(object);
    if (var_r27->unk_14 == 3) {
        if (var_r27->unk_54 == 1) {
            M443DllCameraStruct *var_r31 = fn_1_4148(var_r27->unk_30 + 1);
            if (var_r31->unk_A0 == 0) {
                var_r31->unk_78 = var_r31->unk_44;
                var_r31->unk_7C = var_r31->unk_48;
                var_r31->unk_80 = var_r31->unk_40;
                var_r31->unk_04 = 0x3E8;
            }
            if (var_r31->unk_A0 <= 0x3C) {
                float var_f31 = 0.016666668f * var_r31->unk_A0;
                var_r31->unk_44 = var_r31->unk_78 + ((320.0f - var_r31->unk_78) * var_f31);
                var_r31->unk_48 = var_r31->unk_7C + ((240.0f - var_r31->unk_7C) * var_f31);
                var_r31->unk_40 = var_r31->unk_80 + ((2.0f - var_r31->unk_80) * var_f31);
            }
            else {
                var_r25 = 1;
            }
            var_r31->unk_A0 = var_r31->unk_A0 + 1;
        }
        else {
            var_r25 = 1;
        }
        if ((MGSeqStatGet(lbl_1_bss_58) == 0) && (var_r27->unk_58 == 0x1111) && (var_r25 != 0)) {
            if (var_r27->unk_08 == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            }
            var_r27->unk_14 = 4;
            var_r27->unk_18 = 0;
        }
    }
    else if (WipeStatGet() == 0) {
        var_r27->unk_14 = 5;
        var_r27->unk_18 = 0;
        fn_1_584(object);
    }
}

omObjFunc fn_1_1C98(Process *process, omObjData *object)
{
    CRot.x = -80.5f;
    CRot.y = CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    CZoom = 1000.0f;
    object->work[0] = object->work[1] = 0;
    fn_1_3FE8(1);
    lbl_1_bss_C = HuAudFXPlay(0x734);

    return fn_1_1D8C;
}

Vec lbl_1_data_60[6] = {
    { -500.0f, 150.0f, 350.0f },
    { -500.0f, 150.0f, 350.0f },
    { 500.0f, 150.0f, 350.0f },
    { 500.0f, 150.0f, 350.0f },
    { 0.0f, 150.0f, 350.0f },
    { 0.0f, 150.0f, 350.0f },
};

Vec lbl_1_data_A8[6] = {
    { -1.5f, -40.0f, 880.0f },
    { -1.5f, -40.0f, 880.0f },
    { -20.0f, 40.0f, 1000.0f },
    { -40.0f, 130.0f, 1300.0f },
    { -40.0f, 180.0f, 1500.0f },
    { -40.0f, 180.0f, 1500.0f },
};

s32 lbl_1_data_F0[6] = { 0x3C, 0x5A, 0x6C, 0x96, 0x6C, 0 };

void fn_1_1D8C(omObjData *object)
{
    Vec sp8;

    float var_f31;
    M443DllCameraStruct *var_r27;

    M443DllWork *var_r26 = object->data;
    fn_1_4E4(object);
    var_r26->unk_0C = 1;
    object->work[0]++;
    if ((object->work[1] == 1) && (lbl_1_bss_4 < 0)) {
        lbl_1_bss_4 = HuAudSStreamPlay(0xB);
    }
    var_f31 = (float)object->work[0] / lbl_1_data_F0[object->work[1]];
    VECSubtract(&lbl_1_data_60[object->work[1] + 1], &lbl_1_data_60[object->work[1]], &sp8);
    VECScale(&sp8, &sp8, var_f31);
    VECAdd(&lbl_1_data_60[object->work[1]], &sp8, &sp8);
    Center.x = sp8.x;
    Center.y = sp8.y;
    Center.z = sp8.z;
    VECSubtract(&lbl_1_data_A8[object->work[1] + 1], &lbl_1_data_A8[object->work[1]], &sp8);
    VECScale(&sp8, &sp8, var_f31);
    VECAdd(&lbl_1_data_A8[object->work[1]], &sp8, &sp8);
    CRot.x = sp8.x;
    CRot.y = sp8.y;
    CRot.z = 0.0f;
    CZoom = sp8.z;
    var_r27 = fn_1_4148(0);
    var_r27->unk_1C = Center;
    var_r27->unk_28 = CRot;
    var_r27->unk_34 = CZoom;
    if (object->work[1] == 3) {
        fn_1_3FE8(2);
    }
    if (var_f31 >= 1.0f) {
        object->work[0] = 0;
        object->work[1] += 1;
        if (lbl_1_data_F0[object->work[1]] == 0) {
            var_r26->unk_0C = 2;
            fn_1_584(object);
        }
    }
}

omObjFunc fn_1_2490(Process *process, omObjData *object)
{
    M443DllCameraStruct *var_r31;
    M443DllWork *var_r30 = object->data;

    if (var_r30->unk_08 == 0) {
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    }
    fn_1_3FE8(1);
    var_r31 = fn_1_4148(0);
    if (var_r30->unk_54 == 1) {
        var_r31->unk_1C.x = 70.0f;
        var_r31->unk_1C.y = 250.0f;
        var_r31->unk_1C.z = 500.0f;
    }
    else {
        var_r31->unk_1C.x = 0.0f;
        var_r31->unk_1C.y = 150.0f;
        var_r31->unk_1C.z = 1000.0f;
    }
    var_r31->unk_28.x = -10.0f;
    var_r31->unk_28.y = 0.0f;

    var_r31->unk_34 = 800.0f;
    return fn_1_25A4;
}

void fn_1_25A4(omObjData *object)
{
    M443DllWork *var_r28 = object->data;
    s32 var_r22 = 1;

    fn_1_4E4(object);
    if (lbl_1_bss_50 != 0) {
        var_r22 = 0;
        if (lbl_1_bss_56 < 0) {
            lbl_1_bss_56 = MGSeqCreate(0xE, lbl_1_bss_14.unk_14);
            lbl_1_bss_14.unk_04 = 1;
        }
        else if (MGSeqStatGet(lbl_1_bss_56) == 0) {
            var_r22 = 1;
            lbl_1_bss_50 = 0;
        }
    }
    if ((WipeStatGet() != 0) || (var_r22 == 0)) {
        var_r28->unk_2C = 0;
        return;
    }
    var_r28->unk_28 = 1;
    if (lbl_1_bss_0 < 0) {
        if (var_r28->unk_54 == 1) {
            lbl_1_bss_0 = HuAudSStreamPlay(1);
        }
        else {
            lbl_1_bss_0 = HuAudSStreamPlay(4);
        }
    }
    if (lbl_1_bss_54 < 0) {
        if (var_r28->unk_54 == 1) {
            lbl_1_bss_54 = MGSeqCreate(5, 3, GWPlayerCfg[var_r28->unk_30].character, -1, -1, -1);
            GWPlayerCoinWinAdd(var_r28->unk_30, 10);
        }
        else {
            lbl_1_bss_54 = MGSeqCreate(5, 2);
        }
    }
    else if ((MGSeqStatGet(lbl_1_bss_54) == 0) && (var_r28->unk_2C >= 210.0f)) {
        var_r28->unk_28 = 2;
        fn_1_584(object);
    }
}

M443DllData108Struct lbl_1_data_108[0x10] = {
    { 0x4A001F, 0x10E },
    { 0x610037, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
};

void fn_1_2DD8(M443DllUnkStruct *arg0)
{
    s32 var_r30;

    memset(arg0, 0, sizeof(M443DllUnkStruct));
    arg0->unk_10 = GWMGRecordGet(5);
    if (arg0->unk_10 == 0) {
        arg0->unk_10 = 0xE10;
    }
    arg0->unk_08 = 320.0f;
    arg0->unk_0C = 64.0f;
    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        arg0->unk_1C[var_r30] = -1;
        if (lbl_1_data_108[var_r30].unk_00 != 0) {
            arg0->unk_1C[var_r30] = espEntry(lbl_1_data_108[var_r30].unk_00, lbl_1_data_108[var_r30].unk_04, 0);
            espAttrSet(arg0->unk_1C[var_r30], HUSPR_ATTR_LINEAR);
            espDispOff(arg0->unk_1C[var_r30]);
        }
    }
    espColorSet(arg0->unk_1C[0], 0, 0, 0);
    espTPLvlSet(arg0->unk_1C[0], 0.699999988079071);
    espBankSet(arg0->unk_1C[7], 0xB);
    espBankSet(arg0->unk_1C[8], 0xA);
    espBankSet(arg0->unk_1C[14], 0xB);
    espBankSet(arg0->unk_1C[15], 0xA);
}

Vec2f lbl_1_data_188[0x10] = {
    { 0.0f, 0.0f },
    { -52.0f, -9.0f },
    { 53.0f, -8.0f },
    { 35.0f, -8.0f },
    { 9.0f, -8.0f },
    { -9.0f, -8.0f },
    { -31.0f, -8.0f },
    { 23.0f, -8.0f },
    { -17.0f, -8.0f },
    { 53.0f, 8.0f },
    { 35.0f, 8.0f },
    { 9.0f, 8.0f },
    { -9.0f, 8.0f },
    { -31.0f, 8.0f },
    { 23.0f, 8.0f },
    { -17.0f, 8.0f },
};

void fn_1_2F54(M443DllUnkStruct *arg0)
{
    u32 sp8[3];
    float var_f31;

    s32 var_r30;
    u32 var_r29;
    s32 var_r28;
    s32 var_r27;

    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        if (arg0->unk_1C[var_r30] >= 0) {
            if (arg0->unk_00 == 0) {
                espDispOff(arg0->unk_1C[var_r30]);
            }
            else {
                espDispOn(arg0->unk_1C[var_r30]);
                espPosSet(arg0->unk_1C[var_r30], 0.9f * (arg0->unk_08 + lbl_1_data_188[var_r30].x), arg0->unk_0C + lbl_1_data_188[var_r30].y);
            }
        }
    }
    arg0->unk_18++;
    if (arg0->unk_04 != 0) {
        var_r29 = arg0->unk_14;
        arg0->unk_10 = var_r29;
        var_f31 = 1.100000023841858 + (0.10000000149011612 * sind((22.5f * (arg0->unk_18 & 0xF))));
        espScaleSet(arg0->unk_1C[1], var_f31, var_f31);
        for (var_r30 = 2; var_r30 <= 6; var_r30++) {
            espScaleSet(arg0->unk_1C[var_r30], var_f31, var_f31);
        }
        for (var_r30 = 7; var_r30 <= 8; var_r30++) {
            espScaleSet(arg0->unk_1C[var_r30], var_f31, var_f31);
        }
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        if (var_r30 != 0) {
            var_r29 = arg0->unk_14;
            var_r27 = 9;
        }
        else {
            var_r29 = arg0->unk_10;
            var_r27 = 2;
        }
        sp8[0] = var_r29 % 60;
        var_r29 = (var_r29 - sp8[0]) / 60;
        sp8[0] = 100.0f * (0.016666668f * sp8[0]);
        sp8[1] = var_r29 % 60;
        var_r29 = (var_r29 - sp8[1]) / 60;
        sp8[2] = var_r29;
        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            espBankSet(arg0->unk_1C[var_r27++], sp8[var_r28] % 10);
            if (var_r28 < 2) {
                espBankSet(arg0->unk_1C[var_r27++], sp8[var_r28] / 10);
            }
        }
    }
}

void fn_1_32C0(Process *process)
{
    Hu3DCameraCreate(0x1F);
    lbl_1_bss_6C = omAddObjEx(process, 0x7FDA, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_6C->work[0] = 5;
    lbl_1_bss_68 = omAddObjEx(process, 0xC, 1, 0, -1, fn_1_3370);
    lbl_1_bss_68->work[0] = 0;
}

void fn_1_3370(omObjData *object)
{
    M443DllCameraStruct *var_r31;
    s32 var_r30;
    M443DllCameraStruct *var_r28;

    float sp1C[5][4] = {
        { 320.0f, 240.0f, 640.0f, 416.0f },
        { 160.0f, 136.0f, 320.0f, 208.0f },
        { 480.0f, 136.0f, 320.0f, 208.0f },
        { 160.0f, 344.0f, 320.0f, 208.0f },
        { 480.0f, 344.0f, 320.0f, 208.0f },
    };
    s32 sp8[5] = { 1, 2, 4, 8, 16 };

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 10 * sizeof(M443DllCameraStruct), MEMORY_DEFAULT_NUM);
    var_r28 = object->data;
    memset(var_r28, 0, 10 * sizeof(M443DllCameraStruct));
    object->model[0] = Hu3DHookFuncCreate(fn_1_3D78);
    Hu3DModelLayerSet(*object->model, 0);
    Hu3DModelCameraSet(*object->model, 0x1E);
    for (var_r31 = var_r28, var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
        var_r31->unk_00 = 1;
        var_r31->unk_04 = var_r30 * 0x64;
        var_r31->unk_10 = 41.5f;
        var_r31->unk_14 = 100.0f;
        var_r31->unk_18 = 60000.0f;
        var_r31->unk_1C.x = 0.0f;
        var_r31->unk_1C.y = 0.0f;
        var_r31->unk_1C.z = 0.0f;
        var_r31->unk_28.x = -15.0f;
        var_r31->unk_28.y = 0.0f;
        var_r31->unk_28.z = 0.0f;
        var_r31->unk_34 = 1000.0f;
        var_r31->unk_40 = 1.0f;
        var_r31->unk_44 = sp1C[var_r30][0];
        var_r31->unk_48 = sp1C[var_r30][1];
        var_r31->unk_4C = sp1C[var_r30][2];
        var_r31->unk_50 = sp1C[var_r30][3];
        var_r31->unk_3C = var_r31->unk_0C = sp8[var_r30];
        var_r31->unk_08 = var_r30;
        var_r31->unk_38 = var_r30;
    }
    object->work[1] = 0;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        lbl_1_bss_10[var_r30] = espEntry(0x4A001E, 0x12C, 0);
        espPosSet(lbl_1_bss_10[var_r30], 288.0, 240.0);
        if (var_r30 != 0) {
            espScaleSet(lbl_1_bss_10[var_r30], 0.22499999403953552, 60.0);
        }
        else {
            espScaleSet(lbl_1_bss_10[var_r30], 72.0, 0.25);
        }
        espColorSet(lbl_1_bss_10[var_r30], 0, 0, 0);
        espTPLvlSet(lbl_1_bss_10[var_r30], 1.0);
        espDispOff(lbl_1_bss_10[var_r30]);
    }
    object->work[0]++;
    fn_1_3770(object);
    object->func = fn_1_3710;
}

void fn_1_3710(omObjData *arg0)
{
    M443DllWork *sp8 = arg0->data;
    s32 spC[4] = { 0x100, 0x200, 0x400, 0x800 };
    fn_1_3770(arg0);
}

void fn_1_3770(omObjData *arg0)
{
    float var_f31;

    M443DllCameraStruct *var_r31;
    s32 var_r30;
    s32 var_r29;
    M443DllCameraStruct *var_r28;
    s32 var_r26;
    u32 var_r25;
    s32 var_r24;
    s32 var_r23;
    u32 var_r22;
    u32 var_r21;

    var_r28 = arg0->data;
    {
        s32 sp40[4] = { 2, 4, 8, 16 };
        u32 sp30[4];
        s32 sp20[4];
        float sp18[2];
        float sp10[2];
        float sp8[2];

        var_r24 = 0;
        var_r26 = 0;
        memcpy(&var_r28[5], var_r28, 5 * sizeof(M443DllCameraStruct));
        switch (arg0->work[1]) {
            case 0:
                break;
            case 1:
                var_r26 |= 1;
                break;
            case 2:
                var_r26 |= 1;
            case 3:
                var_r24 = 1;
            case 4:
                var_r26 |= 0x1E;
                break;
        }
        if (var_r24 != 0) {
            Hu3DModelAttrReset(arg0->model[0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            sp30[var_r30] = var_r28[var_r30 + 6].unk_04;
            sp20[var_r30] = var_r30;
        }
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            for (var_r29 = var_r30 + 1; var_r29 < 4; var_r29++) {
                if ((var_r30 != var_r29) && (sp30[var_r30] > sp30[var_r29])) {
                    var_r25 = sp30[var_r30];
                    sp30[var_r30] = sp30[var_r29];
                    sp30[var_r29] = var_r25;
                    var_r25 = sp20[var_r30];
                    sp20[var_r30] = sp20[var_r29];
                    sp20[var_r29] = var_r25;
                }
            }
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            var_r28[sp20[var_r30] + 6].unk_3C = sp40[var_r30];
            var_r28[sp20[var_r30] + 6].unk_38 = var_r30 + 1;
        }
        Hu3DCamera[5].fov = -1.0f;
        for (var_r31 = &var_r28[5], var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
            if ((var_r31->unk_00 == 0) || ((var_r26 & var_r31->unk_0C) == 0)) {
                Hu3DCamera[var_r31->unk_38].fov = -1.0f;
            }
            else {
                var_f31 = 1.2f * ((var_r31->unk_4C / 640.0f) / (var_r31->unk_50 / 480.0f));
                sp18[0] = var_r31->unk_4C * var_r31->unk_40;
                sp18[1] = var_r31->unk_50 * var_r31->unk_40;
                Hu3DCameraPerspectiveSet(var_r31->unk_3C, var_r31->unk_10, var_r31->unk_14, var_r31->unk_18, var_f31);
                Hu3DCameraViewportSet(
                    var_r31->unk_3C, var_r31->unk_44 - (0.5f * sp18[0]), var_r31->unk_48 - (0.5f * sp18[1]), sp18[0], sp18[1], 0.0f, 1.0f);
                sp10[0] = var_r31->unk_44 - (0.5f * sp18[0]);
                sp10[1] = var_r31->unk_48 - (0.5f * sp18[1]);
                sp8[0] = var_r31->unk_44 + (0.5f * sp18[0]);
                sp8[1] = var_r31->unk_48 + (0.5f * sp18[1]);
                if (sp10[0] < 0.0f) {
                    sp10[0] = 0.0f;
                }
                if (sp10[1] < 0.0f) {
                    sp10[1] = 0.0f;
                }
                if (sp8[0] > 640.0f) {
                    sp8[0] = 640.0f;
                }
                if (sp8[1] > 480.0f) {
                    sp8[1] = 480.0f;
                }
                sp8[0] -= sp10[0];
                sp8[1] -= sp10[1];
                Hu3DCameraScissorSet(var_r31->unk_3C, sp10[0], sp10[1], sp8[0], sp8[1]);
                var_r29 = var_r31->unk_38;
                CenterM[var_r29].x = var_r31->unk_1C.x;
                CenterM[var_r29].y = var_r31->unk_1C.y;
                CenterM[var_r29].z = var_r31->unk_1C.z;
                CRotM[var_r29].x = var_r31->unk_28.x;
                CRotM[var_r29].y = var_r31->unk_28.y;
                CRotM[var_r29].z = var_r31->unk_28.z;
                CZoomM[var_r29] = var_r31->unk_34;
            }
        }
    }
    if (arg0->work[1] == 4) {
        espDispOn(lbl_1_bss_10[0]);
        espDispOn(lbl_1_bss_10[1]);
        return;
    }
    espDispOff(lbl_1_bss_10[0]);
    espDispOff(lbl_1_bss_10[1]);
}

GXColor lbl_1_data_208 = { 0x00, 0x00, 0x00, 0x00 };

void fn_1_3D78(ModelData *arg0, Mtx arg1)
{
    Mtx spC;

    MTXIdentity(spC);
    GXLoadPosMtxImm(spC, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, lbl_1_data_208);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-45000.0f, 30000.0f, -59900.0f);
    GXPosition3f32(45000.0f, 30000.0f, -59900.0f);
    GXPosition3f32(45000.0f, -30000.0f, -59900.0f);
    GXPosition3f32(-45000.0f, -30000.0f, -59900.0f);
}

void fn_1_3FE8(u32 arg0)
{
    lbl_1_bss_68->work[1] = arg0;
}

u32 fn_1_3FFC(void)
{
    return lbl_1_bss_68->work[1];
}

M443DllCameraStruct *fn_1_4010(s32 arg0)
{
    M443DllCameraStruct *var_r31;
    s32 var_r30;
    M443DllCameraStruct *var_r29;

    var_r29 = lbl_1_bss_68->data;
    for (var_r31 = var_r29, var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
        if (var_r31->unk_0C & arg0) {
            break;
        }
    }
    if (var_r30 >= 5) {
        OSReport("M443:Camera Flag Error!!\n");
        return NULL;
    }
    return var_r31;
}

M443DllCameraStruct *fn_1_40AC(s32 arg0)
{
    M443DllCameraStruct *var_r31;
    s32 var_r30;
    M443DllCameraStruct *var_r29;

    var_r29 = lbl_1_bss_68->data;
    for (var_r31 = &var_r29[5], var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
        if (var_r31->unk_0C & arg0) {
            break;
        }
    }
    if (var_r30 >= 5) {
        OSReport("M443:Camera Flag Error!!\n");
        return NULL;
    }
    return var_r31;
}

// Get camera
M443DllCameraStruct *fn_1_4148(u32 arg0)
{
    M443DllCameraStruct *var_r31 = lbl_1_bss_68->data;
    if (arg0 >= 5) {
        OSReport("M443:Camera No. Error!!\n");
        return NULL;
    }
    return &var_r31[arg0];
}

M443DllCameraStruct *fn_1_41B0(u32 arg0)
{
    M443DllCameraStruct *var_r31 = lbl_1_bss_68->data;
    if (arg0 >= 5) {
        OSReport("M443:Camera No. Error!!\n");
        return NULL;
    }
    return &var_r31[arg0 + 5];
}

void fn_1_421C(s32 arg0, s32 arg1)
{
    M443DllCameraStruct *var_r31;
    s32 var_r30;
    M443DllCameraStruct *var_r28;
    M443DllCameraStruct *var_r27;

    s32 var_r29 = 0;
    if (arg0 >= 0) {
        var_r27 = lbl_1_bss_68->data;
        var_r28 = &var_r27[5];
        for (var_r31 = var_r28, var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
            if (var_r31->unk_0C & arg1) {
                var_r29 |= var_r31->unk_3C;
            }
        }
        Hu3DModelCameraSet(arg0, var_r29);
    }
}

s32 fn_1_42B4(void)
{
    return ((M443DllWork *)lbl_1_bss_70->data)->unk_00;
}

u32 fn_1_42CC(void)
{
    return ((M443DllWork *)lbl_1_bss_70->data)->unk_0C;
}

u32 fn_1_42E4(void)
{
    return ((M443DllWork *)lbl_1_bss_70->data)->unk_14;
}

u32 fn_1_42FC(void)
{
    return ((M443DllWork *)lbl_1_bss_70->data)->unk_28;
}

void fn_1_4314(s32 arg0, float arg8)
{
    M443DllWork *var_r31 = lbl_1_bss_70->data;

    if (fn_1_42E4() == 2) {
        var_r31->unk_44[arg0] = arg8;
    }
}

s32 fn_1_4368(s32 arg0)
{
    M443DllWork *var_r31 = lbl_1_bss_70->data;

    if (var_r31->unk_54 == 1) {
        return var_r31->unk_34[arg0];
    }
    return -1;
}

void fn_1_43AC(s32 arg0)
{
    ((M443DllWork *)lbl_1_bss_70->data)->unk_58 |= (1 << ((arg0 & 7) * 4));
}

void fn_1_43DC(s32 arg0)
{
    ((M443DllWork *)lbl_1_bss_70->data)->unk_5C |= (1 << ((arg0 & 3) * 4));
}

s32 fn_1_440C(void)
{
    return MGSeqStatGet(lbl_1_bss_58) == 0;
}

void fn_1_4444(Vec *arg0, Vec *arg1)
{
    Vec sp10;
    float var_f30;

    VECSubtract(arg1, arg0, &sp10);
    Center = *arg1;
    var_f30 = (sp10.x * sp10.x) + (sp10.z * sp10.z);
    CRot.x = atan2d(sp10.y, sqrtf(var_f30));
    CRot.y = atan2d(-sp10.x, -sp10.z);
    CRot.z = 0.0f;
    CZoom = VECMag(&sp10);
}

void fn_1_464C(float arg8, float arg9, float argA, float argB, float argC, float argD)
{
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    float var_f30;

    sp3C.x = arg8;
    sp3C.y = arg9;
    sp3C.z = argA;
    sp30.x = argB;
    sp30.y = argC;
    sp30.z = argD;
    VECSubtract(&sp30, &sp3C, &sp24);
    Center = sp30;
    var_f30 = (sp24.x * sp24.x) + (sp24.z * sp24.z);
    CRot.x = atan2d(sp24.y, sqrtf(var_f30));
    CRot.y = atan2d(-sp24.x, -sp24.z);
    CRot.z = 0.0f;
    CZoom = VECMag(&sp24);
}

float fn_1_488C(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;
    float var_f29;

    var_f30 = fmod(arg9 - arg8, 360.0);
    var_f31 = var_f30;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f29 = fmod(arg8 + (argA * var_f31), 360.0);
    var_f31 = var_f29;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    return var_f31;
}

float fn_1_49A8(float arg8, float arg9)
{
    float var_f31;
    float var_f30;

    var_f30 = fmod(arg9 - arg8, 360.0);
    var_f31 = var_f30;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}
