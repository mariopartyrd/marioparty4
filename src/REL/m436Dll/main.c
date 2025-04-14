#include "REL/m436Dll.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"

#include "ext_math.h"
#include "version.h"

s32 rand8(void);
#ifndef __MWERKS__
#include "game/audio.h"
#endif

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ float unk2C;
} StructBss3E4; // Size 0x30

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
} StructBss4A4; // Size 0x10

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ float unk04;
    /* 0x08 */ s32 unk08[15];
    /* 0x44 */ s32 unk44[15];
    /* 0x80 */ float unk80[15][2];
} StructBss234; // Size 0xF8

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ char unk08[0xC];
} StructBss220; // Size 0x14

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ Vec unk04[8];
} StructBss1BC; // Size 0x64

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ float unk08[6];
    /* 0x20 */ char unk20[8];
    /* 0x28 */ float unk28[6];
    /* 0x40 */ char unk40[8];
    /* 0x48 */ float unk48[6];
    /* 0x60 */ char unk60[8];
    /* 0x68 */ float unk68[6];
    /* 0x80 */ char unk80[8];
    /* 0x88 */ float unk88[6];
    /* 0xA0 */ char unkA0[8];
} StructBssD8; // Size 0xA8

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ char unk04[0x10];
} StructBss1A8; // Size 0x14

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ char unk04[0x10];
} StructBss180; // Size 0x14

typedef struct {
    /* 0x00 */ char unk00[0x28];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ char unk2C[0xC];
} StructBss3AC; // Size 0x38

s32 fn_1_538C(s32 arg0);

StructBss4A4 lbl_1_bss_4A4;
StructBss3E4 lbl_1_bss_3E4[4];
StructBss3AC lbl_1_bss_3AC;
s32 lbl_1_bss_3A4[2];
StructBss32C lbl_1_bss_32C;
StructBss234 lbl_1_bss_234;
StructBss220 lbl_1_bss_220;
StructBss1BC lbl_1_bss_1BC;
StructBss1A8 lbl_1_bss_1A8;
StructBss180 lbl_1_bss_180[2];
StructBssD8 lbl_1_bss_D8;
StructBssC0 lbl_1_bss_C0;
StructBssC0 lbl_1_bss_A8;
Mtx lbl_1_bss_78;
Mtx lbl_1_bss_48;
Vec lbl_1_bss_3C;
StructBssC0 lbl_1_bss_24;
s32 lbl_1_bss_20_pad; // unused
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
Process *lbl_1_bss_0;

s32 lbl_1_data_0[]
    = { DATA_MAKE_NUM(DATADIR_M436, 13), DATA_MAKE_NUM(DATADIR_M436, 14), DATA_MAKE_NUM(DATADIR_M436, 15), DATA_MAKE_NUM(DATADIR_M436, 16),
          DATA_MAKE_NUM(DATADIR_M436, 17), DATA_MAKE_NUM(DATADIR_M436, 18), DATA_MAKE_NUM(DATADIR_M436, 19), DATA_MAKE_NUM(DATADIR_M436, 20) };

s32 lbl_1_data_20[] = { MAKE_MESSID(29, 23), MAKE_MESSID(29, 24), MAKE_MESSID(29, 30), MAKE_MESSID(29, 26), MAKE_MESSID(29, 28), MAKE_MESSID(29, 27),
    MAKE_MESSID(29, 25), MAKE_MESSID(29, 29) };

s32 lbl_1_data_40[][5] = { { 91, 105, 126, 141, -1 }, { 91, 105, 126, 141, -1 }, { 124, 137, -1, -1, -1 }, { 85, 100, 127, -1, -1 },
    { 124, 139, -1, -1, -1 }, { 85, 97, 127, 139, -1 }, { 127, 137, -1, -1, -1 }, { 79, 95, 109, 127, -1 } };

s32 lbl_1_data_E0 = -1;
s32 lbl_1_data_E4 = -1;
s32 lbl_1_data_E8 = -1;

void fn_1_0(void)
{
    s32 i;

    while (TRUE) {
        HuPrcVSleep();
        if (lbl_1_data_E0 == -1 || lbl_1_data_E4 == -1 || lbl_1_data_E8 == -1 || lbl_1_data_E4 != Hu3DMotionIDGet(lbl_1_data_E0)) {
            continue;
        }
        for (i = 0; i < 5; i++) {
            if (lbl_1_data_40[lbl_1_data_E8][i] != -1 && Hu3DMotionTimeGet(lbl_1_data_E0) >= lbl_1_data_40[lbl_1_data_E8][i]) {
                OSReport("KE-System  CHR:%d TIME:%d\n", lbl_1_data_E8, lbl_1_data_40[lbl_1_data_E8][i]);
                HuAudFXPlay(0x6D8);
                lbl_1_data_40[lbl_1_data_E8][i] = -1;
            }
        }
    }
}

void fn_1_1A8(void)
{
    s32 var_r31;

    var_r31 = Hu3DGLightCreate(0.0f, 1000.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0xFF, 0xFF, 0xFF);
    Hu3DGLightInfinitytSet(var_r31);
}

void fn_1_230(void)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    if (HuPadBtn[0] & 0x200) {
        if (HuPadBtn[0] & 0x100) {
            var_r31->unk0C -= HuPadStkY[0] / 10.0f;
        }
        else {
            var_r31->unk04 += HuPadStkX[0] / 10.0f;
            var_r31->unk08 += HuPadStkY[0] / 10.0f;
        }
    }
    if (HuPadBtn[0] & 0x800) {
        var_r31->unk1C -= HuPadStkY[0] / 100.0f;
        var_r31->unk20 += HuPadStkX[0] / 100.0f;
    }
    if (HuPadBtn[0] & 0x400) {
        var_r31->unk34 -= HuPadStkY[0] / 10.0f;
    }
    if (var_r31->unk1C >= 360.0f) {
        var_r31->unk1C -= 360.0f;
    }
    if (var_r31->unk1C < 0.0f) {
        var_r31->unk1C += 360.0f;
    }
    if (var_r31->unk20 >= 360.0f) {
        var_r31->unk20 -= 360.0f;
    }
    if (var_r31->unk20 < 0.0f) {
        var_r31->unk20 += 360.0f;
    }
    print8(16, 100, 1.0f, ">>>>>>>>>> CAMERA TEST <<<<<<<<<<");
    print8(16, 110, 1.0f, "CENTER : %.2f, %.2f, %.2f", var_r31->unk04, var_r31->unk08, var_r31->unk0C);
    print8(16, 120, 1.0f, "ROT    : %.2f, %.2f, %.2f", var_r31->unk1C, var_r31->unk20, var_r31->unk24);
    print8(16, 130, 1.0f, "ZOOM   : %.2f", var_r31->unk34);
}

void fn_1_614(s32 arg0, s32 arg1, float arg2)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk40[arg0] = arg1;
    if (var_r31->unk5C[arg0] < 0.0f) {
        var_r31->unk5C[arg0] = -arg2;
    }
    else {
        var_r31->unk5C[arg0] = arg2;
    }
}

void fn_1_67C(s32 arg0, float arg1)
{
    fn_1_614(arg0, -1, arg1);
}

float fn_1_6E8(s32 arg0)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    if (var_r31->unk5C[arg0] != 0.0f) {
        var_r31->unk5C[arg0] *= -0.9f;
        if (var_r31->unk40[arg0] == -1) {
            if (var_r31->unk5C[arg0] >= -0.5f && var_r31->unk5C[arg0] <= 0.5f) {
                var_r31->unk5C[arg0] = 0.0f;
            }
        }
        else {
            var_r31->unk40[arg0]--;
            if (var_r31->unk40[arg0] <= 0) {
                var_r31->unk40[arg0] = 0;
                var_r31->unk5C[arg0] = 0.0f;
            }
        }
    }
    return var_r31->unk5C[arg0];
}

void fn_1_818(void)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk04 = 0.0f;
    var_r31->unk08 = 225.0f;
    var_r31->unk0C = 1740.0f;
    var_r31->unk1C = -10.0f;
    var_r31->unk20 = 0.0f;
    var_r31->unk24 = 0.0f;
    var_r31->unk34 = 300.0f;
}

void fn_1_8A4(void (*arg0)(void))
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk00 = arg0;
}

void fn_1_8C4(omObjData *arg0)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    if (var_r31->unk00 != NULL) {
        var_r31->unk00();
    }
    Center.x = var_r31->unk04 + fn_1_6E8(0);
    Center.y = var_r31->unk08 + fn_1_6E8(1);
    Center.z = var_r31->unk0C + fn_1_6E8(2);
    CRot.x = var_r31->unk1C + fn_1_6E8(3);
    CRot.y = var_r31->unk20 + fn_1_6E8(4);
    CRot.z = var_r31->unk24 + fn_1_6E8(5);
    CZoom = var_r31->unk34 + fn_1_6E8(6);
}

void fn_1_F6C(void)
{
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 45.0f, 0.1f, 10000.0f, 1.2f);
    fn_1_8A4(fn_1_818);
    omAddObjEx(lbl_1_bss_0, 0x7FDA, 0, 0, -1, omOutView);
    omAddObjEx(lbl_1_bss_0, 0x7FD9, 0, 0, -1, fn_1_8C4);
}

void fn_1_1084(void)
{
    Vec sp20 = { 0.0f, 2500.0f, 1.0f };
    Vec sp14 = { 0.0f, 0.0f, 0.0f };
    Vec sp8 = { 0.0f, 1.0f, 0.0f };

    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);
}

void fn_1_1148(s32 arg0, float arg1, float arg2, s32 arg3)
{
    WindowData *temp_r29;
    float temp_f29;
    float temp_f28;
    float temp_f25;
    float temp_f24;
    float temp_f27;
    float temp_f26;
    float var_f31;
    float var_f30;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f20;
    s32 i;

    temp_r29 = &winData[arg0];
    temp_f29 = temp_r29->pos_x;
    temp_f28 = temp_r29->pos_y;
    temp_f25 = temp_r29->w;
    temp_f24 = temp_r29->h;
    var_f31 = temp_f29 + temp_f25 * arg1;
    temp_f27 = 4.0f / temp_f25;
    if (var_f31 + 4.0f - (temp_f29 + temp_f25) >= 0.0f) {
        var_f31 = temp_f29 + temp_f25 - 4.0f;
    }
    else {
        if (temp_f29 - (var_f31 - 2.0f) >= 0.0f) {
            var_f31 = temp_f29;
        }
        else {
            var_f31 -= 2.0f;
        }
    }
    var_f30 = temp_f28 + temp_f24 * arg2;
    temp_f26 = 4.0f / temp_f24;
    if (var_f30 + 4.0f - (temp_f28 + temp_f24) >= 0.0f) {
        var_f30 = temp_f28 + temp_f24 - 4.0f;
    }
    else {
        if (temp_f28 - (var_f30 - 2.0f) >= 0.0f) {
            var_f30 = temp_f28;
        }
        else {
            var_f30 -= 2.0f;
        }
    }
    if (arg3 != 0) {
        HuWinPosSet(arg0, var_f31, var_f30);
        HuWinScaleSet(arg0, temp_f27, temp_f26);
        var_f23 = var_f31;
        var_f21 = temp_f27;
        var_f22 = var_f30;
        var_f20 = temp_f26;
    }
    else {
        HuWinPosSet(arg0, temp_f29, temp_f28);
        HuWinScaleSet(arg0, 1.0f, 1.0f);
        var_f23 = temp_f29;
        var_f21 = 1.0f;
        var_f22 = temp_f28;
        var_f20 = 1.0f;
    }
    HuWinDispOn(arg0);
    for (i = 0; i <= 15; i++) {
        HuPrcVSleep();
        if (arg3 != 0) {
            if (i <= 10) {
                var_f23 = fn_1_11164(var_f31, temp_f29, i, 10.0f);
                var_f21 = fn_1_11164(temp_f27, 1.0f, i, 10.0f);
            }
            else {
                var_f22 = fn_1_11164(var_f30, temp_f28, i - 10, 5.0f);
                var_f20 = fn_1_11164(temp_f26, 1.0f, i - 10, 5.0f);
            }
        }
        else {
            if (i <= 10) {
                var_f22 = fn_1_11164(temp_f28, var_f30, i, 10.0f);
                var_f20 = fn_1_11164(1.0f, temp_f26, i, 10.0f);
            }
            else {
                var_f23 = fn_1_11164(temp_f29, var_f31, i - 10, 5.0f);
                var_f21 = fn_1_11164(1.0f, temp_f27, i - 10, 5.0f);
            }
        }
        HuWinPosSet(arg0, var_f23, var_f22);
        HuWinScaleSet(arg0, var_f21, var_f20);
    }
    if (arg3 != 0) {
        HuWinPosSet(arg0, temp_f29, temp_f28);
        HuWinScaleSet(arg0, 1.0f, 1.0f);
    }
    else {
        HuWinPosSet(arg0, var_f31, var_f30);
        HuWinScaleSet(arg0, temp_f27, temp_f26);
    }
    HuPrcVSleep();
}

void fn_1_178C(void)
{
    HuWinInit(1);
}

void fn_1_17B0(s32 arg0, float arg1, float arg2)
{
    WindowData *temp_r31;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    float temp_f24;
    float var_f31;
    float var_f30;
    float temp_f23;
    float temp_f22;
    float temp_f21;
    float temp_f20;
    s32 i;

    temp_r31 = &winData[arg0];
    temp_f29 = temp_r31->pos_x;
    temp_f28 = temp_r31->pos_y;
    temp_f27 = temp_r31->w;
    temp_f26 = temp_r31->h;
    var_f31 = temp_f29 + temp_f27 * arg1;
    temp_f25 = 4.0f / temp_f27;
    if (var_f31 + 4.0f - (temp_f29 + temp_f27) >= 0.0f) {
        var_f31 = temp_f29 + temp_f27 - 4.0f;
    }
    else {
        if (temp_f29 - (var_f31 - 2.0f) >= 0.0f) {
            var_f31 = temp_f29;
        }
        else {
            var_f31 = var_f31 - 2.0f;
        }
    }
    var_f30 = temp_f28 + temp_f26 * arg2;
    temp_f24 = 4.0f / temp_f26;
    if (var_f30 + 4.0f - (temp_f28 + temp_f26) >= 0.0f) {
        var_f30 = temp_f28 + temp_f26 - 4.0f;
    }
    else {
        if (temp_f28 - (var_f30 - 2.0f) >= 0.0f) {
            var_f30 = temp_f28;
        }
        else {
            var_f30 = var_f30 - 2.0f;
        }
    }
    HuWinPosSet(arg0, var_f31, var_f30);
    HuWinScaleSet(arg0, temp_f25, temp_f24);
    HuPrcVSleep();
    for (i = 0; i < 10; i++) {
        temp_f23 = fn_1_11164(var_f31, temp_f29, i, 10.0f);
        temp_f21 = fn_1_11164(temp_f25, 1.0f, i, 10.0f);
        temp_f22 = fn_1_11164(var_f30, temp_f28, i, 10.0f);
        temp_f20 = fn_1_11164(temp_f24, 1.0f, i, 10.0f);
        HuWinPosSet(arg0, temp_f23, temp_f22);
        HuWinScaleSet(arg0, temp_f21, temp_f20);
        HuPrcVSleep();
    }
    HuWinPosSet(arg0, temp_f29, temp_f28);
    HuWinScaleSet(arg0, 1.0f, 1.0f);
    HuPrcVSleep();
}

void fn_1_1C08(s32 arg0, float arg1, float arg2)
{
    WindowData *temp_r31;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    float temp_f24;
    float var_f31;
    float var_f30;
    float temp_f23;
    float temp_f22;
    float temp_f21;
    float temp_f20;
    s32 i;

    temp_r31 = &winData[arg0];
    temp_f29 = temp_r31->pos_x;
    temp_f28 = temp_r31->pos_y;
    temp_f27 = temp_r31->w;
    temp_f26 = temp_r31->h;
    var_f31 = temp_f29 + temp_f27 * arg1;
    temp_f25 = 4.0f / temp_f27;
    if (var_f31 + 4.0f - (temp_f29 + temp_f27) >= 0.0f) {
        var_f31 = temp_f29 + temp_f27 - 4.0f;
    }
    else {
        if (temp_f29 - (var_f31 - 2.0f) >= 0.0f) {
            var_f31 = temp_f29;
        }
        else {
            var_f31 = var_f31 - 2.0f;
        }
    }
    var_f30 = temp_f28 + temp_f26 * arg2;
    temp_f24 = 4.0f / temp_f26;
    if (var_f30 + 4.0f - (temp_f28 + temp_f26) >= 0.0f) {
        var_f30 = temp_f28 + temp_f26 - 4.0f;
    }
    else {
        if (temp_f28 - (var_f30 - 2.0f) >= 0.0f) {
            var_f30 = temp_f28;
        }
        else {
            var_f30 = var_f30 - 2.0f;
        }
    }
    HuWinPosSet(arg0, temp_f29, temp_f28);
    HuWinScaleSet(arg0, 1.0f, 1.0f);
    HuPrcVSleep();
    for (i = 0; i < 10; i++) {
        temp_f23 = fn_1_112F4(temp_f29, var_f31, i, 10.0f);
        temp_f21 = fn_1_112F4(1.0f, temp_f25, i, 10.0f);
        temp_f22 = fn_1_112F4(temp_f28, var_f30, i, 10.0f);
        temp_f20 = fn_1_112F4(1.0f, temp_f24, i, 10.0f);
        HuWinPosSet(arg0, temp_f23, temp_f22);
        HuWinScaleSet(arg0, temp_f21, temp_f20);
        HuPrcVSleep();
    }
    HuWinPosSet(arg0, var_f31, var_f30);
    HuWinScaleSet(arg0, temp_f25, temp_f24);
    HuPrcVSleep();
}

s32 fn_1_2060(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4)
{
    s32 sp20[][5] = { { 0xFF, 0xFF, 0xCC, 0x00, 0x09 }, { 0xCC, 0xFF, 0xFF, 0x00, 0x09 }, { 0xFF, 0xCC, 0xFF, 0x00, 0x09 } };
    float sp14[] = { 0.9f, 0.9f, 0.9f };
    GXColor sp10;
    s32 temp_r31;

    temp_r31 = HuWinCreate(arg0, arg1, arg2, arg3, 1);
    sp10.r = sp20[arg4][0];
    sp10.g = sp20[arg4][1];
    sp10.b = sp20[arg4][2];
    HuWinBGColSet(temp_r31, &sp10);
    HuWinBGTPLvlSet(temp_r31, sp14[arg4]);
    fn_1_1148(temp_r31, 0.5f, 0.5f, 1);
    return temp_r31;
}

s32 fn_1_2230(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4)
{
    return fn_1_2060(arg0, arg1, arg2, arg3, arg4);
}

void fn_1_2400(s32 arg0)
{
    HuWinMesSet(arg0, MAKE_MESSID(29, 22));
    HuPrcVSleep();
    fn_1_1148(arg0, 0.5f, 0.5f, 0);
    HuWinKill(arg0);
}

void fn_1_2468(s32 arg0)
{
    fn_1_2400(arg0);
}

void fn_1_24D0(s32 arg0, s32 arg1)
{
    s32 i;
    s32 var_r30;
    s32 temp_r28;

    var_r30 = 0;
    temp_r28 = GWMessDelayGet();
    if (arg1 > 0) {
        HuPrcSleep(arg1);
        return;
    }
    HuWinComKeyReset();
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_3E4[i].unk0C == 0) {
            var_r30 = 1;
            winData[arg0].active_pad = 0xF;
        }
    }
    if (var_r30 == 0) {
        winData[arg0].active_pad = 0xF;
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, temp_r28);
    }
    HuWinMesWait(arg0);
    HuWinComKeyReset();
}

void fn_1_25B8(s32 arg0)
{
    s32 var_r31;
    s32 temp_r28;
    s32 i;

    var_r31 = 0;
    temp_r28 = GWMessDelayGet();
    HuWinComKeyReset();
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_3E4[i].unk0C == 0) {
            var_r31 = 1;
            winData[arg0].active_pad = 0xF;
        }
    }
    if (var_r31 == 0) {
        winData[arg0].active_pad = 0xF;
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, temp_r28);
    }
    var_r31 = HuWinChoiceGet(arg0, 1);
    if (var_r31 == -1 || var_r31 == 1) {
        lbl_1_bss_8 = 0;
    }
    else {
        lbl_1_bss_8 = 1;
    }
    HuWinComKeyReset();
}

void fn_1_26D4(float *arg0, s32 arg1)
{
    float spC[2];

    HuWinMesMaxSizeGet(1, spC, arg1);
    if (spC[0] > arg0[0]) {
        arg0[0] = spC[0];
    }
    if (spC[1] > arg0[1]) {
        arg0[1] = spC[1];
    }
}

void fn_1_2744(s32 arg0, s32 arg1)
{
    winData[arg0].mess_color = 0;
    winData[arg0].mess_shadow_color = 9;
    winData[arg0].attr |= 0x80;
    HuWinMesSet(arg0, arg1);
}

void fn_1_27C8(s32 arg0)
{
    if (lbl_1_bss_10 == 0) {
        lbl_1_bss_10 = 1;
        lbl_1_bss_C = arg0 * REFRESH_RATE;
    }
}

s32 fn_1_2800(void)
{
    if (lbl_1_bss_10 == 3) {
        return 1;
    }
    else {
        return 0;
    }
}

void fn_1_2824(void)
{
    if (lbl_1_bss_10 == 2) {
        lbl_1_bss_10 = 3;
        lbl_1_bss_C = 30;
    }
}

s32 lbl_1_data_16C = -1;

void fn_1_285C(omObjData *arg0)
{
    switch (lbl_1_bss_10) {
        case 1:
            if (lbl_1_data_16C == -1) {
                lbl_1_data_16C = MGSeqCreate(1, lbl_1_bss_C / REFRESH_RATE, -1, -1);
            }
            lbl_1_bss_10 = 2;
            break;
        case 2:
            lbl_1_bss_C--;
            if (lbl_1_data_16C != -1) {
                MGSeqParamSet(lbl_1_data_16C, 1, (lbl_1_bss_C + REFRESH_RATE - 1) / REFRESH_RATE);
            }
            if (lbl_1_bss_C <= 0) {
                lbl_1_bss_C = 30;
                lbl_1_bss_10 = 3;
            }
            break;
        case 3:
            if (lbl_1_data_16C != -1) {
                MGSeqParamSet(lbl_1_data_16C, 2, -1);
                lbl_1_data_16C = -1;
            }
            lbl_1_bss_C = 0;
            lbl_1_bss_10 = 0;
            break;
    }
}

void fn_1_2A2C(void)
{
    lbl_1_bss_C = 0;
    lbl_1_bss_10 = 0;
    omAddObjEx(lbl_1_bss_0, 0x2000, 0, 0, -1, fn_1_285C);
}

void fn_1_2A90(s32 arg0)
{
    float spC[2];
    float temp_f31;
    float temp_f30;
    float temp_f28;
    float temp_f29;
    WindowData *temp_r29;
    StructBss234 *var_r31;
    s32 i;

    temp_r29 = &winData[arg0];
    var_r31 = &lbl_1_bss_234;
    temp_f31 = temp_r29->pos_x;
    temp_f30 = temp_r29->pos_y;
    temp_f28 = temp_r29->h;
    temp_f29 = temp_r29->w;
    for (i = 0; i < var_r31->unk00; i++) {
        HuWinMesMaxSizeGet(1, spC, lbl_1_data_20[var_r31->unk44[i]]);
        var_r31->unk08[i]
            = HuWinCreate(temp_f31 + temp_f29 + 16.0f + var_r31->unk80[i][0], temp_f30 + 26.0f + var_r31->unk80[i][1], spC[0], spC[1], 1);
        winData[var_r31->unk08[i]].mess_shadow_color = 9;
        HuWinMesColSet(var_r31->unk08[i], 0);
        HuWinScissorSet(var_r31->unk08[i], temp_f31 + 20.0f, temp_f30, temp_f29 + 20.0f, temp_f28);
        HuWinBGTPLvlSet(var_r31->unk08[i], 0.0f);
        HuPrcVSleep();
        fn_1_2744(var_r31->unk08[i], lbl_1_data_20[var_r31->unk44[i]]);
    }
    var_r31->unk04 = 4.0f;
    HuPrcVSleep();
}

void fn_1_2D94(s32 arg0)
{
    float sp10[2];
    float temp_f31;
    float temp_f29;
    float spC;
    float temp_f30;
    WindowData *temp_r30;
    StructBss234 *var_r31;
    s32 i;

    temp_r30 = &winData[arg0];
    var_r31 = &lbl_1_bss_234;
    temp_f31 = temp_r30->pos_x;
    temp_f29 = temp_r30->pos_y;
    spC = temp_r30->h;
    temp_f30 = temp_r30->w;
    while (TRUE) {
        for (i = 0; i < var_r31->unk00; i++) {
            var_r31->unk80[i][0] -= var_r31->unk04;
            HuWinPosSet(var_r31->unk08[i], temp_f31 + temp_f30 + 16.0f + var_r31->unk80[i][0], 26.0f + temp_f29 + var_r31->unk80[i][1]);
        }
        if (var_r31->unk00 >= 2) {
            HuWinMesMaxSizeGet(1, sp10, lbl_1_data_20[var_r31->unk44[2]]);
            if (temp_f31 + temp_f30 + 16.0f + var_r31->unk80[2][0] + sp10[0] <= temp_f31 + temp_f30 - 16.0f) {
                var_r31->unk04 += 0.75f;
            }
        }
        HuWinMesMaxSizeGet(1, sp10, lbl_1_data_20[var_r31->unk44[var_r31->unk00 - 1]]);
        if (temp_f31 + temp_f30 + 16.0f + var_r31->unk80[var_r31->unk00 - 1][0] + sp10[0] <= temp_f31 - 16.0f) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcVSleep();
}

void fn_1_3020(void)
{
    s32 i;
    StructBss234 *var_r30;

    var_r30 = &lbl_1_bss_234;
    for (i = 0; i < var_r30->unk00; i++) {
        HuWinKill(var_r30->unk08[i]);
        HuPrcVSleep();
    }
    HuPrcVSleep();
}

void fn_1_3088(void)
{
    float sp8[2];
    StructBss234 *var_r31;
    s32 i;

    var_r31 = &lbl_1_bss_234;
    var_r31->unk00 = rand8() % 2 + 10;
    if (var_r31->unk00 >= 15) {
        var_r31->unk00 = 15;
    }
    for (i = 0; i < 15; i++) {
        var_r31->unk44[i] = -1;
    }
    for (i = 0; i < var_r31->unk00; i++) {
        var_r31->unk44[i] = rand8() % 8;
    }
    var_r31->unk80[0][0] = 0.0f;
    var_r31->unk80[0][1] = 0.0f;
    for (i = 1; i < var_r31->unk00; i++) {
        HuWinMesMaxSizeGet(1, sp8, lbl_1_data_20[var_r31->unk44[i - 1]]);
        var_r31->unk80[i][0] = var_r31->unk80[i - 1][0] + sp8[0] + 8.0f;
        var_r31->unk80[i][1] = var_r31->unk80[0][1];
    }
}

void fn_1_31FC(omObjData *arg0)
{
    StructBss220 *var_r29;
    ModelData *temp_r30;
    s32 i;

    var_r29 = &lbl_1_bss_220;
    temp_r30 = &Hu3DData[arg0->model[8]];
    for (i = 0; i < 3; i++) {
        Hu3DData[arg0->model[i + 5]].rot.y += 360.0f / (2500.0f + 2500.0f * i);
    }
    if (arg0->work[0] == 0 && arg0->work[2]++ >= 600) {
        arg0->work[2] = 0;
        if (rand8() % 2 == 0) {
            arg0->work[0] = 1;
        }
    }
    switch (arg0->work[0]) {
        case 10:
            var_r29->unk04 = 11;
            fn_1_11818(arg0, 10, 12, 1, 0);
            Hu3DModelAttrReset(arg0->model[10], HU3D_ATTR_DISPOFF);
            fn_1_614(1, 10, 4.0f);
            HuAudFXPlay(0x6CF);
            /* fallthrough */
        case 1:
        case 11:
            fn_1_11818(arg0, 0, 0, 1, 0);
            fn_1_11818(arg0, 3, 3, 1, 0);
            fn_1_11818(arg0, 4, 4, 1, 0);
            fn_1_11818(arg0, 5, 5, 1, 0);
            fn_1_11818(arg0, 6, 6, 1, 0);
            fn_1_11818(arg0, 7, 7, 1, 0);
            if (arg0->work[0] == 1) {
                HuAudFXPlay(0x6CE);
            }
            arg0->work[0] = 99;
            break;
        case 2:
            arg0->work[0] = 3;
            fn_1_11818(arg0, 0, 0, 1, 0);
            fn_1_11818(arg0, 1, 1, 1, 0);
            fn_1_11818(arg0, 2, 2, 1, 0);
            fn_1_11818(arg0, 3, 3, 1, 0);
            fn_1_11818(arg0, 4, 4, 1, 0);
            fn_1_11818(arg0, 5, 5, 1, 0);
            fn_1_11818(arg0, 6, 6, 1, 0);
            fn_1_11818(arg0, 7, 7, 1, 0);
            fn_1_11818(arg0, 9, 9, 1, 0);
            Hu3DModelAttrReset(arg0->model[9], HU3D_ATTR_DISPOFF);
            HuAudFXPlay(0x6D0);
            break;
        case 3:
            fn_1_614(6, -1, 8.0f);
            if (Hu3DMotionTimeGet(arg0->model[3]) >= 30.0f) {
                arg0->work[0] = 99;
                fn_1_11818(arg0, 8, 8, 0, 0);
                fn_1_614(6, -1, 128.0f);
                HuAudFXPlay(0x6DA);
                omVibrate(fn_1_538C(0), 12, 12, 0);
                omVibrate(fn_1_538C(1), 12, 12, 0);
                omVibrate(fn_1_538C(2), 12, 12, 0);
                omVibrate(fn_1_538C(3), 12, 12, 0);
                Hu3DModelAttrReset(arg0->model[8], HU3D_ATTR_DISPOFF);
            }
            break;
        case 99:
            if (Hu3DMotionEndCheck(arg0->model[3]) != 0) {
                arg0->work[0] = 0;
                fn_1_11818(arg0, 3, 10, 1, 1);
                fn_1_11818(arg0, 4, 11, 1, 1);
                Hu3DModelAttrSet(arg0->model[9], HU3D_ATTR_DISPOFF);
            }
            break;
    }
    if (Hu3DMotionTimeGet(arg0->model[10]) >= 25.0f && var_r29->unk04 == 0) {
        var_r29->unk04 = 1;
        fn_1_614(1, 10, 4.0f);
    }
    else if (Hu3DMotionTimeGet(arg0->model[10]) >= 40.0f && var_r29->unk04 == 1) {
        var_r29->unk04 = 2;
        fn_1_614(1, 10, 4.0f);
    }
    switch (arg0->work[1]) {
        case 1:
            if (arg0->work[3] >= 360.0f) {
                arg0->work[3] = 0;
            }
            temp_r30->pos.y = fn_1_110FC(temp_r30->pos.y, fn_1_1122C(210.0f, 220.0f, arg0->work[3]++, 360.0f), 30.0f);
            break;
        case 2:
            temp_r30->pos.y = fn_1_110FC(temp_r30->pos.y, 60.0f, 20.0f);
            arg0->work[3] = 0;
            break;
        case 3:
            temp_r30->pos.y = fn_1_110FC(temp_r30->pos.y, 260.0f, 20.0f);
            arg0->work[3] = 0;
            break;
    }
}

void fn_1_39B4(omObjData *arg0)
{
    fn_1_11818(arg0, 0, 0, 1, 2);
    Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, -680.0f);
    fn_1_11818(arg0, 1, 1, 1, 2);
    Hu3DModelPosSet(arg0->model[2], 0.0f, 0.0f, -680.0f);
    fn_1_11818(arg0, 2, 2, 1, 2);
    Hu3DModelPosSet(arg0->model[3], 525.0f, 0.0f, -1150.0f);
    fn_1_11818(arg0, 3, 10, 1, 1);
    Hu3DModelPosSet(arg0->model[4], -525.0f, 0.0f, -1150.0f);
    fn_1_11818(arg0, 4, 11, 1, 1);
    fn_1_11818(arg0, 5, 5, 1, 2);
    fn_1_11818(arg0, 6, 6, 1, 2);
    fn_1_11818(arg0, 7, 7, 1, 2);
    Hu3DModelPosSet(arg0->model[8], 0.0f, 210.0f, -320.0f);
    Hu3DModelAttrSet(arg0->model[8], HU3D_ATTR_DISPOFF);
    fn_1_11818(arg0, 8, 8, 1, 1);
    Hu3DModelAttrSet(arg0->model[9], HU3D_ATTR_DISPOFF);
    fn_1_11818(arg0, 9, 9, 1, 2);
    arg0->work[0] = arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
}

void fn_1_3BF0(omObjData *arg0)
{
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 21));
    arg0->motion[0] = Hu3DMotionIDGet(arg0->model[0]);
    Hu3DModelShadowMapSet(arg0->model[0]);
    fn_1_11818(arg0, 0, 0, 1, 2);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 22));
    arg0->motion[1] = Hu3DMotionIDGet(arg0->model[1]);
    Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, -680.0f);
    Hu3DModelShadowMapSet(arg0->model[1]);
    fn_1_11818(arg0, 1, 1, 1, 2);
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 23));
    arg0->motion[2] = Hu3DMotionIDGet(arg0->model[2]);
    Hu3DModelPosSet(arg0->model[2], 0.0f, 0.0f, -680.0f);
    Hu3DModelShadowSet(arg0->model[2]);
    fn_1_11818(arg0, 2, 2, 1, 2);
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 24));
    arg0->motion[3] = Hu3DMotionIDGet(arg0->model[3]);
    arg0->motion[10] = Hu3DJointMotionFile(arg0->model[3], DATA_MAKE_NUM(DATADIR_M436, 26));
    Hu3DModelPosSet(arg0->model[3], 525.0f, 0.0f, -1150.0f);
    Hu3DModelShadowSet(arg0->model[3]);
    fn_1_11818(arg0, 3, 10, 1, 1);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 25));
    arg0->motion[4] = Hu3DMotionIDGet(arg0->model[4]);
    arg0->motion[11] = Hu3DJointMotionFile(arg0->model[4], DATA_MAKE_NUM(DATADIR_M436, 27));
    Hu3DModelPosSet(arg0->model[4], -525.0f, 0.0f, -1150.0f);
    Hu3DModelShadowSet(arg0->model[4]);
    fn_1_11818(arg0, 4, 11, 1, 1);
    arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 10));
    arg0->motion[5] = Hu3DMotionIDGet(arg0->model[5]);
    Hu3DModelPosSet(arg0->model[5], 0.0f, 150.0f, 0.0f);
    Hu3DModelLayerSet(arg0->model[5], 1);
    fn_1_11818(arg0, 5, 5, 1, 2);
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 11));
    arg0->motion[6] = Hu3DMotionIDGet(arg0->model[6]);
    Hu3DModelPosSet(arg0->model[6], 0.0f, 150.0f, 0.0f);
    fn_1_11818(arg0, 6, 6, 1, 2);
    arg0->model[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 12));
    arg0->motion[7] = Hu3DMotionIDGet(arg0->model[7]);
    Hu3DModelPosSet(arg0->model[7], 0.0f, 150.0f, 0.0f);
    fn_1_11818(arg0, 7, 7, 1, 2);
    arg0->model[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 8));
    arg0->motion[8] = Hu3DMotionIDGet(arg0->model[8]);
    Hu3DModelPosSet(arg0->model[8], 0.0f, 210.0f, -320.0f);
    Hu3DModelShadowSet(arg0->model[8]);
    Hu3DModelAttrSet(arg0->model[8], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(arg0->model[8], 2);
    fn_1_11818(arg0, 8, 8, 1, 1);
    arg0->model[9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 28));
    arg0->motion[9] = Hu3DMotionIDGet(arg0->model[9]);
    Hu3DModelAttrSet(arg0->model[9], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(arg0->model[9], 2);
    fn_1_11818(arg0, 9, 9, 1, 2);
    arg0->model[10] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 29));
    arg0->motion[12] = Hu3DMotionIDGet(arg0->model[10]);
    Hu3DModelAttrSet(arg0->model[10], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(arg0->model[10], 2);
    fn_1_11818(arg0, 10, 12, 1, 2);
    arg0->work[0] = arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
    arg0->func = fn_1_31FC;
}

void fn_1_420C(omObjData *arg0)
{
    s32 i;

    switch (arg0->work[0]) {
        case 1:
            arg0->work[0] = 0;
            for (i = 0; i < 8; i++) {
                Hu3DModelAttrReset(arg0->model[i + 1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(arg0->model[i + 9], HU3D_ATTR_DISPOFF);
                fn_1_11818(arg0, i + 1, i + 1, 1, 0);
            }
            break;
        case 2:
            arg0->work[0] = 0;
            Hu3DModelAttrReset(arg0->model[arg0->work[1] + 1], HU3D_ATTR_DISPOFF);
            fn_1_11818(arg0, arg0->work[1] + 1, arg0->work[1] + 1, 1, 0);
            break;
    }
}

void fn_1_4304(omObjData *arg0)
{
    StructBss1BC *var_r30;
    s32 i;

    var_r30 = &lbl_1_bss_1BC;
    for (i = 0; i < 8; i++) {
        var_r30->unk04[i].x = -2000.0 * cosd(287.5f - 5.0f * i);
        var_r30->unk04[i].y = 0.0f;
        var_r30->unk04[i].z = -2000.0 * sind(287.5f - 5.0f * i) - 1500.0;
    }
    for (i = 0; i < 8; i++) {
        Hu3DModelPosSet(arg0->model[i + 1], var_r30->unk04[i].x, var_r30->unk04[i].y + 65.0f, var_r30->unk04[i].z);
        Hu3DModelAttrSet(arg0->model[i + 1], HU3D_ATTR_DISPOFF);
        fn_1_11818(arg0, i + 1, i + 1, 1, 2);
    }
    for (i = 0; i < 8; i++) {
        Hu3DModelPosSet(arg0->model[i + 9], var_r30->unk04[i].x, var_r30->unk04[i].y, var_r30->unk04[i].z);
        Hu3DModelAttrSet(arg0->model[i + 9], HU3D_ATTR_DISPOFF);
    }
    arg0->work[0] = arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
}

void fn_1_4594(omObjData *arg0)
{
    StructBss1BC *var_r30;
    s32 i;

    var_r30 = &lbl_1_bss_1BC;
    for (i = 0; i < 8; i++) {
        var_r30->unk04[i].x = -2000.0 * cosd(287.5f - 5.0f * i);
        var_r30->unk04[i].y = 0.0f;
        var_r30->unk04[i].z = -2000.0 * sind(287.5f - 5.0f * i) - 1500.0;
    }
    for (i = 0; i < 8; i++) {
        arg0->model[i + 1] = Hu3DModelCreateFile(lbl_1_data_0[i]);
        arg0->motion[i + 1] = Hu3DMotionIDGet(arg0->model[i + 1]);
        Hu3DModelPosSet(arg0->model[i + 1], var_r30->unk04[i].x, 65.0f + var_r30->unk04[i].y, var_r30->unk04[i].z);
        Hu3DModelAttrSet(arg0->model[i + 1], HU3D_ATTR_DISPOFF);
        fn_1_11818(arg0, i + 1, i + 1, 1, 2);
    }
    for (i = 0; i < 8; i++) {
        arg0->model[i + 9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 9));
        Hu3DModelPosSet(arg0->model[i + 9], var_r30->unk04[i].x, var_r30->unk04[i].y, var_r30->unk04[i].z);
        Hu3DModelShadowSet(arg0->model[i + 9]);
    }
    arg0->work[0] = arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
    arg0->func = fn_1_420C;
}

void fn_1_48AC(omObjData *arg0)
{
    StructBss1A8 *sp8;

    sp8 = &lbl_1_bss_1A8;
    switch (arg0->work[3]) {
        case 1:
            arg0->work[3] = 0;
            fn_1_11818(arg0, 0, 2, 5, 0);
            break;
        case 2:
            arg0->work[3] = 0;
            fn_1_11818(arg0, 0, 1, 30, 1);
            break;
        case 3:
            arg0->work[3] = 0;
            fn_1_11818(arg0, 0, 3, 5, 0);
            break;
        case 4:
            arg0->work[3] = 0;
            fn_1_11818(arg0, 0, 2, 5, 1);
            break;
        case 5:
            arg0->work[3] = 0;
            fn_1_11818(arg0, 0, 2, 5, 0);
            break;
    }
    if (arg0->work[2] == 1) {
        arg0->work[2] = 0;
        fn_1_11818(arg0, 1, 11, 1, 0);
        Hu3DModelAttrReset(arg0->model[1], HU3D_ATTR_DISPOFF);
    }
}

void fn_1_49FC(omObjData *arg0)
{
    omSetTra(arg0, 0.0f, 37.0f, -565.0f);
    omSetSca(arg0, 1.5f, 1.5f, 1.5f);
    Hu3DModelHookReset(arg0->model[0]);
    fn_1_11818(arg0, 0, 1, 1, 1);
    arg0->work[0] = arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
}

void fn_1_4AB4(s32 arg0)
{
    ModelData *var_r28;
    HsfData *temp_r31;
    HsfMaterial *var_r30;
    s32 i;

    var_r28 = &Hu3DData[arg0];
    temp_r31 = var_r28->hsfData;
    var_r30 = temp_r31->material;
    for (i = 0; i < temp_r31->materialCnt; i++, var_r30++) {
        var_r30->flags = 0x10;
    }
}

void fn_1_4B1C(omObjData *arg0)
{
    StructBss1A8 *sp8;

    sp8 = &lbl_1_bss_1A8;
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 31));
    arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 32));
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 33));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 34));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 35));
    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 36));
    arg0->motion[5] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 37));
    arg0->motion[6] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 38));
    arg0->motion[7] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 39));
    arg0->motion[8] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 40));
    arg0->motion[9] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 41));
    arg0->motion[10] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 42));
    arg0->motion[12] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 43));
    omSetTra(arg0, 0.0f, 37.0f, -565.0f);
    omSetSca(arg0, 1.5f, 1.5f, 1.5f);
    Hu3DModelShadowSet(arg0->model[0]);
    fn_1_11818(arg0, 0, 1, 1, 1);
    arg0->work[0] = arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 30));
    arg0->motion[11] = Hu3DMotionIDGet(arg0->model[1]);
    fn_1_11818(arg0, 0, 11, 1, 2);
    Hu3DModelPosSet(arg0->model[1], 0.0f, 300.0f, -770.0f);
    Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF);
    arg0->func = fn_1_48AC;
}

void fn_1_4EA8(omObjData *arg0)
{
    switch (arg0->work[3]) {
        case 1:
            arg0->work[3] = 0;
            if (arg0->work[0] == 0) {
                fn_1_11818(arg0, 0, 2, 5, 0);
                fn_1_11818(arg0, 1, 5, 5, 2);
            }
            else {
                fn_1_11818(arg0, 0, 3, 5, 0);
            }
            break;
        case 2:
            arg0->work[3] = 0;
            if (arg0->work[0] == 0) {
                fn_1_11818(arg0, 0, 0, 30, 1);
                fn_1_11818(arg0, 1, 5, 30, 1);
            }
            else {
                fn_1_11818(arg0, 0, 0, 30, 1);
            }
            break;
    }
}

void fn_1_4FB0(omObjData *arg0)
{
    s32 temp_r30;

    temp_r30 = arg0->work[0];
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 46));
    if (temp_r30 == 0) {
        arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 48));
        arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 49));
        arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 50));
        omSetTra(arg0, -400.0f, 37.0f, -425.0f);
        arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 58));
        arg0->motion[5] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_M436, 59));
        arg0->motion[6] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_M436, 60));
        Hu3DModelHookSet(arg0->model[0], "g007m0-itemhook_r", arg0->model[1]);
        Hu3DModelLayerSet(arg0->model[0], 2);
        Hu3DModelLayerSet(arg0->model[1], 2);
        fn_1_11818(arg0, 0, 0, 1, 1);
        fn_1_11818(arg0, 1, 5, 1, 1);
    }
    else {
        arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 47));
        arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 51));
        arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 52));
        arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 53));
        arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 54));
        arg0->motion[5] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 55));
        arg0->motion[6] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 56));
        arg0->motion[7] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, 57));
        omSetTra(arg0, 400.0f, 37.0f, -475.0f);
        omSetRot(arg0, 0.0f, -15.0f, 0.0f);
        fn_1_11818(arg0, 0, 0, 1, 1);
    }
    Hu3DModelShadowSet(arg0->model[0]);
    arg0->func = fn_1_4EA8;
}

s32 fn_1_538C(s32 arg0)
{
    StructBss3E4 *temp_r31;

    temp_r31 = &lbl_1_bss_3E4[arg0];
    return temp_r31->unk04;
}

s32 fn_1_53B4(void)
{
    StructBss3E4 *temp_r29;
    s32 var_r30;
    s32 i;

    var_r30 = 0;
    for (i = 0; i < 4; i++) {
        temp_r29 = &lbl_1_bss_3E4[i];
        if (temp_r29->unk0C != 0) {
            var_r30++;
        }
    }
    return var_r30;
}

s32 fn_1_5414(s32 arg0)
{
    StructBss3E4 *temp_r31;

    temp_r31 = &lbl_1_bss_3E4[arg0];
    if (temp_r31->unk0C != 0) {
        return 1;
    }
    return 0;
}

s32 fn_1_5450(s32 arg0)
{
    StructBss3E4 *temp_r31;

    temp_r31 = &lbl_1_bss_3E4[arg0];
    if (HuPadBtnDown[temp_r31->unk18] == 0x100) {
        return 1;
    }
    return 0;
}

void fn_1_54A0(void)
{
    StructBss3E4 *temp_r31;
    s32 sp8[4];
    s32 i;

    sp8[0] = GWPlayerCurrGet();
    for (i = 1; i < 4; i++) {
        sp8[i] = sp8[i - 1] + 1;
        if (sp8[i] >= 4) {
            sp8[i] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        temp_r31 = &lbl_1_bss_3E4[i];
        temp_r31->unk04 = sp8[i];
        temp_r31->unk08 = GWPlayerCfg[temp_r31->unk04].group;
        temp_r31->unk0C = GWPlayerCfg[temp_r31->unk04].iscom;
        if (temp_r31->unk0C != 0) {
            temp_r31->unk10 = GWPlayerCfg[temp_r31->unk04].diff;
        }
        else {
            temp_r31->unk10 = 0;
        }
        temp_r31->unk14 = GWPlayerCfg[temp_r31->unk04].character;
        temp_r31->unk18 = GWPlayerCfg[temp_r31->unk04].pad_idx;
    }
}

s32 fn_1_5608(omObjData *arg0, Vec arg1, float arg2, float arg3, float arg4, float arg5, s32 arg6)
{
    float var_f31;
    float var_f30;
    float var_f27;
    float var_f26;
    s32 var_r30;
    StructBss3E4 *sp18;

    var_r30 = 0;
    sp18 = &lbl_1_bss_3E4[arg0->work[0]];
    var_f31 = arg1.x - arg0->trans.x;
    var_f30 = arg0->trans.z - arg1.z;
    var_f26 = 90.0 + atan2d(var_f30, var_f31);
    var_f27 = sqrtf(var_f31 * var_f31 + var_f30 * var_f30);
    if (var_f27 <= arg4) {
        var_f31 = var_f30 = 0.0f;
        var_r30 = 1;
    }
    else {
        var_f31 = 72.0f * (var_f31 / var_f27);
        var_f30 = 72.0f * (var_f30 / var_f27);
    }
    var_f27 = arg3 * (sqrtf(var_f31 * var_f31 + var_f30 * var_f30) / 72.0f);
    if (var_f27 >= arg3) {
        var_f27 = arg3;
    }
    else if (var_f27 <= 1.0f) {
        var_f31 = var_f30 = var_f27 = 0.0f;
        var_r30 = 1;
    }
    if (var_f31 != 0.0f || var_f30 != 0.0f || arg2 >= 0.0f) {
        if (arg2 >= 0.0f && var_f31 == 0.0f && var_f30 == 0.0f) {
            var_f26 = arg2;
        }
        if (var_f26 >= 180.0f) {
            if (arg0->rot.y - var_f26 >= 180.0f) {
                arg0->rot.y -= 360.0f;
            }
            if (arg0->rot.y - var_f26 < -180.0f) {
                arg0->rot.y += 360.0f;
            }
        }
        else {
            if (arg0->rot.y - var_f26 > 180.0f) {
                arg0->rot.y -= 360.0f;
            }
            if (arg0->rot.y - var_f26 <= -180.0f) {
                arg0->rot.y += 360.0f;
            }
        }
        arg0->rot.y = (var_f26 + arg0->rot.y * (arg5 - 1.0f)) / arg5;
    }
    arg0->trans.x += var_f27 * sind(arg0->rot.y);
    arg0->trans.z += var_f27 * cosd(arg0->rot.y);
    if (arg6 == 0) {
        if (var_f27 >= 6.75f) {
            fn_1_11B18(arg0, 0, 2, 15, 1);
        }
        else if (var_f27 > 0.0f) {
            fn_1_11B18(arg0, 0, 1, 15, 1);
        }
        else {
            fn_1_11B18(arg0, 0, 0, 15, 1);
        }
    }
    return var_r30;
}

void fn_1_5CD0(omObjData *arg0)
{
    StructBss3E4 *sp8;
    char **temp_r26;
    s32 var_r22;
    s32 i, j;
    ModelData *temp_r24;
    HsfData *temp_r27;
    HsfMaterial *var_r31;
    StructBss3E4 *temp_r30;
    HsfAttribute *temp_r23;

    sp8 = &lbl_1_bss_3E4[arg0->work[0]];
    if (arg0->work[2] != 1) {
        return;
    }
    var_r22 = 1;
    temp_r24 = &Hu3DData[arg0->model[0]];
    temp_r27 = temp_r24->hsfData;
    var_r31 = temp_r27->material;
    temp_r30 = &lbl_1_bss_3E4[arg0->work[0]];
    if (temp_r30->unk14 == 3) {
        for (i = 0; i < temp_r24->hsfData->materialCnt; i++, var_r31++) {
            if (i != 1 && i != 2) {
                var_r31->color[0] *= temp_r30->unk2C;
                if (var_r31->color[0] == 0) {
                    var_r31->color[0] = 0;
                }
                var_r31->color[1] *= temp_r30->unk2C;
                if (var_r31->color[1] == 0) {
                    var_r31->color[1] = 0;
                }
                var_r31->color[2] *= temp_r30->unk2C;
                if (var_r31->color[2] == 0) {
                    var_r31->color[2] = 0;
                }
            }
        }
    }
    else {
        temp_r26 = CharModelTexNameGet(temp_r30->unk14, 2);
        for (i = 0; i < temp_r27->materialCnt; i++, var_r31++) {
            var_r22 = 1;
            for (j = 0; j < var_r31->numAttrs; j++) {
                temp_r23 = &temp_r27->attribute[var_r31->attrs[j]];
                if (strcmp(temp_r26[0], temp_r23->bitmap->name) == 0 || strcmp(temp_r26[1], temp_r23->bitmap->name) == 0) {
                    var_r22 = 0;
                }
            }
            if (var_r22 != 0) {
                var_r31->color[0] *= temp_r30->unk2C;
                if (var_r31->color[0] == 0) {
                    var_r31->color[0] = 0;
                }
                var_r31->color[1] *= temp_r30->unk2C;
                if (var_r31->color[1] == 0) {
                    var_r31->color[1] = 0;
                }
                var_r31->color[2] *= temp_r30->unk2C;
                if (var_r31->color[2] == 0) {
                    var_r31->color[2] = 0;
                }
            }
        }
    }
    temp_r30->unk2C -= 0.01;
    if (temp_r30->unk2C < 0.0f) {
        temp_r30->unk2C = 0.0f;
    }
}

void fn_1_6060(omObjData *arg0)
{
    u32 temp_r29 = arg0->work[0];
    StructBss3E4 *temp_r30 = &lbl_1_bss_3E4[temp_r29];
    Vec sp8[] = { { -600.0f, 0.0f, 300.0f }, { -600.0f, 0.0f, 150.0f }, { -450.0f, 0.0f, 150.0f }, { -300.0f, 0.0f, 150.0f } };

    arg0->model[0] = CharModelCreate(temp_r30->unk14, 2);
    arg0->motion[0] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
    arg0->motion[1] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 2));
    arg0->motion[2] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 3));
    arg0->motion[3] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 88));
    arg0->motion[4] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 89));
    arg0->motion[5] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 90));
    arg0->motion[6] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 72));
    arg0->motion[7] = CharModelMotionCreate(temp_r30->unk14, DATA_MAKE_NUM(DATADIR_MARIOMOT, 28));
    arg0->motion[8] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M436, temp_r30->unk14));
    Hu3DModelShadowSet(arg0->model[0]);
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
    fn_1_11B18(arg0, 0, 0, 0, 1);
    omSetTra(arg0, sp8[temp_r29].x, sp8[temp_r29].y, sp8[temp_r29].z);
    CharModelMotionDataClose(temp_r30->unk14);
    temp_r30->unk2C = 1.0f;
    arg0->func = fn_1_5CD0;
}

// unused
s16 gap_04_00000182_data[] = { 0, 0x43, 0, 0x43, 1, 0x43, 2, 0x43, 3, 0x43, 4, 0x43, 5, 0x43, 6, 0x43, 7 };

s32 fn_1_62C4(omObjData *arg0)
{
    Mtx sp8;
    StructBss4A4 *var_r25;
    StructBssD8 *var_r31;
    StructBss1A8 *var_r28;
    StructBss3E4 *temp_r27;
    s32 i;

    var_r25 = &lbl_1_bss_4A4;
    var_r31 = &lbl_1_bss_D8;
    var_r28 = &lbl_1_bss_1A8;
    temp_r27 = &lbl_1_bss_3E4[var_r25->unk00];
    if (arg0->work[3] == 1) {
        arg0->work[3] = 0;
        arg0->work[1] = 1;
        arg0->work[2] = 0;
        var_r31->unk04 = 1;
        for (i = 0; i < 6; i++) {
            var_r31->unk08[i] = -(50.0f * i);
        }
    }
    switch (arg0->work[1]) {
        case 1:
            arg0->work[1] = 2;
            fn_1_11818(var_r28->unk00, 0, 8, 5, 0);
            break;
        case 2:
            if (Hu3DMotionTimeGet(var_r28->unk00->model[0]) == 90.0f) {
                arg0->work[1] = 3;
                fn_1_11818(temp_r27->unk00, 0, 7, 5, 0);
                Hu3DMotionTimeSet(var_r28->unk00->model[0], 90.0f);
                Hu3DMotionSpeedSet(var_r28->unk00->model[0], 0.0f);
                HuAudCharVoicePlay(temp_r27->unk14, 0x123);
                HuAudFXPlay(0x6D5);
                omVibrate(temp_r27->unk04, 120, 12, 0);
            }
            break;
        case 3:
            Hu3DModelObjMtxGet(var_r28->unk00->model[0], "g000m0-itemhook_M", sp8);
            temp_r27->unk00->work[2] = 1;
            for (i = 0; i < 6; i++) {
                if (var_r31->unk04 == 1 || (var_r31->unk04 == 0 && var_r31->unk08[i] > 0.0f)) {
                    var_r31->unk08[i] += 10.0f;
                }
                if (var_r31->unk08[i] > 0.0f) {
                    var_r31->unk48[i] += 0.1f;
                    var_r31->unk28[i] -= 5.0f;
                    if (var_r31->unk88[i] == 0.0f) {
                        fn_1_11818(arg0, i + 1, i + 1, 1, 1);
                    }
                    if (var_r31->unk88[i] < 8.0f) {
                        var_r31->unk68[i] += 0.025f;
                    }
                    else if (var_r31->unk88[i] < 23.0f) {
                        var_r31->unk68[i] = 0.7f;
                    }
                    else if (var_r31->unk88[i] < 31.0f) {
                        var_r31->unk68[i] -= 0.1f;
                        if (var_r31->unk68[i] < 0.0f) {
                            var_r31->unk68[i] = 0.0f;
                        }
                    }
                    var_r31->unk88[i] += 1.0f;
                }
                Hu3DModelPosSet(arg0->model[i + 1], sp8[0][3], sp8[1][3] + var_r31->unk28[i], sp8[2][3] + var_r31->unk08[i]);
                Hu3DModelScaleSet(arg0->model[i + 1], 1.5f * var_r31->unk48[i], 1.5f * var_r31->unk48[i], 1.5f * var_r31->unk48[i]);
                Hu3DModelTPLvlSet(arg0->model[i + 1], var_r31->unk68[i]);
                if (var_r31->unk88[i] == 31.0f) {
                    var_r31->unk08[i] = 0.0f;
                    var_r31->unk28[i] = 0.0f;
                    var_r31->unk48[i] = 0.0f;
                    var_r31->unk68[i] = 0.5f;
                    var_r31->unk88[i] = 0.0f;
                }
            }
            if (arg0->work[2]++ >= 120) {
                var_r31->unk04 = 0;
                Hu3DMotionSpeedSet(var_r28->unk00->model[0], 1.0f);
                temp_r27->unk00->work[2] = 0;
            }
            if (arg0->work[2] >= 10 && arg0->work[2] <= 120) {
                fn_1_67C(6, 8.0f);
            }
            break;
    }
}

void fn_1_68E8(omObjData *arg0)
{
    StructBss1A8 *var_r30;

    var_r30 = &lbl_1_bss_1A8;
    fn_1_11818(var_r30->unk00, 0, 8, 5, 0);
    arg0->func = (void *)fn_1_62C4; // fn_1_62C4 must return s32 to match
}

void fn_1_6944(omObjData *arg0)
{
    StructBssD8 *var_r29;
    s32 i;

    var_r29 = &lbl_1_bss_D8;
    for (i = 0; i < 6; i++) {
        if (i % 2 == 0) {
            arg0->model[i + 1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 44));
            arg0->motion[i + 1] = Hu3DMotionIDGet(arg0->model[i + 1]);
        }
        else {
            arg0->model[i + 1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M436, 45));
            arg0->motion[i + 1] = Hu3DMotionIDGet(arg0->model[i + 1]);
        }
        fn_1_11818(arg0, i + 1, i + 1, 5, 1);
        Hu3DModelPosSet(arg0->model[i + 1], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(arg0->model[i + 1], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(arg0->model[i + 1], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(arg0->model[i + 1], 2);
        var_r29->unk08[i] = -(50.0f * i);
        var_r29->unk28[i] = 0.0f;
        var_r29->unk48[i] = 0.0f;
        var_r29->unk68[i] = 0.5f;
        var_r29->unk88[i] = 0.0f;
    }
    var_r29->unk04 = 1;
    arg0->func = (void *)fn_1_62C4; // fn_1_62C4 must return s32 to match
}

void fn_1_6BDC(void)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk10 = 0.0f;
    var_r31->unk14 = 300.0f;
    var_r31->unk18 = 1740.0f;
    var_r31->unk28 = -10.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk38 = 300.0f;
    fn_1_125F4(var_r31, 200.0f);
}

void fn_1_6C8C(void)
{
    StructBss32C *var_r31;
    StructBss32C sp8;

    var_r31 = &lbl_1_bss_32C;
    sp8.unk04 = 0.0f;
    sp8.unk08 = 200.0f;
    sp8.unk0C = -50.0f;
    sp8.unk1C = 5.0f;
    sp8.unk20 = 0.0f;
    sp8.unk24 = 0.0f;
    sp8.unk34 = 200.0f;
    fn_1_14D24(var_r31, &sp8, var_r31->unk3C++, 30.0f, 5.0f);
}

void fn_1_6D64(void)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk10 = 0.0f;
    var_r31->unk14 = 200.0f;
    var_r31->unk18 = -50.0f;
    var_r31->unk28 = 5.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk38 = 200.0f;
    fn_1_125F4(var_r31, 200.0f);
}

void fn_1_6E14(void)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk10 = 0.0f;
    var_r31->unk14 = 300.0f;
    var_r31->unk18 = -550.0f;
    var_r31->unk28 = -15.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk38 = 1200.0f;
    fn_1_125F4(var_r31, 45.0f);
}

void fn_1_6EC4(void)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk10 = 0.0f;
    var_r31->unk14 = 150.0f;
    var_r31->unk18 = -550.0f;
    var_r31->unk28 = -15.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk38 = 1200.0f;
    fn_1_125F4(var_r31, 30.0f);
}

void fn_1_6F74(void)
{
    StructBss32C *var_r31;
    StructBss32C sp8;

    var_r31 = &lbl_1_bss_32C;
    sp8.unk04 = 0.0f;
    sp8.unk08 = 100.0f;
    sp8.unk0C = -550.0f;
    sp8.unk1C = -20.0f;
    sp8.unk20 = 0.0f;
    sp8.unk24 = 0.0f;
    sp8.unk34 = 2400.0f;
    fn_1_13C48(var_r31, &sp8, var_r31->unk3C++, 10.0f, 5.0f);
}

void fn_1_704C(void)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk10 = 0.0f;
    var_r31->unk14 = 150.0f;
    var_r31->unk18 = -550.0f;
    var_r31->unk28 = -15.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk38 = 1200.0f;
    fn_1_125F4(var_r31, 20.0f);
}

void fn_1_70FC(void)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk10 = 0.0f;
    var_r31->unk14 = 300.0f;
    var_r31->unk18 = -550.0f;
    var_r31->unk28 = -15.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk38 = 1200.0f;
    fn_1_125F4(var_r31, 20.0f);
}

void fn_1_71AC(s32 arg0)
{
    StructBss32C *var_r23;

    var_r23 = &lbl_1_bss_32C;
    fn_1_12294(var_r23);
    switch (arg0) {
        case 0:
            fn_1_8A4(fn_1_6E14);
            break;
        case 1:
            fn_1_8A4(fn_1_6EC4);
            break;
        case 2:
            fn_1_8A4(fn_1_6F74);
            break;
        case 3:
            fn_1_8A4(fn_1_6C8C);
            break;
        case 4:
            fn_1_8A4(fn_1_6BDC);
            break;
        case 5:
            fn_1_8A4(fn_1_6D64);
            break;
        case 10:
            fn_1_8A4(fn_1_704C);
            break;
        case 11:
            fn_1_8A4(fn_1_70FC);
            break;
    }
}

void fn_1_72CC(void)
{
    float sp18[] = { 0.0f, 0.0f };
    StructBss1A8 *var_r30;
    s32 var_r31;

    var_r30 = &lbl_1_bss_1A8;
    fn_1_26D4(sp18, MAKE_MESSID(29, 0));
    fn_1_26D4(sp18, MAKE_MESSID(29, 1));
    var_r31 = fn_1_2230((580.0f - sp18[0]) / 2, 80.0f, sp18[0], sp18[1], 2);
    HuAudFXPlay(0x6D1);
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 0));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 1));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    fn_1_2468(var_r31);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_77F0(void)
{
    float sp18[] = { 0.0f, 0.0f };
    StructBss1A8 *var_r30;
    s32 var_r31;

    var_r30 = &lbl_1_bss_1A8;
    fn_1_26D4(sp18, MAKE_MESSID(29, 3));
    var_r31 = fn_1_2230((580.0f - sp18[0]) / 2, 100.0f, sp18[0], sp18[1], 2);
    HuAudFXPlay(0x6D2);
    var_r30->unk00->work[3] = 3;
    fn_1_2744(var_r31, MAKE_MESSID(29, 3));
    fn_1_24D0(var_r31, REFRESH_RATE);
    lbl_1_bss_4 = 2;
    fn_1_24D0(var_r31, REFRESH_RATE);
    var_r30->unk00->work[3] = 2;
    fn_1_2468(var_r31);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_7B58(s32 arg0)
{
    float sp10[2] = { 0.0f, 0.0f };
    StructBss180 *var_r30 = &lbl_1_bss_180[0];
    s32 sp18[] = { MAKE_MESSID(29, 6), MAKE_MESSID(29, 8), MAKE_MESSID(29, 10), MAKE_MESSID(29, 12), MAKE_MESSID(29, 15), MAKE_MESSID(29, 17) };
    s32 var_r31;

    var_r30->unk00->work[3] = 1;
    HuPrcSleep(15);
    fn_1_26D4(sp10, sp18[arg0]);
    HuAudFXPlayVolPan(0x3E, 0x7F, 0x20);
    var_r31 = fn_1_2230(20.0f, 360.0f, sp10[0], sp10[1], 0);
    fn_1_2744(var_r31, sp18[arg0]);
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    fn_1_2468(var_r31);
}

void fn_1_7F1C(void)
{
    float sp2D8[2] = { 0.0f, 0.0f };
    StructBss180 *var_r30;
    s32 var_r31;

    var_r30 = &lbl_1_bss_180[1];
    fn_1_26D4(sp2D8, MAKE_MESSID(29, 5));
    fn_1_26D4(sp2D8, MAKE_MESSID(29, 7));
    fn_1_26D4(sp2D8, MAKE_MESSID(29, 9));
    fn_1_26D4(sp2D8, MAKE_MESSID(29, 11));
    fn_1_26D4(sp2D8, MAKE_MESSID(29, 13));
    fn_1_26D4(sp2D8, MAKE_MESSID(29, 14));
    fn_1_26D4(sp2D8, MAKE_MESSID(29, 16));
    var_r31 = fn_1_2230(550.0f - sp2D8[0], 340.0f, sp2D8[0], sp2D8[1], 1);
    HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 5));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    fn_1_7B58(0);
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 7));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    fn_1_7B58(1);
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 9));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    fn_1_7B58(2);
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 11));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    fn_1_7B58(3);
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 13));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 14));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    fn_1_7B58(4);
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 16));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    fn_1_7B58(5);
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 18));
    fn_1_24D0(var_r31, 0);
    var_r30->unk00->work[3] = 2;
    fn_1_2468(var_r31);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_A5A8(void)
{
    float sp9C[2] = { 0.0f, 0.0f };
    StructBss220 *sp68;
    StructBss1A8 *var_r28;
    s32 var_r31;

    sp68 = &lbl_1_bss_220;
    var_r28 = &lbl_1_bss_1A8;
    fn_1_26D4(sp9C, MAKE_MESSID(29, 19));
    fn_1_26D4(sp9C, MAKE_MESSID(29, 20));
    fn_1_26D4(sp9C, MAKE_MESSID(29, 21));
    fn_1_26D4(sp9C, MAKE_MESSID(29, 22));
    fn_1_26D4(sp9C, MAKE_MESSID(29, 37));
    var_r31 = fn_1_2230((580.0f - sp9C[0]) / 2, 80.0f, sp9C[0], sp9C[1], 2);
    HuAudFXPlay(0x6D2);
    var_r28->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 19));
    fn_1_24D0(var_r31, 0);
    var_r28->unk00->work[3] = 2;
    var_r28->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 20));
    fn_1_24D0(var_r31, 0);
    var_r28->unk00->work[3] = 2;
    var_r28->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 21));
    fn_1_24D0(var_r31, 3 * REFRESH_RATE);
    var_r28->unk00->work[3] = 2;
    sp68->unk00->work[0] = 10;
    fn_1_2744(var_r31, MAKE_MESSID(29, 22));
    fn_1_24D0(var_r31, REFRESH_RATE);
    var_r28->unk00->work[3] = 4;
    fn_1_2A90(var_r31);
    fn_1_2D94(var_r31);
    fn_1_3020();
    var_r28->unk00->work[3] = 2;
    HuPrcSleep(2 * REFRESH_RATE);
    var_r28->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 37));
    fn_1_24D0(var_r31, 0);
    var_r28->unk00->work[3] = 2;
    fn_1_2468(var_r31);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_B3D4(void)
{
    float sp1C[2] = { 0.0f, 0.0f };
    StructBss180 *var_r30;
    s32 var_r31;

    var_r30 = &lbl_1_bss_180[1];
    lbl_1_bss_4 = 0;
    fn_1_26D4(sp1C, MAKE_MESSID(29, 64));
    var_r31 = fn_1_2230(550.0f - sp1C[0], 340.0f, sp1C[0], sp1C[1], 1);
    HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
    var_r30->unk00->work[3] = 1;
    fn_1_2744(var_r31, MAKE_MESSID(29, 64));
    fn_1_25B8(var_r31);
    var_r30->unk00->work[3] = 2;
    fn_1_2468(var_r31);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_B7E0(void) { }

s32 fn_1_B7E4(void)
{
    StructBss220 *var_r31;

    var_r31 = &lbl_1_bss_220;
    if (fn_1_11F04(&lbl_1_bss_C0, 0) == 80) {
        fn_1_71AC(3);
        lbl_1_bss_3A4[0] = HuAudSeqPlay(6);
    }
    if (fn_1_11F04(&lbl_1_bss_C0, 0) == 115) {
        fn_1_71AC(5);
    }
    if (fn_1_11F04(&lbl_1_bss_C0, 0) == 180) {
        fn_1_71AC(0);
    }
    if (fn_1_11F04(&lbl_1_bss_C0, 0) == 0) {
        var_r31->unk00->work[0] = 10;
    }
    if (fn_1_11F04(&lbl_1_bss_C0, 0) == 150) {
        var_r31->unk00->work[0] = 1;
    }
    if (fn_1_11F04(&lbl_1_bss_C0, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_C0);
    }
    return 0;
}

void fn_1_B968(void)
{
    lbl_1_bss_4 = 0;
    HuPrcChildCreate(fn_1_72CC, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_B9B4(void)
{
    if (lbl_1_bss_4 == 1 && fn_1_11F04(&lbl_1_bss_C0, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_C0);
    }
    return 0;
}

void fn_1_BA10(void)
{
    StructBss3E4 *var_r30;
    s32 i;

    lbl_1_bss_4 = 0;
    HuPrcChildCreate(fn_1_77F0, 100, 0x2000, 0, HuPrcCurrentGet());
    for (i = 0; i < 4; i++) {
        var_r30 = &lbl_1_bss_3E4[i];
        Hu3DModelAttrReset(var_r30->unk00->model[0], HU3D_ATTR_DISPOFF);
    }
}

s32 fn_1_BAA4(void)
{
    StructBss220 *var_r31;
    StructBss1BC *var_r30;
    StructBss220 *var_r29;

    var_r31 = &lbl_1_bss_220;
    var_r30 = &lbl_1_bss_1BC;
    if (lbl_1_bss_4 == 2) {
        lbl_1_bss_4 = 0;
        var_r31->unk00->work[0] = 2;
        var_r30->unk00->work[0] = 1;
    }
    if (lbl_1_bss_4 == 1 && fn_1_11F04(&lbl_1_bss_C0, 0) == 0) {
        var_r29 = &lbl_1_bss_220;
        var_r29->unk00->work[1] = 1;
    }
    if (lbl_1_bss_4 == 1 && fn_1_11F04(&lbl_1_bss_C0, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_C0);
    }
    return 0;
}

void fn_1_BBA4(void)
{
    fn_1_71AC(10);
}

s32 fn_1_BBF4(void)
{
    if (fn_1_11F04(&lbl_1_bss_C0, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_C0);
    }
    return 0;
}

void fn_1_BC3C(void)
{
    HuPrcChildCreate(fn_1_B3D4, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_BC78(void)
{
    if (lbl_1_bss_4 != 0 && fn_1_11F04(&lbl_1_bss_C0, 1) != 0) {
        if (lbl_1_bss_8 != 0) {
            return fn_1_11D74(&lbl_1_bss_C0);
        }
        fn_1_11E70(&lbl_1_bss_C0, 6);
    }
    return 0;
}

void fn_1_BCF8(void)
{
    StructBss1A8 *var_r31;

    var_r31 = &lbl_1_bss_1A8;
    fn_1_11818(var_r31->unk00, 0, 12, 60, 1);
    lbl_1_bss_4 = 0;
    HuPrcChildCreate(fn_1_7F1C, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_BD6C(void)
{
    StructBss1A8 *var_r31;

    var_r31 = &lbl_1_bss_1A8;
    if (lbl_1_bss_4 == 1 && fn_1_11F04(&lbl_1_bss_C0, 0) == 0) {
        fn_1_11818(var_r31->unk00, 0, 1, 60, 1);
    }
    if (lbl_1_bss_4 == 1 && fn_1_11F04(&lbl_1_bss_C0, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_C0);
    }
    return 0;
}

void fn_1_BE1C(void)
{
    fn_1_71AC(11);
}

s32 fn_1_BE6C(void)
{
    if (fn_1_11F04(&lbl_1_bss_C0, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_C0);
    }
    return 0;
}

void fn_1_BEB4(void)
{
    lbl_1_bss_4 = 0;
    HuPrcChildCreate(fn_1_A5A8, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_BF00(void)
{
    if (lbl_1_bss_4 == 1) {
        lbl_1_bss_4 = 2;
        HuAudSeqFadeOut(lbl_1_bss_3A4[0], 1000);
    }
    if (lbl_1_bss_4 != 0 && fn_1_11F04(&lbl_1_bss_C0, 1) != 0) {
        fn_1_71AC(2);
        return fn_1_11D74(&lbl_1_bss_C0);
    }
    return 0;
}

StructData1E8 lbl_1_data_1E8[] = { { fn_1_B7E0, fn_1_B7E4, 300 }, { fn_1_B968, fn_1_B9B4, 60 }, { fn_1_BA10, fn_1_BAA4, 60 },
    { fn_1_BBA4, fn_1_BBF4, 45 }, { fn_1_BC3C, fn_1_BC78, 60 }, { fn_1_BCF8, fn_1_BD6C, 60 }, { fn_1_BE1C, fn_1_BE6C, 45 },
    { fn_1_BEB4, fn_1_BF00, 15 }, { NULL, NULL, -1 } };

void fn_1_BFC8(void)
{
    fn_1_11D18(&lbl_1_bss_C0, lbl_1_data_1E8);
}

s32 fn_1_BFF8(void)
{
    s32 var_r31;

    var_r31 = 0;
    if (lbl_1_bss_C0.unk10 != NULL) {
        lbl_1_bss_C0.unk10();
        lbl_1_bss_C0.unk10 = NULL;
    }
    if (lbl_1_bss_C0.unk14 != NULL) {
        var_r31 = lbl_1_bss_C0.unk14();
    }
    return var_r31;
}

s32 fn_1_C090(s32 arg0, s32 arg1, s32 arg2)
{
    StructBss4A4 *var_r28;
    StructBss3E4 *temp_r31;
    StructBss1BC *var_r27;
    StructBss234 *var_r26;
    s32 var_r29;
    s32 var_r30;
    s32 spC;
    s32 var_r23;
    s32 temp_r22;
    s32 i;

    var_r29 = 0;
    var_r30 = arg1;
    spC = arg1;
    var_r28 = &lbl_1_bss_4A4;
    temp_r31 = &lbl_1_bss_3E4[arg0];
    var_r27 = &lbl_1_bss_1BC;
    var_r26 = &lbl_1_bss_234;
    if (temp_r31->unk0C != 0) {
        if (arg2 % 27 == 2 && temp_r31->unk24 == 0) {
            switch (temp_r31->unk10) {
                case 0:
                    if (arg2 <= 2 * REFRESH_RATE) {
                        var_r29 = 0;
                    }
                    else if (var_r28->unk04 <= 3) {
                        temp_r31->unk24 = var_r29 = 1;
                    }
                    else {
                        var_r29 = 0;
                    }
                    break;
                case 1:
                    if (arg2 <= 2 * REFRESH_RATE) {
                        var_r29 = 0;
                    }
                    else if (var_r28->unk04 <= 6) {
                        temp_r31->unk24 = var_r29 = 1;
                    }
                    else {
                        var_r29 = 0;
                    }
                    break;
                case 2:
                    if (arg2 <= REFRESH_RATE) {
                        var_r29 = 0;
                    }
                    else if (var_r28->unk04 <= 9) {
                        temp_r31->unk24 = var_r29 = 1;
                    }
                    else {
                        var_r29 = 0;
                    }
                    break;
                case 3:
                    if (arg2 <= REFRESH_RATE) {
                        var_r29 = 0;
                    }
                    else if (var_r28->unk04 <= 12) {
                        temp_r31->unk24 = var_r29 = 1;
                    }
                    else {
                        var_r29 = 0;
                    }
                    break;
            }
            if (var_r29 == 0) {
                temp_r31->unk28 = rand8() % 8;
            }
            else {
                var_r23 = 0;
                for (i = 0; i <= temp_r31->unk10; i++) {
                    temp_r22 = rand8() % 10;
                    if (var_r26->unk44[temp_r22] != -1) {
                        temp_r31->unk28 = var_r26->unk44[temp_r22];
                        var_r23 = 1;
                        break;
                    }
                }
                if (var_r23 == 0) {
                    temp_r31->unk28 = rand8() % 8;
                }
            }
        }
        if (temp_r31->unk24 == 1 && temp_r31->unk28 == var_r30) {
            var_r30 = 99;
        }
        else if (temp_r31->unk28 > var_r30 && temp_r31->unk00->trans.x >= var_r27->unk04[var_r30].x - 7.5f && var_r30 < 7) {
            var_r30++;
        }
        else if (temp_r31->unk28 < var_r30 && temp_r31->unk00->trans.x <= var_r27->unk04[var_r30].x + 7.5f && var_r30 > 0) {
            var_r30--;
        }
    }
    else {
        var_r30 = arg1;
        if (HuPadStkX[temp_r31->unk18] > 20.0f && temp_r31->unk00->trans.x >= var_r27->unk04[var_r30].x - 7.5f && var_r30 < 7) {
            var_r30++;
        }
        else if (HuPadStkX[temp_r31->unk18] < -20.0f && temp_r31->unk00->trans.x <= var_r27->unk04[var_r30].x + 7.5f && var_r30 > 0) {
            var_r30--;
        }
        else if (HuPadBtnDown[temp_r31->unk18] & 0x100) {
            var_r30 = 99;
        }
    }
    return var_r30;
}

void fn_1_C4E8(void)
{
    StructBss4A4 *var_r29;
    StructBss3E4 *temp_r30;
    StructBss1BC *var_r28;
    StructBss32C *var_r31;

    var_r29 = &lbl_1_bss_4A4;
    temp_r30 = &lbl_1_bss_3E4[var_r29->unk00];
    var_r28 = &lbl_1_bss_1BC;
    var_r31 = &lbl_1_bss_32C;
    var_r31->unk10 = temp_r30->unk00->trans.x;
    var_r31->unk14 = temp_r30->unk00->trans.y + 75.0f;
    var_r31->unk18 = var_r28->unk04[0].z - 100.0f;
    var_r31->unk28 = -10.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk38 = 750.0f;
    fn_1_125F4(var_r31, 10.0f);
}

void fn_1_C5E4(void)
{
    StructBss32C *var_r31;

    var_r31 = &lbl_1_bss_32C;
    var_r31->unk10 = 0.0f;
    var_r31->unk14 = 100.0f;
    var_r31->unk18 = -550.0f;
    var_r31->unk28 = -20.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk38 = 2400.0f;
    fn_1_125F4(var_r31, 360.0f);
}

void fn_1_C694(void)
{
    StructBss32C *var_r31;
    StructBss32C sp8;

    var_r31 = &lbl_1_bss_32C;
    sp8.unk04 = 0.0f;
    sp8.unk08 = 200.0f;
    sp8.unk0C = -550.0f;
    sp8.unk1C = -15.0f;
    sp8.unk20 = 0.0f;
    sp8.unk24 = 0.0f;
    sp8.unk34 = 1200.0f;
    fn_1_13C48(var_r31, &sp8, var_r31->unk3C++, 10.0f, 5.0f);
}

void fn_1_C76C(void)
{
    StructBss32C *var_r31;
    StructBss32C sp8;

    var_r31 = &lbl_1_bss_32C;
    sp8.unk04 = 0.0f;
    sp8.unk08 = 100.0f;
    sp8.unk0C = -550.0f;
    sp8.unk1C = -20.0f;
    sp8.unk20 = 0.0f;
    sp8.unk24 = 0.0f;
    sp8.unk34 = 2400.0f;
    fn_1_13C48(var_r31, &sp8, var_r31->unk3C++, 60.0f, 10.0f);
}

void fn_1_C844(s32 arg0)
{
    StructBss32C *var_r27;

    var_r27 = &lbl_1_bss_32C;
    fn_1_12294(var_r27);
    switch (arg0) {
        case 0:
            fn_1_8A4(fn_1_C4E8);
            break;
        case 1:
            fn_1_8A4(fn_1_C5E4);
            break;
        case 2:
            fn_1_8A4(fn_1_C694);
            break;
        case 3:
            fn_1_8A4(fn_1_C76C);
            break;
    }
}

void fn_1_C90C(void)
{
    float sp28[] = { 0.0f, 0.0f };
    s32 var_r28;
    s32 var_r31;
    StructBss1A8 *var_r27 = &lbl_1_bss_1A8;
    s32 sp3C[] = { MAKE_MESSID(29, 31), MAKE_MESSID(29, 32), MAKE_MESSID(29, 33) };

    var_r28 = rand8() % 3;
    HuPrcSleep(REFRESH_RATE + 10);
    fn_1_26D4(sp28, sp3C[var_r28]);
    var_r31 = fn_1_2230((580.0f - sp28[0]) / 2, 60.0f, sp28[0], sp28[1], 2);
    var_r27->unk00->work[2] = 1;
    HuAudFXPlay(0x6D2);
    HuAudFXPlay(0x6E3);
    fn_1_2744(var_r31, sp3C[var_r28]);
    fn_1_24D0(var_r31, 2 * REFRESH_RATE);
    fn_1_2468(var_r31);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_CCA4(void)
{
    float sp2C[] = { 0.0f, 0.0f };
    s32 var_r28;
    s32 var_r31;
    s32 sp24[] = { MAKE_MESSID(29, 34), MAKE_MESSID(29, 35) };

    var_r28 = rand8() % 2;
    HuPrcSleep(40);
    fn_1_26D4(sp2C, sp24[var_r28]);
    var_r31 = fn_1_2230((580.0f - sp2C[0]) / 2, 60.0f, sp2C[0], sp2C[1], 2);
    HuAudFXPlay(0x6D6);
    HuAudFXPlay(0x6D9);
    HuAudSeqAllFadeOut(100);
    fn_1_2744(var_r31, sp24[var_r28]);
    fn_1_24D0(var_r31, 2 * REFRESH_RATE);
    fn_1_2468(var_r31);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_D018(void)
{
    float sp2C[] = { 0.0f, 0.0f };
    s32 var_r31;

    HuPrcSleep(40);
    fn_1_26D4(sp2C, MAKE_MESSID(29, 36));
    var_r31 = fn_1_2230((580.0f - sp2C[0]) / 2, 60.0f, sp2C[0], sp2C[1], 2);
    HuAudFXPlay(0x6D6);
    HuAudFXPlay(0x6D9);
    HuAudSeqAllFadeOut(100);
    fn_1_2744(var_r31, MAKE_MESSID(29, 36));
    fn_1_24D0(var_r31, 2 * REFRESH_RATE);
    fn_1_2468(var_r31);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_D344(void)
{
    StructBss4A4 *var_r30;
    StructBss3E4 *temp_r31;
    StructBss1A8 *var_r29;

    var_r30 = &lbl_1_bss_4A4;
    temp_r31 = &lbl_1_bss_3E4[var_r30->unk00];
    temp_r31->unk1C = temp_r31->unk20 = temp_r31->unk24 = temp_r31->unk28 = 0;
    var_r29 = &lbl_1_bss_1A8;
    fn_1_11818(var_r29->unk00, 0, 12, 60, 1);
    fn_1_C844(0);
    fn_1_27C8(5);
}

s32 fn_1_D418(void)
{
    Vec sp14;
    StructBss4A4 *var_r30;
    StructBss3E4 *temp_r31;
    StructBss1BC *var_r28;
    StructBss180 *var_r26;
    StructBss3E4 *var_r25;
    s32 var_r27;
    s32 i;

    var_r27 = 0;
    var_r30 = &lbl_1_bss_4A4;
    temp_r31 = &lbl_1_bss_3E4[var_r30->unk00];
    var_r28 = &lbl_1_bss_1BC;
    fn_1_11F04(&lbl_1_bss_A8, 1);
    if (fn_1_11F04(&lbl_1_bss_A8, 0) < 10) {
        return 0;
    }
    if (temp_r31->unk20 == 0) {
        if (fn_1_2800()) {
            temp_r31->unk20 = 1;
            temp_r31->unk24 = 0;
        }
        else {
            var_r27 = fn_1_C090(var_r30->unk00, temp_r31->unk1C, fn_1_11F04(&lbl_1_bss_A8, 0));
            if (var_r27 == 99) {
                temp_r31->unk20 = 1;
                temp_r31->unk24 = 0;
                fn_1_2824();
            }
            else {
                temp_r31->unk1C = var_r27;
            }
        }
    }
    else if (temp_r31->unk24++ >= 60) {
        return fn_1_11D74(&lbl_1_bss_A8);
    }
    sp14.x = var_r28->unk04[temp_r31->unk1C].x;
    sp14.y = temp_r31->unk00->trans.y;
    sp14.z = var_r28->unk04[0].z - 100.0f;
    fn_1_5608(temp_r31->unk00, sp14, 0.0f, 9.0f, 5.0f, 2.0f, 0);
    if (temp_r31->unk00->trans.z > sp14.z) {
        temp_r31->unk00->trans.z = sp14.z;
    }
    if (temp_r31->unk00->trans.z < sp14.z) {
        temp_r31->unk00->trans.z = sp14.z;
    }
    var_r26 = &lbl_1_bss_180[1];
    fn_1_113CC(var_r26->unk00, 0, temp_r31->unk00, 0);
    for (i = 0; i < 4; i++) {
        if (var_r30->unk00 != i) {
            var_r25 = &lbl_1_bss_3E4[i];
            fn_1_113CC(var_r25->unk00, 0, temp_r31->unk00, 0);
        }
    }
    return 0;
}

void fn_1_D6C0(void)
{
    StructBss4A4 *var_r30;

    var_r30 = &lbl_1_bss_4A4;
    var_r30->unk0C = 0;
}

s32 fn_1_D6E4(void)
{
    StructBss4A4 *var_r29;
    StructBss3E4 *temp_r31;
    StructBss1BC *var_r30;
    StructBss180 *var_r26;
    StructBss3E4 *var_r25;
    s32 i;

    var_r29 = &lbl_1_bss_4A4;
    temp_r31 = &lbl_1_bss_3E4[var_r29->unk00];
    var_r30 = &lbl_1_bss_1BC;
    if (fn_1_11F04(&lbl_1_bss_A8, 0) < 30) {
        if (var_r30->unk04[temp_r31->unk1C].z - 100.0f > temp_r31->unk00->trans.z) {
            temp_r31->unk00->trans.z += 9.0f;
            fn_1_11B18(temp_r31->unk00, 0, 1, 10, 1);
            if (var_r30->unk04[temp_r31->unk1C].z - 100.0f < temp_r31->unk00->trans.z) {
                temp_r31->unk00->trans.z = var_r30->unk04[temp_r31->unk1C].z - 100.0f;
                fn_1_11B18(temp_r31->unk00, 0, 0, 10, 1);
            }
        }
        else {
            fn_1_11B18(temp_r31->unk00, 0, 0, 10, 1);
        }
    }
    else if (fn_1_11F04(&lbl_1_bss_A8, 0) == 30) {
        fn_1_11990(temp_r31->unk00, 0, 5, 30, 0);
    }
    else if (fn_1_11708(temp_r31->unk00, 0, 5, 35, 1) != 0 && var_r29->unk0C == 0) {
        var_r29->unk0C = 1;
        Hu3DModelHookSet(temp_r31->unk00->model[0], CharModelHookNameGet(temp_r31->unk14, 2, 0), var_r30->unk00->model[temp_r31->unk1C + 1]);
        if (temp_r31->unk14 != 7) {
            Hu3DModelPosSet(var_r30->unk00->model[temp_r31->unk1C + 1], 0.0f, 5.0f, 0.0f);
        }
        else {
            Hu3DModelPosSet(var_r30->unk00->model[temp_r31->unk1C + 1], 0.0f, -15.0f, 0.0f);
        }
        Hu3DModelScaleSet(var_r30->unk00->model[temp_r31->unk1C + 1], 0.75f, 0.75f, 0.75f);
        omVibrate(temp_r31->unk04, 12, 4, 2);
    }
    var_r26 = &lbl_1_bss_180[1];
    fn_1_113CC(var_r26->unk00, 0, temp_r31->unk00, 0);
    for (i = 0; i < 4; i++) {
        if (var_r29->unk00 != i) {
            var_r25 = &lbl_1_bss_3E4[i];
            fn_1_113CC(var_r25->unk00, 0, temp_r31->unk00, 0);
        }
    }
    if (fn_1_11F04(&lbl_1_bss_A8, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_A8);
    }
    // Required to match.
    if (0) {
        s32 var_r28 = 0;
        (void)var_r28;
        (void)var_r28;
        (void)var_r28;
        (void)var_r28;
        (void)var_r28;
        (void)var_r28;
    }
    return 0;
}

void fn_1_DA60(void)
{
    StructBss4A4 *var_r30;
    StructBss1A8 *sp8;
    StructBss3E4 *temp_r31;

    var_r30 = &lbl_1_bss_4A4;
    temp_r31 = &lbl_1_bss_3E4[var_r30->unk00];
    sp8 = &lbl_1_bss_1A8;
    var_r30->unk0C = 0;
    temp_r31->unk20 = temp_r31->unk24 = temp_r31->unk28 = 0;
    Hu3DMotionOverlaySet(temp_r31->unk00->model[0], temp_r31->unk00->motion[4]);
    Hu3DModelAttrSet(temp_r31->unk00->model[0], HU3D_MOTATTR_OVL_LOOP);
}

Vec lbl_1_data_254 = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_260 = { 0.0f, 0.0f, 0.0f }; // unused

s32 fn_1_DB00(void)
{
    StructBss4A4 *var_r30;
    StructBss220 *var_r28;
    StructBss1BC *sp8;
    StructBss3E4 *temp_r31;
    StructBss1A8 *var_r27;
    StructBss180 *var_r26;
    StructBss3E4 *var_r25;
    s32 i;

    var_r30 = &lbl_1_bss_4A4;
    var_r28 = &lbl_1_bss_220;
    sp8 = &lbl_1_bss_1BC;
    var_r27 = &lbl_1_bss_1A8;
    temp_r31 = &lbl_1_bss_3E4[var_r30->unk00];
    if (temp_r31->unk20 == 0 && fn_1_11F04(&lbl_1_bss_A8, 0) <= 180) {
        lbl_1_data_254.x = 0.0f;
        lbl_1_data_254.y = temp_r31->unk00->trans.y;
        lbl_1_data_254.z = 300.0f;
    }
    else if (temp_r31->unk20 == 1 && fn_1_11F04(&lbl_1_bss_A8, 0) <= 320) {
        lbl_1_data_254.x = 0.0f;
        lbl_1_data_254.y = temp_r31->unk00->trans.y;
        lbl_1_data_254.z = -240.0f;
    }
    temp_r31->unk20 += fn_1_5608(temp_r31->unk00, lbl_1_data_254, 180.0f, 8.0f, 30.0f, 5.0f, 0);
    if (temp_r31->unk20 == 1 && var_r30->unk0C == 0) {
        var_r30->unk0C = 1;
        fn_1_C844(1);
        fn_1_11B18(var_r27->unk00, 0, 1, 60, 0);
        var_r28->unk00->work[1] = 2;
    }
    var_r26 = &lbl_1_bss_180[1];
    fn_1_113CC(var_r26->unk00, 0, temp_r31->unk00, 0);
    for (i = 0; i < 4; i++) {
        if (var_r30->unk00 != i) {
            var_r25 = &lbl_1_bss_3E4[i];
            fn_1_113CC(var_r25->unk00, 0, temp_r31->unk00, 0);
        }
    }
    fn_1_11F04(&lbl_1_bss_A8, 1);
    if (temp_r31->unk20 == 2) {
        Hu3DModelAttrReset(*temp_r31->unk00->model, HU3D_MOTATTR_OVL_LOOP);
        return fn_1_11D74(&lbl_1_bss_A8);
    }
    return 0;
}

void fn_1_DDBC(void)
{
    StructBss4A4 *var_r30;
    StructBss1A8 *var_r29;
    StructBss3E4 *temp_r31;

    var_r30 = &lbl_1_bss_4A4;
    var_r29 = &lbl_1_bss_1A8;
    temp_r31 = &lbl_1_bss_3E4[var_r30->unk00];
    var_r30->unk0C = 0;
    var_r29->unk00->work[3] = 0;
    Hu3DMotionSet(temp_r31->unk00->model[0], temp_r31->unk00->motion[5]);
    Hu3DMotionTimeSet(temp_r31->unk00->model[0], 999.0f);
    Hu3DModelAttrReset(temp_r31->unk00->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(temp_r31->unk00->model[0], HU3D_MOTATTR_REV);
    Hu3DMotionOverlayReset(temp_r31->unk00->model[0]);
    temp_r31->unk20 = temp_r31->unk24 = temp_r31->unk28 = 0;
}

s32 fn_1_DEB0(void)
{
    StructBss4A4 *var_r30;
    StructBss220 *var_r28;
    StructBss1BC *var_r29;
    StructBss3E4 *temp_r31;
    ModelData *temp_r27;
    ModelData *temp_r26;
    StructBss180 *var_r25;

    var_r30 = &lbl_1_bss_4A4;
    var_r28 = &lbl_1_bss_220;
    var_r29 = &lbl_1_bss_1BC;
    temp_r31 = &lbl_1_bss_3E4[var_r30->unk00];
    temp_r27 = &Hu3DData[var_r28->unk00->model[8]];
    if (fn_1_11708(temp_r31->unk00, 0, 5, 30, 0) != 0 && var_r30->unk0C == 0) {
        Hu3DModelHookReset(temp_r31->unk00->model[0]);
        Hu3DModelPosSet(var_r29->unk00->model[temp_r31->unk1C + 1], 0.0f, temp_r27->pos.y, -355.0f);
        Hu3DModelScaleSet(var_r29->unk00->model[temp_r31->unk1C + 1], 1.0f, 1.0f, 1.0f);
        var_r30->unk0C = temp_r31->unk20 = 1;
    }
    if (temp_r31->unk20 == 1 && temp_r31->unk24++ >= REFRESH_RATE) {
        temp_r26 = &Hu3DData[var_r29->unk00->model[temp_r31->unk1C + 1]];
        var_r28->unk00->work[1] = 3;
        temp_r26->pos.y = temp_r27->pos.y;
        if (var_r30->unk0C == 1) {
            var_r30->unk0C = 2;
            var_r25 = &lbl_1_bss_180[1];
            fn_1_11818(var_r25->unk00, 0, 6, 60, 1);
        }
    }
    if (temp_r31->unk20 == 1 && fn_1_11F04(&lbl_1_bss_A8, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_A8);
    }
    return 0;
}

void fn_1_E0B0(void)
{
    StructBss4A4 *var_r31;
    StructBss1A8 *var_r30;
    StructBss3E4 *var_r29;

    var_r31 = &lbl_1_bss_4A4;
    var_r30 = &lbl_1_bss_1A8;
    var_r29 = &lbl_1_bss_3E4[var_r31->unk00];
    var_r31->unk08 = var_r31->unk0C = 0;
    fn_1_11990(var_r29->unk00, 0, 0, 30, 1);
    fn_1_11818(var_r30->unk00, 0, 4, 1, 0);
}

s32 fn_1_E144(void)
{
    StructBss4A4 *var_r31;
    StructBss220 *var_r28;
    StructBss1BC *var_r30;
    StructBss1A8 *var_r27;
    StructBss3E4 *temp_r29;
    StructBss180 *var_r25;

    var_r31 = &lbl_1_bss_4A4;
    var_r28 = &lbl_1_bss_220;
    var_r30 = &lbl_1_bss_1BC;
    var_r27 = &lbl_1_bss_1A8;
    temp_r29 = &lbl_1_bss_3E4[var_r31->unk00];
    if (fn_1_11708(var_r27->unk00, 0, 4, 80, 1) != 0 && var_r31->unk0C == 0) {
        var_r31->unk0C = 1;
        Hu3DModelHookSet(var_r27->unk00->model[0], "g000m0-itemhook_R", var_r30->unk00->model[temp_r29->unk1C + 1]);
        Hu3DModelPosSet(var_r30->unk00->model[temp_r29->unk1C + 1], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30->unk00->model[temp_r29->unk1C + 1], 0.0f, 90.0f, 0.0f);
        Hu3DModelScaleSet(var_r30->unk00->model[temp_r29->unk1C + 1], 0.5f, 0.5f, 0.5f);
        var_r28->unk00->work[1] = 1;
    }
    if (fn_1_11F04(&lbl_1_bss_A8, 0) == 180) {
        fn_1_C844(2);
    }
    if (var_r31->unk0C == 1) {
        var_r25 = &lbl_1_bss_180[1];
        var_r25->unk00->rot.y = fn_1_110FC(var_r25->unk00->rot.y, 280.0f, 10.0f);
    }
    if (fn_1_11F04(&lbl_1_bss_A8, 1) != 0) {
        var_r28->unk00->work[0] = 10;
        return fn_1_11D74(&lbl_1_bss_A8);
    }
    return 0;
}

void fn_1_E38C(void)
{
    StructBss4A4 *var_r31;
    StructBss220 *sp8;
    StructBss1A8 *var_r30;

    sp8 = &lbl_1_bss_220;
    var_r31 = &lbl_1_bss_4A4;
    var_r30 = &lbl_1_bss_1A8;
    if (var_r31->unk08 == 0) {
        var_r31->unk08 = 1;
        if (var_r31->unk04 > 3) {
            fn_1_11818(var_r30->unk00, 0, 9, 15, 0);
        }
        if (var_r31->unk04 > 3 && rand8() % 2 == 0) {
            var_r31->unk08 = 2;
        }
    }
    else if (var_r31->unk08 == 2) {
        var_r31->unk08 = 1;
        fn_1_11818(var_r30->unk00, 0, 10, 15, 0);
        if (var_r31->unk04 > 6 && rand8() % 2 == 0) {
            var_r31->unk08 = 3;
        }
    }
    else if (var_r31->unk08 == 3) {
        var_r31->unk08 = 1;
        fn_1_11818(var_r30->unk00, 0, 10, 15, 0);
    }
}

s32 fn_1_E4CC(void)
{
    StructBss4A4 *var_r31;
    StructBss1A8 *var_r30;

    var_r31 = &lbl_1_bss_4A4;
    var_r30 = &lbl_1_bss_1A8;
    if (Hu3DMotionEndCheck(var_r30->unk00->model[0]) && fn_1_11F04(&lbl_1_bss_A8, 1) != 0) {
        if (var_r31->unk08 != 1) {
            return fn_1_11E70(&lbl_1_bss_A8, 5);
        }
        else {
            return fn_1_11D74(&lbl_1_bss_A8);
        }
    }
    return 0;
}

void fn_1_E56C(void)
{
    StructBss4A4 *var_r31;
    StructBss234 *var_r30;
    StructBss3E4 *var_r28;
    s32 i;

    var_r31 = &lbl_1_bss_4A4;
    var_r30 = &lbl_1_bss_234;
    var_r28 = &lbl_1_bss_3E4[var_r31->unk00];
    var_r31->unk08 = 1;
    for (i = 0; i < var_r30->unk00; i++) {
        if (var_r30->unk44[i] == var_r28->unk1C) {
            var_r31->unk08 = 0;
            var_r30->unk44[i] = -1;
            break;
        }
    }
    if (var_r30->unk00 == var_r31->unk04) {
        var_r31->unk08 = 2;
    }
}

s32 fn_1_E628(void)
{
    StructBss4A4 *var_r31;

    var_r31 = &lbl_1_bss_4A4;
    if (var_r31->unk08 != 0) {
        fn_1_11E70(&lbl_1_bss_A8, 10);
    }
    else {
        fn_1_11D74(&lbl_1_bss_A8);
    }
}

void fn_1_E680(void)
{
    StructBss4A4 *var_r31;
    StructBss1A8 *var_r30;

    var_r31 = &lbl_1_bss_4A4;
    var_r30 = &lbl_1_bss_1A8;
    var_r31->unk08 = var_r31->unk0C = 0;
    fn_1_11818(var_r30->unk00, 0, 7, 15, 0);
    lbl_1_bss_4 = 0;
    HuPrcChildCreate(fn_1_C90C, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_E710(void)
{
    StructBss4A4 *var_r29;
    StructBss1A8 *var_r28;
    StructBss1BC *var_r31;
    StructBss3E4 *temp_r30;
    StructBss180 *var_r27;

    var_r29 = &lbl_1_bss_4A4;
    var_r31 = &lbl_1_bss_1BC;
    var_r28 = &lbl_1_bss_1A8;
    temp_r30 = &lbl_1_bss_3E4[var_r29->unk00];
    if (fn_1_11708(var_r28->unk00, 0, 7, 30, 1) != 0 && var_r29->unk08 == 0) {
        var_r29->unk08 = 1;
    }
    if (fn_1_11708(var_r28->unk00, 0, 7, 40, 1) != 0 && var_r29->unk0C == 0) {
        var_r29->unk0C = 1;
        var_r27 = &lbl_1_bss_180[1];
        fn_1_11818(var_r27->unk00, 0, 7, 10, 0);
        Hu3DModelHookReset(var_r28->unk00->model[0]);
        Hu3DModelPosSet(var_r31->unk00->model[temp_r30->unk1C + 1], var_r31->unk04[temp_r30->unk1C].x, var_r31->unk04[temp_r30->unk1C].y + 65.0f,
            var_r31->unk04[temp_r30->unk1C].z);
        Hu3DModelRotSet(var_r31->unk00->model[temp_r30->unk1C + 1], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(var_r31->unk00->model[temp_r30->unk1C + 1], 1.0f, 1.0f, 1.0f);
    }
    if (lbl_1_bss_4 == 1) {
        lbl_1_bss_4 = 2;
    }
    if (fn_1_11F04(&lbl_1_bss_A8, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_A8);
    }
    return 0;
}

void fn_1_E930(void)
{
    StructBss4A4 *var_r29;
    StructBss3E4 *var_r28;
    StructBss180 *var_r31;
    s32 var_r30;

    var_r29 = &lbl_1_bss_4A4;
    var_r30 = var_r29->unk00 + 1;
    if (var_r30 == 4) {
        var_r30 = 0;
    }
    var_r28 = &lbl_1_bss_3E4[var_r30];
    fn_1_11990(var_r28->unk00, 0, 1, 15, 1);
    var_r31 = &lbl_1_bss_180[1];
    fn_1_11818(var_r31->unk00, 0, 0, 1, 1);
    Hu3DMotionSpeedSet(var_r31->unk00->model[0], 1.0f);
    fn_1_C844(3);
}

s32 fn_1_EA04(void)
{
    Vec sp14[] = { { -600.0f, 0.0f, 300.0f }, { -600.0f, 0.0f, 150.0f }, { -450.0f, 0.0f, 150.0f }, { -300.0f, 0.0f, 150.0f } };
    StructBss4A4 *var_r30;
    StructBss1BC *var_r27;
    StructBss3E4 *temp_r31;
    StructBss3E4 *temp_r26;
    s32 i;
    s32 var_r28;

    var_r30 = &lbl_1_bss_4A4;
    var_r27 = &lbl_1_bss_1BC;
    var_r28 = var_r30->unk00 + 1;
    if (var_r28 == 4) {
        var_r28 = 0;
    }
    for (i = 0; i < 4; i++) {
        temp_r31 = &lbl_1_bss_3E4[var_r28];
        if (i != 0) {
            fn_1_5608(temp_r31->unk00, sp14[i], 0.0f, 9.0f, 10.0f, 8.0f, 0);
        }
        else {
            temp_r31->unk00->trans.x -= 1.0f;
            temp_r31->unk00->trans.z += 5.0f;
            temp_r31->unk00->rot.y = fn_1_110FC(temp_r31->unk00->rot.y, 0.0f, 10.0f);
            if (temp_r31->unk00->trans.x <= -600.0f) {
                temp_r31->unk00->trans.x = -600.0f;
            }
            if (temp_r31->unk00->trans.z >= var_r27->unk04[0].z - 100.0f) {
                fn_1_11B18(temp_r31->unk00, 0, 0, 15, 1);
                temp_r31->unk00->trans.z = var_r27->unk04[0].z - 100.0f;
            }
        }
        if (i != 0 && i != 3) {
            if (temp_r31->unk00->trans.z > 150.0f) {
                temp_r31->unk00->trans.z = 150.0f;
            }
            if (temp_r31->unk00->trans.z < 150.0f) {
                temp_r31->unk00->trans.z = 150.0f;
            }
        }
        var_r28++;
        if (var_r28 == 4) {
            var_r28 = 0;
        }
    }
    if (fn_1_11F04(&lbl_1_bss_A8, 1) != 0) {
        temp_r26 = &lbl_1_bss_3E4[var_r30->unk00];
        temp_r26->unk00->rot.y = 0.0f;
        var_r30->unk00++;
        if (var_r30->unk00 == 4) {
            var_r30->unk00 = 0;
        }
        var_r30->unk04++;
        return fn_1_11E70(&lbl_1_bss_A8, 0);
    }
    return 0;
}

void fn_1_ED4C(void)
{
    StructBss4A4 *var_r31;
    StructBss1A8 *var_r30;

    var_r31 = &lbl_1_bss_4A4;
    var_r30 = &lbl_1_bss_1A8;
    fn_1_11818(var_r30->unk00, 0, 6, 1, 0);
    lbl_1_bss_4 = 0;
    if (var_r31->unk08 == 1) {
        HuPrcChildCreate(fn_1_CCA4, 100, 0x2000, 0, HuPrcCurrentGet());
    }
    else {
        HuPrcChildCreate(fn_1_D018, 100, 0x2000, 0, HuPrcCurrentGet());
    }
    var_r31->unk04 = var_r31->unk08 = var_r31->unk0C = 0;
}

s32 fn_1_EE10(void)
{
    StructBss4A4 *var_r30;
    StructBss220 *var_r26;
    StructBss1BC *var_r29;
    StructBss1A8 *var_r27;
    StructBss180 *var_r31;
    StructBss3E4 *temp_r28;

    var_r30 = &lbl_1_bss_4A4;
    var_r26 = &lbl_1_bss_220;
    var_r29 = &lbl_1_bss_1BC;
    var_r27 = &lbl_1_bss_1A8;
    var_r31 = &lbl_1_bss_180[1];
    temp_r28 = &lbl_1_bss_3E4[var_r30->unk00];
    lbl_1_bss_48[0][3] = 400.0f;
    lbl_1_bss_48[1][3] = 91.0f;
    lbl_1_bss_48[2][3] = -436.0f;
    var_r31->unk00->rot.y = fn_1_110FC(var_r31->unk00->rot.y, 360.0f, 10.0f);
    if (fn_1_11708(var_r27->unk00, 0, 6, 40, 1) != 0 && var_r30->unk0C == 0) {
        var_r30->unk0C = 1;
        Hu3DModelHookReset(var_r27->unk00->model[0]);
        Hu3DModelObjMtxGet(var_r27->unk00->model[0], "g000m0-itemhook_R", lbl_1_bss_78);
        Hu3DModelPosSet(var_r29->unk00->model[temp_r28->unk1C + 1], lbl_1_bss_78[0][3], lbl_1_bss_78[1][3], lbl_1_bss_78[2][3]);
        Hu3DModelRotSet(var_r29->unk00->model[temp_r28->unk1C + 1], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(var_r29->unk00->model[temp_r28->unk1C + 1], 1.0f, 1.0f, 1.0f);
        Hu3DMotionSpeedSet(var_r26->unk00->model[8], -1.0f);
        var_r30->unk04 = 1;
        HuAudFXPlay(0x6E0);
    }
    if (var_r30->unk04 == 1) {
        lbl_1_bss_3C.x = fn_1_1113C(lbl_1_bss_78[0][3], lbl_1_bss_48[0][3], lbl_1_bss_14, 30.0f);
        if (lbl_1_bss_14 < 13) {
            lbl_1_bss_3C.y = fn_1_11164(lbl_1_bss_78[1][3], 500.0f, lbl_1_bss_14, 13.0f);
        }
        else {
            lbl_1_bss_3C.y = fn_1_112F4(500.0f, lbl_1_bss_48[1][3], lbl_1_bss_14 - 13, 17.0f);
        }
        lbl_1_bss_3C.z = fn_1_1113C(lbl_1_bss_78[2][3], lbl_1_bss_48[2][3], lbl_1_bss_14, 30.0f);
        if (lbl_1_bss_14 == 10) {
            fn_1_11818(var_r31->unk00, 0, 4, 1, 0);
            Hu3DMotionSpeedSet(var_r31->unk00->model[0], 1.0f);
        }
        if (fn_1_11708(var_r31->unk00, 0, 4, 21, 1) != 0 && var_r30->unk08 == 0) {
            var_r30->unk08 = 1;
            Hu3DMotionSpeedSet(var_r31->unk00->model[0], 0.0f);
        }
        else {
            Hu3DModelPosSet(var_r29->unk00->model[temp_r28->unk1C + 1], lbl_1_bss_3C.x, lbl_1_bss_3C.y, lbl_1_bss_3C.z);
        }
        if (lbl_1_bss_14++ >= 30) {
            var_r30->unk04 = 2;
        }
    }
    else if (var_r30->unk04 == 2) {
        Hu3DModelHookSet(var_r31->unk00->model[0], "g007m0-itemhook_c", var_r29->unk00->model[temp_r28->unk1C + 1]);
        Hu3DModelPosSet(var_r29->unk00->model[temp_r28->unk1C + 1], 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(var_r31->unk00->model[0], 1.0f);
    }
    if (lbl_1_bss_4 == 1 && Hu3DMotionEndCheck(var_r31->unk00->model[0])) {
        lbl_1_bss_14 = 0;
        fn_1_11818(var_r31->unk00, 0, 5, 1, 0);
        return fn_1_11D74(&lbl_1_bss_A8);
    }
    return 0;
}

void fn_1_F404(void)
{
    StructBss4A4 *var_r29;
    StructBss1A8 *spC;
    StructBssD8 *var_r28;
    StructBss180 *var_r31;
    StructBss180 *var_r30;
    StructBss3E4 *sp8;

    var_r29 = &lbl_1_bss_4A4;
    spC = &lbl_1_bss_1A8;
    var_r28 = &lbl_1_bss_D8;
    var_r31 = &lbl_1_bss_180[1];
    var_r30 = &lbl_1_bss_180[0];
    sp8 = &lbl_1_bss_3E4[var_r29->unk00];
    var_r28->unk00->work[3] = 1;
    var_r31->unk00->rot.y = 0.0f;
    fn_1_11818(var_r31->unk00, 0, 5, 30, 1);
    fn_1_11818(var_r30->unk00, 0, 1, 30, 1);
    fn_1_11818(var_r30->unk00, 1, 6, 30, 1);
}

s32 fn_1_F4F0(void)
{
    if (fn_1_11F04(&lbl_1_bss_A8, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_A8);
    }
    return 0;
}

StructData1E8 lbl_1_data_290[]
    = { { fn_1_D344, fn_1_D418, 600 }, { fn_1_D6C0, fn_1_D6E4, 90 }, { fn_1_DA60, fn_1_DB00, 300 }, { fn_1_DDBC, fn_1_DEB0, 150 },
          { fn_1_E0B0, fn_1_E144, 240 }, { fn_1_E38C, fn_1_E4CC, 90 }, { fn_1_E56C, fn_1_E628, 120 }, { fn_1_E680, fn_1_E710, 120 },
          { fn_1_E930, fn_1_EA04, 120 }, { NULL, NULL, -1 }, { fn_1_ED4C, fn_1_EE10, -1 }, { fn_1_F404, fn_1_F4F0, 60 }, { NULL, NULL, -1 } };

void fn_1_F538(void)
{
    fn_1_11D18(&lbl_1_bss_A8, lbl_1_data_290);
}

s32 fn_1_F568(void)
{
    s32 var_r31;

    var_r31 = 0;
    if (lbl_1_bss_A8.unk10 != NULL) {
        lbl_1_bss_A8.unk10();
        lbl_1_bss_A8.unk10 = NULL;
    }
    if (lbl_1_bss_A8.unk14 != NULL) {
        var_r31 = lbl_1_bss_A8.unk14();
    }
    return var_r31;
}

void fn_1_F600(void)
{
    StructBss4A4 *var_r30;
    StructBss3E4 *temp_r31;

    var_r30 = &lbl_1_bss_4A4;
    temp_r31 = &lbl_1_bss_3E4[var_r30->unk00];
    var_r30->unk0C = 0;
    lbl_1_data_E0 = temp_r31->unk00->model[0];
    lbl_1_data_E4 = temp_r31->unk00->motion[8];
    lbl_1_data_E8 = temp_r31->unk14;
    HuPrcChildCreate(fn_1_0, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_F6B0(void)
{
    StructBss4A4 *var_r31;
    StructBss3E4 *temp_r30;

    var_r31 = &lbl_1_bss_4A4;
    temp_r30 = &lbl_1_bss_3E4[var_r31->unk00];
    if (fn_1_11F04(&lbl_1_bss_24, 0) == 120) {
        fn_1_11818(temp_r30->unk00, 0, 8, 30, 0);
        HuAudSStreamPlay(3);
    }
    if (fn_1_11F04(&lbl_1_bss_24, 1) != 0) {
        return fn_1_11D74(&lbl_1_bss_24);
    }
    return 0;
}

StructData1E8 lbl_1_data_32C[] = { { fn_1_F600, fn_1_F6B0, 360 }, { NULL, NULL, -1 } };

void fn_1_F75C(void)
{
    fn_1_11D18(&lbl_1_bss_24, lbl_1_data_32C);
}

s32 fn_1_F78C(void)
{
    s32 var_r31;

    var_r31 = 0;
    if (lbl_1_bss_24.unk10 != NULL) {
        lbl_1_bss_24.unk10();
        lbl_1_bss_24.unk10 = NULL;
    }
    if (lbl_1_bss_24.unk14 != NULL) {
        var_r31 = lbl_1_bss_24.unk14();
    }
    return var_r31;
}

void fn_1_F824(omObjData *arg0)
{
    StructBss1A8 *sp8;
    StructBss4A4 *var_r30;
    StructBss3E4 *temp_r29;
    s32 i;

    sp8 = &lbl_1_bss_1A8;
    if (WipeStatGet() == 0) {
        CharModelKill(-1);
        MGSeqKillAll();
        HuAudFadeOut(1);
        var_r30 = &lbl_1_bss_4A4;
        temp_r29 = &lbl_1_bss_3E4[var_r30->unk00];
        for (i = 0; i < 4; i++) {
            GWPlayerCoinWinSet(i, 0);
        }
        GWPlayerCoinWinSet(temp_r29->unk04, 1);
        omOvlReturnEx(1, 1);
        arg0->func = NULL;
    }
}

void fn_1_F924(omObjData *arg0)
{
    if (omSysExitReq == 1) {
        HuAudSeqAllFadeOut(250);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
        arg0->func = fn_1_F824;
    }
}

void fn_1_F984(void)
{
    StructBss180 *var_r21;
    StructBss4A4 *var_r22;
    StructBss3E4 *temp_r25;
    s32 i;

    fn_1_3088();
    fn_1_39B4(lbl_1_bss_220.unk00);
    fn_1_4304(lbl_1_bss_1BC.unk00);
    fn_1_49FC(lbl_1_bss_1A8.unk00);
    var_r21 = &lbl_1_bss_180[1];
    Hu3DModelHookReset(var_r21->unk00->model[0]);
    fn_1_11818(var_r21->unk00, 0, 0, 1, 1);
    var_r22 = &lbl_1_bss_4A4;
    var_r22->unk00 = var_r22->unk04 = var_r22->unk08 = var_r22->unk0C = 0;
    {
        StructBss1BC *var_r20 = &lbl_1_bss_1BC;
        Vec sp18[] = { { -600.0f, 0.0f, 300.0f }, { -600.0f, 0.0f, 150.0f }, { -450.0f, 0.0f, 150.0f }, { -300.0f, 0.0f, 150.0f } };

        sp18[0].z = var_r20->unk04[0].z - 100.0f;
        for (i = 0; i < 4; i++) {
            temp_r25 = &lbl_1_bss_3E4[i];
            if (i == 0) {
                sp18[i].z = var_r20->unk04[0].z - 100.0f;
            }
            omSetTra(temp_r25->unk00, sp18[i].x, sp18[i].y, sp18[i].z);
            omSetRot(temp_r25->unk00, 0.0f, 0.0f, 0.0f);
            omSetSca(temp_r25->unk00, 1.0f, 1.0f, 1.0f);
            temp_r25->unk1C = temp_r25->unk20 = temp_r25->unk24 = temp_r25->unk28 = 0;
        }
    }
    fn_1_BFC8();
    fn_1_F538();
    fn_1_F75C();
    fn_1_71AC(4);
    lbl_1_bss_3AC.unk28 = HuAudFXPlay(0x6D7);
}

void fn_1_1026C(omObjData *arg0)
{
    switch (lbl_1_bss_18) {
        case 0:
            fn_1_F984();
            lbl_1_bss_18 = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                lbl_1_bss_18 = 2;
            }
            break;
        case 2:
            if (fn_1_BFF8()) {
                lbl_1_bss_18 = 3;
            }
            break;
        case 3:
            lbl_1_bss_1C = MGSeqStartCreate();
            lbl_1_bss_18 = 4;
            lbl_1_bss_3A4[1] = -1;
            break;
        case 4:
            if ((MGSeqStatGet(lbl_1_bss_1C) & 0x10) && lbl_1_bss_3A4[1] == -1) {
                lbl_1_bss_3A4[1] = HuAudSeqPlay(0x4D);
            }
            if (MGSeqStatGet(lbl_1_bss_1C) == 0) {
                lbl_1_bss_18 = 5;
            }
            break;
        case 5:
            if (fn_1_F568()) {
                lbl_1_bss_18 = 6;
            }
            break;
        case 6:
            lbl_1_bss_1C = MGSeqFinishCreate();
            lbl_1_bss_18 = 7;
            HuAudSeqPauseAll(0);
            HuAudSeqAllFadeOut(250);
            break;
        case 7:
            if (MGSeqStatGet(lbl_1_bss_1C) == 0) {
                lbl_1_bss_18 = 8;
            }
            break;
        case 8:
            lbl_1_bss_220.unk00->work[0] = 999;
            if (fn_1_F78C()) {
                lbl_1_bss_18 = 9;
            }
            break;
        case 9:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
            arg0->func = fn_1_F824;
            HuAudFXFadeOut(lbl_1_bss_3AC.unk28, 500);
            break;
    }
    fn_1_F924(arg0);
}

void fn_1_10670(omObjData *arg0)
{
    StructBss220 *var_r28;
    StructBss1BC *var_r27;
    StructBss1A8 *var_r26;
    StructBss180 *temp_r30;
    StructBss3E4 *temp_r29;
    StructBssD8 *var_r25;
    s32 i;

    var_r28 = &lbl_1_bss_220;
    var_r28->unk00 = omAddObjEx(lbl_1_bss_0, 0x100, 16, 16, -1, fn_1_3BF0);
    var_r27 = &lbl_1_bss_1BC;
    var_r27->unk00 = omAddObjEx(lbl_1_bss_0, 0x200, 20, 20, -1, fn_1_4594);
    var_r26 = &lbl_1_bss_1A8;
    var_r26->unk00 = omAddObjEx(lbl_1_bss_0, 0x300, 16, 16, -1, fn_1_4B1C);
    for (i = 0; i < 2; i++) {
        temp_r30 = &lbl_1_bss_180[i];
        temp_r30->unk00 = omAddObjEx(lbl_1_bss_0, 0x400, 16, 16, -1, fn_1_4FB0);
        temp_r30->unk00->work[0] = i;
    }
    for (i = 0; i < 4; i++) {
        temp_r29 = &lbl_1_bss_3E4[i];
        temp_r29->unk00 = omAddObjEx(lbl_1_bss_0, 0x500, 16, 16, -1, fn_1_6060);
        temp_r29->unk00->work[0] = i;
    }
    var_r25 = &lbl_1_bss_D8;
    var_r25->unk00 = omAddObjEx(lbl_1_bss_0, 0x600, 16, 16, -1, fn_1_6944);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    arg0->func = fn_1_1026C;
}

#ifdef __MWERKS__
#include "src/REL/executor.c"
#endif

void fn_1_108DC(void)
{
    lbl_1_bss_0 = omInitObjMan(62, 0x2000);
    omGameSysInit(lbl_1_bss_0);
    fn_1_1A8();
    fn_1_F6C();
    fn_1_1084();
    fn_1_178C();
    fn_1_2A2C();
    fn_1_54A0();
    omAddObjEx(lbl_1_bss_0, 0x1000, 0, 0, -1, fn_1_10670);
}

void ObjectSetup(void)
{
    fn_1_108DC();
}
