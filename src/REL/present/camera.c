#include "ext_math.h"
#include "game/hsfman.h"
#include "game/pad.h"
#include "game/printfunc.h"

#include "REL/present.h"

void fn_1_C20(omObjData *object);

omObjData *fn_1_6B4(void)
{
    omObjData *var_r30;
    UnkPresentCameraStruct *var_r31;

    var_r30 = omAddObjEx(lbl_1_bss_4, 1001, 0, 0, 3, fn_1_BF8);
    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, 156, MEMORY_DEFAULT_NUM);
    var_r30->data = var_r31;

    var_r31->pos.x = 0.0f;
    var_r31->pos.y = 0.0f;
    var_r31->pos.z = 0.0f;

    var_r31->target.x = 0.0f;
    var_r31->target.y = 0.0f;
    var_r31->target.z = 0.0f;

    var_r31->up.x = 0.0f;
    var_r31->up.y = 1.0f;
    var_r31->up.z = 0.0f;

    var_r31->unk_24 = 0.0f;
    var_r31->unk_28 = 0.0f;
    var_r31->unk_8C = 1.0f;
    var_r31->unk_84 = 1.0f;
    var_r31->unk_94 = 1.0f;
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 42.0f, 10.0f, 8000.0f, 1.2f);
    fn_1_9A4(var_r30, 0.0f, 0.0f, -600.0f, 1);
    fn_1_920(var_r30, 0.0f, 220.0f, 250.0f, 1);

    return var_r30;
}

void fn_1_8F0(omObjData *object)
{
    HuMemDirectFree(object->data);
}

void fn_1_920(omObjData *object, float arg8, float arg9, float argA, s32 arg1)
{
    UnkPresentCameraStruct *var_r31;

    var_r31 = object->data;
    var_r31->unk_58.x = arg8;
    var_r31->unk_58.y = arg9;
    var_r31->unk_58.z = argA;

    var_r31->unk_2C = var_r31->pos;
    var_r31->unk_84 = 0.0f;
    var_r31->unk_88 = 1.0f / arg1;
}

void fn_1_9A4(omObjData *object, float arg8, float arg9, float argA, s32 arg1)
{
    UnkPresentCameraStruct *var_r31;

    var_r31 = object->data;
    var_r31->unk_64.x = arg8;
    var_r31->unk_64.y = arg9;
    var_r31->unk_64.z = argA;

    var_r31->unk_38 = var_r31->target;
    var_r31->unk_8C = 0.0f;
    var_r31->unk_90 = 1.0f / arg1;
}

void fn_1_A28(omObjData *object, s32 arg1, float arg8, float arg9, float argA)
{
    UnkPresentCameraStruct *var_r31;

    var_r31 = object->data;
    var_r31->unk_64.y = argA;
    var_r31->unk_7C = arg8;
    var_r31->unk_80 = arg9;

    var_r31->unk_38.y = var_r31->target.y;
    var_r31->unk_50 = var_r31->unk_24;
    var_r31->unk_54 = var_r31->unk_28;
    var_r31->unk_94 = 0.0f;
    var_r31->unk_98 = 1.0f / arg1;
}

float fn_1_AAC(omObjData *object)
{
    UnkPresentCameraStruct *var_r31;
    float var_f31;

    var_r31 = object->data;
    var_f31 = var_r31->unk_24;
    return var_f31;
}

float fn_1_ADC(omObjData *object)
{
    UnkPresentCameraStruct *var_r31;
    float var_f31;

    var_r31 = object->data;
    var_f31 = var_r31->unk_28;
    return var_f31;
}

void fn_1_B0C(omObjData *object, float *arg1, float *arg2, float *arg3)
{
    UnkPresentCameraStruct *var_r31;

    var_r31 = object->data;
    *arg1 = var_r31->pos.x;
    *arg2 = var_r31->pos.y;
    *arg3 = var_r31->pos.z;
}

void fn_1_B3C(omObjData *object, float *arg1, float *arg2, float *arg3)
{
    UnkPresentCameraStruct *var_r31;

    var_r31 = object->data;
    *arg1 = var_r31->target.x;
    *arg2 = var_r31->target.y;
    *arg3 = var_r31->target.z;
}

s32 fn_1_B6C(omObjData *object)
{
    UnkPresentCameraStruct *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = object->data;
    var_r30 = 1;
    var_r29 = 1;
    if (!(var_r31->unk_8C < 1.0f) && !(var_r31->unk_94 < 1.0f)) {
        var_r29 = 0;
    }
    if (!var_r29 && !(var_r31->unk_84 < 1.0f)) {
        var_r30 = 0;
    }
    return var_r30;
}

void fn_1_BF8(omObjData *object)
{
    fn_1_C20(object);
}

void fn_1_C20(omObjData *object)
{
    UnkPresentCameraStruct *var_r31;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    var_r31 = object->data;
    if (var_r31->unk_84 < 1.0f) {
        var_f28 = sind(90.0f * var_r31->unk_84);
        var_r31->pos.x = var_r31->unk_2C.x + var_f28 * (var_r31->unk_58.x - var_r31->unk_2C.x);
        var_r31->pos.y = var_r31->unk_2C.y + var_f28 * (var_r31->unk_58.y - var_r31->unk_2C.y);
        var_r31->pos.z = var_r31->unk_2C.z + var_f28 * (var_r31->unk_58.z - var_r31->unk_2C.z);

        if ((var_r31->unk_84 += var_r31->unk_88) >= 1.0f) {
            var_r31->pos = var_r31->unk_58;
        }
    }
    if (var_r31->unk_8C < 1.0f) {
        var_f28 = sind(90.0f * var_r31->unk_8C);
        var_r31->target.x = var_r31->unk_38.x + var_f28 * (var_r31->unk_64.x - var_r31->unk_38.x);
        var_r31->target.y = var_r31->unk_38.y + var_f28 * (var_r31->unk_64.y - var_r31->unk_38.y);
        var_r31->target.z = var_r31->unk_38.z + var_f28 * (var_r31->unk_64.z - var_r31->unk_38.z);

        if ((var_r31->unk_8C += var_r31->unk_90) >= 1.0f) {
            var_r31->target = var_r31->unk_64;
        }
    }
    if (var_r31->unk_94 < 1.0f) {
        var_f28 = sind(90.0f * var_r31->unk_94);
        var_r31->target.y = var_r31->unk_38.y + (var_f28 * (var_r31->unk_64.y - var_r31->unk_38.y));
        var_r31->unk_24 = var_r31->unk_50 + (var_f28 * (var_r31->unk_7C - var_r31->unk_50));
        var_r31->unk_28 = var_r31->unk_54 + (var_f28 * (var_r31->unk_80 - var_r31->unk_54));

        if ((var_r31->unk_94 += var_r31->unk_98) >= 1.0f) {
            var_r31->target.y = var_r31->unk_64.y;
            var_r31->unk_24 = var_r31->unk_7C;
            var_r31->unk_28 = var_r31->unk_80;
        }
        var_r31->target.x = var_r31->unk_24 * -sind(var_r31->unk_28);
        var_r31->target.z = var_r31->unk_24 * cosd(var_r31->unk_28);
    }
    var_f31 = var_r31->target.x - var_r31->pos.x;
    var_f30 = var_r31->target.z - var_r31->pos.z;

    var_r31->unk_24 = sqrtf(var_f31 * var_f31 + var_f30 * var_f30);
    var_r31->unk_28 = fmod(-atan2d(var_f31, var_f30), 360.0);
    if (var_r31->unk_28 < 0.0f) {
        var_r31->unk_28 += 360.0f;
    }
    Hu3DCameraPosSet(1, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z, var_r31->up.x, var_r31->up.y, var_r31->up.z, var_r31->target.x,
        var_r31->target.y, var_r31->target.z);
}

void fn_1_1198(omObjData *object)
{
    UnkPresentCameraStruct *var_r31;

    if (HuPadBtn[0] & PAD_BUTTON_B) {
        var_r31 = object->data;
        var_r31->target.x = var_r31->target.x + (0.5f * HuPadStkX[0]);
        var_r31->target.y = var_r31->target.y + (0.5f * HuPadStkY[0]);
        var_r31->pos.z = var_r31->pos.z + (0.5f * HuPadTrigL[0]);
        var_r31->pos.z = var_r31->pos.z - (0.5f * HuPadTrigR[0]);
        var_r31->pos.x = var_r31->pos.x + (0.5f * HuPadSubStkY[0]);
        var_r31->pos.y = var_r31->pos.y + (0.5f * HuPadSubStkX[0]);
    }
}

void fn_1_1398(omObjData *object)
{
    UnkPresentCameraStruct *var_r31;

    var_r31 = object->data;
    print8(32, 64, 1.5f, "AT  : x=%.2f y=%.2f z=%.2f", var_r31->target.x, var_r31->target.y, var_r31->target.z);
    print8(32, 80, 1.5f, "EYE : x=%.2f y=%.2f z=%.2f", var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
    print8(32, 96, 1.5f, "R : %.2f    DEG: %.2f", var_r31->unk_24, var_r31->unk_28);
}
