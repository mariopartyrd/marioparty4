#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ char unk04[0xB4];
} StructBssC8; // Size 0xB8

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[5];
} StructBss1E8; // Size 0xC

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06[8];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C[4];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ float unk54;
    /* 0x58 */ float unk58;
    /* 0x5C */ float unk5C;
    /* 0x60 */ float unk60;
    /* 0x64 */ float unk64;
    /* 0x68 */ float unk68;
    /* 0x6C */ float unk6C;
    /* 0x70 */ float unk70;
    /* 0x74 */ float unk74;
    /* 0x78 */ float unk78;
    /* 0x7C */ float unk7C;
    /* 0x80 */ float unk80;
    /* 0x84 */ float unk84;
    /* 0x88 */ float unk88;
    /* 0x8C */ float unk8C;
    /* 0x90 */ float unk90;
    /* 0x94 */ float unk94;
    /* 0x98 */ float unk98;
    /* 0x9C */ float unk9C;
    /* 0xA0 */ s8 unkA0;
    /* 0xA1 */ s8 unkA1;
    /* 0xA2 */ s8 unkA2;
    /* 0xA3 */ s8 unkA3;
    /* 0xA4 */ u16 unkA4;
    /* 0xA6 */ u16 unkA6;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s32 unkB0;
    /* 0xB4 */ s32 unkB4;
    /* 0xB8 */ s32 unkB8;
    /* 0xBC */ s32 unkBC;
    /* 0xC0 */ s32 unkC0;
    /* 0xC4 */ float unkC4;
    /* 0xC8 */ char unkC8[4];
    /* 0xCC */ float unkCC;
    /* 0xD0 */ s32 unkD0;
    /* 0xD4 */ s32 unkD4;
    /* 0xD8 */ float unkD8;
    /* 0xDC */ float unkDC;
} StructBss200; // Size 0xE0

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
} StructBss190; // Size 0x2C

void fn_1_57C(s16 arg0);
void fn_1_AD0(s16 arg0);
void fn_1_F58(void);
void fn_1_2254(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_2744(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_47E4(void);
void fn_1_4B20(void);
void fn_1_9AF0(void);
void fn_1_DF98(void);
void fn_1_104A0(void);
void fn_1_10500(void);

s16 lbl_1_bss_5C2;
s16 lbl_1_bss_5C0; // unused
s16 lbl_1_bss_5BE;
s16 lbl_1_bss_5BC;
s16 lbl_1_bss_5BA;
s16 lbl_1_bss_5B8;
s32 lbl_1_bss_5B4;
s32 lbl_1_bss_5B0;
s32 lbl_1_bss_5AC;
s32 lbl_1_bss_5A8;
s32 lbl_1_bss_5A4;
s32 lbl_1_bss_594[4];
s32 lbl_1_bss_584[4];
s32 lbl_1_bss_580;
StructBss200 lbl_1_bss_200[4];
StructBss1E8 lbl_1_bss_1E8[2];
StructBss190 lbl_1_bss_190[2];
Process *lbl_1_bss_180[4];
StructBssC8 lbl_1_bss_C8;
Vec lbl_1_bss_BC;
Vec lbl_1_bss_B0;
Vec lbl_1_bss_A4;
void *lbl_1_bss_84[8];
void *lbl_1_bss_64[8];
u8 lbl_1_bss_60;
Vec lbl_1_bss_0[8];

s32 lbl_1_data_0[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

s32 lbl_1_data_20[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MARIOMOT, 2), DATA_MAKE_NUM(DATADIR_MARIOMOT, 3),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 21), DATA_MAKE_NUM(DATADIR_MARIOMOT, 26), DATA_MAKE_NUM(DATADIR_MARIOMOT, 27), DATA_MAKE_NUM(DATADIR_M419, 0),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 25), DATA_MAKE_NUM(DATADIR_MARIOMOT, 75), DATA_MAKE_NUM(DATADIR_MARIOMOT, 13),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 16) };

s32 lbl_1_data_4C[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MARIOMOT, 27), DATA_MAKE_NUM(DATADIR_MARIOMOT, 75),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 22) };

Vec lbl_1_data_5C[] = { { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f },
    { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f }, { 0.0f, 0.0f, 35.0f } };

void ObjectSetup(void)
{
    Process *temp_r3;

    temp_r3 = omInitObjMan(50, 0x2000);
    omGameSysInit(temp_r3);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    lbl_1_bss_C8.unk00 = omAddObjEx(temp_r3, 0x7FDA, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_C8.unk00->work[0] = 1;
    CRotM->x = -40.0f;
    CRotM->y = 0.0f;
    CRotM->z = 0.0f;
    CenterM->x = 0.0f;
    CenterM->y = 0.0f;
    CenterM->z = 3000.0f;
    CZoomM[0] = 1500.0f;
    Hu3DLighInit();
    lbl_1_bss_5C2 = Hu3DGLightCreate(10000.0f, 0.0f, 10000.0f, -1.0f, 0.0f, -1.0f, 0xFF, 0xFF, 0xFF);
    Hu3DGLightPosAimSet(lbl_1_bss_5C2, 0.0f, 4330.13f, 2500.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(lbl_1_bss_5C2);
    lbl_1_bss_BC.x = -500.0f;
    lbl_1_bss_BC.y = 4000.0f;
    lbl_1_bss_BC.z = 0.0f;
    lbl_1_bss_B0.x = lbl_1_bss_B0.z = 0.0f;
    lbl_1_bss_B0.y = 1.0f;
    lbl_1_bss_A4.x = 0.0f;
    lbl_1_bss_A4.y = 0.0f;
    lbl_1_bss_A4.z = 0.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_bss_BC, &lbl_1_bss_B0, &lbl_1_bss_A4);
    Hu3DBGColorSet(0, 0, 0);
    fn_1_F58();
    HuPrcChildCreate(fn_1_10500, 0x1000, 0x2000, 0, HuPrcCurrentGet());
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
}

void fn_1_4A0(void)
{
    s16 i;

    Hu3DLayerHookSet(1, fn_1_57C);
    for (i = 0; i < 8; i++) {
        lbl_1_bss_84[i] = HuMemDirectMallocNum(HEAP_DATA, 0x4800, MEMORY_DEFAULT_NUM);
        lbl_1_bss_64[i] = HuMemDirectMallocNum(HEAP_DATA, 0x9000, MEMORY_DEFAULT_NUM);
        lbl_1_bss_0[i].x = lbl_1_bss_0[i].y = 0.0f;
    }
}

void fn_1_57C(s16 arg0)
{
    Vec sp14;
    Vec sp8;
    ModelData *temp_r30;
    s16 var_r31;

    temp_r30 = &Hu3DData[lbl_1_bss_5BE];
    sp14 = temp_r30->pos;
    sp14.y += 50.0f;
    Hu3D3Dto2D(&sp14, 1, &sp8.x);
    var_r31 = sp8.x - 96.0f;
    var_r31 &= 0xFFF8;
    sp8.x = var_r31;
    if (sp8.x < 0.0f) {
        sp8.x = 0.0f;
    }
    if (sp8.x > 448.0f) {
        sp8.x = 448.0f;
    }
    var_r31 = sp8.y - 96.0f;
    var_r31 &= 0xFFF8;
    sp8.y = var_r31;
    if (sp8.y < 0.0f) {
        sp8.y = 0.0f;
    }
    if (sp8.y > 288.0f) {
        sp8.y = 288.0f;
    }
    lbl_1_bss_0[lbl_1_bss_60] = sp8;
    GXSetTexCopySrc(sp8.x, sp8.y, 192, 192);
    GXSetTexCopyDst(96, 96, GX_TF_RGB5A3, 1);
    GXCopyTex(lbl_1_bss_84[lbl_1_bss_60], 0);
    GXSetTexCopySrc(sp8.x, sp8.y, 192, 192);
    GXSetTexCopyDst(96, 96, GX_TF_Z24X8, 1);
    GXCopyTex(lbl_1_bss_64[lbl_1_bss_60], 0);
}

void fn_1_848(ModelData *arg0, Mtx arg1)
{
    Mtx44 sp10;
    GXColor spC;
    s16 i;

    C_MTXOrtho(sp10, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 8000.0f);
    GXSetProjection(sp10, GX_ORTHOGRAPHIC);
    MTXIdentity(arg1);
    GXLoadPosMtxImm(arg1, GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOp(GX_TEVSTAGE1, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z24X8, 0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(2);
    if (lbl_1_bss_5BC != 0) {
        for (i = 1; i < 8; i++) {
            spC.a = i * 24;
            GXSetTevColor(GX_TEVREG0, spC);
            fn_1_AD0((lbl_1_bss_60 - 8 + i) & 7);
        }
    }
    lbl_1_bss_60 = (lbl_1_bss_60 + 1) & 7;
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);
}

void fn_1_AD0(s16 arg0)
{
    GXTexObj sp58;
    GXTexObj sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    GXInitTexObj(&sp58, lbl_1_bss_84[arg0], 96, 96, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sp58, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sp58, GX_TEXMAP0);
    GXInitTexObj(&sp38, lbl_1_bss_64[arg0], 96, 96, GX_TF_Z24X8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&sp38, GX_TEXMAP1);
    sp2C.x = 0.0f;
    sp2C.y = 0.0f;
    sp2C.z = 0.0f;
    sp20.x = 640.0f;
    sp20.y = 0.0f;
    sp20.z = 0.0f;
    sp14.x = 640.0f;
    sp14.y = 480.0f;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 480.0f;
    sp8.z = 0.0f;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_FALSE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(lbl_1_bss_0[arg0].x, lbl_1_bss_0[arg0].y, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(lbl_1_bss_0[arg0].x + 192.0f, lbl_1_bss_0[arg0].y, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(lbl_1_bss_0[arg0].x + 192.0f, lbl_1_bss_0[arg0].y + 192.0f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(lbl_1_bss_0[arg0].x, lbl_1_bss_0[arg0].y + 192.0f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
}

void fn_1_F58(void)
{
    void *var_r29;
    StructBss1E8 *temp_r26;
    StructBss200 *temp_r31;
    Process *var_r25;
    float temp_f31;
    s16 var_r30;
    s32 var_r22;
    s32 var_r23;
    AnimData *var_r21;
    s32 i;
    s32 j;

    lbl_1_bss_5BC = 0;
    lbl_1_bss_5BA = 0;
    lbl_1_bss_5B0 = 0;
    HuAudSndGrpSet(0x2C);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 8), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelShadowMapSet(var_r30);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 9), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelShadowMapSet(var_r30);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 10), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r30);
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelShadowSet(var_r30);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 11), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelShadowSet(var_r30);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 12), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    lbl_1_bss_5B8 = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    temp_r26 = &lbl_1_bss_1E8[0];
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 13), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    temp_r26->unk00 = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    for (j = 0; j < 5; j++) {
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 14 + j), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r26->unk02[j] = Hu3DJointMotion(var_r30, var_r29);
    }
    Hu3DMotionSet(var_r30, temp_r26->unk02[0]);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r30);
    HuPrcChildCreate(fn_1_47E4, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    temp_r26 = &lbl_1_bss_1E8[1];
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 19), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    temp_r26->unk00 = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    for (j = 0; j < 5; j++) {
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 20 + j), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r26->unk02[j] = Hu3DJointMotion(var_r30, var_r29);
    }
    Hu3DMotionSet(var_r30, temp_r26->unk02[0]);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r30);
    HuPrcChildCreate(fn_1_4B20, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 25), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    lbl_1_bss_190[0].unk00 = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelAttrSet(var_r30, 1);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 26), MEMORY_DEFAULT_NUM, HEAP_DATA);
    lbl_1_bss_190[0].unk04 = Hu3DJointMotion(var_r30, var_r29);
    Hu3DMotionSet(var_r30, lbl_1_bss_190[0].unk04);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r30);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 27), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    lbl_1_bss_190[0].unk02 = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelAttrSet(var_r30, 1);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 28), MEMORY_DEFAULT_NUM, HEAP_DATA);
    lbl_1_bss_190[0].unk06 = Hu3DJointMotion(var_r30, var_r29);
    Hu3DMotionSet(var_r30, lbl_1_bss_190[0].unk04);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r30);
    lbl_1_bss_190[0].unk08 = 0;
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 29), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    lbl_1_bss_190[1].unk00 = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelAttrSet(var_r30, 1);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    lbl_1_bss_190[1].unk08 = 1;
    Hu3DModelShadowSet(var_r30);
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 30), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r29);
    lbl_1_bss_190[1].unk02 = var_r30;
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelAttrSet(var_r30, 1);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    for (i = 0, var_r22 = 0; i < 4; i++) {
        temp_r31 = &lbl_1_bss_200[i];
        temp_r31->unk28 = i;
        temp_r31->unk2C = i;
        temp_r31->unk30 = GWPlayerCfg[i].pad_idx;
        if (GWPlayerCfg[temp_r31->unk28].group == 0) {
            lbl_1_bss_5AC = temp_r31->unk28;
            lbl_1_bss_5BE = temp_r31->unk00 = CharModelCreate(lbl_1_data_0[GWPlayerCfg[i].character], 2);
            Hu3DModelLayerSet(temp_r31->unk00, 0);
            CharModelLayerSetAll(2);
            fn_1_4A0();
            temp_r31->unk68 = temp_r31->unk70 = temp_r31->unk6C = 0.0f;
            temp_r31->unk9C = temp_r31->unk6C;
            temp_r31->unk54 = temp_r31->unk58 = temp_r31->unk5C = 0.0f;
            temp_r31->unk8C = 50.0f;
            temp_r31->unk90 = 0.0f;
            temp_r31->unk94 = 1.0f;
            Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
            Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk68, temp_r31->unk6C, temp_r31->unk70);
            Hu3DModelShadowSet(temp_r31->unk00);
            for (j = 0; j < 11; j++) {
                var_r23 = lbl_1_data_20[j];
                if ((var_r23 & 0xFFFF0000) == DATADIR_M419) {
                    var_r23 += GWPlayerCfg[i].character;
                }
                temp_r31->unk06[j] = CharModelMotionCreate(lbl_1_data_0[GWPlayerCfg[i].character], var_r23);
            }
            CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[i].character], temp_r31->unk06[0]);
            Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_LOOP);
            CharModelMotionDataClose(lbl_1_data_0[GWPlayerCfg[i].character]);
            var_r25 = HuPrcChildCreate(fn_1_9AF0, 0x2000, 0x3000, 0, HuPrcCurrentGet());
            var_r25->user_data = temp_r31;
            lbl_1_bss_180[i] = var_r25;
        }
        else {
            temp_r31->unk02 = CharModelCreate(lbl_1_data_0[GWPlayerCfg[i].character], 2);
            Hu3DModelLayerSet(temp_r31->unk00, 1);
            CharModelLayerSetAll(2);
            temp_r31->unk80 = lbl_1_data_5C[GWPlayerCfg[i].character].x;
            temp_r31->unk84 = lbl_1_data_5C[GWPlayerCfg[i].character].y;
            temp_r31->unk88 = lbl_1_data_5C[GWPlayerCfg[i].character].z;
            Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk80, temp_r31->unk84, temp_r31->unk88);
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 31), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r31->unk00 = Hu3DModelCreate(var_r29);
            Hu3DModelLayerSet(temp_r31->unk00, 1);
            temp_r31->unk68 = temp_r31->unk70 = 0.0f;
            temp_r31->unk6C = 120.0f * var_r22;
            var_r22++;
            if (temp_r31->unk6C > 360.0f) {
                temp_r31->unk6C -= 360.0f;
            }
            Hu3DModelAttrSet(temp_r31->unk00, 1);
            temp_f31 = 1000.0f;
            temp_r31->unk54 = temp_f31 * sind(temp_r31->unk6C);
            temp_r31->unk58 = 0.0f;
            temp_r31->unk5C = temp_f31 * cosd(temp_r31->unk6C);
            temp_r31->unk6C += 180.0f;
            if (temp_r31->unk6C > 360.0f) {
                temp_r31->unk6C -= 360.0f;
            }
            temp_r31->unk9C = temp_r31->unk6C;
            temp_r31->unk8C = 200.0f;
            temp_r31->unk90 = 2.25f;
            temp_r31->unk94 = 1.0f;
            temp_r31->unk98 = 0.66f;
            Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
            Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk68, temp_r31->unk6C, temp_r31->unk70);
            Hu3DModelShadowSet(temp_r31->unk00);
            Hu3DModelHookSet(temp_r31->unk00, "itemhook_c", temp_r31->unk02);
            for (j = 0; j < 4; j++) {
                temp_r31->unk1C[j] = CharModelMotionCreate(lbl_1_data_0[GWPlayerCfg[i].character], lbl_1_data_4C[j]);
            }
            CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[i].character], temp_r31->unk1C[0]);
            CharModelMotionTimeSet(lbl_1_data_0[GWPlayerCfg[i].character], 60.0f);
            CharModelVoiceEnableSet(lbl_1_data_0[GWPlayerCfg[i].character], temp_r31->unk1C[3], 0);
            for (j = 0; j < 8; j++) {
                var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 32 + j), MEMORY_DEFAULT_NUM, HEAP_DATA);
                temp_r31->unk06[j] = Hu3DJointMotion(temp_r31->unk00, var_r29);
            }
            Hu3DMotionSet(temp_r31->unk00, temp_r31->unk06[1]);
            Hu3DMotionShiftSpeedSet(temp_r31->unk00, 1.0f);
            Hu3DMotionSpeedSet(temp_r31->unk00, 1.0f);
            Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_LOOP);
            var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M419, 40), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r31->unk04 = Hu3DModelCreate(var_r29);
            Hu3DModelLayerSet(temp_r31->unk04, 1);
            Hu3DModelAttrSet(temp_r31->unk04, 1);
            Hu3DModelAttrSet(temp_r31->unk04, HU3D_MOTATTR_PAUSE);
            CharModelMotionDataClose(lbl_1_data_0[GWPlayerCfg[i].character]);
            var_r25 = HuPrcChildCreate(fn_1_DF98, 0x2000, 0x3000, 0, HuPrcCurrentGet());
            var_r25->user_data = temp_r31;
            lbl_1_bss_180[i] = var_r25;
        }
    }
    var_r21 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 2), MEMORY_DEFAULT_NUM));
    var_r30 = Hu3DParticleCreate(var_r21, 50);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r30, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r30, 3);
    Hu3DParticleColSet(var_r30, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r30, 0.0f);
    Hu3DParticleHookSet(var_r30, fn_1_2254);
    var_r21 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 2), MEMORY_DEFAULT_NUM));
    var_r30 = Hu3DParticleCreate(var_r21, 50);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r30, 1.0f, 1.0f, 1.0f);
    Hu3DModelLayerSet(var_r30, 3);
    Hu3DParticleColSet(var_r30, 0xFF, 0xFF, 0xFF);
    Hu3DParticleScaleSet(var_r30, 0.0f);
    Hu3DParticleHookSet(var_r30, fn_1_2744);
    HuDataDirClose(DATADIR_EFFECT);
    lbl_1_bss_580 = 0;
    lbl_1_bss_584[0] = frandmod(5) * 60 + 600;
    lbl_1_bss_584[1] = frandmod(5) * 60 + 1380;
    lbl_1_bss_584[2] = 2760;
    Hu3DModelLayerSet(Hu3DHookFuncCreate(fn_1_848), 1);
    HuPrcChildCreate(fn_1_104A0, 0x1000, 0x1000, 0, HuPrcCurrentGet());
}

float fn_1_1F84(float arg0, float arg1)
{
    float var_f31;
    float var_f30;

    if (arg0 > 600.0f - arg1) {
        var_f31 = 600.0f + 200.0f * ((800.0f - (arg0 + arg1)) / 200.0f);
    }
    else if (arg0 < -(600.0f - arg1)) {
        var_f31 = 600.0f + 200.0f * ((800.0f - ABS_INV(arg0 - arg1)) / 200.0f);
    }
    else {
        var_f31 = 800.0f;
    }
    return var_f31;
}

float fn_1_20AC(float arg0, float arg1)
{
    return fn_1_1F84(arg0, arg1);
}

float fn_1_21D4(float arg0)
{
    while (arg0 >= 360.0f || arg0 < 0.0f) {
        if (arg0 >= 360.0f) {
            arg0 -= 360.0f;
        }
        if (arg0 < 0.0f) {
            arg0 += 360.0f;
        }
    }
    return arg0;
}

void fn_1_2254(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    StructBss200 *temp_r28;
    float var_f31;
    float temp_f29;
    float var_f30;
    s32 var_r27;
    s16 i;
    s16 j;
    s16 k;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (k = 0; k < particle->unk_30; k++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < 4; i++) {
        temp_r28 = &lbl_1_bss_200[i];
        if (temp_r28->unk38 & 1) {
            for (j = 0, var_f30 = 0.0f; j < 16; j++, var_f30 += 22.5f) {
                for (k = 0; k < particle->unk_30; k++, var_r31++) {
                    if (var_r31->unk14.x == 0.0f) {
                        break;
                    }
                }
                if (k == particle->unk_30) {
                    break;
                }
                var_f31 = var_f30;
                temp_f29 = 125.0f + 70.0f * frandf();
                var_r31->unk34.x = temp_r28->unk74 + temp_f29 * sind(var_f31);
                var_r31->unk34.y = temp_r28->unk78 + 50.0f * frandf();
                var_r31->unk34.z = temp_r28->unk7C + temp_f29 * cosd(var_f31);
                var_r31->unk08.x = 5.0 * sind(var_f31);
                var_r31->unk08.y = 9.0f + 2.0f * frandf();
                var_r31->unk08.z = 5.0 * cosd(var_f31);
                var_r31->unk14.x = 30.0f;
                var_r31->unk2C = 80.0f + 20.0f * frandf();
                var_r31->unk14.y = 15.0f;
                var_r31->unk40.a = 0xC8;
                var_r31->unk14.z = 17.0f;
            }
            temp_r28->unk38 &= ~1;
        }
    }
    var_r31 = particle->unk_48;
    for (k = 0; k < particle->unk_30; k++, var_r31++) {
        if (var_r31->unk14.x != 0.0f) {
            VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
            var_r31->unk08.x *= 0.95f;
            var_r31->unk08.z *= 0.95f;
            if (var_r31->unk08.y > 0.1f) {
                var_r31->unk08.y -= 0.2f;
            }
            if (var_r31->unk08.y < 0.0f) {
                var_r31->unk08.y = 0.0f;
            }
            var_r31->unk2C += var_r31->unk14.y;
            if (var_r31->unk14.y > 2.0f) {
                var_r31->unk14.y -= 1.5f;
            }
            var_r27 = var_r31->unk40.a;
            var_r27 -= var_r31->unk14.z;
            if (var_r31->unk14.z > 3.0f) {
                var_r31->unk14.z -= 1.0f;
            }
            if (var_r27 < 0) {
                var_r27 = 0;
                var_r31->unk14.x = 0.0f;
            }
            var_r31->unk40.a = var_r27;
            if (var_r31->unk14.x == 0.0f) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}

void fn_1_2744(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    StructBss200 *temp_r28;
    float temp_f31;
    float temp_f30;
    s32 var_r27;
    s16 i;
    s16 j;
    s16 k;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (k = 0; k < particle->unk_30; k++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
            var_r31->unk20 = -1.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < 4; i++) {
        temp_r28 = &lbl_1_bss_200[i];
        if (temp_r28->unk38 & 2) {
            for (j = 0; j < 10; j++) {
                for (k = 0; k < particle->unk_30; k++, var_r31++) {
                    if (var_r31->unk14.x == 0.0f) {
                        break;
                    }
                }
                if (k == particle->unk_30) {
                    break;
                }
                temp_f31 = 400.0f * frandf() - 200.0f;
                temp_f30 = 400.0f * frandf() - 200.0f;
                var_r31->unk34.x = temp_r28->unk74 + temp_f31;
                var_r31->unk34.y = temp_r28->unk78 + 50.0f;
                var_r31->unk34.z = temp_r28->unk7C + temp_f30;
                var_r31->unk08.x = 0.0f;
                var_r31->unk08.y = 7.0f;
                var_r31->unk08.z = 0.0f;
                var_r31->unk20 = frandmod(10);
                var_r31->unk24 = 0.0f;
                var_r31->unk14.x = 100.0f;
                var_r31->unk2C = 0.0f;
                var_r31->unk14.y = 7.0f;
                var_r31->unk40.a = 0xFF;
                var_r31->unk14.z = 10.0f;
            }
            temp_r28->unk38 &= ~2;
        }
    }
    var_r31 = particle->unk_48;
    for (k = 0; k < particle->unk_30; k++, var_r31++) {
        if (var_r31->unk20 > 0.0f) {
            var_r31->unk20 -= 1.0f;
        }
        if (var_r31->unk20 == 0.0f) {
            var_r31->unk24 = 1.0f;
            var_r31->unk2C = 100.0f + 100.0f * frandf();
            var_r31->unk20 = -1.0f;
        }
        if (var_r31->unk14.x != 0.0f && var_r31->unk24 != 0.0f) {
            VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
            if (var_r31->unk08.y > 1.0f) {
                var_r31->unk08.y -= 0.3f;
            }
            var_r31->unk2C += var_r31->unk14.y;
            if (var_r31->unk14.y > 2.0f) {
                var_r31->unk14.y -= 0.4f;
            }
            var_r27 = var_r31->unk40.a;
            var_r27 -= var_r31->unk14.z;
            if (var_r31->unk14.z > 3.0f) {
                var_r31->unk14.z -= 1.0f;
            }
            if (var_r27 < 0) {
                var_r27 = 0;
                var_r31->unk14.x = 0.0f;
            }
            var_r31->unk40.a = var_r27;
            if (var_r31->unk14.x == 0.0f) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}

s32 fn_1_2BDC(StructBss190 *arg0)
{
    StructBss200 *temp_r31;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f29;
    float var_f28;
    s32 var_r28;
    s32 i;

    for (i = 0, var_f29 = 10000.0f, var_r28 = -1; i < 4; i++) {
        temp_r31 = &lbl_1_bss_200[i];
        HuSetVecF(&sp24, arg0->unk14, 0.0, arg0->unk1C);
        HuSetVecF(&sp18, temp_r31->unk54, 0.0, temp_r31->unk5C);
        HuSubVecF(&spC, &sp24, &sp18);
        if ((var_f28 = VECMagXYZ(&spC)) < 50.0f + temp_r31->unk8C && var_f28 < var_f29) {
            var_f29 = var_f28;
            var_r28 = i;
        }
    }
    return var_r28;
}

void fn_1_2DFC(StructBss190 *arg0)
{
    float temp_f31;
    float var_f26;
    float var_f25;

    temp_f31 = 50.0f;
    var_f26 = fn_1_1F84(arg0->unk1C, 50.0f);
    var_f25 = fn_1_1F84(arg0->unk14, 50.0f);
    if (arg0->unk14 > var_f26 - temp_f31) {
        arg0->unk14 = var_f26 - temp_f31;
    }
    if (arg0->unk14 < -(var_f26 - temp_f31)) {
        arg0->unk14 = -(var_f26 - temp_f31);
    }
    if (arg0->unk1C > var_f25 - temp_f31) {
        arg0->unk1C = var_f25 - temp_f31;
    }
    if (arg0->unk1C < -(var_f25 - temp_f31)) {
        arg0->unk1C = -(var_f25 - temp_f31);
    }
    if (arg0->unk1C > var_f25 - temp_f31 || arg0->unk1C < -(var_f25 - temp_f31)) {
        arg0->unk14 += arg0->unk10 * sind(arg0->unk0C) * 0.8f;
    }
    if (arg0->unk14 > var_f26 - temp_f31 || arg0->unk14 < -(var_f26 - temp_f31)) {
        arg0->unk1C += arg0->unk10 * cosd(arg0->unk0C) * 0.8f;
    }
    if (arg0->unk14 > var_f26 - temp_f31) {
        arg0->unk14 = var_f26 - temp_f31;
    }
    if (arg0->unk14 < -(var_f26 - temp_f31)) {
        arg0->unk14 = -(var_f26 - temp_f31);
    }
    if (arg0->unk1C > var_f25 - temp_f31) {
        arg0->unk1C = var_f25 - temp_f31;
    }
    if (arg0->unk1C < -(var_f25 - temp_f31)) {
        arg0->unk1C = -(var_f25 - temp_f31);
    }
}

void fn_1_32F8(void)
{
    StructBss200 *temp_r31;
    float var_f31;
    s32 var_r29;
    s32 i;

    var_r29 = (s32)HuPrcCurrentGet()->user_data;
    temp_r31 = &lbl_1_bss_200[var_r29];
    for (i = 0, var_f31 = 1.0f; i < 30; i++, var_f31 -= 0.033333335f) {
        Hu3DModelAmbSet(temp_r31->unk00, 1.0f, var_f31, var_f31);
        HuPrcVSleep();
    }
    Hu3DModelAmbSet(temp_r31->unk00, 1.0f, 0.0f, 0.0f);
    while (temp_r31->unk48 > 30) {
        HuPrcVSleep();
    }
    for (i = 0, var_f31 = 0.0f; i < 30; i++, var_f31 += 0.033333335f) {
        Hu3DModelAmbSet(temp_r31->unk00, 1.0f, var_f31, var_f31);
        HuPrcVSleep();
    }
    Hu3DModelAmbSet(temp_r31->unk00, 1.0f, 1.0f, 1.0f);
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_344C(void)
{
    StructBss190 *temp_r31;
    StructBss200 *temp_r30;
    Vec spAC;
    Vec spA0;
    Vec sp94;
    float sp6C;
    float sp68;
    float sp64;
    float sp60;
    float sp5C;
    float sp58;
    float sp54;
    float sp50;
    float sp4C;
    float sp48;
    float sp44;
    float var_f24;
    float var_f23;
    s32 var_r24;
    s32 var_r23;
    s16 var_r22;
    s32 var_r25;
    s32 var_r28;
    s32 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    HuPrcSleep(25);
    var_r23 = 0;
    temp_r31->unk0A = 0;
    var_r28 = 0;
    var_f24 = temp_r31->unk18;
    var_f23 = 15.0f;
    sp58 = 0.9f;
    while (var_f24 > 50.0f) {
        var_f23 -= sp58;
        var_f24 += var_f23;
        var_r28++;
    }
    if (temp_r31->unk08 == 0) {
        Hu3DMotionSet(temp_r31->unk00, temp_r31->unk04);
        Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_LOOP);
        Hu3DModelTPLvlSet(temp_r31->unk00, 1.0f);
    }
    else {
        Hu3DModelAttrReset(temp_r31->unk02, 1);
    }
    Hu3DModelAttrReset(temp_r31->unk00, 1);
    temp_r31->unk0C = atan2d(temp_r31->unk24 - temp_r31->unk14, temp_r31->unk28 - temp_r31->unk1C);
    HuSetVecF(&spAC, temp_r31->unk24, 0.0, temp_r31->unk28);
    HuSetVecF(&spA0, temp_r31->unk14, 0.0, temp_r31->unk1C);
    HuSubVecF(&sp94, &spAC, &spA0);
    temp_r31->unk10 = VECMagXYZ(&sp94) / var_r28;
    var_f24 = temp_r31->unk18;
    var_f23 = 15.0f;
    sp58 = 0.9f;
    while (var_f24 > 50.0f) {
        sp68 = temp_r31->unk14;
        sp64 = temp_r31->unk18;
        sp60 = temp_r31->unk1C;
        temp_r31->unk14 += temp_r31->unk10 * sind(temp_r31->unk0C);
        temp_r31->unk18 = var_f24;
        temp_r31->unk1C += temp_r31->unk10 * cosd(temp_r31->unk0C);
        if ((var_r25 = fn_1_2BDC(temp_r31)) != -1) {
            temp_r30 = &lbl_1_bss_200[var_r25];
            if (GWPlayerCfg[temp_r30->unk28].group == 0) {
                sp5C = 150.0f;
            }
            else {
                sp5C = 400.0f;
            }
            if (temp_r31->unk18 < sp5C) {
                if (temp_r31->unk18 < sp5C && temp_r31->unk18 > sp5C - 50.0f) {
                    var_f23 = 15.0f;
                    sp58 = 0.9f;
                }
                else {
                    sp6C = atan2d(temp_r31->unk14 - temp_r30->unk54, temp_r31->unk1C - temp_r30->unk5C);
                    temp_r31->unk0C = fn_1_21D4(180.0f + temp_r31->unk0C);
                    temp_r31->unk0C = sp6C - (temp_r31->unk0C - sp6C);
                }
                temp_r31->unk14 = sp68;
                temp_r31->unk18 = sp64;
                temp_r31->unk1C = sp60;
            }
        }
        fn_1_2DFC(temp_r31);
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk14, temp_r31->unk18, temp_r31->unk1C);
        if (temp_r31->unk08 != 0) {
            temp_r31->unk20 += 10.0f;
            Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk14, temp_r31->unk18, temp_r31->unk1C);
            Hu3DModelRotSet(temp_r31->unk02, 0.0f, 0.0f, temp_r31->unk20);
        }
        Hu3DModelRotSet(temp_r31->unk00, 0.0f, 0.0f, temp_r31->unk20);
        if (lbl_1_bss_5B4 >= 4) {
            var_r23 = 1;
            goto fn_1_344C_label;
        }
        HuPrcVSleep();
        var_f23 -= sp58;
        var_f24 += var_f23;
    }
    Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk14, 50.0f, temp_r31->unk1C);
    if (temp_r31->unk08 != 0) {
        Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk14, 50.0f, temp_r31->unk1C);
    }
    if (temp_r31->unk08 == 0) {
        Hu3DModelAttrSet(temp_r31->unk00, 1);
        Hu3DModelAttrReset(temp_r31->unk02, 1);
        Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk14, 0.0f, temp_r31->unk1C);
        Hu3DModelRotSet(temp_r31->unk02, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSet(temp_r31->unk02, temp_r31->unk06);
        Hu3DModelAttrReset(temp_r31->unk02, HU3D_MOTATTR_LOOP);
        Hu3DModelTPLvlSet(temp_r31->unk02, 1.0f);
    }
    for (var_r28 = 300, var_r24 = 0; var_r28 != 0; var_r28--) {
        if (temp_r31->unk08 != 0 && 0.0f != temp_r31->unk20) {
            temp_r31->unk20 += 10.0f;
            if (temp_r31->unk20 > 360.0f) {
                temp_r31->unk20 = 0.0f;
            }
            Hu3DModelRotSet(temp_r31->unk00, 0.0f, 0.0f, temp_r31->unk20);
            Hu3DModelRotSet(temp_r31->unk02, 0.0f, 0.0f, temp_r31->unk20);
        }
        for (i = 0, sp50 = 10000.0f; i < 4; i++) {
            temp_r30 = &lbl_1_bss_200[i];
            HuSetVecF(&spAC, temp_r31->unk14, 0.0, temp_r31->unk1C);
            HuSetVecF(&spA0, temp_r30->unk54, 0.0, temp_r30->unk5C);
            HuSubVecF(&sp94, &spAC, &spA0);
            if ((sp54 = VECMagXYZ(&sp94)) < 50.0f + temp_r30->unk8C && sp54 < sp50) {
                sp50 = sp54;
                var_r25 = i;
            }
        }
        if (sp50 < 10000.0f) {
            temp_r30 = &lbl_1_bss_200[var_r25];
            temp_r31->unk0A = 1;
            if (temp_r31->unk08 != 0) {
                temp_r30->unk3C = 1;
                temp_r30->unk48 = 300;
                if (GWPlayerCfg[temp_r30->unk28].group == 0) {
                    temp_r30->unk94 = 3.0f;
                    lbl_1_bss_5BC = 1;
                    HuAudFXPlay(0x5E6);
                }
                else {
                    temp_r30->unk90 = 6.75f;
                    temp_r30->unk98 = 0.99f;
                    HuAudFXPlay(0x5E2);
                }
            }
            else if (temp_r30->unk24 == 0) {
                temp_r30->unk34 = 4;
                HuAudPlayerVoicePlay(temp_r30->unk28, 0x128);
                HuAudFXPlay(0x5E9);
            }
            break;
        }
        if (var_r28 < 60) {
            var_r22 = temp_r31->unk00;
            if (temp_r31->unk08 == 0) {
                var_r22 = temp_r31->unk02;
            }
            if (var_r24 & 1) {
                Hu3DModelAttrReset(var_r22, 1);
            }
            else {
                Hu3DModelAttrSet(var_r22, 1);
            }
            var_r24++;
        }
        HuPrcVSleep();
        if (lbl_1_bss_5B4 >= 4) {
            var_r23 = 1;
            break;
        }
    }
fn_1_344C_label:
    if (var_r23 != 0) {
        for (i = 0, sp4C = 1.0f; i < 30; i++) {
            sp4C -= 0.033333335f;
            Hu3DModelScaleSet(temp_r31->unk00, sp4C, sp4C, sp4C);
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(temp_r31->unk00, 1);
        Hu3DModelAttrSet(temp_r31->unk02, 1);
    }
    else {
        if (temp_r31->unk08 == 0) {
            temp_r30 = &lbl_1_bss_200[var_r25];
            sp6C = atan2d(temp_r31->unk14 - temp_r30->unk54, temp_r31->unk1C - temp_r30->unk5C);
            sp44 = 1.0f;
            temp_r31->unk20 = 0.0f;
            for (i = 0, sp48 = 0.0f; i < 10; i++, sp48 += 9.0f, sp44 -= 0.1f) {
                temp_r31->unk14 += 2.0 * sind(sp6C);
                temp_r31->unk18 += 10.0f;
                temp_r31->unk1C += 2.0 * cosd(sp6C);
                Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk14, temp_r31->unk18, temp_r31->unk1C);
                temp_r31->unk20 += 10.0f;
                Hu3DModelRotSet(temp_r31->unk02, 0.0f, 0.0f, temp_r31->unk20);
                Hu3DModelTPLvlSet(temp_r31->unk02, sp44);
                HuPrcVSleep();
            }
        }
        Hu3DModelAttrSet(temp_r31->unk00, 1);
        if (temp_r31->unk08 != 0) {
            Hu3DModelAttrSet(temp_r31->unk02, 1);
        }
        temp_r31->unk20 = 0.0f;
        HuPrcCurrentGet()->user_data = NULL;
        HuPrcKill(HuPrcCurrentGet());
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_47E4(void)
{
    StructBss1E8 *var_r31;
    StructBss190 *var_r30;
    ModelData *temp_r29;
    Process *temp_r3;
    s32 var_r27;

    var_r31 = &lbl_1_bss_1E8[0];
    while (lbl_1_bss_5B4 != 3) {
        HuPrcVSleep();
    }
    while (TRUE) {
        while (lbl_1_bss_5BA != 0) {
            HuPrcVSleep();
        }
        if (lbl_1_bss_5B4 >= 4) {
            break;
        }
        var_r30 = &lbl_1_bss_190[0];
        if (lbl_1_bss_5B0 > lbl_1_bss_584[lbl_1_bss_580]) {
            lbl_1_bss_580++;
            var_r30 = &lbl_1_bss_190[1];
            Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        }
        else {
            Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[3], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        }
        HuPrcVSleep();
        var_r27 = Hu3DMotionMaxTimeGet(var_r31->unk00);
        while (var_r27 != 0) {
            HuPrcVSleep();
            var_r27--;
        }
        HuAudFXPlay(0x5E4);
        temp_r3 = HuPrcChildCreate(fn_1_344C, 0x2010, 0x3000, 0, HuPrcCurrentGet());
        temp_r3->user_data = var_r30;
        temp_r29 = &Hu3DData[lbl_1_bss_1E8[0].unk00];
        var_r30->unk14 = temp_r29->pos.x + 640.0f;
        var_r30->unk18 = temp_r29->pos.y + 620.0f;
        var_r30->unk1C = temp_r29->pos.y - 200.0f;
        var_r30->unk20 = 0.0f;
        var_r30->unk24 = 1000.0f * frandf() - 500.0f;
        var_r30->unk28 = 1000.0f * frandf() - 500.0f;
        while (!Hu3DMotionEndCheck(var_r31->unk00)) {
            HuPrcVSleep();
        }
        Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        while (temp_r3->user_data) {
            HuPrcVSleep();
        }
        lbl_1_bss_5BA = 1;
        if (var_r30->unk0A != 0) {
            HuAudFXPlay(0x5E8);
            Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[2], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
            HuPrcSleep(6);
            while (!Hu3DMotionEndCheck(var_r31->unk00)) {
                HuPrcVSleep();
            }
            Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        }
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_4B20(void)
{
    StructBss1E8 *var_r31;
    StructBss190 *var_r30;
    Process *temp_r3;
    ModelData *temp_r29;
    s32 var_r27;

    var_r31 = &lbl_1_bss_1E8[1];
    while (lbl_1_bss_5B4 != 3) {
        HuPrcVSleep();
    }
    while (TRUE) {
        while (lbl_1_bss_5BA == 0) {
            HuPrcVSleep();
        }
        if (lbl_1_bss_5B4 >= 4) {
            break;
        }
        var_r30 = lbl_1_bss_190;
        if (lbl_1_bss_5B0 > lbl_1_bss_584[lbl_1_bss_580]) {
            lbl_1_bss_580++;
            var_r30 = &lbl_1_bss_190[1];
            Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        }
        else {
            Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[3], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        }
        HuPrcVSleep();
        var_r27 = Hu3DMotionMaxTimeGet(var_r31->unk00);
        while (var_r27 != 0) {
            HuPrcVSleep();
            var_r27--;
        }
        HuAudFXPlay(0x5E4);
        temp_r3 = HuPrcChildCreate(fn_1_344C, 0x2010, 0x3000, 0, HuPrcCurrentGet());
        temp_r3->user_data = var_r30;
        temp_r29 = &Hu3DData[lbl_1_bss_1E8->unk00];
        var_r30->unk14 = -(temp_r29->pos.x + 640.0f);
        var_r30->unk18 = temp_r29->pos.y + 620.0f;
        var_r30->unk1C = temp_r29->pos.y - 200.0f;
        var_r30->unk24 = 1000.0f * frandf() - 500.0f;
        var_r30->unk28 = 1000.0f * frandf() - 500.0f;
        while (!Hu3DMotionEndCheck(var_r31->unk00)) {
            HuPrcVSleep();
        }
        Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        while (temp_r3->user_data) {
            HuPrcVSleep();
        }
        lbl_1_bss_5BA = 0;
        if (var_r30->unk0A != 0) {
            HuAudFXPlay(0x5E8);
            Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[2], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
            HuPrcSleep(6);
            while (!Hu3DMotionEndCheck(var_r31->unk00)) {
                HuPrcVSleep();
            }
            Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        }
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

s8 fn_1_4E54(s32 arg0, s32 arg1)
{
    StructBss200 *temp_r31;
    s8 var_r30;

    temp_r31 = &lbl_1_bss_200[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        (arg1 != 0) ? (var_r30 = HuPadStkY[temp_r31->unk30]) : (var_r30 = HuPadStkX[temp_r31->unk30]);
    }
    else {
        (arg1 != 0) ? (var_r30 = temp_r31->unkA1) : (var_r30 = temp_r31->unkA0);
    }
    return var_r30;
}

u8 fn_1_4F0C(s32 arg0, s32 arg1)
{
    StructBss200 *temp_r31;
    s8 var_r30;

    temp_r31 = &lbl_1_bss_200[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        (arg1 != 0) ? (var_r30 = HuPadTrigR[temp_r31->unk30]) : (var_r30 = HuPadTrigL[temp_r31->unk30]);
    }
    else {
        (arg1 != 0) ? (var_r30 = temp_r31->unkA2) : (var_r30 = temp_r31->unkA3);
    }
    return var_r30;
}

u16 fn_1_4FCC(s32 arg0)
{
    StructBss200 *temp_r31;
    u16 var_r30;

    temp_r31 = &lbl_1_bss_200[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        var_r30 = HuPadBtnDown[temp_r31->unk30];
    }
    else {
        var_r30 = temp_r31->unkA6;
    }
    return var_r30;
}

u16 fn_1_5038(s32 arg0)
{
    StructBss200 *temp_r31;
    u16 var_r30;

    temp_r31 = &lbl_1_bss_200[arg0];
    if (GWPlayerCfg[arg0].iscom == 0) {
        var_r30 = HuPadBtn[temp_r31->unk30];
    }
    else {
        var_r30 = temp_r31->unkA4;
    }
    return var_r30;
}

s32 fn_1_50A4(StructBss200 *arg0, float arg1, s32 arg2)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    StructBss200 *temp_r30;
    s32 var_r28;
    float var_f27;
    float var_f28;
    s32 i;

    var_r28 = -1;
    for (i = 0, var_f28 = 10000.0f; i < 4; i++) {
        if (i != arg0->unk28 && (arg2 == 0 || i != lbl_1_bss_5AC)) {
            temp_r30 = &lbl_1_bss_200[i];
            HuSetVecF(&sp2C, arg0->unk54, arg0->unk58, arg0->unk5C);
            HuSetVecF(&sp20, temp_r30->unk54, temp_r30->unk58, temp_r30->unk5C);
            HuSubVecF(&sp14, &sp2C, &sp20);
            if ((var_f27 = VECMagXYZ(&sp14)) < arg0->unk8C + temp_r30->unk8C + arg1 && var_f27 < var_f28) {
                var_f28 = var_f27;
                var_r28 = i;
            }
        }
    }
    return var_r28;
}

s32 fn_1_52E8(StructBss200 *arg0)
{
    float var_f25;
    float var_f24;
    s32 var_r28;

    var_f25 = fn_1_1F84(arg0->unk5C, arg0->unk8C);
    var_f24 = fn_1_1F84(arg0->unk54, arg0->unk8C);
    if (arg0->unk54 > var_f25 - arg0->unk8C) {
        arg0->unk54 = var_f25 - arg0->unk8C;
    }
    if (arg0->unk54 < -(var_f25 - arg0->unk8C)) {
        arg0->unk54 = -(var_f25 - arg0->unk8C);
    }
    if (arg0->unk5C > var_f24 - arg0->unk8C) {
        arg0->unk5C = var_f24 - arg0->unk8C;
    }
    if (arg0->unk5C < -(var_f24 - arg0->unk8C)) {
        arg0->unk5C = -(var_f24 - arg0->unk8C);
    }
    if ((var_r28 = fn_1_50A4(arg0, 0.0f, 0)) != -1) {
        arg0->unk54 = arg0->unk60;
        arg0->unk5C = arg0->unk64;
    }
    return var_r28;
}

float fn_1_5858(float arg0, float arg1, float arg2)
{
    float var_f31;
    float var_f30;

    var_f31 = fmod(arg1 - arg0, 360.0);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg0 + var_f31 * arg2, 360.0);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

float fn_1_595C(float arg0, float arg1, StructBss200 *arg2)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;

    HuSetVecF(&sp2C, arg0, 0.0, arg1);
    HuSetVecF(&sp20, arg2->unk54, 0.0, arg2->unk5C);
    HuSubVecF(&sp14, &sp2C, &sp20);
    return VECMagXZ(&sp14);
}

float fn_1_5AD8(float arg0, float arg1)
{
    float var_f31;

    if (arg0 > arg1) {
        var_f31 = fn_1_21D4(arg0 - arg1);
        if (var_f31 < 180.0f) {
            var_f31 = fn_1_21D4(arg1 + var_f31 + 180.0f);
        }
        else {
            var_f31 = fn_1_21D4(arg1 - var_f31);
        }
    }
    else {
        var_f31 = fn_1_21D4(arg1 - arg0);
        if (var_f31 < 180.0f) {
            var_f31 = fn_1_21D4(arg0 + var_f31 + 180.0f);
        }
        else {
            var_f31 = fn_1_21D4(arg0 - var_f31);
        }
    }
    return var_f31;
}

s32 fn_1_5F34(StructBss200 *arg0, float arg1)
{
    s32 var_r31;
    float var_f25;
    float var_f24;

    var_f25 = fn_1_1F84(arg0->unk5C, arg0->unk8C);
    var_f24 = fn_1_1F84(arg0->unk54, arg0->unk8C);
    var_r31 = 0;
    if (arg0->unk54 > var_f25 - arg0->unk8C - arg1 || arg0->unk54 < -(var_f25 - arg0->unk8C - arg1) || arg0->unk5C > var_f24 - arg0->unk8C - arg1
        || arg0->unk5C < -(var_f24 - arg0->unk8C - arg1)) {
        var_r31 = 1;
    }
    return var_r31;
}

void fn_1_628C(StructBss200 *arg0)
{
    Vec spC;

    HuSetVecF(&spC, fn_1_4E54(arg0->unk28, 0) / 4.0f, 0.0, -fn_1_4E54(arg0->unk28, 1) / 4.0f);
    arg0->unk90 = VECMagXYZ(&spC);
    if (arg0->unk90 >= 0.5f) {
        if (arg0->unk90 >= 10.0f) {
            spC.x /= arg0->unk90;
            spC.z /= arg0->unk90;
            arg0->unk90 = 10.0f;
            spC.x = 10.0f * spC.x;
            spC.z = 10.0f * spC.z;
        }
        arg0->unk54 += spC.x * arg0->unk94;
        arg0->unk5C += spC.z * arg0->unk94;
    }
}

void fn_1_65C0(Vec *arg0, StructBss200 **arg1)
{
    float temp_f31;
    StructBss200 *temp_r31;
    StructBss200 *temp_r30;
    s32 var_r28;
    s32 i;

    for (i = 0; i < 3; i++) {
        temp_r31 = arg1[i];
        (i >= 2) ? (var_r28 = 0) : (var_r28 = i + 1);
        temp_r30 = arg1[var_r28];
        temp_f31 = ABS_INV(temp_r31->unk54 - temp_r30->unk54) / 2.0f;
        if (temp_r31->unk54 > temp_r30->unk54) {
            arg0[i].x = temp_r31->unk54 - temp_f31;
        }
        else {
            arg0[i].x = temp_r30->unk54 - temp_f31;
        }
        temp_r31 = arg1[i];
        (i >= 2) ? (var_r28 = 0) : (var_r28 = i + 1);
        temp_r30 = arg1[var_r28];
        temp_f31 = ABS_INV(temp_r31->unk5C - temp_r30->unk5C) / 2.0f;
        if (temp_r31->unk5C > temp_r30->unk5C) {
            arg0[i].z = temp_r31->unk5C - temp_f31;
        }
        else {
            arg0[i].z = temp_r30->unk5C - temp_f31;
        }
    }
}

s32 fn_1_67A0(float arg0, float arg1, StructBss200 *arg2, StructBss200 **arg3)
{
    StructBss200 *var_r31;
    StructBss200 sp5C;
    float var_f29;
    s32 var_r27;
    s32 i;

    var_r31 = &sp5C;
    var_r31->unk28 = arg2->unk28;
    var_r31->unk54 = arg2->unk54;
    var_r31->unk58 = arg2->unk58;
    var_r31->unk5C = arg2->unk5C;
    var_r31->unk8C = arg2->unk8C;
    var_r31->unk90 = arg2->unk90;
    var_r31->unk94 = arg2->unk94;
    var_f29 = fn_1_21D4(atan2d(arg0 - arg2->unk54, arg1 - arg2->unk5C));
    var_r27 = 1;
    while (fn_1_595C(arg0, arg1, var_r31) >= 10.0f) {
        var_r31->unk54 += 10.0 * sind(var_f29);
        var_r31->unk5C += 10.0 * cosd(var_f29);
        for (i = 0; i < 3; i++) {
            if (fn_1_595C(arg3[i]->unk54, arg3[i]->unk5C, var_r31) < var_r31->unk8C + arg3[i]->unk8C + 10.0f) {
                break;
            }
        }
        if (i < 3) {
            var_r27 = 0;
            break;
        }
    }
    return var_r27;
}

s32 fn_1_6D04(void)
{
    StructBss200 *sp8[3];
    StructBss200 *var_r29;
    s32 var_r30;
    s32 var_r28;
    s32 i;

    for (i = 0, var_r30 = 0; i < 4; i++) {
        if (i == lbl_1_bss_5AC) {
            var_r29 = &lbl_1_bss_200[i];
        }
        else {
            sp8[var_r30++] = &lbl_1_bss_200[i];
        }
    }
    var_r30 = 0;
    for (i = 0; i < 3; i++) {
        if (sp8[i]->unk54 > var_r29->unk54) {
            break;
        }
    }
    if (i < 3) {
        var_r30++;
        for (i = 0; i < 3; i++) {
            if (sp8[i]->unk54 < var_r29->unk54) {
                break;
            }
        }
        if (i < 3) {
            var_r30++;
            for (i = 0; i < 3; i++) {
                if (sp8[i]->unk5C > var_r29->unk5C) {
                    break;
                }
            }
            if (i < 3) {
                var_r30++;
                for (i = 0; i < 3; i++) {
                    if (sp8[i]->unk5C < var_r29->unk5C) {
                        break;
                    }
                }
                if (i < 3) {
                    var_r30++;
                }
            }
        }
    }
    var_r28 = 0;
    if (var_r30 >= 4) {
        var_r28 = 1;
    }
    return var_r28;
}

float fn_1_6E9C(StructBss200 *arg0)
{
    s32 sp88[3];
    s32 sp50[2];
    float sp44;
    float var_f20;
    float sp48[2];
    StructBss200 *sp7C[3];
    s32 var_r29;
    s32 var_r28;
    s32 i;

    for (i = 0, var_r29 = 0; i < 4; i++) {
        if (i != arg0->unk28) {
            sp7C[var_r29++] = &lbl_1_bss_200[i];
        }
    }
    for (i = 0, var_r28 = 0; i < 3; i++) {
        sp44 = fn_1_595C(sp7C[i]->unk54, sp7C[i]->unk5C, arg0);
        if (sp44 < arg0->unk8C + sp7C[i]->unk8C + 100.0f) {
            sp88[i] = 1;
            var_r28++;
        }
        else {
            sp88[i] = -1;
        }
    }
    var_f20 = -1.0f;
    switch (var_r28) {
        case 1:
            for (i = 0; i < 3; i++) {
                if (sp88[i] != 0) {
                    break;
                }
            }
            var_f20 = fn_1_21D4(atan2d(arg0->unk54 - sp7C[i]->unk54, arg0->unk5C - sp7C[i]->unk5C));
            break;
        case 2:
            for (i = 0, var_r29 = 0; i < 3; i++) {
                if (sp88[i] == 0) {
                    sp50[var_r29++] = i;
                }
            }
            for (i = 0; i < 2; i++) {
                sp48[i] = fn_1_21D4(atan2d(arg0->unk54 - sp7C[sp50[i]]->unk54, arg0->unk5C - sp7C[sp50[i]]->unk5C));
            }
            var_f20 = fn_1_5AD8(sp48[0], sp48[1]);
            break;
    }
    if (var_f20 != -1.0f)
        ;
    if (var_f20 != -1.0f) {
        var_f20 = fn_1_21D4(var_f20);
    }
    return var_f20;
}

void fn_1_78B4(StructBss200 *arg0)
{
    StructBss200 *temp_r18;
    StructBss200 *var_r17;
    StructBss200 *sp224[3];
    Vec sp254[3];
    Vec sp230[3];
    s32 sp218[3];
    s32 sp138[2];
    s32 sp130[2];
    s32 sp12C;
    float sp128;
    float sp124;
    s32 sp120;
    float sp11C;
    float sp118;
    float sp114;
    float sp110;
    float var_f27; // ! - uninitialized
    float var_f29;
    float var_f28;
    float var_f30;
    float var_f31;
    float var_f26;
    s32 var_r21;
    s32 var_r22;
    s32 var_r29;
    s32 var_r30;
    s32 sp10C;

    arg0->unkA0 = arg0->unkA1 = 0;
    arg0->unkA3 = arg0->unkA2 = 0;
    arg0->unkA4 = arg0->unkA6 = 0;
    switch (GWPlayerCfg[arg0->unk28].diff) {
        case 0:
            sp12C = 60;
            break;
        case 1:
            sp12C = 80;
            break;
        case 2:
            sp12C = 90;
            break;
        default:
            sp12C = 95;
            break;
    }
    for (var_r30 = 0, var_r29 = 0; var_r30 < 4; var_r30++) {
        if (var_r30 != arg0->unk28) {
            sp224[var_r29++] = &lbl_1_bss_200[var_r30];
        }
    }
    for (var_r30 = 0, var_f31 = 10000.0f; var_r30 < 3; var_r30++) {
        if (sp224[var_r30]->unk54 < var_f31) {
            var_f31 = sp224[var_r30]->unk54;
        }
    }
    for (var_r30 = 0, var_f30 = -10000.0f; var_r30 < 3; var_r30++) {
        if (sp224[var_r30]->unk54 > var_f30) {
            var_f30 = sp224[var_r30]->unk54;
        }
    }
    sp124 = ABS_INV(var_f30 - var_f31) / 2.0f;
    var_f29 = var_f30 - sp124;
    for (var_r30 = 0, var_f31 = 10000.0f; var_r30 < 3; var_r30++) {
        if (sp224[var_r30]->unk5C < var_f31) {
            var_f31 = sp224[var_r30]->unk5C;
        }
    }
    for (var_r30 = 0, var_f30 = -10000.0f; var_r30 < 3; var_r30++) {
        if (sp224[var_r30]->unk5C > var_f30) {
            var_f30 = sp224[var_r30]->unk5C;
        }
    }
    sp124 = ABS_INV(var_f30 - var_f31) / 2.0f;
    var_f28 = var_f30 - sp124;
    for (var_r30 = 0, var_f31 = 10000.0f; var_r30 < 3; var_r30++) {
        var_f26 = fn_1_595C(var_f29, var_f28, sp224[var_r30]);
        if (var_f26 < var_f31) {
            var_f31 = var_f26;
        }
    }
    if (fn_1_6D04() != 0) {
        arg0->unkB0 = 0;
        if (var_f31 < 400.0f || (arg0->unkB4 & 2)) {
            arg0->unkB4 |= 2;
            fn_1_65C0(sp254, sp224);
            if (arg0->unkBC == -1) {
                for (var_r30 = 0, sp120 = 0, var_f30 = 0.0f; var_r30 < 3; var_r30++) {
                    temp_r18 = sp224[var_r30];
                    (var_r30 >= 2) ? (var_r29 = 0) : (var_r29 = var_r30 + 1);
                    var_r17 = sp224[var_r29];
                    var_f26 = fn_1_595C(temp_r18->unk54, temp_r18->unk5C, var_r17);
                    if (var_f26 > 700.0f) {
                        sp218[var_r30] = 1;
                        sp120++;
                    }
                    else {
                        sp218[var_r30] = 0;
                    }
                    if (var_f26 > var_f30) {
                        var_f30 = var_f26;
                        var_r21 = var_r30;
                        var_f27 = fn_1_21D4(atan2d(sp254[var_r30].x - arg0->unk54, sp254[var_r30].z - arg0->unk5C));
                    }
                }
                if (sp120 > 0) {
                    var_r29 = frandmod(sp120);
                    for (var_r30 = 0; var_r30 < 3; var_r30++) {
                        if (sp218[var_r30] != 0 && var_r29-- == 0) {
                            break;
                        }
                    }
                    var_r21 = var_r30;
                    var_f27 = fn_1_21D4(atan2d(sp254[var_r30].x - arg0->unk54, sp254[var_r30].z - arg0->unk5C));
                }
                arg0->unkBC = var_r21;
                arg0->unkCC = var_f27;
            }
            else {
                var_r21 = arg0->unkBC;
                var_f27 = arg0->unkCC;
            }
            sp11C = var_f29;
            sp118 = var_f28;
            var_f29 = sp254[var_r21].x;
            var_f28 = sp254[var_r21].z;
            if (fn_1_595C(var_f29, var_f28, arg0) <= 30.0f && !(arg0->unkB4 & 1)) {
                arg0->unkC4 = fn_1_21D4(atan2d(var_f29, var_f28));
                arg0->unkB4 |= 1;
            }
            if (arg0->unkB4 & 1) {
                var_f29 = 800.0 * sind(arg0->unkC4);
                var_f28 = 800.0 * cosd(arg0->unkC4);
            }
        }
    }
    else {
        arg0->unkAC = 0;
        arg0->unkB4 = 0;
        arg0->unkBC = -1;
        if ((var_f31 >= 600.0f && fn_1_67A0(var_f29, var_f28, arg0, &sp224[0]) != 0) || (arg0->unkB0 & 0x10)) {
            arg0->unkB0 |= 0x10;
            fn_1_65C0(sp230, sp224);
            for (var_r30 = 0, var_r21 = 0, var_f31 = 10000.0f; var_r30 < 3; var_r30++) {
                var_f26 = fn_1_595C(sp230[var_r30].x, sp230[var_r30].z, arg0);
                if (var_f26 < var_f31) {
                    var_f31 = var_f26;
                    var_r21 = var_r30;
                }
            }
            sp114 = var_f29;
            sp110 = var_f28;
            var_f29 = sp230[var_r21].x;
            var_f28 = sp230[var_r21].z;
            if (fn_1_595C(var_f29, var_f28, arg0) <= 30.0f && !(arg0->unkB0 & 0x20)) {
                arg0->unkC4 = fn_1_21D4(var_f27 - 90.0f);
                arg0->unkB0 |= 0x20;
            }
            if (arg0->unkB0 & 0x20) {
                var_f29 = 800.0 * sind(arg0->unkC4);
                var_f28 = 800.0 * cosd(arg0->unkC4);
                if (fn_1_5F34(arg0, 10.0f)) {
                    arg0->unkB0 &= ~0x20;
                }
                else {
                    arg0->unkB0 |= 0x20;
                }
            }
        }
        else {
            if (arg0->unk54 >= 0.0f && arg0->unk5C < 0.0f) {
                sp138[0] = 0;
                sp138[1] = 1;
            }
            if (arg0->unk54 < 0.0f && arg0->unk5C < 0.0f) {
                sp138[0] = 3;
                sp138[1] = 0;
            }
            if (arg0->unk54 >= 0.0f && arg0->unk5C >= 0.0f) {
                sp138[0] = 1;
                sp138[1] = 2;
            }
            if (arg0->unk54 < 0.0f && arg0->unk5C >= 0.0f) {
                sp138[0] = 2;
                sp138[1] = 3;
            }
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                var_r22 = 0;
                sp10C = sp138[var_r30];
                switch (sp10C) {
                    case 0:
                        for (var_r29 = 0; var_r29 < 3; var_r29++) {
                            if (sp224[var_r29]->unk5C < -800.0f + sp224[var_r29]->unk8C + 150.0f) {
                                break;
                            }
                        }
                        if (var_r29 >= 3) {
                            var_r22 = 1;
                        }
                        break;
                    case 1:
                        for (var_r29 = 0; var_r29 < 3; var_r29++) {
                            if (sp224[var_r29]->unk54 > 800.0f - sp224[var_r29]->unk8C - 150.0f) {
                                break;
                            }
                        }
                        if (var_r29 >= 3) {
                            var_r22 = 1;
                        }
                        break;
                    case 2:
                        for (var_r29 = 0; var_r29 < 3; var_r29++) {
                            if (sp224[var_r29]->unk5C > 800.0f - sp224[var_r29]->unk8C - 150.0f) {
                                break;
                            }
                        }
                        if (var_r29 >= 3) {
                            var_r22 = 1;
                        }
                        break;
                    case 3:
                        for (var_r29 = 0; var_r29 < 3; var_r29++) {
                            if (sp224[var_r29]->unk54 < -800.0f + sp224[var_r29]->unk8C + 150.0f) {
                                break;
                            }
                        }
                        if (var_r29 >= 3) {
                            var_r22 = 1;
                        }
                        break;
                }
                sp130[var_r30] = var_r22;
            }
            var_r22 = 0;
            if ((arg0->unkB0 & 4) || (arg0->unkB0 & 8)) {
                if ((arg0->unkB0 & 4) && sp130[0] != 0) {
                    var_r22 = 1;
                }
                if ((arg0->unkB0 & 8) && sp130[1] != 0) {
                    var_r22 = 1;
                }
            }
            if (arg0->unkC0 > 0) {
                var_r22 = 1;
                arg0->unkC0--;
            }
            if (var_r22 == 0) {
                arg0->unkB0 &= ~0xC;
                if (sp130[0] != 0 && sp130[1] != 0) {
                    if (frandmod(2) != 0) {
                        arg0->unkB0 |= 4;
                        arg0->unkC0 = 30;
                    }
                    else {
                        arg0->unkB0 |= 8;
                        arg0->unkC0 = 30;
                    }
                }
                else if (sp130[0] != 0) {
                    arg0->unkB0 |= 4;
                    arg0->unkC0 = 30;
                }
                else if (sp130[1] != 0) {
                    arg0->unkB0 |= 8;
                    arg0->unkC0 = 30;
                }
                else {
                    arg0->unkB0 |= 0x10;
                }
            }
            if ((arg0->unkB0 & 4) || (arg0->unkB0 & 8)) {
                var_f27 = fn_1_21D4(atan2d(arg0->unk54, arg0->unk5C));
                if (arg0->unkB0 & 4) {
                    var_f27 += 10.0f;
                }
                else {
                    var_f27 -= 10.0f;
                }
                var_f29 = 800.0 * sind(var_f27);
                var_f28 = 800.0 * cosd(var_f27);
            }
            else {
                var_f29 = arg0->unk54;
                var_f28 = arg0->unk5C;
            }
        }
    }
    var_f26 = fn_1_595C(var_f29, var_f28, arg0);
    if (var_f26 > 100.0f || arg0->unkAC == 1) {
        if (arg0->unkAC != 1) {
            arg0->unkAC = 1;
        }
        if (var_f26 < 20.0f) {
            arg0->unkAC = 0;
            return;
        }
        if (var_f26 < 30.0f) {
            sp128 = 10.0f;
        }
        else {
            sp128 = 50.0f;
        }
        var_f27 = fn_1_21D4(atan2d(var_f29 - arg0->unk54, var_f28 - arg0->unk5C));
        arg0->unkA0 = sp128 * sind(var_f27);
        arg0->unkA1 = sp128 * -cosd(var_f27);
    }
}

void fn_1_9AF0(void)
{
    StructBss200 *temp_r31;
    StructBss200 *temp_r29;
    Vec sp6C;
    float sp44;
    float sp40;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f28;
    float var_f19;
    s32 var_r24;
    s32 var_r30;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk34 = 0;
    temp_r31->unk24 = 0;
    temp_r31->unkA8 = 0;
    temp_r31->unk38 = 0;
    temp_r31->unkBC = -1;
    while (lbl_1_bss_5B4 == 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_5B4 = 2;
    while (lbl_1_bss_5B4 == 2) {
        HuPrcVSleep();
    }
    while (TRUE) {
        temp_r31->unk60 = temp_r31->unk54;
        temp_r31->unk64 = temp_r31->unk5C;
        if (GWPlayerCfg[temp_r31->unk28].iscom == 1) {
            fn_1_78B4(temp_r31);
        }
        if (temp_r31->unk3C != 0 && temp_r31->unk48-- == 0) {
            temp_r31->unk3C = 0;
            temp_r31->unk94 = 1.0f;
            lbl_1_bss_5BC = 0;
        }
        if (temp_r31->unk24 != 0) {
            break;
        }
        switch (temp_r31->unk34) {
            case 4:
                omVibrate(temp_r31->unk28, 12, 6, 6);
                CharModelMotionSpeedSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], 1.0f);
                CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[6]);
                Hu3DModelAttrReset(temp_r31->unk00, HU3D_MOTATTR_LOOP);
                temp_r31->unk44 = 60;
                temp_r31->unk34 = 5;
                break;
            case 5:
                if (temp_r31->unk44 != 0) {
                    if (temp_r31->unk44 == 20) {
                        HuAudPlayerVoicePlay(temp_r31->unk28, 0x119);
                    }
                    temp_r31->unk44--;
                }
                else {
                    CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[7], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    temp_r31->unk44 = 20;
                    temp_r31->unk34 = 6;
                }
                break;
            case 6:
                if (temp_r31->unk44 != 0) {
                    Hu3DModelAttrReset(temp_r31->unk00, HU3D_MOTATTR_LOOP);
                    temp_r31->unk44--;
                }
                else if (Hu3DMotionEndCheck(temp_r31->unk00) == 1) {
                    CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[4], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    temp_r31->unk44 = 10;
                    temp_r31->unk34 = 7;
                }
                break;
            case 7:
                if (temp_r31->unk44 != 0) {
                    temp_r31->unk44--;
                }
                else {
                    CharModelMotionSpeedSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], 2.0f);
                    temp_r31->unk34 = 0;
                }
                break;
            default:
                HuSetVecF(&sp6C, fn_1_4E54(temp_r31->unk28, 0) / 4.0f, 0.0, -fn_1_4E54(temp_r31->unk28, 1) / 4.0f);
                temp_r31->unk90 = VECMagXYZ(&sp6C);
                if (temp_r31->unk90 >= 0.5f) {
                    CharModelMotionSpeedSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], 1.0f);
                    if (temp_r31->unk90 >= 10.0f) {
                        sp6C.x /= temp_r31->unk90;
                        sp6C.z /= temp_r31->unk90;
                        temp_r31->unk90 = 10.0f;
                        sp6C.x = 10.0f * sp6C.x;
                        sp6C.z = 10.0f * sp6C.z;
                    }
                    temp_r31->unk6C = fn_1_5858(temp_r31->unk6C, atan2d(sp6C.x, sp6C.z), 0.4f);
                    if (temp_r31->unk90 >= 8.0f) {
                        if (temp_r31->unk34 != 3) {
                            temp_r31->unk34 = 3;
                            CharModelMotionShiftSet(
                                lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                        }
                    }
                    else if (temp_r31->unk34 != 2) {
                        temp_r31->unk34 = 2;
                        CharModelMotionShiftSet(
                            lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    }
                    temp_r31->unk54 += sp6C.x * temp_r31->unk94;
                    temp_r31->unk5C += sp6C.z * temp_r31->unk94;
                }
                else if (temp_r31->unk34 != 0) {
                    temp_r31->unk34 = 0;
                    CharModelMotionSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[4]);
                    CharModelMotionSpeedSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], 2.0f);
                    Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_LOOP);
                }
                break;
        }
        if ((temp_r31->unk40 = fn_1_50A4(temp_r31, 0.0f, 0)) != -1) {
            temp_r31->unk24 = 1;
            break;
        }
        if ((temp_r31->unk40 = fn_1_52E8(temp_r31)) != -1) {
            temp_r31->unk24 = 1;
            break;
        }
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk68, temp_r31->unk6C, temp_r31->unk70);
        HuPrcVSleep();
    }
    lbl_1_bss_5BC = 0;
    if (lbl_1_bss_5A8 == lbl_1_bss_5AC) {
        var_f23 = 10.0f;
        CharModelMotionSpeedSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], 1.0f);
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        var_r30 = (360.0f - fn_1_21D4(temp_r31->unk6C)) / var_f23;
        if (temp_r31->unk6C < 180.0f) {
            var_r30 = temp_r31->unk6C / var_f23;
            var_f23 = -var_f23;
        }
        for (; var_r30 != 0; var_r30--) {
            temp_r31->unk6C += var_f23;
            Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk68, temp_r31->unk6C, temp_r31->unk70);
            HuPrcVSleep();
        }
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk68, 0.0f, temp_r31->unk70);
    }
    else {
        omVibrate(temp_r31->unk28, 12, 4, 2);
        HuAudPlayerVoicePlay(temp_r31->unk28, 0x123);
        HuAudFXPlay(0x5EC);
        temp_r29 = &lbl_1_bss_200[temp_r31->unk40];
        temp_r31->unk9C = atan2d(temp_r31->unk54 - temp_r29->unk54, temp_r31->unk5C - temp_r29->unk5C);
        var_r30 = 0;
        var_f22 = temp_r31->unk54;
        var_f21 = temp_r31->unk5C;
        while (TRUE) {
            var_f22 += 20.0 * sind(temp_r31->unk9C);
            var_f21 += 20.0 * cosd(temp_r31->unk9C);
            if (ABS_INV(var_f22) > 1200.0f || var_f21 > 1200.0f || var_f21 < -2000.0f) {
                break;
            }
            var_r30++;
        }
        var_f28 = fn_1_21D4(atan2d(temp_r31->unk54 - temp_r29->unk54, temp_r31->unk5C - temp_r29->unk5C));
        if (ABS_INV(var_f28 - temp_r31->unk6C) > 90.0f && ABS_INV(var_f28 - temp_r31->unk6C) < 270.0f) {
            CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk18, 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        }
        else {
            CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk1A, 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        }
        sp44 = temp_r31->unk58;
        var_f19 = 0.0f;
        sp40 = 180.0f / var_r30;
        var_r24 = 0;
        for (; var_r30 != 0; var_r30--) {
            temp_r31->unk54 += 20.0 * sind(temp_r31->unk9C);
            temp_r31->unk58 = 700.0 * sind(var_f19);
            temp_r31->unk5C += 20.0 * cosd(temp_r31->unk9C);
            var_f19 += sp40;
            Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
            if (Hu3DMotionTimeGet(temp_r31->unk00) == 20.0f && var_r24 == 0) {
                var_r24 = 1;
                Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_PAUSE);
            }
            HuPrcVSleep();
        }
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk54, -1000.0f, temp_r31->unk5C);
        Hu3DModelAttrSet(temp_r31->unk00, 1);
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

float fn_1_ADFC(s32 arg0, float arg1, float arg2)
{
    float temp_f31;
    float var_f29;

    temp_f31 = arg1 - fn_1_21D4(arg2);
    if (temp_f31 < 0.0f || ABS_INV(temp_f31) > 180.0f) {
        if (ABS_INV(temp_f31) > 180.0f) {
            var_f29 = (360.0f - ABS_INV(temp_f31)) / arg0;
            if (temp_f31 > 0.0f) {
                var_f29 = -var_f29;
            }
        }
        else {
            var_f29 = temp_f31 / arg0;
        }
    }
    else {
        var_f29 = temp_f31 / arg0;
    }
    return var_f29;
}

void fn_1_B054(StructBss200 *arg0)
{
    StructBss200 sp23C;
    float sp230[3];
    float sp198[2];
    Vec sp224;
    Vec sp218;
    Vec sp20C;
    float sp194;
    float sp190;
    float sp18C;
    float sp188;
    float sp184;
    float sp180;
    s32 sp17C;
    float sp178;
    float sp174;
    float var_f30;
    float var_f29;
    float var_f31;
    s32 var_r21;
    s32 var_r20;
    StructBss200 *temp_r30;
    StructBss200 *var_r29;
    StructBss200 *temp_r28;
    s32 var_r19;
    s32 var_r18;
    s32 var_r17;
    s32 var_r26;
    s32 i;

    arg0->unkA0 = arg0->unkA1 = 0;
    arg0->unkA3 = arg0->unkA2 = 0;
    arg0->unkA4 = arg0->unkA6 = 0;
    switch (GWPlayerCfg[arg0->unk28].diff) {
        case 0:
            var_r19 = 60;
            break;
        case 1:
            var_r19 = 80;
            break;
        case 2:
            var_r19 = 90;
            break;
        default:
            var_r19 = 95;
            break;
    }
    temp_r30 = &lbl_1_bss_200[lbl_1_bss_5AC];
    var_r29 = &sp23C;
    for (i = 0, var_r26 = 0; i < 4; i++) {
        if (i != lbl_1_bss_5AC && i != arg0->unk28) {
            temp_r28 = &lbl_1_bss_200[i];
            sp230[var_r26] = fn_1_21D4(atan2d(temp_r28->unk54 - temp_r30->unk54, temp_r28->unk5C - temp_r30->unk5C));
            var_r26++;
        }
    }
    if (sp230[0] > sp230[1]) {
        sp230[2] = fn_1_21D4(sp230[0] - sp230[1]);
        if (sp230[2] < 180.0f) {
            sp230[2] = fn_1_21D4(sp230[1] + sp230[2] + 180.0f);
        }
        else {
            sp230[2] = fn_1_21D4(sp230[1] - sp230[2]);
        }
    }
    else {
        sp230[2] = fn_1_21D4(sp230[1] - sp230[0]);
        if (sp230[2] < 180.0f) {
            sp230[2] = fn_1_21D4(sp230[0] + sp230[2] + 180.0f);
        }
        else {
            sp230[2] = fn_1_21D4(sp230[0] - sp230[2]);
        }
    }
    temp_r28 = &lbl_1_bss_200[arg0->unk28];
    HuSetVecF(&sp224, temp_r28->unk54, temp_r28->unk58, temp_r28->unk5C);
    HuSetVecF(&sp218, temp_r30->unk54, temp_r30->unk58, temp_r30->unk5C);
    HuSubVecF(&sp20C, &sp224, &sp218);
    sp184 = VECMagXYZ(&sp20C);
    for (i = 0, var_r21 = 0; i < 4; i++) {
        if (i != lbl_1_bss_5AC && i != arg0->unk28 && GWPlayerCfg[i].iscom) {
            temp_r28 = &lbl_1_bss_200[i];
            HuSetVecF(&sp224, temp_r28->unk54, temp_r28->unk58, temp_r28->unk5C);
            HuSetVecF(&sp218, temp_r30->unk54, temp_r30->unk58, temp_r30->unk5C);
            HuSubVecF(&sp20C, &sp224, &sp218);
            sp194 = VECMagXYZ(&sp20C);
            if (sp194 < sp184) {
                var_r21++;
            }
        }
    }
    if (arg0->unkAC != 2) {
        if (fn_1_6D04() != 0) {
            arg0->unkAC = 0;
        }
        else {
            if (ABS_INV(temp_r30->unk54) > 600.0f && ABS_INV(temp_r30->unk5C) > 600.0f) {
                if (var_r21 <= 0) {
                    arg0->unkAC = 0;
                }
                else {
                    arg0->unkAC = 2;
                }
            }
            else {
                if (var_r21 <= 0) {
                    arg0->unkAC = 0;
                }
                else {
                    arg0->unkAC = 1;
                }
            }
        }
    }
    if (arg0->unkAC != 3 && arg0->unkD0 > 180) {
        arg0->unkAC = 3;
        arg0->unkD4 = frandmod(120) + 120;
    }
    switch (arg0->unkAC) {
        case 0:
            var_f30 = temp_r30->unk54;
            var_f29 = temp_r30->unk5C;
            var_f31 = fn_1_21D4(atan2d(var_f30 - arg0->unk54, var_f29 - arg0->unk5C));
            break;
        case 1:
            var_f30 = var_f29 = sp18C = sp188 = 0.0f;
            if (temp_r30->unk54 >= 300.0f && temp_r30->unk5C < -300.0f) {
                var_f30 = 550.0f;
                var_f29 = -100.0f;
                sp18C = 100.0f;
                sp188 = 550.0f;
            }
            if (temp_r30->unk54 < -300.0f && temp_r30->unk5C < -300.0f) {
                var_f30 = -550.0f;
                var_f29 = -100.0f;
                sp18C = -100.0f;
                sp188 = 550.0f;
            }
            if (temp_r30->unk54 >= 300.0f && temp_r30->unk5C >= 300.0f) {
                var_f30 = 550.0f;
                var_f29 = -100.0f;
                sp18C = 100.0f;
                sp188 = -550.0f;
            }
            if (temp_r30->unk54 < -300.0f && temp_r30->unk5C >= -300.0f) {
                var_f30 = -550.0f;
                var_f29 = -100.0f;
                sp18C = -100.0f;
                sp188 = -550.0f;
            }
            if (temp_r30->unk54 > 300.0f && temp_r30->unk5C > -300.0f && temp_r30->unk5C < 300.0f) {
                var_f30 = 200.0f;
                var_f29 = 550.0f;
                sp18C = 200.0f;
                sp188 = -550.0f;
            }
            if (temp_r30->unk54 < -300.0f && temp_r30->unk5C > -300.0f && temp_r30->unk5C < 300.0f) {
                var_f30 = -200.0f;
                var_f29 = 550.0f;
                sp18C = -200.0f;
                sp188 = -550.0f;
            }
            if (temp_r30->unk54 < 300.0f && temp_r30->unk54 > -300.0f && temp_r30->unk5C < -300.0f) {
                var_f30 = 550.0f;
                var_f29 = -200.0f;
                sp18C = -550.0f;
                sp188 = -200.0f;
            }
            if (temp_r30->unk54 < 300.0f && temp_r30->unk54 > -300.0f && temp_r30->unk5C > 300.0f) {
                var_f30 = 550.0f;
                var_f29 = 200.0f;
                sp18C = -550.0f;
                sp188 = 200.0f;
            }
            for (i = 0, var_r17 = -1, sp190 = 10000.0f; i < 4; i++) {
                if (i != lbl_1_bss_5AC) {
                    temp_r28 = &lbl_1_bss_200[i];
                    HuSetVecF(&sp224, temp_r30->unk54, 0.0, temp_r30->unk5C);
                    HuSetVecF(&sp218, temp_r28->unk54, 0.0, temp_r28->unk5C);
                    HuSubVecF(&sp20C, &sp224, &sp218);
                    sp194 = VECMagXZ(&sp20C);
                    if (sp194 < sp190) {
                        sp190 = sp194;
                        var_r17 = i;
                    }
                }
            }
            for (i = 0, var_r26 = -1, sp190 = 10000.0f; i < 4; i++) {
                if (i != lbl_1_bss_5AC && i != var_r17) {
                    temp_r28 = &lbl_1_bss_200[i];
                    HuSetVecF(&sp224, temp_r30->unk54, 0.0, temp_r30->unk5C);
                    HuSetVecF(&sp218, temp_r28->unk54, 0.0, temp_r28->unk5C);
                    HuSubVecF(&sp20C, &sp224, &sp218);
                    sp194 = VECMagXZ(&sp20C);
                    if (sp194 < sp190) {
                        sp190 = sp194;
                        var_r26 = i;
                    }
                }
            }
            if (arg0->unk28 != var_r26) {
                var_f30 = sp18C;
                var_f29 = sp188;
            }
            var_f31 = fn_1_21D4(atan2d(var_f30 - arg0->unk54, var_f29 - arg0->unk5C));
            break;
        case 2:
            for (i = 0, var_r26 = 0; i < 4; i++) {
                if (i != lbl_1_bss_5AC && i != arg0->unk28) {
                    temp_r28 = &lbl_1_bss_200[i];
                    sp198[var_r26++] = fn_1_21D4(atan2d(temp_r28->unk54 - arg0->unk54, temp_r28->unk5C - arg0->unk5C));
                }
            }
            sp180 = fn_1_21D4(ABS_INV(sp198[0] - sp198[1]) / 2.0f);
            if (sp180 < 90.0f) {
                sp180 += 180.0f;
            }
            if (sp198[0] < sp198[1]) {
                sp180 += sp198[0];
            }
            else {
                sp180 += sp198[1];
            }
            sp180 = fn_1_21D4(sp180);
            if (sqrtf(arg0->unk54 * arg0->unk54 + arg0->unk5C * arg0->unk5C) < 500.0f) {
                sp194 = 600.0f;
                var_f30 = arg0->unk54 + sp194 * sind(sp180);
                var_f29 = arg0->unk5C + sp194 * cosd(sp180);
                var_f31 = fn_1_21D4(atan2d(var_f30 - arg0->unk54, var_f29 - arg0->unk5C));
            }
            else {
                arg0->unkAC = 1;
            }
            break;
        case 3:
            for (i = 0, sp174 = 10000.0f; i < 4; i++) {
                if (i != lbl_1_bss_5AC && i != arg0->unk28) {
                    temp_r28 = &lbl_1_bss_200[i];
                    sp178 = fn_1_595C(temp_r28->unk54, temp_r28->unk5C, arg0);
                    if (sp178 < sp174) {
                        sp174 = sp178;
                        sp17C = i;
                    }
                }
            }
            temp_r28 = &lbl_1_bss_200[sp17C];
            var_f31 = fn_1_21D4(180.0 + atan2d(temp_r28->unk54 - arg0->unk54, temp_r28->unk5C - arg0->unk5C));
            var_f30 = arg0->unk54 + 100.0 * sind(var_f31);
            var_f29 = arg0->unk5C + 100.0 * cosd(var_f31);
            if (arg0->unkD4-- == 0) {
                arg0->unkD0 = 0;
                arg0->unkAC = 1;
            }
            break;
    }
    var_r29->unk9C = 0.0f;
    if (ABS_INV(arg0->unk6C - var_f31) > 30.0f && ABS_INV(arg0->unk6C - var_f31) < 330.0f) {
        if (ABS_INV(fn_1_21D4(arg0->unk6C - var_f31)) > 180.0f) {
            arg0->unkA0 = -30;
            var_r29->unk9C = arg0->unk98;
        }
        else {
            arg0->unkA0 = 30;
            var_r29->unk9C = -arg0->unk98;
        }
    }
    if (arg0->unkB8 == 0) {
        HuSetVecF(&sp224, var_f30, 0.0, var_f29);
        HuSetVecF(&sp218, arg0->unk54, 0.0, arg0->unk5C);
        HuSubVecF(&sp20C, &sp224, &sp218);
        if (VECMagXZ(&sp20C) > 10.0f) {
            if (ABS_INV(arg0->unk6C - var_f31) < 90.0f || ABS_INV(arg0->unk6C - var_f31) > 270.0f) {
                arg0->unkA4 |= 0x100;
            }
            else {
                arg0->unkA4 |= 0x200;
                var_r29->unk9C = -var_r29->unk9C;
            }
        }
    }
    var_r29->unk28 = arg0->unk28;
    var_r29->unk54 = arg0->unk54;
    var_r29->unk58 = arg0->unk58;
    var_r29->unk5C = arg0->unk5C;
    var_r29->unk90 = arg0->unk90;
    var_r29->unk9C = fn_1_21D4(arg0->unk9C + var_r29->unk9C);
    var_r29->unk8C = lbl_1_bss_200[lbl_1_bss_5AC].unk8C + arg0->unk8C + arg0->unk90;
    var_r20 = fn_1_50A4(var_r29, arg0->unk90, 0);
    if (var_r20 != -1 && var_r20 != lbl_1_bss_5AC) {
        if (arg0->unkA4 & 0x100) {
            var_r29->unk54 += var_r29->unk90 * sind(var_r29->unk9C);
            var_r29->unk5C += var_r29->unk90 * cosd(var_r29->unk9C);
        }
        if (arg0->unkA4 & 0x200) {
            var_r29->unk54 -= var_r29->unk90 * sind(var_r29->unk9C);
            var_r29->unk5C -= var_r29->unk90 * cosd(var_r29->unk9C);
        }
        temp_r28 = &lbl_1_bss_200[var_r20];
        HuSetVecF(&sp224, arg0->unk54, 0.0, arg0->unk5C);
        HuSetVecF(&sp218, temp_r28->unk54, 0.0, temp_r28->unk5C);
        HuSubVecF(&sp20C, &sp224, &sp218);
        sp194 = VECMagXYZ(&sp20C);
        HuSetVecF(&sp224, var_r29->unk54, 0.0, var_r29->unk5C);
        HuSetVecF(&sp218, temp_r28->unk54, 0.0, temp_r28->unk5C);
        HuSubVecF(&sp20C, &sp224, &sp218);
        sp190 = VECMagXYZ(&sp20C);
        var_r18 = fn_1_50A4(var_r29, 0.0f, 0);
        if (sp194 > sp190 || (var_r20 != var_r18 && var_r18 != -1)) {
            arg0->unkA0 = 30;
            arg0->unkA4 = 0;
            arg0->unkAC = 2;
            arg0->unkA8 = 300;
            if (arg0->unkB8 == 0) {
                arg0->unkB8 = 60;
            }
        }
        else if (var_r18 == -1) {
            arg0->unkAC = 2;
            if (ABS_INV(arg0->unk6C - var_f31) < 90.0f || ABS_INV(arg0->unk6C - var_f31) > 270.0f) {
                arg0->unkA4 |= 0x100;
            }
            else {
                arg0->unkA4 |= 0x200;
                var_r29->unk9C = -var_r29->unk9C;
            }
        }
        else {
            arg0->unkA0 = 30;
        }
    }
    if (arg0->unkB8 != 0) {
        arg0->unkB8--;
    }
}

void fn_1_DECC(void)
{
    StructBss200 *temp_r31;
    s32 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    for (i = 0; i < 20; i++) {
        temp_r31->unk88 -= 4.0f;
        Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk80, temp_r31->unk84, temp_r31->unk88);
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 fn_1_DF3C(StructBss200 *arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r31 = 1;
    var_r30 = 1;
    if (arg0->unk34 != 4 && arg0->unk34 != 5) {
        var_r30 = 0;
    }
    if (var_r30 == 0 && arg0->unk34 != 6) {
        var_r31 = 0;
    }
    return var_r31;
}

void fn_1_DF98(void)
{
    float var_f27;
    float var_f25;
    float var_f26;
    StructBss200 *temp_r31;
    StructBss200 *temp_r30;
    s32 var_r25;
    s32 var_r29;
    s32 var_r28;
    s32 sp90;
    Process *sp8C;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    Process *sp78;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk34 = 0;
    temp_r31->unkA8 = temp_r31->unkAC = temp_r31->unkB0 = temp_r31->unkB4 = temp_r31->unkB8 = temp_r31->unk50 = 0;
    temp_r31->unkC0 = 0;
    temp_r31->unk38 = 0;
    temp_r31->unkD0 = 0;
    while (lbl_1_bss_5B4 == 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_5B4 = 2;
    while (lbl_1_bss_5B4 == 2) {
        HuPrcVSleep();
    }
    temp_r31->unkD8 = temp_r31->unk54;
    temp_r31->unkDC = temp_r31->unk5C;
    var_r29 = 0;
    while (TRUE) {
        temp_r31->unk60 = temp_r31->unk54;
        temp_r31->unk64 = temp_r31->unk5C;
        if (GWPlayerCfg[temp_r31->unk28].iscom == 1) {
            fn_1_B054(temp_r31);
        }
        if (temp_r31->unk3C != 0) {
            if (temp_r31->unk48 == 300) {
                sp8C = HuPrcChildCreate(fn_1_32F8, 0x2000, 0x1000, 0, HuPrcCurrentGet());
                sp8C->user_data = (void *)temp_r31->unk28;
            }
            if (temp_r31->unk48-- == 0) {
                temp_r31->unk3C = 0;
                temp_r31->unk90 = 2.25f;
                temp_r31->unk98 = 0.66f;
            }
        }
        if (temp_r31->unk24 != 0) {
            break;
        }
        switch (temp_r31->unk34) {
            case 8:
                if (temp_r31->unk44 != 0) {
                    temp_r31->unk44--;
                }
                else {
                    Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
                    temp_r31->unk34 = 0;
                }
                break;
            case 4:
                omVibrate(temp_r31->unk28, 12, 4, 2);
                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
                temp_r31->unk44 = 90;
                temp_r31->unk4C = 30;
                temp_r31->unk34 = 5;
                break;
            case 5:
                if (temp_r31->unk4C-- == 0) {
                    HuAudFXPlay(0x5E7);
                    temp_r31->unk74 = temp_r31->unk54;
                    temp_r31->unk78 = temp_r31->unk58;
                    temp_r31->unk7C = temp_r31->unk5C;
                    temp_r31->unk38 |= 1;
                }
                if (temp_r31->unk44 != 0) {
                    temp_r31->unk44--;
                }
                else {
                    Hu3DMotionSet(temp_r31->unk00, temp_r31->unk06[5]);
                    Hu3DModelAttrReset(temp_r31->unk00, HU3D_MOTATTR_LOOP);
                    temp_r31->unk34 = 6;
                }
                break;
            case 6:
                if (Hu3DMotionEndCheck(temp_r31->unk00) == 1) {
                    Hu3DMotionSet(temp_r31->unk00, temp_r31->unk06[0]);
                    temp_r31->unk34 = 0;
                }
                break;
            default:
                if (fn_1_4E54(temp_r31->unk28, 0) > 20) {
                    temp_r31->unk9C -= temp_r31->unk98;
                    if (temp_r31->unk9C < 0.0f) {
                        temp_r31->unk9C += 360.0f;
                    }
                    temp_r31->unk6C = temp_r31->unk9C;
                }
                if (fn_1_4E54(temp_r31->unk28, 0) < -20) {
                    temp_r31->unk9C += temp_r31->unk98;
                    if (temp_r31->unk9C > 360.0f) {
                        temp_r31->unk9C -= 360.0f;
                    }
                    temp_r31->unk6C = temp_r31->unk9C;
                }
                if (fn_1_5038(temp_r31->unk28) & 0x100) {
                    temp_r31->unk54 += temp_r31->unk90 * sind(temp_r31->unk9C);
                    temp_r31->unk5C += temp_r31->unk90 * cosd(temp_r31->unk9C);
                }
                if (fn_1_5038(temp_r31->unk28) & 0x200) {
                    temp_r31->unk54 -= temp_r31->unk90 * sind(temp_r31->unk9C);
                    temp_r31->unk5C -= temp_r31->unk90 * cosd(temp_r31->unk9C);
                }
                if (fn_1_5038(temp_r31->unk28) & 0x300) {
                    if (temp_r31->unk3C != 1) {
                        if (temp_r31->unk34 != 2) {
                            temp_r31->unk34 = 2;
                            if (fn_1_5038(temp_r31->unk28) & 0x100) {
                                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                                Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                            }
                            else {
                                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV);
                                Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                            }
                            if (var_r29 != 0) {
                                var_r29 = 0;
                                HuAudFXStop(var_r25);
                            }
                        }
                    }
                    else {
                        if (temp_r31->unk34 != 3) {
                            temp_r31->unk34 = 3;
                            temp_r31->unk50 = 0;
                            if (fn_1_5038(temp_r31->unk28) & 0x100) {
                                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                                Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                            }
                            else {
                                Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV);
                                Hu3DMotionShiftSpeedSet(temp_r31->unk00, 2.0f);
                            }
                            if (var_r29 != 0) {
                                var_r29 = 0;
                                HuAudFXStop(var_r25);
                            }
                        }
                    }
                    if (temp_r31->unk3C != 1) {
                        sp88 = 8;
                        sp84 = 32;
                    }
                    else {
                        sp88 = 7;
                        sp84 = 22;
                    }
                    if (temp_r31->unk50 == sp88) {
                        HuAudFXPlay(0x5E0);
                    }
                    if (temp_r31->unk50 == sp84) {
                        HuAudFXPlay(0x5E0);
                    }
                    temp_r31->unk50++;
                    if (temp_r31->unk3C != 1) {
                        if (temp_r31->unk50 >= 50) {
                            temp_r31->unk50 -= 50;
                        }
                    }
                    else {
                        if (temp_r31->unk50 >= 30) {
                            temp_r31->unk50 -= 30;
                        }
                    }
                }
                else {
                    if (ABS_INV(fn_1_4E54(temp_r31->unk28, 0)) <= 20) {
                        if (temp_r31->unk34 != 0) {
                            temp_r31->unk34 = 0;
                            Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                            if (var_r29 != 0) {
                                var_r29 = 0;
                                HuAudFXStop(var_r25);
                            }
                        }
                    }
                    else {
                        if (temp_r31->unk34 != 1) {
                            temp_r31->unk34 = 1;
                            Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[3], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                            Hu3DMotionShiftSpeedSet(temp_r31->unk00, 1.5f);
                            var_r25 = HuAudFXPlay(0x5EB);
                            var_r29 = 1;
                        }
                    }
                }
                if ((sp90 = fn_1_50A4(temp_r31, 0.0f, 0)) != -1) {
                    temp_r30 = &lbl_1_bss_200[sp90];
                    if (GWPlayerCfg[temp_r30->unk28].group != 0) {
                        HuAudFXPlay(0x5ED);
                        temp_r31->unk34 = 8;
                        temp_r31->unk44 = 90;
                        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[6], 0.0f, 5.0f, 0U);
                        if ((temp_r30->unk34 == 4 || temp_r30->unk34 == 5 || temp_r30->unk34 == 6) == FALSE) {
                            temp_r30->unk34 = 8;
                            temp_r30->unk44 = 90;
                            Hu3DMotionShiftSet(temp_r30->unk00, temp_r30->unk06[6], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
                        }
                        temp_r31->unk54 = temp_r31->unk60;
                        temp_r31->unk5C = temp_r31->unk64;
                    }
                    else {
                        temp_r30->unk24 = 1;
                        temp_r30->unk40 = temp_r31->unk28;
                    }
                }
                if ((sp90 = fn_1_52E8(temp_r31)) != -1) {
                    temp_r30 = &lbl_1_bss_200[sp90];
                    if (GWPlayerCfg[temp_r30->unk28].group != 0) {
                        HuAudFXPlay(0x5ED);
                        temp_r31->unk34 = 8;
                        temp_r31->unk44 = 90;
                        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[6], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
                        if ((temp_r30->unk34 == 4 || temp_r30->unk34 == 5 || temp_r30->unk34 == 6) == FALSE) {
                            temp_r30->unk34 = 8;
                            temp_r30->unk44 = 90;
                            Hu3DMotionShiftSet(temp_r30->unk00, temp_r30->unk06[6], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
                        }
                        temp_r31->unk54 = temp_r31->unk60;
                        temp_r31->unk5C = temp_r31->unk64;
                    }
                    else {
                        temp_r30->unk24 = 1;
                        temp_r30->unk40 = temp_r31->unk28;
                    }
                }
                break;
        }
        if (temp_r31->unkD8 == temp_r31->unk54 && temp_r31->unkDC == temp_r31->unk5C) {
            temp_r31->unkD0++;
        }
        else {
            temp_r31->unkD8 = temp_r31->unk54;
            temp_r31->unkDC = temp_r31->unk5C;
            temp_r31->unkD0 = 0;
        }
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk68, temp_r31->unk6C, temp_r31->unk70);
        HuPrcVSleep();
    }
    if (var_r29 != 0) {
        HuAudFXStop(var_r25);
    }
    if (lbl_1_bss_5A8 == lbl_1_bss_5AC) {
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[0], 0.0f, 2.0f, HU3D_MOTATTR_LOOP);
        HuPrcSleep(90);
        if (lbl_1_bss_5AC == 0) {
            if (temp_r31->unk28 != 0) {
                HuAudFXPlay(0x5EA);
            }
        }
        else {
            if (temp_r31->unk28 == 0) {
                HuAudFXPlay(0x5EA);
            }
        }
        Hu3DModelAttrReset(temp_r31->unk04, 1);
        Hu3DModelAttrReset(temp_r31->unk04, HU3D_MOTATTR_PAUSE);
        Hu3DModelPosSet(temp_r31->unk04, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[7], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        if (lbl_1_bss_5AC == 0) {
            if (temp_r31->unk28 != 0) {
                HuAudFXPlay(0x5E3);
            }
        }
        else {
            if (temp_r31->unk28 == 0) {
                HuAudFXPlay(0x5E3);
            }
        }
        HuPrcSleep(15);
        HuPrcSleep(30);
        temp_r31->unk74 = temp_r31->unk54;
        temp_r31->unk78 = temp_r31->unk58;
        temp_r31->unk7C = temp_r31->unk5C;
        temp_r31->unk38 |= 2;
        while (!Hu3DMotionEndCheck(temp_r31->unk00)) {
            HuPrcVSleep();
        }
        lbl_1_bss_594[temp_r31->unk28] = HuAudPlayerVoicePlay(temp_r31->unk28, 0x11A);
        CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk1C[3], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        Hu3DModelHookReset(temp_r31->unk00);
        Hu3DModelShadowSet(temp_r31->unk02);
        var_f27 = 50.0f;
        Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk54, temp_r31->unk58 + var_f27, temp_r31->unk5C);
        HuPrcSleep(60);
        for (sp80 = 0, sp7C = 0; sp80 < 90; sp80++) {
            if (sp7C & 1) {
                Hu3DModelAttrReset(temp_r31->unk00, 1);
                Hu3DModelAttrReset(temp_r31->unk04, 1);
            }
            else {
                Hu3DModelAttrSet(temp_r31->unk00, 1);
                Hu3DModelAttrSet(temp_r31->unk04, 1);
            }
            sp7C++;
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(temp_r31->unk04, 1);
        for (var_r28 = 0, var_f25 = 1.0f; var_r28 < 30; var_r28++) {
            var_f25 -= 0.033333335f;
            Hu3DModelTPLvlSet(temp_r31->unk00, var_f25);
            if (var_f27 > 0.0f) {
                var_f27 -= 5.0f;
                Hu3DModelPosSet(temp_r31->unk02, temp_r31->unk54, temp_r31->unk58 + var_f27, temp_r31->unk5C);
            }
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(temp_r31->unk00, 1);
    }
    else {
        var_f26 = temp_r31->unk98;
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[3], 0.0f, 2.0f, HU3D_MOTATTR_LOOP);
        if (fn_1_21D4(temp_r31->unk6C) != 0.0f) {
            var_r28 = (360.0f - fn_1_21D4(temp_r31->unk6C)) / var_f26;
            if (temp_r31->unk6C < 180.0f) {
                var_r28 = temp_r31->unk6C / var_f26;
                var_f26 = -var_f26;
            }
            while (var_r28 != 0) {
                temp_r31->unk6C += var_f26;
                Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk68, temp_r31->unk6C, temp_r31->unk70);
                HuPrcVSleep();
                var_r28--;
            }
            Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk68, 0.0f, temp_r31->unk70);
        }
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk06[0], 0.0f, 2.0f, HU3D_MOTATTR_LOOP);
        while (lbl_1_bss_5A4 < 60) {
            HuPrcVSleep();
        }
        sp78 = HuPrcChildCreate(fn_1_DECC, 0x2000, 0x1000, 0, HuPrcCurrentGet());
        sp78->user_data = temp_r31;
        CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk1C[2], 0.0f, 2.0f, HU3D_MOTATTR_NONE);
        temp_r31->unk34 = 10;
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_F73C(void)
{
    StructBss200 *var_r31;
    float var_f31;
    s32 var_r30;
    s32 var_r29;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        Hu3DModelAttrReset(lbl_1_bss_200[var_r30].unk00, 1);
    }
    for (var_r29 = 0, var_f31 = 1000.0f; var_r29 < 60; var_r29++, var_f31 -= 7.5f) {
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            if (var_r30 != lbl_1_bss_5AC) {
                var_r31 = &lbl_1_bss_200[var_r30];
                var_r31->unk54 = var_f31 * sind(var_r31->unk6C - 180.0f);
                var_r31->unk5C = var_f31 * cosd(var_r31->unk6C - 180.0f);
                Hu3DModelPosSet(var_r31->unk00, var_r31->unk54, var_r31->unk58, var_r31->unk5C);
            }
        }
        HuPrcVSleep();
    }
    var_r31->unk54 = 550.0 * sind(var_r31->unk6C - 180.0f);
    var_r31->unk5C = 550.0 * cosd(var_r31->unk6C - 180.0f);
    Hu3DModelPosSet(var_r31->unk00, var_r31->unk54, var_r31->unk58, var_r31->unk5C);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        if (var_r30 != lbl_1_bss_5AC) {
            var_r31 = &lbl_1_bss_200[var_r30];
            Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk06[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        }
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_F9BC(void)
{
    StructBss200 *temp_r31;
    float temp_f26;
    float temp_f28;
    float temp_f27;
    float temp_f29;
    float temp_f30;
    float var_f31;
    s32 var_r28;
    s32 var_r30;
    s32 var_r29;
    s32 var_r27;

    HuAudFXPlay(0x5E5);
    temp_r31 = &lbl_1_bss_200[lbl_1_bss_5AC];
    CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[4], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    var_r27 = 180;
    temp_f29 = ((CenterM->z - 687.0f) / var_r27) * 40.0f / 60.0f;
    temp_f26 = ((CenterM->z - 687.0f) / var_r27) * 20.0f / 60.0f;
    temp_f30 = CenterM->y;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        for (var_r29 = 30, var_f31 = 0.0f; var_r29 != 0; var_r29--, var_f31 += 3.0f) {
            CenterM->y = temp_f30 + 50.0 * sind(var_f31);
            CenterM->z -= 2.0f * temp_f29;
            HuPrcVSleep();
        }
        for (var_r29 = 20, var_f31 = 90.0f; var_r29 != 0; var_r29--, var_f31 += 4.5f) {
            CenterM->y = temp_f30 + 50.0 * sind(var_f31);
            CenterM->z -= 2.0f * temp_f26 * 1.5f;
            HuPrcVSleep();
        }
        HuAudFXPlay(0x5DF);
        for (var_r28 = 0; var_r28 < 4; var_r28++) {
            omVibrate(var_r28, 12, 12, 0);
        }
        HuPrcSleep(5);
        for (var_r29 = 10, var_f31 = 180.0f; var_r29 != 0; var_r29--, var_f31 += 18.0f) {
            CenterM->y = temp_f30 + 10.0 * sind(var_f31);
            HuPrcVSleep();
        }
        HuPrcSleep(10);
    }
    HuPrcChildCreate(fn_1_F73C, 0x2000, 0x1000, 0, HuPrcCurrentGet());
    temp_f28 = CRotM->x;
    temp_f30 = CenterM->y;
    temp_f29 = CenterM->z;
    temp_f27 = CZoomM[0];
    for (var_r30 = 0; var_r30 < 60; var_r30++) {
        CRotM->x += (-45.0f - temp_f28) / 60.0f;
        CenterM->y += (100.0f - temp_f30) / 60.0f;
        CenterM->z += (70.0f - temp_f29) / 60.0f;
        CZoomM[0] += (2130.0f - temp_f27) / 60.0f;
        HuPrcVSleep();
    }
    HuAudFXPlay(0x5DF);
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        omVibrate(var_r28, 12, 12, 0);
    }
    Hu3DModelAttrSet(lbl_1_bss_5B8, 1);
    HuAudPlayerVoicePlay(temp_r31->unk28, 0x128);
    temp_r31 = &lbl_1_bss_200[lbl_1_bss_5AC];
    while (Hu3DMotionEndCheck(temp_r31->unk00)) {
        HuPrcVSleep();
    }
    CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[5], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(15);
    while (Hu3DMotionEndCheck(temp_r31->unk00)) {
        HuPrcVSleep();
    }
    CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    HuPrcSleep(60);
    temp_f28 = CRotM->x;
    temp_f30 = CenterM->y;
    temp_f29 = CenterM->z;
    temp_f27 = CZoomM[0];
    for (var_r30 = 0; var_r30 < 60; var_r30++) {
        CRotM->x += (-35.0f - temp_f28) / 60.0f;
        CenterM->y += -temp_f30 / 60.0f;
        CenterM->z += (-250.0f - temp_f29) / 60.0f;
        CZoomM[0] += (4820.0f - temp_f27) / 60.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    temp_r31 = &lbl_1_bss_200[lbl_1_bss_5AC];
    CharModelMotionShiftSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], temp_r31->unk06[4], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    HuPrcSleep(15);
    while (Hu3DMotionEndCheck(temp_r31->unk00)) {
        HuPrcVSleep();
    }
    CharModelMotionSpeedSet(lbl_1_data_0[GWPlayerCfg[temp_r31->unk28].character], 2.0f);
}

void fn_1_10258(s32 arg0)
{
    StructBss200 *var_r30;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    s32 i;

    if (arg0 == lbl_1_bss_5AC) {
        HuPrcSleep(120);
        temp_f31 = CenterM->x;
        temp_f30 = CenterM->z;
        temp_f29 = CZoomM[0];
        for (i = 0; i < 60; i++) {
            var_r30 = &lbl_1_bss_200[lbl_1_bss_5AC];
            CenterM->x += (var_r30->unk54 - temp_f31) / 60.0f;
            CenterM->z += (var_r30->unk5C - 100.0f - temp_f30) / 60.0f;
            CZoomM[0] += (1000.0f - temp_f29) / 60.0f;
            HuPrcVSleep();
        }
        for (i = 0; i < 4; i++) {
            if (i == lbl_1_bss_5AC) {
                continue;
            }
            HuAudFXStop(lbl_1_bss_594[i]);
        }
        HuAudSStreamPlay(1);
        Hu3DMotionShiftSet(var_r30->unk00, var_r30->unk16, 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    }
    else {
        for (lbl_1_bss_5A4 = 0; lbl_1_bss_5A4 < 60; lbl_1_bss_5A4++) {
            HuPrcVSleep();
        }
        HuAudSStreamPlay(1);
    }
}

void fn_1_104A0(void)
{
    while (TRUE) {
        if (omSysExitReq == 1) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            HuPrcSleep(60);
            MGSeqKillAll();
            omOvlReturnEx(1, 1);
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_10500(void)
{
    s16 temp_r28;
    s16 temp_r30;
    s16 var_r29;
    s32 var_r26;
    s32 var_r27;
    s32 sp8[3];
    s32 i;

    lbl_1_bss_5B4 = 0;
    lbl_1_bss_5A8 = -1;
    fn_1_F9BC();
    HuPrcSleep(30);
    lbl_1_bss_5B4 = 1;
    while (lbl_1_bss_5B4 == 1) {
        HuPrcVSleep();
    }
    var_r26 = HuAudSeqPlay(0x49);
    temp_r30 = MGSeqStartCreate();
    while (MGSeqStatGet(temp_r30) != 0) {
        HuPrcVSleep();
    }
    var_r29 = 0xAC7;
    temp_r28 = MGSeqTimerCreate(var_r29 / 60);
    lbl_1_bss_5B4 = 3;
    while (TRUE) {
        if (lbl_1_bss_200[lbl_1_bss_5AC].unk24 == 1) {
            break;
        }
        if (var_r29 < 59) {
            lbl_1_bss_5A8 = lbl_1_bss_5AC;
            break;
        }
        MGSeqParamSet(temp_r28, 1, var_r29-- / 60);
        lbl_1_bss_5B0++;
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_200[i].unk24 = 1;
    }
    lbl_1_bss_5B4 = 4;
    HuAudSeqFadeOut(var_r26, 100);
    MGSeqParamSet(temp_r28, 2, -1);
    temp_r30 = MGSeqFinishCreate();
    while (MGSeqStatGet(temp_r30) != 0) {
        HuPrcVSleep();
    }
    fn_1_10258(lbl_1_bss_5A8);
    if (lbl_1_bss_5A8 == lbl_1_bss_5AC) {
        GWPlayerCoinWinSet(lbl_1_bss_5A8, 10);
        temp_r30 = MGSeqWinCreate(GWPlayerCfg[lbl_1_bss_5A8].character, -1, -1, -1);
    }
    else {
        for (i = 0, var_r27 = 0; i < 4; i++) {
            if (i != lbl_1_bss_5AC) {
                sp8[var_r27++] = i;
                GWPlayerCoinWinSet(i, 10);
            }
        }
        temp_r30 = MGSeqWinCreate(GWPlayerCfg[sp8[0]].character, GWPlayerCfg[sp8[1]].character, GWPlayerCfg[sp8[2]].character, -1);
    }
    HuPrcSleep(210);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuPrcSleep(60);
    HuAudFadeOut(1);
    MGSeqKillAll();
    omOvlReturnEx(1, 1);
    while (TRUE) {
        HuPrcVSleep();
    }
}
