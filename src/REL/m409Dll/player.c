#include "REL/m409Dll.h"

#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfmotion.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "ext_math.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#endif

// bss
omObjData *lbl_1_bss_3A0[4];
omObjData *lbl_1_bss_39C;
s32 lbl_1_bss_38C[4];
unkStruct10 lbl_1_bss_10C[8];
s16 lbl_1_bss_108;
s16 lbl_1_bss_106;
s16 lbl_1_bss_104;
unkStruct9 lbl_1_bss_F0;

// data
u32 lbl_1_data_138 = 0xFFFF0000;
s32 lbl_1_data_13C[7] = { 0x30, 0x2D, 0x3A, 0x2E, DATA_MAKE_NUM(DATADIR_M409, 0x32), 0x17, 0x18 };
GXColor lbl_1_data_158[8] = { { 0xFF, 0x00, 0x00, 0xFF }, { 0x00, 0x00, 0xFF, 0xFF }, { 0xFF, 0x80, 0x80, 0xFF }, { 0x00, 0xFF, 0x00, 0xFF },
    { 0x80, 0x00, 0xC0, 0xFF }, { 0x90, 0x30, 0x00, 0xFF }, { 0xFF, 0xFF, 0x00, 0xFF }, { 0x00, 0x00, 0x00, 0xFF } };
HsfVector2f lbl_1_data_178[4] = {
    { 72.0f, 80.0f },
    { 504.0f, 80.0f },
    { 72.0f, 400.0f },
    { 504.0f, 400.0f },
};
GXColor lbl_1_data_198[8] = { { 0xD0, 0x00, 0x00, 0xFF }, { 0x00, 0x00, 0xFF, 0xFF }, { 0x00, 0xA0, 0x00, 0xFF }, { 0xFF, 0xFF, 0x00, 0xFF },
    { 0xA0, 0x00, 0xFF, 0xFF }, { 0xFF, 0x80, 0x40, 0xFF }, { 0xFF, 0xA0, 0xF0, 0xFF }, { 0x00, 0xFF, 0x40, 0xFF } };

void fn_1_67E0(Process *arg0)
{
    s32 var_r31;
    s32 temp_r28;
    omObjData *var_r30;

    omMakeGroupEx(arg0, 0, 4);
    omGetGroupMemberListEx(arg0, 0);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_3A0[var_r31] = var_r30 = omAddObjEx(arg0, 0x30, 3, 7, 0, fn_1_6928);
        var_r30->work[0] = var_r31;
    }
    lbl_1_bss_39C = var_r30 = omAddObjEx(arg0, 0x40, 8, 0xA, 4, fn_1_91C0);
    fn_1_BF88(0x40, 0x40);
    fn_1_DF20(DATA_MAKE_NUM(DATADIR_M409, 0x2C), 0x40, 0x40);
    temp_r28 = (u8)frand();

    for (var_r31 = 0; var_r31 < (temp_r28 + 1); var_r31++) {
        fn_1_ABB4();
    }
}

void fn_1_6900(void)
{
    CharModelKill(-1);
    fn_1_C0C0();
}

void fn_1_6928(omObjData *arg0)
{
    Vec sp8[4] = { { -185.0f, 35.0f, 100.0f }, { -62.5f, 35.0f, 100.0f }, { 62.5f, 35.0f, 100.0f }, { 185.0f, 35.0f, 100.0f } };
    s8 sp38[8][32] = { "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r",
        "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r", "test11_tex_we-itemhook-r" };
    unkStruct7 *var_r31;
    s32 var_r30;
    s32 var_r28;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkStruct7), MEMORY_DEFAULT_NUM);
    arg0->data = var_r31;
    var_r31->unk0 = arg0->work[0];
    var_r31->unk1 = GWPlayerCfg[var_r31->unk0].character;
    var_r31->unk2 = (var_r31->unk0 >> 1);
    var_r31->unk3 = (var_r31->unk0 & 1);
    var_r31->unk4 = GWPlayerCfg[var_r31->unk0].pad_idx;
    var_r31->unk5 = GWPlayerCfg[var_r31->unk0].iscom;
    var_r31->unk6 = GWPlayerCfg[var_r31->unk0].diff;
    var_r31->unk1C = 0;
    var_r31->unk13 = 1;
    var_r31->unk14 = 0;
    var_r31->unk61 = fn_1_ABB4() & 0x1;
    var_r31->unk64 = var_r31->unk63 = 0;
    var_r31->unk18 = -1;
    var_r31->unk24.x = sp8[var_r31->unk0].x;
    var_r31->unk24.y = sp8[var_r31->unk0].y;
    var_r31->unk24.z = sp8[var_r31->unk0].z;
    var_r31->unk30.x = var_r31->unk30.y = var_r31->unk30.z = 0.0f;
    var_r31->unk3C.y = 180.0f;
    var_r31->unk3C.x = var_r31->unk3C.z = 0.0f;
    var_r30 = CharModelCreate(var_r31->unk1, 4);
    arg0->model[0] = var_r30;
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);

    for (var_r28 = 0; var_r28 < 7; var_r28++) {
        if ((lbl_1_data_13C[var_r28] & 0xFFFF0000) != 0) {
            arg0->motion[var_r28] = CharModelMotionCreate(var_r31->unk1, var_r31->unk1 + lbl_1_data_13C[var_r28]);
        }
        else {
            arg0->motion[var_r28] = CharModelMotionCreate(var_r31->unk1, lbl_1_data_13C[var_r28]);
        }
    }
    CharModelMotionDataClose(var_r31->unk1);
    CharModelMotionSet(var_r31->unk1, arg0->motion[var_r31->unk1C]);
    omSetTra(arg0, var_r31->unk24.x, var_r31->unk24.y, var_r31->unk24.z);
    Hu3DModelPosSet(var_r30, var_r31->unk24.x, var_r31->unk24.y, var_r31->unk24.z);
    Hu3DModelRotSet(var_r30, 0.0f, 30.0f, 0.0f);
    CharModelStepTypeSet(var_r31->unk1, 0);
    arg0->model[1] = var_r30 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M409, 0x12));
    Hu3DModelHookSet(arg0->model[0], (char *)sp38[var_r31->unk1], arg0->model[1]);
    var_r30 = fn_1_DA48(2, 1);
    var_r31->unk57 = var_r30;
    lbl_1_bss_F0.unk10[var_r30].unk30 = fn_1_8838;
    fn_1_E2A8(var_r30, 0, DATA_MAKE_NUM(DATADIR_M409, 0x2B), 0x40, 0x40);
    fn_1_F098(
        var_r30, lbl_1_data_158[var_r31->unk1].r, lbl_1_data_158[var_r31->unk1].g, lbl_1_data_158[var_r31->unk1].b, lbl_1_data_158[var_r31->unk1].a);
    fn_1_F024(var_r30, 1, lbl_1_data_158[var_r31->unk1].r, lbl_1_data_158[var_r31->unk1].g, lbl_1_data_158[var_r31->unk1].b, 0x98);
    fn_1_E85C(var_r30, 0, var_r31->unk24.x, 100.0f + var_r31->unk24.y, -1200.0f);
    fn_1_ED44(var_r30, 0, 0x10);
    fn_1_EC1C(var_r30, 0, 2.0f, 2.0f, 1.0f);
    fn_1_EC1C(var_r30, 1, 2.5f, 2.5f, 1.0f);
    fn_1_ED44(var_r30, 1, 0x14);
    fn_1_F408(var_r30, 1, 1);
    var_r30 = fn_1_DA48(1, 1);
    fn_1_DEF4(var_r30, 0, 0);
    fn_1_E7C8(lbl_1_bss_F0.unk6, 0, DATA_MAKE_NUM(DATADIR_M409, 0x2D));
    var_r31->unk58 = var_r30;
    lbl_1_bss_F0.unk10[var_r30].unk30 = &fn_1_8D6C;
    fn_1_ED44(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 4);
    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk70[0] = var_r31->unk0;
    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk70[1] = -1;
    fn_1_EC1C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0.5f, 0.5f, 1.0f);
    var_r31->unk59 = 0;
    var_r31->unk60 = 0;
    var_r30 = espEntry(DATA_MAKE_NUM(DATADIR_M409, 0x31), 1, 0);
    var_r31->unk55 = var_r30;
    espColorSet(var_r30, 0, 0, 0);
    espTPLvlSet(var_r30, 0.5);
    espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x, lbl_1_data_178[var_r31->unk0].y);
    espAttrSet(var_r30, HUSPR_ATTR_DISPOFF);
    var_r30 = espEntry(DATA_MAKE_NUM(DATADIR_M409, 0x30), 1, 0);
    var_r31->unk54 = var_r30;
    espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x, lbl_1_data_178[var_r31->unk0].y);
    espAttrSet(var_r30, HUSPR_ATTR_DISPOFF);
    var_r30 = espEntry(var_r31->unk1 + DATA_MAKE_NUM(DATADIR_MGCONST, 0x00), 1, 0);
    var_r31->unk56 = var_r30;
    espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x - 27.0f, lbl_1_data_178[var_r31->unk0].y - 20.0f);
    espAttrSet(var_r30, HUSPR_ATTR_DISPOFF);

    for (var_r28 = 0; var_r28 < 3; var_r28++) {
        var_r30 = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x0A), 0, 0);
        var_r31->unk5A[var_r28][0] = var_r30;
        espAttrSet(var_r30, HUSPR_ATTR_DISPOFF);
        espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x - 32.0f + (var_r28 * 0x1E), 16.0f + lbl_1_data_178[var_r31->unk0].y);
        var_r30 = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x0B), 0, 0);
        var_r31->unk5A[var_r28][1] = var_r30;
        espAttrSet(var_r30, HUSPR_ATTR_DISPOFF);
        espPosSet(var_r30, lbl_1_data_178[var_r31->unk0].x - 32.0f + (var_r28 * 0x1E), 16.0f + lbl_1_data_178[var_r31->unk0].y);
    }
    arg0->func = fn_1_7344;
}

void fn_1_7344(omObjData *arg0)
{
    s16 sp8;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f31;
    s32 temp_r19;
    s16 temp_r22;
    s16 temp_r26;
    s16 temp_r25;
    s16 var_r27;
    s16 var_r28;
    s32 var_r24;
    s32 temp_r23;
    unkStruct8Sub *temp_r30;
    unkStruct7 *temp_r31;

    var_f31 = 0.0f;
    temp_r31 = (unkStruct7 *)arg0->data;
    temp_r19 = arg0->model[0];
    temp_r31->unk48 = temp_r31->unk24;
    var_r28 = temp_r31->unk1C;
    if (temp_r31->unk5 != 0) {
        fn_1_7FE8(arg0);
    }
    else {
        temp_r31->unkA = HuPadStkX[temp_r31->unk4];
        temp_r31->unkC = HuPadStkY[temp_r31->unk4];
        temp_r31->unkE = HuPadBtnDown[temp_r31->unk4];
        temp_r31->unk10 = HuPadBtn[temp_r31->unk4];
    }
    temp_r26 = temp_r31->unkA;
    temp_r25 = temp_r31->unkC;
    temp_r22 = temp_r31->unkE;
    sp8 = temp_r31->unk10;
    fn_1_DEF4(temp_r31->unk57, 0, 0);
    fn_1_F478(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 2);
    temp_r30 = fn_1_CCCC(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8);
    if (fn_1_2454(7) != 3) {
        fn_1_ED00(temp_r31->unk57, 4);
    }
    else {
        espAttrReset(temp_r31->unk54, HUSPR_ATTR_DISPOFF);
        espAttrReset(temp_r31->unk55, HUSPR_ATTR_DISPOFF);

        for (var_r24 = 0; var_r24 < 3; var_r24++) {
            espAttrReset(temp_r31->unk5A[var_r24][0], HUSPR_ATTR_DISPOFF);
        }
        espAttrReset(temp_r31->unk56, HUSPR_ATTR_DISPOFF);
        fn_1_EE24(temp_r31->unk57, 4);
        temp_f28 = (ABS(temp_r26) + ABS(temp_r25));
        temp_f30 = 0.008f * (temp_f28 * temp_r26);
        temp_f29 = 0.008f * (temp_f28 * temp_r25);
        fn_1_E99C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, temp_f30, temp_f29, 0.0f);
    }
    switch (lbl_1_bss_108) {
        case 4:
            if (temp_r31->unk1C == 2) {
                fn_1_F478(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 0);
                if ((temp_r22 & 0x100) != 0) {
                    temp_r23 = fn_1_8D08(temp_r31->unk0);
                    fn_1_DEF4(temp_r31->unk58, 0, 0);
                    fn_1_EE68(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 4);
                    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk70[1] = temp_r23;
                    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk70[2] = 0;
                    lbl_1_bss_F0.unk10[lbl_1_bss_F0.unk6].unk3C[lbl_1_bss_F0.unk8].unk70[3] = 0;
                    fn_1_E85C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, temp_r31->unk24.x, 100.0f + temp_r31->unk24.y, temp_r31->unk24.z);
                    if (temp_r23 == -1) {
                        lbl_1_bss_F0.unk10[temp_r31->unk58].unk3C[0].unk58.x = temp_r30->unk0.x;
                        lbl_1_bss_F0.unk10[temp_r31->unk58].unk3C[0].unk58.y = temp_r30->unk0.y;
                        lbl_1_bss_F0.unk10[temp_r31->unk58].unk3C[0].unk58.z = temp_r30->unk0.z;
                    }
                }
            }
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            if (temp_r31->unk59 >= 3) {
                lbl_1_bss_104 = temp_r31->unk0 + 1;
            }
            if (temp_r31->unk60 == 0) {
                temp_f29 = atan2d(temp_r30->unk0.x - temp_r31->unk24.x, temp_r30->unk0.z - temp_r31->unk24.z);
                temp_f30 = atan2d(temp_r31->unk24.y - temp_r30->unk0.y, temp_r31->unk24.z - temp_r30->unk0.z);
                temp_f30 *= (1.0f - (0.015f * ABS(temp_f30)));
                temp_r31->unk3C.x = fn_1_AD40(temp_r31->unk3C.x, temp_f30, 0.5f);
                temp_r31->unk3C.y = fn_1_AD40(temp_r31->unk3C.y, temp_f29, 0.5f);
            }
            break;
        case 6:
            fn_1_ED44(temp_r31->unk57, 0, 4);
            Hu3DModelHookReset(temp_r19);
            Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF);
            temp_r23 = fn_1_DA48(1, 1);
            fn_1_DEF4(temp_r23, 0, 0);
            fn_1_E7C8(lbl_1_bss_F0.unk6, 0, DATA_MAKE_NUM(DATADIR_M409, 0x2C));
            fn_1_E85C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 20.0f + temp_r31->unk24.x, 100.0f + temp_r31->unk24.y, temp_r31->unk24.z - 25.0f);
            fn_1_EC1C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 2.0f, 2.0f, 1.0f);
            fn_1_ED44(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0x80000000);
            fn_1_F024(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0xFF, 0xFF, 0xFF, 0xFF);
            fn_1_F17C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 0x11);
            fn_1_F2F8(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 0.5f);
        case 7:
            temp_r31->unk3C.y = fn_1_AD40(temp_r31->unk3C.y, 0.0f, 0.8f);
            temp_r31->unk3C.x = 0.0f;
            if (fn_1_2454(0x80) == 0x80) {
                if (temp_r31->unk59 >= 3) {
                    var_r28 = 5;
                }
                else {
                    var_r28 = 6;
                }
                var_r27 = 0;
                var_f31 = 0.0f;
            }
            break;
    }
    switch (temp_r31->unk1C) {
        case 0:
            if ((lbl_1_bss_108 != 0) && (lbl_1_bss_108 < 6)) {
                var_r28 = 1;
                var_r27 = 0;
                var_f31 = 0.0f;
                temp_r31->unk62 = (s8)(8.0f * (fn_1_ABB4() / 65536.0f));
            }
            break;
        case 2:
            if (lbl_1_bss_108 == 0) {
                var_r28 = 1;
                var_r27 = 4;
                var_f31 = fn_1_BF38(arg0->motion[1]);
                lbl_1_bss_38C[arg0->work[0]] = 1;
            }
            if ((lbl_1_bss_108 == 4) && ((temp_r22 & 0x100) != 0)) {
                HuAudFXPlay(0x556);
                var_r28 = 3;
                var_r27 = 0;
                var_f31 = 0.0f;
            }
            break;
        case 1:
            if (CharModelMotionEndCheck(temp_r31->unk1) != 0) {
                if (CharModelMotionTimeGet(temp_r31->unk1) <= 0.0f) {
                    var_r28 = 0;
                }
                else {
                    var_r28 = 2;
                }
                var_r27 = 1;
                var_f31 = 0.0f;
            }
            break;
        case 3:
            if (temp_r31->unk60 != 0) {
                temp_r31->unk3C.x = fn_1_AD40(temp_r31->unk3C.x, 0.0f, 0.8f);
                temp_r31->unk3C.y = fn_1_AD40(temp_r31->unk3C.y, 0.0f, 0.8f);
                if (ABS(temp_r31->unk3C.y) < 10.0f) {
                    temp_r31->unk3C.y = 0.0f;
                    var_r28 = 4;
                    var_r27 = 0;
                    var_f31 = 0.0f;
                }
            }
            else if (CharModelMotionEndCheck(temp_r31->unk1) != 0) {
                var_r28 = 2;
                var_r27 = 1;
                var_f31 = 0.0f;
            }
            break;
        case 4:
            if (temp_r31->unk18 < 0) {
                temp_r31->unk18 = HuAudCharVoicePlay(temp_r31->unk1, 0x125);
            }
            if (CharModelMotionEndCheck(temp_r31->unk1) != 0) {
                temp_r31->unk3C.y = fn_1_AD40(temp_r31->unk3C.y, 180.0f, 0.8f);
                if (ABS(temp_r31->unk3C.y) > 170.0f) {
                    var_r28 = 2;
                    var_r27 = 1;
                    var_f31 = 0.0f;
                    temp_r31->unk60 = 0;
                    temp_r31->unk18 = -1;
                }
            }
            else {
                temp_r31->unk3C.y = 0.0f;
            }
            break;
        case 5:
        case 6:
            break;
    }
    if (var_r28 != temp_r31->unk1C) {
        temp_r31->unk1C = var_r28;
        CharModelMotionShiftSet(temp_r31->unk1, arg0->motion[temp_r31->unk1C], var_f31, 8.0f, var_r27);
    }
    omSetTra(arg0, temp_r31->unk24.x, temp_r31->unk24.y, temp_r31->unk24.z);
    omSetRot(arg0, temp_r31->unk3C.x, temp_r31->unk3C.y, temp_r31->unk3C.z);
}

void fn_1_7FE8(omObjData *arg0)
{
    Vec sp20;
    Vec sp14;
    unkStruct10 *var_r30;
    unkStruct8Sub *temp_r29;
    f32 temp_f29;
    f32 temp_f30;
    s32 var_r28;

    unkStruct7 *temp_r31 = (unkStruct7 *)arg0->data;
    s32 sp10 = arg0->model[0];
    s16 sp8 = temp_r31->unk1C;
    temp_r31->unkE = temp_r31->unk10 = 0;
    temp_r29 = fn_1_CCCC(temp_r31->unk57, 0);
    sp20.x = sp20.y = sp20.z = 0.0f;
    switch (lbl_1_bss_108) { /* irregular */
        case 2:
            if (temp_r31->unk61 == 0) {
                var_r30 = &lbl_1_bss_10C[0];

                for (var_r28 = 0; var_r28 < 8; var_r28++, var_r30++) {
                    if (var_r30->unk2 == 0)
                        break;
                    sp20.x += var_r30->unkC.x;
                    sp20.y += var_r30->unkC.y;
                    sp20.z += var_r30->unkC.z;
                }
                sp20.x /= var_r28;
                sp20.y /= var_r28;
                sp20.z /= var_r28;
            }
            else {
                var_r30 = &lbl_1_bss_10C[temp_r31->unk62];
                if (var_r30->unk2 != 0) {
                    sp20.x = var_r30->unkC.x;
                    sp20.y = var_r30->unkC.y;
                    sp20.z = var_r30->unkC.z;
                }
                else {
                    sp20.x = 0.0f;
                    sp20.y = 800.0f;
                    sp20.z = -1200.0f;
                }
            }
            break;
        case 3:
            temp_r31->unk62 = 0xFF;
            temp_r31->unk64 = (0x28 - (temp_r31->unk6 * 10));
        case 4:
            sp20.x = temp_r29->unk0.x;
            sp20.y = temp_r29->unk0.y;
            sp20.z = temp_r29->unk0.z;
            if (temp_r31->unk64 != 0) {
                temp_r31->unk64--;
            }
            if ((temp_r31->unk64 == 0)) {
                if (((s32)((0x30 - (temp_r31->unk6 * 8)) * (fn_1_ABB4() / 65536.0f)) == 0)) {
                    temp_r31->unk62 = lbl_1_bss_106;
                }
            }
            if (temp_r31->unk62 != 0xFF) {
                var_r30 = &lbl_1_bss_10C[temp_r31->unk62];
                sp20.x = var_r30->unkC.x;
                sp20.y = var_r30->unkC.y;
                sp20.z = var_r30->unkC.z;
                temp_f29 = 100.0f * (0.5f * (4 - temp_r31->unk6));
                temp_f29 = 20.0f + (temp_f29 * (fn_1_ABB4() / 65536.0f));
                temp_f30 = ((var_r30->unkC.z - temp_r29->unk0.z) * (var_r30->unkC.z - temp_r29->unk0.z))
                    + (((var_r30->unkC.x - temp_r29->unk0.x) * (var_r30->unkC.x - temp_r29->unk0.x))
                        + ((var_r30->unkC.y - temp_r29->unk0.y) * (var_r30->unkC.y - temp_r29->unk0.y)));
                if ((sqrtf(temp_f30) < temp_f29) && ((s32)((0x20 - (temp_r31->unk6 * 8)) * (fn_1_ABB4() / 65536.0f)) == 0)) {
                    temp_r31->unkE = (temp_r31->unkE | 0x100);
                }
            }
            break;
        default:
            sp20.x = 0.0f;
            sp20.y = 800.0f;
            sp20.z = -1200.0f;
            break;
    }
    if (temp_r31->unk63 == 0) {
        temp_f29 = 100.0f * (0.5f * (4 - temp_r31->unk6));
        sp20.x += (temp_f29 * ((fn_1_ABB4() - 0x8000) / 32768.0f));
        sp20.y += (temp_f29 * ((fn_1_ABB4() - 0x8000) / 32768.0f));
        temp_r31->unk68.x = sp20.x;
        temp_r31->unk68.y = sp20.y;
        temp_r31->unk68.z = sp20.z;
        sp14.x = temp_r31->unk68.x - temp_r29->unk0.x;
        sp14.y = temp_r31->unk68.y - temp_r29->unk0.y;
        sp14.z = temp_r31->unk68.z - temp_r29->unk0.z;
        fn_1_B378(&sp14);
        temp_r31->unkA = (sp14.x * ((temp_r31->unk6 * 6) + 0x18));
        temp_r31->unkC = (sp14.y * ((temp_r31->unk6 * 6) + 0x18));
        temp_r31->unk63 = ((s32)(((4 - temp_r31->unk6) * 8) * (fn_1_ABB4() / 65536.0f)) + 8);
    }
    temp_r31->unk63--;
}

void fn_1_8838(unkStruct8 *arg0)
{
    Vec sp18;
    Vec spC;
    f32 sp8;
    f32 temp_f30;
    f32 temp_f31;
    unkStruct8Sub *temp_r30;
    Vec *var_r26;
    s32 var_r28;
    unkStruct10 *temp_r29;
    unkStruct8Sub *temp_r31;

    temp_r30 = &arg0->unk3C[0];
    if (temp_r30->unk0.x < -600.0f) {
        temp_r30->unk0.x = -600.0f;
    }
    if (temp_r30->unk0.x > 600.0f) {
        temp_r30->unk0.x = 600.0f;
    }
    if (temp_r30->unk0.y < 350.0f) {
        temp_r30->unk0.y = 350.0f;
    }
    if (temp_r30->unk0.y > 1200.0f) {
        temp_r30->unk0.y = 1200.0f;
    }
    sp8 = 75.0f;
    spC = temp_r30->unk0;
    var_r26 = &spC;
    var_r28 = fn_1_A9C0(var_r26, &sp8);
    temp_r31 = &arg0->unk3C[1];
    if (var_r28 == -1) {
        if (temp_r31->unk70[0] != -1) {
            temp_r31->unk70[0] = -1;
            temp_r31->unk74 = 0.0f;
            temp_r31->unk58.x = temp_r31->unk0.x;
            temp_r31->unk58.y = temp_r31->unk0.y;
            temp_r31->unk58.z = temp_r31->unk0.z;
            temp_r31->unk78 = temp_r31->unk18.x;
        }
        if (temp_r31->unk74 < 90.0f) {
            temp_r31->unk74 += 9.0f;
            if (temp_r31->unk74 > 90.0f) {
                temp_r31->unk74 = 90.0f;
            }
            temp_f31 = sind(temp_r31->unk74);
            temp_f30 = cosd(temp_r31->unk74);
            sp18.x = temp_r30->unk0.x - temp_r31->unk58.x;
            sp18.y = temp_r30->unk0.y - temp_r31->unk58.y;
            sp18.z = temp_r30->unk0.z - temp_r31->unk58.z;
            temp_r31->unk0.x = (temp_r31->unk58.x + (sp18.x * temp_f31));
            temp_r31->unk0.y = (temp_r31->unk58.y + (sp18.y * temp_f31));
            temp_r31->unk0.z = (temp_r31->unk58.z + (sp18.z * temp_f31));
            temp_r31->unk18.x = (0.001f + (temp_r31->unk78 * temp_f30));
            temp_r31->unk18.y = (0.001f + (temp_r31->unk78 * temp_f30));
            temp_r31->unk18.z = 1.0f;
            return;
        }
        temp_r31->unk34 |= 4;
        temp_r31->unk0.x = temp_r30->unk0.x;
        temp_r31->unk0.y = temp_r30->unk0.y;
        temp_r31->unk0.z = temp_r30->unk0.z;
        return;
    }
    temp_r29 = &lbl_1_bss_10C[var_r28];
    if (temp_r31->unk70[0] != var_r28) {
        temp_r31->unk70[0] = var_r28;
        temp_r31->unk74 = 0.0f;
        temp_r31->unk58.x = temp_r31->unk0.x;
        temp_r31->unk58.y = temp_r31->unk0.y;
        temp_r31->unk58.z = temp_r31->unk0.z;
        temp_r31->unk78 = temp_r31->unk18.x;
        temp_r31->unk7C = (2.5f - temp_r31->unk18.x);
    }
    if (temp_r31->unk74 < 90.0f) {
        temp_r31->unk74 += 9.0f;
        if (temp_r31->unk74 > 90.0f) {
            temp_r31->unk74 = 90.0f;
        }
        temp_f31 = sind(temp_r31->unk74);
        sp18.x = temp_r29->unkC.x - temp_r31->unk58.x;
        sp18.y = temp_r29->unkC.y - temp_r31->unk58.y;
        sp18.z = temp_r29->unkC.z - temp_r31->unk58.z;
        temp_r31->unk0.x = (temp_r31->unk58.x + (sp18.x * temp_f31));
        temp_r31->unk0.y = (temp_r31->unk58.y + (sp18.y * temp_f31));
        temp_r31->unk0.z = (temp_r31->unk58.z + (sp18.z * temp_f31));
        temp_r31->unk18.x = (temp_r31->unk78 + (temp_r31->unk7C * temp_f31));
        temp_r31->unk18.y = (temp_r31->unk78 + (temp_r31->unk7C * temp_f31));
        temp_r31->unk18.z = 1.0f;
    }
    else {
        temp_r31->unk0.x = temp_r29->unkC.x;
        temp_r31->unk0.y = temp_r29->unkC.y;
        temp_r31->unk0.z = temp_r29->unkC.z;
    }
    temp_r31->unk34 &= ~4;
}

s8 fn_1_8D08(u8 arg0)
{
    unkStruct7 *data;
    unkStruct8Sub *var_r30;

    data = (unkStruct7 *)lbl_1_bss_3A0[arg0]->data;
    var_r30 = fn_1_CCCC(data->unk57, 1);
    return var_r30->unk70[0];
}

void fn_1_8D6C(unkStruct8 *arg0)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 temp_r28;
    s32 var_r27;
    f32 var_f31;
    unkStruct10 *var_r29;
    unkStruct7 *temp_r30;
    unkStruct8Sub *temp_r31;

    temp_r31 = &arg0->unk3C[0];
    if ((temp_r31->unk34 & 4) == 0) {
        temp_r28 = temp_r31->unk70[1];
        if (temp_r31->unk70[2] == 0) {
            if (temp_r28 == -1) {
                sp8.x = temp_r31->unk58.x - temp_r31->unk0.x;
                sp8.y = temp_r31->unk58.y - temp_r31->unk0.y;
                sp8.z = temp_r31->unk58.z - temp_r31->unk0.z;
                fn_1_B378(&sp8);
                temp_r31->unk64.x = sp8.x;
                temp_r31->unk64.y = sp8.y;
                temp_r31->unk64.z = sp8.z;
            }
            temp_r31->unk70[2] = 0x10;
        }
        if (temp_r31->unk70[3] == 0) {
            if (temp_r28 != -1) {
                var_r29 = &lbl_1_bss_10C[temp_r28];
                if ((var_r29->unk2 != 0) && (var_r29->unk2 <= 4)) {
                    sp8.x = var_r29->unkC.x - temp_r31->unk0.x;
                    sp8.y = var_r29->unkC.y - temp_r31->unk0.y;
                    sp8.z = var_r29->unkC.z - temp_r31->unk0.z;
                    fn_1_B378(&sp8);
                    temp_r31->unk64.x = sp8.x;
                    temp_r31->unk64.y = sp8.y;
                    temp_r31->unk64.z = sp8.z;
                }
            }
            sp8.x = 100.0f * (2.0f * temp_r31->unk64.x);
            sp8.y = 100.0f * (2.0f * temp_r31->unk64.y);
            sp8.z = 100.0f * (2.0f * temp_r31->unk64.z);
            for (var_r29 = &lbl_1_bss_10C[0], var_r27 = 0; var_r27 < 8; var_r27++, var_r29++) {
                if ((Hu3DModelAttrGet(var_r29->unk0) & 1) == 0) {
                    var_f31 = fn_1_B6A4(&var_r29->unkC, &temp_r31->unk0, &sp8);
                    if (!(var_f31 >= 2250.0f) && (var_r29->unk2 == 3)) {
                        var_r29->unk2 = 4;
                        temp_r31->unk34 |= 4;
                        temp_r30 = (unkStruct7 *)lbl_1_bss_3A0[temp_r31->unk70[0]]->data;
                        if (var_r29->unk48 == lbl_1_bss_106) {
                            espAttrSet(temp_r30->unk5A[temp_r30->unk59][0], HUSPR_ATTR_DISPOFF);
                            espAttrReset(temp_r30->unk5A[temp_r30->unk59][1], HUSPR_ATTR_DISPOFF);
                            HuAudFXPlay(9);
                            temp_r30->unk59++;
                            omVibrate(temp_r30->unk0, 0xC, 6, 6);
                            if (temp_r30->unk59 < 3) {
                                temp_r30->unk60++;
                            }
                        }
                        else if (temp_r30->unk59 != 0) {
                            espAttrReset(temp_r30->unk5A[temp_r30->unk59][0], HUSPR_ATTR_DISPOFF);
                            espAttrSet(temp_r30->unk5A[temp_r30->unk59][1], HUSPR_ATTR_DISPOFF);
                        }
                    }
                }
            }
            sp20.x = -290.0f;
            sp20.y = 350.0f;
            sp20.z = -1200.0f;
            var_f31 = fn_1_B9E0(&sp20, &temp_r31->unk0, &sp8, &sp14, &sp8);
            if (var_f31 <= 100.0f) {
                temp_r31->unk0.x = sp14.x;
                temp_r31->unk0.y = sp14.y;
                temp_r31->unk0.z = sp14.z;
                temp_r31->unk64.x = sp8.x;
                temp_r31->unk64.y = sp8.y;
                temp_r31->unk64.z = sp8.z;
                temp_r31->unk70[3] = 1;
                return;
            }
        }
        temp_r31->unk0.x = (temp_r31->unk0.x + (200.0f * temp_r31->unk64.x));
        temp_r31->unk0.y = (temp_r31->unk0.y + (200.0f * temp_r31->unk64.y));
        temp_r31->unk0.z = (temp_r31->unk0.z + (200.0f * temp_r31->unk64.z));
        if (--temp_r31->unk70[2] == 0) {
            temp_r31->unk34 |= 4;
        }
    }
}

void fn_1_91C0(omObjData *arg0)
{
    s32 var_r28;
    s32 var_r30;
    unkStruct10 *var_r31;

    lbl_1_bss_108 = 0;
    var_r28 = Hu3DModelCreateFile(0x20000);
    arg0->model[0] = var_r28;
    Hu3DModelAttrSet(var_r28, HU3D_MOTATTR_LOOP);

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        arg0->motion[var_r30]
            = Hu3DJointMotion(var_r28, HuDataSelHeapReadNum(var_r30 + DATA_MAKE_NUM(DATADIR_M409, 0x0F), MEMORY_DEFAULT_NUM, HEAP_DATA));
    }
    Hu3DMotionSet(var_r28, arg0->motion[0]);
    omSetTra(arg0, 419.99997f, 250.0f, -180.0f);
    omSetRot(arg0, 0.0f, -30.0f, 0.0f);

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        arg0->work[var_r30] = 0;
    }

    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        var_r28 = Hu3DModelCreateFile(var_r30 + DATA_MAKE_NUM(DATADIR_M409, 0x1B));
        arg0->model[var_r30 + 1] = var_r28;
        Hu3DModelAttrSet(var_r28, HU3D_ATTR_DISPOFF);
    }
    lbl_1_bss_104 = 0;

    for (var_r31 = lbl_1_bss_10C, var_r30 = 0; var_r30 < 8; var_r30++, var_r31++) {
        var_r28 = Hu3DModelCreateFile(var_r30 + DATA_MAKE_NUM(DATADIR_M409, 0x13));
        var_r31->unk0 = var_r28;
        Hu3DModelLayerSet(var_r28, 3);
        var_r31->unkC.x = -400.0f + (100.0f * var_r30);
        var_r31->unkC.y = 300.0f + (100.0f * var_r30);
        var_r31->unkC.z = -1200.0f;
        Hu3DModelPosSet(var_r28, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
        var_r31->unk2 = var_r31->unk3 = 0;
        var_r31->unk18.x = var_r31->unk18.y = var_r31->unk18.z = 0.0f;
        var_r31->unk24.x = var_r31->unk24.y = var_r31->unk24.z = 1.0f;
        var_r31->unk3C.x = var_r31->unk3C.y = var_r31->unk3C.z = 0.0f;
        var_r31->unk30.x = var_r31->unkC.x;
        var_r31->unk30.y = var_r31->unkC.y;
        var_r31->unk30.z = var_r31->unkC.z;
        var_r31->unk48 = var_r30;
        fn_1_DEF4((var_r31->unk1 = fn_1_DA48(1, 1)), 0, 0);
        fn_1_E2A8(lbl_1_bss_F0.unk6, 0, var_r30 + DATA_MAKE_NUM(DATADIR_M409, 0x23), 0x40, 0x40);
        fn_1_EC1C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 2.0f, 2.0f, 1.0f);
        fn_1_F024(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0xFF, 0xFF, 0xFF, 0xA0);
        fn_1_ED44(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0x40000004);
        fn_1_F17C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 0x11);
        fn_1_F2F8(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 1.0f);
    }
    arg0->func = fn_1_962C;
}

void fn_1_962C(omObjData *arg0)
{
    s32 sp8[7];
    unkStruct10 *var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    f32 var_f31;

    var_r27 = 0;
    var_r31 = &lbl_1_bss_10C[0];

    switch (lbl_1_bss_108) {
        case 0:
            if (fn_1_2454(0x18) == 8) {
                lbl_1_bss_108++;
            }
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                if (lbl_1_bss_38C[var_r29] == 0)
                    break;
            }
            if (var_r29 < 4)
                break;
            if (lbl_1_bss_104 == 0)
                break;

            lbl_1_bss_108 = 6;
            break;
        case 1:
            arg0->work[0] = (s32)((fn_1_ABB4() / 65536.0f) * 3.0f) + 6;
            arg0->work[1] = lbl_1_bss_106 = (u16)((fn_1_ABB4() / 65536.0f) * *arg0->work);
            arg0->work[2]++;
            if (arg0->work[2] >= 12) {
                lbl_1_bss_104 = -1;
            }
            arg0->work[3] = 0;
            for (var_r29 = 0; var_r29 < arg0->work[0]; var_r29++, var_r31++) {
                var_r31->unk2 = 1;
            }
            lbl_1_bss_108++;
            break;
        case 3:
            Hu3DModelAttrReset(var_r26 = arg0->model[lbl_1_bss_106 + 1], HU3D_ATTR_DISPOFF);
            Hu3DModelHookSet(arg0->model[0], "g001mk-itemhook_r", var_r26);
            Hu3DMotionShiftSet(arg0->model[0], arg0->motion[1], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            HuAudFXPlay(0x558);
            lbl_1_bss_108++;
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                lbl_1_bss_38C[var_r29] = 0;
            }
            fn_1_2414(0x18, 0x10);
            break;
        case 5:
            if (arg0->work[3] == 0) {
                fn_1_AC08(sp8, arg0->work[0]);
                for (var_r29 = 0, var_r28 = 1; var_r29 < arg0->work[0]; var_r29++) {
                    var_r31 = &lbl_1_bss_10C[sp8[var_r29]];
                    if (var_r31->unk2 == 3) {
                        var_r31->unk2 = 4;
                        var_r31->unk4 = var_r28 * 10;
                        var_r28++;
                    }
                }
                arg0->work[3] = var_r28 * 10 + 10;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[2], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
                if (lbl_1_bss_104 == 0) {
                    fn_1_3840();
                }
                break;
            }
            if (--arg0->work[3] == 0) {
                lbl_1_bss_108 = 0;
                Hu3DModelHookReset(arg0->model[0]);
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                Hu3DModelAttrSet(arg0->model[lbl_1_bss_106 + 1], HU3D_ATTR_DISPOFF);
            }
            break;
        case 6:
            fn_1_2414(7, 4);
            fn_1_23EC(lbl_1_bss_104 - 1);
            lbl_1_bss_108++;
            break;
        case 7:
            break;
    }

    var_r31 = &lbl_1_bss_10C[0];
    for (var_r29 = 0; var_r29 < 8; var_r29++, var_r31++) {
        fn_1_DEF4(var_r31->unk1, 0, 0);

        switch (var_r31->unk2) {
            case 0:
                Hu3DModelAttrSet(var_r31->unk0, HU3D_ATTR_DISPOFF);
                var_r31->unkC.x = var_r31->unkC.y = var_r31->unkC.z = 0.0f;
                continue;
            case 1:
                var_r31->unkC.x = ((fn_1_ABB4() - 0x8000) / 32768.0f) * 150.0f;
                var_r31->unkC.y = (fn_1_ABB4() / 65536.0f) * 100.0f;
                var_r31->unkC.z = -1200.0f;
                Hu3DModelPosSet(var_r31->unk0, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
                Hu3DModelAttrSet(var_r31->unk0, HU3D_ATTR_DISPOFF);
                fn_1_EC1C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 2.0f, 2.0f, 1.0f);
                var_r31->unk18.z = ((fn_1_ABB4() - 0x8000) / 32768.0f) * 60.0f;
                var_r31->unk4 = ((100.0f - var_r31->unkC.y) * 0.5f);
                var_r31->unk8 = 100.0f * ((((fn_1_ABB4() / 65536.0f) * 0.006f) + 0.0128f) + (0.000035f * var_r31->unk4));
                var_r31->unk4C = ((fn_1_ABB4() - 0x8000) / 32768.0f) * 360.0f;
                var_r31->unk2++;
            case 2:
                if (--var_r31->unk4 != 0)
                    break;
                var_r31->unk4 = 1;
                var_r31->unk2++;
            case 3:
                if (var_r31->unk18.z < 0.0f) {
                    var_r31->unk18.z += 0.08f;
                    if (var_r31->unk18.z >= 0.0f) {
                        var_r31->unk18.z = 0.0f;
                    }
                }
                else {
                    var_r31->unk18.z -= 0.08f;
                    if (var_r31->unk18.z <= 0.0f) {
                        var_r31->unk18.z = 0.0f;
                    }
                }
                if (var_r31->unkC.y >= 375.0f) {
                    var_r31->unk8 -= 0.000001f * var_r31->unkC.y;
                }
                var_r31->unkC.x += sind(var_r31->unk18.z) * var_r31->unk8;
                var_r31->unkC.y += cosd(var_r31->unk18.z) * var_r31->unk8;
                if (var_r31->unkC.y >= 200.0) {
                    Hu3DModelAttrReset(var_r31->unk0, HU3D_ATTR_DISPOFF);
                }
                if (var_r31->unkC.x >= 550.0f) {
                    var_r31->unk18.z = -((fn_1_ABB4() / 65536.0f) * 20.0f);
                }
                if (var_r31->unkC.x <= -550.0f) {
                    var_r31->unk18.z = ((fn_1_ABB4() / 65536.0f) * 20.0f);
                }
                if (var_r31->unkC.y >= 1250.0f) {
                    var_r31->unk2 = 4;
                }
                break;
            case 4:
                if (--var_r31->unk4 != 0)
                    break;
                Hu3DModelAttrSet(var_r31->unk0, HU3D_ATTR_DISPOFF);
                fn_1_E85C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
                fn_1_EE68(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 4);
                if (lbl_1_bss_106 == var_r31->unk48) {
                    HuAudFXPlay(0x557);
                }
                else {
                    HuAudFXPlay(0x55A);
                }
                if (var_r31->unk48 == arg0->work[1]) {
                    lbl_1_bss_108 = 5;
                }
                var_r26 = fn_1_DA48(1, 1);
                fn_1_DEF4(var_r26, 0, 0);
                fn_1_E7C8(lbl_1_bss_F0.unk6, 0, DATA_MAKE_NUM(DATADIR_M409, 0x2C));
                fn_1_E85C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
                fn_1_EC1C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 4.0f, 4.0f, 1.0f);
                fn_1_ED44(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0x80000000);
                fn_1_F024(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, 0xFF, 0xFF, 0xFF, 0x60);
                fn_1_F17C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 0x11);
                fn_1_F2F8(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, lbl_1_bss_F0.unkA, 0.5f);
                var_r31->unk2++;
                break;
            case 5:
                var_r31->unk4++;
                fn_1_EC1C(lbl_1_bss_F0.unk6, lbl_1_bss_F0.unk8, (var_r31->unk4 * 0.1f) + 2.0f, (var_r31->unk4 * 0.1f) + 2.0f, 1.0f);
                var_r31->unkC.x = var_r31->unkC.y = var_r31->unkC.z = 0.0f;
                break;
        }
        if (var_r31->unkC.y <= 375.0f) {
            if (var_r31->unkC.x >= 150.0f) {
                var_r31->unkC.x = 150.0f;
            }
            if (var_r31->unkC.x <= -150.0f) {
                var_r31->unkC.x = -150.0f;
            }
        }
        else {
            var_r27++;
        }

        fn_1_A584(var_r31);
        Hu3DModelPosSet(var_r31->unk0, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
        var_f31 = sind(var_r31->unk4C);
        var_r31->unk4C += 3.0f;
        Hu3DModelRotSet(
            var_r31->unk0, 8.0 * sind(var_r31->unk4C * 0.3), var_r31->unk4C * 0.05f, (-var_r31->unk18.z * 0.25f) + (var_f31 * 8.0f));
    }

    if (lbl_1_bss_108 == 2 && var_r27 >= arg0->work[0]) {
        lbl_1_bss_108++;
    }
}

s32 fn_1_A584(unkStruct10 *arg0)
{
    s32 sp20[8];
    Vec sp14;
    Vec sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f31;
    s32 var_r28;
    s32 var_r29;
    unkStruct10 *var_r31;

    if ((arg0->unk2 == 0) || (arg0->unk2 >= 4U)) {
        return 0;
    }
    temp_f29 = 100.0f;
    var_r28 = 0;
    sp14.x = sp14.y = sp14.z = 0.0f;
    var_r31 = lbl_1_bss_10C;

    for (var_r29 = 0; var_r29 < 8; var_r29++, var_r31++) {
        if ((var_r31->unk2 != 0) && (var_r31->unk2 < 4U) && (var_r31 != arg0)) {
            sp8.x = arg0->unkC.x - var_r31->unkC.x;
            sp8.y = arg0->unkC.y - var_r31->unkC.y;
            sp8.z = arg0->unkC.z - var_r31->unkC.z;
            temp_f30 = fn_1_B378(&sp8);
            if (!(temp_f30 > temp_f29)) {
                sp20[var_r28] = var_r29;
                var_r28 += 1;
                sp14.x += 0.5f * (sp8.x * (temp_f29 - temp_f30));
                sp14.y += 0.5f * (sp8.y * (temp_f29 - temp_f30));
                sp14.z += 0.5f * (sp8.z * (temp_f29 - temp_f30));
            }
        }
    }
    if (var_r28 == 0) {
        return 0;
    }
    arg0->unkC.x += sp14.x;
    arg0->unkC.y += sp14.y;
    arg0->unkC.z += sp14.z;
    var_f31 = atan2d(sp14.x, sp14.y);
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    if (var_f31 > 60.0f) {
        var_f31 = 60.0f;
    }
    if (var_f31 < -60.0f) {
        var_f31 = -60.0f;
    }
    arg0->unk18.z = var_f31 = fn_1_AD40(arg0->unk18.z, var_f31, 0.5f);
    var_r31 = lbl_1_bss_10C;

    for (var_r29 = 0; var_r29 < 8; var_r29++, var_r31++) {
        if ((var_r31 != arg0) && (var_r31->unk2 != 0) && (var_r31->unk2 < 4U)) {
            sp8.x = var_r31->unkC.x - arg0->unkC.x;
            sp8.y = var_r31->unkC.y - arg0->unkC.y;
            sp8.z = var_r31->unkC.z - arg0->unkC.z;
            temp_f30 = fn_1_B378(&sp8);
            if (!(temp_f30 > temp_f29)) {
                var_r31->unkC.x += sp8.x * (temp_f29 - temp_f30);
                var_r31->unkC.y += sp8.y * (temp_f29 - temp_f30);
                var_r31->unkC.z += sp8.z * (temp_f29 - temp_f30);
                var_f31 = atan2d(sp8.x, sp8.y);
                if (var_f31 > 180.0f) {
                    var_f31 -= 360.0f;
                }
                if (var_f31 > 60.0f) {
                    var_f31 = 60.0f;
                }
                if (var_f31 < -60.0f) {
                    var_f31 = -60.0f;
                }
                var_r31->unk18.z = var_f31 = fn_1_AD40(var_r31->unk18.z, var_f31, 0.5f);
            }
        }
    }
    return 1;
}

s8 fn_1_A9C0(Vec *arg0, f32 *arg1)
{
    f32 temp_f29;
    f32 var_f30;
    s32 var_r27;
    s32 var_r29;
    unkStruct10 *var_r31;

    var_r27 = -1;
    var_r31 = lbl_1_bss_10C;
    var_f30 = *arg1;
    var_f30 *= var_f30;

    for (var_r29 = 0; var_r29 < 8; var_r29++, var_r31++) {
        if (((Hu3DModelAttrGet(var_r31->unk0) & 1) == 0) && !(var_r31->unkC.y < 300.0f)) {
            temp_f29 = ((arg0->z - var_r31->unkC.z) * (arg0->z - var_r31->unkC.z))
                + (((arg0->x - var_r31->unkC.x) * (arg0->x - var_r31->unkC.x)) + ((arg0->y - var_r31->unkC.y) * (arg0->y - var_r31->unkC.y)));
            if (!(temp_f29 > var_f30)) {
                var_r27 = var_r29;
                var_f30 = temp_f29;
            }
        }
    }
    *arg1 = sqrtf(var_f30);
    return var_r27;
}

u32 lbl_1_data_1EC = 0x41C64E6D;

s32 fn_1_ABB4(void)
{
    lbl_1_data_1EC *= 0x41C64E6D;
    lbl_1_data_1EC += 0x3039;
    return (lbl_1_data_1EC >> 0x10);
}

void fn_1_AC08(s32 *arg0, s32 arg1)
{
    s32 temp_r29;
    s32 temp_r30;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < arg1; var_r31++) {
        arg0[var_r31] = var_r31;
    }

    for (var_r31 = 0; var_r31 < arg1; var_r31++) {
        temp_r30 = (arg1 * (fn_1_ABB4() / 65536.0f));
        temp_r29 = arg0[var_r31];
        arg0[var_r31] = arg0[temp_r30];
        arg0[temp_r30] = temp_r29;
    }
}

f32 fn_1_AD40(f32 arg0, f32 arg1, f32 arg2)
{
    f32 var_f31;

    var_f31 = fmodf(arg1 - arg0, 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f31 = fmodf(arg0 + ((1.0f - arg2) * var_f31), 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 >= 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}

f32 fn_1_AE94(f32 arg8, f32 arg9, f32 argA, f32 argB)
{
    f32 temp_f31;
    f32 var_f30;

    temp_f31 = (1.0 - arg8);
    var_f30 = ((argB * (arg8 * arg8)) + ((arg9 * (temp_f31 * temp_f31)) + (2.0 * (argA * (temp_f31 * arg8)))));
    return var_f30;
}

void fn_1_AF0C(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg8)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        *arg3 = fn_1_AE94(arg8, *arg0++, *arg1++, *arg2++);
        arg3++;
    }
}

f32 fn_1_B028(f32 arg8, f32 arg9, f32 argA, f32 argB)
{
    f32 var_f31;

    var_f31 = (2.0 * ((arg8 * argB) + (((arg8 - 1.0) * arg9) + ((1.0 - (2.0 * arg8)) * argA))));
    return var_f31;
}

void fn_1_B0A0(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 arg8)
{
    f32 spC[3];
    f32 var_f29;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        spC[var_r31] = fn_1_B028(arg8, *arg0++, *arg1++, *arg2++);
    }

    var_f29 = sqrtf((spC[2] * spC[2]) + ((spC[0] * spC[0]) + (spC[1] * spC[1])));

    if (var_f29) {
        var_f29 = (1.0 / var_f29);
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            *arg3++ = var_f29 * spC[var_r31];
        }
    }
    else {
        *arg3++ = 0.0f;
        *arg3++ = 0.0f;
        *arg3++ = 1.0f;
    }
}

f32 fn_1_B378(Vec *arg0)
{
    f32 var_f30;
    f32 var_f29;

    var_f30 = (arg0->z * arg0->z) + ((arg0->x * arg0->x) + (arg0->y * arg0->y));
    var_f30 = sqrtf(var_f30);
    if (var_f30 != 0) {
        var_f29 = 1.0f / var_f30;
        arg0->x *= var_f29;
        arg0->y *= var_f29;
        arg0->z *= var_f29;
    }
    else {
        arg0->x = arg0->y = arg0->z = 0.0f;
    }
    return var_f30;
}

f32 fn_1_B510(Vec arg0, Vec arg1, Vec *arg2, f32 arg8)
{
    if (arg8 <= 0.0f) {
        arg2->x = arg0.x;
        arg2->y = arg0.y;
        arg2->z = arg0.z;
        arg8 = 0.0f;
    }
    else if (arg8 >= 1.0f) {
        arg2->x = (arg0.x + arg1.x);
        arg2->y = (arg0.y + arg1.y);
        arg2->z = (arg0.z + arg1.z);
        arg8 = 1.0f;
    }
    else {
        arg2->x = (arg0.x + (arg8 * arg1.x));
        arg2->y = (arg0.y + (arg8 * arg1.y));
        arg2->z = (arg0.z + (arg8 * arg1.z));
    }
    return arg8;
}

f32 fn_1_B5E8(Vec arg0, Vec arg1, Vec arg2)
{
    f32 temp_f30;
    f32 var_f31;

    var_f31 = (arg2.z * (arg1.z - arg0.z)) + ((arg2.x * (arg1.x - arg0.x)) + (arg2.y * (arg1.y - arg0.y)));
    temp_f30 = -((arg2.z * arg2.z) + ((arg2.x * arg2.x) + (arg2.y * arg2.y)));
    if (temp_f30 != 0.0f) {
        var_f31 /= temp_f30;
    }
    return var_f31;
}

f32 fn_1_B6A4(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Vec sp44;
    f32 var_f31;

    if (((arg2->z * arg2->z) + ((arg2->x * arg2->x) + (arg2->y * arg2->y))) == 0.0f) {
        return ((arg0->z - arg1->z) * (arg0->z - arg1->z))
            + (((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)));
    }
    else {
        var_f31 = fn_1_B5E8(*arg0, *arg1, *arg2);
        fn_1_B510(*arg1, *arg2, &sp44, var_f31);
        return ((arg0->z - sp44.z) * (arg0->z - sp44.z)) + (((arg0->x - sp44.x) * (arg0->x - sp44.x)) + ((arg0->y - sp44.y) * (arg0->y - sp44.y)));
    }
}

f32 fn_1_B9E0(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4)
{
    f32 var_f31;

    if (((arg2->z * arg2->z) + ((arg2->x * arg2->x) + (arg2->y * arg2->y))) == 0.0f) {
        return ((arg0->z - arg1->z) * (arg0->z - arg1->z))
            + (((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)));
    }
    else {
        var_f31 = fn_1_B5E8(*arg0, *arg1, *arg2);
        fn_1_B510(*arg1, *arg2, arg3, var_f31);
    }
    arg4->x = arg3->x - arg0->x;
    arg4->y = arg3->y - arg0->y;
    arg4->z = arg3->z - arg0->z;
    return fn_1_B378(arg4);
}

void fn_1_BE90(ModelData *model, ParticleData *particle, Mtx matrix)
{
    s32 var_r29;
    HsfanimStruct01 *var_r31;

    var_r31 = particle->unk_48;
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        var_r31->unk34.x = 0.0f;
        var_r31->unk34.y = 200.0f;
        var_r31->unk34.z = -500.0f;
        var_r31->unk2C = 80.0f;
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * 0x44);
}

f32 fn_1_BF38(s16 arg0)
{
    MotionData *motionData;
    HsfMotion *hsfMotionData;
    f32 length;

    motionData = &Hu3DMotion[arg0];
    hsfMotionData = motionData->hsfData->motion;
    length = hsfMotionData->len;
    return length;
}
