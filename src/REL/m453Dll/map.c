#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/sprite.h"
#include "math.h"
#include "string.h"

#include "REL/m453Dll.h"

typedef struct M453MapUnkStruct {
    struct {
        u8 unk_00_field0 : 1;
    };
    s32 unk_04;
    float unk_08;
    s32 unk_0C[6];
    s32 unk_24[0xC];
} M453MapUnkStruct; /* size = 0x54 */

void fn_1_6768(omObjData *object);
void fn_1_67EC(omObjData *object);
void fn_1_67F0(omObjData *object);
void fn_1_695C(omObjData *object);
void fn_1_6C74(omObjData *object);
void fn_1_6EB4(omObjData *object);
void fn_1_6FC4(omObjData *object);
void fn_1_73C4(omObjData *object);
void fn_1_7978(void);
void fn_1_7A74(s16 arg0);

Vec lbl_1_data_158[0x10] = {
    { 92.39f, 0.0f, 38.27f },
    { 100.0f, 0.0f, 0.0f },
    { 92.39f, 0.0f, -38.27f },
    { 70.71f, 0.0f, -70.71f },
    { 38.27f, 0.0f, -92.39f },
    { 0.0f, 0.0f, -100.0f },
    { -38.27f, 0.0f, -92.39f },
    { -70.71f, 0.0f, -70.71f },
    { -92.39f, 0.0f, -38.27f },
    { -100.0f, 0.0f, 0.0f },
    { -92.39f, 0.0f, 38.27f },
    { -70.71f, 0.0f, 70.71f },
    { -38.27f, 0.0f, 92.39f },
    { 0.0f, 0.0f, 100.0f },
    { 38.27f, 0.0f, 92.39f },
    { 70.71f, 0.0f, 70.71f },
};

Vec lbl_1_data_218[0x10] = {
    { 55.43f, 0.0f, 22.96f },
    { 60.0f, 0.0f, 0.0f },
    { 55.43f, 0.0f, -22.96f },
    { 42.43f, 0.0f, -42.43f },
    { 22.96f, 0.0f, -55.43f },
    { 0.0f, 0.0f, -60.0f },
    { -22.96f, 0.0f, -55.43f },
    { -42.43f, 0.0f, -42.43f },
    { -55.43f, 0.0f, -22.96f },
    { -60.0f, 0.0f, 0.0f },
    { -55.43f, 0.0f, 22.96f },
    { -42.43f, 0.0f, 42.43f },
    { -22.96f, 0.0f, 55.43f },
    { 0.0f, 0.0f, 60.0f },
    { 22.96f, 0.0f, 55.43f },
    { 42.43f, 0.0f, 42.43f },
};

Vec lbl_1_data_2D8[0xA] = {
    { 38.79f, 0.0f, -53.4f },
    { 0.0f, 0.0f, -120.0f },
    { -38.79f, 0.0f, -53.4f },
    { -114.13f, 0.0f, -37.08f },
    { -62.77f, 0.0f, 20.4f },
    { -70.53f, 0.0f, 97.08f },
    { 0.0f, 0.0f, 66.0f },
    { 70.53f, 0.0f, 97.08f },
    { 62.77f, 0.0f, 20.4f },
    { 114.13f, 0.0f, -37.08f },
};

Vec lbl_1_data_350[0xA] = {
    { 21.34f, 0.0f, -29.37f },
    { 0.0f, 0.0f, -66.0f },
    { -21.34f, 0.0f, -29.37f },
    { -62.77f, 0.0f, -20.4f },
    { -34.52f, 0.0f, 11.22f },
    { -38.79f, 0.0f, 53.4f },
    { 0.0f, 0.0f, 36.3f },
    { 38.79f, 0.0f, 53.4f },
    { 34.52f, 0.0f, 11.22f },
    { 62.77f, 0.0f, -20.4f },
};

Vec lbl_1_data_3C8[0x10] = {
    { 110.87f, 0.0f, 45.92f },
    { 120.0f, 0.0f, 0.0f },
    { 110.87f, 0.0f, -45.92f },
    { 84.85f, 0.0f, -84.85f },
    { 45.92f, 0.0f, -110.87f },
    { 0.0f, 0.0f, -120.0f },
    { -45.92f, 0.0f, -110.87f },
    { -84.85f, 0.0f, -84.85f },
    { -110.87f, 0.0f, -45.92f },
    { -120.0f, 0.0f, 0.0f },
    { -110.87f, 0.0f, 45.92f },
    { -84.85f, 0.0f, 84.85f },
    { -45.92f, 0.0f, 110.87f },
    { 0.0f, 0.0f, 120.0f },
    { 45.92f, 0.0f, 110.87f },
    { 84.85f, 0.0f, 84.85f },
};

Vec lbl_1_data_488[0x10] = {
    { 73.17f, 0.0f, 30.31f },
    { 79.2f, 0.0f, 0.0f },
    { 73.17f, 0.0f, -30.31f },
    { 56.0f, 0.0f, -56.0f },
    { 30.31f, 0.0f, -73.17f },
    { 0.0f, 0.0f, -79.2f },
    { -30.31f, 0.0f, -73.17f },
    { -56.0f, 0.0f, -56.0f },
    { -73.17f, 0.0f, -30.31f },
    { -79.2f, 0.0f, 0.0f },
    { -73.17f, 0.0f, 30.31f },
    { -56.0f, 0.0f, 56.0f },
    { -30.31f, 0.0f, 73.17f },
    { 0.0f, 0.0f, 79.2f },
    { 30.31f, 0.0f, 73.17f },
    { 56.0f, 0.0f, 56.0f },
};

Vec lbl_1_data_548[0xA] = {
    { 48.49f, 0.0f, -66.74f },
    { 0.0f, 0.0f, -150.0f },
    { -48.49f, 0.0f, -66.74f },
    { -142.66f, 0.0f, -46.35f },
    { -78.46f, 0.0f, 25.49f },
    { -88.17f, 0.0f, 121.35f },
    { 0.0f, 0.0f, 82.5f },
    { 88.17f, 0.0f, 121.35f },
    { 78.46f, 0.0f, 25.49f },
    { 142.66f, 0.0f, -46.35f },
};

Vec lbl_1_data_5C0[0xA] = {
    { 29.09f, 0.0f, -40.05f },
    { 0.0f, 0.0f, -90.0f },
    { -29.09f, 0.0f, -40.05f },
    { -85.59f, 0.0f, -27.81f },
    { -47.08f, 0.0f, 15.3f },
    { -52.9f, 0.0f, 72.81f },
    { 0.0f, 0.0f, 49.5f },
    { 52.9f, 0.0f, 72.81f },
    { 47.08f, 0.0f, 15.3f },
    { 85.59f, 0.0f, -27.81f },
};

Vec lbl_1_data_638[0x16] = {
    { 129.1f, 0.0f, 54.6f },
    { 140.0f, 0.0f, 0.0f },
    { 129.3f, 0.0f, -53.6f },
    { 99.0f, 0.0f, -99.0f },
    { 53.6f, 0.0f, -129.3f },
    { 0.0f, 0.0f, -140.0f },
    { -53.6f, 0.0f, -129.3f },
    { -99.0f, 0.0f, -99.0f },
    { -129.4f, 0.0f, -53.5f },
    { -140.0f, 0.0f, 0.0f },
    { -136.0f, 0.0f, 20.4f },
    { -102.1f, 0.0f, -7.6f },
    { -70.0f, 0.0f, -14.0f },
    { -37.8f, 0.0f, -7.6f },
    { -10.6f, 0.0f, 10.6f },
    { 7.6f, 0.0f, 37.8f },
    { 14.0f, 0.0f, 70.0f },
    { 7.6f, 0.0f, 102.2f },
    { -20.4f, 0.0f, 136.0f },
    { 0.1f, 0.0f, 140.1f },
    { 53.9f, 0.0f, 129.5f },
    { 99.5f, 0.0f, 99.0f },
};

Vec lbl_1_data_740[0x16] = {
    { 95.9f, 0.0f, 42.9f },
    { 106.6f, 0.0f, 0.4f },
    { 98.4f, 0.0f, -37.2f },
    { 81.7f, 0.0f, -65.9f },
    { 55.4f, 0.0f, -89.6f },
    { 11.5f, 0.0f, -101.7f },
    { -24.5f, 0.0f, -99.9f },
    { -60.9f, 0.0f, -88.6f },
    { -98.7f, 0.0f, -64.4f },
    { -110.4f, 0.0f, -41.5f },
    { -110.4f, 0.0f, -30.8f },
    { -90.4f, 0.0f, -42.3f },
    { -53.8f, 0.0f, -48.5f },
    { -14.6f, 0.0f, -40.5f },
    { 17.1f, 0.0f, -16.3f },
    { 35.8f, 0.0f, 28.2f },
    { 35.8f, 0.0f, 65.6f },
    { 24.7f, 0.0f, 101.6f },
    { 19.6f, 0.0f, 114.6f },
    { 34.9f, 0.0f, 114.5f },
    { 62.9f, 0.0f, 99.0f },
    { 83.0f, 0.0f, 73.2f },
};

Vec lbl_1_data_848[0x16] = {
    { 110.9f, 0.0f, 45.9f },
    { 120.0f, 0.0f, 0.0f },
    { 110.9f, 0.0f, -45.8f },
    { 84.8f, 0.0f, -84.9f },
    { 45.9f, 0.0f, -110.9f },
    { 0.0f, 0.0f, -120.0f },
    { -45.9f, 0.0f, -110.9f },
    { -84.9f, 0.0f, -84.8f },
    { -110.9f, 0.0f, -45.9f },
    { -120.0f, 0.0f, 0.0f },
    { -116.5f, 0.0f, 17.5f },
    { -87.6f, 0.0f, -6.6f },
    { -60.0f, 0.0f, -12.0f },
    { -32.4f, 0.0f, -6.5f },
    { -9.1f, 0.0f, 9.1f },
    { 6.5f, 0.0f, 32.5f },
    { 12.0f, 0.0f, 60.0f },
    { 6.5f, 0.0f, 87.6f },
    { -17.5f, 0.0f, 116.5f },
    { 0.0f, 0.0f, 120.0f },
    { 45.9f, 0.0f, 110.9f },
    { 84.8f, 0.0f, 84.9f },
};

Vec lbl_1_data_950[0x16] = {
    { 80.0f, 0.0f, 31.0f },
    { 83.9f, 0.0f, -0.1f },
    { 77.2f, 0.0f, -31.7f },
    { 60.4f, 0.0f, -56.8f },
    { 35.6f, 0.0f, -77.4f },
    { -0.5f, 0.0f, -84.1f },
    { -31.5f, 0.0f, -82.9f },
    { -58.9f, 0.0f, -71.4f },
    { -86.3f, 0.0f, -49.4f },
    { -91.5f, 0.0f, -36.4f },
    { -91.5f, 0.0f, -27.3f },
    { -82.1f, 0.0f, -29.8f },
    { -54.7f, 0.0f, -36.2f },
    { -21.9f, 0.0f, -30.9f },
    { 13.3f, 0.0f, -10.2f },
    { 28.3f, 0.0f, 18.3f },
    { 33.4f, 0.0f, 58.4f },
    { 28.0f, 0.0f, 81.6f },
    { 20.7f, 0.0f, 93.3f },
    { 30.4f, 0.0f, 93.3f },
    { 55.4f, 0.0f, 82.2f },
    { 70.4f, 0.0f, 59.3f },
};

s32 lbl_1_data_A58[0xC] = {
    0x220004,
    0x220005,
    0x220006,
    0x220009,
    0x22000C,
    0x22000F,
    0x220007,
    0x220008,
    0x22000A,
    0x22000B,
    0x22000D,
    0x22000E,
};

Vec lbl_1_data_A88[6] = {
    { -400.0f, 0.0f, 300.0f },
    { 0.0f, 0.0f, 300.0f },
    { 400.0f, 0.0f, 300.0f },
    { -400.0f, 0.0f, 700.0f },
    { 0.0f, 0.0f, 700.0f },
    { 400.0f, 0.0f, 700.0f },
};

s32 lbl_1_data_AD0[3] = { 6, 8, 0xA };

s32 lbl_1_data_ADC[3] = { 7, 9, 0xB };

s32 lbl_1_data_AE8[5] = { 1, 2, 3, 4, 5 };

Vec *lbl_1_data_AFC[6] = {
    lbl_1_data_3C8,
    lbl_1_data_158,
    lbl_1_data_548,
    lbl_1_data_2D8,
    lbl_1_data_638,
    lbl_1_data_848,
};

s32 lbl_1_data_B14[6] = { 0x10, 0x10, 0xA, 0xA, 0x16, 0x16 };

Vec lbl_1_data_B2C[6] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, -20.0f },
    { 0.0f, 0.0f, -20.0f },
    { 40.0f, 0.0f, -20.0f },
    { 40.0f, 0.0f, -20.0f },
};

Vec *lbl_1_data_B74[6][2] = {
    { lbl_1_data_3C8, lbl_1_data_488 },
    { lbl_1_data_158, lbl_1_data_218 },
    { lbl_1_data_548, lbl_1_data_5C0 },
    { lbl_1_data_2D8, lbl_1_data_350 },
    { lbl_1_data_638, lbl_1_data_740 },
    { lbl_1_data_848, lbl_1_data_950 },
};

s32 lbl_1_data_BA4[6] = { 0x10, 0x10, 0xA, 0xA, 0x16, 0x16 };

omObjData *lbl_1_bss_BC;
omObjData *lbl_1_bss_B8;
omObjData *lbl_1_bss_A4[5];
s32 lbl_1_bss_A0;
s32 lbl_1_bss_9C;
s32 lbl_1_bss_98;
s32 lbl_1_bss_94;
s32 lbl_1_bss_90;
s32 lbl_1_bss_8C;
float lbl_1_bss_88;
s32 lbl_1_bss_84;
s32 lbl_1_bss_80;
s32 lbl_1_bss_7C;
s32 lbl_1_bss_78;
s32 lbl_1_bss_60[6];

void fn_1_64E8(Process *process)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 var_r31;

    sp20.x = 0.0f;
    sp20.y = 3000.0f;
    sp20.z = 50.0f;
    sp14.x = 0.0f;
    sp14.y = 1.0f;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    lbl_1_bss_BC = omAddObjEx(process, 0xA, 2, 0, -1, fn_1_6768);
    lbl_1_bss_B8 = omAddObjEx(process, 0xC, 4, 0, -1, fn_1_67F0);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_A4[var_r31] = omAddObjEx(process, 0xE, 7, 0, -1, fn_1_6C74);
    }
    Hu3DShadowCreate(30.0f, 20.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.65f);
    Hu3DShadowPosSet(&sp20, &sp14, &sp8);
    lbl_1_bss_A0 = 0;
    lbl_1_bss_9C = lbl_1_bss_98 = 2;
    lbl_1_bss_8C = 0;
    lbl_1_bss_90 = 0;
    lbl_1_bss_88 = 0.75f;
    lbl_1_bss_7C = 3;
    lbl_1_bss_78 = 0;
    lbl_1_bss_84 = 0;
    lbl_1_bss_80 = 0;
    memset(lbl_1_bss_60, 0, 0x18);
}

void fn_1_6748(void)
{
    fn_1_7978();
}

void fn_1_6768(omObjData *object)
{
    object->stat |= 0x100;
    object->model[0] = Hu3DModelCreateFile(0x220010);
    object->model[1] = Hu3DModelCreateFile(0x220011);
    object->func = fn_1_67EC;
}

void fn_1_67EC(omObjData *object) { }

void fn_1_67F0(omObjData *object)
{
    object->stat |= 0x100;
    object->model[0] = Hu3DModelCreateFile(0x220000);
    object->model[1] = Hu3DModelCreateFile(0x220003);
    object->model[2] = Hu3DModelCreateFile(0x220001);
    object->model[3] = Hu3DModelCreateFile(0x220002);
    Hu3DMotionSpeedSet(object->model[2], 0.0f);
    Hu3DModelShadowSet(object->model[1]);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, -500.0f);
    Hu3DData[object->model[3]].unk_94 = 0.0f;
    Hu3DData[object->model[3]].unk_98 = 2.0f;
    object->work[3] = 0x1E;
    object->func = fn_1_695C;
}

void fn_1_695C(omObjData *object)
{
    ModelData *var_r30;
    M453MapUnkStruct *var_r29;

    if (lbl_1_bss_84 != 0) {
        if (lbl_1_bss_80 == 0) {
            if (object->work[0] < 60.0f) {
                object->work[0] += 1;
                var_r30 = &Hu3DData[object->model[1]];
                var_r30->rot.x = (-120.0f * object->work[0]) / 60.0f;
            }
            else {
                lbl_1_bss_80 ^= 1;
                lbl_1_bss_84 = 0;
            }
        }
        else if (object->work[0] != 0) {
            object->work[0] -= 1;
            var_r30 = &Hu3DData[object->model[1]];
            var_r30->rot.x = (-120.0f * object->work[0]) / 60.0f;
        }
        else {
            lbl_1_bss_80 ^= 1;
            lbl_1_bss_84 = 0;
        }
    }
    var_r29 = lbl_1_bss_A4[lbl_1_bss_9C]->data;
    if (lbl_1_bss_94 != 0) {
        lbl_1_bss_94 = 0;
        lbl_1_bss_90 = 1;
    }
    if (lbl_1_bss_9C != lbl_1_bss_98) {
        lbl_1_bss_90 = 0;
        lbl_1_bss_8C = 0;
    }
    lbl_1_bss_98 = lbl_1_bss_9C;
    if (var_r29->unk_00_field0) {
        lbl_1_bss_9C = (lbl_1_bss_9C + 1) % 5;
        lbl_1_bss_8C = 1;
    }
    if (object->work[3] != 0) {
        if (--object->work[3] == 0) {
            HuAudFXPlay(0x521);
        }
    }
}

void fn_1_6C74(omObjData *object)
{
    s32 var_r31;
    M453MapUnkStruct *var_r29;

    var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M453MapUnkStruct), MEMORY_DEFAULT_NUM);
    object->data = var_r29;
    memset(object->data, 0, 0x54);
    for (var_r31 = 0; var_r31 < 0xC; var_r31++) {
        var_r29->unk_24[var_r31] = -1;
    }
    for (var_r31 = 0; (u32)var_r31 < 0xC; var_r31++) {
        var_r29->unk_24[var_r31] = Hu3DModelCreateFile(lbl_1_data_A58[var_r31]);
        Hu3DModelAttrSet(var_r29->unk_24[var_r31], HU3D_ATTR_DISPOFF);
    }
    object->model[0] = var_r29->unk_24[0];
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    var_r29->unk_00_field0 = 0;
    var_r29->unk_04 = 4 - lbl_1_bss_A0;
    fn_1_6FC4(object);
    object->trans.y = 5.0f;
    object->trans.z = -500.0f;
    switch (var_r29->unk_04) {
        case 0:
        case 1:
            break;
        case 2:
            for (var_r31 = 0; var_r31 < 7; var_r31++) {
                Hu3DModelShadowSet(object->model[var_r31]);
            }
            break;
        case 3:
            for (var_r31 = 0; var_r31 < 7; var_r31++) {
                Hu3DModelShadowMapSet(object->model[var_r31]);
            }
            object->trans.y = 2.5f;
            break;
        case 4:
            for (var_r31 = 0; var_r31 < 7; var_r31++) {
                Hu3DModelShadowMapSet(object->model[var_r31]);
            }
            object->trans.y = 0.0f;
            break;
    }
    fn_1_6EB4(object);
    lbl_1_bss_A0++;
    object->func = fn_1_73C4;
}

void fn_1_6EB4(omObjData *object)
{
    Mtx sp38;
    Mtx sp8;
    s32 var_r30;

    MTXTrans(sp38, object->trans.x, object->trans.y, object->trans.z);
    mtxRot(sp8, object->rot.x, object->rot.y, object->rot.z);
    MTXConcat(sp38, sp8, sp38);
    for (var_r30 = 0; var_r30 < 6; var_r30++) {
        MTXTrans(sp8, lbl_1_data_A88[var_r30].x, lbl_1_data_A88[var_r30].y, lbl_1_data_A88[var_r30].z);
        MTXConcat(sp38, sp8, sp8);
        Hu3DModelPosSet(object->model[var_r30 + 1], sp8[0][3], sp8[1][3], sp8[2][3]);
        Hu3DModelRotSet(object->model[var_r30 + 1], object->rot.x, object->rot.y, object->rot.z);
    }
}

void fn_1_6FC4(omObjData *object)
{
    s32 sp8[6];

    s32 var_r31;
    M453MapUnkStruct *var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    var_r30 = object->data;
    for (var_r31 = 0; var_r31 < 0x64; var_r31++) {
        var_r29 = ((u8)frand() * 3) >> 8;
        var_r28 = ((u8)frand() * 3) >> 8;
        var_r26 = lbl_1_data_AD0[var_r29];
        lbl_1_data_AD0[var_r29] = lbl_1_data_AD0[var_r28];
        lbl_1_data_AD0[var_r28] = var_r26;
        var_r29 = ((u8)frand() * 3) >> 8;
        var_r28 = ((u8)frand() * 3) >> 8;
        var_r26 = lbl_1_data_ADC[var_r29];
        lbl_1_data_ADC[var_r29] = lbl_1_data_ADC[var_r28];
        lbl_1_data_ADC[var_r28] = var_r26;
        var_r29 = ((u8)frand() * 5) >> 8;
        var_r28 = ((u8)frand() * 5) >> 8;
        var_r26 = lbl_1_data_AE8[var_r29];
        lbl_1_data_AE8[var_r29] = lbl_1_data_AE8[var_r28];
        lbl_1_data_AE8[var_r28] = var_r26;
    }
    var_r25 = 0;
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (lbl_1_bss_60[var_r31] < 6) {
            sp8[var_r25++] = var_r31;
        }
    }
    for (var_r31 = 0; var_r31 < 0x64; var_r31++) {
        var_r29 = (var_r25 * (u8)frand()) >> 8;
        var_r28 = (var_r25 * (u8)frand()) >> 8;
        var_r26 = sp8[var_r29];
        sp8[var_r29] = sp8[var_r28];
        sp8[var_r28] = var_r26;
    }
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        var_r30->unk_0C[var_r31] = 0;
    }
    for (var_r31 = 0; var_r31 < lbl_1_bss_78; var_r31++) {
        var_r30->unk_0C[sp8[var_r31]] = lbl_1_data_ADC[var_r31];
    }
    while (var_r31 < lbl_1_bss_7C) {
        var_r30->unk_0C[sp8[var_r31]] = lbl_1_data_AD0[var_r31];
        var_r31++;
    }
    var_r24 = 0;
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (var_r30->unk_0C[var_r31] == 0) {
            var_r30->unk_0C[var_r31] = lbl_1_data_AE8[var_r24++];
        }
    }
    memcpy(lbl_1_bss_60, &var_r30->unk_0C, 0x18);
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (object->model[var_r31 + 1] >= 0) {
            Hu3DModelAttrSet(object->model[var_r31 + 1], HU3D_ATTR_DISPOFF);
        }
    }
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        object->model[var_r31 + 1] = var_r30->unk_24[var_r30->unk_0C[var_r31]];
        Hu3DModelAttrReset(object->model[var_r31 + 1], HU3D_ATTR_DISPOFF);
    }
}

void fn_1_73C4(omObjData *object)
{
    Mtx sp38;
    Mtx sp8;
    M453MapUnkStruct *var_r30;
    s32 var_r29;
    s32 var_r28;
    ModelData *var_r27;

    var_r30 = object->data;
    if (lbl_1_bss_90 == 0) {
        if ((lbl_1_bss_84 != 0) && (var_r30->unk_04 < 3)) {
            var_r27 = &Hu3DData[lbl_1_bss_B8->model[1]];
            object->rot.x = var_r27->rot.x;
            switch (var_r30->unk_04) {
                case 0:
                    object->trans.z = -500.0f + ((2.5f * lbl_1_bss_B8->work[0]) / 60.0f);
                    break;
                case 1:
                    object->trans.z = -500.0f + ((5.0f * lbl_1_bss_B8->work[0]) / 60.0f);
                    break;
                case 2:
                    object->trans.z = -500.0f + ((7.5f * lbl_1_bss_B8->work[0]) / 60.0f);
                    break;
            }
        }
        else {
            return;
        }
    }
    else {
        switch (var_r30->unk_04) {
            case 0:
                if (lbl_1_bss_8C != 0) {
                    object->trans.z = -495.0f;
                    var_r30->unk_04++;
                }
                break;
            case 1:
                if (lbl_1_bss_8C != 0) {
                    object->trans.z = -492.5f;
                    var_r30->unk_00_field0 = 0;
                    var_r30->unk_04++;
                    var_r30->unk_08 = 0.0f;
                    for (var_r29 = 0; var_r29 < 7; var_r29++) {
                        Hu3DModelShadowSet(object->model[var_r29]);
                    }
                }
                break;
            case 2:
                if (lbl_1_bss_8C != 0) {
                    var_r30->unk_04 = var_r30->unk_04 + 1;
                    object->trans.y = 2.5f;
                    for (var_r29 = 0; var_r29 < 7; var_r29++) {
                        Hu3DModelShadowReset(object->model[var_r29]);
                        Hu3DModelShadowMapSet(object->model[var_r29]);
                    }
                }
                else {
                    var_r30->unk_08 = var_r30->unk_08 + lbl_1_bss_88;
                    if (var_r30->unk_08 > 90.0f) {
                        var_r30->unk_00_field0 = 1;
                        var_r30->unk_08 = 90.0f;
                        HuAudFXPlay(0x522);
                    }
                    object->rot.x = -120.0 * cosd(var_r30->unk_08);
                    object->trans.z = -500.0 + (7.5 * cosd(var_r30->unk_08));
                }
                break;
            case 3:
                if (lbl_1_bss_8C != 0) {
                    var_r30->unk_04++;
                    object->trans.y = 0.0f;
                }
                break;
            case 4:
                if (lbl_1_bss_8C != 0) {
                    var_r30->unk_04 = 0;
                    object->trans.y = 5.0f;
                    object->trans.z = -497.5f;
                    object->rot.x = -120.0f;
                    for (var_r29 = 0; var_r29 < 7; var_r29++) {
                        fn_1_7A74(object->model[var_r29]);
                    }
                    fn_1_6FC4(object);
                }
                break;
        }
    }
    MTXTrans(sp8, object->trans.x, object->trans.y, object->trans.z);
    mtxRot(sp38, object->rot.x, object->rot.y, object->rot.z);
    MTXConcat(sp8, sp38, sp8);
    for (var_r28 = 0; var_r28 < 6; var_r28++) {
        MTXTrans(sp38, lbl_1_data_A88[var_r28].x, lbl_1_data_A88[var_r28].y, lbl_1_data_A88[var_r28].z);
        MTXConcat(sp8, sp38, sp38);
        Hu3DModelPosSet(object->model[var_r28 + 1], sp38[0][3], sp38[1][3], sp38[2][3]);
        Hu3DModelRotSet(object->model[var_r28 + 1], object->rot.x, object->rot.y, object->rot.z);
    }
}

void fn_1_7978(void)
{
    s32 var_r31;
    omObjData *var_r30;
    M453MapUnkStruct *var_r29;
    s32 var_r28;

    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        var_r30 = lbl_1_bss_A4[var_r31];
        var_r29 = var_r30->data;
        if (var_r29 != NULL) {
            for (var_r28 = 0; var_r28 < 0xC; var_r28++) {
                if (var_r29->unk_24[var_r28] >= 0) {
                    Hu3DModelKill(var_r29->unk_24[var_r28]);
                }
            }
            HuMemDirectFree(var_r29);
            lbl_1_bss_A4[var_r31]->data = NULL;
        }
        for (var_r31 = 0; var_r31 < var_r30->mdlcnt; var_r31++) {
            var_r30->model[var_r31] = -1;
        }
    }
}

void fn_1_7A74(s16 arg0)
{
    HsfData *var_r31;
    HsfObject *var_r30;
    s16 var_r29;
    HsfObject *var_r28;
    HsfConstData *var_r27;

    var_r31 = Hu3DData[arg0].hsfData;
    for (var_r28 = var_r31->object, var_r29 = 0; var_r29 < var_r31->objectCnt; var_r29++, var_r28++) {
        var_r30 = var_r28;
        if (var_r30->constData) {
            var_r27 = var_r30->constData;
            var_r27->flags &= 0xFFFFFFF7;
        }
    }
}

s32 fn_1_7AFC(float arg8, float arg9)
{
    s32 var_r31;
    s32 var_r30;

    var_r31 = (600.0f + arg8) / 400.0f;
    var_r30 = (400.0f + arg9) / 400.0f;
    if (var_r31 < 0) {
        var_r31 = 0;
    }
    else if (var_r31 > 2) {
        var_r31 = 2;
    }
    if (var_r30 < 0) {
        var_r30 = 0;
    }
    else if (var_r30 > 1) {
        var_r30 = 1;
    }
    return var_r31 + (var_r30 * 3);
}

void fn_1_7BB0(s32 arg0, Vec *arg1)
{
    arg1->x = lbl_1_data_A88[arg0].x;
    arg1->y = lbl_1_data_A88[arg0].y;
    arg1->z = lbl_1_data_A88[arg0].z;
}

s32 fn_1_7BFC(M453MapUnkStruct *arg0, s32 arg1)
{
    return arg0->unk_0C[arg1];
}

void fn_1_7C0C(float arg8)
{
    lbl_1_bss_94 = 1;
    lbl_1_bss_88 = arg8;
}

void fn_1_7C2C(s32 arg0)
{
    lbl_1_bss_7C = arg0;
}

void fn_1_7C3C(void)
{
    float var_f31;
    float var_f30;

    lbl_1_bss_84 = 1;
    if (lbl_1_bss_80 == 0) {
        var_f31 = 1.6666666f;
    }
    else {
        var_f31 = -1.6666666f;
    }
    var_f30 = var_f31;
    Hu3DMotionSpeedSet(lbl_1_bss_B8->model[2], var_f30);
    HuAudFXPlay(0x524);
}

s32 fn_1_7CE0(float arg8, float arg9, Vec *arg0)
{
    Mtx sp4C;
    Mtx sp1C;
    Vec sp10;

    omObjData *var_r31;
    Vec *var_r30;
    s32 var_r28;
    s32 var_r27;
    s32 var_r24;
    s32 var_r23;
    M453MapUnkStruct *var_r22;

    var_r31 = lbl_1_bss_A4[lbl_1_bss_9C];
    var_r22 = var_r31->data;
    var_r27 = fn_1_7AFC(arg8, arg9);
    var_r28 = fn_1_7BFC(var_r22, var_r27);
    if (var_r28 < 6) {
        return 0;
    }
    var_r28 -= 6;
    fn_1_7BB0(var_r27, &sp10);
    sp10 = lbl_1_data_A88[var_r27];
    MTXTrans(sp4C, var_r31->trans.x, var_r31->trans.y, var_r31->trans.z);
    mtxRot(sp1C, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
    MTXConcat(sp4C, sp1C, sp4C);
    MTXTrans(sp1C, sp10.x, sp10.y, sp10.z);
    MTXConcat(sp4C, sp1C, sp4C);
    var_r30 = lbl_1_data_AFC[var_r28];
    var_r23 = lbl_1_data_B14[var_r28];
    for (var_r24 = 0; var_r24 < var_r23; var_r24++) {
        MTXTrans(sp1C, var_r30->x, var_r30->y, var_r30->z);
        MTXConcat(sp4C, sp1C, sp1C);
        arg0->x = sp1C[0][3];
        arg0->y = sp1C[1][3];
        arg0->z = sp1C[2][3];
        arg0++;
        var_r30++;
    }
    return var_r23;
}

float fn_1_7F54(float arg8, float arg9)
{
    float var_f31;

    omObjData *var_r31 = lbl_1_bss_A4[lbl_1_bss_9C];
    float var_f30 = -(arg9 - var_r31->trans.z);
    if (cosd(var_r31->rot.x) <= 0.0) {
        var_f31 = 9999.0f;
    }
    else {
        var_f31 = (var_f30 * sind(var_r31->rot.x)) / cosd(var_r31->rot.x);
        if (var_f31 > 9999.0f) {
            var_f31 = 9999.0f;
        }
    }
    return var_f31;
}

float fn_1_80B0(Vec *arg0, float arg8)
{
    return fn_1_7F54(0.0f, arg0->z - arg8);
}

s32 fn_1_8230(void)
{
    return lbl_1_bss_84;
}

s32 fn_1_8240(void)
{
    return lbl_1_bss_90;
}

s32 fn_1_8250(M453MapUnkStruct *arg0, s32 *arg1)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = 0;
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (arg0->unk_0C[var_r31] >= 6) {
            arg1[var_r30++] = var_r31;
        }
    }
    return var_r30;
}

s32 fn_1_82AC(Vec *arg0)
{
    s32 sp8[6];

    omObjData *var_r31;
    s32 var_r30;
    M453MapUnkStruct *var_r28;
    s32 var_r27;
    s32 var_r24;

    var_r31 = lbl_1_bss_A4[lbl_1_bss_9C];
    var_r28 = var_r31->data;
    var_r24 = fn_1_8250(var_r28, sp8);
    for (var_r30 = 0; var_r30 < var_r24; var_r30++) {
        fn_1_7BB0(sp8[var_r30], arg0);
        var_r27 = fn_1_7BFC(var_r28, sp8[var_r30]) - 6;
        arg0->x += var_r31->trans.x + lbl_1_data_B2C[var_r27].x;
        arg0->y += var_r31->trans.y + lbl_1_data_B2C[var_r27].y;
        arg0->z += var_r31->trans.z + lbl_1_data_B2C[var_r27].z;
        arg0++;
    }
    return var_r24;
}

s32 fn_1_844C(Vec *arg0)
{
    Mtx sp50;
    Mtx sp20;
    s32 sp8[6];

    omObjData *var_r30;
    s32 var_r29;
    M453MapUnkStruct *var_r27;
    s32 var_r26;
    s32 var_r23;

    var_r30 = lbl_1_bss_A4[lbl_1_bss_9C];
    var_r27 = var_r30->data;
    var_r23 = fn_1_8250(var_r27, sp8);
    MTXTrans(sp50, var_r30->trans.x, var_r30->trans.y, var_r30->trans.z);
    mtxRot(sp20, var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
    MTXConcat(sp50, sp20, sp50);
    for (var_r29 = 0; var_r29 < var_r23; var_r29++) {
        fn_1_7BB0(sp8[var_r29], arg0);
        var_r26 = fn_1_7BFC(var_r27, sp8[var_r29]) - 6;
        arg0->x += lbl_1_data_B2C[var_r26].x;
        arg0->y += lbl_1_data_B2C[var_r26].y;
        arg0->z += lbl_1_data_B2C[var_r26].z;
        MTXTrans(sp20, arg0->x, arg0->y, arg0->z);
        MTXConcat(sp50, sp20, sp20);
        arg0->x = sp20[0][3];
        arg0->y = sp20[1][3];
        arg0->z = sp20[2][3];
        arg0++;
    }
    return var_r23;
}

void fn_1_864C(s32 arg0)
{
    if (arg0 > lbl_1_bss_7C) {
        arg0 = lbl_1_bss_7C;
    }
    lbl_1_bss_78 = arg0;
}

s32 fn_1_867C(Vec *arg0, Vec *arg1)
{
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;

    s32 var_r31;
    Vec *var_r30;
    Vec *var_r29;
    omObjData *var_r28;
    s32 var_r27;
    s32 var_r24;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;
    M453MapUnkStruct *var_r18;

    var_r28 = lbl_1_bss_A4[lbl_1_bss_9C];
    var_r18 = var_r28->data;
    if ((var_r28->rot.x > 0.0f) || (var_r28->rot.x <= -90.0f)) {
        return 0;
    }
    VECSubtract(arg0, &var_r28->trans, &sp3C);
    sp3C.z = sp3C.z / cosd(var_r28->rot.x);
    var_f24 = arg0->z;
    var_f25 = arg0->x;
    var_r19 = fn_1_7AFC(var_f25, var_f24);
    var_r24 = fn_1_7BFC(var_r18, var_r19);
    if (var_r24 < 6) {
        return 0;
    }
    var_r24 -= 6;
    sp48 = lbl_1_data_A88[var_r19];
    VECSubtract(&sp3C, &sp48, &sp3C);
    var_r30 = lbl_1_data_B74[var_r24][0];
    var_r29 = lbl_1_data_B74[var_r24][1];
    var_r21 = lbl_1_data_BA4[var_r24];
    for (var_r31 = 0; var_r31 < var_r21; var_r31++) {
        var_r27 = (var_r31 + 1) % var_r21;
        VECSubtract(var_r30 + var_r27, var_r30 + var_r31, &sp24);
        VECSubtract(&sp3C, var_r30 + var_r27, &sp18);
        VECCrossProduct(&sp24, &sp18, &spC);
        if (!(spC.y < 0.0f)) {
            VECSubtract(var_r29 + var_r27, var_r30 + var_r27, &sp24);
            VECSubtract(&sp3C, var_r29 + var_r27, &sp18);
            VECCrossProduct(&sp24, &sp18, &spC);
            if (!(spC.y < 0.0f)) {
                VECSubtract(var_r29 + var_r31, var_r29 + var_r27, &sp24);
                VECSubtract(&sp3C, var_r29 + var_r31, &sp18);
                VECCrossProduct(&sp24, &sp18, &spC);
                if (!(spC.y < 0.0f)) {
                    VECSubtract(var_r30 + var_r31, var_r29 + var_r31, &sp24);
                    VECSubtract(&sp3C, var_r30 + var_r31, &sp18);
                    VECCrossProduct(&sp24, &sp18, &spC);
                    if (!(spC.y < 0.0f)) {
                        VECSubtract(var_r30 + var_r27, var_r30 + var_r31, &sp24);
                        var_f30 = (((sp3C.z * sp24.z)
                                       + (((sp3C.y * sp24.y) + ((sp3C.x * sp24.x) - (sp24.x * var_r30[var_r31].x))) - (sp24.y * var_r30[var_r31].y)))
                                      - (sp24.z * var_r30[var_r31].z))
                            / ((sp24.z * sp24.z) + ((sp24.x * sp24.x) + (sp24.y * sp24.y)));
                        sp30.x = var_r30[var_r31].x + (var_f30 * sp24.x);
                        sp30.y = var_r30[var_r31].y + (var_f30 * sp24.y);
                        sp30.z = var_r30[var_r31].z + (var_f30 * sp24.z);
                        VECSubtract(&sp30, &sp3C, &spC);
                        var_f28 = VECMag(&spC);
                        VECSubtract(var_r29 + var_r27, var_r29 + var_r31, &sp18);
                        var_f29 = (((sp3C.z * sp18.z)
                                       + (((sp3C.y * sp18.y) + ((sp3C.x * sp18.x) - (sp18.x * var_r29[var_r31].x))) - (sp18.y * var_r29[var_r31].y)))
                                      - (sp18.z * var_r29[var_r31].z))
                            / ((sp18.z * sp18.z) + ((sp18.x * sp18.x) + (sp18.y * sp18.y)));
                        sp30.x = var_r29[var_r31].x + (var_f29 * sp18.x);
                        sp30.y = var_r29[var_r31].y + (var_f29 * sp18.y);
                        sp30.z = var_r29[var_r31].z + (var_f29 * sp18.z);
                        VECSubtract(&sp30, &sp3C, &spC);
                        var_f27 = VECMag(&spC);
                        if (var_f28 == 0.0f) {
                            var_f31 = var_f30;
                        }
                        else if (var_f27 == 0.0f) {
                            var_f31 = var_f29;
                        }
                        else {
                            var_f26 = 1.0f - (var_f28 / (var_f28 + var_f27));
                            var_f31 = (var_f30 * var_f26) + (var_f29 * (1.0f - var_f26));
                        }
                        if (var_f31 < 0.0f) {
                            var_f31 = 0.0f;
                        }
                        else if (var_f31 > 1.0f) {
                            var_f31 = 1.0f;
                        }
                        sp3C.x = var_r29[var_r31].x + (var_f31 * sp18.x);
                        sp3C.y = var_r29[var_r31].y + (var_f31 * sp18.y);
                        sp3C.z = var_r29[var_r31].z + (var_f31 * sp18.z);
                        arg1->x = sp3C.x + (var_r28->trans.x + sp48.x);
                        arg1->y = sp3C.y + (var_r28->trans.y + sp48.y);
                        arg1->z = var_r28->trans.z + ((sp48.z + sp3C.z) * cosd(var_r28->rot.x));
                        return 1;
                    }
                }
            }
        }
    }
    var_r20 = 0;
    for (var_r31 = 0; var_r31 < var_r21; var_r31++) {
        var_r27 = (var_r31 + 1) % var_r21;
        var_f31 = (sp3C.z - var_r30[var_r31].z) / (var_r30[var_r27].z - var_r30[var_r31].z);
        spC.x = var_r30[var_r31].x + (var_f31 * (var_r30[var_r27].x - var_r30[var_r31].x));
        if ((var_f31 >= 0.0f) && (var_f31 < 1.0f) && (spC.x > sp3C.x)) {
            var_r20++;
        }
    }
    if ((var_r20 & 1) != 0) {
        arg1->x = arg0->x;
        arg1->y = arg0->y;
        arg1->z = arg0->z;
        return 1;
    }
    return 0;
}
