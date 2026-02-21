#include "ext_math.h"
#include "game/chrman.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/wipe.h"
#include "math.h"

#include "REL/m418Dll.h"
#include "version.h"

// types
typedef struct M418DllUnkStruct2 {
    omObjData *unk0;
    s32 unk4[4];
} M418DllUnkStruct2; // sizeof 0x14

typedef struct M418DllUnkStruct3 {
    omObjData *unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    f32 unk20;
    s32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    char unk40[0xC];
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
} M418DllUnkStruct3; // sizeof 0x60

typedef struct M418DllUnkStruct4 {
    omObjData *unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    union {
        f32 unk14;
        s32 unk14s;
    };
    union {
        f32 unk18;
        s32 unk18s;
    };
} M418DllUnkStruct4; // sizeof 0x1C

typedef struct M418DllUnkStruct6 {
    s32 unk0;
    s32 unk4[3];
    s32 unk10[3];
    s32 unk1C[3];
    s32 unk28[3];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
} M418DllUnkStruct6; // sizeof 0x44

typedef struct M418DllWorkStruct {
    omObjData *unk0;
    Vec unk4;
    Vec unk10[10];
    s32 unk88;
    s32 unk8C[10];
} M418DllWorkStruct;

// bss
M418DllUnkStruct6 lbl_1_bss_3EC;
M418DllUnkStruct3 lbl_1_bss_26C[4];
s32 lbl_1_bss_240[11];
M418DllUnkStruct lbl_1_bss_1F4;
M418DllUnkStruct2 lbl_1_bss_1E0;
M418DllUnkStruct4 lbl_1_bss_170[4];
M418DllUnkStruct4 lbl_1_bss_11C[3];
M418DllWorkStruct lbl_1_bss_68;
M418DllUnkStruct7 lbl_1_bss_50;
M418DllUnkStruct7 lbl_1_bss_38;
M418DllUnkStruct7 lbl_1_bss_20;
s32 lbl_1_bss_1C;
u32 lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
Process *lbl_1_bss_0;

// data
s32 lbl_1_data_0[2] = { -1, -1 };
s32 lbl_1_data_8 = -1;

void fn_1_0(void)
{
    Hu3DGLightCreate(-2500.0f, 5000.0f, 5000.0f, 0.0f, -1.0f, -1.0f, 0xFF, 0xD8, 0xA0);
}

void fn_1_74(void)
{
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;
    Vec sp2C = { 0.0f, 1100.0f, 1800.0f };
    Vec sp20 = { 0.0f, 600.0f, 600.0f };

    fn_1_B104(var_r31, sp2C, sp20);
    fn_1_B41C(var_r31);
    var_r31->rot.x++;
}

void fn_1_158(s32 arg0, f32 arg8)
{
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;

    var_r31->unk3C[arg0] = arg8;
}

f32 fn_1_180(s32 arg0)
{
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;

    if (var_r31->unk3C[arg0] != 0.0f) {
        var_r31->unk3C[arg0] *= -0.9f;
        if (var_r31->unk3C[arg0] >= -0.5f) {
            if (var_r31->unk3C[arg0] <= 0.5f) {
                var_r31->unk3C[arg0] = 0.0f;
            }
        }
    }
    return var_r31->unk3C[arg0];
}

void fn_1_248(M418DllFunc arg0)
{
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;

    var_r31->unk0 = arg0;
}

void fn_1_268(omObjData *object)
{
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;

    if (var_r31->unk0 != NULL) {
        var_r31->unk0();
    }

    Center.x = var_r31->center.x + fn_1_180(0);
    Center.y = var_r31->center.y + fn_1_180(1);
    Center.z = var_r31->center.z + fn_1_180(2);
    CRot.x = var_r31->rot.x;
    CRot.y = var_r31->rot.y;
    CRot.z = var_r31->rot.z;
    CZoom = var_r31->zoom;
}

void fn_1_500(void)
{
    M418DllUnkStruct *var_r31;
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 40.0f, 0.1f, 17500.0f, 1.2f);
    var_r31 = &lbl_1_bss_1F4;
    var_r31->unk0 = fn_1_74;
    omAddObjEx(lbl_1_bss_0, 0x7FDA, 0, 0, -1, omOutView);
    omAddObjEx(lbl_1_bss_0, 0x7FD9, 0, 0, -1, fn_1_268);
}

void fn_1_618(void)
{
    Vec sp20 = { -1500.0f, 2500.0f, 1000.0f };
    Vec sp14 = { 0.0f, 0.0f, 0.0f };
    Vec sp8 = { 0.0f, 1.0f, 0.0f };

    Hu3DShadowCreate(40.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.675f);
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);
}

void fn_1_6DC(s32 arg0)
{
    if (lbl_1_bss_8 == 0) {
        lbl_1_bss_8 = 1;
        lbl_1_bss_4 = arg0 * REFRESH_RATE;
    }
}

s32 fn_1_714(void)
{
    s32 var_r31 = 0;

    if (lbl_1_bss_8 == 3) {
        var_r31 = 1;
    }
    return var_r31;
}

void fn_1_748(void)
{
    if (lbl_1_bss_8 == 2) {
        lbl_1_bss_8 = 3;
        lbl_1_bss_4 = 30;
    }
}

void fn_1_780(omObjData *object)
{
    switch (lbl_1_bss_8) {
        case 1:
            if (lbl_1_data_8 == -1) {
                lbl_1_data_8 = MGSeqCreate(1, lbl_1_bss_4 / REFRESH_RATE, -1, -1);
            }
            lbl_1_bss_8 = 2;
            break;
        case 2:
            lbl_1_bss_4--;
            if (lbl_1_data_8 != -1) {
                MGSeqParamSet(lbl_1_data_8, 1, ((lbl_1_bss_4 + REFRESH_RATE - 1) / REFRESH_RATE));
            }
            if (lbl_1_bss_4 <= 0) {
                lbl_1_bss_4 = 30;
                lbl_1_bss_8 = 3;
            }
            break;
        case 3:
            if (lbl_1_data_8 != -1) {
                MGSeqParamSet(lbl_1_data_8, 2, -1);
                lbl_1_data_8 = -1;
            }
            lbl_1_bss_4 = 0;
            lbl_1_bss_8 = 0;
            break;
    }
}

s32 fn_1_950(s32 arg0)
{

    if ((rand8() % arg0) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void fn_1_998(omObjData *object)
{
    s32 var_r31;
    M418DllUnkStruct2 *var_r30 = &lbl_1_bss_1E0;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        switch (var_r30->unk4[var_r31]) {
            case 1:
                fn_1_ABC4(object, var_r31 + 1, var_r31 + 1, 0, 2);
                var_r30->unk4[var_r31] = 99;
                break;
            case 2:
                fn_1_ABC4(object, var_r31 + 1, var_r31 + 1, 0, 0);
                var_r30->unk4[var_r31] = 99;
                break;
            case 3:
                HuAudFXPlay(0x5DD);
                Hu3DModelAttrSet(object->model[var_r31 + 1], 0x40000004);
                var_r30->unk4[var_r31] = 99;
                break;
        }
    }
}

void fn_1_AA8(omObjData *object)
{
    Mtx sp10;
    char *sp8[2] = { "scene02-dai1_null", "scene02-dai2_null1" };
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        Hu3DModelObjMtxGet(object->model[5], sp8[var_r31], sp10);
        Hu3DModelPosSet(object->model[var_r31 + 6], sp10[0][3], sp10[1][3], sp10[2][3]);
    }
    object->func = fn_1_998;
}

void fn_1_B4C(omObjData *object)
{
    s32 sp8[3] = { 0x310021, 0x310022, 0x310023 };
    s32 var_r30;

    object->model[0] = Hu3DModelCreateFile(0x310011);
    Hu3DModelShadowMapSet(object->model[0]);

    for (var_r30 = 1; var_r30 < 4; var_r30++) {
        object->model[var_r30] = Hu3DModelCreateFile(sp8[var_r30 - 1]);
        object->motion[var_r30] = Hu3DMotionIDGet(object->model[var_r30]);
        Hu3DModelShadowMapSet(object->model[var_r30]);
        Hu3DModelPosSet(object->model[var_r30], 0.0f, 0.0f, 0.0f);
        fn_1_ABC4(object, var_r30, var_r30, 0, 2);
    }
    object->model[4] = Hu3DModelCreateFile(0x310016);
    object->model[5] = Hu3DModelCreateFile(0x310018);

    for (var_r30 = 6; var_r30 < 8; var_r30++) {
        object->model[var_r30] = Hu3DModelCreateFile(0x310026);
        object->motion[var_r30] = Hu3DMotionIDGet(object->model[var_r30]);
        Hu3DModelScaleSet(object->model[var_r30], 2.0f, 2.0f, 2.0f);
        Hu3DModelLayerSet(object->model[var_r30], 1);
        fn_1_ABC4(object, var_r30, var_r30, 0, 1);
    }

    for (var_r30 = 8; var_r30 < 11; var_r30++) {
        object->model[var_r30] = Hu3DModelCreateFile(0x31002A);
        object->motion[var_r30] = Hu3DJointMotion(object->model[var_r30], HuDataSelHeapReadNum(0x31002E, MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelPosSet(object->model[var_r30], -350.0f + 360.0f * (var_r30 - 8), -200.0f, -660.0f);
        fn_1_ABC4(object, var_r30, var_r30, 0, 1);
    }
    object->func = fn_1_AA8;
}

void fn_1_E74(omObjData *object)
{
    Mtx sp18;
    f32 var_f31;

    M418DllUnkStruct4 *temp_r30;
    M418DllUnkStruct4 *temp_r29;
    M418DllUnkStruct3 *temp_r28;
    M418DllUnkStruct4 *temp_r27;
    M418DllUnkStruct6 *temp_r26;
    HsfObject *temp_r25;
    ModelData *temp_r24;

    temp_r26 = &lbl_1_bss_3EC;
    temp_r28 = &lbl_1_bss_26C[temp_r26->unk0];
    temp_r30 = &lbl_1_bss_170[object->work[0]];
    if (object->work[1] == 0) {
        fn_1_ABC4(object, 2, 2, 0, 2);
    }
    else if (object->work[1] == 1) {
        Hu3DModelAttrReset(object->model[3], 1);
        Hu3DModelAttrReset(object->model[4], 1);
        Hu3DModelAttrReset(object->model[5], 1);
        Hu3DModelAttrReset(object->model[6], 1);
        fn_1_ABC4(object, 2, 2, 0, 0);
        fn_1_ABC4(object, 3, 3, 0, 0);
        fn_1_ABC4(object, 4, 4, 0, 1);
        object->work[1] = 2;
        lbl_1_bss_240[5] = HuAudFXPlay(0x5D6);
    }
    else if (object->work[1] == 2) {
        if (Hu3DMotionEndCheck(object->model[3]) != 0) {
            object->work[1] = 3;
            object->work[2] = 0;
            temp_r30->unkC = 1;
            HuAudFXFadeOut(lbl_1_bss_240[5], 0x3E8);
        }
    }
    else if (object->work[1] == 3) {
        temp_r29 = &lbl_1_bss_170[object->work[0]];
        temp_r29->unkC = 2;
        temp_r29->unk4 += 1.0f;
        if (temp_r29->unk4 >= 20.0f) {
            temp_r29->unk4 = 20.0f;
        }
        if (object->work[2]++ >= 0x5A) {
            if (temp_r29->unk10 == 1) {
                object->work[1] = 5;
                temp_r29->unk8 = 0.0f;
            }
            else {
                HuAudFXPlay(0x5D2);
                object->work[1] = 4;
                Hu3DModelObjMtxGet(object->model[0], "taihou-null4", sp18);
                Hu3DModelPosSet(object->model[5], sp18[0][3], sp18[1][3], sp18[2][3]);
                fn_1_ABC4(object, 5, 5, 0, 0);
                fn_1_158(2, 256.0f);
            }
            temp_r29->unkC = 3;
        }
    }
    else if (object->work[1] == 4) {
        if ((Hu3DMotionEndCheck(object->model[5]) != 0) || (temp_r30->unk10 == 1)) {
            object->work[1] = 99;
            Hu3DModelAttrSet(object->model[3], 1);
            Hu3DModelAttrSet(object->model[4], 1);
            Hu3DModelAttrSet(object->model[5], 1);
        }
    }
    else if (object->work[1] == 5 || object->work[1] == 6) {
        if (temp_r30->unk8 > 1.7f) {
            temp_r30->unk8 = 1.7f;
        }
        if (object->work[1] == 5) {
            var_f31 = temp_r30->unk8 * temp_r30->unk8 * (temp_r30->unk8 >= 0.0f ? -3.5f : 3.5f);
            temp_r30->unk4 += var_f31;
        }
        else {
            var_f31 = temp_r30->unk8 * temp_r30->unk8 * (temp_r30->unk8 >= 0.0f ? -1.25f : 1.25f);
            temp_r30->unk4 += var_f31;
        }
        if (temp_r30->unk4 <= 0.0f && object->work[1] == 5) {
            temp_r30->unk4 = 0.0f;
            temp_r30->unk8 = -1.47f;
            object->work[1] = 6;
            fn_1_158(1, 4.0f);
            omVibrate(temp_r28->unk4, 0xC, 6, 6);
            HuAudFXPlay(0x5DA);
        }
        else {
            if ((temp_r30->unk4 <= 0.0f) && (object->work[1] == 6)) {
                Hu3DModelObjMtxGet(object->model[0], "taihou-null4", sp18);
                Hu3DModelPosSet(object->model[6], sp18[0][3], sp18[1][3], sp18[2][3]);
                fn_1_158(1, 4.0f);
                omVibrate(temp_r28->unk4, 0xC, 6, 6);
                temp_r30->unk4 = 0.0f;
                temp_r30->unk8 = 0.0f;
                object->work[1] = 4;
                fn_1_ABC4(object, 6, 6, 0, 0);
                HuAudFXPlay(0x5DA);
                HuAudFXPlay(0x5DB);
            }
        }
        temp_r30->unk8 += 0.11f;
    }
    if (object->work[1] != 0) {
        const char *sp8[4] = { "doukasen-null_B", "doukasen-null_A", "doukasen-null_X", "doukasen-null_Y" };
        Hu3DModelObjMtxGet(object->model[3], sp8[object->work[0]], sp18);
        Hu3DModelPosSet(object->model[4], sp18[0][3], sp18[1][3], sp18[2][3]);
    }
    temp_r27 = &lbl_1_bss_170[object->work[0]];
    temp_r25 = Hu3DModelObjPtrGet(object->model[0], "taihou-taihou");
    temp_r25->data.base.rot.x = temp_r27->unk4;
    temp_r24 = &Hu3DData[object->model[1]];
    temp_r24->rot.x = temp_r27->unk4;
}

void fn_1_14F0(omObjData *arg0)
{
    s32 var_r30 = arg0->work[0];
    s32 sp28[4] = { 0x310012, 0x310013, 0x310015, 0x310014 };
    s32 sp18[4] = { 0x310019, 0x31001A, 0x31001B, 0x31001C };
    s32 sp8[4] = { 0x31001D, 0x31001E, 0x31001F, 0x310020 };

    arg0->model[0] = Hu3DModelCreateFile(0x310010);
    omSetTra(arg0, -540.0f + (360.0f * var_r30), 115.0f, -900.0f);
    arg0->model[1] = Hu3DModelCreateFile(sp28[var_r30]);
    Hu3DModelPosSet(arg0->model[1], -540.0f + (360.0f * var_r30), 115.0f, -900.0f);
    arg0->model[2] = Hu3DModelCreateFile(sp18[var_r30]);
    arg0->motion[2] = Hu3DMotionIDGet(arg0->model[2]);
    fn_1_ABC4(arg0, 2, 2, 0, 2);
    arg0->model[3] = Hu3DModelCreateFile(sp8[var_r30]);
    arg0->motion[3] = Hu3DMotionIDGet(arg0->model[3]);
    Hu3DModelAttrSet(arg0->model[3], 1);
    fn_1_ABC4(arg0, 3, 3, 0, 2);
    arg0->model[4] = Hu3DModelCreateFile(0x310025);
    arg0->motion[4] = Hu3DMotionIDGet(arg0->model[4]);
    Hu3DModelAttrSet(arg0->model[4], 1);
    fn_1_ABC4(arg0, 4, 4, 0, 2);
    arg0->model[5] = Hu3DModelCreateFile(0x310024);
    arg0->motion[5] = Hu3DMotionIDGet(arg0->model[5]);
    Hu3DModelAttrSet(arg0->model[5], 1);
    fn_1_ABC4(arg0, 5, 5, 0, 2);
    arg0->model[6] = Hu3DModelCreateFile(0x310028);
    arg0->motion[6] = Hu3DMotionIDGet(arg0->model[6]);
    Hu3DModelAttrSet(arg0->model[6], 1);
    fn_1_ABC4(arg0, 6, 6, 0, 2);
    Hu3DModelScaleSet(arg0->model[6], 3.0f, 3.0f, 3.0f);
    arg0->func = fn_1_E74;
}

void fn_1_18AC(omObjData *object)
{
    M418DllUnkStruct4 *var_r31;

    var_r31 = &lbl_1_bss_11C[object->work[0]];
    if (var_r31->unk14 == 0.0f) {
        var_r31->unk14 = 1.0f;
    }
}

s32 fn_1_18FC(omObjData *object, Vec arg1, f32 arg8, f32 arg9)
{
    M418DllUnkStruct4 *temp_r30;
    s32 var_r28;
    f32 var_f31;
    f32 var_f30;
    f32 var_f27;
    f32 var_f26;
    f32 var_f24;
    f32 var_f20;

    var_r28 = 0;
    temp_r30 = &lbl_1_bss_11C[object->work[0]];
    var_f31 = arg1.x - object->trans.x;
    var_f30 = object->trans.z - arg1.z;
    var_f26 = 90.0 + atan2d(var_f30, var_f31);
    var_f27 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    if (var_f27 <= 15.0f) {
        var_f31 = var_f30 = 0.0f;
    }
    else {
        var_f31 = 55.0f * (var_f31 / var_f27);
        var_f30 = 55.0f * (var_f30 / var_f27);
    }
    if (temp_r30->unk14 == 1.0f) {
        temp_r30->unk18 = -1.47f;
    }
    var_f27 = arg9 * (sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) / 72.0f);
    if (var_f27 >= arg9) {
        var_f27 = arg9;
    }
    else if (var_f27 <= 1.0f) {
        var_f31 = var_f30 = var_f27 = 0.0f;
        var_r28 = 1;
    }
    if (var_f31 != 0.0f || var_f30 != 0.0f || arg8 >= 0.0f) {
        if (arg8 >= 0.0f && var_f31 == 0.0f && var_f30 == 0.0f) {
            var_f26 = arg8;
        }
        if (var_f26 >= 180.0f) {
            if (object->rot.y - var_f26 >= 180.0f) {
                object->rot.y -= 360.0f;
            }
            if (object->rot.y - var_f26 < -180.0f) {
                object->rot.y += 360.0f;
            }
        }
        else {
            if (object->rot.y - var_f26 > 180.0f) {
                object->rot.y -= 360.0f;
            }
            if (object->rot.y - var_f26 <= -180.0f) {
                object->rot.y += 360.0f;
            }
        }
        object->rot.y = (((9.0f * object->rot.y) + var_f26) / 10.0f);
    }
    object->trans.x += var_f27 * sind(object->rot.y);
    object->trans.z += var_f27 * cosd(object->rot.y);
    if (temp_r30->unk14) {
        temp_r30->unk14 = 2.0f;
        if (temp_r30->unk18 > 1.7f) {
            temp_r30->unk18 = 1.7f;
        }
        var_f20 = (temp_r30->unk18 * temp_r30->unk18) * (temp_r30->unk18 >= 0.0f ? -3.5f : 3.5f);
        object->trans.y += var_f20;
        if (object->trans.y <= arg1.y) {
            object->trans.y = arg1.y;
            temp_r30->unk14 = temp_r30->unk18 = 0.0f;
            var_r28 = 2;
        }
        temp_r30->unk18 += 0.11f;
    }
    if (var_f27 > 0.0f) {
        fn_1_AD14(object, 0, 1, 10, 1);
    }
    else {
        fn_1_AD14(object, 0, 0, 10, 1);
    }
    return var_r28;
}

s32 fn_1_20B0(omObjData *object, Vec arg1, f32 arg8, f32 arg9, s32 arg2)
{
    if (arg2 == 1)
        fn_1_18AC(object);
    return fn_1_18FC(object, arg1, arg9, arg8);
}

Vec lbl_1_data_8C[9] = { { 140.0f, 0.0f, -90.0f }, { -200.0f, 0.0f, 50.0f }, { -300.0f, 0.0f, -150.0f }, { -250.0f, 0.0f, -500.0f },
    { 0.0f, 0.0f, 150.0f }, { 700.0f, 0.0f, 50.0f }, { 1000.0f, -50.0f, 500.0f }, { 1000.0f, -100.0f, 500.0f }, { 1000.0f, -150.0f, 500.0f } };

s32 fn_1_2178(omObjData *object)
{
    s32 var_r30;

    switch (object->work[1]) {
        case 1:
            object->work[2] = 0;
            object->work[1] = 10;
        case 10:
            fn_1_20B0(object, lbl_1_data_8C[1], 0.0f, 25.0f, 0);
            if (object->work[2]++ >= 15) {
                object->work[1] = 11;
                object->work[2] = 0;
            }
            break;
        case 11:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[1], 6.0f, -1.0f, 0);
            if (var_r30 != 0) {
                object->work[1] = 12;
                object->work[2] = 0;
            }
            break;
        case 12:
            fn_1_20B0(object, lbl_1_data_8C[1], 0.0f, 0.0f, 0);
            if (object->work[2]++ >= 15) {
                object->work[1] = 13;
                object->work[2] = 0;
            }
            break;

        case 2:
            object->work[2] = 0;
            object->work[1] = 0x14;
        case 20:
            fn_1_20B0(object, lbl_1_data_8C[0], 0.0f, 25.0f, 0);
            if (object->work[2]++ >= 15) {
                object->work[1] = 21;
                object->work[2] = 0;
            }
            break;
        case 21:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[4], 6.0f, -1.0f, 0);
            if (var_r30 != 0) {
                object->work[1] = 22;
                object->work[2] = 0;
            }
            break;
        case 22:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[0], 6.0f, 0.0f, 0);
            if (var_r30 != 0) {
                object->work[1] = 24;
                object->work[2] = 0;
            }
            break;
        case 23:
            fn_1_20B0(object, lbl_1_data_8C[1], 0.0f, 0.0f, 0);
            if (object->work[2]++ >= 30) {
                object->work[1] = 24;
                object->work[2] = 0;
            }
            break;
        case 3:
            object->work[2] = 0;
            object->work[1] = 30;
        case 30:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[5], 6.0f, -1.0f, 0);
            if (var_r30 == 1) {
                object->work[1] = 31;
                object->work[2] = 0;
            }
            break;
        case 31:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[6], 6.0f, -1.0f, 1);
            if (var_r30 != 0) {
                object->work[1] = 32;
                object->work[2] = 0;
            }
            break;
        case 32:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[7], 6.0f, -1.0f, 1);
            if (var_r30 != 0) {
                object->work[1] = 33;
                object->work[2] = 0;
            }
            break;
        case 33:
            var_r30 = fn_1_20B0(object, lbl_1_data_8C[8], 6.0f, -1.0f, 1);
            if (var_r30 != 0) {
                object->work[1] = 34;
                object->work[2] = 0;
            }
            break;
    }
}

void fn_1_2894(omObjData *object)
{
    Mtx sp3C;
    Mtx spC;
    M418DllUnkStruct6 *sp8;
    f32 temp_f31;

    sp8 = &lbl_1_bss_3EC;
    temp_f31 = 0.5f + (0.5f * (CRot.x / 90.0f));
    Hu3DModelObjMtxGet(object->model[0], "g031m1-itemhook_R", spC);
    Hu3DModelObjMtxGet(object->model[5], "g031i00-itemhook_eff", sp3C);
    Hu3DModelRotSet(object->model[6], 0.0f, -object->rot.y, 0.0f);
    Hu3DModelScaleSet(object->model[6], 0.35f, temp_f31, 0.35f);
    fn_1_2178(object);
}

void fn_1_29A0(omObjData *object)
{
    u32 temp_r30;

    temp_r30 = object->work[0];
    object->model[0] = Hu3DModelCreateFile(0x31002A);
    object->motion[0] = Hu3DJointMotionFile(object->model[0], 0x31002B);
    object->motion[1] = Hu3DJointMotionFile(object->model[0], 0x31002C);
    object->motion[2] = Hu3DJointMotionFile(object->model[0], 0x31002D);
    object->motion[3] = Hu3DJointMotionFile(object->model[0], 0x31002E);
    omSetTra(object, lbl_1_data_8C[temp_r30].x, lbl_1_data_8C[temp_r30].y, lbl_1_data_8C[temp_r30].z);
    fn_1_ABC4(object, 0, 0, 0, 1);
    object->model[5] = Hu3DModelCreateFile(0x31002F);
    Hu3DModelHookSet(object->model[0], "g031m1-itemhook_R", object->model[5]);
    object->model[6] = Hu3DModelCreateFile(0x310027);
    object->motion[6] = Hu3DMotionIDGet(object->model[6]);
    Hu3DModelHookSet(object->model[5], "g031i00-itemhook_eff", object->model[6]);
    fn_1_ABC4(object, 6, 6, 0, 1);
    object->work[1] = -1;
    Hu3DModelShadowSet(object->model[0]);
    object->func = fn_1_2894;
}

void fn_1_2BC4(Vec arg0)
{
    M418DllWorkStruct *var_r31 = &lbl_1_bss_68;
    var_r31->unk4.x = arg0.x;
    var_r31->unk4.y = arg0.y;
    var_r31->unk4.z = arg0.z;
    var_r31->unk88 = 0;
    var_r31->unk0->work[0] = 1;
}

void fn_1_2C0C(omObjData *object)
{
    ModelData *temp_r28;
    M418DllWorkStruct *var_r31 = &lbl_1_bss_68;
    s32 var_r30;

    switch (object->work[0]) {
        case 1:
            for (var_r30 = 0; var_r30 < 10; var_r30++) {
                var_r31->unk10[var_r30].x = (var_r31->unk4.x + 50.0 * cosd(36.0f * var_r30)) + (rand8() % 25);
                var_r31->unk10[var_r30].y = (var_r31->unk4.y + 50.0 * sind(36.0f * var_r30)) + (rand8() % 25);
                var_r31->unk10[var_r30].z = var_r31->unk4.z;
                var_r31->unk8C[var_r30] = (rand8() % 5) + 10;
                Hu3DModelPosSet(object->model[var_r30 + 1], var_r31->unk4.x, var_r31->unk4.y, var_r31->unk4.z);
                Hu3DModelTPLvlSet(object->model[var_r30 + 1], 1.0f);
            }
            object->work[0] = 2;
            break;
        case 2:
            for (var_r30 = 0; var_r30 < 10; var_r30++) {
                temp_r28 = &Hu3DData[object->model[var_r30 + 1]];
                temp_r28->pos.x = fn_1_A920(temp_r28->pos.x, var_r31->unk10[var_r30].x, var_r31->unk8C[var_r30]);
                temp_r28->pos.y = fn_1_A920(temp_r28->pos.y, var_r31->unk10[var_r30].y, var_r31->unk8C[var_r30]);
                temp_r28->pos.z = fn_1_A920(temp_r28->pos.z, var_r31->unk10[var_r30].z, var_r31->unk8C[var_r30]);
                if (var_r31->unk88 >= 20) {
                    Hu3DModelTPLvlSet(object->model[var_r30 + 1], 1.0f - (0.1f * (var_r31->unk88 - 0x14)));
                }
            }
            if (var_r31->unk88 >= 30) {
                object->work[0] = 0;
            }
            var_r31->unk88++;
    }
}

void fn_1_3054(omObjData *object)
{
    s32 var_r30;

    for (var_r30 = 1; var_r30 < 11; var_r30++) {
        object->model[var_r30] = Hu3DModelCreateFile(0x310029);
        Hu3DModelPosSet(object->model[var_r30], 0.0f, -500.0f, 0.0f);
        Hu3DModelScaleSet(object->model[var_r30], 10.0f, 10.0f, 10.0f);
    }
    object->work[0] = 0;
    object->func = fn_1_2C0C;
}

void fn_1_3138(void)
{
    M418DllUnkStruct3 *temp_r31;
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        temp_r31 = &lbl_1_bss_26C[var_r30];
        temp_r31->unk4 = var_r30;
        temp_r31->unk8 = GWPlayerCfg[temp_r31->unk4].group;
        if (temp_r31->unk8 == 0) {
            temp_r31->unk8 = 0;
        }
        else {
            temp_r31->unk8 = 1;
        }
        temp_r31->unkC = GWPlayerCfg[temp_r31->unk4].iscom;
        if (temp_r31->unkC != 0) {
            temp_r31->unk10 = GWPlayerCfg[temp_r31->unk4].diff;
        }
        else {
            temp_r31->unk10 = 0;
        }
        temp_r31->unk14 = GWPlayerCfg[temp_r31->unk4].character;
        temp_r31->unk18 = GWPlayerCfg[temp_r31->unk4].pad_idx;
    }
}

char *lbl_1_data_1C0[8] = { "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r",
    "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r" };

void fn_1_3240(omObjData *object)
{
    Mtx sp14;
    Vec sp8;
    M418DllUnkStruct3 *temp_r28;
    ModelData *temp_r30;
    M418DllWorkStruct *var_r29;

    temp_r30 = &Hu3DData[object->model[11]];
    temp_r28 = &lbl_1_bss_26C[object->work[0]];
    switch (object->work[1]) {
        case 1:
            Hu3DModelHookReset(object->model[0]);
            Hu3DModelObjMtxGet(object->model[0], lbl_1_data_1C0[temp_r28->unk14], sp14);
            Hu3DModelPosSet(object->model[11], sp14[0][3], sp14[1][3], sp14[2][3]);
            temp_r30->rot.y = object->rot.y;
            object->work[1] = 2;
            object->work[2] = 0;
            break;
        case 2:
            fn_1_AD14(object, 0, 0, 0x1E, 1);
            temp_r30->pos.y = fn_1_A920(temp_r30->pos.y, 350.0f, 30.0f);
            temp_r30->rot.x += 30.0f;
            if (object->work[2]++ >= 0x1EU) {
                HuAudFXPlay(0x5DE);
                fn_1_2BC4(temp_r30->pos);
                Hu3DModelAttrSet(object->model[11], 1);
                object->work[1] = object->work[2] = 0;
            }
            break;
    }
}

void fn_1_3408(omObjData *object)
{
    M418DllUnkStruct3 *temp_r31;

    temp_r31 = &lbl_1_bss_26C[object->work[0]];
    if (temp_r31->unk1C == 0) {
        temp_r31->unk1C = 1;
    }
}

void fn_1_3444(omObjData *object, Vec arg1, f32 arg8, f32 arg9)
{
    s32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    M418DllUnkStruct3 *temp_r28;
    M418DllUnkStruct3 *temp_r30;

    f32 var_f31;
    f32 var_f30;
    f32 temp_f29;
    f32 temp_f28;
    f32 var_f24;
    f32 var_f23;
    f32 var_f22;

    s32 var_r27;
    s32 var_r29;

    sp24 = 0;
    var_r27 = 0;
    temp_r30 = &lbl_1_bss_26C[object->work[0]];
    var_f31 = arg1.x - object->trans.x;
    var_f30 = object->trans.z - arg1.z;
    var_f23 = 90.0 + atan2d(var_f30, var_f31);
    var_f24 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    if (var_f24 <= 30.0f) {
        var_f31 = var_f30 = 0.0f;
    }
    else {
        var_f31 = 55.0f * (var_f31 / var_f24);
        var_f30 = 55.0f * (var_f30 / var_f24);
    }
    if (temp_r30->unk1C == 1) {
        temp_r30->unk20 = -1.47f;
    }
    var_f24 = arg9 * (sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) / 72.0f);
    if (var_f24 >= arg9) {
        var_f24 = arg9;
    }
    else if (var_f24 <= 1.0f) {
        var_f31 = var_f30 = var_f24 = 0.0f;
    }
    if (var_f31 != 0.0f || var_f30 != 0.0f || arg8 >= 0.0f) {
        if (arg8 >= 0.0f && var_f31 == 0.0f && var_f30 == 0.0f) {
            var_f23 = arg8;
        }
        if (var_f23 >= 180.0f) {
            if (object->rot.y - var_f23 >= 180.0f) {
                object->rot.y -= 360.0f;
            }
            if (object->rot.y - var_f23 < -180.0f) {
                object->rot.y += 360.0f;
            }
        }
        else {
            if (object->rot.y - var_f23 > 180.0f) {
                object->rot.y -= 360.0f;
            }
            if (object->rot.y - var_f23 <= -180.0f) {
                object->rot.y += 360.0f;
            }
        }
        object->rot.y = (((4.0f * object->rot.y) + var_f23) / 5.0f);
    }
    var_r27 = 0;
    sp1C = object->trans.x + (50.0 * cosd(object->rot.y - 90.0f));
    sp18 = object->trans.z - (50.0 * sind(object->rot.y - 90.0f));

    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (var_r29 == object->work[0])
            continue;
        temp_r28 = &lbl_1_bss_26C[var_r29];
        temp_f29 = temp_r28->unk0->trans.x;
        temp_f28 = temp_r28->unk0->trans.z;
        temp_f29 -= sp1C;
        temp_f28 -= sp18;
        if (sqrtf((temp_f29 * temp_f29) + (temp_f28 * temp_f28)) < 100.0f) {
            var_r27 = 1;
            break;
        }
    }
    if (var_r27 == 0) {
        object->trans.x = object->trans.x + (var_f24 * sind(object->rot.y));
        object->trans.z = object->trans.z + (var_f24 * cosd(object->rot.y));
    }
    if (temp_r30->unk1C != 0) {
        temp_r30->unk1C = 2;
        if (temp_r30->unk20 > 1.7f) {
            temp_r30->unk20 = 1.7f;
        }
        sp20 = temp_r30->unk20 * temp_r30->unk20 * (temp_r30->unk20 >= 0.0f ? -17.5f : 17.5f);
        object->trans.y += sp20;
        if (object->trans.y <= 0.0f) {
            object->trans.y = 0.0f;
            temp_r30->unk1C = temp_r30->unk20 = 0.0f;
            omVibrate(temp_r30->unk4, 0xC, 6, 6);
        }
        temp_r30->unk20 += 0.11f;
    }
    if (temp_r30->unk1C != 0) {
        fn_1_AD14(object, 0, 3, 10, 0);
        return;
    }
    if (var_f24 >= 6.75f) {
        fn_1_AD14(object, 0, 2, 10, 1);
        return;
    }
    if (var_f24 > 0.0f) {
        fn_1_AD14(object, 0, 1, 10, 1);
        return;
    }
    fn_1_AD14(object, 0, 0, 10, 1);
}

void fn_1_3EB0(omObjData *object, Vec arg1, f32 arg8, f32 arg9)
{
    M418DllUnkStruct3 *temp_r30;
    s32 sp10;
    f32 var_f31;
    f32 var_f30;
    f32 var_f27;
    f32 var_f26;
    f32 var_f24;
    f32 var_f20;

    sp10 = 0;
    temp_r30 = &lbl_1_bss_26C[object->work[0]];
    var_f31 = arg1.x - object->trans.x;
    var_f30 = object->trans.z - arg1.z;
    var_f26 = 90.0 + atan2d(var_f30, var_f31);
    var_f27 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    if (var_f27 <= 30.0f) {
        var_f31 = var_f30 = 0.0f;
    }
    else {
        var_f31 = 55.0f * (var_f31 / var_f27);
        var_f30 = 55.0f * (var_f30 / var_f27);
    }
    if (temp_r30->unk1C == 1) {
        temp_r30->unk20 = -1.47f;
    }
    var_f27 = arg9 * (sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) / 72.0f);
    if (var_f27 >= arg9) {
        var_f27 = arg9;
    }
    else if (var_f27 <= 1.0f) {
        var_f31 = var_f30 = var_f27 = 0.0f;
    }
    if (var_f31 != 0.0f || var_f30 != 0.0f || arg8 >= 0.0f) {
        if (arg8 >= 0.0f && var_f31 == 0.0f && var_f30 == 0.0f) {
            var_f26 = arg8;
        }
        if (var_f26 >= 180.0f) {
            if (object->rot.y - var_f26 >= 180.0f) {
                object->rot.y -= 360.0f;
            }
            if (object->rot.y - var_f26 < -180.0f) {
                object->rot.y += 360.0f;
            }
        }
        else {
            if (object->rot.y - var_f26 > 180.0f) {
                object->rot.y -= 360.0f;
            }
            if (object->rot.y - var_f26 <= -180.0f) {
                object->rot.y += 360.0f;
            }
        }
        object->rot.y = (((4.0f * object->rot.y) + var_f26) / 5.0f);
    }
    object->trans.x += var_f27 * sind(object->rot.y);
    object->trans.z += var_f27 * cosd(object->rot.y);
    if (temp_r30->unk1C) {
        temp_r30->unk1C = 2.0f;
        if (temp_r30->unk20 > 1.7f) {
            temp_r30->unk20 = 1.7f;
        }
        var_f20 = (temp_r30->unk20 * temp_r30->unk20) * (temp_r30->unk20 >= 0.0f ? -17.5f : 17.5f);
        object->trans.y += var_f20;
        if (object->trans.y <= 0.0f) {
            object->trans.y = 0.0f;
            temp_r30->unk1C = temp_r30->unk20 = 0.0f;
            omVibrate(temp_r30->unk4, 0xC, 6, 6);
        }
        temp_r30->unk20 += 0.11f;
    }
    if (temp_r30->unk1C != 0) {
        fn_1_AD14(object, 0, 3, 10, 0);
    }
    else if (var_f27 >= 6.75f) {
        fn_1_AD14(object, 0, 2, 10, 1);
    }
    else if (var_f27 > 0.0f) {
        fn_1_AD14(object, 0, 1, 10, 1);
    }
    else {
        fn_1_AD14(object, 0, 0, 10, 1);
    }
}

s32 lbl_1_data_1E0[4][2] = { { -1, 127 }, { -1, 127 }, { -1, 127 }, { -1, 127 } };

void fn_1_46C4(omObjData *object)
{
    s32 sp8;
    M418DllUnkStruct3 *temp_r31;

    sp8 = 0;
    temp_r31 = &lbl_1_bss_26C[object->work[0]];

    switch (temp_r31->unk24) {
        case 0:
            temp_r31->unk2C = object->scale.x;
            temp_r31->unk34 = temp_r31->unk38 = 0.0f;
            temp_r31->unk24 = 1;
            break;
        case 1:
            temp_r31->unk28 -= 1.0f;
            if (temp_r31->unk28 <= 0.0f) {
                temp_r31->unk28 = 15.0f;
                temp_r31->unk24 = 2;
                omVibrate(temp_r31->unk4, 0xC, 0xC, 0);
                lbl_1_data_1E0[object->work[0]][0] = HuAudCharVoicePlay(temp_r31->unk14, 0x123);
                lbl_1_data_1E0[object->work[0]][1] = 0x7F;
                HuAudFXPlay(0x5D4);
            }
            break;
        case 2:
            object->trans.x += 4.0f * temp_r31->unk30;
            object->trans.y += 125.0 * sind(temp_r31->unk28);
            object->trans.z -= 125.0 * cos(M_PI / 12.0);
            if (temp_r31->unk28 <= 14.0f) {
                Hu3DModelAttrReset(object->model[0], 1);
            }
            temp_r31->unk28 -= 0.25f;
            if (temp_r31->unk28 <= 0.0f) {
                temp_r31->unk24 = 3;
            }
            break;
        case 3:
            object->trans.y += 110.0 * sind(temp_r31->unk28);
            temp_r31->unk28 -= 0.0275f;
            temp_r31->unk2C -= 0.0025f;
            if (temp_r31->unk2C <= 0.3f) {
                temp_r31->unk2C = 0.0f;
                temp_r31->unk24 = 4;
                temp_r31->unk28 = 0.0f;
                HuAudFXPlay(0x5D5);
            }
            omSetSca(object, temp_r31->unk2C, temp_r31->unk2C, temp_r31->unk2C);
            break;
        case 4:
            temp_r31->unk38 = fn_1_A920(temp_r31->unk38, 360.0f, 15.0f);
            temp_r31->unk34 = fn_1_A920(temp_r31->unk34, 4.0f, 15.0f);
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, temp_r31->unk38);
            Hu3DModelScaleSet(object->model[1], temp_r31->unk34, temp_r31->unk34, temp_r31->unk34);
            if (temp_r31->unk28++ >= 30.0f) {
                temp_r31->unk24 = 5;
                temp_r31->unk28 = 0.0f;
            }
            break;
        case 5:
            temp_r31->unk38 = fn_1_A920(temp_r31->unk38, 720.0f, 15.0f);
            temp_r31->unk34 = fn_1_A920(temp_r31->unk34, 0.0f, 15.0f);
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, temp_r31->unk38);
            Hu3DModelScaleSet(object->model[1], temp_r31->unk34, temp_r31->unk34, temp_r31->unk34);
            if (temp_r31->unk28++ >= 60.0f) {
                temp_r31->unk24 = 6;
                temp_r31->unk28 = 0.0f;
            }
            break;
    }
    if ((temp_r31->unk24 >= 1) && (temp_r31->unk24 <= 5) && (lbl_1_data_1E0[object->work[0]][0] != -1)) {
        HuAudFXVolSet(lbl_1_data_1E0[object->work[0]][0], --lbl_1_data_1E0[object->work[0]][1]);
        if (lbl_1_data_1E0[object->work[0]][1] < 0) {
            lbl_1_data_1E0[object->work[0]][1] = 0;
        }
    }
}

void fn_1_4C84(omObjData *object)
{
    Mtx sp14;
    Vec sp8;
    f32 var_f31;
    M418DllUnkStruct3 *temp_r26;
    M418DllWorkStruct *var_r27;
    M418DllUnkStruct3 *temp_r30;
    ModelData *temp_r28;
    ModelData *temp_r29;
    s32 temp_r0;
    u32 temp_r3;

    temp_r30 = &lbl_1_bss_26C[object->work[0]];
    if (temp_r30->unk8 == 0) {
        var_f31 = (0.5f * temp_r30->unk3C) + ((CRot.x / 90.0f) * (0.5f * temp_r30->unk3C));
        temp_r29 = &Hu3DData[object->model[12]];
        if ((temp_r30->unk14 == 7) || (temp_r30->unk14 == 5)) {
            temp_r29->rot.y = -object->rot.y - 360.0f;
        }
        else {
            temp_r29->rot.y = -object->rot.y - 90.0f;
        }
        temp_r29->scale.x = 0.35f * temp_r30->unk3C;
        temp_r29->scale.y = var_f31;
        temp_r29->scale.z = 0.35f * temp_r30->unk3C;
        fn_1_3240(object);
    }
    fn_1_46C4(object);
}

void fn_1_4F60(omObjData *object)
{
    M418DllUnkStruct3 *temp_r30;

    temp_r30 = &lbl_1_bss_26C[object->work[0]];
    object->model[0] = CharModelCreate(temp_r30->unk14, 2);
    object->motion[0] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
    object->motion[1] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02));
    object->motion[2] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03));
    object->motion[3] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x73));
    object->motion[4] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x74));
    object->motion[5] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17));
    object->motion[6] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18));
    object->motion[7] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1B));
    object->motion[8] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2A));
    object->motion[9] = Hu3DJointMotion(object->model[0], HuDataSelHeapReadNum(temp_r30->unk14 + 0x310000, 0x10000000, HEAP_DATA));
    object->motion[10] = Hu3DJointMotion(object->model[0], HuDataSelHeapReadNum(temp_r30->unk14 + 0x310008, 0x10000000, HEAP_DATA));
    object->model[1] = Hu3DModelCreateFile(0x310017);
    Hu3DModelPosSet(object->model[1], 0.0f, -5000.0f, 0.0f);
    Hu3DModelShadowSet(object->model[0]);
    if (temp_r30->unk8 == 0) {
        Hu3DMotionOverlaySet(object->model[0], object->motion[9]);
        Hu3DMotionOverlaySpeedSet(object->model[0], 0.0f);
        object->model[11] = Hu3DModelCreateFile(0x31002F);
        Hu3DModelHookSet(object->model[0], CharModelHookNameGet(temp_r30->unk14, 2, 0), object->model[11]);
        if ((temp_r30->unk14 == 4) || (temp_r30->unk14 == 5)) {
            Hu3DModelScaleSet(object->model[11], 1.0f, 1.2f, 1.0f);
        }
        object->model[12] = Hu3DModelCreateFile(0x310027);
        object->motion[12] = Hu3DMotionIDGet(object->model[12]);
        Hu3DModelHookSet(object->model[11], "g031i00-itemhook_eff", object->model[12]);
        Hu3DModelScaleSet(object->model[12], 0.0f, 0.5f, 0.0f);
        fn_1_ABC4(object, 0xC, 0xC, 0, 1);
        object->model[13] = Hu3DModelCreateFile(0x310028);
        object->motion[13] = Hu3DMotionIDGet(object->model[13]);
        fn_1_ABC4(object, 0xD, 0xD, 0, 2);
    }
    lbl_1_data_1E0[object->work[0]][0] = -1;
    CharModelMotionDataClose(temp_r30->unk14);
    CharModelLayerSetAll2(7);
    object->func = fn_1_4C84;
}

void fn_1_5358(void)
{
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;
    Vec sp2C = { 0.0f, 1100.0f, 1800.0f };
    Vec sp20 = { 0.0f, 600.0f, 600.0f };

    fn_1_B104(var_r31, sp2C, sp20);
    fn_1_B41C(var_r31);
    var_r31->rot.x++;
}

void fn_1_543C(void)
{
    M418DllUnkStruct sp38;
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;
    Vec sp2C = { -180.0f, 500.0f, 440.0f };
    Vec sp20 = { -180.0f, 330.0f, -760.0f };

    fn_1_B104(&sp38, sp2C, sp20);
    fn_1_B41C(&sp38);
    sp38.center.x = 0.0f;
    sp38.center.y -= 75.0f;
    sp38.rot.x = -10.0f;
    sp38.rot.y = 10.0f;
    fn_1_DC10(var_r31, &sp38, var_r31->unk48++, 30.0f, 10.0f);
}

void fn_1_558C(void)
{
    M418DllUnkStruct sp38;
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;
    Vec sp2C = { 0.0f, 1100.0f, 1800.0f };
    Vec sp20 = { 0.0f, 600.0f, 600.0f };

    fn_1_B104(&sp38, sp2C, sp20);
    fn_1_B41C(&sp38);
    sp38.rot.x++;
    fn_1_CBF8(var_r31, &sp38, var_r31->unk48++, 30.0f, 10.0f);
}

void fn_1_56AC(s32 arg0)
{
    M418DllUnkStruct *var_r28 = &lbl_1_bss_1F4;
    fn_1_B458(var_r28);
    switch (arg0) {
        case 0:
            fn_1_248(fn_1_5358);
            break;
        case 1:
            fn_1_248(fn_1_543C);
            break;
        case 2:
            fn_1_248(fn_1_558C);
            break;
    }
}

void fn_1_5768(s32 arg0)
{
    s32 var_r31;
    M418DllUnkStruct4 *var_r30;
    M418DllUnkStruct *var_r26;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r30 = &lbl_1_bss_170[var_r31];
        var_r30->unkC = 0;
    }

    fn_1_56AC(0);
}

s32 fn_1_57E4(s32 arg0)
{
    M418DllUnkStruct4 *temp_r31;
    M418DllUnkStruct *var_r25;
    s32 var_r29;
    s32 var_r30;

    if (fn_1_B0C8(&lbl_1_bss_50, 0) >= 0x3C) {
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            temp_r31 = &lbl_1_bss_170[var_r30];
            if (temp_r31->unkC == 0) {
                if ((rand8() % 5) == 0) {
                    var_r29 = 1;
                }
                else {
                    var_r29 = 0;
                }
                if (var_r29 || (fn_1_B0C8(&lbl_1_bss_50, 0) >= 0x41)) {
                    HuAudFXPlay(0x5D3);
                    temp_r31->unkC = 1;
                }
            }
            else {
                temp_r31->unk4 += 5.0f;
                if (temp_r31->unk4 >= 90.0f) {
                    temp_r31->unk4 = 90.0f;
                }
            }
        }
    }
    if (fn_1_B0C8(&lbl_1_bss_50, 0) == 0x1E) {
        fn_1_56AC(1);
    }
    if (fn_1_B0C8(&lbl_1_bss_50, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_50);
    }
    else {
        return 0;
    }
}

s32 lbl_1_data_200[16] = { 0x310000, 0x310001, 0x310002, 0x310003, 0x310004, 0x310005, 0x310006, 0x310007, 0x310008, 0x310009, 0x31000A, 0x31000B,
    0x31000C, 0x31000D, 0x31000E, 0x31000F };

Vec lbl_1_data_240[3] = {
    { -540.0f, 225.0f, -900.0f },
    { -180.0f, 225.0f, -900.0f },
    { 180.0f, 225.0f, -900.0f },
};

void fn_1_5970(s32 arg0)
{
    M418DllUnkStruct3 *temp_r30;
    M418DllUnkStruct6 *temp_r29;
    M418DllUnkStruct4 *temp_r28;
    s32 var_r31;

    temp_r29 = &lbl_1_bss_3EC;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        temp_r30 = &lbl_1_bss_26C[temp_r29->unk4[var_r31]];
        omSetTra(temp_r30->unk0, lbl_1_data_240[var_r31].x, lbl_1_data_240[var_r31].y, lbl_1_data_240[var_r31].z - 50.0f);
        temp_r30->unk4C = 0;
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        temp_r28 = &lbl_1_bss_170[var_r31];
        temp_r28->unkC = 0;
    }
}

Vec lbl_1_data_264[4] = {
    { -355.0f, 0.0f, -680.0f },
    { 5.0f, 0.0f, -680.0f },
    { 365.0f, 0.0f, -680.0f },
};

s32 fn_1_5A6C(s32 arg0)
{
    s32 var_r31;
    M418DllUnkStruct3 *temp_r30;
    M418DllUnkStruct4 *temp_r29;
    M418DllUnkStruct3 *temp_r28;
    M418DllUnkStruct6 *temp_r27;
    s32 var_r26;
    omObjData *temp_r25;
    s32 var_r24;
    M418DllUnkStruct *temp_r20;

    temp_r27 = &lbl_1_bss_3EC;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        temp_r30 = &lbl_1_bss_26C[temp_r27->unk4[var_r31]];
        if (temp_r30->unk4C == 0) {
            if ((rand8() % 5) == 0) {
                var_r26 = 1;
            }
            else {
                var_r26 = 0;
            }
            if (var_r26 || (fn_1_B0C8(&lbl_1_bss_50, 0) >= 5)) {
                temp_r30->unk4C = 1;
                temp_r25 = temp_r30->unk0;
                temp_r28 = &lbl_1_bss_26C[temp_r25->work[0]];
                if (temp_r28->unk1C == 0) {
                    temp_r28->unk1C = 1;
                }
                HuAudCharVoicePlay(temp_r30->unk14, 0x122);
            }
        }
        else {
            fn_1_3EB0(temp_r30->unk0, lbl_1_data_264[var_r31], 0.0f, 9.0f);
        }
    }
    if (fn_1_B0C8(&lbl_1_bss_50, 0) >= 0x3C) {

        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            temp_r29 = &lbl_1_bss_170[var_r31];
            if (temp_r29->unkC == 0) {
                if ((rand8() % 5) == 0) {
                    var_r24 = 1;
                }
                else {
                    var_r24 = 0;
                }
                if ((var_r24 != 0) || (fn_1_B0C8(&lbl_1_bss_50, 0) >= 0x41)) {
                    HuAudFXPlay(0x5D3);
                    temp_r29->unkC = 1;
                }
            }
            else {
                temp_r29->unk4 -= 2.5f;
                if (temp_r29->unk4 <= 0.0f) {
                    temp_r29->unk4 = 0.0f;
                }
            }
        }
    }
    if (fn_1_B0C8(&lbl_1_bss_50, 0) == 0x3C) {
        fn_1_56AC(2);
    }
    if (fn_1_B0C8(&lbl_1_bss_50, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_50);
    }
    return 0;
}

M418DllUnkStruct8 lbl_1_data_294[3] = { { fn_1_5768, fn_1_57E4, 0x5A }, { fn_1_5970, fn_1_5A6C, 0xB4 }, { NULL, NULL, -1 } };

void fn_1_5D28(void)
{
    fn_1_AEDC(&lbl_1_bss_50, &lbl_1_data_294[0]);
}

s32 fn_1_5D58(void)
{
    s32 var_r31;

    var_r31 = 0;
    if (lbl_1_bss_50.unk10 != NULL) {
        lbl_1_bss_50.unk10();
        lbl_1_bss_50.unk10 = NULL;
    }
    if (lbl_1_bss_50.unk14 != NULL) {
        var_r31 = lbl_1_bss_50.unk14();
    }
    return var_r31;
}

s32 fn_1_5DF0(omObjData *object, s32 arg1)
{
    M418DllUnkStruct3 *temp_r31;
    s32 var_r30;

    temp_r31 = &lbl_1_bss_26C[object->work[0]];
    var_r30 = temp_r31->unk4C;
    if (temp_r31->unkC != 0) {
        switch (temp_r31->unk10) {
            case 0:
                if ((arg1 % 100) == 0) {
                    var_r30 = rand8() % 4;
                }
                break;
            case 1:
                if ((arg1 % 50) == 0) {
                    var_r30 = rand8() % 4;
                }
                break;
            case 2:
                if ((arg1 % 25) == 0) {
                    var_r30 = rand8() % 4;
                }
                break;
            case 3:
                if ((arg1 % 25) == 0) {
                    var_r30 = rand8() % 4;
                }
                break;
        }
    }
    else {
        if ((HuPadBtnDown[temp_r31->unk18] & PAD_BUTTON_A) != 0) {
            var_r30 = 1;
        }
        if ((HuPadBtnDown[temp_r31->unk18] & PAD_BUTTON_B) != 0) {
            var_r30 = 0;
        }
        if ((HuPadBtnDown[temp_r31->unk18] & PAD_BUTTON_X) != 0) {
            var_r30 = 3;
        }
        if ((HuPadBtnDown[temp_r31->unk18] & PAD_BUTTON_Y) != 0) {
            var_r30 = 2;
        }
    }
    return var_r30;
}

s32 fn_1_6038(omObjData *object, s32 arg1)
{
    M418DllUnkStruct3 *temp_r30;
    M418DllUnkStruct4 *temp_r28;
    M418DllUnkStruct4 *temp_r27;
    M418DllUnkStruct4 *temp_r26;
    s32 var_r29;
    s32 var_r31;

    temp_r30 = &lbl_1_bss_26C[object->work[0]];
    var_r31 = temp_r30->unk4C;
    if (temp_r30->unkC != 0) {
        switch (temp_r30->unk10) {
            case 0:
                if ((arg1 % 200) == 1) {
                    var_r31 = rand8() % 4;
                }
                break;
            case 1:
                if ((arg1 % 150) == 1) {
                    var_r31 = rand8() % 4;
                }
                break;
            case 2:
                if ((arg1 % 100) == 1) {
                    var_r31 = rand8() % 4;
                }
                break;
            case 3:
                if ((arg1 % 100) == 1) {
                    var_r31 = rand8() % 4;
                }
                break;
        }
        if (var_r31 != -1) {
            temp_r28 = &lbl_1_bss_170[var_r31];
            if (temp_r28->unk18s == 1) {
                for (var_r29 = 0; var_r29 < 4; var_r29++) {
                    temp_r27 = &lbl_1_bss_170[var_r29];
                    if (temp_r27->unk18s != 1) {
                        var_r31 = var_r29;
                        temp_r27->unk18s = 1;
                        break;
                    }
                }
            }
            else {
                temp_r28->unk18s = 1;
            }
        }
    }
    else {
        if ((HuPadBtnDown[temp_r30->unk18] & PAD_BUTTON_A) != 0) {
            var_r31 = 1;
        }
        if ((HuPadBtnDown[temp_r30->unk18] & PAD_BUTTON_B) != 0) {
            var_r31 = 0;
        }
        if ((HuPadBtnDown[temp_r30->unk18] & PAD_BUTTON_X) != 0) {
            var_r31 = 3;
        }
        if ((HuPadBtnDown[temp_r30->unk18] & PAD_BUTTON_Y) != 0) {
            var_r31 = 2;
        }
        if (var_r31 != -1) {
            temp_r26 = &lbl_1_bss_170[var_r31];
            if (temp_r26->unk18s == 1) {
                var_r31 = -1;
            }
            else {
                temp_r26->unk18s = 1;
            }
        }
    }
    return var_r31;
}

void fn_1_6314(void)
{
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;
    Vec sp2C = { 0.0f, 1100.0f, 1800.0f };
    Vec sp20 = { 0.0f, 600.0f, 600.0f };

    fn_1_B104(var_r31, sp2C, sp20);
    fn_1_B41C(var_r31);
    var_r31->rot.x++;
}

void fn_1_63F8(void)
{
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;
    M418DllUnkStruct sp38;
    Vec sp2C = { 0.0f, 1800.0f, 480.0f };
    Vec sp20 = { 0.0f, 600.0f, 250.0f };

    fn_1_B104(&sp38, sp2C, sp20);
    fn_1_B41C(&sp38);
    sp38.zoom = 750.0f;
    fn_1_BEAC(var_r31, &sp38, var_r31->unk48++, 120.0f, 10.0f);
}

void fn_1_6510(void)
{
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;
    M418DllUnkStruct sp38;
    Vec sp2C = { 0.0f, 980.0f, 1330.0f };
    Vec sp20 = { 0.0f, 480.0f, 130.0f };

    fn_1_B104(&sp38, sp2C, sp20);
    fn_1_B41C(&sp38);
    fn_1_BEAC(var_r31, &sp38, var_r31->unk48++, 30.0f, 10.0f);
}

Vec lbl_1_data_2B8[8] = { { -540.0f, 225.0f, -900.0f }, { -180.0f, 225.0f, -900.0f }, { 180.0f, 225.0f, -900.0f }, { 540.0f, 225.0f, -900.0f },
    { -360.0f, 0.0f, -680.0f }, { 0.0f, 0.0f, -680.0f }, { 360.0f, 0.0f, -680.0f }, { 0.0f, 0.0f, 0.0f } };

void fn_1_6618(void)
{
    M418DllUnkStruct sp8;
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct *var_r30;
    M418DllUnkStruct6 *var_r29;

    var_r29 = &lbl_1_bss_3EC;
    temp_r31 = &lbl_1_bss_26C[var_r29->unk0];
    var_r30 = &lbl_1_bss_1F4;
    sp8.center.x = lbl_1_data_2B8[temp_r31->unk4C].x;
    sp8.center.y = lbl_1_data_2B8[temp_r31->unk4C].y;
    sp8.center.z = lbl_1_data_2B8[temp_r31->unk4C].z;
    sp8.rot.x = 0.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 725.0f;
    fn_1_CBF8(var_r30, &sp8, var_r30->unk48++, 30.0f, 5.0f);
}

void fn_1_6740(s32 arg0)
{
    M418DllUnkStruct *var_r27 = &lbl_1_bss_1F4;

    fn_1_B458(var_r27);
    switch (arg0) {
        case 0:
            fn_1_248(fn_1_6314);
            break;
        case 1:
            fn_1_248(fn_1_63F8);
            break;
        case 2:
            fn_1_248(fn_1_6510);
            break;
        case 3:
            fn_1_248(fn_1_6618);
            break;
    }
}

void fn_1_6808(s32 arg0)
{
    s32 var_r31;
    M418DllUnkStruct6 *var_r30 = &lbl_1_bss_3EC;
    M418DllUnkStruct3 *var_r29;
    M418DllUnkStruct4 *var_r28;
    M418DllUnkStruct *var_r23;

    HuAudAUXVolSet(0x40, 0x40);

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r29 = &lbl_1_bss_26C[var_r30->unk4[var_r31]];
        var_r29->unk4C = -1;
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r28 = &lbl_1_bss_11C[var_r31];
        fn_1_ABC4(var_r28->unk0, 0, 3, 30, 1);
    }
    if (lbl_1_bss_8 == 0) {
        lbl_1_bss_8 = 1;
        lbl_1_bss_4 = REFRESH_RATE * 5;
    }

    fn_1_6740(0);
}

Vec lbl_1_data_318[4] = { { -540.0f, 115.0f, -700.0f }, { -180.0f, 115.0f, -700.0f }, { 180.0f, 115.0f, -700.0f }, { 540.0f, 115.0f, -700.0f } };

s32 fn_1_6914(s32 arg0)
{
    Vec sp14;
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct3 *temp_r30;
    s32 var_r29;
    s32 temp_r27;
    M418DllUnkStruct6 *var_r26;
    M418DllUnkStruct4 *var_r25;
    M418DllUnkStruct *var_r18;

    var_r26 = &lbl_1_bss_3EC;

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        temp_r31 = &lbl_1_bss_26C[var_r26->unk4[var_r29]];
        temp_r27 = fn_1_B0C8(&lbl_1_bss_38, 0);
        temp_r31->unk4C = fn_1_5DF0(temp_r31->unk0, temp_r27);
        if (temp_r31->unk4C != -1) {
            sp14.x = lbl_1_data_318[temp_r31->unk4C].x;
            sp14.y = lbl_1_data_318[temp_r31->unk4C].y;
            sp14.z = (75.0f * var_r29) + lbl_1_data_318[temp_r31->unk4C].z;
            fn_1_3444(temp_r31->unk0, sp14, -1.0f, 9.0f);
            if (temp_r31->unk0->trans.z <= -720.0f) {
                temp_r31->unk0->trans.z = -720.0f;
            }
            if (temp_r31->unk0->trans.z >= -480.0f) {
                temp_r31->unk0->trans.z = -480.0f;
            }
            if (fn_1_B0C8(&lbl_1_bss_38, 0) >= REFRESH_RATE * 4) {
                temp_r31->unk0->trans.x = temp_r31->unk0->trans.y = -5000.0f;
                fn_1_ABC4(temp_r31->unk0, 0, 0, 0xA, 1);
            }
        }
    }

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        var_r25 = &lbl_1_bss_11C[var_r29];
#if VERSION_PAL
        var_r25->unk0->rot.y += 1.44f;
#else
        var_r25->unk0->rot.y += 1.2f;
#endif
    }
    if (fn_1_B0C8(&lbl_1_bss_38, 0) == REFRESH_RATE) {
        fn_1_6740(1);
    }
    if (fn_1_B0C8(&lbl_1_bss_38, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_38);
    }
    return 0;
}

void fn_1_6DCC(s32 arg0)
{
    s32 var_r31;
    M418DllUnkStruct4 *temp_r30;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        temp_r30 = &lbl_1_bss_11C[var_r31];
        temp_r30->unk0->rot.y = 0.0f;
        fn_1_ABC4(temp_r30->unk0, 0, 0, 0x1E, 1);
    }
    fn_1_6740(2);
}

s32 fn_1_6E6C(s32 arg0)
{
    if (fn_1_B0C8(&lbl_1_bss_38, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_38);
    }
    return 0;
}

void fn_1_6EB4(s32 arg0)
{
    M418DllUnkStruct6 *var_r31 = &lbl_1_bss_3EC;
    s32 var_r30;
    M418DllUnkStruct3 *temp_r29;

    var_r31->unk34 = 0;

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r29 = &lbl_1_bss_26C[var_r31->unk4[var_r30]];
        if (temp_r29->unk4C == -1) {
            var_r31->unk34++;
            temp_r29->unk50 = 0;
        }
    }
}

s32 fn_1_6F38(s32 arg0)
{
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct2 *temp_r29;
    M418DllUnkStruct6 *temp_r28;
    M418DllUnkStruct2 *temp_r27;

    s32 var_r26;
    s32 var_r30;
    f32 var_f31;

    temp_r29 = &lbl_1_bss_1E0;
    temp_r28 = &lbl_1_bss_3EC;

    if (temp_r28->unk34 == 0) {
        return fn_1_B034(&lbl_1_bss_38, 9);
    }

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r31 = &lbl_1_bss_26C[temp_r28->unk4[var_r30]];
        if (temp_r31->unk4C == -1) {
            if (temp_r29->unk4[var_r30] == 0) {
                if ((rand8() % 10) == 0) {
                    var_r26 = 1;
                }
                else {
                    var_r26 = 0;
                }
                if ((var_r26 != 0) || (fn_1_B0C8(&lbl_1_bss_38, 0) >= 10)) {
                    HuAudFXPlay(0x5DC);
                    HuAudCharVoicePlay(temp_r31->unk14, 0x128);
                    temp_r29->unk4[var_r30] = 2;
                    Hu3DModelShadowDispOff(temp_r31->unk0->model[0]);
                    fn_1_ABC4(temp_r31->unk0, 0, 7, 0x1E, 0);
                    temp_r31->unk50 = fn_1_B0C8(&lbl_1_bss_38, 0);
                    omVibrate(temp_r31->unk4, 0xC, 6, 6);
                }
            }
            else if (fn_1_B0C8(&lbl_1_bss_38, 0) >= (temp_r31->unk50 + 0x1E)) {
                temp_r31->unk0->trans.y -= 15.0f;
            }
            if (fn_1_B0C8(&lbl_1_bss_38, 0) >= (temp_r31->unk50 + 0x3C)) {
                var_f31 = fn_1_AA30(-200.0f, -110.0f, fn_1_B0C8(&lbl_1_bss_38, 0) - (temp_r31->unk50 + 0x3C), 90.0f);
                Hu3DModelPosSet(temp_r29->unk0->model[var_r30 + 8], -350.0f + (360.0f * var_r30), var_f31, -660.0f);
                Hu3DModelRotSet(temp_r29->unk0->model[var_r30 + 8], 0.0f, 0.0f, 20.0f);
            }
        }
    }
    if (fn_1_B0C8(&lbl_1_bss_38, 1) != 0) {
        temp_r27 = &lbl_1_bss_1E0;
        temp_r27->unk4[0] = temp_r27->unk4[1] = temp_r27->unk4[2] = 3;
        if (temp_r28->unk34 >= 3) {
            return 1;
        }
        return fn_1_B034(&lbl_1_bss_38, 9);
    }
    else {
        return 0;
    }
}

void fn_1_7294(s32 arg0) { }

s32 fn_1_7298(s32 arg0)
{
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct4 *temp_r30;
    M418DllUnkStruct6 *temp_r29;

    temp_r29 = &lbl_1_bss_3EC;
    temp_r31 = &lbl_1_bss_26C[temp_r29->unk0];
    temp_r30 = &lbl_1_bss_11C[temp_r29->unk38];
    if (fn_1_B0C8(&lbl_1_bss_38, 0) < 0x3C) {
        if (((temp_r30->unk0->work[0] == 0) || (temp_r30->unk0->work[1] == 0x18)) && (temp_r30->unk0->rot.y > -50.0f)) {
            temp_r30->unk0->rot.y -= 5.0f;
            if (temp_r30->unk0->rot.y <= -50.0f) {
                temp_r30->unk0->rot.y = -50.0f;
            }
        }
        if (temp_r31->unk0->rot.y < 180.0f) {
            temp_r31->unk0->rot.y += 5.0f;
            if (temp_r30->unk0->rot.y <= -50.0f) {
                temp_r30->unk0->rot.y = -50.0f;
            }
        }
    }
    else if (fn_1_B0C8(&lbl_1_bss_38, 0) == 0x3C) {
        HuAudFXPlay(0x40);
        fn_1_ABC4(temp_r30->unk0, 0, 2, 0xA, 0);
        fn_1_AD14(temp_r31->unk0, 0, 0, 0xA, 1);
        Hu3DMotionOverlaySet(temp_r31->unk0->model[0], temp_r31->unk0->motion[9]);
        Hu3DMotionOverlaySpeedSet(temp_r31->unk0->model[0], 1.0f);
        lbl_1_bss_240[8] = HuAudFXPlay(0x5D9);
    }
    else if (fn_1_B0C8(&lbl_1_bss_38, 0) <= 0xAA) {
        if (fn_1_B0C8(&lbl_1_bss_38, 0) >= 0x5A) {
            temp_r31->unk3C += 0.025f;
            if (temp_r31->unk3C >= 1.0f) {
                temp_r31->unk3C = 1.0f;
            }
        }
    }
    else {
        Hu3DMotionOverlaySpeedSet(temp_r31->unk0->model[0], -1.0f);
    }
    if (fn_1_B0C8(&lbl_1_bss_38, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_38);
    }
    else {
        return 0;
    }
}

void fn_1_7570(s32 arg0)
{
    M418DllUnkStruct6 *var_r31 = &lbl_1_bss_3EC;
    M418DllUnkStruct3 *var_r30 = &lbl_1_bss_26C[var_r31->unk0];
    var_r30->unk4C = -1;
    if (lbl_1_bss_8 == 0) {
        lbl_1_bss_8 = 1;
        lbl_1_bss_4 = REFRESH_RATE * 5;
    }
}

s32 fn_1_75E4(s32 arg0)
{
    Mtx sp38;
    Mtx sp8;
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct6 *var_r30;
    s32 var_r29;

    var_r30 = &lbl_1_bss_3EC;
    temp_r31 = &lbl_1_bss_26C[var_r30->unk0];
    if (fn_1_B0C8(&lbl_1_bss_38, 0) >= 10) {
        temp_r31->unk4C = fn_1_6038(temp_r31->unk0, fn_1_B0C8(&lbl_1_bss_38, 0));
        if (temp_r31->unk4C != -1) {
            if (lbl_1_bss_8 == 2) {
                lbl_1_bss_8 = 3;
                lbl_1_bss_4 = 0x1E;
            }
            return fn_1_AF38(&lbl_1_bss_38);
        }
    }
    fn_1_B0C8(&lbl_1_bss_38, 1);
    var_r29 = 0;
    if (lbl_1_bss_8 == 3) {
        var_r29 = 1;
    }
    if (var_r29 != 0) {
        Hu3DModelObjMtxGet(temp_r31->unk0->model[0], lbl_1_data_1C0[temp_r31->unk14], sp8);
        Hu3DModelObjMtxGet(temp_r31->unk0->model[12], "g031i00-itemhook_eff", sp38);
        Hu3DModelPosSet(temp_r31->unk0->model[13], sp38[0][3] + sp8[0][3], 80.0f + (sp38[1][3] + sp8[1][3]), sp38[2][3] + sp8[2][3]);
        Hu3DModelScaleSet(temp_r31->unk0->model[13], 0.5f, 0.5f, 0.5f);
        Hu3DMotionSpeedSet(temp_r31->unk0->model[13], 2.0f);
        fn_1_ABC4(temp_r31->unk0, 0xD, 0xD, 0, 0);
        return fn_1_AF38(&lbl_1_bss_38);
    }
    else {
        return 0;
    }
}

void fn_1_77F8(s32 arg0)
{
    M418DllUnkStruct6 *var_r31;
    M418DllUnkStruct3 *var_r30;

    var_r31 = &lbl_1_bss_3EC;
    var_r30 = &lbl_1_bss_26C[var_r31->unk0];
    if (var_r30->unk4C == -1) {
        HuAudFXFadeOut(lbl_1_bss_240[8], 0x3E8);
    }
}

s32 fn_1_7860(s32 arg0)
{
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct6 *temp_r30;

    temp_r30 = &lbl_1_bss_3EC;
    temp_r31 = &lbl_1_bss_26C[temp_r30->unk0];
    if (temp_r31->unk4C == -1) {
        temp_r31->unk3C -= 0.025f;
        if (temp_r31->unk3C <= 0.0f) {
            temp_r31->unk3C = 0.0f;
        }
        if (fn_1_B0C8(&lbl_1_bss_38, 1) != 0) {
            return fn_1_AF38(&lbl_1_bss_38);
        }
    }
    else {
        temp_r31->unk0->rot.y = fn_1_A940(180.0f, 200.0f - (10.0f * temp_r31->unk4C), fn_1_B0C8(&lbl_1_bss_38, 0), 10.0f);
        if (fn_1_B0C8(&lbl_1_bss_38, 0) == 0xA) {
            Hu3DMotionOverlaySet(temp_r31->unk0->model[0], temp_r31->unk0->motion[10]);
            Hu3DMotionOverlaySpeedSet(temp_r31->unk0->model[0], 1.0f);
            temp_r31->unk5C = 1;
        }
        if (fn_1_B0C8(&lbl_1_bss_38, 1) != 0) {
            Hu3DMotionOverlaySpeedSet(temp_r31->unk0->model[0], -1.0f);
            temp_r31->unk5C = 2;
            return fn_1_AF38(&lbl_1_bss_38);
        }
    }
    return 0;
}

void fn_1_7A68(s32 arg0)
{
    M418DllUnkStruct6 *temp_r31;
    M418DllUnkStruct3 *temp_r30;
    M418DllUnkStruct4 *temp_r29;
    s32 var_r28;
    M418DllUnkStruct3 *temp_r27;
    s32 var_r26;

    var_r26 = 0;
    temp_r31 = &lbl_1_bss_3EC;
    temp_r30 = &lbl_1_bss_26C[temp_r31->unk0];
    if (temp_r30->unk4C != -1) {
        temp_r31->unk10[0] = temp_r31->unk10[1] = temp_r31->unk10[2] = -1;

        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            temp_r27 = &lbl_1_bss_26C[temp_r31->unk4[var_r28]];
            if (temp_r30->unk4C == temp_r27->unk4C) {
                temp_r31->unk10[var_r26++] = temp_r27->unk0->work[0];
            }
        }
        temp_r29 = &lbl_1_bss_170[temp_r30->unk4C];
        temp_r29->unkC = 0;
        if (temp_r31->unk10[0] == -1) {
            temp_r29->unk10 = 1;
        }
        temp_r29->unk0->work[1] = 1;
    }
}

s32 fn_1_7B68(s32 arg0)
{
    Mtx sp8;
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct6 *temp_r30;
    M418DllUnkStruct3 *temp_r29;
    M418DllUnkStruct4 *temp_r28;
    s32 var_r27;
    s32 var_r26;
    M418DllUnkStruct *temp_r21;

    var_r26 = -1;
    temp_r30 = &lbl_1_bss_3EC;
    temp_r29 = &lbl_1_bss_26C[temp_r30->unk0];
    temp_r28 = &lbl_1_bss_170[temp_r29->unk4C];
    if (temp_r29->unk4C == -1) {
        return fn_1_AF38(&lbl_1_bss_38);
    }
    if (temp_r28->unkC == 1) {
        fn_1_6740(3);
    }
    if (temp_r28->unkC == 3) {

        for (var_r27 = 0; var_r27 < 3; var_r27++) {
            if (temp_r30->unk10[var_r27] != -1) {
                temp_r31 = &lbl_1_bss_26C[temp_r30->unk10[var_r27]];
                Hu3DModelObjMtxGet(*temp_r28->unk0->model, "taihou-null4", (f32(*)[4]) & sp8[0]);
                omSetTra(temp_r31->unk0, sp8[0][3], sp8[1][3] - 25.0f, 50.0f + sp8[2][3]);
                omSetRot(temp_r31->unk0, 0.0f, 180.0f, 0.0f);
                fn_1_AD14(temp_r31->unk0, 0, 8, 0, 2);
                temp_r31->unk4C = -1;
                temp_r31->unk24 = 0;
                if (var_r26 >= 2) {
                    var_r26 = 1;
                }
                temp_r31->unk30 = var_r26++;
                temp_r31->unk28 = 0.0f;
                omVibrate((s16)temp_r29->unk4, 0xC, 4, 2);
            }
        }
        return fn_1_AF38(&lbl_1_bss_38);
    }
    return 0;
}

void fn_1_7D80(s32 arg0)
{
    s32 var_r31;
    M418DllUnkStruct3 *temp_r30;
    M418DllUnkStruct6 *temp_r29;
    M418DllUnkStruct4 *temp_r28;

    temp_r29 = &lbl_1_bss_3EC;
    temp_r30 = &lbl_1_bss_26C[temp_r29->unk0];
    temp_r30->unk0->rot.y = 180.0f;
    temp_r30->unk3C = 0.0f;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        temp_r28 = &lbl_1_bss_11C[var_r31];
        temp_r28->unk0->rot.y = 0.0f;
    }
}

s32 fn_1_7E24(s32 arg0)
{
    M418DllUnkStruct6 *var_r31;
    s32 var_r30;
    s32 var_r29;
    M418DllUnkStruct4 *var_r28;
    M418DllUnkStruct4 *var_r27;
    M418DllUnkStruct4 *var_r26;
    M418DllUnkStruct3 *var_r25;

    var_r29 = 0;
    var_r31 = &lbl_1_bss_3EC;
    var_r28 = &lbl_1_bss_11C[0];
    var_r27 = &lbl_1_bss_11C[1];
    var_r26 = &lbl_1_bss_11C[2];
    if (var_r31->unk38 == 2) {
        var_r28->unk0->work[1] = 0;
        var_r27->unk0->work[1] = 0;
        var_r26->unk0->work[1] = 3;
        return 1;
    }
    var_r31->unk38++;

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        var_r25 = &lbl_1_bss_26C[var_r31->unk4[var_r30]];
        if (var_r25->unk4C != -1) {
            var_r29++;
        }
    }
    if (var_r29 == 0) {
        return 1;
    }
    else {
        return fn_1_AF38(&lbl_1_bss_38);
    }
}

void fn_1_7F1C(s32 arg0)
{
    M418DllUnkStruct6 *var_r31;
    M418DllUnkStruct4 *var_r30;
    M418DllUnkStruct4 *var_r29;
    M418DllUnkStruct4 *var_r28;

    var_r31 = &lbl_1_bss_3EC;
    var_r30 = &lbl_1_bss_11C[0];
    var_r29 = &lbl_1_bss_11C[1];
    var_r28 = &lbl_1_bss_11C[2];
    if (var_r31->unk38 == 1) {
        var_r30->unk0->work[1] = 3;
        var_r29->unk0->work[1] = 2;
        var_r28->unk0->work[1] = 1;
    }
    else if (var_r31->unk38 == 2) {
        var_r30->unk0->work[1] = 0;
        var_r29->unk0->work[1] = 3;
        var_r28->unk0->work[1] = 2;
    }
}

s32 fn_1_7FD4(s32 arg0)
{
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct6 *temp_r30;
    M418DllUnkStruct4 *temp_r29;

    temp_r30 = &lbl_1_bss_3EC;
    temp_r31 = &lbl_1_bss_26C[temp_r30->unk0];
    if (temp_r31->unk4C == -1) {
        if (fn_1_B0C8(&lbl_1_bss_38, 0) == 30) {
            fn_1_6740(2);
        }
        if (fn_1_B0C8(&lbl_1_bss_38, 0) == 120) {
            return fn_1_B034(&lbl_1_bss_38, 9);
        }
    }
    else {
        temp_r29 = &lbl_1_bss_170[temp_r31->unk4C];
        if (temp_r29->unk10 != 0) {
            if (fn_1_B0C8(&lbl_1_bss_38, 0) == 210) {
                fn_1_6740(2);
            }
            if (fn_1_B0C8(&lbl_1_bss_38, 0) == 300) {
                return fn_1_B034(&lbl_1_bss_38, 9);
            }
        }
        else {
            if (fn_1_B0C8(&lbl_1_bss_38, 0) == 30) {
                fn_1_6740(2);
            }
            if (fn_1_B0C8(&lbl_1_bss_38, 0) == 120) {
                return fn_1_B034(&lbl_1_bss_38, 3);
            }
        }
    }
    fn_1_B0C8(&lbl_1_bss_38, 1);
    return 0;
}

void fn_1_81A0(s32 arg0) { }

s32 fn_1_81A4(s32 arg0)
{
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct4 *temp_r30;
    M418DllUnkStruct6 *temp_r29;

    temp_r29 = &lbl_1_bss_3EC;
    temp_r31 = &lbl_1_bss_26C[temp_r29->unk0];
    temp_r30 = &lbl_1_bss_11C[temp_r29->unk38];
    if (fn_1_B0C8(&lbl_1_bss_38, 0) < 0x3C) {
        if (((temp_r30->unk0->work[0] == 0) || (temp_r30->unk0->work[1] == 0x18)) && (temp_r30->unk0->rot.y > -50.0f)) {
            temp_r30->unk0->rot.y -= 5.0f;
            if (temp_r30->unk0->rot.y <= -50.0f) {
                temp_r30->unk0->rot.y = -50.0f;
            }
        }
        if (temp_r31->unk0->rot.y < 180.0f) {
            temp_r31->unk0->rot.y += 5.0f;
            if (temp_r30->unk0->rot.y <= -50.0f) {
                temp_r30->unk0->rot.y = -50.0f;
            }
        }
    }
    else if (fn_1_B0C8(&lbl_1_bss_38, 0) == 0x3C) {
        HuAudFXPlay(0x40);
        fn_1_ABC4(temp_r30->unk0, 0, 2, 0xA, 0);
        fn_1_AD14(temp_r31->unk0, 0, 0, 0xA, 1);
        Hu3DMotionOverlaySet(temp_r31->unk0->model[0], temp_r31->unk0->motion[9]);
        Hu3DMotionOverlaySpeedSet(temp_r31->unk0->model[0], 1.0f);
        lbl_1_bss_240[8] = HuAudFXPlay(0x5D9);
    }
    else if (fn_1_B0C8(&lbl_1_bss_38, 0) <= 0xAA) {
        if (fn_1_B0C8(&lbl_1_bss_38, 0) >= 0x5A) {
            temp_r31->unk3C += 0.025f;
            if (temp_r31->unk3C >= 1.0f) {
                temp_r31->unk3C = 1.0f;
            }
        }
    }
    else {
        Hu3DMotionOverlaySpeedSet(temp_r31->unk0->model[0], -1.0f);
    }
    if (fn_1_B0C8(&lbl_1_bss_38, 1) != 0) {
        return fn_1_B034(&lbl_1_bss_38, 4);
    }
    else {
        return 0;
    }
}

M418DllUnkStruct8 lbl_1_data_348[11] = { { fn_1_6808, fn_1_6914, VERSION_PAL ? 250 : 300 }, { fn_1_6DCC, fn_1_6E6C, 60 }, { fn_1_6EB4, fn_1_6F38, 180 },
    { fn_1_7294, fn_1_7298, 300 }, { fn_1_7570, fn_1_75E4, VERSION_PAL ? 250 : 300 }, { fn_1_77F8, fn_1_7860, 60 }, { fn_1_7A68, fn_1_7B68, 180 },
    { fn_1_7D80, fn_1_7E24, -1 }, { fn_1_7F1C, fn_1_7FD4, 300 }, { fn_1_81A0, fn_1_81A4, 240 }, { NULL, NULL, -1 } };

void fn_1_8480(void)
{
    fn_1_AEDC(&lbl_1_bss_38, &lbl_1_data_348[0]);
}

s32 fn_1_84B0(void)
{
    s32 var_r31;

    var_r31 = 0;
    if (lbl_1_bss_38.unk10 != NULL) {
        lbl_1_bss_38.unk10();
        lbl_1_bss_38.unk10 = NULL;
    }
    if (lbl_1_bss_38.unk14 != NULL) {
        var_r31 = lbl_1_bss_38.unk14();
    }
    return var_r31;
}

void fn_1_8548(void)
{
    M418DllUnkStruct sp38;
    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;
    Vec sp2C = { 0.0f, 1100.0f, 1800.0f };
    Vec sp20 = { 0.0f, 600.0f, 600.0f };

    fn_1_B104(&sp38, sp2C, sp20);
    fn_1_B41C(&sp38);
    sp38.rot.x++;
    fn_1_CBF8(var_r31, &sp38, var_r31->unk48++, 60.0f, 10.0f);
}

void fn_1_8668(void)
{
    M418DllUnkStruct sp8;
    f32 temp_f1;

    M418DllUnkStruct *var_r31 = &lbl_1_bss_1F4;

    sp8.center.x = sp8.center.y = 0.0f;
    sp8.center.z = -500.0f;
    sp8.rot.x = -20.0f;
    sp8.rot.y = sp8.rot.z = 0.0f;
    sp8.zoom = 1000.0f;
    fn_1_CBF8(var_r31, &sp8, var_r31->unk48++, 10.0f, 5.0f);
}

void fn_1_8728(void)
{
    M418DllUnkStruct sp8;
    M418DllUnkStruct *var_r31;

    var_r31 = &lbl_1_bss_1F4;

    sp8.center.x = var_r31->center.x;
    sp8.center.y = var_r31->center.y;
    sp8.center.z = var_r31->center.z;
    sp8.rot.x = var_r31->rot.x;
    sp8.rot.y = var_r31->rot.y;
    sp8.rot.z = var_r31->rot.z;
    sp8.zoom = 500.0f;
    fn_1_CBF8(var_r31, &sp8, var_r31->unk48++, 10.0f, 5.0f);
}

void fn_1_87D0(s32 arg0)
{
    M418DllUnkStruct *var_r31;

    var_r31 = &lbl_1_bss_1F4;

    fn_1_B458(var_r31);
    switch (arg0) {
        case 0:
            fn_1_248(fn_1_8548);
            break;
        case 1:
            fn_1_248(fn_1_8668);
            break;
        case 2:
            fn_1_248(fn_1_8728);
            break;
    }
}

void fn_1_888C(s32 arg0)
{
    HuAudAUXVolSet(-1, -1);
}

s32 fn_1_88B4(s32 arg0)
{
    s32 var_r31;
    M418DllUnkStruct6 *var_r30;
    s32 var_r29;
    M418DllUnkStruct3 *var_r28;
    M418DllUnkStruct3 *var_r27;
    M418DllUnkStruct *var_r23;

    var_r29 = 5;
    var_r30 = &lbl_1_bss_3EC;

    fn_1_87D0(0);
    lbl_1_bss_10 = 0;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r28 = &lbl_1_bss_26C[var_r30->unk4[var_r31]];
        if (var_r28->unk4C != -1) {
            var_r29 = 1;
            lbl_1_bss_10 = 1;
        }
    }
    if (var_r29 == 5) {
        var_r27 = &lbl_1_bss_26C[var_r30->unk0];
        var_r27->unk0->rot.y = 0.0f;
    }
    fn_1_B034(&lbl_1_bss_20, var_r29);
}

void fn_1_89B0(s32 arg0)
{
    M418DllUnkStruct6 *var_r31;
    s32 var_r30;
    s32 var_r29;
    M418DllUnkStruct3 *temp_r28;
    M418DllUnkStruct4 *temp_r27;

    var_r29 = 0;
    var_r31 = &lbl_1_bss_3EC;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r28 = &lbl_1_bss_26C[var_r31->unk4[var_r30]];
        if (temp_r28->unk4C != -1) {
            var_r31->unk1C[var_r29] = var_r31->unk28[var_r29] = temp_r28->unk4C;
            var_r29++;
        }
    }
    switch (var_r29) { /* irregular */
        case 1:
            var_r31->unk1C[0] = 3;
            break;
        case 2:
            var_r31->unk1C[0] = 4;
            var_r31->unk1C[1] = 5;
            break;
        case 3:
            var_r31->unk1C[0] = 0;
            var_r31->unk1C[1] = 1;
            var_r31->unk1C[2] = 2;
            break;
    }
    if (var_r31->unk28[0] == var_r31->unk28[1]) {
        var_r31->unk28[1] = -1;
    }
    if (var_r31->unk28[0] == var_r31->unk28[1]) {
        var_r31->unk28[1] = -1;
    }
    if (var_r31->unk28[1] == var_r31->unk28[2]) {
        var_r31->unk28[2] = -1;
    }

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        temp_r27 = &lbl_1_bss_170[var_r30];
        temp_r27->unkC = 0;
    }
}

s32 fn_1_8B14(s32 arg0)
{
    M418DllUnkStruct4 *temp_r31;
    s32 var_r30;
    M418DllUnkStruct6 *var_r29;
    s32 var_r28;

    var_r29 = &lbl_1_bss_3EC;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        if (var_r29->unk28[var_r30] != -1) {
            temp_r31 = &lbl_1_bss_170[var_r29->unk28[var_r30]];
            if (temp_r31->unkC == 0) {
                if ((rand8() % 5) == 0) {
                    var_r28 = 1;
                }
                else {
                    var_r28 = 0;
                }
                if ((var_r28 != 0) || (fn_1_B0C8(&lbl_1_bss_20, 0) >= 5)) {
                    temp_r31->unkC = 1;
                    HuAudFXPlay(0x5D3);
                }
            }
            else {
                temp_r31->unk4 += 5.0f;
                if (temp_r31->unk4 >= 90.0f) {
                    temp_r31->unk4 = 90.0f;
                }
            }
        }
    }
    if (fn_1_B0C8(&lbl_1_bss_20, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_20);
    }
    else {
        return 0;
    }
}

void fn_1_8C84(s32 arg0)
{
    M418DllUnkStruct3 *temp_r31;
    s32 var_r30;
    M418DllUnkStruct6 *temp_r29;
    M418DllUnkStruct3 *temp_r28;
    s32 var_r27;
    s32 temp_r0;

    var_r27 = 0;
    temp_r29 = &lbl_1_bss_3EC;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r31 = &lbl_1_bss_26C[temp_r29->unk4[var_r30]];
        if (temp_r31->unk4C != -1) {
            omSetRot(temp_r31->unk0, 0.0f, 0.0f, 0.0f);
            temp_r31->unk50 = var_r27 * -10;
            temp_r31->unk54 = 0;
            temp_r31->unk58 = var_r27++;
        }
    }
    temp_r28 = &lbl_1_bss_26C[temp_r29->unk0];
    Hu3DMotionOverlayReset(*temp_r28->unk0->model);
    temp_r28->unk0->work[1] = 1;
}

Vec lbl_1_data_3CC[4] = { { -540.0f, 225.0f, -900.0f }, { -180.0f, 225.0f, -900.0f }, { 180.0f, 225.0f, -900.0f }, { 540.0f, 225.0f, -900.0f } };

Vec lbl_1_data_3FC[6] = { { -200.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, -400.0f }, { 200.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, -400.0f },
    { -100.0f, 0.0f, -425.0f }, { 100.0f, 0.0f, -425.0f } };

s32 fn_1_8D70(s32 arg0)
{
    s32 sp10;
    s32 spC;
    s32 sp8;
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct6 *temp_r30;
    s32 var_r29;
    M418DllUnkStruct3 *temp_r28;
    M418DllUnkStruct3 *temp_r27;
    omObjData *var_r26;
    s32 temp_r3;
    void *temp_r4;

    temp_r30 = &lbl_1_bss_3EC;

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        temp_r31 = &lbl_1_bss_26C[temp_r30->unk4[var_r29]];
        if (temp_r31->unk4C != -1) {
            if (temp_r31->unk54 == 0) {
                if (temp_r31->unk50++ == 0) {
                    temp_r31->unk54 = 1;
                    omSetTra(temp_r31->unk0, lbl_1_data_3CC[temp_r31->unk4C].x, lbl_1_data_3CC[temp_r31->unk4C].y,
                        lbl_1_data_3CC[temp_r31->unk4C].z - 50.0f);
                    var_r26 = temp_r31->unk0;
                    temp_r28 = &lbl_1_bss_26C[var_r26->work[0]];
                    if (temp_r28->unk1C == 0) {
                        temp_r28->unk1C = 1;
                    }
                }
            }
            else if (temp_r31->unk54 == 1) {
                fn_1_3EB0(temp_r31->unk0, lbl_1_data_3FC[temp_r30->unk1C[temp_r31->unk58]], 0.0f, 12.0f);
            }
        }
    }
    temp_r27 = &lbl_1_bss_26C[temp_r30->unk0];
    if (fn_1_B0C8(&lbl_1_bss_20, 0) == 0x1E) {
        fn_1_ABC4(temp_r27->unk0, 0, 0, 0xA, 1);
    }
    if (fn_1_B0C8(&lbl_1_bss_20, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_20);
    }
    else {
        return 0;
    }
}

void fn_1_8F74(s32 arg0)
{
    s32 sp8[3];
    M418DllUnkStruct3 *temp_r31;
    s32 var_r30;
    M418DllUnkStruct6 *var_r29;
    M418DllUnkStruct3 *temp_r28;

    var_r29 = &lbl_1_bss_3EC;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r31 = &lbl_1_bss_26C[var_r29->unk4[var_r30]];
        if (temp_r31->unk4C != -1) {
            fn_1_ABC4(temp_r31->unk0, 0, 5, 10, 0);
        }
        sp8[var_r30] = temp_r31->unk14;
    }
    temp_r28 = &lbl_1_bss_26C[var_r29->unk0];
    fn_1_ABC4(temp_r28->unk0, 0, 6, 10, 0);
    fn_1_87D0(1);
    lbl_1_bss_14 = MGSeqCreate(5, 3, sp8[0], sp8[1], sp8[2], -1);
    HuAudSStreamPlay(1);
}

s32 fn_1_9094(s32 arg0)
{
    if (fn_1_B0C8(&lbl_1_bss_20, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_20);
    }
    else {
        return 0;
    }
}

void fn_1_90DC(s32 arg0)
{
    M418DllUnkStruct3 *temp_r31;
    M418DllUnkStruct6 *temp_r30;

    temp_r30 = &lbl_1_bss_3EC;
    temp_r31 = &lbl_1_bss_26C[temp_r30->unk0];
    Hu3DMotionOverlayReset(temp_r31->unk0->model[0]);
    temp_r31->unk0->work[1] = 1;
}

s32 fn_1_9140(s32 arg0)
{
    M418DllUnkStruct6 *temp_r31;
    M418DllUnkStruct3 *temp_r30;

    temp_r31 = &lbl_1_bss_3EC;

    temp_r30 = &lbl_1_bss_26C[temp_r31->unk0];
    if (fn_1_B0C8(&lbl_1_bss_20, 0) == 0x1E) {
        fn_1_ABC4(temp_r30->unk0, 0, 0, 0xA, 1);
    }
    if (fn_1_B0C8(&lbl_1_bss_20, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_20);
    }
    else {
        return 0;
    }
}

void fn_1_91E4(s32 arg0)
{
    M418DllUnkStruct3 *temp_r31;
    s32 var_r30;
    M418DllUnkStruct6 *temp_r29;
    M418DllUnkStruct4 *temp_r28;

    temp_r29 = &lbl_1_bss_3EC;
    temp_r31 = &lbl_1_bss_26C[temp_r29->unk0];
    Hu3DMotionOverlayReset(temp_r31->unk0->model[0]);
    fn_1_ABC4(temp_r31->unk0, 0, 5, 10, 0);

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r28 = &lbl_1_bss_11C[var_r30];
        fn_1_ABC4(temp_r28->unk0, 0, 3, 10, 1);
    }
    fn_1_87D0(2);
    lbl_1_bss_14 = MGSeqCreate(5, 3, temp_r31->unk14, -1, -1, -1);
    HuAudSStreamPlay(1);
}

s32 fn_1_92EC(s32 arg0)
{
    if (fn_1_B0C8(&lbl_1_bss_20, 1) != 0) {
        return fn_1_AF38(&lbl_1_bss_20);
    }
    else {
        return 0;
    }
}

M418DllUnkStruct8 lbl_1_data_444[8] = { { fn_1_888C, fn_1_88B4, -1 }, { fn_1_89B0, fn_1_8B14, 90 }, { fn_1_8C84, fn_1_8D70, 180 },
    { fn_1_8F74, fn_1_9094, 210 }, { NULL, NULL, -1 }, { fn_1_90DC, fn_1_9140, 180 }, { fn_1_91E4, fn_1_92EC, 240 }, { NULL, NULL, -1 } };

void fn_1_9334(void)
{
    fn_1_AEDC(&lbl_1_bss_20, &lbl_1_data_444[0]);
}

s32 fn_1_9364(void)
{
    s32 var_r31;

    var_r31 = 0;
    if (lbl_1_bss_20.unk10 != NULL) {
        lbl_1_bss_20.unk10();
        lbl_1_bss_20.unk10 = NULL;
    }
    if (lbl_1_bss_20.unk14 != NULL) {
        var_r31 = lbl_1_bss_20.unk14();
    }
    return var_r31;
}

void fn_1_93FC(omObjData *object)
{
    s32 var_r31;
    M418DllUnkStruct6 *var_r30;
    M418DllUnkStruct3 *var_r29;
    M418DllUnkStruct3 *var_r28;
    s32 temp_r27;
    s32 temp_r26;

    if (WipeStatGet() == 0) {
        var_r30 = &lbl_1_bss_3EC;
        if (lbl_1_bss_10 != 0) {
            for (var_r31 = 0; var_r31 < 3; var_r31++) {
                var_r29 = &lbl_1_bss_26C[var_r30->unk4[var_r31]];
                temp_r27 = var_r29->unk4;
                if (_CheckFlag(0x1000C) == 0) {
                    GWPlayer[temp_r27].coin_win = 10;
                }
            }
        }
        else {
            var_r28 = &lbl_1_bss_26C[var_r30->unk0];
            temp_r26 = var_r28->unk4;
            if (_CheckFlag(0x1000CU) == 0) {
                GWPlayer[temp_r26].coin_win = 10;
            }
        }
        HuAudFadeOut(0x3E8);
        CharModelKill(-1);
        MGSeqKillAll();
        HuAudAllStop();
        omOvlReturnEx(1, 1);
        object->func = NULL;
    }
}

void fn_1_952C(omObjData *object)
{
    if (omSysExitReq == 1) {
        HuAudSeqAllFadeOut(0xFA);
        WipeCreate(2, 0, -1);
        object->func = fn_1_93FC;
    }
}

void fn_1_958C(void)
{
    M418DllUnkStruct3 *temp_r31;
    s32 var_r30;
    M418DllUnkStruct6 *temp_r29;
    M418DllUnkStruct2 *temp_r28;
    M418DllUnkStruct4 *temp_r27;
    M418DllUnkStruct4 *temp_r26;
    M418DllUnkStruct3 *temp_r25;
    s32 temp_r0;
    s32 var_r24;

    var_r24 = 0;
    temp_r28 = &lbl_1_bss_1E0;
    for (var_r30 = 1; var_r30 < 4; var_r30++) {
        fn_1_ABC4(temp_r28->unk0, var_r30, var_r30, 0, 2);
    }

    for (var_r30 = 8; var_r30 < 11; var_r30++) {
        fn_1_ABC4(temp_r28->unk0, var_r30, var_r30, 0, 1);
        Hu3DModelPosSet(temp_r28->unk0->model[var_r30 + 8], -360.0f + (360.0f * (var_r30 - 8)), -200.0f, -660.0f);
        Hu3DModelRotSet(temp_r28->unk0->model[var_r30], 0.0f, 0.0f, 20.0f);
    }

    temp_r28->unk4[0] = temp_r28->unk4[1] = temp_r28->unk4[2] = temp_r28->unk4[3] = 0;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        temp_r27 = &lbl_1_bss_170[var_r30];
        temp_r27->unk0->work[1] = temp_r27->unk0->work[2] = 0;
        temp_r27->unk4 = 0.0f;
        temp_r27->unkC = temp_r27->unk10 = temp_r27->unk14s = temp_r27->unk18s = 0;
    }

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r26 = &lbl_1_bss_11C[var_r30];
        omSetTra(temp_r26->unk0, lbl_1_data_8C[var_r30].x, lbl_1_data_8C[var_r30].y, lbl_1_data_8C[var_r30].z);
        omSetRot(temp_r26->unk0, 0.0f, 0.0f, 0.0f);
        omSetSca(temp_r26->unk0, 1.0f, 1.0f, 1.0f);
        fn_1_AD14(temp_r26->unk0, 0, 0, 10, 1);
        temp_r26->unk0->work[1] = -1U;
    }

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        temp_r31 = &lbl_1_bss_26C[var_r30];
        if (temp_r31->unk8 != 0) {
            omSetTra(temp_r31->unk0, 0.0f, -5000.0f, 0.0f);
        }
        else {
            omSetTra(temp_r31->unk0, 0.0f, 0.0f, 0.0f);
        }
        omSetRot(temp_r31->unk0, 0.0f, 0.0f, 0.0f);
        omSetSca(temp_r31->unk0, 1.0f, 1.0f, 1.0f);
        if (temp_r31->unk8 == 0) {
            Hu3DModelAttrReset(temp_r31->unk0->model[11], 1);
            Hu3DModelHookSet(temp_r31->unk0->model[0], lbl_1_data_1C0[temp_r31->unk14], temp_r31->unk0->model[11]);
            Hu3DModelPosSet(temp_r31->unk0->model[11], 0.0f, 0.0f, 0.0f);
            Hu3DModelRotSet(temp_r31->unk0->model[11], 0.0f, 0.0f, 0.0f);
            Hu3DMotionOverlaySet(temp_r31->unk0->model[0], temp_r31->unk0->motion[9]);
            Hu3DMotionOverlaySpeedSet(temp_r31->unk0->model[0], 0.0f);
        }
        fn_1_ABC4(temp_r31->unk0, 0, 0, 0, 1);
        Hu3DModelShadowDispOn(temp_r31->unk0->model[0]);
        temp_r31->unk4C = temp_r31->unk50 = temp_r31->unk54 = temp_r31->unk58 = temp_r31->unk5C = 0;
        temp_r31->unk24 = -1;
        temp_r31->unk28 = temp_r31->unk2C = temp_r31->unk30 = temp_r31->unk34 = temp_r31->unk38 = 0.0f;
    }

    temp_r29 = &lbl_1_bss_3EC;
    for (var_r30 = 0, var_r24 = 0; var_r30 < 4; var_r30++) {
        temp_r25 = &lbl_1_bss_26C[var_r30];
        if (temp_r25->unk8 != 0) {
            temp_r29->unk4[var_r24++] = temp_r25->unk4;
        }
        else {
            temp_r29->unk0 = temp_r25->unk4;
        }
    }

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r29->unk1C[var_r30] = temp_r29->unk28[var_r30] = -1;
        temp_r29->unk10[var_r30] = -1;
    }

    temp_r29->unk34 = temp_r29->unk38 = temp_r29->unk3C = temp_r29->unk40 = 0;
    fn_1_5D28();
    fn_1_8480();
    fn_1_9334();

    for (var_r30 = 0; var_r30 < 10; var_r30++) {
        lbl_1_bss_240[var_r30] = -1;
    }
    lbl_1_bss_240[6] = HuAudFXPlay(0x5D7);
    lbl_1_bss_240[7] = HuAudFXPlay(0x5D8);
}

void fn_1_9BA4(omObjData *object)
{
    switch (lbl_1_bss_18) {
        case 0:
            fn_1_958C();
            lbl_1_bss_18 = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                lbl_1_bss_18 = 2;
            }
            break;
        case 2:
            if (fn_1_5D58()) {
                lbl_1_bss_18 = 3;
            }
            break;
        case 3:
            lbl_1_bss_1C = MGSeqCreate(3, 0);
            lbl_1_bss_18 = 4;
            lbl_1_data_0[1] = -1;
            break;
        case 4:
            if (((MGSeqStatGet(lbl_1_bss_1C) & 0x10) != 0) && (lbl_1_data_0[1] == -1)) {
                lbl_1_data_0[1] = HuAudSeqPlay(0x49);
            }
            if (MGSeqStatGet(lbl_1_bss_1C) == 0) {
                lbl_1_bss_18 = 5;
            }
            break;
        case 5:
            if (fn_1_84B0()) {
                lbl_1_bss_18 = 6;
            }
            break;
        case 6:
            lbl_1_bss_1C = MGSeqCreate(3, 1);
            HuAudSeqPauseAll(0);
            HuAudSeqAllFadeOut(0x64);
            lbl_1_bss_18 = 7;
            break;
        case 7:
            if (MGSeqStatGet(lbl_1_bss_1C) == 0) {
                lbl_1_bss_18 = 8;
            }
            break;
        case 8:
            if (fn_1_9364()) {
                lbl_1_bss_18 = 9;
            }
            break;
        case 9:
            WipeCreate(2, 0, -1);
            object->func = fn_1_93FC;
            break;
        default:
            lbl_1_bss_18 = 0;
            break;
    }
    if (omSysExitReq == 1) {
        HuAudSeqAllFadeOut(0xFA);
        WipeCreate(2, 0, -1);
        object->func = fn_1_93FC;
    }
}

void fn_1_9F94(omObjData *object)
{
    s32 var_r31;
    M418DllUnkStruct4 *temp_r30;
    M418DllUnkStruct4 *temp_r29;
    M418DllUnkStruct3 *temp_r28;
    M418DllUnkStruct2 *temp_r27;
    M418DllWorkStruct *temp_r26;

    temp_r27 = &lbl_1_bss_1E0;
    temp_r27->unk0 = omAddObjEx(lbl_1_bss_0, 0x100, 0x14U, 0x14U, -1, fn_1_B4C);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        temp_r30 = &lbl_1_bss_170[var_r31];
        temp_r30->unk0 = omAddObjEx(lbl_1_bss_0, 0x200, 0x14U, 0x14U, -1, fn_1_14F0);
        temp_r30->unk0->work[0] = var_r31;
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        temp_r29 = &lbl_1_bss_11C[var_r31];
        temp_r29->unk0 = omAddObjEx(lbl_1_bss_0, 0x300, 0x14U, 0x14U, -1, fn_1_29A0);
        temp_r29->unk0->work[0] = var_r31;
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        temp_r28 = &lbl_1_bss_26C[var_r31];
        temp_r28->unk0 = omAddObjEx(lbl_1_bss_0, 0x400, 0x14U, 0x14U, -1, fn_1_4F60);
        temp_r28->unk0->work[0] = var_r31;
    }

    temp_r26 = &lbl_1_bss_68;
    temp_r26->unk0 = omAddObjEx(lbl_1_bss_0, 0x500, 0xBU, 0xBU, -1, fn_1_3054);
    WipeCreate(1, 0, -1);
    object->func = fn_1_9BA4;
}

#include "src/REL/executor.c"

void fn_1_A1F0(void)
{
    lbl_1_bss_0 = omInitObjMan(0x3E, 0x2000);
    omGameSysInit(lbl_1_bss_0);
    HuAudAUXVolSet(-1, -1);
    fn_1_0();
    fn_1_500();
    fn_1_618();
    fn_1_3138();
    omAddObjEx(lbl_1_bss_0, 0x1000, 0U, 0U, -1, fn_1_9F94);
    omAddObjEx(lbl_1_bss_0, 0x2000, 0U, 0U, -1, fn_1_780);
}

void ObjectSetup(void)
{
    fn_1_A1F0();
}
