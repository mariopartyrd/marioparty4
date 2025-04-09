#include "REL/m440Dll.h"

#include "ext_math.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/hsfdraw.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "math.h"

#include "string.h"
#include "version.h"

// bss
omObjData *lbl_1_bss_6C;
omObjData *lbl_1_bss_68;
unkStruct6 *lbl_1_bss_64;
s16 lbl_1_bss_60;
Mtx lbl_1_bss_30;
s16 lbl_1_bss_2C;
void *lbl_1_bss_28;
u32 lbl_1_bss_24;
s16 lbl_1_bss_10[10];
s16 lbl_1_bss_E;
u8 lbl_1_bss_C;
u8 lbl_1_bss_B;
u8 lbl_1_bss_A;
s16 lbl_1_bss_8;
s16 lbl_1_bss_6;
s16 lbl_1_bss_4;
s8 lbl_1_bss_2;
s8 lbl_1_bss_1;
s8 lbl_1_bss_0;

// data
f32 lbl_1_data_0[5] = { 90.0f, 80.0f, 100.0f, 70.0f, 110.0f };
s16 lbl_1_data_14[6] = { 1, 1, 1, 1, 1 };
Vec lbl_1_data_20 = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_2C = { 800.0f, 1300.0f, 1000.0f };
Vec lbl_1_data_38 = { 0.0f, 0.0f, 0.0f };
unkStruct7 lbl_1_data_44 = { 0xFF, 0xFF, 0xFF, 0xFF, 10.0f, 45.0f, 0.0f };
Vec lbl_1_data_54 = { 1300.0f, 2500.0f, 1300.0f };
Vec lbl_1_data_60 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_6C = { 0.0f, 0.0f, -500.0f };
unkStruct lbl_1_data_78[3] = {
    { 1450.0f, { 0.0f, 452.0f, 0.0f }, { 11.0f, -23.0f, 0.0f } },
    { 1700.0f, { 0.0f, 315.0f, 0.0f }, { -2.0f, 0.0f, 0.0f } },
    { 1040.0f, { 200.0f, 21.0f, 0.0f }, { -6.0f, 0.0f, 0.0f } },
};

void ObjectSetup(void)
{
    Vec sp8;
    LightData *var_r30;
    Process *var_r31;

    Hu3DLightAllKill();
    lbl_1_bss_E = Hu3DGLightCreateV(&lbl_1_data_2C, &lbl_1_data_38, &lbl_1_data_44.unk0);
    Hu3DGLightInfinitytSet(lbl_1_bss_E);
    var_r30 = &Hu3DGlobalLight[lbl_1_bss_E];
    var_r30->unk_00 |= 0x8000;
    sp8.x = sp8.y = sp8.z = 0.0f;
    Hu3DGLightPosAimSetV(lbl_1_bss_E, &lbl_1_data_2C, &sp8);
    Hu3DShadowCreate(45.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_data_54, &lbl_1_data_60, &lbl_1_data_6C);
    HuAudSndGrpSet(0x42);
    var_r31 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(var_r31);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 41.5f, 5.0f, 5000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omAddObjEx(var_r31, 0x7FDA, 0, 0, -1, omOutView);
    CRot.x = lbl_1_data_78[0].rot.x;
    CRot.y = lbl_1_data_78[0].rot.y;
    CRot.z = lbl_1_data_78[0].rot.z;
    Center.x = lbl_1_data_78[0].center.x;
    Center.y = lbl_1_data_78[0].center.y;
    Center.z = lbl_1_data_78[0].center.z;
    CZoom = lbl_1_data_78[0].zoom;
    omAddObjEx(var_r31, 0x3E8, 0, 0, -1, fn_1_3C4);
    lbl_1_bss_6C = omAddObjEx(var_r31, 10, 9, 0, -1, fn_1_8F0);
    lbl_1_bss_68 = omAddObjEx(var_r31, 50, 9, 9, -1, fn_1_2470);
    Hu3DBGColorSet(0, 0, 0);
    fn_1_AE08(var_r31);
}

void fn_1_3C4(omObjData *object)
{
    if ((omSysExitReq != 0) || (lbl_1_bss_0 != 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = &fn_1_434;
    }
}

void fn_1_434(omObjData *object)
{
    if ((WipeStatGet() == 0) && (MGSeqDoneCheck() != 0)) {
        HuMemDirectFree(lbl_1_bss_64);
        fn_1_9AB0(lbl_1_bss_10[0]);
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

s32 fn_1_4A4(void)
{
    f32 var_f31;
    unkStruct *var_r31;
    s32 var_r30;

    var_r31 = &lbl_1_data_78[0];
    var_r30 = 0;
    lbl_1_bss_4++;
    var_f31 = lbl_1_bss_4 / (2 * REFRESH_RATE_F);
    if (var_f31 > 1.0f) {
        lbl_1_bss_4 = 0;
        var_f31 = 1.0f;
        var_r30 = 1;
    }

    var_f31 = sind(90.0f * var_f31) * sind(90.0f * var_f31);
    CZoom = fn_1_93C0(var_r31[0].zoom, var_r31[1].zoom, var_f31);
    Center.x = fn_1_93C0(var_r31[0].center.x, var_r31[1].center.x, var_f31);
    Center.y = fn_1_93C0(var_r31[0].center.y, var_r31[1].center.y, var_f31);
    Center.z = fn_1_93C0(var_r31[0].center.z, var_r31[1].center.z, var_f31);
    CRot.x = fn_1_93C0(var_r31[0].rot.x, var_r31[1].rot.x, var_f31);
    CRot.y = fn_1_93C0(var_r31[0].rot.y, var_r31[1].rot.y, var_f31);
    CRot.z = fn_1_93C0(var_r31[0].rot.z, var_r31[1].rot.z, var_f31);
    return var_r30;
}

s32 fn_1_6C8(void)
{
    f32 var_f31;
    unkStruct *var_r31;
    s32 var_r30;

    var_r31 = &lbl_1_data_78[1];
    var_r30 = 0;
    lbl_1_bss_4++;
    var_f31 = lbl_1_bss_4 / (2 * REFRESH_RATE_F);
    if (var_f31 > 1.0f) {
        lbl_1_bss_4 = 0;
        var_f31 = 1.0f;
        var_r30 = 1;
    }

    var_f31 = (sind(90.0f * var_f31) * sind(90.0f * var_f31));
    CZoom = fn_1_93C0(var_r31[0].zoom, var_r31[1].zoom, var_f31);
    Center.x = fn_1_93C0(var_r31[0].center.x, var_r31[1].center.x, var_f31);
    Center.y = fn_1_93C0(var_r31[0].center.y, var_r31[1].center.y, var_f31);
    Center.z = fn_1_93C0(var_r31[0].center.z, var_r31[1].center.z, var_f31);
    CRot.x = fn_1_93C0(var_r31[0].rot.x, var_r31[1].rot.x, var_f31);
    CRot.y = fn_1_93C0(var_r31[0].rot.y, var_r31[1].rot.y, var_f31);
    CRot.z = fn_1_93C0(var_r31[0].rot.z, var_r31[1].rot.z, var_f31);
    return var_r30;
}

void fn_1_8F0(omObjData *arg0)
{
    s16 var_r30;
    unkStruct2 *temp_r31;
    AnimData *anim;

    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x10, MEMORY_DEFAULT_NUM);
    temp_r31 = (unkStruct2 *)arg0->data;
    temp_r31->unk0 = 1;
    temp_r31->unk4 = -1;
    temp_r31->unk8 = -1;
    temp_r31->unk6 = 5 * REFRESH_RATE;
    temp_r31->unkA = 0;
    temp_r31->unkC = -1;

    for (var_r30 = 1; var_r30 < 4; var_r30++) {
        lbl_1_bss_10[var_r30] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x0A));
        Hu3DModelAttrSet(lbl_1_bss_10[var_r30], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_10[var_r30], HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(lbl_1_bss_10[var_r30], 7);
        Hu3DModelScaleSet(lbl_1_bss_10[var_r30], 3.0f, 3.0f, 3.0f);
    }

    anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M440, 0x0B), MEMORY_DEFAULT_NUM));
    lbl_1_bss_10[0] = fn_1_956C(anim, 0x40, 50.0f, 0x40, 0x40);
    fn_1_9B94(lbl_1_bss_10[0], fn_1_2240);
    Hu3DModelLayerSet(lbl_1_bss_10[0], 7);
    arg0->func = &fn_1_AE0;
}

void fn_1_AE0(omObjData *arg0)
{
    f32 temp_f31;
    unkStruct2 *temp_r31;

    temp_r31 = arg0->data;
    switch (fn_1_23E4(7)) {
        case 1:
            if (lbl_1_bss_A == 0) {
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                lbl_1_bss_A = 1;
            }
            if (WipeStatGet() != 0)
                break;
            fn_1_2428(7, 2);
            break;
        case 2:
            if (fn_1_E14(arg0) != 0) {
                fn_1_2428(7, 3);
            }
            break;
        case 3:
            if (temp_r31->unk8 != -1) {
                MGSeqParamSet(temp_r31->unk8, 1, ((temp_r31->unk6 + REFRESH_RATE - 1) / REFRESH_RATE));
            }
            if ((temp_r31->unkC < 0) && ((MGSeqStatGet(temp_r31->unk4) & 0x10) != 0)) {
                temp_r31->unkC = HuAudSeqPlay(0x49);
            }
            if (lbl_1_bss_2 == 0) {
                if (temp_r31->unkA != 0) {
                    temp_r31->unkA++;
                    temp_f31 = (((rand8() << 8) | rand8()) % 361);
                    Center.x = (lbl_1_data_78[1].center.x + (10.0 * sind(temp_f31)));
                    Center.y = (lbl_1_data_78[1].center.y + (10.0 * cosd(temp_f31)));
                    if (temp_r31->unkA > (2 * REFRESH_RATE / 3)) {
                        temp_r31->unkA = 0;
                        return;
                    }
                }
                else {
                    Center.x = lbl_1_data_78[1].center.x;
                    Center.y = lbl_1_data_78[1].center.y;
                    Center.z = lbl_1_data_78[1].center.z;
                    return;
                }
            }
            break;
        case 4:
            if (fn_1_1138(arg0) != 0) {
                fn_1_2428(7, 5);
                return;
            }
            break;
        case 5:
            lbl_1_bss_0 = 1;
            break;
    }
}

u8 fn_1_E14(omObjData *arg0)
{
    f32 var_f31;
    unkStruct *var_r31;
    u8 var_r30;

    switch (lbl_1_bss_6) {
        case 0:
            fn_1_4EEC(7, 1);
            fn_1_4EEC(0x18, 8);
            HuAudFXPlay(0x70E);
            lbl_1_bss_6++;
            break;
        case 1:
            if (++lbl_1_bss_8 > (s16)(0.5f * REFRESH_RATE_F)) {
                fn_1_F168();
                lbl_1_bss_8 = 0;
                lbl_1_bss_6++;
            }
            break;
        case 2:
            var_r31 = lbl_1_data_78;
            var_r30 = 0;
            lbl_1_bss_4++;
            var_f31 = lbl_1_bss_4 / (2 * REFRESH_RATE_F);
            if (var_f31 > 1.0f) {
                lbl_1_bss_4 = 0;
                var_f31 = 1.0f;
                var_r30 = 1;
            }
            var_f31 = (sind(90.0f * var_f31) * sind(90.0f * var_f31));
            CZoom = fn_1_93C0(var_r31[0].zoom, var_r31[1].zoom, var_f31);
            Center.x = fn_1_93C0(var_r31[0].center.x, var_r31[1].center.x, var_f31);
            Center.y = fn_1_93C0(var_r31[0].center.y, var_r31[1].center.y, var_f31);
            Center.z = fn_1_93C0(var_r31[0].center.z, var_r31[1].center.z, var_f31);
            CRot.x = fn_1_93C0(var_r31[0].rot.x, var_r31[1].rot.x, var_f31);
            CRot.y = fn_1_93C0(var_r31[0].rot.y, var_r31[1].rot.y, var_f31);
            CRot.z = fn_1_93C0(var_r31[0].rot.z, var_r31[1].rot.z, var_f31);
            if (var_r30 != 0) {
                lbl_1_bss_8 = 0;
                lbl_1_bss_6 = 0;
                return 1;
            }
            break;
    }
    return 0;
}

u8 fn_1_1138(omObjData *object)
{
    unkStruct2 *sp8;
    f32 var_f31;
    f32 var_f30;
    s16 temp_r29;
    u8 var_r28;
    unkStruct3 *temp_r30;
    unkStruct *var_r31;

    sp8 = (unkStruct2 *)lbl_1_bss_6C->data;
    temp_r29 = fn_1_F0FC();
    temp_r30 = (unkStruct3 *)lbl_1_bss_C0[temp_r29]->data;
    switch (lbl_1_bss_6) {
        case 0:
            if (lbl_1_bss_8 == 0) {
                Hu3DMotionShiftSet(lbl_1_bss_C0[temp_r29]->model[0], lbl_1_bss_C0[temp_r29]->motion[1], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
                temp_r30->unk40 = temp_r30->unk34;
            }
            lbl_1_bss_8++;
            var_f30 = lbl_1_bss_8 / (0.5f * REFRESH_RATE_F);
            if (var_f30 >= 1.0f) {
                var_f30 = 1.0f;
                if (lbl_1_bss_B == 0) {
                    lbl_1_bss_B = 1;
                    Hu3DMotionShiftSet(lbl_1_bss_C0[temp_r29]->model[0], lbl_1_bss_C0[temp_r29]->motion[0], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
                }
            }
            temp_r30->unk34 = (temp_r30->unk40 + (var_f30 * (360.0f - temp_r30->unk40)));
            var_r31 = &lbl_1_data_78[1]; // could be fn_1_6C8
            var_r28 = 0;
            lbl_1_bss_4++;
            var_f31 = lbl_1_bss_4 / (2 * REFRESH_RATE_F);
            if (var_f31 > 1.0f) {
                lbl_1_bss_4 = 0;
                var_f31 = 1.0f;
                var_r28 = 1;
            }
            var_f31 = (sind(90.0f * var_f31) * sind(90.0f * var_f31));
            CZoom = fn_1_93C0(var_r31[0].zoom, var_r31[1].zoom, var_f31);
            Center.x = fn_1_93C0(var_r31[0].center.x, var_r31[1].center.x, var_f31);
            Center.y = fn_1_93C0(var_r31[0].center.y, var_r31[1].center.y, var_f31);
            Center.z = fn_1_93C0(var_r31[0].center.z, var_r31[1].center.z, var_f31);
            CRot.x = fn_1_93C0(var_r31[0].rot.x, var_r31[1].rot.x, var_f31);
            CRot.y = fn_1_93C0(var_r31[0].rot.y, var_r31[1].rot.y, var_f31);
            CRot.z = fn_1_93C0(var_r31[0].rot.z, var_r31[1].rot.z, var_f31);
            if (var_r28 != 0) {
                lbl_1_bss_8 = 0;
                lbl_1_bss_6++;
            }
            break;
        case 1:
            Hu3DMotionShiftSet(lbl_1_bss_C0[temp_r29]->model[0], lbl_1_bss_C0[temp_r29]->motion[5], 0.0f, 7.0f, HU3D_MOTATTR_NONE);
            HuAudSStreamPlay(1);
            lbl_1_bss_6++;
            lbl_1_bss_8 = 0;
            break;
        case 2:
            if (++lbl_1_bss_8 > (3.5f * REFRESH_RATE)) {
                lbl_1_bss_6 = 0;
                return 1;
            }
            break;
    }
    return 0;
}

void fn_1_16D8(void)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    temp_r31->unk6--;
}

void fn_1_1708(void)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    if (temp_r31->unk8 != -1) {
        MGSeqParamSet(temp_r31->unk8, 2, -1);
        temp_r31->unk8 = -1;
        temp_r31->unk6 = 0;
    }
}

void fn_1_1768(void)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    if (temp_r31->unk8 == -1) {
        temp_r31->unk6 = 5 * REFRESH_RATE;
        temp_r31->unk8 = MGSeqCreate(1, 5, -1, -1);
    }
}

s16 fn_1_17CC(void)
{
    unkStruct2 *var_r31;

    var_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    return var_r31->unk6;
}

s16 fn_1_17F4(void)
{
    unkStruct2 *var_r31;

    var_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    return var_r31->unk8;
}

void fn_1_181C(void)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    if (temp_r31->unk4 == -1) {
        temp_r31->unk4 = MGSeqCreate(3, 0);
        MGSeqPosSet(temp_r31->unk4, 320.0f, 240.0f);
    }
}

u8 fn_1_1890(void)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    if (temp_r31->unk4 != -1) {
        return MGSeqStatGet(temp_r31->unk4);
    }
    else {
        return 0;
    }
}

void fn_1_18E0(void)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    temp_r31->unk4 = MGSeqCreate(3, 1);
    MGSeqPosSet(temp_r31->unk4, 320.0f, 240.0f);
    HuAudSeqFadeOut(temp_r31->unkC, 0x64);
}

u8 fn_1_1954(void)
{
    unkStruct2 *sp8;

    sp8 = (unkStruct2 *)lbl_1_bss_6C->data;
    if ((lbl_1_bss_2 != 0) || (lbl_1_bss_1 != 0)) {
        return 0;
    }
    else {
        return 1;
    }
}

void fn_1_19B0(void)
{
    f32 temp_f29;
    f32 var_f28;
    f32 var_f27;
    f32 temp_f31;
    f32 var_f30;
    s16 var_r31;

    var_f30 = (((rand8() << 8) | rand8()) % 361);

    for (var_r31 = 1; var_r31 < 4; var_r31++, var_f30 += 120.0f) {
        temp_f31 = 0.01f * ((((rand8() << 8) | rand8()) % 51) + 50);
        temp_f29 = (temp_f31 * (200.0 * sind(var_f30)));
        var_f28 = (temp_f31 * (200.0 * cosd(var_f30)));
        var_f27 = 0.0f;
        Hu3DModelPosSet(lbl_1_bss_10[var_r31], temp_f29, 300.0f + var_f28, var_f27);
        temp_f31 = 0.1f * ((((rand8() << 8) | rand8()) % 11) + 25);
        Hu3DModelScaleSet(lbl_1_bss_10[var_r31], temp_f31, temp_f31, temp_f31);
        Hu3DModelAttrReset(lbl_1_bss_10[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_10[var_r31], HU3D_MOTATTR_PAUSE);
    }
}

void fn_1_1CAC(void)
{
    s16 var_r31;

    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        Hu3DMotionTimeSet(lbl_1_bss_10[var_r31], 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_10[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_10[var_r31], HU3D_MOTATTR_PAUSE);
    }
}

void fn_1_1D54(f32 arg8, f32 arg9, f32 argA, s16 arg0, f32 argB, s16 arg1)
{
    Vec sp30;
    Vec sp24;
    GXColor sp1E;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f31;
    s16 var_r30;
    unkStruct4 *var_r31;

    for (var_r30 = 0; var_r30 < arg0; var_r30++) {
        temp_f31 = argB + ((((rand8() << 8) | rand8()) % 11) - 5);
        temp_f30 = sind(temp_f31);
        temp_f29 = cosd(temp_f31);
        sp30.x = arg8 + ((((rand8() << 8) | rand8()) % 21) - 10);
        sp30.y = arg9 + ((((rand8() << 8) | rand8()) % 21) - 10);
        sp30.z = argA;
        sp24.x = sp24.y = sp24.z = 1.0f;
        sp1E.r = sp1E.g = sp1E.b = 0xFF;
        sp1E.a = 0x80;
        var_r31 = fn_1_942C(arg1, &sp30, &sp24, 0.0f, &sp1E);
        if (!var_r31)
            break;

        var_r31->unk34 = 0;
        var_r31->unk36 = ((rand8() << 8) | rand8()) % 2 + 2;
        var_r31->unk0.x = (temp_f30 * (0.1f * ((((rand8() << 8) | rand8()) % 41) + 0x28)));
        var_r31->unk0.y = (temp_f29 * (0.1f * ((((rand8() << 8) | rand8()) % 61) + 0x3C)));
        var_r31->unk0.z = 0.0f;
        var_r31->unk18 = (0.01f * var_r31->unk0.x);
        var_r31->unk1C = 0.1f;
        var_r31->unk24 = 1.5f;
        var_r31->unk28 = ((0.1f * ((((rand8() << 8) | rand8()) % 7) + 2)) / (var_r31->unk36 * 0xE));
        var_r31->unk2C = sp1E.a;
        var_r31->unk30 = (var_r31->unk2C / (var_r31->unk36 * 0xE));
    }
}

void fn_1_2240(ModelData *data, unkStruct5 *arg1, Mtx arg2)
{
    unkStruct4 *var_r31;
    GXColor *var_r30;
    s16 var_r29;

    var_r31 = arg1->unk18;
    var_r30 = arg1->unk24;

    for (var_r29 = 0; var_r29 < arg1->unk0; var_r29++, var_r31++, var_r30++) {
        if (var_r31->unk62 != 0) {
            var_r31->unk54.x += var_r31->unk0.x;
            var_r31->unk54.y += var_r31->unk0.y;
            var_r31->unk54.z += var_r31->unk0.z;
            var_r31->unk0.x -= var_r31->unk18;
            var_r31->unk0.y += var_r31->unk1C;
            var_r31->unk18 = (0.001f * var_r31->unk0.x);
            var_r31->unk1C *= 1.05f;
            var_r31->unk24 += var_r31->unk28;
            var_r31->unk48.x = var_r31->unk48.y = var_r31->unk48.z = var_r31->unk24;
            var_r31->unk2C -= var_r31->unk30;
            var_r30->a = var_r31->unk2C > 255.0f ? 255 : (u8)var_r31->unk2C;
            var_r31->unk34++;
            if (var_r31->unk34 >= var_r31->unk36) {
                var_r31->unk34 = 0;
                var_r31->unk60++;
            }
            if (var_r31->unk60 >= arg1->unk14 - 2) {
                var_r31->unk62 = 0;
            }
        }
    }
}

u16 fn_1_23E4(u16 arg0)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    if (!temp_r31) {
        return 0;
    }
    return temp_r31->unk0 & arg0;
}

void fn_1_2428(u16 arg0, u16 arg1)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_6C->data;
    temp_r31->unk0 = (temp_r31->unk0 & ~arg0);
    temp_r31->unk0 = (temp_r31->unk0 | arg1);
}

void fn_1_2470(omObjData *arg0)
{
    ModelData *temp_r29;
    HsfObject *temp_r28;
    f32 temp_f31;
    f32 var_f30;
    f32 var_f29;
    s16 temp_r26;
    s16 var_r30;
    unkStruct2 *temp_r27;

    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x34, MEMORY_DEFAULT_NUM);
    temp_r27 = arg0->data;
    arg0->stat |= 0x100;
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x08));
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x09));
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x00));
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x02));
    arg0->model[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x03));
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x04));
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x05));
    arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x06));
    arg0->model[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x07));
    temp_r26 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M440, 0x01));
    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_HILITE);
    Hu3DModelAttrSet(arg0->model[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(temp_r26, HU3D_ATTR_DISPOFF);

    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        Hu3DModelLayerSet(arg0->model[var_r30], 1);
    }
    Hu3DModelPosSet(arg0->model[2], 0.0f, 5000.0f, 0.0f);
    Hu3DModelPosSet(arg0->model[3], 0.0f, 5000.0f, 0.0f);
    Hu3DModelShadowSet(arg0->model[2]);
    Hu3DModelShadowSet(arg0->model[3]);
    Hu3DModelShadowMapSet(arg0->model[0]);

    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        temp_f31 = 450.0 * cosd(lbl_1_data_0[var_r30]);
        var_f29 = 450.0 * sind(lbl_1_data_0[var_r30]);
        Hu3DModelPosSet(arg0->model[var_r30 + 4], temp_f31, 0.0f, var_f29);
        var_f30 = 90.0f - lbl_1_data_0[var_r30];
        Hu3DModelRotSet(arg0->model[var_r30 + 4], 0.0f, var_f30, 0.0f);
        Hu3DMotionSpeedSet(arg0->model[var_r30 + 4], 0.0f);
    }
    temp_r27->unk0 = 0;
    temp_r27->unk1C = 5;
    temp_r29 = &Hu3DData[temp_r26];
    temp_r28 = temp_r29->hsfData->root;
    lbl_1_bss_60 = temp_r28->data.childrenCount;
    lbl_1_bss_64 = HuMemDirectMalloc(HEAP_DATA, lbl_1_bss_60 * sizeof(unkStruct6));
    OSReport("Koopa Object Count %d\n", temp_r29->hsfData->objectCnt);

    for (var_r30 = 0; var_r30 < lbl_1_bss_60; var_r30++) {
        lbl_1_bss_64[var_r30].unk20 = 0;
    }

    for (var_r30 = 0; var_r30 < lbl_1_bss_60; var_r30++) {
        lbl_1_bss_64[var_r30].unk4 = var_r30;
        fn_1_5C2C(temp_r26, temp_r28->data.children[var_r30], &lbl_1_bss_64[var_r30], 2);
        if (lbl_1_bss_64[var_r30].unk20 != 0) {
            Hu3DModelAttrSet(lbl_1_bss_64[var_r30].unk0, HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(lbl_1_bss_64[var_r30].unk0, 0.0f, 250.0f, 0.0f);
            lbl_1_bss_64[var_r30].unk38 = &fn_1_57B4;
        }
    }
    arg0->func = &fn_1_2A74;
}

void fn_1_2A74(omObjData *object)
{
    fn_1_2AB4(object);
    fn_1_2CA8(object);
    fn_1_4660(object);
}

void fn_1_2AB4(omObjData *object)
{
    unkStruct2 *sp8;

    sp8 = (unkStruct2 *)object->data;

    switch (fn_1_4EA8(0x20)) {
        case 0x20:
            fn_1_2B04(object);
    }
}

s16 lbl_1_data_E4[2] = { 0, 0 };
s16 lbl_1_data_E8[2] = { 0, 0 };
s16 lbl_1_data_EC[2] = { 0, 0 };
s16 lbl_1_data_F0[2] = { 0, 0 };
s32 lbl_1_data_F4[4] = { 20, 60, 100, 140 };
s16 lbl_1_data_104[2] = { 0, 0 };
s16 lbl_1_data_108[2] = { 0, 0 };
s16 lbl_1_data_10C[9] = { 0, 3, 1, 0, 2, 3, 1, 3, 2 };

void fn_1_2B04(omObjData *object)
{
    f32 temp_f31;
    unkStruct *temp_r31;

    temp_r31 = (unkStruct *)object->data;
    switch (lbl_1_data_E4[0]) {
        case 0:
            lbl_1_data_E8[0]++;
            temp_f31 = lbl_1_data_E8[0] / (6 * REFRESH_RATE_F);
            if (temp_f31 > 1.0f) {
                temp_f31 = 1.0f;
                Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
                lbl_1_data_E8[0] = 0;
                lbl_1_data_E4[0] = 0;
                fn_1_4EEC(0x20, 0);
                return;
            }
            temp_f31 = sind(90.0f * temp_f31);
            temp_r31->center.y = (250.0f + (1750.0f * temp_f31));
    }
    Hu3DModelPosSet(object->model[3], temp_r31->center.x, temp_r31->center.y, temp_r31->center.z);
    Hu3DModelRotSet(object->model[3], temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
}

void fn_1_2CA8(omObjData *arg0)
{
    unkStruct2 *sp8;

    sp8 = (unkStruct2 *)arg0->data;

    switch (fn_1_4EA8(7)) {
        case 1:
            fn_1_2D28(arg0);
            break;
        case 3:
            fn_1_33D4(arg0);
            break;
        case 4:
        case 5:
            fn_1_3DD8(arg0);
    }
}

void fn_1_2D28(omObjData *object)
{
    f32 var_f31;
    unkStruct *temp_r31;

    temp_r31 = (unkStruct *)object->data;
    switch (lbl_1_data_EC[0]) {
        case 0x0:
            temp_r31->center.x = temp_r31->center.z = 0.0f;
            temp_r31->center.y = 2000.0f;
            temp_r31->rot.x = temp_r31->rot.y = temp_r31->rot.z = 0.0f;
            Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(object->model[3], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[3], HU3D_MOTATTR_PAUSE);
            Hu3DMotionTimeSet(object->model[3], 0.0f);
            lbl_1_data_EC[0]++;
            lbl_1_data_F0[0] = 0;
            HuAudFXPlay(0x709);
            HuAudFXPlay(0x711);
            break;
        case 0x1:
            lbl_1_data_F0[0]++;
            var_f31 = lbl_1_data_F0[0] / (2 * REFRESH_RATE_F);
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
                lbl_1_data_F0[0] = 0;
                lbl_1_data_F0[1] = REFRESH_RATE / 4;
                lbl_1_data_EC[1] = (lbl_1_data_EC[0] + 1);
                lbl_1_data_EC[0] = 0x63;
            }
            if ((11 * REFRESH_RATE_F / 6) == lbl_1_data_F0[0]) {
                HuAudFXPlay(0x70A);
            }
            var_f31 = sind(90.0f * var_f31);
            temp_r31->center.y = (2000.0f + (-1750.0f * var_f31));
            break;
        case 0x2:
            if (lbl_1_data_F0[0] == 0) {
                HuAudFXPlay(0x713);
            }
            lbl_1_data_F0[0]++;
            var_f31 = lbl_1_data_F0[0] / REFRESH_RATE_F;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
                lbl_1_data_F0[0] = 0;
                lbl_1_data_F0[1] = REFRESH_RATE / 4;
                lbl_1_data_EC[1] = lbl_1_data_EC[0] + 1;
                lbl_1_data_EC[0] = 0x63;
                HuAudFXPlay(0x714);
            }
            temp_r31->rot.y = (360.0f * var_f31);
            break;
        case 0x3:
            Hu3DModelAttrReset(object->model[3], HU3D_MOTATTR_PAUSE);
            Hu3DMotionSpeedSet(object->model[3], 2.0f);
            if (lbl_1_data_F0[0] == 0) {
                HuAudFXPlay(0x711);
            }
            if (++lbl_1_data_F0[0] > (0.2 * REFRESH_RATE)) {
                if (fn_1_4EA8(0x40) != 0) {
                    fn_1_4EEC(0x40, 0);
                    fn_1_F228();
                }
                fn_1_4EEC(0x20, 0x20);
                fn_1_4EEC(7, 2);
                lbl_1_data_F0[0] = 0;
                lbl_1_data_EC[0] = 0;
            }
            break;
        case 0x4:
            lbl_1_data_F0[0]++;
            var_f31 = lbl_1_data_F0[0] / (6 * REFRESH_RATE_F);
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
                Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
                lbl_1_data_F0[0] = 0;
                lbl_1_data_EC[0] = 0;
                fn_1_4EEC(7, 2);
                return;
            }
            var_f31 = sind(90.0f * var_f31);
            temp_r31->center.y = (250.0f + (1750.0f * var_f31));
            break;
        case 0x63:
            if (++lbl_1_data_F0[0] > lbl_1_data_F0[1]) {
                lbl_1_data_F0[0] = 0;
                lbl_1_data_EC[0] = lbl_1_data_EC[1];
            }
            break;
    }
    Hu3DModelPosSet(object->model[3], temp_r31->center.x, temp_r31->center.y, temp_r31->center.z);
    Hu3DModelRotSet(object->model[3], temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
    Hu3DModelPosSet(object->model[2], temp_r31->center.x, temp_r31->center.y, temp_r31->center.z);
    Hu3DModelRotSet(object->model[2], temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
    return;
}

void fn_1_33D4(omObjData *object)
{
    unkStruct2 *sp10;

    sp10 = (unkStruct2 *)object->data;
    switch (lbl_1_data_EC[0]) {
        case 0:
            fn_1_1D54(30.0f, 500.0f, 200.0f, 12, 135.0f, lbl_1_bss_10[0]);
            fn_1_1D54(-30.0f, 500.0f, 200.0f, 12, 225.0f, lbl_1_bss_10[0]);
            fn_1_4EEC(0x100, 0x100);
            fn_1_4EEC(7, 2);
            HuAudFXPlay(0x710);
    }
}

void fn_1_3DD8(omObjData *object)
{
    unkStruct *sp8;
    f32 var_f29;
    f32 var_f28;
    f32 var_f27;
    f32 var_f26;
    f32 var_f30;
    f32 var_f31;
    unkStruct2 *var_r25;
    omObjData **var_r24;
    s16 var_r29;
    s16 var_r31;
    s32 var_r23;
    s32 *var_r26;
    unkStruct2 *var_r28;
    s16 var_r27;

    var_r25 = (unkStruct2 *)lbl_1_bss_6C->data;
    sp8 = (unkStruct *)object->data;
    switch (lbl_1_data_EC[0]) {
        case 0:
            Hu3DModelAttrReset(object->model[2], HU3D_MOTATTR_PAUSE);
            lbl_1_data_EC[0]++;
            return;
        case 1:
            if (++lbl_1_data_F0[0] == 0x1E) {
                fn_1_4EEC(0x100, 0x100);
            }
            else if (lbl_1_data_F0[0] == 0x32) {
                fn_1_EE78();
            }
            var_f26 = Hu3DMotionMaxTimeGet(object->model[2]);
            if (Hu3DMotionTimeGet(object->model[2]) >= var_f26) {
                Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
                for (var_r31 = 0; var_r31 < lbl_1_bss_60; var_r31++) {
                    Hu3DModelAttrReset(lbl_1_bss_64[var_r31].unk0, HU3D_ATTR_DISPOFF);
                    fn_1_57B4(&lbl_1_bss_64[var_r31]);
                }
                lbl_1_data_F0[0] = 0;
                lbl_1_data_EC[0]++;
                HuAudFXPlay(0x70C);
            }

            for (var_r31 = 0; var_r31 < 4U; var_r31++) {
                if (lbl_1_data_F0[0] == lbl_1_data_F4[var_r31] * 2) {
                    HuAudFXPlay(0x70D);
                }
            }
            return;
        case 2:
            var_f30 = (((rand8() << 8) | rand8()) % 361);

            for (var_r29 = 1; var_r29 < 4; var_r29++, var_f30 += 120.0f) {
                var_f31 = 0.01f * ((((rand8() << 8) | rand8()) % 51) + 0x32);
                var_f27 = (var_f31 * (200.0 * sind(var_f30)));
                var_f28 = (var_f31 * (200.0 * cosd(var_f30)));
                var_f29 = 0.0f;
                Hu3DModelPosSet(lbl_1_bss_10[var_r29], var_f27, 300.0f + var_f28, var_f29);
                var_f31 = 0.1f * ((((rand8() << 8) | rand8()) % 11) + 0x19);
                Hu3DModelScaleSet(lbl_1_bss_10[var_r29], var_f31, var_f31, var_f31);
                Hu3DModelAttrReset(lbl_1_bss_10[var_r29], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_10[var_r29], HU3D_MOTATTR_PAUSE);
            }
            fn_1_45BC(object);
            fn_1_4EEC(7, 5);
            var_r25->unkA = 1;
            lbl_1_data_EC[0]++;
            var_r24 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (fn_1_F4FC(var_r31) >= 0) {
                    var_r28 = (unkStruct2 *)var_r24[fn_1_F4FC(var_r31)]->data;
                    switch (var_r28->unk0 & 0xF) {
                        case 6:
                            omVibrate(var_r28->unk4, 0x30, 0xC, 0);
                            break;
                        case 8:
                            omVibrate(var_r28->unk4, 0x30, 4, 2);
                            break;
                    }
                }
            }
            return;
        case 3:
            if (lbl_1_bss_64[0].unk3C == 0) {
                for (var_r27 = 1; var_r27 < 4; var_r27++) {
                    Hu3DMotionTimeSet(lbl_1_bss_10[var_r27], 0.0f);
                    Hu3DModelAttrSet(lbl_1_bss_10[var_r27], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_10[var_r27], HU3D_MOTATTR_PAUSE);
                }
                Hu3DModelAttrSet(object->model[2], HU3D_MOTATTR_PAUSE);
                Hu3DMotionTimeSet(object->model[2], 0.0f);
                for (var_r31 = 0; var_r31 < lbl_1_bss_60; var_r31++) {
                    Hu3DModelAttrSet(lbl_1_bss_64[var_r31].unk0, HU3D_ATTR_DISPOFF);
                }
                fn_1_4558(object);
                if (lbl_1_data_1D8 >= 0) {
                    fn_1_EF50();
                    fn_1_4EEC(0x18, 0x18);
                    fn_1_4EEC(0x40, 0x40);
                    fn_1_4EEC(7, 1);
                    HuAudFXPlay(0x70E);
                }
                else {
                    fn_1_4EEC(7, 2);
                    var_r26 = lbl_1_bss_6C->data;
                    var_r26[0] &= 0xFFFFFFF8;
                    var_r26[0] |= 4;
                }
                lbl_1_data_EC[0] = 0;
            }
    }
}

void fn_1_4558(omObjData *object)
{
    s16 var_r31;

    for (var_r31 = 0; var_r31 < lbl_1_bss_60; var_r31++) {
        fn_1_4F34(&lbl_1_bss_64[var_r31]);
    }
}

void fn_1_45BC(omObjData *object)
{
    Vec sp8;
    s16 var_r31;

    sp8.x = 0.0f;
    sp8.y = 250.0f;
    sp8.z = 0.0f;

    for (var_r31 = 0; var_r31 < lbl_1_bss_60; var_r31++) {
        fn_1_5010(&lbl_1_bss_64[var_r31], &sp8, 1500.0f);
    }
}

void fn_1_4660(omObjData *object)
{
    void *sp8;
    s16 temp_r3;

    sp8 = object->data;
    switch (fn_1_4EA8(0x18)) {
        case 8:
            fn_1_46E0(object);
            return;
        case 16:
            fn_1_4A20(object);
            return;
        case 24:
            fn_1_4B44(object);
    }
}

void fn_1_46E0(omObjData *object)
{
    f32 var_f31;
    s16 temp_r0;
    s16 var_r30;
    s32 temp_r28;
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)object->data;
    switch (lbl_1_data_104[0]) {
        case 0x0:
            fn_1_4E00(-1, 0.0f);

            for (var_r30 = 0; var_r30 < 5; var_r30++) {
                Hu3DMotionTimeSet(object->model[var_r30 + 4], 0.0f);
                lbl_1_data_14[var_r30] = 0;
            }
            temp_r31->unk2C = (((rand8() << 8) | rand8()) % (s16)temp_r31->unk1C);
            temp_r31->unk24 = 0.0f;
            lbl_1_data_108[0] = 0;
            lbl_1_data_104[0]++;
            break;
        case 0x1:
            lbl_1_data_108[0]++;
            var_f31 = lbl_1_data_108[0] / REFRESH_RATE_F;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
                lbl_1_data_108[0] = 0;
                lbl_1_data_104[0] = 0;
                fn_1_4EEC(0x18, 0x10);
                HuAudFXPlay(0x70F);
            }
            var_f31 = sind(90.0f * var_f31);
            temp_r31->unk24 = (150.0f * var_f31);
            break;
        case 0x63:
            if (++lbl_1_data_108[0] > lbl_1_data_108[1]) {
                lbl_1_data_108[0] = 0;
                lbl_1_data_104[0] = lbl_1_data_104[1];
            }
            break;
    }

    for (var_r30 = 0; var_r30 < temp_r31->unk1C; var_r30++) {
        Hu3DData[object->model[var_r30 + 4]].pos.y = temp_r31->unk24;
        lbl_1_data_14[var_r30] = 1;
    }
    Hu3DData[object->model[1]].pos.y = temp_r31->unk24;
}

void fn_1_4A20(omObjData *object)
{
    ModelData *temp_r31;
    s16 temp_r28;
    unkStruct2 *temp_r30;
    f32 var_f31;

    temp_r30 = (unkStruct2 *)object->data;
    temp_r28 = temp_r30->unk2E;
    if (temp_r28 != -1) {
        temp_r31 = &Hu3DData[object->model[temp_r28 + 4]];
        if (-1.0f == temp_r30->unk30) {
            if (0.0f != temp_r31->unk_64) {
                temp_r31->unk_64 -= 4.0f;
                if (temp_r31->unk_64 < 0.0f) {
                    temp_r31->unk_64 = 0.0f;
                }
            }
        }
        else {
            var_f31 = Hu3DMotionMaxTimeGet(object->model[temp_r28 + 4]);
            temp_r31->unk_64 = var_f31 * temp_r30->unk30;
        }
    }
}

void fn_1_4B44(omObjData *object)
{
    f32 var_f31;
    s16 var_r30;
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)object->data;
    switch (lbl_1_data_104[0]) {
        case 0:
            lbl_1_data_108[0]++;
            var_f31 = lbl_1_data_108[0] / REFRESH_RATE_F;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
                lbl_1_data_108[0] = 0;
                lbl_1_data_104[0]++;
            }
            var_f31 = sind(90.0f * var_f31);
            temp_r31->unk24 = (150.0f + (-150.0f * var_f31));
            break;
        case 1:
            lbl_1_data_108[0]++;
            var_f31 = (lbl_1_data_108[0] / (0.5f * REFRESH_RATE_F));
            if (var_f31 >= 1.0f) {
                lbl_1_data_108[0] = 0;
                lbl_1_data_104[0] = 0;
                if (fn_1_4EA8(0x40) != 0) {
                    temp_r31->unk1C--;
                }
                fn_1_4EEC(0x18, 8);
            }
            break;
    }

    for (var_r30 = 0; var_r30 < temp_r31->unk1C; var_r30++) {
        Hu3DData[object->model[var_r30 + 4]].pos.y = temp_r31->unk24;
        lbl_1_data_14[var_r30] = 1;
    }
    Hu3DData[object->model[1]].pos.y = temp_r31->unk24;
}

void fn_1_4E00(s16 arg0, f32 arg8)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_68->data;
    temp_r31->unk2E = arg0;
    temp_r31->unk30 = arg8;
}

s16 fn_1_4E2C(void)
{
    unkStruct2 *var_r31;

    var_r31 = (unkStruct2 *)lbl_1_bss_68->data;
    return var_r31->unk1C;
}

s16 fn_1_4E54(s16 arg0)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_68->data;
    if (arg0 == -1) {
        return temp_r31->unk2C;
    }
    if (arg0 == temp_r31->unk2C) {
        return 1;
    }
    return 0;
}

u16 fn_1_4EA8(u16 arg0)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_68->data;
    if (!temp_r31) {
        return 0;
    }
    return temp_r31->unk0 & arg0;
}

void fn_1_4EEC(u16 arg0, u16 arg1)
{
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_68->data;
    temp_r31->unk0 &= ~arg0;
    temp_r31->unk0 |= arg1;
}

void fn_1_4F34(unkStruct6 *arg0)
{
    s16 var_r30;
    unkStruct8 *var_r31;

    var_r31 = arg0->unk24;
    if (arg0->unk20 != 0) {
        for (var_r30 = 0; var_r30 < arg0->unk20; var_r30++, var_r31++) {
            var_r31->unk94.x = var_r31->unk94.y = var_r31->unk94.z = 0.0f;
            var_r31->unkA0.x = var_r31->unkA0.y = var_r31->unkA0.z = 0.0f;
            var_r31->unkAC.x = var_r31->unkAC.y = var_r31->unkAC.z = 0.0f;
            var_r31->unkB8.x = var_r31->unkB8.y = var_r31->unkB8.z = 0.0f;
            var_r31->unkC4.y = 0.0f;
        }
        arg0->unk2 &= ~4;
        arg0->unk3C = 0xFF;
        arg0->unk3E = 0;
    }
}

void fn_1_5010(unkStruct6 *arg0, Vec *arg1, f32 arg8)
{
    Vec sp14;
    ModelData *temp_r29;
    f32 var_f25;
    f32 var_f28;
    f32 var_f27;
    f32 var_f26;
    s32 var_r27;
    unkStruct8 *var_r31;

    var_r31 = arg0->unk24;
    if (arg0->unk20 != 0) {
        temp_r29 = &Hu3DData[arg0->unk0];
        arg0->unk2 |= 4;

        for (var_r27 = 0; var_r27 < arg0->unk20; var_r27++, var_r31++) {
            sp14.x = (var_r31->unk7C.x + temp_r29->pos.x) - arg1->x;
            sp14.y = (var_r31->unk7C.y + temp_r29->pos.y) - arg1->y;
            sp14.z = (var_r31->unk7C.z + temp_r29->pos.z) - arg1->z;
            var_f25 = sqrtf((sp14.z * sp14.z) + ((sp14.x * sp14.x) + (sp14.y * sp14.y)));
            sp14.x /= var_f25;
            sp14.y /= var_f25;
            sp14.z /= var_f25;

            var_f25 = (1.0f - (var_f25 / arg8));
            if (var_f25 < 0.0f) {
                var_f25 = 0.0f;
            }
            var_f28 = (ABS(sp14.x) < 0.1f) ? 100.0f : 100.0f * sp14.x;
            var_f27 = (ABS(sp14.y) < 0.1f) ? 100.0f : 100.0f * sp14.y;
            var_f26 = (ABS(sp14.z) < 0.1f) ? 100.0f : 100.0f * sp14.z;
            sp14.x += (0.001f * (-var_f28 + (((rand8() << 8) | rand8()) % (s16)(1.0f + (var_f28 - -var_f28)))));
            sp14.y += (0.001f * (-var_f27 + (((rand8() << 8) | rand8()) % (s16)(1.0f + (var_f27 - -var_f27)))));
            sp14.z += (0.001f * (-var_f26 + (((rand8() << 8) | rand8()) % (s16)(1.0f + (var_f26 - -var_f26)))));
            var_r31->unkAC.x = (sp14.x * ((((rand8() << 8) | rand8()) % 21) + 0x50));
            var_r31->unkAC.y = (sp14.y * ((((rand8() << 8) | rand8()) % 16) + 0x1E));
            var_r31->unkAC.z = (sp14.z * ((((rand8() << 8) | rand8()) % 21) + 0x50));
            var_r31->unkC4.y = 1.47f;
            var_r31->unkB8.x = (120.0f * (-sp14.z * ABS(sp14.y)));
            var_r31->unkB8.z = (120.0f * (-sp14.x * ABS(sp14.y)));
        }
    }
}

void fn_1_57B4(unkStruct6 *arg0)
{
    Mtx sp14;
    Vec sp8;
    s16 var_r29;
    Vec *temp_r26;
    s32 var_r27;
    s32 var_r28;
    unkStruct8 *var_r31;

    var_r31 = arg0->unk24;
    temp_r26 = arg0->unk10;

    for (var_r27 = 0; var_r27 < arg0->unk20; var_r27++, var_r31++) {
        var_r31->unkAC.y = (var_r31->unkAC.y - var_r31->unkC4.y);
        var_r31->unk94.x = (var_r31->unk94.x + var_r31->unkAC.x);
        var_r31->unk94.y = (var_r31->unk94.y + var_r31->unkAC.y);
        var_r31->unk94.z = (var_r31->unk94.z + var_r31->unkAC.z);
        var_r31->unkA0.x = (var_r31->unkA0.x + var_r31->unkB8.x);
        var_r31->unkA0.y = (var_r31->unkA0.y + var_r31->unkB8.y);
        var_r31->unkA0.z = (var_r31->unkA0.z + var_r31->unkB8.z);
        if ((var_r31->unk94.x < -500.0f) || (var_r31->unk94.x > 500.0f)) {
            var_r31->unkAC.x = (0.5f * -var_r31->unkAC.x);
            var_r31->unkB8.x = (0.5f * -var_r31->unkB8.x);
        }
        if (var_r31->unk94.z < -500.0f) {
            var_r31->unkAC.z = (0.5f * -var_r31->unkAC.z);
            var_r31->unkB8.z = (0.5f * -var_r31->unkB8.z);
        }
        if ((var_r31->unk7C.y + var_r31->unk94.y) < -250.0f) {
            if (var_r31->unkAC.y > -2.0f) {
                var_r31->unk94.y = (-250.0f - var_r31->unk7C.y);
                var_r31->unkAC.x = 0.0f;
                var_r31->unkAC.y = 0.0f;
                var_r31->unkAC.z = 0.0f;
                var_r31->unkB8.x = 0.0f;
                var_r31->unkB8.z = 0.0f;
            }
            else {
                var_r31->unkAC.x *= 0.5f;
                var_r31->unkAC.y = -(0.3f * var_r31->unkAC.y);
                var_r31->unkAC.z *= 0.5f;
                var_r31->unkB8.x *= 0.5f;
                var_r31->unkB8.z *= 0.5f;
            }
        }
        MTXScale(sp14, var_r31->unk88.x, var_r31->unk88.y, var_r31->unk88.z);
        mtxTransCat(sp14, -var_r31->unk7C.x, -var_r31->unk7C.y, -var_r31->unk7C.z);
        mtxRotCat(sp14, var_r31->unkA0.x, var_r31->unkA0.y, var_r31->unkA0.z);
        mtxTransCat(sp14, var_r31->unk94.x + var_r31->unk7C.x, var_r31->unk94.y + var_r31->unk7C.y, var_r31->unk94.z + var_r31->unk7C.z);

        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            if ((arg0->unk2 & 1) != 0) {
                var_r29 = var_r31->unk0[var_r28].unk0;
            }
            else {
                var_r29 = var_r31->unk18[var_r28];
            }
            MTXMultVec(sp14, &temp_r26[var_r29], &sp8);
            arg0->unkC[var_r29].x = sp8.x;
            arg0->unkC[var_r29].y = sp8.y;
            arg0->unkC[var_r29].z = sp8.z;
        }
        if ((arg0->unk2 & 2) != 0) {
            var_r29 = var_r31->unk1E;
            MTXMultVec(sp14, &temp_r26[var_r29], &sp8);
            arg0->unkC[var_r29].x = sp8.x;
            arg0->unkC[var_r29].y = sp8.y;
            arg0->unkC[var_r29].z = sp8.z;
        }
    }
    if ((arg0->unk2 & 4) != 0) {
        if (++arg0->unk3E > (4 * REFRESH_RATE / 3)) {
            arg0->unk3C = ((arg0->unk3C - 10) < 0) ? 0 : arg0->unk3C - 10;
        }
    }
    DCFlushRangeNoSync(arg0->unkC, arg0->unk8 * 0xC);
}

void fn_1_5C2C(s16 arg0, HsfObject *arg1, unkStruct6 *arg2, u16 arg3)
{
    Mtx sp68;
    Vec sp44[3];
    Vec sp38;
    Vec sp2C;
    ModelData *sp1C;
    GXColor sp18 = { 0xFF, 0xFF, 0xFF, 0xFF };
    Vec *var_r21;
    Vec *var_r19;
    s16 var_r20;
    HsfVector2f *var_r22;
    s16 var_r24;
    s16 var_r23;
    HsfTransform *var_r25;
    s16 var_r27;
    ModelData *var_r29;
    s16 var_r28;
    s16 var_r30;

    sp1C = &Hu3DData[arg0];
    arg2->unk20 = 0;
    if (arg1->type == 2) {
        var_r30 = Hu3DHookFuncCreate(&fn_1_806C);
        arg2->unk0 = var_r30;
        Hu3DModelLayerSet(var_r30, 1);
        var_r29 = &Hu3DData[var_r30];
        var_r29->unk_120 = (ParticleData *)arg2;
        var_r29->unk_58.x = var_r29->unk_58.z = var_r29->unk_58.y = 1.0f;
        arg2->unk2 = arg3;
        arg2->unk28 = &arg1->data.material[((s16 *)(arg1->data.face->data))[1] & 0xFFF];
        arg2->unk2C = arg1->data.attribute;
        arg2->unk38 = NULL;
        arg2->unk3C = 0xFF;
        arg2->unk3E = 0;
        arg2->unk18 = HuMemDirectMallocNum(HEAP_DATA, arg1->data.vertex->count * 0xC, var_r29->unk_48);
        fn_1_6554(arg2, arg1);
        fn_1_6B58(arg2, arg1);
        arg2->unkC = HuMemDirectMallocNum(HEAP_DATA, arg2->unk8 * 0xC, var_r29->unk_48);
        arg2->unk10 = HuMemDirectMallocNum(HEAP_DATA, arg2->unk8 * 0xC, var_r29->unk_48);
        arg2->unk14 = HuMemDirectMallocNum(HEAP_DATA, arg2->unk8 * 0xC, var_r29->unk_48);
        if (arg2->unk28->numAttrs != 0) {
            arg2->unk1C = HuMemDirectMallocNum(HEAP_DATA, arg1->data.st->count * 8, var_r29->unk_48);
            var_r22 = arg1->data.st->data;
        }
        else {
            arg2->unk1C = NULL;
            var_r22 = NULL;
        }
        var_r25 = &arg1->data.base;
        MTXScale(sp68, var_r25->scale.x, var_r25->scale.y, var_r25->scale.z);
        mtxRotCat(sp68, var_r25->rot.x, var_r25->rot.y, var_r25->rot.z);
        mtxTransCat(sp68, var_r25->pos.x, var_r25->pos.y, var_r25->pos.z);

        for (var_r30 = 0; var_r30 < arg2->unk20; var_r30++) {
            sp2C.x = sp2C.y = sp2C.z = 0.0f;

            for (var_r28 = 0; var_r28 < 3; var_r28++) {
                if ((arg2->unk2 & 1) != 0) {
                    var_r23 = arg2->unk24[var_r30].unk0[var_r28].unk0;
                    var_r27 = var_r23;
                }
                else {
                    var_r27 = arg2->unk24[var_r30].unk18[var_r28];
                    var_r23 = arg2->unk24[var_r30].unk0[var_r28].unk0;
                }
                MTXMultVec(sp68, &((Vec *)(arg1->data.vertex->data))[var_r23], &sp38);
                arg2->unkC[var_r27] = sp38;
                sp44[var_r28] = arg2->unkC[var_r27];
                arg2->unk14[var_r27] = arg2->unk18[var_r23];
                sp2C.x += sp38.x;
                sp2C.y += sp38.y;
                sp2C.z += sp38.z;
                if (arg2->unk28->numAttrs != 0) {
                    var_r23 = arg2->unk24[var_r30].unk0[var_r28].unk6;
                    var_r27 = var_r23;
                    arg2->unk1C[var_r27].x = var_r22[var_r23].x;
                    arg2->unk1C[var_r27].y = var_r22[var_r23].y;
                }
            }
            fn_1_91A4(&sp44[0], &sp44[1], &sp44[2], arg2->unk24[var_r30].unk68);
            if ((arg2->unk2 & 2) != 0) {
                var_r27 = arg2->unk24[var_r30].unk1E;
                fn_1_71FC(arg2, &arg2->unkC[var_r27], var_r30, sp2C);
                sp2C.x += arg2->unkC[var_r27].x;
                sp2C.y += arg2->unkC[var_r27].y;
                sp2C.z += arg2->unkC[var_r27].z;
            }
            fn_1_7934(arg2, &arg2->unk24[var_r30], &sp2C);
        }
        memcpy(arg2->unk10, arg2->unkC, arg2->unk8 * 0xC);
        DCFlushRangeNoSync(arg2->unkC, arg2->unk8 * 0xC);
        DCFlushRangeNoSync(arg2->unk14, arg2->unk8 * 0xC);
        if (arg2->unk28->numAttrs != 0) {
            DCFlushRangeNoSync(arg2->unk1C, arg1->data.st->count * 8);
        }
        var_r20 = 0;
        var_r19 = var_r21 = HuMemDirectMallocNum(HEAP_DATA, 0x20000, var_r29->unk_48);
        GXBeginDisplayList(var_r19, 0x20000);
        if ((arg2->unk2 & 2) != 0) {
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, (arg2->unk20 * 0xC));

            for (var_r30 = 0; var_r30 < arg2->unk20; var_r30++) {

                for (var_r28 = 0; var_r28 < 3; var_r28++) {
                    if ((arg2->unk2 & 1) != 0) {
                        var_r27 = arg2->unk24[var_r30].unk0[var_r28].unk0;
                    }
                    else {
                        var_r27 = arg2->unk24[var_r30].unk18[var_r28];
                    }
                    GXPosition1x16(var_r27);
                    GXNormal1x16(var_r27);
                    if (arg2->unk28->numAttrs != 0) {
                        GXTexCoord1x16(arg2->unk24[var_r30].unk0[var_r28].unk6);
                    }
                }

                for (var_r24 = 0; var_r24 < 9; var_r24++) {
                    if (var_r20 < arg2->unk24[var_r30].unk20[var_r24].unk0) {
                        var_r20 = arg2->unk24[var_r30].unk20[var_r24].unk0;
                    }
                    GXPosition1x16(arg2->unk24[var_r30].unk20[var_r24].unk0);
                    GXNormal1x16(arg2->unk24[var_r30].unk20[var_r24].unk0);
                    if (arg2->unk28->numAttrs != 0) {
                        GXTexCoord1x16(arg2->unk24[var_r30].unk20[var_r24].unk6);
                    }
                }
            }
        }
        else {
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, (arg2->unk20 * 3));
            for (var_r30 = 0; var_r30 < arg2->unk20; var_r30++) {
                for (var_r28 = 0; var_r28 < 3; var_r28++) {
                    if ((arg2->unk2 & 1) != 0) {
                        var_r27 = arg2->unk24[var_r30].unk0[var_r28].unk0;
                    }
                    else {
                        var_r27 = arg2->unk24[var_r30].unk18[var_r28];
                    }
                    GXPosition1x16(var_r27);
                    GXNormal1x16(var_r27);
                    if (arg2->unk28->numAttrs != 0) {
                        GXTexCoord1x16(arg2->unk24[var_r30].unk0[var_r28].unk6);
                    }
                }
            }
        }
        arg2->unk34 = GXEndDisplayList();
        DCFlushRangeNoSync(var_r21, arg2->unk34);
        arg2->unk30 = HuMemDirectMallocNum(HEAP_DATA, arg2->unk34, var_r29->unk_48);
        memcpy(arg2->unk30, var_r21, arg2->unk34);
        DCFlushRangeNoSync(arg2->unk30, arg2->unk34);
        HuMemDirectFree(var_r21);
    }
}

void fn_1_6554(unkStruct6 *arg0, HsfObject *arg1)
{
    Vec sp20[3];
    f32 spC[5];
    f32 var_f28;
    HsfBuffer *temp_r26;
    s16 var_r28;
    s16 var_r29;
    unkStruct10 *var_r30;

    temp_r26 = arg1->data.face;

    for (var_r28 = 0; var_r28 < arg1->data.vertex->count; var_r28++) {
        arg0->unk18[var_r28].x = 0.0f;
        arg0->unk18[var_r28].y = 0.0f;
        arg0->unk18[var_r28].z = 0.0f;
    }
    var_r30 = (unkStruct10 *)temp_r26->data;

    for (var_r28 = 0; var_r28 < temp_r26->count; var_r28++, var_r30++) {
        sp20[0] = ((Vec *)(arg1->data.vertex->data))[var_r30->unk4[0].unk0];
        sp20[1] = ((Vec *)(arg1->data.vertex->data))[var_r30->unk4[1].unk0];
        sp20[2] = ((Vec *)(arg1->data.vertex->data))[var_r30->unk4[2].unk0];
        fn_1_91A4(&sp20[0], &sp20[1], &sp20[2], spC);
        spC[0] = -spC[0];
        spC[1] = -spC[1];
        spC[2] = -spC[2];
        switch (var_r30->unk0 & 7) {
            case 2:
                for (var_r29 = 0; var_r29 < 3; var_r29++) {
                    arg0->unk18[var_r30->unk4[var_r29].unk0].x += spC[0];
                    arg0->unk18[var_r30->unk4[var_r29].unk0].y += spC[1];
                    arg0->unk18[var_r30->unk4[var_r29].unk0].z += spC[2];
                }
                break;
            case 3:
                for (var_r29 = 0; var_r29 < 4; var_r29++) {
                    arg0->unk18[var_r30->unk4[var_r29].unk0].x += spC[0];
                    arg0->unk18[var_r30->unk4[var_r29].unk0].y += spC[1];
                    arg0->unk18[var_r30->unk4[var_r29].unk0].z += spC[2];
                }
                break;
            case 4:
                for (var_r29 = 0; var_r29 < 3; var_r29++) {
                    arg0->unk18[var_r30->unk4[var_r29].unk0].x += spC[0];
                    arg0->unk18[var_r30->unk4[var_r29].unk0].y += spC[1];
                    arg0->unk18[var_r30->unk4[var_r29].unk0].z += spC[2];
                }
                for (var_r29 = 0; var_r29 < var_r30->unk1C; var_r29++) {
                    arg0->unk18[var_r30->unk20[var_r29].unk0].x += spC[0];
                    arg0->unk18[var_r30->unk20[var_r29].unk0].y += spC[1];
                    arg0->unk18[var_r30->unk20[var_r29].unk0].z += spC[2];
                }
                break;
        }
    }

    for (var_r28 = 0; var_r28 < arg1->data.vertex->count; var_r28++) {
        sp20[0].x = arg0->unk18[var_r28].x;
        sp20[0].y = arg0->unk18[var_r28].y;
        sp20[0].z = arg0->unk18[var_r28].z;
        var_f28 = sqrtf((sp20[0].z * sp20[0].z) + ((sp20[0].x * sp20[0].x) + (sp20[0].y * sp20[0].y)));
        arg0->unk18[var_r28].x /= var_f28;
        arg0->unk18[var_r28].y /= var_f28;
        arg0->unk18[var_r28].z /= var_f28;
    }
}

void fn_1_6B58(unkStruct6 *arg0, HsfObject *arg1)
{
    HsfBuffer *temp_r25;
    s32 var_r28;
    s32 var_r30;
    u8 var_r24;
    ModelData *var_r22;
    unkStruct8 *var_r31;
    unkStruct11 *temp_r26;
    unkStruct10 *var_r29;

    var_r22 = &Hu3DData[arg0->unk0];
    temp_r25 = arg1->data.face;
    var_r24 = ((arg0->unk2 & 1) != 0) ? 1 : 0;
    arg0->unk20 = 0;

    var_r28 = 0;
    var_r29 = (unkStruct10 *)temp_r25->data;
    for (; var_r28 < temp_r25->count; var_r28++, var_r29++) {
        switch (var_r29->unk0 & 7) {
            case 2:
                arg0->unk20 += 1;
                break;
            case 3:
                arg0->unk20 += 2;
                break;
            case 4:
                arg0->unk20 += var_r29->unk1C + 1;
                break;
        }
    }
    arg0->unk24 = HuMemDirectMallocNum(HEAP_DATA, arg0->unk20 * 0xD0, var_r22->unk_48);
    var_r31 = arg0->unk24;
    if (var_r24 != 0) {
        var_r30 = arg1->data.vertex->count;
    }
    else {
        var_r30 = 0;
    }

    var_r28 = 0;
    var_r29 = (unkStruct10 *)temp_r25->data;
    for (; var_r28 < temp_r25->count; var_r28++, var_r29++) {
        switch (var_r29->unk0 & 7) {
            case 2:
                var_r31->unk0[0] = var_r29->unk4[0];
                var_r31->unk0[1] = var_r29->unk4[2];
                var_r31->unk0[2] = var_r29->unk4[1];
                if (var_r24 == 0) {
                    var_r31->unk18[0] = var_r30++;
                    var_r31->unk18[1] = var_r30++;
                    var_r31->unk18[2] = var_r30++;
                }
                var_r31->unk1E = var_r30++;
                var_r31++;
                break;
            case 3:
                var_r31->unk0[0] = var_r29->unk4[0];
                var_r31->unk0[1] = var_r29->unk4[2];
                var_r31->unk0[2] = var_r29->unk4[1];
                if (var_r24 == 0) {
                    var_r31->unk18[0] = var_r30++;
                    var_r31->unk18[1] = var_r30++;
                    var_r31->unk18[2] = var_r30++;
                }
                var_r31->unk1E = var_r30++;
                var_r31++;
                var_r31->unk0[0] = var_r29->unk4[1];
                var_r31->unk0[1] = var_r29->unk4[2];
                var_r31->unk0[2] = var_r29->unk4[3];
                if (var_r24 == 0) {
                    var_r31->unk18[0] = var_r30++;
                    var_r31->unk18[1] = var_r30++;
                    var_r31->unk18[2] = var_r30++;
                }
                var_r31->unk1E = var_r30++;
                var_r31++;
                break;
            case 4:
                var_r31->unk0[0] = var_r29->unk4[0];
                var_r31->unk0[1] = var_r29->unk4[2];
                var_r31->unk0[2] = var_r29->unk4[1];
                if (var_r24 == 0) {
                    var_r31->unk18[0] = var_r30++;
                    var_r31->unk18[1] = var_r30++;
                    var_r31->unk18[2] = var_r30++;
                }
                var_r31->unk1E = var_r30++;
                var_r31++;
                var_r28 = 0;
                temp_r26 = var_r29->unk20;
                for (; var_r28 < var_r29->unk1C; var_r28++) {
                    if (var_r28 == 0) {
                        var_r31->unk0[0] = var_r31->unk0[1];
                        var_r31->unk0[1] = var_r31->unk0[2];
                        var_r31->unk0[2] = temp_r26[0];
                    }
                    else if (var_r28 == 1) {
                        var_r31->unk0[0] = var_r31->unk0[2];
                        var_r31->unk0[1] = temp_r26[1];
                        var_r31->unk0[2] = temp_r26[0];
                    }
                    else {
                        if ((var_r28 % 2) != 0) {
                            var_r31->unk0[0] = temp_r26[var_r28 - 2];
                            var_r31->unk0[1] = temp_r26[var_r28 - 0];
                            var_r31->unk0[2] = temp_r26[var_r28 - 1];
                        }
                        else {
                            var_r31->unk0[0] = temp_r26[var_r28 - 2];
                            var_r31->unk0[1] = temp_r26[var_r28 - 1];
                            var_r31->unk0[2] = temp_r26[var_r28 - 0];
                        }
                    }
                    if (var_r24 == 0) {
                        var_r31->unk18[0] = var_r30++;
                        var_r31->unk18[1] = var_r30++;
                        var_r31->unk18[2] = var_r30++;
                    }
                    var_r31->unk1E = var_r30++;
                    var_r31++;
                }
                break;
        }
    }
    arg0->unk8 = var_r30;
}

void fn_1_71FC(unkStruct6 *arg0, Vec *arg1, s16 arg2, Vec arg3)
{
    Vec sp40;
    Vec sp34;
    Vec sp28[3];
    Vec sp1C;
    unkStruct8 *temp_r30 = &arg0->unk24[arg2];
    s16 sp10[3][2] = { { 0, 1 }, { 0, 2 }, { 1, 2 } };
    f32 var_f31;
    f32 var_f30;
    f32 var_f29;
    f32 var_f27;
    s16 var_r31;

    if ((arg0->unk2 & 1) != 0) {
        sp28[0] = arg0->unkC[temp_r30->unk0[0].unk0];
        sp28[1] = arg0->unkC[temp_r30->unk0[1].unk0];
        sp28[2] = arg0->unkC[temp_r30->unk0[2].unk0];
    }
    else {
        sp28[0] = arg0->unkC[temp_r30->unk18[0]];
        sp28[1] = arg0->unkC[temp_r30->unk18[1]];
        sp28[2] = arg0->unkC[temp_r30->unk18[2]];
    }
    sp1C.x = temp_r30->unk68[0];
    sp1C.y = temp_r30->unk68[1];
    sp1C.z = temp_r30->unk68[2];
    VECNormalize(&sp1C, &sp1C);
    var_f31 = var_f30 = var_f29 = 0.0f;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_f31 += (sp28[sp10[var_r31][0]].x - sp28[sp10[var_r31][1]].x < 0.0f) ? -(sp28[sp10[var_r31][0]].x - sp28[sp10[var_r31][1]].x)
                                                                                : (sp28[sp10[var_r31][0]].x - sp28[sp10[var_r31][1]].x);

        var_f30 += (sp28[sp10[var_r31][0]].y - sp28[sp10[var_r31][1]].y < 0.0f) ? -(sp28[sp10[var_r31][0]].y - sp28[sp10[var_r31][1]].y)
                                                                                : (sp28[sp10[var_r31][0]].y - sp28[sp10[var_r31][1]].y);

        var_f29 += (sp28[sp10[var_r31][0]].z - sp28[sp10[var_r31][1]].z < 0.0f) ? -(sp28[sp10[var_r31][0]].z - sp28[sp10[var_r31][1]].z)
                                                                                : (sp28[sp10[var_r31][0]].z - sp28[sp10[var_r31][1]].z);
    }
    var_f31 *= 0.3333f;
    var_f30 *= 0.3333f;
    var_f29 *= 0.3333f;
    var_f27 = 0.5f * sqrtf((var_f29 * var_f29) + ((var_f31 * var_f31) + (var_f30 * var_f30)));
    sp28[0].x = 0.3333f * arg3.x;
    sp28[0].y = 0.3333f * arg3.y;
    sp28[0].z = 0.3333f * arg3.z;
    arg1->x = (sp28[0].x - (sp1C.x * var_f27));
    arg1->y = (sp28[0].y - (sp1C.y * var_f27));
    arg1->z = (sp28[0].z - (sp1C.z * var_f27));
}

void fn_1_7934(unkStruct6 *arg0, unkStruct8 *arg1, Vec *arg2)
{
    Vec sp2C[3];
    f32 sp18[5];
    s16 sp10[4];
    s16 sp8[4];
    s16 var_r28;
    Vec *temp_r30;
    Vec *temp_r4;
    Vec *temp_r4_2;
    Vec *temp_r4_3;

    arg1->unk88.x = arg1->unk88.y = arg1->unk88.z = 1.0f;
    arg1->unk94.x = arg1->unk94.y = arg1->unk94.z = 0.0f;
    arg1->unkA0.x = arg1->unkA0.y = arg1->unkA0.z = 0.0f;
    arg1->unkAC.x = arg1->unkAC.y = arg1->unkAC.z = 0.0f;
    arg1->unkB8.x = arg1->unkB8.y = arg1->unkB8.z = 0.0f;
    arg1->unkC4.x = arg1->unkC4.y = arg1->unkC4.z = 0.0f;

    if ((arg0->unk2 & 2) != 0) {
        arg2->x *= 0.25f;
        arg2->y *= 0.25f;
        arg2->z *= 0.25f;
    }
    else {
        arg2->x /= 3.0f;
        arg2->y /= 3.0f;
        arg2->z /= 3.0f;
    }
    arg1->unk7C.x = arg2->x;
    arg1->unk7C.y = arg2->y;
    arg1->unk7C.z = arg2->z;
    if ((arg0->unk2 & 2) != 0) {
        if ((arg0->unk2 & 1) != 0) {
            sp10[0] = arg1->unk0[0].unk0;
            sp10[1] = arg1->unk0[1].unk0;
            sp10[2] = arg1->unk0[2].unk0;
        }
        else {
            sp10[0] = arg1->unk18[0];
            sp10[1] = arg1->unk18[1];
            sp10[2] = arg1->unk18[2];
        }
        sp10[3] = arg1->unk1E;
        sp8[0] = arg1->unk0[0].unk6;
        sp8[1] = arg1->unk0[1].unk6;
        sp8[2] = arg1->unk0[2].unk6;
        sp8[3] = arg1->unk0[0].unk6;

        for (var_r28 = 0; var_r28 < 9; var_r28++) {
            arg1->unk20[var_r28].unk0 = sp10[lbl_1_data_10C[var_r28]];
            arg1->unk20[var_r28].unk6 = sp8[lbl_1_data_10C[var_r28]];
        }
        temp_r30 = &arg0->unk14[arg1->unk1E];
        temp_r30->x = temp_r30->y = temp_r30->z = 0.0f;

        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            sp2C[0] = arg0->unkC[sp10[lbl_1_data_10C[var_r28]]];
            sp2C[1] = arg0->unkC[sp10[lbl_1_data_10C[var_r28 + 1]]];
            sp2C[2] = arg0->unkC[sp10[lbl_1_data_10C[var_r28 + 2]]];
            fn_1_91A4(&sp2C[0], &sp2C[1], &sp2C[2], sp18);
            temp_r30->x += sp18[0];
            temp_r30->y += sp18[1];
            temp_r30->z += sp18[2];
        }
        temp_r30->x *= 0.3333f;
        temp_r30->y *= 0.3333f;
        temp_r30->z *= 0.3333f;
    }
}

void fn_1_7D60(unkStruct15 *arg0, unkStruct13 *arg1, s16 arg2)
{
    GXTexObj sp1C;
    GXTlutObj sp10;
    s32 sp8;
    s16 temp_r29;
    s16 temp_r28;
    s16 var_r27;
    s16 var_r26;

    if (!arg0) {
        OSReport("Error: No Texture\n");
        return;
    }
    temp_r29 = arg0->unkA;
    temp_r28 = arg0->unkC;
    var_r27 = (arg1->unk64 == 1) ? 1 : 0;
    var_r26 = (arg1->unk68 == 1) ? 1 : 0;
    switch (arg0->unk8) {
        case 6:
            GXInitTexObj(&sp1C, arg0->unk1C, temp_r29, temp_r28, GX_TF_RGBA8, var_r27, var_r26, GX_FALSE);
            break;
        case 4:
            GXInitTexObj(&sp1C, arg0->unk1C, temp_r29, temp_r28, GX_TF_RGB565, var_r27, var_r26, GX_FALSE);
            break;
        case 5:
            GXInitTexObj(&sp1C, arg0->unk1C, temp_r29, temp_r28, GX_TF_RGB5A3, var_r27, var_r26, GX_FALSE);
            break;
        case 9:
            if (arg0->unk9 < 8) {
                GXInitTlutObj(&sp10, arg0->unk14, GX_TL_RGB565, arg0->unkE);
                GXLoadTlut(&sp10, arg2);
                GXInitTexObjCI(&sp1C, arg0->unk1C, temp_r29, temp_r28, GX_TF_C4, var_r27, var_r26, GX_FALSE, arg2);
            }
            else {
                GXInitTlutObj(&sp10, arg0->unk14, GX_TL_RGB565, arg0->unkE);
                GXLoadTlut(&sp10, arg2);
                GXInitTexObjCI(&sp1C, arg0->unk1C, temp_r29, temp_r28, GX_TF_C8, var_r27, var_r26, GX_FALSE, arg2);
            }
            break;
        case 10:
            if (arg0->unk9 < 8) {
                GXInitTlutObj(&sp10, arg0->unk14, GX_TL_RGB5A3, arg0->unkE);
                GXLoadTlut(&sp10, arg2);
                GXInitTexObjCI(&sp1C, arg0->unk1C, temp_r29, temp_r28, GX_TF_C4, var_r27, var_r26, GX_FALSE, arg2);
            }
            else {
                GXInitTlutObj(&sp10, arg0->unk14, GX_TL_RGB5A3, arg0->unkE);
                GXLoadTlut(&sp10, arg2);
                GXInitTexObjCI(&sp1C, arg0->unk1C, temp_r29, temp_r28, GX_TF_C8, var_r27, var_r26, GX_FALSE, arg2);
            }
            break;
        default:
            OSReport("Error: Texture format\n");
            return;
    }
    GXInitTexObjLOD(&sp1C, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&sp1C, arg2);
#ifdef TARGET_PC
    GXDestroyTexObj(&sp1C);
    GXDestroyTlutObj(&sp10);
#endif
}

void fn_1_806C(ModelData *arg0, Mtx arg1)
{
    Mtx sp14;
    GXColor sp10;
    unkStruct13 *temp_r29;
    unkStruct14 *temp_r31;
    m440Func14 temp_r27;

    temp_r31 = (unkStruct14 *)arg0->unk_120;
    if (((u8)omPauseChk() == 0) && (temp_r31->unk38)) {
        temp_r27 = temp_r31->unk38;
        temp_r27(temp_r31);
    }
    GXLoadPosMtxImm(arg1, 0);
    MTXInvXpose(arg1, sp14);
    GXLoadNrmMtxImm(sp14, 0);
    fn_1_8AC4(arg1);
    sp10.r = (temp_r31->unk28->unkB[0] * arg0->unk_58.x);
    sp10.g = (temp_r31->unk28->unkB[1] * arg0->unk_58.z);
    sp10.b = (temp_r31->unk28->unkB[2] * arg0->unk_58.y);
    sp10.a = 0xFF;
    GXSetChanAmbColor(GX_COLOR0A0, sp10);
    sp10.r = temp_r31->unk28->unkE[0];
    sp10.g = temp_r31->unk28->unkE[1];
    sp10.b = temp_r31->unk28->unkE[2];
    sp10.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, sp10);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, temp_r31->unkC, 12);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_NRM, temp_r31->unk14, 12);
    lbl_1_bss_C = temp_r31->unk3C;
    if (temp_r31->unk28->unk34 == 0) {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumTexGens(0);
        GXSetNumChans(0);
    }
    else {
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetArray(GX_VA_TEX0, temp_r31->unk1C, 8);
        temp_r29 = &temp_r31->unk2C[temp_r31->unk28->unk38[0]];
        fn_1_7D60(temp_r29->unk80, temp_r29, 0);
        lbl_1_bss_2C = 1;
        HuSprTexLoad(*hiliteAnim, 0, lbl_1_bss_2C, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        fn_1_8470(temp_r31->unk28, temp_r29);
    }
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXCallDisplayList(temp_r31->unk30, temp_r31->unk34);
}

void fn_1_8470(unkStruct12 *arg0, unkStruct13 *arg1)
{
    ModelData sp40;
    Mtx sp10;
    GXColor spC;
    GXColor sp8;
    f32 var_f30;
    f32 var_f31;
    s16 temp_r29;
    u16 var_r31;
    u32 temp_r24;
    u16 var_r28;
    u16 var_r27;
    s32 var_r25;

    sp40.attr = 0x20000;
    temp_r24 = arg0->unk30;
    if ((arg0->unkA == 2) || (arg0->unkA == 3)) {
        var_r27 = 1;
    }
    else {
        var_r27 = 0;
        if ((arg0->unkA == 0) || (arg0->unkA == 5)) {
            var_r25 = 0;
        }
        else {
            var_r25 = 1;
        }
    }
    var_r28 = var_r31 = 1;
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    if (1.0f == arg1->unk20) {
        if (arg1->unkA == 0) {
            GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
            GXSetTevOrder(var_r31, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
            GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            var_r31++;
        }
        else {
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
    }
    else {
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    }
    if (var_r27 != 0) {
        if (((sp40.attr & 0x20000) != 0) || ((temp_r24 & 0x100) != 0)) {
            spC.a = lbl_1_bss_C;
            GXSetTevColor(GX_TEVREG0, spC);
            GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX2, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(var_r31, var_r28, lbl_1_bss_2C, GX_COLOR0A0);
            GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_CPREV);
            GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            var_f31 = 6.0f * (arg0->unk14 / 300.0f);
            if (var_f31 < 0.1) {
                var_f31 = 0.1f;
            }
            MTXCopy(lbl_1_bss_30, sp10);
            mtxScaleCat(sp10, var_f31, var_f31, var_f31);
            GXLoadTexMtxImm(sp10, 0x24, GX_MTX2x4);
            var_r31++;
            var_r28++;
            var_r27 = 0;
            var_r25 = 1;
        }
        else {
            if (1.0f == arg1->unk20) {
                GXSetTevOrder(var_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR1A1);
                GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            }
            else {
                GXSetTevOrder(var_r31, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR1A1);
                GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_CPREV);
            }
            GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            var_r31++;
        }
    }
    else if (0.0f != arg0->unk1C) {
        GXSetTevOrder(var_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
        GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
        GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        var_r31++;
    }
    GXSetNumTexGens(var_r28);
    GXSetNumTevStages(var_r31);
    if (var_r27 != 0) {
        var_f30 = arg0->unk14;
    }
    else {
        var_f30 = 0.0f;
    }
    temp_r29 = Hu3DLightSet(&sp40, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, var_f30);
    if (var_r27 != 0) {
        GXSetNumChans(2);
        if (arg0->unkA == 5) {
            GXSetChanCtrl(GX_COLOR0A0, 1, GX_SRC_REG, GX_SRC_VTX, temp_r29, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR1A1, 1, GX_SRC_REG, GX_SRC_VTX, temp_r29, GX_DF_NONE, GX_AF_SPEC);
            return;
        }
        GXSetChanCtrl(GX_COLOR0A0, 1, GX_SRC_REG, GX_SRC_REG, temp_r29, GX_DF_CLAMP, GX_AF_NONE);
        GXSetChanCtrl(GX_COLOR1A1, 1, GX_SRC_REG, GX_SRC_REG, temp_r29, GX_DF_NONE, GX_AF_SPEC);
        return;
    }
    GXSetNumChans(1);
    if (arg0->unkA == 5) {
        GXSetChanCtrl(GX_COLOR0A0, var_r25, GX_SRC_REG, GX_SRC_REG, temp_r29, GX_DF_CLAMP, GX_AF_SPOT);
        return;
    }
    GXSetChanCtrl(GX_COLOR0A0, var_r25, GX_SRC_REG, GX_SRC_REG, temp_r29, GX_DF_CLAMP, GX_AF_SPOT);
}

void fn_1_8AC4(Mtx arg0)
{
    Mtx spA0;
    Mtx sp70;
    Mtx sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10 = { 0, 0, -1 };
    f32 var_f29;
    f32 var_f30;
    LightData *var_r29;
    s16 temp_r31;

    var_r29 = &Hu3DGlobalLight[0];
    sp34 = var_r29->unk_28;
    if ((var_r29->unk_00 & 0x8000) != 0) {
        MTXMultVecSR(Hu3DCameraMtx, &sp34, &sp34);
    }
    var_f30 = VECDotProduct(&sp34, &sp10);
    var_f30 *= 10000.0f;
    OSf32tos16(&var_f30, &temp_r31);
    if (temp_r31 == -0x2710) {
        MTXScale(lbl_1_bss_30, 0.0f, 0.0f, 0.0f);
        return;
    }
    C_VECHalfAngle(&sp34, &sp10, &sp28);
    sp28.x = -sp28.x;
    sp28.y = -sp28.y;
    sp28.z = -sp28.z;
    MTXInvXpose(arg0, sp70);
    if (temp_r31 == 0x2710) {
        MTXIdentity(sp40);
    }
    else {
        VECCrossProduct(&sp28, &sp10, &sp1C);
        var_f29 = acosf(VECDotProduct(&sp10, &sp28));
        MTXRotAxisRad(sp40, &sp1C, var_f29);
    }
    MTXConcat(sp40, sp70, spA0);
    MTXTrans(sp40, 0.5f, 0.5f, 0.0f);
    MTXConcat(sp40, spA0, lbl_1_bss_30);
}

void fn_1_8D1C(void)
{
    Mtx44 sp60;
    Mtx sp30;
    GXTexObj sp10;
    GXColor spC;
    u16 var_r30;
    unkStruct2 *temp_r31;

    temp_r31 = (unkStruct2 *)lbl_1_bss_68->data;
    if (!temp_r31) {
        var_r30 = 0;
    }
    else {
        var_r30 = temp_r31->unk0 & 7;
    }

    if (var_r30 == 5) {
        C_MTXOrtho(sp60, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 10.0f);
        GXSetProjection(sp60, GX_ORTHOGRAPHIC);
        MTXIdentity(sp30);
        GXLoadPosMtxImm(sp30, 0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXInitTexObj(&sp10, lbl_1_bss_28, 0x280, 0x1E0, 6, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&sp10, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&sp10, GX_TEXMAP0);
        GXSetNumTevStages(1);
        spC.a = 0xC4;
        GXSetTevColor(GX_TEVREG0, spC);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetZMode(0, GX_LEQUAL, GX_FALSE);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(0.0f, 0.0f, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(640.0f, 0.0f, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(640.0f, 480.0f, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(0.0f, 480.0f, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
    }
    GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
    GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGBA8, GX_FALSE);
    GXCopyTex(lbl_1_bss_28, 0);
    DCFlushRange(lbl_1_bss_28, lbl_1_bss_24);
#ifdef TARGET_PC
    GXDestroyTexObj(&sp10);
#endif
}

void fn_1_91A4(Vec *arg0, Vec *arg1, Vec *arg2, f32 arg3[5])
{
    Vec sp14;
    Vec sp8;

    sp14.x = arg1->x - arg0->x;
    sp14.y = arg1->y - arg0->y;
    sp14.z = arg1->z - arg0->z;
    sp8.x = arg2->x - arg1->x;
    sp8.y = arg2->y - arg1->y;
    sp8.z = arg2->z - arg1->z;
    arg3[0] = -((sp14.y * sp8.z) - (sp14.z * sp8.y));
    arg3[1] = -((sp14.z * sp8.x) - (sp14.x * sp8.z));
    arg3[2] = -((sp14.x * sp8.y) - (sp14.y * sp8.x));
}

f32 fn_1_927C(f32 arg8, f32 arg9, f32 argA)
{
    f32 var_f31;

    var_f31 = arg9 - arg8;
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    else if (var_f31 < -180.0f) {
        var_f31 += 360.0f;
    }
    var_f31 = arg8 + (var_f31 * argA);
    if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    else if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    return var_f31;
}

void fn_1_9344(Mtx arg0, Mtx arg1)
{
    arg1[0][0] = arg0[0][0];
    arg1[1][0] = arg0[0][1];
    arg1[2][0] = arg0[0][2];
    arg1[0][1] = arg0[1][0];
    arg1[1][1] = arg0[1][1];
    arg1[2][1] = arg0[1][2];
    arg1[0][2] = arg0[2][0];
    arg1[1][2] = arg0[2][1];
    arg1[2][2] = arg0[2][2];
    arg1[0][3] = 0.0f;
    arg1[1][3] = 0.0f;
    arg1[2][3] = 0.0f;
}

f32 fn_1_93C0(f32 arg0, f32 arg1, f32 arg2)
{
    return arg0 + (arg2 * (arg1 - arg0));
}

f32 fn_1_93D0(f32 arg8, f32 arg9, f32 argA, f32 argB)
{
    f32 temp_f31;

    temp_f31 = 1.0f - argB;
    return (argA * (argB * argB)) + ((arg8 * (temp_f31 * temp_f31)) + (arg9 * (2.0f * temp_f31 * argB)));
}

unkStruct4 *fn_1_942C(s16 arg0, Vec *arg1, Vec *arg2, f32 arg3, GXColor *arg4)
{
    ModelData *var_r28;
    s16 var_r29;
    unkStruct4 *var_r31;
    unkStruct14 *temp_r30;

    var_r28 = &Hu3DData[arg0];
    temp_r30 = var_r28->unk_120;
    var_r29 = 0;
    var_r31 = temp_r30->unk18;
    for (; var_r29 < temp_r30->unk0; var_r29++, var_r31++) {
        if (var_r31->unk62 == 0)
            break;
    }
    if (var_r29 == temp_r30->unk0) {
        return NULL;
    }
    temp_r30->unk24[var_r29].r = arg4->r;
    temp_r30->unk24[var_r29].g = arg4->g;
    temp_r30->unk24[var_r29].b = arg4->b;
    temp_r30->unk24[var_r29].a = arg4->a;
    var_r31->unk40 = var_r29;
    var_r31->unk44 = arg3;
    var_r31->unk48 = *arg2;
    var_r31->unk54 = *arg1;
    var_r31->unk60 = 0;
    var_r31->unk3C = 0;
    var_r31->unk62 = 1;
    return var_r31;
}

s16 fn_1_956C(AnimData *arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4)
{
    ModelData *temp_r28;
    s16 var_r20;
    s16 var_r22;
    s16 var_r19;
    HsfVector2f *var_r29;
    s16 var_r30;
    unkStruct5 *var_r31;
    void *var_r21;
    void *var_r18;
    unkStruct4 *var_r24;
    Vec *var_r25;
    GXColor *var_r27;

    var_r20 = Hu3DHookFuncCreate(fn_1_9C04);
    temp_r28 = &Hu3DData[var_r20];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, 0x68, temp_r28->unk_48);
    temp_r28->unk_120 = var_r31;
    arg0->useNum += 1;
    var_r31->unk10 = arg0;
    var_r31->unk0 = arg1;
    var_r31->unk8 = 0;
    var_r31->unkC = NULL;
    var_r24 = HuMemDirectMallocNum(HEAP_DATA, arg1 * 0x64, temp_r28->unk_48);
    var_r31->unk18 = var_r24;

    for (var_r30 = 0; var_r30 < arg1; var_r30++, var_r24++) {
        var_r24->unk60 = -1;
        var_r24->unk62 = 0;
    }
    var_r25 = HuMemDirectMallocNum(HEAP_DATA, arg1 * 0xC * 4, temp_r28->unk_48);
    var_r31->unk1C = var_r25;

    for (var_r30 = 0; var_r30 < (arg1 * 4); var_r30++, var_r25++) {
        var_r25->x = var_r25->y = var_r25->z = 0.0f;
    }
    var_r27 = HuMemDirectMallocNum(HEAP_DATA, arg1 * 4, temp_r28->unk_48);
    var_r31->unk24 = var_r27;

    for (var_r30 = 0; var_r30 < arg1; var_r30++, var_r27++) {
        var_r27->r = var_r27->g = var_r27->b = var_r27->a = 0xFF;
    }
    var_r29 = HuMemDirectMallocNum(HEAP_DATA, arg1 * 8 * 4, temp_r28->unk_48);
    var_r31->unk20 = var_r29;

    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        var_r29->x = 0.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 1.0f;
        var_r29++;
        var_r29->x = 0.0f;
        var_r29->y = 1.0f;
        var_r29++;
    }
    if ((arg3 != 0) || (arg4 != 0)) {
        var_r22 = (arg0->bmp->sizeX / arg3);
        var_r19 = arg0->bmp->sizeY / arg4;
        var_r31->unk14 = (var_r22 * var_r19);
        var_r31->unk60 = (1.0f / var_r22);
        var_r31->unk64 = (1.0f / var_r19);
    }
    else {
        var_r22 = 1;
        var_r31->unk14 = 1;
        var_r31->unk60 = 1.0f;
        var_r31->unk64 = 1.0f;
    }
    var_r31->unk5C = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * 8, temp_r28->unk_48);
    fn_1_A1B8(var_r31->unk5C, var_r31->unk14, var_r22, var_r31->unk60, var_r31->unk64);
    var_r31->unk2C.x = var_r31->unk50.x = var_r31->unk44.y = var_r31->unk50.y = -arg2;
    var_r31->unk38.x = var_r31->unk44.x = var_r31->unk2C.y = var_r31->unk38.y = arg2;
    var_r31->unk2C.z = var_r31->unk38.z = var_r31->unk44.z = var_r31->unk50.z = 0.0f;
    var_r21 = HuMemDirectMallocNum(HEAP_DATA, 0x20000, temp_r28->unk_48);
    var_r18 = var_r21;
    GXBeginDisplayList(var_r18, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, (arg1 * 4));

    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        GXPosition1x16(var_r30 * 4);
        GXColor1x16(var_r30);
        GXTexCoord1x16(var_r30 * 4);
        GXPosition1x16((var_r30 * 4) + 1);
        GXColor1x16(var_r30);
        GXTexCoord1x16((var_r30 * 4) + 1);
        GXPosition1x16((var_r30 * 4) + 2);
        GXColor1x16(var_r30);
        GXTexCoord1x16((var_r30 * 4) + 2);
        GXPosition1x16((var_r30 * 4) + 3);
        GXColor1x16(var_r30);
        GXTexCoord1x16((var_r30 * 4) + 3);
    }
    var_r31->unk4 = GXEndDisplayList();
    DCFlushRangeNoSync(var_r21, var_r31->unk4);
    var_r31->unk28 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk4, temp_r28->unk_48);
    memcpy(var_r31->unk28, var_r21, var_r31->unk4);
    DCFlushRangeNoSync(var_r31->unk28, var_r31->unk4);
    HuMemDirectFree(var_r21);
    return var_r20;
}

void fn_1_9AB0(s16 arg0)
{
    ModelData *data;
    unkStruct5 *temp2;

    data = &Hu3DData[arg0];
    temp2 = (unkStruct5 *)data->unk_120;
    HuSprAnimKill(temp2->unk10);
    Hu3DModelKill(arg0);
}

unkStruct5 *fn_1_9B10(s16 arg0)
{
    ModelData *data;

    data = &Hu3DData[arg0];
    return (unkStruct5 *)data->unk_120;
}

unkStruct4 *fn_1_9B3C(s16 arg0, s16 arg1)
{
    ModelData *data;
    unkStruct5 *temp;

    data = &Hu3DData[arg0];
    temp = (unkStruct5 *)data->unk_120;

    if (arg1 == -1) {
        return 0;
    }

    return &temp->unk18[arg1];
}

void fn_1_9B94(s16 arg0, m440Func5 arg1)
{
    ModelData *data;
    unkStruct5 *temp;

    data = &Hu3DData[arg0];
    temp = (unkStruct5 *)data->unk_120;
    temp->unkC = arg1;
}

void fn_1_9BCC(s16 arg0, u8 arg1)
{
    ModelData *data;
    unkStruct5 *temp;

    data = &Hu3DData[arg0];
    temp = (unkStruct5 *)data->unk_120;
    temp->unk8 = arg1;
}

void fn_1_9C04(ModelData *arg0, Mtx arg1)
{
    Mtx sp128;
    ROMtx spF8;
    Mtx spC8;
    Mtx sp98;
    Mtx sp68;
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Vec *var_r31;
    s16 temp_r0;
    u8 temp_r0_2;
    unkStruct5 *temp_r30;
    HsfVector2f *var_r27;
    s16 var_r26;
    unkStruct4 *var_r29;
    m440Func5 var_r23;

    temp_r30 = (unkStruct5 *)arg0->unk_120;
    GXLoadPosMtxImm(arg1, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    temp_r0 = temp_r30->unk10->bmp->dataFmt & 0xF;
    if ((temp_r0 == 7) || (temp_r0 == 8)) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXA, GX_CC_RASC, GX_CC_ZERO);
    }
    else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    }
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    HuSprTexLoad(temp_r30->unk10, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(0);
    switch (temp_r30->unk8) {
        case 0:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            break;
        case 1:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
            break;
        case 2:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
            break;
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, temp_r30->unk1C, 0xC);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, temp_r30->unk24, 4);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, temp_r30->unk20, 8);
    fn_1_9344(arg1, sp128);
    MTXReorder(sp128, spF8);
    if (((u8)omPauseChk() == 0) && (temp_r30->unkC)) {
        var_r23 = temp_r30->unkC;
        var_r23(arg0, temp_r30, arg1);
    }
    var_r29 = temp_r30->unk18;
    var_r31 = temp_r30->unk1C;
    var_r27 = temp_r30->unk20;
    MTXROMultVecArray(spF8, &temp_r30->unk2C, (Vec *)&sp68[0], 4);

    for (var_r26 = 0; var_r26 < temp_r30->unk0; var_r26++, var_r29++, var_r27 += 4) {
        if (var_r29->unk62 == 0) {
            var_r31->x = var_r31->y = var_r31->z = 0.0f;
            var_r31++;
            var_r31->x = var_r31->y = var_r31->z = 0.0f;
            var_r31++;
            var_r31->x = var_r31->y = var_r31->z = 0.0f;
            var_r31++;
            var_r31->x = var_r31->y = var_r31->z = 0.0f;
            var_r31++;
        }
        else {
            if (0.0f == var_r29->unk44) {
                fn_1_A328((Vec *)&sp68[0], &sp38, &var_r29->unk48, 4);
                VECAdd(&sp38, &var_r29->unk54, var_r31++);
                VECAdd(&sp44, &var_r29->unk54, var_r31++);
                VECAdd(&sp50, &var_r29->unk54, var_r31++);
                VECAdd(&sp5C, &var_r29->unk54, var_r31++);
            }
            else {
                fn_1_A328(&temp_r30->unk2C, &sp38, &var_r29->unk48, 4);
                MTXRotRad(spC8, 0x5A, 0.017453292f * var_r29->unk44);
                MTXConcat(sp128, spC8, sp98);
                MTXMultVecArray(sp98, &sp38, &sp8, 4);
                VECAdd(&sp8, &var_r29->unk54, var_r31++);
                VECAdd(&sp14, &var_r29->unk54, var_r31++);
                VECAdd(&sp20, &var_r29->unk54, var_r31++);
                VECAdd(&sp2C, &var_r29->unk54, var_r31++);
            }
            if (var_r29->unk60 != -1) {
                fn_1_A284(var_r27, temp_r30->unk5C, var_r29->unk60, temp_r30->unk60, temp_r30->unk64);
            }
        }
    }
    DCFlushRangeNoSync(temp_r30->unk1C, temp_r30->unk0 * 0xC * 4);
    DCFlushRangeNoSync(temp_r30->unk20, temp_r30->unk0 * 8 * 4);
    GXCallDisplayList(temp_r30->unk28, temp_r30->unk4);
}

void fn_1_A1B8(HsfVector2f *arg0, s16 arg1, s16 arg2, f32 arg8, f32 arg9)
{
    s16 var_r31;
    s16 var_r30;
    s16 var_r29;

    for (var_r31 = 0; var_r31 < arg1; var_r31++, arg0++) {
        var_r30 = (var_r31 % arg2);
        var_r29 = (var_r31 / arg2);
        arg0->x = (var_r30 * arg8);
        arg0->y = (var_r29 * arg9);
    }
}

void fn_1_A284(HsfVector2f *arg0, HsfVector2f *arg1, s16 arg2, f32 arg3, f32 arg4)
{
    arg0[0].x = arg1[arg2].x;
    arg0[0].y = arg1[arg2].y;
    arg0[1].x = (arg3 + arg1[arg2].x);
    arg0[1].y = arg1[arg2].y;
    arg0[2].x = (arg3 + arg1[arg2].x);
    arg0[2].y = (arg4 + arg1[arg2].y);
    arg0[3].x = arg1[arg2].x;
    arg0[3].y = (arg4 + arg1[arg2].y);
}

void fn_1_A328(Vec *arg0, Vec *arg1, Vec *arg2, s16 arg3)
{
    s16 var_r31;

    for (var_r31 = 0; var_r31 < arg3; var_r31++, arg0++, arg1++) {
        arg1->x = (arg0->x * arg2->x);
        arg1->y = (arg0->y * arg2->y);
        arg1->z = (arg0->z * arg2->z);
    }
}

static s8 lbl_1_data_148 = 0xFF;

void fn_1_A390(ModelData *arg0, Mtx arg1)
{
    if (lbl_1_bss_2 == 0) {
        if ((HuPadBtnDown[0] & 0x10) != 0) {
            lbl_1_bss_1 ^= 1;
        }
        if (lbl_1_bss_1 == 0)
            return;

        if ((HuPadBtn[0] & 1) != 0) {
            lbl_1_data_20.x -= 4.0f;
        }
        if ((HuPadBtn[0] & 2) != 0) {
            lbl_1_data_20.x += 4.0f;
        }
        lbl_1_data_2C.x += HuPadSubStkX[0];
        if ((HuPadBtn[0] & 0x20) != 0) {
            if ((HuPadBtn[0] & 8) != 0) {
                lbl_1_data_20.y -= 4.0f;
            }
            if ((HuPadBtn[0] & 4) != 0) {
                lbl_1_data_20.y += 4.0f;
            }
            lbl_1_data_2C.y += HuPadSubStkY[0];
        }
        else {
            if ((HuPadBtn[0] & 8) != 0) {
                lbl_1_data_20.z -= 4.0f;
            }
            if ((HuPadBtn[0] & 4) != 0) {
                lbl_1_data_20.z += 4.0f;
            }
            lbl_1_data_2C.z -= HuPadSubStkY[0];
        }
        lbl_1_data_54.x = lbl_1_data_2C.x;
        lbl_1_data_54.y = lbl_1_data_2C.y;
        lbl_1_data_54.z = lbl_1_data_2C.z;
        lbl_1_data_6C.x = lbl_1_data_20.x;
        lbl_1_data_6C.y = lbl_1_data_20.y;
        lbl_1_data_6C.z = lbl_1_data_20.z - 500.0f;
        Hu3DGLightPosSet(lbl_1_bss_E, lbl_1_data_2C.x, lbl_1_data_2C.y, lbl_1_data_2C.z, 0.0f, 0.0f, 0.0f);
        Hu3DGLightPosAimSetV(lbl_1_bss_E, &lbl_1_data_2C, &lbl_1_data_20);
        Hu3DShadowPosSet(&lbl_1_data_54, &lbl_1_data_60, &lbl_1_data_6C);
    }

    print8(8, 0x64, 1.5f, "InterXYZ: %.2f %.2f %.2f", lbl_1_data_20.x, lbl_1_data_20.y, lbl_1_data_20.z);
    print8(8, 0x70, 1.5f, "PositionXYZ: %.2f %.2f %.2f", lbl_1_data_2C.x, lbl_1_data_2C.y, lbl_1_data_2C.z);
    GXLoadPosMtxImm(arg1, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(lbl_1_data_20.x, lbl_1_data_20.y, lbl_1_data_20.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
    GXPosition3f32(lbl_1_data_2C.x, lbl_1_data_2C.y, lbl_1_data_2C.z);
    GXColor4u8(0xFF, 0x00, 0x00, 0xFF);
}

void fn_1_AA94(void)
{
    if ((HuPadBtnDown[0] & 0x40) != 0) {
        lbl_1_bss_2 ^= 1;
    }
    if (lbl_1_bss_2 != 0) {
        if ((HuPadBtn[0] & 1) != 0) {
            CRot.y += 1.0f;
        }
        if ((HuPadBtn[0] & 2) != 0) {
            CRot.y -= 1.0f;
        }
        if ((HuPadBtn[0] & 8) != 0) {
            CRot.x -= 1.0f;
        }
        if ((HuPadBtn[0] & 4) != 0) {
            CRot.x += 1.0f;
        }
        Center.x += HuPadSubStkX[0];
        if ((HuPadBtn[0] & 0x20) != 0) {
            Center.y += HuPadSubStkY[0];
        }
        else {
            Center.z += HuPadSubStkY[0];
        }
        if ((HuPadBtn[0] & 0x400) != 0) {
            CZoom += 10.0f;
        }
        if ((HuPadBtn[0] & 0x800) != 0) {
            CZoom -= 10.0f;
        }
        if ((HuPadBtnDown[0] & 0x100) != 0) {
            OSReport("\nCZoom = %.2f \n", CZoom);
            OSReport("Center x = %.2f: y = %.2f: z = %.2f \n", Center.x, Center.y, Center.z);
            OSReport("CRot x = %.2f: y = %.2f: z = %.2f \n", CRot.x, CRot.y, CRot.z);
        }
    }
}
