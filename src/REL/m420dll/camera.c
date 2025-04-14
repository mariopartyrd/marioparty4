#include "ext_math.h"
#include "game/flag.h"
#include "game/hsfman.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"

#include "REL/m420dll.h"

Process *lbl_1_bss_A8;
M420DllUnkStruct lbl_1_bss_8C;
M420DllUnkStruct lbl_1_bss_70;
M420DllUnkStruct lbl_1_bss_54;
s32 lbl_1_bss_50;
s32 lbl_1_bss_4C;
s32 lbl_1_bss_48;
float lbl_1_bss_44;
float lbl_1_bss_40;
float lbl_1_bss_3C;
float lbl_1_bss_38;
float lbl_1_bss_34;
float lbl_1_bss_30;

s32 fn_1_D98(void)
{
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 30.0f, 10.0f, 8000.0f, 1.2f);
    lbl_1_bss_8C.unk_00.x = 0.0f;
    lbl_1_bss_8C.unk_00.y = 0.0f;
    lbl_1_bss_8C.unk_00.z = 0.0f;
    lbl_1_bss_8C.unk_0C.x = -10.0f;
    lbl_1_bss_8C.unk_0C.y = 0.0f;
    lbl_1_bss_8C.unk_0C.z = 0.0f;
    lbl_1_bss_8C.unk_18 = 1000.0f;
    lbl_1_bss_50 = 0;
    lbl_1_bss_4C = 0;
    lbl_1_bss_48 = 0;
    lbl_1_bss_A8 = HuPrcChildCreate(fn_1_1184, 0x1F4, 0x2000, 0, lbl_1_bss_4);
    return 1;
}

void fn_1_F48(void)
{
    HuPrcKill(lbl_1_bss_A8);
}

void fn_1_F74(const Vec *arg0, s32 arg1)
{
    lbl_1_bss_54.unk_00 = *arg0;
    lbl_1_bss_70.unk_00 = lbl_1_bss_8C.unk_00;
    lbl_1_bss_44 = 0.0f;
    lbl_1_bss_38 = 1.0f / arg1;
    lbl_1_bss_50 = 1;
}

void fn_1_1030(const Vec *arg0, s32 arg1)
{
    lbl_1_bss_54.unk_0C = *arg0;
    lbl_1_bss_70.unk_0C = lbl_1_bss_8C.unk_0C;
    lbl_1_bss_40 = 0.0f;
    lbl_1_bss_34 = 1.0f / arg1;
    lbl_1_bss_4C = 1;
}

void fn_1_10EC(float arg8, s32 arg0)
{
    lbl_1_bss_54.unk_18 = arg8;
    lbl_1_bss_70.unk_18 = lbl_1_bss_8C.unk_18;
    lbl_1_bss_3C = 0.0f;
    lbl_1_bss_30 = 1.0f / arg0;
    lbl_1_bss_48 = 1;
}

void fn_1_1184(void)
{
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float var_f31;

    while (TRUE) {
        if (lbl_1_bss_50 != 0) {
            var_f31 = sind((90.0f * lbl_1_bss_44));
            var_f31 *= var_f31;
            lbl_1_bss_8C.unk_00.x = lbl_1_bss_70.unk_00.x + (var_f31 * (lbl_1_bss_54.unk_00.x - lbl_1_bss_70.unk_00.x));
            lbl_1_bss_8C.unk_00.y = lbl_1_bss_70.unk_00.y + (var_f31 * (lbl_1_bss_54.unk_00.y - lbl_1_bss_70.unk_00.y));
            lbl_1_bss_8C.unk_00.z = lbl_1_bss_70.unk_00.z + (var_f31 * (lbl_1_bss_54.unk_00.z - lbl_1_bss_70.unk_00.z));
            if ((lbl_1_bss_44 += lbl_1_bss_38) >= 1.0f) {
                lbl_1_bss_8C.unk_00 = lbl_1_bss_54.unk_00;
                lbl_1_bss_50 = 0;
            }
        }
        if (lbl_1_bss_4C != 0) {
            var_f31 = sind((90.0f * lbl_1_bss_40));
            var_f31 *= var_f31;
            lbl_1_bss_8C.unk_0C.x = lbl_1_bss_70.unk_0C.x + (var_f31 * (lbl_1_bss_54.unk_0C.x - lbl_1_bss_70.unk_0C.x));
            lbl_1_bss_8C.unk_0C.y = lbl_1_bss_70.unk_0C.y + (var_f31 * (lbl_1_bss_54.unk_0C.y - lbl_1_bss_70.unk_0C.y));
            lbl_1_bss_8C.unk_0C.z = lbl_1_bss_70.unk_0C.z + (var_f31 * (lbl_1_bss_54.unk_0C.z - lbl_1_bss_70.unk_0C.z));
            if ((lbl_1_bss_40 += lbl_1_bss_34) >= 1.0f) {
                lbl_1_bss_8C.unk_0C = lbl_1_bss_54.unk_0C;
                lbl_1_bss_4C = 0;
            }
        }
        if (lbl_1_bss_48 != 0) {
            var_f31 = sind((90.0f * lbl_1_bss_3C));
            var_f31 *= var_f31;
            lbl_1_bss_8C.unk_18 = lbl_1_bss_70.unk_18 + (var_f31 * (lbl_1_bss_54.unk_18 - lbl_1_bss_70.unk_18));
            if ((lbl_1_bss_3C += lbl_1_bss_30) >= 1.0f) {
                lbl_1_bss_8C.unk_18 = lbl_1_bss_54.unk_18;
                lbl_1_bss_48 = 0;
            }
        }
        sp28.x = lbl_1_bss_8C.unk_00.x + (lbl_1_bss_8C.unk_18 * (sind(lbl_1_bss_8C.unk_0C.y) * cosd(lbl_1_bss_8C.unk_0C.x)));
        sp28.y = lbl_1_bss_8C.unk_00.y + (lbl_1_bss_8C.unk_18 * -sind(lbl_1_bss_8C.unk_0C.x));
        sp28.z = lbl_1_bss_8C.unk_00.z + (lbl_1_bss_8C.unk_18 * (cosd(lbl_1_bss_8C.unk_0C.y) * cosd(lbl_1_bss_8C.unk_0C.x)));
        sp10.x = sind(lbl_1_bss_8C.unk_0C.y) * sind(lbl_1_bss_8C.unk_0C.x);
        sp10.y = cosd(lbl_1_bss_8C.unk_0C.x);
        sp10.z = cosd(lbl_1_bss_8C.unk_0C.y) * sind(lbl_1_bss_8C.unk_0C.x);
        sp1C = lbl_1_bss_8C.unk_00;

        Hu3DCameraPosSet(1, sp28.x, sp28.y, sp28.z, sp10.x, sp10.y, sp10.z, sp1C.x, sp1C.y, sp1C.z);
        HuPrcVSleep();
    }
}

void fn_1_189C(void)
{
    lbl_1_bss_8C.unk_00.x += (0.02f * *HuPadStkX);
    lbl_1_bss_8C.unk_00.y += (0.02f * *HuPadStkY);
    lbl_1_bss_8C.unk_0C.y -= (0.02f * *HuPadSubStkX);
    lbl_1_bss_8C.unk_0C.x += (0.02f * *HuPadSubStkY);
    lbl_1_bss_8C.unk_18 += (0.02f * *HuPadTrigL);
    lbl_1_bss_8C.unk_18 -= (0.02f * *HuPadTrigR);
}

void fn_1_1AB0(void)
{
    print8(0x20, 0x84, 1.5f, "LOOKAT : x=%.2f y=%.2f z=%.2f", lbl_1_bss_8C.unk_00.x, lbl_1_bss_8C.unk_00.y, lbl_1_bss_8C.unk_00.z);
    print8(0x20, 0x94, 1.5f, "ANGLE  : x=%.2f y=%.2f z=%.2f", lbl_1_bss_8C.unk_0C.x, lbl_1_bss_8C.unk_0C.y, lbl_1_bss_8C.unk_0C.z);
    print8(0x20, 0xA4, 1.5f, "ZOOM   : x=%.2f", lbl_1_bss_8C.unk_18);
}
