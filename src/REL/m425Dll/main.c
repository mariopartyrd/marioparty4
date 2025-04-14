#define HUSPR_USE_OLD_DEFS
#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXVert.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "math.h"
#include "string.h"

#include "REL/m425Dll.h"

SHARED_SYM extern u8 texMtxTbl[]; // TODO maybe put in hsfdraw.h?

typedef struct M425DllWork {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    char unk07[2];
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
    u8 unk_0C;
    char unk0D;
    s16 unk_0E;
    float unk_10;
    float unk_14;
    Vec unk_18;
    Vec unk_24;
    Vec unk_30;
    float unk_3C[8];
    s32 unk_5C;
    float unk_60;
    s32 unk_64;
    s32 unk_68;
} M425DllWork; /* size = 0x6C */

typedef struct M425DllWork2 {
    char unk00[4];
    Vec unk_04;
    Vec unk_10;
    Vec unk_1C;
    Vec unk_28;
    float unk_34;
    float unk_38;
    float unk_3C;
    float unk_40;
    float unk_44;
    float unk_48;
    char unk4C[0x18];
    float unk_64;
    float unk_68;
    float unk_6C;
    char unk70[4];
    s16 unk_74;
    s16 unk_76;
} M425DllWork2; /* size = 0x78 */

typedef struct M425DllUnkStruct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    char unk06[0x42];
} M425DllUnkStruct; /* size = 0x48 */

typedef struct M425DllUnkStruct2 {
    AnimData *unk_00;
    s16 unk_04;
    Vec unk_08;
    Mtx unk_14;
    Vec2f *unk_44;
    s16 unk_48;
} M425DllUnkStruct2; /* size = 0x4C */

typedef struct M425DllUnkStruct3 {
    char unk00[0xC];
    s16 unk_0C;
    void *unk_10;
    Vec *unk_14;
    GXColor *unk_18;
    Vec *unk_1C;
    GXColor unk_20;
    GXColor unk_24;
    s16 unk_28;
    s16 unk_2A;
    M425DllUnkStruct2 *unk_2C;
} M425DllUnkStruct3; /* size = 0x30 */

typedef struct M425DllUnkBss10Struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ char pad_01[1];
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ float unk_04;
    /* 0x08 */ Vec unk_08;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
    /* 0x1C */ float unk_1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ float unk_30;
    /* 0x34 */ float unk_34;
    /* 0x38 */ float unk_38;
    /* 0x3C */ float unk_3C;
    /* 0x40 */ float unk_40;
    union {
        /* 0x44 */ s16 unk_44[0x20];
        struct {
            float unk_44f;
            float unk_48;
            char unk4C[4];
            float unk_50;
            char unk54[0x30];
        };
    };
} M425DllUnkBss10Struct; /* size = 0x84 */

void fn_1_1B40(omObjData *object);
void fn_1_2784(omObjData *object);
void fn_1_2870(omObjData *object);
void fn_1_2A94(s16 arg0, Vec *arg1, Vec *arg2, float arg8);
void fn_1_2B2C(omObjData *object);
void fn_1_2E78(omObjData *object);
void fn_1_33E0(omObjData *object);
void fn_1_3764(omObjData *object);
s16 fn_1_3ED0(s32 arg0, s16 arg1, ParticleHook arg2);
void fn_1_3F80(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_460(omObjData *object);
void fn_1_480(omObjData *object);
void fn_1_4A88(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_5044(s16 arg0);
void fn_1_573C(Vec2f **arg0, s16 arg1, Vec2f *arg2);
void fn_1_57D4(ModelData *model, Mtx matrix);
void fn_1_5C20(ModelData *model, Mtx matrix);
s32 fn_1_64D4(void);
void fn_1_8E4(omObjData *object);
void fn_1_F48(omObjData *object);
void fn_1_FA8(omObjData *object);

s16 lbl_1_data_0 = -1;
Vec lbl_1_data_4 = { -200.0f, 2500.0f, 1200.0f };
Vec lbl_1_data_10 = { 0.2f, -0.8f, -0.2f };
float lbl_1_data_1C[9] = { 0.0f, 2500.0f, 1500.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };
GXColor lbl_1_data_40 = { 0xFF, 0xFF, 0xFF, 0xFF };

omObjData *lbl_1_bss_668;
omObjData *lbl_1_bss_664;
// M425DllWork2
omObjData *lbl_1_bss_660;
omObjData *lbl_1_bss_65C;
// M425DllWork
omObjData *lbl_1_bss_64C[4];
u16 lbl_1_bss_648;
s16 lbl_1_bss_646;
s16 lbl_1_bss_644;
s16 lbl_1_bss_642;
s16 lbl_1_bss_640;
M425DllUnkBss10Struct lbl_1_bss_10[0xC];
float lbl_1_bss_C;
float lbl_1_bss_8;
float lbl_1_bss_4;
char lbl_1_bss_0[4];

void ObjectSetup(void)
{
    s32 var_r31;
    Process *process;
    omObjData *object;
    s32 var_r28;
    LightData *var_r27;
    CameraData *var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 sp8[4] = { 0, 0, 0, 0 };

    OSReport("******* M425ObjectSetup *********\n");
    Hu3DLighInit();
    var_r24 = Hu3DGLightCreateV(&lbl_1_data_4, &lbl_1_data_10, &lbl_1_data_40);
    Hu3DGLightInfinitytSet(var_r24);
    var_r27 = Hu3DGlobalLight;
    var_r27->unk_00 |= 0x8000;
    process = omInitObjMan(0x32, 0x2000);
    var_r25 = frand() & 0x1F;
    for (var_r31 = 0; var_r31 < var_r25; var_r31++) {
        fn_1_64D4();
    }
    CRot.x = 8.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 430.0f;
    Center.z = -400.0f;
    CZoom = 1650.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lbl_1_bss_664 = omAddObjEx(process, 0x7FDA, 0, 0, -1, omOutView);
    var_r26 = Hu3DCamera;
    var_r26->fov = -1.0f;
    lbl_1_bss_668 = omAddObjEx(process, 0x10, 8, 0, -1, fn_1_460);
    lbl_1_bss_65C = omAddObjEx(process, 0x20, 0x10, 0, -1, fn_1_FA8);
    lbl_1_bss_660 = omAddObjEx(process, 0x50, 0x10, 0, -1, fn_1_2784);
    fn_1_6A0C(process, 0x40);
    omMakeGroupEx(process, 0, 4);
    omGetGroupMemberListEx(process, 0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        object = omAddObjEx(process, 0x30, 2, 0xA, 0, fn_1_2B2C);
        lbl_1_bss_64C[var_r31] = object;
        object->work[0] = var_r31;
        object->work[1] = GWPlayerCfg[var_r31].group;
        for (var_r28 = object->work[1] * 2; var_r28 < 4; var_r28++) {
            if (sp8[var_r28] == 0) {
                object->work[1] = var_r28;
                sp8[var_r28]++;
                break;
            }
        }
    }
    omGameSysInit(process);
    HuAudSndGrpSet(0x32);
}

void fn_1_460(omObjData *object)
{
    lbl_1_bss_648 = 0;
    object->func = fn_1_480;
}

void fn_1_480(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    CameraData *var_r30;

    switch (lbl_1_bss_648) {
        case 0:
            sp14.x = -250.0f;
            sp14.y = 225.0f;
            sp14.z = 200.0f;
            sp8.x = 22.0f;
            sp8.y = 10.0f;
            sp8.z = 0.0f;
            var_f31 = 500.0f;
            fn_1_2A94(1, &sp14, &sp8, var_f31);
            lbl_1_bss_C = -4.866667f;
            lbl_1_bss_8 = 600.0f;
            sp14.x = -300.0f;
            sp14.y = lbl_1_bss_8;
            sp14.z = 0.0f;
            fn_1_6CD0(0, &sp14);
            sp14.x = 300.0f;
            fn_1_6CD0(1, &sp14);
            var_r30 = Hu3DCamera;
            var_r30->fov = 45.0f;
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            lbl_1_bss_648++;
            break;
        case 1:
            lbl_1_bss_8 += lbl_1_bss_C;
            lbl_1_bss_C += -2.4333334f;
            if (lbl_1_bss_8 < 0.0f) {
                lbl_1_bss_8 = 0.0f;
                lbl_1_bss_648++;
                lbl_1_bss_640 = 0x3C;
                fn_1_10DB4(0);
                fn_1_10DB4(1);
                fn_1_10E3C(0);
            }
            sp14.x = -300.0f;
            sp14.y = lbl_1_bss_8;
            sp14.z = 0.0f;
            fn_1_6CD0(0, &sp14);
            sp14.x = 300.0f;
            fn_1_6CD0(1, &sp14);
            break;
        case 2:
            if (--lbl_1_bss_640 == 0) {
                sp14.x = 0.0f;
                sp14.y = 430.0f;
                sp14.z = -400.0f;
                sp8.x = 8.0f;
                sp8.y = 0.0f;
                sp8.z = 0.0f;
                var_f31 = 1650.0f;
                lbl_1_bss_640 = 0x48;
                fn_1_2A94(0x3C, &sp14, &sp8, var_f31);
                lbl_1_bss_648++;
            }
            break;
        case 3:
            if (--lbl_1_bss_640 == 0) {
                lbl_1_bss_648 = 4;
                object->func = fn_1_8E4;
                lbl_1_bss_646 = lbl_1_bss_644 = -1;
            }
            break;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_F48;
    }
}

s32 lbl_1_data_68 = -1;
s32 lbl_1_data_6C[0xA] = { 0, 2, 3, 5, 6, 8, 0xA, 9, 0x17, 0x18 };
Vec lbl_1_data_94[4] = {
    { -350.0f, 800.0f, 100.0f },
    { -200.0f, 1000.0f, 0.0f },
    { 200.0f, 1200.0f, 0.0f },
    { 350.0f, 1400.0f, 100.0f },
};

void fn_1_8E4(omObjData *object)
{
    s16 sp8[2];
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s16 var_r26;
    s16 var_r25;

    switch (lbl_1_bss_648) {
        case 4:
            if (lbl_1_bss_644 == -1) {
                lbl_1_bss_642 = 0x708;
                lbl_1_bss_644 = MGSeqCreate(3, 0);
                MGSeqPosSet(lbl_1_bss_644, 320.0f, 240.0f);
            }
            else {
                if (MGSeqStatGet(lbl_1_bss_644) == 0) {
                    lbl_1_bss_644 = -1;
                    lbl_1_bss_648++;
                    lbl_1_bss_646 = MGSeqCreate(1, lbl_1_bss_642 / 60, -1, -1);
                }
            }
            if ((lbl_1_data_68 == -1) && ((MGSeqStatGet(lbl_1_bss_644) & 0x10) != 0)) {
                lbl_1_data_68 = HuAudSeqPlay(0x48);
            }
            break;
        case 5:
            var_r30 = 0;
            lbl_1_bss_642--;
            var_r28 = (lbl_1_bss_642 + 0x3B) / 60;
            if (var_r28 < 0) {
                var_r28 = 0;
            }
            MGSeqParamSet(lbl_1_bss_646, 1, var_r28);
            if (lbl_1_bss_642 < -1) {
                var_r30++;
                if ((fn_1_10CF4(0) == 1000.0f) && (fn_1_10CF4(1) == 1000.0f)) {
                    lbl_1_data_0 = -1;
                }
                else {
                    var_f31 = fn_1_10CF4(1);
                    if (fn_1_10CF4(0) <= var_f31) {
                        lbl_1_data_0 = 0;
                    }
                    else {
                        lbl_1_data_0 = 1;
                    }
                }
            }
            for (var_r31 = 0; var_r31 < 2; var_r31++) {
                if (!(fn_1_10CF4(var_r31) > 0.0f)) {
                    lbl_1_data_0 = var_r31;
                    var_r30++;
                }
            }
            if (var_r30 != 0) {
                lbl_1_bss_648++;
            }
            break;
        case 6:
            if (lbl_1_bss_644 == -1) {
                lbl_1_bss_644 = MGSeqCreate(3, 1);
                MGSeqPosSet(lbl_1_bss_644, 320.0f, 240.0f);
                MGSeqParamSet(lbl_1_bss_646, 2, -1);
                HuAudSeqFadeOut(lbl_1_data_68, 0x64);
            }
            else if (MGSeqStatGet(lbl_1_bss_644) == 0) {
                lbl_1_bss_644 = -1;
                lbl_1_bss_640 = 1;
                lbl_1_bss_648++;
            }
            break;
        case 7:
            if (--lbl_1_bss_640 <= 0) {
                lbl_1_bss_644 = -1;
                lbl_1_bss_648++;
            }
            break;
        case 8:
            if (lbl_1_data_0 != -1) {
                for (var_r31 = 0, var_r29 = 0; var_r31 < 4; var_r31++) {
                    if (lbl_1_data_0 == OM_GET_DATA_PTR(lbl_1_bss_64C[var_r31], M425DllWork)->unk_02) {
                        sp8[var_r29] = OM_GET_DATA_PTR(lbl_1_bss_64C[var_r31], M425DllWork)->unk_01;
                        var_r29++;
                        GWPlayerCoinWinAdd(var_r31, 10);
                    }
                }
                lbl_1_bss_644 = MGSeqCreate(5, 3, sp8[0], sp8[1], -1, -1);
                HuAudSStreamPlay(1);
            }
            else {
                lbl_1_bss_644 = MGSeqCreate(3, 2);
                HuAudSStreamPlay(4);
            }
            lbl_1_bss_640 = 0xD2;
            lbl_1_bss_648++;
            break;
        case 9:
            if (--lbl_1_bss_640 <= 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                object->func = fn_1_F48;
            }
            break;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_F48;
    }
}

void fn_1_F48(omObjData *object)
{
    if (WipeStatGet() == 0) {
        CharModelKill(-1);
        MGSeqKill(lbl_1_bss_646);
        MGSeqKillAll();
        fn_1_6C08();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_FA8(omObjData *object)
{
    M425DllUnkBss10Struct *var_r31;
    s32 var_r30;
    s16 *var_r28;
    s32 var_r27;
    s32 var_r26;
    Vec sp8[] = {
        { 475.0f, 800.0f, -1400.0f },
        { -300.0f, 900.0f, -1400.0f },
        { 300.0f, 875.0f, -1450.0f },
        { -575.0f, 850.0f, -1550.0f },
        { 350.0f, 750.0f, -1500.0f },
        { -450.0f, 775.0f, -1550.0f },
        { 325.0f, 725.0f, -1450.0f },
        { -525.0f, 725.0f, -1500.0f },
        { 575.0f, 850.0f, -1550.0f },
        { -350.0f, 750.0f, -1500.0f },
        { 450.0f, 775.0f, -1550.0f },
        { -325.0f, 725.0f, -1450.0f },
        { 525.0f, 725.0f, -1500.0f },
        { -475.0f, 800.0f, -1400.0f },
        { 300.0f, 900.0f, -1400.0f },
        { -300.0f, 875.0f, -1450.0f },
    };

    var_r30 = Hu3DModelCreateFile(0x380000);
    object->model[0] = var_r30;
    var_r30 = Hu3DModelCreateFile(0x380001);
    object->model[1] = var_r30;
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    var_r30 = Hu3DHookFuncCreate(fn_1_57D4);
    object->model[2] = var_r30;
    fn_1_5044(var_r30);
    var_r30 = fn_1_3ED0(0x1E0020, 0xC8, fn_1_4A88);
    object->model[3] = var_r30;
    Hu3DParticleBlendModeSet(var_r30, 1);
    var_r30 = fn_1_3ED0(0x380005, 1, fn_1_3F80);
    object->model[5] = var_r30;
    Hu3DParticleBlendModeSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 6);
    var_r28 = ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_1C;
    var_r28[1] = 0;
    var_r30 = fn_1_3ED0(0x380008, 0xA, fn_1_3F80);
    object->model[6] = var_r30;
    Hu3DParticleBlendModeSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 6);
    var_r28 = ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_1C;
    var_r28[1] = 1;
    var_r30 = fn_1_3ED0(0x380007, 4, fn_1_3F80);
    object->model[7] = var_r30;
    Hu3DParticleBlendModeSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 6);
    var_r28 = ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_1C;
    var_r28[1] = 2;
    var_r30 = fn_1_3ED0(0x380006, 6, fn_1_3F80);
    object->model[8] = var_r30;
    Hu3DParticleBlendModeSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 6);
    var_r28 = ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_1C;
    var_r28[1] = 3;
    for (var_r27 = 0; var_r27 < 0xC; var_r27++) {
        var_r31 = &lbl_1_bss_10[var_r27];
        var_r30 = Hu3DModelCreateFile(0x380002);
        var_r31->unk_00 = var_r30;
        var_r31->unk_08.x = sp8[var_r27].x;
        var_r31->unk_08.y = sp8[var_r27].y;
        var_r31->unk_08.z = sp8[var_r27].z;
        Hu3DModelPosSet(var_r30, var_r31->unk_08.x, var_r31->unk_08.y, var_r31->unk_08.z);
        Hu3DMotionSpeedSet(var_r30, 6.0f);
        var_r31->unk_02 = var_r31->unk_03 = 0;
        var_r31->unk_14 = var_r31->unk_18 = var_r31->unk_1C = 0.0f;
        var_r31->unk_20 = var_r31->unk_24 = var_r31->unk_28 = 1.0f;
        var_r31->unk_38 = var_r31->unk_3C = var_r31->unk_40 = 0.0f;
        var_r31->unk_2C = var_r31->unk_08.x;
        var_r31->unk_30 = var_r31->unk_08.y;
        var_r31->unk_34 = var_r31->unk_08.z;
        if ((var_r27 & 1) != 0) {
            var_r31->unk_18 = 90.0f;
            var_r31->unk_08.y += 650.0;
            var_r31->unk_08.x -= 1400.0;
        }
        else {
            var_r31->unk_18 = 90.0f;
        }
        var_r31->unk_18 += 10.0 * (3.0517578125e-05 * (float)((u16)frand() - 0x8000));
        var_r31->unk_08.z -= 400.0;
        var_r31->unk_04 = 100.0 * (0.10000000149011612 + (0.019999999552965164 * (1.52587890625e-05 * (float)(s32)(u16)frand())));
        for (var_r26 = 0; var_r26 < 0x20; var_r26++) {
            var_r31->unk_44[var_r26] = 0;
        }
        var_r31->unk_50 = var_r31->unk_04;
    }
    HuAudFXPlay(0x633);
    HuAudFXPlay(0x635);
    object->func = fn_1_1B40;
}

void fn_1_14CC(Mtx arg0, float arg8, float arg9, float argA)
{
    Mtx sp38;
    Mtx sp8;
    if (argA != 0.0f) {
        MTXRotRad(arg0, 0x5A, MTXDegToRad(argA));
    }
    else {
        MTXIdentity(arg0);
    }
    if (arg8 != 0.0f) {
        MTXRotRad(sp38, 0x58, MTXDegToRad(arg8));
        MTXConcat(sp38, arg0, arg0);
    }
    if (arg9 != 0.0f) {
        MTXRotRad(sp8, 0x59, MTXDegToRad(arg9));
        MTXConcat(sp8, arg0, arg0);
    }
}

float fn_1_15EC(float arg8, float arg9)
{
    float var_f30 = 360.0f;
    float var_f31 = 180.0 * (atan2f(arg9, arg8) / M_PI);
    if (var_f31 < 0.0f) {
        var_f31 += var_f30;
    }
    else if (var_f31 >= var_f30) {
        var_f31 -= var_f30;
    }
    return var_f31;
}

void fn_1_16B0(Mtx var_r30, Vec *var_r31)
{
    float var_f29;
    float var_f25;

    var_r31->x = fn_1_15EC(var_r30[2][2], var_r30[1][2]);
    var_r31->z = fn_1_15EC(var_r30[0][0], var_r30[0][1]);
    var_f29 = -var_r30[0][2];
    var_f25 = sqrtf((1.0 - (var_f29 * var_f29)) < 0.0 ? (-1.0 - (var_f29 * var_f29)) : (1.0 - (var_f29 * var_f29)));
    if ((var_r31->x > 90.0f) && (var_r31->x < 270.0f) && (var_r31->z > 90.0f) && (var_r31->z < 270.0f)) {
        var_r31->x = fmod(180.0f + var_r31->x, 360.0);
        var_r31->z = fmod(180.0f + var_r31->z, 360.0);
        var_f25 = -var_f25;
    }
    var_r31->y = fn_1_15EC(var_f25, var_f29);
}

void fn_1_1B40(omObjData *object)
{
    Mtx spCC;
    Mtx sp9C;
    Mtx sp6C;
    Vec sp60;
    M425DllUnkBss10Struct *var_r31;
    s32 var_r27;

    for (var_r27 = 0; var_r27 < 0xC; var_r27++) {
        var_r31 = &lbl_1_bss_10[var_r27];
        switch (var_r31->unk_03) {
            case 0:
                if (var_r31->unk_04 < var_r31->unk_50) {
                    var_r31->unk_04 += 0.4f;
                }
                if ((s32)(64.0 * (1.52587890625e-05 * (float)fn_1_64D4())) == 0) {
                    Hu3DMotionTimeSet(var_r31->unk_00, 0.0f);
                }
                if (Hu3DMotionEndCheck(var_r31->unk_00) != 0) {
                    var_r31->unk_3C = -2.92f;
                }
                else {
                    var_r31->unk_3C = -0.48666668f;
                }
                var_r31->unk_44f += 0.10000000149011612 * (3.0517578125e-05 * (float)((u16)frand() - 0x8000));
                var_r31->unk_48 += var_r31->unk_44f;
                if (var_r31->unk_48 > 180.0f) {
                    var_r31->unk_48 -= 180.0f;
                }
                if (var_r31->unk_48 < -180.0f) {
                    var_r31->unk_48 += 180.0f;
                }
                var_r31->unk_14 = -30.0 * sind(var_r31->unk_48) * sind(var_r31->unk_18);
                var_r31->unk_1C = -30.0 * sind(var_r31->unk_48) * cosd(var_r31->unk_18);
                if ((var_r31->unk_08.y <= 700.0f) || (fabs(var_r31->unk_08.x) > 2000.0)) {
                    var_r31->unk_3C = 0.0f;
                    var_r31->unk_44[6] = (s32)(20.0 * (3.0517578125e-05 * (float)(fn_1_64D4() - 0x8000))) + 0xB4;
                    var_r31->unk_04 *= 0.75f;
                    var_r31->unk_03++;
                }
                break;
            case 1:
                var_r31->unk_18 += 1.0f;
                var_r31->unk_14 = 0.0f;
                var_r31->unk_1C = 60.0 * sind(var_r31->unk_44[6]) * cosd(var_r31->unk_18);
                if (--var_r31->unk_44[6] == 0) {
                    Hu3DModelAttrSet(var_r31->unk_00, HU3D_MOTATTR_LOOP);
                    Hu3DMotionSpeedSet(var_r31->unk_00, 6.0f);
                    var_r31->unk_3C = 5.3533335f;
                    var_r31->unk_03++;
                }
                break;
            case 2:
                if (var_r31->unk_04 > 4.0f) {
                    var_r31->unk_04 -= 0.1f;
                    var_r31->unk_3C += 0.73f;
                }
                var_r31->unk_3C += -0.5475f;
                if (var_r31->unk_3C < 0.0f) {
                    Hu3DModelAttrReset(var_r31->unk_00, HU3D_MOTATTR_LOOP);
                    Hu3DMotionSpeedSet(var_r31->unk_00, 2.0f);
                    var_r31->unk_50 = 100.0 * (0.10000000149011612 + (0.019999999552965164 * (1.52587890625e-05 * (float)(s32)(u16)frand())));
                    var_r31->unk_03 = 0;
                }
                break;
        }
        if (0) {
            s32 var_r31;
            s32 var_r30;
            s32 var_r29;
            float var_f31;
            float var_f20;
            float var_f19;
            float var_f18;

            (void) object;
            (void) object;
            (void) var_r31;
            (void) var_r31;
            (void) var_r31;
            (void) var_r31;
            (void) var_r31;
            (void) var_r31;
            (void) var_r30;
            (void) var_r30;
            (void) var_r30;
            (void) var_r30;
            (void) var_r30;
            (void) var_r30;
            (void) var_r29;
            (void) var_r29;
            (void) var_r29;
            (void) var_r29;
            (void) var_r29;
            (void) var_r29;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f31;
            (void) var_f20;
            (void) var_f20;
            (void) var_f20;
            (void) var_f19;
            (void) var_f19;
            (void) var_f19;
            (void) var_f18;
            (void) var_f18;
            (void) var_f18;
        }
        var_r31->unk_38 = var_r31->unk_04 * sind(var_r31->unk_18);
        var_r31->unk_40 = var_r31->unk_04 * cosd(var_r31->unk_18);
        var_r31->unk_08.x += var_r31->unk_38;
        var_r31->unk_08.y += var_r31->unk_3C;
        var_r31->unk_08.z += var_r31->unk_40;
        Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_08.x, var_r31->unk_08.y, var_r31->unk_08.z);
        fn_1_14CC(spCC, var_r31->unk_14, -var_r31->unk_18, var_r31->unk_1C);
        fn_1_16B0(spCC, &sp60);
        Hu3DModelRotSetV(var_r31->unk_00, &sp60);
    }
}

void fn_1_2784(omObjData *object)
{
    M425DllWork2 *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M425DllWork2), MEMORY_DEFAULT_NUM);
    object->data = work;
    work->unk_76 = work->unk_74 = 0;
    work->unk_10.x = work->unk_28.x = 8.0f;
    work->unk_10.y = work->unk_28.y = 0.0f;
    work->unk_10.z = work->unk_28.z = 0.0f;
    work->unk_04.x = work->unk_1C.x = 0.0f;
    work->unk_04.y = work->unk_1C.y = 430.0f;
    work->unk_04.z = work->unk_1C.z = -400.0f;
    work->unk_64 = work->unk_68 = 1650.0f;
    object->func = fn_1_2870;
}

void fn_1_2870(omObjData *object)
{
    float var_f31;
    M425DllWork2 *work;

    work = object->data;
    if (work->unk_76 != 0) {
        work->unk_76--;
        var_f31 = (float)(work->unk_74 - work->unk_76) / work->unk_74;
        var_f31 = sind((90.0f * var_f31));
        work->unk_04.x = work->unk_1C.x + (var_f31 * (work->unk_34 - work->unk_1C.x));
        work->unk_04.y = work->unk_1C.y + (var_f31 * (work->unk_38 - work->unk_1C.y));
        work->unk_04.z = work->unk_1C.z + (var_f31 * (work->unk_3C - work->unk_1C.z));
        work->unk_10.x = work->unk_28.x + (var_f31 * (work->unk_40 - work->unk_28.x));
        work->unk_10.y = work->unk_28.y + (var_f31 * (work->unk_44 - work->unk_28.y));
        work->unk_10.z = work->unk_28.z + (var_f31 * (work->unk_48 - work->unk_28.z));
        work->unk_64 = work->unk_68 + (var_f31 * (work->unk_6C - work->unk_68));
    }
    CRot.x = work->unk_10.x;
    CRot.y = work->unk_10.y;
    CRot.z = work->unk_10.z;
    Center.x = work->unk_04.x;
    Center.y = work->unk_04.y;
    Center.z = work->unk_04.z;
    CZoom = work->unk_64;
}

void fn_1_2A94(s16 arg0, Vec *arg1, Vec *arg2, float arg8)
{
    M425DllWork2 *work = lbl_1_bss_660->data;
    work->unk_74 = arg0;
    work->unk_76 = arg0;
    work->unk_1C = work->unk_04;
    work->unk_34 = arg1->x;
    work->unk_38 = arg1->y;
    work->unk_3C = arg1->z;
    work->unk_28 = work->unk_10;
    work->unk_40 = arg2->x;
    work->unk_44 = arg2->y;
    work->unk_48 = arg2->z;
    work->unk_68 = work->unk_64;
    work->unk_6C = arg8;
}

void fn_1_2B2C(omObjData *object)
{
    s32 sp8; // ! - uninitialized
    M425DllWork *var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M425DllWork), MEMORY_DEFAULT_NUM);
    object->data = var_r31;
    var_r31->unk_00 = object->work[0];
    var_r31->unk_01 = GWPlayerCfg[var_r31->unk_00].character;
    var_r31->unk_02 = GWPlayerCfg[var_r31->unk_00].group;
    var_r31->unk_03 = object->work[1] & 1;
    var_r31->unk_04 = GWPlayerCfg[var_r31->unk_00].pad_idx;
    var_r31->unk_05 = GWPlayerCfg[var_r31->unk_00].iscom;
    var_r31->unk_06 = GWPlayerCfg[var_r31->unk_00].diff;
    var_r31->unk_0E = 0;
    var_r31->unk_0B = 1;
    var_r31->unk_0C = 0;
    memset(var_r31->unk_3C, 0, sizeof(var_r31->unk_3C));
    var_r31->unk_5C = 0;
    var_r31->unk_60 = 1.0f;
    var_r31->unk_64 = 0;
    var_r31->unk_68 = 0;
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if ((var_r29 != var_r31->unk_00) && (var_r31->unk_02 == GWPlayerCfg[var_r29].group)) {
            var_r31->unk_09 = var_r29;
            break;
        }
    }
    var_r27 = object->work[1];
    var_r31->unk_18.x = lbl_1_data_94[var_r27].x;
    var_r31->unk_18.y = lbl_1_data_94[var_r27].y;
    var_r31->unk_18.z = lbl_1_data_94[var_r27].z;
    var_r31->unk_24.x = var_r31->unk_24.y = var_r31->unk_24.z = 0.0f;
    if (var_r31->unk_02 == 0) {
        var_r31->unk_10 = 30.0f;
    }
    else {
        var_r31->unk_10 = -30.0f;
    }
    var_r28 = CharModelCreate(var_r31->unk_01, 4);
    object->model[0] = var_r28;
    Hu3DModelAttrSet(var_r28, HU3D_MOTATTR_LOOP);
    CharModelStepTypeSet(var_r31->unk_01, 1);
    for (var_r29 = 0; var_r29 < 0xA; var_r29++) {
        object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_01, lbl_1_data_6C[var_r29]);
        if (var_r29 == 5) {
            CharModelVoiceEnableSet(var_r31->unk_01, object->motion[var_r29], 0);
        }
    }
    CharModelMotionDataClose(var_r31->unk_01);
    CharModelMotionSet(var_r31->unk_01, object->motion[var_r31->unk_0E]);
    omSetTra(object, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
    Hu3DModelPosSet(var_r28, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
    Hu3DModelRotSet(var_r28, 0.0f, 30.0f, 0.0f);
    HuDataDirClose(sp8);
    object->func = fn_1_2E78;
}

void fn_1_2E78(omObjData *object)
{
    float spC[8];
    s32 sp8;
    M425DllWork *var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r26 = 0;
    sp8 = object->model[0];
    var_r31 = object->data;
    var_r31->unk_30 = var_r31->unk_18;
    if ((lbl_1_bss_648 == 5) && (var_r31->unk_05 != 0)) {
        fn_1_33E0(object);
    }
    fn_1_3764(object);
    switch (lbl_1_bss_648) {
        case 2:
            if (lbl_1_bss_640 == 1) {
                var_r31->unk_0E = 5;
                CharModelMotionShiftSet(var_r31->unk_01, object->motion[var_r31->unk_0E], 0.0f, 8.0f, 0);
                var_r31->unk_24.y = 0.0f;
                var_r31->unk_0B = 0;
            }
            var_r31->unk_68 = 0;
            break;
        case 3:
            if (var_r31->unk_64 != 0) {
                var_r31->unk_18.y = fn_1_10EF8(var_r31->unk_02, var_r31->unk_03, var_r31->unk_18.x, var_r31->unk_18.z);
                var_r31->unk_18.y -= 10.0f;
            }
            else if (fn_1_109EC(var_r31->unk_02, var_r31->unk_03, &var_r31->unk_30, &var_r31->unk_24, &var_r31->unk_18, 0) != 0) {
                if (var_r31->unk_0B == 0) {
                    HuAudFXPlay(0x62F);
                }
                CharModelVoiceEnableSet(var_r31->unk_01, object->motion[5], 1);
                var_r31->unk_0B = 1;
            }
            break;
        case 5:
            if ((var_r31->unk_0E == 5) && (var_r31->unk_0C == 0)) {
                var_r26 = 1;
            }

        case 4:
        case 6:
        case 7:
            if (var_r31->unk_64 != 0) {
                var_r31->unk_18.y = fn_1_10EF8(var_r31->unk_02, var_r31->unk_03, var_r31->unk_18.x, var_r31->unk_18.z);
                var_r31->unk_18.y -= 10.0f;
            }
            else if (fn_1_109EC(var_r31->unk_02, var_r31->unk_03, &var_r31->unk_30, &var_r31->unk_24, &var_r31->unk_18, var_r26) != 0) {
                var_r31->unk_0B = 1;
            }
            break;
        case 8:
            if (var_r31->unk_64 != 0) {
                var_r31->unk_18.y = fn_1_10EF8(var_r31->unk_02, var_r31->unk_03, var_r31->unk_18.x, var_r31->unk_18.z);
                var_r31->unk_18.y -= 10.0f;
                var_r31->unk_0B = 1;
            }
            else if (fn_1_109EC(var_r31->unk_02, var_r31->unk_03, &var_r31->unk_30, &var_r31->unk_24, &var_r31->unk_18, 0) != 0) {
                var_r31->unk_0B = 1;
            }
            if ((var_r31->unk_0B != 0) && (var_r31->unk_0E != 8) && (var_r31->unk_0E != 9)) {
                if (var_r31->unk_02 == lbl_1_data_0) {
                    var_r31->unk_0E = 8;
                }
                else {
                    var_r31->unk_0E = 9;
                }
                CharModelMotionShiftSet(var_r31->unk_01, object->motion[var_r31->unk_0E], 0.0f, 8.0f, 0);
            }
            break;
        case 9:
            if (var_r31->unk_64 != 0) {
                var_r31->unk_18.y = fn_1_10EF8(var_r31->unk_02, var_r31->unk_03, var_r31->unk_18.x, var_r31->unk_18.z);
                var_r31->unk_18.y -= 10.0f;
            }
            else if (fn_1_109EC(var_r31->unk_02, var_r31->unk_03, &var_r31->unk_30, &var_r31->unk_24, &var_r31->unk_18, 0) != 0) {
                var_r31->unk_0B = 1;
            }
            break;
    }
    if (var_r31->unk_18.y < 0.0f) {
        var_r31->unk_18.y = 0.0f;
        var_r31->unk_0B = 1;
    }
    var_r27 = var_r31->unk_5C % 8;
    var_r31->unk_3C[var_r27] = var_r31->unk_18.y;
    if (++var_r31->unk_5C > 8) {
        for (var_r29 = 0; var_r29 < 8; var_r29++) {
            var_r28 = var_r27 - var_r29;
            if (var_r28 < 0) {
                var_r28 += 8;
            }
            spC[var_r29] = var_r31->unk_3C[var_r28];
        }
        for (var_r29 = 1; var_r29 < 8; var_r29++) {
            if (fabs(spC[var_r29] - spC[0]) > 25.0) {
                break;
            }
        }
        if (((var_r31->unk_0E == 0) || (var_r31->unk_0E == 8) || (var_r31->unk_0E == 9)) && (var_r29 >= 8)) {
            var_r31->unk_60 = var_r31->unk_60 - 0.05f;
            if (var_r31->unk_60 < 0.75f) {
                var_r31->unk_60 = 0.75f;
            }
        }
        else {
            var_r31->unk_60 = 1.0f;
        }
    }
    omSetTra(object, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
}

void fn_1_33E0(omObjData *object)
{
    s32 spC;
    s16 sp8;
    M425DllWork *var_r31;
    M425DllWork *var_r30;

    var_r31 = object->data;
    var_r30 = lbl_1_bss_64C[var_r31->unk_09]->data;
    spC = object->model[0];
    sp8 = var_r31->unk_0E;
    switch (var_r31->unk_0E) {
        case 4:
        case 7:
        case 0:
            if (var_r30->unk_0E == 3) {
                if ((var_r30->unk_05 == 0) || ((s32)((0x18 - (var_r31->unk_06 * 3)) * (1.52587890625e-05 * (float)fn_1_64D4())) == 0)) {
                    HuPadBtnDown[var_r31->unk_04] |= 0x100;
                    break;
                }
            }
            else {
                if ((s32)((0x30 - (var_r31->unk_06 * 4)) * (1.52587890625e-05 * (float)fn_1_64D4())) == 0) {
                    HuPadBtnDown[var_r31->unk_04] |= 0x100;
                    break;
                }
                break;
            }
            break;
        case 3:
            if ((s32)(4.0 * (1.52587890625e-05 * (float)fn_1_64D4())) != 0) {
                HuPadBtn[var_r31->unk_04] |= 0x100;
            }
            if ((var_r30->unk_05 == 0) && (var_r30->unk_0E == 5)) {
                HuPadBtnDown[var_r31->unk_04] |= 0x100;
                break;
            }
            if ((var_r31->unk_24.y < 5.353333473205566) && ((s32)((0xE - (var_r31->unk_06 * 2)) * (1.52587890625e-05 * (float)fn_1_64D4())) == 0)) {
                HuPadBtnDown[var_r31->unk_04] |= 0x100;
            }
            break;
    }
}

void fn_1_3764(omObjData *object)
{
    float var_f30;
    float var_f29;

    M425DllWork *var_r31;
    s16 var_r30;
    s16 var_r29;
    s16 var_r27;
    s16 var_r26;
    s16 var_r25;
    s16 var_r24;
    s32 var_r23;

    var_r31 = object->data;
    var_r23 = object->model[0];
    var_r30 = var_r31->unk_0E;
    if (lbl_1_bss_648 == 5) {
        var_r26 = 0;
        var_r25 = 0;
        var_r27 = HuPadBtnDown[var_r31->unk_04];
        var_r24 = HuPadBtn[var_r31->unk_04];
    }
    else {
        var_r26 = 0;
        var_r25 = 0;
        var_r27 = 0;
        var_r24 = 0;
    }
    var_r31->unk_64 = 0;
    switch (var_r31->unk_0E) {
        case 4:
        case 7:
            if (CharModelMotionEndCheck(var_r31->unk_01) != 0) {
                var_r30 = 0;
                var_r29 = 1;
            }

        case 0:
        case 1:
        case 2:
            var_r31->unk_24.x = 0.25f * var_r26;
            var_r31->unk_24.z = 0.25f * -var_r25;
            var_r31->unk_14 = sqrtf((var_r31->unk_24.x * var_r31->unk_24.x) + (var_r31->unk_24.z * var_r31->unk_24.z));
            var_r31->unk_64 = 1;
            if (var_r31->unk_14 > 0.1f) {
                if (var_r31->unk_14 >= 8.0f) {
                    var_r30 = 2;
                    var_r29 = 1;
                }
                else {
                    var_r30 = 1;
                    var_r29 = 1;
                }
                var_f30 = atan2d(var_r31->unk_24.x, var_r31->unk_24.z);
                if (var_f30 >= 180.0f) {
                    var_f30 = var_f30 - 360.0f;
                }
                else if (var_f30 < -180.0f) {
                    var_f30 += 360.0f;
                }
                var_f29 = var_r31->unk_10 - var_f30;
                if (var_f29 >= 180.0f) {
                    var_f29 -= 360.0f;
                }
                else if (var_f29 < -180.0f) {
                    var_f29 += 360.0f;
                }
                var_r31->unk_10 = var_f30 + (0.5f * var_f29);
                if (var_r31->unk_10 >= 180.0f) {
                    var_r31->unk_10 = var_r31->unk_10 - 360.0f;
                }
                else if (var_r31->unk_10 < -180.0f) {
                    var_r31->unk_10 += 360.0f;
                }
            }
            else {
                var_r30 = 0;
                var_r29 = 1;
            }
            var_r31->unk_24.y = 0.0f;
            var_r31->unk_24.y += -2.4333334f * var_r31->unk_60;
            if ((var_r27 & 0x100) != 0) {
                var_r31->unk_0B = 0;
                var_r31->unk_0A = 1;
                var_r31->unk_24.y = 26.766666f;
                var_r30 = 3;
                var_r29 = 0;
            }
            break;
        case 3:
            if (var_r31->unk_0A != 0) {
                if ((var_r24 & 0x100) != 0) {
                    if (++var_r31->unk_0A > 4) {
                        var_r31->unk_0A = 0;
                    }
                    else {
                        var_r31->unk_24.y += 4.866667f;
                    }
                }
                else {
                    var_r31->unk_0A = 0;
                }
            }
            var_r31->unk_24.y += -2.4333334f;
            if (var_r31->unk_0B != 0) {
                var_r31->unk_0B = 1;
                var_r30 = 4;
                var_r29 = 0;
                var_r31->unk_24.y = 0.0f;
            }
            if (((var_r27 & 0x100) != 0) || ((var_r27 & 0x40) != 0)) {
                var_r31->unk_24.y = 0.0f;
                var_r31->unk_0C = 0;
                var_r30 = 5;
                var_r29 = 0;
            }
            break;
        case 5:
            if ((Hu3DData[var_r23].unk_0C == -1) && (CharModelMotionEndCheck(var_r31->unk_01) != 0)) {
                var_r31->unk_24.y += -2.4333334f;
            }
            else {
                var_r31->unk_24.y = 0.0f;
            }
            if (var_r31->unk_0B != 0) {
                if (var_r31->unk_0C != 0) {
                    var_r31->unk_24.y = 0.0f;
                    var_r31->unk_0C = 0;
                    var_r30 = 7;
                    var_r29 = 0;
                }
                else {
                    var_r31->unk_24.y = 9.733334f;
                    var_r31->unk_0B = 0;
                    var_r30 = 6;
                    var_r29 = 0;
                }
            }
            break;
        case 6:
            var_r31->unk_24.y += -2.4333334f;
            if ((var_r31->unk_0B != 0) && (CharModelMotionEndCheck(var_r31->unk_01) != 0)) {
                var_r30 = 7;
                var_r29 = 0;
            }
            break;
        case 8:
        case 9:
            var_r31->unk_24.y = -2.4333334f * var_r31->unk_60;
            var_r31->unk_64 = 1;
            break;
    }
    var_r31->unk_18.x += var_r31->unk_24.x;
    if (var_r31->unk_0B == 0) {
        var_r31->unk_18.y += var_r31->unk_24.y;
    }
    var_r31->unk_18.z += var_r31->unk_24.z;
    if (var_r30 != var_r31->unk_0E) {
        var_r31->unk_0E = var_r30;
        CharModelMotionShiftSet(var_r31->unk_01, object->motion[var_r31->unk_0E], 0.0f, 8.0f, var_r29);
    }
    omSetTra(object, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
    omSetRot(object, 0.0f, var_r31->unk_10, 0.0f);
}

s16 fn_1_3ED0(s32 arg0, s16 arg1, ParticleHook arg2)
{
    s32 var_r31;
    M425DllUnkStruct *var_r30;
    ParticleData *var_r29;
    AnimData *var_r28;

    var_r28 = HuSprAnimRead(HuDataReadNum(arg0, MEMORY_DEFAULT_NUM));
    var_r31 = Hu3DParticleCreate(var_r28, arg1);
    Hu3DParticleHookSet(var_r31, arg2);
    var_r29 = Hu3DData[var_r31].unk_120;
    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M425DllUnkStruct), MEMORY_DEFAULT_NUM);
    var_r29->unk_1C = var_r30;
    var_r30->unk_04 = 0;
    return var_r31;
}

void fn_1_3F80(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float var_f29;
    float var_f28;
    float var_f26;
    float var_f25;
    float var_f24;

    HsfanimStruct01 *var_r31;
    M425DllUnkStruct *var_r29;
    s32 var_r28;

    float sp54[4] = { 1000.0f, 200.0f, 600.0f, 1200.0f };
    float sp44[4] = { 1.0f, 0.6f, 0.3f, 0.425f };
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    s16 sp8 = 0;

    var_r29 = particle->unk_1C;
    switch (var_r29->unk_04) {
        case 0:
            var_r31 = particle->unk_48;
            if (var_r29->unk_02 != 0) {
                sp14.x = 0.0f;
                sp14.y = -3600.0f;
                sp14.z = 6250.0f;
                var_f28 = (sp14.z * sp14.z) + ((sp14.x * sp14.x) + (sp14.y * sp14.y));
                var_f29 = 1.0f / sqrtf(var_f28);
                sp14.x *= var_f29;
                sp14.y *= var_f29;
                sp14.z *= var_f29;
                var_f24 = 6000.0f / particle->unk_30;
                for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
                    var_f26 = 500.0 + ((var_f24 * var_r28) + ((0.25f * var_f24) * (1.52587890625e-05 * (float)(s32)(u16)frand())));
                    var_f25 = var_f26 / 6000.0f;
                    var_r31->unk14.x = var_f26;
                    var_r31->unk34.x = var_f26 * sp14.x;
                    var_r31->unk34.y = 4000.0f + (var_f26 * sp14.y);
                    var_r31->unk34.z = -6750.0f + (var_f26 * sp14.z);
                    var_r31->unk2C = (0.3f + (0.7f * (var_f25 * var_f25)))
                        * (sp54[var_r29->unk_02] * (0.699999988079071 + (0.30000001192092896 * (1.52587890625e-05 * (float)(s32)(u16)frand()))));
                    var_r31->unk40.r = (s32)(160.0 * (1.52587890625e-05 * (float)fn_1_64D4())) + 0x20;
                    var_r31->unk40.g = (s32)(96.0 * (1.52587890625e-05 * (float)fn_1_64D4())) + 0x20;
                    var_r31->unk40.b = (s32)(128.0 * (1.52587890625e-05 * (float)fn_1_64D4())) + 0x20;
                    var_r31->unk40.a
                        = ((1.0 - (0.4 * var_f25)) * (255.0f * sp44[var_r29->unk_02])) - (s32)(16.0 * (1.52587890625e-05 * (float)fn_1_64D4()));
                }
                var_r29->unk_04++;
            }
            else {
                var_r31->unk34.x = 0.0f;
                var_r31->unk34.y = 4000.0f;
                var_r31->unk34.z = -6750.0f;
                var_r31->unk2C = 1000.0f;
            }
            break;
        case 1:
            sp38.x = sind(CRot.y) * cosd(CRot.x);
            sp38.y = -sind(CRot.x);
            sp38.z = cosd(CRot.y) * cosd(CRot.x);
            sp2C.x = -(Center.x + (1.25f * (sp38.x * CZoom)));
            sp2C.y = 4000.0f - (Center.y + (sp38.y * CZoom));
            sp2C.z = -6750.0f - (Center.z + (1.25f * (sp38.z * CZoom)));
            var_f29 = 1.0f / sqrtf((sp2C.z * sp2C.z) + ((sp2C.x * sp2C.x) + (sp2C.y * sp2C.y)));
            sp2C.x *= var_f29;
            sp2C.y *= var_f29;
            sp2C.z *= var_f29;
            var_f29 = -((-sp2C.z * -sp38.z) + ((-sp2C.x * -sp38.x) + (-sp2C.y * -sp38.y)));
            sp20.x = -sp38.x + (-2.0f * sp2C.x * var_f29);
            sp20.y = -sp38.y + (-2.0f * sp2C.y * var_f29);
            sp20.z = -sp38.z + (-2.0f * sp2C.z * var_f29);
            for (var_r31 = particle->unk_48, var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
                var_r31->unk34.x = sp20.x * var_r31->unk14.x;
                var_r31->unk34.y = 4000.0f + (sp20.y * var_r31->unk14.x);
                var_r31->unk34.z = -6750.0f + (sp20.z * var_r31->unk14.x);
            }
            break;
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_4A88(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float var_f31;
    HsfanimStruct01 *var_r31;
    M425DllUnkStruct *var_r29;
    s32 var_r28;
    s16 var_r27;

    var_r27 = 0;
    var_r29 = particle->unk_1C;
    switch (var_r29->unk_04) {
        case 0:
            for (var_r31 = particle->unk_48, var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
                var_r31->unk00 = var_r31->unk02 = 0;
            }
            var_r29->unk_04++;
            break;
        case 1:
            for (var_r31 = particle->unk_48, var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
                if (var_r31->unk00 != 0) {
                    var_r31->unk00--;
                }
                else {
                    if (var_r31->unk02 == 0) {
                        var_f31 = 180.0 * (1.52587890625e-05 * (float)(s32)(u16)frand());
                        var_f31 = var_f31;
                        if ((s32)(4.0 * (1.52587890625e-05 * (float)fn_1_64D4())) != 0) {
                            var_r31->unk34.x = 100.0 * (4.0 * (1.52587890625e-05 * (float)(s32)(u16)frand())) * cosd(var_f31);
                        }
                        else {
                            var_r31->unk34.x = 100.0 * (2.0 * (1.52587890625e-05 * (float)(s32)(u16)frand())) * cosd(var_f31);
                        }
                        var_r31->unk34.y = -10.0f;
                        var_r31->unk34.z = -7000.0 + (100.0 * (40.0 * (1.52587890625e-05 * (float)(s32)(u16)frand())) * sind(var_f31));
                        var_r31->unk30 = 1.5707964f;
                        var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = var_r31->unk40.a = 0xC0;
                        var_r31->unk40.b = 0xA0;
                        var_r31->unk2C = 0.0f;
                        var_r31->unk00 = (s32)(90.0 * (1.52587890625e-05 * (float)fn_1_64D4()));
                        var_r31->unk02 = 0x3C;
                        var_r31->unk40.r = 0xC0;
                        var_r31->unk40.g = 0xE0;
                        var_r31->unk40.b = 0xE0;
                        var_r31->unk08.z = 0.01f * (0.05f * (3000.0f + -var_r31->unk34.z));
                        var_r31->unk08.z *= var_r31->unk08.z;
                        var_r31->unk08.z *= 0.125f;
                    }
                    var_r31->unk40.a = 248.0 * sind((var_r31->unk02 * 3));
                    var_r31->unk2C = (30.0f * var_r31->unk08.z) * sind((var_r31->unk02 * 3));
                    var_r31->unk02--;
                }
            }
            if (particle->unk_30 == var_r27) {
                Hu3DModelAttrReset(var_r29->unk_00, HU3D_ATTR_PARTICLE_KILL);
                Hu3DModelKill(var_r29->unk_00);
                return;
            }
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_5044(s16 sp8)
{
    M425DllUnkStruct3 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    ModelData *var_r27;
    void *var_r26;

    Vec2f spC[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    var_r27 = &Hu3DData[sp8];
    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M425DllUnkStruct3), MEMORY_DEFAULT_NUM);
    var_r27->unk_120 = var_r31;
    var_r31->unk_2A = 1;
    var_r31->unk_20.r = var_r31->unk_20.g = var_r31->unk_20.b = 0x40;
    var_r31->unk_20.a = 0xFF;
    var_r31->unk_24.a = var_r31->unk_24.g = var_r31->unk_24.b = 0xFF;
    var_r31->unk_24.r = var_r31->unk_24.b = 0;
    // maybe Mtx?
    var_r31->unk_14 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk_2A * (4 * sizeof(Vec)), MEMORY_DEFAULT_NUM);
    var_r31->unk_14[0].x = -4500.0f;
    var_r31->unk_14[0].y = 0.0f;
    var_r31->unk_14[0].z = -7000.0f;
    var_r31->unk_14[1].x = 4500.0f;
    var_r31->unk_14[1].y = 0.0f;
    var_r31->unk_14[1].z = -7000.0f;
    var_r31->unk_14[2].x = 3000.0f;
    var_r31->unk_14[2].y = -200.0f;
    var_r31->unk_14[2].z = 0.0f;
    var_r31->unk_14[3].x = -3000.0f;
    var_r31->unk_14[3].y = -200.0f;
    var_r31->unk_14[3].z = 0.0f;
    var_r31->unk_18 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk_2A * (4 * sizeof(GXColor)), MEMORY_DEFAULT_NUM);
    var_r31->unk_18[0].r = 0xFF;
    var_r31->unk_18[0].g = 0xFF;
    var_r31->unk_18[0].b = 0xFF;
    var_r31->unk_18[0].a = 0xFF;
    var_r31->unk_18[1].r = 0xFF;
    var_r31->unk_18[1].g = 0xFF;
    var_r31->unk_18[1].b = 0xFF;
    var_r31->unk_18[1].a = 0xFF;
    var_r31->unk_18[2].r = 0xFF;
    var_r31->unk_18[2].g = 0xFF;
    var_r31->unk_18[2].b = 0xFF;
    var_r31->unk_18[2].a = 0xFF;
    var_r31->unk_18[3].r = 0xFF;
    var_r31->unk_18[3].g = 0xFF;
    var_r31->unk_18[3].b = 0xFF;
    var_r31->unk_18[3].a = 0xFF;
    var_r31->unk_1C = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk_2A * sizeof(Vec), MEMORY_DEFAULT_NUM);
    var_r31->unk_1C->x = 0.0f;
    var_r31->unk_1C->y = 1.0f;
    var_r31->unk_1C->z = 0.0f;
    var_r31->unk_28 = 2;
    var_r31->unk_2C = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk_2A * (var_r31->unk_28 * sizeof(M425DllUnkStruct2)), MEMORY_DEFAULT_NUM);
    var_r31->unk_2C[0].unk_00 = HuSprAnimReadFile(0x380003);
    var_r31->unk_2C[0].unk_04 = 0;
    var_r31->unk_2C[1].unk_00 = HuSprAnimReadFile(0x380004);
    var_r31->unk_2C[1].unk_04 = 0;
    var_r31->unk_2C[1].unk_48 = 0x80;
    for (var_r30 = 0; var_r30 < (var_r31->unk_28 * var_r31->unk_2A); var_r30++) {
        MTXIdentity(var_r31->unk_2C[var_r30].unk_14);
        var_r31->unk_2C[var_r30].unk_08.x = var_r31->unk_2C[var_r30].unk_08.y = var_r31->unk_2C[var_r30].unk_08.z = 0.0f;
    }
    for (var_r30 = 0; var_r30 < var_r31->unk_28; var_r30++) {
        fn_1_573C(&var_r31->unk_2C[var_r30].unk_44, var_r31->unk_2A, spC);
    }
    var_r26 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x20000, MEMORY_DEFAULT_NUM);
    var_r31->unk_10 = var_r26;
    DCFlushRange(var_r31->unk_10, 0x20000);
    GXBeginDisplayList(var_r26, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, var_r31->unk_2A * 4);
    for (var_r30 = 0; var_r30 < var_r31->unk_2A; var_r30++) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            GXUnknownu16(var_r29 + (var_r30 * 4));
            GXUnknownu16(var_r30);
            GXUnknownu16(var_r29 + (var_r30 * 4));
            for (var_r28 = 0; var_r28 < var_r31->unk_28; var_r28++) {
                GXUnknownu16(var_r29 + (var_r30 * 4));
            }
        }
    }
    var_r31->unk_0C = GXEndDisplayList();
}

void fn_1_5568(Vec **arg0, s16 arg1, Vec *arg2)
{
    Vec *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * (4 * sizeof(Vec)), MEMORY_DEFAULT_NUM);
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
            var_r31->z = arg2->z;
        }
    }
}

void fn_1_5608(GXColor **arg0, s16 arg1, GXColor *arg2)
{
    GXColor *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * (4 * sizeof(GXColor)), 0x10000000);
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->r = arg2->r;
            var_r31->g = arg2->g;
            var_r31->b = arg2->b;
            var_r31->a = arg2->a;
        }
    }
}

void fn_1_56B0(Vec **arg0, s16 arg1, Vec *arg2)
{
    Vec *var_r31;
    s32 var_r29;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    for (var_r29 = 0; var_r29 < arg1; var_r31++, arg2++, var_r29++) {
        var_r31->x = arg2->x;
        var_r31->y = arg2->y;
        var_r31->z = arg2->z;
    }
}

void fn_1_573C(Vec2f **arg0, s16 arg1, Vec2f *arg2)
{
    Vec2f *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * (4 * sizeof(Vec2f)), MEMORY_DEFAULT_NUM);
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
        }
    }
}

void fn_1_57D4(ModelData *model, Mtx matrix)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    M425DllUnkStruct3 *var_r30;

    var_r30 = model->unk_120;
    var_r30->unk_2C[1].unk_08.y -= 0.0005f;
    var_f31 = sind(lbl_1_bss_4);
    var_f30 = cosd(lbl_1_bss_4);
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        var_r30->unk_2C[var_r31].unk_44[0].x = 0.005f * var_f31 * (var_r31 != 0 ? 10.0f : -1.0f);
        var_r30->unk_2C[var_r31].unk_44[0].y = 0.005f * var_f30 * (var_r31 != 0 ? 1.0f : -1.0f);
        var_r30->unk_2C[var_r31].unk_44[1].x = 1.0f + (0.005f * var_f30 * (var_r31 != 0 ? 10.0f : -1.0f));
        var_r30->unk_2C[var_r31].unk_44[1].y = 0.005f * var_f31 * (var_r31 != 0 ? 1.0f : -1.0f);
        var_r30->unk_2C[var_r31].unk_44[2].x = 1.0f + (0.005f * var_f31 * (var_r31 != 0 ? 10.0f : -1.0f));
        var_r30->unk_2C[var_r31].unk_44[2].y = 1.0f + (0.005f * var_f30 * (var_r31 != 0 ? 1.0f : -1.0f));
        var_r30->unk_2C[var_r31].unk_44[3].x = 0.005f * var_f30 * (var_r31 != 0 ? 10.0f : -1.0f);
        var_r30->unk_2C[var_r31].unk_44[3].y = 1.0f + (0.005f * var_f31 * (var_r31 != 0 ? 1.0f : -1.0f));
    }
    lbl_1_bss_4 += 1.0f;
    fn_1_5C20(model, matrix);
}

void fn_1_5C20(ModelData *var_r27, Mtx sp8)
{
    Mtx sp5C;
    Mtx sp2C;
    GXColor sp26;
    s16 spC;
    GXTexMapID var_r29;
    M425DllUnkStruct3 *var_r31;
    s16 var_r30;
    s16 var_r28;
    s16 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    var_r31 = var_r27->unk_120;
    GXSetChanAmbColor(GX_COLOR0A0, var_r31->unk_20);
    GXSetChanMatColor(GX_COLOR0A0, var_r31->unk_24);
    GXLoadPosMtxImm(sp8, 0);
    MTXInverse(sp8, sp5C);
    MTXTranspose(sp5C, sp2C);
    GXLoadNrmMtxImm(sp2C, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(1, GX_LEQUAL, 1);
    var_r30 = 0;
    var_r28 = 0;
    spC = 0;
    for (var_r29 = GX_TEXMAP0; var_r29 < var_r31->unk_28; var_r29++) {
        MTXRotRad(var_r31->unk_2C[var_r29].unk_14, 0x5A, 0.0f);
        mtxTransCat(
            var_r31->unk_2C[var_r29].unk_14, var_r31->unk_2C[var_r29].unk_08.x, var_r31->unk_2C[var_r29].unk_08.y, var_r31->unk_2C[var_r29].unk_08.z);
        switch (var_r31->unk_2C[var_r29].unk_04) {
            case 0:
                GXLoadTexMtxImm(var_r31->unk_2C[var_r29].unk_14, texMtxTbl[var_r28], GX_MTX2x4);
                var_r25 = texMtxTbl[var_r28];
                GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r29 + 4, var_r25, GX_FALSE, 0x7D);
                GXSetTevOrder(var_r30, var_r28, var_r29, GX_COLOR0A0);
                if (var_r29 == GX_TEXMAP0) {
                    GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                    GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                }
                else {
                    sp26.a = var_r31->unk_2C[var_r29].unk_48;
                    GXSetTevColor(GX_TEVREG2, sp26);
                    GXSetTevColorIn(var_r30, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO, GX_CC_TEXC);
                    GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                }
                GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                break;
            case 1:
                GXLoadTexMtxImm(var_r31->unk_2C[var_r29].unk_14, texMtxTbl[var_r28], GX_MTX2x4);
                var_r24 = texMtxTbl[var_r28];
                GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r29 + 4, var_r24, GX_FALSE, 0x7D);
                GXSetTevOrder(var_r30, var_r28, var_r29, GX_COLOR0A0);
                GXSetTevColor(GX_TEVREG2, sp26);
                GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
                GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                break;
            case 2:
                sp26.a = 0xE0;
                GXSetTevColor(GX_TEVREG1, sp26);
                GXSetTexCoordGen2(var_r28 + 1, GX_TG_BUMP0, var_r28, 0x3C, GX_FALSE, 0x7D);
                GXSetTevOrder(var_r30, var_r28, var_r29, GX_COLOR0A0);
                GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_RASC);
                GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                var_r30++;
                GXSetTevOrder(var_r30, var_r28 + 1, GX_TEXMAP0, GX_COLOR0A0);
                GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_CPREV);
                GXSetTevColorOp(var_r30, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                break;
            case 3:
                var_r28--;
                GXLoadTexMtxImm(var_r31->unk_2C[var_r29].unk_14, texMtxTbl[var_r28], GX_MTX2x4);
                var_r23 = texMtxTbl[var_r28];
                GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r29 + 4, var_r23, 0, 0x7D);
                GXSetTevOrder(var_r30, var_r28, var_r29, GX_COLOR0A0);
                GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
                GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                var_r28++;
                break;
        }
        var_r30++;
        var_r28++;
        HuSprTexLoad(var_r31->unk_2C[var_r29].unk_00, 0, var_r29, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    }
    sp26.a = var_r31->unk_24.a;
    GXSetTevColor(GX_TEVREG0, sp26);
    GXSetTevOrder(var_r30, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_KONST);
    GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    var_r30++;
    GXSetNumTevStages((s32)var_r30);
    GXSetNumTexGens((s32)var_r28);
    var_r26 = Hu3DLightSet(var_r27, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, 0.0f);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, var_r26, GX_DF_CLAMP, GX_AF_SPOT);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSETARRAY(GX_VA_POS, var_r31->unk_14, var_r31->unk_2A * (4 * sizeof(Vec)), sizeof(Vec));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSETARRAY(GX_VA_CLR0, var_r31->unk_18, var_r31->unk_2A * (4 * sizeof(GXColor)), sizeof(GXColor));
    for (var_r29 = GX_TEXMAP0; var_r29 < (var_r31->unk_28 * var_r31->unk_2A); var_r29++) {
        GXSetVtxDesc(var_r29 + 0xD, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, var_r29 + 0xD, GX_TEX_ST, GX_F32, 0);
        GXSETARRAY(var_r29 + 0xD, var_r31->unk_2C[var_r29].unk_44, var_r31->unk_2A * (4 * sizeof(Vec2f)), sizeof(Vec2f));
    }
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSETARRAY(GX_VA_NRM, var_r31->unk_1C, var_r31->unk_2A * (4 * sizeof(Vec)), sizeof(Vec));
    GXCallDisplayList(var_r31->unk_10, var_r31->unk_0C);
}

u32 lbl_1_data_114 = 0x41C64E6D;

s32 fn_1_64D4(void)
{
    lbl_1_data_114 *= 0x41C64E6D;
    lbl_1_data_114 += 0x3039;
    return lbl_1_data_114 >> 0x10;
}

float fn_1_6528(float arg8, float arg9, float argA, float argB)
{
    float var_f31 = 1.0 - arg8;
    float var_f30 = (argB * (arg8 * arg8)) + ((arg9 * (var_f31 * var_f31)) + (2.0 * (argA * (var_f31 * arg8))));
    return var_f30;
}

void fn_1_65A0(float *arg0, float *arg1, float *arg2, float *arg3, float arg8)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        *arg3++ = fn_1_6528(arg8, *arg0++, *arg1++, *arg2++);
    }
}

float fn_1_66BC(float arg8, float arg9, float argA, float argB)
{
    float var_f31 = 2.0 * ((arg8 * argB) + (((arg8 - 1.0) * arg9) + ((1.0 - (2.0 * arg8)) * argA)));
    return var_f31;
}

void fn_1_6734(float *arg0, float *arg1, float *arg2, float *arg3, float arg8)
{
    float spC[3];
    float sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f22;
    float var_f21;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        spC[var_r31] = fn_1_66BC(arg8, *arg0++, *arg1++, *arg2++);
    }

    var_f29 = sqrtf((spC[2] * spC[2]) + ((spC[0] * spC[0]) + (spC[1] * spC[1])));
    if (var_f29) {
        var_f29 = 1.0 / var_f29;
        var_f29 = var_f29;
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            *arg3++ = var_f29 * spC[var_r31];
        }
        return;
    }
    *arg3++ = 0.0f;
    *arg3++ = 0.0f;
    *arg3++ = 1.0f;
}
