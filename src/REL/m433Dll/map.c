#include "dolphin/mtx.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/flag.h"
#include "game/frand.h"
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

#include "REL/m433Dll.h"

typedef struct M433DllBss38Struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ char unk01[2];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ char unk05[3];
    /* 0x08 */ float unk_08;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ Vec unk_24;
    /* 0x30 */ Vec unk_30;
    /* 0x3C */ char unk3C[0xC];
    /* 0x48 */ Vec unk_48;
    union {
        struct {
            /* 0x54 */ float unk_54;
            /* 0x58 */ float unk_58;
            char unk5C[4];
            /* 0x60 */ float unk_60;
        };
        struct {
            /* 0x54 */ s16 unk_54_s16[0x20];
        };
    };
} M433DllBss38Struct; /* size = 0x94 */

typedef struct M433DllMapWork {
    char unk00;
    u8 unk_01;
    u8 unk_02;
    char unk03;
    u8 unk_04;
    char unk08[4];
    Vec unk_0C;
    Vec unk_18;
    char unk24[0xC];
    Vec unk_30;
    Vec unk_3C;
    char unk48[0xC];
    s16 unk_54;
    char unk56[0x3E];
} M433DllMapWork; /* size 0x94 */

typedef struct M433DllMapWork2 {
    u8 unk_00;
    Vec unk_04;
    Vec unk_10;
    Vec unk_1C;
    Vec unk_28;
    Vec unk_34;
    Vec unk_40;
    char unk4C[0xE4];
    float unk_130;
    float unk_134;
    float unk_138;
    char unk13C[4];
    float unk_140;
    float unk_144;
    float unk_148;
    float unk_14C[3];
    float unk_158[3];
    float unk_164[3];
    float unk_170[3];
    float unk_17C[3];
    u16 unk_188[3];
} M433DllMapWork2; /* size 0x190 */

typedef struct M433DllUnkStruct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    char unk06[0x42];
} M433DllUnkStruct; /* size 0x48 */

void fn_1_2AC4(omObjData *object);
void fn_1_2CE0(omObjData *object);
void fn_1_32CC(omObjData *object);
void fn_1_39AC(omObjData *object);
void fn_1_3C1C(omObjData *object);
s16 fn_1_3E5C(s32 arg0, s16 arg1, ParticleHook arg2);
void fn_1_3F14(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_4A94(omObjData *object);
void fn_1_4BA0(omObjData *object);
void fn_1_4ED4(float arg8, Vec *arg0, Vec *arg1, float arg9);
void fn_1_5068(void);
void *fn_1_50A8(s32 arg0);
void fn_1_51DC(void);
s32 fn_1_5260(void);
float fn_1_52B4(float arg8, float arg9, float argA);
void fn_1_541C(Mtx arg0, float arg8, float arg9, float argA);
void fn_1_553C(Mtx arg0, Vec *arg1);
extern s32 lbl_1_bss_34;

omObjData *lbl_1_bss_7B0;
omObjData *lbl_1_bss_7AC;
omObjData *lbl_1_bss_7A8;
void *lbl_1_bss_728[0x20];
M433DllBss38Struct lbl_1_bss_38[0xC];

void fn_1_2894(Process *process)
{
    s32 var_r31;
    s32 var_r29;

    lbl_1_bss_34 = 1;
    lbl_1_bss_7AC = omAddObjEx(process, 0x1E, 8, 0, -1, fn_1_2CE0);
    lbl_1_bss_7A8 = omAddObjEx(process, 0x1F, 3, 6, -1, fn_1_39AC);
    lbl_1_bss_7B0 = omAddObjEx(process, 0x1D, 1, 0, -1, fn_1_4A94);
    var_r29 = frand() & 0x1F;
    for (var_r31 = 0; var_r31 < var_r29; var_r31++) {
        fn_1_5260();
    }
    fn_1_5068();
}

void fn_1_2984(void)
{
    fn_1_51DC();
}

omObjFunc fn_1_29A4(Process *process, omObjData *object)
{
    M433DllWork *work = object->data;
    CRot.x = 54.3f;
    CRot.y = 22.3f;
    CRot.z = 0.0f;
    Center.x = -130.1f;
    Center.y = 885.0f;
    Center.z = -900.3f;
    CZoom = 1100.0f;
    fn_1_4ED4(0.0f, &Center, &CRot, CZoom);
    object->work[0] = 0xB4;
    work->unk_0C = 1;
    return fn_1_2AC4;
}

void fn_1_2AC4(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    M433DllWork *work = object->data;

    fn_1_584(object);
    if (object->work[0] == 120.0f) {
        sp14.x = 0.0f;
        sp14.y = -10.0f;
        sp14.z = -207.5f;
        sp8.x = -26.5f;
        sp8.y = 0.0f;
        sp8.z = 0.0f;
        var_f31 = 1400.0f;
        fn_1_4ED4(90.0f, &sp14, &sp8, var_f31);
    }
    if (object->work[0] == 48.0f) {
        sp14.x = 0.0f;
        sp14.y = 200.0f;
        sp14.z = 0.0f;
        sp8.x = -30.0f;
        sp8.y = 0.0f;
        sp8.z = 0.0f;
        var_f31 = 1900.0f;
        fn_1_4ED4(object->work[0], &sp14, &sp8, var_f31);
    }
    if (--object->work[0] == 0) {
        work->unk_0C = 2;
        fn_1_618(object);
        lbl_1_bss_7B0->func = NULL;
    }
}

void fn_1_2CE0(omObjData *object)
{
    Vec sp8[0x10] = {
        { 475.0f, 800.0f, -1400.0f },
        { -300.0f, 700.0f, -1400.0f },
        { 300.0f, 875.0f, -1450.0f },
        { -575.0f, 850.0f, -1550.0f },
        { 350.0f, 750.0f, -1500.0f },
        { -450.0f, 775.0f, -1550.0f },
        { 325.0f, 725.0f, -1450.0f },
        { -525.0f, 725.0f, -1500.0f },
        { 575.0f, 850.0f, -1550.0f },
        { -350.0f, 750.0f, -1500.0f },
        { 450.0f, 775.0f, -1550.0f },
        { -325.0f, 725.0f, -1450.0f },
        { 525.0f, 725.0f, -1500.0f },
        { -475.0f, 800.0f, -1400.0f },
        { 300.0f, 700.0f, -1400.0f },
        { -300.0f, 875.0f, -1450.0f },
    };
    M433DllBss38Struct *var_r31;
    s32 var_r30;
    M433DllUnkStruct *var_r28;
    s32 i;
    s32 var_r26;

    var_r30 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 0xCD));
    object->model[0] = var_r30;
    var_r30 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 0xCE));
    object->model[1] = var_r30;
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(var_r30, 0.5f);
    var_r30 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 0xCF));
    object->model[2] = var_r30;
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    var_r30 = fn_1_3E5C(DATA_MAKE_NUM(DATADIR_M425, 0x05), 1, fn_1_3F14);
    object->model[3] = var_r30;
    Hu3DParticleBlendModeSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 6);
    var_r28 = ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_1C;
    var_r28->unk_02 = 0;
    HuDataDirClose(DATA_MAKE_NUM(DATADIR_M425, 0x05));
    var_r30 = fn_1_3E5C(DATA_MAKE_NUM(DATADIR_M433, 0xD3), 0xA, fn_1_3F14);
    object->model[4] = var_r30;
    Hu3DParticleBlendModeSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 6);
    var_r28 = ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_1C;
    var_r28->unk_02 = 1;
    var_r30 = fn_1_3E5C(DATA_MAKE_NUM(DATADIR_M433, 0xD2), 4, fn_1_3F14);
    object->model[5] = var_r30;
    Hu3DParticleBlendModeSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 6);
    var_r28 = ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_1C;
    var_r28->unk_02 = 2;
    var_r30 = fn_1_3E5C(DATA_MAKE_NUM(DATADIR_M433, 0xD1), 6, fn_1_3F14);
    object->model[6] = var_r30;
    Hu3DParticleBlendModeSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 6);
    var_r28 = ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_1C;
    var_r28->unk_02 = 3;
    for (i = 0; i < 0xC; i++) {
        var_r31 = &lbl_1_bss_38[i];
        var_r30 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M425, 0x02));
        var_r31->unk_00 = var_r30;
        var_r31->unk_0C.x = sp8[i].x;
        var_r31->unk_0C.y = sp8[i].y - 300.0f;
        var_r31->unk_0C.z = 800.0f + sp8[i].z;
        Hu3DModelPosSet(var_r30, var_r31->unk_0C.x, var_r31->unk_0C.y, var_r31->unk_0C.z);
        Hu3DMotionSpeedSet(var_r30, 6.0f);
        var_r31->unk_03 = var_r31->unk_04 = 0;
        var_r31->unk_18.x = var_r31->unk_18.y = var_r31->unk_18.z = 0.0f;
        var_r31->unk_24.x = var_r31->unk_24.y = var_r31->unk_24.z = 1.0f;
        var_r31->unk_48.x = var_r31->unk_48.y = var_r31->unk_48.z = 0.0f;
        var_r31->unk_30.x = var_r31->unk_0C.x;
        var_r31->unk_30.y = var_r31->unk_0C.y;
        var_r31->unk_30.z = var_r31->unk_0C.z;
        if ((i & 1) != 0) {
            var_r31->unk_18.y = 90.0f;
            var_r31->unk_0C.y += 650.0;
            var_r31->unk_0C.x -= 1000.0 + (200.0f * ((fn_1_5260() - 0x8000) / 32768.0f));
        }
        else {
            var_r31->unk_18.y = 90.0f;
            var_r31->unk_0C.x += 200.0f * ((fn_1_5260() - 0x8000) / 32768.0f);
        }
        var_r31->unk_18.y += 10.0f * ((fn_1_5260() - 0x8000) / 32768.0f);
        var_r31->unk_0C.z = var_r31->unk_0C.z - 400.0;
        var_r31->unk_08 = 100.0f * (0.1f + (0.02f * (fn_1_5260() / 65536.0f)));
        for (var_r26 = 0; var_r26 < 0x20; var_r26++) {
            var_r31->unk_54_s16[var_r26] = 0;
        }
        var_r31->unk_60 = var_r31->unk_08;
    }
    HuDataDirClose(DATA_MAKE_NUM(DATADIR_M425, 0x02));
    HuAudFXPlayVol(0x6A3, 0x41);
    object->func = fn_1_32CC;
}

void fn_1_32CC(omObjData *object)
{
    Mtx sp14;
    Vec sp8;
    M433DllBss38Struct *var_r31;
    s32 i;

    for (i = 0; i < 0xC; i++) {
        var_r31 = &lbl_1_bss_38[i];
        switch (var_r31->unk_04) {
            case 0:
                if (var_r31->unk_08 < var_r31->unk_60) {
                    var_r31->unk_08 += 0.4f;
                }
                if ((s32)(64.0f * (fn_1_5260() / 65536.0f)) == 0) {
                    Hu3DMotionTimeSet(var_r31->unk_00, 0.0f);
                }
                if (Hu3DMotionEndCheck(var_r31->unk_00) != 0) {
                    var_r31->unk_48.y = -3.8933334f;
                }
                else {
                    var_r31->unk_48.y = -1.2166667f;
                }
                var_r31->unk_54 += 0.1f * ((fn_1_5260() - 0x8000) / 32768.0f);
                var_r31->unk_58 += var_r31->unk_54;
                if (var_r31->unk_58 > 180.0f) {
                    var_r31->unk_58 -= 180.0f;
                }
                if (var_r31->unk_58 < -180.0f) {
                    var_r31->unk_58 += 180.0f;
                }
                var_r31->unk_18.x = -30.0 * sind(var_r31->unk_58) * sind(var_r31->unk_18.y);
                var_r31->unk_18.z = -30.0 * sind(var_r31->unk_58) * cosd(var_r31->unk_18.y);
                if (var_r31->unk_0C.y <= 500.0f || fabs(var_r31->unk_0C.x) > 1600.0) {
                    var_r31->unk_48.y = 0.0f;
                    var_r31->unk_54_s16[6] = 0xB4;
                    var_r31->unk_08 *= 0.75f;
                    var_r31->unk_04++;
                }
                break;
            case 1:
                var_r31->unk_18.y += 1.0f;
                var_r31->unk_18.x = 0.0f;
                var_r31->unk_18.z = 60.0 * sind(var_r31->unk_54_s16[6]) * cosd(var_r31->unk_18.y);
                if (--var_r31->unk_54_s16[6] == 0) {
                    Hu3DModelAttrSet(var_r31->unk_00, HU3D_MOTATTR_LOOP);
                    Hu3DMotionSpeedSet(var_r31->unk_00, 6.0f);
                    var_r31->unk_48.y = 4.866667f;
                    var_r31->unk_04++;
                }
                break;
            case 2:
                if (var_r31->unk_08 > 4.0f) {
                    var_r31->unk_08 -= 0.1f;
                    var_r31->unk_48.y += 0.73f;
                }
                var_r31->unk_48.y += -0.5475f;
                if (var_r31->unk_48.y < 0.0f) {
                    Hu3DModelAttrReset(var_r31->unk_00, HU3D_MOTATTR_LOOP);
                    Hu3DMotionSpeedSet(var_r31->unk_00, 2.0f);
                    var_r31->unk_60 = 100.0f * (0.1f + (0.02f * (fn_1_5260() / 65536.0f)));
                    var_r31->unk_04 = 0;
                }
                break;
        }
        var_r31->unk_48.x = var_r31->unk_08 * sind(var_r31->unk_18.y);
        var_r31->unk_48.z = var_r31->unk_08 * cosd(var_r31->unk_18.y);
        var_r31->unk_0C.x += var_r31->unk_48.x;
        var_r31->unk_0C.y += var_r31->unk_48.y;
        var_r31->unk_0C.z += var_r31->unk_48.z;
        if (var_r31->unk_0C.z >= -500.0f) {
            var_r31->unk_0C.z = -500.0f;
        }
        Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_0C.x, var_r31->unk_0C.y, var_r31->unk_0C.z);
        fn_1_541C(sp14, var_r31->unk_18.x, -var_r31->unk_18.y, var_r31->unk_18.z);
        fn_1_553C(sp14, &sp8);
        Hu3DModelRotSetV(var_r31->unk_00, &sp8);
    }
}

void fn_1_39AC(omObjData *object)
{
    s32 var_r29;
    s32 var_r28;

    s32 sp18[4] = { 0x004000D4, 0x004000D5, 0x004000D6, 0x004000D7 };
    s32 sp8[4] = { 0x0040000C, 0x00400010, 0x0040000F, 0x0040000E };
    M433DllMapWork *work = fn_1_50A8(sizeof(M433DllMapWork));
    object->data = work;
    if (lbl_1_bss_34 != 0) {
        var_r28 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 0x0B));
    }
    else {
        var_r28 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 0x62));
    }
    object->model[0] = var_r28;
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (lbl_1_bss_34 != 0) {
            object->motion[var_r29] = Hu3DJointMotionFile(var_r28, sp8[var_r29]);
        }
        else {
            object->motion[var_r29] = Hu3DJointMotionFile(var_r28, sp18[var_r29]);
        }
    }
    Hu3DMotionSet(var_r28, object->motion[0]);
    Hu3DModelAttrSet(var_r28, HU3D_MOTATTR_LOOP);
    work->unk_01 = work->unk_02 = 0;
    work->unk_04 = 0;
    work->unk_54 = 0;
    work->unk_0C.x = 0.0f;
    work->unk_0C.y = 180.0f;
    work->unk_0C.z = -490.0f;
    work->unk_30 = work->unk_0C;
    work->unk_18.x = work->unk_18.y = work->unk_18.z = 0.0f;
    work->unk_3C = work->unk_18;
    omSetTra(object, work->unk_0C.x, work->unk_0C.y, work->unk_0C.z);
    omSetRot(object, work->unk_18.x, work->unk_18.y, work->unk_18.z);
    object->func = fn_1_3C1C;
}

void fn_1_3C1C(omObjData *object)
{
    M433DllMapWork *work;
    s32 var_r29;
    s32 var_r28;

    work = object->data;
    var_r28 = object->model[0];
    switch (work->unk_04) {
        case 0:
            work->unk_01 = 0;
            var_r29 = 0x40000001;
            break;
        case 1:
            work->unk_3C.y = 0.0f;
            work->unk_01 = 1;
            var_r29 = 0x40000001;
            if (work->unk_54++ >= 0x5A) {
                work->unk_54 = 0;
                work->unk_04 = 0;
            }
            break;
        case 2:
            work->unk_3C.y = 0.0f;
            work->unk_01 = 2;
            var_r29 = 0;
            if (Hu3DMotionEndCheck(var_r28) != 0) {
                work->unk_04 = 0;
            }
            break;
        case 3:
            work->unk_3C.y = 0.0f;
            work->unk_01 = 3;
            var_r29 = 0x40000001;
            break;
        case 4:
            work->unk_3C.y = 0.0f;
            work->unk_04 = 0;
            break;
        case 5:
            work->unk_3C.y = 50.0f;
            work->unk_04 = 0;
            break;
        case 6:
            work->unk_3C.y = -50.0f;
            work->unk_04 = 0;
            break;
    }
    if (work->unk_01 != work->unk_02) {
        work->unk_02 = work->unk_01;
        Hu3DMotionShiftSet(var_r28, object->motion[work->unk_01], 0.0f, 8.0f, var_r29);
        switch (work->unk_01) {
            case 1:
                HuAudFXPlay(0x43);
                break;
            case 2:
                HuAudFXPlay(0x45);
                break;
        }
    }
    work->unk_18.y = fn_1_52B4(work->unk_18.y, work->unk_3C.y, 0.9f);
    omSetTra(object, work->unk_0C.x, work->unk_0C.y, work->unk_0C.z);
    omSetRot(object, work->unk_18.x, work->unk_18.y, work->unk_18.z);
}

s16 fn_1_3E5C(s32 sp8, s16 spC, ParticleHook sp10)
{
    M433DllUnkStruct *var_r31;
    s32 var_r30;
    ParticleData *var_r29;
    AnimData *var_r28;

    var_r28 = HuSprAnimRead(HuDataReadNum(sp8, MEMORY_DEFAULT_NUM));
    var_r30 = Hu3DParticleCreate(var_r28, spC);
    Hu3DParticleHookSet(var_r30, sp10);
    var_r29 = Hu3DData[var_r30].unk_120;
    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M433DllUnkStruct), MEMORY_DEFAULT_NUM);
    var_r29->unk_1C = var_r31;
    var_r31->unk_00 = var_r30;
    var_r31->unk_04 = 0;
    return var_r30;
}

void fn_1_3F14(ModelData *model, ParticleData *var_r30, Mtx matrix)
{
    float var_f29;
    float var_f26;
    float var_f25;
    float var_f24;
    HsfanimStruct01 *var_r31;
    s32 var_r28;
    float sp54[4] = { 1000.0f, 200.0f, 600.0f, 1200.0f };
    float sp44[4] = { 1.0f, 0.6f, 0.3f, 0.425f };
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    s16 sp8 = 0;
    M433DllUnkStruct *var_r29 = var_r30->unk_1C;
    switch (var_r29->unk_04) {
        case 0:
            var_r30->unk_00 = 0x54;
            var_r31 = var_r30->unk_48;
            if (var_r29->unk_02 != 0) {
                sp14.x = 0.0f;
                sp14.y = -4700.0f;
                sp14.z = 4450.0f;
                var_f29 = 1.0f / sqrtf((sp14.z * sp14.z) + ((sp14.x * sp14.x) + (sp14.y * sp14.y)));
                sp14.x *= var_f29;
                sp14.y *= var_f29;
                sp14.z *= var_f29;
                var_f24 = 4000.0f / var_r30->unk_30;
                for (var_r28 = 0; var_r28 < var_r30->unk_30; var_r28++, var_r31++) {
                    var_f26 = 500.0f + ((var_f24 * var_r28) + (0.25f * var_f24 * (fn_1_5260() / 65536.0f)));
                    var_f25 = var_f26 / 4000.0f;
                    var_r31->unk14.x = var_f26;
                    var_r31->unk34.x = var_f26 * sp14.x;
                    var_r31->unk34.y = 5500.0f + (var_f26 * sp14.y);
                    var_r31->unk34.z = -3950.0f + (var_f26 * sp14.z);
                    var_r31->unk2C = (0.3f + (0.7f * (var_f25 * var_f25))) * (sp54[var_r29->unk_02] * (0.7f + (0.3f * (fn_1_5260() / 65536.0f))));
                    var_r31->unk40.r = (s32)(160.0f * (fn_1_5260() / 65536.0f)) + 0x20;
                    var_r31->unk40.g = (s32)(96.0f * (fn_1_5260() / 65536.0f)) + 0x20;
                    var_r31->unk40.b = (s32)(128.0f * (fn_1_5260() / 65536.0f)) + 0x20;
                    var_r31->unk40.a = ((1.0 - (0.4 * var_f25)) * (255.0f * sp44[var_r29->unk_02])) - (s32)(16.0f * (fn_1_5260() / 65536.0f));
                }
                var_r29->unk_04++;
            }
            else {
                var_r31->unk34.x = 0.0f;
                var_r31->unk34.y = 5500.0f;
                var_r31->unk34.z = -3950.0f;
                var_r31->unk2C = 1000.0f;
            }
            break;
        case 1:
            sp38.x = sind(CRot.y) * cosd(CRot.x);
            sp38.y = -sind(CRot.x);
            sp38.z = cosd(CRot.y) * cosd(CRot.x);
            sp2C.x = -(Center.x + (1.25f * (sp38.x * CZoom)));
            sp2C.y = 5500.0f - (Center.y + (sp38.y * CZoom));
            sp2C.z = -3950.0f - (Center.z + (1.25f * (sp38.z * CZoom)));
            var_f29 = 1.0f / sqrtf((sp2C.z * sp2C.z) + ((sp2C.x * sp2C.x) + (sp2C.y * sp2C.y)));
            sp2C.x *= var_f29;
            sp2C.y *= var_f29;
            sp2C.z *= var_f29;
            var_f29 = -((-sp2C.z * -sp38.z) + ((-sp2C.x * -sp38.x) + (-sp2C.y * -sp38.y)));
            sp20.x = -sp38.x + (-2.0f * sp2C.x * var_f29);
            sp20.y = -sp38.y + (-2.0f * sp2C.y * var_f29);
            sp20.z = -sp38.z + (-2.0f * sp2C.z * var_f29);
            for (var_r31 = var_r30->unk_48, var_r28 = 0; var_r28 < var_r30->unk_30; var_r28++, var_r31++) {
                var_r31->unk34.x = sp20.x * var_r31->unk14.x;
                var_r31->unk34.y = 5500.0f + (sp20.y * var_r31->unk14.x);
                var_r31->unk34.z = -3950.0f + (sp20.z * var_r31->unk14.x);
                if (var_r30->unk_00 < 0xA) {
                    var_r31->unk40.a *= 0.8f;
                }
            }
            var_r30->unk_00--;
            if (var_r30->unk_00 == 0) {
                Hu3DModelAttrReset(var_r29->unk_00, HU3D_ATTR_PARTICLE_KILL);
                Hu3DModelKill(var_r29->unk_00);
                return;
            }
            break;
    }
    DCFlushRange(var_r30->unk_48, var_r30->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_4A94(omObjData *var_r30)
{
    M433DllMapWork2 *work = fn_1_50A8(sizeof(M433DllMapWork2));
    var_r30->data = work;
    work->unk_148 = work->unk_144 = 0.0f;
    work->unk_140 = 1.0f;
    work->unk_10.x = work->unk_28.x = -30.0f;
    work->unk_10.y = work->unk_28.y = 0.0f;
    work->unk_10.z = work->unk_28.z = 0.0f;
    work->unk_04.x = work->unk_1C.x = 0.0f;
    work->unk_04.y = work->unk_1C.y = 200.0f;
    work->unk_04.z = work->unk_1C.z = 0.0f;
    work->unk_130 = work->unk_134 = 1900.0f;
    work->unk_188[0] = work->unk_188[1] = work->unk_188[2] = 0;
    var_r30->func = fn_1_4BA0;
}

void fn_1_4BA0(omObjData *object)
{
    float var_f31;
    s32 var_r30;
    M433DllMapWork2 *work = object->data;
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
    }
    CRot.x = work->unk_10.x;
    CRot.y = work->unk_10.y;
    CRot.z = work->unk_10.z;
    Center.x = work->unk_04.x;
    Center.y = work->unk_04.y;
    Center.z = work->unk_04.z;
    CZoom = work->unk_130;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        work->unk_17C[var_r30] = 0.0f;
        if (work->unk_188[var_r30] != 0) {
            work->unk_17C[var_r30] = work->unk_14C[var_r30] * sind(work->unk_164[var_r30]);
            work->unk_164[var_r30] += work->unk_170[var_r30];
            work->unk_14C[var_r30] *= work->unk_158[var_r30];
            work->unk_188[var_r30] -= 1;
        }
    }
    Center.x += work->unk_17C[0];
    Center.y += work->unk_17C[1];
    Center.z += work->unk_17C[2];
}

void fn_1_4ED4(float arg8, Vec *arg0, Vec *arg1, float arg9)
{
    M433DllMapWork2 *work = lbl_1_bss_7B0->data;
    work->unk_00 = 0;
    work->unk_144 = arg8;
    work->unk_148 = arg8;
    if (arg8 == 0.0f) {
        work->unk_04.x = arg0->x;
        work->unk_04.y = arg0->y;
        work->unk_04.z = arg0->z;
        work->unk_10.x = arg1->x;
        work->unk_10.y = arg1->y;
        work->unk_10.z = arg1->z;
        work->unk_130 = arg9;
        return;
    }
    work->unk_1C = work->unk_04;
    work->unk_34.x = arg0->x;
    work->unk_34.y = arg0->y;
    work->unk_34.z = arg0->z;
    work->unk_28 = work->unk_10;
    work->unk_40.x = arg1->x;
    work->unk_40.y = arg1->y;
    work->unk_40.z = arg1->z;
    work->unk_134 = work->unk_130;
    work->unk_138 = arg9;
}

void fn_1_4FC0(float arg8)
{
    M433DllMapWork2 *var_r31 = lbl_1_bss_7B0->data;
    var_r31->unk_140 = arg8;
}

void fn_1_4FE8(u8 arg0, u16 arg1, float arg8, float arg9, float argA)
{
    M433DllMapWork2 *var_r31 = lbl_1_bss_7B0->data;
    var_r31->unk_188[arg0] = arg1;
    var_r31->unk_14C[arg0] = arg8;
    var_r31->unk_158[arg0] = arg9;
    var_r31->unk_170[arg0] = argA;
    var_r31->unk_164[arg0] = 90.0f;
}

void fn_1_5068(void)
{
    s32 i;
    for (i = 0; i < 0x20; i++) {
        lbl_1_bss_728[i] = NULL;
    }
}

void *fn_1_50A8(s32 arg0)
{
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (!lbl_1_bss_728[i]) {
            break;
        }
    }
    if (i == 0x20) {
        return NULL;
    }
    lbl_1_bss_728[i] = HuMemDirectMallocNum(HEAP_SYSTEM, arg0, MEMORY_DEFAULT_NUM);
    return lbl_1_bss_728[i];
}

void fn_1_5148(u32 sp8)
{
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (lbl_1_bss_728[i] == (void *)sp8) {
            break;
        }
    }
    if (i != 0x20) {
        HuMemDirectFree(lbl_1_bss_728[i]);
        lbl_1_bss_728[i] = NULL;
    }
}

void fn_1_51DC(void)
{
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (lbl_1_bss_728[i]) {
            HuMemDirectFree(lbl_1_bss_728[i]);
            lbl_1_bss_728[i] = NULL;
        }
    }
}

u32 lbl_1_data_C4 = 0x41C64E6D;

s32 fn_1_5260(void)
{
    lbl_1_data_C4 *= 0x41C64E6D;
    lbl_1_data_C4 += 0x3039;
    return lbl_1_data_C4 >> 0x10;
}

float fn_1_52B4(float arg8, float arg9, float argA)
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

void fn_1_541C(Mtx arg0, float arg8, float arg9, float argA)
{
    Mtx sp38;
    Mtx sp8;

    if (argA != 0.0f) {
        PSMTXRotRad(arg0, 0x5A, MTXDegToRad(argA));
    }
    else {
        PSMTXIdentity(arg0);
    }
    if (arg8 != 0.0f) {
        PSMTXRotRad(sp38, 0x58, MTXDegToRad(arg8));
        PSMTXConcat(sp38, arg0, arg0);
    }
    if (arg9 != 0.0f) {
        PSMTXRotRad(sp8, 0x59, MTXDegToRad(arg9));
        PSMTXConcat(sp8, arg0, arg0);
    }
}

void fn_1_553C(Mtx arg0, Vec *arg1)
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

void fn_1_58D8(s32 arg0)
{
    M433DllMapWork *work = lbl_1_bss_7A8->data;
    work->unk_04 = arg0;
}
