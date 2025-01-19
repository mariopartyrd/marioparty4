#include "REL/m409Dll.h"

#include "ext_math.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "math.h"

// bss
Process *lbl_1_bss_E8;
s16 lbl_1_bss_E4;
omObjData *lbl_1_bss_E0;
omObjData *lbl_1_bss_DC;
Vec lbl_1_bss_D0;
unkStruct4 lbl_1_bss_40[4];
s32 lbl_1_bss_3C;
unkStruct3 lbl_1_bss_24;
s8 lbl_1_bss_21;
u8 lbl_1_bss_20;
f32 lbl_1_bss_1C;
f32 lbl_1_bss_18;
s16 lbl_1_bss_16;
s8 lbl_1_bss_14;
f32 lbl_1_bss_10;
f32 lbl_1_bss_C;
s8 lbl_1_bss_A;
s16 lbl_1_bss_8;
s8 lbl_1_bss_6;
s16 lbl_1_bss_4;
s16 lbl_1_bss_2;
s8 lbl_1_bss_0;

// data
Vec lbl_1_data_0 = { 800.0f, 1300.0f, 1000.0f };
Vec lbl_1_data_C = { 0.0f, 0.0f, 0.0f };
unkStruct2 lbl_1_data_18 = { { 0xFF, 0xFF, 0xFF, 0xFF }, { 10.0f, 45.0f, 0.0f } };
Vec lbl_1_data_28 = { 1300.0f, 2500.0f, 1300.0f };
Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_40 = { 0.0f, 0.0f, -1200.0f };
unkStruct lbl_1_data_4C[4]
    = { { 469.8f, { 225.0f, 184.0f, -1358.0f }, { 10.62f, -109.0f, 0.0f } }, { 1800.0f, { 0.0f, 300.0f, -1316.0f }, { -20.38f, 0.0f, 0.0f } },
          { 2209.82f, { 0.0f, 478.0f, -1316.0f }, { 4.62f, 0.0f, 0.0f } }, { 2059.82f, { 0.0f, 528.0f, -1316.0f }, { 10.62f, 0.0f, 0.0f } } };
u32 lbl_1_data_BC = 0xFFFFFFFF;
s32 lbl_1_data_C0 = -1;

void ObjectSetup(void)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    LightData *temp_r31;

    Hu3DLightAllKill();
    lbl_1_bss_E4 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_18.unk0);
    Hu3DGLightInfinitytSet(lbl_1_bss_E4);
    temp_r31 = &Hu3DGlobalLight[lbl_1_bss_E4];
    temp_r31->unk_00 |= 0x8000;
    sp2C.x = sp2C.y = sp2C.z = 0.0f;
    Hu3DGLightPosAimSetV(lbl_1_bss_E4, &lbl_1_data_0, &sp2C);
    Hu3DShadowCreate(45.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    lbl_1_bss_E8 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_E8);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 41.5f, 5.0f, 5000.0f, 1.2f);
    omAddObjEx(lbl_1_bss_E8, 0x7FDA, 0U, 0U, -1, omOutView);
    sp14.x = 0.0f;
    sp14.y = 374.0f;
    sp14.z = 1086.0f;
    sp20.x = 0.0f;
    sp20.y = 568.0f;
    sp20.z = -1316.0f;
    sp8.z = sp20.x - sp14.x;
    sp8.y = sp20.y - sp14.y;
    sp8.x = sp20.z - sp14.z;
    CRot.x = lbl_1_data_4C[0].rot.x;
    CRot.y = lbl_1_data_4C[0].rot.y;
    CRot.z = lbl_1_data_4C[0].rot.z;
    Center.x = lbl_1_data_4C[0].center.x;
    Center.y = lbl_1_data_4C[0].center.y;
    Center.z = lbl_1_data_4C[0].center.z;
    CZoom = lbl_1_data_4C[0].zoom;
    omAddObjEx(lbl_1_bss_E8, 0x3E8, 0, 0, -1, fn_1_434);
    lbl_1_bss_E0 = omAddObjEx(lbl_1_bss_E8, 0xA, 3U, 0U, -1, fn_1_DDC);
    lbl_1_bss_DC = omAddObjEx(lbl_1_bss_E8, 0x32, 7U, 0U, -1, fn_1_2484);
    Hu3DBGColorSet(0, 0, 0);
    HuAudSndGrpSet(0x22);
    fn_1_67E0(lbl_1_bss_E8);
}

void fn_1_434(omObjData *object)
{
    if ((omSysExitReq != 0) || (lbl_1_bss_0 != 0)) {
        HuAudFXListnerKill();
        fn_1_5F5C(lbl_1_bss_E0->model[0]);
        fn_1_5F5C(lbl_1_bss_E0->model[1]);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
        MGSeqKillAll();
        object->func = fn_1_4DC;
    }
}

void fn_1_4DC(omObjData *object)
{
    if ((WipeStatGet() == 0) && (MGSeqDoneCheck() != 0)) {
        fn_1_6900();
        omOvlReturnEx(1, 1);
    }
}

s8 fn_1_524(void)
{
    Vec sp8;
    f32 temp_f29;
    f32 var_f30;
    f32 temp_f31;
    s8 var_r30;
    unkStruct *var_r31;

    var_r31 = lbl_1_data_4C;
    var_r30 = 0;
    if (++lbl_1_bss_2 > 0x12C) {
        lbl_1_bss_2 = 0x12C;
        var_r30 = 1;
    }
    var_f30 = lbl_1_bss_2 / 300.0f;
    temp_f31 = sind(90.0f * var_f30) * sind(90.0f * var_f30);
    CZoom = fn_1_4120(var_r31[0].zoom, var_r31[1].zoom, var_r31[2].zoom, temp_f31);
    Center.x = fn_1_4120(var_r31[0].center.x, var_r31[1].center.x, var_r31[2].center.x, temp_f31);
    Center.y = fn_1_4120(var_r31[0].center.y, var_r31[1].center.y, var_r31[2].center.y, temp_f31);
    Center.z = fn_1_4120(var_r31[0].center.z, var_r31[1].center.z, var_r31[2].center.z, temp_f31);
    CRot.x = fn_1_4120(var_r31[0].rot.x, var_r31[1].rot.x, var_r31[2].rot.x, temp_f31);
    CRot.y = fn_1_4120(var_r31[0].rot.y, var_r31[1].rot.y, var_r31[2].rot.y, temp_f31);
    CRot.z = fn_1_4120(var_r31[0].rot.z, var_r31[1].rot.z, var_r31[2].rot.z, temp_f31);
    if (var_f30 > 0.65f) {
        Hu3DModelAttrSet(lbl_1_bss_DC->model[1], HU3D_ATTR_DISPOFF);
    }
    temp_f29 = var_r31[0].rot.x + (-var_r31[0].rot.x * temp_f31);
    Hu3DModelRotSet(lbl_1_bss_DC->model[2], 0.2f * temp_f29, 0.85f * CRot.y, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_DC->model[3], 0.2f * temp_f29, 0.85f * CRot.y, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_DC->model[6], 0.2f * temp_f29, 0.85f * CRot.y, 0.0f);
    var_f30 *= 1.2f;
    if (var_f30 > 1.0f) {
        var_f30 = 1.0f;
    }
    temp_f31 = cosd(-45.0f + (135.0f * var_f30));
    Hu3DTexScrollPosSet(lbl_1_bss_24.unk12, lbl_1_bss_24.unk14, 0.0f, 0.0f);
    lbl_1_bss_24.unk14 -= 0.01f * temp_f31;
    Hu3DTexScrollPosMoveSet(lbl_1_bss_24.unkC, -0.0001f - (0.005f * temp_f31), 0.0f, 0.0f);
    Hu3DTexScrollPosMoveSet(lbl_1_bss_24.unkE, -0.0002f - (0.005f * temp_f31), 0.0f, 0.0f);
    Hu3DTexScrollPosMoveSet(lbl_1_bss_24.unk10, -0.0003f - (0.005f * temp_f31), 0.0f, 0.0f);
    sp8.x = -(sind(CRot.y) * cosd(CRot.x));
    sp8.y = sind(CRot.x);
    sp8.z = -(cosd(CRot.y) * cosd(CRot.x));
    HuAudFXListnerUpdate(&Hu3DCamera->pos, &sp8);
    return var_r30;
}

s8 fn_1_B80(void)
{
    f32 temp_f30;
    f32 temp_f31;
    s8 var_r30;
    unkStruct *var_r31;

    var_r31 = &lbl_1_data_4C[2];
    var_r30 = 0;
    if (++lbl_1_bss_4 > 0x3C) {
        lbl_1_bss_4 = 0x3C;
        var_r30 = 1;
    }
    temp_f30 = lbl_1_bss_4 / 60.0f;
    temp_f31 = sind(90.0f * temp_f30) * sind(90.0f * temp_f30);
    CZoom = var_r31[0].zoom + (temp_f31 * (var_r31[1].zoom - var_r31[0].zoom));
    Center.x = var_r31[0].center.x + (temp_f31 * (var_r31[1].center.x - var_r31[0].center.x));
    Center.y = var_r31[0].center.y + (temp_f31 * (var_r31[1].center.y - var_r31[0].center.y));
    Center.z = var_r31[0].center.z + (temp_f31 * (var_r31[1].center.z - var_r31[0].center.z));
    CRot.x = var_r31[0].rot.x + (temp_f31 * (var_r31[1].rot.x - var_r31[0].rot.x));
    CRot.y = var_r31[0].rot.y + (temp_f31 * (var_r31[1].rot.y - var_r31[0].rot.y));
    CRot.z = var_r31[0].rot.z + (temp_f31 * (var_r31[1].rot.z - var_r31[0].rot.z));
    return var_r30;
}

void fn_1_DDC(omObjData *object)
{
    s16 *var_r29;
    AnimData *var_r30;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 6, MEMORY_DEFAULT_NUM);
    var_r29 = (s16 *)object->data;
    var_r29[0] = 1;
    var_r30 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M409, 0x0D), MEMORY_DEFAULT_NUM));
    object->model[0] = fn_1_5A18(var_r30, 0x800, 10.0f, 0x40, 0x40);
    fn_1_5FBC(object->model[0], fn_1_5408);
    Hu3DModelLayerSet(object->model[0], 5);
    var_r30 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M409, 0x0E), MEMORY_DEFAULT_NUM));
    object->model[1] = fn_1_5A18(var_r30, 0x400, 2.0f, 0, 0);
    fn_1_5FBC(object->model[1], fn_1_55E0);
    fn_1_5FF4(object->model[1], 1);
    Hu3DModelLayerSet(object->model[1], 5);
    HuAudFXListnerSetEX(&Hu3DCamera->pos, &Hu3DCamera->up, 10000.0f, 566.6667f, 0.0f, 300.0f, 300.0f);
    object->func = fn_1_F70;
}

void fn_1_F70(omObjData *object)
{
    s16 *sp8;
    s16 temp_r3;
    s16 temp_r3_2;
    s32 var_r31;

    sp8 = (s16 *)object->data;
    switch (fn_1_2454(7)) {
        case 1:
            if (lbl_1_bss_6 == 0) {
                lbl_1_bss_6 = 1;
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 0x3C);
            }
            if (WipeStatGet() == 0) {
                fn_1_2414(7, 2);

                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    omVibrate(var_r31, 0xC8, 6, 6);
                }
            }
            break;
        case 2:
            if (fn_1_10E8(object) != 0) {
                fn_1_2414(7, 3);
            }
            break;
        case 3:
            switch (fn_1_2454(0x60)) {
                case 0x40:
                    break;
                case 0x20:
                    fn_1_2098(object);
                    break;
            }
            break;
        case 4:
            if (fn_1_1B74(object) != 0) {
                fn_1_2414(7, 5);
                return;
            }
            break;
        case 5:
            lbl_1_bss_0 = 1;
            break;
    }
}

s8 fn_1_10E8(omObjData *object)
{
    Vec sp8;
    ModelData *temp_r31;
    f32 var_f26;
    f32 var_f27;
    f32 temp_f29;
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f31;
    s8 var_r29;
    unkStruct3 *temp_r30;

    temp_r31 = &Hu3DData[lbl_1_bss_DC->model[4]];
    temp_r30 = (unkStruct3 *)object->data;
    if (lbl_1_bss_A != 0) {
        var_r29 = fn_1_524();
    }
    switch (lbl_1_bss_8) { /* irregular */
        case -1:
            if ((HuPadBtnDown[0] & 0x100) != 0) {
                lbl_1_bss_8 = 0;
            }
            break;
        case 0:
            Hu3DModelAttrReset(lbl_1_bss_DC->model[1], HU3D_MOTATTR_PAUSE);
            if (lbl_1_bss_C == 0.0f) {
                fn_1_3840();
                sp8.x = 1520.0f;
                sp8.y = 0.0f;
                sp8.z = -1200.0f;
                lbl_1_data_BC = HuAudFXEmiterPlay(0x554, &sp8);
                HuAudFXEmiterPlay(0x559, &sp8);
            }
            lbl_1_bss_C += 0.004f;
            if (lbl_1_bss_C >= 1.0f) {
                lbl_1_bss_C = 1.0f;
                lbl_1_bss_8 = 0x63;
            }
            else if (lbl_1_bss_C > 0.2f) {
                lbl_1_bss_A = 1;
            }
            var_f31 = sind(90.0f * lbl_1_bss_C);
            var_f27 = 1520.0f;
            var_f26 = -1030.0f;
            temp_f30 = var_f27 + (var_f31 * (var_f26 - var_f27));
            Hu3DModelPosSet(lbl_1_bss_DC->model[4], temp_f30, 0.0f, -1200.0f);
            Hu3DModelPosSet(lbl_1_bss_DC->model[1], temp_f30, 0.0f, -1200.0f);
            if (lbl_1_data_BC != ~0) {
                sp8.x = temp_f30;
                sp8.y = 0.0f;
                sp8.z = -1200.0f;
                HuAudFXEmiterUpDate(lbl_1_data_BC, &sp8);
            }
            var_f31 = 1.2f * lbl_1_bss_C;
            if ((var_f31 >= 1.0f) && lbl_1_data_BC != ~0) {
                HuAudFXEmiterPlay(0x555, &sp8);
                sp8.x += 200.0f;
                HuAudFXEmiterPlay(0x55E, &sp8);
                HuAudFXStop(lbl_1_data_BC);
                lbl_1_data_BC = -1;
            }
            if (var_f31 >= 1.0f) {
                var_f31 = 0.0f;
            }
            else {
                var_f31 = sind(90.0f + 90.0f * var_f31);
            }
            Hu3DMotionSpeedSet(lbl_1_bss_DC->model[4], 2.0f * var_f31);
            if (lbl_1_bss_C > 0.5f) {
                var_f31 = 2.0f * (9.0f * (1.0f - lbl_1_bss_C));
            }
            else {
                var_f31 = 9.0f;
            }
            fn_1_44F0(lbl_1_bss_E0->model[0], 0.0f, 0.0f, 0.0f, 0, var_f31);
            if ((lbl_1_bss_C > 0.7f) && (lbl_1_bss_C < 0.9f)) {
                var_f31 = (lbl_1_bss_C - 3.5f);
                if (++lbl_1_bss_10 > (var_f31 * 10.0f)) {
                    lbl_1_bss_10 = 0.0f;
                    temp_f30 = 190.0f + temp_r31->pos.x;
                    temp_f29 = 20.0f + temp_r31->pos.y;
                    temp_f28 = 95.0f + temp_r31->pos.z;
                    var_f31 = 1.0f - (lbl_1_bss_C - 3.5f);
                    fn_1_4FFC(lbl_1_bss_E0->model[1], temp_f30, temp_f29, temp_f28, (u8)(2.0f * var_f31));
                    temp_f30 = 370.0f + temp_r31->pos.x;
                    fn_1_4FFC(lbl_1_bss_E0->model[1], temp_f30, temp_f29, temp_f28, (u8)var_f31);
                    temp_f30 = 490.0f + temp_r31->pos.x;
                    fn_1_4FFC(lbl_1_bss_E0->model[1], temp_f30, temp_f29, temp_f28, (u8)var_f31);
                }
            }
            if (++lbl_1_bss_14 > 1) {
                lbl_1_bss_14 = 0;
                fn_1_44F0(lbl_1_bss_E0->model[0], 190.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z + 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 370.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z + 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 490.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z + 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 190.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z - 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 370.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z - 95.0f, 1, 1);
                fn_1_44F0(lbl_1_bss_E0->model[0], 490.0f + temp_r31->pos.x, 15.0f, temp_r31->pos.z - 95.0f, 1, 1);
            }
            break;
        case 99:
            if (var_r29 == 0) {
                return 0;
            }
            temp_r30->unk2 = MGSeqCreate(3, 0);
            MGSeqPosSet(temp_r30->unk2, 320.0f, 240.0f);
            lbl_1_bss_8 = 0x270F;
            break;
        default:
            if (MGSeqStatGet(temp_r30->unk2) == 0) {
                lbl_1_bss_8 = 0;
                return 1;
            }
            if ((lbl_1_data_C0 == -1) && ((MGSeqStatGet(temp_r30->unk2) & 0x10) != 0)) {
                lbl_1_data_C0 = HuAudSeqPlay(0x48);
            }
            break;
    }
    return 0;
}

s8 fn_1_1B74(omObjData *object)
{
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r27;
    s32 temp_r28;
    unkStruct4 *temp_r30;

    temp_r30 = (unkStruct4 *)object->data;
    switch (lbl_1_bss_8) {
        case 0:
            temp_r30->unk2 = MGSeqCreate(3, 1);
            MGSeqPosSet(temp_r30->unk2, 320.0f, 240.0f);
            HuAudSeqFadeOut(lbl_1_data_C0, 0x64);
            lbl_1_bss_16 = 0;
            lbl_1_bss_8 = 1;
            break;
        case 1:
            if (++lbl_1_bss_16 > 30) {
                lbl_1_bss_8 = 2;
            }
            break;
        case 2:
            if (fn_1_B80()) {
                lbl_1_bss_8 = 3;
            }
            break;
        case 3:
            fn_1_2414(0x80, 0x80);
            if (temp_r30->unk4 >= 0) {
                GWPlayerCoinWinAdd(temp_r30->unk4, 10);
                temp_r30->unk2 = MGSeqCreate(5, 3, GWPlayerCfg[temp_r30->unk4].character, -1, -1, -1);
                HuAudSStreamPlay(1);
            }
            else {
                temp_r30->unk2 = MGSeqCreate(3, 2);
                HuAudSStreamPlay(4);
            }
            MGSeqPosSet(temp_r30->unk2, 320.0f, 240.0f);
            lbl_1_bss_8 = 4;
            lbl_1_bss_16 = 0;
            break;
        case 4:
            lbl_1_bss_16++;
            if (MGSeqStatGet(temp_r30->unk2) == 0) {
                lbl_1_bss_8 = 5;
            }
            break;
        case 5:
            lbl_1_bss_16++;
            if (lbl_1_bss_16 > 210.0f) {
                return 1;
            }
            break;
    }
    return 0;
}

void fn_1_2098(omObjData *object)
{
    ModelData *temp_r31;
    f32 var_f28;
    f32 var_f29;
    f32 var_f31;
    f32 var_f30;
    s32 var_r30;

    temp_r31 = &Hu3DData[lbl_1_bss_DC->model[4]];
    if (fn_1_2454(0x18) != 0x18) {
        lbl_1_bss_18 += 0.008f;
        if (lbl_1_bss_18 >= 1.0f) {
            fn_1_2414(0x60, 0x40);
            Hu3DModelAttrSet(lbl_1_bss_DC->model[4], HU3D_ATTR_DISPOFF);
            lbl_1_bss_18 = 1.0f;
        }
        var_f31 = sind(90.0f * lbl_1_bss_18);
        var_f29 = -1030.0f;
        var_f28 = -1880.0f;
        var_f30 = var_f29 + (var_f31 * (var_f28 - var_f29));
        Hu3DModelPosSet(lbl_1_bss_DC->model[4], var_f30, 0.0f, -1200.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_DC->model[4], 3.0f * var_f31);
        var_f31 = (4.0f * (9.0f * lbl_1_bss_18));
        fn_1_44F0(lbl_1_bss_E0->model[0], 0.0f, 0.0f, 0.0f, 0, var_f31);
        fn_1_44F0(lbl_1_bss_E0->model[0], 190.0f + var_f30, 15.0f, 95.0f + temp_r31->pos.z, 1, 1);
        fn_1_44F0(lbl_1_bss_E0->model[0], 370.0f + var_f30, 15.0f, 95.0f + temp_r31->pos.z, 1, 1);
        fn_1_44F0(lbl_1_bss_E0->model[0], 490.0f + var_f30, 15.0f, 95.0f + temp_r31->pos.z, 1, 1);
    }
}

void fn_1_23EC(s16 arg0)
{
    unkStruct4 *var_r31;

    var_r31 = (unkStruct4 *)lbl_1_bss_E0->data;
    var_r31->unk4 = arg0;
}

void fn_1_2414(u16 arg0, u16 arg1)
{
    unkStruct4 *var_r31;

    var_r31 = (unkStruct4 *)lbl_1_bss_E0->data;
    var_r31->unk0 &= ~arg0;
    var_r31->unk0 |= arg1;
}

u16 fn_1_2454(u16 arg0)
{
    unkStruct4 *var_r31;

    var_r31 = (unkStruct4 *)lbl_1_bss_E0->data;
    return var_r31->unk0 & arg0;
}

static inline void unkInline(unkStruct4 *var_r31, s16 var_r29, s16 *var_r28, s16 arg3)
{
    var_r31[var_r29].unk2 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x02));
    var_r31[var_r29].unk4 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x03));
    Hu3DModelAttrSet(var_r31[var_r29].unk2, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(var_r31[var_r29].unk4, HU3D_MOTATTR_PAUSE);
    if (arg3) {
        Hu3DModelAttrSet(var_r31[var_r29].unk2, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(var_r31[var_r29].unk4, HU3D_ATTR_DISPOFF);
    }
    var_r31[var_r29].unk6 = Hu3DModelCreateFile(0x2001C);
    var_r31[var_r29].unk8 = Hu3DJointMotionFile(var_r31[var_r29].unk6, DATA_MAKE_NUM(DATADIR_M409, 11));
    var_r31[var_r29].unkA = Hu3DJointMotionFile(var_r31[var_r29].unk6, DATA_MAKE_NUM(DATADIR_M409, 12));
    Hu3DModelAttrSet(var_r31[var_r29].unk6, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(var_r31[var_r29].unk6, var_r31[var_r29].unk8);
    var_r31[var_r29].unkC = var_r29 + 3;
    if (arg3) {
        *var_r28 += (((rand8() << 8) | rand8()) % 4) + 2;
    }
    else {
        *var_r28 = 2;
    }
    fn_1_3988(&var_r31[var_r29], *var_r28, var_r29);
    Hu3DModelPosSet(var_r31[var_r29].unk2, var_r31[var_r29].unk18, 0.0f, -1200.0f);
    Hu3DModelPosSet(var_r31[var_r29].unk4, var_r31[var_r29].unk18, 0.0f, -1200.0f);
}

void fn_1_2484(omObjData *object)
{
    s16 var_r28; // ! - uninitialized
    s16 var_r29;
    unkStruct4 *var_r31;

    var_r31 = &lbl_1_bss_40[0];
    object->stat |= 0x100;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x00));
    object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x08));
    Hu3DModelLayerSet(object->model[0], 2);
    Hu3DModelLayerSet(object->model[5], 2);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x05));
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x06));
    Hu3DModelScaleSet(object->model[2], 1.1f, 1.0f, 1.0f);
    Hu3DModelScaleSet(object->model[3], 1.1f, 1.0f, 1.0f);
    Hu3DModelRotSet(object->model[2], 0.2f * lbl_1_data_4C->rot.x, 0.85f * lbl_1_data_4C->rot.y, 0.0f);
    Hu3DModelRotSet(object->model[3], 0.2f * lbl_1_data_4C->rot.x, 0.85f * lbl_1_data_4C->rot.y, 0.0f);
    Hu3DModelLayerSet(object->model[2], 2);
    Hu3DModelLayerSet(object->model[3], 2);
    lbl_1_bss_24.unkE = Hu3DTexScrollCreate(object->model[2], "cr_kumo2");
    Hu3DTexScrollPosMoveSet(lbl_1_bss_24.unkE, -0.0002f, 0.0f, 0.0f);
    lbl_1_bss_24.unk10 = Hu3DTexScrollCreate(object->model[3], "cr_kumo3");
    Hu3DTexScrollPosMoveSet(lbl_1_bss_24.unk10, -0.0003f, 0.0f, 0.0f);
    var_r29 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x0A));
    Hu3DModelLayerSet(var_r29, 0);
    object->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x07));
    Hu3DModelAttrSet(object->model[6], HU3D_ATTR_ZWRITE_OFF);
    Hu3DModelScaleSet(object->model[6], 1.1f, 1.0f, 1.0f);
    Hu3DModelRotSet(object->model[6], 0.2f * lbl_1_data_4C->rot.x, 0.85f * lbl_1_data_4C->rot.y, 0.0f);
    Hu3DModelLayerSet(object->model[6], 1);
    lbl_1_bss_24.unk12 = Hu3DTexScrollCreate(object->model[6], "bg");
    lbl_1_bss_24.unk14 = 0.0f;
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x01));
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x04));
    Hu3DModelAttrSet(object->model[4], HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(object->model[4], 1660.0f, 0.0f, -1200.0f);
    Hu3DModelPosSet(object->model[1], 1660.0f, 0.0f, -1200.0f);
    Hu3DModelLayerSet(object->model[1], 6);
    Hu3DModelAttrSet(object->model[1], HU3D_MOTATTR_PAUSE);

    unkInline(var_r31, 0, &var_r28, 0);
    for (var_r29 = 1; var_r29 < 4; var_r29++) {
        unkInline(var_r31, var_r29, &var_r28, 1);
    }

    lbl_1_bss_24.unk0 = 0;
    lbl_1_bss_24.unk1 = 0;
    lbl_1_bss_24.unk8 = 0;
    lbl_1_bss_24.unkA = 0xB4;
    Hu3DModelShadowMapSet(object->model[0]);
    Hu3DModelShadowSet(object->model[4]);

    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        Hu3DModelShadowSet(var_r31[var_r29].unk2);
        Hu3DModelShadowSet(var_r31[var_r29].unk4);
    }
    lbl_1_bss_3C = 0;
    object->func = fn_1_2DCC;
}

void fn_1_2DCC(omObjData *object)
{
    u16 spE;
    u16 spC;
    u16 spA;
    u16 sp8;
    ModelData *temp_r30;
    f32 temp_f29;
    f32 var_f31;
    f32 var_f30;
    s16 var_r22;
    s16 var_r23;
    s16 var_r28;
    s16 var_r27;
    s16 var_r29;
    s32 temp_r16;
    s16 var_r18;
    unkStruct4 *var_r31;

    if ((lbl_1_bss_24.unk0 == 0) || (fn_1_2454(0x18) == 0x18)) {
        if (lbl_1_bss_24.unk1 != 0) {
            var_r31 = lbl_1_bss_24.unk4;
            switch (lbl_1_bss_24.unk1) {
                case 1:
                    if (++lbl_1_bss_24.unk8 == (lbl_1_bss_24.unkA - 5)) {
                        Hu3DMotionSet(var_r31->unk6, var_r31->unkA);
                        Hu3DModelAttrReset(var_r31->unk6, HU3D_MOTATTR_LOOP);
                        lbl_1_bss_3C++;
                        break;
                    }
                    if (lbl_1_bss_24.unk8 > lbl_1_bss_24.unkA) {
                        lbl_1_bss_24.unk8 = 0;
                        lbl_1_bss_24.unkA = 0xF;
                        Hu3DModelAttrReset(var_r31->unk4, HU3D_MOTATTR_PAUSE);
                        lbl_1_bss_24.unk1 = 2;
                        HuAudFXPlay(0x55B);
                        HuAudFXPlay(0x55D);
                    }
                    break;
                case 2:
                    temp_f29 = Hu3DMotionMaxTimeGet(var_r31->unk4);
                    if (Hu3DMotionTimeGet(var_r31->unk4) >= temp_f29) {
                        Hu3DMotionSet(var_r31->unk6, var_r31->unk8);
                        Hu3DModelAttrSet(var_r31->unk6, HU3D_MOTATTR_LOOP);
                        Hu3DModelAttrSet(var_r31->unk4, HU3D_MOTATTR_PAUSE);
                        fn_1_2414(24, 8);
                        lbl_1_bss_24.unk1 = 0;
                    }
                    break;
            }
        }
        else {
            var_r31 = lbl_1_bss_24.unk4;
            switch (fn_1_2454(0x18)) {
                case 16:
                    Hu3DMotionSet(var_r31->unk6, var_r31->unkA);
                    Hu3DMotionTimeSet(var_r31->unk6, Hu3DMotionMaxTimeGet(var_r31->unk6));
                    Hu3DMotionSpeedSet(var_r31->unk6, -1.0f);
                    Hu3DModelAttrReset(var_r31->unk6, HU3D_MOTATTR_LOOP);
                    Hu3DMotionSpeedSet(var_r31->unk4, -1.0f);
                    Hu3DModelAttrReset(var_r31->unk4, HU3D_MOTATTR_PAUSE);
                    fn_1_2414(24, 0x18);
                    HuAudFXPlay(0x55C);
                    HuAudFXPlay(0x55D);
                    break;
                case 24:
                    if (Hu3DMotionTimeGet(var_r31->unk4) <= 0.0f) {
                        Hu3DMotionSet(var_r31->unk6, var_r31->unk8);
                        Hu3DMotionSpeedSet(var_r31->unk6, 1.0f);
                        Hu3DModelAttrSet(var_r31->unk6, HU3D_MOTATTR_LOOP);
                        Hu3DMotionSpeedSet(var_r31->unk4, 1.0f);
                        Hu3DModelAttrSet(var_r31->unk4, HU3D_MOTATTR_PAUSE);
                        fn_1_2414(24, 0);
                    }
                    break;
            }
        }
    }
    else {
        if (fn_1_2454(7) == 2) {
            var_f30 = 0.004f;
        }
        else {
            var_f30 = 0.008f;
        }
        var_r29 = 0;
        var_r23 = 0;
        var_r31 = lbl_1_bss_40;

        for (; var_r29 < 4; var_r29++, var_r31++) {
            if ((s8)var_r31->unk0b == 0) {
                var_r23++;
            }
            else {
                if (var_r31->unkE-- <= 0) {
                    temp_r30 = &Hu3DData[var_r31->unk2];
                    if ((var_r31->unkC < 2) && (lbl_1_bss_3C < 0xBU)) {
                        Hu3DModelAttrReset(var_r31->unk2, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(var_r31->unk4, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(var_r31->unk6, HU3D_ATTR_DISPOFF);
                    }
                    var_r31->unk10 += var_f30;
                    var_f31 = sind(90.0f * var_r31->unk10);
                    if (var_r31->unk10 >= 1.0f) {
                        var_f31 = 1.0f;
                        var_r31->unk10 = var_f31;
                        temp_r30->pos.x = var_r31->unk1C;
                        if (var_r31->unkC == 0) {
                            lbl_1_bss_24.unk4 = var_r31;
                        }
                        var_r27 = var_r31->unkC - 1;
                        if (var_r27 == -3) {
                            Hu3DModelAttrSet(var_r31->unk2, HU3D_ATTR_DISPOFF);
                            Hu3DModelAttrSet(var_r31->unk4, HU3D_ATTR_DISPOFF);
                            Hu3DModelAttrSet(var_r31->unk6, HU3D_ATTR_DISPOFF);
                            var_r31->unkC = 2;
                            var_r27 = 1;
                        }
                        fn_1_3988(var_r31, 0, var_r27);
                    }
                    else {
                        temp_r30->pos.x = var_r31->unk18 + (var_f31 * (var_r31->unk1C - var_r31->unk18));
                    }
                    if (var_f31 > 0.1f) {
                        if (++var_r31->unk16 > 1) {
                            var_r31->unk16 = 0;
                            fn_1_44F0(*lbl_1_bss_E0->model, 130.0f + temp_r30->pos.x, 15.0f, 95.0f + temp_r30->pos.z, 1, 1);
                            fn_1_44F0(*lbl_1_bss_E0->model, 630.0f + temp_r30->pos.x, 15.0f, 95.0f + temp_r30->pos.z, 1, 1);
                        }
                    }
                    if ((var_r31->unk10 > 0.7f) && (var_r31->unk10 < 0.9f)) {
                        var_f31 = var_r31->unk10 - 3.5f;
                        if (++lbl_1_bss_1C > (40.0f * var_f31)) {
                            lbl_1_bss_1C = 0.0f;
                            var_f31 = 1.0f - var_f31;
                            fn_1_4FFC(lbl_1_bss_E0->model[1], 130.0f + temp_r30->pos.x, 20.0f + temp_r30->pos.y, 95.0f + temp_r30->pos.z,
                                (u8)(2.0f * var_f31));
                            fn_1_4FFC(
                                lbl_1_bss_E0->model[1], 630.0f + temp_r30->pos.x, 20.0f + temp_r30->pos.y, 95.0f + temp_r30->pos.z, (u8)var_f31);
                        }
                        if (var_r31->unk10 < (0.7f + var_f30)) {
                            HuAudFXEmiterPlay(0x55E, &temp_r30->pos);
                        }
                    }
                    Hu3DModelPosSet(var_r31->unk6, 70.0f + temp_r30->pos.x, 290.0f, -1200.0f);
                    Hu3DData[var_r31->unk4].pos.x = temp_r30->pos.x;
                    var_f31 = 0.8f * sind(180.0f * var_r31->unk10);
                    Hu3DMotionSpeedSet(var_r31->unk2, var_f31);
                }
            }
        }
        if (var_r23 == 4) {
            var_r22 = 0x63;
            lbl_1_bss_24.unk0 = 0;

            for (var_r29 = 0, var_r31 = &lbl_1_bss_40[0]; var_r29 < 4; var_r29++, var_r31++) {
                if (var_r31->unkC < var_r22) {
                    var_r22 = var_r31->unkC;
                    var_r27 = var_r29;
                }

                for (var_r28 = 0, var_r31->unk20 = NULL; var_r28 < 4; var_r28++) {
                    if ((var_r31->unkC + 1) == lbl_1_bss_40[var_r28].unkC) {
                        var_r31->unk20 = &lbl_1_bss_40[var_r28];
                    }
                }
            }
            var_r31 = &lbl_1_bss_40[var_r27];
            var_r31->unkE = 0;

        loop:
            if (var_r31->unk20) {
                var_r31->unk20->unkE = 2 + (((rand8() << 8) | rand8()) % 4) + var_r31->unkE;
                var_r31 = var_r31->unk20;
                goto loop;
            }
            lbl_1_bss_24.unk1 = 1;
        }
    }
}

void fn_1_3840(void)
{
    s16 var_r31;

    if ((lbl_1_bss_24.unk0 == 0) && (fn_1_2454(7) != 4)) {
        lbl_1_bss_24.unk0 = 1;

        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            lbl_1_bss_40[var_r31].unk0b = 1;
        }
        if (++lbl_1_bss_20 == 2) {

            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                lbl_1_bss_40[var_r31].unkE += 3;
            }
            fn_1_2414(0x60, 0x20);
        }
        HuAudFXPlay(0x55F);
    }
}

void fn_1_3988(unkStruct4 *arg0, s16 arg1, s16 arg2)
{
    arg0->unk0b = 0;
    arg0->unkE = arg1;
    arg0->unk10 = 0.0f;
    arg0->unk18 = ((850.0f * arg0->unkC) - 370.0f);
    arg0->unk1C = ((850.0f * arg2) - 370.0f);
    arg0->unkC = arg2;
    if ((arg0->unkC >= 2) && (fn_1_2454(7) != 2)) {
        Hu3DModelAttrSet(arg0->unk2, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->unk4, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->unk6, HU3D_ATTR_DISPOFF);
    }
}

s32 fn_1_3AD8(s32 arg0, f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC, f32 argD)
{
    f32 sp1C;
    f32 temp;
    ModelData *temp_r31;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;
    f32 temp_f27;
    f32 temp_f26;
    s16 var_r29;
    unkStruct4 *var_r30;

    var_r30 = lbl_1_bss_24.unk4;
    if (!var_r30)
        return;

    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        temp_r31 = &Hu3DData[var_r30->unk6];
        temp_f31 = temp_r31->pos.x;
        temp_f30 = 75.0f + temp_r31->pos.y;
        temp_f29 = temp_r31->pos.z;
        temp_f28 = arg8 + argB;
        temp_f27 = arg9 + argC;
        temp_f26 = argA + argD;
        temp = sqrtf((temp_f28 - temp_f31) * (temp_f28 - temp_f31) + (temp_f27 - temp_f30) * (temp_f27 - temp_f30)
            + (temp_f26 - temp_f29) * (temp_f26 - temp_f29));
        if (temp < 50.0f) {
            return 1;
        }
        sp1C = -((argA * argD) + (((arg9 * argC) + (((-temp_f31 * argB) + (arg8 * argB)) - (temp_f30 * argC))) - (temp_f29 * argD)))
            / ((argD * argD) + ((argB * argB) + (argC * argC)));
        if (sp1C >= 1.0f)
            continue;

        temp_f28 = arg8 + (argB * sp1C);
        temp_f27 = arg9 + (argC * sp1C);
        temp_f26 = argA + (argD * sp1C);
        temp = sqrtf((temp_f28 - temp_f31) * (temp_f28 - temp_f31) + (temp_f27 - temp_f30) * (temp_f27 - temp_f30)
            + (temp_f26 - temp_f29) * (temp_f26 - temp_f29));
        if (temp < 50.0f) {
            return 1;
        }
        var_r30 = var_r30->unk20;
        continue;
    }
    return 0;
}

void fn_1_40A4(Mtx arg0, Mtx arg1)
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

f32 fn_1_4120(f32 arg0, f32 arg1, f32 arg2, f32 arg3)
{
    f32 temp_f31;

    temp_f31 = 1.0f - arg3;
    return (arg2 * (arg3 * arg3)) + ((arg0 * (temp_f31 * temp_f31)) + (arg1 * (2.0f * temp_f31 * arg3)));
}

void fn_1_417C(void)
{

    if ((HuPadBtnDown[0] & 0x40) != 0) {
        lbl_1_bss_21 ^= 1;
    }
    if (lbl_1_bss_21 != 0) {
        if ((HuPadBtn[0] & 1) != 0) {
            CRot.y++;
        }
        if ((HuPadBtn[0] & 2) != 0) {
            CRot.y--;
        }
        if ((HuPadBtn[0] & 8) != 0) {
            CRot.x--;
        }
        if ((HuPadBtn[0] & 4) != 0) {
            CRot.x++;
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

void fn_1_44F0(s16 arg0, f32 arg8, f32 arg9, f32 argA, s8 arg1, s16 arg2)
{
    Vec sp20;
    Vec sp14;
    unkStruct4 *sp10;
    GXColor spA;
    ModelData *temp_r30;
    f32 temp_f31;
    s16 var_r29;
    unkStruct5 *var_r31;

    temp_r30 = &Hu3DData[lbl_1_bss_DC->model[4]];
    sp10 = (unkStruct4 *)temp_r30->unk_120;
    if (arg1 == 0) {
        arg8 = 150.0f + temp_r30->pos.x;
        arg9 = 360.0f + temp_r30->pos.y;
        argA = temp_r30->pos.z;
    }

    for (var_r29 = 0; var_r29 < arg2; var_r29++) {
        switch (arg1) { /* irregular */
            case 0:
                sp20.x = arg8 + ((((rand8() << 8) | rand8()) % 41) - 20);
                sp20.z = argA + ((((rand8() << 8) | rand8()) % 41) - 20);
                sp20.y = arg9;
                sp14.x = 0.01f * ((((rand8() << 8) | rand8()) % 101) + 200);
                sp14.y = 0.01f * ((((rand8() << 8) | rand8()) % 101) + 200);
                sp14.z = 0.01f * ((((rand8() << 8) | rand8()) % 101) + 200);
                spA.r = spA.g = spA.b = (((rand8() << 8) | rand8()) % 33) + 32;
                spA.a = 0xFF;
                var_r31 = fn_1_58E0(arg0, &sp20, &sp14, 0.0f, &spA);
                if (!var_r31)
                    return;

                temp_f31 = (((rand8() << 8) | rand8()) % 361);
                var_r31->unk0.x = 2.0 + (3.0 * sind(temp_f31));
                var_r31->unk0.y = (0.1f * ((((rand8() << 8) | rand8()) % 31) + 40));
                var_r31->unk0.z = (3.5 * cosd(temp_f31));
                var_r31->unk28 = 0;
                var_r31->unk2A = ((((rand8() << 8) | rand8()) % 3) + 2);
                var_r31->unk18 = (f32)spA.r;
                var_r31->unk1C = (((((rand8() << 8) | rand8()) % 69) + 0x80) / (f32)(var_r31->unk2A * 0xE));
                var_r31->unk20 = 255.0f;
                var_r31->unk24 = (((((rand8() << 8) | rand8())) % 128 + 0x80) / (f32)(var_r31->unk2A * 0xE));
                break;
            case 1:
                sp20.x = arg8 + ((((rand8() << 8) | rand8()) % 41) - 20);
                sp20.z = argA + ((((rand8() << 8) | rand8()) % 41) - 20);
                sp20.y = arg9 + ((((rand8() << 8) | rand8()) % 41) - 20);
                sp14.x = 0.01f * ((((rand8() << 8) | rand8()) % 101) + 300);
                sp14.y = 0.01f * ((((rand8() << 8) | rand8()) % 101) + 300);
                sp14.z = 0.01f * ((((rand8() << 8) | rand8()) % 101) + 300);
                spA.r = 0xFF;
                spA.g = 0xDC;
                spA.b = 0x8C;
                spA.a = 0x80;
                var_r31 = fn_1_58E0(arg0, &sp20, &sp14, 0.0f, &spA);
                if (!var_r31)
                    return;

                var_r31->unk28 = 0;
                var_r31->unk2A = ((((rand8() << 8) | rand8()) % 3) + 2);
                var_r31->unk0.x = (0.1f * ((((rand8() << 8) | rand8()) % 11) + 30));
                var_r31->unk0.y = 0.0f;
                var_r31->unk0.z = (0.1f * ((((rand8() << 8) | rand8()) % 41) - 20));
                var_r31->unk20 = 32.0f;
                var_r31->unk24 = (32.0f / (var_r31->unk2A * 0xE));
                break;
        }
        var_r31->unk2C = arg1;
    }
}

void fn_1_4FFC(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4)
{
    Vec sp2C;
    Vec sp20;
    GXColor sp1A;
    s16 sp18;
    f32 temp_f31;
    s16 var_r30;
    unkStruct5 *temp_r31;

    for (var_r30 = 0; var_r30 < arg4; var_r30++) {
        sp2C.x = arg1 + ((((rand8() << 8) | rand8()) % 21) - 10);
        sp2C.y = arg2;
        sp2C.z = arg3 + ((((rand8() << 8) | rand8()) % 21) - 10);
        sp20.x = 0.1f * ((((rand8() << 8) | rand8()) % 31) + 10);
        sp20.y = 1.0f;
        sp20.z = 1.0f;
        sp1A.r = sp1A.g = sp1A.b = sp1A.a = 0xFF;
        temp_r31 = fn_1_58E0(arg0, &sp2C, &sp20, 0.0f, &sp1A);
        if (!temp_r31)
            break;

        temp_r31->unk4C = -1;
        temp_f31 = ((((rand8() << 8) | rand8()) % 81) - 40);
        temp_r31->unk0.x = (13.0 * cosd(temp_f31));
        temp_r31->unk0.y = 0.1f * ((((rand8() << 8) | rand8()) % 21) + 20);
        temp_r31->unk0.z = (9.0 * sind(temp_f31));
        temp_r31->unkC.x = (0.05f * temp_r31->unk0.x);
        temp_r31->unkC.z = (0.05f * temp_r31->unk0.z);
        temp_r31->unk18 = 500.0f;
        temp_r31->unk1C = ((((rand8() << 8) | rand8()) % 21) + 40);
    }
}

void fn_1_5408(ModelData *arg0, struct _unkStruct6 *arg1, Mtx arg2)
{
    s16 var_r29;
    GXColor *var_r30;
    unkStruct5 *var_r31;

    var_r29 = 0;
    var_r31 = arg1->unk18;
    var_r30 = arg1->unk24;

    for (; var_r29 < arg1->unk0; var_r29++, var_r31++, var_r30++) {
        if (var_r31->unk4E != 0) {
            switch (var_r31->unk2C) {
                case 0:
                    var_r31->unk0.y -= 0.1f;
                    var_r31->unk40.x += var_r31->unk0.x;
                    var_r31->unk40.y += var_r31->unk0.y;
                    var_r31->unk40.z += var_r31->unk0.z;
                    var_r31->unk18 += var_r31->unk1C;
                    if (var_r31->unk18 > 255.0f) {
                        var_r31->unk18 = 255.0f;
                    }
                    var_r30->r = var_r30->g = var_r30->b = var_r31->unk18;
                    break;
                case 1:
                    var_r31->unk40.x += var_r31->unk0.x;
                    var_r31->unk40.z += var_r31->unk0.z;
                    break;
            }
            var_r31->unk20 -= var_r31->unk24;
            if (var_r31->unk20 < 0.0f) {
                var_r31->unk20 = 0.0f;
            }
            var_r30->a = var_r31->unk20;
            var_r31->unk28++;
            if (var_r31->unk28 >= var_r31->unk2A) {
                var_r31->unk28 = 0;
                var_r31->unk4C++;
            }
            if (var_r31->unk4C >= (arg1->unk14 - 2)) {
                var_r31->unk4E = 0;
            }
        }
    }
}

void fn_1_55E0(ModelData *arg0, struct _unkStruct6 *arg1, Mtx arg2)
{
    GXColor *var_r30;
    f32 var_f31;
    f32 var_f30;
    s16 var_r29;
    s32 var_r28;
    unkStruct5 *var_r31;

    var_r29 = 0;
    var_r31 = arg1->unk18;
    var_r30 = arg1->unk24;

    for (; var_r29 < arg1->unk0; var_r29++, var_r31++, var_r30++) {
        if (var_r31->unk4E != 0) {
            var_r31->unk0.x -= var_r31->unkC.x;
            var_r31->unk0.y -= 0.2f;
            var_r31->unk0.z -= var_r31->unkC.z;
            if (var_r31->unk0.x < var_r31->unkC.x) {
                var_r31->unk0.x = var_r31->unkC.x;
            }
            if (var_r31->unkC.z < 0.0f) {
                var_f31 = -var_r31->unkC.z;
            }
            else {
                var_f31 = var_r31->unkC.z;
            }
            if (var_r31->unk0.z < 0.0f) {
                var_f30 = -var_r31->unk0.z;
            }
            else {
                var_f30 = var_r31->unk0.z;
            }
            if (var_f30 < var_f31) {
                var_r31->unk0.z = var_r31->unkC.z;
            }
            var_r31->unk40.x += var_r31->unk0.x;
            var_r31->unk40.y += var_r31->unk0.y;
            var_r31->unk40.z += var_r31->unk0.z;
            var_r31->unk18 -= var_r31->unk1C;
            if (var_r31->unk18 < 0.0f) {
                var_r31->unk18 = 0.0f;
            }
            if (var_r31->unk18 > 255.0f) {
                var_r28 = 0xFF;
            }
            else {
                var_r28 = (u8)var_r31->unk18;
            }
            var_r30->a = var_r28;
            if (0.0f == var_r31->unk18) {
                var_r31->unk4E = 0;
            }
        }
    }
}

void fn_1_57DC(ModelData *arg0, struct _unkStruct6 *arg1, Mtx arg2)
{
    Vec sp18;
    Vec spC;
    GXColor sp8;
    ModelData *temp_r30;
    unkStruct5 *temp_r31;

    temp_r30 = &Hu3DData[lbl_1_bss_DC->model[4]];
    temp_r31 = arg1->unk18;
    if (temp_r31->unk4E == 0) {
        spC.x = spC.y = spC.z = 1.0f;
        sp8.r = sp8.g = sp8.b = sp8.a = 0xFF;
        fn_1_58E0(lbl_1_bss_E0->model[2], &sp18, &spC, 0.0f, &sp8);
    }
    temp_r31->unk40.x = (60.0f + temp_r30->pos.x);
    temp_r31->unk40.y = (260.0f + temp_r30->pos.y);
    temp_r31->unk40.z = temp_r30->pos.z;
}

unkStruct5 *fn_1_58E0(s16 arg0, Vec *arg1, Vec *arg2, f32 arg3, GXColor *arg4)
{
    s16 var_r29;
    unkStruct5 *var_r31;
    unkStruct6 *temp_r30;
    ModelData *var_r28;

    var_r28 = &Hu3DData[arg0];
    temp_r30 = (unkStruct6 *)var_r28->unk_120;

    var_r29 = 0;
    var_r31 = temp_r30->unk18;
    for (; var_r29 < temp_r30->unk0; var_r29++, var_r31++) {
        if (var_r31->unk4E == 0) {
            break;
        }
    }
    if (var_r29 == temp_r30->unk0) {
        return NULL;
    }
    temp_r30->unk24[var_r29].r = arg4->r;
    temp_r30->unk24[var_r29].g = arg4->g;
    temp_r30->unk24[var_r29].b = arg4->b;
    temp_r30->unk24[var_r29].a = arg4->a;
    var_r31->unk2E = var_r29;
    var_r31->unk30 = arg3;
    var_r31->unk34 = *arg2;
    var_r31->unk40 = *arg1;
    var_r31->unk4C = 0;
    var_r31->unk4E = 1;
    return var_r31;
}

s16 fn_1_5A18(AnimData *arg0, s16 arg1, f32 arg8, s16 arg2, s16 arg3)
{
    ModelData *temp_r28;
    f32 temp_f0;
    s16 var_r21;
    s16 var_r22;
    s16 var_r30;
    s16 var_r20;
    unkStruct6 *var_r31;
    void *var_r19;
    void *var_r18;
    unkStruct5 *var_r24;
    Vec *var_r25;
    GXColor *var_r27;
    HsfVector2f *var_r29;

    var_r21 = Hu3DHookFuncCreate(fn_1_602C);
    temp_r28 = &Hu3DData[var_r21];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(unkStruct6), temp_r28->unk_48);
    temp_r28->unk_120 = var_r31;
    arg0->useNum++;
    var_r31->unk10 = arg0;
    var_r31->unk0 = arg1;
    var_r31->unk8 = 0;
    var_r31->unkC = NULL;
    var_r24 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(unkStruct5), temp_r28->unk_48);
    var_r31->unk18 = var_r24;

    for (var_r30 = 0; var_r30 < arg1; var_r30++, var_r24++) {
        var_r24->unk4C = -1;
        var_r24->unk4E = 0;
    }
    var_r25 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec) * 4, temp_r28->unk_48);
    var_r31->unk1C = var_r25;

    for (var_r30 = 0; var_r30 < (arg1 * 4); var_r30++, var_r25++) {
        var_r25->x = var_r25->y = var_r25->z = 0.0f;
    }
    var_r27 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(GXColor), temp_r28->unk_48);
    var_r31->unk24 = var_r27;

    for (var_r30 = 0; var_r30 < arg1; var_r30++, var_r27++) {
        var_r27->r = var_r27->g = var_r27->b = var_r27->a = 0xFF;
    }
    var_r29 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(HsfVector2f) * 4, temp_r28->unk_48);
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
    if ((arg2 != 0) || (arg3 != 0)) {
        var_r22 = arg0->bmp->sizeX / arg2;
        var_r20 = arg0->bmp->sizeY / arg3;
        var_r31->unk14 = (var_r22 * var_r20);
        var_r31->unk60 = (1.0f / var_r22);
        var_r31->unk64 = (1.0f / var_r20);
    }
    else {
        var_r22 = 1;
        var_r31->unk14 = 1;
        var_r31->unk60 = 1.0f;
        var_r31->unk64 = 1.0f;
    }
    var_r31->unk5C = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * sizeof(HsfVector2f), temp_r28->unk_48);
    fn_1_6608(var_r31->unk5C, var_r31->unk14, var_r22, var_r31->unk60, var_r31->unk64);
    var_r31->unk2C.x = var_r31->unk50.x = var_r31->unk44.y = var_r31->unk50.y = -arg8;
    var_r31->unk38.x = var_r31->unk44.x = var_r31->unk2C.y = var_r31->unk38.y = arg8;
    var_r31->unk2C.z = var_r31->unk38.z = var_r31->unk44.z = var_r31->unk50.z = 0.0f;
    var_r19 = var_r18 = HuMemDirectMallocNum(HEAP_DATA, 0x20000, temp_r28->unk_48);
    DCFlushRange(var_r19, 0x20000);
    GXBeginDisplayList(var_r19, 0x20000);
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
    var_r31->unk28 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk4, temp_r28->unk_48);
    memcpy(var_r31->unk28, var_r18, var_r31->unk4);
    DCFlushRange(var_r31->unk28, var_r31->unk4);
    HuMemDirectFree(var_r18);
    return var_r21;
}

void fn_1_5F5C(s16 arg0)
{
    ModelData *var_r31;
    unkStruct6 *var_r30;

    var_r31 = &Hu3DData[arg0];
    var_r30 = (unkStruct6 *)var_r31->unk_120;
    HuSprAnimKill(var_r30->unk10);
    Hu3DModelKill(arg0);
}

void fn_1_5FBC(s16 arg0, m409Func6 arg1)
{
    ModelData *var_r31;
    unkStruct6 *var_r30;

    var_r31 = &Hu3DData[arg0];
    var_r30 = (unkStruct6 *)var_r31->unk_120;
    var_r30->unkC = arg1;
}

void fn_1_5FF4(s16 arg0, u8 arg1)
{
    ModelData *var_r31;
    unkStruct6 *var_r30;

    var_r31 = &Hu3DData[arg0];
    var_r30 = (unkStruct6 *)var_r31->unk_120;
    var_r30->unk8 = arg1;
}

void fn_1_602C(ModelData *arg0, f32 (*arg1)[4])
{
    Mtx sp128;
    ROMtx spF8;
    Mtx spC8;
    Mtx sp98;
    Vec sp68[4];
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Vec *var_r31;
    s16 var_r24;
    HsfVector2f *var_r26;
    s16 var_r25;
    unkStruct6 *temp_r30;
    unkStruct5 *var_r29;
    m409Func6 var_r23;

    temp_r30 = (unkStruct6 *)arg0->unk_120;
    GXLoadPosMtxImm(arg1, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    var_r24 = temp_r30->unk10->bmp->dataFmt & 0xF;
    if ((var_r24 == 7) || (var_r24 == 8)) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
    }
    else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    }
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    if ((arg0->attr & 2) != 0) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
    else {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    }
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
    GXSetArray(GX_VA_POS, temp_r30->unk1C, 12);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, temp_r30->unk24, 4);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, temp_r30->unk20, 8);
    fn_1_40A4(arg1, sp128);
    PSMTXReorder(sp128, spF8);
    if (((u8)omPauseChk() == 0) && (temp_r30->unkC)) {
        var_r23 = temp_r30->unkC;
        var_r23(arg0, temp_r30, arg1);
    }
    var_r29 = temp_r30->unk18;
    var_r31 = temp_r30->unk1C;
    var_r26 = temp_r30->unk20;
    PSMTXROMultVecArray(spF8, &temp_r30->unk2C, &sp68[0], 4);

    for (var_r25 = 0; var_r25 < temp_r30->unk0; var_r25++, var_r29++, var_r26 += 4) {
        if (var_r29->unk4E == 0) {
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
            if (var_r29->unk30 == 0.0f) {
                fn_1_6778(&sp68[0], &sp38, &var_r29->unk34, 4);
                VECAdd(&sp38, &var_r29->unk40, var_r31++);
                VECAdd(&sp44, &var_r29->unk40, var_r31++);
                VECAdd(&sp50, &var_r29->unk40, var_r31++);
                VECAdd(&sp5C, &var_r29->unk40, var_r31++);
            }
            else {
                fn_1_6778(&temp_r30->unk2C, &sp38, &var_r29->unk34, 4);
                MTXRotRad(spC8, 0x5A, 0.017453292f * var_r29->unk30);
                MTXConcat(sp128, spC8, sp98);
                MTXMultVecArray(sp98, &sp38, &sp8, 4);
                VECAdd(&sp8, &var_r29->unk40, var_r31++);
                VECAdd(&sp14, &var_r29->unk40, var_r31++);
                VECAdd(&sp20, &var_r29->unk40, var_r31++);
                VECAdd(&sp2C, &var_r29->unk40, var_r31++);
            }
            if (var_r29->unk4C != -1) {
                fn_1_66D4(var_r26, temp_r30->unk5C, var_r29->unk4C, temp_r30->unk60, temp_r30->unk64);
            }
        }
    }
    DCFlushRangeNoSync(temp_r30->unk1C, temp_r30->unk0 * 0xC * 4);
    DCFlushRangeNoSync(temp_r30->unk20, temp_r30->unk0 * 8 * 4);
    PPCSync();
    GXCallDisplayList(temp_r30->unk28, temp_r30->unk4);
}

void fn_1_6608(HsfVector2f *arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4)
{
    s16 var_r31;
    s16 var_r30;
    s16 var_r29;

    for (var_r31 = 0; var_r31 < arg1; var_r31++, arg0++) {
        var_r30 = (var_r31 % arg2);
        var_r29 = (var_r31 / arg2);
        arg0->x = (var_r30 * arg3);
        arg0->y = (var_r29 * arg4);
    }
}

void fn_1_66D4(HsfVector2f *arg0, HsfVector2f *arg1, s16 arg2, f32 arg3, f32 arg4)
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

void fn_1_6778(Vec *arg0, Vec *arg1, Vec *arg2, s16 arg3)
{
    s16 var_r31;

    for (var_r31 = 0; var_r31 < arg3; var_r31++, arg0++, arg1++) {
        arg1->x = arg0->x * arg2->x;
        arg1->y = arg0->y * arg2->y;
        arg1->z = arg0->z * arg2->z;
    }
}
