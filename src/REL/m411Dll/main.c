#include "REL/executor.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/frand.h"
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
#include "game/wipe.h"

#include "ext_math.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#endif

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[5];
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ Vec unk1C;
} UnkBss138InnerStruct00; // Size 0x28

typedef struct {
    /* 0x000 */ s16 unk00;
    /* 0x002 */ char unk02[2];
    /* 0x004 */ Vec unk04;
    /* 0x010 */ Vec unk10;
    /* 0x01C */ UnkBss138InnerStruct00 unk1C[5];
    /* 0x0E4 */ UnkBss138InnerStruct00 unkE4[5];
    /* 0x1AC */ UnkBss138InnerStruct00 unk1AC[4];
    /* 0x24C */ char unk24C[0x28];
    /* 0x274 */ UnkBss138InnerStruct00 unk274[5];
} UnkBss138Struct; // Size 0x33C

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
} UnkBss474DoublyInnerStruct6C; // Size unknown

// Maybe HsfObject, but unk1C doesn't seem to match.
typedef struct {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ UnkBss474DoublyInnerStruct6C unk1C;
} UnkBss474InnerStruct6C; // Size unknown

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
} UnkBss474InnerStructE4; // Size 0x24

typedef struct {
    /* 0x000 */ s16 unk00;
    /* 0x002 */ s16 unk02;
    /* 0x004 */ s16 unk04;
    /* 0x006 */ s16 unk06;
    /* 0x008 */ s16 unk08;
    /* 0x00A */ s16 unk0A;
    /* 0x00C */ s16 unk0C;
    /* 0x00E */ s16 unk0E[9];
    /* 0x020 */ s16 unk20;
    /* 0x022 */ s16 unk22[9];
    /* 0x034 */ s32 unk34;
    /* 0x038 */ s32 unk38;
    /* 0x03C */ s32 unk3C;
    /* 0x040 */ s32 unk40;
    /* 0x044 */ s32 unk44;
    /* 0x048 */ float unk48;
    /* 0x04C */ float unk4C;
    /* 0x050 */ float unk50;
    /* 0x054 */ float unk54;
    /* 0x058 */ float unk58;
    /* 0x05C */ float unk5C;
    /* 0x060 */ float unk60;
    /* 0x064 */ float unk64;
    /* 0x068 */ float unk68;
    /* 0x06C */ UnkBss474InnerStruct6C *unk6C[10];
    /* 0x094 */ UnkBss474InnerStruct6C *unk94[10];
    /* 0x0BC */ UnkBss474InnerStruct6C *unkBC[10];
    /* 0x0E4 */ UnkBss474InnerStructE4 unkE4[10];
    /* 0x24C */ AnimData *unk24C;
    /* 0x250 */ AnimData *unk250;
    /* 0x254 */ s8 unk254;
    /* 0x255 */ s8 unk255;
    /* 0x256 */ s8 unk256;
    /* 0x257 */ s8 unk257;
    /* 0x258 */ u16 unk258;
    /* 0x25A */ char unk25A[0xA];
    /* 0x264 */ s32 unk264;
    /* 0x268 */ s32 unk268;
} UnkBss474Struct; // Size 0x26C

typedef struct {
    /* 0x00 */ UnkBss474Struct *unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 *unk0C;
} UnkFn64A3Struct; // Size unknown

void fn_1_E80(omObjData *arg0);
void fn_1_F8C(float arg0);
void fn_1_1074(void);
void fn_1_1498(s16 layer);
s32 fn_1_1520(void);
s32 fn_1_1C4C(void);
s32 fn_1_20C8(void);
void fn_1_25D0(void);
void fn_1_34B0(ModelData *model, ParticleData *particle, Mtx matrix, s32 arg3);
void fn_1_3A60(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_3A9C(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_3AD8(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_3B14(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_3B50(void);
void fn_1_3F34(void);
void fn_1_4218(void);
void fn_1_4454(void);
void fn_1_4968(void);
void fn_1_4BB0(void);
void fn_1_4E8C(void);
void fn_1_507C(void);
void fn_1_5384(void);
void fn_1_544C(void);
void fn_1_5554(void);
void fn_1_58BC(void);
void fn_1_5910(void);
s8 fn_1_5D58(s32 arg0, s32 arg1);
u8 fn_1_5E10(s32 arg0, s32 arg1);
u16 fn_1_5ED0(s32 arg0);
void fn_1_5F3C(UnkBss474Struct *arg0, s32 arg1);
void fn_1_6428(UnkBss474Struct *arg0, s32 arg1);
void fn_1_6820(UnkBss474Struct *arg0, s32 arg1, s32 arg2);
void fn_1_6A3C(void);
void fn_1_6CF4(void);
void fn_1_6DD8(UnkBss474Struct *arg0, s32 arg1);
void fn_1_6E9C(s32 arg0, s32 arg1);
void fn_1_6F48(UnkBss474Struct *arg0, s32 arg1, s32 arg2);
void fn_1_75C8(void);
void fn_1_7680(void);
void fn_1_7738(void);
void fn_1_8A80(float arg0, float arg1);
void fn_1_8DBC(void);
void fn_1_9490(void);
void fn_1_9BC0(s32 arg0);
void fn_1_A004(void);
void fn_1_A07C(void);
void fn_1_A120(s32 arg0);
void fn_1_A4B4(s32 arg0);
void fn_1_A788(s32 arg0);
void fn_1_ACB0(void);
void fn_1_AD58(void);

s16 lbl_1_bss_EA0;
s16 lbl_1_bss_E9E;
s16 lbl_1_bss_E9C;
s32 lbl_1_bss_E98;
s32 lbl_1_bss_E94;
s32 lbl_1_bss_E6C[10];
s32 lbl_1_bss_E44[10];
s32 lbl_1_bss_E40;
s32 lbl_1_bss_E3C;
s32 lbl_1_bss_E38;
s32 lbl_1_bss_E2C[3];
s32 lbl_1_bss_E28;
float lbl_1_bss_E24;
UnkBss474Struct lbl_1_bss_474[4];
UnkBss138Struct lbl_1_bss_138;
omObjData *lbl_1_bss_134;
Process *lbl_1_bss_124[4];
Vec lbl_1_bss_C4[8];
Vec lbl_1_bss_64[8];
Vec lbl_1_bss_4[8];
void *lbl_1_bss_0;

float lbl_1_data_0[][7] = { { -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, -3375.0f, 7460.0f }, { -9.5f, 0.0f, 0.0f, 0.0f, 0.0f, -510.0f, 1860.0f },
    { -5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -2870.0f, 5060.0f } };

s32 lbl_1_data_54[] = { DATA_MAKE_NUM(DATADIR_M411, 9), DATA_MAKE_NUM(DATADIR_M411, 11), DATA_MAKE_NUM(DATADIR_M411, 10) };

char *lbl_1_data_6C[] = { "puzzle00", "puzzle00", "puzzle00" };

char *lbl_1_data_1C8[][10] = { { "puzzle_B1-p01", "puzzle_B1-p02", "puzzle_B1-p03", "puzzle_B1-p04", "puzzle_B1-p05", "puzzle_B1-p06",
                                   "puzzle_B1-p07", "puzzle_B1-p08" },
    { "puzzle_B2-p01", "puzzle_B2-p02", "puzzle_B2-p03", "puzzle_B2-p04", "puzzle_B2-p05", "puzzle_B2-p06", "puzzle_B2-p07", "puzzle_B2-p08" },
    { "puzzle_B3-p01", "puzzle_B3-p02", "puzzle_B3-p03", "puzzle_B3-p04", "puzzle_B3-p05", "puzzle_B3-p06", "puzzle_B3-p07", "puzzle_B3-p08" } };

s32 lbl_1_data_240[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

s32 lbl_1_data_260[8] = { DATA_MAKE_NUM(DATADIR_MARIOMDL1, 0), DATA_MAKE_NUM(DATADIR_LUIGIMDL1, 0), DATA_MAKE_NUM(DATADIR_PEACHMDL1, 0),
    DATA_MAKE_NUM(DATADIR_YOSHIMDL1, 0), DATA_MAKE_NUM(DATADIR_WARIOMDL1, 0), DATA_MAKE_NUM(DATADIR_DONKEYMDL1, 0),
    DATA_MAKE_NUM(DATADIR_DAISYMDL1, 0), DATA_MAKE_NUM(DATADIR_WALUIGIMDL1, 0) };

s32 lbl_1_data_280[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MARIOMOT, 1), DATA_MAKE_NUM(DATADIR_MARIOMOT, 2),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 5), DATA_MAKE_NUM(DATADIR_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MARIOMOT, 27), DATA_MAKE_NUM(DATADIR_MARIOMOT, 32),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 33), DATA_MAKE_NUM(DATADIR_MARIOMOT, 23) };

s32 lbl_1_data_2A4[8] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_PEACHMOT, 0),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0), DATA_MAKE_NUM(DATADIR_WARIOMOT, 0), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0), DATA_MAKE_NUM(DATADIR_DAISYMOT, 0),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0) };

s32 lbl_1_data_2C4[] = { DATA_MAKE_NUM(DATADIR_M411, 27), DATA_MAKE_NUM(DATADIR_M411, 28), DATA_MAKE_NUM(DATADIR_M411, 23) };

s32 lbl_1_data_2D0[] = { DATA_MAKE_NUM(DATADIR_M411, 30), DATA_MAKE_NUM(DATADIR_M411, 31), DATA_MAKE_NUM(DATADIR_M411, 32),
    DATA_MAKE_NUM(DATADIR_M411, 33), DATA_MAKE_NUM(DATADIR_M411, 34) };

void ObjectSetup(void)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f31;
    float temp_f30;
    float sp8;
    Process *temp_r3;
    s32 var_r29;
    s32 i;

    var_r29 = GWSystem.mg_type;
    lbl_1_bss_E40 = var_r29;
    if (var_r29 == -1) {
        lbl_1_bss_E40 = frandmod(3);
    }
    lbl_1_bss_E3C = frandmod(3);
    switch (lbl_1_bss_E3C) {
        case 0:
            lbl_1_bss_E38 = 8;
            break;
        case 1:
            lbl_1_bss_E38 = 8;
            break;
        default:
            lbl_1_bss_E38 = 8;
            break;
    }
    temp_r3 = omInitObjMan(50, 0x2000);
    omGameSysInit(temp_r3);
    Hu3DCameraCreate(0x1F);
    Hu3DCameraPerspectiveSet(1, 15.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraPerspectiveSet(0x1E, 15.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(2, 0.0f, 0.0f, 318.0f, 238.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(4, 322.0f, 0.0f, 318.0f, 238.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(8, 0.0f, 242.0f, 318.0f, 238.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(0x10, 322.0f, 242.0f, 318.0f, 238.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 0x140, 0xF0);
    Hu3DCameraScissorSet(2, 0, 0, 0x13E, 0xEE);
    Hu3DCameraScissorSet(4, 0x142, 0, 0x13E, 0xEE);
    Hu3DCameraScissorSet(8, 0, 0xF2, 0x13E, 0xEE);
    Hu3DCameraScissorSet(0x10, 0x142, 0xF2, 0x13E, 0xEE);
    if (lbl_1_bss_E40 == 0) {
        lbl_1_bss_134 = omAddObjEx(temp_r3, 0x7FDA, 0, 0, -1, fn_1_E80);
    }
    else {
        lbl_1_bss_134 = omAddObjEx(temp_r3, 0x7FDA, 0, 0, -1, omOutViewMulti);
    }
    lbl_1_bss_134->work[0] = 5;
    for (i = 0; i < 1; i++) {
        CRotM[i].x = lbl_1_data_0[lbl_1_bss_E40][0];
        CRotM[i].y = lbl_1_data_0[lbl_1_bss_E40][1];
        CRotM[i].z = lbl_1_data_0[lbl_1_bss_E40][2];
        CenterM[i].x = lbl_1_data_0[lbl_1_bss_E40][3];
        CenterM[i].y = lbl_1_data_0[lbl_1_bss_E40][4];
        CenterM[i].z = lbl_1_data_0[lbl_1_bss_E40][5];
        CZoomM[i] = lbl_1_data_0[lbl_1_bss_E40][6];
    }
    for (i = 1; i < lbl_1_bss_134->work[0]; i++) {
        CRotM[i].x = 0.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 0.0f;
        CenterM[i].z = 0.0f;
        CZoomM[i] = 1900.0f;
    }
    temp_f31 = CRotM[1].x;
    temp_f30 = CRotM[1].y;
    sp8 = CRotM[1].z;
    lbl_1_bss_C4[1].x = CenterM[1].x + sind(temp_f30) * cosd(temp_f31) * CZoomM[1];
    lbl_1_bss_C4[1].y = CenterM[1].y + -sind(temp_f31) * CZoomM[1];
    lbl_1_bss_C4[1].z = CenterM[1].z + cosd(temp_f30) * cosd(temp_f31) * CZoomM[1];
    lbl_1_bss_64[1].x = CenterM[1].x;
    lbl_1_bss_64[1].y = CenterM[1].y;
    lbl_1_bss_64[1].z = CenterM[1].z;
    lbl_1_bss_4[1].x = sind(temp_f30) * sind(temp_f31);
    lbl_1_bss_4[1].y = cosd(temp_f31);
    lbl_1_bss_4[1].z = cosd(temp_f30) * sind(temp_f31);
    for (i = 0; i < 1; i++) {
        lbl_1_bss_C4[i].x = 0.0f;
        lbl_1_bss_C4[i].y = 1295.0f;
        lbl_1_bss_C4[i].z = 3971.0f;
        lbl_1_bss_4[i].x = 0.0f;
        lbl_1_bss_4[i].y = 1.0f;
        lbl_1_bss_4[i].z = 0.0f;
        lbl_1_bss_64[i].x = 0.0f;
        lbl_1_bss_64[i].y = 0.0f;
        lbl_1_bss_64[i].z = -3375.0f;
    }
    for (i = 1; i < lbl_1_bss_134->work[0]; i++) {
        lbl_1_bss_C4[i].x = 0.0f;
        lbl_1_bss_C4[i].y = 0.0f;
        lbl_1_bss_C4[i].z = 1900.0f;
        lbl_1_bss_4[i].x = 0.0f;
        lbl_1_bss_4[i].y = 1.0f;
        lbl_1_bss_4[i].z = 0.0f;
        lbl_1_bss_64[i].x = 0.0f;
        lbl_1_bss_64[i].y = 0.0f;
        lbl_1_bss_64[i].z = 0.0f;
    }
    Hu3DLighInit();
    lbl_1_bss_EA0 = Hu3DGLightCreate(10000.0f, 0.0f, 10000.0f, -1.0f, 0.0f, -1.0f, 0xFF, 0xFF, 0xFF);
    Hu3DGLightPosAimSet(lbl_1_bss_EA0, 0.0f, 6796.88f, 9706.95f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(lbl_1_bss_EA0);
    sp24.x = -1800.0f;
    sp24.y = 3600.0f;
    sp24.z = 0.0f;
    sp18.x = sp18.z = 0.0f;
    sp18.y = 1.0f;
    spC.x = -100.0f;
    spC.y = 0.0f;
    spC.z = 0.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.4f);
    Hu3DShadowPosSet(&sp24, &sp18, &spC);
    Hu3DBGColorSet(0, 0, 0);
    fn_1_25D0();
    fn_1_8A80(640.0f, 480.0f);
    HuPrcChildCreate(fn_1_AD58, 0x1000, 0x2000, 0, HuPrcCurrentGet());
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
}

void fn_1_E80(omObjData *arg0)
{
    s32 i;

    for (i = 0; i < arg0->work[0]; i++) {
        Hu3DCameraPosSet(1 << i, lbl_1_bss_C4[i].x, lbl_1_bss_C4[i].y, lbl_1_bss_C4[i].z, lbl_1_bss_4[i].x, lbl_1_bss_4[i].y, lbl_1_bss_4[i].z,
            lbl_1_bss_64[i].x, lbl_1_bss_64[i].y, lbl_1_bss_64[i].z);
    }
}

void fn_1_F8C(float arg0)
{
    lbl_1_bss_E24 = arg0;
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9E, -0.01f * arg0, 0.0f, 0.0f);
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9C, -0.017f * arg0, 0.0f, 0.0f);
    HuAudFXPitchSet(lbl_1_bss_E2C[0], -8191.0f * (1.0f - arg0));
}

void fn_1_1074(void)
{
    Mtx44 sp64;
    Mtx sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    GXColor spC;
    CameraData *var_r31;

    var_r31 = &Hu3DCamera[0];
    C_MTXPerspective(sp64, var_r31->fov, var_r31->aspect, var_r31->nnear, var_r31->ffar);
    GXSetProjection(sp64, GX_PERSPECTIVE);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 640, 480);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
    spC.r = spC.g = spC.b = 0;
    spC.a = 0xFF;
    GXSetTevColor(GX_TEVREG0, spC);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    sp28.x = sp28.y = sp28.z = 0.0f;
    sp1C.x = sp1C.y = 0.0f;
    sp1C.z = -100.0f;
    sp10.x = sp10.z = 0.0f;
    sp10.y = 1.0f;
    C_MTXLookAt(sp34, &sp28, &sp10, &sp1C);
    GXLoadPosMtxImm(sp34, GX_PNMTX0);
    sp28.x = 10000.0f * -sin(var_r31->fov / 2) * 1.2f;
    sp28.y = 10000.0f * -sin(var_r31->fov / 2) * 0.8333333f;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-sp28.x, -sp28.y, -10000.0f);
    GXPosition3f32(sp28.x, -sp28.y, -10000.0f);
    GXPosition3f32(sp28.x, sp28.y, -10000.0f);
    GXPosition3f32(-sp28.x, sp28.y, -10000.0f);
    GXEnd();
}

void fn_1_1498(s16 layer)
{
    if (Hu3DCameraNo == 1) {
        GXSetTexCopySrc(0, 0, 320, 240);
        GXSetTexCopyDst(320, 240, GX_TF_RGB5A3, GX_FALSE);
        GXCopyTex(lbl_1_bss_0, GX_TRUE);
        DCFlushRange(lbl_1_bss_0, 0x25800); // TODO: sizeof?
        fn_1_1074();
    }
}

s32 fn_1_1520(void)
{
    UnkBss138Struct *var_r30;
    UnkBss138InnerStruct00 *var_r31;
    UnkBss138InnerStruct00 *temp_r28;
    Process *var_r23;
    void *var_r26;
    s16 var_r27;
    s16 var_r24;
    s16 var_r22;
    s16 var_r21;
    s32 i;
    s32 j;

    var_r30 = &lbl_1_bss_138;
    var_r26 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 15), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30->unk00 = var_r27 = Hu3DModelCreate(var_r26);
    Hu3DModelCameraSet(var_r27, 1);
    var_r30->unk04.x = var_r30->unk04.y = var_r30->unk04.z = 0.0f;
    var_r30->unk10.x = var_r30->unk10.y = var_r30->unk10.z = 0.0f;
    Hu3DModelPosSet(var_r27, var_r30->unk04.x, var_r30->unk04.y, var_r30->unk04.z);
    Hu3DModelRotSet(var_r27, var_r30->unk10.x, var_r30->unk10.y, var_r30->unk10.z);
    Hu3DModelShadowMapSet(var_r27);
    var_r26 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 16), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30->unk1C[0].unk00 = var_r27 = Hu3DModelCreate(var_r26);
    Hu3DModelCameraSet(var_r27, 1);
    Hu3DModelPosSet(var_r27, var_r30->unk04.x, var_r30->unk04.y, var_r30->unk04.z);
    Hu3DModelRotSet(var_r27, var_r30->unk10.x, var_r30->unk10.y, var_r30->unk10.z);
    var_r31 = &var_r30->unkE4[0];
    var_r26 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 17), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r31->unk00 = var_r27 = Hu3DModelCreate(var_r26);
    Hu3DModelAttrSet(var_r27, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(var_r27, 1);
    var_r26 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 18), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r31->unk0C = var_r24 = Hu3DModelCreate(var_r26);
    Hu3DModelAttrSet(var_r24, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(var_r24, 1);
    for (i = 1; i < 5; i++) {
        var_r31 = &var_r30->unkE4[i];
        var_r31->unk00 = Hu3DModelLink(var_r27);
        Hu3DModelAttrSet(var_r31->unk00, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(var_r31->unk00, 1);
        if (i == 1) {
            var_r26 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 19), MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r31->unk0C = var_r22 = Hu3DModelCreate(var_r26);
        }
        else if (i & 1) {
            var_r31->unk0C = Hu3DModelLink(var_r22);
        }
        else {
            var_r31->unk0C = Hu3DModelLink(var_r24);
        }
        Hu3DModelAttrSet(var_r31->unk0C, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(var_r31->unk0C, 1);
    }
    var_r26 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 17), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30->unk274[0].unk00 = var_r27 = Hu3DModelCreate(var_r26);
    Hu3DModelAttrSet(var_r27, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(var_r27, 1);
    for (i = 1; i < 5; i++) {
        var_r30->unk274[i].unk00 = Hu3DModelLink(var_r27);
        Hu3DModelAttrSet(var_r30->unk274[i].unk00, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(var_r30->unk274[i].unk00, 1);
    }
    var_r31 = &var_r30->unk1C[1];
    var_r26 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 20), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r31->unk00 = var_r27 = Hu3DModelCreate(var_r26);
    Hu3DModelCameraSet(var_r27, 1);
    var_r31->unk10.x = -470.0f;
    var_r31->unk10.y = 0.0f;
    var_r31->unk10.z = -930.0f;
    var_r31->unk1C.x = 0.0f;
    var_r31->unk1C.y = 90.0f;
    var_r31->unk1C.z = 0.0f;
    Hu3DModelPosSet(var_r27, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
    Hu3DModelRotSet(var_r27, var_r31->unk1C.x, var_r31->unk1C.y, var_r31->unk1C.z);
    for (i = 0; i < 3; i++) {
        var_r26 = HuDataSelHeapReadNum(lbl_1_data_2C4[i], MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r31->unk02[i] = Hu3DJointMotion(var_r27, var_r26);
    }
    Hu3DMotionSet(var_r27, var_r31->unk02[0]);
    Hu3DModelAttrSet(var_r27, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r27);
    temp_r28 = &var_r30->unk1C[2];
    temp_r28->unk00 = Hu3DModelLink(var_r27);
    Hu3DModelCameraSet(temp_r28->unk00, 1);
    Hu3DModelPosSet(temp_r28->unk00, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
    Hu3DModelRotSet(temp_r28->unk00, var_r31->unk1C.x, var_r31->unk1C.y, var_r31->unk1C.z);
    for (i = 0; i < 3; i++) {
        var_r26 = HuDataSelHeapReadNum(lbl_1_data_2C4[i], MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r28->unk02[i] = Hu3DJointMotion(var_r27, var_r26);
    }
    Hu3DModelAttrSet(temp_r28->unk00, HU3D_ATTR_CULL_FRONT);
    Hu3DModelAttrSet(temp_r28->unk00, HU3D_MOTATTR_LOOP);
    Hu3DModelScaleSet(temp_r28->unk00, 1.0f, -1.0f, 1.0f);
    for (i = 0; i < 2; i++) {
        var_r31 = &var_r30->unk1AC[i];
        var_r26 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 29), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r31->unk00 = var_r21 = Hu3DModelCreate(var_r26);
        var_r27 = var_r31->unk00;
        var_r31->unk0E = i;
        Hu3DModelCameraSet(var_r27, 1);
        for (j = 0; j < 5; j++) {
            var_r26 = HuDataSelHeapReadNum(lbl_1_data_2D0[j], MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r31->unk02[j] = Hu3DJointMotion(var_r27, var_r26);
        }
        Hu3DMotionSet(var_r27, var_r31->unk02[0]);
        Hu3DModelAttrSet(var_r27, HU3D_MOTATTR_LOOP);
        var_r31->unk10.x = 200.0f;
        var_r31->unk10.y = 0.0f;
        var_r31->unk10.z = -930.0f;
        Hu3DModelPosSet(var_r27, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
        Hu3DModelShadowSet(var_r27);
    }
    for (i = 2; i < 4; i++) {
        temp_r28 = &var_r30->unk1AC[i];
        temp_r28->unk00 = Hu3DModelLink(var_r21);
        temp_r28->unk0E = i;
        for (j = 0; j < 5; j++) {
            var_r26 = HuDataSelHeapReadNum(lbl_1_data_2D0[j], MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r28->unk02[j] = Hu3DJointMotion(temp_r28->unk00, var_r26);
        }
        Hu3DModelCameraSet(temp_r28->unk00, 1);
        Hu3DModelAttrSet(temp_r28->unk00, HU3D_ATTR_CULL_FRONT);
        Hu3DModelAttrSet(temp_r28->unk00, HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(temp_r28->unk00, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
        Hu3DModelScaleSet(temp_r28->unk00, 1.0f, -1.0f, 1.0f);
    }
    var_r23 = HuPrcChildCreate(fn_1_4BB0, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    var_r23->user_data = var_r30;
}

s32 fn_1_1C4C(void)
{
    UnkBss138Struct *var_r30;
    UnkBss138InnerStruct00 *var_r29;
    s16 var_r31;
    s16 sp8;
    s16 temp_r27;
    Process *var_r26;
    void *var_r28;

    var_r30 = &lbl_1_bss_138;
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 35), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30->unk00 = var_r31 = Hu3DModelCreate(var_r28);
    Hu3DModelCameraSet(var_r31, 1);
    var_r30->unk04.x = var_r30->unk04.y = var_r30->unk04.z = 0.0f;
    var_r30->unk10.x = var_r30->unk10.y = var_r30->unk10.z = 0.0f;
    Hu3DModelPosSet(var_r31, var_r30->unk04.x, var_r30->unk04.y, var_r30->unk04.z);
    Hu3DModelRotSet(var_r31, var_r30->unk10.x, var_r30->unk10.y, var_r30->unk10.z);
    Hu3DModelShadowMapSet(var_r31);
    var_r29 = &var_r30->unk1C[0];
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 36), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk00 = var_r31 = Hu3DModelCreate(var_r28);
    Hu3DModelCameraSet(var_r31, 1);
    Hu3DModelAttrSet(var_r31, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r31);
    var_r29 = &var_r30->unk1C[1];
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 38), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r31 = sp8 = Hu3DModelCreate(var_r28);
    var_r29->unk00 = var_r31;
    Hu3DModelCameraSet(var_r31, 1);
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 39), MEMORY_DEFAULT_NUM, HEAP_DATA);
    Hu3DMotionSet(var_r31, Hu3DJointMotion(var_r31, var_r28));
    Hu3DModelAttrSet(var_r31, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r31);
    var_r29 = &var_r30->unk1C[2];
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 38), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk00 = var_r31 = Hu3DModelCreate(var_r28);
    Hu3DModelCameraSet(var_r31, 1);
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 40), MEMORY_DEFAULT_NUM, HEAP_DATA);
    Hu3DMotionSet(var_r31, Hu3DJointMotion(var_r31, var_r28));
    Hu3DModelAttrSet(var_r31, HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(var_r31, 0.0f, 60.0f, -70.0f);
    Hu3DModelShadowSet(var_r31);
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 37), MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r27 = Hu3DModelCreate(var_r28);
    var_r29 = &var_r30->unkE4[0];
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 38), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk00 = var_r31 = Hu3DModelCreate(var_r28);
    Hu3DModelCameraSet(var_r31, 1);
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 41), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk02[0] = Hu3DJointMotion(var_r31, var_r28);
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 42), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk02[1] = Hu3DJointMotion(var_r31, var_r28);
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 45), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk02[2] = Hu3DJointMotion(var_r31, var_r28);
    Hu3DMotionSet(var_r31, var_r29->unk02[0]);
    Hu3DModelAttrSet(var_r31, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31, HU3D_MOTATTR_LOOP);
    Hu3DModelHookSet(var_r31, "itemhook_r", temp_r27);
    Hu3DModelShadowSet(var_r31);
    var_r29 = &var_r30->unkE4[1];
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 38), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk00 = var_r31 = Hu3DModelCreate(var_r28);
    Hu3DModelCameraSet(var_r31, 1);
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 43), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk02[0] = Hu3DJointMotion(var_r31, var_r28);
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 44), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk02[1] = Hu3DJointMotion(var_r31, var_r28);
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 46), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29->unk02[2] = Hu3DJointMotion(var_r31, var_r28);
    Hu3DMotionSet(var_r31, var_r29->unk02[0]);
    Hu3DModelAttrSet(var_r31, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31, HU3D_MOTATTR_LOOP);
    Hu3DModelHookSet(var_r31, "itemhook_l", temp_r27);
    Hu3DModelShadowSet(var_r31);
    var_r26 = HuPrcChildCreate(fn_1_5384, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    var_r26->user_data = var_r30;
}

s32 fn_1_20C8(void)
{
    UnkBss138Struct *var_r31;
    UnkBss138InnerStruct00 *temp_r29;
    Process *var_r26;
    void *var_r28;
    s16 var_r30;
    s16 var_r25;
    s32 i;

    var_r31 = &lbl_1_bss_138;
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 47), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r28);
    var_r31->unk00 = var_r30;
    Hu3DModelCameraSet(var_r30, 1);
    var_r31->unk04.x = var_r31->unk04.y = var_r31->unk04.z = 0.0f;
    var_r31->unk10.x = var_r31->unk10.y = var_r31->unk10.z = 0.0f;
    Hu3DModelPosSet(var_r30, var_r31->unk04.x, var_r31->unk04.y, var_r31->unk04.z);
    Hu3DModelRotSet(var_r30, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
    Hu3DModelShadowMapSet(var_r30);
    lbl_1_bss_E9E = Hu3DTexScrollCreate(var_r30, "jimen01");
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9E, -0.01f, 0.0f, 0.0f);
    lbl_1_bss_E9C = Hu3DTexScrollCreate(var_r30, "kusa01");
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9C, -0.017f, 0.0f, 0.0f);
    lbl_1_bss_E24 = 1.0f;
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9E, -0.01f, 0.0f, 0.0f);
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9C, -0.017f, 0.0f, 0.0f);
    HuAudFXPitchSet(lbl_1_bss_E2C[0], 0);
    temp_r29 = &var_r31->unk1C[0];
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 48), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r28);
    temp_r29->unk00 = var_r30;
    Hu3DModelCameraSet(var_r30, 1);
    Hu3DModelPosSet(var_r30, var_r31->unk04.x, var_r31->unk04.y, var_r31->unk04.z);
    Hu3DModelRotSet(var_r30, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(var_r30, Hu3DMotionMaxTimeGet(var_r30) / 4);
    temp_r29 = &var_r31->unk1C[1];
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 49), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r28);
    temp_r29->unk00 = var_r30;
    Hu3DModelCameraSet(var_r30, 1);
    Hu3DModelPosSet(var_r30, var_r31->unk04.x, var_r31->unk04.y, var_r31->unk04.z);
    Hu3DModelRotSet(var_r30, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(var_r30, Hu3DMotionMaxTimeGet(var_r30) / 4);
    for (i = 0; i < 3; i++) {
        temp_r29 = &var_r31->unk1C[i + 2];
        if (i == 0) {
            var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 50), MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r29->unk00 = var_r30 = var_r25 = Hu3DModelCreate(var_r28);
        }
        else {
            temp_r29->unk00 = Hu3DModelLink(var_r25);
        }
        var_r30 = temp_r29->unk00;
        Hu3DModelCameraSet(var_r30, 1);
        Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_SHAPE_LOOP);
    }
    temp_r29 = &var_r31->unkE4[0];
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 51), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r28);
    temp_r29->unk00 = var_r30;
    Hu3DModelCameraSet(var_r30, 1);
    for (i = 0; i < 5; i++) {
        var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 52 + i), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r29->unk02[i] = Hu3DJointMotion(var_r30, var_r28);
    }
    temp_r29->unk10.x = temp_r29->unk10.y = temp_r29->unk10.z = 0.0f;
    Hu3DModelPosSet(var_r30, temp_r29->unk10.x, temp_r29->unk10.y, temp_r29->unk10.z);
    Hu3DModelRotSet(var_r30, 0.0f, -90.0f, 0.0f);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r30);
    Hu3DMotionSet(var_r30, temp_r29->unk02[0]);
    temp_r29 = &var_r31->unk1AC[0];
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 57), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r28);
    temp_r29->unk00 = var_r30;
    Hu3DModelCameraSet(var_r30, 1);
    Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    var_r26 = HuPrcChildCreate(fn_1_5910, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    var_r26->user_data = var_r31;
}

ParticleHook lbl_1_data_30C[] = { fn_1_3A60, fn_1_3A9C, fn_1_3AD8, fn_1_3B14 };

void fn_1_25D0(void)
{
    u32 temp_r24;
    UnkBss474Struct *temp_r31;
    void *var_r28;
    UnkBss474InnerStructE4 *temp_r27;
    UnkBss474DoublyInnerStruct6C *temp_r26;
    AnimData *var_r21;
    AnimData *var_r20;
    Process *var_r23;
    s16 temp_r25;
    s32 var_r22;
    s32 i;
    s32 j;

    HuAudSndGrpSet(0x24);
    temp_r24 = GXGetTexBufferSize(320, 240, GX_TF_RGB5A3, GX_FALSE, 0);
    if (!lbl_1_bss_0) {
        lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_DATA, temp_r24, MEMORY_DEFAULT_NUM);
    }
    Hu3DLayerHookSet(0, fn_1_1498);
    switch (lbl_1_bss_E40) {
        case 0:
            fn_1_1520();
            break;
        case 1:
            fn_1_1C4C();
            break;
        default:
            fn_1_20C8();
            break;
    }
    for (i = 0; i < 4; i++) {
        temp_r31 = &lbl_1_bss_474[i];
        temp_r31->unk34 = i;
        temp_r31->unk3C = GWPlayerCfg[i].pad_idx;
        temp_r31->unk38 = i + 1;
        temp_r31->unk44 = 0;
        temp_r31->unk264 = -1;
        var_r28 = HuDataSelHeapReadNum(lbl_1_data_54[lbl_1_bss_E3C], MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk00 = Hu3DModelCreate(var_r28);
        temp_r31->unk24C = HuSprAnimMake(320, 240, 2);
        temp_r31->unk24C->bmp->data = lbl_1_bss_0;
        Hu3DAnimCreate(temp_r31->unk24C, temp_r31->unk00, lbl_1_data_6C[lbl_1_bss_E3C]);
        Hu3DModelCameraSet(temp_r31->unk00, 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r31->unk00, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31->unk00, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrSet(temp_r31->unk00, HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
        var_r28 = HuDataSelHeapReadNum(lbl_1_data_54[lbl_1_bss_E3C], MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk04 = Hu3DModelCreate(var_r28);
        var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 14), MEMORY_DEFAULT_NUM, HEAP_DATA);
        Hu3DAnimCreate(var_r28, temp_r31->unk04, lbl_1_data_6C[lbl_1_bss_E3C]);
        Hu3DModelCameraSet(temp_r31->unk04, 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r31->unk04, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31->unk04, 0.0f, 0.0f, 0.0f);
        var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 12), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk02 = Hu3DModelCreate(var_r28);
        temp_r31->unk250 = HuSprAnimMake(320, 240, 2);
        temp_r31->unk250->bmp->data = lbl_1_bss_0;
        Hu3DAnimCreate(temp_r31->unk250, temp_r31->unk02, lbl_1_data_6C[lbl_1_bss_E3C]);
        Hu3DModelCameraSet(temp_r31->unk02, 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r31->unk02, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31->unk02, 0.0f, 0.0f, 0.0f);
        var_r28 = HuDataSelHeapReadNum(lbl_1_data_54[lbl_1_bss_E3C], MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk06 = Hu3DModelCreate(var_r28);
        Hu3DModelCameraSet(temp_r31->unk06, 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r31->unk06, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31->unk06, 0.0f, 0.0f, 0.0f);
        Hu3DModelTPLvlSet(temp_r31->unk06, 128.0f);
        Hu3DModelAttrSet(temp_r31->unk06, HU3D_ATTR_NOCULL);
        for (j = 0; j < lbl_1_bss_E38; j++) {
            temp_r31->unk6C[j] = (void *)Hu3DModelObjPtrGet(temp_r31->unk00, lbl_1_data_1C8[lbl_1_bss_E3C][j]);
            if (!temp_r31->unk6C[j]) {
                OSReport("objname %s\n", lbl_1_data_1C8[lbl_1_bss_E3C][j]);
                OSPanic("m411.c", 908, "ObjPtr");
            }
            temp_r27 = &temp_r31->unkE4[j];
            temp_r26 = &temp_r31->unk6C[j]->unk1C;
            temp_r27->unk00 = temp_r26->unk00;
            temp_r27->unk04 = temp_r26->unk04;
            temp_r27->unk08 = temp_r26->unk08;
            temp_r27->unk0C = temp_r26->unk0C;
            temp_r27->unk10 = temp_r26->unk10;
            temp_r27->unk14 = temp_r26->unk14;
            temp_r27->unk18 = temp_r26->unk18;
            temp_r27->unk1C = temp_r26->unk1C;
            temp_r27->unk20 = temp_r26->unk20;
            temp_r31->unk94[j] = (void *)Hu3DModelObjPtrGet(temp_r31->unk06, lbl_1_data_1C8[lbl_1_bss_E3C][j]);
            if (!temp_r31->unk94[j]) {
                OSReport("objname %s\n", lbl_1_data_1C8[lbl_1_bss_E3C][j]);
                OSPanic("m411.c", 919, "ObjPtr");
            }
            temp_r31->unkBC[j] = (void *)Hu3DModelObjPtrGet(temp_r31->unk04, lbl_1_data_1C8[lbl_1_bss_E3C][j]);
            if (!temp_r31->unkBC[j]) {
                OSReport("objname %s\n", lbl_1_data_1C8[lbl_1_bss_E3C][j]);
                OSPanic("m411.c", 925, "ObjPtr");
            }
        }
        var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 0), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk0A = Hu3DModelCreate(var_r28);
        Hu3DModelCameraSet(temp_r31->unk0A, 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r31->unk0A, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31->unk0A, 0.0f, 0.0f, 0.0f);
        var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M411, 1 + GWPlayerCfg[i].character), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r25 = Hu3DModelCreate(var_r28);
        Hu3DModelCameraSet(temp_r25, 1 << temp_r31->unk38);
        var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 56 + GWPlayerCfg[i].character), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r21 = HuSprAnimRead(var_r28);
        temp_r25 = HuSprCreate(var_r21, 0x4000, 0);
        temp_r31->unk0C = HuSprGrpCreate(1);
        HuSprGrpMemberSet(temp_r31->unk0C, 0, temp_r25);
        HuSprAttrSet(temp_r31->unk0C, 0, 7);
        temp_r31->unk08 = CharModelCreate(lbl_1_data_240[GWPlayerCfg[i].character], 2);
        Hu3DModelCameraSet(temp_r31->unk08, 1 << temp_r31->unk38);
        CharModelStepTypeSet(lbl_1_data_240[GWPlayerCfg[i].character], 1);
        CharModelLayerSetAll(2);
        temp_r31->unk48 = 0.0f;
        switch (lbl_1_data_240[GWPlayerCfg[i].character]) {
            case 7:
                temp_r31->unk4C = -400.0f;
                break;
            case 5:
                temp_r31->unk4C = -330.0f;
                break;
            case 2:
            case 6:
                temp_r31->unk4C = -375.0f;
                break;
            default:
                temp_r31->unk4C = -350.0f;
                break;
        }
        temp_r31->unk50 = 500.0f;
        temp_r31->unk54 = temp_r31->unk5C = 0.0f;
        temp_r31->unk58 = 180.0f;
        Hu3DModelPosSet(temp_r31->unk08, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        Hu3DModelRotSet(temp_r31->unk08, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
        Hu3DModelAttrSet(temp_r31->unk08, HU3D_ATTR_DISPOFF);
        for (j = 0; j < 9; j++) {
            temp_r31->unk0E[j] = CharModelMotionCreate(lbl_1_data_240[GWPlayerCfg[i].character], lbl_1_data_280[j]);
        }
        CharModelMotionSet(lbl_1_data_240[GWPlayerCfg[i].character], temp_r31->unk0E[0]);
        Hu3DModelAttrSet(temp_r31->unk08, HU3D_MOTATTR_LOOP);
        if (lbl_1_bss_E40 == 0) {
            var_r28 = HuDataSelHeapReadNum(lbl_1_data_260[GWPlayerCfg[i].character], MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r31->unk20 = Hu3DModelCreate(var_r28);
            Hu3DModelAttrSet(temp_r31->unk20, HU3D_ATTR_DISPOFF | HU3D_ATTR_CULL_FRONT);
            Hu3DModelCameraSet(temp_r31->unk20, 1);
            for (j = 0; j < 9; j++) {
                var_r28 = HuDataSelHeapReadNum((u8)lbl_1_data_280[j] + lbl_1_data_2A4[GWPlayerCfg[i].character], MEMORY_DEFAULT_NUM, HEAP_DATA);
                temp_r31->unk22[j] = Hu3DJointMotion(temp_r31->unk20, var_r28);
            }
            Hu3DMotionSet(temp_r31->unk20, temp_r31->unk22[3]);
            Hu3DModelPosSet(temp_r31->unk20, temp_r31->unk48, 0.0f, temp_r31->unk50);
            Hu3DModelRotSet(temp_r31->unk20, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
            Hu3DModelScaleSet(temp_r31->unk20, 1.0f, -1.0f, 1.0f);
        }
        CharModelMotionDataClose(lbl_1_data_240[GWPlayerCfg[i].character]);
        var_r20 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M411, 13), MEMORY_DEFAULT_NUM));
        temp_r25 = Hu3DParticleCreate(var_r20, 300);
        Hu3DModelPosSet(temp_r25, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(temp_r25, 1.0f, 1.0f, 1.0f);
        Hu3DModelLayerSet(temp_r25, 1);
        Hu3DParticleColSet(temp_r25, 0xFF, 0xFF, 0);
        Hu3DParticleScaleSet(temp_r25, 0.0f);
        Hu3DParticleHookSet(temp_r25, lbl_1_data_30C[temp_r31->unk34]);
        Hu3DModelCameraSet(temp_r25, 1 << temp_r31->unk38);
        var_r23 = HuPrcChildCreate(fn_1_7738, 0x2000, 0x3000, 0, HuPrcCurrentGet());
        var_r23->user_data = temp_r31;
        lbl_1_bss_124[i] = var_r23;
    }
    for (i = 0; i < lbl_1_bss_E38; i++) {
        lbl_1_bss_E6C[i] = i;
        lbl_1_bss_E44[i] = frandmod(4);
    }
    for (i = 0; i < 50; i++) {
        j = frandmod(lbl_1_bss_E38);
        var_r22 = frandmod(lbl_1_bss_E38);
        temp_r24 = lbl_1_bss_E6C[j];
        lbl_1_bss_E6C[j] = lbl_1_bss_E6C[var_r22];
        lbl_1_bss_E6C[var_r22] = temp_r24;
    }
    HuPrcChildCreate(fn_1_ACB0, 0x1000, 0x1000, 0, HuPrcCurrentGet());
}

void fn_1_34B0(ModelData *model, ParticleData *particle, Mtx matrix, s32 arg3)
{
    float var_f30;
    float temp_f28;
    float var_f31;
    float temp_f29;
    HsfanimStruct01 *var_r31;
    UnkBss474Struct *temp_r28;
    s16 i;
    s16 j;
    s16 k;
    s32 var_r25;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (k = 0; k < particle->unk_30; k++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;
    temp_r28 = &lbl_1_bss_474[arg3];
    if (temp_r28->unk44 == 1) {
        for (i = 0; i < 4; i++) {
            temp_f28 = 1.0f;
            for (j = 0, var_f30 = 0.0f; j < 24; j++, var_f30 += 15.0f) {
                for (k = 0; k < particle->unk_30; k++, var_r31++) {
                    if (var_r31->unk14.x == 0.0f) {
                        break;
                    }
                }
                if (k == particle->unk_30) {
                    break;
                }
                var_f31 = var_f30;
                temp_f29 = temp_f28 + 5.0f * frandf();
                var_r31->unk34.x = temp_r28->unk64 + 10.0f * i * sind(var_f31);
                var_r31->unk34.y = temp_r28->unk68 + 10.0f * i * cosd(var_f31);
                var_r31->unk34.z = 50.0f;
                var_r31->unk08.x = temp_f29 * sind(var_f31);
                var_r31->unk08.y = temp_f29 * cosd(var_f31);
                var_r31->unk08.z = 0.0f;
                var_r31->unk14.x = 30.0f;
                var_r31->unk14.y = 360.0f * frandf();
                var_r31->unk14.z = 225.0f;
                var_r31->unk2C = 40.0f + 10.0f * frandf();
                var_r31->unk40.r = frandmod(20) + 235;
                var_r31->unk40.g = frandmod(50) + 205;
                var_r31->unk40.b = frandmod(50);
                var_r31->unk40.a = 0xFF;
            }
        }
        temp_r28->unk44++;
        DCStoreRangeNoSync(particle->unk_48, particle->unk_30 * sizeof(*particle->unk_48));
    }
    var_r31 = particle->unk_48;
    for (k = 0; k < particle->unk_30; k++, var_r31++) {
        if (var_r31->unk14.x == 0.0f) {
            continue;
        }
        VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
        var_r31->unk08.x *= 0.95f;
        var_r31->unk08.y *= 0.95f;
        var_r31->unk14.y += 20.0f;
        if (var_r31->unk14.y >= 180.0f && var_r31->unk14.y < 200.0f) {
            var_r31->unk14.z *= 0.6f;
        }
        if (var_r31->unk14.y >= 360.0f && var_r31->unk14.y < 380.0f) {
            var_r31->unk14.z *= 0.6f;
        }
        if (var_r31->unk14.y >= 360.0f) {
            var_r31->unk14.y -= 360.0f;
        }
        var_r25 = var_r31->unk14.z + 30.0 * sind(var_r31->unk14.y);
        if (var_r25 < 0) {
            var_r25 = 0;
            var_r31->unk14.x = 0.0f;
        }
        var_r31->unk40.a = var_r25;
        if (var_r31->unk14.x == 0.0f) {
            var_r31->unk2C = 0.0f;
        }
    }
    PPCSync();
}

void fn_1_3A60(ModelData *model, ParticleData *particle, Mtx matrix)
{
    fn_1_34B0(model, particle, matrix, 0);
}

void fn_1_3A9C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    fn_1_34B0(model, particle, matrix, 1);
}

void fn_1_3AD8(ModelData *model, ParticleData *particle, Mtx matrix)
{
    fn_1_34B0(model, particle, matrix, 2);
}

void fn_1_3B14(ModelData *model, ParticleData *particle, Mtx matrix)
{
    fn_1_34B0(model, particle, matrix, 3);
}

void fn_1_3B50(void)
{
    float temp_f31;
    float temp_f30;
    UnkBss138InnerStruct00 *temp_r31;
    s16 temp_r30;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r30 = temp_r31->unk0C;
    Hu3DModelRotSet(temp_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(temp_r30, HU3D_ATTR_DISPOFF);
    temp_f31 = -15.0f;
    temp_f30 = -15.0f;
    Hu3DModelPosSet(temp_r30, temp_r31->unk10.x + 2.0 * sind(temp_r31->unk1C.y) + temp_f31, temp_r31->unk10.y + temp_f30,
        temp_r31->unk10.z + 2.0 * cosd(temp_r31->unk1C.y));
    HuPrcVSleep();
    Hu3DModelAttrSet(temp_r30, HU3D_ATTR_DISPOFF);
    HuPrcSleep(4);
    Hu3DModelAttrReset(temp_r30, HU3D_ATTR_DISPOFF);
    temp_f31 = 15.0f;
    temp_f30 = -15.0f;
    Hu3DModelPosSet(temp_r30, temp_r31->unk10.x + 2.0 * sind(temp_r31->unk1C.y) + temp_f31, temp_r31->unk10.y + temp_f30,
        temp_r31->unk10.z + 2.0 * cosd(temp_r31->unk1C.y));
    HuPrcVSleep();
    Hu3DModelAttrSet(temp_r30, HU3D_ATTR_DISPOFF);
    HuPrcSleep(4);
    Hu3DModelAttrReset(temp_r30, HU3D_ATTR_DISPOFF);
    temp_f31 = -15.0f;
    temp_f30 = 15.0f;
    Hu3DModelPosSet(temp_r30, temp_r31->unk10.x + 2.0 * sind(temp_r31->unk1C.y) + temp_f31, temp_r31->unk10.y + temp_f30,
        temp_r31->unk10.z + 2.0 * cosd(temp_r31->unk1C.y));
    HuPrcVSleep();
    Hu3DModelAttrSet(temp_r30, HU3D_ATTR_DISPOFF);
    HuPrcSleep(4);
    Hu3DModelAttrReset(temp_r30, HU3D_ATTR_DISPOFF);
    temp_f31 = 15.0f;
    temp_f30 = 15.0f;
    Hu3DModelPosSet(temp_r30, temp_r31->unk10.x + 2.0 * sind(temp_r31->unk1C.y) + temp_f31, temp_r31->unk10.y + temp_f30,
        temp_r31->unk10.z + 2.0 * cosd(temp_r31->unk1C.y));
    HuPrcVSleep();
    Hu3DModelAttrSet(temp_r30, HU3D_ATTR_DISPOFF);
    HuPrcSleep(4);
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_3F34(void)
{
    float temp_f28;
    float var_f31;
    float temp_f30;
    float var_f29;
    UnkBss138InnerStruct00 *temp_r31;
    Process *var_r30;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk10.x = -500.0f + 1000.0f * frandf();
    temp_r31->unk10.y = 1200.0f;
    temp_r31->unk10.z = 0.0f;
    temp_r31->unk1C.x = temp_r31->unk1C.y = temp_r31->unk1C.z = 0.0f;
    Hu3DModelAttrReset(temp_r31->unk00, HU3D_ATTR_DISPOFF);
    temp_f28 = temp_r31->unk10.x;
    var_f31 = 0.0f;
    temp_f30 = 1.0f + 2.0f * frandf();
    Hu3DModelScaleSet(temp_r31->unk00, temp_f30, temp_f30, temp_f30);
    Hu3DModelScaleSet(temp_r31->unk0C, temp_f30, temp_f30, temp_f30);
    var_f29 = 10.0f + 20.0f * frandf();
    while (TRUE) {
        temp_r31->unk10.x = temp_f28 + var_f29 * sind(var_f31);
        var_f31 += 10.0f;
        if (var_f31 == 180.0f || var_f31 == 360.0f) {
            var_f29 = 10.0f + 20.0f * frandf();
        }
        if (var_f31 > 360.0f) {
            var_f31 -= 360.0f;
        }
        temp_r31->unk10.y -= 3.0f;
        if (temp_r31->unk10.y < 0.0f) {
            break;
        }
        temp_r31->unk1C.y += 10.0f;
        if (temp_r31->unk1C.y > 360.0f) {
            temp_r31->unk1C.y -= 360.0f;
        }
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        if (temp_r31->unk1C.y == 350.0f) {
            var_r30 = HuPrcChildCreate(fn_1_3B50, 0x2000, 0x2000, 0, HuPrcCurrentGet());
            var_r30->user_data = temp_r31;
        }
        HuPrcVSleep();
    }
    HuPrcCurrentGet()->user_data_u32 = 10000;
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_4218(void)
{
    float temp_f28;
    float var_f29;
    float temp_f26;
    float temp_f25;
    float var_f31;
    float temp_f24;
    float var_f30;
    float temp_f23;
    float temp_f27;
    float temp_f22;
    UnkBss138InnerStruct00 *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_f28 = -600.0f + 1200.0f * frandf();
    var_f29 = 1200.0f;
    temp_f26 = -2900.0f;
    temp_f25 = var_f31 = temp_f24 = 0.0f;
    Hu3DModelAttrReset(temp_r31->unk00, HU3D_ATTR_DISPOFF);
    temp_f23 = temp_f28;
    var_f30 = 0.0f;
    temp_f27 = 1.0f + 2.0f * frandf();
    Hu3DModelScaleSet(temp_r31->unk00, temp_f27, temp_f27, temp_f27);
    temp_f22 = 10.0f + 20.0f * frandf();
    while (TRUE) {
        temp_f28 = temp_f23 + temp_f22 * sind(var_f30);
        var_f30 += 10.0f;
        if (var_f30 > 360.0f) {
            var_f30 -= 360.0f;
        }
        var_f29 -= 3.0f;
        if (var_f29 < 0.0f) {
            break;
        }
        var_f31 += 10.0f;
        if (var_f31 > 360.0f) {
            var_f31 -= 360.0f;
        }
        Hu3DModelPosSet(temp_r31->unk00, temp_f28, var_f29, temp_f26);
        Hu3DModelRotSet(temp_r31->unk00, temp_f25, var_f31, temp_f24);
        HuPrcVSleep();
    }
    HuPrcCurrentGet()->user_data_u32 = 10000;
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_4454(void)
{
    float temp_f30;
    float sp8;
    float temp_f29;
    float var_f31;
    UnkBss138InnerStruct00 *temp_r31;
    UnkBss138InnerStruct00 *var_r30;
    s32 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    if (temp_r31->unk0E == 0) {
        var_f31 = 0.0f;
        var_r30 = &lbl_1_bss_138.unk1AC[2];
    }
    else {
        var_f31 = 180.0f;
        var_r30 = &lbl_1_bss_138.unk1AC[3];
    }
    temp_f30 = temp_r31->unk10.x;
    sp8 = temp_r31->unk10.y;
    temp_f29 = temp_r31->unk10.z;
    while (TRUE) {
        temp_r31->unk10.x = temp_f30 + 200.0 * sind(var_f31);
        temp_r31->unk10.z = temp_f29 + 200.0 * cosd(var_f31);
        var_f31 += 1.5f;
        if (!HuPrcCurrentGet()->user_data && ((var_f31 > 90.0f && var_f31 < 100.0f) || (var_f31 > 270.0f && var_f31 < 280.0f))) {
            break;
        }
        if (var_f31 > 360.0f) {
            var_f31 -= 360.0f;
        }
        temp_r31->unk1C.y = var_f31 + 90.0f;
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        Hu3DModelPosSet(var_r30->unk00, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        Hu3DModelRotSet(var_r30->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        HuPrcVSleep();
    }
    while (TRUE) {
        if (temp_r31->unk1C.y > 180.0f) {
            temp_r31->unk1C.y += 10.0f;
            if (temp_r31->unk1C.y >= 360.0f) {
                break;
            }
        }
        if (temp_r31->unk1C.y <= 180.0f) {
            temp_r31->unk1C.y -= 10.0f;
            if (temp_r31->unk1C.y <= 0.0f) {
                break;
            }
        }
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        Hu3DModelRotSet(var_r30->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk1C.x, 0.0f, temp_r31->unk1C.z);
    Hu3DModelRotSet(var_r30->unk00, temp_r31->unk1C.x, 0.0f, temp_r31->unk1C.z);
    Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk02[1], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    Hu3DMotionShiftSet(var_r30->unk00, var_r30->unk02[1], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    for (i = 0; i < 120; i++) {
        if (var_f31 > 180.0f) {
            temp_r31->unk10.x += 1.6666666f;
            temp_r31->unk10.z += 0.8333333f;
        }
        else {
            temp_r31->unk10.z += 0.8333333f;
        }
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        Hu3DModelPosSet(var_r30->unk00, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        HuPrcVSleep();
    }
    Hu3DMotionSet(temp_r31->unk00, temp_r31->unk02[2]);
    Hu3DModelAttrReset(temp_r31->unk00, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(var_r30->unk00, var_r30->unk02[2]);
    Hu3DModelAttrReset(var_r30->unk00, HU3D_MOTATTR_LOOP);
    while (Hu3DMotionEndCheck(temp_r31->unk00) == 0) {
        HuPrcVSleep();
    }
    if (temp_r31->unk0E == 0) {
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk02[3], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        Hu3DMotionShiftSet(var_r30->unk00, var_r30->unk02[3], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    }
    else {
        Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk02[4], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        Hu3DMotionShiftSet(var_r30->unk00, var_r30->unk02[4], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_4968(void)
{
    UnkBss138InnerStruct00 *var_r31;
    UnkBss138InnerStruct00 *var_r30;
    s32 i;

    var_r31 = &lbl_1_bss_138.unk1C[1];
    var_r30 = &lbl_1_bss_138.unk1C[2];
    for (i = 0; i < 30; i++) {
        var_r31->unk1C.y -= 2.6666667f;
        Hu3DModelRotSet(var_r31->unk00, var_r31->unk1C.x, var_r31->unk1C.y, var_r31->unk1C.z);
        Hu3DModelRotSet(var_r30->unk00, var_r31->unk1C.x, var_r31->unk1C.y, var_r31->unk1C.z);
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[2], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    Hu3DMotionShiftSet(var_r30->unk00, var_r30->unk02[2], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 60; i++) {
        var_r31->unk10.x += 2.5f;
        var_r31->unk10.z += 3.3333333f;
        Hu3DModelPosSet(var_r31->unk00, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
        Hu3DModelPosSet(var_r30->unk00, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
        HuPrcVSleep();
    }
    for (i = 0; i < 5; i++) {
        var_r31->unk1C.y -= 2.0f;
        Hu3DModelRotSet(var_r31->unk00, var_r31->unk1C.x, var_r31->unk1C.y, var_r31->unk1C.z);
        Hu3DModelRotSet(var_r30->unk00, var_r31->unk1C.x, var_r31->unk1C.y, var_r31->unk1C.z);
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    Hu3DMotionShiftSet(var_r30->unk00, var_r30->unk02[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    while (TRUE) {
        if (lbl_1_bss_E98 >= 5) {
            break;
        }
        if (Hu3DMotionTimeGet(var_r31->unk00) == 0.0f) {
            HuAudFXPlay(0x576);
        }
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_4BB0(void)
{
    UnkBss138Struct *temp_r28;
    Process *sp24[5];
    Process *sp10[5];
    Process *sp8[2];
    s32 var_r30;
    s32 var_r29;
    s32 var_r27;
    s32 i;

    temp_r28 = HuPrcCurrentGet()->user_data;
    for (i = 0; i < 5; i++) {
        sp24[i] = NULL;
        sp10[i] = NULL;
    }
    for (i = 0; i < 2; i++) {
        sp8[i] = HuPrcChildCreate(fn_1_4454, 0x2000, 0x2000, 0, HuPrcCurrentGet());
        sp8[i]->user_data = &temp_r28->unk1AC[i];
    }
    var_r30 = var_r29 = 0;
    var_r27 = 0;
    while (TRUE) {
        if (var_r30 == 0) {
            for (i = 0; i < 5; i++) {
                if (!sp24[i]) {
                    sp24[i] = HuPrcChildCreate(fn_1_3F34, 0x2000, 0x2000, 0, HuPrcCurrentGet());
                    sp24[i]->user_data = &temp_r28->unkE4[i];
                    var_r30 = frandmod(20) + 20;
                    break;
                }
            }
        }
        else {
            var_r30--;
        }
        if (var_r29 == 0) {
            for (i = 0; i < 5; i++) {
                if (!sp10[i]) {
                    sp10[i] = HuPrcChildCreate(fn_1_4218, 0x2000, 0x2000, 0, HuPrcCurrentGet());
                    sp10[i]->user_data = &temp_r28->unk274[i];
                    var_r29 = frandmod(20) + 20;
                    break;
                }
            }
        }
        else {
            var_r29--;
        }
        if (lbl_1_bss_E98 == 4 && var_r27 == 0) {
            var_r27 = 1;
            HuPrcChildCreate(fn_1_4968, 0x2000, 0x2000, 0, HuPrcCurrentGet());
            for (i = 0; i < 2; i++) {
                sp8[i]->user_data = NULL;
            }
        }
        HuPrcVSleep();
        for (i = 0; i < 5; i++) {
            if (sp24[i] && sp24[i]->user_data == (void *)10000) {
                sp24[i] = NULL;
            }
            if (sp10[i] && sp10[i]->user_data == (void *)10000) {
                sp10[i] = NULL;
            }
        }
    }
}

void fn_1_4E8C(void)
{
    float var_f31;
    UnkBss138InnerStruct00 *temp_r31;
    s32 temp_r29;
    s32 i;

    temp_r29 = HuPrcCurrentGet()->user_data_u32;
    temp_r31 = &lbl_1_bss_138.unkE4[temp_r29 - 1];
    temp_r31->unk10.y = 0.0f;
    temp_r31->unk10.z = 200.0f;
    if (temp_r29 < 2) {
        temp_r31->unk10.x = 500.0f;
        temp_r31->unk1C.x = temp_r31->unk1C.z = 0.0f;
        temp_r31->unk1C.y = -90.0f;
        var_f31 = (120.0f - temp_r31->unk10.x) / 60.0f;
    }
    else {
        temp_r31->unk10.x = -500.0f;
        temp_r31->unk1C.x = temp_r31->unk1C.z = 0.0f;
        temp_r31->unk1C.y = 90.0f;
        var_f31 = (-120.0f - temp_r31->unk10.x) / 60.0f;
    }
    Hu3DModelAttrReset(temp_r31->unk00, HU3D_ATTR_DISPOFF);
    Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
    for (i = 0; i < 60; i++) {
        temp_r31->unk10.x += var_f31;
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk02[1], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    while (!Hu3DMotionEndCheck(temp_r31->unk00)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(temp_r31->unk00, temp_r31->unk02[2], 0.0f, 2.0f, HU3D_MOTATTR_LOOP);
    HuAudFXPlay(0x36);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_507C(void)
{
    float temp_f31;
    s32 var_r28;
    s32 var_r29;
    UnkBss138Struct *temp_r27;
    UnkBss138InnerStruct00 *temp_r31;
    UnkBss138InnerStruct00 *temp_r30;

    temp_r27 = HuPrcCurrentGet()->user_data;
    temp_r31 = &temp_r27->unk1C[0];
    temp_r30 = &temp_r27->unk1C[1];
    temp_f31 = 2.0f;
    var_r28 = 0;
    lbl_1_bss_E2C[0] = -1;
    while (TRUE) {
        if (lbl_1_bss_E98 == 4) {
            break;
        }
        temp_r31->unk10.x = 500.0f;
        temp_r31->unk10.y = 0.0f;
        temp_r31->unk10.z = 100.0f;
        temp_r31->unk1C.x = temp_r31->unk1C.z = 0.0f;
        temp_r31->unk1C.y = -90.0f;
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        Hu3DModelRotSet(temp_r30->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        var_r29 = 0;
        while (TRUE) {
            temp_r31->unk10.x -= temp_f31;
            if (var_r29 == 0 && temp_r31->unk10.x < 400.0f) {
                var_r29 = 1;
                if (lbl_1_bss_E2C[0] != -1) {
                    HuAudFXStop(lbl_1_bss_E2C[0]);
                }
                lbl_1_bss_E2C[0] = HuAudFXPlayVol(0x56E, 0);
                if (var_r28 == 0) {
                    var_r28 = 1;
                    HuAudFXVolSet(lbl_1_bss_E2C[0], 0x7F);
                }
            }
            if (temp_r31->unk10.x < -300.0f) {
                break;
            }
            Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
            Hu3DModelPosSet(temp_r30->unk00, temp_r31->unk10.x + 35.0f, temp_r31->unk10.y, temp_r31->unk10.z);
            HuPrcVSleep();
        }
        if (lbl_1_bss_E98 == 4) {
            break;
        }
        temp_r31->unk10.x = -500.0f;
        temp_r31->unk1C.y = 90.0f;
        Hu3DModelRotSet(temp_r31->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        Hu3DModelRotSet(temp_r30->unk00, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        var_r29 = 0;
        while (TRUE) {
            temp_r31->unk10.x += temp_f31;
            if (var_r29 == 0 && temp_r31->unk10.x > -400.0f) {
                var_r29 = 1;
                if (lbl_1_bss_E2C[0] != -1) {
                    HuAudFXStop(lbl_1_bss_E2C[0]);
                }
                lbl_1_bss_E2C[0] = HuAudFXPlayVol(0x56E, 0);
            }
            if (temp_r31->unk10.x > 300.0f) {
                break;
            }
            Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
            Hu3DModelPosSet(temp_r30->unk00, temp_r31->unk10.x - 35.0f, temp_r31->unk10.y, temp_r31->unk10.z);
            HuPrcVSleep();
        }
    }
    Hu3DModelAttrSet(temp_r31->unk00, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r30->unk00, HU3D_ATTR_DISPOFF);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_5384(void)
{
    UnkBss138Struct *temp_r30;
    Process *var_r31;

    temp_r30 = HuPrcCurrentGet()->user_data;
    var_r31 = HuPrcChildCreate(fn_1_507C, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    var_r31->user_data = temp_r30;
    while (lbl_1_bss_E98 != 4) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x122);
    var_r31 = HuPrcChildCreate(fn_1_4E8C, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    var_r31->user_data_u32 = 1;
    var_r31 = HuPrcChildCreate(fn_1_4E8C, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    var_r31->user_data_u32 = 2;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_544C(void)
{
    UnkBss138InnerStruct00 *temp_r31;
    s32 temp_r30;

    temp_r30 = (s32)HuPrcCurrentGet()->user_data;
    temp_r31 = &lbl_1_bss_138.unk1C[temp_r30 + 2];
    switch (temp_r30) {
        case 0:
            temp_r31->unk10.x = 433.0f;
            break;
        case 1:
            temp_r31->unk10.x = 0.0f;
            break;
        default:
            temp_r31->unk10.x = -433.0f;
            break;
    }
    while (TRUE) {
        Hu3DModelAttrSet(temp_r31->unk00, HU3D_MOTATTR_LOOP);
        temp_r31->unk10.x += 2.0f * lbl_1_bss_E24;
        if (temp_r31->unk10.x > 650.0f) {
            temp_r31->unk10.x -= 1300.0f;
        }
        Hu3DModelPosSet(temp_r31->unk00, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        HuPrcVSleep();
    }
}

void fn_1_5554(void)
{
    float var_f28;
    float temp_f25;
    float temp_f27;
    float var_f26;
    float var_f31;
    float var_f30;
    float var_f29; // ! - uninitialized
    float sp8;
    float temp_f24;
    UnkBss138InnerStruct00 spC;
    UnkBss138InnerStruct00 *var_r31;
    UnkBss138InnerStruct00 *var_r30;

    var_r31 = &spC;
    var_r30 = &lbl_1_bss_138.unk1AC[0];
    var_r31->unk00 = Hu3DModelLink(var_r30->unk00);
    Hu3DModelCameraSet(var_r31->unk00, 1);
    Hu3DModelAttrReset(var_r31->unk00, HU3D_ATTR_DISPOFF);
    var_r31->unk10.x = -500.0f + 100.0f * frandf();
    var_r31->unk10.y = var_f26 = 200.0f + 500.0f * frandf();
    var_r31->unk10.z = 400.0f;
    var_r31->unk1C.x = -80.0f;
    var_r31->unk1C.y = 190.0f;
    var_r31->unk1C.z = 45.0f;
    var_f28 = 5.5f + frandf();
    temp_f25 = 2.0f;
    temp_f27 = 0.4f + 0.2f * frandf();
    Hu3DModelScaleSet(var_r31->unk00, temp_f27, temp_f27, temp_f27);
    var_f31 = 0.0f;
    var_f30 = 0.0f;
    while (TRUE) {
        var_r31->unk10.x += var_f28;
        var_f29 += 10.0f;
        if (var_f29 > 360.0f) {
            var_f29 -= 360.0f;
        }
        var_r31->unk10.y = var_f26 + 20.0 * sind(var_f29);
        var_f26 -= temp_f25;
        var_f28 += 0.1f;
        Hu3DModelPosSet(var_r31->unk00, var_r31->unk10.x, var_r31->unk10.y, var_r31->unk10.z);
        var_f31 += 20.0f;
        var_f30 += 20.0f;
        if (var_f31 > 360.0f) {
            var_f31 -= 360.0f;
        }
        if (var_f30 > 360.0f) {
            var_f30 -= 360.0f;
        }
        temp_f24 = var_r31->unk1C.y + 40.0 * sind(var_f31);
        sp8 = var_r31->unk1C.x + 30.0 * sind(var_f31);
        Hu3DModelRotSet(var_r31->unk00, var_r31->unk1C.x, temp_f24, var_r31->unk1C.z);
        if (var_r31->unk10.x > 400.0f) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DModelKill(var_r31->unk00);
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_58BC(void)
{
    while (TRUE) {
        if (lbl_1_bss_E98 == 4) {
            break;
        }
        HuPrcChildCreate(fn_1_5554, 0x2000, 0x2000, 0, HuPrcCurrentGet());
        HuPrcSleep(20);
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_5910(void)
{
    float var_f31;
    UnkBss138Struct *spC;
    Process *var_r29;
    UnkBss138InnerStruct00 *var_r31;
    UnkBss474Struct *sp8;
    s32 i;

    spC = HuPrcCurrentGet()->user_data;
    HuPrcChildCreate(fn_1_58BC, 0x2000, 0x2000, 0, HuPrcCurrentGet());
    for (i = 0; i < 3; i++) {
        var_r29 = HuPrcChildCreate(fn_1_544C, 0x2000, 0x2000, 0, HuPrcCurrentGet());
        var_r29->user_data_u32 = i;
    }
    while (lbl_1_bss_E98 != 4) {
        HuPrcVSleep();
    }
    var_r31 = &lbl_1_bss_138.unkE4[0];
    Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[1], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    for (var_f31 = 1.0f; var_f31 > 0.0f; var_f31 -= 0.033333335f) {
        lbl_1_bss_E24 = var_f31;
        Hu3DTexScrollPosMoveSet(lbl_1_bss_E9E, -0.01f * var_f31, 0.0f, 0.0f);
        Hu3DTexScrollPosMoveSet(lbl_1_bss_E9C, -0.017f * var_f31, 0.0f, 0.0f);
        HuAudFXPitchSet(lbl_1_bss_E2C[0], -8191.0f * (1.0f - var_f31));
        HuPrcVSleep();
    }
    lbl_1_bss_E24 = 0.0f;
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9E, -0.0f, 0.0f, 0.0f);
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9C, -0.0f, 0.0f, 0.0f);
    HuAudFXPitchSet(lbl_1_bss_E2C[0], -0x1FFF);
    HuPrcSleep(270);
    sp8 = &lbl_1_bss_474[lbl_1_bss_E94];
    Hu3DMotionSet(var_r31->unk00, var_r31->unk02[2]);
    for (var_f31 = 0.0f; var_f31 < 1.0f; var_f31 += 0.033333335f) {
        lbl_1_bss_E24 = var_f31;
        Hu3DTexScrollPosMoveSet(lbl_1_bss_E9E, -0.01f * var_f31, 0.0f, 0.0f);
        Hu3DTexScrollPosMoveSet(lbl_1_bss_E9C, -0.017f * var_f31, 0.0f, 0.0f);
        HuAudFXPitchSet(lbl_1_bss_E2C[0], -8191.0f * (1.0f - var_f31));
        HuPrcVSleep();
    }
    lbl_1_bss_E24 = 1.0f;
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9E, -0.01f, 0.0f, 0.0f);
    Hu3DTexScrollPosMoveSet(lbl_1_bss_E9C, -0.017f, 0.0f, 0.0f);
    HuAudFXPitchSet(lbl_1_bss_E2C[0], 0);
    Hu3DMotionShiftSet(var_r31->unk00, var_r31->unk02[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    while (TRUE) {
        HuPrcVSleep();
    }
}

s8 fn_1_5D58(s32 arg0, s32 arg1)
{
    UnkBss474Struct *temp_r31;
    s8 var_r30;

    temp_r31 = &lbl_1_bss_474[arg0];
    if (!GWPlayerCfg[arg0].iscom) {
        (arg1 != 0) ? (var_r30 = HuPadStkY[temp_r31->unk3C]) : (var_r30 = HuPadStkX[temp_r31->unk3C]);
    }
    else {
        (arg1 != 0) ? (var_r30 = temp_r31->unk255) : (var_r30 = temp_r31->unk254);
    }
    return var_r30;
}

u8 fn_1_5E10(s32 arg0, s32 arg1)
{
    UnkBss474Struct *temp_r31;
    s8 var_r30;

    temp_r31 = &lbl_1_bss_474[arg0];
    if (!GWPlayerCfg[arg0].iscom) {
        (arg1 != 0) ? (var_r30 = HuPadTrigR[temp_r31->unk3C]) : (var_r30 = HuPadTrigL[temp_r31->unk3C]);
    }
    else {
        (arg1 != 0) ? (var_r30 = temp_r31->unk256) : (var_r30 = temp_r31->unk257);
    }
    return var_r30;
}

u16 fn_1_5ED0(s32 arg0)
{
    UnkBss474Struct *temp_r31;
    u16 var_r30;

    temp_r31 = &lbl_1_bss_474[arg0];
    if (!GWPlayerCfg[arg0].iscom) {
        var_r30 = HuPadBtnDown[temp_r31->unk3C];
    }
    else {
        var_r30 = temp_r31->unk258;
    }
    return var_r30;
}

void fn_1_5F3C(UnkBss474Struct *arg0, s32 arg1)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    UnkBss474DoublyInnerStruct6C *temp_r31;
    UnkBss474DoublyInnerStruct6C *temp_r29;
    UnkBss474DoublyInnerStruct6C *temp_r27;
    UnkBss474InnerStructE4 *temp_r28;
    s32 var_r25;
    s32 i;

    temp_r31 = &arg0->unk6C[arg1]->unk1C;
    temp_r29 = &arg0->unk94[arg1]->unk1C;
    temp_r27 = &arg0->unkBC[arg1]->unk1C;
    temp_r28 = &arg0->unkE4[arg1];
    temp_f31 = (temp_r28->unk00 - temp_r31->unk00) / 15.0f;
    temp_f29 = (temp_r28->unk08 - temp_r31->unk08) / 30.0f;
    temp_f30 = (temp_r28->unk04 - temp_r31->unk04) / 15.0f;
    HuSprAttrSet(arg0->unk0C, 0, HUSPR_ATTR_REVERSE);
    omVibrate(arg0->unk34, 12, 6, 6);
    var_r25 = 0;
    for (i = 0; i < 30; i++) {
        temp_r31->unk08 += temp_f29;
        temp_r27->unk08 = temp_r29->unk08 = temp_r31->unk08 - 5.0f;
        if (i < 15) {
            temp_r31->unk00 += temp_f31;
            temp_r31->unk04 += temp_f30;
            temp_r27->unk00 = temp_r29->unk00 = temp_r31->unk00;
            temp_r27->unk04 = temp_r29->unk04 = temp_r31->unk04;
            temp_r29->unk18 *= 0.95f;
            temp_r29->unk1C *= 0.95f;
            sp2C.x = temp_r31->unk00 + 60.0f;
            sp2C.z = 100.0f;
            sp2C.y = temp_r31->unk04 - 30.0f;
            Hu3D3Dto2D(&sp2C, 1 << arg0->unk38, &sp20);
            var_f28 = 290.0f * (arg0->unk34 % 2) + sp20.x / 2;
            var_f27 = 245.0f * (arg0->unk34 / 2) + sp20.y / 2;
            HuSprGrpPosSet(arg0->unk0C, var_f28, var_f27);
        }
        temp_r27->unk08 += 10.0f;
        if (i < 14) {
            var_r25 += 17;
        }
        else if (i < 28) {
            var_r25 -= 17;
        }
        Hu3DModelTPLvlSet(arg0->unk04, 255 - var_r25);
        HuPrcVSleep();
    }
    temp_r31->unk00 = temp_r28->unk00;
    temp_r31->unk04 = temp_r28->unk04;
    temp_r31->unk08 = temp_r28->unk08;
    sp14.x = temp_r31->unk00 + 60.0f;
    sp14.z = 100.0f;
    sp14.y = temp_r31->unk04 - 30.0f;
    Hu3D3Dto2D(&sp14, 1 << arg0->unk38, &sp8);
    var_f26 = 290.0f * (arg0->unk34 % 2) + sp8.x / 2;
    var_f25 = 245.0f * (arg0->unk34 / 2) + sp8.y / 2;
    HuSprGrpPosSet(arg0->unk0C, var_f26, var_f25);
    temp_r29->unk00 = 5000.0f;
    temp_r27->unk00 = 5000.0f;
}

void fn_1_6428(UnkBss474Struct *arg0, s32 arg1)
{
    float var_f31;
    UnkBss474DoublyInnerStruct6C *temp_r31;
    UnkBss474DoublyInnerStruct6C *temp_r29;
    UnkBss474InnerStructE4 *temp_r30;

    temp_r31 = &arg0->unk6C[arg1]->unk1C;
    temp_r29 = &arg0->unk94[arg1]->unk1C;
    temp_r30 = &arg0->unkE4[arg1];
    for (var_f31 = 0.0f; var_f31 < 180.0f; var_f31 += 10.0f) {
        temp_r31->unk18 = 0.8f * temp_r30->unk18 + temp_r30->unk18 * (1.0 - sind(var_f31)) * 0.2f;
        temp_r31->unk1C = 0.8f * temp_r30->unk1C + temp_r30->unk1C * (1.0 - sind(var_f31)) * 0.2f;
        temp_r31->unk20 = 0.8f * temp_r30->unk20 + temp_r30->unk20 * (1.0 - sind(var_f31)) * 0.2f;
        temp_r29->unk18 = temp_r31->unk18;
        temp_r29->unk1C = temp_r31->unk1C;
        temp_r29->unk20 = 0.8f * temp_r31->unk20;
        HuPrcVSleep();
    }
    for (var_f31 = 180.0f; var_f31 < 360.0f; var_f31 += 20.0f) {
        temp_r31->unk18 = 0.9f * temp_r30->unk18 + temp_r30->unk18 * (1.0 - sind(var_f31)) * 0.1f;
        temp_r31->unk1C = 0.9f * temp_r30->unk1C + temp_r30->unk1C * (1.0 - sind(var_f31)) * 0.1f;
        temp_r31->unk20 = 0.9f * temp_r30->unk20 + temp_r30->unk20 * (1.0 - sind(var_f31)) * 0.1f;
        temp_r29->unk18 = temp_r31->unk18;
        temp_r29->unk1C = temp_r31->unk1C;
        temp_r29->unk20 = 0.8f * temp_r31->unk20;
        HuPrcVSleep();
    }
    temp_r31->unk18 = temp_r30->unk18;
    temp_r31->unk1C = temp_r30->unk1C;
    temp_r31->unk20 = temp_r30->unk20;
    temp_r29->unk18 = temp_r31->unk18;
    temp_r29->unk1C = temp_r31->unk1C;
    temp_r29->unk20 = 0.8f * temp_r31->unk20;
}

void fn_1_6820(UnkBss474Struct *arg0, s32 arg1, s32 arg2)
{
    UnkBss474DoublyInnerStruct6C *temp_r30;
    UnkBss474DoublyInnerStruct6C *temp_r31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float var_f31;
    s32 i;

    temp_r31 = &arg0->unk6C[arg1]->unk1C;
    temp_r30 = &arg0->unk94[arg1]->unk1C;
    temp_f30 = temp_r31->unk18;
    temp_f29 = temp_r31->unk1C;
    temp_f28 = temp_r31->unk20;
    temp_r31->unk18 = temp_r31->unk1C = temp_r31->unk20 = 0.0f;
    temp_r30->unk18 = temp_r30->unk1C = temp_r30->unk20 = 0.0f;
    for (i = 0, var_f31 = 0.0f; i < 30; i++, var_f31 += 0.033333335f) {
        temp_r31->unk18 += temp_f30 / 30.0f;
        temp_r31->unk1C += temp_f29 / 30.0f;
        temp_r31->unk20 += temp_f28 / 30.0f;
        temp_r30->unk18 = temp_r31->unk18;
        temp_r30->unk1C = temp_r31->unk1C;
        temp_r30->unk20 = 0.8f * temp_r31->unk20;
        if (arg2 == 0) {
            HuSprGrpScaleSet(arg0->unk0C, var_f31, var_f31);
        }
        HuPrcVSleep();
    }
    temp_r31->unk18 = temp_f30;
    temp_r31->unk1C = temp_f29;
    temp_r31->unk20 = temp_f28;
    temp_r30->unk18 = temp_r31->unk18;
    temp_r30->unk1C = temp_r31->unk1C;
    temp_r30->unk20 = 0.8f * temp_r31->unk20;
    if (arg2 == 0) {
        HuSprAttrReset(arg0->unk0C, 0, HUSPR_ATTR_NOANIM);
        HuSprGrpScaleSet(arg0->unk0C, 1.0f, 1.0f);
        return;
    }
    HuSprAttrReset(arg0->unk0C, 0, HUSPR_ATTR_REVERSE);
}

void fn_1_6A3C(void)
{
    float var_f31;
    float var_f30;
    float temp_f29;
    UnkFn64A3Struct *temp_r30;
    UnkBss474DoublyInnerStruct6C *temp_r31;
    UnkBss474DoublyInnerStruct6C *temp_r28;
    s32 var_r27;
    s32 i;

    temp_r30 = HuPrcCurrentGet()->user_data;
    temp_r31 = &temp_r30->unk00->unk6C[temp_r30->unk04]->unk1C;
    temp_r28 = &temp_r30->unk00->unk94[temp_r30->unk04]->unk1C;
    HuAudFXPlay(0x56C);
    if (temp_r30->unk08 != 0) {
        var_f30 = temp_r31->unk14 + 90.0f;
    }
    else {
        var_f30 = temp_r31->unk14 - 90.0f;
    }
    if (var_f30 >= 360.0f) {
        var_f30 -= 360.0f;
    }
    if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    temp_f29 = temp_r31->unk14;
    var_f31 = 0.0f;
    for (i = 0, var_r27 = 15; i < var_r27; i++) {
        if (temp_r30->unk08 != 0) {
            temp_r31->unk14 = temp_f29 + 100.0 * sind(var_f31);
        }
        else {
            temp_r31->unk14 = temp_f29 - 100.0 * sind(var_f31);
        }
        temp_r28->unk14 = temp_r31->unk14;
        var_f31 += 6.0f;
        HuPrcVSleep();
    }
    var_f31 = 90.0f;
    for (i = 0, var_r27 = 3; i < var_r27; i++) {
        var_f31 -= 8.333333f;
        if (temp_r30->unk08 != 0) {
            temp_r31->unk14 = temp_f29 + 100.0 * sind(var_f31);
        }
        else {
            temp_r31->unk14 = temp_f29 - 100.0 * sind(var_f31);
        }
        temp_r28->unk14 = temp_r31->unk14;
        HuPrcVSleep();
    }
    temp_r28->unk14 = var_f30;
    temp_r31->unk14 = var_f30;
    *temp_r30->unk0C = 0;
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_6CF4(void)
{
    float temp_f30;
    float var_f31;
    UnkBss474DoublyInnerStruct6C *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    HuPrcSleep(frandmod(30));
    temp_f30 = temp_r31->unk00 / 100.0f;
    var_f31 = -7.0f;
    while (TRUE) {
        temp_r31->unk04 -= var_f31;
        if (temp_r31->unk04 < -500.0f) {
            break;
        }
        var_f31 += 0.5f;
        if (var_f31 > 20.0f) {
            var_f31 = 20.0f;
        }
        temp_r31->unk00 += temp_f30;
        temp_r31->unk08 += 10.0f;
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_6DD8(UnkBss474Struct *arg0, s32 arg1)
{
    UnkBss474DoublyInnerStruct6C *temp_r31;

    temp_r31 = &arg0->unk6C[arg1]->unk1C;
    if (temp_r31->unk00 > 220.0f) {
        temp_r31->unk00 = 220.0f;
    }
    if (temp_r31->unk00 < -220.0f) {
        temp_r31->unk00 = -220.0f;
    }
    if (temp_r31->unk04 > 140.0f) {
        temp_r31->unk04 = 140.0f;
    }
    if (temp_r31->unk04 < -140.0f) {
        temp_r31->unk04 = -140.0f;
    }
}

void fn_1_6E9C(s32 arg0, s32 arg1)
{
    switch (GWPlayerCfg[arg0].diff) {
        case 0:
            arg1 *= 8;
            break;
        case 1:
            arg1 *= 4;
            break;
        case 2:
            arg1 *= 3;
            break;
        default:
            arg1 *= 2;
            break;
    }
    if (arg1 <= 1) {
        HuPrcVSleep();
    }
    else {
        HuPrcSleep(arg1 + frandmod(arg1 / 2));
    }
}

void fn_1_6F48(UnkBss474Struct *arg0, s32 arg1, s32 arg2)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f29;
    UnkBss474DoublyInnerStruct6C *temp_r30;
    UnkBss474InnerStructE4 *temp_r25;
    s32 var_r27;
    s32 var_r23;

    arg1 = lbl_1_bss_E6C[arg2];
    temp_r30 = &arg0->unk6C[arg1]->unk1C;
    arg0->unk254 = arg0->unk255 = 0;
    arg0->unk257 = arg0->unk256 = 0;
    arg0->unk258 = 0;
    switch (GWPlayerCfg[arg0->unk34].diff) {
        case 0:
            var_r27 = arg2 * 2 + 60;
            break;
        case 1:
            var_r27 = arg2 + 80;
            break;
        case 2:
            var_r27 = arg2 + 85;
            break;
        default:
            var_r27 = arg2 + 90;
            break;
    }
    if (var_r27 > 100) {
        var_r27 = 100;
    }
    if (arg0->unk264 == -1) {
        if (frandmod(100) < var_r27 || lbl_1_bss_E38 == arg2 + 1) {
            arg0->unk264 = arg1;
        }
        else {
            var_r23 = frandmod(lbl_1_bss_E38 - arg2);
            arg0->unk264 = lbl_1_bss_E6C[arg2 + var_r23];
        }
        arg0->unk268 = -1;
        if ((GWPlayerCfg[arg0->unk34].diff == 2 || GWPlayerCfg[arg0->unk34].diff == 3) && (frandmod(100) < var_r27 || lbl_1_bss_E38 == arg2 + 1)) {
            arg0->unk268 = 10;
        }
        fn_1_6E9C(arg0->unk34, 10);
    }
    temp_r25 = &arg0->unkE4[arg0->unk264];
    HuSetVecF(&sp24, temp_r25->unk00, temp_r25->unk04, 0.0);
    HuSetVecF(&sp18, temp_r30->unk00, temp_r30->unk04, 0.0);
    HuSubVecF(&spC, &sp24, &sp18);
    if (sqrtf(spC.x * spC.x + spC.y * spC.y) >= 40.0f) {
        temp_f29 = atan2d(spC.x, spC.y);
        arg0->unk254 = 50.0 * sind(temp_f29);
        arg0->unk255 = 50.0 * cosd(temp_f29);
        if (arg0->unk268 >= 0) {
            if (arg0->unk268-- == 0 && temp_r30->unk14 != 0.0f) {
                arg0->unk268 = 10;
                if (temp_r30->unk14 - 90.0f == 0.0f) {
                    arg0->unk256 = 50;
                }
                else {
                    arg0->unk257 = 50;
                }
            }
        }
    }
    else {
        fn_1_6E9C(arg0->unk34, 1);
        if (frandmod(100) < var_r27 || lbl_1_bss_E38 == arg2 + 1) {
            if (temp_r30->unk14 != 0.0f) {
                if (temp_r30->unk14 - 90.0f == 0.0f) {
                    arg0->unk256 = 50;
                }
                else {
                    arg0->unk257 = 50;
                }
            }
            else {
                arg0->unk258 = 0x100;
                arg0->unk264 = -1;
            }
        }
        else {
            switch (frandmod(3)) {
                case 0:
                    arg0->unk256 = 50;
                    break;
                case 1:
                    arg0->unk256 = 50;
                    break;
                default:
                    arg0->unk258 = 0x100;
                    arg0->unk264 = -1;
                    break;
            }
            if (frandmod(100) < var_r27) {
                arg0->unk264 = -1;
            }
        }
    }
}

void fn_1_75C8(void)
{
    s16 var_r30;
    s32 var_r31;

    for (var_r30 = 127; var_r30 > 0; var_r30 -= 4) {
        for (var_r31 = 0; var_r31 < lbl_1_bss_E28; var_r31++) {
            HuAudFXVolSet(lbl_1_bss_E2C[var_r31], var_r30);
        }
        HuPrcVSleep();
    }
    for (var_r31 = 0; var_r31 < lbl_1_bss_E28; var_r31++) {
        HuAudFXVolSet(lbl_1_bss_E2C[var_r31], 0);
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_7680(void)
{
    s16 var_r30;
    s32 var_r31;

    for (var_r30 = 0; var_r30 < 127; var_r30 += 4) {
        for (var_r31 = 0; var_r31 < lbl_1_bss_E28; var_r31++) {
            HuAudFXVolSet(lbl_1_bss_E2C[var_r31], var_r30);
        }
        HuPrcVSleep();
    }
    for (var_r31 = 0; var_r31 < lbl_1_bss_E28; var_r31++) {
        HuAudFXVolSet(lbl_1_bss_E2C[var_r31], 0x7F);
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

static inline void m411InlineFunc(UnkBss474Struct *temp_r31, UnkBss474DoublyInnerStruct6C *temp_r30)
{
    Vec sp74;
    Vec sp80;

    float var_f22;
    float var_f23;

    sp80.x = 60.0f + temp_r30->unk00;
    sp80.z = 100.0f;
    sp80.y = temp_r30->unk04 - 30.0f;
    Hu3D3Dto2D(&sp80, 1 << temp_r31->unk38, &sp74);
    var_f23 = 290.0f * (temp_r31->unk34 % 2) + sp74.x / 2.0f;
    var_f22 = 245.0f * (temp_r31->unk34 / 2) + sp74.y / 2.0f;
    HuSprGrpPosSet(temp_r31->unk0C, var_f23, var_f22);
}

#define SOME_MACRO(x) ((x) >= 0 ? (x) : (-(x) > 20))

void fn_1_7738(void)
{
    f32 temp_f26;
    f32 temp_f27;
    Process *var_r24;
    UnkBss474Struct *temp_r31;
    UnkBss474DoublyInnerStruct6C *temp_r30;
    s32 var_r29;
    UnkBss474DoublyInnerStruct6C *temp_r28;
    s32 temp_r26;
    UnkBss474InnerStructE4 *temp_r25;
    s32 var_r23;
    Vec spCC;
    Vec spC0;
    Vec spB4;
    UnkFn64A3Struct spA4;
    s32 sp70;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk40 = 0;
    for (var_r29 = 0; var_r29 < lbl_1_bss_E38; var_r29++) {
        temp_r30 = &temp_r31->unk94[var_r29]->unk1C;
        temp_r30->unk00 = 5000.0f;
        temp_r30 = &temp_r31->unkBC[var_r29]->unk1C;
        temp_r30->unk00 = 5000.0f;
    }
    while (lbl_1_bss_E98 == 0) {
        HuPrcVSleep();
    }
    Hu3DModelAttrReset(temp_r31->unk08, HU3D_ATTR_DISPOFF);
    for (var_r29 = 0; var_r29 < 30; var_r29++) {
        if (lbl_1_bss_E40 == 0) {
            lbl_1_bss_C4[temp_r31->unk38].z += 10.0f;
        }
        else {
            CZoomM[temp_r31->unk38] += 10.0f;
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrReset(temp_r31->unk00, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r31->unk02, HU3D_ATTR_DISPOFF);
    if (temp_r31->unk34 == 0) {
        HuAudFXPlay(0x56F);
    }
    for (var_r29 = 0; var_r29 < lbl_1_bss_E38; var_r29++) {
        temp_r30 = &temp_r31->unk6C[var_r29]->unk1C;
        temp_f26 = atan2d(temp_r30->unk00, temp_r30->unk04);
        temp_f27 = sqrtf(temp_r30->unk00 * temp_r30->unk00 + temp_r30->unk04 * temp_r30->unk04);
        temp_f27 *= 1.05f;
        temp_r30->unk00 = temp_f27 * sind(temp_f26);
        temp_r30->unk04 = temp_f27 * cosd(temp_f26);
    }
    omVibrate(temp_r31->unk34, 12, 6, 6);
    HuPrcSleep(30);
    CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[5], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    HuPrcChildCreate(fn_1_75C8, 0x2000, 0x1000, 0, HuPrcCurrentGet());
    if (temp_r31->unk34 == 0) {
        HuAudFXPlay(0x56B);
    }
    for (var_r29 = 0; var_r29 < lbl_1_bss_E38; var_r29++) {
        var_r24 = HuPrcChildCreate(fn_1_6CF4, 0x2000, 0x1000, 0, HuPrcCurrentGet());
        temp_r30 = &temp_r31->unk6C[var_r29]->unk1C;
        var_r24->user_data = temp_r30;
    }
    HuPrcSleep(40);
    HuPrcSleep(40);
    for (var_r29 = 0; var_r29 < 30; var_r29++) {
        if (lbl_1_bss_E40 == 0) {
            lbl_1_bss_C4[temp_r31->unk38].z -= 10.0f;
        }
        else {
            CZoomM[temp_r31->unk38] -= 10.0f;
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(temp_r31->unk08, HU3D_ATTR_DISPOFF);
    HuPrcSleep(60);
    lbl_1_bss_E98 = 2;
    for (var_r29 = 0; var_r29 < lbl_1_bss_E38; var_r29++) {
        sp70 = 0;
        temp_r31->unk44 = 0;
        temp_r31->unk264 = -1;
        temp_r26 = lbl_1_bss_E6C[var_r29];
        temp_r30 = &temp_r31->unk6C[temp_r26]->unk1C;
        temp_r28 = &temp_r31->unk94[temp_r26]->unk1C;
        if (var_r29 != 0) {
            temp_r25 = &temp_r31->unkE4[lbl_1_bss_E6C[var_r29 - 1]];
            temp_r30->unk00 = temp_r25->unk00;
            temp_r30->unk04 = temp_r25->unk04;
            temp_r28->unk00 = 20.0f + temp_r30->unk00;
            temp_r28->unk04 = -20.0f + temp_r30->unk04;
        }
        else {
            temp_r30->unk00 = temp_r30->unk04 = 0.0f;
            temp_r28->unk00 = 20.0f + temp_r30->unk00;
            temp_r28->unk04 = -20.0f + temp_r30->unk04;
            m411InlineFunc(temp_r31, temp_r30);
            HuSprAttrReset(temp_r31->unk0C, 0, HUSPR_ATTR_DISPOFF);
        }
        temp_r30->unk08 = 50.0f;
        temp_r28->unk08 = temp_r30->unk08 - 5.0f;
        temp_r30->unk14 = temp_r28->unk14 = 90.0f * lbl_1_bss_E44[var_r29];
        fn_1_6820(temp_r31, temp_r26, var_r29);
        if (var_r29 == 0) {
            while (lbl_1_bss_E98 != 3) {
                HuPrcVSleep();
            }
        }
        while (TRUE) {
            if (GWPlayerCfg[temp_r31->unk34].iscom == 1) {
                fn_1_6F48(temp_r31, temp_r26, var_r29);
            }
            if (sp70 == 0) {
                var_r23 = -1;
                if (fn_1_5E10(temp_r31->unk34, 0) > 20) {
                    var_r23 = 1;
                }
                if (fn_1_5E10(temp_r31->unk34, 1) > 20) {
                    var_r23 = 0;
                }
                if (var_r23 != -1) {
                    sp70 = 1;
                    var_r24 = HuPrcChildCreate(fn_1_6A3C, 0x2000, 0x2000, 0, HuPrcCurrentGet());
                    var_r24->user_data = &spA4;
                    spA4.unk00 = temp_r31;
                    spA4.unk04 = temp_r26;
                    spA4.unk08 = var_r23;
                    spA4.unk0C = &sp70;
                }
            }
            if ((fn_1_5ED0(temp_r31->unk34) & 0x100) && sp70 == 0) {
                if (0.0f == temp_r30->unk14) {
                    temp_r25 = &temp_r31->unkE4[temp_r26];
                    HuSetVecF(&spCC, temp_r25->unk00, temp_r25->unk04, 0.0);
                    HuSetVecF(&spC0, temp_r30->unk00, temp_r30->unk04, 0.0);
                    HuSubVecF(&spB4, &spCC, &spC0);
                    if (sqrtf(spB4.x * spB4.x + spB4.y * spB4.y) < 40.0f) {
                        HuAudFXPlay(0x56D);
                        temp_r31->unk44 = 1;
                        temp_r31->unk64 = temp_r30->unk00;
                        temp_r31->unk68 = temp_r30->unk04;
                        fn_1_5F3C(temp_r31, temp_r26);
                        break;
                    }
                }
                fn_1_6428(temp_r31, temp_r26);
            }
            temp_r31->unk60 = -1.0f;
            if (SOME_MACRO(fn_1_5D58(temp_r31->unk34, 0)) != 0 || SOME_MACRO(fn_1_5D58(temp_r31->unk34, 1)) != 0) {
                temp_r31->unk60 = atan2d(fn_1_5D58(temp_r31->unk34, 0), fn_1_5D58(temp_r31->unk34, 1));
            }
            if (-1.0f != temp_r31->unk60) {
                temp_r30->unk00 += 5 * sind(temp_r31->unk60);
                temp_r30->unk04 += 5 * cosd(temp_r31->unk60);
                fn_1_6DD8(temp_r31, temp_r26);
                temp_r28->unk00 = 20.0f + temp_r30->unk00;
                temp_r28->unk04 = -20.0f + temp_r30->unk04;
                m411InlineFunc(temp_r31, temp_r30);
            }
            HuPrcVSleep();
        }
    }
    temp_r31->unk40 = 4;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_8A80(float arg0, float arg1)
{
    Hu3DCameraViewportSet(2, 10.0f, 10.0f, arg0 - 11.0f, arg1 - 11.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 10, 10, arg0 - 11.0f, arg1 - 11.0f);
    Hu3DCameraViewportSet(4, arg0 + 2.0f, 10.0f, 630.0f - arg0, arg1 - 11.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(4, arg0 + 2.0f, 10, 630.0f - arg0, arg1 - 11.0f);
    Hu3DCameraViewportSet(8, 10.0f, arg1 + 2.0f, arg0 - 11.0f, 470.0f - arg1, 0.0f, 1.0f);
    Hu3DCameraScissorSet(8, 10, arg1 + 2.0f, arg0 - 11.0f, 470.0f - arg1);
    Hu3DCameraViewportSet(16, arg0 + 2.0f, arg1 + 2.0f, 630.0f - arg0, 470.0f - arg1, 0.0f, 1.0f);
    Hu3DCameraScissorSet(16, arg0 + 2.0f, arg1 + 2.0f, 630.0f - arg0, 470.0f - arg1);
}

void fn_1_8DBC(void)
{
    float var_f31;
    float var_f30;
    s32 i;

    Hu3DCameraViewportSet(2, 10.0f, 10.0f, 629.0f, 469.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 10, 10, 629, 469);
    Hu3DCameraViewportSet(4, 642.0f, 10.0f, -10.0f, 469.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(4, 642, 10, -10, 469);
    Hu3DCameraViewportSet(8, 10.0f, 482.0f, 629.0f, -10.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(8, 10, 482, 629, -10);
    Hu3DCameraViewportSet(16, 642.0f, 482.0f, -10.0f, -10.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(16, 642, 482, -10, -10);
    HuPrcSleep(60);
    for (i = 0, var_f31 = 645.0f, var_f30 = 485.0f; i < 30; i++) {
        var_f31 -= 10.833333f;
        var_f30 -= 8.166667f;
        fn_1_8A80(var_f31, var_f30);
        HuPrcVSleep();
    }
    Hu3DCameraViewportSet(2, 10.0f, 10.0f, 309.0f, 229.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 10, 10, 309, 229);
    Hu3DCameraViewportSet(4, 322.0f, 10.0f, 310.0f, 229.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(4, 322, 10, 310, 229);
    Hu3DCameraViewportSet(8, 10.0f, 242.0f, 309.0f, 230.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(8, 10, 242, 309, 230);
    Hu3DCameraViewportSet(16, 322.0f, 242.0f, 310.0f, 230.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(16, 322, 242, 310, 230);
}

void fn_1_9490(void)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float temp_f27;
    float temp_f26;
    u32 temp_r30;
    s32 i;

    temp_r30 = HuPrcCurrentGet()->user_data_u32;
    switch (temp_r30) {
        case 0:
            var_f31 = 645.0f;
            var_f30 = 485.0f;
            break;
        case 1:
            var_f31 = -5.0f;
            var_f30 = 485.0f;
            break;
        case 2:
            var_f31 = 645.0f;
            var_f30 = -5.0f;
            break;
        default:
            var_f31 = -5.0f;
            var_f30 = -5.0f;
            break;
    }
    var_f29 = 320.0f;
    var_f28 = 240.0f;
    temp_f27 = (var_f31 - var_f29) / 30.0f;
    temp_f26 = (var_f30 - var_f28) / 30.0f;
    for (i = 0; i < 30; i++) {
        var_f29 += temp_f27;
        var_f28 += temp_f26;
        fn_1_8A80(var_f29, var_f28);
        HuPrcVSleep();
    }
    fn_1_8A80(var_f31, var_f30);
    HuPrcChildCreate(fn_1_7680, 0x2000, 0x1000, 0, HuPrcCurrentGet());
    HuPrcCurrentGet()->user_data = NULL;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_9BC0(s32 arg0)
{
    float var_f30;
    float var_f31;
    s32 var_r29;
    UnkBss474Struct *temp_r31;
    UnkBss474Struct *var_r26;
    Process *var_r28;
    UnkBss138InnerStruct00 *var_r27;
    s32 i;

    temp_r31 = &lbl_1_bss_474[arg0];
    for (i = 0, var_f30 = 1.0f; i < 15; i++) {
        var_f30 -= 0.06666667f;
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            var_r26 = &lbl_1_bss_474[var_r29];
            HuSprGrpScaleSet(var_r26->unk0C, var_f30, var_f30);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuSprAttrSet(lbl_1_bss_474[i].unk0C, 0, HUSPR_ATTR_DISPOFF);
    }
    Hu3DModelAttrReset(temp_r31->unk02, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r31->unk00, HU3D_ATTR_DISPOFF);
    var_r28 = HuPrcChildCreate(fn_1_9490, 0x2000, 0x1000, 0, HuPrcCurrentGet());
    var_r28->user_data_u32 = arg0;
    while (var_r28->user_data_u32) {
        HuPrcVSleep();
    }
    temp_r31->unk48 = 500.0f;
    temp_r31->unk4C = -280.0f;
    temp_r31->unk50 = 200.0f;
    temp_r31->unk58 = -90.0f;
    Hu3DModelAttrReset(temp_r31->unk08, HU3D_ATTR_DISPOFF);
    Hu3DModelRotSet(temp_r31->unk08, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
    CharModelMotionSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[2]);
    Hu3DModelAttrSet(temp_r31->unk08, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(temp_r31->unk08, 1 << temp_r31->unk38);
    i = 0;
    while (TRUE) {
        temp_r31->unk48 -= 5.0f;
        if (temp_r31->unk48 <= 0.0f) {
            break;
        }
        if (i == 70 && lbl_1_bss_E40 == 2) {
            var_r27 = &lbl_1_bss_138.unkE4[0];
            Hu3DMotionSet(var_r27->unk00, var_r27->unk02[4]);
            HuAudFXPlay(0x41);
        }
        Hu3DModelPosSet(temp_r31->unk08, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        HuPrcVSleep();
        i++;
    }
    Hu3DModelPosSet(temp_r31->unk08, 0.0f, temp_r31->unk4C, temp_r31->unk50);
    CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    HuPrcSleep(10);
    for (i = 0; i < 9; i++) {
        temp_r31->unk58 -= 10.0f;
        Hu3DModelRotSet(temp_r31->unk08, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[3], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    if (lbl_1_bss_E40 == 1) {
        var_f31 = -20.0f;
    }
    else {
        var_f31 = -20.0f;
    }
    for (; var_f31 < 0.0f; var_f31 += 1.765f) {
        temp_r31->unk4C -= var_f31;
        Hu3DModelPosSet(temp_r31->unk08, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        HuPrcVSleep();
    }
    Hu3DModelShadowSet(temp_r31->unk08);
}

void fn_1_A004(void)
{
    s32 i;

    for (i = 0; i < 67; i++) {
        lbl_1_bss_C4->y += -10.0f;
        lbl_1_bss_C4->z += -26.656717f;
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_A07C(void)
{
    UnkBss474Struct *temp_r31;

    temp_r31 = &lbl_1_bss_474[lbl_1_bss_E94];
    while (TRUE) {
        temp_r31->unk58 += 10.0f;
        if (temp_r31->unk58 > 360.0f) {
            temp_r31->unk58 -= 360.0f;
        }
        Hu3DModelRotSet(temp_r31->unk08, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
        Hu3DModelRotSet(temp_r31->unk20, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
        HuPrcVSleep();
    }
}

void fn_1_A120(s32 arg0)
{
    float temp_f30;
    float var_f31;
    UnkBss474Struct *temp_r31;
    s32 var_r29;
    s32 i;

    temp_r31 = &lbl_1_bss_474[arg0];
    temp_r31->unk48 = 0.0f;
    temp_r31->unk4C = 930.0f;
    temp_r31->unk50 = 2790.0f;
    Hu3DModelAttrReset(temp_r31->unk20, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(temp_r31->unk08, 1);
    HuPrcChildCreate(fn_1_A004, 0x2000, 0x1000, 0, HuPrcCurrentGet());
    temp_f30 = (-730.0f - temp_r31->unk50) / 80.0f;
    var_f31 = 0.0f;
    for (i = 0, var_r29 = 0; i < 80; i++) {
        if (var_r29 == 0) {
            temp_r31->unk4C -= var_f31;
            if (temp_r31->unk4C < 0.0f) {
                var_r29 = 1;
                CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
                Hu3DMotionShiftSet(temp_r31->unk20, temp_r31->unk22[4], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
                temp_r31->unk4C = 0.0f;
                break;
            }
        }
        var_f31 += 1.2f;
        if (var_f31 > 14.0f) {
            var_f31 = 14.0f;
        }
        if (-530.0f < temp_r31->unk50) {
            temp_r31->unk50 += temp_f30;
        }
        Hu3DModelPosSet(temp_r31->unk08, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        Hu3DModelPosSet(temp_r31->unk20, temp_r31->unk48, -temp_r31->unk4C, temp_r31->unk50);
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    while (!Hu3DMotionEndCheck(temp_r31->unk08)) {
        HuPrcVSleep();
    }
    CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    HuPrcSleep(30);
    HuAudSStreamPlay(1);
    HuAudPlayerVoicePlay(temp_r31->unk34, 0x124);
    CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[7], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    Hu3DMotionShiftSet(temp_r31->unk20, temp_r31->unk22[7], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    HuPrcChildCreate(fn_1_A07C, 0x2000, 0x1000, 0, HuPrcCurrentGet());
}

void fn_1_A4B4(s32 arg0)
{
    float temp_f30;
    float var_f31;
    UnkBss474Struct *temp_r31;
    s32 var_r29;
    s32 i;

    temp_r31 = &lbl_1_bss_474[arg0];
    temp_r31->unk48 = 0.0f;
    temp_r31->unk4C = -40.0f;
    temp_r31->unk50 = 180.0f;
    Hu3DModelCameraSet(temp_r31->unk08, 1);
    temp_f30 = (200.0f - temp_r31->unk50) / 30.0f;
    var_f31 = 0.0f;
    for (i = 0, var_r29 = 0; i < 30; i++) {
        if (var_r29 == 0) {
            temp_r31->unk4C -= var_f31;
            if (temp_r31->unk4C < 0.0f) {
                var_r29 = 1;
                CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[2], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
                temp_r31->unk4C = 0.0f;
            }
        }
        var_f31 += 1.0f;
        if (var_f31 > 10.0f) {
            var_f31 = 10.0f;
        }
        temp_r31->unk50 += temp_f30;
        Hu3DModelPosSet(temp_r31->unk08, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        HuPrcVSleep();
    }
    CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 30; i++) {
        temp_r31->unk58 += 6.0f;
        Hu3DModelRotSet(temp_r31->unk08, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
        HuPrcVSleep();
    }
    HuAudSStreamPlay(1);
    CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[8], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
}

void fn_1_A788(s32 arg0)
{
    float temp_f30;
    float temp_f29;
    float var_f31;
    UnkBss474Struct *temp_r31;
    UnkBss138InnerStruct00 *var_r29;
    s32 var_r28;
    s32 i;

    temp_r31 = &lbl_1_bss_474[arg0];
    var_r29 = &lbl_1_bss_138.unkE4[0];
    temp_r31->unk48 = 0.0f;
    temp_r31->unk4C = 170.0f;
    temp_r31->unk50 = 900.0f;
    Hu3DModelCameraSet(temp_r31->unk08, 1);
    temp_f29 = (150.0f - temp_r31->unk50) / 30.0f;
    temp_f30 = -temp_r31->unk48 / 30.0f;
    var_f31 = 0.0f;
    for (i = 0, var_r28 = 0; i < 30; i++) {
        if (var_r28 == 0) {
            temp_r31->unk4C -= var_f31;
            if (temp_r31->unk4C < 0.0f) {
                var_r28 = 1;
                CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[2], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
                temp_r31->unk4C = 0.0f;
            }
        }
        var_f31 += 1.0f;
        if (var_f31 > 10.0f) {
            var_f31 = 10.0f;
        }
        temp_r31->unk48 += temp_f30;
        temp_r31->unk50 += temp_f29;
        Hu3DModelPosSet(temp_r31->unk08, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        HuPrcVSleep();
    }
    CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    HuPrcSleep(30);
    temp_f30 = (100.0f - temp_r31->unk48) / 30.0f;
    temp_f29 = -temp_r31->unk50 / 30.0f;
    var_f31 = 20.0f;
    Hu3DMotionShiftSet(var_r29->unk00, var_r29->unk02[3], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(10);
    CharModelMotionShiftSet(lbl_1_data_240[GWPlayerCfg[temp_r31->unk34].character], temp_r31->unk0E[6], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    for (i = 0; i < 30; i++) {
        temp_r31->unk4C += var_f31;
        var_f31 -= 1.2f;
        temp_r31->unk48 += temp_f30;
        temp_r31->unk50 += temp_f29;
        Hu3DModelPosSet(temp_r31->unk08, temp_r31->unk48, temp_r31->unk4C, temp_r31->unk50);
        temp_r31->unk58 += 3.0f;
        Hu3DModelRotSet(temp_r31->unk08, temp_r31->unk54, temp_r31->unk58, temp_r31->unk5C);
        HuPrcVSleep();
    }
    HuAudPlayerVoicePlay(temp_r31->unk34, 0x124);
    Hu3DModelPosSet(temp_r31->unk08, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(temp_r31->unk08, 0.0f, 0.0f, 0.0f);
    switch (GWPlayerCfg[temp_r31->unk34].character) {
        case 1:
            Hu3DModelPosSet(temp_r31->unk08, 0.0f, -80.0f, 0.0f);
            break;
        case 3:
            Hu3DModelPosSet(temp_r31->unk08, 0.0f, -90.0f, 0.0f);
            break;
        case 2:
            Hu3DModelPosSet(temp_r31->unk08, 0.0f, 20.0f, 0.0f);
            break;
    }
    Hu3DModelHookSet(var_r29->unk00, "zaseki", temp_r31->unk08);
    HuAudSStreamPlay(1);
}

void fn_1_ACB0(void)
{
    s32 i;

    while (TRUE) {
        if (omSysExitReq == 1) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            HuPrcSleep(60);
            for (i = 0; i < 4; i++) {
                HuSprAnimKill(lbl_1_bss_474[i].unk24C);
                HuSprAnimKill(lbl_1_bss_474[i].unk250);
            }
            MGSeqKillAll();
            omOvlReturnEx(1, 1);
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_AD58(void)
{
    s16 temp_r28;
    s16 var_r27;
    s16 temp_r25;
    s32 var_r24;
    s32 var_r29;
    s32 var_r30;
    s32 i;

    lbl_1_bss_E98 = 0;
    HuPrcSleep(1.0f + wipeData.duration);
    switch (lbl_1_bss_E40) {
        case 0:
            lbl_1_bss_E28 = 1;
            lbl_1_bss_E2C[0] = HuAudFXPlay(0x573);
            break;
        case 1:
            lbl_1_bss_E28 = 2;
            lbl_1_bss_E2C[1] = HuAudFXPlay(0x577);
            break;
        default:
            lbl_1_bss_E28 = 1;
            lbl_1_bss_E2C[0] = HuAudFXPlay(0x571);
            break;
    }
    fn_1_8DBC();
    HuPrcSleep(60);
    lbl_1_bss_E98 = 1;
    while (lbl_1_bss_E98 == 1) {
        HuPrcVSleep();
    }
    var_r24 = HuAudSeqPlay(0x45);
    temp_r28 = MGSeqCreate(3, 0);
    while (MGSeqStatGet(temp_r28) != 0) {
        HuPrcVSleep();
    }
    var_r27 = 3659;
    temp_r25 = MGSeqCreate(1, var_r27 / 60, -1, -1);
    lbl_1_bss_E98 = 3;
    while (TRUE) {
        for (i = 0, var_r29 = 0; i < 4; i++) {
            if (lbl_1_bss_474[i].unk40 == 4) {
                var_r29++;
                var_r30 = i;
            }
        }
        if (var_r29 > 0) {
            if (var_r29 > 1) {
                var_r29 = frandmod(var_r29);
                for (i = 0; i < 4; i++) {
                    if (lbl_1_bss_474[i].unk40 == 4 && var_r29-- == 0) {
                        var_r30 = i;
                        break;
                    }
                }
            }
            break;
        }
        else if (var_r27 < 59) {
            var_r30 = -1;
            break;
        }
        MGSeqParamSet(temp_r25, 1, var_r27-- / 60);
        HuPrcVSleep();
    }
    HuAudSeqFadeOut(var_r24, 100);
    for (i = 0; i < 4; i++) {
        HuPrcKill(lbl_1_bss_124[i]);
    }
    MGSeqParamSet(temp_r25, 2, -1);
    temp_r28 = MGSeqCreate(3, 1);
    while (MGSeqStatGet(temp_r28) != 0) {
        HuPrcVSleep();
    }
    if (var_r30 != -1) {
        lbl_1_bss_E98 = 4;
        lbl_1_bss_E94 = var_r30;
        fn_1_9BC0(var_r30);
        switch (lbl_1_bss_E40) {
            case 0:
                fn_1_A120(var_r30);
                break;
            case 1:
                fn_1_A4B4(var_r30);
                break;
            default:
                fn_1_A788(var_r30);
                break;
        }
    }
    if (var_r30 != -1) {
        if (!_CheckFlag(FLAG_ID_MAKE(1, 12))) {
            GWPlayer[var_r30].coin_win = 10;
        }
        temp_r28 = MGSeqCreate(5, 3, GWPlayerCfg[var_r30].character, -1, -1, -1);
    }
    else {
        HuAudSStreamPlay(4);
        temp_r28 = MGSeqCreate(3, 2);
    }
    HuPrcSleep(210);
    lbl_1_bss_E98 = 5;
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuPrcSleep(60);
    HuAudFadeOut(1);
    for (i = 0; i < 4; i++) {
        HuSprAnimKill(lbl_1_bss_474[i].unk24C);
        HuSprAnimKill(lbl_1_bss_474[i].unk250);
    }
    MGSeqKillAll();
    omOvlReturnEx(1, 1);
    while (TRUE) {
        HuPrcVSleep();
    }
}
