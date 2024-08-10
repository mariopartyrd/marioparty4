
#include "ext_math.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/minigame_seq.h"
#include "game/wipe.h"
#include "rel_sqrt_consts.h"

#include "REL/m406Dll.h"

typedef struct UnkM417Data0Struct {
    float unk_00;
    float unk_04;
    float unk_08;
    float unk0C;
    float unk10;
    float unk14;
    float unk18;
    float unk_1C;
    float unk_20;
    float unk_24;
    float unk_28;
    float unk_2C;
    float unk_30;
    float unk_34;
    float unk_38; // it's the same structure twice, rot, center etc.
    float unk_3C;
    float unk_40;
    float unk_44;
    float unk_48;
    float unk_4C;
    float unk_50;
    float unk_54;
    float unk_58;
    float unk_5C;
    float unk_60;
    float unk_64;
    float unk_68;
    float unk_6C;
    float unk_70;
    float unk_74;
    float unk_78;
    float unk_7C;
    float unk_80;
    float unk_84;
    float unk_88;
} UnkM417Data0Struct; /* size = unknown */

void fn_1_110C(omObjData *object);
void fn_1_1168(omObjData *object);
void fn_1_1340(void);
void fn_1_151C(omObjData *object);
void fn_1_15D0(float arg8);
void fn_1_183C(float arg8);
float fn_1_1F10(float arg9, float argA, float argB);
void fn_1_3B8(omObjData *object);
void fn_1_40C(omObjData *object);

UnkM417Data0Struct lbl_1_data_0 = {
    330.0f,
    105.0f,
    0.0f,
    0.0f,
    100.0f,
    0.0f,
    1650.0f,
    91.0f,
    124.0f,
    0.0f,
    0.0f,
    -35440.0f,
    -60022.0f,
    1226.0f,
    0.0f,
    180.0f,
    0.0f,
    0.0f,
    -1300.0f,
    -2000.0f,
    1000.0f,
    -5.0f,
    0.0f,
    0.0f,
    31.0f,
    75.0f,
    -250.0f,
    675.0f,
    111.0f,
    164.0f,
    0.0f,
    0.0f,
    -35440.0f,
    -60022.0f,
    1226.0f,
};

Process *lbl_1_bss_2C;
omObjData *lbl_1_bss_28;
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
omObjData *lbl_1_bss_4;
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    Vec sp14;
    Vec sp8;

    Process *var_r31;

    OSReport("******* M426ObjectSetup *********\n");
    var_r31 = omInitObjMan(50, 8192);
    lbl_1_bss_2C = var_r31;
    omGameSysInit(var_r31);
    fn_1_1340();
    HuAudSndGrpSet(0x1F);
    sp14.x = Center.x + (CZoom * (sind(CRot.y) * cosd(CRot.x)));
    sp14.y = Center.y + (CZoom * -sind(CRot.x));
    sp14.z = Center.z + (CZoom * (cosd(CRot.y) * cosd(CRot.x)));
    VECSubtract(&Center, &sp14, &sp8);
    VECNormalize(&sp8, &sp8);
    HuAudFXListnerSetEX(&sp14, &sp8, 100000.0f, 4166.6665f, 0.0f, 300.0f, 300.0f);
    Hu3DLightAllKill();
    Hu3DLighInit();
    lbl_1_bss_28 = omAddObjEx(var_r31, 255, 2, 0, -1, fn_1_3B8);
    lbl_1_bss_24 = lbl_1_bss_20 = -1;
    lbl_1_bss_1C = 0;
    lbl_1_bss_18 = 0;
    lbl_1_bss_10 = -1;
    lbl_1_bss_C = -1;
    lbl_1_bss_8 = 0;
    WipeCreate(1, 0, 60);
    lbl_1_bss_8 = 0;
}

void fn_1_3B8(omObjData *object)
{
    fn_1_2308(lbl_1_bss_2C);
    fn_1_D65C(lbl_1_bss_2C);
    object->func = fn_1_40C;
}

void fn_1_40C(omObjData *object)
{
    Vec sp14;
    Vec sp8;

    float var_f31;

    u8 var_r31;

    switch (lbl_1_bss_1C) {
        case 0:
            if (!WipeStatGet()) {
                lbl_1_bss_1C = 1;
                lbl_1_bss_18 = 0;
            }
            break;
        case 1:
            lbl_1_bss_18++;
            if (lbl_1_bss_18 >= 48.0f) {
                fn_1_696C(30.000002f);
            }
            break;
        case 2:
            lbl_1_bss_18++;
            var_f31 = lbl_1_bss_18 / 45.0f;
            fn_1_15D0(var_f31);
            if (lbl_1_bss_18 >= 45.0f) {
                lbl_1_bss_24 = MGSeqCreate(3, 0);
                lbl_1_bss_1C = 3;
                lbl_1_bss_18 = 0;
            }
            break;
        case 3:
            if (lbl_1_bss_24 != -1) {
                var_r31 = MGSeqStatGet(lbl_1_bss_24);
                if (var_r31 & 16 && lbl_1_bss_C == -1) {
                    lbl_1_bss_C = HuAudSeqPlay(74);
                }
            } else {
                var_r31 = 0;
            }
            if (lbl_1_bss_24 == -1 || !var_r31) {
                lbl_1_bss_24 = -1;
                lbl_1_bss_1C = 4;
                lbl_1_bss_18 = 0;
            }
            break;
        case 4:
            if (lbl_1_bss_10 != -1) {
                lbl_1_bss_24 = MGSeqCreate(3, 1);
                HuAudFXAllStop();
                if (lbl_1_bss_C != -1) {
                    HuAudSeqFadeOut(lbl_1_bss_C, 100);
                }
                if (lbl_1_bss_10 != 99) {
                    fn_1_B25C();
                    fn_1_B104(1.0f);
                    fn_1_6B5C();
                    fn_1_183C(0.0f);
                    Hu3DBGColorSet(0x40, 0x40, 0xFF);
                    lbl_1_bss_1C = 5;
                    lbl_1_bss_18 = 0;
                } else {
                    WipeCreate(2, 0, 30);
                    WipeColorSet(0xFF, 0xFF, 0xFF);
                    lbl_1_bss_8 = 1;
                    lbl_1_bss_1C = 9;
                    lbl_1_bss_18 = 0;
                    lbl_1_bss_14 = 0;
                }
            }
            break;
        case 5:
            lbl_1_bss_14++;
            var_f31 = lbl_1_bss_14 / 90.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            fn_1_183C(var_f31);
            Hu3DBGColorSet(0x40, 0x40, 0xFF);
            break;
        case 6:
            lbl_1_bss_14++;
            var_f31 = lbl_1_bss_14 / 90.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            fn_1_183C(var_f31);
            WipeCreate(2, 0, 30);
            WipeColorSet(0xFF, 0xFF, 0xFF);
            lbl_1_bss_8 = 1;
            lbl_1_bss_1C = 7;
            lbl_1_bss_18 = 0;
            break;
        case 7:
            lbl_1_bss_14++;
            var_f31 = lbl_1_bss_14 / 90.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            fn_1_183C(var_f31);
            if (!WipeStatGet() && (lbl_1_bss_24 == -1 || !MGSeqStatGet(lbl_1_bss_24))) {
                lbl_1_bss_24 = -1;
                WipeCreate(1, 0, 30);
                WipeColorSet(0xFF, 0xFF, 0xFF);
                lbl_1_bss_8 = 0;
                CRot.x = lbl_1_data_0.unk_54;
                CRot.y = lbl_1_data_0.unk_58;
                CRot.z = lbl_1_data_0.unk_5C;
                Center.x = lbl_1_data_0.unk_60;
                Center.y = lbl_1_data_0.unk_64;
                Center.z = lbl_1_data_0.unk_68;
                CZoom = lbl_1_data_0.unk_6C;
                fn_1_3064(1);
                lbl_1_bss_1C = 8;
                lbl_1_bss_18 = 0;
            }
            break;
        case 8:
            if (!WipeStatGet()) {
                lbl_1_bss_1C = 11;
                lbl_1_bss_18 = 0;
            }
            break;
        case 9:
            if (!WipeStatGet() && (lbl_1_bss_24 == -1 || !MGSeqStatGet(lbl_1_bss_24))) {
                lbl_1_bss_24 = -1;
                WipeCreate(1, 0, 30);
                WipeColorSet(0xFF, 0xFF, 0xFF);
                lbl_1_bss_8 = 0;
                CRot.x = lbl_1_data_0.unk_54;
                CRot.y = lbl_1_data_0.unk_58;
                CRot.z = lbl_1_data_0.unk_5C;
                Center.x = lbl_1_data_0.unk_60;
                Center.y = lbl_1_data_0.unk_64;
                Center.z = lbl_1_data_0.unk_68;
                CZoom = lbl_1_data_0.unk_6C;
                sp14.x = Center.x + (CZoom * (sind(CRot.y) * cosd(CRot.x)));
                sp14.y = Center.y + (CZoom * -sind(CRot.x));
                sp14.z = Center.z + (CZoom * (cosd(CRot.y) * cosd(CRot.x)));
                VECSubtract(&Center, &sp14, &sp8);
                VECNormalize(&sp8, &sp8);
                HuAudFXListnerUpdate(&sp14, &sp8);
                fn_1_6B5C();
                fn_1_3064(1);
                lbl_1_bss_1C = 10;
                lbl_1_bss_18 = 0;
            }
            break;
        case 10:
            if (!WipeStatGet()) {
                lbl_1_bss_1C = 11;
                lbl_1_bss_18 = 0;
            }
            break;
        case 11:
            break;
        case 12:
            if (lbl_1_bss_10 != 99) {
                lbl_1_bss_24 = MGSeqCreate(5, 3, GWPlayerCfg[lbl_1_bss_10].character, -1, -1, -1);
                HuAudSStreamPlay(1);
                GWPlayerCoinWinAdd(lbl_1_bss_10, 10);
                lbl_1_bss_1C = 13;
                lbl_1_bss_18 = 0;
            } else {
                lbl_1_bss_24 = MGSeqCreate(3, 2);
                HuAudSStreamPlay(4);
                lbl_1_bss_1C = 13;
                lbl_1_bss_18 = 0;
            }
            break;
        case 13:
            if (++lbl_1_bss_18 >= 210.0f) {
                lbl_1_bss_24 = -1;
                WipeCreate(2, 0, 60);
                lbl_1_bss_8 = 1;
                lbl_1_bss_1C = 14;
                lbl_1_bss_18 = 0;
            }
            break;
        case 14:
            if (!WipeStatGet()) {
                Hu3DBGColorSet(0, 0, 0);
                lbl_1_bss_1C = 15;
                lbl_1_bss_18 = 0;
            }
            break;
        case 15:
        default:
            object->func = fn_1_110C;
            break;
    }
    fn_1_1168(object);
}

void fn_1_110C(omObjData *object)
{
    if (!WipeStatGet()) {
        fn_1_D8B0();
        fn_1_2BEC();
        fn_1_B41C();
        HuAudFXListnerKill();
        HuDataDirClose(DATA_MAKE_NUM(DATADIR_M406, 0));
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_1168(omObjData *object)
{
    s32 var_r30;

    var_r30 = 0;
    if (WipeStatGet() || object->func == fn_1_110C) {
        return;
    }
    if (omSysExitReq) {
        var_r30 = 1;
    }
    if (var_r30) {
        if (!lbl_1_bss_8) {
            WipeCreate(2, 0, 60);
        }
        lbl_1_bss_8 = 1;
        HuAudStreamFadeOut(30);
        object->func = fn_1_110C;
    }
}

s32 fn_1_122C(void)
{
    return lbl_1_bss_1C;
}

void fn_1_123C(void)
{
    if (lbl_1_bss_1C <= 1) {
        lbl_1_bss_1C = 2;
        lbl_1_bss_18 = 0;
    }
}

void fn_1_1274(s32 arg0)
{
    lbl_1_bss_10 = arg0;
}

void fn_1_1284(void)
{
    if (lbl_1_bss_1C == 5) {
        lbl_1_bss_1C = 6;
        lbl_1_bss_18 = 0;
    }
}

void fn_1_12BC(void)
{
    if (lbl_1_bss_10 != 99) {
        if (lbl_1_bss_1C == 11) {
            lbl_1_bss_1C = 12;
            lbl_1_bss_18 = 0;
        }
    } else if (lbl_1_bss_1C == 11) {
        lbl_1_bss_1C = 12;
        lbl_1_bss_18 = 0;
    }
}

void fn_1_1340(void)
{
    omObjData *sp8;

    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    sp8 = lbl_1_bss_4 = omAddObjEx(lbl_1_bss_2C, 0x7FDA, 0, 0, -1, omOutView);
    CRot.x = lbl_1_data_0.unk_38;
    CRot.y = lbl_1_data_0.unk_3C;
    CRot.z = lbl_1_data_0.unk_40;
    Center.x = lbl_1_data_0.unk_44;
    Center.y = lbl_1_data_0.unk_48;
    Center.z = lbl_1_data_0.unk_4C;
    CZoom = lbl_1_data_0.unk_50;
    lbl_1_bss_0 = 0;
    omAddObjEx(lbl_1_bss_2C, 0xFF, 0, 0, -1, fn_1_151C);
}

void fn_1_151C(omObjData *object) { }

void fn_1_1520(void) { }

void fn_1_1524(void)
{
    CRot.x = lbl_1_data_0.unk_38;
    CRot.y = lbl_1_data_0.unk_3C;
    CRot.z = lbl_1_data_0.unk_40;
    Center.x = lbl_1_data_0.unk_44;
    Center.y = lbl_1_data_0.unk_48;
    Center.z = lbl_1_data_0.unk_4C;
    CZoom = lbl_1_data_0.unk_50;
}

void fn_1_15D0(float arg8)
{
    Vec sp14;
    Vec sp8;

    CRot.x = fn_1_1F10(arg8, lbl_1_data_0.unk_38, lbl_1_data_0.unk_00);
    CRot.y = fn_1_1F10(arg8, lbl_1_data_0.unk_3C, lbl_1_data_0.unk_04);
    CRot.z = fn_1_1F10(arg8, lbl_1_data_0.unk_40, lbl_1_data_0.unk_08);
    sp14.x = Center.x + (CZoom * (sind(CRot.y) * cosd(CRot.x)));
    sp14.y = Center.y + (CZoom * -sind(CRot.x));
    sp14.z = Center.z + (CZoom * (cosd(CRot.y) * cosd(CRot.x)));
    VECSubtract(&Center, &sp14, &sp8);
    VECNormalize(&sp8, &sp8);
    HuAudFXListnerUpdate(&sp14, &sp8);
}

void fn_1_183C(float arg8)
{
    Vec sp14;
    Vec sp8;

    CRot.x = fn_1_1F10(arg8, lbl_1_data_0.unk_1C, lbl_1_data_0.unk_70);
    CRot.y = fn_1_1F10(arg8, lbl_1_data_0.unk_20, lbl_1_data_0.unk_74);
    CRot.z = fn_1_1F10(arg8, lbl_1_data_0.unk_24, lbl_1_data_0.unk_78);
    Center.x = lbl_1_data_0.unk_28 + (arg8 * (lbl_1_data_0.unk_7C - lbl_1_data_0.unk_28));
    Center.y = lbl_1_data_0.unk_2C + (arg8 * (lbl_1_data_0.unk_80 - lbl_1_data_0.unk_2C));
    Center.z = lbl_1_data_0.unk_30 + (arg8 * (lbl_1_data_0.unk_84 - lbl_1_data_0.unk_30));
    CZoom = lbl_1_data_0.unk_34 + (arg8 * (lbl_1_data_0.unk_88 - lbl_1_data_0.unk_34));
    sp14.x = Center.x + (CZoom * (sind(CRot.y) * cosd(CRot.x)));
    sp14.y = Center.y + (CZoom * -sind(CRot.x));
    sp14.z = Center.z + (CZoom * (cosd(CRot.y) * cosd(CRot.x)));
    VECSubtract(&Center, &sp14, &sp8);
    VECNormalize(&sp8, &sp8);
    HuAudFXListnerUpdate(&sp14, &sp8);
}

s32 fn_1_1B98(void)
{
    return lbl_1_bss_0;
}

float fn_1_1BA8(float arg8, float arg9)
{
    float var_f31;

    if (arg8 >= 360.0f) {
        arg8 -= 360.0f;
    } else if (arg8 < 0.0f) {
        arg8 += 360.0f;
    }
    if (arg9 >= 360.0f) {
        arg9 -= 360.0f;
    } else if (arg9 < 0.0f) {
        arg9 += 360.0f;
    }
    var_f31 = arg8 - arg9;
    if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    } else if (var_f31 >= 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}

float fn_1_1CC0(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;

    if (arg8 >= 360.0) {
        arg8 -= 360.0;
    } else if (arg8 < 0.0) {
        arg8 += 360.0;
    }
    if (arg9 >= 360.0) {
        arg9 -= 360.0;
    } else if (arg9 < 0.0) {
        arg9 += 360.0;
    }
    var_f30 = 360.0 + (arg8 - arg9);
    if (fabs(var_f30) >= 360.0) {
        var_f30 = fmod(var_f30, 360.0);
    }
    if (var_f30 < 180.0) {
        if (var_f30 <= argA) {
            var_f31 = var_f30;
        } else {
            var_f31 = argA;
        }
    } else if (360.0 - var_f30 <= argA) {
        var_f31 = -(360.0 - var_f30);
    } else {
        var_f31 = -argA;
    }
    var_f31 += arg9;
    if (var_f31 >= 360.0) {
        var_f31 -= 360.0;
    } else if (var_f31 < 0.0) {
        var_f31 += 360.0;
    }
    return var_f31;
}

float fn_1_1F10(float arg8, float arg9, float argA)
{
    float var_f24;
    float var_f23;

    var_f23 = fn_1_1BA8(argA, arg9);
    var_f24 = fabs(var_f23 * arg8);
    return fn_1_1CC0(argA, arg9, var_f24);
}
