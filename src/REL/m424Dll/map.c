#include "REL/m424Dll.h"

#include "game/audio.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "math.h"
#include <string.h>

// STRUCT
typedef struct _M424DllMapStruct {
    f32 unk0;
    f32 unk4;
    Mtx unk8;
    s32 unk38;
    f32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
} M424DllMapStruct; // sizeof 0x54

// BSS
Process *lbl_1_bss_54;
omObjData *lbl_1_bss_50;

// DATA
Vec lbl_1_data_E0 = { 0.0f, 3000.0f, 1.0f };
Vec lbl_1_data_EC = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_F8 = { 0.0f, 0.0f, 0.0f };

// PROTO
void fn_1_1BB8(omObjData *);
void fn_1_1E1C(omObjData *);
void fn_1_2130(omObjData *);
void fn_1_2438(f32);

omObjData *fn_1_1AB8(Process *arg0)
{
    lbl_1_bss_54 = arg0;
    lbl_1_bss_50 = omAddObjEx(arg0, 0x7F, 6, 0, -1, fn_1_1BB8);
    lbl_1_bss_50->data = NULL;
    Hu3DShadowCreate(45.0f, 1000.0f, 250000.0f);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowPosSet(&lbl_1_data_E0, &lbl_1_data_EC, &lbl_1_data_F8);
    return lbl_1_bss_50;
}

void fn_1_1B8C(void)
{
    fn_1_2130(lbl_1_bss_50);
}

void fn_1_1BB8(omObjData *arg0)
{
    M424DllMapStruct *var_r30;

    var_r30 = arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M424DllMapStruct), MEMORY_DEFAULT_NUM);
    memset(var_r30, 0, sizeof(M424DllMapStruct));
    var_r30->unk0 = 0.0f;
    var_r30->unk4 = 0.0f;
    var_r30->unk38 = -1;
    var_r30->unk3C = 0.0f;
    var_r30->unk40 = 0;
    var_r30->unk44 = -1;
    var_r30->unk48 = 0;
    var_r30->unk4C = 0;
    var_r30->unk50 = -1;
    arg0->model[0] = Hu3DModelCreateFile(0x370017);
    arg0->model[1] = Hu3DModelCreateFile(0x370018);
    arg0->model[2] = Hu3DModelCreateFile(0x370019);
    arg0->model[3] = Hu3DModelCreateFile(0x37001A);
    arg0->model[4] = Hu3DModelCreateFile(0x37001B);
    arg0->model[5] = Hu3DModelCreateFile(0x37001C);
    Hu3DModelAttrSet(arg0->model[4], 1);
    Hu3DMotionSpeedSet(arg0->model[1], var_r30->unk0);
    Hu3DModelAttrSet(arg0->model[1], 0x40000001);
    Hu3DMotionSpeedSet(arg0->model[0], 0.15f);
    Hu3DModelAttrSet(arg0->model[0], 0x40000001);
    Hu3DModelPosSet(arg0->model[2], 847.135f, 0.0f, 424.56f);
    Hu3DMotionSpeedSet(arg0->model[4], 2.0f);
    Hu3DModelAttrSet(arg0->model[4], 0x40000001);
    Hu3DModelShadowMapSet(arg0->model[0]);
    Hu3DModelShadowMapSet(arg0->model[1]);
    Hu3DModelShadowMapSet(arg0->model[2]);
    arg0->func = fn_1_1E1C;
}

void fn_1_1E1C(omObjData *arg0)
{
    f32 temp_f31;
    M424DllMapStruct *temp_r31;

    temp_r31 = arg0->data;
    if (temp_r31->unk40 > 0) {
        fn_1_2438(temp_r31->unk3C);
        if ((--temp_r31->unk40 <= 0) && (temp_r31->unk44 != -1)) {
            HuAudFXStop(temp_r31->unk44);
            temp_r31->unk44 = -1;
        }
    }
    switch (fn_1_FE0()) {
        case 0:
            temp_r31->unk0 = 0.5f;
            break;
        case 1:
        case 2:
            temp_r31->unk0 = 0.0f;
            break;
        case 3:
        case 4:
            temp_r31->unk0 += 0.001f;
            if (temp_r31->unk0 > 0.04f) {
                temp_r31->unk0 = 0.04f;
            }
            if (temp_r31->unk38 != -1)
                break;

            temp_r31->unk38 = HuAudFXPlay(0x626);
            break;
        default:
            if ((fn_1_B804() == 0) && (fn_1_8A2C() != 0)) {
                temp_r31->unk0 *= 0.9f;
                if (temp_r31->unk0 < 0.01f) {
                    temp_r31->unk0 = 0.0f;
                }
                temp_f31 = temp_r31->unk0 / 0.04f;
                if (temp_r31->unk38 != -1) {
                    HuAudFXVolSet(temp_r31->unk38, (s16)(-8191.0f * (1.0f - temp_f31)));
                    HuAudFXPitchSet(temp_r31->unk38, (s16)(127.0f * temp_f31));
                    if (temp_f31 <= 0.0f) {
                        HuAudFXStop(temp_r31->unk38);
                        temp_r31->unk38 = -1;
                    }
                }
            }
            break;
    }

    if (temp_r31->unk48 != 0) {
        if (temp_r31->unk4C != 0) {
            temp_r31->unk4C = (temp_r31->unk4C - 1);
        }
        else {
            temp_r31->unk48 = (temp_r31->unk48 - 1);
            if (temp_r31->unk48 != 0) {
                Hu3DModelAttrReset(arg0->model[4], 1);
                Hu3DModelAttrSet(arg0->model[5], 1);
            }
            else {
                Hu3DModelAttrSet(arg0->model[4], 1);
                Hu3DModelAttrReset(arg0->model[5], 1);
                if (temp_r31->unk50 != -1) {
                    HuAudFXStop(temp_r31->unk50);
                    temp_r31->unk50 = -1;
                }
            }
        }
    }
    temp_r31->unk4 = (20.0f * temp_r31->unk0);
    MTXRotRad(temp_r31->unk8, 0x59, MTXDegToRad(temp_r31->unk4));
    Hu3DMotionSpeedSet(arg0->model[1], temp_r31->unk0);
}

void fn_1_2130(omObjData *arg0)
{
    arg0->func = NULL;
}

f32 fn_1_213C(void)
{
    M424DllMapStruct *var_r31;
    if (!lbl_1_bss_50) {
        return 0.0f;
    }
    if (!lbl_1_bss_50->data) {
        return 0.0f;
    }
    var_r31 = lbl_1_bss_50->data;
    return var_r31->unk4;
}

void fn_1_21B0(Mtx arg0)
{
    M424DllMapStruct *var_r31;
    if (lbl_1_bss_50 && lbl_1_bss_50->data) {
        var_r31 = lbl_1_bss_50->data;
        MTXCopy(var_r31->unk8, *(Mtx *)&arg0);
    }
}

void fn_1_2220(Vec *arg0, Vec *arg1)
{
    Vec spC;
    M424DllMapStruct *temp_r30;

    if (lbl_1_bss_50 && lbl_1_bss_50->data) {
        temp_r30 = lbl_1_bss_50->data;
        if (sqrtf((arg0->x * arg0->x) + (arg0->z * arg0->z)) < 700.0f) {
            spC.x = (temp_r30->unk8[0][0] * arg0->x) + (temp_r30->unk8[0][2] * arg0->z);
            spC.z = (temp_r30->unk8[2][0] * arg0->x) + (temp_r30->unk8[2][2] * arg0->z);
            spC.y = arg0->y;
        }
        else {
            spC = *arg0;
        }
        VECSubtract(&spC, arg0, &spC);
        *arg1 = spC;
    }
}

void fn_1_2438(f32 arg0)
{
    M424DllMapStruct *spC;
    HsfAttribute *var_r31;
    ModelData *temp_r30;
    HsfData *temp_r29;
    s32 var_r28;
    HsfBitmap *var_r27;
    omObjData *var_r26;

    if (lbl_1_bss_50 && lbl_1_bss_50->data) {
        var_r26 = lbl_1_bss_50;
        spC = lbl_1_bss_50->data;
        temp_r30 = &Hu3DData[var_r26->model[2]];
        temp_r29 = temp_r30->hsfData;
        var_r31 = temp_r30->hsfData->attribute;
        for (var_r28 = 0; var_r28 < temp_r29->attributeCnt; var_r28++, var_r31++) {
            var_r27 = var_r31->bitmap;
            if (strcmp("cr_dk2", var_r27->name) == 0)
                break;
        }
        if (var_r28 < temp_r29->attributeCnt) {
            var_r31->unk30 += arg0;
        }
    }
}

void fn_1_252C(f32 arg8, s32 arg0)
{
    omObjData *sp10;
    M424DllMapStruct *temp_r31;

    if (lbl_1_bss_50 && lbl_1_bss_50->data) {
        sp10 = lbl_1_bss_50;
        temp_r31 = lbl_1_bss_50->data;
        temp_r31->unk44 = HuAudFXPlay(0x627);
        temp_r31->unk3C = arg8;
        temp_r31->unk40 = arg0;
    }
}

f32 fn_1_25C0(void)
{
    omObjData *sp8;
    M424DllMapStruct *temp_r31;

    if (!lbl_1_bss_50) {
        return 0.0f;
    }
    if (!lbl_1_bss_50->data) {
        return 0.0f;
    }
    sp8 = lbl_1_bss_50;
    temp_r31 = lbl_1_bss_50->data;
    if (temp_r31->unk40 != 0) {
        return 250.0f * temp_r31->unk3C;
    }
    return 0.0f;
}

void fn_1_2670(s32 arg0, s32 arg1)
{
    omObjData *temp_r30;
    M424DllMapStruct *temp_r31;

    if (lbl_1_bss_50 && lbl_1_bss_50->data) {
        temp_r30 = lbl_1_bss_50;
        temp_r31 = lbl_1_bss_50->data;
        temp_r31->unk50 = HuAudFXPlay(0x629);
        temp_r31->unk48 = arg0;
        temp_r31->unk4C = arg1;
        Hu3DMotionTimeSet(temp_r30->model[4], 0.0f);
    }
}

// UNUSED (guessing types)
M424DllMainStruct lbl_1_data_10C = { { 0.0f, 0.0f, 5500.0f }, { -3950.0f, 0.0f, -0.7f }, 0.6f };

GXColor lbl_1_data_128 = { 0xFF, 0xFF, 0xFF, 0xFF };
M424DllMainStruct lbl_1_data_12C = { { 0.0f, 5500.0f, -3950.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f };

s32 lbl_1_data_148[2] = { 0 };
