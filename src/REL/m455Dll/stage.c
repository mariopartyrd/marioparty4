#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/objsub.h"


#include "game/hsfmotion.h"

#include "game/frand.h"
#include "game/sprite.h"

#include "REL/m455Dll.h"

#include "ext_math.h"
#include "math.h"

Process *lbl_1_bss_70;
omObjData *lbl_1_bss_6C;
omObjData *lbl_1_bss_68;
omObjData *lbl_1_bss_64;
omObjData *lbl_1_bss_60;
omObjData *lbl_1_bss_5C;
omObjData *lbl_1_bss_58;
Vec lbl_1_bss_4C;

typedef struct struct_bss48 {
    AnimData *unk0[4];
    s32 unk10[4];
    Vec unk20;
} StructBss48;

StructBss48 *lbl_1_bss_48;

Vec lbl_1_data_1D8[4] = {
    { -460, 0, 150 },
    { 460, 0, 150 },
    { -460, 0, -150 },
    { 460, 0, -150 },
};

GXColor lbl_1_data_208 = { 255, 255, 255, 255 };

typedef struct struct_data20C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    BOOL unk10;
} StructData20C;

StructData20C lbl_1_data_20C[4] = {
    { 400, 400, 400, 400, FALSE },
    { 640, 480, 320, 240, TRUE },
    { 640, 480, 640, 480, FALSE },
    { 640, 480, 320, 240, TRUE },
};

void fn_1_8EAC(void);

void fn_1_6914(omObjData *object);
void fn_1_7280(omObjData *object);
void fn_1_75C0(omObjData *object);
void fn_1_7C48(omObjData *object);
void fn_1_891C(omObjData *object);

omObjData *fn_1_347C(void);

void fn_1_32C4(Process *objman)
{
    lbl_1_bss_70 = objman;
    fn_1_8EAC();
    lbl_1_bss_68 = omAddObjEx(lbl_1_bss_70, 50, 0, 0, -1, fn_1_6914);
    lbl_1_bss_64 = omAddObjEx(lbl_1_bss_70, 50, 8, 0, -1, fn_1_7280);
    lbl_1_bss_60 = omAddObjEx(lbl_1_bss_70, 50, 1, 0, -1, fn_1_75C0);
    lbl_1_bss_5C = omAddObjEx(lbl_1_bss_70, 50, 0, 0, -1, fn_1_7C48);
    lbl_1_bss_58 = omAddObjEx(lbl_1_bss_70, 50, 0, 0, -1, fn_1_891C);
    lbl_1_bss_6C = fn_1_347C();
}

void fn_1_4104(omObjData *object);

void fn_1_6C60(omObjData *object);
void fn_1_7430(omObjData *object);
void fn_1_7974(omObjData *object);
void fn_1_8474(omObjData *object);

void fn_1_9168(void);

void fn_1_340C(void)
{
    fn_1_4104(lbl_1_bss_6C);
    fn_1_9168();
    fn_1_6C60(lbl_1_bss_68);
    fn_1_7430(lbl_1_bss_64);
    fn_1_7974(lbl_1_bss_60);
    fn_1_8474(lbl_1_bss_5C);
}

typedef struct work_347C_unk4 {
    void *unk0;
    u32 unk4;
    BOOL unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Work347CUnk4;

typedef struct work_347C_unk74 {
    Vec unk0;
    Vec unkC;
    float unk18;
    u16 unk1C;
    u16 unk1E;
} Work347CUnk74;

typedef struct work_347C {
    s32 unk0;
    Work347CUnk4 unk4[4];
    Work347CUnk74 unk74[64];
    float unk874[26][2];
    float unk944[26][2];
    void *unkA14;
    u32 unkA18;
    AnimData *unkA1C[9];
    float unkA40;
    float unkA44;
    u32 unkA48;
    u32 unkA4C;
    u32 unkA50;
    float unkA54;
    float unkA58;
} Work347C;

void fn_1_3DDC(omObjData *object);

void fn_1_4180(ModelData *model, Mtx matrix);
void fn_1_49AC(ModelData *model, Mtx matrix);
void fn_1_4E64(ModelData *model, Mtx matrix);

omObjData *fn_1_347C(void)
{
    omObjData *object = omAddObjEx(lbl_1_bss_70, 127, 15, 0, -1, fn_1_3DDC);
    Work347C *work = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work347C), MEMORY_DEFAULT_NUM);
    Work347C *work2 = work;
    Work347CUnk74 *workUnk74 = &work->unk74[0];
    Work347CUnk4 *workUnk4;
    s32 id;
    ModelData *modelP;
    s32 i;

    work->unkA40 = 0;
    work->unkA44 = 0;
    work->unkA48 = 0;
    work->unkA4C = 0;
    work->unkA50 = 0;
    work->unkA54 = 0;
    work->unkA58 = 0;

    object->model[0] = id = Hu3DHookFuncCreate(fn_1_4E64);
    Hu3DModelCameraSet(id, HU3D_CAM0);
    Hu3DModelLayerSet(id, 5);
    modelP = &Hu3DData[id];
    modelP->unk_120 = work;
    work->unkA1C[4] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 21), MEMORY_DEFAULT_NUM));
    work->unkA1C[5] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 22), MEMORY_DEFAULT_NUM));
    work->unkA1C[6] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 23), MEMORY_DEFAULT_NUM));
    work->unkA1C[7] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 24), MEMORY_DEFAULT_NUM));
    work->unkA1C[0] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 17), MEMORY_DEFAULT_NUM));
    work->unkA1C[1] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 18), MEMORY_DEFAULT_NUM));
    work->unkA1C[2] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 19), MEMORY_DEFAULT_NUM));
    work->unkA1C[3] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 20), MEMORY_DEFAULT_NUM));
    work->unkA1C[8] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 25), MEMORY_DEFAULT_NUM));
    object->model[1] = id = Hu3DHookFuncCreate(fn_1_4180);
    Hu3DModelCameraSet(id, HU3D_CAM0);
    Hu3DModelLayerSet(id, 0);
    modelP = &Hu3DData[id];
    modelP->unk_120 = work;
    work2->unkA18 = 16384;
    work2->unkA14 = HuMemDirectMallocNum(HEAP_SYSTEM, work2->unkA18, MEMORY_DEFAULT_NUM);
    DCFlushRange(work2->unkA14, 16384);
    GXBeginDisplayList(work2->unkA14, work2->unkA18);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2f32(-0.5f, -0.5f);
    GXTexCoord2f32(0, 0);
    GXPosition2f32(0.5f, -0.5f);
    GXTexCoord2f32(1, 0);
    GXPosition2f32(0.5f, 0.5f);
    GXTexCoord2f32(1, 1);
    GXPosition2f32(-0.5f, 0.5f);
    GXTexCoord2f32(0, 1);
    work2->unkA18 = GXEndDisplayList();
    for (i = 0; i < 26; i++) {
        work2->unk874[i][0] = 0;
        work2->unk874[i][1] = 0;
        work2->unk944[i][0] = 0;
        work2->unk944[i][1] = 0;
    }

    object->model[3] = id = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M455, 5));
    Hu3DModelPosSet(id, 0, 0, -5000);
    Hu3DModelScaleSet(id, 2, 2, 2);
    Hu3DModelCameraSet(id, HU3D_CAM0);
    Hu3DModelLayerSet(id, 1);
    id = Hu3DTexScrollCreate(object->model[3], "S3TCsk");
    Hu3DTexScrollPosMoveSet(id, -0.00009166667f, 0, 0);
    id = Hu3DTexScrollCreate(object->model[3], "pa_sk3");
    Hu3DTexScrollPosMoveSet(id, -0.00020833335f, 0, 0);

    object->model[4] = id = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M455, 6));
    Hu3DModelPosSet(id, 0, 0, -3000);
    Hu3DModelScaleSet(id, 1.2f, 1.2f, 1.2f);
    Hu3DModelCameraSet(id, HU3D_CAM0);
    Hu3DModelLayerSet(id, 1);

    object->model[8] = id = Hu3DHookFuncCreate(fn_1_49AC);
    Hu3DModelCameraSet(id, HU3D_CAM0);
    Hu3DModelLayerSet(id, 2);
    modelP = &Hu3DData[id];
    modelP->unk_120 = work;

    object->model[10] = id = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M455, 0));
    Hu3DModelPosSet(id, 0, 0, 0);
    Hu3DModelCameraSet(id, HU3D_CAM0);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelShadowMapSet(object->model[10]);
    for (i = 0; i < 4; i++) {

        object->model[i + 11] = id = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M455, 1));
        Hu3DModelCameraSet(object->model[i + 11], HU3D_CAM0);
        Hu3DModelLayerSet(object->model[i + 11], 3);
        Hu3DModelPosSet(object->model[i + 11], lbl_1_data_1D8[i].x, lbl_1_data_1D8[i].y, lbl_1_data_1D8[i].z);
        Hu3DModelAttrSet(object->model[i + 11], HU3D_MOTATTR_SHAPE_LOOP);
        Hu3DMotionShapeTimeSet(object->model[i + 11], (0.25 * i) * Hu3DMotionShapeMaxTimeGet(object->model[i + 11]));
    }
    modelP = &Hu3DData[object->model[0]];
    workUnk4 = &work2->unk4[0];
    for (i = 0; i < 4; i++, workUnk4++) {
        workUnk4->unkC = lbl_1_data_20C[i].unk0;
        workUnk4->unk10 = lbl_1_data_20C[i].unk4;
        workUnk4->unk14 = lbl_1_data_20C[i].unk8;
        workUnk4->unk18 = lbl_1_data_20C[i].unkC;
        workUnk4->unk8 = lbl_1_data_20C[i].unk10;
        workUnk4->unk4 = GXGetTexBufferSize(workUnk4->unk14, workUnk4->unk18, GX_TF_RGB565, GX_FALSE, GX_FALSE);
        workUnk4->unk0 = HuMemDirectMallocNum(HEAP_DATA, workUnk4->unk4, modelP->unk_48);
        memset(workUnk4->unk0, 0, workUnk4->unk4);
        DCFlushRange(workUnk4->unk0, workUnk4->unk4);
    }
    for (i = 0; i < 64; i++, workUnk74++) {
        workUnk74->unk0.x = workUnk74->unk0.y = workUnk74->unk0.z = 0;
        workUnk74->unkC.x = 0;
        workUnk74->unkC.y = 0;
        workUnk74->unkC.z = 1;
        workUnk74->unk18 = 0.016666668f;
        workUnk74->unk1C = 60;
        workUnk74->unk1E = 0;
    }
    return object;
}

void fn_1_9CFC(float arg0);

void fn_1_3DDC(omObjData *object)
{
    Work347C *work = object->data;
    Work347C *work2 = work;
    s32 i;
    if ((work->unkA50 = work->unkA50 + (0.007874016f * ((s32)frand() & 0x7F) * 3.0f)) > 360) {
        work->unkA50 -= 360;
    }
    work->unkA44 = (25 + work->unkA40) + (5.0 * sind(work->unkA50));
    Hu3DModelPosSet(object->model[10], 0, work->unkA44, 0);
    for (i = 0; i < 4; i++) {
        Hu3DModelPosSet(object->model[i + 11], lbl_1_data_1D8[i].x, work->unkA44 + lbl_1_data_1D8[i].y, lbl_1_data_1D8[i].z);
    }
    work->unkA54 += 0.001f;
    work->unkA58 += 0.001f;
    work->unkA48++;
    work->unkA4C++;
    if (work->unkA4C >= 60.0f && work->unkA4C <= 81.0f) {
        float time = 1 - ((work->unkA4C - 60.0f) / 21.0f);
        if (time < 0.0f) {
            time = 0.0f;
        }
        fn_1_9CFC(time);
    }
}

void fn_1_4104(omObjData *object)
{
    Work347C *work = object->data;
    HuSprAnimKill(work->unkA1C[0]);
    HuSprAnimKill(work->unkA1C[1]);
    HuSprAnimKill(work->unkA1C[2]);
    HuSprAnimKill(work->unkA1C[3]);
    HuSprAnimKill(work->unkA1C[6]);
    HuSprAnimKill(work->unkA1C[7]);
    HuSprAnimKill(work->unkA1C[4]);
    HuSprAnimKill(work->unkA1C[5]);
    HuSprAnimKill(work->unkA1C[8]);
}

GXColor lbl_1_data_26A = { 255, 255, 255, 32 };
GXColor lbl_1_data_26E = { 255, 255, 255, 10 };
GXColor lbl_1_data_272 = { 0, 126, 126, 255 };
Vec lbl_1_data_278[4] = { -1000, 50, 1000, -1000, 50, -1000, 1000, 50, -1000, 1000, 50, 1000 };

Vec lbl_1_data_2A8[26] = { -1500, 0, 1000, -1400, 0, 1000, 0, 0, 1000, 1400, 0, 1000, 1500, 0, 1000, -1500, 0, -500, -1400, 0, -500, 0, 0, -500, 1400,
    0, -500, 1500, 0, -500, -1500, 0, -2000, -1400, 0, -2000, 0, 0, -2000, 1400, 0, -2000, 1500, 0, -2000, -1500, 0, -5000, -1400, 0, -5000, 0, 0,
    -5000, 1400, 0, -5000, 1500, 0, -5000, -2000, 0, -500, -2500, 0, -2000, -3000, 0, -5000, 2000, 0, -500, 2500, 0, -2000, 3000, 0, -5000 };

GXColor lbl_1_data_3E0[26] = { { 96, 128, 255, 255 }, { 128, 160, 255, 32 }, { 128, 160, 255, 32 }, { 128, 160, 255, 32 }, { 96, 128, 255, 255 },
    { 24, 48, 255, 255 }, { 96, 128, 255, 32 }, { 128, 160, 255, 32 }, { 96, 128, 255, 32 }, { 24, 48, 255, 255 }, { 24, 48, 255, 255 },
    { 24, 48, 255, 255 }, { 96, 128, 255, 255 }, { 24, 48, 255, 255 }, { 24, 48, 255, 255 }, { 8, 24, 143, 255 }, { 8, 24, 143, 255 },
    { 8, 24, 143, 255 }, { 8, 24, 143, 255 }, { 8, 24, 143, 255 }, { 24, 48, 255, 255 }, { 24, 48, 255, 255 }, { 24, 48, 255, 255 },
    { 24, 48, 255, 255 }, { 24, 48, 255, 255 }, { 24, 48, 255, 255 } };

float lbl_1_data_448[26][2]
    = { 0, 1, 0.033333335, 1, 0.5, 1, 0.96666664, 1, 1, 1, 0, 0.5, 0.033333335, 0.5, 0.5, 0.5, 0.96666664, 0.5, 1, 0.5, 0, 0, 0.033333335, 0, 0.5, 0,
          0.96666664, 0, 1, 0, 0, 0, 0.033333335, 0, 0.5, 0, 0.96666664, 0, 1, 0, -0.15, 0.5, -0.33, 0, -0.49, 0, 1.15, 0.5, 1.33, 0, 1.49, 0 };

float lbl_1_data_518[26][2] = { 0, 30, 0.5, 30, 7.5, 30, 14.5, 30, 15, 30, 0, 15, 0.5, 15, 7.5, 15, 14.5, 15, 15, 15, 0, 7.5, 0.5, 7.5, 7.5, 7.5,
    14.5, 7.5, 15, 7.5, 0, 0, 0.5, 0, 7.5, 0, 14.5, 0, 15, 0, -2.25, 15, -4.9500003, 7.5, -7.3500004, 0, 17.25, 15, 19.95, 7.5, 22.35, 0 };

float lbl_1_data_5E8[2][3] = { 0, 0, 0.5, 0, 0.5, 0 };

GXColor lbl_1_data_600 = { 80, 80, 80, 80 };

Vec lbl_1_data_604[9]
    = { -1500, 0, -5000, 0, 0, -5000, 1500, 0, -5000, -1500, 0, -3000, 0, 0, -3000, 1500, 0, -3000, -1500, 0, 1000, 0, 0, 1000, 1500, 0, 1000 };

GXColor lbl_1_data_670[9] = {
    { 255, 255, 255, 0 },
    { 255, 255, 255, 0 },
    { 255, 255, 255, 0 },
    { 255, 255, 255, 0 },
    { 255, 255, 255, 255 },
    { 255, 255, 255, 0 },
    { 255, 255, 255, 0 },
    { 255, 255, 255, 255 },
    { 255, 255, 255, 0 },
};

GXColor lbl_1_data_694 = { 255, 165, 89, 178 };
GXColor lbl_1_data_698 = { 153, 114, 89, 178 };
GXColor lbl_1_data_69C = { 0, 0, 0, 255 };

void fn_1_6088(Work347CUnk4 *arg0, s32 arg1);

void fn_1_4180(ModelData *model, Mtx matrix)
{
    Work347C *work = model->unk_120;
    Work347C *work2 = work;
    Work347CUnk74 *workUnk74 = &work2->unk74[0];
    Work347CUnk4 *workUnk4 = &work2->unk4[0];
    s32 i;
    Mtx proj;
    Mtx modelview;
    MTXOrtho(proj, 0, 480, 0, 640, 0, 100);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    MTXIdentity(modelview);
    GXLoadPosMtxImm(modelview, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_272);
    GXSetTevColor(GX_TEVREG0, lbl_1_data_26E);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetScissor(0, 0, 400, 400);
    HuSprTexLoad(work->unkA1C[4], 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2u16(0, 0);
    GXTexCoord2f32(work->unkA54, work->unkA58);
    GXPosition2u16(400, 0);
    GXTexCoord2f32(work->unkA54 + 7, work->unkA58);
    GXPosition2u16(400, 400);
    GXTexCoord2f32(work->unkA54 + 7, work->unkA58 + 7);
    GXPosition2u16(0, 400);
    GXTexCoord2f32(work->unkA54, work->unkA58 + 7);
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
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    HuSprTexLoad(work->unkA1C[8], 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    workUnk74 = &work2->unk74[0];
    for (i = 0; i < 64; i++, workUnk74++) {
        float scale;
        float accel;
        if (workUnk74->unk1E == 0) {
            continue;
        }
        scale = 128 * (workUnk74->unkC.x * (0.2f + cosd(workUnk74->unk1E * workUnk74->unk18 * 90.0f)));
        accel = workUnk74->unk1E * workUnk74->unk18;
        lbl_1_data_26A.a = workUnk74->unkC.z * sind((accel * accel) * 90.0f) * 255.0;
        GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_26A);
        MTXScale(modelview, 0.5f * scale, 0.5f * scale, 1.0f);
        mtxRotCat(modelview, 0, 0, workUnk74->unkC.y);
        mtxTransCat(modelview, 400 * (workUnk74->unk0.x + 1500) / 3000, 400 * (workUnk74->unk0.z - -2000) / 3000, 0);
        GXLoadPosMtxImm(modelview, GX_PNMTX0);
        GXCallDisplayListNative(work2->unkA14, work2->unkA18);
        if (!omPauseChk()) {
            workUnk74->unk1E--;
        }
    }
    workUnk4 = &work2->unk4[0];
    fn_1_6088(workUnk4, 1);
}

void fn_1_59A0(ModelData *model, Mtx matrix);

void fn_1_49AC(ModelData *model, Mtx matrix)
{
    Work347C *work;
    Work347C *work2;
    Work347CUnk4 *workUnk4;
    fn_1_59A0(model, matrix);
    work = model->unk_120;
    work2 = work;
    workUnk4 = &work2->unk4[1];
    fn_1_6088(workUnk4, 0);
}

void fn_1_6144(Work347CUnk4 *arg0, float arg1, float arg2, float arg3);

void fn_1_4A14(ModelData *model, Mtx matrix)
{
    Work347C *work = model->unk_120;
    Work347C *work2 = work;
    Work347CUnk4 *workUnk4 = &work2->unk4[0];

    fn_1_6144(workUnk4, 200, 0, 0.5f);
    workUnk4 = &work2->unk4[1];
    fn_1_6144(workUnk4, 0, 0, 0.5f);
    workUnk4 = &work2->unk4[2];
    fn_1_6144(workUnk4, 0, 150, 0.25f);
    workUnk4 = &work2->unk4[3];
    fn_1_6144(workUnk4, 0, 300, 0.5f);
}

void fn_1_6594(s16 arg0, Work347CUnk4 *arg1, GXTexWrapMode arg2, s32 arg3, BOOL arg4);

void fn_1_4B1C(ModelData *model, Mtx matrix)
{
    CameraData *cameraP = &Hu3DCamera[Hu3DCameraNo];
    Work347C *work = model->unk_120;
    Work347C *work2 = work;
    Work347CUnk4 *workUnk4 = &work2->unk4[2];
    float fov;
    Mtx proj;
    Mtx texMtx;
    Mtx projCamera;
    s16 lightMask;
    s16 i;

    fn_1_6088(workUnk4, 0);
    GXLoadPosMtxImm(matrix, GX_PNMTX0);
    fov = cameraP->fov;
    if (fov <= 0.0f) {
        fov = 45;
    }
    MTXLightPerspective(proj, fov, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, texMtx);
    MTXConcat(texMtx, Hu3DCameraMtx, texMtx);
    MTXConcat(proj, Hu3DCameraMtx, projCamera);
    MTXConcat(projCamera, texMtx, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0);
    lightMask = Hu3DLightSet(model, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, 4);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_208);
    GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    workUnk4 = &work2->unk4[1];
    fn_1_6594(0, workUnk4, 0, 0, 0);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSETARRAY(GX_VA_POS, lbl_1_data_278, sizeof(lbl_1_data_278), sizeof(Vec));
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition1x16(i);
    }
    GXEnd();
    workUnk4 = &work2->unk4[3];
    fn_1_6088(workUnk4, 0);
    workUnk4 = &work2->unk4[2];
    fn_1_6594(0, workUnk4, 0, 0, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition1x16(i);
    }
    GXEnd();
}

void fn_1_4E64(ModelData *model, Mtx matrix)
{
    CameraData *cameraP = &Hu3DCamera[Hu3DCameraNo];
    Work347C *work = model->unk_120;
    Work347C *work2 = work;
    Work347CUnk4 *workUnk4 = &work2->unk4[2];
    Mtx invXPose;
    Mtx proj;
    Mtx texMtx;
    Mtx projCamera;
    float sp14;
    float sp10;
    float fov;
    s16 i;
    fn_1_4B1C(model, matrix);
    sp14 = 1.5f;
    sp10 = 0;
    GXLoadPosMtxImm(matrix, GX_PNMTX0);
    MTXInvXpose(matrix, invXPose);
    GXLoadNrmMtxImm(invXPose, GX_PNMTX0);
    fov = cameraP->fov;
    if (fov <= 0.0f) {
        fov = 45;
    }
    MTXLightPerspective(proj, fov, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, texMtx);
    MTXConcat(texMtx, Hu3DCameraMtx, texMtx);
    MTXConcat(proj, Hu3DCameraMtx, projCamera);
    MTXConcat(projCamera, texMtx, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY);
    GXSetNumTevStages(2);
    GXSetNumTexGens(3);
    GXSetNumChans(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_RASC, GX_CC_RASA, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColor(GX_TEVREG0, lbl_1_data_600);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXA, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_208);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    workUnk4 = &work2->unk4[3];
    fn_1_6594(0, workUnk4, 0, 0, 0);
    HuSprTexLoad(work->unkA1C[3], 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    workUnk4 = &work2->unk4[0];
    fn_1_6594(2, workUnk4, 0, 0, 1);
    GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD2, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_1);
    GXSetIndTexMtx(GX_ITM_1, lbl_1_data_5E8, -1);
    for (i = 0; i < 26; i++) {
        work2->unk944[i][0] -= 0.007874016f * ((s32)frand() & 0x7F) * 0.005f;
        work2->unk944[i][1] += 0.007874016f * ((s32)frand() & 0x7F) * 0.005f;
        work2->unk874[i][0] = work2->unk944[i][0] + lbl_1_data_518[i][0];
        work2->unk874[i][1] = work2->unk944[i][1] + lbl_1_data_518[i][1];
    }
    DCFlushRange(&work2->unk874[0][0], sizeof(work2->unk874));
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);

    GXSETARRAY(GX_VA_POS, lbl_1_data_2A8, sizeof(lbl_1_data_2A8), sizeof(Vec));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSETARRAY(GX_VA_CLR0, lbl_1_data_3E0, sizeof(lbl_1_data_3E0), sizeof(GXColor));
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSETARRAY(GX_VA_TEX0, lbl_1_data_448, sizeof(lbl_1_data_448), sizeof(float) * 2);
    GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
    GXSETARRAY(GX_VA_TEX1, &work2->unk874[0][0], sizeof(work2->unk874), sizeof(float) * 2);
    GXBegin(GX_QUADS, GX_VTXFMT0, 48);
    for (i = 0; i < 12; i++) {
        s16 index;
        if (i == 4) {
            index = 12;
        }
        else if (i == 9) {
            index = 13;
        }
        else {
            index = i;
        }
        GXPosition1x16(index + 0);
        GXColor1x16(index + 0);
        GXTexCoord1x16(index + 0);
        GXTexCoord1x16(index + 0);
        GXPosition1x16(index + 5);
        GXColor1x16(index + 5);
        GXTexCoord1x16(index + 5);
        GXTexCoord1x16(index + 5);
        GXPosition1x16(index + 6);
        GXColor1x16(index + 6);
        GXTexCoord1x16(index + 6);
        GXTexCoord1x16(index + 6);
        GXPosition1x16(index + 1);
        GXColor1x16(index + 1);
        GXTexCoord1x16(index + 1);
        GXTexCoord1x16(index + 1);
    }
    GXEnd();
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 8);
    GXPosition1x16(22);
    GXColor1x16(22);
    GXTexCoord1x16(22);
    GXTexCoord1x16(22);
    GXPosition1x16(15);
    GXColor1x16(15);
    GXTexCoord1x16(15);
    GXTexCoord1x16(15);
    GXPosition1x16(21);
    GXColor1x16(21);
    GXTexCoord1x16(21);
    GXTexCoord1x16(21);
    GXPosition1x16(10);
    GXColor1x16(10);
    GXTexCoord1x16(10);
    GXTexCoord1x16(10);
    GXPosition1x16(20);
    GXColor1x16(20);
    GXTexCoord1x16(20);
    GXTexCoord1x16(20);
    GXPosition1x16(5);
    GXColor1x16(5);
    GXTexCoord1x16(5);
    GXTexCoord1x16(5);
    GXPosition1x16(0);
    GXColor1x16(0);
    GXTexCoord1x16(0);
    GXTexCoord1x16(0);
    GXPosition1x16(0);
    GXColor1x16(0);
    GXTexCoord1x16(0);
    GXTexCoord1x16(0);
    GXEnd();
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 8);
    GXPosition1x16(19);
    GXColor1x16(19);
    GXTexCoord1x16(19);
    GXTexCoord1x16(19);
    GXPosition1x16(25);
    GXColor1x16(25);
    GXTexCoord1x16(25);
    GXTexCoord1x16(25);
    GXPosition1x16(14);
    GXColor1x16(14);
    GXTexCoord1x16(14);
    GXTexCoord1x16(14);
    GXPosition1x16(24);
    GXColor1x16(24);
    GXTexCoord1x16(24);
    GXTexCoord1x16(24);
    GXPosition1x16(9);
    GXColor1x16(9);
    GXTexCoord1x16(9);
    GXTexCoord1x16(9);
    GXPosition1x16(23);
    GXColor1x16(23);
    GXTexCoord1x16(23);
    GXTexCoord1x16(23);
    GXPosition1x16(4);
    GXColor1x16(4);
    GXTexCoord1x16(4);
    GXTexCoord1x16(4);
    GXPosition1x16(4);
    GXColor1x16(4);
    GXTexCoord1x16(4);
    GXTexCoord1x16(4);
    GXEnd();
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
}

void fn_1_59A0(ModelData *model, Mtx matrix)
{
    s32 sp10 = 0;
    Work347C *work = model->unk_120;
    float scale = 1.5f;
    float x = 0;
    Mtx temp;
    Mtx final;
    MTXTrans(final, x, -300, 0);
    GXSetTevColor(GX_TEVREG0, lbl_1_data_694);
    MTXScale(temp, scale, 1, 1);
    MTXConcat(final, temp, final);
    MTXConcat(Hu3DCameraMtx, final, final);
    GXLoadPosMtxImm(final, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_208);
    HuSprTexLoad(work->unkA1C[0], 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(work->unkA1C[1], 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(2);
    MTXRotDeg(final, 'X', 90.0f);
    x = 0.004f * scale;
    MTXScale(temp, x, -0.004f, 0.004f);
    MTXConcat(final, temp, final);
    MTXTrans(temp, (work->unkA48 % 1024) / (512.0f * x), 0, 1.2499999f * (work->unkA48 % 400));
    MTXConcat(final, temp, final);
    GXLoadTexMtxImm(final, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_POS, GX_TEXMTX0);
    MTXRotDeg(final, 'X', 90.0f);
    x = 0.004f * scale;
    MTXScale(temp, x, -0.004f, 0.004f);
    MTXConcat(final, temp, final);
    MTXTrans(temp, (work->unkA48 % 300) / (150.0f * x), 0, 0);
    MTXConcat(final, temp, final);
    GXLoadTexMtxImm(final, GX_TEXMTX1, GX_MTX2x4);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_POS, GX_TEXMTX1);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_SET);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSETARRAY(GX_VA_POS, lbl_1_data_604, sizeof(lbl_1_data_604), sizeof(Vec));
    GXSETARRAY(GX_VA_CLR0, lbl_1_data_670, sizeof(lbl_1_data_670), sizeof(GXColor));
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 6);
    GXPosition1x8(0);
    GXColor1x8(0);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXPosition1x8(3);
    GXColor1x8(3);
    GXPosition1x8(4);
    GXColor1x8(4);
    GXPosition1x8(6);
    GXColor1x8(6);
    GXPosition1x8(7);
    GXColor1x8(7);
    GXEnd();
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 6);
    GXPosition1x8(1);
    GXColor1x8(1);
    GXPosition1x8(2);
    GXColor1x8(2);
    GXPosition1x8(4);
    GXColor1x8(4);
    GXPosition1x8(5);
    GXColor1x8(5);
    GXPosition1x8(7);
    GXColor1x8(7);
    GXPosition1x8(8);
    GXColor1x8(8);
    GXEnd();
}

void fn_1_6088(Work347CUnk4 *arg0, s32 arg1)
{
    GXSetTexCopySrc(0, 0, arg0->unkC, arg0->unk10);
    GXSetTexCopyDst(arg0->unk14, arg0->unk18, GX_TF_RGB565, arg0->unk8);
    GXSetCopyClear(lbl_1_data_69C, GX_MAX_Z24);
    GXCopyTex(arg0->unk0, arg1);
}

void fn_1_6144(Work347CUnk4 *fbWork, float x1, float y1, float scale)
{
    float x2 = x1 + (fbWork->unk14 * scale);
    float y2 = y1 + (fbWork->unk18 * scale);
    Mtx44 proj;
    Mtx modelview;
    GXTexObj texObj;
    GXColor color;
    GXInitTexObj(&texObj, fbWork->unk0, fbWork->unk14, fbWork->unk18, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    MTXOrtho(proj, 0, 480, 0, 640, 0, 10);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    color.a = 255;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    MTXIdentity(modelview);
    GXLoadPosMtxImm(modelview, GX_PNMTX0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x1, y1, 0);
    GXTexCoord2f32(0, 0);
    GXPosition3f32(x2, y1, 0);
    GXTexCoord2f32(1, 0);
    GXPosition3f32(x2, y2, 0);
    GXTexCoord2f32(1, 1);
    GXPosition3f32(x1, y2, 0);
    GXTexCoord2f32(0, 1);
    GXEnd();
#ifdef TARGET_PC
    GXDestroyTexObj(&texObj);
#endif
}

void fn_1_6594(s16 arg0, Work347CUnk4 *arg1, GXTexWrapMode arg2, s32 arg3, BOOL arg4)
{
    GXTexObj texObj;
    GXInitTexObj(&texObj, arg1->unk0, arg1->unk14, arg1->unk18, GX_TF_RGB565, arg2, arg2, FALSE);
    if (arg4) {
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    else {
        GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    GXLoadTexObj(&texObj, arg0);
#ifdef TARGET_PC
    GXDestroyTexObj(&texObj);
#endif
}

s32 fn_1_6698(Vec *arg0, float arg1, float arg2, s32 arg3)
{
    Work347C *work;
    Work347C *work2;
    Work347CUnk74 *workUnk74;
    s32 i;
    if (!lbl_1_bss_6C) {
        return -1;
    }
    work = lbl_1_bss_6C->data;
    work2 = work;
    workUnk74 = &work->unk74[0];
    for (i = 0; i < 64; i++, workUnk74++) {
        if (workUnk74->unk1E == 0) {
            break;
        }
    }
    if (i >= 64) {
        return -1;
    }
    workUnk74->unk0 = *arg0;
    if (arg1 < 0.0f) {
        workUnk74->unkC.x = 1;
    }
    else {
        workUnk74->unkC.x = arg1;
    }
    if (arg2 < 0.0f) {
        workUnk74->unkC.z = 1;
    }
    else {
        workUnk74->unkC.z = arg2;
    }
    if (arg3 < 0) {
        workUnk74->unk1C = 60;
    }
    else {
        workUnk74->unk1C = arg3;
    }
    workUnk74->unkC.y = (s32)frand() % 360;
    workUnk74->unk1E = workUnk74->unk1C;
    workUnk74->unk18 = 1.0f / workUnk74->unk1C;
    return i;
}

float fn_1_687C(void)
{
    if (!lbl_1_bss_6C) {
        return 0;
    }
    else {
        Work347C *work = lbl_1_bss_6C->data;
        return work->unkA44;
    }
}

float fn_1_68C8(void)
{
    if (!lbl_1_bss_6C) {
        return 0;
    }
    else {
        Work347C *work = lbl_1_bss_6C->data;
        return work->unkA40;
    }
}

typedef struct work6914 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    AnimData *unk10;
    Vec unk14;
    Vec unk20;
    Vec unk2C;
} Work6914;

void fn_1_6A6C(omObjData *object);

void fn_1_6914(omObjData *object)
{
    Work6914 *work;
    s32 i;
    AnimData *anim;
    work = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work6914) * 8, MEMORY_DEFAULT_NUM);
    memset(work, 0, sizeof(Work6914) * 8);
    anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 26), MEMORY_DEFAULT_NUM));
    for (i = 0; i < 8; i++, work++) {
        work->unk10 = anim;
        work->unk0 = i;
        work->unk4 = Hu3DParticleCreate(work->unk10, 32);
        Hu3DModelCameraSet(work->unk4, HU3D_CAM0);
        Hu3DModelLayerSet(work->unk4, 6);
        Hu3DModelAttrSet(work->unk4, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk4, HU3D_ATTR_PARTICLE_KILL);
        work->unk8 = 0;
        work->unkC = 0;
        work->unk14.x = work->unk14.y = work->unk14.z = 0;
        work->unk20.x = work->unk20.y = work->unk20.z = 0;
        work->unk2C.x = work->unk2C.y = work->unk2C.z = 1;
    }
    object->func = fn_1_6A6C;
}

void fn_1_6A6C(omObjData *object)
{
    Work6914 *work = object->data;
    s32 i;
    for (i = 0; i < 8; i++, work++) {
        if (work->unk8 == 0) {
            continue;
        }
        if (work->unkC > 1) {
            ModelData *modelP = &Hu3DData[work->unk4];
            ParticleData *particleP = modelP->unk_120;
            HsfanimStruct01 *data = particleP->unk_48;
            s32 j;
            for (j = 0; j < particleP->unk_30; j++, data++) {
                if (++data->unk00 > data->unk02) {
                    s32 alpha = data->unk40.a - 1;
                    if (alpha < 0) {
                        data->unk2C = 0;
                    }
                    else {
                        data->unk40.a = alpha;
                    }
                }
                data->unk2C *= 0.975;
                data->unk34.x += data->unk08.x;
                data->unk34.y += data->unk08.y;
                data->unk34.z += data->unk08.z;
                data->unk08.y -= 0.3103333379576603;
            }
        }
        if (++work->unkC > 90.0f) {
            Hu3DModelAttrSet(work->unk4, HU3D_ATTR_DISPOFF);
            work->unk8 = 0;
        }
        else {
            Hu3DModelPosSet(work->unk4, work->unk14.x, work->unk14.y, work->unk14.z);
            Hu3DModelRotSet(work->unk4, work->unk20.x, work->unk20.y, work->unk20.z);
            Hu3DModelScaleSet(work->unk4, work->unk2C.x, work->unk2C.y, work->unk2C.z);
        }
    }
}

void fn_1_6C60(omObjData *object)
{
    Work6914 *work = object->data;
    AnimData *anim = work->unk10;
    anim->useNum = 0;
    HuSprAnimKill(anim);
}

s32 fn_1_6CB0(Vec *arg0, float arg1)
{
    Work6914 *work = lbl_1_bss_68->data;
    s32 i;
    ModelData *temp_r27;
    ParticleData *temp_r28;
    HsfanimStruct01 *temp_r30;

    for (i = 0; i < 8; i++, work++) {
        if (work->unk8 == 0) {
            break;
        }
    }
    if (i >= 8) {
        return -1;
    }
    Hu3DModelAttrReset(work->unk4, HU3D_ATTR_DISPOFF);
    work->unk8 = 1;
    work->unkC = 0;
    temp_r27 = &Hu3DData[work->unk4];
    temp_r28 = temp_r27->unk_120;
    temp_r28->unk_2C = 1;
    temp_r30 = temp_r28->unk_48;
    for (i = 0; i < temp_r28->unk_30; i++, temp_r30++) {
        float temp_f30 = ((s32)frand() % 20) + 90;
        float temp_f29 = (s32)frand() % 360;
        float temp_f26 = sind(temp_f30);
        float temp_f28 = cosd(temp_f30);
        float temp_f25 = 0.75f + 0.15f * (0.007874016f * ((s32)frand() & 0x7F));
        float temp_f31 = 0.15f;
        temp_r30->unk08.x = temp_f31 * (0.65f * (50.0 * (temp_f28 * sind(temp_f29))));
        temp_r30->unk08.z = temp_f31 * (0.65f * (50.0 * (temp_f28 * cosd(temp_f29))));
        temp_r30->unk08.y = temp_f31 * (50 * temp_f26 * temp_f25);
        temp_r30->unk00 = 0;
        temp_r30->unk02 = ((s32)frand() % 16) + 45;
        temp_r30->unk30 = (s32)frand() % 360;
        temp_r30->unk2C = 145;
        temp_r30->unk34.x = 0.05f * (((s32)frand() & 0x7F) - 64);
        temp_r30->unk34.y = 0.65f * (((s32)frand() & 0x7F) - 64);
        temp_r30->unk34.z = 0.05f * (((s32)frand() & 0x7F) - 64);
        temp_r30->unk40.r = ((s32)frand() % 64) + 192;
        temp_r30->unk40.g = ((s32)frand() % 64) + 192;
        temp_r30->unk40.b = ((s32)frand() % 64) + 192;
        temp_r30->unk40.a = 64;
    }
    if (arg1 < 0.0f) {
        arg1 = 1.0f;
    }
    work->unk14 = *arg0;
    work->unk20.x = work->unk20.y = work->unk20.z = 0;
    work->unk2C.x = work->unk2C.y = work->unk2C.z = arg1;
    Hu3DModelPosSet(work->unk4, work->unk14.x, work->unk14.y, work->unk14.z);
    Hu3DModelRotSet(work->unk4, work->unk20.x, work->unk20.y, work->unk20.z);
    Hu3DModelScaleSet(work->unk4, work->unk2C.x, work->unk2C.y, work->unk2C.z);
    return i;
}

void fn_1_7368(omObjData *object);

void fn_1_7280(omObjData *object)
{
    s32 i;
    for (i = 0; i < object->mdlcnt; i++) {
        if (i == 0) {
            object->model[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M455, 9));
        }
        else {
            object->model[i] = Hu3DModelLink(object->model[0]);
        }
        Hu3DModelCameraSet(object->model[i], HU3D_CAM0);
        Hu3DModelLayerSet(object->model[i], 6);
        Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF);
    }
    object->stat |= 0x100;
    object->func = fn_1_7368;
}

void fn_1_7368(omObjData *object)
{
    s32 i;
    for (i = 0; i < object->mdlcnt; i++) {
        ModelData *modelP = &Hu3DData[object->model[i]];
        if (!(modelP->attr & HU3D_ATTR_DISPOFF)) {
            if (Hu3DMotionTimeGet(object->model[i]) >= Hu3DMotionMaxTimeGet(object->model[i])) {
                Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF);
            }
        }
    }
}

void fn_1_7430(omObjData *object) { }

s32 fn_1_7434(Vec *pos, float scale)
{
    s32 i;
    for (i = 0; i < lbl_1_bss_64->mdlcnt; i++) {
        ModelData *modelP = &Hu3DData[lbl_1_bss_64->model[i]];
        if (modelP->attr & HU3D_ATTR_DISPOFF) {
            break;
        }
    }
    if (i >= lbl_1_bss_64->mdlcnt) {
        return -1;
    }
    Hu3DMotionTimeSet(lbl_1_bss_64->model[i], 0);
    Hu3DMotionSpeedSet(lbl_1_bss_64->model[i], 1);
    Hu3DModelPosSet(lbl_1_bss_64->model[i], pos->x, pos->y, pos->z);
    Hu3DModelScaleSet(lbl_1_bss_64->model[i], scale, scale, scale);
    Hu3DModelAttrReset(lbl_1_bss_64->model[i], HU3D_ATTR_DISPOFF);
    return i;
}

void fn_1_76B0(omObjData *object);

void fn_1_75C0(omObjData *object)
{
    ParticleData *temp_r30;
    HsfanimStruct01 *temp_r29;
    s32 i;
    ModelData *modelP;
    AnimData *anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 26), MEMORY_DEFAULT_NUM));

    object->data = anim;
    object->model[0] = Hu3DParticleCreate(anim, 64);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    Hu3DModelLayerSet(object->model[0], 3);
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_PARTICLE_KILL);
    modelP = &Hu3DData[object->model[0]];
    temp_r30 = modelP->unk_120;
    temp_r29 = temp_r30->unk_48;
    temp_r30->unk_2C = 1;
    for (i = 0; i < temp_r30->unk_30; i++, temp_r29++) {
        temp_r29->unk2C = 0;
    }
    object->func = fn_1_76B0;
}

void fn_1_76B0(omObjData *object)
{
    ModelData *modelP = &Hu3DData[object->model[0]];
    ParticleData *temp_r29 = modelP->unk_120;
    HsfanimStruct01 *temp_r30 = temp_r29->unk_48;
    s32 i;
    for (i = 0; i < temp_r29->unk_30; i++, temp_r30++) {
        if (temp_r30->unk2C <= 0.0f) {
            continue;
        }
        if (++temp_r30->unk00 > 360) {
            temp_r30->unk00 -= 360;
        }
        temp_r30->unk34.x += temp_r30->unk08.x * sind(2.0f * temp_r30->unk00);
        temp_r30->unk34.y += temp_r30->unk08.y;
        if (temp_r30->unk34.y >= 0.0f) {
            fn_1_6698(&temp_r30->unk34, 0.00625f * temp_r30->unk2C, 1, 15);
            temp_r30->unk2C = 0;
        }
    }
}

void fn_1_7974(omObjData *object)
{
    AnimData *anim = object->data;
    HuSprAnimKill(anim);
    Hu3DModelKill(object->model[0]);
    object->model[0] = -1;
}

s32 fn_1_79C8(Vec *pos, float scale)
{
    s32 i;
    ModelData *modelP = &Hu3DData[lbl_1_bss_60->model[0]];
    ParticleData *temp_r30 = modelP->unk_120;
    HsfanimStruct01 *temp_r31 = temp_r30->unk_48;
    for (i = 0; i < temp_r30->unk_30; i++, temp_r31++) {
        if (temp_r31->unk2C <= 0.0f) {
            break;
        }
    }
    if (i >= temp_r30->unk_30) {
        return -1;
    }
    if (scale <= 0.0f) {
        scale = 1.0f;
    }
    temp_r31->unk34 = *pos;
    temp_r31->unk08.x = (1.5f + (0.2f * (0.007874016f * ((s32)frand() & 0x7F)))) * 0.5f;
    temp_r31->unk08.z = (1.5f + (0.2f * (0.007874016f * ((s32)frand() & 0x7F))));
    temp_r31->unk08.y = (1.5f + (0.2f * (0.007874016f * ((s32)frand() & 0x7F)))) * 2.0f;
    temp_r31->unk00 = (s32)frand() % 360;
    temp_r31->unk2C = 20 * scale;
    return i;
}

typedef struct work7C48 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    float unkC;
    float unk10;
    Vec unk14;
    Vec unk20;
} Work7C48;

void fn_1_8050(omObjData *object);

void fn_1_7C48(omObjData *object)
{
    Work7C48 *workBase = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work7C48) * 8, MEMORY_DEFAULT_NUM);
    Work7C48 *workP = workBase;
    s32 i;
    memset(workP, 0, 8 * sizeof(Work7C48));
    for (i = 0; i < 8; i++, workP++) {
        switch (i) {
            case 0:
                workP->unk0 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M455, 10));
                break;

            case 1:
                workP->unk0 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M455, 10));
                break;

            default:
                if (i & 0x1) {
                    workP->unk0 = Hu3DModelLink(workBase[0].unk0);
                }
                else {
                    workP->unk0 = Hu3DModelLink(workBase[1].unk0);
                }
                break;
        }
        Hu3DModelScaleSet(workP->unk0, 0.5f, 0.5f, 0.5f);
        Hu3DModelCameraSet(workP->unk0, HU3D_CAM0);
        Hu3DModelLayerSet(workP->unk0, 1);
        workP->unk4 = 0;
        workP->unk8 = 0;
        workP->unkC = 2;
        workP->unk10 = (s32)frand() % 360;
        workP->unk14.x = 1500 * ((0.007874016f * ((s32)frand() & 0x7F)) - 0.5f);
        workP->unk14.z = 500 * ((0.007874016f * ((s32)frand() & 0x7F)) - 0.5f);
        workP->unk14.y = -250 + (100 * (0.3f * i));
        workP->unk20.x = 1500 * ((0.007874016f * ((s32)frand() & 0x7F)) - 0.5f);
        workP->unk20.z = 500 * ((0.007874016f * ((s32)frand() & 0x7F)) - 0.5f);
        workP->unk20.y = workP->unk14.y;
        Hu3DModelPosSet(workP->unk0, workP->unk14.x, workP->unk14.y, workP->unk14.z);
        Hu3DModelRotSet(workP->unk0, 0, workP->unk10, 0);
    }
    object->func = fn_1_8050;
}

float fn_1_9F18(float start, float end, float weight);

void fn_1_8050(omObjData *object)
{
    Work7C48 *workP = object->data;
    s32 i;
    for (i = 0; i < 8; i++, workP++) {
        float dx;
        float dz;
        float vel;
        float angle;
        if (workP->unk4 == 0) {
            vel = 1 + (0.5 * sind((workP->unk8 * 5) % 180));
        }
        else {
            vel = 3;
        }
        workP->unk14.x += vel * (workP->unkC * sind(workP->unk10));
        workP->unk14.z += vel * (workP->unkC * cosd(workP->unk10));
        dx = workP->unk20.x - workP->unk14.x;
        dz = workP->unk20.z - workP->unk14.z;
        angle = atan2d(dx, dz);
        workP->unk10 = fn_1_9F18(angle, workP->unk10, 3.5f);
        if ((dx * dx) + (dz * dz) < 10000.0f) {
            if (workP->unk4 == 0) {
                workP->unk20.x = 2000 * ((0.007874016f * ((s32)frand() & 0x7F)) - 0.5f);
                workP->unk20.z = 700 * ((0.007874016f * ((s32)frand() & 0x7F)) - 0.5f);
                workP->unk20.y = workP->unk14.y;
            }
            else {
                if (workP->unk14.x < 0.0f) {
                    workP->unk20.x = -2500;
                }
                else {
                    workP->unk20.x = 2500;
                }
                workP->unk20.z = 500 * ((0.007874016f * ((s32)frand() & 0x7F)) - 0.5f);
                workP->unk20.y = workP->unk14.y;
            }
        }
        Hu3DModelPosSet(workP->unk0, workP->unk14.x, workP->unk14.y, workP->unk14.z);
        Hu3DModelRotSet(workP->unk0, 0, workP->unk10, 0);
        workP->unk8 += frand() & 0x3;
    }
}

void fn_1_8474(omObjData *object) { }

void fn_1_8478(void)
{
    Work7C48 *workP = lbl_1_bss_5C->data;
    s32 i;
    for (i = 0; i < 8; i++, workP++) {
        workP->unk4 = 1;
        if (workP->unk14.x < 0.0f) {
            workP->unk20.x = -2500;
        }
        else {
            workP->unk20.x = 2500;
        }
        workP->unk20.z = 500 * ((0.007874016f * ((s32)frand() & 0x7F)) - 0.5f);
        workP->unk20.y = workP->unk14.y;
    }
}

typedef struct work891C {
    s16 unk0;
    s16 unk2[2];
    s16 unk6;
    Vec unk8;
    Vec unk14;
    float unk20;
    float unk24;
    float unk28;
    float unk2C;
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
} Work891C;

void fn_1_8578(omObjData *object, Work891C *workP)
{
    s32 num = workP[0].unk6;
    float ofsZ = -2000;
    s32 i;
    for (i = 0; i < num; i++, workP++) {
        Mtx *modelMtx;
        Mtx rotZ;
        Hu3DModelPosSet(workP->unk0, workP->unk8.x, workP->unk8.y, workP->unk8.z + ofsZ);
        modelMtx = &Hu3DData[workP->unk0].unk_F0;
        MTXRotDeg(*modelMtx, 'Y', workP->unk28);
        MTXRotDeg(rotZ, 'Z', workP->unk38);
        MTXConcat(*modelMtx, rotZ, *modelMtx);
        Hu3DModelAttrReset(workP->unk0, HU3D_ATTR_DISPOFF);
    }
}

float fn_1_8D90(float start, float end, float weight);

void fn_1_867C(omObjData *object)
{
    Work891C *workP = object->data;
    s32 num = workP[0].unk6;
    s32 i;
    for (i = 0; i < num; i++, workP++) {
        Vec diff;
        s32 unk8 = 0;
        VECSubtract(&workP->unk14, &workP->unk8, &diff);
        workP->unk2C = atan2d(diff.x, diff.z);
        workP->unk28 = fn_1_8D90(workP->unk28, workP->unk2C + workP->unk3C, 0.08f);
        workP->unk24 += 0.05f * (600.0f - workP->unk24);
        workP->unk20 += 0.2f * (workP->unk24 - workP->unk20);
        workP->unk8.x += (workP->unk20 * 0.016666668f) * sind(workP->unk28);
        workP->unk8.z += (workP->unk20 * 0.016666668f) * cosd(workP->unk28);
        workP->unk30 += workP->unk20 * 0.016666668f;
    }
    fn_1_8578(object, object->data);
}

void fn_1_891C(omObjData *object)
{
    s16 num = 12;
    Work891C *workBase;
    s32 modelId;
    Work891C *work;
    float radius;
    float angle;
    float ofsZ;
    s32 i;
    object->data = workBase = HuMemDirectMallocNum(HEAP_SYSTEM, num * sizeof(Work891C), MEMORY_DEFAULT_NUM);
    memset(workBase, 0, num * sizeof(Work891C));
    modelId = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M455, 8));
    ofsZ = 1500;
    work = workBase;
    for (i = 0; i < num; i++, work++) {

        work->unk0 = Hu3DModelLink(modelId);
        Hu3DModelLayerSet(work->unk0, 6);
        Hu3DModelCameraSet(work->unk0, 1);
        Hu3DModelScaleSet(work->unk0, 7, 7, 7);
        work->unk14.x = ((s32)frandmod(1000) * 4.0f) - 2000;
        work->unk14.z = ((s32)frandmod(1000)) - 500.0f;
        work->unk14.y = ((s32)frandmod(1000) * 0.8f) + 300;
        angle = (s32)frandmod(360);
        radius = ((s32)frandmod(250)) + 200.0f;
        work->unk8.x = radius * sind(angle);
        work->unk8.y = 0;
        work->unk8.z = radius * cosd(angle);
        VECAdd(&work->unk14, &work->unk8, &work->unk8);
        work->unk38 = 60 - ((6.0f / 55.0f) * radius);
        work->unk28 = (s32)frandmod(360);

        work->unk3C = ((s32)frandmod(1000) < 500) ? (-70.0f + ((s32)frandmod(50) * 0.1f)) : (70.0f - ((s32)frandmod(50) * 0.1f));
        if (work->unk3C < 0.0f) {
            work->unk38 = -work->unk38;
        }
        work->unk30 = 1;
        work->unk34 = 0;
        ofsZ -= 50.0f;
        work->unk6 = num;
    }
    Hu3DModelKill(modelId);
    object->func = fn_1_867C;
}

float fn_1_8D90(float start, float end, float weight)
{
    float angle = fmodf(end - start, 360);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    if (angle > 180.0f) {
        angle -= 360.0f;
    }
    angle = fmodf(start + (weight * angle), 360);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

void fn_1_91B8(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_1_8EAC(void)
{
    StructBss48 *workP = lbl_1_bss_48 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(StructBss48), MEMORY_DEFAULT_NUM);
    ParticleData *particle;
    ModelData *modelP;
    s16 *newWork;
    s32 modelId;
    memset(workP, 0, sizeof(StructBss48));
    workP->unk0[0] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 13), MEMORY_DEFAULT_NUM));
    workP->unk0[1] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 14), MEMORY_DEFAULT_NUM));
    workP->unk0[2] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 15), MEMORY_DEFAULT_NUM));
    workP->unk0[3] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M455, 16), MEMORY_DEFAULT_NUM));
    workP->unk20.y = 1;
    workP->unk20.z = 0;
    workP->unk10[0] = modelId = Hu3DParticleCreate(workP->unk0[0], 1);
    Hu3DModelLayerSet(modelId, 6);
    modelP = &Hu3DData[modelId];
    particle = modelP->unk_120;
    particle->unk_2C = 1;
    particle->unk_54 = fn_1_91B8;
    newWork = particle->unk_1C = HuMemDirectMallocNum(HEAP_DATA, sizeof(s16) * 4, modelP->unk_48);
    memset(newWork, 0, 4 * sizeof(s16));
    newWork[1] = 0;
    workP->unk10[1] = modelId = Hu3DParticleCreate(workP->unk0[3], 10);
    Hu3DModelLayerSet(modelId, 6);
    modelP = &Hu3DData[modelId];
    particle = modelP->unk_120;
    particle->unk_2C = 1;
    particle->unk_54 = fn_1_91B8;
    newWork = particle->unk_1C = HuMemDirectMallocNum(HEAP_DATA, sizeof(s16) * 4, modelP->unk_48);
    memset(newWork, 0, 4 * sizeof(s16));
    newWork[1] = 1;
    workP->unk10[2] = modelId = Hu3DParticleCreate(workP->unk0[2], 4);
    Hu3DModelLayerSet(modelId, 6);
    modelP = &Hu3DData[modelId];
    particle = modelP->unk_120;
    particle->unk_2C = 1;
    particle->unk_54 = fn_1_91B8;
    newWork = particle->unk_1C = HuMemDirectMallocNum(HEAP_DATA, sizeof(s16) * 4, modelP->unk_48);
    memset(newWork, 0, 4 * sizeof(s16));
    newWork[1] = 2;
    workP->unk10[3] = modelId = Hu3DParticleCreate(workP->unk0[1], 6);
    Hu3DModelLayerSet(modelId, 6);
    modelP = &Hu3DData[modelId];
    particle = modelP->unk_120;
    particle->unk_2C = 1;
    particle->unk_54 = fn_1_91B8;
    newWork = particle->unk_1C = HuMemDirectMallocNum(HEAP_DATA, sizeof(s16) * 4, modelP->unk_48);
    memset(newWork, 0, 4 * sizeof(s16));
    newWork[1] = 3;
}

void fn_1_9168(void)
{
    StructBss48 *workP = lbl_1_bss_48;
    HuSprAnimKill(workP->unk0[0]);
    HuSprAnimKill(workP->unk0[1]);
    HuSprAnimKill(workP->unk0[2]);
    HuSprAnimKill(workP->unk0[3]);
}

float lbl_1_data_6A0[4] = { 1000, 200, 600, 1200 };

float lbl_1_data_6B0[4] = { 1, 0.6, 0.3, 0.425 };

void fn_1_91B8(ModelData *model, ParticleData *particle, Mtx matrix)
{
    s16 unk8 = 0;
    StructBss48 *workP = lbl_1_bss_48;
    s16 *newWorkP = particle->unk_1C;
    s32 unk14 = 0;
    Vec pos = Center;
    Vec rot = CRot;
    float temp_f26;
    float temp_f25;
    float zoom = CZoom;
    HsfanimStruct01 *temp_r31;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    float temp_f29;
    float temp_f23;
    s32 i;
    switch (newWorkP[2]) {
        case 0:
            temp_r31 = particle->unk_48;
            if (newWorkP[1]) {
                sp18.x = 2000;
                sp18.y = -300;
                sp18.z = 500;
                temp_f29 = 1 / VECMagPoint(sp18.x, sp18.y, sp18.z);
                sp18.x *= temp_f29;
                sp18.y *= temp_f29;
                sp18.z *= temp_f29;
                temp_f23 = 3200.0f / particle->unk_30;
                for (i = 0; i < particle->unk_30; i++, temp_r31++) {
                    temp_f26 = 500.0 + ((temp_f23 * i) + ((0.25f * temp_f23) * ((float)((s32)frand() & 0xFFFF) * 0.0000152587890625)));
                    temp_f25 = temp_f26 / 3200;
                    temp_r31->unk14.x = temp_f26;
                    temp_r31->unk34.x = 1000 + (temp_f26 * sp18.x);
                    temp_r31->unk34.y = 4800 + (temp_f26 * sp18.y);
                    temp_r31->unk34.z = -3500 + (temp_f26 * sp18.z);
                    temp_r31->unk2C = ((0.7f * (temp_f25 * temp_f25)) + 0.3f)
                        * (lbl_1_data_6A0[newWorkP[1]] * (0.7f + (0.3f * ((float)((s32)frand() & 0xFFFF) * 0.0000152587890625))));
                    temp_r31->unk40.r = (s32)(((float)((s32)frand() & 0xFFFF) * 0.0000152587890625) * 160.0) + 32;
                    temp_r31->unk40.g = (s32)(((float)((s32)frand() & 0xFFFF) * 0.0000152587890625) * 96.0) + 32;
                    temp_r31->unk40.b = (s32)(((float)((s32)frand() & 0xFFFF) * 0.0000152587890625) * 128.0) + 32;
                    temp_r31->unk40.a = (255 * lbl_1_data_6B0[newWorkP[1]] * (1.0 - (0.4 * temp_f25)))
                        - (s32)(((float)((s32)frand() & 0xFFFF) * 0.0000152587890625) * 16.0);
                    temp_r31->unk14.z = temp_r31->unk40.a;
                }
                newWorkP[2]++;
            }
            else {
                temp_r31->unk34.x = 1000;
                temp_r31->unk34.y = 4800;
                temp_r31->unk34.z = -3500;
                temp_r31->unk2C = 1000;
            }
            break;

        case 1:
            sp3C.x = sind(rot.y) * cosd(rot.x);
            sp3C.y = -sind(rot.x);
            sp3C.z = cosd(rot.y) * cosd(rot.x);
            sp30.x = 1000 - (pos.x + (1.25f * (sp3C.x * zoom)));
            sp30.y = 4800 - (pos.y + (sp3C.y * zoom));
            sp30.z = -3500 - (pos.z + (1.25f * (sp3C.z * zoom)));
            temp_f29 = 1 / VECMagPoint(sp30.x, sp30.y, sp30.z);
            sp30.x *= temp_f29;
            sp30.y *= temp_f29;
            sp30.z *= temp_f29;
            temp_f29 = -((-sp30.x * -sp3C.x) + (-sp30.y * -sp3C.y) + (-sp30.z * -sp3C.z));
            sp24.x = -sp3C.x + ((-2.0f * sp30.x) * temp_f29);
            sp24.y = -sp3C.y + ((-2.0f * sp30.y) * temp_f29);
            sp24.z = -sp3C.z + ((-2.0f * sp30.z) * temp_f29);
            temp_r31 = particle->unk_48;
            for (i = 0; i < particle->unk_30; i++, temp_r31++) {
                temp_r31->unk34.x = 1000 + (sp24.x * temp_r31->unk14.x);
                temp_r31->unk34.y = 4800 + (sp24.y * temp_r31->unk14.x);
                temp_r31->unk34.z = -3500 + (sp24.z * temp_r31->unk14.x);
                temp_r31->unk40.a = temp_r31->unk14.z * workP->unk20.y;
            }
            break;
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_9CFC(float arg0)
{
    StructBss48 *workP = lbl_1_bss_48;
    workP->unk20.y = arg0;
    if (workP->unk20.y > 1.0f) {
        workP->unk20.y = 1.0f;
    }
    if (workP->unk20.y <= 0.0f) {
        Hu3DModelAttrSet(workP->unk10[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(workP->unk10[1], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(workP->unk10[2], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(workP->unk10[3], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrReset(workP->unk10[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(workP->unk10[1], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(workP->unk10[2], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(workP->unk10[3], HU3D_ATTR_DISPOFF);
    }
}

float fn_1_9E00(float start, float end)
{
    float angleDiff;
    if (start >= 360.0f) {
        start -= 360.0f;
    }
    else if (start < 0.0f) {
        start += 360.0f;
    }
    if (end >= 360.0f) {
        end -= 360.0f;
    }
    else if (end < 0.0f) {
        end += 360.0f;
    }
    angleDiff = start - end;
    if (angleDiff <= -180.0f) {
        angleDiff += 360.0f;
    }
    else if (angleDiff >= 180.0f) {
        angleDiff -= 360.0f;
    }
    return angleDiff;
}

float fn_1_9F18(float start, float end, float max)
{
    float angle;
    float diff;

    if (start >= 360.0) {
        start -= 360.0;
    }
    else if (start < 0.0) {
        start += 360.0;
    }
    if (end >= 360.0) {
        end -= 360.0;
    }
    else if (end < 0.0) {
        end += 360.0;
    }
    diff = 360.0 + (start - end);
    if (fabs(diff) >= 360.0) {
        diff = fmod(diff, 360.0);
    }
    if (diff < 180.0) {
        if (diff <= max) {
            angle = diff;
        }
        else {
            angle = max;
        }
    }
    else if (360.0 - diff <= max) {
        angle = -(360.0 - diff);
    }
    else {
        angle = -max;
    }
    angle += end;
    if (angle >= 360.0) {
        angle -= 360.0;
    }
    else if (angle < 0.0) {
        angle += 360.0;
    }

    return angle;
}
