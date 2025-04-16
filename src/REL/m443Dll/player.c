#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/frand.h"
#endif

#include "REL/m443Dll.h"

typedef struct M443DllUnkStruct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    Vec2f unkC;
    s16 unk14[11];
} M443DllUnkStruct;

typedef struct M443DllWorkStruct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u32 unk10;
    s32 unk14;
    f32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    char unk28[0xC];
    u16 unk34;
    s32 unk38;
    char unk3C[0x4];
    s16 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    s32 unk60;
    f32 unk64;
    u32 unk68;
    f32 unk6C;
    f32 unk70;
    u32 unk74;
    f32 unk78;
    f32 unk7C;
    u32 unk80;
    u32 unk84;
    f32 unk88;
    char unk8C[0x4];
    f32 unk90;
    f32 unk94;
    f32 unk98;
    f32 unk9C;
    f32 unkA0;
    f32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s32 unkB4;
    s32 unkB8;
    f32 unkBC;
    f32 unkC0;
    Vec unkC4;
    Vec unkD0;
    Vec unkDC;
    Vec unkE8;
    char unkF4[0xC];
    M443DllCameraStruct *unk100;
    M443DllCameraStruct *unk104;
    union {
        M443DllUnkStruct unk108s;
        struct {
            s32 unk108;
            s32 unk10C;
        };
    };
} M443DllWorkStruct; /* size = 0x134 */

typedef struct M443DllStruct8 {
    u16 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u32 unk10;
} M443DllStruct8; // copy of UnkM417Struct8

void fn_1_5680(omObjData *object);
void fn_1_5BD4(omObjData *object);
void fn_1_6458(omObjData *object);
void fn_1_6674(omObjData *object);
void fn_1_6750(omObjData *object);
void fn_1_69B4(omObjData *object);
void fn_1_6B90(omObjData *object);
void fn_1_6DA8(omObjData *object);
void fn_1_7130(omObjData *object);
void fn_1_7340(omObjData *object);
void fn_1_8138(omObjData *, u32);
s32 fn_1_82C4(omObjData *object);
void fn_1_8508(omObjData *);
void fn_1_8680(omObjData *object);
f32 fn_1_8AC8(u32, f32);
f32 fn_1_8C68(f32);
f32 fn_1_8C8C(s32, f32);
f32 fn_1_8D00(u32, f32);
f32 fn_1_8D74(f32);
void fn_1_8E34(s32);
void fn_1_8FFC(u32, Vec *, f32, f32);
void fn_1_95A4(u32);

omObjData *lbl_1_bss_90[4];
s32 lbl_1_bss_78[6];

char *lbl_1_data_264[0x8] = { "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r" };
u32 lbl_1_data_284[8][2] = {
    { 0x4A0005, 0x4A0006 },
    { 0x4A0007, 0x4A0008 },
    { 0x4A0009, 0x4A000A },
    { 0x4A000B, 0x4A000C },
    { 0x4A000D, 0x4A000E },
    { 0x4A000F, 0x4A0010 },
    { 0x4A0011, 0x4A0012 },
    { 0x4A0013, 0x4A0014 },
};
u32 lbl_1_data_2C4[4] = { 0, 0x4A0020, 0x17, 0x72 };

M443DllStruct8 lbl_1_data_2D4[4] = { { 0x0, 0.2f, 0.0f, -1.0f, 0x40000001 }, { 0x1, 0.2f, 0.0f, -1.0f, 0x40000001 }, { 0x2, 0.2f, 0.0f, -1.0f, 0x0 },
    { 0x3, 0.2f, 0.0f, -1.0f, 0x0 } };

s32 lbl_1_data_324[4] = {
    0x727,
    0x728,
    0x729,
    0x72A,
};
s32 lbl_1_data_334[4] = {
    0x72B,
    0x72C,
    0x72D,
    0x72E,
};
s32 lbl_1_data_344[4] = {
    0x72F,
    0x730,
    0x731,
    0x732,
};
s32 lbl_1_data_354[4] = {
    0x736,
    0x737,
    0x738,
    0x739,
};
Vec lbl_1_data_364[4] = { { 0.0f, 180.0f, 500.0f }, { -150.0f, 110.0f, 500.0f }, { 170.0f, 80.0f, 500.0f }, { 350.0f, 0.0f, 500.0f } };
Vec lbl_1_data_394[4] = { { -225.0f, 0.0f, 1000.0f }, { -75.0f, 0.0f, 1000.0f }, { 75.0f, 0.0f, 1000.0f }, { 225.0f, 0.0f, 1000.0f } };
Vec lbl_1_data_3C4[4] = { { 250.0f, 0.0f, -1000.0f }, { -350.0f, 0.0f, -1700.0f }, { 450.0f, 0.0f, -2200.0f }, { 0.0f, 0.0f, -3000.0f } };

void fn_1_5444(Process *arg0)
{
    u32 sp18[4];
    u32 sp8[4];
    omObjData *var_r28;
    u32 var_r29;
    s16 var_r30;
    s16 var_r31;

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
        lbl_1_bss_78[sp8[var_r31]] = (s16)var_r31;
    }
    omMakeGroupEx(arg0, 0, 4);
    omGetGroupMemberListEx(arg0, 0);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r28 = lbl_1_bss_90[var_r31] = omAddObjEx(arg0, 0x28, 5, 4, 0, fn_1_5680);
        var_r28->work[0] = var_r31;
    }
}

void fn_1_565C(void)
{
    CharModelKill(-1);
}

void fn_1_5680(omObjData *object)
{
    f32 spC[4] = { 0.25f, 0.5f, 0.75f, 1.0f };
    s32 sp8;
    s32 temp_r27;
    s32 temp_r3;
    s32 var_r29;
    u32 temp_r25;
    M443DllWorkStruct *temp_r31;
    HsfanimStruct01 *var_r28;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M443DllWorkStruct), MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    memset(temp_r31, 0, 0x134);
    object->stat |= 0x100;
    temp_r25 = object->work[0];
    temp_r27 = GWPlayerCfg[temp_r25].character;
    temp_r31->unk0 = temp_r27;
    sp8 = temp_r31->unk4 = 0;
    temp_r31->unkC = lbl_1_bss_78[object->work[0]];
    temp_r31->unk5C = spC[GWPlayerCfg[temp_r25].diff & 3];
    temp_r31->unk24 = GWPlayerCfg[object->work[0]].iscom;
    object->model[0] = CharModelCreate(temp_r27, 8);
    Hu3DModelLayerSet(object->model[0], 4);
    object->model[1] = Hu3DModelCreateFile(lbl_1_data_284[temp_r27][0]);
    Hu3DModelLayerSet(object->model[1], 4);
    Hu3DMotionSpeedSet(object->model[1], 0.0f);
    object->model[2] = Hu3DModelCreateFile(lbl_1_data_284[temp_r27][1]);
    Hu3DModelLayerSet(object->model[2], 4);
    Hu3DMotionSpeedSet(object->model[2], 0.0f);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);

    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (lbl_1_data_2C4[var_r29] < 0x10000) {
            object->motion[var_r29] = CharModelMotionCreate(temp_r27, lbl_1_data_2C4[var_r29]);
        }
        else {
            object->motion[var_r29]
                = Hu3DJointMotion(object->model[0], HuDataSelHeapReadNum(temp_r27 + lbl_1_data_2C4[var_r29], 0x10000000, HEAP_DATA));
        }
    }
    CharModelMotionDataClose(temp_r27);
    temp_r3 = Hu3DParticleCreate(HuSprAnimReadFile(0x4A001D), 0xC8);
    object->model[3] = temp_r3;
    Hu3DModelLayerSet(temp_r3, 4);
    var_r28 = ((ParticleData *)Hu3DData[temp_r3].unk_120)->unk_48;

    for (var_r29 = 0; var_r29 < 0xC8; var_r29++, var_r28++) {
        var_r28->unk2C = 0.0f;
        var_r28->unk40.a = 0;
        var_r28->unk00 = 0;
    }

    object->trans.x = temp_r31->unkC4.x = temp_r31->unkDC.x = (100.0f * (4.0f * object->work[0])) - 600.0f;
    object->trans.y = temp_r31->unkC4.y = temp_r31->unkDC.y = 0.0f;
    object->trans.z = temp_r31->unkC4.z = temp_r31->unkDC.z = 0.0f;

    temp_r31->unkD0.x = temp_r31->unkD0.y = temp_r31->unkD0.z = 0.0f;
    temp_r31->unkE8.x = temp_r31->unkE8.y = temp_r31->unkE8.z = 0.0f;
    temp_r31->unk48 = temp_r31->unk4C = 0.0f;
    temp_r31->unk50 = 0.0f;
    temp_r31->unk54 = 0.02f;
    temp_r31->unk58 = 180.0f;
    temp_r31->unkC0 = 50.0f;
    temp_r31->unkBC = 350.0f;
    temp_r31->unk8 = -1;
    temp_r31->unk1C = 1;
    temp_r31->unk20 = 0;
    temp_r31->unk9C = 1.0f;
    temp_r31->unk98 = 0.0f;
    temp_r31->unkA0 = 0.0f;
    temp_r31->unkA4 = 0.0f;
    temp_r31->unk88 = 1000.0f;
    temp_r31->unk90 = fn_1_8C8C(temp_r31->unk80, temp_r31->unk88);
    temp_r31->unkA8 = temp_r31->unkAC = -1;
    temp_r31->unkB0 = temp_r31->unkB4 = temp_r31->unkB8 = -1;
    temp_r31->unkB4 = HuAudFXPlay(lbl_1_data_334[object->work[0]]);
    temp_r31->unk68 = -1;
    temp_r31->unk60 = 0;
    temp_r31->unk100 = fn_1_4148(object->work[0] + 1);
    temp_r31->unk104 = fn_1_41B0(object->work[0] + 1);
    temp_r31->unk100->unk_00 = 0;
    fn_1_8508(object);
    temp_r31->unk34 = 0;
    object->func = fn_1_5BD4;
}

void fn_1_5BD4(omObjData *object)
{
    Vec sp8;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    M443DllWorkStruct *temp_r31;

    temp_r31 = object->data;
    temp_r31->unk10 = 0;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0.0f;
    if (temp_r31->unk108 != 0) {
        if (temp_r31->unk24 != 0) {
            fn_1_6DA8(object);
        }
        else {
            temp_r31->unk14 = HuPadBtn[GWPlayerCfg[object->work[0]].pad_idx];
            temp_r31->unk10 = HuPadBtnDown[GWPlayerCfg[object->work[0]].pad_idx];
            var_f29 = HuPadTrigR[GWPlayerCfg[object->work[0]].pad_idx];
            if (var_f29 > 140.0f) {
                var_f29 = 140.0f;
            }
            temp_r31->unk18 = (1.0f / 140.0f) * var_f29;
        }
    }
    switch (temp_r31->unk34) {
        case 0:
            temp_r31->unk100->unk_1C = temp_r31->unkDC;
            temp_r31->unk100->unk_54.y = 150.0f;
            temp_r31->unk100->unk_1C.y += temp_r31->unk100->unk_54.y;
            temp_r31->unk100->unk_28.x = -30.0f;
            temp_r31->unk100->unk_28.y = 90.0f;
            temp_r31->unk100->unk_34 = 500.0f;
            temp_r31->unk100->unk_6C = -20.0f - frandmod(10);
            temp_r31->unk100->unk_70 = 160.0f + frandmod(0x28);
            temp_r31->unk100->unk_78 = temp_r31->unk100->unk_44;
            temp_r31->unk100->unk_7C = temp_r31->unk100->unk_48;
            temp_r31->unk100->unk_80 = temp_r31->unk100->unk_40;
            if ((temp_r31->unk40 < 120.0f) && ((temp_r31->unk40 % 60) > 10)) {
                temp_r31->unk18 = 1.0f;
            }
            if (fn_1_3FFC() == 2) {
                temp_r31->unk34++;
                temp_r31->unk40 = 0;
                temp_r31->unkB0 = HuAudFXPlay(lbl_1_data_324[object->work[0]]);
            }
            break;
        case 1:
            temp_r31->unk100->unk_00 = 1;
            var_f31 = (5.0f / 600.0f) * temp_r31->unk40;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            var_f30 = 2.0f * (var_f31 - 0.5f);
            if (var_f30 < 0.0f) {
                var_f30 = 0.0f;
            }
            var_f30 = var_f30 * var_f30;
            sp8.x = 320.0 + 160.0 * (var_f31 * cosd(450.0f * var_f31 + 90.0f * object->work[0]));
            sp8.y = 240.0 + 120.0 * (var_f31 * sind(450.0f * var_f31 + 90.0f * object->work[0]));
            temp_r31->unk100->unk_44 = sp8.x + (var_f30 * (temp_r31->unk100->unk_78 - sp8.x));
            temp_r31->unk100->unk_48 = sp8.y + (var_f30 * (temp_r31->unk100->unk_7C - sp8.y));
            temp_r31->unk100->unk_40 = 0.01f + ((temp_r31->unk100->unk_80 - 0.01f) * var_f31);
            temp_r31->unk100->unk_28.y = 90.0f + ((temp_r31->unk100->unk_70 - 90.0f) * var_f31);
            temp_r31->unk100->unk_34 = 500.0f + (-200.0f * var_f30);
            if (var_f31 >= 1.0f) {
                temp_r31->unk108 = 1;
                if (temp_r31->unk40 >= 150.0f) {
                    fn_1_3FE8(4);
                    temp_r31->unk34++;
                    temp_r31->unk40 = 0;
                }
            }
            break;
        case 2:
            var_f31 = (5.0f / 600.0f) * temp_r31->unk40;
            if (var_f31 > 0.2f) {
                var_f31 = 0.2f;
            }
            temp_r31->unk100->unk_28.x = fn_1_488C(temp_r31->unk100->unk_28.x, -12.0f, var_f31);
            temp_r31->unk100->unk_28.y = fn_1_488C(temp_r31->unk100->unk_28.y, 0.0f, var_f31);
            temp_r31->unk100->unk_34 += ((1000.0f - temp_r31->unk100->unk_34) * (0.5f * var_f31));
            break;
    }
    fn_1_7340(object);
    VECAdd(&temp_r31->unkC4, &temp_r31->unkD0, &temp_r31->unkC4);
    fn_1_7130(object);
    fn_1_69B4(object);

    if (fn_1_42CC() == 2) {
        temp_r31->unk100->unk_1C = temp_r31->unkDC;
        temp_r31->unk100->unk_1C.y += 150.0f;
        temp_r31->unk100->unk_54.y = 150.0f;
        temp_r31->unk100->unk_28.x = -12.0f;
        temp_r31->unk100->unk_28.y = 0.0f;
        temp_r31->unk100->unk_34 = 1000.0f;
        temp_r31->unk34 = 0;
        object->func = &fn_1_6458;
    }
}

void fn_1_6458(omObjData *object)
{
    f32 var_f31;
    s32 var_r29;
    M443DllWorkStruct *temp_r31;

    temp_r31 = object->data;
    var_r29 = 0;
    temp_r31->unk10 = 0;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0.0f;
    if (temp_r31->unk24 != 0) {
        fn_1_6DA8(object);
    }
    else {
        temp_r31->unk14 = HuPadBtn[GWPlayerCfg[object->work[0]].pad_idx];
        temp_r31->unk10 = HuPadBtnDown[GWPlayerCfg[object->work[0]].pad_idx];
        var_f31 = HuPadTrigR[GWPlayerCfg[object->work[0]].pad_idx];
        if (var_f31 > 140.0f) {
            var_f31 = 140.0f;
        }
        temp_r31->unk18 = (1.0f / 140.0f) * var_f31;
    }
    switch (temp_r31->unk34) {
        case 0:
            fn_1_8138(object, 1);
            var_r29 = 1;
    }
    fn_1_7340(object);
    VECAdd(&temp_r31->unkC4, &temp_r31->unkD0, &temp_r31->unkC4);
    fn_1_7130(object);
    fn_1_69B4(object);
    temp_r31->unk100->unk_1C = temp_r31->unkDC;
    VECAdd(&temp_r31->unk100->unk_1C, &temp_r31->unk100->unk_54, &temp_r31->unk100->unk_1C);
    if ((fn_1_42E4() == 3) && (var_r29 != 0)) {
        fn_1_43AC(object->work[0]);
        temp_r31->unk108 = 0;
        temp_r31->unk34 = 0;
        object->func = fn_1_6674;
    }
}

void fn_1_6674(omObjData *object)
{
    M443DllWorkStruct *temp_r31;

    temp_r31 = object->data;
    temp_r31->unk10 = 0;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0.0f;
    fn_1_7340(object);
    VECAdd(&temp_r31->unkC4, &temp_r31->unkD0, &temp_r31->unkC4);
    fn_1_7130(object);
    fn_1_69B4(object);
    temp_r31->unk100->unk_1C = temp_r31->unkDC;
    VECAdd(&temp_r31->unk100->unk_1C, &temp_r31->unk100->unk_54, &temp_r31->unk100->unk_1C);
    if (fn_1_42E4() == 5) {
        temp_r31->unk1C = 0;
        temp_r31->unk34 = 0;
        object->func = fn_1_6750;
    }
}

void fn_1_6750(omObjData *object)
{
    M443DllWorkStruct *temp_r31;

    temp_r31 = object->data;
    VECAdd(&temp_r31->unkC4, &temp_r31->unkD0, &temp_r31->unkC4);
    fn_1_7130(object);
    fn_1_69B4(object);
    switch (temp_r31->unk34) {
        case 0:
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
            fn_1_95A4(object->work[0]);
            Hu3DModelShadowSet(object->model[0]);
            temp_r31->unk8 = -1;
            fn_1_8138(object, 0);
            if (fn_1_4368(object->work[0]) >= 0) {
                temp_r31->unkC4 = lbl_1_data_364[fn_1_4368(object->work[0])];
                temp_r31->unkDC = lbl_1_data_3C4[fn_1_4368(object->work[0])];
                temp_r31->unk58 = 30.0f;
            }
            else {
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
                temp_r31->unkC4 = lbl_1_data_394[object->work[0]];
            }
            temp_r31->unk34++;
            break;
        case 1:
            temp_r31->unk4C = 0.0f;
            temp_r31->unk50 = 0.15f;
            temp_r31->unk54 = 0.0f;
            temp_r31->unkD0.x = temp_r31->unkD0.y = temp_r31->unkD0.z = 0.0f;
            fn_1_43AC(object->work[0]);
            temp_r31->unk34++;
            break;
        case 2:
            if (fn_1_42FC() == 1) {
                if (fn_1_4368(object->work[0]) == 0) {
                    fn_1_8138(object, 2);
                }
                else {
                    fn_1_8138(object, 3);
                }
                temp_r31->unk34++;
            }
            break;
        case 3:
            if (fn_1_82C4(object) != 0) {
                fn_1_43DC(object->work[0]);
                temp_r31->unk34++;
            }
            break;
    }
}

void fn_1_69B4(omObjData *object)
{
    M443DllWorkStruct *temp_r31;

    temp_r31 = object->data;
    temp_r31->unk40++;
    temp_r31->unk38++;
    object->trans.x = temp_r31->unkC4.x;
    object->trans.y = temp_r31->unkC4.y;
    object->trans.z = temp_r31->unkC4.z;
    temp_r31->unk50 += temp_r31->unk54;
    if (temp_r31->unk50 > 0.45f) {
        temp_r31->unk50 = 0.45f;
    }
    temp_r31->unk48 = fn_1_488C(temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
    object->rot.y = temp_r31->unk48;
    if (temp_r31->unk1C != 0) {
        if (temp_r31->unk20 == 0) {
            Hu3DModelHookSet(object->model[1], "hook", object->model[0]);
        }

        temp_r31->unkDC.z = temp_r31->unkC4.z = -(temp_r31->unk78 - temp_r31->unkBC);
        fn_1_8138(object, 1);
    }
    else {
        if (temp_r31->unk20 != 0) {
            Hu3DModelHookReset(object->model[1]);
        }
        Hu3DModelPosSetV(object->model[0], &temp_r31->unkC4);
        Hu3DModelRotSet(object->model[0], 0.0f, temp_r31->unk48, 0.0f);
    }
    temp_r31->unk20 = temp_r31->unk1C;
    Hu3DModelPosSetV(object->model[1], &temp_r31->unkDC);
    Hu3DModelRotSet(object->model[1], 0.0f, temp_r31->unk58, 0.0f);
    Hu3DModelPosSetV(object->model[2], &temp_r31->unkDC);
    Hu3DModelRotSet(object->model[2], 0.0f, temp_r31->unk58, 0.0f);
}

void fn_1_6B90(omObjData *object)
{
    M443DllWorkStruct *temp_r29;
    M443DllWorkStruct *temp_r27 = object->data;
    s32 sp28[4][4] = {
        { 0, 1, 2, 3 },
        { 1, 0, 1, 2 },
        { 2, 1, 0, 1 },
        { 3, 2, 1, 0 },
    };
    f32 sp18[4] = { 0.0f, -700.0f, 600.0f, 1200.0f };
    s32 sp8[4] = { 2, 4, 8, 16 };
    f32 var_f31;
    s32 var_r28;
    u32 var_r30;

    var_r28 = sp8[object->work[0]] | 1;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        if (var_r30 != object->work[0]) {
            temp_r29 = lbl_1_bss_90[var_r30]->data;
            var_f31 = temp_r29->unk78;
            if (temp_r29->unk74 != temp_r27->unk74) {
                var_f31 += 1.6666667f * temp_r29->unk7C;
            }
            var_f31 = temp_r27->unk78 - var_f31;
            if (var_f31 > sp18[sp28[object->work[0]][var_r30]]) {
                var_r28 |= sp8[var_r30];
            }
        }
    }
    fn_1_421C(object->model[0], var_r28);
    fn_1_421C(object->model[1], var_r28);
    fn_1_421C(object->model[2], var_r28);
    fn_1_421C(object->model[3], var_r28);
}

void fn_1_6DA8(omObjData *object)
{
    f32 var_f31;
    M443DllWorkStruct *temp_r31;

    temp_r31 = object->data;
    switch (temp_r31->unk60) {
        case 0:
            var_f31 = 1.25f - temp_r31->unk5C;
            var_f31 *= 0.6f + (0.00040000002f * frandmod(0x3E8));
            if (frandmod(0x3E8) < 0x1F4) {
                var_f31 *= -1.0f;
            }
            temp_r31->unk64 = (3000.0f + (2000.0f * var_f31));
            temp_r31->unk60++;
            /* fallthrough */
        case 1:
            if (temp_r31->unk88 < temp_r31->unk64) {
                temp_r31->unk18 = 1.0f;
            }
            if (temp_r31->unkA0 >= 1.0f) {
                temp_r31->unk60 = (s32)(temp_r31->unk60 + 1);
            }
            break;
        case 2:
            temp_r31->unk18 = 1.0f;
            if (temp_r31->unk80 != temp_r31->unk68) {
                temp_r31->unk6C = temp_r31->unk70 = 0.0f;
                if (frandmod(0x3E8) < 0x1F4) {
                    var_f31 = 1.2f - temp_r31->unk5C;
                    var_f31 *= (0.5f + 0.0005f * frandmod(0x3E8));
                    temp_r31->unk6C = 8000.0f - 1500.0f * var_f31;
                }
                else {
                    var_f31 = 1.2f - temp_r31->unk5C;
                    var_f31 *= (0.5f + 0.0005f * frandmod(0x3E8));
                    temp_r31->unk70 = 0.016666668f + var_f31;
                }
            }
            temp_r31->unk68 = temp_r31->unk80;
            if (temp_r31->unk6C > 0.0f) {
                if (temp_r31->unk88 > temp_r31->unk6C) {
                    temp_r31->unk10 = (s32)(temp_r31->unk10 | 0x100);
                    temp_r31->unk6C = 0.0f;
                    break;
                }
            }
            else if (temp_r31->unk70 > 0.0f) {
                if (temp_r31->unk88 >= 8000.0f) {
                    temp_r31->unk70 = (temp_r31->unk70 - 0.016666668f);
                    if (temp_r31->unk70 <= 0.0f) {
                        temp_r31->unk10 = (s32)(temp_r31->unk10 | 0x100);
                        temp_r31->unk70 = 0.0f;
                    }
                }
            }
            break;
    }
}

void fn_1_7130(omObjData *object)
{
    Vec sp8;
    f32 var_f31;
    s32 var_r27;
    s32 var_r29;
    s32 var_r28;
    M443DllWorkStruct *temp_r30;
    M443DllWorkStruct *temp_r31;

    for (var_r27 = 0; var_r27 < 2; var_r27++) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            temp_r31 = lbl_1_bss_90[var_r29]->data;

            for (var_r28 = 0; var_r28 < 4; var_r28++) {
                if (var_r29 != var_r28) {
                    temp_r30 = lbl_1_bss_90[var_r28]->data;
                    VECSubtract(&temp_r31->unkC4, &temp_r30->unkC4, &sp8);
                    sp8.y = 0.0f;
                    var_f31 = VECMag(&sp8);
                    if (var_f31 < (temp_r31->unkC0 + temp_r30->unkC0)) {
                        if (var_f31 > 0.0f) {
                            var_f31 = 0.5f * ((temp_r31->unkC0 + temp_r30->unkC0) - var_f31);
                        }
                        else {
                            var_f31 = 0.5f * (temp_r31->unkC0 + temp_r30->unkC0);
                            sp8.x = (frandmod(0x3E8) - 0x1F4);
                            sp8.z = (frandmod(0x3E8) - 0x1F4);
                        }
                        VECNormalize(&sp8, &sp8);
                        VECScale(&sp8, &sp8, var_f31);
                        VECAdd(&temp_r31->unkC4, &sp8, &temp_r31->unkC4);
                        VECSubtract(&temp_r30->unkC4, &sp8, &temp_r30->unkC4);
                    }
                }
            }
            if (temp_r31->unkC4.y < 0.0f) {
                temp_r31->unkC4.y = 0.0f;
            }
        }
    }
}

void fn_1_7340(omObjData *object)
{
    M443DllWorkStruct *temp_r31 = object->data;
    HsfObject *var_r29;
    f32 sp28[8] = { 0.0f, 40.0f, 0.0f, 0.0f, -16.0f, 40.0f, -16.0f, 0.0f };
    f32 var_f31;
    f32 var_f29;
    u32 temp_r24;

    temp_r24 = temp_r31->unk80;
    if (temp_r31->unk88 > 3300.0f) {
        if (fn_1_42E4() == 2) {
            temp_r31->unk10C = 0;
            if (temp_r31->unk84 == 0) {
                if ((temp_r31->unk10 & 0x100) != 0) {
                    if (temp_r31->unk80 < 3) {
                        temp_r31->unk80++;
                        temp_r31->unk84 = 30;
                    }
                }
                else {
                    if (temp_r31->unk88 >= 8000.0f) {
                        temp_r31->unk10C = 1;
                    }
                }
            }
            else {
                temp_r31->unk84--;
            }
        }
    }
    else if ((temp_r31->unk88 < 1500.0f) && (temp_r31->unk80 != 0)) {
        temp_r31->unk80--;
        temp_r31->unk84 = 30;
    }
    if (temp_r31->unk80 != temp_r24) {
        temp_r31->unk88 = fn_1_8D00(temp_r31->unk80, temp_r31->unk90);
        omVibrate(object->work[0], 0xC, 4, 2);
    }
    var_f31 = (1.5f * temp_r31->unk18) - 0.5f;
    if (var_f31 < -0.4f) {
        var_f31 = -1.0f;
    }
    var_f29 = 0.75f;
    if ((var_f31 > -0.5f) && (temp_r31->unkA0 < 1.0f)) {
        var_f29 += 0.25f * (1.0f - temp_r31->unkA0);
    }
    var_f31 = var_f31 * fn_1_8AC8(temp_r31->unk80, temp_r31->unk88);
    var_f31 -= temp_r31->unkA0 * fn_1_8D74(fn_1_8C8C(temp_r31->unk80, temp_r31->unk88));
    var_f31 = var_f29 * fn_1_8C68(var_f31);
    temp_r31->unk90 += 0.016666668f * var_f31;
    temp_r31->unk7C += temp_r31->unkA0 * (temp_r31->unk90 - temp_r31->unk7C);
    var_f31 = temp_r31->unk90 + temp_r31->unkA0 * (temp_r31->unk7C - temp_r31->unk90);
    temp_r31->unk88 = fn_1_8D00(temp_r31->unk80, var_f31);
    if (fn_1_42E4() <= 2) {
        if (fn_1_42E4() == 2) {
            if (temp_r31->unk18 <= 0.0f) {
                temp_r31->unk90 *= 0.98f;
            }
        }
        if ((temp_r31->unk88 > 8000.0f) && ((temp_r31->unk40 & 0xF) == 0)) {
            omVibrate(object->work[0], 0xC, 6, 6);
        }
    }
    if (temp_r31->unk88 > 9500.0f) {
        temp_r31->unk88 = 9000.0f;
        temp_r31->unk90 = fn_1_8C8C(temp_r31->unk80, temp_r31->unk88);
    }
    else if (temp_r31->unk88 < 1000.0f) {
        temp_r31->unk88 = 1000.0f;
        temp_r31->unk90 = fn_1_8C8C(temp_r31->unk80, temp_r31->unk88);
    }
    temp_r31->unk94 = (0.31206876f * temp_r31->unk90);
    if (temp_r31->unkA0 < 1.0f) {
        var_f31 = temp_r31->unk90 - temp_r31->unk7C;
        if (var_f31 > 2.0f) {
            var_f31 = 1.0f - (0.02f * var_f31);
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            if (var_f31 < 0.0f) {
                var_f31 = 0.0f;
            }
            var_f31 = (1.0f - var_f31 * var_f31);
            temp_r31->unkA0 += (1.0f / 3000.0f) * (1.0f - 1.5f * var_f31);
            if (temp_r31->unkA0 > 0.9f) {
                temp_r31->unkA0 = 1.0f;
            }
            if (temp_r31->unkA0 < 0.0001f) {
                temp_r31->unkA0 = 0.0001f;
            }
        }
        else {
            temp_r31->unkA0 = 1.0f;
        }
    }
    temp_r31->unk78 += 1.6666667f * temp_r31->unk7C;
    if (fn_1_42E4() < 2) {
        temp_r31->unk7C = 0.0f;
        temp_r31->unk78 = 0.0f;
        temp_r31->unkA0 = 0.0f;
    }
    if (temp_r31->unk78 >= 40000.0f) {
        if (temp_r31->unk7C >= 30.0f) {
            Hu3DMotionSpeedSet(object->model[2], 1.0f);
            Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
            if (fn_1_42E4() == 2) {
                HuAudFXPlay(0x733);
            }
        }
    }
    fn_1_8680(object);
    temp_r31->unk74 = 1 - temp_r31->unk74;
    var_f31 = 22.5f * (temp_r31->unk40 & 0xF);
    var_r29 = Hu3DModelObjPtrGet(object->model[2], "ballon");
    var_r29->data.base.rot.z = var_f31;
    var_r29 = Hu3DModelObjPtrGet(object->model[1], "r_tire");
    if ((temp_r31->unk7C <= 0.0f) && (temp_r31->unk94 < 1.5f)) {
        temp_r31->unk94 = 0.0f;
    }
    var_r29->data.base.rot.x += 6.0000005f * temp_r31->unk94;
    var_r29->data.base.rot.x = fmod(var_r29->data.base.rot.x, 360.0);
    var_r29 = Hu3DModelObjPtrGet(object->model[1], "f_tire");
    var_r29->data.base.rot.x += 6.0000005f * (0.003978877f * (100.0f * temp_r31->unk7C));
    var_r29->data.base.rot.x = fmod(var_r29->data.base.rot.x, 360.0);
    var_f31 = 0.110999994f * temp_r31->unk94;
    if (var_f31 > 1.0f) {
        var_f31 = 1.0f;
    }
    Hu3DMotionTimeSet(object->model[1], 30.0f * var_f31);
    fn_1_4314(object->work[0], temp_r31->unk78);
    fn_1_6B90(object);
    if (temp_r31->unkA0 < 1.0f) {
        var_f31 = (320.4422f * temp_r31->unk94) - (100.0f * temp_r31->unk7C);
        if (var_f31 > 0.0f) {
            var_f31 *= 0.0002f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            fn_1_8FFC(object->work[0], &temp_r31->unkDC, var_f31, 100.0f * temp_r31->unk7C);
        }
    }
    fn_1_8E34(object->model[3]);
    if (temp_r31->unkB4 >= 0) {
        HuAudFXPitchSet(temp_r31->unkB4, (8191.0f * (0.0001f * temp_r31->unk88)));
        if (fn_1_42E4() >= 5) {
            HuAudFXFadeOut(temp_r31->unkB4, 0x3C);
            temp_r31->unkB4 = -1;
        }
    }
    if (fn_1_42E4() < 2) {
        if (temp_r31->unkA8 < 0) {
            temp_r31->unkA8 = HuAudFXPlay(lbl_1_data_344[object->work[0]]);
        }
        if (temp_r31->unkA8 >= 0) {
            var_f31 = fn_1_8C8C(temp_r31->unk80, 10000.0f);
            var_f31 = (1.0f / (0.31206876f * var_f31));
            HuAudFXPitchSet(temp_r31->unkA8, (8191.0f * (temp_r31->unk94 * var_f31)));
            var_f31 = 127.0f;
            if (temp_r31->unk94 < 0.1f) {
                var_f31 = 0.0f;
            }
            HuAudFXVolSet(temp_r31->unkA8, var_f31);
        }
    }
    else if (fn_1_42E4() <= 2) {
        if (temp_r31->unkA8 < 0) {
            temp_r31->unkA8 = HuAudFXPlay(lbl_1_data_344[object->work[0]]);
        }
        if (temp_r31->unkA8 >= 0) {
            HuAudFXPitchSet(temp_r31->unkA8, (8191.0f * (0.0001f * temp_r31->unk88) * (1.0f - temp_r31->unkA0)));
            var_f31 = 127.0f;
            if (temp_r31->unkA0 >= 1.0f) {
                var_f31 = 0.0f;
            }
            HuAudFXVolSet(temp_r31->unkA8, var_f31);
        }
    }
    else if (temp_r31->unkA8 >= 0) {
        HuAudFXStop(temp_r31->unkA8);
        temp_r31->unkA8 = -1;
    }
    if ((fn_1_42E4() >= 1) && (temp_r31->unkB0 >= 0)) {
        HuAudFXFadeOut(temp_r31->unkB0, 30);
        temp_r31->unkB0 = -1;
    }
    if ((fn_1_42E4() == 2) && (temp_r31->unkB8 < 0)) {
        temp_r31->unkB8 = HuAudFXPlay(lbl_1_data_354[object->work[0]]);
    }
    if (temp_r31->unkB8 >= 0) {
        var_f31 = 0.012048192f * temp_r31->unk7C;
        HuAudFXPitchSet(temp_r31->unkB8, ((2.0f * (8191.0f * var_f31)) - 8191.0f));
        HuAudFXVolSet(temp_r31->unkB8, (127.0f * var_f31));
        if (fn_1_42E4() >= 5U) {
            HuAudFXFadeOut(temp_r31->unkB8, 0x3C);
            temp_r31->unkB8 = -1;
        }
    }
}

void fn_1_8138(omObjData *object, u32 arg1)
{ // near replica of fn_1_B8A0 of m417Dll
    f32 var_f31;
    M443DllWorkStruct *temp_r30;

    temp_r30 = object->data;
    if ((temp_r30->unk8 != arg1) && (arg1 < 4)) {
        var_f31 = 60.0f * lbl_1_data_2D4[arg1].unk4;
        if (temp_r30->unk8 < 0) {
            var_f31 = 0.0f;
        }
        temp_r30->unk8 = arg1;
        CharModelMotionShiftSet(
            temp_r30->unk0, object->motion[lbl_1_data_2D4[arg1].unk0], 60.0f * lbl_1_data_2D4[arg1].unk8, var_f31, lbl_1_data_2D4[arg1].unk10);
        if (lbl_1_data_2D4[arg1].unkC >= 0.0f) {
            Hu3DMotionShiftStartEndSet(object->model[0], 60.0f * lbl_1_data_2D4[arg1].unk8, 60.0f * lbl_1_data_2D4[arg1].unkC);
        }
    }
}

s32 fn_1_82C4(omObjData *object)
{
    s32 var_r30;
    M443DllWorkStruct *temp_r31;

    temp_r31 = object->data;
    var_r30 = 0;
    if ((CharModelMotionEndCheck(temp_r31->unk0) != 0) && (CharModelMotionShiftIDGet(temp_r31->unk0) < 0)) {
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_8338(omObjData *object, u32 arg1)
{
    s32 var_r27;
    s32 var_r26;
    M443DllWorkStruct *temp_r31;

    var_r27 = 0;
    temp_r31 = object->data;
    var_r26 = 0;
    if ((CharModelMotionEndCheck(temp_r31->unk0) != 0) && (CharModelMotionShiftIDGet(temp_r31->unk0) < 0)) {
        var_r26 = 1;
    }

    if (var_r26 != 0) {
        fn_1_8138(object, arg1);
        var_r27 = 1;
    }
    return var_r27;
}

u32 lbl_1_data_410[11][2] = {
    { 0x4A0015, 0xFA },
    { 0x4A0016, 0xF0 },
    { 0x4A0017, 0xE6 },
    { 0x4A0018, 0xF0 },
    { 0x4A0019, 0xF0 },
    { 0x4A001A, 0xF0 },
    { 0x4A001B, 0xF0 },
    { 0x61002E, 0xF0 },
    { 0x61002E, 0xF0 },
    { 0x61002E, 0xF0 },
    { 0x4A001C, 0xF0 },
};

Vec2f lbl_1_data_468[4] = {
    { 64.0f, 54.0f },
    { 46.0f, 54.0f },
    { 64.0f, 44.0f },
    { 46.0f, 44.0f },
};

void fn_1_8508(omObjData *object)
{
    s32 var_r30;
    M443DllWorkStruct *temp_r28;
    M443DllUnkStruct *temp_r31;

    temp_r28 = object->data;
    temp_r31 = &temp_r28->unk108s;

    for (var_r30 = 0; var_r30 < 11; var_r30++) {
        temp_r31->unk14[var_r30] = -1;
        if (lbl_1_data_410[var_r30][0] != 0) {
            temp_r31->unk14[var_r30] = espEntry(lbl_1_data_410[var_r30][0], lbl_1_data_410[var_r30][1], 0);
            espAttrSet(temp_r31->unk14[var_r30], HUSPR_ATTR_LINEAR);
            espDispOff(temp_r31->unk14[var_r30]);
        }
    }
    espColorSet(temp_r31->unk14[0], 0, 0, 0);
    espTPLvlSet(temp_r31->unk14[0], 0.5);
    espScaleSet(temp_r31->unk14[1], 0.75, 0.75);
    espScaleSet(temp_r31->unk14[2], 0.75, 0.75);
    temp_r31->unkC = lbl_1_data_468[object->work[0]];
}

f32 lbl_1_data_488[][2] = {
    { 20.0f, 4.0f },
    { 18.0f, 6.0f },
    { 46.0f, 33.0f },
    { 72.0f, 32.0f },
    { 72.0f, 14.0f },
    { 72.0f, -4.0f },
    { 72.0f, -22.0f },
    { -140.0f, 32.0f },
    { -158.0f, 32.0f },
    { -176.0f, 32.0f },
    { -96.0f, 32.0f },
};

void fn_1_8680(omObjData *object)
{
    f32 var_f31;
    s32 var_r27;
    s32 var_r30;
    u32 var_r28;
    M443DllWorkStruct *temp_r29;
    M443DllUnkStruct *temp_r31;

    temp_r29 = object->data;
    temp_r31 = &temp_r29->unk108s;
    temp_r31->unk8++;

    for (var_r30 = 0; var_r30 < 11; var_r30++) {
        if (temp_r31->unk14[var_r30] >= 0) {
            if (temp_r31->unk0 == 0) {
                espDispOff(temp_r31->unk14[var_r30]);
            }
            else {
                espDispOn(temp_r31->unk14[var_r30]);
                espPosSet(temp_r31->unk14[var_r30], 0.9f * (temp_r29->unk104->unk_44 + temp_r31->unkC.x + lbl_1_data_488[var_r30][0]),
                    temp_r29->unk104->unk_48 + temp_r31->unkC.y + lbl_1_data_488[var_r30][1]);
            }
        }
    }
    var_f31 = 0.0f;
    if (temp_r29->unk88 > 8000.0f) {
        var_f31 = (0.004f * frandmod(0x3E8)) - 2.0f;
    }
    espZRotSet(temp_r31->unk14[2], (90.0f * (0.0001f * temp_r29->unk88)) + var_f31);

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r27 = 0;
        if (temp_r29->unk80 == var_r30) {
            var_r27 = 2;
        }
        else if (((temp_r29->unk80 + 1) == var_r30) && (temp_r31->unk4 != 0)) {
            var_r27 += (temp_r31->unk8 >> 1) & 1;
        }
        espBankSet(temp_r31->unk14[var_r30 + 3], var_r27);
    }
    var_r28 = (3.6f * temp_r29->unk7C);
    var_r30 = var_r28 % 10;
    espBankSet(temp_r31->unk14[7], var_r30);
    var_r28 = (var_r28 - var_r30) / 10;
    var_r30 = var_r28 % 10;
    espBankSet(temp_r31->unk14[8], var_r30);
    var_r28 = (var_r28 - var_r30) / 10;
    var_r30 = var_r28 % 10;
    espBankSet(temp_r31->unk14[9], var_r30);
}

f32 lbl_1_data_4E0[4] = { 18.5f, 9.25f, 6.66f, 5.55f };

f32 fn_1_8958(u32 arg0)
{
    if (arg0 >= 4) {
        if (arg0 >= 4) { }
    }
    return lbl_1_data_4E0[arg0];
}

f32 fn_1_8990(f32 arg8)
{
    f32 var_f30;
    f32 var_f31;

    var_f30 = 0.8f * (0.00016666666f * (6000.0f - arg8));
    var_f30 = 0.6f * (1.0f - (var_f30 * var_f30));
    var_f31 = 0.000400000002f * (6500.0f - arg8);
    var_f31 = 0.4f * (1.0f - (var_f31 * var_f31));
    if (var_f31 > 0.0f) {
        var_f30 += var_f31;
    }
    var_f31 = arg8 - 8000.0f;
    if (var_f31 > 0.0f) {
        var_f31 = 1.0f - (0.00033333333f * var_f31);
        var_f30 = var_f31 * (var_f30 * var_f31);
    }
    return 55.0f * var_f30;
}

f32 fn_1_8AC8(u32 arg0, f32 arg1)
{
    return 1.7647059f * (fn_1_8990(arg1) * fn_1_8958(arg0));
}

f32 fn_1_8C68(f32 arg0)
{
    return 9.8f * (0.0012820513f * arg0);
}

f32 fn_1_8C8C(s32 arg0, f32 arg1)
{
    return 3.204422f * ((0.016666668f * arg1) / fn_1_8958(arg0));
}

f32 fn_1_8D00(u32 arg0, f32 arg1)
{
    return 0.31206876f * (60.0f * arg1) * fn_1_8958(arg0);
}

f32 fn_1_8D74(f32 arg0)
{
    return 0.024899999f * (arg0 * arg0);
}

f32 fn_1_8D8C(u32 arg0, f32 arg8)
{
    return arg8 / fn_1_8958(arg0);
}
f32 fn_1_8DE0(u32 arg0, f32 arg8)
{
    return arg8 * fn_1_8958(arg0);
}

void fn_1_8E34(s32 arg0)
{
    s32 var_r29;
    ParticleData *temp_r30;
    HsfanimStruct01 *var_r31;

    temp_r30 = Hu3DData[arg0].unk_120;
    var_r31 = temp_r30->unk_48;

    for (var_r29 = 0; var_r29 < temp_r30->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00 != 0) {
            VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            var_r31->unk08.z -= 0.3f;
            var_r31->unk2C += 2.0f;
            var_r31->unk40.a *= 0.98f;
            if (var_r31->unk00 < 24.0f) {
                var_r31->unk40.a = var_r31->unk40.a * 0.9f;
            }
            if (--var_r31->unk00 == 0) {
                var_r31->unk00 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(temp_r30->unk_48, temp_r30->unk_30 * 0x44);
}

static inline f32 isEven(u32 arg)
{
    if ((arg & 1) != 0) {
        return 1.0f;
    }
    else {
        return -1.0f;
    }
}

void fn_1_8FFC(u32 arg0, Vec *arg1, f32 arg2, f32 arg3)
{
    f32 temp_f31;
    f32 var_f29;
    ParticleData *temp_r29;
    s32 var_r28;
    u32 var_r27;
    HsfanimStruct01 *var_r31;

    temp_r29 = Hu3DData[lbl_1_bss_90[arg0]->model[3]].unk_120;
    if (frandmod(0x3E8) > 1000.0f * arg2)
        return;

    var_r27 = 2;
    var_r31 = temp_r29->unk_48;

    for (var_r28 = 0; var_r28 < temp_r29->unk_30; var_r28++, var_r31++) {
        if (var_r31->unk00 != 0)
            continue;

        var_r31->unk00 = (60.0f * (0.6f + (0.0005f * frandmod(0x3E8))));
        var_f29 = isEven(var_r27);
        temp_f31 = 0.030000001f * frandmod(0x3E8);
        var_r31->unk34.x = arg1->x + var_f29 * (70.0f + (0.07f * frandmod(0x3E8)));
        var_r31->unk34.y = 10.0f + (arg1->y + (0.02f * frandmod(0x3E8)));
        var_r31->unk34.z = (250.0f + arg1->z);
        temp_f31 = 0.8333334f + 0.0016666667f * frandmod(0x3E8);
        temp_f31 *= 1.0f + arg2;
        var_r31->unk08.x = (0.0025f * frandmod(0x3E8) - 1.25f);
        var_r31->unk08.y = (3.3333335f + 0.0016666667f * frandmod(0x3E8));
        var_r31->unk08.z = ((4.166667f + (0.0016666667f * frandmod(0x3E8))) - (0.016666668f * (0.5f * arg3)));
        var_r31->unk30 = frandmod(0x168);
        temp_f31 = 0.001f * frandmod(0x3E8);
        var_r31->unk2C = (50.0f + (100.0f * temp_f31));
        var_r31->unk40.a = (70.0f + (80.0f * (1.0f - temp_f31)));
        var_r31->unk40.r = (50.0f + (145.0f * temp_f31));
        var_r31->unk40.g = (55.0f + (140.0f * temp_f31));
        var_r31->unk40.b = (70.0f + (125.0f * temp_f31));
        if (--var_r27 < 1)
            break;
    }
}

void fn_1_95A4(u32 arg0)
{
    s32 var_r29;
    ParticleData *temp_r30;
    HsfanimStruct01 *var_r31;

    temp_r30 = Hu3DData[lbl_1_bss_90[arg0]->model[3]].unk_120;
    var_r31 = temp_r30->unk_48;

    for (var_r29 = 0; var_r29 < temp_r30->unk_30; var_r29++, var_r31++) {
        var_r31->unk00 = 0;
        var_r31->unk2C = 0.0f;
        var_r31->unk40.a = 0;
    }
}
