#include "datadir_enum.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/pad.h"
#include "string.h"

#include "REL/m460Dll.h"
#include "version.h"

#ifndef __MWERKS__
#include "game/frand.h"
#endif

typedef struct UnkData110Struct {
    /* 0x00 */ u16 unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ u32 unk_10;
} UnkData110Struct; /* size = 0x14 */

typedef struct UnkM460DllPlayerWork {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    u32 unk_14;
    u32 unk_18;
    float unk_1C;
    float unk_20;
    s32 unk_24;
    s32 unk_28;
    u16 unk_2C;
    s32 unk_30;
    char unk34[0x4];
    s16 unk_38;
    char unk3A[6];
    s32 unk_40;
    float unk_44;
    float unk_48;
    float unk_4C;
    float unk_50;
    float unk_54;
    s32 unk_58;
    float unk_5C;
    Vec unk_60;
    Vec unk_6C;
    Vec unk_78;
    s32 unk_84;
} UnkM460DllPlayerWork; /* size = 0x88 */

void fn_1_4C08(omObjData *object);
void fn_1_4F6C(omObjData *object);
void fn_1_5168(omObjData *object);
void fn_1_55EC(omObjData *object);
void fn_1_57D8(omObjData *object);
s32 fn_1_58C8(omObjData *object, float arg8, float arg9);
void fn_1_5A14(omObjData *object);
void fn_1_5C88(omObjData *object);
void fn_1_5CE0(omObjData *object, u32 arg1);
s32 fn_1_5E6C(omObjData *object);
void fn_1_60B0(omObjData *object);
void fn_1_61F4(omObjData *object);

u32 lbl_1_data_F0[8] = { 0, 2, 3, 0x590015, 0x59000D, 0x17, 0x18, 0x1A };
struct UnkData110Struct lbl_1_data_110[8] = {
    { 0, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 1, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 2, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 3, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 4, 0.2f, 0.0f, -1.0f, 0 },
    { 5, 0.2f, 0.0f, -1.0f, 0 },
    { 6, 0.2f, 0.0f, -1.0f, 0 },
    { 7, 0.2f, 0.0f, -1.0f, 0x40000001 },
};

omObjData *lbl_1_bss_40[1];
omObjData *lbl_1_bss_3C;
s32 lbl_1_bss_38[1];

void fn_1_49A0(Process *process)
{
    u32 spC[1];
    u32 sp8[1];

    s16 var_r31;
    s16 var_r30;
    u32 var_r29;
    omObjData *var_r27;

    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        spC[var_r31] = GWPlayerCfg[var_r31].group;
        sp8[var_r31] = var_r31;
    }
    for (var_r31 = 0; var_r31 < 0; var_r31++) {
        for (var_r30 = var_r31 + 1; var_r30 < 1; var_r30++) {
            if (spC[var_r31] > spC[var_r30]) {
                var_r29 = spC[var_r31];
                spC[var_r31] = spC[var_r30];
                spC[var_r30] = var_r29;
                var_r29 = sp8[var_r31];
                sp8[var_r31] = sp8[var_r30];
                sp8[var_r30] = var_r29;
            }
        }
    }
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        lbl_1_bss_38[sp8[var_r31]] = var_r31;
    }
    omMakeGroupEx(process, 0, 1);
    omGetGroupMemberListEx(process, 0);
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        var_r27 = lbl_1_bss_40[var_r31] = omAddObjEx(process, 0x28, 1, 8, 0, fn_1_4C08);
        var_r27->work[0] = var_r31;
    }
    lbl_1_bss_3C = omAddObjEx(process, 0x28, 1, 5, -1, fn_1_60B0);
}

void fn_1_4BE4(void)
{
    CharModelKill(-1);
}

void fn_1_4C08(omObjData *object)
{
    UnkM460DllPlayerWork *var_r31;
    s32 var_r29;

    float sp8[4] = { 0.25f, 0.5f, 0.75f, 1.0f };
    Vec sp18[4] = {
        { 0.0f, 0.0f, 300.0f },
        { -450.0f, 0.0f, -50.0f },
        { 0.0f, 0.0f, -350.0f },
        { 450.0f, 0.0f, -50.0f },
    };
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM460DllPlayerWork), MEMORY_DEFAULT_NUM);
    var_r31 = object->data;
    memset(var_r31, 0, sizeof(UnkM460DllPlayerWork));
    object->stat |= 0x100;
    var_r31->unk_00 = GWPlayerCfg[object->work[0]].character;
    var_r31->unk_08 = lbl_1_bss_38[object->work[0]];
    fn_1_41B4(object->work[0], var_r31->unk_08, var_r31->unk_00);
    var_r31->unk_54 = sp8[GWPlayerCfg[object->work[0]].diff & 3];
    var_r31->unk_24 = GWPlayerCfg[object->work[0]].iscom;
    object->model[0] = CharModelCreate(var_r31->unk_00, 2);
    Hu3DModelLayerSet(object->model[0], 1);
    CharModelLayerSetAll(2);
    Hu3DModelShadowSet(object->model[0]);
    for (var_r29 = 0; var_r29 < 8; var_r29++) {
        if (lbl_1_data_F0[var_r29] < 0x10000) {
            object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_00, lbl_1_data_F0[var_r29]);
        }
        else {
            object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], var_r31->unk_00 + lbl_1_data_F0[var_r29]);
        }
    }
    CharModelMotionDataClose(var_r31->unk_00);
    CharModelEffectNpcInitSilent(object->model[0], object->motion[3], 1);
    object->trans.x = var_r31->unk_60.x = sp18[var_r31->unk_08].x;
    object->trans.y = var_r31->unk_60.y = sp18[var_r31->unk_08].y;
    object->trans.z = var_r31->unk_60.z = sp18[var_r31->unk_08].z;
    var_r31->unk_44 = var_r31->unk_48 = 0.0f;
    var_r31->unk_4C = 0.0f;
    var_r31->unk_50 = 0.02f;
    var_r31->unk_5C = 50.0f;
    var_r31->unk_58 = 0;
    var_r31->unk_2C = 0;
    var_r31->unk_04 = -1;
    fn_1_5CE0(object, 0);
    var_r31->unk_84 = -1;
    object->func = fn_1_4F6C;
}

void fn_1_4F6C(omObjData *object)
{
    UnkM460DllPlayerWork *var_r31;
    s32 var_r29;

    var_r31 = object->data;
    var_r31->unk_14 = var_r31->unk_18 = 0;
    var_r31->unk_0C = var_r31->unk_10 = 0;
    var_r31->unk_1C = 0.0f;
    var_r31->unk_20 = 0.0f;
    switch (var_r31->unk_2C) {
        case 0:
            var_r31->unk_44 = var_r31->unk_48 = 180.0f;
            var_r31->unk_60.x = 0.0f;
            var_r31->unk_60.y = 0.0f;
            var_r31->unk_60.z = -450.0f;
            fn_1_5CE0(object, 7);
            var_r31->unk_2C = 1;
            var_r31->unk_30 = 0;
            break;
        case 1:
            if (fn_1_414C() == 1) {
                var_r31->unk_60.x = 0.0f;
                var_r31->unk_60.y = 0.0f;
                var_r31->unk_60.z = -100.0f;
                var_r31->unk_78.x = 0.0f;
                var_r31->unk_78.y = 0.0f;
                var_r31->unk_78.z = -450.0f;
                var_r31->unk_2C = 2;
                var_r31->unk_30 = 0;
            }
            break;
        case 2:
            var_r29 = fn_1_58C8(object, 0.5f, 20.0f);
            fn_1_5A14(object);
            if (var_r29 != 0) {
                var_r31->unk_2C = 3;
                var_r31->unk_30 = 0;
            }
            break;
    }
    VECAdd(&var_r31->unk_60, &var_r31->unk_6C, &var_r31->unk_60);
    fn_1_57D8(object);
    if (fn_1_414C() == 2) {
        var_r31->unk_2C = 0;
        object->func = fn_1_5168;
    }
}

void fn_1_5168(omObjData *object)
{
    UnkM460DllPlayerWork *var_r31;
    s32 var_r29;
    u32 var_r28;
    s32 var_r27;

    var_r31 = object->data;
    var_r27 = 0;
    {
        Vec sp20[2] = {
            { -250.0f, 0.0f, -900.0f },
            { 250.0f, 0.0f, -900.0f },
        };

        Vec sp8[2] = {
            { -250.0f, 0.0f, -1400.0f },
            { 250.0f, 0.0f, -1400.0f },
        };
        var_r31->unk_14 = var_r31->unk_18 = 0;
        var_r31->unk_0C = var_r31->unk_10 = 0;
        var_r31->unk_1C = 0.0f;
        var_r31->unk_20 = 0.0f;
        if (fn_1_4164() == 2) {
            if (var_r31->unk_24 != 0) {
                fn_1_5C88(object);
            }
            else {
                if (HuPadTrigL[GWPlayerCfg[object->work[0]].pad_idx] > 0x28) {
                    var_r31->unk_14 = 1;
                }
                if (HuPadTrigR[GWPlayerCfg[object->work[0]].pad_idx] > 0x28) {
                    var_r31->unk_18 = 1;
                }
            }
        }
        switch (var_r31->unk_2C) {
            case 0:
                if (fn_1_4370() != 0) {
                    var_r31->unk_60.x = -140.0f;
                    var_r31->unk_60.y = 0.0f;
                    var_r31->unk_60.z = -150.0f;
                }
                var_r31->unk_78.x = 0.0f;
                var_r31->unk_78.y = 0.0f;
                var_r31->unk_78.z = -450.0f;
                var_r31->unk_40 = 3;
                var_r31->unk_2C = 4;
            case 4:
                var_r29 = fn_1_58C8(object, 0.5f, 20.0f);
                fn_1_5A14(object);
                if ((var_r29 != 0) && (fn_1_4164() == 2)) {
                    var_r31->unk_48 = 180.0f;
                    var_r31->unk_6C.x = var_r31->unk_6C.y = var_r31->unk_6C.z = 0.0f;
                    var_r31->unk_2C = 5;
                }
                break;
            case 5:
                var_r29 = 0;
                fn_1_5A14(object);
                if (CharModelMotionShiftIDGet(var_r31->unk_00) < 0) {
                    var_r29 = 1;
                }
                var_r28 = fn_1_42F0();
                if (var_r28 == 3) {
                    if (var_r29 != 0) {
                        if (var_r31->unk_14 != 0) {
                            var_r28 = 0;
                        }
                        else if (var_r31->unk_18 != 0) {
                            var_r28 = 1;
                        }
                        if (var_r28 != 3) {
                            fn_1_42BC(var_r28);
                        }
                    }
                }
                else {
                    var_r31->unk_40 = var_r28;
                    var_r31->unk_78 = sp20[var_r31->unk_40];
                    var_r31->unk_2C = 6;
                }
                break;
            case 6:
                var_r29 = fn_1_58C8(object, 1.0f, 20.0f);
                fn_1_5A14(object);
                if (var_r29 != 0) {
                    fn_1_4308();
                    var_r31->unk_48 = 180.0f;
                    var_r31->unk_6C.x = var_r31->unk_6C.y = var_r31->unk_6C.z = 0.0f;
                    var_r31->unk_2C = 7;
                }
                break;
            case 7:
                fn_1_5A14(object);
                if (fn_1_4358() != 0) {
                    if (fn_1_419C() == 0) {
                        var_r31->unk_78 = sp8[var_r31->unk_40];
                        var_r31->unk_2C = 8;
                    }
                    else {
                        var_r27 = 1;
                    }
                }
                break;
            case 8:
                var_r29 = fn_1_58C8(object, 0.5f, 20.0f);
                fn_1_5A14(object);

            default:
                if (fn_1_4164() == 1) {
                    var_r31->unk_2C = 0;
                }
                var_r27 = 1;
                break;
        }
    }
    VECAdd(&var_r31->unk_60, &var_r31->unk_6C, &var_r31->unk_60);
    fn_1_57D8(object);
    if ((fn_1_4164() == 5) && (var_r27 != 0)) {
        var_r31->unk_2C = 0;
        object->func = fn_1_55EC;
    }
}

void fn_1_55EC(omObjData *object)
{
    Vec sp8;
    UnkM460DllPlayerWork *var_r31;
    s32 var_r29;

    var_r31 = object->data;
    var_r29 = 0;
    switch (var_r31->unk_2C) {
        case 0:
            fn_1_41F4(object->work[0]);
            fn_1_5CE0(object, 4);
            sp8 = var_r31->unk_60;
            sp8.y += 160.0f;
            var_r31->unk_2C = 9;
            break;
        case 9:
            if (fn_1_5E6C(object) != 0) {
                var_r31->unk_78.x = 0.0f;
                var_r31->unk_78.y = 0.0f;
                var_r31->unk_78.z = 500.0f;
                fn_1_4224(object->work[0]);
                HuAudCharVoicePlay(var_r31->unk_00, 0x128);
                var_r31->unk_28 = 1;
                var_r31->unk_2C = 0xA;
            }
            break;
        case 10:
            var_r29 = fn_1_58C8(object, 1.0f, 20.0f);
            fn_1_5A14(object);
            if (var_r29 != 0) {
                var_r31->unk_6C.x = var_r31->unk_6C.y = var_r31->unk_6C.z = 0.0f;
                var_r31->unk_2C = 0xB;
            }
            break;
        case 11:
            fn_1_5CE0(object, 0);
            break;
    }
    VECAdd(&var_r31->unk_60, &var_r31->unk_6C, &var_r31->unk_60);
    fn_1_57D8(object);
    if (var_r31->unk_84 >= 0) {
        sp8 = var_r31->unk_60;
        sp8.y += 160.0f;
        HuAudFXEmiterUpDate(var_r31->unk_84, &sp8);
    }
}

void fn_1_57D8(omObjData *object)
{
    UnkM460DllPlayerWork *var_r31 = object->data;
    var_r31->unk_38++;
    var_r31->unk_30++;
    object->trans.x = var_r31->unk_60.x;
    object->trans.y = var_r31->unk_60.y;
    object->trans.z = var_r31->unk_60.z;
    var_r31->unk_4C = var_r31->unk_4C + var_r31->unk_50;
    if (var_r31->unk_4C > 0.45f) {
        var_r31->unk_4C = 0.45f;
    }
    var_r31->unk_44 = fn_1_47D0(var_r31->unk_44, var_r31->unk_48, var_r31->unk_4C);
    object->rot.y = var_r31->unk_44;
    Hu3DModelPosSetV(object->model[0], &var_r31->unk_60);
    Hu3DModelRotSet(object->model[0], 0.0f, var_r31->unk_44, 0.0f);
}

s32 fn_1_58C8(omObjData *object, float arg8, float arg9)
{
    Vec spC;
    float var_f31;
    UnkM460DllPlayerWork *var_r31;
    s32 var_r30;

    var_r31 = object->data;
    var_r30 = 0;
    VECSubtract(&var_r31->unk_78, &var_r31->unk_60, &spC);
    spC.y = 0.0f;
    var_f31 = VECMag(&spC);
    if (var_f31 < arg9) {
        var_f31 = 0.0f;
        var_r30 = 1;
    }
    else {
        if (VECMag(&spC) >= 100.0f) {
            var_f31 = 100.0f;
        }
        var_f31 = 0.2f + (0.008f * var_f31);
    }
    var_r31->unk_1C = atan2d(spC.x, spC.z);
    var_r31->unk_20 = var_f31;
    if (var_r31->unk_20 > arg8) {
        var_r31->unk_20 = arg8;
    }
    return var_r30;
}

void fn_1_5A14(omObjData *object)
{
    float var_f31;
    float var_f30;

    UnkM460DllPlayerWork *var_r31 = object->data;
    if (var_r31->unk_20 > 0.0f) {
        var_r31->unk_48 = var_r31->unk_1C;
    }
    if (var_r31->unk_20 > 0.05f) {
        // 1 / REFRESH_RATE?
        var_r31->unk_6C.x = REFRESH_FREQ * (550.0 * (var_r31->unk_20 * sind(var_r31->unk_1C)));
        var_r31->unk_6C.z = REFRESH_FREQ * (550.0 * (var_r31->unk_20 * cosd(var_r31->unk_1C)));
        if (var_r31->unk_28 != 0) {
            var_r31->unk_6C.x *= 1.5f;
            var_r31->unk_6C.z *= 1.5f;
        }
        var_r31->unk_4C = 0.2f;
        var_r31->unk_50 = 0.0f;
        if (CharModelMotionShiftIDGet(var_r31->unk_00) < 0) {
            var_f31 = 0.5f;
            if (var_r31->unk_04 == 2) {
                var_f31 = 0.45f;
            }
            if (var_r31->unk_20 > var_f31) {
                if (var_r31->unk_28 != 0) {
                    fn_1_5CE0(object, 3);
                }
                else {
                    fn_1_5CE0(object, 2);
                }
                var_f30 = var_r31->unk_20;
            }
            else {
                fn_1_5CE0(object, 1);
                var_f30 = var_r31->unk_20 / var_f31;
            }
            CharModelMotionSpeedSet(var_r31->unk_00, var_f30);
        }
    }
    else {
        var_r31->unk_6C.x = var_r31->unk_6C.y = var_r31->unk_6C.z = 0.0f;
        if (CharModelMotionShiftIDGet(var_r31->unk_00) < 0) {
            fn_1_5CE0(object, 0);
        }
    }
}

void fn_1_5C88(omObjData *object)
{
    UnkM460DllPlayerWork *var_r31 = object->data;
    if (frandmod(0x3E8) < 0x1F4) {
        var_r31->unk_14 = 1;
        return;
    }
    var_r31->unk_18 = 1;
}

void fn_1_5CE0(omObjData *object, u32 arg1)
{
    UnkM460DllPlayerWork *var_r30 = object->data;
    if ((var_r30->unk_04 != arg1) && (arg1 < 8)) {
        float var_f31 = REFRESH_RATE_F * lbl_1_data_110[arg1].unk_04;
        if (var_r30->unk_04 < 0) {
            var_f31 = 0.0f;
        }
        var_r30->unk_04 = arg1;
        CharModelMotionShiftSet(
            var_r30->unk_00, object->motion[lbl_1_data_110[arg1].unk_00], REFRESH_RATE_F * lbl_1_data_110[arg1].unk_08, var_f31, lbl_1_data_110[arg1].unk_10);
        if (lbl_1_data_110[arg1].unk_0C >= 0.0f) {
            Hu3DMotionShiftStartEndSet(object->model[0], REFRESH_RATE_F * lbl_1_data_110[arg1].unk_08, REFRESH_RATE_F * lbl_1_data_110[arg1].unk_0C);
        }
    }
}

s32 fn_1_5E6C(omObjData *object)
{
    M460DllCameraStruct *var_r31 = object->data;
    s32 var_r30 = 0;
    if ((CharModelMotionEndCheck(var_r31->unk_00) != 0) && (CharModelMotionShiftIDGet(var_r31->unk_00) < 0)) {
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_5EE0(omObjData *object, u32 arg1)
{
    s32 var_r27 = 0;
    if (fn_1_5E6C(object)) {
        fn_1_5CE0(object, arg1);
        var_r27 = 1;
    }
    return var_r27;
}

s32 lbl_1_data_1D4[5] = {
    DATA_MAKE_NUM(DATADIR_M460, 0x1E),
    DATA_MAKE_NUM(DATADIR_M460, 0x1F),
    DATA_MAKE_NUM(DATADIR_M460, 0x20),
    DATA_MAKE_NUM(DATADIR_M460, 0x21),
    DATA_MAKE_NUM(DATADIR_M460, 0x22),
};

void fn_1_60B0(omObjData *object)
{
    s32 var_r30;
    s32 var_r29;

    omSetTra(object, 0.0f, 0.0f, 0.0f);
    var_r30 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M460, 0x1D));
    object->model[0] = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelShadowSet(var_r30);
    Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    for (var_r29 = 0; var_r29 < 5; var_r29++) {
        object->motion[var_r29] = Hu3DJointMotionFile(var_r30, lbl_1_data_1D4[var_r29]);
    }
    CharModelEffectNpcInitSilent(var_r30, object->motion[1], 0);
    CharModelEffectNpcInitSilent(var_r30, object->motion[2], 1);
    CharModelEffectNpcInitSilent(var_r30, object->motion[3], 1);
    object->work[1] = 0;
    object->func = fn_1_61F4;
}

void fn_1_61F4(omObjData *object)
{
    float var_f31;
    float var_f30;
    s32 var_r30;
    s32 var_r29;

    Vec sp1C[2] = {
        { -250.0f, 0.0f, -2200.0f },
        { 250.0f, 0.0f, -2200.0f },
    };
    Vec sp10;
    s32 sp8[2] = { 6, 21 };
    switch (object->work[1]) {
        case 0:
            if ((fn_1_4164() == 3) && (fn_1_419C() != 0) && (fn_1_4324() != 0)) {
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
                Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
                var_r30 = fn_1_42F0();
                object->trans.x = sp1C[var_r30].x;
                object->trans.y = sp1C[var_r30].y;
                object->trans.z = sp1C[var_r30].z;
                object->rot.y = 0.0f;
                object->work[1] = 1;
                object->work[2] = 0;
            }
            break;
        case 1:
            object->work[2]++;
            if (object->work[2] > 0.3f * REFRESH_RATE_F) {
                Hu3DMotionShiftSet(object->model[0], object->motion[2], 0.0f, REFRESH_RATE_F / 2, HU3D_MOTATTR_LOOP);
                object->work[1] = 2;
            }
            break;
        case 2:
            sp10.x = (*lbl_1_bss_40)->trans.x - object->trans.x;
            sp10.y = 0.0f;
            sp10.z = (*lbl_1_bss_40)->trans.z - object->trans.z;
            object->rot.y = fn_1_47D0(object->rot.y, atan2d(sp10.x, sp10.z), 0.1f);
            object->trans.z += 400.0f * REFRESH_FREQ;
            if (fn_1_4358() != 0) {
                HuAudFXPlay(0x3C);
                Hu3DMotionShiftSet(object->model[0], object->motion[3], 0.0f, REFRESH_RATE_F / 2, HU3D_MOTATTR_LOOP);
                object->work[1] = 3;
                object->work[3] = REFRESH_RATE;
            }
            break;
        case 3:
            Hu3DMotionSpeedSet(object->model[0], 0.9f);
            var_r29 = Hu3DMotionTimeGet(object->model[0]);
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                if (var_r29 == sp8[var_r30]) {
                    var_f30 = 127.0f / REFRESH_RATE_F * object->work[3];
                    HuAudFXPlayVol(0x6B, var_f30);
                }
            }
            sp10.x = (*lbl_1_bss_40)->trans.x - object->trans.x;
            sp10.y = 0.0f;
            sp10.z = (*lbl_1_bss_40)->trans.z - object->trans.z;
            object->rot.y = fn_1_47D0(object->rot.y, atan2d(sp10.x, sp10.z), 0.1f);
            if (object->trans.z < -900.0f) {
                object->trans.z += 700.0f / REFRESH_RATE_F;
            }
            else {
                var_f31 = VECMag(&sp10);
                if (var_f31 < 20.0f) {
                    var_f31 = 0.0f;
                }
                else {
                    if (VECMag(&sp10) >= 100.0f) {
                        var_f31 = 100.0f;
                    }
                    var_f31 = 0.2f + (0.008f * var_f31);
                    var_f31 *= 700.0f / REFRESH_RATE_F;
                }
                object->trans.x = object->trans.x + (var_f31 * sind(object->rot.y));
                object->trans.z = object->trans.z + (var_f31 * cosd(object->rot.y));
            }
            if ((object->trans.z > 450.0f) && (object->work[3] != 0)) {
                object->work[3]--;
            }
            break;
    }
}
