#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"

#include "ext_math.h"

#include "REL/m416Dll.h"

GXColor lbl_1_data_268 = { 0, 0, 0, 255 };
Vec lbl_1_data_26C[8] = {
    { 70, 0, 70 },
    { 70, 0, -70 },
    { -70, 0, -70 },
    { -70, 0, 70 },
    { 70, 0, 70 },
    { 70, 0, -70 },
    { -70, 0, -70 },
    { -70, 0, 70 },
};
Vec lbl_1_data_2CC[2] = { { 370, 615, -245 }, { -370, 615, -245 } };
float lbl_1_data_2E4[2] = { 0, 1 };

omObjData *lbl_1_bss_118C;
omObjData *lbl_1_bss_1188;
u32 lbl_1_bss_1184;
void *lbl_1_bss_1180;
float lbl_1_bss_117C;
s16 lbl_1_bss_1174[4];
float lbl_1_bss_116C[2];
s16 lbl_1_bss_1168;
s16 lbl_1_bss_968[256][4];

void fn_1_7A74(omObjData *object);
void fn_1_7D74(omObjData *object);
void fn_1_7F30(omObjData *object);
void fn_1_83B4(omObjData *object);

void fn_1_89BC(ModelData *model, Mtx mtx);

void fn_1_8EA0(void);
void fn_1_8FF0(void);

void fn_1_79D0(Process *objman)
{
    lbl_1_bss_118C = omAddObjEx(objman, 20, 2, 0, -1, fn_1_7A74);
    lbl_1_bss_1188 = omAddObjEx(objman, 20, 10, 0, -1, fn_1_7F30);
    fn_1_8EA0();
}

void fn_1_7A54(void)
{
    fn_1_8FF0();
}

void fn_1_7A74(omObjData *object)
{
    s16 i;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M416, 0x00));
    Hu3DModelShadowMapSet(object->model[0]);
    Hu3DModelLayerSet(object->model[0], 0);
    object->trans.x = 0;
    object->trans.y = 0;
    object->trans.z = 0;
    fn_1_8EB4(object->model[0]);
    for (i = 0; i < 2; i++) {
        lbl_1_bss_1174[i + 2] = Hu3DLLightCreate(object->model[0], 0, 0, 0, 0, 0, 0, 0, 0, 0);
        Hu3DLLightStaticSet(object->model[0], lbl_1_bss_1174[i + 2], 1);
        Hu3DLLightPointSet(object->model[0], lbl_1_bss_1174[i + 2], 45, 0.8, 3);
        Hu3DLLightColorSet(object->model[0], lbl_1_bss_1174[i + 2], 255, 160, 0, 255);
        Hu3DLLightPosSet(object->model[0], lbl_1_bss_1174[i + 2], lbl_1_data_2CC[i].x, 475, lbl_1_data_2CC[i].z, 0, 1, 0);
    }
    object->model[1] = Hu3DHookFuncCreate(fn_1_89BC);
    Hu3DModelLayerSet(object->model[1], 1);
    lbl_1_bss_1184 = GXGetTexBufferSize(640, 480, GX_TF_RGBA8, GX_FALSE, 0);
    lbl_1_bss_1180 = HuMemDirectMallocNum(HEAP_DATA, lbl_1_bss_1184, MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_1180, 0, lbl_1_bss_1184);
    object->func = fn_1_7D74;
}

void fn_1_7D74(omObjData *object)
{
    s32 i;
    for (i = 0; i < 2; i++) {
        Hu3DLLightPointSet(object->model[0], lbl_1_bss_1174[i + 2], (15 * sind(object->work[i])) + 45, 0.8, 3);
        object->work[i] += 8.0f;
        if (object->work[i] > 360.0f) {
            object->work[i] -= 360.0f;
        }
    }
}

void fn_1_7F30(omObjData *object)
{
    Mtx sp68;
    Mtx sp38;
    Mtx sp8;
    s32 temp_r30;
    Vec *temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    AnimData *temp_r23;
    object->stat |= 0x100;
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        if (temp_r30 == 0) {
            temp_r25 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M416, 0x01));
            temp_r26 = temp_r25;
        }
        else {
            temp_r24 = Hu3DModelLink(temp_r25);
            temp_r26 = temp_r24;
        }
        object->model[temp_r30] = temp_r26;
        Hu3DModelLayerSet(temp_r26, 2);
        fn_1_8EB4(object->model[temp_r30]);
        Hu3DModelPosSet(object->model[temp_r30], lbl_1_data_2CC[temp_r30].x, lbl_1_data_2CC[temp_r30].y, lbl_1_data_2CC[temp_r30].z);
    }
    temp_r23 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M416, 0x06));
    temp_r29 = &lbl_1_data_26C[0];
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        for (temp_r27 = 0; temp_r27 < 4; temp_r27++, temp_r29++) {
            temp_r28 = (temp_r30 * 4) + 2;
            temp_r28 = temp_r27 + temp_r28;
            object->model[temp_r28] = Hu3DParticleCreate(temp_r23, 50);
            Hu3DParticleHookSet(object->model[temp_r28], fn_1_613C);
            Hu3DParticleBlendModeSet(object->model[temp_r28], 1);
            Hu3DModelLayerSet(object->model[temp_r28], 6);
            Hu3DModelScaleSet(object->model[temp_r28], 0.5f, 0.7f, 0.5f);
            MTXTrans(sp68, lbl_1_data_2CC[temp_r30].x, lbl_1_data_2CC[temp_r30].y, lbl_1_data_2CC[temp_r30].z);
            MTXTrans(sp38, 0, -150, 0);
            MTXConcat(sp68, sp38, sp68);
            MTXTrans(sp8, temp_r29->x, temp_r29->y, temp_r29->z);
            MTXConcat(sp68, sp8, sp68);
            Hu3DModelPosSet(object->model[temp_r28], sp68[0][3], sp68[1][3], sp68[2][3]);
        }
    }
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        lbl_1_bss_1174[temp_r30] = Hu3DLLightCreate(object->model[temp_r30], 0, 0, 0, 0, 0, 0, 0, 0, 0);
        Hu3DLLightStaticSet(object->model[temp_r30], lbl_1_bss_1174[temp_r30], 1);
        Hu3DLLightPointSet(object->model[temp_r30], lbl_1_bss_1174[temp_r30], 1000, 0.8, 3);
        Hu3DLLightColorSet(object->model[temp_r30], lbl_1_bss_1174[temp_r30], 255, 160, 0, 255);
        Hu3DLLightPosSet(object->model[temp_r30], lbl_1_bss_1174[temp_r30], lbl_1_data_2CC[temp_r30].x, 475, lbl_1_data_2CC[temp_r30].z, 0, 1, 0);
    }
    object->work[0] = 0;
    object->work[1] = 45;
    lbl_1_bss_117C = 0;
    object->func = fn_1_83B4;
}

void fn_1_83B4(omObjData *object)
{
    float temp_f31;

    s32 temp_r31;
    Vec *temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    ModelData *temp_r26;

    Mtx sp130[2];
    Mtx sp100;
    Mtx spD0;
    Mtx spA0;
    Mtx sp70;
    Mtx sp40;
    Mtx sp10;
    float sp8[2];
    MTXIdentity(sp100);
    MTXIdentity(sp130[0]);
    MTXIdentity(sp130[1]);
    MTXIdentity(spD0);
    MTXIdentity(spA0);
    MTXIdentity(sp70);
    MTXIdentity(sp40);
    MTXIdentity(sp10);
    lbl_1_bss_117C = fmod(1 + lbl_1_bss_117C, 360);
    sp8[0] = 20 * sind(lbl_1_bss_117C);
    sp8[1] = 20 * cosd(lbl_1_bss_117C);
    if (fn_1_1240() == 6) {
        for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
            temp_f31 = sp8[temp_r31] - lbl_1_bss_116C[temp_r31];
            if (temp_f31 * lbl_1_data_2E4[temp_r31] <= 0.0f) {
                temp_r26 = &Hu3DData[object->model[temp_r31]];
                HuAudFXEmiterPlay(1467, &temp_r26->pos);
            }
            lbl_1_data_2E4[temp_r31] = temp_f31;
        }
    }
    lbl_1_bss_116C[0] = sp8[0];
    lbl_1_bss_116C[1] = sp8[1];
    temp_r29 = &lbl_1_data_26C[0];
    for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
        MTXRotDeg(sp130[temp_r31], 'y', lbl_1_bss_116C[temp_r31]);
        for (temp_r28 = 0; temp_r28 < 4; temp_r28++, temp_r29++) {
            temp_r27 = (temp_r31 * 4) + 2;
            temp_r27 = temp_r28 + temp_r27;
            MTXTrans(spA0, lbl_1_data_2CC[temp_r31].x, lbl_1_data_2CC[temp_r31].y, lbl_1_data_2CC[temp_r31].z);
            MTXTrans(sp70, 0, -150, 0);
            MTXConcat(spA0, sp70, spA0);
            MTXTrans(sp40, temp_r29->x, temp_r29->y, temp_r29->z);
            MTXConcat(sp130[temp_r31], sp40, sp10);
            MTXConcat(spA0, sp10, spA0);
            Hu3DModelPosSet(object->model[temp_r27], spA0[0][3], spA0[1][3], spA0[2][3]);
        }
    }
    Hu3DModelRotSet(object->model[0], 0, lbl_1_bss_116C[0], 0);
    Hu3DModelRotSet(object->model[1], 0, lbl_1_bss_116C[1], 0);
    for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
        Hu3DLLightPointSet(object->model[temp_r31], lbl_1_bss_1174[temp_r31], (15 * sind(object->work[temp_r31])) + 45, 0.9, 3);
        object->work[temp_r31] += 8.0f;
        if (object->work[temp_r31] > 360.0f) {
            object->work[temp_r31] -= 360.0f;
        }
    }
}

void fn_1_8904(void *arg0, u8 arg1)
{
    GXSetTexCopySrc(0, 0, 640, 480);
    GXSetTexCopyDst(640, 480, GX_TF_RGBA8, GX_FALSE);
    GXSetCopyClear(BGColor, 0xFFFFFF);
    GXCopyTex(arg0, arg1);
    DCFlushRange(arg0, lbl_1_bss_1184);
}

void fn_1_89BC(ModelData *model, Mtx mtx)
{
    Mtx44 sp34;
    GXTexObj sp14;
    MTXOrtho(sp34, 0, 480, 0, 576, 0, 1000);
    GXSetProjection(sp34, GX_ORTHOGRAPHIC);
    MTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, lbl_1_data_268);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_268);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXInitTexObj(&sp14, lbl_1_bss_1180, 640, 480, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&sp14, GX_TEXMAP0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_INVSRCALPHA, GX_BL_SRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0, 0, -10);
    GXTexCoord2f32(0, 0);
    GXPosition3f32(576, 0, -10);
    GXTexCoord2f32(1, 0);
    GXPosition3f32(576, 480, -10);
    GXTexCoord2f32(1, 1);
    GXPosition3f32(0, 480, -10);
    GXTexCoord2f32(0, 1);
    GXEnd();
    fn_1_8904(lbl_1_bss_1180, GX_FALSE);
#ifdef TARGET_PC
    GXDestroyTexObj(&sp14);
#endif
}

void fn_1_8EA0(void)
{
    lbl_1_bss_1168 = 0;
}

void fn_1_8EB4(s16 model)
{
    HsfMaterial *temp_r31;
    HsfData *temp_r30;
    s32 temp_r29;
    ModelData *temp_r28;
    s16 *temp_r27;
    s16 temp_r26;
    temp_r28 = &Hu3DData[model];
    temp_r30 = temp_r28->hsfData;
    temp_r26 = temp_r30->materialCnt;
    temp_r27 = &lbl_1_bss_968[lbl_1_bss_1168][0];
    *temp_r27 = model;
    temp_r31 = temp_r30->material;
    for (temp_r29 = 0; temp_r29 < temp_r26; temp_r31++, temp_r29++) {
        temp_r31->vtxMode = 1;
    }
    lbl_1_bss_1168++;
}

void fn_1_8F60(float arg0)
{
    s16 *temp_r31;
    s32 temp_r30;
    temp_r31 = &lbl_1_bss_968[0][0];
    for (temp_r30 = 0; temp_r30 < lbl_1_bss_1168; temp_r31 += 4, temp_r30++) {
        ModelData *sp8 = &Hu3DData[*temp_r31];
        Hu3DModelAmbSet(*temp_r31, arg0, arg0, arg0);
    }
}

void fn_1_8FF0(void) { }

void fn_1_8FF4(float arg0)
{
    lbl_1_data_268.a = arg0 * 255;
}
