#include "REL/m446Dll.h"

#include "math.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/chrman.h"
#include "game/pad.h"
#include "game/objsub.h"

// cursor.c
extern unkStruct7 *m446CursorCreate(s32);
extern void fn_1_76E8(unkStruct7*);
extern void fn_1_77C8(unkStruct7*, u8);

// bss
unkStruct3 *lbl_1_bss_30;

// data
s32 lbl_1_data_228[9] = {
    0x4D000A, 0x4D000B, 0x4D000C,
    0x4D000D, 0x4D000E, 0x4D000F,
    0x4D0010, 0x4D0011, 0x4D0021
};
s32 lbl_1_data_24C[9][4] = {
    { 0x5F0000, 0x5F0036, 0x5F0017, 0x5F0072 },
    { 0x1A0000, 0x1A0036, 0x1A0017, 0x1A0072 },
    { 0x6D0000, 0x6D0036, 0x6D0017, 0x6D0072 },
    { 0x8A0000, 0x8A0036, 0x8A0017, 0x8A0072 },
    { 0x850000, 0x850036, 0x850017, 0x850072 },
    { 0x110000, 0x110036, 0x110017, 0x110072 },
    { 0x0D0000, 0x0D0036, 0x0D0017, 0x0D0072 },
    { 0x810000, 0x810036, 0x810017, 0x810072 },
    { 0x4D0022, 0x4D0023, 0x4D0025, 0x4D0024 }
};
m446Func8 lbl_1_data_2DC[5] = {NULL, fn_1_5B48, fn_1_5C24, fn_1_5D00, fn_1_6074};

s32 fn_1_480C(void) {
    lbl_1_bss_30 = 0;
    return 1;
}

void fn_1_4824(void) {
    unkStruct3* var_r31;
    void* var_r30;

    var_r31 = lbl_1_bss_30;
    if (var_r31) {
        do {
            var_r30 = var_r31->unk0;
            fn_1_509C(var_r30);
            var_r31 = var_r31->unk8;
        } while (var_r31);
    }
}

void fn_1_487C(void) {
    f32 temp_f31;
    unkStruct8* temp_r31;
    unkStruct3* var_r30;

    var_r30 = lbl_1_bss_30;
    if (var_r30) {
        do {
            temp_r31 = var_r30->unk0;
            if (lbl_1_data_2DC[temp_r31->unk18]) {
                lbl_1_data_2DC[temp_r31->unk18](temp_r31);
            }
            if (temp_r31->unkB4 != 0) {
                temp_f31 = sin((M_PI * (90.0f * temp_r31->unkC0)) / 180.0);
                temp_f31 *= temp_f31;
                temp_r31->unk48.x = (temp_r31->unk9C.x + (temp_f31 * (temp_r31->unkA8.x - temp_r31->unk9C.x)));
                temp_r31->unk48.y = (temp_r31->unk9C.y + (temp_f31 * (temp_r31->unkA8.y - temp_r31->unk9C.y)));
                temp_r31->unk48.z = (temp_r31->unk9C.z + (temp_f31 * (temp_r31->unkA8.z - temp_r31->unk9C.z)));
                temp_r31->unkC0 += temp_r31->unkC4;
                if (temp_r31->unkC0 >= 1.0f) {
                    temp_r31->unk48.x = temp_r31->unkA8.x;
                    temp_r31->unk48.y = temp_r31->unkA8.y;
                    temp_r31->unk48.z = temp_r31->unkA8.z;
                    temp_r31->unkB4 = 0;
                }
            }
            if (temp_r31->unk98 != 0) {
                temp_f31 = sin((M_PI * (90.0f * temp_r31->unkB8)) / 180.0);
                temp_f31 *= temp_f31;
                temp_r31->unk54.x = (temp_r31->unk80.x + (temp_f31 * (temp_r31->unk8C.x - temp_r31->unk80.x)));
                temp_r31->unk54.y = (temp_r31->unk80.y + (temp_f31 * (temp_r31->unk8C.y - temp_r31->unk80.y)));
                temp_r31->unk54.z = (temp_r31->unk80.z + (temp_f31 * (temp_r31->unk8C.z - temp_r31->unk80.z)));
                temp_r31->unkB8 = (temp_r31->unkB8 + temp_r31->unkBC);
                if (temp_r31->unkB8 >= 1.0f) {
                    temp_r31->unk54.x = temp_r31->unk8C.x;
                    temp_r31->unk54.y = temp_r31->unk8C.y;
                    temp_r31->unk54.z = temp_r31->unk8C.z;
                    temp_r31->unk98 = 0;
                }
            }
            fn_1_6578(temp_r31);
            var_r30 = var_r30->unk8;
        } while (var_r30);
    }
}

unkStruct8* m446PlayerCreate(s32 arg0, unkStruct6* arg1) {
    f32 var_f31;
    s32 var_r27;
    s32 var_r26;
    s16 var_r25;
    s16 var_r24;
    unkStruct3* var_r28;
    s32 var_r30;
    unkStruct8* var_r31;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, 0xCC, 0x10000000);
    if (!var_r31) {
        return NULL;
    }
    var_r31->unk0 = arg0;
    if (GWPlayerCfg[arg0].iscom != 0) {
        var_r27 = 1;
    } else {
        var_r27 = 0;
    }
    var_r31->unk68 = var_r27;
    var_r31->unk4 = arg1;
    if (GWPlayerCfg[arg0].character == 0xB) {
        var_r26 = 1;
    } else {
        var_r26 = 0;
    }
    var_r31->unk70 = var_r26;
    if (var_r31->unk70 != 0) {
        var_r25 = 8;
    } else {
        var_r25 = GWPlayerCfg[arg0].character;
    }
    var_r31->unk64 = var_r25;
    if (var_r31->unk68 != 0) {
        var_r24 = 4;
    } else {
        var_r24 = GWPlayerCfg[arg0].pad_idx;
    }
    var_r31->unk66 = var_r24;
    var_r31->unk65 = GWPlayerCfg[arg0].diff;
    var_r31->unk6C = 0;
    var_r31->unkC = 0;
    var_r31->unk10 = 2;
    var_r31->unk48.x = 0.0f;
    if (var_r31->unk70 != 0) {
        var_f31 = 70.0f;
    } else {
        var_f31 = 0.0f;
    }
    var_r31->unk48.y = var_f31;
    var_r31->unk48.z = 0.0f;
    var_r31->unk54.x = 0.0f;
    var_r31->unk54.y = 0.0f;
    var_r31->unk54.z = 0.0f;
    var_r31->unk60 = 1.0f;
    var_r31->unk38 = 0;
    var_r31->unk24 = 0;
    var_r31->unk74 = 0;
    var_r31->unk18 = 0;
    var_r31->unk1C = 0;
    var_r31->unk98 = 0;
    var_r31->unkB4 = 0;
    
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        var_r31->unk2C[var_r30] = NULL;
    }
    var_r31->unk8 = m446CursorCreate(1);
    if (!var_r31->unk8) {
        HuMemDirectFree(var_r31);
        return NULL;
    }
    fn_1_7884(var_r31->unk8);
    switch (var_r31->unk0) {
    case 0:
        var_r31->unk48.z = 150.0f;
        var_r31->unk54.y = 180.0f;
        break;
    case 1:
        var_r31->unk48.z = -150.0f;
        var_r31->unk54.y = 0.0f;
        break;
    }
    if (var_r31->unk70 != 0) {
        var_r31->unk3C[0] = Hu3DModelCreateFile(0x4D0020);
        var_r31->unk3C[1] = Hu3DModelCreateFile(0x4D0021);
    } else {
        var_r31->unk3C[0] = CharModelCreate(var_r31->unk64, 2);
        var_r31->unk3C[1] = Hu3DModelCreateFile(lbl_1_data_228[var_r31->unk64]);
    }
    Hu3DModelAmbSet(var_r31->unk3C[0], 0.0f, 0.0f, 0.0f);
    Hu3DModelAmbSet(var_r31->unk3C[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowSet(var_r31->unk3C[0]);
    Hu3DModelShadowSet(var_r31->unk3C[1]);
    Hu3DModelPosSet(var_r31->unk3C[1], 0.0f, 100.0f, 0.0f);
    Hu3DModelAttrReset(var_r31->unk3C[1], 0x40000001);
    Hu3DModelAttrSet(var_r31->unk3C[1], 1);
    Hu3DModelPosSet(var_r31->unk3C[1], 2000.0f, 2000.0f, 2000.0f);
    fn_1_637C(var_r31, 0);
    
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        if (var_r31->unk70 != 0) {
            var_r31->unk40[var_r30] = Hu3DJointMotionFile(var_r31->unk3C[0], lbl_1_data_24C[var_r31->unk64][var_r30]);
        } else {
            var_r31->unk40[var_r30] = CharModelMotionCreate(var_r31->unk64, lbl_1_data_24C[var_r31->unk64][var_r30]);
        }
    }
    if (var_r31->unk70 == 0) {
        CharModelMotionDataClose(var_r31->unk64);
    }
    if (var_r31->unk70 != 0) {
        Hu3DMotionSet(var_r31->unk3C[0], var_r31->unk40[0]);
    } else {
        CharModelMotionSet(var_r31->unk64, var_r31->unk40[0]);
    }
    Hu3DModelAttrSet(var_r31->unk3C[0], 0x40000001);
    var_r28 = fn_1_1DF4(var_r31);
    if (!var_r28) {
        OSReport("[!] m446PlayerCreate ERROR...\n");
        HuMemDirectFree(var_r31);
        return NULL;
    }
    if (lbl_1_bss_30) {
        fn_1_1EC8(lbl_1_bss_30, var_r28);
    } else {
        lbl_1_bss_30 = var_r28;
    }
    return var_r31;
}

void fn_1_509C(unkStruct8* arg0) {
    s32 var_r29;
    unkStruct3* var_r30;

    var_r30 = lbl_1_bss_30;
    
    do {
        if (arg0 == var_r30->unk0) {
            if (var_r30 == lbl_1_bss_30) {
                lbl_1_bss_30 = var_r30->unk8;
            }
            fn_1_1F04(var_r30);
            fn_1_1E5C(var_r30);
            
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                if (arg0->unk70 != 0) {
                    Hu3DMotionKill(arg0->unk40[var_r29]);
                } else {
                    CharModelMotionKill(arg0->unk64, arg0->unk40[var_r29]);
                }
            }
            if (arg0->unk70 != 0) {
                Hu3DModelKill(arg0->unk3C[0]);
                Hu3DModelKill(arg0->unk3C[1]);
            } else {
                CharModelKill(arg0->unk64);
                Hu3DModelKill(arg0->unk3C[1]);
            }
            fn_1_76E8(arg0->unk8);
            HuMemDirectFree(arg0);
            break;
        }
        var_r30 = var_r30->unk8;
    } while (var_r30);
}

s32 m446PlayerAppendCard(unkStruct8* arg0, unkStruct4* arg1, s32 arg2) {
    Vec sp18;
    Vec spC;
    s32 temp_r0_2;
    s32 temp_r28;
    s32 temp_r27;
    s32 var_r29;

    if (arg0->unk38 >= 3) {
        OSReport("m446PlayerAppendCard ERROR...\n");
        return 0;
    }
    
    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        if (!arg0->unk2C[var_r29]) {
            break;
        }
    }
    
    if (var_r29 == 3) {
        OSReport("m446PlayerAppendCard ERROR...\n");
        return 0;
    }
    arg0->unk2C[var_r29] = arg1;
    arg0->unk38++;
    sp18.y = 86.0f;
    switch (arg0->unk0) {
        case 0:
            sp18.x = -30.0f + (30.0f * var_r29);
            sp18.z = 45.0f;
            break;
        case 1:
            sp18.x = 30.0f - (30.0f * var_r29);
            sp18.z = -45.0f;
            break;
    }
    
    spC = arg1->unk34;
    switch (arg0->unk0) {
    case 0:
        spC.y = 0.0f;
        break;
    case 1:
        spC.y = 180.0f;
        break;
    }
    switch (arg2) {
        case 0:
            arg1->unk10 = sp18;
            arg1->unk34 = spC;
            arg1->unk58 = 1.5f;
            fn_1_272C(arg1);
            break;
        case 1:
            fn_1_27FC(arg1, &sp18, 0x3C);
            fn_1_2928(arg1, &spC, 0x1E);
            fn_1_29B4(arg1, 1.5f, 0x1E);
            break;
        case 4:
            fn_1_27FC(arg1, &sp18, 0x1E);
            fn_1_2928(arg1, &spC, 0x1E);
            fn_1_29B4(arg1, 1.5f, 0x1E);
            break;
    }
    temp_r28 = arg0->unk24;
    temp_r27 = arg0->unk20;
    fn_1_6620(arg0);
    if ((arg0->unk24 != 0) && (temp_r28 == 0)) {
        HuAudFXPlay(0x76B);
        fn_1_64BC(arg0, 1, 0x3C);
    } else if ((arg0->unk20 != 0) && (temp_r27 == 0)) {
        HuAudFXPlay(0x76B);
        fn_1_64BC(arg0, 0, 0x3C);
    }
    return 1;
}

s32 m446PlayerRemoveCard(unkStruct8* arg0, unkStruct4* arg1, s32 arg2) {
    Vec spC;
    s32 var_r30;

    if (arg0->unk38 <= 0) {
        OSReport("m446PlayerRemoveCard ERROR...\n");
        return 0;
    }
    
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        if (arg0->unk2C[var_r30] == arg1) {
            break;
        }
    }
    if (var_r30 == 3) {
        OSReport("m446PlayerRemoveCard ERROR...\n");
        return 0;
    }
    arg0->unk2C[var_r30] = NULL;
    arg0->unk38--;
    fn_1_2A58(arg1);
    fn_1_6620(arg0);
    switch (arg2) {
        case 3:
            spC = arg1->unk10;
            spC.y = 86.0f;
            spC.z = 0.0f;
            fn_1_2890(arg1, &spC, 0x1E, 0x21);
            fn_1_5E54(arg0, var_r30);
            break;
    }
    return 1;
}

s32 fn_1_5648(unkStruct8* arg0, s32 arg1, unkStruct4** arg2) {
    if ((arg1 < 0) || (arg1 >= 3)) {
        return 0;
    }
    *arg2 = arg0->unk2C[arg1];
    return 1;
}

s32 fn_1_5678(unkStruct8* arg0, unkStruct4** arg1, s32 arg2) {
    s32 sp14[3];
    Vec sp8;
    s32 var_r28;
    s32 var_r30;
    s32 var_r25;
    s32 var_r24;
    s32 var_r27;
    s32 var_r26;
    unkStruct4* var_r29;

    var_r27 = 0;
    var_r26 = 0;
    var_r25 = 0;
    *arg1 = NULL;
    if (arg0->unk68 != 0) {
        if (arg0->unk6C == 0) {
            if (arg0->unk20 != 0) {
                var_r24 = fn_1_4720(arg0->unk4, arg0->unk28);
                if (var_r24 >= 1) {
                    for (var_r30 = 0; var_r30 < 3; var_r30++) {
                        var_r29 = arg0->unk2C[var_r30];
                        if (var_r29->unk0 != arg0->unk28) {
                            arg0->unk74 = var_r30;
                            break;
                        }
                    }
                } else {
                    for (var_r30 = 0; var_r30 < 3; var_r30++) {
                        var_r29 = arg0->unk2C[var_r30];
                        if (var_r29->unk0 != arg0->unk28) {
                            break;
                        }
                    }
                    
                    var_r24 = fn_1_4720(arg0->unk4, var_r29->unk0);
                    if (var_r24 >= 2) {
                        for (var_r30 = 0; var_r30 < 3; var_r30++) {
                            var_r29 = arg0->unk2C[var_r30];
                            if (var_r29->unk0 == arg0->unk28) {
                                arg0->unk74 = var_r30;
                                break;
                            }
                        }
                    } else {
                        arg0->unk74 = (fn_1_38F0() % 3);
                    }
                }
            } else {
                for (var_r30 = 0; var_r30 < 3; var_r30++) {
                    var_r29 = arg0->unk2C[var_r30];
                    sp14[var_r30] = fn_1_4720(arg0->unk4, var_r29->unk0);
                }
                for (var_r28 = 0; var_r28 < 5; var_r28++) {
                    for (var_r30 = 0; var_r30 < 3; var_r30++) {
                        if (var_r28 == sp14[var_r30]) {
                            break;
                        }
                    }
                    if (var_r30 < 3) {
                        break;
                    }
                }
                if (var_r28 == 5) {
                    arg0->unk74 = (fn_1_38F0() % 3);
                } else {
                    arg0->unk74 = var_r30;
                }
            }
            arg0->unk6C = 1;
            arg0->unk7C = 0x1E;
        }
        if (arg0->unk7C > 0) {
            arg0->unk7C--;
        } else {
            var_r27 = arg0->unk74 < arg0->unk10;
            var_r26 = arg0->unk74 > arg0->unk10;
            var_r25 = arg0->unk74 == arg0->unk10;
            arg0->unk7C = 0x12;
        }
    } else {
        switch (arg0->unk0) {
        case 0:
            var_r27 = (HuPadDStkRep[arg0->unk66] & 1) != 0;
            var_r26 = (HuPadDStkRep[arg0->unk66] & 2) != 0;
            break;
        case 1:
            var_r27 = (HuPadDStkRep[arg0->unk66] & 2) != 0;
            var_r26 = (HuPadDStkRep[arg0->unk66] & 1) != 0;
            break;
        }
        var_r25 = (HuPadBtnDown[arg0->unk66] & 0x100) != 0;
    }
    if (arg2 == 0) {
        if (var_r27 != 0) {
            if (--arg0->unk10 < 0) {
                arg0->unk10 = 2;
            }
            HuAudFXPlay(0);
        }
        if (var_r26 != 0) {
            if (++arg0->unk10 > 2) {
                arg0->unk10 = 0;
            }
            HuAudFXPlay(0);
        }
    }
    var_r29 = arg0->unk2C[arg0->unk10];
    if (!var_r29) {
        return 0;
    }
    if (arg0->unk8->field00_bit0 == 0) {
        fn_1_77C8(arg0->unk8, arg0->unk64);
    }
    sp8 = var_r29->unk10;
    sp8.y++;
    arg0->unk8->unk20 = sp8;
    arg0->unk8->unk44 = 1.5f;
    if ((var_r25 != 0) || (arg2 != 0)) {
        HuAudFXPlay(0x769);
        *arg1 = var_r29;
        fn_1_7884(arg0->unk8);
        arg0->unk6C = 0;
        return 1;
    }
    return 0;
}

void fn_1_5B34(unkStruct8* arg0) {
    arg0->unk18 = 1;
    arg0->unk1C = 0;
}

static const s32 lbl_1_rodata_1C8[4] = {0, 1, 2, 3};

void fn_1_5B48(unkStruct8* arg0) {
    switch (arg0->unk1C) {
        case 0:
            if (arg0->unk70 != 0) {
                Hu3DMotionShiftSet(arg0->unk3C[0], arg0->unk40[2], 0.0f, 10.0f, 0);
            } else {
                CharModelMotionShiftSet(arg0->unk64, arg0->unk40[2], 0.0f, 10.0f, 0);
            }
            arg0->unk1C = 1;
            break;
        case 1:
            if (Hu3DMotionEndCheck(arg0->unk3C[0]) != 0) {
                arg0->unk18 = 0;
            }
    }
}

void fn_1_5C10(unkStruct8* arg0) {
    arg0->unk18 = 2;
    arg0->unk1C = 0;
}

void fn_1_5C24(unkStruct8* arg0) {
    switch (arg0->unk1C) {
        case 0:
            if (arg0->unk70 != 0) {
                Hu3DMotionShiftSet(arg0->unk3C[0], arg0->unk40[3], 0.0f, 10.0f, 0);
            } else {
                CharModelMotionShiftSet(arg0->unk64, arg0->unk40[3], 0.0f, 10.0f, 0);
            }
            arg0->unk1C = 1;
            break;
        case 1:
            if (Hu3DMotionEndCheck(arg0->unk3C[0]) != 0) {
                arg0->unk18 = 0;
            }
    }
}

void fn_1_5CEC(unkStruct8* arg0) {
    arg0->unk18 = 3;
    arg0->unk1C = 0;
}

void fn_1_5D00(unkStruct8* arg0) {
    Vec sp8;

    sp8 = arg0->unk54;
    switch (arg0->unk1C) {
        case 0:
            Hu3DModelAmbSet(arg0->unk3C[0], 0.8f, 0.8f, 0.8f);
            if (arg0->unk70 != 0) {
                Hu3DMotionShiftSet(arg0->unk3C[0], arg0->unk40[1], 0.0f, 10.0f, 0U);
            } else {
                CharModelMotionShiftSet(arg0->unk64, arg0->unk40[1], 0.0f, 10.0f, 0x40000001U);
                Hu3DMotionStartEndSet(arg0->unk3C[0], 0.0f, 59.0f);
            }
            sp8.y = 0.0f;
            fn_1_6264(arg0, &sp8, 0x3C);
            arg0->unk1C = 1;
            arg0->unk14 = 0;
            return;
        case 1:
            if (arg0->unk98 == 0) {
                arg0->unk18 = 0;
            }
    }
}

void fn_1_5E54(unkStruct8* arg0, s32 arg1) {
    Vec sp14;
    Vec sp8;
    f32 var_f31;
    f32 var_f30;
    f32 var_f29;

    if (arg0->unk70 != 0) {
        var_f31 = 95.0f;
    } else {
        var_f31 = 80.0f;
    }
    sp14.y = var_f31;
    
    switch (arg0->unk0) {
        case 0:
            sp14.x = -30.0f + (30.0f * arg1);
            sp14.z = 105.0f;
            sp8.x = 0.0f;
            sp8.y = 90.0f;
            sp8.z = 0.0f;
            break;
        case 1:
            sp14.x = 30.0f - (30.0f * arg1);
            if (arg0->unk70 != 0) {
                var_f30 = 30.0f;
            } else {
                var_f30 = 55.0f;
            }
            sp14.z = -50.0f - var_f30;
            sp8.x = 0.0f;
            if (arg0->unk70 != 0) {
                var_f29 = 180.0f;
            } else {
                var_f29 = -90.0f;
            }
            sp8.y = var_f29;
            sp8.z = 0.0f;
            break;
    }
    arg0->unk48 = sp14;
    arg0->unk54 = sp8;
    arg0->unk18 = 4;
    arg0->unk1C = 0;
}

void fn_1_6074(unkStruct8* arg0) {
    Vec sp8;
    f32 var_f31;
    f32 var_f30;
    
    switch (arg0->unk1C) {
        case 0:
            arg0->unk1C = 1;
            arg0->unk14 = 0;
        case 1:
            sp8 = arg0->unk48;
            if (arg0->unk0 == 0) {
                var_f31 = -25.0f;
            } else {
                var_f31 = 25.0f;
            }
            sp8.z += var_f31;
            fn_1_62F0(arg0, &sp8, 0x1E);

            arg0->unk1C = 2;
            arg0->unk14 = 0;
            break;
        case 2:
            if (arg0->unk14++ < 0x1E) break;
            arg0->unk1C = 3;
        case 3:
            Hu3DModelAttrSet(arg0->unk3C[1], 0x40000001);
            arg0->unk1C = 4;
            arg0->unk14 = 0;
            break;
        case 4:
            if (arg0->unk14 == 1) {
                Hu3DModelAttrReset(arg0->unk3C[1], 0x40000001);
            }
            if (arg0->unk14++ < 0x1E) break;
            arg0->unk1C = 5;
        case 5:
            sp8 = arg0->unk48;
            if (arg0->unk0 == 0) {
                var_f30 = -50.0f;
            } else {
                var_f30 = 50.0f;
            }
            sp8.z -= var_f30;
            fn_1_62F0(arg0, &sp8, 12);
            arg0->unk1C = 6;
            arg0->unk14 = 0;
            break;
        case 6:
            if (arg0->unk14++ >= 12) {
                arg0->unk18 = 0;
            }
            break;
    }
}

void fn_1_6264(unkStruct8* arg0, Vec* arg1, s32 arg2) {
    arg0->unk8C = *arg1;
    arg0->unk80 = arg0->unk54;
    arg0->unkB8 = 0.0f;
    arg0->unkBC = (1.0f / arg2);
    arg0->unk98 = 1;
}

void fn_1_62F0(unkStruct8* arg0, Vec* arg1, s32 arg2) {
    arg0->unkA8 = *arg1;
    arg0->unk9C = arg0->unk48;
    arg0->unkC0 = 0.0f;
    arg0->unkC4 = (1.0f / arg2);
    arg0->unkB4 = 1;
}

void fn_1_637C(unkStruct8* arg0, s32 arg1) {
    f32 var_f31;

    arg0->unkC8 = arg1;
    switch (arg1) {
        case 0:
            Hu3DModelAttrReset(arg0->unk3C[0], 1);
            Hu3DModelAttrSet(arg0->unk3C[0], 0x40000001);
            Hu3DModelAttrSet(arg0->unk3C[1], 1);
            arg0->unk48.x = 0.0f;
            if (arg0->unk70 != 0) {
                var_f31 = 70.0f;
            } else {
                var_f31 = 0.0f;
            }
            arg0->unk48.y = var_f31;
            switch (arg0->unk0) {
                case 0:
                    arg0->unk48.z = 150.0f;
                    arg0->unk54.y = 180.0f;
                    return;
                case 1:
                    arg0->unk48.z = -150.0f;
                    arg0->unk54.y = 0.0f;
                    return;
                }
                break;
        case 1:
            Hu3DModelAttrReset(arg0->unk3C[1], 1);
            Hu3DModelAttrSet(arg0->unk3C[0], 1);
            break;
    }
}

void fn_1_64BC(unkStruct8* arg0, s32 arg1, s32 arg2) {
    if (arg0->unk70 == 0) {
        switch (arg1) {
        case 0:
            omVibrate(arg0->unk0, arg2, 6, 6);
            return;
        case 1:
            omVibrate(arg0->unk0, arg2, 4, 2);
            return;
        case 2:
            omVibrate(arg0->unk0, arg2, 12, 0);
            break;
        }
    }
}

static inline unkStruct8UnkC8(unkStruct8* arg0) {
    if (arg0->unkC8 == 0) {
        return 0;
    } else {
        return 1;
    }
}

void fn_1_6578(unkStruct8* arg0) {
    s32 var_r30;

    var_r30 = unkStruct8UnkC8(arg0);
    Hu3DModelPosSet(arg0->unk3C[var_r30], arg0->unk48.x, arg0->unk48.y, arg0->unk48.z);
    Hu3DModelRotSet(arg0->unk3C[var_r30], arg0->unk54.x, arg0->unk54.y, arg0->unk54.z);
    Hu3DModelScaleSet(arg0->unk3C[var_r30], arg0->unk60, arg0->unk60, arg0->unk60);
}

void fn_1_6620(unkStruct8* arg0) {
    s32 var_r26;
    unkStruct4* temp_r27;
    unkStruct4* temp_r30;
    s32 var_r29;
    s32 var_r28;

    arg0->unk20 = 0;
    arg0->unk24 = 0;
    
    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        temp_r30 = arg0->unk2C[var_r29];
        if (temp_r30) {
            fn_1_2A58(temp_r30);
        }
    }
    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        var_r26 = 0;
        temp_r30 = arg0->unk2C[var_r29];
        if (temp_r30) {
            
            for (var_r28 = 0; var_r28 < 3; var_r28++) {
                temp_r27 = arg0->unk2C[var_r28];
                if ((var_r29 != var_r28) && (temp_r27) && (temp_r30->unk0 == temp_r27->unk0)) {
                    var_r26++;
                }
            }
            if (var_r26 > 0) {
                arg0->unk28 = temp_r30->unk0;
                if (var_r26 == 1) {
                    arg0->unk20 = 1;
                } else if (var_r26 == 2) {
                    arg0->unk24 = 1;
                }
                
                for (var_r28 = 0; var_r28 < 3; var_r28++) {
                    temp_r27 = arg0->unk2C[var_r28];
                    if ((temp_r27) && (temp_r30->unk0 == temp_r27->unk0)) {
                        fn_1_2A1C(temp_r27);
                    }
                }
                break;
            }
        }
    }
}