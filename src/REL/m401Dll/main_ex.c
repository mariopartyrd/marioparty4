#include "game/audio.h"
#include "game/frand.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"

#include "ext_math.h"

#include "REL/m401Dll.h"

struct Bss13EData {
    s16 unk0;
    s16 unk2[3];
};

AnimData *lbl_2_bss_250;
AnimData *lbl_2_bss_24C;
AnimData *lbl_2_bss_248;
AnimData *lbl_2_bss_244;
AnimData *lbl_2_bss_240;
AnimData *lbl_2_bss_23C;
AnimData *lbl_2_bss_238;
AnimData *lbl_2_bss_220[2][3];
struct Bss13EData lbl_2_bss_13E[28];
s16 lbl_2_bss_136[4];
s16 lbl_2_bss_134;
float lbl_2_bss_130;
float lbl_2_bss_12C;
float lbl_2_bss_128;
float lbl_2_bss_124;
s16 lbl_2_bss_120;

void fn_2_10240(Vec *arg0, Vec *arg1)
{
    CameraData *camera;
    Mtx lookat;
    Mtx44 proj;
    float coord[4];
    arg0->y = -arg0->y;
    camera = &Hu3DCamera[0];
    MTXLookAt(lookat, &camera->pos, &camera->up, &camera->target);
    MTXMultVec(lookat, arg0, arg0);
    MTXPerspective(proj, camera->fov, camera->aspect, camera->near, camera->far);
    coord[0] = (arg0->x * proj[0][0]) + (arg0->y * proj[0][1]) + (arg0->z * proj[0][2]) + proj[0][3];
    coord[1] = (arg0->x * proj[1][0]) + (arg0->y * proj[1][1]) + (arg0->z * proj[1][2]) + proj[1][3];
    coord[2] = (arg0->x * proj[2][0]) + (arg0->y * proj[2][1]) + (arg0->z * proj[2][2]) + proj[2][3];
    coord[3] = (arg0->x * proj[3][0]) + (arg0->y * proj[3][1]) + (arg0->z * proj[3][2]) + proj[3][3];
    arg1->x = ((coord[0] / coord[3]) * 320.0f) + 320.0f;
    arg1->y = ((coord[1] / coord[3]) * 240.0f) + 240.0f;
    arg1->z = coord[2] / coord[3];
}

void fn_2_1041C(void)
{
    s32 i;
    lbl_2_bss_250 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x11));
    lbl_2_bss_24C = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x12));
    lbl_2_bss_248 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x13));
    lbl_2_bss_240 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x14));
    lbl_2_bss_23C = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x15));
    lbl_2_bss_238 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x16));
    HuSprAnimLock(lbl_2_bss_250);
    HuSprAnimLock(lbl_2_bss_24C);
    HuSprAnimLock(lbl_2_bss_248);
    HuSprAnimLock(lbl_2_bss_240);
    HuSprAnimLock(lbl_2_bss_23C);
    HuSprAnimLock(lbl_2_bss_238);
    lbl_2_bss_244 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x26));
    HuSprAnimLock(lbl_2_bss_244);
    lbl_2_bss_220[0][0] = lbl_2_bss_250;
    lbl_2_bss_220[0][1] = lbl_2_bss_24C;
    lbl_2_bss_220[0][2] = lbl_2_bss_248;
    lbl_2_bss_220[1][0] = lbl_2_bss_240;
    lbl_2_bss_220[1][1] = lbl_2_bss_23C;
    lbl_2_bss_220[1][2] = lbl_2_bss_238;
    for (i = 0; i < 4; i++) {
        lbl_2_bss_136[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x17));
        Hu3DModelAttrSet(lbl_2_bss_136[i], 1);
        Hu3DModelAttrSet(lbl_2_bss_136[i], 0x40000001);
        Hu3DModelScaleSet(lbl_2_bss_136[i], 1.5f, 1.5f, 1.0f);
        Hu3DModelLayerSet(lbl_2_bss_136[i], 2);
    }
}

void fn_2_10710(void)
{
    HuSprAnimKill(lbl_2_bss_250);
    HuSprAnimKill(lbl_2_bss_24C);
    HuSprAnimKill(lbl_2_bss_248);
    HuSprAnimKill(lbl_2_bss_240);
    HuSprAnimKill(lbl_2_bss_23C);
    HuSprAnimKill(lbl_2_bss_238);
    HuSprAnimKill(lbl_2_bss_244);
}

void fn_2_1079C(void)
{
    s32 i;
    for (i = 0; i < 28; i++) {
        lbl_2_bss_13E[i].unk0 = 0;
        lbl_2_bss_13E[i].unk2[0] = Hu3DParticleCreate(lbl_2_bss_250, 80);
        lbl_2_bss_13E[i].unk2[1] = Hu3DParticleCreate(lbl_2_bss_24C, 80);
        lbl_2_bss_13E[i].unk2[2] = Hu3DParticleCreate(lbl_2_bss_248, 80);
        Hu3DModelAttrSet(lbl_2_bss_13E[i].unk2[0], 1);
        Hu3DModelAttrSet(lbl_2_bss_13E[i].unk2[1], 1);
        Hu3DModelAttrSet(lbl_2_bss_13E[i].unk2[2], 1);
    }
    lbl_2_bss_134 = 0;
}

s16 fn_2_108C8(void)
{
    s32 i;
    s32 j;
    for (i = 0; i < 28; i++) {
        if (!lbl_2_bss_13E[i].unk0) {
            for (j = 0; j < 3; j++) {
                Hu3DModelAttrReset(lbl_2_bss_13E[i].unk2[j], 1);
            }
            lbl_2_bss_13E[i].unk0 = 1;
            return i;
        }
    }
    return -1;
}

void fn_2_10980(s16 arg0)
{
    s32 i;
    lbl_2_bss_13E[arg0].unk0 = 0;
    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(lbl_2_bss_13E[arg0].unk2[i], 1);
    }
}

s16 fn_2_10A08(void)
{
    s16 temp_r31 = lbl_2_bss_136[lbl_2_bss_134];
    lbl_2_bss_134 = (lbl_2_bss_134 + 1) & 0x3;
    Hu3DModelTPLvlSet(temp_r31, 1.0f);
    return temp_r31;
}

void fn_2_113AC(omObjData *object);
void fn_2_11A68(omObjData *object);
void fn_2_11B78(omObjData *object);
void fn_2_11C30(omObjData *object);
void fn_2_11D40(omObjData *object);
void fn_2_11E44(omObjData *object);
void fn_2_11EFC(omObjData *object);

void fn_2_11FB4(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_2_126C8(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_2_126F4(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_2_12B30(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_2_1301C(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_2_1350C(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_2_13B7C(ModelData *model, ParticleData *particle, Mtx matrix);

omObjData *fn_2_10A88(Vec *arg0, s16 arg1)
{
    omObjData *temp_r31;
    s32 temp_r30;
    ParticleData *temp_r28;
    UnkWork10A88 *temp_r27;
    s16 temp_r24 = fn_2_108C8();
    if (temp_r24 < 0) {
        return NULL;
    }
    {
        s16 temp_r22 = -1;
        if (arg1 == 0) {
            temp_r22 = 1;
        }
        temp_r31 = omAddObjEx(HuPrcCurrentGet(), 0x514, 3, 0, temp_r22, NULL);
    }

    temp_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkWork10A88), MEMORY_DEFAULT_NUM);
    temp_r27 = temp_r31->data;
    temp_r27->unk0 = *arg0;
    for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
        temp_r31->model[temp_r30] = lbl_2_bss_13E[temp_r24].unk2[temp_r30];
        temp_r28 = Hu3DData[temp_r31->model[temp_r30]].unk_120;
        Hu3DParticleCntSet(temp_r31->model[temp_r30], 0);
        Hu3DParticleAnimModeSet(temp_r31->model[temp_r30], 0);
        Hu3DModelLayerSet(temp_r31->model[temp_r30], 1);
        if (arg1 == 1) {
            temp_r31->unk10 = fn_2_10A08();
            Hu3DModelAttrReset(temp_r31->unk10, 1);
            temp_r28->unk_44 = lbl_2_bss_220[1][temp_r30];
            temp_r27->unk1C = 1.0f;
            temp_r31->work[3] = 45;
            Hu3DModelTPLvlSet(temp_r31->unk10, temp_r27->unk1C);
        }
        else {
            temp_r28->unk_44 = lbl_2_bss_220[0][temp_r30];
        }
    }
    temp_r27->unk10 = 3;
    temp_r27->unk12 = temp_r24;
    // I am not table to force arg1 to get reloaded without deleting code or serious temporary register allocation issues
    (void)arg1;
    switch ((temp_r27->unk18 = arg1)) {
        case 1:
            Hu3DModelPosSet(temp_r31->unk10, arg0->x, arg0->y, lbl_2_bss_60.z + arg0->z);

        case 0:
            temp_r31->trans.x = arg0->x;
            temp_r31->trans.y = arg0->y;
            temp_r31->trans.z = lbl_2_bss_60.z + arg0->z;
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                Hu3DParticleHookSet(temp_r31->model[temp_r30], fn_2_11FB4);
                Hu3DParticleColSet(temp_r31->model[temp_r30], 255, 255, 255);
                Hu3DModelPosSet(temp_r31->model[temp_r30], temp_r31->trans.x, temp_r31->trans.y, temp_r31->trans.z);
                temp_r28 = Hu3DData[temp_r31->model[temp_r30]].unk_120;
                Hu3DParticleBlendModeSet(temp_r31->model[temp_r30], 0);
                temp_r28->unk_00 = (temp_r30 * 4.5f) / 3.0f;
                temp_r28->unk_02 = 0;
                temp_r28->unk_1C = temp_r31;
            }
            temp_r27->unk14 = 0;
            temp_r31->func = fn_2_113AC;
            break;

        case 2:
            fn_2_A8A4(temp_r31, arg0->x, arg0->y, arg0->z);
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                Hu3DParticleHookSet(temp_r31->model[temp_r30], fn_2_126C8);
                Hu3DParticleColSet(temp_r31->model[temp_r30], 255, 255, 255);
                Hu3DModelPosSet(temp_r31->model[temp_r30], temp_r31->trans.x, temp_r31->trans.y, temp_r31->trans.z);
                Hu3DParticleBlendModeSet(temp_r31->model[temp_r30], 0);
                temp_r28 = Hu3DData[temp_r31->model[temp_r30]].unk_120;
                temp_r28->unk_00 = (temp_r30 * 2) + (frand() & 0x7);
                temp_r28->unk_1C = temp_r31;
            }
            temp_r31->func = fn_2_11A68;
            break;

        case 3:
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                Hu3DParticleHookSet(temp_r31->model[temp_r30], fn_2_126F4);
                Hu3DParticleColSet(temp_r31->model[temp_r30], 255, 255, 255);
                Hu3DModelPosSet(temp_r31->model[temp_r30], arg0->x, arg0->y, arg0->z);
                Hu3DParticleBlendModeSet(temp_r31->model[temp_r30], 0);
                temp_r28 = Hu3DData[temp_r31->model[temp_r30]].unk_120;
                temp_r28->unk_00 = (temp_r30 * 2) + (frand() & 0x7);
                temp_r28->unk_1C = temp_r31;
            }
            temp_r31->func = fn_2_11B78;
            break;

        case 4:
            fn_2_A8A4(temp_r31, arg0->x, arg0->y, arg0->z);
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                Hu3DParticleHookSet(temp_r31->model[temp_r30], fn_2_12B30);
                Hu3DParticleColSet(temp_r31->model[temp_r30], 255, 255, 255);
                Hu3DModelPosSet(temp_r31->model[temp_r30], temp_r31->trans.x, temp_r31->trans.y, temp_r31->trans.z);
                Hu3DParticleBlendModeSet(temp_r31->model[temp_r30], 0);
                temp_r28 = Hu3DData[temp_r31->model[temp_r30]].unk_120;
                temp_r28->unk_00 = (temp_r30 * 2) + (frand() & 0x7);
                temp_r28->unk_1C = temp_r31;
            }
            temp_r31->func = fn_2_11C30;
            break;

        case 5:
            fn_2_A8A4(temp_r31, arg0->x, arg0->y, arg0->z);
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                Hu3DParticleHookSet(temp_r31->model[temp_r30], fn_2_1301C);
                Hu3DParticleColSet(temp_r31->model[temp_r30], 255, 255, 255);
                Hu3DModelPosSet(temp_r31->model[temp_r30], temp_r31->trans.x, temp_r31->trans.y, temp_r31->trans.z);
                Hu3DParticleBlendModeSet(temp_r31->model[temp_r30], 1);
                temp_r28 = Hu3DData[temp_r31->model[temp_r30]].unk_120;
                temp_r28->unk_00 = (temp_r30 * 2) + (frand() & 0x7);
                temp_r28->unk_1C = temp_r31;
            }
            temp_r31->func = fn_2_11D40;
            break;

        case 6:
            omSetTra(temp_r31, arg0->x, arg0->y, arg0->z);
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                Hu3DParticleHookSet(temp_r31->model[temp_r30], fn_2_1350C);
                Hu3DParticleColSet(temp_r31->model[temp_r30], 255, 255, 255);
                Hu3DModelPosSet(temp_r31->model[temp_r30], temp_r31->trans.x, temp_r31->trans.y, temp_r31->trans.z);
                temp_r28 = Hu3DData[temp_r31->model[temp_r30]].unk_120;
                Hu3DParticleBlendModeSet(temp_r31->model[temp_r30], 1);
            }
            temp_r31->func = fn_2_11E44;
            break;

        case 7:
            omSetTra(temp_r31, arg0->x, arg0->y, arg0->z);
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                Hu3DParticleHookSet(temp_r31->model[temp_r30], fn_2_13B7C);
                Hu3DParticleColSet(temp_r31->model[temp_r30], 255, 255, 255);
                Hu3DModelPosSet(temp_r31->model[temp_r30], temp_r31->trans.x, temp_r31->trans.y, temp_r31->trans.z);
                temp_r28 = Hu3DData[temp_r31->model[temp_r30]].unk_120;
                Hu3DParticleBlendModeSet(temp_r31->model[temp_r30], 1);
            }
            temp_r31->func = fn_2_11EFC;
            break;

        default:
            break;
    }
    return temp_r31;
}

void fn_2_118B0(omObjData *object);
void fn_2_123F8(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_2_113AC(omObjData *object)
{
    UnkWork10A88 *temp_r30;
    s32 temp_r29;
    M401WorkPlayer *temp_r28;
    omObjData *temp_r27;
    ParticleData *temp_r25;
    s16 temp_r24;
    temp_r30 = object->data;
    temp_r30->unk0.z += (lbl_2_bss_50 * 0.5f);
    object->trans.x = temp_r30->unk0.x;
    object->trans.y = temp_r30->unk0.y;
    object->trans.z = lbl_2_bss_60.z + temp_r30->unk0.z;
    if (object->unk10 != 0) {
        Hu3DModelPosSet(object->unk10, object->trans.x, object->trans.y, object->trans.z);
    }
    for (temp_r29 = 1; temp_r29 < 3; temp_r29++) {
        Hu3DModelRotSet(object->model[temp_r29], object->rot.x, object->rot.y, object->rot.z);
        Hu3DModelPosSet(object->model[temp_r29], object->trans.x, object->trans.y, object->trans.z);
    }
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        float dist;
        temp_r27 = lbl_2_bss_118[temp_r29];
        temp_r28 = temp_r27->data;
        if (temp_r28->unk78 != 0) {
            continue;
        }
        dist = VECDistanceXYZ(&object->trans, &temp_r27->trans);
        if (dist < 108.00001f) {
            Hu3DMotionShiftSet(lbl_2_bss_118[temp_r29]->model[0], lbl_2_bss_118[temp_r29]->motion[6], 0, 10, 0);
            HuAudFXPlay(1288);
            if (temp_r30->unk18 == 0) {
                HuAudFXPlay(9);
                temp_r28->unk72++;
                omVibrate(temp_r28->unk4, 12, 6, 6);
            }
            else {
                HuAudFXPlay(1292);
                temp_r28->unk74 = 3;
                temp_r28->unk72 += 3;
                fn_2_169C(temp_r28->unk4);
                omVibrate(temp_r28->unk4, 12, 4, 2);
            }
            temp_r28->unk84 = 50;
            for (temp_r29 = 0; temp_r29 < 3; temp_r29++) {
                temp_r25 = Hu3DData[object->model[temp_r29]].unk_120;
                temp_r25->unk_02 = 0;
                Hu3DParticleHookSet(object->model[temp_r29], fn_2_123F8);
            }
            object->func = fn_2_118B0;
            break;
        }
    }
    if (temp_r30->unk0.z > 850.0f) {
        temp_r30->unk14 = 1;
    }
    if (object->unk10) {
        if (object->work[3] != 0) {
            object->work[3]--;
        }
        else {
            temp_r30->unk1C -= 0.033333335f;
            if (temp_r30->unk1C < 0) {
                temp_r30->unk1C = 0;
            }
            Hu3DModelTPLvlSet(object->unk10, temp_r30->unk1C);
        }
    }
    if (temp_r30->unk10 == 0) {
        if (object->unk10) {
            Hu3DModelAttrSet(object->unk10, 1);
        }
        fn_2_10980(temp_r30->unk12);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fn_2_118B0(omObjData *object)
{
    UnkWork10A88 *temp_r30;
    s32 temp_r29;

    temp_r30 = object->data;
    temp_r30->unk0.z += (lbl_2_bss_50 * 0.5f);
    object->trans.x = temp_r30->unk0.x;
    object->trans.y = temp_r30->unk0.y;
    object->trans.z = lbl_2_bss_60.z + temp_r30->unk0.z;
    for (temp_r29 = 1; temp_r29 < 3; temp_r29++) {
        Hu3DModelPosSet(object->model[temp_r29], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->unk10 != 0) {
        Hu3DModelPosSet(object->unk10, object->trans.x, object->trans.y, object->trans.z);
        temp_r30->unk1C -= 0.033333335f;
        if (temp_r30->unk1C < 0) {
            temp_r30->unk1C = 0;
        }
        Hu3DModelTPLvlSet(object->unk10, temp_r30->unk1C);
    }

    if (temp_r30->unk10 == 0) {
        if (object->unk10) {
            Hu3DModelAttrSet(object->unk10, 1);
        }
        fn_2_10980(temp_r30->unk12);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fn_2_11A68(omObjData *object)
{
    s32 temp_r30;
    UnkWork10A88 *temp_r29;
    UnkWork10A88 *sp8;
    temp_r29 = object->data;
    sp8 = temp_r29->unkC->data;
    omSetTra(object, 0, 0, 0);
    for (temp_r30 = 1; temp_r30 < 3; temp_r30++) {
        Hu3DModelPosSet(object->model[temp_r30], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->work[0] == 1) {
        fn_2_10980(temp_r29->unk12);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fn_2_11B78(omObjData *object)
{
    UnkWork10A88 *temp_r29;
    temp_r29 = object->data;
    if (object->work[0] == 1) {
        fn_2_10980(temp_r29->unk12);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fn_2_11C30(omObjData *object)
{
    s32 temp_r30;
    UnkWork10A88 *temp_r29;
    UnkWork10A88 *sp8;
    temp_r29 = object->data;
    sp8 = temp_r29->unkC->data;
    omSetTra(object, 0, 0, 0);
    for (temp_r30 = 1; temp_r30 < 3; temp_r30++) {
        Hu3DModelPosSet(object->model[temp_r30], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->work[1] == 1) {
        fn_2_10980(temp_r29->unk12);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fn_2_11D40(omObjData *object)
{
    s32 temp_r30;
    UnkWork10A88 *temp_r29;
    UnkWork10A88 *sp8;
    temp_r29 = object->data;
    sp8 = temp_r29->unkC->data;
    omSetTra(object, temp_r29->unkC->trans.x, temp_r29->unkC->trans.y, temp_r29->unkC->trans.z);
    for (temp_r30 = 1; temp_r30 < 3; temp_r30++) {
        Hu3DModelPosSet(object->model[temp_r30], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->work[1] == 1) {
        fn_2_10980(temp_r29->unk12);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fn_2_11E44(omObjData *object)
{
    UnkWork10A88 *temp_r29;
    temp_r29 = object->data;
    if (object->work[0] == 1) {
        fn_2_10980(temp_r29->unk12);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fn_2_11EFC(omObjData *object)
{
    UnkWork10A88 *temp_r29;
    temp_r29 = object->data;
    if (object->work[0] == 1) {
        fn_2_10980(temp_r29->unk12);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fn_2_11FB4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    UnkWork10A88 *temp_r28;
    s32 temp_r27;
    temp_r28 = ((omObjData *)(particle->unk_1C))->data;
    if (particle->unk_34 == 0) {
        temp_r31 = particle->unk_48;
        temp_f29 = 360.0f / (particle->unk_30 / 2);
        temp_f31 = particle->unk_00;
        for (temp_r29 = 0; temp_r29 < particle->unk_30 / 2; temp_r29++, temp_r31++) {
            temp_f30 = (0.1f * (rand8() % 50)) + 50;
            temp_r31->unk2C = (0.1f * (rand8() % 41)) + 8.0f;
            temp_r31->unk08.x = temp_f31;
            temp_r31->unk08.y = temp_f30;
            temp_r31->unk08.z = 0;
            temp_r31->unk14.x = (10.0f / 255.0f) * ((u8)frand());
            temp_r31->unk40.a = 180;
            temp_f31 += temp_f29;
            temp_r31->unk34.z = 0;
        }
        for (temp_r29 = 0; temp_r29 < particle->unk_30 / 2; temp_r29++, temp_r31++) {
            temp_r31->unk2C = 0;
            temp_r31->unk40.a = 0;
        }
    }
    temp_r31 = particle->unk_48;
    temp_r27 = 0;
    for (temp_r29 = 0; temp_r29 < particle->unk_30 / 2; temp_r29++, temp_r31++) {
        if (temp_r31->unk40.a != 0) {
            temp_r27++;
            temp_f30 = (6.0 * sind(temp_r31->unk08.z)) + temp_r31->unk08.y;
            temp_r31->unk34.x = temp_f30 * cosd(temp_r31->unk08.x);
            temp_r31->unk34.y = temp_f30 * sind(temp_r31->unk08.x);
            temp_r31->unk08.z += temp_r31->unk14.x;
            if (temp_r31->unk08.z >= 360.0f) {
                temp_r31->unk08.z -= 360.0f;
            }
            temp_f31 = temp_r31->unk40.a;
            if (temp_r28->unk14) {
                temp_f31 -= 3.0f;
                if (temp_f31 < 0.0f) {
                    temp_f31 = 0.0f;
                }
            }
            temp_r31->unk40.a = temp_f31;
        }
    }
    if (!temp_r27) {
        temp_r28->unk10--;
    }
}

void fn_2_123F8(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    UnkWork10A88 *temp_r27;
    if (!particle->unk_02) {
        particle->unk_02 = 1;
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30 / 2; temp_r29++, temp_r31++) {
            temp_r31->unk08.x = temp_r31->unk34.x;
            temp_r31->unk14.x = 0;
            temp_r31->unk14.y = 5.0f + ((35.0f / 255.0f) * ((u8)frand()));
            temp_r31->unk14.z = 8.0f + ((8.0f / 255.0f) * ((u8)frand()));
            temp_r31->unk24 = 3.0f + ((5.0f / 255.0f) * ((u8)frand()));
        }
    }
    temp_r31 = particle->unk_48;
    temp_r28 = 0;
    for (temp_r29 = 0; temp_r29 < particle->unk_30 / 2; temp_r29++, temp_r31++) {
        if (temp_r31->unk40.a != 0) {
            temp_r28++;
            temp_r31->unk34.x = temp_r31->unk08.x + (temp_r31->unk14.z * sind(temp_r31->unk14.x));
            temp_r31->unk14.x += temp_r31->unk14.y;
            if (temp_r31->unk14.x >= 360.0f) {
                temp_r31->unk14.x -= 360.0f;
            }
            temp_r31->unk34.y += temp_r31->unk24;
            temp_f31 = temp_r31->unk40.a;
            temp_f31 -= 3.0f;
            if (temp_f31 < 0.0f) {
                temp_f31 = 0.0f;
            }
            temp_r31->unk40.a = temp_f31;
        }
    }
    if (temp_r28 == 0) {
        UnkWork10A88 *temp_r27 = ((omObjData *)(particle->unk_1C))->data;
        temp_r27->unk10--;
    }
}

// Here exclusively to match fn_2_126C8
static inline void DummyInline(s32 arg0)
{
    s32 temp1, temp2, temp3, temp4, temp5;
    if (arg0 != 0) {
        temp1 = 1;
        temp2 = temp1 * 2;
        temp3 = temp2 * 3;
        temp4 = temp3 * 4;
        temp5 = temp4 * 5;
        temp5 = temp5 / 2;
    }
}

void fn_2_126C8(ModelData *model, ParticleData *particle, Mtx matrix)
{
    DummyInline(0);
}

void fn_2_126F4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    if (particle->unk_34 == 0) {
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk40.a = 0;
            temp_r31->unk2C = 0;
        }
        particle->unk_00 = 0;
    }
    if (particle->unk_00 == 0) {
        for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                if (temp_r31->unk40.a == 0) {
                    break;
                }
            }
            if (temp_r28 == particle->unk_30) {
                continue;
            }
            temp_r31->unk08.x = -50.0f + (0.3921569f * ((u8)frand()));
            temp_r31->unk08.y = 0.058823533f * ((u8)frand());
            temp_r31->unk14.x = (90.0f / 255.0f) * ((u8)frand());
            temp_r31->unk14.y = 5.0f + (0.098039225f * ((u8)frand()));
            temp_r31->unk14.z = (float)(frand() % 10) + 8.0f;
            temp_r31->unk34.z = -5.0f + ((11.0f / 255.0f) * ((u8)frand()));
            temp_r31->unk34.y = (float)(frand() % 31) + -5.0f;
            temp_r31->unk2C = temp_r31->unk08.y + 35.0f;
            temp_r31->unk40.a = 210;
            temp_r31->unk08.y = (0.2 * temp_r31->unk08.y) + 5.0;
            particle->unk_00 = (frand() % 10) + 10;
        }
    }
    else {
        particle->unk_00--;
    }
    temp_r31 = particle->unk_48;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk40.a == 0) {
            continue;
        }
        temp_r31->unk34.x = (temp_r31->unk14.z * sind(temp_r31->unk14.x)) + temp_r31->unk08.x;
        temp_r31->unk14.x += temp_r31->unk14.y;
        if (temp_r31->unk14.x >= 360.0f) {
            temp_r31->unk14.x -= 360.0f;
        }
        temp_r31->unk34.y += temp_r31->unk08.y;
        temp_r31->unk40.a--;
    }
}

void fn_2_12B30(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    M401WorkPlayer *temp_r28;
    omObjData *temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    UnkWork10A88 *temp_r24;
    temp_r27 = particle->unk_1C;
    temp_r24 = ((omObjData *)(particle->unk_1C))->data;
    temp_r28 = temp_r24->unkC->data;
    if (particle->unk_34 == 0) {
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk40.a = 0;
            temp_r31->unk2C = 0;
            temp_r31->unk20 = 0;
        }
        particle->unk_00 = 0;
    }
    if (particle->unk_00 == 0 && temp_r27->work[0] == 0) {
        for (temp_r29 = 0; temp_r29 < 10; temp_r29++) {
            temp_r31 = particle->unk_48;
            for (temp_r26 = 0; temp_r26 < particle->unk_30; temp_r26++, temp_r31++) {
                if (temp_r31->unk20 == 0) {
                    break;
                }
            }
            if (temp_r26 == particle->unk_30) {
                continue;
            }
            temp_r31->unk08.x = (((40.0f / 255.0f) * ((u8)frand())) + (temp_r28->unk18.x - 20.0f));
            temp_r31->unk08.y = (frand() % 5) + 3;
            temp_r31->unk14.x = ((90.0f / 255.0f) * ((u8)frand()));
            temp_r31->unk14.y = 5.0f + ((45.0f / 255.0f) * ((u8)frand()));
            temp_r31->unk14.z = 2.0f + (0.011764707f * ((u8)frand()));
            temp_r31->unk40.a = 180;
            temp_r31->unk34.z = ((0.121568635f * ((u8)frand())) + (temp_r28->unk18.z + 70.0f));
            temp_r31->unk34.y = ((0.20000002f * ((u8)frand())) + (temp_r28->unk18.y - 25.0f));
            particle->unk_00 = (frand() % 6) + 5;
            temp_r31->unk20 = 1;
            temp_r31->unk2C = 11;
        }
    }
    else {
        particle->unk_00--;
    }
    temp_r31 = particle->unk_48;
    temp_r25 = 0;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk40.a != 0) {
            float temp_f31;
            temp_r31->unk34.x = (temp_r31->unk14.z * sind(temp_r31->unk14.x)) + temp_r31->unk08.x;
            temp_r31->unk14.x += temp_r31->unk14.y;
            if (temp_r31->unk14.x >= 360.0f) {
                temp_r31->unk14.x -= 360.0f;
            }
            temp_r31->unk34.y += 3.0f;
            temp_f31 = temp_r31->unk40.a;
            temp_f31 -= temp_r31->unk08.y;
            if (temp_f31 < 0.0f) {
                temp_f31 = 0.0f;
                temp_r31->unk20 = 0;
            }

            temp_r31->unk40.a = temp_f31;
            temp_r25++;
        }
    }
    if (temp_r25 == 0 && temp_r27->work[0] == 1) {
        temp_r27->work[1] = 1;
    }
}

void fn_2_1301C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    M401WorkPlayer *temp_r28;
    omObjData *temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    UnkWork10A88 *temp_r24;
    temp_r27 = particle->unk_1C;
    temp_r24 = (temp_r27)->data;
    temp_r28 = temp_r24->unkC->data;
    if (particle->unk_34 == 0) {
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk40.a = 0;
            temp_r31->unk2C = 0;
            temp_r31->unk20 = 0;
        }
        particle->unk_00 = 0;
    }
    if (particle->unk_00 == 0 && temp_r27->work[0] == 0) {
        for (temp_r29 = 0; temp_r29 < 10; temp_r29++) {
            temp_r31 = particle->unk_48;
            for (temp_r26 = 0; temp_r26 < particle->unk_30; temp_r26++, temp_r31++) {
                if (temp_r31->unk20 == 0) {
                    break;
                }
            }
            if (temp_r26 == particle->unk_30) {
                continue;
            }
            temp_r31->unk08.x = (((80.0f / 255.0f) * ((u8)frand())) + (-40.0f));
            temp_r31->unk08.y = (frand() % 10) + 7;
            temp_r31->unk14.x = ((90.0f / 255.0f) * ((u8)frand()));
            temp_r31->unk14.y = 5.0f + ((45.0f / 255.0f) * ((u8)frand()));
            temp_r31->unk14.z = 2.0f + (frand() % 3);
            temp_r31->unk40.a = 180;
            temp_r31->unk34.z = ((0.121568635f * ((u8)frand())) + (85.0f));
            temp_r31->unk34.y = ((0.2392157f * ((u8)frand())) + (-30.0f));
            particle->unk_00 = (frand() % 3) + 3;
            temp_r31->unk20 = 1;
            temp_r31->unk2C = 11;
        }
    }
    else {
        particle->unk_00--;
    }
    temp_r31 = particle->unk_48;
    temp_r25 = 0;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk40.a != 0) {
            float temp_f31;
            temp_r31->unk34.x = (temp_r31->unk14.z * sind(temp_r31->unk14.x)) + temp_r31->unk08.x;
            temp_r31->unk14.x += temp_r31->unk14.y;
            if (temp_r31->unk14.x >= 360.0f) {
                temp_r31->unk14.x -= 360.0f;
            }
            temp_r31->unk34.y += 3.0f;
            temp_r31->unk34.z -= 1.0f;
            temp_f31 = temp_r31->unk40.a;
            temp_f31 -= temp_r31->unk08.y;
            if (temp_f31 < 0.0f) {
                temp_f31 = 0.0f;
                temp_r31->unk20 = 0;
            }

            temp_r31->unk40.a = temp_f31;
            temp_r25++;
        }
    }
    if (temp_r25 == 0 && temp_r27->work[0] == 1) {
        temp_r27->work[1] = 1;
    }
}

void fn_2_1350C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    if (particle->unk_34 == 0) {
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk2C = 0;
        }
        particle->unk_1C = (void *)1;
        particle->unk_02 = 0;
        particle->unk_00 = 0;
    }
    if (particle->unk_00 == 0) {
        for (temp_r29 = 0; temp_r29 < 16; temp_r29++) {
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                if (temp_r31->unk2C == 0) {
                    break;
                }
            }
            if (temp_r28 == particle->unk_30) {
                continue;
            }
            temp_f30 = (360.0f / 255.0f) * ((u8)frand());
            temp_r31->unk20 = 45 * sind(temp_f30);
            temp_r31->unk28 = 45 * cosd(temp_f30);
            temp_r31->unk24 = 0;
            temp_f28 = 0.098039225f * ((u8)frand()) + 50.0f;
            temp_f29 = (2.0f / 255.0f) * ((u8)frand()) + 2.5f;
            temp_r31->unk08.x = temp_f29 * sind(temp_f30) * cosd(temp_f28);
            temp_r31->unk08.y = 0.8f * (temp_f29 * sind(temp_f28));
            temp_r31->unk08.z = temp_f29 * cosd(temp_f30) * cosd(temp_f28);
            temp_r31->unk14.x = 1;
            temp_r31->unk14.y = 255;
            temp_r31->unk2C = (4.0f / 255.0f) * ((u8)frand()) + 3.0f;
            temp_r31->unk40.r = (155.0f / 255.0f) * ((u8)frand()) + 100.0f;
            temp_r31->unk40.g = 0.21568629f * ((u8)frand()) + 200.0f;
            temp_r31->unk40.b = 255;
            temp_r31->unk40.a = temp_r31->unk14.y;
        }
        particle->unk_00 = 0.058823533f * ((u8)frand()) + 30.0f;
    }
    else {
        particle->unk_00--;
    }
    temp_r31 = particle->unk_48;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk2C != 0) {
            temp_f31 = temp_r31->unk14.x;
            temp_r31->unk34.x = (temp_r31->unk08.x * temp_f31) + temp_r31->unk20;
            temp_r31->unk34.z = (temp_r31->unk08.z * temp_f31) + temp_r31->unk28;
            temp_r31->unk34.y = ((temp_r31->unk08.y * temp_f31) + temp_r31->unk24) - (0.2 * temp_f31 * temp_f31);
            temp_r31->unk14.y -= 3.5f;
            temp_r31->unk40.a = temp_r31->unk14.y;
            if (temp_r31->unk2C < 0 || temp_r31->unk14.y < 10.0f || temp_r31->unk34.y <= 0.0f) {
                temp_r31->unk2C = 0;
                particle->unk_02++;
            }

            temp_r31->unk14.x += 0.7f;
        }
    }
}

void fn_2_13B7C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    if (particle->unk_34 == 0) {
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk2C = 0;
        }
        particle->unk_1C = (void *)1;
        particle->unk_02 = 0;
        particle->unk_00 = 0;
    }
    if (particle->unk_1C) {
        for (temp_r29 = 0; temp_r29 < 20; temp_r29++) {
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                if (temp_r31->unk2C == 0) {
                    break;
                }
            }
            if (temp_r28 != particle->unk_30) {
                temp_f30 = (360.0f / 255.0f) * ((u8)frand());
                temp_r31->unk20 = 40 * sind(temp_f30);
                temp_r31->unk28 = 40 * cosd(temp_f30);
                temp_r31->unk24 = 0;
                temp_f28 = (20.0f / 255.0f) * ((u8)frand()) + 70.0f;
                temp_f29 = (4.0f / 255.0f) * ((u8)frand()) + 5.0f;
                temp_r31->unk08.x = temp_f29 * sind(temp_f30) * cosd(temp_f28);
                temp_r31->unk08.y = temp_f29 * sind(temp_f28);
                temp_r31->unk08.z = temp_f29 * cosd(temp_f30) * cosd(temp_f28);
                temp_r31->unk14.x = 1;
                temp_r31->unk14.y = 255;
                temp_r31->unk2C = (4.0f / 255.0f) * ((u8)frand()) + 5.0f;
                temp_r31->unk40.r = (155.0f / 255.0f) * ((u8)frand()) + 100.0f;
                temp_r31->unk40.g = 0.21568629f * ((u8)frand()) + 200.0f;
                temp_r31->unk40.b = 255;
                temp_r31->unk40.a = temp_r31->unk14.y;
            }
            else {
                particle->unk_1C = NULL;
                break;
            }
        }
    }
    temp_r31 = particle->unk_48;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk2C != 0) {
            temp_f31 = temp_r31->unk14.x;
            temp_r31->unk34.x = (temp_r31->unk08.x * temp_f31) + temp_r31->unk20;
            temp_r31->unk34.z = (temp_r31->unk08.z * temp_f31) + temp_r31->unk28;
            temp_r31->unk34.y = ((temp_r31->unk08.y * temp_f31) + temp_r31->unk24) - (0.2 * temp_f31 * temp_f31);
            temp_r31->unk14.y -= 3.5f;
            temp_r31->unk40.a = temp_r31->unk14.y;
            if (temp_r31->unk2C < 0 || temp_r31->unk14.y < 10.0f || temp_r31->unk34.y <= 0.0f) {
                temp_r31->unk2C = 0;
                particle->unk_02++;
            }
            temp_r31->unk14.x += 1.0f;
        }
    }
    if (particle->unk_02 >= particle->unk_30 && particle->unk_1C == NULL) {
        particle->unk_00 = 1;
    }
}

void fn_2_142D0(omObjData *object);
void fn_2_142D4(ModelData *model, ParticleData *particle, Mtx matrix);

omObjData *fn_2_141B0(void)
{
    omObjData *object = omAddObjEx(HuPrcCurrentGet(), 1300, 5, 0, -1, fn_2_142D0);
    ParticleData *particle;
    omSetStatBit(object, 0x100);
    object->model[0] = Hu3DParticleCreate(lbl_2_bss_244, 200);
    Hu3DParticleHookSet(object->model[0], fn_2_142D4);
    Hu3DParticleColSet(object->model[0], 255, 255, 255);
    Hu3DModelPosSet(object->model[0], 0, 0, 0);
    Hu3DParticleAnimModeSet(object->model[0], 0);
    Hu3DModelLayerSet(object->model[0], 1);
    Hu3DParticleBlendModeSet(object->model[0], 1);
    particle = Hu3DData[object->model[0]].unk_120;
    return object;
}

void fn_2_142D0(omObjData *object) { }

void fn_2_142D4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    if (particle->unk_34 == 0) {
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk2C = 0;
            temp_r31->unk34.y = 950;
        }
    }
    if (particle->unk_00 == 0) {
        for (temp_r29 = 0; temp_r29 < 30; temp_r29++) {
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                if (temp_r31->unk2C == 0) {
                    break;
                }
            }
            if (temp_r28 == particle->unk_30) {
                continue;
            }
            temp_r31->unk2C = 1;
            temp_r31->unk40.a = 150;
            temp_r31->unk34.x = ((11.764707f * ((u8)frand())) + (-1500.0f));
            temp_r31->unk34.z = ((6.666667f * ((u8)frand())) + (-2000.0f));
            temp_r31->unk08.x = 0;
            temp_r31->unk08.y = (((5.0f / 255.0f) * ((u8)frand())) + (5.0f));
            temp_r31->unk08.z = ((0.011764707f * ((u8)frand())) + (18.0f));
        }
        particle->unk_00 = (frand() % 5) + 4;
    }
    else {
        particle->unk_00--;
    }
    temp_r31 = particle->unk_48;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk2C != 0) {
            temp_r31->unk34.x += 1.1f;
            temp_r31->unk34.z += 1.1f;
            temp_r31->unk2C = (temp_r31->unk08.z * sind(temp_r31->unk08.x)) + 1.0;
            temp_r31->unk08.x += temp_r31->unk08.y;
            if (temp_r31->unk08.x >= 180.0f) {
                temp_r31->unk2C = 0.0f;
            }
        }
    }
}

void fn_2_14738(omObjData *object);
void fn_2_147B4(ModelData *model, ParticleData *particle, Mtx matrix);

omObjData *fn_2_14640(Process *objman)
{
    omObjData *object;
    object = omAddObjEx(objman, 1300, 1, 0, -1, fn_2_14738);
    object->model[0] = Hu3DParticleCreate(lbl_2_bss_250, 450);
    Hu3DParticleHookSet(object->model[0], fn_2_147B4);
    Hu3DParticleColSet(object->model[0], 255, 255, 255);
    Hu3DModelPosSet(object->model[0], 0, -6000, -21000);
    Hu3DParticleAnimModeSet(object->model[0], 0);
    Hu3DModelLayerSet(object->model[0], 1);
    Hu3DParticleBlendModeSet(object->model[0], 1);
    return object;
}

void fn_2_14738(omObjData *object)
{
    omSetTra(object, lbl_2_bss_6C.x, lbl_2_bss_6C.y, lbl_2_bss_6C.z);
    if (object->work[0] == 1) {
        Hu3DModelAttrSet(object->model[0], 1);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void fn_2_147B4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    if (particle->unk_34 == 0) {
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk40.a = 180;
            temp_r31->unk08.x = ((3.9215689f * ((u8)frand())) + (-500.0f));
            temp_r31->unk08.y = ((3.529412f * ((u8)frand())) + (-500.0f));
            temp_r31->unk08.z = (-300.0f) - ((3.9215689f * ((u8)frand())));
            temp_r31->unk14.x = (360.0f / 255.0f) * ((u8)frand());
            temp_r31->unk14.y = (4.0f / 255.0f) * ((u8)frand());
            temp_r31->unk2C = 2;
        }
        particle->unk_00 = 0;
    }
    if (particle->unk_00 == 0) {
        for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
            temp_r31 = particle->unk_48;
            for (temp_r28 = 0; temp_r28 < particle->unk_30; temp_r28++, temp_r31++) {
                if (temp_r31->unk40.a == 0) {
                    break;
                }
            }
            if (temp_r28 == particle->unk_30) {
                continue;
            }
            temp_r31->unk40.a = 180;
            temp_r31->unk08.x = -50.0f + (0.3921569f * ((u8)frand()));
            temp_r31->unk08.y = 0.058823533f * ((u8)frand());
            temp_r31->unk14.x = (90.0f / 255.0f) * ((u8)frand());
            temp_r31->unk14.y = 5.0f + (0.098039225f * ((u8)frand()));
            temp_r31->unk14.z = (float)(frand() % 10) + 8.0f;
            temp_r31->unk34.z = -5.0f + ((11.0f / 255.0f) * ((u8)frand()));
            temp_r31->unk34.y = (float)(frand() % 31) + -5.0f;
            temp_r31->unk2C = temp_r31->unk08.y + 35.0f;
            temp_r31->unk40.a = 210;
            temp_r31->unk08.y = (0.2 * temp_r31->unk08.y) + 5.0;
            particle->unk_00 = (frand() % 10) + 10;
        }
    }
    else {
        particle->unk_00--;
    }
    temp_r31 = particle->unk_48;
    temp_f30 = lbl_2_bss_50 * 0.3f;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk40.a == 0) {
            continue;
        }
        temp_r31->unk34.x = temp_r31->unk08.x;
        temp_r31->unk34.y = temp_r31->unk08.y;
        temp_r31->unk34.z = temp_r31->unk08.z;
        temp_r31->unk08.x -= 0.5 * sind(temp_r31->unk14.x);
        temp_r31->unk08.z -= -temp_f30;
        temp_r31->unk14.x += temp_r31->unk14.y;
        if (temp_r31->unk14.x >= 360.0f) {
            temp_r31->unk14.x -= 360.0f;
        }
        if (temp_r31->unk08.z >= 0.0f) {
            temp_f31 = 800.0f + ((300.0f / 255.0f) * ((u8)frand()));
            temp_r31->unk08.z -= temp_f31;
        }
    }
}
