#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/objsub.h"

#include "game/frand.h"
#include "game/hsfmotion.h"
#include "game/sprite.h"

#include "REL/m434Dll.h"
#include "ext_math.h"
#include "version.h"

typedef struct bss_2468_data {
    Vec unk0;
    u16 unkC;
} Bss2468Data;

typedef struct bss_450_data {
    void *unk0;
    u32 unk4;
} Bss450Data;

typedef struct bss_3F0_data {
    void *unk0;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u32 unkC;
    s32 unk10;
} Bss3F0Data;

typedef struct struct_data100 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
} StructData100;

StructData100 lbl_1_data_100[5] = {
    { 200, 200, 200, 200, 0 },
    { 320, 240, 160, 120, 1 },
    { 640, 480, 320, 240, 1 },
    { 640, 480, 640, 480, 0 },
    { 0, 0, 0, 0, 0 },
};

omObjData *lbl_1_bss_5868;
Vec lbl_1_bss_2868[1024];
Bss2468Data lbl_1_bss_2468[64];
s32 lbl_1_bss_2464;
HsfVector2f lbl_1_bss_464[1024];
AnimData *lbl_1_bss_460;
AnimData *lbl_1_bss_45C;
AnimData *lbl_1_bss_458;
Bss450Data lbl_1_bss_450;
Bss450Data lbl_1_bss_448;
Bss450Data lbl_1_bss_440;
Bss3F0Data lbl_1_bss_3F0[4];
Vec lbl_1_bss_3D8[2];

void fn_1_1E64(omObjData *object);

void fn_1_1DB0(Process *objman)
{
    "\0"; // Force lbl_1_data_132 to 0
    lbl_1_bss_5868 = omAddObjEx(objman, 10, 16, 0, -1, fn_1_1E64);
    CenterM[1].y = -CenterM[2].y + -15.000001f;
    CRotM[1].x = -CRotM[2].x;
}

void fn_1_28F0(void);

void fn_1_1E44(void)
{
    fn_1_28F0();
}

void fn_1_26A4(omObjData *object);

void fn_1_2978(ModelData *model, Mtx mtx);
void fn_1_3004(void);
void fn_1_3128(void);

void fn_1_33A4(ModelData *model, Mtx mtx);
void fn_1_349C(ModelData *model, Mtx mtx);
void fn_1_3594(ModelData *model, Mtx mtx);
void fn_1_3CC8(ModelData *model, Mtx mtx);

void fn_1_443C(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_1_1E64(omObjData *object)
{
    s32 temp_r30;
    Vec *temp_r29;
    HsfVector2f *temp_r28;
    s32 temp_r27;
    AnimData *temp_r26;

    object->model[9] = Hu3DHookFuncCreate(fn_1_3CC8);
    Hu3DModelLayerSet(object->model[9], 1);
    Hu3DModelCameraSet(object->model[9], 1);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M434, 0x02));
    Hu3DModelLayerSet(object->model[1], 2);
    Hu3DModelCameraSet(object->model[1], 2);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M434, 0x00));
    Hu3DModelLayerSet(object->model[0], 2);
    Hu3DModelCameraSet(object->model[0], 8);
    object->model[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M434, 0x01));
    Hu3DModelLayerSet(object->model[8], 2);
    Hu3DModelCameraSet(object->model[8], 4);
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M434, 0x08));
    Hu3DModelClusterAttrSet(object->model[3], 0, 0xC0000001);
    Hu3DModelLayerSet(object->model[3], 2);
    Hu3DModelCameraSet(object->model[3], 8);
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M434, 0x09));
    Hu3DModelClusterAttrSet(object->model[4], 0, 0xC0000001);
    Hu3DModelLayerSet(object->model[4], 2);
    Hu3DModelCameraSet(object->model[4], 8);
    object->model[2] = Hu3DHookFuncCreate(fn_1_2978);
    Hu3DModelLayerSet(object->model[2], 3);
    Hu3DModelCameraSet(object->model[2], 8);
    temp_r29 = lbl_1_bss_2868;
    for (temp_r30 = 0; temp_r30 < 32; temp_r30++) {
        for (temp_r27 = 0; temp_r27 < 32; temp_r29++, temp_r27++) {
            temp_r29->x = -700.0f + ((1400.0f * temp_r27) / 31.0f);
            temp_r29->y = -15.000001f;
            temp_r29->z = -600.0f + ((1200.0f * temp_r30) / 31.0f);
            if (temp_r30 & 0x1) {
                temp_r29->x += 700.0f / 31.0f;
            }
        }
    }
    DCFlushRangeNoSync(lbl_1_bss_2868, sizeof(lbl_1_bss_2868));
    temp_r28 = lbl_1_bss_464;
    for (temp_r30 = 0; temp_r30 < 1024; temp_r30++, temp_r28++) {
        temp_r28->x = 360.0f * ((1.0f / 256.0f) * frand8());
        temp_r28->y = 2.0f * ((1.0f / 256.0f) * frand8()) + 0.5f;
    }
    memset(lbl_1_bss_2468, 0, sizeof(lbl_1_bss_2468));
    lbl_1_bss_2464 = 0;
    lbl_1_bss_450.unk4 = 16384;
    lbl_1_bss_450.unk0 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_450.unk4, MEMORY_DEFAULT_NUM);
    DCInvalidateRange(lbl_1_bss_450.unk0, lbl_1_bss_450.unk4);
    fn_1_3004();
    lbl_1_bss_440.unk4 = 16384;
    lbl_1_bss_440.unk0 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_440.unk4, MEMORY_DEFAULT_NUM);
    fn_1_3128();
    lbl_1_bss_45C = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M430, 0x19));
    lbl_1_bss_458 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M434, 0x0A));
    HuDataDirClose(DATADIR_M430);
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        lbl_1_bss_3F0[temp_r30].unk4 = lbl_1_data_100[temp_r30].unk0;
        lbl_1_bss_3F0[temp_r30].unk6 = lbl_1_data_100[temp_r30].unk2;
        lbl_1_bss_3F0[temp_r30].unk8 = lbl_1_data_100[temp_r30].unk4;
        lbl_1_bss_3F0[temp_r30].unkA = lbl_1_data_100[temp_r30].unk6;
        lbl_1_bss_3F0[temp_r30].unk10 = lbl_1_data_100[temp_r30].unk8;
        lbl_1_bss_3F0[temp_r30].unkC = GXGetTexBufferSize(lbl_1_bss_3F0[temp_r30].unk8, lbl_1_bss_3F0[temp_r30].unkA, GX_TF_RGB565, GX_FALSE, 0);
        lbl_1_bss_3F0[temp_r30].unk0 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_3F0[temp_r30].unkC, MEMORY_DEFAULT_NUM);
        memset(lbl_1_bss_3F0[temp_r30].unk0, 0, lbl_1_bss_3F0[temp_r30].unkC);
    }
    object->model[5] = Hu3DHookFuncCreate(fn_1_33A4);
    Hu3DModelLayerSet(object->model[5], 3);
    Hu3DModelCameraSet(object->model[5], 2);
    object->model[6] = Hu3DHookFuncCreate(fn_1_349C);
    Hu3DModelLayerSet(object->model[6], 3);
    Hu3DModelCameraSet(object->model[6], 4);
    object->model[7] = Hu3DHookFuncCreate(fn_1_3594);
    Hu3DModelLayerSet(object->model[7], 5);
    Hu3DModelCameraSet(object->model[7], 4);
    temp_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M434, 0x0B));
    object->model[10] = Hu3DParticleCreate(temp_r26, 100);
    Hu3DParticleHookSet(object->model[10], fn_1_443C);
    Hu3DModelAttrSet(object->model[10], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(object->model[10], 4);
    Hu3DModelCameraSet(object->model[10], 8);
    object->func = fn_1_26A4;
}

HsfAttribute *fn_1_2608(s16 model, char *name)
{
    HsfData *temp_r31;
    HsfAttribute *temp_r30;
    s32 temp_r29;
    ModelData *temp_r28;
    HsfBitmap *temp_r27;
    temp_r28 = &Hu3DData[model];
    temp_r31 = temp_r28->hsfData;
    temp_r30 = temp_r31->attribute;
    for (temp_r29 = 0; temp_r29 < temp_r31->attributeCnt; temp_r29++, temp_r30++) {
        temp_r27 = temp_r30->bitmap;
        if (strcmp(name, temp_r27->name) == 0) {
            break;
        }
    }
    if (temp_r29 >= temp_r31->attributeCnt) {
        return NULL;
    }
    return temp_r30;
}

void fn_1_26A4(omObjData *object)
{
    s32 temp_r31;
    Bss2468Data *temp_r30;
    HsfVector2f *temp_r29;
    HsfAttribute *temp_r27;
    Vec *temp_r25;
    s32 temp_r23;
    s32 temp_r22;
    Bss2468Data *sp8[64];

    temp_r27 = fn_1_2608(object->model[1], "sora");
    if (temp_r27 != NULL) {
        temp_r27->unk30 += 0.0001f;
        temp_r27->unk34 -= 0.00005f;
    }
    temp_r30 = lbl_1_bss_2468;
    temp_r22 = 0;
    for (temp_r31 = 0; temp_r31 < 64; temp_r31++, temp_r30++) {
        if (temp_r30->unkC) {
            sp8[temp_r22++] = temp_r30;
        }
    }
    temp_r25 = lbl_1_bss_2868;
    temp_r29 = lbl_1_bss_464;
    for (temp_r31 = 0; temp_r31 < 32; temp_r31++) {
        for (temp_r23 = 0; temp_r23 < 32; temp_r23++, temp_r25++, temp_r29++) {
            temp_r25->y = -15.000001f + (2.0f * sind(temp_r29->x));
            temp_r29->x += temp_r29->y;
        }
    }
    DCFlushRangeNoSync(lbl_1_bss_2868, sizeof(lbl_1_bss_2868));
    for (temp_r31 = 0; temp_r31 < temp_r22; temp_r31++) {
        temp_r30 = sp8[temp_r31];
        temp_r30->unkC--;
    }
    CenterM[1].y = -15.000001f + (-CenterM[2].y);
    CRotM[1].x = -CRotM[2].x;
}

void fn_1_28F0(void)
{
    s32 temp_r31;
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        if (lbl_1_bss_3F0[temp_r31].unk0 != NULL) {
            HuMemDirectFree(lbl_1_bss_3F0[temp_r31].unk0);
            lbl_1_bss_3F0[temp_r31].unk0 = NULL;
        }
    }
}

GXColor lbl_1_data_139 = { 255, 255, 255, 64 };

float lbl_1_data_140[2][3] = { 0.012f, 0, 0, 0, 0.012f, 0 };

float lbl_1_data_158[2][3] = { 0, 0, 0.5f, 0, 0.5f, 0 };

void fn_1_2978(ModelData *model, Mtx mtx)
{
    float temp_f31;

    Mtx sp1AC;
    Mtx sp17C;
    Mtx sp14C;
    Mtx sp11C;
    Mtx spEC;
    Mtx spBC;
    Mtx sp8C;
    Mtx sp5C;
    Mtx sp2C;
    GXTexObj spC;
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetNumTexGens(4);
    GXInitTexObj(&spC, lbl_1_bss_3F0[2].unk0, lbl_1_bss_3F0[2].unk8, lbl_1_bss_3F0[2].unkA, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&spC, GX_TEXMAP0);
    GXInitTexObj(&spC, lbl_1_bss_3F0[1].unk0, lbl_1_bss_3F0[1].unk8, lbl_1_bss_3F0[1].unkA, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&spC, GX_TEXMAP1);
    MTXLightPerspective(sp1AC, 30.0f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, spBC);
    MTXConcat(spBC, mtx, spBC);
    MTXConcat(sp1AC, Hu3DCameraMtx, sp8C);
    MTXConcat(sp8C, spBC, spBC);
    GXLoadTexMtxImm(spBC, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0);
    MTXLightPerspective(sp1AC, 30.0f, 1.2f, 0.5f, 0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, sp5C);
    MTXConcat(sp5C, mtx, sp5C);
    MTXConcat(sp1AC, Hu3DCameraMtx, sp2C);
    MTXConcat(sp2C, sp5C, sp5C);
    GXLoadTexMtxImm(sp5C, GX_TEXMTX1, GX_MTX3x4);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX1);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColor(GX_TEVSTAGE1, lbl_1_data_139);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    HuSprTexLoad(lbl_1_bss_45C, 0, GX_TEXMAP2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXInitTexObj(&spC, lbl_1_bss_3F0[0].unk0, lbl_1_bss_3F0[0].unk8, lbl_1_bss_3F0[0].unkA, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&spC, GX_TEXMAP3);
    GXSetNumIndStages(2);
    MTXRotDeg(sp11C, 'X', -90.0f);
    temp_f31 = 1.0f / 600.0f;
    MTXScale(sp14C, temp_f31, temp_f31, temp_f31);
    MTXConcat(sp14C, sp11C, sp17C);
    sp17C[0][1] = -0.03f;
    GXLoadTexMtxImm(sp17C, GX_TEXMTX2, GX_MTX2x4);
    GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_POS, GX_TEXMTX2);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD2, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_0, lbl_1_data_140, 0);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    MTXRotDeg(sp11C, 'X', -90.0f);
    temp_f31 = 1.0f / 1200.0f;
    MTXScale(sp14C, temp_f31, temp_f31, temp_f31);
    MTXConcat(sp14C, sp11C, sp17C);
    MTXTrans(spEC, 0.5f, 0.5f, 0.0f);
    MTXConcat(spEC, sp17C, sp17C);
    GXLoadTexMtxImm(sp17C, GX_TEXMTX3, GX_MTX2x4);
    GXSetTexCoordGen(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_POS, GX_TEXMTX3);
    GXSetIndTexOrder(GX_INDTEXSTAGE1, GX_TEXCOORD3, GX_TEXMAP3);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_1, lbl_1_data_158, 0);
    GXSetTevIndWarp(GX_TEVSTAGE1, GX_INDTEXSTAGE1, GX_TRUE, GX_FALSE, GX_ITM_1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSETARRAY(GX_VA_POS, lbl_1_bss_2868, sizeof(lbl_1_bss_2868), sizeof(Vec));
    GXSetCullMode(GX_CULL_BACK);
    GXCallDisplayList(lbl_1_bss_450.unk0, lbl_1_bss_450.unk4);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
#ifdef TARGET_PC
    GXDestroyTexObj(&spC);
#endif
}

void fn_1_3004(void)
{
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    GXBeginDisplayList(lbl_1_bss_450.unk0, lbl_1_bss_450.unk4);
    for (temp_r30 = 0; temp_r30 < 31; temp_r30++) {
        temp_r29 = temp_r30 * 32;
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 64);
        if (temp_r30 & 0x1) {
            for (temp_r31 = 0; temp_r31 < 32; temp_r31++) {
                GXPosition1x16(temp_r29 + temp_r31 + 32);
                GXPosition1x16(temp_r29 + temp_r31);
            }
        }
        else {
            for (temp_r31 = 31; temp_r31 >= 0; temp_r31--) {
                GXPosition1x16(temp_r29 + temp_r31);
                GXPosition1x16(temp_r29 + temp_r31 + 32);
            }
        }
    }
    lbl_1_bss_450.unk4 = GXEndDisplayList();
    DCFlushRangeNoSync(lbl_1_bss_450.unk0, lbl_1_bss_450.unk4);
}

void fn_1_3128(void)
{
    GXBeginDisplayList(lbl_1_bss_440.unk0, lbl_1_bss_440.unk4);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2f32(-0.5f, -0.5f);
    GXTexCoord2f32(0, 0);
    GXPosition2f32(0.5f, -0.5f);
    GXTexCoord2f32(1, 0);
    GXPosition2f32(0.5f, 0.5f);
    GXTexCoord2f32(1, 1);
    GXPosition2f32(-0.5f, 0.5f);
    GXTexCoord2f32(0, 1);
    GXEnd();
    lbl_1_bss_440.unk4 = GXEndDisplayList();
    DCFlushRangeNoSync(lbl_1_bss_440.unk0, lbl_1_bss_440.unk4);
}

void fn_1_32DC(Bss3F0Data *arg0, GXBool arg1)
{
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);
    GXSetTexCopySrc(0, 0, arg0->unk4, arg0->unk6);
    GXSetTexCopyDst(arg0->unk8, arg0->unkA, GX_TF_RGB565, arg0->unk10);
    GXSetCopyClear(BGColor, 0xFFFFFF);
    GXCopyTex(arg0->unk0, arg1);
    GXPixModeSync();
    DCFlushRange(arg0->unk0, arg0->unkC);
}

void fn_1_33A4(ModelData *model, Mtx mtx)
{
    fn_1_32DC(&lbl_1_bss_3F0[1], GX_TRUE);
}

void fn_1_349C(ModelData *model, Mtx mtx)
{
    fn_1_32DC(&lbl_1_bss_3F0[2], GX_TRUE);
}

void fn_1_3594(ModelData *model, Mtx mtx)
{
    Mtx sp90;
    Mtx sp60;
    Mtx sp30;
    GXTexObj sp10;

    fn_1_32DC(&lbl_1_bss_3F0[3], GX_FALSE);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    MTXLightPerspective(sp90, 30.0f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, sp60);
    MTXConcat(sp60, mtx, sp60);
    MTXConcat(sp90, Hu3DCameraMtx, sp30);
    MTXConcat(sp30, sp60, sp60);
    GXLoadTexMtxImm(sp60, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXInitTexObj(&sp10, lbl_1_bss_3F0[2].unk0, lbl_1_bss_3F0[2].unk8, lbl_1_bss_3F0[2].unkA, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&sp10, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-1000.0f, -5.000001f, -1000.0f);
    GXPosition3f32(1000.0f, -5.000001f, -1000.0f);
    GXPosition3f32(1000.0f, -5.000001f, 1000.0f);
    GXPosition3f32(-1000.0f, -5.000001f, 1000.0f);
    GXEnd();
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-1000.0f, -70.0f, -1000.0f);
    GXPosition3f32(1000.0f, -70.0f, -1000.0f);
    GXPosition3f32(1000.0f, -70.0f, 1000.0f);
    GXPosition3f32(-1000.0f, -70.0f, 1000.0f);
    GXEnd();
    fn_1_32DC(&lbl_1_bss_3F0[2], GX_FALSE);
    GXInitTexObj(&sp10, lbl_1_bss_3F0[3].unk0, lbl_1_bss_3F0[3].unk8, lbl_1_bss_3F0[3].unkA, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&sp10, GX_TEXMAP0);
    GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-1000.0f, -5.000001f, -1000.0f);
    GXPosition3f32(1000.0f, -5.000001f, -1000.0f);
    GXPosition3f32(1000.0f, -5.000001f, 1000.0f);
    GXPosition3f32(-1000.0f, -5.000001f, 1000.0f);
    GXEnd();
#ifdef TARGET_PC
    GXDestroyTexObj(&sp10);
#endif
}

GXColor lbl_1_data_170 = { 255, 0, 0, 255 };
GXColor lbl_1_data_174 = { 255, 255, 255, 32 };
GXColor lbl_1_data_178 = { 0, 126, 126, 255 };

void fn_1_3CC8(ModelData *model, Mtx mtx)
{

    float temp_f31;
    Mtx sp44;
    Mtx sp14;
    Bss2468Data *temp_r31;
    s32 temp_r30;
    s32 temp_r29;

    MTXOrtho(sp44, 0, 480, 0, 640, 0, 100);
    GXSetProjection(sp44, GX_ORTHOGRAPHIC);
    MTXIdentity(sp14);
    GXLoadPosMtxImm(sp14, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_178);
    GXSetNumTexGens(0);
    HuSprTexLoad(lbl_1_bss_458, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetScissor(0, 0, lbl_1_bss_3F0[0].unk8, lbl_1_bss_3F0[0].unkA);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2u16(0, 0);
    GXPosition2u16(lbl_1_bss_3F0[0].unk8, 0);
    GXPosition2u16(lbl_1_bss_3F0[0].unk8, lbl_1_bss_3F0[0].unkA);
    GXPosition2u16(0, lbl_1_bss_3F0[0].unkA);
    GXEnd();
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetNumTevStages(1);

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXClearVtxDesc();

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    temp_r29 = lbl_1_bss_2464;
    for (temp_r30 = 0; temp_r30 < 64; temp_r29 = (temp_r29 + 1) % 64, temp_r30++) {
        temp_r31 = &lbl_1_bss_2468[temp_r29];
        if (temp_r31->unkC == 0) {
            continue;
        }
        temp_f31 = (0.2f + cosd((90.0f * temp_r31->unkC) / REFRESH_RATE)) * 128.0f;
        lbl_1_data_174.a = 255.0f * sind((90.0f * temp_r31->unkC) / REFRESH_RATE);
        GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_174);
        MTXScale(sp14, 0.5f * temp_f31, 0.5f * temp_f31, 1.0f);
        mtxTransCat(sp14, (200.0f * (600.0f + temp_r31->unk0.x)) / 1200.0f, (200.0f * (600.0f + temp_r31->unk0.z)) / 1200.0f, 0);
        GXLoadPosMtxImm(sp14, GX_PNMTX0);
        GXCallDisplayList(lbl_1_bss_440.unk0, lbl_1_bss_440.unk4);
    }
    fn_1_32DC(&lbl_1_bss_3F0[0], GX_TRUE);
}

void fn_1_43AC(Vec *arg0)
{
    Bss2468Data *temp_r31;
    temp_r31 = &lbl_1_bss_2468[lbl_1_bss_2464];
    if (temp_r31->unkC == 0) {
        temp_r31->unk0.x = arg0->x;
        temp_r31->unk0.y = arg0->y;
        temp_r31->unk0.z = arg0->z;
        temp_r31->unkC = REFRESH_RATE;
        lbl_1_bss_2464 = (lbl_1_bss_2464 + 1) % 64;
        return;
    }
}

void fn_1_443C(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    if (particle->unk_00 == 0) {
        particle->unk_00 = 1;
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r31++, temp_r29++) {
            temp_r31->unk2C = 10;
            temp_f31 = ((1.0f / 256.0f) * frand8()) * 360.0f;
            temp_r31->unk34.x = (0.2f * sind(temp_f31)) * 100.0f;
            temp_r31->unk34.y = 0;
            temp_r31->unk34.z = (0.2f * cosd(temp_f31)) * 100.0f;
            temp_f30 = (100.0f * (0.025f * ((1.0f / 256.0f) * frand8()))) + 2.5f;
            temp_r31->unk08.x = temp_f30 * sind(temp_f31);
            temp_r31->unk08.y = (100.0f * (0.025f * (((1.0f / 256.0f) * (s32)(frand() & 0x1FF)) - 1.0f))) + 7.5000005f;
            temp_r31->unk08.z = temp_f30 * cosd(temp_f31);
            temp_r31->unk40.r = temp_r31->unk40.g = temp_r31->unk40.b = 255;
            temp_r31->unk40.a = (frand() & 0x1F) + 16;
        }
    }
    temp_r28 = 0;
    temp_r31 = particle->unk_48;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk40.a == 0) {
            temp_r28++;
            continue;
        }
        temp_r31->unk34.x += temp_r31->unk08.x;
        temp_r31->unk34.y += temp_r31->unk08.y;
        temp_r31->unk34.z += temp_r31->unk08.z;
        temp_r31->unk08.y += -0.5f;
        temp_r31->unk40.a--;
    }
    if (temp_r28 == particle->unk_30) {
        model->attr |= 0x1;
    }
    DCStoreRangeNoSync(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_47EC(Vec *arg0)
{
    Hu3DModelPosSet(lbl_1_bss_5868->model[10], arg0->x, arg0->y, arg0->z);
    Hu3DModelAttrReset(lbl_1_bss_5868->model[10], HU3D_ATTR_DISPOFF);
}
