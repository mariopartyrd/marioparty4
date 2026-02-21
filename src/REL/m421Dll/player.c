#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "string.h"

#include "REL/m421Dll.h"
#include "version.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/frand.h"
#endif

typedef struct M421DllPlayerWork {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    s32 unk_14;
    float unk_18;
    float unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    char unk30[0x4];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    char unk40[4];
    u16 unk_44;
    u32 unk_48;
    char unk4C[0x4];
    s16 unk_50;
    char unk52[6];
    float unk_58;
    float unk_5C;
    float unk_60;
    float unk_64;
    float unk_68;
    s32 unk_6C;
    u32 unk_70;
    u32 unk_74;
    s32 unk_78;
    char unk7C[4];
    float unk_80;
    float unk_84;
    float unk_88;
    float unk_8C;
    float unk_90;
    float unk_94;
    float unk_98;
    float unk_9C;
    float unk_A0;
    float unk_A4;
    float unk_A8;
    float unk_AC;
    float unk_B0;
    float unk_B4;
    u32 unk_B8;
    u32 unk_BC;
    u32 unk_C0;
    u32 unk_C4;
    s32 unk_C8;
    Vec unk_CC;
    Vec unk_D8;
    Vec unk_E4;
    Vec unk_F0;
    Vec unk_FC;
    float unk_108[4];
    Mtx unk_118;
    float *unk_148;
} M421DllPlayerWork; /* size = 0x14C */

typedef struct M421DllPlayerDLWork {
    Vec unk_00[4];
    u32 unk_30[4];
    GXColor unk_40[4];
    Vec unk_50[4][0xE];
    u32 unk_2F0;
    void *unk_2F4;
} M421DllPlayerDLWork; /* size = 0x2F8 */

typedef struct UnkData1BCStruct {
    /* 0x00 */ u16 unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ u32 unk_10;
} UnkData1BCStruct; /* size = 0x14 */

void fn_1_48D4(omObjData *object);
void fn_1_4F00(omObjData *object);
void fn_1_5060(omObjData *object);
void fn_1_53C8(omObjData *object);
void fn_1_578C(omObjData *object);
void fn_1_5B9C(omObjData *object);
void fn_1_6184(omObjData *object);
void fn_1_6400(omObjData *object);
void fn_1_66B4(omObjData *object);
void fn_1_676C(omObjData *object);
void fn_1_6D48(omObjData *object);
void fn_1_7478(omObjData *object);
void fn_1_7670(omObjData *object);
void fn_1_7AA0(omObjData *object);
void fn_1_80C0(omObjData *object);
void fn_1_893C(omObjData *object);
void fn_1_9474(omObjData *object, Vec *arg1, Vec *arg2);
void fn_1_956C(omObjData *object);
void fn_1_982C(omObjData *object, u32 arg1);
s32 fn_1_99B8(omObjData *object);
void fn_1_9BFC(float arg8, float arg9, float *arg0);
void fn_1_9C38(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_9DD0(omObjData *object, Vec *arg1);
void fn_1_A528(omObjData *object);
void fn_1_AB68(omObjData *object);
void fn_1_AB6C(ModelData *model, Mtx matrix);
void fn_1_ABDC(ModelData *model, Mtx matrix);

char *lbl_1_data_E4[8] = {
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
};

s32 lbl_1_data_104[8][3] = {
    { DATA_MAKE_NUM(DATADIR_M421, 0x06), DATA_MAKE_NUM(DATADIR_M421, 0x0E), DATA_MAKE_NUM(DATADIR_M421, 0x16) },
    { DATA_MAKE_NUM(DATADIR_M421, 0x07), DATA_MAKE_NUM(DATADIR_M421, 0x0F), DATA_MAKE_NUM(DATADIR_M421, 0x17) },
    { DATA_MAKE_NUM(DATADIR_M421, 0x08), DATA_MAKE_NUM(DATADIR_M421, 0x10), DATA_MAKE_NUM(DATADIR_M421, 0x18) },
    { DATA_MAKE_NUM(DATADIR_M421, 0x09), DATA_MAKE_NUM(DATADIR_M421, 0x11), DATA_MAKE_NUM(DATADIR_M421, 0x19) },
    { DATA_MAKE_NUM(DATADIR_M421, 0x0A), DATA_MAKE_NUM(DATADIR_M421, 0x12), DATA_MAKE_NUM(DATADIR_M421, 0x1A) },
    { DATA_MAKE_NUM(DATADIR_M421, 0x0B), DATA_MAKE_NUM(DATADIR_M421, 0x13), DATA_MAKE_NUM(DATADIR_M421, 0x1B) },
    { DATA_MAKE_NUM(DATADIR_M421, 0x0C), DATA_MAKE_NUM(DATADIR_M421, 0x14), DATA_MAKE_NUM(DATADIR_M421, 0x1C) },
    { DATA_MAKE_NUM(DATADIR_M421, 0x0D), DATA_MAKE_NUM(DATADIR_M421, 0x15), DATA_MAKE_NUM(DATADIR_M421, 0x1D) },
};
s32 lbl_1_data_164[8] = {
    DATA_MAKE_NUM(DATADIR_M421, 0x1E),
    DATA_MAKE_NUM(DATADIR_M421, 0x1F),
    DATA_MAKE_NUM(DATADIR_M421, 0x20),
    DATA_MAKE_NUM(DATADIR_M421, 0x21),
    DATA_MAKE_NUM(DATADIR_M421, 0x22),
    DATA_MAKE_NUM(DATADIR_M421, 0x23),
    DATA_MAKE_NUM(DATADIR_M421, 0x24),
    DATA_MAKE_NUM(DATADIR_M421, 0x25),
};
float lbl_1_data_184[8] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.8f };
s32 lbl_1_data_1A4[6] = { 0, 2, 3, 0x14, 0x17, 0x18 };
UnkData1BCStruct lbl_1_data_1BC[6] = {
    { 0, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 1, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 2, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 3, 0.2f, 0.0f, -1.0f, 0 },
    { 4, 0.2f, 0.0f, -1.0f, 0 },
    { 5, 0.2f, 0.0f, -1.0f, 0 },
};
Vec lbl_1_data_234[4] = {
    { 0.0f, 0.0f, 100.0f },
    { -200.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 200.0f, 0.0f, 0.0f },
};
Vec lbl_1_data_264[4] = {
    { -80.0f, 0.0f, -300.0f },
    { -200.0f, 0.0f, -50.0f },
    { 0.0f, 0.0f, -150.0f },
    { 200.0f, 0.0f, -50.0f },
};
Vec2f lbl_1_data_294[3] = { { 300.0f, 0.4f }, { 450.0f, 0.7f }, { 600.0f, 1.0f } };
u32 lbl_1_data_2AC[3] = { REFRESH_RATE / 10, REFRESH_RATE / 5, REFRESH_RATE / 5 };
float lbl_1_data_2B8[3] = {

    (VERSION_PAL) ? 480.0f / REFRESH_RATE_F : 480.0f / REFRESH_RATE_OFF_BY_1,
    510.0f / REFRESH_RATE,
    550.0f / REFRESH_RATE
};
float lbl_1_data_2C4[3] = { 0.9f, 0.8f, 0.5f };
float lbl_1_data_2D0[3] = { 1188.0f * REFRESH_FREQ, 1224.0f * REFRESH_FREQ, 1224.0f * REFRESH_FREQ };
float lbl_1_data_2DC[3] = { -70.0f, -60.000004f, -70.0f };

float lbl_1_data_2E8[3] = { VERSION_PAL ? 192.0f : 192.00003f, 357.0f, 550.0f };

// M421DllPlayerWork
omObjData *lbl_1_bss_48[4];
// M421DllPlayerDLWork
omObjData *lbl_1_bss_44;
u32 lbl_1_bss_34[4];
u32 lbl_1_bss_30;

void fn_1_4648(Process *process)
{
    u32 sp18[4];
    u32 sp8[4];
    s16 var_r31;
    s16 var_r30;
    u32 var_r29;
    omObjData *var_r27;

    lbl_1_bss_30 = -1;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp18[var_r31] = GWPlayerCfg[var_r31].group;
        sp8[var_r31] = var_r31;
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        for (var_r30 = var_r31 + 1; var_r30 < 4; var_r30++) {
            if (sp18[var_r31] > sp18[var_r30]) {
                var_r29 = sp18[var_r31];
                sp18[var_r31] = sp18[var_r30];
                sp18[var_r30] = var_r29;
                var_r29 = sp8[var_r31];
                sp8[var_r31] = sp8[var_r30];
                sp8[var_r30] = var_r29;
            }
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_34[sp8[var_r31]] = var_r31;
    }
    omMakeGroupEx(process, 0, 4);
    omGetGroupMemberListEx(process, 0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r27 = lbl_1_bss_48[var_r31] = omAddObjEx(process, 0x28, 5, 6, 0, fn_1_48D4);
        var_r27->work[0] = var_r31;
    }
    lbl_1_bss_44 = omAddObjEx(process, 0x1E, 2, 0, -1, fn_1_A528);
    lbl_1_bss_44->work[0] = 0;
}

void fn_1_48B0(void)
{
    CharModelKill(-1);
}

void fn_1_48D4(omObjData *object)
{
    s32 sp8;

    M421DllPlayerWork *work;
    s32 var_r29;
    HsfanimStruct01 *var_r28;
    u32 var_r27;
    s32 var_r26;
    s32 var_r25;
    u32 var_r24;

    float sp1C[4] = { 0.25f, 0.5f, 0.75f, 1.0f };
    float spC[2][2] = { { 100.0f, 143.0f }, { 100.0f, 100.0f } };
    Vec sp2C[4] = { 0.0f, 1500.0f, 300.0f, -450.0f, 0.0f, -50.0f, 0.0f, 0.0f, -350.0f, 450.0f, 0.0f, -50.0f };

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M421DllPlayerWork), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, sizeof(M421DllPlayerWork));
    object->stat |= 0x100;
    var_r24 = object->work[0];
    var_r26 = GWPlayerCfg[var_r24].character;
    work->unk_00 = var_r26;
    sp8 = work->unk_04 = 0;
    work->unk_0C = lbl_1_bss_34[object->work[0]];
    var_r27 = 0;
    if (work->unk_0C != 0) {
        var_r27++;
    }
    fn_1_3F28(object->work[0], work->unk_0C, work->unk_00);
    work->unk_68 = sp1C[GWPlayerCfg[var_r24].diff & 3];
    work->unk_2C = GWPlayerCfg[object->work[0]].iscom;
    object->model[0] = CharModelCreate(var_r26, 4);
    Hu3DModelLayerSet(object->model[0], 1);
    for (var_r29 = 0; var_r29 < 6; var_r29++) {
        object->motion[var_r29] = CharModelMotionCreate(var_r26, lbl_1_data_1A4[var_r29]);
    }
    CharModelMotionDataClose(var_r26);
    if (var_r27 == 1) {
        object->model[1] = Hu3DModelCreateFile(lbl_1_data_164[var_r26]);
        Hu3DModelLayerSet(object->model[1], 1);
        fn_1_982C(object, 0);
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    }
    object->model[2] = Hu3DModelCreateFile(lbl_1_data_104[var_r26][var_r27]);
    Hu3DModelLayerSet(object->model[2], 1);
    Hu3DModelShadowSet(object->model[2]);
    if (var_r27 != 0) {
        object->model[3] = Hu3DModelCreateFile(lbl_1_data_104[var_r26][2]);
        Hu3DModelLayerSet(object->model[3], 1);
        Hu3DModelShadowSet(object->model[3]);
        Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
        work->unk_C8 = espEntry(0x120006, 1, 0);
        espDispOff(work->unk_C8);
        espAttrSet(work->unk_C8, HUSPR_ATTR_LINEAR);
    }
    var_r25 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M421, 0x27)), 0x80);
    object->model[4] = var_r25;
    Hu3DModelLayerSet(var_r25, 1);
    Hu3DParticleHookSet(var_r25, fn_1_9C38);
    for (var_r28 = ((ParticleData *)Hu3DData[var_r25].unk_120)->unk_48, var_r29 = 0; var_r29 < 0x80; var_r29++, var_r28++) {
        var_r28->unk2C = 0.0f;
        var_r28->unk40.a = 0;
        var_r28->unk00 = 0;
    }
    if (work->unk_0C == 0) {
        work->unk_148 = HuMemDirectMallocNum(HEAP_SYSTEM, 441 * sizeof(float), MEMORY_DEFAULT_NUM);
        memset(work->unk_148, 0, 441 * sizeof(float));
    }
    object->trans.x = work->unk_CC.x = sp2C[work->unk_0C].x;
    object->trans.y = work->unk_CC.y = sp2C[work->unk_0C].y;
    object->trans.z = work->unk_CC.z = sp2C[work->unk_0C].z;
    work->unk_20 = 1;
    work->unk_94 = 1.0f;
    work->unk_84 = spC[var_r27][0];
    work->unk_88 = spC[var_r27][1];
    work->unk_8C = 110.0f;
    work->unk_90 = 1.0f;
    work->unk_98 = work->unk_CC.y + (2.0f * work->unk_88);
    work->unk_9C = work->unk_CC.y;
    work->unk_A0 = 0.0f;
    work->unk_A4 = 0.0f;
    work->unk_78 = -1;
    work->unk_58 = work->unk_5C = 0.0f;
    work->unk_60 = 0.0f;
    work->unk_64 = 0.02f;
    work->unk_80 = 50.0f;
    work->unk_A8 = 0.0f;
    MTXIdentity(work->unk_118);
    work->unk_08 = -1;
    work->unk_6C = 0;
    work->unk_3C = 1;
    work->unk_44 = 0;
    if (var_r27 == 0) {
        Hu3DModelShadowSet(object->model[0]);
        object->func = fn_1_4F00;
        Hu3DModelReflectTypeSet(object->model[2], 4);
        work->unk_90 = lbl_1_data_184[work->unk_00];
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
        return;
    }
    object->func = fn_1_5060;
}

void fn_1_4F00(omObjData *object)
{
    M421DllPlayerWork *work = object->data;
    work->unk_10 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0.0f;
    work->unk_1C = 0.0f;
    switch (work->unk_44) {
        case 0:
            if (work->unk_48 > REFRESH_RATE_F * 1.8f) {
                HuAudFXPlay(0x601);
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
                work->unk_10 = 0x100;
                work->unk_44++;
            }
            break;
        case 1:
            if (work->unk_24 == 0) {
                work->unk_10 = 0x100;
                work->unk_44++;
            }
            break;
    }
    VECAdd(&work->unk_CC, &work->unk_D8, &work->unk_CC);
    fn_1_676C(object);
    fn_1_66B4(object);
    fn_1_7670(object);
    if (fn_1_3E34() == 2) {
        work->unk_44 = 0;
        object->func = fn_1_53C8;
    }
}

void fn_1_5060(omObjData *object)
{
    M421DllPlayerWork *work = object->data;
    {
        Vec sp8[4] = {
            { 0.0f, 0.0f, 0.0f },
            { 80.0f, 190.0f, 0.0f },
            { 290.0f, 120.0f, 0.0f },
            { 500.0f, 190.0f, 0.0f },
        };
        work->unk_10 = 0;
        work->unk_14 = 0;
        work->unk_18 = 0.0f;
        work->unk_1C = 0.0f;
        switch (work->unk_44) {
            case 0:
                if ((work->unk_48 > REFRESH_RATE_F / 2) && ((work->unk_48 & 0xF) == 0) && (frandmod(0x3E8) < 0x12C)) {
                    work->unk_10 = 0x100;
                    work->unk_44++;
                }
                else if (work->unk_48 > REFRESH_RATE_F * 2) {
                    work->unk_44++;
                }
                break;
            case 1:
                if (work->unk_48 > REFRESH_RATE_F * 2) {
                    work->unk_18 = atan2d(-work->unk_CC.x, 300.0f - work->unk_CC.z);
                    work->unk_1C = 0.01f;
                    if (work->unk_48 < REFRESH_RATE_F * 2.6f) {
                        espPosSet(work->unk_C8, sp8[work->unk_0C].x, sp8[work->unk_0C].y);
                        espScaleSet(work->unk_C8, 0.6000000238418579, 0.6000000238418579);
                        espDispOn(work->unk_C8);
                    }
                    else {
                        espDispOff(work->unk_C8);
                    }
                }
                if (work->unk_48 >= REFRESH_RATE_F * 3) {
                    work->unk_10 = 0x100;
                    work->unk_C0 = 1;
                    work->unk_44++;
                }
                break;
        }
    }
    VECAdd(&work->unk_CC, &work->unk_D8, &work->unk_CC);
    fn_1_6D48(object);
    fn_1_66B4(object);
    fn_1_7670(object);
    if (fn_1_3E34() == 2) {
        work->unk_44 = 0;
        object->func = fn_1_578C;
    }
}

void fn_1_53C8(omObjData *object)
{
    float var_f31;
    float var_f30;

    M421DllPlayerWork *work = object->data;
    s32 var_r29 = 0;
    work->unk_10 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0.0f;
    work->unk_1C = 0.0f;
    if (fn_1_3E4C() == 2) {
        if (work->unk_2C != 0) {
            fn_1_80C0(object);
        }
        else {
            work->unk_14 = HuPadBtn[GWPlayerCfg[object->work[0]].pad_idx];
            work->unk_10 = HuPadBtnDown[GWPlayerCfg[object->work[0]].pad_idx];
            var_f31 = HuPadStkX[GWPlayerCfg[object->work[0]].pad_idx];
            var_f30 = -HuPadStkY[GWPlayerCfg[object->work[0]].pad_idx];
            work->unk_18 = atan2d(var_f31, var_f30);
            work->unk_1C = 0.013888889f * sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
            if (work->unk_1C > 1.0f) {
                work->unk_1C = 1.0f;
            }
        }
    }
    if ((s32)work->unk_44 != 0) {
        (void)var_r29;
    }
    else {
        var_r29 = 1;
    }
    VECAdd(&work->unk_CC, &work->unk_D8, &work->unk_CC);
    fn_1_893C(object);
    fn_1_66B4(object);
    fn_1_676C(object);
    fn_1_7670(object);
    if ((fn_1_3E4C() == 3) && (var_r29 != 0) && (fn_1_3FF8() != 0)) {
        work->unk_44 = 0;
        object->func = fn_1_6184;
    }
}

void fn_1_578C(omObjData *object)
{
    float var_f31;
    float var_f30;

    M421DllPlayerWork *work = object->data;
    s32 var_r29 = 0;
    work->unk_10 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0.0f;
    work->unk_1C = 0.0f;
    if (fn_1_3E4C() == 2) {
        if (work->unk_2C != 0) {
            fn_1_80C0(object);
        }
        else {
            work->unk_14 = HuPadBtn[GWPlayerCfg[object->work[0]].pad_idx];
            work->unk_10 = HuPadBtnDown[GWPlayerCfg[object->work[0]].pad_idx];
            var_f31 = HuPadStkX[GWPlayerCfg[object->work[0]].pad_idx];
            var_f30 = -HuPadStkY[GWPlayerCfg[object->work[0]].pad_idx];
            work->unk_18 = atan2d(var_f31, var_f30);
            work->unk_1C = 0.013888889f * sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
            if (work->unk_1C > 1.0f) {
                work->unk_1C = 1.0f;
            }
        }
    }
    if ((s32)work->unk_44 != 0) {
        (void)var_r29;
    }
    else if (work->unk_24 == 0) {
        var_r29 = 1;
    }
    VECAdd(&work->unk_CC, &work->unk_D8, &work->unk_CC);
    fn_1_893C(object);
    fn_1_6D48(object);
    fn_1_66B4(object);
    fn_1_7670(object);
    if (work->unk_38 != 0) {
        if (fn_1_3E7C(work->unk_0C) != 0) {
            object->func = fn_1_5B9C;
        }
        else {
            work->unk_38 = 0;
        }
    }
    if ((work->unk_38 == 0) && (fn_1_3E4C() == 3) && (var_r29 != 0) && (fn_1_3FF8() != 0)) {
        work->unk_44 = 0;
        object->func = fn_1_6184;
    }
}

void fn_1_5B9C(omObjData *object)
{
    Mtx sp34;
    Vec sp28;
    Vec sp1C;
    s32 spC;
    float sp8;
    float var_f29;

    M421DllPlayerWork *work;
    M421DllCameraStruct *var_r29;

    work = object->data;
    spC = 0;
    {
        Vec sp10 = { 0.0f, 0.0f, 0.0f };
        switch (work->unk_44) {
            case 7:
                break;
            case 0:
                fn_1_B39C();
                work->unk_20 = 0;
                work->unk_58 = work->unk_5C = 0.0f;
                MTXIdentity(work->unk_118);
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(object->model[3], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSetV(object->model[3], &work->unk_F0);
                Hu3DMotionTimeSet(object->model[3], 0.0f);
                Hu3DMotionSpeedSet(object->model[3], 3.0f);
                HuAudFXEmiterPlay(0x5FC, &work->unk_F0);
                work->unk_78 = HuAudCharVoicePlayPos(work->unk_00, 0x123, &work->unk_CC);
                omVibrate(object->work[0], 0xC, 4, 2);
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
                fn_1_982C(object, 0);
                fn_1_9DD0(object, &work->unk_F0);
                var_r29 = fn_1_3C14(1);
                mtxRot(sp34, var_r29->unk_28.x, var_r29->unk_28.y, 0.0f);
                sp10.z = var_r29->unk_34 - 350.0f;
                MTXMultVec(sp34, &sp10, &sp1C);
                VECAdd(&var_r29->unk_1C, &sp1C, &sp28);
                fn_1_9BFC(sp28.y - work->unk_CC.y, 0.9f, work->unk_108);
                VECSubtract(&sp28, &work->unk_CC, &sp1C);
                work->unk_D8.y = REFRESH_FREQ * work->unk_108[2];
                work->unk_D8.x = (10.0f / 9.0f) * REFRESH_FREQ * sp1C.x;
                work->unk_D8.z = (10.0f / 9.0f) * REFRESH_FREQ * sp1C.z;
                work->unk_44 = 1;
                work->unk_48 = 0;
                break;
            case 1:
                work->unk_D8.y += REFRESH_FREQ * (REFRESH_FREQ * work->unk_108[3]);
                var_f29 = sqrtf((work->unk_D8.x * work->unk_D8.x) + (work->unk_D8.z * work->unk_D8.z));
                var_f29 = atan2d(var_f29, work->unk_D8.y);
                var_f29 = var_f29;
                sp1C.x = work->unk_D8.z;
                sp1C.y = 0.0f;
                sp1C.z = -work->unk_D8.x;
                VECNormalize(&sp1C, &sp1C);
                MTXRotAxisRad(work->unk_118, &sp1C, MTXDegToRad(var_f29));
                sp1C.x = sp1C.z = 0.0f;
                sp1C.y = 1.0f;
                MTXRotAxisRad(sp34, &sp1C, MTXDegToRad(22.5f * work->unk_48));
                MTXConcat(work->unk_118, sp34, work->unk_118);
                HuAudFXEmiterUpDate(work->unk_78, &work->unk_CC);
                if (work->unk_48 >= REFRESH_RATE_F * 1.2f) {
                    MTXIdentity(work->unk_118);
                    work->unk_D8.x = work->unk_D8.y = work->unk_D8.z = 0.0f;
                    work->unk_44 = 2;
                    work->unk_48 = 0;
                    fn_1_3F68(object->work[0]);
                    fn_1_3F98(object->work[0]);
                    fn_1_3FC8(object->work[0]);
                }
                break;
            case 2:
                work->unk_D8.y += -980.0f * REFRESH_FREQ * REFRESH_FREQ;
                if (work->unk_48 > REFRESH_RATE_F * 2) {
                    work->unk_44 = 7;
                    work->unk_48 = 0;
                    work->unk_D8.x = work->unk_D8.y = work->unk_D8.z = 0.0f;
                }
                break;
        }
    }
    VECAdd(&work->unk_CC, &work->unk_D8, &work->unk_CC);
    fn_1_66B4(object);
    fn_1_7670(object);
}

void fn_1_6184(omObjData *object)
{
    M421DllPlayerWork *work = object->data;
    work->unk_10 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0.0f;
    work->unk_1C = 0.0f;
    switch (work->unk_44) {
        case 0:
            if (work->unk_0C == 0) {
                work->unk_20 = 0;
                work->unk_58 = work->unk_5C = 0.0f;
                MTXIdentity(work->unk_118);
                Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
                fn_1_982C(object, 0);
                work->unk_CC = work->unk_E4;
            }
            else {
                work->unk_20 = 0;
                work->unk_58 = work->unk_5C = 0.0f;
                MTXIdentity(work->unk_118);
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
                fn_1_982C(object, 0);
                work->unk_CC = work->unk_E4;
            }
            fn_1_9DD0(object, &work->unk_F0);
            HuAudFXEmiterPlay(0x600, &work->unk_F0);
            work->unk_D8.x = work->unk_D8.y = work->unk_D8.z = 0.0f;
            work->unk_44 = 3;
            break;
        case 3:
            Hu3DModelShadowSet(object->model[0]);
            work->unk_D8.y += -980.0f * REFRESH_FREQ * REFRESH_FREQ;
            if (work->unk_CC.y <= 0.0f) {
                work->unk_CC.y = 0.0f;
                work->unk_D8.y = 0.0f;
                work->unk_44 = 4;
            }
            break;
        case 4:
            work->unk_48 = 0;
            fn_1_3F68(object->work[0]);
            break;
    }
    VECAdd(&work->unk_CC, &work->unk_D8, &work->unk_CC);
    work->unk_E4 = work->unk_CC;
    fn_1_956C(object);
    fn_1_66B4(object);
    fn_1_7670(object);
    if (fn_1_3E4C() == 5) {
        object->func = fn_1_6400;
    }
}

void fn_1_6400(omObjData *object)
{
    Vec sp8;
    float var_f31;
    M421DllPlayerWork *work = object->data;

    VECAdd(&work->unk_CC, &work->unk_D8, &work->unk_CC);
    work->unk_E4 = work->unk_CC;
    fn_1_956C(object);
    fn_1_66B4(object);
    fn_1_7670(object);
    switch (work->unk_44) {
        case 4:
            if (fn_1_3EF8(object->work[0]) >= 0) {
                VECSubtract(&lbl_1_data_234[work->unk_0C], &work->unk_CC, &sp8);
            }
            else {
                VECSubtract(&lbl_1_data_264[work->unk_0C], &work->unk_CC, &sp8);
            }
            sp8.y = 0.0f;
            var_f31 = VECMag(&sp8);
            if (var_f31 < 10.0f) {
                var_f31 = 0.0f;
            }
            else {
                if (VECMag(&sp8) >= 100.0f) {
                    var_f31 = 100.0f;
                }
                var_f31 = 0.2f + (0.008f * var_f31);
            }
            work->unk_18 = atan2d(sp8.x, sp8.z);
            work->unk_1C = var_f31;
            fn_1_7478(object);
            if ((work->unk_1C == 0.0f) || (work->unk_48 > REFRESH_RATE * 5)) {
                work->unk_5C = 0.0f;
                work->unk_60 = 0.15f;
                work->unk_64 = 0.0f;
                work->unk_D8.x = work->unk_D8.y = work->unk_D8.z = 0.0f;
                fn_1_3F98(object->work[0]);
            }
            if (fn_1_3E64() == 1) {
                work->unk_44 = 5;
            }
            break;
        case 5:
            if (fn_1_3E64() == 1) {
                if (fn_1_3EF8(object->work[0]) >= 0) {
                    fn_1_982C(object, 4);
                }
                else {
                    fn_1_982C(object, 5);
                }
                work->unk_44 = 6;
                return;
            }
            break;
        case 6:
            if (fn_1_99B8(object) != 0) {
                fn_1_3FC8(object->work[0]);
            }
            break;
    }
}

void fn_1_66B4(omObjData *object)
{
    M421DllPlayerWork *work = object->data;
    work->unk_50++;
    work->unk_48++;
    object->trans.x = work->unk_CC.x;
    object->trans.y = work->unk_CC.y;
    object->trans.z = work->unk_CC.z;
    work->unk_60 += work->unk_64;
    if (work->unk_60 > 0.45f) {
        work->unk_60 = 0.45f;
    }
    work->unk_58 = fn_1_4478(work->unk_58, work->unk_5C, work->unk_60);
    object->rot.y = work->unk_58;
}

void fn_1_676C(omObjData *object)
{
    Mtx sp44;
    Mtx sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    M421DllPlayerWork *work = object->data;
    if (work->unk_20 != 0) {
        if (work->unk_1C > 0.0f) {
            work->unk_5C = work->unk_18;
            work->unk_60 = 0.15f;
            work->unk_64 = 0.0f;
        }
        if (work->unk_1C < 0.05f) {
            fn_1_982C(object, 0);
            CharModelMotionSpeedSet(work->unk_00, 1.0f);
        }
        else {
            var_f30 = 0.5f;
            if (work->unk_08 == 2) {
                var_f30 = 0.45f;
            }
            if (work->unk_1C > var_f30) {
                fn_1_982C(object, 2);
                var_f29 = work->unk_1C;
            }
            else {
                fn_1_982C(object, 1);
                var_f29 = work->unk_1C / var_f30;
            }
            CharModelMotionSpeedSet(work->unk_00, var_f29);
        }
        sp8.x = 1.0 * REFRESH_FREQ * (REFRESH_FREQ * 100.0f * (2.0 * (work->unk_1C * sind(work->unk_18))));
        sp8.y = 0.0f;
        sp8.z = 1.0 * REFRESH_FREQ * (REFRESH_FREQ * 100.0f * (2.0 * (work->unk_1C * cosd(work->unk_18))));
        VECAdd(&sp8, &work->unk_D8, &work->unk_D8);
        if (work->unk_24 == 0) {
            if ((work->unk_10 & 0x100) != 0) {
                work->unk_24 = 1;
                fn_1_9BFC(400.0f - (2.0f * work->unk_88), 0.25f, work->unk_108);
                work->unk_D8.y = REFRESH_FREQ * work->unk_108[2];
                if (fn_1_3E34() == 2) {
                    HuAudFXEmiterPlay(0x5FE, &work->unk_F0);
                }
            }
        }
        else {
            work->unk_D8.y += REFRESH_FREQ * (REFRESH_FREQ * work->unk_108[3]);
            if ((work->unk_D8.y < 0.0f) && (work->unk_CC.y <= 0.0f)) {
                work->unk_D8.y = 0.0f;
                work->unk_24 = 0;
                if (fn_1_3E34() != 2) {
                    HuAudFXEmiterPlay(0x5FD, &work->unk_F0);
                    omVibrate(object->work[0], 0xC, 4, 2);
                }
                else {
                    HuAudFXEmiterPlay(0x5FF, &work->unk_F0);
                }
            }
        }
        MTXIdentity(sp44);
        MTXIdentity(sp14);
        work->unk_A8 = 1.0f - work->unk_1C;
        sp8 = work->unk_D8;
        sp8.y = 0.0f;
        var_f31 = VECMag(&sp8);
        if (var_f31 > 0.0f) {
            VECNormalize(&sp8, &sp8);
            var_f28 = sp8.z;
            sp8.z = -sp8.x;
            sp8.x = var_f28;
            var_f31 *= 360.0f / (3.14159f * (2.0f * work->unk_88));
            MTXRotAxisRad(sp44, &sp8, 0.017453292f * var_f31);
        }
        sp8.x = sind((90.0f + work->unk_18));
        sp8.y = 0.0f;
        sp8.z = cosd((90.0f + work->unk_18));
        if (work->unk_1C > 0.0f) {
            var_f31 = REFRESH_FREQ * 100.0f * work->unk_1C * (360.0f / (3.14159f * (2.0f * work->unk_88)));
            if (work->unk_24 != 0) {
                var_f31 *= 2.0f;
            }
            MTXRotAxisRad(sp14, &sp8, 0.017453292f * var_f31);
        }
        MTXConcat(sp44, sp14, sp44);
        MTXConcat(sp44, work->unk_118, work->unk_118);
        fn_1_7AA0(object);
    }
}

void fn_1_6D48(omObjData *object)
{
    M421DllPlayerWork *work = object->data;
    if (work->unk_20 != 0) {
        if (work->unk_D8.y > 0.0f) {
            work->unk_9C = work->unk_CC.y - (0.03f / REFRESH_FREQ * work->unk_D8.y);
            if (work->unk_9C < 0.0f) {
                work->unk_9C = 0.0f;
            }
            work->unk_98 = (2.0f * (work->unk_CC.y + work->unk_88)) - work->unk_9C;
            work->unk_A0 = 0.5f * work->unk_D8.y;
            work->unk_A4 = -0.2f * work->unk_A0;
        }
        else if (work->unk_D8.y < 0.0f) {
            work->unk_98 = work->unk_CC.y + (2.0f * work->unk_88);
            work->unk_9C = work->unk_CC.y;
            work->unk_A0 = 0.8f * work->unk_D8.y;
            work->unk_A4 = work->unk_A0 * (-2.0f / work->unk_B8);
        }
        else if (work->unk_24 == 0) {
            work->unk_9C = work->unk_CC.y;
            if ((work->unk_B8 != 0) || (work->unk_BC != 0)) {
                work->unk_98 += work->unk_A0;
                work->unk_A0 += work->unk_A4;
            }
            else {
                work->unk_A0 = work->unk_A4 = 0.0f;
                work->unk_98 = work->unk_CC.y + (2.0f * work->unk_88);
            }
            if (work->unk_BC != 0) {
                work->unk_AC = work->unk_AC + work->unk_B0;
                work->unk_98 = work->unk_CC.y + (2.0f * work->unk_88);
                work->unk_98 = work->unk_98 + ((work->unk_BC / (0.3f / REFRESH_FREQ)) * (work->unk_B4 * sind(work->unk_AC)));
            }
        }
        work->unk_F0 = work->unk_CC;
        work->unk_F0.y = 0.5f * (work->unk_98 + work->unk_9C);
        work->unk_94 = (work->unk_F0.y - work->unk_9C) / work->unk_88;
        if ((work->unk_1C > 0.0f) && (work->unk_24 == 0)) {
            work->unk_5C = work->unk_18;
            work->unk_60 = 0.15f;
            work->unk_64 = 0.0f;
        }
        if ((work->unk_10 & 0x100) != 0) {
            work->unk_C4 = REFRESH_RATE / 5;
        }
        if (work->unk_C4 != 0) {
            work->unk_C4--;
        }
        if (work->unk_24 == 0) {
            if ((work->unk_28 == 0) && (work->unk_C0 < 3) && ((work->unk_C0 != 0) || (work->unk_BC == 0)) && (work->unk_C4 != 0)) {
                work->unk_28 = 1;
            }
            if (work->unk_B8 != 0) {
                work->unk_B8--;
                if (work->unk_B8 == 0) {
                    work->unk_A0 *= lbl_1_data_2C4[work->unk_C0 - 1];
                    work->unk_A4 = work->unk_A0 * (-2.0f / (work->unk_BC + 1));
                }
            }
            else {
                if (work->unk_BC != 0) {
                    work->unk_BC--;
                }
                if ((work->unk_C0 >= 3) || (work->unk_28 == 0)) {
                    work->unk_C0 = 0;
                }
                if (work->unk_28 != 0) {
                    work->unk_28 = 0;
                    work->unk_24 = 1;
                    work->unk_D8.x = lbl_1_data_2B8[work->unk_C0] * (work->unk_1C * sind(work->unk_18));
                    work->unk_D8.z = lbl_1_data_2B8[work->unk_C0] * (work->unk_1C * cosd(work->unk_18));
                    if (work->unk_C0 < 2) {
                        HuAudFXEmiterPlay(0x5F9, &work->unk_F0);
                    }
                    else {
                        HuAudFXEmiterPlay(0x5FA, &work->unk_F0);
                    }
                    fn_1_9BFC(lbl_1_data_294[work->unk_C0].x - (2.0f * work->unk_88), 0.5f * lbl_1_data_294[work->unk_C0].y, work->unk_108);
                    work->unk_D8.y = REFRESH_FREQ * work->unk_108[2];
                    work->unk_B8 = (VERSION_PAL) ? 7 : 9;
                    work->unk_BC = lbl_1_data_2AC[work->unk_C0];
                    work->unk_C0++;
                }
            }
        }
        else {
            work->unk_AC = 0.0f;
            work->unk_B0 = lbl_1_data_2D0[work->unk_C0 - 1];
            work->unk_B4 = lbl_1_data_2DC[work->unk_C0 - 1];
            work->unk_D8.y += REFRESH_FREQ * (REFRESH_FREQ * work->unk_108[3]);
            if ((work->unk_D8.y < 0.0f) && (work->unk_CC.y <= 0.0f)) {
                work->unk_D8.x = work->unk_D8.y = work->unk_D8.z = 0.0f;
                work->unk_24 = 0;
                HuAudFXEmiterPlay(0x5FB, &work->unk_F0);
            }
        }
    }
}

void fn_1_7478(omObjData *object)
{
    float var_f31;
    float var_f30;

    M421DllPlayerWork *work = object->data;
    if (work->unk_1C > 0.0f) {
        work->unk_5C = work->unk_18;
    }
    if ((work->unk_1C > 0.05f) && (work->unk_34 == 0)) {
        work->unk_D8.x = REFRESH_FREQ * (550.0 * (work->unk_1C * sind(work->unk_18)));
        work->unk_D8.z = REFRESH_FREQ * (550.0 * (work->unk_1C * cosd(work->unk_18)));
        work->unk_60 = 0.2f;
        work->unk_64 = 0.0f;
        var_f31 = 0.5f;
        if (work->unk_08 == 2) {
            var_f31 = 0.45f;
        }
        if (work->unk_1C > var_f31) {
            fn_1_982C(object, 2);
            var_f30 = work->unk_1C;
        }
        else {
            fn_1_982C(object, 1);
            var_f30 = work->unk_1C / var_f31;
        }
        CharModelMotionSpeedSet(work->unk_00, var_f30);
        return;
    }
    work->unk_D8.x = work->unk_D8.y = work->unk_D8.z = 0.0f;
    fn_1_982C(object, 0);
}

void fn_1_7670(omObjData *object)
{
    float var_f29;

    M421DllPlayerWork *work = object->data;
    work->unk_E4 = work->unk_CC;
    if (work->unk_20 != 0) {
        if (work->unk_0C == 0) {
            work->unk_F0 = work->unk_CC;
            work->unk_F0.y += work->unk_88 * work->unk_94;
            work->unk_E4.y += work->unk_94 * (work->unk_88 - work->unk_84);
            Hu3DModelPosSetV(object->model[0], &work->unk_E4);
            Hu3DModelRotSet(object->model[0], 0.0f, work->unk_58, 0.0f);
            Hu3DModelScaleSet(object->model[0], work->unk_90, work->unk_90, work->unk_90);
            Hu3DModelPosSetV(object->model[2], &work->unk_F0);
            MTXCopy(work->unk_118, Hu3DData[object->model[2]].unk_F0);
            Hu3DModelScaleSet(object->model[2], 1.0f, work->unk_94, 1.0f);
            return;
        }
        work->unk_E4.y += (2.0f * work->unk_88 * work->unk_94) - work->unk_8C;
        Hu3DModelPosSetV(object->model[0], &work->unk_E4);
        Hu3DModelRotSet(object->model[0], 0.0f, work->unk_58, 0.0f);
        Hu3DModelPosSetV(object->model[2], &work->unk_F0);
        Hu3DModelRotSet(object->model[2], 0.0f, work->unk_58, 0.0f);
        var_f29 = sqrtf(1.0f / work->unk_94);
        Hu3DModelScaleSet(object->model[2], var_f29, work->unk_94, var_f29);
        Hu3DModelPosSet(object->model[1], work->unk_F0.x, 15.000001f + (work->unk_F0.y + (work->unk_88 * work->unk_94)), work->unk_F0.z);
        Hu3DModelRotSet(object->model[1], 0.0f, work->unk_58, 0.0f);
        return;
    }
    work->unk_90 += 0.1f * (1.0f - work->unk_90);
    Hu3DModelPosSetV(object->model[0], &work->unk_E4);
    Hu3DModelRotSet(object->model[0], 0.0f, work->unk_58, 0.0f);
    Hu3DModelScaleSet(object->model[0], work->unk_90, work->unk_90, work->unk_90);
    MTXCopy(work->unk_118, Hu3DData[object->model[0]].unk_F0);
}

void fn_1_7AA0(omObjData *object)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    M421DllPlayerWork *work = object->data;
    sp38 = work->unk_CC;
    sp38.y = 0.0f;
    VECScale(&work->unk_D8, &sp14, (VERSION_PAL) ? 6.25f : 7.5f);
    sp2C = sp38;
    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        VECAdd(&sp2C, &sp14, &sp2C);
        fn_1_9474(object, &sp2C, &sp2C);
    }
    sp2C.y = 0.0f;
    VECSubtract(&sp38, &sp2C, &sp8);
    sp8.y = 0.0f;
    var_f28 = VECMag((Vec *)&sp8.y);
    var_f29 = 0.0025f * var_f28;
    if (var_f29 > 1.0f) {
        var_f29 = 1.0f;
    }
    if (var_f28 > 0.0f) {
        VECNormalize(&sp8, &sp8);
    }
    sp20.y = 0.0f;
    sp20.z = -750.0f;
    var_r29 = 0;
    for (var_r30 = 0; var_r30 < 0x15; var_r30++) {
        sp20.x = -750.0f;
        for (var_r28 = 0; var_r28 < 0x15; var_r28++, var_r29++) {
            if (VECMag(&sp20) >= 700.0f) {
                work->unk_148[var_r29] = 10.0f;
            }
            else {
                VECSubtract(&sp2C, &sp20, &sp14);
                var_f31 = 1.0f - (0.001f * VECMag(&sp14));
                if (var_f31 < 0.0f) {
                    var_f31 = 0.0f;
                }
                work->unk_148[var_r29] = 3.0f * var_f31;
                VECSubtract(&sp38, &sp20, &sp14);
                var_f31 = 1.0f - (0.001f * VECMag(&sp14));
                if (var_f31 < 0.0f) {
                    var_f31 = 0.0f;
                }
                work->unk_148[var_r29] += 3.0f * var_f31;
                VECSubtract(&sp20, &sp38, &sp14);
                var_f31 = VECMag(&sp14);
                var_f30 = 1.0f - (0.001f * var_f31);
                if (var_f30 < 0.0f) {
                    var_f30 = 0.0f;
                }
                if (var_f31 > 0.0f) {
                    VECNormalize(&sp14, &sp14);
                }
                var_f31 = VECDotProduct(&sp14, &sp8);
                if (var_f31 > 0.0f) {
                    var_f31 = 4.0f * (var_f29 * (var_f30 * (var_f31 * var_f31)));
                    work->unk_148[var_r29] += var_f31;
                }
            }
            sp20.x += 75.0f;
        }
        sp20.z += 75.0f;
    }
}

void fn_1_7EB8(Vec *var_r26, float sp8, Vec *var_r27)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f31;
    float var_f30;

    s32 var_r31;
    M421DllPlayerWork *work;
    s32 var_r29;
    s32 var_r28;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        work = lbl_1_bss_48[var_r31]->data;
        if ((work->unk_0C == 0) && work->unk_148) {
            break;
        }
    }
    sp24 = *var_r26;
    sp24.y = 0.0f;
    *var_r27 = sp24;
    var_f30 = 100.0f;
    sp18.y = 0.0f;
    sp18.z = -750.0f;
    var_r28 = 0;
    for (var_r31 = 0; var_r31 < 0x15; var_r31++) {
        sp18.x = -750.0f;
        for (var_r29 = 0; var_r29 < 0x15; var_r29++, var_r28++) {
            VECSubtract(&sp18, &sp24, &spC);
            var_f31 = VECMag(&spC);
            if (var_f31 <= sp8) {
                var_f31 = 1.0f + (0.5f - (0.0005f * var_f31));
                var_f31 *= work->unk_148[var_r28];
                if (var_f31 < var_f30) {
                    var_f30 = var_f31;
                    *var_r27 = sp18;
                }
            }
            sp18.x += 75.0f;
        }
        sp18.z += 75.0f;
    }
}

void fn_1_80C0(omObjData *var_r28)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;

    M421DllPlayerWork *var_r30;
    s32 var_r29;

    M421DllPlayerWork *var_r31 = var_r28->data;
    if (var_r31->unk_0C != 0) {
        if (var_r31->unk_24 == 0) {
            switch (var_r31->unk_6C) {
                case 0:
                    if (var_r31->unk_C0 == 3) {
                        var_r31->unk_6C = 3;
                        return;
                    }
                    var_r31->unk_6C = 2;
                    var_r31->unk_70 = REFRESH_RATE_F * (0.3f + (0.00040000002f * frandmod(0x3E8)));
                    if ((frandmod(0x410) < (1000.0f * (0.5f + (0.5f * var_r31->unk_68)))) || (var_r31->unk_3C != 0)) {
                        var_r31->unk_3C = 0;
                        var_r31->unk_6C = 1;
                        return;
                    }
                    break;
                case 1:
                    var_f29 = lbl_1_data_2E8[var_r31->unk_C0];
                    fn_1_7EB8(&var_r31->unk_CC, 1000.0f, &sp38);
                    VECSubtract(&sp38, &var_r31->unk_CC, &sp2C);
                    sp2C.y = 0.0f;
                    var_f31 = VECMag(&sp2C);
                    if (var_f31 < var_f29) {
                        var_r31->unk_1C = VECMag(&sp2C) / var_f29;
                    }
                    else {
                        var_r31->unk_1C = 1.0f;
                    }
                    var_r31->unk_18 = atan2d(sp2C.x, sp2C.z);
                    var_r31->unk_10 = 0x100;
                    return;
                case 2:
                    if (var_r31->unk_70 != 0) {
                        var_r31->unk_70--;
                        return;
                    }
                    var_r31->unk_6C = 0;
                    return;
                case 3:
                    if (var_r31->unk_C0 != 3) {
                        var_r31->unk_6C = 2;
                        var_r31->unk_70 = REFRESH_RATE_F * (0.0003f * frandmod(0x3E8));
                        return;
                    }
                    break;
            }
        }
        else {
            var_r31->unk_6C = 0;
        }
    }
    else {
        var_f30 = 10000.0f;
        if (var_r31->unk_74 == 0) {
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                if (var_r28->work[0] != lbl_1_bss_48[var_r29]->work[0]) {
                    var_r30 = lbl_1_bss_48[var_r29]->data;
                    if (var_r30->unk_38 == 0) {
                        if (var_r30->unk_24 != 0) {
                            VECScale(&var_r30->unk_D8, &sp20, REFRESH_RATE_F);
                            VECAdd(&var_r30->unk_CC, &sp20, &sp20);
                        }
                        else {
                            sp20 = var_r30->unk_CC;
                        }
                        sp20.y = 0.0f;
                        sp20.x += 100.0f * (0.5f * ((((2.0f * var_r31->unk_68) / 1000.0f) * frandmod(0x3E8)) - var_r31->unk_68));
                        sp20.z += 100.0f * (0.5f * ((((2.0f * var_r31->unk_68) / 1000.0f) * frandmod(0x3E8)) - var_r31->unk_68));
                        var_f31 = VECMag(&sp20);
                        if (var_f31 > (700.0f - (100.0f * (2.3f * var_r31->unk_68)))) {
                            var_f31 = (700.0f - (100.0f * (2.3f * var_r31->unk_68))) / var_f31;
                            VECScale(&sp20, &sp20, var_f31);
                        }
                        VECSubtract(&sp20, &var_r31->unk_CC, &sp14);
                        sp14.y = 0.0f;
                        var_f31 = VECMag(&sp14);
                        if (var_f30 > var_f31) {
                            var_r31->unk_FC = sp20;
                            var_f30 = var_f31;
                        }
                    }
                }
            }
            var_r31->unk_74 = REFRESH_RATE_F * ((1.5f - var_r31->unk_68) + (0.0015f * frandmod(0x3E8)));
        }
        VECSubtract(&var_r31->unk_FC, &var_r31->unk_CC, &sp14);
        sp8 = var_r31->unk_D8;
        if (VECMag(&sp14)) {
            VECNormalize(&sp14, &sp14);
        }
        if (VECMag(&sp8)) {
            VECNormalize(&sp8, &sp8);
        }
        var_f31 = (0.5f + (0.5f * var_r31->unk_68)) * (1.0f - VECDotProduct(&sp14, &sp8));
        VECScale(&var_r31->unk_D8, &sp14, REFRESH_RATE_F * (2.0f * var_f31));
        VECAdd(&var_r31->unk_CC, &sp14, &sp14);
        VECSubtract(&var_r31->unk_FC, &sp14, &sp20);
        var_f30 = VECMag(&sp20);
        var_r31->unk_18 = fn_1_4478(var_r31->unk_58, atan2d(sp20.x, sp20.z), 0.5f);
        var_r31->unk_1C = 0.95f + (0.05f * var_r31->unk_68);
        if ((var_f30 < 300.0f) && ((var_r31->unk_50 & 7) == 0) && (frandmod(0x514) < (1000.0f * var_r31->unk_68))) {
            var_r31->unk_10 = 0x100;
        }
        var_r31->unk_74--;
        if (var_f30 < 130.0f) {
            var_r31->unk_74 = 0;
        }
    }
}

void fn_1_893C(omObjData *object)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;

    M421DllPlayerWork *var_r31;
    M421DllPlayerWork *var_r30;
    s32 var_r29;
    s32 var_r28;
    M421DllPlayerWork *var_r27;
    M421DllPlayerWork *var_r26;
    s32 var_r24;
    s32 var_r23;

    if (lbl_1_bss_30 >= object->work[0]) {
        for (var_r24 = 0; var_r24 < 4; var_r24++) {
            for (var_r28 = 0; var_r28 < 4; var_r28++) {
                for (var_r29 = 0; var_r29 < 4; var_r29++) {
                    var_r31 = lbl_1_bss_48[var_r29]->data;
                    if ((var_r31->unk_38 == 0) && (var_r31->unk_20 != 0)) {
                        var_r31->unk_F0 = var_r31->unk_CC;
                        var_r31->unk_F0.y += var_r31->unk_88;
                    }
                }
                var_r31 = lbl_1_bss_48[var_r28]->data;
                if ((var_r31->unk_38 == 0) && (var_r31->unk_20 != 0)) {
                    for (var_r29 = 0; var_r29 < 4; var_r29++) {
                        if (var_r28 != var_r29) {
                            var_r30 = lbl_1_bss_48[var_r29]->data;
                            if ((var_r30->unk_38 == 0) && (var_r30->unk_20 != 0)) {
                                VECSubtract(&var_r31->unk_F0, &var_r30->unk_F0, &sp38);
                                var_f31 = VECMag(&sp38);
                                if (var_f31 < (var_r31->unk_88 + var_r30->unk_88)) {
                                    if (var_f31 > 0.0f) {
                                        var_f31 = 0.5f * ((var_r31->unk_88 + var_r30->unk_88) - var_f31);
                                    }
                                    else {
                                        var_f31 = 0.5f * (var_r31->unk_88 + var_r30->unk_88);
                                        sp38.x = frandmod(0x3E8) - 0.0005f;
                                        sp38.y = 0.0f;
                                        sp38.z = frandmod(0x3E8) - 0.0005f;
                                    }
                                    VECNormalize(&sp38, &sp38);
                                    VECScale(&sp38, &sp38, var_f31);
                                    VECAdd(&var_r31->unk_F0, &sp38, &var_r31->unk_F0);
                                    VECSubtract(&var_r30->unk_F0, &sp38, &var_r30->unk_F0);
                                    if ((var_r31->unk_0C == 0) && (var_r30->unk_0C != 0)) {
                                        var_r30->unk_38 = 1;
                                    }
                                    else if ((var_r31->unk_0C != 0) && (var_r30->unk_0C == 0)) {
                                        var_r31->unk_38 = 1;
                                    }
                                }
                            }
                        }
                    }
                    for (var_r29 = 0; var_r29 < 4; var_r29++) {
                        var_r31 = lbl_1_bss_48[var_r29]->data;
                        if ((var_r31->unk_38 == 0) && (var_r31->unk_20 != 0)) {
                            var_r31->unk_CC = var_r31->unk_F0;
                            var_r31->unk_CC.y -= var_r31->unk_88;
                        }
                    }
                    var_r31 = lbl_1_bss_48[var_r28]->data;
                    if (var_r31->unk_24 != 0) {
                        if (var_r31->unk_CC.y < 0.0f) {
                            var_r31->unk_CC.y = 0.0f;
                        }
                    }
                    else {
                        var_r31->unk_CC.y = 0.0f;
                    }
                    sp38 = var_r31->unk_CC;
                    sp38.y = 0.0f;
                    var_f31 = VECMag(&sp38);
                    if (var_f31 > (750.0f - var_r31->unk_88)) {
                        var_f30 = (750.0f - var_r31->unk_88) / var_f31;
                        VECScale(&sp38, &sp38, var_f30);
                        var_r31->unk_CC.x = sp38.x;
                        var_r31->unk_CC.z = sp38.z;
                    }
                }
            }
        }
        for (var_r28 = 0; var_r28 < 4; var_r28++) {
            var_r31 = lbl_1_bss_48[var_r28]->data;
            if ((var_r31->unk_38 == 0) && (var_r31->unk_20 != 0) && (var_r31->unk_0C == 0)) {
                sp38 = var_r31->unk_CC;
                sp38.y = 0.0f;
                var_f31 = VECMag(&sp38);
                if (var_f31 >= (750.0f - var_r31->unk_88)) {
                    var_f31 = VECDotProduct(&var_r31->unk_D8, &sp38);
                    if (var_f31 > 0.0f) {
                        VECNormalize(&sp38, &sp38);
                        var_f31 = VECDotProduct(&var_r31->unk_D8, &sp38);
                        var_r31->unk_D8.x = 0.92f * (var_r31->unk_D8.x - (1.1f * (var_f31 * sp38.x)));
                        var_r31->unk_D8.z = 0.92f * (var_r31->unk_D8.z - (1.1f * (var_f31 * sp38.z)));
                    }
                }
            }
        }
        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                var_r31 = lbl_1_bss_48[var_r29]->data;
                if ((var_r31->unk_38 == 0) && (var_r31->unk_20 != 0)) {
                    var_r31->unk_F0 = var_r31->unk_CC;
                    var_r31->unk_F0.y += var_r31->unk_88;
                }
            }
            var_r31 = lbl_1_bss_48[var_r28]->data;
            if ((var_r31->unk_38 == 0) && (var_r31->unk_20 != 0) && (var_r31->unk_0C != 0)) {
                for (var_r29 = var_r28; var_r29 < 4; var_r29++) {
                    if (var_r28 != var_r29) {
                        var_r30 = lbl_1_bss_48[var_r29]->data;
                        if ((var_r30->unk_38 == 0) && (var_r30->unk_20 != 0) && (var_r30->unk_0C != 0)) {
                            var_r23 = 0;
                            var_f31 = VECMag(&var_r31->unk_D8);
                            var_f30 = VECMag(&var_r30->unk_D8);
                            if ((!(var_f31 <= 0.0f) && (var_r31->unk_24 != 0)) || (!(var_f30 <= 0.0f) && (var_r30->unk_24 != 0))) {
                                if (var_r31->unk_24 == 0) {
                                    var_r27 = var_r30;
                                    var_r26 = var_r31;
                                }
                                else if (var_r30->unk_24 == 0) {
                                    var_r27 = var_r31;
                                    var_r26 = var_r30;
                                }
                                else {
                                    var_r23 = 1;
                                    var_r27 = var_r31;
                                    var_r26 = var_r30;
                                }
                                VECAdd(&var_r27->unk_F0, &var_r27->unk_D8, &sp14);
                                VECAdd(&var_r26->unk_F0, &var_r26->unk_D8, &sp8);
                                VECSubtract(&sp14, &sp8, &sp38);
                                var_f31 = VECMag(&sp38);
                                if ((var_f31 < (var_r27->unk_88 + var_r26->unk_88)) && (var_f31 > 0.0f)) {
                                    VECNormalize(&sp38, &sp38);
                                    if (var_r23 != 0) {
                                        VECNormalize(&var_r27->unk_D8, &sp2C);
                                        VECNormalize(&var_r26->unk_D8, &sp20);
                                        var_f31 = -VECDotProduct(&sp2C, &sp38);
                                        var_f30 = VECDotProduct(&sp20, &sp38);
                                    }
                                    else {
                                        VECNormalize(&var_r27->unk_D8, &sp2C);
                                        sp20.x = sp20.y = sp20.z = 0.0f;
                                        var_f31 = -VECDotProduct(&sp2C, &sp38);
                                        var_f30 = 0.0f;
                                    }
                                    if ((var_f31 > 0.01f) || (var_f31 > 0.01f)) {
                                        var_f31 = VECDotProduct(&var_r27->unk_D8, &sp38);
                                        var_f30 = VECDotProduct(&var_r26->unk_D8, &sp38);
                                        sp14.x = var_r27->unk_D8.x - (var_f31 * sp38.x);
                                        sp14.y = var_r27->unk_D8.y - (var_f31 * sp38.y);
                                        sp14.z = var_r27->unk_D8.z - (var_f31 * sp38.z);
                                        sp8.x = var_r26->unk_D8.x - (var_f30 * sp38.x);
                                        sp8.y = var_r26->unk_D8.y - (var_f30 * sp38.y);
                                        sp8.z = var_r26->unk_D8.z - (var_f30 * sp38.z);
                                        if (var_r23 != 0) {
                                            sp14.x += 0.5f * (var_f30 * sp38.x);
                                            sp14.y += var_f30 * sp38.y;
                                            sp14.z += 0.5f * (var_f30 * sp38.z);
                                            sp8.x += 0.5f * (var_f31 * sp38.x);
                                            sp8.y += var_f31 * sp38.y;
                                            sp8.z += 0.5f * (var_f31 * sp38.z);
                                        }
                                        else {
                                            sp14.x -= 0.5f * (var_f31 * sp38.x);
                                            sp14.y -= var_f31 * sp38.y;
                                            sp14.z -= 0.5f * (var_f31 * sp38.z);
                                        }
                                        var_r27->unk_D8 = sp14;
                                        var_r26->unk_D8 = sp8;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        var_r31 = object->data;
        if (var_r31->unk_38 == 0) {
            if (var_r31->unk_CC.y < 0.0f) {
                var_r31->unk_CC.y = 0.0f;
            }
            sp38 = var_r31->unk_CC;
            sp38.y = 0.0f;
            var_f31 = VECMag(&sp38);
            if (var_f31 > (750.0f - var_r31->unk_88)) {
                var_f30 = (750.0f - var_r31->unk_88) / var_f31;
                VECScale(&sp38, &sp38, var_f30);
                var_r31->unk_CC.x = sp38.x;
                var_r31->unk_CC.z = sp38.z;
            }
        }
    }
    lbl_1_bss_30 = object->work[0];
}

void fn_1_9474(omObjData *object, Vec *arg1, Vec *arg2)
{
    Vec sp8;
    float var_f31;
    float var_f30;

    M421DllPlayerWork *work = object->data;

    sp8 = *arg1;
    if (work->unk_38 == 0) {
        var_f31 = VECMag(&sp8);
        if (var_f31 > (750.0f - work->unk_88)) {
            var_f30 = (750.0f - work->unk_88) / var_f31;
            VECScale(&sp8, &sp8, var_f30);
        }
    }
    *arg2 = sp8;
}

void fn_1_956C(omObjData *object)
{
    Vec sp8;
    float var_f31;
    float var_f30;

    M421DllPlayerWork *var_r31;
    M421DllPlayerWork *var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    for (var_r27 = 0; var_r27 < 2; var_r27++) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            var_r31 = lbl_1_bss_48[var_r29]->data;
            if (var_r31->unk_38 == 0) {
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    if (var_r29 != var_r28) {
                        var_r30 = lbl_1_bss_48[var_r28]->data;
                        if (var_r30->unk_38 == 0) {
                            VECSubtract(&var_r31->unk_CC, &var_r30->unk_CC, &sp8);
                            sp8.y = 0.0f;
                            var_f31 = VECMag(&sp8);
                            if (var_f31 < (var_r31->unk_80 + var_r30->unk_80)) {
                                if (var_f31 > 0.0f) {
                                    var_f31 = 0.5f * ((var_r31->unk_80 + var_r30->unk_80) - var_f31);
                                }
                                else {
                                    var_f31 = 0.5f * (var_r31->unk_80 + var_r30->unk_80);
                                    sp8.x = frandmod(0x3E8) - 0x1F4;
                                    sp8.z = frandmod(0x3E8) - 0x1F4;
                                }
                                VECNormalize(&sp8, &sp8);
                                VECScale(&sp8, &sp8, var_f31);
                                VECAdd(&var_r31->unk_CC, &sp8, &var_r31->unk_CC);
                                VECSubtract(&var_r30->unk_CC, &sp8, &var_r30->unk_CC);
                            }
                        }
                    }
                }
                if (var_r31->unk_CC.y < 0.0f) {
                    var_r31->unk_CC.y = 0.0f;
                }
                sp8 = var_r31->unk_CC;
                sp8.y = 0.0f;
                var_f31 = VECMag(&sp8);
                if (var_f31 > (750.0f - var_r31->unk_80)) {
                    var_f30 = (750.0f - var_r31->unk_80) / var_f31;
                    VECScale(&sp8, &sp8, var_f30);
                    var_r31->unk_CC.x = sp8.x;
                    var_r31->unk_CC.z = sp8.z;
                }
            }
        }
    }
}

void fn_1_982C(omObjData *object, u32 arg1)
{

    M421DllPlayerWork *work = object->data;
    if ((work->unk_08 != arg1) && (arg1 < 6)) {
        float var_f31 = REFRESH_RATE_F * lbl_1_data_1BC[arg1].unk_04;
        if (work->unk_08 < 0) {
            var_f31 = 0.0f;
        }
        work->unk_08 = arg1;
        CharModelMotionShiftSet(
            work->unk_00, object->motion[lbl_1_data_1BC[arg1].unk_00], REFRESH_RATE_F * lbl_1_data_1BC[arg1].unk_08, var_f31, lbl_1_data_1BC[arg1].unk_10);
        if (lbl_1_data_1BC[arg1].unk_0C >= 0.0f) {
            Hu3DMotionShiftStartEndSet(object->model[0], REFRESH_RATE_F * lbl_1_data_1BC[arg1].unk_08, REFRESH_RATE_F * lbl_1_data_1BC[arg1].unk_0C);
        }
    }
}

s32 fn_1_99B8(omObjData *object)
{

    M421DllPlayerWork *work = object->data;
    s32 var_r30 = 0;
    if ((CharModelMotionEndCheck(work->unk_00) != 0) && (CharModelMotionShiftIDGet(work->unk_00) < 0)) {
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_9A2C(omObjData *object, u32 arg1)
{
    s32 var_r27;

    var_r27 = 0;
    if (fn_1_99B8(object)) {
        fn_1_982C(object, arg1);
        var_r27 = 1;
    }
    return var_r27;
}

void fn_1_9BFC(float arg8, float arg9, float *arg0)
{
    arg0[0] = arg9;
    arg0[1] = arg8;
    arg0[3] = (2.0f * -arg8) / (arg9 * arg9);
    arg0[2] = -arg0[3] * arg9;
}

void fn_1_9C38(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    s32 var_r29;

    for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00 != 0) {
            VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            var_r31->unk2C += 2.0f;
            var_r31->unk40.a *= 0.98f;
            if (var_r31->unk00 < REFRESH_RATE_F / 2.5f) {
                var_r31->unk40.a = 0.9f * var_r31->unk40.a;
            }
            if (--var_r31->unk00 == 0) {
                var_r31->unk00 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_9DD0(omObjData *object, Vec *arg1)
{
    Vec sp18;
    GXColor sp14;
    u8 sp10[4];
    u8 spC[4];
    float var_f31;
    float var_f30;

    HsfanimStruct01 *var_r31;
    ParticleData *var_r30;
    s32 var_r29;
    M421DllPlayerWork *work;
    u32 var_r26;

    work = object->data;
    var_r30 = Hu3DData[object->model[4]].unk_120;
    GWCharColorGet(work->unk_00, &sp14);
    sp10[0] = 100.0f + (0.47058824f * sp14.r);
    sp10[1] = 100.0f + (0.47058824f * sp14.g);
    sp10[2] = 100.0f + (0.47058824f * sp14.b);
    spC[0] = (220.0f + (0.13725491f * sp14.r)) - sp10[0];
    spC[1] = (220.0f + (0.13725491f * sp14.g)) - sp10[1];
    spC[2] = (220.0f + (0.13725491f * sp14.b)) - sp10[2];
    var_r26 = 0x64;
    for (var_r31 = var_r30->unk_48, var_r29 = 0; var_r29 < var_r30->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00 != 0) {
            continue;
        }
        var_r31->unk00 = REFRESH_RATE_F * (0.6f + (0.0005f * frandmod(0x3E8)));
        var_f31 = frandmod(0x168);
        var_f30 = frandmod(0x168);
        sp18.y = sind(var_f31);
        var_f31 = cosd(var_f31);
        sp18.x = var_f31 * sind(var_f30);
        sp18.z = var_f31 * cosd(var_f30);
        var_f31 = 120.00001f;
        VECScale(&sp18, &sp18, var_f31);
        VECAdd(&sp18, arg1, &var_r31->unk34);
        var_r31->unk08.x = REFRESH_FREQ * (0.5f * sp18.x);
        var_r31->unk08.y = ((VERSION_PAL) ? 6.0f : 5.0f) + (REFRESH_FREQ * (0.5f * sp18.y));
        var_r31->unk08.z = REFRESH_FREQ * (0.5f * sp18.z);
        var_r31->unk30 = 0.0031415902f * frandmod(0x3E8);
        var_f31 = 0.001f * frandmod(0x3E8);
        var_r31->unk2C = 80.0f + (220.0f * var_f31);
        var_r31->unk40.a = 100.0f + (100.0f * (1.0f - var_f31));
        var_r31->unk40.r = sp10[0] + (spC[0] * var_f31);
        var_r31->unk40.g = sp10[1] + (spC[1] * var_f31);
        var_r31->unk40.b = sp10[2] + (spC[2] * var_f31);
        if (--var_r26 < 1) {
            break;
        }
    }
}

void fn_1_A528(omObjData *object)
{
    M421DllPlayerDLWork *work;
    s32 i;

    object->stat |= 0x100;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M421DllPlayerDLWork), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, sizeof(M421DllPlayerDLWork));
    work->unk_2F0 = GXGetTexBufferSize(0x280, 0x1E0, 5, 0, 0);
    work->unk_2F4 = HuMemDirectMallocNum(HEAP_SYSTEM, work->unk_2F0, MEMORY_DEFAULT_NUM);
    DCFlushRange(work->unk_2F4, work->unk_2F0);
    for (i = 0; i < 4; i++) {
        work->unk_40[i].r = work->unk_40[i].g = work->unk_40[i].b = 0xFF;
    }
    work->unk_40[0].a = 0x40;
    work->unk_40[1].a = 0;
    work->unk_40[2].a = 0xFF;
    work->unk_40[3].a = 0;
    for (i = 0; i < 4; i++) {
        work->unk_50[i][0].x = work->unk_50[i][0].y = work->unk_50[i][0].z = 0.0f;
    }
    for (i = 1; i < 0xE; i++) {
        work->unk_50[0][i].x = 100.0 * (1.7999999523162842 * sind((30.0f * i)));
        work->unk_50[0][i].y = 100.0 * (1.7999999523162842 * cosd((30.0f * i)));
        work->unk_50[0][i].z = 0.0f;
        work->unk_50[1][i].x = 100.0 * (2.0 * cosd((30.0f * i)));
        work->unk_50[1][i].y = 0.0f;
        work->unk_50[1][i].z = 100.0 * (2.0 * sind((30.0f * i)));
        work->unk_50[2][i].x = 100.0 * sind((30.0f * i));
        work->unk_50[2][i].y = 100.0 * (1.2000000476837158 * cosd((30.0f * i)));
        work->unk_50[2][i].z = 0.0f;
        work->unk_50[3][i].x = 100.0 * sind((30.0f * i));
        work->unk_50[3][i].y = 0.0f;
        work->unk_50[3][i].z = 100.0 * cosd((30.0f * i));
    }
    DCStoreRangeNoSync(work->unk_40, sizeof(work->unk_40));
    DCStoreRangeNoSync(work->unk_50, sizeof(work->unk_50));
    PPCSync();
    object->model[0] = Hu3DHookFuncCreate(fn_1_AB6C);
    Hu3DModelLayerSet(object->model[0], 4);
    object->model[1] = Hu3DHookFuncCreate(fn_1_ABDC);
    Hu3DModelLayerSet(object->model[1], 6);
    object->func = fn_1_AB68;
}

void fn_1_AB68(omObjData *object) { }

void fn_1_AB6C(ModelData *model, Mtx matrix)
{
    M421DllPlayerDLWork *work = lbl_1_bss_44->data;
    GXPixModeSync();
    GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
    GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB5A3, GX_FALSE);
    GXCopyTex(work->unk_2F4, GX_FALSE);
    GXPixModeSync();
}

void fn_1_ABDC(ModelData *model, Mtx matrix)
{
    Mtx sp118;
    Mtx spE8;
    Mtx spB8;
    Mtx sp88;
    Mtx sp58;
    Mtx sp28;
    GXTexObj sp8;

    M421DllPlayerDLWork *work;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    work = lbl_1_bss_44->data;
    MTXTrans(spE8, -400.0f, 400.0f, -700.0f);
    MTXConcat(Hu3DCameraMtx, spE8, sp88);
    GXLoadPosMtxImm(sp88, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXInitTexObj(&sp8, work->unk_2F4, 0x280, 0x1E0, 5, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sp8, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sp8, GX_TEXMAP0);
    GXSetNumTexGens(1);
    C_MTXLightPerspective(spB8, 41.5f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXConcat(spB8, Hu3DCameraMtx, spB8);
    MTXInverse(Hu3DCameraMtx, sp58);
    MTXConcat(sp58, sp88, sp118);
    MTXConcat(spB8, sp118, spE8);
    GXLoadTexMtxImm(spE8, 0x1E, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, 0x1E, 0, 0x7D);
    MTXInverse(Hu3DCameraMtx, sp28);
    sp28[0][3] = sp28[1][3] = sp28[2][3] = 0.0f;
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        work->unk_00[var_r30] = ((M421DllPlayerWork *)lbl_1_bss_48[var_r30]->data)->unk_F0;
        if (work->unk_30[var_r30] == 2) {
            var_r27 = 2;
        }
        else {
            var_r27 = 0;
        }
        var_r28 = var_r27;
        MTXTrans(spE8, work->unk_00[var_r30].x, work->unk_00[var_r30].y, work->unk_00[var_r30].z);
        MTXConcat(spE8, sp28, spE8);
        MTXConcat(Hu3DCameraMtx, spE8, sp88);
        GXLoadPosMtxImm(sp88, 0);
        MTXConcat(sp58, sp88, sp118);
        MTXConcat(spB8, sp118, spE8);
        GXLoadTexMtxImm(spE8, 0x1E, GX_MTX3x4);
        GXSetArray(GX_VA_POS, work->unk_50[var_r28], 0xC);
        GXSetArray(GX_VA_CLR0, &work->unk_40[var_r28], 4);
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 0xE);
        GXPosition1x8(0);
        GXPosition1x8(0);
        for (var_r29 = 1; var_r29 < 0xE; var_r29++) {
            GXColor1x8(var_r29);
            GXColor1x8(1);
        }
        MTXTrans(spE8, work->unk_00[var_r30].x, 0.0f, work->unk_00[var_r30].z);
        MTXConcat(Hu3DCameraMtx, spE8, sp88);
        GXLoadPosMtxImm(sp88, 0);
        MTXConcat(sp58, sp88, sp118);
        MTXConcat(spB8, sp118, spE8);
        GXLoadTexMtxImm(spE8, 0x1E, GX_MTX3x4);
        GXSetArray(GX_VA_POS, work->unk_50[var_r28 + 1], 0xC);
        GXSetArray(GX_VA_CLR0, &work->unk_40[var_r28], 4);
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 0xE);
        GXPosition1x8(0);
        GXPosition1x8(0);
        for (var_r29 = 1; var_r29 < 0xE; var_r29++) {
            GXColor1x8(var_r29);
            GXColor1x8(1);
        }
    }
}
