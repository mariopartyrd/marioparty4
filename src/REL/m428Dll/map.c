#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXVert.h"
#include "ext_math.h"
#include "game/hsfanim.h"
#include "game/hsfformat.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"
#include "string.h"

#include "REL/m428Dll.h"

#ifndef __MWERKS__
#include "game/frand.h"
#endif

typedef struct M433DllMapWork2 {
    u8 unk_00;
    Vec unk_04;
    Vec unk_10;
    Vec unk_1C;
    Vec unk_28;
    Vec unk_34;
    Vec unk_40;
    Vec unk_4C;
    Vec unk_58;
    Vec unk_64[3];
    Vec unk_88[3];
    Vec unk_AC[3];
    Vec unk_D0[3];
    float unk_F4[3];
    float unk_100[3];
    float unk_10C[3];
    float unk_118[3];
    float unk_124[3];
    float unk_130;
    float unk_134;
    float unk_138;
    float unk_13C;
    float unk_140;
    float unk_144;
    float unk_148;
    float unk_14C[3];
    float unk_158[3];
    float unk_164[3];
    float unk_170[3];
    float unk_17C[3];
    u16 unk_188[3];
} M433DllMapWork2; /* size = 0x190 */

typedef struct M433DllUnkStruct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    float unk_08;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    char unk20[0x28];
} M433DllUnkStruct; /* size = 0x48 */

typedef struct M433DllUnkStruct4 {
    Vec unk_00;
    s32 unk_0C[3];
    s8 unk_18[4];
    s8 unk_1C;
    float unk_20;
    float unk_24;
    float unk_28;
    float unk_2C;
    float unk_30;
} M433DllUnkStruct4; /* size = 0x34 */

typedef struct M433DllUnkStruct2 {
    Vec *unk_00;
    s32 unk_04;
    s32 unk_08;
    M433DllUnkStruct4 *unk_0C;
} M433DllUnkStruct2; /* size 0x10 */

typedef struct M433DllUnkStruct3 {
    s32 unk_00;
    M433DllUnkStruct2 *unk_04;
} M433DllUnkStruct3; /* size = 0x08 */

void fn_1_4650(omObjData *object);
void fn_1_475C(omObjData *object);
void fn_1_4F04(omObjData *object);
void fn_1_51E0(omObjData *object);
u8 fn_1_5370(M433DllUnkStruct2 *arg0, Vec *arg1);
void fn_1_5558(s32 arg0, M433DllUnkStruct3 *arg1);
void fn_1_5CCC(HsfData *arg0, HsfObject *arg1);
void fn_1_6280(ModelData *arg1, ParticleData *particle, Mtx matrix);
s16 fn_1_71AC(s32 arg0, s16 arg1, ParticleHook arg2);
void fn_1_7294(void);
void *fn_1_72D4(s32 arg0);
void fn_1_739C(M433DllUnkStruct2 *arg0);
void fn_1_7430(void);
s32 fn_1_7500(void);
void fn_1_8F90(float *arg0, float *arg1, float *arg2, s32 arg3);
float fn_1_9248(float arg8, float *arg0, float *arg1, float *arg2, s32 arg3);
void fn_1_939C(float *arg0, float (*arg1)[3], float (*arg2)[3], s32 arg3);
void fn_1_977C(float arg8, float *arg0, float *arg1, float (*arg2)[3], float (*arg3)[3], s32 arg4);

M433DllUnkStruct3 *lbl_1_bss_12C;
M433DllUnkStruct2 *lbl_1_bss_128;
void *lbl_1_bss_A8[0x20];
omObjData *lbl_1_bss_A4;
omObjData *lbl_1_bss_A0;
omObjData *lbl_1_bss_98[2];
M433DllUnkStruct3 lbl_1_bss_90;

void fn_1_43C8(Process *arg0)
{
    s32 var_r31;
    omObjData *var_r30;
    s32 var_r28;

    var_r28 = frand() & 0x1F;
    for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
        fn_1_7500();
    }
    fn_1_7294();
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 7500.0f, 0.6f);
    Hu3DCameraPerspectiveSet(2, 45.0f, 100.0f, 7500.0f, 0.6f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(2, 320.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 0x140, 0x1E0);
    Hu3DCameraScissorSet(2, 0x140, 0, 0x140, 0x1E0);
    lbl_1_bss_A4 = omAddObjEx(arg0, 0x7FDA, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_A4->work[0] = 2;
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r30 = omAddObjEx(arg0, 0xFE, 1, 0, -1, fn_1_4650);
        lbl_1_bss_98[var_r31] = var_r30;
        var_r30->work[0] = var_r31;
    }
    lbl_1_bss_A0 = omAddObjEx(arg0, 0x7F, 9, 0, -1, fn_1_4F04);
}

void fn_1_4630(void)
{
    fn_1_7430();
}

void fn_1_4650(omObjData *object)
{
    M433DllMapWork2 *work;

    work = fn_1_72D4(0x190);
    object->data = work;
    work->unk_148 = work->unk_144 = 0.0f;
    work->unk_140 = 1.0f;
    work->unk_10.x = work->unk_28.x = 0.0f;
    work->unk_10.y = work->unk_28.y = 0.0f;
    work->unk_10.z = work->unk_28.z = 0.0f;
    work->unk_04.x = work->unk_1C.x = 0.0f;
    work->unk_04.y = work->unk_1C.y = 80.0f;
    work->unk_04.z = work->unk_1C.z = 0.0f;
    work->unk_130 = work->unk_134 = 600.0f;
    work->unk_188[0] = work->unk_188[1] = work->unk_188[2] = 0;
    object->func = fn_1_475C;
}

void fn_1_475C(omObjData *object)
{
    float var_f31;
    M433DllMapWork2 *work;
    s32 var_r29;

    work = object->data;
    if (work->unk_148 > 0.0f) {
        work->unk_148 = work->unk_148 - work->unk_140;
        var_f31 = (work->unk_144 - work->unk_148) / work->unk_144;
        var_f31 = sind((90.0f * var_f31));
        if (work->unk_00 == 0) {
            work->unk_04.x = work->unk_1C.x + (var_f31 * (work->unk_34.x - work->unk_1C.x));
            work->unk_04.y = work->unk_1C.y + (var_f31 * (work->unk_34.y - work->unk_1C.y));
            work->unk_04.z = work->unk_1C.z + (var_f31 * (work->unk_34.z - work->unk_1C.z));
            work->unk_10.x = work->unk_28.x + (var_f31 * (work->unk_40.x - work->unk_28.x));
            work->unk_10.y = work->unk_28.y + (var_f31 * (work->unk_40.y - work->unk_28.y));
            work->unk_10.z = work->unk_28.z + (var_f31 * (work->unk_40.z - work->unk_28.z));
            work->unk_130 = work->unk_134 + (var_f31 * (work->unk_138 - work->unk_134));
        }
        else {
            fn_1_977C(2.0f * var_f31, (float *)&work->unk_04, work->unk_F4, (float(*)[3])work->unk_64, (float(*)[3])work->unk_88, 3);
            fn_1_977C(2.0f * var_f31, (float *)&work->unk_10, work->unk_100, (float(*)[3])work->unk_AC, (float(*)[3])work->unk_D0, 3);
            work->unk_130 = fn_1_9248(2.0f * var_f31, work->unk_124, work->unk_10C, work->unk_118, 3);
        }
    }
    CRotM[object->work[0]].x = work->unk_10.x;
    CRotM[object->work[0]].y = work->unk_10.y;
    CRotM[object->work[0]].z = work->unk_10.z;
    CenterM[object->work[0]].x = work->unk_04.x;
    CenterM[object->work[0]].y = work->unk_04.y;
    CenterM[object->work[0]].z = work->unk_04.z;
    CZoomM[object->work[0]] = work->unk_130;
    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        work->unk_17C[var_r29] = 0.0f;
        if (work->unk_188[var_r29] != 0) {
            work->unk_17C[var_r29] = work->unk_14C[var_r29] * sind(work->unk_164[var_r29]);
            work->unk_164[var_r29] += work->unk_170[var_r29];
            work->unk_14C[var_r29] *= work->unk_158[var_r29];
            work->unk_188[var_r29] -= 1;
        }
    }
    CenterM[object->work[0]].x += work->unk_17C[0];
    CenterM[object->work[0]].y += work->unk_17C[1];
    CenterM[object->work[0]].z += work->unk_17C[2];
}

void fn_1_4B7C(u8 arg0, float arg1, Vec *arg2, Vec *arg3, float arg8, Vec *arg4, Vec *arg5, float arg9)
{
    float var_f31;
    float var_f30;
    M433DllMapWork2 *var_r31;

    var_r31 = lbl_1_bss_98[arg0]->data;
    var_r31->unk_00 = 1;
    var_r31->unk_148 = var_r31->unk_144 = arg1;
    var_r31->unk_1C = var_r31->unk_04;
    var_r31->unk_34.x = arg2->x;
    var_r31->unk_34.y = arg2->y;
    var_r31->unk_34.z = arg2->z;
    var_r31->unk_4C.x = arg4->x;
    var_r31->unk_4C.y = arg4->y;
    var_r31->unk_4C.z = arg4->z;
    var_r31->unk_28 = var_r31->unk_10;
    var_r31->unk_40.x = arg3->x;
    var_r31->unk_40.y = arg3->y;
    var_r31->unk_40.z = arg3->z;
    var_r31->unk_58.x = arg5->x;
    var_r31->unk_58.y = arg5->y;
    var_r31->unk_58.z = arg5->z;
    var_r31->unk_134 = var_r31->unk_130;
    var_r31->unk_138 = arg8;
    var_r31->unk_13C = arg9;
    var_r31->unk_64[0] = var_r31->unk_1C;
    var_r31->unk_64[1] = var_r31->unk_4C;
    var_r31->unk_64[2] = var_r31->unk_34;
    var_r31->unk_AC[0] = var_r31->unk_28;
    var_r31->unk_AC[1] = var_r31->unk_58;
    var_r31->unk_AC[2] = var_r31->unk_40;
    var_r31->unk_10C[0] = var_r31->unk_134;
    var_r31->unk_10C[1] = var_r31->unk_13C;
    var_r31->unk_10C[2] = var_r31->unk_138;
    var_r31->unk_124[0] = 0.0f;
    if ((var_r31->unk_10C[1] - var_r31->unk_10C[0]) < 0.0f) {
        var_f31 = -(var_r31->unk_10C[1] - var_r31->unk_10C[0]);
    }
    else {
        var_f31 = var_r31->unk_10C[1] - var_r31->unk_10C[0];
    }
    var_r31->unk_124[1] = var_f31;
    if ((var_r31->unk_10C[2] - var_r31->unk_10C[1]) < 0.0f) {
        var_f30 = -(var_r31->unk_10C[2] - var_r31->unk_10C[1]);
    }
    else {
        var_f30 = var_r31->unk_10C[2] - var_r31->unk_10C[1];
    }
    var_r31->unk_124[2] = var_r31->unk_124[1] + var_f30;
    fn_1_939C(var_r31->unk_F4, (float(*)[3])var_r31->unk_64, (float(*)[3])var_r31->unk_88, 3);
    fn_1_939C(var_r31->unk_100, (float(*)[3])var_r31->unk_AC, (float(*)[3])var_r31->unk_D0, 3);
    fn_1_8F90(var_r31->unk_124, var_r31->unk_10C, var_r31->unk_118, 3);
}

void fn_1_4E44(u8 arg0, float arg8)
{
    M433DllMapWork2 *work = lbl_1_bss_98[arg0]->data;
    work->unk_140 = arg8;
}

void fn_1_4E78(u8 arg0, u8 arg1, u16 arg2, float arg8, float arg9, float argA)
{
    M433DllMapWork2 *var_r31 = lbl_1_bss_98[arg0]->data;
    var_r31->unk_188[arg1] = arg2;
    var_r31->unk_14C[arg1] = arg8;
    var_r31->unk_158[arg1] = arg9;
    var_r31->unk_170[arg1] = argA;
    var_r31->unk_164[arg1] = 90.0f;
}

static char lbl_1_data_130[20] = "goal"; // explicitly declared because of padding

void fn_1_4F04(omObjData *object)
{
    s32 var_r31;
    M433DllUnkStruct *var_r29;
    s32 var_r28;

    var_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M428, 0));
    object->model[0] = var_r31;
    Hu3DModelShadowMapSet(var_r31);
    Hu3DModelLayerSet(var_r31, 2);
    var_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M428, 1));
    object->model[1] = var_r31;
    Hu3DModelAttrSet(var_r31, HU3D_ATTR_DISPOFF);
    fn_1_5558(var_r31, &lbl_1_bss_90);
    var_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M428, 2));
    object->model[2] = var_r31;
    Hu3DModelLayerSet(var_r31, 2);
    var_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M428, 3));
    object->model[3] = var_r31;
    Hu3DModelAttrSet(var_r31, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowMapObjSet(var_r31, lbl_1_data_130);
    Hu3DModelLayerSet(var_r31, 2);
    var_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M428, 4));
    object->model[4] = var_r31;
    Hu3DModelAttrSet(var_r31, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31, HU3D_MOTATTR_SHAPE_LOOP);
    Hu3DModelLayerSet(var_r31, 2);
    Hu3DModelCameraSet(var_r31, 1);
    fn_1_4170(var_r31, 1);
    var_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M428, 5));
    object->model[5] = var_r31;
    Hu3DModelAttrSet(var_r31, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31, HU3D_MOTATTR_SHAPE_LOOP);
    Hu3DModelLayerSet(var_r31, 2);
    Hu3DModelCameraSet(var_r31, 2);
    fn_1_4170(var_r31, 2);
    for (var_r28 = 0; var_r28 < 2; var_r28++) {
        var_r31 = fn_1_71AC(DATA_MAKE_NUM(DATADIR_M428, 6), 0x3E8, fn_1_6280);
        object->model[var_r28 + 6] = var_r31;
        Hu3DModelLayerSet(var_r31, 4);
        Hu3DModelCameraSet(var_r31, 1 << var_r28);
        var_r29 = ((ParticleData *)Hu3DData[var_r31].unk_120)->unk_1C;
        var_r29->unk_08 = 400.0f;
        var_r29->unk_0C = -400.0f;
        var_r29->unk_10 = 1300.0f;
        var_r29->unk_14 = -800.0f;
        var_r29->unk_18 = 700.0f;
        var_r29->unk_1C = 150.0f;
    }
    object->func = fn_1_51E0;
}

void fn_1_51E0(omObjData *object)
{
    M433DllUnkStruct *var_r31;
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31 = ((ParticleData *)Hu3DData[object->model[var_r30 + 6]].unk_120)->unk_1C;
        var_r31->unk_08 = 500.0f + CenterM[var_r30].x;
        var_r31->unk_0C = -500.0f + CenterM[var_r30].x;
        var_r31->unk_10 = 900.0f + CenterM[var_r30].y;
        var_r31->unk_14 = -1200.0f + CenterM[var_r30].y;
    }
}

void fn_1_52D8(omObjData *object) { }

u8 fn_1_52DC(M433DllUnkStruct3 *arg0, Vec *arg1)
{
    u32 var_r30;
    M433DllUnkStruct2 *var_r29;
    s32 var_r28;

    var_r28 = 0;
    for (var_r29 = arg0->unk_04, var_r30 = 0; var_r30 < arg0->unk_00; var_r30++, var_r29++) {
        if (fn_1_5370(var_r29, arg1) != 0) {
            break;
        }
    }
    if (var_r30 < arg0->unk_00) {
        var_r28 = 1;
    }
    return var_r28;
}

u8 fn_1_5370(M433DllUnkStruct2 *arg0, Vec *arg1)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    M433DllUnkStruct4 *var_r31;
    s32 var_r28;
    u32 var_r27;
    s32 var_r26;
    Vec *var_r25;
    s32 var_r24;
    Vec *var_r23;

    var_r31 = arg0->unk_0C;
    for (var_r27 = 0; var_r27 < arg0->unk_08; var_r27++, var_r31++) {
        sp8 = *arg1;
        sp8.y = 0.0f;
        VECSubtract(&sp8, &var_r31->unk_00, &sp20);
        var_f30 = VECMag(&sp20);
        if (!(var_f30 > (400.0f + var_r31->unk_20)) && (var_r31->unk_2C != 0.0f)) {
            var_r24 = 0;
            for (var_r28 = 0; var_r28 < 3; var_r28++) {
                var_r26 = var_r28 + 1;
                if (var_r26 == 3) {
                    var_r26 = 0;
                }
                var_r23 = &arg0->unk_00[var_r31->unk_0C[var_r28]];
                var_r25 = &arg0->unk_00[var_r31->unk_0C[var_r26]];
                VECSubtract(var_r25, var_r23, &sp20);
                VECSubtract(arg1, var_r25, &sp14);
                var_f31 = (sp20.x * sp14.y) - (sp20.y * sp14.x);
                if ((var_f31 * var_r31->unk_2C) < 0.0) {
                    var_r24 = 1;
                    break;
                }
            }
            if (var_r24 == 0) {
                arg1->z = ((var_r31->unk_30 - (var_r31->unk_24 * arg1->x)) - (var_r31->unk_28 * arg1->y)) / var_r31->unk_2C;
                return 1;
            }
        }
    }
    return 0;
}

void fn_1_5558(s32 arg0, M433DllUnkStruct3 *arg1)
{
    HsfData *var_r31;
    u32 var_r30;

    var_r31 = Hu3DData[arg0].hsfData;
    lbl_1_bss_12C = arg1;
    lbl_1_bss_12C->unk_00 = 0;
    lbl_1_bss_12C->unk_04 = fn_1_72D4(0x1000);
    lbl_1_bss_128 = lbl_1_bss_12C->unk_04;
    fn_1_5CCC(var_r31, var_r31->root);
    var_r30 = lbl_1_bss_12C->unk_00 * 0x10;
    lbl_1_bss_128 = lbl_1_bss_12C->unk_04;
    lbl_1_bss_12C->unk_04 = fn_1_72D4(var_r30);
    memcpy(lbl_1_bss_12C->unk_04, lbl_1_bss_128, var_r30);
    fn_1_739C(lbl_1_bss_128);
}

void fn_1_5684(HsfData *arg0, HsfObject *arg1)
{
    Vec sp18;
    Vec spC;
    float var_f31;
    M433DllUnkStruct4 *var_r31;
    HsfFace *var_r30;
    HsfBuffer *var_r29;
    s32 var_r28;
    s32 var_r27;
    HsfBuffer *var_r25;

    var_r29 = arg1->data.vertex;
    var_r25 = arg1->data.face;
    lbl_1_bss_128->unk_08 = var_r25->count;
    lbl_1_bss_128->unk_04 = var_r29->count;
    lbl_1_bss_128->unk_00 = var_r29->data;
    lbl_1_bss_128->unk_0C = fn_1_72D4(lbl_1_bss_128->unk_08 * sizeof(M433DllUnkStruct4));
    var_r30 = var_r25->data;
    var_r31 = lbl_1_bss_128->unk_0C;
    for (var_r27 = 0; var_r27 < var_r25->count; var_r27++, var_r30++, var_r31++) {
        switch (var_r30->type & 7) {
            case 2:
                var_r31->unk_1C = 3;
                var_r31->unk_00.x = var_r31->unk_00.y = var_r31->unk_00.z = 0.0f;
                for (var_r28 = 0; var_r28 < 3; var_r28++) {
                    var_r31->unk_0C[var_r28] = var_r30->indices[var_r28][0];
                    var_r31->unk_00.x += ((Vec *)var_r29->data)[var_r30->indices[var_r28][0]].x;
                    var_r31->unk_00.y += ((Vec *)var_r29->data)[var_r30->indices[var_r28][0]].y;
                    var_r31->unk_00.z += ((Vec *)var_r29->data)[var_r30->indices[var_r28][0]].z;
                }
                var_r31->unk_00.x /= 3.0f;
                var_r31->unk_00.y /= 3.0f;
                var_r31->unk_00.z /= 3.0f;
                var_r31->unk_20 = 0.0f;
                for (var_r28 = 0; var_r28 < 3; var_r28++) {
                    VECSubtract(&((Vec *)var_r29->data)[var_r30->indices[var_r28][0]], &var_r31->unk_00, &sp18);
                    var_f31 = VECMag(&sp18);
                    if (var_f31 > var_r31->unk_20) {
                        var_r31->unk_20 = var_f31;
                    }
                }
                var_r31->unk_00.y = 0.0f;
                VECSubtract(&((Vec *)var_r29->data)[var_r30->strip.indices[1][0]], &((Vec *)var_r29->data)[var_r30->strip.indices[0][0]], &sp18);
                VECSubtract(&((Vec *)var_r29->data)[var_r30->strip.indices[2][0]], &((Vec *)var_r29->data)[var_r30->strip.indices[0][0]], &spC);
                var_r31->unk_24 = (sp18.y * spC.z) - (sp18.z * spC.y);
                var_r31->unk_28 = (sp18.z * spC.x) - (sp18.x * spC.z);
                var_r31->unk_2C = (sp18.x * spC.y) - (sp18.y * spC.x);
                var_r31->unk_30 = (var_r31->unk_2C * ((Vec *)var_r29->data)[var_r30->strip.indices[0][0]].z)
                    + ((var_r31->unk_24 * ((Vec *)var_r29->data)[var_r30->strip.indices[0][0]].x)
                        + (var_r31->unk_28 * ((Vec *)var_r29->data)[var_r30->strip.indices[0][0]].y));
                break;
            case 3:
                var_r31->unk_1C = 4;
                var_r31->unk_00.x = var_r31->unk_00.y = var_r31->unk_00.z = 0.0f;
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    var_r31->unk_0C[var_r28] = var_r30->indices[var_r28][0];
                    var_r31->unk_00.x += ((Vec *)var_r29->data)[var_r30->indices[var_r28][0]].x;
                    var_r31->unk_00.y += ((Vec *)var_r29->data)[var_r30->indices[var_r28][0]].y;
                    var_r31->unk_00.z += ((Vec *)var_r29->data)[var_r30->indices[var_r28][0]].z;
                }
                var_r31->unk_00.x *= 0.25f;
                var_r31->unk_00.y *= 0.25f;
                var_r31->unk_00.z *= 0.25f;
                var_r31->unk_20 = 0.0f;
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    VECSubtract(&((Vec *)var_r29->data)[var_r30->indices[var_r28][0]], &var_r31->unk_00, &sp18);
                    var_f31 = VECMag(&sp18);
                    if (var_f31 > var_r31->unk_20) {
                        var_r31->unk_20 = var_f31;
                    }
                }
                VECSubtract(&((Vec *)var_r29->data)[var_r30->strip.indices[1][0]], &((Vec *)var_r29->data)[var_r30->strip.indices[0][0]], &sp18);
                VECSubtract(&((Vec *)var_r29->data)[var_r30->strip.indices[2][0]], &((Vec *)var_r29->data)[var_r30->strip.indices[1][0]], &spC);
                var_r31->unk_24 = (sp18.y * spC.z) - (sp18.z * spC.y);
                var_r31->unk_28 = (sp18.z * spC.x) - (sp18.x * spC.z);
                var_r31->unk_2C = (sp18.x * spC.y) - (sp18.y * spC.x);
                var_r31->unk_30 = (var_r31->unk_24 * ((Vec *)var_r29->data)[var_r30->strip.indices[0][0]].x)
                    + ((var_r31->unk_28 * ((Vec *)var_r29->data)[var_r30->strip.indices[0][0]].y))
                    + (var_r31->unk_2C * ((Vec *)var_r29->data)[var_r30->strip.indices[0][0]].z);
                break;
            default:
                OSReport("Error\n");
                break;
        }
    }
    for (var_r27 = 0; var_r27 < arg1->data.childrenCount; var_r27++) {
        fn_1_5CCC(arg0, arg1->data.children[var_r27]);
    }
}

void fn_1_5CCC(HsfData *var_r31, HsfObject *var_r23)
{
    s16 var_r22;

    switch (var_r23->type) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 9:
            for (var_r22 = 0; var_r22 < var_r23->data.childrenCount; var_r22++) {
                fn_1_5CCC(var_r31, var_r23->data.children[var_r22]);
            }
            break;
        case 2:
            fn_1_5684(var_r31, var_r23);
            lbl_1_bss_12C->unk_00++;
            lbl_1_bss_128++;
            break;
    }
}

void fn_1_6280(ModelData *arg1, ParticleData *particle, Mtx matrix)
{
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    HsfanimStruct01 *var_r31;
    M433DllUnkStruct *var_r30;
    s32 var_r28;
    s32 var_r27;

    var_r30 = particle->unk_1C;
    var_f29 = var_r30->unk_08 - var_r30->unk_0C;
    var_f30 = var_r30->unk_10 - var_r30->unk_14;
    var_f28 = var_r30->unk_18 - var_r30->unk_1C;
    switch (var_r30->unk_04) {
        case 2:
            break;
        case 0:
            for (var_r31 = particle->unk_48, var_r28 = 0; var_r28 < (0.3f * particle->unk_30); var_r28++, var_r31++) {
                var_r31->unk00 = 1;
                var_r31->unk34.x = var_r30->unk_0C + (var_f29 * (fn_1_7500() / 65536.0f));
                var_r31->unk34.y = (var_r30->unk_14 + ((200.0f + var_f30) * (fn_1_7500() / 65536.0f))) - 100.0f;
                var_r31->unk34.z = var_r30->unk_1C + (var_f28 * (fn_1_7500() / 65536.0f));
                var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = var_r31->unk40.a = 0xFF;
                var_r31->unk2C = 26.0f + (10.0f * (fn_1_7500() / 65536.0f));
                var_r31->unk08.x = 0.0f;
                var_r31->unk08.y = -1.6333333f * (fn_1_7500() / 65536.0f);
                var_r31->unk08.z = 0.0f;
                var_r31->unk14.x = var_r31->unk14.y = var_r31->unk14.z = 0.0f;
                var_r31->unk30 = 360.0f * (fn_1_7500() / 65536.0f);
                var_r31->unk02 = 0;
            }
            for (; var_r28 < particle->unk_30; var_r28++, var_r31++) {
                var_r31->unk00 = 0;
                var_r31->unk40.a = 0;
                var_r31->unk08.x = 0.0f;
                var_r31->unk08.y = -1.6333333f * (fn_1_7500() / 65536.0f);
                var_r31->unk08.z = 0.0f;
                var_r31->unk14.x = var_r31->unk14.y = var_r31->unk14.z = 0.0f;
            }
            particle->unk_04.x = particle->unk_04.y = particle->unk_04.z = 0.0f;
            var_r30->unk_04++;
            break;
        case 1:
            particle->unk_04.x = particle->unk_04.y = particle->unk_04.z = 0.0f;
            var_r30->unk_06 = 0;
            break;
        case 3:
            particle->unk_04.x *= 0.95f;
            if (particle->unk_04.x < 0.0f) {
                var_f27 = -particle->unk_04.x;
            }
            else {
                var_f27 = particle->unk_04.x;
            }
            if (var_f27 < 0.01f) {
                var_r30->unk_04 = 1;
            }
            break;
    }
    for (var_r31 = particle->unk_48, var_r27 = 0, var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
        switch (var_r31->unk00) {
            case 0:
                if (((var_r28 > (0.4f * particle->unk_30)) && (particle->unk_04.x == 0.0f)) || (var_r27 >= (10.0f + (0.75f * particle->unk_04.x)))) {
                    var_r31->unk2C = 0.01f;
                }
                else {
                    if (((fn_1_7500() & 3) == 0) || (particle->unk_04.x == 0.0f)) {
                        var_r31->unk34.x = var_r30->unk_0C + (var_f29 * (fn_1_7500() / 65536.0f));
                        var_r31->unk34.y = var_r30->unk_10 + (100.0f * (fn_1_7500() / 65536.0f));
                        var_r31->unk40.a = 7;
                    }
                    else {
                        if (particle->unk_04.x > 0.0f) {
                            var_r31->unk34.x = var_r30->unk_0C - (100.0f * (fn_1_7500() / 65536.0f));
                        }
                        else {
                            var_r31->unk34.x = var_r30->unk_08 + (100.0f * (fn_1_7500() / 65536.0f));
                        }
                        var_r31->unk34.y = var_r30->unk_10 - (var_f30 * (fn_1_7500() / 65536.0f));
                        var_r31->unk40.a = 0xFF;
                    }
                    var_r31->unk34.z = var_r30->unk_1C + (var_f28 * (fn_1_7500() / 65536.0f));
                    var_r31->unk2C = 28.0f + (10.0f * (fn_1_7500() / 65536.0f));
                    var_r31->unk08.x = 0.0f;
                    var_r31->unk08.y = -1.6333333f * (fn_1_7500() / 65536.0f);
                    var_r31->unk08.z = 0.0f;
                    var_r31->unk08.x = 0.25f * var_r31->unk08.y * ((fn_1_7500() - 0x8000) / 32768.0f);
                    var_r31->unk14.x = var_r31->unk14.y = var_r31->unk14.z = 0.0f;
                    var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = 0xFF;
                    var_r31->unk02 = 0;
                    var_r27++;
                    var_r31->unk00++;
                }
                break;
            case 1:
                var_r31->unk08.y += -1.6333333f;
                var_r31->unk08.y += 0.19998f * (1.6333333f * (4.81f + (0.005f * var_r31->unk2C)));
                if (var_r31->unk02 != 0) {
                    var_r31->unk02--;
                    var_r31->unk08.y *= 0.8f;
                    var_r31->unk08.y += 0.0025f * (-1.6333333f * var_r31->unk2C);
                }
                else if ((fn_1_7500() & 0x7F) == 0) {
                    var_r31->unk02 = (s32)(30.0f * (fn_1_7500() / 65536.0f));
                }
                if (var_r31->unk08.x < 0.0f) {
                    var_f26 = -var_r31->unk08.x;
                }
                else {
                    var_f26 = var_r31->unk08.x;
                }
                if (var_f26 < 0.02f) {
                    var_r31->unk14.x = 0.025f * (var_r31->unk2C * (-1.6333333f * ((fn_1_7500() - 0x8000) / 32768.0f)));
                    if (var_r31->unk14.x > 0.0f) {
                        var_r31->unk08.x = 0.02f + (0.04f * var_r31->unk14.x);
                    }
                    else {
                        var_r31->unk08.x = (0.04f * var_r31->unk14.x) - 0.02f;
                    }
                }
                else {
                    var_f31 = var_r31->unk08.x - var_r31->unk14.x;
                    var_r31->unk08.x = var_r31->unk14.x + (0.98f * var_f31);
                    if (var_f31 < 0.0f) {
                        var_f25 = -var_f31;
                    }
                    else {
                        var_f25 = var_f31;
                    }
                    if (var_f25 < 0.02f) {
                        var_r31->unk14.x = 0.0f;
                    }
                }
                if ((var_r31->unk34.y < (var_r30->unk_14 - 100.0f)) || (var_r31->unk34.x > (100.0f + var_r30->unk_08))
                    || (var_r31->unk34.x < (var_r30->unk_0C - 100.0f))) {
                    var_r31->unk00 = 0;
                }
                if (var_r31->unk34.y > (100.0f + var_r30->unk_10)) {
                    var_r31->unk34.y = var_r30->unk_14 - (100.0f * (fn_1_7500() / 65536.0f));
                }
                if (var_r31->unk34.y < var_r30->unk_14) {
                    var_r31->unk40.a *= 0.9f;
                }
                else if (var_r31->unk40.a < 0xFF) {
                    var_r31->unk40.a += 8;
                }
                break;
        }
        VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
        if (particle->unk_04.x != 0.0f) {
            sp8 = particle->unk_04;
            sp8.x *= var_r31->unk2C / 28.0f;
            sp8.y = (((u8)var_r31->unk2C & 1) != 0 ? 1.0f : -1.0f) * (sp8.x * (0.05f + (s32)(0.2f * (fn_1_7500() / 65536.0f))));
            VECAdd(&var_r31->unk34, &sp8, &var_r31->unk34);
        }
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

s16 fn_1_71AC(s32 arg0, s16 arg1, ParticleHook hook)
{
    HsfanimStruct01 *var_r31;
    ParticleData *var_r30;
    s32 var_r29;
    s32 var_r28;
    M433DllUnkStruct *var_r27;
    AnimData *var_r25;

    var_r25 = HuSprAnimRead(HuDataReadNum(arg0, MEMORY_DEFAULT_NUM));
    var_r28 = Hu3DParticleCreate(var_r25, arg1);
    Hu3DParticleHookSet(var_r28, hook);
    var_r30 = Hu3DData[var_r28].unk_120;
    var_r27 = fn_1_72D4(0x48);
    var_r30->unk_1C = var_r27;
    var_r27->unk_04 = 0;
    var_r31 = var_r30->unk_48;
    memset(var_r31, 0, arg1 * 0x44);
    for (var_r29 = 0; var_r29 < arg1; var_r29++, var_r31++) {
        var_r31->unk06 = -1;
        var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = var_r31->unk40.a = 0xFF;
    }
    return var_r28;
}

void fn_1_7294(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x20; var_r31++) {
        lbl_1_bss_A8[var_r31] = NULL;
    }
}

void *fn_1_72D4(s32 arg0)
{
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (!lbl_1_bss_A8[i]) {
            break;
        }
    }
    if (i == 0x20) {
        return NULL;
    }
    lbl_1_bss_A8[i] = HuMemDirectMallocNum(HEAP_SYSTEM, arg0, MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_A8[i], 0, arg0);
    return lbl_1_bss_A8[i];
}

void fn_1_739C(M433DllUnkStruct2 *arg0)
{
    s32 var_r31;
    for (var_r31 = 0; var_r31 < 0x20; var_r31++) {
        if (lbl_1_bss_A8[var_r31] == arg0) {
            break;
        }
    }
    if (var_r31 != 0x20) {
        HuMemDirectFree(lbl_1_bss_A8[var_r31]);
        lbl_1_bss_A8[var_r31] = NULL;
    }
}

void fn_1_7430(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x20; var_r31++) {
        if (lbl_1_bss_A8[var_r31]) {
            HuMemDirectFree(lbl_1_bss_A8[var_r31]);
            lbl_1_bss_A8[var_r31] = NULL;
        }
    }
}

void fn_1_74B4(s16 arg0, Mtx arg1)
{
    ModelData *var_r31 = &Hu3DData[arg0];
    MTXCopy(arg1, var_r31->unk_F0);
}

u32 lbl_1_data_14C = 0x41C64E6D;

s32 fn_1_7500(void)
{
    lbl_1_data_14C *= 0x41C64E6D;
    lbl_1_data_14C += 0x3039;
    return lbl_1_data_14C >> 0x10;
}

void fn_1_7554(s32 arg0, s32 *arg1)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    for (var_r31 = 0; var_r31 < arg0; var_r31++) {
        arg1[var_r31] = var_r31;
    }
    for (var_r31 = 0; var_r31 < (arg0 - 1); var_r31++) {
        lbl_1_data_14C *= 0x41C64E6D;
        lbl_1_data_14C += 0x3039;
        var_r28 = lbl_1_data_14C >> 0x10;
        var_r27 = var_r28;
        var_r30 = arg0 * (var_r27 / 65536.0f);
        var_r29 = arg1[var_r31];
        arg1[var_r31] = arg1[var_r30];
        arg1[var_r30] = var_r29;
    }
}

float fn_1_7690(float arg8, float arg9, float argA)
{
    float var_f31;

    if (arg8 > 180.0f) {
        arg8 -= 360.0f;
    }
    else if (arg8 <= -180.0f) {
        arg8 += 360.0f;
    }
    if (arg9 > 180.0f) {
        arg9 -= 360.0f;
    }
    else if (arg9 <= -180.0f) {
        arg9 += 360.0f;
    }
    var_f31 = arg8 - arg9;
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    else if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    }
    arg8 = arg9 + (var_f31 * argA);
    if (arg8 > 180.0f) {
        return arg8 - 360.0f;
    }
    if (arg8 <= -180.0f) {
        arg8 += 360.0f;
    }
    return arg8;
}

void fn_1_77F8(Mtx arg0, float arg8, float arg9, float argA)
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

void fn_1_7918(Mtx arg0, Vec *arg1)
{
    float var_f29;
    float var_f28;

    arg1->x = atan2d(arg0[1][2], arg0[2][2]);
    if (arg1->x < 0.0f) {
        arg1->x += 360.0f;
    }
    arg1->z = atan2d(arg0[0][1], arg0[0][0]);
    if (arg1->z < 0.0f) {
        arg1->z += 360.0f;
    }
    var_f29 = -arg0[0][2];
    var_f28 = sqrtf((1.0 - (var_f29 * var_f29)) < 0.0 ? (-(1.0 - (var_f29 * var_f29))) : (1.0 - (var_f29 * var_f29)));
    if ((arg1->x > 90.0f) && (arg1->x < 270.0f) && (arg1->z > 90.0f) && (arg1->z < 270.0f)) {
        arg1->x = fmod(180.0f + arg1->x, 360.0);
        arg1->z = fmod(180.0f + arg1->z, 360.0);
        var_f28 = -var_f28;
    }
    arg1->y = atan2d(var_f29, var_f28);
    if (arg1->y < 0.0f) {
        arg1->y += 360.0f;
    }
}

void fn_1_7CB4(Mtx arg0, Vec *arg1)
{
    float var_f29;
    float var_f27;

    arg1->z = atan2d(arg0[0][1], arg0[1][1]);
    if (arg1->z < 0.0f) {
        arg1->z += 360.0f;
    }
    arg1->y = atan2d(arg0[0][2], arg0[2][2]);
    if (arg1->y < 0.0f) {
        arg1->y += 360.0f;
    }
    var_f29 = -arg0[2][1];
    var_f27 = sqrtf((1.0 - (var_f29 * var_f29)) < 0.0 ? (-(1.0 - (var_f29 * var_f29))) : (1.0 - (var_f29 * var_f29)));
    arg1->x = atan2d(var_f29, var_f27);
    if (arg1->x < 0.0f) {
        arg1->x += 360.0f;
    }
}

float fn_1_7F94(Vec *arg0)
{
    float var_f30 = (arg0->z * arg0->z) + ((arg0->x * arg0->x) + (arg0->y * arg0->y));
    var_f30 = sqrtf(var_f30);
    if (var_f30 != 0.0f) {
        float var_f29 = 1.0f / var_f30;
        arg0->x = arg0->x * var_f29;
        arg0->y = arg0->y * var_f29;
        arg0->z = arg0->z * var_f29;
    }
    else {
        arg0->x = arg0->y = arg0->z = 0.0f;
    }
    return var_f30;
}

void fn_1_812C(Vec arg0, Vec arg1, Vec *arg2, float arg8)
{
    if (arg8 <= 0.0f) {
        arg2->x = arg0.x;
        arg2->y = arg0.y;
        arg2->z = arg0.z;
        arg8 = 0.0f;
    }
    else if (arg8 >= 1.0f) {
        arg2->x = arg0.x + arg1.x;
        arg2->y = arg0.y + arg1.y;
        arg2->z = arg0.z + arg1.z;
        arg8 = 1.0f;
    }
    else {
        arg2->x = arg0.x + (arg8 * arg1.x);
        arg2->y = arg0.y + (arg8 * arg1.y);
        arg2->z = arg0.z + (arg8 * arg1.z);
    }
}

float fn_1_8204(Vec arg0, Vec arg1, Vec arg2)
{
    float var_f31;
    float temp_f30;

    var_f31 = arg2.x * (arg1.x - arg0.x) + arg2.y * (arg1.y - arg0.y) + arg2.z * (arg1.z - arg0.z);
    temp_f30 = -(arg2.x * arg2.x + arg2.y * arg2.y + arg2.z * arg2.z);
    if (temp_f30 != 0.0f) {
        var_f31 /= temp_f30;
    }
    return var_f31;
}

float fn_1_82C0(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Vec sp44;
    float var_f31;

    if (arg2->x * arg2->x + arg2->y * arg2->y + arg2->z * arg2->z == 0.0f) {
        return (arg0->x - arg1->x) * (arg0->x - arg1->x) + (arg0->y - arg1->y) * (arg0->y - arg1->y) + (arg0->z - arg1->z) * (arg0->z - arg1->z);
    }
    var_f31 = fn_1_8204(*arg0, *arg1, *arg2);
    fn_1_812C(*arg1, *arg2, &sp44, var_f31);
    return (arg0->x - sp44.x) * (arg0->x - sp44.x) + (arg0->y - sp44.y) * (arg0->y - sp44.y) + (arg0->z - sp44.z) * (arg0->z - sp44.z);
}

float fn_1_85FC(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4)
{
    float var_f30;

    if (((arg2->z * arg2->z) + ((arg2->x * arg2->x) + (arg2->y * arg2->y))) == 0.0f) {
        return ((arg0->z - arg1->z) * (arg0->z - arg1->z))
            + (((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)));
    }
    var_f30 = fn_1_8204(*arg0, *arg1, *arg2);
    fn_1_812C(*arg1, *arg2, arg3, var_f30);

    arg4->x = arg0->x - arg3->x;
    arg4->y = arg0->y - arg3->y;
    arg4->z = arg0->z - arg3->z;
    return fn_1_7F94(arg4);
}

float fn_1_8AAC(float arg8, float arg9, float argA, float argB)
{
    float var_f31 = 1.0 - arg8;
    float var_f30 = (argB * (arg8 * arg8)) + ((arg9 * (var_f31 * var_f31)) + (2.0 * (argA * (var_f31 * arg8))));
    return var_f30;
}

void fn_1_8B24(float *arg0, float *arg1, float *arg2, float *arg3, float arg8)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        *arg3++ = fn_1_8AAC(arg8, *arg0++, *arg1++, *arg2++);
    }
}

float fn_1_8C40(float arg8, float arg9, float argA, float argB)
{
    float var_f31 = 2.0 * ((arg8 * argB) + (((arg8 - 1.0) * arg9) + ((1.0 - (2.0 * arg8)) * argA)));
    return var_f31;
}

void fn_1_8CB8(float *arg0, float *arg1, float *arg2, float *arg3, float arg8)
{
    float spC[3];
    float var_f29;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        spC[var_r31] = fn_1_8C40(arg8, *arg0++, *arg1++, *arg2++);
    }
    var_f29 = sqrtf((spC[2] * spC[2]) + ((spC[0] * spC[0]) + (spC[1] * spC[1])));
    if (var_f29) {
        var_f29 = 1.0 / var_f29;
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            *arg3++ = var_f29 * spC[var_r31];
        }
        return;
    }
    *arg3++ = 0.0f;
    *arg3++ = 0.0f;
    *arg3++ = 1.0f;
}

void fn_1_8F90(float *arg0, float *arg1, float *arg2, s32 arg3)
{
    float sp48[16];
    float sp8[16];
    double var_f31;
    s32 var_r31;

    arg2[0] = 0.0f;
    arg2[arg3 - 1] = 0.0f;
    for (var_r31 = 0; var_r31 < (arg3 - 1); var_r31++) {
        sp48[var_r31] = arg0[var_r31 + 1] - arg0[var_r31];
        if (sp48[var_r31] == 0.0f) {
            sp8[var_r31 + 1] = 0.0f;
        }
        else {
            sp8[var_r31 + 1] = (arg1[var_r31 + 1] - arg1[var_r31]) / sp48[var_r31];
        }
    }
    arg2[1] = sp8[2] - sp8[1];
    sp8[1] = 2.0f * (arg0[2] - arg0[0]);
    for (var_r31 = 1; var_r31 < (arg3 - 2); var_r31++) {
        var_f31 = sp48[var_r31] / sp8[var_r31];
        arg2[var_r31 + 1] = (sp8[var_r31 + 2] - sp8[var_r31 + 1]) - (var_f31 * arg2[var_r31]);
        sp8[var_r31 + 1] = (2.0f * (arg0[var_r31 + 2] - arg0[var_r31])) - (var_f31 * sp48[var_r31]);
    }
    arg2[arg3 - 2] -= sp48[arg3 - 2] * arg2[arg3 - 1];
    for (var_r31 = arg3 - 2; var_r31 > 0; var_r31--) {
        if (sp8[var_r31] == 0.0f) {
            arg2[var_r31] = 0.0f;
        }
        else {
            arg2[var_r31] = (arg2[var_r31] - (sp48[var_r31] * arg2[var_r31 + 1])) / sp8[var_r31];
        }
    }
}

float fn_1_9248(float arg8, float *arg0, float *arg1, float *arg2, s32 arg3)
{
    float var_f31;
    float var_f30;
    float var_f29;

    s32 var_r31 = arg8;
    arg8 = arg8 - var_r31;
    var_f31 = arg0[var_r31 + 1] - arg0[var_r31];
    var_f30 = var_f31 * arg8;
    var_f29 = arg1[var_r31]
        + (var_f30
            * ((var_f30 * ((3.0f * arg2[var_r31]) + ((var_f30 * (arg2[var_r31 + 1] - arg2[var_r31])) / var_f31)))
                + (((arg1[var_r31 + 1] - arg1[var_r31]) / var_f31) - (var_f31 * ((2.0f * arg2[var_r31]) + arg2[var_r31 + 1])))));
    if (var_f31 == 0.0f) {
        var_f29 = arg1[var_r31];
    }
    return var_f29;
}

void fn_1_939C(float *arg0, float (*arg1)[3], float (*arg2)[3], s32 var_r28)
{
    float spD4[16];
    float sp94[16];
    Vec sp8;
    s32 var_r30;
    s32 var_r27;

    arg0[0] = 0.0f;
    for (var_r30 = 1; var_r30 < var_r28; var_r30++) {
        VECSubtract((Vec *)&arg1[var_r30], (Vec *)&arg1[var_r30 - 1], &sp8);
        arg0[var_r30] = arg0[var_r30 - 1] + VECMag(&sp8);
    }
    for (var_r27 = 0; var_r27 < 3; var_r27++) {
        for (var_r30 = 0; var_r30 < var_r28; var_r30++) {
            spD4[var_r30] = arg1[var_r30][var_r27];
        }
        fn_1_8F90(arg0, spD4, sp94, var_r28);
        for (var_r30 = 0; var_r30 < var_r28; var_r30++) {
            arg2[var_r30][var_r27] = sp94[var_r30];
        }
    }
}

void fn_1_977C(float arg8, float *arg0, float *arg1, float (*arg2)[3], float (*arg3)[3], s32 arg4)
{
    float sp48[16];
    float sp8[16];
    s32 var_r30;
    s32 var_r29;

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        for (var_r30 = 0; var_r30 < arg4; var_r30++) {
            sp48[var_r30] = arg2[var_r30][var_r29];
            sp8[var_r30] = arg3[var_r30][var_r29];
        }
        arg0[var_r29] = fn_1_9248(arg8, arg1, sp48, sp8, 3);
    }
}

u8 fn_1_9990(Vec *sp8)
{
    u32 var_r31;
    M433DllUnkStruct2 *var_r30;
    s32 var_r29;

    var_r29 = 0;
    var_r30 = lbl_1_bss_90.unk_04;
    for (var_r31 = 0; var_r31 < lbl_1_bss_90.unk_00; var_r31++, var_r30++) {
        if (fn_1_5370(var_r30, sp8) != 0) {
            break;
        }
    }
    if (var_r31 < lbl_1_bss_90.unk_00) {
        var_r29 = 1;
    }
    return var_r29;
}

void fn_1_9A30(u8 arg0, float arg8, Vec *arg1, Vec *arg2, float arg9)
{
    M433DllMapWork2 *var_r31;

    var_r31 = lbl_1_bss_98[arg0]->data;
    var_r31->unk_00 = 0;
    var_r31->unk_144 = arg8;
    var_r31->unk_148 = arg8;
    var_r31->unk_1C = var_r31->unk_04;
    var_r31->unk_34.x = arg1->x;
    var_r31->unk_34.y = arg1->y;
    var_r31->unk_34.z = arg1->z;
    var_r31->unk_28 = var_r31->unk_10;
    var_r31->unk_40.x = arg2->x;
    var_r31->unk_40.y = arg2->y;
    var_r31->unk_40.z = arg2->z;
    var_r31->unk_134 = var_r31->unk_130;
    var_r31->unk_138 = arg9;
}

void fn_1_9ADC(u8 arg0)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    M433DllMapWork2 *work;
    omObjData *var_r30;

    sp14.x = 0.0f;
    sp14.y = 80.0f;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    var_f31 = 600.0f;
    work = lbl_1_bss_98[arg0]->data;
    work->unk_00 = 0;
    work->unk_148 = work->unk_144 = 1.0f;
    work->unk_1C = work->unk_04;
    work->unk_34.x = sp14.x;
    work->unk_34.y = sp14.y;
    work->unk_34.z = sp14.z;
    work->unk_28 = work->unk_10;
    work->unk_40.x = sp8.x;
    work->unk_40.y = sp8.y;
    work->unk_40.z = sp8.z;
    work->unk_134 = work->unk_130;
    work->unk_138 = var_f31;
    Hu3DCameraPerspectiveSet(1 << arg0, 45.0f, 100.0f, 5000.0f, 1.2f);
    Hu3DCameraViewportSet(1 << arg0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(2 >> arg0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1 << arg0, 0, 0, 0x280, 0x1E0);
    Hu3DCameraScissorSet(2 >> arg0, 0, 0, 0, 0);
    var_r30 = lbl_1_bss_A0;
    Hu3DModelAttrSet(var_r30->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r30->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r30->model[6], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r30->model[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(var_r30->model[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(var_r30->model[arg0 + 4], HU3D_ATTR_DISPOFF);
    var_r30->func = fn_1_52D8;
}

void fn_1_9DE8(u8 arg0, float arg8, s8 arg1)
{
    ParticleData *var_r31;
    M433DllUnkStruct *var_r30;

    var_r31 = Hu3DData[lbl_1_bss_A0->model[arg0 + 6]].unk_120;
    var_r30 = ((ParticleData *)Hu3DData[lbl_1_bss_A0->model[arg0 + 6]].unk_120)->unk_1C;
    var_r30->unk_04 = 2;
    var_r31->unk_04.x = arg8 * arg1;
}

void fn_1_9EA8(u8 arg0)
{
    M433DllUnkStruct *var_r31 = ((ParticleData *)Hu3DData[lbl_1_bss_A0->model[arg0 + 6]].unk_120)->unk_1C;
    if (var_r31->unk_04 == 2) {
        var_r31->unk_04 = 3;
    }
}

u8 fn_1_9F08(u8 arg0)
{
    M433DllUnkStruct *var_r31 = ((ParticleData *)Hu3DData[lbl_1_bss_A0->model[arg0 + 6]].unk_120)->unk_1C;
    return var_r31->unk_04;
}
