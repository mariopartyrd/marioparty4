#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/wipe.h"

#include "REL/m417Dll.h"

typedef struct UnkM417Struct8 {
    /* 0x00 */ u16 unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ u32 unk_10;
} UnkM417Struct8; /* size = 0x14 */

typedef struct UnkM417Struct10 {
    /* 0x04 */ s32 unk_00;
    /* 0x08 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ u16 unk_50;
    /* 0x52 */ char unk52[2];
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ char unk58[4];
    /* 0x5C */ s16 unk_5C;
    /* 0x5E */ char unk5E[6];
    /* 0x64 */ float unk_64;
    /* 0x68 */ float unk_68;
    /* 0x6C */ float unk_6C;
    /* 0x70 */ float unk_70;
    /* 0x74 */ float unk_74;
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ float unk_7C;
    /* 0x80 */ u32 unk_80;
    /* 0x84 */ u32 unk_84;
    /* 0x88 */ float unk_88;
    /* 0x8C */ float unk_8C;
    /* 0x90 */ u32 unk_90;
    /* 0x94 */ char unk94[4];
    /* 0x98 */ float unk_98;
    /* 0x9C */ s32 unk_9C;
    /* 0xA0 */ s32 unk_A0;
    /* 0xA4 */ u32 unk_A4;
    /* 0xA8 */ u32 unk_A8;
    /* 0xAC */ float unk_AC;
    /* 0xB0 */ float unk_B0;
    /* 0xB4 */ Vec unk_B4;
    /* 0xC0 */ u32 unk_C0;
    /* 0xC4 */ u32 unk_C4;
    /* 0xC8 */ Vec unk_C8;
    /* 0xD4 */ Vec unk_D4;
    /* 0xE0 */ Vec unk_E0;
    /* 0xEC */ Vec unk_EC;
    /* 0xF8 */ Vec unk_F8;
    /* 0x104 */ Vec unk_104;
    /* 0x110 */ Vec unk_110;
    /* 0x11C */ Quaternion unk_11C;
    /* 0x12C */ float unk_12C;
    /* 0x130 */ float unk_130;
    /* 0x134 */ float unk_134;
    /* 0x138 */ float unk_138;
    /* 0x13C */ float unk_13C;
    /* 0x140 */ float unk_140;
    /* 0x144 */ float unk_144;
    /* 0x148 */ float unk_148;
    /* 0x14C */ Vec unk_14C;
    /* 0x158 */ char unk_158[0xC];
    /* 0x164 */ Quaternion unk_164;
    /* 0x174 */ Quaternion unk_174;
    /* 0x184 */ Quaternion unk_184;
    /* 0x194 */ Quaternion unk_194;
    /* 0x1A4 */ Quaternion unk_1A4;
    /* 0x1B4 */ Quaternion unk_1B4;
    /* 0x1C4 */ Mtx unk_1C4;
    /* 0x1F4 */ Mtx unk_1F4;
    /* 0x224 */ Mtx unk_224;
    /* 0x254 */ Vec unk_254[16]; // maybe less
} UnkM417Struct10; /* size = 0x314 */

void fn_1_7C8C(omObjData *object);
void fn_1_82FC(omObjData *object);
void fn_1_86E8(omObjData *object);
void fn_1_8B0C(omObjData *object);
void fn_1_8D30(omObjData *object);
void fn_1_8E44(omObjData *object);
void fn_1_91E0(omObjData *object);
void fn_1_9298(omObjData *object);
void fn_1_9A1C(omObjData *object);
void fn_1_9C14(omObjData *object);
void fn_1_9FF0(omObjData *object);
void fn_1_AD24(omObjData *object);
void fn_1_ADC4(omObjData *object);
void fn_1_B2C0(omObjData *object);
void fn_1_B8A0(omObjData *object, u32 arg1);
s32 fn_1_BA2C(omObjData *object);
void fn_1_BC70(float arg8, float arg9, Quaternion *arg0);

s32 lbl_1_data_50[][2] = {
    { DATA_MAKE_NUM(DATADIR_M417, 1), DATA_MAKE_NUM(DATADIR_M417, 6) },
    { DATA_MAKE_NUM(DATADIR_M417, 1), DATA_MAKE_NUM(DATADIR_M417, 7) },
    { DATA_MAKE_NUM(DATADIR_M417, 1), DATA_MAKE_NUM(DATADIR_M417, 8) },
    { DATA_MAKE_NUM(DATADIR_M417, 1), DATA_MAKE_NUM(DATADIR_M417, 9) },
    { DATA_MAKE_NUM(DATADIR_M417, 1), DATA_MAKE_NUM(DATADIR_M417, 10) },
    { DATA_MAKE_NUM(DATADIR_M417, 1), DATA_MAKE_NUM(DATADIR_M417, 11) },
    { DATA_MAKE_NUM(DATADIR_M417, 1), DATA_MAKE_NUM(DATADIR_M417, 12) },
    { DATA_MAKE_NUM(DATADIR_M417, 1), DATA_MAKE_NUM(DATADIR_M417, 13) },
};

u32 lbl_1_data_90[11][3] = {
    { 0, 1, 1 },
    { 23, 1, 1 },
    { 24, 1, 1 },
    { 2, 1, 0 },
    { 3, 1, 0 },
    { DATA_MAKE_NUM(DATADIR_M417, 18), 1, 0 },
    { DATA_MAKE_NUM(DATADIR_M417, 26), 1, 0 },
    { 5, 0, 1 },
    { 6, 0, 1 },
    { 8, 0, 1 },
    { 9, 0, 1 },
};

UnkM417Struct8 lbl_1_data_114[11] = {
    { 0, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 1, 0.2f, 0.0f, -1.0f, 0 },
    { 2, 0.2f, 0.0f, -1.0f, 0 },
    { 3, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 4, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 5, 0.5f, 0.0f, -1.0f, 0 },
    { 6, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 7, 0.03f, 0.0f, -1.0f, 0 },
    { 8, 0.0f, 0.0f, -1.0f, 0 },
    { 9, 0.2f, 0.0f, -1.0f, 0 },
    { 10, 0.0f, 0.0f, -1.0f, 0 },
};

s32 lbl_1_bss_8AC; // unused
s32 lbl_1_bss_8A8; // unused
omObjData *lbl_1_bss_898[4];
u32 lbl_1_bss_888[4];
u32 lbl_1_bss_884;
u32 lbl_1_bss_880;

void fn_1_7A34(Process *arg0)
{
    u32 sp18[4];
    u32 sp8[4];

    s16 var_r31;
    s16 var_r30;
    s32 var_r29;
    omObjData *var_r28;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp18[var_r31] = GWPlayerCfg[var_r31].group;
        sp8[var_r31] = var_r31;
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        for (var_r30 = var_r31 + 1; var_r30 < 4; var_r30++) {
            if (sp18[var_r31] > sp18[var_r30]) {
                var_r29 = sp18[var_r31];
                sp18[var_r31] = sp18[var_r30];
                sp18[var_r30] = var_r29;
                var_r29 = sp8[var_r31];
                sp8[var_r31] = sp8[var_r30];
                sp8[var_r30] = var_r29;
            }
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_888[sp8[var_r31]] = var_r31;
    }
    omMakeGroupEx(arg0, 0, 4);
    omGetGroupMemberListEx(arg0, 0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r28 = lbl_1_bss_898[var_r31] = omAddObjEx(arg0, 40, 2, 11, 0, fn_1_7C8C);
        var_r28->work[0] = var_r31;
    }
    lbl_1_bss_880 = lbl_1_bss_884 = 0;
}

void fn_1_7C68(void)
{
    CharModelKill(-1);
}

void fn_1_7C8C(omObjData *object)
{
    s32 sp8;

    UnkM417Struct10 *var_r31;
    s32 var_r29;
    s32 var_r28;
    u32 var_r27;
    u32 var_r26;

    float sp44[4] = { 0.25f, 0.5f, 0.75f, 1.0f };
    float sp34[4] = { 0.0f, 650.0f, 650.0f, 650.0f };
    float sp24[4] = { 180.0f, 180.0f, 300.0f, 60.0f };

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM417Struct10), MEMORY_DEFAULT_NUM);
    var_r31 = object->data;
    memset(var_r31, 0, sizeof(UnkM417Struct10));
    object->stat |= 256;
    var_r26 = object->work[0];
    var_r28 = GWPlayerCfg[var_r26].character;
    var_r31->unk_00 = var_r28;
    sp8 = var_r31->unk_04 = 0;
    var_r31->unk_0C = lbl_1_bss_888[object->work[0]];
    var_r27 = 0;
    if (var_r31->unk_0C) {
        var_r27++;
    }
    fn_1_2808(object->work[0], var_r31->unk_0C, var_r31->unk_00);
    var_r31->unk_74 = sp44[GWPlayerCfg[var_r26].diff & 3];
    var_r31->unk_44 = GWPlayerCfg[object->work[0]].iscom;
    object->model[0] = CharModelCreate(var_r28, 4);
    Hu3DModelLayerSet(object->model[0], 4);
    Hu3DModelShadowSet(object->model[0]);
    for (var_r29 = 0; var_r29 < 11; var_r29++) {
        if (lbl_1_data_90[var_r29][var_r27 + 1]) {
            if (lbl_1_data_90[var_r29][0] < 65536) {
                object->motion[var_r29] = CharModelMotionCreate(var_r28, lbl_1_data_90[var_r29][0]);
            } else {
                object->motion[var_r29]
                    = Hu3DJointMotion(object->model[0], HuDataSelHeapReadNum(var_r28 + lbl_1_data_90[var_r29][0], MEMORY_DEFAULT_NUM, HEAP_DATA));
            }
        }
    }
    CharModelMotionDataClose(var_r28);
    object->model[1] = Hu3DModelCreateFile(lbl_1_data_50[var_r28][var_r27]);
    Hu3DModelShadowMapSet(object->model[1]);

    var_r31->unk_B4.x = sp24[var_r31->unk_0C];
    var_r31->unk_B4.y = 0.0f;
    var_r31->unk_B4.z = sp34[var_r31->unk_0C];

    object->trans.x = var_r31->unk_C8.x = var_r31->unk_B4.z * sind(var_r31->unk_B4.x);
    object->trans.y = var_r31->unk_C8.y = 0.0f;
    object->trans.z = var_r31->unk_C8.z = var_r31->unk_B4.z * cosd(var_r31->unk_B4.x);

    var_r31->unk_D4 = var_r31->unk_C8;
    var_r31->unk_F8 = var_r31->unk_C8;
    var_r31->unk_104 = var_r31->unk_F8;

    var_r31->unk_64 = var_r31->unk_68 = var_r31->unk_B4.x - 180.0f;
    var_r31->unk_6C = 0.0f;
    var_r31->unk_70 = 0.02f;
    if (var_r31->unk_0C) {
        Vec sp18 = { 0.0f, 1.0f, 0.0f };
        MTXRotAxisDeg(var_r31->unk_1C4, &sp18, var_r31->unk_64);
    } else {
        Vec spC = { 0.0f, 1.0f, 0.0f };
        PSMTXIdentity(var_r31->unk_1C4);
        C_QUATRotAxisRad(&var_r31->unk_184, &spC, 0.0f);
        var_r31->unk_194 = var_r31->unk_184;
        PSQUATInverse(&var_r31->unk_194, &var_r31->unk_1A4);
        var_r31->unk_1B4 = var_r31->unk_1A4;
        var_r31->unk_164 = var_r31->unk_194;
        var_r31->unk_174 = var_r31->unk_194;
        var_r31->unk_144 = 1.0f;
        var_r31->unk_D4.z += 50.0f;
    }
    PSMTXInverse(var_r31->unk_1C4, var_r31->unk_1F4);
    PSMTXCopy(var_r31->unk_1F4, var_r31->unk_224);
    var_r31->unk_134 = var_r31->unk_138 = 0.0f;
    var_r31->unk_12C = 1.0f;
    var_r31->unk_08 = -1;
    fn_1_B8A0(object, 0);
    var_r31->unk_78 = 0;
    var_r31->unk_9C = -1;
    lbl_1_bss_884 = object->work[0];
    lbl_1_bss_880 = 60.0f * (4.0f + (0.002f * frandmod(1000)));
    var_r31->unk_28 = 1;
    var_r31->unk_50 = 0;
    if (!var_r27) {
        object->func = fn_1_82FC;
        return;
    }
    var_r31->unk_2C = 1;
    object->func = fn_1_86E8;
}

void fn_1_82FC(omObjData *object)
{
    float var_f31;
    float var_f30;
    double var_f29;
    float var_f28;

    UnkM417Struct10 *var_r31;
    s32 var_r29;

    var_r31 = object->data;
    var_r29 = 0;
    var_r31->unk_10 = var_r31->unk_18 = 0;
    var_r31->unk_14 = 0;
    var_r31->unk_20 = 0.0f;
    var_r31->unk_24 = 0.0f;
    if (fn_1_26F8() == 2) {
        if (var_r31->unk_44) {
            fn_1_ADC4(object);
        } else {
            var_r31->unk_14 = HuPadBtn[GWPlayerCfg[object->work[0]].pad_idx];
            var_r31->unk_10 = HuPadBtnDown[GWPlayerCfg[object->work[0]].pad_idx];
            var_f31 = HuPadStkX[GWPlayerCfg[object->work[0]].pad_idx];
            var_f30 = -HuPadStkY[GWPlayerCfg[object->work[0]].pad_idx];
            var_r31->unk_20 = atan2d(var_f31, var_f30);
            var_r31->unk_24 = 0.013888889f * sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
            if (var_r31->unk_24 > 1.0f) {
                var_r31->unk_24 = 1.0f;
            }
        }
    }
    if ((s32)var_r31->unk_50 != 0) {
        (void)var_r29;
    } else {
        var_r29 = 1;
    }
    fn_1_9FF0(object);
    fn_1_9C14(object);
    fn_1_91E0(object);
    fn_1_AD24(object);
    if (fn_1_26F8() == 3) {
        if (var_r29 && fn_1_27D0()) {
            var_r31->unk_50 = 0;
            object->func = fn_1_8B0C;
        }
    } else if (var_r31->unk_3C) {
        var_r31->unk_40 = 1;
        fn_1_2728(2);
        var_r31->unk_50 = 0;
        object->func = fn_1_8E44;
    }
}

void fn_1_86E8(omObjData *object)
{
    float var_f31;
    float var_f30;
    double var_f29;
    float var_f28;

    UnkM417Struct10 *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r31 = object->data;
    var_r29 = 0;
    var_r31->unk_10 = var_r31->unk_18 = 0;
    var_r31->unk_14 = 0;
    var_r31->unk_20 = 0.0f;
    var_r31->unk_24 = 0.0f;
    if (fn_1_26F8() == 2) {
        if (var_r31->unk_44 != 0) {
            var_r31->unk_1C = 0;
            fn_1_B2C0(object);
        } else {
            var_r31->unk_14 = HuPadBtn[GWPlayerCfg[object->work[0]].pad_idx];
            var_r31->unk_10 = HuPadBtnDown[GWPlayerCfg[object->work[0]].pad_idx];
            var_f31 = HuPadStkX[GWPlayerCfg[object->work[0]].pad_idx];
            var_f30 = -HuPadStkY[GWPlayerCfg[object->work[0]].pad_idx];
            var_r31->unk_20 = atan2d(var_f31, var_f30);
            var_r31->unk_24 = 0.013888889f * sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
            if (var_r31->unk_24 > 1.0f) {
                var_r31->unk_24 = 1.0f;
            }
            var_r28 = var_r31->unk_1C;
            var_r31->unk_1C = 0;
            if (HuPadTrigL[GWPlayerCfg[object->work[0]].pad_idx] > 80) {
                var_r31->unk_1C = 1;
            }
            var_r31->unk_18 = var_r31->unk_1C & ~var_r28;
        }
    }
    fn_1_9298(object);
    if ((s32)var_r31->unk_50 != 0) {
        (void)var_r29;
    } else if (var_r31->unk_2C) {
        var_r29 = 1;
    }
    fn_1_91E0(object);
    fn_1_AD24(object);
    if (fn_1_26F8() == 3 && var_r29 && fn_1_27D0()) {
        fn_1_2770(object->work[0]);
        var_r31->unk_50 = 0;
        object->func = fn_1_8D30;
    }
}

void fn_1_8B0C(omObjData *object)
{
    Vec sp8;

    float var_f31;

    UnkM417Struct10 *var_r31;

    var_r31 = object->data;
    var_r31->unk_10 = var_r31->unk_18 = 0;
    var_r31->unk_14 = 0;
    var_r31->unk_20 = 0.0f;
    var_r31->unk_24 = 0.0f;

    switch (var_r31->unk_50) {
        case 0:
            sp8 = var_r31->unk_EC;
            sp8.y = 0.0f;
            var_f31 = PSVECMag(&sp8);
            if (var_f31 > 30.000002f) {
                var_r31->unk_20 = atan2d(-sp8.x, -sp8.z);
                var_r31->unk_24 = 0.01f * var_f31;
                if (var_r31->unk_24 > 1.0f) {
                    var_r31->unk_24 = 1.0f;
                }
            } else {
                var_r31->unk_20 = 0.0f;
                var_r31->unk_24 = 0.01f;
                fn_1_2770(object->work[0]);
                var_r31->unk_50++;
            }
            break;
        case 1:
            if (fn_1_2710() == 1) {
                var_r31->unk_28 = 0;
                if (fn_1_2740(object->work[0]) >= 0) {
                    fn_1_B8A0(object, 1);
                } else {
                    fn_1_B8A0(object, 2);
                }
                var_r31->unk_50++;
            }
            break;
        case 2:
            if (fn_1_BA2C(object)) {
                fn_1_27A0(object->work[0]);
            }
            break;
    }
    fn_1_9FF0(object);
    fn_1_9C14(object);
    fn_1_91E0(object);
    fn_1_AD24(object);
}

void fn_1_8D30(omObjData *object)
{
    UnkM417Struct10 *var_r31;

    var_r31 = object->data;
    var_r31->unk_10 = var_r31->unk_18 = 0;
    var_r31->unk_14 = 0;
    var_r31->unk_20 = 0.0f;
    var_r31->unk_24 = 0.0f;
    switch (var_r31->unk_50) {
        case 0:
            if (fn_1_2710() == 1) {
                var_r31->unk_28 = 0;
                if (fn_1_2740(object->work[0]) >= 0) {
                    var_r31->unk_68 = 0.0f;
                    fn_1_B8A0(object, 1);
                } else {
                    fn_1_B8A0(object, 2);
                }
                var_r31->unk_50++;
            }
            break;
        case 1:
            if (fn_1_BA2C(object)) {
                fn_1_27A0(object->work[0]);
            }
            break;
    }
    fn_1_9298(object);
    fn_1_91E0(object);
    fn_1_AD24(object);
}

void fn_1_8E44(omObjData *object)
{
    Vec sp14;
    Vec sp8;

    float var_f31;

    UnkM417Struct10 *var_r31;

    var_r31 = object->data;
    var_r31->unk_10 = var_r31->unk_18 = 0;
    var_r31->unk_14 = 0;
    var_r31->unk_20 = 0.0f;
    var_r31->unk_24 = 0.0f;
    switch (var_r31->unk_50) {
        case 0:
            sp8 = var_r31->unk_14C;
            sp8.y = 0.0f;
            if (PSVECMag(&sp8) > 0.0f) {
                PSVECNormalize(&sp8, &sp8);
            } else {
                sp8.x = 1.0f;
                sp8.z = 0.0f;
            }
            var_r31->unk_68 = atan2d(-sp8.x, -sp8.z);
            PSVECScale(&sp8, &var_r31->unk_E0, 1.6666667f);
            fn_1_B8A0(object, 5);
            Hu3DModelLayerSet(object->model[0], 0);
            Hu3DModelShadowReset(object->model[0]);
            var_r31->unk_50++;

        case 1:
            var_r31->unk_E0.y += -0.8166667f;
            if ((var_r31->unk_D4.y < -50.0f) && (var_r31->unk_9C < 0)) {
                var_r31->unk_9C = HuAudFXPlay(1483);
            }
            if (var_r31->unk_D4.y < -300.0f) {
                sp8 = var_r31->unk_D4;
                sp8.y = 0.0f;
                if (PSVECMag(&sp8) > 0.0f) {
                    PSVECNormalize(&sp8, &sp8);
                } else {
                    sp8.x = 0.0f;
                    sp8.z = 1.0f;
                }
                PSVECScale(&sp8, &sp14, 250.0f);
                sp14.y = -100.0f;
                PSVECSubtract(&sp14, &var_r31->unk_D4, &sp8);
                PSVECScale(&sp8, &var_r31->unk_E0, 1.0f / 60.0f);
                fn_1_B8A0(object, 6);
                var_r31->unk_50++;
            }
            break;
        case 2:
            if (-100.0f > var_r31->unk_D4.y) {
                break;
            }
            var_r31->unk_E0.x = var_r31->unk_E0.y = var_r31->unk_E0.z = 0.0f;
            fn_1_2770(object->work[0]);
            fn_1_27A0(object->work[0]);
            var_r31->unk_50++;
        case 3:
            var_f31 = fn_1_78BC(var_r31->unk_D4.x, var_r31->unk_D4.y, var_r31->unk_D4.z);
            var_r31->unk_D4.y += (0.1f * ((var_f31 - 80.0f) - var_r31->unk_D4.y));

            break;
    }
    PSVECAdd(&var_r31->unk_D4, &var_r31->unk_E0, &var_r31->unk_D4);
    fn_1_9FF0(object);
    fn_1_91E0(object);
    fn_1_AD24(object);
}

void fn_1_91E0(omObjData *object)
{
    UnkM417Struct10 *var_r31;

    var_r31 = object->data;
    var_r31->unk_5C++;
    var_r31->unk_54++;
    object->trans.x = var_r31->unk_C8.x;
    object->trans.y = var_r31->unk_C8.y;
    object->trans.z = var_r31->unk_C8.z;
    var_r31->unk_6C += var_r31->unk_70;
    if (var_r31->unk_6C > 0.45f) {
        var_r31->unk_6C = 0.45f;
    }
    var_r31->unk_64 = fn_1_2F08(var_r31->unk_64, var_r31->unk_68, var_r31->unk_6C);
    object->rot.y = var_r31->unk_64;
}

void fn_1_9298(omObjData *object)
{
    Vec sp20;
    Vec sp14;

    float var_f31;

    UnkM417Struct10 *var_r31;

    var_r31 = object->data;
    {
        Vec sp8 = { 0.0f, 1.0f, 0.0f };
        fn_1_9A1C(object);
        var_f31 = fn_1_78BC(var_r31->unk_F8.x, var_r31->unk_F8.y, var_r31->unk_F8.z);
        var_r31->unk_F8.y += (0.2f * (var_f31 - var_r31->unk_F8.y));
        var_f31 = 0.0f;
        if (var_r31->unk_24 > 0.05f && var_r31->unk_2C) {
            sp20.x = sind(90.0f + var_r31->unk_B4.x);
            sp20.y = 0.0f;
            sp20.z = cosd(90.0f + var_r31->unk_B4.x);
            sp14.x = sind(var_r31->unk_20);
            sp14.y = 0.0f;
            sp14.z = cosd(var_r31->unk_20);
            var_f31 = PSVECDotProduct(&sp20, &sp14);
            var_f31 *= (1.0f / 60.0f) * (30.0f * var_r31->unk_24);
        }
        var_r31->unk_B4.y += (0.1f * (var_f31 - var_r31->unk_B4.y));
        var_r31->unk_B4.x += var_r31->unk_B4.y;
        if (var_r31->unk_B4.x >= 360.0f) {
            var_r31->unk_B4.x -= 360.0f;
        } else if (var_r31->unk_B4.x < 0.0f) {
            var_r31->unk_B4.x += 360.0f;
        }
        MTXRotAxisDeg(var_r31->unk_1C4, &sp8, var_r31->unk_B4.x);
    }
    object->rot.y = var_r31->unk_68 = var_r31->unk_B4.x - 180.0f;
    object->trans.x = var_r31->unk_D4.x = var_r31->unk_F8.x = var_r31->unk_C8.x = var_r31->unk_B4.z * sind(var_r31->unk_B4.x);
    object->trans.z = var_r31->unk_D4.z = var_r31->unk_F8.z = var_r31->unk_C8.z = var_r31->unk_B4.z * cosd(var_r31->unk_B4.x);
    if (var_r31->unk_10 & 256) {
        var_r31->unk_A8 = 9;
    }
    if (var_r31->unk_A8) {
        var_r31->unk_A8--;
    }
    switch (var_r31->unk_A0) {
        case 0:
            var_r31->unk_2C = 1;
            var_r31->unk_34 = 0;
            if (var_r31->unk_28) {
                fn_1_B8A0(object, 0);
                if (var_r31->unk_A8) {
                    var_r31->unk_2C = 0;
                    var_r31->unk_38 = 0;
                    fn_1_B8A0(object, 7);
                    var_r31->unk_A4 = 9;
                    var_r31->unk_A0++;
                }
            }
            break;
        case 1:
            var_r31->unk_A4--;
            if (!var_r31->unk_A4) {
                var_r31->unk_30 = 1;
                fn_1_BC70(400.0f, 0.3f, &var_r31->unk_11C);
                var_r31->unk_E0.y = (1.0f / 60.0f) * var_r31->unk_11C.z;
                var_r31->unk_AC = 0.0f;
                var_r31->unk_A0++;
            }
            break;
        case 2:
            if (var_r31->unk_E0.y >= 0.0f) {
                var_r31->unk_AC += (1.0f / 60.0f);
            } else {
                var_r31->unk_AC -= (1.0f / 60.0f);
            }
            var_r31->unk_34 = 0;
            var_r31->unk_B0 = 0.0f;
            var_f31 = var_r31->unk_AC - 0.060000002f;
            if (var_f31 > 0.0f) {
                var_r31->unk_34 = 1;
                var_f31 = var_f31 * 9.009008f;
                if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                var_r31->unk_B0 = var_f31;
            }
            if (var_r31->unk_34 && var_r31->unk_10 & 320) {
                var_r31->unk_34 = 0;
                var_r31->unk_38 = 1;
                var_r31->unk_E0.y = 0.0f;
                fn_1_B8A0(object, 9);
                var_r31->unk_A0++;
            } else {
                var_r31->unk_E0.y += (0.016666668f * (0.016666668f * var_r31->unk_11C.w));
                var_r31->unk_D4.y += var_r31->unk_E0.y;
                if (var_r31->unk_D4.y <= var_r31->unk_F8.y) {
                    var_r31->unk_30 = 0;
                    var_r31->unk_34 = 0;
                    var_r31->unk_E0.y = 0.0f;
                    var_r31->unk_D4.y = var_r31->unk_F8.y;
                    var_r31->unk_A0 = 0;
                }
            }
            break;
        case 3:
            if (fn_1_BA2C(object)) {
                var_r31->unk_A0++;
            }
            break;
        case 4:
            var_r31->unk_E0.y += (0.016666668f * (0.016666668f * var_r31->unk_11C.w));
            var_r31->unk_D4.y += +var_r31->unk_E0.y;
            if (var_r31->unk_D4.y <= var_r31->unk_F8.y) {
                fn_1_7510(var_r31->unk_F8.x, 0.0f, var_r31->unk_F8.z, var_r31->unk_B0);
                HuAudFXEmiterPlay(1482, &var_r31->unk_D4);
                omVibrate(object->work[0], 12, 4, 2);
                var_r31->unk_30 = 0;
                var_r31->unk_E0.y = 0.0f;
                var_r31->unk_D4.y = var_r31->unk_F8.y;
                fn_1_B8A0(object, 10);
                var_r31->unk_A0 = var_r31->unk_A0 + 1;
            }
            break;
        case 5:
            if (fn_1_BA2C(object) != 0) {
                var_r31->unk_38 = 0;
                var_r31->unk_A0 = 0;
            }
            break;
    }
    if (!var_r31->unk_30) {
        var_r31->unk_D4.y = var_r31->unk_F8.y;
    }
}

void fn_1_9A1C(omObjData *object)
{
    float var_f31;
    float var_f30;

    s32 var_r31;
    UnkM417Struct10 *var_r30;
    UnkM417Struct10 *var_r29;
    UnkM417Struct10 *var_r28;
    s32 var_r27;

    var_r30 = object->data;
    var_r30->unk_C0++;
    if (((UnkM417Struct10 *)lbl_1_bss_898[0]->data)->unk_C4 == var_r30->unk_C0) {
        return;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        ((UnkM417Struct10 *)lbl_1_bss_898[var_r31]->data)->unk_C4 = var_r30->unk_C0;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = lbl_1_bss_898[var_r31]->data;
        if (!var_r29->unk_0C) {
            continue;
        }
        for (var_r27 = 0; var_r27 < 4; var_r27++) {
            if (var_r31 == var_r27) {
                continue;
            }
            var_r28 = lbl_1_bss_898[var_r27]->data;
            if (!var_r28->unk_0C) {
                continue;
            }
            var_f31 = fn_1_3024(var_r29->unk_B4.x, var_r28->unk_B4.x);
            if (fabs(var_f31) > 23.0) {
                continue;
            }
            if (var_f31 == 0.0f) {
                var_f30 = 11.5f;
            } else {
                var_f30 = 23.0 - fabs(var_f31);
                var_f30 = (0.5f * var_f30) * (var_f31 / fabs(var_f31));
            }
            var_r29->unk_B4.x -= var_f30;
            var_r28->unk_B4.x += var_f30;
        }
    }
}

void fn_1_9C14(omObjData *object)
{
    Qtrn sp28;
    Vec sp1C;
    Vec sp10;
    float spC;
    float sp8;

    float var_f31;
    float var_f30;
    float var_f29;

    UnkM417Struct10 *var_r31;

    var_r31 = object->data;
    if (var_r31->unk_24 > 0.0f) {
        var_r31->unk_68 = var_r31->unk_20;
    }
    if (var_r31->unk_24 > 0.05f) {
        var_r31->unk_E0.x = 0.01666666753590107 * (500.0 * (var_r31->unk_24 * sind(var_r31->unk_20)));
        var_r31->unk_E0.z = 0.01666666753590107 * (500.0 * (var_r31->unk_24 * cosd(var_r31->unk_20)));
        var_r31->unk_6C = 0.2f;
        var_r31->unk_70 = 0.0f;
        if (CharModelMotionShiftIDGet(var_r31->unk_00) < 0) {
            var_f30 = 0.5f;
            if (var_r31->unk_08 == 4) {
                var_f30 = 0.45f;
            }
            if (var_r31->unk_24 > var_f30) {
                fn_1_B8A0(object, 4);
                var_f29 = var_r31->unk_24;
            } else {
                fn_1_B8A0(object, 3);
                var_f29 = var_r31->unk_24 / var_f30;
            }
            CharModelMotionSpeedSet(var_r31->unk_00, var_f29);
        }
    } else {
        var_r31->unk_E0.x = var_r31->unk_E0.y = var_r31->unk_E0.z = 0.0f;
        if (var_r31->unk_28 && CharModelMotionShiftIDGet(var_r31->unk_00) < 0) {
            fn_1_B8A0(object, 0);
        }
    }
    PSVECSubtract(&var_r31->unk_D4, &var_r31->unk_104, &sp1C);
    if (fn_1_26F8() == 2) {
        sp1C.y += -5.8333335f * var_r31->unk_148;
    }
    PSMTXMultVec(var_r31->unk_224, &sp1C, &sp1C);
    PSVECAdd(&sp1C, &var_r31->unk_E0, &sp1C);
    sp10 = sp1C;
    sp10.y = 0.0f;
    var_f31 = sp8 = PSVECMag(&sp10);
    if (var_f31 > 150.0f) {
        var_f31 = 150.0f / var_f31;
        sp1C.x = sp1C.x * var_f31;
        sp1C.z *= var_f31;
    }
    sp1C.y = 80.0f;
    var_r31->unk_EC = sp1C;
    spC = atan2d(sp1C.x, sp1C.z);
    PSMTXMultVec(var_r31->unk_1C4, &sp1C, &sp1C);
    PSVECAdd(&sp1C, &var_r31->unk_F8, &var_r31->unk_D4);
    if (var_r31->unk_13C >= 0.95f) {
        var_r31->unk_3C = 1;
        return;
    }
    PSQUATNormalize(&var_r31->unk_194, &sp28);
    if (sp28.w < cos(0.4363323129985824)) {
        var_r31->unk_3C = 1;
    }
}

void fn_1_9FF0(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;

    UnkM417Struct10 *var_r31;
    s32 var_r30;
    UnkM417Struct2 *var_r29;
    s32 var_r28;

    var_r31 = object->data;
    {
        Quaternion sp3C;
        Quaternion sp2C = { 0.0f, 0.0f, 0.0f, 1.0f };
        Vec sp20;
        Vec sp14;
        Vec sp8 = { 0.0f, 0.0f, 0.0f };

        if (fn_1_26F8() == 2) {
            var_r31->unk_148 += 0.0011111111f;
            if (var_r31->unk_148 > 1.0f) {
                var_r31->unk_148 = 1.0f;
            }
        }
        var_r31->unk_1B4 = var_r31->unk_1A4;
        PSMTXCopy(var_r31->unk_1F4, var_r31->unk_224);
        var_r31->unk_104 = var_r31->unk_F8;
        var_f31 = fn_1_75BC();
        for (var_r30 = 0; var_r30 < 8; var_r30++) {
            var_f29 = 45.0f * var_r30;
            var_f31 += fn_1_78BC(0.5 * (150.0 * sind(var_f29)), 0.0f, 0.5 * (150.0 * cosd(var_f29)));
        }
        var_f31 *= 0.11111111f;
        var_r31->unk_F8.y = var_r31->unk_F8.y + var_r31->unk_98;
        if (var_f31 > var_r31->unk_F8.y || (!var_r31->unk_30 && fn_1_26F8() != 2)) {
            var_r31->unk_F8.y = var_r31->unk_F8.y + (0.1388889f * (var_f31 - var_r31->unk_F8.y));
            var_r31->unk_98 = var_r31->unk_F8.y - var_r31->unk_104.y;
            var_r31->unk_98 += -0.27222225f;
            var_r31->unk_30 = 0;
        } else {
            var_r31->unk_98 = var_r31->unk_F8.y - var_r31->unk_104.y;
            var_r31->unk_98 += -0.8166667f;
            var_r31->unk_30 = 1;
        }
        if (var_r31->unk_40) {
            var_r31->unk_12C += 1.0f / 60.0f;
            if (var_r31->unk_12C > 2.0f) {
                var_r31->unk_12C = 2.0f;
            }
        }
        var_r31->unk_130 += 1.0f / 60.0f;
        var_f28 = 0.1f * var_r31->unk_130;
        var_f26 = fmod(var_f28, 1.0);
        var_f25 = var_f26;
        var_r31->unk_134 = 360.0f * var_f25;
        var_f27 = var_r31->unk_130;
        var_f24 = fmod(var_f27, 1.0);
        var_f23 = var_f24;
        var_r31->unk_138 = 0.04712389037013054 * sind((360.0f * var_f23));

        sp8.x = sind(var_r31->unk_134);
        sp8.y = 0.0f;
        sp8.z = cosd(var_r31->unk_134);
        C_QUATRotAxisRad(&var_r31->unk_164, &sp8, var_r31->unk_138 * var_r31->unk_12C);
        if (!var_r31->unk_40) {
            sp20 = var_r31->unk_EC;
            sp20.y = 0.0f;
            var_f31 = (2.0f / 300.0f) * PSVECMag(&sp20);
            if (var_f31 <= 0.0f) {
                var_f31 = 0.0f;
                sp8.x = 1.0f;
                sp8.y = sp8.z = 0.0f;
            } else {
                if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                sp8.x = sp20.z;
                sp8.y = 0.0f;
                sp8.z = -sp20.x;
            }
            C_QUATRotAxisRad(&var_r31->unk_174, &sp8, 0.09424778f * var_f31);
            if (!var_r31->unk_30 && !var_r31->unk_40) {
                for (var_r29 = fn_1_7A28(); var_r29->unk_00 > -2; var_r29++) {
                    if (var_r29->unk_00 >= 0 && var_r29->unk_00 < 16) {
                        var_r28 = var_r29->unk_00;
                        var_f31 = var_r29->unk_08 * var_r29->unk_0C;
                        if (var_r31->unk_254[var_r28].y <= var_f31) {
                            var_r31->unk_254[var_r28].y += 0.044444446f;
                            var_r31->unk_254[var_r28].x = var_r29->unk_04;
                        }
                        if (fn_1_26F8() == 2 && var_r31->unk_254[var_r28].z <= var_f31) {
                            var_r31->unk_254[var_r28].z += 0.08888889f;
                        }
                    }
                }
            }
        }
        sp2C.w = 1.0f;
        sp2C.x = sp2C.y = sp2C.z = 0.0f;

        sp20.x = sp20.y = sp20.z = 0.0f;

        var_f30 = 0.0f;
        for (var_r30 = 0; var_r30 < 16; var_r30++) {
            if (var_r31->unk_254[var_r30].z > 0.0f) {
                var_f30 += 0.5f * var_r31->unk_254[var_r30].z;
                if (var_r31->unk_30 == 0) {
                    var_r31->unk_254[var_r30].z -= 1.0f / 60.0f;
                    if (var_r31->unk_254[var_r30].z < 0.0f) {
                        var_r31->unk_254[var_r30].z = 0.0f;
                    }
                }
            }
            if (var_r31->unk_254[var_r30].y > 0.0f) {
                sp20.x += var_r31->unk_254[var_r30].y * sind(var_r31->unk_254[var_r30].x);
                sp20.z += var_r31->unk_254[var_r30].y * cosd(var_r31->unk_254[var_r30].x);
                var_r31->unk_254[var_r30].y -= 0.012820514f;
                if (var_r31->unk_254[var_r30].y < 0.0f) {
                    var_r31->unk_254[var_r30].y = 0.0f;
                }
            }
        }
        if (var_f30 > 1.0f) {
            var_f30 = 1.0f;
        }
        var_f30 *= 1.0f / 60.0f;
        var_f30 *= var_r31->unk_148;
        var_r31->unk_144 = var_r31->unk_144 + (0.1f * (var_f30 - var_r31->unk_144));
        var_f31 = 90.0 + (atan2d(sp20.x, sp20.z));
        sp8.x = sind(var_f31);
        sp8.y = 0.0f;
        sp8.z = cosd(var_f31);
        var_f29 = PSVECMag(&sp20);
        if (var_f29 > 0.5f) {
            var_f29 = 0.5f;
        }
        C_QUATRotAxisRad(&sp2C, &sp8, 3.1415927f * var_f29 * 0.18f);
        if (!var_r31->unk_40) {
            if (fn_1_26F8() == 2) {
                sp20 = var_r31->unk_EC;
                sp20.y = 0.0f;
                var_f31 = PSVECMag(&sp20);
                var_f29 = 0.006666667f * var_f31;
                if (var_f31 > 0.0f) {
                    PSVECNormalize(&sp20, &sp20);
                }
                PSVECSubtract(&sp20, &var_r31->unk_14C, &sp14);
                if (PSVECMag(&sp14)) {
                    PSVECNormalize(&sp14, &sp14);
                }
                PSVECScale(&sp14, &sp14, (0.0033333336f * var_f29) + var_r31->unk_144);
                PSVECAdd(&var_r31->unk_14C, &sp14, &var_r31->unk_14C);
            } else {
                PSVECScale(&var_r31->unk_14C, &var_r31->unk_14C, 0.98f);
            }
            var_r31->unk_14C.y = 0.0f;
            var_f31 = PSVECMag(&var_r31->unk_14C);
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f / var_f31;
                var_r31->unk_14C.x *= var_f31;
                var_r31->unk_14C.z *= var_f31;
                var_f31 = 1.0f;
            }
            var_r31->unk_13C = var_f31;
            var_r31->unk_140 = atan2d(var_r31->unk_14C.x, var_r31->unk_14C.z);
            if (var_f31 > 0.0f) {
                sp8.x = var_r31->unk_14C.z;
                sp8.y = 0.0f;
                sp8.z = -var_r31->unk_14C.x;
            } else {
                sp8.x = 1.0f;
                sp8.y = sp8.z = 0.0f;
            }
            C_QUATRotAxisRad(&var_r31->unk_184, &sp8, 0.9424779f * var_f31);
        } else {
            sp8.x = var_r31->unk_14C.z;
            sp8.y = 0.0f;
            sp8.z = -var_r31->unk_14C.x;
            C_QUATRotAxisRad(&sp3C, &sp8, M_PI);
            C_QUATSlerp(&var_r31->unk_184, &sp3C, &var_r31->unk_184, 0.027777778f);
        }
        PSQUATMultiply(&var_r31->unk_174, &var_r31->unk_184, &var_r31->unk_194);
        PSQUATMultiply(&var_r31->unk_164, &var_r31->unk_194, &var_r31->unk_194);
        PSQUATMultiply(&sp2C, &var_r31->unk_194, &var_r31->unk_194);
        PSMTXQuat(var_r31->unk_1C4, &var_r31->unk_194);
        PSMTXInverse(var_r31->unk_1C4, var_r31->unk_1F4);
        PSQUATInverse(&var_r31->unk_194, &var_r31->unk_1A4);
    }
}

void fn_1_AD24(omObjData *object)
{
    UnkM417Struct10 *var_r30;

    var_r30 = object->data;
    Hu3DModelPosSetV(object->model[0], &var_r30->unk_D4);
    Hu3DModelRotSet(object->model[0], 0.0f, var_r30->unk_64, 0.0f);
    Hu3DModelPosSetV(object->model[1], &var_r30->unk_F8);
    PSMTXCopy(var_r30->unk_1C4, Hu3DData[object->model[1]].unk_F0);
}

void fn_1_ADC4(omObjData *object)
{
    Vec sp28;
    Vec sp1C;
    Vec sp10;

    float var_f31;
    float var_f30;

    UnkM417Struct10 *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = object->data;
    {
        float sp8[2] = { 30.000002f, 80.0f };

        if (!var_r31->unk_84) {
            sp28 = var_r31->unk_14C;
            sp28.y = 0.0f;
            var_f31 = 0.75f + (2.5f * (var_r31->unk_74 * var_r31->unk_74));
            PSVECScale(&sp28, &sp28, 150.0f * -var_f31);
            var_f31 = PSVECMag(&sp28);
            if (var_f31 > 150.0f) {
                var_f31 = 150.0f / var_f31;
                sp28.x *= var_f31;
                sp28.z *= var_f31;
            }
            sp28.x += (100.0 * ((0.9f - (0.3f * var_r31->unk_74)) * ((0.002 * (float)frandmod(1000)) - 1.0)));
            sp28.z += (100.0 * ((0.9f - (0.3f * var_r31->unk_74)) * ((0.002 * (float)frandmod(1000)) - 1.0)));
            sp1C = var_r31->unk_110;
            sp1C.y = 0.0f;
            PSVECSubtract(&sp28, &sp1C, &sp10);
            var_f31 = PSVECMag(&sp10);
            if (var_f31 > (100.0f * (1.2f - (0.3f * var_r31->unk_74)))) {
                var_r31->unk_110 = sp28;
            }
            var_r31->unk_84 = 60.0f * ((0.23f - (0.04f * var_r31->unk_74)) + (0.001f * ((0.4f - (0.15f * var_r31->unk_74)) * frandmod(1000))));
        } else {
            var_r31->unk_84--;
        }
        sp28 = var_r31->unk_110;
        sp28.y = 0.0f;
        sp1C = var_r31->unk_EC;
        sp1C.y = 0.0f;
        PSVECSubtract(&sp28, &sp1C, &sp10);
        var_f31 = PSVECMag(&sp10);
        if (var_r31->unk_48) {
            var_r30 = 1;
        } else {
            var_r30 = 0;
        }
        var_r29 = var_r30;
        if (var_f31 > sp8[var_r29]) {
            var_r31->unk_48 = 0;
            var_r31->unk_20 = fn_1_2F08(var_r31->unk_64, atan2d(sp10.x, sp10.z), 0.5f);
            var_f30 = 0.014285714f * var_f31;
            if (var_f30 > 1.0f) {
                var_f30 = 1.0f;
            }
            var_r31->unk_24 = var_f30;
            return;
        }
        var_r31->unk_48 = 1;
        var_r31->unk_110 = var_r31->unk_EC;
    }
}

void fn_1_B2C0(omObjData *object)
{
    UnkM417Struct10 *var_r31;
    s32 var_r29;

    var_r31 = object->data;
    var_r29 = 0;
    if (var_r31->unk_90) {
        var_r31->unk_90--;
    } else {
        var_r31->unk_88 = 1.0f;
        if (frandmod(1000) < 500) {
            var_r31->unk_88 = -1.0f;
        }
        var_r31->unk_8C = 0.001f * frandmod(1000);
        var_r31->unk_90 = 0.15f * frandmod(1000);
    }
    var_r31->unk_20 = var_r31->unk_B4.x + (90.0f * var_r31->unk_88);
    var_r31->unk_24 = 0.5f + (0.5f * var_r31->unk_74);
    if (lbl_1_bss_884 >= object->work[0]) {
        if (lbl_1_bss_880) {
            lbl_1_bss_880--;
        } else {
            lbl_1_bss_880 = 60.0f * (8.0f + (0.004f * frandmod(1000)));
        }
    }
    lbl_1_bss_884 = object->work[0];
    if (var_r31->unk_2C) {
        if (!var_r31->unk_4C && lbl_1_bss_880 < 132.0f && lbl_1_bss_880 > 30.0f) {
            var_r31->unk_80 = 0;
            var_r29 = 1;
        }
        if (!var_r31->unk_80) {
            if (var_r29) {
                var_r31->unk_80 = lbl_1_bss_880;
                var_r31->unk_80 -= (60.0f * (0.16f + (0.6f * (0.1f + (0.5f * var_r31->unk_74)))));
                var_r31->unk_4C = 1;
                if (var_r31->unk_80 > 240.0f) {
                    var_r31->unk_80 = 1;
                }
            } else {
                var_r31->unk_80 = 60.0f * (0.00080000004f * ((1.05f - var_r31->unk_74) * frandmod(1000)));
                var_r31->unk_80 += (var_r31->unk_8C * (30.0f + (0.03f * frandmod(1000))));
            }
        } else {
            var_r31->unk_80--;
            if (!var_r31->unk_80) {
                var_r31->unk_10 |= 256;
                var_r31->unk_7C = (0.5f * var_r31->unk_74) + (((1.2f * var_r31->unk_74) / 1000.0f) * frandmod(1000));
                if (var_r31->unk_7C < 0.25f) {
                    var_r31->unk_7C = 0.25f;
                }
                if (var_r31->unk_4C) {
                    var_r31->unk_7C = 0.0f;
                }
                var_r31->unk_4C = 0;
            }
        }
    }
    if (var_r31->unk_34 && ((var_r31->unk_E0.y < 0.0f && var_r31->unk_B0 < var_r31->unk_7C) || !lbl_1_bss_880)) {
        var_r31->unk_10 |= 256;
    }
}

void fn_1_B8A0(omObjData *object, u32 arg1)
{
    float var_f31;

    UnkM417Struct10 *var_r30;

    var_r30 = object->data;
    if (var_r30->unk_08 != arg1 && arg1 < 11) {
        var_f31 = 60.0f * lbl_1_data_114[arg1].unk_04;
        if (var_r30->unk_08 < 0) {
            var_f31 = 0.0f;
        }
        var_r30->unk_08 = arg1;
        CharModelMotionShiftSet(
            var_r30->unk_00, object->motion[lbl_1_data_114[arg1].unk_00], 60.0f * lbl_1_data_114[arg1].unk_08, var_f31, lbl_1_data_114[arg1].unk_10);
        if (lbl_1_data_114[arg1].unk_0C >= 0.0f) {
            Hu3DMotionShiftStartEndSet(*object->model, 60.0f * lbl_1_data_114[arg1].unk_08, 60.0f * lbl_1_data_114[arg1].unk_0C);
        }
    }
}

s32 fn_1_BA2C(omObjData *object)
{
    UnkM417Struct10 *var_r31;
    s32 var_r30;

    var_r31 = object->data;
    var_r30 = 0;
    if (CharModelMotionEndCheck(var_r31->unk_00) && CharModelMotionShiftIDGet(var_r31->unk_00) < 0) {
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_BAA0(omObjData *object, u32 arg1)
{
    s32 var_r27;

    var_r27 = 0;
    if (fn_1_BA2C(object)) {
        fn_1_B8A0(object, arg1);
        var_r27 = 1;
    }
    return var_r27;
}

void fn_1_BC70(float arg8, float arg9, Quaternion *arg0)
{
    arg0->x = arg9;
    arg0->y = arg8;
    arg0->w = (2.0f * -arg8) / (arg9 * arg9);
    arg0->z = -arg0->w * arg9;
}
