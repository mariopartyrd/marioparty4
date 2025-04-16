#include "REL/m440Dll.h"

#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/flag.h"
#include "game/gamework_data.h"
#include "game/hsfmotion.h"
#include "game/pad.h"
#include "math.h"
#include "string.h"
#include "version.h"

// bss
omObjData *lbl_1_bss_C0[4];
s16 lbl_1_bss_B8[4];
Vec lbl_1_bss_88[4];
f32 lbl_1_bss_84;
Vec lbl_1_bss_78;
s16 lbl_1_bss_74;
u8 lbl_1_bss_72;
s16 lbl_1_bss_70;

// data
s16 lbl_1_data_1D8 = 2;
s16 lbl_1_data_1DA = -1;
u32 lbl_1_data_1DC[8][2] = { { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00), 0 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02), 0 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03), 0 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x38), 0 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x48), 0 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17), 0 }, { 0x47000C, 1 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x36), 0 } };
f32 lbl_1_data_21C[4] = { 210.0f, 190.0f, 170.0f, 0.0f };

// prototypes
void fn_1_B180(omObjData *);

void fn_1_AE08(Process *arg0)
{
    s16 var_r31;

    omMakeGroupEx(arg0, 0, 4);
    omGetGroupMemberListEx(arg0, 0);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_C0[var_r31] = omAddObjEx(arg0, 0x64, 9, 8, 0, fn_1_AEE4);
        lbl_1_bss_C0[var_r31]->work[0] = var_r31;
    }
    omAddObjEx(arg0, 0x65, 0, 0, -1, fn_1_B180);
}

void fn_1_AEE4(omObjData *arg0)
{
    f32 var_f31;
    s32 temp_r28;
    s16 var_r29;
    unkObjStruct *temp_r31;

    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkObjStruct), MEMORY_DEFAULT_NUM);
    temp_r31 = (unkObjStruct *)arg0->data;
    memset(temp_r31, 0, sizeof(unkObjStruct));
    arg0->stat |= 0x100;
    temp_r31->unk4 = arg0->work[0];
    temp_r31->unk6 = GWPlayerCfg[temp_r31->unk4].pad_idx;
    temp_r31->unk8 = GWPlayerCfg[temp_r31->unk4].character;
    arg0->model[0] = CharModelCreate(temp_r31->unk8, 4);
    Hu3DModelLayerSet(arg0->model[0], 1);
    Hu3DModelShadowSet(arg0->model[0]);

    for (var_r29 = 0; var_r29 < 8; var_r29++) {
        if (lbl_1_data_1DC[var_r29][1] == 0) {
            arg0->motion[var_r29] = CharModelMotionCreate(temp_r31->unk8, lbl_1_data_1DC[var_r29][0]);
        }
        else {
            arg0->motion[var_r29] = CharModelMotionCreate(temp_r31->unk8, temp_r31->unk8 + lbl_1_data_1DC[var_r29][0]);
        }
    }
    CharModelVoiceEnableSet(temp_r31->unk8, arg0->motion[4], 0);
    CharModelMotionDataClose(temp_r31->unk8);
    Hu3DMotionSet(arg0->model[0], arg0->motion[0]);
    temp_r31->unk18.x = temp_r31->unk18.y = temp_r31->unk18.z = 0.0f;
    temp_r31->unk30.x = temp_r31->unk30.y = temp_r31->unk30.z = 0.0f;
    temp_r31->unk3C.y = 90.0f;
    temp_r31->unkC = 0;
    temp_r31->unkE = 2 * REFRESH_RATE_F;
    temp_r31->unk10 = temp_r31->unk12 = temp_r31->unk14 = 0;
    if (temp_r31->unk8 == 5) {
        var_f31 = 350.0f;
    }
    else {
        var_f31 = 410.0f;
    }
    temp_r31->unk5C = var_f31;
    temp_r28 = temp_r31->unk4;
    if (_CheckFlag(FLAG_ID_MAKE(1, 12)) == 0) {
        GWPlayer[temp_r28].coin_win = 0;
    }
    arg0->func = fn_1_B17C;
}

void fn_1_B17C(omObjData *arg0)
{
    return;
}

void fn_1_B180(omObjData *arg0)
{
    s16 var_r29;
    s16 var_r31;
    unkObjStruct *temp_r30;

    s32 var_r28 = GWSystem.player_curr;
    if (var_r28 < 0) {
        var_r28 = 0;
    }
    var_r29 = var_r28;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_B8[var_r31] = var_r29;
        var_r29 = (var_r29 + 1) % 4;
    }
    lbl_1_bss_88->x = (700.0f * cos(M_PI / 2 - M_PI / 9));
    lbl_1_bss_88->z = (700.0f * sin(M_PI / 2 - M_PI / 9));

    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        lbl_1_bss_88[var_r31].x = lbl_1_bss_88[var_r31 - 1].x - 150.0f;
        lbl_1_bss_88[var_r31].z = lbl_1_bss_88->z;
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        temp_r30 = lbl_1_bss_C0[lbl_1_bss_B8[var_r31]]->data;
        temp_r30->unkA = var_r31;
        temp_r30->unk24.x = (lbl_1_bss_88[var_r31].x - 1000.0f);
        temp_r30->unk24.y = 0.0f;
        temp_r30->unk24.z = lbl_1_bss_88->z;
    }
    arg0->func = fn_1_B3A4;
}

void fn_1_B3A4(omObjData *arg0)
{
    f32 sp14;
    ModelData *sp8;
    f32 var_f31;
    s16 var_r28;
    s16 var_r29;
    omObjData *var_r30;
    unkObjStruct *var_r31;

    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (lbl_1_bss_B8[var_r29] != -1) {
            var_r30 = lbl_1_bss_C0[lbl_1_bss_B8[var_r29]];
            sp8 = &Hu3DData[var_r30->model[0]];
            var_r31 = (unkObjStruct *)var_r30->data;
            switch (var_r31->unk0 & 0xF) {
                case 1:
                    var_r31->unkC++;
                    var_f31 = (f32)var_r31->unkC / var_r31->unkE;
                    if (var_f31 >= 1.0f) {
                        var_f31 = 1.0f;
                        var_r31->unkC = 0;
                        if (lbl_1_bss_72 == 0) {
                            lbl_1_bss_72 = 1;
                            fn_1_F228();
                        }
                        else {
                            fn_1_F4D4(var_r31, 15, 7);
                            Hu3DMotionShiftSet(var_r30->model[0], var_r30->motion[1], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
                        }
                    }
                    var_r28 = (var_r31->unkA == -1) ? 0 : var_r31->unkA;
                    var_r31->unk18.x = var_r31->unk24.x + (lbl_1_bss_88[var_r28].x - var_r31->unk24.x) * var_f31;
                    var_r31->unk18.y = 0.0f;
                    var_r31->unk18.z = var_r31->unk24.z + (lbl_1_bss_88[var_r28].z - var_r31->unk24.z) * var_f31;
                    var_r31->unk14++;
                    var_f31 = var_r31->unk14 / (REFRESH_RATE_F / 3.0f);
                    if (var_f31 >= 1.0f) {
                        var_f31 = 1.0f;
                    }
                    var_r31->unk30.y = var_r31->unk3C.y + (90.0f - var_r31->unk3C.y) * var_f31;
                    break;
                case 7:
                    var_r31->unkC++;
                    var_f31 = (f32)var_r31->unkC / (2.0f * REFRESH_RATE_F / 3);
                    if (var_f31 >= 1.0f) {
                        var_f31 = 1.0f;
                        var_r31->unkC = 0;
                        fn_1_F4D4(var_r31, 15, 8);
                        Hu3DMotionShiftSet(var_r30->model[0], var_r30->motion[0], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
                    }
                    var_r31->unk30.y = 90.0f + (lbl_1_data_21C[var_r31->unkA] - 90.0f) * var_f31;
                    var_r31->unk3C = var_r31->unk30;
                    break;
                case 2:
                    fn_1_B884(var_r30, var_r31);
                    break;
                case 3:
                    if (fn_1_1954() != 0) {
                        fn_1_16D8();
                        fn_1_C1D4(var_r30, var_r31);
                        fn_1_C944(var_r30, var_r31);
                        fn_1_D34C(var_r30, var_r31);
                    }
                    break;
                case 4:
                    fn_1_D7F8(var_r30, var_r31);
                    break;
                case 5:
                    fn_1_E034(var_r30, var_r31);
                    break;
                case 6:
                    if (fn_1_E8AC(var_r30, var_r31) != 0) {
                        lbl_1_bss_B8[var_r29] = -1;
                    }
                    break;
                case 0:
                case 8:
                    break;
            }
            Hu3DModelPosSet(var_r30->model[0], var_r31->unk18.x, var_r31->unk18.y, var_r31->unk18.z);
            Hu3DModelRotSet(var_r30->model[0], var_r31->unk30.x, var_r31->unk30.y, var_r31->unk30.z);
        }
    }
}

f32 lbl_1_data_250 = 70.0f;

void fn_1_B884(omObjData *arg0, unkObjStruct *arg1)
{
    s16 sp8[5] = { 3, 1, 0, 2, 4 };
    f32 var_f29;
    f32 var_f28;
    f32 var_f31;
    f32 var_f30;
    s16 var_r30;

    switch (lbl_1_bss_74) {
        case 0:
            lbl_1_data_250 -= (REFRESH_RATE_F / 120);
            if (lbl_1_data_250 <= 45.0f) {
                lbl_1_data_250 = 45.0f;
                lbl_1_bss_74++;
            }
            arg1->unk24 = arg1->unk18;
            arg1->unk18.x = (700.0 * cosd(lbl_1_data_250));
            arg1->unk18.z = (700.0 * sind(lbl_1_data_250));
            var_f29 = (arg1->unk18.x - arg1->unk24.x);
            var_f28 = (arg1->unk18.z - arg1->unk24.z);
            var_f30 = atan2d(var_f29, var_f28);
            if (var_f30 < 0.0f) {
                var_f30 += 360.0f;
            }
            arg1->unk68 = var_f30;
            arg1->unk30.y = var_f30;
            return;
        case 1:
            arg1->unkE++;
            var_f31 = arg1->unkE / (REFRESH_RATE_F / 6.0f);
            if (var_f31 >= 1.0f) {
                var_f31 = 1.0f;
            }
            var_f30 = 225.0f;
            arg1->unk30.y = arg1->unk68 + (var_f31 * (var_f30 - arg1->unk68));
            arg1->unkC++;
            var_f31 = arg1->unkC / (5.0f * REFRESH_RATE_F / 6.0f);
            if (var_f31 >= 1.0f) {
                var_f31 = 1.0f;
                arg1->unkC = arg1->unkE = 0;
                arg1->unk68 = arg1->unk30.y;

                for (var_r30 = 0; var_r30 < 5; var_r30++) {
                    if (lbl_1_data_14[sp8[var_r30]] != 0) {
                        arg1->unk4A = arg1->unk60 = sp8[var_r30];
                        break;
                    }
                }
                lbl_1_bss_74++;
            }
            var_f29 = 700.0f + ((arg1->unk5C - 700.0f) * var_f31);
            arg1->unk18.x = (var_f29 * cos(M_PI / 4));
            arg1->unk18.z = (var_f29 * sin(M_PI / 4));
            var_f29 = 0.1f;
            var_f28 = 0.6f;
            if (var_f31 >= var_f29) {
                var_f31 -= var_f29;
                var_f31 *= (1.0f / var_f28);
                if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                arg1->unk18.y = 150.0f * var_f31;
            }
            break;
        case 2:
            lbl_1_data_250 += REFRESH_RATE_F / 60.0f;
            if (lbl_1_data_250 >= lbl_1_data_0[arg1->unk60]) {
                lbl_1_data_250 = lbl_1_data_0[arg1->unk60];
                lbl_1_bss_74++;
            }
            arg1->unk24 = arg1->unk18;
            arg1->unk18.x = (arg1->unk5C * cosd(lbl_1_data_250));
            arg1->unk18.z = (arg1->unk5C * sind(lbl_1_data_250));
            var_f29 = (arg1->unk18.x - arg1->unk24.x);
            var_f28 = (arg1->unk18.z - arg1->unk24.z);
            var_f30 = atan2d(var_f29, var_f28);
            if (var_f30 < 0.0f) {
                var_f30 += 360.0f;
            }
            arg1->unkC++;
            var_f31 = arg1->unkC / (REFRESH_RATE_F / 6.0f);
            if (var_f31 < 1.0f) {
                arg1->unk30.y = arg1->unk68 + (var_f31 * (var_f30 - arg1->unk68));
            }
            else {
                arg1->unk30.y = var_f30;
            }
            arg1->unk6C = arg1->unk30.y;
            return;
        case 3:
            arg1->unkE++;
            var_f31 = arg1->unkE / (REFRESH_RATE_F / 6.0f);
            if (var_f31 >= 1.0f) {
                var_f31 = 1.0f;
                arg1->unkC = arg1->unkE = 0;
                lbl_1_bss_74++;
                Hu3DMotionShiftSet(*arg0->model, *arg0->motion, 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
            }

            var_f30 = 90.0f - lbl_1_data_0[arg1->unk60];
            arg1->unk30.y = fn_1_927C(arg1->unk6C, var_f30, var_f31);
            return;
        case 4:
            if (++arg1->unkC > (REFRESH_RATE / 4)) {
                lbl_1_bss_74++;
            }
            break;
        case 5:
            if (lbl_1_data_1DA < 0) {
                fn_1_181C();
                lbl_1_data_1DA++;
                return;
            }
            if (lbl_1_data_1DA == 0) {
                if (fn_1_1890() == 0) {
                    lbl_1_data_1DA++;
                    return;
                }
            }
            else {
                lbl_1_bss_74 = 0;
                lbl_1_data_250 = 70.0f;
                arg1->unk48 = 0;
                arg1->unkC = arg1->unkE = 0;
                arg1->unk68 = lbl_1_data_0[arg1->unk60];
                arg1->unk6C = 0.0f;
                arg1->unk60 = 0;
                fn_1_D24C(arg1, arg1->unk30.y, arg1->unk30.y);
                fn_1_F4D4(arg1, 15, 3);
                fn_1_1768();
            }
            break;
    }
}

void fn_1_C1D4(omObjData *arg0, unkObjStruct *arg1)
{
    s16 sp12[5];
    s16 sp8[5];
    f32 var_f30;
    f32 var_f31;
    s16 var_r29;
    s16 var_r28;
    s16 var_r30;

    if (GWPlayerCfg[arg1->unk4].iscom != 0) {
        HuPadStkX[arg1->unk6] = 0;
        HuPadStkY[arg1->unk6] = 0;
        HuPadTrigR[arg1->unk6] = 0;
        HuPadBtn[arg1->unk6] = 0;
        switch (GWPlayerCfg[arg1->unk4].diff) {
            case 0:
                var_f31 = 0.3f;
                break;
            case 1:
                var_f31 = 0.3f;
                break;
            case 2:
                var_f31 = 0.3f;
                break;
            case 3:
                var_f31 = 0.3f;
                break;
        }

        var_f31 += (0.1f * lbl_1_bss_70);
        for (var_r30 = 0, var_r29 = 0; var_r30 < 5; var_r30++) {
            if (lbl_1_data_14[var_r30] != 0) {
                sp8[var_r29++] = var_r30;
            }
        }
        var_r29--;
        if (arg1->unk50 == -1) {
            if (arg1->unk4C < var_f31) {
                arg1->unk50 = fn_1_4E54(-1);
            }
            else {
                for (var_r30 = 0, var_r28 = 0; var_r30 < 5; var_r30++) {
                    if ((var_r30 != fn_1_4E54(-1)) && (lbl_1_data_14[var_r30] != 0)) {
                        sp12[var_r28++] = var_r30;
                    }
                }
                var_r28--;
                var_r30 = (((rand8() << 8) | rand8()) % (s16)(var_r28 + 1));
                arg1->unk50 = sp12[var_r30];
            }
            var_r30 = (((rand8() << 8) | rand8()) % (s16)(var_r29 + 1));
            arg1->unk52 = sp8[var_r30];
        }
        if (arg1->unk54 == 0) {
            var_f30 = ABS(arg1->unk68 - lbl_1_data_0[arg1->unk50]);
            if (var_f30 < 5.0f) {
                HuPadTrigR[arg1->unk6] = 0x96;
                HuPadBtn[arg1->unk6] = 0x20;
                return;
            }
            if (arg1->unk68 < lbl_1_data_0[arg1->unk50]) {
                HuPadStkX[arg1->unk6] = -0x2D;
                return;
            }
            if (arg1->unk68 > lbl_1_data_0[arg1->unk50]) {
                HuPadStkX[arg1->unk6] = 0x2D;
            }
        }
        else {
            var_f30 = ABS(arg1->unk68 - lbl_1_data_0[arg1->unk52]);
            if (var_f30 < 5.0f) {
                if (arg1->unk5A != 0) {
                    arg1->unk56++;
                    var_f31 = arg1->unk56 / (2.0f * REFRESH_RATE_F / 3.0f);
                    if (var_f31 > 1.0f) {
                        var_f31 = 1.0f;
                        arg1->unk5A = 0;
                        arg1->unk54--;
                        var_r30 = (((rand8() << 8) | rand8()) % (s16)(var_r29 + 1));
                        arg1->unk52 = sp8[var_r30];
                    }
                    HuPadTrigR[arg1->unk6] = (u8)(arg1->unk58 * var_f31);
                    return;
                }
                if ((((rand8() << 8) | rand8()) % 101) < 0x32) {
                    arg1->unk56 = 0;
                    arg1->unk58 = ((((rand8() << 8) | rand8()) % 81) + 0x32);
                    arg1->unk5A = 1;
                    return;
                }
                arg1->unk54--;
                var_r30 = (((rand8() << 8) | rand8()) % (s16)(var_r29 + 1));
                arg1->unk52 = sp8[var_r30];
                return;
            }
            if (arg1->unk68 < lbl_1_data_0[arg1->unk52]) {
                HuPadStkX[arg1->unk6] = -0x2D;
                return;
            }
            if (arg1->unk68 > lbl_1_data_0[arg1->unk52]) {
                HuPadStkX[arg1->unk6] = 0x2D;
            }
        }
    }
}

void fn_1_C944(omObjData *arg0, unkObjStruct *arg1)
{
    s16 sp8;
    f32 var_f26;
    f32 var_f25;
    f32 var_f28;
    f32 temp_f27;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s16 var_r30;
    s16 var_r29;

    if (fn_1_17CC() < -1) {
        fn_1_1708();
        HuPadStkX[arg1->unk6] = 0;
        HuPadStkY[arg1->unk6] = 0;
        HuPadTrigR[arg1->unk6] = 0x96;
        HuPadBtn[arg1->unk6] = 0x20;
    }
    else {
        var_r29 = HuPadStkX[arg1->unk6];
        sp8 = HuPadStkY[arg1->unk6];
    }
    if ((arg1->unk48 & 8) == 0) {
        var_r30 = -1;
        if (ABS(var_r29) < 7) {
            var_r30 = fn_1_CFAC(arg1, 0);
        }
        else {
            if (var_r29 > 0) {
                arg1->unk48 = arg1->unk48 & 0xFFFFFFFD;
                arg1->unk48 = arg1->unk48 | 1;
            }
            else {
                arg1->unk48 = arg1->unk48 & 0xFFFFFFFE;
                arg1->unk48 = arg1->unk48 | 2;
            }
            var_r30 = fn_1_CFAC(arg1, 1);
            if (var_r30 >= 0x64) {
                var_r30 -= 0x64;
                arg1->unk4A = var_r30;
                arg1->unk48 = arg1->unk48 & 0xFFFFFFFC;
            }
        }
        if ((arg1->unk48 & 1) != 0) {
            arg1->unk68 -= REFRESH_RATE_F / 60.0f;
            if ((var_r30 != -1) && (lbl_1_data_0[var_r30] > arg1->unk68)) {
                arg1->unk68 = lbl_1_data_0[var_r30];
                arg1->unk4A = var_r30;
                arg1->unk48 = arg1->unk48 & 0xFFFFFFFE;
            }
        }
        else if ((arg1->unk48 & 2) != 0) {
            arg1->unk68 += REFRESH_RATE_F / 60.0f;
            if ((var_r30 != -1) && (lbl_1_data_0[var_r30] < arg1->unk68)) {
                arg1->unk68 = lbl_1_data_0[var_r30];
                arg1->unk4A = var_r30;
                arg1->unk48 = arg1->unk48 & 0xFFFFFFFD;
            }
        }
        arg1->unk24 = arg1->unk18;
        arg1->unk18.x = (arg1->unk5C * cosd(arg1->unk68));
        arg1->unk18.z = (arg1->unk5C * sind(arg1->unk68));
        if ((arg1->unk48 & 3) != 0) {
            arg1->unk48 = arg1->unk48 & ~4;
            var_f26 = (arg1->unk18.x - arg1->unk24.x);
            var_f25 = (arg1->unk18.z - arg1->unk24.z);
            var_f29 = atan2d(var_f26, var_f25);
            if (var_f29 < 0.0f) {
                var_f29 += 360.0f;
            }
            fn_1_D24C(arg1, arg1->unk30.y, var_f29);
        }
        else {
            arg1->unk48 |= 4;
            var_f29 = 90.0f - lbl_1_data_0[arg1->unk4A];
            fn_1_D24C(arg1, arg1->unk30.y, var_f29);
        }
        arg1->unkC++;
        var_f28 = (f32)arg1->unkC / arg1->unkE;
        if (arg1->unkC >= arg1->unkE) {
            arg1->unkC = arg1->unkE;
            var_f28 = 1.0f;
            if ((arg1->unk48 & 4) != 0) {
                fn_1_ED88(arg0, 0, HU3D_MOTATTR_LOOP);
            }
            else {
                fn_1_ED88(arg0, 2, HU3D_MOTATTR_LOOP);
            }
        }
        else {
            fn_1_ED88(arg0, 2, HU3D_MOTATTR_LOOP);
        }
        if ((arg1->unk48 & 4) != 0) {
            arg1->unk30.y = fn_1_927C(arg1->unk6C, arg1->unk70, var_f28);
            return;
        }
        var_f31 = arg1->unk6C;
        temp_f27 = arg1->unk70;
        if ((arg1->unk48 & 1) != 0) {
            if (var_f31 > temp_f27) {
                var_f31 -= 360.0f;
            }
        }
        else if (((arg1->unk48 & 2) != 0) && (var_f31 < temp_f27)) {
            var_f31 += 360.0f;
        }
        var_f30 = var_f31 + (var_f28 * (temp_f27 - var_f31));
        if (var_f30 < 0.0f) {
            var_f30 += 360.0f;
        }
        else {
            if (var_f30 >= 360.0f) {
                var_f30 -= 360.0f;
            }
        }
        arg1->unk30.y = var_f30;
    }
}

s16 fn_1_CFAC(unkObjStruct *arg0, u8 arg1)
{
    f32 var_f31;
    s16 var_r30;
    s16 var_r31;

    var_f31 = 999.0f;
    var_r30 = -1;
    if ((arg0->unk48 & 1) != 0) {
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            if (lbl_1_data_14[var_r31] != 0) {
                if (arg1 == 0) {
                    if (lbl_1_data_0[var_r31] > arg0->unk68) {
                        continue;
                    }
                }
                else if (lbl_1_data_0[var_r31] >= arg0->unk68) {
                    continue;
                }
                if (var_f31 > (arg0->unk68 - lbl_1_data_0[var_r31])) {
                    var_r30 = var_r31;
                    var_f31 = arg0->unk68 - lbl_1_data_0[var_r31];
                }
            }
        }
    }
    else if ((arg0->unk48 & 2) != 0) {
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            if (lbl_1_data_14[var_r31] != 0) {
                if (arg1 == 0) {
                    if (lbl_1_data_0[var_r31] < arg0->unk68) {
                        continue;
                    }
                }
                else if (lbl_1_data_0[var_r31] <= arg0->unk68) {
                    continue;
                }
                if (var_f31 > (lbl_1_data_0[var_r31] - arg0->unk68)) {
                    var_r30 = var_r31;
                    var_f31 = lbl_1_data_0[var_r31] - arg0->unk68;
                }
            }
        }
    }
    if ((var_r30 == -1) && (arg1 != 0)) {
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            if ((lbl_1_data_14[var_r31] != 0) && (arg0->unk68 == lbl_1_data_0[var_r31])) {
                var_r30 = var_r31 + 0x64;
            }
        }
    }
    return var_r30;
}

void fn_1_D24C(unkObjStruct *arg0, f32 arg1, f32 arg2)
{
    f32 var_f31;
    f32 var_f28;

    var_f28 = REFRESH_RATE_F / 6.0f;
    arg0->unk6C = arg1;
    arg0->unk70 = arg2;
    var_f31 = ABS(arg1 - arg2);
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f31 = ABS(var_f31);
    arg0->unkC = 0;
    arg0->unkE = ((var_f28 / 90.0f) * var_f31);
}

void fn_1_D34C(omObjData *arg0, unkObjStruct *arg1)
{
    ModelData *temp_r30;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f31;
    f32 var_f26;

    temp_r30 = &Hu3DData[arg0->model[0]];
    temp_f29 = 7.0f;
    temp_f28 = Hu3DMotionMaxTimeGet(arg0->model[0]) - temp_f29;
    temp_f30 = HuPadTrigR[arg1->unk6];
    if ((temp_r30->unk_0C == -1) && (temp_r30->unk_08 == arg0->motion[0]) && ((arg1->unk48 & 8) == 0) && (temp_f30 > 10.0f)) {
        arg1->unk48 |= 8;
        Hu3DMotionShiftSet(arg0->model[0], arg0->motion[3], 0.0f, 7.0f, HU3D_MOTATTR_NONE);
    }
    if ((arg1->unk48 & 8) != 0) {
        if (temp_f30 <= 10.0f) {
            fn_1_4E00(arg1->unk4A, -1.0f);
            arg1->unk48 &= ~8;
            temp_r30->unk_68 = 1.0f;
            Hu3DMotionShiftSet(arg0->model[0], arg0->motion[0], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
        }
        else if (temp_f30 > 10.0f) {
            if ((HuPadBtn[arg1->unk6] & 0x20) != 0) {
                arg1->unk60 = 0;
                arg1->unk68 = temp_f30;
                arg1->unk6C = 0.0f;
                arg1->unk48 = 0;
                lbl_1_data_14[arg1->unk4A] = 0;
                if (fn_1_17CC() < (4.5f * REFRESH_RATE)) {
                    fn_1_1708();
                }
                fn_1_F4D4(arg1, 15, 4);
            }
            if (temp_r30->unk_0C == -1) {
                temp_r30->unk_68 = 0.0f;
                var_f31 = 0.006666667f * (temp_f30 - 10.0f);
                if (var_f31 > 0.8f) {
                    var_f31 = 0.8f;
                }
                var_f31 = temp_f29 + (var_f31 * temp_f28);
                var_f26 = ABS(temp_r30->unk_64 - var_f31);
                if (var_f26 < 1.0f) {
                    temp_r30->unk_64 = var_f31;
                }
                if (temp_r30->unk_64 < var_f31) {
                    temp_r30->unk_64 += 1.0f;
                }
                else if (temp_r30->unk_64 > var_f31) {
                    temp_r30->unk_64 -= 1.0f;
                }
                var_f31 = (temp_r30->unk_64 - temp_f29) / temp_f28;
                fn_1_4E00(arg1->unk4A, var_f31);
            }
        }
        arg1->unk18.x = (410.0 * cosd(lbl_1_data_0[arg1->unk4A]));
        arg1->unk18.z = (410.0 * sind(lbl_1_data_0[arg1->unk4A]));
    }
}

void fn_1_D7F8(omObjData *arg0, unkObjStruct *arg1)
{
    ModelData *temp_r29;
    f32 temp_f28;
    f32 temp_f29;
    f32 var_f26;
    f32 var_f30;
    f32 var_f31;

    temp_r29 = &Hu3DData[arg0->model[0]];
    temp_f29 = 7.0f;
    temp_f28 = Hu3DMotionMaxTimeGet(arg0->model[0]) - temp_f29;
    switch (arg1->unk60) {
        case 0:
            if (temp_r29->unk_0C == -1) {
                arg1->unk68 += 40.0f;
                temp_r29->unk_68 = 0.0f;
                var_f31 = 0.006666667f * (arg1->unk68 - 10.0f);
                if (var_f31 > 0.8f) {
                    var_f31 = 0.8f;
                }
                var_f30 = 0.01f * (arg1->unk68 - 130.0f);
                if (var_f30 > 0.19999999f) {
                    var_f30 = 0.19999999f;
                }
                else if (var_f30 < 0.0f) {
                    var_f30 = 0.0f;
                }
                var_f31 += var_f30;
                var_f31 = var_f30 = temp_f29 + (var_f31 * temp_f28);
                var_f26 = ABS(temp_r29->unk_64 - var_f31);
                if (var_f26 < 1.0f) {
                    temp_r29->unk_64 = var_f31;
                }
                if (temp_r29->unk_64 < var_f31) {
                    temp_r29->unk_64 += 3.0f;
                }
                else if (temp_r29->unk_64 > var_f31) {
                    temp_r29->unk_64 -= 3.0f;
                }
                var_f31 = (temp_r29->unk_64 - temp_f29) / temp_f28;
                fn_1_4E00(arg1->unk4A, var_f31);
                arg1->unk18.x = (410.0 * cosd(lbl_1_data_0[arg1->unk4A]));
                arg1->unk18.z = (410.0 * sind(lbl_1_data_0[arg1->unk4A]));
                if (arg1->unk68 >= 150.0f) {
                    arg1->unk68 = 150.0f;
                    if (temp_r29->unk_64 == var_f30) {
                        arg1->unkC = 0;
                        arg1->unk68 = arg1->unk30.y;
                        arg1->unk6C = 180.0f + arg1->unk30.y;
                        if (arg1->unk6C >= 360.0f) {
                            arg1->unk6C -= 360.0f;
                        }
                        arg1->unk60++;
                        HuAudFXPlay(0x70B);
                    }
                }
            }
            break;
        case 1:
            if (++arg1->unkC > (REFRESH_RATE / 6)) {
                arg1->unkC = 0;
                Hu3DMotionSpeedSet(arg0->model[0], 2.0f);
                if ((arg1->unk6C - arg1->unk68) > 0.0f) {
                    Hu3DMotionShiftSet(arg0->model[0], arg0->motion[7], 64.0f, 7.0f, HU3D_MOTATTR_NONE);
                }
                else {
                    Hu3DMotionShiftSet(arg0->model[0], arg0->motion[7], 4.0f, 7.0f, HU3D_MOTATTR_NONE);
                }
                Hu3DMotionShiftSpeedSet(arg0->model[0], 2.0f);
                arg1->unk60++;
            }
            break;
        case 2:
            arg1->unkC++;
            var_f31 = arg1->unkC / (0.5f * REFRESH_RATE_F);
            arg1->unk18.x = ((410.0f + (var_f31 * (arg1->unk5C - 410.0f))) * cosd(lbl_1_data_0[arg1->unk4A]));
            arg1->unk18.z = ((410.0f + (var_f31 * (arg1->unk5C - 410.0f))) * sind(lbl_1_data_0[arg1->unk4A]));
            if (var_f31 >= 1.0f) {
                arg1->unkC = 0;
                var_f31 = 1.0f;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[0], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
                arg1->unk60++;
            }
            else if (((arg1->unk6C - arg1->unk68) < 0.0f) && (Hu3DMotionShiftIDGet(arg0->model[0]) < 0)) {
                if (Hu3DMotionTimeGet(arg0->model[0]) >= 60.0f) {
                    Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
                }
            }
            arg1->unk30.y = fn_1_927C(arg1->unk68, arg1->unk6C, var_f31);
            break;
        case 3:
            if (++arg1->unkC > (s32)REFRESH_RATE_F) {
                if (fn_1_4E54(arg1->unk4A) == 0) {
                    fn_1_4EEC(7U, 3U);
                }
                else {
                    fn_1_4EEC(7U, 4U);
                }
                arg1->unkC = 0;
                arg1->unk60++;
            }
            break;
        case 4:
            if (fn_1_4EA8(0x100U) != 0) {
                fn_1_4EEC(0x100U, 0U);
                if (fn_1_4E54(arg1->unk4A) == 0) {
                    fn_1_F4D4(arg1, 15, 5);
                }
                else {
                    fn_1_F4D4(arg1, 15, 6);
                }
                arg1->unkC = arg1->unkE = 0;
                arg1->unk60 = arg1->unk62 = 0;
                arg1->unk68 = arg1->unk6C = 0.0f;
            }
            break;
    }
    if (fn_1_17F4() >= 0) {
        if (fn_1_17CC() < (4.5f * REFRESH_RATE)) {
            fn_1_1708();
            return;
        }
        fn_1_16D8();
    }
}

void fn_1_E034(omObjData *arg0, unkObjStruct *arg1)
{
    ModelData *temp_r27;
    f32 var_f28;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s16 var_r28;
    s16 var_r29;

    temp_r27 = &Hu3DData[arg0->model[0]];
    switch (arg1->unk60) {
        case 0:
            lbl_1_bss_84 = lbl_1_data_0[arg1->unk4A];
#if VERSION_NTSC
            Hu3DMotionShiftSet(arg0->model[0], arg0->motion[4], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
#else
            Hu3DMotionSet(arg0->model[0], arg0->motion[4]);
#endif
            HuAudCharVoicePlay(arg1->unk8, 0x125);
            arg1->unk60++;
            break;
        case 1:
            if (temp_r27->unk_64 >= (Hu3DMotionMaxTimeGet(arg0->model[0]) - 1.0f)) {
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[2], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
                arg1->unkC = arg1->unkE = 0;
                arg1->unk68 = arg1->unk30.y;

                for (var_r29 = 0, var_r28 = -1; var_r29 < 5; var_r29++) {
                    if (lbl_1_data_14[var_r29] != 0) {
                        var_r28++;
                    }
                }
                if (var_r28 == 0) {
                    lbl_1_bss_70++;
                    fn_1_4EEC(0x18, 0x18);
                    HuAudFXPlay(0x70E);
                }
                arg1->unk60++;
            }
            break;
        case 2:
            lbl_1_bss_84 += REFRESH_RATE_F / 60.0f;
            if (lbl_1_bss_84 >= 135.0f) {
                lbl_1_bss_84 = 135.0f;
                arg1->unkE = arg1->unk10 = 0;
                fn_1_F228();
                arg1->unk60++;
            }
            arg1->unk24 = arg1->unk18;
            arg1->unk18.x = (arg1->unk5C * cosd(lbl_1_bss_84));
            arg1->unk18.z = (arg1->unk5C * sind(lbl_1_bss_84));
            var_f29 = (arg1->unk18.x - arg1->unk24.x);
            var_f28 = (arg1->unk18.z - arg1->unk24.z);
            var_f30 = atan2d(var_f29, var_f28);
            if (var_f30 < 0.0f) {
                var_f30 += 360.0f;
            }
            arg1->unkC++;
            var_f31 = arg1->unkC / (REFRESH_RATE_F / 6.0f);
            if (var_f31 >= 1.0f) {
                var_f31 = 1.0f;
            }
            arg1->unk30.y = fn_1_927C(arg1->unk68, var_f30, var_f31);
            arg1->unk6C = arg1->unk30.y;
            break;
        case 3:
            arg1->unkE++;
            var_f31 = arg1->unkE / (REFRESH_RATE_F / 6.0f);
            if (var_f31 >= 1.0f) {
                var_f31 = 1.0f;
            }
            var_f30 = 315.0f;
            arg1->unk30.y = arg1->unk6C + (var_f31 * (var_f30 - arg1->unk6C));
            arg1->unk10++;
            var_f31 = arg1->unk10 / (5.0f * REFRESH_RATE_F / 6.0f);
            if (var_f31 >= 1.0f) {
                var_f31 = 1.0f;
                arg1->unkC = arg1->unkE = arg1->unk10 = 0;
                arg1->unk68 = arg1->unk30.y;
                arg1->unk60++;
            }
            var_f29 = arg1->unk5C + ((700.0f - arg1->unk5C) * var_f31);
            arg1->unk18.x = var_f29 * cosd(135);
            arg1->unk18.z = var_f29 * sind(135);
            var_f29 = 0.3f;
            var_f28 = 0.6f;
            if (var_f31 >= var_f29) {
                var_f31 -= var_f29;
                var_f31 *= (1.0f / var_f28);
                if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                arg1->unk18.y = 150.0f * (1.0f - var_f31);
            }
            break;
        case 4:
            lbl_1_bss_84 -= REFRESH_RATE_F / 120;
            if (lbl_1_bss_84 <= 110.0f) {
                lbl_1_bss_84 = 110.0f;
                arg1->unk60 = 0;
                arg1->unkC = 0;
                arg1->unkE = (3 - lbl_1_data_1D8) * (s32)(0.5f * REFRESH_RATE_F);
                arg1->unk14 = 0;
                arg1->unk3C.y = 90.0f;
                fn_1_F4D4(arg1, 15, 1);
            }
            arg1->unk24 = arg1->unk18;
            arg1->unk18.x = (700.0 * cosd(lbl_1_bss_84));
            arg1->unk18.z = (700.0 * sind(lbl_1_bss_84));
            var_f29 = (arg1->unk18.x - arg1->unk24.x);
            var_f28 = (arg1->unk18.z - arg1->unk24.z);
            var_f30 = atan2d(var_f29, var_f28);
            if (var_f30 < 0.0f) {
                var_f30 += 360.0f;
            }
            arg1->unk10++;
            var_f31 = arg1->unk10 / (REFRESH_RATE_F / 6.0f);
            if (var_f31 >= 1.0f) {
                var_f31 = 1.0f;
            }
            arg1->unk30.y = fn_1_927C(arg1->unk68, var_f30, var_f31);
            break;
    }
}

u8 fn_1_E8AC(omObjData *arg0, unkObjStruct *arg1)
{
    ModelData *temp_r29;
    f32 var_f31;
    s32 temp_r28;
    s16 temp_r27;

    temp_r29 = &Hu3DData[arg0->model[0]];
    switch (arg1->unk60) {
        case 0:
            lbl_1_bss_70 = 0;
            Hu3DMotionShiftSet(arg0->model[0], arg0->motion[6], 0.0f, 7.0f, HU3D_MOTATTR_NONE);
            HuAudCharVoicePlay(arg1->unk8, 0x12E);
            arg1->unk60++;
            break;
        case 1:
            if (fn_1_4EA8(7U) == 5) {
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[0], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
                arg1->unkC = 0;
                arg1->unk68 = arg1->unk30.y;
                var_f31 = lbl_1_data_0[arg1->unk4A];
                lbl_1_bss_78 = arg1->unk18;
                if ((arg1->unk4A == 4) || (arg1->unk4A == 3)) {
                    arg1->unk24.x = (840.0000610351563 * cosd(var_f31));
                    arg1->unk24.y = 0.0f;
                    arg1->unk24.z = (840.0000610351563 * sind(var_f31));
                }
                else {
                    arg1->unk24.x = (1050.0 * cosd(var_f31));
                    arg1->unk24.y = 0.0f;
                    arg1->unk24.z = (1050.0 * sind(var_f31));
                }
                arg1->unk30.y = 0.0f;
                MTXRotRad(temp_r29->unk_F0, 0x59, 0.017453292f * arg1->unk68);
                arg1->unk60++;
                if (lbl_1_data_1D8 == 0) {
                    fn_1_18E0();
                }
            }
            break;
        case 2:
            arg1->unkC++;
            arg1->unk68 += 40.0f;
            var_f31 = arg1->unkC / (1.5f * REFRESH_RATE_F);
            if (var_f31 >= 1.0f) {
                var_f31 = 1.0f;
                arg1->unk60++;
            }
            arg1->unk18.x = lbl_1_bss_78.x + (var_f31 * (arg1->unk24.x - lbl_1_bss_78.x));
            arg1->unk18.y = fn_1_93D0(lbl_1_bss_78.y, 1400.0f + lbl_1_bss_78.y, 0.0f, var_f31);
            arg1->unk18.z = lbl_1_bss_78.z + (var_f31 * (arg1->unk24.z - lbl_1_bss_78.x));
            arg1->unk30.x = 180.0f * var_f31;
            MTXRotRad(temp_r29->unk_F0, 0x59, 0.017453292f * arg1->unk68);
            break;
        case 3:
            fn_1_F4D4(arg1, 15, 8);
            Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
            temp_r27 = lbl_1_data_1D8 + 1;
            temp_r28 = arg1->unk4;
            GWPlayerCoinWinSet(temp_r28, temp_r27);
            lbl_1_data_1D8 -= 1;
            return 1;
    }
    return 0;
}

s32 fn_1_ED88(omObjData *arg0, s16 arg1, u32 arg2)
{
    s16 var_r28;
    s16 var_r29;

    var_r28 = Hu3DData[arg0->model[0]].unk_08;
    var_r29 = Hu3DData[arg0->model[0]].unk_0C;
    if ((var_r29 != arg0->motion[arg1]) && (var_r28 != arg0->motion[arg1])) {
        Hu3DMotionShiftSet(arg0->model[0], arg0->motion[arg1], 0.0f, 7.0f, arg2);
    }
}

void fn_1_EE78(void)
{
    s16 var_r31;
    unkObjStruct *var_r30;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = (unkObjStruct *)lbl_1_bss_C0[var_r31]->data;
        if (fn_1_F4C0(var_r30, 15) == 8) {
            Hu3DMotionShiftSet(lbl_1_bss_C0[var_r31]->model[0], lbl_1_bss_C0[var_r31]->motion[6], 0.0f, 7.0f, HU3D_MOTATTR_NONE);
        }
    }
}

void fn_1_EF50(void)
{
    unkObjStruct *var_r30;
    s16 var_r28;
    s16 var_r29;
    s16 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = (unkObjStruct *)lbl_1_bss_C0[var_r31]->data;
        if (fn_1_F4C0(var_r30, 15) == 8) {
            var_r28 = Hu3DData[lbl_1_bss_C0[var_r31]->model[0]].unk_08;
            var_r29 = Hu3DData[lbl_1_bss_C0[var_r31]->model[0]].unk_0C;
            if ((var_r29 != lbl_1_bss_C0[var_r31]->motion[0]) && (var_r28 != lbl_1_bss_C0[var_r31]->motion[0])) {
                Hu3DMotionShiftSet(lbl_1_bss_C0[var_r31]->model[0], lbl_1_bss_C0[var_r31]->motion[0], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
            }
        }
    }
}

s16 fn_1_F0FC(void)
{
    s16 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_B8[var_r31] != -1) {
            return lbl_1_bss_B8[var_r31];
        }
    }
    return 0;
}

void fn_1_F168(void)
{
    omObjData *temp_r31;
    s16 var_r30;
    unkObjStruct *var_r29;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        temp_r31 = lbl_1_bss_C0[lbl_1_bss_B8[var_r30]];
        var_r29 = (unkObjStruct *)temp_r31->data;
        fn_1_F4D4(var_r29, 15, 1);
        Hu3DMotionShiftSet(temp_r31->model[0], temp_r31->motion[2], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
    }
}

void fn_1_F228(void)
{
    omObjData *temp_r30;
    s16 var_r29;
    s32 var_r28;
    unkObjStruct *temp_r31;

    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (lbl_1_bss_B8[var_r29] != -1) {
            temp_r30 = lbl_1_bss_C0[lbl_1_bss_B8[var_r29]];
            temp_r31 = (unkObjStruct *)temp_r30->data;
            if (temp_r31->unkA == 0) {
                switch (GWPlayerCfg[temp_r31->unk4].diff) {
                    case 0:
                        var_r28 = 3;
                        break;
                    case 1:
                        var_r28 = 2;
                        break;
                    case 2:
                        var_r28 = 1;
                        break;
                    case 3:
                        var_r28 = 0;
                        break;
                }
                temp_r31->unk4C = ((((rand8() << 8) | rand8()) % 256) / 255.0f);
                temp_r31->unk54 = (((rand8() << 8) | rand8()) % (s16)(var_r28 + 1));
                temp_r31->unk50 = -1;
                temp_r31->unk56 = temp_r31->unk5A = 0;
                temp_r31->unkA = -1;
                temp_r31->unkC = temp_r31->unkE = 0;
                fn_1_F4D4(temp_r31, 15, 2);
            }
            else if (temp_r31->unkA == -1) {
                temp_r31->unkA = lbl_1_data_1D8;
            }
            else {
                temp_r31->unkA--;
                temp_r31->unk24 = temp_r31->unk18;
                temp_r31->unkC = 0;
                temp_r31->unkE = (s32)(0.5f * REFRESH_RATE_F);
                temp_r31->unk14 = 0;
                fn_1_F4D4(temp_r31, 15, 1);
            }
            if (temp_r30->motion[2] != Hu3DData[temp_r30->model[0]].unk_08) {
                Hu3DMotionShiftSet(temp_r30->model[0], temp_r30->motion[2], 0.0f, 7.0f, HU3D_MOTATTR_LOOP);
            }
        }
    }
}

u16 fn_1_F4C0(unkObjStruct *arg0, u16 arg1)
{
    return arg0->unk0 & arg1;
}

void fn_1_F4D4(unkObjStruct *arg0, u16 arg1, u16 arg2)
{
    arg0->unk0 &= ~arg1;
    arg0->unk0 |= arg2;
}

s32 fn_1_F4FC(s32 arg0)
{
    return lbl_1_bss_B8[arg0];
}
