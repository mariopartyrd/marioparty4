#include "game/audio.h"
#include "game/chrman.h"
#include "game/hsfman.h"
#include "game/hsfdraw.h"
#include "game/hsfmotion.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "ext_math.h"
#include "version.h"

#include "REL/m434Dll.h"

#ifndef __MWERKS__
#include "game/frand.h"
#include <string.h>
#endif

typedef struct data_224_struct {
    u16 unk0;
    u16 unk2;
    float unk4;
    float unk8;
    u32 unkC;
} Data224Struct;

omObjData *lbl_1_bss_5870[4];

char *lbl_1_data_190[8] = {
    "dmy-itemhook-r",
    "dmy-itemhook-r",
    "dmy-itemhook-r",
    "dmy-itemhook-r",
    "dmy-itemhook-r",
    "dmy-itemhook-r",
    "dmy-itemhook-r",
    "dmy-itemhook-r",
};

char *lbl_1_data_1BC[8] = {
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
    "itemhook-r",
};

s32 lbl_1_data_1DC[2] = { 0x410003, 0x410004 };

Vec lbl_1_data_1E4[2] = { { -550, 0, 550 }, { 550, 0, 550 } };

u32 lbl_1_data_1FC[10] = { 0, 2, 23, 133, 0x41000E, 0x410016, 0x41001E, 0x410026, 0x41002E, 0x410036 };

Data224Struct lbl_1_data_224[9] = {
    { 0, 4, 0.2f * REFRESH_RATE, 0, HU3D_MOTATTR_LOOP },
    { 1, 6, 0.1f * REFRESH_RATE, 0, HU3D_MOTATTR_LOOP },
    { 0, 8, 0.1f * REFRESH_RATE, 0, HU3D_MOTATTR_NONE },
    { 0, 5, 0.1f * REFRESH_RATE, 0, HU3D_MOTATTR_LOOP },
    { 1, 5, 0.1f * REFRESH_RATE, 0, HU3D_MOTATTR_LOOP },
    { 0, 8, 0.1f * REFRESH_RATE, 0.5f * REFRESH_RATE, HU3D_MOTATTR_NONE },
    { 0, 9, 0.1f * REFRESH_RATE, 0, HU3D_MOTATTR_NONE },
    { 2, 0, 0.2f * REFRESH_RATE, 0, HU3D_MOTATTR_NONE },
    { 3, 0, 0.2f * REFRESH_RATE, 0, HU3D_MOTATTR_NONE },
};

void fn_1_4988(omObjData *object);

void fn_1_4854(Process *objman)
{
    s16 temp_r31;
    omObjData *temp_r30;
    s16 temp_r29;
    s32 sp8[2] = { 0, 0 };
    omMakeGroupEx(objman, 0, 4);
    omGetGroupMemberListEx(objman, 0);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r30 = lbl_1_bss_5870[temp_r31] = omAddObjEx(objman, 40, 2, 10, 0, fn_1_4988);
        temp_r30->work[0] = temp_r31;
        temp_r29 = fn_1_1D74(temp_r31);
        temp_r30->work[1] = (temp_r29 * 2) + sp8[temp_r29];
        sp8[temp_r29]++;
    }
}

void fn_1_4964(void)
{
    CharModelKill(-1);
}

typedef struct work_4988 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    u32 unk14;
    u32 unk18;
    float unk1C;
    float unk20;
    s32 unk24;
    Vec unk28;
    float unk34;
    u16 unk38;
    s16 unk3A;
    s16 unk3C;
    s16 unk3E;
    float unk40;
    float unk44;
    float unk48;
    float unk4C;
    float unk50;
    s32 unk54;
    s16 unk58[3];
    s32 unk60;
    float unk64;
    s32 unk68;
    u16 unk6C;
    s32 unk70;
    Vec unk74;
    s16 unk80;
    float unk84;
    Vec unk88;
    Vec unk94;
} Work4988;

void fn_1_4DF4(omObjData *object);
void fn_1_60AC(omObjData *arg0, u32 arg1);

void fn_1_4988(omObjData *object)
{
    Work4988 *temp_r31;
    s16 temp_r29;
    s32 temp_r28;
    s32 temp_r27;

    float sp1C[4] = { 0.5f, 0.65f, 0.8f, 1.0f };
    s32 spC[4] = { 1, 1, 2, 2 };
    s32 sp8;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work4988), MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    memset(temp_r31, 0, sizeof(Work4988));
    temp_r27 = object->work[0];
    temp_r28 = GWPlayerCfg[temp_r27].character;
    temp_r31->unk8 = temp_r28;
    sp8 = temp_r31->unkC = 0;
    temp_r31->unk0 = (object->work[1] >> 1) & 0x1;
    temp_r31->unk4 = object->work[1] & 0x1;
    temp_r31->unk6C = 0;
    temp_r31->unk64 = sp1C[GWPlayerCfg[temp_r27].diff & 0x3];
    temp_r31->unk68 = spC[GWPlayerCfg[temp_r27].diff & 0x3];
    object->model[0] = CharModelCreate(temp_r28, 8);
    CharModelStepTypeSet(temp_r28, 3);
    Hu3DModelCameraSet(object->model[0], 4);
    Hu3DModelLayerSet(object->model[0], 4);
    object->model[1] = Hu3DModelCreateFile(lbl_1_data_1DC[temp_r31->unk0]);
    Hu3DModelCameraSet(object->model[1], 4);
    Hu3DModelLayerSet(object->model[1], 4);
    Hu3DModelHookSet(object->model[0], lbl_1_data_190[temp_r31->unkC], object->model[1]);
    Hu3DModelClusterAttrSet(object->model[1], 0, 0xC0000001);
    for (temp_r29 = 0; temp_r29 < 10; temp_r29++) {
        if (lbl_1_data_1FC[temp_r29] < 0x10000) {
            object->motion[temp_r29] = CharModelMotionCreate(temp_r28, lbl_1_data_1FC[temp_r29]);
        }
        else {
            object->motion[temp_r29] = Hu3DJointMotionFile(object->model[0], temp_r28 + lbl_1_data_1FC[temp_r29]);
        }
    }
    CharModelMotionDataClose(temp_r28);
    object->trans.x = temp_r31->unk88.x = ((2.0f * object->work[1]) * 100.0f) - 300.0f;
    object->trans.y = temp_r31->unk88.y = -70;
    object->trans.z = temp_r31->unk88.z = 0;
    temp_r31->unk94.x = temp_r31->unk94.y = temp_r31->unk94.z = 0;
    temp_r31->unk40 = temp_r31->unk44 = 0;
    temp_r31->unk48 = 0;
    temp_r31->unk4C = 0.02f;
    temp_r31->unk84 = 55;
    temp_r31->unk28 = lbl_1_data_1E4[temp_r31->unk0];
    temp_r31->unk28.y = object->trans.y;
    temp_r31->unk34 = 400;
    temp_r31->unk54 = 0;
    for (temp_r29 = 0; temp_r29 < 3; temp_r29++) {
        temp_r31->unk58[temp_r29] = -1;
    }
    temp_r31->unk50 = 0;
    temp_r31->unk10 = -1;
    temp_r31->unk60 = 0;
    fn_1_60AC(object, 0);
    temp_r31->unk38 = 0;
    object->func = fn_1_4DF4;
}

void fn_1_4E50(omObjData *object);
void fn_1_5BEC(omObjData *object);

void fn_1_4DF4(omObjData *object)
{
    Work4988 *temp_r31 = object->data;
    fn_1_5BEC(object);
    temp_r31->unk3C++;
    temp_r31->unk38 = 0;
    object->func = fn_1_4E50;
}

void fn_1_5AB0(omObjData *object);

void fn_1_5C98(omObjData *object);
void fn_1_64C0(omObjData *object);

float fn_1_67AC(float arg0, float arg1);

void fn_1_4E50(omObjData *object)
{
    float temp_f31;
    float temp_f30;
    float temp_f28;
    Work4988 *temp_r31 = object->data;

    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27 = 0;
    Mtx sp2C;
    Vec sp20;
    char *sp14[3] = { "f0", "f1", "f2" };
    float spC[2] = { 0.05, 0.02 };
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0;
    temp_r31->unk20 = 0;
    temp_r31->unk1C = 0;
    if (fn_1_1D54() == 2) {
        if (GWPlayerCfg[object->work[0]].iscom) {
            fn_1_5C98(object);
        }
        else {
            temp_r31->unk18 = HuPadBtn[GWPlayerCfg[object->work[0]].pad_idx];
            temp_r31->unk14 = HuPadBtnDown[GWPlayerCfg[object->work[0]].pad_idx];
            temp_f31 = HuPadStkX[GWPlayerCfg[object->work[0]].pad_idx];
            temp_f30 = -HuPadStkY[GWPlayerCfg[object->work[0]].pad_idx];

            temp_r31->unk20 = atan2d(temp_f31, temp_f30);
            temp_r31->unk1C = (1.0f / 72.0f) * VECMagPoint(temp_f31, temp_f30, 0);
            if (temp_r31->unk1C > 1.0f) {
                temp_r31->unk1C = 1.0f;
            }
        }
    }
    temp_r31->unk60 = 0;
    switch (temp_r31->unk38) {
        case 0:
            temp_r27 = 1;
            if (temp_r31->unk1C > spC[temp_r31->unk24]) {
                temp_r31->unk24 = 1;
                temp_r31->unk44 = temp_r31->unk20;
                temp_r31->unk94.x += 225.0f * (temp_r31->unk1C * sind(temp_r31->unk20)) * (1.0f / REFRESH_RATE);
                temp_r31->unk94.z += 225.0f * (temp_r31->unk1C * cosd(temp_r31->unk20)) * (1.0f / REFRESH_RATE);
                temp_r31->unk48 = 0.2f;
                temp_r31->unk4C = 0;
                if (CharModelMotionShiftIDGet(temp_r31->unk8) < 0) {
                    fn_1_60AC(object, 1);
                    CharModelMotionSpeedSet(temp_r31->unk8, temp_r31->unk1C);
                }
                if (temp_r31->unk1C > 0.75f && (temp_r31->unk3A & 0x7) == 0) {
                    fn_1_8C14(object->work[0], &temp_r31->unk88, temp_r31->unk1C);
                    if ((temp_r31->unk3A & 0xF) == 0) {
                        fn_1_43AC(&temp_r31->unk88);
                    }
                }
            }
            else {
                temp_r31->unk24 = 0;
                if (CharModelMotionShiftIDGet(temp_r31->unk8) < 0) {
                    fn_1_60AC(object, 0);
                }
            }
            if (temp_r31->unk14 & PAD_BUTTON_A) {
                temp_r31->unk38 = 1;
                temp_r31->unk3C = 0;
            }
            else if (temp_r31->unk14 & PAD_BUTTON_B) {
                temp_r31->unk38 = 3;
                temp_r31->unk3C = 0;
                temp_r31->unk3A = 0;
            }
            else {
                temp_r31->unk60 = 1;
            }
            break;

        case 1:
            temp_r31->unk24 = 0;
            if (temp_r31->unk3C == 0) {
                fn_1_60AC(object, 2);
                temp_r31->unk3A = 0;
                temp_r31->unk3C++;
            }
            else if (temp_r31->unk3C == 1 && temp_r31->unk3A > (0.5f * REFRESH_RATE)) {
                if (temp_r31->unk54 < 3) {
                    temp_r28 = fn_1_8884(&temp_r31->unk88, 20, 150, temp_r31->unk40, -30, 30, 1, object->work[0]);
                    if (temp_r28 >= 0) {
                        temp_r31->unk58[temp_r31->unk54++] = temp_r28;
                        omVibrate(object->work[0], 12, 6, 6);
                    }
                }
                temp_r31->unk38 = 2;
                temp_r31->unk3A = 0;
                temp_r31->unk3C = 0;
            }
            break;

        case 2:
            if (temp_r31->unk3C == 0) {
                if (!(temp_r31->unk18 & PAD_BUTTON_A)) {
                    temp_r31->unk24 = 0;
                    fn_1_60AC(object, 5);
                    temp_r31->unk3A = 0;
                    temp_r31->unk3C++;
                }
                else {
                    temp_f28 = fn_1_67AC(temp_r31->unk40, temp_r31->unk20);
                    if (temp_f28 > 10.0f) {
                        temp_f28 = 10.0f;
                    }
                    else if (temp_f28 < -10.0f) {
                        temp_f28 = -10.0f;
                    }
                    if (temp_r31->unk1C > spC[temp_r31->unk24] && fabs(temp_f28) > 5.0) {
                        temp_r31->unk24 = 1;
                        temp_r31->unk44 = temp_r31->unk40 + temp_f28;
                        temp_r31->unk48 = 0.2f;
                        temp_r31->unk4C = 0;
                        if (CharModelMotionShiftIDGet(temp_r31->unk8) < 0) {
                            fn_1_60AC(object, 4);
                            CharModelMotionSpeedSet(temp_r31->unk8, 0.5f);
                        }
                        if (temp_r31->unk54 < 3) {
                            temp_r28 = fn_1_8884(&temp_r31->unk88, 20, 150, temp_r31->unk40, -15, 15, 1, object->work[0]);
                            if (temp_r28 >= 0) {
                                temp_r31->unk58[temp_r31->unk54++] = temp_r28;
                                omVibrate(object->work[0], 12, 6, 6);
                            }
                        }
                    }
                    else {
                        temp_r31->unk24 = 0;
                        if (CharModelMotionShiftIDGet(temp_r31->unk8) < 0) {
                            fn_1_60AC(object, 3);
                        }
                    }
                }
            }
            else {
                if (temp_r31->unk3A > (0.5f * REFRESH_RATE)) {
                    temp_r31->unk38 = 0;
                }
            }
            break;

        case 3:
            temp_r31->unk24 = 0;
            if (temp_r31->unk3C == 0) {
                temp_r31->unk3E = 0;
                VECSubtract(&temp_r31->unk28, &temp_r31->unk88, &sp20);
                temp_r31->unk44 = atan2d(sp20.x, sp20.z);
                temp_f28 = VECMag(&sp20);
                if (temp_f28 < temp_r31->unk34) {
                    temp_r31->unk3E++;
                    fn_1_60AC(object, 6);
                }
                else {
                    fn_1_60AC(object, 0);
                }
                temp_r31->unk3A = 0;
                temp_r31->unk3C++;
            }
            if (temp_r31->unk3E) {
                if (temp_r31->unk3A > (VERSION_NTSC ? 36.0f : 30.000002f)) {
                    for (temp_r29 = 0; temp_r29 < temp_r31->unk54; temp_r29++) {
                        fn_1_8B58(temp_r31->unk58[temp_r29]);
                    }
                    temp_r31->unk54 = 0;
                    temp_r31->unk3E = 0;
                }
            }
            if (temp_r31->unk3A > 1.0f * REFRESH_RATE) {
                temp_r31->unk38 = 0;
            }
            break;
    }
    VECAdd(&temp_r31->unk88, &temp_r31->unk94, &temp_r31->unk88);
    temp_r31->unk94.x = temp_r31->unk94.y = temp_r31->unk94.z = 0;
    fn_1_64C0(object);
    temp_f28 = 0;
    if (temp_r31->unk54) {
        temp_f28 = (temp_r31->unk54 * 10) + 10;
    }
    temp_r31->unk50 += (temp_f28 - temp_r31->unk50) * 0.3f;
    Hu3DData[object->model[1]].unk_A4[0] = temp_r31->unk50;
    Hu3DModelObjMtxGet(object->model[0], lbl_1_data_190[temp_r31->unkC], sp2C);
    for (temp_r29 = 0; temp_r29 < temp_r31->unk54; temp_r29++) {
        Hu3DModelObjPosGet(object->model[1], sp14[temp_r29], &sp20);
        MTXMultVec(sp2C, &sp20, &sp20);
        fn_1_8AEC(temp_r31->unk58[temp_r29], &sp20);
    }
    fn_1_5BEC(object);
    if (fn_1_1D54() == 5 && temp_r27) {
        temp_r31->unk38 = 0;
        object->func = fn_1_5AB0;
    }
}

s32 fn_1_6248(omObjData *object);

void fn_1_5AB0(omObjData *object)
{
    Work4988 *temp_r31 = object->data;
    s32 sp8[2] = { -1, 1 };
    fn_1_5BEC(object);
    switch (temp_r31->unk38) {
        case 0:
            temp_r31->unk38++;
            break;

        case 1:
            Hu3DModelHookReset(object->model[0]);
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
            if (sp8[temp_r31->unk0] == fn_1_1D8C()) {
                fn_1_60AC(object, 7);
            }
            else {
                fn_1_60AC(object, 8);
            }
            temp_r31->unk44 = 0;
            temp_r31->unk48 = 0;
            temp_r31->unk4C = 0.005f;
            temp_r31->unk38++;
            break;

        case 2:
            if (fn_1_6248(object)) {
                temp_r31->unk38++;
            }
            break;
    }
}

float fn_1_6690(float arg0, float arg1, float arg2);

void fn_1_5BEC(omObjData *object)
{
    Work4988 *temp_r31 = object->data;
    temp_r31->unk3A++;
    object->trans.x = temp_r31->unk88.x;
    object->trans.y = temp_r31->unk88.y;
    object->trans.z = temp_r31->unk88.z;
    temp_r31->unk48 += temp_r31->unk4C;
    if (temp_r31->unk48 > 0.45f) {
        temp_r31->unk48 = 0.45f;
    }
    temp_r31->unk40 = fn_1_6690(temp_r31->unk40, temp_r31->unk44, temp_r31->unk48);
    object->rot.y = temp_r31->unk40;
}

void fn_1_5C98(omObjData *object)
{
    Vec sp8;
    Work4988 *temp_r31 = object->data;
    s32 temp_r30;
    s32 temp_r29 = 0;
    s32 temp_r28;
    switch (temp_r31->unk6C) {
        case 0:
            if (temp_r31->unk60) {
                temp_r31->unk70 = fn_1_8FA0(&temp_r31->unk88);
                if (temp_r31->unk70 < 0 || temp_r31->unk54 >= temp_r31->unk68 || fn_1_1D44() < 10) {
                    temp_r29 = 1;
                }
                if (temp_r31->unk54 && temp_r29) {
                    temp_r31->unk6C = 3;
                    temp_r31->unk80 = 0;
                }
                else if (temp_r31->unk70 >= 0) {
                    temp_r31->unk6C = 1;
                    temp_r31->unk80 = 0;
                    fn_1_8E2C(temp_r31->unk70, &temp_r31->unk74);
                    temp_r31->unk74.y = temp_r31->unk88.y;
                }
            }
            break;

        case 1:
            temp_r31->unk1C = 0.73f * temp_r31->unk64;
            if (temp_r31->unk54 && fn_1_1D44() < 10) {
                temp_r31->unk6C = 0;
            }
            else {
                temp_r28 = fn_1_8D78(&temp_r31->unk88);
                if (fn_1_8F3C(temp_r28) > 0) {
                    temp_r31->unk6C = 2;
                    temp_r31->unk80 = 0;
                }
                else {
                    VECSubtract(&temp_r31->unk74, &temp_r31->unk88, &sp8);
                    temp_r31->unk20 = fn_1_6690(temp_r31->unk40, atan2d(sp8.x, sp8.z), temp_r31->unk64 * 0.25f);
                    temp_r30 = 0;
                    if (VECMag(&sp8) < 50.0f) {
                        temp_r30 = 1;
                    }
                    if (temp_r30 && fn_1_8F3C(temp_r31->unk70) > 0) {
                        temp_r31->unk6C = 2;
                        temp_r31->unk80 = 0;
                    }
                    else {
                        temp_r31->unk80++;
                        if (temp_r30 || temp_r31->unk80 > (1.0f * REFRESH_RATE)) {
                            if (temp_r30 || frandmod(1000) < 10) {
                                temp_r31->unk70 = fn_1_8FA0(&temp_r31->unk88);
                                fn_1_8E2C(temp_r31->unk70, &temp_r31->unk74);
                                temp_r31->unk74.y = temp_r31->unk88.y;
                                temp_r31->unk80 = 0;
                                if (temp_r31->unk70 < 0) {
                                    temp_r31->unk6C = 0;
                                }
                            }
                        }
                    }
                }
            }
            break;

        case 2:
            temp_r31->unk80++;
            if (temp_r31->unk80 < (2 * REFRESH_RATE) * temp_r31->unk64) {
                temp_r31->unk1C = 0.4f;
                temp_r31->unk20 = temp_r31->unk40 + 10.0f;
                temp_r31->unk14 = temp_r31->unk18 = PAD_BUTTON_A;
            }
            else {
                temp_r31->unk6C = 0;
            }
            break;

        case 3:
            temp_r31->unk1C = 0.75f + (0.25f * temp_r31->unk64);
            VECSubtract(&temp_r31->unk28, &temp_r31->unk88, &sp8);
            temp_r31->unk20 = fn_1_6690(temp_r31->unk40, atan2d(sp8.x, sp8.z), 0.2f);
            if (VECMag(&sp8) < temp_r31->unk34 - 30.000002f) {
                temp_r31->unk14 = temp_r31->unk18 = PAD_BUTTON_B;
                temp_r31->unk6C = 0;
            }
            break;
    }
}

void fn_1_60AC(omObjData *arg0, u32 arg1)
{
    float temp_f31;
    Work4988 *temp_r30 = arg0->data;
    if (temp_r30->unk10 != arg1 && arg1 < 9) {
        temp_f31 = lbl_1_data_224[arg1].unk4;
        if (temp_r30->unk10 < 0) {
            temp_f31 = 0;
        }
        temp_r30->unk10 = arg1;
        CharModelMotionShiftSet(temp_r30->unk8, arg0->motion[lbl_1_data_224[arg1].unk0], 0, temp_f31, lbl_1_data_224[arg1].unkC);
        CharModelMotionSpeedSet(temp_r30->unk8, 1.0f);
        if (lbl_1_data_224[arg1].unk2) {
            Hu3DMotionOverlaySet(arg0->model[0], arg0->motion[lbl_1_data_224[arg1].unk2]);
            Hu3DMotionOverlayTimeSet(arg0->model[0], lbl_1_data_224[arg1].unk8);
            Hu3DData[arg0->model[0]].unk_78 = 1.0f;
        }
        else {
            Hu3DMotionOverlayReset(arg0->model[0]);
        }
    }
}

s32 fn_1_6248(omObjData *object)
{
    Work4988 *temp_r31 = object->data;
    s32 temp_r30 = 0;
    if (CharModelMotionEndCheck(temp_r31->unk8) && CharModelMotionShiftIDGet(temp_r31->unk8) < 0) {
        temp_r30 = 1;
    }
    return temp_r30;
}

s32 fn_1_62BC(omObjData *arg0, u32 arg1)
{
    s32 result = 0;
    if (fn_1_6248(arg0)) {
        fn_1_60AC(arg0, arg1);
        result = 1;
    }
    return result;
}

s32 fn_1_649C(omObjData *object)
{
    Work4988 *sp8 = object->data;
    s32 temp_r31 = 0;
    return temp_r31;
}

void fn_1_64C0(omObjData *object)
{
    float temp_f31;
    Vec sp8;
    Work4988 *temp_r31;
    Work4988 *temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    for (temp_r27 = 0; temp_r27 < 2; temp_r27++) {
        for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
            temp_r31 = lbl_1_bss_5870[temp_r29]->data;
            for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
                if (temp_r29 == temp_r28) {
                    continue;
                }
                temp_r30 = lbl_1_bss_5870[temp_r28]->data;
                VECSubtract(&temp_r31->unk88, &temp_r30->unk88, &sp8);
                temp_f31 = VECMag(&sp8);
                if (temp_f31 < temp_r31->unk84 + temp_r30->unk84) {
                    temp_f31 = 0.5f * ((temp_r31->unk84 + temp_r30->unk84) - temp_f31);
                    VECNormalize(&sp8, &sp8);
                    VECScale(&sp8, &sp8, temp_f31);
                    VECAdd(&temp_r31->unk88, &sp8, &temp_r31->unk88);
                    VECSubtract(&temp_r30->unk88, &sp8, &temp_r30->unk88);
                }
            }
            sp8 = temp_r31->unk88;
            sp8.y = 0;
            temp_f31 = VECMag(&sp8);
            if (temp_f31 > 510.0f - temp_r31->unk84) {
                VECNormalize(&sp8, &sp8);
                VECScale(&sp8, &sp8, -(temp_f31 - (510.0f - temp_r31->unk84)));
                VECAdd(&sp8, &temp_r31->unk88, &temp_r31->unk88);
            }
        }
    }
}

float fn_1_6690(float arg0, float arg1, float arg2)
{
    float temp_f31;
    temp_f31 = fmodf(arg1 - arg0, 360.0);
    if (temp_f31 < 0.0f) {
        temp_f31 += 360.0f;
    }
    if (temp_f31 > 180.0f) {
        temp_f31 -= 360.0f;
    }
    temp_f31 = fmodf((arg2 * temp_f31) + arg0, 360.0);
    if (temp_f31 < 0.0f) {
        temp_f31 += 360.0f;
    }
    return temp_f31;
}

float fn_1_67AC(float arg0, float arg1)
{
    float temp_f31;
    temp_f31 = fmodf(arg1 - arg0, 360.0);
    if (temp_f31 < 0.0f) {
        temp_f31 += 360.0f;
    }
    if (temp_f31 > 180.0f) {
        temp_f31 -= 360.0f;
    }
    return temp_f31;
}
