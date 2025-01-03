#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/pad.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#endif

s32 rand8(void);

typedef struct UnkCameraStruct {
    /* 0x00 */ float unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
} UnkCameraStruct; /* size = 0x18 */

typedef struct M449DllUnkStruct {
    /* 0x00 */ s32 unk_00[4];
    /* 0x10 */ s32 unk_10[4];
} M449DllUnkStruct; /* size = 0x20 */

typedef struct M449DllWork {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    float unk_20;
    float unk_24;
    float unk_28;
    float unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    float unk_3C;
    float unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    float unk_58;
    float unk_5C;
    float unk_60[4];
    float unk_70[4];
    float unk_80[4];
    float unk_90[4];
    float unk_A0[4];
    float unk_B0[4];
    float unk_C0[4];
    float unk_D0[4];
    float unk_E0[4];
    s32 unk_F0[4];
    s32 unk_100[4];
    s32 unk_110[4];
    s32 unk_120[4];
    s32 unk_130[4];
    s32 unk_140[4];
    s32 unk_150[4];
    float unk_160[4];
    float unk_170[4];
    s32 unk_180[4];
    s32 unk_190;
    float unk_194[4];
    float unk_1A4[4];
    s32 unk_1B4[4];
    s32 unk_1C4[4];
    char unk1D4[0x30];
    s32 unk_204;
    s32 unk_208;
    s32 unk_20C;
    s32 unk_210;
    s32 unk_214;
} M449DllWork; /* size = 0x218 */

typedef struct UnkBss64Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ float unk_04[2];
} UnkBss64Struct; /* size = 0x0C */

void fn_1_9A38(omObjData *arg0);

s32 lbl_1_data_0[0x12] = {
    0x50001A,
    0x500019,
    0x500016,
    0x500016,
    0x500016,
    0x500017,
    0x500017,
    0x500017,
    0x610000,
    0x50001A,
    0x500019,
    0x500016,
    0x500016,
    0x500016,
    0x500017,
    0x500017,
    0x500017,
    0x610000,
};
s32 lbl_1_data_48[0x12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
s32 lbl_1_data_90[4] = { 0x5F0000, 0x500000, 0x5F0017, 0x5F0085 };
s32 lbl_1_data_A0[4] = { 0x50001C, 0x50001E, 0x50001D, 0x50001F };
u8 lbl_1_data_B0[0x38] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08

};
char lbl_1_data_E8[4][20] = {
    "m432_00-a00",
    "m432_00-b00",
    "m432_00-player00",
    "m432_00-player01",
};
char lbl_1_data_138[4][20] = {
    "m449_01a-a00",
    "m449_01a-a1",
    "m449_01a-a2",
    "m449_01a-a3",
};
char lbl_1_data_188[4][20] = {
    "m449_01a-b00",
    "m449_01a-b1",
    "m449_01a-b2",
    "m449_01a-b3",
};
char lbl_1_data_1D8[4][20] = {
    "m449_01a-c00",
    "m449_01a-c1",
    "m449_01a-c2",
    "m449_01a-c3",
};
s16 lbl_1_data_228 = -1;
s16 lbl_1_data_22A = -1;
s32 lbl_1_data_22C = -1;
s32 lbl_1_data_230[3] = { -1, -1, -1 };
s32 lbl_1_data_23C[0xA] = {
    0,
    1,
    0xC2B40000,
    0,
    0x44034000,
    0x43340000,
    0x42B40000,
    0,
    0x44034000,
    0x43340000,
};

UnkBss64Struct lbl_1_bss_64[12];
omObjData *lbl_1_bss_60;
omObjData *lbl_1_bss_5C;
omObjData *lbl_1_bss_58;
omObjData *lbl_1_bss_54;
omObjData *lbl_1_bss_50;
s32 lbl_1_bss_4C;
s32 lbl_1_bss_48;
s32 lbl_1_bss_44;
s32 lbl_1_bss_40;
s32 lbl_1_bss_3C;
Process *lbl_1_bss_38;
s32 lbl_1_bss_34;
s32 lbl_1_bss_30;
s32 lbl_1_bss_2C;
float lbl_1_bss_28;
float lbl_1_bss_24;
float lbl_1_bss_20;
s32 lbl_1_bss_1C;
float lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

static const s32 lbl_1_rodata_10[4] = { 0x8C, 0x6E, 0x3C, 0 };

void fn_1_A0(void)
{
    if ((HuPadBtnDown[0] & PAD_BUTTON_B) != 0) {
        Center.x = lbl_1_bss_54->trans.x;
        Center.y = lbl_1_bss_54->trans.y;
        Center.z = lbl_1_bss_54->trans.z;
    }
    Center.x += 10.0 * (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0));
    Center.z -= 10.0 * (((HuPadBtn[0] & PAD_BUTTON_UP) != 0) - ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0));
    Center.y += (30.0 * ((HuPadTrigL[0] - HuPadTrigR[0]) / 128.0));
    CZoom += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
    CRot.y += HuPadSubStkX[0] / 16.0;
    CRot.x += HuPadSubStkY[0] / -16.0;
}

void fn_1_3F8(s32 arg0, Mtx sp8)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;

    GXLoadPosMtxImm(sp8, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 0x12);
        GXPosition3f32(0.0f, 0.0f, 0.0f);
        GXColor4u8(0xFF, 0xFF, 0x00, 0xFF);
        for (var_r31 = 0; var_r31 < 0x11; var_r31++) {
            var_f30 = (var_r30 == 0 ? 1 : -1) * (75.0 * cosd((360.0 * (var_r31 / 16.0))));
            var_f31 = 75.0 * sind((360.0 * (var_r31 / 16.0)));
            GXPosition3f32(var_f31, var_r30 * 10, var_f30);
            GXColor4u8(0xFF, 0xFF, 0x00, 0xFF);
        }
    }
}

void fn_1_758(omObjData *var_r29)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f20;
    float var_f19;
    float var_f18;

    M449DllWork *var_r31;
    s32 var_r30;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    ModelData *var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    ModelData *var_r19;
    s32 var_r18;
    s32 var_r17;

    Vec sp3C4[3];
    Vec sp394[4];
    Mtx sp364;
    Mtx sp334;
    Mtx sp304;
    Vec sp2D8;
    Vec sp2CC;
    Vec sp2C0;
    Vec sp2B4;
    Vec sp2A8;
    void *sp238;
    s32 sp234;
    s32 sp230;
    float sp22C;
    float sp228;
    float sp224;
    s32 sp220;
    float sp21C;
    float sp218;
    s32 sp214;
    float sp210;
    float sp20C;
    float sp208;
    s32 sp204;
    s32 sp200;
    s32 sp1FC;
    float sp1F8;
    s32 sp1F4;
    float sp1F0;
    float sp1EC;
    float sp1E8;
    float sp1E4;
    float sp1E0;
    float sp1DC;
    float sp1D8;
    float sp1D4;
    float sp1D0;
    float sp1CC;
    float sp1C8;
    float sp1C4;
    float sp1C0;
    float sp1BC;
    float sp1B8;
    float sp1B4;
    float sp1B0;
    float sp1AC;
    float sp1A8;
    float sp1A4;
    float sp1A0;
    float sp19C;
    float sp198;
    float sp194;
    float sp190;
    float sp18C;
    float sp188;
    float sp184;
    float sp180;
    float sp17C;
    float sp178;
    float sp174;
    float sp170;
    float sp16C;
    float sp168;
    float sp164;
    s32 sp160;
    float sp15C;
    float sp158;
    s32 sp154;
    float sp150;
    float sp14C;
    float sp148;
    float sp144;
    float sp140;
    float sp13C;
    float sp138;
    float sp134;
    float sp130;
    float sp12C;
    float sp128;
    float sp124;

    {
        s32 sp568[4][4][3] = {
            {
                { 2, 5, 5 },
                { 2, 7, 11 },
                { 0, 4, 7 },
                { 0, 7, 8 },
            },
            {
                { 1, 6, 3 },
                { 1, 1, 2 },
                { 8, 2, 3 },
                { 8, 12, 16 },
            },
            {
                { 3, 5, 5 },
                { 1, 6, 13 },
                { 1, 3, 4 },
                { 3, 8, 12 },
            },
            {
                { 2, 3, 4 },
                { 1, 2, 3 },
                { 0, 1, 3 },
                { 2, 3, 3 },
            },
        };
        s32 sp4A8[4][4][3] = {
            {
                { 0, 44, 23 },
                { 32, -64, -29 },
                { 0, 52, -60 },
                { 0, -51, 56 },
            },
            {
                { -29, 28, -52 },
                { 32, 31, -22 },
                { 0, 20, -49 },
                { 0, 0, 0 },
            },
            {
                { 56, 59, -37 },
                { -36, 33, 47 },
                { 27, 39, 28 },
                { 55, -31, 0 },
            },
            {
                { -52, -61, 31 },
                { 42, -55, 30 },
                { 0, 22, -24 },
                { -48, 25, 61 },
            },
        };

        s32 sp3E8[4][4][3] = {
            {
                { 0, -44, 23 },
                { -32, 64, 29 },
                { 0, -52, -60 },
                { 0, -51, -56 },
            },
            {
                { -29, 28, 52 },
                { 32, -31, -22 },
                { 0, 20, 49 },
                { 0, 0, 0 },
            },
            {
                { -56, 59, -37 },
                { 36, 33, -47 },
                { -27, 39, -28 },
                { -55, -31, 0 },
            },
            {
                { 52, -61, -31 },
                { -42, 55, -30 },
                { 0, -22, -24 },
                { 48, 25, -61 },
            },
        };
        var_r31 = var_r29->data;
        sp238 = (&lbl_1_bss_54)[1 - var_r29->work[0]]->data;
        var_f29 = 0.0f;
        var_f28 = 0.0f;
        Hu3DModelObjPosGet(lbl_1_bss_50->model[1], lbl_1_data_E8[var_r31->unk_00], &sp2D8);
        for (var_r30 = 0; var_r30 < (lbl_1_data_230[var_r31->unk_190] == 2 ? 2 : 3); var_r30++) {
            Hu3DModelObjPosGet(var_r29->model[var_r31->unk_190 + 4], lbl_1_data_188[var_r30], &sp3C4[var_r30]);
            sp3C4[var_r30].x -= sp2D8.x;
            sp3C4[var_r30].y -= sp2D8.y;
            sp3C4[var_r30].z -= sp2D8.z;
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            Hu3DModelObjPosGet(var_r29->model[var_r31->unk_190 + 4], lbl_1_data_1D8[var_r30], &sp394[var_r30]);
            sp394[var_r30].x -= sp2D8.x;
            sp394[var_r30].y -= sp2D8.y;
            sp394[var_r30].z -= sp2D8.z;
        }
        switch (var_r31->unk_4C) {
            case 0:
                if (lbl_1_bss_48 == 0x3EC) {
                    var_r31->unk_4C = 1;
                    var_r31->unk_14 = var_r31->unk_204 % 4;
                    var_r31->unk_14 = var_r31->unk_1C = var_r31->unk_30 = var_r31->unk_34 = var_r31->unk_38 = 0;
                    var_r31->unk_18 = -1;
                    var_r31->unk_3C = var_r31->unk_40 = var_r31->unk_44 = var_r31->unk_48 = 0;
                    var_r31->unk_208 = var_r31->unk_0C == -1 ? 1 : 0;
                    if (var_r31->unk_0C == -1) {
                        var_r17 = lbl_1_data_23C[var_r31->unk_00];
                        var_r31->unk_204 = sp568[lbl_1_data_230[var_r31->unk_190]][var_r31->unk_10][var_r17];
                        var_r31->unk_20C = sp4A8[lbl_1_data_230[var_r31->unk_190]][var_r31->unk_10][var_r17];
                        var_r31->unk_210 = sp3E8[lbl_1_data_230[var_r31->unk_190]][var_r31->unk_10][var_r17];
                    }
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        var_r31->unk_90[var_r30] = var_r31->unk_A0[var_r30] = var_r31->unk_B0[var_r30] = var_r31->unk_D0[var_r30]
                            = var_r31->unk_E0[var_r30] = 0.0f;
                        var_r31->unk_F0[var_r30] = var_r31->unk_100[var_r30] = var_r31->unk_110[var_r30] = var_r31->unk_120[var_r30]
                            = var_r31->unk_130[var_r30] = var_r31->unk_140[var_r30] = 0;
                        var_r31->unk_160[var_r30] = var_r31->unk_170[var_r30] = var_r31->unk_150[var_r30] = 0;
                    }
                }
                break;
            case 1:
                if (lbl_1_bss_30 != -1) {
                    var_r31->unk_4C = 3;
                    if ((lbl_1_bss_30 == var_r31->unk_00) && (var_r31->unk_F0[0] != 0) && (var_r31->unk_F0[1] != 0) && (var_r31->unk_F0[2] != 0)
                        && (var_r31->unk_F0[3] != 0)) {
                        var_r31->unk_54 = 0x1E;
                        HuAudFXPlay(9);
                    }
                }
                else if ((var_r31->unk_190 < 2) && (var_r31->unk_F0[0] != 0) && (var_r31->unk_F0[1] != 0) && (var_r31->unk_F0[2] != 0)
                    && (var_r31->unk_F0[3] != 0)) {
                    if (lbl_1_bss_64[3].unk_00 < 2) {
                        lbl_1_bss_64[3].unk_04[lbl_1_bss_64[3].unk_00] = 0.0f;
                        lbl_1_bss_64[3].unk_00++;
                    }
                    var_r31->unk_4C = 2;
                    var_r31->unk_50 = 0;
                    Hu3DMotionSpeedSet(var_r29->model[var_r31->unk_190 + 1], -1.0f);
                    var_r31->unk_14 = var_r31->unk_1C = var_r31->unk_30 = var_r31->unk_34 = var_r31->unk_38 = 0;
                    var_r31->unk_18 = -1;
                    var_r31->unk_3C = var_r31->unk_40 = var_r31->unk_44 = var_r31->unk_48 = 0;
                    var_r31->unk_208 = var_r31->unk_0C == -1 ? 1 : 0;
                    if (var_r31->unk_0C == -1) {
                        sp234 = (var_r31->unk_190 + lbl_1_data_23C[var_r31->unk_00] + 1) % 3;
                        var_r31->unk_204 = sp568[lbl_1_data_230[var_r31->unk_190 + 1]][var_r31->unk_10][sp234];
                        var_r31->unk_20C = sp4A8[lbl_1_data_230[var_r31->unk_190 + 1]][var_r31->unk_10][sp234];
                        var_r31->unk_210 = sp3E8[lbl_1_data_230[var_r31->unk_190 + 1]][var_r31->unk_10][sp234];
                    }
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        var_r31->unk_90[var_r30] = var_r31->unk_A0[var_r30] = var_r31->unk_B0[var_r30] = var_r31->unk_D0[var_r30]
                            = var_r31->unk_E0[var_r30] = 0.0f;
                        var_r31->unk_F0[var_r30] = var_r31->unk_100[var_r30] = var_r31->unk_110[var_r30] = var_r31->unk_120[var_r30]
                            = var_r31->unk_130[var_r30] = var_r31->unk_140[var_r30] = 0;
                        var_r31->unk_160[var_r30] = var_r31->unk_170[var_r30] = var_r31->unk_150[var_r30] = 0;
                    }
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        sp230 = -1;
                        sp22C = 10000.0f;
                        Hu3DModelObjPosGet(var_r29->model[4], lbl_1_data_138[var_r30], &sp2CC);
                        for (var_r28 = 0; var_r28 < 4; var_r28++) {
                            sp228 = sp2CC.x - var_r31->unk_60[var_r28];
                            sp224 = sp2CC.z - var_r31->unk_80[var_r28];
                            if ((var_r31->unk_F0[var_r28] == 0) && (sqrtf((sp228 * sp228) + (sp224 * sp224)) < sp22C)) {
                                sp230 = var_r28;
                                sp22C = sqrtf((sp228 * sp228) + (sp224 * sp224));
                            }
                        }
                        var_r31->unk_1B4[sp230] = var_r30;
                        var_r31->unk_F0[sp230] = 1;
                        var_r31->unk_194[var_r30] = var_r31->unk_60[var_r30];
                        var_r31->unk_1A4[var_r30] = var_r31->unk_80[var_r30];
                    }
                    var_r31->unk_F0[0] = var_r31->unk_F0[1] = var_r31->unk_F0[2] = var_r31->unk_F0[3] = 0;
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        sp220 = var_r30 + 7;
                        var_r19 = &Hu3DData[var_r29->model[var_r30 + 0xC]];
                        Hu3DModelPosSet(var_r29->model[sp220], var_r19->pos.x, 0.0f, var_r19->pos.z);
                        Hu3DModelAttrReset(var_r29->model[sp220], HU3D_ATTR_DISPOFF);
                        Hu3DParticleCntSet(var_r29->model[sp220], 0);
                    }
                    if (lbl_1_bss_30 == -1) {
                        var_r31->unk_54 = 0x1E;
                        HuAudFXPlay(9);
                    }
                }
                break;
            case 2:
                var_r31->unk_50++;
                if (var_r31->unk_50 == 0xA) {
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        Hu3DModelAttrSet(var_r29->model[var_r30 + 0xC], HU3D_ATTR_DISPOFF);
                    }
                }
                if (var_r31->unk_50 <= 0x3C) {
                    sp21C = var_r31->unk_50 / 60.0;
                    for (var_r30 = 0; var_r30 < 4; var_r30++) { }
                }
                var_r31->unk_50 == 0x3C;
                if ((var_r31->unk_50 >= 0) && (var_r31->unk_50 <= 0x3C)) {
                    sp218 = var_r31->unk_50 / 60.0;
                    var_f21 = 0.5 + (-0.5 * cosd((180.0f * sp218)));
                    var_f21 = sp218 < 0.75 ? 0 : 1;
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        Hu3DModelObjPosGet(var_r29->model[var_r31->unk_190 + 5], lbl_1_data_138[var_r30], &sp2C0);
                        var_r31->unk_60[var_r30] = (var_f21 * (sp2C0.x - sp2D8.x)) + (var_r31->unk_194[var_r30] * (1.0f - var_f21));
                        var_r31->unk_80[var_r30] = (var_f21 * (sp2C0.z - sp2D8.z)) + (var_r31->unk_1A4[var_r30] * (1.0f - var_f21));
                        var_r31->unk_70[var_r30] = 300.0 * sind((180.0f * sp218));
                        var_r31->unk_70[var_r30] = -25.0f * (1.0f - var_f21);
                    }
                }
                if (var_r31->unk_50 == 0x3C) {
                    Hu3DMotionSpeedSet(var_r29->model[var_r31->unk_190 + 1], 1.0f);
                    Hu3DModelAttrSet(var_r29->model[var_r31->unk_190 + 1], HU3D_ATTR_DISPOFF);
                    var_r31->unk_190++;
                    Hu3DModelAttrReset(var_r29->model[var_r31->unk_190 + 1], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(var_r29->model[var_r31->unk_190 + 1], HU3D_MOTATTR_LOOP);
                    Hu3DMotionTimeSet(var_r29->model[var_r31->unk_190 + 1], 0.0f);
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        sp214 = var_r30 + 7;
                        var_r24 = &Hu3DData[var_r29->model[var_r30 + 0xC]];
                        Hu3DModelPosSet(var_r29->model[sp214], var_r24->pos.x, var_r24->pos.y, var_r24->pos.z);
                        Hu3DModelAttrReset(var_r29->model[sp214], HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(var_r29->model[var_r30 + 0xC], HU3D_ATTR_DISPOFF);
                        Hu3DModelScaleSet(var_r29->model[var_r30 + 0xC], 0.0f, 0.0f, 0.0f);
                        Hu3DParticleCntSet(var_r29->model[sp214], 0);
                    }
                }
                if ((var_r31->unk_50 >= 0x3E) && (var_r31->unk_50 <= 0x78)) {
                    sp210 = (var_r31->unk_50 - 0x3E) / 58.0;
                    sp20C = sp210 < 0.25 ? (sp210 / 0.25) : 1.0;
                    sp20C = var_r31->unk_50 < 0x46 ? 0 : 1;
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        Hu3DModelScaleSet(var_r29->model[var_r30 + 0xC], sp20C, sp20C, sp20C);
                    }
                }
                if (var_r31->unk_50 == 0x78) {
                    var_r31->unk_4C = 1;
                    var_r31->unk_50 = 0;
                }
                break;
            case 3:
                break;
        }
        if (var_r31->unk_54 > 0) {
            var_f26 = 1.0 - ((var_r31->unk_54 - 1) / 30.0);
            sp204 = var_r31->unk_190 + 5 + (var_r31->unk_00 * 9);
            var_f26 = (0.5 * var_f26) + (0.5 * (1.0f - ((1.0f - var_f26) * (1.0f - var_f26))));
            sp208 = var_f26 < 0.75 ? (var_f26 / 0.75) : 1.0;
            var_f26 = 1.0f - ((1.0f - var_f26) * (1.0f - var_f26));
            sp208 = 1.0f - ((1.0f - sp208) * (1.0f - sp208));
            if (var_r31->unk_54 == 0x1E) {
                espDispOn(lbl_1_data_48[sp204]);
                espDispOff(lbl_1_data_48[var_r31->unk_190 + 2 + (var_r31->unk_00 * 9)]);
            }
            espTPLvlSet(lbl_1_data_48[sp204], sp208);
            espScaleSet(lbl_1_data_48[sp204], 4.0f - (3.0f * var_f26), 4.0f - (3.0f * var_f26));
            var_r31->unk_54--;
        }
        if (var_r31->unk_4C == 1) {
            if (var_r31->unk_0C != -1) {
                var_f29 = HuPadStkX[var_r31->unk_0C];
                var_f28 = HuPadStkY[var_r31->unk_0C];
                var_f29 /= 40.0f;
                var_f28 /= 40.0f;
            }
            else if (var_r31->unk_208 != 0) {
                var_f29 = 3.0f * -var_r31->unk_58;
                var_f28 = -3.0f * -var_r31->unk_5C;
            }
            else if ((var_r31->unk_0C == -1) && ((var_r31->unk_20C != 0) || (var_r31->unk_210 != 0))) {
                var_f29 = var_r31->unk_20C < 0 ? -1 : (var_r31->unk_20C > 0 ? 1 : 0);
                var_f28 = var_r31->unk_210 < 0 ? -1 : (var_r31->unk_210 > 0 ? 1 : 0);
                var_r31->unk_20C = var_r31->unk_20C + (var_r31->unk_20C < 0 ? 1 : (var_r31->unk_20C > 0 ? -1 : 0));
                var_r31->unk_210 = var_r31->unk_210 + (var_r31->unk_210 < 0 ? 1 : (var_r31->unk_210 > 0 ? -1 : 0));
            }
            else if ((var_r31->unk_F0[0] == 0) || (var_r31->unk_F0[1] == 0) || (((var_r31->unk_F0[2] == 0) != 0)) || (var_r31->unk_F0[3] == 0)) {
                if (var_r31->unk_F0[var_r31->unk_14] != 0) {
                    var_r23 = -1;
                    sp1FC = var_r31->unk_F0[3] + (var_r31->unk_F0[0] + var_r31->unk_F0[1] + var_r31->unk_F0[2]);
                    for (sp200 = 0; sp200 <= (sp1FC == 1 ? ((var_r31->unk_204 / 4) % 3) : (sp1FC == 2 ? (((var_r31->unk_204 / 4) / 3) % 2) : 0));
                         sp200++) {
                        for (var_r23++; var_r31->unk_F0[var_r23] != 0; var_r23++) { }
                    }
                    var_r31->unk_14 = var_r23;
                }
                var_r25 = var_r31->unk_14;
                if (var_r25 != -1) {
                    var_f30 = var_r31->unk_60[var_r25] + var_r31->unk_90[var_r25];
                    var_f31 = var_r31->unk_80[var_r25] + var_r31->unk_B0[var_r25];
                    var_r22 = -1;
                    sp1F8 = -1.0f;
                    sp1F4 = var_r31->unk_1C;
                    if (var_r31->unk_100[var_r31->unk_18] != 0) {
                        var_r31->unk_1C = 0;
                        var_r31->unk_18 = -1;
                    }
                    if (var_r31->unk_1C != 0) {
                        for (var_r26 = 0; var_r26 < 4; var_r26++) {
                            sp1F0 = var_r31->unk_60[var_r26] + var_r31->unk_90[var_r26];
                            sp1EC = var_r31->unk_80[var_r26] + var_r31->unk_B0[var_r26];
                            if (var_r31->unk_F0[var_r26] == 0) {
                                if (var_r31->unk_28 != 0.0f && !(var_r31->unk_28 < 0.0f ? (sp1F0 < var_r31->unk_20) : (sp1F0 > var_r31->unk_20))) { }
                                else {
                                    if (var_r31->unk_2C != 0.0f
                                        && !(var_r31->unk_2C < 0.0f ? (sp1EC < var_r31->unk_24) : (sp1EC > var_r31->unk_24))) { }
                                    else {
                                        var_r31->unk_1C = 0;
                                        var_r31->unk_14 = var_r26;
                                        var_r25 = var_r26;
                                        var_f30 = sp1F0;
                                        var_f31 = sp1EC;
                                    }
                                }
                            }
                        }
                    }
                    switch (lbl_1_data_230[var_r31->unk_190]) {
                        case 0:
                            if ((var_r31->unk_100[0] != 0) && (var_r31->unk_18 == 1) && (var_f31 > 0.0f) && (var_f30 < 0.0f)) {
                                var_r31->unk_1C = 1;
                                var_r31->unk_20 = 150.0f;
                                var_r31->unk_24 = 150.0f;
                                var_r31->unk_28 = 1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_r31->unk_100[0] != 0) && (var_r31->unk_18 == 1) && (var_f31 > 100.0f) && (var_f30 < 150.0f)) {
                                var_r31->unk_1C = 1;
                                var_r31->unk_20 = 150.0f;
                                var_r31->unk_24 = 150.0f;
                                var_r31->unk_28 = 1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_r31->unk_100[0] != 0) && (var_r31->unk_1C == 0) && (sp1F4 == 1)) {
                                var_r31->unk_1C = 2;
                                var_r31->unk_24 = -50.0f;
                                var_r31->unk_28 = 0.0f;
                                var_r31->unk_2C = -1.0f;
                            }
                            if ((var_r31->unk_100[0] != 0) && (var_r31->unk_18 >= 2) && (var_f30 < -100.0f) && (var_f31 < -120.0f)) {
                                var_r31->unk_1C = 3;
                                var_r31->unk_24 = -120.0f;
                                var_r31->unk_28 = 0.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_r31->unk_100[0] != 0) && (var_r31->unk_18 >= 2) && (var_r31->unk_1C == 0) && (var_f30 < 0.0f)
                                && (var_f31 < 0.0f)) {
                                var_r31->unk_1C = 4;
                                var_r31->unk_20 = 0.0f;
                                var_r31->unk_24 = -120.0f;
                                var_r31->unk_28 = 1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_r31->unk_100[0] != 0) && (var_r31->unk_18 >= 2) && (var_r31->unk_1C == 0) && (sp1F4 == 3)) {
                                var_r31->unk_1C = 5;
                                var_r31->unk_20 = 190.0f;
                                var_r31->unk_24 = 190.0f;
                                var_r31->unk_28 = 1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_r31->unk_100[0] != 0) && (var_r31->unk_1C == 0) && (sp1F4 == 5) && (var_r31->unk_18 == 3)) {
                                var_r31->unk_1C = 6;
                                var_r31->unk_20 = 0.0f;
                                var_r31->unk_28 = -1.0f;
                                var_r31->unk_2C = 0.0f;
                            }
                            break;
                        case 1:
                            if ((var_r31->unk_18 == 3) && (var_f31 > 75.0f) && ((var_f30 < -150.0f) || (var_f30 > 150.0f))) {
                                var_r31->unk_1C = 1;
                                var_r31->unk_24 = 75.0f;
                                var_r31->unk_28 = 0.0f;
                                var_r31->unk_2C = -1.0f;
                            }
                            if ((var_r31->unk_100[1] != 0) && (var_f31 < -120.0f) && (var_f30 > 100.0f)) {
                                var_r31->unk_1C = 2;
                                var_r31->unk_24 = -120.0f;
                                var_r31->unk_28 = 0.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_r31->unk_18 == 2) && (var_r31->unk_100[0] != 0) && (var_f31 < -120.0f) && (var_f30 < -120.0f)) {
                                var_r31->unk_1C = 3;
                                if (var_f30 < var_f31) {
                                    var_r31->unk_20 = -150.0f;
                                    var_r31->unk_24 = -80.0f;
                                    var_r31->unk_28 = -1.0f;
                                    var_r31->unk_2C = 1.0f;
                                }
                                else {
                                    var_r31->unk_24 = -150.0f;
                                    var_r31->unk_20 = -80.0f;
                                    var_r31->unk_2C = -1.0f;
                                    var_r31->unk_28 = 1.0f;
                                }
                            }
                            break;
                        case 2:
                            if ((var_r31->unk_100[3] != 0) && (var_f31 > 100.0f) && (var_f30 < -75.0f)) {
                                var_r31->unk_1C = 1;
                                var_r31->unk_20 = -75.0f;
                                var_r31->unk_24 = 175.0f;
                                var_r31->unk_28 = 1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_r31->unk_100[3] != 0) && (var_f31 < -50.0f) && (var_f30 < -150.0f)) {
                                var_r31->unk_1C = 2;
                                var_r31->unk_20 = -200.0f;
                                var_r31->unk_24 = -25.0f;
                                var_r31->unk_28 = -1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_r31->unk_18 == 2) && (var_r31->unk_100[2] != 0) && ((var_f30 + var_f31) > 300.0f)) {
                                var_r31->unk_1C = 3;
                                if (var_f30 > var_f31) {
                                    var_r31->unk_20 = 200.0f;
                                    var_r31->unk_24 = 80.0f;
                                    var_r31->unk_28 = 1.0f;
                                    var_r31->unk_2C = -1.0f;
                                }
                                else {
                                    var_r31->unk_24 = 200.0f;
                                    var_r31->unk_20 = 80.0f;
                                    var_r31->unk_2C = 1.0f;
                                    var_r31->unk_28 = -1.0f;
                                }
                            }
                            if ((var_r31->unk_18 == 1) && (var_r31->unk_100[2] != 0) && ((var_f30 - var_f31) > 300.0f)) {
                                var_r31->unk_1C = 4;
                                if (var_f30 > -var_f31) {
                                    var_r31->unk_20 = 200.0f;
                                    var_r31->unk_24 = -80.0f;
                                    var_r31->unk_28 = 1.0f;
                                    var_r31->unk_2C = 1.0f;
                                }
                                else {
                                    var_r31->unk_24 = -200.0f;
                                    var_r31->unk_20 = 80.0f;
                                    var_r31->unk_2C = -1.0f;
                                    var_r31->unk_28 = -1.0f;
                                }
                            }
                            break;
                        case 3:
                            if ((var_f31 > 200.0f) && (var_f30 > 200.0f) && (var_r31->unk_18 != 3)) {
                                var_r31->unk_1C = 2;
                                if (var_r31->unk_18 == 2) {
                                    var_r31->unk_20 = -150.0f;
                                    var_r31->unk_24 = 150.0f;
                                    var_r31->unk_28 = -1.0f;
                                    var_r31->unk_2C = 1.0f;
                                }
                                else {
                                    var_r31->unk_20 = 150.0f;
                                    var_r31->unk_24 = -150.0f;
                                    var_r31->unk_28 = 1.0f;
                                    var_r31->unk_2C = -1.0f;
                                }
                            }
                            if ((var_f31 > 0.0f) && (var_f30 > 0.0f) && (!(var_f30 < 100.0f) || !(var_f31 < 100.0f)) && (var_r31->unk_18 != 3)
                                && (var_r31->unk_1C == 0)) {
                                var_r31->unk_1C = 1;
                                var_r31->unk_20 = 200.0f;
                                var_r31->unk_24 = 200.0f;
                                var_r31->unk_28 = 1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_f31 > 200.0f) && (var_f30 < -200.0f) && (var_r31->unk_18 != 2)) {
                                var_r31->unk_1C = 4;
                                if (var_r31->unk_18 == 3) {
                                    var_r31->unk_20 = 150.0f;
                                    var_r31->unk_24 = 150.0f;
                                    var_r31->unk_28 = 1.0f;
                                    var_r31->unk_2C = 1.0f;
                                }
                                else {
                                    var_r31->unk_20 = -150.0f;
                                    var_r31->unk_24 = -150.0f;
                                    var_r31->unk_28 = -1.0f;
                                    var_r31->unk_2C = -1.0f;
                                }
                            }
                            if ((var_f31 > 0.0f) && (var_f30 < 0.0f) && (var_r31->unk_18 != 2) && (var_r31->unk_1C == 0)
                                && ((var_r31->unk_100[0] != 0) || (var_r31->unk_18 == 3))) {
                                var_r31->unk_1C = 3;
                                var_r31->unk_20 = -200.0f;
                                var_r31->unk_24 = 200.0f;
                                var_r31->unk_28 = -1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_f31 < -200.0f) && (var_f30 > 200.0f) && (var_r31->unk_18 == 3) && (var_r31->unk_1C == 0)) {
                                var_r31->unk_1C = 9;
                                var_r31->unk_20 = 200.0f;
                                var_r31->unk_24 = 0.0;
                                var_r31->unk_28 = 1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_f31 < -200.0f) && (var_f30 < -200.0f) && (var_r31->unk_18 == 2) && (var_r31->unk_1C == 0)) {
                                var_r31->unk_1C = 8;
                                var_r31->unk_20 = -200.0f;
                                var_r31->unk_24 = 0.0f;
                                var_r31->unk_28 = -1.0f;
                                var_r31->unk_2C = 1.0f;
                            }
                            if ((var_f31 < -200.0f) && (var_r31->unk_18 >= 2) && (var_r31->unk_1C == 0)) {
                                var_r31->unk_1C = 7;
                                var_r31->unk_24 = -200.0f;
                                var_r31->unk_2C = -1.0f;
                                if (var_r31->unk_18 == 3) {
                                    var_r31->unk_20 = 200.0f;
                                    var_r31->unk_28 = 1.0f;
                                }
                                else {
                                    var_r31->unk_20 = -200.0f;
                                    var_r31->unk_28 = -1.0f;
                                }
                            }
                            if ((var_f31 < 0.0f) && (var_r31->unk_18 >= 2) && (var_r31->unk_1C == 0)) {
                                var_r31->unk_1C = 6;
                                var_r31->unk_24 = -200.0f;
                                var_r31->unk_28 = 0.0;
                                var_r31->unk_2C = -1.0f;
                            }
                            if ((var_f31 < -175.0f) && (var_f30 > 175.0f) && ((var_r31->unk_18 == 0) || (var_r31->unk_18 == 2))
                                && (var_r31->unk_1C == 0)) {
                                var_r31->unk_1C = 0xA;
                                var_r31->unk_20 = 0.0f;
                                var_r31->unk_24 = -200.0f;
                                var_r31->unk_28 = -1.0f;
                                var_r31->unk_2C = -1.0f;
                            }
                            break;
                    }
                    if (var_r31->unk_18 == -1) {
                        for (var_r30 = 0; var_r30 < 4; var_r30++) {
                            if ((var_r31->unk_100[var_r30] == 0)
                                && ((sp1E8 = sp394[var_r30].x - var_r31->unk_60[var_r25], sp1E4 = sp394[var_r30].z - var_r31->unk_80[var_r25],
                                        ((var_r22 == -1) != 0))
                                    || (((sp1E8 * sp1E8) + (sp1E4 * sp1E4)) < sp1F8))) {
                                var_r22 = var_r30;
                                sp1F8 = (sp1E8 * sp1E8) + (sp1E4 * sp1E4);
                            }
                        }
                        if (var_r22 != -1) {
                            var_r31->unk_18 = var_r22;
                        }
                    }
                    else {
                        var_r22 = var_r31->unk_18;
                    }
                    if ((var_r31->unk_18 != -1) && (var_r31->unk_1C == 0)) {
                        if (((var_r31->unk_58 < -0.95) || (var_r31->unk_58 > 0.95)) && ((var_r31->unk_5C < -0.95) || (var_r31->unk_5C > 0.95))
                            && (var_r31->unk_34 > 0xF) && (var_r31->unk_38 < 0x3C)) {
                            var_f29 = var_f30 < sp394[var_r31->unk_18].x ? 1 : (var_f30 > sp394[var_r31->unk_18].x ? -1 : 0);
                            var_f28 = var_f31 < sp394[var_r31->unk_18].z ? 1 : (var_f31 > sp394[var_r31->unk_18].z ? -1 : 0);
                        }
                        else {
                            var_f29 = var_f30 < sp394[var_r31->unk_18].x ? 1 : (var_f30 > sp394[var_r31->unk_18].x ? -1 : 0);
                            var_f28 = var_f31 < sp394[var_r31->unk_18].z ? 1 : (var_f31 > sp394[var_r31->unk_18].z ? -1 : 0);
                        }
                    }
                    else if (var_r31->unk_1C != 0) {
                        if (var_r31->unk_28 != 0.0f && !(var_r31->unk_28 < 0.0f ? (var_f30 < var_r31->unk_20) : (var_f30 > var_r31->unk_20))) {
                            var_f29 = var_r31->unk_28 < 0.0f ? (var_f30 > var_r31->unk_20 ? -1 : 0) : (var_f30 < var_r31->unk_20 ? 1 : 0);
                        }
                        else {
                            var_f29 = var_r31->unk_58 < -0.1 ? 1.0f : (var_r31->unk_58 > 0.1 ? -1.0f : (-10.0f * var_r31->unk_58));
                        }
                        if (var_r31->unk_2C != 0.0f && (var_r31->unk_2C < 0.0f ? (var_f31 < var_r31->unk_24) : (var_f31 > var_r31->unk_24)) == 0) {
                            var_f28 = var_r31->unk_2C < 0.0f ? (var_f31 > var_r31->unk_24 ? -1 : 0) : (var_f31 < var_r31->unk_24 ? 1 : 0);
                        }
                        else {
                            var_f28 = var_r31->unk_5C < -0.1 ? 1.0f : (var_r31->unk_5C > 0.1 ? -1.0f : (-10.0f * var_r31->unk_5C));
                        }
                    }
                    for (var_r30 = 0; var_r30 < 4; var_r30++) {
                        sp1E0 = var_r31->unk_60[var_r30] - var_r31->unk_160[var_r30];
                        sp1DC = var_r31->unk_80[var_r30] - var_r31->unk_170[var_r30];
                        if (((sp1E0 * sp1E0) + (sp1DC * sp1DC)) < 9.0f) {
                            var_r31->unk_150[var_r30]++;
                        }
                        else {
                            var_r31->unk_160[var_r30] = var_r31->unk_60[var_r30];
                            var_r31->unk_170[var_r30] = var_r31->unk_80[var_r30];
                            var_r31->unk_150[var_r30] = 0;
                        }
                    }
                    if (var_r31->unk_44 <= 0) {
                        var_r31->unk_3C = var_f29;
                        var_r31->unk_40 = var_f28;
                        var_r31->unk_44 = var_r31->unk_48;
                        var_r31->unk_48 -= (var_r31->unk_48 >= (var_r31->unk_48 / 10) ? (var_r31->unk_48 / 10) : 0);
                    }
                    else {
                        var_f29 = var_r31->unk_3C;
                        var_f28 = var_r31->unk_40;
                        var_r31->unk_44--;
                    }
                    var_f29 *= 0.5;
                    var_f28 *= -0.5;
                }
            }
            if (((var_f29 * var_f29) + (var_f28 * var_f28)) > 1.0f) {
                sp1D8 = sqrt((var_f29 * var_f29) + (var_f28 * var_f28));
                var_f29 *= 1.0f / sp1D8;
                var_f28 *= 1.0f / sp1D8;
            }
            if ((((var_f29 * var_f29) + (var_f28 * var_f28)) < 0.0625) && (var_r31->unk_208 == 0)) {
                var_f29 = 0.0f;
                var_f28 = 0.0f;
            }
        }
        sp1D4 = var_r31->unk_58;
        sp1D0 = var_r31->unk_5C;
        var_r31->unk_58 = var_r31->unk_58 + (var_f29 / 3.0f);
        var_r31->unk_58 = var_r31->unk_58 < -1.0f ? -1.0f : (var_r31->unk_58 > 1.0f ? 1.0f : var_r31->unk_58);
        var_r31->unk_5C = var_r31->unk_5C + (-var_f28 / 3.0f);
        var_r31->unk_5C = var_r31->unk_5C < -1.0f ? -1.0f : (var_r31->unk_5C > 1.0f ? 1.0f : var_r31->unk_5C);
        var_r31->unk_208 = ((var_r31->unk_58 == 0.0f) && (var_r31->unk_5C == 0.0f)) ? 0 : var_r31->unk_208;
        if ((lbl_1_bss_48 == 0x3EC) && ((sp1D4 != var_r31->unk_58) || (sp1D0 != var_r31->unk_5C))) {
            if (var_r31->unk_214 == -1) {
                var_r31->unk_214 = HuAudFXPlay(0x7A6);
            }
        }
        else {
            if (var_r31->unk_214 != -1) {
                HuAudFXStop(var_r31->unk_214);
            }
            var_r31->unk_214 = -1;
        }
        if (lbl_1_bss_48 >= 0x3ED) {
            sp1CC = 0.666f;
            sp1C8 = 0.9f;
            var_r31->unk_5C = var_r31->unk_5C > sp1CC
                ? ((var_r31->unk_5C * sp1C8) + (sp1CC * (1.0f - sp1C8)))
                : (var_r31->unk_5C < -sp1CC ? ((var_r31->unk_5C * sp1C8) - (sp1CC * (1.0f - sp1C8))) : var_r31->unk_5C);
        }
        if (var_r31->unk_4C != 2) {
            for (var_r18 = 0; var_r18 < 2; var_r18++) {
                for (var_r30 = 0; var_r30 < 4; var_r30++) {
                    var_r31->unk_110[var_r30] = var_r31->unk_120[var_r30] = var_r31->unk_130[var_r30] = var_r31->unk_140[var_r30] = 0;
                    if (var_r31->unk_F0[var_r30] == 0) {
                        var_r31->unk_90[var_r30] += 0.13888888888888887 * var_r31->unk_58 * (var_r31->unk_208 != 0 ? 0 : 1)
                            * (var_r31->unk_70[var_r30] >= 0.0f ? 1.0f : (1.0f - (var_r31->unk_70[var_r30] / -25.0f)));
                        var_r31->unk_B0[var_r30] += 0.13888888888888887 * var_r31->unk_5C * (var_r31->unk_208 != 0 ? 0 : 1)
                            * (var_r31->unk_70[var_r30] >= 0.0f ? 1.0f : (1.0f - (var_r31->unk_70[var_r30] / -25.0f)));
                        var_r31->unk_70[var_r30] += var_r31->unk_A0[var_r30];
                        var_r31->unk_38 += var_r31->unk_38 < 0x8000;
                        var_f27
                            = sqrtf((var_r31->unk_90[var_r30] * var_r31->unk_90[var_r30]) + (var_r31->unk_B0[var_r30] * var_r31->unk_B0[var_r30]));
                        sp1C4 = var_r31->unk_90[var_r30];
                        sp1C0 = var_r31->unk_B0[var_r30];
                        if (var_f27 > 0.0f) {
                            if (var_f27 > 7.59375) {
                                var_r31->unk_90[var_r30] *= 7.5 / var_f27;
                                var_r31->unk_B0[var_r30] *= 7.5 / var_f27;
                            }
                            else {
                                var_r31->unk_90[var_r30] *= (var_f27 < 0.09375 ? 0.0 : (var_f27 - 0.09375)) / var_f27;
                                var_r31->unk_B0[var_r30] *= (var_f27 < 0.09375 ? 0.0 : (var_f27 - 0.09375)) / var_f27;
                            }
                        }
                        var_r31->unk_60[var_r30] += var_r31->unk_90[var_r30];
                        var_r31->unk_80[var_r30] += var_r31->unk_B0[var_r30];
                        var_f27
                            = sqrtf((var_r31->unk_90[var_r30] * var_r31->unk_90[var_r30]) + (var_r31->unk_B0[var_r30] * var_r31->unk_B0[var_r30]));
                        for (var_r28 = 0; var_r28 < 4; var_r28++) {
                            sp1BC = var_r31->unk_60[var_r30] - var_r31->unk_60[var_r28];
                            sp1B8 = var_r31->unk_80[var_r30] - var_r31->unk_80[var_r28];
                            var_f24 = sqrtf((sp1BC * sp1BC) + (sp1B8 * sp1B8));
                            if ((var_r30 != var_r28) && (var_r31->unk_F0[var_r28] == 0) && (var_f24 > 0.0f) && (var_f24 < 62.5)) {
                                var_f20 = sp1BC / var_f24;
                                var_f19 = sp1B8 / var_f24;
                                sp1B4 = var_r31->unk_90[var_r30];
                                sp1B0 = var_r31->unk_B0[var_r30];
                                var_f18 = (var_r31->unk_90[var_r30] + var_r31->unk_90[var_r28]) / 2.0;
                                sp1A4 = (var_r31->unk_B0[var_r30] + var_r31->unk_B0[var_r28]) / 2.0;
                                sp1AC = (var_f20 * -(var_r31->unk_90[var_r30] - var_f18)) - (var_f19 * (var_r31->unk_B0[var_r30] - sp1A4));
                                sp1A8 = (-var_f20 * -(var_r31->unk_90[var_r28] - var_f18)) - (-var_f19 * (var_r31->unk_B0[var_r28] - sp1A4));
                                var_r31->unk_60[var_r30] += var_f20 * (0.1 + (62.5 - var_f24)) / 2.0;
                                var_r31->unk_80[var_r30] += var_f19 * (0.1 + (62.5 - var_f24)) / 2.0;
                                var_r31->unk_60[var_r28] -= var_f20 * (0.1 + (62.5 - var_f24)) / 2.0;
                                var_r31->unk_80[var_r28] -= var_f19 * (0.1 + (62.5 - var_f24)) / 2.0;
                                var_r31->unk_90[var_r30] = var_f18 + (0.75 * ((var_r31->unk_90[var_r30] - var_f18) + (2.0f * var_f20 * sp1AC)));
                                var_r31->unk_B0[var_r30] = sp1A4 + (0.75 * ((var_r31->unk_B0[var_r30] - sp1A4) + (2.0f * var_f19 * sp1AC)));
                                var_r31->unk_90[var_r28] = var_f18 + (0.75 * ((var_r31->unk_90[var_r28] - var_f18) + (2.0f * -var_f20 * sp1A8)));
                                var_r31->unk_B0[var_r28] = sp1A4 + (0.75 * ((var_r31->unk_B0[var_r28] - sp1A4) + (2.0f * -var_f19 * sp1A8)));
                                var_r31->unk_110[var_r30] = 1 << var_r28;
                                if (((var_r31->unk_90[var_r30] + var_r31->unk_B0[var_r30]) > 0.0) && (var_r31->unk_1C4[var_r30] > 0xF)
                                    && (var_r31->unk_1C4[var_r28] > 0xF) && (lbl_1_bss_64[1].unk_00 < 2)) {
                                    lbl_1_bss_64[1].unk_04[lbl_1_bss_64[1].unk_00] = 0.0f;
                                    lbl_1_bss_64[1].unk_00++;
                                }
                                var_r31->unk_1C4[var_r30] = 0;
                                var_r31->unk_1C4[var_r28] = 0;
                            }
                        }
                        for (var_r28 = 0; var_r28 < 4; var_r28++) {
                            sp1A0 = var_r31->unk_60[var_r30] - var_r31->unk_60[var_r28];
                            sp19C = var_r31->unk_80[var_r30] - var_r31->unk_80[var_r28];
                            sp198 = sqrtf((sp1A0 * sp1A0) + (sp19C * sp19C));
                            if ((var_r31->unk_F0[var_r28] != 0) && (var_f27 > 0.0f)) {
                                if (sp198 < 62.5) {
                                    sp194 = sp1A0 / sp198;
                                    sp190 = sp19C / sp198;
                                    sp18C = var_r31->unk_90[var_r30];
                                    sp188 = var_r31->unk_B0[var_r30];
                                    sp184 = (-sp18C * sp194) - (sp188 * sp190);
                                    var_r31->unk_60[var_r30] += sp194 * (0.1 + (62.5 - sp198));
                                    var_r31->unk_80[var_r30] += sp190 * (0.1 + (62.5 - sp198));
                                    var_r31->unk_90[var_r30] = 0.75 * (sp18C + (2.0f * sp194 * sp184));
                                    var_r31->unk_B0[var_r30] = 0.75 * (sp188 + (2.0f * sp190 * sp184));
                                    var_r31->unk_60[var_r30] += var_r31->unk_90[var_r30];
                                    var_r31->unk_80[var_r30] += var_r31->unk_B0[var_r30];
                                    var_r31->unk_34 = var_r31->unk_30 == (var_r28 + 1) ? (var_r31->unk_34 + 1) : 1;
                                    var_r31->unk_30 = var_r28 + 1;
                                    var_r31->unk_38 = 0;
                                    var_r31->unk_120[var_r30] = 1 << var_r28;
                                    if (((var_r31->unk_90[var_r30] + var_r31->unk_B0[var_r30]) > 0.0) && (var_r31->unk_1C4[var_r30] > 0xF)
                                        && (var_r31->unk_1C4[var_r28] > 0xF) && (lbl_1_bss_64[1].unk_00 < 2)) {
                                        lbl_1_bss_64[1].unk_04[lbl_1_bss_64[1].unk_00] = 0.0f;
                                        lbl_1_bss_64[1].unk_00++;
                                    }
                                    var_r31->unk_1C4[var_r30] = 0;
                                    var_r31->unk_1C4[var_r28] = 0;
                                }
                            }
                        }
                        for (var_r28 = 0; var_r28 < (lbl_1_data_230[var_r31->unk_190] == 2 ? 2 : 3); var_r28++) {
                            sp180 = var_r31->unk_60[var_r30] - sp3C4[var_r28].x;
                            sp17C = var_r31->unk_80[var_r30] - sp3C4[var_r28].z;
                            sp178 = sqrtf((sp180 * sp180) + (sp17C * sp17C));
                            if ((sp178 > 0.0f) && (sp178 < 62.5)) {
                                sp174 = sp180 / sp178;
                                sp170 = sp17C / sp178;
                                sp16C = var_r31->unk_90[var_r30];
                                sp168 = var_r31->unk_B0[var_r30];
                                sp164 = (-sp16C * sp174) - (sp168 * sp170);
                                var_r31->unk_60[var_r30] += sp174 * (0.1 + (62.5 - sp178));
                                var_r31->unk_80[var_r30] += sp170 * (0.1 + (62.5 - sp178));
                                var_r31->unk_90[var_r30] = 0.75 * (sp16C + (2.0f * sp174 * sp164));
                                var_r31->unk_B0[var_r30] = 0.75 * (sp168 + (2.0f * sp170 * sp164));
                                var_r31->unk_60[var_r30] += var_r31->unk_90[var_r30];
                                var_r31->unk_80[var_r30] += var_r31->unk_B0[var_r30];
                                var_r31->unk_34 = var_r31->unk_30 == (var_r28 + 5) ? (var_r31->unk_34 + 1) : 1;
                                var_r31->unk_30 = var_r28 + 5;
                                var_r31->unk_38 = 0;
                                var_r31->unk_130[var_r30] = 1 << var_r28;
                                if (((var_r31->unk_90[var_r30] + var_r31->unk_B0[var_r30]) > 0.0) && (var_r31->unk_1C4[var_r30] > 0xF)
                                    && (lbl_1_bss_64[1].unk_00 < 2)) {
                                    lbl_1_bss_64[1].unk_04[lbl_1_bss_64[1].unk_00] = 0.0f;
                                    lbl_1_bss_64[1].unk_00++;
                                }
                                var_r31->unk_1C4[var_r30] = 0;
                            }
                        }
                        if (((var_r31->unk_60[var_r30] - 37.5) < -250.0) || ((37.5 + var_r31->unk_60[var_r30]) > 250.0)) {
                            var_r31->unk_60[var_r30] = (var_r31->unk_60[var_r30] - 37.5) < -250.0 ? -212.5 : 212.5;
                            var_r31->unk_90[var_r30] *= -0.75;
                            var_r31->unk_60[var_r30] += var_r31->unk_90[var_r30];
                            if (((var_r31->unk_90[var_r30] + var_r31->unk_B0[var_r30]) > 0.0) && (var_r31->unk_1C4[var_r30] > 0xF)
                                && (lbl_1_bss_64[1].unk_00 < 2)) {
                                lbl_1_bss_64[1].unk_04[lbl_1_bss_64[1].unk_00] = 0.0f;
                                lbl_1_bss_64[1].unk_00++;
                            }
                            var_r31->unk_1C4[var_r30] = 0;
                        }
                        if (((var_r31->unk_80[var_r30] - 37.5) < -250.0) || ((37.5 + var_r31->unk_80[var_r30]) > 250.0)) {
                            var_r31->unk_80[var_r30] = (var_r31->unk_80[var_r30] - 37.5) < -250.0 ? -212.5 : 212.5;
                            var_r31->unk_B0[var_r30] *= -0.75;
                            var_r31->unk_80[var_r30] += var_r31->unk_B0[var_r30];
                            if (((var_r31->unk_90[var_r30] + var_r31->unk_B0[var_r30]) > 0.0) && (var_r31->unk_1C4[var_r30] > 0xF)
                                && (lbl_1_bss_64[1].unk_00 < 2)) {
                                lbl_1_bss_64[1].unk_04[lbl_1_bss_64[1].unk_00] = 0.0f;
                                lbl_1_bss_64[1].unk_00++;
                            }
                            var_r31->unk_1C4[var_r30] = 0;
                        }
                        var_r21 = 0;
                        for (var_r21 = 0; var_r21 < 0x10; var_r21++) {
                            var_r31->unk_1C4[var_r21]++;
                        }
                        sp160 = 0;
                        for (var_r28 = 0; var_r28 < 4; var_r28++) {
                            sp15C = var_r31->unk_60[var_r30] - sp394[var_r28].x;
                            sp158 = ((sp15C == 0.0f) && (var_r31->unk_80[var_r30] == sp394[var_r28].z))
                                ? 1e-10
                                : (var_r31->unk_80[var_r30] - sp394[var_r28].z);
                            var_f23 = sqrtf((sp15C * sp15C) + (sp158 * sp158));
                            sp154 = 0;
                            for (var_r20 = 0; var_r20 < 4; var_r20++) {
                                if (((var_r31->unk_110[var_r30] & (1 << var_r20)) != 0) && (var_r31->unk_130[var_r20] != 0)) {
                                    sp154 = 1;
                                }
                            }
                            if ((var_r31->unk_0C != -1) && (lbl_1_data_230[var_r31->unk_190] == 1) && (var_r28 == 3)) {
                                if (var_r31->unk_180[var_r30] > 0) {
                                    var_f23 = 1000.0f;
                                    var_r31->unk_180[var_r30]--;
                                }
                                for (var_r27 = 0; var_r27 < 4; var_r27++) {
                                    if ((var_r31->unk_00 == 0) && ((HuPadBtn[0] & PAD_BUTTON_B) != 0)) {
                                        OSReport("%d | %d\n%d | %d\n%f,%f\n%f,%f\n", var_r31->unk_110[var_r30], 1 << var_r27,
                                            var_r31->unk_110[var_r27], 1 << var_r30, var_r31->unk_60[var_r30], var_r31->unk_80[var_r30],
                                            var_r31->unk_60[var_r27], var_r31->unk_80[var_r27]);
                                    }
                                    if ((((var_r31->unk_110[var_r30] & (1 << var_r27)) != 0) || ((var_r31->unk_110[var_r27] & (1 << var_r30)) != 0))
                                        && (var_r31->unk_80[var_r27] > var_r31->unk_80[var_r30]) && (var_r31->unk_60[var_r30] < 100.0f)
                                        && (var_r31->unk_60[var_r30] > -100.0f) && (var_r31->unk_80[var_r30] > 150.0f)
                                        && (var_r31->unk_60[var_r27] < 100.0f) && (var_r31->unk_60[var_r27] > -100.0f)
                                        && (var_r31->unk_80[var_r27] > 150.0f)) {
                                        var_f23 = 1000.0f;
                                        var_r31->unk_180[var_r30] = 3;
                                    }
                                }
                            }
                            if ((sp154 == 0) && (var_f23 < 37.5)) {
                                sp150 = sp15C / var_f23;
                                sp14C = sp158 / var_f23;
                                sp148 = 37.5 * sind((90.0 * (-var_r31->unk_70[var_r30] / 37.5)));
                                sp144 = var_r31->unk_70[var_r30] <= -37.5 ? 90.0 : (asind(1.0 + (var_r31->unk_70[var_r30] / 37.5)));
                                var_r31->unk_140[var_r30] = 1 << var_r28;
                                sp140 = sqrtf((var_r31->unk_B0[var_r30] * var_r31->unk_B0[var_r30])
                                    + ((var_r31->unk_90[var_r30] * var_r31->unk_90[var_r30])
                                        + (var_r31->unk_A0[var_r30] * var_r31->unk_A0[var_r30])));
                                sp13C = sqrtf(
                                    (var_r31->unk_90[var_r30] * var_r31->unk_90[var_r30]) + (var_r31->unk_B0[var_r30] * var_r31->unk_B0[var_r30]));
                                sp138 = atan2d(var_r31->unk_A0[var_r30], sp13C);
                                var_r31->unk_90[var_r30] -= 0.375 * sp150;
                                var_r31->unk_B0[var_r30] -= 0.375 * sp14C;
                                var_r31->unk_60[var_r30] -= 0.375 * sp150;
                                var_r31->unk_80[var_r30] -= 0.375 * sp14C;
                                if (var_r31->unk_70[var_r30] < (-25.0 * sind((90.0 * (1.0 - (var_f23 / 37.5)))))) {
                                    var_r31->unk_70[var_r30] = -25.0 * sind((90.0 * (1.0 - (var_f23 / 37.5))));
                                }
                                if ((var_r31->unk_70[var_r30] <= -24.5) && (var_f23 < 0.75)) {
                                    var_r31->unk_70[var_r30] = -25.0f;
                                    var_r31->unk_A0[var_r30] = 0.0f;
                                    var_r31->unk_F0[var_r30] = 1;
                                    var_r31->unk_100[var_r28] = 1;
                                    var_r31->unk_48 = lbl_1_rodata_10[var_r31->unk_10];
                                    if (lbl_1_bss_64[2].unk_00 < 2) {
                                        lbl_1_bss_64[2].unk_04[lbl_1_bss_64[2].unk_00] = 0.0f;
                                        lbl_1_bss_64[2].unk_00++;
                                    }
                                    omVibrate(var_r31->unk_04, 0xC, 6, 6);
                                }
                            }
                            else {
                                sp160++;
                            }
                            if (var_r28 == 3) {
                                if ((sp160 == 4) && (var_r31->unk_70[var_r30] < 0.0f)) {
                                    var_r31->unk_70[var_r30] = 0.0f;
                                    var_r31->unk_A0[var_r30] *= -0.0;
                                }
                                else {
                                    var_r31->unk_A0[var_r30] += -0.1875;
                                }
                            }
                        }
                        sp134 = atan2d(sp1C4, sp1C0);
                        sp130 = atan2d(var_r31->unk_90[var_r30], var_r31->unk_B0[var_r30]);
                        var_f22
                            = sqrtf((var_r31->unk_90[var_r30] * var_r31->unk_90[var_r30]) + (var_r31->unk_B0[var_r30] * var_r31->unk_B0[var_r30]));
                        var_f25 = sp130 - sp134;
                        var_f25 += var_f25 < -180.0f ? 0x168 : (var_f25 > 180.0f ? -0x168 : 0);
                        var_f25 += var_f25 < -180.0f ? 0x168 : (var_f25 > 180.0f ? -0x168 : 0);
                        var_f22 = var_f22 <= (1.03125 * sqrt(0.03858024691358024)) ? 0.0f : var_f22;
                        var_r31->unk_D0[var_r30]
                            -= (2.625 * ((var_f22 * (var_f25 < -90.0f ? -1.0 : (var_f25 > 90.0f ? 1.0 : (var_f25 / 90.0)))) / 3.75));
                        var_r31->unk_D0[var_r30] = var_r31->unk_D0[var_r30] >= 7.875 ? 7.875 : var_r31->unk_D0[var_r30];
                        var_r31->unk_C0[var_r30] += var_r31->unk_D0[var_r30];
                        var_r31->unk_C0[var_r30] += var_r31->unk_C0[var_r30] < -180.0f ? 0xB4 : (var_r31->unk_C0[var_r30] > 180.0f ? -0xB4 : 0);
                        if (fabs(var_f22) < fabs(var_r31->unk_E0[var_r30])) {
                            var_r31->unk_D0[var_r30]
                                = var_r31->unk_E0[var_r30] == 0.0f ? 0.0f : ((var_r31->unk_D0[var_r30] * var_f22) / var_r31->unk_E0[var_r30]);
                        }
                        var_r31->unk_E0[var_r30] = var_f22;
                    }
                }
            }
        }
        Hu3DModelRotSet(var_r29->model[var_r31->unk_190 + 1], 10.0f * var_r31->unk_5C, 0.0f, 10.0f * -var_r31->unk_58);
        Hu3DModelRotSet(var_r29->model[11], 10.0f * var_r31->unk_5C, 0.0f, 10.0f * -(var_r31->unk_58));
        if (lbl_1_bss_48 == 0x3EB) {
            sp12C = var_r29->rot.y;
            sp128 = 180.0 + ((8.0f * var_r31->unk_58) * (0.125 + ((0.6 + var_r31->unk_5C) / 0.875)));
            var_r29->rot.y = (3.0f + sp12C) < sp128 ? (3.0f + sp12C) : ((sp12C - 3.0f) > sp128 ? (sp12C - 3.0f) : sp128);
            if (lbl_1_bss_4C == 0xA) {
                Hu3DMotionShiftSet(var_r29->model[0], var_r29->motion[1], 39.0 * (0.5 + (0.5 * var_r31->unk_5C)), 20.0f, HU3D_MOTATTR_PAUSE);
            }
        }
        else if (lbl_1_bss_48 == 0x3EC) {
            omSetRot(var_r29, 0.0f, 180.0 + ((8.0f * var_r31->unk_58) * (0.125 + ((0.6 + var_r31->unk_5C) / 0.875))), 0.0f);
            Hu3DMotionTimeSet(var_r29->model[0], 39.0 * (0.5 + (0.5 * var_r31->unk_5C)));
        }
        else if (lbl_1_bss_48 == 0x3ED) {
            if (lbl_1_bss_4C == 1) {
                Hu3DModelAttrReset(var_r29->model[0], HU3D_MOTATTR_PAUSE);
                Hu3DMotionShiftSet(var_r29->model[0], var_r29->motion[0], 0.0f, 12.0f, HU3D_MOTATTR_LOOP);
            }
            if (lbl_1_bss_4C >= 0x19) {
                var_r29->rot.y *= 0.8;
            }
        }
        else if (lbl_1_bss_48 >= 0x3EE) {
            var_r29->rot.y = 0.0f;
            if ((lbl_1_bss_4C == 1) && (lbl_1_bss_48 == 0x3EE)) {
                if ((var_r31->unk_00 != lbl_1_bss_30) && (var_r31->unk_08 != -1)) {
                    s32 sp2E4[8] = { 0x121, 0x161, 0x1A1, 0x1E1, 0x221, 0x261, 0x2A1, 0x2E1 };
                    HuAudFXPlay(sp2E4[var_r31->unk_08]);
                }
                Hu3DMotionShiftSet(var_r29->model[0], var_r29->motion[var_r31->unk_00 == lbl_1_bss_30 ? 2 : 3], 0.0f, 8.0f,
                    ((var_r31->unk_00 == lbl_1_bss_30) && (var_r31->unk_08 == -1)) ? 0x40000001 : 0);
            }
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            lbl_1_bss_18 = var_r31->unk_C0[var_r30];
            lbl_1_bss_18 = lbl_1_bss_18 < -180.0f ? (360.0f + lbl_1_bss_18) : (lbl_1_bss_18 > 180.0f ? (lbl_1_bss_18 - 360.0f) : lbl_1_bss_18);
            sp124 = ((-90.175 <= lbl_1_bss_18) && (lbl_1_bss_18 <= -90.0f)) != 0
                ? -90.175
                : ((-90.0f <= lbl_1_bss_18) && (lbl_1_bss_18 <= -89.825) ? -89.825 : lbl_1_bss_18);
            PSMTXRotRad(sp304, 0x78, 0.017453292f * (10.0f * var_r31->unk_5C));
            PSMTXRotRad(sp364, 0x7A, 0.017453292f * (10.0f * -var_r31->unk_58));
            PSMTXConcat(sp364, sp304, sp364);
            PSMTXRotRad(sp304, 0x79, 0.017453292f * sp124);
            PSMTXRotRad(sp334, 0x78, 0.017453292f * (15.0f * var_r31->unk_5C));
            PSMTXConcat(sp334, sp304, sp334);
            PSMTXRotRad(sp304, 0x7A, 0.017453292f * (15.0f * -var_r31->unk_58));
            PSMTXConcat(sp304, sp334, sp334);
            Hu3DMtxRotGet(sp334, &sp2A8);
            sp2B4.x = var_r31->unk_60[var_r30];
            sp2B4.y = var_r31->unk_70[var_r30];
            sp2B4.z = var_r31->unk_80[var_r30];
            PSMTXMultVec(sp364, &sp2B4, &sp2B4);
            Hu3DModelPosSet(var_r29->model[var_r30 + 0xC], sp2D8.x + sp2B4.x, sp2D8.y + sp2B4.y, sp2D8.z + sp2B4.z);
            Hu3DModelRotSet(var_r29->model[var_r30 + 0xC], 10.0f * var_r31->unk_5C, 0.0f, 10.0f * -var_r31->unk_58);
            Hu3DModelRotSet(var_r29->model[var_r30 + 0xC], sp2A8.x, sp2A8.y, sp2A8.z);
        }
    }
}

s32 lbl_1_data_284 = -1;
float lbl_1_data_288 = 700.0f;
float lbl_1_data_28C = 314.0f;
float lbl_1_data_290 = -100.0f;
float lbl_1_data_294 = -30.0f;

void fn_1_6850(omObjData *object)
{
    M449DllWork *sp20[2];
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    float var_f31;
    float var_f30;
    float var_f29;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        sp20[var_r31] = (&lbl_1_bss_54)[var_r31]->data;
    }
    lbl_1_bss_4++;
    if (lbl_1_bss_48 == 0x3EC) {
        lbl_1_bss_14++;
    }
    var_r27 = 0;
    var_r26 = 0;
    var_r25 = 0;
    var_r24 = 0;
    if ((sp20[0]->unk_190 == 2) && (sp20[0]->unk_F0[0] != 0)) {
        var_r24 = 1;
    }
    if ((var_r24 != 0) && (sp20[0]->unk_F0[1] != 0)) {
        var_r25 = 1;
    }
    if ((var_r25 != 0) && (sp20[0]->unk_F0[2] != 0)) {
        var_r26 = 1;
    }
    if ((var_r26 != 0) && (sp20[0]->unk_F0[3] != 0)) {
        var_r27 = 1;
    }
    var_r30 = var_r27;
    var_r23 = 0;
    var_r22 = 0;
    var_r21 = 0;
    var_r20 = 0;
    if ((sp20[1]->unk_190 == 2) && (sp20[1]->unk_F0[0] != 0)) {
        var_r20 = 1;
    }
    if ((var_r20 != 0) && (sp20[1]->unk_F0[1] != 0)) {
        var_r21 = 1;
    }
    if ((var_r21 != 0) && (sp20[1]->unk_F0[2] != 0)) {
        var_r22 = 1;
    }
    if ((var_r22 != 0) && (sp20[1]->unk_F0[3] != 0)) {
        var_r23 = 1;
    }
    var_r29 = var_r23;
    lbl_1_bss_30 = lbl_1_bss_30 == -1 ? ((var_r30 != 0) && (var_r29 != 0) ? (rand8() % 2) : (var_r30 != 0 ? 0 : (var_r29 != 0 ? 1 : lbl_1_bss_30)))
                                      : lbl_1_bss_30;
    lbl_1_bss_30 = ((lbl_1_bss_30 == -1) && (lbl_1_bss_14 >= 0x4650)) != 0
        ? (sp20[0]->unk_190 > sp20[1]->unk_190 ? 0 : (sp20[0]->unk_190 < sp20[1]->unk_190 ? 1 : 4))
        : lbl_1_bss_30;
    var_r28 = lbl_1_data_284;
    {
        UnkCameraStruct sp28[4] = {
            { 2500.0f, 0.0f, 0.0f, -100.0f, -40.0f, 0.0f },
            { 700.0f, 0.0f, 0.0f, -750.0f, -30.0f, 0.0f },
            { 775.0f, -350.0f, -27.0f, 400.0f, -25.0f, -7.0f },
            { 775.0f, 350.0f, -27.0f, 400.0f, -25.0f, 7.0f },
        };
        if (lbl_1_data_284 == -1) {
            lbl_1_data_284 = 1;
            lbl_1_bss_1C = 1;
            lbl_1_bss_20 = 1.0f;
        }
        if ((lbl_1_bss_48 == 0x3E9) && (lbl_1_data_284 == 1)) {
            lbl_1_data_284 = 0;
            lbl_1_bss_1C = 1;
            lbl_1_bss_20 = 0.0f;
        }
        if ((lbl_1_bss_48 == 0x3EE) && (lbl_1_bss_4C == 1) && (lbl_1_bss_30 == 0)) {
            lbl_1_data_284 = 2;
            lbl_1_bss_1C = 0;
            lbl_1_bss_20 = 0.0f;
        }
        if ((lbl_1_bss_48 == 0x3EE) && (lbl_1_bss_4C == 1) && (lbl_1_bss_30 == 1) && (sp20[1]->unk_08 != -1)) {
            lbl_1_data_284 = 3;
            lbl_1_bss_1C = 0;
            lbl_1_bss_20 = 0.0f;
        }
        if ((var_r28 != lbl_1_data_284) && (var_r28 != -1)) {
            lbl_1_data_288 = CZoom;
            lbl_1_data_28C = Center.y;
            lbl_1_data_290 = Center.z;
            lbl_1_data_294 = CRot.x;
        }
        if (lbl_1_bss_20 <= 1.0f) {
            if (lbl_1_bss_1C == 0) {
                lbl_1_bss_20 = 1.0 - (0.95 * (1.0f - lbl_1_bss_20));
                var_f31 = lbl_1_bss_20;
            }
            else {
                lbl_1_bss_20 += 0.008333333333333333;
                lbl_1_bss_20 = lbl_1_bss_20 > 1.0f ? 1.0f : lbl_1_bss_20;
                var_f31 = 0.5 + (-0.5 * cosd((180.0f * lbl_1_bss_20)));
            }
            lbl_1_bss_20 = lbl_1_bss_20 > 1.0f ? 1.0f : lbl_1_bss_20;
            CZoom = (var_f31 * sp28[lbl_1_data_284].unk_00) + (lbl_1_data_288 * (1.0f - var_f31));
            Center.x = (var_f31 * sp28[lbl_1_data_284].unk_04) + (lbl_1_bss_24 * (1.0f - var_f31));
            Center.y = (var_f31 * sp28[lbl_1_data_284].unk_08) + (lbl_1_data_28C * (1.0f - var_f31));
            Center.z = (var_f31 * sp28[lbl_1_data_284].unk_0C) + (lbl_1_data_290 * (1.0f - var_f31));
            CRot.x = (var_f31 * sp28[lbl_1_data_284].unk_10) + (lbl_1_data_294 * (1.0f - var_f31));
            CRot.y = (var_f31 * sp28[lbl_1_data_284].unk_14) + (lbl_1_bss_28 * (1.0f - var_f31));
        }
    }
}

static const u32 lbl_1_rodata_580[6] = { 0x2C0003, 0x2C0004, 0x2C0005, 0x2C0006, 0x2C0007, 0 };

void fn_1_71A8(void)
{
    M449DllWork *sp8[2];

    s16 var_r31;
    s32 var_r30;
    s16 var_r29;
    s32 var_r28;
    s32 var_r27;
    u32 var_r26;

    var_r29 = 0;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        sp8[var_r30] = (&lbl_1_bss_54)[var_r30]->data;
    }
    HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 0x3C);
    HuWinComKeyReset();
    var_r31 = HuWinExCreateStyled(-10000.0f, 60.0f, 0x118, 0x78, -1, 1);
    HuWinExAnimIn(var_r31);
    HuWinBGTPLvlSet(var_r31, 0.8f);
    HuWinMesSpeedSet(var_r31, 1);
    HuWinDisablePlayerSet(
        var_r31, 0xF & ((sp8[0]->unk_0C != -1) ? ~(1 << sp8[0]->unk_0C) : 0xF) & ((sp8[1]->unk_0C != -1) ? ~(1 << sp8[1]->unk_0C) : 0xF));
    HuWinMesColSet(var_r31, 0);
    HuWinMesSet(var_r31, 0x2C0001);
    if (((sp8[0]->unk_0C == -1) || (sp8[0]->unk_08 == -1)) && ((sp8[1]->unk_0C == -1) || (sp8[1]->unk_08 == -1))) {
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 0x3C);
    }
    HuWinMesWait(var_r31);
    if ((sp8[0]->unk_0C != -1) || (sp8[1]->unk_0C != -1)) {
        HuWinMesColSet(var_r31, 0);
        HuWinMesSet(var_r31, 0x2C0002);
        if ((sp8[0]->unk_0C == -1) && (sp8[1]->unk_0C == -1)) {
            HuPrcSleep(0x3C);
            var_r29 = 1;
        }
        else {
            var_r29 = HuWinChoiceGet(var_r31, 0);
        }
    }
    else {
        var_r29 = 1;
    }
    if (var_r29 == 0) {
        var_r30 = 0;
        while ((var_r26 = lbl_1_rodata_580[var_r30++]) != 0) {
            HuWinMesColSet(var_r31, 0);
            HuWinMesSet(var_r31, var_r26);
            if ((sp8[0]->unk_0C == -1 || sp8[0]->unk_08 == -1) && (sp8[1]->unk_0C == -1 || sp8[1]->unk_08 == -1)) {
                HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
            }
            HuWinMesWait(var_r31);
        }
    }
    else {
        HuWinMesColSet(var_r31, 0);
        HuWinMesSet(var_r31, 0x2C0008);
        if (((sp8[0]->unk_0C == -1) || (sp8[0]->unk_08 == -1)) && ((sp8[1]->unk_0C == -1) || (sp8[1]->unk_08 == -1))) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
        }
        HuWinMesWait(var_r31);
    }
    HuWinExAnimOut(var_r31);
    HuWinExCleanup(var_r31);
    lbl_1_bss_10 = 0;
    HuPrcEnd();
}

void fn_1_7544(omObjData *var_r29)
{
    M449DllWork *spC[2];
    s32 sp8;

    s32 var_r31;
    s32 var_r30;

    for (var_r31 = 0; var_r31 < 0xC; var_r31++) {
        s32 sp14[12] = { 0x7A2, 0x7A3, 0x7A4, 0x7A5, 0, 0, 0, 0, 0, 0, 0, 0 };
        if (lbl_1_bss_64[var_r31].unk_00 > 3) {
            lbl_1_bss_64[var_r31].unk_00 = 3;
        }
        if ((lbl_1_bss_64[var_r31].unk_00 > 0) && (var_r31 != 1)) {
            sp8 = HuAudFXPlay(sp14[var_r31]);
            lbl_1_bss_64[var_r31].unk_00--;
        }
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        spC[var_r31] = (&lbl_1_bss_54)[var_r31]->data;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        var_r29->func = fn_1_9A38;
    }
    switch (lbl_1_bss_48) {
        case 0x3E8:
            if (WipeStatGet() == 0) {
                lbl_1_bss_48++;
                lbl_1_bss_4C = 0;
                return;
            }
            break;
        case 0x3E9:
            lbl_1_bss_4C++;
            if (lbl_1_bss_4C > 0x78) {
                lbl_1_bss_48++;
                if ((spC[0]->unk_08 != -1) && (spC[1]->unk_08 != -1)) {
                    lbl_1_bss_48++;
                }
                lbl_1_bss_44 = 0;
                lbl_1_bss_4C = 0;
                return;
            }
            break;
        case 0x3EA:
            lbl_1_bss_4C++;
            if (lbl_1_bss_4C == 1) {
                HuPrcChildCreate(fn_1_71A8, 0x64, 0x2000, 0, HuPrcCurrentGet());
                lbl_1_bss_10 = 1;
                if (lbl_1_data_22C == -1) {
                    lbl_1_data_22C = HuAudSeqPlay(0x3D);
                    return;
                }
            }
            else if (lbl_1_bss_10 == 0) {
                lbl_1_bss_48++;
                if (lbl_1_data_22C != -1) {
                    HuAudSeqFadeOut(lbl_1_data_22C, 0x3E8);
                    lbl_1_data_22C = -1;
                }
                lbl_1_bss_4C = 0;
                return;
            }
            break;
        case 0x3EB:
            lbl_1_bss_4C++;
            if ((lbl_1_bss_4C == 5) && (lbl_1_data_228 < 0)) {
                lbl_1_data_228 = MGSeqCreate(3, 0);
            }
            if ((lbl_1_bss_4C >= 5) && (lbl_1_data_22C == -1) && ((MGSeqStatGet(lbl_1_data_228) & 0x10) != 0)) {
                lbl_1_data_22C = HuAudSeqPlay(0x3E);
            }
            if ((lbl_1_bss_4C >= 5) && (MGSeqStatGet(lbl_1_data_228) == 0) && (lbl_1_data_228 >= 0)) {
                for (var_r30 = 0; var_r30 < 0x12; var_r30++) {
                    if (((var_r30 % 9) < 5) || ((var_r30 % 9) > 7)) {
                        espDispOn(lbl_1_data_48[var_r30]);
                    }
                }
                lbl_1_bss_48++;
                lbl_1_data_228 = -1;
                lbl_1_bss_4C = 0;
                return;
            }
            break;
        case 0x3EC:
            lbl_1_bss_4C++;
            if (lbl_1_bss_14 == 0x3F48) {
                lbl_1_data_22A = MGSeqCreate(1, 0x1E, -1, -1);
            }
            if (lbl_1_data_22A != -1) {
                MGSeqParamSet(lbl_1_data_22A, 1, (0x468B - lbl_1_bss_14) / 60);
            }
            if (lbl_1_bss_30 != -1) {
                lbl_1_bss_48 = 0x3ED;
                lbl_1_bss_4C = 0;
                return;
            }
            break;
        case 0x3ED:
            lbl_1_bss_4C++;
            if ((lbl_1_data_228 < 0) && (lbl_1_bss_4C == 1)) {
                if (lbl_1_data_22A != -1) {
                    MGSeqParamSet(lbl_1_data_22A, 2, -1);
                }
                lbl_1_data_228 = MGSeqCreate(3, 1);
                if (lbl_1_data_22C != -1) {
                    HuAudSeqFadeOut(lbl_1_data_22C, 0x64);
                    lbl_1_data_22C = -1;
                    return;
                }
            }
            else if (MGSeqStatGet(lbl_1_data_228) == 0) {
                lbl_1_bss_48++;
                lbl_1_bss_4C = 0;
                if (lbl_1_bss_30 == 4) {
                    lbl_1_bss_30 = spC[0]->unk_08 == -1 ? 0 : (spC[1]->unk_08 == -1 ? 1 : lbl_1_bss_30);
                    return;
                }
            }
            break;
        case 0x3EE:
            lbl_1_bss_4C++;
            if (lbl_1_bss_4C == 1) {
                if (lbl_1_bss_30 != 4) {
                    if (spC[lbl_1_bss_30]->unk_08 != -1) {
                        HuAudSStreamPlay(1);
                    }
                    else {
                        HuAudSStreamPlay(3);
                    }
                    GWPlayerCoinWinSet(spC[lbl_1_bss_30]->unk_04, 10);
                }
                else if (lbl_1_bss_30 == 4) {
                    HuAudSStreamPlay(4);
                }
            }
            if ((210.0f + (lbl_1_bss_30 == 4 ? 0x1E : 0)) < lbl_1_bss_4C) {
                lbl_1_data_228 = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
                var_r29->func = fn_1_9A38;
            }
            break;
    }
}

void fn_1_7ECC(omObjData *var_r31)
{
    var_r31->model[0] = Hu3DModelCreateFile(0x500008);
    Hu3DModelAttrSet(var_r31->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowMapSet(var_r31->model[0]);
    var_r31->model[1] = Hu3DModelCreateFile(0x500009);
    var_r31->model[2] = Hu3DModelCreateFile(0x50000A);
    Hu3DModelAttrSet(var_r31->model[2], HU3D_MOTATTR_LOOP);
    var_r31->func = fn_1_6850;
}

void fn_1_7F94(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float var_f31;
    float var_f30;
    float var_f29;

    HsfanimStruct01 *var_r31;
    s16 var_r29;

    if (particle->unk_34 == 0) {
        for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            var_r31->unk00 = 0;
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
    }
    if (particle->unk_34 >= 0xFF) {
        for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            var_r31->unk00 = 0xFF;
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
    }
    for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (!var_r31->unk2C) {
            break;
        }
    }
    for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00_s16 == 1) {
            var_f31 = ((frand() & 0xFF) * 0x168) >> 8;
            var_f30 = 0.5 + (1.5 * (rand8() / 256.0));
            var_r31->unk08.x = 2.5 * (var_f30 * sind(var_f31));
            var_r31->unk08.y = 4.5 * (var_f30 * cosd(var_f31));
            var_r31->unk08.y *= var_r31->unk08.y < 0.0f ? -0.5 : 1.0;
            var_r31->unk08.x = (12.0 * (rand8() / 255.0)) - 6.0;
            var_r31->unk08.y = 12.0 * (rand8() / 255.0);
            var_r31->unk08.z = (rand8() / 255.0) - 0.5;
            var_r31->unk34.x = 2.0f * var_r31->unk08.x;
            var_r31->unk34.y = 10.0f + (2.0f * var_r31->unk08.y);
            var_r31->unk34.z = 50.0f + (2.0f * var_r31->unk08.z);
            var_r31->unk40.r = 0xFF;
            var_r31->unk40.g = 0xFF;
            var_r31->unk40.b = 0xFF;
            var_r31->unk40.a = 0xFF;
            var_r31->unk2C = 50.0f;
        }
        if (var_r31->unk00_s16 < 0xF0) {
            PSVECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
            var_r31->unk08.x *= 0.9f;
            var_r31->unk08.z *= 0.9f;
            var_r31->unk08.y *= 0.9f;
            var_r31->unk40.a = (var_r31->unk40.a * 0xB) / 12;
            var_r31->unk2C += 1.01f;
            if (var_r31->unk2C <= 0.0f) {
                var_r31->unk2C = 0.0f;
            }
            if (var_r31->unk40.a == 0) {
                var_r31->unk40.a = 0;
                var_r31->unk2C = 0.0f;
            }
        }
        var_r31->unk00_s16 += var_r31->unk00_s16 < 0x8000;
        if (var_r31->unk00_s16 >= 0xF0) {
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
    }
}

void fn_1_8538(omObjData *var_r30)
{
    Vec sp60;
    Vec sp54;
    void *sp48;

    M449DllWork *var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    M449DllWork *var_r25;
    s32 var_r24;
    s32 var_r23;

    var_r26 = -1;
    var_r24 = -1;
    var_r31 = var_r30->data;
    sp48 = (&lbl_1_bss_54)[1 - var_r30->work[0]]->data;
    memset(var_r31, 0, sizeof(M449DllWork));
    var_r31->unk_00 = var_r30->work[0];
    if ((GWPlayerCfg->character == 0xC) || (GWPlayerCfg[1].character == 0xC) || (GWPlayerCfg[2].character == 0xC)
        || (GWPlayerCfg[3].character == 0xC)) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if (GWPlayerCfg[var_r29].character == 0xC) {
                var_r26 = var_r29;
            }
        }
        var_r24 = GWPlayerCfg[var_r26].group == 0 ? 1 : 0;
        if (var_r31->unk_00 == 0) {
            var_r31->unk_04 = var_r24;
            var_r23 = var_r26;
        }
        else {
            var_r31->unk_04 = var_r26;
            var_r23 = var_r24;
        }
    }
    else {
        var_r31->unk_04 = GWPlayerCfg[0].group == var_r31->unk_00
            ? 0
            : (GWPlayerCfg[1].group == var_r31->unk_00
                    ? 1
                    : (GWPlayerCfg[2].group == var_r31->unk_00 ? 2 : (GWPlayerCfg[3].group == var_r31->unk_00 ? 3 : 4)));
        var_r23 = GWPlayerCfg->group == (1 - var_r31->unk_00)
            ? 0
            : (GWPlayerCfg[1].group == (1 - var_r31->unk_00)
                    ? 1
                    : (GWPlayerCfg[2].group == (1 - var_r31->unk_00) ? 2 : (GWPlayerCfg[3].group == (1 - var_r31->unk_00) ? 3 : 4)));
    }
    if (var_r31->unk_04 == 4) {
        OSReport("m448:wrong player group\n");
        var_r31->unk_04 = var_r31->unk_00;
    }
    var_r31->unk_08 = ((var_r26 != -1) && (var_r31->unk_00 == 1)) != 0 ? -1 : GWPlayerCfg[var_r31->unk_04].character;
    var_r31->unk_0C = ((var_r31->unk_08 == -1) || (GWPlayerCfg[var_r31->unk_04].iscom != 0)) != 0 ? -1 : GWPlayerCfg[var_r31->unk_04].pad_idx;
    var_r31->unk_10 = var_r31->unk_0C != -1 ? 0 : GWPlayerCfg[var_r31->unk_04].diff;
    var_r31->unk_18 = -1;
    var_r31->unk_1C = 0;
    var_r31->unk_48 = lbl_1_rodata_10[var_r31->unk_10];
    var_r31->unk_4C = 0;
    var_r31->unk_214 = -1;
    if (var_r31->unk_08 != -1) {
        var_r30->model[0] = CharModelCreate(var_r31->unk_08, 1);
    }
    else {
        var_r30->model[0] = Hu3DModelCreateFile(0x50001B);
    }
    Hu3DModelObjPosGet(lbl_1_bss_50->model[1], lbl_1_data_E8[var_r31->unk_00 + 2], &sp54);
    omSetTra(var_r30, sp54.x, sp54.y, sp54.z);
    if (var_r30->trans.x == -360.0f) {
        var_r30->trans.x = -350.0f;
    }
    omSetRot(var_r30, 0.0f, (var_r31->unk_00 * 0xB4) + 0x5A, 0.0f);
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (var_r31->unk_08 != -1) {
            var_r30->motion[var_r29]
                = CharModelMotionCreate(var_r31->unk_08, lbl_1_data_90[var_r29] + (lbl_1_data_B0[var_r29] != 0 ? var_r31->unk_08 : 0));
        }
        else {
            var_r30->motion[var_r29] = Hu3DJointMotionFile(var_r30->model[0], lbl_1_data_A0[var_r29]);
        }
    }
    Hu3DMotionSet(var_r30->model[0], var_r30->motion[0]);
    Hu3DMotionTimeSet(var_r30->model[0], 20.0f);
    Hu3DModelAttrSet(var_r30->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r30->model[0]);
    CharModelVoiceEnableSet(var_r31->unk_08, var_r30->motion[3], 0);
    lbl_1_data_23C[var_r31->unk_00] = var_r31->unk_00 == 0 ? (rand8() % 3) : ((lbl_1_data_23C[0] + ((rand8() % 2)) + 1) % 3);
    if (var_r31->unk_00 == 0) {
        for (var_r29 = 0; var_r29 < 3; var_r29++) {
            M449DllUnkStruct sp6C = {
                { 0x0050000B, 0x0050000D, 0x0050000F, 0x00500011 },
                { 0x0050000C, 0x0050000E, 0x00500010, 0x00500012 },
            };
            do {
                while (TRUE) {
                    var_r27 = rand8() % 4;
                    if (lbl_1_data_230[0] == var_r27) {
                        continue;
                    }
                    if (lbl_1_data_230[1] == var_r27) {
                        continue;
                    }
                    break;
                }
            } while (lbl_1_data_230[2] == var_r27);
            lbl_1_data_230[var_r29] = var_r27;
            var_r30->model[var_r29 + 1] = Hu3DModelCreateFile(sp6C.unk_00[var_r27]);
            var_r30->model[var_r29 + 4] = Hu3DModelCreateFile(sp6C.unk_10[var_r27]);
        }
        var_r30->model[11] = Hu3DModelCreateFile(0x500013);
    }
    else {
        for (var_r29 = 0; var_r29 < 3; var_r29++) {
            var_r30->model[var_r29 + 1] = Hu3DModelLink(lbl_1_bss_54->model[var_r29 + 1]);
            var_r30->model[var_r29 + 4] = Hu3DModelLink(lbl_1_bss_54->model[var_r29 + 4]);
        }
        var_r30->model[11] = Hu3DModelLink(lbl_1_bss_54->model[11]);
    }
    Hu3DModelObjPosGet(lbl_1_bss_50->model[1], lbl_1_data_E8[var_r31->unk_00], &sp54);
    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        if (var_r29 != 0) {
            Hu3DModelAttrSet(var_r30->model[var_r29 + 1], HU3D_ATTR_DISPOFF);
        }
        Hu3DModelPosSet(var_r30->model[var_r29 + 1], sp54.x, sp54.y, sp54.z);
        Hu3DModelPosSet(var_r30->model[var_r29 + 4], sp54.x, sp54.y, sp54.z);
        Hu3DModelShadowSet(var_r30->model[var_r29 + 1]);
    }
    Hu3DModelPosSet(var_r30->model[11], sp54.x, sp54.y, sp54.z);
    Hu3DModelShadowSet(var_r30->model[11]);
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (var_r29 == 0) {
            var_r30->model[var_r29 + 0xC] = Hu3DModelCreateFile(var_r31->unk_00 == 0 ? 0x500014 : 0x500015);
        }
        else {
            var_r30->model[var_r29 + 0xC] = Hu3DModelLink(var_r30->model[12]);
        }
        Hu3DModelObjPosGet(lbl_1_bss_50->model[1], lbl_1_data_E8[var_r31->unk_00], &sp54);
        Hu3DModelObjPosGet(var_r30->model[4], lbl_1_data_138[var_r29], &sp60);
        var_r31->unk_60[var_r29] = sp60.x - sp54.x;
        var_r31->unk_80[var_r29] = sp60.z - sp54.z;
        var_r31->unk_90[var_r29] = var_r31->unk_B0[var_r29] = 0.0f;
        Hu3DModelPosSet(var_r30->model[var_r29 + 0xC], sp60.x, sp60.y, sp60.z);
    }
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        var_r28 = var_r29 + 7;
        Hu3DModelObjPosGet(var_r30->model[4], lbl_1_data_138[var_r29], &sp60);
        var_r30->model[var_r28] = Hu3DParticleCreate(HuSprAnimRead(HuDataReadNum(0x120003, 0x10000000)), 0x32);
        Hu3DModelPosSet(var_r30->model[var_r28], 2000.0f, -2000.0f, -2000.0f);
        Hu3DModelScaleSet(var_r30->model[var_r28], 1.0f, 1.0f, 1.0f);
        Hu3DModelLayerSet(var_r30->model[var_r28], 3);
        Hu3DModelAttrReset(var_r30->model[var_r28], HU3D_ATTR_DISPOFF);
        Hu3DParticleColSet(var_r30->model[var_r28], 0xFF, 0xFF, 0xFF);
        Hu3DParticleScaleSet(var_r30->model[var_r28], 5.0f);
        Hu3DParticleHookSet(var_r30->model[var_r28], fn_1_7F94);
        Hu3DParticleCntSet(var_r30->model[var_r28], 0xFF);
    }
    if (var_r31->unk_00 == 1) {
        for (var_r29 = 0; var_r29 < 0x12; var_r29++) {
            s32 sp4C[2] = { 0x64, 0x1E5 };
            s32 spD4[0x12] = { 0, 0, -14, 16, 46, -14, 16, 46, -50, 0, 0, -14, 16, 46, -14, 16, 46, -50 };
            s32 sp8C[0x12] = { 0, 0, -2, -2, -2, -2, -2, -2, 0, 0, 0, -2, -2, -2, -2, -2, -2, 0 };
            if ((lbl_1_data_0[var_r29] + 0xFF9F0000) == 0) {
                var_r25 = (&lbl_1_bss_54)[var_r29 == 8 ? 0 : (var_r29 == 0x11 ? 1 : 0)]->data;
                lbl_1_data_48[var_r29] = espEntry(var_r25->unk_08 == -1 ? 0x500018 : (var_r25->unk_08 + lbl_1_data_0[var_r29]), 0, 0);
            }
            else {
                lbl_1_data_48[var_r29] = espEntry(lbl_1_data_0[var_r29], 0, 0);
            }
            espDrawNoSet(lbl_1_data_48[var_r29], 0);
            espAttrSet(lbl_1_data_48[var_r29], HUSPR_ATTR_NOANIM | HUSPR_ATTR_DISPOFF);
            espBankSet(lbl_1_data_48[var_r29], 0);
            espPriSet(lbl_1_data_48[var_r29], 0x80 - var_r29);
            espPosSet(lbl_1_data_48[var_r29], spD4[var_r29] + sp4C[var_r29 < 9 ? 0 : 1], sp8C[var_r29] + 0x46);
            if ((var_r29 >= 9 ? (var_r29 - 9) : var_r29) != 0) {
                (void)var_r29;
                continue;
            }
            else {
                espTPLvlSet(lbl_1_data_48[var_r29], 0.5f);
                espColorSet(lbl_1_data_48[var_r29], 0, 0, 0);
            }
        }
    }
    var_r30->func = fn_1_758;
}

void fn_1_94F8(omObjData *var_r31)
{
    lbl_1_bss_48 = 0x3E8;
    lbl_1_bss_4C = 0;
    lbl_1_bss_40 = 0;
    lbl_1_bss_3C = 0;
    if (lbl_1_bss_64[0].unk_00 < 2) {
        lbl_1_bss_64[0].unk_04[lbl_1_bss_64[0].unk_00] = 0.0f;
        lbl_1_bss_64[0].unk_00++;
    }
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    var_r31->func = fn_1_7544;
}

void ObjectSetup(void)
{
    s32 var_r31;
    omObjData *var_r30;

    OSReport("******* M449 ObjectSetup *********\n");
    lbl_1_bss_38 = omInitObjMan(0x258, 0x2000);
    omGameSysInit(lbl_1_bss_38);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    CZoom = 2500.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = -100.0f;
    CRot.x = -40.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    {
        Vec sp3C = { 0.0f, 0.0f, 0.0f };
        Vec sp30 = { -0.5850064f, -0.788462f, 0.1545085f };
        Vec sp24;
        Vec sp18;
        Vec spC;
        GXColor sp8 = { 0xFF, 0xFF, 0xFF, 0xFF };
        lbl_1_bss_34 = Hu3DGLightCreateV(&sp3C, &sp30, &sp8);
        Hu3DGLightStaticSet(lbl_1_bss_34, 1);
        Hu3DGLightInfinitytSet(lbl_1_bss_34);
        sp24.x = 0.0f;
        sp24.y = 10000.0f;
        sp24.z = 0.0f;
        sp18.x = 0.0f;
        sp18.y = 1.0f;
        sp18.z = 0.0f;
        spC.x = 0.0f;
        spC.y = 0.0f;
        spC.z = 0.5f;
        Hu3DShadowCreate(6.0f, 9000.0f, 11500.0f);
        Hu3DShadowTPLvlSet(0.625f);
        Hu3DShadowPosSet(&sp24, &sp18, &spC);
    }
    Hu3DShadowSizeSet(0xE0);
    lbl_1_data_228 = -1;
    lbl_1_bss_30 = -1;
    HuWinInit(1);
    lbl_1_bss_50 = omAddObjEx(lbl_1_bss_38, 0x64, 3, 0, 1, fn_1_7ECC);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r30 = (&lbl_1_bss_54)[var_r31] = omAddObjEx(lbl_1_bss_38, 0x65, 0x14, 4, 0, fn_1_8538);
        var_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M449DllWork), MEMORY_DEFAULT_NUM);
        var_r30->work[0] = var_r31;
    }
    lbl_1_bss_5C = omAddObjEx(lbl_1_bss_38, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_60 = omAddObjEx(lbl_1_bss_38, 0x67, 0, 0, -1, fn_1_94F8);
}

void fn_1_9A38(omObjData *arg0)
{
    void *sp8;
    s32 var_r31;

    if (WipeStatGet() == 0) {
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            sp8 = (&lbl_1_bss_54)[var_r31]->data;
        }
        if (lbl_1_data_228 >= 0) {
            MGSeqKill(lbl_1_data_228);
        }
        MGSeqKillAll();
        HuAudAllStop();
        omOvlReturnEx(1, 1);
    }
}
