#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/mtx/GeoTypes.h"
#include "ext_math.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfload.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/init.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

#include "REL/m428Dll.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/frand.h"
#endif

typedef struct M428DllBss13CStruct {
    /* 0x00 */ float unk_00;
    /* 0x04 */ char pad_04[0x3C]; /* maybe part of unk_00[0x10]? */
} M428DllBss13CStruct; /* size = 0x40 */

typedef struct M428DllData4B0Struct {
    Vec unk_00;
    float unk_0C;
} M428DllData4B0Struct; /* size = 0x10 */

typedef struct M428DllData500Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} M428DllData500Struct; /* size = 0x08 */

typedef struct M428DllPlayerWork {
    omObjData *unk_00[2]; // M428DllPlayerWork2
    s16 unk_08[2];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s32 unk_14;
    s32 unk_18;
    float unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    float unk_2C;
    float unk_30;
    float unk_34;
    s32 unk_38;
    Vec unk_3C;
    float unk_48;
    float unk_4C[2];
    float unk_54[2];
    float unk_5C;
    float unk_60;
    Vec unk_64[2];
    Vec unk_7C;
    Vec unk_88;
    Vec unk_94;
    Vec unk_A0;
    Vec unk_AC;
    s32 unk_B8;
    s32 unk_BC;
    s32 unk_C0;
    s32 unk_C4;
    float unk_C8;
} M428DllPlayerWork; /* size = 0xCC */

typedef struct M428DllPlayerWork2 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    float unk_14;
    float unk_18;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
    float unk_28;
    float unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    Vec unk_3C;
    Vec unk_48;
    Vec unk_54;
    Mtx unk_60;
    Vec unk_90;
    char unk_9C[0x100];
    s32 unk_19C;
    s32 unk_1A0;
    s32 unk_1A4;
    s32 unk_1A8;
    float unk_1AC;
    s32 unk_1B0;
    s32 unk_1B4;
    Vec unk_1B8;
} M428DllPlayerWork2; /* size = 0x1C4 */

typedef struct M428DllPlayerWork3 {
    s32 unk_00;
    s32 unk_04[2];
    float unk_0C[2][2];
    s32 unk_1C[2];
    float unk_24[2][2];
    AnimData *unk_34;
    AnimData *unk_38;
    s32 unk_3C[2][2];
    s32 unk_4C[2][2];
} M428DllPlayerWork3; /* size = 0x5C */

typedef struct M428DllPlayerUnkStruct {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    Vec unk_08[4];
} M428DllPlayerUnkStruct; /* size = 0x38 */

typedef struct M428DllPlayerUnk120Struct {
    s16 unk_00;
    s16 unk_02;
    float unk_04;
    float unk_08;
    s32 unk_0C;
    s32 unk_10;
    float unk_14;
    float unk_18;
    s32 unk_1C;
    Vec unk_20;
    Vec unk_2C;
    Vec unk_38;
    s32 unk_44;
    float unk_48;
    float unk_4C;
    float unk_50;
    M428DllPlayerUnkStruct *unk_54;
} M428DllPlayerUnk120Struct; /* size = 0x58 */

typedef struct M428DllPlayerUnkStruct2 {
    s16 unk_00;
    s16 unk_02;
    float unk_04;
    float unk_08;
    float unk_0C;
    char unk10[8];
    float unk_18;
    char unk1C[0xC];
    float unk_28;
    float unk_2C;
    float unk_30;
    float unk_34;
    Vec unk_38;
    GXColor unk_44;
    s32 unk_48;
} M428DllPlayerUnkStruct2; /* size = 0x4C */

typedef void (*M428DllPlayerHook)(ModelData *model, struct M428DllPlayerUnk120Struct2 *arg1, Mtx matrix);

typedef struct M428DllPlayerUnk120Struct2 {
    s16 unk_00;
    s16 unk_02;
    char unk04[0x1C];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
    char unk24[2];
    s16 unk_26;
    s32 unk_28;
    s32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    AnimData *unk_38;
    M428DllPlayerUnkStruct2 *unk_3C;
    Vec *unk_40;
    Vec2f *unk_44;
    void *unk_48;
    M428DllPlayerHook unk_4C;
    ModelData *unk_50;
} M428DllPlayerUnk120Struct2; /* size = 0x54 */

typedef struct M428DllPlayerWork4 {
    s32 unk_00[2];
    s32 unk_08[2];
    AnimData *unk_10;
} M428DllPlayerWork4; /* size = 0x14 */

void fn_1_102A8(ModelData *modle, Mtx matrix);
void fn_1_10530(s32 arg0, Vec *arg1, Vec *arg2);
void fn_1_10590(s32 arg0, s32 arg1, s32 arg2, Vec *arg3);
void fn_1_105E8(s32 arg0, float arg8, float arg9);
s32 fn_1_10788(s32 arg0, Vec *arg1, Vec *arg2, Vec *arg3);
void fn_1_10A88(void);
void fn_1_11014(omObjData *object);
void fn_1_115F8(void);
void fn_1_118A8(s32 arg0, float arg8);
void fn_1_11930(void);
void fn_1_11A60(omObjData *object);
void fn_1_11C20(void);
s32 fn_1_11DE4(s32 arg0, Vec arg1, Vec arg2, float arg8, float arg9, float argA, float argB, GXColor arg3);
float fn_1_1236C(float arg8, float arg9, float argA);
void fn_1_129B4(float arg8, Vec *arg0, Vec *arg1, Vec *arg2);
void fn_1_12AA4(float arg8, Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3);
s16 fn_1_12CD4(AnimData *arg0, s16 arg1);
void fn_1_134C0(ModelData *model, Mtx matrix);
void fn_1_13D9C(s16 arg0, s16 arg1, s32 arg2);
void fn_1_13E14(s16 arg0, s16 arg1, Vec arg2);
void fn_1_13EC8(s16 arg0, s16 arg1, float arg8);
s32 fn_1_13F54(s16 arg0, char *arg1, Mtx arg2, s32 arg3);
void fn_1_14088(HsfObject *arg0, Mtx arg1, char *arg2, Mtx arg3);
void fn_1_A108(omObjData *object);
void fn_1_A4C8(omObjData *object);
void fn_1_B3D4(omObjData *object);
void fn_1_B43C(omObjData *object);
void fn_1_BBD0(omObjData *object);
void fn_1_E5F4(omObjData *object);
void fn_1_E600(omObjData *object);
s32 fn_1_F288(Vec *arg0, Vec *arg1, float arg8);
s32 fn_1_F538(Vec *arg0, Vec *arg1, Vec *arg2, float arg8);
s32 fn_1_FB8C(Vec *arg0, Vec *arg1, float arg8, s32 arg2, s32 arg3);

extern u32 GlobalCounter;

Vec lbl_1_data_150[4] = {
    { -140.0f, -400.0f, 0.0f },
    { 140.0f, -300.0f, 0.0f },
    { -140.0f, -300.0f, 0.0f },
    { 140.0f, -400.0f, 0.0f },
};
Vec lbl_1_data_180[4] = {
    { -100.0f, -10.0f, 150.0f },
    { 100.0f, -10.0f, 150.0f },
    { -100.0f, -10.0f, 150.0f },
    { 100.0f, -10.0f, 150.0f },
};
Vec lbl_1_data_1B0[4][0xE] = {
    {
        { -11.0f, 214.0f, 39.0f },
        { -11.0f, 400.0f, 46.0f },
        { -11.0f, 668.0f, 56.0f },
        { -11.0f, 931.0f, 42.0f },
        { 7.0f, 1131.0f, 65.0f },
        { -452.0f, 1449.0f, 57.0f },
        { -478.0f, 1763.0f, 48.0f },
        { -452.0f, 2001.0f, 44.0f },
        { -311.0f, 2120.0f, 55.0f },
        { -85.0f, 2442.0f, 42.0f },
        { -32.0f, 2876.0f, 43.0f },
        { -12.0f, 3300.0f, 48.0f },
        { -42.0f, 4500.0f, 48.0f },
        { -42.0f, 4500.0f, 48.0f },
    },
    {
        { 16.0f, 203.0f, 40.0f },
        { 0.0f, 456.0f, 50.0f },
        { 15.0f, 650.0f, 58.0f },
        { -268.0f, 935.0f, 51.0f },
        { -463.0f, 1205.0f, 66.0f },
        { -663.0f, 1313.0f, 69.0f },
        { -460.0f, 1600.0f, 59.0f },
        { -333.0f, 1946.0f, 46.0f },
        { -82.0f, 2188.0f, 44.0f },
        { -76.0f, 2374.0f, 40.0f },
        { -108.0f, 2620.0f, 43.0f },
        { -95.0f, 2990.0f, 46.0f },
        { -270.0f, 3445.0f, 46.0f },
        { -42.0f, 4500.0f, 48.0f },
    },
    {
        { 26.0f, 354.0f, 46.0f },
        { 29.0f, 604.0f, 57.0f },
        { 30.0f, 877.0f, 39.0f },
        { 51.0f, 1086.0f, 64.0f },
        { 360.0f, 1196.0f, 46.0f },
        { 398.0f, 1416.0f, 39.0f },
        { 468.0f, 1658.0f, 43.0f },
        { 468.0f, 1944.0f, 53.0f },
        { 135.0f, 2174.0f, 47.0f },
        { 107.0f, 2430.0f, 61.0f },
        { 98.0f, 2698.0f, 43.0f },
        { 90.0f, 2995.0f, 50.0f },
        { 0.0f, 4500.0f, 48.0f },
        { 0.0f, 4500.0f, 48.0f },
    },
    {
        { -24.0f, 313.0f, 41.0f },
        { -11.0f, 529.0f, 51.0f },
        { -33.0f, 799.0f, 44.0f },
        { 7.0f, 990.0f, 53.0f },
        { 135.0f, 1196.0f, 57.0f },
        { 393.0f, 1379.0f, 39.0f },
        { 429.0f, 1457.0f, 42.0f },
        { 420.0f, 1984.0f, 54.0f },
        { 190.0f, 2239.0f, 53.0f },
        { 70.0f, 2532.0f, 55.0f },
        { 75.0f, 2933.0f, 44.0f },
        { 75.0f, 4500.0f, 48.0f },
        { 75.0f, 4500.0f, 48.0f },
        { 75.0f, 4500.0f, 48.0f },
    },
};
Vec lbl_1_data_450[4] = {
    { -30.000002f, -10.0f, -90.0f },
    { 20.0f, -10.0f, -70.0f },
    { 0.0f, -10.0f, 0.0f },
    { 0.0f, -10.0f, 0.0f },
};
Vec lbl_1_data_480[4] = {
    { 15.0f, 150.0f, 0.0f },
    { 15.0f, 210.0f, 0.0f },
    { 0.0f, 180.0f, 0.0f },
    { 0.0f, 180.0f, 0.0f },
};
M428DllData4B0Struct lbl_1_data_4B0[5] = {
    { { -400.0f, 700.0f, 0.0f }, 200.0f },
    { { 400.0f, 900.0f, 0.0f }, 200.0f },
    { { 0.0f, 1800.0f, 0.0f }, 220.0f },
    { { -600.0f, 3100.0f, 0.0f }, 300.0f },
    { { 600.0f, 2880.0f, 0.0f }, 300.0f },
};
M428DllData500Struct lbl_1_data_500[0xC] = {
    { 0x5F0000, 0 },
    { 0x5F0002, 0 },
    { 0x5F0003, 0 },
    { -1, 0 },
    { -1, 1 },
    { -1, 2 },
    { -1, 3 },
    { 0x5F0006, 0 },
    { 0x5F0014, 0 },
    { 0x5F005B, 0 },
    { 0x5F0017, 0 },
    { 0x5F0018, 0 },
};
s32 lbl_1_data_560[4][8] = {
    {
        DATA_MAKE_NUM(DATADIR_M428, 0x11),
        DATA_MAKE_NUM(DATADIR_M428, 0x12),
        DATA_MAKE_NUM(DATADIR_M428, 0x13),
        DATA_MAKE_NUM(DATADIR_M428, 0x14),
        DATA_MAKE_NUM(DATADIR_M428, 0x15),
        DATA_MAKE_NUM(DATADIR_M428, 0x16),
        DATA_MAKE_NUM(DATADIR_M428, 0x17),
        DATA_MAKE_NUM(DATADIR_M428, 0x18),
    },
    {
        DATA_MAKE_NUM(DATADIR_M428, 0x19),
        DATA_MAKE_NUM(DATADIR_M428, 0x1A),
        DATA_MAKE_NUM(DATADIR_M428, 0x1B),
        DATA_MAKE_NUM(DATADIR_M428, 0x1C),
        DATA_MAKE_NUM(DATADIR_M428, 0x1D),
        DATA_MAKE_NUM(DATADIR_M428, 0x1E),
        DATA_MAKE_NUM(DATADIR_M428, 0x1F),
        DATA_MAKE_NUM(DATADIR_M428, 0x20),
    },
    {
        DATA_MAKE_NUM(DATADIR_M428, 0x21),
        DATA_MAKE_NUM(DATADIR_M428, 0x22),
        DATA_MAKE_NUM(DATADIR_M428, 0x23),
        DATA_MAKE_NUM(DATADIR_M428, 0x24),
        DATA_MAKE_NUM(DATADIR_M428, 0x25),
        DATA_MAKE_NUM(DATADIR_M428, 0x26),
        DATA_MAKE_NUM(DATADIR_M428, 0x27),
        DATA_MAKE_NUM(DATADIR_M428, 0x28),
    },
    {
        DATA_MAKE_NUM(DATADIR_M428, 0x29),
        DATA_MAKE_NUM(DATADIR_M428, 0x2A),
        DATA_MAKE_NUM(DATADIR_M428, 0x2B),
        DATA_MAKE_NUM(DATADIR_M428, 0x2C),
        DATA_MAKE_NUM(DATADIR_M428, 0x2D),
        DATA_MAKE_NUM(DATADIR_M428, 0x2E),
        DATA_MAKE_NUM(DATADIR_M428, 0x2F),
        DATA_MAKE_NUM(DATADIR_M428, 0x30),
    },
};
Vec lbl_1_data_5E0[8] = {
    { 0.0f, -10.0f, -20.0f },
    { 0.0f, -10.0f, -20.0f },
    { 0.0f, -30.000002f, -20.0f },
    { 0.0f, -10.0f, -20.0f },
    { 0.0f, -10.0f, -20.0f },
    { 0.0f, 10.0f, -10.0f },
    { 0.0f, -30.000002f, -20.0f },
    { 0.0f, -10.0f, -20.0f },
};
s32 lbl_1_data_640[4] = { 0x80000000, 0x40000000, 0x20000000, 0x10000000 };
GXColor lbl_1_data_650 = { 0xFF, 0xFF, 0xFF, 0x20 };
GXColor lbl_1_data_654 = { 0xFF, 0xFF, 0xFF, 0x40 };

Process *lbl_1_bss_2D0;
// M428DllPlayerWork
omObjData *lbl_1_bss_2C8[2];
omObjData *lbl_1_bss_2B8[4];
// M428DllPlayerWork3
omObjData *lbl_1_bss_2B4;
// M428DllPlayerWork4
omObjData *lbl_1_bss_2B0;
M428DllPlayerWork *lbl_1_bss_2AC;
M428DllPlayerWork2 *lbl_1_bss_2A8;
s32 lbl_1_bss_2A4;
s32 lbl_1_bss_29C[2];
Mtx lbl_1_bss_23C[2];
M428DllBss13CStruct lbl_1_bss_1BC[2];
M428DllBss13CStruct lbl_1_bss_13C[2];
s32 lbl_1_bss_138;
s32 lbl_1_bss_134;
s32 lbl_1_bss_130;

omObjData *fn_1_9F5C(Process *process)
{
    s32 var_r31;

    lbl_1_bss_2D0 = process;
    lbl_1_bss_2A4 = 0;
    lbl_1_bss_2AC = HuMemDirectMallocNum(HEAP_SYSTEM, 2 * sizeof(M428DllPlayerWork), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_2AC, 0, 2 * sizeof(M428DllPlayerWork));
    lbl_1_bss_2A8 = HuMemDirectMallocNum(HEAP_SYSTEM, 4 * sizeof(M428DllPlayerWork2), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_2A8, 0, 4 * sizeof(M428DllPlayerWork2));
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_2C8[var_r31] = omAddObjEx(process, 0x40, 1, 0, -1, fn_1_A108);
        lbl_1_bss_2C8[var_r31]->work[0] = var_r31;
    }
    fn_1_10A88();
    fn_1_11798(0);
    fn_1_11930();
    lbl_1_bss_29C[0] = lbl_1_bss_29C[1] = 0;
    return lbl_1_bss_2C8[var_r31];
}

void fn_1_A0B0(void)
{
    s32 var_r31;

    fn_1_115F8();
    fn_1_11C20();
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        fn_1_B3D4(lbl_1_bss_2C8[var_r31]);
    }
}

void fn_1_A108(omObjData *object)
{
    M428DllPlayerWork *work;
    s32 var_r30;
    s32 var_r28;
    s32 var_r27;

    var_r28 = object->work[0];
    work = &lbl_1_bss_2AC[var_r28];
    object->data = work;
    work->unk_0C = var_r28;
    work->unk_0E = 0;
    work->unk_10 = 0;
    work->unk_12 = (u8)frand() % 4;
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->unk_1C = 0.0f;
    work->unk_20 = 0;
    work->unk_24 = 0;
    work->unk_28 = 0;
    work->unk_2C = 0.0f;
    work->unk_30 = 0.0f;
    work->unk_34 = 0.0f;
    work->unk_B8 = 0;
    work->unk_BC = -1;
    work->unk_C0 = work->unk_C4 = 0;
    work->unk_C8 = 0.0f;
    work->unk_38 = -1;
    work->unk_4C[0] = work->unk_4C[1] = 0.0f;
    work->unk_48 = 400.0f;
    work->unk_54[0] = work->unk_5C = 200.0f;
    work->unk_54[1] = work->unk_60 = 200.0f;
    work->unk_64[0].x = 0.5f * (lbl_1_data_150[0].x + lbl_1_data_150[1].x);
    work->unk_64[0].y = 0.5f * (lbl_1_data_150[0].y + lbl_1_data_150[1].y);
    work->unk_64[0].z = 0.5f * (lbl_1_data_150[0].z + lbl_1_data_150[1].z);
    work->unk_64[1] = work->unk_64[0];
    work->unk_7C = work->unk_64[0];
    work->unk_88 = work->unk_64[1];
    work->unk_94.x = work->unk_94.y = work->unk_94.z = 0.0f;
    work->unk_A0.x = work->unk_A0.y = work->unk_A0.z = 0.0f;
    work->unk_AC.x = work->unk_AC.y = work->unk_AC.z = 0.0f;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r27 = lbl_1_bss_50[var_r30 + (var_r28 * 2)];
        work->unk_08[var_r30] = var_r27;
        work->unk_00[var_r30] = lbl_1_bss_2B8[var_r27] = omAddObjEx(lbl_1_bss_2D0, 0x41, 2, 0xC, -1, fn_1_B43C);
        work->unk_00[var_r30]->data = NULL;
        work->unk_00[var_r30]->work[0] = var_r27;
        work->unk_00[var_r30]->work[1] = work->unk_0C;
        work->unk_00[var_r30]->work[2] = var_r30;
    }
    object->model[0] = fn_1_FB8C(&lbl_1_data_150[0], &lbl_1_data_150[1], 400.0f, 0x30, work->unk_0C);
    if (work->unk_0C == 0) {
        Hu3DModelCameraSet(object->model[0], 1);
    }
    else {
        Hu3DModelCameraSet(object->model[0], 2);
    }
    object->func = fn_1_A4C8;
}

void fn_1_A4C8(omObjData *object)
{
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    M428DllPlayerWork *var_r31;
    M428DllPlayerWork2 *var_r30;
    M428DllPlayerWork2 *var_r29;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21;

    var_r22 = 0;
    var_r24 = 0;
    var_r23 = 0;
    var_r31 = object->data;
    var_r30 = var_r31->unk_00[0]->data;
    var_r29 = var_r31->unk_00[1]->data;
    if (!var_r30 || !var_r29) {
        return;
    }
    if ((fn_1_26E0() < 7) || (lbl_1_bss_2A4 == 0)) {
        sp50.x = var_r30->unk_90.x;
        sp50.y = var_r30->unk_90.y;
        sp50.z = var_r30->unk_90.z;
        sp44.x = var_r29->unk_90.x;
        sp44.y = var_r29->unk_90.y;
        sp44.z = var_r29->unk_90.z;
        VECAdd(&sp50, &sp44, &sp2C);
        VECScale(&sp2C, &sp2C, 0.5f);
        var_r21 = fn_1_10788(object->model[0], &sp50, &sp44, &sp38);
        if (var_r21 != -1) {
            if (var_r31->unk_38 != var_r21) {
                var_r31->unk_38 = var_r21;
                var_r31->unk_3C = sp38;
                var_r23 = 1;
            }
            else {
                var_r23 = 0;
            }
            var_r31->unk_64[1] = var_r31->unk_3C;
            var_r31->unk_64[0] = var_r31->unk_64[1];
            var_f31 = var_r31->unk_4C[0] + var_r31->unk_4C[1];
            if (var_f31 >= 400.0f) {
                if (var_r23 != 0) {
                    var_r31->unk_48 = var_f31;
                }
                else {
                    var_r31->unk_48 + (400.0f - var_r31->unk_48) * 0.01f; // bug
                    (void)var_r22;
                }
                var_f31 = 1.0f / var_f31;
                var_r31->unk_54[0] = var_r31->unk_48 * (var_r31->unk_4C[0] * var_f31);
                var_r31->unk_54[1] = var_r31->unk_48 * (var_r31->unk_4C[1] * var_f31);
            }
            else {
                var_f31 = 1.0f / var_f31;
                var_r31->unk_54[0] = 400.0f * (var_r31->unk_4C[0] * var_f31);
                var_r31->unk_54[1] = 400.0f * (var_r31->unk_4C[1] * var_f31);
                var_r31->unk_48 = 400.0f;
            }
            var_f31 = var_r31->unk_54[0] + var_r31->unk_54[1];
            var_r26 = 48.0f * (var_r31->unk_54[0] / var_f31);
            if (var_r26 < 1) {
                var_r26 = 1;
            }
            else if (var_r26 > 0x2E) {
                var_r26 = 0x2E;
            }
            fn_1_10590(object->model[0], 1, var_r26, &var_r31->unk_3C);
            var_f31 = (var_r31->unk_4C[0] + var_r31->unk_4C[1]) / var_r31->unk_48;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            fn_1_105E8(object->model[0], 1.0f - var_f31, 1.0f - var_f31);
        }
        else {
            var_r31->unk_38 = -1;
            fn_1_10590(object->model[0], 0, 0x18, &var_r31->unk_3C);
            var_f31 = (var_r31->unk_4C[0] + var_r31->unk_4C[1]) / 400.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            fn_1_105E8(object->model[0], 1.0f - var_f31, 1.0f - var_f31);
            var_r31->unk_48 = 400.0f;
            var_r31->unk_64[1] = sp2C;
            var_r31->unk_64[0] = var_r31->unk_64[1];
            var_r31->unk_54[0] = 200.0f;
            var_r31->unk_54[1] = 200.0f;
        }
        var_r31->unk_54[0] = var_r31->unk_5C + (0.01f * (var_r31->unk_54[0] - var_r31->unk_5C));
        var_r31->unk_54[1] = var_r31->unk_60 + (0.01f * (var_r31->unk_54[1] - var_r31->unk_60));
        fn_1_129B4(0.1f, &var_r31->unk_64[2], &var_r31->unk_64[0], &var_r31->unk_64[0]);
        fn_1_129B4(0.1f, &var_r31->unk_88, &var_r31->unk_64[1], &var_r31->unk_64[1]);
        var_r31->unk_5C = var_r31->unk_54[0];
        var_r31->unk_60 = var_r31->unk_54[1];
        var_r31->unk_7C = var_r31->unk_64[0];
        var_r31->unk_88 = var_r31->unk_64[1];
        if (var_r31->unk_38 != -1) {
            var_r31->unk_94 = var_r31->unk_64[0];
            var_r31->unk_A0 = var_r31->unk_64[1];
        }
        else if (var_r30->unk_20 == 4) {
            var_r31->unk_94 = var_r29->unk_90;
            var_r31->unk_A0 = var_r30->unk_90;
        }
        else if (var_r29->unk_20 == 4) {
            var_r31->unk_94 = var_r30->unk_90;
            var_r31->unk_A0 = var_r29->unk_90;
        }
        else {
            var_r31->unk_94 = var_r31->unk_64[0];
            var_r31->unk_A0 = var_r31->unk_64[1];
        }
        if (lbl_1_bss_29C[var_r31->unk_0C] == 5) {
            var_r24 = 1;
        }
        if ((fn_1_26E0() != 4) || (var_r31->unk_18 != 0)) {
            var_r24 = 0;
        }
        if (var_r24 != 0) {
            var_r27 = -1;
            if ((var_r30->unk_20 == 2) && (var_r29->unk_20 == 3)) {
                var_r27 = 0;
            }
            else if ((var_r30->unk_20 == 3) && (var_r29->unk_20 == 2)) {
                var_r27 = 1;
            }
            else if ((var_r30->unk_20 == 2) && (var_r29->unk_20 == 2)) {
                if (sp50.y > sp44.y) {
                    var_r27 = 0;
                }
                else {
                    var_r27 = 1;
                }
            }
            if (var_r27 == 0) {
                var_r30->unk_20 = 4;
                var_r30->unk_22 = 0;
                var_r30->unk_34 = 0;
                var_r30->unk_38 = 0;
                var_r30->unk_3C.x = 0.0f;
                var_r30->unk_3C.y = var_r30->unk_3C.z = 0.0f;
                var_r31->unk_2C = sp50.y;
                var_r31->unk_AC = sp50;
                var_r31->unk_34 = 0.0f;
            }
            else if (var_r27 == 1) {
                var_r29->unk_20 = 4;
                var_r29->unk_22 = 0;
                var_r29->unk_34 = 0;
                var_r29->unk_38 = 0;
                var_r29->unk_3C.x = 0.0f;
                var_r29->unk_3C.y = var_r29->unk_3C.z = 0.0f;
                var_r31->unk_2C = sp44.y;
                var_r31->unk_AC = sp44;
                var_r31->unk_34 = 0.0f;
            }
        }
        if ((var_r30->unk_20 == 4) || (var_r29->unk_20 == 4)) {
            var_r31->unk_24 = 1;
            var_r31->unk_28 = 1;
        }
        else {
            var_r31->unk_24 = 0;
        }
        if (lbl_1_bss_29C[var_r31->unk_0C] != 5) {
            var_r31->unk_28 = 0;
        }
        sp50.x = var_r30->unk_90.x;
        sp50.y = var_r30->unk_90.y;
        sp50.z = var_r30->unk_90.z;
        sp44.x = var_r29->unk_90.x;
        sp44.y = var_r29->unk_90.y;
        sp44.z = var_r29->unk_90.z;
        fn_1_10530(object->model[0], &sp50, &sp44);
        if (var_r31->unk_00[0]->trans.y > var_r31->unk_00[1]->trans.y) {
            var_r31->unk_1C = var_r31->unk_00[0]->trans.y;
            var_r31->unk_10 = 0;
        }
        else if (var_r31->unk_00[1]->trans.y > var_r31->unk_00[0]->trans.y) {
            var_r31->unk_1C = var_r31->unk_00[1]->trans.y;
            var_r31->unk_10 = 1;
        }
        else {
            var_r25 = frand() & 1;
            var_r31->unk_1C = var_r31->unk_00[var_r25]->trans.y;
            var_r31->unk_10 = var_r25;
        }
        fn_1_118A8(var_r31->unk_0C, var_r31->unk_1C / 3800.0f);
        if (fn_1_26E0() == 4) {
            sp50.x = var_r31->unk_00[0]->trans.x;
            sp50.y = var_r31->unk_00[0]->trans.y;
            sp50.z = var_r31->unk_00[0]->trans.z;
            sp44.x = var_r31->unk_00[1]->trans.x;
            sp44.y = var_r31->unk_00[1]->trans.y;
            sp44.z = var_r31->unk_00[1]->trans.z;
            VECAdd(&sp50, &sp44, &sp2C);
            VECScale(&sp2C, &sp2C, 0.5f);
            VECSubtract(&sp50, &sp44, &sp20);
            sp20.z = 0.0f;
            var_f29 = VECMag(&sp20);
            if (var_f29 < 100.0f) {
                var_f27 = 0.0f;
            }
            else if (var_f29 >= 300.0f) {
                var_f27 = 1.0f;
            }
            else {
                var_f27 = (var_f29 - 100.0f) / 200.0f;
            }
            var_f29 = 1500.0f + (500.0f * var_f27);
            var_f28 = sp2C.x;
            if (var_f28 > 400.0f) {
                var_f28 = 400.0f;
            }
            else if (var_f28 < -400.0f) {
                var_f28 = -400.0f;
            }
            var_f26 = sp2C.y;
            if (var_f26 < 400.0f) {
                var_f26 = 400.0f;
            }
            var_f25 = var_r31->unk_1C;
            if (var_f25 < 20.0f) {
                var_f30 = 0.0f;
            }
            else {
                var_f30 = (var_f25 - 20.0f) / 3780.0f;
                if (var_f30 >= 1.0f) {
                    var_f30 = 1.0f;
                }
            }
            sp14.x = var_f28;
            sp14.y = var_f26;
            sp14.z = 0.0f;
            sp8.x = 70.0f * var_f30;
            sp8.y = 0.0f;
            sp8.z = 0.0f;
            if (var_r31->unk_C4 > 0) {
                var_f30 = var_r31->unk_C8 * ((float)var_r31->unk_C0 / var_r31->unk_C4);
                var_r25 = (var_r31->unk_C0 * 0x2D) % 360;
                var_f30 = var_f30 * sind(var_r25);
                var_f30 = var_f30;
                sp14.x += var_f30;
                sp14.y += var_f30;
                if (--var_r31->unk_C0 <= 0) {
                    var_r31->unk_C0 = var_r31->unk_C4 = 0;
                }
                var_r22 = 1;
            }
            if (var_r22 == 0) {
                fn_1_9A30(var_r31->unk_0C, 12.0f, &sp14, &sp8, var_f29);
            }
            else {
                fn_1_9A30(var_r31->unk_0C, 3.0f, &sp14, &sp8, var_f29);
            }
        }
        if (var_r31->unk_BC != -1) {
            if (var_r31->unk_BC == 0) {
                var_r31->unk_B8++;
                if (var_r31->unk_B8 == 1) {
                    omVibrate(var_r31->unk_08[0], 0xC, 6, 6);
                    omVibrate(var_r31->unk_08[1], 0xC, 6, 6);
                    return;
                }
                if (var_r31->unk_B8 >= 45.0f) {
                    var_r31->unk_B8 = 0;
                }
            }
            else {
                var_r31->unk_B8++;
                if (var_r31->unk_B8 == 1) {
                    omVibrate(var_r31->unk_08[0], 0xC, 0xC, 0);
                    omVibrate(var_r31->unk_08[1], 0xC, 0xC, 0);
                    return;
                }
                if (var_r31->unk_B8 >= 6.0f) {
                    var_r31->unk_B8 = 0;
                }
            }
        }
    }
    else {
        switch (fn_1_26E0()) {
            case 7:
                if (lbl_1_bss_2A4 != 0) {
                    if (var_r31->unk_14 != 0) {
                        var_r30->unk_20 = 7;
                        var_r30->unk_22 = 0;
                        var_r29->unk_20 = 7;
                        var_r29->unk_22 = 0;
                    }
                    else {
                        var_r30->unk_20 = 9;
                        var_r30->unk_22 = 0;
                        var_r29->unk_20 = 9;
                        var_r29->unk_22 = 0;
                    }
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
                }
                break;
            case 8:
                break;
            case 9:
                if ((var_r31->unk_14 != 0) && (lbl_1_bss_2A4 != 0)) {
                    var_r30->unk_20 = 8;
                    var_r30->unk_22 = 0;
                    var_r29->unk_20 = 8;
                    var_r29->unk_22 = 0;
                }
                break;
        }
    }
}

void fn_1_B3D4(omObjData *object)
{
    s32 var_r31;
    M428DllPlayerWork *work = object->data;
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        fn_1_E5F4(work->unk_00[var_r31]);
        work->unk_00[var_r31] = NULL;
    }
}

void fn_1_B43C(omObjData *object)
{
    M428DllPlayerWork2 *var_r31;
    s32 var_r29;
    s32 var_r28;
    u32 var_r27;
    M428DllPlayerWork *var_r26;
    u32 var_r25;
    u32 var_r24;

    var_r27 = object->work[0];
    var_r25 = object->work[1];
    var_r24 = object->work[2];
    var_r26 = &lbl_1_bss_2AC[var_r25];
    var_r31 = object->data = &lbl_1_bss_2A8[var_r27];
    var_r31->unk_00 = var_r27;
    var_r31->unk_02 = var_r25;
    var_r31->unk_04 = var_r24;
    var_r31->unk_06 = GWPlayerCfg[var_r27].character;
    var_r31->unk_08 = GWPlayerCfg[var_r27].pad_idx;
    var_r31->unk_0A = GWPlayerCfg[var_r27].iscom;
    var_r31->unk_0C = GWPlayerCfg[var_r27].diff;
    if ((var_r31->unk_0A == 0) && ((lbl_1_data_640[var_r31->unk_08] & HuPadRumbleGet()) == 0)) {
        lbl_1_bss_18 = 0;
    }
    if (var_r31->unk_0A != 0) {
        var_r26->unk_0E = var_r26->unk_0E | (1 << var_r31->unk_04);
    }
    var_r31->unk_0E = var_r31->unk_10 = 0;
    var_r31->unk_14 = var_r31->unk_18 = 0.0f;
    var_r31->unk_1C = -1;
    var_r31->unk_1E = 4;
    var_r31->unk_20 = 0;
    var_r31->unk_22 = var_r31->unk_24 = 0;
    var_r31->unk_26 = 0;
    var_r31->unk_28 = 200.0f;
    var_r31->unk_2C = var_r31->unk_28;
    var_r31->unk_30 = 0;
    var_r31->unk_34 = 0;
    var_r31->unk_38 = 0;
    var_r31->unk_3C.x = var_r31->unk_3C.y = var_r31->unk_3C.z = 0.0f;
    var_r31->unk_48.x = var_r31->unk_48.y = var_r31->unk_48.z = 0.0f;
    var_r31->unk_54.x = 0.0f;
    var_r31->unk_54.z = 0.0f;
    var_r31->unk_54.y = 75.0f;
    mtxRot(var_r31->unk_60, 0.0f, 0.0f, 0.0f);
    mtxTransCat(var_r31->unk_60, lbl_1_data_5E0[var_r31->unk_06].x, lbl_1_data_5E0[var_r31->unk_06].y, lbl_1_data_5E0[var_r31->unk_06].z);
    var_r31->unk_90.x = lbl_1_data_150[var_r31->unk_04].x;
    var_r31->unk_90.y = 80.0f + lbl_1_data_150[var_r31->unk_04].y;
    var_r31->unk_90.z = lbl_1_data_150[var_r31->unk_04].z;
    strcpy(var_r31->unk_9C, MakeObjectName(CharModelHookNameGet(var_r31->unk_06, 4, 4)));
    var_r31->unk_19C = -1;
    var_r31->unk_1A0 = 30.0f * ((frand() & 0x7FFF) % 5);
    var_r31->unk_1A4 = 0;
    var_r31->unk_1A8 = 0;
    var_r31->unk_1AC = 0.0f;
    var_r31->unk_1B0 = 0;
    var_r31->unk_1B4 = 0;
    var_r31->unk_1B8.x = 0.5f * (100.0f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
    var_r31->unk_1B8.y = 0.5f * (100.0f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
    var_r31->unk_1B8.z = 0.5f * (100.0f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
    var_r29 = CharModelCreate(var_r31->unk_06, 4);
    object->model[0] = var_r29;
    if (var_r31->unk_02 == 0) {
        Hu3DModelCameraSet(var_r29, 1);
        fn_1_4170(var_r29, 1);
    }
    else {
        Hu3DModelCameraSet(var_r29, 2);
        fn_1_4170(var_r29, 2);
    }
    Hu3DModelLayerSet(var_r29, 2);
    CharModelStepTypeSet(var_r31->unk_06, 0);
    if (var_r31->unk_02 == 0) {
        var_r29 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M428, 0x07));
        object->model[1] = var_r29;
        Hu3DModelCameraSet(var_r29, 1);
    }
    else {
        var_r29 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M428, 0x08));
        object->model[1] = var_r29;
        Hu3DModelCameraSet(var_r29, 2);
    }
    Hu3DModelLayerSet(var_r29, 2);
    for (var_r28 = 0; var_r28 < 0xC; var_r28++) {
        if (lbl_1_data_500[var_r28].unk_00 != 0xFFFFFFFF) {
            object->motion[var_r28] = CharModelMotionCreate(var_r31->unk_06, lbl_1_data_500[var_r28].unk_00);
        }
        else {
            object->motion[var_r28] = Hu3DJointMotionFile(object->model[0], lbl_1_data_560[lbl_1_data_500[var_r28].unk_04][var_r31->unk_06]);
        }
    }
    var_r31->unk_1C = 3;
    CharModelMotionSet(var_r31->unk_06, object->motion[var_r31->unk_1C]);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    CharModelMotionDataClose(var_r31->unk_06);
    object->trans.x = var_r31->unk_48.x = lbl_1_data_150[var_r31->unk_04].x;
    object->trans.y = var_r31->unk_48.y = lbl_1_data_150[var_r31->unk_04].y;
    object->trans.z = var_r31->unk_48.z = lbl_1_data_150[var_r31->unk_04].z;
    object->rot.x = object->rot.z = 0.0f;
    object->rot.y = 180.0f;
    object->func = fn_1_BBD0;
}

void fn_1_BBD0(omObjData *object)
{
    Mtx sp104;
    Vec spF8;
    Vec spEC;
    Vec spE0;
    float var_f31;
    float var_f30;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f22;
    M428DllPlayerWork2 *var_r31;
    M428DllPlayerWork *var_r29;
    omObjData *var_r28;
    M428DllPlayerWork2 *var_r27;
    s32 var_r26;
    ModelData *var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;

    var_r31 = object->data;
    var_r29 = &lbl_1_bss_2AC[var_r31->unk_02];
    var_r22 = var_r31->unk_04 ^ 1;
    var_r28 = var_r29->unk_00[var_r22];
    var_r27 = var_r28->data;
    if (fn_1_26E0() == 4) {
        if (var_r31->unk_0A != 0) {
            var_r31->unk_0E = var_r31->unk_10 = 0;
            var_r31->unk_14 = var_r31->unk_18 = 0.0f;
            fn_1_E600(object);
        }
        else {
            var_r31->unk_0E = HuPadBtnDown[var_r31->unk_08];
            var_r31->unk_10 = HuPadBtn[var_r31->unk_08];
            var_r31->unk_14 = HuPadStkX[var_r31->unk_08];
            var_r31->unk_18 = HuPadStkY[var_r31->unk_08];
        }
    }
    else {
        var_r31->unk_0E = var_r31->unk_10 = 0;
        var_r31->unk_14 = var_r31->unk_18 = 0.0f;
    }
    switch (var_r31->unk_20) {
        case 0:
            var_r31->unk_20 = 1;
            var_r31->unk_22 = 0;
            break;
        case 1:
            if (object->trans.y < 0.0f) {
                object->trans.y += 1.6f;
                var_r26 = 3;
                if ((var_r26 != var_r31->unk_1C) && (CharModelMotionShiftIDGet(var_r31->unk_06) == -1)) {
                    var_r31->unk_1C = var_r26;
                    CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 8.0f, 0x40000001);
                }
            }
            else {
                object->trans.y = 0.0f;
                CharModelMotionSpeedSet(var_r31->unk_06, 0.0f);
            }
            spF8 = var_r31->unk_90;
            VECSubtract(&spF8, &var_r29->unk_64[var_r31->unk_04], &spEC);
            var_r31->unk_30 = 0;
            var_f31 = VECMag(&spEC);
            var_r29->unk_4C[var_r31->unk_04] = var_f31;
            spF8.x = object->trans.x + var_r31->unk_54.x;
            spF8.y = object->trans.y + var_r31->unk_54.y;
            spF8.z = object->trans.z + var_r31->unk_54.z;
            if (fn_1_9990(&spF8) != 0) {
                object->trans.z = 50.0f + spF8.z;
            }
            if (fn_1_26E0() >= 4) {
                var_r31->unk_20 = 2;
                var_r31->unk_22 = 0;
            }
            break;
        case 2:
            if (((var_r31->unk_0E & 0x100) != 0) || (var_r29->unk_24 != 0) || (var_r29->unk_28 != 0)) {
                if (var_r31->unk_1C == 4) {
                    var_r31->unk_1E = 5;
                }
                else {
                    var_r31->unk_1E = 4;
                }
                var_r31->unk_26 = 0;
                var_r31->unk_20 = 3;
                var_r31->unk_22 = 0;
            }
            else {
                if (fabs(var_r31->unk_14) >= 8.0) {
                    var_f27 = 0.025f * var_r31->unk_14;
                }
                else {
                    var_f27 = 0.0f;
                }
                if (fabs(var_r31->unk_18) >= 8.0) {
                    var_f24 = 0.025f * var_r31->unk_18;
                }
                else {
                    var_f24 = 0.0f;
                }
                spE0.x = var_f27;
                spE0.y = var_f24;
                spE0.z = 0.0f;
                if (VECMag(&spE0) > 0.0f) {
                    spF8.x = object->trans.x + var_r31->unk_54.x;
                    spF8.y = object->trans.y + var_r31->unk_54.y;
                    spF8.z = object->trans.z + var_r31->unk_54.z;
                    if (fn_1_F288(&spF8, &spE0, 75.0f) != 0) {
                        object->trans.x += spE0.x;
                        object->trans.y += spE0.y;
                    }
                    else {
                        object->trans.x = spF8.x - var_r31->unk_54.x;
                        object->trans.y = spF8.y - var_r31->unk_54.y;
                    }
                    if ((var_r27->unk_20 == 2) || (var_r27->unk_20 == 3)) {
                        spE0.x = (object->trans.x + var_r31->unk_54.x) - (var_r28->trans.x + var_r27->unk_54.x);
                        spE0.y = (object->trans.y + var_r31->unk_54.y) - (var_r28->trans.y + var_r27->unk_54.y);
                        spE0.z = (object->trans.z + var_r31->unk_54.z) - (var_r28->trans.z + var_r27->unk_54.z);
                        var_f30 = VECMag(&spE0);
                        if (var_f30 <= 200.0f) {
                            if (var_f30 <= 0.0f) {
                                spE0.y = -1.0f;
                            }
                            VECNormalize(&spE0, &spE0);
                            VECScale(&spE0, &spE0, 200.0f);
                            object->trans.x = spE0.x + (var_r28->trans.x + var_r27->unk_54.x);
                            object->trans.y = spE0.y + (var_r28->trans.y + var_r27->unk_54.x);
                            object->trans.z = spE0.z + (var_r28->trans.z + var_r27->unk_54.x);
                        }
                    }
                }
                spF8 = var_r31->unk_90;
                VECSubtract(&spF8, &var_r29->unk_64[var_r31->unk_04], &spEC);
                var_r31->unk_30 = 0;
                var_f31 = VECMag(&spEC);
                var_r29->unk_4C[var_r31->unk_04] = var_f31;
                if (var_f31 > var_r29->unk_54[var_r31->unk_04]) {
                    var_r31->unk_30 = 1;
                    VECNormalize(&spEC, &spEC);
                    VECScale(&spEC, &spEC, var_r29->unk_54[var_r31->unk_04]);
                    VECAdd(&var_r29->unk_64[var_r31->unk_04], &spEC, &spF8);
                    object->trans.x += spF8.x - var_r31->unk_90.x;
                    object->trans.y += spF8.y - var_r31->unk_90.y;
                    object->trans.z += spF8.z - var_r31->unk_90.z;
                    var_r20 = 1;
                }
                if ((var_r20 != 0) || (object->trans.x != var_r31->unk_48.x) || (object->trans.y != var_r31->unk_48.y)) {
                    spF8.x = var_r31->unk_48.x + var_r31->unk_54.x;
                    spF8.y = var_r31->unk_48.y + var_r31->unk_54.y;
                    spF8.z = var_r31->unk_48.z + var_r31->unk_54.z;
                    spE0.x = (object->trans.x + var_r31->unk_54.x) - spF8.x;
                    spE0.y = (object->trans.y + var_r31->unk_54.y) - spF8.y;
                    spE0.z = (object->trans.z + var_r31->unk_54.z) - spF8.z;
                    if (fn_1_F288(&spF8, &spE0, 75.0f) == 0) {
                        object->trans.x = spF8.x - var_r31->unk_54.x;
                        object->trans.y = spF8.y - var_r31->unk_54.y;
                        var_r20 = 1;
                    }
                }
                if (object->trans.x < -700.0f) {
                    object->trans.x = -700.0f;
                }
                else if (object->trans.x > 700.0f) {
                    object->trans.x = 700.0f;
                }
                if (object->trans.y < -200.0f) {
                    object->trans.y = -200.0f;
                }
                spF8.x = object->trans.x + var_r31->unk_54.x;
                spF8.y = object->trans.y + var_r31->unk_54.y;
                spF8.z = object->trans.z + var_r31->unk_54.z;
                if (fn_1_9990(&spF8) != 0) {
                    object->trans.z = 50.0f + spF8.z;
                }
                var_f31 = sqrtf((var_r31->unk_14 * var_r31->unk_14) + (var_r31->unk_18 * var_r31->unk_18));
                var_f31 *= 0.02f;
                CharModelMotionSpeedSet(var_r31->unk_06, var_f31);
                if ((var_f27 == 0.0f) && (var_f24 == 0.0f)) {
                    CharModelMotionSpeedSet(var_r31->unk_06, 0.0f);
                    if ((var_r31->unk_1C != 8) && (var_r31->unk_1C != 9) && (var_r31->unk_1C != 6)) {
                        var_r26 = var_r31->unk_1C;
                    }
                    else {
                        var_r26 = 4;
                    }
                    var_f22 = object->rot.z;
                }
                else {
                    if (fabs(var_f27) > (2.0 * fabs(var_f24))) {
                        if (var_f27 > 0.0f) {
                            var_r26 = 4;
                        }
                        else {
                            var_r26 = 5;
                        }
                        var_f22 = 0.0f;
                    }
                    else {
                        var_r26 = 3;
                        if (var_f24 > 0.0f) {
                            var_f22 = -30.0f * (var_f27 / 1.6f);
                        }
                        else {
                            var_f22 = -(-30.0f * (var_f27 / 1.6f));
                            CharModelMotionSpeedSet(var_r31->unk_06, -var_f31);
                        }
                    }
                }
                if ((var_r26 != var_r31->unk_1C) && (CharModelMotionShiftIDGet(var_r31->unk_06) == -1)) {
                    var_r23 = var_r31->unk_1C;
                    var_r31->unk_1C = var_r26;
                    if (var_r23 != 6) {
                        CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 8.0f, 0x40000001);
                    }
                    else {
                        CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 25.0f, 0x40000001);
                    }
                }
                else {
                    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
                }
                object->rot.x = 0.0f;
                object->rot.y = 180.0f;
                object->rot.z = fn_1_1236C(var_f22, object->rot.z, 1.25f);
            }
            break;
        case 3:
            spF8 = var_r31->unk_90;
            VECSubtract(&spF8, &var_r29->unk_64[var_r31->unk_04], &spEC);
            var_r31->unk_30 = 0;
            var_f31 = VECMag(&spEC);
            var_r29->unk_4C[var_r31->unk_04] = var_f31;
            if (fn_1_26E0() != 4) {
                var_r31->unk_10 = 0;
                var_r31->unk_26 = 0;
            }
            if (((var_r31->unk_10 & 0x100) != 0) || (var_r29->unk_24 != 0) || (var_r29->unk_28 != 0) || (var_r31->unk_26 != 0)) {
                if (var_r31->unk_26 > 0) {
                    var_r31->unk_26--;
                }
                if (var_r29->unk_24 != 0) {
                    if (fabs(var_r29->unk_34) > 0.0) {
                        spF8.x = object->trans.x;
                        spF8.y = object->trans.y;
                        spF8.z = object->trans.z;
                        var_r29->unk_A0.z = object->trans.z;
                        VECSubtract(&var_r29->unk_A0, &spF8, &spEC);
                        var_f30 = VECMag(&spEC);
                        if (var_f30 < var_r29->unk_34) {
                            var_r29->unk_34 = var_f30;
                        }
                        if (var_f30 > 0.0f) {
                            VECNormalize(&spEC, &spEC);
                            VECScale(&spEC, &spEC, var_r29->unk_34);
                            VECAdd(&spF8, &var_r31->unk_54, &spF8);
                            if (fn_1_F288(&spF8, &spEC, 75.0f) != 0) {
                                for (var_r24 = 0; var_r24 < 6; var_r24++) {
                                    spF8.x = object->trans.x + (0.5f * (100.0f * ((0.007874016f * (frand() & 0x7F)) - 0.5f)));
                                    spF8.y = 100.0f + object->trans.y + 0.5f * (100.0f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
                                    spF8.z = object->trans.z - 47.5f;
                                    var_f31 = -22.5f + (45.0f * (0.007874016f * (frand() & 0x7F)));
                                    spE0.x = 2.5 * sind(var_f31);
                                    spE0.y = 2.5 * cosd(var_f31);
                                    spE0.z = 0.0f;
                                    fn_1_11DE4(var_r29->unk_0C, spF8, spE0, 50.0f, 5.0f, 100.0f, 0.5f, lbl_1_data_650);
                                }
                                object->trans.x += spEC.x;
                                object->trans.y += spEC.y;
                            }
                        }
                    }
                }
                spF8.x = object->trans.x;
                spF8.y = object->trans.y;
                spF8.z = object->trans.z;
                if (fn_1_9990(&spF8) != 0) {
                    object->trans.z = 50.0f + spF8.z;
                }
                if (object->trans.x < -700.0f) {
                    object->trans.x = -700.0f;
                }
                else if (object->trans.x > 700.0f) {
                    object->trans.x = 700.0f;
                }
                if (object->trans.y < -200.0f) {
                    object->trans.y = -200.0f;
                }
                if (lbl_1_bss_29C[var_r29->unk_0C] == 5) {
                    var_r26 = 6;
                    if ((object->rot.z > 180.0f) || (object->rot.z < 45.0f)) {
                        object->rot.z += 5.0f;
                    }
                    if (object->rot.z >= 360.0f) {
                        object->rot.z -= 360.0f;
                    }
                }
                else {
                    var_r26 = var_r31->unk_1E;
                    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
                }
                if ((var_r26 != var_r31->unk_1C) && (var_r26 != -1) && (CharModelMotionShiftIDGet(var_r31->unk_06) == -1)) {
                    var_r23 = var_r31->unk_1C;
                    var_r31->unk_1C = var_r26;
                    if (var_r31->unk_1C != 6) {
                        if (var_r23 != 6) {
                            CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 8.0f, 0);
                        }
                        else {
                            CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 25.0f, 0);
                        }
                        CharModelMotionSpeedSet(var_r31->unk_06, 0.0f);
                    }
                    else {
                        CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 8.0f, 0x40000001);
                    }
                }
                if ((var_r31->unk_1C != 6) && (CharModelMotionShiftIDGet(var_r31->unk_06) == -1)) {
                    CharModelMotionTimeSet(var_r31->unk_06, 0.0f);
                    CharModelMotionSpeedSet(var_r31->unk_06, 0.0f);
                }
                if (var_r31->unk_1C == 6) {
                    CharModelMotionSpeedSet(var_r31->unk_06, 2.0f);
                }
            }
            else {
                var_r31->unk_20 = 2;
                var_r31->unk_22 = 0;
            }
            break;
        case 4:
            spF8 = var_r31->unk_90;
            VECSubtract(&spF8, &var_r29->unk_64[var_r31->unk_04], &spEC);
            var_r31->unk_30 = 0;
            var_f31 = VECMag(&spEC);
            var_r29->unk_4C[var_r31->unk_04] = var_f31;
            spF8.x = object->trans.x;
            spF8.y = object->trans.y;
            spF8.z = object->trans.z;
            var_r31->unk_3C.y -= 0.65333337f;
            if (var_r29->unk_38 == -1) {
                var_r29->unk_30 = 400.0f;
                var_r29->unk_94.x = var_r28->trans.x + var_r27->unk_54.x;
                var_r29->unk_94.y = var_r28->trans.y + var_r27->unk_54.y;
                var_r29->unk_94.z = var_r28->trans.z + var_r27->unk_54.z;
            }
            else {
                var_r29->unk_30 = var_r29->unk_48 - var_r29->unk_54[var_r22];
            }
            VECAdd(&spF8, &var_r31->unk_54, &spF8);
            if ((fn_1_F288(&spF8, &var_r31->unk_3C, 75.0f) != 0) && ((object->trans.y + var_r31->unk_3C.y) >= -200.0f)) {
                spF8.x = object->trans.x + var_r31->unk_3C.x;
                spF8.y = object->trans.y + var_r31->unk_3C.y;
                spF8.z = object->trans.z + var_r31->unk_3C.z;
                if (object->trans.x < -700.0f) {
                    object->trans.x = -700.0f;
                }
                else if (object->trans.x > 700.0f) {
                    object->trans.x = 700.0f;
                }
                if (object->trans.y < -200.0f) {
                    object->trans.y = -200.0f;
                }
                VECSubtract(&spF8, &var_r29->unk_94, &spEC);
                var_f31 = VECMag(&spEC);
                if (var_f31 > var_r29->unk_30) {
                    VECNormalize(&spEC, &spEC);
                    VECScale(&spEC, &spEC, var_r29->unk_30);
                    VECAdd(&var_r29->unk_94, &spEC, &spF8);
                    if (fabs(spEC.x) < 180.0) {
                        var_r31->unk_34 = 1;
                    }
                }
                object->trans.x = spF8.x;
                object->trans.y = spF8.y;
                object->trans.z = spF8.z;
            }
            else {
                object->trans.x = spF8.x - var_r31->unk_54.x;
                object->trans.y = spF8.y - var_r31->unk_54.y;
                object->trans.z = spF8.z - var_r31->unk_54.z;
                if ((object->trans.y + var_r31->unk_3C.y) >= -200.0f) {
                    for (var_r24 = 0; var_r24 < 6; var_r24++) {
                        var_f30 = -90.0f + (36.0f * var_r24);
                        spF8.x = object->trans.x + (12.5 * sind(var_f30));
                        spF8.z = object->trans.z + 12.5 * cosd(var_f30);
                        spF8.y = (object->trans.y - 25.0f) + (0.25f * (100.0f * ((0.007874016f * (frand() & 0x7F)) - 0.5f)));
                        var_f31 = -22.5f + (45.0f * (0.007874016f * (frand() & 0x7F)));
                        var_f23 = 0.3f + (0.7f * (0.007874016f * (frand() & 0x7F)));
                        spE0.x = var_f23 * ((2.5 * sind(var_f30)) + (2.5 * sind(var_f31)));
                        spE0.y = var_f23 * (2.5 * cosd(var_f31));
                        spE0.z = var_f23 * (2.5 * cosd(var_f30));
                        fn_1_11DE4(var_r29->unk_0C, spF8, spE0, 100.0f, 5.0f, 100.0f, 0.5f * var_f23, lbl_1_data_654);
                    }
                }
                spF8.x = object->trans.x;
                spF8.y = object->trans.y;
                spF8.z = object->trans.x;
                var_r31->unk_38 = 1;
                var_r31->unk_3C.x = var_r31->unk_3C.y = var_r31->unk_3C.z = 0.0f;
                var_r29->unk_34 = 0.0f;
                var_r31->unk_1E = 4;
                var_r31->unk_26 = 0x12;
                var_r31->unk_20 = 5;
                var_r31->unk_22 = 0;
                break;
            }
            if (var_r31->unk_34 == 0) {
                var_r29->unk_34 = 0.0f;
                var_r31->unk_22++;
                var_r31->unk_24 = 0;
                var_f31 = 2.0f * var_r31->unk_22;
                if (var_f31 >= 90.0f) {
                    var_f31 = 90.0f;
                }
                if ((object->trans.z = object->trans.z + (10.0 * cosd(var_f31))) >= (150.0f + var_r29->unk_AC.z)) {
                    object->trans.z = 150.0f + var_r29->unk_AC.z;
                }
                spF8.x = object->trans.x;
                spF8.y = object->trans.y;
                spF8.z = object->trans.z;
                if (fn_1_9990(&spF8) != 0) {
                    spF8.z += 50.0f;
                }
                else {
                    spF8.z = 50.0f;
                }
                if (object->trans.z < spF8.z) {
                    object->trans.z = spF8.z;
                }
                var_r26 = 8;
                if ((var_r26 != var_r31->unk_1C) && (CharModelMotionShiftIDGet(var_r31->unk_06) == -1)) {
                    var_r31->unk_1C = var_r26;
                    CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 8.0f, 0);
                    CharModelMotionSpeedSet(var_r31->unk_06, 0.0f);
                }
            }
            else {
                spF8.x = object->trans.x;
                spF8.y = object->trans.y;
                spF8.z = object->trans.z;
                VECSubtract(&spF8, &var_r29->unk_94, &spEC);
                if (fabs(spEC.x) < 100.0) {
                    if ((var_r31->unk_3C.y += 0.65333337f) > 0.0f) {
                        var_r31->unk_3C.y = 0.0f;
                    }
                    var_r31->unk_3C.x *= 0.96f;
                    var_r31->unk_3C.y *= 0.97f;
                }
                else {
                    var_r31->unk_22++;
                }
                var_r29->unk_34 = fabs(0.45f * sqrtf((var_r31->unk_3C.x * var_r31->unk_3C.x) + (var_r31->unk_3C.y * var_r31->unk_3C.y)));
                spF8.x = object->trans.x;
                spF8.y = object->trans.y;
                spF8.z = object->trans.z;
                if (fn_1_9990(&spF8) != 0) {
                    spF8.z += 50.0f;
                }
                else {
                    spF8.z = 50.0f;
                }
                if ((object->trans.z -= 5.0f) < spF8.z) {
                    object->trans.z = 50.0f + spF8.z;
                }
                var_r26 = 9;
                if ((var_r26 != var_r31->unk_1C) && (CharModelMotionShiftIDGet(var_r31->unk_06) == -1)) {
                    var_r31->unk_1C = var_r26;
                    CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 8.0f, 0);
                    CharModelMotionSpeedSet(var_r31->unk_06, 0.0f);
                }
                if (++var_r31->unk_24 > var_r31->unk_22) {
                    var_r31->unk_1E = 4;
                    var_r31->unk_26 = 0x12;
                    var_r31->unk_20 = 5;
                    var_r31->unk_22 = 0;
                }
            }

            break;
        case 5:
            spF8 = var_r31->unk_90;
            VECSubtract(&spF8, &var_r29->unk_64[var_r31->unk_04], &spEC);
            var_r31->unk_30 = 0;
            var_f31 = VECMag(&spEC);
            var_r29->unk_4C[var_r31->unk_04] = var_f31;
            if (var_r31->unk_38 != 0) {
                var_r26 = 7;
                if ((var_r26 != var_r31->unk_1C) && (CharModelMotionShiftIDGet(var_r31->unk_06) == -1)) {
                    var_r31->unk_1C = var_r26;
                    CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 8.0f, 0);
                    CharModelMotionSpeedSet(var_r31->unk_06, 0.0f);
                }
            }
            var_r21 = 0;
            if ((var_r27->unk_20 == 2) || (var_r27->unk_20 == 3)) {
                spE0.x = (object->trans.x + var_r31->unk_54.x) - (var_r28->trans.x + var_r27->unk_54.x);
                spE0.y = (object->trans.y + var_r31->unk_54.y) - (var_r28->trans.y + var_r27->unk_54.y);
                spE0.z = (object->trans.z + var_r31->unk_54.z) - (var_r28->trans.z + var_r27->unk_54.z);
                var_f30 = VECMag(&spE0);
                if (var_f30 <= 200.0f) {
                    if (object->trans.x > var_r28->trans.x) {
                        var_f30 = 10.0f;
                    }
                    else {
                        var_f30 = -10.0f;
                    }
                    spF8.x = object->trans.x + var_r31->unk_54.x;
                    spF8.y = object->trans.y + var_r31->unk_54.y;
                    spF8.z = object->trans.z + var_r31->unk_54.z;
                    spE0.x = var_f30;
                    spE0.y = spE0.z = 0.0f;
                    if (fn_1_F288(&spF8, &spE0, 75.0f) != 0) {
                        object->trans.x += spE0.x;
                        object->trans.y += spE0.y;
                        object->trans.z += spE0.z;
                    }
                    else {
                        object->trans.x = spF8.x - var_r31->unk_54.x;
                        object->trans.y = spF8.y - var_r31->unk_54.y;
                        object->trans.z = spF8.z - var_r31->unk_54.z;
                    }
                    spF8.x = var_r28->trans.x + var_r27->unk_54.x;
                    spF8.y = var_r28->trans.y + var_r27->unk_54.y;
                    spF8.z = var_r28->trans.z + var_r27->unk_54.z;
                    spE0.x = -var_f30;
                    spE0.y = spE0.z = 0.0f;
                    if (fn_1_F288(&spF8, &spE0, 75.0f) != 0) {
                        var_r28->trans.x += spE0.x;
                        var_r28->trans.y += spE0.y;
                        var_r28->trans.z += spE0.z;
                    }
                    else {
                        var_r28->trans.x = spF8.x - var_r27->unk_54.x;
                        var_r28->trans.y = spF8.y - var_r27->unk_54.y;
                        var_r28->trans.z = spF8.z - var_r27->unk_54.z;
                    }
                    var_r21 = 1;
                }
            }
            if (object->trans.x < -700.0f) {
                object->trans.x = -700.0f;
            }
            else if (object->trans.x > 700.0f) {
                object->trans.x = 700.0f;
            }
            if (object->trans.y < -200.0f) {
                object->trans.y = -200.0f;
            }
            spF8.x = object->trans.x;
            spF8.y = object->trans.y;
            spF8.z = object->trans.z;
            if (fn_1_9990(&spF8) != 0) {
                spF8.z += 50.0f;
            }
            else {
                spF8.z = 50.0f;
            }
            if ((object->trans.z - spF8.z) > 30.000002f) {
                object->trans.z -= 30.000002f;
            }
            else {
                object->trans.z = spF8.z;
                if (var_r21 == 0) {
                    var_r31->unk_20 = 3;
                    var_r31->unk_22 = 0;
                }
            }
            break;
        case 7:
            object->trans.x = lbl_1_data_180[var_r31->unk_04].x;
            object->trans.y = lbl_1_data_180[var_r31->unk_04].y;
            object->trans.z = lbl_1_data_180[var_r31->unk_04].z;
            object->rot.x = object->rot.y = object->rot.z = 0.0f;
            var_r25 = &Hu3DData[object->model[0]];
            var_r25->unk_F0[0][3] = 0.0f;
            var_r25->unk_F0[1][3] = 0.0f;
            var_r25->unk_F0[2][3] = 0.0f;
            var_r25 = &Hu3DData[object->model[1]];
            MTXIdentity(var_r25->unk_F0);
            Hu3DModelPosSet(
                object->model[1], lbl_1_data_450[var_r31->unk_04].x, lbl_1_data_450[var_r31->unk_04].y, lbl_1_data_450[var_r31->unk_04].z);
            Hu3DModelRotSet(
                object->model[1], lbl_1_data_480[var_r31->unk_04].x, lbl_1_data_480[var_r31->unk_04].y, lbl_1_data_480[var_r31->unk_04].z);
            if (var_r31->unk_02 == 0) {
                fn_1_4170(object->model[1], 1);
            }
            else {
                fn_1_4170(object->model[1], 2);
            }
            var_r26 = 0;
            if ((var_r26 != var_r31->unk_1C) && (CharModelMotionShiftIDGet(var_r31->unk_06) == -1)) {
                var_r31->unk_1C = var_r26;
                CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 8.0f, 0x40000001);
            }
            break;
        case 8:
            var_r26 = 0xA;
            if ((var_r26 != var_r31->unk_1C) && (CharModelMotionShiftIDGet(var_r31->unk_06) == -1)) {
                var_r31->unk_1C = var_r26;
                CharModelMotionShiftSet(var_r31->unk_06, object->motion[var_r31->unk_1C], 0.0f, 8.0f, 0);
            }
            break;
        case 9:
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
            break;
    }
    var_r31->unk_48.x = object->trans.x;
    var_r31->unk_48.y = object->trans.y;
    var_r31->unk_48.z = object->trans.z;
    if (var_r31->unk_20 < 7) {
        if (fn_1_13F54(object->model[0], var_r31->unk_9C, sp104, 0) != 0) {
            var_r25 = &Hu3DData[object->model[1]];
            MTXConcat(sp104, var_r31->unk_60, sp104);
            MTXCopy(sp104, var_r25->unk_F0);
            var_r31->unk_90.x = sp104[0][3];
            var_r31->unk_90.y = sp104[1][3];
            var_r31->unk_90.z = sp104[2][3];
        }
        else {
            OSReport("NO OBJECT %d %s \n", var_r31->unk_06, CharModelHookNameGet(var_r31->unk_06, 4, 4));
        }
        spF8.x = 0.0f;
        spF8.y = 100.0f;
        spF8.z = 0.0f;
        spE0.x = spF8.y * sind((180.0f + object->rot.z));
        spE0.y = spF8.y * sind((90.0f + object->rot.z));
        spE0.z = 0.0f;
        VECSubtract(&spE0, &spF8, &spEC);
        var_r25 = &Hu3DData[object->model[0]];
        var_r25->unk_F0[0][3] = spEC.x;
        var_r25->unk_F0[1][3] = spEC.y;
        var_r25->unk_F0[2][3] = spEC.z;
    }
}

void fn_1_E5F4(omObjData *object)
{
    object->func = NULL;
}

void fn_1_E600(omObjData *object)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    s32 sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    M428DllPlayerWork2 *var_r31;
    M428DllPlayerWork *var_r29;
    omObjData *var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    var_r31 = object->data;
    var_r29 = &lbl_1_bss_2AC[var_r31->unk_02];
    var_r24 = var_r31->unk_04 ^ 1;
    var_r28 = var_r29->unk_00[var_r24];
    if ((var_r29->unk_0E == 3) && (var_r29->unk_10 == var_r31->unk_04)) {
        var_r26 = 1;
    }
    else {
        var_r26 = 0;
    }
    if ((lbl_1_bss_29C[var_r31->unk_02] == 6) || (var_r31->unk_19C == -1)) {
        if (var_r29->unk_0E != 3) {
            var_r31->unk_19C = 2;
        }
        else {
            var_r25 = (s32)(50.0f * (0.007874016f * (frand() & 0x7F))) + var_r31->unk_0C * 0xF + 5;
            var_r31->unk_1A0 = (u8)frand() % 90;
            if (var_r26 == 0) {
                var_r31->unk_1A0 = (u8)frand() % 60;
            }
            if (var_r25 < 0x2D) {
                var_r31->unk_19C = 0;
            }
            else if (var_r25 < 0x4B) {
                var_r31->unk_19C = 1;
            }
            else {
                var_r31->unk_19C = 2;
            }
        }
    }
    var_f31 = 1.0f;
    switch (var_r31->unk_19C) {
        case 0:
            break;
        case 1:
            if (lbl_1_bss_29C[var_r31->unk_02] != 0) {
                if (var_r31->unk_1A0 > 0) {
                    var_r31->unk_1A0--;
                }
                else {
                    var_r31->unk_0E |= 0x100;
                    var_r31->unk_10 |= 0x100;
                }
            }
            break;
        case 2:
            if ((lbl_1_bss_29C[var_r31->unk_02] == 3) || (lbl_1_bss_29C[var_r31->unk_02] == 5)) {
                var_r31->unk_0E |= 0x100;
                var_r31->unk_10 |= 0x100;
            }
            break;
    }
    if (var_r26 != 0) {
        for (var_r27 = 0; var_r27 < 0x10; var_r27++) {
            if ((lbl_1_data_1B0[var_r29->unk_12][var_r27].y - 100.0f) > object->trans.y) {
                break;
            }
        }
        var_r31->unk_1B0 = var_r27;
        sp18 = lbl_1_data_1B0[var_r29->unk_12][var_r31->unk_1B0];
        sp8 = var_r31->unk_1B0;
        sp24.x = object->trans.x;
        sp24.y = object->trans.y;
        sp24.z = object->trans.z;
        VECSubtract(&var_r31->unk_48, &sp24, &spC);
        if ((VECMag(&spC) < 1.0f) && (lbl_1_bss_29C[var_r31->unk_02] != 0)) {
            var_r31->unk_1B4++;
        }
        if (var_r31->unk_1B4 >= 180.0f) {
            if (var_r31->unk_1B4 < 300.0f) {
                if ((var_r31->unk_1B0 >= 2) && (var_r31->unk_1B0 <= 3)) {
                    if (fabs(object->trans.x) < 500.0) {
                        if (object->trans.x > 0.0f) {
                            var_r31->unk_14 = 64.0f;
                        }
                        else {
                            var_r31->unk_14 = -64.0f;
                        }
                    }
                }
                else {
                    if (fabs(object->trans.x) > 50.0) {
                        if (object->trans.x > 0.0f) {
                            var_r31->unk_14 = -64.0f;
                        }
                        else {
                            var_r31->unk_14 = 64.0f;
                        }
                    }
                }
            }
            else if (var_r31->unk_1B0 > 0) {
                var_r31->unk_1B0--;
                var_r31->unk_1B4 = 0;
            }
        }
        else {
            var_r31->unk_1B4 = 0;
            sp24.x = object->trans.x;
            sp24.y = object->trans.y;
            sp24.z = object->trans.z;
            VECAdd(&sp18, &var_r31->unk_1B8, &sp18);
            VECSubtract(&sp18, &sp24, &spC);
            var_f30 = VECMag(&spC);
            VECNormalize(&spC, &spC);
            var_r31->unk_14 = 64.0f * (spC.x * var_f31);
            var_r31->unk_18 = 64.0f * (spC.y * var_f31);
            if (++var_r31->unk_1A4 > 180.0f) {
                var_r31->unk_1B8.x = 0.5f * (100.0f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
                var_r31->unk_1B8.y = 0.5f * (100.0f * (0.007874016f * (frand() & 0x7F)));
                var_r31->unk_1B8.z = 0.5f * (100.0f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
                var_r31->unk_1A4++;
            }
        }
    }
    else {
        sp24.x = object->trans.x;
        sp24.y = object->trans.y;
        sp24.z = object->trans.z;
        sp18.x = var_r28->trans.x;
        sp18.y = var_r28->trans.y;
        sp18.z = var_r28->trans.z;
        VECSubtract(&sp18, &sp24, &spC);
        var_f30 = VECMag(&spC);
        if (var_f30 != 0.0f) {
            var_f29 = atan2d(spC.x, spC.y);
        }
        else {
            spC.y = 1.0f;
            var_f29 = 0.0;
        }
        if (var_f30 < 230.0f) {
            spC.x *= -1.0f;
            spC.y *= -1.0f;
            var_f29 += 180.0f;
        }
        if ((var_f30 >= 250.0f) || (var_f30 <= 230.0f)) {
            VECNormalize(&spC, &spC);
            if (var_f30 >= 250.0f) {
                var_f31 = (var_f30 - 250.0f) / 20.0f;
                if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
            }
            else {
                var_f31 = 1.0f;
            }
            sp24.x = object->trans.x;
            sp24.y = object->trans.y;
            sp24.z = object->trans.z;
            VECAdd(&sp24, &var_r31->unk_54, &sp24);
            var_f29 = var_f29 + var_r31->unk_1AC;
            sp18.x = 64.0 * sind(var_f29);
            sp18.y = 64.0 * cosd(var_f29);
            sp18.z = 0.0f;
            var_r31->unk_14 = sp18.x * var_f31;
            var_r31->unk_18 = sp18.y * var_f31;
            var_r31->unk_1A8 = 0;
        }
    }
    var_r31->unk_1A4++;
}

s32 fn_1_F080(Vec *arg0, Vec *arg1, float arg8)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f31;
    float var_f30;
    s32 var_r31;

    if (VECMag(arg1) <= 0.0f) {
        return 0;
    }
    var_f30 = atan2d(arg1->x, arg1->y);
    var_f30 = var_f30;
    sp24 = *arg0;
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        var_f31 = -45.0f + (15.0f * var_r31);
        var_f31 += var_f30;
        spC.x = sind(var_f31);
        spC.y = cosd(var_f31);
        spC.z = 0.0f;
        VECNormalize(&spC, &spC);
        VECScale(&spC, &spC, arg8);
        VECAdd(arg0, &spC, &sp24);
        if (fn_1_9990(&sp24) != 0) {
            if (var_r31 == 3) {
                sp18 = sp24;
            }
        }
        else {
            break;
        }
    }
    if (var_r31 < 6) {
        return 0;
    }
    return 1;
}

s32 fn_1_F288(Vec *arg0, Vec *arg1, float arg2)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    s32 var_r30;

    sp24 = *arg0;
    sp18 = *arg1;
    var_r30 = fn_1_F538(&sp24, &sp18, &spC, arg2);
    if (var_r30 != 0) {
        *arg0 = spC;
        return 0;
    }
    *arg0 = sp24;
    return 1;
}

s32 fn_1_F354(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_2B8[var_r31]->trans.y < 0.0f) {
            break;
        }
    }
    if (var_r31 < 4) {
        return 0;
    }
    return 1;
}

s32 fn_1_F3BC(s32 arg0)
{
    M428DllPlayerWork *var_r31 = &lbl_1_bss_2AC[arg0];
    if (var_r31->unk_1C >= 3800.0f) {
        return var_r31->unk_18 = 1;
    }
    return var_r31->unk_18 = 0;
}

void fn_1_F414(s32 arg0)
{
    M428DllPlayerWork *var_r31 = &lbl_1_bss_2AC[arg0];
    var_r31->unk_14 = 1;
    lbl_1_bss_2A4 = 1;
}

void fn_1_F454(s32 arg0, s32 arg1)
{
    lbl_1_bss_29C[arg0] = arg1;
}

void fn_1_F46C(s32 arg0, s32 arg1)
{
    if (lbl_1_bss_18 != 0) {
        M428DllPlayerWork *var_r31 = &lbl_1_bss_2AC[arg0];
        var_r31->unk_B8 = 0;
        var_r31->unk_BC = arg1;
    }
}

void fn_1_F4B4(s32 arg0, s32 arg1, float arg8)
{
    M428DllPlayerWork *var_r31 = &lbl_1_bss_2AC[arg0];
    var_r31->unk_C4 = arg1;
    var_r31->unk_C0 = arg1;
    var_r31->unk_C8 = arg8;
}

s32 fn_1_F4E8(s32 arg0)
{
    M428DllPlayerWork *var_r31 = &lbl_1_bss_2AC[arg0];
    if (var_r31->unk_1C >= 500.0f) {
        return 1;
    }
    return 0;
}

s32 fn_1_F538(Vec *arg0, Vec *arg1, Vec *arg2, float arg8)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f30;
    float var_f29;
    M428DllData4B0Struct *var_r30;
    s32 var_r27;

    *arg2 = *arg0;
    var_r30 = lbl_1_data_4B0;
    for (var_r27 = 0; var_r27 < 5; var_r27++, var_r30++) {
        sp38 = var_r30->unk_00;
        VECAdd(arg0, arg1, &sp2C);
        if ((arg0->y >= (sp38.y + arg8)) && (sp2C.y <= (sp38.y + arg8))) {
            sp8.x = sp2C.y - arg0->y;
            sp8.y = arg0->x - sp2C.x;
            sp8.z = -((sp8.x * arg0->x) + (sp8.y * arg0->y));
            var_f29 = -((sp8.z + (sp8.y * (sp38.y + arg8))) / sp8.x);
            if ((var_f29 >= (sp38.x - (var_r30->unk_0C + arg8))) && (var_f29 <= (sp38.x + (var_r30->unk_0C + arg8)))) {
                arg2->x = arg0->x + arg1->x;
                arg2->y = 0.1f + (sp38.y + arg8);
                arg2->z = arg0->z + arg1->z;
                return 1;
            }
        }
        VECSubtract(&sp2C, &sp38, &sp20);
        var_f30 = VECMag(&sp20);
        if (var_f30 == 0.0f) {
            sp20.y = 1.0f;
        }
        sp14 = sp20;
        if ((var_f30 < (var_r30->unk_0C + arg8)) && (sp20.y < arg8)) {
            sp38 = var_r30->unk_00;
            sp2C = *arg0;
            VECSubtract(&sp2C, &sp38, &sp20);
            var_f30 = VECMag(&sp20);
            if (var_f30 == 0.0f) {
                sp20.y = 1.0f;
            }
            if (sp20.y <= arg8) {
                VECNormalize(&sp14, &sp20);
                VECScale(&sp20, &sp20, var_r30->unk_0C + arg8);
                VECAdd(&sp38, &sp20, arg2);
                return 1;
            }
            arg2->x = arg0->x + arg1->x;
            arg2->y = 0.1f + (sp38.y + arg8);
            arg2->z = arg0->z + arg1->z;
            return 1;
        }
    }
    return 0;
}

s32 fn_1_F88C(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    M428DllData4B0Struct *var_r30;
    s32 var_r27;

    *arg2 = *arg0;
    var_r30 = lbl_1_data_4B0;
    for (var_r27 = 0; var_r27 < 5; var_r27++, var_r30++) {
        sp2C = var_r30->unk_00;
        VECAdd(arg0, arg1, &sp20);
        if ((arg0->y >= sp2C.y) && (sp20.y <= sp2C.y)) {
            sp8.x = sp20.y - arg0->y;
            sp8.y = arg0->x - sp20.x;
            sp8.z = -((sp8.x * arg0->x) + (sp8.y * arg0->y));
            var_f30 = -((sp8.z + (sp8.y * sp2C.y)) / sp8.x);
            if ((var_f30 >= (sp2C.x - var_r30->unk_0C)) && (var_f30 <= (sp2C.x + var_r30->unk_0C))) {
                arg2->x = arg0->x + arg1->x;
                arg2->y = sp2C.y;
                arg2->z = arg0->z + arg1->z;
                return 1;
            }
        }
        VECSubtract(&sp20, &sp2C, &sp14);
        var_f31 = VECMag(&sp14);
        if (var_f31 == 0.0f) {
            sp14.y = 1.0f;
        }
        if ((var_f31 < var_r30->unk_0C) && (sp14.y <= 0.0f)) {
            sp2C = var_r30->unk_00;
            sp20 = *arg0;
            VECSubtract(&sp20, &sp2C, &sp14);
            var_f31 = VECMag(&sp14);
            if (var_f31 == 0.0f) {
                sp14.y = 1.0f;
            }
            if (sp14.y <= 0.0f) {
                VECNormalize(&sp14, &sp14);
                VECScale(&sp14, &sp14, var_r30->unk_0C);
                VECAdd(&sp2C, &sp14, arg2);
                return var_r27;
            }
            arg2->x = arg0->x + arg1->x;
            arg2->y = sp2C.y;
            arg2->z = arg0->z + arg1->z;
            return var_r27;
        }
    }
    return -1;
}

s32 fn_1_FB8C(Vec *arg0, Vec *arg1, float arg8, s32 arg2, s32 arg3)
{
    float var_f31;
    M428DllPlayerUnk120Struct *var_r31;
    M428DllPlayerUnkStruct *var_r30;
    s32 var_r29;
    ModelData *var_r28;
    s32 var_r26;

    var_r26 = Hu3DHookFuncCreate(fn_1_102A8);
    var_r28 = &Hu3DData[var_r26];
    Hu3DModelLayerSet(var_r26, 2);
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(M428DllPlayerUnk120Struct), var_r28->unk_48);
    var_r28->unk_120 = var_r31;
    memset(var_r31, 0, sizeof(M428DllPlayerUnk120Struct));
    var_r30 = HuMemDirectMallocNum(HEAP_DATA, arg2 * sizeof(M428DllPlayerUnkStruct), var_r28->unk_48);
    var_r31->unk_54 = var_r30;
    memset(var_r30, 0, arg2 * sizeof(M428DllPlayerUnkStruct));
    var_r31->unk_00 = var_r26;
    var_r31->unk_02 = arg2;
    var_r31->unk_04 = arg8;
    var_r31->unk_08 = arg8 / (arg2 - 1);
    var_r31->unk_0C = 0;
    var_r31->unk_10 = arg3;
    var_r31->unk_14 = 0.0f;
    var_r31->unk_18 = 0.0f;
    var_r31->unk_1C = 0;
    var_r31->unk_20 = *arg0;
    var_r31->unk_2C = *arg1;
    var_r31->unk_38.x = var_r31->unk_38.y = var_r31->unk_38.z = 0.0f;
    var_r31->unk_44 = -1;
    var_r31->unk_48 = var_r31->unk_4C = var_r31->unk_50 = 0.0f;
    for (var_r29 = 0; var_r29 < arg2; var_r29++, var_r30++) {
        var_r30->unk_00 = var_r29;
        if (var_r29 == 0) {
            var_r30->unk_02 = 0;
        }
        else if (var_r29 == (arg2 - 1)) {
            var_r30->unk_02 = 1;
        }
        else {
            var_r30->unk_02 = -1;
        }
        var_r30->unk_04 = 0;
        var_f31 = (float)var_r29 / (arg2 - 1);
        var_r30->unk_08[0].x = var_r31->unk_20.x + (var_f31 * (var_r31->unk_2C.x - var_r31->unk_20.x));
        var_r30->unk_08[0].y = var_r31->unk_20.y + (var_f31 * (var_r31->unk_2C.y - var_r31->unk_20.y));
        var_r30->unk_08[0].z = var_r31->unk_20.z + (var_f31 * (var_r31->unk_2C.z - var_r31->unk_20.z));
        var_r30->unk_08[1] = var_r30->unk_08[0];
        var_r30->unk_08[2] = var_r30->unk_08[0];
        var_r30->unk_08[3].x = var_r30->unk_08[3].y = var_r30->unk_08[3].z = 0.0f;
    }
    return var_r26;
}

void fn_1_FE98(M428DllPlayerUnk120Struct *arg0)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    s32 sp8;
    float var_f31;
    float var_f30;
    M428DllPlayerUnkStruct *var_r30;
    s32 var_r29;

    if (arg0->unk_1C == 0) {
        fn_1_129B4(0.5f, &arg0->unk_20, &arg0->unk_2C, &spC);
        spC.y -= arg0->unk_14 * (0.75f * arg0->unk_04);
        for (var_r30 = arg0->unk_54, var_r29 = 0; var_r29 < arg0->unk_02; var_r29++, var_r30++) {
            var_f31 = (float)var_r29 / (arg0->unk_02 - 1);
            fn_1_12AA4(var_f31, &arg0->unk_20, &spC, &arg0->unk_2C, &var_r30->unk_08[0]);
            fn_1_129B4(var_f31, &arg0->unk_20, &arg0->unk_2C, &var_r30->unk_08[2]);
        }
    }
    else {
        arg0->unk_38.z = 0.5f * (arg0->unk_20.z + arg0->unk_2C.z);
        fn_1_129B4(0.5f, &arg0->unk_20, &arg0->unk_38, &spC);
        spC.y -= arg0->unk_14 * (0.375f * arg0->unk_04);
        for (var_r30 = arg0->unk_54, var_r29 = 0; var_r29 < arg0->unk_44; var_r29++, var_r30++) {
            var_f31 = (float)var_r29 / (arg0->unk_44 - 1);
            fn_1_12AA4(var_f31, &arg0->unk_20, &spC, &arg0->unk_38, &var_r30->unk_08[0]);
            fn_1_129B4(var_f31, &arg0->unk_20, &arg0->unk_38, &var_r30->unk_08[2]);
        }
        fn_1_129B4(0.1f, &arg0->unk_38, &arg0->unk_2C, &spC);
        spC.y -= arg0->unk_18 * (0.375f * arg0->unk_04);
        for (var_r30 = &arg0->unk_54[arg0->unk_44], var_r29 = arg0->unk_44; var_r29 < arg0->unk_02; var_r29++, var_r30++) {
            var_f31 = (float)(var_r29 - arg0->unk_44) / ((arg0->unk_02 - arg0->unk_44) - 1);
            fn_1_12AA4(var_f31, &arg0->unk_38, &spC, &arg0->unk_2C, &var_r30->unk_08[0]);
            fn_1_129B4(var_f31, &arg0->unk_38, &arg0->unk_2C, &var_r30->unk_08[2]);
        }
    }
    for (var_r29 = 0, var_r30 = arg0->unk_54; var_r29 < arg0->unk_02; var_r29++, var_r30++) {
        PSVECSubtract(&var_r30->unk_08[0], &var_r30->unk_08[2], &sp24);
        var_f30 = var_r30->unk_08[0].z;
        if ((sp8 = fn_1_F88C(&var_r30->unk_08[2], &sp24, &sp18)) != -1) {
            var_r30->unk_08[0] = sp18;
            var_r30->unk_08[0].z = var_f30;
            var_r30->unk_04 = 1;
        }
        else {
            var_r30->unk_04 = 0;
        }
        if (var_r30->unk_02 == -1) {
            fn_1_129B4(0.9f, &var_r30->unk_08[1], &var_r30->unk_08[0], &var_r30->unk_08[0]);
        }
        var_r30->unk_08[1] = var_r30->unk_08[0];
    }
}

s32 lbl_1_data_694[2] = { 0xFFA040FF, 0xC8FFFF };
s16 lbl_1_data_69C[2] = { -0x10, 0x10 };
s16 lbl_1_data_6A0[2] = { 0x1A4, 0x60 };
Vec lbl_1_data_6A4[4] = {
    { -0.5f, 0.5f, 0.0f },
    { 0.5f, 0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f },
};
Vec2f lbl_1_data_6D4[4] = { { 0.0f, 0.0f }, { 0.25f, 0.0f }, { 0.25f, 0.25f }, { 0.0f, 0.25f } };

void fn_1_102A8(ModelData *model, Mtx matrix)
{
    Mtx sp8;
    s16 var_r30;

    M428DllPlayerUnk120Struct *var_r31 = model->unk_120;
    if (omPauseChk() == 0) {
        fn_1_FE98(var_r31);
    }
    GXLoadPosMtxImm(matrix, 0);
    MTXInvXpose(matrix, sp8);
    GXLoadNrmMtxImm(sp8, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_SPEC);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetLineWidth(0x10, GX_TO_ZERO);
    // bug, it should be var_r31->unk_54
    DCFlushRange(&var_r31->unk_54, var_r31->unk_02 * sizeof(M428DllPlayerUnkStruct));
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, var_r31->unk_54->unk_08, sizeof(M428DllPlayerUnkStruct));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, &lbl_1_data_694[var_r31->unk_10], 4);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, var_r31->unk_02);
    for (var_r30 = 0; var_r30 < var_r31->unk_02; var_r30++) {
        GXPosition1x16(var_r30);
        GXColor1x16(0);
    }
}

void fn_1_10530(s32 arg0, Vec *arg1, Vec *arg2)
{
    ModelData *var_r30 = &Hu3DData[arg0];
    M428DllPlayerUnk120Struct *var_r31 = var_r30->unk_120;
    var_r31->unk_20 = *arg1;
    var_r31->unk_2C = *arg2;
}

void fn_1_10590(s32 arg0, s32 arg1, s32 arg2, Vec *arg3)
{
    ModelData *var_r30 = &Hu3DData[arg0];
    M428DllPlayerUnk120Struct *var_r31 = var_r30->unk_120;
    var_r31->unk_1C = arg1;
    if (arg1 != 0) {
        var_r31->unk_38 = *arg3;
        var_r31->unk_44 = arg2;
    }
}

void fn_1_105E8(s32 arg0, float arg8, float arg9)
{
    ModelData *var_r30 = &Hu3DData[arg0];
    M428DllPlayerUnk120Struct *var_r31 = var_r30->unk_120;
    if (arg8 > 1.0f) {
        arg8 = 1.0f;
    }
    else if (arg8 < 0.0f) {
        arg8 = 0.0f;
    }
    if (arg9 > 1.0f) {
        arg9 = 1.0f;
    }
    else if (arg9 < 0.0f) {
        arg9 = 0.0f;
    }
    var_r31->unk_14 = arg8;
    var_r31->unk_18 = arg9;
}

s32 fn_1_106A8(s32 arg0, s32 arg1, Vec *arg2, float *arg3)
{
    M428DllPlayerUnkStruct *var_r30;
    s32 var_r29;

    ModelData *var_r28 = &Hu3DData[arg0];
    M428DllPlayerUnk120Struct *var_r31 = var_r28->unk_120;
    float var_f31 = 0.0f;
    for (var_r29 = 0; var_r29 < var_r31->unk_02; var_f31 += var_r31->unk_08, var_r29++) {
        if (arg1 == 0) {
            var_r30 = &var_r31->unk_54[var_r29];
        }
        else {
            var_r30 = &var_r31->unk_54[(var_r31->unk_02 - 1) - var_r29];
        }
        if (var_r30->unk_04 != 0) {
            *arg2 = var_r30->unk_08[0];
            *arg3 = var_f31;
            return 1;
        }
    }
    return 0;
}

s32 fn_1_10788(s32 arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    ModelData *sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    M428DllData4B0Struct *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    sp8 = &Hu3DData[arg0];
    sp18.x = arg2->y - arg1->y;
    sp18.y = arg1->x - arg2->x;
    sp18.z = -((sp18.x * arg1->x) + (sp18.y * arg1->y));
    if (arg1->x < arg2->x) {
        var_f27 = arg1->x;
        var_f26 = arg2->x;
    }
    else {
        var_f27 = arg2->x;
        var_f26 = arg1->x;
    }
    if (arg1->y < arg2->y) {
        var_f30 = arg1->y;
        var_f29 = arg2->y;
    }
    else {
        var_f30 = arg2->y;
        var_f29 = arg1->y;
    }
    for (var_r30 = 0, var_r31 = lbl_1_data_4B0; var_r30 < 5; var_r30++, var_r31++) {
        sp30 = var_r31->unk_00;
        sp30.x -= var_r31->unk_0C;
        sp24 = var_r31->unk_00;
        sp24.x += var_r31->unk_0C;
        spC.x = sp24.y - sp30.y;
        spC.y = sp30.x - sp24.x;
        spC.z = -((spC.x * sp30.x) + (spC.y * sp30.y));
        if ((var_r31->unk_00.y >= var_f30) && (var_r31->unk_00.y <= var_f29) && (sp18.x != 0.0f)) {
            var_f31 = -((sp18.z + (sp18.y * var_r31->unk_00.y)) / sp18.x);
            var_f28 = var_r31->unk_00.y;
            if ((var_f31 >= sp30.x) && (var_f31 <= sp24.x)) {
                var_r29 = 1;
            }
            else {
                var_r29 = 0;
            }
            if ((var_f31 >= var_f27) && (var_f31 <= var_f26) && (var_f28 >= var_f30) && (var_f28 <= var_f29)) {
                var_r28 = 1;
            }
            else {
                var_r28 = 0;
            }
            if ((var_r29 != 0) && (var_r28 != 0)) {
                if (var_f31 < var_r31->unk_00.x) {
                    *arg3 = sp30;
                }
                else {
                    *arg3 = sp24;
                }
                return var_r30;
            }
        }
    }
    return -1;
}

void fn_1_10A88(void)
{
    M428DllPlayerWork3 *var_r31;
    omObjData *var_r30;
    s32 var_r29;
    M428DllPlayerUnk120Struct2 *var_r28;
    ModelData *var_r27;
    s32 var_r26;
    s32 var_r25;

    var_r30 = lbl_1_bss_2B4 = omAddObjEx(lbl_1_bss_2D0, 0x42, 0xA, 0, -1, fn_1_11014);
    var_r31 = var_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M428DllPlayerWork3), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(M428DllPlayerWork3));
    var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_M428, 0x0E), 0x80, 0);
    var_r31->unk_00 = var_r29;
    espDispOn(var_r29);
    espDrawNoSet(var_r29, 0);
    espAttrSet(var_r29, HUSPR_ATTR_NOANIM);
    espPosSet(var_r29, 288.0, 240.0);
    var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_M428, 0x0C), 0x50, 0);
    var_r31->unk_04[0] = var_r29;
    espDispOn(var_r29);
    espDrawNoSet(var_r29, 0);
    espAttrSet(var_r29, HUSPR_ATTR_NOANIM);
    espPosSet(var_r29, 288.0, 240.0);
    var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_M428, 0x0D), 0x50, 0);
    var_r31->unk_04[1] = var_r29;
    espDispOn(var_r29);
    espDrawNoSet(var_r29, 0);
    espAttrSet(var_r29, HUSPR_ATTR_NOANIM);
    espPosSet(var_r29, 288.0, 240.0);
    var_r31->unk_0C[0][0] = var_r31->unk_0C[0][1] = 0.0f;
    var_r31->unk_0C[1][0] = var_r31->unk_0C[1][1] = 0.0f;
    var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_M428, 0x10), 0x100, 0);
    var_r31->unk_1C[0] = var_r29;
    espDispOn(var_r29);
    espDrawNoSet(var_r29, 0);
    espAttrSet(var_r29, HUSPR_ATTR_NOANIM);
    espPosSet(var_r29, 144.0, 240.0);
    espScaleSet(var_r29, 36.0, 60.0);
    espColorSet(var_r29, 0xFF, 0xFF, 0xFF);
    espTPLvlSet(var_r29, 0.0);
    var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_M428, 0x10), 0x100, 0);
    var_r31->unk_1C[1] = var_r29;
    espDispOn(var_r29);
    espDrawNoSet(var_r29, 0);
    espAttrSet(var_r29, HUSPR_ATTR_NOANIM);
    espPosSet(var_r29, 432.0, 240.0);
    espScaleSet(var_r29, 36.0, 60.0);
    espColorSet(var_r29, 0xFF, 0xFF, 0xFF);
    espTPLvlSet(var_r29, 0.0);
    var_r31->unk_24[0][0] = var_r31->unk_24[0][1] = 0.0f;
    var_r31->unk_24[1][0] = var_r31->unk_24[1][1] = 0.0f;
    var_r31->unk_34 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M428, 0x0A), MEMORY_DEFAULT_NUM));
    var_r31->unk_38 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M428, 0x0B), MEMORY_DEFAULT_NUM));
    var_r30->model[0] = fn_1_12CD4(var_r31->unk_34, 2);
    Hu3DModelCameraSet(var_r30->model[0], 1);
    Hu3DModelLayerSet(var_r30->model[0], 5);
    fn_1_13D9C(var_r30->model[0], -1, 0);
    var_r27 = &Hu3DData[var_r30->model[0]];
    var_r28 = var_r27->unk_120;
    var_r28->unk_22 |= 3;
    var_r30->model[1] = fn_1_12CD4(var_r31->unk_38, 2);
    Hu3DModelCameraSet(var_r30->model[1], 1);
    Hu3DModelLayerSet(var_r30->model[1], 5);
    fn_1_13D9C(var_r30->model[1], -1, 0);
    var_r27 = &Hu3DData[var_r30->model[1]];
    var_r28 = var_r27->unk_120;
    var_r28->unk_22 |= 3;
    var_r30->model[2] = fn_1_12CD4(var_r31->unk_34, 2);
    Hu3DModelCameraSet(var_r30->model[2], 2);
    Hu3DModelLayerSet(var_r30->model[2], 5);
    fn_1_13D9C(var_r30->model[2], -1, 0);
    var_r27 = &Hu3DData[var_r30->model[2]];
    var_r28 = var_r27->unk_120;
    var_r28->unk_22 |= 3;
    var_r30->model[3] = fn_1_12CD4(var_r31->unk_38, 2);
    Hu3DModelCameraSet(var_r30->model[3], 2);
    Hu3DModelLayerSet(var_r30->model[3], 5);
    fn_1_13D9C(var_r30->model[3], -1, 0);
    var_r27 = &Hu3DData[var_r30->model[3]];
    var_r28 = var_r27->unk_120;
    var_r28->unk_22 |= 3;
    for (var_r26 = 0; var_r26 < 2; var_r26++) {
        for (var_r25 = 0; var_r25 < 2; var_r25++) {
            var_r31->unk_3C[var_r26][var_r25] = var_r31->unk_4C[var_r26][var_r25] = -1;
        }
    }
}

void fn_1_11014(omObjData *object)
{
    Vec sp20;
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r29;
    omObjData *var_r27;
    M428DllPlayerWork *var_r26;

    M428DllPlayerWork3 *var_r30 = object->data;
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r30->unk_0C[var_r31][0] = var_r30->unk_0C[var_r31][0] + (0.05f * (var_r30->unk_0C[var_r31][1] - var_r30->unk_0C[var_r31][0]));
        var_f30 = lbl_1_data_6A0[0] + (var_r30->unk_0C[var_r31][0] * (lbl_1_data_6A0[1] - lbl_1_data_6A0[0]));
        espPosSet(var_r30->unk_04[var_r31], 288.0f + lbl_1_data_69C[var_r31], var_f30);
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r30->unk_24[var_r31][0] = var_r30->unk_24[var_r31][0] + (0.05f * (var_r30->unk_24[var_r31][1] - var_r30->unk_24[var_r31][0]));
        espTPLvlSet(var_r30->unk_1C[var_r31], var_r30->unk_24[var_r31][0]);
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        for (var_r29 = 0; var_r29 < 2; var_r29++) {
            var_r26 = lbl_1_bss_2C8[var_r31]->data;
            var_r27 = var_r26->unk_00[var_r29];
            if (var_r30->unk_3C[var_r31][var_r29] > 0) {
                var_f31 = (30.0f - var_r30->unk_3C[var_r31][var_r29]) / 6.0f;
                if (var_f31 < 0.0f) {
                    var_f31 = 0.0f;
                }
                else if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                var_f31 = sind((180.0f * var_f31));
                sp20.x = var_r27->trans.x;
                sp20.y = 200.0f + var_r27->trans.y;
                sp20.z = var_r27->trans.z;
                fn_1_13E14(object->model[var_r31 * 2], var_r29, sp20);
                fn_1_13EC8(object->model[var_r31 * 2], var_r29, 125.0f * (1.0f + var_f31));
                var_r30->unk_3C[var_r31][var_r29] -= 1;
            }
            else {
                fn_1_13D9C(object->model[var_r31 * 2], var_r29, 0);
            }
            if (var_r30->unk_4C[var_r31][var_r29] > 0) {
                var_f31 = (30.0f - var_r30->unk_4C[var_r31][var_r29]) / 6.0f;
                if (var_f31 < 0.0f) {
                    var_f31 = 0.0f;
                }
                else if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                var_f31 = sind((180.0f * var_f31));
                sp20.x = var_r27->trans.x;
                sp20.y = 200.0f + var_r27->trans.y;
                sp20.z = var_r27->trans.z;
                fn_1_13E14(object->model[(var_r31 * 2) + 1], var_r29, sp20);
                fn_1_13EC8(object->model[(var_r31 * 2) + 1], var_r29, 125.0f * (1.0f + var_f31));
                var_r30->unk_4C[var_r31][var_r29] -= 1;
            }
            else {
                fn_1_13D9C(object->model[(var_r31 * 2) + 1], var_r29, 0);
            }
        }
    }
}

void fn_1_115F8(void)
{
    M428DllPlayerWork3 *var_r31 = lbl_1_bss_2B4->data;
    espKill(var_r31->unk_00);
    espKill(var_r31->unk_04[0]);
    espKill(var_r31->unk_04[1]);
    espKill(var_r31->unk_1C[0]);
    espKill(var_r31->unk_1C[1]);
    Hu3DModelKill(lbl_1_bss_2B4->model[0]);
    Hu3DModelKill(lbl_1_bss_2B4->model[1]);
    Hu3DModelKill(lbl_1_bss_2B4->model[2]);
    Hu3DModelKill(lbl_1_bss_2B4->model[3]);
    HuSprAnimKill(var_r31->unk_34);
    HuSprAnimKill(var_r31->unk_38);
}

void fn_1_116C4(s32 arg0, s32 arg1)
{
    if (lbl_1_bss_2B4) {
        s32 var_r31;
        M428DllPlayerWork3 *var_r30 = lbl_1_bss_2B4->data;
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            if (arg1 == 0) {
                var_r30->unk_3C[arg0][var_r31] = 0x1E;
            }
            else {
                var_r30->unk_4C[arg0][var_r31] = 0x1E;
            }
        }
    }
}

void fn_1_11754(s32 arg0, float arg8)
{
    if (lbl_1_bss_2B4) {
        M428DllPlayerWork3 *var_r31 = lbl_1_bss_2B4->data;
        var_r31->unk_24[arg0][1] = arg8;
    }
}

void fn_1_11798(s32 sp8)
{
    s32 var_r30;
    s32 var_r29;

    if (lbl_1_bss_2B4) {
        M428DllPlayerWork3 *work = lbl_1_bss_2B4->data;
        if (sp8 == 0) {
            espDispOff(work->unk_00);
            espDispOff(work->unk_04[0]);
            espDispOff(work->unk_04[1]);
            espDispOff(work->unk_1C[0]);
            espDispOff(work->unk_1C[1]);
        }
        else {
            espDispOn(work->unk_00);
            espDispOn(work->unk_04[0]);
            espDispOn(work->unk_04[1]);
            espDispOn(work->unk_1C[0]);
            espDispOn(work->unk_1C[1]);
        }
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            for (var_r29 = 0; var_r29 < 2; var_r29++) {
                work->unk_3C[var_r30][var_r29] = work->unk_4C[var_r30][var_r29] = -1;
            }
        }
    }
}

void fn_1_118A8(s32 arg0, float var_f1)
{
    M428DllPlayerWork3 *var_r31;
    if (lbl_1_bss_2B4) {
        var_r31 = lbl_1_bss_2B4->data;
        if (var_f1 < 0.0f) {
            var_f1 = 0.0f;
        }
        else if (var_f1 > 1.0f) {
            var_f1 = 1.0f;
        }
        var_r31->unk_0C[arg0][1] = var_f1;
    }
}

void fn_1_11930(void)
{
    M428DllPlayerWork4 *var_r31;
    s32 var_r30;
    s32 var_r29;
    omObjData *var_r28;
    M428DllPlayerUnk120Struct2 *var_r27;
    ModelData *var_r26;
    AnimData *var_r25;

    var_r28 = lbl_1_bss_2B0 = omAddObjEx(lbl_1_bss_2D0, 0xBF, 0, 0, -1, fn_1_11A60);
    var_r31 = var_r28->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M428DllPlayerWork4), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(M428DllPlayerWork4));
    var_r25 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M428, 0x0F), MEMORY_DEFAULT_NUM));
    var_r31->unk_10 = var_r25;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r29 = fn_1_12CD4(var_r25, 0x200);
        var_r31->unk_00[var_r30] = var_r29;
        if (var_r30 == 0) {
            Hu3DModelCameraSet(var_r29, 1);
        }
        else {
            Hu3DModelCameraSet(var_r29, 2);
        }
        Hu3DModelLayerSet(var_r29, 3);
        var_r31->unk_08[var_r30] = 0;
        var_r26 = &Hu3DData[var_r29];
        var_r27 = var_r26->unk_120;
        var_r27->unk_20 = 0;
    }
}

void fn_1_11A60(omObjData *object)
{
    s32 temp_r4;
    M428DllPlayerUnkStruct2 *var_r31;
    M428DllPlayerWork4 *var_r30;
    s32 var_r29;
    M428DllPlayerUnk120Struct2 *var_r28;
    s32 var_r27;
    ModelData *var_r26;

    var_r30 = object->data;
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        if (var_r30->unk_08[var_r29] <= 0) {
            Hu3DModelAttrSet(var_r30->unk_00[var_r29], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(var_r30->unk_00[var_r29], HU3D_ATTR_DISPOFF);
            var_r26 = &Hu3DData[var_r30->unk_00[var_r29]];
            var_r28 = var_r26->unk_120;
            var_r31 = var_r28->unk_3C;
            var_r28->unk_23 = 0;
            for (var_r27 = 0; var_r27 < var_r28->unk_26; var_r27++, var_r31++) {
                if (!(var_r31->unk_30 <= 0.0f)) {
                    var_r31->unk_38.x += var_r31->unk_04;
                    var_r31->unk_38.y += var_r31->unk_08;
                    var_r31->unk_38.z += var_r31->unk_0C;
                    var_r31->unk_34 = var_r31->unk_34 + var_r31->unk_18;
                    if (var_r31->unk_34 >= 360.0f) {
                        var_r31->unk_34 = var_r31->unk_34 - 360.0f;
                    }
                    var_r31->unk_48 = var_r31->unk_28;
                    var_r31->unk_28 = var_r31->unk_28 + var_r31->unk_2C;
                    if (var_r31->unk_48 >= 0x10) {
                        var_r31->unk_48 = 0;
                        var_r31->unk_00 = 0;
                        var_r31->unk_30 = 0.0f;
                        var_r30->unk_08[var_r29] -= 1;
                    }
                }
            }
        }
    }
}

void fn_1_11C20(void)
{

    omObjData *var_r30 = lbl_1_bss_2B0;
    M428DllPlayerWork4 *var_r31 = var_r30->data;
    Hu3DModelAttrSet(var_r31->unk_00[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->unk_00[1], HU3D_ATTR_DISPOFF);
    HuSprAnimKill(var_r31->unk_10);
    var_r30->func = NULL;
}

s32 fn_1_11C8C(s32 arg0, Vec arg1, Vec arg2, GXColor arg3, float arg8, float arg9, float argA)
{
    M428DllPlayerUnkStruct2 *var_r31;
    M428DllPlayerUnk120Struct2 *var_r30;
    s32 var_r29;
    M428DllPlayerWork4 *var_r28;
    omObjData *var_r27;
    ModelData *var_r26;

    var_r27 = lbl_1_bss_2B0;
    var_r28 = var_r27->data;
    var_r26 = &Hu3DData[var_r28->unk_00[arg0]];
    var_r30 = var_r26->unk_120;
    for (var_r31 = var_r30->unk_3C, var_r29 = 0; var_r29 < var_r30->unk_26; var_r29++, var_r31++) {
        if (var_r31->unk_30 <= 0.0f) {
            break;
        }
    }
    if (var_r29 >= var_r30->unk_26) {
        return -1;
    }
    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r31->unk_38.x = arg1.x;
    var_r31->unk_38.y = arg1.y;
    var_r31->unk_38.z = arg1.z;
    var_r31->unk_04 = arg2.x;
    var_r31->unk_08 = arg2.y;
    var_r31->unk_0C = arg2.z;
    var_r31->unk_18 = arg9;
    var_r31->unk_30 = arg8;
    var_r31->unk_44.r = arg3.r;
    var_r31->unk_44.g = arg3.g;
    var_r31->unk_44.b = arg3.b;
    var_r31->unk_44.a = arg3.a;
    var_r31->unk_34 = 0.0f;
    var_r31->unk_48 = 0;
    var_r31->unk_00 = 0;
    var_r31->unk_28 = 0.0f;
    var_r31->unk_2C = argA;
    var_r28->unk_08[arg0]++;
    return var_r29;
}

static inline s32 fn_1_11C8C_inlined(s32 arg0, Vec arg1, Vec arg2, GXColor arg3, float arg8, float arg9, float argA)
{
    M428DllPlayerUnkStruct2 *var_r31;
    M428DllPlayerUnk120Struct2 *var_r30;
    s32 var_r29;
    M428DllPlayerWork4 *var_r28;
    omObjData *var_r27;
    ModelData *var_r26;

    var_r27 = lbl_1_bss_2B0;
    var_r28 = var_r27->data;
    var_r26 = &Hu3DData[var_r28->unk_00[arg0]];
    var_r30 = var_r26->unk_120;
    for (var_r31 = var_r30->unk_3C, var_r29 = 0; var_r29 < var_r30->unk_26; var_r29++, var_r31++) {
        if (var_r31->unk_30 <= 0.0f) {
            break;
        }
    }
    if (var_r29 >= var_r30->unk_26) {
        return -1;
    }
    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r31->unk_38.x = arg1.x;
    var_r31->unk_38.y = arg1.y;
    var_r31->unk_38.z = arg1.z;
    var_r31->unk_04 = arg2.x;
    var_r31->unk_08 = arg2.y;
    var_r31->unk_0C = arg2.z;
    var_r31->unk_18 = arg9;
    var_r31->unk_30 = arg8;
    var_r31->unk_44.r = arg3.r;
    var_r31->unk_44.g = arg3.g;
    var_r31->unk_44.b = arg3.b;
    var_r31->unk_44.a = arg3.a;
    var_r31->unk_34 = 0.0f;
    var_r31->unk_48 = 0;
    var_r31->unk_00 = 0;
    var_r31->unk_28 = 0.0f;
    var_r31->unk_2C = argA;
    var_r28->unk_08[arg0]++;
    return var_r29;
}

s32 fn_1_11DE4(s32 arg0, Vec arg1, Vec arg2, float arg8, float arg9, float argA, float argB, GXColor arg3)
{
    Vec sp64;
    Vec sp58;
    s32 sp24;
    s32 sp20;
    float var_f31;

    sp58.x = arg2.z;
    sp58.z = arg2.x;
    sp58.y = 0.0f;
    VECNormalize(&sp58, &sp58);
    var_f31 = 0.5f * argA;
    sp64.x = arg1.x + (sp58.x * var_f31);
    sp64.y = arg1.y + (sp58.y * var_f31);
    sp64.z = arg1.z + (sp58.z * var_f31);

    sp24 = fn_1_11C8C_inlined(arg0, sp64, arg2, arg3, arg8, arg9, argB);
    sp64.x = arg1.x - (sp58.x * var_f31);
    sp64.y = arg1.y - (sp58.y * var_f31);
    sp64.z = arg1.z - (sp58.z * var_f31);

    sp20 = fn_1_11C8C_inlined(arg0, sp64, arg2, arg3, arg8, -arg9, argB);
    return (sp24 << 0x10) | sp20;
}

float fn_1_12254(float arg8, float arg9)
{
    float var_f31;

    if (arg8 >= 360.0f) {
        arg8 -= 360.0f;
    }
    else if (arg8 < 0.0f) {
        arg8 += 360.0f;
    }
    if (arg9 >= 360.0f) {
        arg9 -= 360.0f;
    }
    else if (arg9 < 0.0f) {
        arg9 += 360.0f;
    }
    var_f31 = arg8 - arg9;
    if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    }
    else if (var_f31 >= 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}

float fn_1_1236C(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;

    if (arg8 >= 360.0) {
        arg8 -= 360.0;
    }
    else if (arg8 < 0.0) {
        arg8 += 360.0;
    }
    if (arg9 >= 360.0) {
        arg9 -= 360.0;
    }
    else if (arg9 < 0.0) {
        arg9 += 360.0;
    }
    var_f30 = 360.0 + (arg8 - arg9);
    if (fabs(var_f30) >= 360.0) {
        var_f30 = fmod(var_f30, 360.0);
    }
    if (var_f30 < 180.0) {
        if (var_f30 <= argA) {
            var_f31 = var_f30;
        }
        else {
            var_f31 = argA;
        }
    }
    else if (360.0 - var_f30 <= argA) {
        var_f31 = -(360.0 - var_f30);
    }
    else {
        var_f31 = -argA;
    }
    var_f31 += arg9;
    if (var_f31 >= 360.0) {
        var_f31 -= 360.0;
    }
    else if (var_f31 < 0.0) {
        var_f31 += 360.0;
    }
    return var_f31;
}

float fn_1_125BC(float arg8, float arg9, float argA)
{
    float var_f24;
    float var_f23;

    var_f23 = fn_1_12254(argA, arg9);
    var_f24 = fabs(var_f23 * arg8);
    return fn_1_1236C(argA, arg9, var_f24);
}

void fn_1_129B4(float arg8, Vec *arg0, Vec *arg1, Vec *arg2)
{
    Vec sp8;
    sp8.x = arg0->x + (arg8 * (arg1->x - arg0->x));
    sp8.y = arg0->y + (arg8 * (arg1->y - arg0->y));
    sp8.z = arg0->z + (arg8 * (arg1->z - arg0->z));
    *arg2 = sp8;
}

float fn_1_12A2C(float arg8, float arg9, float argA, float argB)
{
    float var_f31;
    float var_f30;

    var_f31 = 1.0 - arg8;
    var_f30 = (argB * (arg8 * arg8)) + ((arg9 * (var_f31 * var_f31)) + (2.0 * (argA * (var_f31 * arg8))));
    return var_f30;
}

void fn_1_12AA4(float arg8, Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    arg3->x = fn_1_12A2C(arg8, arg0->x, arg1->x, arg2->x);
    arg3->y = fn_1_12A2C(arg8, arg0->y, arg1->y, arg2->y);
    arg3->z = fn_1_12A2C(arg8, arg0->z, arg1->z, arg2->z);
}

s16 fn_1_12CD4(AnimData *sp8, s16 var_r26)
{
    s16 var_r30;
    M428DllPlayerUnkStruct2 *var_r29;
    Vec2f *var_r28;
    Vec *var_r25;
    void *var_r24;
    void *var_r22;

    s16 var_r23 = Hu3DHookFuncCreate(fn_1_134C0);
    ModelData *var_r27 = &Hu3DData[var_r23];
    M428DllPlayerUnk120Struct2 *var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(M428DllPlayerUnk120Struct2), var_r27->unk_48);
    var_r27->unk_120 = var_r31;
    var_r31->unk_38 = sp8;
    var_r31->unk_26 = var_r26;
    var_r31->unk_20 = 0;
    var_r31->unk_22 = 0;
    var_r31->unk_4C = 0;
    var_r31->unk_50 = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_21 = 0;
    var_r31->unk_23 = 0;
    var_r31->unk_30 = 0;
    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r29 = HuMemDirectMallocNum(HEAP_DATA, var_r26 * sizeof(M428DllPlayerUnkStruct2), var_r27->unk_48);
    var_r31->unk_3C = var_r29;
    memset(var_r29, 0, var_r26 * sizeof(M428DllPlayerUnkStruct2));
    for (var_r30 = 0; var_r30 < var_r26; var_r30++, var_r29++) {
        var_r29->unk_30 = 0.0f;
        var_r29->unk_34 = 0.0f;
        var_r29->unk_28 = 0.0f;
        var_r29->unk_2C = 1.0f;
        var_r29->unk_38.x = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r29->unk_38.y = ((frand() & 0x7F) - 0x40) * 0x1E;
        var_r29->unk_38.z = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r29->unk_44.r = var_r29->unk_44.g = var_r29->unk_44.b = var_r29->unk_44.a = 0xFF;
        var_r29->unk_48 = 0;
    }
    var_r25 = HuMemDirectMallocNum(HEAP_DATA, var_r26 * sizeof(Vec) * 4, var_r27->unk_48);
    var_r31->unk_40 = var_r25;
    for (var_r30 = 0; var_r30 < (var_r26 * 4); var_r30++, var_r25++) {
        var_r25->x = var_r25->y = var_r25->z = 0.0f;
    }
    var_r28 = HuMemDirectMallocNum(HEAP_DATA, var_r26 * sizeof(Vec2f) * 4, var_r27->unk_48);
    var_r31->unk_44 = var_r28;
    for (var_r30 = 0; var_r30 < var_r26; var_r30++) {
        var_r28->x = 0.0f;
        var_r28->y = 0.0f;
        var_r28++;
        var_r28->x = 1.0f;
        var_r28->y = 0.0f;
        var_r28++;
        var_r28->x = 1.0f;
        var_r28->y = 1.0f;
        var_r28++;
        var_r28->x = 0.0f;
        var_r28->y = 1.0f;
        var_r28++;
    }
    var_r24 = HuMemDirectMallocNum(HEAP_DATA, 0x10000, var_r27->unk_48);
    var_r22 = var_r24;
    DCFlushRange(var_r24, 0x10000);
    GXBeginDisplayList(var_r22, 0x10000);
    GXBegin(GX_QUADS, GX_VTXFMT0, var_r26 * 4);
    for (var_r30 = 0; var_r30 < var_r26; var_r30++) {
        GXUnknownu16(var_r30 * 4);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4);
        GXUnknownu16(var_r30 * 4 + 1);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4 + 1);
        GXUnknownu16(var_r30 * 4 + 2);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4 + 2);
        GXUnknownu16(var_r30 * 4 + 3);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4 + 3);
    }
    var_r31->unk_34 = GXEndDisplayList();
    var_r31->unk_48 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_34, var_r27->unk_48);
    memcpy(var_r31->unk_48, var_r24, var_r31->unk_34);
    DCFlushRange(var_r31->unk_48, var_r31->unk_34);
    HuMemDirectFree(var_r24);
    (void)var_r30;
    (void)var_r26;
    return var_r23;
}

s16 fn_1_13184(s16 sp8)
{
    M428DllPlayerUnk120Struct2 *var_r31;
    M428DllPlayerUnkStruct2 *var_r30;
    Vec2f *var_r29;
    s16 var_r28;
    ModelData *var_r27;
    M428DllPlayerUnk120Struct2 *var_r26;
    Vec *var_r25;
    s32 var_r24;
    ModelData *var_r23;
    s16 var_r22;

    var_r23 = &Hu3DData[sp8];
    var_r26 = var_r23->unk_120;
    var_r22 = Hu3DHookFuncCreate(var_r23->hook);
    var_r27 = &Hu3DData[var_r22];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(M428DllPlayerUnk120Struct2), var_r27->unk_48);
    var_r27->unk_120 = var_r31;
    var_r31->unk_38 = var_r26->unk_38;
    var_r31->unk_26 = var_r26->unk_26;
    var_r24 = var_r31->unk_26;
    var_r31->unk_20 = 0;
    var_r31->unk_22 = var_r26->unk_22;
    var_r31->unk_4C = NULL;
    var_r31->unk_50 = NULL;
    var_r31->unk_28 = 0;
    var_r31->unk_21 = 0;
    var_r31->unk_30 = 0;
    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r30 = HuMemDirectMallocNum(HEAP_DATA, var_r24 * sizeof(M428DllPlayerUnkStruct2), var_r27->unk_48);
    var_r31->unk_3C = var_r30;
    for (var_r28 = 0; var_r28 < var_r24; var_r28++, var_r30++) {
        var_r30->unk_30 = 0.0f;
        var_r30->unk_34 = 0.0f;
        var_r30->unk_28 = 0.0f;
        var_r30->unk_2C = 1.0f;
        var_r30->unk_38.x = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r30->unk_38.y = ((frand() & 0x7F) - 0x40) * 0x1E;
        var_r30->unk_38.z = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r30->unk_44.r = var_r30->unk_44.g = var_r30->unk_44.b = var_r30->unk_44.a = 0xFF;
        var_r30->unk_48 = 0;
    }
    var_r25 = HuMemDirectMallocNum(HEAP_DATA, var_r24 * sizeof(Vec) * 4, var_r27->unk_48);
    var_r31->unk_40 = var_r25;
    for (var_r28 = 0; var_r28 < (var_r24 * 4); var_r28++, var_r25++) {
        var_r25->x = var_r25->y = var_r25->z = 0.0f;
    }
    var_r29 = HuMemDirectMallocNum(HEAP_DATA, var_r24 * sizeof(Vec2f) * 4, var_r27->unk_48);
    var_r31->unk_44 = var_r29;
    for (var_r28 = 0; var_r28 < var_r24; var_r28++) {
        var_r29->x = 0.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 1.0f;
        var_r29++;
        var_r29->x = 0.0f;
        var_r29->y = 1.0f;
        var_r29++;
    }
    var_r31->unk_34 = var_r26->unk_34;
    var_r31->unk_48 = var_r26->unk_48;
    return var_r22;
}

void fn_1_134C0(ModelData *var_r23, Mtx var_r22)
{
    Mtx sp128;
    Mtx spF8;
    Mtx spC8;
    Vec sp98[4];
    Vec sp68[4];
    Vec sp38[4];
    ROMtx sp8;
    M428DllPlayerUnk120Struct2 *var_r31;
    Vec *var_r30;
    M428DllPlayerUnkStruct2 *var_r29;
    Vec2f *var_r28;
    Vec *var_r27;
    s16 var_r26;
    s16 var_r25;
    Vec *var_r24;
    s16 var_r21;
    s16 var_r20;
    s16 var_r19;
    M428DllPlayerHook var_r18;

    var_r31 = var_r23->unk_120;
    if ((var_r31->unk_2C != GlobalCounter) || (shadowModelDrawF != 0)) {
        if ((var_r31->unk_50) && (var_r31->unk_50 != var_r23)) {
            fn_1_134C0(var_r31->unk_50, var_r22);
        }
        GXLoadPosMtxImm(var_r22, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        if (shadowModelDrawF != 0) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        }
        else {
            var_r21 = var_r31->unk_38->bmp->dataFmt & 0xF;
            if ((var_r21 == 7) || (var_r21 == 8)) {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            }
            else {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            }
            if ((var_r31->unk_22 & 1) != 0) {
                GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
            }
            else if ((var_r23->attr & 2) != 0) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            }
            else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            }
        }
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
        HuSprTexLoad(var_r31->unk_38, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(0);
        switch (var_r31->unk_20) {
            case 0:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
                break;
            case 1:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
                break;
            case 2:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
                break;
        }
        if (HmfInverseMtxF3X3(var_r22, &sp128[0]) == 0) {
            MTXIdentity(sp128);
        }
        PSMTXReorder(sp128, sp8);
        if (var_r31->unk_4C) {
            var_r18 = var_r31->unk_4C;
            var_r18(var_r23, var_r31, var_r22);
        }
        var_r29 = var_r31->unk_3C;
        var_r30 = var_r31->unk_40;
        var_r28 = var_r31->unk_44;
        PSMTXROMultVecArray(sp8, lbl_1_data_6A4, &sp38[0], 4);
        for (var_r26 = 0; var_r26 < var_r31->unk_26; var_r26++, var_r29++) {
            if (!var_r29->unk_30) {
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
            }
            else if (!var_r29->unk_34) {
                var_r27 = &sp98[0];
                var_r24 = &sp38[0];
                VECScale(var_r24++, var_r27, var_r29->unk_30);
                VECAdd(var_r27++, &var_r29->unk_38, var_r30++);
                VECScale(var_r24++, var_r27, var_r29->unk_30);
                VECAdd(var_r27++, &var_r29->unk_38, var_r30++);
                VECScale(var_r24++, var_r27, var_r29->unk_30);
                VECAdd(var_r27++, &var_r29->unk_38, var_r30++);
                VECScale(var_r24++, var_r27, var_r29->unk_30);
                VECAdd(var_r27++, &var_r29->unk_38, var_r30++);
            }
            else {
                VECScale(lbl_1_data_6A4, &sp98[0], var_r29->unk_30);
                VECScale(&lbl_1_data_6A4[1], &sp98[1], var_r29->unk_30);
                VECScale(&lbl_1_data_6A4[2], &sp98[2], var_r29->unk_30);
                VECScale(&lbl_1_data_6A4[3], &sp98[3], var_r29->unk_30);
                MTXRotRad(spC8, 0x5A, var_r29->unk_34);
                MTXConcat(&sp128[0], spC8, spF8);
                MTXMultVecArray(spF8, &sp98[0], &sp68[0], 4);
                VECAdd(&sp68[0], &var_r29->unk_38, var_r30++);
                VECAdd(&sp68[1], &var_r29->unk_38, var_r30++);
                VECAdd(&sp68[2], &var_r29->unk_38, var_r30++);
                VECAdd(&sp68[3], &var_r29->unk_38, var_r30++);
            }
        }
        var_r29 = var_r31->unk_3C;
        var_r28 = var_r31->unk_44;
        if ((var_r31->unk_22 & 2) == 0) {
            for (var_r26 = 0; var_r26 < var_r31->unk_26; var_r26++, var_r29++) {
                var_r20 = var_r29->unk_48 & 3;
                var_r19 = (var_r29->unk_48 >> 2) & 3;
                for (var_r25 = 0; var_r25 < 4; var_r25++, var_r28++) {
                    var_r28->x = (0.25f * var_r20) + lbl_1_data_6D4[var_r25].x;
                    var_r28->y = (0.25f * var_r19) + lbl_1_data_6D4[var_r25].y;
                }
            }
        }
        else {
            for (var_r26 = 0; var_r26 < var_r31->unk_26; var_r26++, var_r29++) {
                for (var_r25 = 0; var_r25 < 4; var_r25++, var_r28++) {
                    var_r28->x = 4.0f * lbl_1_data_6D4[var_r25].x;
                    var_r28->y = 4.0f * lbl_1_data_6D4[var_r25].y;
                }
            }
        }
        DCFlushRangeNoSync(var_r31->unk_40, var_r31->unk_26 * 0xC * 4);
        DCFlushRangeNoSync(var_r31->unk_44, var_r31->unk_26 * 8 * 4);
        DCFlushRangeNoSync(var_r31->unk_3C, var_r31->unk_26 * 0x4C);
        PPCSync();
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetArray(GX_VA_POS, var_r31->unk_40, sizeof(Vec));
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetArray(GX_VA_CLR0, &var_r31->unk_3C->unk_44, sizeof(M428DllPlayerUnkStruct2)); // bug?
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetArray(GX_VA_TEX0, var_r31->unk_44, sizeof(Vec2f));
        GXCallDisplayList(var_r31->unk_48, var_r31->unk_34);
        if (shadowModelDrawF == 0) {
            if ((var_r31->unk_21 & 2) == 0) {
                var_r31->unk_28++;
            }
            if ((var_r31->unk_30 != 0) && (var_r31->unk_30 <= var_r31->unk_28)) {
                if ((var_r31->unk_21 & 1) != 0) {
                    var_r31->unk_28 = 0;
                }
                var_r31->unk_28 = var_r31->unk_30;
            }
            var_r31->unk_2C = GlobalCounter;
        }
    }
}

void fn_1_13D9C(s16 arg0, s16 arg1, s32 arg2)
{
    if (arg2 == 0) {
        fn_1_13EC8(arg0, arg1, 0.0f);
        return;
    }
    fn_1_13EC8(arg0, arg1, 1.0f);
}

void fn_1_13E14(s16 arg0, s16 arg1, Vec arg2)
{
    M428DllPlayerUnkStruct2 *var_r31;
    M428DllPlayerUnk120Struct2 *var_r30;
    s32 var_r29;
    ModelData *var_r28;

    var_r28 = &Hu3DData[arg0];
    var_r30 = var_r28->unk_120;
    if (arg1 != -1) {
        var_r31 = &var_r30->unk_3C[arg1];
        var_r31->unk_38 = arg2;
        return;
    }
    for (var_r31 = var_r30->unk_3C, var_r29 = 0; var_r29 < var_r30->unk_26; var_r29++, var_r31++) {
        var_r31->unk_38 = arg2;
    }
}

void fn_1_13EC8(s16 arg0, s16 arg1, float arg8)
{
    M428DllPlayerUnkStruct2 *var_r31;
    M428DllPlayerUnk120Struct2 *var_r30;
    s32 var_r29;
    ModelData *var_r28;

    var_r28 = &Hu3DData[arg0];
    var_r30 = var_r28->unk_120;
    if (arg1 != -1) {
        var_r31 = &var_r30->unk_3C[arg1];
        var_r31->unk_30 = arg8;
        return;
    }
    for (var_r31 = var_r30->unk_3C, var_r29 = 0; var_r29 < var_r30->unk_26; var_r29++, var_r31++) {
        var_r31->unk_30 = arg8;
    }
}

s32 fn_1_13F54(s16 arg0, char *arg1, Mtx arg2, s32 arg3)
{
    Mtx sp44;
    Mtx sp14;
    ModelData *var_r31;
    HsfData *var_r30;

    var_r31 = &Hu3DData[arg0];
    var_r30 = var_r31->hsfData;
    lbl_1_bss_130 = 0;
    if (var_r31->unk_08 != -1) {
        lbl_1_bss_134 = 1;
    }
    else {
        lbl_1_bss_134 = 0;
    }
    mtxRot(sp14, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
    MTXScale(sp44, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
    MTXConcat(sp14, sp44, sp44);
    mtxTransCat(sp44, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
    MTXConcat(sp44, var_r31->unk_F0, sp44);
    if (arg3 != 0) {
        MTXConcat(arg2, sp44, sp44);
    }
    fn_1_14088(var_r30->root, sp44, arg1, arg2);
    return lbl_1_bss_130;
}

void fn_1_14088(HsfObject *arg0, Mtx arg1, char *arg2, Mtx arg3)
{
    Mtx spF8;
    Mtx spC8;
    Mtx sp98;
    Mtx sp68;
    Mtx sp38;
    Mtx sp8;
    HsfTransform *var_r31;
    HsfTransform *var_r30;
    HsfTransform *var_r29;
    HsfObject *var_r28;
    HsfObject *var_r27;
    u32 var_r25;
    u32 var_r24;
    u32 var_r23;

    if (lbl_1_bss_130 == 0) {
        if (lbl_1_bss_134 != 0) {
            var_r31 = &arg0->data.curr;
        }
        else {
            var_r31 = &arg0->data.base;
        }
        if ((var_r31->scale.x <= 0.0f) && (var_r31->scale.y <= 0.0f) && (var_r31->scale.z <= 0.0f)) {
            MTXCopy(arg1, spF8);
            OSReport("OBJ MTX CHECK ERROR %s \n", arg0->name);
        }
        else {
            mtxRot(spC8, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
            MTXScale(spF8, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
            MTXConcat(spC8, spF8, spF8);
            mtxTransCat(spF8, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
            MTXConcat(arg1, spF8, spF8);
        }
        if (lbl_1_bss_138 != 0) {
            OSReport("%s \n", arg0->name);
        }
        if (strcmp(arg2, arg0->name) == 0) {
            MTXCopy(spF8, arg3);
            lbl_1_bss_130 = 1;
        }
        for (var_r25 = 0; var_r25 < arg0->data.childrenCount; var_r25++) {
            var_r28 = arg0->data.children[var_r25];
            if (lbl_1_bss_130 == 0) {
                if (lbl_1_bss_134 != 0) {
                    var_r30 = &var_r28->data.curr;
                }
                else {
                    var_r30 = &var_r28->data.base;
                }
                if ((var_r30->scale.x <= 0.0f) && (var_r30->scale.y <= 0.0f) && (var_r30->scale.z <= 0.0f)) {
                    MTXCopy(spF8, sp68);
                    OSReport("OBJ MTX CHECK ERROR %s \n", var_r28->name);
                }
                else {
                    mtxRot(&sp98[0], var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
                    MTXScale(sp68, var_r30->scale.x, var_r30->scale.y, var_r30->scale.z);
                    MTXConcat(&sp98[0], sp68, sp68);
                    mtxTransCat(sp68, var_r30->pos.x, var_r30->pos.y, var_r30->pos.z);
                    MTXConcat(spF8, sp68, sp68);
                }
                if (lbl_1_bss_138 != 0) {
                    OSReport("%s \n", var_r28->name);
                }
                if (strcmp(arg2, var_r28->name) == 0) {
                    MTXCopy(sp68, arg3);
                    lbl_1_bss_130 = 1;
                }
                for (var_r24 = 0; var_r24 < var_r28->data.childrenCount; var_r24++) {
                    var_r27 = var_r28->data.children[var_r24];
                    if (lbl_1_bss_130 == 0) {
                        if (lbl_1_bss_134 != 0) {
                            var_r29 = &var_r27->data.curr;
                        }
                        else {
                            var_r29 = &var_r27->data.base;
                        }
                        if ((var_r29->scale.x <= 0.0f) && (var_r29->scale.y <= 0.0f) && (var_r29->scale.z <= 0.0f)) {
                            MTXCopy(sp68, sp8);
                            OSReport("OBJ MTX CHECK ERROR %s \n", var_r27->name);
                        }
                        else {
                            mtxRot(sp38, var_r29->rot.x, var_r29->rot.y, var_r29->rot.z);
                            MTXScale(sp8, var_r29->scale.x, var_r29->scale.y, var_r29->scale.z);
                            MTXConcat(sp38, sp8, sp8);
                            mtxTransCat(sp8, var_r29->pos.x, var_r29->pos.y, var_r29->pos.z);
                            MTXConcat(sp68, sp8, sp8);
                        }
                        if (lbl_1_bss_138 != 0) {
                            OSReport("%s \n", var_r27->name);
                        }
                        if (strcmp(arg2, var_r27->name) == 0) {
                            MTXCopy(sp8, arg3);
                            lbl_1_bss_130 = 1;
                        }
                        for (var_r23 = 0; var_r23 < var_r27->data.childrenCount; var_r23++) {
                            fn_1_14088(var_r27->data.children[var_r23], sp8, arg2, arg3);
                        }
                    }
                }
            }
        }
    }
}

void fn_1_14560(s16 arg0)
{
    CameraData *var_r31 = &Hu3DCamera[arg0];
    C_MTXLookAt(lbl_1_bss_23C[arg0], &var_r31->pos, &var_r31->up, &var_r31->target);
    GXGetProjectionv(&lbl_1_bss_1BC[arg0].unk_00);
    GXGetViewportv(&lbl_1_bss_13C[arg0].unk_00);
}

void fn_1_145F8(s16 var_r29, Vec *var_r31, float *var_r30)
{
    GXProject(var_r31->x, var_r31->y, var_r31->z, lbl_1_bss_23C[var_r29], &lbl_1_bss_1BC[var_r29].unk_00, &lbl_1_bss_13C[var_r29].unk_00, var_r30,
        &var_r30[1], &var_r30[2]);
}
