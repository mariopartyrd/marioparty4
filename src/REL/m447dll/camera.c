#include "REL/m447dll.h"
#include "game/hsfman.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"

#include "ext_math.h"

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ float unk18;
} UnkM447Struct_05; // Size 0x1C

void fn_1_3564(void);
void fn_1_3C7C(void);
void fn_1_3EA8(void);

Process* lbl_1_bss_90;
UnkM447Struct_05 lbl_1_bss_74;
UnkM447Struct_05 lbl_1_bss_58;
UnkM447Struct_05 lbl_1_bss_3C;
s32 lbl_1_bss_38;
s32 lbl_1_bss_34;
s32 lbl_1_bss_30;
float lbl_1_bss_2C;
float lbl_1_bss_28;
float lbl_1_bss_24;
float lbl_1_bss_20;
float lbl_1_bss_1C;
float lbl_1_bss_18;

s32 fn_1_3130(void) {
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 55.0f, 10.0f, 8000.0f, 1.2f);
    lbl_1_bss_74.unk00.x = 0.0f;
    lbl_1_bss_74.unk00.y = 400.0f;
    lbl_1_bss_74.unk00.z = 0.0f;
    lbl_1_bss_74.unk0C.x = 0.0f;
    lbl_1_bss_74.unk0C.y = 0.0f;
    lbl_1_bss_74.unk0C.z = 0.0f;
    lbl_1_bss_74.unk18 = 200.0f;
    lbl_1_bss_38 = 0;
    lbl_1_bss_34 = 0;
    lbl_1_bss_30 = 0;
    lbl_1_bss_90 = HuPrcChildCreate(fn_1_3564, 100, 0x2000, 0, lbl_1_bss_4);
    return 1;
}

void fn_1_32E0(void) {
    HuPrcKill(lbl_1_bss_90);
}

void fn_1_330C(const Vec* arg0, s32 arg1) {
    lbl_1_bss_3C.unk00 = *arg0;
    lbl_1_bss_58.unk00 = lbl_1_bss_74.unk00;
    lbl_1_bss_2C = 0.0f;
    lbl_1_bss_20 = 1.0f / arg1;
    lbl_1_bss_38 = 1;
}

void fn_1_33C8(const Vec* arg0, s32 arg1) {
    lbl_1_bss_3C.unk0C = *arg0;
    lbl_1_bss_58.unk0C = lbl_1_bss_74.unk0C;
    lbl_1_bss_28 = 0.0f;
    lbl_1_bss_1C = 1.0f / arg1;
    lbl_1_bss_34 = 1;
}

void fn_1_3484(float arg0, s32 arg1) {
    lbl_1_bss_3C.unk18 = arg0;
    lbl_1_bss_58.unk18 = lbl_1_bss_74.unk18;
    lbl_1_bss_24 = 0.0f;
    lbl_1_bss_18 = 1.0f / arg1;
    lbl_1_bss_30 = 1;
}

void fn_1_351C(Vec* arg0) {
    *arg0 = lbl_1_bss_74.unk00;
}

void fn_1_3540(Vec* arg0) {
    lbl_1_bss_74.unk00 = *arg0;
}

void fn_1_3564(void) {
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float temp_f31;

    while (TRUE) {
        if (lbl_1_bss_38 != 0) {
            temp_f31 = sind(90.0f * lbl_1_bss_2C);
            temp_f31 *= temp_f31;
            lbl_1_bss_74.unk00.x = lbl_1_bss_58.unk00.x + temp_f31 * (lbl_1_bss_3C.unk00.x - lbl_1_bss_58.unk00.x);
            lbl_1_bss_74.unk00.y = lbl_1_bss_58.unk00.y + temp_f31 * (lbl_1_bss_3C.unk00.y - lbl_1_bss_58.unk00.y);
            lbl_1_bss_74.unk00.z = lbl_1_bss_58.unk00.z + temp_f31 * (lbl_1_bss_3C.unk00.z - lbl_1_bss_58.unk00.z);
            if ((lbl_1_bss_2C += lbl_1_bss_20) >= 1.0f) {
                lbl_1_bss_74.unk00 = lbl_1_bss_3C.unk00;
                lbl_1_bss_38 = 0;
            }
        }
        if (lbl_1_bss_34 != 0) {
            temp_f31 = sind(90.0f * lbl_1_bss_28);
            temp_f31 *= temp_f31;
            lbl_1_bss_74.unk0C.x = lbl_1_bss_58.unk0C.x + temp_f31 * (lbl_1_bss_3C.unk0C.x - lbl_1_bss_58.unk0C.x);
            lbl_1_bss_74.unk0C.y = lbl_1_bss_58.unk0C.y + temp_f31 * (lbl_1_bss_3C.unk0C.y - lbl_1_bss_58.unk0C.y);
            lbl_1_bss_74.unk0C.z = lbl_1_bss_58.unk0C.z + temp_f31 * (lbl_1_bss_3C.unk0C.z - lbl_1_bss_58.unk0C.z);
            if ((lbl_1_bss_28 += lbl_1_bss_1C) >= 1.0f) {
                lbl_1_bss_74.unk0C = lbl_1_bss_3C.unk0C;
                lbl_1_bss_34 = 0;
            }
        }
        if (lbl_1_bss_30 != 0) {
            temp_f31 = sind(90.0f * lbl_1_bss_24);
            temp_f31 *= temp_f31;
            lbl_1_bss_74.unk18 = lbl_1_bss_58.unk18 + temp_f31 * (lbl_1_bss_3C.unk18 - lbl_1_bss_58.unk18);
            if ((lbl_1_bss_24 += lbl_1_bss_18) >= 1.0f) {
                lbl_1_bss_74.unk18 = lbl_1_bss_3C.unk18;
                lbl_1_bss_30 = 0;
            }
        }
        sp28.x = lbl_1_bss_74.unk00.x + sind(lbl_1_bss_74.unk0C.y) * cosd(lbl_1_bss_74.unk0C.x) * lbl_1_bss_74.unk18;
        sp28.y = lbl_1_bss_74.unk00.y + -sind(lbl_1_bss_74.unk0C.x) * lbl_1_bss_74.unk18;
        sp28.z = lbl_1_bss_74.unk00.z + cosd(lbl_1_bss_74.unk0C.y) * cosd(lbl_1_bss_74.unk0C.x) * lbl_1_bss_74.unk18;
        sp10.x = sind(lbl_1_bss_74.unk0C.y) * sind(lbl_1_bss_74.unk0C.x);
        sp10.y = cosd(lbl_1_bss_74.unk0C.x);
        sp10.z = cosd(lbl_1_bss_74.unk0C.y) * sind(lbl_1_bss_74.unk0C.x);
        sp1C = lbl_1_bss_74.unk00;
        Hu3DCameraPosSet(1, sp28.x, sp28.y, sp28.z, sp10.x, sp10.y, sp10.z, sp1C.x, sp1C.y, sp1C.z);
        HuPrcVSleep();
    }
}

void fn_1_3C7C(void) {
    if (HuPadBtn[0] & 4) {
        lbl_1_bss_74.unk00.x += 0.02f * HuPadStkX[0];
        lbl_1_bss_74.unk00.y += 0.02f * HuPadStkY[0];
        lbl_1_bss_74.unk0C.y -= 0.02f * HuPadSubStkX[0];
        lbl_1_bss_74.unk0C.x += 0.02f * HuPadSubStkY[0];
        lbl_1_bss_74.unk18 += 0.02f * HuPadTrigL[0];
        lbl_1_bss_74.unk18 -= 0.02f * HuPadTrigR[0];
    }
}

void fn_1_3EA8(void) {
    print8(32, 132, 1.5f, "LOOKAT : x=%.2f y=%.2f z=%.2f", lbl_1_bss_74.unk00.x, lbl_1_bss_74.unk00.y, lbl_1_bss_74.unk00.z);
    print8(32, 148, 1.5f, "ANGLE  : x=%.2f y=%.2f z=%.2f", lbl_1_bss_74.unk0C.x, lbl_1_bss_74.unk0C.y, lbl_1_bss_74.unk0C.z);
    print8(32, 164, 1.5f, "ZOOM   : x=%.2f", lbl_1_bss_74.unk18);
}
