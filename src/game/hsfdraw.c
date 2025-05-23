#include "game/hsfdraw.h"
#include "game/hsfanim.h"
#include "game/hsfformat.h"
#include "game/hsfload.h"
#include "game/sprite.h"
#include "game/disp.h"

#include "ext_math.h"
#include "string.h"

static void objCall(ModelData *arg0, HsfObject *arg1);
static void objMesh(ModelData *arg0, HsfObject *arg1);
static void SetTevStageNoTex(HsfDrawObject *arg0, HsfMaterial *arg1);
static void SetTevStageTex(HsfDrawObject *arg0, HsfMaterial *arg1);
static GXTevKColorSel SetKColor(GXTevStageID arg0, u8 arg1);
static GXTevKColorSel SetKColorRGB(GXTevStageID arg0, GXColor *arg1);
static void FlushKColor(void);
static void SetReflect(HsfDrawObject *arg0, s16 arg1, s16 arg2, u8 arg3);
static void SetProjection(HsfDrawObject *arg0, s16 arg1, s16 arg2, s16 arg3, GXTexMapID arg4, u32 arg5);
static void SetShadowTex(void);
static void SetShadow(HsfDrawObject *arg0, s16 arg1, s16 arg2);
static void FaceDrawShadow(HsfDrawObject *arg0, HsfFace *arg1);
static void LoadTexture(ModelData *arg0, HsfBitmap *arg1, HsfAttribute *arg2, s16 arg3);
static void objNull(ModelData *arg0, HsfObject *arg1);
static void objRoot(ModelData *arg0, HsfObject *arg1);
static void objJoint(ModelData *arg0, HsfObject *arg1);
static void objMap(ModelData *arg0, HsfObject *arg1);
static void objReplica(ModelData *arg0, HsfObject *arg1);
static void ObjDraw(HsfDrawObject *arg0);
static void MDObjCall(HsfData *arg0, HsfObject *arg1);
static void MDObjMesh(HsfData *arg0, HsfObject *arg1);
static void MDFaceDraw(HsfObject *arg0, HsfFace *arg1);
static s32 MakeCalcNBT(HsfObject *arg0, HsfFace *arg1, s16 arg2, s16 arg3);
static s32 MakeNBT(HsfObject *arg0, HsfFace *arg1, s16 arg2, s16 arg3);
static void MDFaceCnt(HsfObject *arg0, HsfFace *arg1);

void GXResetWriteGatherPipe(void);

static const Vec lbl_8011DD20 = { 0.0f, 0.0f, -1.0f };

static HsfDrawObject DrawObjData[HU3D_MODEL_MAX];
static HsfAttribute *BmpPtrBak[8];
static Mtx MTXBuf[96];
static Vec scaleBuf[96];
static GXColor texCol[16];
static Mtx hiliteMtx;
static s16 DrawObjNum[HU3D_MODEL_MAX];
static Vec NBTB;
static Vec NBTT;
Vec PGMaxPos;
Vec PGMinPos;

s16 MTXIdx;
static HsfMaterial *materialBak;
static u8 polyTypeBak;
static s32 shadingBak;
static void *DLBufP;
static void *DLBufStartP;
static HsfDrawData *DrawData;
static s32 drawCnt;
static s16 lightBit;
static s16 DrawObjIdx;
static HsfConstData *Hu3DObjInfoP;
static s16 reflectionMapNo;
static s16 hiliteMapNo;
static s16 vtxModeBak;
static s32 attachMotionF;
static s16 shadowMapNo;
static s16 toonMapNo;
static s16 projectionMapNo;
static GXColor kColor;
static s32 kColorIdx;
static s16 hookIdx;
u32 totalPolyCnt;
u32 totalPolyCnted;
u32 totalMatCnt;
u32 totalMatCnted;
u32 totalTexCnt;
u32 totalTexCnted;
u32 totalTexCacheCnt;
u32 totalTexCacheCnted;
s16 modelMeshNum;
s16 modelObjNum;
static s32 DLFirstF;
static u16 matChgCnt;
static u16 triCnt;
static u16 quadCnt;
static u16 faceCnt;
static u16 *faceNumBuf;
static s32 DLTotalNum;
static u32 totalSize;
static u32 mallocNo;
static s32 curModelID;
static s16 polySize;
static s32 PGFinishF;
static u8 *PGName;
static s32 TL32F;
static s32 CancelTRXF;

u8 texMtxTbl[] = {
    GX_TEXMTX0, GX_TEXMTX1,
    GX_TEXMTX2, GX_TEXMTX3,
    GX_TEXMTX4, GX_TEXMTX5,
    GX_TEXMTX6, GX_TEXMTX7,
    GX_TEXMTX8, GX_TEXMTX9
};

static s16 oneceF = 1;
static GXColor firstTev = { 0xFF, 0xFF, 0x00, 0x00 };
static GXColor secondTev = { 0x00, 0x00, 0xFF, 0xFF };

void Hu3DDrawPreInit(void) {
    DrawObjIdx = 0;
}

void Hu3DDraw(ModelData *arg0, Mtx arg1, Vec *arg2) {
    HsfDrawObject *temp_r31;
    HsfData *temp_r28;
    float temp_f31;
    Vec sp8;
    s16 i;

    temp_r28 = arg0->hsfData;
    if (arg0->attr & HU3D_ATTR_HOOKFUNC) {
        temp_r31 = &DrawObjData[DrawObjIdx];
        PSMTXCopy(arg1, temp_r31->matrix);
        sp8.x = temp_r31->matrix[0][3];
        sp8.y = temp_r31->matrix[1][3];
        sp8.z = temp_r31->matrix[2][3];
        temp_f31 = VECMag(&sp8);
        temp_r31->z = temp_f31;
        temp_r31->model = arg0;
        DrawObjIdx++;
        return;
    }
    modelMeshNum = 0;
    modelObjNum = 0;
    GXSetCullMode(GX_CULL_BACK);
    for (i = 0; i < 8; i++) {
        BmpPtrBak[i] = (HsfAttribute*) -1;
    }
    PSMTXCopy(arg1, MTXBuf[0]);
    scaleBuf[0] = *arg2;
    MTXIdx = 1;
    CancelTRXF = 0;
    hookIdx = -1;
    shadingBak = -1;
    vtxModeBak = -1;
    materialBak = (HsfMaterial*) -1;
    if (arg0->unk_08 != -1) {
        attachMotionF = 1;
    } else {
        attachMotionF = 0;
    }
    objCall(arg0, temp_r28->root);
    GXSetNumTevStages(1);
    oneceF = 1;
}

static void objCall(ModelData *arg0, HsfObject *arg1) {
    modelObjNum++;
    switch (arg1->type) {
        case 2:
            objMesh(arg0, arg1);
            modelMeshNum++;
            break;
        case 4:
            objJoint(arg0, arg1);
            break;
        case 5:
            objNull(arg0, arg1);
            break;
        case 0:
            objNull(arg0, arg1);
            break;
        case 1:
            objReplica(arg0, arg1);
            break;
        case 3:
            objRoot(arg0, arg1);
            break;
        case 6:
            objNull(arg0, arg1);
            break;
        case 9:
            objMap(arg0, arg1);
            break;
    }
}

static void objMesh(ModelData *arg0, HsfObject *arg1) {
    HsfDrawObject *temp_r29;
    HsfConstData *temp_r25;
    HsfTransform *var_r30;
    HsfData *temp_r20;
    ModelData *temp_r31;
    Mtx sp1C;
    Vec sp10;
    Vec *temp_r24;
    Vec *temp_r28;
    void *spC;
    s16 sp8;
    s16 temp_r21;
    s16 var_r18;
    s16 var_r19;
    float temp_f31;
    HsfBuffer *temp_r17;

    temp_r17 = arg1->data.face;
    spC = temp_r17->data;
    temp_r29 = &DrawObjData[DrawObjIdx];
    temp_r20 = arg0->hsfData;
    if (attachMotionF == 0) {
        var_r30 = &arg1->data.base;
    } else {
        var_r30 = &arg1->data.curr;
    }
    temp_r25 = arg1->constData;
    if (!(temp_r25->flags & 0x1000)) {
        if (CancelTRXF == 0) {
            if (arg1->data.cenvCnt != 0 && hookIdx == -1) {
                temp_r21 = arg1 - temp_r20->object;
                PSMTXConcat(MTXBuf[0], temp_r20->matrix->data[temp_r21 + temp_r20->matrix->base_idx], MTXBuf[MTXIdx]);
            } else {
                PSMTXScale(sp1C, var_r30->scale.x, var_r30->scale.y, var_r30->scale.z);
                mtxRotCat(sp1C, var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
                mtxTransCat(sp1C, var_r30->pos.x, var_r30->pos.y, var_r30->pos.z);
                PSMTXConcat(MTXBuf[MTXIdx - 1], sp1C, MTXBuf[MTXIdx]);
            }
            temp_r28 = &scaleBuf[MTXIdx];
            temp_r24 = temp_r28 - 1;
            temp_r28->x = temp_r24->x * var_r30->scale.x;
            temp_r28->y = temp_r24->y * var_r30->scale.y;
            temp_r28->z = temp_r24->z * var_r30->scale.z;
            temp_r29->scale = *temp_r28;
            if (arg1->flags & 1) {
                PSMTXInverse(MTXBuf[MTXIdx], sp1C);
                sp1C[0][3] = sp1C[1][3] = sp1C[2][3] = 0.0f;
                PSMTXConcat(MTXBuf[MTXIdx], sp1C, temp_r29->matrix);
                mtxScaleCat(temp_r29->matrix, temp_r28->x, temp_r28->y, temp_r28->z);
            } else {
                PSMTXCopy(MTXBuf[MTXIdx], temp_r29->matrix);
            }
            MTXIdx++;
            var_r18 = 1;
        } else {
            if (arg1->flags & 1) {
                PSMTXInverse(MTXBuf[MTXIdx - 1], sp1C);
                sp1C[0][3] = sp1C[1][3] = sp1C[2][3] = 0.0f;
                PSMTXConcat(MTXBuf[MTXIdx - 1], sp1C, temp_r29->matrix);
                mtxScaleCat(temp_r29->matrix, scaleBuf[MTXIdx - 1].x, scaleBuf[MTXIdx - 1].y, scaleBuf[MTXIdx - 1].z);
            } else {
                PSMTXCopy(MTXBuf[MTXIdx - 1], temp_r29->matrix);
            }
            temp_r29->scale = scaleBuf[MTXIdx - 1];
            CancelTRXF = 0;
            var_r18 = 0;
        }
        PSMTXCopy(temp_r29->matrix, temp_r25->matrix);
        if (temp_r25->hook != -1) {
            temp_r31 = &Hu3DData[temp_r25->hook];
            if (!(temp_r31->attr & HU3D_ATTR_DISPOFF)) {
                temp_r21 = attachMotionF;
                if (temp_r31->unk_08 != -1) {
                    attachMotionF = 1;
                } else {
                    attachMotionF = 0;
                }
                sp8 = hookIdx;
                hookIdx = temp_r25->hook;
                PSMTXScale(sp1C, temp_r31->scale.x, temp_r31->scale.y, temp_r31->scale.z);
                mtxRotCat(sp1C, temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
                mtxTransCat(sp1C, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
                PSMTXConcat(sp1C, temp_r31->unk_F0, sp1C);
                PSMTXConcat(temp_r29->matrix, sp1C, MTXBuf[MTXIdx]);
                temp_r28 = &scaleBuf[MTXIdx];
                temp_r24 = temp_r28 - 1;
                temp_r28->x = temp_r24->x * temp_r31->scale.x;
                temp_r28->y = temp_r24->y * temp_r31->scale.y;
                temp_r28->z = temp_r24->z * temp_r31->scale.z;
                MTXIdx++;
                objCall(temp_r31, temp_r31->hsfData->root);
                MTXIdx--;
                hookIdx = sp8;
                attachMotionF = temp_r21;
            }
        } else {
            if (arg0->attr & HU3D_ATTR_NOCULL) {
                var_r19 = ObjCullCheck(arg0->hsfData, arg1, temp_r29->matrix);
            } else {
                var_r19 = 1;
            }
            if ((temp_r25->flags & 0x2000) || (arg1->flags & HU3D_ATTR_CLUSTER_ON)) {
                var_r19 = 0;
            }
            if (var_r19 != 0 && (var_r30->scale.x != 0.0f || var_r30->scale.y != 0.0f || var_r30->scale.z != 0.0f)) {
                temp_r29->model = arg0;
                temp_r29->object = arg1;
                if ((temp_r25->flags & 0x10801) && shadowModelDrawF == 0) {
                    sp10.x = temp_r29->matrix[0][3];
                    sp10.y = temp_r29->matrix[1][3];
                    sp10.z = temp_r29->matrix[2][3];
                    temp_f31 = VECMag(&sp10);
                    if (temp_r25->flags & 0x10000) {
                        temp_r29->z = -(900000.0f - temp_f31);
                    } else {
                        temp_r29->z = -(1000000.0f - temp_f31);
                    }
                    DrawObjIdx++;
                    if (DrawObjIdx > 0x200) {
                        OSReport("Error: DrawObjIdx Over\n");
                        DrawObjIdx--;
                    }
                } else if (arg0->attr & HU3D_ATTR_ZCMP_OFF) {
                    temp_r29->z = -1000000.0f;
                    DrawObjIdx++;
                    if (DrawObjIdx > 0x200) {
                        OSReport("Error: DrawObjIdx Over\n");
                        DrawObjIdx--;
                    }
                } else {
                    materialBak = (HsfMaterial*) -1;
                    ObjDraw(temp_r29);
                }
            }
        }
        for (temp_r21 = 0; temp_r21 < arg1->data.childrenCount; temp_r21++) {
            objCall(arg0, arg1->data.children[temp_r21]);
        }
        if (var_r18 != 0) {
            MTXIdx--;
        }
    }
}

s32 ObjCullCheck(HsfData *arg0, HsfObject *arg1, Mtx arg2) {
    CameraData *temp_r30;
    HsfVector3f *temp_r29;
    HsfVector3f *temp_r31;
    Mtx sp28;
    float sp24;
    float temp_f20;
    float temp_f19;
    float temp_f18;
    float temp_f21;
    float temp_f24;
    float temp_f23;
    float temp_f22;
    float temp_f27;
    float var_f26;
    float temp_f25;
    float temp_f31;
    float temp_f30;
    float temp_f29;

    temp_r30 = &Hu3DCamera[Hu3DCameraNo];
    temp_r31 = &arg1->data.mesh.min;
    temp_r29 = &arg1->data.mesh.max;
    temp_f23 = scaleBuf[MTXIdx - 1].x;
    temp_f22 = scaleBuf[MTXIdx - 1].y;
    temp_f25 = scaleBuf[MTXIdx - 1].z;
    if (temp_f23 > temp_f22) {
        if (temp_f23 > temp_f25) {
            var_f26 = temp_f23;
        } else if (temp_f22 > temp_f25) {
            var_f26 = temp_f22;
        } else {
            var_f26 = temp_f25;
        }
    } else if (temp_f22 > temp_f25) {
        var_f26 = temp_f22;
    } else if (temp_f23 > temp_f25) {
        var_f26 = temp_f23;
    } else {
        var_f26 = temp_f25;
    }
    temp_f31 = (temp_r29->x - temp_r31->x) * 0.5;
    temp_f30 = (temp_r29->y - temp_r31->y) * 0.5;
    temp_f29 = (temp_r29->z - temp_r31->z) * 0.5;
    PSMTXTrans(sp28, temp_f31 + temp_r31->x, temp_f30 + temp_r31->y, temp_f29 + temp_r31->z);
    PSMTXConcat(arg2, sp28, sp28);
    temp_f21 = var_f26 * sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30 + temp_f29 * temp_f29);
    temp_f20 = sp28[0][3];
    temp_f19 = sp28[1][3];
    temp_f18 = -sp28[2][3];
    if (temp_f18 + temp_f21 < temp_r30->near || temp_f18 - temp_f21 > temp_r30->far) {
        return 0;
    }
    sp24 = sind(temp_r30->fov * 0.5) / cosd(temp_r30->fov * 0.5);
    temp_f27 = sp24 * temp_f18;
    temp_f24 = HU_DISP_ASPECT * temp_f27;
    temp_f24 = temp_f21 + ABS(temp_f24);
    temp_f27 = temp_f21 + ABS(temp_f27);
    if (ABS(temp_f20) < temp_f24 && ABS(temp_f19) < temp_f27) {
        return 1;
    }
    return 0;
}

inline void SetBlendMode(u32 flags) {
    if (flags & 0x30) {
        if (flags & 0x10) {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        } else {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
        }
    } else {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }
}

inline void SetupGX(const HsfMaterial* material, const HsfConstData* constData, const ModelData* modelData, u32 flags, s16 tevStage) {
    if ((material->invAlpha != 0.0f || (material->pass & 0xF) || (constData->flags & 0x800)) && !((modelData->attr & HU3D_ATTR_ZWRITE_OFF) | (flags & 0x1200))) {
        GXSetZMode(tevStage, GX_LEQUAL, GX_FALSE);
    } else {
        GXSetZMode(tevStage, GX_LEQUAL, GX_TRUE);
    }

    if (flags & 0x1200) {
        GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_GEQUAL, 0x80);
    } else {
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    }

    if (modelData->attr & HU3D_ATTR_CULL_FRONT) {
        GXSetCullMode(GX_CULL_FRONT);
    } else if (flags & 2) {
        GXSetCullMode(GX_CULL_NONE);
    } else {
        GXSetCullMode(GX_CULL_BACK);
    }
}

static void FaceDraw(HsfDrawObject *hsfDrawObject, HsfFace *hsfFace) {
    GXColor tempColor;
    void *displayListPtr;
    Hu3DTexAnimDataStruct *texAnimData;
	s16 tevStage;
	HsfMaterial *faceMaterial;
	ModelData *model;
	HsfObject *object;
	HsfBitmap *currentBitmap;
    HsfAttribute *currentAttribute;
	HsfdrawStruct01 *currentDrawData;
	HsfConstData *constData;
    s16 var_r24;
    s16 vtxMode;
	s16 textureIdx; // var_r21
    u32 flags;
    s16 hiliteAnimIdx;
    s16 reflectAnimIdx;

    object = hsfDrawObject->object;
    model = hsfDrawObject->model;
    constData = object->constData;
    kColorIdx = 0;
    faceMaterial = &object->data.material[hsfFace->mat & 0xFFF];
    flags = object->flags | faceMaterial->flags;
    SetBlendMode(flags);
    
    if (faceMaterial != materialBak) {
        totalMatCnt++;
        materialBak = faceMaterial;
        tempColor.r = faceMaterial->litColor[0] * model->unk_58.x;
        tempColor.g = faceMaterial->litColor[1] * model->unk_58.z;
        tempColor.b = faceMaterial->litColor[2] * model->unk_58.y;
        tempColor.a = 0xFF;
        GXSetChanAmbColor(GX_COLOR0A0, tempColor);
        tempColor.r = faceMaterial->color[0];
        tempColor.g = faceMaterial->color[1];
        tempColor.b = faceMaterial->color[2];
        tempColor.a = 0xFF;
        GXSetChanMatColor(GX_COLOR0A0, tempColor);
        
        if (model->attr & HU3D_ATTR_ZCMP_OFF) {
            tevStage = GX_FALSE;
        } else {
            tevStage = GX_TRUE;
        }
        
        SetupGX(faceMaterial, constData, model, flags, tevStage);
        
        if (TL32F != 0) {
            for (tevStage = GX_TEVSTAGE0; tevStage < GX_MAX_TEVSTAGE; tevStage++) {
                GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
            }
            TL32F = 0;
        }
        
        for (tevStage = GX_TEVSTAGE0; tevStage < GX_MAX_TEVSTAGE; tevStage++) {
            GXSetTevKAlphaSel(tevStage, GX_TEV_KASEL_1);
        }
        
        if (faceMaterial->numAttrs == 0) {
            vtxMode = (faceMaterial->vtxMode == 5) ? 4 : 0;
            if (vtxMode != vtxModeBak) {
                vtxModeBak = vtxMode;
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, object->data.vertex->data, 3 * sizeof(float));
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                if (model->hsfData->cenvCnt == 0) {
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 0);
                    GXSetArray(GX_VA_NRM, object->data.normal->data, 3);
                } else {
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                    GXSetArray(GX_VA_NRM, object->data.normal->data, 3 * sizeof(float));
                }
                if (vtxMode & 4) {
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                    GXSetArray(GX_VA_CLR0, object->data.color->data, 4);
                }
                GXSetZCompLoc(1);
            }
            if (faceMaterial->refAlpha != 0.0f) {
                reflectionMapNo = 0;
                BmpPtrBak[0] = (HsfAttribute*) -1;
                if (model->unk_04 != -1) {
                    reflectAnimIdx = model->unk_04;
                } else {
                    reflectAnimIdx = reflectMapNo;
                }
                HuSprTexLoad(reflectAnim[reflectAnimIdx], 0, reflectionMapNo, GX_REPEAT, GX_REPEAT, GX_LINEAR);
            }
            if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->flags & 8)) {
                shadowMapNo = 1;
                SetShadowTex();
                BmpPtrBak[1] = (HsfAttribute*) -1;
            }
            if (model->attr & HU3D_ATTR_TOON_MAP) {
                toonMapNo = 2;
                HuSprTexLoad(toonAnim, 0, toonMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                BmpPtrBak[2] = (HsfAttribute*) -1;
            }
            if (model->unk_02 != 0) {
                projectionMapNo = 3;
                hiliteMapNo = projectionMapNo + 1;
                for (tevStage = 0, var_r24 = 1; tevStage < 4; tevStage++, var_r24 <<= 1) {
                    if (var_r24 & model->unk_02) {
                        HuSprTexLoad(Hu3DProjection[tevStage].unk_04, 0, projectionMapNo + tevStage, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                        BmpPtrBak[projectionMapNo + tevStage] = (HsfAttribute*) -1;
                        hiliteMapNo++;
                    }
                }
            } else {
                hiliteMapNo = 3;
            }
            if ((model->attr & HU3D_ATTR_HILITE) || (flags & 0x100)) {
                if (constData->hiliteMap == 0) {
                    if (faceMaterial->flags != 0) {
                        hiliteAnimIdx = (faceMaterial->pass >> 4) & 0xF;
                    } else {
                        hiliteAnimIdx = (object->data.unk123 >> 4) & 0xF;
                    }
                    HuSprTexLoad(hiliteAnim[hiliteAnimIdx], 0, hiliteMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                } else {
                    HuSprTexLoad(constData->hiliteMap, 0, hiliteMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                }
                BmpPtrBak[hiliteMapNo] = (HsfAttribute*) -1;
            }
            SetTevStageNoTex(hsfDrawObject, faceMaterial);
        } else {
            vtxMode = (faceMaterial->vtxMode == 5) ? 5 : 1;
            if (DrawData[drawCnt].flags & 2) {
                vtxMode |= 2;
            }
            if (vtxMode != vtxModeBak) {
                vtxModeBak = vtxMode;
                    GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, object->data.vertex->data, 3 * sizeof(float));
                if (vtxMode & 2) {
                    GXSetVtxDesc(GX_VA_NBT, GX_DIRECT);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NBT, GX_NRM_NBT, GX_S16, 8);
                } else {
                    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                    if (model->hsfData->cenvCnt == 0) {
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 0);
                        GXSetArray(GX_VA_NRM, object->data.normal->data, 3);
                    } else {
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                        GXSetArray(GX_VA_NRM, object->data.normal->data, 3 * sizeof(float));
                    }
                }
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
                GXSetArray(GX_VA_TEX0, object->data.st->data, 2 * sizeof(float));
                if (vtxMode & 4) {
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                    GXSetArray(GX_VA_CLR0, object->data.color->data, 4);
                }
                GXSetZCompLoc(0);
            }
            textureIdx = faceMaterial->numAttrs;
            for (tevStage = 0; tevStage < faceMaterial->numAttrs; tevStage++) {
                currentAttribute = &object->data.attribute[faceMaterial->attrs[tevStage]];
                currentBitmap = currentAttribute->bitmap;
                if (currentAttribute->unk04 != 0) {
                    texCol[tevStage].a = 0;
                    currentDrawData = currentAttribute->unk04;
                    texAnimData = &Hu3DTexAnimData[currentDrawData->unk02];
                    if (((currentDrawData->unk00) & 1) && !(texAnimData->unk00 & 4)) {
                        if (Hu3DAnimSet(hsfDrawObject->model, currentAttribute, (s32) tevStage) != 0) {
                            BmpPtrBak[tevStage] = (HsfAttribute*) -1;
                            totalTexCnt++;
                            continue;
                        }
                    } else if (currentDrawData->unk00 & 8) {
                        currentBitmap = currentDrawData->unk3C;
                        if (currentBitmap->dataFmt != 0xB) {
                            LoadTexture(hsfDrawObject->model, currentBitmap, currentAttribute, (s32) tevStage); // or: tevStage | 0x0000?
                        } else {
                            LoadTexture(hsfDrawObject->model, currentDrawData->unk3C, currentAttribute, (s32) tevStage);
                            LoadTexture(hsfDrawObject->model, currentDrawData->unk3C, currentAttribute, textureIdx | 0x8000);
                            texCol[tevStage].r = (s16) textureIdx;
                            texCol[tevStage].a = 2;
                            textureIdx++;
                        }
                        if (currentBitmap->sizeX * currentBitmap->sizeY * currentBitmap->pixSize > 0x40000) {
                            for (var_r24 = 0; var_r24 < 8; var_r24++) {
                                BmpPtrBak[var_r24] = (HsfAttribute*) -1;
                            }
                        } else {
                            BmpPtrBak[tevStage] = (HsfAttribute*) -1;
                        }
                        totalTexCnt++;
                        continue;
                    }
                }
                if (BmpPtrBak[tevStage] != currentAttribute) {
                    if (BmpPtrBak[tevStage] != (HsfAttribute*) -1 && BmpPtrBak[tevStage]->bitmap == currentBitmap && currentAttribute->wrap_s == BmpPtrBak[tevStage]->wrap_s && currentAttribute->wrap_t == BmpPtrBak[tevStage]->wrap_t) {
                        if (currentBitmap->dataFmt == 0xB) {
                            TL32F = 1;
                        }
                        totalTexCacheCnt++;
                    } else {
                        texCol[tevStage].a = 0;
                        if (currentBitmap->dataFmt != 0xB) {
                            LoadTexture(hsfDrawObject->model, currentBitmap, currentAttribute, (s32) tevStage);
                        } else {
                            LoadTexture(hsfDrawObject->model, currentBitmap, currentAttribute, (s32) tevStage);
                            LoadTexture(hsfDrawObject->model, currentBitmap, currentAttribute, textureIdx | 0x8000);
                            texCol[tevStage].r = (s16) textureIdx;
                            texCol[tevStage].a = 2;
                            textureIdx++;
                        }
                        if (currentBitmap->sizeX * currentBitmap->sizeY * currentBitmap->pixSize > 0x40000) {
                            for (var_r24 = 0; var_r24 < 8; var_r24++) {
                                BmpPtrBak[var_r24] = (HsfAttribute*) -1;
                            }
                        } else {
                            BmpPtrBak[tevStage] = currentAttribute;
                        }
                        totalTexCnt++;
                    }
                } else {
                    totalTexCacheCnt++;
                }
            }
            if (faceMaterial->refAlpha != 0.0f) {
                reflectionMapNo = (s16) textureIdx;
                shadowMapNo = reflectionMapNo + 1;
                if (model->unk_04 != -1) {
                    reflectAnimIdx = model->unk_04;
                } else {
                    reflectAnimIdx = reflectMapNo;
                }
                HuSprTexLoad(reflectAnim[reflectAnimIdx], 0, reflectionMapNo, GX_REPEAT, GX_REPEAT, GX_LINEAR);
                BmpPtrBak[reflectionMapNo] = (HsfAttribute*) -1;
            } else {
                shadowMapNo = (s16) textureIdx;
            }
            if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->flags & 8)) {
                toonMapNo = shadowMapNo + 1;
                SetShadowTex();
                BmpPtrBak[shadowMapNo] = (HsfAttribute*) -1;
            } else {
                toonMapNo = shadowMapNo;
            }
            if (model->attr & HU3D_ATTR_TOON_MAP) {
                HuSprTexLoad(toonAnim, 0, toonMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                BmpPtrBak[toonMapNo] = (HsfAttribute*) -1;
                projectionMapNo = toonMapNo + 1;
            } else {
                projectionMapNo = toonMapNo;
            }
            if (model->unk_02 != 0) {
                for (tevStage = 0, var_r24 = 1; tevStage < 4; tevStage++, var_r24 <<= 1) {
                    if (var_r24 & model->unk_02) {
                        HuSprTexLoad(Hu3DProjection[tevStage].unk_04, 0, projectionMapNo + tevStage, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                        BmpPtrBak[projectionMapNo + tevStage] = (HsfAttribute*) -1;
                        hiliteMapNo = projectionMapNo + tevStage + 1;
                    }
                }
            } else {
                hiliteMapNo = projectionMapNo;
            }
            if ((model->attr & HU3D_ATTR_HILITE) || (flags & 0x100)) {
                if (constData->hiliteMap == 0) {
                    if (faceMaterial->flags != 0) {
                        hiliteAnimIdx = ((faceMaterial->pass >> 4) & 0xF);
                    } else {
                        hiliteAnimIdx = ((object->data.unk123 >> 4) & 0xF);
                    }
                    HuSprTexLoad(hiliteAnim[hiliteAnimIdx], 0, hiliteMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                } else {
                    HuSprTexLoad(constData->hiliteMap, 0, hiliteMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                }
                BmpPtrBak[toonMapNo] = (HsfAttribute*) -1;
            }
            SetTevStageTex(hsfDrawObject, faceMaterial);
        }
        displayListPtr = (u8*) DLBufStartP + DrawData[drawCnt].dlOfs;
        GXCallDisplayList(displayListPtr, DrawData[drawCnt].dlSize);
    } else {
        displayListPtr = (u8*) DLBufStartP + DrawData[drawCnt].dlOfs;
        GXCallDisplayList(displayListPtr, DrawData[drawCnt].dlSize);
    }
    drawCnt++;
}

static void SetTevStageNoTex(HsfDrawObject *arg0, HsfMaterial *arg1) {
    GXColor sp1C;
    ModelData *temp_r28;
    HsfObject *var_r21;
    float var_f30;
    float var_f31;
    s16 var_r23;
    s16 var_r26;
    s16 var_r25;
    s16 var_r29;
    s16 var_r30;
    s16 var_r24;
    u32 var_r20;
    GXChannelID var_r19;
    GXTevAlphaArg var_r18;
    u32 var_r22;
    u32 sp18;
    Mtx sp20;

    var_r30 = 1;
    var_r29 = 0;
    var_r21 = arg0->object;
    temp_r28 = arg0->model;
    sp18 = var_r21->flags | arg1->flags;
    if (arg1->vtxMode == 2 || arg1->vtxMode == 3) {
        var_r26 = 1;
        var_r24 = 1;
    } else {
        var_r26 = 0;
        if (arg1->vtxMode == 0 || arg1->vtxMode == 5) {
            var_r24 = 0;
        } else {
            var_r24 = 1;
        }
    }
    if ((Hu3DObjInfoP->flags & 0x4000) && arg1->vtxMode == 5) {
        var_r19 = GX_COLOR0A0;
        var_r18 = GX_CA_RASA;
        var_r22 = 1;
    } else {
        var_r19 = GX_COLOR0;
        var_r18 = GX_CA_KONST;
        var_r22 = 0;
    }
    sp1C.a = 255.0f * (1.0f - arg1->invAlpha);
    if (temp_r28->attr & HU3D_ATTR_TOON_MAP) {
        sp1C.r = arg1->color[0];
        sp1C.g = arg1->color[1];
        sp1C.b = arg1->color[2];
        GXSetTevColor(GX_TEVREG0, sp1C);
        GXSetTexCoordGen2(var_r29, GX_TG_SRTG, GX_TG_COLOR0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE0, var_r29, toonMapNo, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        var_r29++;
    } else {
        GXSetTevColor(GX_TEVREG0, sp1C);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, var_r19);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, var_r18);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    }
    if (arg1->refAlpha != 0.0f) {
        SetReflect(arg0, var_r30, (s16) var_r29, arg1->refAlpha * 255.0f);
        var_r30++;
        var_r29++;
    }
    if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->flags & 8)) {
        SetShadow(arg0, var_r30, (s16) var_r29);
        var_r30++;
        var_r29++;
    }
    if (var_r26 != 0) {
        if ((temp_r28->attr & HU3D_ATTR_HILITE) || (sp18 & 0x100)) {
            GXSetTexCoordGen2(var_r29, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX7, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(var_r30, var_r29, hiliteMapNo, GX_COLOR0A0);
            GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_ONE, GX_CC_TEXC, GX_CC_CPREV);
            GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            var_f31 = 6.0f * (arg1->hilite_scale / 300.0f);
            if (var_f31 < 0.1) {
                var_f31 = 0.1f;
            }
            PSMTXCopy(hiliteMtx, sp20);
            mtxScaleCat(sp20, var_f31, var_f31, var_f31);
            GXLoadTexMtxImm(sp20, GX_TEXMTX7, GX_MTX2x4);
            var_r30++;
            var_r29++;
            var_r24 = 1;
            var_r26 = 0;
        } else {
            GXSetTevOrder(var_r30, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR1A1);
            GXSetTevColorIn(var_r30, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            var_r30++;
        }
    } else if (arg1->invAlpha != 0.0f) {
        GXSetTevOrder(var_r30, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_ONE, GX_CC_CPREV, GX_CC_ZERO);
        GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
        GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        var_r30++;
    }
    if (temp_r28->unk_02 != 0) {
        for (var_r25 = 0, var_r23 = 1; var_r25 < 4; var_r25++, var_r23 <<= 1) {
            if (var_r23 & temp_r28->unk_02) {
                SetProjection(arg0, var_r30, var_r25, (GXTexMapID) var_r29, projectionMapNo + var_r25, texMtxTbl[var_r25 + 3]);
                var_r29++;
                var_r30 += 2;
            }
        }
    }
    FlushKColor();
    GXSetNumTexGens(var_r29);
    GXSetNumTevStages(var_r30);
    var_r20 = (var_r26 != 0) ? 2 : arg1->vtxMode;
    if (var_r20 != shadingBak) {
        shadingBak = var_r20;
        if (var_r26 != 0) {
            var_f30 = arg1->hilite_scale;
        } else {
            var_f30 = 0.0f;
        }
        lightBit = Hu3DLightSet(arg0->model, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, var_f30);
    }
    if (var_r26 != 0) {
        GXSetNumChans(2);
        if (arg1->vtxMode == 5) {
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR1, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_NONE, GX_AF_SPEC);
            if (var_r22 != 0) {
                GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
                GXSetChanCtrl(GX_ALPHA1, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPEC);
            } else {
                GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
                GXSetChanCtrl(GX_ALPHA1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            }
        } else {
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR1, GX_TRUE, GX_SRC_REG, GX_SRC_REG, lightBit, GX_DF_NONE, GX_AF_SPEC);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_ALPHA1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
        }
    } else {
        GXSetNumChans(1);
        if (arg1->vtxMode == 5) {
            GXSetChanCtrl(GX_COLOR0, var_r24, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            if (var_r22 != 0) {
                GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            } else {
                GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            }
        } else {
            GXSetChanCtrl(GX_COLOR0, var_r24, GX_SRC_REG, GX_SRC_REG, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
        }
        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    }
}

static Mtx refMtx = {
    { 0.25f,   0.0f,  0.0f, -0.5f },
    {  0.0f, -0.25f,  0.0f, -0.5f },
    {  0.0f,   0.0f, 0.25f, -0.5f }
};

static void SetTevStageTex(HsfDrawObject *arg0, HsfMaterial *arg1) {
    GXColor sp50;
    GXTexMapID sp4C;
    GXTevStageID sp48;
    s32 sp44;
    u32 sp40;
    GXChannelID sp3C;
    u32 sp38;
    HsfAttribute *temp_r29;
    HsfObject *temp_r19;
    ModelData *temp_r25;
    HsfdrawStruct01 *temp_r28;
    GXTevAlphaArg var_r17;
    float var_f30;
    float var_f31;
    u16 sp8;
    u16 temp_r23;
    u16 var_r22;
    u16 var_r30;
    u16 var_r31;
    u16 var_r21;
    u16 var_r18;
    u16 i;
    s16 var_r20;
    Mtx sp54;

    sp8 = 0;
    var_r20 = -1;
    temp_r19 = arg0->object;
    temp_r25 = arg0->model;
    sp40 = temp_r19->flags | arg1->flags;
    if (arg1->vtxMode == 2 || arg1->vtxMode == 3) {
        var_r21 = 1;
    } else {
        var_r21 = 0;
        if (arg1->vtxMode == 0 || arg1->vtxMode == 5) {
            var_r18 = 0;
        } else {
            var_r18 = 1;
        }
    }
    if ((Hu3DObjInfoP->flags & 0x4000) && arg1->vtxMode == 5) {
        sp3C = GX_COLOR0A0;
        var_r17 = GX_CA_RASA;
        sp38 = 1;
    } else {
        sp3C = GX_COLOR0;
        var_r17 = GX_CA_KONST;
        sp38 = 0;
    }
    if (arg1->numAttrs == 1) {
        var_r30 = var_r31 = 1;
        temp_r29 = &temp_r19->data.attribute[arg1->attrs[0]];
        if (temp_r29->unk28 != 1.0f || temp_r29->unk2C != 1.0f) {
            PSMTXScale(sp54, 1.0f / temp_r29->unk28, 1.0f / temp_r29->unk2C, 1.0f);
            mtxTransCat(sp54, -temp_r29->unk30, -temp_r29->unk34, 0.0f);
            GXLoadTexMtxImm(sp54, texMtxTbl[var_r30], GX_MTX2x4);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[var_r30]);
        } else if (temp_r29->unk30 != 0.0f || temp_r29->unk34 != 0.0f) {
            PSMTXTrans(sp54, -temp_r29->unk30, -temp_r29->unk34, 0.0f);
            GXLoadTexMtxImm(sp54, texMtxTbl[var_r30], GX_MTX2x4);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[var_r30]);
        } else {
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        }
        if (temp_r29->unk20 == 1.0f) {
            if (temp_r29->unk04) {
                temp_r28 = temp_r29->unk04;
                if (temp_r28->unk00 & 2) {
                    GXLoadTexMtxImm(Hu3DTexScrData[temp_r28->unk04].unk3C, GX_TEXMTX0, GX_MTX2x4);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                } else if (temp_r28->unk00 & 4) {
                    PSMTXScale(sp54, 1.0f / temp_r28->unk20, 1.0f / temp_r28->unk24, 1.0f / temp_r28->unk28);
                    mtxRotCat(sp54, temp_r28->unk14, temp_r28->unk18, temp_r28->unk1C);
                    mtxTransCat(sp54, -temp_r28->unk08, -temp_r28->unk0C, -temp_r28->unk10);
                    GXLoadTexMtxImm(sp54, GX_TEXMTX0, GX_MTX2x4);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                } else if (temp_r28->unk00 & 1) {
                    PSMTXScale(sp54, temp_r28->unk2C, temp_r28->unk30, 1.0f);
                    mtxTransCat(sp54, temp_r28->unk34, temp_r28->unk38, 0.0f);
                    GXLoadTexMtxImm(sp54, GX_TEXMTX0, GX_MTX2x4);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
            }
            if (temp_r29->unk8[2] == 0) {
                GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
                GXSetTevOrder(var_r31, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
                GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                var_r31++;
            } else {
                GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
                if (!(temp_r25->attr & HU3D_ATTR_TOON_MAP)) {
                    if (texCol[0].a == 1) {
                        sp50 = texCol[0];
                        sp50.a = 0xFF;
                        SetKColorRGB(GX_TEVSTAGE0, &sp50);
                        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
                        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevOrder(var_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, sp3C);
                        GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, var_r17, GX_CA_ZERO);
                        GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        var_r31++;
                    } else if (texCol[0].a == 2) {
                        GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
                        GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
                        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
                        SetKColorRGB(GX_TEVSTAGE0, &firstTev);
                        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
                        GXSetTevSwapMode(var_r31, GX_TEV_SWAP0, GX_TEV_SWAP2);
                        SetKColorRGB(var_r31, &secondTev);
                        GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_CPREV);
                        GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
                        GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevOrder(var_r31, GX_TEXCOORD0, texCol->r, GX_COLOR_NULL);
                        var_r31++;
                    } else {
                        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, var_r17, GX_CA_ZERO);
                        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    }
                } else {
                    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
                    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
                    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                }
            }
        } else {
            GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        }
        if (temp_r25->attr & HU3D_ATTR_TOON_MAP) {
            GXSetTexCoordGen2(var_r30, GX_TG_SRTG, GX_TG_COLOR0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(var_r31, var_r30, toonMapNo, GX_COLOR0A0);
            GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_KONST, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            var_r30++;
            var_r31++;
        }
        sp50.a = 255.0f * (1.0f - arg1->invAlpha);
        GXSetTevColor(GX_TEVREG0, sp50);
        if (arg1->refAlpha != 0.0f) {
            SetReflect(arg0, var_r31, (u16) var_r30, 255.0f * arg1->refAlpha);
            var_r30++;
            var_r31++;
        }
        if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->flags & 8)) {
            SetShadow(arg0, var_r31, (u16) var_r30);
            var_r30++;
            var_r31++;
        }
        if (var_r21 != 0) {
            if ((temp_r25->attr & HU3D_ATTR_HILITE) || (sp40 & 0x100)) {
                GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX7, GX_FALSE, GX_PTIDENTITY);
                GXSetTevOrder(var_r31, var_r30, hiliteMapNo, GX_COLOR0A0);
                GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_CPREV);
                GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                var_f31 = 6.0f * (arg1->hilite_scale / 300.0f);
                if (var_f31 < 0.1) {
                    var_f31 = 0.1f;
                }
                PSMTXCopy(hiliteMtx, sp54);
                mtxScaleCat(sp54, var_f31, var_f31, var_f31);
                GXLoadTexMtxImm(sp54, GX_TEXMTX7, GX_MTX2x4);
                var_r31++;
                var_r30++;
                var_r21 = 0;
                var_r18 = 1;
            } else {
                if (temp_r29->unk20 == 1.0f) {
                    GXSetTevOrder(var_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR1A1);
                    GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
                } else {
                    GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(var_r31, var_r30, GX_TEXMAP0, GX_COLOR1A1);
                    GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_CPREV);
                    var_r30++;
                }
                GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                var_r31++;
            }
        } else if (arg1->invAlpha != 0.0f) {
            GXSetTevOrder(var_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            var_r31++;
        }
        if (temp_r25->unk_02 != 0) {
            for (i = 0, var_r22 = 1; i < 4; i++, var_r22 <<= 1) {
                if (var_r22 & temp_r25->unk_02) {
                    SetProjection(arg0, var_r31, i, (u16) var_r30, projectionMapNo + i, texMtxTbl[i + 3]);
                    var_r30++;
                    var_r31 += 2;
                }
            }
        }
    } else {
        sp44 = 0;
        var_r30 = 0;
        sp4C = -1;
        for (i = var_r31 = 0; i < arg1->numAttrs; i++) {
            temp_r29 = &temp_r19->data.attribute[arg1->attrs[i]];
            if (temp_r29->unk14 != 0.0f) {
                GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_BUMP0, GX_TG_TEXCOORD0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                SetKColor(var_r31, temp_r29->unk14 * 10.0f);
                GXSetTevOrder(var_r31, var_r30, i, GX_COLOR0A0);
                GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_RASC);
                GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                var_r31++;
                sp4C = i;
                sp48 = var_r31;
                GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_CPREV);
                GXSetTevColorOp(var_r31, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                var_r30++;
                sp44 = 1;
            } else if (temp_r29->unk20 != 1.0f) {
                var_r20 = i;
                continue;
            } else {
                if (temp_r29->unk04) {
                    temp_r28 = temp_r29->unk04;
                    if (temp_r28->unk00 & 2) {
                        GXLoadTexMtxImm(Hu3DTexScrData[temp_r28->unk04].unk3C, texMtxTbl[var_r30], GX_MTX2x4);
                        GXSetTexCoordGen(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[var_r30]);
                        temp_r23 = (u16) var_r30;
                        var_r30++;
                    } else if (temp_r28->unk00 & 4) {
                        PSMTXScale(sp54, 1.0f / temp_r28->unk20, 1.0f / temp_r28->unk24, 1.0f / temp_r28->unk28);
                        mtxRotCat(sp54, temp_r28->unk14, temp_r28->unk18, temp_r28->unk1C);
                        mtxTransCat(sp54, -temp_r28->unk08, -temp_r28->unk0C, -temp_r28->unk10);
                        GXLoadTexMtxImm(sp54, texMtxTbl[var_r30], GX_MTX2x4);
                        GXSetTexCoordGen(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[var_r30]);
                        temp_r23 = (u16) var_r30;
                        var_r30++;
                    } else if (temp_r28->unk00 & 1) {
                        PSMTXScale(sp54, temp_r28->unk2C, temp_r28->unk30, 1.0f);
                        mtxTransCat(sp54, temp_r28->unk34, temp_r28->unk38, 0.0f);
                        GXLoadTexMtxImm(sp54, texMtxTbl[var_r30], GX_MTX2x4);
                        GXSetTexCoordGen(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[var_r30]);
                        temp_r23 = (u16) var_r30;
                        var_r30++;
                    } else {
                        GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                        temp_r23 = (u16) var_r30;
                        var_r30++;
                    }
                } else {
                    if (temp_r29->unk28 != 1.0f || temp_r29->unk2C != 1.0f) {
                        PSMTXScale(sp54, 1.0f / temp_r29->unk28, 1.0f / temp_r29->unk2C, 1.0f);
                        mtxTransCat(sp54, -temp_r29->unk30, -temp_r29->unk34, 0.0f);
                        GXLoadTexMtxImm(sp54, texMtxTbl[var_r30], GX_MTX2x4);
                        GXSetTexCoordGen(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[var_r30]);
                    } else if (temp_r29->unk30 != 0.0f || temp_r29->unk34 != 0.0f) {
                        PSMTXTrans(sp54, -temp_r29->unk30, -temp_r29->unk34, 0.0f);
                        GXLoadTexMtxImm(sp54, texMtxTbl[var_r30], GX_MTX2x4);
                        GXSetTexCoordGen(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[var_r30]);
                    } else {
                        GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                    }
                    temp_r23 = (u16) var_r30;
                    var_r30++;
                }
                GXSetTevOrder(var_r31, temp_r23, i, GX_COLOR0A0);
                if (i == 0) {
                    if (texCol[i].a == 1) {
                        sp50 = texCol[i];
                        sp50.a = 0xFF;
                        sp8 = SetKColorRGB(GX_TEVSTAGE0, &sp50);
                        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        var_r31++;
                        GXSetTevKColorSel(var_r31, sp8);
                        GXSetTevOrder(var_r31, temp_r23, i, sp3C);
                        GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_CPREV, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
                    } else if (texCol[i].a == 2) {
                        GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
                        GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
                        GXSetTevSwapMode(var_r31, GX_TEV_SWAP0, GX_TEV_SWAP1);
                        SetKColorRGB(var_r31, &firstTev);
                        GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
                        GXSetTevOrder(var_r31, GX_TEXCOORD0, i, GX_COLOR_NULL);
                        var_r31++;
                        GXSetTevSwapMode(var_r31, GX_TEV_SWAP0, GX_TEV_SWAP2);
                        SetKColorRGB(var_r31, &secondTev);
                        GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_C2);
                        GXSetTevAlphaIn(var_r31, GX_CA_APREV, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
                        GXSetTevOrder(var_r31, GX_TEXCOORD0, texCol->r, GX_COLOR_NULL);
                    } else {
                        GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_TEXA, var_r17, GX_CA_ZERO);
                    }
                } else if (sp44 != 0) {
                    GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
                    GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                    sp44 = 0;
                } else if (temp_r29->unk8[2] == 0) {
                    if (temp_r29->unk0C != 1.0f) {
                        sp50.a = temp_r29->unk0C * 255.0f;
                        SetKColorRGB(var_r31, &sp50);
                        GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
                        GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        var_r31++;
                        GXSetTevOrder(var_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
                        GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_C2, GX_CC_A2, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    } else {
                        GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                        GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        var_r31++;
                        GXSetTevOrder(var_r31, temp_r23, i, GX_COLOR0A0);
                        GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_C2, GX_CC_TEXA, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    }
                } else if (texCol[i].a == 1) {
                    sp50 = texCol[i];
                    sp50.a = 0xFF;
                    SetKColorRGB(var_r31, &sp50);
                    GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                    GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                    GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_KONST, GX_CA_APREV, GX_CA_ZERO);
                    GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                    var_r31++;
                    GXSetTevOrder(var_r31, temp_r23, i, GX_COLOR0A0);
                    SetKColor(var_r31, temp_r29->unk0C * 255.0f);
                    GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_C2, GX_CC_KONST, GX_CC_ZERO);
                    GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                } else if (texCol[i].a == 2) {
                    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
                    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
                    GXSetTevSwapMode(var_r31, GX_TEV_SWAP0, GX_TEV_SWAP1);
                    SetKColorRGB(var_r31, &firstTev);
                    GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                    GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
                    GXSetTevOrder(var_r31, GX_TEXCOORD0, i, GX_COLOR_NULL);
                    var_r31++;
                    GXSetTevSwapMode(var_r31, GX_TEV_SWAP0, GX_TEV_SWAP2);
                    SetKColorRGB(var_r31, &secondTev);
                    GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_C2);
                    GXSetTevAlphaIn(var_r31, GX_CA_APREV, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
                    GXSetTevOrder(var_r31, GX_TEXCOORD0, texCol->r, GX_COLOR_NULL);
                } else {
                    SetKColor(var_r31, temp_r29->unk0C * 255.0f);
                    GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                    GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                }
                GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }
            var_r31++;
        }
        if (temp_r25->attr & HU3D_ATTR_TOON_MAP) {
            GXSetTexCoordGen2(var_r30, GX_TG_SRTG, GX_TG_COLOR0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(var_r31, var_r30, toonMapNo, GX_COLOR0A0);
            GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_KONST, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            var_r30++;
            var_r31++;
        }
        if (arg1->refAlpha != 0.0f) {
            if (var_r20 != -1) {
                SetKColor(var_r31, arg1->refAlpha * 255.0f);
                GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                GXSetTevOrder(var_r31, var_r30, var_r20, GX_COLOR0A0);
                GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
                var_r31++;
                var_r30++;
                GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX8, GX_FALSE, GX_PTIDENTITY);
                GXSetTevOrder(var_r31, var_r30, reflectionMapNo, GX_COLOR0A0);
                GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C2, GX_CC_ZERO);
                GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            } else {
                SetKColor(var_r31, arg1->refAlpha * 255.0f);
                GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX8, GX_FALSE, GX_PTIDENTITY);
                GXSetTevOrder(var_r31, var_r30, reflectionMapNo, GX_COLOR0A0);
                GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            }
            PSMTXScale(sp54, 1.0f / arg0->scale.x, 1.0f / arg0->scale.y, 1.0f / arg0->scale.z);
            PSMTXConcat(arg0->matrix, sp54, sp54);
            sp54[0][3] = sp54[1][3] = sp54[2][3] = 0.0f;
            PSMTXConcat(sp54, Hu3DCameraMtxXPose, sp54);
            PSMTXConcat(refMtx, sp54, sp54);
            GXLoadTexMtxImm(sp54, 0x36, GX_MTX2x4);
            var_r31++;
            var_r30++;
        }
        if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->flags & 8)) {
            SetShadow(arg0, var_r31, (u16) var_r30);
            var_r30++;
            var_r31++;
        }
        sp50.a = (1.0f - arg1->invAlpha) * 255.0f;
        GXSetTevColor(GX_TEVREG0, sp50);
        if (var_r21 != 0) {
            if ((temp_r25->attr & HU3D_ATTR_HILITE) || (sp40 & 0x100)) {
                var_f31 = (arg1->hilite_scale / 300.0f) * 6.0f;
                if (var_f31 < 0.1) {
                    var_f31 = 0.1f;
                }
                PSMTXCopy(hiliteMtx, sp54);
                mtxScaleCat(sp54, var_f31, var_f31, var_f31);
                GXLoadTexMtxImm(sp54, 0x33, GX_MTX2x4);
                if (var_r20 == -1) {
                    GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX7, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(var_r31, var_r30, hiliteMapNo, GX_COLOR0A0);
                    GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_CPREV);
                    GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
                    GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                } else {
                    GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(var_r31, var_r30, var_r20, GX_COLOR0A0);
                    GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
                    GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
                    GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                    GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG0);
                    var_r31++;
                    var_r30++;
                    GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX7, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(var_r31, var_r30, hiliteMapNo, GX_COLOR0A0);
                    GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_CPREV);
                    GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                }
                var_r31++;
                var_r30++;
                var_r21 = 0;
                var_r18 = 1;
            } else {
                if (var_r20 == -1) {
                    GXSetTevOrder(var_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR1A1);
                    GXSetTevColorIn(var_r31, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
                } else {
                    GXSetTexCoordGen2(var_r30, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(var_r31, var_r30, var_r20, GX_COLOR1A1);
                    GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_CPREV);
                    var_r30++;
                }
                GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
                GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                var_r31++;
            }
        } else if (arg1->invAlpha != 0.0f) {
            GXSetTevOrder(var_r31, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorIn(var_r31, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(var_r31, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(var_r31, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            var_r31++;
        }
        if (temp_r25->unk_02 != 0) {
            for (i = 0, var_r22 = 1; i < 4; i++, var_r22 <<= 1) {
                if (var_r22 & temp_r25->unk_02) {
                    SetProjection(arg0, var_r31, i, (u16) var_r30, projectionMapNo + i, texMtxTbl[i + 3]);
                    var_r30++;
                    var_r31 += 2;
                }
            }
        }
        if (sp4C != -1) {
            GXSetTexCoordGen2(var_r30, GX_TG_BUMP0, GX_TG_TEXCOORD0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(sp48, var_r30, sp4C, GX_COLOR0A0);
            var_r30++;
        }
    }
    FlushKColor();
    GXSetNumTexGens(var_r30);
    GXSetNumTevStages(var_r31);
    if (arg1->vtxMode != shadingBak) {
        shadingBak = arg1->vtxMode;
        if (var_r21 != 0) {
            var_f30 = arg1->hilite_scale;
        } else {
            var_f30 = 0.0f;
        }
        lightBit = Hu3DLightSet(arg0->model, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, var_f30);
    }
    if (var_r21 != 0) {
        GXSetNumChans(2);
        if (arg1->vtxMode == 5) {
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR1, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_NONE, GX_AF_SPEC);
            if (sp38 != 0) {
                GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
                GXSetChanCtrl(GX_ALPHA1, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPEC);
            } else {
                GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
                GXSetChanCtrl(GX_ALPHA1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            }
        } else {
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR1, GX_TRUE, GX_SRC_REG, GX_SRC_REG, lightBit, GX_DF_NONE, GX_AF_SPEC);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_ALPHA1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
        }
    } else {
        GXSetNumChans(1);
        if (arg1->vtxMode == 5) {
            GXSetChanCtrl(GX_COLOR0, var_r18, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            if (sp38 != 0) {
                GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            } else {
                GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            }
        } else {
            GXSetChanCtrl(GX_COLOR0, var_r18, GX_SRC_REG, GX_SRC_REG, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
        }
        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    }
}

static s32 kColorSelTbl[] = {
    GX_TEV_KCSEL_K0_R,
	GX_TEV_KCSEL_K0_G,
	GX_TEV_KCSEL_K0_B,
    GX_TEV_KCSEL_K1_R,
	GX_TEV_KCSEL_K1_G,
	GX_TEV_KCSEL_K1_B,
    GX_TEV_KCSEL_K2_R,
	GX_TEV_KCSEL_K2_G,
	GX_TEV_KCSEL_K2_B,
    GX_TEV_KCSEL_K3_R,
	GX_TEV_KCSEL_K3_G,
	GX_TEV_KCSEL_K3_B
};

static s32 kColorTbl[] = {
    GX_KCOLOR0,
    GX_KCOLOR1,
    GX_KCOLOR2,
    GX_KCOLOR3
};

static s32 kColorSelTbl2[] = {
	GX_TEV_KCSEL_K0,
	GX_TEV_KCSEL_K1,
	GX_TEV_KCSEL_K2,
	GX_TEV_KCSEL_K3
};

static s32 kColorSelATbl[] = {
	GX_TEV_KASEL_K0_A,
	GX_TEV_KASEL_K1_A,
	GX_TEV_KASEL_K2_A,
	GX_TEV_KASEL_K3_A
};

static GXTevKColorSel SetKColor(GXTevStageID arg0, u8 arg1) {
    GXTevKColorSel temp_r30;

    switch (kColorIdx % 3) {
        case 0:
            kColor.r = arg1;
            break;
        case 1:
            kColor.g = arg1;
            break;
        case 2:
            kColor.b = arg1;
            kColor.a = 0xFF;
            GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
            break;
    }
    temp_r30 = kColorSelTbl[kColorIdx];
    GXSetTevKColorSel(arg0, temp_r30);
    GXSetTevKAlphaSel(arg0, kColorSelATbl[kColorIdx / 3]);
    kColorIdx++;
    if (kColorIdx > 0xC) {
        kColorIdx = 0xB;
    }
    return temp_r30;
}

static GXTevKColorSel SetKColorRGB(GXTevStageID arg0, GXColor *arg1) {
    GXTevKColorSel temp_r30;

    GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
    kColorIdx = ((kColorIdx / 3) + 1) * 3;
    GXSetTevKColor(kColorTbl[kColorIdx / 3], *arg1);
    temp_r30 = kColorSelTbl2[kColorIdx / 3];
    GXSetTevKColorSel(arg0, temp_r30);
    GXSetTevKAlphaSel(arg0, kColorSelATbl[kColorIdx / 3]);
    kColorIdx += 3;
    if (kColorIdx > 0xC) {
        kColorIdx = 0xB;
    }
    return temp_r30;
}

static void FlushKColor(void) {
    kColor.a = 0xFF;
    if (kColorIdx % 3 != 0) {
        GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
    }
}

static void SetReflect(HsfDrawObject *arg0, s16 arg1, s16 arg2, u8 arg3) {
    GXTevKColorSel var_r27;
    Mtx sp3C;
    Mtx spC;

    switch (kColorIdx % 3) {
        case 0:
            kColor.r = arg3;
            break;
        case 1:
            kColor.g = arg3;
            break;
        case 2:
            kColor.b = arg3;
            kColor.a = 0xFF;
            GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
            break;
    }
    var_r27 = kColorSelTbl[kColorIdx];
    GXSetTevKColorSel(arg1, var_r27);
    GXSetTevKAlphaSel(arg1, kColorSelATbl[kColorIdx / 3]);
    kColorIdx++;
    if (kColorIdx > 0xC) {
        kColorIdx = 0xB;
    }
    GXSetTexCoordGen2(arg2, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX8, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(arg1, arg2, reflectionMapNo, GX_COLOR0A0);
    GXSetTevColorIn(arg1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
    GXSetTevColorOp(arg1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(arg1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(arg1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    PSMTXScale(sp3C, 1.0f / arg0->scale.x, 1.0f / arg0->scale.y, 1.0f / arg0->scale.z);
    PSMTXConcat(arg0->matrix, sp3C, spC);
    spC[0][3] = spC[1][3] = spC[2][3] = 0.0f;
    PSMTXConcat(spC, Hu3DCameraMtxXPose, sp3C);
    PSMTXConcat(refMtx, sp3C, spC);
    GXLoadTexMtxImm(spC, GX_TEXMTX8, GX_MTX2x4);
}

static void SetProjection(HsfDrawObject *arg0, s16 arg1, s16 arg2, s16 arg3, GXTexMapID arg4, u32 arg5) {
    GXTevKColorSel var_r26;
    u8 temp_r30;

    GXSetTexCoordGen2(arg3, GX_TG_MTX3x4, GX_TG_POS, arg5, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(arg1, arg3, arg4, GX_COLOR0A0);
    temp_r30 = Hu3DProjection[arg2].unk_00;
    switch (kColorIdx % 3) {
        case 0:
            kColor.r = temp_r30;
            break;
        case 1:
            kColor.g = temp_r30;
            break;
        case 2:
            kColor.b = temp_r30;
            kColor.a = 0xFF;
            GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
            break;
    }
    var_r26 = kColorSelTbl[kColorIdx];
    GXSetTevKColorSel(arg1, var_r26);
    GXSetTevKAlphaSel(arg1, kColorSelATbl[kColorIdx / 3]);
    kColorIdx++;
    if (kColorIdx > 0xC) {
        kColorIdx = 0xB;
    }
    GXSetTevColorIn(arg1, GX_CC_ZERO, GX_CC_TEXA, GX_CC_KONST, GX_CC_ZERO);
    GXSetTevColorOp(arg1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
    GXSetTevAlphaIn(arg1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(arg1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
    arg1++;
    GXSetTevOrder(arg1, arg3, arg4, GX_COLOR0A0);
    GXSetTevColorIn(arg1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C2, GX_CC_ZERO);
    GXSetTevColorOp(arg1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(arg1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(arg1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
}

static void SetShadowTex(void) {
    GXTexObj sp8;

    GXInitTexObj(&sp8, Hu3DShadowData.unk_04, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sp8, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sp8, shadowMapNo);
}

static void SetShadow(HsfDrawObject *arg0, s16 arg1, s16 arg2) {
    GXSetTexCoordGen2(arg2, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX9, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(arg1, arg2, shadowMapNo, GX_COLOR0A0);
    GXSetTevColorIn(arg1, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(arg1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(arg1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(arg1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
}

static void FaceDrawShadow(HsfDrawObject *arg0, HsfFace *arg1) {
    HsfObject *temp_r31;
    ModelData *temp_r28;
    HsfConstData *temp_r27;
    HsfMaterial *temp_r29;
    void *var_r26;
    GXColor spC;
    s16 var_r30;

    temp_r31 = arg0->object;
    temp_r28 = arg0->model;
    temp_r27 = temp_r31->constData;
    temp_r29 = &temp_r31->data.material[arg1->mat & 0xFFF];
    if (temp_r29 != materialBak) {
        if (!(temp_r27->flags & 0x400)) {
            drawCnt++;
            return;
        }
        materialBak = temp_r29;
        spC.a = 255.0f * (1.0f - temp_r29->invAlpha);
        GXSetTevColor(GX_TEVREG0, spC);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        if (temp_r29->numAttrs == 0) {
            var_r30 = (temp_r31->data.color) ? 4 : 0;
            if (var_r30 != vtxModeBak) {
                vtxModeBak = var_r30;
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, temp_r31->data.vertex->data, 3 * sizeof(float));
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                if (temp_r28->hsfData->cenvCnt == 0) {
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 0);
                    GXSetArray(GX_VA_NRM, temp_r31->data.normal->data, 3);
                } else {
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                    GXSetArray(GX_VA_NRM, temp_r31->data.normal->data, 3 * sizeof(float));
                }
                if (var_r30 & 4) {
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                    GXSetArray(GX_VA_CLR0, temp_r31->data.color->data, 4);
                }
                GXSetZCompLoc(1);
            }
            GXSetNumTexGens(0);
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_A1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        } else {
            var_r30 = (temp_r29->vtxMode == 5) ? 5 : 1;
            if (DrawData[drawCnt].flags & 2) {
                var_r30 |= 2;
            }
            if (var_r30 != vtxModeBak) {
                vtxModeBak = var_r30;
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, temp_r31->data.vertex->data, 3 * sizeof(float));
                if (var_r30 & 2) {
                    GXSetVtxDesc(GX_VA_NBT, GX_DIRECT);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NBT, GX_NRM_NBT, GX_S16, 8);
                } else {
                    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                    if (temp_r28->hsfData->cenvCnt == 0) {
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_RGB8, 0);
                        GXSetArray(GX_VA_NRM, temp_r31->data.normal->data, 3);
                    } else {
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                        GXSetArray(GX_VA_NRM, temp_r31->data.normal->data, 3 * sizeof(float));
                    }
                }
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
                GXSetArray(GX_VA_TEX0, temp_r31->data.st->data, 2 * sizeof(float));
                if (var_r30 & 4) {
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                    GXSetArray(GX_VA_CLR0, temp_r31->data.color->data, 4);
                }
                GXSetZCompLoc(0);
            }
            GXSetNumTexGens(0);
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_A1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        var_r26 = (u8*) DLBufStartP + DrawData[drawCnt].dlOfs;
        GXCallDisplayList(var_r26, DrawData[drawCnt].dlSize);
    } else {
        if (!(temp_r27->flags & 0x400)) {
            drawCnt++;
            return;
        }
        var_r26 = (u8*) DLBufStartP + DrawData[drawCnt].dlOfs;
        GXCallDisplayList(var_r26, DrawData[drawCnt].dlSize);
    }
    drawCnt++;
}

static void LoadTexture(ModelData *arg0, HsfBitmap *arg1, HsfAttribute *arg2, s16 arg3) {
    GXTexObj sp1C;
    GXTlutObj sp10;
    s16 var_r27;
    s16 var_r26;
    s16 var_r22;
    s16 var_r21;
    s32 var_r20;
    s16 var_r30;

    if (arg1 == 0) {
        OSReport("Error: No Texture\n");
        return;
    }
    var_r27 = arg1->sizeX;
    var_r26 = arg1->sizeY;
    var_r22 = (arg2->wrap_s == 1) ? GX_REPEAT : GX_CLAMP;
    var_r21 = (arg2->wrap_t == 1) ? GX_REPEAT : GX_CLAMP;
    var_r20 = (arg2->flag & 0x80) ? GX_TRUE : GX_FALSE;
    switch (arg1->dataFmt) {
        case 6:
            GXInitTexObj(&sp1C, arg1->data, var_r27, var_r26, GX_TF_RGBA8, var_r22, var_r21, var_r20);
            break;
        case 4:
            GXInitTexObj(&sp1C, arg1->data, var_r27, var_r26, GX_TF_RGB565, var_r22, var_r21, var_r20);
            break;
        case 5:
            GXInitTexObj(&sp1C, arg1->data, var_r27, var_r26, GX_TF_RGB5A3, var_r22, var_r21, var_r20);
            break;
        case 9:
            if (arg1->pixSize < 8) {
                GXInitTlutObj(&sp10, arg1->palData, GX_TL_RGB565, arg1->palSize);
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, var_r27, var_r26, GX_TF_C4, var_r22, var_r21, var_r20, arg3);
            } else {
                GXInitTlutObj(&sp10, arg1->palData, GX_TL_RGB565, arg1->palSize);
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, var_r27, var_r26, GX_TF_C8, var_r22, var_r21, var_r20, arg3);
            }
            break;
        case 10:
            if (arg1->pixSize < 8) {
                GXInitTlutObj(&sp10, arg1->palData, GX_TL_RGB5A3, arg1->palSize);
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, var_r27, var_r26, GX_TF_C4, var_r22, var_r21, var_r20, arg3);
            } else {
                GXInitTlutObj(&sp10, arg1->palData, GX_TL_RGB5A3, arg1->palSize);
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, var_r27, var_r26, GX_TF_C8, var_r22, var_r21, var_r20, arg3);
            }
            break;
        case 0:
            var_r30 = (s16) arg3;
            texCol[var_r30].r = arg1->tint.r;
            texCol[var_r30].g = arg1->tint.g;
            texCol[var_r30].b = arg1->tint.b;
            texCol[var_r30].a = 1;
            GXInitTexObj(&sp1C, arg1->data, var_r27, var_r26, GX_TF_I4, var_r22, var_r21, var_r20);
            break;
        case 1:
            var_r30 = (s16) arg3;
            texCol[var_r30].r = arg1->tint.r;
            texCol[var_r30].g = arg1->tint.g;
            texCol[var_r30].b = arg1->tint.b;
            texCol[var_r30].a = 1;
            GXInitTexObj(&sp1C, arg1->data, var_r27, var_r26, GX_TF_I8, var_r22, var_r21, var_r20);
            break;
        case 2:
            var_r30 = (s16) arg3;
            texCol[var_r30].r = arg1->tint.r;
            texCol[var_r30].g = arg1->tint.g;
            texCol[var_r30].b = arg1->tint.b;
            texCol[var_r30].a = 1;
            GXInitTexObj(&sp1C, arg1->data, var_r27, var_r26, GX_TF_IA4, var_r22, var_r21, var_r20);
            break;
        case 3:
            var_r30 = (s16) arg3;
            texCol[var_r30].r = arg1->tint.r;
            texCol[var_r30].g = arg1->tint.g;
            texCol[var_r30].b = arg1->tint.b;
            texCol[var_r30].a = 1;
            GXInitTexObj(&sp1C, arg1->data, var_r27, var_r26, GX_TF_IA8, var_r22, var_r21, var_r20);
            break;
        case 7:
            GXInitTexObj(&sp1C, arg1->data, var_r27, var_r26, GX_TF_CMPR, var_r22, var_r21, var_r20);
            break;
        case 11:
            if (arg3 & 0x8000) {
                GXInitTlutObj(&sp10, &((s16*) arg1->palData)[(arg1->palSize + 0xF) & 0xFFF0], GX_TL_IA8, arg1->palSize);
            } else {
                GXInitTlutObj(&sp10, arg1->palData, GX_TL_IA8, arg1->palSize);
            }
            arg3 &= 0x7FFF;
            if (arg1->pixSize < 8) {
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, var_r27, var_r26, GX_TF_C4, var_r22, var_r21, var_r20, arg3);
            } else {
                GXLoadTlut(&sp10, arg3);
                GXInitTexObjCI(&sp1C, arg1->data, var_r27, var_r26, GX_TF_C8, var_r22, var_r21, var_r20, arg3);
            }
            TL32F = 1;
            break;
    }
    if ((arg0->attr & HU3D_ATTR_TEX_NEAR) || (arg2->flag & 0x40)) {
        GXInitTexObjLOD(&sp1C, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    } else if (var_r20) {
        GXInitTexObjLOD(&sp1C, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, arg2->unk78, 0.0f, GX_FALSE, GX_TRUE, GX_ANISO_2);
    } else if (arg1->maxLod == 0) {
        GXInitTexObjLOD(&sp1C, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    } else {
        GXInitTexObjLOD(&sp1C, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, arg1->maxLod - 1, 0.0f, GX_TRUE, GX_TRUE, GX_ANISO_1);
    }
    GXLoadTexObj(&sp1C, arg3);
}

static void objNull(ModelData *arg0, HsfObject *arg1) {
    HsfTransform *var_r31;
    Vec *temp_r27;
    Vec *temp_r28;
    s16 var_r24;
    s16 i;
    Mtx sp8;

    if (CancelTRXF == 0) {
        if (attachMotionF == 0) {
            var_r31 = &arg1->data.base;
        } else {
            var_r31 = &arg1->data.curr;
        }
        if (arg0->hsfData->cenvCnt == 0 || hookIdx != -1) {
            PSMTXScale(sp8, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
            mtxRotCat(sp8, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
            mtxTransCat(sp8, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
            PSMTXConcat(MTXBuf[MTXIdx - 1], sp8, MTXBuf[MTXIdx]);
        }
        temp_r28 = &scaleBuf[MTXIdx];
        temp_r27 = temp_r28 - 1;
        temp_r28->x = temp_r27->x * var_r31->scale.x;
        temp_r28->y = temp_r27->y * var_r31->scale.y;
        temp_r28->z = temp_r27->z * var_r31->scale.z;
        MTXIdx++;
        var_r24 = 1;
    } else {
        CancelTRXF = 0;
        var_r24 = 0;
    }
    for (i = 0; i < arg1->data.childrenCount; i++) {
        objCall(arg0, arg1->data.children[i]);
    }
    if (var_r24 != 0) {
        MTXIdx--;
    }
}

static void objRoot(ModelData *arg0, HsfObject *arg1) {
    HsfTransform *var_r31;
    Vec *temp_r29;
    Vec *temp_r30;
    s16 var_r26;
    s16 i;
    Mtx sp8;

    if (CancelTRXF == 0) {
        if (attachMotionF == 0) {
            var_r31 = &arg1->data.base;
        } else {
            var_r31 = &arg1->data.curr;
        }
        if (arg0->hsfData->cenvCnt == 0 || hookIdx != -1) {
            PSMTXScale(sp8, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
            mtxRotCat(sp8, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
            mtxTransCat(sp8, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
            PSMTXConcat(MTXBuf[MTXIdx - 1], sp8, MTXBuf[MTXIdx]);
        }
        temp_r30 = &scaleBuf[MTXIdx];
        temp_r29 = temp_r30 - 1;
        temp_r30->x = temp_r29->x * var_r31->scale.x;
        temp_r30->y = temp_r29->y * var_r31->scale.y;
        temp_r30->z = temp_r29->z * var_r31->scale.z;
        MTXIdx++;
        var_r26 = 1;
    } else {
        CancelTRXF = 0;
        var_r26 = 0;
    }
    for (i = 0; i < arg1->data.childrenCount; i++) {
        objCall(arg0, arg1->data.children[i]);
    }
    if (var_r26 != 0) {
        MTXIdx--;
    }
}

static void objJoint(ModelData *arg0, HsfObject *arg1) {
    HsfTransform *var_r31;
    Vec *temp_r27;
    Vec *temp_r28;
    s16 var_r24;
    s16 i;
    Mtx sp8;

    if (CancelTRXF == 0) {
        if (attachMotionF == 0) {
            var_r31 = &arg1->data.base;
        } else {
            var_r31 = &arg1->data.curr;
        }
        if (arg0->hsfData->cenvCnt == 0 || hookIdx != -1) {
            PSMTXScale(sp8, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
            mtxRotCat(sp8, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
            mtxTransCat(sp8, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
            PSMTXConcat(MTXBuf[MTXIdx - 1], sp8, MTXBuf[MTXIdx]);
        }
        temp_r28 = &scaleBuf[MTXIdx];
        temp_r27 = temp_r28 - 1;
        temp_r28->x = temp_r27->x * var_r31->scale.x;
        temp_r28->y = temp_r27->y * var_r31->scale.y;
        temp_r28->z = temp_r27->z * var_r31->scale.z;
        MTXIdx++;
        var_r24 = 1;
    } else {
        CancelTRXF = 0;
        var_r24 = 0;
    }
    for (i = 0; i < arg1->data.childrenCount; i++) {
        objCall(arg0, arg1->data.children[i]);
    }
    if (var_r24 != 0) {
        MTXIdx--;
    }
}

static void objMap(ModelData *arg0, HsfObject *arg1) {
    HsfTransform *var_r31;
    Vec *temp_r29;
    Vec *temp_r30;
    s16 var_r26;
    s16 i;
    Mtx spC;

    if (CancelTRXF == 0) {
        if (attachMotionF == 0) {
            var_r31 = &arg1->data.base;
        } else {
            var_r31 = &arg1->data.curr;
        }
        PSMTXScale(spC, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
        mtxRotCat(spC, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
        mtxTransCat(spC, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
        PSMTXConcat(MTXBuf[MTXIdx - 1], spC, MTXBuf[MTXIdx]);
        temp_r30 = &scaleBuf[MTXIdx];
        temp_r29 = temp_r30 - 1;
        temp_r30->x = temp_r29->x * var_r31->scale.x;
        temp_r30->y = temp_r29->y * var_r31->scale.y;
        temp_r30->z = temp_r29->z * var_r31->scale.z;
        MTXIdx++;
        var_r26 = 1;
    } else {
        CancelTRXF = 0;
        var_r26 = 0;
    }
    for (i = 0; i < arg1->data.childrenCount; i++) {
        objCall(arg0, arg1->data.children[i]);
    }
    if (var_r26 != 0) {
        MTXIdx--;
    }
}

static void objReplica(ModelData *arg0, HsfObject *arg1) {
    HsfTransform *var_r31;
    Mtx sp3C;
    Mtx spC;

    if (attachMotionF == 0) {
        var_r31 = &arg1->data.base;
    } else {
        var_r31 = &arg1->data.curr;
    }
    mtxRot(spC, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
    PSMTXScale(sp3C, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
    PSMTXConcat(spC, sp3C, sp3C);
    mtxTransCat(sp3C, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
    PSMTXConcat(MTXBuf[MTXIdx - 1], sp3C, MTXBuf[MTXIdx]);
    scaleBuf[MTXIdx].x = var_r31->scale.x * scaleBuf[MTXIdx - 1].x;
    scaleBuf[MTXIdx].y = var_r31->scale.y * scaleBuf[MTXIdx - 1].y;
    scaleBuf[MTXIdx].z = var_r31->scale.z * scaleBuf[MTXIdx - 1].z;
    MTXIdx++;
    CancelTRXF = 1;
    objCall(arg0, arg1->data.replica);
    CancelTRXF = 0;
    MTXIdx--;
}

void Hu3DDrawPost(void) {
    Vec sp54;
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    GXColor sp2C;
    void (*sp28)(ModelData*, Mtx);
    s16 spA;
    s16 sp8;
    HsfBuffer *temp_r24;
    HsfDrawObject *temp_r28;
    s16 var_r21;
    s16 var_r20;
    s16 var_r19;
    s16 var_r23;
    s16 var_r25;
    s16 var_r26;
    s16 i;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    LightData *temp_r22;
    HsfFace *var_r27;
    Mtx sp150;
    Mtx sp120;
    Mtx spF0;
    Mtx spC0;
    Mtx sp90;
    Mtx sp60;

    spA = 0;
    if (DrawObjIdx != 0) {
        for (i = 0; i < DrawObjIdx; i++) {
            DrawObjNum[i] = i;
        }
        if (shadowModelDrawF == 0) {
            var_r25 = 1;
            while (var_r25 <= DrawObjIdx) {
                var_r25 = var_r25 * 3 + 1;
            }
            while ((var_r25 /= 3) >= 1) {
                for (i = var_r25; i < DrawObjIdx; i++) {
                    var_r20 = DrawObjNum[i];
                    temp_f29 = DrawObjData[DrawObjNum[i]].z;
                    var_r26 = i - var_r25;
                    while (var_r26 >= 0) {
                        if (DrawObjData[DrawObjNum[var_r26]].z < temp_f29) {
                            DrawObjNum[var_r26 + var_r25] = DrawObjNum[var_r26];
                            var_r26 -= var_r25;
                        } else {
                            break;
                        }
                    }
                    DrawObjNum[var_r26 + var_r25] = var_r20;
                }
            }
            for (i = 0; i < DrawObjIdx - 1; i++) {
                for (var_r26 = i + 1; var_r26 < DrawObjIdx; var_r26++) {
                    if (DrawObjData[DrawObjNum[i]].z != DrawObjData[DrawObjNum[var_r26]].z) {
                        break;
                    }
                    if (DrawObjNum[var_r26] < DrawObjNum[i]) {
                        var_r20 = DrawObjNum[i];
                        DrawObjNum[i] = DrawObjNum[var_r26];
                        DrawObjNum[var_r26] = var_r20;
                    }
                }
            }
        }
        GXInvalidateTexAll();
        GXInvalidateVtxCache();
        materialBak = (HsfMaterial*) -1;
        for (i = 0; i < 8; i++) {
            BmpPtrBak[i] = (HsfAttribute*) -1;
        }
        GXSetCullMode(GX_CULL_BACK);
        for (var_r23 = 0; var_r23 < DrawObjIdx; var_r23++) {
            temp_r28 = &DrawObjData[DrawObjNum[var_r23]];
            if (temp_r28->model->attr & HU3D_ATTR_HOOKFUNC) {
                sp28 = (void*) temp_r28->model->hsfData;
                sp28(temp_r28->model, temp_r28->matrix);
                for (i = 0; i < 8; i++) {
                    BmpPtrBak[i] = (HsfAttribute*) -1;
                }
                materialBak = (HsfMaterial*) -1;
                Hu3DCameraSet(Hu3DCameraNo, Hu3DCameraMtx);
            } else {
                Hu3DObjInfoP = temp_r28->object->constData;
                DLBufStartP = Hu3DObjInfoP->dlBuf;
                DrawData = Hu3DObjInfoP->drawData;
                GXLoadPosMtxImm(temp_r28->matrix, GX_PNMTX0);
                PSMTXInvXpose(temp_r28->matrix, sp120);
                GXLoadNrmMtxImm(sp120, 0);
                if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->flags & 8)) {
                    PSMTXInverse(Hu3DCameraMtx, spF0);
                    PSMTXConcat(spF0, temp_r28->matrix, sp120);
                    PSMTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, sp150);
                    PSMTXConcat(sp150, sp120, sp120);
                    GXLoadTexMtxImm(sp120, GX_TEXMTX9, GX_MTX3x4);
                    var_r19 = 1;
                } else {
                    var_r19 = 0;
                }
                if (temp_r28->model->unk_02 != 0) {
                    if (var_r19 == 0) {
                        PSMTXInverse(Hu3DCameraMtx, spF0);
                    }
                    for (i = 0, var_r21 = 1; i < 4; i++, var_r21 <<= 1) {
                        if (var_r21 & temp_r28->model->unk_02) {
                            PSMTXConcat(spF0, temp_r28->matrix, sp120);
                            PSMTXConcat(Hu3DProjection[i].unk_68, Hu3DProjection[i].unk_38, sp150);
                            PSMTXConcat(sp150, sp120, sp120);
                            GXLoadTexMtxImm(sp120, texMtxTbl[i + 3], GX_MTX3x4);
                        }
                    }
                }
                if ((temp_r28->model->attr & HU3D_ATTR_HILITE) || (Hu3DObjInfoP->flags & 0x8000)) {
                    sp54 = lbl_8011DD20;
                    temp_r22 = &Hu3DGlobalLight[temp_r28->model->unk_03];
                    sp30 = temp_r22->unk_28;
                    if (temp_r22->unk_00 & 0x8000) {
                        PSMTXMultVecSR(Hu3DCameraMtx, &sp30, &sp30);
                    }
                    temp_f30 = VECDotProduct(&sp30, &sp54);
                    temp_f30 *= 10000.0f;
                    OSf32tos16(&temp_f30, &sp8);
                    if (sp8 == -10000) {
                        PSMTXScale(hiliteMtx, 0.0f, 0.0f, 0.0f);
                    } else {
                        C_VECHalfAngle(&sp30, &sp54, &sp3C);
                        sp3C.x = -sp3C.x;
                        sp3C.y = -sp3C.y;
                        sp3C.z = -sp3C.z;
                        PSMTXScale(sp60, 1.0f / temp_r28->scale.x, 1.0f / temp_r28->scale.y, 1.0f / temp_r28->scale.z);
                        PSMTXConcat(temp_r28->matrix, sp60, spC0);
                        spC0[0][3] = spC0[1][3] = spC0[2][3] = 0.0f;
                        PSMTXInvXpose(spC0, sp90);
                        if (sp8 == 10000) {
                            PSMTXIdentity(spC0);
                        } else {
                            VECCrossProduct(&sp3C, &sp54, &sp48);
                            temp_f28 = acosf(VECDotProduct(&sp54, &sp3C));
                            PSMTXRotAxisRad(spC0, &sp48, temp_f28);
                        }
                        PSMTXConcat(spC0, sp90, sp60);
                        PSMTXTrans(spC0, 0.5f, 0.5f, 0.0f);
                        PSMTXConcat(spC0, sp60, hiliteMtx);
                    }
                }
                temp_r24 = temp_r28->object->data.face;
                var_r27 = temp_r24->data;
                drawCnt = 0;
                shadingBak = -1;
                vtxModeBak = -1;
                materialBak = (HsfMaterial*) -1;
                if (shadowModelDrawF == 0) {
                    for (i = 0; i < temp_r24->count;) {
                        FaceDraw(temp_r28, var_r27);
                        if (var_r27->type == 4) {
                            totalPolyCnt += DrawData[drawCnt - 1].polyCnt;
                            i++;
                            var_r27++;
                        } else {
                            totalPolyCnt += DrawData[drawCnt - 1].polyCnt * ((var_r27->type & 7) == 3 ? 2 : 1);
                            i += DrawData[drawCnt - 1].polyCnt;
                            var_r27 += DrawData[drawCnt - 1].polyCnt;
                        }
                    }
                } else {
                    sp2C.a = 0xFF;
                    GXSetChanAmbColor(GX_COLOR0A0, sp2C);
                    GXSetChanMatColor(GX_COLOR0A0, sp2C);
                    sp2C.a = Hu3DShadowData.unk_00;
                    GXSetTevColor(GX_TEVREG1, sp2C);
                    GXSetNumChans(1);
                    for (i = 0; i < temp_r24->count;) {
                        FaceDrawShadow(temp_r28, var_r27);
                        if (var_r27->type == 4) {
                            i++;
                            var_r27++;
                        } else {
                            i += DrawData[drawCnt - 1].polyCnt;
                            var_r27 += DrawData[drawCnt - 1].polyCnt;
                        }
                    }
                }
                if (TL32F != 0) {
                    for (i = GX_TEVSTAGE0; i < GX_MAX_TEVSTAGE; i++) {
                        GXSetTevSwapMode(i, GX_TEV_SWAP0, GX_TEV_SWAP0);
                    }
                    TL32F = 0;
                }
            }
        }
    }
    (void)var_r19; // required to match
}

static void ObjDraw(HsfDrawObject *arg0) {
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    GXColor sp1C;
    HsfBuffer *temp_r26;
    s16 var_r22;
    s16 var_r21;
    s16 var_r23;
    s16 i;
    s32 var_r20;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    LightData *temp_r24;
    HsfDrawData *temp_r25;
    HsfFace *var_r27;
    Mtx sp140;
    Mtx sp110;
    Mtx spE0;
    Mtx spB0;
    Mtx sp80;
    Mtx sp50;

    Hu3DObjInfoP = arg0->object->constData;
    DLBufStartP = Hu3DObjInfoP->dlBuf;
    DrawData = Hu3DObjInfoP->drawData;
    GXLoadPosMtxImm(arg0->matrix, GX_PNMTX0);
    PSMTXInvXpose(arg0->matrix, sp110);
    GXLoadNrmMtxImm(sp110, 0);
    GXInvalidateVtxCache();
    if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->flags & 8)) {
        PSMTXInverse(Hu3DCameraMtx, spE0);
        PSMTXConcat(spE0, arg0->matrix, sp110);
        PSMTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, sp140);
        PSMTXConcat(sp140, sp110, sp110);
        GXLoadTexMtxImm(sp110, GX_TEXMTX9, GX_MTX3x4);
        var_r22 = 1;
    } else {
        var_r22 = 0;
    }
    if (arg0->model->unk_02 != 0) {
        if (var_r22 == 0) {
            PSMTXInverse(Hu3DCameraMtx, spE0);
        }
        for (i = 0, var_r23 = 1; i < 4; i++, var_r23 <<= 1) {
            if (var_r23 & arg0->model->unk_02) {
                PSMTXConcat(spE0, arg0->matrix, sp110);
                PSMTXConcat(Hu3DProjection[i].unk_68, Hu3DProjection[i].unk_38, sp140);
                PSMTXConcat(sp140, sp110, sp110);
                GXLoadTexMtxImm(sp110, texMtxTbl[i + 3], GX_MTX3x4);
            }
        }
    }
    if ((arg0->model->attr & HU3D_ATTR_HILITE) || (Hu3DObjInfoP->flags & 0x8000)) {
        sp44 = lbl_8011DD20;
        temp_r24 = &Hu3DGlobalLight[arg0->model->unk_03];
        sp20 = temp_r24->unk_28;
        if (temp_r24->unk_00 & 0x8000) {
            PSMTXMultVecSR(Hu3DCameraMtx, &sp20, &sp20);
        }
        temp_f30 = VECDotProduct(&sp20, &sp44);
        temp_f30 *= 10000.0f;
        OSf32tos16(&temp_f30, &var_r21);
        if (var_r21 == -10000) {
            PSMTXScale(hiliteMtx, 0.0f, 0.0f, 0.0f);
        } else {
            C_VECHalfAngle(&sp20, &sp44, &sp2C);
            sp2C.x = -sp2C.x;
            sp2C.y = -sp2C.y;
            sp2C.z = -sp2C.z;
            PSMTXScale(sp50, 1.0f / arg0->scale.x, 1.0f / arg0->scale.y, 1.0f / arg0->scale.z);
            PSMTXConcat(arg0->matrix, sp50, spB0);
            spB0[0][3] = spB0[1][3] = spB0[2][3] = 0.0f;
            PSMTXInvXpose(spB0, sp80);
            if (var_r21 == 10000) {
                PSMTXIdentity(spB0);
            } else {
                VECCrossProduct(&sp2C, &sp44, &sp38);
                temp_f29 = acosf(VECDotProduct(&sp44, &sp2C));
                PSMTXRotAxisRad(spB0, &sp38, temp_f29);
            }
            PSMTXConcat(spB0, sp80, sp50);
            PSMTXTrans(spB0, 0.5f, 0.5f, 0.0f);
            PSMTXConcat(spB0, sp50, hiliteMtx);
        }
    }
    temp_r26 = arg0->object->data.face;
    var_r27 = temp_r26->data;
    drawCnt = 0;
    shadingBak = -1;
    vtxModeBak = -1;
    materialBak = (HsfMaterial*) -1;
    if (shadowModelDrawF == 0) {
        for (i = 0; i < temp_r26->count;) {
            FaceDraw(arg0, var_r27);
            if (var_r27->type == 4) {
                totalPolyCnt += DrawData[drawCnt - 1].polyCnt;
                i++;
                var_r27++;
            } else {
                temp_r25 = &DrawData[drawCnt - 1];
                if ((var_r27->type & 7) == 3) {
                    var_r20 = 2;
                } else {
                    var_r20 = 1;
                }
                totalPolyCnt += temp_r25->polyCnt * var_r20;
                i += temp_r25->polyCnt;
                var_r27 += temp_r25->polyCnt;
            }
        }
    } else {
        sp1C.a = 0xFF;
        GXSetChanAmbColor(GX_COLOR0A0, sp1C);
        GXSetChanMatColor(GX_COLOR0A0, sp1C);
        sp1C.a = Hu3DShadowData.unk_00;
        GXSetTevColor(GX_TEVREG1, sp1C);
        GXSetNumChans(1);
        for (i = 0; i < temp_r26->count;) {
            FaceDrawShadow(arg0, var_r27);
            if (var_r27->type == 4) {
                i++;
                var_r27++;
            } else {
                i += DrawData[drawCnt - 1].polyCnt;
                var_r27 += DrawData[drawCnt - 1].polyCnt;
            }
        }
    }
    if (TL32F != 0) {
        for (i = GX_TEVSTAGE0; i < GX_MAX_TEVSTAGE; i++) {
            GXSetTevSwapMode(i, GX_TEV_SWAP0, GX_TEV_SWAP0);
        }
        TL32F = 0;
    }
}

void MakeDisplayList(s16 arg0, u32 arg1) {
    HsfData *temp_r31;
    ModelData *var_r30;

    temp_r31 = Hu3DData[arg0].hsfData;
    var_r30 = &Hu3DData[arg0];
    curModelID = arg0;
    mallocNo = arg1;
    faceNumBuf = HuMemDirectMallocNum(HEAP_DATA, 0x800 * sizeof(u16), mallocNo);
    MDObjCall(temp_r31, temp_r31->root);
    HuMemDirectFree(faceNumBuf);
    if (var_r30->attr & HU3D_ATTR_SHADOW) {
        Hu3DShadowCamBit++;
    }
}

static void MDObjCall(HsfData *arg0, HsfObject *arg1) {
    s16 i;

    switch (arg1->type) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 9:
            for (i = 0; i < arg1->data.childrenCount; i++) {
                MDObjCall(arg0, arg1->data.children[i]);
            }
            break;
        case 2:
            MDObjMesh(arg0, arg1);
            break;
    }
}

static void MDObjMesh(HsfData *arg0, HsfObject *arg1) {
    HsfBuffer *temp_r29;
    HsfFace *var_r28;
    s16 i;

    temp_r29 = arg1->data.face;
    DLFirstF = 0;
    drawCnt = matChgCnt = triCnt = quadCnt = 0;
    faceNumBuf[0] = 0;
    materialBak = (HsfMaterial*) -1;
    polyTypeBak = 0xFF;
    DLTotalNum = 0;
    var_r28 = temp_r29->data;
    for (i = 0; i < temp_r29->count; i++, var_r28++) {
        MDFaceCnt(arg1, var_r28);
    }
    DLTotalNum = (DLTotalNum + 0x40) & ~0x1F;
    Hu3DObjInfoP = ObjConstantMake(arg1, mallocNo);
    Hu3DObjInfoP->drawData = DrawData = HuMemDirectMallocNum(HEAP_DATA, matChgCnt * sizeof(HsfDrawData), mallocNo);
    memset(DrawData, 0, matChgCnt * sizeof(HsfDrawData));
    DLBufP = DLBufStartP = HuMemDirectMallocNum(HEAP_DATA, DLTotalNum, mallocNo);
    DCInvalidateRange(DLBufStartP, DLTotalNum);
    DLFirstF = 0;
    materialBak = (HsfMaterial*) -1;
    polyTypeBak = 0xFF;
    totalSize = drawCnt = 0;
    var_r28 = temp_r29->data;
    if (arg1->flags & 4) {
        Hu3DObjInfoP->flags |= 0x400;
        Hu3DModelAttrSet(curModelID, HU3D_ATTR_SHADOW);
    }
    if (arg1->flags & 8) {
        Hu3DObjInfoP->flags |= 8;
    }
    if (arg1->flags & 0x30) {
        Hu3DObjInfoP->flags |= 0x800;
    }
    if (arg1->flags & 0x100) {
        Hu3DObjInfoP->flags |= 0x8000;
    }
    for (i = 0; i < temp_r29->count; i++, var_r28++) {
        MDFaceDraw(arg1, var_r28);
    }
    Hu3DObjInfoP->dlBuf = DLBufStartP;
    if (DLTotalNum < totalSize) {
        OSReport("DLBuf Over >>>>>>>>>>>>>");
        OSReport("%x:%x:%x\n", Hu3DObjInfoP->dlBuf, totalSize, DLTotalNum);
    }
    for (i = 0; i < arg1->data.childrenCount; i++) {
        MDObjCall(arg0, arg1->data.children[i]);
    }
}

HsfConstData *ObjConstantMake(HsfObject *arg0, u32 arg1) {
    HsfConstData *temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfConstData), arg1);
    arg0->constData = temp_r3;
    temp_r3->flags = 0;
    temp_r3->hook = -1;
    temp_r3->hiliteMap = NULL;
    return temp_r3;
}

static void MDFaceDraw(HsfObject *arg0, HsfFace *arg1) {
    HsfMaterial *temp_r30;
    s16 *var_r24;
    s16 var_r26;
    s16 var_r27;
    s16 var_r22;
    s32 temp_r28;
    s32 temp_r3;
    s32 var_r25;

    var_r26 = -1;
    temp_r30 = &arg0->data.material[arg1->mat & 0xFFF];
    if (temp_r30 != materialBak || polyTypeBak != (arg1->type & 7) || (arg1->type & 7) == 4) {
        polyTypeBak = arg1->type & 7;
        materialBak = temp_r30;
        DrawData[drawCnt].dlOfs = (u32) DLBufP - (u32) DLBufStartP;
        GXBeginDisplayList(DLBufP, 0x20000);
        GXResetWriteGatherPipe();
        if (temp_r30->numAttrs == 0) {
            var_r25 = 0;
        } else {
            var_r25 = 1;
            for (var_r27 = 0; var_r27 < temp_r30->numAttrs; var_r27++) {
                if (arg0->data.attribute[temp_r30->attrs[var_r27]].unk14 != 0.0) {
                    Hu3DObjInfoP->flags |= 2;
                    DrawData[drawCnt].flags |= 2;
                    var_r26 = var_r27;
                }
            }
            if (var_r26 != -1 && var_r26 != 0) {
                var_r22 = temp_r30->attrs[var_r26];
                for (var_r27 = temp_r30->numAttrs - 2; var_r27 >= 0; var_r27--) {
                    if (var_r27 != var_r26) {
                        temp_r30->attrs[var_r27 + 1] = temp_r30->attrs[var_r27];
                    }
                }
                temp_r30->attrs[0] = var_r22;
            }
        }
        if (temp_r30->invAlpha != 0.0 || (temp_r30->pass & 0xF)) {
            Hu3DObjInfoP->flags |= 1;
        }
        if (temp_r30->flags & 0x30) {
            Hu3DObjInfoP->flags |= 0x800;
        }
        if (temp_r30->refAlpha != 0.0) {
            Hu3DObjInfoP->flags |= 4;
        }
        if (temp_r30->flags & 0x100) {
            Hu3DObjInfoP->flags |= 0x8000;
        }
        if (temp_r30->flags & 0x1000) {
            Hu3DObjInfoP->flags |= 0x10000;
        }
        faceCnt = 0;
        switch (arg1->type & 7) {
            case 0:
            case 1:
                break;
            case 2:
                GXBegin(GX_TRIANGLES, GX_VTXFMT0, faceNumBuf[drawCnt]);
                for (var_r27 = 0; var_r27 < faceNumBuf[drawCnt] / 3; var_r27++, arg1++) {
                    GXPosition1x16(arg1->indices[0][0]);
                    if (var_r26 == -1) {
                        GXNormal1x16(arg1->indices[0][1]);
                    } else {
                        MakeCalcNBT(arg0, arg1, 0, 1);
                    }
                    if (temp_r30->vtxMode == 5) {
                        temp_r28 = arg1->indices[0][2];
                        GXColor1x16(temp_r28);
                        if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                            Hu3DObjInfoP->flags |= 0x4001;
                        }
                    }
                    if (var_r25 != 0) {
                        GXTexCoord1x16(arg1->indices[0][3]);
                    }
                    GXPosition1x16(arg1->indices[2][0]);
                    if (var_r26 == -1) {
                        GXNormal1x16(arg1->indices[2][1]);
                    } else {
                        MakeNBT(arg0, arg1, 2, 0);
                    }
                    if (temp_r30->vtxMode == 5) {
                        temp_r28 = arg1->indices[2][2];
                        GXColor1x16(temp_r28);
                        if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                            Hu3DObjInfoP->flags |= 0x4001;
                        }
                    }
                    if (var_r25 != 0) {
                        GXTexCoord1x16(arg1->indices[2][3]);
                    }
                    GXPosition1x16(arg1->indices[1][0]);
                    if (var_r26 == -1) {
                        GXNormal1x16(arg1->indices[1][1]);
                    } else {
                        MakeNBT(arg0, arg1, 1, 2);
                    }
                    if (temp_r30->vtxMode == 5) {
                        temp_r28 = arg1->indices[1][2];
                        GXColor1x16(temp_r28);
                        if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                            Hu3DObjInfoP->flags |= 0x4001;
                        }
                    }
                    if (var_r25 != 0) {
                        GXTexCoord1x16(arg1->indices[1][3]);
                    }
                }
                faceCnt = faceNumBuf[drawCnt] / 3;
                break;
            case 3:
                GXBegin(GX_QUADS, GX_VTXFMT0, faceNumBuf[drawCnt]);
                for (var_r27 = 0; var_r27 < faceNumBuf[drawCnt] / 4; var_r27++, arg1++) {
                    GXPosition1x16(arg1->indices[0][0]);
                    if (var_r26 == -1) {
                        GXNormal1x16(arg1->indices[0][1]);
                    } else {
                        MakeCalcNBT(arg0, arg1, 0, 1);
                    }
                    if (temp_r30->vtxMode == 5) {
                        temp_r28 = arg1->indices[0][2];
                        GXColor1x16(temp_r28);
                        if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                            Hu3DObjInfoP->flags |= 0x4001;
                        }
                    }
                    if (var_r25 != 0) {
                        GXTexCoord1x16(arg1->indices[0][3]);
                    }
                    GXPosition1x16(arg1->indices[2][0]);
                    if (var_r26 == -1) {
                        GXNormal1x16(arg1->indices[2][1]);
                    } else {
                        MakeNBT(arg0, arg1, 2, 0);
                    }
                    if (temp_r30->vtxMode == 5) {
                        temp_r28 = arg1->indices[2][2];
                        GXColor1x16(temp_r28);
                        if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                            Hu3DObjInfoP->flags |= 0x4001;
                        }
                    }
                    if (var_r25 != 0) {
                        GXTexCoord1x16(arg1->indices[2][3]);
                    }
                    GXPosition1x16(arg1->indices[3][0]);
                    if (var_r26 == -1) {
                        GXNormal1x16(arg1->indices[3][1]);
                    } else {
                        MakeNBT(arg0, arg1, 3, 2);
                    }
                    if (temp_r30->vtxMode == 5) {
                        temp_r28 = arg1->indices[3][2];
                        GXColor1x16(temp_r28);
                        if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                            Hu3DObjInfoP->flags |= 0x4001;
                        }
                    }
                    if (var_r25 != 0) {
                        GXTexCoord1x16(arg1->indices[3][3]);
                    }
                    GXPosition1x16(arg1->indices[1][0]);
                    if (var_r26 == -1) {
                        GXNormal1x16(arg1->indices[1][1]);
                    } else {
                        MakeNBT(arg0, arg1, 1, 3);
                    }
                    if (temp_r30->vtxMode == 5) {
                        temp_r28 = arg1->indices[1][2];
                        GXColor1x16(temp_r28);
                        if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                            Hu3DObjInfoP->flags |= 0x4001;
                        }
                    }
                    if (var_r25 != 0) {
                        GXTexCoord1x16(arg1->indices[1][3]);
                    }
                }
                faceCnt = faceNumBuf[drawCnt] / 4;
                break;
            case 4:
                GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, faceNumBuf[drawCnt]);
                GXPosition1x16(arg1->indices[0][0]);
                if (var_r26 == -1) {
                    GXNormal1x16(arg1->indices[0][1]);
                } else {
                    MakeCalcNBT(arg0, arg1, 0, 1);
                }
                if (temp_r30->vtxMode == 5) {
                    temp_r28 = arg1->indices[0][2];
                    GXColor1x16(temp_r28);
                    if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                        Hu3DObjInfoP->flags |= 0x4001;
                    }
                }
                if (var_r25 != 0) {
                    GXTexCoord1x16(arg1->indices[0][3]);
                }
                GXPosition1x16(arg1->indices[2][0]);
                if (var_r26 == -1) {
                    GXNormal1x16(arg1->indices[2][1]);
                } else {
                    MakeNBT(arg0, arg1, 2, 0);
                }
                if (temp_r30->vtxMode == 5) {
                    temp_r28 = arg1->indices[2][2];
                    GXColor1x16(temp_r28);
                    if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                        Hu3DObjInfoP->flags |= 0x4001;
                    }
                }
                if (var_r25 != 0) {
                    GXTexCoord1x16(arg1->indices[2][3]);
                }
                GXPosition1x16(arg1->indices[1][0]);
                if (var_r26 == -1) {
                    GXNormal1x16(arg1->indices[1][1]);
                } else {
                    MakeNBT(arg0, arg1, 1, 2);
                }
                if (temp_r30->vtxMode == 5) {
                    temp_r28 = arg1->indices[1][2];
                    GXColor1x16(temp_r28);
                    if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                        Hu3DObjInfoP->flags |= 0x4001;
                    }
                }
                if (var_r25 != 0) {
                    GXTexCoord1x16(arg1->indices[1][3]);
                }
                var_r24 = arg1->strip.data;
                for (var_r27 = 0; var_r27 < arg1->strip.count; var_r27++, var_r24 += 4) {
                    GXPosition1x16(var_r24[0]);
                    if (var_r26 == -1) {
                        GXNormal1x16(var_r24[1]);
                    } else {
                        MakeCalcNBT(arg0, arg1, 0, 1);
                    }
                    if (temp_r30->vtxMode == 5) {
                        temp_r28 = var_r24[2];
                        GXColor1x16(temp_r28);
                        if (((GXColor*) arg0->data.color->data)[temp_r28].a != 0xFF) {
                            Hu3DObjInfoP->flags |= 0x4001;
                        }
                    }
                    if (var_r25 != 0) {
                        GXTexCoord1x16(var_r24[3]);
                    }
                }
                faceCnt = arg1->strip.count + 1;
                break;
        }
        temp_r3 = GXEndDisplayList();
        DrawData[drawCnt].dlSize = temp_r3;
        DrawData[drawCnt].polyCnt = faceCnt;
        totalSize += temp_r3;
        drawCnt++;
        DLBufP = (u8*) DLBufP + temp_r3;
    }
}

static s32 MakeCalcNBT(HsfObject *arg0, HsfFace *arg1, s16 arg2, s16 arg3) {
    Vec sp10;
    Vec *temp_r29;
    Vec *temp_r31;
    s8 (*temp_r28)[3];
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r27;

    temp_r31 = arg0->data.vertex->data;
    temp_r27 = arg1->indices[arg2][1];
    temp_r25 = arg1->indices[arg2][0];
    temp_r24 = arg1->indices[arg3][0];
    if (arg0->data.cenvCnt != 0) {
        temp_r29 = arg0->data.normal->data;
        sp10.x = temp_r29[temp_r27].x;
        sp10.y = temp_r29[temp_r27].y;
        sp10.z = temp_r29[temp_r27].z;
    } else {
        temp_r28 = arg0->data.normal->data;
        sp10.x = temp_r28[temp_r27][0];
        sp10.y = temp_r28[temp_r27][1];
        sp10.z = temp_r28[temp_r27][2];
        VECNormalize(&sp10, &sp10);
    }
    NBTB.x = temp_r31[temp_r25].x - temp_r31[temp_r24].x;
    NBTB.y = temp_r31[temp_r25].y - temp_r31[temp_r24].y;
    NBTB.z = temp_r31[temp_r25].z - temp_r31[temp_r24].z;
    VECNormalize(&NBTB, &NBTB);
    VECCrossProduct(&NBTB, &sp10, &NBTT);
    GXNormal3s16(sp10.x * 256.0f, sp10.y * 256.0f, sp10.z * 256.0f);
    GXNormal3s16(NBTB.x * 256.0f, NBTB.y * 256.0f, NBTB.z * 256.0f);
    GXNormal3s16(NBTT.x * 256.0f, NBTT.y * 256.0f, NBTT.z * 256.0f);
}

static s32 MakeNBT(HsfObject *arg0, HsfFace *arg1, s16 arg2, s16 arg3) {
    Vec sp10;
    Vec *temp_r30;
    Vec *spC;
    s8 (*temp_r29)[3];
    s16 temp_r28;

    spC = arg0->data.vertex->data;
    temp_r28 = arg1->indices[arg2][1];
    if (arg0->data.cenvCnt != 0) {
        temp_r30 = arg0->data.normal->data;
        sp10.x = temp_r30[temp_r28].x;
        sp10.y = temp_r30[temp_r28].y;
        sp10.z = temp_r30[temp_r28].z;
    } else {
        temp_r29 = arg0->data.normal->data;
        sp10.x = temp_r29[temp_r28][0];
        sp10.y = temp_r29[temp_r28][1];
        sp10.z = temp_r29[temp_r28][2];
        VECNormalize(&sp10, &sp10);
    }
    GXNormal3s16(sp10.x * 256.0f, sp10.y * 256.0f, sp10.z * 256.0f);
    GXNormal3s16(NBTB.x * 256.0f, NBTB.y * 256.0f, NBTB.z * 256.0f);
    GXNormal3s16(NBTT.x * 256.0f, NBTT.y * 256.0f, NBTT.z * 256.0f);
}

static void MDFaceCnt(HsfObject *arg0, HsfFace *arg1) {
    HsfMaterial *temp_r30;
    s16 i;

    temp_r30 = &arg0->data.material[arg1->mat & 0xFFF];
    // Bug? Likely to be polyTypeBak != (arg1->unk00 & 7)
    if (temp_r30 != materialBak || ((polyTypeBak != arg1->type) & 7) || (arg1->type & 7) == 4) {
        polySize = 4;
        polyTypeBak = arg1->type & 7;
        materialBak = temp_r30;
        matChgCnt++;
        if (DLFirstF != 0) {
            drawCnt++;
            faceNumBuf[drawCnt] = 0;
            DLTotalNum = ((DLTotalNum + 0x20) & ~0x1F) + 0x20;
        } else {
            DLFirstF = 1;
        }
        if (temp_r30->numAttrs != 0) {
            polySize += 2;
            for (i = 0; i < temp_r30->numAttrs; i++) {
                if (arg0->data.attribute[temp_r30->attrs[i]].unk14 != 0.0) {
                    polySize += 0x12;
                }
            }
        }
        if (temp_r30->vtxMode == 5) {
            polySize += 2;
        }
    }
    switch (arg1->type & 7) {
        case 0:
            OSReport("Error\n");
            break;
        case 1:
            OSReport("Error\n");
            break;
        case 2:
            triCnt++;
            faceNumBuf[drawCnt] += 3;
            DLTotalNum += polySize * 3;
            break;
        case 3:
            quadCnt++;
            faceNumBuf[drawCnt] += 4;
            DLTotalNum += polySize * 4;
            break;
        case 4:
            triCnt++;
            faceNumBuf[drawCnt] += arg1->strip.count + 3;
            DLTotalNum += polySize * 3;
            DLTotalNum += polySize * arg1->strip.count;
            break;
        default:
            OSReport("Error\n");
            break;
    }
}

void mtxTransCat(Mtx arg0, float arg1, float arg2, float arg3) {
    if (arg1 != 0.0f || arg2 != 0.0f || arg3 != 0.0f) {
        arg0[0][3] += arg1;
        arg0[1][3] += arg2;
        arg0[2][3] += arg3;
    }
}

void mtxRotCat(Mtx arg0, float arg1, float arg2, float arg3) {
    Mtx sp8;

    if (arg1 != 0.0f) {
        PSMTXRotRad(sp8, 'X', MTXDegToRad(arg1));
        PSMTXConcat(sp8, arg0, arg0);
    }
    if (arg2 != 0.0f) {
        PSMTXRotRad(sp8, 'Y', MTXDegToRad(arg2));
        PSMTXConcat(sp8, arg0, arg0);
    }
    if (arg3 != 0.0f) {
        PSMTXRotRad(sp8, 'Z', MTXDegToRad(arg3));
        PSMTXConcat(sp8, arg0, arg0);
    }
}

void mtxRot(Mtx arg0, float arg1, float arg2, float arg3) {
    Mtx sp38;
    Mtx sp8;

    if (arg1 != 0.0f) {
        PSMTXRotRad(arg0, 'X', MTXDegToRad(arg1));
    } else {
        PSMTXIdentity(arg0);
    }
    if (arg2 != 0.0f) {
        PSMTXRotRad(sp38, 'Y', MTXDegToRad(arg2));
        PSMTXConcat(sp38, arg0, arg0);
    }
    if (arg3 != 0.0f) {
        PSMTXRotRad(sp8, 'Z', MTXDegToRad(arg3));
        PSMTXConcat(sp8, arg0, arg0);
    }
}

void mtxScaleCat(Mtx arg0, float arg1, float arg2, float arg3) {
    arg0[0][0] *= arg1;
    arg0[1][0] *= arg1;
    arg0[2][0] *= arg1;
    arg0[0][1] *= arg2;
    arg0[1][1] *= arg2;
    arg0[2][1] *= arg2;
    arg0[0][2] *= arg3;
    arg0[1][2] *= arg3;
    arg0[2][2] *= arg3;
}

s16 HmfInverseMtxF3X3(Mtx arg0, Mtx arg1) {
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f31;

    temp_f30 = arg0[1][1] * arg0[2][2] - arg0[2][1] * arg0[1][2];
    temp_f29 = arg0[2][1] * arg0[0][2] - arg0[0][1] * arg0[2][2];
    temp_f28 = arg0[0][1] * arg0[1][2] - arg0[1][1] * arg0[0][2];
    temp_f31 = arg0[0][0] * temp_f30 + arg0[1][0] * temp_f29 + arg0[2][0] * temp_f28;
    if (temp_f31 == 0.0f) {
        return 0;
    }
    temp_f31 = 1.0f / temp_f31;
    arg1[0][0] = temp_f30 * temp_f31;
    arg1[0][1] = temp_f29 * temp_f31;
    arg1[0][2] = temp_f28 * temp_f31;
    arg1[1][0] = temp_f31 * (arg0[2][0] * arg0[1][2] - arg0[1][0] * arg0[2][2]);
    arg1[2][0] = temp_f31 * (arg0[1][0] * arg0[2][1] - arg0[2][0] * arg0[1][1]);
    arg1[1][1] = temp_f31 * (arg0[0][0] * arg0[2][2] - arg0[2][0] * arg0[0][2]);
    arg1[2][1] = temp_f31 * (arg0[2][0] * arg0[0][1] - arg0[0][0] * arg0[2][1]);
    arg1[1][2] = temp_f31 * (arg0[1][0] * arg0[0][2] - arg0[0][0] * arg0[1][2]);
    arg1[2][2] = temp_f31 * (arg0[0][0] * arg0[1][1] - arg0[1][0] * arg0[0][1]);
    arg1[0][3] = arg1[1][3] = arg1[2][3] = 0.0f;
    return 1;
}

static inline void SetDefLightInlineFunc(GXLightObj *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9) {
    GXColor spE;

    spE.r = arg1;
    spE.g = arg2;
    spE.b = arg3;
    spE.a = 0xFF;
    GXInitLightColor(arg0, spE);
    GXLoadLightObjImm(arg0, GX_LIGHT0);
    spE.r = arg4;
    spE.g = arg5;
    spE.b = arg6;
    GXSetChanAmbColor(GX_COLOR0A0, spE);
    spE.r = arg7;
    spE.g = arg8;
    spE.b = arg9;
    GXSetChanMatColor(GX_COLOR0A0, spE);
}

void SetDefLight(Vec *arg0, Vec *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA) {
    GXLightObj sp20;

    GXInitLightAttn(&sp20, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    GXInitLightSpot(&sp20, 20.0f, GX_SP_COS);
    GXInitLightPos(&sp20, arg0->x, arg0->y, arg0->z);
    GXInitLightDir(&sp20, arg1->x, arg1->y, arg1->z);
    SetDefLightInlineFunc(&sp20, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA);
}

void Hu3DModelObjPosGet(s16 arg0, char *arg1, Vec *arg2) {
    Mtx spC;

    Hu3DModelObjMtxGet(arg0, arg1, spC);
    arg2->x = spC[0][3];
    arg2->y = spC[1][3];
    arg2->z = spC[2][3];
    if (PGFinishF == 0) {
        OSReport("Error: Not Found %s for ObjPosGet\n", arg1);
        arg2->x = arg2->y = arg2->z = 0.0f;
    }
}

void Hu3DModelObjMtxGet(s16 arg0, char *arg1, Mtx arg2) {
    ModelData *temp_r31;
    HsfData *temp_r30;
    Mtx spA0;
    Mtx sp70;
    Mtx sp40;

    temp_r31 = &Hu3DData[arg0];
    temp_r30 = temp_r31->hsfData;
    mtxRot(sp70, temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
    PSMTXScale(spA0, temp_r31->scale.x, temp_r31->scale.y, temp_r31->scale.z);
    PSMTXConcat(sp70, spA0, MTXBuf[0]);
    mtxTransCat(MTXBuf[0], temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
    PGMaxPos.x = PGMaxPos.y = PGMaxPos.z = -1000000.0f;
    PGMinPos.x = PGMinPos.y = PGMinPos.z = 1000000.0f;
    MTXIdx = 1;
    CancelTRXF = 0;
    PGFinishF = 0;
    hookIdx = -1;
    PGName = HuMemDirectMallocNum(HEAP_SYSTEM, 0x200, MEMORY_DEFAULT_NUM);
    strcpy((char*) PGName, MakeObjectName(arg1));
    if (temp_r31->unk_08 != -1) {
        attachMotionF = 1;
    } else {
        attachMotionF = 0;
    }
    PGObjCall(temp_r31, temp_r30->root);
    PSMTXCopy(MTXBuf[MTXIdx - 1], arg2);
    if (PGFinishF == 0 && *PGName != 0) {
        OSReport("Error: Not Found %s for ObjPosGet\n", arg1);
        PSMTXIdentity(MTXBuf[MTXIdx]);
    }
    HuMemDirectFree(PGName);
}

void PGObjCall(ModelData *arg0, HsfObject *arg1) {
    switch (arg1->type) {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 9:
            PGObjCalc(arg0, arg1);
            break;
        case 1:
            PGObjReplica(arg0, arg1);
            break;
    }
}

void PGObjCalc(ModelData *arg0, HsfObject *arg1) {
    Vec sp8;
    s16 temp_r22;
    s16 var_r24;
    s16 var_r27;
    HsfObject *var_r23;
    HsfConstData *temp_r28;
    HsfTransform *var_r30;
    ModelData *temp_r31;
    Mtx spD4;
    Mtx spA4;
    Mtx sp74;

    if (CancelTRXF == 0) {
        if (attachMotionF == 0) {
            var_r30 = &arg1->data.base;
        } else {
            var_r30 = &arg1->data.curr;
        }
        mtxRot(spA4, var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
        PSMTXScale(spD4, var_r30->scale.x, var_r30->scale.y, var_r30->scale.z);
        PSMTXConcat(spA4, spD4, spD4);
        mtxTransCat(spD4, var_r30->pos.x, var_r30->pos.y, var_r30->pos.z);
        PSMTXConcat(MTXBuf[MTXIdx - 1], spD4, MTXBuf[MTXIdx]);
        MTXIdx++;
        var_r24 = 1;
    } else {
        CancelTRXF = 0;
        var_r24 = 0;
    }
    if (strcmp((char*) PGName, arg1->name) == 0) {
        PGFinishF = 1;
        return;
    }
    temp_r28 = arg1->constData;
    if (temp_r28 && temp_r28->hook != -1) {
        temp_r31 = &Hu3DData[temp_r28->hook];
        if (!(temp_r31->attr & HU3D_ATTR_DISPOFF)) {
            var_r27 = attachMotionF;
            if (temp_r31->unk_08 != -1) {
                attachMotionF = 1;
            } else {
                attachMotionF = 0;
            }
            temp_r22 = hookIdx;
            hookIdx = temp_r28->hook;
            PSMTXScale(spD4, temp_r31->scale.x, temp_r31->scale.y, temp_r31->scale.z);
            mtxRotCat(spD4, temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
            mtxTransCat(spD4, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            PSMTXConcat(spD4, temp_r31->unk_F0, spD4);
            PSMTXConcat(MTXBuf[MTXIdx - 1], spD4, MTXBuf[MTXIdx]);
            MTXIdx++;
            PGObjCall(temp_r31, temp_r31->hsfData->root);
            MTXIdx--;
            hookIdx = temp_r22;
            attachMotionF = var_r27;
        }
    }
    if (*PGName == 0 && arg1->type == 2) {
        var_r23 = arg1;
        PSMTXMultVec(MTXBuf[MTXIdx - 1], (Vec*) &var_r23->data.mesh.min, &sp8);
        if (sp8.x < PGMinPos.x) {
            PGMinPos.x = sp8.x;
        }
        if (sp8.y < PGMinPos.y) {
            PGMinPos.y = sp8.y;
        }
        if (sp8.z < PGMinPos.z) {
            PGMinPos.z = sp8.z;
        }
        if (sp8.x > PGMaxPos.x) {
            PGMaxPos.x = sp8.x;
        }
        if (sp8.y > PGMaxPos.y) {
            PGMaxPos.y = sp8.y;
        }
        if (sp8.z > PGMaxPos.z) {
            PGMaxPos.z = sp8.z;
        }
        PSMTXMultVec(MTXBuf[MTXIdx - 1], (Vec*) &var_r23->data.mesh.max, &sp8);
        if (sp8.x < PGMinPos.x) {
            PGMinPos.x = sp8.x;
        }
        if (sp8.y < PGMinPos.y) {
            PGMinPos.y = sp8.y;
        }
        if (sp8.z < PGMinPos.z) {
            PGMinPos.z = sp8.z;
        }
        if (sp8.x > PGMaxPos.x) {
            PGMaxPos.x = sp8.x;
        }
        if (sp8.y > PGMaxPos.y) {
            PGMaxPos.y = sp8.y;
        }
        if (sp8.z > PGMaxPos.z) {
            PGMaxPos.z = sp8.z;
        }
    }
    for (var_r27 = 0; var_r27 < arg1->data.childrenCount; var_r27++) {
        PGObjCall(arg0, arg1->data.children[var_r27]);
        if (PGFinishF != 0) {
            return;
        }
    }
    if (var_r24 != 0) {
        MTXIdx--;
    }
}

void PGObjReplica(ModelData *arg0, HsfObject *arg1) {
    HsfTransform *var_r31;
    Mtx sp1B8;
    Mtx sp188;

    if (attachMotionF == 0) {
        var_r31 = &arg1->data.base;
    } else {
        var_r31 = &arg1->data.curr;
    }
    mtxRot(sp188, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
    PSMTXScale(sp1B8, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
    PSMTXConcat(sp188, sp1B8, sp1B8);
    mtxTransCat(sp1B8, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
    PSMTXConcat(MTXBuf[MTXIdx - 1], sp1B8, MTXBuf[MTXIdx]);
    MTXIdx++;
    CancelTRXF = 1;
    PGObjCall(arg0, arg1->data.replica);
    if (PGFinishF == 0) {
        CancelTRXF = 0;
        MTXIdx--;
    }
}

HsfObject *Hu3DObjDuplicate(HsfData *arg0, u32 arg1) {
    HsfObject *temp_r27;
    HsfObject *var_r30;
    HsfObject *var_r31;
    s16 i;
    s16 j;

    var_r31 = HuMemDirectMallocNum(HEAP_DATA, arg0->objectCnt * sizeof(HsfObject), arg1);
    temp_r27 = var_r31;
    var_r30 = arg0->object;
    memcpy(temp_r27, var_r30, arg0->objectCnt * sizeof(HsfObject));
    for (i = 0; i < arg0->objectCnt; i++, var_r31++, var_r30++) {
        if (var_r31->type != 8 && var_r31->type != 7) {
            if (var_r31->data.parent) {
                var_r31->data.parent = (HsfObject*) ((u8*) temp_r27 + ((u32) var_r30->data.parent - (u32) arg0->object));
            }
            var_r31->data.children = HuMemDirectMallocNum(HEAP_DATA, var_r30->data.childrenCount * 4, arg1);
            if (var_r30->constData) {
                var_r31->constData = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfConstData), arg1);
                memcpy(var_r31->constData, var_r30->constData, sizeof(HsfConstData));
            }
            for (j = 0; j < var_r30->data.childrenCount; j++) {
                var_r31->data.children[j] = (HsfObject*) ((u8*) temp_r27 + ((u32) var_r30->data.children[j] - (u32) arg0->object));
            }
        }
    }
    return temp_r27;
}

void Hu3DModelObjDrawInit(void) {
    s16 i;

    GXSetCullMode(GX_CULL_BACK);
    for (i = 0; i < 8; i++) {
        BmpPtrBak[i] = (HsfAttribute*) -1;
    }
    CancelTRXF = 0;
    hookIdx = -1;
    shadingBak = -1;
    vtxModeBak = -1;
    materialBak = (HsfMaterial*) -1;
    attachMotionF = 0;
}

void Hu3DModelObjDraw(s16 arg0, char *arg1, Mtx arg2) {
    HsfDrawObject sp14;
    HsfConstData *sp10;
    HsfObject *temp_r3;

    sp14.model = &Hu3DData[arg0];
    sp14.object = temp_r3 = Hu3DModelObjPtrGet(arg0, arg1);
    sp10 = temp_r3->constData;
    PSMTXCopy(arg2, sp14.matrix);
    sp14.scale.x = sp14.scale.y = sp14.scale.z = 1.0f;
    ObjDraw(&sp14);
}
