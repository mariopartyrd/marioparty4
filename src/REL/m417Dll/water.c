#include "ext_math.h"
#include "game/audio.h"
#include "game/hsfdraw.h"
#include "game/hsfmotion.h"
#include "game/sprite.h"

#include "REL/m417Dll.h"

typedef struct UnkM417Struct3 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk02[4];
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ Vec unk_08;
    /* 0x14 */ Vec unk_14;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ float unk_30;
    /* 0x34 */ float unk_34;
} UnkM417Struct3; /* size = 0x38 */

typedef struct UnkM417Struct5 {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ float *unk_20;
    /* 0x24 */ u16 *unk_24;
} UnkM417Struct5; /* size = 0x28 */

typedef struct UnkM417Struct6 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ Vec unk_04;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
    /* 0x1C */ float unk_1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ char unk30[0x30];
} UnkM417Struct6; /* size = 0x60 */

typedef struct UnkM417Struct4 {
    /* 0x00 */ float unk_00; // maybe Vec
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ u16 *unk_1C;
    /* 0x20 */ float *unk_20;
    /* 0x24 */ float *unk_24;
    /* 0x28 */ s32 *unk_28;
    /* 0x2C */ Vec *unk_2C;
    /* 0x30 */ Vec *unk_30;
    /* 0x34 */ Vec *unk_34;
    /* 0x38 */ u16 (*unk_38)[4];
    /* 0x3C */ UnkM417Struct5 unk_3C[3];
    /* 0xB4 */ UnkM417Struct6 unk_B4[16];
    /* 0x6B4 */ s32 unk_6B4;
    /* 0x6B8 */ float unk_6B8;
    /* 0x6BC */ Vec *unk_6BC[2];
    /* 0x6C4 */ Vec *unk_6C4[2];
    /* 0x6CC */ GXColor *unk_6CC[2];
    /* 0x6D4 */ Vec2f *unk_6D4[2];
    /* 0x6DC */ s32 unk_6DC;
    /* 0x6E0 */ void *unk_6E0[2];
    /* 0x6E8 */ s32 unk_6E8[2];
    /* 0x6F0 */ u32 unk_6F0;
    /* 0x6F4 */ void *unk_6F4;
    /* 0x6F8 */ char unk6F8[8];
} UnkM417Struct4; /* size = 0x700 */

float fn_1_2F08(float arg8, float arg9, float arg10);
void fn_1_3400(omObjData *object);
void fn_1_3534(omObjData *object);
UnkM417Struct3 *fn_1_3574(omObjData *object, s16 arg1, s16 arg2);
void fn_1_37A0(omObjData *object, UnkM417Struct3 *arg1);
void fn_1_3B1C(omObjData *object, UnkM417Struct3 *arg1);
void fn_1_3BC4(omObjData *object);
void fn_1_3D54(omObjData *object);
void fn_1_3D58(omObjData *object);
void fn_1_57B0(omObjData *object);
void fn_1_5E3C(omObjData *object);
void fn_1_604C(ModelData *model, Mtx mtx);
void fn_1_6B04(ModelData *model, Mtx mtx);
void fn_1_6B60(ModelData *model, Mtx mtx);
void fn_1_6B94(ModelData *model, ParticleData *particle, Mtx mtx);
void fn_1_6D64(s32 arg0, u32 arg1, float arg8, float arg9, float argA);

omObjData *lbl_1_bss_878;
UnkM417Struct4 lbl_1_bss_178;
UnkM417Struct2 lbl_1_bss_68[17];
AnimData *lbl_1_bss_64;
AnimData *lbl_1_bss_60;
AnimData *lbl_1_bss_5C;
s16 lbl_1_bss_58;
char lbl_1_bss_28[0x30]; // unused, might be in main.c

void fn_1_3274(Process *arg0)
{
    omObjData *var_r31;
    s32 var_r30;

    lbl_1_bss_64 = HuSprAnimRead(HuDataReadNum(3145742, MEMORY_DEFAULT_NUM));
    lbl_1_bss_60 = HuSprAnimRead(HuDataReadNum(3145744, MEMORY_DEFAULT_NUM));
    lbl_1_bss_5C = HuSprAnimRead(HuDataReadNum(3145743, MEMORY_DEFAULT_NUM));
    var_r31 = omAddObjEx(arg0, 30, 9, 0, -1, fn_1_3400);
    var_r31->work[0] = 0;
    var_r31 = lbl_1_bss_878 = omAddObjEx(arg0, 31, 5, 0, -1, fn_1_3BC4);
    var_r31->work[0] = 0;
    for (var_r30 = 0; var_r30 < 16; var_r30++) {
        lbl_1_bss_68[var_r30].unk_00 = -1;
    }
    lbl_1_bss_68[var_r30].unk_00 = -2;
}

void fn_1_33B4(void)
{
    HuSprAnimKill(lbl_1_bss_64);
    HuSprAnimKill(lbl_1_bss_60);
    HuSprAnimKill(lbl_1_bss_5C);
}

void fn_1_3400(omObjData *object)
{
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M417, 0));
    Hu3DModelLayerSet(object->model[0], 0);
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M417, 4));
    Hu3DModelLayerSet(object->model[3], 3);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M417, 2));
    Hu3DModelLayerSet(object->model[2], 5);
    Hu3DModelAttrSet(object->model[2], 0x40000001);
    Hu3DMotionSpeedSet(object->model[2], 0.7f);
    object->data = fn_1_3574(object, 5, 3);
    HuAudFXPlay(1480);
    object->func = fn_1_3534;
}

void fn_1_3534(omObjData *object)
{
    fn_1_37A0(object, object->data);
    fn_1_3B1C(object, object->data);
}

UnkM417Struct3 *fn_1_3574(omObjData *arg0, s16 arg1, s16 arg2)
{
    float var_f31;
    float var_f30;
    float var_f29;

    UnkM417Struct3 *var_r31; // size 0x38
    UnkM417Struct3 *var_r30;
    s32 var_r29;

    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, arg2 * sizeof(UnkM417Struct3), MEMORY_DEFAULT_NUM);
    memset(var_r30, 0, arg2 * sizeof(UnkM417Struct3));
    var_f31 = -200.0f;
    var_r31 = var_r30;
    for (var_r29 = 0; var_r29 < arg2; var_r29++, var_r31++, arg1++) {
        var_r31->unk_00 = arg1;
        arg0->model[arg1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M417, 3), MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelLayerSet(arg0->model[var_r31->unk_00], 0);
        var_f30 = frandmod(360);
        var_f29 = frandmod(640);
        var_r31->unk_08.x = var_f29 * sind(var_f30);
        var_r31->unk_08.y = var_f31;
        var_r31->unk_08.z = var_f29 * cosd(var_f30);
        var_r31->unk_28 = frandmod(360);
        var_r31->unk_30 = 1.0f;
        var_r31->unk_34 = 0.0f;
        var_f31 -= 80.0f;
        var_r31->unk_06 = arg2;
    }
    return var_r30;
}

void fn_1_37A0(omObjData *object, UnkM417Struct3 *arg1)
{
    Vec sp8;

    float var_f31;
    float var_f30;

    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = arg1->unk_06;
    for (var_r30 = 0; var_r30 < var_r28; var_r30++, arg1++) {
        var_r29 = 0;
        if (arg1->unk_30 > arg1->unk_34) {
            var_r29 = 1;
        } else {
            VECSubtract(&arg1->unk_14, &arg1->unk_08, &sp8);
            var_f31 = VECMag(&sp8);
            if (var_f31 < 50.0f) {
                var_r29 = 1;
            }
        }
        if (var_r29) {
            var_f31 = frandmod(360);
            var_f30 = 200.0f + frandmod(550);
            arg1->unk_14.x = var_f30 * sind(var_f31);
            arg1->unk_14.z = var_f30 * cosd(var_f31);
            arg1->unk_14.y = arg1->unk_08.y;
            arg1->unk_30 = 0.0f;
            arg1->unk_34 = 200.0f + frandmod(600);
            arg1->unk_24 = 0.0f;
        }
        VECSubtract(&arg1->unk_14, &arg1->unk_08, &sp8);
        arg1->unk_2C = atan2d(sp8.x, sp8.z);
        arg1->unk_28 = fn_1_2F08(arg1->unk_28, arg1->unk_2C, 0.05f);
        arg1->unk_24 += (0.05f * (300.0f - arg1->unk_24));
        arg1->unk_20 += (0.2f * (arg1->unk_24 - arg1->unk_20));
        arg1->unk_08.x += (((1.0f / 60.0f) * arg1->unk_20) * sind(arg1->unk_28));
        arg1->unk_08.z += (((1.0f / 60.0f) * arg1->unk_20) * cosd(arg1->unk_28));
        arg1->unk_30 += (1.0f / 60.0f) * arg1->unk_20;
    }
}

void fn_1_3B1C(omObjData *object, UnkM417Struct3 *arg1)
{
    s32 var_r30;
    s32 var_r28;

    var_r28 = arg1->unk_06;
    for (var_r30 = 0; var_r30 < var_r28; var_r30++, arg1++) {
        Hu3DModelPosSetV(object->model[arg1->unk_00], &arg1->unk_08);
        Hu3DModelRotSet(object->model[arg1->unk_00], 0.0f, arg1->unk_28, 0.0f);
    }
}

void fn_1_3BC4(omObjData *object)
{
    s16 var_r30;

    omSetTra(object, 0.0f, 0.0f, 0.0f);
    object->model[0] = Hu3DHookFuncCreate(fn_1_604C);
    Hu3DModelLayerSet(object->model[0], 2);
    object->model[1] = Hu3DHookFuncCreate(fn_1_6B04);
    Hu3DModelLayerSet(object->model[1], 1);
    object->model[2] = Hu3DHookFuncCreate(fn_1_6B60);
    Hu3DModelLayerSet(object->model[2], 7);
    var_r30 = Hu3DParticleCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M417, 17), MEMORY_DEFAULT_NUM, HEAP_DATA)), 512);
    object->model[3] = var_r30;
    Hu3DModelLayerSet(var_r30, 4);
    Hu3DParticleColSet(var_r30, 255, 255, 255);
    Hu3DParticleHookSet(var_r30, fn_1_6B94);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_00 = 0;
    lbl_1_bss_58 = var_r30;
    fn_1_3D58(object);
    object->func = fn_1_3D54;
}

void fn_1_3D54(omObjData *object) { }

void fn_1_3D58(omObjData *object)
{
    Vec spC;
    float sp8;

    float var_f31;
    float var_f29;
    float var_f28;
    float var_f27;

    s32 var_r31;
    s32 var_r30;
    Vec *var_r28;
    s32 var_r29;
    u16(*var_r27)[4];
    s32 var_r26;

    Vec sp3C[3] = { { 0.0f, 0.0f, 700.0f }, { -609.0f, 0.0f, -350.0f }, { 609.0f, 0.0f, -350.0f } };
    Vec sp18[3] = { { 0.006f, -0.013333335f, 10.8f }, { 0.0045f, -0.010000001f, 9.6f }, { 0.0033f, -0.0066666673f, 12.0f } };

    lbl_1_bss_178.unk_00 = 0.0f;
    lbl_1_bss_178.unk_04 = 0.0f;
    lbl_1_bss_178.unk_08 = 0.0f;
    lbl_1_bss_178.unk_0C.x = 0.0f;
    lbl_1_bss_178.unk_0C.y = 1.0f;
    lbl_1_bss_178.unk_0C.z = 0.0f;
    lbl_1_bss_178.unk_20 = HuMemDirectMallocNum(HEAP_SYSTEM, 30 * 36 * sizeof(float), MEMORY_DEFAULT_NUM);
    lbl_1_bss_178.unk_28 = HuMemDirectMallocNum(HEAP_SYSTEM, 1080 * sizeof(s32), MEMORY_DEFAULT_NUM);
    lbl_1_bss_178.unk_24 = HuMemDirectMallocNum(HEAP_SYSTEM, 1080 * sizeof(float), MEMORY_DEFAULT_NUM);
    lbl_1_bss_178.unk_1C = HuMemDirectMallocNum(HEAP_SYSTEM, 1080 * sizeof(s16), MEMORY_DEFAULT_NUM);
    lbl_1_bss_178.unk_2C = HuMemDirectMallocNum(HEAP_SYSTEM, 30 * 36 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    lbl_1_bss_178.unk_30 = HuMemDirectMallocNum(HEAP_SYSTEM, 30 * 36 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    lbl_1_bss_178.unk_34 = HuMemDirectMallocNum(HEAP_SYSTEM, 30 * 36 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    lbl_1_bss_178.unk_38 = HuMemDirectMallocNum(HEAP_SYSTEM, 8120, MEMORY_DEFAULT_NUM);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_178.unk_3C[var_r31].unk_20 = HuMemDirectMallocNum(HEAP_SYSTEM, 4320, MEMORY_DEFAULT_NUM);
        lbl_1_bss_178.unk_3C[var_r31].unk_24 = HuMemDirectMallocNum(HEAP_SYSTEM, 2160, MEMORY_DEFAULT_NUM);
    }
    lbl_1_bss_178.unk_6B4 = 0;
    lbl_1_bss_178.unk_6DC = 19296;
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_178.unk_6BC[var_r31] = HuMemDirectMallocNum(HEAP_SYSTEM, 30 * 36 * sizeof(Vec), MEMORY_DEFAULT_NUM);
        lbl_1_bss_178.unk_6C4[var_r31] = HuMemDirectMallocNum(HEAP_SYSTEM, 30 * 36 * sizeof(Vec), MEMORY_DEFAULT_NUM);
        lbl_1_bss_178.unk_6CC[var_r31] = HuMemDirectMallocNum(HEAP_SYSTEM, 1080 * sizeof(GXColor), MEMORY_DEFAULT_NUM);
        lbl_1_bss_178.unk_6D4[var_r31] = HuMemDirectMallocNum(HEAP_SYSTEM, 30 * 36 * sizeof(Vec2f), MEMORY_DEFAULT_NUM);
        lbl_1_bss_178.unk_6E0[var_r31] = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_178.unk_6DC, MEMORY_DEFAULT_NUM);
        DCFlushRange(lbl_1_bss_178.unk_6E0[var_r31], lbl_1_bss_178.unk_6DC);
        lbl_1_bss_178.unk_6E8[var_r31] = 0;
    }
    lbl_1_bss_178.unk_6F0 = GXGetTexBufferSize(640, 480, 5, GX_FALSE, 0);
    lbl_1_bss_178.unk_6F4 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_178.unk_6F0, MEMORY_DEFAULT_NUM);
    DCFlushRange(lbl_1_bss_178.unk_6F4, lbl_1_bss_178.unk_6F0);
    lbl_1_bss_178.unk_6B8 = 30.0f;
    var_r28 = lbl_1_bss_178.unk_2C;
    var_f31 = 0.0f;
    var_f29 = -900.0f;
    var_f28 = 60.0f;
    for (var_r31 = 0; var_r31 < 36; var_r31++) {
        var_f31 = 26.666666f - var_f31;
        for (var_r30 = 0; var_r30 < 30; var_r28++, var_r30++) {
            var_r28->x = var_f31 + ((var_r30 * var_f28) - 900.0f);
            var_r28->y = 0.0f;
            var_r28->z = var_f29;
        }
        var_f29 += (var_f28 * sin(1.0471975511965976));
    }
    var_r28 = lbl_1_bss_178.unk_2C;
    var_r30 = 0;
    var_r29 = 1080;
    for (var_r31 = 0; var_r31 < 1080; var_r31++, var_r28++) {
        var_f31 = VECMag(var_r28);
        if (var_f31 > 850.0f) {
            var_r29--;
            lbl_1_bss_178.unk_28[var_r31] = 0;
            lbl_1_bss_178.unk_1C[var_r31] = var_r29;
            lbl_1_bss_178.unk_24[var_r29] = 0.0f;
            var_f31 = 850.0f / var_f31;
            VECScale(var_r28, var_r28, var_f31);
        } else {
            lbl_1_bss_178.unk_28[var_r31] = 1;
            lbl_1_bss_178.unk_1C[var_r31] = var_r30;
            lbl_1_bss_178.unk_24[var_r30] = 1.0f;
            var_f31 = 750.0f - var_f31;
            if (var_f31 < 100.0f) {
                var_f31 *= 0.01f;
                lbl_1_bss_178.unk_24[var_r30] = sqrtf(var_f31);
            }
            var_r30++;
        }
    }
    lbl_1_bss_178.unk_18 = var_r30;
    var_r28 = HuMemDirectMallocNum(HEAP_SYSTEM, 30 * 36 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    for (var_r31 = 0; var_r31 < 30 * 36; var_r31++) {
        var_r28[lbl_1_bss_178.unk_1C[var_r31]] = lbl_1_bss_178.unk_2C[var_r31];
    }
    HuMemDirectFree(lbl_1_bss_178.unk_2C);
    lbl_1_bss_178.unk_2C = var_r28;
    memset(lbl_1_bss_178.unk_30, 0, 30 * 36 * sizeof(Vec));
    var_r27 = lbl_1_bss_178.unk_38;
    for (var_r31 = 0; var_r31 < 35; var_r31++) {
        for (var_r30 = 0; var_r30 < 29; var_r27++, var_r30++) {
            if ((var_r31 & 1) == 0) {
                var_r29 = var_r30 + (var_r31 * 30);
                (*var_r27)[0] = lbl_1_bss_178.unk_1C[var_r29];
                (*var_r27)[1] = lbl_1_bss_178.unk_1C[var_r29 + 30];
                (*var_r27)[2] = lbl_1_bss_178.unk_1C[var_r29 + 1];
                (*var_r27)[3] = lbl_1_bss_178.unk_1C[var_r29 + 31];
            } else {
                var_r29 = var_r30 + (var_r31 * 30);
                (*var_r27)[1] = lbl_1_bss_178.unk_1C[var_r29];
                (*var_r27)[3] = lbl_1_bss_178.unk_1C[var_r29 + 30];
                (*var_r27)[0] = lbl_1_bss_178.unk_1C[var_r29 + 1];
                (*var_r27)[2] = lbl_1_bss_178.unk_1C[var_r29 + 31];
            }
            var_r31 == 1;
        }
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_178.unk_3C[var_r31].unk_00 = sp3C[var_r31];
        lbl_1_bss_178.unk_3C[var_r31].unk_0C = 0.0f;
        lbl_1_bss_178.unk_3C[var_r31].unk_10 = 360.0f * sp18[var_r31].x;
        lbl_1_bss_178.unk_3C[var_r31].unk_18 = 360.0f * sp18[var_r31].y;
        lbl_1_bss_178.unk_3C[var_r31].unk_14 = sp18[var_r31].z;
        var_r29 = -1;
        var_f28 = 500000.0f;
        var_r28 = lbl_1_bss_178.unk_2C;
        for (var_r30 = 0; var_r30 < lbl_1_bss_178.unk_18; var_r30++) {
            VECSubtract(var_r28++, &lbl_1_bss_178.unk_3C[var_r31].unk_00, &spC);
            var_f31 = VECMag(&spC);
            if (var_f31 < var_f28) {
                var_r29 = var_r30;
                var_f28 = var_f31;
            }
        }
        lbl_1_bss_178.unk_3C[var_r31].unk_00 = lbl_1_bss_178.unk_2C[var_r29];
        var_r28 = lbl_1_bss_178.unk_2C;
        var_r26 = 0;
        for (var_r30 = 0; var_r30 < lbl_1_bss_178.unk_18; var_r30++) {
            VECSubtract(var_r28++, &lbl_1_bss_178.unk_3C[var_r31].unk_00, &spC);
            var_f31 = lbl_1_bss_178.unk_3C[var_r31].unk_10 * VECMag(&spC);
            lbl_1_bss_178.unk_3C[var_r31].unk_20[var_r26] = var_f31;
            for (var_r29 = 0; var_r29 <= var_r26; var_r29++) {
                var_f29 = lbl_1_bss_178.unk_3C[var_r31].unk_20[var_r29] - var_f31;
                if (fabs(var_f29) < 5.0) {
                    if (var_r29 == var_r26) {
                        var_r26++;
                    }
                    break;
                }
            }
            lbl_1_bss_178.unk_3C[var_r31].unk_24[var_r30] = var_r29;
        }
        lbl_1_bss_178.unk_3C[var_r31].unk_1C = var_r26;
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        memcpy(lbl_1_bss_178.unk_6BC[var_r31], lbl_1_bss_178.unk_2C, 12960);
        for (var_r30 = 0; var_r30 < 1080; var_r30++) {
            lbl_1_bss_178.unk_6CC[var_r31][var_r30].r = 240;
            lbl_1_bss_178.unk_6CC[var_r31][var_r30].g = 250;
            lbl_1_bss_178.unk_6CC[var_r31][var_r30].b = 255;
            lbl_1_bss_178.unk_6CC[var_r31][var_r30].a = 192;
        }
        for (var_r26 = 0, var_r30 = 0; var_r30 < 36; var_r30++) {
            for (var_r29 = 0; var_r29 < 30; var_r29++) {
                var_r26 = lbl_1_bss_178.unk_1C[var_r29 + (var_r30 * 30)];
                lbl_1_bss_178.unk_6D4[var_r31][var_r26].x = 0.000625f * lbl_1_bss_178.unk_2C[var_r26].x;
                lbl_1_bss_178.unk_6D4[var_r31][var_r26].y = 0.000625f * lbl_1_bss_178.unk_2C[var_r26].z;
                lbl_1_bss_178.unk_6D4[var_r31][var_r26].x *= 3.0f;
                lbl_1_bss_178.unk_6D4[var_r31][var_r26].y *= 3.0f;
            }
        }
    }
    fn_1_57B0(object);
    fn_1_5E3C(object);
}

void fn_1_4BC8(float arg8, float arg9)
{
    float var_f30;
    float var_f28;

    UnkM417Struct6 *var_r31;
    s32 var_r30;

    if (arg9 < 0.0f) {
        arg9 = 0.0f;
    } else if (arg9 > 1.0f) {
        arg9 = 1.0f;
    }
    var_f30 = 1.0f - arg9;
    var_f28 = var_f30;
    arg9 = 0.5f + (0.5f * arg9);
    var_f30 = 0.5f + (0.5f * var_f30);
    var_r31 = &lbl_1_bss_178.unk_B4[0];

    for (var_r30 = 0; var_r30 < 16; var_r30++, var_r31++) {
        if (!var_r31->unk_00) {
            var_r31->unk_00 = 1;
            var_r31->unk_04.x = 700.0 * sind(180.0f + arg8);
            var_r31->unk_04.y = 0.0f;
            var_r31->unk_04.z = 700.0 * cosd(180.0f + arg8);
            var_r31->unk_10 = arg8;
            var_r31->unk_14 = 520.0f + (80.0f * var_f28);
            var_r31->unk_14 *= 1.0f / 60.0f;
            var_r31->unk_18 = 800.0f * arg9;
            var_r31->unk_1C = 0.05f;
            var_r31->unk_20 = arg9;
            var_r31->unk_24 = 0.0f;
            var_r31->unk_28 = 0.2f + (0.2f * var_f30);
            var_r31->unk_2C = HuAudFXEmiterPlay(1484, &var_r31->unk_04);
            return;
        }
    }
	(void)var_r31;
}

void fn_1_4E64(omObjData *object)
{
    Mtx spC8;
    Mtx sp98;
    Mtx sp68;
    ROMtx sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    UnkM417Struct6 *var_r31;
    u32 var_r30;
    UnkM417Struct2 *var_r29;
    GXColor *var_r28;
    Vec *var_r27;
    Vec *var_r26;
    s32 var_r25;

    Vec sp8 = { 0.0f, 0.0f, 0.0f };
    var_r28 = lbl_1_bss_178.unk_6CC[lbl_1_bss_178.unk_6B4];
    for (var_r30 = 0; var_r30 < lbl_1_bss_178.unk_18; var_r30++) {
        var_r28[var_r30].a += -(float)(var_r28[var_r30].a) * 0.15f;
    }
    var_r29 = &lbl_1_bss_68[0]; // looks like fn_1_7A28 but it doesn't get inlined
    var_r31 = &lbl_1_bss_178.unk_B4[0];

    for (var_r25 = 0; var_r25 < 16; var_r25++, var_r31++, var_r29++) {
        var_r29->unk_00 = -1;
        if (var_r31->unk_00 != 0) {
            sp14.x = var_r31->unk_14 * sind(var_r31->unk_10);
            sp14.y = 0.0f;
            sp14.z = var_r31->unk_14 * cosd(var_r31->unk_10);
            VECAdd(&var_r31->unk_04, &sp14, &var_r31->unk_04);
            if (var_r31->unk_2C >= 0) {
                HuAudFXEmiterUpDate(var_r31->unk_2C, &var_r31->unk_04);
            }
            if (VECMag(&var_r31->unk_04) > 800.0f && var_r31->unk_00 >= 2 && (var_r31->unk_1C -= 0.033333335f, var_r31->unk_1C < 0.0f)) {
                var_r31->unk_00 = 0;
            } else {
                if (var_r31->unk_00 < 2) {
                    VECSubtract(&sp8, &var_r31->unk_04, &sp20);
                    if (VECDotProduct(&sp14, &sp20) <= 0.0f) {
                        var_r31->unk_00 = 2;
                    } else {
                        var_f31 = 1.2f * (VECMag(&sp20) / (var_r31->unk_18 * var_r31->unk_28));
                        if (var_f31 < 1.2f) {
                            if (var_f31 > 1.0f) {
                                var_f31 = 5.0f * (1.2f - var_f31);
                            }
                            var_r29->unk_00 = var_r25;
                            var_r29->unk_08 = var_r31->unk_20;
                            var_r29->unk_04 = var_r31->unk_10;
                            var_r29->unk_0C = var_f31;
                        }
                    }
                } else if (var_r31->unk_00 == 2 && VECMag(&var_r31->unk_04) > ((800.0f - (100.0f * (2.0f * var_r31->unk_20))) - 30.000002f)) {
                    var_r31->unk_00 = 3;
                    fn_1_6D64(lbl_1_bss_58, 0, var_r31->unk_10, 20.0f + (40.0f * var_r31->unk_20), var_r31->unk_20);
                    sp2C.x = sind(var_r31->unk_10);
                    sp2C.y = 0.0f;
                    sp2C.z = cosd(var_r31->unk_10);
                    VECScale(&sp2C, &sp2C, 800.0f);
                    HuAudFXEmiterPlay(1481, &sp2C);
                    if (var_r31->unk_2C >= 0) {
                        var_r31->unk_2C = -1;
                    }
                }
                var_r31->unk_1C += 0.016666668f;
                if (var_r31->unk_1C > 1.0f) {
                    var_r31->unk_1C = 1.0f;
                }
                if (var_r31->unk_00 >= 2) {
                    var_r31->unk_24 += 0.016666668f;
                    if (var_r31->unk_24 > 1.0f) {
                        var_r31->unk_24 = 1.0f;
                    }
                }
                PSMTXTrans(spC8, var_r31->unk_04.x, var_r31->unk_04.y, var_r31->unk_04.z);
                MTXRotDeg(sp98, 89, var_r31->unk_10);
                PSMTXConcat(spC8, sp98, sp68);
                var_f31 = var_r31->unk_18 * var_r31->unk_1C;
                PSMTXScale(spC8, var_f31, var_f31, var_f31 * var_r31->unk_28);
                PSMTXConcat(sp68, spC8, sp98);
                PSMTXInverse(sp98, spC8);
                PSMTXReorder(spC8, sp38);
                PSMTXROMultVecArray(sp38, lbl_1_bss_178.unk_2C, lbl_1_bss_178.unk_34, lbl_1_bss_178.unk_18);
                sp2C.x = (0.15f * var_r31->unk_18) * (var_r31->unk_24 * sind(var_r31->unk_10));
                sp2C.y = 0.0f;
                sp2C.z = (0.15f * var_r31->unk_18) * (var_r31->unk_24 * cosd(var_r31->unk_10));
                var_f29 = 255.0f;
                var_r26 = lbl_1_bss_178.unk_34;
                var_r27 = lbl_1_bss_178.unk_30;
                var_r28 = lbl_1_bss_178.unk_6CC[lbl_1_bss_178.unk_6B4];
                for (var_r30 = 0; var_r30 < lbl_1_bss_178.unk_18; var_r30++, var_r26++, var_r27++) {
                    var_f31 = VECMag(var_r26);
                    if (!(var_f31 >= 1.0f)) {
                        var_f30 = (1.0f - var_f31) * var_r31->unk_1C;
                        var_f28 = var_r31->unk_24 * ((1.0f - var_f31) * (1.0f - var_f31));
                        var_f27 = ((1.0f - var_f31) * (1.0f - (var_f31 * var_f31))) + (var_f31 * ((1.0f - var_f31) * (1.0f - var_f31)));
                        var_r27->x += lbl_1_bss_178.unk_24[var_r30] * (sp2C.x * var_f30);
                        var_r27->y += lbl_1_bss_178.unk_24[var_r30]
                            * (((sp2C.y * var_f30) + (var_r31->unk_1C * (0.3f * var_r31->unk_18 * var_f27))) - (0.3f * var_r31->unk_18 * var_f28));
                        var_r27->z += lbl_1_bss_178.unk_24[var_r30] * (sp2C.z * var_f30);
                        if (var_r26->z >= -0.2f) {
                            var_f31 = var_r28[var_r30].a + (var_f29 * (1.0f - (var_f31 * (var_f31 * var_f31))));
                            if (var_f31 > var_f29) {
                                var_f31 = var_f29;
                            }
                            var_r28[var_r30].a = var_f31;
                        }
                    }
                }
            }
        }
    }
    var_r29->unk_00 = -2;
}

void fn_1_57B0(omObjData *object)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;

    float var_f31;

    u16(*var_r31)[4];
    s32 var_r30;
    UnkM417Struct5 *var_r29;
    Vec *var_r28;
    Vec *var_r27;
    u32 var_r26;
    Vec *var_r25;
    Vec *var_r24;
    Vec *var_r23;

    lbl_1_bss_178.unk_6B4 = 1 - lbl_1_bss_178.unk_6B4;
    fn_1_4E64(object);
    lbl_1_bss_178.unk_6B8 += 0.083333336f;
    if (lbl_1_bss_178.unk_6B8 >= 360.0f) {
        lbl_1_bss_178.unk_6B8 -= 360.0f;
    }
    var_r29 = lbl_1_bss_178.unk_3C;
    for (var_r30 = 0; var_r30 < 3; var_r30++, var_r29++) {
        var_r29->unk_0C += var_r29->unk_18;
        if (var_r29->unk_0C >= 360.0f) {
            var_r29->unk_0C -= 360.0f;
        } else if (var_r29->unk_0C < 0.0f) {
            var_r29->unk_0C += 360.0f;
        }
        var_f31 = var_r29->unk_0C;
        for (var_r26 = 0; var_r26 < var_r29->unk_1C; var_r26++) {
            lbl_1_bss_178.unk_20[var_r26] = var_r29->unk_14 * sind((var_f31 + var_r29->unk_20[var_r26]));
        }
        var_r27 = lbl_1_bss_178.unk_30;
        for (var_r26 = 0; var_r26 < lbl_1_bss_178.unk_18; var_r26++, var_r27++) {
            var_r27->y = var_r27->y + lbl_1_bss_178.unk_20[var_r29->unk_24[var_r26]];
        }
    }
    var_r23 = lbl_1_bss_178.unk_2C;
    var_r24 = lbl_1_bss_178.unk_30;
    var_r25 = lbl_1_bss_178.unk_6BC[lbl_1_bss_178.unk_6B4];
    for (var_r30 = 0; var_r30 < lbl_1_bss_178.unk_18; var_r23++, var_r24++, var_r25++, var_r30++) {
        VECAdd(var_r23, var_r24, var_r25);
    }
    memset(lbl_1_bss_178.unk_30, 0, 30 * 36 * sizeof(Vec));
    var_r28 = lbl_1_bss_178.unk_6C4[lbl_1_bss_178.unk_6B4];
    memset(var_r28, 0, 30 * 36 * sizeof(Vec));
    var_r27 = lbl_1_bss_178.unk_6BC[lbl_1_bss_178.unk_6B4];
    var_r31 = lbl_1_bss_178.unk_38;
    for (var_r30 = 0; var_r30 < 1015; var_r31++, var_r30++) {
        VECSubtract(&var_r27[(*var_r31)[1]], &var_r27[(*var_r31)[0]], &sp30);
        VECSubtract(&var_r27[(*var_r31)[3]], &var_r27[(*var_r31)[0]], &sp24);
        VECSubtract(&var_r27[(*var_r31)[2]], &var_r27[(*var_r31)[0]], &sp18);
        VECCrossProduct(&sp30, &sp24, &spC);
        VECNormalize(&spC, &spC);
        VECAdd(&spC, &var_r28[(*var_r31)[0]], &var_r28[(*var_r31)[0]]);
        VECAdd(&spC, &var_r28[(*var_r31)[1]], &var_r28[(*var_r31)[1]]);
        VECAdd(&spC, &var_r28[(*var_r31)[3]], &var_r28[(*var_r31)[3]]);
        VECCrossProduct(&sp24, &sp18, &spC);
        VECNormalize(&spC, &spC);
        VECAdd(&spC, &var_r28[(*var_r31)[0]], &var_r28[(*var_r31)[0]]);
        VECAdd(&spC, &var_r28[(*var_r31)[3]], &var_r28[(*var_r31)[3]]);
        VECAdd(&spC, &var_r28[(*var_r31)[2]], &var_r28[(*var_r31)[2]]);
    }
    for (var_r30 = 0; var_r30 < 1080; var_r30++, var_r28++) {
        VECNormalize(var_r28, var_r28);
    }
    var_r25 = lbl_1_bss_178.unk_6BC[lbl_1_bss_178.unk_6B4];
    for (var_r30 = 0; var_r30 < lbl_1_bss_178.unk_18; var_r25++, var_r30++) {
        var_f31 = 0.5f - (0.00041666668f * var_r25->y);
        var_r25->y = 1600.0f * (0.25f - (var_f31 * var_f31));
    }
    var_r30 = lbl_1_bss_178.unk_1C[555];
    var_f31 = lbl_1_bss_178.unk_6BC[lbl_1_bss_178.unk_6B4][var_r30].y;
    lbl_1_bss_178.unk_08 = var_f31 - lbl_1_bss_178.unk_04;
    lbl_1_bss_178.unk_04 = var_f31;
    lbl_1_bss_178.unk_0C = lbl_1_bss_178.unk_6C4[lbl_1_bss_178.unk_6B4][var_r30];

    DCStoreRangeNoSync(lbl_1_bss_178.unk_6BC[lbl_1_bss_178.unk_6B4], 30 * 36 * sizeof(Vec));
    DCStoreRangeNoSync(lbl_1_bss_178.unk_6C4[lbl_1_bss_178.unk_6B4], 30 * 36 * sizeof(Vec));
    DCStoreRangeNoSync(lbl_1_bss_178.unk_6CC[lbl_1_bss_178.unk_6B4], 1080 * sizeof(GXColor));
    DCStoreRangeNoSync(lbl_1_bss_178.unk_6D4[lbl_1_bss_178.unk_6B4], 30 * 36 * sizeof(Vec2f));
    PPCSync();
	(void)var_r30;
	(void)var_r30;
}

void fn_1_5E3C(omObjData *object)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    GXBeginDisplayList(lbl_1_bss_178.unk_6E0[0], lbl_1_bss_178.unk_6DC);
    for (var_r29 = 0; var_r29 < 35; var_r29++) {
        if ((var_r29 & 1) == 0) {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 60);
            for (var_r30 = 0; var_r30 < 30; var_r30++) {
                var_r31 = lbl_1_bss_178.unk_1C[var_r30 + ((var_r29 + 1) * 30)];
                GXPosition1x16(var_r31);
                GXNormal1x16(var_r31);
                GXColor1x16(var_r31);
                GXTexCoord1x16(var_r31);
                var_r31 = lbl_1_bss_178.unk_1C[var_r30 + (var_r29 * 30)];
                GXPosition1x16(var_r31);
                GXNormal1x16(var_r31);
                GXColor1x16(var_r31);
                GXTexCoord1x16(var_r31);
            }
        } else {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 59);
            for (var_r30 = 29; var_r30 >= 0; var_r30--) {
                var_r31 = lbl_1_bss_178.unk_1C[var_r30 + (var_r29 * 30)];
                GXPosition1x16(var_r31);
                GXNormal1x16(var_r31);
                GXColor1x16(var_r31);
                GXTexCoord1x16(var_r31);
                if (!var_r30) {
                    break;
                }
                var_r31 = lbl_1_bss_178.unk_1C[((var_r29 + 1) * 30) + var_r30 - 1];
                GXPosition1x16(var_r31);
                GXNormal1x16(var_r31);
                GXColor1x16(var_r31);
                GXTexCoord1x16(var_r31);
            }
        }
    }
    lbl_1_bss_178.unk_6E8[0] = GXEndDisplayList();
}

void fn_1_604C(ModelData *arg0, Mtx arg1)
{
    Mtx sp98;
    Mtx sp68;
    Mtx sp38;
    GXTexObj sp18;

    GXColor *var_r30;
    GXColor *var_r29;

    GXColor sp14 = { 0xD8, 0xE2, 0xE5, 0x4C };
    GXColor sp10 = { 0xE0, 0xD8, 0xF4, 0x40 };
    DCStoreRangeNoSync(&sp14, 4);
    DCStoreRangeNoSync(&sp10, 4);
    PPCSync();
    GXLoadPosMtxImm(arg1, 0);
    PSMTXInvXpose(arg1, sp98);
    GXLoadNrmMtxImm(sp98, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXInitTexObj(&sp18, lbl_1_bss_178.unk_6F4, 640, 480, 5, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sp18, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sp18, GX_TEXMAP0);
    HuSprTexLoad(lbl_1_bss_64, 0, 1, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_5C, 0, 2, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_60, 0, 3, GX_MIRROR, GX_MIRROR, GX_LINEAR);
    GXSetNumTexGens(5);
    C_MTXLightPerspective(sp38, 35.0f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    PSMTXInverse(Hu3DCameraMtx, sp98);
    PSMTXConcat(sp98, arg1, sp98);
    PSMTXConcat(sp38, Hu3DCameraMtx, sp68);
    PSMTXConcat(sp68, sp98, sp68);
    sp68[1][3] -= 44.0f;
    GXLoadTexMtxImm(sp68, 30, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, 30, GX_FALSE, 125);
    C_MTXLightPerspective(sp38, 70.0f, 1.0f, 0.5f, -0.5f, 0.5f, 0.5f);
    PSMTXInverse(Hu3DCameraMtx, sp98);
    PSMTXConcat(sp98, arg1, sp98);
    PSMTXConcat(sp38, Hu3DCameraMtx, sp68);
    PSMTXConcat(sp68, sp98, sp68);
    GXLoadTexMtxImm(sp68, 36, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX3x4, GX_TG_POS, 36, GX_FALSE, 125);
    MTXRotDeg(sp68, 90, lbl_1_bss_178.unk_6B8);
    GXLoadTexMtxImm(sp68, 39, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEXCOORD0, 39, GX_FALSE, 125);
    PSMTXScale(sp98, 1.2f, -1.2f, 1.2f);
    PSMTXConcat(sp68, sp98, sp68);
    GXLoadTexMtxImm(sp68, 42, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEXCOORD0, 42, GX_FALSE, 125);
    PSMTXScale(sp98, 0.49f, -0.49f, 0.49f);
    PSMTXConcat(sp98, Hu3DCameraMtx, sp68);
    sp68[0][3] = 0.5f;
    sp68[1][3] = 0.5f;
    GXLoadTexMtxImm(sp68, 33, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_NRM, 33, GX_FALSE, 125);
    GXSetNumIndStages(3);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    PSMTXScale(sp68, -0.5f, -0.5f, 0.5f);
    GXSetIndTexMtx(GX_ITM_0, (float(*)[3])sp68, -2);
    GXSetIndTexOrder(GX_INDTEXSTAGE1, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE1, GX_INDTEXSTAGE1, GX_TRUE, GX_FALSE, GX_ITM_1);
    PSMTXScale(sp68, 0.5f, 0.5f, 0.5f);
    GXSetIndTexMtx(GX_ITM_1, (float(*)[3])sp68, 0);
    GXSetIndTexOrder(GX_INDTEXSTAGE2, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE2, GX_INDTEXSTAGE2, GX_TRUE, GX_FALSE, GX_ITM_2);
    GXSetTevIndWarp(GX_TEVSTAGE3, GX_INDTEXSTAGE2, GX_TRUE, GX_FALSE, GX_ITM_2);
    PSMTXScale(sp68, -0.65f, -0.65f, 0.65f);
    GXSetIndTexMtx(GX_ITM_2, (float(*)[3])sp68, -3);
    GXSetNumTevStages(5);
    GXSetTevColor(GX_TEVREG0, sp14);
    GXSetTevColor(GX_TEVREG1, sp10);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD3, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD4, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
    GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE4, GX_CC_CPREV, GX_CC_C1, GX_CC_C2, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE4, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE4, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE4, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_POS, lbl_1_bss_178.unk_6BC[lbl_1_bss_178.unk_6B4], 12);
    GXSetArray(GX_VA_NRM, lbl_1_bss_178.unk_6C4[lbl_1_bss_178.unk_6B4], 12);
    GXSetArray(GX_VA_CLR0, lbl_1_bss_178.unk_6CC[lbl_1_bss_178.unk_6B4], 4);
    GXSetArray(GX_VA_TEX0, lbl_1_bss_178.unk_6D4[lbl_1_bss_178.unk_6B4], 8);
    GXCallDisplayList(lbl_1_bss_178.unk_6E0[0], lbl_1_bss_178.unk_6E8[0]);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTevDirect(GX_TEVSTAGE3);
}

void fn_1_6B04(ModelData *model, Mtx arg1)
{
    GXSetTexCopySrc(0, 0, 640, 480);
    GXSetTexCopyDst(640, 480, GX_TF_RGB5A3, GX_FALSE);
    GXCopyTex(lbl_1_bss_178.unk_6F4, GX_FALSE);
    GXPixModeSync();
}

void fn_1_6B60(ModelData *model, Mtx arg1)
{
    if (!omPauseChk()) {
        fn_1_57B0(NULL);
    }
}

void fn_1_6B94(ModelData *model, ParticleData *particle, float (*matrix)[4])
{
    HsfanimStruct01 *var_r31;
    s32 var_r29;

    if (!particle->unk_00) {
        particle->unk_00++;
        var_r31 = particle->unk_48;
        for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            var_r31->unk00_s16 = 0;
            var_r31->unk2C = 0.0f;
            var_r31->unk40.a = 0;
        }
        return;
    }
    var_r31 = particle->unk_48;
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00_s16) {
            var_r31->unk34.x += var_r31->unk08.x;
            var_r31->unk34.y += var_r31->unk08.y;
            var_r31->unk34.z += var_r31->unk08.z;
            var_r31->unk08.y += -0.27222225f;
            if (var_r31->unk00_s16 < 12.0f) {
                var_r31->unk40.a = 0.88f * var_r31->unk40.a;
            }
            if (!(--var_r31->unk00_s16)) {
                var_r31->unk00_s16 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * 68);
}

void fn_1_6D64(s32 arg0, u32 arg1, float arg8, float arg9, float argA)
{
    Vec sp14;

    float var_f31;
    float var_f30;
    float var_f28;
    float var_f27;

    HsfanimStruct01 *var_r31;
    ParticleData *var_r30;
    s32 var_r29;
    u32 var_r28;

    var_r30 = Hu3DData[arg0].unk_120;
    {
        float spC[2] = { 800.0f, 150.0f };
        if (!var_r30->unk_00) {
            return;
        }
        var_r31 = var_r30->unk_48;
        if (arg1) {
            var_r28 = 10.0f + (20.0f * argA);
            argA *= 0.7f;
            arg8 += 180.0f;
            arg9 = 60.0f;
            var_f27 = fn_1_75BC();
        } else {
            var_r28 = 20.0f + (80.0f * argA);
            var_f27 = 0.0f;
        }
        for (var_r29 = 0; var_r29 < var_r30->unk_30; var_r29++, var_r31++) {
            if (var_r31->unk00_s16) {
                continue;
            }
            var_r31->unk00 = 60.0f * (1.0f + (0.0005f * frandmod(1000)));
            var_f30 = 0.001f * frandmod(1000);
            var_f28 = var_f30;
            if (frandmod(1000) < 500) {
                var_f28 *= -1.0f;
            }
            var_f30 = argA * (0.4f + (0.6f * (1.0f - (var_f30 * var_f30))));
            var_f31 = arg8 + (var_f28 * arg9);
            sp14.x = sind(var_f31);
            sp14.y = 0.0f;
            sp14.z = cosd(var_f31);
            var_r31->unk34.x = sp14.x * spC[arg1];
            var_r31->unk34.y = (var_f27 + (0.15f * frandmod(1000))) - 100.0f;
            var_r31->unk34.z = sp14.z * spC[arg1];
            var_r31->unk08.x = 0.016666668f * (((100.0f * (1.5f * sp14.x)) + (0.1f * frandmod(1000))) - 50.0f);
            var_r31->unk08.y = 0.016666668f * (450.0f + (0.5f * frandmod(1000)));
            var_r31->unk08.z = 0.016666668f * (((100.0f * (1.5f * sp14.z)) + (0.1f * frandmod(1000))) - 50.0f);
            var_r31->unk08.x *= var_f30;
            var_r31->unk08.y *= 0.2f + (0.8f * var_f30);
            var_r31->unk08.z *= var_f30;
            var_r31->unk30 = frandmod(360);
            var_f31 = 0.001f * frandmod(1000);
            if (arg1) {
                var_r31->unk2C = 50.0f + frandmod(50);
                var_r31->unk40.a = frandmod(80) + 60;
                var_r31->unk40.r = 200.0f + (55.0f * var_f31);
                var_r31->unk40.g = 220.0f + (20.0f * var_f31);
                var_r31->unk40.b = 245.0f + (10.0f * var_f31);
            } else {
                var_r31->unk2C = 100.0f + frandmod(100);
                var_r31->unk40.a = frandmod(100) + 80;
                var_r31->unk40.r = 200.0f + (55.0f * var_f31);
                var_r31->unk40.g = 220.0f + (20.0f * var_f31);
                var_r31->unk40.b = 245.0f + (10.0f * var_f31);
            }
            var_r28--;
            if (!var_r28) {
                break;
            }
        }
    }
    (void)var_r29;
}

void fn_1_7510(float arg8, float arg9, float argA, float argB)
{
    float var_f31;
    float var_f30;
    float var_f28;

    s32 var_r31;
    s32 var_r30;

    var_f31 = 180.0 + (atan2d(arg8, argA));
    if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    fn_1_4BC8(var_f31, argB);
}

float fn_1_75BC(void)
{
    return 10.0f + (lbl_1_bss_178.unk_04 + lbl_1_bss_878->trans.y);
}

float fn_1_75F0(void)
{
    return lbl_1_bss_178.unk_08;
}

void fn_1_7600(Vec *arg0)
{
    *arg0 = lbl_1_bss_178.unk_0C;
}

s32 fn_1_7624(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;
    float var_f29;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    var_f31 = lbl_1_bss_178.unk_2C[lbl_1_bss_178.unk_1C[555]].x - lbl_1_bss_178.unk_2C[lbl_1_bss_178.unk_1C[554]].x;
    var_r30 = (15.0f + (s32)(arg8 / var_f31)) - 1.0f;
    var_r28 = var_r30 + 2;
    if (var_r30 < 0) {
        var_r30 = 0;
    }
    if (var_r28 > 30) {
        var_r28 = 30;
    }
    var_f31 = lbl_1_bss_178.unk_2C[lbl_1_bss_178.unk_1C[555]].z - lbl_1_bss_178.unk_2C[lbl_1_bss_178.unk_1C[525]].z;
    var_r31 = (18.0f + (s32)(argA / var_f31)) - 1.0f;
    var_r27 = var_r31 + 2;
    if (var_r31 < 0) {
        var_r31 = 0;
    }
    if (var_r27 > 36) {
        var_r27 = 36;
    }
    var_f29 = 1e10f;
    var_r25 = -1;
    for (; var_r31 < var_r27; var_r31++) {
        for (var_r29 = var_r30; var_r29 < var_r28; var_r29++) {
            var_r26 = lbl_1_bss_178.unk_1C[var_r29 + (var_r31 * 30)];
            var_f31 = arg8 - lbl_1_bss_178.unk_2C[var_r26].x;
            var_f30 = argA - lbl_1_bss_178.unk_2C[var_r26].z;
            var_f31 = (var_f31 * var_f31) + (var_f30 * var_f30);
            if (var_f31 < var_f29) {
                var_f29 = var_f31;
                var_r25 = var_r26;
            }
        }
    }
    return var_r25;
}

float fn_1_78BC(float arg8, float arg9, float argA)
{
    s32 var_r31;

    var_r31 = fn_1_7624(arg8, arg9, argA);
    if (var_r31 < 0) {
        return 0.0f;
    }
    return 25.0f + (lbl_1_bss_878->trans.y + lbl_1_bss_178.unk_6BC[lbl_1_bss_178.unk_6B4][var_r31].y);
}

void fn_1_7968(float arg8, float arg9, float argA, Vec *arg0)
{
    s32 var_r30;

    var_r30 = fn_1_7624(arg8, arg9, argA);
    if (var_r30 < 0) {
        arg0->x = arg0->z = 0.0f;
        arg0->y = 1.0f;
    } else {
        *arg0 = lbl_1_bss_178.unk_6C4[lbl_1_bss_178.unk_6B4][var_r30];
    }
}

UnkM417Struct2 *fn_1_7A28(void)
{
    return &lbl_1_bss_68[0];
}
