#include "REL/m435Dll.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include <string.h>

#include "ext_math.h"

s32 rand8(void);
#ifndef __MWERKS__
#include "game/audio.h"
#endif

typedef struct {
    /* 0x00 */ omObjData* unk00;
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
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ float unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ float unk50;
    /* 0x54 */ float unk54;
    /* 0x58 */ StructFn19894 unk58;
} StructBssE88; // Size 0x4D8

typedef struct {
    /* 0x00 */ omObjData* unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} StructBssDE4; // Size 0x24

typedef struct {
    /* 0x000 */ omObjData* unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14[3];
    /* 0x020 */ s32 unk20;
    /* 0x024 */ s32 unk24;
    /* 0x028 */ s32 unk28;
    /* 0x02C */ s32 unk2C[3];
    /* 0x038 */ s32 unk38[3];
    /* 0x044 */ s32 unk44[3];
    /* 0x050 */ s32 unk50[3];
    /* 0x05C */ s32 unk5C[3];
    /* 0x068 */ s32 unk68[3];
    /* 0x074 */ float unk74;
    /* 0x078 */ float unk78;
    /* 0x07C */ float unk7C[3];
    /* 0x088 */ float unk88[3];
    /* 0x094 */ float unk94[3];
    /* 0x0A0 */ float unkA0[3];
    /* 0x0AC */ Vec unkAC[3];
    /* 0x0D0 */ Vec unkD0[3];
    /* 0x0F4 */ Vec unkF4[3];
    /* 0x118 */ Vec unk118[3];
    /* 0x13C */ Vec unk13C[3];
    /* 0x160 */ Vec unk160[3];
    /* 0x184 */ Vec unk184[3];
    /* 0x1A8 */ float unk1A8[3];
} StructBssC30; // Size 0x1B4

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ char unk08[0xC];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ char unk18[0x20];
} StructBss4F10; // Size 0x38

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
} StructBss4EE8; // Size 0x20

typedef struct {
    /* 0x00 */ omObjData* unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
} StructBssC1C; // Size 0x14

typedef struct {
    /* 0x000 */ omObjData* unk00;
    /* 0x004 */ Vec unk04;
    /* 0x010 */ Vec unk10;
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ s32 unk20;
    /* 0x024 */ s32 unk24;
    /* 0x028 */ s32 unk28;
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ s32 unk30;
    /* 0x034 */ s32 unk34;
    /* 0x038 */ s32 unk38;
    /* 0x03C */ StructFn19894 unk3C;
} StructBss2A4; // Size 0x4BC

typedef struct {
    /* 0x00 */ omObjData* unk00;
    /* 0x04 */ s32 unk04[6];
    /* 0x1C */ char unk1C[0x10];
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
} StructBss144; // Size 0x58

typedef struct {
    /* 0x00 */ omObjData* unk00;
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
} StructBss9C; // Size 0xA8

void fn_1_3AF4(s32 arg0);
void fn_1_4104(s32 arg0);
void fn_1_7D50(s32 arg0);
void fn_1_8544(s32 arg0);
s32 fn_1_8E48(s32 arg0);
s32 fn_1_8F34(s32 arg0);

StructBss4F10 lbl_1_bss_4F10;
s32 lbl_1_bss_4F08[2];
StructBss4EE8 lbl_1_bss_4EE8;
char lbl_1_bss_21E8_pad[0x2D00]; // unused
StructBssE88 lbl_1_bss_E88[4];
StructBssE08 lbl_1_bss_E08;
StructBssDE4 lbl_1_bss_DE4;
StructBssC30 lbl_1_bss_C30;
StructBssC1C lbl_1_bss_C1C;
StructBss2A4 lbl_1_bss_2A4[2];
StructBss144 lbl_1_bss_144[4];
StructBss9C lbl_1_bss_9C;
StructBss84 lbl_1_bss_84;
StructBss84 lbl_1_bss_6C;
Vec lbl_1_bss_3C[4];
StructBss84 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18; // unused
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
Process* lbl_1_bss_0;

s32 lbl_1_data_0[][3] = {
    { DATA_MAKE_NUM(DATADIR_M435, 27), DATA_MAKE_NUM(DATADIR_M435, 26), DATA_MAKE_NUM(DATADIR_MGCONST, 0) },
    { DATA_MAKE_NUM(DATADIR_M435, 28), DATA_MAKE_NUM(DATADIR_M435, 26), DATA_MAKE_NUM(DATADIR_MGCONST, 1) },
    { DATA_MAKE_NUM(DATADIR_M435, 30), DATA_MAKE_NUM(DATADIR_M435, 26), DATA_MAKE_NUM(DATADIR_MGCONST, 2) },
    { DATA_MAKE_NUM(DATADIR_M435, 29), DATA_MAKE_NUM(DATADIR_M435, 26), DATA_MAKE_NUM(DATADIR_MGCONST, 3) },
    { DATA_MAKE_NUM(DATADIR_M435, 32), DATA_MAKE_NUM(DATADIR_M435, 26), DATA_MAKE_NUM(DATADIR_MGCONST, 4) },
    { DATA_MAKE_NUM(DATADIR_M435, 31), DATA_MAKE_NUM(DATADIR_M435, 26), DATA_MAKE_NUM(DATADIR_MGCONST, 5) },
    { DATA_MAKE_NUM(DATADIR_M435, 33), DATA_MAKE_NUM(DATADIR_M435, 26), DATA_MAKE_NUM(DATADIR_MGCONST, 6) },
    { DATA_MAKE_NUM(DATADIR_M435, 34), DATA_MAKE_NUM(DATADIR_M435, 26), DATA_MAKE_NUM(DATADIR_MGCONST, 7) }
};

char* lbl_1_data_E0[] = {
    "c000m1-ske_head",
    "c001m1-ske_head",
    "c002m1-ske_head",
    "c003m1-ske_head",
    "c004m1-ske_head",
    "c005m1-ske_head",
    "c006m1-ske_head",
    "c007m1-ske_head"
};

s32 lbl_1_data_100[][2] = {
    { 0x00000100, 0x00000001 },
    { 0x00000100, 0x00000001 },
    { 0x00000080, 0x00000000 },
    { 0x00000080, 0x00000000 },
    { 0x00000080, 0x00000000 },
    { 0x00000100, 0x00000001 },
    { 0x00000080, 0x00000000 },
    { 0x00000080, 0x00000000 }
};

s32 lbl_1_data_140[][5] = {
    {  91, 105, 126, 141, -1 },
    {  91, 105, 126, 141, -1 },
    { 124, 137,  -1,  -1, -1 },
    {  85, 100, 127,  -1, -1 },
    { 124, 139,  -1,  -1, -1 },
    {  85,  97, 127, 139, -1 },
    { 127, 137,  -1,  -1, -1 },
    {  79,  95, 109, 127, -1 }
};

s32 lbl_1_data_1E0 = -1;
s32 lbl_1_data_1E4 = -1;
s32 lbl_1_data_1E8 = -1;

void fn_1_0(void) {
    s32 i;

    while (TRUE) {
        HuPrcVSleep();
        if (lbl_1_data_1E0 == -1 || lbl_1_data_1E4 == -1 || lbl_1_data_1E8 == -1 || lbl_1_data_1E4 != Hu3DMotionIDGet(lbl_1_data_1E0)) {
            continue;
        }
        for (i = 0; i < 5; i++) {
            if (lbl_1_data_140[lbl_1_data_1E8][i] != -1 && Hu3DMotionTimeGet(lbl_1_data_1E0) >= lbl_1_data_140[lbl_1_data_1E8][i]) {
                OSReport("KE-System  CHR:%d TIME:%d\n", lbl_1_data_1E8, lbl_1_data_140[lbl_1_data_1E8][i]);
                HuAudFXPlay(0x6D8);
                lbl_1_data_140[lbl_1_data_1E8][i] = -1;
            }
        }
    }
}

void fn_1_1A8(void) {
    s32 var_r31;

    var_r31 = Hu3DGLightCreate(0.0f, 1000.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0xFF, 0xFF, 0xFF);
    Hu3DGLightInfinitytSet(var_r31);
}

void fn_1_230(s32 arg0, s32 arg1, float arg2) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk48[arg0] = arg1;
    if (var_r31->unk64[arg0] < 0.0f) {
        var_r31->unk64[arg0] = -arg2;
    }
    else {
        var_r31->unk64[arg0] = arg2;
    }
}

void fn_1_298(s32 arg0, float arg1) {
    fn_1_230(arg0, -1, arg1);
}

float fn_1_304(s32 arg0) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    if (var_r31->unk64[arg0] != 0.0f) {
        var_r31->unk64[arg0] *= -0.9f;
        if (var_r31->unk48[arg0] == -1) {
            if (var_r31->unk64[arg0] >= -0.5f && var_r31->unk64[arg0] <= 0.5f) {
                var_r31->unk64[arg0] = 0.0f;
            }
        }
        else {
            var_r31->unk48[arg0]--;
            if (var_r31->unk48[arg0] <= 0) {
                var_r31->unk48[arg0] = 0;
                var_r31->unk64[arg0] = 0.0f;
            }
        }
    }
    return var_r31->unk64[arg0];
}

void fn_1_434(void) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    if (HuPadBtn[0] & 0x200) {
        if (HuPadBtn[0] & 0x100) {
            var_r31->unk14 -= HuPadStkY[0] / 10.0f;
        }
        else {
            var_r31->unk0C += HuPadStkX[0] / 10.0f;
            var_r31->unk10 += HuPadStkY[0] / 10.0f;
        }
    }
    if (HuPadBtn[0] & 0x800) {
        var_r31->unk24 -= HuPadStkY[0] / 100.0f;
        var_r31->unk28 += HuPadStkX[0] / 100.0f;
        if (var_r31->unk24 < 0.0f) {
            var_r31->unk24 += 360.0f;
        }
        if (var_r31->unk24 >= 360.0f) {
            var_r31->unk24 -= 360.0f;
        }
        if (var_r31->unk28 < 0.0f) {
            var_r31->unk28 += 360.0f;
        }
        if (var_r31->unk28 >= 360.0f) {
            var_r31->unk28 -= 360.0f;
        }
    }
    if (HuPadBtn[0] & 0x400) {
        var_r31->unk3C -= HuPadStkY[0] / 10.0f;
    }
    print8(16, 100, 1.0f, ">>>>>>>>>> CAMERA TEST <<<<<<<<<<");
    print8(16, 110, 1.0f, "CENTER : %.2f, %.2f, %.2f", var_r31->unk0C, var_r31->unk10, var_r31->unk14);
    print8(16, 120, 1.0f, "ROT    : %.2f, %.2f, %.2f", var_r31->unk24, var_r31->unk28, var_r31->unk2C);
    print8(16, 130, 1.0f, "ZOOM   : %.2f", var_r31->unk3C);
}

void fn_1_818(void) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk0C = 0.0f;
    var_r31->unk10 = 225.0f;
    var_r31->unk14 = 1740.0f;
    var_r31->unk24 = -10.0f;
    var_r31->unk28 = 0.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk3C = 300.0f;
}

void fn_1_8A4(void (*arg0)(void)) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk04 = arg0;
}

void fn_1_8C4(void (*arg0)(void)) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk08 = arg0;
}

void fn_1_8E4(omObjData* arg0) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    if (var_r31->unk04 != NULL) {
        var_r31->unk04();
    }
}

void fn_1_92C(omObjData* arg0) {
    StructBssE08* var_r23;

    var_r23 = &lbl_1_bss_E08;
    fn_1_8E4(arg0);
    Center.x = var_r23->unk0C + fn_1_304(0);
    Center.y = var_r23->unk10 + fn_1_304(1);
    Center.z = var_r23->unk14 + fn_1_304(2);
    CRot.x = var_r23->unk24 + fn_1_304(3);
    CRot.y = var_r23->unk28 + fn_1_304(4);
    CRot.z = var_r23->unk2C + fn_1_304(5);
    CZoom = var_r23->unk3C + fn_1_304(6);
}

void fn_1_FDC(void) {
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 45.0f, 0.1f, 10000.0f, 1.2f);
    fn_1_8A4(fn_1_818);
    fn_1_8C4(fn_1_434);
    omAddObjEx(lbl_1_bss_0, 0x7FDA, 0, 0, -1, omOutView);
    omAddObjEx(lbl_1_bss_0, 0x7FD9, 0, 0, -1, fn_1_92C);
}

void fn_1_1110(void) {
    Vec sp20 = { 0.0f, 2500.0f, 1.0f };
    Vec sp14 = { 0.0f, 0.0f, 0.0f };
    Vec sp8 = { 0.0f, 1.0f, 0.0f };

    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);
}

void fn_1_11D4(s32 arg0, float arg1, float arg2, s32 arg3) {
    WindowData* temp_r29;
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
                var_f23 = fn_1_152D4(var_f31, temp_f29, i, 10.0f);
                var_f21 = fn_1_152D4(temp_f27, 1.0f, i, 10.0f);
            }
            else {
                var_f22 = fn_1_152D4(var_f30, temp_f28, i - 10, 5.0f);
                var_f20 = fn_1_152D4(temp_f26, 1.0f, i - 10, 5.0f);
            }
        }
        else {
            if (i <= 10) {
                var_f22 = fn_1_152D4(temp_f28, var_f30, i, 10.0f);
                var_f20 = fn_1_152D4(1.0f, temp_f26, i, 10.0f);
            }
            else {
                var_f23 = fn_1_152D4(temp_f29, var_f31, i - 10, 5.0f);
                var_f21 = fn_1_152D4(1.0f, temp_f27, i - 10, 5.0f);
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

void fn_1_1818(void) {
    HuWinInit(1);
}

void fn_1_183C(s32 arg0, float arg1, float arg2) {
    WindowData* temp_r31;
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
            var_f31 -= 2.0f;
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
            var_f30 -= 2.0f;
        }
    }
    HuWinPosSet(arg0, var_f31, var_f30);
    HuWinScaleSet(arg0, temp_f25, temp_f24);
    HuPrcVSleep();
    for (i = 0; i < 10; i++) {
        temp_f23 = fn_1_152D4(var_f31, temp_f29, i, 10.0f);
        temp_f21 = fn_1_152D4(temp_f25, 1.0f, i, 10.0f);
        temp_f22 = fn_1_152D4(var_f30, temp_f28, i, 10.0f);
        temp_f20 = fn_1_152D4(temp_f24, 1.0f, i, 10.0f);
        HuWinPosSet(arg0, temp_f23, temp_f22);
        HuWinScaleSet(arg0, temp_f21, temp_f20);
        HuPrcVSleep();
    }
    HuWinPosSet(arg0, temp_f29, temp_f28);
    HuWinScaleSet(arg0, 1.0f, 1.0f);
    HuPrcVSleep();
}

s32 fn_1_1C94(float arg0, float arg1, float arg2, float arg3, s32 arg4) {
    s32 var_r31;
    s32 sp18[][6] = {
        { 0xFF, 0xFF, 0xCC, 0x00, 0x09, 0x09 },
        { 0xCC, 0xFF, 0xFF, 0x00, 0x09, 0x09 },
        { 0xFF, 0xCC, 0xFF, 0x00, 0x09, 0x09 }
    };

    var_r31 = HuWinCreate(arg0, arg1, arg2, arg3, 1);
    HuSprColorSet(winData[var_r31].group, 0, sp18[arg4][0], sp18[arg4][1], sp18[arg4][2]);
    winData[var_r31].mess_color = sp18[arg4][3];
    winData[var_r31].mess_shadow_color = sp18[arg4][4];
    winData[var_r31].attr |= 0x80;
    HuWinBGTPLvlSet(var_r31, sp18[arg4][5] / 10.0f);
    winData[var_r31].active_pad = 0;
    fn_1_11D4(var_r31, 0.5f, 0.5f, 1);
    return var_r31;
}

s32 fn_1_1E80(float arg0, float arg1, float arg2, float arg3, s32 arg4) {
    return fn_1_1C94(arg0, arg1, arg2, arg3, arg4);
}

void fn_1_206C(s32 arg0, float arg1, float arg2) {
    WindowData* temp_r31;
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
        temp_f23 = fn_1_1539C(temp_f29, var_f31, i, 10.0f);
        temp_f21 = fn_1_1539C(1.0f, temp_f25, i, 10.0f);
        temp_f22 = fn_1_1539C(temp_f28, var_f30, i, 10.0f);
        temp_f20 = fn_1_1539C(1.0f, temp_f24, i, 10.0f);
        HuWinPosSet(arg0, temp_f23, temp_f22);
        HuWinScaleSet(arg0, temp_f21, temp_f20);
        HuPrcVSleep();
    }
    HuWinPosSet(arg0, var_f31, var_f30);
    HuWinScaleSet(arg0, temp_f25, temp_f24);
    HuPrcVSleep();
}

void fn_1_24C4(s32 arg0) {
    HuWinMesSet(arg0, MAKE_MESSID(29, 22));
    HuPrcVSleep();
    fn_1_11D4(arg0, 0.5f, 0.5f, 0);
    HuWinKill(arg0);
}

void fn_1_252C(s32 arg0) {
    fn_1_24C4(arg0);
}

void fn_1_2594(s32 arg0, s32 arg1) {
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
        if (lbl_1_bss_E88[i].unk2C == 0) {
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

void fn_1_267C(s32 arg0) {
    s32 var_r31;
    s32 temp_r28;
    s32 i;

    var_r31 = 0;
    temp_r28 = GWMessDelayGet();
    HuWinComKeyReset();
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_E88[i].unk2C == 0) {
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

void fn_1_2798(s32 arg0, s32 arg1) {
    winData[arg0].mess_color = 0;
    winData[arg0].mess_shadow_color = 9;
    winData[arg0].attr |= 0x80;
    HuWinMesSet(arg0, arg1);
}

void fn_1_281C(float* arg0, s32 arg1) {
    float spC[2];

    HuWinMesMaxSizeGet(1, spC, arg1);
    if (spC[0] > arg0[0]) {
        arg0[0] = spC[0];
    }
    if (spC[1] > arg0[1]) {
        arg0[1] = spC[1];
    }
}

void fn_1_288C(s32 arg0) {
    if (lbl_1_bss_10 == 0) {
        lbl_1_bss_10 = 1;
        lbl_1_bss_C = arg0 * 60;
    }
}

s32 fn_1_28C4(void) {
    if (lbl_1_bss_10 == 3) {
        return 1;
    } else {
        return 0;
    }
}

s32 fn_1_28E8(void) {
    if (lbl_1_bss_10 == 2) {
        lbl_1_bss_10 = 3;
        lbl_1_bss_C = 30;
    }
}

s32 lbl_1_data_26C = -1;

void fn_1_2920(omObjData* arg0) {
    switch (lbl_1_bss_10) {
        case 1:
            if (lbl_1_data_26C == -1) {
                lbl_1_data_26C = MGSeqCreate(1, lbl_1_bss_C / 60, -1, -1);
            }
            lbl_1_bss_10 = 2;
            break;
        case 2:
            lbl_1_bss_C--;
            if (lbl_1_data_26C != -1) {
                MGSeqParamSet(lbl_1_data_26C, 1, (lbl_1_bss_C + 59) / 60);
            }
            if (lbl_1_bss_C <= 0) {
                lbl_1_bss_C = 30;
                lbl_1_bss_10 = 3;
            }
            break;
        case 3:
            if (lbl_1_data_26C != -1) {
                MGSeqParamSet(lbl_1_data_26C, 2, -1);
                lbl_1_data_26C = -1;
            }
            lbl_1_bss_C = 0;
            lbl_1_bss_10 = 0;
            break;
    }
}

void fn_1_2AF0(void) {
    lbl_1_bss_C = 0;
    lbl_1_bss_10 = 0;
    omAddObjEx(lbl_1_bss_0, 0x2000, 0, 0, -1, fn_1_2920);
}

void fn_1_2B54(omObjData* arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        Hu3DData[arg0->model[i + 5]].rot.y += 360.0f / (2500.0f + 2500.0f * i);
    }
}

void fn_1_2BFC(s32 arg0) {
    StructBssDE4* var_r31;

    var_r31 = &lbl_1_bss_DE4;
    var_r31->unk04 = arg0;
}

void fn_1_2C1C(omObjData* arg0) {
    StructBssDE4* var_r30;

    var_r30 = &lbl_1_bss_DE4;
    switch (var_r30->unk04) {
        case 2:
            fn_1_157BC(arg0, 9, 9, 1, 0);
            Hu3DModelAttrReset(arg0->model[9], 1);
            var_r30->unk1C = 0;
            fn_1_230(1, 10, 4.0f);
            HuAudFXPlay(0x6CF);
            /* fallthrough */
        case 1:
            fn_1_157BC(arg0, 0, 0, 1, 0);
            fn_1_157BC(arg0, 3, 3, 1, 0);
            fn_1_157BC(arg0, 4, 4, 1, 0);
            fn_1_157BC(arg0, 5, 5, 1, 0);
            fn_1_157BC(arg0, 6, 6, 1, 0);
            fn_1_157BC(arg0, 7, 7, 1, 0);
            if (var_r30->unk04 == 1) {
                HuAudFXPlay(0x6CE);
            }
            var_r30->unk04 = 20;
            break;
        case 3:
            var_r30->unk04 = 10;
            fn_1_157BC(arg0, 0, 0, 1, 0);
            fn_1_157BC(arg0, 1, 1, 1, 0);
            fn_1_157BC(arg0, 2, 2, 1, 0);
            fn_1_157BC(arg0, 3, 3, 1, 0);
            fn_1_157BC(arg0, 4, 4, 1, 0);
            fn_1_157BC(arg0, 5, 5, 1, 0);
            fn_1_157BC(arg0, 6, 6, 1, 0);
            fn_1_157BC(arg0, 7, 7, 1, 0);
            fn_1_157BC(arg0, 8, 8, 0, 0);
            HuAudFXPlay(0x6D0);
            Hu3DModelAttrReset(arg0->model[8], 1);
            break;
        case 10:
            fn_1_230(6, -1, 8.0f);
            if (Hu3DMotionTimeGet(arg0->model[3]) >= 30.0f) {
                var_r30->unk04 = 20;
                fn_1_3AF4(1);
                fn_1_230(6, -1, 128.0f);
                HuAudFXPlay(0x6DA);
                omVibrate(fn_1_8E48(0), 12, 12, 0);
                omVibrate(fn_1_8E48(1), 12, 12, 0);
                omVibrate(fn_1_8E48(2), 12, 12, 0);
                omVibrate(fn_1_8E48(3), 12, 12, 0);
            }
            break;
        case 20:
            if (Hu3DMotionEndCheck(arg0->model[3])) {
                var_r30->unk04 = 0;
                fn_1_157BC(arg0, 3, 10, 1, 1);
                fn_1_157BC(arg0, 4, 11, 1, 1);
                Hu3DModelAttrSet(arg0->model[8], 1);
                Hu3DModelAttrSet(arg0->model[9], 1);
            }
            break;
    }
    if (Hu3DMotionTimeGet(arg0->model[9]) >= 25.0f && var_r30->unk1C == 0) {
        var_r30->unk1C = 1;
        fn_1_230(1, 10, 4.0f);
    } else if (Hu3DMotionTimeGet(arg0->model[9]) >= 40.0f && var_r30->unk1C == 1) {
        var_r30->unk1C = 2;
        fn_1_230(1, 10, 4.0f);
    }
    if (var_r30->unk04 == 0) {
        if (var_r30->unk14++ >= 300) {
            var_r30->unk14 = 0;
            if (rand8() % 2 != 0) {
                fn_1_2BFC(1);
            }
        }
    }
}

void fn_1_31BC(omObjData* arg0) {
    fn_1_2B54(arg0);
    fn_1_2C1C(arg0);
}

void fn_1_3288(StructBssDE4* arg0) {
    omObjData* temp_r31;

    temp_r31 = arg0->unk00;
    fn_1_157BC(temp_r31, 0, 0, 1, 2);
    Hu3DModelPosSet(temp_r31->model[1], 0.0f, 0.0f, -680.0f);
    fn_1_157BC(temp_r31, 1, 1, 1, 2);
    Hu3DModelPosSet(temp_r31->model[2], 0.0f, 0.0f, -680.0f);
    fn_1_157BC(temp_r31, 2, 2, 1, 2);
    Hu3DModelPosSet(temp_r31->model[3], 525.0f, 0.0f, -1150.0f);
    fn_1_157BC(temp_r31, 3, 10, 1, 1);
    Hu3DModelPosSet(temp_r31->model[4], -525.0f, 0.0f, -1150.0f);
    fn_1_157BC(temp_r31, 4, 11, 1, 1);
    Hu3DModelPosSet(temp_r31->model[5], 50.0f, 150.0f, 50.0f);
    fn_1_157BC(temp_r31, 5, 5, 1, 2);
    Hu3DModelPosSet(temp_r31->model[6], 0.0f, 150.0f, 0.0f);
    fn_1_157BC(temp_r31, 6, 6, 1, 2);
    Hu3DModelPosSet(temp_r31->model[7], 0.0f, 150.0f, 0.0f);
    fn_1_157BC(temp_r31, 7, 7, 1, 2);
    Hu3DModelAttrSet(temp_r31->model[8], 1);
    fn_1_157BC(temp_r31, 8, 8, 1, 2);
    Hu3DModelAttrSet(temp_r31->model[9], 1);
    fn_1_157BC(temp_r31, 9, 9, 1, 2);
    temp_r31->work[0] = temp_r31->work[1] = temp_r31->work[2] = temp_r31->work[3] = 0;
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
    arg0->unk14 = arg0->unk18 = arg0->unk1C = arg0->unk20 = 0;
}

void fn_1_3558(omObjData* arg0) {
    StructBssDE4* var_r30;

    var_r30 = &lbl_1_bss_DE4;
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 39));
    arg0->motion[0] = Hu3DMotionIDGet(arg0->model[0]);
    Hu3DModelShadowMapSet(arg0->model[0]);
    fn_1_157BC(arg0, 0, 0, 1, 2);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 40));
    arg0->motion[1] = Hu3DMotionIDGet(arg0->model[1]);
    Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, -680.0f);
    Hu3DModelShadowMapSet(arg0->model[1]);
    fn_1_157BC(arg0, 1, 1, 1, 2);
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 41));
    arg0->motion[2] = Hu3DMotionIDGet(arg0->model[2]);
    Hu3DModelPosSet(arg0->model[2], 0.0f, 0.0f, -680.0f);
    Hu3DModelShadowSet(arg0->model[2]);
    fn_1_157BC(arg0, 2, 2, 1, 2);
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 42));
    arg0->motion[3] = Hu3DMotionIDGet(arg0->model[3]);
    arg0->motion[10] = Hu3DJointMotionFile(arg0->model[3], DATA_MAKE_NUM(DATADIR_M435, 44));
    Hu3DModelPosSet(arg0->model[3], 525.0f, 0.0f, -1150.0f);
    Hu3DModelShadowSet(arg0->model[3]);
    fn_1_157BC(arg0, 3, 10, 1, 1);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 43));
    arg0->motion[4] = Hu3DMotionIDGet(arg0->model[4]);
    arg0->motion[11] = Hu3DJointMotionFile(arg0->model[4], DATA_MAKE_NUM(DATADIR_M435, 45));
    Hu3DModelPosSet(arg0->model[4], -525.0f, 0.0f, -1150.0f);
    Hu3DModelShadowSet(arg0->model[4]);
    fn_1_157BC(arg0, 4, 11, 1, 1);
    arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 36));
    arg0->motion[5] = Hu3DMotionIDGet(arg0->model[5]);
    Hu3DModelPosSet(arg0->model[5], 50.0f, 150.0f, 50.0f);
    fn_1_157BC(arg0, 5, 5, 1, 2);
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 37));
    arg0->motion[6] = Hu3DMotionIDGet(arg0->model[6]);
    Hu3DModelPosSet(arg0->model[6], 0.0f, 150.0f, 0.0f);
    fn_1_157BC(arg0, 6, 6, 1, 2);
    arg0->model[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 38));
    arg0->motion[7] = Hu3DMotionIDGet(arg0->model[7]);
    Hu3DModelPosSet(arg0->model[7], 0.0f, 150.0f, 0.0f);
    fn_1_157BC(arg0, 7, 7, 1, 2);
    arg0->model[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 46));
    arg0->motion[8] = Hu3DMotionIDGet(arg0->model[8]);
    Hu3DModelAttrSet(arg0->model[8], 1);
    Hu3DModelLayerSet(arg0->model[8], 1);
    fn_1_157BC(arg0, 8, 8, 1, 2);
    arg0->model[9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 47));
    arg0->motion[9] = Hu3DMotionIDGet(arg0->model[9]);
    Hu3DModelAttrSet(arg0->model[9], 1);
    Hu3DModelLayerSet(arg0->model[9], 1);
    fn_1_157BC(arg0, 9, 9, 1, 2);
    arg0->work[0] = arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
    var_r30->unk04 = var_r30->unk08 = var_r30->unk0C = var_r30->unk10 = 0;
    var_r30->unk14 = var_r30->unk18 = var_r30->unk1C = var_r30->unk20 = 0;
    arg0->func = fn_1_31BC;
}

void fn_1_3AF4(s32 arg0) {
    StructBssC30* var_r31;

    var_r31 = &lbl_1_bss_C30;
    var_r31->unk04 = arg0;
}

float lbl_1_data_2C4 = 270.0f;

void fn_1_3B14(omObjData* arg0) {
    Vec sp14;
    Vec sp8;
    ModelData* temp_r30;
    StructBssC30* var_r29;
    s32 var_r28;

    temp_r30 = &Hu3DData[arg0->model[1]];
    var_r29 = &lbl_1_bss_C30;
    if (var_r29->unk04 == 1) {
        var_r29->unk04 = 0;
        fn_1_157BC(arg0, 0, 0, 1, 0);
        fn_1_157BC(arg0, 1, 2, 1, 0);
        Hu3DModelAttrReset(arg0->model[0], 1);
        Hu3DModelAttrReset(arg0->model[1], 1);
    } else if (var_r29->unk04 >= 2) {
        temp_r30->pos.x = 750.0 * cosd(lbl_1_data_2C4);
        temp_r30->pos.z = 500.0 + 750.0 * sind(lbl_1_data_2C4);
        temp_r30->rot.y += 0.2f;
        if (var_r29->unk04 == 2) {
            var_r29->unk04 = 3;
            lbl_1_bss_4F10.unk00 = HuAudFXPlay(0x6DB);
            fn_1_157BC(arg0, 1, 1, 1, 1);
        }
        lbl_1_data_2C4 -= 0.2f;
        if (lbl_1_data_2C4 < 180.0f) {
            var_r29->unk04 = 0;
            HuAudFXStop(lbl_1_bss_4F10.unk00);
            lbl_1_bss_4F10.unk00 = -1;
            lbl_1_data_2C4 = 270.0f;
            Hu3DModelPosSet(arg0->model[1], -750.0f, 0.0f, 500.0f);
            Hu3DModelRotSet(arg0->model[1], 0.0f, 90.0f, 0.0f);
            fn_1_157BC(arg0, 1, 1, 1, 2);
            fn_1_7D50(6);
        }
    }
    sp14.x = temp_r30->pos.x;
    sp14.y = temp_r30->pos.y;
    sp14.z = temp_r30->pos.z;
    Hu3D3Dto2D(&sp14, 1, &sp8);
    var_r28 = 32.0f + sp8.x * 0.1f;
    if (var_r28 <= 32) {
        var_r28 = 32;
    } else if (var_r28 >= 96) {
        var_r28 = 96;
    }
    if (lbl_1_bss_4F10.unk00 != -1) {
        HuAudFXPanning(lbl_1_bss_4F10.unk00, var_r28);
    }
}

void fn_1_3E84(s32 arg0) {
    StructBssC30* var_r31;

    var_r31 = &lbl_1_bss_C30;
    var_r31->unk08 = arg0;
}

void fn_1_3EA4(omObjData* arg0) {
    StructBssC30* var_r31;
    s32 i;

    var_r31 = &lbl_1_bss_C30;
    switch (var_r31->unk08) {
        case 0:
            var_r31->unk10 = 0;
            var_r31->unk78 = 7.5f;
            var_r31->unk74 = var_r31->unk74;
            break;
        case 1:
            if (lbl_1_bss_4F10.unk14 == 0) {
                lbl_1_bss_4F10.unk14 = 1;
                lbl_1_bss_4F10.unk04 = HuAudFXPlay(0x6DE);
            }
            fn_1_4104(1);
            var_r31->unk74 -= var_r31->unk78;
            if (var_r31->unk74 < 0.0f) {
                var_r31->unk74 += 360.0f;
            }
            break;
        case 2:
            if (lbl_1_bss_4F10.unk14 == 1) {
                lbl_1_bss_4F10.unk14 = 0;
                HuAudFXStop(lbl_1_bss_4F10.unk04);
            }
            for (i = 0; i < 3; i++) {
                if (var_r31->unk2C[i] != 7) {
                    break;
                }
            }
            var_r31->unk74 -= var_r31->unk78;
            if (var_r31->unk74 < 0.0f) {
                var_r31->unk74 += 360.0f;
            }
            if (i == 3) {
                var_r31->unk08 = 3;
            }
            break;
        case 3:
            var_r31->unk74 -= var_r31->unk78;
            if (var_r31->unk74 < 0.0f) {
                var_r31->unk74 += 360.0f;
            }
            var_r31->unk78 -= 0.025f;
            if (var_r31->unk78 < 0.0f) {
                var_r31->unk78 = 0.0f;
            }
            break;
    }
    omSetRot(arg0, 0.0f, 0.0f, var_r31->unk74);
}

void fn_1_4104(s32 arg0) {
    StructBssC30* var_r31;

    var_r31 = &lbl_1_bss_C30;
    if (var_r31->unk10 == 0) {
        var_r31->unk10 = arg0;
    }
}

void fn_1_4130(omObjData* arg0) {
    Vec spC;
    StructBss4EE8* sp8;
    StructBssC30* var_r31;
    ModelData* temp_r28;
    ModelData* temp_r29;
    s32 temp_r26;
    s32 i;

    sp8 = &lbl_1_bss_4EE8;
    var_r31 = &lbl_1_bss_C30;
    temp_r26 = lbl_1_bss_4EE8.unk10 - 1;
    switch (var_r31->unk10) {
        case 1:
            var_r31->unk10 = 2;
            if (temp_r26 < 0) {
                var_r31->unk10 = 0;
                break;
            }
            for (i = 0; i < 3; i++) {
                temp_r28 = &Hu3DData[arg0->model[i + temp_r26 * 3 + 2]];
                var_r31->unk13C[i].x = temp_r28->pos.x;
                var_r31->unk13C[i].y = temp_r28->pos.y;
                var_r31->unk13C[i].z = temp_r28->pos.z;
                var_r31->unk160[i].x = var_r31->unk13C[i].x + rand8() % 50;
                var_r31->unk160[i].y = 7.5f;
                var_r31->unk160[i].z = var_r31->unk13C[i].z + (rand8() % 150 - 75);
                var_r31->unk184[i].x = 0.0f;
                var_r31->unk184[i].y = rand8() % 120;
                if (rand8() % 2 == 0) {
                    var_r31->unk184[i].y *= -1.0f;
                }
                var_r31->unk184[i].z = 5.0f + rand8() % 5;
                var_r31->unk14[i] = rand8() % 10 + 15;
            }
            var_r31->unk20 = 0;
            break;
        case 2:
            for (i = 0; i < 3; i++) {
                temp_r29 = &Hu3DData[arg0->model[i + temp_r26 * 3 + 2]];
                spC.x = fn_1_1539C(var_r31->unk13C[i].x, var_r31->unk160[i].x, var_r31->unk20, var_r31->unk14[i]);
                spC.y = fn_1_1539C(var_r31->unk13C[i].y, var_r31->unk160[i].y, var_r31->unk20, var_r31->unk14[i]);
                spC.z = fn_1_1539C(var_r31->unk13C[i].z, var_r31->unk160[i].z, var_r31->unk20, var_r31->unk14[i]);
                Hu3DModelPosSet(arg0->model[i + temp_r26 * 3 + 2], spC.x, spC.y, spC.z);
                if (var_r31->unk20 <= var_r31->unk14[i]) {
                    temp_r29->rot.y = fn_1_15294(temp_r29->rot.y, var_r31->unk184[i].y, 15.0f);
                    temp_r29->rot.z = fn_1_15294(temp_r29->rot.z, 90.0f, 15.0f);
                } else {
                    temp_r29->rot.z = fn_1_15294(temp_r29->rot.z, 0.0f, 3.0f);
                }
            }
            var_r31->unk20++;
            if (var_r31->unk20 >= 60) {
                var_r31->unk20 = 0;
                var_r31->unk10 = 3;
            }
            break;
    }
}

s32 fn_1_46D8(float arg0, float arg1) {
    s32 sp8[] = { 90, 5, 70, 30, 50, 1, 100, 10 };
    s32 var_r31;

    if (arg0 >= 0.0f && arg0 < 45.0f) {
        var_r31 = sp8[0];
    } else if (arg0 >= 45.0f && arg0 < 90.0f) {
        var_r31 = sp8[1];
    } else if (arg0 >= 90.0f && arg0 < 135.0f) {
        var_r31 = sp8[2];
    } else if (arg0 >= 135.0f && arg0 < 180.0f) {
        var_r31 = sp8[3];
    } else if (arg0 >= 180.0f && arg0 < 225.0f) {
        var_r31 = sp8[4];
    } else if (arg0 >= 225.0f && arg0 < 270.0f) {
        var_r31 = sp8[5];
    } else if (arg0 >= 270.0f && arg0 < 315.0f) {
        var_r31 = sp8[6];
    } else if (arg0 >= 315.0f && arg0 < 360.0f) {
        var_r31 = sp8[7];
    }
    if (arg1 > 75.0f) {
        var_r31 = 0;
    }
    if (arg1 < 25.0f) {
        var_r31 = -999;
    }
    return var_r31;
}

void fn_1_4904(s32 arg0) {
    Vec spC;
    StructBssC30* var_r31;

    var_r31 = &lbl_1_bss_C30;
    spC.x = -675.0f;
    spC.y = var_r31->unkD0[arg0].y - 175.0f;
    spC.z = var_r31->unkD0[arg0].z - 500.0f;
    var_r31->unk7C[arg0] = var_r31->unk1A8[arg0] + sqrtf(spC.y * spC.y + spC.z * spC.z);
    var_r31->unk94[arg0] = var_r31->unk74 - var_r31->unk78 * (var_r31->unk50[arg0] + 2) + atan2d(spC.y, spC.z);
    if (var_r31->unk94[arg0] >= 360.0f) {
        var_r31->unk94[arg0] -= 360.0f;
    } else if (var_r31->unk94[arg0] < 0.0f) {
        var_r31->unk94[arg0] += 360.0f;
    }
    if (var_r31->unk94[arg0] >= 360.0f) {
        var_r31->unk94[arg0] -= 360.0f;
    } else if (var_r31->unk94[arg0] < 0.0f) {
        var_r31->unk94[arg0] += 360.0f;
    }
    if (var_r31->unk94[arg0] >= 360.0f) {
        var_r31->unk94[arg0] -= 360.0f;
    } else if (var_r31->unk94[arg0] < 0.0f) {
        var_r31->unk94[arg0] += 360.0f;
    }
    var_r31->unk5C[arg0] = fn_1_46D8(var_r31->unk94[arg0], var_r31->unk7C[arg0]);
}

void fn_1_4CEC(s32 arg0) {
    StructBssC30* var_r31;

    var_r31 = &lbl_1_bss_C30;
    if ((var_r31->unk7C[arg0] >= 23.0f && var_r31->unk7C[arg0] <= 27.0f)
        || (var_r31->unk7C[arg0] >= 73.0f && var_r31->unk7C[arg0] <= 77.0f))
    {
        var_r31->unk1A8[arg0] = 5.0f;
        if (rand8() % 2 == 0) {
            var_r31->unk1A8[arg0] *= -1.0f;
        }
    }
}

void fn_1_4E08(s32 arg0) {
    StructBssC30* var_r31;
    float temp_f31;

    var_r31 = &lbl_1_bss_C30;
    temp_f31 = var_r31->unk94[arg0];
    if ((temp_f31 >= -2.0f && temp_f31 < 2.0f)
        || (temp_f31 >= 43.0f && temp_f31 < 47.0f)
        || (temp_f31 >= 88.0f && temp_f31 < 92.0f)
        || (temp_f31 >= 133.0f && temp_f31 < 137.0f)
        || (temp_f31 >= 178.0f && temp_f31 < 182.0f)
        || (temp_f31 >= 223.0f && temp_f31 < 227.0f)
        || (temp_f31 >= 268.0f && temp_f31 < 272.0f)
        || (temp_f31 >= 313.0f && temp_f31 < 317.0f))
    {
        var_r31->unk50[arg0]++;
    }
}

s32 fn_1_4FB4(void) {
    StructBssC30* var_r29;
    s32 var_r28;
    s32 i;

    var_r28 = 0;
    var_r29 = &lbl_1_bss_C30;
    for (i = 0; i < 3; i++) {
        var_r28 += var_r29->unk5C[i];
    }
    if (var_r28 < 0) {
        return 1;
    }
    if (var_r29->unk24 == var_r28) {
        for (i = 0; i < 3; i++) {
            var_r29->unk50[i] += 3;
            fn_1_4904(i);
        }
        return 0;
    }
    if (var_r29->unk24 > var_r28) {
        var_r29->unk24 = var_r28;
    }
    return 1;
}

s32 fn_1_5438(void) {
    Vec spC;
    float var_f28;
    StructBssC30* var_r30;
    s32 var_r29;
    s32 i;

    var_r29 = 1;
    var_r30 = &lbl_1_bss_C30;
    for (i = 0; i < 3; i++) {
        spC.x = -675.0f;
        spC.y = var_r30->unkD0[i].y - 175.0f;
        spC.z = var_r30->unkD0[i].z - 500.0f;
        var_f28 = sqrtf(spC.y * spC.y + spC.z * spC.z);
        if (var_f28 <= 30.0f) {
            var_r29 = 0;
        }
    }
    return var_r29;
}

void fn_1_5600(s32 arg0) {
    StructBssC30* var_r30;
    s32 i;

    var_r30 = &lbl_1_bss_C30;
    for (i = 0; i < 3; i++) {
        var_r30->unk2C[i] = arg0;
    }
}

void fn_1_5644(omObjData* arg0) {
    Vec sp2C;
    float temp_f27;
    float temp_f23;
    StructBssC30* var_r31;
    s32 temp_r26;
    s32 i;

    var_r31 = &lbl_1_bss_C30;
    temp_r26 = lbl_1_bss_4EE8.unk14;
    for (i = 0; i < 3; i++) {
        switch (var_r31->unk2C[i]) {
            case 1:
                var_r31->unkAC[i].x = var_r31->unkD0[i].x = -675.0f;
                var_r31->unkAC[i].y = var_r31->unkD0[i].y = 175.0f;
                var_r31->unkAC[i].z = var_r31->unkD0[i].z = 500.0f;
                var_r31->unk38[i] = 0;
                var_r31->unkF4[i].x = 0.0f;
                var_r31->unkF4[i].y = -325.0f;
                var_r31->unkF4[i].z = 500.0f;
                var_r31->unk118[i].x = var_r31->unk118[i].y = var_r31->unk118[i].z = 0.0f;
                var_r31->unk44[i] = 0;
                var_r31->unk50[i] = i + 15;
                var_r31->unk7C[i] = var_r31->unk88[i] = 0.0f;
                var_r31->unk94[i] = var_r31->unkA0[i] = 0.0f;
                var_r31->unk5C[i] = var_r31->unk68[i] = 0;
                var_r31->unk1A8[i] = 0.0f;
                Hu3DModelPosSet(arg0->model[i + temp_r26 * 3 + 2], var_r31->unkF4[i].x, var_r31->unkF4[i].y, var_r31->unkF4[i].z);
                Hu3DModelRotSet(arg0->model[i + temp_r26 * 3 + 2], 0.0f, 0.0f, 0.0f);
                /* fallthrough */
            case 2:
                var_r31->unk2C[i] = 2;
                temp_f27 = fn_1_152D4(1.5f, 0.5f, var_r31->unk38[i], 15.0f);
                temp_f23 = fn_1_152D4(0.0f, 1.0f, var_r31->unk38[i], 10.0f);
                Hu3DModelAttrReset(arg0->model[i + temp_r26 * 3 + 14], 1);
                Hu3DModelScaleSet(arg0->model[i + temp_r26 * 3 + 14], temp_f27, temp_f27, temp_f27);
                Hu3DModelTPLvlSet(arg0->model[i + temp_r26 * 3 + 14], temp_f23);
                Hu3DModelPosSet(arg0->model[i + temp_r26 * 3 + 14], var_r31->unkD0[i].x, var_r31->unkD0[i].y, var_r31->unkD0[i].z);
                if (var_r31->unk38[i]++ >= 20) {
                    var_r31->unk38[i] = 0;
                    var_r31->unk2C[i] = 3;
                }
                break;
            case 3:
                if (var_r31->unk38[i]++ >= 30) {
                    var_r31->unk38[i] = 0;
                    temp_f23 = 100.0f - i * 15;
                    temp_f27 = 2.0f * (rand8() % 180);
                    var_r31->unkAC[i].x = -675.0f;
                    var_r31->unkAC[i].y = 175.0 + temp_f23 * sind(temp_f27);
                    var_r31->unkAC[i].z = 500.0 + temp_f23 * cosd(temp_f27);
                }
                var_r31->unkD0[i].x = var_r31->unkAC[i].x;
                var_r31->unkD0[i].y = fn_1_15294(var_r31->unkD0[i].y, var_r31->unkAC[i].y, 30.0f);
                var_r31->unkD0[i].z = fn_1_15294(var_r31->unkD0[i].z, var_r31->unkAC[i].z, 30.0f);
                Hu3DModelPosSet(arg0->model[i + temp_r26 * 3 + 14], var_r31->unkD0[i].x, var_r31->unkD0[i].y, var_r31->unkD0[i].z);
                break;
            case 4:
                var_r31->unk2C[i] = 100;
                fn_1_4904(i);
                fn_1_4CEC(i);
                fn_1_4E08(i);
                fn_1_4904(i);
                var_r31->unk28 = 0;
                HuAudFXPlay(0x6DC);
                /* fallthrough */
            case 100:
                var_r31->unk2C[i] = 5;
                if (var_r31->unk28 == 1) {
                    var_r31->unk2C[i] = 5;
                }
                if (i == 2) {
                    while (fn_1_4FB4() == 0) {
                    }
                    var_r31->unk28 = 1;
                }
                Hu3DModelAttrReset(arg0->model[i + temp_r26 * 3 + 2], 1);
                break;
            case 5:
                var_r31->unkF4[i].x = fn_1_1526C(0.0f, -675.0f, var_r31->unk44[i], var_r31->unk50[i]);
                var_r31->unkF4[i].y = fn_1_1526C(175.0f, var_r31->unkD0[i].y, var_r31->unk44[i], var_r31->unk50[i]);
                var_r31->unkF4[i].z = fn_1_1526C(500.0f, var_r31->unkD0[i].z, var_r31->unk44[i], var_r31->unk50[i]);
                var_r31->unk118[i].x -= 360.0f / var_r31->unk50[i];
                if (var_r31->unk118[i].x >= 360.0f) {
                    var_r31->unk118[i].x -= 360.0f;
                } else if (var_r31->unk118[i].x < 0.0f) {
                    var_r31->unk118[i].x += 360.0f;
                }
                Hu3DModelPosSet(arg0->model[i + temp_r26 * 3 + 2], var_r31->unkF4[i].x, var_r31->unkF4[i].y, var_r31->unkF4[i].z);
                Hu3DModelRotSet(arg0->model[i + temp_r26 * 3 + 2], var_r31->unk118[i].x, 0.0f, 0.0f);
                if (var_r31->unk44[i]++ >= var_r31->unk50[i]) {
                    var_r31->unk2C[i] = 6;
                    var_r31->unk38[i] = 0;
                }
                break;
            case 6:
                var_r31->unk2C[i] = 7;
                sp2C.x = -675.0f;
                sp2C.y = var_r31->unkF4[i].y - 175.0f;
                sp2C.z = var_r31->unkF4[i].z - 500.0f;
                var_r31->unk88[i] = var_r31->unk1A8[i] + sqrtf(sp2C.y * sp2C.y + sp2C.z * sp2C.z);
                var_r31->unkA0[i] = var_r31->unk74 + atan2d(sp2C.y, sp2C.z);
                if (var_r31->unkA0[i] >= 360.0f) {
                    var_r31->unkA0[i] -= 360.0f;
                } else if (var_r31->unkA0[i] < 0.0f) {
                    var_r31->unkA0[i] += 360.0f;
                }
                var_r31->unk118[i].y = atan2d(sp2C.y, sp2C.z);
                var_r31->unk68[i] = fn_1_46D8(var_r31->unkA0[i], var_r31->unk88[i]);
                if (var_r31->unk68[i] >= 0) {
                    HuAudFXPlay(0x6DD);
                } else {
                    HuAudFXPlay(0x6DF);
                }
                fn_1_8544(7);
                fn_1_3E84(2);
                omVibrate(fn_1_8E48(lbl_1_bss_4EE8.unk14), 12, 6, 6);
                /* fallthrough */
            case 7:
                temp_f27 = fn_1_152D4(0.5f, 1.5f, var_r31->unk38[i], 15.0f);
                temp_f23 = fn_1_152D4(1.0f, 0.0f, var_r31->unk38[i], 10.0f);
                Hu3DModelScaleSet(arg0->model[i + temp_r26 * 3 + 14], temp_f27, temp_f27, temp_f27);
                Hu3DModelTPLvlSet(arg0->model[i + temp_r26 * 3 + 14], temp_f23);
                if (var_r31->unk38[i]++ >= 20) {
                    Hu3DModelAttrSet(arg0->model[i + temp_r26 * 3 + 14], 1);
                }
                var_r31->unkF4[i].x = -675.0f;
                var_r31->unkF4[i].y = 175.0 + var_r31->unk88[i] * sind(var_r31->unk118[i].y);
                var_r31->unkF4[i].z = 500.0 + var_r31->unk88[i] * cosd(var_r31->unk118[i].y);
                Hu3DModelPosSet(arg0->model[i + temp_r26 * 3 + 2], var_r31->unkF4[i].x, var_r31->unkF4[i].y, var_r31->unkF4[i].z);
                Hu3DModelRotSet(arg0->model[i + temp_r26 * 3 + 2], var_r31->unk118[i].x, 0.0f, 0.0f);
                var_r31->unk118[i].z = var_r31->unk118[i].y + var_r31->unk74;
                if (var_r31->unk118[i].z >= 360.0f) {
                    var_r31->unk118[i].z -= 360.0f;
                } else if (var_r31->unk118[i].z < 0.0f) {
                    var_r31->unk118[i].z += 360.0f;
                }
                var_r31->unk118[i].x -= var_r31->unk78;
                if (var_r31->unk118[i].x >= 360.0f) {
                    var_r31->unk118[i].x -= 360.0f;
                } else if (var_r31->unk118[i].x < 0.0f) {
                    var_r31->unk118[i].x += 360.0f;
                }
                var_r31->unk118[i].y += var_r31->unk78;
                if (var_r31->unk118[i].y >= 360.0f) {
                    var_r31->unk118[i].y -= 360.0f;
                } else if (var_r31->unk118[i].y < 0.0f) {
                    var_r31->unk118[i].y += 360.0f;
                }
                break;
        }
    }
}

void fn_1_725C(omObjData* arg0) {
    fn_1_3B14(arg0);
    fn_1_3EA4(arg0);
    fn_1_5644(arg0);
    fn_1_4130(arg0);
}

void fn_1_72A4(StructBssC30* arg0) {
    omObjData* temp_r29;
    s32 i;
    s32 j;

    temp_r29 = arg0->unk00;
    Hu3DModelRotSet(temp_r29->model[0], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(temp_r29->model[0], 1);
    Hu3DModelPosSet(temp_r29->model[1], 0.0f, 0.0f, -250.0f);
    Hu3DModelRotSet(temp_r29->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(temp_r29->model[1], 1);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DModelPosSet(temp_r29->model[i + 2], 0.0f, -325.0f, 500.0f);
            Hu3DModelAttrSet(temp_r29->model[j + i * 3 + 2], 1);
            Hu3DModelAttrSet(temp_r29->model[j + i * 3 + 14], 1);
        }
    }
    arg0->unk74 = 0.0f;
    for (i = 0; i < 3; i++) {
        arg0->unk2C[i] = 0;
        arg0->unkAC[i].x = arg0->unkD0[i].x = -675.0f;
        arg0->unkAC[i].y = arg0->unkD0[i].y = 175.0f;
        arg0->unkAC[i].z = arg0->unkD0[i].z = 500.0f;
        arg0->unk38[i] = 0;
        arg0->unkF4[i].x = 0.0f;
        arg0->unkF4[i].y = -325.0f;
        arg0->unkF4[i].z = 500.0f;
        arg0->unk118[i].x = arg0->unk118[i].y = arg0->unk118[i].z = 0.0f;
        arg0->unk44[i] = 0;
        arg0->unk50[i] = 0;
        arg0->unk7C[i] = arg0->unk88[i] = 0.0f;
        arg0->unk94[i] = arg0->unkA0[i] = 0.0f;
        arg0->unk5C[i] = arg0->unk68[i] = 0;
    }
    arg0->unk24 = 9999;
    temp_r29->work[0] = temp_r29->work[1] = temp_r29->work[2] = temp_r29->work[3] = 0;
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
    arg0->unk14[0] = arg0->unk14[1] = arg0->unk14[2] = arg0->unk20 = 0;
}

void fn_1_7628(omObjData* arg0) {
    StructBssC30* var_r30;
    s32 i;
    s32 j;

    var_r30 = &lbl_1_bss_C30;
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 24));
    arg0->motion[0] = Hu3DMotionIDGet(arg0->model[0]);
    Hu3DModelRotSet(arg0->model[0], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[0], 1U);
    Hu3DModelLayerSet(arg0->model[0], 1);
    Hu3DModelShadowSet(arg0->model[0]);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 25));
    arg0->motion[1] = Hu3DMotionIDGet(arg0->model[1]);
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_M435, 35));
    Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, -250.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[1], 1);
    Hu3DModelLayerSet(arg0->model[1], 1);
    Hu3DModelShadowSet(arg0->model[1]);
    Hu3DModelHookSet(arg0->model[1], "m435a02-itemfook_d", arg0->model[0]);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            arg0->model[j + i * 3 + 2] = Hu3DModelCreateFile(lbl_1_data_0[fn_1_8F34(i)][0]);
            Hu3DModelAttrSet(arg0->model[j + i * 3 + 2], 1);
            Hu3DModelShadowSet(arg0->model[j + i * 3 + 2]);
            arg0->model[j + i * 3 + 14] = Hu3DModelCreateFile(lbl_1_data_0[fn_1_8F34(i)][1]);
            Hu3DModelRotSet(arg0->model[j + i * 3 + 14], 0.0f, 90.0f, 0.0f);
            Hu3DModelAttrSet(arg0->model[j + i * 3 + 14], 1);
        }
    }
    arg0->work[0] = arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
    var_r30->unk04 = var_r30->unk08 = var_r30->unk0C = var_r30->unk10 = 0;
    var_r30->unk14[0] = var_r30->unk14[1] = var_r30->unk14[2] = var_r30->unk20 = 0;
    arg0->func = fn_1_725C;
}

void fn_1_799C(s32 arg0) {
    StructBssC1C* var_r31;

    var_r31 = &lbl_1_bss_C1C;
    var_r31->unk00->work[0] = arg0;
}

void fn_1_79C0(omObjData* arg0) {
    switch (arg0->work[0]) {
        case 1:
            arg0->work[0] = 0;
            fn_1_157BC(arg0, 0, 1, 30, 1);
            break;
        case 2:
            arg0->work[0] = 0;
            fn_1_157BC(arg0, 0, 2, 10, 0);
            break;
        case 3:
            arg0->work[0] = 0;
            fn_1_157BC(arg0, 0, 3, 10, 0);
            break;
    }
}

void fn_1_7A78(StructBssC1C* arg0) {
    omObjData* temp_r31;

    temp_r31 = arg0->unk00;
    omSetTra(temp_r31, 0.0f, 37.0f, -565.0f);
    omSetSca(temp_r31, 1.5f, 1.5f, 1.5f);
    fn_1_157BC(temp_r31, 0, 1, 1, 1);
    temp_r31->work[0] = temp_r31->work[1] = temp_r31->work[2] = temp_r31->work[3] = 0;
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
}

void fn_1_7B44(omObjData* arg0) {
    StructBssC1C* var_r30;

    var_r30 = &lbl_1_bss_C1C;
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 48));
    arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 53));
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 49));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 50));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 51));
    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 52));
    omSetTra(arg0, 0.0f, 37.0f, -565.0f);
    omSetSca(arg0, 1.5f, 1.5f, 1.5f);
    Hu3DModelShadowSet(arg0->model[0]);
    fn_1_157BC(arg0, 0, 1, 1, 1);
    arg0->work[0] = arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
    var_r30->unk04 = var_r30->unk08 = var_r30->unk0C = var_r30->unk10 = 0;
    arg0->func = fn_1_79C0;
}

void fn_1_7D28(s32 arg0, s32 arg1) {
    StructBss2A4* temp_r31;

    temp_r31 = &lbl_1_bss_2A4[arg0];
    temp_r31->unk1C = arg1;
}

void fn_1_7D50(s32 arg0) {
    StructBss2A4* temp_r31;

    temp_r31 = &lbl_1_bss_2A4[1];
    temp_r31->unk20 = arg0;
}

void fn_1_7D74(omObjData* arg0) {
    StructBss2A4* temp_r30;

    temp_r30 = &lbl_1_bss_2A4[arg0->work[0]];
    switch (temp_r30->unk1C) {
        case 1:
            temp_r30->unk1C = 0;
            if (arg0->work[0] != 0) {
                fn_1_157BC(arg0, 0, 0, 30, 1);
            } else {
                fn_1_157BC(arg0, 0, 0, 30, 1);
                fn_1_157BC(arg0, 1, 5, 30, 1);
            }
            break;
        case 2:
            temp_r30->unk1C = 0;
            if (arg0->work[0] != 0) {
                fn_1_157BC(arg0, 0, 4, 10, 0);
            } else {
                fn_1_157BC(arg0, 0, 2, 10, 0);
                fn_1_157BC(arg0, 1, 5, 10, 2);
            }
            break;
        case 3:
            temp_r30->unk1C = 0;
            if (arg0->work[0] != 0) {
                fn_1_157BC(arg0, 0, 9, 5, 0);
            }
            break;
    }
}

void fn_1_7ED4(omObjData* arg0) {
    StructBss2A4* temp_r31;
    Mtx sp38;
    Mtx sp8;

    temp_r31 = &lbl_1_bss_2A4[arg0->work[0]];
    switch (temp_r31->unk20) {
        case 1:
        case 3:
        case 6:
            temp_r31->unk04.x = arg0->trans.x;
            temp_r31->unk04.y = arg0->trans.y;
            temp_r31->unk04.z = arg0->trans.z;
            Hu3DModelObjMtxGet(lbl_1_bss_C30.unk00->model[1], "435a02-point00", sp38);
            temp_r31->unk10.x = sp38[0][3];
            temp_r31->unk10.y = sp38[1][3];
            temp_r31->unk10.z = sp38[2][3];
            if (temp_r31->unk20 == 1) {
                temp_r31->unk10.x = temp_r31->unk04.x - 30.0f;
            } else if (temp_r31->unk20 == 6) {
                temp_r31->unk10.x = (120.0f + sp38[0][3]);
                temp_r31->unk10.z = (sp38[2][3] - 50.0f);
            }
            temp_r31->unk2C = 0;
            temp_r31->unk20++;
            break;
        case 2:
            fn_1_15934(arg0, 0, 1, 10, 1);
            fn_1_195F4(arg0, 0, &temp_r31->unk04, &temp_r31->unk10, 5, temp_r31->unk2C++, 0xF);
            if (temp_r31->unk2C > 15) {
                temp_r31->unk20++;
            }
            break;
        case 4:
            if (temp_r31->unk2C == 25) {
                fn_1_15934(arg0, 0, 0, 5, 1);
            } else if (temp_r31->unk2C == 40) {
                fn_1_15934(arg0, 0, 5, 30, 1);
            }
            fn_1_195F4(arg0, 0, &temp_r31->unk04, &temp_r31->unk10, 10, temp_r31->unk2C++, 25);
            if (temp_r31->unk2C > 60) {
                fn_1_3AF4(2);
                temp_r31->unk20++;
            }
            break;
        case 5:
            Hu3DModelObjMtxGet(lbl_1_bss_C30.unk00->model[1], "435a02-point00", sp8);
            omSetTra(arg0, sp8[0][3], sp8[1][3], sp8[2][3]);
            omSetRot(arg0, 0.0f, Hu3DData[lbl_1_bss_C30.unk00->model[1]].rot.y - 90.0f, 0.0f);
            break;
        case 7:
            fn_1_15934(arg0, 0, 1, 10, 1);
            fn_1_19530(arg0, 0, &temp_r31->unk04, &temp_r31->unk10, 5, temp_r31->unk2C++, 15);
            fn_1_19658(arg0, 0, 90.0f, 5);
            if (temp_r31->unk2C > 15) {
                temp_r31->unk20++;
            }
            break;
        case 8:
            fn_1_15934(arg0, 0, 0, 5, 1);
            lbl_1_bss_14 = 1;
            temp_r31->unk20 = temp_r31->unk2C = 0;
            break;
    }
}

void fn_1_8250(s32 arg0) {
    StructBss2A4* temp_r31;

    temp_r31 = &lbl_1_bss_2A4[1];
    temp_r31->unk24 = arg0;
}

void fn_1_8274(omObjData* arg0) {
    StructBss2A4* temp_r31;
    Mtx sp8;

    temp_r31 = &lbl_1_bss_2A4[arg0->work[0]];
    switch (temp_r31->unk24) {
        case 1:
        case 3:
        case 5:
            fn_1_15934(temp_r31->unk00, 0, 1, 10, 1);
            temp_r31->unk04.x = arg0->trans.x;
            temp_r31->unk04.y = arg0->trans.y;
            temp_r31->unk04.z = arg0->trans.z;
            if (temp_r31->unk24 == 1) {
                temp_r31->unk10.x = -400.0f;
                temp_r31->unk10.y = arg0->trans.y;
                temp_r31->unk10.z = -310.0f;
            } else if (temp_r31->unk24 == 3) {
                temp_r31->unk10.x = 400.0f;
                temp_r31->unk10.y = arg0->trans.y;
                temp_r31->unk10.z = arg0->trans.z;
            } else if (temp_r31->unk24 == 5) {
                temp_r31->unk10.x = 400.0f;
                temp_r31->unk10.y = 37.0f;
                temp_r31->unk10.z = -425.0f;
            }
            temp_r31->unk2C = 0;
            temp_r31->unk24++;
            break;
        case 2:
            fn_1_195F4(arg0, 0, &temp_r31->unk04, &temp_r31->unk10, 10, temp_r31->unk2C++, 90);
            if (temp_r31->unk2C > 90) {
                temp_r31->unk24++;
            }
            break;
        case 4:
            fn_1_195F4(arg0, 0, &temp_r31->unk04, &temp_r31->unk10, 10, temp_r31->unk2C++, 90);
            if (temp_r31->unk2C > 90) {
                temp_r31->unk24++;
            }
            break;
        case 6:
            fn_1_195F4(arg0, 0, &temp_r31->unk04, &temp_r31->unk10, 10, temp_r31->unk2C++, 15);
            if (temp_r31->unk2C > 15) {
                temp_r31->unk24++;
                temp_r31->unk2C = 0;
            }
            break;
        case 7:
            fn_1_19658(arg0, 0, -15.0f, 5);
            if (temp_r31->unk2C++ > 15) {
                temp_r31->unk24++;
            }
            break;
        case 8:
            fn_1_15934(temp_r31->unk00, 0, 0, 10, 1);
            temp_r31->unk24 = 0;
            break;
        case 10:
            temp_r31->unk24 = 0;
            Hu3DModelObjMtxGet(lbl_1_bss_C30.unk00->model[1], "435a02-point00", sp8);
            arg0->trans.x = sp8[0][3];
            arg0->trans.y = sp8[1][3];
            arg0->trans.z = sp8[2][3];
            break;
    }
}

void fn_1_8544(s32 arg0) {
    StructBss2A4* temp_r31;

    temp_r31 = &lbl_1_bss_2A4[1];
    fn_1_15934(temp_r31->unk00, 0, arg0, 1, 0);
}

void fn_1_8590(omObjData* arg0) {
    StructBss2A4* temp_r29;

    temp_r29 = &lbl_1_bss_2A4[arg0->work[0]];
    if (temp_r29->unk1C != 0) {
        fn_1_7D74(arg0);
    }
    if (temp_r29->unk20 != 0) {
        fn_1_7ED4(arg0);
    }
    fn_1_8274(arg0);
}

void fn_1_8734(StructBss2A4* arg0) {
    omObjData* temp_r30;

    temp_r30 = arg0->unk00;
    if (temp_r30->work[0] != 0) {
        omSetTra(temp_r30, 400.0f, 37.0f, -425.0f);
        omSetRot(temp_r30, 0.0f, -15.0f, 0.0f);
        fn_1_157BC(temp_r30, 0, 0, 1, 1);
        fn_1_19974(&arg0->unk3C, 0);
        fn_1_198F8(&arg0->unk3C, -1);
        fn_1_19968(&arg0->unk3C, -1);
    } else {
        omSetTra(temp_r30, -400.0f, 37.0f, -425.0f);
        fn_1_157BC(temp_r30, 0, 0, 1, 1);
        fn_1_157BC(temp_r30, 1, 5, 1, 1);
    }
    temp_r30->work[1] = temp_r30->work[2] = temp_r30->work[3] = 0;
    arg0->unk1C = arg0->unk20 = arg0->unk24 = arg0->unk28 = 0;
    arg0->unk2C = arg0->unk30 = arg0->unk34 = arg0->unk38 = 0;
    lbl_1_bss_14 = 0;
}

void fn_1_88B0(omObjData* arg0) {
    StructBss2A4* temp_r30;
    s32 var_r29;

    var_r29 = arg0->work[0];
    temp_r30 = &lbl_1_bss_2A4[var_r29];
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 56));
    if (arg0->work[0] != 0) {
        arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 57));
        arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 58));
        arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 62));
        arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 63));
        arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 64));
        arg0->motion[5] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 65));
        arg0->motion[6] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 66));
        arg0->motion[7] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 67));
        arg0->motion[8] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 68));
        arg0->motion[9] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 69));
        arg0->motion[10] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 70));
        arg0->motion[11] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 71));
        arg0->motion[12] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 72));
        omSetTra(arg0, 400.0f, 37.0f, -425.0f);
        omSetRot(arg0, 0.0f, -15.0f, 0.0f);
        fn_1_157BC(arg0, 0, 0, 1, 1);
        fn_1_1A33C(lbl_1_bss_0, &temp_r30->unk3C, arg0->model[0], "g007m0-skl_at", 0x100, 0);
        fn_1_19974(&temp_r30->unk3C, 0);
        fn_1_198F8(&temp_r30->unk3C, -1);
        fn_1_19968(&temp_r30->unk3C, -1);
    } else {
        arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 59));
        arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 60));
        arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 61));
        arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 73));
        omSetTra(arg0, -400.0f, 37.0f, -425.0f);
        fn_1_157BC(arg0, 0, 0, 1, 1);
        arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 74));
        arg0->motion[5] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_M435, 75));
        arg0->motion[6] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_M435, 76));
        Hu3DModelHookSet(arg0->model[0], "g007m0-itemhook_r", arg0->model[1]);
        Hu3DModelLayerSet(arg0->model[0], 2);
        Hu3DModelLayerSet(arg0->model[1], 2);
        fn_1_157BC(arg0, 1, 5, 1, 1);
    }
    Hu3DModelShadowSet(arg0->model[0]);
    arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
    temp_r30->unk1C = temp_r30->unk20 = temp_r30->unk24 = temp_r30->unk28 = 0;
    temp_r30->unk2C = temp_r30->unk30 = temp_r30->unk34 = temp_r30->unk38 = 0;
    lbl_1_bss_14 = 0;
    arg0->func = fn_1_8590;
}

s32 fn_1_8E48(s32 arg0) {
    StructBssE88* temp_r31;

    temp_r31 = &lbl_1_bss_E88[arg0];
    return temp_r31->unk24;
}

s32 fn_1_8E70(void) {
    s32 var_r30;
    s32 i;

    var_r30 = 0;
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_E88[i].unk2C != 0) {
            var_r30++;
        }
    }
    return var_r30;
}

s32 fn_1_8EC8(s32 arg0) {
    if (lbl_1_bss_E88[arg0].unk2C != 0) {
        return 1;
    } else {
        return 0;
    }
}

s32 fn_1_8EF4(s32 arg0) {
    if (HuPadBtnDown[lbl_1_bss_E88[arg0].unk38] == 0x100) {
        return 1;
    } else {
        return 0;
    }
}

s32 fn_1_8F34(s32 arg0) {
    return lbl_1_bss_E88[arg0].unk34;
}

void fn_1_8F4C(void) {
    StructBssE88* temp_r31;
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
        temp_r31 = &lbl_1_bss_E88[i];
        temp_r31->unk24 = sp8[i];
        temp_r31->unk28 = GWPlayerCfg[temp_r31->unk24].group;
        temp_r31->unk2C = GWPlayerCfg[temp_r31->unk24].iscom;
        temp_r31->unk30 = GWPlayerCfg[temp_r31->unk24].diff;
        temp_r31->unk34 = GWPlayerCfg[temp_r31->unk24].character;
        temp_r31->unk38 = GWPlayerCfg[temp_r31->unk24].pad_idx;
    }
}

void fn_1_909C(omObjData* arg0, Vec arg1, float arg2, float arg3, float arg4, float arg5, s32 arg6) {
    StructBssE88* sp18;
    float temp_f31;
    float temp_f30;
    float var_f26;
    float var_f27;

    sp18 = &lbl_1_bss_E88[arg0->work[0]];
    temp_f31 = arg1.x - arg0->trans.x;
    temp_f30 = arg0->trans.z - arg1.z;
    var_f26 = 90.0 + atan2d(temp_f30, temp_f31);
    var_f27 = sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30);
    if (var_f27 <= arg4) {
        temp_f31 = temp_f30 = 0.0f;
    } else {
        temp_f31 = 72.0f * (temp_f31 / var_f27);
        temp_f30 = 72.0f * (temp_f30 / var_f27);
    }
    var_f27 = arg3 * (sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30) / 72.0f);
    if (var_f27 >= arg3) {
        var_f27 = arg3;
    } else if (var_f27 <= 1.0f) {
        temp_f31 = temp_f30 = var_f27 = 0.0f;
    }
    if (temp_f31 != 0.0f || temp_f30 != 0.0f || arg2 >= 0.0f) {
        if (arg2 >= 0.0f && temp_f31 == 0.0f && temp_f30 == 0.0f) {
            var_f26 = arg2;
        }
        if (var_f26 >= 180.0f) {
            if (arg0->rot.y - var_f26 >= 180.0f) {
                arg0->rot.y -= 360.0f;
            }
            if (arg0->rot.y - var_f26 < -180.0f) {
                arg0->rot.y += 360.0f;
            }
        } else {
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
    if (var_f27 >= 6.75f) {
        if (arg6 != 0) {
            fn_1_15934(arg0, 0, 5, 10, 1);
        } else {
            fn_1_15934(arg0, 0, 2, 10, 1);
        }
    } else {
        if (var_f27 > 0.0f) {
            fn_1_15934(arg0, 0, 2, 10, 1);
        } else {
            fn_1_15934(arg0, 0, 0, 10, 1);
        }
    }
}

void fn_1_9768(s32 arg0, s32 arg1) {
    StructBssE88* temp_r31;

    temp_r31 = &lbl_1_bss_E88[arg0];
    temp_r31->unk04 = arg1;
}

void fn_1_9790(omObjData* arg0) {
    StructBssE88* temp_r31;

    temp_r31 = &lbl_1_bss_E88[arg0->work[0]];
    switch (temp_r31->unk04) {
        case 0:
            temp_r31->unk04 = 99;
            Hu3DModelAttrSet(arg0->model[0], 1);
            break;
        case 1:
            temp_r31->unk04 = 99;
            Hu3DModelAttrReset(arg0->model[0], 1);
            break;
    }
}

void fn_1_9824(s32 arg0, s32 arg1) {
    StructBssE88* temp_r31;

    temp_r31 = &lbl_1_bss_E88[arg0];
    temp_r31->unk08 = arg1;
}

void fn_1_984C(omObjData* arg0) {
    StructBssE88* temp_r30;
    HsfMaterial* var_r31;
    HsfData* temp_r28;
    char** temp_r27;
    s32 var_r23;
    s32 i, j;
    ModelData* temp_r25;
    HsfAttribute* temp_r24;

    temp_r30 = &lbl_1_bss_E88[arg0->work[0]];
    if (temp_r30->unk08 != 1) {
        return;
    }
    var_r23 = 1;
    temp_r25 = &Hu3DData[arg0->model[0]];
    temp_r28 = temp_r25->hsfData;
    var_r31 = temp_r28->material;
    if (temp_r30->unk34 == 3) {
        for (i = 0; i < temp_r25->hsfData->materialCnt; i++, var_r31++) {
            if (i == 1 || i == 2) {
                continue;
            }
            var_r31->color[0] *= temp_r30->unk3C;
            if (var_r31->color[0] == 0) {
                var_r31->color[0] = 0;
            }
            var_r31->color[1] *= temp_r30->unk3C;
            if (var_r31->color[1] == 0) {
                var_r31->color[1] = 0;
            }
            var_r31->color[2] *= temp_r30->unk3C;
            if (var_r31->color[2] == 0) {
                var_r31->color[2] = 0;
            }
        }
    } else {
        temp_r27 = CharModelTexNameGet(temp_r30->unk34, 2);
        for (i = 0; i < temp_r28->materialCnt; i++, var_r31++) {
            var_r23 = 1;
            for (j = 0; j < var_r31->numAttrs; j++) {
                temp_r24 = &temp_r28->attribute[var_r31->attrs[j]];
                if (strcmp(temp_r27[0], temp_r24->bitmap->name) == 0 || strcmp(temp_r27[1], temp_r24->bitmap->name) == 0) {
                    var_r23 = 0;
                }
            }
            if (var_r23 == 0) {
                continue;
            }
            var_r31->color[0] *= temp_r30->unk3C;
            if (var_r31->color[0] == 0) {
                var_r31->color[0] = 0;
            }
            var_r31->color[1] *= temp_r30->unk3C;
            if (var_r31->color[1] == 0) {
                var_r31->color[1] = 0;
            }
            var_r31->color[2] *= temp_r30->unk3C;
            if (var_r31->color[2] == 0) {
                var_r31->color[2] = 0;
            }
        }
    }
    temp_r30->unk3C -= 0.01;
    if (temp_r30->unk3C < 0.0f) {
        temp_r30->unk08 = 99;
        temp_r30->unk3C = 0.0f;
    }
}

void fn_1_9BCC(s32 arg0, s32 arg1) {
    StructBssE88* temp_r31;

    temp_r31 = &lbl_1_bss_E88[arg0];
    temp_r31->unk0C = arg1;
    temp_r31->unk1C = 15 - arg1 * 5;
    temp_r31->unk20 = 0;
}

void fn_1_9C08(omObjData* arg0) {
    StructBssE88* temp_r31 = &lbl_1_bss_E88[arg0->work[0]];
    Vec sp14[] = {
        {     0.0f, 0.0f,   0.0f },
        {   600.0f, 0.0f, 800.0f },
        {  -200.0f, 0.0f, 800.0f },
        { -1000.0f, 0.0f, 400.0f }
    };

    if (temp_r31->unk0C >= 1) {
        if (temp_r31->unk1C-- <= 0) {
            temp_r31->unk20 = 1;
        }
        if (temp_r31->unk20 != 0) {
            fn_1_909C(arg0, sp14[temp_r31->unk0C], -1.0f, 7.0f + temp_r31->unk0C, 30.0f, 5.0f, 1);
        }
    }
}

void fn_1_9D88(omObjData* arg0) {
    fn_1_9790(arg0);
    fn_1_984C(arg0);
    fn_1_9C08(arg0);
}

void fn_1_9F7C(StructBssE88* arg0) {
    omObjData* temp_r30 = arg0->unk00;
    Vec sp8[] = {
        {   0.0f, 0.0f, 500.0f },
        { 200.0f, 0.0f, 300.0f },
        { 200.0f, 0.0f, 450.0f },
        { 200.0f, 0.0f, 600.0f }
    };
    s32 temp_r29;

    temp_r29 = temp_r30->work[0];
    omSetTra(temp_r30, sp8[temp_r29].x, sp8[temp_r29].y, sp8[temp_r29].z);
    omSetRot(temp_r30, 0.0f, -90.0f, 0.0f);
    Hu3DModelAttrSet(temp_r30->model[0], 1);
    fn_1_15934(temp_r30, 0, 0, 0, 1);
    fn_1_19974(&arg0->unk58, 0);
    fn_1_198F8(&arg0->unk58, -1);
    fn_1_19968(&arg0->unk58, -1);
    temp_r30->work[1] = temp_r30->work[2] = temp_r30->work[3] = 0;
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
    arg0->unk14 = arg0->unk18 = arg0->unk1C = arg0->unk20 = 0;
    arg0->unk40 = arg0->unk44 = arg0->unk48 = 0.0f;
    arg0->unk4C = arg0->unk50 = arg0->unk54 = 0.0f;
    arg0->unk3C = 1.0f;
}

void fn_1_A148(omObjData* arg0) {
    s32 temp_r29 = arg0->work[0];
    StructBssE88* temp_r31 = &lbl_1_bss_E88[temp_r29];
    Vec sp8[] = {
        {   0.0f, 0.0f, 500.0f },
        { 200.0f, 0.0f, 300.0f },
        { 200.0f, 0.0f, 450.0f },
        { 200.0f, 0.0f, 600.0f }
    };

    arg0->model[0] = CharModelCreate(temp_r31->unk34, 2);
    arg0->motion[0] = CharModelMotionCreate(temp_r31->unk34, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
    arg0->motion[1] = CharModelMotionCreate(temp_r31->unk34, DATA_MAKE_NUM(DATADIR_MARIOMOT, 2));
    arg0->motion[2] = CharModelMotionCreate(temp_r31->unk34, DATA_MAKE_NUM(DATADIR_MARIOMOT, 3));
    arg0->motion[6] = CharModelMotionCreate(temp_r31->unk34, DATA_MAKE_NUM(DATADIR_MARIOMOT, 28));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, temp_r31->unk34));
    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 8 + temp_r31->unk34));
    arg0->motion[5] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M435, 16 + temp_r31->unk34));
    omSetTra(arg0, sp8[temp_r29].x, sp8[temp_r29].y, sp8[temp_r29].z);
    omSetRot(arg0, 0.0f, -90.0f, 0.0f);
    Hu3DModelShadowSet(arg0->model[0]);
    Hu3DModelAttrSet(arg0->model[0], 1);
    fn_1_15934(arg0, 0, 0, 0, 1);
    fn_1_1A33C(lbl_1_bss_0, &temp_r31->unk58, arg0->model[0], lbl_1_data_E0[temp_r31->unk34], lbl_1_data_100[temp_r31->unk34][0], lbl_1_data_100[temp_r31->unk34][1]);
    fn_1_19974(&temp_r31->unk58, 0);
    fn_1_198F8(&temp_r31->unk58, -1);
    fn_1_19968(&temp_r31->unk58, -1);
    arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
    temp_r31->unk04 = temp_r31->unk08 = temp_r31->unk0C = temp_r31->unk10 = 0;
    temp_r31->unk14 = temp_r31->unk18 = temp_r31->unk1C = temp_r31->unk20 = 0;
    temp_r31->unk40 = temp_r31->unk44 = temp_r31->unk48 = 0.0f;
    temp_r31->unk4C = temp_r31->unk50 = temp_r31->unk54 = 0.0f;
    temp_r31->unk3C = 1.0f;
    CharModelMotionDataClose(temp_r31->unk34);
    arg0->func = fn_1_9D88;
}

void fn_1_A4B8(s32 arg0, s32 arg1) {
    StructBss144* var_r31;

    var_r31 = &lbl_1_bss_144[arg0];
    var_r31->unk2C = arg1;
}

void fn_1_A4E0(omObjData* arg0) {
    StructBss144* temp_r31;
    s32 i;

    temp_r31 = &lbl_1_bss_144[arg0->work[0]];
    switch (temp_r31->unk2C) {
        case 0:
            temp_r31->unk4C -= 0.1f;
            if (temp_r31->unk4C < 0.0f) {
                temp_r31->unk4C = 0.0f;
            }
            break;
        case 1:
            temp_r31->unk4C += 0.1f;
            if (temp_r31->unk4C > 1.0f) {
                temp_r31->unk4C = 1.0f;
            }
            break;
    }
    for (i = 0; i < 6; i++) {
        if (temp_r31->unk4C > 0.0f) {
            espDispOn(temp_r31->unk04[i]);
        } else {
            espDispOff(temp_r31->unk04[i]);
        }
        if (i == 5) {
            espTPLvlSet(temp_r31->unk04[i], 0.5f * temp_r31->unk4C);
        } else {
            espTPLvlSet(temp_r31->unk04[i], temp_r31->unk4C);
        }
    }
}

void fn_1_A670(s32 arg0, s32 arg1) {
    StructBss144* temp_r31;

    temp_r31 = &lbl_1_bss_144[arg0];
    temp_r31->unk54 = temp_r31->unk50;
    temp_r31->unk50 = arg1;
    if (temp_r31->unk50 < 0) {
        temp_r31->unk50 = 0;
    } else if (temp_r31->unk50 > 999) {
        temp_r31->unk50 = 999;
    }
    temp_r31->unk3C = 0;
}

void fn_1_A6D4(omObjData* arg0) {
    StructBss144* temp_r31;
    s32 temp_r30;
    s32 var_r29;

    temp_r31 = &lbl_1_bss_144[arg0->work[0]];
    if (temp_r31->unk3C <= 60) {
        var_r29 = fn_1_152D4(temp_r31->unk54, temp_r31->unk50, temp_r31->unk3C++, 60.0f);
    } else {
        var_r29 = temp_r31->unk54 = temp_r31->unk50;
    }
    if ((temp_r30 = var_r29 / 100) == 0) {
        espDispOff(temp_r31->unk04[0]);
    }
    espBankSet(temp_r31->unk04[0], temp_r30);
    if ((temp_r30 = (var_r29 % 100) / 10) == 0 && var_r29 / 100 == 0) {
        espDispOff(temp_r31->unk04[1]);
    }
    espBankSet(temp_r31->unk04[1], temp_r30);
    temp_r30 = var_r29 % 10;
    espBankSet(temp_r31->unk04[2], temp_r30);
}

void fn_1_A8C4(omObjData* arg0) {
    fn_1_A4E0(arg0);
    fn_1_A6D4(arg0);
}

void fn_1_ABFC(StructBss144* arg0) {
    omObjData* temp_r30;

    temp_r30 = arg0->unk00;
    espTPLvlSet(arg0->unk04[5], 0.0f);
    espDispOff(arg0->unk04[5]);
    espTPLvlSet(arg0->unk04[4], 0.0f);
    espDispOff(arg0->unk04[4]);
    espTPLvlSet(arg0->unk04[3], 0.0f);
    espDispOff(arg0->unk04[3]);
    espTPLvlSet(arg0->unk04[2], 0.0f);
    espDispOff(arg0->unk04[2]);
    espTPLvlSet(arg0->unk04[1], 0.0f);
    espDispOff(arg0->unk04[1]);
    espTPLvlSet(arg0->unk04[0], 0.0f);
    espDispOff(arg0->unk04[0]);
    temp_r30->work[1] = temp_r30->work[2] = temp_r30->work[3] = 0;
    arg0->unk4C = 0.0f;
    arg0->unk50 = arg0->unk54 = 0;
    arg0->unk2C = arg0->unk30 = arg0->unk34 = arg0->unk38 = 0;
    arg0->unk3C = arg0->unk40 = arg0->unk44 = arg0->unk48 = 0;
}

void fn_1_AD5C(omObjData* arg0) {
    StructBss144* temp_r31;
    StructBssE88* var_r26;
    s32 temp_r27;
    s32 var_r28;
    s32 var_r29;

    temp_r27 = arg0->work[0];
    var_r28 = 62;
    temp_r31 = &lbl_1_bss_144[temp_r27];
    var_r26 = &lbl_1_bss_E88[temp_r27];
    if (temp_r27 < 2) {
        var_r29 = temp_r27 * 118 + 84;
    } else {
        var_r29 = (temp_r27 - 2) * 118 + 390;
    }
    temp_r31->unk04[5] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 21), 100, 0);
    espPosSet(temp_r31->unk04[5], var_r29, var_r28);
    espColorSet(temp_r31->unk04[5], 1, 1, 1);
    espTPLvlSet(temp_r31->unk04[5], 0.0f);
    espDispOff(temp_r31->unk04[5]);
    temp_r31->unk04[4] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 20), 100, 0);
    espPosSet(temp_r31->unk04[4], var_r29, var_r28);
    espTPLvlSet(temp_r31->unk04[4], 0.0f);
    espDispOff(temp_r31->unk04[4]);
    temp_r31->unk04[3] = espEntry(lbl_1_data_0[var_r26->unk34][2], 100, 0);
    espPosSet(temp_r31->unk04[3], var_r29 - 46, var_r28 - 2);
    espTPLvlSet(temp_r31->unk04[3], 0.0f);
    espDispOff(temp_r31->unk04[3]);
    temp_r31->unk04[0] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 51), 100, 0);
    espPosSet(temp_r31->unk04[0], var_r29 - 14, var_r28 + 2);
    espTPLvlSet(temp_r31->unk04[2], 0.0f);
    espDispOff(temp_r31->unk04[2]);
    temp_r31->unk04[1] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 51), 100, 0);
    espPosSet(temp_r31->unk04[1], var_r29 + 6, var_r28 + 2);
    espTPLvlSet(temp_r31->unk04[1], 0.0f);
    espDispOff(temp_r31->unk04[1]);
    temp_r31->unk04[2] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 51), 100, 0);
    espPosSet(temp_r31->unk04[2], var_r29 + 26, var_r28 + 2);
    espTPLvlSet(temp_r31->unk04[0], 0.0f);
    espDispOff(temp_r31->unk04[0]);
    arg0->work[1] = arg0->work[2] = arg0->work[3] = 0;
    temp_r31->unk4C = 0.0f;
    temp_r31->unk50 = temp_r31->unk54 = 0;
    temp_r31->unk2C = temp_r31->unk30 = temp_r31->unk34 = temp_r31->unk38 = 0;
    temp_r31->unk3C = temp_r31->unk40 = temp_r31->unk44 = temp_r31->unk48 = 0;
    arg0->func = fn_1_A8C4;
}

s32 fn_1_B1F4(omObjData* arg0) {
    StructBss4EE8* var_r25;
    StructBss9C* var_r31;
    StructBssC1C* var_r28;
    StructBssE88* temp_r26;
    Mtx sp8;
    s32 i;

    var_r25 = &lbl_1_bss_4EE8;
    var_r31 = &lbl_1_bss_9C;
    var_r28 = &lbl_1_bss_C1C;
    temp_r26 = &lbl_1_bss_E88[var_r25->unk10];
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
            fn_1_19974(&temp_r26->unk58, 0);
            fn_1_157BC(var_r28->unk00, 0, 4, 5, 0);
            break;
        case 2:
            if (Hu3DMotionTimeGet(var_r28->unk00->model[0]) == 90.0f) {
                arg0->work[1] = 3;
                fn_1_157BC(temp_r26->unk00, 0, 6, 5, 0);
                Hu3DMotionTimeSet(var_r28->unk00->model[0], 90.0f);
                Hu3DMotionSpeedSet(var_r28->unk00->model[0], 0.0f);
                HuAudCharVoicePlay(temp_r26->unk34, 0x123);
                HuAudFXPlay(0x6D5);
                omVibrate(temp_r26->unk24, 120, 12, 0);
            }
            break;
        case 3:
            Hu3DModelObjMtxGet(var_r28->unk00->model[0], "g000m0-itemhook_M", sp8);
            fn_1_9824(var_r25->unk10, 1);
            for (i = 0; i < 6; i++) {
                if (var_r31->unk04 == 1 || (var_r31->unk04 == 0 && var_r31->unk08[i] > 0.0f)) {
                    var_r31->unk08[i] += 10.0f;
                }
                if (var_r31->unk08[i] > 0.0f) {
                    var_r31->unk48[i] += 0.1f;
                    var_r31->unk28[i] -= 5.0f;
                    if (var_r31->unk88[i] == 0.0f) {
                        fn_1_157BC(arg0, i + 1, i + 1, 1, 1);
                    }
                    if (var_r31->unk88[i] < 8.0f) {
                        var_r31->unk68[i] += 0.025f;
                    } else if (var_r31->unk88[i] < 23.0f) {
                        var_r31->unk68[i] = 0.7f;
                    } else if (var_r31->unk88[i] < 31.0f) {
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
            }
            if (arg0->work[2] >= 10 && arg0->work[2] <= 120) {
                fn_1_230(6, -1, 8.0f);
            }
            break;
    }
}

void fn_1_B828(StructBss9C* arg0) {
    omObjData* temp_r29;
    s32 i;

    temp_r29 = arg0->unk00;
    for (i = 0; i < 6; i++) {
        fn_1_157BC(temp_r29, i + 1, i + 1, 5, 1);
        arg0->unk08[i] = -(50.0f * i);
        arg0->unk28[i] = 0.0f;
        arg0->unk48[i] = 0.0f;
        arg0->unk68[i] = 0.5f;
        arg0->unk88[i] = 0.0f;
    }
    arg0->unk04 = 1;
    temp_r29->work[0] = temp_r29->work[1] = temp_r29->work[2] = temp_r29->work[3] = 0;
}

void fn_1_B950(omObjData *arg0) {
    StructBss9C* var_r29;
    s32 i;

    var_r29 = &lbl_1_bss_9C;
    for (i = 0; i < 6; i++) {
        if (i % 2 == 0) {
            arg0->model[i + 1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 54));
            arg0->motion[i + 1] = Hu3DMotionIDGet(arg0->model[i + 1]);
        }
        else {
            arg0->model[i + 1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M435, 55));
            arg0->motion[i + 1] = Hu3DMotionIDGet(arg0->model[i + 1]);
        }
        fn_1_157BC(arg0, i + 1, i + 1, 5, 1);
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
    arg0->func = (void*) fn_1_B1F4; // fn_1_B1F4 must return s32 to match
}

void fn_1_BBE8(void) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk18 = 0.0f;
    var_r31->unk1C = 300.0f;
    var_r31->unk20 = 1740.0f;
    var_r31->unk30 = -10.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk38 = 0.0f;
    var_r31->unk40 = 300.0f;
    fn_1_161B0(var_r31, 200.0f);
}

void fn_1_BC98(void) {
    StructBssE08* var_r31;
    StructBssE08 sp8;

    var_r31 = &lbl_1_bss_E08;
    sp8.unk0C = 0.0f;
    sp8.unk10 = 200.0f;
    sp8.unk14 = -50.0f;
    sp8.unk24 = 5.0f;
    sp8.unk28 = 0.0f;
    sp8.unk2C = 0.0f;
    sp8.unk3C = 200.0f;
    fn_1_188E0(var_r31, &sp8, var_r31->unk44++, 30.0f, 5.0f);
}

void fn_1_BD70(void) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk18 = 0.0f;
    var_r31->unk1C = 200.0f;
    var_r31->unk20 = -50.0f;
    var_r31->unk30 = 5.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk38 = 0.0f;
    var_r31->unk40 = 200.0f;
    fn_1_161B0(var_r31, 200.0f);
}

void fn_1_BE20(void) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk18 = 0.0f;
    var_r31->unk1C = 300.0f;
    var_r31->unk20 = -550.0f;
    var_r31->unk30 = -15.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk38 = 0.0f;
    var_r31->unk40 = 1200.0f;
    fn_1_161B0(var_r31, 45.0f);
}

void fn_1_BED0(void) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk18 = 0.0f;
    var_r31->unk1C = 150.0f;
    var_r31->unk20 = -550.0f;
    var_r31->unk30 = -15.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk38 = 0.0f;
    var_r31->unk40 = 1200.0f;
    fn_1_161B0(var_r31, 30.0f);
}

void fn_1_BF80(void) {
    StructBssC30* var_r29;
    StructBss2A4* sp8;
    StructBssE08* var_r31;
    ModelData* temp_r30;

    var_r29 = &lbl_1_bss_C30;
    sp8 = &lbl_1_bss_2A4[1];
    var_r31 = &lbl_1_bss_E08;
    temp_r30 = &Hu3DData[var_r29->unk00->model[1]];
    var_r31->unk18 = temp_r30->pos.x;
    var_r31->unk1C = temp_r30->pos.y + 175.0f;
    var_r31->unk20 = temp_r30->pos.z;
    var_r31->unk30 = -5.0f;
    var_r31->unk34 = temp_r30->rot.y;
    var_r31->unk38 = 0.0f;
    var_r31->unk40 = 600.0f;
    fn_1_161B0(var_r31, 15.0f);
}

void fn_1_C064(void) {
    StructBssE08* var_r31;
    StructBssE08 sp8;

    var_r31 = &lbl_1_bss_E08;
    sp8.unk0C = 0.0f;
    sp8.unk10 = 175.0f;
    sp8.unk14 = -250.0f;
    sp8.unk24 = -5.0f;
    sp8.unk28 = 0.0f;
    sp8.unk2C = 0.0f;
    sp8.unk3C = 600.0f;
    fn_1_17804(var_r31, &sp8, var_r31->unk44++, 10.0f, 5.0f);
}

void fn_1_C13C(void) {
    StructBssE08* var_r31;
    StructBssE08 sp8;

    var_r31 = &lbl_1_bss_E08;
    sp8.unk0C = 0.0f;
    sp8.unk10 = 145.0f;
    sp8.unk14 = 500.0f;
    sp8.unk24 = -15.0f;
    sp8.unk28 = 90.0f;
    sp8.unk2C = 0.0f;
    sp8.unk3C = 800.0f;
    fn_1_17804(var_r31, &sp8, var_r31->unk44++, 60.0f, 5.0f);
}

void fn_1_C214(void) {
    StructBssE08* var_r31;
    StructBssE08 sp8;

    var_r31 = &lbl_1_bss_E08;
    sp8.unk0C = -1000.0f;
    sp8.unk10 = 150.0f;
    sp8.unk14 = 435.0f;
    sp8.unk24 = 0.0f;
    sp8.unk28 = 90.0f;
    sp8.unk2C = 0.0f;
    sp8.unk3C = 800.0f;
    fn_1_188E0(var_r31, &sp8, var_r31->unk44++, 30.0f, 15.0f);
}

void fn_1_C2EC(void) {
    StructBssE08* var_r31;
    StructBssE08 sp8;

    var_r31 = &lbl_1_bss_E08;
    sp8.unk0C = -1000.0f;
    sp8.unk10 = 200.0f;
    sp8.unk14 = 500.0f;
    sp8.unk24 = 10.0f;
    sp8.unk28 = 105.0f;
    sp8.unk2C = 0.0f;
    sp8.unk3C = 800.0f;
    fn_1_17804(var_r31, &sp8, var_r31->unk44++, 30.0f, 15.0f);
}

void fn_1_C3C4(void) {
    StructBssE08* var_r31;
    StructBssE08 sp8;

    var_r31 = &lbl_1_bss_E08;
    sp8.unk0C = -1000.0f;
    sp8.unk10 = 200.0f;
    sp8.unk14 = 500.0f;
    sp8.unk24 = 10.0f;
    sp8.unk28 = 105.0f;
    sp8.unk2C = 0.0f;
    sp8.unk3C = 800.0f;
    fn_1_188E0(var_r31, &sp8, var_r31->unk44++, 10.0f, 5.0f);
}

void fn_1_C49C(void) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk18 = 0.0f;
    var_r31->unk1C = 150.0f;
    var_r31->unk20 = -550.0f;
    var_r31->unk30 = -15.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk38 = 0.0f;
    var_r31->unk40 = 1200.0f;
    fn_1_161B0(var_r31, 20.0f);
}

void fn_1_C54C(void) {
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    var_r31->unk18 = 0.0f;
    var_r31->unk1C = 300.0f;
    var_r31->unk20 = -550.0f;
    var_r31->unk30 = -15.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk38 = 0.0f;
    var_r31->unk40 = 1200.0f;
    fn_1_161B0(var_r31, 20.0f);
}

void fn_1_C5FC(s32 arg0) {
    StructBssE08* var_r20;

    var_r20 = &lbl_1_bss_E08;
    fn_1_15E50(var_r20);
    switch (arg0) {
        case 0:
            fn_1_8A4(fn_1_BBE8);
            break;
        case 1:
            fn_1_8A4(fn_1_BC98);
            break;
        case 2:
            fn_1_8A4(fn_1_BD70);
            break;
        case 3:
            fn_1_8A4(fn_1_BE20);
            break;
        case 4:
            fn_1_8A4(fn_1_BED0);
            break;
        case 5:
            fn_1_8A4(fn_1_BF80);
            break;
        case 6:
            fn_1_8A4(fn_1_C064);
            break;
        case 7:
            fn_1_8A4(fn_1_C13C);
            break;
        case 8:
            fn_1_8A4(fn_1_C214);
            break;
        case 10:
            fn_1_8A4(fn_1_C49C);
            break;
        case 11:
            fn_1_8A4(fn_1_C54C);
            break;
    }
}

void fn_1_C764(void) {
    float sp1C[] = { 0.0f, 0.0f };
    s32 sp8;

    lbl_1_bss_4 = 0;
    fn_1_281C(sp1C, MAKE_MESSID(29, 0));
    fn_1_281C(sp1C, MAKE_MESSID(29, 1));
    sp8 = fn_1_1E80((580.0f - sp1C[0]) / 2, 80.0f, sp1C[0], sp1C[1], 2);
    HuAudFXPlay(0x6D1);
    fn_1_799C(2);
    fn_1_2798(sp8, MAKE_MESSID(29, 0));
    fn_1_2594(sp8, 0);
    fn_1_799C(2);
    fn_1_2798(sp8, MAKE_MESSID(29, 1));
    fn_1_2594(sp8, 0);
    fn_1_799C(1);
    fn_1_24C4(sp8);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_CCBC(void) {
    float sp1C[] = { 0.0f, 0.0f };
    s32 sp8;

    lbl_1_bss_4 = 0;
    fn_1_281C(sp1C, MAKE_MESSID(29, 2));
    sp8 = fn_1_1E80((580.0f - sp1C[0]) / 2, 100.0f, sp1C[0], sp1C[1], 2);
    HuAudFXPlay(0x6D2);
    fn_1_799C(3);
    fn_1_2798(sp8, MAKE_MESSID(29, 2));
    fn_1_2594(sp8, 60);
    fn_1_2BFC(3);
    fn_1_2594(sp8, 60);
    fn_1_799C(1);
    fn_1_24C4(sp8);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_D05C(void) {
    float sp1C[] = { 0.0f, 0.0f };
    s32 sp8;

    lbl_1_bss_4 = 0;
    fn_1_281C(sp1C, MAKE_MESSID(29, 64));
    sp8 = fn_1_1E80(550.0f - sp1C[0], 340.0f, sp1C[0], sp1C[1], 1);
    fn_1_7D28(1, 2);
    HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
    fn_1_2798(sp8, MAKE_MESSID(29, 64));
    fn_1_267C(sp8);
    fn_1_7D28(1, 1);
    fn_1_24C4(sp8);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_D498(s32 arg0) {
    float sp1C[] = { 0.0f, 0.0f };
    s32 sp10[] = {
        MAKE_MESSID(29, 6),
        MAKE_MESSID(29, 39),
        MAKE_MESSID(29, 41),
        MAKE_MESSID(29, 43),
        MAKE_MESSID(29, 45),
        MAKE_MESSID(29, 47),
        MAKE_MESSID(29, 49),
        MAKE_MESSID(29, 51),
        -1
    };
    s32 sp8;

    if (sp10[arg0] == -1) {
        return;
    }
    fn_1_7D28(0, 2);
    HuPrcSleep(15);
    fn_1_281C(sp1C, sp10[arg0]);
    sp8 = fn_1_1E80(20.0f, 360.0f, sp1C[0], sp1C[1], 0);
    HuAudFXPlayVolPan(0x3E, 0x7F, 0x20);
    fn_1_2798(sp8, sp10[arg0]);
    fn_1_2594(sp8, 0);
    fn_1_7D28(0, 1);
    fn_1_24C4(sp8);
}

void fn_1_D8BC(void) {
    float sp64[] = { 0.0f, 0.0f };
    s32 sp10[] = {
        MAKE_MESSID(29, 5),
        MAKE_MESSID(29, 38),
        MAKE_MESSID(29, 40),
        MAKE_MESSID(29, 42),
        MAKE_MESSID(29, 44),
        MAKE_MESSID(29, 46),
        MAKE_MESSID(29, 48),
        MAKE_MESSID(29, 50),
        MAKE_MESSID(29, 52)
    };
    s32 var_r30;
    s32 i;

    lbl_1_bss_4 = 0;
    for (i = 0; i < 9; i++) {
        fn_1_281C(sp64, sp10[i]);
    }
    var_r30 = fn_1_1E80(550.0f - sp64[0], 340.0f, sp64[0], sp64[1], 1);
    HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
    for (i = 0; i < 9; i++) {
        fn_1_7D28(1, 2);
        fn_1_2798(var_r30, sp10[i]);
        fn_1_2594(var_r30, 0);
        fn_1_D498(i);
    }
    fn_1_7D28(1, 1);
    fn_1_24C4(var_r30);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_E190(void) {
    float sp1C[] = { 0.0f, 0.0f };
    s32 sp8;

    lbl_1_bss_4 = 0;
    fn_1_281C(sp1C, MAKE_MESSID(29, 53));
    sp8 = fn_1_1E80((580.0f - sp1C[0]) / 2, 80.0f, sp1C[0], sp1C[1], 2);
    omVibrate(fn_1_8E48(0), 12, 4, 2);
    omVibrate(fn_1_8E48(1), 12, 4, 2);
    omVibrate(fn_1_8E48(2), 12, 4, 2);
    omVibrate(fn_1_8E48(3), 12, 4, 2);
    HuAudFXPlay(0x6D2);
    fn_1_799C(2);
    fn_1_2798(sp8, MAKE_MESSID(29, 53));
    fn_1_2594(sp8, 0);
    fn_1_799C(1);
    fn_1_24C4(sp8);
    lbl_1_bss_4++;
    HuPrcEnd();
}

void fn_1_E670(void) {
    float sp1C[] = { 0.0f, 0.0f };
    StructBss2A4* var_r27;
    s32 sp8;

    lbl_1_bss_4 = 0;
    fn_1_281C(sp1C, MAKE_MESSID(29, 54));
    sp8 = fn_1_1E80(580.0f - sp1C[0] - 40.0f, 260.0f, sp1C[0], sp1C[1], 1);
    var_r27 = &lbl_1_bss_2A4[1];
    fn_1_157BC(var_r27->unk00, 0, 12, 1, 0);
    HuAudFXPlayVolPan(0x3E, 0x7F, 0x20);
    fn_1_2798(sp8, MAKE_MESSID(29, 54));
    fn_1_2594(sp8, 15);
    fn_1_7D50(1);
    fn_1_2594(sp8, 15);
    fn_1_24C4(sp8);
    fn_1_C5FC(5);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_EA54(void) {
    float sp1C[] = { 0.0f, 0.0f };
    StructBss2A4* var_r27;
    s32 sp8;

    fn_1_281C(sp1C, MAKE_MESSID(29, 55));
    sp8 = fn_1_1E80(40.0f, 260.0f, sp1C[0], sp1C[1], 0);
    var_r27 = &lbl_1_bss_2A4[0];
    fn_1_157BC(var_r27->unk00, 0, 3, 1, 0);
    HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
    fn_1_2798(sp8, MAKE_MESSID(29, 55));
    fn_1_2594(sp8, 15);
    fn_1_7D28(0, 1);
    fn_1_2594(sp8, 15);
    fn_1_24C4(sp8);
    HuPrcEnd();
}

void fn_1_ED94(void) {
    float sp1C[] = { 0.0f, 0.0f };
    s32 sp8;

    lbl_1_bss_4 = 0;
    fn_1_281C(sp1C, MAKE_MESSID(29, 56));
    fn_1_C5FC(6);
    sp8 = fn_1_1E80((580.0f - sp1C[0]) / 2, 320.0f, sp1C[0], sp1C[1], 2);
    HuAudFXPlay(0x6D2);
    fn_1_799C(2);
    fn_1_2798(sp8, MAKE_MESSID(29, 56));
    fn_1_2594(sp8, 0);
    fn_1_799C(1);
    fn_1_24C4(sp8);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_F1DC(void) {
}

s32 fn_1_F1E0(void) {
    if (fn_1_15670(&lbl_1_bss_84, 0) == 80) {
        fn_1_C5FC(1);
        lbl_1_bss_4F08[0] = HuAudSeqPlay(6);
    }
    if (fn_1_15670(&lbl_1_bss_84, 0) == 115) {
        fn_1_C5FC(2);
    }
    if (fn_1_15670(&lbl_1_bss_84, 0) == 180) {
        fn_1_C5FC(3);
    }
    if (fn_1_15670(&lbl_1_bss_84, 0) == 0) {
        fn_1_2BFC(2);
    }
    if (fn_1_15670(&lbl_1_bss_84, 0) == 150) {
        fn_1_2BFC(1);
    }
    if (fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_F36C(void) {
    HuPrcChildCreate(fn_1_C764, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_F3A8(void) {
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_F404(void) {
    s32 i;

    HuPrcChildCreate(fn_1_CCBC, 100, 0x2000, 0, HuPrcCurrentGet());
    for (i = 0; i < 4; i++) {
        fn_1_9768(i, 1);
    }
}

s32 fn_1_F47C(void) {
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_F4D8(void) {
    StructBssC1C* sp8;

    sp8 = &lbl_1_bss_C1C;
    fn_1_C5FC(10);
}

s32 fn_1_F534(void) {
    if (fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_F57C(void) {
    HuPrcChildCreate(fn_1_D05C, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_F5B8(void) {
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        if (lbl_1_bss_8 != 0) {
            return fn_1_15520(&lbl_1_bss_84);
        }
        fn_1_1561C(&lbl_1_bss_84, 6);
    }
    return 0;
}

void fn_1_F638(void) {
    StructBssC1C* var_r31;

    var_r31 = &lbl_1_bss_C1C;
    fn_1_157BC(var_r31->unk00, 0, 0, 60, 1);
    HuPrcChildCreate(fn_1_D8BC, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_F69C(void) {
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_F6F8(void) {
    StructBssC1C* var_r31;

    var_r31 = &lbl_1_bss_C1C;
    fn_1_C5FC(11);
    fn_1_157BC(var_r31->unk00, 0, 1, 60, 1);
}

s32 fn_1_F768(void) {
    if (fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_F7B0(void) {
    StructBssC1C* var_r30;
    StructBss2A4* var_r31;

    lbl_1_bss_4 = 0;
    HuPrcChildCreate(fn_1_E190, 100, 0x2000, 0, HuPrcCurrentGet());
    var_r31 = &lbl_1_bss_2A4[1];
    var_r30 = &lbl_1_bss_C1C;
    fn_1_19974(&var_r31->unk3C, 1);
    fn_1_198F8(&var_r31->unk3C, -1);
    fn_1_19968(&var_r31->unk3C, -1);
    fn_1_19960(&var_r31->unk3C, var_r30->unk00->model[0]);
}

s32 fn_1_F858(void) {
    if (lbl_1_bss_4 != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_F89C(void) {
    HuPrcChildCreate(fn_1_E670, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_EA54, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_F8F8(void) {
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_F954(void) {
}

s32 fn_1_F958(void) {
    if (fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_F9A0(void) {
    lbl_1_bss_4 = 0;
    HuPrcChildCreate(fn_1_ED94, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_F9EC(void) {
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_FA48(void) {
    s32 i;
    StructBssC30* var_r28;
    StructBssC1C* var_r27;
    StructBssE88* temp_r30;
    StructBss2A4* var_r29;

    var_r28 = &lbl_1_bss_C30;
    var_r27 = &lbl_1_bss_C1C;
    fn_1_157BC(var_r27->unk00, 0, 0, 60, 1);
    fn_1_C5FC(7);
    for (i = 0; i < 4; i++) {
        temp_r30 = &lbl_1_bss_E88[i];
        fn_1_19974(&temp_r30->unk58, 1);
        fn_1_198F8(&temp_r30->unk58, -1);
        fn_1_19968(&temp_r30->unk58, -1);
        fn_1_19960(&temp_r30->unk58, var_r28->unk00->model[1]);
    }
    var_r29 = &lbl_1_bss_2A4[1];
    fn_1_19974(&var_r29->unk3C, 0);
    fn_1_198F8(&var_r29->unk3C, -1);
    fn_1_19968(&var_r29->unk3C, -1);
}

s32 fn_1_FB50(void) {
    if (fn_1_15670(&lbl_1_bss_84, 1) != 0 && lbl_1_bss_14 != 0) {
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

void fn_1_FBAC(void) {
    StructBss4EE8* var_r31;
    StructBss2A4* var_r30;
    StructBssE88* temp_r29;

    var_r31 = &lbl_1_bss_4EE8;
    var_r30 = &lbl_1_bss_2A4[1];
    temp_r29 = &lbl_1_bss_E88[var_r31->unk10];
    var_r31->unk0C = 0;
    fn_1_157BC(var_r30->unk00, 0, 6, 10, 0);
    fn_1_157BC(temp_r29->unk00, 0, 4, 60, 1);
    var_r31->unk14 = var_r31->unk10;
    HuAudSeqFadeOut(lbl_1_bss_4F08[0], 1000);
}

s32 fn_1_FC5C(void) {
    StructBss4EE8* var_r29;
    StructBss2A4* var_r30;
    StructBssC30* var_r26;
    StructBss2A4* var_r28;
    s32 i;

    var_r29 = &lbl_1_bss_4EE8;
    var_r30 = &lbl_1_bss_2A4[1];
    if (fn_1_156AC(var_r30->unk00, 0, 6, 50, 0) != 0) {
        fn_1_19658(var_r30->unk00, 0, 0.0f, 10);
    } else if (fn_1_156AC(var_r30->unk00, 0, 6, 50, 1) != 0) {
        fn_1_19658(var_r30->unk00, 0, 90.0f, 10);
        if (var_r29->unk0C == 0) {
            var_r29->unk0C = 1;
            for (i = 0; i < 4; i++) {
                fn_1_A4B8(i, 1);
            }
            fn_1_3E84(1);
            fn_1_5600(1);
        }
    }
    if (fn_1_15670(&lbl_1_bss_84, 1) != 0) {
        var_r26 = &lbl_1_bss_C30;
        var_r28 = &lbl_1_bss_2A4[1];
        fn_1_19974(&var_r28->unk3C, 1);
        fn_1_198F8(&var_r28->unk3C, -1);
        fn_1_19968(&var_r28->unk3C, -1);
        for (i = 0; i < 3; i++) {
            fn_1_19894(&var_r28->unk3C, var_r26->unk00->model[i + var_r29->unk10 * 3 + 2]);
        }
        fn_1_C5FC(8);
        return fn_1_15520(&lbl_1_bss_84);
    }
    return 0;
}

StructData3A0 lbl_1_data_3A0[] = {
    { fn_1_F1DC, fn_1_F1E0, 300 },
    { fn_1_F36C, fn_1_F3A8,  60 },
    { fn_1_F404, fn_1_F47C,  60 },
    { fn_1_F4D8, fn_1_F534,  45 },
    { fn_1_F57C, fn_1_F5B8,  60 },
    { fn_1_F638, fn_1_F69C,  60 },
    { fn_1_F6F8, fn_1_F768,  45 },
    { fn_1_F7B0, fn_1_F858,  60 },
    { fn_1_F89C, fn_1_F8F8,  60 },
    { fn_1_F954, fn_1_F958,  90 },
    { fn_1_F9A0, fn_1_F9EC,  60 },
    { fn_1_FA48, fn_1_FB50, 180 },
    { fn_1_FBAC, fn_1_FC5C, 180 },
    {      NULL,      NULL,  -1 }
};

void fn_1_FE64(void) {
    fn_1_154C4(&lbl_1_bss_84, lbl_1_data_3A0);
}

s32 fn_1_FE94(void) {
    s32 var_r31;

    var_r31 = 0;
    if (lbl_1_bss_84.unk10 != NULL) {
        lbl_1_bss_84.unk10();
        lbl_1_bss_84.unk10 = NULL;
    }
    if (lbl_1_bss_84.unk14 != NULL) {
        var_r31 = lbl_1_bss_84.unk14();
    }
    return var_r31;
}

s32 fn_1_FF2C(s32 arg0, s32 arg1) {
    s32 var_r31;
    StructBssE88* temp_r30;

    var_r31 = 0;
    temp_r30 = &lbl_1_bss_E88[arg0];
    if (temp_r30->unk2C != 0) {
        switch (temp_r30->unk30) {
            case 0:
                if (arg1 % 60 == 1 && fn_1_5438()) {
                    var_r31 = 1;
                }
                break;
            case 1:
                if (arg1 % 45 == 1 && fn_1_5438()) {
                    var_r31 = 1;
                }
                break;
            case 2:
                if (arg1 % 30 == 1 && fn_1_5438()) {
                    var_r31 = 1;
                }
                break;
            case 3:
                if (arg1 % 15 == 1 && fn_1_5438()) {
                    var_r31 = 1;
                }
                break;
        }
    } else if (HuPadBtnDown[temp_r30->unk38] & 0x100) {
        var_r31 = 1;
    }
    return var_r31;
}

void fn_1_10734(void) {
    StructBss2A4* spC;
    StructBssE08* sp8;

    spC = &lbl_1_bss_2A4[1];
    sp8 = &lbl_1_bss_E08;
}

void fn_1_1075C(void) {
    StructBssE08 sp8;
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    sp8.unk0C = 0.0f;
    sp8.unk10 = 200.0f;
    sp8.unk14 = -550.0f;
    sp8.unk24 = 5.0f;
    sp8.unk28 = 0.0f;
    sp8.unk2C = 0.0f;
    sp8.unk3C = 1300.0f;
    fn_1_169F4(var_r31, &sp8, var_r31->unk44++, 90.0f, 10.0f);
}

void fn_1_10834(void) {
    StructBssE08 sp8;
    StructBssE08* var_r31;

    var_r31 = &lbl_1_bss_E08;
    sp8.unk0C = 0.0f;
    sp8.unk10 = 200.0f;
    sp8.unk14 = -850.0f;
    sp8.unk24 = 5.0f;
    sp8.unk28 = 0.0f;
    sp8.unk2C = 0.0f;
    sp8.unk3C = 1300.0f;
    fn_1_169F4(var_r31, &sp8, var_r31->unk44++, 120.0f, 10.0f);
}

void fn_1_1090C(s32 arg0) {
    StructBssE08* var_r24;

    var_r24 = &lbl_1_bss_E08;
    fn_1_15E50(var_r24);
    switch (arg0) {
        case 0:
            fn_1_8A4(fn_1_C13C);
            break;
        case 1:
            fn_1_8A4(fn_1_C214);
            break;
        case 2:
            fn_1_8A4(fn_1_C2EC);
            break;
        case 3:
            fn_1_8A4(fn_1_C3C4);
            break;
        case 4:
            fn_1_8A4(fn_1_10734);
            break;
        case 5:
            fn_1_8A4(fn_1_1075C);
            break;
        case 6:
            fn_1_8A4(fn_1_10834);
            break;
    }
}

void fn_1_10A14(void) {
    char sp18[8];
    float sp10[] = { 0.0f, 0.0f };
    StructBss4EE8* var_r29;
    StructBssE88* temp_r27;
    s32 sp8;

    var_r29 = &lbl_1_bss_4EE8;
    temp_r27 = &lbl_1_bss_E88[var_r29->unk10];
    lbl_1_bss_4 = 0;
    sprintf(sp18, "%d", var_r29->unk04);
    HuWinInsertMesSizeGet(temp_r27->unk34, 0);
    HuWinInsertMesSizeGet(MAKE_MESSID_PTR(sp18), 1);
    HuWinMesMaxSizeGet(1, sp10, MAKE_MESSID(29, 63));
    sp8 = fn_1_1E80(550.0f - sp10[0], 180.0f, sp10[0], sp10[1], 1);
    HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
    fn_1_A670(var_r29->unk10, var_r29->unk04);
    HuWinInsertMesSet(sp8, MAKE_MESSID_PTR(temp_r27->unk34), 0);
    HuWinInsertMesSet(sp8, MAKE_MESSID_PTR(sp18), 1);
    fn_1_7D28(1, 2);
    fn_1_2798(sp8, MAKE_MESSID(29, 63));
    fn_1_2594(sp8, 120);
    fn_1_7D28(1, 1);
    fn_1_24C4(sp8);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_10E1C(void) {
    float sp14[] = { 0.0f, 0.0f };
    s32 sp1C[][2] = {
        { MAKE_MESSID(29, 60), 9 },
        { MAKE_MESSID(29, 61), 11 }
    };
    StructBss2A4* var_r27;
    s32 sp8;
    s32 i;

    lbl_1_bss_4 = 0;
    for (i = 0; i < 2; i++) {
        if (i == 1) {
            var_r27 = &lbl_1_bss_2A4[1];
            fn_1_19974(&var_r27->unk3C, 0);
            fn_1_198F8(&var_r27->unk3C, -1);
            fn_1_19968(&var_r27->unk3C, -1);
        }
        fn_1_281C(sp14, sp1C[i][0]);
        sp8 = fn_1_1E80(550.0f - sp14[0], 180.0f, sp14[0], sp14[1], 1);
        HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
        fn_1_8544(sp1C[i][1]);
        fn_1_2798(sp8, sp1C[i][0]);
        fn_1_2594(sp8, 120);
        fn_1_24C4(sp8);
    }
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_11220(void) {
    float sp10[] = { 0.0f, 0.0f };
    float temp_f31;
    float temp_f30;
    s32 var_r22;
    s32 sp8;
    s32 i;
    StructBssC1C* var_r27;
    StructBss2A4* var_r28;

    lbl_1_bss_4 = 0;
    fn_1_281C(sp10, MAKE_MESSID(29, 62));
    temp_f31 = 640.0f;
    temp_f30 = (580.0f - sp10[0]) / 2 - 1.0f;
    sp8 = fn_1_1E80(temp_f31, 100.0f, sp10[0], sp10[1], 2);
    fn_1_8544(9);
    var_r27 = &lbl_1_bss_C1C;
    var_r28 = &lbl_1_bss_2A4[1];
    fn_1_19974(&var_r28->unk3C, 1);
    fn_1_198F8(&var_r28->unk3C, -1);
    fn_1_19968(&var_r28->unk3C, -1);
    fn_1_19960(&var_r28->unk3C, var_r27->unk00->model[0]);
    var_r22 = HuAudFXPlay(0x6D6);
    HuAudFXPanning(var_r22, 0x60);
    fn_1_799C(2);
    fn_1_2798(sp8, MAKE_MESSID(29, 62));
    HuPrcSleep(5);
    for (i = 0; i < 120; i++) {
        temp_f31 = fn_1_1539C(640.0f, temp_f30, i, 30.0f);
        HuWinPosSet(sp8, temp_f31, 100.0f);
        HuPrcVSleep();
    }
    HuPrcSleep(60);
    fn_1_799C(1);
    fn_1_24C4(sp8);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_116A8(void) {
    float sp10[] = { 0.0f, 0.0f };
    float temp_f31;
    float temp_f30;
    s32 var_r22;
    s32 sp8;
    s32 i;
    StructBssC1C* var_r27;
    StructBss2A4* var_r28;

    lbl_1_bss_4 = 0;
    fn_1_281C(sp10, MAKE_MESSID(29, 57));
    temp_f31 = 640.0f;
    temp_f30 = (580.0f - sp10[0]) / 2 - 1.0f;
    sp8 = fn_1_1E80(temp_f31, 100.0f, sp10[0], sp10[1], 2);
    var_r27 = &lbl_1_bss_C1C;
    var_r28 = &lbl_1_bss_2A4[1];
    fn_1_19974(&var_r28->unk3C, 1);
    fn_1_198F8(&var_r28->unk3C, -1);
    fn_1_19968(&var_r28->unk3C, -1);
    fn_1_19960(&var_r28->unk3C, var_r27->unk00->model[0]);
    var_r22 = HuAudFXPlay(0x6D2);
    HuAudFXPanning(var_r22, 0x60);
    fn_1_799C(2);
    fn_1_2798(sp8, MAKE_MESSID(29, 57));
    HuPrcSleep(5);
    for (i = 0; i < 120; i++) {
        temp_f31 = fn_1_1539C(640.0f, temp_f30, i, 30.0f);
        HuWinPosSet(sp8, temp_f31, 100.0f);
        HuPrcVSleep();
    }
    fn_1_799C(1);
    fn_1_24C4(sp8);
    lbl_1_bss_4 = 1;
    HuPrcEnd();
}

void fn_1_11B04(void) {
    float sp14[] = { 0.0f, 0.0f };
    s32 sp1C[] = {
        MAKE_MESSID(29, 58),
        MAKE_MESSID(29, 59)
    };
    StructBss2A4* var_r25;
    StructBss2A4* var_r28;
    StructBss9C* var_r24;
    s32 sp8;
    s32 i;

    lbl_1_bss_4 = 0;
    for (i = 0; i < 2; i++) {
        if (i == 1) {
            var_r25 = &lbl_1_bss_2A4[1];
            var_r28 = &lbl_1_bss_2A4[0];
            var_r24 = &lbl_1_bss_9C;
            var_r24->unk00->work[3] = 1;
            fn_1_157BC(var_r28->unk00, 0, 1, 30, 1);
            fn_1_157BC(var_r28->unk00, 1, 6, 30, 1);
            fn_1_157BC(var_r25->unk00, 0, 10, 60, 0);
            lbl_1_bss_4 = 1;
        }
        fn_1_281C(sp14, sp1C[i]);
        sp8 = fn_1_1E80((580.0f - sp14[0]) / 2 - 1.0f, 75.0f, sp14[0], sp14[1], 2);
        HuAudFXPlay(0x6D6);
        if (i == 0) {
            fn_1_799C(2);
        }
        fn_1_2798(sp8, sp1C[i]);
        fn_1_2594(sp8, 60);
        if (i == 0) {
            fn_1_799C(1);
        }
        if (i == 1) {
            fn_1_2594(sp8, 60);
        }
        fn_1_24C4(sp8);
    }
    HuPrcEnd();
}

void fn_1_11F7C(void) {
}

s32 fn_1_11F80(void) {
    if (fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

void fn_1_11FC8(void) {
    StructBss4EE8* var_r31;
    StructBss2A4* var_r30;
    StructBssE88* temp_r29;

    var_r31 = &lbl_1_bss_4EE8;
    var_r30 = &lbl_1_bss_2A4[1];
    temp_r29 = &lbl_1_bss_E88[var_r31->unk10];
    var_r31->unk0C = 0;
    fn_1_157BC(var_r30->unk00, 0, 6, 10, 0);
    fn_1_157BC(temp_r29->unk00, 0, 4, 60, 1);
    var_r31->unk14 = var_r31->unk10;
}

s32 fn_1_12064(void) {
    s32 i;
    StructBss4EE8* var_r29;
    StructBss2A4* var_r30;
    StructBssC30* var_r26;
    StructBss2A4* var_r28;

    var_r29 = &lbl_1_bss_4EE8;
    var_r30 = &lbl_1_bss_2A4[1];
    if (fn_1_156AC(var_r30->unk00, 0, 6, 50, 0) != 0) {
        fn_1_19658(var_r30->unk00, 0, 0.0f, 10);
    } else if (fn_1_156AC(var_r30->unk00, 0, 6, 50, 1) != 0) {
        fn_1_19658(var_r30->unk00, 0, 90.0f, 10);
        if (var_r29->unk0C == 0) {
            var_r29->unk0C = 1;
            fn_1_3E84(1);
            fn_1_5600(1);
        }
    }
    if (fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        var_r26 = &lbl_1_bss_C30;
        var_r28 = &lbl_1_bss_2A4[1];
        fn_1_19974(&var_r28->unk3C, 1);
        fn_1_198F8(&var_r28->unk3C, -1);
        fn_1_19968(&var_r28->unk3C, -1);
        for (i = 0; i < 3; i++) {
            fn_1_19960(&var_r28->unk3C, var_r26->unk00->model[i + var_r29->unk10 * 3 + 2]);
        }
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

void fn_1_12210(void) {
    fn_1_1090C(1);
}

s32 fn_1_12260(void) {
    if (fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

void fn_1_122A8(void) {
    if (lbl_1_bss_10 == 0) {
        lbl_1_bss_10 = 1;
        lbl_1_bss_C = 300;
    }
}

s32 fn_1_122E0(void) {
    s32 var_r30;
    StructBss4EE8* var_r29;

    var_r30 = 0;
    var_r29 = &lbl_1_bss_4EE8;
    fn_1_15670(&lbl_1_bss_6C, 1);
    if (fn_1_15670(&lbl_1_bss_6C, 0) <= 10) {
        return 0;
    }
    if (fn_1_FF2C(var_r29->unk10, fn_1_15670(&lbl_1_bss_6C, 0)) != 0) {
        var_r30 = 1;
        fn_1_28E8();
    }
    if (var_r30 != 0 || fn_1_28C4() != 0) {
        fn_1_5600(4);
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

void fn_1_12414(void) {
    StructBss4EE8* var_r31;

    var_r31 = &lbl_1_bss_4EE8;
    var_r31->unk00 = var_r31->unk04 = var_r31->unk08 = 0;
}

s32 fn_1_12440(void) {
    s32 i;
    s32 j;
    StructBss4EE8* var_r31;
    StructBssC30* var_r28;

    var_r31 = &lbl_1_bss_4EE8;
    var_r28 = &lbl_1_bss_C30;
    if (var_r31->unk00 == 0) {
        for (i = 0; i < 3; i++) {
            if (var_r28->unk2C[i] != 7) {
                break;
            }
        }
        if (i == 3) {
            var_r31->unk00 = 1;
            for (j = 0; j < 3; j++) {
                var_r31->unk04 += var_r28->unk68[j];
            }
        }
    } else if (var_r31->unk00 == 1) {
        if (var_r31->unk04 < 0) {
            var_r31->unk08 = 1;
            fn_1_1561C(&lbl_1_bss_6C, 9);
            fn_1_1090C(3);
        } else if (fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
            return fn_1_15520(&lbl_1_bss_6C);
        }
    }
    return 0;
}

void fn_1_12574(void) {
    StructBss2A4* temp_r31;

    temp_r31 = &lbl_1_bss_2A4[1];
    fn_1_157BC(temp_r31->unk00, 0, 8, 10, 1);
}

s32 fn_1_125BC(void) {
    if (fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

void fn_1_12604(void) {
    StructBss4EE8* var_r30;
    StructBssE88* spC;
    StructBss2A4* var_r29;
    StructBssC30* sp8;
    StructBss2A4* var_r31;

    var_r30 = &lbl_1_bss_4EE8;
    spC = &lbl_1_bss_E88[var_r30->unk10];
    var_r29 = &lbl_1_bss_2A4[1];
    fn_1_157BC(var_r29->unk00, 0, 0, 10, 1);
    HuPrcChildCreate(fn_1_10A14, 100, 0x2000, 0, HuPrcCurrentGet());
    fn_1_1090C(3);
    sp8 = &lbl_1_bss_C30;
    var_r31 = &lbl_1_bss_2A4[1];
    fn_1_19974(&var_r31->unk3C, 0);
    fn_1_198F8(&var_r31->unk3C, -1);
    fn_1_19968(&var_r31->unk3C, -1);
}

s32 fn_1_126F4(void) {
    StructBss4EE8* var_r31;
    StructBssE88* var_r30;

    var_r31 = &lbl_1_bss_4EE8;
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        var_r30 = &lbl_1_bss_E88[var_r31->unk10];
        fn_1_157BC(var_r30->unk00, 0, 0, 1, 1);
        if (var_r31->unk10 == 3) {
            fn_1_1561C(&lbl_1_bss_6C, 11);
        } else {
            return fn_1_15520(&lbl_1_bss_6C);
        }
    }
    return 0;
}

void fn_1_127B4(void) {
    StructBss4EE8* sp8;

    sp8 = &lbl_1_bss_4EE8;
    fn_1_1090C(0);
}

s32 fn_1_12810(void) {
    if (fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

void fn_1_12858(void) {
    StructBss4EE8* var_r28;
    StructBssE88* temp_r31;
    s32 var_r30;
    s32 i;

    var_r28 = &lbl_1_bss_4EE8;
    var_r30 = var_r28->unk10 + 1;
    if (var_r30 >= 4) {
        var_r30 = 0;
    }
    for (i = 0; i < 4; i++) {
        temp_r31 = &lbl_1_bss_E88[var_r30];
        lbl_1_bss_3C[i].x = temp_r31->unk00->trans.x;
        lbl_1_bss_3C[i].y = temp_r31->unk00->trans.y;
        lbl_1_bss_3C[i].z = temp_r31->unk00->trans.z;
        temp_r31->unk14 = 0;
        fn_1_15934(temp_r31->unk00, 0, 2, 10, 1);
        var_r30++;
        if (var_r30 >= 4) {
            var_r30 = 0;
        }
    }
}

s32 fn_1_12958(void) {
    StructBss4EE8* var_r30 = &lbl_1_bss_4EE8;
    StructBssE88* temp_r31;
    s32 var_r28;
    s32 var_r29;
    Vec sp8[] = {
        {   0.0f, 0.0f, 500.0f },
        { 200.0f, 0.0f, 300.0f },
        { 200.0f, 0.0f, 450.0f },
        { 200.0f, 0.0f, 600.0f }
    };

    var_r29 = var_r30->unk10 + 1;
    if (var_r29 >= 4) {
        var_r29 = 0;
    }
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        temp_r31 = &lbl_1_bss_E88[var_r29];
        if (temp_r31->unk14++ <= 30) {
            fn_1_195F4(temp_r31->unk00, 0, &lbl_1_bss_3C[var_r28], &sp8[var_r28], 5, temp_r31->unk14, 30);
        } else {
            fn_1_19658(temp_r31->unk00, 0, -90.0f, 10);
            if (temp_r31->unk14 >= 40) {
                fn_1_15934(temp_r31->unk00, 0, 0, 10, 1);
            }
        }
        var_r29++;
        if (var_r29 == 4) {
            var_r29 = 0;
        }
    }
    if (fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        var_r30->unk10++;
        if (var_r30->unk10 >= 4) {
            var_r30->unk10 = 0;
        }
        fn_1_3E84(0);
        fn_1_5600(0);
        fn_1_1561C(&lbl_1_bss_6C, 0);
    }
    return 0;
}

void fn_1_12B50(void) {
    HuPrcChildCreate(fn_1_10E1C, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_12B8C(void) {
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

void fn_1_12BE8(void) {
    HuPrcChildCreate(fn_1_11220, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_12C24(void) {
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        fn_1_1561C(&lbl_1_bss_6C, 12);
    }
    return 0;
}

void fn_1_12C80(void) {
    HuPrcChildCreate(fn_1_116A8, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_12CBC(void) {
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

void fn_1_12D18(void) {
    StructBss4EE8* var_r28;
    StructBssC1C* sp10;
    StructBss144* temp_r27;
    s32 var_r30;
    s32 i;

    var_r30 = 999;
    var_r28 = &lbl_1_bss_4EE8;
    sp10 = &lbl_1_bss_C1C;
    for (i = 0; i < 4; i++) {
        fn_1_A4B8(i, 0);
    }
    fn_1_8250(1);
    if (var_r28->unk08 != 1) {
        for (i = 0; i < 4; i++) {
            temp_r27 = &lbl_1_bss_144[i];
            if (var_r30 > temp_r27->unk50) {
                var_r30 = temp_r27->unk50;
                var_r28->unk10 = i;
            }
        }
    }
    {
        StructBssE88* temp_r29;
        StructBss2A4* var_r24;
        Vec sp14[] = {
            {    0.0f, 0.0f, -225.0f },
            { -200.0f, 0.0f, -225.0f },
            {  200.0f, 0.0f, -225.0f },
            {  400.0f, 0.0f, -225.0f }
        };

        var_r30 = var_r28->unk10;
        for (i = 0; i < 4; i++) {
            temp_r29 = &lbl_1_bss_E88[var_r30];
            omSetTra(temp_r29->unk00, sp14[i].x, sp14[i].y, sp14[i].z);
            omSetRot(temp_r29->unk00, 0.0f, 180.0f, 0.0f);
            fn_1_157BC(temp_r29->unk00, 0, 0, 10, 1);
            var_r30++;
            if (var_r30 >= 4) {
                var_r30 = 0;
            }
            var_r24 = &lbl_1_bss_2A4[1];
            fn_1_19960(&temp_r29->unk58, var_r24->unk00->model[0]);
        }
    }
    fn_1_1090C(5);

    // Hack required to match.
    if (0) {
        s32 var_r25;
        s32 var_r26;

        (void) var_r26;
        (void) var_r26;
        (void) var_r26;
        (void) var_r26;
        (void) var_r25;
        (void) var_r25;
        (void) var_r25;
        (void) var_r25;
    }
}

// Unused. Mirrors the Vec array defined in fn_1_12D18.
const Vec lbl_1_rodata_48C[] = {
    {    0.0f, 0.0f, -225.0f },
    { -200.0f, 0.0f, -225.0f },
    {  200.0f, 0.0f, -225.0f },
    {  400.0f, 0.0f, -225.0f }
};

static inline void fn_1_12F48_inline_hack(s32 arg0) {
    StructBss4EE8* var_r27;

    var_r27 = &lbl_1_bss_4EE8;
    (void) var_r27;
    (void) var_r27;
    (void) var_r27;
    (void) var_r27;

    if (arg0) {
        s32 var_r31;
        s32 var_r30;
        s32 var_r26;
        s32 var_r23;
        s32 var_r22;
        s32 var_r21;
        s32 var_r20;
        s32 var_r19;
        s32 var_r18;
        s32 var_r17;

        (void) var_r31;
        (void) var_r31;
        (void) var_r31;
        (void) var_r31;
        (void) var_r31;
        (void) var_r31;
        (void) var_r30;
        (void) var_r30;
        (void) var_r30;
        (void) var_r30;
        (void) var_r30;
        (void) var_r30;
        (void) var_r26;
        (void) var_r26;
        (void) var_r26;
        (void) var_r26;
        (void) var_r23;
        (void) var_r23;
        (void) var_r23;
        (void) var_r22;
        (void) var_r22;
        (void) var_r22;
        (void) var_r21;
        (void) var_r21;
        (void) var_r21;
        (void) var_r20;
        (void) var_r20;
        (void) var_r20;
        (void) var_r19;
        (void) var_r19;
        (void) var_r19;
        (void) var_r18;
        (void) var_r18;
        (void) var_r18;
        (void) var_r17;
        (void) var_r17;
        (void) var_r17;
    }
}

s32 fn_1_12F48(void) {
    StructBssC1C* var_r25;
    StructBssC30* var_r24;
    StructBssE88* sp8;
    s32 var_r29;
    s32 var_r28;

    fn_1_12F48_inline_hack(0); // Required to match.
    if (fn_1_15670(&lbl_1_bss_6C, 0) == 180) {
        var_r25 = &lbl_1_bss_C1C;
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            sp8 = &lbl_1_bss_E88[var_r29];
            fn_1_19960(&sp8->unk58, var_r25->unk00->model[0]);
        }
    }
    if (fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        var_r24 = &lbl_1_bss_C30;
        for (var_r28 = 0; var_r28 < 14; var_r28++) {
            Hu3DModelAttrSet(var_r24->unk00->model[var_r28], 1);
        }
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

void fn_1_1303C(void) {
    lbl_1_bss_4 = 0;
    HuPrcChildCreate(fn_1_11B04, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_13088(void) {
    s32 var_r31;
    s32 i;
    StructBss4EE8* var_r28;
    StructBssE88* temp_r29;

    var_r28 = &lbl_1_bss_4EE8;
    var_r31 = var_r28->unk10;
    if (var_r31 == 4) {
        var_r31 = 0;
    }
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_6C, 0) == 20) {
        fn_1_1090C(6);
        for (i = 0; i < 4; i++) {
            if (i != 0) {
                temp_r29 = &lbl_1_bss_E88[var_r31];
                temp_r29->unk0C = i;
                temp_r29->unk1C = 15 - i * 5;
                temp_r29->unk20 = 0;
            }
            var_r31++;
            if (var_r31 >= 4) {
                var_r31 = 0;
            }
        }
    }
    if (lbl_1_bss_4 != 0 && fn_1_15670(&lbl_1_bss_6C, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_6C);
    }
    return 0;
}

StructData3A0 lbl_1_data_468[] = {
    { fn_1_11F7C, fn_1_11F80,   1 },
    { fn_1_11FC8, fn_1_12064, 120 },
    { fn_1_12210, fn_1_12260,  90 },
    { fn_1_122A8, fn_1_122E0, 120 },
    { fn_1_12414, fn_1_12440,  -1 },
    { fn_1_12574, fn_1_125BC, 120 },
    { fn_1_12604, fn_1_126F4,  60 },
    { fn_1_127B4, fn_1_12810,  30 },
    { fn_1_12858, fn_1_12958, 120 },
    { fn_1_12B50, fn_1_12B8C,  60 },
    { fn_1_12BE8, fn_1_12C24,  60 },
    { fn_1_12C80, fn_1_12CBC,  60 },
    { fn_1_12D18, fn_1_12F48, 300 },
    { fn_1_1303C, fn_1_13088,  60 },
    {       NULL,       NULL,  -1 }
};

void fn_1_131B0(void) {
    fn_1_154C4(&lbl_1_bss_6C, lbl_1_data_468);
    fn_1_1561C(&lbl_1_bss_6C, 3);
}

s32 fn_1_131F0(void) {
    s32 var_r31;

    var_r31 = 0;
    if (lbl_1_bss_6C.unk10 != NULL) {
        lbl_1_bss_6C.unk10();
        lbl_1_bss_6C.unk10 = NULL;
    }
    if (lbl_1_bss_6C.unk14 != NULL) {
        var_r31 = lbl_1_bss_6C.unk14();
    }
    return var_r31;
}

void fn_1_13288(void) {
    StructBss4EE8* var_r30;
    StructBssE88* temp_r31;

    var_r30 = &lbl_1_bss_4EE8;
    temp_r31 = &lbl_1_bss_E88[var_r30->unk10];
    var_r30->unk1C = 0;
    lbl_1_data_1E0 = temp_r31->unk00->model[0];
    lbl_1_data_1E4 = temp_r31->unk00->motion[3];
    lbl_1_data_1E8 = temp_r31->unk34;
    HuPrcChildCreate(fn_1_0, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_13338(void) {
    StructBss4EE8* var_r31;
    StructBssE88* temp_r30;

    var_r31 = &lbl_1_bss_4EE8;
    temp_r30 = &lbl_1_bss_E88[var_r31->unk10];
    if (fn_1_15670(&lbl_1_bss_24, 0) == 120) {
        fn_1_157BC(temp_r30->unk00, 0, 3, 30, 0);
        HuAudSStreamPlay(3);
    }
    if (fn_1_15670(&lbl_1_bss_24, 1) != 0) {
        return fn_1_15520(&lbl_1_bss_24);
    }
    return 0;
}

StructData3A0 lbl_1_data_51C[] = {
    { fn_1_13288, fn_1_13338, 360 },
    {       NULL,       NULL,  -1 }
};

void fn_1_133E4(void) {
    fn_1_154C4(&lbl_1_bss_24, lbl_1_data_51C);
}

s32 fn_1_13414(void) {
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

void fn_1_134AC(omObjData* arg0) {
    StructBss4EE8* var_r30;
    StructBssE88* temp_r29;
    s32 i;

    if (WipeStatGet() == 0) {
        CharModelKill(-1);
        MGSeqKillAll();
        HuAudFadeOut(1);
        var_r30 = &lbl_1_bss_4EE8;
        temp_r29 = &lbl_1_bss_E88[var_r30->unk10];
        for (i = 0; i < 4; i++) {
            GWPlayerCoinWinSet(i, 0);
        }
        GWPlayerCoinWinSet(temp_r29->unk24, 1);
        omOvlReturnEx(1, 1);
        arg0->func = NULL;
    }
}

void fn_1_135A0(omObjData* arg0) {
    if (omSysExitReq == 1) {
        HuAudSeqAllFadeOut(250);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
        arg0->func = fn_1_134AC;
    }
}

void fn_1_13600(void) {
    StructBss4EE8* var_r29;
    s32 i;

    fn_1_3288(&lbl_1_bss_DE4);
    fn_1_72A4(&lbl_1_bss_C30);
    fn_1_7A78(&lbl_1_bss_C1C);
    for (i = 0; i < 2; i++) {
        fn_1_8734(&lbl_1_bss_2A4[i]);
    }
    for (i = 0; i < 4; i++) {
        fn_1_9F7C(&lbl_1_bss_E88[i]);
    }
    for (i = 0; i < 4; i++) {
        fn_1_ABFC(&lbl_1_bss_144[i]);
    }
    fn_1_B828(&lbl_1_bss_9C);
    var_r29 = &lbl_1_bss_4EE8;
    var_r29->unk00 = var_r29->unk04 = var_r29->unk08 = var_r29->unk0C = 0;
    var_r29->unk10 = var_r29->unk14 = var_r29->unk18 = var_r29->unk1C = 0;
    fn_1_FE64();
    fn_1_131B0();
    fn_1_133E4();
    fn_1_C5FC(0);
    HuAudFXPlay(0x6D7);
}

void fn_1_14384(omObjData* arg0) {
    StructBssDE4* var_r25;

    switch (lbl_1_bss_1C) {
        case 0:
            fn_1_13600();
            lbl_1_bss_1C = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                lbl_1_bss_1C = 2;
            }
            break;
        case 2:
            if (fn_1_FE94()) {
                lbl_1_bss_1C = 3;
            }
            break;
        case 3:
            lbl_1_bss_20 = MGSeqStartCreate();
            lbl_1_bss_1C = 4;
            lbl_1_bss_4F08[1] = -1;
            break;
        case 4:
            if ((MGSeqStatGet(lbl_1_bss_20) & 0x10) && lbl_1_bss_4F08[1] == -1) {
                lbl_1_bss_4F08[1] = HuAudSeqPlay(0x4D);
            }
            if (MGSeqStatGet(lbl_1_bss_20) == 0) {
                lbl_1_bss_1C = 5;
            }
            break;
        case 5:
            if (fn_1_131F0()) {
                lbl_1_bss_1C = 6;
            }
            break;
        case 6:
            lbl_1_bss_20 = MGSeqFinishCreate();
            lbl_1_bss_1C = 7;
            HuAudSeqPauseAll(0);
            HuAudSeqAllFadeOut(250);
            break;
        case 7:
            if (MGSeqStatGet(lbl_1_bss_20) == 0) {
                lbl_1_bss_1C = 8;
            }
            break;
        case 8:
            var_r25 = &lbl_1_bss_DE4;
            var_r25->unk04 = 999;
            if (fn_1_13414()) {
                lbl_1_bss_1C = 9;
            }
            break;
        case 9:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
            arg0->func = fn_1_134AC;
            break;
    }
    fn_1_135A0(arg0);

    // Hack required to match.
    if (0) {
        s32 var_r31;
        s32 var_r28;

        (void) var_r31;
        (void) var_r31;
        (void) var_r31;
        (void) var_r31;
        (void) var_r28;
        (void) var_r28;
        (void) var_r28;
    }
}

void fn_1_14760(omObjData* arg0) {
    s32 i;

    lbl_1_bss_DE4.unk00 = omAddObjEx(lbl_1_bss_0, 0x200, 16, 16, -1, fn_1_3558);
    lbl_1_bss_C30.unk00 = omAddObjEx(lbl_1_bss_0, 0x300, 32, 32, -1, fn_1_7628);
    lbl_1_bss_C1C.unk00 = omAddObjEx(lbl_1_bss_0, 0x400, 16, 16, -1, fn_1_7B44);
    for (i = 0; i < 2; i++) {
        lbl_1_bss_2A4[i].unk00 = omAddObjEx(lbl_1_bss_0, 0x500, 16, 16, -1, fn_1_88B0);
        lbl_1_bss_2A4[i].unk00->work[0] = i;
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_E88[i].unk00 = omAddObjEx(lbl_1_bss_0, 0x50, 16, 16, -1, fn_1_A148);
        lbl_1_bss_E88[i].unk00->work[0] = i;
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_144[i].unk00 = omAddObjEx(lbl_1_bss_0, 0x800, 16, 16, -1, fn_1_AD5C);
        lbl_1_bss_144[i].unk00->work[0] = i;
    }
    lbl_1_bss_9C.unk00 = omAddObjEx(lbl_1_bss_0, 0x700, 16, 16, -1, fn_1_B950);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    arg0->func = fn_1_14384;
}

#ifdef __MWERKS__
#include "src/REL/executor.c"
#endif

void fn_1_14A54(void) {
    lbl_1_bss_0 = omInitObjMan(62, 0x2000);
    omGameSysInit(lbl_1_bss_0);
    fn_1_1A8();
    fn_1_FDC();
    fn_1_1110();
    fn_1_1818();
    fn_1_2AF0();
    fn_1_8F4C();
    omAddObjEx(lbl_1_bss_0, 0x1000, 0, 0, -1, fn_1_14760);
}

void ObjectSetup(void) {
    fn_1_14A54();
}
