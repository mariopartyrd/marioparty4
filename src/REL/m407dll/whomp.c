#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/process.h"

#include "REL/m407dll.h"

#define MAX_WHOMPS_PLAYER 160
#define MAX_WHOMPS_ALL_PLAYERS MAX_WHOMPS_PLAYER *ARRAY_COUNT(GWPlayer)
#define MAX_WHOMPS (MAX_WHOMPS_PLAYER + 1) * ARRAY_COUNT(GWPlayer)

typedef struct unkDominationData7 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Vec unk_08;
    /* 0x14 */ Vec unk_14;
    /* 0x20 */ char unk_20[4];
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
} unkDominationData7; // sizeof 0x30

// function signatures
void fn_1_3360(omObjData *);
void fn_1_3364(omObjData *);
void fn_1_34A4(omObjData *);
void fn_1_37B0(omObjData *);
void fn_1_36D0(omObjData *);
void fn_1_2B7C(omObjData *);
void fn_1_290C(omObjData *, s32);
void fn_1_31F8(omObjData *);
void fn_1_4544(s32, s32, f32, f32, f32);
void fn_1_3BB8(s16, f32, f32);
void fn_1_568(s16, s16, s16);

// bss
Process *lbl_1_bss_37C0;
omObjData *lbl_1_bss_2DB0[MAX_WHOMPS];
s16 lbl_1_bss_1E98[MAX_WHOMPS][3];
s16 lbl_1_bss_68[MAX_WHOMPS][6];
s16 lbl_1_bss_66;
s16 lbl_1_bss_64;
s16 lbl_1_bss_3A[21];
s16 lbl_1_bss_38;

// data
s32 lbl_1_data_228[] = {
    DATA_MAKE_NUM(DATADIR_M407, 0x1C),
    DATA_MAKE_NUM(DATADIR_M407, 0x1D),
    DATA_MAKE_NUM(DATADIR_M407, 0x1E),
    DATA_MAKE_NUM(DATADIR_M407, 0x1B),
};

s32 lbl_1_data_238[] = {
    DATA_MAKE_NUM(DATADIR_M407, 0x2E),
    DATA_MAKE_NUM(DATADIR_M407, 0x2F),
    DATA_MAKE_NUM(DATADIR_M407, 0x2D),
    DATA_MAKE_NUM(DATADIR_M407, 0x2A),
    DATA_MAKE_NUM(DATADIR_M407, 0x2C),
    DATA_MAKE_NUM(DATADIR_M407, 0x27),
    DATA_MAKE_NUM(DATADIR_M407, 0x28),
    DATA_MAKE_NUM(DATADIR_M407, 0x29),
};

ObjFuncs lbl_1_data_258[] = {
    fn_1_3360,
    fn_1_3364,
    fn_1_34A4,
    fn_1_37B0,
    fn_1_36D0,
};

void fn_1_2354(Process *arg0)
{
    Process *sp8;
    u32 i;
    u32 j;

    lbl_1_bss_37C0 = arg0;

    for (j = 0, i = 0; i < MAX_WHOMPS_ALL_PLAYERS; i++) {
        lbl_1_bss_2DB0[i] = omAddObjEx(lbl_1_bss_37C0, 0x200, 3, 6, 2, fn_1_2B7C);
        lbl_1_bss_2DB0[i]->work[0] = i;
        lbl_1_bss_2DB0[i]->work[1] = 0;
    }

    j = j + i;

    for (i = 0; i < 4; i++) {
        lbl_1_bss_2DB0[j + i] = omAddObjEx(lbl_1_bss_37C0, 0x200, 3, 6, 2, fn_1_2B7C);
        lbl_1_bss_2DB0[j + i]->work[0] = j + i;
        lbl_1_bss_2DB0[j + i]->work[1] = 1;
    }

    for (i = 0; i < 4; i++) {
        lbl_1_bss_3A[i] = 0;
    }

    lbl_1_bss_64 = 0;
}

void fn_1_24F0(void)
{
    u32 i;

    for (i = 0; i < MAX_WHOMPS; i++) {
        fn_1_31F8(lbl_1_bss_2DB0[i]);
        omDelObjEx(lbl_1_bss_37C0, lbl_1_bss_2DB0[i]);
    }
}

void fn_1_2564(void)
{
    u32 i;

    HuAudFXPlay(0x542);
    for (i = 0; i < MAX_WHOMPS; i++) {
        fn_1_290C(lbl_1_bss_2DB0[i], 1);
    }
}

void fn_1_25C0(void)
{
    u32 i, j;

    lbl_1_bss_38 = 0;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_38 < lbl_1_bss_3A[i]) {
            lbl_1_bss_38 = lbl_1_bss_3A[i];
        }
    }

    lbl_1_bss_66 = 0;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_3A[i] > 0) {
            fn_1_290C(lbl_1_bss_2DB0[i], 3);
            lbl_1_bss_66 += 1;
        }
    }
}

void fn_1_26CC(u8 arg0)
{
    u32 i;
    omObjData *temp;

    i = lbl_1_bss_3A[arg0];
    if (i < MAX_WHOMPS_PLAYER) {
        lbl_1_bss_3A[arg0] = i + 1;
        temp = lbl_1_bss_2DB0[arg0 + i * ARRAY_COUNT(GWPlayer)];
        fn_1_290C(temp, 2);
    }
}

void fn_1_2770(u8 arg0, s16 arg2)
{
    omObjData *temp_r30;
    unkDominationData7 *temp_r31;

    temp_r30 = lbl_1_bss_2DB0[arg0 + MAX_WHOMPS_ALL_PLAYERS];
    temp_r31 = temp_r30->data;
    temp_r31->unk_08.x = 600.0f - (400.0f * arg0);
    temp_r31->unk_08.y = -300.0f;
    temp_r31->unk_08.z = 200.0f * (lbl_1_bss_3A[arg0] + 2);
    fn_1_290C(temp_r30, 2);
}

s32 fn_1_2880(void)
{
    return (lbl_1_bss_66 == 0) ? 1 : 0;
}

s16 fn_1_28B8(u8 arg0)
{
    return lbl_1_bss_3A[arg0];
}

s16 fn_1_28D4(void)
{
    return lbl_1_bss_64;
}

s16 fn_1_28E4(u8 arg0)
{
    return lbl_1_bss_2DB0[arg0 + MAX_WHOMPS_ALL_PLAYERS]->model[0];
}

void fn_1_290C(omObjData *arg0, s32 arg1)
{
    unkDominationData7 *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk_24 = arg1;
    temp_r31->unk_2C = 0;
}

void fn_1_2930(omObjData *arg0)
{
    unkDominationData7 *temp_r28;
    omObjData *temp_r29;
    u32 i;
    unkDominationData7 *temp_r31;

    temp_r31 = arg0->data;
    lbl_1_data_258[temp_r31->unk_24](arg0);
    if ((temp_r31->unk_08.z > (Center.z - 2000.0f)) && (temp_r31->unk_08.z < (2000.0f + Center.z)) && (temp_r31->unk_04 == 0)) {
        for (i = 0; i < 8; i++) {
            temp_r29 = lbl_1_bss_2DB0[(temp_r31->unk_00 % 80) + (i * 80)];
            temp_r29->model[0] = -1;
            temp_r28 = temp_r29->data;
            temp_r28->unk_04 = 0;
        }
        arg0->model[0] = lbl_1_bss_1E98[((temp_r31->unk_00 % 80))][0];

        if (temp_r31->unk_08.y < 0.0f) {
            Hu3DModelShadowDispOff(arg0->model[0]);
        }
        else {
            Hu3DModelShadowDispOn(arg0->model[0]);
        }

        temp_r31->unk_04 = 1;
    }

    if ((temp_r31->unk_08.y < 0.0f) || (temp_r31->unk_08.z < (Center.z - 2000.0f))) {
        Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrReset(arg0->model[0], HU3D_ATTR_DISPOFF);
    }

    omSetTra(arg0, temp_r31->unk_08.x, temp_r31->unk_08.y, temp_r31->unk_08.z);
    omSetRot(arg0, temp_r31->unk_14.x, temp_r31->unk_14.y, temp_r31->unk_14.z);

    if (temp_r31->unk_28 == 1) {
        Hu3DModelPosSet(arg0->model[2], temp_r31->unk_08.x, 1.0f + temp_r31->unk_08.y, temp_r31->unk_08.z);
    }
}

void fn_1_2B7C(omObjData *arg0)
{
    u32 i;
    unkDominationData7 *temp_r30;

    arg0->func = fn_1_2930;
    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkDominationData7), MEMORY_DEFAULT_NUM);
    temp_r30 = arg0->data;

    for (i = 0; i < 3; i++) {
        arg0->model[i] = -1;
    }

    for (i = 0; i < 6; i++) {
        arg0->motion[i] = -1;
    }

    temp_r30->unk_00 = (u32)arg0->work[0];
    temp_r30->unk_28 = (u32)arg0->work[1];
    temp_r30->unk_04 = 0;
    temp_r30->unk_2C = 0;
    switch (temp_r30->unk_28) {
        case 0:
            temp_r30->unk_14.x = 0.0f;
            temp_r30->unk_14.y = 180.0f;
            temp_r30->unk_14.z = 0.0f;
            if (temp_r30->unk_00 < 80) {
                arg0->model[0] = Hu3DModelCreateFile(lbl_1_data_228[1]);
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_NOCULL);
                Hu3DModelAmbSet(arg0->model[0], 1.0f, 1.0f, 1.0f);
                if (temp_r30->unk_00 == 0) {
                    arg0->motion[5] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_238[5]);
                    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_238[7]);
                    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_238[6]);
                }
                else {
                    arg0->motion[5] = lbl_1_bss_68[0][5];
                    arg0->motion[3] = lbl_1_bss_68[0][3];
                    arg0->motion[4] = lbl_1_bss_68[0][4];
                }
                Hu3DModelShadowSet(arg0->model[0]);
                for (i = 0; i < 3; i++) {
                    lbl_1_bss_1E98[temp_r30->unk_00][i] = arg0->model[i];
                }

                for (i = 0; i < 6; i++) {
                    lbl_1_bss_68[temp_r30->unk_00][i] = arg0->motion[i];
                }
                Hu3DMotionSet(arg0->model[0], arg0->motion[5]);
                Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
                temp_r30->unk_04 = 1;
            }
            else {
                temp_r30->unk_04 = 0;
            }
            break;
        case 1:
            temp_r30->unk_14.x = 0.0f;
            temp_r30->unk_14.y = 0.0f;
            temp_r30->unk_14.z = 0.0f;
            arg0->model[0] = Hu3DModelCreateFile(lbl_1_data_228[0]);
            arg0->model[1] = Hu3DModelCreateFile(lbl_1_data_228[2]);
            arg0->model[2] = Hu3DModelCreateFile(lbl_1_data_228[3]);
            Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_NOCULL);
            Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_NOCULL);
            Hu3DModelAmbSet(arg0->model[0], 1.0f, 1.0f, 1.0f);
            Hu3DModelAmbSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
            arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_238[2]);
            arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_238[4]);
            arg0->motion[5] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_238[3]);
            arg0->motion[0] = Hu3DJointMotionFile(arg0->model[1], lbl_1_data_238[0]);
            arg0->motion[1] = Hu3DJointMotionFile(arg0->model[1], lbl_1_data_238[1]);
            Hu3DModelHookSet(arg0->model[0], "itemhook_r", arg0->model[1]);
            Hu3DModelShadowSet(arg0->model[0]);
            Hu3DModelShadowSet(arg0->model[1]);
            Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[2], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(arg0->model[2], HU3D_MOTATTR_LOOP);
            temp_r30->unk_04 = 1;
            break;
    }
    temp_r30->unk_08.x = (600.0f - (400.0f * (temp_r30->unk_00 & 3)));
    temp_r30->unk_08.y = 0.0f;
    temp_r30->unk_08.z = (200.0f * (temp_r30->unk_00 >> 2));
    fn_1_290C(arg0, 0);
}

void fn_1_31F8(omObjData *arg0)
{
    s32 i;
    unkDominationData7 *temp_r29;

    temp_r29 = arg0->data;
    switch (temp_r29->unk_28) { /* irregular */
        case 0:
            if (temp_r29->unk_00 == 0) {
                for (i = 0; i < 6; i++) {
                    if (arg0->motion[i] != -1) {
                        Hu3DMotionKill(arg0->motion[i]);
                    }
                }
            }
            if (temp_r29->unk_04 != 0) {
                for (i = 0; i < 3; i++) {
                    if (arg0->model[i] != -1) {
                        Hu3DModelKill(arg0->model[i]);
                    }
                }
            }
            break;
        case 1:
            for (i = 0; i < 6; i++) {
                if (arg0->motion[i] != -1) {
                    Hu3DMotionKill(arg0->motion[i]);
                }
            }
            for (i = 0; i < 3; i++) {
                if (arg0->model[i] != -1) {
                    Hu3DModelKill(arg0->model[i]);
                }
            }
            break;
    }
    if (arg0->data) {
        HuMemDirectFree(arg0->data);
    }
}

void fn_1_3360(omObjData *) { }

void fn_1_3364(omObjData *arg0)
{
    unkDominationData7 *temp_r31;

    temp_r31 = arg0->data;
    if (temp_r31->unk_2C == 0) {
        Hu3DMotionSet(arg0->model[0], arg0->motion[4]);
        Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
        switch (temp_r31->unk_28) {
            case 0:
                fn_1_4544(0, 0, temp_r31->unk_08.x, 0.0f, temp_r31->unk_08.z);
                break;
            case 1:
                fn_1_4544(1, 0, temp_r31->unk_08.x, 0.0f, temp_r31->unk_08.z);
                break;
        }
    }

    if (temp_r31->unk_2C == 0x2A) {
        Hu3DModelShadowDispOff(arg0->model[0]);
    }

    if (Hu3DMotionEndCheck(*arg0->model) == 0) {
        temp_r31->unk_2C++;
        return;
    }

    temp_r31->unk_08.y = -300.0f;
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
    fn_1_290C(arg0, 0);
}

void fn_1_34A4(omObjData *arg0)
{
    unkDominationData7 *temp_r30;

    temp_r30 = arg0->data;
    if (temp_r30->unk_2C == 0) {
        if (temp_r30->unk_28 == 1) {
            Hu3DModelAttrReset(arg0->model[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(arg0->model[1], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(arg0->model[0], HU3D_ATTR_DISPOFF);
        }
        Hu3DMotionSet(arg0->model[0], arg0->motion[3]);
        Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
        switch (temp_r30->unk_28) { /* irregular */
            case 0:
                fn_1_4544(0, 0, temp_r30->unk_08.x, 0.0f, temp_r30->unk_08.z);
                HuAudFXPlay(0x543);
                break;
            case 1:
                HuAudFXPlay(0x544);
                fn_1_4544(1, 0, temp_r30->unk_08.x, 0.0f, temp_r30->unk_08.z);
                break;
        }
        temp_r30->unk_08.y = 0.0f;
    }

    if (temp_r30->unk_2C == 0xA) {
        Hu3DModelShadowDispOn(arg0->model[0]);
    }

    if ((temp_r30->unk_2C == 0xA) && (temp_r30->unk_28 == 1)) {
        Hu3DMotionSet(arg0->model[1], arg0->motion[1]);
        Hu3DModelAttrReset(arg0->model[1], HU3D_MOTATTR_LOOP);
    }

    temp_r30->unk_2C++;

    if (Hu3DMotionEndCheck(arg0->model[0]) != 0) {
        Hu3DMotionShiftSet(arg0->model[0], arg0->motion[5], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
        switch (temp_r30->unk_28) {
            case 0:
                fn_1_290C(arg0, 0);
                return;
            case 1:
                fn_1_290C(arg0, 4);
                break;
        }
    }
}

void fn_1_36D0(omObjData *arg0)
{
    unkDominationData7 *sp8;

    sp8 = arg0->data;
    Hu3DMotionShiftSet(arg0->model[0], arg0->motion[2], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(arg0->model[1], arg0->motion[0]);
    Hu3DModelAttrSet(arg0->model[1], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(arg0->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(arg0->model[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(arg0->model[2], HU3D_MOTATTR_LOOP);
    fn_1_290C(arg0, 0);
}

void fn_1_37B0(omObjData *arg0)
{
    unkDominationData7 *temp_r31;

    temp_r31 = arg0->data;
    if (temp_r31->unk_2C == 0) {
        temp_r31->unk_14.x = 0.0f;
        temp_r31->unk_08.y = 0.0f;
        Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_PAUSE);
        temp_r31->unk_2C++;
    }
    temp_r31->unk_14.x -= 4.0f;
    temp_r31->unk_08.y += 0.9f;
    if ((temp_r31->unk_14.x <= -25.0f) && (temp_r31->unk_2C == 1)) {
        if ((temp_r31->unk_00 < 640) && ((temp_r31->unk_00 >> 2) < (lbl_1_bss_3A[temp_r31->unk_00 & 3] - 1))) {
            fn_1_290C(lbl_1_bss_2DB0[temp_r31->unk_00 + 4], 3);
            temp_r31->unk_2C++;
        }
        if (lbl_1_bss_64 < (temp_r31->unk_00 >> 2) + 1) {
            lbl_1_bss_64 = (temp_r31->unk_00 >> 2) + 1;
        }
    }
    if ((temp_r31->unk_2C == 1) && (temp_r31->unk_14.x > -90.0f) || (temp_r31->unk_2C == 2) && (temp_r31->unk_14.x > -68.0f)) {
        return;
    }

    temp_r31->unk_14.x = (temp_r31->unk_2C == 1) ? -90.0f : -68.0f;

    if (temp_r31->unk_2C == 1) {
        fn_1_4544(3, 0, temp_r31->unk_08.x, 0.0f, 200.0f + temp_r31->unk_08.z);
        HuAudFXPlay(0x544);
        if (lbl_1_bss_38 > (temp_r31->unk_00 >> 2) + 1) {
            fn_1_3BB8((temp_r31->unk_00 >> 2) + 1, temp_r31->unk_08.x, temp_r31->unk_08.z);
        }
        lbl_1_bss_66 -= 1;
    }
    else {
        fn_1_4544(2, 0, temp_r31->unk_08.x, 0.0f, 200.0f + temp_r31->unk_08.z);
        HuAudFXPlay(0x543);
    }
    fn_1_568(temp_r31->unk_00 & 3, 2, 4);
    fn_1_290C(arg0, 0);
}
