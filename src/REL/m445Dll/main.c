#include "REL/executor.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/mapspace.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[3];
    /* 0x08 */ char unk08[4];
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ char unk12[2];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20[2];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ float unk50[2];
    /* 0x58 */ float unk58[2];
} UnkM445Struct_00; // Size 0x60

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08[16];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
} UnkM445Struct_01; // Size 0x38

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08[8];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ float unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ float unk50;
    /* 0x54 */ float unk54;
    /* 0x58 */ float unk58;
    /* 0x5C */ float unk5C;
    /* 0x60 */ float unk60;
    /* 0x64 */ char unk64[0xC];
    /* 0x70 */ Vec unk70;
    /* 0x7C */ s8 unk7C;
    /* 0x7D */ s8 unk7D;
    /* 0x7E */ s8 unk7E;
    /* 0x7F */ s8 unk7F;
    /* 0x80 */ u16 unk80;
    /* 0x82 */ u16 unk82;
    /* 0x84 */ float unk84;
    /* 0x88 */ float unk88;
    /* 0x8C */ char unk8C[4];
    /* 0x90 */ s32 unk90;
    /* 0x94 */ char unk94[4];
    /* 0x98 */ s32 unk98;
} UnkM445Struct_02; // Size 0x9C

typedef struct {
    /* 0x00 */ char unk00[0x18];
    /* 0x18 */ float unk18;
    /* 0x1C */ char unk1C[4];
    /* 0x20 */ float unk20;
} UnkM445Struct_03; // Size unknown

typedef struct {
    /* 0x00 */ UnkM445Struct_03 *unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
} UnkM445Struct_04; // Size unknown

void ObjectSetup(void);
void fn_1_4B8(float arg0, float arg1, s32 arg2);
void fn_1_50C(omObjData *arg0);
void fn_1_510(omObjData *arg0);
BOOL fn_1_520(s32 arg0);
void fn_1_550(void);
float fn_1_1858(float arg0);
UnkM445Struct_01 *fn_1_18D8(void);
void fn_1_1934(void);
void fn_1_1968(void);
s32 fn_1_1AD0(s32 arg0);
void fn_1_1B0C(void);
void fn_1_1C64(void);
s8 fn_1_2BF4(s32 arg0, s32 arg1);
void fn_1_2CAC(Vec *arg0, float arg1, float arg2);
s8 fn_1_2E68(s32 arg0, s32 arg1);
u8 fn_1_2F38(s32 arg0, s32 arg1);
u16 fn_1_3010(s32 arg0);
u16 fn_1_3094(s32 arg0);
s32 fn_1_3114(UnkM445Struct_02 *arg0, float arg1, float arg2, float arg3);
s32 fn_1_3334(UnkM445Struct_02 *arg0, s32 *arg1);
void fn_1_3548(UnkM445Struct_02 *arg0);
float fn_1_42A0(float arg0, float arg1, float arg2);
BOOL fn_1_43A4(UnkM445Struct_02 *arg0, float arg1, float arg2);
void fn_1_45D0(UnkM445Struct_02 *arg0);
void fn_1_557C(void);
void fn_1_55F0(void);
void fn_1_5664(UnkM445Struct_02 *arg0, s32 arg1);
void fn_1_5700(UnkM445Struct_02 *arg0);
void fn_1_6268(void);
void fn_1_7FC0(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_8320(void);
void fn_1_8938(void);
void fn_1_89B8(void);
void fn_1_8A18(void);

s16 lbl_1_bss_6E6;
char lbl_1_bss_6E4_pad[2]; // Unused.
s16 lbl_1_bss_6E2;
s16 lbl_1_bss_6E0;
s32 lbl_1_bss_6DC;
s32 lbl_1_bss_6D8;
s32 lbl_1_bss_6CC[3];
s32 lbl_1_bss_6C8;
s32 lbl_1_bss_6C4;
char lbl_1_bss_6C0_pad[4]; // Unused.
UnkM445Struct_02 lbl_1_bss_588[2];
UnkM445Struct_00 lbl_1_bss_288[8];
UnkM445Struct_01 lbl_1_bss_58[10];
Process *lbl_1_bss_54;
char lbl_1_bss_30_pad[0x24]; // Unused.
omObjData *lbl_1_bss_2C;
Vec lbl_1_bss_20;
Vec lbl_1_bss_14;
Vec lbl_1_bss_8;
s32 lbl_1_bss_4;
float lbl_1_bss_0;

s32 lbl_1_data_0[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

// Unused.
s32 lbl_1_data_20[] = { DATADIR_MARIOMOT, DATADIR_LUIGIMOT, DATADIR_PEACHMOT, DATADIR_YOSHIMOT, DATADIR_WARIOMOT, DATADIR_DONKEYMOT, DATADIR_DAISYMOT,
    DATADIR_WALUIGIMOT };

s32 lbl_1_data_40[]
    = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MARIOMOT, 2), DATA_MAKE_NUM(DATADIR_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_M445, 0),
          DATA_MAKE_NUM(DATADIR_M445, 8), DATA_MAKE_NUM(DATADIR_M445, 16), DATA_MAKE_NUM(DATADIR_MARIOMOT, 75), DATA_MAKE_NUM(DATADIR_MARIOMOT, 24) };

Vec lbl_1_data_60[] = { { -100.0f, 75.0f, 60.0f }, { 100.0f, 75.0f, -60.0f } };

Vec lbl_1_data_78[] = { { 0.0f, 0.0f, -79.5f }, { 180.0f, 0.0f, -100.5f } };

float lbl_1_data_90[][2] = { { 471.0f, 280.0f }, { -461.5f, 299.5f }, { 271.7f, -482.6f }, { -373.1f, -457.1f }, { 462.8f, -128.5f },
    { 0.0f, -495.4f }, { -40.8f, 632.3f }, { -477.7f, -110.0f } };

float lbl_1_data_D0[][2] = { { 467.0f, 393.0f }, { -461.5f, 395.5f }, { 367.7f, -492.1f }, { -268.9f, -467.0f }, { 462.8f, -128.5f },
    { 0.0f, -495.4f }, { -40.8f, 632.3f }, { -477.7f, -110.0f } };

s32 lbl_1_data_110[][2] = { { 360, 306 }, { -360, 341 }, { 326, -360 }, { -326, -360 }, { 321, -122 }, { 0, -332 }, { -50, 500 }, { -334, -110 } };

char *lbl_1_data_220[][2] = { { "tansu_w_itemhook1", "tansu_w_itemhook2" }, { "sidebord_itemhook1", "sidebord_itemhook2" },
    { "pinkshelf_itemhook1", "pinkshelf_itemhook2" }, { "green_itemhook1", "green_itemhook2" }, { "bookshelf_itemhook", "bookshelf_itemhook" },
    { "clock_itemhook", "clock_itemhook" }, { "book_itemhook", "book_itemhook" }, { "tv_itemhook", "tv_itemhook" } };

s32 lbl_1_data_260[] = { 2, 2, 2, 2, 1, 1, 1, 1 };

void ObjectSetup(void)
{
    lbl_1_bss_54 = omInitObjMan(50, 0x2000);
    omGameSysInit(lbl_1_bss_54);
    HuWinInit(1);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 40.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    lbl_1_bss_2C = omAddObjEx(lbl_1_bss_54, 32730, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_2C->work[0] = 1;
    CRotM[0].x = -12.5f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CenterM[0].x = 0.0f;
    CenterM[0].y = 345.0f;
    CenterM[0].z = -250.0f;
    CZoomM[0] = 520.0f;
    Hu3DLighInit();
    lbl_1_bss_6E6 = Hu3DGLightCreate(10000.0f, 0.0f, 10000.0f, -1.0f, 0.0f, -1.0f, 0xFF, 0xFF, 0xFF);
    Hu3DGLightPosAimSet(lbl_1_bss_6E6, 0.0f, 4330.13f, 2500.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(lbl_1_bss_6E6);
    lbl_1_bss_20.x = -200.0f;
    lbl_1_bss_20.y = 4000.0f;
    lbl_1_bss_20.z = 0.0f;
    lbl_1_bss_14.x = lbl_1_bss_14.z = 0.0f;
    lbl_1_bss_14.y = 1.0f;
    lbl_1_bss_8.x = 0.0f;
    lbl_1_bss_8.y = 0.0f;
    lbl_1_bss_8.z = 0.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowPosSet(&lbl_1_bss_20, &lbl_1_bss_14, &lbl_1_bss_8);
    Hu3DBGColorSet(0, 0, 0);
    fn_1_550();
    HuPrcChildCreate(fn_1_8A18, 0x1000, 0x2000, 0, HuPrcCurrentGet());
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
}

void fn_1_4B8(float arg0, float arg1, s32 arg2)
{
    Vec sp14;

    sp14.x = arg0;
    sp14.y = 0.0f;
    sp14.z = arg1;
    HuAudFXEmiterPlay(arg2, &sp14);
}

void fn_1_50C(omObjData *arg0) { }

void fn_1_510(omObjData *arg0)
{
    arg0->func = fn_1_50C;
}

BOOL fn_1_520(s32 arg0)
{
    return (GWPlayerCfg[arg0].character == 9);
}

void fn_1_550(void)
{
    float var_f31;
    float var_f30;
    float var_f29;
    UnkM445Struct_00 *temp_r26;
    UnkM445Struct_01 *temp_r25;
    UnkM445Struct_02 *temp_r31;
    omObjData *temp_r24;
    Process *var_r22;
    AnimData *var_r20;
    AnimData *sp38[4];
    void *var_r29;
    s16 var_r30;
    s32 var_r23;
    s32 var_r21;
    Vec sp2C;
    Vec sp20;
    s32 i;
    s32 j;

    nMap = 0;
    HuAudSndGrpSet(0x47);
    sp2C.x = 0.0f;
    sp2C.y = 998.0f;
    sp2C.z = 1551.0f;
    sp20.x = 0.0f;
    sp20.y = -0.5f;
    sp20.z = -1.0f;
    HuAudFXListnerSetEX(&sp2C, &sp20, 10000.0f, 34.0f*(1.0f/REFRESH_RATE), 0.0f, 300.0f, 300.0f);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 24), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    Hu3DModelLayerSet(var_r30, 0);
    Hu3DModelShadowMapSet(var_r30);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 25), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    temp_r24 = omAddObjEx(lbl_1_bss_54, 0x100, 1, 0, -1, fn_1_510);
    MapObject[nMap++] = temp_r24;
    temp_r24->model[0] = var_r30;
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 26), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    Hu3DModelLayerSet(var_r30, 0);
    Hu3DModelShadowSet(var_r30);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 27), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    Hu3DModelLayerSet(var_r30, 0);
    Hu3DModelShadowMapSet(var_r30);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 28), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    temp_r24 = omAddObjEx(lbl_1_bss_54, 0x100, 1, 0, -1, fn_1_510);
    MapObject[nMap++] = temp_r24;
    temp_r24->model[0] = var_r30;
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 100), MEMORY_DEFAULT_NUM, HEAP_DATA);
    lbl_1_bss_6E0 = Hu3DModelCreate(var_r29);
    Hu3DModelAttrSet(lbl_1_bss_6E0, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 8; i++) {
        temp_r26 = &lbl_1_bss_288[i];
        temp_r26->unk14 = i;
        temp_r26->unk30 = 0;
        var_r23 = DATA_MAKE_NUM(DATADIR_M445, 38 + i * 5);
        var_r29 = HuDataSelHeapReadNum(var_r23, MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r29);
        temp_r26->unk00 = var_r30;
        for (j = 0, var_r23++; j < 3; j++) {
            var_r29 = HuDataSelHeapReadNum(var_r23++, MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r26->unk02[j] = Hu3DJointMotion(var_r30, var_r29);
        }
        Hu3DModelShadowSet(var_r30);
        Hu3DMotionSet(var_r30, temp_r26->unk02[0]);
        Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
        temp_r26->unk48 = lbl_1_data_110[i][0];
        temp_r26->unk4C = lbl_1_data_110[i][1];
        temp_r26->unk50[0] = lbl_1_data_90[i][0];
        temp_r26->unk58[0] = lbl_1_data_90[i][1];
        temp_r26->unk50[1] = lbl_1_data_D0[i][0];
        temp_r26->unk58[1] = lbl_1_data_D0[i][1];
        if (i == 5) {
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 81), MEMORY_DEFAULT_NUM, HEAP_DATA);
            lbl_1_bss_6E2 = Hu3DJointMotion(var_r30, var_r29);
            Hu3DMotionSet(var_r30, lbl_1_bss_6E2);
            Hu3DMotionTimeSet(var_r30, 61.0f);
            Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_PAUSE);
        }
        if (i == 6) {
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 78), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r26->unk0E = Hu3DJointMotion(var_r30, var_r29);
        }
        if (i == 7) {
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 79), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r26->unk0E = Hu3DJointMotion(var_r30, var_r29);
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 80), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r26->unk10 = Hu3DJointMotion(var_r30, var_r29);
        }
        temp_r26->unk18 = nMap;
        var_r29 = HuDataSelHeapReadNum(var_r23, MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r29);
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
        temp_r24 = MapObject[nMap++] = omAddObjEx(lbl_1_bss_54, 0x100, 1, 0, -1, fn_1_510);
        temp_r24->model[0] = var_r30;
        temp_r24->trans.x = temp_r26->unk48;
        temp_r24->trans.y = 0.0f;
        temp_r24->trans.z = temp_r26->unk4C;
        var_r22 = HuPrcChildCreate(fn_1_1C64, 0x2000, 0x2000, 0, HuPrcCurrentGet());
        var_r22->user_data = temp_r26;
    }
    HuPrcChildCreate(fn_1_1B0C, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    for (i = 0; i < 10; i++) {
        temp_r25 = &lbl_1_bss_58[i];
        temp_r25->unk2C = i;
        temp_r25->unk30 = -1;
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 82), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r29);
        temp_r25->unk00 = var_r30;
        for (j = 0; j < 4; j++) {
            var_r29 = HuDataSelHeapReadNum(j + DATA_MAKE_NUM(DATADIR_M445, 83), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r25->unk08[j] = Hu3DJointMotion(var_r30, var_r29);
        }
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 82), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r29);
        temp_r25->unk04 = var_r30;
        for (j = 0; j < 4; j++) {
            var_r29 = HuDataSelHeapReadNum(j + DATA_MAKE_NUM(DATADIR_M445, 87), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r25->unk08[j + 4] = Hu3DJointMotion(var_r30, var_r29);
        }
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 91), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r29);
        temp_r25->unk02 = var_r30;
        for (j = 0; j < 4; j++) {
            var_r29 = HuDataSelHeapReadNum(j + DATA_MAKE_NUM(DATADIR_M445, 92), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r25->unk08[j + 8] = Hu3DJointMotion(var_r30, var_r29);
        }
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 91), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r29);
        temp_r25->unk06 = var_r30;
        for (j = 0; j < 4; j++) {
            var_r29 = HuDataSelHeapReadNum(j + DATA_MAKE_NUM(DATADIR_M445, 96), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r25->unk08[j + 12] = Hu3DJointMotion(var_r30, var_r29);
        }
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 2; i++) {
        temp_r31 = &lbl_1_bss_588[i];
        temp_r31->unk18 = i;
        temp_r31->unk1C = i;
        temp_r31->unk20 = GWPlayerCfg[i].pad_idx;
        if (fn_1_520(temp_r31->unk18) == FALSE) {
            temp_r31->unk00 = CharModelCreate(lbl_1_data_0[GWPlayerCfg[i].character], 2);
        }
        else {
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 29), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r31->unk00 = Hu3DModelCreate(var_r29);
        }
        Hu3DModelLayerSet(temp_r31->unk00, 0);
        CharModelStepTypeSet(lbl_1_data_0[GWPlayerCfg[i].character], 1);
        CharModelLayerSetAll(3);
        temp_r31->unk48 = temp_r31->unk50 = 0.0f;
        if (i != 0) {
            var_f31 = temp_r31->unk4C = fn_1_1858(-90.0f);
        }
        else {
            temp_r31->unk4C = var_f31 = 90.0f;
        }
        temp_r31->unk60 = temp_r31->unk4C;
        if (i != 0) {
            var_f30 = temp_r31->unk34 = 160.0f;
        }
        else {
            var_f30 = temp_r31->unk34 = -160.0f;
        }
        temp_r31->unk38 = 0.0f;
        if (i != 0) {
            var_f29 = temp_r31->unk3C = -45.0f;
        }
        else {
            var_f29 = temp_r31->unk3C = 45.0f;
        }
        temp_r31->unk54 = 50.0f;
        temp_r31->unk5C = temp_r31->unk58 = 0.0f;
        HuSetVecF(&temp_r31->unk70, 0.0, 0.0, 0.0);
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk34, temp_r31->unk38, temp_r31->unk3C);
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        Hu3DModelShadowSet(temp_r31->unk00);
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 37), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r29);
        temp_r31->unk06 = var_r30;
        Hu3DModelLayerSet(var_r30, 0);
        Hu3DModelShadowSet(var_r30);
        Hu3DModelPosSet(var_r30, lbl_1_data_60[i].x, lbl_1_data_60[i].y, lbl_1_data_60[i].z);
        Hu3DModelRotSet(var_r30, lbl_1_data_78[i].x, lbl_1_data_78[i].y, lbl_1_data_78[i].z);
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 101), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r29);
        temp_r31->unk02 = var_r30;
        Hu3DMotionSpeedSet(var_r30, 1.4f);
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
        if (fn_1_520(temp_r31->unk18) == FALSE) {
            for (j = 0; j < 8; j++) {
                var_r21 = lbl_1_data_40[j];
                if ((var_r21 & ~0xFFFF) == DATADIR_M445) {
                    var_r21 += GWPlayerCfg[i].character;
                }
                temp_r31->unk08[j] = CharModelMotionCreate(lbl_1_data_0[GWPlayerCfg[i].character], var_r21);
            }
            CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[i].character], temp_r31->unk08[0]);
        }
        else {
            for (j = 0; j < 7; j++) {
                var_r29 = HuDataSelHeapReadNum(j + DATA_MAKE_NUM(DATADIR_M445, 30), MEMORY_DEFAULT_NUM, HEAP_DATA);
                temp_r31->unk08[j] = Hu3DJointMotion(temp_r31->unk00, var_r29);
            }
            Hu3DMotionSet(temp_r31->unk00, temp_r31->unk08[0]);
            CharModelEffectNpcInit(temp_r31->unk00, temp_r31->unk08[1], 0, 9);
            CharModelEffectNpcInit(temp_r31->unk00, temp_r31->unk08[2], 1, 9);
        }
        Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_LOOP);
        if (i == 0) {
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 22), MEMORY_DEFAULT_NUM, HEAP_DATA);
            sp38[0] = HuSprAnimRead(var_r29);
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 23), MEMORY_DEFAULT_NUM, HEAP_DATA);
            sp38[1] = HuSprAnimRead(var_r29);
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 51), MEMORY_DEFAULT_NUM, HEAP_DATA);
            sp38[3] = HuSprAnimRead(var_r29);
        }
        if (fn_1_520(temp_r31->unk18) == FALSE) {
            var_r29 = HuDataSelHeapReadNum(GWPlayerCfg[i].character + DATADIR_MGCONST, MEMORY_DEFAULT_NUM, HEAP_DATA);
        }
        else {
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M445, 102), MEMORY_DEFAULT_NUM, HEAP_DATA);
        }
        sp38[2] = HuSprAnimRead(var_r29);
        temp_r31->unk04 = HuSprGrpCreate(5);
        var_r30 = HuSprCreate(sp38[0], 0x1000, 0);
        HuSprGrpMemberSet(temp_r31->unk04, 0, var_r30);
        HuSprPosSet(temp_r31->unk04, 0, 0.0f, 0.0f);
        var_r30 = HuSprCreate(sp38[1], 0x1001, 0);
        HuSprGrpMemberSet(temp_r31->unk04, 1, var_r30);
        HuSprPosSet(temp_r31->unk04, 1, 0.0f, 0.0f);
        HuSprTPLvlSet(temp_r31->unk04, 1, 0.5f);
        HuSprColorSet(temp_r31->unk04, 1, 0, 0, 0);
        var_r30 = HuSprCreate(sp38[2], 0x1000, 0);
        HuSprGrpMemberSet(temp_r31->unk04, 2, var_r30);
        HuSprPosSet(temp_r31->unk04, 2, -36.0f, -2.0f);
        var_r30 = HuSprCreate(sp38[3], 0x1000, 0);
        HuSprGrpMemberSet(temp_r31->unk04, 3, var_r30);
        HuSprPosSet(temp_r31->unk04, 3, 16.0f, 2.0f);
        var_r30 = HuSprCreate(sp38[3], 0x1000, 0);
        HuSprGrpMemberSet(temp_r31->unk04, 4, var_r30);
        HuSprPosSet(temp_r31->unk04, 4, -4.0f, 2.0f);
        HuSprAttrSet(temp_r31->unk04, 4, 4);
        HuSprGrpPosSet(temp_r31->unk04, i * 438 + 73, 61.0f);
        temp_r31->unk30 = 0;
        fn_1_5664(temp_r31, temp_r31->unk30);
        fn_1_55F0();
        CharModelMotionDataClose(lbl_1_data_0[GWPlayerCfg[i].character]);
        var_r22 = HuPrcChildCreate(fn_1_6268, 0x2000, 0x3000, 0, HuPrcCurrentGet());
        var_r22->user_data = temp_r31;
    }
    var_r20 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 3), MEMORY_DEFAULT_NUM));
    var_r30 = Hu3DParticleCreate(var_r20, 3);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r30, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r30, 4);
    Hu3DParticleColSet(var_r30, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r30, 0.0f);
    Hu3DParticleHookSet(var_r30, fn_1_7FC0);
    HuDataDirClose(DATADIR_EFFECT);
    lbl_1_bss_6C8 = 0;
    lbl_1_bss_6CC[0] = frandmod(25);
    lbl_1_bss_6CC[1] = frandmod(25) + 30;
    lbl_1_bss_6CC[2] = 1000;
    HuPrcChildCreate(fn_1_89B8, 0x1000, 0x1000, 0, HuPrcCurrentGet());
}

float fn_1_1858(float arg0)
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

UnkM445Struct_01 *fn_1_18D8(void)
{
    UnkM445Struct_01 *var_r30;
    s32 i;

    for (i = 0; i < 10; i++) {
        var_r30 = &lbl_1_bss_58[i];
        if (var_r30->unk30 == -1) {
            break;
        }
    }
    if (i >= 10) {
        var_r30 = NULL;
    }
    return var_r30;
}

void fn_1_1934(void)
{
    UnkM445Struct_04 *var_r31;

    var_r31 = HuPrcCurrentGet()->user_data;
    HuMemDirectFree(var_r31);
}

void fn_1_1968(void)
{
    float var_f31;
    float var_f30;
    UnkM445Struct_04 *temp_r31;
    s32 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    HuPrcDestructorSet(fn_1_1934);
    switch (temp_r31->unk04) {
        case 0:
            var_f31 = -140.0f / temp_r31->unk0C;
            var_f30 = 0.0f / temp_r31->unk0C;
            break;
        default:
            var_f31 = 0.0f;
            var_f30 = 0.0f;
            break;
    }
    for (i = temp_r31->unk0C; i != 0; i--) {
        temp_r31->unk00->unk18 += var_f31;
        temp_r31->unk00->unk20 += var_f30;
        HuPrcVSleep();
    }
    while (temp_r31->unk08 == 0) {
        HuPrcVSleep();
    }
    for (i = temp_r31->unk0C; i != 0; i--) {
        temp_r31->unk00->unk18 -= var_f31;
        temp_r31->unk00->unk20 -= var_f30;
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 fn_1_1AD0(s32 arg0)
{
    s32 var_r31;

    if (arg0 < 20) {
        var_r31 = 3;
    }
    else if (arg0 < 40) {
        var_r31 = 4;
    }
    else {
        var_r31 = 5;
    }
    return var_r31;
}

void fn_1_1B0C(void)
{
    UnkM445Struct_00 *temp_r30;
    s32 spC;
    s32 sp8;
    s32 var_r29;
    s32 var_r28;
    s32 i;

    spC = -1;
    sp8 = 0;
    while (lbl_1_bss_6DC < 3) {
        HuPrcVSleep();
    }
    while (TRUE) {
        if (lbl_1_bss_6DC >= 4) {
            break;
        }
        for (i = 0, var_r28 = 0; i < 8; i++) {
            temp_r30 = &lbl_1_bss_288[i];
            if (temp_r30->unk34 != 0) {
                var_r28++;
            }
        }
        if (var_r28 < fn_1_1AD0(lbl_1_bss_6D8 / REFRESH_RATE)) {
            var_r29 = frandmod(8) + 1;
            i = 0;
            while (TRUE) {
                temp_r30 = &lbl_1_bss_288[i];
                if (temp_r30->unk34 == 0) {
                    var_r29--;
                }
                if (var_r29 == 0) {
                    break;
                }
                i++;
                if (i >= 8) {
                    i = 0;
                }
            }
            temp_r30->unk34 = 1;
            HuPrcSleep(60);
        }
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_1C64(void)
{
    UnkM445Struct_00 *temp_r31;
    UnkM445Struct_01 *var_r25;
    UnkM445Struct_01 *var_r29;
    s32 var_r23;
    s32 var_r26;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk1C = 0;
    temp_r31->unk34 = 0;
    while (TRUE) {
        while (temp_r31->unk34 == 0) {
            HuPrcVSleep();
        }
        temp_r31->unk20[0] = temp_r31->unk20[1] = 0;
        temp_r31->unk0C = 0;
        if (temp_r31->unk14 == 5 || temp_r31->unk14 == 7) {
            temp_r31->unk0C = 4;
        }
        var_r25 = fn_1_18D8();
        var_r25->unk30 = temp_r31->unk14;
        var_r25->unk34 = 0;
        temp_r31->unk3C = var_r25->unk2C;
        temp_r31->unk40 = -1;
        if (lbl_1_bss_6CC[lbl_1_bss_6C8] < lbl_1_bss_6D8 / REFRESH_RATE) {
            temp_r31->unk38 = 1;
            if (lbl_1_data_260[temp_r31->unk14] == 1) {
                lbl_1_bss_6C8++;
            }
            if (temp_r31->unk14 == 5 || temp_r31->unk14 == 7) {
                var_r25->unk28 = var_r25->unk04;
            }
            else {
                var_r25->unk28 = var_r25->unk00;
            }
        }
        else {
            temp_r31->unk38 = 0;
            if (temp_r31->unk14 == 5 || temp_r31->unk14 == 7) {
                var_r25->unk28 = var_r25->unk06;
            }
            else {
                var_r25->unk28 = var_r25->unk02;
            }
            temp_r31->unk0C += 8;
        }
        Hu3DModelAttrReset(var_r25->unk28, HU3D_ATTR_DISPOFF);
        Hu3DModelHookSet(temp_r31->unk00, lbl_1_data_220[temp_r31->unk14][0], var_r25->unk28);
        Hu3DMotionSet(var_r25->unk28, var_r25->unk08[temp_r31->unk0C]);
        if (lbl_1_data_260[temp_r31->unk14] > 1) {
            var_r29 = fn_1_18D8();
            var_r29->unk30 = temp_r31->unk14;
            var_r29->unk34 = 0;
            temp_r31->unk40 = var_r29->unk2C;
            if (lbl_1_bss_6CC[lbl_1_bss_6C8] < lbl_1_bss_6D8 / REFRESH_RATE) {
                lbl_1_bss_6C8++;
                if (temp_r31->unk14 == 5 || temp_r31->unk14 == 7) {
                    var_r29->unk28 = var_r29->unk04;
                }
                else {
                    var_r29->unk28 = var_r29->unk00;
                }
            }
            else {
                if (temp_r31->unk14 == 5 || temp_r31->unk14 == 7) {
                    var_r29->unk28 = var_r29->unk06;
                }
                else {
                    var_r29->unk28 = var_r29->unk02;
                }
            }
            Hu3DModelAttrReset(var_r29->unk28, HU3D_ATTR_DISPOFF);
            Hu3DModelHookSet(temp_r31->unk00, lbl_1_data_220[temp_r31->unk14][1], var_r29->unk28);
            Hu3DMotionSet(var_r29->unk28, var_r29->unk08[temp_r31->unk0C]);
        }
        temp_r31->unk1C = 1;
        temp_r31->unk44 = 0;
        switch (temp_r31->unk14) {
            case 0:
            case 1:
            case 3:
                fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x751);
                break;
            case 6:
                fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x753);
                break;
            default:
                fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x752);
                break;
        }
        if (temp_r31->unk14 == 7 && temp_r31->unk38 == 0) {
            Hu3DMotionSet(temp_r31->unk00, temp_r31->unk0E);
        }
        else {
            Hu3DMotionSet(temp_r31->unk00, temp_r31->unk02[1]);
        }
        Hu3DModelAttrReset(temp_r31->unk00, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV);
        while (!Hu3DMotionEndCheck(temp_r31->unk00)) {
            temp_r31->unk44++;
            HuPrcVSleep();
        }
        if (lbl_1_bss_6DC >= 4) {
            break;
        }
        if (temp_r31->unk14 == 7 && temp_r31->unk38 == 0) {
            Hu3DMotionSet(temp_r31->unk00, temp_r31->unk10);
        }
        else if (temp_r31->unk14 == 6 && temp_r31->unk38 == 0) {
            Hu3DMotionSet(temp_r31->unk00, temp_r31->unk0E);
        }
        else {
            Hu3DMotionSet(temp_r31->unk00, temp_r31->unk02[2]);
        }
        var_r23 = REFRESH_RATE*2.5f;
        Hu3DMotionSet(var_r25->unk28, var_r25->unk08[temp_r31->unk0C + 1]);
        Hu3DModelAttrSet(var_r25->unk28, HU3D_MOTATTR_PAUSE);
        if (temp_r31->unk14 == 6) {
            HuPrcSleep(12);
            Hu3DModelAttrReset(var_r25->unk28, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
            if (temp_r31->unk38 != 0) {
                fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x758);
            }
            else {
                fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x757);
            }
        }
        if (temp_r31->unk14 == 7) {
            HuPrcSleep(11);
            Hu3DModelAttrReset(var_r25->unk28, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
            fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x754);
            Hu3DModelAttrReset(lbl_1_bss_6E0, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(lbl_1_bss_6E0, 0.0f);
        }
        while (!Hu3DMotionEndCheck(temp_r31->unk00)) {
            temp_r31->unk44++;
            HuPrcVSleep();
        }
        if (temp_r31->unk14 != 6) {
            if (temp_r31->unk38 != 0) {
                fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x758);
            }
            else {
                fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x757);
            }
            Hu3DModelAttrReset(var_r25->unk28, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
            if (lbl_1_data_260[temp_r31->unk14] > 1) {
                Hu3DMotionSet(var_r29->unk28, var_r29->unk08[temp_r31->unk0C + 1]);
                Hu3DModelAttrReset(var_r29->unk28, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
            }
        }
        while (!Hu3DMotionEndCheck(var_r25->unk28)) {
            HuPrcVSleep();
        }
        var_r25->unk34 = 1;
        Hu3DMotionSet(var_r25->unk28, var_r25->unk08[temp_r31->unk0C + 2]);
        Hu3DModelAttrSet(var_r25->unk28, HU3D_MOTATTR_LOOP);
        if (lbl_1_data_260[temp_r31->unk14] > 1) {
            var_r29->unk34 = 1;
            Hu3DMotionSet(var_r29->unk28, var_r29->unk08[temp_r31->unk0C + 2]);
            Hu3DModelAttrSet(var_r29->unk28, HU3D_MOTATTR_LOOP);
        }
        temp_r31->unk1C = 2;
        var_r26 = var_r23;
        while (TRUE) {
            if (temp_r31->unk20[0] == 1) {
                temp_r31->unk20[0] = 2;
                Hu3DMotionSet(var_r25->unk28, var_r25->unk08[temp_r31->unk0C + 3]);
                Hu3DModelAttrReset(var_r25->unk28, HU3D_MOTATTR_LOOP);
                if (temp_r31->unk38 != 0) {
                    if (temp_r31->unk28 != 0) {
                        fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x75C);
                    }
                    else {
                        fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x75A);
                    }
                }
                else {
                    if (temp_r31->unk28 != 0) {
                        fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x75B);
                    }
                    else {
                        fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x759);
                    }
                }
            }
            if (temp_r31->unk20[1] == 1) {
                temp_r31->unk20[1] = 2;
                Hu3DMotionSet(var_r29->unk28, var_r29->unk08[temp_r31->unk0C + 3]);
                Hu3DModelAttrReset(var_r29->unk28, HU3D_MOTATTR_LOOP);
                if (temp_r31->unk38 != 0) {
                    if (temp_r31->unk2C != 0) {
                        fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x75C);
                    }
                    else {
                        fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x75A);
                    }
                }
                else {
                    if (temp_r31->unk2C != 0) {
                        fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x75B);
                    }
                    else {
                        fn_1_4B8(temp_r31->unk48, temp_r31->unk4C, 0x759);
                    }
                }
            }
            if (temp_r31->unk14 == 6 && temp_r31->unk20[0] == 2 && Hu3DMotionTimeGet(var_r25->unk28) == 12.0f) {
                break;
            }
            if (lbl_1_data_260[temp_r31->unk14] > 1) {
                if (var_r26 <= 0) {
                    break;
                }
                if (Hu3DMotionEndCheck(var_r25->unk28) && Hu3DMotionEndCheck(var_r29->unk28)) {
                    break;
                }
            }
            else {
                if (var_r26 <= 0) {
                    break;
                }
                if (Hu3DMotionEndCheck(var_r25->unk28)) {
                    break;
                }
            }
            HuPrcVSleep();
            var_r26--;
        }
        temp_r31->unk1C = 0;
        var_r25->unk34 = 0;
        if (temp_r31->unk14 != 6) {
            if (temp_r31->unk20[0] == 0) {
                Hu3DMotionSet(var_r25->unk28, var_r25->unk08[temp_r31->unk0C + 1]);
                Hu3DMotionTimeSet(var_r25->unk28, Hu3DMotionMaxTimeGet(var_r25->unk28));
                Hu3DMotionSpeedSet(var_r25->unk28, 2.0f);
                Hu3DModelAttrSet(var_r25->unk28, HU3D_MOTATTR_REV);
                Hu3DModelAttrReset(var_r25->unk28, HU3D_MOTATTR_LOOP);
            }
            if (lbl_1_data_260[temp_r31->unk14] > 1 && temp_r31->unk20[1] == 0) {
                var_r29->unk34 = 0;
                Hu3DMotionSet(var_r29->unk28, var_r29->unk08[temp_r31->unk0C + 1]);
                Hu3DMotionTimeSet(var_r29->unk28, Hu3DMotionMaxTimeGet(var_r29->unk28));
                Hu3DMotionSpeedSet(var_r29->unk28, 2.0f);
                Hu3DModelAttrSet(var_r29->unk28, HU3D_MOTATTR_REV);
                Hu3DModelAttrReset(var_r29->unk28, HU3D_MOTATTR_LOOP);
            }
            if (lbl_1_data_260[temp_r31->unk14] > 1) {
                while (!Hu3DMotionEndCheck(var_r25->unk28) || !Hu3DMotionEndCheck(var_r29->unk28)) {
                    HuPrcVSleep();
                }
            }
            else {
                while (!Hu3DMotionEndCheck(var_r25->unk28)) {
                    HuPrcVSleep();
                }
            }
        }
        Hu3DMotionSpeedSet(var_r25->unk28, 1.0f);
        if (lbl_1_data_260[temp_r31->unk14] > 1) {
            Hu3DMotionSpeedSet(var_r29->unk28, 1.0f);
        }
        Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_REV);
        if (temp_r31->unk14 == 6 && temp_r31->unk20[0] == 0) {
            HuPrcSleep(26);
            Hu3DMotionSet(var_r25->unk28, var_r25->unk08[temp_r31->unk0C + 1]);
            Hu3DMotionTimeSet(var_r25->unk28, Hu3DMotionMaxTimeGet(var_r25->unk28));
            Hu3DMotionSpeedSet(var_r25->unk28, 2.0f);
            Hu3DModelAttrSet(var_r25->unk28, HU3D_MOTATTR_REV);
            Hu3DModelAttrReset(var_r25->unk28, HU3D_MOTATTR_LOOP);
        }
        while (!Hu3DMotionEndCheck(temp_r31->unk00)) {
            HuPrcVSleep();
        }
        var_r25->unk30 = -1;
        Hu3DModelAttrSet(var_r25->unk28, HU3D_ATTR_DISPOFF);
        if (lbl_1_data_260[temp_r31->unk14] > 1) {
            var_r29->unk30 = -1;
            Hu3DModelAttrSet(var_r29->unk28, HU3D_ATTR_DISPOFF);
        }
        Hu3DModelHookReset(temp_r31->unk00);
        Hu3DMotionSet(temp_r31->unk00, temp_r31->unk02[0]);
        Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_LOOP);
        temp_r31->unk34 = 0;
        HuPrcVSleep();
    }
}

// identical to m411Dll/main.c::fn_1_5D58
s8 fn_1_2BF4(s32 arg0, s32 arg1)
{
    UnkM445Struct_02 *temp_r31;
    s8 var_r30;

    temp_r31 = &lbl_1_bss_588[arg0];
    if (!GWPlayerCfg[arg0].iscom) {
        (arg1 != 0) ? (var_r30 = HuPadStkY[temp_r31->unk20]) : (var_r30 = HuPadStkX[temp_r31->unk20]);
    }
    else {
        (arg1 != 0) ? (var_r30 = temp_r31->unk7D) : (var_r30 = temp_r31->unk7C);
    }
    return var_r30;
}

void fn_1_2CAC(Vec *arg0, float arg1, float arg2)
{
    float temp_f29;

    temp_f29 = sqrtf(arg0->x * arg0->x + arg0->z * arg0->z);
    temp_f29 *= arg2;
    arg0->x = temp_f29 * sind(arg1);
    arg0->z = temp_f29 * cosd(arg1);
}

// similar to m414Dll/main.c::fn_1_5554
// TODO: update other files (m414 and m411).
s8 fn_1_2E68(s32 arg0, s32 arg1)
{
    UnkM445Struct_02 *temp_r31;
    s8 var_r30;

    temp_r31 = &lbl_1_bss_588[arg0];
    var_r30 = 0;
    if (!GWPlayerCfg[arg0].iscom && lbl_1_bss_6DC < 4) {
        (arg1 != 0) ? (var_r30 = HuPadStkY[temp_r31->unk20]) : (var_r30 = HuPadStkX[temp_r31->unk20]);
    }
    else {
        (arg1 != 0) ? (var_r30 = temp_r31->unk7D) : (var_r30 = temp_r31->unk7C);
    }
    return var_r30;
}

u8 fn_1_2F38(s32 arg0, s32 arg1)
{
    UnkM445Struct_02 *temp_r31;
    s8 var_r30;

    temp_r31 = &lbl_1_bss_588[arg0];
    var_r30 = 0;
    if (lbl_1_bss_6DC < 4) {
        if (!GWPlayerCfg[arg0].iscom) {
            (arg1 != 0) ? (var_r30 = HuPadTrigR[temp_r31->unk20]) : (var_r30 = HuPadTrigL[temp_r31->unk20]);
        }
        else {
            (arg1 != 0) ? (var_r30 = temp_r31->unk7E) : (var_r30 = temp_r31->unk7F);
        }
    }
    return var_r30;
}

u16 fn_1_3010(s32 arg0)
{
    UnkM445Struct_02 *temp_r31;
    u16 var_r30;

    temp_r31 = &lbl_1_bss_588[arg0];
    var_r30 = 0;
    if (lbl_1_bss_6DC < 4) {
        if (!GWPlayerCfg[arg0].iscom) {
            var_r30 = HuPadBtnDown[temp_r31->unk20];
        }
        else {
            var_r30 = temp_r31->unk82;
        }
    }
    return var_r30;
}

u16 fn_1_3094(s32 arg0)
{
    UnkM445Struct_02 *temp_r31;
    u16 var_r30;

    temp_r31 = &lbl_1_bss_588[arg0];
    if (lbl_1_bss_6DC < 4) {
        if (!GWPlayerCfg[arg0].iscom) {
            var_r30 = HuPadBtn[temp_r31->unk20];
        }
        else {
            var_r30 = temp_r31->unk80;
        }
    }
    return var_r30;
}

s32 fn_1_3114(UnkM445Struct_02 *arg0, float arg1, float arg2, float arg3)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    s32 var_r28;
    float var_f27;
    float var_f28;
    UnkM445Struct_02 *temp_r31;
    s32 i;

    var_r28 = -1;
    for (i = 0, var_f28 = 10000.0f; i < 2; i++) {
        if (i == arg0->unk18) {
            continue;
        }
        temp_r31 = &lbl_1_bss_588[i];
        HuSetVecF(&sp30, arg1, arg2, arg3);
        HuSetVecF(&sp24, temp_r31->unk34, temp_r31->unk38, temp_r31->unk3C);
        HuSubVecF(&sp18, &sp30, &sp24);
        if ((var_f27 = sqrtf(sp18.x * sp18.x + sp18.y * sp18.y + sp18.z * sp18.z)) < arg0->unk54 + temp_r31->unk54 && var_f27 < var_f28) {
            var_f28 = var_f27;
            var_r28 = i;
        }
    }
    return var_r28;
}

s32 fn_1_3334(UnkM445Struct_02 *arg0, s32 *arg1)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    float var_f27;
    float var_f28;
    UnkM445Struct_02 *temp_r31;
    s32 var_r27;
    s32 var_r28;
    s32 i;

    var_r27 = -1;
    for (i = 0, var_f28 = 10000.0f, var_r28 = 0; i < 2; i++) {
        if (i == arg0->unk18) {
            continue;
        }
        temp_r31 = &lbl_1_bss_588[i];
        HuSetVecF(&sp30, arg0->unk34, arg0->unk38, arg0->unk3C);
        HuSetVecF(&sp24, temp_r31->unk34, temp_r31->unk38, temp_r31->unk3C);
        HuSubVecF(&sp18, &sp30, &sp24);
        if ((var_f27 = sqrtf(sp18.x * sp18.x + sp18.y * sp18.y + sp18.z * sp18.z)) < arg0->unk54 + temp_r31->unk54) {
            var_r28++;
            if (var_f27 < var_f28) {
                var_f28 = var_f27;
                var_r27 = i;
            }
        }
    }
    *arg1 = var_r28;
    return var_r27;
}

void fn_1_3548(UnkM445Struct_02 *arg0)
{
    Vec spA8;
    Vec sp9C;
    Vec sp90;
    s32 sp68;
    s32 var_r25;
    s32 temp_r24;
    float sp64;
    float sp60;
    float sp5C;
    float sp58;
    float sp54;
    float sp50;
    float sp4C;
    float var_f20;
    float var_f27;
    float var_f26;
    float var_f25;
    UnkM445Struct_02 *var_r30;
    UnkM445Struct_02 *temp_r27;
    s32 i;

    temp_r24 = fn_1_3334(arg0, &sp68);
    if (temp_r24 == -1) {
        return;
    }
    var_f20 = fn_1_1858(atan2d(arg0->unk34 - arg0->unk40, arg0->unk3C - arg0->unk44));
    sp58 = var_f27 = arg0->unk40;
    sp54 = var_f26 = arg0->unk44;
    sp4C = 1.0f;
    var_r25 = 1.0f + 10.0f / sp4C;
    while (var_r25 != 0) {
        var_f27 += sp4C * sind(var_f20);
        var_f26 += sp4C * cosd(var_f20);
        HuSetVecF(&spA8, var_f27, arg0->unk38, var_f26);
        for (i = 0; i < 2; i++) {
            if (i != arg0->unk18) {
                var_r30 = &lbl_1_bss_588[i];
                HuSetVecF(&sp9C, var_r30->unk34, var_r30->unk38, var_r30->unk3C);
                HuSubVecF(&sp90, &spA8, &sp9C);
                if (sqrtf(sp90.x * sp90.x + sp90.y * sp90.y + sp90.z * sp90.z) < arg0->unk54 + var_r30->unk54) {
                    break;
                }
            }
        }
        if (i < 2) {
            break;
        }
        AddX = 0.0f;
        AddZ = 0.0f;
        MapWall(arg0->unk54, var_f27, arg0->unk38 + arg0->unk54, var_f26);
        if (AddX + AddZ != 0.0f) {
            goto block_end;
        }
        sp58 = var_f27;
        sp54 = var_f26;
        var_r25--;
    }
    var_f20 = fn_1_1858(atan2d(arg0->unk34 - arg0->unk40, arg0->unk3C - arg0->unk44));
    var_f25 = fn_1_1858(atan2d(var_r30->unk34 - arg0->unk40, var_r30->unk3C - arg0->unk44));
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
    var_f25 = fn_1_1858(atan2d(arg0->unk40 - var_r30->unk34, arg0->unk44 - var_r30->unk3C));
    sp50 = 0.8f * arg0->unk58;
    temp_r24 = var_r30->unk18;
    sp64 = arg0->unk54 + var_r30->unk54 + 1.0f;
    while (TRUE) {
        var_f27 = var_r30->unk34 + sp64 * sind(var_f25);
        var_f26 = var_r30->unk3C + sp64 * cosd(var_f25);
        HuSetVecF(&spA8, var_f27, 0.0, var_f26);
        for (i = 0; i < 2; i++) {
            if (i != arg0->unk18 && i != temp_r24) {
                temp_r27 = &lbl_1_bss_588[i];
                HuSetVecF(&sp9C, temp_r27->unk34, 0.0, temp_r27->unk3C);
                HuSubVecF(&sp90, &spA8, &sp9C);
                if (sqrtf(sp90.x * sp90.x + sp90.z * sp90.z) < arg0->unk54 + temp_r27->unk54) {
                    break;
                }
            }
        }
        if (i < 2) {
            break;
        }
        AddX = 0.0f;
        AddZ = 0.0f;
        MapWall(arg0->unk54, var_f27, arg0->unk38 + arg0->unk54, var_f26);
        if (AddX + AddZ >= 5.0f) {
            break;
        }
        sp58 = var_f27;
        sp54 = var_f26;
        HuSetVecF(&spA8, arg0->unk40, 0.0, arg0->unk44);
        HuSetVecF(&sp9C, var_f27, 0.0, var_f26);
        HuSubVecF(&sp90, &spA8, &sp9C);
        if (sqrtf(sp90.x * sp90.x + sp90.z * sp90.z) > sp50) {
            break;
        }
        var_f25 += sp5C;
    }
block_end:
    arg0->unk34 = sp58;
    arg0->unk3C = sp54;
}

float fn_1_42A0(float arg0, float arg1, float arg2)
{
    float var_f31;
    float var_f30;

    var_f31 = fmod(arg1 - arg0, 360.0);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg0 + var_f31 * arg2, 360.0);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

BOOL fn_1_43A4(UnkM445Struct_02 *arg0, float arg1, float arg2)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    BOOL var_r30;

    var_r30 = FALSE;
    HuSetVecF(&sp2C, arg0->unk34 + 120.0 * sind(arg0->unk4C), 0.0, arg0->unk3C + 120.0 * cosd(arg0->unk4C));
    HuSetVecF(&sp20, arg1, 0.0, arg2);
    HuSubVecF(&sp14, &sp2C, &sp20);
    if (sqrtf(sp14.x * sp14.x + sp14.z * sp14.z) < 80.0f) {
        var_r30 = TRUE;
    }
    return var_r30;
}

void fn_1_45D0(UnkM445Struct_02 *arg0)
{
    Vec spC8;
    Vec spBC;
    Vec spB0;
    float sp64;
    float sp60;
    float sp5C;
    float sp58;
    float sp54;
    float var_f24;
    UnkM445Struct_00 *temp_r30;
    UnkM445Struct_02 *var_r28;
    u32 var_r27;
    s32 i;

    arg0->unk7C = arg0->unk7D = 0;
    arg0->unk7F = arg0->unk7E = 0;
    arg0->unk80 = arg0->unk82 = 0;
    if (arg0->unk18 != 0) {
        var_r28 = &lbl_1_bss_588[0];
    }
    else {
        var_r28 = &lbl_1_bss_588[1];
    }
    switch (GWPlayerCfg[arg0->unk18].diff) {
        case 0:
            var_r27 = 90;
            sp58 = 90.0f;
            sp54 = 0.4f;
            break;
        case 1:
            var_r27 = 95;
            sp58 = 60.0f;
            sp54 = 0.6f;
            break;
        case 2:
            var_r27 = 99;
            sp58 = 30.0f;
            sp54 = 0.8f;
            break;
        default:
            var_r27 = 100;
            sp58 = 10.0f;
            sp54 = 1.0f;
            break;
    }
    for (i = 0, sp5C = 10000.0f; i < 8; i++) {
        temp_r30 = &lbl_1_bss_288[i];
        if (temp_r30->unk1C >= 1 && !(temp_r30->unk44 < sp58)) {
            HuSetVecF(&spC8, arg0->unk34, 0.0, arg0->unk3C);
            HuSetVecF(&spBC, temp_r30->unk48, 0.0, temp_r30->unk4C);
            HuSubVecF(&spB0, &spC8, &spBC);
            var_f24 = sqrtf(spB0.x * spB0.x + spB0.z * spB0.z);
            sp60 = sqrtf(arg0->unk34 * arg0->unk34 + arg0->unk3C * arg0->unk3C);
            if (sp60 < 200.0f) {
                sp60 = 400.0f;
            }
            else {
                sp60 = 600.0f;
            }
            if (sp5C > var_f24 && var_f24 < sp60) {
                HuSetVecF(&spC8, var_r28->unk34, 0.0, var_r28->unk3C);
                HuSetVecF(&spBC, temp_r30->unk48, 0.0, temp_r30->unk4C);
                HuSubVecF(&spB0, &spC8, &spBC);
                if (sqrtf(spB0.x * spB0.x + spB0.z * spB0.z) > 50.0f) {
                    arg0->unk98 = i;
                    sp5C = var_f24;
                }
            }
        }
    }
    if (arg0->unk98 == -1) {
        for (i = 0, sp5C = 10000.0f; i < 8; i++) {
            temp_r30 = &lbl_1_bss_288[i];
            HuSetVecF(&spC8, arg0->unk34, 0.0, arg0->unk3C);
            HuSetVecF(&spBC, temp_r30->unk48, 0.0, temp_r30->unk4C);
            HuSubVecF(&spB0, &spC8, &spBC);
            var_f24 = sqrtf(spB0.x * spB0.x + spB0.z * spB0.z);
            if (sp5C > var_f24 && var_f24 > 200.0f) {
                arg0->unk98 = i;
                sp5C = var_f24;
                sp54 = 0.3f;
            }
        }
    }
    if (arg0->unk98 != -1) {
        temp_r30 = &lbl_1_bss_288[arg0->unk98];
        arg0->unk84 = temp_r30->unk48;
        arg0->unk88 = temp_r30->unk4C;
        HuSetVecF(&spC8, arg0->unk34, 0.0, arg0->unk3C);
        HuSetVecF(&spBC, arg0->unk84, 0.0, arg0->unk88);
        HuSubVecF(&spB0, &spC8, &spBC);
        var_f24 = sqrtf(spB0.x * spB0.x + spB0.z * spB0.z);
        if (var_f24 > 20.0f) {
            sp64 = atan2d(arg0->unk84 - arg0->unk34, arg0->unk88 - arg0->unk3C);
            arg0->unk7C = 50.0 * sind(sp64) * sp54;
            arg0->unk7D = -50.0 * cosd(sp64) * sp54;
        }
        else {
            if (temp_r30->unk1C == 2) {
                for (i = 0; i < lbl_1_data_260[temp_r30->unk14]; i++) {
                    if (temp_r30->unk20[i] == 0) {
                        sp64 = atan2d(temp_r30->unk50[i] - arg0->unk34, temp_r30->unk58[i] - arg0->unk3C);
                        arg0->unk7C = 15.0 * sind(sp64);
                        arg0->unk7D = -15.0 * cosd(sp64);
                    }
                }
            }
            if (frandmod(100) > var_r27) {
                arg0->unk82 |= 0x100;
            }
            arg0->unk98 = -1;
        }
        if (temp_r30->unk1C == 2) {
            if (fn_1_43A4(arg0, temp_r30->unk50[0], temp_r30->unk58[0]) && temp_r30->unk20[0] == 0) {
                arg0->unk82 |= 0x100;
            }
            if (lbl_1_data_260[temp_r30->unk14] > 1 && fn_1_43A4(arg0, temp_r30->unk50[1], temp_r30->unk58[1]) && temp_r30->unk20[1] == 0) {
                arg0->unk82 |= 0x100;
            }
        }
    }
}

void fn_1_557C(void)
{
    s32 j;
    s32 i;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 5; j++) {
            HuSprAttrReset(lbl_1_bss_588[i].unk04, j, HUSPR_ATTR_DISPOFF);
        }
    }
}

void fn_1_55F0(void)
{
    s32 j;
    s32 i;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 5; j++) {
            HuSprAttrSet(lbl_1_bss_588[i].unk04, j, HUSPR_ATTR_DISPOFF);
        }
    }
}

void fn_1_5664(UnkM445Struct_02 *arg0, s32 arg1)
{
    HuSprBankSet(arg0->unk04, 3, arg1 % 10);
    HuSprBankSet(arg0->unk04, 4, arg1 / 10);
    HuSprAttrReset(arg0->unk04, 4, HUSPR_ATTR_DISPOFF);
}

void fn_1_5700(UnkM445Struct_02 *arg0)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    float temp_f27;
    float var_f26;
    float var_f21;
    float var_f20;
    UnkM445Struct_02 *var_r27;
    s32 i;
    s32 var_r28;

    if (lbl_1_bss_6DC == 4) {
        arg0->unk28 = 1;
        for (i = 10, var_f21 = 1.0f; i != 0; i--, var_f21 -= 0.1f) {
            Hu3DModelScaleSet(arg0->unk06, var_f21, var_f21, var_f21);
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(arg0->unk06, HU3D_ATTR_DISPOFF);
        arg0->unk06 = -1;
        Hu3DMotionOverlayReset(arg0->unk00);
        if (lbl_1_bss_588[0].unk06 == -1 && lbl_1_bss_588[1].unk06 == -1) {
            lbl_1_bss_6DC = 5;
        }
        return;
    }
    Hu3DMotionOverlayReset(arg0->unk00);
    arg0->unk7C = arg0->unk7D = 0;
    arg0->unk7F = arg0->unk7E = 0;
    arg0->unk80 = arg0->unk82 = 0;
    var_r28 = 0;
    if (arg0->unk18 == 0) {
        if (arg0->unk34 <= -152.0f) {
            arg0->unk84 = -230.0f;
            arg0->unk88 = 45.0f;
            var_r28 = 1;
        }
        else if (arg0->unk3C > 203.0f || arg0->unk3C < -203.0f) {
            arg0->unk84 = -170.0f;
            arg0->unk88 = arg0->unk3C;
        }
        else {
            arg0->unk84 = arg0->unk34;
            if (arg0->unk3C > 0.0f) {
                arg0->unk88 = 210.0f;
            }
            else {
                arg0->unk88 = -210.0f;
            }
        }
    }
    else {
        if (arg0->unk34 >= 152.0f) {
            arg0->unk84 = 230.0f;
            arg0->unk88 = -45.0f;
            var_r28 = 1;
        }
        else if (arg0->unk3C > 203.0f || arg0->unk3C < -203.0f) {
            arg0->unk84 = 170.0f;
            arg0->unk88 = arg0->unk3C;
        }
        else {
            arg0->unk84 = arg0->unk34;
            if (arg0->unk3C > 0.0f) {
                arg0->unk88 = 210.0f;
            }
            else {
                arg0->unk88 = -210.0f;
            }
        }
    }
    var_r27 = (arg0->unk18 != 0) ? &lbl_1_bss_588[0] : &lbl_1_bss_588[1];
    HuSetVecF(&sp38, arg0->unk34, 0.0, arg0->unk3C);
    HuSetVecF(&sp2C, var_r27->unk34, 0.0, var_r27->unk3C);
    HuSubVecF(&sp20, &sp38, &sp2C);
    var_f26 = sqrtf(sp20.x * sp20.x + sp20.z * sp20.z);
    if (var_f26 <= 110.0f) {
        var_f26 = sqrtf(arg0->unk34 * arg0->unk34 + arg0->unk3C * arg0->unk3C);
        var_f20 = sqrtf(var_r27->unk34 * var_r27->unk34 + var_r27->unk3C * var_r27->unk3C);
        if (lbl_1_bss_4 == -1) {
            temp_f27 = atan2d(arg0->unk34, arg0->unk3C);
            if (var_f26 < 400.0f) {
                if (var_f26 > var_f20) {
                    lbl_1_bss_4 = arg0->unk18;
                    lbl_1_bss_0 = temp_f27;
                    arg0->unk84 = arg0->unk34 + 100.0 * sind(temp_f27);
                    arg0->unk88 = arg0->unk3C + 100.0 * cosd(temp_f27);
                }
            }
            else {
                if (var_f26 < var_f20) {
                    temp_f27 += 180.0f;
                    lbl_1_bss_4 = arg0->unk18;
                    lbl_1_bss_0 = temp_f27;
                    arg0->unk84 = arg0->unk34 + 100.0 * sind(temp_f27);
                    arg0->unk88 = arg0->unk3C + 100.0 * cosd(temp_f27);
                }
            }
        }
        else if (arg0->unk18 == lbl_1_bss_4) {
            OSReport("pno %d dir %f\n", arg0->unk18, lbl_1_bss_0);
            arg0->unk84 = arg0->unk34 + 100.0 * sind(lbl_1_bss_0);
            arg0->unk88 = arg0->unk3C + 100.0 * cosd(lbl_1_bss_0);
        }
    }
    HuSetVecF(&sp38, arg0->unk34, 0.0, arg0->unk3C);
    HuSetVecF(&sp2C, arg0->unk84, 0.0, arg0->unk88);
    HuSubVecF(&sp20, &sp38, &sp2C);
    var_f26 = sqrtf(sp20.x * sp20.x + sp20.z * sp20.z);
    if (var_f26 < 20.0f && var_r28 != 0) {
        arg0->unk24 = 4;
    }
    temp_f27 = atan2d(arg0->unk84 - arg0->unk34, arg0->unk88 - arg0->unk3C);
    arg0->unk7C = 50.0 * sind(temp_f27);
    arg0->unk7D = -50.0 * cosd(temp_f27);
}

void fn_1_6268(void)
{
    Vec sp1D8;
    s32 sp120;
    float sp11C;
    float var_f19;
    UnkM445Struct_02 *temp_r31;
    UnkM445Struct_00 *temp_r30;
    u32 var_r24;
    s32 var_r26;
    s32 var_r28;
    s32 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk24 = 0;
    temp_r31->unk90 = 0;
    temp_r31->unk98 = -1;
    temp_r31->unk28 = 1;
    lbl_1_bss_4 = -1;
    while (lbl_1_bss_6DC == 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_6DC = 2;
    while (lbl_1_bss_6DC == 2) {
        HuPrcVSleep();
    }
    while (TRUE) {
        temp_r31->unk40 = temp_r31->unk34;
        temp_r31->unk44 = temp_r31->unk3C;
        if (GWPlayerCfg[temp_r31->unk18].iscom == 1) {
            fn_1_45D0(temp_r31);
        }
        if (lbl_1_bss_6DC >= 4) {
            fn_1_5700(temp_r31);
        }
        switch (temp_r31->unk24) {
            case 4:
                goto block_exit_loop;
        }
        if (fn_1_3010(temp_r31->unk18) & 0x100) {
            if (fn_1_520(temp_r31->unk18) == FALSE) {
                Hu3DMotionOverlayReset(temp_r31->unk00);
                CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk18].character], temp_r31->unk08[5]);
            }
            else {
                Hu3DMotionSet(temp_r31->unk00, temp_r31->unk08[4]);
                Hu3DMotionSpeedSet(temp_r31->unk00, 1.0f);
            }
            Hu3DModelAttrReset(temp_r31->unk00, HU3D_MOTATTR_LOOP);
            HuPrcSleep(15);
            if (temp_r31->unk18 != 0) {
                fn_1_4B8(temp_r31->unk34, temp_r31->unk3C, 0x75F);
            }
            else {
                fn_1_4B8(temp_r31->unk34, temp_r31->unk3C, 0x75E);
            }
            HuPrcSleep(15);
            HuSetVecF(&sp1D8, temp_r31->unk34 + 120.0 * sind(temp_r31->unk4C), 0.0, temp_r31->unk3C + 120.0 * cosd(temp_r31->unk4C));
            for (i = 0; i < 8; i++) {
                temp_r30 = &lbl_1_bss_288[i];
                if (temp_r30->unk1C == 2) {
                    sp120 = 0;
                    if (fn_1_43A4(temp_r31, temp_r30->unk50[0], temp_r30->unk58[0]) && temp_r30->unk20[0] == 0) {
                        sp120 = 1;
                        temp_r30->unk20[0] = 1;
                        temp_r30->unk28 = temp_r31->unk18;
                        if (temp_r31->unk18 != 0) {
                            fn_1_4B8(temp_r30->unk48, temp_r30->unk4C, 0x75D);
                        }
                        else {
                            fn_1_4B8(temp_r30->unk48, temp_r30->unk4C, 0x750);
                        }
                        Hu3DModelAttrReset(temp_r31->unk02, HU3D_ATTR_DISPOFF);
                        Hu3DMotionTimeSet(temp_r31->unk02, 0.0f);
                        Hu3DModelPosSet(temp_r31->unk02, sp1D8.x, 160.0f, sp1D8.z + 100.0f);
                        if (temp_r30->unk38 != 0) {
                            temp_r31->unk30 += 2;
                        }
                        else {
                            temp_r31->unk30++;
                        }
                        fn_1_5664(temp_r31, temp_r31->unk30);
                    }
                    if (lbl_1_data_260[temp_r30->unk14] > 1 && fn_1_43A4(temp_r31, temp_r30->unk50[1], temp_r30->unk58[1])
                        && temp_r30->unk20[1] == 0) {
                        temp_r30->unk20[1] = 1;
                        temp_r30->unk2C = temp_r31->unk18;
                        if (temp_r31->unk18 != 0) {
                            fn_1_4B8(temp_r30->unk48, temp_r30->unk4C, 0x75D);
                        }
                        else {
                            fn_1_4B8(temp_r30->unk48, temp_r30->unk4C, 0x750);
                        }
                        Hu3DModelAttrReset(temp_r31->unk02, HU3D_ATTR_DISPOFF);
                        Hu3DMotionTimeSet(temp_r31->unk02, 0.0f);
                        Hu3DModelPosSet(temp_r31->unk02, sp1D8.x, 160.0f, sp1D8.z + 100.0f);
                        if (temp_r30->unk38 != 0) {
                            temp_r31->unk30 += 2;
                        }
                        else {
                            temp_r31->unk30++;
                        }
                        fn_1_5664(temp_r31, temp_r31->unk30);
                    }
                }
            }
            while (!Hu3DMotionEndCheck(temp_r31->unk00)) {
                HuPrcVSleep();
            }
            temp_r31->unk24 = 0;
            if (fn_1_520(temp_r31->unk18) == FALSE) {
                CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk18].character], temp_r31->unk08[0]);
                Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_OVL_LOOP);
                if (lbl_1_bss_6DC < 5) {
                    Hu3DMotionOverlaySet(temp_r31->unk00, temp_r31->unk08[4]);
                    Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_OVL_LOOP);
                }
            }
            else {
                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk08[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                Hu3DMotionShiftSpeedSet(temp_r31->unk00, 1.0f);
            }
        }
        else {
            HuSetVecF(&sp1D8, fn_1_2E68(temp_r31->unk18, 0) / 4.0f, 0.0, -fn_1_2E68(temp_r31->unk18, 1) / 4.0f);
            temp_r31->unk5C = sqrtf(sp1D8.x * sp1D8.x + sp1D8.y * sp1D8.y + sp1D8.z * sp1D8.z);
            if (temp_r31->unk5C >= 0.5f) {
                if (temp_r31->unk5C >= 10.0f) {
                    sp1D8.x /= temp_r31->unk5C;
                    sp1D8.z /= temp_r31->unk5C;
                    temp_r31->unk5C = 10.0f;
                    sp1D8.x = 10.0f * sp1D8.x;
                    sp1D8.z = 10.0f * sp1D8.z;
                }
                temp_r31->unk4C = fn_1_1858(fn_1_42A0(temp_r31->unk4C, atan2d(sp1D8.x, sp1D8.z), 0.4f));
                if (temp_r31->unk5C >= 8.0f) {
                    if (temp_r31->unk24 != 2) {
                        temp_r31->unk24 = 2;
                        if (fn_1_520(temp_r31->unk18) == FALSE) {
                            CharModelMotionShiftSet(
                                lbl_1_data_0[GWPlayerCfg[temp_r31->unk18].character], temp_r31->unk08[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                            if (lbl_1_bss_6DC < 5) {
                                Hu3DMotionOverlaySet(temp_r31->unk00, temp_r31->unk08[4]);
                                Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_OVL_LOOP);
                            }
                        }
                        else {
                            Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk08[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                            Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                        }
                    }
                }
                else if (temp_r31->unk24 != 1) {
                    temp_r31->unk24 = 1;
                    if (fn_1_520(temp_r31->unk18) == FALSE) {
                        CharModelMotionShiftSet(
                            lbl_1_data_0[GWPlayerCfg[temp_r31->unk18].character], temp_r31->unk08[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                        if (lbl_1_bss_6DC < 5) {
                            Hu3DMotionOverlaySet(temp_r31->unk00, temp_r31->unk08[4]);
                            Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_OVL_LOOP);
                        }
                    }
                    else {
                        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk08[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                        Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                    }
                }
            }
            else if (temp_r31->unk24 != 0) {
                temp_r31->unk24 = 0;
                if (fn_1_520(temp_r31->unk18) == FALSE) {
                    CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk18].character], temp_r31->unk08[0], 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
                    if (lbl_1_bss_6DC < 5) {
                        Hu3DMotionOverlaySet(temp_r31->unk00, temp_r31->unk08[4]);
                        Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_OVL_LOOP);
                    }
                }
                else {
                    Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk08[0], 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
                    Hu3DMotionShiftSpeedSet(temp_r31->unk00, 1.0f);
                }
            }
            temp_r31->unk70.x = sp1D8.x;
            temp_r31->unk70.z = sp1D8.z;
            temp_r31->unk58 = temp_r31->unk5C;
            temp_r31->unk34 += temp_r31->unk70.x;
            temp_r31->unk3C += temp_r31->unk70.z;
        }
        if ((temp_r31->unk2C = fn_1_3114(temp_r31, temp_r31->unk34, temp_r31->unk38, temp_r31->unk3C)) != -1) {
            fn_1_3548(temp_r31);
        }
        AddX = 0.0f;
        AddZ = 0.0f;
        MapWall(temp_r31->unk54, temp_r31->unk34, temp_r31->unk38 + temp_r31->unk54, temp_r31->unk3C);
        temp_r31->unk34 += AddX;
        temp_r31->unk3C += AddZ;
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk34, temp_r31->unk38, temp_r31->unk3C);
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        HuPrcVSleep();
    }
block_exit_loop:
    lbl_1_bss_6DC = 6;
    if (fn_1_520(temp_r31->unk18) == FALSE) {
        CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk18].character], temp_r31->unk08[0], 0.0f, 2.0f, HU3D_MOTATTR_LOOP);
    }
    else {
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk08[0], 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
        Hu3DMotionShiftSpeedSet(temp_r31->unk00, 1.0f);
    }
    var_f19 = 10.0f;
    i = (360.0f - fn_1_1858(temp_r31->unk4C)) / var_f19;
    if (temp_r31->unk4C < 180.0f) {
        i = fn_1_1858(temp_r31->unk4C) / var_f19;
        var_f19 = -var_f19;
    }
    for (; i != 0; i--) {
        temp_r31->unk4C += var_f19;
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk48, 0.0f, temp_r31->unk50);
    while (lbl_1_bss_6DC < 7) {
        HuPrcVSleep();
    }
    if (lbl_1_bss_588->unk30 == lbl_1_bss_588[1].unk30) {
        var_r26 = -1;
    }
    if (lbl_1_bss_588->unk30 < lbl_1_bss_588[1].unk30) {
        var_r26 = 1;
    }
    if (lbl_1_bss_588->unk30 > lbl_1_bss_588[1].unk30) {
        var_r26 = 0;
    }
    var_r24 = HU3D_MOTATTR_NONE;
    if (temp_r31->unk18 != 0) {
        if (fn_1_520(1) == FALSE) {
            if (var_r26 != -1) {
                HuAudSStreamPlay(1);
            }
            else {
                HuAudSStreamPlay(4);
            }
        }
        else {
            if (var_r26 == 0) {
                HuAudSStreamPlay(1);
            }
            else {
                HuAudSStreamPlay(3);
            }
        }
    }
    if (var_r26 == -1) {
        if (fn_1_520(temp_r31->unk18) == FALSE) {
            var_r28 = 7;
        }
        else {
            var_r28 = 6;
        }
    }
    else {
        GWPlayerCoinWinSet(var_r26, 10);
        if (var_r26 == temp_r31->unk18) {
            var_r28 = 6;
        }
        else {
            var_r28 = 7;
        }
    }
    if (fn_1_520(temp_r31->unk18) == FALSE) {
        CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk18].character], temp_r31->unk08[var_r28], 0.0f, 8.0f, var_r24);
    }
    else {
        if (var_r28 == 6) {
            var_r28 = 5;
            var_r24 = HU3D_MOTATTR_LOOP;
        }
        else {
            var_r28 = 6;
            var_r24 = HU3D_MOTATTR_NONE;
        }
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk08[var_r28], 0.0f, 8.0f, var_r24);
        if (var_r28 == 6) {
            for (i = 10, sp11C = 30.0f / i; i != 0; i--) {
                temp_r31->unk4C += sp11C;
                Hu3DModelRotSet(temp_r31->unk00, 0.0f, temp_r31->unk4C, 0.0f);
                HuPrcVSleep();
            }
        }
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_7FC0(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    UnkM445Struct_02 *temp_r29;
    float var_f31;
    s16 var_r27;
    s16 var_r28;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (var_r27 = 0; var_r27 < 2; var_r27++) {
        temp_r29 = &lbl_1_bss_588[var_r27];
        if (temp_r29->unk28 != 0) {
            for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
                if (var_r31->unk14.x == 0.0f) {
                    break;
                }
            }
            if (var_r28 == particle->unk_30) {
                break;
            }
            var_r31->unk34.x = temp_r29->unk34 + 50.0 * sind(temp_r29->unk4C - 90.0f);
            var_r31->unk34.y = temp_r29->unk38 + 98.0f;
            var_r31->unk34.z = temp_r29->unk3C + 50.0 * cosd(temp_r29->unk4C - 90.0f);
            var_r31->unk14.x = 30.0f;
            var_r31->unk2C = 100.0f;
            var_r31->unk14.y = 10.0f;
            var_r31->unk40.a = 200;
            var_r31->unk14.z = 17.0f;
            temp_r29->unk28 = 0;
        }
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
            if (0.0f == var_r31->unk14.x) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}

void fn_1_8320(void)
{
    float sp20[2];
    GXColor sp1C;
    WindowData *var_r26;
    UnkM445Struct_02 *temp_r31;
    s16 temp_r25;
    s16 var_r29;
    u32 var_r27;
    s32 temp_r28;
    s32 var_r24;
    s32 i;

    HuPrcSleep(30);
    HuAudFXPlay(0x755);
    temp_r28 = lbl_1_bss_288[5].unk00;
    Hu3DModelAttrReset(temp_r28, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    while (!Hu3DMotionEndCheck(temp_r28)) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x756);
    Hu3DMotionSet(temp_r28, lbl_1_bss_288[5].unk02[0]);
    Hu3DModelAttrSet(temp_r28, HU3D_MOTATTR_LOOP);
    HuPrcSleep(30);
    for (i = 30; i != 0; i--) {
        CRotM[0].x += -0.55f;
        CenterM[0].y += -11.5f;
        CZoomM[0] += 51.333332f;
        HuPrcVSleep();
    }
    if (fn_1_520(1) == TRUE) {
        temp_r25 = HuAudSeqPlay(0x3D);
        HuWinMesMaxSizeGet(8, sp20, MAKE_MESSID(41, 1), MAKE_MESSID(41, 2), MAKE_MESSID(41, 3), MAKE_MESSID(41, 4), MAKE_MESSID(41, 5),
            MAKE_MESSID(41, 6), MAKE_MESSID(41, 7), MAKE_MESSID(41, 8));
        var_r29 = HuWinCreate(-10000.0f, 40.0f, sp20[0], sp20[1], 1);
        HuWinPriSet(var_r29, 0x100);
        sp1C.r = sp1C.g = sp1C.b = 0xFF;
        HuWinBGColSet(var_r29, &sp1C);
        HuWinBGTPLvlSet(var_r29, 0.9f);
        HuWinMesColSet(var_r29, 0);
        var_r26 = &winData[var_r29];
        var_r26->mess_shadow_color = 9;
        HuWinMesSpeedSet(var_r29, 0);
        HuWinDisablePlayerSet(var_r29, (1 << GWPlayerCfg->pad_idx) ^ 0xF);
        HuWinExAnimIn(var_r29);
        HuWinMesSet(var_r29, MAKE_MESSID(41, 1));
        HuWinMesWait(var_r29);
        HuWinMesColSet(var_r29, 0);
        HuWinMesSet(var_r29, MAKE_MESSID(41, 2));
        var_r24 = HuWinChoiceGet(var_r29, 0);
        if (var_r24 == 0) {
            i = 5;
            var_r27 = MAKE_MESSID(41, 3);
        }
        else {
            i = 1;
            var_r27 = MAKE_MESSID(41, 8);
        }
        for (; i != 0; i--) {
            HuWinMesColSet(var_r29, 0);
            HuWinMesSet(var_r29, var_r27++);
            HuWinMesWait(var_r29);
        }
        HuAudSeqFadeOut(temp_r25, 1000);
        HuWinExAnimOut(var_r29);
        HuWinAllKill();
    }
    for (i = 0; i < 2; i++) {
        temp_r31 = &lbl_1_bss_588[i];
        if (fn_1_520(temp_r31->unk18) == FALSE) {
            CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[i].character], temp_r31->unk08[3]);
        }
        else {
            Hu3DMotionSet(temp_r31->unk00, temp_r31->unk08[3]);
        }
        Hu3DModelAttrReset(temp_r31->unk00, HU3D_MOTATTR_LOOP);
    }
    HuPrcSleep(20);
    for (i = 0; i < 2; i++) {
        temp_r31 = &lbl_1_bss_588[i];
        Hu3DModelPosSet(temp_r31->unk06, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31->unk06, 0.0f, 0.0f, 0.0f);
        if (fn_1_520(temp_r31->unk18) == FALSE) {
            Hu3DModelHookSet(temp_r31->unk00, CharModelHookNameGet(GWPlayerCfg[i].character, 2, 0), temp_r31->unk06);
        }
        else {
            Hu3DModelHookSet(temp_r31->unk00, "itemhook_r", temp_r31->unk06);
        }
    }
    HuPrcSleep(20);
    for (i = 0; i < 2; i++) {
        temp_r31 = &lbl_1_bss_588[i];
        if (fn_1_520(temp_r31->unk18) == FALSE) {
            CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk18].character], temp_r31->unk08[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            Hu3DMotionOverlaySet(temp_r31->unk00, temp_r31->unk08[4]);
        }
        else {
            Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk08[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        }
    }
}

void fn_1_8938(void)
{
    s32 i;

    while (lbl_1_bss_6DC < 6) {
        HuPrcVSleep();
    }
    for (i = 30; i != 0; i--) {
        CZoomM[0] += -27.7f;
        HuPrcVSleep();
    }
}

void fn_1_89B8(void)
{
    while (TRUE) {
        if (omSysExitReq == 1) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            HuPrcSleep(60);
            MGSeqKillAll();
            omOvlReturnEx(1, 1);
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_8A18(void)
{
    s16 temp_r28;
    s16 var_r31;
    s16 temp_r26;
    s32 var_r25;
    s32 i;

    lbl_1_bss_6DC = 0;
    fn_1_8320();
    HuPrcSleep(30);
    lbl_1_bss_6DC = 1;
    while (lbl_1_bss_6DC == 1) {
        HuPrcVSleep();
    }
    var_r25 = HuAudSeqPlay(0x3E);
    temp_r28 = MGSeqStartCreate();
    while (MGSeqStatGet(temp_r28) != 0) {
        HuPrcVSleep();
    }
    fn_1_557C();
    var_r31 = (REFRESH_RATE*61)-1;
    temp_r26 = MGSeqTimerCreate(var_r31 / REFRESH_RATE);
    lbl_1_bss_6DC = 3;
    while (TRUE) {
        if (var_r31 < (REFRESH_RATE-1)) {
            break;
        }
        MGSeqParamSet(temp_r26, 1, var_r31-- / REFRESH_RATE);
        lbl_1_bss_6D8++;
        HuPrcVSleep();
    }
    lbl_1_bss_6C4 = -1;
    if (lbl_1_bss_588->unk30 != lbl_1_bss_588[1].unk30) {
        lbl_1_bss_6C4 = 0;
        if (lbl_1_bss_588->unk30 < lbl_1_bss_588[1].unk30) {
            lbl_1_bss_6C4 = 1;
        }
    }
    lbl_1_bss_6DC = 4;
    HuAudSeqFadeOut(var_r25, 100);
    MGSeqParamSet(temp_r26, 2, -1);
    temp_r28 = MGSeqFinishCreate();
    while (MGSeqStatGet(temp_r28) != 0) {
        HuPrcVSleep();
    }
    while (lbl_1_bss_588->unk24 != 4 || lbl_1_bss_588[1].unk24 != 4) {
        HuPrcVSleep();
    }
    while (lbl_1_bss_6DC < 6) {
        HuPrcVSleep();
    }
    for (i = 30; i != 0; i--) {
        CZoomM[0] += -27.7f;
        HuPrcVSleep();
    }
    lbl_1_bss_6DC = 7;
    HuPrcSleep(210);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuPrcSleep(60);
    HuAudFadeOut(1);
    MGSeqKillAll();
    omOvlReturnEx(1, 1);
    while (TRUE) {
        HuPrcVSleep();
    }
}
