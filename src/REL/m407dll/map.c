#include "game/process.h"
#include "game/object.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

//function signatures
void fn_1_162C(omObjData*);
void fn_1_1A8C(omObjData*);

//bss
Process* lbl_1_bss_2C;
omObjData* lbl_1_bss_28;
s16 lbl_1_bss_24;
s32 lbl_1_bss_20;

//data
s32 lbl_1_data_198[] = {
    0x00260000,
    0x00260002,
    0x00260003,
    0x00260001,
    0x00260005,
    0x00260006,
    0x00260007,
    0x00260008,
    0x00260009,
    0x0026000A,
    0x0026000B,
    0x0026000C,
    0x00260004,
};

Vec lbl_1_data_1CC[] = {
    {600.0f, 3.0f, -300.0f},
    {200.0f, 3.0f, -300.0f},
    {-200.0f, 3.0f, -300.0f},
    {-600.0f, 3.0f, -300.0f}
};

Point3d lbl_1_data_1FC = {2000.0f, 3000.0f, 2000.0f};
Point3d lbl_1_data_208 = {-0.5f, -0.5f, -0.5f};
GXColor lbl_1_data_214 = {255, 255, 255, 255};
Point3d lbl_1_data_218 = {0.0f, 1.0f, 0.0f};

void fn_1_14F0(Process* arg0, s32 arg1) {
    LightData* sp10;

    lbl_1_bss_2C = arg0;
    lbl_1_bss_20 = arg1;
    lbl_1_bss_28 = omAddObjEx(lbl_1_bss_2C, 0x100, 0xD, 0, 1, fn_1_162C);
    omSetStatBit(lbl_1_bss_28, 0x100);
    Hu3DLighInit();
    lbl_1_bss_24 = Hu3DGLightCreateV(&lbl_1_data_1FC, &lbl_1_data_208, &lbl_1_data_214);
    Hu3DGLightInfinitytSet(lbl_1_bss_24);
    sp10 = &Hu3DGlobalLight[lbl_1_bss_24];
}

void fn_1_15D8(void) {
    s32 i;

    for (i = 0; i < 13; i++) {
        Hu3DModelKill(lbl_1_bss_28->model[i]);
    }
}

void fn_1_162C(omObjData* arg0) {
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 i;

    arg0->func = fn_1_1A8C;
    arg0->model[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_198[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelShadowMapSet(arg0->model[0]);
    Hu3DModelAmbSet(arg0->model[0], 1.0f, 1.0f, 1.0f);
    arg0->model[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_198[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAmbSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrSet(arg0->model[1], 1);
    for (i = 0; i < ARRAY_COUNT(GWPlayerCfg); i++) {
        arg0->model[i+2] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_198[GWPlayerCfg[i].character + 4], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAmbSet(arg0->model[i + 2], 1.0f, 1.0f, 1.0f);
        Hu3DModelShadowMapSet(arg0->model[i + 2]);
    }

    for (i = 0; i < 5; i++) {
        if (i == 0) {
            arg0->model[i + 6] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_198[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            arg0->model[i + 6] = Hu3DModelLink(arg0->model[6]);
        }
        Hu3DModelAmbSet(arg0->model[i + 6], 1.0f, 1.0f, 1.0f);
        Hu3DModelShadowMapSet(arg0->model[i + 6]);
    }

    arg0->model[11] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_198[12], MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[12] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_198[1], MEMORY_DEFAULT_NUM, HEAP_DATA));

    for (i = 0; i < 4; i++) {
        Hu3DModelPosSetV(arg0->model[i + 2], &lbl_1_data_1CC[i]);
    }

    for (i = 0; i < 5; i++) {
        Hu3DModelPosSet(arg0->model[i + 6], 0.0f, 0.0f, -2000.0f + (8000.0f * (f32) i));
    }
    
    Hu3DModelPosSet(arg0->model[11], 0.0f, 0.0f, -3900.0f);
    Hu3DModelPosSet(arg0->model[12], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[12], 0x40000001);
    
    if (lbl_1_bss_20 > 0) {
        Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, 200.0f * (f32) lbl_1_bss_20);
        Hu3DModelAttrReset(arg0->model[1], 1);
    }
}

void fn_1_1A8C(omObjData* arg0) {
    Point3d sp8;

    sp8.x = lbl_1_data_1FC.x;
    sp8.y = lbl_1_data_1FC.y;
    sp8.z = lbl_1_data_1FC.z + Center.z;
    Hu3DGLightPosSetV(lbl_1_bss_24, &sp8, &lbl_1_data_208);
    Hu3DShadowPosSet(&sp8, &lbl_1_data_218, &Center);
}