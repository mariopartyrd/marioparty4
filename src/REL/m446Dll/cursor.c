#include "REL/m446Dll.h"

#include "math.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

// bss
unkStruct3* lbl_1_bss_98;

// data
s32 lbl_1_data_3C8[9] = {
    0x4D0012, 0x4D0013, 0x4D0014,
    0x4D0015, 0x4D0016, 0x4D0017,
    0x4D0018, 0x4D0019, 0x4D001A
};

s32 fn_1_72E0(void) {
    lbl_1_bss_98 = NULL;
    return 1;
}

void fn_1_72F8(void) {
    unkStruct3* var_r31;
    unkStruct7* var_r30;

    var_r31 = lbl_1_bss_98;
    if (var_r31) {
        do {
            var_r30 = var_r31->unk0;
            fn_1_76E8(var_r30);
            var_r31 = var_r31->unk8;
        } while (var_r31);
    }
}

void fn_1_7350(void) {
    f32 temp_f31;
    unkStruct3* var_r30;
    unkStruct7* temp_r31;

    var_r30 = lbl_1_bss_98;
    if (var_r30) {
        do {
            temp_r31 = var_r30->unk0;
            if (temp_r31->field00_bit1 != 0) {
                temp_f31 = sin((M_PI * (90.0f * temp_r31->unk4C)) / 180.0);
                temp_f31 *= temp_f31;
                temp_r31->unk20.x = (temp_r31->unk2C.x + (temp_f31 * (temp_r31->unk38.x - temp_r31->unk2C.x)));
                temp_r31->unk20.y = (temp_r31->unk2C.y + (temp_f31 * (temp_r31->unk38.y - temp_r31->unk2C.y)));
                temp_r31->unk20.z = (temp_r31->unk2C.z + (temp_f31 * (temp_r31->unk38.z - temp_r31->unk2C.z)));
                temp_r31->unk4C += temp_r31->unk50;
                if (temp_r31->unk4C >= 1.0f) {
                    temp_r31->unk20.x = temp_r31->unk38.x;
                    temp_r31->unk20.y = temp_r31->unk38.y;
                    temp_r31->unk20.z = temp_r31->unk38.z;
                    temp_r31->field00_bit1 = 0;
                }
            }
            if ((temp_r31->unk8 == 0) && (temp_r31->field00_bit3 != 0) && (Hu3DMotionEndCheck(temp_r31->unkC[1]) != 0)) {
                fn_1_7884(temp_r31);
            }
            fn_1_7AB4(temp_r31);
            var_r30 = var_r30->unk8;
        } while (var_r30);
    }
}

unkStruct7* m446CursorCreate(s32 arg0) {
    s32 var_r30;
    unkStruct7* var_r31;
    unkStruct3* var_r29;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x54, 0x10000000);
    if (!var_r31) {
        return NULL;
    }
    var_r31->unk4 = 0;
    var_r31->unk20.x = 0.0f;
    var_r31->unk20.y = 72.0f;
    var_r31->unk20.z = 0.0f;
    var_r31->unk44 = 1.0f;
    var_r31->field00_bit1 = 0;
    var_r31->field00_bit2 = 0;
    var_r31->field00_bit3 = 0;
    var_r31->unk8 = arg0;
    var_r31->unk48 = 0;
    var_r31->unkC[0] = Hu3DModelCreateFile(0x4D0009);
    Hu3DModelLayerSet(var_r31->unkC[0], 6);
    if (var_r31->unk8 == 0) {
        for (var_r30 = 0; var_r30 < 9; var_r30++) {
            var_r31->unkC[var_r30 + 1] = Hu3DModelCreateFile(lbl_1_data_3C8[var_r30]);
            Hu3DModelLayerSet(var_r31->unkC[var_r30 + 1], 7);
        }
    }
    fn_1_77C8(var_r31, 0);
    var_r29 = fn_1_1DF4(var_r31);
    if (!var_r29) {
        OSReport("[!] m446CursorCreate ERROR...\n");
        HuMemDirectFree(var_r31);
        return NULL;
    }
    if (lbl_1_bss_98) {
        fn_1_1EC8(lbl_1_bss_98, var_r29);
    } else {
        lbl_1_bss_98 = var_r29;
    }
    return var_r31;
}

void fn_1_76E8(unkStruct7* arg0) {
    s32 var_r29;
    unkStruct3* var_r31;

    var_r31 = lbl_1_bss_98;
    if (var_r31) {
        do {
            if (arg0 == var_r31->unk0) {
                if (var_r31 == lbl_1_bss_98) {
                    lbl_1_bss_98 = var_r31->unk8;
                }
                fn_1_1F04(var_r31);
                fn_1_1E5C(var_r31);
                Hu3DModelKill(arg0->unkC[0]);
                if (arg0->unk8 == 0) {
                    for (var_r29 = 0; var_r29 < 9; var_r29++) {
                        Hu3DModelKill(arg0->unkC[var_r29 + 1]);
                    }
                }
                HuMemDirectFree(arg0);
                return;
            }
            var_r31 = var_r31->unk8;
        } while (var_r31);
    }
}

void fn_1_77C8(unkStruct7* arg0, u8 arg1) {
    s32 var_r30;

    arg0->field00_bit0 = 1;
    arg0->unk48 = arg1;
    Hu3DModelAttrReset(arg0->unkC[0], 1);
    if (arg0->unk8 == 0) {
        for (var_r30 = 0; var_r30 < 9; var_r30++) {
            if (var_r30 == arg1) {
                Hu3DModelAttrReset(arg0->unkC[var_r30 + 1], 1);
            } else {
                Hu3DModelAttrSet(arg0->unkC[var_r30 + 1], 1);
            }
        }
    }
}

void fn_1_7884(unkStruct7* arg0) {
    s32 var_r30;

    arg0->field00_bit0 = 0;
    Hu3DModelAttrSet(arg0->unkC[0], 1);
    if (arg0->unk8 == 0) {
        for (var_r30 = 0; var_r30 < 9; var_r30++) {
            Hu3DModelAttrSet(arg0->unkC[var_r30 + 1], 1);
        }
    }
}

void fn_1_7908(unkStruct7* arg0, Vec* arg1, s32 arg2) {
    arg0->unk38 = *arg1;
    arg0->unk2C = arg0->unk20;
    arg0->unk4C = 0.0f;
    arg0->unk50 = (1.0f / arg2);
    arg0->field00_bit1 = 1;
}

void fn_1_799C(unkStruct7* arg0) {
    s32 var_r30;

    if (arg0->unk8 == 0) {
        for (var_r30 = 0; var_r30 < 9; var_r30++) {
            Hu3DModelAttrReset(arg0->unkC[var_r30 + 1], 0x40000002);
            Hu3DMotionTimeSet(arg0->unkC[var_r30 + 1], 0.0f);
        }
    }
    arg0->field00_bit3 = 1;
}

void fn_1_7A38(unkStruct7* arg0) {
    s32 var_r31;

    if (arg0->unk8 == 0) {
        for (var_r31 = 0; var_r31 < 9; var_r31++) {
            Hu3DModelAttrSet(arg0->unkC[var_r31 + 1], 0x40000002);
        }
    }
    arg0->field00_bit3 = 0;
}

void fn_1_7AB4(unkStruct7* arg0) {
    f32 var_f31;
    s32 temp_r29;
    s32 var_r30;

    Hu3DModelPosSet(arg0->unkC[0], arg0->unk20.x, arg0->unk20.y, arg0->unk20.z);
    Hu3DModelScaleSet(arg0->unkC[0], arg0->unk44, arg0->unk44, arg0->unk44);
    if (arg0->unk8 == 0) {
        for (var_r30 = 0; var_r30 < 9; var_r30++) {
            temp_r29 = var_r30 + 1;
            Hu3DModelPosSet(arg0->unkC[temp_r29], arg0->unk20.x, 0.1f + arg0->unk20.y, arg0->unk20.z);
            Hu3DModelScaleSet(arg0->unkC[temp_r29], arg0->unk44, arg0->unk44, arg0->unk44);
            if (arg0->field00_bit2 != 0) {
                var_f31 = 180.0f;
            } else {
                var_f31 = 0.0f;
            }
            Hu3DModelRotSet(arg0->unkC[temp_r29], 0.0f, var_f31, 0.0f);
        }
    }
}