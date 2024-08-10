#include "ext_math.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "REL/present.h"

void fn_1_4620(omObjData *arg0);
void fn_1_4880(omObjData *arg0);

omObjFunc lbl_1_data_1A0[] = { NULL, fn_1_4620, fn_1_4880 };

static const s32 lbl_1_rodata_BD8[] = { 0x006E0089, 0x006E008A, 0x006E008B };

void fn_1_4A04(omObjData *object);
float fn_1_4CEC(float arg8, float arg9, float argA);

omObjData *fn_1_42F4(void)
{
    omObjData *var_r31;
    s32 var_lr;
    s32 var_r29;
    UnkPresentStruct5 *var_r30;

    var_r31 = omAddObjEx(lbl_1_bss_4, 1002, 1, 3, 2, NULL);
    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, 88, MEMORY_DEFAULT_NUM);
    var_r31->data = var_r30;
    var_r30->x = 0.0f;
    var_r30->z = 0.0f;
    var_r30->y = 0.0f;
    var_r30->unk_20 = 0.0f;
    var_r30->unk_24 = 0.0f;
    var_r30->unk_28 = 0.0f;
    var_r30->unk_2C = 0.0f;
    var_r30->unk_34 = 0.0f;
    var_r30->unk_30 = 0.0f;
    var_r31->model[0] = Hu3DModelCreate(HuDataReadNum(0x6E0088, MEMORY_DEFAULT_NUM));
    Hu3DModelLayerSet(var_r31->model[0], 1);

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        var_r31->motion[var_r29] = Hu3DJointMotion(var_r31->model[0], HuDataSelHeapReadNum(lbl_1_rodata_BD8[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA));
    }
    Hu3DMotionShiftSet(var_r31->model[0], var_r31->motion[var_r30->unk_04 = 0], 0.0f, 8.0f, 0x40000001);
    var_r30->unk_50 = CharModelEffectNpcInit(var_r31->model[0], var_r31->motion[2], 1, 10);
    var_r30->unk_54 = CharModelEffectNpcInit(var_r31->model[0], var_r31->motion[1], 0, 10);
    CharModelLayerSetAll(1);
    Hu3DModelShadowSet(var_r31->model[0]);
    fn_1_45C0(var_r31, 0);
    fn_1_4A04(var_r31);
    Hu3DModelAttrSet(var_r31->model[0], 1);

    return var_r31;
}

void fn_1_4534(omObjData *object)
{
    s32 var_r31;
    void *var_r29;
    void *var_r30;

    var_r29 = object->data;

    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        Hu3DModelKill(object->model[var_r31]);
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        Hu3DMotionKill(object->motion[var_r31]);
    }
    HuMemDirectFree(var_r29);
}

void fn_1_45C0(omObjData *object, s32 arg1)
{
    UnkPresentStruct5 *var_r31;

    var_r31 = object->data;
    var_r31->unk_00 = arg1;
    object->func = lbl_1_data_1A0[arg1];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 fn_1_4604(omObjData *object)
{
    s32 *var_r31;

    var_r31 = object->data;
    return *var_r31;
}

void fn_1_4620(omObjData *object)
{
    float var_f31;
    omObjData *var_r30;
    void *var_r29;
    UnkPresentStruct5 *var_r31;

    var_r31 = object->data;
    switch (object->unk10) {
    case 0:
        Hu3DModelAttrReset(object->model[0], 1);
        var_r31->x = -300.0f;
        var_r31->z = -180.0f;
        var_r31->unk_48 = 0.0f;
        var_r31->unk_4C = 0.025f;
        object->unk10 = 1;
    case 1:
        var_f31 = sind(90.0f * var_r31->unk_48);
        var_f31 *= var_f31;
        var_r31->unk_14 = -300.0f + (300.0f * var_f31);
        var_r31->unk_2C = var_r31->unk_14 - var_r31->x;
        if ((var_r31->unk_48 = var_r31->unk_48 + var_r31->unk_4C) < 1.0f) {
            break;
        }
        var_r31->x = 0.0f;
        var_r31->unk_48 = 0.0f;
        var_r31->unk_4C = 0.05f;
        object->unk10 = 2;
    case 2:
        var_r31->unk_2C = 0.0f;
        var_r31->unk_34 = 0.01f;
        if ((var_r31->unk_48 = var_r31->unk_48 + var_r31->unk_4C) < 1.0f) {
            break;
        }
        var_r31->unk_24 = 0.0f;
        var_r31->unk_2C = 0.0f;
        var_r31->unk_30 = 0.0f;
        var_r31->unk_34 = 0.0f;
        object->unk10 = 3;
    case 3:
        fn_1_45C0(object, 0);
        break;
    default:
        break;
    }
    fn_1_4A04(object);
}

void fn_1_4880(omObjData *object)
{
    float var_f31;
    UnkPresentStruct5 *var_r30;
    void *var_r29;

    var_r30 = object->data;
    switch (object->unk10) {
    case 0:
        var_r30->unk_48 = 0.0f;
        var_r30->unk_4C = 0.025f;
        Hu3DModelAttrReset(object->model[0], 1);
        object->unk10 = 1;
    case 1:
        var_f31 = sind(90.0f * var_r30->unk_48);
        var_f31 *= var_f31;
        var_r30->unk_14 = -(300.0f * var_f31);
        var_r30->unk_2C = var_r30->unk_14 - var_r30->x;
        if ((var_r30->unk_48 = var_r30->unk_48 + var_r30->unk_4C) < 1.0f) {
            break;
        }
        object->unk10 = 2;
    case 2:
        Hu3DModelAttrSet(object->model[0], 1);
        fn_1_45C0(object, 0);
        break;
    default:
        break;
    }
    fn_1_4A04(object);
    (void)object;
}

void fn_1_4A04(omObjData *object)
{
    float var_f29;
    float var_f30;
    s16 var_r29;
    UnkPresentStruct5 *var_r31;

    var_r31 = object->data;
    var_r29 = 0;
    var_f30 = var_r31->unk_2C * var_r31->unk_2C + var_r31->unk_34 * var_r31->unk_34;
    var_r31->unk_38 = sqrtf(var_f30);
    if (0.001f <= var_r31->unk_38) {
        if (12.0f <= var_r31->unk_38) {
            var_r31->unk_2C = var_r31->unk_2C / var_r31->unk_38;
            var_r31->unk_34 = var_r31->unk_34 / var_r31->unk_38;
            var_r31->unk_38 = 12.0f;
            var_r31->unk_2C = 12.0f * var_r31->unk_2C;
            var_r31->unk_34 = 12.0f * var_r31->unk_34;
        }
        var_r31->unk_24 = fn_1_4CEC(var_r31->unk_24, atan2d(var_r31->unk_2C, var_r31->unk_34), 0.4f);

        if (8.0f <= var_r31->unk_38) {
            var_r29 = 2;
        } else {
            var_r29 = 1;
        }
    }
    var_r31->x = var_r31->x + var_r31->unk_2C;
    var_r31->z = var_r31->z + var_r31->unk_34;
    if (var_r31->unk_04 != var_r29) {
        Hu3DMotionShiftSet(object->model[0], object->motion[var_r31->unk_04 = var_r29], 0.0f, 8.0f, 0x40000001); // or 0x41000000
    }
    omSetTra(object, var_r31->x, var_r31->y, var_r31->z);
    omSetRot(object, var_r31->unk_20, var_r31->unk_24, var_r31->unk_28);
}

float fn_1_4CEC(float arg8, float arg9, float argA)
{
    float var_f30;
    float var_f31;

    var_f31 = fmod(arg9 - arg8, 360.0f);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg8 + (var_f31 * argA), 360.0f);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}
