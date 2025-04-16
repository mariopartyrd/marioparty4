#include "game/audio.h"
#include "game/chrman.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/wipe.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/sprite.h"

#include "REL/m408Dll.h"

#include "ext_math.h"
#include "math.h"

#ifndef __MWERKS__
#include "game/frand.h"
#endif

omObjData *lbl_1_bss_110;
u32 lbl_1_bss_10C;
Vec lbl_1_bss_100;
Vec lbl_1_bss_F4;
HsfanimStruct01 *lbl_1_bss_A4[20];
u32 lbl_1_bss_A0;
HsfanimStruct01 *lbl_1_bss_94[3];
s32 lbl_1_bss_88[3];
s32 lbl_1_bss_84;
s32 lbl_1_bss_80;

void fn_1_8A20(omObjData *object);
void fn_1_9770(omObjData *object);

void fn_1_8958(Process *objman)
{
    omObjData *object;
    lbl_1_bss_10C = 0;
    object = omAddObjEx(objman, 20, 9, 0, -1, fn_1_8A20);
    object->work[0] = 0;
    lbl_1_bss_110 = omAddObjEx(objman, 21, 2, 0, -1, fn_1_9770);
    lbl_1_bss_110->work[0] = 0;
    lbl_1_bss_84 = lbl_1_bss_80 = -1;
}

void fn_1_8FAC(omObjData *object);

void fn_1_A894(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_B700(s16 arg0, u32 arg1);
void fn_1_BB94(void);
void fn_1_BDE0(void);

void fn_1_8A20(omObjData *object)
{
    s16 temp_r31;
    s32 temp_r29;
    for (temp_r29 = 0; temp_r29 < 20; temp_r29++) {
        lbl_1_bss_A4[temp_r29] = NULL;
    }
    lbl_1_bss_A0 = 0;
    for (temp_r29 = 0; temp_r29 < 3; temp_r29++) {
        lbl_1_bss_94[temp_r29] = NULL;
        lbl_1_bss_88[temp_r29] = 0;
    }
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x00));
    omSetSca(object, 0.1f, 0.1f, 0.1f);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x01));
    Hu3DModelScaleSet(object->model[1], 0.1f, 0.1f, 0.1f);
    Hu3DModelPosSet(object->model[1], 0, 11990, 0);
    Hu3DModelShadowMapSet(object->model[1]);
    temp_r31 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M408, 0x0B)), 1);
    object->model[2] = temp_r31;
    Hu3DModelLayerSet(temp_r31, 6);
    Hu3DParticleColSet(temp_r31, 255, 255, 255);
    Hu3DParticleHookSet(temp_r31, fn_1_A894);
    Hu3DModelPosSet(temp_r31, 0, 0, 0);
    ((ParticleData *)Hu3DData[temp_r31].unk_120)->unk_00 = 0;
    ((ParticleData *)Hu3DData[temp_r31].unk_120)->unk_02 = 0;
    temp_r31 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M408, 0x0D)), 1);
    object->model[3] = temp_r31;
    Hu3DParticleBlendModeSet(temp_r31, 1);
    Hu3DModelLayerSet(temp_r31, 6);
    Hu3DParticleColSet(temp_r31, 255, 255, 255);
    Hu3DParticleHookSet(temp_r31, fn_1_A894);
    Hu3DModelPosSet(temp_r31, 0, 0, 0);
    ((ParticleData *)Hu3DData[temp_r31].unk_120)->unk_00 = 0;
    ((ParticleData *)Hu3DData[temp_r31].unk_120)->unk_02 = 1;
    temp_r31 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M408, 0x11)), 1);
    object->model[5] = temp_r31;
    Hu3DModelLayerSet(temp_r31, 7);
    Hu3DParticleColSet(temp_r31, 255, 255, 255);
    Hu3DParticleHookSet(temp_r31, fn_1_A894);
    Hu3DModelPosSet(temp_r31, 0, 0, 0);
    ((ParticleData *)Hu3DData[temp_r31].unk_120)->unk_00 = 0;
    ((ParticleData *)Hu3DData[temp_r31].unk_120)->unk_02 = 2;
    temp_r31 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M408, 0x10)), 8);
    object->model[6] = temp_r31;
    Hu3DParticleBlendModeSet(temp_r31, 1);
    Hu3DModelLayerSet(temp_r31, 6);
    Hu3DModelPosSet(temp_r31, 0, 0, 0);
    fn_1_B700(temp_r31, 0);
    temp_r31 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M408, 0x0F)), 6);
    object->model[6] = temp_r31;
    Hu3DParticleBlendModeSet(temp_r31, 1);
    Hu3DModelLayerSet(temp_r31, 6);
    Hu3DModelPosSet(temp_r31, 0, 0, 0);
    fn_1_B700(temp_r31, 1);
    temp_r31 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M408, 0x0D)), 5);
    object->model[6] = temp_r31;
    Hu3DParticleBlendModeSet(temp_r31, 1);
    Hu3DModelLayerSet(temp_r31, 6);
    Hu3DModelPosSet(temp_r31, 0, 0, 0);
    fn_1_B700(temp_r31, 2);
    fn_1_BB94();
    lbl_1_bss_10C = 1;
    object->func = fn_1_8FAC;
    object->work[1] = 0;
}

void fn_1_9514(omObjData *object);

void fn_1_8FAC(omObjData *object)
{
    object->work[1]++;
    switch (lbl_1_bss_10C) {
        case 1:
            if (lbl_1_bss_110->work[0] == 4) {
                lbl_1_bss_10C = 2;
                fn_1_817C(&lbl_1_bss_100, &lbl_1_bss_F4);
                object->work[1] = 0;
            }
            break;

        case 2:
            fn_1_817C(&lbl_1_bss_100, &lbl_1_bss_F4);
            if (lbl_1_bss_80 < 0) {
                lbl_1_bss_80 = HuAudFXPlay(1361);
            }
            lbl_1_bss_10C = 3;
            object->work[1] = 0;
            break;

        case 3:
            lbl_1_bss_F4.y += -6.666667f;
            lbl_1_bss_F4.z += -0.5833334f;
            lbl_1_bss_100.y += 20.0f / 60.0f;
            fn_1_817C(&lbl_1_bss_100, &lbl_1_bss_F4);
            if (lbl_1_bss_F4.y > 12010) {
                break;
            }
            if (lbl_1_bss_84 < 0) {
                lbl_1_bss_84 = HuAudFXPlay(1357);
            }
            if (lbl_1_bss_80 >= 0) {
                HuAudFXStop(lbl_1_bss_80);
                lbl_1_bss_80 = -1;
            }
            lbl_1_bss_10C = 4;
            object->work[1] = 0;
            object->work[2] = 0;
            break;

        case 4:
            if (object->work[1] < 24.0f) {
                lbl_1_bss_100.y += 4.0f / 12.0f;
                fn_1_817C(&lbl_1_bss_100, &lbl_1_bss_F4);
            }
            else {
                if (object->work[2] == 0) {
                    if (!lbl_1_bss_40) {
                        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
                        lbl_1_bss_44 = 1;
                    }
                    object->work[2]++;
                }
                CZoom -= 2.5000002f;
                if (object->work[1] < 90.0f) {
                    break;
                }
                lbl_1_bss_10C = 5;
                object->work[1] = 0;
            }
            break;

        default:
            lbl_1_bss_10C = 5;
            break;
    }
    omSetTra(object, Center.x + (sind(CRot.y) * cosd(CRot.x) * CZoom), Center.y + (-sind(CRot.x) * CZoom),
        Center.z + (cosd(CRot.y) * cosd(CRot.x) * CZoom));
    fn_1_BDE0();
    if (lbl_1_bss_10C == 5) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
        lbl_1_bss_10C = 5;
        object->func = fn_1_9514;
    }
}

void fn_1_9514(omObjData *object)
{
    if (!WipeStatGet() && object->work[2] != 0) {
        if (!lbl_1_bss_40) {
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
            lbl_1_bss_44 = 0;
        }
        object->work[2] = 0;
    }
    if (fn_1_6878() >= 4) {
        Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    }
    omSetTra(object, Center.x + (sind(CRot.y) * cosd(CRot.x) * CZoom), Center.y + (-sind(CRot.x) * CZoom) - 1000,
        Center.z + (cosd(CRot.y) * cosd(CRot.x) * CZoom));
}

typedef struct work_99C8 {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    Vec unk24;
    Vec unk30;
    Vec unk3C;
    s32 unk48[2];
} Work99C8;

void fn_1_99C8(omObjData *object);
void fn_1_A37C(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_1_9770(omObjData *object)
{
    Work99C8 *temp_r31;
    s32 temp_r29;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work99C8), MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M408, 0x0A));
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(object->model[0], 3.0f);
    Hu3DModelShadowSet(object->model[0]);
    object->func = fn_1_99C8;
    object->work[0] = 0;
    object->work[1] = 0;
    temp_r31->unk3C.x = temp_r31->unk3C.y = temp_r31->unk3C.z = 0;
    temp_r31->unk0.x = temp_r31->unk0.y = temp_r31->unk0.z = 0;
    temp_r31->unk0.z = 1000;
    omSetTra(object, 0, 12080, -2 * temp_r31->unk0.z);
    omSetSca(object, 0.5f, 0.5f, 0.5f);
    temp_r29 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M408, 0x24)), 1024);
    object->model[1] = temp_r29;
    Hu3DModelLayerSet(temp_r29, 6);
    Hu3DParticleColSet(temp_r29, 255, 255, 255);
    Hu3DParticleHookSet(temp_r29, fn_1_A37C);
    Hu3DModelPosSet(temp_r29, 0, 0, 0);
    ((ParticleData *)Hu3DData[temp_r29].unk_120)->unk_00 = 0;
    temp_r31->unk30.y = -35;
    temp_r31->unk30.z = 350;
    temp_r31->unk18.y = 800 + object->trans.y;
    temp_r31->unk48[0] = temp_r31->unk48[1] = -1;
    HuDataDirClose(DATA_MAKE_NUM(DATADIR_M408, 10));
}

void fn_1_A334(omObjData *object);
void fn_1_A4E8(s32 arg0, Vec *arg1, u32 arg2);

void fn_1_99C8(omObjData *object)
{
    float temp_f31;

    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    Work99C8 *temp_r31;
    temp_r31 = object->data;
    object->trans.x += temp_r31->unk0.x * (1.0f / 60.0f);
    object->trans.y += temp_r31->unk0.y * (1.0f / 60.0f);
    object->trans.z += temp_r31->unk0.z * (1.0f / 60.0f);
    object->work[1]++;
    switch (object->work[0]) {
        case 0:
            if (object->work[1] < 120.0f) {
                float temp_f30 = (1.0f / 60.0f) * (1.5f * (120.0f - object->work[1]));
                if (temp_f30 > 1.0f) {
                    temp_f30 = 1.0f;
                }
                temp_f31 = temp_r31->unk18.z;
                temp_r31->unk30.z -= (175.0f / 60.0f) * temp_f30;
                temp_r31->unk30.y += 1.1666667f * temp_f30;
                temp_r31->unk18.x = object->trans.x + (temp_r31->unk30.z * sind(temp_r31->unk30.y));
                temp_r31->unk18.z = object->trans.z + (temp_r31->unk30.z * cosd(temp_r31->unk30.y));
                temp_r31->unk18.y -= 8.333334f * temp_f30;
                temp_r31->unk24.x = 0;
                temp_r31->unk24.y = 0;
                temp_r31->unk24.z = 0.96f * temp_r31->unk0.z;
            }
            else {
                temp_r31->unk18.z += temp_r31->unk24.z * (1.0f / 60.0f);
            }
            temp_r31->unkC.x = object->trans.x;
            temp_r31->unkC.y = object->trans.y;
            temp_r31->unkC.z = object->trans.z;
            sp2C.x = object->trans.x;
            sp2C.y = object->trans.y;
            sp2C.z = object->trans.z;
            if (temp_r31->unk48[0] < 0) {
                temp_r31->unk48[0] = HuAudFXEmiterPlay(1362, &sp2C);
            }
            if (temp_r31->unk48[1] < 0) {
                temp_r31->unk48[1] = HuAudFXEmiterPlay(1356, &sp2C);
            }
            if (object->work[1] < 180.0f) {
                break;
            }
            object->work[0] = 1;
            object->work[1] = 0;
            break;

        case 1:
            temp_r31->unk24.z *= 0.6f;
            temp_r31->unk18.z += (temp_r31->unk24.z * (1.0f / 60.0f));
            temp_r31->unk18.x += (temp_r31->unk24.z * (1.0f / 60.0f));
            temp_r31->unkC.x = object->trans.x;
            temp_r31->unkC.y = object->trans.y;
            temp_r31->unkC.z = object->trans.z;
            if (object->work[1] < 60.0f) {
                break;
            }
            object->work[0] = 2;
            object->work[1] = 0;
            break;

        case 2:
            temp_r31->unk3C.x += 1.5000001f;
            temp_r31->unk0.z = 1000.0 * cosd(temp_r31->unk3C.x);
            temp_r31->unk0.y = 1000.0 * sind(temp_r31->unk3C.x);
            temp_r31->unkC.x = object->trans.x;
            temp_r31->unkC.y = object->trans.y;
            temp_r31->unkC.z = object->trans.z;
            if (object->work[1] < 120.0f) {
                break;
            }
            object->work[0] = 3;
            object->work[1] = 0;
            temp_r31->unk3C.x = 180;
            break;

        case 3:
            temp_r31->unk3C.z += 3.0000002f;
            temp_f31 = (1.0f / 60.0f) * object->work[1];
            temp_f31 = 1.0f - (temp_f31 * temp_f31);
            temp_r31->unkC.x += temp_f31 * (object->trans.x - temp_r31->unkC.x);
            temp_r31->unkC.y += temp_f31 * (object->trans.y - temp_r31->unkC.y);
            temp_r31->unkC.z += temp_f31 * (object->trans.z - temp_r31->unkC.z);
            if (object->work[1] < 60.0f) {
                break;
            }
            lbl_1_bss_F4.x = temp_r31->unkC.x;
            lbl_1_bss_F4.y = temp_r31->unkC.y;
            lbl_1_bss_F4.z = temp_r31->unkC.z;
            lbl_1_bss_100.x = temp_r31->unk18.x;
            lbl_1_bss_100.y = temp_r31->unk18.y;
            lbl_1_bss_100.z = temp_r31->unk18.z;
            object->work[0] = 4;
            object->work[1] = 0;
            break;

        case 4:
            temp_r31->unk3C.z += 3.0000002f;
            if (object->work[1] > 42.0f) {
                if (temp_r31->unk48[0] >= 0) {
                    HuAudFXStop(temp_r31->unk48[0]);
                    temp_r31->unk48[0] = -1;
                }
                if (temp_r31->unk48[1] >= 0) {
                    HuAudFXStop(temp_r31->unk48[1]);
                    temp_r31->unk48[1] = -1;
                }
            }
            if (object->work[1] < 240.0f) {
                break;
            }
            object->work[0] = 5;
            object->work[1] = 0;
            break;

        default:
            object->work[0] = 5;
            object->func = fn_1_A334;
            break;
    }
    omSetRot(object, -temp_r31->unk3C.x, temp_r31->unk3C.y, temp_r31->unk3C.z);
    if (object->trans.y < 12150.0f) {
        sp20.x = object->trans.x;
        sp20.y = object->trans.y;
        sp20.z = object->trans.z + 10;
        fn_1_A4E8(object->model[1], &sp20, 4);
        sp20.x = sp8.x = object->trans.x;
        sp20.z = object->trans.z;
        sp8.z = object->trans.z - 10;
        sp20.y = object->trans.y + 250.0f;
        sp8.y = object->trans.y;
        sp14.x = 0;
        sp14.y = 0;
        sp14.z = 1;
        Hu3DShadowPosSet(&sp20, &sp14, &sp8);
    }
    if (temp_r31->unk48[0] >= 0) {
        sp2C.x = object->trans.x - 30;
        sp2C.y = object->trans.y;
        sp2C.z = object->trans.z + 25;
        HuAudFXEmiterUpDate(temp_r31->unk48[0], &sp2C);
    }
    if (temp_r31->unk48[1] < 0) {
        sp2C.x = object->trans.x + 30;
        sp2C.y = object->trans.y;
        sp2C.z = object->trans.z + 25;
        HuAudFXEmiterUpDate(temp_r31->unk48[1], &sp2C);
    }
    if (object->work[0] < 4) {
        fn_1_84C4(temp_r31->unk18.x, temp_r31->unk18.y, temp_r31->unk18.z, temp_r31->unkC.x, temp_r31->unkC.y, temp_r31->unkC.z);
    }
    if (fn_1_C43C() == 5) {
        object->func = fn_1_A334;
    }
}

void fn_1_A334(omObjData *object)
{
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
}

void fn_1_A37C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    if (particle->unk_00 == 0) {
        particle->unk_00++;
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk00 = 0;
            temp_r31->unk2C = 0;
            temp_r31->unk40.a = 0;
        }
    }
    else {
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            if (temp_r31->unk00) {
                temp_r31->unk34.x += temp_r31->unk08.x;
                temp_r31->unk34.y += temp_r31->unk08.y;
                temp_r31->unk34.z += temp_r31->unk08.z;
                temp_r31->unk2C += temp_r31->unk14.x;
                temp_r31->unk14.y -= temp_r31->unk14.z;
                temp_r31->unk40.a = temp_r31->unk14.y;
                if (--temp_r31->unk00 == 0) {
                    temp_r31->unk00 = 0;
                    temp_r31->unk2C = 0;
                    temp_r31->unk40.a = 0;
                }
            }
        }
        DCStoreRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
    }
}

void fn_1_A4E8(s32 arg0, Vec *arg1, u32 arg2)
{
    ParticleData *temp_r30 = Hu3DData[arg0].unk_120;
    if (temp_r30->unk_00) {
        float temp_f31;
        s32 temp_r29;
        HsfanimStruct01 *temp_r31 = temp_r30->unk_48;
        for (temp_r29 = 0; temp_r29 < temp_r30->unk_30; temp_r29++, temp_r31++) {
            if (temp_r31->unk00 != 0) {
                continue;
            }
            temp_r31->unk00 = 60.0f * (((1.5f / 1000.0f) * frandmod(1000)) + 1.0f);
            temp_r31->unk34.x = arg1->x;
            temp_r31->unk34.y = 12000;
            temp_r31->unk34.z = arg1->z;
            temp_r31->unk08.x = (1.0f / 60.0f) * ((0.6f * frandmod(1000)) - 300.0f);
            temp_r31->unk08.y = (1.0f / 60.0f) * ((0.04f * frandmod(1000)) + 10.0f);
            temp_r31->unk08.z = 0;
            temp_r31->unk14.x = 0.3f + ((3.0f / 1000.0f) * frandmod(1000));
            temp_r31->unk2C = 10;
            temp_r31->unk40.a = frandmod(127) + 64;
            temp_r31->unk14.y = temp_r31->unk40.a;
            temp_r31->unk14.z = temp_r31->unk14.y * (1.0f / temp_r31->unk00);
            temp_f31 = frandmod(1000) * (1.0f / 1000.0f);
            temp_r31->unk40.r = (temp_f31 * 55) + 200;
            temp_r31->unk40.g = (temp_f31 * 50) + 205;
            temp_r31->unk40.b = (temp_f31 * 5) + 250;
            if (--arg2 == 0) {
                break;
            }
        }
    }
}

void fn_1_A894(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    float sp14[][6] = {
        { 600, 1, 0.95, 0.8, 1, 0 },
        { 600, 1, 0.6, 0.9, 0.3, 0 },
        { 13, 1, 1, 1, 0.5, 0 },
    };
    if (particle->unk_00 == 0) {
        particle->unk_00++;
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk00 = 1;
            temp_r31->unk2C = sp14[particle->unk_02][0];
            temp_r31->unk40.r = 255 * sp14[particle->unk_02][1];
            temp_r31->unk40.g = 255 * sp14[particle->unk_02][2];
            temp_r31->unk40.b = 255 * sp14[particle->unk_02][3];
            temp_r31->unk40.a = 255 * sp14[particle->unk_02][4];
            temp_f31 = -70;
            temp_f30 = -10;
            temp_r31->unk08.x = sind(temp_f30) * cosd(temp_f31);
            temp_r31->unk08.y = -sind(temp_f31);
            temp_r31->unk08.z = cosd(temp_f30) * cosd(temp_f31);
        }
    }
    else {
        particle->unk_00++;
        if (particle->unk_00 < 339.0f) {
            return;
        }
        if (particle->unk_00 >= 600.0f) {
            particle->unk_00 = 601;
            temp_r31 = particle->unk_48;
            for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
                temp_r31->unk00 = 0;
                temp_r31->unk2C = 0;
                temp_r31->unk40.a = 0;
            }
        }
        else {
            temp_r31 = particle->unk_48;
            for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
                Vec sp8;
                if (temp_r31->unk00 == 0) {
                    continue;
                }
                sp8.x = sind(CRot.y) * cosd(CRot.x);
                sp8.y = -sind(CRot.x);
                sp8.z = cosd(CRot.y) * cosd(CRot.x);
                if (particle->unk_02 < 2) {
                    temp_f31 = 4500;
                    temp_r31->unk34.x = (Center.x + (temp_r31->unk08.x * temp_f31)) + (sp8.x * CZoom);
                    temp_r31->unk34.y = (Center.y + (temp_r31->unk08.y * temp_f31)) + (sp8.y * CZoom);
                    temp_r31->unk34.z = (Center.z + (temp_r31->unk08.z * temp_f31)) + (sp8.z * CZoom);
                    if (particle->unk_02 != 0) {
                        temp_f31 = -((sp8.x * temp_r31->unk08.x) + (sp8.y * temp_r31->unk08.y) + (sp8.z * temp_r31->unk08.z));
                        if (temp_f31 > 0.77f) {
                            temp_f30 = (1.0f / 0.23f) * (temp_f31 - 0.77f);
                            temp_r31->unk2C = 1400 * temp_f30;
                            temp_r31->unk40.a = (32.0f * temp_f30) + 16.0f;
                        }
                        else {
                            temp_r31->unk2C = 0;
                        }
                    }
                }
                else {
                    temp_f31 = CZoom - 10;
                    temp_r31->unk34.x = (sp8.x * temp_f31) + Center.x;
                    temp_r31->unk34.y = (sp8.y * temp_f31) + Center.y;
                    temp_r31->unk34.z = (sp8.z * temp_f31) + Center.z;
                    temp_f31 = -((sp8.x * temp_r31->unk08.x) + (sp8.y * temp_r31->unk08.y) + (sp8.z * temp_r31->unk08.z));
                    if (temp_f31 > 0.9f) {
                        temp_f30 = 10.0f * (temp_f31 - 0.9f);
                        temp_r31->unk40.a = temp_f30 * 210.0f;
                    }
                    else {
                        temp_r31->unk40.a = 0;
                    }
                }
            }
            DCStoreRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
        }
    }
}

void fn_1_AFF4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    HsfanimStruct01 *temp_r30;
    s32 temp_r29;
    if (particle->unk_00 == 0) {
        particle->unk_00++;
        temp_f31 = -70;
        temp_f30 = -10;
        particle->unk_04.x = sind(temp_f30) * cosd(temp_f31);
        particle->unk_04.y = -sind(temp_f31);
        particle->unk_04.z = cosd(temp_f30) * cosd(temp_f31);
        temp_f31 = 0;
        temp_r30 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r30++) {
            temp_r30->unk00 = 1;
            temp_f31 += 1.0f / particle->unk_30;
            temp_r30->unk2C = 40.0f + ((1.0f - temp_f31) * (100.0f + frandmod(1000)));
            temp_r30->unk40.r = frandmod(127) + 128;
            temp_r30->unk40.g = frandmod(127) + 128;
            temp_r30->unk40.b = frandmod(127) + 128;
            temp_r30->unk40.a = frandmod(16) + 16;
        }
    }
    else {
        particle->unk_00++;
        if (particle->unk_00 < 339.0f) {
            return;
        }
        if (particle->unk_00 >= 600.0f) {
            particle->unk_00 = 601;
            temp_r30 = particle->unk_48;
            for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r30++) {
                temp_r30->unk00 = 0;
                temp_r30->unk2C = 0;
                temp_r30->unk40.a = 0;
            }
        }
        else {
            Vec sp20;
            Vec sp14;
            Vec sp8;
            sp20.x = sind(CRot.y) * cosd(CRot.x);
            sp20.y = -sind(CRot.x);
            sp20.z = cosd(CRot.y) * cosd(CRot.x);
            temp_f31 = -((-particle->unk_04.x * -sp20.x) + (-particle->unk_04.y * -sp20.y) + (-particle->unk_04.z * -sp20.z));
            sp14.x = -sp20.x + (-2.0f * particle->unk_04.x * temp_f31);
            sp14.y = -sp20.y + (-2.0f * particle->unk_04.y * temp_f31);
            sp14.z = -sp20.z + (-2.0f * particle->unk_04.z * temp_f31);
            temp_f31 = 4500;
            sp8.x = (Center.x + (particle->unk_04.x * temp_f31)) + (sp20.x * CZoom);
            sp8.y = (Center.y + (particle->unk_04.y * temp_f31)) + (sp20.y * CZoom);
            sp8.z = (Center.z + (particle->unk_04.z * temp_f31)) + (sp20.z * CZoom);
            temp_r30 = particle->unk_48;
            temp_f30 = 0;
            for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r30++) {
                if (temp_r30->unk00 == 0) {
                    continue;
                }
                temp_f30 += 1.0f / particle->unk_30;
                temp_f31 = 10.0f * (430.0f * (1.0f - ((1.0f - temp_f30) * (1.0f - temp_f30))));
                temp_r30->unk34.x = sp8.x + (sp14.x * temp_f31);
                temp_r30->unk34.y = sp8.y + (sp14.y * temp_f31);
                temp_r30->unk34.z = sp8.z + (sp14.z * temp_f31);
            }
            DCStoreRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
        }
    }
}

void fn_1_B700(s16 arg0, u32 arg1)
{
    float temp_f31;
    float temp_f30;
    HsfanimStruct01 *temp_r31;
    ParticleData *temp_r30;
    s32 temp_r29;
    s32 temp_r27;
    float sp1C[] = { 0.4f, 0.21f, 0.16f, 1.0f };
    float spC[] = { 0.15f, 0.6f, 1.3f, 1.0f };
    s16 sp2C[] = { 1, 0, 2, 0, 0, 1, 2, 0, 0, 1, 2, 1, 0, 0, 1, 2, 0, 1, 2, -1 };
    arg1 &= 0x3;
    temp_r30 = Hu3DData[arg0].unk_120;
    temp_r30->unk_00 = 1;
    temp_f31 = -70;
    temp_f30 = -10;
    temp_r30->unk_04.x = sind(temp_f30) * cosd(temp_f31);
    temp_r30->unk_04.y = -sind(temp_f31);
    temp_r30->unk_04.z = cosd(temp_f30) * cosd(temp_f31);
    temp_r31 = temp_r30->unk_48;
    for (temp_r27 = 0; temp_r27 < temp_r30->unk_30; temp_r27++, temp_r31++) {
        temp_r31->unk00 = 1;
        temp_r31->unk02 = arg1;
        for (temp_r29 = 0; sp2C[temp_r29] >= 0; temp_r29++) {
            if (arg1 != sp2C[temp_r29]) {
                continue;
            }
            if (lbl_1_bss_A4[temp_r29] == NULL) {
                break;
            }
        }
        if (sp2C[temp_r29] < 0) {
            temp_r31->unk2C = 0;
            temp_r31->unk40.a = 0;
            continue;
        }
        lbl_1_bss_A4[temp_r29] = temp_r31;
        lbl_1_bss_A0++;
        temp_r31->unk2C = 800.0f * (spC[arg1] * (1.0f + ((0.7f / 1000.0f) * frandmod(1000))));
        temp_r31->unk40.r = frandmod(160) + 32;
        temp_r31->unk40.g = frandmod(160) + 32;
        temp_r31->unk40.b = frandmod(160) + 32;
        temp_r31->unk40.a = (255.0f * sp1C[arg1]) - frandmod(16);
    }
    lbl_1_bss_94[arg1] = temp_r30->unk_48;
    lbl_1_bss_88[arg1] = temp_r30->unk_30;
}

void fn_1_BB94(void)
{
    float temp_f31;
    float temp_f30;
    HsfanimStruct01 *temp_r31;
    s32 temp_r30;
    float sp18[] = { 0.02f, 0.08f, 0.07f, 0.5f };
    float sp8[] = { 0.0009f, 0.00020000001f, 0.00001f, 0.0005f };
    temp_f31 = 0.1f;
    for (temp_r30 = 0; temp_r30 < lbl_1_bss_A0; temp_r30++) {
        temp_r31 = lbl_1_bss_A4[temp_r30];
        temp_f30 = 0.5f * (sp18[temp_r31->unk02] * (1.0f + (frandmod(1000) * sp8[temp_r31->unk02])));
        temp_f31 += temp_f30;
        temp_r31->unk14.x = temp_f31;
        temp_f31 += temp_f30;
    }
    temp_f31 = 1.0f / temp_f31;
    for (temp_r30 = 0; temp_r30 < lbl_1_bss_A0; temp_r30++) {
        temp_r31 = lbl_1_bss_A4[temp_r30];
        temp_r31->unk14.x *= temp_f31;
        temp_r31->unk2C *= (0.8f - (0.4f * temp_r31->unk14.x));
        temp_r31->unk14.x = 10.0f * (400.0f * temp_r31->unk14.x);
    }
    for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
        DCStoreRangeNoSync(lbl_1_bss_94[temp_r30], lbl_1_bss_88[temp_r30] * sizeof(HsfanimStruct01));
    }
    PPCSync();
}

void fn_1_BDE0(void)
{
    float temp_f31;
    float temp_f30;
    HsfanimStruct01 *temp_r31;
    s32 temp_r30;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    temp_r31 = lbl_1_bss_A4[0];
    temp_r31->unk00++;
    if (temp_r31->unk00 < 339.0f) {
        return;
    }
    if (temp_r31->unk00 >= 600.0f) {
        temp_r31->unk00 = 601;
        for (temp_r30 = 0; temp_r30 < lbl_1_bss_A0; temp_r30++) {
            temp_r31 = lbl_1_bss_A4[temp_r30];
            temp_r31->unk00 = 0;
            temp_r31->unk2C = 0;
            temp_r31->unk40.a = 0;
        }
        return;
    }
    sp2C.x = sind(CRot.y) * cosd(CRot.x);
    sp2C.y = -sind(CRot.x);
    sp2C.z = cosd(CRot.y) * cosd(CRot.x);
    temp_f31 = -70;
    temp_f30 = -10;
    sp20.x = sind(temp_f30) * cosd(temp_f31);
    sp20.y = -sind(temp_f31);
    sp20.z = cosd(temp_f30) * cosd(temp_f31);
    temp_f31 = 4500;
    sp8.x = (Center.x + (sp20.x * temp_f31)) + (sp2C.x * CZoom);
    sp8.y = (Center.y + (sp20.y * temp_f31)) + (sp2C.y * CZoom);
    sp8.z = (Center.z + (sp20.z * temp_f31)) + (sp2C.z * CZoom);
    temp_f31 = -((-sp20.x * -sp2C.x) + (-sp20.y * -sp2C.y) + (-sp20.z * -sp2C.z));
    sp14.x = -sp2C.x + (-2.0f * sp20.x * temp_f31);
    sp14.y = -sp2C.y + (-2.0f * sp20.y * temp_f31);
    sp14.z = -sp2C.z + (-2.0f * sp20.z * temp_f31);
    if (temp_f31 > 0.5f) {
        temp_f30 = 3.0f - (2.0f * temp_f31);
    }
    else {
        temp_f30 = 1.0f;
    }
    for (temp_r30 = 0; temp_r30 < lbl_1_bss_A0; temp_r30++) {
        temp_r31 = lbl_1_bss_A4[temp_r30];
        temp_r31->unk34.x = sp8.x + (temp_f30 * (sp14.x * temp_r31->unk14.x));
        temp_r31->unk34.y = sp8.y + (temp_f30 * (sp14.y * temp_r31->unk14.x));
        temp_r31->unk34.z = sp8.z + (temp_f30 * (sp14.z * temp_r31->unk14.x));
    }
    for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
        DCStoreRangeNoSync(lbl_1_bss_94[temp_r30], lbl_1_bss_88[temp_r30] * sizeof(HsfanimStruct01));
    }
    PPCSync();
}

void fn_1_C3C0(Vec *arg0, Vec *arg1)
{
    arg0->x = lbl_1_bss_110->trans.x;
    arg0->y = lbl_1_bss_110->trans.y;
    arg0->z = lbl_1_bss_110->trans.z;
    arg1->x = lbl_1_bss_110->rot.x;
    arg1->y = lbl_1_bss_110->rot.y;
    arg1->z = lbl_1_bss_110->rot.z;
}

u32 fn_1_C43C(void)
{
    return lbl_1_bss_10C;
}
