#include "REL/m437Dll.h"
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
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "dolphin.h"
#include "math.h"
#include "string.h"
#include "version.h"

typedef struct {
    /* 0x000 */ omObjData *unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ char unk18[4];
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ s32 unk20;
    /* 0x024 */ s32 unk24;
    /* 0x028 */ s32 unk28;
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ s32 unk30;
    /* 0x034 */ s32 unk34;
    /* 0x038 */ s32 unk38;
    /* 0x03C */ s32 unk3C;
    /* 0x040 */ s32 unk40;
    /* 0x044 */ float unk44;
    /* 0x048 */ float unk48;
    /* 0x04C */ float unk4C;
    /* 0x050 */ StructFn15CD0 unk50;
} StructBss1DC; // Size 0x138

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
} StructBss920; // Size 0x24

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
} StructFn3410; // Size 0x14

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
    /* 0x24 */ float unk24;
} StructBss8D4; // Size 0x28

typedef struct {
    /* 0x000 */ omObjData *unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ s32 unk18;
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ s32 unk20;
    /* 0x024 */ StructFn15CD0 unk24;
} StructBss6BC; // Size 0x10C

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
} StructBss8FC; // Size 0x24

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
    /* 0x24 */ float unk24[7];
    /* 0x40 */ char unk40[4];
    /* 0x44 */ float unk44[7];
    /* 0x60 */ char unk60[4];
    /* 0x64 */ float unk64[7];
    /* 0x80 */ char unk80[4];
    /* 0x84 */ float unk84[7];
    /* 0xA0 */ char unkA0[4];
    /* 0xA4 */ float unkA4[7];
    /* 0xC0 */ char unkC0[4];
    /* 0xC4 */ float unkC4[7];
    /* 0xE0 */ char unkE0[4];
} StructBss68; // Size 0xE4

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} StructBss944; // Size 0x24

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ char unk08[0x38];
} StructBss968; // Size 0x40

void fn_1_0(void);
void fn_1_1A8(void);
void fn_1_230(s32 arg0, s32 arg1, float arg2);
void fn_1_298(s32 arg0, float arg1);
float fn_1_304(s32 arg0);
void fn_1_434(void);
void fn_1_4C0(void);
void fn_1_8A4(void (*arg0)(void));
void fn_1_8C4(void (*arg0)(void));
void fn_1_8E4(omObjData *arg0);
void fn_1_F8C(void);
void fn_1_10C0(void);
void fn_1_1184(s32 arg0);
s32 fn_1_11BC(void);
void fn_1_11E0(void);
void fn_1_1218(omObjData *arg0);
void fn_1_13E8(void);
void fn_1_144C(s32 arg0, float arg1, float arg2, s32 arg3);
void fn_1_1A90(void);
void fn_1_1AB4(s32 arg0, float arg1, float arg2);
s32 fn_1_1F0C(float arg0, float arg1, float arg2, float arg3, s32 arg4);
s32 fn_1_20F8(float arg0, float arg1, float arg2, float arg3, s32 arg4);
void fn_1_22E4(s32 arg0, float arg1, float arg2);
void fn_1_273C(s32 arg0);
void fn_1_27A4(s32 arg0);
void fn_1_280C(s32 arg0, s32 arg1);
void fn_1_28F4(s32 arg0);
void fn_1_2A10(s32 arg0, s32 arg1);
void fn_1_2A94(float *arg0, s32 arg1);
void fn_1_2B04(omObjData *arg0);
void fn_1_2BAC(s32 arg0);
void fn_1_2BBC(omObjData *arg0);
void fn_1_3194(omObjData *arg0);
void fn_1_3260(StructBss920 *arg0);
void fn_1_3410(omObjData *arg0);
float fn_1_3694(void);
float fn_1_36B4(void);
void fn_1_37D4(s32 arg0);
void fn_1_37E8(omObjData *arg0);
s32 fn_1_3990(void);
void fn_1_39C4(float arg0);
void fn_1_39E4(omObjData *arg0);
void fn_1_3B50(void);
void fn_1_3B64(omObjData *arg0);
void fn_1_3CB8(s32 arg0);
void fn_1_3D40(omObjData *arg0);
void fn_1_3F44(omObjData *arg0);
void fn_1_4538(StructBss8FC *arg0);
void fn_1_46C0(omObjData *arg0);
void fn_1_4928(s32 arg0);
void fn_1_4938(omObjData *arg0);
void fn_1_4AF8(s32 arg0);
void fn_1_4BAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_4C40(omObjData *arg0);
void fn_1_4E00(StructBss8D4 *arg0);
void fn_1_4EE0(omObjData *arg0);
void fn_1_5148(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_51DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_5270(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_5304(s32 arg0);
void fn_1_532C(omObjData *arg0);
void fn_1_5658(omObjData *arg0);
void fn_1_5984(StructBss6BC *arg0);
void fn_1_5AD8(omObjData *arg0);
void fn_1_5FBC(void);
void fn_1_610C(s32 arg0, s32 arg1);
void fn_1_6134(omObjData *arg0);
void fn_1_6198(s32 arg0, s32 arg1);
void fn_1_6200(omObjData *arg0);
void fn_1_6580(s32 arg0, s32 arg1, s32 arg2);
void fn_1_65E0(omObjData *arg0);
void fn_1_70F8(s32 arg0, s32 arg1);
void fn_1_7134(omObjData *arg0);
void fn_1_72CC(omObjData *arg0);
void fn_1_74B0(StructBss1DC *arg0);
void fn_1_7678(omObjData *arg0);
void fn_1_79E0(void);
void fn_1_7A14(omObjData *arg0);
void fn_1_82E0(omObjData *arg0);
void fn_1_8308(StructBss68 *arg0);
void fn_1_84C4(omObjData *arg0);
void fn_1_8684(void);
void fn_1_8734(void);
void fn_1_8824(void);
void fn_1_88D4(void);
void fn_1_8984(void);
void fn_1_8A34(void);
void fn_1_8B24(void);
void fn_1_8BD4(void);
void fn_1_8C84(s32 arg0);
void fn_1_8DA4(void);
void fn_1_9320(void);
void fn_1_96D8(void);
void fn_1_9B2C(s32 arg0);
void fn_1_9FA0(void);
void fn_1_A440(void);
void fn_1_A860(void);
s32 fn_1_A864(void);
void fn_1_A9E8(void);
s32 fn_1_AA24(void);
void fn_1_AA80(void);
s32 fn_1_AABC(void);
void fn_1_AB18(void);
s32 fn_1_AB68(void);
void fn_1_ABB0(void);
s32 fn_1_ABEC(void);
void fn_1_AC70(void);
s32 fn_1_ACCC(void);
void fn_1_AD28(void);
s32 fn_1_AD98(void);
void fn_1_ADE0(void);
s32 fn_1_AE1C(void);
void fn_1_AE78(void);
s32 fn_1_AF4C(void);
void fn_1_B194(void);
s32 fn_1_B1C4(void);
float fn_1_B250(void);
void fn_1_B270(void);
s32 fn_1_B3F0(s32 arg0);
float fn_1_B4F4(s32 arg0, s32 arg1);
void fn_1_B7E0(void);
void fn_1_B8D0(void);
void fn_1_BC18(void);
void fn_1_BCC8(void);
void fn_1_BDB8(s32 arg0);
void fn_1_BE80(void);
void fn_1_C248(void);
void fn_1_C610(void);
void fn_1_C9C4(void);
void fn_1_CD20(void);
void fn_1_D03C(void);
void fn_1_D3C0(void);
void fn_1_D754(void);
s32 fn_1_D930(void);
void fn_1_DCEC(void);
s32 fn_1_DEC4(void);
void fn_1_E2A8(void);
s32 fn_1_E598(void);
void fn_1_E634(void);
s32 fn_1_E944(void);
void fn_1_E9A0(void);
s32 fn_1_EAA4(void);
void fn_1_EB38(void);
s32 fn_1_EC10(void);
void fn_1_EDD4(void);
s32 fn_1_EEA0(void);
void fn_1_EFCC(void);
s32 fn_1_F0B8(void);
void fn_1_F0F8(void);
s32 fn_1_F144(void);
void fn_1_F18C(void);
s32 fn_1_F294(void);
void fn_1_F3D8(void);
s32 fn_1_F494(void);
void fn_1_F4D4(void);
s32 fn_1_F504(void);
void fn_1_F590(void);
s32 fn_1_F640(void);
void fn_1_F6EC(void);
s32 fn_1_F71C(void);
void fn_1_F7A8(omObjData *arg0);
s32 fn_1_F89C(void);
void fn_1_F8AC(void);
void fn_1_1043C(omObjData *arg0);
void fn_1_108A4(omObjData *arg0);
void fn_1_10B30(void);

StructBss968 lbl_1_bss_968;
StructBss944 lbl_1_bss_944;
StructBss920 lbl_1_bss_920;
StructBss8FC lbl_1_bss_8FC;
StructBss8D4 lbl_1_bss_8D4;
StructBss6BC lbl_1_bss_6BC[2];
StructBss1DC lbl_1_bss_1DC[4];
StructBss160 lbl_1_bss_160;
float lbl_1_bss_15C;
float lbl_1_bss_158;
float lbl_1_bss_154;
float lbl_1_bss_150;
float lbl_1_bss_14C;
StructBss68 lbl_1_bss_68;
StructBss50 lbl_1_bss_50;
StructBss50 lbl_1_bss_38;
StructBss50 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
float lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
Process *lbl_1_bss_0;

s32 lbl_1_data_0[][5] = { { 91, 105, 126, 141, -1 }, { 91, 105, 126, 141, -1 }, { 124, 137, -1, -1, -1 }, { 85, 100, 127, -1, -1 },
    { 124, 139, -1, -1, -1 }, { 85, 97, 127, 139, -1 }, { 127, 137, -1, -1, -1 }, { 79, 95, 109, 127, -1 } };

s32 lbl_1_data_A0 = -1;
s32 lbl_1_data_A4 = -1;
s32 lbl_1_data_A8 = -1;

void fn_1_0(void)
{
    s32 i;

    while (TRUE) {
        HuPrcVSleep();
        if (lbl_1_data_A0 == -1 || lbl_1_data_A4 == -1 || lbl_1_data_A8 == -1 || lbl_1_data_A4 != Hu3DMotionIDGet(lbl_1_data_A0)) {
            continue;
        }
        for (i = 0; i < 5; i++) {
            if (lbl_1_data_0[lbl_1_data_A8][i] != -1 && Hu3DMotionTimeGet(lbl_1_data_A0) >= lbl_1_data_0[lbl_1_data_A8][i]) {
                OSReport("KE-System  CHR:%d TIME:%d\n", lbl_1_data_A8, lbl_1_data_0[lbl_1_data_A8][i]);
                HuAudFXPlay(0x6D8);
                lbl_1_data_0[lbl_1_data_A8][i] = -1;
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

void fn_1_230(s32 arg0, s32 arg1, float arg2)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk44[arg0] = arg1;
    if (var_r31->unk60[arg0] < 0.0f) {
        var_r31->unk60[arg0] = -arg2;
    }
    else {
        var_r31->unk60[arg0] = arg2;
    }
}

void fn_1_298(s32 arg0, float arg1)
{
    fn_1_230(arg0, -1, arg1);
}

float fn_1_304(s32 arg0)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    if (var_r31->unk60[arg0] != 0.0f) {
        var_r31->unk60[arg0] *= -0.9f;
        if (var_r31->unk44[arg0] == -1) {
            if (var_r31->unk60[arg0] >= -0.5f && var_r31->unk60[arg0] <= 0.5f) {
                var_r31->unk60[arg0] = 0.0f;
            }
        }
        else {
            var_r31->unk44[arg0]--;
            if (var_r31->unk44[arg0] <= 0) {
                var_r31->unk44[arg0] = 0;
                var_r31->unk60[arg0] = 0.0f;
            }
        }
    }
    return var_r31->unk60[arg0];
}

void fn_1_434(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk08 = 0.0f;
    var_r31->unk0C = 225.0f;
    var_r31->unk10 = 1740.0f;
    var_r31->unk20 = -10.0f;
    var_r31->unk24 = 0.0f;
    var_r31->unk28 = 0.0f;
    var_r31->unk38 = 300.0f;
}

void fn_1_4C0(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    if (HuPadBtn[0] & 0x200) {
        if (HuPadBtn[0] & 0x100) {
            var_r31->unk10 -= HuPadStkY[0] / 10.0f;
        }
        else {
            var_r31->unk08 += HuPadStkX[0] / 10.0f;
            var_r31->unk0C += HuPadStkY[0] / 10.0f;
        }
    }
    if (HuPadBtn[0] & 0x800) {
        var_r31->unk20 -= HuPadStkY[0] / 100.0f;
        var_r31->unk24 += HuPadStkX[0] / 100.0f;
        if (var_r31->unk20 < 0.0f) {
            var_r31->unk20 += 360.0f;
        }
        if (var_r31->unk20 >= 360.0f) {
            var_r31->unk20 -= 360.0f;
        }
        if (var_r31->unk24 < 0.0f) {
            var_r31->unk24 += 360.0f;
        }
        if (var_r31->unk24 >= 360.0f) {
            var_r31->unk24 -= 360.0f;
        }
    }
    if (HuPadBtn[0] & 0x400) {
        var_r31->unk38 -= HuPadStkY[0] / 10.0f;
    }
    print8(16, 100, 1.0f, ">>>>>>>>>> CAMERA TEST <<<<<<<<<<");
    print8(16, 110, 1.0f, "CENTER : %.2f, %.2f, %.2f", var_r31->unk08, var_r31->unk0C, var_r31->unk10);
    print8(16, 120, 1.0f, "ROT    : %.2f, %.2f, %.2f", var_r31->unk20, var_r31->unk24, var_r31->unk28);
    print8(16, 130, 1.0f, "ZOOM   : %.2f", var_r31->unk38);
}

void fn_1_8A4(void (*arg0)(void))
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk00 = arg0;
}

void fn_1_8C4(void (*arg0)(void))
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk04 = arg0;
}

void fn_1_8E4(omObjData *arg0)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    if (var_r31->unk00 != NULL) {
        var_r31->unk00();
    }
    Center.x = var_r31->unk08 + fn_1_304(0);
    Center.y = var_r31->unk0C + fn_1_304(1);
    Center.z = var_r31->unk10 + fn_1_304(2);
    CRot.x = var_r31->unk20 + fn_1_304(3);
    CRot.y = var_r31->unk24 + fn_1_304(4);
    CRot.z = var_r31->unk28 + fn_1_304(5);
    CZoom = var_r31->unk38 + fn_1_304(6);
}

void fn_1_F8C(void)
{
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 45.0f, 0.1f, 10000.0f, 1.2f);
    fn_1_8A4(fn_1_434);
    fn_1_8C4(fn_1_4C0);
    omAddObjEx(lbl_1_bss_0, 0x7FDA, 0, 0, -1, omOutView);
    omAddObjEx(lbl_1_bss_0, 0x7FD9, 0, 0, -1, fn_1_8E4);
}

void fn_1_10C0(void)
{
    Vec sp20 = { 0.0f, 3000.0f, 1.0f };
    Vec sp14 = { 0.0f, 0.0f, 0.0f };
    Vec sp8 = { 0.0f, 1.0f, 0.0f };

    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);
}

void fn_1_1184(s32 arg0)
{
    if (lbl_1_bss_8 == 0) {
        lbl_1_bss_8 = 1;
        lbl_1_bss_4 = arg0 * REFRESH_RATE;
    }
}

s32 fn_1_11BC(void)
{
    if (lbl_1_bss_8 == 3) {
        return 1;
    }
    else {
        return 0;
    }
}

void fn_1_11E0(void)
{
    if (lbl_1_bss_8 == 2) {
        lbl_1_bss_8 = 3;
        lbl_1_bss_4 = 30;
    }
}

s32 lbl_1_data_12C = -1;

void fn_1_1218(omObjData *arg0)
{
    switch (lbl_1_bss_8) {
        case 1:
            if (lbl_1_data_12C == -1) {
                lbl_1_data_12C = MGSeqCreate(1, lbl_1_bss_4 / REFRESH_RATE, -1, -1);
            }
            lbl_1_bss_8 = 2;
            break;
        case 2:
            lbl_1_bss_4--;
            if (lbl_1_data_12C != -1) {
                MGSeqParamSet(lbl_1_data_12C, 1, (lbl_1_bss_4 + REFRESH_RATE - 1) / REFRESH_RATE);
            }
            if (lbl_1_bss_4 <= 0) {
                lbl_1_bss_4 = 30;
                lbl_1_bss_8 = 3;
            }
            break;
        case 3:
            if (lbl_1_data_12C != -1) {
                MGSeqParamSet(lbl_1_data_12C, 2, -1);
                lbl_1_data_12C = -1;
            }
            lbl_1_bss_4 = 0;
            lbl_1_bss_8 = 0;
            break;
    }
}

void fn_1_13E8(void)
{
    lbl_1_bss_4 = 0;
    lbl_1_bss_8 = 0;
    omAddObjEx(lbl_1_bss_0, 0x2000, 0, 0, -1, fn_1_1218);
}

// Identical to mgmodedll/main.c::fn_1_245CC
void fn_1_144C(s32 arg0, float arg1, float arg2, s32 arg3)
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
                var_f23 = fn_1_113B0(var_f31, temp_f29, i, 10.0f);
                var_f21 = fn_1_113B0(temp_f27, 1.0f, i, 10.0f);
            }
            else {
                var_f22 = fn_1_113B0(var_f30, temp_f28, i - 10, 5.0f);
                var_f20 = fn_1_113B0(temp_f26, 1.0f, i - 10, 5.0f);
            }
        }
        else {
            if (i <= 10) {
                var_f22 = fn_1_113B0(temp_f28, var_f30, i, 10.0f);
                var_f20 = fn_1_113B0(1.0f, temp_f26, i, 10.0f);
            }
            else {
                var_f23 = fn_1_113B0(temp_f29, var_f31, i - 10, 5.0f);
                var_f21 = fn_1_113B0(1.0f, temp_f27, i - 10, 5.0f);
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

void fn_1_1A90(void)
{
    HuWinInit(1);
}

void fn_1_1AB4(s32 arg0, float arg1, float arg2)
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
        temp_f23 = fn_1_113B0(var_f31, temp_f29, i, 10.0f);
        temp_f21 = fn_1_113B0(temp_f25, 1.0f, i, 10.0f);
        temp_f22 = fn_1_113B0(var_f30, temp_f28, i, 10.0f);
        temp_f20 = fn_1_113B0(temp_f24, 1.0f, i, 10.0f);
        HuWinPosSet(arg0, temp_f23, temp_f22);
        HuWinScaleSet(arg0, temp_f21, temp_f20);
        HuPrcVSleep();
    }
    HuWinPosSet(arg0, temp_f29, temp_f28);
    HuWinScaleSet(arg0, 1.0f, 1.0f);
    HuPrcVSleep();
}

s32 fn_1_1F0C(float arg0, float arg1, float arg2, float arg3, s32 arg4)
{
    s32 var_r31;
    s32 sp18[][6] = { { 0xFF, 0xFF, 0xCC, 0x00, 0x09, 0x09 }, { 0xCC, 0xFF, 0xFF, 0x00, 0x09, 0x09 }, { 0xFF, 0xCC, 0xFF, 0x00, 0x09, 0x09 } };

    var_r31 = HuWinCreate(arg0, arg1, arg2, arg3, 1);
    HuSprColorSet(winData[var_r31].group, 0, sp18[arg4][0], sp18[arg4][1], sp18[arg4][2]);
    winData[var_r31].mess_color = sp18[arg4][3];
    winData[var_r31].mess_shadow_color = sp18[arg4][4];
    winData[var_r31].attr |= 0x80;
    HuWinBGTPLvlSet(var_r31, sp18[arg4][5] / 10.0f);
    winData[var_r31].active_pad = 0;
    fn_1_144C(var_r31, 0.5f, 0.5f, 1);
    return var_r31;
}

s32 fn_1_20F8(float arg0, float arg1, float arg2, float arg3, s32 arg4)
{
    return fn_1_1F0C(arg0, arg1, arg2, arg3, arg4);
}

void fn_1_22E4(s32 arg0, float arg1, float arg2)
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
        temp_f23 = fn_1_11540(temp_f29, var_f31, i, 10.0f);
        temp_f21 = fn_1_11540(1.0f, temp_f25, i, 10.0f);
        temp_f22 = fn_1_11540(temp_f28, var_f30, i, 10.0f);
        temp_f20 = fn_1_11540(1.0f, temp_f24, i, 10.0f);
        HuWinPosSet(arg0, temp_f23, temp_f22);
        HuWinScaleSet(arg0, temp_f21, temp_f20);
        HuPrcVSleep();
    }
    HuWinPosSet(arg0, var_f31, var_f30);
    HuWinScaleSet(arg0, temp_f25, temp_f24);
    HuPrcVSleep();
}

void fn_1_273C(s32 arg0)
{
    HuWinMesSet(arg0, MAKE_MESSID(29, 22));
    HuPrcVSleep();
    fn_1_144C(arg0, 0.5f, 0.5f, 0);
    HuWinKill(arg0);
}

void fn_1_27A4(s32 arg0)
{
    fn_1_273C(arg0);
}

void fn_1_280C(s32 arg0, s32 arg1)
{
    s32 var_r30;
    s32 temp_r28;
    s32 i;

    var_r30 = 0;
    temp_r28 = GWMessDelayGet();
    if (arg1 > 0) {
        HuPrcSleep(arg1);
        return;
    }
    HuWinComKeyReset();
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_1DC[i].unk34 == 0) {
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

void fn_1_28F4(s32 arg0)
{
    s32 var_r31;
    s32 temp_r28;
    s32 i;

    var_r31 = 0;
    temp_r28 = GWMessDelayGet();
    HuWinComKeyReset();
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_1DC[i].unk34 == 0) {
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
        lbl_1_bss_10 = 0;
    }
    else {
        lbl_1_bss_10 = 1;
    }
    HuWinComKeyReset();
}

void fn_1_2A10(s32 arg0, s32 arg1)
{
    winData[arg0].mess_color = 0;
    winData[arg0].mess_shadow_color = 9;
    winData[arg0].attr |= 0x80;
    HuWinMesSet(arg0, arg1);
}

void fn_1_2A94(float *arg0, s32 arg1)
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

void fn_1_2B04(omObjData *arg0)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        Hu3DData[arg0->model[i + 5]].rot.y += 360.0f / (2500.0f + 2500.0f * i);
    }
}

void fn_1_2BAC(s32 arg0)
{
    lbl_1_bss_920.unk04 = arg0;
}

void fn_1_2BBC(omObjData *arg0)
{
    StructBss920 *temp_r30;

    temp_r30 = arg0->data;
    switch (temp_r30->unk04) {
        case 2:
            fn_1_119A0(arg0, 9, 9, 1, 0);
            Hu3DModelAttrReset(arg0->model[9], HU3D_ATTR_DISPOFF);
            temp_r30->unk1C = 0;
            fn_1_230(1, 10, 4.0f);
            HuAudFXPlay(0x6CF);
            /* fallthrough */
        case 1:
            fn_1_119A0(arg0, 0, 0, 1, 0);
            fn_1_119A0(arg0, 3, 3, 1, 0);
            fn_1_119A0(arg0, 4, 4, 1, 0);
            fn_1_119A0(arg0, 5, 5, 1, 0);
            fn_1_119A0(arg0, 6, 6, 1, 0);
            fn_1_119A0(arg0, 7, 7, 1, 0);
            if (temp_r30->unk04 == 1) {
                HuAudFXPlay(0x6CE);
            }
            temp_r30->unk04 = 10;
            break;
        case 3:
            temp_r30->unk04 = 30;
            fn_1_119A0(arg0, 0, 0, 1, 0);
            fn_1_119A0(arg0, 1, 1, 1, 0);
            fn_1_119A0(arg0, 2, 2, 1, 0);
            fn_1_119A0(arg0, 3, 3, 1, 0);
            fn_1_119A0(arg0, 4, 4, 1, 0);
            fn_1_119A0(arg0, 5, 5, 1, 0);
            fn_1_119A0(arg0, 6, 6, 1, 0);
            fn_1_119A0(arg0, 7, 7, 1, 0);
            fn_1_119A0(arg0, 8, 8, 0, 0);
            Hu3DModelAttrReset(arg0->model[8], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(arg0->model[9], HU3D_ATTR_DISPOFF);
            HuAudFXPlay(0x6D0);
            break;
        case 10:
            if (Hu3DMotionEndCheck(arg0->model[3])) {
                temp_r30->unk04 = 0;
                fn_1_119A0(arg0, 3, 13, 1, 1);
                fn_1_119A0(arg0, 4, 14, 1, 1);
                Hu3DModelAttrSet(arg0->model[8], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(arg0->model[9], HU3D_ATTR_DISPOFF);
            }
            break;
        case 30:
            fn_1_230(6, -1, 8.0f);
            if (Hu3DMotionTimeGet(arg0->model[3]) >= 30.0f) {
                temp_r30->unk04 = 10;
                fn_1_230(6, -1, 128.0f);
                HuAudFXPlay(0x6DA);
                omVibrate(lbl_1_bss_1DC[0].unk2C, 12, 12, 0);
                omVibrate(lbl_1_bss_1DC[1].unk2C, 12, 12, 0);
                omVibrate(lbl_1_bss_1DC[2].unk2C, 12, 12, 0);
                omVibrate(lbl_1_bss_1DC[3].unk2C, 12, 12, 0);
                fn_1_37D4(1);
            }
            break;
    }
    if (Hu3DMotionTimeGet(arg0->model[9]) >= 25.0f && temp_r30->unk1C == 0) {
        temp_r30->unk1C = 1;
        fn_1_230(1, 10, 4.0f);
    }
    else if (Hu3DMotionTimeGet(arg0->model[9]) >= 40.0f && temp_r30->unk1C == 1) {
        temp_r30->unk1C = 2;
        fn_1_230(1, 10, 4.0f);
    }
    if (temp_r30->unk04 == 0) {
        if (temp_r30->unk14++ >= 5 * REFRESH_RATE) {
            temp_r30->unk14 = 0;
            if (rand8() % 2 != 0) {
                fn_1_2BAC(1);
            }
        }
    }
}

void fn_1_3194(omObjData *arg0)
{
    fn_1_2B04(arg0);
    fn_1_2BBC(arg0);
}

void fn_1_3260(StructBss920 *arg0)
{
    omObjData *temp_r29 = arg0->unk00;
    s32 sp80[][3] = { { 2, -1, 0 }, { 2, -1, 0 }, { 2, -1, 0 }, { 1, 1, 0 }, { 1, 1, 0 }, { 2, -1, 0 }, { 2, -1, 0 }, { 2, -1, 0 }, { 2, -1, 1 },
        { 2, -1, 1 } };
    Vec sp8[] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -680.0f }, { 0.0f, 0.0f, -680.0f }, { 525.0f, 0.0f, -1150.0f }, { -525.0f, 0.0f, -1150.0f },
        { 0.0f, 150.0f, 50.0f }, { 0.0f, 150.0f, 0.0f }, { 0.0f, 150.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
    s32 i;

    for (i = 0; i < 10; i++) {
        Hu3DModelPosSet(temp_r29->model[i], sp8[i].x, sp8[i].y, sp8[i].z);
        if (sp80[i][2] == 1) {
            Hu3DModelAttrSet(temp_r29->model[i], HU3D_ATTR_DISPOFF);
        }
        if (sp80[i][1] != -1) {
            fn_1_119A0(temp_r29, i, i + 10, 1, sp80[i][1]);
        }
        else {
            fn_1_119A0(temp_r29, i, i, 1, sp80[i][1]);
        }
    }
    temp_r29->work[0] = temp_r29->work[1] = temp_r29->work[2] = temp_r29->work[3] = 0;
    arg0->unk14 = arg0->unk18 = arg0->unk1C = arg0->unk20 = 0;
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
}

void fn_1_3410(omObjData *arg0)
{
    StructFn3410 sp80[] = { { DATA_MAKE_NUM(DATADIR_M437, 36), 2, -1, 1, 0 }, { DATA_MAKE_NUM(DATADIR_M437, 37), 2, -1, 1, 0 },
        { DATA_MAKE_NUM(DATADIR_M437, 38), 2, -1, 2, 0 }, { DATA_MAKE_NUM(DATADIR_M437, 39), 1, DATA_MAKE_NUM(DATADIR_M437, 41), 2, 0 },
        { DATA_MAKE_NUM(DATADIR_M437, 40), 1, DATA_MAKE_NUM(DATADIR_M437, 42), 2, 0 }, { DATA_MAKE_NUM(DATADIR_M437, 33), 2, -1, 0, 0 },
        { DATA_MAKE_NUM(DATADIR_M437, 34), 2, -1, 0, 0 }, { DATA_MAKE_NUM(DATADIR_M437, 35), 2, -1, 0, 0 },
        { DATA_MAKE_NUM(DATADIR_M437, 43), 2, -1, 0, 1 }, { DATA_MAKE_NUM(DATADIR_M437, 44), 2, -1, 0, 1 } };
    Vec sp8[] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -680.0f }, { 0.0f, 0.0f, -680.0f }, { 525.0f, 0.0f, -1150.0f }, { -525.0f, 0.0f, -1150.0f },
        { 0.0f, 150.0f, 50.0f }, { 0.0f, 150.0f, 0.0f }, { 0.0f, 150.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
    s32 i;

    for (i = 0; i < 10; i++) {
        arg0->model[i] = Hu3DModelCreateFile(sp80[i].unk00);
        arg0->motion[i] = Hu3DMotionIDGet(arg0->model[i]);
        if (sp80[i].unk08 != -1) {
            arg0->motion[i + 10] = Hu3DJointMotionFile(arg0->model[i], sp80[i].unk08);
        }
        Hu3DModelPosSet(arg0->model[i], sp8[i].x, sp8[i].y, sp8[i].z);
        if (sp80[i].unk0C == 1) {
            Hu3DModelShadowMapSet(arg0->model[i]);
        }
        else if (sp80[i].unk0C == 2) {
            Hu3DModelShadowSet(arg0->model[i]);
        }
        if (sp80[i].unk10 == 1) {
            Hu3DModelAttrSet(arg0->model[i], HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(arg0->model[i], 1);
        }
        if (sp80[i].unk08 != -1) {
            fn_1_119A0(arg0, i, i + 10, 1, sp80[i].unk04);
        }
        else {
            fn_1_119A0(arg0, i, i, 1, sp80[i].unk04);
        }
    }
    arg0->data = &lbl_1_bss_920;
    arg0->func = fn_1_3194;
}

float fn_1_3694(void)
{
    return lbl_1_bss_150 / lbl_1_bss_154;
}

float fn_1_36B4(void)
{
    float temp_f31;
    StructBss6BC *sp8;

    temp_f31 = lbl_1_bss_150 / lbl_1_bss_154;
    sp8 = &lbl_1_bss_6BC[1];
    if (lbl_1_bss_8D4.unk08 == 0) {
        if (temp_f31 > 0.875f) {
            fn_1_4AF8(3);
            fn_1_5304(3);
            fn_1_5148(3, 5, 0, 0);
            fn_1_5270(5, 10, 2, 1);
        }
        else if (temp_f31 > 0.75f) {
            fn_1_4AF8(2);
            fn_1_5304(2);
        }
        else if (temp_f31 > 0.5f) {
            fn_1_4AF8(1);
            fn_1_5304(1);
        }
        else {
            fn_1_4AF8(0);
            fn_1_5304(0);
        }
    }
    return temp_f31;
}

void fn_1_37D4(s32 arg0)
{
    lbl_1_bss_8FC.unk04 = 1;
}

void fn_1_37E8(omObjData *arg0)
{
    Mtx sp8;
    StructBss8FC *var_r30;

    var_r30 = &lbl_1_bss_8FC;
    switch (var_r30->unk04) {
        case 1:
            var_r30->unk04 = 2;
            Hu3DModelAttrReset(arg0->model[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(arg0->model[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(arg0->model[2], HU3D_ATTR_DISPOFF);
            fn_1_119A0(arg0, 0, 3, 1, 0);
            fn_1_119A0(arg0, 2, 10, 1, 0);
            break;
        case 2:
            if (Hu3DMotionTimeGet(arg0->model[0]) >= 20.0f) {
                arg0->trans.y -= 20.0f;
                if (arg0->trans.y <= 0.0f) {
                    arg0->trans.y = 0.0f;
                    var_r30->unk04 = 3;
                }
            }
            break;
        case 3:
            if (Hu3DMotionEndCheck(arg0->model[0])) {
                var_r30->unk04 = 4;
                Hu3DModelHookReset(arg0->model[2]);
                Hu3DModelObjMtxGet(arg0->model[0], "m437a01-balloon-point", sp8);
                Hu3DModelPosSet(arg0->model[1], sp8[0][3], 0.0f, -250.0f);
            }
            break;
    }
}

s32 fn_1_3990(void)
{
    if (lbl_1_bss_15C <= lbl_1_bss_158) {
        return 1;
    }
    else {
        return 0;
    }
}

void fn_1_39C4(float arg0)
{
    lbl_1_bss_158 += arg0;
}

void fn_1_39E4(omObjData *arg0)
{
    if (lbl_1_bss_15C > lbl_1_bss_158) {
        lbl_1_bss_150 = lbl_1_bss_158 * (lbl_1_bss_154 / lbl_1_bss_15C);
        lbl_1_bss_14C = fn_1_11370(lbl_1_bss_14C, lbl_1_bss_150, 5.0f);
        Hu3DMotionTimeSet(arg0->model[1], lbl_1_bss_14C);
    }
    else {
        lbl_1_bss_158 = lbl_1_bss_15C;
        lbl_1_bss_150 = lbl_1_bss_158 * (lbl_1_bss_154 / lbl_1_bss_15C);
        lbl_1_bss_14C = fn_1_11370(lbl_1_bss_14C, lbl_1_bss_150, 5.0f);
        Hu3DMotionTimeSet(arg0->model[1], lbl_1_bss_14C);
    }
}

void fn_1_3B50(void)
{
    lbl_1_bss_8FC.unk08 = 1;
}

void fn_1_3B64(omObjData *arg0)
{
    Mtx sp8;
    StructBss8FC *var_r30;

    var_r30 = &lbl_1_bss_8FC;
    if (var_r30->unk08 == 1) {
        var_r30->unk08 = 0;
        Hu3DModelAttrReset(arg0->model[3], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF);
        Hu3DModelObjMtxGet(arg0->model[0], "m437a01-balloon-point", sp8);
        Hu3DModelPosSet(arg0->model[3], sp8[0][3], 0.0f, -250.0f);
        fn_1_119A0(arg0, 3, 6, 1, 0);
        omVibrate(lbl_1_bss_1DC[0].unk2C, 12, 12, 0);
        omVibrate(lbl_1_bss_1DC[1].unk2C, 12, 12, 0);
        omVibrate(lbl_1_bss_1DC[2].unk2C, 12, 12, 0);
        omVibrate(lbl_1_bss_1DC[3].unk2C, 12, 12, 0);
        HuAudFXPlay(0x6F4);
        HuAudSeqAllFadeOut(100);
    }
}

void fn_1_3CB8(s32 arg0)
{
    lbl_1_bss_14 += arg0;
    if (lbl_1_bss_14 >= 3.0f) {
        lbl_1_bss_14 = 3.0f;
    }
}

void fn_1_3D40(omObjData *arg0)
{
    float temp_f31;
    StructBss8FC *sp8;
    s32 temp_r31;

    sp8 = &lbl_1_bss_8FC;
    temp_r31 = 100.0f * fn_1_3694();
    temp_f31 = fn_1_11478(0.0f, lbl_1_bss_14, lbl_1_bss_8FC.unk1C++, temp_r31);
    if (lbl_1_bss_8FC.unk1C >= temp_r31) {
        lbl_1_bss_8FC.unk1C = 0;
        lbl_1_bss_14 -= 0.5f;
        if (lbl_1_bss_14 <= 0.0f) {
            lbl_1_bss_14 = 0.0f;
        }
    }
    if (fn_1_3694() >= 0.2f) {
        Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, temp_f31);
    }
}

void fn_1_3F44(omObjData *arg0)
{
    fn_1_37E8(arg0);
    fn_1_39E4(arg0);
    fn_1_3D40(arg0);
    fn_1_3B64(arg0);
}

void fn_1_4538(StructBss8FC *arg0)
{
    omObjData *temp_r31;

    temp_r31 = arg0->unk00;
    omSetTra(temp_r31, 0.0f, 210.0f, -250.0f);
    Hu3DModelAttrSet(temp_r31->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r31->model[1], HU3D_ATTR_DISPOFF);
    lbl_1_bss_150 = 0.0f;
    lbl_1_bss_154 = Hu3DMotionMaxTimeGet(temp_r31->model[1]);
    lbl_1_bss_14C = 0.0f;
    lbl_1_bss_158 = 0.0f;
    lbl_1_bss_15C = rand8() % 7 + 30;
    Hu3DModelAttrSet(temp_r31->model[2], HU3D_ATTR_DISPOFF);
    temp_r31->work[0] = temp_r31->work[1] = temp_r31->work[2] = temp_r31->work[3] = 0;
    arg0->unk14 = arg0->unk18 = arg0->unk1C = arg0->unk20 = 0;
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
}

void fn_1_46C0(omObjData *arg0)
{
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M437, 24));
    arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 28));
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 29));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 30));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 31));
    Hu3DModelShadowMapSet(arg0->model[0]);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M437, 26));
    arg0->motion[5] = Hu3DMotionIDGet(arg0->model[1]);
    Hu3DModelLayerSet(arg0->model[1], 2);
    fn_1_119A0(arg0, 1, 5, 1, 2);
    lbl_1_bss_15C = Hu3DMotionMaxTimeGet(arg0->model[1]);
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M437, 25));
    arg0->motion[10] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 32));
    Hu3DModelShadowMapSet(arg0->model[0]);
    Hu3DModelHookSet(arg0->model[0], "m437a01-balloon-point", arg0->model[2]);
    Hu3DModelHookSet(arg0->model[2], "m437test04-b_point", arg0->model[1]);
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M437, 27));
    arg0->motion[6] = Hu3DMotionIDGet(arg0->model[3]);
    Hu3DModelLayerSet(arg0->model[3], 2);
    Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF);
    arg0->func = fn_1_3F44;
}

void fn_1_4928(s32 arg0)
{
    lbl_1_bss_8D4.unk04 = arg0;
}

void fn_1_4938(omObjData *arg0)
{
    float sp8;
    StructBss8D4 *temp_r31;

    sp8 = 0.0f;
    temp_r31 = arg0->data;
    switch (temp_r31->unk04) {
        case 1:
            temp_r31->unk04 = 2;
            temp_r31->unk14 = temp_r31->unk18 = 0;
            temp_r31->unk24 = 0.0f;
            /* fallthrough */
        case 2:
            temp_r31->unk24 = fn_1_11478(0.0f, 10.0f, temp_r31->unk14, 30.0f);
            if (temp_r31->unk14++ >= 30) {
                temp_r31->unk14 = 0;
                temp_r31->unk18++;
                if (temp_r31->unk18 >= 2) {
                    temp_r31->unk04 = 3;
                }
            }
            break;
        case 3:
            temp_r31->unk24 = fn_1_11370(temp_r31->unk24, 0.0f, 5.0f);
            if (temp_r31->unk14++ >= 15) {
                temp_r31->unk04 = 0;
                temp_r31->unk14 = temp_r31->unk18 = 0;
                temp_r31->unk24 = 0.0f;
                Hu3DMotionNoMotReset(arg0->model[0], "g000m0-ns_ago", 0x200);
            }
            break;
    }
    if (temp_r31->unk04 != 0) {
        Hu3DMotionForceSet(arg0->model[0], "g000m0-ns_ago", 0x200, temp_r31->unk24);
    }
}

void fn_1_4AF8(s32 arg0)
{
    s32 sp8[] = { 4, 5, 6, 7, 8 };

    if (arg0 <= 3) {
        fn_1_11B18(lbl_1_bss_8D4.unk00, 0, sp8[arg0], 120, 1);
    }
    else {
        fn_1_11B18(lbl_1_bss_8D4.unk00, 0, sp8[arg0], 5, 0);
    }
}

void fn_1_4BAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    if (arg3 != 0) {
        fn_1_119A0(lbl_1_bss_8D4.unk00, 0, arg0, arg1, arg2);
    }
    else {
        fn_1_11B18(lbl_1_bss_8D4.unk00, 0, arg0, arg1, arg2);
    }
}

void fn_1_4C40(omObjData *arg0)
{
    fn_1_4938(arg0);
}

void fn_1_4E00(StructBss8D4 *arg0)
{
    omObjData *temp_r30;

    temp_r30 = arg0->unk00;
    omSetTra(temp_r30, 0.0f, 37.0f, -565.0f);
    omSetSca(temp_r30, 1.5f, 1.5f, 1.5f);
    fn_1_119A0(temp_r30, 0, 0, 1, 1);
    temp_r30->work[0] = temp_r30->work[1] = temp_r30->work[2] = temp_r30->work[3] = 0;
    arg0->unk14 = arg0->unk18 = arg0->unk1C = arg0->unk20 = 0;
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
}

void fn_1_4EE0(omObjData *arg0)
{
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M437, 45));
    arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 46));
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 47));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 48));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 49));
    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 50));
    arg0->motion[5] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 51));
    arg0->motion[6] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 52));
    arg0->motion[7] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 53));
    arg0->motion[8] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 54));
    omSetTra(arg0, 0.0f, 37.0f, -565.0f);
    omSetSca(arg0, 1.5f, 1.5f, 1.5f);
    Hu3DModelShadowSet(arg0->model[0]);
    fn_1_119A0(arg0, 0, 0, 1, 1);
    arg0->data = &lbl_1_bss_8D4;
    arg0->func = fn_1_4C40;
}

void fn_1_5148(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    if (arg3 != 0) {
        fn_1_119A0(lbl_1_bss_6BC[0].unk00, 0, arg0, arg1, arg2);
    }
    else {
        fn_1_11B18(lbl_1_bss_6BC[0].unk00, 0, arg0, arg1, arg2);
    }
}

void fn_1_51DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    if (arg3 != 0) {
        fn_1_119A0(lbl_1_bss_6BC[1].unk00, 0, arg0, arg1, arg2);
    }
    else {
        fn_1_11B18(lbl_1_bss_6BC[1].unk00, 0, arg0, arg1, arg2);
    }
}

void fn_1_5270(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    if (arg3 != 0) {
        fn_1_119A0(lbl_1_bss_6BC[0].unk00, 1, arg0, arg1, arg2);
    }
    else {
        fn_1_11B18(lbl_1_bss_6BC[0].unk00, 1, arg0, arg1, arg2);
    }
}

void fn_1_5304(s32 arg0)
{
    StructBss6BC *var_r31;

    var_r31 = &lbl_1_bss_6BC[1];
    var_r31->unk04 = arg0 + 1;
}

void fn_1_532C(omObjData *arg0)
{
    StructBss6BC *temp_r31 = arg0->data;
    Vec sp38[] = { { 480.0f, 0.0f, -1250.0f }, { 400.0f, 37.0f, -850.0f }, { 400.0f, 37.0f, -600.0f }, { 400.0f, 37.0f, -425.0f } };

    if (arg0->work[0] == 0) {
        return;
    }
    if (temp_r31->unk04 == 7) {
        temp_r31->unk08 = temp_r31->unk04;
    }
    if (temp_r31->unk04 != 4 || temp_r31->unk08 <= 4) {
        temp_r31->unk08 = temp_r31->unk04;
    }
    switch (temp_r31->unk08) {
        case 1:
        case 2:
        case 3:
            fn_1_11CE0(arg0, sp38[4 - temp_r31->unk08], 0.0f, 6.0f, 10.0f, 10.0f, 1);
            temp_r31->unk00->trans.x = 400.0f;
            break;
        case 4:
            fn_1_11CE0(arg0, sp38[0], 0.0f, 6.0f, 10.0f, 10.0f, 1);
            temp_r31->unk00->trans.x = 400.0f;
            if (temp_r31->unk18++ >= 60) {
                temp_r31->unk08 = 5;
                temp_r31->unk18 = 0;
            }
            break;
        case 5:
            fn_1_11CE0(arg0, sp38[0], 0.0f, 6.0f, 10.0f, 10.0f, 1);
            if (temp_r31->unk18++ >= 60) {
                temp_r31->unk08 = 6;
                temp_r31->unk18 = 0;
            }
            break;
        case 6:
            fn_1_11B18(arg0, 0, 6, 10, 0);
            break;
        case 7:
            fn_1_11CE0(arg0, sp38[3], -15.0f, 6.0f, 10.0f, 10.0f, 1);
            break;
    }
}

void fn_1_5658(omObjData *arg0)
{
    fn_1_532C(arg0);
}

void fn_1_5984(StructBss6BC *arg0)
{
    s32 var_r29;
    omObjData *temp_r30;

    var_r29 = arg0->unk00->work[0];
    temp_r30 = arg0->unk00;
    if (var_r29 != 0) {
        omSetTra(temp_r30, 400.0f, 37.0f, -425.0f);
        omSetRot(temp_r30, 0.0f, -15.0f, 0.0f);
        fn_1_119A0(temp_r30, 0, 0, 1, 1);
    }
    else {
        omSetTra(temp_r30, -400.0f, 37.0f, -425.0f);
        fn_1_119A0(temp_r30, 0, 0, 1, 1);
        fn_1_119A0(temp_r30, 1, 5, 1, 1);
    }
    temp_r30->work[1] = temp_r30->work[2] = temp_r30->work[3] = 0;
    arg0->unk14 = arg0->unk18 = arg0->unk1C = arg0->unk20 = 0;
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
}

void fn_1_5AD8(omObjData *arg0)
{
    StructBss6BC *temp_r29;
    s32 temp_r30;

    temp_r30 = arg0->work[0];
    temp_r29 = &lbl_1_bss_6BC[temp_r30];
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M437, 57));
    if (temp_r30 != 0) {
        arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 58));
        arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 59));
        arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 63));
        arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 64));
        arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 65));
        arg0->motion[5] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 66));
        arg0->motion[6] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 67));
        arg0->motion[7] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 68));
        arg0->motion[8] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 69));
        arg0->motion[9] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 71));
        omSetTra(arg0, 400.0f, 37.0f, -425.0f);
        omSetRot(arg0, 0.0f, -15.0f, 0.0f);
        fn_1_119A0(arg0, 0, 0, 1, 1);
        fn_1_164B0(lbl_1_bss_0, &temp_r29->unk24, arg0->model[0], "g007m0-skl_at");
        fn_1_15DC8(&temp_r29->unk24);
    }
    else {
        arg0->motion[0] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 60));
        arg0->motion[1] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 61));
        arg0->motion[2] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 62));
        arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 70));
        arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 72));
        omSetTra(arg0, -400.0f, 37.0f, -425.0f);
        fn_1_119A0(arg0, 0, 0, 1, 1);
        arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M437, 73));
        arg0->motion[5] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_M437, 74));
        arg0->motion[6] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_M437, 75));
        Hu3DModelHookSet(arg0->model[0], "g007m0-itemhook_r", arg0->model[1]);
        Hu3DModelLayerSet(arg0->model[0], 2);
        Hu3DModelLayerSet(arg0->model[1], 2);
        fn_1_119A0(arg0, 1, 5, 1, 1);
    }
    Hu3DModelShadowSet(arg0->model[0]);
    arg0->data = &lbl_1_bss_6BC[temp_r30];
    arg0->func = fn_1_5658;
}

void fn_1_5FBC(void)
{
    StructBss1DC *temp_r31;
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
        temp_r31 = &lbl_1_bss_1DC[i];
        temp_r31->unk2C = sp8[i];
        temp_r31->unk30 = GWPlayerCfg[temp_r31->unk2C].group;
        temp_r31->unk34 = GWPlayerCfg[temp_r31->unk2C].iscom;
        temp_r31->unk38 = GWPlayerCfg[temp_r31->unk2C].diff;
        temp_r31->unk3C = GWPlayerCfg[temp_r31->unk2C].character;
        temp_r31->unk40 = GWPlayerCfg[temp_r31->unk2C].pad_idx;
    }
}

void fn_1_610C(s32 arg0, s32 arg1)
{
    StructBss1DC *temp_r31;

    temp_r31 = &lbl_1_bss_1DC[arg0];
    temp_r31->unk04 = arg1;
}

void fn_1_6134(omObjData *arg0)
{
    StructBss1DC *var_r30;

    var_r30 = arg0->data;
    if (var_r30->unk04 != 0) {
        Hu3DModelAttrReset(arg0->model[0], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
    }
}

void fn_1_6198(s32 arg0, s32 arg1)
{
    StructBss1DC *temp_r31;

    temp_r31 = &lbl_1_bss_1DC[arg0];
    temp_r31->unk08 = arg1;
    fn_1_15DC8(&temp_r31->unk50);
    fn_1_11B18(temp_r31->unk00, 0, 2, 10, 0);
}

void fn_1_6200(omObjData *arg0)
{
    StructBss1DC *temp_r30;
    HsfMaterial *var_r31;
    HsfData *temp_r28;
    char **temp_r27;
    s32 var_r23;
    s32 i, j;
    ModelData *temp_r25;
    HsfAttribute *temp_r24;

    temp_r30 = &lbl_1_bss_1DC[arg0->work[0]];
    if (temp_r30->unk08 != 1) {
        return;
    }
    var_r23 = 1;
    temp_r25 = &Hu3DData[arg0->model[0]];
    temp_r28 = temp_r25->hsfData;
    var_r31 = temp_r28->material;
    if (temp_r30->unk3C == 3) {
        for (i = 0; i < temp_r25->hsfData->materialCnt; i++, var_r31++) {
            if (i == 1 || i == 2) {
                continue;
            }
            var_r31->color[0] *= temp_r30->unk44;
            if (var_r31->color[0] == 0) {
                var_r31->color[0] = 0;
            }
            var_r31->color[1] *= temp_r30->unk44;
            if (var_r31->color[1] == 0) {
                var_r31->color[1] = 0;
            }
            var_r31->color[2] *= temp_r30->unk44;
            if (var_r31->color[2] == 0) {
                var_r31->color[2] = 0;
            }
        }
    }
    else {
        temp_r27 = CharModelTexNameGet(temp_r30->unk3C, 2);
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
            var_r31->color[0] *= temp_r30->unk44;
            if (var_r31->color[0] == 0) {
                var_r31->color[0] = 0;
            }
            var_r31->color[1] *= temp_r30->unk44;
            if (var_r31->color[1] == 0) {
                var_r31->color[1] = 0;
            }
            var_r31->color[2] *= temp_r30->unk44;
            if (var_r31->color[2] == 0) {
                var_r31->color[2] = 0;
            }
        }
    }
    temp_r30->unk44 -= 0.01;
    if (temp_r30->unk44 < 0.0f) {
        temp_r30->unk08 = 99;
        temp_r30->unk44 = 0.0f;
    }
}

void fn_1_6580(s32 arg0, s32 arg1, s32 arg2)
{
    StructBss1DC *temp_r31;

    temp_r31 = &lbl_1_bss_1DC[arg0];
    if (temp_r31->unk0C == 0) {
        temp_r31->unk0C = arg1;
        temp_r31->unk10 = arg2;
        temp_r31->unk28 = 0;
    }
    else if (temp_r31->unk0C == 2) {
        temp_r31->unk10 = 0;
        temp_r31->unk28 = 1;
    }
}

float lbl_1_data_188 = -1.0f;

void fn_1_65E0(omObjData *arg0)
{
    Mtx sp60;
    StructBss1DC *temp_r31;
    StructBss1DC *var_r26;
    StructBss1DC *temp_r27;
    StructBss8FC *var_r28;
    StructBss8FC *spC;
    s32 var_r29;

    temp_r31 = arg0->data;
    switch (temp_r31->unk0C) {
        case 1:
            temp_r31->unk0C = 2;
            temp_r31->unk48 = -1.5f;
            lbl_1_data_188 = -1.0f;
            fn_1_119A0(arg0, 0, 5, 15, 0);
            break;
        case 2:
            if (temp_r31->unk48 >= 1.7f) {
                temp_r31->unk48 = 1.7f;
            }
            arg0->trans.y += temp_r31->unk48 * temp_r31->unk48 * (temp_r31->unk48 >= 0.0f ? -25.0f : 25.0f);
            if (temp_r31->unk28 != 0 && arg0->trans.y >= 25.0f + temp_r31->unk4C && temp_r31->unk10 == 0) {
                temp_r31->unk0C = 5;
                temp_r31->unk48 = 0.0f;
                lbl_1_data_188 = arg0->trans.y - temp_r31->unk4C;
                fn_1_11B18(arg0, 0, 7, 15, 0);
                for (var_r29 = 0; var_r29 < 4; var_r29++) {
                    if (var_r29 != arg0->work[0]) {
                        var_r26 = &lbl_1_bss_1DC[var_r29];
                        var_r26->unk00->work[2] = rand8() % 10;
                    }
                }
            }
            if (((!(HuPadBtn[temp_r31->unk40] & 0x100) && temp_r31->unk10 == 0) || temp_r31->unk10 == 2) && temp_r31->unk48 < -0.8f) {
                temp_r31->unk48 = -0.8f;
            }
            if (arg0->trans.y <= temp_r31->unk4C && temp_r31->unk48 > 0.0f) {
                arg0->trans.y = temp_r31->unk4C;
                temp_r31->unk0C = 4;
                temp_r31->unk48 = 0.0f;
                fn_1_11B18(arg0, 0, 6, 5, 0);
            }
            temp_r31->unk48 += 0.09f;
            break;
        case 4:
            if (temp_r31->unk48++ >= 15.0f) {
                temp_r31->unk0C = 0;
                temp_r31->unk28 = 0;
                fn_1_11B18(arg0, 0, 0, 15, 1);
            }
            break;
        case 5:
            if (fn_1_36B4() > 0.75f) {
                for (var_r29 = 0; var_r29 < 4; var_r29++) {
                    if (var_r29 != arg0->work[0]) {
                        temp_r27 = &lbl_1_bss_1DC[var_r29];
                        if (temp_r27->unk00->work[2]-- == 0) {
                            fn_1_11B18(temp_r27->unk00, 0, 11, 5, 0);
                        }
                    }
                }
            }
            if (temp_r31->unk48++ >= 25.0f) {
                temp_r31->unk0C = 6;
            }
            break;
        case 6:
            if (temp_r31->unk48 >= 1.7f) {
                temp_r31->unk48 = 1.7f;
            }
            arg0->trans.y += temp_r31->unk48 * temp_r31->unk48 * (temp_r31->unk48 >= 0.0f ? -17.5f : 17.5f);
            if (arg0->trans.y <= temp_r31->unk4C && temp_r31->unk48 > 0.0f) {
                arg0->trans.y = temp_r31->unk4C;
                temp_r31->unk0C = 7;
                temp_r31->unk48 = 0.0f;
                var_r28 = &lbl_1_bss_8FC;
                if (lbl_1_data_188 <= 135.0f) {
                    fn_1_119A0(var_r28->unk00, 0, 2, 5, 0);
                }
                else if (lbl_1_data_188 <= 245.0f) {
                    fn_1_119A0(var_r28->unk00, 0, 1, 5, 0);
                }
                else {
                    fn_1_119A0(var_r28->unk00, 0, 0, 5, 0);
                }
                HuAudFXPlay(0x6F5);
                omVibrate(temp_r31->unk2C, 12, 6, 6);
                fn_1_11B18(arg0, 0, 8, 15, 0);
            }
            temp_r31->unk48 += 0.1f;
            break;
        case 7:
            if (temp_r31->unk48++ >= 15.0f) {
                spC = &lbl_1_bss_8FC;
                if (lbl_1_data_188 <= 135.0f) {
                    fn_1_39C4(1.0f);
                    fn_1_3CB8(1.0f);
                    HuAudFXPlay(0x6F6);
                }
                else if (lbl_1_data_188 <= 245.0f) {
                    fn_1_39C4(2.0f);
                    fn_1_3CB8(2.0f);
                    HuAudFXPlay(0x6F7);
                }
                else {
                    fn_1_39C4(3.0f);
                    fn_1_3CB8(3.0f);
                    HuAudFXPlay(0x6F8);
                }
                fn_1_11B18(arg0, 0, 9, 15, 0);
                temp_r31->unk48 = 0.0f;
                temp_r31->unk0C = 4;
            }
            break;
    }
    if ((temp_r31->unk0C == 4 || temp_r31->unk0C == 7) && temp_r31->unk10 == 0) {
        StructBss8FC *temp = &lbl_1_bss_8FC;
        Hu3DModelObjMtxGet(temp->unk00->model[0], "m437a01-chara-point", sp60);
        arg0->trans.y = sp60[1][3];
    }
}

void fn_1_70F8(s32 arg0, s32 arg1)
{
    StructBss1DC *temp_r31;

    temp_r31 = &lbl_1_bss_1DC[arg0];
    temp_r31->unk14 = arg1;
    temp_r31->unk24 = 15 - arg1 * 5;
    temp_r31->unk28 = 0;
}

void fn_1_7134(omObjData *arg0)
{
    StructBss1DC *temp_r31 = &lbl_1_bss_1DC[arg0->work[0]];
    Vec sp14[] = { { 0.0f, 0.0f, 0.0f }, { -1000.0f, 0.0f, 800.0f }, { -200.0f, 0.0f, 800.0f }, { 1000.0f, 0.0f, 800.0f } };

    if (temp_r31->unk14 < 1) {
        return;
    }
    if (temp_r31->unk24-- <= 0) {
        fn_1_11B18(arg0, 0, 4, 15, 1);
        temp_r31->unk28 = 1;
    }
    if (temp_r31->unk28 != 0) {
        fn_1_11CE0(arg0, sp14[temp_r31->unk14], -1.0f, temp_r31->unk0C + 7.0f, 30.0f, 5.0f, 0);
    }
}

void fn_1_72CC(omObjData *arg0)
{
    fn_1_6134(arg0);
    fn_1_6200(arg0);
    fn_1_65E0(arg0);
    fn_1_7134(arg0);
}

void fn_1_74B0(StructBss1DC *arg0)
{
    s32 var_r29;
    omObjData *temp_r30;

    var_r29 = arg0->unk00->work[0];
    temp_r30 = arg0->unk00;
    omSetTra(temp_r30, var_r29 * -150 - (rand8() % 100) * 2, 0.0f, (rand8() % 100) * 2 + 250);
    omSetRot(temp_r30, 0.0f, 180.0f, 0.0f);
    fn_1_119A0(temp_r30, 0, 0, 1, 1);
    fn_1_15DC8(&arg0->unk50);
    fn_1_15CD0(&arg0->unk50, lbl_1_bss_8FC.unk00->model[0]);
    arg0->unk44 = 1.0f;
    temp_r30->work[1] = temp_r30->work[2] = temp_r30->work[3] = 0;
    arg0->unk1C = arg0->unk20 = arg0->unk24 = arg0->unk28 = 0;
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
    arg0->unk14 = 0;
}

void fn_1_7678(omObjData *arg0)
{
    StructBss1DC *temp_r30;
    s32 temp_r29;

    temp_r29 = arg0->work[0];
    temp_r30 = &lbl_1_bss_1DC[temp_r29];
    arg0->model[0] = CharModelCreate(temp_r30->unk3C, 2);
    arg0->motion[0] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
    arg0->motion[1] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 3));
    arg0->motion[2] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 28));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, temp_r30->unk3C));
    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[0], DATA_MAKE_NUM(DATADIR_M437, 8 + temp_r30->unk3C));
    arg0->motion[5] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 5));
    arg0->motion[6] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 6));
    arg0->motion[7] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 8));
    arg0->motion[8] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 10));
    arg0->motion[9] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 9));
    arg0->motion[10] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 2));
    arg0->motion[11] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 78));
    arg0->motion[12] = CharModelMotionCreate(temp_r30->unk3C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 27));
    omSetTra(arg0, temp_r29 * -150 + (rand8() % 100) * 5, 0.0f, (rand8() % 100) * 5 + 250);
    omSetRot(arg0, 0.0f, 180.0f, 0.0f);
    Hu3DModelShadowSet(arg0->model[0]);
    fn_1_119A0(arg0, 0, 0, 1, 1);
    CharModelMotionDataClose(temp_r30->unk3C);
    fn_1_1660C(lbl_1_bss_0, &temp_r30->unk50, arg0->model[0], temp_r30->unk3C);
    fn_1_15DC8(&temp_r30->unk50);
    temp_r30->unk04 = 1;
    arg0->data = &lbl_1_bss_1DC[temp_r29];
    arg0->func = fn_1_72CC;
}

void fn_1_79E0(void)
{
    lbl_1_bss_68.unk04 = 1;
    lbl_1_bss_68.unk08 = 1;
    lbl_1_bss_68.unk14 = 0;
}

void fn_1_7A14(omObjData *arg0)
{
    Mtx sp8;
    StructBss68 *temp_r31;
    StructBss8D4 *var_r29;
    StructBss6BC *var_r25;
    s32 var_r24;
    s32 i;

    temp_r31 = arg0->data;
    var_r29 = &lbl_1_bss_8D4;
    switch (temp_r31->unk04) {
        case 1:
            temp_r31->unk04 = 2;
            for (i = 1; i < 7; i++) {
                Hu3DModelPosSet(arg0->model[i], 0.0f, 0.0f, 0.0f);
                Hu3DModelRotSet(arg0->model[i], 0.0f, 0.0f, 0.0f);
                Hu3DModelScaleSet(arg0->model[i], 0.0f, 0.0f, 0.0f);
                temp_r31->unk24[i] = -1.0f + rand8() % 3;
                temp_r31->unk44[i] = 0.0f;
                temp_r31->unk64[i] = -(50.0f * (i - 1));
                temp_r31->unk84[i] = 0.0f;
                temp_r31->unkA4[i] = 0.5f;
                temp_r31->unkC4[i] = 0.0f;
            }
            fn_1_119A0(var_r29->unk00, 0, 3, 10, 0);
            var_r25 = &lbl_1_bss_6BC[0];
            fn_1_119A0(var_r25->unk00, 0, 1, 60, 1);
            fn_1_119A0(var_r25->unk00, 1, 6, 60, 1);
            break;
        case 2:
            if (fn_1_11890(var_r29->unk00, 0, 3, 90, 1) != 0) {
                temp_r31->unk04 = 3;
                Hu3DMotionTimeSet(var_r29->unk00->model[0], 90.0f);
                Hu3DMotionSpeedSet(var_r29->unk00->model[0], 0.0f);
                HuAudCharVoicePlay(lbl_1_bss_1DC[lbl_1_bss_944.unk10].unk3C, 0x123);
                HuAudFXPlay(0x6D5);
                omVibrate(lbl_1_bss_1DC[lbl_1_bss_944.unk10].unk2C, 120, 12, 0);
            }
            break;
        case 3:
            Hu3DModelObjMtxGet(var_r29->unk00->model[0], "g000m0-itemhook_M", sp8);
            var_r24 = lbl_1_bss_944.unk10;
            fn_1_6198(var_r24, 1);
            for (i = 1; i < 7; i++) {
                if (temp_r31->unk08 == 1 || (temp_r31->unk08 == 0 && temp_r31->unk64[i] > 0.0f)) {
                    temp_r31->unk64[i] += 10.0f;
                }
                if (temp_r31->unk64[i] > 0.0f) {
                    temp_r31->unk84[i] += 0.1f;
                    temp_r31->unk24[i] += rand8() % 5 - 2;
                    temp_r31->unk44[i] -= rand8() % 5 - 2 + 2.5f;
                    if (temp_r31->unkC4[i] == 0.0f) {
                        fn_1_119A0(arg0, i, i, 1, 1);
                    }
                    if (temp_r31->unkC4[i] < 8.0f) {
                        temp_r31->unkA4[i] += 0.025f;
                    }
                    else if (temp_r31->unkC4[i] < 23.0f) {
                        temp_r31->unkA4[i] = 0.7f;
                    }
                    else if (temp_r31->unkC4[i] < 31.0f) {
                        temp_r31->unkA4[i] -= 0.1f;
                        if (temp_r31->unkA4[i] < 0.0f) {
                            temp_r31->unkA4[i] = 0.0f;
                        }
                    }
                    temp_r31->unkC4[i] += 1.0f;
                }
                Hu3DModelPosSet(arg0->model[i], sp8[0][3] + temp_r31->unk24[i], sp8[1][3] + temp_r31->unk44[i], sp8[2][3] + temp_r31->unk64[i]);
                Hu3DModelScaleSet(arg0->model[i], 1.5f * temp_r31->unk84[i], 1.5f * temp_r31->unk84[i], 1.5f * temp_r31->unk84[i]);
                Hu3DModelTPLvlSet(arg0->model[i], temp_r31->unkA4[i]);
                if (temp_r31->unkC4[i] >= 31.0f) {
                    temp_r31->unk24[i] = 0.0f;
                    temp_r31->unk44[i] = 0.0f;
                    temp_r31->unk64[i] = 0.0f;
                    temp_r31->unk84[i] = 0.0f;
                    temp_r31->unkA4[i] = 0.5f;
                    temp_r31->unkC4[i] = 0.0f;
                }
            }
            if (temp_r31->unk14++ == 120) {
                temp_r31->unk08 = 0;
                Hu3DMotionSpeedSet(var_r29->unk00->model[0], 1.0f);
            }
            else if (temp_r31->unk14 >= 180) {
                temp_r31->unk04 = 4;
            }
            break;
        case 4:
            temp_r31->unk04 = 0;
            fn_1_119A0(var_r29->unk00, 0, 0, 30, 1);
            break;
    }
    if (temp_r31->unk14 >= 10 && temp_r31->unk14 <= 120) {
        fn_1_298(6, 8.0f);
    }
}

void fn_1_82E0(omObjData *arg0)
{
    fn_1_7A14(arg0);
}

void fn_1_8308(StructBss68 *arg0)
{
    omObjData *temp_r29;
    s32 i;

    temp_r29 = arg0->unk00;
    for (i = 1; i < 7; i++) {
        Hu3DModelPosSet(temp_r29->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r29->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(temp_r29->model[i], 0.0f, 0.0f, 0.0f);
        fn_1_119A0(temp_r29, i, i, 1, 2);
        arg0->unk24[i] = 0.0f;
        arg0->unk44[i] = 0.0f;
        arg0->unk64[i] = 0.0f;
        arg0->unk84[i] = 0.0f;
        arg0->unkA4[i] = 0.0f;
        arg0->unkC4[i] = 0.0f;
    }
    arg0->unk04 = arg0->unk08 = arg0->unk0C = arg0->unk10 = 0;
    arg0->unk14 = arg0->unk18 = arg0->unk1C = arg0->unk20 = 0;
}

void fn_1_84C4(omObjData *arg0)
{
    s32 i;

    for (i = 1; i < 7; i++) {
        if (i % 2 == 0) {
            arg0->model[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M437, 55));
            arg0->motion[i] = Hu3DMotionIDGet(arg0->model[i]);
        }
        else {
            arg0->model[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M437, 56));
            arg0->motion[i] = Hu3DMotionIDGet(arg0->model[i]);
        }
        Hu3DModelPosSet(arg0->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(arg0->model[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(arg0->model[i], 0.0f, 0.0f, 0.0f);
        fn_1_119A0(arg0, i, i, 1, 2);
        Hu3DModelLayerSet(arg0->model[i], 2);
    }
    arg0->data = &lbl_1_bss_68;
    arg0->func = fn_1_82E0;
}

void fn_1_8684(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = 300.0f;
    var_r31->unk1C = 1740.0f;
    var_r31->unk2C = -10.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk3C = 300.0f;
    fn_1_12E14(var_r31, 200.0f);
}

void fn_1_8734(void)
{
    StructBss160 *var_r31;
    StructBss160 sp8;

    var_r31 = &lbl_1_bss_160;
    sp8.unk08 = 0.0f;
    sp8.unk0C = 200.0f;
    sp8.unk10 = -50.0f;
    sp8.unk20 = 5.0f;
    sp8.unk24 = 0.0f;
    sp8.unk28 = 0.0f;
    sp8.unk38 = 200.0f;
    fn_1_15544(var_r31, &sp8, var_r31->unk40++, 30.0f, 5.0f);
}

void fn_1_8824(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = 200.0f;
    var_r31->unk1C = -50.0f;
    var_r31->unk2C = 5.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk3C = 200.0f;
    fn_1_12E14(var_r31, 200.0f);
}

void fn_1_88D4(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = 300.0f;
    var_r31->unk1C = -550.0f;
    var_r31->unk2C = -15.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk3C = 1200.0f;
    fn_1_12E14(var_r31, 45.0f);
}

void fn_1_8984(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = 150.0f;
    var_r31->unk1C = -550.0f;
    var_r31->unk2C = -15.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk3C = 1200.0f;
    fn_1_12E14(var_r31, 30.0f);
}

void fn_1_8A34(void)
{
    StructBss160 *var_r31;
    StructBss160 sp8;

    var_r31 = &lbl_1_bss_160;
    sp8.unk08 = 0.0f;
    sp8.unk0C = 300.0f;
    sp8.unk10 = 0.0f;
    sp8.unk20 = 0.0f;
    sp8.unk24 = 0.0f;
    sp8.unk28 = 0.0f;
    sp8.unk38 = 1200.0f;
    fn_1_13658(var_r31, &sp8, var_r31->unk40++, 30.0f, 10.0f);
}

void fn_1_8B24(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = 150.0f;
    var_r31->unk1C = -550.0f;
    var_r31->unk2C = -15.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk3C = 1200.0f;
    fn_1_12E14(var_r31, 20.0f);
}

void fn_1_8BD4(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = 300.0f;
    var_r31->unk1C = -550.0f;
    var_r31->unk2C = -15.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk3C = 1200.0f;
    fn_1_12E14(var_r31, 20.0f);
}

void fn_1_8C84(s32 arg0)
{
    StructBss160 *var_r23;

    var_r23 = &lbl_1_bss_160;
    fn_1_12ABC(var_r23);
    switch (arg0) {
        case 0:
            fn_1_8A4(fn_1_8684);
            break;
        case 1:
            fn_1_8A4(fn_1_8734);
            break;
        case 2:
            fn_1_8A4(fn_1_8824);
            break;
        case 3:
            fn_1_8A4(fn_1_88D4);
            break;
        case 4:
            fn_1_8A4(fn_1_8984);
            break;
        case 5:
            fn_1_8A4(fn_1_8A34);
            break;
        case 10:
            fn_1_8A4(fn_1_8B24);
            break;
        case 11:
            fn_1_8A4(fn_1_8BD4);
            break;
    }
}

void fn_1_8DA4(void)
{
    float sp18[] = { 0.0f, 0.0f };
    s32 var_r31;

    lbl_1_bss_C = 0;
    fn_1_2A94(sp18, MAKE_MESSID(29, 0));
    fn_1_2A94(sp18, MAKE_MESSID(29, 1));
    var_r31 = fn_1_20F8((580.0f - sp18[0]) / 2, 80.0f, sp18[0], sp18[1], 2);
    HuAudFXPlay(0x6D1);
    fn_1_4BAC(1, 10, 0, 1);
    fn_1_2A10(var_r31, MAKE_MESSID(29, 0));
    fn_1_280C(var_r31, 0);
    fn_1_4BAC(1, 10, 0, 1);
    fn_1_2A10(var_r31, MAKE_MESSID(29, 1));
    fn_1_280C(var_r31, 0);
    fn_1_4BAC(0, 10, 1, 1);
    fn_1_27A4(var_r31);
    lbl_1_bss_C = 1;
    HuPrcEnd();
}

void fn_1_9320(void)
{
    float sp10[] = { 0.0f, 0.0f };
    s32 var_r31;

    lbl_1_bss_C = 0;
    fn_1_2A94(sp10, MAKE_MESSID(29, 4));
    var_r31 = fn_1_20F8((580.0f - sp10[0]) / 2, 100.0f, sp10[0], sp10[1], 2);
    HuAudFXPlay(0x6D2);
    fn_1_4BAC(2, 10, 0, 1);
    fn_1_2A10(var_r31, MAKE_MESSID(29, 4));
    fn_1_280C(var_r31, REFRESH_RATE);
    fn_1_2BAC(3);
    fn_1_280C(var_r31, REFRESH_RATE);
    fn_1_4BAC(0, 30, 1, 1);
    fn_1_27A4(var_r31);
    lbl_1_bss_C = 1;
    HuPrcEnd();
}

void fn_1_96D8(void)
{
    float sp10[] = { 0.0f, 0.0f };
    s32 var_r31;

    lbl_1_bss_C = 0;
    fn_1_2A94(sp10, MAKE_MESSID(29, 64));
    var_r31 = fn_1_20F8(550.0f - sp10[0], 340.0f, sp10[0], sp10[1], 1);
    HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
    fn_1_51DC(4, 10, 0, 1);
    fn_1_2A10(var_r31, MAKE_MESSID(29, 64));
    fn_1_28F4(var_r31);
    fn_1_51DC(0, 10, 1, 1);
    fn_1_27A4(var_r31);
    lbl_1_bss_C = 1;
    HuPrcEnd();
}

void fn_1_9B2C(s32 arg0)
{
    float sp10[2] = { 0.0f, 0.0f };
    s32 sp18[] = { MAKE_MESSID(29, 6), MAKE_MESSID(29, 66), MAKE_MESSID(29, 68), MAKE_MESSID(29, 70), MAKE_MESSID(29, 72), MAKE_MESSID(29, 74),
        MAKE_MESSID(29, 76), -1 };
    s32 var_r31;

    if (sp18[arg0] == -1) {
        return;
    }
    fn_1_2A94(sp10, sp18[arg0]);
    var_r31 = fn_1_20F8(20.0f, 360.0f, sp10[0], sp10[1], 0);
    HuAudFXPlayVolPan(0x3E, 0x7F, 0x20);
    fn_1_5148(2, 10, 0, 1);
    fn_1_5270(5, 10, 2, 1);
    fn_1_2A10(var_r31, sp18[arg0]);
    fn_1_280C(var_r31, 0);
    fn_1_5148(0, 10, 1, 1);
    fn_1_5270(5, 10, 1, 1);
    fn_1_27A4(var_r31);
}

void fn_1_9FA0(void)
{
    float sp10[2] = { 0.0f, 0.0f };
    s32 sp18[] = { MAKE_MESSID(29, 5), MAKE_MESSID(29, 65), MAKE_MESSID(29, 67), MAKE_MESSID(29, 69), MAKE_MESSID(29, 71), MAKE_MESSID(29, 73),
        MAKE_MESSID(29, 75), MAKE_MESSID(29, 77) };
    s32 i;
    s32 var_r30;

    lbl_1_bss_C = 0;
    for (i = 0; i < 8; i++) {
        fn_1_2A94(sp10, sp18[i]);
    }
    var_r30 = fn_1_20F8(550.0f - sp10[0], 340.0f, sp10[0], sp10[1], 1);
    HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
    for (i = 0; i < 8; i++) {
        fn_1_51DC(4, 10, 0, 1);
        fn_1_2A10(var_r30, sp18[i]);
        fn_1_280C(var_r30, 0);
        fn_1_51DC(0, 10, 1, 1);
        fn_1_9B2C(i);
    }
    fn_1_27A4(var_r30);
    lbl_1_bss_C = 1;
    HuPrcEnd();
}

void fn_1_A440(void)
{
    float sp10[] = { 0.0f, 0.0f };
    s32 var_r31;

    lbl_1_bss_C = 0;
    fn_1_2A94(sp10, MAKE_MESSID(29, 78));
    var_r31 = fn_1_20F8((580.0f - sp10[0]) / 2, 80.0f, sp10[0], sp10[1], 2);
    HuAudFXPlay(0x6D2);
    fn_1_4BAC(1, 10, 0, 1);
    fn_1_2A10(var_r31, MAKE_MESSID(29, 78));
    fn_1_280C(var_r31, 0);
    fn_1_4BAC(0, 10, 1, 1);
    fn_1_27A4(var_r31);
    lbl_1_bss_C = 1;
    HuPrcEnd();
}

void fn_1_A860(void) { }

s32 fn_1_A864(void)
{
    if (fn_1_11854(&lbl_1_bss_50, 0) == 80) {
        fn_1_8C84(1);
        lbl_1_bss_968.unk00 = HuAudSeqPlay(6);
    }
    if (fn_1_11854(&lbl_1_bss_50, 0) == 115) {
        fn_1_8C84(2);
    }
    if (fn_1_11854(&lbl_1_bss_50, 0) == 180) {
        fn_1_8C84(3);
    }
    if (fn_1_11854(&lbl_1_bss_50, 0) == 0) {
        fn_1_2BAC(2);
    }
    if (fn_1_11854(&lbl_1_bss_50, 0) == 150) {
        fn_1_2BAC(1);
    }
    if (fn_1_11854(&lbl_1_bss_50, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_50);
    }
    return 0;
}

void fn_1_A9E8(void)
{
    HuPrcChildCreate(fn_1_8DA4, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_AA24(void)
{
    if (lbl_1_bss_C != 0 && fn_1_11854(&lbl_1_bss_50, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_50);
    }
    return 0;
}

void fn_1_AA80(void)
{
    HuPrcChildCreate(fn_1_9320, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_AABC(void)
{
    if (lbl_1_bss_C != 0 && fn_1_11854(&lbl_1_bss_50, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_50);
    }
    return 0;
}

void fn_1_AB18(void)
{
    fn_1_8C84(10);
}

s32 fn_1_AB68(void)
{
    if (fn_1_11854(&lbl_1_bss_50, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_50);
    }
    return 0;
}

void fn_1_ABB0(void)
{
    HuPrcChildCreate(fn_1_96D8, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_ABEC(void)
{
    if (lbl_1_bss_C != 0 && fn_1_11854(&lbl_1_bss_50, 1) != 0) {
        if (lbl_1_bss_10 != 0) {
            return fn_1_116C4(&lbl_1_bss_50);
        }
        else {
            return fn_1_117C0(&lbl_1_bss_50, 6);
        }
    }
    return 0;
}

void fn_1_AC70(void)
{
    fn_1_4BAC(4, 60, 1, 1);
    HuPrcChildCreate(fn_1_9FA0, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_ACCC(void)
{
    if (lbl_1_bss_C != 0 && fn_1_11854(&lbl_1_bss_50, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_50);
    }
    return 0;
}

void fn_1_AD28(void)
{
    fn_1_8C84(11);
    fn_1_4BAC(0, 60, 1, 0);
}

s32 fn_1_AD98(void)
{
    if (fn_1_11854(&lbl_1_bss_50, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_50);
    }
    return 0;
}

void fn_1_ADE0(void)
{
    HuPrcChildCreate(fn_1_A440, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_AE1C(void)
{
    if (lbl_1_bss_C != 0 && fn_1_11854(&lbl_1_bss_50, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_50);
    }
    return 0;
}

void fn_1_AE78(void)
{
    StructBss6BC *var_r30;
    StructBss1DC *sp8;
    StructBss8FC *var_r29;
    s32 i;

    fn_1_8C84(5);
    for (i = 0; i < 4; i++) {
        fn_1_610C(i, 1);
    }
    var_r30 = &lbl_1_bss_6BC[1];
    sp8 = &lbl_1_bss_1DC[i];
    var_r29 = &lbl_1_bss_8FC;
    fn_1_15DC8(&var_r30->unk24);
    fn_1_15CD0(&var_r30->unk24, var_r29->unk00->model[2]);
    HuAudSeqFadeOut(lbl_1_bss_968.unk00, 1000);
}

s32 fn_1_AF4C(void)
{
    Vec sp20[] = { { -200.0f, 0.0f, -250.0f }, { -340.0f, 0.0f, -250.0f }, { -490.0f, 0.0f, -250.0f }, { -640.0f, 0.0f, -250.0f } };
    s32 i;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_1DC[i].unk3C == 7) {
            fn_1_11CE0(lbl_1_bss_1DC[i].unk00, sp20[i], 90.0f, 9.0f, 30.0f, 15.0f, 3);
        }
        else {
            fn_1_11CE0(lbl_1_bss_1DC[i].unk00, sp20[i], 90.0f, 9.0f, 30.0f, 15.0f, 1);
        }
    }
    if (fn_1_11854(&lbl_1_bss_50, 1) != 0) {
        fn_1_4BAC(4, 60, 1, 1);
        for (i = 0; i < 4; i++) {
            fn_1_11B18(lbl_1_bss_1DC[i].unk00, 0, 0, 10, 1);
        }
        return fn_1_116C4(&lbl_1_bss_50);
    }
    return 0;
}

StructData204 lbl_1_data_204[] = { { fn_1_A860, fn_1_A864, 300 }, { fn_1_A9E8, fn_1_AA24, 60 }, { fn_1_AA80, fn_1_AABC, 60 },
    { fn_1_AB18, fn_1_AB68, 45 }, { fn_1_ABB0, fn_1_ABEC, 60 }, { fn_1_AC70, fn_1_ACCC, 60 }, { fn_1_AD28, fn_1_AD98, 45 },
    { fn_1_ADE0, fn_1_AE1C, 60 }, { fn_1_AE78, fn_1_AF4C, 120 }, { NULL, NULL, -1 } };

void fn_1_B194(void)
{
    fn_1_11668(&lbl_1_bss_50, lbl_1_data_204);
}

s32 fn_1_B1C4(void)
{
    if (lbl_1_bss_50.unk08 != NULL) {
        lbl_1_bss_50.unk08();
        lbl_1_bss_50.unk08 = NULL;
    }
    if (lbl_1_bss_50.unk0C != NULL) {
        return lbl_1_bss_50.unk0C();
    }
    return 0;
}

float fn_1_B250(void)
{
    return lbl_1_bss_15C - lbl_1_bss_158;
}

void fn_1_B270(void)
{
    StructBss944 *var_r30;
    StructBss1DC *temp_r31;

    var_r30 = &lbl_1_bss_944;
    temp_r31 = &lbl_1_bss_1DC[var_r30->unk10];
    if (fn_1_B250() <= 3.0f) {
        temp_r31->unk00->work[1] = fn_1_B250() - 1.0f;
        if (temp_r31->unk00->work[1] == 0) {
            temp_r31->unk00->work[1] = rand8() % 3 + 1;
        }
    }
    else {
        temp_r31->unk00->work[1] = rand8() % 3 + 1;
    }
    temp_r31->unk00->work[2] = 0;
    temp_r31->unk00->work[3] = rand8() % 60 + 60;
}

s32 fn_1_B3F0(s32 arg0)
{
    StructBss944 *var_r30;
    StructBss1DC *temp_r31;
    float temp_f31;

    var_r30 = &lbl_1_bss_944;
    temp_r31 = &lbl_1_bss_1DC[var_r30->unk10];
    temp_f31 = temp_r31->unk00->trans.y - temp_r31->unk4C;
    switch (arg0) {
        case 1:
            if (temp_f31 > 80.0f && temp_f31 <= 135.0f) {
                return 1;
            }
            break;
        case 2:
            if (temp_f31 > 190.0f && temp_f31 <= 245.0f) {
                return 1;
            }
            break;
        case 3:
            if (temp_f31 > 300.0f) {
                return 1;
            }
            break;
    }
    return 0;
}

float fn_1_B4F4(s32 arg0, s32 arg1)
{
    StructBss1DC *temp_r31;

    temp_r31 = &lbl_1_bss_1DC[arg0];
    if (temp_r31->unk34 != 0) {
        if (arg1 > temp_r31->unk00->work[3]) {
            if (temp_r31->unk00->work[2] == 0) {
                temp_r31->unk00->work[2] = 1;
                fn_1_6580(arg0, 1, 1);
            }
            else if (fn_1_B3F0(temp_r31->unk00->work[1]) != 0) {
                fn_1_6580(arg0, 1, 0);
            }
        }
    }
    else if ((HuPadBtnDown[temp_r31->unk40] & 0x100) || ((HuPadBtnDown[temp_r31->unk40] & 0x40) && temp_r31->unk0C == 2)) {
        fn_1_6580(arg0, 1, 0);
    }
    return temp_r31->unk0C;
}

void fn_1_B7E0(void)
{
    StructBss160 *var_r31;
    StructBss160 sp8;

    var_r31 = &lbl_1_bss_160;
    sp8.unk08 = 0.0f;
    sp8.unk0C = 300.0f;
    sp8.unk10 = 0.0f;
    sp8.unk20 = 0.0f;
    sp8.unk24 = 0.0f;
    sp8.unk28 = 0.0f;
    sp8.unk38 = 1200.0f;
    fn_1_13658(var_r31, &sp8, var_r31->unk40++, 30.0f, 10.0f);
}

void fn_1_B8D0(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = 300.0f;
    var_r31->unk1C = -350.0f + 450.0f * fn_1_36B4();
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk3C = 1200.0f;
    fn_1_12E14(var_r31, 10.0f);
}

void fn_1_BC18(void)
{
    StructBss160 *var_r31;

    var_r31 = &lbl_1_bss_160;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = 300.0f;
    var_r31->unk1C = -50.0f;
    var_r31->unk2C = -15.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk3C = 1200.0f;
    fn_1_12E14(var_r31, 5.0f);
}

void fn_1_BCC8(void)
{
    StructBss160 *var_r31;
    StructBss160 sp8;

    var_r31 = &lbl_1_bss_160;
    sp8.unk08 = 0.0f;
    sp8.unk0C = 225.0f;
    sp8.unk10 = -800.0f;
    sp8.unk20 = 0.0f;
    sp8.unk24 = 0.0f;
    sp8.unk28 = 0.0f;
    sp8.unk38 = 1200.0f;
    fn_1_15544(var_r31, &sp8, var_r31->unk40++, 30.0f, 10.0f);
}

void fn_1_BDB8(s32 arg0)
{
    StructBss160 *var_r27;

    var_r27 = &lbl_1_bss_160;
    fn_1_12ABC(var_r27);
    switch (arg0) {
        case 0:
            fn_1_8A4(fn_1_B7E0);
            break;
        case 1:
            fn_1_8A4(fn_1_B8D0);
            break;
        case 2:
            fn_1_8A4(fn_1_BC18);
            break;
        case 3:
            fn_1_8A4(fn_1_BCC8);
            break;
    }
}

void fn_1_BE80(void)
{
    s32 sp1C[] = { MAKE_MESSID(29, 79), MAKE_MESSID(29, 80), MAKE_MESSID(29, 81), MAKE_MESSID(29, 82) };
    float sp14[2] = { 0.0f, 0.0f };
    s32 temp_r27;
    s32 var_r30;

    temp_r27 = rand8() % 4;
    lbl_1_bss_C = 0;
    fn_1_2A94(sp14, sp1C[temp_r27]);
    var_r30 = fn_1_20F8((580.0f - sp14[0]) / 2, 100.0f, sp14[0], sp14[1], 2);
    HuAudFXPlay(0x6D2);
    fn_1_4928(1);
    fn_1_2A10(var_r30, sp1C[temp_r27]);
    fn_1_280C(var_r30, REFRESH_RATE);
    lbl_1_bss_C = 1;
    fn_1_280C(var_r30, REFRESH_RATE);
    fn_1_27A4(var_r30);
    HuPrcEnd();
}

void fn_1_C248(void)
{
    s32 sp1C[] = { MAKE_MESSID(29, 83), MAKE_MESSID(29, 84), MAKE_MESSID(29, 85) };
    float sp14[2] = { 0.0f, 0.0f };
    s32 temp_r27;
    s32 var_r31;

    temp_r27 = rand8() % 3;
    lbl_1_bss_C = 0;
    fn_1_2A94(sp14, sp1C[temp_r27]);
    var_r31 = fn_1_20F8((580.0f - sp14[0]) / 2, 100.0f, sp14[0], sp14[1], 2);
    HuAudFXPlay(0x6D2);
    fn_1_4928(1);
    fn_1_2A10(var_r31, sp1C[temp_r27]);
    fn_1_280C(var_r31, REFRESH_RATE);
    lbl_1_bss_C = 1;
    fn_1_280C(var_r31, REFRESH_RATE);
    fn_1_27A4(var_r31);
    HuPrcEnd();
}

void fn_1_C610(void)
{
    float sp14[2] = { 0.0f, 0.0f };
    s32 var_r31;

    lbl_1_bss_C = 0;
    fn_1_2A94(sp14, MAKE_MESSID(29, 86));
    var_r31 = fn_1_20F8((580.0f - sp14[0]) / 2, 80.0f, sp14[0], sp14[1], 2);
    HuAudFXPlay(0x6D2);
    fn_1_4AF8(4);
    lbl_1_bss_C = 1;
    fn_1_2A10(var_r31, MAKE_MESSID(29, 86));
    fn_1_280C(var_r31, 30);
    fn_1_27A4(var_r31);
    lbl_1_bss_C = 2;
    HuPrcEnd();
}

void fn_1_C9C4(void)
{
    float sp10[] = { 0.0f, 0.0f };
    s32 var_r31;

    fn_1_2A94(sp10, MAKE_MESSID(29, 87));
    var_r31 = fn_1_20F8(580.0f - sp10[0] - 40.0f, 200.0f, sp10[0], sp10[1], 1);
    HuAudFXPlayVolPan(0x65, 0x7F, 0x60);
    fn_1_51DC(9, 10, 0, 0);
    fn_1_2A10(var_r31, MAKE_MESSID(29, 87));
    fn_1_280C(var_r31, 30);
    fn_1_27A4(var_r31);
    HuPrcEnd();
}

void fn_1_CD20(void)
{
    float sp10[] = { 0.0f, 0.0f };
    s32 var_r31;

    fn_1_2A94(sp10, MAKE_MESSID(29, 88));
    var_r31 = fn_1_20F8(40.0f, 200.0f, sp10[0], sp10[1], 0);
    HuAudFXPlayVolPan(0x3E, 0x7F, 0x20);
    fn_1_5148(4, 10, 0, 0);
    fn_1_2A10(var_r31, MAKE_MESSID(29, 88));
    fn_1_280C(var_r31, 30);
    fn_1_27A4(var_r31);
    HuPrcEnd();
}

void fn_1_D03C(void)
{
    s32 sp18[] = { MAKE_MESSID(29, 89), MAKE_MESSID(29, 90), MAKE_MESSID(29, 91) };
    float sp10[2] = { 0.0f, 0.0f };
    s32 temp_r28;
    s32 var_r31;

    temp_r28 = rand8() % 3;
    fn_1_2A94(sp10, sp18[temp_r28]);
    var_r31 = fn_1_20F8((580.0f - sp10[0]) / 2, 100.0f, sp10[0], sp10[1], 2);
    HuAudFXPlay(0x6D6);
    fn_1_2A10(var_r31, sp18[temp_r28]);
    fn_1_280C(var_r31, 2 * REFRESH_RATE);
    fn_1_27A4(var_r31);
    HuPrcEnd();
}

void fn_1_D3C0(void)
{
    float sp10[] = { 0.0f, 0.0f };
    s32 var_r31;

    lbl_1_bss_C = 0;
    fn_1_2A94(sp10, MAKE_MESSID(29, 92));
    var_r31 = fn_1_20F8((580.0f - sp10[0]) / 2, 80.0f, sp10[0], sp10[1], 2);
    HuAudFXPlay(0x6D6);
    fn_1_4BAC(1, 10, 0, 1);
    fn_1_2A10(var_r31, MAKE_MESSID(29, 92));
    fn_1_280C(var_r31, 2 * REFRESH_RATE);
    fn_1_4BAC(0, 30, 1, 1);
    fn_1_27A4(var_r31);
    lbl_1_bss_C = 1;
    HuPrcEnd();
}

void fn_1_D754(void)
{
    Mtx sp8;
    s32 var_r26;
    s32 i;
    StructBss944 *var_r29;
    StructBss8FC *var_r24;
    StructBss1DC *temp_r27;
    StructBss1DC *temp_r25;
    StructBss1DC *var_r23;

    var_r29 = &lbl_1_bss_944;
    var_r24 = &lbl_1_bss_8FC;
    temp_r27 = &lbl_1_bss_1DC[var_r29->unk10];
    for (i = 0; i < 4; i++) {
        if (i != var_r29->unk10) {
            temp_r25 = &lbl_1_bss_1DC[i];
            fn_1_15DC8(&temp_r25->unk50);
            fn_1_15CD0(&temp_r25->unk50, temp_r27->unk00->model[0]);
            temp_r25->unk50.unkE4->trans.z = 10.0f;
        }
        else {
            fn_1_15DC8(&temp_r27->unk50);
        }
    }
    if (var_r29->unk20 != 0) {
        lbl_1_bss_38.unk14 = 180;
        var_r26 = var_r29->unk10 - 1;
        if (var_r26 < 0) {
            var_r26 = 3;
        }
        var_r23 = &lbl_1_bss_1DC[var_r26];
        var_r23->unk4C = 0.0f;
        fn_1_6580(var_r26, 1, 2);
    }
    Hu3DModelObjMtxGet(var_r24->unk00->model[0], "m437a01-chara-point", sp8);
    temp_r27->unk4C = sp8[1][3];
    fn_1_6580(var_r29->unk10, 1, 1);
}

s32 fn_1_D930(void)
{
    s32 var_r25 = 4;
    StructBss944 *var_r31 = &lbl_1_bss_944;
    Vec sp5C[] = { { 5.0f, 0.0f, -250.0f }, { -175.0f, 0.0f, -250.0f }, { -325.0f, 0.0f, -250.0f }, { -490.0f, 0.0f, -250.0f } };
    StructBss1DC *temp_r27;
    StructBss1DC *temp_r30;
    s32 var_r28;
    s32 var_r26;
    s32 i;

    var_r28 = var_r31->unk10;
    if (var_r31->unk20 != 0) {
        var_r25 = 3;
    }
    for (i = 0; i < var_r25; i++) {
        temp_r27 = &lbl_1_bss_1DC[var_r28];
        if (i == 0) {
            fn_1_11CE0(temp_r27->unk00, sp5C[i], 0.0f, 4.5f, 10.0f, 5.0f, 0);
        }
        else if (fn_1_11854(&lbl_1_bss_38, 0) >= i * 5 + 10) {
            fn_1_11CE0(temp_r27->unk00, sp5C[i], 90.0f, 9.0f, 30.0f, 15.0f, 2);
        }
        var_r28++;
        if (var_r28 >= 4) {
            var_r28 = 0;
        }
    }
    if (var_r31->unk20 != 0) {
        Vec sp44[] = { { 0.0f, 0.0f, -50.0f }, { -510.0f, 0.0f, -250.0f } };

        var_r26 = var_r31->unk10 - 1;
        if (var_r26 < 0) {
            var_r26 = 3;
        }
        temp_r30 = &lbl_1_bss_1DC[var_r26];
        if (fn_1_11854(&lbl_1_bss_38, 0) <= 60) {
            fn_1_11CE0(temp_r30->unk00, sp44[0], -1.0f, 9.0f, 10.0f, 15.0f, 0);
        }
        else if (temp_r30->unk3C == 7) {
            fn_1_11CE0(temp_r30->unk00, sp44[1], 90.0f, 9.0f, 30.0f, 15.0f, 3);
        }
        else {
            fn_1_11CE0(temp_r30->unk00, sp44[1], 90.0f, 9.0f, 30.0f, 15.0f, 1);
        }
    }
    if (fn_1_11854(&lbl_1_bss_38, 1) != 0) {
        var_r31->unk20 = 1;
        return fn_1_116C4(&lbl_1_bss_38);
    }
}

void fn_1_DCEC(void)
{
    fn_1_B270();
    fn_1_BDB8(1);
    fn_1_1184(5);
}

s32 fn_1_DEC4(void)
{
    StructBss944 *var_r24;

    var_r24 = &lbl_1_bss_944;
    fn_1_11854(&lbl_1_bss_38, 1);
    if (fn_1_11854(&lbl_1_bss_38, 0) <= 10) {
        return 0;
    }
    if (fn_1_11BC() != 0) {
        return fn_1_117C0(&lbl_1_bss_38, 8);
    }
    if (fn_1_B4F4(var_r24->unk10, fn_1_11854(&lbl_1_bss_38, 0)) == 5.0f) {
        fn_1_11E0();
        return fn_1_116C4(&lbl_1_bss_38);
    }
    return 0;
}

void fn_1_E2A8(void)
{
    if (fn_1_36B4() < 0.75f) {
        lbl_1_bss_38.unk14 = 60;
    }
    else {
        lbl_1_bss_38.unk14 = 120;
    }
}

s32 fn_1_E598(void)
{
    if (fn_1_11854(&lbl_1_bss_38, 1) != 0) {
        if (fn_1_3990()) {
            return fn_1_117C0(&lbl_1_bss_38, 5);
        }
        else {
            return fn_1_116C4(&lbl_1_bss_38);
        }
    }
    return 0;
}

void fn_1_E634(void)
{
    if (fn_1_36B4() < 0.75f) {
        HuPrcChildCreate(fn_1_BE80, 100, 0x2000, 0, HuPrcCurrentGet());
    }
    else {
        HuPrcChildCreate(fn_1_C248, 100, 0x2000, 0, HuPrcCurrentGet());
    }
}

s32 fn_1_E944(void)
{
    if (lbl_1_bss_C != 0 && fn_1_11854(&lbl_1_bss_38, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_38);
    }
    return 0;
}

void fn_1_E9A0(void)
{
    StructBss944 *var_r30;
    StructBss1DC *temp_r29;
    s32 i;

    var_r30 = &lbl_1_bss_944;
    temp_r29 = &lbl_1_bss_1DC[var_r30->unk10];
    fn_1_BDB8(0);
    for (i = 0; i < 4; i++) {
        if (i != var_r30->unk10) {
            StructBss1DC *var_r28 = &lbl_1_bss_1DC[i];

            fn_1_15DC8(&temp_r29->unk50);
            fn_1_15CD0(&temp_r29->unk50, var_r28->unk00->model[0]);
        }
    }
    for (i = 0; i < 4; i++) {
        if (i != temp_r29->unk00->work[0]) {
            StructBss1DC *var_r27 = &lbl_1_bss_1DC[i];

            fn_1_11B18(var_r27->unk00, 0, 0, 15, 0);
        }
    }
}

s32 fn_1_EAA4(void)
{
    StructBss944 *var_r30;
    StructBss1DC *sp8;

    var_r30 = &lbl_1_bss_944;
    sp8 = &lbl_1_bss_1DC[var_r30->unk10];
    if (fn_1_11854(&lbl_1_bss_38, 1) != 0) {
        var_r30->unk10++;
        if (var_r30->unk10 >= 4) {
            var_r30->unk10 = 0;
        }
        return fn_1_117C0(&lbl_1_bss_38, 0);
    }
    return 0;
}

void fn_1_EB38(void)
{
    StructBss8D4 *sp8;
    StructBss6BC *var_r31;

    lbl_1_bss_8D4.unk08 = 1;
    var_r31 = &lbl_1_bss_6BC[1];
    var_r31->unk04 = 0;
    var_r31->unk08 = 0;
    var_r31->unk14 = 0;
    lbl_1_bss_C = 0;
    fn_1_3B50();
    HuPrcChildCreate(fn_1_C610, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_C9C4, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_CD20, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_EC10(void)
{
    StructBss1DC *var_r29;
    StructBss8D4 *var_r31;
    s32 i;

    if (lbl_1_bss_C == 1) {
        lbl_1_bss_C = 0;
        for (i = 0; i < 4; i++) {
            var_r29 = &lbl_1_bss_1DC[i];
            fn_1_119A0(var_r29->unk00, 0, 12, 1, 0);
        }
    }
    var_r31 = &lbl_1_bss_8D4;
    if (var_r31->unk00->motion[8] == Hu3DMotionIDGet(var_r31->unk00->model[0]) && Hu3DMotionTimeGet(var_r31->unk00->model[0]) >= 5.0f) {
        Hu3DMotionTimeSet(var_r31->unk00->model[0], 5.0f);
        Hu3DMotionSpeedSet(var_r31->unk00->model[0], 0.0f);
        fn_1_5148(0, 30, 1, 0);
        fn_1_51DC(0, 30, 1, 0);
        fn_1_5270(5, 10, 1, 1);
    }
    if (lbl_1_bss_C == 2 && fn_1_11854(&lbl_1_bss_38, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_38);
    }
    return 0;
}

void fn_1_EDD4(void)
{
    StructBss944 *var_r30;
    StructBss8D4 *var_r29;
    StructBss1DC *temp_r31;

    var_r30 = &lbl_1_bss_944;
    var_r29 = &lbl_1_bss_8D4;
    temp_r31 = &lbl_1_bss_1DC[var_r30->unk10];
    fn_1_4BAC(0, 60, 1, 1);
    Hu3DMotionSpeedSet(var_r29->unk00->model[0], 1.0f);
    temp_r31->unk00->rot.y = 0.0f;
    temp_r31->unk1C = 0;
    fn_1_BDB8(3);
}

s32 fn_1_EEA0(void)
{
    StructBss944 *var_r30;
    StructBss1DC *temp_r31;

    var_r30 = &lbl_1_bss_944;
    temp_r31 = &lbl_1_bss_1DC[var_r30->unk10];
    if (temp_r31->unk1C++ == 0) {
        fn_1_11B18(temp_r31->unk00, 0, 10, 30, 1);
    }
    else if (temp_r31->unk1C > 0) {
        temp_r31->unk00->rot.y = fn_1_11348(0.0f, 180.0f, temp_r31->unk1C, 30.0f);
        if (temp_r31->unk1C >= 30) {
            fn_1_11B18(temp_r31->unk00, 0, 0, 30, 1);
        }
    }
    if (fn_1_11854(&lbl_1_bss_38, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_38);
    }
    return 0;
}

void fn_1_EFCC(void)
{
    StructBss944 *var_r28;
    s32 var_r29;
    s32 i;

    fn_1_79E0();
    var_r28 = &lbl_1_bss_944;
    var_r29 = var_r28->unk10;
    for (i = 0; i < 4; i++) {
        if (i >= 1) {
            fn_1_70F8(var_r29, i);
        }
        var_r29++;
        if (var_r29 >= 4) {
            var_r29 = 0;
        }
    }
    HuPrcChildCreate(fn_1_D03C, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_F0B8(void)
{
    if (fn_1_11854(&lbl_1_bss_38, 1) != 0) {
        return 1;
    }
    return 0;
}

void fn_1_F0F8(void)
{
    lbl_1_bss_8D4.unk08 = 1;
    fn_1_4BAC(0, 60, 1, 1);
}

s32 fn_1_F144(void)
{
    if (fn_1_11854(&lbl_1_bss_38, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_38);
    }
    return 0;
}

void fn_1_F18C(void)
{
    StructBss944 *var_r30;
    StructBss1DC *temp_r31;

    var_r30 = &lbl_1_bss_944;
    temp_r31 = &lbl_1_bss_1DC[var_r30->unk10];
    HuPrcChildCreate(fn_1_D3C0, 100, 0x2000, 0, HuPrcCurrentGet());
    temp_r31->unk00->rot.y = 0.0f;
    temp_r31->unk1C = 0;
    fn_1_5148(0, 10, 1, 0);
    fn_1_51DC(0, 10, 1, 0);
    fn_1_5270(5, 10, 1, 1);
    fn_1_BDB8(3);
}

s32 fn_1_F294(void)
{
    StructBss944 *var_r30;
    StructBss1DC *temp_r31;

    var_r30 = &lbl_1_bss_944;
    temp_r31 = &lbl_1_bss_1DC[var_r30->unk10];
    if (temp_r31->unk1C++ == 60) {
        fn_1_11B18(temp_r31->unk00, 0, 10, 30, 1);
    }
    else if (temp_r31->unk1C > 60) {
        temp_r31->unk00->rot.y = fn_1_11348(0.0f, 180.0f, temp_r31->unk1C - 60, 30.0f);
        if (temp_r31->unk1C >= 90) {
            fn_1_11B18(temp_r31->unk00, 0, 0, 30, 1);
        }
    }
    if (lbl_1_bss_C != 0 && (fn_1_11854(&lbl_1_bss_38, 1) != 0)) {
        return fn_1_116C4(&lbl_1_bss_38);
    }
    return 0;
}

void fn_1_F3D8(void)
{
    StructBss944 *var_r28;
    s32 var_r29;
    s32 i;

    fn_1_79E0();
    var_r28 = &lbl_1_bss_944;
    var_r29 = var_r28->unk10;
    for (i = 0; i < 4; i++) {
        if (i >= 1) {
            fn_1_70F8(var_r29, i);
        }
        var_r29++;
        if (var_r29 >= 4) {
            var_r29 = 0;
        }
    }
}

s32 fn_1_F494(void)
{
    if (fn_1_11854(&lbl_1_bss_38, 1) != 0) {
        return 1;
    }
    return 0;
}

StructData204 lbl_1_data_27C[] = { { fn_1_D754, fn_1_D930, 60 }, { fn_1_DCEC, fn_1_DEC4, 60 }, { fn_1_E2A8, fn_1_E598, 60 },
    { fn_1_E634, fn_1_E944, 10 }, { fn_1_E9A0, fn_1_EAA4, 30 }, { fn_1_EB38, fn_1_EC10, 60 }, { fn_1_EDD4, fn_1_EEA0, 60 },
    { fn_1_EFCC, fn_1_F0B8, 90 }, { fn_1_F0F8, fn_1_F144, 60 }, { fn_1_F18C, fn_1_F294, 60 }, { fn_1_F3D8, fn_1_F494, 90 }, { NULL, NULL, -1 } };

void fn_1_F4D4(void)
{
    fn_1_11668(&lbl_1_bss_38, lbl_1_data_27C);
}

s32 fn_1_F504(void)
{
    if (lbl_1_bss_38.unk08 != NULL) {
        lbl_1_bss_38.unk08();
        lbl_1_bss_38.unk08 = NULL;
    }
    if (lbl_1_bss_38.unk0C != NULL) {
        return lbl_1_bss_38.unk0C();
    }
    return 0;
}

void fn_1_F590(void)
{
    StructBss944 *var_r30;
    StructBss1DC *temp_r31;

    var_r30 = &lbl_1_bss_944;
    temp_r31 = &lbl_1_bss_1DC[var_r30->unk10];
    var_r30->unk1C = 0;
    lbl_1_data_A0 = temp_r31->unk00->model[0];
    lbl_1_data_A4 = temp_r31->unk00->motion[3];
    lbl_1_data_A8 = temp_r31->unk3C;
    HuPrcChildCreate(fn_1_0, 100, 0x2000, 0, HuPrcCurrentGet());
}

s32 fn_1_F640(void)
{
    StructBss944 *var_r31;
    StructBss1DC *temp_r30;

    var_r31 = &lbl_1_bss_944;
    temp_r30 = &lbl_1_bss_1DC[var_r31->unk10];
    if (fn_1_11854(&lbl_1_bss_20, 0) == 120) {
        fn_1_119A0(temp_r30->unk00, 0, 3, 30, 0);
        HuAudSStreamPlay(3);
    }
    if (fn_1_11854(&lbl_1_bss_20, 1) != 0) {
        return fn_1_116C4(&lbl_1_bss_20);
    }
    return 0;
}

StructData204 lbl_1_data_30C[] = { { fn_1_F590, fn_1_F640, 360 }, { NULL, NULL, -1 } };

void fn_1_F6EC(void)
{
    fn_1_11668(&lbl_1_bss_20, lbl_1_data_30C);
}

s32 fn_1_F71C(void)
{
    if (lbl_1_bss_20.unk08 != NULL) {
        lbl_1_bss_20.unk08();
        lbl_1_bss_20.unk08 = NULL;
    }
    if (lbl_1_bss_20.unk0C != NULL) {
        return lbl_1_bss_20.unk0C();
    }
    return 0;
}

void fn_1_F7A8(omObjData *arg0)
{
    StructBss944 *var_r30;
    StructBss1DC *temp_r29;
    s32 i;

    if (WipeStatGet() == 0) {
        HuAudFadeOut(1);
        CharModelKill(-1);
        MGSeqKillAll();
        var_r30 = &lbl_1_bss_944;
        temp_r29 = &lbl_1_bss_1DC[var_r30->unk10];
        for (i = 0; i < 4; i++) {
            GWPlayerCoinWinSet(i, 0);
        }
        GWPlayerCoinWinSet(temp_r29->unk2C, 1);
        omOvlReturnEx(1, 1);
        arg0->func = NULL;
    }
}

s32 fn_1_F89C(void)
{
    return omSysExitReq;
}

void fn_1_F8AC(void)
{
    StructBss944 *var_r29;
    s32 i;

    fn_1_3260(&lbl_1_bss_920);
    fn_1_4538(&lbl_1_bss_8FC);
    fn_1_4E00(&lbl_1_bss_8D4);
    for (i = 0; i < 2; i++) {
        fn_1_5984(&lbl_1_bss_6BC[i]);
    }
    for (i = 0; i < 4; i++) {
        fn_1_74B0(&lbl_1_bss_1DC[i]);
    }
    fn_1_8308(&lbl_1_bss_68);
    var_r29 = &lbl_1_bss_944;
    var_r29->unk00 = var_r29->unk04 = var_r29->unk08 = var_r29->unk0C = 0;
    var_r29->unk10 = var_r29->unk14 = var_r29->unk18 = var_r29->unk1C = 0;
    fn_1_B194();
    fn_1_F4D4();
    fn_1_F6EC();
    fn_1_8C84(0);
    HuAudFXPlay(0x6D7);
}

void fn_1_1043C(omObjData *arg0)
{
    StructBss920 *var_r30;

    switch (lbl_1_bss_18) {
        case 0:
            fn_1_F8AC();
            lbl_1_bss_18++;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                lbl_1_bss_18++;
            }
            break;
        case 2:
            if (fn_1_B1C4() != 0) {
                lbl_1_bss_18++;
            }
            break;
        case 3:
            lbl_1_bss_1C = MGSeqStartCreate();
            lbl_1_bss_18++;
            lbl_1_bss_968.unk04 = -1;
            break;
        case 4:
            if ((MGSeqStatGet(lbl_1_bss_1C) & 0x10) && lbl_1_bss_968.unk04 == -1) {
                lbl_1_bss_968.unk04 = HuAudSeqPlay(0x4D);
            }
            if (MGSeqStatGet(lbl_1_bss_1C) == 0) {
                lbl_1_bss_18++;
            }
            break;
        case 5:
            if (fn_1_F504() != 0) {
                lbl_1_bss_18++;
            }
            break;
        case 6:
            lbl_1_bss_1C = MGSeqFinishCreate();
            lbl_1_bss_18++;
            HuAudSeqPauseAll(0);
            HuAudSeqAllFadeOut(0xFA);
            break;
        case 7:
            if (MGSeqStatGet(lbl_1_bss_1C) == 0) {
                lbl_1_bss_18++;
            }
            break;
        case 8:
            var_r30 = &lbl_1_bss_920;
            var_r30->unk04 = 999;
            if (fn_1_F71C() != 0) {
                lbl_1_bss_18++;
            }
            break;
        case 9:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
            arg0->func = fn_1_F7A8;
            break;
        case 10:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
            arg0->func = fn_1_F7A8;
            break;
    }
    if (omSysExitReq != 0) {
        HuAudSeqAllFadeOut(0xFA);
        lbl_1_bss_18 = 10;
    }
}

void fn_1_108A4(omObjData *arg0)
{
    s32 i;

    lbl_1_bss_920.unk00 = omAddObjEx(lbl_1_bss_0, 0x100, 16, 16, -1, fn_1_3410);
    lbl_1_bss_8FC.unk00 = omAddObjEx(lbl_1_bss_0, 0x200, 16, 16, -1, fn_1_46C0);
    lbl_1_bss_8D4.unk00 = omAddObjEx(lbl_1_bss_0, 0x300, 16, 16, -1, fn_1_4EE0);
    for (i = 0; i < 2; i++) {
        lbl_1_bss_6BC[i].unk00 = omAddObjEx(lbl_1_bss_0, 0x400, 16, 16, -1, fn_1_5AD8);
        lbl_1_bss_6BC[i].unk00->work[0] = i;
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_1DC[i].unk00 = omAddObjEx(lbl_1_bss_0, 0x500, 16, 16, -1, fn_1_7678);
        lbl_1_bss_1DC[i].unk00->work[0] = i;
    }
    lbl_1_bss_68.unk00 = omAddObjEx(lbl_1_bss_0, 0x600, 16, 16, -1, fn_1_84C4);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    arg0->func = fn_1_1043C;
}

#ifdef __MWERKS__
#include "src/REL/executor.c"
#endif

void fn_1_10B30(void)
{
    lbl_1_bss_0 = omInitObjMan(62, 0x2000);
    omGameSysInit(lbl_1_bss_0);
    fn_1_1A8();
    fn_1_F8C();
    fn_1_10C0();
    fn_1_13E8();
    fn_1_1A90();
    fn_1_5FBC();
    omAddObjEx(lbl_1_bss_0, 0x1000, 0, 0, -1, fn_1_108A4);
}

void ObjectSetup(void)
{
    fn_1_10B30();
}
