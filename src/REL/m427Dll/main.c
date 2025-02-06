#include "REL/m427Dll.h"

#include "ext_math.h"
#include "game/audio.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfformat.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/wipe.h"

typedef struct M427DllStruct2 {
    s32 unk0[3];
    s32 unkC;
    s32 unk10;
    s32 unk14[7];
    s32 unk30[7];
    HsfVector2f unk4C[7];
    f32 unk84;
    f32 unk88;
    s32 unk8C;
    f32 unk90;
    f32 unk94;
    f32 unk98;
    s32 unk9C;
    s32 unkA0;
} M427DllStruct2; // sizeof 0xA4

typedef struct M427DllStruct3 {
    Vec rot;
    Vec cen;
    f32 zoom;
} M427DllStruct3;

Process* lbl_1_bss_8C;
omObjData* lbl_1_bss_88;
s32 lbl_1_bss_84;
s32 lbl_1_bss_80;
s32 lbl_1_bss_7C;
s32 lbl_1_bss_78;
s32 lbl_1_bss_74;
f32 lbl_1_bss_6C[2];
s32 lbl_1_bss_68;
s32 lbl_1_bss_64;
s32 lbl_1_bss_60;
s32 lbl_1_bss_5C;
s32 lbl_1_bss_58;
s32 lbl_1_bss_54;
s32 lbl_1_bss_50;
s32 lbl_1_bss_4C;
omObjData* lbl_1_bss_48;
s32 lbl_1_bss_44;
M427DllStruct2* lbl_1_bss_40;
M427DllStruct lbl_1_bss_0[8];

void fn_1_29C(omObjData*);
void fn_1_300(omObjData*);
void fn_1_1664(omObjData*);
void fn_1_16C4(omObjData*);
void fn_1_1864(s32);
void fn_1_1954(void);
void fn_1_1F34(void);
void fn_1_2188(void);
void fn_1_21E8(s32, s32);
void fn_1_232C(s32);
void fn_1_2518(s32);
void fn_1_2704(void);
void fn_1_272C(void);
void fn_1_2790(void);
void fn_1_2B20(omObjData* object);
void fn_1_2B28(void);
void fn_1_2CE8(f32);
void fn_1_2EE0(void);
void fn_1_2F6C(f32);
void fn_1_3164(void);

M427DllStruct3 lbl_1_data_0[4] = {
    {
        { -25.0f,   0.0f, 0.0f },
        {   0.0f, 275.0f, 0.0f },
        1975.0f
    },
    {
        { 4.0f,  167.0f, 0.0f },
        { 57.0f, 475.0f, 198.0f },
        3375.0f
    },
    {
        {  -0.0f, -190.0f, 0.0f },
        { -90.0f,   50.0f, 800.0f },
        1700.0f
    },
    {
        {    2.0f, 170.0f,   0.0f },
        { -400.0f, 175.0f, 127.0f },
        2425.0f
    }
};

void ObjectSetup(void) {
    Process* var_r30;
    s32 var_r31;

    OSReport("******* M426ObjectSetup *********\n");
    var_r30 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_8C = var_r30;
    omGameSysInit(var_r30);
    fn_1_2790();
    Hu3DLightAllKill();
    Hu3DLighInit();
    HuAudSndGrpSet(0x34);
    lbl_1_bss_88 = omAddObjEx(var_r30, 0xFF, 2, 0, -1, fn_1_29C);
    lbl_1_bss_84 = 0;
    lbl_1_bss_80 = 0;
    lbl_1_bss_7C = 0;
    lbl_1_bss_78 = lbl_1_bss_74 = GWMGRecordGet(2);
    if (lbl_1_bss_78 <= 0) {
        lbl_1_bss_78 = lbl_1_bss_74 = 0xE10;
    }
    
    lbl_1_bss_68 = lbl_1_bss_64 = 0;
    
    lbl_1_bss_60 = lbl_1_bss_5C = -1;
    lbl_1_bss_58 = -1;
    lbl_1_bss_54 = lbl_1_bss_50 = -1;
    
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_6C[var_r31] = 0.0f;
    }
    
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        lbl_1_bss_0[var_r31].unk0 = -1;
        lbl_1_bss_0[var_r31].unk4 = 0;
    }
}

void fn_1_29C(omObjData* arg0) {
    fn_1_32F4(lbl_1_bss_8C);
    fn_1_E98C(lbl_1_bss_8C);
    fn_1_1954();
    fn_1_21E8(0, 1);
    arg0->func = fn_1_300;
}

void fn_1_300(omObjData* arg0) {
    s32 sp10[2];
    s32 sp8[2];
    f32 var_f31;
    f32 var_f30;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r26;

    switch (lbl_1_bss_84) {
        case 0:
            lbl_1_bss_80++;
            if (lbl_1_bss_80 == 3) {
                WipeCreate(1, 0, 0x3C);
                lbl_1_bss_4C = 0;
                fn_1_21E8(1, 1);
                fn_1_2B28();
            } else if ((lbl_1_bss_80 > 3) && (WipeStatGet() == 0)) {
                lbl_1_bss_54 = HuAudFXPlay(0x657);
                lbl_1_bss_50 = HuAudFXPlay(0x651);
                lbl_1_bss_84 = 1;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            }
            break;
        case 1:
            lbl_1_bss_80++;
            var_f31 = lbl_1_bss_80 / 300.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            fn_1_11298(sind(90.0f * var_f31));
            if (++lbl_1_bss_7C >= 60.0f) {
                lbl_1_bss_84 = 2;
                lbl_1_bss_7C = 0;
            }
            break;
        case 2:
            lbl_1_bss_80++;
            var_f31 = lbl_1_bss_80 / 300.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            fn_1_11298(sind(90.0f * var_f31));
            var_f30 = sind(90.0f * (lbl_1_bss_7C / 240.0f));
            fn_1_2CE8(var_f30 * var_f30);
            if (++lbl_1_bss_7C >= 240.0f) {
                lbl_1_bss_60 = MGSeqCreate(3, 0);
                fn_1_2EE0();
                lbl_1_bss_84 = 3;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            }
            break;
        case 3:
            if (lbl_1_bss_60 != -1) {
                var_r28 = MGSeqStatGet(lbl_1_bss_60);
                if (((var_r28 & 0x10) != 0) && (lbl_1_bss_58 == -1)) {
                    lbl_1_bss_58 = HuAudSeqPlay(0x49);
                }
            } else {
                var_r28 = 0;
            }
            if ((lbl_1_bss_60 == -1) || (var_r28 == 0)) {
                lbl_1_bss_84 = 4;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            }
            break;
        case 4:
            lbl_1_bss_80++;
            var_r30 = lbl_1_bss_80;
            if (var_r30 > 0x4650) {
                var_r30 = 0x4650;
            }
            
            fn_1_2518(var_r30);
            for (var_r31 = 0; var_r31 < 8; var_r31++) {
                if (lbl_1_bss_0[var_r31].unk0 != -1) {
                    if (--lbl_1_bss_0[var_r31].unk4 <= 0) {
                        lbl_1_bss_0[var_r31].unk0 = -1;
                        lbl_1_bss_0[var_r31].unk4 = 0;
                    }
                }
            }
            if (lbl_1_bss_80 == 0x3F48) {
                lbl_1_bss_5C = MGSeqCreate(1, 0x708, -1, -1);
            }
            if (lbl_1_bss_5C != -1) {
                var_r26 = (0x4650 - lbl_1_bss_80);
                var_r30 = (var_r26 + 0x3A) / 60;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
                MGSeqParamSet(lbl_1_bss_5C, 1, var_r30);
            }
            if (lbl_1_bss_68 != 0) {
                if (lbl_1_bss_68 != 1 && lbl_1_bss_68 != 2) {
                    if (((s32)frand() & 1) != 0) {
                        lbl_1_bss_68 = 1;
                    } else {
                        lbl_1_bss_68 = 2;
                    }
                }
                if (lbl_1_bss_5C != -1) {
                    MGSeqParamSet(lbl_1_bss_5C, 2, -1);
                }
                lbl_1_bss_5C = -1;
                lbl_1_bss_60 = MGSeqCreate(3, 1);
                if (lbl_1_bss_58 != -1) {
                    HuAudSeqFadeOut(lbl_1_bss_58, 0x64);
                }
                
                for (var_r31 = 0; var_r31 < 8; var_r31++) {
                    if ((lbl_1_bss_0[var_r31].unk0 != -1) && (lbl_1_bss_0[var_r31].unk4 > 0)) {
                        HuAudFXFadeOut(lbl_1_bss_0[var_r31].unk0, 0x64);
                    }
                }
                HuAudFXFadeOut(lbl_1_bss_54, 0x64);
                HuAudFXFadeOut(lbl_1_bss_50, 0x64);
                if ((lbl_1_bss_68 != 0) && (lbl_1_bss_80 < lbl_1_bss_78)) {
                    if (lbl_1_bss_68 == 1) {
                        var_r29 = 0;
                    } else {
                        var_r29 = 1;
                    }
                    if (fn_1_113F0(var_r29) == 0) {
                        lbl_1_bss_74 = lbl_1_bss_80;
                    }
                }
                if ((lbl_1_bss_68 != 0) && (lbl_1_bss_80 <= 0xA8C)) {
                    if (lbl_1_bss_68 == 1) {
                        var_r29 = 0;
                    } else {
                        var_r29 = 1;
                    }
                    if (fn_1_113F0(var_r29) == 0) {
                        GWGameStat.present[0x34] = 1;
                    }
                }
                lbl_1_bss_84 = 5;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            } else {
                if (lbl_1_bss_80 >= 0x4651) {
                    MGSeqParamSet(lbl_1_bss_5C, 1, 0);
                    MGSeqParamSet(lbl_1_bss_5C, 2, -1);
                    lbl_1_bss_5C = -1;
                    lbl_1_bss_60 = MGSeqCreate(3, 1);
                    if (lbl_1_bss_58 != -1) {
                        HuAudSeqFadeOut(lbl_1_bss_58, 0x64);
                    }
                    
                    for (var_r31 = 0; var_r31 < 8; var_r31++) {
                        if ((lbl_1_bss_0[var_r31].unk0 != -1) && (lbl_1_bss_0[var_r31].unk4 > 0)) {
                            HuAudFXFadeOut(lbl_1_bss_0[var_r31].unk0, 0x64);
                        }
                    }
                    HuAudFXFadeOut(lbl_1_bss_54, 0x64);
                    HuAudFXFadeOut(lbl_1_bss_50, 0x64);
                    lbl_1_bss_64 = 1;
                    lbl_1_bss_84 = 5;
                    lbl_1_bss_80 = 0;
                    lbl_1_bss_7C = 0;
                }
            }
            break;
        case 5:
            if (lbl_1_bss_68 != 0) {
                WipeCreate(2, 0, 0x3C);
                WipeColorSet(0xFF, 0xFF, 0xFF);
                lbl_1_bss_4C = 1;
                lbl_1_bss_84 = 6;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            } else if ((lbl_1_bss_60 == -1) || (MGSeqStatGet(lbl_1_bss_60) == 0)) {
                lbl_1_bss_84 = 0xA;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            }
            break;
        case 6:
            if ((WipeStatGet() == 0) && ((lbl_1_bss_60 == -1) || (MGSeqStatGet(lbl_1_bss_60) == 0))) {
                lbl_1_bss_60 = -1;
                fn_1_21E8(0, 0);
                fn_1_3164();
                HuAudFXAllStop();
                HuAudFXPlay(0x65E);
                lbl_1_bss_84 = 7;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            }
            break;
        case 7:
            if (++lbl_1_bss_80 > 5) {
                WipeCreate(1, 0, 0x1E);
                WipeColorSet(0xFF, 0xFF, 0xFF);
                lbl_1_bss_4C = 0;
                HuAudAUXVolSet(-1, -1);
                fn_1_272C();
                lbl_1_bss_84 = 8;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            }
            break;
        case 8:
            if (WipeStatGet() == 0) {
                lbl_1_bss_84 = 0xA;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            }
            break;
        case 10:
            if (lbl_1_bss_68 != 0) {
                var_f31 = sind((90.0f * (lbl_1_bss_80 / 180.0f)));
                if (var_f31 >= 1.0f) {
                    var_f31 = 1.0f;
                }
                fn_1_11298(var_f31);
                if (lbl_1_bss_80 > 30.0f) {
                    var_f30 = lbl_1_bss_7C / 150.0f;
                    lbl_1_bss_7C++;
                    if (var_f30 >= 1.0f) {
                        var_f30 = 1.0f;
                    }
                    var_f30 = sind(90.0f * var_f30);
                    fn_1_2F6C(var_f30);
                }
                if (++lbl_1_bss_80 > 180.0f) {
                    if (lbl_1_bss_68 == 1) {
                        fn_1_110E8(0, sp10);
                        fn_1_111C0(0, sp8);
                    } else {
                        fn_1_110E8(1, sp10);
                        fn_1_111C0(1, sp8);
                    }
                    GWPlayerCoinWinAdd(sp8[0], 10);
                    GWPlayerCoinWinAdd(sp8[1], 10);
                    if (lbl_1_bss_74 < lbl_1_bss_78) {
                        lbl_1_bss_78 = lbl_1_bss_74;
                        fn_1_232C(lbl_1_bss_78);
                        GWMGRecordSet(2, lbl_1_bss_78);
                        fn_1_2704();
                        lbl_1_bss_60 = MGSeqCreate(0xE, lbl_1_bss_78);
                        lbl_1_bss_7C = 0xB4;
                        lbl_1_bss_84 = 0xB;
                        lbl_1_bss_80 = 0;
                    } else {
                        lbl_1_bss_60 = MGSeqCreate(5, 3, sp10[0], sp10[1], -1, -1);
                        HuAudSStreamPlay(1);
                        lbl_1_bss_7C = 0xB4;
                        lbl_1_bss_84 = 0xC;
                        lbl_1_bss_80 = 0;
                    }
                }
            } else {
                lbl_1_bss_60 = MGSeqCreate(3, 2);
                HuAudSStreamPlay(4);
                lbl_1_bss_7C = 0xB4;
                lbl_1_bss_84 = 0xC;
                lbl_1_bss_80 = 0;
            }
            break;
        case 11:
            if ((lbl_1_bss_60 == -1) || (MGSeqStatGet(lbl_1_bss_60) == 0)) {
                if (lbl_1_bss_68 == 1) {
                    fn_1_110E8(0, sp10);
                } else {
                    fn_1_110E8(1, sp10);
                }
                lbl_1_bss_60 = MGSeqCreate(5, 3, sp10[0], sp10[1], -1, -1);
                HuAudSStreamPlay(1);
                lbl_1_bss_7C = 0xB4;
                lbl_1_bss_84 = 0xC;
                lbl_1_bss_80 = 0;
            }
            break;
        case 12:
            if (++lbl_1_bss_80 >= 210.0f) {
                WipeCreate(2, 0, 0x3C);
                lbl_1_bss_4C = 1;
                lbl_1_bss_84 = 0xD;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            }
            break;
        case 13:
            if (WipeStatGet() == 0) {
                lbl_1_bss_84 = 0xE;
                lbl_1_bss_80 = 0;
                lbl_1_bss_7C = 0;
            }
            break;
        case 14:
            arg0->func = fn_1_1664;
            break;
    }
    fn_1_1F34();
    fn_1_16C4(arg0);
}

void fn_1_1664(omObjData* arg0) {
    if (WipeStatGet() == 0) {
        fn_1_EC54();
        fn_1_3A88();
        fn_1_2188();
        CharModelKill(-1);
        HuDataDirClose(0x3A0000);
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_16C4(omObjData* arg0) {
    s32 var_r30;

    var_r30 = 0;
    if ((WipeStatGet() != 0) || (arg0->func == fn_1_1664)) {
        return;
    }
    if (omSysExitReq != 0) {
        var_r30 = 1;
    }
    if (var_r30 != 0) {
        if ((s32) lbl_1_bss_4C == 0) {
            WipeCreate(2, 0, 0x3C);
        }
        lbl_1_bss_4C = 1;
        HuAudStreamFadeOut(0x1E);
        arg0->func = fn_1_1664;
    }
}

s32 fn_1_1788(void) {
    return lbl_1_bss_84;
}

void fn_1_1798(s32 arg0, f32 arg8) {
    
    if (arg8 < 0.0f) {
        arg8 = 0.0f;
    } else if (arg8 > 1.0f) {
        arg8 = 1.0f;
    }
    lbl_1_bss_6C[arg0] = arg8;
    if (lbl_1_bss_6C[arg0] >= 1.0f) {
        fn_1_1864(1 << arg0);
    }
}

void fn_1_1864(s32 arg0) {
    lbl_1_bss_68 |= arg0;
}

s32 fn_1_1884(void) {
    if (lbl_1_bss_68 != 0) {
        if (lbl_1_bss_68 != 1 && lbl_1_bss_68 != 2) {
            if (((s32)frand() & 1) != 0) {
                lbl_1_bss_68 = 1;
            } else {
                lbl_1_bss_68 = 2;
            }
        }
        if (lbl_1_bss_68 == 1) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if (lbl_1_bss_64 != 0) {
            return 3;
        } else {
            return -1;
        }
    }
}

s32 lbl_1_data_D0[2] = { 0x3A0029, 0x3A002A };
s16 lbl_1_data_D8[2] = { -24, 24 };
s16 lbl_1_data_DC[2] = { -10, 10 };
s16 lbl_1_data_E0[2] = { 350, 96 };

void fn_1_1954(void) {
    f32 temp_f28;
    f32 temp_f29;
    f32 var_f31;
    f32 var_f30;
    s32 var_r29;
    s32 var_r31;
    M427DllStruct2* var_r30;

    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, 0xA4, 0x10000000);
    lbl_1_bss_40 = var_r30;
    var_r30->unk9C = 0;
    var_r30->unkA0 = 0;
    var_r31 = espEntry(0x3A0028, 1, 0);
    var_r30->unk0[0] = var_r31;
    espPriSet(var_r31, 0xFF);
    espDispOn(var_r31);
    espDrawNoSet(var_r31, 0);
    espAttrSet(var_r31, 1);
    espBankSet(var_r31, 0);
    espPosSet(var_r31, 288.0, 240.0);
    
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        var_r31 = espEntry(lbl_1_data_D0[var_r29], 1, 0);
        var_r30->unk0[var_r29 + 1] = var_r31;
        espPriSet(var_r31, 0xC8);
        espDispOn(var_r31);
        espDrawNoSet(var_r31, 0);
        espAttrSet(var_r31, 1);
        espBankSet(var_r31, 0);
        espPosSet(var_r31, 288.0f + lbl_1_data_D8[var_r29], 240.0);
    }
    
    temp_f28 = 288.0f;
    temp_f29 = 400.0f;
    var_f31 = 288.0f;
    var_f30 = temp_f29;
    var_r31 = espEntry(0x3A002B, 1, 0);
    var_r30->unkC = var_r31;
    espPriSet(var_r31, 0xBE);
    espDispOn(var_r31);
    espDrawNoSet(var_r31, 0);
    espAttrSet(var_r31, 1);
    espBankSet(var_r31, 0);
    espTPLvlSet(var_r31, 0.5);
    espColorSet(var_r31, 0x80, 0x80, 0x80);
    espScaleSet(var_r31, 1.25, 1.5);
    espPosSet(var_r31, var_f31, var_f30);
    var_f31 = 248.0f;
    var_f30 = temp_f29 - 8.0f;
    var_r31 = espEntry(0x610037, 1, 0);
    var_r30->unk10 = var_r31;
    espPriSet(var_r31, 0xBE);
    espDispOn(var_r31);
    espDrawNoSet(var_r31, 0);
    espAttrSet(var_r31, 1);
    espBankSet(var_r31, 0);
    espScaleSet(var_r31, 1.0, 1.0);
    espPosSet(var_r31, var_f31 - 18.0f, var_f30);
    var_r30->unk84 = ((var_f31 - 18.0f) - temp_f28);
    var_r30->unk88 = (var_f30 - temp_f29);
    var_r30->unk8C = -1;
    var_r30->unk98 = 1.0f;
    var_r30->unk90 = temp_f28;
    var_r30->unk94 = temp_f29;
    var_f31 = 248.0f;
    var_f30 = temp_f29 - 8.0f;
    
    for (var_r29 = 0; var_r29 < 7; var_r29++) {
        var_r31 = espEntry(0x610030, 1, 0);
        var_r30->unk14[var_r29] = var_r31;
        espPriSet(var_r31, 0xB4);
        espDispOn(var_r31);
        espDrawNoSet(var_r31, 0);
        espAttrSet(var_r31, 9);
        espScaleSet(var_r31, 1.0, 1.0);
        espPosSet(var_r31, var_f31, var_f30);
        if (var_r29 == 1) {
            espBankSet(var_r31, 10);
        } else if (var_r29 == 4) {
            espBankSet(var_r31, 11);
        } else {
            espBankSet(var_r31, 0);
        }
        var_r30->unk4C[var_r29].x = var_f31 - temp_f28;
        var_r30->unk4C[var_r29].y = var_f30 - temp_f29;
        var_f31 += 16.0f;
    }
    var_f31 = 248.0f;
    var_f30 = 8.0f + temp_f29;
    
    for (var_r29 = 0; var_r29 < 7; var_r29++) {
        var_r31 = espEntry(0x610031, 1, 0);
        var_r30->unk30[var_r29] = var_r31;
        espPriSet(var_r31, 0xB4);
        espDispOn(var_r31);
        espDrawNoSet(var_r31, 0);
        espAttrSet(var_r31, 1);
        espScaleSet(var_r31, 1.0, 1.0);
        espPosSet(var_r31, var_f31, var_f30);
        if (var_r29 == 1) {
            espBankSet(var_r31, 10);
        } else if (var_r29 == 4) {
            espBankSet(var_r31, 11);
        } else {
            espBankSet(var_r31, 0);
        }
        var_f31 += 16.0f;
    }
    fn_1_232C(lbl_1_bss_78);
    fn_1_2518(0);
}

void fn_1_1F34(void) {
    f32 var_f30;
    f32 temp_f31;
    s32 var_r29;
    s32 var_r30;
    M427DllStruct2* temp_r31;

    temp_r31 = lbl_1_bss_40;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r29 = temp_r31->unk0[var_r30 + 1];
        var_f30 = lbl_1_data_E0[0] + (lbl_1_bss_6C[var_r30] * (lbl_1_data_E0[1] - lbl_1_data_E0[0]));
        espPosSet(var_r29, 288.0f + lbl_1_data_DC[var_r30], var_f30);
    }
    if (temp_r31->unk8C != -1) {
        if (temp_r31->unk8C == 0) {
            if ((temp_r31->unk98 += 0.02f) >= 1.2f) {
                temp_r31->unk98 = 1.2f;
                temp_r31->unk8C = 1;
            }
        } else {
            if ((temp_r31->unk98 -= 0.04f) <= 1.0f) {
                temp_r31->unk98 = 1.0f;
                temp_r31->unk8C = 0;
            }
        }
        temp_f31 = temp_r31->unk98;
        
        for (var_r30 = 0; var_r30 < 7; var_r30++) {
            var_r29 = temp_r31->unk14[var_r30];
            espScaleSet(var_r29, temp_f31, temp_f31);
        }
        var_r29 = temp_r31->unk10;
        espScaleSet(var_r29, temp_f31, temp_f31);
    }
}

void fn_1_2188(void) {
    M427DllStruct2* temp_r31;
    s32 var_r30;

    temp_r31 = lbl_1_bss_40;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        espKill(temp_r31->unk0[var_r30]);
    }
    espKill(temp_r31->unkC);
}

void fn_1_21E8(s32 arg0, s32 arg1) {
    M427DllStruct2* temp_r31;
    s32 var_r30;

    temp_r31 = lbl_1_bss_40;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        if (arg0 == 0) {
            espDispOff(temp_r31->unk0[var_r30]);
        } else {
            espDispOn(temp_r31->unk0[var_r30]);
        }
    }
    if (arg1 != 0) {
        if (arg0 == 0) {
            espDispOff(temp_r31->unkC);
        } else {
            espDispOn(temp_r31->unkC);
        }
        if (arg0 == 0) {
            espDispOff(temp_r31->unk10);
        } else {
            espDispOn(temp_r31->unk10);
        }
        
        for (var_r30 = 0; var_r30 < 7; var_r30++) {
            if (arg0 == 0) {
                espDispOff(temp_r31->unk14[var_r30]);
            } else {
                espDispOn(temp_r31->unk14[var_r30]);
            }
        }
        
        for (var_r30 = 0; var_r30 < 7; var_r30++) {
            if (arg0 == 0) {
                espDispOff(temp_r31->unk30[var_r30]);
            } else {
                espDispOn(temp_r31->unk30[var_r30]);
            }
        }
    }
}

void fn_1_232C(s32 arg0) {
    M427DllStruct2* temp_r29;
    f32 temp_f0;
    s32 var_r31;

    temp_r29 = lbl_1_bss_40;
    temp_r29->unk9C = arg0;
    var_r31 = arg0 / 3600;
    arg0 -= var_r31 * 3600;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk14[0], var_r31);
    var_r31 = (arg0 / 600);
    arg0 -= var_r31 * 600;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk14[2], var_r31);
    var_r31 = arg0 / 60;
    arg0 -= var_r31 * 60;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk14[3], var_r31);
    arg0 = 100.0f * (arg0 / 60.0f);
    var_r31 = arg0 / 10;
    arg0 -= var_r31 * 10;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk14[5], var_r31);
    var_r31 = arg0;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk14[6], var_r31);
}

void fn_1_2518(s32 arg0) {
    M427DllStruct2* temp_r29;
    f32 temp_f0;
    s32 var_r31;

    temp_r29 = lbl_1_bss_40;
    temp_r29->unkA0 = arg0;
    var_r31 = arg0 / 3600;
    arg0 -= var_r31 * 3600;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk30[0], var_r31);
    var_r31 = (arg0 / 600);
    arg0 -= var_r31 * 600;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk30[2], var_r31);
    var_r31 = arg0 / 60;
    arg0 -= var_r31 * 60;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk30[3], var_r31);
    arg0 = 100.0f * (arg0 / 60.0f);
    var_r31 = arg0 / 10;
    arg0 -= var_r31 * 10;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk30[5], var_r31);
    var_r31 = arg0;
    if (var_r31 > 9) {
        var_r31 = 9;
    } else if (var_r31 < 0) {
        var_r31 = 0;
    }
    espBankSet(temp_r29->unk30[6], var_r31);
}

void fn_1_2704(void) {
    M427DllStruct2* var_r31;

    var_r31 = lbl_1_bss_40;
    var_r31->unk8C = 0;
}

void fn_1_272C(void) {
    M427DllStruct2* var_r31;
    s32 temp_r30;

    var_r31 = lbl_1_bss_40;
    temp_r30 = var_r31->unkC;
    espTPLvlSet(temp_r30, 0.5);
    espColorSet(temp_r30, 0, 0, 0);
}

void fn_1_2790(void) {
    omObjData* var_r30;
    s32 var_r31;

    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, -1.0f, 300.0f, 50000.0f, 0.6f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 0x140, 0x1E0);
    Hu3DCameraCreate(2);
    Hu3DCameraPerspectiveSet(2, -1.0f, 300.0f, 50000.0f, 0.6f);
    Hu3DCameraViewportSet(2, 320.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 0x140, 0, 0x140, 0x1E0);
    Hu3DCameraCreate(4);
    Hu3DCameraPerspectiveSet(4, -1.0f, 100.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(4, 0.0f, 0.0f, 576.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(4, 0, 0, 0x280, 0x1E0);
    var_r30 = lbl_1_bss_48 = omAddObjEx(lbl_1_bss_8C, 0x7FDA, 0, 0, -1, omOutViewMulti);
    var_r30->work[0] = 3;
    
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        CRotM[var_r31].x = lbl_1_data_0[0].rot.x;
        CRotM[var_r31].y = lbl_1_data_0[0].rot.y;
        CRotM[var_r31].z = lbl_1_data_0[0].rot.z;
        CenterM[var_r31].x = lbl_1_data_0[0].cen.x;
        CenterM[var_r31].y = lbl_1_data_0[0].cen.y;
        CenterM[var_r31].z = lbl_1_data_0[0].cen.z;
        CZoomM[var_r31] = lbl_1_data_0[0].zoom;
    }
    lbl_1_bss_44 = 0;
    omAddObjEx(lbl_1_bss_8C, 0x3F, 0, 0, -1, fn_1_2B20);
}

void fn_1_2B20(omObjData* object) {}

void fn_1_2B24(void) {}

void fn_1_2B28(void) {
    s32 var_r31;

    Hu3DCameraPerspectiveSet(1, 45.0f, 300.0f, 50000.0f, 0.6f);
    Hu3DCameraPerspectiveSet(2, 45.0f, 300.0f, 50000.0f, 0.6f);
    Hu3DCameraPerspectiveSet(4, 45.0f, 100.0f, 50000.0f, 1.2f);
    
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        CRotM[var_r31].x = lbl_1_data_0[2].rot.x;
        CRotM[var_r31].y = lbl_1_data_0[2].rot.y;
        CRotM[var_r31].z = lbl_1_data_0[2].rot.z;
        CenterM[var_r31].x = lbl_1_data_0[2].cen.x;
        CenterM[var_r31].y = lbl_1_data_0[2].cen.y;
        CenterM[var_r31].z = lbl_1_data_0[2].cen.z;
        CZoomM[var_r31] = lbl_1_data_0[2].zoom;
    }
}

void fn_1_2CE8(f32 arg0) {
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        CRotM[var_r31].x = fn_1_168FC(arg0, lbl_1_data_0[2].rot.x, lbl_1_data_0->rot.x);
        CRotM[var_r31].y = fn_1_168FC(arg0, lbl_1_data_0[2].rot.y, lbl_1_data_0->rot.z);
        CRotM[var_r31].z = fn_1_168FC(arg0, lbl_1_data_0[2].rot.z, lbl_1_data_0->rot.z);
        CenterM[var_r31].x = lbl_1_data_0[2].cen.x + (arg0 * (lbl_1_data_0->cen.x - lbl_1_data_0[2].cen.x));
        CenterM[var_r31].y = lbl_1_data_0[2].cen.y + (arg0 * (lbl_1_data_0->cen.y - lbl_1_data_0[2].cen.y));
        CenterM[var_r31].z = lbl_1_data_0[2].cen.z + (arg0 * (lbl_1_data_0->cen.z - lbl_1_data_0[2].cen.z));
        CZoomM[var_r31] = lbl_1_data_0[2].zoom + (arg0 * (lbl_1_data_0->zoom - lbl_1_data_0[2].zoom));
    }
}

void fn_1_2EE0(void) {
    Hu3DCameraPerspectiveSet(1, 45.0f, 700.0f, 50000.0f, 0.6f);
    Hu3DCameraPerspectiveSet(2, 45.0f, 700.0f, 50000.0f, 0.6f);
}

void fn_1_2F6C(f32 arg0) {
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        CRotM[var_r31].x = fn_1_168FC(arg0, lbl_1_data_0[1].rot.x, lbl_1_data_0[3].rot.x);
        CRotM[var_r31].y = fn_1_168FC(arg0, lbl_1_data_0[1].rot.y, lbl_1_data_0[3].rot.y);
        CRotM[var_r31].z = fn_1_168FC(arg0, lbl_1_data_0[1].rot.z, lbl_1_data_0[3].rot.z);
        CenterM[var_r31].x = lbl_1_data_0[1].cen.x + (arg0 * (lbl_1_data_0[3].cen.x - lbl_1_data_0[1].cen.x));
        CenterM[var_r31].y = lbl_1_data_0[1].cen.y + (arg0 * (lbl_1_data_0[3].cen.y - lbl_1_data_0[1].cen.y));
        CenterM[var_r31].z = lbl_1_data_0[1].cen.z + (arg0 * (lbl_1_data_0[3].cen.z - lbl_1_data_0[1].cen.z));
        CZoomM[var_r31] = lbl_1_data_0[1].zoom + (arg0 * (lbl_1_data_0[3].zoom - lbl_1_data_0[1].zoom));
    }
}

void fn_1_3164(void) {
    lbl_1_bss_48->work[0] = 1;
    Hu3DCameraKill(2);
    Hu3DCameraKill(4);
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 0x280, 0x1E0);
    CRotM->x = lbl_1_data_0[1].rot.x;
    CRotM->y = lbl_1_data_0[1].rot.y;
    CRotM->z = lbl_1_data_0[1].rot.z;
    CenterM->x = lbl_1_data_0[1].cen.x;
    CenterM->y = lbl_1_data_0[1].cen.y;
    CenterM->z = lbl_1_data_0[1].cen.z;
    *CZoomM = lbl_1_data_0[1].zoom;
}

s32 fn_1_32EC(void) {
    return 0;
}
