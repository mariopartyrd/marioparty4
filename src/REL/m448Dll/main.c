#include "REL/executor.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "dolphin.h"
#include "ext_math.h"
#include "version.h"

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ char unk14[4];
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
} UnkM448Struct_00; // Size 0x4C

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ char unk14[4];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} UnkM448Struct_01; // Size 0x24

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ float unk04[3];
} UnkM448Struct_02; // Size 0x10

void fn_1_A0(void);
void fn_1_38C(void);
void fn_1_478(void);
void fn_1_4FC(ModelData *model, Mtx matrix);
void fn_1_1338(omObjData *arg0);
void fn_1_4310(omObjData *arg0);
void fn_1_6DAC(void);
void fn_1_7148(omObjData *arg0);
void fn_1_7DC4(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_81C0(omObjData *arg0);
void fn_1_8DD0(omObjData *arg0);
void fn_1_9508(omObjData *arg0);
void ObjectSetup(void);
void fn_1_9B00(omObjData *arg0);

UnkM448Struct_01 lbl_1_bss_16C[20];
UnkM448Struct_02 lbl_1_bss_9C[13];
omObjData *lbl_1_bss_98;
omObjData *lbl_1_bss_94;
omObjData *lbl_1_bss_8C[2];
omObjData *lbl_1_bss_88;
s32 lbl_1_bss_84;
s32 lbl_1_bss_80;
s32 lbl_1_bss_7C;
s32 lbl_1_bss_78;
s32 lbl_1_bss_74;
Process *lbl_1_bss_70;
s32 lbl_1_bss_6C;
s32 lbl_1_bss_68;
s32 lbl_1_bss_64;
s32 lbl_1_bss_60;
GXTexObj lbl_1_bss_40;
char lbl_1_bss_3C_pad[4];
float lbl_1_bss_38;
s32 lbl_1_bss_34;
char lbl_1_bss_30_pad[4];
void *lbl_1_bss_2C;
void *lbl_1_bss_28;
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
char lbl_1_bss_8_pad[8];
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

s32 lbl_1_data_0[] = { DATA_MAKE_NUM(DATADIR_MGCONST, 23), DATA_MAKE_NUM(DATADIR_MGCONST, 22), DATA_MAKE_NUM(DATADIR_MGCONST, 51),
    DATA_MAKE_NUM(DATADIR_MGCONST, 51), DATADIR_MGCONST, DATA_MAKE_NUM(DATADIR_MGCONST, 23), DATA_MAKE_NUM(DATADIR_MGCONST, 22),
    DATA_MAKE_NUM(DATADIR_MGCONST, 51), DATA_MAKE_NUM(DATADIR_MGCONST, 51), DATADIR_MGCONST };

s32 lbl_1_data_28[10] = { 0 };

s32 lbl_1_data_50[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MARIOMOT, 2), DATA_MAKE_NUM(DATADIR_MARIOMOT, 3),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 5), DATA_MAKE_NUM(DATADIR_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MARIOMOT, 8), DATA_MAKE_NUM(DATADIR_MARIOMOT, 10),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 9), DATA_MAKE_NUM(DATADIR_MARIOMOT, 26), DATA_MAKE_NUM(DATADIR_MARIOMOT, 23),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 24) };

s32 lbl_1_data_7C[] = { DATA_MAKE_NUM(DATADIR_M448, 19), DATA_MAKE_NUM(DATADIR_M448, 20), DATA_MAKE_NUM(DATADIR_M448, 21),
    DATA_MAKE_NUM(DATADIR_M448, 24), DATA_MAKE_NUM(DATADIR_M448, 25), DATA_MAKE_NUM(DATADIR_M448, 26), DATA_MAKE_NUM(DATADIR_M448, 27),
    DATA_MAKE_NUM(DATADIR_M448, 28), DATA_MAKE_NUM(DATADIR_M448, 19), DATA_MAKE_NUM(DATADIR_M448, 22), DATA_MAKE_NUM(DATADIR_M448, 23) };

u8 lbl_1_data_A8[11] = { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 };
u8 lbl_1_data_B3[11] = { 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1 };
s32 lbl_1_data_C0[11] = { 8, 8, 8, 0, 0, 0, 8, 8, 2, 8, 8 };
s32 lbl_1_data_EC[11] = { 0, 0, 0, 3, 5, 0, 0, 0, 0, 0, 0 };
s32 lbl_1_data_118[11] = { 8, 8, 8, 0, 2, 0, 0, 0, 0, 8, 8 };
s32 lbl_1_data_144[11] = { 0 }; // unused
s32 lbl_1_data_170[2] = { 0 };
s32 lbl_1_data_178[] = { 1, 1, 0, 0, 0, 1, 0, 0 };
s16 lbl_1_data_198 = -1;
s16 lbl_1_data_19A = -1;
s16 lbl_1_data_19C = -1;
s32 lbl_1_data_1A0 = -1;
s32 lbl_1_data_1A4[2] = { 0 };
s32 lbl_1_data_1AC[2] = { 0 };
s32 lbl_1_data_1B4[2] = { 0 };

float lbl_1_data_1BC[][4] = { { -90.0f, 2.0f, 525.0f, 180.0f }, { 90.0f, 2.0f, 525.0f, 180.0f } };

float lbl_1_data_1DC[] = { 0.0f, 0.0f, 0.0f, 1.0f };

void fn_1_A0(void)
{
    Center.x += 10.0 * (((HuPadBtn[0] & 2) != 0) - ((HuPadBtn[0] & 1) != 0));
    Center.z -= 10.0 * (((HuPadBtn[0] & 8) != 0) - ((HuPadBtn[0] & 4) != 0));
    Center.y += 30.0 * ((HuPadTrigL[0] - HuPadTrigR[0]) / 128.0);
    CZoom += 25.0 * (((HuPadBtn[0] & 0x400) != 0) - ((HuPadBtn[0] & 0x800) != 0));
    CRot.y += HuPadSubStkX[0] / 16.0;
    CRot.x += HuPadSubStkY[0] / -16.0;
}

void fn_1_38C(void)
{
    lbl_1_bss_64 = GXGetTexBufferSize(640, 480, GX_TF_RGB565, GX_FALSE, 0);
    lbl_1_bss_60 = GXGetTexBufferSize(160, 120, GX_TF_RGB565, GX_FALSE, 0);
    lbl_1_bss_28 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_64, MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_28, 0, lbl_1_bss_64);
    lbl_1_bss_2C = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_60, MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_2C, 0, lbl_1_bss_60);
}

void fn_1_478(void)
{
    if (lbl_1_bss_28) {
        HuMemDirectFree(lbl_1_bss_28);
    }
    lbl_1_bss_28 = NULL;
    if (lbl_1_bss_2C) {
        HuMemDirectFree(lbl_1_bss_2C);
    }
    lbl_1_bss_2C = NULL;
}

void fn_1_4FC(ModelData *model, Mtx matrix)
{
    Mtx spC8;
    Mtx sp98;
    float temp_f31;
    float temp_f29;
    float temp_f30;
    float temp_f28;
    s32 sp10;
    void *spC;
    s32 var_r29;
    s32 var_r20;
    void *var_r28;
    s32 i;
    s32 j;

    sp10 = lbl_1_bss_64;
    spC = lbl_1_bss_28;
    if (!lbl_1_bss_28) {
        return;
    }
    GXSetScissor(0, 0, 640, 480);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    C_MTXOrtho(sp98, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    GXSetProjection(sp98, GX_ORTHOGRAPHIC);
    MTXIdentity(spC8);
    GXLoadPosMtxImm(spC8, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    for (i = 0; i < 0; i++) {
        s32 sp84[5] = { 0, 1, 1, 0, 1 };
        float sp70[5] = { 1.0f, 2.0f, 2.5f, 0.0f, 0.0f };
        float sp5C[5] = { 1.0f, 4.0f, 5.0f, 1.0f, 5.0f };
        float sp48[5] = { 2.0f, 2.5f, 0.0f, 1.0f, 1.0f };
        float sp34[5] = { 0.5f, -0.5f, 0.0f, 0.0f, 0.0f };

        var_r20 = (sp84[i] == 0) ? lbl_1_bss_64 : lbl_1_bss_60;
        var_r28 = (sp84[i] == 0) ? lbl_1_bss_28 : lbl_1_bss_2C;
        if (sp70[i] > 0.0f) {
            GXSetTexCopySrc(0, 0, 640.0f / sp70[i], 480.0f / sp70[i]);
            GXSetTexCopyDst(
                (sp84[i] == 0 ? 640 : 320) / sp70[i], (sp84[i] == 0 ? 480 : 240) / sp70[i], GX_TF_RGB565, sp84[i] == 0 ? GX_FALSE : GX_TRUE);
            GXSetCopyClear(BGColor, 0xFFFFFF);
            GXCopyTex(var_r28, GX_FALSE);
            DCFlushRange(var_r28, var_r20);
            GXPixModeSync();
        }
        if (sp48[i] > 0.0f) {
            GXInitTexObj(&lbl_1_bss_40, var_r28, 640.0f / sp5C[i], 480.0f / sp5C[i], GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXLoadTexObj(&lbl_1_bss_40, GX_TEXMAP0);
            for (j = 0; j < (i != 4 ? 1 : 4); j++) {
                float sp24[4] = { 16.5f, -8.5f, -16.5f, 8.5f };
                float sp14[4] = { -8.5f, -16.5f, 8.5f, 16.5f };

                temp_f31 = 0.0015625 * (0.5 * sp24[j]);
                temp_f29 = 0.0f;
                temp_f30 = 0.0015625 * (0.6666666666666666 * sp14[j]);
                temp_f28 = 0.0f;
                var_r29 = 16 - j * 5;
                var_r29 = (i != 4) ? 0xFF : 0xB1;
                if (i != 4) {
                    temp_f31 = 0.0f;
                    temp_f30 = 0.0f;
                }
                if (i == 3) {
                    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ZERO, GX_LO_NOOP);
                }
                else if (i == 4) {
                    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_SUBHALF, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
                    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
                }
                else {
                    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ZERO, GX_LO_NOOP);
                }
                temp_f31 = 0.0015625 * sp34[i];
                temp_f30 = 0.0015625 * sp34[i];
                temp_f31 = 0.0f;
                temp_f30 = 0.0f;
                temp_f29 += 0.5 * (1.0f / (640.0f / sp5C[i]));
                temp_f28 += 0.5 * (1.0f / (640.0f / sp5C[i]));
                temp_f31 = temp_f30 = temp_f29 = temp_f28 = 0.0f;
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(temp_f31 + 1.25 * (0.0f / sp48[i]), temp_f30 + 1.25 * (0.0f / sp48[i]), 0.0f);
                GXColor4u8(0xFF, 0xFF, 0xFF, var_r29);
                GXPosition2f32(temp_f29 + 0.0, temp_f28 + 0.0);
                GXPosition3f32(temp_f31 + 1.25 * (1.0f / sp48[i]), temp_f30 + 1.25 * (0.0f / sp48[i]), 0.0f);
                GXColor4u8(0xFF, 0xFF, 0xFF, var_r29);
                GXPosition2f32(temp_f29 + 1.25, temp_f28 + 0.0);
                GXPosition3f32(temp_f31 + 1.25 * (1.0f / sp48[i]), temp_f30 + 1.25 * (1.0f / sp48[i]), 0.0f);
                GXColor4u8(0xFF, 0xFF, 0xFF, var_r29);
                GXPosition2f32(temp_f29 + 1.25, temp_f28 + 1.25);
                GXPosition3f32(temp_f31 + 1.25 * (0.0f / sp48[i]), temp_f30 + 1.25 * (1.0f / sp48[i]), 0.0f);
                GXColor4u8(0xFF, 0xFF, 0xFF, var_r29);
                GXPosition2f32(temp_f29 + 0.0, temp_f28 + 1.25);
                GXEnd();
            }
        }
    }
}

const Vec lbl_1_rodata_100 = { 0.0f, 0.0f, 0.0f };

void fn_1_1338(omObjData *arg0)
{
    Mtx sp184;
    Vec sp178;
    s32 var_r24;
    UnkM448Struct_00 *temp_r31;
    UnkM448Struct_00 *sp11C;
    UnkM448Struct_00 *temp_r23;
    UnkM448Struct_00 *temp_r25;
    UnkM448Struct_01 *temp_r28;
    UnkM448Struct_01 *temp_r27;
    float var_f29;
    float var_f20;
    float sp118;
    float sp114;
    float sp110;
    float sp10C;
    float sp108;
    float sp104;
    float sp100;
    float spFC;
    float spF8;
    float spF4;
    float spF0;
    s32 var_r17;
    s32 spEC;
    float spE8;
    s32 spE4;
    float spE0;
    float spDC;
    float spD8;
    float spD4;
    float spD0;
    float spCC;
    float temp_f24;
    float temp_f23;
    float temp_f22;
    float temp_f21;
    float temp_f26;
    float temp_f25;
    float temp_f27;
    float temp_f31;
    float temp_f30;
    float var_f28;
    s16 var_r29;
    s32 var_r21;
    s32 var_r26;
    s32 var_r20;
    s32 var_r19;
    s32 var_r18;
    s32 var_r22;

    temp_r31 = arg0->data;
    sp11C = lbl_1_bss_8C[1 - arg0->work[0]]->data;
    var_f29 = 0.0f;
    var_f20 = 0.0f;
    sp118 = 0.0f;
    sp114 = 0.0f;
    sp110 = 0.0f;
    var_r29 = -1;
    if (temp_r31->unk20 != 3) {
        temp_r31->unk40 = temp_r31->unk48 = 0.0f;
    }
    temp_r31->unk38++;
    switch (temp_r31->unk34) {
        case 0:
            if (lbl_1_bss_80 == 1001 && lbl_1_bss_84 == 45 && temp_r31->unk08 != -1) {
                var_r20 = 8;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[var_r20], lbl_1_data_EC[var_r20], 45.0f,
                    (lbl_1_data_A8[var_r20] != 0) ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
                temp_r31->unk20 = var_r20;
            }
            if (lbl_1_bss_80 == 1001 && lbl_1_bss_84 == 210 && temp_r31->unk08 != -1) {
                var_r19 = 0;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[var_r19], lbl_1_data_EC[var_r19], 30.0f,
                    (lbl_1_data_A8[var_r19] != 0) ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
                temp_r31->unk20 = var_r19;
            }
            if (lbl_1_bss_80 == 1003 && temp_r31->unk08 != -1) {
                arg0->rot.y = 0.9 * (arg0->rot.y - (temp_r31->unk00 == 0 ? 90 : -90)) + (temp_r31->unk00 == 0 ? 90 : -90);
            }
            if (lbl_1_bss_80 == 1005) {
                temp_r31->unk34 = (lbl_1_bss_14 == temp_r31->unk00) ? 1 : 3;
            }
            break;
        case 1:
            if (temp_r31->unk38 == 1 && temp_r31->unk08 != -1) {
                Hu3DMotionNoMotReset(arg0->model[0], "ske_head", (lbl_1_data_178[temp_r31->unk08] != 0) ? 0x100 : 0x80);
            }
            sp118 = (lbl_1_bss_1C < 90) ? 0 : 0x48;
            if (arg0->trans.z < 250.0f) {
                temp_r31->unk34 = 2;
                lbl_1_bss_0 = 600;
                if (lbl_1_data_19A != -1) {
                    MGSeqKill(lbl_1_data_19A);
                }
                lbl_1_data_19A = MGSeqCreate(1, lbl_1_bss_0 / 60, -1, -1);
                for (var_r17 = 0; var_r17 < 10; var_r17++) {
                    espDispOn(lbl_1_data_28[var_r17]);
                }
                if (temp_r31->unk0C == -1) {
                    var_r24 = 0;
                    temp_r31->unk18 = temp_r31->unk1C = -1;
                    for (var_r26 = 0; var_r26 < 20; var_r26++) {
                        var_r24 += (lbl_1_bss_16C[var_r26].unk18 != 9);
                    }
                    if (var_r24 != 0) {
                        var_r24 = rand8() % var_r24;
                        for (var_r26 = 0; var_r26 < 20; var_r26++) {
                            if (lbl_1_bss_16C[var_r26].unk18 != 9) {
                                if (var_r24 <= 0) {
                                    temp_r31->unk18 = lbl_1_bss_16C[var_r26].unk00;
                                    temp_r31->unk1C = lbl_1_bss_16C[var_r26].unk04;
                                    break;
                                }
                                var_r24--;
                            }
                        }
                    }
                }
            }
            break;
        case 6:
            var_f20 = 4.0f * (0.5f + lbl_1_data_1BC[temp_r31->unk00][0] - arg0->trans.x);
            sp118 = 4.0f * -(0.5f + lbl_1_data_1BC[temp_r31->unk00][2] - arg0->trans.z);
            if (lbl_1_bss_80 == 1005) {
                var_f20 = 0.0f;
            }
            if (arg0->trans.z >= lbl_1_data_1BC[temp_r31->unk00][2]) {
                temp_r31->unk34 = (lbl_1_bss_80 < 1005) ? 0 : ((lbl_1_bss_68 == -1) ? 3 : 7);
                temp_r31->unk38 = 0;
                if (temp_r31->unk34 == 0) {
                    arg0->rot.y = 180.0f;
                }
            }
            break;
        case 2:
            if (lbl_1_bss_14 != temp_r31->unk00) {
                OSReport("m448 player turn error!\n");
            }
            if (lbl_1_bss_0 > 0 && lbl_1_bss_18 < 18000) {
                if (temp_r31->unk0C != -1) {
                    var_f20 = HuPadStkX[temp_r31->unk0C];
                    sp118 = HuPadStkY[temp_r31->unk0C];
                    sp114 = (HuPadBtn[temp_r31->unk0C] & 0x100) > 0;
                    sp110 = (HuPadBtnDown[temp_r31->unk0C] & (temp_r31->unk20 == 3 ? 320 : 256)) > 0;
                    sp178 = lbl_1_rodata_100;
                    sp178.x = var_f20;
                    sp178.z = -sp118;
                    MTXRotRad(sp184, 'y', MTXDegToRad(CRot.y));
                    MTXMultVec(sp184, &sp178, &sp178);
                    var_f20 = sp178.x;
                    sp118 = -sp178.z;
                }
                else {
                    if (temp_r31->unk20 == 3) {
                        if (temp_r31->unk44 < 0.0f && temp_r31->unk08 != -1) {
                            sp110 = sp114 = 1.0f;
                        }
                        else {
                            sp114 = 1.0f;
                        }
                    }
                    if (temp_r31->unk18 != -1 && temp_r31->unk1C != -1) {
                        temp_f26 = 100.0 + 200.0 * (temp_r31->unk18 - 2.5) - arg0->trans.x;
                        temp_f25 = 100.0 + 200.0 * (temp_r31->unk1C - 2.0) - arg0->trans.z;
                        sp10C = sqrtf(temp_f26 * temp_f26 + temp_f25 * temp_f25);
                        if (temp_r31->unk08 != -1 && temp_r31->unk20 != 3) {
                            if (sp10C < 60.0f) {
                                sp110 = sp114 = 1.0f;
                            }
                            else {
                                var_f20 = temp_f26;
                                sp118 = -temp_f25;
                            }
                        }
                        else if (sp10C < 277.5) {
                            if (temp_r31->unk20 != 3) {
                                sp110 = sp114 = 1.0f;
                            }
                            var_f20 = (temp_f26 / 37.0) / 0.25;
                            sp118 = (-temp_f25 / 37.0) / 0.25;
                        }
                        else {
                            var_f20 = temp_f26;
                            sp118 = -temp_f25;
                        }
                    }
                }
            }
            arg0->trans.x = (arg0->trans.x < -450.0f) ? -450.0f : (arg0->trans.x > 450.0f) ? 450.0f : arg0->trans.x;
            arg0->trans.z = (arg0->trans.z < -350.0f) ? -350.0f : (arg0->trans.z > 350.0f) ? 350.0f : arg0->trans.z;
            if ((lbl_1_bss_0 <= 0 || lbl_1_bss_18 >= 18000) && temp_r31->unk20 == 0) {
                temp_r31->unk34 = 5;
                temp_r31->unk38 = 0;
                lbl_1_bss_1C = 0;
                if (lbl_1_bss_18 >= 18000) {
                    temp_r23 = lbl_1_bss_8C[1 - temp_r31->unk00]->data;
                    lbl_1_bss_68 = (temp_r31->unk08 == -1) ? temp_r31->unk00 : (temp_r23->unk08 == -1) ? temp_r23->unk00 : 4;
                    temp_r23->unk34 = 7;
                    temp_r23->unk38 = 0;
                }
            }
            break;
        case 3:
            spFC = (arg0->rot.y > 0.0f) ? -180 : 180;
            sp104 = lbl_1_bss_8C[1 - temp_r31->unk00]->trans.x;
            sp100 = lbl_1_bss_8C[1 - temp_r31->unk00]->trans.z;
            sp108 = atan2d(sp104 - arg0->trans.x, sp100 - arg0->trans.z);
            arg0->rot.y = 0.3 * (arg0->rot.y + spFC) - spFC;
            if (temp_r31->unk08 != -1) {
                Hu3DMotionForceSet(arg0->model[0], "ske_head", (lbl_1_data_178[temp_r31->unk08] != 0) ? 0x100 : 0x80,
                    (lbl_1_data_178[temp_r31->unk08] != 0) ? 180.0f + -sp108 : 180.0f + sp108);
            }
            break;
        case 5:
            if (arg0->trans.z >= 400.0f) {
                temp_r25 = lbl_1_bss_8C[1 - temp_r31->unk00]->data;
                temp_r31->unk34 = 6;
                temp_r31->unk38 = 0;
                sp118 = -40.0f;
                if (lbl_1_bss_68 == -1) {
                    temp_r25->unk34 = 1;
                    temp_r25->unk38 = 0;
                    if (temp_r25->unk08 != -1) {
                        Hu3DMotionForceSet(
                            lbl_1_bss_8C[1 - temp_r31->unk00]->model[0], "ske_head", (lbl_1_data_178[temp_r25->unk08] != 0) ? 0x100 : 0x80, 180.0f);
                        Hu3DMotionNoMotReset(
                            lbl_1_bss_8C[1 - temp_r31->unk00]->model[0], "ske_head", (lbl_1_data_178[temp_r25->unk08] != 0) ? 0x100 : 0x80);
                    }
                }
                lbl_1_bss_14 = 1 - lbl_1_bss_14;
            }
            else {
                spF8 = lbl_1_data_1BC[temp_r31->unk00][0] - arg0->trans.x;
                spF4 = 400.0f - arg0->trans.z;
                spF0 = atan2d(lbl_1_data_1BC[temp_r31->unk00][0] - arg0->trans.x, 400.0f - arg0->trans.z);
                var_f20 = 10.0 * sind(spF0) / 0.25;
                sp118 = 10.0 * -cosd(spF0) / 0.25;
                if (fabs(var_f20) > fabs(4.0f * (lbl_1_data_1BC[temp_r31->unk00][0] - arg0->trans.x))) {
                    var_f20 = 4.0f * (lbl_1_data_1BC[temp_r31->unk00][0] - arg0->trans.x);
                }
            }
            break;
        case 7:
            if (temp_r31->unk38 == 1 && temp_r31->unk08 != -1) {
                Hu3DMotionForceSet(arg0->model[0], "ske_head", (lbl_1_data_178[temp_r31->unk08] != 0) ? 0x100 : 0x80, 180.0f);
                Hu3DMotionNoMotReset(arg0->model[0], "ske_head", (lbl_1_data_178[temp_r31->unk08] != 0) ? 0x100 : 0x80);
            }
            arg0->rot.y *= 0.3;
            if (lbl_1_bss_80 == 1007 && temp_r31->unk20 == 0) {
                temp_r31->unk24 = (lbl_1_bss_68 == temp_r31->unk00) ? 9 : 10;
            }
            break;
    }
    switch (temp_r31->unk20) {
        case 4:
        case 7:
        case 8:
            if ((temp_r31->unk08 != -1) ? CharModelMotionEndCheck(temp_r31->unk08) : Hu3DMotionEndCheck(arg0->model[0])) {
                var_r29 = 0;
            }
            /* fallthrough */
        case 0:
        case 1:
        case 2:
            temp_f31 = 0.25 * var_f20;
            temp_f30 = 0.25 * -sp118;
            var_f29 = sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30);
            if (var_f29 >= 0.5f) {
                if (var_f29 < 10.0f) {
                    temp_r31->unk40 = temp_f31;
                    temp_r31->unk48 += temp_f30;
                }
                else {
                    temp_f31 = temp_f31 / var_f29;
                    temp_f30 = temp_f30 / var_f29;
                    var_f29 = 10.0f;
                    if (temp_r31->unk20 != 3) {
                        temp_r31->unk40 = temp_f31 * var_f29;
                        temp_r31->unk48 = temp_f30 * var_f29;
                    }
                    else {
                        temp_r31->unk40 = 0.875 * temp_r31->unk40 + temp_f31 * var_f29 * 0.125;
                        temp_r31->unk48 = 0.875 * temp_r31->unk48 + temp_f30 * var_f29 * 0.125;
                    }
                }
                temp_r31->unk3C = var_f29;
                arg0->rot.y = atan2d(temp_r31->unk40, temp_r31->unk48);
                if (temp_r31->unk3C >= 8.0f) {
                    var_r29 = 2;
                }
                else {
                    var_r29 = 1;
                }
            }
            else if (temp_r31->unk20 != 7 && temp_r31->unk20 != 4 && temp_r31->unk20 != 8) {
                var_r29 = 0;
            }
            temp_r31->unk44 = 0.0f;
            if (sp110) {
                temp_r31->unk2C = 0;
                temp_r31->unk28 = 1;
                temp_r31->unk44 = 26.766666f;
                var_r29 = 3;
            }
            break;
        case 3:
            if (temp_r31->unk08 != -1) {
                temp_f31 = 0.25 * var_f20;
                temp_f30 = 0.25 * -sp118;
                var_f29 = sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30);
                if (var_f29 >= 0.5f) {
                    if (var_f29 < 10.0f) {
                        temp_r31->unk40 = temp_f31;
                        temp_r31->unk48 = temp_f30;
                    }
                    else {
                        temp_f31 = temp_f31 / var_f29;
                        temp_f30 = temp_f30 / var_f29;
                        var_f29 = 10.0f;
                        if (temp_r31->unk20 != 3) {
                            temp_r31->unk40 = temp_f31 * var_f29;
                            temp_r31->unk48 = temp_f30 * var_f29;
                        }
                        else {
                            temp_r31->unk40 = 0.875 * temp_r31->unk40 + temp_f31 * var_f29 * 0.125;
                            temp_r31->unk48 = 0.875 * temp_r31->unk48 + temp_f30 * var_f29 * 0.125;
                        }
                    }
                    temp_r31->unk3C = var_f29;
                    arg0->rot.y = atan2d(temp_r31->unk40, temp_r31->unk48);
                }
                else {
                    // Required to match.
                    0.875 * temp_r31->unk40;
                    0.875 * temp_r31->unk48;
                }
            }
            if (temp_r31->unk28 != 0) {
                if (sp114) {
                    if (++temp_r31->unk28 > 4) {
                        temp_r31->unk28 = 0;
                    }
                    else {
                        temp_r31->unk44 += 4.866667f;
                    }
                }
                else {
                    temp_r31->unk28 = 0;
                }
            }
            temp_r31->unk44 += -2.4333334f;
            if (temp_r31->unk2C != 0) {
                temp_r31->unk44 = 0.0f;
                temp_r31->unk2C = 1;
                var_r29 = 4;
                if (temp_r31->unk08 != -1) {
                    break;
                }
                temp_r31->unk44 = 9.733334f;
                temp_r31->unk44 = 0.0f;
                temp_r31->unk2C = 0;
                var_r29 = 6;
                if (temp_r31->unk34 != 2) {
                    break;
                }
                for (spEC = 0; spEC < 20; spEC++) {
                    temp_r28 = &lbl_1_bss_16C[spEC];
                    temp_f24 = 100.0 + 200.0 * (temp_r28->unk00 - 2.5) - arg0->trans.x;
                    temp_f23 = 100.0 + 200.0 * (temp_r28->unk04 - 2.0) - arg0->trans.z;
                    spE8 = sqrtf(temp_f24 * temp_f24 + temp_f23 * temp_f23);
                    if (temp_r28->unk0C == -1 && spE8 <= 100.0) {
                        temp_r31->unk34 = 4;
                        temp_r31->unk38 = 0;
                        temp_r28->unk18 = 8;
                        temp_r28->unk1C = 0;
                        temp_r28->unk0C = temp_r31->unk00;
                        MGSeqParamSet(lbl_1_data_19A, 2, -1);
                        lbl_1_data_19A = -1;
                        lbl_1_bss_1C = 0;
                    }
                }
            }
            else if (sp110) {
                temp_r31->unk44 = 0.0f;
                temp_r31->unk30 = 0;
                var_r29 = 5;
            }
            break;
        case 5:
            if ((Hu3DData[arg0->model[0]].unk_0C == -1 && temp_r31->unk08 != -1) ? CharModelMotionEndCheck(temp_r31->unk08)
                                                                                 : Hu3DMotionEndCheck(arg0->model[0])) {
                temp_r31->unk44 += -2.4333334f;
            }
            else {
                temp_r31->unk44 = 0.0f;
            }
            if (temp_r31->unk44 < 0.0f && temp_r31->unk2C != 0) {
                if (temp_r31->unk30 != 0) {
                    temp_r31->unk44 = 0.0f;
                    temp_r31->unk30 = 0;
                    var_r29 = 7;
                }
                else {
                    temp_r31->unk44 = 9.733334f;
                    temp_r31->unk2C = 0;
                    var_r29 = 6;
                    if (temp_r31->unk0C != -1) {
                        omVibrate(temp_r31->unk04, 12, 6, 6);
                    }
                    if (temp_r31->unk34 == 2) {
                        for (spE4 = 0; spE4 < 20; spE4++) {
                            temp_r27 = &lbl_1_bss_16C[spE4];
                            temp_f22 = 100.0 + 200.0 * (temp_r27->unk00 - 2.5) - arg0->trans.x;
                            temp_f21 = 100.0 + 200.0 * (temp_r27->unk04 - 2.0) - arg0->trans.z;
                            spE0 = sqrtf(temp_f22 * temp_f22 + temp_f21 * temp_f21);
                            if (temp_r27->unk0C == -1 && spE0 <= 100.0) {
                                temp_r31->unk34 = 4;
                                temp_r31->unk38 = 0;
                                temp_r27->unk18 = 8;
                                temp_r27->unk1C = 0;
                                temp_r27->unk0C = temp_r31->unk00;
                                MGSeqParamSet(lbl_1_data_19A, 2, -1);
                                lbl_1_data_19A = -1;
                                lbl_1_bss_1C = 0;
                            }
                        }
                    }
                }
            }
            break;
        case 6:
            temp_r31->unk44 += -2.4333334f;
            if (temp_r31->unk2C != 0) {
                if ((temp_r31->unk08 != -1) ? CharModelMotionEndCheck(temp_r31->unk08) : Hu3DMotionEndCheck(arg0->model[0])) {
                    var_r29 = 7;
                }
            }
            break;
        case 9:
        case 10:
            break;
    }
    arg0->trans.x += temp_r31->unk40;
    if (temp_r31->unk2C == 0) {
        arg0->trans.y += temp_r31->unk44;
    }
    arg0->trans.z += temp_r31->unk48;
    for (var_r22 = 1; var_r22 < 2; var_r22++) {
        temp_f27 = lbl_1_bss_8C[var_r22]->trans.x - arg0->trans.x;
        var_f28 = lbl_1_bss_8C[var_r22]->trans.z - arg0->trans.z;
        if (var_r22 != temp_r31->unk00) {
            if (temp_f27 == 0.0f && var_f28 == 0.0f) {
                var_f28 = -1.0f;
            }
            spDC = sqrtf(temp_f27 * temp_f27 + var_f28 * var_f28);
            if (spDC < 100.0f) {
                temp_f27 *= 100.0f / spDC;
                var_f28 *= 100.0f / spDC;
                arg0->trans.x = lbl_1_bss_8C[var_r22]->trans.x - temp_f27;
                arg0->trans.z = lbl_1_bss_8C[var_r22]->trans.z - var_f28;
            }
        }
    }
    if (arg0->trans.y < 0.0f) {
        arg0->trans.y = (temp_r31->unk34 == 7) ? 2.5f : 0.0f;
        temp_r31->unk2C = 1;
    }
    if (temp_r31->unk24 >= 0) {
        var_r29 = temp_r31->unk24;
    }
    if (var_r29 >= 0 && var_r29 != temp_r31->unk20) {
        var_r18 = (temp_r31->unk08 == -1 && (var_r29 == 9 || var_r29 == 10)) ? 0 : var_r29;
        if (temp_r31->unk08 != -1) {
            Hu3DMotionShiftSet(arg0->model[0], arg0->motion[var_r18], lbl_1_data_EC[var_r18], lbl_1_data_C0[var_r18],
                (lbl_1_data_A8[var_r18] != 0) ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
        }
        else {
            Hu3DMotionShiftSet(arg0->model[0], arg0->motion[var_r29], lbl_1_data_EC[var_r29], lbl_1_data_118[var_r29],
                (lbl_1_data_B3[var_r29] != 0) ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
            if (var_r29 == 3) {
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[5], 15.0f, 33.0f, HU3D_MOTATTR_PAUSE);
            }
        }
        temp_r31->unk20 = var_r29;
    }
    espBankSet(lbl_1_data_28[temp_r31->unk00 * 5 + 2], lbl_1_data_1A4[temp_r31->unk00] % 10);
    espBankSet(lbl_1_data_28[temp_r31->unk00 * 5 + 3], (lbl_1_data_1A4[temp_r31->unk00] / 10) % 10);
    lbl_1_data_1B4[temp_r31->unk00] += (lbl_1_data_1B4[temp_r31->unk00] < 256) ? 1 : 0;
    if (lbl_1_data_1B4[temp_r31->unk00] <= 15) {
        spD8 = 1.0 - lbl_1_data_1B4[temp_r31->unk00] / 15.0;
        spD4 = 1.0f;
        spD0 = 0.0f;
        spCC = 0.0f;
        for (var_r21 = 0; var_r21 < 2; var_r21++) {
            if (lbl_1_data_1AC[temp_r31->unk00] > 0) {
                float sp1B4[21] = { 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 15.0f };

                spD8 = (lbl_1_data_1B4[temp_r31->unk00] < 10) ? 1.0 - lbl_1_data_1B4[temp_r31->unk00] / 10.0 : 0.0;
                spD4 = 1.0 + (spD8 * 0.5 + spD8 * spD8 * 0.5) * sp1B4[lbl_1_data_1AC[temp_r31->unk00]] / 10.0;
                espScaleSet(lbl_1_data_28[(var_r21 == 0 ? 2 : 3) + temp_r31->unk00 * 5], spD4, spD4);
            }
            else if (lbl_1_data_1AC[temp_r31->unk00] < 0) {
                s32 sp168[4] = { 100, 485, 16, -4 };

                spD0 = spD8 * lbl_1_data_1AC[temp_r31->unk00] * (rand8() / 255.0 - 0.5);
                spCC = spD8 * lbl_1_data_1AC[temp_r31->unk00] * (rand8() / 255.0 - 0.5);
                espPosSet(
                    lbl_1_data_28[(var_r21 == 0 ? 2 : 3) + temp_r31->unk00 * 5], (&sp168[var_r21])[2] + sp168[temp_r31->unk00] + spD0, 72.0f + spCC);
            }
        }
    }
}

s32 lbl_1_data_25C = -1;
float lbl_1_data_260 = 2775.0f;
float lbl_1_data_264 = 314.0f;
float lbl_1_data_268 = -100.0f;
float lbl_1_data_26C = -38.75f;

void fn_1_4310(omObjData *arg0)
{
    UnkM448Struct_00 *spC8[2];
    float spB0;
    float spAC;
    float temp_f19;
    float var_f18;
    float spA8;
    float spA4;
    float spA0;
    float sp9C;
    float sp98;
    float sp94;
    float sp90;
    float sp8C;
    float sp88;
    float sp84;
    float sp80;
    float sp7C;
    float sp78;
    float sp74;
    float sp70;
    float sp6C;
    ModelData *temp_r23;
    ModelData *temp_r22;
    ModelData *temp_r26;
    ModelData *temp_r29;
    UnkM448Struct_01 *temp_r31;
    float temp_f21;
    float temp_f20;
    float temp_f26;
    float temp_f30;
    float temp_f29;
    float var_f28;
    float var_f27;
    float var_f22;
    float var_f23;
    float var_f31;
    s32 temp_r21;
    s32 var_r25;
    s32 var_r20;
    s32 var_r19;
    s32 var_r24;
    s32 i;

    for (i = 0; i < 2; i++) {
        spC8[i] = lbl_1_bss_8C[i]->data;
    }
    lbl_1_bss_4++;
    lbl_1_bss_1C++;
    if (lbl_1_bss_80 == 1005) {
        lbl_1_bss_18++;
        if (lbl_1_bss_18 == 16200) {
            lbl_1_data_19C = MGSeqCreate(1, (18060 - lbl_1_bss_18) / 60, -1, -1);
            MGSeqPosSet(lbl_1_data_19C, 288.0f, 400.0f);
        }
        if (lbl_1_data_19C != -1) {
            MGSeqParamSet(lbl_1_data_19C, 1, (18060 - lbl_1_bss_18) / 60);
        }
    }
    lbl_1_data_1DC[0] = lbl_1_data_1DC[1] = lbl_1_data_1DC[2] = 0.0f;
    if (lbl_1_bss_80 == 1004 && lbl_1_bss_84 == 0) {
        lbl_1_bss_84++;
        lbl_1_bss_78 = 1;
        lbl_1_bss_74 = 0;
        for (i = 0; i < 20; i++) {
            lbl_1_bss_16C[i].unk18 = 2;
            lbl_1_bss_16C[i].unk1C = 0;
            lbl_1_bss_16C[i].unk08 = rand8() % 16;
            lbl_1_bss_16C[i].unk10 = -40.0f;
        }
    }
    switch (lbl_1_bss_78) {
        case 1:
            lbl_1_bss_74++;
            if (lbl_1_bss_74 == 1) {
                spC8[0]->unk34 = spC8[1]->unk34 = 6;
                spC8[0]->unk38 = spC8[1]->unk38 = 0;
            }
            var_r20 = 0;
            for (i = 0; i < 20; i++) {
                var_r20 += (lbl_1_bss_16C[i].unk10 == 0.0f);
            }
            if (var_r20 >= 20) {
                lbl_1_bss_78 = 2;
                lbl_1_bss_74 = 0;
            }
            break;
        case 2:
            lbl_1_bss_74++;
            if (lbl_1_bss_74 >= 30) {
                lbl_1_bss_78 = 0;
                lbl_1_bss_74 = 0;
                for (i = 0; i < 20; i++) {
                    lbl_1_bss_16C[i].unk18 = 3;
                    lbl_1_bss_16C[i].unk1C = 0;
                }
                if (lbl_1_bss_9C[8].unk00 < 3) {
                    lbl_1_bss_9C[8].unk04[lbl_1_bss_9C[8].unk00] = 0.0f;
                    lbl_1_bss_9C[8].unk00++;
                }
            }
            break;
        case 3:
            lbl_1_bss_74++;
            if (lbl_1_bss_74 == 1) {
                s32 var_r27 = 0;
                s32 sp170[20] = { 0 };

                for (var_r27 = 0; var_r27 < 20; var_r27++) {
                    temp_r23 = &Hu3DData[arg0->model[var_r27 + 7]];
                    temp_r22 = &Hu3DData[arg0->model[var_r27 + 27]];
                    do {
                        do {
                            var_r25 = rand8();
                        } while (var_r25 >= 240);
                    } while (sp170[var_r25 % 20] != 0);
                    sp170[var_r25 % 20] = 1;
                    lbl_1_bss_16C[var_r27].unk00 = (var_r25 % 20) % 5;
                    lbl_1_bss_16C[var_r27].unk04 = ((var_r25 % 20) / 5) % 4;
                    temp_r23->pos.x = temp_r22->pos.x = 100.0 + 200.0 * (lbl_1_bss_16C[var_r27].unk00 - 2.5);
                    temp_r23->pos.z = temp_r22->pos.z = 100.0 + 200.0 * (lbl_1_bss_16C[var_r27].unk04 - 2.0);
                }
            }
            if (lbl_1_bss_74 >= 10) {
                lbl_1_bss_78 = 4;
                lbl_1_bss_74 = 0;
                lbl_1_data_170[0] = 1;
            }
            break;
        case 4:
            if (lbl_1_bss_74 == 0 && lbl_1_bss_9C[0].unk00 < 3) {
                lbl_1_bss_9C[0].unk04[lbl_1_bss_9C[0].unk00] = 0.0f;
                lbl_1_bss_9C[0].unk00++;
            }
            lbl_1_bss_74++;
            if (lbl_1_bss_74 % 4 == 1) {
                spB0 = 10000.0f;
                var_r24 = -1;
                var_r19 = 0;
                for (i = 0; i < 20; i++) {
                    var_r19 = (lbl_1_bss_16C[i].unk18 == 6 || !(lbl_1_bss_16C[i].unk00 == 0 && lbl_1_bss_16C[i].unk04 == 0)) ? 1 : var_r19;
                    if (lbl_1_bss_16C[i].unk18 != 6 && (lbl_1_bss_16C[i].unk00 != 0 || lbl_1_bss_16C[i].unk04 != 0)) {
                        temp_f20 = lbl_1_bss_16C[i].unk00 * lbl_1_bss_16C[i].unk00 + lbl_1_bss_16C[i].unk04 * lbl_1_bss_16C[i].unk04;
                        spAC = sqrtf(temp_f20) + (rand8() / 256.0) * 0.01;
                        if (spB0 > spAC) {
                            var_r24 = i;
                            spB0 = spAC;
                        }
                    }
                }
                if (var_r24 != -1) {
                    lbl_1_bss_16C[var_r24].unk18 = 6;
                    lbl_1_bss_16C[var_r24].unk1C = 0;
                    lbl_1_data_170[0]++;
                    lbl_1_bss_16C[var_r24].unk08 = lbl_1_data_170[0] - 1;
                }
                if (var_r19 == 0) {
                    lbl_1_bss_78 = 5;
                    lbl_1_bss_74 = 0;
                }
            }
            break;
        case 5:
            lbl_1_bss_74++;
            if (lbl_1_bss_74 == 5 && lbl_1_bss_9C[1].unk00 < 3) {
                lbl_1_bss_9C[1].unk04[lbl_1_bss_9C[1].unk00] = 0.0f;
                lbl_1_bss_9C[1].unk00++;
            }
            if (lbl_1_bss_74 == 5) {
                s32 sp120[20] = { 0 };

                for (i = 0; i < 20; i++) {
                    lbl_1_bss_16C[i].unk18 = 7;
                    lbl_1_bss_16C[i].unk1C = (19 - lbl_1_bss_16C[i].unk08) * 3;
                    do {
                        temp_r21 = rand8() % 20;
                    } while (sp120[temp_r21] != 0);
                    sp120[temp_r21] = 1;
                    lbl_1_bss_16C[i].unk00 = temp_r21 % 5;
                    lbl_1_bss_16C[i].unk04 = temp_r21 / 5;
                }
            }
            if (lbl_1_bss_74 == 115 && lbl_1_data_1A0 != -1) {
                HuAudSeqFadeOut(lbl_1_data_1A0, 1000);
                lbl_1_data_1A0 = -1;
            }
            if (lbl_1_bss_74 == 145) {
                lbl_1_bss_84++;
            }
            break;
    }
    for (i = 0; i < 20; i++) {
        temp_r29 = &Hu3DData[arg0->model[i + 7]];
        temp_r26 = &Hu3DData[arg0->model[i + 27]];
        var_f18 = temp_r29->pos.x;
        var_f31 = temp_r29->pos.y;
        spA8 = temp_r29->pos.z;
        var_f23 = temp_r29->rot.x;
        spA4 = temp_r29->rot.y;
        temp_r31 = &lbl_1_bss_16C[i];
        switch (lbl_1_bss_16C[i].unk18) {
            case 2:
                temp_r31->unk1C++;
                temp_r31->unk08 -= (temp_r31->unk08 > 0);
                var_f23 = 180.0f;
                if (temp_r31->unk08 == 0) {
                    if (var_f31 > 0.0f && var_f31 + temp_r31->unk10 <= 0.0f && lbl_1_bss_9C[7].unk00 < 3) {
                        lbl_1_bss_9C[7].unk04[lbl_1_bss_9C[7].unk00] = 0.0f;
                        lbl_1_bss_9C[7].unk00++;
                    }
                    var_f31 += temp_r31->unk10;
                }
                if (var_f31 < 150.0 * sind(ABS(var_f23))) {
                    temp_r31->unk10 = 0.0f;
                    var_f31 = 150.0 * sind(ABS(var_f23));
                }
                break;
            case 3:
                temp_r31->unk1C++;
                var_f31 = 2.0 * (temp_r31->unk1C / 35.0) - 1.0;
                var_f31 = 1.0f - var_f31 * var_f31;
                var_f31 *= 200.0f;
                var_f23 = 180.0 + 360.0 * (temp_r31->unk1C / 35.0) * 0.5;
                if (temp_r31->unk1C >= 35) {
                    var_f31 = 0.0f;
                    temp_r31->unk18 = 4;
                    temp_r31->unk1C = 0;
                }
                break;
            case 4:
                temp_r31->unk1C++;
                var_f23 = 0.0f;
                if (lbl_1_bss_16C->unk18 == 4) {
                    temp_r31->unk1C = lbl_1_bss_16C->unk1C;
                }
                if (temp_r31->unk1C > 120) {
                    temp_r31->unk18++;
                    temp_r31->unk1C = 0;
                }
                break;
            case 5:
                if (i == 0 && temp_r31->unk1C == 0 && lbl_1_bss_9C[9].unk00 < 3) {
                    lbl_1_bss_9C[9].unk04[lbl_1_bss_9C[9].unk00] = 0.0f;
                    lbl_1_bss_9C[9].unk00++;
                }
                temp_r31->unk1C++;
                var_f31 = 2.0 * (temp_r31->unk1C / 45.0) - 1.0;
                var_f31 = 1.0f - var_f31 * var_f31;
                var_f31 *= 200.0f;
                var_f23 = 360.0 * (temp_r31->unk1C / 45.0) * 1.5;
                if (temp_r31->unk1C >= 45) {
                    var_f31 = 0.0f;
                    lbl_1_bss_78 = 3;
                    lbl_1_bss_74 = 0;
                    temp_r31->unk18 = 0;
                    temp_r31->unk1C = 0;
                }
                break;
            case 6:
                temp_r31->unk1C++;
                spA0 = 20.0f;
                temp_f30 = 100.0 + 200.0 * (temp_r31->unk00 - 2.5);
                temp_f29 = 100.0 + 200.0 * (temp_r31->unk04 - 2.0);
                var_f28 = -400.0f;
                var_f27 = -300.0f;
                sp9C = sqrtf((temp_f30 - var_f28) * (temp_f30 - var_f28) + (temp_f29 - var_f27) * (temp_f29 - var_f27));
                temp_f19 = sp9C / spA0;
                temp_f26 = temp_r31->unk1C * spA0;
                temp_f26 = (temp_f26 >= sp9C) ? 1.0f : (temp_f26 / sp9C);
                temp_f26 = 0.75 * temp_f26 + 0.25 * (1.0f - (1.0f - temp_f26) * (1.0f - temp_f26));
                sp98 = 1.0f - temp_f26;
                var_f18 = temp_f30 * sp98 + var_f28 * temp_f26;
                spA8 = temp_f29 * sp98 + var_f27 * temp_f26;
                var_f31 = (temp_r31->unk08 * 10 < temp_r31->unk1C * spA0) ? temp_r31->unk08 * 10 : temp_r31->unk1C * spA0;
                temp_f19 = 4.0f * (temp_r31->unk1C / temp_f19) - 2.0f;
                temp_f19 = 4.0f - temp_f19 * temp_f19;
                var_f31 = temp_f19 / 4.0 * temp_f26 * 0.5 * (temp_r31->unk08 * 10 + 100) + temp_f26 * temp_r31->unk08 * 10.0f;
                if (temp_f26 >= 1.0f) {
                    temp_r31->unk18 = 0;
                    temp_r31->unk1C = 0;
                    temp_r31->unk00 = 0;
                    temp_r31->unk04 = 0;
                    var_f31 = temp_r31->unk08 * 10;
                }
                break;
            case 7:
                temp_r31->unk1C++;
                if (temp_r31->unk1C == 60 && i != 0) {
                    lbl_1_data_170[0]--;
                }
                if (temp_r31->unk1C >= 60) {
                    sp94 = 100.0 + 200.0 * (temp_r31->unk00 - 2.5);
                    sp90 = 100.0 + 200.0 * (temp_r31->unk04 - 2.0);
                    sp8C = -400.0f;
                    sp88 = -300.0f;
                    temp_f21 = (temp_r31->unk1C - 60) / 50.0;
                    // Cast required to match.
                    temp_f21 = (double)(1.0f - (1.0f - temp_f21) * (1.0f - temp_f21));
                    sp84 = 1.0f - temp_f21;
                    var_f18 = sp8C * sp84 + sp94 * temp_f21;
                    spA8 = sp88 * sp84 + sp90 * temp_f21;
                    var_f31 = temp_r31->unk08 * 10 * sp84;
                    if (temp_f21 >= 1.0f) {
                        temp_r31->unk18 = 0;
                        temp_r31->unk1C = 0;
                        temp_r31->unk08 = 0;
                        lbl_1_data_170[0] = 0;
                    }
                }
                break;
            case 8:
                if (temp_r31->unk1C == 0) {
                    if (lbl_1_bss_9C[(temp_r31->unk20 > 0) ? 3 : 4].unk00 < 3) {
                        lbl_1_bss_9C[(temp_r31->unk20 > 0) ? 3 : 4].unk04[lbl_1_bss_9C[(temp_r31->unk20 > 0) ? 3 : 4].unk00] = 0.0f;
                        lbl_1_bss_9C[(temp_r31->unk20 > 0) ? 3 : 4].unk00++;
                    }
                }
                temp_r31->unk1C++;
                var_f31 = 2.0 * (temp_r31->unk1C / 75.0) - 1.0;
                var_f31 = 1.0f - var_f31 * var_f31;
                var_f31 *= 400.0f;
                var_f23 = 360.0 * (temp_r31->unk1C / 75.0) * 3.0;
                if (temp_r31->unk1C == 1) {
                    Hu3DParticleCntSet(lbl_1_bss_88->model[5], 0);
                }
                sp80 = 100.0 + 200.0 * (temp_r31->unk00 - 2.5);
                sp7C = 100.0 + 200.0 * (temp_r31->unk04 - 2.0);
                sp78 = (temp_r31->unk0C == 0) ? -640.0 : 640.0;
                sp74 = (temp_r31->unk0C == 0) ? 0.0 : 0.0;
                sp70 = temp_r31->unk1C / 75.0;
                sp6C = 1.0f - sp70;
                var_f31 += sp70 * (lbl_1_data_170[temp_r31->unk0C] * 10 + 33);
                var_f18 = sp80 * sp6C + sp78 * sp70;
                spA8 = sp7C * sp6C + sp74 * sp70;
                lbl_1_data_1DC[0] = var_f18;
                lbl_1_data_1DC[1] = var_f31;
                lbl_1_data_1DC[2] = spA8;
                if (temp_r31->unk1C >= 75) {
                    var_f31 = lbl_1_data_170[temp_r31->unk0C] * 10 + 33;
                    lbl_1_data_170[temp_r31->unk0C]++;
                    lbl_1_data_1A4[temp_r31->unk0C] += temp_r31->unk20;
                    lbl_1_data_1AC[temp_r31->unk0C] = temp_r31->unk20;
                    lbl_1_data_1B4[temp_r31->unk0C] = 0;
                    lbl_1_data_1A4[temp_r31->unk0C] = (lbl_1_data_1A4[temp_r31->unk0C] < 0) ? 0 : lbl_1_data_1A4[temp_r31->unk0C];
                    spC8[temp_r31->unk0C]->unk34 = 5;
                    spC8[temp_r31->unk0C]->unk38 = 0;
                    temp_r31->unk18 = 9;
                    temp_r31->unk1C = 0;
                    if (lbl_1_bss_9C[(temp_r31->unk20) > 0 ? 5 : 6].unk00 < 3) {
                        lbl_1_bss_9C[(temp_r31->unk20) > 0 ? 5 : 6].unk04[lbl_1_bss_9C[(temp_r31->unk20) > 0 ? 5 : 6].unk00] = 0.0f;
                        lbl_1_bss_9C[(temp_r31->unk20) > 0 ? 5 : 6].unk00++;
                    }
                    if (lbl_1_data_1A4[temp_r31->unk0C] >= 50 || lbl_1_data_170[0] + lbl_1_data_170[1] >= 20) {
                        lbl_1_bss_68 = (lbl_1_data_1A4[temp_r31->unk0C] >= 50) ? temp_r31->unk0C
                            : (lbl_1_data_1A4[0] > lbl_1_data_1A4[1])          ? 0
                            : (lbl_1_data_1A4[0] < lbl_1_data_1A4[1])          ? 1
                                                                               : 4;
                        spC8[1 - temp_r31->unk0C]->unk34 = 7;
                        spC8[1 - temp_r31->unk0C]->unk38 = 0;
                    }
                }
                break;
        }
        temp_r29->pos.x = temp_r26->pos.x = var_f18;
        temp_r29->pos.y = var_f31;
        temp_r29->pos.z = temp_r26->pos.z = spA8;
        temp_r29->rot.x = temp_r26->rot.x = var_f23;
        temp_r29->rot.y = spA4;
        if (temp_r29->pos.y <= 0.0f || temp_r31->unk18 == 9) {
            Hu3DModelAttrSet(arg0->model[i + 7], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(arg0->model[i + 27], HU3D_ATTR_DISPOFF);
            temp_r26->pos.y = (temp_r31->unk18 != 9) ? 0.0f : temp_r29->pos.y;
        }
        else {
            Hu3DModelAttrReset(arg0->model[i + 7], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[i + 27], HU3D_ATTR_DISPOFF);
        }
    }
    {
        s32 var_r18 = lbl_1_data_25C;
        float spD0[][4] = { { 2500.0f, 0.0f, -100.0f, -40.0f }, { 2775.0f, 314.0f, -100.0f, -38.75f }, { 875.0f, 116.0f, -100.0f, -15.0f },
            { 1625.0f, -416.0f, -340.0f, -30.25f }, { 875.0f, 116.0f, -100.0f, -30.0f } };

        if (lbl_1_data_25C == -1) {
            lbl_1_data_25C = 1;
            lbl_1_bss_34 = 0;
            lbl_1_bss_38 = 0.0f;
        }
        if (lbl_1_bss_80 == 1003 && lbl_1_bss_84 == 1) {
            lbl_1_data_25C = 2;
            lbl_1_bss_34 = 0;
            lbl_1_bss_38 = 0.0f;
        }
        if (lbl_1_bss_80 == 1004 && lbl_1_data_25C != 0) {
            lbl_1_data_25C = 0;
            lbl_1_bss_34 = 1;
            lbl_1_bss_38 = 0.0f;
        }
        if (lbl_1_bss_80 == 1007 && lbl_1_bss_84 == 1) {
            lbl_1_data_25C = 3;
            lbl_1_bss_34 = 0;
            lbl_1_bss_38 = 0.0f;
        }
        if (var_r18 != lbl_1_data_25C && var_r18 != -1) {
            lbl_1_data_260 = CZoom;
            lbl_1_data_264 = Center.y;
            lbl_1_data_268 = Center.z;
            lbl_1_data_26C = CRot.x;
        }
        if (lbl_1_bss_38 < 1.0f) {
            if (lbl_1_bss_34 == 0) {
                lbl_1_bss_38 = 1.0 - 0.95 * (1.0f - lbl_1_bss_38);
                var_f22 = lbl_1_bss_38;
            }
            else {
                lbl_1_bss_38 += 0.011111111111111112;
                lbl_1_bss_38 = (lbl_1_bss_38 > 1.0f) ? 1.0f : lbl_1_bss_38;
                var_f22 = 0.5 + -0.5 * cosd(180.0f * lbl_1_bss_38);
            }
            lbl_1_bss_38 = (lbl_1_bss_38 > 1.0f) ? 1.0f : lbl_1_bss_38;
            CZoom = var_f22 * spD0[lbl_1_data_25C][0] + lbl_1_data_260 * (1.0f - var_f22);
            Center.y = var_f22 * spD0[lbl_1_data_25C][1] + lbl_1_data_264 * (1.0f - var_f22);
            Center.z = var_f22 * spD0[lbl_1_data_25C][2] + lbl_1_data_268 * (1.0f - var_f22);
            CRot.x = var_f22 * spD0[lbl_1_data_25C][3] + lbl_1_data_26C * (1.0f - var_f22);
        }
    }
}

const s32 lbl_1_rodata_408[] = { MAKE_MESSID(43, 3), MAKE_MESSID(43, 4), MAKE_MESSID(43, 5), MAKE_MESSID(43, 6), MAKE_MESSID(43, 7),
    MAKE_MESSID(43, 8), MAKE_MESSID(43, 9), MAKE_MESSID(43, 10), 0 };

void fn_1_6DAC(void)
{
    UnkM448Struct_00 *sp8[2];
    s16 var_r29;
    s16 temp_r31;
    u32 temp_r26;
    s32 i;

    var_r29 = 0;
    for (i = 0; i < 2; i++) {
        sp8[i] = lbl_1_bss_8C[i]->data;
    }
    HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
    HuWinComKeyReset();
    temp_r31 = HuWinExCreateStyled(-10000.0f, 60.0f, 280, 120, -1, 1);
    HuWinExAnimIn(temp_r31);
    HuWinBGTPLvlSet(temp_r31, 0.8f);
    HuWinMesSpeedSet(temp_r31, 1);
    HuWinDisablePlayerSet(
        temp_r31, 0xF & ((sp8[0]->unk0C != -1) ? ~(1 << sp8[0]->unk0C) : 0xF) & ((sp8[1]->unk0C != -1) ? ~(1 << sp8[1]->unk0C) : 0xF));
    HuWinMesColSet(temp_r31, 0);
    HuWinMesSet(temp_r31, MAKE_MESSID(43, 1));
    if (((sp8[0]->unk0C == -1) || (sp8[0]->unk08 == -1)) && ((sp8[1]->unk0C == -1) || (sp8[1]->unk08 == -1))) {
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
    }
    HuWinMesWait(temp_r31);
    if (sp8[0]->unk0C != -1 || sp8[1]->unk0C != -1) {
        HuWinMesColSet(temp_r31, 0);
        HuWinMesSet(temp_r31, MAKE_MESSID(43, 2));
        if (sp8[0]->unk0C == -1 && sp8[1]->unk0C == -1) {
            HuPrcSleep(60);
            var_r29 = 1;
        }
        else {
            var_r29 = HuWinChoiceGet(temp_r31, 0);
        }
    }
    else {
        var_r29 = 1;
    }
    if (var_r29 == 0) {
        i = 0;
        while ((temp_r26 = lbl_1_rodata_408[i++]) != 0) {
            HuWinMesColSet(temp_r31, 0);
            HuWinMesSet(temp_r31, temp_r26);
            if ((sp8[0]->unk0C == -1 || sp8[0]->unk08 == -1) && (sp8[1]->unk0C == -1 || sp8[1]->unk08 == -1)) {
                HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
            }
            HuWinMesWait(temp_r31);
        }
    }
    else {
        HuWinMesColSet(temp_r31, 0);
        HuWinMesSet(temp_r31, MAKE_MESSID(43, 10));
        if ((sp8[0]->unk0C == -1 || sp8[0]->unk08 == -1) && (sp8[1]->unk0C == -1 || sp8[1]->unk08 == -1)) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
        }
        HuWinMesWait(temp_r31);
    }
    HuWinExAnimOut(temp_r31);
    HuWinExCleanup(temp_r31);
    lbl_1_bss_10 = 0;
    HuPrcEnd();
}

void fn_1_7148(omObjData *arg0)
{
    float temp_f31;
    UnkM448Struct_00 *spC[2];
    s32 sp8;
    s32 i;

    for (i = 0; i < 13; i++) {
        s32 sp14[] = { 0x0000078E, 0x0000078F, 0x00000790, 0x00000791, 0x00000792, 0x00000793, 0x00000794, 0x00000795, 0x00000796, 0x00000797,
            0x00000798, 0x00000799, 0x0000079A };

        if (lbl_1_bss_9C[i].unk00 > 3) {
            lbl_1_bss_9C[i].unk00 = 3;
        }
        if (lbl_1_bss_9C[i].unk00 > 0) {
            sp8 = HuAudFXPlay(sp14[i]);
            lbl_1_bss_9C[i].unk00--;
        }
    }
    for (i = 0; i < 2; i++) {
        spC[i] = lbl_1_bss_8C[i]->data;
    }
    if (omSysExitReq != 0 && WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        arg0->func = fn_1_9B00;
    }
    switch (lbl_1_bss_80) {
        case 1000:
            if (WipeStatGet() == 0) {
                lbl_1_bss_80++;
                lbl_1_bss_84 = 0;
            }
            break;
        case 1001:
            lbl_1_bss_84++;
            if (lbl_1_bss_84 == 1) {
                Hu3DModelAttrReset(lbl_1_bss_88->model[1], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(lbl_1_bss_88->model[2], HU3D_MOTATTR_PAUSE);
            }
            if (lbl_1_bss_84 > 0 && lbl_1_bss_84 <= 40 && lbl_1_bss_84 % 10 == 0 && lbl_1_bss_9C[12].unk00 < 3) {
                lbl_1_bss_9C[12].unk04[lbl_1_bss_9C[12].unk00] = 0.0f;
                lbl_1_bss_9C[12].unk00++;
            }
            if (lbl_1_bss_84 == 50 && lbl_1_bss_9C[10].unk00 < 3) {
                lbl_1_bss_9C[10].unk04[lbl_1_bss_9C[10].unk00] = 0.0f;
                lbl_1_bss_9C[10].unk00++;
            }
            if (lbl_1_bss_84 == 200 && lbl_1_bss_9C[11].unk00 < 3) {
                lbl_1_bss_9C[11].unk04[lbl_1_bss_9C[11].unk00] = 0.0f;
                lbl_1_bss_9C[11].unk00++;
            }
            if (lbl_1_bss_84 >= 210) {
                temp_f31 = (lbl_1_bss_84 - 210) / 30.0;
                Hu3DModelAmbSet(lbl_1_bss_8C[0]->model[0], temp_f31, temp_f31, temp_f31);
                Hu3DModelAmbSet(lbl_1_bss_8C[1]->model[0], temp_f31, temp_f31, temp_f31);
            }
            if (lbl_1_bss_84 > 240) {
                lbl_1_bss_80++;
                lbl_1_bss_84 = 0;
                Hu3DModelAttrSet(lbl_1_bss_88->model[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_88->model[2], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_88->model[0], HU3D_ATTR_DISPOFF);
                Hu3DModelAmbSet(lbl_1_bss_8C[0]->model[0], 1.0f, 1.0f, 1.0f);
                Hu3DModelAmbSet(lbl_1_bss_8C[1]->model[0], 1.0f, 1.0f, 1.0f);
            }
            break;
        case 1002:
            lbl_1_bss_84++;
            if (lbl_1_bss_84 > 60) {
                lbl_1_bss_80++;
                if (spC[0]->unk08 != -1 && spC[1]->unk08 != -1) {
                    lbl_1_bss_80++;
                }
                lbl_1_bss_7C = 0;
                lbl_1_bss_84 = 0;
                if (lbl_1_data_1A0 == -1) {
                    lbl_1_data_1A0 = HuAudSeqPlay(0x3D);
                }
            }
            break;
        case 1003:
            lbl_1_bss_84++;
            if (lbl_1_bss_84 == 1) {
                HuPrcChildCreate(fn_1_6DAC, 100, 0x2000, 0, HuPrcCurrentGet());
                lbl_1_bss_10 = 1;
            }
            else if (lbl_1_bss_10 == 0) {
                lbl_1_bss_80++;
                lbl_1_bss_84 = 0;
            }
            break;
        case 1004:
            lbl_1_bss_84 += (lbl_1_bss_84 >= 2);
            if (lbl_1_bss_84 == 5 && lbl_1_data_198 < 0) {
                lbl_1_data_198 = MGSeqCreate(3, 0);
            }
            if (lbl_1_bss_84 >= 5 && lbl_1_data_1A0 == -1 && (MGSeqStatGet(lbl_1_data_198) & 0x10)) {
                lbl_1_data_1A0 = HuAudSeqPlay(0x3E);
            }
            if (lbl_1_bss_84 >= 5 && MGSeqStatGet(lbl_1_data_198) == 0 && lbl_1_data_198 >= 0) {
                lbl_1_bss_80++;
                lbl_1_data_198 = -1;
                lbl_1_bss_84 = 0;
            }
            break;
        case 1005:
            lbl_1_bss_84++;
            if (lbl_1_data_19A != -1) {
                MGSeqParamSet(lbl_1_data_19A, 1, ((lbl_1_bss_0 < 0 ? 0 : lbl_1_bss_0) + REFRESH_RATE - 1) / REFRESH_RATE);
                lbl_1_bss_0--;
                if (lbl_1_bss_0 <= -30) {
                    MGSeqParamSet(lbl_1_data_19A, 2, -1);
                    lbl_1_data_19A = -1;
                }
            }
            if (lbl_1_bss_68 != -1) {
                lbl_1_bss_80 = 1006;
                lbl_1_bss_84 = 0;
            }
            break;
        case 1006:
            lbl_1_bss_84++;
            if (lbl_1_data_198 < 0 && lbl_1_bss_84 == 1) {
                if (lbl_1_data_19A != -1) {
                    MGSeqParamSet(lbl_1_data_19A, 2, -1);
                }
                if (lbl_1_data_19C != -1) {
                    MGSeqParamSet(lbl_1_data_19C, 2, -1);
                }
                lbl_1_data_198 = MGSeqCreate(3, 1);
                if (lbl_1_data_1A0 == -1) {
                    break;
                }
                HuAudSeqFadeOut(lbl_1_data_1A0, 100);
                lbl_1_data_1A0 = -1;
            }
            else if (MGSeqStatGet(lbl_1_data_198) == 0) {
                lbl_1_bss_80++;
                lbl_1_bss_84 = 0;
            }
            break;
        case 1007:
            lbl_1_bss_84++;
            if (lbl_1_bss_84 == 1) {
                if (lbl_1_bss_68 != 4) {
                    if (spC[lbl_1_bss_68]->unk08 != -1) {
                        HuAudSStreamPlay(1);
                    }
                    else {
                        HuAudSStreamPlay(3);
                    }
                    GWPlayerCoinWinSet(spC[lbl_1_bss_68]->unk04, 10);
                }
                else if (lbl_1_bss_68 == 4) {
                    HuAudSStreamPlay(4);
                }
            }
            if (210.0f < lbl_1_bss_84) {
                lbl_1_data_198 = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                arg0->func = fn_1_9B00;
            }
            break;
    }
}

void fn_1_7DC4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    s16 i;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk00_s16 = i * 2 + 100;
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (!var_r31->unk2C) {
            break;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (var_r31->unk00_s16 == 100) {
            var_r31->unk00_s16 = (lbl_1_data_1DC[0] == 0.0f && lbl_1_data_1DC[1] == 0.0f && lbl_1_data_1DC[2] == 0.0f) ? 0 : var_r31->unk00_s16;
            var_r31->unk34.x = lbl_1_data_1DC[0] + 75.0 * (rand8() / 255.0);
            var_r31->unk34.y = lbl_1_data_1DC[1] + 75.0 * (rand8() / 255.0);
            var_r31->unk34.z = lbl_1_data_1DC[2] + 75.0 * (rand8() / 255.0);
            var_r31->unk40.r = 0xFF;
            var_r31->unk40.g = 0xF0;
            var_r31->unk40.b = 0xA0;
            var_r31->unk40.a = 0xFF;
            var_r31->unk30 = 0.785f;
            var_r31->unk2C = 40.0f;
        }
        if (var_r31->unk00_s16 <= 100) {
            var_r31->unk34.y -= 3.0f;
            var_r31->unk2C = ((var_r31->unk00_s16 > 50) ? (var_r31->unk00_s16 - 50) / 50.0 : 0.0) * (rand8() * 80 / 255.0);
        }
        if (var_r31->unk00_s16 == 0) {
            var_r31->unk2C = 0.0f;
        }
        var_r31->unk00_s16 -= (var_r31->unk00_s16 > 0);
    }
}

void fn_1_81C0(omObjData *arg0)
{
    UnkM448Struct_00 *temp_r26;
    UnkM448Struct_00 *temp_r23;
    s32 temp_r29;
    s32 temp_r25;
    s32 i, j, k;
    s32 var_r27;

    memset(lbl_1_bss_16C, 0, sizeof(lbl_1_bss_16C));
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M448, 0));
    Hu3DModelShadowMapSet(arg0->model[0]);
    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(arg0->model[0], 0);
    Hu3DMotionTimeSet(arg0->model[0], 20.0f);
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
    arg0->model[6] = Hu3DHookFuncCreate(fn_1_4FC);
    Hu3DModelLayerSet(arg0->model[6], 6);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M448, 1));
    Hu3DModelShadowMapSet(arg0->model[1]);
    Hu3DModelLayerSet(arg0->model[1], 0);
    Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[1], HU3D_MOTATTR_PAUSE);
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M448, 2));
    Hu3DModelShadowMapSet(arg0->model[2]);
    Hu3DModelLayerSet(arg0->model[2], 0);
    Hu3DModelPosSet(arg0->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[2], HU3D_MOTATTR_PAUSE);
    {
        s32 sp9C[] = { DATA_MAKE_NUM(DATADIR_M448, 9), DATA_MAKE_NUM(DATADIR_M448, 10), DATA_MAKE_NUM(DATADIR_M448, 11),
            DATA_MAKE_NUM(DATADIR_M448, 12), DATA_MAKE_NUM(DATADIR_M448, 13), DATA_MAKE_NUM(DATADIR_M448, 14), DATA_MAKE_NUM(DATADIR_M448, 16),
            DATA_MAKE_NUM(DATADIR_M448, 15), DATA_MAKE_NUM(DATADIR_M448, 17) };

        for (i = 0; i < 2; i++) {
            temp_r26 = lbl_1_bss_8C[i]->data;
            arg0->model[i + 3] = Hu3DModelCreateFile(sp9C[(temp_r26->unk08 == -1) ? 8 : temp_r26->unk08]);
            Hu3DModelShadowMapSet(arg0->model[i + 3]);
            Hu3DModelLayerSet(arg0->model[i + 3], 0);
            Hu3DModelRotSet(arg0->model[i + 3], 0.0f, (temp_r26->unk08 == -1) ? (1 - i) * 180 : i * 180, 0.0f);
        }
    }
    {
        s32 sp110[] = { -10, -5, -5, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 20, 20 };
        s32 spC0[] = { 0, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5 };
        s32 sp34[] = { DATA_MAKE_NUM(DATADIR_M448, 3), DATA_MAKE_NUM(DATADIR_M448, 4), DATA_MAKE_NUM(DATADIR_M448, 5), DATA_MAKE_NUM(DATADIR_M448, 6),
            DATA_MAKE_NUM(DATADIR_M448, 7), DATA_MAKE_NUM(DATADIR_M448, 8) };
        s32 sp1C[] = { -1, -1, -1, -1, -1, -1 };

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 5; j++) {
                temp_r29 = j + i * 5;
                lbl_1_bss_16C[temp_r29].unk00 = j;
                lbl_1_bss_16C[temp_r29].unk04 = i;
                lbl_1_bss_16C[temp_r29].unk08 = 0;
                lbl_1_bss_16C[temp_r29].unk0C = -1;
                lbl_1_bss_16C[temp_r29].unk18 = 1;
                temp_r25 = 19 - temp_r29;
                lbl_1_bss_16C[temp_r29].unk20 = sp110[temp_r25];
                sp110[temp_r25] = 0;
                lbl_1_bss_16C[temp_r29].unk1C = 0;
                for (k = 0; k < 2; k++) {
                    var_r27 = (k == 0) ? 7 : 27;
                    if (sp1C[spC0[temp_r25]] == -1) {
                        if (k == 1) {
                            sp1C[spC0[temp_r25]] = temp_r29;
                        }
                        arg0->model[var_r27 + temp_r29] = Hu3DModelCreateFile(sp34[spC0[temp_r25]]);
                    }
                    else {
                        arg0->model[var_r27 + temp_r29] = Hu3DModelLink(arg0->model[var_r27 + sp1C[spC0[temp_r25]]]);
                    }
                    Hu3DModelPosSet(arg0->model[var_r27 + temp_r29], 100.0 + 200.0 * (lbl_1_bss_16C[temp_r29].unk00 - 2.5), (k == 0) ? 4000 : 0,
                        100.0 + 200.0 * (lbl_1_bss_16C[temp_r29].unk04 - 2.0));
                    if (k == 0) {
                        Hu3DModelShadowSet(arg0->model[var_r27 + temp_r29]);
                    }
                    else {
                        Hu3DModelAttrSet(arg0->model[var_r27 + temp_r29], HU3D_ATTR_DISPOFF);
                        Hu3DModelShadowMapSet(arg0->model[var_r27 + temp_r29]);
                    }
                }
            }
        }
    }
    arg0->model[5] = Hu3DParticleCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M448, 30), MEMORY_DEFAULT_NUM)), 70);
    Hu3DModelPosSet(arg0->model[5], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[5], 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(arg0->model[5], 3);
    Hu3DModelAttrReset(arg0->model[5], HU3D_ATTR_DISPOFF);
    Hu3DParticleColSet(arg0->model[5], 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(arg0->model[5], 1.0f);
    Hu3DParticleHookSet(arg0->model[5], fn_1_7DC4);
    Hu3DParticleCntSet(arg0->model[5], 0);
    Hu3DParticleBlendModeSet(arg0->model[5], 1);
    for (i = 0; i < 10; i++) {
        s32 sp14[] = { 100, 485 };
        s32 sp74[] = { 0, 0, 16, -4, -36, 0, 0, 16, -4, -36 };
        s32 sp4C[] = { 0, 0, 2, 2, -2, 0, 0, 2, 2, -2 };

        if (lbl_1_data_0[i] == DATADIR_MGCONST) {
            temp_r23 = lbl_1_bss_8C[i == 4 ? 0 : (i == 9 ? 1 : 0)]->data;
            lbl_1_data_28[i]
                = espEntry((temp_r23->unk08 == -1) ? DATA_MAKE_NUM(DATADIR_M448, 29) : DATA_MAKE_NUM(lbl_1_data_0[i], temp_r23->unk08), 0, 0);
        }
        else {
            lbl_1_data_28[i] = espEntry(lbl_1_data_0[i], 0, 0);
        }
        espDrawNoSet(lbl_1_data_28[i], 0);
        espAttrSet(lbl_1_data_28[i], HUSPR_ATTR_NOANIM | HUSPR_ATTR_DISPOFF);
        espBankSet(lbl_1_data_28[i], 0);
        espPriSet(lbl_1_data_28[i], 128 - i);
        espPosSet(lbl_1_data_28[i], sp74[i] + sp14[i < 5 ? 0 : 1], sp4C[i] + 70);
        if (((i >= 5) ? i - 5 : i) != 0) {
            (void)1; // Required to match.
        }
        else {
            espTPLvlSet(lbl_1_data_28[i], 0.5f);
            espColorSet(lbl_1_data_28[i], 0, 0, 0);
        }
    }
    arg0->func = fn_1_4310;
}

void fn_1_8DD0(omObjData *arg0)
{
    s32 var_r28;
    s32 var_r27;
    UnkM448Struct_00 *temp_r31;
    UnkM448Struct_00 *sp30;
    s32 var_r26;
    s32 i;

    var_r28 = -1;
    var_r27 = -1;
    temp_r31 = arg0->data;
    sp30 = lbl_1_bss_8C[1 - arg0->work[0]]->data;
    memset(temp_r31, 0, sizeof(*temp_r31));
    temp_r31->unk00 = arg0->work[0];
    if (GWPlayerCfg->character == 14 || GWPlayerCfg[1].character == 14 || GWPlayerCfg[2].character == 14 || GWPlayerCfg[3].character == 14) {
        for (i = 0; i < 4; i++) {
            if (GWPlayerCfg[i].character == 14) {
                var_r28 = i;
            }
        }
        var_r27 = (GWPlayerCfg[var_r28].group == 0) ? 1 : 0;
        if (temp_r31->unk00 == 0) {
            temp_r31->unk04 = var_r27;
            var_r26 = var_r28;
        }
        else {
            temp_r31->unk04 = var_r28;
            var_r26 = var_r27;
        }
    }
    else {
        temp_r31->unk04 = (GWPlayerCfg[0].group == temp_r31->unk00) ? 0
            : GWPlayerCfg[1].group == temp_r31->unk00               ? 1
            : GWPlayerCfg[2].group == temp_r31->unk00               ? 2
            : GWPlayerCfg[3].group == temp_r31->unk00               ? 3
                                                                    : 4;
        var_r26 = (GWPlayerCfg[0].group == 1 - temp_r31->unk00) ? 0
            : (GWPlayerCfg[1].group == 1 - temp_r31->unk00)     ? 1
            : (GWPlayerCfg[2].group == 1 - temp_r31->unk00)     ? 2
            : (GWPlayerCfg[3].group == 1 - temp_r31->unk00)     ? 3
                                                                : 4;
    }
    if (temp_r31->unk04 == 4) {
        OSReport("m448:wrong player group\n");
        temp_r31->unk04 = temp_r31->unk00;
    }
    temp_r31->unk08 = (var_r28 != -1 && temp_r31->unk00 == 1) ? -1 : GWPlayerCfg[temp_r31->unk04].character;
    temp_r31->unk0C = (temp_r31->unk08 == -1 || GWPlayerCfg[temp_r31->unk04].iscom) ? -1 : GWPlayerCfg[temp_r31->unk04].pad_idx;
    temp_r31->unk10 = (temp_r31->unk0C != -1) ? 0 : GWPlayerCfg[temp_r31->unk04].diff;
    temp_r31->unk34 = 0;
    if (temp_r31->unk08 != -1) {
        arg0->model[0] = CharModelCreate(temp_r31->unk08, 2);
    }
    else {
        arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M448, 18));
    }
    Hu3DModelLayerSet(arg0->model[0], 0);
    CharModelLayerSetAll2(1);
    Hu3DModelShadowSet(arg0->model[0]);
    Hu3DModelAmbSet(arg0->model[0], 0.0f, 0.0f, 0.0f);
    for (i = 0; i < 11; i++) {
        if (temp_r31->unk08 != -1) {
            arg0->motion[i] = CharModelMotionCreate(temp_r31->unk08, lbl_1_data_50[i]);
        }
        else {
            arg0->motion[i] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_7C[i]);
        }
    }
    temp_r31->unk20 = (temp_r31->unk08 != -1) ? 0 : 0;
    temp_r31->unk24 = -1;
    Hu3DMotionSet(arg0->model[0], arg0->motion[temp_r31->unk20]);
    if (temp_r31->unk08 != -1) {
        Hu3DMotionTimeSet(arg0->model[0], (temp_r31->unk00 == 0) ? 0 : 80);
        Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
    }
    else {
        lbl_1_bss_20 = CharModelEffectNpcInit(arg0->model[0], arg0->motion[2], 1, 14);
        lbl_1_bss_24 = CharModelEffectNpcInit(arg0->model[0], arg0->motion[6], 5, 14);
    }
    arg0->trans.x = lbl_1_data_1BC[temp_r31->unk00][0];
    arg0->trans.y = lbl_1_data_1BC[temp_r31->unk00][1];
    arg0->trans.z = 0.0f;
    arg0->rot.y = (temp_r31->unk00 == 0) ? 90 : 270;
    arg0->rot.y = (temp_r31->unk08 != -1) ? 0 : (temp_r31->unk00 == 0) ? 90 : 270;
    arg0->scale.x = arg0->scale.y = arg0->scale.z = 1.0f;
    arg0->rot.x = arg0->rot.z = 0.0f;
    arg0->func = fn_1_1338;
}

void fn_1_9508(omObjData *arg0)
{
    lbl_1_bss_80 = 1000;
    lbl_1_bss_84 = 0;
    lbl_1_bss_78 = 0;
    lbl_1_bss_74 = 0;
    lbl_1_bss_64 = GXGetTexBufferSize(640, 480, GX_TF_RGB565, GX_FALSE, 0);
    lbl_1_bss_60 = GXGetTexBufferSize(160, 120, GX_TF_RGB565, GX_FALSE, 0U);
    lbl_1_bss_28 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_64, MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_28, 0, lbl_1_bss_64);
    lbl_1_bss_2C = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_60, MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_2C, 0, lbl_1_bss_60);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    arg0->func = fn_1_7148;
}

void ObjectSetup(void)
{
    omObjData *var_r30;
    s32 i;

    OSReport("******* M448 ObjectSetup *********\n");
    lbl_1_bss_70 = omInitObjMan(600, 0x2000);
    omGameSysInit(lbl_1_bss_70);
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
        Vec sp3C = { 0.0f, 10000.0f, 0.0f };
        Vec sp30 = { 0.0f, -1.0f, 0.0f };
        GXColor sp8 = { 0xFF, 0xFF, 0xFF, 0xFF };

        lbl_1_bss_6C = Hu3DGLightCreateV(&sp3C, &sp30, &sp8);
        Hu3DGLightStaticSet(lbl_1_bss_6C, 1);
        Hu3DGLightInfinitytSet(lbl_1_bss_6C);
        lbl_1_bss_6C = Hu3DGLightCreateV(&sp3C, &sp30, &sp8);
        Hu3DGLightStaticSet(lbl_1_bss_6C, 1);
        Hu3DGLightInfinitytSet(lbl_1_bss_6C);
    }
    {
        Vec sp24;
        Vec sp18;
        Vec spC;

        sp24.x = 0.0f;
        sp24.y = 10000.0f;
        sp24.z = 0.0f;
        sp18.x = 0.0f;
        sp18.y = 1.0f;
        sp18.z = 0.0f;
        spC.x = 0.0f;
        spC.y = 0.0f;
        spC.z = 0.5f;
        Hu3DShadowCreate(8.0f, 9000.0f, 11500.0f);
        Hu3DShadowTPLvlSet(0.75f);
        Hu3DShadowPosSet(&sp24, &sp18, &spC);
    }
    lbl_1_data_198 = -1;
    lbl_1_bss_68 = -1;
    HuWinInit(1);
    lbl_1_bss_88 = omAddObjEx(lbl_1_bss_70, 101, 47, 0, 1, fn_1_81C0);
    for (i = 0; i < 2; i++) {
        var_r30 = lbl_1_bss_8C[i] = omAddObjEx(lbl_1_bss_70, 100, 1, 11, 0, fn_1_8DD0);
        var_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM448Struct_00), MEMORY_DEFAULT_NUM);
        var_r30->work[0] = i;
    }
    lbl_1_bss_94 = omAddObjEx(lbl_1_bss_70, 32730, 0, 0, -1, omOutView);
    lbl_1_bss_98 = omAddObjEx(lbl_1_bss_70, 103, 0, 0, -1, fn_1_9508);
}

void fn_1_9B00(omObjData *arg0)
{
    s32 i;
    UnkM448Struct_00 *temp_r30;

    if (WipeStatGet() != 0) {
        return;
    }
    if (lbl_1_bss_28) {
        HuMemDirectFree(lbl_1_bss_28);
    }
    lbl_1_bss_28 = NULL;
    if (lbl_1_bss_2C) {
        HuMemDirectFree(lbl_1_bss_2C);
    }
    lbl_1_bss_2C = NULL;
    for (i = 0; i < 2; i++) {
        temp_r30 = lbl_1_bss_8C[i]->data;
        if (temp_r30->unk08 != -1) {
            CharModelKill(temp_r30->unk08);
        }
    }
    if (lbl_1_data_198 >= 0) {
        MGSeqKill(lbl_1_data_198);
    }
    MGSeqKillAll();
    HuAudAllStop();
    omOvlReturnEx(1, 1);
}
