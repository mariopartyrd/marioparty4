#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"
#include "game/wipe.h"


#include "REL/m408Dll.h"

#ifndef __MWERKS__
#include "game/frand.h"
#endif

s32 lbl_1_bss_160[2];
AnimData *lbl_1_bss_14C[5];
s16 lbl_1_bss_148;
s32 lbl_1_bss_144;
u32 lbl_1_bss_140;
omObjData *lbl_1_bss_13C;
s32 lbl_1_bss_138;
s32 lbl_1_bss_134;
s32 lbl_1_bss_130;
HsfConstData *lbl_1_bss_128[2];
void *lbl_1_bss_120[2];
HsfDrawData *lbl_1_bss_11C;
s16 lbl_1_bss_118;

float lbl_1_data_198 = 1000;
u32 lbl_1_data_19C = 0x41C64E6D;

void fn_1_C4E4(Process *objman);

void fn_1_C44C(Process *objman)
{
    s32 i;
    lbl_1_bss_144 = 0;
    lbl_1_bss_140 = 0;
    lbl_1_bss_138 = lbl_1_bss_134 = lbl_1_bss_130 = -1;
    fn_1_C4E4(objman);
    for (i = 0; i < (frand() & 0x7F); i++) {
        fn_1_11670();
    }
}

void fn_1_C530(omObjData *object);

void fn_1_C4E4(Process *objman)
{
    lbl_1_bss_13C = omAddObjEx(objman, 30, 35, 0, -1, fn_1_C530);
}

typedef struct work_f4b0 {
    s16 unk0;
    s16 unk2;
    GXColor *unk4;
    HsfVector2f *unk8;
    u8 *unkC;
    union {
        s16 unk10[32];
        float unk10_f[16];
    };
} WorkF4B0;

void fn_1_CD14(omObjData *object);

s16 fn_1_D978(AnimData *arg0, s16 arg1, ParticleHook arg2);
void fn_1_E310(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_EEF8(ModelData *model, ParticleData *particle, Mtx matrix);

WorkF4B0 *fn_1_F4B0(s16 arg0, s16 arg1);

void fn_1_C530(omObjData *object)
{
    s32 temp_r31;
    float *temp_r29;
    s32 temp_r28;

    u16 *spC;
    WorkF4B0 *sp8;
    object->data = spC = HuMemDirectMallocNum(HEAP_SYSTEM, 436 * sizeof(u16), MEMORY_DEFAULT_NUM);
    lbl_1_bss_14C[0] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M408, 0x24), MEMORY_DEFAULT_NUM));
    lbl_1_bss_14C[1] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M408, 0x25), MEMORY_DEFAULT_NUM));
    lbl_1_bss_14C[2] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M408, 0x26), MEMORY_DEFAULT_NUM));
    lbl_1_bss_14C[4] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M408, 0x28), MEMORY_DEFAULT_NUM));
    lbl_1_bss_14C[3] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M408, 0x29), MEMORY_DEFAULT_NUM));
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x1A));
    omSetSca(object, 0.1f, 0.1f, 0.1f);
    temp_r31 = object->model[0];
    Hu3DModelLayerSet(temp_r31, 1);
    Hu3DModelAttrSet(temp_r31, HU3D_ATTR_DISPOFF);
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x1E));
    temp_r31 = object->model[4];
    Hu3DModelLayerSet(temp_r31, 1);
    Hu3DModelScaleSet(temp_r31, 0.1f, 0.1f, 0.1f);
    Hu3DModelAttrSet(temp_r31, HU3D_ATTR_DISPOFF);
    object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x20));
    temp_r31 = object->model[5];
    Hu3DModelLayerSet(temp_r31, 1);
    Hu3DModelScaleSet(temp_r31, 0.1f, 0.1f, 0.1f);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x1B));
    temp_r31 = object->model[2];
    Hu3DModelLayerSet(temp_r31, 1);
    Hu3DModelPosSet(temp_r31, -20, -10, -150);
    Hu3DModelScaleSet(temp_r31, 0.14500001f, 0.14500001f, 0.14500001f);
    Hu3DModelAttrSet(temp_r31, HU3D_ATTR_DISPOFF);
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x1D));
    temp_r31 = object->model[3];
    Hu3DModelPosSet(temp_r31, 0, -50, -500);
    Hu3DModelScaleSet(temp_r31, 0.15f, 0.15f, 0.15f);
    Hu3DModelLayerSet(temp_r31, 0);
    Hu3DModelAttrSet(temp_r31, HU3D_ATTR_DISPOFF);
    sp8 = fn_1_F4B0(temp_r31, temp_r31);
    object->model[9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x1C));
    temp_r31 = object->model[9];
    lbl_1_bss_148 = temp_r31;
    Hu3DModelScaleSet(temp_r31, 0.11000001f, 0.1f, 0.11000001f);
    Hu3DModelPosSet(temp_r31, 0, 10000, 0);
    Hu3DModelLayerSet(temp_r31, 1);
    Hu3DModelAttrSet(temp_r31, HU3D_ATTR_DISPOFF);
    object->model[11] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x1F));
    temp_r31 = object->model[11];
    Hu3DModelPosSet(temp_r31, 0, 10000, 0);
    Hu3DModelLayerSet(temp_r31, 1);
    Hu3DModelScaleSet(temp_r31, 0.105f, 0.1f, 0.105f);
    Hu3DModelAttrSet(temp_r31, HU3D_ATTR_DISPOFF);
    object->model[12] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x23));
    temp_r31 = object->model[12];
    Hu3DModelLayerSet(temp_r31, 3);
    Hu3DModelPosSet(temp_r31, 0, 5000, 0);
    Hu3DModelScaleSet(temp_r31, 0.1f, 0.1f, 0.1f);
    Hu3DModelAttrSet(temp_r31, HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(temp_r31, 0);
    object->model[19] = temp_r31 = fn_1_D978(lbl_1_bss_14C[0], 80, fn_1_E310);
    Hu3DModelLayerSet(temp_r31, 1);
    Hu3DModelPosSet(temp_r31, 0, 5100, 0);
    Hu3DParticleBlendModeSet(temp_r31, 1);
    temp_r29 = ((ParticleData *)Hu3DData[temp_r31].unk_120)->unk_1C;
    temp_r29[2] = 140;
    object->model[14] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x21));
    object->model[15] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x22));
    object->model[16] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x21));
    object->model[17] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x22));
    for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
        temp_r31 = object->model[temp_r28 + 14];
        Hu3DModelLayerSet(temp_r31, 3);
        Hu3DModelRotSet(temp_r31, 0, frandmod(360), 0);
        Hu3DModelScaleSet(temp_r31, 0.1f, 0.1f, 0.1f);
        Hu3DModelAttrSet(temp_r31, HU3D_ATTR_DISPOFF);
        Hu3DMotionSpeedSet(temp_r31, 0);
    }
    object->model[6] = temp_r31 = fn_1_D978(lbl_1_bss_14C[4], 1, fn_1_EEF8);
    Hu3DModelPosSet(temp_r31, 0, 5000, 0);
    Hu3DModelLayerSet(temp_r31, 3);
    Hu3DModelAttrReset(temp_r31, HU3D_ATTR_DISPOFF);
    Hu3DParticleBlendModeSet(temp_r31, 1);
    temp_r29 = ((ParticleData *)Hu3DData[temp_r31].unk_120)->unk_1C;
    temp_r29[1] = 800;
    object->func = fn_1_CD14;
}

void fn_1_D004(omObjData *object);

void fn_1_CD14(omObjData *object)
{
    u16 *temp_r30;
    u32 temp_r29;
    temp_r29 = fn_1_6878();
    temp_r30 = object->data;
    switch (temp_r29) {
        case 1:
            temp_r30[0] = 2;
            temp_r30[1] = 0;
            lbl_1_bss_140 = 1;
            break;

        case 2:
        case 3:
            fn_1_D004(object);
            temp_r30[1]++;
            break;

        case 4:
            Hu3DModelScaleSet(object->model[2], 0.16000001f, 0.16000001f, 0.16000001f);
            Hu3DModelShadowMapSet(object->model[0]);
            Hu3DModelShadowSet(object->model[4]);
            break;

        default:
            break;
    }
    if (temp_r29 > 3) {
        if (lbl_1_bss_134 >= 0) {
            HuAudFXStop(lbl_1_bss_134);
            lbl_1_bss_134 = -1;
        }
        if (lbl_1_bss_130 >= 0) {
            HuAudFXStop(lbl_1_bss_130);
            lbl_1_bss_130 = -1;
        }
    }
}

s32 fn_1_CE68(void)
{
    switch (lbl_1_bss_140) {
        case 0:
            return 0;

        case 1:
            if (lbl_1_bss_144) {
                return 2;
            }
            else {
                return 1;
            }
            break;

        case 2:
            if (lbl_1_bss_144) {
                return 3;
            }
            else {
                return 4;
            }
            break;
    }
}

void fn_1_CEEC(void)
{
    omObjData *temp_r31;
    s32 temp_r30;
    temp_r31 = lbl_1_bss_13C;
    if (lbl_1_bss_140 >= 2) {
        return;
    }
    lbl_1_bss_140 = 2;
    Hu3DModelAttrSet(temp_r31->model[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r31->model[9], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r31->model[11], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r31->model[12], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r31->model[19], HU3D_ATTR_DISPOFF);
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        Hu3DModelAttrSet(temp_r31->model[temp_r30 + 14], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrReset(temp_r31->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(temp_r31->model[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(temp_r31->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(temp_r31->model[3], HU3D_ATTR_DISPOFF);
}

void fn_1_D6F0(omObjData *object);

void fn_1_D004(omObjData *object)
{
    float temp_f31;
    float temp_f29;
    float *temp_r28;
    s32 temp_r27;
    s32 temp_r26;
    u16 *temp_r30 = object->data;
    CameraData *sp8 = &Hu3DCamera[0];
    float temp_f30 = fn_1_6888();
    float temp_f28 = 7000;
    switch (temp_r30[0]) {
        case 2:
            Hu3DModelAttrReset(object->model[9], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(object->model[11], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(object->model[12], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(object->model[19], HU3D_ATTR_DISPOFF);
            for (temp_r26 = 0; temp_r26 < 4; temp_r26++) {
                Hu3DModelAttrReset(object->model[temp_r26 + 14], HU3D_ATTR_DISPOFF);
            }
            Hu3DModelAttrReset(object->model[6], HU3D_ATTR_DISPOFF);
            if (lbl_1_bss_134 < 0) {
                lbl_1_bss_134 = HuAudFXPlay(1363);
            }
            temp_r30[2] = 0;
            temp_r30[0]++;

        case 3:
            temp_f31 = temp_r30[1] * 0.25f;
            Hu3DModelRotSet(object->model[9], 0, 0.7f * -temp_f31, 0);
            Hu3DModelRotSet(object->model[11], 0, 1.3f * temp_f31, 0);
            Hu3DModelRotSet(object->model[12], 0, 3.7f * temp_f31, 0);
            temp_f29 = 1.0f - ((temp_f30 - 5000) / 15000);
            Hu3DMotionTimeSet(object->model[12], 95.0f * temp_f29);
            temp_r27 = object->model[6];
            temp_r28 = ((ParticleData *)Hu3DData[temp_r27].unk_120)->unk_1C;
            temp_r28[2] = 1.0f - ((temp_f30 - 5000) / (temp_f28 - 5000));
            if (temp_f30 <= 5400 && temp_r30[2] == 0) {
                temp_r30[2] = 30;
                if (!lbl_1_bss_40) {
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, temp_r30[2]);
                    lbl_1_bss_44 = 1;
                }
                lbl_1_bss_144 = 1;
                temp_r30[0]++;
            }
            if (temp_f30 <= 4800) {
                temp_r28[1] = 1200;
                temp_r30[0]++;
            }
            fn_1_D6F0(object);
            break;

        case 4:
            if (temp_r30[2]-- == 0) {
                if (!lbl_1_bss_40) {
                    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
                    lbl_1_bss_44 = 0;
                }
                if (lbl_1_bss_138 < 0) {
                    lbl_1_bss_138 = HuAudFXPlay(1357);
                }
                fn_1_CEEC();
                if (lbl_1_bss_134 >= 0) {
                    HuAudFXStop(lbl_1_bss_134);
                    lbl_1_bss_134 = -1;
                }
                if (lbl_1_bss_130 < 0) {
                    lbl_1_bss_130 = HuAudFXPlay(1361);
                }
                temp_r30[0]++;
            }

            break;

        case 5:
            if (!WipeStatGet()) {
                lbl_1_bss_144 = 0;
            }
            temp_r27 = object->model[6];
            if (temp_r27 != 0) {
                Hu3DModelPosSet(temp_r27, 0, 200 + temp_f30, 0);
                temp_r28 = ((ParticleData *)Hu3DData[temp_r27].unk_120)->unk_1C;
                temp_r28[2] -= 0.025f;
                if (temp_r28[2] <= 0) {
                    Hu3DModelAttrReset(temp_r27, HU3D_ATTR_PARTICLE_KILL);
                    Hu3DModelKill(temp_r27);
                    object->model[6] = 0;
                }
            }
            temp_f31 = temp_r30[1] % 360;
            temp_f31 = 0.1f * (1.4f + ((0.2f * temp_f30) / 5000));
            Hu3DModelScaleSet(object->model[2], temp_f31, temp_f31, temp_f31);
            break;
    }
}

void fn_1_D6F0(omObjData *object)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    temp_f28 = fn_1_6888() - 1500;
    temp_f29 = 500.0f * (int)(temp_f28 / 500.0f);
    temp_r30 = (int)(temp_f28 / 500.0f) % 4;
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r29 = object->model[temp_r30 + 14];
        Hu3DModelPosSet(temp_r29, 0, temp_f29, 0);
        temp_f31 = temp_f29 - temp_f28;
        temp_f30 = 0;
        if (temp_f31 > -250.0f && temp_f31 < 1525.0f) {
            temp_f30 = 45;
            if (temp_f31 < 0.0f) {
                temp_f31 -= -250.0f;
                temp_f30 *= fabs(temp_f31 / 250.0f);
            }
            else {
                if (temp_f31 > 1425) {
                    temp_f31 -= 1425;
                    temp_f30 *= 1.0 - fabs(temp_f31 / 100.0f);
                }
            }
        }
        Hu3DMotionTimeSet(temp_r29, temp_f30);
        temp_f29 += 500.0f;
        temp_r30 = (temp_r30 + 1) % 4;
    }
}

s16 fn_1_D978(AnimData *arg0, s16 arg1, ParticleHook arg2)
{
    s32 temp_r31;
    HsfanimStruct01 *temp_r30;
    ParticleData *temp_r29;
    s32 temp_r28;
    HsfanimStruct01 *temp_r27;
    temp_r28 = Hu3DParticleCreate(arg0, arg1);
    Hu3DParticleHookSet(temp_r28, arg2);
    Hu3DModelAttrSet(temp_r28, HU3D_ATTR_DISPOFF);
    temp_r29 = Hu3DData[temp_r28].unk_120;
    temp_r27 = temp_r29->unk_48;
    for (temp_r31 = 0; temp_r31 < temp_r29->unk_30; temp_r31++, temp_r27++) {
        temp_r27->unk2C = 0;
    }
    temp_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(HsfanimStruct01), MEMORY_DEFAULT_NUM);
    temp_r29->unk_1C = temp_r30;
    temp_r30->unk00 = temp_r28;
    temp_r30->unk02 = 0;
    for (temp_r31 = 0; temp_r31 < 32; temp_r31++) {
        // Ugly expression to match store without new type
        *((s16 *)(((u8 *)temp_r30) + (temp_r31 * 2) + 4)) = 0;
    }
    return temp_r28;
}

void fn_1_DA6C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;

    HsfanimStruct01 *temp_r31;
    ParticleData *temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    s16 temp_r26;
    temp_r29 = particle->unk_1C;
    switch (temp_r29->unk_02) {
        case 0:
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                temp_r31->unk00 = 0;
            }
            particle->unk_00 = 0;
            temp_r29->unk_02++;
            temp_r29->unk_04.y = 3;
            temp_r29->unk_04.z = 25;
            break;

        case 1:
            for (temp_r28 = 0; temp_r28 < 100; temp_r28++) {
                temp_r31 = particle->unk_48;
                for (temp_r27 = 0; temp_r27 < particle->unk_30; temp_r27++, temp_r31++) {
                    if (!temp_r31->unk00) {
                        break;
                    }
                }
                if (temp_r27 == particle->unk_30) {
                    temp_r29->unk_02++;
                    break;
                }
                temp_r31->unk34.x = temp_r31->unk34.y = temp_r31->unk34.z = 0;
                temp_r26 = fn_1_11670() % 360;
                temp_r31->unk08.x = sind(temp_r26);
                temp_r31->unk08.y = -6.0 + (2.0 * temp_r29->unk_10.x);
                temp_r31->unk08.z = cosd(temp_r26);
                temp_r31->unk14.x = ((fn_1_11670() & 0x7) + temp_r29->unk_04.z) - 4.0f;
                temp_r31->unk14.x *= 0.1f;
                temp_f31 = temp_r29->unk_04.y + (0.01 * (float)(fn_1_11670() % 400));
                temp_f31 *= 0.1f;
                temp_r31->unk34.x = temp_f31 * temp_r31->unk08.x;
                temp_r31->unk34.y = 0;
                temp_r31->unk34.z = temp_f31 * temp_r31->unk08.z;
                temp_r31->unk2C = (0.01 * (frand() % 2000)) + 30.0;
                temp_r31->unk2C *= 0.1f;
                temp_r31->unk40.a = 255;
                temp_r31->unk00 = 30;
            }
            break;
    }
    temp_r31 = particle->unk_48;
    for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
        if (temp_r31->unk00 == 0) {
            continue;
        }
        temp_f30 = temp_r31->unk14.x;
        temp_r31->unk34.x += temp_r31->unk08.x * temp_f30;
        temp_r31->unk34.y += temp_r31->unk08.y;
        temp_r31->unk34.z += temp_r31->unk08.z * temp_f30;
        temp_r31->unk2C *= 1.025f;
        temp_r31->unk40.a *= 0.95f;
        temp_r31->unk40.a--;
        temp_r31->unk14.x *= 0.8f;
        temp_r31->unk08.y *= 0.85f;
        temp_r31->unk08.y += 0.1f;
        if (temp_r31->unk40.a < 2) {
            temp_r31->unk40.a = 0;
            temp_r31->unk00 = 0;
            particle->unk_00++;
        }
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
    if (particle->unk_00 >= particle->unk_30 && temp_r29->unk_02 == 2) {
        temp_r29->unk_02 = 0;
        Hu3DModelAttrReset(temp_r29->unk_00, HU3D_ATTR_PARTICLE_KILL);
        Hu3DModelKill(temp_r29->unk_00);
    }
}

void fn_1_DFD0(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    HsfanimStruct01 *temp_r31;
    ParticleData *temp_r30;
    s32 temp_r28;
    s16 temp_r27;
    s32 temp_r26;
    temp_r30 = particle->unk_1C;
    switch (temp_r30->unk_02) {
        case 0:
            temp_r31 = particle->unk_48;
            temp_r30->unk_04.x = 10;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                temp_r31->unk34.x = temp_r31->unk34.y = temp_r31->unk34.z = 0;
                temp_r27 = fn_1_11670() % 360;
                temp_r31->unk08.x = sind(temp_r27);
                temp_r31->unk08.y = 0;
                temp_r31->unk08.z = cosd(temp_r27);
                temp_f31 = temp_r30->unk_04.x + (temp_r30->unk_04.x * ((1.0 / 65536.0) * (float)fn_1_11670()));
                temp_r31->unk34.x = temp_f31 * temp_r31->unk08.x;
                temp_r31->unk34.y = -(100.0 * ((1.0 / 65536.0) * (float)fn_1_11670()));
                temp_r31->unk34.z = temp_f31 * temp_r31->unk08.z;
                temp_r31->unk2C = (0.01 * (frand() % 2000)) + 40.0;
                temp_r26 = frand() & 0x2F;
                temp_r31->unk40.r = temp_r26 + 208;
                temp_r31->unk40.g = temp_r26 + 208;
                temp_r31->unk40.a = (frand() & 0x5F) + 32;
            }
            temp_r30->unk_02++;
            particle->unk_00 = 60;
            break;

        case 1:
            if (--particle->unk_00 == 0) {
                Hu3DModelAttrReset(temp_r30->unk_00, HU3D_ATTR_PARTICLE_KILL);
                Hu3DModelKill(temp_r30->unk_00);
                return;
            }
            break;
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_E310(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;

    HsfanimStruct01 *temp_r31;
    ParticleData *temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    s16 temp_r26;
    temp_r29 = particle->unk_1C;
    switch (temp_r29->unk_02) {
        case 0:
            temp_r31 = particle->unk_48;
            temp_f30 = 360.0f / particle->unk_30;

            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                temp_r31->unk00 = (s32)(360.0 * ((1.0 / 65536.0) * (float)fn_1_11670()));
                temp_r31->unk34.x = temp_r31->unk34.y = temp_r31->unk34.z = 0;
                temp_r26 = (temp_f30 * temp_r28) + (int)((temp_f30 * 0.5f) * ((1.0 / 32768.0) * (float)(fn_1_11670() - 32768)));
                temp_r31->unk20 = temp_r26;
                temp_r31->unk30 = (M_PI * (temp_r26 + 90.0f)) / 180.0;
                temp_r31->unk08.x = sind(temp_r26);
                temp_r31->unk08.y = 0;
                temp_r31->unk08.z = cosd(temp_r26);
                temp_f31 = temp_r29->unk_04.y + ((0.25f * temp_r29->unk_04.y) * ((1.0 / 65536.0) * (float)fn_1_11670()));
                temp_r31->unk14.x = temp_f31 * temp_r31->unk08.x;
                temp_r31->unk14.y = 120.0 * ((1.0 / 32768.0) * (float)(fn_1_11670() - 32768));
                temp_r31->unk14.z = temp_f31 * temp_r31->unk08.z;
                temp_r31->unk24 = temp_r31->unk2C = (0.01 * (frand() % 2000)) + 160;
                if (particle->unk_2C == 1) {
                    temp_r27 = frand() & 0x2F;
                    temp_r31->unk40.r = temp_r27 + 32;
                    temp_r31->unk40.g = temp_r27 + 32;
                    temp_r31->unk40.b = 64 + temp_r27 + ((int)(((46 - temp_r27) * ((1.0 / 65536.0) * (float)fn_1_11670()))));
                    temp_r31->unk40.a = (frand() & 0x2F) + 32;
                }
                else {
                    temp_r27 = frand() & 0x2F;
                    temp_r31->unk40.r = temp_r27 + 208;
                    temp_r31->unk40.g = temp_r27 + 208;
                    temp_r31->unk40.a = (frand() & 0x4F) + 176;
                }
            }
            temp_r29->unk_02++;

        case 1:
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                temp_r31->unk00 += 4;
                if (temp_r31->unk00 >= 360) {
                    temp_r31->unk00 -= 360;
                }
                temp_r31->unk34.x = temp_r31->unk14.x;
                temp_r31->unk34.y = temp_r31->unk14.y;
                temp_r31->unk34.z = temp_r31->unk14.z;
                temp_r31->unk30 = M_PI * (90 + (temp_r31->unk20 + temp_r29->unk_04.z)) / 180;
                temp_r31->unk2C = temp_r31->unk24 * ((0.1f * sind(temp_r31->unk00)) + 1.0);
            }
            break;
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_E9B4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f30;
    float temp_f31;
    HsfanimStruct01 *temp_r31;
    ParticleData *temp_r30;
    s32 temp_r28;
    s16 temp_r27;
    s32 temp_r26;
    temp_r30 = particle->unk_1C;
    switch (temp_r30->unk_02) {
        case 0:
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                temp_r31->unk00 = fn_1_11670() % 360;
                temp_r31->unk34.x = temp_r31->unk34.y = temp_r31->unk34.z = 0;
                temp_r27 = fn_1_11670() % 360;
                temp_r31->unk20 = temp_r27;
                temp_r31->unk08.x = sind(temp_r27);
                temp_r31->unk08.y = 0;
                temp_r31->unk08.z = cosd(temp_r27);
                temp_f31 = temp_r30->unk_04.x + (0.01 * ((30.0f * temp_r30->unk_04.x) * ((1.0 / 65536.0) * (float)fn_1_11670())));
                temp_f30 = (0.15f + (0.3f * ((1.0 / 65536.0) * (float)fn_1_11670())));
                temp_r31->unk14.x = temp_f31 * temp_r31->unk08.x;
                temp_r31->unk14.y = 50 * ((1.0 / 32768.0) * (float)(fn_1_11670() - 32768));
                temp_r31->unk14.z = temp_f31 * temp_r31->unk08.z * temp_f30;
                temp_r31->unk24 = temp_r31->unk2C
                    = temp_r30->unk_04.x + (0.01 * ((50.0f * temp_r30->unk_04.x) * ((1.0 / 65536.0) * (float)fn_1_11670())));
                temp_r26 = frand() & 0x7F;
                temp_r31->unk40.r = temp_r26 + 64;
                temp_r31->unk40.g = temp_r26 + 64;
                temp_f31 -= temp_r30->unk_04.x;
                temp_r31->unk40.a
                    = 32 + (int)((48.0f * temp_f31) / (0.2f * temp_r30->unk_04.x)) + (int)(32 * ((1.0 / 65536.0) * (float)fn_1_11670()));
            }
            temp_r30->unk_02++;

        case 1:
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                temp_r31->unk00 += 2;
                if (temp_r31->unk00 >= 360) {
                    temp_r31->unk00 -= 360;
                }
                temp_r31->unk34.x = temp_r31->unk14.x;
                temp_r31->unk34.y = temp_r31->unk14.y;
                temp_r31->unk34.z = temp_r31->unk14.z;
                temp_r31->unk2C = temp_r31->unk24 * ((0.1f * sind(temp_r31->unk00)) + 1.0);
            }
            break;
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_EEF8(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    HsfanimStruct01 *temp_r31;
    ParticleData *temp_r29;
    s32 temp_r28;
    u8 temp_r27;
    temp_r29 = particle->unk_1C;
    switch (temp_r29->unk_02) {
        case 0:
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                temp_r31->unk34.x = temp_r31->unk34.y = temp_r31->unk34.z = 0;
                temp_r31->unk40.r = temp_r31->unk40.g = temp_r31->unk40.b = temp_r31->unk40.a = 255;
                temp_r31->unk2C = temp_r29->unk_04.x;
            }
            temp_r29->unk_02++;
            break;

        case 1:
            if (temp_r29->unk_04.y < 0.0f) {
                break;
            }
            temp_f31 = 0.1f + temp_r29->unk_04.y;
            temp_f31 = 1.2f * (temp_f31 * temp_f31);
            if (temp_f31 > 1.0f) {
                temp_f31 = 1.0f;
            }
            temp_r27 = 255 * temp_f31;
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                temp_r31->unk40.a = temp_r27;
            }
            break;
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_F06C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    HsfanimStruct01 *temp_r31;
    ParticleData *temp_r29;
    s32 temp_r28;
    s16 temp_r27;
    temp_r27 = 0;
    temp_r29 = particle->unk_1C;
    switch (temp_r29->unk_02) {
        case 0:
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                temp_r31->unk00 = temp_r31->unk02 = 0;
            }
            temp_r29->unk_02++;
            break;

        case 1:
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                if (temp_r31->unk00) {
                    temp_r31->unk00--;
                    continue;
                }
                if (temp_r31->unk02 == 0) {
                    temp_f31 = 360.0f * ((1.0 / 65536.0) * (float)fn_1_11670());
                    temp_r31->unk34.x = 10.0 * (50.0 + (250.0 * ((1.0 / 65536.0) * (float)fn_1_11670()))) * sind(temp_f31);
                    temp_r31->unk34.y = 0;
                    temp_r31->unk34.z = 10.0 * (50.0 + (250.0 * ((1.0 / 65536.0) * (float)fn_1_11670()))) * cosd(temp_f31);
                    temp_r31->unk30 = (M_PI * (temp_f31 - 90.0f)) / 180;
                    temp_r31->unk40.r = temp_r31->unk40.g = temp_r31->unk40.b = temp_r31->unk40.a = 192;
                    temp_r31->unk40.b = 160;
                    temp_r31->unk2C = 0;
                    temp_r31->unk00 = (s32)(90.0 * ((1.0 / 65536.0) * (float)fn_1_11670()));
                    temp_r31->unk02 = 60;
                }
                temp_r31->unk40.a = 248 * sind(temp_r31->unk02 * 3);
                temp_r31->unk2C = temp_r29->unk_04.x * (60 - temp_r31->unk02);
                temp_r31->unk02--;
            }
            if (particle->unk_30 == temp_r27) {
                Hu3DModelAttrReset(temp_r29->unk_00, HU3D_ATTR_PARTICLE_KILL);
                Hu3DModelKill(temp_r29->unk_00);
                return;
            }
            break;
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

WorkF4B0 *fn_1_F4B0(s16 arg0, s16 arg1)
{
    WorkF4B0 *temp_r31;
    s32 temp_r30;
    ModelData *temp_r29;
    temp_r29 = &Hu3DData[arg0];
    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkF4B0), MEMORY_DEFAULT_NUM);
    temp_r29->unk_120 = temp_r31;
    temp_r31->unk0 = arg0;
    temp_r31->unk2 = arg1;
    temp_r31->unk4 = NULL;
    temp_r31->unk8 = NULL;
    for (temp_r30 = 0; temp_r30 < 32; temp_r30++) {
        temp_r31->unk10[temp_r30] = 0;
    }
    return temp_r31;
}

void fn_1_F564(s16 arg0)
{
    float temp_f31;
    WorkF4B0 *temp_r31;
    s32 temp_r30;
    HsfObject *temp_r29;
    s32 temp_r28;
    ModelData *temp_r27;
    temp_r27 = &Hu3DData[arg0];
    temp_r29 = temp_r27->hsfData->root;
    temp_r31 = temp_r27->unk_120;
    if (temp_r31->unk8 == NULL) {
        temp_r31->unk8 = HuMemDirectMallocNum(HEAP_SYSTEM, temp_r29->data.st->count * sizeof(HsfVector2f), MEMORY_DEFAULT_NUM);
        temp_r31->unkC = HuMemDirectMallocNum(HEAP_SYSTEM, temp_r29->data.st->count, MEMORY_DEFAULT_NUM);
        for (temp_r30 = 0; temp_r30 < temp_r29->data.st->count; temp_r30++) {
            temp_r31->unk8[temp_r30].x = ((HsfVector2f *)(temp_r29->data.st->data))[temp_r30].x;
            temp_r31->unk8[temp_r30].y = ((HsfVector2f *)(temp_r29->data.st->data))[temp_r30].y;
        }
    }
    temp_r31->unk10_f[0] += 2.0f;
    for (temp_r30 = 0; temp_r30 < temp_r29->data.st->count; temp_r30++) {
        temp_r31->unkC[temp_r30] = 0;
    }
    for (temp_r30 = 0; temp_r30 < temp_r29->data.st->count; temp_r30++) {
        if (temp_r31->unkC[temp_r30]) {
            continue;
        }
        temp_r31->unkC[temp_r30]++;
        temp_f31 = temp_r31->unk10_f[0] + (60.0f * temp_r30);
        ((HsfVector2f *)(temp_r29->data.st->data))[temp_r30].x = temp_r31->unk8[temp_r30].x + (0.005f * sind(temp_f31));
        ((HsfVector2f *)(temp_r29->data.st->data))[temp_r30].y = temp_r31->unk8[temp_r30].y + (0.005f * cosd(temp_f31));
        for (temp_r28 = temp_r30; temp_r28 < temp_r29->data.st->count; temp_r28++) {
            if (temp_r31->unkC[temp_r28]) {
                continue;
            }
            if (temp_r31->unk8[temp_r30].x != temp_r31->unk8[temp_r28].x || temp_r31->unk8[temp_r30].y != temp_r31->unk8[temp_r28].y) {
                continue;
            }
            temp_r31->unkC[temp_r28]++;
            ((HsfVector2f *)(temp_r29->data.st->data))[temp_r28].x = ((HsfVector2f *)(temp_r29->data.st->data))[temp_r30].x;
            ((HsfVector2f *)(temp_r29->data.st->data))[temp_r28].y = ((HsfVector2f *)(temp_r29->data.st->data))[temp_r30].y;
        }
    }
}

typedef struct unk_fn_10484 {
    ModelData *unk0;
    HsfObject *unk4;
    s32 unk8;
    Mtx unkC;
    float unk3C[2];

} UnkFn10484;

void fn_1_10484(UnkFn10484 *arg0, HsfFace *arg1, HsfDrawData *arg2, GXColor *arg3);

void fn_1_F8A0(ModelData *arg0, Mtx arg1)
{
    WorkF4B0 *temp_r31;
    GXColor *temp_r30;
    s16 temp_r29;
    s32 temp_r28;
    HsfBuffer *temp_r27;
    HsfFace *temp_r26;

    UnkFn10484 spA0;
    Mtx sp70;
    Mtx sp40;
    Mtx sp10;
    s16 spC = 0;
    temp_r31 = arg0->unk_120;
    spA0.unk0 = &Hu3DData[temp_r31->unk2];
    spA0.unk4 = spA0.unk0->hsfData->root;
    MTXCopy(arg1, spA0.unkC);
    lbl_1_bss_128[0] = spA0.unk4->constData;
    lbl_1_bss_120[0] = lbl_1_bss_128[0]->dlBuf;
    lbl_1_bss_11C = lbl_1_bss_128[0]->drawData;
    GXLoadPosMtxImm(spA0.unkC, GX_PNMTX0);
    MTXInverse(spA0.unkC, sp70);
    MTXTranspose(sp70, sp40);
    GXLoadNrmMtxImm(sp40, GX_PNMTX0);
    if (Hu3DShadowF && (lbl_1_bss_128[0]->flags & 0x8)) {
        MTXConcat(sp10, spA0.unkC, sp40);
        MTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, sp70);
        MTXConcat(sp70, sp40, sp40);
        GXLoadTexMtxImm(sp40, GX_TEXMTX9, GX_MTX3x4);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    if (temp_r31->unk4 == NULL) {
        temp_r31->unk4 = HuMemDirectMallocNum(HEAP_SYSTEM, spA0.unk4->data.color->count * sizeof(GXColor), MEMORY_DEFAULT_NUM);
        for (temp_r29 = 0; temp_r29 < spA0.unk4->data.color->count; temp_r29++) {
            temp_r30 = &temp_r31->unk4[temp_r29];
            temp_r30->r = temp_r31->unk10[0];
            temp_r30->g = temp_r31->unk10[1];
            temp_r30->b = temp_r31->unk10[2];
            if (((GXColor *)(spA0.unk4->data.color->data))[temp_r29].a == 255) {
                temp_r30->a = temp_r31->unk10[3];
            }
            else {
                temp_r30->a = ((GXColor *)(spA0.unk4->data.color->data))[temp_r29].a;
            }
        }
    }
    temp_r27 = spA0.unk4->data.face;
    temp_r26 = temp_r27->data;
    temp_r28 = 0;
    for (temp_r29 = 0; temp_r29 < temp_r27->count;) {
        fn_1_10484(&spA0, temp_r26, &lbl_1_bss_11C[temp_r28], temp_r31->unk4);
        temp_r28++;
        temp_r29 += lbl_1_bss_11C[temp_r28 - 1].polyCnt;
        temp_r26 += lbl_1_bss_11C[temp_r28 - 1].polyCnt;
    }
}

void fn_1_FB98(ModelData *arg0, Mtx arg1)
{
    WorkF4B0 *temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    GXColor *temp_r27;
    s32 temp_r26;
    HsfBuffer *temp_r25;
    HsfFace *temp_r24;
    s32 temp_r23;
    void *temp_r22;

    UnkFn10484 sp120;
    Mtx spF0;
    Mtx spC0;
    Mtx sp90;
    float sp50[2][8];
    float sp10[2][8];
    s16 spC = 0;
    temp_r31 = arg0->unk_120;
    sp120.unk0 = &Hu3DData[temp_r31->unk2];
    sp120.unk4 = sp120.unk0->hsfData->root;
    MTXCopy(arg1, sp120.unkC);
    lbl_1_bss_128[0] = sp120.unk4->constData;
    lbl_1_bss_120[0] = lbl_1_bss_128[0]->dlBuf;
    lbl_1_bss_11C = lbl_1_bss_128[0]->drawData;
    GXLoadPosMtxImm(sp120.unkC, GX_PNMTX0);
    MTXInverse(sp120.unkC, spF0);
    MTXTranspose(spF0, spC0);
    GXLoadNrmMtxImm(spC0, GX_PNMTX0);
    if (Hu3DShadowF && (lbl_1_bss_128[0]->flags & 0x8)) {
        MTXConcat(sp90, sp120.unkC, spC0);
        MTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, spF0);
        MTXConcat(spF0, spC0, spC0);
        GXLoadTexMtxImm(spC0, GX_TEXMTX9, GX_MTX3x4);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    if (temp_r31->unk4 == NULL) {
        temp_r31->unk4 = HuMemDirectMallocNum(HEAP_SYSTEM, sp120.unk4->data.color->count * sizeof(GXColor), MEMORY_DEFAULT_NUM);
        for (temp_r30 = 0; temp_r30 < sp120.unk4->data.color->count; temp_r30++) {
            temp_r27 = &temp_r31->unk4[temp_r30];
            temp_r27->r = temp_r31->unk10[0];
            temp_r27->g = temp_r31->unk10[1];
            temp_r27->b = temp_r31->unk10[2];
            temp_r27->a = temp_r31->unk10[3];
        }
    }
    if (temp_r31->unk8 == NULL) {
        temp_r31->unk8 = HuMemDirectMallocNum(HEAP_SYSTEM, sp120.unk4->data.st->count * sizeof(HsfVector2f), MEMORY_DEFAULT_NUM);
        temp_r31->unkC = HuMemDirectMallocNum(HEAP_SYSTEM, sp120.unk4->data.st->count, MEMORY_DEFAULT_NUM);
        for (temp_r30 = 0; temp_r30 < sp120.unk4->data.st->count; temp_r30++) {
            temp_r31->unk8[temp_r30].x = ((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r30].x;
            temp_r31->unk8[temp_r30].y = ((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r30].y;
        }
    }
    temp_r31->unk10_f[15] += 0.5f;
    for (temp_r30 = 0; temp_r30 < 8; temp_r30++) {
        float temp_f31 = temp_r31->unk10_f[15] + (40.0f * temp_r30);
        sp50[0][temp_r30] = sind(temp_f31);
        sp10[0][temp_r30] = cosd(temp_f31);
    }
    for (temp_r30 = 0; temp_r30 < sp120.unk4->data.st->count; temp_r30++) {
        temp_r31->unkC[temp_r30] = 0;
    }
    for (temp_r30 = 0, temp_r29 = 0; temp_r30 < sp120.unk4->data.st->count; temp_r30++, temp_r29++) {
        if (temp_r31->unkC[temp_r30]) {
            continue;
        }
        temp_r31->unkC[temp_r30]++;
        if (temp_r31->unk10[4]) {
            temp_r31->unk8[temp_r30].x = (1.5f * ((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r30].x) + (0.04f * sp50[0][temp_r29 & 0x7]);
            temp_r31->unk8[temp_r30].y = (2.0f * ((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r30].y) + (0.04f * sp10[0][temp_r29 & 0x7]);
        }
        else {
            temp_r31->unk8[temp_r30].x = (1.25f * ((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r30].x) + (0.04f * sp50[0][temp_r29 & 0x7]);
            temp_r31->unk8[temp_r30].y = (1.75f * ((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r30].y) + (0.04f * sp10[0][temp_r29 & 0x7]);
        }
        temp_r23 = temp_r31->unk10[3] + ((0.8f * temp_r31->unk10[3]) * sind((3.0f * temp_r31->unk10_f[15]) + (120.0f * temp_r29)));
        temp_r31->unk4[temp_r30].a = temp_r23;
        for (temp_r28 = temp_r30; temp_r28 < sp120.unk4->data.st->count; temp_r28++) {
            temp_r29++;
            if (temp_r31->unkC[temp_r28]) {
                continue;
            }
            if (((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r30].x != ((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r28].x
                || ((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r30].y != ((HsfVector2f *)(sp120.unk4->data.st->data))[temp_r28].y) {
                continue;
            }
            temp_r31->unkC[temp_r28]++;
            temp_r31->unk8[temp_r28].x = temp_r31->unk8[temp_r30].x;
            temp_r31->unk8[temp_r28].y = temp_r31->unk8[temp_r30].y;
            temp_r31->unk4[temp_r28].a = temp_r23;
            temp_r29--;
        }
    }
    temp_r22 = sp120.unk4->data.st->data;
    sp120.unk4->data.st->data = temp_r31->unk8;
    temp_r25 = sp120.unk4->data.face;
    temp_r24 = temp_r25->data;
    temp_r26 = 0;
    for (temp_r30 = 0; temp_r30 < temp_r25->count;) {
        fn_1_10484(&sp120, temp_r24, &lbl_1_bss_11C[temp_r26], temp_r31->unk4);
        temp_r26++;
        temp_r30 += lbl_1_bss_11C[temp_r26 - 1].polyCnt;
        temp_r24 += lbl_1_bss_11C[temp_r26 - 1].polyCnt;
    }
    sp120.unk4->data.st->data = temp_r22;
}

void fn_1_10830(ModelData *arg0, HsfBitmap *arg1, HsfAttribute *arg2, s16 arg3);
void fn_1_10B60(UnkFn10484 *arg0, HsfMaterial *arg1);

void fn_1_10484(UnkFn10484 *arg0, HsfFace *arg1, HsfDrawData *arg2, GXColor *arg3)
{
    HsfMaterial *temp_r31;
    HsfObject *temp_r30;
    HsfAttribute *temp_r29;
    s16 temp_r27;
    s16 temp_r25;
    HsfdrawStruct01 *temp_r24;
    ModelData *temp_r23;
    Hu3DTexAnimDataStruct *temp_r22;
    void *temp_r20;
    GXColor sp14;
    temp_r30 = arg0->unk4;
    temp_r23 = arg0->unk0;
    temp_r31 = &temp_r30->data.material[arg1->mat & 0xFFF];
    sp14.r = temp_r31->litColor[0];
    sp14.g = temp_r31->litColor[1];
    sp14.b = temp_r31->litColor[2];
    sp14.a = 255;
    GXSetChanAmbColor(GX_COLOR0A0, sp14);
    sp14.r = temp_r31->color[0];
    sp14.g = temp_r31->color[1];
    sp14.b = temp_r31->color[2];
    sp14.a = 255;
    GXSetChanMatColor(GX_COLOR0A0, sp14);
    if ((temp_r31->invAlpha != 0 || temp_r31->pass == 1) && !(temp_r23->attr & 0x2)) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    }
    else {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
    if (temp_r31->numAttrs == 0) {
        return;
    }
    temp_r25 = (temp_r30->data.color) ? 5 : 1;
    if (arg2->flags & 0x2) {
        temp_r25 |= 0x2;
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSETARRAY(GX_VA_POS, temp_r30->data.vertex->data, temp_r30->data.vertex->count * sizeof(HsfVector3f), sizeof(HsfVector3f));
    if (temp_r25 & 0x2) {
        GXSetVtxDesc(GX_VA_NBT, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NBT, GX_NRM_NBT, GX_S16, 8);
    }
    else {
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
        GXSETARRAY(GX_VA_NRM, temp_r30->data.normal->data, temp_r30->data.vertex->count * sizeof(HsfVector3f), sizeof(HsfVector3f));
    }
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSETARRAY(GX_VA_TEX0, temp_r30->data.st->data, temp_r30->data.vertex->count * sizeof(HsfVector2f), sizeof(HsfVector2f));
    if (temp_r25 & 0x4) {
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSETARRAY(GX_VA_CLR0, arg3, arg0->unk4->data.color->count * sizeof(GXColor), sizeof(GXColor));
    }
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    for (temp_r27 = 0; temp_r27 < temp_r31->numAttrs; temp_r27++) {
        temp_r29 = &temp_r30->data.attribute[temp_r31->attrs[temp_r27]];
        if (temp_r29->unk04) {
            temp_r24 = temp_r29->unk04;
            temp_r22 = &Hu3DTexAnimData[temp_r24->unk02];
            if ((temp_r24->unk00 & 0x1) && !(temp_r22->unk00 & 0x4)) {
                if (Hu3DAnimSet(arg0->unk0, temp_r29, (s16)temp_r27)) {
                    continue;
                }
            }
        }
        fn_1_10830(arg0->unk0, temp_r29->bitmap, temp_r29, (s16)temp_r27);
    }
    fn_1_10B60(arg0, temp_r31);
    temp_r20 = (void *)(arg2->dlOfs + ((u32)lbl_1_bss_120[0]));
    GXCallDisplayList(temp_r20, arg2->dlSize);
}

void fn_1_10830(ModelData *arg0, HsfBitmap *arg1, HsfAttribute *arg2, s16 arg3)
{
    GXTexObj sp1C;
    GXTlutObj sp10;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    temp_r29 = arg1->sizeX;
    temp_r28 = arg1->sizeY;
    temp_r27 = (arg2->wrap_s == 1) ? 1 : 0;
    temp_r26 = (arg2->wrap_t == 1) ? 1 : 0;
    switch (arg1->dataFmt) {
        case 6:
            GXInitTexObj(&sp1C, arg1->data, temp_r29, temp_r28, GX_TF_RGBA8, temp_r27, temp_r26, GX_FALSE);
            break;

        case 4:
            GXInitTexObj(&sp1C, arg1->data, temp_r29, temp_r28, GX_TF_RGB565, temp_r27, temp_r26, GX_FALSE);
            break;

        case 5:
            GXInitTexObj(&sp1C, arg1->data, temp_r29, temp_r28, GX_TF_RGB5A3, temp_r27, temp_r26, GX_FALSE);
            break;

        case 9:
            if (arg1->pixSize < 8) {
                GXInitTlutObj(&sp10, arg1->palData, GX_TL_RGB565, arg1->palSize);
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, temp_r29, temp_r28, GX_TF_C4, temp_r27, temp_r26, GX_FALSE, arg3);
            }
            else {
                GXInitTlutObj(&sp10, arg1->palData, GX_TL_RGB565, arg1->palSize);
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, temp_r29, temp_r28, GX_TF_C8, temp_r27, temp_r26, GX_FALSE, arg3);
            }
            break;

        case 10:
            if (arg1->pixSize < 8) {
                GXInitTlutObj(&sp10, arg1->palData, GX_TL_RGB5A3, arg1->palSize);
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, temp_r29, temp_r28, GX_TF_C4, temp_r27, temp_r26, GX_FALSE, arg3);
            }
            else {
                GXInitTlutObj(&sp10, arg1->palData, GX_TL_RGB5A3, arg1->palSize);
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, temp_r29, temp_r28, GX_TF_C8, temp_r27, temp_r26, GX_FALSE, arg3);
            }
            break;
    }
    if (arg0->attr & 0x40) {
        GXInitTexObjLOD(&sp1C, GX_NEAR, GX_NEAR, 0, 0, 0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    else {
        GXInitTexObjLOD(&sp1C, GX_LINEAR, GX_LINEAR, 0, 0, 0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    GXLoadTexObj(&sp1C, arg3);
#ifdef TARGET_PC
    GXDestroyTexObj(&sp1C);
    GXDestroyTlutObj(&sp10);
#endif
}

#define SET_TEVCOLOR_ALPHA(reg, color_var, value)                                                                                                    \
    {                                                                                                                                                \
        color_var.a = (value);                                                                                                                       \
        GXSetTevColor(reg, color_var);                                                                                                               \
    }

SHARED_SYM extern u32 texMtxTbl[];

void fn_1_10B60(UnkFn10484 *arg0, HsfMaterial *arg1)
{
    GXColor sp28;
    GXColor sp24;
    GXColor sp20;
    u16 temp_r31;
    HsfAttribute *temp_r29;
    u16 temp_r28;
    HsfObject *temp_r27;
    HsfdrawStruct01 *temp_r26;
    u16 temp_r25;
    u16 temp_r24;
    s32 temp_r23;
    s32 temp_r22;
    u16 temp_r20;
    temp_r27 = arg0->unk4;
    if (arg1->vtxMode == 2 || arg1->vtxMode == 3) {
        temp_r24 = 1;
    }
    else {
        temp_r24 = 0;
        if (arg1->vtxMode == 0 && !temp_r27->data.color) {
            temp_r23 = 0;
        }
        else {
            temp_r23 = 1;
        }
    }

    if (arg1->numAttrs == 1) {
        temp_r28 = temp_r31 = 1;
        temp_r29 = &temp_r27->data.attribute[arg1->attrs[0]];
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        if (temp_r29->unk04) {
            temp_r26 = temp_r29->unk04;
            if (temp_r26->unk00 & 0x2) {
                GXLoadTexMtxImm(Hu3DTexScrData[temp_r26->unk04].unk3C, GX_TEXMTX0, GX_MTX2x4);
                GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0);
            }
        }
        if (temp_r29->unk8[2] == 0) {
            GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
            GXSetTevOrder(temp_r31, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevColorIn(temp_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
            GXSetTevColorOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            GXSetTevAlphaOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            temp_r31++;
        }
        else {
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
        SET_TEVCOLOR_ALPHA(GX_TEVREG0, sp28, 255 * (1.0f - arg1->invAlpha));
        if (temp_r24) {
            GXSetTevOrder(temp_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR1A1);
            GXSetTevColorIn(temp_r31, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            temp_r31++;
        }
        else if (0.0f != arg1->invAlpha) {
            GXSetTevOrder(temp_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorIn(temp_r31, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
            GXSetTevAlphaOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            temp_r31++;
        }
        GXSetNumTexGens(temp_r28);
        GXSetNumTevStages(temp_r31);
    }
    else {
        temp_r22 = 0;
        temp_r28 = 1;
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        for (temp_r25 = temp_r31 = 0; temp_r25 < arg1->numAttrs; temp_r31++, temp_r25++) {
            temp_r29 = &temp_r27->data.attribute[arg1->attrs[temp_r25]];
            if (0.0f != temp_r29->unk14) {
                GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_BUMP0, GX_TG_TEXCOORD0, GX_IDENTITY);
                SET_TEVCOLOR_ALPHA(GX_TEVREG1, sp24, 10 * temp_r29->unk14);
                GXSetTevOrder(temp_r31, GX_TEXCOORD0, temp_r25, GX_COLOR0A0);
                GXSetTevColorIn(temp_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_RASC);
                GXSetTevColorOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                temp_r31++;
                GXSetTevOrder(temp_r31, GX_TEXCOORD1, temp_r25, GX_COLOR0A0);
                GXSetTevColorIn(temp_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_CPREV);
                GXSetTevColorOp(temp_r31, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                temp_r28++;
                temp_r22 = 1;
            }
            else {
                if (temp_r29->unk04) {
                    temp_r26 = temp_r29->unk04;
                    if (temp_r26->unk00 & 0x2) {
                        GXLoadTexMtxImm(Hu3DTexScrData[temp_r26->unk04].unk3C, texMtxTbl[temp_r28], GX_MTX2x4);
                        GXSetTexCoordGen(temp_r28, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[temp_r28]);
                        temp_r20 = (u16)temp_r28;
                        temp_r28++;
                    }
                }
                else {
                    temp_r20 = 0;
                }
                GXSetTevOrder(temp_r31, temp_r20, temp_r25, GX_COLOR0A0);
                if (temp_r25 == 0) {
                    GXSetTevColorIn(temp_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                    GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                }
                else if (temp_r22 != 0) {
                    GXSetTevColorIn(temp_r31, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
                    GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                    temp_r22 = 0;
                }
                else if (temp_r29->unk8[2] == 0) {
                    GXSetTevColorIn(temp_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
                    GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                }
                else {
                    SET_TEVCOLOR_ALPHA(GX_TEVREG2, sp20, 255 * temp_r29->unk0C);
                    GXSetTevColorIn(temp_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A2, GX_CC_ZERO);
                    GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                }
                GXSetTevColorOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }
        }
        SET_TEVCOLOR_ALPHA(GX_TEVREG0, sp28, 255 * (1.0f - arg1->invAlpha));
        if (temp_r24) {
            GXSetTevOrder(temp_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR1A1);
            GXSetTevColorIn(temp_r31, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            temp_r31++;
        }
        else {
            GXSetTevOrder(temp_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorIn(temp_r31, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(temp_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(temp_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            temp_r31++;
        }
        GXSetNumTexGens(temp_r28);
        GXSetNumTevStages(temp_r31);
    }
    lbl_1_bss_118 = Hu3DLightSet(arg0->unk0, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, (temp_r24) ? arg1->hilite_scale : 0);
    if (temp_r24) {
        GXSetNumChans(2);
        if (temp_r27->data.color) {
            GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lbl_1_bss_118, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR1A1, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lbl_1_bss_118, GX_DF_NONE, GX_AF_SPEC);
        }
        else {
            GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, lbl_1_bss_118, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR1A1, GX_TRUE, GX_SRC_REG, GX_SRC_REG, lbl_1_bss_118, GX_DF_NONE, GX_AF_SPEC);
        }
    }
    else {
        GXSetNumChans(1);
        if (temp_r27->data.color) {
            GXSetChanCtrl(GX_COLOR0A0, temp_r23, GX_SRC_REG, GX_SRC_VTX, lbl_1_bss_118, GX_DF_CLAMP, GX_AF_SPOT);
        }
        else {
            GXSetChanCtrl(GX_COLOR0A0, temp_r23, GX_SRC_REG, GX_SRC_REG, lbl_1_bss_118, GX_DF_CLAMP, GX_AF_SPOT);
        }
    }
}
#undef SET_TEVCOLOR_ALPHA

s32 fn_1_11670(void)
{
    lbl_1_data_19C *= 0x41C64E6D;
    lbl_1_data_19C += 0x3039;
    return lbl_1_data_19C >> 16;
}

float fn_1_116C4(float arg0, float arg1)
{
    float temp_f31;
    float temp_f30;
    temp_f30 = 360;
    temp_f31 = atan2d(arg0, arg1);
    if (temp_f31 < -180) {
        temp_f31 += temp_f30;
    }
    else if (temp_f31 >= 180.0) {
        temp_f31 -= temp_f30;
    }
    return temp_f31;
}

float fn_1_11780(Vec *arg0, Vec *arg1)
{
    return VECDistanceXYZ(arg0, arg1);
}
