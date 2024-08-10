#include "REL/m446Dll.h"

#include "game/hsfman.h"
#include "math.h"

// data
m446Func4 lbl_1_data_150[3] = {NULL, fn_1_2AA8, fn_1_2DA8};
static const s32 lbl_1_rodata_58[5] = {0x4D0001, 0x4D0002, 0x4D0003, 0x4D0004, 0x4D0000};
static const s32 lbl_1_rodata_6C[5] = {0x4D001B, 0x4D001C, 0x4D001D, 0x4D001E, 0x4D001E};

// bss
unkStruct3* lbl_1_bss_18;

unkStruct2* fn_1_1C64(s32 arg0) {
    unkStruct2* temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, 0xC, 0x10000000U);
    if (!temp_r3) {
        return NULL;
    }
    temp_r3->unk0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * 4, 0x10000000U);
    if (!temp_r3->unk0) {
        HuMemDirectFree(temp_r3);
        return NULL;
    }
    temp_r3->unk4 = arg0;
    temp_r3->unk8 = 0;
    return temp_r3;
}

void fn_1_1CF8(unkStruct2* arg0) {
    HuMemDirectFree(arg0->unk0);
    HuMemDirectFree(arg0);
}

s32 fn_1_1D30(unkStruct2* arg0, void* arg1) {
    if (arg0->unk4 <= arg0->unk8) {
        return 0;
    } else {
        arg0->unk0[arg0->unk8] = arg1;
        arg0->unk8++;
        return 1;
    }
}

s32 fn_1_1D6C(unkStruct2* arg0, unkStruct4** arg1) {
    if (arg0->unk8 <= 0) {
        return 0;
    } else {
        arg0->unk8--;
        *arg1 = arg0->unk0[arg0->unk8];
        return 1;
    }
}

s32 fn_1_1DA8(unkStruct2* arg0, void** arg1) {
    if (arg0->unk8 <= 0) {
        return 0;
    } else {
        *arg1 = *(&arg0->unk0[arg0->unk8] - 1);
        return 1;
    }
}

BOOL fn_1_1DDC(unkStruct2* arg0) {
    return arg0->unk8 == 0;
}

s32 fn_1_1DEC(unkStruct2* arg0) {
    return arg0->unk8;
}

#pragma dont_inline on

unkStruct3* fn_1_1DF4(void* arg0) {
    unkStruct3* temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, 0xC, 0x10000000);
    if (!temp_r3) {
        return NULL;
    }
    temp_r3->unk4 = NULL;
    temp_r3->unk8 = NULL;
    temp_r3->unk0 = arg0;
    return temp_r3;
}

void fn_1_1E5C(unkStruct3* arg0) {
    HuMemDirectFree(arg0);
}

void fn_1_1E84(unkStruct3** arg0) {
    unkStruct3 *temp = *arg0;
    HuMemDirectFree(temp);
    *arg0 = NULL;
}

void fn_1_1EC8(unkStruct3* arg0, unkStruct3* arg1) {
    if (arg0) {
        arg1->unk8 = arg0->unk8;
        arg1->unk4 = arg0;
        arg0->unk8 = arg1;
        if (arg1->unk8) {
            arg1->unk8->unk4 = arg1;
        }
    } else {
        arg1->unk4 = arg1;
        arg1->unk8 = arg1;
    }
}

void fn_1_1F04(unkStruct3* arg0) {
    if (arg0->unk8) {
        arg0->unk8->unk4 = arg0->unk4;
    }
    if (arg0->unk4) {
        arg0->unk4->unk8 = arg0->unk8;
    }
}

#pragma dont_inline reset

void fn_1_1F38(u8* arg0, u8* arg1, s32 arg2) {
    u8* var_r30 = arg0;
    u8* var_r31 = arg1;
    if (arg2 <= 0) {
        return;
    }
    while (arg2-- != 0) {
        *var_r30 = *var_r31++;
        *var_r30++;
    }
}

void fn_1_1F84(u8* arg0, s8 arg1, s32 arg2) {
    u8* var_r30 = arg0;
    if (arg2 <= 0) {
        return;
    }
    while (arg2-- != 0) {
        *var_r30 = arg1;
        *var_r30++;
    }
}

void fn_1_1FC0(u8* arg0, s32 arg1) {
    u8* var_r30 = arg0;
    if (arg1 <= 0) {
        return;
    }
    while (arg1-- != 0) {
        *var_r30 = 0;
        *var_r30++;
    }
}

s32 fn_1_1FFC(s8* arg0, s8* arg1, s32 arg2) {
    s8* var_r30 = arg0;
    s8* var_r31 = arg1;
    
    if (arg2 <= 0) {
        return 0;
    }
    while (*var_r30 == *var_r31) {
        var_r30++;
        var_r31++;
    }
    return *var_r30 - *var_r31;
}

s32 fn_1_2064(void) {
    lbl_1_bss_18 = 0;
    return 1;
}

void fn_1_207C(void) {
    unkStruct4* var_r30;
    unkStruct3* var_r31;

    var_r31 = lbl_1_bss_18;
    if (var_r31) {
        do {
            var_r30 = var_r31->unk0;
            fn_1_2688(var_r30);
            var_r31 = var_r31->unk8;
        } while (var_r31);
    }
}

void fn_1_20D4(void) {
    m446Func1 *temp_r4;
    f32 temp_f31;
    s32 temp_r5;
    unkStruct4* temp_r31;
    unkStruct3* var_r30;

    var_r30 = lbl_1_bss_18;
    if (var_r30) {
        do {
            temp_r31 = var_r30->unk0;
            if (lbl_1_data_150[temp_r31->unk4]) {
                lbl_1_data_150[temp_r31->unk4](temp_r31);
            }
            if (temp_r31->unk70 != 0) {
                if (temp_r31->unk7C > 0) {
                    temp_r31->unk7C--;
                } else {
                    temp_f31 = sin((M_PI * (90.0f * temp_r31->unk80)) / 180.0);
                    temp_r31->unk10.x = temp_r31->unk1C.x + (temp_f31 * (temp_r31->unk28.x - temp_r31->unk1C.x));
                    temp_r31->unk10.y = temp_r31->unk1C.y + (temp_f31 * (temp_r31->unk28.y - temp_r31->unk1C.y));
                    temp_r31->unk10.z = temp_r31->unk1C.z + (temp_f31 * (temp_r31->unk28.z - temp_r31->unk1C.z));
                    temp_r31->unk80 = temp_r31->unk80 + temp_r31->unk84;
                    if (temp_r31->unk80 >= 1.0f) {
                        temp_r31->unk10.x = temp_r31->unk28.x;
                        temp_r31->unk10.y = temp_r31->unk28.y;
                        temp_r31->unk10.z = temp_r31->unk28.z;
                        temp_r31->unk70 = 0;
                    }
                }
            }
            if (temp_r31->unk74 != 0) {
                temp_f31 = sin((M_PI * (90.0f * temp_r31->unk88)) / 180.0);
                temp_r31->unk34.x = (temp_r31->unk40.x + (temp_f31 * (temp_r31->unk4C.x - temp_r31->unk40.x)));
                temp_r31->unk34.y = (temp_r31->unk40.y + (temp_f31 * (temp_r31->unk4C.y - temp_r31->unk40.y)));
                temp_r31->unk34.z = (temp_r31->unk40.z + (temp_f31 * (temp_r31->unk4C.z - temp_r31->unk40.z)));
                temp_r31->unk88 = (temp_r31->unk88 + temp_r31->unk8C);
                if (temp_r31->unk88 >= 1.0f) {
                    temp_r31->unk34.x = temp_r31->unk4C.x;
                    temp_r31->unk34.y = temp_r31->unk4C.y;
                    temp_r31->unk34.z = temp_r31->unk4C.z;
                    temp_r31->unk74 = 0;
                }
            }
            if (temp_r31->unk78 != 0) {
                temp_f31 = sin((M_PI * (90.0f * temp_r31->unk90)) / 180.0);
                temp_r31->unk58 = (temp_r31->unk5C + (temp_f31 * (temp_r31->unk60 - temp_r31->unk5C)));
                temp_r31->unk90 = (temp_r31->unk90 + temp_r31->unk94);
                if (temp_r31->unk90 >= 1.0f) {
                    temp_r31->unk58 = temp_r31->unk60;
                    temp_r31->unk78 = 0;
                }
            }
            fn_1_2F64(temp_r31);
            var_r30 = var_r30->unk8;
        } while (var_r30);
    }
}

unkStruct4* m446CardCreate(s32 arg0) {
    unkStruct4* temp_r31;
    unkStruct3* temp_r30;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x98, 0x10000000U);
    if (!temp_r31) {
        OSReport("[!] m446CardCreate ERROR...\n");
        return NULL;
    }
    temp_r31->unk0 = arg0;
    temp_r31->unk4 = 0;
    temp_r31->unk10.x = 0.0f;
    temp_r31->unk10.y = 0.0f;
    temp_r31->unk10.z = 0.0f;
    temp_r31->unk34.x = 0.0f;
    temp_r31->unk34.y = 0.0f;
    temp_r31->unk34.z = 180.0f;
    temp_r31->unk58 = 1.0f;
    temp_r31->unk64 = 0;
    temp_r31->unk68 = 1;
    temp_r31->unk6C = 0;
    temp_r31->unk70 = 0;
    temp_r31->unk74 = 0;
    temp_r31->unk78 = 0;
    temp_r31->unk7C = 0;
    temp_r31->unkA[0] = Hu3DModelCreateFile(lbl_1_rodata_58[arg0]);
    Hu3DModelAmbSet(temp_r31->unkA[0], 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowSet(temp_r31->unkA[0]);
    Hu3DModelLayerSet(temp_r31->unkA[0], 0);
    temp_r31->unkA[1] = Hu3DModelCreateFile(lbl_1_rodata_6C[arg0]);
    Hu3DModelAmbSet(temp_r31->unkA[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrSet(temp_r31->unkA[1], 0x40000001U);
    Hu3DModelLayerSet(temp_r31->unkA[0], 0);
    fn_1_2A58(temp_r31);
    fn_1_2EC0(temp_r31, 1);
    temp_r30 = fn_1_1DF4(temp_r31);
    if (!temp_r30) {
        OSReport("[!] m446CardCreate ERROR...\n");
        HuMemDirectFree(temp_r31);
        return NULL;
    }
    if (lbl_1_bss_18) {
        fn_1_1EC8(lbl_1_bss_18, temp_r30);
    } else {
        lbl_1_bss_18 = temp_r30;
    }
    return temp_r31;
}

void fn_1_2688(unkStruct4* arg0) {
    unkStruct3* var_r31 = lbl_1_bss_18;
    do {
        if (arg0 == var_r31->unk0) {
            if (var_r31 == lbl_1_bss_18) {
                lbl_1_bss_18 = var_r31->unk8;
            }
            fn_1_1F04(var_r31);
            fn_1_1E5C(var_r31);
            Hu3DModelKill(arg0->unkA[0]);
            Hu3DModelKill(arg0->unkA[1]);
            HuMemDirectFree(arg0);
            return;
        }
        var_r31 = var_r31->unk8;
    } while (var_r31);
}

void fn_1_272C(unkStruct4* arg0) {
    Vec sp8;

    sp8 = arg0->unk34;
    sp8.z = 0.0f;
    arg0->unk64 = 1;
    fn_1_2928(arg0, &sp8, 0x1E);
}

void fn_1_2794(unkStruct4* arg0) {
    Vec sp8;

    sp8 = arg0->unk34;
    sp8.z = 180.0f;
    arg0->unk64 = 0;
    fn_1_2928(arg0, &sp8, 0x3C);
}

void fn_1_27FC(unkStruct4* arg0, Vec* arg1, s32 arg2) {
    arg0->unk7C = 0;
    arg0->unk28 = *arg1;
    arg0->unk1C = arg0->unk10;
    arg0->unk80 = 0.0f;
    arg0->unk84 = (1.0f / arg2);
    arg0->unk70 = 1;
}

void fn_1_2890(unkStruct4* arg0, Vec* arg1, s32 arg2, s32 arg3) {
    arg0->unk7C = 0;
    arg0->unk28 = *arg1;
    arg0->unk1C = arg0->unk10;
    arg0->unk80 = 0.0f;
    arg0->unk84 = (1.0f / arg2);
    arg0->unk70 = 1;
    arg0->unk7C = arg3;
}

void fn_1_2928(unkStruct4* arg0, Vec* arg1, s32 arg2) {
    arg0->unk4C = *arg1;
    arg0->unk40 = arg0->unk34;
    arg0->unk88 = 0.0f;
    arg0->unk8C = (1.0f / arg2);
    arg0->unk74 = 1;
}

void fn_1_29B4(unkStruct4* arg0, f32 arg8, s32 arg1) {
    arg0->unk60 = arg8;
    arg0->unk5C = arg0->unk58;
    arg0->unk90 = 0.0f;
    arg0->unk94 = (1.0f / arg1);
    arg0->unk78 = 1;
}

void fn_1_2A1C(unkStruct4* arg0) {
    Hu3DModelAttrReset(arg0->unkA[1], 1);
    arg0->unk6C = 1;
}

void fn_1_2A58(unkStruct4* arg0) {
    Hu3DModelAttrSet(arg0->unkA[1], 1);
    arg0->unk6C = 0;
}

void fn_1_2A94(unkStruct4* arg0) {
    arg0->unk4 = 1;
    arg0->unk8 = 0;
}

void fn_1_2AA8(unkStruct4* arg0) {
    Vec sp8;
    
    switch (arg0->unk8) {
        case 0:
            arg0->unk8 = 1;
            Hu3DModelAttrReset(arg0->unkA[1], 1);
            arg0->unk6C = 1;
            arg0->unk8 = 1; // ?
        case 1:
            arg0->unk60 = 2.5f;
            arg0->unk5C = arg0->unk58;
            arg0->unk90 = 0.0f;
            arg0->unk94 = 0.055555556f;
            arg0->unk78 = 1;
            arg0->unk8 = 2; // ?????
            break;
        
        case 2:
            if (arg0->unk78 != 0) break;
            arg0->unk8 = 3; // ??????????
        case 3:
            arg0->unk60 = 1.5f;
            arg0->unk5C = arg0->unk58;
            arg0->unk90 = 0.0f;
            arg0->unk94 = 0.055555556f;
            arg0->unk78 = 1;
            arg0->unk8 = 4;
            break;
        
        case 4:
            if (arg0->unk78 != 0) break;
            arg0->unk8 = 5;
        case 5:
            arg0->unk60 = 2.5f;
            arg0->unk5C = arg0->unk58;
            arg0->unk90 = 0.0f;
            arg0->unk94 = 0.055555556f;
            arg0->unk78 = 1;
            arg0->unk8 = 6;
            break;
        
        case 6:
            if (arg0->unk78 != 0) break;
            arg0->unk8 = 8;
        case 7:
            arg0->unk60 = 1.5f;
            arg0->unk5C = arg0->unk58;
            arg0->unk90 = 0.0f;
            arg0->unk94 = 0.055555556f;
            arg0->unk78 = 1;
            arg0->unk8 = 8;
        case 8:
            if (arg0->unk78 != 0) break;
            arg0->unk8 = 9;
        case 9:
            sp8 = arg0->unk34;
            sp8.y = 720.0f;
            arg0->unk4C = sp8;
            arg0->unk40 = arg0->unk34;
            arg0->unk88 = 0.0f;
            arg0->unk8C = 0.016666668f;
            arg0->unk74 = 1;
            arg0->unk60 = 0.0f;
            arg0->unk5C = arg0->unk58;
            arg0->unk90 = 0.0f;
            arg0->unk94 = 0.016666668f;
            arg0->unk78 = 1;
            arg0->unk8 = 10;
            break;
        case 10:
            if (arg0->unk78 != 0) break;
            arg0->unk4 = 0;
            arg0->unk8 = 0;
            Hu3DModelAttrSet(arg0->unkA[1], 1);
            arg0->unk6C = 0;
            return;
    }
}

void fn_1_2D94(unkStruct4* arg0) {
    arg0->unk4 = 2;
    arg0->unk8 = 0;
}

void fn_1_2DA8(unkStruct4* arg0) {
    f32 var_f31;
    f32 var_f30;
    
    switch (arg0->unk8) {
        case 0:
            arg0->unk8 = 1;
        case 1:
            if (arg0->unk78 == 0) {
                var_f31 = arg0->unk58 + 0.25f;
                arg0->unk60 = var_f31;
                arg0->unk5C = arg0->unk58;
                arg0->unk90 = 0.0f;
                arg0->unk94 = 0.033333335f;
                arg0->unk78 = 1;
                arg0->unk8 = 2U;
            }
            break;
        case 2:
            if (arg0->unk78 == 0) {
                var_f30 = arg0->unk58 - 0.25f;
                arg0->unk60 = var_f30;
                arg0->unk5C = arg0->unk58;
                arg0->unk90 = 0.0f;
                arg0->unk94 = 0.033333335f;
                arg0->unk78 = 1;
                arg0->unk8 = 1;
            }
            break;
    }
}

void fn_1_2EC0(unkStruct4* arg0, s32 arg1) {
    if (arg1 != 0) {
        Hu3DModelShadowDispOn(arg0->unkA[0]);
        Hu3DModelAmbSet(arg0->unkA[0], 0.0f, 0.0f, 0.0f);
        return;
    }
    Hu3DModelShadowDispOff(arg0->unkA[0]);
    Hu3DModelAmbSet(arg0->unkA[0], 1.0f, 1.0f, 1.0f);
}

void fn_1_2F64(unkStruct4* arg0) {
    if ((arg0->unk58 > 1.0f) || (arg0->unk58 < 1.0f)) {
        Hu3DModelLayerSet(arg0->unkA[0], 1);
        Hu3DModelLayerSet(arg0->unkA[1], 1);
    } else {
        Hu3DModelLayerSet(arg0->unkA[0], 0);
        Hu3DModelLayerSet(arg0->unkA[1], 0);
    }
    Hu3DModelPosSet(arg0->unkA[0], arg0->unk10.x, arg0->unk10.y, arg0->unk10.z);
    Hu3DModelPosSet(arg0->unkA[1], arg0->unk10.x, 0.1f + arg0->unk10.y, arg0->unk10.z);
    Hu3DModelScaleSet(arg0->unkA[0], arg0->unk58, arg0->unk58, arg0->unk58);
    Hu3DModelScaleSet(arg0->unkA[1], arg0->unk58, arg0->unk58, arg0->unk58);
    Hu3DModelRotSet(arg0->unkA[0], arg0->unk34.x, arg0->unk34.y, arg0->unk34.z);
}