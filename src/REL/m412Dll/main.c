#include "REL/m412Dll.h"

#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/hsfmotion.h"
#include "game/mapspace.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "math.h"
#include "version.h"

// bss
s16 lbl_1_bss_7A0;
s16 lbl_1_bss_79E;
s16 lbl_1_bss_79C;
s16 lbl_1_bss_798[2];
s32 lbl_1_bss_794;
s32 lbl_1_bss_790;
s32 lbl_1_bss_780[4];
f32 lbl_1_bss_77C;
f32 lbl_1_bss_778;
f32 lbl_1_bss_774;
unkStruct3 lbl_1_bss_4D4[4];
unkStruct2 lbl_1_bss_33C[6];
unkStruct2 lbl_1_bss_2F8;
unkStruct *lbl_1_bss_278[0x20];
Process *lbl_1_bss_274;
Vec lbl_1_bss_268;
Vec lbl_1_bss_25C;
Vec lbl_1_bss_250;
Vec lbl_1_bss_13C[0x17];
Vec lbl_1_bss_28[0x17];
s32 lbl_1_bss_24;
Vec lbl_1_bss_18;
Vec lbl_1_bss_C;
Vec lbl_1_bss_0;

// data
s32 lbl_1_data_0[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
s32 lbl_1_data_20[8] = { DATA_MAKE_NUM(DATADIR_MARIOMDL1, 0x01), DATA_MAKE_NUM(DATADIR_LUIGIMDL1, 0x01), DATA_MAKE_NUM(DATADIR_PEACHMDL1, 0x01),
    DATA_MAKE_NUM(DATADIR_YOSHIMDL1, 0x01), DATA_MAKE_NUM(DATADIR_WARIOMDL1, 0x01), DATA_MAKE_NUM(DATADIR_DONKEYMDL1, 0x01),
    DATA_MAKE_NUM(DATADIR_DAISYMDL1, 0x01), DATA_MAKE_NUM(DATADIR_WALUIGIMDL1, 0x01) };
s32 lbl_1_data_40[8] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00), DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00), DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00) };
s32 lbl_1_data_60[6] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1A), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1B), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x4B) };
Vec lbl_1_data_78[7] = { { 474.0f, 30.0f, -497.0f }, { 330.0f, 30.0f, 562.0f }, { -694.0f, 30.0f, 43.0f }, { -375.0f, 30.0f, -483.0f },
    { 715.0f, 30.0f, 62.0f }, { -334.0f, 30.0f, 570.0f }, { 100.0f, 30.0f, -630.0f } };
char *lbl_1_data_298[0x17] = { "sb_hahen-sb_hahen01", "sb_hahen-sb_hahen02", "sb_hahen-sb_hahen03", "sb_hahen-sb_hahen04", "sb_hahen-sb_hahen05",
    "sb_hahen-sb_hahen06", "sb_hahen-sb_hahen07", "sb_hahen-sb_hahen08", "sb_hahen-sb_hahen09", "sb_hahen-sb_hahen10", "sb_hahen-sb_hahen11",
    "sb_hahen-sb_hahen12", "sb_hahen-sb_hahen13", "sb_hahen-sb_hahen14", "sb_hahen-sb_hahen15", "sb_hahen-sb_hahen16", "sb_hahen-sb_hahen17",
    "sb_hahen-sb_hahen18", "sb_hahen-sb_hahen19", "sb_hahen-sb_hahen20", "sb_hahen-sb_hahen21", "sb_hahen-sb_hahen22", "sb_hahen-sb_hahen23" };

void ObjectSetup(void)
{
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f31;

    lbl_1_bss_274 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_274);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 40.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0U, 0U, 0x280U, 0x1E0U);
    lbl_1_bss_268.x = 1100.0f;
    lbl_1_bss_268.y = 1600.0f;
    lbl_1_bss_268.z = 760.0f;
    lbl_1_bss_250.x = 0.0f;
    lbl_1_bss_250.y = 1.0f;
    lbl_1_bss_250.z = 0.0f;
    lbl_1_bss_25C.x = 60.0f;
    lbl_1_bss_25C.y = 0.0f;
    lbl_1_bss_25C.z = 0.0f;
    temp_f30 = lbl_1_bss_268.x;
    temp_f29 = lbl_1_bss_268.y;
    temp_f31 = lbl_1_bss_268.z;
    lbl_1_bss_774 = sqrtf((temp_f31 * temp_f31) + ((temp_f30 * temp_f30) + (temp_f29 * temp_f29)));
    lbl_1_bss_778 = fn_1_1D08(atan2d(temp_f30, temp_f31));
    lbl_1_bss_77C = fn_1_1D08(atan2d(temp_f29, temp_f31));
    lbl_1_bss_77C = 50.0f;
    Hu3DLighInit();
    lbl_1_bss_7A0 = Hu3DGLightCreate(10000.0f, 0.0f, 10000.0f, -1.0f, 0.0f, -1.0f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DGLightPosAimSet(lbl_1_bss_7A0, 0.0f, 4330.13f, 2500.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(lbl_1_bss_7A0);
    lbl_1_bss_18.x = -500.0f;
    lbl_1_bss_18.y = 4000.0f;
    lbl_1_bss_18.z = 0.0f;
    lbl_1_bss_C.x = lbl_1_bss_C.z = 0.0f;
    lbl_1_bss_C.y = 1.0f;
    lbl_1_bss_0.x = 0.0f;
    lbl_1_bss_0.y = 0.0f;
    lbl_1_bss_0.z = 0.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_bss_18, &lbl_1_bss_C, &lbl_1_bss_0);
    Hu3DBGColorSet(0U, 0U, 0U);
    fn_1_8BC();
    HuPrcChildCreate(fn_1_B1C0, 0x1000U, 0x2000U, 0, HuPrcCurrentGet());
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
}

void *fn_1_6EC(f32 arg8, f32 arg9, f32 argA, s32 arg0)
{
    Vec sp8;

    sp8.x = arg8;
    sp8.y = arg9;
    sp8.z = argA;
    return (void *)HuAudFXEmiterPlay(arg0, &sp8);
}

void fn_1_73C(void)
{
    Vec sp8;
    CameraData *camera;

    camera = &Hu3DCamera[0];

    sp8.x = 0.0f;
    sp8.y = 0.0f;
    sp8.z = -1.0f;

    while (1) {
        HuAudFXListnerUpdate(&camera->pos, &sp8);
        if (lbl_1_bss_794 >= 3)
            break;
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_7BC(void)
{
    Vec sp14;
    Vec sp8;
    s32 temp_r30;
    s32 var_r31;

    temp_r30 = (s32)HuPrcCurrentGet()->user_data;
    sp14.x = 1465.0f;
    sp14.y = 770.0f;
    sp14.z = -2400.0f;
    sp8.x = sp14.x - 474.0f;
    sp8.y = sp14.y - 30.0f;
    sp8.z = sp14.z - -497.0f;

    for (var_r31 = 0; var_r31 < 0x168; var_r31++) {
        HuAudFXEmiterUpDate(temp_r30, &sp14);
        VECAdd(&sp8, &sp14, &sp14);
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_894(omObjData *object)
{
    return;
}

void fn_1_898(omObjData *object)
{
    object->model[0] = lbl_1_bss_79C;
    object->func = &fn_1_894;
}

void fn_1_8BC(void)
{
    Vec sp20;
    Vec sp14;
    s32 sp10;
    volatile u32 spC;
    volatile u32 sp8;
    unkStruct2 *temp_r31;
    unkStruct3 *temp_r30;
    s16 var_r29;
    void *var_r27;
    s32 var_r28;
    s32 var_r26;
    unkStruct2 *temp_r25;
    HsfTransform *temp_r24;
    Process *var_r23;
    s32 temp_r22;
    AnimData *var_r21;
    s16 var_r20;
    s16 var_r19;
    s32 var_r18;
    HsfObject *var_r17;

    nMap = 0;
    HuAudSndGrpSet(0x25);
    sp20.x = 1100.0f;
    sp20.y = 1600.0f;
    sp20.z = 760.0f;
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = -1.0f;
    HuAudFXListnerSetEX(&sp20, &sp14, 10000.0f, 34 * REFRESH_FREQ, 0.0f, 300.0f, 300.0f);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x00), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29 = Hu3DModelCreate(var_r27);
    Hu3DModelLayerSet(var_r29, 1);
    Hu3DModelShadowMapSet(var_r29);
    Hu3DModelAttrSet(var_r29, HU3D_MOTATTR_LOOP);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x01), MEMORY_DEFAULT_NUM, HEAP_DATA);
    lbl_1_bss_79C = Hu3DModelCreate(var_r27);
    Hu3DModelAttrSet(lbl_1_bss_79C, HU3D_ATTR_DISPOFF);
    MapObject[nMap++] = omAddObjEx(lbl_1_bss_274, 0x100, 1, 0, -1, fn_1_898);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x02), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29 = Hu3DModelCreate(var_r27);
    Hu3DModelLayerSet(var_r29, 0);
    Hu3DModelAttrSet(var_r29, HU3D_MOTATTR_LOOP);

    for (var_r28 = 0; var_r28 < 0x20; var_r28++) {
        lbl_1_bss_278[var_r28] = NULL;
    }
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x1F), MEMORY_DEFAULT_NUM, HEAP_DATA);
    lbl_1_bss_79E = var_r29 = Hu3DModelCameraCreate(Hu3DMotionCreate(var_r27), 1);
    Hu3DCameraMotionStart(var_r29, 1);

    for (var_r28 = 0; var_r28 < 2; var_r28++) {
        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x1D), MEMORY_DEFAULT_NUM, HEAP_DATA);
        lbl_1_bss_798[var_r28] = var_r29 = Hu3DModelCreate(var_r27);
        Hu3DModelLayerSet(var_r29, 2);
        Hu3DModelAttrSet(var_r29, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);
    }

    for (var_r28 = 0; var_r28 < 6; var_r28++) {
        temp_r31 = &lbl_1_bss_33C[var_r28];
        temp_r31->unk24 = var_r28;
        temp_r31->unk28 = var_r28;
        temp_r31->unk20 = 0;
        if (var_r28 == 0) {
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x06), MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r20 = var_r29 = Hu3DModelCreate(var_r27);
        }
        else {
            var_r29 = Hu3DModelLink(var_r20);
        }
        temp_r31->unk0 = var_r29;
        temp_r31->unk2C.x = lbl_1_data_78[var_r28].x;
        temp_r31->unk2C.y = lbl_1_data_78[var_r28].y;
        temp_r31->unk2C.z = lbl_1_data_78[var_r28].z;
        Hu3DModelPosSet(var_r29, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
        temp_r31->unk38.x = temp_r31->unk38.z = 0.0f;
        temp_r31->unk38.y = fn_1_1D08(180.0 + atan2d(temp_r31->unk2C.x, temp_r31->unk2C.z));
        Hu3DModelRotSet(var_r29, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        Hu3DModelLayerSet(var_r29, 1);
        Hu3DModelShadowSet(var_r29);

        for (var_r26 = 0; var_r26 < 3; var_r26++) {
            var_r27 = HuDataSelHeapReadNum(var_r26 + DATA_MAKE_NUM(DATADIR_M412, 0x07), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r31->unkC[var_r26] = Hu3DJointMotion(var_r29, var_r27);
        }
        var_r27 = HuDataSelHeapReadNum(var_r28 + DATA_MAKE_NUM(DATADIR_M412, 0x0A), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unkC[var_r26] = Hu3DJointMotion(var_r29, var_r27);
        Hu3DMotionSet(var_r29, temp_r31->unkC[3]);
        temp_r31->unk2 = var_r29 = Hu3DModelLink(var_r20);
        Hu3DModelPosSet(var_r29, temp_r31->unk2C.x, temp_r31->unk2C.y - 10.0f, temp_r31->unk2C.z);
        Hu3DModelRotSet(var_r29, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        Hu3DModelScaleSet(var_r29, 1.0f, -1.0f, 1.0f);
        Hu3DModelLayerSet(var_r29, 0);
        Hu3DModelShadowReset(var_r29);
        Hu3DMotionSet(var_r29, temp_r31->unkC[3]);
        Hu3DModelAttrSet(var_r29, HU3D_ATTR_CULL_FRONT);
        var_r27 = HuDataSelHeapReadNum(var_r28 + DATA_MAKE_NUM(DATADIR_M412, 0x10), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk4 = var_r29 = Hu3DModelCreate(var_r27);
        Hu3DModelLayerSet(var_r29, 1);
        if (var_r28 >= 3) {
            Hu3DModelAttrSet(temp_r31->unk0, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(temp_r31->unk2, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(temp_r31->unk4, HU3D_MOTATTR_PAUSE);
        }
        if (var_r28 == 0) {
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x03), MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r19 = var_r29 = Hu3DModelCreate(var_r27);
        }
        else {
            var_r29 = Hu3DModelLink(var_r19);
        }
        temp_r31->unk6 = var_r29;
        Hu3DModelLayerSet(var_r29, 1);
        Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);
        Hu3DModelShadowSet(var_r29);
        Hu3DModelShadowDispOff(var_r29);
        temp_r31->unk8 = Hu3DModelLink(var_r19);
        Hu3DModelLayerSet(var_r29, 0);
        Hu3DModelAttrSet(temp_r31->unk8, HU3D_ATTR_DISPOFF);
        var_r23 = HuPrcChildCreate(fn_1_2A1C, 0x2000, 0x3000, 0, HuPrcCurrentGet());
        var_r23->user_data = temp_r31;
    }

    for (var_r28 = 0, var_r18 = 0; var_r28 < 50; var_r28++) {
        temp_r31 = &lbl_1_bss_33C[frandmod(3) + var_r18];
        temp_r25 = &lbl_1_bss_33C[frandmod(3) + var_r18];
        temp_r22 = temp_r31->unk28;
        temp_r31->unk28 = temp_r25->unk28;
        temp_r25->unk28 = temp_r22;
    }
    temp_r31 = &lbl_1_bss_33C[3];
    temp_r25 = &lbl_1_bss_33C[5];
    temp_r22 = temp_r31->unk28;
    temp_r31->unk28 = temp_r25->unk28;
    temp_r25->unk28 = temp_r22;
    if (frandmod(2) != 0) {
        temp_r31 = &lbl_1_bss_33C[4];
        temp_r25 = &lbl_1_bss_33C[5];
        temp_r22 = temp_r31->unk28;
        temp_r31->unk28 = temp_r25->unk28;
        temp_r25->unk28 = temp_r22;
    }
    temp_r31 = &lbl_1_bss_2F8;
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x16), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r20 = var_r29 = Hu3DModelCreate(var_r27);
    temp_r31->unk0 = var_r29;
    temp_r31->unk2C.x = lbl_1_data_78[6].x;
    temp_r31->unk2C.y = lbl_1_data_78[6].y;
    temp_r31->unk2C.z = lbl_1_data_78[6].z;
    Hu3DModelPosSet(var_r29, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
    temp_r31->unk38.x = temp_r31->unk38.z = 0.0f;
    temp_r31->unk38.y = fn_1_1D08(180.0 + atan2d(temp_r31->unk2C.x, temp_r31->unk2C.z));
    Hu3DModelRotSet(var_r29, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
    Hu3DModelLayerSet(var_r29, 1);
    Hu3DModelShadowSet(var_r29);

    for (var_r26 = 0; var_r26 < 5; var_r26++) {
        var_r27 = HuDataSelHeapReadNum(var_r26 + DATA_MAKE_NUM(DATADIR_M412, 0x17), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unkC[var_r26] = Hu3DJointMotion(var_r29, var_r27);
    }
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x16), MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r31->unk2 = var_r29 = Hu3DModelCreate(var_r27);

    for (var_r26 = 0; var_r26 < 5; var_r26++) {
        var_r27 = HuDataSelHeapReadNum(var_r26 + DATA_MAKE_NUM(DATADIR_M412, 0x17), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk16[var_r26] = Hu3DJointMotion(var_r29, var_r27);
    }
    Hu3DModelPosSet(var_r29, temp_r31->unk2C.x, temp_r31->unk2C.y - 10.0f, temp_r31->unk2C.z);
    Hu3DModelRotSet(var_r29, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
    Hu3DModelScaleSet(var_r29, 1.0f, -1.0f, 1.0f);
    Hu3DModelLayerSet(var_r29, 0);
    Hu3DModelShadowReset(var_r29);
    Hu3DModelAttrSet(var_r29, HU3D_ATTR_CULL_FRONT);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x04), MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r31->unk6 = var_r29 = Hu3DModelCreate(var_r27);
    Hu3DModelLayerSet(var_r29, 1);
    Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(var_r29);
    Hu3DModelShadowDispOff(var_r29);
    temp_r31->unk8 = Hu3DModelLink(temp_r31->unk6);
    Hu3DModelLayerSet(temp_r31->unk8, 0);
    Hu3DModelAttrSet(temp_r31->unk8, HU3D_ATTR_DISPOFF);
    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x05), MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r31->unkA = var_r29 = Hu3DModelCreate(var_r27);
    Hu3DModelShadowSet(var_r29);
    Hu3DModelShadowDispOff(var_r29);
    Hu3DModelLayerSet(var_r29, 1);
    Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);

    for (var_r28 = 0; var_r28 < 0x17; var_r28++) {
        var_r17 = Hu3DModelObjPtrGet(var_r29, lbl_1_data_298[var_r28]);
        if (!var_r17) {
            OSReport("objname %s\n", lbl_1_data_298[var_r28]);
            OSPanic("m412.c", 0x258, "ObjPtr");
        }
        temp_r24 = &var_r17->data.base;
        lbl_1_bss_13C[var_r28].x = temp_r24->pos.x;
        lbl_1_bss_13C[var_r28].y = temp_r24->pos.y;
        lbl_1_bss_13C[var_r28].z = temp_r24->pos.z;
        lbl_1_bss_28[var_r28].x = temp_r24->scale.x;
        lbl_1_bss_28[var_r28].y = temp_r24->scale.y;
        lbl_1_bss_28[var_r28].z = temp_r24->scale.z;
    }
    var_r23 = HuPrcChildCreate(fn_1_3950, 0x2000, 0x3000, 0, HuPrcCurrentGet());
    var_r23->user_data = temp_r31;

    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        lbl_1_bss_4D4[var_r28].unk3C = var_r28;
    }

    for (var_r28 = 0; var_r28 < 50; var_r28++) {
        spC = frandmod(4);
        sp8 = frandmod(4);
        sp10 = lbl_1_bss_4D4[sp8].unk3C;
        lbl_1_bss_4D4[sp8].unk3C = lbl_1_bss_4D4[spC].unk3C;
        lbl_1_bss_4D4[spC].unk3C = sp10;
    }

    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        temp_r30 = &lbl_1_bss_4D4[var_r28];
        temp_r30->unk24 = var_r28;
        temp_r30->unk28 = var_r28;
        temp_r30->unk2C = GWPlayerCfg[var_r28].pad_idx;
        temp_r30->unk0 = CharModelCreate(lbl_1_data_0[GWPlayerCfg[var_r28].character], 4);
        Hu3DModelLayerSet(temp_r30->unk0, 1);
        var_r27 = HuDataSelHeapReadNum(lbl_1_data_20[GWPlayerCfg[var_r28].character], MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r30->unk2 = Hu3DModelCreate(var_r27);
        Hu3DModelScaleSet(temp_r30->unk2, 1.0f, -1.0f, 1.0f);
        Hu3DModelAttrSet(temp_r30->unk2, HU3D_ATTR_CULL_FRONT);
        Hu3DModelLayerSet(temp_r30->unk2, 0);
        CharModelLayerSetAll(3);
        temp_r30->unk54.x = temp_r30->unk54.z = temp_r30->unk54.y = 0.0f;
        temp_r30->unk54.y = fn_1_1D08(45.0f + (90.0f * temp_r30->unk3C) + lbl_1_bss_778);
        temp_r30->unk40.x = (400.0 * sind(temp_r30->unk54.y));
        temp_r30->unk40.z = (400.0 * cosd(temp_r30->unk54.y));
        temp_r30->unk54.y = fn_1_1D08(180.0f + temp_r30->unk54.y);
        temp_r30->unk6C = temp_r30->unk54.y;
        temp_r30->unk40.y = 0.0f;
        temp_r30->unk60.x = 50.0f;
        temp_r30->unk60.z = temp_r30->unk60.y = 0.0f;
        HuSetVecF(&temp_r30->unk7C, 0.0, 0.0, 0.0);
        Hu3DModelPosSet(temp_r30->unk0, temp_r30->unk40.x, temp_r30->unk40.y, temp_r30->unk40.z);
        Hu3DModelRotSet(temp_r30->unk0, temp_r30->unk54.x, temp_r30->unk54.y, temp_r30->unk54.z);
        Hu3DModelPosSet(temp_r30->unk2, temp_r30->unk40.x, temp_r30->unk40.y, temp_r30->unk40.z);
        Hu3DModelRotSet(temp_r30->unk2, temp_r30->unk54.x, temp_r30->unk54.y, temp_r30->unk54.z);
        Hu3DModelShadowSet(temp_r30->unk0);

        for (var_r26 = 0; var_r26 < 6; var_r26++) {
            temp_r30->unkC[var_r26] = CharModelMotionCreate(lbl_1_data_0[GWPlayerCfg[var_r28].character], lbl_1_data_60[var_r26]);
            var_r27
                = HuDataSelHeapReadNum((u16)lbl_1_data_60[var_r26] | lbl_1_data_40[GWPlayerCfg[var_r28].character], MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r30->unk18[var_r26] = Hu3DJointMotion(temp_r30->unk2, var_r27);
        }
        CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[var_r28].character], temp_r30->unkC[0]);
        Hu3DModelAttrSet(temp_r30->unk0, HU3D_MOTATTR_LOOP);
        Hu3DMotionSet(temp_r30->unk2, temp_r30->unk18[0]);
        Hu3DModelAttrSet(temp_r30->unk2, HU3D_MOTATTR_LOOP);
        CharModelMotionDataClose(lbl_1_data_0[GWPlayerCfg[var_r28].character]);
        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x1C), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r30->unk6 = var_r29 = Hu3DModelCreate(var_r27);
        Hu3DModelLayerSet(var_r29, 1);
        Hu3DModelAttrSet(var_r29, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);
        Hu3DModelShadowSet(var_r29);
        Hu3DModelShadowDispOff(var_r29);
        temp_r30->unk8 = var_r29 = Hu3DModelLink(var_r29);
        Hu3DModelLayerSet(var_r29, 0);
        Hu3DModelAttrSet(var_r29, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF | HU3D_ATTR_CULL_FRONT);
        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x1D), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r30->unkA = var_r29 = Hu3DModelCreate(var_r27);
        Hu3DModelLayerSet(var_r29, 3);
        Hu3DModelAttrSet(var_r29, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);
        var_r23 = HuPrcChildCreate(fn_1_7C60, 0x2000, 0x4000, 0, HuPrcCurrentGet());
        var_r23->user_data = temp_r30;
    }
    var_r21 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M412, 0x1E), MEMORY_DEFAULT_NUM));
    var_r29 = Hu3DParticleCreate(var_r21, 0x100);
    Hu3DModelPosSet(var_r29, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r29, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r29, 4);
    Hu3DParticleColSet(var_r29, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r29, 0.0f);
    Hu3DParticleHookSet(var_r29, fn_1_A01C);
    var_r21 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 0x03), MEMORY_DEFAULT_NUM));
    var_r29 = Hu3DParticleCreate(var_r21, 0x40);
    Hu3DModelPosSet(var_r29, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r29, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r29, 4);
    Hu3DParticleColSet(var_r29, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r29, 0.0f);
    Hu3DParticleHookSet(var_r29, fn_1_A618);
    var_r21 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 0x03), MEMORY_DEFAULT_NUM));
    var_r29 = Hu3DParticleCreate(var_r21, 3);
    Hu3DModelPosSet(var_r29, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r29, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r29, 4);
    Hu3DParticleColSet(var_r29, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r29, 0.0f);
    Hu3DParticleHookSet(var_r29, fn_1_AA88);
    HuDataDirClose(DATADIR_EFFECT);
    HuPrcChildCreate(fn_1_B160, 0x1000, 0x1000, 0, HuPrcCurrentGet());
}

f32 fn_1_1D08(f32 arg0)
{
    while (arg0 >= 360.0f || arg0 < 0.0f) {
        if (arg0 >= 360.0f) {
            arg0 -= 360.0f;
        }
        if (arg0 < 0.0f) {
            arg0 += 360.0f;
        }
    }
    return arg0;
}

void fn_1_1D88(void)
{
    void *var_r31;

    var_r31 = HuPrcCurrentGet()->user_data;
    HuMemDirectFree(var_r31);
}

void fn_1_1DBC(void)
{
    Vec sp8;
    HsfObject *var_r27;
    HsfTransform *temp_r31;
    unkStruct4 *temp_r30;
    Vec *temp_r29;
    s32 var_r28;
    f32 var_f31;
    f32 var_f30;

    temp_r30 = HuPrcCurrentGet()->user_data;
    HuPrcDestructorSet(fn_1_1D88);
    var_r27 = Hu3DModelObjPtrGet(temp_r30->unk0, lbl_1_data_298[temp_r30->unk4]);
    if (!var_r27) {
        OSReport("objname %s\n", lbl_1_data_298[temp_r30->unk4]);
        OSPanic("m412.c", 0x32E, "ObjPtr");
    }
    temp_r31 = &var_r27->data.base;
    temp_r29 = &lbl_1_bss_13C[temp_r30->unk4];
    temp_r31->pos.x = temp_r29->x;
    temp_r31->pos.y = temp_r29->y;
    temp_r31->pos.z = temp_r29->z;
    HuSetVecF(&sp8, 0.15f * temp_r31->pos.x, 0.15f * temp_r31->pos.y, 0.15f * temp_r31->pos.z);
    temp_r29 = &lbl_1_bss_28[temp_r30->unk4];
    temp_r31->scale.x = temp_r29->x;
    temp_r31->scale.y = temp_r29->y;
    temp_r31->scale.z = temp_r29->z;
    for (var_r28 = 0, var_f31 = -2.0f, var_f30 = 1.0f; var_r28 < 0x1E; var_r28++) {
        sp8.y -= var_f31;
        var_f31 += 0.5f;
        temp_r31->pos.x += sp8.x;
        temp_r31->pos.y += sp8.y;
        temp_r31->pos.z += sp8.z;
        temp_r31->scale.x *= 0.95f;
        temp_r31->scale.y *= 0.95f;
        temp_r31->scale.z *= 0.95f;
        if (temp_r30->unk4 == 0) {
            var_f30 -= 0.033333335f;
            Hu3DModelTPLvlSet(temp_r30->unk0, var_f30);
        }
        HuPrcVSleep();
    }
    temp_r30->unk8 = 0;
    HuPrcVSleep();
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_2014(void)
{
    unkStruct2 *temp_r31; // could also be unkStruct3 `\_("/)_/`

    temp_r31 = (unkStruct2 *)HuPrcCurrentGet()->user_data;
    lbl_1_bss_278[temp_r31->unk6] = NULL;
    HuMemDirectFree(temp_r31);
}

void fn_1_2064(void)
{
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    f32 spC;
    f32 sp8;
    Process *temp_r26;
    s32 var_r30;
    unkStruct *temp_r28;
    unkStruct3 *temp_r29;
    unkStruct *temp_r31;
    unkStruct4 *var_r27;

    temp_r31 = (unkStruct *)HuPrcCurrentGet()->user_data;
    temp_r31->unk8 = 0;
    temp_r31->unkA = 0;
    HuPrcDestructorSet(fn_1_2014);

    do {
        if ((temp_r31->unk8 != 0) || (lbl_1_bss_794 >= 4))
            break;
        temp_r31->unk10.x += (temp_r31->unk24.y * sind(temp_r31->unk24.x));
        temp_r31->unk10.z += (temp_r31->unk24.y * cosd(temp_r31->unk24.x));
        temp_r31->unk10.y += temp_r31->unk24.z;
        temp_r31->unk24.z -= 0.9f;
        if (temp_r31->unk30 != 100.0f) {
            HuSetVecF(&sp28, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
            for (var_r30 = 0; var_r30 < 0x20; var_r30++) {
                temp_r28 = lbl_1_bss_278[var_r30];
                if ((var_r30 != temp_r31->unk6) && temp_r28 && (temp_r28->unk6 != -1)) {
                    HuSetVecF(&sp1C, temp_r28->unk10.x, temp_r28->unk10.y, temp_r28->unk10.z);
                    HuSubVecF(&sp10, &sp28, &sp1C);
                    if (sqrtf((sp10.z * sp10.z) + ((sp10.x * sp10.x) + (sp10.y * sp10.y))) < (temp_r31->unk30 + temp_r28->unk30)) {
                        if (temp_r28->unk30 != 100.0f) {
                            temp_r28->unk8 = 1;
                        }
                        temp_r31->unk8 = 1;
                    }
                }
            }
        }
        HuSetVecF(&sp28, temp_r31->unk10.x, 0.0, temp_r31->unk10.z);

        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            temp_r29 = &lbl_1_bss_4D4[var_r30];
            HuSetVecF(&sp1C, temp_r29->unk40.x, 0.0, temp_r29->unk40.z);
            HuSubVecF(&sp10, &sp28, &sp1C);
            if ((sqrtf((sp10.z * sp10.z) + ((sp10.x * sp10.x) + (sp10.y * sp10.y))) < (temp_r31->unk30 + temp_r29->unk60.x))
                && ((150.0f + temp_r29->unk40.y + temp_r31->unk30) > temp_r31->unk10.y)) {

                if (temp_r29->unk30 != 3) {
                    if (temp_r31->unkC == 0) {
                        omVibrate(temp_r29->unk24, 0xC, 4, 2);
                    }
                    else {
                        omVibrate(temp_r29->unk24, 0xC, 0xC, 0);
                    }
                }
                HuAudFXPlay(0x585);
                temp_r29->unk30 = 3;
                temp_r31->unk8 = 1;
            }
        }
        if (temp_r31->unk10.y < temp_r31->unk30) {
            temp_r31->unk10.y = temp_r31->unk30;
            temp_r31->unk8 = 1;
        }
        Hu3DModelPosSet(temp_r31->unk0, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        Hu3DModelPosSet(temp_r31->unk2, temp_r31->unk10.x, -temp_r31->unk10.y, temp_r31->unk10.z);
        if (temp_r31->unk8 != 0)
            break;
        HuPrcVSleep();
    } while (1);
    if (temp_r31->unkC == 1) {
        HuAudFXPlay(0x58D);
    }
    else {
        HuAudFXPlay(0x58C);
    }
    Hu3DModelAttrSet(temp_r31->unk0, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r31->unk2, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowDispOff(temp_r31->unk0);
    temp_r31->unkA = 1;
    if (temp_r31->unkC == 1) {

        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            if (lbl_1_bss_4D4[var_r30].unk30 != 3) {
                omVibrate(lbl_1_bss_4D4[var_r30].unk24, 0xC, 6, 6);
            }
        }
        Hu3DModelPosSet(temp_r31->unk4, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        Hu3DModelAttrReset(temp_r31->unk4, HU3D_ATTR_DISPOFF);
        Hu3DModelShadowDispOn(temp_r31->unk4);

        for (var_r30 = 0; var_r30 < 0x17; var_r30++) {
            temp_r26 = HuPrcChildCreate(fn_1_1DBC, 0x2000, 0x1000, 0, HuPrcCurrentGet());
            var_r27 = HuMemDirectMalloc(HEAP_DATA, sizeof(unkStruct4));
            temp_r26->user_data = var_r27;
            var_r27->unk0 = temp_r31->unk4;
            var_r27->unk4 = var_r30;
            var_r27->unk8 = 1;
            var_r27->unkC.x = temp_r31->unk10.x;
            var_r27->unkC.y = temp_r31->unk10.y;
            var_r27->unkC.z = temp_r31->unk10.z;
        }
        while (var_r27->unk8 != 0) {
            HuPrcVSleep();
        }
    }
    HuPrcVSleep();
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

s32 fn_1_2708(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x20; var_r31++) {
        if (!lbl_1_bss_278[var_r31])
            break;
    }
    if (var_r31 >= 0x20) {
        var_r31 = -1;
    }
    lbl_1_bss_278[var_r31] = HuMemDirectMalloc(HEAP_DATA, sizeof(unkStruct));
    lbl_1_bss_278[var_r31]->unk6 = -1;
    lbl_1_bss_278[var_r31]->unkA = 0;
    return var_r31;
}

f32 fn_1_27C4(s32 arg0, f32 arg8, f32 arg9)
{
    f32 temp_f31;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    f32 var_f28;
    f32 var_f29;

    temp_f31 = arg8 - fn_1_1D08(arg9);
    if ((temp_f31 < 0.0f) || (ABS_INV(temp_f31) > 180.0f)) {
        if (ABS_INV(temp_f31) > 180.0f) {
            var_f29 = (360.0f - ABS_INV(temp_f31)) / arg0;
            if (temp_f31 > 0.0f) {
                var_f29 = -var_f29;
            }
        }
        else {
            var_f29 = temp_f31 / arg0;
        }
    }
    else {
        var_f29 = temp_f31 / arg0;
    }
    return var_f29;
}

s32 lbl_1_data_310[6][2] = { { 0x09249222, 0x22210842 }, { 0x04924888, 0x88842108 }, { 0x12492222, 0x22108420 }, { 0x04444444, 0x44444400 },
    { 0x11111111, 0x11100000 }, { 0x04444444, 0x40000000 } };

s32 lbl_1_data_340[1][2] = { { 0x00040008, 0x02000000 } };

s32 lbl_1_data_348[6] = { 0x0, 0x0, 0x0, 0x8, 0x12, 0x1C };

void fn_1_2A1C(void)
{
    Vec sp68;
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    f32 sp40;
    f32 temp_f18;
    f32 var_f24;
    f32 var_f23;
    f32 var_f19;
    f32 var_f22;
    s32 var_r22;
    s32 var_r23;
    s32 var_r25;
    s32 var_r24;
    s32 var_r26;
    s32 var_r29;
    unkStruct *temp_r30;
    unkStruct3 *temp_r27;
    unkStruct2 *temp_r31;
    s32 var_r21;
    Process *var_r20;

    temp_r31 = HuPrcCurrentGet()->user_data;
    switch (temp_r31->unk24) {
        case 0:
            var_r25 = 0x142;
            var_r24 = 0x154;
            break;
        case 1:
            var_r25 = 0x14A;
            var_r24 = 0x15E;
            break;
        case 2:
            var_r25 = 0x148;
            var_r24 = 0x162;
            break;
        default:
            var_r25 = 0x4E;
            var_r24 = 0x5D;
            break;
    }

loop_10:
    var_r29 = lbl_1_bss_790 / REFRESH_RATE;
    if (var_r29 >= 0x3C) {
        var_r29 = 0x3C;
    }
    if (var_r29 == lbl_1_data_348[temp_r31->unk28]) {
        Hu3DModelAttrReset(temp_r31->unk0, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(temp_r31->unk2, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(temp_r31->unk4, HU3D_MOTATTR_PAUSE);
    }
    if (var_r25 == Hu3DMotionTimeGet(temp_r31->unk0)) {
        temp_r31->unk20 = 1;
    }
    if (var_r24 == Hu3DMotionTimeGet(temp_r31->unk0)) {
        HuAudFXPlay(0x581);
    }
    if (lbl_1_bss_794 >= 4) {
        while (1) {
            HuPrcVSleep();
        }
    }
    var_r22 = 1;
    if (var_r29 >= 0x20) {
        var_r22 = 0;
    }
    if (((1 << (var_r29 % 32)) & lbl_1_data_310[temp_r31->unk28][var_r22]) != 0) {
        var_r21 = fn_1_2708();
    }
    else {
        HuPrcVSleep();
        goto loop_10;
    }
    var_r26 = frandmod(4);
    if (lbl_1_bss_4D4[var_r26].unk30 == 3) {
        for (var_r23 = 3; var_r23 != 0; var_r23--) {
            var_r26++;
            if (var_r26 >= 4) {
                var_r26 = 0;
            }
            if (lbl_1_bss_4D4[var_r26].unk30 != 3)
                break;
        }
    }
    temp_r27 = &lbl_1_bss_4D4[var_r26];
    Hu3DMotionSet(temp_r31->unk0, temp_r31->unkC[1]);
    Hu3DMotionSet(temp_r31->unk2, temp_r31->unkC[1]);
    Hu3DModelAttrReset(temp_r31->unk0, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(temp_r31->unk2, HU3D_MOTATTR_LOOP);
    var_r29 = Hu3DMotionMaxTimeGet(temp_r31->unk0);
    var_f24 = fn_1_1D08(atan2d(temp_r27->unk40.x - temp_r31->unk2C.x, temp_r27->unk40.z - temp_r31->unk2C.z));
    temp_f18 = (temp_r27->unk40.x + (50.0 * sind(var_f24)));
    sp44.y = (temp_r27->unk40.z + (50.0 * cosd(var_f24)));
    sp44.x = 360.0f * frandf();
    var_f23 = 50.0f * frandf();
    temp_f18 += (var_f23 * sind(sp44.x));
    sp44.y += (var_f23 * cosd(sp44.x));
    sp44.z = fn_1_27C4(var_r29, var_f24, temp_r31->unk38.y);
    HuAudFXPlay(0x583);

    for (; var_r29 != 0; var_r29--) {
        temp_r31->unk38.y += sp44.z;
        Hu3DModelRotSet(temp_r31->unk0, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        Hu3DModelRotSet(temp_r31->unk2, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);
    Hu3DModelAttrReset(temp_r31->unk6, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(temp_r31->unk8, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowDispOn(temp_r31->unk6);
    Hu3DModelPosSet(temp_r31->unk6, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(temp_r31->unk8, 0.0f, 0.0f, 0.0f);
    Hu3DModelHookSet(temp_r31->unk0, "itemhook", temp_r31->unk6);
    Hu3DModelHookSet(temp_r31->unk2, "itemhook", temp_r31->unk8);
    Hu3DMotionShiftSet(temp_r31->unk0, temp_r31->unkC[2], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unkC[2], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(10);
    while (Hu3DMotionTimeGet(temp_r31->unk0) < 18.0f) {
        HuPrcVSleep();
    }
    Hu3DModelHookReset(temp_r31->unk0);
    Hu3DModelHookReset(temp_r31->unk2);
    HuAudFXPlay(0x582);
    temp_r30 = lbl_1_bss_278[var_r21];
    temp_r30->unk6 = var_r21;
    temp_r30->unkA = 0;
    var_r20 = HuPrcChildCreate(fn_1_2064, 0x1000, 0x3000, 0, HuPrcCurrentGet());
    var_r20->user_data = temp_r30;
    temp_r30->unkC = 0;
    temp_r30->unk0 = temp_r31->unk6;
    temp_r30->unk2 = temp_r31->unk8;
    temp_r30->unk30 = 25.0f;
    temp_r30->unk10.x = -89.937f;
    temp_r30->unk10.y = 125.861f;
    temp_r30->unk10.z = 43.181f;
    temp_r30->unk1C.x = temp_f18;
    temp_r30->unk1C.y = sp44.y;
    var_f24 = fn_1_1D08(atan2d(temp_r30->unk10.x, temp_r30->unk10.z));
    var_f24 += temp_r31->unk38.y;
    var_f23 = sqrtf((temp_r30->unk10.x * temp_r30->unk10.x) + (temp_r30->unk10.z * temp_r30->unk10.z));
    temp_r30->unk10.x = (temp_r31->unk2C.x + (var_f23 * sind(var_f24)));
    temp_r30->unk10.y = 125.861f + temp_r31->unk2C.y;
    temp_r30->unk10.z = (temp_r31->unk2C.z + (var_f23 * cosd(var_f24)));
    Hu3DModelPosSet(temp_r31->unk6, temp_r30->unk10.x, temp_r30->unk10.y, temp_r30->unk10.z);
    Hu3DModelPosSet(temp_r31->unk8, temp_r30->unk10.x, -temp_r30->unk10.y, temp_r30->unk10.z);
    HuSetVecF(&sp68, temp_r31->unk2C.x, 0.0, temp_r31->unk2C.z);
    HuSetVecF(&sp5C, temp_f18, 0.0, sp44.y);
    HuSubVecF(&sp50, &sp68, &sp5C);
    var_f23 = sqrtf((sp50.x * sp50.x) + (sp50.z * sp50.z));
    sp40 = 1.0f;
    while (1) {
        for (var_r29 = 0, var_f19 = temp_r30->unk10.y, var_f22 = sp40; var_f22 > 0.0f; var_r29++) {
            var_f19 += var_f22;
            var_f22 -= 0.9f;
        }
        if (var_f19 >= (var_f23 / 2.0f))
            break;
        sp40++;
    }

    for (; var_f19 > 0.0f; var_r29++) {
        var_f19 += var_f22;
        var_f22 -= 0.9f;
    }
    temp_r30->unk24.z = sp40;
    temp_r30->unk24.x = fn_1_1D08(atan2d(temp_f18 - temp_r30->unk10.x, sp44.y - temp_r30->unk10.z));
    temp_r30->unk24.y = var_f23 / var_r29;

    while (Hu3DMotionEndCheck(temp_r31->unk0) == 0) {
        HuPrcVSleep();
    }
    goto loop_10;
}

void fn_1_3950(void)
{
    Vec sp8C;
    Vec sp80;
    Vec sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    volatile f32 sp58;
    f32 sp54;
    f32 temp_f27;
    f32 var_f29;
    f32 temp_f31;
    f32 temp_f30;
    f32 var_f18;
    f32 var_f19;
    f32 var_f20;
    f32 var_f21;
    f32 var_f22;
    f32 var_f23;
    f32 var_f24;
    s32 var_r28;
    s32 var_r24;
    s32 var_r25;
    s32 var_r29;
    s32 var_r26;
    unkStruct *temp_r30;
    unkStruct3 *temp_r27;
    unkStruct2 *temp_r31;
    s32 var_r23;
    Process *var_r22;

    temp_r31 = HuPrcCurrentGet()->user_data;
loop_1:
    var_r29 = lbl_1_bss_790 / REFRESH_RATE;
    if (var_r29 >= 0x3C) {
        var_r29 = 0x3C;
    }
    if (lbl_1_bss_794 >= 4) {
        while (1) {
            HuPrcVSleep();
        }
    }
    var_r24 = 1;
    if (var_r29 >= 0x20) {
        var_r24 = 0;
    }
    if (((1 << (var_r29 % 32)) & lbl_1_data_340[temp_r31->unk28][var_r24]) != 0) {
        var_r23 = fn_1_2708();
    }
    else {
        HuPrcVSleep();
        goto loop_1;
    }
    Hu3DModelAttrReset(temp_r31->unk0, HU3D_MOTATTR_PAUSE);
    Hu3DModelClusterAttrReset(temp_r31->unk0, 0, -0x3FFFFFFE);
    Hu3DModelAttrReset(temp_r31->unk2, HU3D_MOTATTR_PAUSE);
    Hu3DModelClusterAttrReset(temp_r31->unk2, 0, -0x3FFFFFFE);
    Hu3DModelAttrReset(temp_r31->unk6, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(temp_r31->unk8, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowDispOn(temp_r31->unk6);
    var_f18 = 850.0f;
    temp_f31 = -217.722f;
    temp_f30 = 0.0f;
    var_f29 = fn_1_1D08(atan2d(temp_f31, temp_f30));
    var_f29 += temp_r31->unk38.y;
    var_f24 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
    temp_f31 = (temp_r31->unk2C.x + (var_f24 * sind(var_f29)));
    temp_f30 = (temp_r31->unk2C.z + (var_f24 * cosd(var_f29)));
    sp64 = 5.0f;
    while (1) {
        var_f18 -= sp64;
        sp64 += 0.9f;
        if (sp64 > 20.0f) {
            sp64 = 20.0f;
        }
        if (var_f18 < (304.52f + temp_r31->unk2C.y)) {
            var_f18 = 304.52f + temp_r31->unk2C.y;
        }
        Hu3DModelPosSet(temp_r31->unk6, temp_f31, var_f18, temp_f30);
        Hu3DModelPosSet(temp_r31->unk8, temp_f31, -var_f18, temp_f30);
        if (var_f18 == (304.52f + temp_r31->unk2C.y))
            break;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(temp_r31->unk6, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(temp_r31->unk8, 0.0f, 0.0f, 0.0f);
    Hu3DModelHookSet(temp_r31->unk0, "itemhook", temp_r31->unk6);
    Hu3DModelHookSet(temp_r31->unk2, "itemhook", temp_r31->unk8);
    Hu3DMotionShiftSet(temp_r31->unk0, temp_r31->unkC[2], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unk16[2], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(10);

    while (Hu3DMotionEndCheck(temp_r31->unk0) == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(0xA);
    var_r26 = frandmod(4);
    if (lbl_1_bss_4D4[var_r26].unk30 == 3) {
        for (var_r25 = 3; var_r25 != 0; var_r25--) {
            var_r26 += 1;
            if (var_r26 >= 4) {
                var_r26 = 0;
            }
            if (lbl_1_bss_4D4[var_r26].unk30 != 3)
                break;
        }
    }
    temp_r27 = &lbl_1_bss_4D4[var_r26];
    Hu3DMotionSet(temp_r31->unk0, temp_r31->unkC[3]);
    Hu3DModelAttrReset(temp_r31->unk0, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(temp_r31->unk2, temp_r31->unk16[3]);
    Hu3DModelAttrReset(temp_r31->unk2, HU3D_MOTATTR_LOOP);
    var_r29 = Hu3DMotionMaxTimeGet(temp_r31->unk0);
    var_f29 = fn_1_1D08(atan2d(temp_r27->unk40.x - temp_r31->unk2C.x, temp_r27->unk40.z - temp_r31->unk2C.z));
    sp6C = (temp_r27->unk40.x + (50.0 * sind(var_f29)));
    sp68 = (temp_r27->unk40.z + (50.0 * cosd(var_f29)));
    sp60 = 360.0f * frandf();
    var_f24 = 50.0f * frandf();
    sp6C += (var_f24 * sind(sp60));
    sp68 += (var_f24 * cosd(sp60));
    sp70 = fn_1_27C4(var_r29, var_f29, temp_r31->unk38.y);
    HuAudFXPlay(0x587);

    for (; var_r29 != 0; var_r29--) {
        temp_r31->unk38.y += sp70;
        Hu3DModelRotSet(temp_r31->unk0, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        Hu3DModelRotSet(temp_r31->unk2, temp_r31->unk38.x, temp_r31->unk38.y, temp_r31->unk38.z);
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    Hu3DMotionShiftSet(temp_r31->unk0, temp_r31->unkC[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unk16[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(10);

    while (Hu3DMotionTimeGet(temp_r31->unk0) < 24.0f) {
        HuPrcVSleep();
    }
    Hu3DModelHookReset(temp_r31->unk0);
    Hu3DModelHookReset(temp_r31->unk2);
    HuAudFXPlay(0x586);
    temp_r30 = lbl_1_bss_278[var_r23];
    temp_r30->unk6 = var_r23;
    temp_r30->unkA = 0;
    var_r22 = HuPrcChildCreate(fn_1_2064, 0x1000, 0x3000, 0, HuPrcCurrentGet());
    var_r22->user_data = temp_r30;
    temp_r30->unkC = 1;
    temp_r30->unk0 = temp_r31->unk6;
    temp_r30->unk2 = temp_r31->unk8;
    temp_r30->unk4 = temp_r31->unkA;
    temp_r30->unk30 = 100.0f;
    temp_r30->unk10.x = -217.722f;
    temp_r30->unk10.y = 404.52f;
    temp_r30->unk10.z = 0.0f;
    var_f29 = fn_1_1D08(atan2d(temp_r30->unk10.x, temp_r30->unk10.z));
    var_f29 += temp_r31->unk38.y;
    var_f24 = sqrtf((temp_r30->unk10.x * temp_r30->unk10.x) + (temp_r30->unk10.z * temp_r30->unk10.z));
    temp_r30->unk10.x = (temp_r31->unk2C.x + (var_f24 * sind(var_f29)));
    temp_r30->unk10.y = (404.52f + temp_r31->unk2C.y) - 100.0f;
    temp_r30->unk10.z = (temp_r31->unk2C.z + (var_f24 * cosd(var_f29)));
    Hu3DModelPosSet(temp_r31->unk6, temp_r30->unk10.x, temp_r30->unk10.y, temp_r30->unk10.z);
    Hu3DModelPosSet(temp_r31->unk8, temp_r30->unk10.x, -temp_r30->unk10.y, temp_r30->unk10.z);
    HuSetVecF(&sp8C, temp_r31->unk2C.x, 0.0, temp_r31->unk2C.z);
    HuSetVecF(&sp80, sp6C, 0.0, sp68);
    HuSubVecF(&sp74, &sp8C, &sp80);
    var_f24 = sqrtf((sp74.x * sp74.x) + (sp74.z * sp74.z));
    sp54 = 1.0f;

    while (1) {
        for (var_r29 = 0, sp5C = temp_r30->unk10.y, sp58 = sp54; sp58 > 0.0f; var_r29++) {
            sp5C += sp58;
            sp58 -= 0.9f;
        }
        if (sp5C >= 600.0f)
            break;
        sp54++;
    }
    for (; sp5C > 0.0f; var_r29++) {
        sp5C += sp58;
        sp58 -= 0.9f;
    }
    temp_r30->unk24.z = sp54;
    temp_r30->unk24.x = fn_1_1D08(atan2d((sp6C - temp_r30->unk10.x), (sp68 - temp_r30->unk10.z)));
    temp_r30->unk24.y = var_f24 / var_r29;
    while (Hu3DMotionEndCheck(temp_r31->unk0) == 0) {
        HuPrcVSleep();
    }
    goto loop_1;
}

s8 fn_1_4BE4(s32 arg0, s32 arg1)
{
    s8 var_r30;
    unkStruct3 *temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        (arg1 != 0) ? (var_r30 = HuPadStkY[temp_r31->unk2C]) : (var_r30 = HuPadStkX[temp_r31->unk2C]);
    }
    else {
        (arg1 != 0) ? (var_r30 = temp_r31->unk89) : (var_r30 = temp_r31->unk88);
    }
    return var_r30;
}

void fn_1_4C9C(Vec *arg0, f32 arg8, f32 arg9)
{
    f32 temp_f29;

    temp_f29 = sqrtf((arg0->x * arg0->x) + (arg0->z * arg0->z));
    temp_f29 *= arg9;
    arg0->x = (temp_f29 * sind(arg8));
    arg0->z = (temp_f29 * cosd(arg8));
}

s8 fn_1_4E58(s32 arg0, s32 arg1)
{
    Vec spC;
    f32 temp_f28;
    s8 var_r30;
    s8 temp_r29;
    s8 temp_r28;
    unkStruct3 *temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        temp_r29 = HuPadStkX[temp_r31->unk2C];
        temp_r28 = HuPadStkY[temp_r31->unk2C];
        temp_f28 = fn_1_1D08(atan2d(temp_r29, temp_r28));
        temp_f28 -= lbl_1_bss_778;
        HuSetVecF(&spC, (f32)temp_r29, 0.0, (f32)temp_r28);
        fn_1_4C9C(&spC, temp_f28, 1.0f);
        (arg1 != 0) ? (var_r30 = spC.z) : (var_r30 = spC.x);
    }
    else {
        (arg1 != 0) ? (var_r30 = temp_r31->unk89) : (var_r30 = temp_r31->unk88);
    }
    return var_r30;
}

u8 fn_1_525C(s32 arg0, s32 arg1)
{
    s8 var_r30;
    unkStruct3 *temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        (arg1 != 0) ? (var_r30 = HuPadTrigR[temp_r31->unk2C]) : (var_r30 = HuPadTrigL[temp_r31->unk2C]);
    }
    else {
        (arg1 != 0) ? (var_r30 = temp_r31->unk8A) : (var_r30 = temp_r31->unk8B);
    }
    return var_r30;
}

u16 fn_1_531C(s32 arg0)
{
    u16 var_r30;
    unkStruct3 *temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        var_r30 = HuPadBtnDown[temp_r31->unk2C];
    }
    else {
        var_r30 = temp_r31->unk8E;
    }
    return var_r30;
}

u16 fn_1_5388(s32 arg0)
{
    u16 var_r30;
    unkStruct3 *temp_r31;

    temp_r31 = &lbl_1_bss_4D4[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        var_r30 = HuPadBtn[temp_r31->unk2C];
    }
    else {
        var_r30 = temp_r31->unk8C;
    }
    return var_r30;
}

s32 fn_1_53F4(unkStruct3 *arg0, f32 arg8, f32 arg9, f32 argA)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    unkStruct3 *temp_r31;
    s32 var_r30;
    s32 var_r28;
    f32 var_f27;
    f32 var_f28;

    var_r28 = -1;

    for (var_r30 = 0, var_f28 = 10000.0f; var_r30 < 4; var_r30++) {
        if (var_r30 != arg0->unk24) {
            temp_r31 = &lbl_1_bss_4D4[var_r30];
            HuSetVecF(&sp30, arg8, arg9, argA);
            HuSetVecF(&sp24, temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z);
            HuSubVecF(&sp18, &sp30, &sp24);
            if (((var_f27 = sqrtf((sp18.z * sp18.z) + ((sp18.x * sp18.x) + (sp18.y * sp18.y)))) < (arg0->unk60.x + temp_r31->unk60.x))
                && (var_f27 < var_f28)) {
                var_f28 = var_f27;
                var_r28 = var_r30;
                arg0->unkA4 = 0;
            }
        }
    }
    return var_r28;
}

s32 fn_1_561C(unkStruct3 *arg0, s32 *arg1)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    f32 var_f27;
    f32 var_f28;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    unkStruct3 *temp_r30;

    var_r27 = -1;
    var_r29 = 0;
    var_f28 = 10000.0f;
    var_r28 = 0;

    for (; var_r29 < 4; var_r29++) {
        if (var_r29 != arg0->unk24) {
            temp_r30 = &lbl_1_bss_4D4[var_r29];
            HuSetVecF(&sp24, arg0->unk40.x, arg0->unk40.y, arg0->unk40.z);
            HuSetVecF(&sp18, temp_r30->unk40.x, temp_r30->unk40.y, temp_r30->unk40.z);
            HuSubVecF(&spC, &sp24, &sp18);
            if ((var_f27 = sqrtf((spC.z * spC.z) + ((spC.x * spC.x) + (spC.y * spC.y)))) < (arg0->unk60.x + temp_r30->unk60.x)) {
                var_r28 += 1;
                if (var_f27 < var_f28) {
                    var_f28 = var_f27;
                    var_r27 = var_r29;
                    arg0->unkA4 = 0;
                }
            }
        }
    }
    *arg1 = var_r28;
    return var_r27;
}

void fn_1_5838(unkStruct3 *arg0)
{
    Vec spA8;
    Vec sp9C;
    Vec sp90;
    Vec sp84;
    Vec sp78;
    Vec sp6C;
    s32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 var_f20;
    f32 var_f25;
    f32 var_f27;
    f32 var_f26;
    s32 var_r25;
    s32 var_r29;
    unkStruct3 *temp_r27;
    unkStruct3 *var_r30;
    s32 var_r24;

    var_r24 = fn_1_561C(arg0, &sp68);
    if (var_r24 != -1) {
        var_f20 = fn_1_1D08(atan2d((arg0->unk40.x - arg0->unk4C.x), (arg0->unk40.z - arg0->unk4C.y)));
        sp58 = var_f27 = arg0->unk4C.x;
        sp54 = var_f26 = arg0->unk4C.y;
        sp4C = 1.0f;
        var_r25 = (1.0f + (10.0f / sp4C));

        while (var_r25 != 0) {
            var_f27 += sp4C * sind(var_f20);
            var_f26 += sp4C * cosd(var_f20);
            HuSetVecF(&spA8, var_f27, arg0->unk40.y, var_f26);

            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                if (var_r29 == arg0->unk24)
                    continue;
                var_r30 = &lbl_1_bss_4D4[var_r29];
                HuSetVecF(&sp9C, var_r30->unk40.x, var_r30->unk40.y, var_r30->unk40.z);
                HuSubVecF(&sp90, &spA8, &sp9C);
                if (sqrtf((sp90.z * sp90.z) + ((sp90.x * sp90.x) + (sp90.y * sp90.y))) < (arg0->unk60.x + var_r30->unk60.x))
                    break;
            }
            if (var_r29 < 4)
                break;
            AddX = 0.0f;
            AddZ = 0.0f;
            MapWall(arg0->unk60.x, var_f27, arg0->unk40.y + arg0->unk60.x, var_f26);
            if ((AddX + AddZ) != 0.0f)
                goto end;
            sp58 = var_f27;
            sp54 = var_f26;
            var_r25--;
        }
        var_f20 = fn_1_1D08(atan2d((arg0->unk40.x - arg0->unk4C.x), (arg0->unk40.z - arg0->unk4C.y)));
        var_f25 = fn_1_1D08(atan2d((var_r30->unk40.x - arg0->unk4C.x), (var_r30->unk40.z - arg0->unk4C.y)));
        sp60 = var_f20 - var_f25;
        if (sp60 > 0.0f) {
            sp5C = -0.5f;
        }
        else {
            sp5C = 0.5f;
        }
        if (ABS_INV(var_f20 - var_f25) > 180.0f) {
            sp5C = -sp5C;
        }
        var_f25 = fn_1_1D08(atan2d((arg0->unk4C.x - var_r30->unk40.x), (arg0->unk4C.y - var_r30->unk40.z)));
        sp50 = 0.8f * arg0->unk60.y;
        var_r24 = var_r30->unk24;
        sp64 = 1.0f + (arg0->unk60.x + var_r30->unk60.x);
        while (1) {
            var_f27 = (var_r30->unk40.x + (sp64 * sind(var_f25)));
            var_f26 = (var_r30->unk40.z + (sp64 * cosd(var_f25)));
            HuSetVecF(&spA8, var_f27, 0.0, var_f26);

            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                if ((var_r29 == arg0->unk24) || (var_r29 == var_r24))
                    continue;
                temp_r27 = &lbl_1_bss_4D4[var_r29];
                HuSetVecF(&sp9C, temp_r27->unk40.x, 0.0, temp_r27->unk40.z);
                HuSubVecF(&sp90, &spA8, &sp9C);
                if (sqrtf((sp90.x * sp90.x) + (sp90.z * sp90.z)) < (arg0->unk60.x + temp_r27->unk60.x))
                    break;
            }
            if (var_r29 < 4)
                break;
            AddX = 0.0f;
            AddZ = 0.0f;
            MapWall(arg0->unk60.x, var_f27, arg0->unk40.y + arg0->unk60.x, var_f26);
            if ((AddX + AddZ) != 0.0f)
                break;
            sp58 = var_f27;
            sp54 = var_f26;
            HuSetVecF(&spA8, arg0->unk4C.x, 0.0, arg0->unk4C.y);
            HuSetVecF(&sp9C, var_f27, 0.0, var_f26);
            HuSubVecF(&sp90, &spA8, &sp9C);
            if (sqrtf((sp90.x * sp90.x) + (sp90.z * sp90.z)) > sp50)
                break;
            var_f25 += sp5C;
        }
    end:
        arg0->unk40.x = sp58;
        arg0->unk40.z = sp54;
    }
}

f32 fn_1_6594(f32 arg8, f32 arg9, f32 argA)
{
    f32 var_f31;
    f32 var_f30;

    var_f31 = fmod((arg9 - arg8), 360.0);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod((arg8 + (var_f31 * argA)), 360.0);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

f32 fn_1_6698(f32 arg8, f32 arg9, unkStruct3 *arg0)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;

    HuSetVecF(&sp2C, arg8, 0.0, arg9);
    HuSetVecF(&sp20, arg0->unk40.x, 0.0, arg0->unk40.z);
    HuSubVecF(&sp14, &sp2C, &sp20);
    return sqrtf((sp14.x * sp14.x) + (sp14.z * sp14.z));
}

static inline void PadInline(void)
{
    float var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
    (void)var_f27;
}

void fn_1_6814(unkStruct3 *arg0)
{
    Vec sp104;
    Vec spF8;
    Vec spEC;
    volatile f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 var_f27; // probably debug code
    f32 var_f18;
    f32 temp_f31;
    f32 temp_f30;
    f32 var_f29;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    unkStruct *temp_r27;
    s32 var_r28;
    unkStruct3 *temp_r29;
    unkStruct *var_r30;

    arg0->unk88 = arg0->unk89 = 0;
    arg0->unk8B = arg0->unk8A = 0;
    arg0->unk8C = arg0->unk8E = 0;

    switch (GWPlayerCfg[arg0->unk24].diff) {
        case 0:
            var_r22 = 0x3C;
            break;
        case 1:
            var_r22 = 0x50;
            break;
        case 2:
            var_r22 = 0x5A;
            break;
        default:
            var_r22 = 0x5F;
            break;
    }
    switch (GWPlayerCfg[arg0->unk24].diff) {
        case 0:
            spA0 = 200.0f;
            break;
        case 1:
            spA0 = 250.0f;
            break;
        case 2:
            spA0 = 300.0f;
            break;
        default:
            spA0 = 350.0f;
            break;
    }

    for (var_r28 = 0, sp98 = 10000.0f; var_r28 < 0x20; var_r28++) {
        temp_r27 = lbl_1_bss_278[var_r28];
        if (temp_r27 && (temp_r27->unk6 != -1)) {
            HuSetVecF(&sp104, arg0->unk40.x, 0.0, arg0->unk40.z);
            HuSetVecF(&spF8, temp_r27->unk10.x, 0.0, temp_r27->unk10.z);
            HuSubVecF(&spEC, &sp104, &spF8);
            var_f29 = sqrtf((spEC.z * spEC.z) + ((spEC.x * spEC.x) + (spEC.y * spEC.y)));
            if ((var_f29 < (spA0 + (arg0->unk60.x + temp_r27->unk30))) && (sp98 > var_f29)) {
                var_r30 = temp_r27;
                sp98 = var_f29;
            }
        }
    }
    if (sp98 < 10000.0f) {
        arg0->unk9C = 0;
        var_r21 = 1;
        if (arg0->unkA0 != var_r30->unk6) {
            if (frandmod(0x64) < 0) {
                (void)var_r21; // probably debug code
                PadInline();
            }
            else {
                (void)var_r21;
            }
        }
        if (var_r21 != 0) {
            sp9C = 200.0f + (var_r30->unk30 + arg0->unk60.x) + (100.0f * frandf());
            sp104.x = temp_f31 = (var_r30->unk10.x + (sp9C * sind(var_r30->unk24.x + 90.0f)));
            sp104.z = temp_f30 = (var_r30->unk10.z + (sp9C * cosd(var_r30->unk24.x + 90.0f)));
            var_f29 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
            spF8.x = temp_f31 = (var_r30->unk10.x + (sp9C * sind(var_r30->unk24.x - 90.0f)));
            spF8.z = temp_f30 = (var_r30->unk10.z + (sp9C * cosd(var_r30->unk24.x - 90.0f)));
            spA0 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
            if (sqrtf((arg0->unk40.x * arg0->unk40.x) + (arg0->unk40.z * arg0->unk40.z)) < 400.0f) {
                spEC.x = var_f29;
                var_f29 = spA0;
                spA0 = spEC.x;
            }
            if (var_f29 > spA0) {
                spEC.x = spF8.x;
                spEC.z = spF8.z;
            }
            else {
                spEC.x = sp104.x;
                spEC.z = sp104.z;
            }
            if (arg0->unkA0 != var_r30->unk6) {
                arg0->unkA0 = var_r30->unk6;
                arg0->unk90.x = spEC.x;
                arg0->unk90.y = spEC.z;
            }

            var_f18 = atan2d((arg0->unk90.x - arg0->unk40.x), (arg0->unk90.y - arg0->unk40.z));

            if (fn_1_53F4(arg0, arg0->unk40.x + arg0->unk7C.x, arg0->unk40.y, arg0->unk40.z + arg0->unk7C.z) != -1) {
                var_f18 += 90.0f;
            }
            arg0->unk88 = 50.0 * sind(var_f18);
            arg0->unk89 = -50.0f * cosd(var_f18);
        }
    }
    else {
        if (arg0->unk9C == 0) {
            arg0->unk9C = 1;
            arg0->unk98 = (250.0f + (90.0f * frandf()));
            arg0->unkA4 = 30;
        }
        if ((sqrtf((arg0->unk40.x * arg0->unk40.x) + (arg0->unk40.z * arg0->unk40.z)) > arg0->unk98) && (arg0->unkA4 != 0)) {
            arg0->unkA4--;
            var_f18 = (180.0 + (atan2d(arg0->unk40.x, arg0->unk40.z)));
            if (fn_1_53F4(arg0, arg0->unk40.x + arg0->unk7C.x, arg0->unk40.y, arg0->unk40.z + arg0->unk7C.z) != -1) {
                arg0->unkA4 = 0;
                var_f18 += 90.0f;
            }
            arg0->unk88 = 25.0 * sind(var_f18);
            arg0->unk89 = -25.0 * cosd(var_f18);
            return;
        }
        var_r28 = 0;
        sp98 = 10000.0f;
        var_r20 = -1;

        for (; var_r28 < 4; var_r28++) {
            if (var_r28 != arg0->unk24) {
                temp_r29 = &lbl_1_bss_4D4[var_r28];
                HuSetVecF(&sp104, arg0->unk40.x, 0.0, arg0->unk40.z);
                HuSetVecF(&spF8, temp_r29->unk40.x, 0.0, temp_r29->unk40.z);
                HuSubVecF(&spEC, &sp104, &spF8);
                var_f29 = sqrtf((spEC.z * spEC.z) + ((spEC.x * spEC.x) + (spEC.y * spEC.y)));
                if (var_f29 < sp98) {
                    var_r20 = var_r28;
                    sp98 = var_f29;
                }
            }
        }
        if (var_r20 != -1) {
            temp_r29 = &lbl_1_bss_4D4[var_r20];
            HuSetVecF(&sp104, arg0->unk40.x, 0.0, arg0->unk40.z);
            HuSetVecF(&spF8, temp_r29->unk40.x, 0.0, temp_r29->unk40.z);
            HuSubVecF(&spEC, &sp104, &spF8);
            var_f29 = sqrtf((spEC.x * spEC.x) + (spEC.z * spEC.z));
            if ((var_f29 < 200.0f) && (var_f29 > 150.0f)) {
                var_f18 = atan2d((arg0->unk40.x - temp_r29->unk40.x), (arg0->unk40.z - temp_r29->unk40.z));
                (void)var_f29;
                arg0->unk88 = 30.0f * sind(var_f18);
                arg0->unk89 = -30.0f * cosd(var_f18);
            }
        }
    }
}

void fn_1_7C60(void)
{
    Vec sp1A0;
    Vec sp188;
    Vec sp17C;
    Vec sp170;
    Vec sp164;
    Vec sp158;
    Vec sp14C;
    Vec sp140;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    f32 sp12C;
    f32 temp_f20;
    f32 var_f21;
    f32 var_f31;
    s32 var_r27;
    unkStruct3 *temp_r30;
    unkStruct3 *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk30 = 0;
    temp_r31->unk9C = 0;
    temp_r31->unkA0 = -1;

    while (lbl_1_bss_794 == 0) {
        HuPrcVSleep();
    }

    lbl_1_bss_794 = 2;
    while (lbl_1_bss_794 == 2) {
        HuPrcVSleep();
    }
loop_6:
    temp_r31->unk4C.x = temp_r31->unk40.x;
    temp_r31->unk4C.y = temp_r31->unk40.z;
    if (GWPlayerCfg[temp_r31->unk24].iscom == 1) {
        fn_1_6814(temp_r31);
    }
    switch (temp_r31->unk30) {
        default:
            HuSetVecF(&sp1A0, fn_1_4E58(temp_r31->unk24, 0) / 4.0f, 0.0, -fn_1_4E58(temp_r31->unk24, 1) / 4.0f);
            temp_r31->unk60.z = sqrtf((sp1A0.z * sp1A0.z) + ((sp1A0.x * sp1A0.x) + (sp1A0.y * sp1A0.y)));
            if (temp_r31->unk60.z >= 0.5f) {
                if (temp_r31->unk60.z >= 10.0f) {
                    sp1A0.x /= temp_r31->unk60.z;
                    sp1A0.z /= temp_r31->unk60.z;
                    temp_r31->unk60.z = 10.0f;
                    sp1A0.x = 10.0f * sp1A0.x;
                    sp1A0.z = 10.0f * sp1A0.z;
                }
                temp_r31->unk54.y = fn_1_6594(temp_r31->unk54.y, atan2d(sp1A0.x, sp1A0.z), 0.4f);
                if (temp_r31->unk60.z >= 8.0f) {
                    if (temp_r31->unk30 != 2) {
                        temp_r31->unk30 = 2;
                        CharModelMotionShiftSet(
                            lbl_1_data_0[GWPlayerCfg[temp_r31->unk24].character], temp_r31->unkC[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                        Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unk18[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    }
                }
                else if (temp_r31->unk30 != 1) {
                    temp_r31->unk30 = 1;
                    CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk24].character], temp_r31->unkC[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unk18[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
                temp_r31->unk7C.x += 0.1f * sp1A0.x;
                temp_r31->unk7C.z += 0.1f * sp1A0.z;
            }
            else if (temp_r31->unk30 != 0) {
                temp_r31->unk30 = 0;
                CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk24].character], temp_r31->unkC[0]);
                Hu3DModelAttrSet(temp_r31->unk0, HU3D_MOTATTR_LOOP);
                Hu3DMotionSet(temp_r31->unk2, temp_r31->unk18[0]);
                Hu3DMotionSpeedSet(temp_r31->unk2, 2.0f);
                Hu3DModelAttrSet(temp_r31->unk2, HU3D_MOTATTR_LOOP);
            }
            var_f21 = sqrtf((temp_r31->unk7C.x * temp_r31->unk7C.x) + (temp_r31->unk7C.z * temp_r31->unk7C.z));
            if (temp_r31->unk60.z > 0.5f) {
                if (var_f21 > 0.25f) {
                    var_f21 -= 0.25f;
                }
            }
            else {
                var_f21 -= 0.25f;
            }
            if (var_f21 < 0.0f) {
                HuSetVecF(&temp_r31->unk7C, 0.0, 0.0, 0.0);
                var_f21 = 0.0f;
            }
            else {
                if (var_f21 > 10.0f) {
                    var_f21 = 10.0f;
                }
                sp13C = fn_1_1D08(atan2d(temp_r31->unk7C.x, temp_r31->unk7C.z));
                HuSetVecF(&temp_r31->unk7C, (var_f21 * sind(sp13C)), 0.0, (var_f21 * cosd(sp13C)));
            }
            temp_r31->unk60.y = var_f21;
            temp_r31->unk40.x += temp_r31->unk7C.x;
            temp_r31->unk40.z += temp_r31->unk7C.z;
            if ((temp_r31->unk38 = fn_1_53F4(temp_r31, temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z)) != -1) {
                temp_r30 = &lbl_1_bss_4D4[temp_r31->unk38];
                if (temp_r30->unk30 != 3) {
                    var_f31 = atan2d((temp_r30->unk40.x - temp_r31->unk40.x), (temp_r30->unk40.z - temp_r31->unk40.z));
                    temp_f20 = atan2d(temp_r31->unk7C.x, temp_r31->unk7C.z);
                    var_f31 = ABS_INV(var_f31 - temp_f20);
                    if (var_f31 > 180.0f) {
                        var_f31 = 360.0f - var_f31;
                    }
                    sp138 = var_f31 / 90.0f;
                    var_f31 = atan2d((temp_r31->unk40.x - temp_r30->unk40.x), (temp_r31->unk40.z - temp_r30->unk40.z));
                    temp_f20 = atan2d(temp_r31->unk7C.x, temp_r31->unk7C.z);
                    temp_f20 = fn_1_1D08(180.0f + temp_f20);
                    temp_f20 = fn_1_1D08(var_f31 - (temp_f20 - var_f31));
                    var_f31 = fn_1_1D08(atan2d((temp_r30->unk40.x - temp_r31->unk40.x), (temp_r30->unk40.z - temp_r31->unk40.z)));
                    HuSetVecF(&sp1A0, temp_r31->unk7C.x, 0.0, temp_r31->unk7C.z);
                    fn_1_4C9C(&sp1A0, var_f31, 1.0f - sp138);
                    HuSetVecF(&temp_r30->unk7C, sp1A0.x, 0.0, sp1A0.z);
                    HuSetVecF(&sp1A0, temp_r31->unk7C.x, 0.0, temp_r31->unk7C.z);
                    fn_1_4C9C(&sp1A0, temp_f20, sp138);
                    HuSetVecF(&temp_r31->unk7C, sp1A0.x, 0.0, sp1A0.z);
                }
                fn_1_5838(temp_r31);
            }
            while (1) {
                AddX = 0.0f;
                AddZ = 0.0f;
                MapWall(temp_r31->unk60.x, temp_r31->unk40.x, temp_r31->unk40.y + temp_r31->unk60.x, temp_r31->unk40.z);
                temp_r31->unk40.x += AddX;
                temp_r31->unk40.z += AddZ;
                if ((temp_r31->unk38 = fn_1_53F4(temp_r31, temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z)) == -1)
                    break;
                temp_r31->unk40.x = temp_r31->unk4C.x;
                temp_r31->unk40.z = temp_r31->unk4C.y;
            }
            Hu3DModelPosSet(temp_r31->unk0, temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z);
            Hu3DModelRotSet(temp_r31->unk0, temp_r31->unk54.x, temp_r31->unk54.y, temp_r31->unk54.z);
            Hu3DModelPosSet(temp_r31->unk2, temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z);
            Hu3DModelRotSet(temp_r31->unk2, temp_r31->unk54.x, temp_r31->unk54.y, temp_r31->unk54.z);
            HuPrcVSleep();
            goto loop_6;
        case 3:
            HuAudFXPlay(0x584);
            Hu3DModelAttrSet(temp_r31->unk0, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(temp_r31->unk2, HU3D_MOTATTR_PAUSE);
            Hu3DModelPosSet(temp_r31->unkA, temp_r31->unk40.x + (100.0 * sind(lbl_1_bss_778)), 200.0f + temp_r31->unk40.y,
                temp_r31->unk40.z + (100.0 * cosd(lbl_1_bss_778)));
            Hu3DModelAttrReset(temp_r31->unkA, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(temp_r31->unkA, HU3D_MOTATTR_PAUSE);
            HuPrcSleep(10);
            Hu3DModelAttrSet(temp_r31->unk0, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(temp_r31->unk2, HU3D_MOTATTR_PAUSE);
            HuPrcSleep(10);
            Hu3DModelPosSet(temp_r31->unk6, temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z);
            Hu3DModelPosSet(temp_r31->unk8, temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z);
            Hu3DModelAttrReset(temp_r31->unk6, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(temp_r31->unk8, HU3D_ATTR_DISPOFF);
            Hu3DModelShadowDispOn(temp_r31->unk6);

            for (sp134 = 0.0f, sp130 = 1.0f; sp134 < 1; sp134 += 0.05f, sp130 -= 0.1f) {
                Hu3DModelScaleSet(temp_r31->unk6, 1.0f, sp134, 1.0f);
                Hu3DModelScaleSet(temp_r31->unk8, 1.0f, -sp134, 1.0f);
                if (sp130 > 0.0f) {
                    Hu3DModelAmbSet(temp_r31->unk0, sp130, sp130, 1.0f);
                }
                HuPrcVSleep();
            }
            Hu3DModelScaleSet(temp_r31->unk6, 1.0f, 1.0f, 1.0f);
            Hu3DModelScaleSet(temp_r31->unk8, 1.0f, -1.0f, 1.0f);
            while (1) {
                HuPrcVSleep();
            }
        case 4:
            CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk24].character], temp_r31->unkC[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
            Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unk18[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
            var_r27 = 30;
            sp12C = fn_1_27C4(var_r27, lbl_1_bss_778, temp_r31->unk54.y);

            for (; var_r27 != 0; var_r27--) {
                temp_r31->unk54.y += sp12C;
                Hu3DModelRotSet(temp_r31->unk0, temp_r31->unk54.x, temp_r31->unk54.y, temp_r31->unk54.z);
                Hu3DModelRotSet(temp_r31->unk2, temp_r31->unk54.x, temp_r31->unk54.y, temp_r31->unk54.z);
                HuPrcVSleep();
            }
            while (lbl_1_bss_794 < 5) {
                HuPrcVSleep();
            }
            CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk24].character], temp_r31->unkC[5], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
            Hu3DMotionShiftSet(temp_r31->unk2, temp_r31->unk18[5], 0.0f, 5.0f, HU3D_MOTATTR_NONE);

            while (1) {
                HuPrcVSleep();
            }
    }
}

void fn_1_A01C(ModelData *model, ParticleData *particle, f32 (*matrix)[4])
{
    HsfanimStruct01 *var_r31;
    f32 var_f29;
    f32 var_f28;
    f32 var_f30;
    f32 var_f31;
    s16 var_r25;
    s16 var_r24;
    s16 var_r26;
    s16 var_r28;
    s32 var_r27;
    unkStruct *temp_r30;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;

    for (var_r26 = 0; var_r26 < 0x20; var_r26++) {
        temp_r30 = lbl_1_bss_278[var_r26];
        if (temp_r30 && (temp_r30->unkA != 0)) {
            for (var_r25 = 0, var_f30 = 0.0f; var_r25 < 4; var_r25++, var_f30 += 45.0f) {
                for (var_r24 = 0, var_f31 = 0.0f; var_r24 < 8; var_r24++, var_f31 += 45.0f) {
                    for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
                        if (var_r31->unk14.x == 0.0f)
                            break;
                    }
                    if (var_r28 == particle->unk_30)
                        break;
                    if (temp_r30->unkC == 1) {
                        var_f29 = 2.0f + (2.0f * frandf());
                        var_f28 = 10.0f;
                    }
                    else {
                        var_f29 = 1.0f + frandf();
                        var_f28 = 3.0f;
                    }
                    var_r31->unk34.x = temp_r30->unk10.x + (var_f29 * (sind(var_f30) * cosd(var_f31)));
                    var_r31->unk34.y = temp_r30->unk10.y + (var_f29 * sind(var_f31));
                    var_r31->unk34.z = (temp_r30->unk10.z + (var_f29 * (cosd(var_f30) * cosd(var_f31))));
                    var_r31->unk08.x = (var_f28 * (sind(var_f30) * cosd(var_f31)));
                    var_r31->unk08.y = (var_f28 * sind(var_f31));
                    var_r31->unk08.z = (var_f28 * (cosd(var_f30) * cosd(var_f31)));
                    var_r31->unk14.x = 30.0f;
                    if (temp_r30->unkC == 1) {
                        var_r31->unk2C = 20.0f + (2.0f * frandf());
                        var_r31->unk14.y = 0.0f;
                    }
                    else {
                        var_r31->unk2C = 15.0f;
                        var_r31->unk14.y = 0.0f;
                    }
                    var_r31->unk40.a = 0xFF;
                    var_r31->unk14.z = 20.0f;
                }
            }
            temp_r30->unkA++;
        }
    }
    var_r31 = particle->unk_48;
    for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
        if (var_r31->unk14.x != 0.0f) {
            VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
            var_r31->unk08.x *= 0.95f;
            var_r31->unk08.z *= 0.95f;
            var_r31->unk08.y -= 0.2f;
            var_r31->unk2C += var_r31->unk14.y;
            var_r27 = var_r31->unk40.a;
            var_r27 -= var_r31->unk14.z;
            if (var_r31->unk14.z > 3.0f) {
                var_r31->unk14.z -= 1.0f;
            }
            if (var_r27 < 0) {
                var_r27 = 0;
                var_r31->unk14.x = 0.0f;
            }
            var_r31->unk40.a = var_r27;
            if (var_r31->unk14.x == 0.0f) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}

void fn_1_A618(ModelData *model, ParticleData *particle, f32 (*matrix)[4])
{
    HsfanimStruct01 *var_r31;
    f32 var_f31;
    f32 var_f30;
    f32 var_f29;
    f32 var_f28;
    s16 var_r26;
    s16 var_r25;
    s16 var_r29;
    s32 var_r27;
    unkStruct *temp_r28;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;

        for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;

    for (var_r26 = 0; var_r26 < 0x20; var_r26++) {
        temp_r28 = lbl_1_bss_278[var_r26];
        if (temp_r28 && (temp_r28->unkA != 0)) {

            for (var_r25 = 0, var_f28 = 0.0f; var_r25 < 9; var_r25++, var_f28 += 45.0f) {
                for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
                    if (var_r31->unk14.x == 0.0f)
                        break;
                }
                if (var_r29 == particle->unk_30)
                    break;
                var_f31 = var_f28;
                if (var_r25 < 8) {
                    var_f30 = 1.0f + frandf();
                    var_f29 = 2.0f;
                }
                else {
                    var_f30 = var_f29 = 0.0f;
                }
                var_r31->unk34.x = temp_r28->unk10.x + (var_f30 * sind(var_f31));
                var_r31->unk34.y = temp_r28->unk10.y + (10.0f * frandf());
                var_r31->unk34.z = temp_r28->unk10.z + (var_f30 * cosd(var_f31));
                var_r31->unk08.x = var_f29 * sind(var_f31);
                var_r31->unk08.y = -1.0f + frandf();
                var_r31->unk08.z = var_f29 * cosd(var_f31);
                var_r31->unk14.x = 30.0f;
                var_r31->unk2C = 15.0f;
                var_r31->unk14.y = 1.5f;
                var_r31->unk40.a = 0xC8;
                var_r31->unk14.z = 17.0f;
            }
            temp_r28->unkA = 0;
        }
    }
    var_r31 = particle->unk_48;
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (0.0f != var_r31->unk14.x) {
            VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
            var_r31->unk08.x *= 0.95f;
            var_r31->unk08.z *= 0.95f;
            var_r31->unk08.y -= 0.2f;
            var_r31->unk2C += var_r31->unk14.y;
            var_r27 = var_r31->unk40.a;
            var_r27 -= var_r31->unk14.z;
            if (var_r31->unk14.z > 3.0f) {
                var_r31->unk14.z -= 1.0f;
            }
            if (var_r27 < 0) {
                var_r27 = 0;
                var_r31->unk14.x = 0.0f;
            }
            var_r31->unk40.a = var_r27;
            if (0.0f == var_r31->unk14.x) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}

void fn_1_AA88(ModelData *model, ParticleData *particle, f32 (*matrix)[4])
{
    HsfanimStruct01 *var_r31;
    f32 var_f31;
    s16 var_r27;
    s16 var_r28;
    unkStruct2 *temp_r29;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;

        for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;

    for (var_r27 = 0; var_r27 < 6; var_r27++) {
        temp_r29 = &lbl_1_bss_33C[var_r27];
        if (temp_r29->unk20 == 0)
            continue;
        for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
            if (var_r31->unk14.x == 0.0f)
                break;
        }
        if (var_r28 == particle->unk_30)
            break;
        var_r31->unk34.x = temp_r29->unk2C.x + (-100.0 * cosd(temp_r29->unk38.y));
        var_r31->unk34.y = 98.0f + temp_r29->unk2C.y;
        var_r31->unk34.z = temp_r29->unk2C.z + (100.0 * sind(temp_r29->unk38.y));
        var_r31->unk14.x = 30.0f;
        var_r31->unk2C = 80.0f;
        var_r31->unk14.y = 5.0f;
        var_r31->unk40.a = 0xC8;
        var_r31->unk14.z = 17.0f;
        temp_r29->unk20 = 0;
    }
    var_r31 = particle->unk_48;

    for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
        if (0.0f != var_r31->unk14.x) {
            var_r31->unk2C += var_r31->unk14.y;
            if (var_r31->unk14.y > 2.0f) {
                var_r31->unk14.y -= 0.2f;
            }
            var_f31 = var_r31->unk40.a;
            var_f31 -= var_r31->unk14.z;
            if (var_r31->unk14.z > 3.0f) {
                var_r31->unk14.z -= 1.0f;
            }
            if (var_f31 < 0.0f) {
                var_f31 = 0.0f;
                var_r31->unk14.x = 0.0f;
            }
            var_r31->unk40.a = var_f31;
            if (var_r31->unk14.x == 0.0f) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}

void fn_1_ADC8(void)
{
    Vec sp14;
    Vec sp8;
    f32 var_f31;
    void *temp_r28;
    Process *var_r29;
    s32 var_r31;
    unkStruct3 *temp_r30;

    fn_1_6EC(1465.0f, 770.0f, -2400.0f, 0x588);
    HuAudFXPlay(0x58B);

    var_r31 = 0;
    var_f31 = Hu3DMotionMaxTimeGet(lbl_1_bss_79E);
    for (; var_f31; var_r31++, var_f31--) {
        if (var_r31 == 0x33) {
            Hu3DModelAttrReset(lbl_1_bss_798[0], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(lbl_1_bss_798[0], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(lbl_1_bss_798[0], 1465.0f, 770.0f, -2400.0f);
        }
        if (var_r31 == 0x47) {
            Hu3DModelAttrReset(lbl_1_bss_798[1], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(lbl_1_bss_798[1], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(lbl_1_bss_798[1], 1531.0f, 773.0f, -2380.0f);
        }
        if (var_r31 == 0x82) {
            temp_r28 = fn_1_6EC(1465.0f, 770.0f, -2400.0f, 0x580);
            var_r29 = HuPrcChildCreate(fn_1_7BC, 0x2000, 0x1000, 0, HuPrcCurrentGet());
            var_r29->user_data = temp_r28;
        }
        if (var_f31 == 90.0f) {
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                temp_r30 = &lbl_1_bss_4D4[var_r31];
                CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[var_r31].character], temp_r30->unkC[3], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
                Hu3DMotionShiftSet(temp_r30->unk2, temp_r30->unk18[3], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
            }
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        temp_r30 = &lbl_1_bss_4D4[var_r31];
        HuAudPlayerVoicePlay(temp_r30->unk24, 0x128);
        CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[var_r31].character], temp_r30->unkC[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        Hu3DMotionShiftSet(temp_r30->unk2, temp_r30->unk18[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    }
}

void fn_1_B13C(void)
{
    HuPrcSleep(0x1E);
}

void fn_1_B160(void)
{
    while (1) {
        while (1) {
            if (omSysExitReq != 1)
                break;
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(0x3E8);
            HuPrcSleep(0x3C);
            MGSeqKillAll();
            omOvlReturnEx(1, 1);
            while (1) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_B1C0(void)
{
    s16 temp_r27;
    s16 temp_r30;
    s16 var_r29;
    s32 var_r26;
    s32 var_r28;
    s32 var_r31;

    lbl_1_bss_794 = 0;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_780[var_r31] = -1;
    }
    HuAudFXPlay(0x57F);
    fn_1_6EC(1465.0f, 770.0f, -2400.0f, 0x589);
    HuPrcSleep(1);
    Hu3DModelAttrSet(lbl_1_bss_2F8.unk0, HU3D_MOTATTR_PAUSE);
    Hu3DModelClusterAttrSet(lbl_1_bss_2F8.unk0, 0, -0x3FFFFFFE);
    Hu3DModelAttrSet(lbl_1_bss_2F8.unk2, HU3D_MOTATTR_PAUSE);
    Hu3DModelClusterAttrSet(lbl_1_bss_2F8.unk2, 0, -0x3FFFFFFE);
    HuPrcSleep(1.0f + wipeData.duration);
    fn_1_ADC8();
    HuPrcSleep(30);
    lbl_1_bss_794 = 1;
    while (lbl_1_bss_794 == 1) {
        HuPrcVSleep();
    }
    var_r26 = HuAudSeqPlay(0x43);
    temp_r30 = MGSeqCreate(3, 0);

    while (MGSeqStatGet(temp_r30) != 0) {
        HuPrcVSleep();
    }
    var_r29 = REFRESH_RATE * 60 + REFRESH_RATE - 1;
    temp_r27 = MGSeqCreate(1, var_r29 / REFRESH_RATE, -1, -1);
    lbl_1_bss_794 = 3;

    while (1) {
        for (var_r31 = 0, var_r28 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_4D4[var_r31].unk30 != 3) {
                var_r28++;
            }
        }
        if ((var_r28 <= 1) || (var_r29 < REFRESH_RATE - 1))
            break;
        MGSeqParamSet(temp_r27, 1, var_r29-- / REFRESH_RATE);
        lbl_1_bss_790++;
        HuPrcVSleep();
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_4D4[var_r31].unk30 != 3) {
            lbl_1_bss_780[var_r31] = GWPlayerCfg[var_r31].character;
            if (_CheckFlag(0x1000C) == 0) {
                GWPlayer[var_r31].coin_win = 10;
            }
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_4D4[var_r31].unk30 = 4;
    }
    lbl_1_bss_794 = 4;
    HuAudSeqFadeOut(var_r26, 0x64);
    MGSeqParamSet(temp_r27, 2, -1);
    temp_r30 = MGSeqCreate(3, 1);

    while (MGSeqStatGet(temp_r30) != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    lbl_1_bss_794 = 5;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_780[var_r31] != -1)
            break;
    }
    if (var_r31 < 4) {
        HuAudSStreamPlay(1);
        temp_r30 = MGSeqCreate(5, 3, lbl_1_bss_780[0], lbl_1_bss_780[1], lbl_1_bss_780[2], lbl_1_bss_780[3]);
    }
    else {
        HuAudSStreamPlay(4);
        temp_r30 = MGSeqCreate(3, 2);
    }
    HuPrcSleep(0xD2);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuPrcSleep(0x3C);
    HuAudFadeOut(1);
    MGSeqKillAll();
    omOvlReturnEx(1, 1);
    while (1) {
        HuPrcVSleep();
    }
}
