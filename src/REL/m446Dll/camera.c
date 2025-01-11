#include "REL/m446Dll.h"

#include "math.h"
#include "ext_math.h"
#include "game/hsfman.h"
#include "game/printfunc.h"
#include "game/pad.h"

// bss
Vec lbl_1_bss_8C;
Vec lbl_1_bss_80;
f32 lbl_1_bss_7C;
Vec lbl_1_bss_70;
Vec lbl_1_bss_64;
f32 lbl_1_bss_60;
Vec lbl_1_bss_54;
Vec lbl_1_bss_48;
f32 lbl_1_bss_44;
f32 lbl_1_bss_40;
f32 lbl_1_bss_3C;
s32 lbl_1_bss_38;

// data
Vec lbl_1_data_370 = {0, 1, 0};

s32 fn_1_6778(void) {
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 30.0f, 10.0f, 8000.0f, 1.2f);
    lbl_1_bss_8C.x = 0.0f;
    lbl_1_bss_8C.y = 0.0f;
    lbl_1_bss_8C.z = 0.0f;
    lbl_1_bss_80.x = 0.0f;
    lbl_1_bss_80.y = 0.0f;
    lbl_1_bss_80.z = 0.0f;
    lbl_1_bss_7C = 2000.0f;
    lbl_1_bss_38 = 0;
    return 1;
}

void fn_1_68D8(void) {
    return;
}

void fn_1_68DC(void) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    f32 sp10;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;

    if (lbl_1_bss_38 != 0) {
        temp_f31 = sind(90.0f * lbl_1_bss_40);
        temp_f31 *= temp_f31;
        lbl_1_bss_8C.x = lbl_1_bss_54.x + (temp_f31 * (lbl_1_bss_70.x - lbl_1_bss_54.x));
        lbl_1_bss_8C.y = lbl_1_bss_54.y + (temp_f31 * (lbl_1_bss_70.y - lbl_1_bss_54.y));
        lbl_1_bss_8C.z = lbl_1_bss_54.z + (temp_f31 * (lbl_1_bss_70.z - lbl_1_bss_54.z));
        lbl_1_bss_80.x = lbl_1_bss_48.x + (temp_f31 * (lbl_1_bss_64.x - lbl_1_bss_48.x));
        lbl_1_bss_80.y = lbl_1_bss_48.y + (temp_f31 * (lbl_1_bss_64.y - lbl_1_bss_48.y));
        lbl_1_bss_80.z = lbl_1_bss_48.z + (temp_f31 * (lbl_1_bss_64.z - lbl_1_bss_48.z));
        lbl_1_bss_7C = lbl_1_bss_44 + (temp_f31 * (lbl_1_bss_60 - lbl_1_bss_44));
        lbl_1_bss_40 += lbl_1_bss_3C;
        if (lbl_1_bss_40 >= 1.0f) {
            lbl_1_bss_8C = lbl_1_bss_70;
            lbl_1_bss_80 = lbl_1_bss_64;
            lbl_1_bss_7C = lbl_1_bss_60;
            lbl_1_bss_38 = 0;
        }
    }
    temp_f30 = lbl_1_bss_80.x;
    temp_f29 = lbl_1_bss_80.y;
    sp10 = lbl_1_bss_80.z;
    sp2C.x = (lbl_1_bss_8C.x + (lbl_1_bss_7C * (sind(temp_f29) * cosd(temp_f30))));
    sp2C.y = (lbl_1_bss_8C.y + (lbl_1_bss_7C * -sind(temp_f30)));
    sp2C.z = (lbl_1_bss_8C.z + (lbl_1_bss_7C * (cosd(temp_f29) * cosd(temp_f30))));
    sp20.x = lbl_1_bss_8C.x;
    sp20.y = lbl_1_bss_8C.y;
    sp20.z = lbl_1_bss_8C.z;
    sp14.x = (sind(temp_f29) * sind(temp_f30));
    sp14.y = cosd(temp_f30);
    sp14.z = (cosd(temp_f29) * sind(temp_f30));
    Hu3DCameraPosSet(1, sp2C.x, sp2C.y, sp2C.z, sp14.x, sp14.y, sp14.z, sp20.x, sp20.y, sp20.z);
}

void fn_1_6EA0(Vec* arg0) {
    lbl_1_bss_8C = *arg0;
}

void fn_1_6EC4(Vec* arg0) {
    lbl_1_bss_80 = *arg0;
}

void fn_1_6EE8(f32 arg0) {
    lbl_1_bss_7C = arg0;
}

void fn_1_6EF8(Vec* arg0, Vec* arg1, f32* arg2, s32 arg3) {
    Vec* var_r31;
    Vec* var_r30;
    f32 var_f31;

    if (arg0) {
        var_r31 = arg0;
    } else {
        var_r31 = &lbl_1_bss_8C;
    }
    lbl_1_bss_70 = *var_r31;
    if (arg1) {
        var_r30 = arg1;
    } else {
        var_r30 = &lbl_1_bss_80;
    }
    lbl_1_bss_64 = *var_r30;
    if (arg2) {
        var_f31 = *arg2;
    } else {
        var_f31 = lbl_1_bss_7C;
    }
    lbl_1_bss_60 = var_f31;
    lbl_1_bss_54 = lbl_1_bss_8C;
    lbl_1_bss_48 = lbl_1_bss_80;
    lbl_1_bss_44 = lbl_1_bss_7C;
    lbl_1_bss_40 = 0.0f;
    lbl_1_bss_3C = 1.0f / arg3;
    lbl_1_bss_38 = 1;
}

s32 fn_1_708C(void) {
    return lbl_1_bss_38;
}

void fn_1_709C(void) {
    lbl_1_bss_80.x += 0.01f * *HuPadSubStkX;
    lbl_1_bss_80.z += 0.01f * *HuPadSubStkY;
    lbl_1_bss_7C += 0.05f * *HuPadTrigL;
    lbl_1_bss_7C -= 0.05f * *HuPadTrigR;
    print8(0x20, 0x84, 1.5f, "LOOKAT : x=%.2f y=%.2f z=%.2f", lbl_1_bss_8C.x, lbl_1_bss_8C.y, lbl_1_bss_8C.z);
    print8(0x20, 0x94, 1.5f, "ANGLE  : x=%.2f y=%.2f z=%.2f", lbl_1_bss_80.x, lbl_1_bss_80.y, lbl_1_bss_80.z);
    print8(0x20, 0xA4, 1.5f, "ZOOM   : %.2f", lbl_1_bss_7C);
}
