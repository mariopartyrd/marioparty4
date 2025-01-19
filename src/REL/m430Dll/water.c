#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXVert.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/flag.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

#include "REL/m430Dll.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/frand.h"

void GXSetTevIndWarp(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXBool signed_offsets, GXBool replace_mode, GXIndTexMtxID matrix_sel);
#endif

inline double fabs2(double x)
{
    return (double)fabs(x);
}

typedef struct M430DllUnkStruct2 {
    s32 unk_00;
    s16 unk_04;
    char unk06[2];
    s16 unk_08;
    s16 unk_0A;
    Vec unk_0C;
    Vec unk_18;
    float unk_24;
    float unk_28;
    float unk_2C;
    float unk_30;
    float unk_34;
    float unk_38;
} M430DllUnkStruct2; /* size 0x3C */

typedef struct M430DllWork {
    s32 unk_00;
    Vec unk_04;
    s32 unk_10;
    s32 unk_14;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    float unk_20;
    s16 unk_24[0xC];
    s32 unk_3C;
    s16 unk_40[0xA];
    s16 unk_54[0xA];
    s16 unk_68[0xA];
    s32 unk_7C;
    s16 unk_80[6];
    s16 unk_8C[6];
    s16 unk_98[6];
    s32 unk_A4[6];
    s32 unk_BC;
    M430DllUnkStruct2 *unk_C0;
} M430DllWork; /* size 0xC4 */

typedef struct M430DllWork2 {
    s16 unk_00;
    char unk02[4];
    s16 unk_06;
    Vec unk_08;
    Vec unk_14;
    float unk_20;
    float unk_24;
    float unk_28;
    float unk_2C;
    float unk_30;
    float unk_34;
    float unk_38;
    float unk_3C;
} M430DllWork2; /* size 0x40 */

typedef struct M430DllBss60Struct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ Vec *unk_2C;
    /* 0x30 */ Vec *unk_30;
    /* 0x34 */ void *unk_34;
    /* 0x38 */ void *unk_38;
    /* 0x3C */ char pad_3C[4];
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ Vec *unk_44[2];
    /* 0x4C */ char pad_4C[8];
    /* 0x54 */ GXColor *unk_54[2];
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ void *unk_60;
    /* 0x64 */ u32 unk_64;
    /* 0x68 */ u32 unk_68;
    /* 0x6C */ void *unk_6C;
} M430DllBss60Struct; /* size = 0x70 */

void fn_1_4CB4(omObjData *object);
void fn_1_5DF8(omObjData *object);
void fn_1_6180(M430DllWork *arg0);
void fn_1_6540(M430DllWork *arg0);
void fn_1_6754(M430DllWork *arg0);
void fn_1_6DC8(M430DllWork *arg0);
M430DllUnkStruct2 *fn_1_70AC(omObjData *arg0, s32 arg1, s16 arg2);
void fn_1_732C(omObjData *object, M430DllUnkStruct2 *arg1);
void fn_1_76D8(omObjData *object, M430DllUnkStruct2 *arg1);
void fn_1_7848(omObjData *object);
void fn_1_7CAC(omObjData *object);
void fn_1_7EAC(omObjData *object, M430DllWork2 *arg1);
void fn_1_803C(omObjData *object);
void fn_1_8264(omObjData *object);
void fn_1_82F4(omObjData *object, M430DllBss60Struct *arg1);
void fn_1_86B4(omObjData *object, M430DllBss60Struct *arg1);
void fn_1_8B5C(omObjData *object, M430DllBss60Struct *arg1);
void fn_1_8CE0(ModelData *model, Mtx matrix);
void fn_1_963C(ModelData *model, Mtx matrix, u32 arg2);
void fn_1_9C90(ModelData *model, Mtx matrix);
void fn_1_A3A8(ModelData *model, Mtx matrix);
void fn_1_AB98(ModelData *model, Mtx matrix);
void fn_1_AC84(ModelData *model, Mtx matrix);
void fn_1_AD04(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_B394(ModelData *model, ParticleData *particle, Mtx matrix);
float fn_1_BB54(u32 arg0);

AnimData *lbl_1_bss_150;
AnimData *lbl_1_bss_14C;
AnimData *lbl_1_bss_148;
AnimData *lbl_1_bss_144;
AnimData *lbl_1_bss_140;
M430DllBss60Struct lbl_1_bss_60[2];
s32 lbl_1_bss_5C;
omObjData *lbl_1_bss_58;
omObjData *lbl_1_bss_54;
omObjData *lbl_1_bss_50;
float lbl_1_bss_4C;
float lbl_1_bss_48;
s32 lbl_1_bss_44;
s32 lbl_1_bss_40;

void fn_1_4A80(Process *process)
{
    omObjData *object;

    lbl_1_bss_150 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M430, 0x19), MEMORY_DEFAULT_NUM));
    lbl_1_bss_14C = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M430, 0x1A), MEMORY_DEFAULT_NUM));
    lbl_1_bss_148 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M430, 0x14), MEMORY_DEFAULT_NUM));
    lbl_1_bss_144 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M430, 0x17), MEMORY_DEFAULT_NUM));
    lbl_1_bss_140 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M430, 0x18), MEMORY_DEFAULT_NUM));
    object = lbl_1_bss_58 = omAddObjEx(process, 0x1E, 0x68, 0, -1, fn_1_4CB4);
    object->work[0] = 0;
    object = lbl_1_bss_54 = omAddObjEx(process, 0x1E, 7, 0, -1, fn_1_803C);
    object->work[0] = 0;
    object = lbl_1_bss_50 = omAddObjEx(process, 0x1E, 0, 0, -1, fn_1_7848);
    object->work[0] = 0;
    lbl_1_bss_5C = 0;
    lbl_1_bss_44 = lbl_1_bss_40 = 0;
    lbl_1_bss_4C = lbl_1_bss_48 = 0.0f;
}

void fn_1_4C48(void)
{
    HuSprAnimKill(lbl_1_bss_150);
    HuSprAnimKill(lbl_1_bss_14C);
    HuSprAnimKill(lbl_1_bss_148);
    HuSprAnimKill(lbl_1_bss_144);
    HuSprAnimKill(lbl_1_bss_140);
}

void fn_1_4CB4(omObjData *object)
{
    s32 var_r31;
    M430DllWork *var_r30;
    s32 var_r28;
    s32 var_r27;
    HsfData *var_r26;
    s32 var_r25;
    M430DllWork *work;

    u32 spC[1] = { DATA_MAKE_NUM(DATADIR_M430, 0x01) };
    s32 sp8[1];
    u32 sp90[4] = { DATA_MAKE_NUM(DATADIR_M430, 0x0B), DATA_MAKE_NUM(DATADIR_M430, 0x0C), DATA_MAKE_NUM(DATADIR_M430, 0x0D),
        DATA_MAKE_NUM(DATADIR_M430, 0x0E) };
    u32 sp80[4] = { DATA_MAKE_NUM(DATADIR_M430, 0x02), DATA_MAKE_NUM(DATADIR_M430, 0x02), DATA_MAKE_NUM(DATADIR_M430, 0x03),
        DATA_MAKE_NUM(DATADIR_M430, 0x03) };
    u32 sp70[4] = { DATA_MAKE_NUM(DATADIR_M430, 0x04), DATA_MAKE_NUM(DATADIR_M430, 0x04), 0, 0 };
    u32 sp60[4] = { DATA_MAKE_NUM(DATADIR_M430, 0x06), DATA_MAKE_NUM(DATADIR_M430, 0x07), DATA_MAKE_NUM(DATADIR_M430, 0x08),
        DATA_MAKE_NUM(DATADIR_M430, 0x09) };
    s32 sp50[4];
    s32 sp40[4];
    s32 sp30[4];
    s32 sp20[4];
    s32 sp18[2] = { 1, 2 };
    s32 sp10[2];
    s32 spA0[6] = { 0, 3, 2, 1, 2, 3 };

    object->stat |= 0x100;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 2 * sizeof(M430DllWork), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, 2 * sizeof(M430DllWork));
    for (var_r30 = work, var_r31 = 0; var_r31 < 2; var_r31++, var_r30++) {
        var_r30->unk_00 = var_r31;
        var_r30->unk_04.x = var_r30->unk_04.y = var_r30->unk_04.z = 0.0f;
        var_r30->unk_3C = 0;
        var_r30->unk_7C = 0;
        var_r30->unk_BC = 0;
    }
    var_r30 = work;
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        object->model[var_r31] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M430, 0x00));
        var_r30[var_r31].unk_18 = object->model[var_r31];
        Hu3DModelLayerSet(var_r30[var_r31].unk_18, 0);
        Hu3DModelScaleSet(var_r30[var_r31].unk_18, 1.15f, 1.15f, 1.15f);
        var_r27 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M430, 0x0A)), 1);
        var_r30[var_r31].unk_1A = var_r27;
        Hu3DModelLayerSet(var_r27, 1);
        *((s16 *)Hu3DData[var_r27].unk_120) = 1;
        var_r30[var_r31].unk_1C = Hu3DTexScrollCreate(var_r30[var_r31].unk_18, "pa_sk2");
        var_r30[var_r31].unk_1E = Hu3DTexScrollCreate(var_r30[var_r31].unk_18, "pa_sk3");
        Hu3DTexScrollPosMoveSet(var_r30[var_r31].unk_1C, -0.00009166667f, 0.0f, 0.0f);
        Hu3DTexScrollPosMoveSet(var_r30[var_r31].unk_1E, -0.00020000001f, 0.0f, 0.0f);
        var_r30[var_r31].unk_20 = 50000.0f;
        var_r26 = Hu3DData[var_r30[var_r31].unk_18].hsfData;
        for (var_r28 = 0; var_r28 < var_r26->materialCnt; var_r28++) {
            var_r26->material[var_r28].flags &= 0xFFFFFDFF;
            var_r26->material[var_r28].pass = 1;
            var_r26->material[var_r28].invAlpha = 0.001f;
        }
    }
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M430, 0x0F));
    Hu3DModelLayerSet(object->model[2], 1);
    Hu3DModelScaleSet(object->model[2], 1.5f, 1.5f, 1.5f);
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M430, 0x10));
    Hu3DModelLayerSet(object->model[3], 2);
    Hu3DModelScaleSet(object->model[3], 1.5f, 1.5f, 1.5f);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r27 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M430, 0x15)), 0x64);
        object->model[var_r31 + 4] = var_r27;
        var_r30[var_r31].unk_10 = var_r27;
        Hu3DModelLayerSet(var_r27, 2);
        Hu3DParticleColSet(var_r27, 0xFF, 0xFF, 0xFF);
        Hu3DParticleHookSet(var_r27, fn_1_AD04);
        Hu3DModelPosSet(var_r27, 0.0f, 0.0f, 0.0f);
        *((s16 *)Hu3DData[var_r27].unk_120) = 0;
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r27 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M430, 0x15)), 0x64);
        object->model[var_r31 + 6] = var_r27;
        var_r30[var_r31].unk_14 = var_r27;
        Hu3DModelLayerSet(var_r27, 1);
        Hu3DParticleColSet(var_r27, 0xFF, 0xFF, 0xFF);
        Hu3DParticleHookSet(var_r27, fn_1_B394);
        Hu3DModelPosSet(var_r27, 0.0f, 0.0f, 0.0f);
        *((s16 *)Hu3DData[var_r27].unk_120) = 0;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp20[var_r31] = Hu3DModelCreateFile(sp90[var_r31]);
    }
    for (var_r31 = 0; var_r31 < 0xC; var_r31++) {
        var_r27 = sp20[var_r31 % 4];
        object->model[var_r31 + 8] = Hu3DModelLink(var_r27);
        object->model[var_r31 + 0x14] = Hu3DModelLink(var_r27);
        var_r30[0].unk_24[var_r31] = object->model[var_r31 + 8];
        var_r30[1].unk_24[var_r31] = object->model[var_r31 + 0x14];
        Hu3DModelLayerSet(var_r30[0].unk_24[var_r31], 1);
        Hu3DModelLayerSet(var_r30[1].unk_24[var_r31], 1);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp50[var_r31] = Hu3DModelCreateFile(sp80[var_r31]);
        sp40[var_r31] = -1;
        sp30[var_r31] = -1;
        if (sp70[var_r31] != 0) {
            sp40[var_r31] = Hu3DModelCreateFile(sp70[var_r31]);
        }
    }
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        s32 sp10[2] = { 0x5C, 0x62 };
        var_r25 = spA0[var_r31];
        var_r27 = sp50[var_r25];
        for (var_r28 = 0; var_r28 < 2; var_r28++) {
            object->model[var_r31 + sp10[var_r28]] = Hu3DModelLink(var_r27);
            var_r30[var_r28].unk_80[var_r31] = object->model[var_r31 + sp10[var_r28]];
            Hu3DModelLayerSet(var_r30[var_r28].unk_80[var_r31], 1);
        }
        for (var_r28 = 0; var_r28 < 2; var_r28++) {
            var_r30[var_r28].unk_8C[var_r31] = -1;
            var_r30[var_r28].unk_98[var_r31] = -1;
        }
        if (sp40[var_r25] >= 0) {
            var_r27 = sp40[var_r25];
            for (var_r28 = 0; var_r28 < 2; var_r28++) {
                var_r30[var_r28].unk_8C[var_r31] = Hu3DModelLink(var_r27);
                Hu3DModelLayerSet(var_r30[var_r28].unk_8C[var_r31], 4);
                Hu3DModelAttrSet(var_r30[var_r28].unk_8C[var_r31], HU3D_ATTR_ZWRITE_OFF);
            }
        }
        if (sp60[var_r25] != 0) {
            for (var_r28 = 0; var_r28 < 2; var_r28++) {
                var_r27 = Hu3DParticleCreate(HuSprAnimReadFile(sp60[var_r25]), 1);
                var_r30[var_r28].unk_98[var_r31] = var_r27;
                Hu3DModelLayerSet(var_r27, 5);
                Hu3DParticleColSet(var_r27, 0xFF, 0xFF, 0xFF);
                Hu3DModelPosSet(var_r27, 0.0f, 0.0f, 0.0f);
                *((s16 *)Hu3DData[var_r27].unk_120) = 1;
            }
        }
    }
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        sp8[var_r31] = Hu3DModelCreateFile(spC[var_r31]);
    }
    for (var_r31 = 0; var_r31 < 0x1E; var_r31 += 3) {
        var_r27 = sp8[frandmod(1)];
        object->model[var_r31 + 0x20] = Hu3DModelLink(var_r27);
        object->model[var_r31 + 0x21] = Hu3DModelLink(var_r27);
        object->model[var_r31 + 0x22] = Hu3DModelLink(var_r27);
        object->model[var_r31 + 0x3E] = Hu3DModelLink(var_r27);
        object->model[var_r31 + 0x3F] = Hu3DModelLink(var_r27);
        object->model[var_r31 + 0x40] = Hu3DModelLink(var_r27);
        var_r30->unk_40[var_r31 / 3] = object->model[var_r31 + 0x20];
        var_r30->unk_54[var_r31 / 3] = object->model[var_r31 + 0x21];
        var_r30->unk_68[var_r31 / 3] = object->model[var_r31 + 0x22];
        var_r30[1].unk_40[var_r31 / 3] = object->model[var_r31 + 0x3E];
        var_r30[1].unk_54[var_r31 / 3] = object->model[var_r31 + 0x3F];
        var_r30[1].unk_68[var_r31 / 3] = object->model[var_r31 + 0x40];
        Hu3DModelLayerSet(var_r30->unk_40[var_r31 / 3], 1);
        Hu3DModelLayerSet(var_r30->unk_54[var_r31 / 3], 1);
        Hu3DModelLayerSet(var_r30->unk_68[var_r31 / 3], 1);
        Hu3DModelLayerSet(var_r30[1].unk_40[var_r31 / 3], 1);
        Hu3DModelLayerSet(var_r30[1].unk_54[var_r31 / 3], 1);
        Hu3DModelLayerSet(var_r30[1].unk_68[var_r31 / 3], 1);
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r30[var_r31].unk_C0 = fn_1_70AC(object, var_r31, 8);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        Hu3DModelKill(sp20[var_r31]);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        Hu3DModelKill(sp50[var_r31]);
        if (sp40[var_r31] >= 0) {
            Hu3DModelKill(sp40[var_r31]);
        }
        if (sp30[var_r31] >= 0) {
            Hu3DModelKill(sp30[var_r31]);
        }
    }
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        Hu3DModelKill(sp8[var_r31]);
    }
    for (var_r30 = work, var_r31 = 0; var_r31 < 2; var_r31++, var_r30++) {
        Hu3DModelCameraSet(var_r30->unk_18, sp18[var_r31]);
        Hu3DModelCameraSet(var_r30->unk_1A, sp18[var_r31]);
        Hu3DModelCameraSet(var_r30->unk_10, sp18[var_r31]);
        Hu3DModelCameraSet(var_r30->unk_14, sp18[var_r31]);
        for (var_r28 = 0; var_r28 < 0xC; var_r28++) {
            Hu3DModelCameraSet(var_r30->unk_24[var_r28], sp18[var_r31]);
        }
        for (var_r28 = 0; var_r28 < 6; var_r28++) {
            Hu3DModelCameraSet(var_r30->unk_80[var_r28], sp18[var_r31]);
            Hu3DModelAttrSet(var_r30->unk_80[var_r28], HU3D_ATTR_DISPOFF);
            if (var_r30->unk_8C[var_r28] >= 0) {
                Hu3DModelCameraSet(var_r30->unk_8C[var_r28], sp18[var_r31]);
                Hu3DModelAttrSet(var_r30->unk_8C[var_r28], HU3D_ATTR_DISPOFF);
            }
            if (var_r30->unk_98[var_r28] >= 0) {
                Hu3DModelCameraSet(var_r30->unk_98[var_r28], sp18[var_r31]);
                Hu3DModelAttrSet(var_r30->unk_98[var_r28], HU3D_ATTR_DISPOFF);
            }
        }
        for (var_r28 = 0; var_r28 < 0xA; var_r28++) {
            Hu3DModelCameraSet(var_r30->unk_40[var_r28], sp18[var_r31]);
            Hu3DModelCameraSet(var_r30->unk_54[var_r28], sp18[var_r31]);
            Hu3DModelCameraSet(var_r30->unk_68[var_r28], sp18[var_r31]);
            Hu3DModelAttrSet(var_r30->unk_40[var_r28], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(var_r30->unk_54[var_r28], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(var_r30->unk_68[var_r28], HU3D_ATTR_DISPOFF);
        }
    }
    Hu3DModelCameraSet(object->model[2], sp18[0]);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(object->model[3], sp18[0]);
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
    object->func = fn_1_5DF8;
}

void fn_1_5DF8(omObjData *object)
{
    M430DllWork *var_r31;
    s32 var_r29;
    M430DllWork *work;

    work = object->data;
    if ((fn_1_4070() >= 2) && (fn_1_4030() != 0)) {
        var_r31 = work;
        if ((lbl_1_bss_44 == 0) && (fn_1_4130() < 5.0f)) {
            lbl_1_bss_4C = var_r31[0].unk_04.x;
            if (lbl_1_bss_4C > var_r31[1].unk_04.x) {
                lbl_1_bss_4C = var_r31[1].unk_04.x;
            }
            lbl_1_bss_44 = 1;
        }
        if ((lbl_1_bss_40 == 0) && (fn_1_4130() < 1.8f)) {
            lbl_1_bss_48 = var_r31[0].unk_04.x;
            if (lbl_1_bss_48 > var_r31[1].unk_04.x) {
                lbl_1_bss_48 = var_r31[1].unk_04.x;
            }
            lbl_1_bss_40 = 1;
        }
    }
    for (var_r31 = work, var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        var_r31->unk_04.z = var_r31->unk_04.x;
        var_r31->unk_04.x = var_r31->unk_04.y;
        fn_1_6180(var_r31);
        fn_1_6540(var_r31);
        fn_1_6DC8(var_r31);
        fn_1_6754(var_r31);
        fn_1_732C(object, var_r31->unk_C0);
        fn_1_76D8(object, var_r31->unk_C0);
        if (var_r29 != 0) {
            if (fn_1_4030() != 0) {
                Hu3DModelCameraSet(var_r31->unk_10, 2);
                Hu3DModelCameraSet(var_r31->unk_14, 2);
            }
            else {
                Hu3DModelCameraSet(var_r31->unk_10, 1);
                Hu3DModelCameraSet(var_r31->unk_14, 1);
            }
        }
    }
    if (lbl_1_bss_5C != 0) {
        Vec sp20 = { 0.0f, 3000.0f, 0.0f };
        Vec sp14 = { 0.0f, 0.0f, 0.0f };
        Vec sp8 = { 0.0f, 1.0f, 0.0f };

        Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
        Hu3DModelShadowMapSet(object->model[2]);
        Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, fn_1_7FBC(0) - 400.0f);
        Hu3DModelAttrReset(object->model[3], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(object->model[3], 0.0f, 0.0f, fn_1_7FBC(0) - 400.0f);
        sp20.z = sp14.z = fn_1_7FBC(0) - 400.0f;
        sp20.z += 100.0f;
        Hu3DShadowPosSet(&sp20, &sp8, &sp14);
        return;
    }
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
}

void fn_1_6180(M430DllWork *work)
{
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    HsfanimStruct01 *var_r30;
    s32 var_r29;

    float sp8[2] = { -450.0f, 450.0f };
    sp1C.x = CenterM[work->unk_00].x;
    sp1C.y = CenterM[work->unk_00].y + (CZoomM[work->unk_00] * sind(-CRotM[work->unk_00].x));
    sp1C.z = CenterM[work->unk_00].z + (CZoomM[work->unk_00] * cosd(-CRotM[work->unk_00].x));
    sp28.x = sp1C.x;
    sp28.y = 0.0f;
    sp28.z = sp1C.z - 450000.0f;
    VECSubtract(&sp28, &sp1C, &sp10);
    VECNormalize(&sp10, &sp10);
    VECScale(&sp10, &sp10, 6000.0f);
    VECAdd(&sp1C, &sp10, &sp28);
    Hu3DModelPosSetV(work->unk_18, &sp28);
    if ((fn_1_4070() >= 2) && (fn_1_4030() != 0)) {
        if ((lbl_1_bss_40 != 0) && (lbl_1_bss_48 >= work->unk_04.x)) {
            if (work->unk_20 > 0.0f) {
                work->unk_20 = fn_1_7FBC(work->unk_00) - 23000.0f;
            }
            sp28.x = 0.0f;
            sp28.y = 0.0f;
            sp28.z = work->unk_20 - fn_1_7FBC(work->unk_00);
            VECSubtract(&sp28, &sp1C, &sp10);
            VECNormalize(&sp10, &sp10);
            VECScale(&sp10, &sp10, 5000.0f);
            VECAdd(&sp1C, &sp10, &sp28);
            sp28.y += 237.5f;
            Hu3DModelPosSet(work->unk_1A, 0.0f, 593.75f, work->unk_20);
            var_r30 = ((ParticleData *)Hu3DData[work->unk_1A].unk_120)->unk_48;
            var_r30->unk34.x = var_r30->unk34.y = var_r30->unk34.z = 0.0f;
            var_r30->unk2C = 2000.0f;
            var_r29 = var_r30->unk40.a;
            var_r29 += 2;
            if (var_r29 > 0xFF) {
                var_r29 = 0xFF;
            }
            var_r30->unk40.a = var_r29;
        }
    }
    else {
        var_r30 = ((ParticleData *)Hu3DData[work->unk_1A].unk_120)->unk_48;
        var_r30->unk2C = 0.0f;
        var_r30->unk40.a = 0;
    }
    DCStoreRange(var_r30, sizeof(HsfanimStruct01));
}

void fn_1_6540(M430DllWork *work)
{
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = 1;
    var_f29 = work->unk_04.x;
    work->unk_3C = (s32)(fabs2(var_f29) / 1000.0) % 12;
    var_r30 = work->unk_3C;
    var_f31 = 1000.0f * (s32)(work->unk_04.x / 1000.0f);
    var_f30 = 4000.0f;
    for (var_r29 = 0; var_r29 < 0xC; var_r29++) {
        if (var_r28 != 0) {
            Hu3DModelAttrReset(work->unk_24[var_r30], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(work->unk_24[var_r30], 0.0f, 0.0f, var_f31);
            var_f31 -= 1000.0f;
            var_f30 -= 1000.0f;
            if (var_f30 < 0.0f) {
                var_r28 = 0;
            }
        }
        else {
            Hu3DModelAttrSet(work->unk_24[var_r30], HU3D_ATTR_DISPOFF);
        }
        var_r30 = (var_r30 + 1) % 12;
    }
}

void fn_1_6754(M430DllWork *work)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    s32 var_r30;
    HsfanimStruct01 *var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    var_r27 = 1;
    {
        float sp20[6] = { -1800.0f, 2000.0f, -1800.0f, 2000.0f, -1800.0f, 2000.0f };
        Vec2f sp38[6] = {
            { -130.0f, 500.0f },
            { 180.0f, 70.0f },
            { 100.0f, 50.0f },
            { -30.000002f, 500.0f },
            { 100.0f, 50.0f },
            { 180.0f, 70.0f },
        };
        float sp8[6] = { 2750.0f, 1550.0f, 1450.0f, 2750.0f, 1450.0f, 1550.0f };
        if (lbl_1_bss_5C != 0) {
            var_r27 = 0;
        }
        if ((fn_1_4070() == 0) || (fn_1_4030() == 0) || (lbl_1_bss_44 == 0) || !(lbl_1_bss_4C > work->unk_04.x)) {
            for (var_r28 = 0; var_r28 < 6; var_r28++) {
                work->unk_A4[var_r28] = 1;
            }
        }
        var_f26 = work->unk_04.x;
        work->unk_BC = (s32)(fabs2(var_f26) / 5000.0) % 6;
        var_r30 = work->unk_BC;
        var_f31 = 1000.0f + (5000.0f * (s32)(work->unk_04.x / 5000.0f));
        var_f28 = (1000.0f + work->unk_04.x) - 9000.0f;
        var_f27 = (1000.0f + work->unk_04.x) - 20000.0f;
        for (var_r28 = 0; var_r28 < 6; var_r28++) {
            var_r25 = var_r24 = var_r23 = 1;
            if ((var_r27 != 0) && (work->unk_A4[var_r30] != 0)) {
                if ((var_f31 > var_f28) || ((work->unk_98[var_r30] >= 0) && (var_f31 > var_f27))) {
                    if (var_f31 > var_f28) {
                        Hu3DModelAttrReset(work->unk_80[var_r30], HU3D_ATTR_DISPOFF);
                        Hu3DModelPosSet(work->unk_80[var_r30], sp20[var_r30], 0.0f, var_f31);
                        if (work->unk_8C[var_r30] >= 0) {
                            Hu3DModelAttrReset(work->unk_8C[var_r30], HU3D_ATTR_DISPOFF);
                            Hu3DModelPosSet(work->unk_8C[var_r30], sp20[var_r30], 0.0f, var_f31);
                        }
                        var_r25 = var_r24 = 0;
                    }
                    if ((work->unk_98[var_r30] >= 0) && (var_f31 > var_f27) && (var_f31 < (1000.0f + var_f28))) {
                        var_r26 = work->unk_98[var_r30];
                        Hu3DModelAttrReset(var_r26, HU3D_ATTR_DISPOFF);
                        var_r29 = ((ParticleData *)Hu3DData[var_r26].unk_120)->unk_48;
                        Hu3DModelPosSet(work->unk_98[var_r30], sp20[var_r30] + sp38[var_r30].x, sp38[var_r30].y, var_f31);
                        var_r29->unk34.x = var_r29->unk34.y = var_r29->unk34.z = 0.0f;
                        var_r29->unk2C = sp8[var_r30];
                        var_r29->unk40.a = -1;
                        var_f30 = fabs(var_f27 - var_f31);
                        var_f29 = 1000.0f - (var_f31 - var_f28);
                        if (var_f30 < 2000.0f) {
                            var_f30 *= 0.0005f;
                            var_r29->unk40.a = 255.0f * var_f30;
                        }
                        else if (var_f29 < 1000.0f) {
                            var_f29 *= 0.001f;
                            var_r29->unk40.a = 255.0f * var_f29;
                        }
                        DCStoreRange(var_r29, sizeof(HsfanimStruct01));
                        var_r23 = 0;
                    }
                }
            }
            else {
                work->unk_A4[var_r30] = 0;
            }
            if (var_r25 != 0) {
                Hu3DModelAttrSet(work->unk_80[var_r30], HU3D_ATTR_DISPOFF);
            }
            if ((var_r24 != 0) && (work->unk_8C[var_r30] >= 0)) {
                Hu3DModelAttrSet(work->unk_8C[var_r30], HU3D_ATTR_DISPOFF);
            }
            if ((var_r23 != 0) && (work->unk_98[var_r30] >= 0)) {
                Hu3DModelAttrSet(work->unk_98[var_r30], HU3D_ATTR_DISPOFF);
            }
            var_f31 -= 5000.0f;
            if (var_f31 < var_f27) {
                var_r27 = 0;
            }
            var_r30 = (var_r30 + 1) % 6;
        }
    }
}

void fn_1_6DC8(M430DllWork *work)
{
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = 1;
    if (lbl_1_bss_5C != 0) {
        var_r28 = 0;
    }
    var_f29 = work->unk_04.x;
    work->unk_7C = (s32)(fabs2(var_f29) / 1000.0) % 10;
    var_r30 = work->unk_7C;
    var_f31 = 1000.0f + (1000.0f * (s32)(work->unk_04.x / 1000.0f));
    var_f30 = 8000.0f;
    for (var_r29 = 0; var_r29 < 0xA; var_r29++) {
        if (var_r28 != 0) {
            Hu3DModelAttrReset(work->unk_40[var_r30], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->unk_54[var_r30], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->unk_68[var_r30], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(work->unk_40[var_r30], -920.0f, 0.0f, var_f31);
            Hu3DModelPosSet(work->unk_54[var_r30], 0.0f, 0.0f, var_f31);
            Hu3DModelPosSet(work->unk_68[var_r30], 920.0f, 0.0f, var_f31);
            var_f31 -= 1000.0f;
            var_f30 -= 1000.0f;
            if (var_f30 < 0.0f) {
                var_r28 = 0;
            }
        }
        else {
            Hu3DModelAttrSet(work->unk_40[var_r30], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk_54[var_r30], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk_68[var_r30], HU3D_ATTR_DISPOFF);
        }
        var_r30 = (var_r30 + 1) % 10;
    }
}

M430DllUnkStruct2 *fn_1_70AC(omObjData *arg0, s32 var_r27, s16 var_r28)
{
    float var_f31;
    float var_f30;
    float var_f29;
    M430DllUnkStruct2 *var_r31;
    s32 var_r30;
    M430DllUnkStruct2 *var_r29;

    u32 sp10[2] = { DATA_MAKE_NUM(DATADIR_M430, 0x11), DATA_MAKE_NUM(DATADIR_M430, 0x12) };
    s32 sp8[2] = { 1, 2 };
    var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r28 * sizeof(M430DllUnkStruct2), MEMORY_DEFAULT_NUM);
    memset(var_r29, 0, var_r28 * 0x3C);
    var_f31 = -90.0f;
    for (var_r31 = var_r29, var_r30 = 0; var_r30 < var_r28; var_r30++, var_r31++) {
        var_r31->unk_00 = var_r27;
        var_r31->unk_04 = Hu3DModelCreateFile(sp10[var_r30 & 1]);
        Hu3DModelLayerSet(var_r31->unk_04, 1);
        Hu3DModelCameraSet(var_r31->unk_04, sp8[var_r31->unk_00]);
        var_f30 = frandmod(0x168);
        var_f29 = frandmod(0x118);
        var_r31->unk_0C.x = var_f29 * sind(var_f30) + fn_1_BB54(var_r27);
        var_r31->unk_0C.y = var_f31;
        var_r31->unk_0C.z = var_f29 * cosd(var_f30);
        var_r31->unk_2C = frandmod(0x168);
        var_r31->unk_34 = 1.0f;
        var_r31->unk_38 = 0.0f;
        var_f31 -= 10.0f;
        var_r31->unk_0A = var_r28;
    }
    return var_r29;
}

void fn_1_732C(omObjData *object, M430DllUnkStruct2 *arg1)
{
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = arg1->unk_0A;
    for (var_r30 = 0; var_r30 < var_r28; var_r30++, arg1++) {
        var_r29 = 0;
        if (arg1->unk_34 > arg1->unk_38) {
            var_r29 = 1;
        }
        else {
            VECSubtract(&arg1->unk_18, &arg1->unk_0C, &sp8);
            var_f31 = VECMag(&sp8);
            if (var_f31 < 50.0f) {
                var_r29 = 1;
            }
        }
        if (var_r29 != 0) {
            var_f31 = frandmod(0x168);
            var_f30 = 400.0f + frandmod(0x15E);
            arg1->unk_18.x = var_f30 * sind(var_f31) + fn_1_BB54(arg1->unk_00);
            arg1->unk_18.z = 2.0 * (var_f30 * cosd(var_f31));
            arg1->unk_18.y = arg1->unk_0C.y;
            arg1->unk_34 = 0.0f;
            arg1->unk_38 = 200.0f + frandmod(0x258);
            arg1->unk_28 = 400.0f;
        }
        VECSubtract(&arg1->unk_18, &arg1->unk_0C, &sp8);
        arg1->unk_30 = atan2d(sp8.x, sp8.z);
        arg1->unk_2C = fn_1_48B0(arg1->unk_2C, arg1->unk_30, 0.08f);
        arg1->unk_28 += 0.05f * (300.0f - arg1->unk_28);
        arg1->unk_24 += 0.2f * (arg1->unk_28 - arg1->unk_24);
        arg1->unk_0C.x = arg1->unk_0C.x + ((0.016666668f * arg1->unk_24) * sind(arg1->unk_2C));
        arg1->unk_0C.z = arg1->unk_0C.z + ((0.016666668f * arg1->unk_24) * cosd(arg1->unk_2C));
        arg1->unk_34 += 0.016666668f * arg1->unk_24;
    }
}

void fn_1_76D8(omObjData *object, M430DllUnkStruct2 *arg1)
{
    float var_f31;
    s32 var_r30;
    s32 var_r29;

    var_r29 = arg1->unk_0A;
    if (lbl_1_bss_5C != 0) {
        for (var_r30 = 0; var_r30 < var_r29; var_r30++, arg1++) {
            Hu3DModelAttrSet(arg1->unk_04, HU3D_ATTR_DISPOFF);
        }
        return;
    }
    var_f31 = (s32)(0.00011111111f * (1000.0f + fn_1_7FBC(arg1->unk_00)));
    var_f31 = (100.0f * (90.0f * var_f31)) - 5000.0f;
    for (var_r30 = 0; var_r30 < var_r29; var_r30++, arg1++) {
        Hu3DModelPosSet(arg1->unk_04, arg1->unk_0C.x, arg1->unk_0C.y, arg1->unk_0C.z + var_f31);
        Hu3DModelRotSet(arg1->unk_04, 0.0f, arg1->unk_2C, 0.0f);
        Hu3DModelAttrReset(arg1->unk_04, HU3D_ATTR_DISPOFF);
    }
}

void fn_1_7848(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    M430DllWork2 *var_r31;
    s16 var_r30;
    s32 var_r29;
    M430DllWork2 *work;
    s32 var_r26;

    var_r30 = 0x20;
    work = HuMemDirectMallocNum(HEAP_SYSTEM, var_r30 * sizeof(M430DllWork2), MEMORY_DEFAULT_NUM);
    object->data = work;
    memset(work, 0, var_r30 * sizeof(M430DllWork2));
    var_r26 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M430, 0x13));
    var_f29 = 1000.0f;
    for (var_r31 = work, var_r29 = 0; var_r29 < var_r30; var_r29++, var_r31++) {
        var_r31->unk_00 = Hu3DModelLink(var_r26);
        Hu3DModelLayerSet(var_r31->unk_00, 1);
        Hu3DModelCameraSet(var_r31->unk_00, 1);
        Hu3DModelAttrSet(var_r31->unk_00, HU3D_ATTR_DISPOFF);
        var_r31->unk_14.x = (2.8f * frandmod(0x3E8)) - 1400.0f;
        var_r31->unk_14.z = 0.7f * frandmod(0x3E8) - 350.0f;
        var_r31->unk_14.y = 300.0f + (0.8f * frandmod(0x3E8));
        var_f30 = frandmod(0x168);
        var_f31 = 200.0f + frandmod(0xAF);
        var_r31->unk_08.x = var_f31 * sind(var_f30);
        var_r31->unk_08.y = 0.0f;
        var_r31->unk_08.z = var_f31 * cosd(var_f30);
        VECAdd(&var_r31->unk_14, &var_r31->unk_08, &var_r31->unk_08);
        var_r31->unk_38 = 60.0f - (0.13483146f * var_f31);
        var_r31->unk_28 = frandmod(0x168);
        if (frandmod(0x3E8) < 0x1F4) {
            var_f28 = -70.0f + (0.1f * frandmod(0x32));
        }
        else {
            var_f28 = 70.0f - (0.1f * frandmod(0x32));
        }
        var_r31->unk_3C = var_f28;
        if (var_r31->unk_3C < 0.0f) {
            var_r31->unk_38 = -var_r31->unk_38;
        }
        var_r31->unk_30 = 1.0f;
        var_r31->unk_34 = 0.0f;
        var_f29 -= 50.0f;
        var_r31->unk_06 = var_r30;
    }
    (void)var_r29;
    (void)object;
    Hu3DModelKill(var_r26);
    object->func = fn_1_7CAC;
}

void fn_1_7CAC(omObjData *object)
{
    Vec spC;
    s32 sp8;
    s32 var_r29;

    M430DllWork2 *work = object->data;
    s32 var_r28 = work->unk_06;
    if (fn_1_4070() >= 4) {
        for (var_r29 = 0; var_r29 < var_r28; var_r29++, work++) {
            sp8 = 0;
            VECSubtract(&work->unk_14, &work->unk_08, &spC);
            work->unk_2C = atan2d(spC.x, spC.z);
            work->unk_28 = fn_1_48B0(work->unk_28, work->unk_2C + work->unk_3C, 0.08f);
            work->unk_24 += (0.05f * (600.0f - work->unk_24));
            work->unk_20 += (0.2f * (work->unk_24 - work->unk_20));
            work->unk_08.x += ((0.016666668f * work->unk_20) * sind(work->unk_28));
            work->unk_08.z += ((0.016666668f * work->unk_20) * cosd(work->unk_28));
            work->unk_30 += (0.016666668f * work->unk_20);
        }
        fn_1_7EAC(object, object->data);
    }
}

void fn_1_7EAC(omObjData *object, M430DllWork2 *var_r31)
{
    Mtx sp8;
    float var_f31;
    s32 var_r30;
    Mtx *var_r29;
    s32 var_r28;

    var_r28 = var_r31->unk_06;
    var_f31 = fn_1_7FBC(0) - 2000.0f;
    for (var_r30 = 0; var_r30 < var_r28; var_r30++, var_r31++) {
        Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_08.x, var_r31->unk_08.y, var_r31->unk_08.z + var_f31);
        var_r29 = &Hu3DData[var_r31->unk_00].unk_F0;
        MTXRotRad(*var_r29, 0x59, 0.017453292f * var_r31->unk_28);
        MTXRotRad(sp8, 0x5A, 0.017453292f * var_r31->unk_38);
        MTXConcat(*var_r29, sp8, *var_r29);
        Hu3DModelAttrReset(var_r31->unk_00, HU3D_ATTR_DISPOFF);
    }
}

float fn_1_7FBC(s32 arg0)
{
    M430DllWork *var_r31;
    M430DllWork *var_r30;

    var_r30 = lbl_1_bss_58->data;
    arg0 &= 1;
    var_r31 = var_r30;
    return var_r31[arg0].unk_04.x;
}

void fn_1_7FFC(s32 arg0, float arg8)
{
    M430DllWork *var_r31;
    M430DllWork *var_r30;

    var_r30 = lbl_1_bss_58->data;
    arg0 &= 1;
    var_r31 = var_r30;
    var_r31[arg0].unk_04.y = arg8;
}

void fn_1_803C(omObjData *var_r31)
{
    var_r31->stat |= 0x100;
    omSetStatBit(var_r31, 0xA0);
    var_r31->model[0] = Hu3DHookFuncCreate(fn_1_8CE0);
    Hu3DModelLayerSet(var_r31->model[0], 4);
    Hu3DModelCameraSet(var_r31->model[0], 1);
    var_r31->model[1] = Hu3DHookFuncCreate(fn_1_8CE0);
    Hu3DModelLayerSet(var_r31->model[1], 4);
    Hu3DModelCameraSet(var_r31->model[1], 2);
    var_r31->model[2] = Hu3DHookFuncCreate(fn_1_9C90);
    Hu3DModelLayerSet(var_r31->model[2], 0);
    Hu3DModelCameraSet(var_r31->model[2], 1);
    var_r31->model[3] = Hu3DHookFuncCreate(fn_1_9C90);
    Hu3DModelLayerSet(var_r31->model[3], 0);
    Hu3DModelCameraSet(var_r31->model[3], 2);
    var_r31->model[4] = Hu3DHookFuncCreate(fn_1_A3A8);
    Hu3DModelLayerSet(var_r31->model[4], 1);
    Hu3DModelCameraSet(var_r31->model[4], 3);
    var_r31->model[5] = Hu3DHookFuncCreate(fn_1_AB98);
    Hu3DModelLayerSet(var_r31->model[5], 3);
    Hu3DModelCameraSet(var_r31->model[5], 3);
    var_r31->model[6] = Hu3DHookFuncCreate(fn_1_AC84);
    Hu3DModelLayerSet(var_r31->model[6], 7);
    Hu3DModelCameraSet(var_r31->model[6], 3);
    lbl_1_bss_60->unk_00 = 0;
    lbl_1_bss_60->unk_04 = var_r31->model[0];
    fn_1_82F4(var_r31, lbl_1_bss_60);
    lbl_1_bss_60[1].unk_00 = 1;
    lbl_1_bss_60[1].unk_04 = var_r31->model[1];
    fn_1_82F4(var_r31, &lbl_1_bss_60[1]);
    var_r31->func = fn_1_8264;
}

void fn_1_8264(omObjData *object)
{
    lbl_1_bss_60[0].unk_08 = lbl_1_bss_60[1].unk_08 = 0;
    lbl_1_bss_60[0].unk_0C = lbl_1_bss_60[1].unk_0C = 0;
    lbl_1_bss_60[0].unk_10 = lbl_1_bss_60[1].unk_10 = 0;
    lbl_1_bss_60[0].unk_14 = lbl_1_bss_60[1].unk_14 = 0;
    lbl_1_bss_60[0].unk_18 = lbl_1_bss_60[1].unk_18 = 0;
}

void fn_1_82F4(omObjData *object, M430DllBss60Struct *var_r31)
{
    float var_f31;
    float var_f30;
    s32 var_r30;
    Vec *var_r29;
    GXColor *var_r28;
    s32 var_r27;

    s32 sp8[8] = { 0, 0x16, 1, 0x17, 1, 0, 0x17, 0x16 };

    var_r31->unk_2C = HuMemDirectMallocNum(HEAP_SYSTEM, 0x1B8 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    var_r31->unk_30 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x1B8 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    var_r31->unk_34 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x14A0, MEMORY_DEFAULT_NUM);
    var_r31->unk_38 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x6E0, MEMORY_DEFAULT_NUM);
    var_r31->unk_40 = 0;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31->unk_44[var_r30] = HuMemDirectMallocNum(HEAP_SYSTEM, 0x1B8 * sizeof(Vec), MEMORY_DEFAULT_NUM);
        var_r31->unk_54[var_r30] = HuMemDirectMallocNum(HEAP_SYSTEM, 0x1B8 * sizeof(GXColor), MEMORY_DEFAULT_NUM);
    }
    var_r31->unk_5C = 0x12D0;
    var_r31->unk_60 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk_5C, MEMORY_DEFAULT_NUM);
    DCFlushRange(var_r31->unk_60, var_r31->unk_5C);
    var_r31->unk_64 = 0;
    var_r31->unk_68 = GXGetTexBufferSize(0x140, 0x1E0, 5, 0, 0);
    if (var_r31->unk_00 == 0) {
        var_r31->unk_68 *= 2;
    }
    var_r31->unk_6C = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk_68, MEMORY_DEFAULT_NUM);
    DCFlushRange(var_r31->unk_6C, var_r31->unk_68);
    var_r31->unk_1C = 0;
    var_r31->unk_20 = 0;
    var_r31->unk_24 = 0.0f;
    var_r31->unk_28 = 0.0f;
    var_r29 = var_r31->unk_2C;
    var_f31 = 0.0f;
    var_f30 = -2000.0f;
    for (var_r30 = 0; var_r30 < 0x14; var_r30++) {
        var_f31 = 65.47619f - var_f31;
        for (var_r27 = 0; var_r27 < 0x16; var_r27++) {
            var_r29->x = ((130.95238f * var_r27) - 1375.0f) + var_f31;
            var_r29->y = 0.0f;
            var_r29->z = var_f30;
            var_r29++;
        }
        var_f30 += 210.52632f;
    }
    memset(var_r31->unk_30, 0, 0x1B8 * sizeof(Vec));
    for (var_r29 = var_r31->unk_30, var_r30 = 0; var_r30 < 0x1B8; var_r30++, var_r29++) {
        var_r29->y = (0.05f * frandmod(0x3E8)) - 20.0f;
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        memcpy(var_r31->unk_44[var_r30], var_r31->unk_2C, 0x1B8 * sizeof(Vec));
        for (var_r28 = var_r31->unk_54[var_r30], var_r27 = 0; var_r27 < 0x1B8; var_r27++, var_r28++) {
            var_r28->r = 0x32;
            var_r28->g = 0x8C;
            var_r28->b = 0xB4;
            var_r28->a = 0;
        }
    }
    fn_1_86B4(object, var_r31);
    fn_1_8B5C(object, var_r31);
}

void fn_1_86B4(omObjData *object, M430DllBss60Struct *arg1)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    GXColor *var_r30;
    s32 var_r29;
    Vec *var_r28;
    Vec *var_r27;
    Vec *var_r26;
    u32 var_r25;
    s32 var_r24;
    s32 var_r23;
    M430DllWork *var_r22;
    M430DllWork *var_r21;

    if (omPauseChk() == 0) {
        arg1->unk_1C++;
    }
    arg1->unk_40 = 1 - arg1->unk_40;
    var_r25 = arg1->unk_00;
    var_r21 = lbl_1_bss_58->data;
    var_r25 &= 1;
    var_r22 = var_r21;
    var_f29 = var_r22[var_r25].unk_04.x;
    var_f28 = var_f29;
    var_f30 = var_f28;
    var_r24 = 0.002375f * var_f30;
    arg1->unk_28 = 421.05264f * var_r24;
    arg1->unk_24 = var_f30 - arg1->unk_28;
    arg1->unk_20 = (var_r24 * 2) % 20;
    var_r23 = (arg1->unk_20 + 0x14) % 20;
    Hu3DModelPosSet(arg1->unk_04, fn_1_BB54(arg1->unk_00), 0.0f, arg1->unk_28 - 500.0f);
    var_r28 = arg1->unk_2C;
    var_r30 = arg1->unk_54[arg1->unk_40];
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = 2000.0f + arg1->unk_24;
    if (lbl_1_bss_5C != 0) {
        for (var_r29 = 0; var_r29 < 0x1B8; var_r29++) {
            VECSubtract(var_r28, &sp14, &sp8);
            var_f31 = 0.00025f * VECMag(&sp8);
            if (var_f31 < 0.3f) {
                var_r30->a = -1;
            }
            else if (var_f31 > 0.75f) {
                var_r30->a = 0;
            }
            else {
                var_f31 = 255.0f - (566.6667f * (var_f31 - 0.3f));
                var_r30->a = var_f31;
            }
            var_r28++;
            var_r30++;
        }
    }
    else {
        for (var_r29 = 0; var_r29 < 0x1B8; var_r29++) {
            VECSubtract(var_r28, &sp14, &sp8);
            var_f31 = 0.00025f * VECMag(&sp8);
            if (var_f31 < 0.25f) {
                var_r30->a = -0x1A;
            }
            else if (var_f31 > 0.85f) {
                var_r30->a = 0;
            }
            else {
                var_f31 = 230.0f - (383.3333f * (var_f31 - 0.25f));
                var_r30->a = var_f31;
            }
            var_r28++;
            var_r30++;
        }
    }
    if (lbl_1_bss_5C != 0) {
        memcpy(arg1->unk_44[arg1->unk_40], arg1->unk_2C, 0x1B8 * sizeof(Vec));
    }
    else {
        var_r28 = arg1->unk_2C;
        var_r26 = arg1->unk_44[arg1->unk_40];
        var_r29 = (0x14 - var_r23) * 0x16;
        var_r27 = &arg1->unk_30[0x1B8 - var_r29];
        while (var_r29-- != 0) {
            VECAdd(var_r28, var_r27, var_r26);
            var_r28++;
            var_r27++;
            var_r26++;
        }
        var_r29 = var_r23 * 0x16;
        var_r27 = arg1->unk_30;
        while (var_r29-- != 0) {
            VECAdd(var_r28, var_r27, var_r26);
            var_r28++;
            var_r27++;
            var_r26++;
        }
        memcpy(arg1->unk_44[arg1->unk_40], arg1->unk_2C, 0x16 * sizeof(Vec));
    }
    DCStoreRangeNoSync(arg1->unk_44[arg1->unk_40], 0x1B8 * sizeof(Vec));
    DCStoreRangeNoSync(arg1->unk_54[arg1->unk_40], 0x1B8 * sizeof(GXColor));
    PPCSync();
}

void fn_1_8B5C(omObjData *object, M430DllBss60Struct *var_r30)
{
    s32 var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    s32 sp28[5] = { 0, 0, 0, 1, 1 };
    s32 sp18[4] = { 1, 0, 0, 0 };
    s32 sp8[4] = { 0, 0, 1, 2 };
    GXBeginDisplayList(var_r30->unk_60, var_r30->unk_5C);
    var_r26 = 0;
    var_r31 = 0;
    for (var_r29 = 0; var_r29 < 0x13; var_r29++) {
        var_r24 = 0x2B - (((var_r26 * 2) + sp8[var_r31]) * 2);
        var_r27 = sp18[var_r31];
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, var_r24);
        for (var_r28 = 0; var_r28 < var_r24; var_r28++) {
            var_r25 = (var_r28 >> 1) + ((var_r29 + var_r27) * 0x16) + (var_r26 + sp28[var_r31 + var_r27]);
            GXUnknownu16(var_r25);
            GXUnknownu16(var_r25);
            var_r27 = 1 - var_r27;
        }
        var_r31++;
        if (var_r31 >= 4) {
            var_r31 = 0;
            var_r26++;
        }
    }
    var_r30->unk_64 = GXEndDisplayList();
}

void fn_1_8CE0(ModelData *model, Mtx matrix)
{
    Mtx sp194;
    Mtx sp164;
    Mtx sp134;
    Mtx sp104;
    Mtx spD4;
    Mtx spA4;
    Mtx sp74;
    Mtx sp44;
    GXTexObj sp24;
    float var_f31;
    float var_f30;
    M430DllBss60Struct *var_r31;

    GXColor sp20 = { 0xFF, 0xFF, 0xFF, 0xFF };
    GXColor sp1C = { 0x08, 0x08, 0x08, 0xFF };
    GXColor sp18 = { 0x00, 0x00, 0x00, 0x80 };
    GXColor sp14 = { 0xCC, 0xBF, 0xB2, 0x33 };
    GXColor sp10 = { 0xE0, 0xD8, 0xF4, 0x08 };
    var_r31 = lbl_1_bss_60;
    if (var_r31->unk_10 != 0) {
        var_r31 = &var_r31[1];
    }
    var_r31->unk_10 = 1;
    fn_1_963C(model, matrix, var_r31->unk_00);
    MTXCopy(matrix, sp134);
    if (fn_1_4030() != 0) {
        var_f30 = 1.0f;
        var_f31 = fn_1_BB54(var_r31->unk_00);
    }
    else {
        var_f30 = 1.5f;
        var_f31 = 0.0f;
    }
    MTXTrans(sp164, var_f31 - fn_1_BB54(var_r31->unk_00), 0.0f, 0.0f);
    MTXConcat(sp134, sp164, sp134);
    MTXScale(sp194, var_f30, 1.0f, 1.0f);
    MTXConcat(sp134, sp194, sp134);
    GXLoadPosMtxImm(sp134, 0);
    MTXInvXpose(sp134, sp194);
    GXLoadNrmMtxImm(sp194, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    if ((fn_1_4030() == 0) && (var_r31->unk_00 == 0)) {
        GXInitTexObj(&sp24, var_r31->unk_6C, 0x280, 0x1E0, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    }
    else {
        GXInitTexObj(&sp24, var_r31->unk_6C, 0x140, 0x1E0, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    }
    GXInitTexObjLOD(&sp24, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sp24, GX_TEXMAP0);
    HuSprTexLoad(lbl_1_bss_150, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_148, 0, 2, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetNumTexGens(3);
    if (fn_1_4030() != 0) {
        C_MTXLightPerspective(sp104, 41.5f, 0.6f, 0.5f, -0.5f, 0.5f, 0.5f);
    }
    else {
        C_MTXLightPerspective(sp104, 41.5f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    }
    MTXInverse(Hu3DCameraMtx, spD4);
    MTXConcat(spD4, sp134, spD4);
    MTXConcat(sp104, Hu3DCameraMtx, spA4);
    MTXConcat(spA4, spD4, spD4);
    GXLoadTexMtxImm(spD4, 0x1E, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, 0x1E, GX_FALSE, 0x7D);
    C_MTXLightPerspective(sp104, 70.0f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, sp74);
    MTXConcat(sp74, sp134, sp74);
    MTXConcat(sp104, Hu3DCameraMtx, sp44);
    MTXConcat(sp44, sp74, sp74);
    GXLoadTexMtxImm(sp74, 0x24, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX3x4, GX_TG_POS, 0x24, GX_FALSE, 0x7D);
    MTXRotRad(sp164, 0x58, 1.5707964f);
    var_f31 = 0.00075f * var_f30;
    MTXScale(sp194, var_f31, -0.003f, 0.00075f);
    MTXConcat(sp164, sp194, sp164);
    MTXTrans(sp194, (var_r31->unk_1C & 0x3FF) / (1024.0f * var_f31), 0.0f, (0.7f * var_r31->unk_28) - (0.3f * var_r31->unk_24));
    MTXConcat(sp164, sp194, sp164);
    sp164[0][1] = -0.001f;
    GXLoadTexMtxImm(sp164, 0x21, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_POS, 0x21, GX_FALSE, 0x7D);
    GXSetNumIndStages(2);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(0, 0, GX_TRUE, GX_FALSE, 1);
    MTXScale(sp164, -0.25f, -0.5f, 0.5f);
    GXSetIndTexMtx(GX_ITM_0, (float(*)[3])sp164, -4);
    GXSetIndTexOrder(GX_INDTEXSTAGE1, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(1, 1, GX_TRUE, GX_FALSE, 2);
    MTXScale(sp164, 0.4f, 0.5f, 0.5f);
    GXSetIndTexMtx(GX_ITM_1, (float(*)[3])sp164, -1);
    GXSetNumTevStages(2);
    GXSetTevColor(GX_TEVREG0, sp14);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
    GXSetZMode(1, GX_LEQUAL, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_POS, var_r31->unk_44[var_r31->unk_40], sizeof(Vec));
    GXSetArray(GX_VA_CLR0, var_r31->unk_54[var_r31->unk_40], sizeof(GXColor));
    GXSetCullMode(GX_CULL_NONE);
    GXCallDisplayList(var_r31->unk_60, var_r31->unk_64);
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
}

Vec lbl_1_data_60[6] = {
    { -2750.0f, 0.0f, -2500.0f },
    { 2750.0f, 0.0f, -2500.0f },
    { -2750.0f, 0.0f, 0.0f },
    { 2750.0f, 0.0f, 0.0f },
    { -1375.0f, 0.0f, 2500.0f },
    { 1375.0f, 0.0f, 2500.0f },
};
GXColor lbl_1_data_A8[6] = {
    { 5, 0x38, 0xA2, 0 },
    { 5, 0x38, 0xA2, 0xFF },
    { 0x14, 0x54, 0xAB, 0xFF },
    { 0x1E, 0x6D, 0xB0, 0xFF },
    { 0x2A, 0x7E, 0xB4, 0xFF },
    { 0x32, 0x8C, 0xB4, 0xFF },
};

void fn_1_963C(ModelData *model, Mtx matrix, u32 var_r31)
{
    Mtx sp100;
    Mtx spD0;
    Mtx spA0;
    Mtx sp70;
    Mtx sp40;
    Mtx sp10;
    float var_f31;
    float var_f30;

    GXColor spC = { 0x32, 0x8C, 0xB4, 0x33 };
    if (fn_1_4030() != 0) {
        var_f30 = 1.0f;
        var_f31 = fn_1_BB54(var_r31);
    }
    else {
        var_f30 = 1.5f;
        var_f31 = 0.0f;
    }
    MTXTrans(spD0, var_f31, 0.0f, ((lbl_1_bss_60[var_r31].unk_28 + lbl_1_bss_60[var_r31].unk_24) - 2500.0f) - 2000.0f);
    MTXScale(sp100, var_f30, 1.0f, 1.0f);
    MTXConcat(spD0, sp100, spD0);
    MTXConcat(Hu3DCameraMtx, spD0, spA0);
    GXLoadPosMtxImm(spA0, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    HuSprTexLoad(lbl_1_bss_14C, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_148, 0, 1, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetNumTexGens(2);
    C_MTXLightPerspective(sp70, 70.0f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, sp40);
    MTXConcat(sp40, spA0, sp40);
    MTXConcat(sp70, Hu3DCameraMtx, sp10);
    MTXConcat(sp10, sp40, sp40);
    GXLoadTexMtxImm(sp40, 0x21, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX3x4, GX_TG_POS, 0x21, GX_FALSE, 0x7D);
    MTXRotRad(spD0, 0x58, 1.5707964f);
    var_f31 = 0.00075f * var_f30;
    MTXScale(sp100, var_f31, -0.003f, 0.00075f);
    MTXConcat(spD0, sp100, spD0);
    MTXTrans(sp100, (lbl_1_bss_60[var_r31].unk_1C & 0x3FF) / (1024.0f * var_f31), 0.0f,
        0.3f * (lbl_1_bss_60[var_r31].unk_28 + lbl_1_bss_60[var_r31].unk_24));
    MTXConcat(spD0, sp100, spD0);
    GXLoadTexMtxImm(spD0, 0x1E, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_POS, 0x1E, GX_FALSE, 0x7D);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(0, 0, GX_TRUE, GX_FALSE, 1);
    MTXScale(spD0, 0.5f, 0.6f, 0.6f);
    GXSetIndTexMtx(GX_ITM_0, (float(*)[3])spD0, -1);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, spC);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_POS, lbl_1_data_60, sizeof(Vec));
    GXSetArray(GX_VA_CLR0, lbl_1_data_A8, sizeof(GXColor));
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 6);
    GXPosition1x8(0);
    GXColor1x8(3);
    GXPosition1x8(1);
    GXColor1x8(3);
    GXPosition1x8(2);
    GXColor1x8(4);
    GXPosition1x8(3);
    GXColor1x8(4);
    GXPosition1x8(4);
    GXColor1x8(5);
    GXPosition1x8(5);
    GXColor1x8(5);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
}

Vec lbl_1_data_C0[8] = {
    { -2750.0f, 20.0f, 0.0f },
    { 2750.0f, 20.0f, 0.0f },
    { -2750.0f, -20.0f, 0.0f },
    { 2750.0f, -20.0f, 0.0f },
    { -2750.0f, -160.0f, 0.0f },
    { 2750.0f, -160.0f, 0.0f },
    { -2750.0f, -340.0f, 0.0f },
    { 2750.0f, -340.0f, 0.0f },
};
Vec lbl_1_data_120[6] = {
    { -700.0f, 0.0f, -1750.0f },
    { 700.0f, 0.0f, -1750.0f },
    { -700.0f, 0.0f, -1400.0f },
    { 700.0f, 0.0f, -1400.0f },
    { -700.0f, 0.0f, 700.0f },
    { 700.0f, 0.0f, 700.0f },
};

void fn_1_9C90(ModelData *model, Mtx matrix)
{
    Mtx sp124;
    Mtx spF4;
    Mtx spC4;
    Mtx sp94;
    Mtx sp64;
    Mtx sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;

    GXColor spC = { 0x32, 0x8C, 0xB4, 0x33 };
    var_r31 = 0;
    if (lbl_1_bss_60[var_r31].unk_14 != 0) {
        var_r31++;
    }
    lbl_1_bss_60[var_r31].unk_14 = 1;
    sp1C.x = CenterM[var_r31].x;
    sp1C.y = CenterM[var_r31].y + (CZoomM[var_r31] * sind(-CRotM[var_r31].x));
    sp1C.z = CenterM[var_r31].z + (CZoomM[var_r31] * cosd(-CRotM[var_r31].x));
    sp28.x = sp1C.x;
    sp28.y = 0.0f;
    sp28.z = sp1C.z - 450000.0f;
    VECSubtract(&sp28, &sp1C, &sp10);
    VECNormalize(&sp10, &sp10);
    VECScale(&sp10, &sp10, 8000.0f);
    VECAdd(&sp1C, &sp10, &sp28);
    MTXTrans(spF4, sp28.x, sp28.y, sp28.z);
    var_f31 = 1.0f;
    if (fn_1_4030() == 0) {
        var_f31 = 1.5f;
        MTXScale(sp124, var_f31, 1.0f, 1.0f);
        MTXConcat(spF4, sp124, spF4);
    }
    MTXConcat(Hu3DCameraMtx, spF4, spC4);
    GXLoadPosMtxImm(spC4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    HuSprTexLoad(lbl_1_bss_14C, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_148, 0, 1, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetNumTexGens(2);
    C_MTXLightPerspective(sp94, 70.0f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, sp64);
    MTXConcat(sp64, spC4, sp64);
    MTXConcat(sp94, Hu3DCameraMtx, sp34);
    MTXConcat(sp34, sp64, sp64);
    GXLoadTexMtxImm(sp64, 0x21, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX3x4, GX_TG_POS, 0x21, GX_FALSE, 0x7D);
    var_f30 = 0.00075f * var_f31;
    MTXScale(spF4, var_f30, -0.005f, 0.00075f);
    MTXTrans(sp124, (lbl_1_bss_60[var_r31].unk_1C & 0x3FF) / (1024.0f * var_f30),
        0.03f * -(lbl_1_bss_60[var_r31].unk_28 + lbl_1_bss_60[var_r31].unk_24), 0.0f);
    MTXConcat(spF4, sp124, spF4);
    GXLoadTexMtxImm(spF4, 0x1E, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_POS, 0x1E, GX_FALSE, 0x7D);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(0, 0, GX_TRUE, GX_FALSE, 1);
    MTXScale(spF4, 0.5f, 0.6f, 0.6f);
    GXSetIndTexMtx(GX_ITM_0, (float(*)[3])spF4, -1);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, spC);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_POS, lbl_1_data_C0, 0xC);
    GXSetArray(GX_VA_CLR0, lbl_1_data_A8, 4);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 8);
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        GXPosition1x8(var_r30);
        GXColor1x8(var_r30 >> 1);
    }
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
}

GXColor lbl_1_data_168[2] = { { 0xFF, 0xFF, 0xFF, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } };

void fn_1_A3A8(ModelData *model, Mtx matrix)
{
    Mtx sp48;
    Mtx sp18;
    float var_f31;
    float var_f30;
    u8 *var_r30;
    u8 *var_r29;

    GXColor sp14 = { 0xFF, 0xA5, 0x59, 0xB2 };
    GXColor sp10 = { 0x99, 0x72, 0x59, 0xB2 };
    s32 var_r31 = 0;
    if (lbl_1_bss_60[var_r31].unk_0C != 0) {
        var_r31++;
    }
    lbl_1_bss_60[var_r31].unk_0C = 1;
    if (fn_1_4030() != 0) {
        var_f30 = 1.0f;
        var_f31 = fn_1_BB54(var_r31);
    }
    else {
        var_f30 = 1.5f;
        var_f31 = 0.0f;
    }
    if (lbl_1_bss_5C != 0) {
        MTXTrans(sp18, var_f31, 0.0f, 300.0f + (lbl_1_bss_60[var_r31].unk_28 + lbl_1_bss_60[var_r31].unk_24));
        GXSetTevColor(GX_TEVREG0, sp10);
    }
    else {
        MTXTrans(sp18, var_f31, -150.0f, lbl_1_bss_60[var_r31].unk_28 + lbl_1_bss_60[var_r31].unk_24);
        GXSetTevColor(GX_TEVREG0, sp14);
    }
    MTXScale(sp48, var_f30, 1.0f, 1.0f);
    MTXConcat(sp18, sp48, sp18);
    MTXConcat(Hu3DCameraMtx, sp18, sp18);
    GXLoadPosMtxImm(sp18, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    HuSprTexLoad(lbl_1_bss_144, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_140, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(2);
    MTXRotRad(sp18, 0x58, 1.5707964f);
    var_f31 = 0.004f * var_f30;
    MTXScale(sp48, var_f31, -0.004f, 0.004f);
    MTXConcat(sp18, sp48, sp18);
    MTXTrans(sp48, (lbl_1_bss_60[var_r31].unk_1C & 0x3FF) / (512.0f * var_f31), 0.0f,
        (1.2499999f * (lbl_1_bss_60[var_r31].unk_1C % 400)) + (lbl_1_bss_60[var_r31].unk_28 + lbl_1_bss_60[var_r31].unk_24));
    MTXConcat(sp18, sp48, sp18);
    GXLoadTexMtxImm(sp18, 0x1E, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_POS, 0x1E, GX_FALSE, 0x7D);
    MTXRotRad(sp18, 0x58, 1.5707964f);
    var_f31 = 0.004f * var_f30;
    MTXScale(sp48, var_f31, -0.004f, 0.004f);
    MTXConcat(sp18, sp48, sp18);
    MTXTrans(sp48, (lbl_1_bss_60[var_r31].unk_1C % 300) / (150.0f * var_f31), 0.0f, lbl_1_bss_60[var_r31].unk_28 + lbl_1_bss_60[var_r31].unk_24);
    MTXConcat(sp18, sp48, sp18);
    GXLoadTexMtxImm(sp18, 0x21, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_POS, 0x21, GX_FALSE, 0x7D);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_SET);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_POS, lbl_1_data_120, 0xC);
    GXSetArray(GX_VA_CLR0, lbl_1_data_168, 4);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 6);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXPosition1x8(1);
    GXColor1x8(0);
    GXPosition1x8(2);
    GXColor1x8(1);
    GXPosition1x8(3);
    GXColor1x8(1);
    GXPosition1x8(4);
    GXColor1x8(1);
    GXPosition1x8(5);
    GXColor1x8(1);
}

void fn_1_AB98(ModelData *model, Mtx matrix)
{
    s32 var_r31 = 0;
    if (lbl_1_bss_60[var_r31].unk_08 != 0) {
        var_r31++;
    }
    if ((fn_1_4030() == 0) && (var_r31 == 0)) {
        GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
        GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB5A3, 0);
    }
    else {
        GXSetTexCopySrc(var_r31 * 0x140, 0, 0x140, 0x1E0);
        GXSetTexCopyDst(0x140, 0x1E0, GX_TF_RGB5A3, 0);
    }
    GXCopyTex(lbl_1_bss_60[var_r31].unk_6C, 0);
    GXPixModeSync();
    lbl_1_bss_60[var_r31].unk_08 = 1;
}

void fn_1_AC84(ModelData *model, Mtx matrix)
{
    s32 var_r31 = 0;
    if (lbl_1_bss_60[var_r31].unk_18 != 0) {
        var_r31++;
    }
    lbl_1_bss_60[var_r31].unk_18 = 1;
    fn_1_86B4(lbl_1_bss_54, &lbl_1_bss_60[var_r31]);
}

void fn_1_AD04(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    s32 var_r29;

    if ((particle->unk_00 == 0) || (lbl_1_bss_5C != 0)) {
        particle->unk_00++;
        for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            var_r31->unk00 = 0;
            var_r31->unk2C = 0.0f;
            var_r31->unk40.a = 0;
        }
        return;
    }
    for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00_s16 != 0) {
            VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            VECScale(&var_r31->unk08, &var_r31->unk08, 0.97f);
            if (var_r31->unk00_s16 < 24.0f) {
                var_r31->unk40.a = 0.9f * var_r31->unk40.a;
            }
            var_r31->unk2C += 1.5f;
            if (--var_r31->unk00_s16 == 0) {
                var_r31->unk00_s16 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_AEE0(s32 arg0, Vec *arg1, float arg8, float arg9)
{
    Vec sp10;
    float var_f31;
    float var_f30;
    float var_f28;
    HsfanimStruct01 *var_r31;
    ParticleData *var_r30;
    s32 var_r29;
    M430DllWork *var_r28;
    u32 var_r27;
    void *var_r26;

    var_r26 = lbl_1_bss_58->data;
    var_r28 = var_r26;
    var_r30 = Hu3DData[var_r28[arg0].unk_10].unk_120;
    if (var_r30->unk_00 != 0) {
        var_r31 = var_r30->unk_48;
        if (!(frandmod(0x3E8) > (1200.0f * arg9))) {
            var_r27 = 1;
            var_f28 = 30.0f;
            for (var_r29 = 0; var_r29 < var_r30->unk_30; var_r29++, var_r31++) {
                if (var_r31->unk00_s16 == 0) {
                    var_r31->unk00 = 60.0f * (0.5f + (0.0005f * frandmod(0x3E8)));
                    var_f30 = (0.002f * frandmod(0x3E8)) - 1.0f;
                    var_f30 = arg8 + (var_f30 * var_f28);
                    sp10.x = sind(var_f30);
                    sp10.y = 0.0f;
                    sp10.z = cosd(var_f30);
                    var_r31->unk34 = *arg1;
                    var_r31->unk34.y = -20.0f;
                    var_f31 = 5.0f + arg9 * (1.6666667f * (2.0f * (0.001f * frandmod(0x3E8))));
                    var_r31->unk08.x = sp10.x * var_f31;
                    var_r31->unk08.y = -0.2f * var_f31;
                    var_r31->unk08.z = sp10.z * var_f31;
                    var_f31 = 0.001f * frandmod(0x3E8);
                    var_f31 += (1.0f - var_f31) * (0.5f * arg9);
                    var_r31->unk30 = frandmod(0x168);
                    var_r31->unk2C = 80.0f + frandmod(0x46);
                    var_r31->unk40.a = frandmod(0x64) + 0x64;
                    var_r31->unk40.r = 150.0f + (95.0f * var_f31);
                    var_r31->unk40.g = 160.0f + (80.0f * var_f31);
                    var_r31->unk40.b = 166.0f + (60.0f * var_f31);
                    if (--var_r27 == 0) {
                        break;
                    }
                }
            }
        }
    }
}

void fn_1_B394(ModelData *model, ParticleData *var_r30, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    s32 var_r29;

    if ((var_r30->unk_00 == 0) || (lbl_1_bss_5C != 0)) {
        var_r30->unk_00++;
        for (var_r31 = var_r30->unk_48, var_r29 = 0; var_r29 < var_r30->unk_30; var_r29++, var_r31++) {
            var_r31->unk00_s16 = 0;
            var_r31->unk2C = 0.0f;
            var_r31->unk40.a = 0;
        }
        return;
    }
    for (var_r31 = var_r30->unk_48, var_r29 = 0; var_r29 < var_r30->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00_s16 != 0) {
            var_r31->unk00_s16--;
            VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            var_r31->unk2C += 0.5f;
            if (var_r31->unk00_s16 < 30.0) {
                var_r31->unk40.a = 0.98f * var_r31->unk40.a;
            }
            if ((var_r31->unk34.y < -40.0f) || (var_r31->unk00_s16 == 0)) {
                var_r31->unk00_s16 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(var_r30->unk_48, var_r30->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_B570(s32 arg0, Vec *arg1, float arg8, float arg9, Vec *arg2)
{
    Vec sp28;
    Vec sp1C;
    s32 sp18;
    float var_f31;
    float var_f30;
    float var_f28;
    HsfanimStruct01 *var_r31;
    ParticleData *var_r30;
    s32 var_r29;
    M430DllWork *var_r28;
    u32 var_r27;
    M430DllWork *var_r26;

    var_r26 = lbl_1_bss_58->data;
    {
        float sp14[2] = { -100.0f, 100.0f };
        var_r28 = var_r26;
        var_r30 = Hu3DData[var_r28[arg0].unk_14].unk_120;
        if (var_r30->unk_00 != 0) {
            var_r31 = var_r30->unk_48;
            if (!(frandmod(0x3E8) > (1000.0f * arg9))) {
                var_r27 = 2;
                var_f28 = 40.0f;
                VECScale(arg2, &sp1C, 0.2f);
                sp1C.x = 0.0f;
                for (var_r29 = 0; var_r29 < var_r30->unk_30; var_r29++, var_r31++) {
                    if (var_r31->unk00_s16 == 0) {
                        var_r31->unk00_s16 = 60.0f * (0.5f + (0.0005f * frandmod(0x3E8)));
                        var_f30 = (0.002f * frandmod(0x3E8)) - 1.0f;
                        var_f30 = arg8 + sp14[var_r29 & 1] + (var_f30 * var_f28);
                        sp28.x = sind(var_f30);
                        sp28.y = 0.0f;
                        sp28.z = cosd(var_f30);
                        var_r31->unk34 = *arg1;
                        var_r31->unk34.x = var_r31->unk34.x + ((0.05f * frandmod(0x3E8)) - 25.0f);
                        var_r31->unk34.z = var_r31->unk34.z + ((0.05f * frandmod(0x3E8)) - 25.0f);
                        var_r31->unk34.y = 40.0f;
                        var_f31 = 1.6666667f + (arg9 * (0.0016666667f * frandmod(0x3E8)));
                        var_r31->unk08.x = sp28.x * var_f31;
                        var_r31->unk08.z = sp28.z * var_f31;
                        var_r31->unk08.y = 0.0f;
                        VECAdd(&var_r31->unk08, &sp1C, &var_r31->unk08);
                        var_f31 = 0.001f * frandmod(0x3E8);
                        var_f31 += (1.0f - var_f31) * (0.3f * arg9);
                        var_r31->unk30 = frandmod(0x168);
                        var_r31->unk2C = 60.0f + frandmod(0x50);
                        var_r31->unk40.a = (60.0f * arg9) + frandmod(0x50);
                        var_r31->unk40.r = 150.0f + (95.0f * var_f31);
                        var_r31->unk40.g = 160.0f + (80.0f * var_f31);
                        var_r31->unk40.b = 166.0f + (60.0f * var_f31);
                        if (--var_r27 == 0) {
                            break;
                        }
                    }
                }
            }
        }
    }
}

float fn_1_BB54(u32 arg0)
{
    float sp8[2] = { -450.0f, 450.0f };

    return sp8[arg0 & 1];
}

float fn_1_BB88(void)
{
    return 0.0f;
}

void fn_1_BB98(u32 arg0)
{
    lbl_1_bss_5C = 0;
    if (arg0 != 0) {
        lbl_1_bss_5C = 1;
    }
}
