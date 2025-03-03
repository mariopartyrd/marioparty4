#include "REL/m424Dll.h"

#include "ext_math.h"
#include "game/audio.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/wipe.h"

// BSS
Process* lbl_1_bss_4C;
s32 lbl_1_bss_48;
s32 lbl_1_bss_44;
s32 lbl_1_bss_40;
s32 lbl_1_bss_3C;
s32 lbl_1_bss_38; // UNUSED
s32 lbl_1_bss_34;
s32 lbl_1_bss_30;
s32 lbl_1_bss_2C;
s16 lbl_1_bss_24[4];
s16 lbl_1_bss_1C[4];
omObjData* lbl_1_bss_18;
omObjData* lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
f32 lbl_1_bss_4[2]; // UNUSED
f32 lbl_1_bss_0;

// data
M424DllMainStruct lbl_1_data_0[3] = {
    {
        { 320.0f,  0.0f,   0.0f  },
        { 201.0f,  175.0f, 72.0f },
        2025.0f
    },
    {
        { 320.0f,  0.0f,    0.0f  },
        { 0.0f,    225.0f, -72.0f },
        550.0f
    },
    {
        { 320.0f,  0.0f,   0.0f  },
        { 401.0f,  175.0f, 72.0f },
        625.0f
    }
};
Vec lbl_1_data_54 = { 1000.0f, 2000.0f, 1000.0f };
Vec lbl_1_data_60 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_6C = { 0.0f, 0.0f, -450.0f };

// PROTO
void fn_1_264(omObjData* object);
void fn_1_41C(omObjData* object);
void fn_1_EE0(omObjData* object);
void fn_1_F40(omObjData* object);
void fn_1_FF0(void);
void fn_1_11EC(omObjData* object);
void fn_1_1204(s32, s32, f32);
f32 fn_1_16C0(f32, f32, f32);

/// FUNCTIONS ///

void ObjectSetup(void) {
    s32 var_r31;
    Process* var_r30;
    CameraData* var_r29;

    OSReport("******* M424ObjectSetup *********\n");
    var_r30 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_4C = var_r30;
    omGameSysInit(var_r30);
    fn_1_FF0();
    var_r29 = &Hu3DCamera[0];
    var_r29->fov = -1.0f;
    Hu3DLightAllKill();
    Hu3DLighInit();
    HuAudSndGrpSet(0x31);
    lbl_1_bss_18 = omAddObjEx(var_r30, 0xFF, 2, 0, -1, fn_1_264);
    lbl_1_bss_48 = lbl_1_bss_44 = -1;
    lbl_1_bss_40 = 0;
    lbl_1_bss_3C = 0;
    lbl_1_bss_34 = 0;
    lbl_1_bss_2C = -1;
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_24[var_r31] = -1;
        lbl_1_bss_1C[var_r31] = -1;
    }
    Hu3DShadowCreate(30.0f, 1000.0f, 250000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_data_54, &lbl_1_data_60, &lbl_1_data_6C);
    Hu3DBGColorSet(0xFFU, 0xFFU, 0xFFU);
}

Vec lbl_1_data_9C = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_A8 = { -1.0f, -2.0f, -1.0f };
GXColor lbl_1_data_B4 = { 0xFF, 0xFF, 0xFF, 0xFF };

void fn_1_264(omObjData* object) {
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r29 = Hu3DGLightCreateV(&lbl_1_data_9C, &lbl_1_data_A8, &lbl_1_data_B4);
    Hu3DGLightStaticSet(var_r29, 1);
    Hu3DGLightInfinitytSet(var_r29);
    
    for (var_r31 = 0, var_r30 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayerCfg[var_r31].group == 0) {
            lbl_1_bss_24[3] = var_r31;
            lbl_1_bss_1C[3] = GWPlayerCfg[var_r31].character;
        } else {
            lbl_1_bss_24[var_r30] = var_r31;
            lbl_1_bss_1C[var_r30] = GWPlayerCfg[var_r31].character;
            var_r30++;
        }
    }
    if (var_r30 >= 4) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            lbl_1_bss_24[var_r31] = var_r31;
            lbl_1_bss_1C[var_r31] = GWPlayerCfg[var_r31].character;
        }
    }
    fn_1_1AB8(lbl_1_bss_4C);
    fn_1_2720(lbl_1_bss_4C);
    fn_1_93F0(lbl_1_bss_4C);
    object->func = fn_1_41C;
}

void fn_1_41C(omObjData* object) {
    s16 sp16;
    s16 sp12;
    s16 spE;
    s16 spA;
    f32 var_f31; // ! - uninitalized
    s32 var_r31;
    s32 var_r30;
    CameraData* var_r29;

    switch (lbl_1_bss_40) {
        case 0:
            lbl_1_bss_0 += fn_1_213C();
            fn_1_1204(2, 2, var_f31);
            if (lbl_1_bss_0 >= 360.0f) {
                WipeCreate(1, 0, 0x3C);
                var_r29 = &Hu3DCamera[0];
                var_r29->fov = 45.0f;
                lbl_1_bss_40 = 1;
                lbl_1_bss_3C = 0;
            }
            break;
        case 1:
            if (WipeStatGet() == 0) {
                lbl_1_bss_40 = 2;
                lbl_1_bss_3C = 0;
            }
            break;
        case 2:
            if (++lbl_1_bss_3C >= 120.0f) {
                lbl_1_bss_48 = MGSeqCreate(3, 0);
                lbl_1_bss_40 = 3;
                lbl_1_bss_3C = 0;
                lbl_1_bss_34 = 0;
            }
            break;
        case 3:
            lbl_1_bss_34++;
            var_f31 = lbl_1_bss_34 / 60.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            var_f31 = sind((90.0f * (var_f31 * var_f31)));
            fn_1_1204(2, 0, var_f31);
            if (lbl_1_bss_48 != -1) {
                var_r31 = MGSeqStatGet(lbl_1_bss_48);
                if (((var_r31 & 0x10) != 0) && (lbl_1_bss_2C == -1)) {
                    lbl_1_bss_2C = HuAudSeqPlay(0x48);
                }
            } else {
                var_r31 = 0;
            }
            if ((lbl_1_bss_48 == -1) || (var_r31 == 0)) {
                if (lbl_1_bss_34 >= 60.0f) {
                    lbl_1_bss_48 = -1;
                    lbl_1_bss_40 = 4;
                    lbl_1_bss_3C = 0;
                    lbl_1_bss_34 = 0xE10;
                    lbl_1_bss_44 = MGSeqCreate(1, lbl_1_bss_34 / 60, -1, -1);
                }
            }
            break;
        case 4:
            var_r30 = (lbl_1_bss_34 + 0x3B) / 60;
            if (var_r30 < 0) {
                var_r30 = 0;
            }
            MGSeqParamSet(lbl_1_bss_44, 1, var_r30);
            if ((--lbl_1_bss_34 < -1) || (fn_1_B888() != 0)) {
                MGSeqParamSet(lbl_1_bss_44, 2, -1);
                lbl_1_bss_44 = -1;
                lbl_1_bss_48 = MGSeqCreate(3, 1);
                if (lbl_1_bss_2C != -1) {
                    HuAudSeqFadeOut(lbl_1_bss_2C, 0x64);
                }
                lbl_1_bss_40 = 5;
                lbl_1_bss_3C = 0;
            }
            break;
        case 5:
            if ((lbl_1_bss_48 == -1) || ((MGSeqStatGet(lbl_1_bss_48) == 0) && (fn_1_B8AC() != 0) && (fn_1_8A2C() != 0) && (fn_1_213C() <= 0.0f))) {
                if (fn_1_B888() != 0) {
                    lbl_1_bss_30 = 0;
                } else {
                    lbl_1_bss_30 = 1;
                }
                HuAudAllStop();
                lbl_1_bss_40 = 6;
                lbl_1_bss_3C = 0;
            }
            break;
        case 6:
            if (lbl_1_bss_30 == 0) {
                if (fn_1_B924() != 0) {
                    lbl_1_bss_40 = 7;
                    lbl_1_bss_3C = 0;
                }
            } else {
                if (++lbl_1_bss_3C >= 120.0f) {
                    lbl_1_bss_40 = 7;
                    lbl_1_bss_3C = 0;
                }
            }
            break;
        case 7:
            if (lbl_1_bss_30 != 0) {
                lbl_1_bss_48 = MGSeqCreate(5, 3, lbl_1_bss_1C[0], lbl_1_bss_1C[1], lbl_1_bss_1C[2], -1);
                GWPlayerCoinWinSet(lbl_1_bss_24[0], GWPlayerCoinWinGet(lbl_1_bss_24[0]) + 10);
                GWPlayerCoinWinSet(lbl_1_bss_24[1], GWPlayerCoinWinGet(lbl_1_bss_24[1]) + 10);
                GWPlayerCoinWinSet(lbl_1_bss_24[2], GWPlayerCoinWinGet(lbl_1_bss_24[2]) + 10);
                HuAudSStreamPlay(1);
                lbl_1_bss_40 = 8;
                lbl_1_bss_34 = 0;
            } else {
                lbl_1_bss_48 = MGSeqCreate(5, 3, lbl_1_bss_1C[3], -1, -1, -1);
                GWPlayerCoinWinSet(lbl_1_bss_24[3], GWPlayerCoinWinGet(lbl_1_bss_24[3]) + 10);
                HuAudSStreamPlay(1);
                lbl_1_bss_40 = 8;
                lbl_1_bss_34 = 0;
            }
            break;
        case 8:
            if (lbl_1_bss_30 == 0) {
                var_f31 = lbl_1_bss_34 / 60.0f;
                if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                var_f31 = sind(90.0f * (var_f31 * var_f31));
                fn_1_1204(0, 1, var_f31);
            }
            if (++lbl_1_bss_34 >= 210.0f) {
                lbl_1_bss_48 = -1;
                lbl_1_bss_40 = 9;
                lbl_1_bss_34 = 0;
            }
            break;
        case 9:
            WipeCreate(2, 0, 0x3C);
            object->func = fn_1_EE0;
            break;
    }
    fn_1_F40(object);
}

void fn_1_EE0(omObjData* object) {
    if (WipeStatGet() == 0) {
        Hu3DBGColorSet(0, 0, 0);
        fn_1_1B8C();
        fn_1_2880();
        fn_1_94A4();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_F40(omObjData* object) {
    s32 var_r30;

    var_r30 = 0;
    if ((WipeStatGet() != 0) || (object->func == fn_1_EE0)) {
        return;
    }
    if (omSysExitReq != 0) {
        var_r30 = 1;
    }
    if (var_r30 != 0) {
        WipeCreate(2, 0, 0x3C);
        HuAudStreamFadeOut(0x1E);
        object->func = fn_1_EE0;
    }
}

s32 fn_1_FE0(void) {
    return lbl_1_bss_40;
}

void fn_1_FF0(void) {
    omObjData* var_r31;

    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 50.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 0x280, 0x1E0);
    var_r31 = lbl_1_bss_14 = omAddObjEx(lbl_1_bss_4C, 0x7FDA, 0, 0, -1, omOutView);
    var_r31->work[0] = 1;
    CRot.x = lbl_1_data_0[0].rot.x;
    CRot.y = lbl_1_data_0[0].rot.y;
    CRot.z = lbl_1_data_0[0].rot.z;
    Center.x = lbl_1_data_0[0].center.x;
    Center.y = lbl_1_data_0[0].center.y;
    Center.z = lbl_1_data_0[0].center.z;
    CZoom = lbl_1_data_0[0].zoom;
    lbl_1_bss_C = 0;
    lbl_1_bss_10 = -1;
    omAddObjEx(lbl_1_bss_4C, 0xFF, 0, 0, -1, fn_1_11EC);
}

void fn_1_11EC(omObjData* object) {}
void fn_1_11F0(void) {}

s32 fn_1_11F4(void) {
    return lbl_1_bss_C;
}

void fn_1_1204(s32 arg0, s32 arg1, f32 arg2) {
    M424DllMainStruct* temp_r30;
    M424DllMainStruct* temp_r31;

    temp_r31 = &lbl_1_data_0[arg0];
    temp_r30 = &lbl_1_data_0[arg1];
    CRot.x = fn_1_16C0(arg2, temp_r31->rot.x, temp_r30->rot.x);
    CRot.y = fn_1_16C0(arg2, temp_r31->rot.y, temp_r30->rot.y);
    CRot.z = fn_1_16C0(arg2, temp_r31->rot.z, temp_r30->rot.z);
    Center.x = temp_r31->center.x + (arg2 * (temp_r30->center.x - temp_r31->center.x));
    Center.y = temp_r31->center.y + (arg2 * (temp_r30->center.y - temp_r31->center.y));
    Center.z = temp_r31->center.z + (arg2 * (temp_r30->center.z - temp_r31->center.z));
    CZoom = temp_r31->zoom + (arg2 * (temp_r30->zoom - temp_r31->zoom));
}

f32 fn_1_1358(f32 arg8, f32 arg9) {
    f32 var_f31;

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
    } else {
        if (var_f31 >= 180.0f) {
            var_f31 -= 360.0f;
        }
    }
    return var_f31;
}

f32 fn_1_1470(f32 arg8, f32 arg9, f32 argA) {
    f32 var_f30;
    f32 var_f31;

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
    var_f30 = (360.0 + (arg8 - arg9));
    if (fabs(var_f30) >= 360.0) {
        var_f30 = fmod(var_f30, 360.0);
    }
    if (var_f30 < 180.0) {
        if (var_f30 <= argA) {
            var_f31 = var_f30;
        } else {
            var_f31 = argA;
        }
    } else {
        if ((360.0 - var_f30) <= argA) {
            var_f31 = -(360.0 - var_f30);
        } else {
            var_f31 = -argA;
        }
    }
    var_f31 = var_f31 + arg9;
    if (var_f31 >= 360.0) {
        var_f31 -= 360.0;
    } else if (var_f31 < 0.0) {
        var_f31 += 360.0;
    }
    return var_f31;
}

f32 fn_1_16C0(f32 arg0, f32 arg1, f32 arg2) {
    f32 temp_f24;
    f32 var_f23;

    var_f23 = fn_1_1358(arg2, arg1);
    temp_f24 = fabs(var_f23 * arg0);
    return fn_1_1470(arg2, arg1, temp_f24);
}
