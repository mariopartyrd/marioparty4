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
#endif

inline double fabs2(double x)
{
    return (double)fabs(x);
}

typedef struct M430PlayerData170Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} M430PlayerData170Struct; /* size = 0x08 */

typedef struct M430PlayerBss160Struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10[6];
    s32 unk_28[6][3];
    s32 unk_70[6][3];
    s32 unk_B8;
    s32 unk_BC;
} M430PlayerBss160Struct; /* size = 0xC0 */

typedef struct M430PlayerBss164Struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    AnimData *unk_14;
    Vec unk_18;
    Vec unk_24;
    Vec unk_30;
} M430PlayerBss164Struct; /* size = 0x3C */

typedef struct M430PlayerBss168Struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    Vec unk_14;
    Vec unk_20;
    Vec unk_2C;
} M430PlayerBss168Struct; /* size = 0x38 */

typedef struct M430PlayerBss16CStruct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    float unk_18;
    Vec unk_1C;
    float unk_28;
    float unk_2C;
    float unk_30;
    float unk_34;
    float unk_38;
    float unk_3C;
} M430PlayerBss16CStruct; /* size = 0x40 */

typedef struct M430PlayerBss170Struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    float unk_20;
    float unk_24;
    float unk_28;
    float unk_2C;
    float unk_30;
    float unk_34;
    float unk_38;
    float unk_3C;
    float unk_40;
    float unk_44;
    float unk_48;
    Vec *unk_4C;
    Vec *unk_50;
    Vec2f *unk_54;
    s32 unk_58;
    u32 unk_5C;
    void *unk_60;
} M430PlayerBss170Struct; /* size = 0x64 */

typedef struct M430PlayerBss174Struct {
    s32 unk_00[2];
    s32 unk_08;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    s32 unk_20;
} M430PlayerBss174Struct; /* size = 0x24 */

typedef struct M430PlayerWork {
    u32 unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    float unk_18;
    float unk_1C;
    float unk_20;
    float unk_24;
    float unk_28;
    float unk_2C;
    float unk_30;
    s32 unk_34;
    s32 unk_38;
    char unk3C[4];
    s32 unk_40;
    u32 unk_44;
    float unk_48;
    float unk_4C;
    float unk_50;
    float unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    float unk_70;
    s32 unk_74;
    s32 unk_78;
    float unk_7C;
} M430PlayerWork; /* size = 0x80 */

void fn_1_100A0(void);
void fn_1_1033C(void);
void fn_1_1053C(void);
void fn_1_10540(s32 arg0, s32 arg1, float arg8, float arg9, float argA);
void fn_1_1058C(s32 arg0, float arg8);
void fn_1_105B8(s32 arg0);
void fn_1_1061C(M430PlayerBss170Struct *arg0);
void fn_1_10948(ModelData *model, Mtx matrix);
void fn_1_10B88(void);
void fn_1_10D1C(void);
void fn_1_10F20(void);
s32 fn_1_10F24(s32 arg0, float arg8, float arg9, float argA);
s32 fn_1_110A8(s32 arg0, float arg8, float arg9, float argA, s32 arg1);
s32 fn_1_111BC(s32 arg0, float arg8, Vec *arg1);
void fn_1_11314(s32 arg0);
void fn_1_113AC(void);
void fn_1_114F0(void);
void fn_1_11644(void);
s32 fn_1_11648(s32 arg0, float arg8, float arg9, float argA);
s32 fn_1_117A4(s32 arg0, float arg8, float arg9, float argA, s32 arg1);
s32 fn_1_11A1C(s32 arg0, float arg8, Vec *arg1);
M430PlayerBss168Struct *fn_1_11B64(s32 arg0);
void fn_1_11B94(s32 arg0);
void fn_1_11C1C(void);
void fn_1_11D70(void);
void fn_1_11F60(void);
s32 fn_1_11F90(s32 arg0, float arg8, float arg9, float argA);
void fn_1_12550(s32 arg0);
void fn_1_125C4(void);
void fn_1_129CC(void);
void fn_1_12D74(void);
void fn_1_12DF0(s32 arg0);
void fn_1_12F20(float arg8, float *arg0, float *arg1, float *arg2, float *arg3);
float fn_1_1303C(float arg8, float arg9);
float fn_1_13154(float arg8, float arg9, float argA);
void fn_1_133A4(AnimData *arg0);
void fn_1_133DC(Mtx arg0, Vec *arg1);
void fn_1_BE24(omObjData *object);
void fn_1_C040(void);
void fn_1_C1E4(omObjData *object);
void fn_1_CA3C(omObjData *object);
void fn_1_D2D0(omObjData *object);
void fn_1_D828(omObjData *object);
void fn_1_E8FC(omObjData *object);
void fn_1_F0D8(omObjData *object);
s32 fn_1_F62C(omObjData *object);
void fn_1_F6A0(omObjData *object);
void fn_1_FC9C(omObjData *object);

M430PlayerData170Struct lbl_1_data_170[7] = {
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x42), -1 },
    { 0, 1 },
    { 0, 2 },
    { 0, 3 },
    { 0, -1 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17), -1 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18), -1 },
};
M430PlayerData170Struct lbl_1_data_1A8[4] = {
    { 0, 4 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00), -1 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17), -1 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18), -1 },
};
s32 lbl_1_data_1C8[5] = { 0, DATA_MAKE_NUM(DATADIR_M430, 0x31), DATA_MAKE_NUM(DATADIR_M430, 0x39), DATA_MAKE_NUM(DATADIR_M430, 0x41),
    DATA_MAKE_NUM(DATADIR_M430, 0x49) };
float lbl_1_data_1DC[7] = { -262.5f, -173.25f, -86.625f, 0.0f, 86.625f, 173.25f, 262.5f };
Vec lbl_1_data_1F8[8] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 160.0f },
    { 60.000004f, 0.0f, 0.0f },
    { -60.000004f, 0.0f, 0.0f },
    { 50.0f, 0.0f, 100.0f },
    { -50.0f, 0.0f, 100.0f },
    { 60.000004f, 0.0f, -120.00001f },
    { -60.000004f, 0.0f, -120.00001f },
};
float lbl_1_data_258[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 25.0f };
s32 lbl_1_data_278[2] = { DATA_MAKE_NUM(DATADIR_M430, 0x1C), DATA_MAKE_NUM(DATADIR_M430, 0x1D) };
s32 lbl_1_data_280[2] = { DATA_MAKE_NUM(DATADIR_M430, 0x1E), DATA_MAKE_NUM(DATADIR_M430, 0x1F) };
s32 lbl_1_data_288[2] = { DATA_MAKE_NUM(DATADIR_M430, 0x20), DATA_MAKE_NUM(DATADIR_M430, 0x21) };

s32 lbl_1_bss_17C;
Process *lbl_1_bss_178;
M430PlayerBss174Struct *lbl_1_bss_174;
M430PlayerBss170Struct *lbl_1_bss_170;
M430PlayerBss16CStruct *lbl_1_bss_16C;
M430PlayerBss168Struct *lbl_1_bss_168;
M430PlayerBss164Struct *lbl_1_bss_164;
M430PlayerBss160Struct *lbl_1_bss_160;
s32 lbl_1_bss_15C;
s32 lbl_1_bss_158;

void fn_1_BBC4(Process *process)
{
    Vec sp14;
    Vec sp8;

    lbl_1_bss_178 = process;
    fn_1_C040();
    fn_1_100A0();
    fn_1_10B88();
    fn_1_113AC();
    fn_1_11C1C();
    fn_1_125C4();
    omAddObjEx(process, 0x2D, 0, 0, -1, fn_1_BE24);
    sp14.x = CenterM[0].x + (CZoomM[0] * (sind(CRotM[0].y) * cosd(CRotM[0].x)));
    sp14.y = CenterM[0].y + (CZoomM[0] * -sind(CRotM[0].x));
    sp14.z = CenterM[0].z + (CZoomM[0] * (cosd(CRotM[0].y) * cosd(CRotM[0].x)));
    PSVECSubtract(CenterM, &sp14, &sp8);
    PSVECNormalize(&sp8, &sp8);
    HuAudFXListnerSetEX(&sp14, &sp8, 100000.0f, 566.6667f, 0.0f, 300.0f, 300.0f);
}

void fn_1_BE24(omObjData *object)
{
    Vec sp14;
    Vec sp8;

    fn_1_1033C();
    fn_1_10D1C();
    fn_1_114F0();
    fn_1_11D70();
    fn_1_129CC();
    sp14.x = CenterM[0].x + (CZoomM[0] * (sind(CRotM[0].y) * cosd(CRotM[0].x)));
    sp14.y = CenterM[0].y + (CZoomM[0] * -sind(CRotM[0].x));
    sp14.z = CenterM[0].z + (CZoomM[0] * (cosd(CRotM[0].y) * cosd(CRotM[0].x)));
    PSVECSubtract(CenterM, &sp14, &sp8);
    PSVECNormalize(&sp8, &sp8);
    HuAudFXListnerUpdate(&sp14, &sp8);
}

void fn_1_C00C(void)
{
    HuAudFXListnerKill();
    fn_1_1053C();
    fn_1_10F20();
    fn_1_11644();
    fn_1_11F60();
    fn_1_12D74();
}

void fn_1_C040(void)
{
    s8 spC[4];
    s32 sp8;
    s32 var_r31;
    omObjData *var_r30;
    s32 var_r29;
    s32 var_r28;

    sp8 = 0;
    lbl_1_bss_17C = 1;
    omMakeGroupEx(lbl_1_bss_178, 0, 4);
    omGetGroupMemberListEx(lbl_1_bss_178, 0);
    lbl_1_bss_174 = HuMemDirectMallocNum(HEAP_SYSTEM, 2 * sizeof(M430PlayerBss174Struct), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_174, 0, 2 * sizeof(M430PlayerBss174Struct));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        spC[var_r31] = -1;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = GWPlayerCfg[var_r31].group;
        if (spC[var_r29] == -1) {
            spC[var_r29] = var_r31;
        }
        else {
            break;
        }
    }
    if (var_r31 < 4) {
        spC[0] = 0;
        spC[1] = 1;
        spC[2] = 2;
        spC[3] = 3;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = omAddObjEx(lbl_1_bss_178, 0x28, 3, 7, 0, fn_1_C1E4);
        var_r28 = spC[var_r31];
        var_r30->work[0] = var_r28;
        var_r30->work[1] = var_r31 >> 1;
        var_r30->work[2] = var_r31 & 1;
    }
}

void fn_1_C1E4(omObjData *object)
{
    M430PlayerWork *work;
    s32 var_r29;
    M430PlayerBss174Struct *var_r28;
    u32 var_r27;
    HsfData *var_r26;
    HsfMaterial *var_r25;
    ModelData *var_r24;
    s32 var_r23;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M430PlayerWork), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, sizeof(M430PlayerWork));
    var_r27 = object->work[0];
    var_r23 = GWPlayerCfg[var_r27].character;
    work->unk_38 = var_r23;
    work->unk_00 = var_r27;
    work->unk_04 = object->work[1];
    work->unk_06 = GWPlayerCfg[var_r27].pad_idx;
    work->unk_08 = GWPlayerCfg[var_r27].iscom;
    work->unk_0A = GWPlayerCfg[var_r27].diff;
    work->unk_0C = object->work[2];
    work->unk_0E = 0;
    work->unk_10 = 0;
    work->unk_12 = 0;
    work->unk_14 = 0;
    work->unk_16 = 0;
    if (work->unk_04 == 0) {
        work->unk_18 = 450.0f;
    }
    else {
        work->unk_18 = -450.0f;
    }
    work->unk_34 = 1;
    work->unk_24 = 12.500001f;
    work->unk_28 = 0.0f;
    work->unk_1C = 180.0f;
    work->unk_2C = 0.0f;
    work->unk_30 = 0.0f;
    work->unk_20 = 0.0f;
    work->unk_40 = work->unk_44 = 0;
    work->unk_48 = work->unk_4C = 0.0f;
    work->unk_50 = 0.0f;
    work->unk_54 = 0.0f;
    work->unk_74 = 0;
    work->unk_78 = -1;
    work->unk_7C = 0.0f;
    work->unk_60 = -1;
    work->unk_64 = -1;
    work->unk_68 = -1;
    work->unk_6C = -1;
    work->unk_70 = lbl_1_data_258[var_r23];
    object->model[0] = CharModelCreate(work->unk_38, 4);
    Hu3DModelCameraSet(object->model[0], 3);
    Hu3DModelLayerSet(object->model[0], 6);
    CharModelStepTypeSet(work->unk_38, 3);
    if (work->unk_0C == 0) {
        for (var_r29 = 0; var_r29 < 7; var_r29++) {
            if ((lbl_1_data_170[var_r29].unk_04) == 0xFFFFFFFF) {
                object->motion[var_r29] = CharModelMotionCreate(work->unk_38, lbl_1_data_170[var_r29].unk_00);
            }
            else {
                object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], work->unk_38 + lbl_1_data_1C8[lbl_1_data_170[var_r29].unk_04]);
            }
            if (var_r29 == 5) {
                CharModelVoiceEnableSet(work->unk_38, object->motion[var_r29], 0);
            }
        }
        work->unk_58 = 0;
        CharModelMotionSet(work->unk_38, object->motion[work->unk_58]);
        object->model[1] = Hu3DModelCreateFile(lbl_1_data_278[work->unk_04]);
        Hu3DModelLayerSet(object->model[1], 2);
        Hu3DModelCameraSet(object->model[1], 3);
        Hu3DModelScaleSet(object->model[1], 1.2f, 1.2f, 1.2f);
        object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M430, 0x25));
        Hu3DModelLayerSet(object->model[2], 1);
        Hu3DModelCameraSet(object->model[2], 3);
        work->unk_60 = HuAudFXPlay(0x67A);
        work->unk_68 = 0x50;
        if (work->unk_60 != -1) {
            HuAudFXVolSet(work->unk_60, work->unk_68);
        }
        if (work->unk_04 == 0) {
            work->unk_64 = HuAudFXPlay(0x675);
        }
        else {
            work->unk_64 = HuAudFXPlay(0x676);
        }
        if (work->unk_64 != -1) {
            HuAudFXPitchSet(work->unk_64, 0);
        }
    }
    else {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if (lbl_1_data_1A8[var_r29].unk_04 == 0xFFFFFFFF) {
                object->motion[var_r29] = CharModelMotionCreate(work->unk_38, lbl_1_data_1A8[var_r29].unk_00);
            }
            else {
                object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], work->unk_38 + lbl_1_data_1C8[lbl_1_data_1A8[var_r29].unk_04]);
            }
            if (var_r29 == 2) {
                CharModelVoiceEnableSet(work->unk_38, object->motion[var_r29], 0);
            }
        }
        work->unk_58 = 0;
        CharModelMotionSet(work->unk_38, object->motion[work->unk_58]);
        Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
        object->model[1] = Hu3DModelCreateFile(lbl_1_data_280[work->unk_04]);
        Hu3DModelLayerSet(object->model[1], 7);
        Hu3DModelCameraSet(object->model[1], 3);
        Hu3DModelAttrSet(object->model[1], HU3D_MOTATTR_LOOP);
        Hu3DMotionSpeedSet(object->model[1], 2.0f);
        object->model[2] = Hu3DModelCreateFile(lbl_1_data_288[work->unk_04]);
        Hu3DModelLayerSet(object->model[2], 6);
        Hu3DModelCameraSet(object->model[2], 3);
    }
    CharModelMotionDataClose(work->unk_38);
    object->trans.x = work->unk_18;
    if (work->unk_0C == 0) {
        object->trans.y = 0.0f;
    }
    else {
        object->trans.y = 200.0f;
    }
    if (work->unk_04 == 0) {
        object->trans.z = -100000.0f;
    }
    else {
        object->trans.z = -101000.0f;
    }
    object->rot.y = 180.0f;
    work->unk_20 = object->trans.y;
    var_r28 = &lbl_1_bss_174[work->unk_04];
    if (work->unk_0C == 0) {
        var_r28->unk_00[work->unk_0C] = work->unk_00;
        if (work->unk_08 != 0) {
            var_r23 = var_r28->unk_08 | 1;
            var_r28->unk_08 = var_r23;
        }
        var_r28->unk_0C = object->trans.x;
        var_r28->unk_10 = 0.0f;
        var_r28->unk_14 = object->trans.z;
        var_r28->unk_18 = object->trans.z;
        var_r28->unk_1C = work->unk_24;
        var_r28->unk_20 = 0;
        lbl_1_bss_158 = 1;
    }
    else {
        var_r28->unk_00[work->unk_0C] = work->unk_00;
        if (work->unk_08 != 0) {
            var_r28->unk_08 = var_r28->unk_08 | 2;
        }
    }
    if (work->unk_0C != 0) {
        var_r24 = &Hu3DData[object->model[1]];
        var_r26 = var_r24->hsfData;
        for (var_r25 = var_r26->material, var_r29 = 0; var_r29 < var_r26->materialCnt; var_r29++, var_r25++) {
            var_r25->flags |= 2;
        }
    }
    object->func = fn_1_CA3C;
    (void)var_r24;
    (void)var_r24;
}

void fn_1_CA3C(omObjData *object)
{
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    M430PlayerWork *work;
    s32 var_r29;
    M430PlayerBss174Struct *var_r28;
    HsfData *var_r27;
    HsfMaterial *var_r26;
    ModelData *var_r25;

    work = object->data;
    var_r28 = &lbl_1_bss_174[work->unk_04];
    work->unk_40 = 0;
    work->unk_44 = 0;
    work->unk_48 = 0.0f;
    work->unk_4C = 0.0f;
    if (work->unk_0C == 0) {
        work->unk_34 = 3;
        work->unk_24 = -41.000004f;
        object->rot.y = 0.0f;
        object->rot.z = 0.0f;
        object->trans.z -= work->unk_30;
        fn_1_D828(object);
        if (work->unk_60 != -1) {
            HuAudFXVolSet(work->unk_60, work->unk_68);
        }
        if (work->unk_64 != -1) {
            HuAudFXPitchSet(work->unk_64, (s32)(8192.0f * (work->unk_68 / 127.0f)));
        }
        object->rot.y = object->rot.z = 0.0f;
        if (++work->unk_10 > (60.0f * (1.5f + (0.5f * work->unk_04)))) {
            work->unk_30 += 30.000002f;
            var_r28->unk_18 = object->trans.z = object->trans.z + work->unk_30;
            work->unk_68 += 3;
            if (work->unk_68 > 0x7F) {
                work->unk_68 = 0x7F;
            }
        }
        else {
            var_r28->unk_18 = object->trans.z;
        }
        var_f30 = work->unk_70 * sind(object->rot.y);
        var_f29 = work->unk_70 * cosd(object->rot.y);
        Hu3DModelPosSet(object->model[1], object->trans.x + var_f30, object->trans.y, object->trans.z + var_f29);
        Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
        Hu3DModelPosSet(object->model[2], object->trans.x + var_f30, object->trans.y - 150.0f, object->trans.z + var_f29);
        Hu3DModelRotSet(object->model[2], object->rot.x, 180.0f + object->rot.y, object->rot.z);
        fn_1_10540(work->unk_04, 0, object->trans.x, 25.0f + object->trans.y, object->trans.z - 100.0f);
        if (work->unk_10 > 30.0f) {
            var_f31 = 0.016666668f * (work->unk_10 - 30.0f);
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            var_f31 = sind((90.0f * var_f31));
            var_f31 *= var_f31;
        }
        else {
            var_f31 = 0.0f;
        }
        CenterM[work->unk_04].x = work->unk_18 - (var_f31 * work->unk_18);
        CenterM[work->unk_04].z = (950.0f * (0.5f + (0.5f * var_f31))) + fn_1_7FBC(work->unk_04);
    }
    else {
        work->unk_1C = 0.0f;
        object->rot.y = 0.0f;
        object->rot.z = 0.0f;
        fn_1_E8FC(object);
        work->unk_1C = 0.0f;
        object->rot.y = 0.0f;
        object->rot.z = 0.0f;
        object->trans.y = 200.0f;
        object->trans.z = var_r28->unk_18 - 300.0f;
        object->rot.z = 0.0f;
        for (var_r29 = 0; var_r29 < 2; var_r29++) {
            Hu3DModelPosSet(object->model[var_r29 + 1], object->trans.x, 150.0f + object->trans.y, 50.0f + object->trans.z);
            Hu3DModelRotSet(object->model[var_r29 + 1], object->rot.x, object->rot.y, object->rot.z);
        }
        fn_1_10540(work->unk_04, 1, object->trans.x, 150.0f + object->trans.y, 50.0f + object->trans.z);
        if (work->unk_6C == -1) {
            sp8.x = object->trans.x;
            sp8.y = object->trans.y;
            sp8.z = object->trans.z;
            work->unk_6C = HuAudFXEmiterPlay(0x67B, &sp8);
        }
        else {
            sp8.x = object->trans.x;
            sp8.y = object->trans.y;
            sp8.z = object->trans.z;
            HuAudFXEmiterUpDate(work->unk_6C, &sp8);
        }
    }
    if (fn_1_4058() == 2) {
        if (work->unk_0C == 0) {
            work->unk_34 = 1;
            work->unk_24 = 12.500001f;
            work->unk_28 = 0.0f;
            work->unk_68 = 0x50;
            object->trans.y = 0.0f;
        }
        else {
            var_r25 = &Hu3DData[object->model[1]];
            var_r27 = var_r25->hsfData;
            for (var_r26 = var_r27->material, var_r29 = 0; var_r29 < var_r27->materialCnt; var_r29++, var_r26++) {
                var_r26->flags &= 0xFFFFFFFD;
            }
            if (work->unk_6C != -1) {
                HuAudFXStop(work->unk_6C);
            }
            work->unk_6C = -1;
            if (work->unk_04 == 0) {
                work->unk_6C = HuAudFXPlay(0x67C);
            }
            else {
                work->unk_6C = HuAudFXPlay(0x67D);
            }
            if (work->unk_6C != -1) {
                HuAudFXPitchSet(work->unk_6C, -0x2000);
            }
            work->unk_28 = 0.0f;
            object->trans.y = 200.0f;
            object->rot.z = 180.0f;
        }
        object->trans.x *= -1.0f;
        work->unk_18 *= -1.0f;
        object->trans.x = work->unk_18;
        object->trans.z = 0.0f;
        object->rot.x = 0.0f;
        object->rot.y = 180.0f;
        work->unk_1C = 180.0f;
        work->unk_20 = object->trans.y;
        lbl_1_bss_158 = 0;
        object->func = fn_1_D2D0;
    }
}

void fn_1_D2D0(omObjData *object)
{
    s32 spC;
    s32 sp8;
    float var_f31;
    M430PlayerWork *work;
    s32 var_r29;
    M430PlayerBss174Struct *var_r28;

    work = object->data;
    spC = 0;
    sp8 = -1;
    var_r28 = &lbl_1_bss_174[work->unk_04];
    if ((lbl_1_bss_15C == 0) && (fn_1_4070() >= 2)) {
        fn_1_12DF0(1);
    }
    if (lbl_1_bss_17C != 0) {
        Hu3DModelCameraSet(object->model[0], 3);
        Hu3DModelCameraSet(object->model[1], 3);
        if (object->model[2] != -1) {
            Hu3DModelCameraSet(object->model[2], 3);
        }
    }
    else {
        if (work->unk_04 == 0) {
            var_r29 = 1;
        }
        else {
            var_r29 = 2;
        }
        Hu3DModelCameraSet(object->model[0], var_r29);
        Hu3DModelCameraSet(object->model[1], var_r29);
        if (object->model[2] != -1) {
            Hu3DModelCameraSet(object->model[2], var_r29);
        }
    }
    if (fn_1_4070() == 2) {
        work->unk_40 = HuPadBtn[work->unk_06];
        work->unk_44 = HuPadBtnDown[work->unk_06];
        work->unk_48 = HuPadStkX[work->unk_06];
        work->unk_4C = HuPadStkY[work->unk_06];
    }
    else {
        work->unk_40 = 0;
        work->unk_44 = 0;
        work->unk_48 = 0.0f;
        work->unk_4C = 0.0f;
    }
    if (fn_1_4070() < 2) {
        work->unk_1C = 180.0f;
        work->unk_28 = 0.0f;
        object->trans.x = work->unk_18;
        object->rot.y = 180.0f;
    }
    if (work->unk_0C == 0) {
        fn_1_D828(object);
        var_f31 = (work->unk_24 - 12.500001f) / 28.500004f;
        work->unk_68 = 80.0f + (47.0f * var_f31);
        if (work->unk_60 != -1) {
            HuAudFXVolSet(work->unk_60, work->unk_68);
        }
        if (work->unk_64 != -1) {
            HuAudFXPitchSet(work->unk_64, (s32)(8192.0f * (work->unk_68 / 127.0f)));
        }
    }
    else {
        fn_1_E8FC(object);
        var_f31 = (var_r28->unk_1C - 12.500001f) / 28.500004f;
        var_f31 = 8192.0f + (-16384.0f * (1.0f - var_f31));
        if (work->unk_6C != -1) {
            HuAudFXPitchSet(work->unk_6C, var_f31);
        }
    }
    if (fn_1_4070() == 3) {
        fn_1_40D0(work->unk_00);
        work->unk_5C = 0;
        return;
    }
    if (fn_1_4070() == 4) {
        work->unk_0E = 2;
        work->unk_10 = 0;
        if (work->unk_0C == 0) {
            work->unk_58 = 4;
        }
        else {
            work->unk_58 = 1;
        }
        CharModelMotionSet(work->unk_38, object->motion[work->unk_58]);
        Hu3DModelCameraSet(object->model[0], 1);
        Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
        if ((object->model[1] != -1) && (work->unk_0C != 0)) {
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
        }
        if (work->unk_60 != -1) {
            HuAudFXStop(work->unk_60);
        }
        if (work->unk_64 != -1) {
            HuAudFXStop(work->unk_64);
        }
        work->unk_60 = work->unk_64 = -1;
        if (work->unk_6C != -1) {
            HuAudFXStop(work->unk_6C);
        }
        if (object->model[2] != -1) {
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
        }
        fn_1_105B8(work->unk_04);
        fn_1_11314(work->unk_04);
        fn_1_11B94(work->unk_04);
        fn_1_12550(work->unk_04);
        object->func = fn_1_F0D8;
    }
}

void fn_1_D828(omObjData *var_r30)
{
    Mtx sp20;
    Vec sp14;
    Vec sp8;
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
    float var_f18;
    M430PlayerWork *var_r31;
    M430PlayerBss174Struct *var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r31 = var_r30->data;
    var_r27 = -1;
    var_r29 = &lbl_1_bss_174[var_r31->unk_04];
    if ((fn_1_4070() == 2) && (var_r31->unk_08 != 0)) {
        fn_1_F6A0(var_r30);
    }
    mtxRot(sp20, var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
    sp20[1][0] *= var_r30->scale.y;
    sp20[1][1] *= var_r30->scale.y;
    sp20[1][2] *= var_r30->scale.z;
    var_r30->trans.y = 0.3f * (100.0f * (var_r31->unk_24 / 41.000004f));
    if (var_r30->trans.y < 0.0f) {
        var_r30->trans.y *= -0.5f;
    }
    var_f27 = 15.0f * (var_r31->unk_24 / 41.000004f);
    if (var_r31->unk_24 < 0.0f) {
        var_f27 *= -0.5f;
    }
    switch (var_r31->unk_0E) {
        case 0:
            var_r31->unk_12 = var_r31->unk_34 + (frand() & 7) + var_r31->unk_12;
            var_r31->unk_14 = var_r31->unk_34 + (frand() & 7) + var_r31->unk_14;
            var_r30->rot.x = (2.5 * sind(var_r31->unk_12)) - var_f27;
            var_r30->rot.z = 2.0 * cosd(var_r31->unk_14);
            for (var_r28 = 0; var_r28 < 8; var_r28++) {
                sp14.x = lbl_1_data_1F8[var_r28].x;
                sp14.y = lbl_1_data_1F8[var_r28].y;
                sp14.z = lbl_1_data_1F8[var_r28].z;
                fn_1_133DC(&sp20[0], &sp14);
                var_f31 = var_r31->unk_70 * sind(var_r30->rot.y);
                var_f29 = var_r31->unk_70 * cosd(var_r30->rot.y);
                if (fn_1_110A8(
                        var_r31->unk_04, var_f31 + (sp14.x + var_r30->trans.x), sp14.y + var_r30->trans.y, var_f29 + (sp14.z + var_r30->trans.z), 1)
                    != 0) {
                    break;
                }
            }
            if (var_r28 < 8) {
                var_r31->unk_58 = 3;
                CharModelMotionShiftSet(var_r31->unk_38, var_r30->motion[var_r31->unk_58], 0.0f, 10.0f, 0);
                var_r31->unk_0E = 1;
                var_r31->unk_10 = 0;
                if (var_r31->unk_04 == 0) {
                    HuAudFXPlay(0x678);
                }
                else {
                    HuAudFXPlay(0x67E);
                }
                HuAudCharVoicePlay(var_r31->unk_38, 0x123);
                omVibrate(var_r31->unk_00, 0xC, 4, 2);
                var_r31->unk_2C = 5.0f;
                var_r31->unk_16 = frand() & 3;
            }
            break;
        case 1:
            var_r31->unk_34 = 1;
            var_r31->unk_44 = 0;
            var_r31->unk_48 = 0.0f;
            var_r31->unk_12 = var_r31->unk_34 + (frand() & 7) + var_r31->unk_12;
            var_r31->unk_14 = var_r31->unk_34 + (frand() & 7) + var_r31->unk_14;
            var_r30->rot.x = (2.5 * sind(var_r31->unk_12)) - var_f27;
            var_r30->rot.z = 2.0 * cosd(var_r31->unk_14);
            var_r31->unk_2C = 5.0f - (5.0f * (0.011111111f * var_r31->unk_10));
            var_f25 = 7.0 * (var_r31->unk_2C * sind((10.0f * var_r31->unk_10)));
            if ((var_r31->unk_16 & 1) != 0) {
                var_r30->rot.x += var_f25;
            }
            else {
                var_r30->rot.x -= var_f25;
            }
            if ((var_r31->unk_16 & 2) != 0) {
                var_r30->rot.z += var_f25;
            }
            else {
                var_r30->rot.z -= var_f25;
            }
            if ((var_r31->unk_10 & 1) != 0) {
                Hu3DModelAttrSet(var_r30->model[0], HU3D_ATTR_DISPOFF);
            }
            else {
                Hu3DModelAttrReset(var_r30->model[0], HU3D_ATTR_DISPOFF);
            }
            if (++var_r31->unk_10 >= 90.0f) {
                var_r31->unk_0E = 0;
                var_r31->unk_10 = 0;
                Hu3DModelAttrReset(var_r30->model[0], HU3D_ATTR_DISPOFF);
            }
            break;
    }
    var_f24 = var_r31->unk_48;
    var_f23 = var_f24;
    if (fabs2(var_f23) < 8.0) {
        var_f24 = 0.0f;
    }
    var_r31->unk_28 *= 0.98f;
    var_r31->unk_28 += 0.0017499999f * var_f24;
    if (var_r31->unk_28 < -8.75f) {
        var_r31->unk_28 = -8.75f;
    }
    else if (var_r31->unk_28 > 8.75f) {
        var_r31->unk_28 = 8.75f;
    }
    var_r30->trans.x += var_r31->unk_28;
    var_f26 = 180.0f - (30.0f * (0.015625f * var_f24));
    var_r31->unk_1C = fn_1_13154(var_f26, var_r31->unk_1C, 1.0f);
    var_r30->rot.y = var_r31->unk_1C;
    if (var_r30->trans.x > (350.0f + var_r31->unk_18)) {
        var_r30->trans.x = 350.0f + var_r31->unk_18;
    }
    else if (var_r30->trans.x < (var_r31->unk_18 - 350.0f)) {
        var_r30->trans.x = var_r31->unk_18 - 350.0f;
    }
    if (var_r31->unk_0E == 0) {
        if ((var_r31->unk_48 > 8.0f) && (var_r30->rot.y < 170.0f)) {
            var_r27 = 1;
        }
        else if ((var_r31->unk_48 < -8.0f) && (var_r30->rot.y > 190.0f)) {
            var_r27 = 2;
        }
        else {
            var_r27 = 0;
        }
        if ((var_r27 != -1) && (var_r31->unk_58 != var_r27) && (CharModelMotionShiftIDGet(var_r31->unk_38) < 0)) {
            var_r31->unk_58 = var_r27;
            CharModelMotionShiftSet(var_r31->unk_38, var_r30->motion[var_r31->unk_58], 0.0f, 10.0f, 0);
        }
    }
    if ((var_r31->unk_44 & 0x100) != 0) {
        var_r31->unk_34++;
    }
    else if ((var_r31->unk_44 & 0x200) != 0) {
        var_r31->unk_34--;
    }
    if (var_r31->unk_34 < 1) {
        var_r31->unk_34 = 1;
    }
    else if (var_r31->unk_34 > 3) {
        var_r31->unk_34 = 3;
    }
    switch (var_r31->unk_34) {
        case 1:
            var_f30 = 12.500001f;
            (void)var_f30;
            break;
        case 2:
            var_f30 = 27.916668f;
            (void)var_f30;
            break;
        default:
            var_f30 = 41.000004f;
            break;
    }
    if (fabs(var_f30 - var_r31->unk_24) < 1.6666667461395264) {
        var_r31->unk_24 = var_f30;
    }
    else if (var_f30 > var_r31->unk_24) {
        var_r31->unk_24 += 1.6666667f;
    }
    else {
        var_r31->unk_24 -= 1.6666667f;
    }
    var_r30->trans.z -= var_r31->unk_24;
    if (fn_1_4070() >= 1) {
        if ((var_r31->unk_50 -= var_r31->unk_24) < 0.0f) {
            var_r31->unk_50 = 4500.0f - (500.0f * ((frand() & 0x8F) / 128.0f));
            var_f31 = var_r31->unk_18 + lbl_1_data_1DC[frand() & 7];
            fn_1_10F24(var_r31->unk_04, var_f31, var_r30->trans.y - 100.0f, -6000.0f + var_r30->trans.z);
        }
        if ((var_r31->unk_54 -= var_r31->unk_24) < 0.0f) {
            var_r31->unk_54 = 2000.0f;
            var_f31 = var_r31->unk_18 + lbl_1_data_1DC[frand() & 7];
            if ((frand() & 1) != 0) {
                var_f26 = 350.0f;
            }
            else {
                var_f26 = 500.0f;
            }
            if (fn_1_4070() == 2) {
                fn_1_11648(var_r31->unk_04, var_f31, 50.0f + var_f26, -6000.0f + var_r30->trans.z);
            }
        }
    }
    var_r29->unk_10 = var_r30->trans.x - var_r29->unk_0C;
    var_r29->unk_0C = var_r30->trans.x;
    var_r29->unk_14 = var_r30->trans.z;
    if (lbl_1_bss_158 == 0) {
        var_r29->unk_18 = var_r30->trans.z;
    }
    var_r29->unk_1C = var_r31->unk_24;
    fn_1_7FFC(var_r31->unk_04, var_r30->trans.z);
    CenterM[var_r31->unk_04].x = var_r31->unk_18 + (0.5f * (var_r30->trans.x - var_r31->unk_18));
    CenterM[var_r31->unk_04].z = 950.0f + fn_1_7FBC(var_r31->unk_04);
    var_f31 = var_r31->unk_70 * sind(var_r30->rot.y);
    var_f31 = var_f31;
    var_f29 = var_r31->unk_70 * cosd(var_r30->rot.y);
    var_f29 = var_f29;
    if (var_r31->unk_00 == 0) {
        OSReport("X>%3.3f Z>%3.3f \n", var_f31, var_f29);
    }
    Hu3DModelPosSet(var_r30->model[1], var_r30->trans.x + var_f31, var_r30->trans.y, var_r30->trans.z + var_f29);
    Hu3DModelRotSet(var_r30->model[1], var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
    Hu3DModelPosSet(var_r30->model[2], var_r30->trans.x + var_f31, var_r30->trans.y - 150.0f, var_r30->trans.z + var_f29);
    Hu3DModelRotSet(var_r30->model[2], var_r30->rot.x, 180.0f + var_r30->rot.y, var_r30->rot.z);
    sp14.x = 0.0f;
    sp14.y = 25.0f;
    sp14.z = -100.0f;
    fn_1_133DC(sp20, &sp14);
    sp14.x += var_r30->trans.x;
    sp14.y += var_r30->trans.y;
    sp14.z += var_r29->unk_18;
    fn_1_10540(var_r31->unk_04, 0, sp14.x, sp14.y, sp14.z);
    var_f28 = var_r31->unk_24 / 41.000004f;
    if (var_f28 < 0.0) {
        var_f28 *= -1.0f;
    }
    fn_1_AEE0(var_r31->unk_04, &sp14, 180.0f + var_r30->rot.y, var_f28);
    sp8.x = var_r31->unk_28;
    sp8.y = 0.0f;
    sp8.z = -var_r31->unk_24;
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = 160.0f;
    fn_1_133DC(&sp20[0], &sp14);
    sp14.x += var_r30->trans.x;
    sp14.y += var_r30->trans.y;
    sp14.z += var_r29->unk_18;
    fn_1_B570(var_r31->unk_04, &sp14, var_r30->rot.y, var_f28, &sp8);
}

s32 lbl_1_data_2A4[2] = { 1, 2 };
Vec lbl_1_data_2AC[7] = {
    { -300.0f, 30.000002f, -150.0f },
    { -150.0f, 30.000002f, 0.0f },
    { 150.0f, 30.000002f, 0.0f },
    { 300.0f, 30.000002f, -150.0f },
    { -400.0f, 0.0f, 250.0f },
    { 380.0f, 0.0f, 300.0f },
    { 0.0f, 1.0f, 0.0f },
};
Vec2f lbl_1_data_300 = { 0.0f, 0.0f };
s32 lbl_1_data_308 = 0xFFA040FF;

void fn_1_E8FC(omObjData *object)
{
    Mtx sp3C;
    Vec sp30;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    M430PlayerWork *work;
    M430PlayerBss174Struct *var_r29;
    s32 var_r28;

    work = object->data;
    var_f27 = 180.0f;
    var_f31 = 0.0f;
    var_f29 = 0.0f;
    var_r29 = &lbl_1_bss_174[work->unk_04];
    if ((fn_1_4070() == 2) && (work->unk_08 != 0)) {
        fn_1_FC9C(object);
    }
    if ((s32)work->unk_0E != 0) {
        (void)object;
    }
    else if ((fn_1_4070() == 2) && (fn_1_117A4(work->unk_04, object->trans.x, 50.0f + object->trans.y, object->trans.z, 1) != -1)) {
        HuAudFXPlay(7);
        var_r29->unk_20++;
    }
    if (fabs(var_f28 = work->unk_48) < 8.0) {
        var_f28 = 0.0f;
    }
    work->unk_28 *= 0.98f;
    work->unk_28 += 0.002625f * var_f28;
    if (work->unk_28 < -8.75f) {
        work->unk_28 = -8.75f;
    }
    else if (work->unk_28 > 8.75f) {
        work->unk_28 = 8.75f;
    }
    var_f26 = object->trans.x;
    object->trans.x += work->unk_28;
    if (object->trans.x > (350.0f + work->unk_18)) {
        object->trans.x = 350.0f + work->unk_18;
    }
    else if (object->trans.x < (work->unk_18 - 350.0f)) {
        object->trans.x = work->unk_18 - 350.0f;
    }
    var_f30 = fabs(0.0033333334f * (object->trans.y - 200.0f));
    var_f31 = 245.0f + (-105.0f * var_f30);
    if (object->trans.x > (var_r29->unk_0C + var_f31)) {
        object->trans.x = var_r29->unk_0C + var_f31;
    }
    else if (object->trans.x < (var_r29->unk_0C - var_f31)) {
        object->trans.x = var_r29->unk_0C - var_f31;
    }
    var_f27 = 180.0f;
    work->unk_1C = var_f27 - (30.0f * (0.114285715f * (object->trans.x - var_f26)));
    object->rot.y = fn_1_13154(work->unk_1C, object->rot.y, 2.5f);
    if (fabs(fn_1_1303C(object->rot.y, 180.0f)) < 90.0) {
        object->rot.z = 0.5f * (object->rot.y - 180.0f);
    }
    else {
        object->rot.z = 0.5f * object->rot.y;
    }
    object->trans.z = 300.0f + var_r29->unk_18;
    if (var_r29->unk_1C < 18.75f) {
        var_f29 = 200.0f;
    }
    else if (var_r29->unk_1C < 33.333336f) {
        var_f29 = 350.0f;
    }
    else {
        var_f29 = 500.0f;
    }
    var_f30 = work->unk_20 - var_f29;
    if (fabs(var_f30) < 1.6666667461395264) {
        work->unk_20 = var_f29;
    }
    else if (var_f30 > 0.0f) {
        work->unk_20 -= 1.6666667f;
    }
    else if (var_f30 < 0.0f) {
        work->unk_20 += 1.6666667f;
    }
    work->unk_10 += (frand() & 3) + 1;
    object->trans.y = work->unk_20 + (0.10000000149011612 * (100.0 * sind(work->unk_10)));
    mtxRot(&sp3C[0], object->rot.x, object->rot.y, object->rot.z);
    sp3C[1][0] *= object->scale.y;
    sp3C[1][1] *= object->scale.y;
    sp3C[1][2] *= object->scale.z;
    sp30.x = 0.0f;
    sp30.y = 150.0f;
    sp30.z = 50.0f;
    fn_1_133DC(&sp3C[0], &sp30);
    for (var_r28 = 0; var_r28 < 2; var_r28++) {
        Hu3DModelPosSet(object->model[lbl_1_data_2A4[var_r28]], object->trans.x + sp30.x, object->trans.y + sp30.y, object->trans.z + sp30.z);
        Hu3DModelRotSet(object->model[lbl_1_data_2A4[var_r28]], object->rot.x, object->rot.y, object->rot.z);
    }
    sp30.x = 0.0f;
    sp30.y = 150.0f;
    sp30.z = 50.0f;
    fn_1_133DC(&sp3C[0], &sp30);
    fn_1_10540(work->unk_04, 1, object->trans.x + sp30.x, object->trans.y + sp30.y, object->trans.z + sp30.z);
    fn_1_1058C(work->unk_04, 1.0 - fabs((object->trans.x - var_r29->unk_0C) / var_f31));
}

void fn_1_F0D8(omObjData *object)
{
    float var_f31;
    float var_f30;
    M430PlayerWork *work;
    s32 var_r29;
    M430PlayerBss174Struct *var_r28;
    s32 var_r27;
    M430PlayerBss174Struct *var_r26;

    work = object->data;
    var_r28 = &lbl_1_bss_174[work->unk_04];
    var_r26 = &lbl_1_bss_174[work->unk_04 ^ 1];
    switch (work->unk_5C) {
        case 0:
            var_r27 = work->unk_0C + (work->unk_04 * 2);
            object->trans.x = lbl_1_data_2AC[var_r27].x;
            object->trans.y = lbl_1_data_2AC[var_r27].y;
            object->trans.z = lbl_1_data_2AC[var_r27].z + fn_1_7FBC(0);
            object->rot.x = object->rot.y = object->rot.z = 0.0f;
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
            CenterM[0].x = 0.0f;
            CenterM[0].z = 750.0f + object->trans.z;
            if (work->unk_0C == 0) {
                work->unk_58 = 4;
            }
            else {
                work->unk_58 = 1;
            }
            CharModelMotionSet(work->unk_38, object->motion[work->unk_58]);
            Hu3DModelShadowSet(object->model[0]);
            if (work->unk_0C == 0) {
                Hu3DModelCameraSet(object->model[1], 3);
                Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
                Hu3DModelCameraSet(object->model[2], 3);
                Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
                work->unk_1C = (180.0f + (40.0f * (0.007874016f * (frand() & 0x7F)))) - 20.0f;
                if (work->unk_04 == 0) {
                    var_r29 = 4;
                }
                else {
                    var_r29 = 5;
                }
                Hu3DModelPosSet(object->model[1], lbl_1_data_2AC[var_r29].x, lbl_1_data_2AC[var_r29].y, lbl_1_data_2AC[var_r29].z + fn_1_7FBC(0));
                Hu3DModelPosSet(
                    object->model[2], lbl_1_data_2AC[var_r29].x, lbl_1_data_2AC[var_r29].y - 150.0f, lbl_1_data_2AC[var_r29].z + fn_1_7FBC(0));
                Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
                Hu3DModelShadowSet(object->model[1]);
            }
            if (var_r28->unk_20 > 0) {
                work->unk_0E = 3;
            }
            else {
                work->unk_0E = 4;
            }
            GWPlayerCoinCollectAdd(work->unk_00, var_r28->unk_20);
            work->unk_5C++;
            break;
        case 1:
            if (fn_1_4088() == 1) {
                if (work->unk_00 == 0) {
                    if ((var_r28->unk_20 == 0) && (var_r26->unk_20 == 0)) {
                        HuAudSStreamPlay(4);
                    }
                    else {
                        HuAudSStreamPlay(1);
                    }
                }
                if (work->unk_0C == 0) {
                    if (work->unk_0E == 3) {
                        work->unk_58 = 5;
                    }
                    else {
                        work->unk_58 = 6;
                    }
                }
                else if (work->unk_0E == 3) {
                    work->unk_58 = 2;
                }
                else {
                    work->unk_58 = 3;
                }
                CharModelMotionShiftSet(work->unk_38, object->motion[work->unk_58], 0.0f, 8.0f, 0);
                if (work->unk_0E == 3) {
                    HuAudCharVoicePlay(work->unk_38, 0x122);
                }
                work->unk_10 = 0;
                work->unk_5C++;
            }
            break;
        case 2:
            if (fn_1_F62C(object) != 0) {
                fn_1_4100(work->unk_00);
                work->unk_5C++;
            }
            break;
    }
    if (work->unk_0C == 0) {
        var_f31 = -10.0f;
        var_f30 = 0.0f;
        Hu3DModelRotSet(object->model[1], var_f31, work->unk_1C, var_f30);
        Hu3DModelRotSet(object->model[2], var_f31, work->unk_1C, var_f30);
    }
}

s32 fn_1_F62C(omObjData *object)
{
    M430PlayerWork *work = object->data;
    s32 var_r30 = 0;
    if ((CharModelMotionEndCheck(work->unk_38) != 0) && (CharModelMotionShiftIDGet(work->unk_38) < 0)) {
        var_r30 = 1;
    }
    return var_r30;
}

void fn_1_F6A0(omObjData *object)
{
    Vec sp38;
    float sp30;
    float sp28;
    float sp20;
    float sp18;
    float sp10;
    float sp8;
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
    float var_f18;
    M430PlayerWork *work;
    s32 var_r29;
    s32 var_r28;
    M430PlayerBss168Struct *var_r27;
    M430PlayerBss174Struct *var_r26;
    s32 var_r25;
    s32 var_r24;

    work = object->data;
    var_r28 = 3;
    var_r26 = &lbl_1_bss_174[work->unk_04];
    if (var_r26->unk_08 != 3) {
        work->unk_0A = 3;
    }
    if (--work->unk_74 < 0) {
        work->unk_7C = 150.0f * (3 - work->unk_0A) * ((frand() & 0x7F) / 127.0f);
        if ((frand() & 1) != 0) {
            work->unk_7C *= -1.0f;
        }
        work->unk_74 = 0x1E + (frand() % 30) + (4 - work->unk_0A) * 0x3C;
    }
    switch (work->unk_34) {
        case 1:
            var_f27 = 500.0f;
            break;
        case 2:
            var_f27 = 1500.0f;
            break;
        default:
            var_f27 = 3000.0f;
            break;
    }
    var_r25 = fn_1_111BC(work->unk_04, object->trans.z, &sp38);
    var_f30 = sp38.x;
    var_f25 = sp38.z;
    var_r29 = fn_1_11A1C(work->unk_04, object->trans.z, &sp38);
    var_f29 = sp38.x;
    var_f28 = sp38.z;
    if (var_r29 == work->unk_78) {
        var_r29 = fn_1_11A1C(work->unk_04, 100.0f + var_f28, &sp38);
        var_f29 = sp38.x;
        var_f28 = sp38.z;
    }
    else if (work->unk_78 == -1) {
        var_r24 = fn_1_11A1C(work->unk_04, 100.0f + var_f28, &sp38);
        var_f26 = sp38.x;
        if (work->unk_0A >= 2) {
            if (fabs(var_f29 - object->trans.x) > 300.0) {
                if (fabs(var_f26 - object->trans.x) < 300.0) {
                    if ((fabs(var_f28 - object->trans.z) < 1800.0) && (work->unk_34 == 3)) {
                        work->unk_78 = var_r29;
                        var_r29 = var_r24;
                        var_f29 = var_f26;
                    }
                }
            }
        }
    }
    else {
        work->unk_78 = -1;
    }
    if (fabs(var_f25 - object->trans.z) < var_f27) {
        if (var_f30 > object->trans.x) {
            var_f31 = var_f30 - 200.0f;
        }
        else {
            var_f31 = 200.0f + var_f30;
        }
    }
    else {
        if ((fabs(var_f30 - var_f29) > 200.0) || (var_r25 == -1)) {
            var_f31 = var_f29;
        }
        else if ((var_f30 > var_f29) || (var_f30 > (250.0f + work->unk_18))) {
            var_f31 = var_f30 - 200.0f;
        }
        else {
            var_f31 = 200.0f + var_f30;
        }
    }
    var_f31 += work->unk_7C;
    if (var_f31 > (350.0f + work->unk_18)) {
        var_f31 = 350.0f + work->unk_18;
    }
    else if (var_f31 < (work->unk_18 - 350.0f)) {
        var_f31 = work->unk_18 - 350.0f;
    }
    if (var_r29 != -1) {
        var_f31 -= object->trans.x;
        if (var_f31 > 30.000002f) {
            work->unk_48 = 64.0f;
        }
        else if (var_f31 < -30.000002f) {
            work->unk_48 = -64.0f;
        }
        var_r27 = fn_1_11B64(var_r29);
        if (var_r27 != NULL) {
            if (var_r27->unk_14.y > 450.0f) {
                var_r28 = 3;
            }
            else {
                var_r28 = 2;
            }
        }
        if (var_r28 > work->unk_34) {
            work->unk_44 |= 0x100;
            return;
        }
        if (var_r28 < work->unk_34) {
            work->unk_44 |= 0x200;
        }
    }
    else if (var_r28 > work->unk_34) {
        work->unk_44 |= 0x100;
    }
}

void fn_1_FC9C(omObjData *object)
{
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    M430PlayerWork *work;
    s32 var_r29;
    M430PlayerBss174Struct *var_r28;
    s32 var_r27;

    work = object->data;
    var_r28 = &lbl_1_bss_174[work->unk_04];
    if (var_r28->unk_08 != 3) {
        work->unk_0A = 3;
    }
    if (--work->unk_74 < 0) {
        work->unk_7C = 75.0f * (3 - work->unk_0A) * ((frand() & 0x7F) / 127.0f);
        if ((frand() & 1) != 0) {
            work->unk_7C *= -1.0f;
        }
        work->unk_74 = 0x1E + (frand() % 60) + (4 - work->unk_0A) * 0x3C;
    }
    var_r29 = fn_1_11A1C(work->unk_04, object->trans.z, &sp8);
    var_f31 = sp8.x;
    var_f30 = sp8.z;
    if (var_r29 == work->unk_78) {
        var_r29 = fn_1_11A1C(work->unk_04, 100.0f + var_f30, &sp8);
        var_f31 = sp8.x;
        var_f30 = sp8.z;
    }
    else if (work->unk_78 == -1) {
        var_r27 = fn_1_11A1C(work->unk_04, 100.0f + var_f30, &sp8);
        var_f29 = sp8.x;
        if (work->unk_0A >= 2) {
            if (fabs(var_f31 - object->trans.x) > 300.0) {
                if (fabs(var_f29 - object->trans.x) < 300.0) {
                    if ((fabs(var_f30 - object->trans.z) < 1800.0) && (work->unk_34 == 3)) {
                        work->unk_78 = var_r29;
                        var_r29 = var_r27;
                        var_f31 = var_f29;
                    }
                }
            }
        }
    }
    else {
        work->unk_78 = -1;
    }
    var_f31 += work->unk_7C;
    if (var_f31 > (350.0f + work->unk_18)) {
        var_f31 = 350.0f + work->unk_18;
    }
    else if (var_f31 < (work->unk_18 - 350.0f)) {
        var_f31 = work->unk_18 - 350.0f;
    }
    if (var_r29 != -1) {
        var_f31 -= object->trans.x;
        if (var_f31 > 30.000002f) {
            work->unk_48 = 64.0f;
            return;
        }
        if (var_f31 < -30.000002f) {
            work->unk_48 = -64.0f;
        }
    }
}

void fn_1_100A0(void)
{
    M430PlayerBss170Struct *var_r31;
    ModelData *var_r30;
    s32 var_r29;
    s32 var_r28;
    void *var_r27;
    void *var_r26;

    var_r31 = lbl_1_bss_170 = HuMemDirectMallocNum(HEAP_SYSTEM, 2 * sizeof(M430PlayerBss170Struct), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 2 * sizeof(M430PlayerBss170Struct));
    for (var_r28 = 0; var_r28 < 2; var_r31++) {
        var_r31->unk_00 = var_r28;
        var_r31->unk_04 = Hu3DHookFuncCreate(fn_1_10948);
        Hu3DModelLayerSet(var_r31->unk_04, 6);
        Hu3DModelCameraSet(var_r31->unk_04, 3);
        var_r30 = &Hu3DData[var_r31->unk_04];
        var_r30->unk_120 = var_r31;
        var_r31->unk_08 = 1;
        var_r31->unk_0C = 0.0f;
        var_r31->unk_10 = var_r31->unk_14 = var_r31->unk_18 = 0.0f;
        var_r31->unk_1C = var_r31->unk_20 = var_r31->unk_24 = 500.0f;
        var_r31->unk_28 = var_r31->unk_2C = var_r31->unk_30 = 1000.0f;
        var_r31->unk_34 = var_r31->unk_38 = var_r31->unk_3C = 0.0f;
        var_r31->unk_40 = var_r31->unk_44 = var_r31->unk_48 = 1000.0f;
        var_r31->unk_58 = 0;
        var_r31->unk_4C = HuMemDirectMallocNum(HEAP_SYSTEM, 0xC0, MEMORY_DEFAULT_NUM);
        memset(var_r31->unk_4C, 0, 0xC0);
        var_r31->unk_50 = HuMemDirectMallocNum(HEAP_SYSTEM, 0xC0, MEMORY_DEFAULT_NUM);
        memset(var_r31->unk_50, 0, 0xC0);
        var_r31->unk_54 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x80, MEMORY_DEFAULT_NUM);
        memset(var_r31->unk_54, 0, 0x80);
        var_r30 = &Hu3DData[var_r31->unk_04];
        var_r27 = HuMemDirectMallocNum(HEAP_DATA, 0x200, var_r30->unk_48);
        var_r26 = var_r27;
        DCFlushRange(var_r27, 0x200);
        GXBeginDisplayList(var_r26, 0x200);
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 0x10);
        for (var_r29 = 0; var_r29 < 0x10; var_r29++) {
            GXUnknownu16(var_r29);
            GXUnknownu16(0);
            GXUnknownu16(var_r29);
        }
        var_r31->unk_5C = GXEndDisplayList();
        var_r31->unk_60 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_5C, var_r30->unk_48);
        memcpy(var_r31->unk_60, var_r27, var_r31->unk_5C);
        DCFlushRange(var_r31->unk_60, var_r31->unk_5C);
        HuMemDirectFree(var_r27);
        fn_1_1061C(var_r31);
        var_r28++;
    }
}

void fn_1_1033C(void)
{
    float var_f31;
    M430PlayerBss170Struct *var_r31;
    s32 var_r30;
    s32 var_r29;

    for (var_r31 = lbl_1_bss_170, var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        if (var_r31->unk_08 != 0) {
            var_r31->unk_34 = var_r31->unk_38 = var_r31->unk_3C = 0.0f;
            var_r31->unk_40 = var_r31->unk_28 - var_r31->unk_10;
            var_r31->unk_44 = var_r31->unk_2C - var_r31->unk_14;
            var_r31->unk_48 = var_r31->unk_30 - var_r31->unk_18;
            var_f31 = 0.5f * (var_r31->unk_34 + var_r31->unk_40);
            var_r31->unk_1C = var_f31 + (var_r31->unk_0C * (var_r31->unk_40 - var_f31));
            var_f31 = 0.5f * (var_r31->unk_38 + var_r31->unk_44);
            var_r31->unk_20 = var_f31 + (var_r31->unk_0C * (var_r31->unk_38 - var_f31));
            var_f31 = 0.5f * (var_r31->unk_3C + var_r31->unk_48);
            var_r31->unk_24 = var_f31 + (var_r31->unk_0C * (var_r31->unk_3C - var_f31));
            for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
                var_f31 = var_r30 / 15.0f;
                if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                fn_1_12F20(var_f31, &var_r31->unk_34, &var_r31->unk_1C, &var_r31->unk_40, (float *)&var_r31->unk_4C[var_r30]);
            }
            fn_1_1061C(var_r31);
            Hu3DModelPosSet(var_r31->unk_04, var_r31->unk_10, var_r31->unk_14, var_r31->unk_18);
        }
    }
}

void fn_1_1053C(void) { }

void fn_1_10540(s32 arg0, s32 arg1, float arg8, float arg9, float argA)
{
    M430PlayerBss170Struct *var_r31 = &lbl_1_bss_170[arg0];
    if (arg1 == 0) {
        var_r31->unk_10 = arg8;
        var_r31->unk_14 = arg9;
        var_r31->unk_18 = argA;
        return;
    }
    var_r31->unk_28 = arg8;
    var_r31->unk_2C = arg9;
    var_r31->unk_30 = argA;
}

void fn_1_1058C(s32 arg0, float arg8)
{
    M430PlayerBss170Struct *var_r31 = &lbl_1_bss_170[arg0];
    var_r31->unk_0C = arg8;
}

void fn_1_105B8(s32 arg0)
{
    M430PlayerBss170Struct *var_r31 = &lbl_1_bss_170[arg0];
    if (var_r31->unk_08 != 0) {
        Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
    }
    var_r31->unk_08 = 0;
}

void fn_1_1061C(M430PlayerBss170Struct *var_r31)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f27;
    float var_f25;
    s32 var_r30;

    var_f27 = 0.0f;
    for (var_r30 = 0xF; var_r30 >= 0; var_r30--) {
        var_r31->unk_50[var_r30] = var_r31->unk_4C[var_r30];
        var_r31->unk_54[var_r30] = lbl_1_data_300;
        if (var_r30 == 0) {
            var_f27 = 0.0f;
            var_r31->unk_54[var_r30].y = var_f27;
        }
        else {
            var_f31 = var_r31->unk_4C[var_r30 - 1].x - var_r31->unk_4C[var_r30].x;
            var_f30 = var_r31->unk_4C[var_r30 - 1].y - var_r31->unk_4C[var_r30].y;
            var_f29 = var_r31->unk_4C[var_r30 - 1].z - var_r31->unk_4C[var_r30].z;
            var_f25 = sqrtf((var_f29 * var_f29) + ((var_f31 * var_f31) + (var_f30 * var_f30)));
            var_f27 -= 0.01f * var_f25;
            var_r31->unk_54[var_r30].y = var_f27;
        }
    }
    DCFlushRangeNoSync(var_r31->unk_50, 0xC0);
    DCFlushRangeNoSync(var_r31->unk_54, 0x80);
    PPCSync();
}

void fn_1_10948(ModelData *var_r29, Mtx var_r30)
{
    Mtx sp8;
    M430PlayerBss170Struct *var_r31 = var_r29->unk_120;
    GXLoadPosMtxImm(var_r30, 0);
    PSMTXInvXpose(var_r30, sp8);
    GXLoadNrmMtxImm(sp8, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0, 0x7D);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVREG0);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_SPEC);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetLineWidth(0x10, GX_TO_ZERO);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXSetArray(GX_VA_POS, var_r31->unk_50, 0xC);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, &lbl_1_data_308, 4);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetArray(GX_VA_TEX0, var_r31->unk_54, 8);
    GXCallDisplayList(var_r31->unk_60, var_r31->unk_5C);
}

void fn_1_10B88(void)
{
    M430PlayerBss16CStruct *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_16C = HuMemDirectMallocNum(HEAP_SYSTEM, 0x10 * sizeof(M430PlayerBss16CStruct), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 0x10 * sizeof(M430PlayerBss16CStruct));
    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        var_r31->unk_00 = var_r30;
        if (var_r30 == 0) {
            var_r31->unk_04 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M430, 0x23));
        }
        else {
            var_r31->unk_04 = Hu3DModelLink(lbl_1_bss_16C[0].unk_04);
        }
        Hu3DModelLayerSet(var_r31->unk_04, 2);
        Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
        var_r31->unk_08 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M430, 0x24));
        Hu3DModelLayerSet(var_r31->unk_08, 2);
        Hu3DModelAttrSet(var_r31->unk_08, HU3D_ATTR_DISPOFF);
        var_r31->unk_0C = 0;
        var_r31->unk_10 = 0;
        var_r31->unk_14 = 0;
        var_r31->unk_18 = 0.0f;
        var_r31->unk_1C.x = var_r31->unk_1C.y = var_r31->unk_1C.z = 0.0f;
        var_r31->unk_28 = var_r31->unk_2C = var_r31->unk_30 = 0.0f;
        var_r31->unk_34 = var_r31->unk_38 = var_r31->unk_3C = 1.0f;
    }
}

void fn_1_10D1C(void)
{
    M430PlayerBss16CStruct *var_r31;
    s32 var_r30;
    M430PlayerBss174Struct *var_r29;

    for (var_r31 = lbl_1_bss_16C, var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (var_r31->unk_10 != 0) {
            var_r29 = &lbl_1_bss_174[var_r31->unk_0C];
            switch (var_r31->unk_10) {
                case 1:
                    if (var_r31->unk_1C.y < 0.0f) {
                        var_r31->unk_1C.y += 1.0f;
                    }
                    break;
                case 2:
                    Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(var_r31->unk_08, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(var_r31->unk_08, 0.0f);
                    Hu3DMotionSpeedSet(var_r31->unk_08, 1.0f);
                    var_r31->unk_10 = 3;
                    break;
                case 3:
                    break;
            }
            if (var_r31->unk_1C.z > (1000.0f + var_r29->unk_14)) {
                Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(var_r31->unk_08, HU3D_ATTR_DISPOFF);
                var_r31->unk_10 = 0;
            }
            Hu3DModelPosSet(var_r31->unk_04, var_r31->unk_1C.x, var_r31->unk_1C.y, var_r31->unk_1C.z);
            Hu3DModelRotSet(var_r31->unk_04, var_r31->unk_28, var_r31->unk_2C, var_r31->unk_30);
            Hu3DModelScaleSet(var_r31->unk_04, var_r31->unk_34, var_r31->unk_38, var_r31->unk_3C);
            Hu3DModelPosSet(var_r31->unk_08, var_r31->unk_1C.x, var_r31->unk_1C.y, var_r31->unk_1C.z);
            Hu3DModelRotSet(var_r31->unk_08, var_r31->unk_28, var_r31->unk_2C, var_r31->unk_30);
            Hu3DModelScaleSet(var_r31->unk_08, var_r31->unk_34, var_r31->unk_38, var_r31->unk_3C);
        }
    }
}

void fn_1_10F20(void) { }

s32 fn_1_10F24(s32 var_r29, float sp8, float spC, float sp10)
{
    M430PlayerBss16CStruct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_16C, var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (var_r31->unk_10 == 0) {
            break;
        }
    }
    if (var_r30 >= 0x10) {
        return -1;
    }
    if (var_r29 == 0) {
        Hu3DModelCameraSet(var_r31->unk_04, 1);
        Hu3DModelCameraSet(var_r31->unk_08, 1);
    }
    else {
        Hu3DModelCameraSet(var_r31->unk_04, 2);
        Hu3DModelCameraSet(var_r31->unk_08, 2);
    }
    Hu3DModelAttrReset(var_r31->unk_04, HU3D_ATTR_DISPOFF);
    var_r31->unk_0C = var_r29;
    var_r31->unk_10 = 1;
    var_r31->unk_14 = 0;
    var_r31->unk_1C.x = sp8;
    var_r31->unk_1C.y = spC;
    var_r31->unk_1C.z = sp10;
    var_r31->unk_28 = var_r31->unk_2C = var_r31->unk_30 = 0.0f;
    var_r31->unk_34 = var_r31->unk_38 = var_r31->unk_3C = 1.0f;
    Hu3DModelPosSet(var_r31->unk_04, var_r31->unk_1C.x, var_r31->unk_1C.y, var_r31->unk_1C.z);
    Hu3DModelRotSet(var_r31->unk_04, var_r31->unk_28, var_r31->unk_2C, var_r31->unk_30);
    Hu3DModelScaleSet(var_r31->unk_04, var_r31->unk_34, var_r31->unk_38, var_r31->unk_3C);
}

s32 fn_1_110A8(s32 arg0, float arg8, float arg9, float argA, s32 arg1)
{
    float var_f31;
    float var_f30;
    M430PlayerBss16CStruct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_16C, var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        if ((var_r31->unk_10 == 1) && (var_r31->unk_0C == arg0)) {
            var_f31 = arg8 - var_r31->unk_1C.x;
            var_f30 = argA - var_r31->unk_1C.z;
            if ((fabs(var_f31) < 50.0) && (fabs(var_f30) < 50.0)) {
                break;
            }
        }
    }
    if (var_r30 >= 0x20) {
        return 0;
    }
    if (arg1 != 0) {
        var_r31->unk_18 = 50.0f;
        var_r31->unk_10 = 2;
        var_r31->unk_14 = 0;
    }
    return 1;
}

s32 fn_1_111BC(s32 arg0, float arg8, Vec *arg1)
{
    float var_f31;
    float var_f30;
    M430PlayerBss16CStruct *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = lbl_1_bss_16C;
    var_r29 = -1;
    var_f31 = 10000.0f;
    arg1->x = arg1->y = arg1->z = 0.0f;
    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if ((var_r31->unk_10 == 1) && (var_r31->unk_0C == arg0) && !(var_r31->unk_1C.z > arg8)) {
            var_f30 = fabs(var_r31->unk_1C.z - (arg8 - 100.0f));
            if (var_f30 < var_f31) {
                var_f31 = var_f30;
                var_r29 = var_r30;
            }
        }
    }
    if (var_r29 == -1) {
        return -1;
    }
    var_r31 = &lbl_1_bss_16C[var_r29];
    *arg1 = var_r31->unk_1C;
    return var_r29;
}

void fn_1_11314(s32 arg0)
{
    M430PlayerBss16CStruct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_16C, var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if ((var_r31->unk_10 != 0) && (var_r31->unk_0C == arg0)) {
            var_r31->unk_10 = 0;
            Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(var_r31->unk_08, HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_1_113AC(void)
{
    M430PlayerBss168Struct *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_168 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x20 * sizeof(M430PlayerBss168Struct), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 0x20 * sizeof(M430PlayerBss168Struct));
    for (var_r30 = 0; var_r30 < 0x20; var_r31++) {
        var_r31->unk_00 = var_r30;
        if (var_r30 == 0) {
            var_r31->unk_04 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M430, 0x22));
        }
        else {
            var_r31->unk_04 = Hu3DModelLink(lbl_1_bss_168[0].unk_04);
        }
        Hu3DModelLayerSet(var_r31->unk_04, 7);
        Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
        var_r31->unk_08 = 0;
        var_r31->unk_0C = 0;
        var_r31->unk_10 = 0;
        var_r31->unk_14.x = var_r31->unk_14.y = var_r31->unk_14.z = 0.0f;
        var_r31->unk_20.x = var_r31->unk_20.y = var_r31->unk_20.z = 0.0f;
        var_r31->unk_2C.x = var_r31->unk_2C.y = var_r31->unk_2C.z = 1.0f;
        var_r30++;
    }
}

void fn_1_114F0(void)
{
    M430PlayerBss168Struct *var_r31;
    s32 var_r30;
    M430PlayerBss174Struct *var_r29;

    for (var_r31 = lbl_1_bss_168, var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        if (var_r31->unk_0C != 0) {
            switch (var_r31->unk_0C) {
                case 1:
                    var_r31->unk_20.y += 7.5;
                    break;
                case 2:
                    Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
                    var_r31->unk_0C = 0;
                    break;
            }
            var_r29 = &lbl_1_bss_174[var_r31->unk_08];
            if (var_r31->unk_14.z > (1000.0f + var_r29->unk_14)) {
                Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
                var_r31->unk_0C = 0;
            }
            else {
                Hu3DModelPosSet(var_r31->unk_04, var_r31->unk_14.x, var_r31->unk_14.y, var_r31->unk_14.z);
                Hu3DModelRotSet(var_r31->unk_04, var_r31->unk_20.x, var_r31->unk_20.y, var_r31->unk_20.z);
                Hu3DModelScaleSet(var_r31->unk_04, var_r31->unk_2C.x, var_r31->unk_2C.y, var_r31->unk_2C.z);
            }
        }
    }
}

void fn_1_11644(void) { }

s32 fn_1_11648(s32 arg0, float arg1, float arg8, float arg9)
{
    M430PlayerBss168Struct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_168, var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        if (var_r31->unk_0C == 0) {
            break;
        }
    }
    if (var_r30 >= 0x20) {
        return -1;
    }
    if (arg0 == 0) {
        Hu3DModelCameraSet(var_r31->unk_04, 1);
    }
    else {
        Hu3DModelCameraSet(var_r31->unk_04, 2);
    }
    Hu3DModelAttrReset(var_r31->unk_04, HU3D_ATTR_DISPOFF);
    var_r31->unk_08 = arg0;
    var_r31->unk_0C = 1;
    var_r31->unk_14.x = arg1;
    var_r31->unk_14.y = arg8;
    var_r31->unk_14.z = arg9;
    var_r31->unk_20.x = var_r31->unk_20.y = var_r31->unk_20.z = 0.0f;
    var_r31->unk_2C.x = var_r31->unk_2C.y = var_r31->unk_2C.z = 1.0f;
    Hu3DModelPosSet(var_r31->unk_04, var_r31->unk_14.x, var_r31->unk_14.y, var_r31->unk_14.z);
    Hu3DModelRotSet(var_r31->unk_04, var_r31->unk_20.x, var_r31->unk_20.y, var_r31->unk_20.z);
    Hu3DModelScaleSet(var_r31->unk_04, var_r31->unk_2C.x, var_r31->unk_2C.y, var_r31->unk_2C.z);
}

s32 fn_1_117A4(s32 arg0, float arg8, float arg9, float argA, s32 arg1)
{
    float var_f31;
    float var_f30;
    float var_f27;
    M430PlayerBss168Struct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_168, var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        if ((var_r31->unk_0C == 1) && (var_r31->unk_08 == arg0)) {
            var_f31 = var_r31->unk_14.x - arg8;
            var_f27 = var_r31->unk_14.y - arg9;
            var_f30 = var_r31->unk_14.z - argA;
            if ((fabs(var_f27) < 100.0) && (sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) < 100.0f)) {
                break;
            }
        }
    }
    if (var_r30 >= 0x20) {
        return -1;
    }
    if (arg1 != 0) {
        fn_1_11F90(var_r31->unk_08, var_r31->unk_14.x, var_r31->unk_14.y, var_r31->unk_14.z);
        var_r31->unk_0C = 2;
        var_r31->unk_10 = 0;
    }
    return 1;
}

s32 fn_1_11A1C(s32 arg0, float arg8, Vec *arg1)
{
    float var_f31;
    float var_f30;
    M430PlayerBss168Struct *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = lbl_1_bss_168;
    var_r29 = -1;
    var_f31 = 10000.0f;
    arg1->x = arg1->y = arg1->z = 0.0f;
    for (var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        if ((var_r31->unk_0C == 1) && (var_r31->unk_08 == arg0) && !(var_r31->unk_14.z > arg8)) {
            var_f30 = fabs(var_r31->unk_14.z - arg8);
            if (var_f30 < var_f31) {
                var_f31 = var_f30;
                var_r29 = var_r30;
            }
        }
    }
    if (var_r29 == -1) {
        return -1;
    }
    var_r31 = &lbl_1_bss_168[var_r29];
    *arg1 = var_r31->unk_14;
    return var_r29;
}

M430PlayerBss168Struct *fn_1_11B64(s32 arg0)
{
    if ((arg0 < 0) || (arg0 >= 0x20)) {
        return NULL;
    }
    return &lbl_1_bss_168[arg0];
}

void fn_1_11B94(s32 arg0)
{
    M430PlayerBss168Struct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_168, var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        if ((var_r31->unk_0C != 0) && (var_r31->unk_08 == arg0)) {
            var_r31->unk_0C = 0;
            Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_1_11C1C(void)
{
    M430PlayerBss164Struct *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_164 = HuMemDirectMallocNum(HEAP_SYSTEM, 8 * sizeof(M430PlayerBss164Struct), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 8 * sizeof(M430PlayerBss164Struct));
    for (var_r30 = 0; var_r30 < 8; var_r30++, var_r31++) {
        if (var_r30 == 0) {
            var_r31->unk_14 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M430, 0x26), MEMORY_DEFAULT_NUM));
        }
        else {
            var_r31->unk_14 = lbl_1_bss_164[0].unk_14;
        }
        var_r31->unk_00 = var_r30;
        var_r31->unk_04 = Hu3DParticleCreate(var_r31[0].unk_14, 0x20);
        Hu3DModelLayerSet(var_r31->unk_04, 7);
        Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(var_r31->unk_04, HU3D_ATTR_PARTICLE_KILL);
        var_r31->unk_08 = 0;
        var_r31->unk_0C = 0;
        var_r31->unk_10 = 0;

        var_r31->unk_18.x = var_r31->unk_18.y = var_r31->unk_18.z = 0.0f;
        var_r31->unk_24.x = var_r31->unk_24.y = var_r31->unk_24.z = 0.0f;
        var_r31->unk_30.x = var_r31->unk_30.y = var_r31->unk_30.z = 1.0f;
    }
}

void fn_1_11D70(void)
{
    M430PlayerBss164Struct *var_r31;
    HsfanimStruct01 *var_r30;
    ParticleData *var_r29;
    s32 var_r28;
    s32 var_r27;
    M430PlayerBss174Struct *var_r26;
    ModelData *var_r25;
    s32 var_r24;

    for (var_r31 = lbl_1_bss_164, var_r28 = 0; var_r28 < 8; var_r28++, var_r31++) {
        if (var_r31->unk_0C != 0) {
            if (var_r31->unk_10 > 1) {
                var_r25 = &Hu3DData[var_r31->unk_04];
                var_r29 = var_r25->unk_120;
                for (var_r30 = var_r29->unk_48, var_r27 = 0; var_r27 < var_r29->unk_30; var_r27++, var_r30++) {
                    if (++var_r30->unk00_s16 > var_r30->unk02) {
                        var_r24 = var_r30->unk40.a - 9;
                        if (var_r24 < 0) {
                            var_r30->unk2C = 0.0f;
                        }
                        else {
                            var_r30->unk40.a = var_r24;
                        }
                    }
                    var_r30->unk2C *= 0.975;
                    var_r30->unk34.x += var_r30->unk08.x;
                    var_r30->unk34.y += var_r30->unk08.y;
                    var_r30->unk34.z += var_r30->unk08.z;
                    var_r30->unk08.y -= 0.3103333379576603;
                }
            }
            var_r26 = &lbl_1_bss_174[var_r31->unk_08];
            var_r31->unk_18.z -= var_r26->unk_1C;
            if (++var_r31->unk_10 > 0x78) {
                Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
                var_r31->unk_0C = 0;
            }
            else {
                Hu3DModelPosSet(var_r31->unk_04, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
                Hu3DModelRotSet(var_r31->unk_04, var_r31->unk_24.x, var_r31->unk_24.y, var_r31->unk_24.z);
                Hu3DModelScaleSet(var_r31->unk_04, var_r31->unk_30.x, var_r31->unk_30.y, var_r31->unk_30.z);
            }
        }
    }
}

void fn_1_11F60(void)
{
    fn_1_133A4(lbl_1_bss_164[0].unk_14);
}

s32 fn_1_11F90(s32 arg0, float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    M430PlayerBss164Struct *var_r31;
    HsfanimStruct01 *var_r30;
    s32 var_r29;
    ParticleData *var_r28;
    ModelData *var_r27;

    for (var_r31 = lbl_1_bss_164, var_r29 = 0; var_r29 < 8; var_r29++, var_r31++) {
        if (var_r31->unk_0C == 0) {
            break;
        }
    }
    if (var_r29 >= 8) {
        return -1;
    }
    if (arg0 == 0) {
        Hu3DModelCameraSet(var_r31->unk_04, 1);
    }
    else {
        Hu3DModelCameraSet(var_r31->unk_04, 2);
    }
    Hu3DModelAttrReset(var_r31->unk_04, HU3D_ATTR_DISPOFF);
    var_r31->unk_08 = arg0;
    var_r31->unk_0C = 1;
    var_r31->unk_10 = 0;
    var_r27 = &Hu3DData[var_r31->unk_04];
    var_r28 = var_r27->unk_120;
    var_r28->unk_2C = 1;
    for (var_r30 = var_r28->unk_48, var_r29 = 0; var_r29 < var_r28->unk_30; var_r29++, var_r30++) {
        var_f30 = (frand() % 30) + 0x4B;
        var_f29 = frand() % 360;
        var_f27 = sind(var_f30);
        var_f28 = cosd(var_f30);
        var_f26 = 0.8f + (0.3f * (0.007874016f * (frand() % 255)));
        var_f31 = 0.35f;
        var_r30->unk08.x = var_f31 * (0.6499999761581421 * (50.0 * (var_f28 * sind(var_f29))));
        var_r30->unk08.y = var_f31 * (50.0f * var_f27 * var_f26);
        var_r30->unk08.z = var_f31 * (0.6499999761581421 * (50.0 * (var_f28 * cosd(var_f29))));
        var_r30->unk00 = 0;
        var_r30->unk02 = (frand() % 7) + 0xA;
        var_r30->unk2C = 45.0f;
        var_r30->unk34.x = 0.25f * ((frand() & 0x7F) - 0x40);
        var_r30->unk34.y = 0.25f * ((frand() & 0x7F) - 0x40);
        var_r30->unk34.z = 0.25f * ((frand() & 0x7F) - 0x40);
        var_r30->unk40.r = (frand() % 64) + 0xC0;
        var_r30->unk40.g = (frand() % 64) + 0xC0;
        var_r30->unk40.b = (frand() % 64) + 0xC0;
        var_r30->unk40.a = 0xFF;
    }
    var_r31->unk_18.x = arg8;
    var_r31->unk_18.y = arg9;
    var_r31->unk_18.z = argA;
    var_r31->unk_24.x = var_r31->unk_24.y = var_r31->unk_24.z = 0.0f;
    var_r31->unk_30.x = var_r31->unk_30.y = var_r31->unk_30.z = 1.0f;
    Hu3DModelPosSet(var_r31->unk_04, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
    Hu3DModelRotSet(var_r31->unk_04, var_r31->unk_24.x, var_r31->unk_24.y, var_r31->unk_24.z);
    Hu3DModelScaleSet(var_r31->unk_04, var_r31->unk_30.x, var_r31->unk_30.y, var_r31->unk_30.z);
}

void fn_1_12550(s32 arg0)
{
    M430PlayerBss164Struct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_164, var_r30 = 0; var_r30 < 8; var_r30++, var_r31++) {
        if (var_r31->unk_0C != 0) {
            var_r31->unk_0C = 0;
            Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_1_125C4(void)
{
    M430PlayerBss160Struct *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, 2 * sizeof(M430PlayerBss160Struct), MEMORY_DEFAULT_NUM);
    lbl_1_bss_160 = var_r31;
    for (var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        if (var_r29 == 0) {
            var_r31->unk_00 = 0x90;
        }
        else {
            var_r31->unk_00 = 0x1B0;
        }
        var_r31->unk_04 = 0x198;
        var_r31->unk_08 = 0;
        var_r31->unk_0C = 0;
        var_r31->unk_B8 = 0x15;
        var_r31->unk_BC = 0;
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            switch (var_r30) {
                case 0:
                case 1:
                    var_r31->unk_10[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x33), 1, 0);
                    espPriSet(var_r31->unk_10[var_r30], 0x40);
                    var_r31->unk_28[var_r30][0] = (var_r30 * 0x14) + 0xB;
                    var_r31->unk_28[var_r30][1] = 0;
                    var_r31->unk_70[var_r30][0] = var_r31->unk_28[var_r30][0] - var_r31->unk_B8;
                    var_r31->unk_70[var_r30][1] = var_r31->unk_28[var_r30][1] - var_r31->unk_BC;
                    break;
                case 2:
                    if (var_r29 == 0) {
                        var_r31->unk_10[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x1B), 1, 0);
                    }
                    else {
                        var_r31->unk_10[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x1C), 1, 0);
                    }
                    espPriSet(var_r31->unk_10[var_r30], 0xFF);
                    var_r31->unk_28[var_r30][0] = 0;
                    var_r31->unk_28[var_r30][1] = 0;
                    break;
                case 3:
                    var_r31->unk_10[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x1D), 1, 0);
                    espPriSet(var_r31->unk_10[var_r30], 0x100);
                    espTPLvlSet(var_r31->unk_10[var_r30], 0.6000000238418579);
                    espColorSet(var_r31->unk_10[var_r30], 0, 0, 0);
                    var_r31->unk_28[var_r30][0] = 0;
                    var_r31->unk_28[var_r30][1] = 0;
                    break;
                case 4:
                    var_r31->unk_10[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x08), 1, 0);
                    espPriSet(var_r31->unk_10[var_r30], 0x80);
                    var_r31->unk_28[var_r30][0] = -0x21;
                    var_r31->unk_28[var_r30][1] = 0;
                    break;
                case 5:
                    var_r31->unk_10[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_M430, 0x28), 1, 0);
                    espPriSet(var_r31->unk_10[var_r30], 0x80);
                    espZRotSet(var_r31->unk_10[var_r30], 45.0);
                    var_r31->unk_28[var_r30][0] = -0xA;
                    var_r31->unk_28[var_r30][1] = 0;
                    break;
            }
            espDispOn(var_r31->unk_10[var_r30]);
            espDrawNoSet(var_r31->unk_10[var_r30], 0);
            espAttrSet(var_r31->unk_10[var_r30], HUSPR_ATTR_NOANIM);
            espPosSet(var_r31->unk_10[var_r30], var_r31->unk_00 + var_r31->unk_28[var_r30][0], var_r31->unk_04 + var_r31->unk_28[var_r30][1]);
            espBankSet(var_r31->unk_10[var_r30], 0);
        }
    }
    lbl_1_bss_15C = 1;
    fn_1_12DF0(0);
}

void fn_1_129CC(void)
{
    s32 sp8[4];
    float var_f31;
    float var_f30;
    float var_f29;
    M430PlayerBss160Struct *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    for (var_r31 = lbl_1_bss_160, var_r28 = 0; var_r28 < 2; var_r28++, var_r31++) {
        var_r29 = lbl_1_bss_174[var_r28].unk_20;
        if (lbl_1_bss_15C != 0) {
            if (var_r29 != var_r31->unk_08) {
                var_r31->unk_08 = var_r29;
                var_r31->unk_0C = 0x14;
            }
            if (var_r31->unk_0C != 0) {
                var_f31 = 1.0 + (0.800000011920929 * sind((180.0f * (var_r31->unk_0C / 20.0f))));
                var_r31->unk_0C--;
            }
            else {
                var_f31 = 1.0f;
            }
            if ((sp8[0] = var_r29 / 10) > 9) {
                sp8[0] = 9;
            }
            var_r29 -= sp8[0] * 0xA;
            sp8[1] = var_r29;
            if (var_r29 > 9) {
                sp8[1] = 9;
            }
            for (var_r30 = 0; var_r30 < 6; var_r30++) {
                if (var_r30 < 2) {
                    var_f30 = (var_r31->unk_00 + var_r31->unk_B8) + (var_r31->unk_70[var_r30][0] * var_f31);
                    var_f29 = (var_r31->unk_04 + var_r31->unk_BC) + (var_r31->unk_70[var_r30][1] * var_f31);
                    espBankSet(var_r31->unk_10[var_r30], sp8[var_r30]);
                    espScaleSet(var_r31->unk_10[var_r30], var_f31, var_f31);
                }
                else {
                    var_f30 = var_r31->unk_00 + var_r31->unk_28[var_r30][0];
                    var_f29 = var_r31->unk_04 + var_r31->unk_28[var_r30][1];
                }
                if (sp8[var_r30] < 0) {
                    sp8[var_r30] = 0;
                }
                espPosSet(var_r31->unk_10[var_r30], var_f30, var_f29);
            }
        }
    }
}

void fn_1_12D74(void)
{
    M430PlayerBss160Struct *var_r31;
    s32 var_r30;
    s32 var_r29;

    for (var_r31 = lbl_1_bss_160, var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            espKill(var_r31->unk_10[var_r30]);
        }
    }
}

void fn_1_12DF0(s32 arg0)
{
    M430PlayerBss160Struct *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = lbl_1_bss_160;
    lbl_1_bss_15C = arg0;
    for (var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            if (arg0 != 0) {
                espAttrReset(var_r31->unk_10[var_r30], HUSPR_ATTR_DISPOFF);
            }
            else {
                espAttrSet(var_r31->unk_10[var_r30], HUSPR_ATTR_DISPOFF);
            }
        }
    }
}

float fn_1_12EA8(float arg8, float arg9, float argA, float argB)
{
    float var_f31;
    float var_f30;

    var_f31 = 1.0 - arg8;
    var_f30 = (argB * (arg8 * arg8)) + ((arg9 * (var_f31 * var_f31)) + (2.0 * (argA * (var_f31 * arg8))));
    return var_f30;
}

void fn_1_12F20(float arg8, float *var_r3, float *var_r4, float *var_r5, float *var_r6)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        *var_r6++ = fn_1_12EA8(arg8, *var_r3++, *var_r4++, *var_r5++);
    }
}

float fn_1_1303C(float arg8, float arg9)
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

float fn_1_13154(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;
    float var_f26;

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
    else if ((360.0 - var_f30) <= argA) {
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

void fn_1_133A4(AnimData *arg0)
{
    arg0->useNum = 0;
    HuSprAnimKill(arg0);
}

void fn_1_133DC(Mtx arg0, Vec *arg1)
{
    Vec sp8;

    sp8.x = (arg0[0][2] * arg1->z) + ((arg0[0][0] * arg1->x) + (arg0[0][1] * arg1->y));
    sp8.y = (arg0[1][2] * arg1->z) + ((arg0[1][0] * arg1->x) + (arg0[1][1] * arg1->y));
    sp8.z = (arg0[2][2] * arg1->z) + ((arg0[2][0] * arg1->x) + (arg0[2][1] * arg1->y));
    *arg1 = sp8;
}
