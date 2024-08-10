#define HUSPR_USE_OLD_DEFS
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "rel_sqrt_consts.h"

#include "REL/m442Dll.h"

typedef struct M442StructBss5C {
    /* 0x00 */ float unk_00; // probably Vec
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ char unk14[4];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ float unk_1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
} M442StructBss5C; /* size = 0x30 */

typedef struct M442StructBssC05C {
    /* 0x00 */ void *unk_00;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ s32 unk_10;
} M442StructBssC05C; /* size = 0x14 */

typedef struct M442StructBssC084 {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ u8 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ float unk_10;
} M442StructBssC084; /* size = 0x14 */

typedef struct M442StructBssC9F8 {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ u8 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ omObjData *unk_10;
} M442StructBssC9F8; /* size = 0x14 */

typedef struct M442MainWork {
    /* 0x00 */ struct {
        u8 unk_00_field0 : 1;
        u8 unk_00_field1 : 1;
        u8 unk_00_field2 : 1;
        u8 unk_00_field3 : 1;
    };
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s8 unk_06;
    /* 0x07 */ s8 unk_07;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ float unk_18;
    /* 0x1C */ float unk_1C;
    /* 0x20 */ char unk20[4];
    /* 0x24 */ Vec unk_24;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ float unk_38;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ s16 unk_3E;
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ float unk_44;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ char unk4A[2];
    /* 0x4C */ float unk_4C;
    /* 0x50 */ float unk_50;
    /* 0x54 */ float unk_54;
    /* 0x58 */ float unk_58;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ char unk60[0xC];
    /* 0x6C */ s16 unk_6C;
    /* 0x70 */ Vec unk_70;
    /* 0x7C */ s32 unk_7C;
} M442MainWork; /* size = 0x80 */

typedef struct M442StructData0 {
    /* 0x00 */ float unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
} M442StructData0; /* size = 0x1C */

typedef struct M442MainWork2 {
    /* 0x00 */ struct {
        u8 unk_00_field0 : 1;
    };
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ float unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ float unk_18;
} M442MainWork2; /* size = 0x1C */

void GWMGRecordSet(s32 index, s32 value);
u32 GWMGRecordGet(s32 index);

void fn_1_A30(omObjData *object);
void fn_1_A90(Process *arg0);
void fn_1_D9C(void);
s32 fn_1_E04(void);
void fn_1_E88(omObjData *object);
void fn_1_2254(omObjData *object);
s16 fn_1_31FC(omObjData *object);
void fn_1_35AC(omObjData *object);
void fn_1_3658(omObjData *object);
void fn_1_37B8(omObjData *object);
void fn_1_394(omObjData *object);
s32 fn_1_3AE4(omObjData *object, Vec *arg1);
void fn_1_3C20(omObjData *object);
void fn_1_3C94(omObjData *object);
void fn_1_3E14(omObjData *object);
void fn_1_3E64(Process *arg0);
void fn_1_3EBC(void);
void fn_1_3EC0(omObjData *object);
void fn_1_4364(omObjData *object);
void fn_1_4444(s32 arg0);
void fn_1_448(omObjData *object);
void fn_1_485C(ModelData *model, Mtx mtx);
void fn_1_54C8(ModelData *model, Mtx mtx);
s16 fn_1_5918(Vec *arg0);
void fn_1_5A48(ModelData *model, Mtx mtx);
void fn_1_5EDC(ModelData *model, Mtx mtx);
void fn_1_64B4(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_6BB4(Process *arg0);
void fn_1_6CC8(void);
void fn_1_6D24(omObjData *object);
void fn_1_72C4(omObjData *object);
s32 fn_1_75DC(Vec *arg0);
void fn_1_7734(s32 arg0, s32 arg1);
void fn_1_7848(omObjData *object);
void fn_1_7890(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_7EBC(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_8520(M442StructBssC05C *arg0, u8 arg1);
float fn_1_85E8(float arg8, float arg9, float argA);
void fn_1_86EC(omObjData *object);
void fn_1_8738(s32 arg0, s32 arg1, float arg8);
void fn_1_8988(omObjData *object);
s32 fn_1_90FC(void);

M442StructData0 lbl_1_data_0[3] = {
    { 500.0f, 0.0f, 500.0f, 350.0f, 84.0f, 0.0f, 0.0f },
    { 600.0f, 0.0f, 350.0f, 400.0f, -30.0f, 0.0f, 0.0f },
    { 3300.0f, 0.0f, 150.0f, 150.0f, -37.0f, 0.0f, 0.0f },
};

Vec lbl_1_data_54 = { 700.0f, 2500.0f, -700.0f };

Vec lbl_1_data_60 = { 0.0f, 0.0f, 0.0f };

GXColor lbl_1_data_6C = { 0xFF, 0xFF, 0xFF, 0xFF };

Vec lbl_1_data_70 = { 200.0f, 15000.0f, -200.0f };

Vec lbl_1_data_7C = { 0.0f, 1.0f, 0.0f };

omObjData *lbl_1_bss_11F40;
omObjData *lbl_1_bss_11F3C;
omObjData *lbl_1_bss_11F38;
s32 lbl_1_bss_11F34;
u32 lbl_1_bss_11F30;
s32 lbl_1_bss_11F2C[1];
s32 lbl_1_bss_11F28[1];
s32 lbl_1_bss_11F24;
s32 lbl_1_bss_11F20;
s16 lbl_1_bss_11F1C;
s16 lbl_1_bss_11F1A;
s16 lbl_1_bss_11F18;
s16 lbl_1_bss_11F16;
s16 lbl_1_bss_11F14[1];
AnimData *lbl_1_bss_11F10;
AnimData *lbl_1_bss_11F04[3];
AnimData *lbl_1_bss_11F00;
AnimData *lbl_1_bss_11EFC;
AnimData *lbl_1_bss_11EEC[4];
s16 lbl_1_bss_11EE8;
s32 lbl_1_bss_11EE4;
s32 lbl_1_bss_11EE0;
u8 lbl_1_bss_11C6D[0x271];
char lbl_1_bss_119FC[0x271];
s32 lbl_1_bss_119F8;
M442StructBssC9F8 lbl_1_bss_C9F8[0x400];
M442StructBssC084 lbl_1_bss_C084[11][11];
M442StructBssC05C lbl_1_bss_C05C[2];
M442StructBss5C lbl_1_bss_5C[0x400];
float lbl_1_bss_20[0xF];
Vec lbl_1_bss_14;
s16 lbl_1_bss_12;
s16 lbl_1_bss_10;
char pad_05_00000000_bss[0x10];

void ObjectSetup(void)
{
    Process *var_r31;
    CameraData *var_r30;
    s16 var_r29;

    var_r30 = Hu3DCamera;
    OSReport("******* M442ObjectSetup *********\n");
    var_r31 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(var_r31);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lbl_1_bss_11F38 = omAddObjEx(var_r31, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_14.x = lbl_1_data_60.x - lbl_1_data_54.x;
    lbl_1_bss_14.y = lbl_1_data_60.y - lbl_1_data_54.y;
    lbl_1_bss_14.z = lbl_1_data_60.z - lbl_1_data_54.z;
    VECNormalize(&lbl_1_bss_14, &lbl_1_bss_14);
    var_r29 = Hu3DGLightCreateV(&lbl_1_data_54, &lbl_1_bss_14, &lbl_1_data_6C);
    Hu3DGLightInfinitytSet(var_r29);
    Hu3DGLightStaticSet(var_r29, 1);
    Hu3DShadowCreate(10.0f, var_r30->near, var_r30->far);
    Hu3DShadowTPLvlSet(0.625f);
    Hu3DShadowPosSet(&lbl_1_data_70, &lbl_1_data_7C, &lbl_1_data_60);
    HuAudSndGrpSet(0x44);
    lbl_1_bss_11F40 = omAddObjEx(var_r31, 0, 0, 0, -1, fn_1_394);
    lbl_1_bss_11F3C = omAddObjEx(var_r31, 0xA, 0, 0, -1, fn_1_86EC);
    fn_1_A90(var_r31);
    fn_1_3E64(var_r31);
    fn_1_6BB4(var_r31);
    if (!GWMGRecordGet(4)) {
        GWMGRecordSet(4, 0);
    }
    fn_1_91AC(var_r31, GWMGRecordGet(4));
    fn_1_94AC(0);
}

void fn_1_374(u32 arg0)
{
    lbl_1_bss_11F30 = arg0;
}

u32 fn_1_384(void)
{
    return lbl_1_bss_11F30;
}

void fn_1_394(omObjData *object)
{
    lbl_1_bss_11F30 = 0;
    lbl_1_bss_11F24 = 60;
    lbl_1_bss_11F1C = 60;
    lbl_1_bss_11F1A = 60;
    lbl_1_bss_11F18 = -1;
    lbl_1_bss_11F16 = 0;
    lbl_1_bss_11EE8 = 0;
    WipeCreate(1, 0, 60);
    object->func = fn_1_448;
}

s32 lbl_1_data_AC = -1;

void fn_1_448(omObjData *object)
{
    s32 var_r31;

    switch (lbl_1_bss_11F30) {
        case 0:
            if (lbl_1_bss_11F24 == 60) {
                HuAudFXPlay(0x71B);
                HuAudFXPlay(0x71F);
            }
            if (--lbl_1_bss_11F24 == 0) {
                lbl_1_bss_11F30 = 1;
                lbl_1_bss_11F24 = 0x78;
            }
            break;
        case 1:
            if (--lbl_1_bss_11F24 == 0) {
                lbl_1_bss_11F30 = 2;
                lbl_1_bss_11F24 = 0x78;
            }
            break;
        case 2:
            if (--lbl_1_bss_11F24 == 0) {
                lbl_1_bss_11F30 = 3;
                lbl_1_bss_12 = MGSeqCreate(3, 0);
            }
            break;
        case 3:
            if (MGSeqStatGet(lbl_1_bss_12) == 0) {
                lbl_1_bss_11F30 = 4;
                lbl_1_bss_10 = MGSeqCreate(1, 60, -1, -1);
            }
            if (lbl_1_data_AC < 0 && (MGSeqStatGet(lbl_1_bss_12) & 0x10)) {
                lbl_1_data_AC = HuAudSeqPlay(0x43);
            }
            break;
        case 4:
            if (--lbl_1_bss_11F1A == 0) {
                lbl_1_bss_11F1C -= 1;
                MGSeqParamSet(lbl_1_bss_10, 1, lbl_1_bss_11F1C);
                lbl_1_bss_11F1A = 0x3C;
            }
            if (lbl_1_bss_11F1C == 0 || lbl_1_bss_11EE4 == 0) {
                lbl_1_bss_11F30 = 5;
                lbl_1_bss_12 = MGSeqCreate(3, 1);
                HuAudSeqFadeOut(lbl_1_data_AC, 100);
            }
            break;
        case 5:
            if (lbl_1_bss_10 >= 0) {
                MGSeqParamSet(lbl_1_bss_10, 2, -1);
                lbl_1_bss_10 = -1;
            }
            if (MGSeqStatGet(lbl_1_bss_12) == 0 && fn_1_E04()) {
                if (GWMGRecordGet(4) < lbl_1_bss_11EE8) {
                    GWMGRecordSet(4, lbl_1_bss_11EE8);
                    lbl_1_bss_11F30 = 6;
                    lbl_1_bss_11F24 = 60;
                    lbl_1_bss_12 = MGSeqCreate(0xE, lbl_1_bss_11EE8);
                    fn_1_94AC(1);
                }
                else {
                    lbl_1_bss_11F30 = 9;
                    lbl_1_bss_11F24 = 60;
                }
                mgRecordExtra = lbl_1_bss_11EE8;
            }
            break;
        case 6:
            if (MGSeqStatGet(lbl_1_bss_12) == 0) {
                lbl_1_bss_11F30 = 9;
                lbl_1_bss_11F24 = 60;
            }
            break;
        case 9:
            if (--lbl_1_bss_11F24 == 0) {
                lbl_1_bss_11F30 = 11;
                if (lbl_1_bss_11EE8) {
                    HuAudSStreamPlay(1);
                }
                else {
                    HuAudSStreamPlay(4);
                }
                lbl_1_bss_11F24 = 0xD2;
            }
            break;
        case 11:
            if (--lbl_1_bss_11F24 == 0) {
                WipeCreate(2, 0, 0x3C);
                object->func = fn_1_A30;
            }
            break;
    }
    if (lbl_1_bss_11F16 != 0) {
        lbl_1_bss_11F18++;
        for (var_r31 = 0; var_r31 < lbl_1_bss_11F16; var_r31++) {
            GWPlayerCoinWinSet(lbl_1_bss_11F14[var_r31], lbl_1_bss_11F18);
        }
        lbl_1_bss_11F16 = 0;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(2, 0, 0x3C);
        object->func = fn_1_A30;
    }
}

void fn_1_A30(omObjData *object)
{
    if (WipeStatGet() == 0) {
        fn_1_D9C();
        fn_1_3EBC();
        fn_1_6CC8();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
        OSReport("******* M442Exit *********\n");
    }
}

void fn_1_A90(Process *arg0)
{
    s32 var_r31;
    s32 var_r30;

    s32 sp8[4] = { 0x00490003, 0x00490006, 0x00490005, 0x00490004 };

    lbl_1_bss_11F2C[0] = lbl_1_bss_11F2C[1] = lbl_1_bss_11F2C[2] = lbl_1_bss_11F2C[3] = -1;
    lbl_1_bss_11F28[0] = lbl_1_bss_11F28[1] = lbl_1_bss_11F28[2] = lbl_1_bss_11F28[3] = -1;
    lbl_1_bss_11F20 = 0;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayerCfg[var_r31].iscom != 1) {
            break;
        }
        lbl_1_bss_11F20++;
    }
    omMakeGroupEx(arg0, 0, 1);
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        omAddObjEx(arg0, 5, 0xA, 0x32, 0, fn_1_E88);
    }
    lbl_1_bss_11F00 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M442, 0x0A), MEMORY_DEFAULT_NUM));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_11EEC[var_r31] = HuSprAnimRead(HuDataReadNum(sp8[var_r31], MEMORY_DEFAULT_NUM));
    }
    memset(lbl_1_bss_C084, 0, 0x974);
    for (var_r31 = 0; var_r31 < 9; var_r31++) {
        for (var_r30 = 0; var_r30 < 9; var_r30++) {
            lbl_1_bss_C084[var_r31 + 1][var_r30 + 1].unk_00.x = 1600.0f * (var_r30 - 4) / 8;
            lbl_1_bss_C084[var_r31 + 1][var_r30 + 1].unk_00.y = 0.0f;
            lbl_1_bss_C084[var_r31 + 1][var_r30 + 1].unk_00.z = 1600.0f * (var_r31 - 4) / 8;
        }
    }
}

void fn_1_D9C(void)
{
    s32 var_r31;
    omObjData **var_r30;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    if (var_r30 != NULL) {
        for (var_r31 = 0; var_r31 < 1; var_r31++) {
            fn_1_3E14(var_r30[var_r31]);
        }
    }
}

s32 fn_1_E04(void)
{
    s32 var_r31;
    omObjData **var_r30;
    M442MainWork *var_r29;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        var_r29 = var_r30[var_r31]->data;
        if (!var_r29->unk_00_field1) {
            return 0;
        }
    }
    return 1;
}

s32 lbl_1_data_FC[7] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x48),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18),
};

s32 lbl_1_data_118[2] = { 0x490010, 0x490018 };

Vec lbl_1_data_120[4] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};

void fn_1_E88(omObjData *object)
{
    M442MainWork *var_r30;
    u32 var_r29;
    u32 var_r28;
    ModelData *var_r27;
    s32 var_r26;

    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M442MainWork), MEMORY_DEFAULT_NUM);
    object->data = var_r30;
    memset(var_r30, 0, sizeof(M442MainWork));
    var_r30->unk_02 = lbl_1_bss_11F20++;
    var_r30->unk_04 = GWPlayerCfg[var_r30->unk_02].pad_idx;
    var_r30->unk_0C = fn_1_90FC();
    var_r26 = GWPlayerCfg[var_r30->unk_02].character;
    var_r30->unk_10 = var_r26;
    var_r30->unk_12 = GWPlayerCfg[var_r30->unk_02].diff;
    var_r30->unk_14 = GWPlayerCfg[var_r30->unk_02].group;
    object->model[0] = CharModelCreate(var_r26, 8);
    Hu3DModelLayerSet(object->model[0], 1);
    Hu3DModelShadowSet(object->model[0]);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M442, 0x01));
    Hu3DModelHookSet(object->model[0], "test11_tex_we-itemhook-r", object->model[1]);
    var_r30->unk_30 = 0;
    for (var_r29 = 0; var_r29 < 7; var_r29++) {
        object->motion[var_r29] = CharModelMotionCreate(var_r30->unk_10, lbl_1_data_FC[var_r29]);
    }
    for (var_r28 = 0; var_r28 < 2; var_r28++) {
        object->motion[var_r29 + var_r28] = CharModelMotionCreate(var_r30->unk_10, var_r30->unk_10 + lbl_1_data_118[var_r28]);
    }
    Hu3DMotionSet(object->model[0], object->motion[0]);
    Hu3DModelAttrSet(object->model[0], 0x40000001);
    Hu3DMotionOverlaySet(object->model[0], object->motion[7]);
    CharModelVoiceEnableSet(var_r30->unk_10, object->motion[5], 0);
    object->trans.x = lbl_1_data_120[var_r30->unk_02].x;
    object->trans.y = lbl_1_data_120[var_r30->unk_02].y;
    object->trans.z = lbl_1_data_120[var_r30->unk_02].z;
    object->model[2] = Hu3DParticleCreate(lbl_1_bss_11F00, 0x32);
    Hu3DParticleHookSet(object->model[2], fn_1_7890);
    Hu3DModelAttrSet(object->model[2], 1);
    Hu3DModelLayerSet(object->model[2], 1);
    var_r30->unk_5C = -1;
    var_r30->unk_40 = -1;
    object->model[3] = Hu3DHookFuncCreate(fn_1_5EDC);
    Hu3DModelLayerSet(object->model[3], 7);
    Hu3DModelAttrSet(object->model[3], 1);
    var_r27 = &Hu3DData[object->model[3]];
    var_r27->unk_120 = var_r30;
    CharModelDataClose(var_r30->unk_10);
    var_r30->unk_00_field2 = 1;
    var_r30->unk_00_field3 = 1;
    object->func = fn_1_2254;
}

void fn_1_1200(omObjData *object)
{
    void *sp8;
    s32 var_r31;

    sp8 = object->data;
    var_r31 = lbl_1_bss_11F30;
    if (var_r31 >= 2) {
        (void)var_r31;
    }
}

typedef struct Vec2s16 {
    s16 unk_00;
    s16 unk_02;
} Vec2s16;

s16 lbl_1_data_16A[8][2] = {
    { 0xFFFF, 0xFFFF },
    { 0, 0xFFFF },
    { 1, 0xFFFF },
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
    { 0xFFFF, 1 },
    { 0xFFFF, 0 },
};

void fn_1_1230(omObjData *object)
{
    Vec2s16 sp2AC[0x51];
    Vec2s16 sp168[0x51];
    s16 sp24[0xA2];
    Vec sp18;
    Vec2s16 sp14;
    Vec2s16 sp10;
    Vec2s16 spC;
    Vec2s16 sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    s32 var_r31;
    M442MainWork *var_r30;
    s32 var_r29;
    s32 var_r28;
    omObjData **var_r27;
    u32 var_r25;
    s32 var_r24;
    s16 var_r23;
    s16 var_r22;
    s32 var_r21;
    s16 var_r20;
    M442MainWork *var_r19;

    var_r30 = object->data;
    var_f28 = 1.0f;
    VECSubtract(&var_r30->unk_70, &object->trans, &sp18);
    var_f30 = VECMag(&sp18);
    if (var_f30 < 300.0f) {
        if (var_f30 < 140.0f) {
            if ((frand() & 1) == 0) {
                var_r30->unk_6C = 1;
            }
            else {
                var_r30->unk_00_field2 = 1;
            }
        }
        else {
            var_f29 = 32.0f;
            VECNormalize(&sp18, &sp18);
            var_r30->unk_06 = sp18.x * var_f29;
            var_r30->unk_07 = -sp18.z * var_f29;
        }
        return;
    }
    sp14.unk_00 = 4.0f + ((8.0f * object->trans.x) / 1600.0f);
    sp14.unk_02 = 4.0f + ((8.0f * object->trans.z) / 1600.0f);
    sp8.unk_00 = 4.0f + ((8.0f * var_r30->unk_70.x) / 1600.0f);
    sp8.unk_02 = 4.0f + ((8.0f * var_r30->unk_70.z) / 1600.0f);
    for (var_r31 = 0; var_r31 < 9; var_r31++) {
        for (var_r29 = 0; var_r29 < 9; var_r29++) {
            lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_0C = 0;
            lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_10 = 0.0f;
            var_r27 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
            for (var_r28 = 0; var_r28 < 1; var_r28++) {
                if (var_r27[var_r28] != object) {
                    VECSubtract(&lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_00, &var_r27[var_r28]->trans, &sp18);
                    var_f30 = VECMag(&sp18);
                    if (var_f30 < 800.0f) {
                        var_f31 = cosd(((90.0f * var_f30) / 800.0f));
                        var_f31 *= var_f31;
                        if (var_f31 > lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_10) {
                            lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_10 = var_f31;
                        }
                    }
                }
            }
            var_r27 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
            for (var_r28 = 0; var_r28 < 15; var_r28++) {
                var_r19 = var_r27[var_r28]->data;
                if (var_r19->unk_00_field0) {
                    VECSubtract(&lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_00, &var_r27[var_r28]->trans, &sp18);
                    var_f30 = VECMag(&sp18);
                    if (var_f30 < 800.0f) {
                        var_f31 = cosd(((90.0f * var_f30) / 800.0f));
                        var_f31 *= var_f31;
                        if (var_f31 > lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_10) {
                            lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_10 = var_f31;
                        }
                    }
                }
            }
        }
    }
    var_r23 = var_r20 = 0;
    lbl_1_bss_C084[sp14.unk_02 + 1][sp14.unk_00 + 1].unk_0C = 1;
    sp2AC[var_r20++] = sp14;
    do {
        for (var_r31 = 0; var_r31 < 8U; var_r31++) {
            sp10.unk_00 = sp2AC[var_r23].unk_00 + lbl_1_data_16A[var_r31][0];
            sp10.unk_02 = sp2AC[var_r23].unk_02 + lbl_1_data_16A[var_r31][1];
            if ((sp10.unk_00 >= 0) && (sp10.unk_00 < 9) && (sp10.unk_02 >= 0) && (sp10.unk_02 < 9)
                && (lbl_1_bss_C084[sp10.unk_02 + 1][sp10.unk_00 + 1].unk_0C == 0)
                && (lbl_1_bss_C084[sp10.unk_02 + 1][sp10.unk_00 + 1].unk_10 >= 0.0f)) {
                lbl_1_bss_C084[sp10.unk_02 + 1][sp10.unk_00 + 1].unk_0C
                    = lbl_1_bss_C084[sp2AC[var_r23].unk_02 + 1][sp2AC[var_r23].unk_00 + 1].unk_0C + 1;
                sp2AC[var_r20++] = sp10;
            }
        }
        var_r23++;
    } while (var_r23 != var_r20);
    var_r24 = lbl_1_bss_C084[sp8.unk_02 + 1][sp8.unk_00 + 1].unk_0C;
    for (var_r31 = 0; var_r31 < 9; var_r31++) {
        for (var_r29 = 0; var_r29 < 9; var_r29++) {
            if (lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_0C >= var_r24) {
                lbl_1_bss_C084[var_r31 + 1][var_r29 + 1].unk_0C = 0;
            }
        }
    }
    lbl_1_bss_C084[sp8.unk_02 + 1][sp8.unk_00 + 1].unk_0C = var_r24;
    if (var_r24 > 1) {
        for (var_r31 = var_r24 - 1; var_r31 > 1; var_r31--) {
            for (var_r29 = 0; var_r29 < 9; var_r29++) {
                for (var_r28 = 0; var_r28 < 9; var_r28++) {
                    if (var_r31 == lbl_1_bss_C084[var_r29 + 1][var_r28 + 1].unk_0C) {
                        var_r21 = 0;
                        for (var_r25 = 0; var_r25 < 8; var_r25++) {
                            if ((var_r31 - 1)
                                == lbl_1_bss_C084[lbl_1_data_16A[var_r25][1] + var_r29 + 1][lbl_1_data_16A[var_r25][0] + var_r28 + 1].unk_0C) {
                                var_r21 |= 1;
                            }
                            else if ((var_r31 + 1)
                                == lbl_1_bss_C084[lbl_1_data_16A[var_r25][1] + var_r29 + 1][lbl_1_data_16A[var_r25][0] + var_r28 + 1].unk_0C) {
                                var_r21 |= 2;
                            }
                        }
                        if (var_r21 != 3) {
                            lbl_1_bss_C084[var_r29 + 1][var_r28 + 1].unk_0C = 0;
                        }
                    }
                }
            }
        }
    }
    var_r22 = 0;
    sp2AC[var_r22++] = sp14;
    var_f28 = 1.0f;
    do {
        var_r22--;
        spC = sp2AC[var_r22];
        sp168[lbl_1_bss_C084[spC.unk_02 + 1][spC.unk_00 + 1].unk_0C - 1] = spC;

        if (lbl_1_bss_C084[spC.unk_02 + 1][spC.unk_00 + 1].unk_0C >= var_r24) {
            var_f31 = 0.0f;
            for (var_r31 = 1; var_r31 < var_r24; var_r31++) {
                if (lbl_1_bss_C084[sp168[var_r31].unk_02 + 1][sp168[var_r31].unk_00 + 1].unk_10 > var_f31) {
                    var_f31 = lbl_1_bss_C084[sp168[var_r31].unk_02 + 1][sp168[var_r31].unk_00 + 1].unk_10;
                }
            }
            if (var_f31 < var_f28) {
                var_f28 = var_f31;
                memcpy(&sp24, &sp168[0], var_r24 * 4);
            }
        }
        else {
            for (var_r31 = 0; var_r31 < 8U; var_r31++) {
                sp10.unk_00 = spC.unk_00 + lbl_1_data_16A[var_r31][0];
                sp10.unk_02 = spC.unk_02 + lbl_1_data_16A[var_r31][1];
                if (lbl_1_bss_C084[sp10.unk_02 + 1][sp10.unk_00 + 1].unk_0C == (lbl_1_bss_C084[spC.unk_02 + 1][spC.unk_00 + 1].unk_0C + 1)) {
                    sp2AC[var_r22++] = sp10;
                }
            }
        }
    } while (var_r22 != 0);
    VECSubtract(&lbl_1_bss_C084[sp24[3] + 1][sp24[2] + 1].unk_00, &object->trans, &sp18);
    var_f30 = VECMag(&sp18);
    var_f29 = 64.0f + (0.2f * (32.0f * var_r30->unk_12));
    var_r30->unk_18 = fn_1_85E8(var_r30->unk_18, atan2d(sp18.x, sp18.z), 0.1f);
    var_r30->unk_06 = var_f29 * sind(var_r30->unk_18);
    var_r30->unk_07 = var_f29 * -cosd(var_r30->unk_18);

    if (++var_r30->unk_7C > 300) {
        var_r30->unk_00_field2 = 1;
        var_r30->unk_7C = 0;
    }
    (void)object;
    (void)var_r25;
    (void)var_r24;
    (void)var_r23;
}

void fn_1_2010(omObjData *object)
{
    omObjData *sp8[15];

    M442MainWork *var_r31;
    s32 var_r30;
    omObjData **var_r29;
    s32 var_r28;
    M442MainWork *var_r26;

    var_r31 = object->data;
    if (var_r31->unk_00_field2) {
        var_r31->unk_00_field2 = 0;
        var_r31->unk_6C = 0;
        var_r31->unk_7C = 0;
        if (((frand() & 0x1F) < (var_r31->unk_12 + 4)) && !var_r31->unk_00_field3) {
            var_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
            var_r28 = 0;
            for (var_r30 = 0; var_r30 < 15; var_r30++) {
                var_r26 = var_r29[var_r30]->data;
                if (!var_r26->unk_00_field0) {
                    sp8[var_r28++] = var_r29[var_r30];
                }
            }
            if (var_r28 == 0) {
                return;
            }
            var_r30 = (var_r28 * (frand() & 0xFF)) >> 8;
            var_r31->unk_70.x = sp8[var_r30]->trans.x;
            var_r31->unk_70.z = sp8[var_r30]->trans.z;
        }
        else {
            var_r31->unk_00_field3 = 0;
            var_r31->unk_70.x = 800.0f * ((frand() & 0x1FF) - 256.0f) / 256;
            var_r31->unk_70.z = 800.0f * ((frand() & 0x1FF) - 256.0f) / 256;
        }
    }
    switch (var_r31->unk_6C) {
        case 0:
            fn_1_1230(object);
            break;
        case 1:
            var_r31->unk_0A |= 0x100;
            break;
        default:
            break;
    }
}

void fn_1_2254(omObjData *object)
{
    Vec spC;
    float sp8;

    float var_f31;
    float var_f30;
    double var_f29;
    float var_f28;
    float var_f27;
    float var_f26;

    M442MainWork *var_r31;
    s32 var_r29;
    u32 var_r28;
    s32 var_r27;
    void *var_r26;
    omObjData **var_r25;
    M442MainWork *var_r24;
    s32 var_r23;
    s32 var_r22;

    var_r31 = object->data;
    var_r29 = var_r31->unk_30;
    var_r28 = var_r31->unk_34;
    var_f28 = var_r31->unk_38;

    if (!var_r31->unk_00_field1) {
        var_r23 = lbl_1_bss_11F30;
        if (var_r23 == 5 && (var_r31->unk_16 == 0 || var_r31->unk_16 == 5)) {
            var_r31->unk_00_field1 = 1;
            object->func = fn_1_3C20;
            return;
        }
    }
    else {
        return;
    }
    var_r22 = lbl_1_bss_11F30;
    if (var_r22 < 4) {
        return;
    }
    switch (var_r31->unk_16) {
        case 0:
            if (GWPlayerCfg[var_r31->unk_02].iscom == 0) {
                var_r31->unk_06 = HuPadStkX[var_r31->unk_04];
                var_r31->unk_07 = HuPadStkY[var_r31->unk_04];
                var_r31->unk_08 = HuPadBtn[var_r31->unk_04];
                var_r31->unk_0A = HuPadBtnDown[var_r31->unk_04];
            }
            else {
                var_r31->unk_08 = var_r31->unk_0A = 0;
                var_r31->unk_06 = var_r31->unk_07 = 0;
                fn_1_2010(object);
            }
            var_f31 = var_r31->unk_06;
            var_f30 = -(float)var_r31->unk_07;
            var_f27 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
            if (var_f27 > 0.0f) {
                var_f31 /= var_f27;
                var_f30 /= var_f27;
                if (var_f27 > 72.0f) {
                    var_f27 = 72.0f;
                }
                var_f26 = (10.0f * var_f27) / 72.0f;
                var_r31->unk_24.x = var_f31 * var_f26;
                var_r31->unk_24.z = var_f30 * var_f26;
                var_r31->unk_1C = var_f26;
                object->rot.y = fn_1_85E8(object->rot.y, atan2d(var_r31->unk_24.x, var_r31->unk_24.z), 0.5f);
                if (var_r31->unk_1C < 7.5f) {
                    var_r29 = 1;
                    var_f28 = var_r31->unk_1C / 7.5f;
                }
                else {
                    var_r29 = 2;
                    var_f28 = var_r31->unk_1C / 10.0f;
                }
            }
            else {
                var_r31->unk_24.x = var_r31->unk_24.z = 0.0f;
                var_r29 = 0;
                var_f28 = 1.0f;
            }
            var_r28 = 0x40000001;
            object->trans.x += var_r31->unk_24.x;
            object->trans.z += var_r31->unk_24.z;
            fn_1_37B8(object);
            fn_1_3658(object);
            fn_1_35AC(object);
            var_r31->unk_48 = fn_1_31FC(object);
            if (var_r31->unk_0A & 0x100) {
                if (var_r31->unk_48 < 0) {
                    spC.x = object->trans.x + (140.0 * sind(object->rot.y));
                    spC.y = object->trans.y;
                    spC.z = object->trans.z + (140.0 * cosd(object->rot.y));
                }
                else {
                    spC = lbl_1_bss_C9F8[var_r31->unk_48].unk_00;
                }
                Hu3DModelAttrSet(object->model[3], 1);
                if ((fn_1_3AE4(object, &spC) == 1)
                    && ((var_r31->unk_48 >= 0
                            && ((lbl_1_bss_C9F8[var_r31->unk_48].unk_10 == object) || (lbl_1_bss_C9F8[var_r31->unk_48].unk_10 == NULL)))
                        || (var_r31->unk_48 < 0))) {
                    var_r31->unk_16 = 1;
                    var_r31->unk_3C = var_r31->unk_3E = 60;
                    if (var_r31->unk_48 >= 0) {
                        lbl_1_bss_C9F8[var_r31->unk_48].unk_10 = object;
                    }
                }
                else {
                    var_r31->unk_16 = 2;
                    var_r31->unk_3C = var_r31->unk_3E = 24;
                    var_r31->unk_00_field2 = 1;
                }
            }
            break;
        case 1:
            if (var_r31->unk_3C == (var_r31->unk_3E - 8)) {
                Hu3DMotionOverlayReset(object->model[0]);
            }
            if (var_r31->unk_3C == (var_r31->unk_3E / 2)) {
                if (var_r31->unk_48 < 0) {
                    if (var_r31->unk_00_field0) {
                        spC.x = object->trans.x + (140.0 * sind(object->rot.y));
                        spC.y = object->trans.y;
                        spC.z = object->trans.z + 140.0 * cosd(object->rot.y);
                        var_r31->unk_48 = fn_1_5918(&spC);
                        lbl_1_bss_C9F8[var_r31->unk_48].unk_10 = object;
                    }
                    else {
                        var_r31->unk_00_field2 = 1;
                    }
                }
                if ((var_r31->unk_48 >= 0) && (lbl_1_bss_C9F8[var_r31->unk_48].unk_0C < 3)) {
                    lbl_1_bss_C9F8[var_r31->unk_48].unk_0C += 1;
                    lbl_1_bss_C9F8[var_r31->unk_48].unk_0E = 120;
                    HuAudFXPlay(0x71C);
                    if (lbl_1_bss_C9F8[var_r31->unk_48].unk_0C == 3) {
                        var_r31->unk_00_field2 = 1;
                        if (var_r31->unk_5C >= 0) {
                            fn_1_7734(var_r31->unk_5C, var_r31->unk_48);
                        }
                    }
                    var_r26 = Hu3DData[object->model[2]].unk_120;
                    *(s16 *)var_r26 = 0;
                    (void)var_r26;
                    Hu3DModelAttrReset(object->model[2], 1);
                    Hu3DModelPosSet(object->model[2], object->trans.x + (140.0 * sind(object->rot.y)), object->trans.y,
                        object->trans.z + (140.0 * cosd(object->rot.y)));
                }
            }
            var_r29 = 8;
            var_f28 = 1.0f;
            var_r28 = 0;
            object->trans.x += 0.2f * (var_r31->unk_4C - object->trans.x);
            object->trans.z += 0.2f * (var_r31->unk_54 - object->trans.z);
            object->rot.y = fn_1_85E8(object->rot.y, var_r31->unk_58, 0.2f);
            if (--var_r31->unk_3C == 0) {
                var_r31->unk_16 = 0;
                Hu3DMotionOverlaySet(object->model[0], object->motion[7]);
            }
            break;
        case 2:
            if (var_r31->unk_3C == (var_r31->unk_3E - 8)) {
                Hu3DMotionOverlayReset(object->model[0]);
            }
            var_r29 = 8;
            var_f28 = var_r31->unk_3C < (var_r31->unk_3E / 2) ? 0.0f : 1.0f;
            var_r28 = 0;
            object->trans.x += 0.2f * (var_r31->unk_4C - object->trans.x);
            object->trans.z += 0.2f * (var_r31->unk_54 - object->trans.z);
            object->rot.y = fn_1_85E8(object->rot.y, var_r31->unk_58, 0.2f);
            if (--var_r31->unk_3C == 0) {
                var_r31->unk_16 = 0;
                Hu3DMotionOverlaySet(object->model[0], object->motion[7]);
            }
            break;
    }
    if (var_r31->unk_5C >= 0 && (var_r31->unk_48 < 0 || (var_r31->unk_48 >= 0 && lbl_1_bss_C9F8[var_r31->unk_48].unk_0C < 3))) {
        var_r25 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
        var_r24 = var_r25[var_r31->unk_5C]->data;
        var_r27 = var_r24->unk_14;
    }
    else {
        var_r27 = -1;
    }
    if (var_r27 != var_r31->unk_40) {
        var_r31->unk_40 = var_r27;
        if (var_r27 < 0) {
            var_r31->unk_42 = 0;
        }
    }
    if (var_r31->unk_40 >= 0) {
        if (var_r31->unk_0C == 0) {
            Hu3DModelAttrReset(object->model[3], 1);
        }
        switch (var_r31->unk_40) {
            case 0:
                var_r31->unk_44 = 0.75 + sind(((90.0f * (var_r31->unk_42 % 15)) / 15.0f));
                if ((var_r31->unk_42 % 20) == 0) {
                    omVibrate(var_r31->unk_02, 0xC, 0xC, 0);
                }
                break;
            case 1:
                var_r31->unk_44 = 0.75 + (0.75 * sind(((90.0f * (var_r31->unk_42 % 30)) / 30.0f)));
                if ((var_r31->unk_42 % 20) == 0) {
                    omVibrate(var_r31->unk_02, 0xC, 4, 2);
                }
                break;
            case 2:
                var_r31->unk_44 = 0.75 + (0.5 * sind(((90.0f * (var_r31->unk_42 % 60)) / 60.0f)));
                if ((var_r31->unk_42 % 20) == 0) {
                    omVibrate(var_r31->unk_02, 12, 6, 6);
                }
                break;
        }
        var_r31->unk_42++;
    }
    else {
        Hu3DModelAttrSet(object->model[3], 1);
    }
    Hu3DModelPosSet(object->model[3], object->trans.x, 300.0f + object->trans.y, object->trans.z);
    if ((var_r29 >= 0 && var_r29 != var_r31->unk_30) || var_r28 != var_r31->unk_34) {
        var_r31->unk_30 = var_r29;
        var_r31->unk_34 = var_r28;
        CharModelMotionShiftSet(var_r31->unk_10, object->motion[var_r31->unk_30], 0.0f, 8.0f, var_r28);
    }
    var_r31->unk_38 = var_f28;
    CharModelMotionSpeedSet(var_r31->unk_10, var_f28);
}

s16 fn_1_31FC(omObjData *object)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;

    M442MainWork *var_r31;
    s32 var_r29;
    s32 var_r28;
    M442StructBssC9F8 *var_r27;
    s32 var_r26;

    var_r29 = -1;
    var_r26 = 0;
    var_f30 = 50.0f;
    var_r31 = object->data;
    sp8.x = sind(object->rot.y);
    sp8.y = 0.0f;
    sp8.z = cosd(object->rot.y);
    sp20.x = object->trans.x + (140.0f * sp8.x);
    sp20.y = object->trans.y;
    sp20.z = object->trans.z + (140.0f * sp8.z);
    if (sp20.x >= -800.0f && sp20.x < 800.0f && sp20.z >= -800.0f && sp20.z < 800.0f) {
        for (var_r27 = lbl_1_bss_C9F8, var_r28 = 0; var_r28 < lbl_1_bss_119F8; var_r28++, var_r27++) {
            VECSubtract(&var_r27->unk_00, &sp20, &sp14);
            var_f31 = VECMag(&sp14);
            VECSubtract(&var_r27->unk_00, &object->trans, &sp14);
            VECNormalize(&sp14, &sp14);
            var_f29 = VECDotProduct(&sp14, &sp8);
            if (var_f31 < var_f30 && var_f29 >= 0.0f) {
                var_f30 = var_f31;
                var_r29 = var_r28;
            }
        }
    }
    else {
        var_r26 = 1;
    }
    if (var_r29 >= 0 && lbl_1_bss_C9F8[var_r29].unk_0C < 3) {
        VECSubtract(&object->trans, &lbl_1_bss_C9F8[var_r29].unk_00, &sp14);
        VECNormalize(&sp14, &sp14);
        var_r31->unk_4C = (140.0f * sp14.x) + lbl_1_bss_C9F8[var_r29].unk_00.x;
        var_r31->unk_50 = 0.0f;
        var_r31->unk_54 = (140.0f * sp14.z) + lbl_1_bss_C9F8[var_r29].unk_00.z;
        var_r31->unk_58 = atan2d(-sp14.x, -sp14.z);
        var_r31->unk_5C = fn_1_75DC(&lbl_1_bss_C9F8[var_r29].unk_00);
    }
    else {
        var_r31->unk_4C = object->trans.x;
        var_r31->unk_50 = object->trans.y;
        var_r31->unk_54 = object->trans.z;
        var_r31->unk_58 = object->rot.y;
        var_r31->unk_5C = fn_1_75DC(&sp20);
        var_r31->unk_00_field0 = 0;
        if (var_r29 < 0 && var_r26 == 0) {
            var_r31->unk_00_field0 = 1;
        }
    }
    return var_r29;
}

void fn_1_35AC(omObjData *object)
{
    if (object->trans.x < -800.0f) {
        object->trans.x = -800.0f;
    }
    else if (object->trans.x > 800.0f) {
        object->trans.x = 800.0f;
    }
    if (object->trans.z < -800.0f) {
        object->trans.z = -800.0f;
        return;
    }
    if (object->trans.z > 800.0f) {
        object->trans.z = 800.0f;
    }
}

void fn_1_3658(omObjData *object)
{
    Vec spC;
    M442MainWork *sp8;

    float var_f31;
    float var_f30;

    s32 var_r30;
    omObjData **var_r29;
    M442MainWork *var_r28;

    sp8 = object->data;
    var_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
    for (var_r30 = 0; var_r30 < 15; var_r30++) {
        var_r28 = var_r29[var_r30]->data;
        if (var_r28->unk_00_field0) {
            VECSubtract(&object->trans, &var_r29[var_r30]->trans, &spC);
            var_f31 = VECMag(&spC);
            if (var_f31 < 70.0f) {
                var_f30 = 70.0f - var_f31;
                if (var_f31 != 0.0f) {
                    VECNormalize(&spC, &spC);
                }
                else {
                    spC.x = 0.0f;
                    spC.z = 1.0f;
                }
                object->trans.x += spC.x * var_f30;
                object->trans.z += spC.z * var_f30;
            }
        }
    }
}

void fn_1_37B8(omObjData *object)
{
    Vec sp10;
    void *spC;
    void *sp8;

    float var_f30;
    float var_f31;

    s32 var_r30;
    omObjData *var_r29;
    omObjData **var_r28;

    spC = object->data;
    var_r28 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    for (var_r30 = 0; var_r30 < 1; var_r30++) {
        var_r29 = var_r28[var_r30];
        if (object != var_r29) {
            sp8 = var_r29->data;
            VECSubtract(&object->trans, &var_r29->trans, &sp10);
            var_f31 = VECMag(&sp10);
            if (var_f31 < 100.0f) {
                var_f30 = 100.0f - var_f31;
                if (var_f31 != 0.0f) {
                    VECNormalize(&sp10, &sp10);
                }
                else {
                    sp10.x = 0.0f;
                    sp10.z = 1.0f;
                }
                object->trans.x += sp10.x * var_f30;
                object->trans.z += sp10.z * var_f30;
            }
        }
    }
}

void fn_1_3908(omObjData *object)
{
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;

    omObjData *var_r31;
    s32 var_r29;
    omObjData **var_r28;
    M442MainWork *var_r27;
    M442MainWork *var_r26;

    var_r27 = object->data;
    var_r28 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    for (var_r29 = 0; var_r29 < 1; var_r29++) {
        var_r31 = var_r28[var_r29];
        if (object != var_r31) {
            var_r26 = var_r31->data;
            VECSubtract(&object->trans, &var_r31->trans, &sp8);
            var_f27 = VECMag(&sp8);
            if (var_f27 < 100.0f) {
                var_f31 = 100.0f - var_f27;
                var_f29 = VECMag(&var_r27->unk_24);
                var_f26 = VECMag(&var_r26->unk_24);
                if (var_f29 + var_f26 == 0.0f) {
                    var_f30 = var_f28 = 0.5f;
                }
                else {
                    var_f30 = var_f29 / (var_f29 + var_f26);
                    var_f28 = 1.0f - var_f30;
                }
                VECNormalize(&sp8, &sp8);
                object->trans.x += var_f28 * (sp8.x * var_f31);
                object->trans.z += var_f28 * (sp8.z * var_f31);
                var_r31->trans.x += var_f30 * (-sp8.x * var_f31);
                var_r31->trans.z += var_f30 * (-sp8.z * var_f31);
            }
        }
    }
}

s32 fn_1_3AE4(omObjData *object, Vec *arg1)
{
    Vec sp18;
    Vec spC;
    void *sp8;

    float var_f30;
    float var_f31;

    s32 var_r31;
    omObjData **var_r30;
    s32 var_r28;

    sp8 = object->data;
    VECSubtract(arg1, &object->trans, &spC);
    VECNormalize(&spC, &spC);
    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    var_r28 = 1;
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        if (object != var_r30[var_r31]) {
            VECSubtract(&var_r30[var_r31]->trans, arg1, &sp18);
            var_f30 = VECMag(&sp18);
            VECSubtract(&var_r30[var_r31]->trans, &object->trans, &sp18);
            VECNormalize(&sp18, &sp18);
            var_f31 = VECDotProduct(&sp18, &spC);
            if (var_f31 >= 0.0f && var_f30 < 80.0f) {
                var_r28 = 0;
            }
        }
    }
    (void)var_f31;
    return var_r28;
}

void fn_1_3C20(omObjData *object)
{
    M442MainWork *var_r30;

    var_r30 = object->data;
    Hu3DMotionOverlayReset(object->model[0]);
    Hu3DModelAttrSet(object->model[1], 1);
    Hu3DModelAttrSet(object->model[3], 1);
    var_r30->unk_3C = 10;
    object->func = fn_1_3C94;
}

void fn_1_3C94(omObjData *object)
{
    float var_f31;

    M442MainWork *var_r31;
    s32 var_r29;
    u32 var_r28;
    s32 var_r27;

    var_r31 = object->data;
    var_r29 = var_r31->unk_30;
    var_r28 = var_r31->unk_34;
    var_f31 = var_r31->unk_38;
    var_r27 = lbl_1_bss_11F30;
    if (var_r27 < 11) {
        var_r29 = 0;
        var_f31 = 1.0f;
        var_r28 = 0x40000001;
    }
    else {
        object->rot.y = fn_1_85E8(object->rot.y, 0.0f, 0.2f);
        if (lbl_1_bss_11EE8 != 0) {
            var_r29 = 5;
            var_f31 = 1.0f;
            var_r28 = 0;
            if (var_r31->unk_3C != 0) {
                if (--var_r31->unk_3C == 0) {
                    HuAudCharVoicePlay(var_r31->unk_10, 0x125);
                }
            }
        }
        else {
            var_r29 = 6;
            var_f31 = 1.0f;
            var_r28 = 0;
        }
    }
    if ((var_r29 >= 0 && var_r29 != var_r31->unk_30) || var_r28 != var_r31->unk_34) {
        var_r31->unk_30 = var_r29;
        var_r31->unk_34 = var_r28;
        CharModelMotionShiftSet(var_r31->unk_10, object->motion[var_r31->unk_30], 0.0f, 8.0f, var_r28);
    }
    var_r31->unk_38 = var_f31;
    CharModelMotionSpeedSet(var_r31->unk_10, var_f31);
}

void fn_1_3E14(omObjData *object)
{
    void *sp8;

    sp8 = object->data;
    if (object->data != NULL) {
        HuMemDirectFree(object->data);
        object->data = NULL;
    }
}

void fn_1_3E64(Process *arg0)
{
    omMakeGroupEx(arg0, 1, 1);
    omAddObjEx(arg0, 10, 6, 0, 1, fn_1_3EC0);
}

void fn_1_3EBC(void) { }

u16 lbl_1_data_18A[2][5] = {
    { 0x280, 0x1E0, 0x280, 0x1E0, 0 },
    { 0x280, 0x1E0, 0x280, 0x1E0, 0 },
};

s32 lbl_1_data_1A0[3] = { 0x490007, 0x490008, 0x490009 };

void fn_1_3EC0(omObjData *object)
{
    s32 var_r31;
    s16 var_r29;
    ParticleData *var_r28;

    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M442, 0));
    Hu3DModelLayerSet(object->model[0], 1);
    Hu3DModelShadowMapObjSet(object->model[0], "oasis-grid4");
    object->model[1] = Hu3DParticleCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M442, 12), MEMORY_DEFAULT_NUM)), 1);
    Hu3DModelLayerSet(object->model[1], 7);
    Hu3DParticleHookSet(object->model[1], fn_1_64B4);
    var_r28 = Hu3DData[object->model[1]].unk_120;
    object->model[2] = Hu3DParticleCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M442, 13), MEMORY_DEFAULT_NUM)), 20);
    Hu3DModelLayerSet(object->model[2], 7);
    var_r28->unk_1C = Hu3DData[object->model[2]].unk_120;
    var_r29 = espEntry(0x49000E, 0x8000, 0);
    espPosSet(var_r29, 288.0, 240.0);
    espScaleSet(var_r29, 80.0, 60.0);
    espColorSet(var_r29, 0xFF, 0xFF, 0xFF);
    var_r28->unk_02 = var_r29;
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_C05C[var_r31].unk_04 = lbl_1_data_18A[var_r31][0];
        lbl_1_bss_C05C[var_r31].unk_06 = lbl_1_data_18A[var_r31][1];
        lbl_1_bss_C05C[var_r31].unk_08 = lbl_1_data_18A[var_r31][2];
        lbl_1_bss_C05C[var_r31].unk_0A = lbl_1_data_18A[var_r31][3];
        lbl_1_bss_C05C[var_r31].unk_10 = lbl_1_data_18A[var_r31][4];
        lbl_1_bss_C05C[var_r31].unk_0C = GXGetTexBufferSize(lbl_1_bss_C05C[var_r31].unk_08, lbl_1_bss_C05C[var_r31].unk_0A, 4, GX_FALSE, 0);
        lbl_1_bss_C05C[var_r31].unk_00 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_C05C[var_r31].unk_0C, MEMORY_DEFAULT_NUM);
        memset(lbl_1_bss_C05C[var_r31].unk_00, 0, lbl_1_bss_C05C[var_r31].unk_0C);
    }
    for (var_r31 = 0; var_r31 < 1024; var_r31++) {
        fn_1_4444(var_r31);
    }
    object->model[3] = Hu3DHookFuncCreate(fn_1_485C);
    lbl_1_bss_11F10 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M442, 0x0B));
    object->model[4] = Hu3DHookFuncCreate(fn_1_54C8);
    Hu3DModelLayerSet(object->model[4], 6);
    for (var_r31 = 0; var_r31 < 15; var_r31++) {
        lbl_1_bss_20[var_r31] = ((float)(frand() & 0xFF)) / 256;
    }
    memset(lbl_1_bss_119FC, 0, 0x271);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_11F04[var_r31] = HuSprAnimReadFile(lbl_1_data_1A0[var_r31]);
    }
    object->model[5] = Hu3DHookFuncCreate(fn_1_5A48);
    Hu3DModelLayerSet(object->model[5], 2);
    object->func = fn_1_4364;
}

void fn_1_4364(omObjData *object) { }

void fn_1_4368(u8 arg0, u8 arg1, Vec *arg2)
{
    arg2->x = (66.666664f * (arg0 - 12)) + (33.333332f * (arg1 & 1));
    arg2->y = 0.0f;
    arg2->z = 66.666664f * (arg1 - 12);
}

void fn_1_4444(s32 arg0)
{
    lbl_1_bss_5C[arg0].unk_00 = 100.0f * (18.0f * ((frand() & 0x1FF) - 256.0f)) / 256;
    lbl_1_bss_5C[arg0].unk_04 = 0.0f;
    lbl_1_bss_5C[arg0].unk_08 = 100.0f * (18.0f * ((frand() & 0x1FF) - 256.0f)) / 256;
    lbl_1_bss_5C[arg0].unk_0C = lbl_1_bss_5C[arg0].unk_00;
    lbl_1_bss_5C[arg0].unk_10 = 0.41666666f + (1.6666666f * (frand() & 0xFF) / 256);
    lbl_1_bss_5C[arg0].unk_18 = lbl_1_bss_5C[arg0].unk_1A = (frand() & 0x3F) + 0x20;
    lbl_1_bss_5C[arg0].unk_1C = 0.1f + (0.9f * (frand() & 0xFF) / 256);
    lbl_1_bss_5C[arg0].unk_20 = 360.0f * (frand() & 0xFF) / 256;
    lbl_1_bss_5C[arg0].unk_24 = 4.0f * (frand() & 0xFF) / 256;
    lbl_1_bss_5C[arg0].unk_28 = 100.0f * (frand() & 0xFF) / 256;
    lbl_1_bss_5C[arg0].unk_2C = 1.0f + (3.0f * (frand() & 0xFF) / 256);
}

GXColor lbl_1_data_1B8 = { 0xFF, 0xFF, 0xFF, 0x20 };

GXColor lbl_1_data_1BC = { 0x00, 0x7E, 0x7E, 0xFF };

Vec lbl_1_data_1C0[4] = {
    { -1.0f, 1.0f, 0.0f },
    { 1.0f, 1.0f, 0.0f },
    { 1.0f, -1.0f, 0.0f },
    { -1.0f, -1.0f, 0.0f },
};

void fn_1_485C(ModelData *model, Mtx mtx)
{
    Mtx sp100;
    Mtx spD0;
    Mtx spA0;
    ROMtx sp70;
    Mtx sp40;
    Vec sp34; // ! - uninitialized
    Vec sp28; // ! - uninitialized
    Vec sp1C; // ! - uninitialized
    Vec sp10;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f20;
    float var_f19;

    M442StructBss5C *var_r31;
    s32 var_r30;
    CameraData *var_r29;
    u16 var_r28;
    u16 var_r27;
    u16 var_r26;
    u16 var_r25;

    var_r29 = Hu3DCamera;
    C_MTXOrtho(sp100, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 100.0f);
    GXSetProjection(sp100, GX_ORTHOGRAPHIC);
    PSMTXIdentity(spD0);
    GXLoadPosMtxImm(spD0, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_1BC);
    GXSetNumTexGens(0);
    HuSprTexLoad(lbl_1_bss_11F10, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetScissor(0, 0, lbl_1_bss_C05C[0].unk_08, lbl_1_bss_C05C[0].unk_0A);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2u16(0, 0);
    GXPosition2u16(lbl_1_bss_C05C[0].unk_08, 0);
    GXPosition2u16(lbl_1_bss_C05C[0].unk_08, lbl_1_bss_C05C[0].unk_0A);
    GXPosition2u16(0, lbl_1_bss_C05C[0].unk_0A);
    GXDrawDone();
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    C_MTXPerspective(sp40, var_r29->fov, var_r29->aspect, var_r29->near, var_r29->far);
    GXSetProjection(sp40, GX_PERSPECTIVE);
    PSMTXInverse(mtx, spA0);
    spA0[0][3] = spA0[1][3] = spA0[2][3] = 0.0f;
    PSMTXReorder(spA0, sp70);
    PSMTXROMultVecArray(sp70, &lbl_1_data_1C0[0], &sp10, 4);
    GXLoadPosMtxImm(mtx, 0);
    var_r31 = lbl_1_bss_5C;
    for (var_r30 = 0; var_r30 < 1024; var_r30++, var_r31++) {
        var_f31 = 50.0f * var_r31->unk_1C;
        lbl_1_data_1B8.a = 255.0 * sind(((180.0f * var_r31->unk_18) / var_r31->unk_1A));
        GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_1B8);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(
            var_r31->unk_00 + (var_r31->unk_2C * (sp10.x * var_f31)), var_r31->unk_04 + (sp10.y * var_f31), var_r31->unk_08 + (sp10.z * var_f31));
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(
            var_r31->unk_00 + (var_r31->unk_2C * (sp1C.x * var_f31)), var_r31->unk_04 + (sp1C.y * var_f31), var_r31->unk_08 + (sp1C.z * var_f31));
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(
            var_r31->unk_00 + (var_r31->unk_2C * (sp28.x * var_f31)), var_r31->unk_04 + (sp28.y * var_f31), var_r31->unk_08 + (sp28.z * var_f31));
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(
            var_r31->unk_00 + (var_r31->unk_2C * (sp34.x * var_f31)), var_r31->unk_04 + (sp34.y * var_f31), var_r31->unk_08 + (sp34.z * var_f31));
        GXTexCoord2f32(0.0f, 1.0f);
        var_r31->unk_20 += var_r31->unk_24;
        var_r31->unk_00 = var_r31->unk_0C + (var_r31->unk_28 * sind(var_r31->unk_20));
        var_r31->unk_04 += var_r31->unk_10;
        if (--var_r31->unk_18 == 0) {
            fn_1_4444(var_r30);
        }
    }
    GXDrawDone();
    fn_1_8520(&lbl_1_bss_C05C[0], 1);
}

GXColor lbl_1_data_1F0 = { 0xFF, 0xFF, 0xFF, 0x40 };

float lbl_1_data_1F4[2][3] = {
    { 0.0f, 0.0f, 0.025f },
    { 0.0f, 0.025f, 0.0f },
};

GXColor lbl_1_data_20C[3] = {
    { 0xFF, 0x00, 0x00, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0x40 },
    { 0xFF, 0x00, 0x00, 0xFF },
};

void fn_1_54C8(ModelData *model, Mtx mtx)
{
    Mtx sp5C;
    Mtx sp2C;
    GXTexObj spC;

    fn_1_8520(&lbl_1_bss_C05C[1], 0);
    C_MTXOrtho(sp5C, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 100.0f);
    GXSetProjection(sp5C, GX_ORTHOGRAPHIC);
    PSMTXIdentity(sp2C);
    GXLoadPosMtxImm(sp2C, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumTexGens(2);
    GXInitTexObj(&spC, lbl_1_bss_C05C[1].unk_00, lbl_1_bss_C05C[1].unk_08, lbl_1_bss_C05C[1].unk_0A, 4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&spC, GX_TEXMAP0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColor(GX_TEVREG0, lbl_1_data_1F0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXInitTexObj(&spC, lbl_1_bss_C05C->unk_00, lbl_1_bss_C05C->unk_08, lbl_1_bss_C05C->unk_0A, 4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&spC, GX_TEXMAP1);
    GXSetNumIndStages(1);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_0, lbl_1_data_1F4, 0);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetCullMode(GX_CULL_BACK);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2u16(0, 0);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition2u16(640, 0);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition2u16(640, 480);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition2u16(0, 480);
    GXTexCoord2f32(0.0f, 1.0f);

    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
}

s16 fn_1_5918(Vec *arg0)
{
    s32 var_r30;
    M442StructBssC9F8 *var_r31;

    var_r30 = lbl_1_bss_119F8;
    var_r31 = &lbl_1_bss_C9F8[lbl_1_bss_119F8];
    var_r31->unk_00.x = arg0->x;
    var_r31->unk_00.y = arg0->y;
    var_r31->unk_00.z = arg0->z;
    var_r31->unk_0C = 0;
    var_r31->unk_0E = 0;
    var_r31->unk_10 = NULL;
    lbl_1_bss_119F8 = (lbl_1_bss_119F8 + 1) % 1024;
    return var_r30;
}

s32 fn_1_59C0(Vec *arg0)
{
    Vec spC;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < lbl_1_bss_119F8; var_r31++) {
        VECSubtract(&lbl_1_bss_C9F8[var_r31].unk_00, arg0, &spC);
        if (VECMag(&spC) < 50.0f) {
            return var_r31;
        }
    }
}

void fn_1_5A48(ModelData *arg0, Mtx arg1)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;

    M442StructBssC9F8 *var_r31;
    s32 var_r30;

    GXLoadPosMtxImm(arg1, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetNumTexGens(1);
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        HuSprTexLoad(lbl_1_bss_11F04[var_r30], 0, var_r30, GX_REPEAT, GX_REPEAT, GX_LINEAR); // TODO
    }
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetCullMode(GX_CULL_BACK);
    var_r31 = lbl_1_bss_C9F8;
    for (var_r30 = 0; var_r30 < lbl_1_bss_119F8; var_r30++, var_r31++) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, var_r31->unk_0C - 1, GX_COLOR0A0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(var_r31->unk_00.x - 50.0f, 1.0f, var_r31->unk_00.z - 50.0f);
        GXTexCoord2f32(0.0f, 0.0f);

        GXPosition3f32(50.0f + var_r31->unk_00.x, 1.0f, var_r31->unk_00.z - 50.0f);
        GXTexCoord2f32(1.0f, 0.0f);

        GXPosition3f32(50.0f + var_r31->unk_00.x, 1.0f, 50.0f + var_r31->unk_00.z);
        GXTexCoord2f32(1.0f, 1.0f);

        GXPosition3f32(var_r31->unk_00.x - 50.0f, 1.0f, 50.0f + var_r31->unk_00.z);
        GXTexCoord2f32(0.0f, 1.0f);

        if (var_r31->unk_0E != 0) {
            if (--var_r31->unk_0E == 0) {
                var_r31->unk_10 = NULL;
            }
        }
    }
}

GXColor lbl_1_data_218 = { 0xFF, 0xFF, 0xFF, 0x80 };

void fn_1_5EDC(ModelData *model, float (*mtx)[4])
{
    float sp38;
    float sp28;
    Mtx spC;

    M442MainWork *var_r31;
    s32 var_r30;

    var_r31 = model->unk_120;
    PSMTXInverse(mtx, spC);
    spC[0][3] = spC[1][3] = spC[2][3] = 0.0f;
    PSMTXConcat(mtx, &spC[0], mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetNumTexGens(1);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        HuSprTexLoad(lbl_1_bss_11EEC[var_r30], 0, var_r30, GX_CLAMP, GX_CLAMP, GX_LINEAR); // TODO
    }
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_218);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(-80.0f, 80.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);

    GXPosition3f32(80.0f, 80.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);

    GXPosition3f32(80.0f, -80.0f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);

    GXPosition3f32(-80.0f, -80.0f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, var_r31->unk_40 + 1, GX_COLOR0A0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    mtxScaleCat(mtx, var_r31->unk_44, var_r31->unk_44, var_r31->unk_44);
    GXLoadPosMtxImm(mtx, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(-80.0f, 80.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);

    GXPosition3f32(80.0f, 80.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);

    GXPosition3f32(80.0f, -80.0f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);

    GXPosition3f32(-80.0f, -80.0f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
}

void fn_1_64B4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;

    HsfanimStruct01 *var_r31;
    ParticleData *var_r29;
    s32 var_r28;

    var_r29 = particle->unk_1C;
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    if (particle->unk_00 == 0) {
        particle->unk_00 = 1;
        var_r31 = particle->unk_48;
        for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
            var_r31->unk2C = 2000.0f;
            var_r31->unk08.x = 20.0f;
            var_r31->unk08.y = 100.0f;
            var_r31->unk08.z = 0.0f;
            VECNormalize(&var_r31->unk08, &var_r31->unk08);
            var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = var_r31->unk40.a = 0xFF;
        }
        var_r31 = var_r29->unk_48;
        for (var_r28 = 0; var_r28 < var_r29->unk_30; var_r28++, var_r31++) {
            var_r31->unk2C = 50.0f + 500.0f * (frand() & 0xFF) / 256;
            var_r31->unk40.r = (frand() & 0x3F) + 0xC0;
            var_r31->unk40.g = (frand() & 0x3F) + 0xC0;
            var_r31->unk40.b = (frand() & 0x3F) + 0xC0;
            var_r31->unk40.a = 0x40;
            var_r31->unk08.x = (frand() & 0xFF) / 4096.0f;
        }
    }
    sp14.x = sind(CRot.y) * cosd(CRot.x);
    sp14.y = -sind(CRot.x);
    sp14.z = cosd(CRot.y) * cosd(CRot.x);
    sp38.x = Center.x + (sp14.x * CZoom);
    sp38.y = Center.y + (sp14.y * CZoom);
    sp38.z = Center.z + (sp14.z * CZoom);

    var_r31 = particle->unk_48;
    sp2C.x = sp38.x + (2500.0f * var_r31->unk08.x);
    sp2C.y = sp38.y + (2500.0f * var_r31->unk08.y);
    sp2C.z = sp38.z + (2500.0f * var_r31->unk08.z);

    var_r31->unk30 += 0.0034906585560035243;
    var_r31->unk34 = sp2C;
    DCStoreRangeNoSync(particle->unk_48, particle->unk_30 * 0x44);
    var_f29 = (var_r31->unk08.z * -sp14.z) + ((var_r31->unk08.x * -sp14.x) + (var_r31->unk08.y * -sp14.y));

    sp8.x = -var_r31->unk08.x + (2.0f * -sp14.x * var_f29);
    sp8.y = -var_r31->unk08.y + (2.0f * -sp14.y * var_f29);
    sp8.z = -var_r31->unk08.z + (2.0f * -sp14.z * var_f29);
    sp20.x = sp38.x + (2500.0f * sp8.x);
    sp20.y = sp38.y + (2500.0f * sp8.y);
    sp20.z = sp38.z + (2500.0f * sp8.z);
    var_f31 = -VECDotProduct(&var_r31->unk08, &sp14);
    if (var_f31 >= 0.0f) {
        espTPLvlSet(particle->unk_02, 0.5f * var_f31 * var_f31);
    }
    else {
        espTPLvlSet(particle->unk_02, 0.0);
    }
    var_r31 = var_r29->unk_48;
    for (var_r28 = 0; var_r28 < var_r29->unk_30; var_r28++, var_r31++) {
        var_f30 = var_r31->unk08.x + ((float)(var_r28 - 2) / (var_r29->unk_30 - 2));
        var_r31->unk34.x = sp2C.x + (var_f30 * (sp20.x - sp2C.x));
        var_r31->unk34.y = sp2C.y + (var_f30 * (sp20.y - sp2C.y));
        var_r31->unk34.z = sp2C.z + (var_f30 * (sp20.z - sp2C.z));
        if (var_f31 >= 0.0f) {
            var_r31->unk40.a = 64.0f * (var_f31 * var_f31);
        }
    }
    DCStoreRangeNoSync(var_r29->unk_48, var_r29->unk_30 * 0x44);
}

void fn_1_6BB4(Process *arg0)
{
    s32 var_r31;
    s32 var_r30;

    lbl_1_bss_11EE4 = 15;
    lbl_1_bss_11EE0 = 0;
    omMakeGroupEx(arg0, 2, 15);
    for (var_r31 = 0; var_r31 < 15; var_r31++) {
        omAddObjEx(arg0, 10, 2, 0, 2, fn_1_6D24);
    }
    memset(lbl_1_bss_11C6D, 0, 0x271);
    for (var_r31 = 9; var_r31 < 16; var_r31++) {
        for (var_r30 = 9; var_r30 < 16; var_r30++) {
            *(lbl_1_bss_11C6D + (var_r31 * 0x19) + var_r30) = 1;
        }
    }
    lbl_1_bss_11EFC = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M442, 15), MEMORY_DEFAULT_NUM));
}

void fn_1_6CC8(void)
{
    s32 var_r31;
    omObjData **var_r30;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
    for (var_r31 = 0; var_r31 < 15; var_r31++) {
        fn_1_7848(var_r30[var_r31]);
    }
}

s16 lbl_1_data_21C[16] = { 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 0 };

void fn_1_6D24(omObjData *object)
{
    s16 sp18[625][2];
    Vec spC;

    float var_f31;
    float var_f30;

    s32 var_r30;
    M442MainWork2 *var_r29;
    s32 var_r28;
    s32 var_r27;
    u8 var_r26;
    u8 var_r25;

    var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M442MainWork2), MEMORY_DEFAULT_NUM);
    object->data = var_r29;
    memset(var_r29, 0, sizeof(M442MainWork2));
    var_r29->unk_16 = lbl_1_bss_11EE0++;
    var_r29->unk_18 = 1.0f;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M442, 0x02));
    Hu3DModelLayerSet(object->model[0], 7);
    Hu3DModelAttrSet(object->model[0], 0x40000001);
    Hu3DModelAttrSet(object->model[0], 1);
    object->model[1] = Hu3DParticleCreate(lbl_1_bss_11EFC, 0x64);
    Hu3DParticleHookSet(object->model[1], fn_1_7EBC);
    Hu3DModelLayerSet(object->model[1], 7);
    Hu3DModelAttrSet(object->model[1], 1);
    for (var_r27 = 0, var_r30 = 1; var_r30 < 24; var_r30++) {
        for (var_r28 = 1; var_r28 < 24; var_r28++) {
            if (*(lbl_1_bss_11C6D + (var_r30 * 0x19) + var_r28) == 0) {
                sp18[var_r27][0] = var_r28;
                sp18[var_r27][1] = var_r30;
                var_r27++;
            }
        }
    }
    var_r30 = (var_r27 * (frand() & 0xFF)) >> 8;
    var_r26 = sp18[var_r30][1];
    var_r25 = sp18[var_r30][0];
    fn_1_4368(var_r25, var_r26, &object->trans);
    var_r29->unk_04 = sp18[var_r30][0];
    var_r29->unk_06 = sp18[var_r30][1];
    for (var_r30 = 0; var_r30 < 25; var_r30++) {
        for (var_r28 = 0; var_r28 < 25; var_r28++) {
            fn_1_4368(var_r28, var_r30, &spC);
            var_f31 = spC.x - object->trans.x;
            var_f30 = spC.z - object->trans.z;

            if (sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) < 250.0f) {
                *(lbl_1_bss_11C6D + (var_r30 * 0x19) + var_r28) = 1;
            }
        }
    }
    var_r29->unk_14 = lbl_1_data_21C[var_r29->unk_16];
    var_r29->unk_08 = 0.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    object->func = fn_1_72C4;
}

s32 lbl_1_data_23C[3] = { 0x721, 0x71E, 0x720 };

void fn_1_72C4(omObjData *object)
{
    M442MainWork2 *var_r31 = object->data;
    float sp8[3] = { 1.0f, 0.6f, 0.3f };

    switch (var_r31->unk_02) {
        case 0:
            if (var_r31->unk_00_field0) {
                Hu3DModelAttrReset(object->model[0], 1);
                Hu3DModelAttrReset(object->model[1], 1);
                var_r31->unk_02 = 1;
                var_r31->unk_18 = 0.0f;
                var_r31->unk_0C = 60;
            }
            break;
        case 1:
            if (var_r31->unk_18 < 0.3f) {
                var_r31->unk_18 += 0.05f;
            }
            var_r31->unk_02 = 2;
            var_r31->unk_0C = var_r31->unk_0E = 45;
            var_r31->unk_10 = HuAudFXPlay(lbl_1_data_23C[var_r31->unk_14]);
            break;
        case 2:
            var_r31->unk_18 = 0.30000001192092896 + (0.800000011920929 * cosd(((90.0f * var_r31->unk_0C) / var_r31->unk_0E)));
            if (--var_r31->unk_0C == 0) {
                var_r31->unk_02 = 3;
                var_r31->unk_0C = 90;
            }
            break;
        case 3:
            var_r31->unk_18 = 1.0 + (0.10000000149011612 * sind(var_r31->unk_0C));
            var_r31->unk_0C += 3;
            break;
    }
    object->scale.x = object->scale.z = sp8[var_r31->unk_14];
    object->scale.y = var_r31->unk_18 * sp8[var_r31->unk_14];
    var_r31->unk_08 = 400.0f * object->scale.y;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
}

s32 fn_1_75DC(Vec *arg0)
{
    Vec spC;
    float sp8;

    float var_f31;

    s32 var_r30;
    omObjData **var_r29;
    M442MainWork *var_r28;

    sp8 = 10000.0f;
    if ((arg0->x < -800.0f) || (arg0->x >= 800.0f) || (arg0->z < -800.0f) || (arg0->z >= 800.0f)) {
        return -1;
    }
    var_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
    for (var_r30 = 0; var_r30 < 15; var_r30++) {
        var_r28 = var_r29[var_r30]->data;
        if (var_r28->unk_00_field0 == 0) {
            VECSubtract(&var_r29[var_r30]->trans, arg0, &spC);
            var_f31 = VECMag(&spC);
            if (var_f31 < 100.0f) {
                return var_r30;
            }
        }
    }
    return -1;
}

s16 lbl_1_data_248[4] = { 0x64, 0xA, 1, 0 };

void fn_1_7734(s32 arg0, s32 arg1)
{
    omObjData *var_r31;
    M442MainWork *var_r30;
    omObjData **var_r29;

    var_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
    var_r31 = var_r29[arg0];
    var_r30 = var_r31->data;
    var_r30->unk_00_field0 = 1;
    var_r31->trans.x = lbl_1_bss_C9F8[arg1].unk_00.x;
    var_r31->trans.y = lbl_1_bss_C9F8[arg1].unk_00.y;
    var_r31->trans.z = lbl_1_bss_C9F8[arg1].unk_00.z;
    HuAudFXPlay(0x71D);
    lbl_1_bss_11EE8 += lbl_1_data_248[var_r30->unk_14];
    lbl_1_bss_11EE4--;
}

void fn_1_7848(omObjData *object)
{
    if (object->data != NULL) {
        HuMemDirectFree(object->data);
        object->data = NULL;
    }
}

void fn_1_7890(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float var_f31;
    float var_f30;

    HsfanimStruct01 *var_r31;
    s32 var_r29;
    s32 var_r28;

    if (particle->unk_00 == 0) {
        particle->unk_00 = 1;
        var_r31 = particle->unk_48;
        for (var_r29 = 0; var_r29 < particle->unk_30; var_r31++, var_r29++) {
            var_r31->unk2C = (50.0f + (20.0f * (frand() & 0xFF))) / 256;
            var_f31 = 360.0f * (frand() & 0xFF) / 256;
            var_r31->unk34.x = 100.0 * (0.20000000298023224 * sind(var_f31));
            var_r31->unk34.y = 0.0f;
            var_r31->unk34.z = 100.0 * (0.20000000298023224 * cosd(var_f31));
            var_f30 = 1.6666666f + (2.5f * (frand() & 0xFF) / 256);
            var_f31 = 360.0f * (frand() & 0xFF) / 256;
            var_r31->unk08.x = var_f30 * sind(var_f31);
            var_r31->unk08.z = var_f30 * cosd(var_f31);
            var_r31->unk08.y = 16.666666f * (frand() & 0xFF) / 256;
            var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = var_r31->unk40.a = 0xFF;
        }
    }
    var_r28 = 0;
    var_r31 = particle->unk_48;
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk34.y < -50.0f) {
            var_r28++;
        }
        else {
            var_r31->unk08.y += -0.50000006f;
            var_r31->unk34.x += var_r31->unk08.x;
            var_r31->unk34.y += var_r31->unk08.y;
            var_r31->unk34.z += var_r31->unk08.z;
        }
    }
    if (var_r28 == particle->unk_30) {
        model->attr |= 1;
    }
    DCStoreRangeNoSync(particle->unk_48, particle->unk_30 * 0x44);
}

void fn_1_7C8C(HsfanimStruct01 *arg0)
{
    float sp8;

    arg0->unk2C = 30.0f + (10.0f * (frand() & 0xFF) / 256);
    sp8 = 360.0f * (frand() & 0xFF) / 256;
    arg0->unk34.x = 0.0f;
    arg0->unk34.y = 0.0f;
    arg0->unk34.z = 0.0f;
    arg0->unk08.x = 0.0f;
    arg0->unk08.y = 0.2f + (0.8f * (frand() & 0xFF) / 256);
    arg0->unk08.z = ((frand() & 0xFF) * 0x168) >> 8;
    arg0->unk14.x = 0.5f + (0.5f * (frand() & 0xFF) / 256);
    arg0->unk40.r = 0x19;
    arg0->unk40.g = 0x13;
    arg0->unk40.b = 0x1E;
    arg0->unk40.a = 0xFF;
}

void fn_1_7EBC(ModelData *model, ParticleData *particle, Mtx matrix)
{
    s32 sp14;
    float sp10;
    float spC;
    float sp8;

    float var_f31;

    HsfanimStruct01 *var_r31;
    s32 var_r29;

    if (particle->unk_00 == 0) {
        particle->unk_00 = 1;
        var_r31 = particle->unk_48;
        sp10 = atan2d(particle->unk_04.x, particle->unk_04.z);
        for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            fn_1_7C8C(var_r31);
            var_r31->unk08.x = 30.0f * (frand() & 0xFF) / 256;
            var_r31->unk2C *= model->scale.x;
        }
    }
    sp14 = 0;
    var_r31 = particle->unk_48;
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        var_f31 = var_r31->unk08.x - 20.0f;
        var_r31->unk34.y = 400.0f + (var_f31 * (-var_r31->unk08.y * var_f31));
        var_r31->unk34.x = 2.0 * (var_r31->unk08.x * sind(var_r31->unk08.z));
        var_r31->unk34.z = 2.0 * (var_r31->unk08.x * cosd(var_r31->unk08.z));
        var_r31->unk08.x += var_r31->unk14.x;
        if (var_r31->unk08.x > 30.0f) {
            fn_1_7C8C(var_r31);
            var_r31->unk2C *= model->scale.x;
        }
    }
    DCStoreRangeNoSync(particle->unk_48, particle->unk_30 * 0x44);
}

void fn_1_8520(M442StructBssC05C *arg0, u8 arg1)
{
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);
    GXSetTexCopySrc(0, 0, arg0->unk_04, arg0->unk_06);
    GXSetTexCopyDst(arg0->unk_08, arg0->unk_0A, GX_TF_RGB565, arg0->unk_10);
    GXSetCopyClear(BGColor, 0xFFFFFF);
    GXCopyTex(arg0->unk_00, arg1);
    GXPixModeSync();
    DCFlushRange(arg0->unk_00, arg0->unk_0C);
}

float fn_1_85E8(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;

    var_f31 = fmod(arg9 - arg8, 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg8 + (argA * var_f31), 360.0);
    if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

void fn_1_86EC(omObjData *object)
{
    fn_1_8738(0, 0, 0.0f);
    object->func = fn_1_8988;
}

void fn_1_8738(s32 arg0, s32 arg1, float arg8)
{
    CZoom = lbl_1_data_0[arg0].unk_00 + (arg8 * (lbl_1_data_0[arg1].unk_00 - lbl_1_data_0[arg0].unk_00));
    Center.x = lbl_1_data_0[arg0].unk_04 + (arg8 * (lbl_1_data_0[arg1].unk_04 - lbl_1_data_0[arg0].unk_04));
    Center.y = lbl_1_data_0[arg0].unk_08 + (arg8 * (lbl_1_data_0[arg1].unk_08 - lbl_1_data_0[arg0].unk_08));
    Center.z = lbl_1_data_0[arg0].unk_0C + (arg8 * (lbl_1_data_0[arg1].unk_0C - lbl_1_data_0[arg0].unk_0C));
    CRot.x = lbl_1_data_0[arg0].unk_10 + (arg8 * (lbl_1_data_0[arg1].unk_10 - lbl_1_data_0[arg0].unk_10));
    CRot.y = lbl_1_data_0[arg0].unk_14 + (arg8 * (lbl_1_data_0[arg1].unk_14 - lbl_1_data_0[arg0].unk_14));
    CRot.z = lbl_1_data_0[arg0].unk_18 + (arg8 * (lbl_1_data_0[arg1].unk_18 - lbl_1_data_0[arg0].unk_18));
}

float lbl_1_data_250[2] = { 0.0f, 0.0f };

void fn_1_8988(omObjData *arg0)
{
    CameraData *sp8 = Hu3DCamera;
    switch (lbl_1_bss_11F30) {
        case 1:
            fn_1_8738(0, 1, sind((90.0f * lbl_1_data_250[0])));
            if (lbl_1_data_250[0] < 1.0f) {
                lbl_1_data_250[0] += 0.016666668f;
                if (lbl_1_data_250[0] > 1.0f) {
                    lbl_1_data_250[0] = 1.0f;
                    return;
                }
            }
        case 3:
        case 4:
            break;
        case 2:
            fn_1_8738(1, 2, 1.0 - cosd((90.0f * lbl_1_data_250[1])));
            if (lbl_1_data_250[1] < 1.0f) {
                lbl_1_data_250[1] += 0.016666668f;
                if (lbl_1_data_250[1] > 1.0f) {
                    lbl_1_data_250[1] = 1.0f;
                    return;
                }
            }
            break;
        case 8:
            fn_1_8738(1, 1, 0.0f);
            break;
        case 9:
            break;
        default:
            break;
    }
}

s16 fn_1_90EC(void)
{
    return lbl_1_bss_11EE8;
}

s32 lbl_1_data_258[4] = { 0x80000000, 0x40000000, 0x20000000, 0x10000000 };

s32 fn_1_90FC(void)
{
    s32 var_r31;
    u32 var_r30;

    var_r30 = HuPadRumbleGet();
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        if (GWPlayerCfg[var_r31].iscom == 0 && (var_r30 & lbl_1_data_258[GWPlayerCfg[var_r31].pad_idx]) == 0) {
            return 0;
        }
    }
    return GWGameStat.rumble;
}
