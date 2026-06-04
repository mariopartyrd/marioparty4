#include "game/disp.h"
#include "game/hu3d.h"
#include "game/hsfformat.h"
#include "game/hsfload.h"
#include "game/sprite.h"

#include "ext_math.h"
#include <string.h>

#define DRAW_OBJ_MAX 512

#define PTR_INVALID ((void *)-1)

#define HSF_TEXID_TL32 0x8000

#define MTXBUF_MAX 96

static void objCall(HU3DMODEL *modelP, HSFOBJECT *objPtr);
static void objMesh(HU3DMODEL *modelP, HSFOBJECT *objPtr);
static void SetTevStageNoTex(HU3DDRAWOBJ *drawObj, HSFMATERIAL *matP);
static void SetTevStageTex(HU3DDRAWOBJ *drawObj, HSFMATERIAL *matP);
static GXTevKColorSel SetKColor(GXTevStageID tevStage, u8 color);
static GXTevKColorSel SetKColorRGB(GXTevStageID tevStage, GXColor *color);
static void FlushKColor(void);
static void SetReflect(HU3DDRAWOBJ *drawObj, s16 tevStage, s16 texCoord, u8 color);
static void SetProjection(HU3DDRAWOBJ *drawObj, s16 tevStage, s16 projNo, s16 texCoord, GXTexMapID texMap, u32 texMtx);
static void SetShadowTex(void);
static void SetShadow(HU3DDRAWOBJ *drawObj, s16 tevStage, s16 texCoord);
static void FaceDrawShadow(HU3DDRAWOBJ *drawObj, HSFFACE *face);
static void LoadTexture(HU3DMODEL *modelP, HSFBITMAP *bmpPtr, HSFATTRIBUTE *attrP, s16 texId);
static void objNull(HU3DMODEL *modelP, HSFOBJECT *objPtr);
static void objRoot(HU3DMODEL *modelP, HSFOBJECT *objPtr);
static void objJoint(HU3DMODEL *modelP, HSFOBJECT *objPtr);
static void objMap(HU3DMODEL *modelP, HSFOBJECT *objPtr);
static void objReplica(HU3DMODEL *modelP, HSFOBJECT *objPtr);
static void ObjDraw(HU3DDRAWOBJ *arg0);
static void MDObjCall(HSFDATA *hsf, HSFOBJECT *objPtr);
static void MDObjMesh(HSFDATA *hsf, HSFOBJECT *objPtr);
static void MDFaceDraw(HSFOBJECT *objPtr, HSFFACE *face);
static s32 MakeCalcNBT(HSFOBJECT *objPtr, HSFFACE *face, s16 endVtx, s16 startVtx);
static s32 MakeNBT(HSFOBJECT *objPtr, HSFFACE *face, s16 endVtx, s16 startVtx);
static void MDFaceCnt(HSFOBJECT *objPtr, HSFFACE *face);

void GXResetWriteGatherPipe(void);

static const Vec lbl_8011DD20 = { 0.0f, 0.0f, -1.0f };

static HU3DDRAWOBJ DrawObjData[DRAW_OBJ_MAX];
static HSFATTRIBUTE *BmpPtrBak[8];
static Mtx MTXBuf[MTXBUF_MAX];
static Vec scaleBuf[MTXBUF_MAX];
static GXColor texCol[16];
static Mtx hiliteMtx;
static s16 DrawObjNum[DRAW_OBJ_MAX];
static Vec NBTB;
static Vec NBTT;
Vec PGMaxPos;
Vec PGMinPos;

s16 MTXIdx;
static HSFMATERIAL *materialBak;
static u8 polyTypeBak;
static s32 shadingBak;
static void *DLBufP;
static void *DLBufStartP;
static HSFDRAWDATA *DrawData;
static s32 drawCnt;
static s16 lightBit;
static s16 DrawObjIdx;
static HSFCONSTDATA *Hu3DObjInfoP;
static s16 reflectionMapNo;
static s16 hiliteMapNo;
static s16 vtxModeBak;
static s32 attachMotionF;
static s16 shadowMapNo;
static s16 toonMapNo;
static s16 projectionMapNo;
static GXColor kColor;
static s32 kColorIdx;
static HU3DMODELID hookIdx;
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
static BOOL DLFirstF;
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
static BOOL PGFinishF;
static u8 *PGName;
static BOOL TL32F;
static BOOL CancelTRXF;

u8 texMtxTbl[] = {
    GX_TEXMTX0, GX_TEXMTX1,
    GX_TEXMTX2, GX_TEXMTX3,
    GX_TEXMTX4, GX_TEXMTX5,
    GX_TEXMTX6, GX_TEXMTX7,
    GX_TEXMTX8, GX_TEXMTX9
};

static s16 oneceF = TRUE;
static GXColor firstTev = { 0xFF, 0xFF, 0x00, 0x00 };
static GXColor secondTev = { 0x00, 0x00, 0xFF, 0xFF };

void Hu3DDrawPreInit(void) {
    DrawObjIdx = 0;
}

void Hu3DDraw(HU3DMODEL *modelP, Mtx mtx, HuVecF *scale) {
    HU3DDRAWOBJ *drawObj;
    HSFDATA *hsf;
    float z;
    HuVecF pos;
    s16 i;

    hsf = modelP->hsf;
    if (modelP->attr & HU3D_ATTR_HOOKFUNC) {
        drawObj = &DrawObjData[DrawObjIdx];
        MTXCopy(mtx, drawObj->matrix);
        pos.x = drawObj->matrix[0][3];
        pos.y = drawObj->matrix[1][3];
        pos.z = drawObj->matrix[2][3];
        z = VECMag(&pos);
        drawObj->z = z;
        drawObj->model = modelP;
        DrawObjIdx++;
        return;
    }
    modelMeshNum = 0;
    modelObjNum = 0;
    GXSetCullMode(GX_CULL_BACK);
    for (i = 0; i < 8; i++) {
        BmpPtrBak[i] = PTR_INVALID;
    }
    MTXCopy(mtx, MTXBuf[0]);
    scaleBuf[0] = *scale;
    MTXIdx = 1;
    CancelTRXF = 0;
    hookIdx = HU3D_MODELID_NONE;
    shadingBak = -1;
    vtxModeBak = -1;
    materialBak = PTR_INVALID;
    if (modelP->motId != HU3D_MOTID_NONE) {
        attachMotionF = TRUE;
    } else {
        attachMotionF = FALSE;
    }
    objCall(modelP, hsf->root);
    GXSetNumTevStages(1);
    oneceF = 1;
}

static void objCall(HU3DMODEL *modelP, HSFOBJECT *objPtr) {
    modelObjNum++;
    switch (objPtr->type) {
        case 2:
            objMesh(modelP, objPtr);
            modelMeshNum++;
            break;
        case 4:
            objJoint(modelP, objPtr);
            break;
        case 5:
            objNull(modelP, objPtr);
            break;
        case 0:
            objNull(modelP, objPtr);
            break;
        case 1:
            objReplica(modelP, objPtr);
            break;
        case 3:
            objRoot(modelP, objPtr);
            break;
        case 6:
            objNull(modelP, objPtr);
            break;
        case 9:
            objMap(modelP, objPtr);
            break;
    }
}

static void objMesh(HU3DMODEL *modelP, HSFOBJECT *objPtr) {
    HU3DDRAWOBJ *drawObj;
    HSFCONSTDATA *constData;
    HSFTRANSFORM *transformP;
    HSFDATA *hsf;
    HU3DMODEL *hookMdlP;
    Mtx mtx;
    HuVecF pos;
    HuVecF *prevScale;
    HuVecF *scale;
    void *faceData;
    s16 hookIdxOld;
    s16 i;
    s16 applyF;
    s16 dispF;
    float z;
    HSFBUFFER *faceBuf;

    faceBuf = objPtr->mesh.face;
    faceData = faceBuf->data;
    drawObj = &DrawObjData[DrawObjIdx];
    hsf = modelP->hsf;
    if (attachMotionF == FALSE) {
        transformP = &objPtr->mesh.base;
    } else {
        transformP = &objPtr->mesh.curr;
    }
    constData = objPtr->constData;
    if (!(constData->attr & HU3D_CONST_LOCK)) {
        if (CancelTRXF == FALSE) {
            if (objPtr->mesh.cenvNum != 0 && hookIdx == HU3D_MODELID_NONE) {
                i = objPtr - hsf->object;
                MTXConcat(MTXBuf[0], hsf->matrix->data[i + hsf->matrix->base_idx], MTXBuf[MTXIdx]);
            } else {
                MTXScale(mtx, transformP->scale.x, transformP->scale.y, transformP->scale.z);
                mtxRotCat(mtx, transformP->rot.x, transformP->rot.y, transformP->rot.z);
                mtxTransCat(mtx, transformP->pos.x, transformP->pos.y, transformP->pos.z);
                MTXConcat(MTXBuf[MTXIdx - 1], mtx, MTXBuf[MTXIdx]);
            }
            scale = &scaleBuf[MTXIdx];
            prevScale = scale - 1;
            scale->x = prevScale->x * transformP->scale.x;
            scale->y = prevScale->y * transformP->scale.y;
            scale->z = prevScale->z * transformP->scale.z;
            drawObj->scale = *scale;
            if (objPtr->flags & HSF_MATERIAL_BBOARD) {
                MTXInverse(MTXBuf[MTXIdx], mtx);
                mtx[0][3] = mtx[1][3] = mtx[2][3] = 0.0f;
                MTXConcat(MTXBuf[MTXIdx], mtx, drawObj->matrix);
                mtxScaleCat(drawObj->matrix, scale->x, scale->y, scale->z);
            } else {
                MTXCopy(MTXBuf[MTXIdx], drawObj->matrix);
            }
            MTXIdx++;
            applyF = TRUE;
        } else {
            if (objPtr->flags & HSF_MATERIAL_BBOARD) {
                MTXInverse(MTXBuf[MTXIdx - 1], mtx);
                mtx[0][3] = mtx[1][3] = mtx[2][3] = 0.0f;
                MTXConcat(MTXBuf[MTXIdx - 1], mtx, drawObj->matrix);
                mtxScaleCat(drawObj->matrix, scaleBuf[MTXIdx - 1].x, scaleBuf[MTXIdx - 1].y, scaleBuf[MTXIdx - 1].z);
            } else {
                MTXCopy(MTXBuf[MTXIdx - 1], drawObj->matrix);
            }
            drawObj->scale = scaleBuf[MTXIdx - 1];
            CancelTRXF = FALSE;
            applyF = FALSE;
        }
        MTXCopy(drawObj->matrix, constData->matrix);
        if (constData->hookMdlId != HU3D_MODELID_NONE) {
            hookMdlP = &Hu3DData[constData->hookMdlId];
            if (!(hookMdlP->attr & HU3D_ATTR_DISPOFF)) {
                i = attachMotionF;
                if (hookMdlP->motId != HU3D_MOTID_NONE) {
                    attachMotionF = 1;
                } else {
                    attachMotionF = 0;
                }
                hookIdxOld = hookIdx;
                hookIdx = constData->hookMdlId;
                MTXScale(mtx, hookMdlP->scale.x, hookMdlP->scale.y, hookMdlP->scale.z);
                mtxRotCat(mtx, hookMdlP->rot.x, hookMdlP->rot.y, hookMdlP->rot.z);
                mtxTransCat(mtx, hookMdlP->pos.x, hookMdlP->pos.y, hookMdlP->pos.z);
                MTXConcat(mtx, hookMdlP->mtx, mtx);
                MTXConcat(drawObj->matrix, mtx, MTXBuf[MTXIdx]);
                scale = &scaleBuf[MTXIdx];
                prevScale = scale - 1;
                scale->x = prevScale->x * hookMdlP->scale.x;
                scale->y = prevScale->y * hookMdlP->scale.y;
                scale->z = prevScale->z * hookMdlP->scale.z;
                MTXIdx++;
                objCall(hookMdlP, hookMdlP->hsf->root);
                MTXIdx--;
                hookIdx = hookIdxOld;
                attachMotionF = i;
            }
        } else {
            if (modelP->attr & HU3D_ATTR_NOCULL) {
                dispF = ObjCullCheck(modelP->hsf, objPtr, drawObj->matrix);
            } else {
                dispF = TRUE;
            }
            if ((constData->attr & HU3D_CONST_DISPOFF) || (objPtr->flags & HU3D_ATTR_CLUSTER_ON)) {
                dispF = FALSE;
            }
            if (dispF && (transformP->scale.x != 0.0f || transformP->scale.y != 0.0f || transformP->scale.z != 0.0f)) {
                drawObj->model = modelP;
                drawObj->object = objPtr;
                if ((constData->attr & (HU3D_CONST_NEAR|HU3D_CONST_ALTBLEND|HU3D_CONST_XLU)) && shadowModelDrawF == FALSE) {
                    pos.x = drawObj->matrix[0][3];
                    pos.y = drawObj->matrix[1][3];
                    pos.z = drawObj->matrix[2][3];
                    z = VECMag(&pos);
                    if (constData->attr & HU3D_CONST_NEAR) {
                        drawObj->z = -(900000.0f - z);
                    } else {
                        drawObj->z = -(1000000.0f - z);
                    }
                    DrawObjIdx++;
                    if (DrawObjIdx > DRAW_OBJ_MAX) {
                        OSReport("Error: DrawObjIdx Over\n");
                        DrawObjIdx--;
                    }
                } else if (modelP->attr & HU3D_ATTR_ZCMP_OFF) {
                    drawObj->z = -1000000.0f;
                    DrawObjIdx++;
                    if (DrawObjIdx > DRAW_OBJ_MAX) {
                        OSReport("Error: DrawObjIdx Over\n");
                        DrawObjIdx--;
                    }
                } else {
                    materialBak = PTR_INVALID;
                    ObjDraw(drawObj);
                }
            }
        }
        for (i = 0; i < objPtr->mesh.childrenCount; i++) {
            objCall(modelP, objPtr->mesh.children[i]);
        }
        if (applyF != 0) {
            MTXIdx--;
        }
    }
}

BOOL ObjCullCheck(HSFDATA *hsf, HSFOBJECT *objPtr, Mtx mtx) {
    HU3DCAMERA *cameraP;
    HuVecF *max;
    HuVecF *min;
    Mtx cullMtx;
    float fovTan;
    float x;
    float y;
    float z;
    float radius;
    float cameraW;
    float scaleX;
    float scaleY;
    float cameraH;
    float scale;
    float scaleZ;
    float centerX;
    float centerY;
    float centerZ;

    cameraP = &Hu3DCamera[Hu3DCameraNo];
    min = &objPtr->mesh.mesh.min;
    max = &objPtr->mesh.mesh.max;
    scaleX = scaleBuf[MTXIdx - 1].x;
    scaleY = scaleBuf[MTXIdx - 1].y;
    scaleZ = scaleBuf[MTXIdx - 1].z;
    if (scaleX > scaleY) {
        if (scaleX > scaleZ) {
            scale = scaleX;
        } else if (scaleY > scaleZ) {
            scale = scaleY;
        } else {
            scale = scaleZ;
        }
    } else if (scaleY > scaleZ) {
        scale = scaleY;
    } else if (scaleX > scaleZ) {
        scale = scaleX;
    } else {
        scale = scaleZ;
    }
    centerX = (max->x - min->x) * 0.5;
    centerY = (max->y - min->y) * 0.5;
    centerZ = (max->z - min->z) * 0.5;
    MTXTrans(cullMtx, centerX + min->x, centerY + min->y, centerZ + min->z);
    MTXConcat(mtx, cullMtx, cullMtx);
    radius = scale * sqrtf(centerX * centerX + centerY * centerY + centerZ * centerZ);
    x = cullMtx[0][3];
    y = cullMtx[1][3];
    z = -cullMtx[2][3];
    if (z + radius < cameraP->near || z - radius > cameraP->far) {
        return 0;
    }
    fovTan = sind(cameraP->fov * 0.5) / cosd(cameraP->fov * 0.5);
    cameraH = fovTan * z;
    cameraW = HU_DISP_ASPECT * cameraH;
    cameraW = radius + ABS(cameraW);
    cameraH = radius + ABS(cameraH);
    if (ABS(x) < cameraW && ABS(y) < cameraH) {
        return 1;
    }
    return 0;
}

inline void SetBlendMode(u32 flags) {
    if (flags & (HSF_MATERIAL_ADDCOL|HSF_MATERIAL_INVCOL)) {
        if (flags & HSF_MATERIAL_ADDCOL) {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        } else {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
        }
    } else {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }
}

inline void SetupGX(const HSFMATERIAL* material, const HSFCONSTDATA* constData, const HU3DMODEL* modelData, u32 flags, s16 tevStage) {
    if ((material->invAlpha != 0.0f || (material->pass & 0xF) || (constData->attr & HU3D_CONST_ALTBLEND)) && !((modelData->attr & HU3D_ATTR_ZWRITE_OFF) | (flags & (HSF_MATERIAL_DISABLE_ZWRITE|HSF_MATERIAL_NEAR)))) {
        GXSetZMode(tevStage, GX_LEQUAL, GX_FALSE);
    } else {
        GXSetZMode(tevStage, GX_LEQUAL, GX_TRUE);
    }

    if (flags & (HSF_MATERIAL_DISABLE_ZWRITE|HSF_MATERIAL_NEAR)) {
        GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_GEQUAL, 0x80);
    } else {
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    }

    if (modelData->attr & HU3D_ATTR_CULL_FRONT) {
        GXSetCullMode(GX_CULL_FRONT);
    } else if (flags & HSF_MATERIAL_NOCULL) {
        GXSetCullMode(GX_CULL_NONE);
    } else {
        GXSetCullMode(GX_CULL_BACK);
    }
}

static void FaceDraw(HU3DDRAWOBJ *hsfDrawObject, HSFFACE *hsfFace) {
    GXColor tempColor;
    void *displayListPtr;
    HU3DTEXANIM *texAnimData;
    s16 tevStage;
    HSFMATERIAL *faceMaterial;
    HU3DMODEL *model;
    HSFOBJECT *object;
    HSFBITMAP *currentBitmap;
    HSFATTRIBUTE *currentAttribute;
    HU3DATTRANIM *currentDrawData;
    HSFCONSTDATA *constData;
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
    faceMaterial = &object->mesh.material[hsfFace->mat & 0xFFF];
    flags = object->flags | faceMaterial->flags;
    SetBlendMode(flags);

    if (faceMaterial != materialBak) {
        totalMatCnt++;
        materialBak = faceMaterial;
        tempColor.r = faceMaterial->litColor[0] * model->ambR;
        tempColor.g = faceMaterial->litColor[1] * model->ambG;
        tempColor.b = faceMaterial->litColor[2] * model->ambB;
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

        if (TL32F) {
            for (tevStage = GX_TEVSTAGE0; tevStage < GX_MAX_TEVSTAGE; tevStage++) {
                GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
            }
            TL32F = 0;
        }

        for (tevStage = GX_TEVSTAGE0; tevStage < GX_MAX_TEVSTAGE; tevStage++) {
            GXSetTevKAlphaSel(tevStage, GX_TEV_KASEL_1);
        }

        if (faceMaterial->attrNum == 0) {
            vtxMode = (faceMaterial->vtxMode == 5) ? 4 : 0;
            if (vtxMode != vtxModeBak) {
                vtxModeBak = vtxMode;
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, object->mesh.vertex->data, 3 * sizeof(float));
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                if (model->hsf->cenvNum == 0) {
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 0);
                    GXSetArray(GX_VA_NRM, object->mesh.normal->data, 3);
                } else {
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                    GXSetArray(GX_VA_NRM, object->mesh.normal->data, 3 * sizeof(float));
                }
                if (vtxMode & 4) {
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                    GXSetArray(GX_VA_CLR0, object->mesh.color->data, 4);
                }
                GXSetZCompLoc(GX_TRUE);
            }
            if (faceMaterial->refAlpha != 0.0f) {
                reflectionMapNo = 0;
                BmpPtrBak[0] = PTR_INVALID;
                if (model->reflectType != HU3D_REFLECT_TYPE_NONE) {
                    reflectAnimIdx = model->reflectType;
                } else {
                    reflectAnimIdx = reflectMapNo;
                }
                HuSprTexLoad(reflectAnim[reflectAnimIdx], 0, reflectionMapNo, GX_REPEAT, GX_REPEAT, GX_LINEAR);
            }
            if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->attr & HU3D_CONST_SHADOW_MAP)) {
                shadowMapNo = 1;
                SetShadowTex();
                BmpPtrBak[1] = PTR_INVALID;
            }
            if (model->attr & HU3D_ATTR_TOON_MAP) {
                toonMapNo = 2;
                HuSprTexLoad(toonAnim, 0, toonMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                BmpPtrBak[2] = PTR_INVALID;
            }
            if (model->projBit != 0) {
                projectionMapNo = 3;
                hiliteMapNo = projectionMapNo + 1;
                for (tevStage = 0, var_r24 = 1; tevStage < HU3D_PROJ_MAX; tevStage++, var_r24 <<= 1) {
                    if (var_r24 & model->projBit) {
                        HuSprTexLoad(Hu3DProjection[tevStage].anim, 0, projectionMapNo + tevStage, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                        BmpPtrBak[projectionMapNo + tevStage] = PTR_INVALID;
                        hiliteMapNo++;
                    }
                }
            } else {
                hiliteMapNo = 3;
            }
            if ((model->attr & HU3D_ATTR_HILITE) || (flags & HSF_MATERIAL_HILITE)) {
                if (!constData->hiliteMap) {
                    if (faceMaterial->flags) {
                        hiliteAnimIdx = (faceMaterial->pass >> 4) & 0xF;
                    } else {
                        hiliteAnimIdx = (object->mesh.matPass >> 4) & 0xF;
                    }
                    HuSprTexLoad(hiliteAnim[hiliteAnimIdx], 0, hiliteMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                } else {
                    HuSprTexLoad(constData->hiliteMap, 0, hiliteMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                }
                BmpPtrBak[hiliteMapNo] = PTR_INVALID;
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
                GXSetArray(GX_VA_POS, object->mesh.vertex->data, 3 * sizeof(float));
                if (vtxMode & 2) {
                    GXSetVtxDesc(GX_VA_NBT, GX_DIRECT);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NBT, GX_NRM_NBT, GX_S16, 8);
                } else {
                    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                    if (model->hsf->cenvNum == 0) {
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 0);
                        GXSetArray(GX_VA_NRM, object->mesh.normal->data, 3);
                    } else {
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                        GXSetArray(GX_VA_NRM, object->mesh.normal->data, 3 * sizeof(float));
                    }
                }
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
                GXSetArray(GX_VA_TEX0, object->mesh.st->data, 2 * sizeof(float));
                if (vtxMode & 4) {
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                    GXSetArray(GX_VA_CLR0, object->mesh.color->data, 4);
                }
                GXSetZCompLoc(0);
            }
            textureIdx = faceMaterial->attrNum;
            for (tevStage = 0; tevStage < faceMaterial->attrNum; tevStage++) {
                currentAttribute = &object->mesh.attribute[faceMaterial->attr[tevStage]];
                currentBitmap = currentAttribute->bitmap;
                if (currentAttribute->animWorkP) {
                    texCol[tevStage].a = 0;
                    currentDrawData = currentAttribute->animWorkP;
                    texAnimData = &Hu3DTexAnimData[currentDrawData->animId];
                    if ((currentDrawData->attr & HU3D_ATTRANIM_ATTR_ANIM2D) && !(texAnimData->attr & HU3D_ANIM_ATTR_NOUSE)) {
                        if (Hu3DAnimSet(hsfDrawObject->model, currentAttribute, (s32) tevStage) != 0) {
                            BmpPtrBak[tevStage] = PTR_INVALID;
                            totalTexCnt++;
                            continue;
                        }
                    } else if (currentDrawData->attr & HU3D_ATTRANIM_ATTR_BMPANIM) {
                        currentBitmap = currentDrawData->bitMapPtr;
                        if (currentBitmap->dataFmt != HSF_BMPFMT_CI_IA8) {
                            LoadTexture(hsfDrawObject->model, currentBitmap, currentAttribute, (s32) tevStage); // or: tevStage | 0x0000?
                        } else {
                            LoadTexture(hsfDrawObject->model, currentDrawData->bitMapPtr, currentAttribute, (s32) tevStage);
                            LoadTexture(hsfDrawObject->model, currentDrawData->bitMapPtr, currentAttribute, textureIdx | HSF_TEXID_TL32);
                            texCol[tevStage].r = (s16) textureIdx;
                            texCol[tevStage].a = 2;
                            textureIdx++;
                        }
                        if (currentBitmap->sizeX * currentBitmap->sizeY * currentBitmap->pixSize > 0x40000) {
                            for (var_r24 = 0; var_r24 < 8; var_r24++) {
                                BmpPtrBak[var_r24] = PTR_INVALID;
                            }
                        } else {
                            BmpPtrBak[tevStage] = PTR_INVALID;
                        }
                        totalTexCnt++;
                        continue;
                    }
                }
                if (BmpPtrBak[tevStage] != currentAttribute) {
                    if (BmpPtrBak[tevStage] != PTR_INVALID && BmpPtrBak[tevStage]->bitmap == currentBitmap && currentAttribute->wrapS == BmpPtrBak[tevStage]->wrapS && currentAttribute->wrapT == BmpPtrBak[tevStage]->wrapT) {
                        if (currentBitmap->dataFmt == HSF_BMPFMT_CI_IA8) {
                            TL32F = 1;
                        }
                        totalTexCacheCnt++;
                    } else {
                        texCol[tevStage].a = 0;
                        if (currentBitmap->dataFmt != HSF_BMPFMT_CI_IA8) {
                            LoadTexture(hsfDrawObject->model, currentBitmap, currentAttribute, (s32) tevStage);
                        } else {
                            LoadTexture(hsfDrawObject->model, currentBitmap, currentAttribute, (s32) tevStage);
                            LoadTexture(hsfDrawObject->model, currentBitmap, currentAttribute, textureIdx | HSF_TEXID_TL32);
                            texCol[tevStage].r = (s16) textureIdx;
                            texCol[tevStage].a = 2;
                            textureIdx++;
                        }
                        if (currentBitmap->sizeX * currentBitmap->sizeY * currentBitmap->pixSize > 0x40000) {
                            for (var_r24 = 0; var_r24 < 8; var_r24++) {
                                BmpPtrBak[var_r24] = PTR_INVALID;
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
                if (model->reflectType != -1) {
                    reflectAnimIdx = model->reflectType;
                } else {
                    reflectAnimIdx = reflectMapNo;
                }
                HuSprTexLoad(reflectAnim[reflectAnimIdx], 0, reflectionMapNo, GX_REPEAT, GX_REPEAT, GX_LINEAR);
                BmpPtrBak[reflectionMapNo] = PTR_INVALID;
            } else {
                shadowMapNo = (s16) textureIdx;
            }
            if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->attr & HU3D_CONST_SHADOW_MAP)) {
                toonMapNo = shadowMapNo + 1;
                SetShadowTex();
                BmpPtrBak[shadowMapNo] = PTR_INVALID;
            } else {
                toonMapNo = shadowMapNo;
            }
            if (model->attr & HU3D_ATTR_TOON_MAP) {
                HuSprTexLoad(toonAnim, 0, toonMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                BmpPtrBak[toonMapNo] = PTR_INVALID;
                projectionMapNo = toonMapNo + 1;
            } else {
                projectionMapNo = toonMapNo;
            }
            if (model->projBit != 0) {
                for (tevStage = 0, var_r24 = 1; tevStage < 4; tevStage++, var_r24 <<= 1) {
                    if (var_r24 & model->projBit) {
                        HuSprTexLoad(Hu3DProjection[tevStage].anim, 0, projectionMapNo + tevStage, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                        BmpPtrBak[projectionMapNo + tevStage] = PTR_INVALID;
                        hiliteMapNo = projectionMapNo + tevStage + 1;
                    }
                }
            } else {
                hiliteMapNo = projectionMapNo;
            }
            if ((model->attr & HU3D_ATTR_HILITE) || (flags & HSF_MATERIAL_HILITE)) {
                if (constData->hiliteMap == 0) {
                    if (faceMaterial->flags != 0) {
                        hiliteAnimIdx = ((faceMaterial->pass >> 4) & 0xF);
                    } else {
                        hiliteAnimIdx = ((object->mesh.matPass >> 4) & 0xF);
                    }
                    HuSprTexLoad(hiliteAnim[hiliteAnimIdx], 0, hiliteMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                } else {
                    HuSprTexLoad(constData->hiliteMap, 0, hiliteMapNo, GX_CLAMP, GX_CLAMP, GX_LINEAR);
                }
                BmpPtrBak[toonMapNo] = PTR_INVALID;
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

static void SetTevStageNoTex(HU3DDRAWOBJ *drawObj, HSFMATERIAL *matP) {
    GXColor color;
    HU3DMODEL *modelP;
    HSFOBJECT *objPtr;
    float hiliteScale;
    s16 j;
    s16 matHiliteF;
    s16 i;
    s16 texMap;
    s16 tevStage;
    s16 lightOnF;
    u32 shading;
    GXChannelID colorChan;
    GXTevAlphaArg alphaSrc;
    u32 alphaLightF;
    u32 flags;
    Mtx mtx;

    tevStage = 1;
    texMap = 0;
    objPtr = drawObj->object;
    modelP = drawObj->model;
    flags = objPtr->flags | matP->flags;
    if (matP->vtxMode == 2 || matP->vtxMode == 3) {
        matHiliteF = TRUE;
        lightOnF = TRUE;
    } else {
        matHiliteF = FALSE;
        if (matP->vtxMode == 0 || matP->vtxMode == 5) {
            lightOnF = FALSE;
        } else {
            lightOnF = TRUE;
        }
    }
    if ((Hu3DObjInfoP->attr & 0x4000) && matP->vtxMode == 5) {
        colorChan = GX_COLOR0A0;
        alphaSrc = GX_CA_RASA;
        alphaLightF = TRUE;
    } else {
        colorChan = GX_COLOR0;
        alphaSrc = GX_CA_KONST;
        alphaLightF = FALSE;
    }
    color.a = 255.0f * (1.0f - matP->invAlpha);
    if (modelP->attr & HU3D_ATTR_TOON_MAP) {
        color.r = matP->color[0];
        color.g = matP->color[1];
        color.b = matP->color[2];
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTexCoordGen2(texMap, GX_TG_SRTG, GX_TG_COLOR0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE0, texMap, toonMapNo, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        texMap++;
    } else {
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, colorChan);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaSrc);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    }
    if (matP->refAlpha != 0.0f) {
        SetReflect(drawObj, tevStage, (s16) texMap, matP->refAlpha * 255.0f);
        tevStage++;
        texMap++;
    }
    if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->attr & HU3D_CONST_SHADOW_MAP)) {
        SetShadow(drawObj, tevStage, (s16) texMap);
        tevStage++;
        texMap++;
    }
    if (matHiliteF != 0) {
        if ((modelP->attr & HU3D_ATTR_HILITE) || (flags & HSF_MATERIAL_HILITE)) {
            GXSetTexCoordGen2(texMap, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX7, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(tevStage, texMap, hiliteMapNo, GX_COLOR0A0);
            GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ONE, GX_CC_TEXC, GX_CC_CPREV);
            GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            hiliteScale = 6.0f * (matP->hiliteScale / 300.0f);
            if (hiliteScale < 0.1) {
                hiliteScale = 0.1f;
            }
            MTXCopy(hiliteMtx, mtx);
            mtxScaleCat(mtx, hiliteScale, hiliteScale, hiliteScale);
            GXLoadTexMtxImm(mtx, GX_TEXMTX7, GX_MTX2x4);
            tevStage++;
            texMap++;
            lightOnF = TRUE;
            matHiliteF = FALSE;
        } else {
            GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR1A1);
            GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            tevStage++;
        }
    } else if (matP->invAlpha != 0.0f) {
        GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ONE, GX_CC_CPREV, GX_CC_ZERO);
        GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
        GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        tevStage++;
    }
    if (modelP->projBit != 0) {
        for (i = 0, j = 1; i < HU3D_PROJ_MAX; i++, j <<= 1) {
            if (j & modelP->projBit) {
                SetProjection(drawObj, tevStage, i, (GXTexMapID) texMap, projectionMapNo + i, texMtxTbl[i + 3]);
                texMap++;
                tevStage += 2;
            }
        }
    }
    FlushKColor();
    GXSetNumTexGens(texMap);
    GXSetNumTevStages(tevStage);
    shading = (matHiliteF != 0) ? 2 : matP->vtxMode;
    if (shading != shadingBak) {
        shadingBak = shading;
        lightBit = Hu3DLightSet(drawObj->model, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, matHiliteF ? matP->hiliteScale : 0.0f);
    }
    if (matHiliteF != 0) {
        GXSetNumChans(2);
        if (matP->vtxMode == 5) {
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR1, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_NONE, GX_AF_SPEC);
            if (alphaLightF) {
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
        if (matP->vtxMode == 5) {
            GXSetChanCtrl(GX_COLOR0, lightOnF, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            if (alphaLightF) {
                GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            } else {
                GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            }
        } else {
            GXSetChanCtrl(GX_COLOR0, lightOnF, GX_SRC_REG, GX_SRC_REG, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
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

static void SetTevStageTex(HU3DDRAWOBJ *drawObj, HSFMATERIAL *matP) {
    GXColor color;
    GXTexMapID bumpTexMap;
    GXTevStageID bumpTevStage;
    s32 texBlendF;
    u32 flags;
    GXChannelID colorChan;
    u32 alphaLightF;
    HSFATTRIBUTE *attrP;
    HSFOBJECT *objPtr;
    HU3DMODEL *modelP;
    HU3DATTRANIM *animWorkP;
    GXTevAlphaArg alphaSrc;
    float hiliteScale;
    u16 kColorId;
    u16 tevTexCoordId;
    u16 j;
    u16 texCoordId;
    u16 tevStage;
    u16 matHiliteF;
    u16 lightOnF;
    u16 i;
    s16 texMapId;
    Mtx mtx;

    kColorId = 0;
    texMapId = -1;
    objPtr = drawObj->object;
    modelP = drawObj->model;
    flags = objPtr->flags | matP->flags;
    if (matP->vtxMode == 2 || matP->vtxMode == 3) {
        matHiliteF = TRUE;
    } else {
        matHiliteF = FALSE;
        if (matP->vtxMode == 0 || matP->vtxMode == 5) {
            lightOnF = GX_FALSE;
        } else {
            lightOnF = GX_TRUE;
        }
    }
    if ((Hu3DObjInfoP->attr & HU3D_CONST_XLUVERTEX) && matP->vtxMode == 5) {
        colorChan = GX_COLOR0A0;
        alphaSrc = GX_CA_RASA;
        alphaLightF = TRUE;
    } else {
        colorChan = GX_COLOR0;
        alphaSrc = GX_CA_KONST;
        alphaLightF = FALSE;
    }
    if (matP->attrNum == 1) {
        texCoordId = tevStage = 1;
        attrP = &objPtr->mesh.attribute[matP->attr[0]];
        if (attrP->scale.x != 1.0f || attrP->scale.y != 1.0f) {
            MTXScale(mtx, 1.0f / attrP->scale.x, 1.0f / attrP->scale.y, 1.0f);
            mtxTransCat(mtx, -attrP->trans.x, -attrP->trans.y, 0.0f);
            GXLoadTexMtxImm(mtx, texMtxTbl[texCoordId], GX_MTX2x4);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[texCoordId]);
        } else if (attrP->trans.x != 0.0f || attrP->trans.y != 0.0f) {
            MTXTrans(mtx, -attrP->trans.x, -attrP->trans.y, 0.0f);
            GXLoadTexMtxImm(mtx, texMtxTbl[texCoordId], GX_MTX2x4);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[texCoordId]);
        } else {
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        }
        if (attrP->unk20 == 1.0f) {
            if (attrP->animWorkP) {
                animWorkP = attrP->animWorkP;
                if (animWorkP->attr & HU3D_ATTRANIM_ATTR_TEXMTX) {
                    GXLoadTexMtxImm(Hu3DTexScrData[animWorkP->texScrId].texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                } else if (animWorkP->attr & HU3D_ATTRANIM_ATTR_ANIM3D) {
                    MTXScale(mtx, 1.0f / animWorkP->scale3D.x, 1.0f / animWorkP->scale3D.y, 1.0f / animWorkP->scale3D.z);
                    mtxRotCat(mtx, animWorkP->rot.x, animWorkP->rot.y, animWorkP->rot.z);
                    mtxTransCat(mtx, -animWorkP->trans3D.x, -animWorkP->trans3D.y, -animWorkP->trans3D.z);
                    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                } else if (animWorkP->attr & HU3D_ATTRANIM_ATTR_ANIM2D) {
                    MTXScale(mtx, animWorkP->scale.x, animWorkP->scale.y, 1.0f);
                    mtxTransCat(mtx, animWorkP->trans.x, animWorkP->trans.y, 0.0f);
                    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
            }
            if (attrP->unk8[2] == 0) {
                GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
                GXSetTevOrder(tevStage, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
                GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                tevStage++;
            } else {
                GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
                if (!(modelP->attr & HU3D_ATTR_TOON_MAP)) {
                    if (texCol[0].a == 1) {
                        color = texCol[0];
                        color.a = 0xFF;
                        SetKColorRGB(GX_TEVSTAGE0, &color);
                        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
                        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, colorChan);
                        GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, alphaSrc, GX_CA_ZERO);
                        GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        tevStage++;
                    } else if (texCol[0].a == 2) {
                        GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
                        GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
                        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
                        SetKColorRGB(GX_TEVSTAGE0, &firstTev);
                        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
                        GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP2);
                        SetKColorRGB(tevStage, &secondTev);
                        GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_CPREV);
                        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
                        GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevOrder(tevStage, GX_TEXCOORD0, texCol->r, GX_COLOR_NULL);
                        tevStage++;
                    } else {
                        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, alphaSrc, GX_CA_ZERO);
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
        if (modelP->attr & HU3D_ATTR_TOON_MAP) {
            GXSetTexCoordGen2(texCoordId, GX_TG_SRTG, GX_TG_COLOR0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(tevStage, texCoordId, toonMapNo, GX_COLOR0A0);
            GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_KONST, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            texCoordId++;
            tevStage++;
        }
        color.a = 255.0f * (1.0f - matP->invAlpha);
        GXSetTevColor(GX_TEVREG0, color);
        if (matP->refAlpha != 0.0f) {
            SetReflect(drawObj, tevStage, (u16) texCoordId, 255.0f * matP->refAlpha);
            texCoordId++;
            tevStage++;
        }
        if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->attr & 8)) {
            SetShadow(drawObj, tevStage, (u16) texCoordId);
            texCoordId++;
            tevStage++;
        }
        if (matHiliteF != 0) {
            if ((modelP->attr & HU3D_ATTR_HILITE) || (flags & 0x100)) {
                GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX7, GX_FALSE, GX_PTIDENTITY);
                GXSetTevOrder(tevStage, texCoordId, hiliteMapNo, GX_COLOR0A0);
                GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_CPREV);
                GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                hiliteScale = 6.0f * (matP->hiliteScale / 300.0f);
                if (hiliteScale < 0.1) {
                    hiliteScale = 0.1f;
                }
                MTXCopy(hiliteMtx, mtx);
                mtxScaleCat(mtx, hiliteScale, hiliteScale, hiliteScale);
                GXLoadTexMtxImm(mtx, GX_TEXMTX7, GX_MTX2x4);
                tevStage++;
                texCoordId++;
                matHiliteF = 0;
                lightOnF = 1;
            } else {
                if (attrP->unk20 == 1.0f) {
                    GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR1A1);
                    GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
                } else {
                    GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(tevStage, texCoordId, GX_TEXMAP0, GX_COLOR1A1);
                    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_CPREV);
                    texCoordId++;
                }
                GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                tevStage++;
            }
        } else if (matP->invAlpha != 0.0f) {
            GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            tevStage++;
        }
        if (modelP->projBit != 0) {
            for (i = 0, j = 1; i < HU3D_PROJ_MAX; i++, j <<= 1) {
                if (j & modelP->projBit) {
                    SetProjection(drawObj, tevStage, i, (u16) texCoordId, projectionMapNo + i, texMtxTbl[i + 3]);
                    texCoordId++;
                    tevStage += 2;
                }
            }
        }
    } else {
        texBlendF = FALSE;
        texCoordId = 0;
        bumpTexMap = -1;
        for (i = tevStage = 0; i < matP->attrNum; i++) {
            attrP = &objPtr->mesh.attribute[matP->attr[i]];
            if (attrP->nbtTpLvl != 0.0f) {
                GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_BUMP0, GX_TG_TEXCOORD0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                SetKColor(tevStage, attrP->nbtTpLvl * 10.0f);
                GXSetTevOrder(tevStage, texCoordId, i, GX_COLOR0A0);
                GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_RASC);
                GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                tevStage++;
                bumpTexMap = i;
                bumpTevStage = tevStage;
                GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_CPREV);
                GXSetTevColorOp(tevStage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                texCoordId++;
                texBlendF = TRUE;
            } else if (attrP->unk20 != 1.0f) {
                texMapId = i;
                continue;
            } else {
                if (attrP->animWorkP) {
                    animWorkP = attrP->animWorkP;
                    if (animWorkP->attr & HU3D_ATTRANIM_ATTR_TEXMTX) {
                        GXLoadTexMtxImm(Hu3DTexScrData[animWorkP->texScrId].texMtx, texMtxTbl[texCoordId], GX_MTX2x4);
                        GXSetTexCoordGen(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[texCoordId]);
                        tevTexCoordId = (u16) texCoordId;
                        texCoordId++;
                    } else if (animWorkP->attr & HU3D_ATTRANIM_ATTR_ANIM3D) {
                        MTXScale(mtx, 1.0f / animWorkP->scale3D.x, 1.0f / animWorkP->scale3D.y, 1.0f / animWorkP->scale3D.z);
                        mtxRotCat(mtx, animWorkP->rot.x, animWorkP->rot.y, animWorkP->rot.z);
                        mtxTransCat(mtx, -animWorkP->trans3D.x, -animWorkP->trans3D.y, -animWorkP->trans3D.z);
                        GXLoadTexMtxImm(mtx, texMtxTbl[texCoordId], GX_MTX2x4);
                        GXSetTexCoordGen(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[texCoordId]);
                        tevTexCoordId = (u16) texCoordId;
                        texCoordId++;
                    } else if (animWorkP->attr & HU3D_ATTRANIM_ATTR_ANIM2D) {
                        MTXScale(mtx, animWorkP->scale.x, animWorkP->scale.y, 1.0f);
                        mtxTransCat(mtx, animWorkP->trans.x, animWorkP->trans.y, 0.0f);
                        GXLoadTexMtxImm(mtx, texMtxTbl[texCoordId], GX_MTX2x4);
                        GXSetTexCoordGen(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[texCoordId]);
                        tevTexCoordId = (u16) texCoordId;
                        texCoordId++;
                    } else {
                        GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                        tevTexCoordId = (u16) texCoordId;
                        texCoordId++;
                    }
                } else {
                    if (attrP->scale.x != 1.0f || attrP->scale.y != 1.0f) {
                        MTXScale(mtx, 1.0f / attrP->scale.x, 1.0f / attrP->scale.y, 1.0f);
                        mtxTransCat(mtx, -attrP->trans.x, -attrP->trans.y, 0.0f);
                        GXLoadTexMtxImm(mtx, texMtxTbl[texCoordId], GX_MTX2x4);
                        GXSetTexCoordGen(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[texCoordId]);
                    } else if (attrP->trans.x != 0.0f || attrP->trans.y != 0.0f) {
                        MTXTrans(mtx, -attrP->trans.x, -attrP->trans.y, 0.0f);
                        GXLoadTexMtxImm(mtx, texMtxTbl[texCoordId], GX_MTX2x4);
                        GXSetTexCoordGen(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, texMtxTbl[texCoordId]);
                    } else {
                        GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                    }
                    tevTexCoordId = (u16) texCoordId;
                    texCoordId++;
                }
                GXSetTevOrder(tevStage, tevTexCoordId, i, GX_COLOR0A0);
                if (i == 0) {
                    if (texCol[i].a == 1) {
                        color = texCol[i];
                        color.a = 0xFF;
                        kColorId = SetKColorRGB(GX_TEVSTAGE0, &color);
                        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        tevStage++;
                        GXSetTevKColorSel(tevStage, kColorId);
                        GXSetTevOrder(tevStage, tevTexCoordId, i, colorChan);
                        GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
                    } else if (texCol[i].a == 2) {
                        GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
                        GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
                        GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
                        SetKColorRGB(tevStage, &firstTev);
                        GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                        GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
                        GXSetTevOrder(tevStage, GX_TEXCOORD0, i, GX_COLOR_NULL);
                        tevStage++;
                        GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP2);
                        SetKColorRGB(tevStage, &secondTev);
                        GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_C2);
                        GXSetTevAlphaIn(tevStage, GX_CA_APREV, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
                        GXSetTevOrder(tevStage, GX_TEXCOORD0, texCol->r, GX_COLOR_NULL);
                    } else {
                        GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_TEXA, alphaSrc, GX_CA_ZERO);
                    }
                } else if (texBlendF) {
                    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
                    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                    texBlendF = 0;
                } else if (attrP->unk8[2] == 0) {
                    if (attrP->kColor != 1.0f) {
                        color.a = attrP->kColor * 255.0f;
                        SetKColorRGB(tevStage, &color);
                        GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_ZERO);
                        GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        tevStage++;
                        GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
                        GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_C2, GX_CC_A2, GX_CC_ZERO);
                        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    } else {
                        GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                        GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                        tevStage++;
                        GXSetTevOrder(tevStage, tevTexCoordId, i, GX_COLOR0A0);
                        GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_C2, GX_CC_TEXA, GX_CC_ZERO);
                        GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    }
                } else if (texCol[i].a == 1) {
                    color = texCol[i];
                    color.a = 0xFF;
                    SetKColorRGB(tevStage, &color);
                    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_KONST, GX_CA_APREV, GX_CA_ZERO);
                    GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                    tevStage++;
                    GXSetTevOrder(tevStage, tevTexCoordId, i, GX_COLOR0A0);
                    SetKColor(tevStage, attrP->kColor * 255.0f);
                    GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_C2, GX_CC_KONST, GX_CC_ZERO);
                    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                } else if (texCol[i].a == 2) {
                    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
                    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
                    GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
                    SetKColorRGB(tevStage, &firstTev);
                    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
                    GXSetTevOrder(tevStage, GX_TEXCOORD0, i, GX_COLOR_NULL);
                    tevStage++;
                    GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP2);
                    SetKColorRGB(tevStage, &secondTev);
                    GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_C2);
                    GXSetTevAlphaIn(tevStage, GX_CA_APREV, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
                    GXSetTevOrder(tevStage, GX_TEXCOORD0, texCol->r, GX_COLOR_NULL);
                } else {
                    SetKColor(tevStage, attrP->kColor * 255.0f);
                    GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                }
                GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }
            tevStage++;
        }
        if (modelP->attr & HU3D_ATTR_TOON_MAP) {
            GXSetTexCoordGen2(texCoordId, GX_TG_SRTG, GX_TG_COLOR0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(tevStage, texCoordId, toonMapNo, GX_COLOR0A0);
            GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_KONST, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            texCoordId++;
            tevStage++;
        }
        if (matP->refAlpha != 0.0f) {
            if (texMapId != -1) {
                SetKColor(tevStage, matP->refAlpha * 255.0f);
                GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                GXSetTevOrder(tevStage, texCoordId, texMapId, GX_COLOR0A0);
                GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
                tevStage++;
                texCoordId++;
                GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX8, GX_FALSE, GX_PTIDENTITY);
                GXSetTevOrder(tevStage, texCoordId, reflectionMapNo, GX_COLOR0A0);
                GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C2, GX_CC_ZERO);
                GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            } else {
                SetKColor(tevStage, matP->refAlpha * 255.0f);
                GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX8, GX_FALSE, GX_PTIDENTITY);
                GXSetTevOrder(tevStage, texCoordId, reflectionMapNo, GX_COLOR0A0);
                GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
                GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            }
            MTXScale(mtx, 1.0f / drawObj->scale.x, 1.0f / drawObj->scale.y, 1.0f / drawObj->scale.z);
            MTXConcat(drawObj->matrix, mtx, mtx);
            mtx[0][3] = mtx[1][3] = mtx[2][3] = 0.0f;
            MTXConcat(mtx, Hu3DCameraMtxXPose, mtx);
            MTXConcat(refMtx, mtx, mtx);
            GXLoadTexMtxImm(mtx, 0x36, GX_MTX2x4);
            tevStage++;
            texCoordId++;
        }
        if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->attr & HU3D_CONST_SHADOW_MAP)) {
            SetShadow(drawObj, tevStage, (u16) texCoordId);
            texCoordId++;
            tevStage++;
        }
        color.a = (1.0f - matP->invAlpha) * 255.0f;
        GXSetTevColor(GX_TEVREG0, color);
        if (matHiliteF != 0) {
            if ((modelP->attr & HU3D_ATTR_HILITE) || (flags & HSF_MATERIAL_HILITE)) {
                hiliteScale = (matP->hiliteScale / 300.0f) * 6.0f;
                if (hiliteScale < 0.1) {
                    hiliteScale = 0.1f;
                }
                MTXCopy(hiliteMtx, mtx);
                mtxScaleCat(mtx, hiliteScale, hiliteScale, hiliteScale);
                GXLoadTexMtxImm(mtx, 0x33, GX_MTX2x4);
                if (texMapId == -1) {
                    GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX7, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(tevStage, texCoordId, hiliteMapNo, GX_COLOR0A0);
                    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_CPREV);
                    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
                    GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                } else {
                    GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(tevStage, texCoordId, texMapId, GX_COLOR0A0);
                    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
                    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
                    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                    GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG0);
                    tevStage++;
                    texCoordId++;
                    GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX7, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(tevStage, texCoordId, hiliteMapNo, GX_COLOR0A0);
                    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_CPREV);
                    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                }
                tevStage++;
                texCoordId++;
                matHiliteF = FALSE;
                lightOnF = GX_TRUE;
            } else {
                if (texMapId == -1) {
                    GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR1A1);
                    GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
                } else {
                    GXSetTexCoordGen2(texCoordId, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                    GXSetTevOrder(tevStage, texCoordId, texMapId, GX_COLOR1A1);
                    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_CPREV);
                    texCoordId++;
                }
                GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
                GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                tevStage++;
            }
        } else if (matP->invAlpha != 0.0f) {
            GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            tevStage++;
        }
        if (modelP->projBit != 0) {
            for (i = 0, j = 1; i < HU3D_PROJ_MAX; i++, j <<= 1) {
                if (j & modelP->projBit) {
                    SetProjection(drawObj, tevStage, i, (u16) texCoordId, projectionMapNo + i, texMtxTbl[i + 3]);
                    texCoordId++;
                    tevStage += 2;
                }
            }
        }
        if (bumpTexMap != -1) {
            GXSetTexCoordGen2(texCoordId, GX_TG_BUMP0, GX_TG_TEXCOORD0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(bumpTevStage, texCoordId, bumpTexMap, GX_COLOR0A0);
            texCoordId++;
        }
    }
    FlushKColor();
    GXSetNumTexGens(texCoordId);
    GXSetNumTevStages(tevStage);
    if (matP->vtxMode != shadingBak) {
        shadingBak = matP->vtxMode;
        lightBit = Hu3DLightSet(drawObj->model, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, (matHiliteF) ? matP->hiliteScale : 0.0f);
    }
    if (matHiliteF != 0) {
        GXSetNumChans(2);
        if (matP->vtxMode == 5) {
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_COLOR1, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_NONE, GX_AF_SPEC);
            if (alphaLightF != 0) {
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
        if (matP->vtxMode == 5) {
            GXSetChanCtrl(GX_COLOR0, lightOnF, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            if (alphaLightF != 0) {
                GXSetChanCtrl(GX_ALPHA0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
            } else {
                GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, lightBit, GX_DF_CLAMP, GX_AF_NONE);
            }
        } else {
            GXSetChanCtrl(GX_COLOR0, lightOnF, GX_SRC_REG, GX_SRC_REG, lightBit, GX_DF_CLAMP, GX_AF_SPOT);
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

static GXTevKColorSel SetKColor(GXTevStageID tevStage, u8 color) {
    GXTevKColorSel kColorSel;

    switch (kColorIdx % 3) {
        case 0:
            kColor.r = color;
            break;
        case 1:
            kColor.g = color;
            break;
        case 2:
            kColor.b = color;
            kColor.a = 0xFF;
            GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
            break;
    }
    kColorSel = kColorSelTbl[kColorIdx];
    GXSetTevKColorSel(tevStage, kColorSel);
    GXSetTevKAlphaSel(tevStage, kColorSelATbl[kColorIdx / 3]);
    kColorIdx++;
    if (kColorIdx > 12) {
        kColorIdx = 11;
    }
    return kColorSel;
}

static GXTevKColorSel SetKColorRGB(GXTevStageID tevStage, GXColor *color) {
    GXTevKColorSel kColorSel;

    GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
    kColorIdx = ((kColorIdx / 3) + 1) * 3;
    GXSetTevKColor(kColorTbl[kColorIdx / 3], *color);
    kColorSel = kColorSelTbl2[kColorIdx / 3];
    GXSetTevKColorSel(tevStage, kColorSel);
    GXSetTevKAlphaSel(tevStage, kColorSelATbl[kColorIdx / 3]);
    kColorIdx += 3;
    if (kColorIdx > 12) {
        kColorIdx = 11;
    }
    return kColorSel;
}

static void FlushKColor(void) {
    kColor.a = 0xFF;
    if (kColorIdx % 3 != 0) {
        GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
    }
}

static void SetReflect(HU3DDRAWOBJ *drawObj, s16 tevStage, s16 texCoord, u8 color) {
    GXTevKColorSel kColorSel;
    Mtx sp3C;
    Mtx spC;

    switch (kColorIdx % 3) {
        case 0:
            kColor.r = color;
            break;
        case 1:
            kColor.g = color;
            break;
        case 2:
            kColor.b = color;
            kColor.a = 0xFF;
            GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
            break;
    }
    kColorSel = kColorSelTbl[kColorIdx];
    GXSetTevKColorSel(tevStage, kColorSel);
    GXSetTevKAlphaSel(tevStage, kColorSelATbl[kColorIdx / 3]);
    kColorIdx++;
    if (kColorIdx > 12) {
        kColorIdx = 11;
    }
    GXSetTexCoordGen2(texCoord, GX_TG_MTX2x4, GX_TG_NRM, GX_TEXMTX8, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(tevStage, texCoord, reflectionMapNo, GX_COLOR0A0);
    GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_KONST, GX_CC_ZERO);
    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    MTXScale(sp3C, 1.0f / drawObj->scale.x, 1.0f / drawObj->scale.y, 1.0f / drawObj->scale.z);
    MTXConcat(drawObj->matrix, sp3C, spC);
    spC[0][3] = spC[1][3] = spC[2][3] = 0.0f;
    MTXConcat(spC, Hu3DCameraMtxXPose, sp3C);
    MTXConcat(refMtx, sp3C, spC);
    GXLoadTexMtxImm(spC, GX_TEXMTX8, GX_MTX2x4);
}

static void SetProjection(HU3DDRAWOBJ *drawObj, s16 tevStage, s16 projNo, s16 texCoord, GXTexMapID texMap, u32 texMtx) {
    GXTevKColorSel kColorSel;
    u8 color;

    GXSetTexCoordGen2(texCoord, GX_TG_MTX3x4, GX_TG_POS, texMtx, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(tevStage, texCoord, texMap, GX_COLOR0A0);
    color = Hu3DProjection[projNo].alpha;
    switch (kColorIdx % 3) {
        case 0:
            kColor.r = color;
            break;
        case 1:
            kColor.g = color;
            break;
        case 2:
            kColor.b = color;
            kColor.a = 0xFF;
            GXSetTevKColor(kColorTbl[kColorIdx / 3], kColor);
            break;
    }
    kColorSel = kColorSelTbl[kColorIdx];
    GXSetTevKColorSel(tevStage, kColorSel);
    GXSetTevKAlphaSel(tevStage, kColorSelATbl[kColorIdx / 3]);
    kColorIdx++;
    if (kColorIdx > 12) {
        kColorIdx = 11;
    }
    GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXA, GX_CC_KONST, GX_CC_ZERO);
    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
    tevStage++;
    GXSetTevOrder(tevStage, texCoord, texMap, GX_COLOR0A0);
    GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C2, GX_CC_ZERO);
    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
}

static void SetShadowTex(void) {
    GXTexObj texObj;

    GXInitTexObj(&texObj, Hu3DShadowData.buf, Hu3DShadowData.size, Hu3DShadowData.size, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, shadowMapNo);
}

static void SetShadow(HU3DDRAWOBJ *drawObj, s16 tevStage, s16 texCoord) {
    GXSetTexCoordGen2(texCoord, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX9, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(tevStage, texCoord, shadowMapNo, GX_COLOR0A0);
    GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
}

static void FaceDrawShadow(HU3DDRAWOBJ *drawObj, HSFFACE *face) {
    HSFOBJECT *objPtr;
    HU3DMODEL *modelP;
    HSFCONSTDATA *constDataP;
    HSFMATERIAL *matP;
    void *list;
    GXColor color;
    s16 vtxMode;

    objPtr = drawObj->object;
    modelP = drawObj->model;
    constDataP = objPtr->constData;
    matP = &objPtr->mesh.material[face->mat & 0xFFF];
    if (matP != materialBak) {
        if (!(constDataP->attr & HU3D_CONST_SHADOW)) {
            drawCnt++;
            return;
        }
        materialBak = matP;
        color.a = 255.0f * (1.0f - matP->invAlpha);
        GXSetTevColor(GX_TEVREG0, color);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        if (matP->attrNum == 0) {
            vtxMode = (objPtr->mesh.color) ? 4 : 0;
            if (vtxMode != vtxModeBak) {
                vtxModeBak = vtxMode;
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, objPtr->mesh.vertex->data, 3 * sizeof(float));
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                if (modelP->hsf->cenvNum == 0) {
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 0);
                    GXSetArray(GX_VA_NRM, objPtr->mesh.normal->data, 3);
                } else {
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                    GXSetArray(GX_VA_NRM, objPtr->mesh.normal->data, 3 * sizeof(float));
                }
                if (vtxMode & 4) {
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                    GXSetArray(GX_VA_CLR0, objPtr->mesh.color->data, 4);
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
            vtxMode = (matP->vtxMode == 5) ? 5 : 1;
            if (DrawData[drawCnt].flags & 2) {
                vtxMode |= 2;
            }
            if (vtxMode != vtxModeBak) {
                vtxModeBak = vtxMode;
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, objPtr->mesh.vertex->data, 3 * sizeof(float));
                if (vtxMode & 2) {
                    GXSetVtxDesc(GX_VA_NBT, GX_DIRECT);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NBT, GX_NRM_NBT, GX_S16, 8);
                } else {
                    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                    if (modelP->hsf->cenvNum == 0) {
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_RGB8, 0);
                        GXSetArray(GX_VA_NRM, objPtr->mesh.normal->data, 3);
                    } else {
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                        GXSetArray(GX_VA_NRM, objPtr->mesh.normal->data, 3 * sizeof(float));
                    }
                }
                GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
                GXSetArray(GX_VA_TEX0, objPtr->mesh.st->data, 2 * sizeof(float));
                if (vtxMode & 4) {
                    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                    GXSetArray(GX_VA_CLR0, objPtr->mesh.color->data, 4);
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
        list = (u8*) DLBufStartP + DrawData[drawCnt].dlOfs;
        GXCallDisplayList(list, DrawData[drawCnt].dlSize);
    } else {
        if (!(constDataP->attr & HU3D_CONST_SHADOW)) {
            drawCnt++;
            return;
        }
        list = (u8*) DLBufStartP + DrawData[drawCnt].dlOfs;
        GXCallDisplayList(list, DrawData[drawCnt].dlSize);
    }
    drawCnt++;
}

static void LoadTexture(HU3DMODEL *modelP, HSFBITMAP *bmpPtr, HSFATTRIBUTE *attrP, s16 texId) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    s16 sizeX;
    s16 sizeY;
    s16 wrapX;
    s16 wrapT;
    s32 mipmap;
    s16 var_r30;

    if (bmpPtr == 0) {
        OSReport("Error: No Texture\n");
        return;
    }
    sizeX = bmpPtr->sizeX;
    sizeY = bmpPtr->sizeY;
    wrapX = (attrP->wrapS == TRUE) ? GX_REPEAT : GX_CLAMP;
    wrapT = (attrP->wrapT == TRUE) ? GX_REPEAT : GX_CLAMP;
    mipmap = (attrP->flag & HSF_FLAG_MIPMAP) ? GX_TRUE : GX_FALSE;
    switch (bmpPtr->dataFmt) {
        case HSF_BMPFMT_RGBA8:
            GXInitTexObj(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_RGBA8, wrapX, wrapT, mipmap);
            break;
        case HSF_BMPFMT_RGB565:
            GXInitTexObj(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_RGB565, wrapX, wrapT, mipmap);
            break;
        case HSF_BMPFMT_RGB5A3:
            GXInitTexObj(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_RGB5A3, wrapX, wrapT, mipmap);
            break;
        case HSF_BMPFMT_CI_RGB565:
            if (bmpPtr->pixSize < 8) {
                GXInitTlutObj(&tlutObj, bmpPtr->palData, GX_TL_RGB565, bmpPtr->palSize);
                GXLoadTlut(&tlutObj, texId);
                GXInitTexObjCI(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_C4, wrapX, wrapT, mipmap, texId);
            } else {
                GXInitTlutObj(&tlutObj, bmpPtr->palData, GX_TL_RGB565, bmpPtr->palSize);
                GXLoadTlut(&tlutObj, texId);
                GXInitTexObjCI(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_C8, wrapX, wrapT, mipmap, texId);
            }
            break;
        case HSF_BMPFMT_CI_RGB5A3:
            if (bmpPtr->pixSize < 8) {
                GXInitTlutObj(&tlutObj, bmpPtr->palData, GX_TL_RGB5A3, bmpPtr->palSize);
                GXLoadTlut(&tlutObj, texId);
                GXInitTexObjCI(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_C4, wrapX, wrapT, mipmap, texId);
            } else {
                GXInitTlutObj(&tlutObj, bmpPtr->palData, GX_TL_RGB5A3, bmpPtr->palSize);
                GXLoadTlut(&tlutObj, texId);
                GXInitTexObjCI(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_C8, wrapX, wrapT, mipmap, texId);
            }
            break;
        case HSF_BMPFMT_I4:
            var_r30 = (s16) texId;
            texCol[var_r30].r = bmpPtr->tint.r;
            texCol[var_r30].g = bmpPtr->tint.g;
            texCol[var_r30].b = bmpPtr->tint.b;
            texCol[var_r30].a = 1;
            GXInitTexObj(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_I4, wrapX, wrapT, mipmap);
            break;
        case HSF_BMPFMT_I8:
            var_r30 = (s16) texId;
            texCol[var_r30].r = bmpPtr->tint.r;
            texCol[var_r30].g = bmpPtr->tint.g;
            texCol[var_r30].b = bmpPtr->tint.b;
            texCol[var_r30].a = 1;
            GXInitTexObj(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_I8, wrapX, wrapT, mipmap);
            break;
        case HSF_BMPFMT_IA4:
            var_r30 = (s16) texId;
            texCol[var_r30].r = bmpPtr->tint.r;
            texCol[var_r30].g = bmpPtr->tint.g;
            texCol[var_r30].b = bmpPtr->tint.b;
            texCol[var_r30].a = 1;
            GXInitTexObj(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_IA4, wrapX, wrapT, mipmap);
            break;
        case HSF_BMPFMT_IA8:
            var_r30 = (s16) texId;
            texCol[var_r30].r = bmpPtr->tint.r;
            texCol[var_r30].g = bmpPtr->tint.g;
            texCol[var_r30].b = bmpPtr->tint.b;
            texCol[var_r30].a = 1;
            GXInitTexObj(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_IA8, wrapX, wrapT, mipmap);
            break;
        case HSF_BMPFMT_CMPR:
            GXInitTexObj(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_CMPR, wrapX, wrapT, mipmap);
            break;
        case HSF_BMPFMT_CI_IA8:
            if (texId & HSF_TEXID_TL32) {
                GXInitTlutObj(&tlutObj, &((s16*) bmpPtr->palData)[(bmpPtr->palSize + 0xF) & 0xFFF0], GX_TL_IA8, bmpPtr->palSize);
            } else {
                GXInitTlutObj(&tlutObj, bmpPtr->palData, GX_TL_IA8, bmpPtr->palSize);
            }
            texId &= 0x7FFF;
            if (bmpPtr->pixSize < 8) {
                GXLoadTlut(&tlutObj, texId);
                GXInitTexObjCI(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_C4, wrapX, wrapT, mipmap, texId);
            } else {
                GXLoadTlut(&tlutObj, texId);
                GXInitTexObjCI(&texObj, bmpPtr->data, sizeX, sizeY, GX_TF_C8, wrapX, wrapT, mipmap, texId);
            }
            TL32F = TRUE;
            break;
    }
    if ((modelP->attr & HU3D_ATTR_TEX_NEAR) || (attrP->flag & HSF_FLAG_NEAR)) {
        GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    } else if (mipmap) {
        GXInitTexObjLOD(&texObj, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, attrP->maxLod, 0.0f, GX_FALSE, GX_TRUE, GX_ANISO_2);
    } else if (bmpPtr->maxLod == 0) {
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    } else {
        GXInitTexObjLOD(&texObj, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, bmpPtr->maxLod - 1, 0.0f, GX_TRUE, GX_TRUE, GX_ANISO_1);
    }
    GXLoadTexObj(&texObj, texId);
}

static void objNull(HU3DMODEL *modelP, HSFOBJECT *objPtr) {
    HSFTRANSFORM *transformP;
    HuVecF *prevScale;
    HuVecF *scale;
    s16 applyF;
    s16 i;
    Mtx mtx;

    if (CancelTRXF == FALSE) {
        if (attachMotionF == FALSE) {
            transformP = &objPtr->mesh.base;
        } else {
            transformP = &objPtr->mesh.curr;
        }
        if (modelP->hsf->cenvNum == 0 || hookIdx != HU3D_MODELID_NONE) {
            MTXScale(mtx, transformP->scale.x, transformP->scale.y, transformP->scale.z);
            mtxRotCat(mtx, transformP->rot.x, transformP->rot.y, transformP->rot.z);
            mtxTransCat(mtx, transformP->pos.x, transformP->pos.y, transformP->pos.z);
            MTXConcat(MTXBuf[MTXIdx - 1], mtx, MTXBuf[MTXIdx]);
        }
        scale = &scaleBuf[MTXIdx];
        prevScale = scale - 1;
        scale->x = prevScale->x * transformP->scale.x;
        scale->y = prevScale->y * transformP->scale.y;
        scale->z = prevScale->z * transformP->scale.z;
        MTXIdx++;
        applyF = TRUE;
    } else {
        CancelTRXF = FALSE;
        applyF = FALSE;
    }
    for (i = 0; i < objPtr->mesh.childrenCount; i++) {
        objCall(modelP, objPtr->mesh.children[i]);
    }
    if (applyF != 0) {
        MTXIdx--;
    }
}

static void objRoot(HU3DMODEL *modelP, HSFOBJECT *objPtr) {
    HSFTRANSFORM *transformP;
    HuVecF *prevScale;
    HuVecF *scale;
    s16 applyF;
    s16 i;
    Mtx mtx;

    if (CancelTRXF == FALSE) {
        if (attachMotionF == FALSE) {
            transformP = &objPtr->mesh.base;
        } else {
            transformP = &objPtr->mesh.curr;
        }
        if (modelP->hsf->cenvNum == 0 || hookIdx != HU3D_MODELID_NONE) {
            MTXScale(mtx, transformP->scale.x, transformP->scale.y, transformP->scale.z);
            mtxRotCat(mtx, transformP->rot.x, transformP->rot.y, transformP->rot.z);
            mtxTransCat(mtx, transformP->pos.x, transformP->pos.y, transformP->pos.z);
            MTXConcat(MTXBuf[MTXIdx - 1], mtx, MTXBuf[MTXIdx]);
        }
        scale = &scaleBuf[MTXIdx];
        prevScale = scale - 1;
        scale->x = prevScale->x * transformP->scale.x;
        scale->y = prevScale->y * transformP->scale.y;
        scale->z = prevScale->z * transformP->scale.z;
        MTXIdx++;
        applyF = TRUE;
    } else {
        CancelTRXF = FALSE;
        applyF = FALSE;
    }
    for (i = 0; i < objPtr->mesh.childrenCount; i++) {
        objCall(modelP, objPtr->mesh.children[i]);
    }
    if (applyF != 0) {
        MTXIdx--;
    }
}

static void objJoint(HU3DMODEL *modelP, HSFOBJECT *objPtr) {
    HSFTRANSFORM *transformP;
    HuVecF *prevScale;
    HuVecF *scale;
    s16 applyF;
    s16 i;
    Mtx mtx;

    if (CancelTRXF == FALSE) {
        if (attachMotionF == FALSE) {
            transformP = &objPtr->mesh.base;
        } else {
            transformP = &objPtr->mesh.curr;
        }
        if (modelP->hsf->cenvNum == 0 || hookIdx != HU3D_MODELID_NONE) {
            MTXScale(mtx, transformP->scale.x, transformP->scale.y, transformP->scale.z);
            mtxRotCat(mtx, transformP->rot.x, transformP->rot.y, transformP->rot.z);
            mtxTransCat(mtx, transformP->pos.x, transformP->pos.y, transformP->pos.z);
            MTXConcat(MTXBuf[MTXIdx - 1], mtx, MTXBuf[MTXIdx]);
        }
        scale = &scaleBuf[MTXIdx];
        prevScale = scale - 1;
        scale->x = prevScale->x * transformP->scale.x;
        scale->y = prevScale->y * transformP->scale.y;
        scale->z = prevScale->z * transformP->scale.z;
        MTXIdx++;
        applyF = TRUE;
    } else {
        CancelTRXF = FALSE;
        applyF = FALSE;
    }
    for (i = 0; i < objPtr->mesh.childrenCount; i++) {
        objCall(modelP, objPtr->mesh.children[i]);
    }
    if (applyF) {
        MTXIdx--;
    }
}

static void objMap(HU3DMODEL *modelP, HSFOBJECT *objPtr) {
    HSFTRANSFORM *transformP;
    HuVecF *prevScale;
    HuVecF *scale;
    s16 applyF;
    s16 i;
    Mtx mtx;

    if (CancelTRXF == 0) {
        if (attachMotionF == 0) {
            transformP = &objPtr->mesh.base;
        } else {
            transformP = &objPtr->mesh.curr;
        }
        MTXScale(mtx, transformP->scale.x, transformP->scale.y, transformP->scale.z);
        mtxRotCat(mtx, transformP->rot.x, transformP->rot.y, transformP->rot.z);
        mtxTransCat(mtx, transformP->pos.x, transformP->pos.y, transformP->pos.z);
        MTXConcat(MTXBuf[MTXIdx - 1], mtx, MTXBuf[MTXIdx]);
        scale = &scaleBuf[MTXIdx];
        prevScale = scale - 1;
        scale->x = prevScale->x * transformP->scale.x;
        scale->y = prevScale->y * transformP->scale.y;
        scale->z = prevScale->z * transformP->scale.z;
        MTXIdx++;
        applyF = TRUE;
    } else {
        CancelTRXF = FALSE;
        applyF = FALSE;
    }
    for (i = 0; i < objPtr->mesh.childrenCount; i++) {
        objCall(modelP, objPtr->mesh.children[i]);
    }
    if (applyF) {
        MTXIdx--;
    }
}

static void objReplica(HU3DMODEL *modelP, HSFOBJECT *objPtr) {
    HSFTRANSFORM *transformP;
    Mtx mtx;
    Mtx rot;

    if (attachMotionF == 0) {
        transformP = &objPtr->mesh.base;
    } else {
        transformP = &objPtr->mesh.curr;
    }
    mtxRot(rot, transformP->rot.x, transformP->rot.y, transformP->rot.z);
    MTXScale(mtx, transformP->scale.x, transformP->scale.y, transformP->scale.z);
    MTXConcat(rot, mtx, mtx);
    mtxTransCat(mtx, transformP->pos.x, transformP->pos.y, transformP->pos.z);
    MTXConcat(MTXBuf[MTXIdx - 1], mtx, MTXBuf[MTXIdx]);
    scaleBuf[MTXIdx].x = transformP->scale.x * scaleBuf[MTXIdx - 1].x;
    scaleBuf[MTXIdx].y = transformP->scale.y * scaleBuf[MTXIdx - 1].y;
    scaleBuf[MTXIdx].z = transformP->scale.z * scaleBuf[MTXIdx - 1].z;
    MTXIdx++;
    CancelTRXF = TRUE;
    objCall(modelP, objPtr->mesh.replica);
    CancelTRXF = FALSE;
    MTXIdx--;
}

void Hu3DDrawPost(void) {
    Vec axis;
    Vec cross;
    Vec halfAngle;
    Vec dir;
    GXColor color;
    HU3DMODELHOOK hookFunc;
    s16 spA;
    s16 similar;
    HSFBUFFER *faceBuf;
    HU3DDRAWOBJ *drawObj;
    s16 projBit;
    s16 temp;
    s16 invF;
    s16 drawObjNo;
    s16 drawObjNextNo;
    s16 j;
    s16 i;
    float z;
    float dot;
    float cosDot;
    HU3DLIGHT *lightP;
    HSFFACE *facePtr;
    Mtx shadowCam;
    Mtx mtx;
    Mtx invCamera;
    Mtx mtx2;
    Mtx sp90;
    Mtx scale;

    spA = 0;
    if (DrawObjIdx != 0) {
        for (i = 0; i < DrawObjIdx; i++) {
            DrawObjNum[i] = i;
        }
        if (shadowModelDrawF == 0) {
            drawObjNextNo = 1;
            while (drawObjNextNo <= DrawObjIdx) {
                drawObjNextNo = drawObjNextNo * 3 + 1;
            }
            while ((drawObjNextNo /= 3) >= 1) {
                for (i = drawObjNextNo; i < DrawObjIdx; i++) {
                    temp = DrawObjNum[i];
                    z = DrawObjData[DrawObjNum[i]].z;
                    j = i - drawObjNextNo;
                    while (j >= 0) {
                        if (DrawObjData[DrawObjNum[j]].z < z) {
                            DrawObjNum[j + drawObjNextNo] = DrawObjNum[j];
                            j -= drawObjNextNo;
                        } else {
                            break;
                        }
                    }
                    DrawObjNum[j + drawObjNextNo] = temp;
                }
            }
            for (i = 0; i < DrawObjIdx - 1; i++) {
                for (j = i + 1; j < DrawObjIdx; j++) {
                    if (DrawObjData[DrawObjNum[i]].z != DrawObjData[DrawObjNum[j]].z) {
                        break;
                    }
                    if (DrawObjNum[j] < DrawObjNum[i]) {
                        temp = DrawObjNum[i];
                        DrawObjNum[i] = DrawObjNum[j];
                        DrawObjNum[j] = temp;
                    }
                }
            }
        }
        GXInvalidateTexAll();
        GXInvalidateVtxCache();
        materialBak = PTR_INVALID;
        for (i = 0; i < 8; i++) {
            BmpPtrBak[i] = PTR_INVALID;
        }
        GXSetCullMode(GX_CULL_BACK);
        for (drawObjNo = 0; drawObjNo < DrawObjIdx; drawObjNo++) {
            drawObj = &DrawObjData[DrawObjNum[drawObjNo]];
            if (drawObj->model->attr & HU3D_ATTR_HOOKFUNC) {
                hookFunc = (void*) drawObj->model->hsf;
                hookFunc(drawObj->model, drawObj->matrix);
                for (i = 0; i < 8; i++) {
                    BmpPtrBak[i] = PTR_INVALID;
                }
                materialBak = PTR_INVALID;
                Hu3DCameraSet(Hu3DCameraNo, Hu3DCameraMtx);
            } else {
                Hu3DObjInfoP = drawObj->object->constData;
                DLBufStartP = Hu3DObjInfoP->dlBuf;
                DrawData = Hu3DObjInfoP->drawData;
                GXLoadPosMtxImm(drawObj->matrix, GX_PNMTX0);
                MTXInvXpose(drawObj->matrix, mtx);
                GXLoadNrmMtxImm(mtx, 0);
                if (Hu3DShadowF != 0 && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->attr & 8)) {
                    MTXInverse(Hu3DCameraMtx, invCamera);
                    MTXConcat(invCamera, drawObj->matrix, mtx);
                    MTXConcat(Hu3DShadowData.projMtx, Hu3DShadowData.lookAtMtx, shadowCam);
                    MTXConcat(shadowCam, mtx, mtx);
                    GXLoadTexMtxImm(mtx, GX_TEXMTX9, GX_MTX3x4);
                    invF = TRUE;
                } else {
                    invF = FALSE;
                }
                if (drawObj->model->projBit != 0) {
                    if (invF == FALSE) {
                        MTXInverse(Hu3DCameraMtx, invCamera);
                    }
                    for (i = 0, projBit = 1; i < HU3D_PROJ_MAX; i++, projBit <<= 1) {
                        if (projBit & drawObj->model->projBit) {
                            MTXConcat(invCamera, drawObj->matrix, mtx);
                            MTXConcat(Hu3DProjection[i].projMtx, Hu3DProjection[i].lookAtMtx, shadowCam);
                            MTXConcat(shadowCam, mtx, mtx);
                            GXLoadTexMtxImm(mtx, texMtxTbl[i + 3], GX_MTX3x4);
                        }
                    }
                }
                if ((drawObj->model->attr & HU3D_ATTR_HILITE) || (Hu3DObjInfoP->attr & HU3D_CONST_HILITE)) {
                    // TODO SetHiliteTexMtx
                    axis = lbl_8011DD20;
                    lightP = &Hu3DGlobalLight[drawObj->model->hiliteIdx];
                    dir = lightP->dir;
                    if (lightP->type & 0x8000) {
                        MTXMultVecSR(Hu3DCameraMtx, &dir, &dir);
                    }
                    dot = VECDotProduct(&dir, &axis);
                    dot *= 10000.0f;
                    OSf32tos16(&dot, &similar);
                    if (similar == -10000) {
                        MTXScale(hiliteMtx, 0.0f, 0.0f, 0.0f);
                    } else {
                        C_VECHalfAngle(&dir, &axis, &halfAngle);
                        halfAngle.x = -halfAngle.x;
                        halfAngle.y = -halfAngle.y;
                        halfAngle.z = -halfAngle.z;
                        MTXScale(scale, 1.0f / drawObj->scale.x, 1.0f / drawObj->scale.y, 1.0f / drawObj->scale.z);
                        MTXConcat(drawObj->matrix, scale, mtx2);
                        mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
                        PSMTXInvXpose(mtx2, sp90);
                        if (similar == 10000) {
                            PSMTXIdentity(mtx2);
                        } else {
                            VECCrossProduct(&halfAngle, &axis, &cross);
                            cosDot = acosf(VECDotProduct(&axis, &halfAngle));
                            PSMTXRotAxisRad(mtx2, &cross, cosDot);
                        }
                        PSMTXConcat(mtx2, sp90, scale);
                        PSMTXTrans(mtx2, 0.5f, 0.5f, 0.0f);
                        PSMTXConcat(mtx2, scale, hiliteMtx);
                    }
                }
                faceBuf = drawObj->object->mesh.face;
                facePtr = faceBuf->data;
                drawCnt = 0;
                shadingBak = -1;
                vtxModeBak = -1;
                materialBak = PTR_INVALID;
                if (shadowModelDrawF == 0) {
                    for (i = 0; i < faceBuf->count;) {
                        FaceDraw(drawObj, facePtr);
                        if (facePtr->type == 4) {
                            totalPolyCnt += DrawData[drawCnt - 1].polyCnt;
                            i++;
                            facePtr++;
                        } else {
                            totalPolyCnt += DrawData[drawCnt - 1].polyCnt * ((facePtr->type & 7) == 3 ? 2 : 1);
                            i += DrawData[drawCnt - 1].polyCnt;
                            facePtr += DrawData[drawCnt - 1].polyCnt;
                        }
                    }
                } else {
                    color.a = 0xFF;
                    GXSetChanAmbColor(GX_COLOR0A0, color);
                    GXSetChanMatColor(GX_COLOR0A0, color);
                    color.a = Hu3DShadowData.alpha;
                    GXSetTevColor(GX_TEVREG1, color);
                    GXSetNumChans(1);
                    for (i = 0; i < faceBuf->count;) {
                        FaceDrawShadow(drawObj, facePtr);
                        if (facePtr->type == 4) {
                            i++;
                            facePtr++;
                        } else {
                            i += DrawData[drawCnt - 1].polyCnt;
                            facePtr += DrawData[drawCnt - 1].polyCnt;
                        }
                    }
                }
                if (TL32F) {
                    for (i = GX_TEVSTAGE0; i < GX_MAX_TEVSTAGE; i++) {
                        GXSetTevSwapMode(i, GX_TEV_SWAP0, GX_TEV_SWAP0);
                    }
                    TL32F = 0;
                }
            }
        }
    }
    (void)invF; // required to match
}

static void ObjDraw(HU3DDRAWOBJ *arg0) {
    Vec axis;
    Vec sp38;
    Vec halfAngle;
    Vec dir;
    GXColor color;
    HSFBUFFER *faceBuf;
    s16 invF;
    s16 similar;
    s16 projBit;
    s16 i;
    float dot;
    float cosDot;
    HU3DLIGHT *lightP;
    HSFDRAWDATA *draw;
    HSFFACE *facePtr;
    Mtx shadowCam;
    Mtx mtx;
    Mtx invCamera;
    Mtx mtx2;
    Mtx invXPose;
    Mtx scale;

    Hu3DObjInfoP = arg0->object->constData;
    DLBufStartP = Hu3DObjInfoP->dlBuf;
    DrawData = Hu3DObjInfoP->drawData;
    GXLoadPosMtxImm(arg0->matrix, GX_PNMTX0);
    MTXInvXpose(arg0->matrix, mtx);
    GXLoadNrmMtxImm(mtx, 0);
    GXInvalidateVtxCache();
    if (Hu3DShadowF != FALSE && Hu3DShadowCamBit != 0 && (Hu3DObjInfoP->attr & HU3D_CONST_SHADOW_MAP)) {
        MTXInverse(Hu3DCameraMtx, invCamera);
        MTXConcat(invCamera, arg0->matrix, mtx);
        MTXConcat(Hu3DShadowData.projMtx, Hu3DShadowData.lookAtMtx, shadowCam);
        MTXConcat(shadowCam, mtx, mtx);
        GXLoadTexMtxImm(mtx, GX_TEXMTX9, GX_MTX3x4);
        invF = TRUE;
    } else {
        invF = FALSE;
    }
    if (arg0->model->projBit != 0) {
        if (invF == FALSE) {
            MTXInverse(Hu3DCameraMtx, invCamera);
        }
        for (i = 0, projBit = 1; i < HU3D_PROJ_MAX; i++, projBit <<= 1) {
            if (projBit & arg0->model->projBit) {
                MTXConcat(invCamera, arg0->matrix, mtx);
                MTXConcat(Hu3DProjection[i].projMtx, Hu3DProjection[i].lookAtMtx, shadowCam);
                MTXConcat(shadowCam, mtx, mtx);
                GXLoadTexMtxImm(mtx, texMtxTbl[i + 3], GX_MTX3x4);
            }
        }
    }
    if ((arg0->model->attr & HU3D_ATTR_HILITE) || (Hu3DObjInfoP->attr & HU3D_CONST_HILITE)) {
        // TODO SetHiliteTexMtx
        axis = lbl_8011DD20;
        lightP = &Hu3DGlobalLight[arg0->model->hiliteIdx];
        dir = lightP->dir;
        if (lightP->type & 0x8000) {
            MTXMultVecSR(Hu3DCameraMtx, &dir, &dir);
        }
        dot = VECDotProduct(&dir, &axis);
        dot *= 10000.0f;
        OSf32tos16(&dot, &similar);
        if (similar == -10000) {
            MTXScale(hiliteMtx, 0.0f, 0.0f, 0.0f);
        } else {
            C_VECHalfAngle(&dir, &axis, &halfAngle);
            halfAngle.x = -halfAngle.x;
            halfAngle.y = -halfAngle.y;
            halfAngle.z = -halfAngle.z;
            MTXScale(scale, 1.0f / arg0->scale.x, 1.0f / arg0->scale.y, 1.0f / arg0->scale.z);
            MTXConcat(arg0->matrix, scale, mtx2);
            mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
            PSMTXInvXpose(mtx2, invXPose);
            if (similar == 10000) {
                PSMTXIdentity(mtx2);
            } else {
                VECCrossProduct(&halfAngle, &axis, &sp38);
                cosDot = acosf(VECDotProduct(&axis, &halfAngle));
                PSMTXRotAxisRad(mtx2, &sp38, cosDot);
            }
            PSMTXConcat(mtx2, invXPose, scale);
            PSMTXTrans(mtx2, 0.5f, 0.5f, 0.0f);
            PSMTXConcat(mtx2, scale, hiliteMtx);
        }
    }
    faceBuf = arg0->object->mesh.face;
    facePtr = faceBuf->data;
    drawCnt = 0;
    shadingBak = -1;
    vtxModeBak = -1;
    materialBak = PTR_INVALID;
    if (shadowModelDrawF == 0) {
        for (i = 0; i < faceBuf->count;) {
            FaceDraw(arg0, facePtr);
            if (facePtr->type == 4) {
                totalPolyCnt += DrawData[drawCnt - 1].polyCnt;
                i++;
                facePtr++;
            } else {
                draw = &DrawData[drawCnt - 1];
                totalPolyCnt += draw->polyCnt * ((facePtr->type & 7) == 3 ? 2 : 1);
                i += draw->polyCnt;
                facePtr += draw->polyCnt;
            }
        }
    } else {
        color.a = 0xFF;
        GXSetChanAmbColor(GX_COLOR0A0, color);
        GXSetChanMatColor(GX_COLOR0A0, color);
        color.a = Hu3DShadowData.alpha;
        GXSetTevColor(GX_TEVREG1, color);
        GXSetNumChans(1);
        for (i = 0; i < faceBuf->count;) {
            FaceDrawShadow(arg0, facePtr);
            if (facePtr->type == 4) {
                i++;
                facePtr++;
            } else {
                i += DrawData[drawCnt - 1].polyCnt;
                facePtr += DrawData[drawCnt - 1].polyCnt;
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

void MakeDisplayList(HU3DMODELID modelId, u32 no) {
    HSFDATA *hsf;
    HU3DMODEL *modelP;

    hsf = Hu3DData[modelId].hsf;
    modelP = &Hu3DData[modelId];
    curModelID = modelId;
    mallocNo = no;
    faceNumBuf = HuMemDirectMallocNum(HEAP_MODEL, 0x800 * sizeof(u16), mallocNo);
    MDObjCall(hsf, hsf->root);
    HuMemDirectFree(faceNumBuf);
    if (modelP->attr & HU3D_ATTR_SHADOW) {
        Hu3DShadowCamBit++;
    }
}

static void MDObjCall(HSFDATA *hsf, HSFOBJECT *objPtr) {
    s16 i;

    switch (objPtr->type) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 9:
            for (i = 0; i < objPtr->mesh.childrenCount; i++) {
                MDObjCall(hsf, objPtr->mesh.children[i]);
            }
            break;
        case 2:
            MDObjMesh(hsf, objPtr);
            break;
    }
}

static void MDObjMesh(HSFDATA *hsf, HSFOBJECT *objPtr) {
    HSFBUFFER *faceBuf;
    HSFFACE *facePtr;
    s16 i;

    faceBuf = objPtr->mesh.face;
    DLFirstF = 0;
    drawCnt = matChgCnt = triCnt = quadCnt = 0;
    faceNumBuf[0] = 0;
    materialBak = PTR_INVALID;
    polyTypeBak = 0xFF;
    DLTotalNum = 0;
    facePtr = faceBuf->data;
    for (i = 0; i < faceBuf->count; i++, facePtr++) {
        MDFaceCnt(objPtr, facePtr);
    }
    DLTotalNum = (DLTotalNum + 0x40) & ~0x1F;
    Hu3DObjInfoP = ObjConstantMake(objPtr, mallocNo);
    Hu3DObjInfoP->drawData = DrawData = HuMemDirectMallocNum(HEAP_MODEL, matChgCnt * sizeof(HSFDRAWDATA), mallocNo);
    memset(DrawData, 0, matChgCnt * sizeof(HSFDRAWDATA));
    DLBufP = DLBufStartP = HuMemDirectMallocNum(HEAP_MODEL, DLTotalNum, mallocNo);
    DCInvalidateRange(DLBufStartP, DLTotalNum);
    DLFirstF = 0;
    materialBak = PTR_INVALID;
    polyTypeBak = 0xFF;
    totalSize = drawCnt = 0;
    facePtr = faceBuf->data;
    if (objPtr->flags & HSF_MATERIAL_SHADOW) {
        Hu3DObjInfoP->attr |= HU3D_CONST_SHADOW;
        Hu3DModelAttrSet(curModelID, HU3D_ATTR_SHADOW);
    }
    if (objPtr->flags & HSF_MATERIAL_SHADOWMAP) {
        Hu3DObjInfoP->attr |= HU3D_CONST_SHADOW_MAP;
    }
    if (objPtr->flags & (HSF_MATERIAL_ADDCOL|HSF_MATERIAL_INVCOL)) {
        Hu3DObjInfoP->attr |= HU3D_CONST_ALTBLEND;
    }
    if (objPtr->flags & HSF_MATERIAL_HILITE) {
        Hu3DObjInfoP->attr |= HU3D_CONST_HILITE;
    }
    for (i = 0; i < faceBuf->count; i++, facePtr++) {
        MDFaceDraw(objPtr, facePtr);
    }
    Hu3DObjInfoP->dlBuf = DLBufStartP;
    if (DLTotalNum < totalSize) {
        OSReport("DLBuf Over >>>>>>>>>>>>>");
        OSReport("%x:%x:%x\n", Hu3DObjInfoP->dlBuf, totalSize, DLTotalNum);
    }
    for (i = 0; i < objPtr->mesh.childrenCount; i++) {
        MDObjCall(hsf, objPtr->mesh.children[i]);
    }
}

HSFCONSTDATA *ObjConstantMake(HSFOBJECT *object, u32 no) {
    HSFCONSTDATA *constDataP = HuMemDirectMallocNum(HEAP_MODEL, sizeof(HSFCONSTDATA), no);
    object->constData = constDataP;
    constDataP->attr = HU3D_CONST_NONE;
    constDataP->hookMdlId = HU3D_MODELID_NONE;
    constDataP->hiliteMap = NULL;
    return constDataP;
}

#define VTX_COLOR(obj, idx) (&((GXColor *) obj->mesh.color->data)[idx])
static void MDFaceDraw(HSFOBJECT *objPtr, HSFFACE *face) {
    HSFMATERIAL *matP;
    s16 *stripPtr;
    s16 nbtAttrIdx;
    s16 i;
    s16 nbtAttr;
    s32 colorIdx;
    s32 dlSize;
    s32 stF;

    nbtAttrIdx = -1;
    matP = &objPtr->mesh.material[face->mat & 0xFFF];
    if (matP != materialBak || polyTypeBak != (face->type & 7) || (face->type & 7) == 4) {
        polyTypeBak = face->type & 7;
        materialBak = matP;
        DrawData[drawCnt].dlOfs = (u32) DLBufP - (u32) DLBufStartP;
        GXBeginDisplayList(DLBufP, 0x20000);
        GXResetWriteGatherPipe();
        if (matP->attrNum == 0) {
            stF = FALSE;
        } else {
            stF = TRUE;
            for (i = 0; i < matP->attrNum; i++) {
                if (objPtr->mesh.attribute[matP->attr[i]].nbtTpLvl != 0.0) {
                    Hu3DObjInfoP->attr |= 2;
                    DrawData[drawCnt].flags |= 2;
                    nbtAttrIdx = i;
                }
            }
            if (nbtAttrIdx != -1 && nbtAttrIdx != 0) {
                nbtAttr = matP->attr[nbtAttrIdx];
                for (i = matP->attrNum - 2; i >= 0; i--) {
                    if (i != nbtAttrIdx) {
                        matP->attr[i + 1] = matP->attr[i];
                    }
                }
                matP->attr[0] = nbtAttr;
            }
        }
        if (matP->invAlpha != 0.0 || (matP->pass & 0xF)) {
            Hu3DObjInfoP->attr |= HU3D_CONST_XLU;
        }
        if (matP->flags & (HSF_MATERIAL_ADDCOL|HSF_MATERIAL_INVCOL)) {
            Hu3DObjInfoP->attr |= HU3D_CONST_ALTBLEND;
        }
        if (matP->refAlpha != 0.0) {
            Hu3DObjInfoP->attr |= HU3D_CONST_REFLECT;
        }
        if (matP->flags & HSF_MATERIAL_HILITE) {
            Hu3DObjInfoP->attr |= HU3D_CONST_HILITE;
        }
        if (matP->flags & HSF_MATERIAL_NEAR) {
            Hu3DObjInfoP->attr |= HU3D_CONST_NEAR;
        }
        faceCnt = 0;
        switch (face->type & 7) {
            case 0:
            case 1:
                break;
            case HSF_FACE_TRI:
                GXBegin(GX_TRIANGLES, GX_VTXFMT0, faceNumBuf[drawCnt]);
                for (i = 0; i < faceNumBuf[drawCnt] / 3; i++, face++) {
                    GXPosition1x16(face->indices[0][0]);
                    if (nbtAttrIdx == -1) {
                        GXNormal1x16(face->indices[0][1]);
                    } else {
                        MakeCalcNBT(objPtr, face, 0, 1);
                    }
                    if (matP->vtxMode == 5) {
                        colorIdx = face->indices[0][2];
                        GXColor1x16(colorIdx);
                        if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                            Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                        }
                    }
                    if (stF != 0) {
                        GXTexCoord1x16(face->indices[0][3]);
                    }
                    GXPosition1x16(face->indices[2][0]);
                    if (nbtAttrIdx == -1) {
                        GXNormal1x16(face->indices[2][1]);
                    } else {
                        MakeNBT(objPtr, face, 2, 0);
                    }
                    if (matP->vtxMode == 5) {
                        colorIdx = face->indices[2][2];
                        GXColor1x16(colorIdx);
                        if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                            Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                        }
                    }
                    if (stF != 0) {
                        GXTexCoord1x16(face->indices[2][3]);
                    }
                    GXPosition1x16(face->indices[1][0]);
                    if (nbtAttrIdx == -1) {
                        GXNormal1x16(face->indices[1][1]);
                    } else {
                        MakeNBT(objPtr, face, 1, 2);
                    }
                    if (matP->vtxMode == 5) {
                        colorIdx = face->indices[1][2];
                        GXColor1x16(colorIdx);
                        if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                            Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                        }
                    }
                    if (stF != 0) {
                        GXTexCoord1x16(face->indices[1][3]);
                    }
                }
                faceCnt = faceNumBuf[drawCnt] / 3;
                break;
            case HSF_FACE_QUAD:
                GXBegin(GX_QUADS, GX_VTXFMT0, faceNumBuf[drawCnt]);
                for (i = 0; i < faceNumBuf[drawCnt] / 4; i++, face++) {
                    GXPosition1x16(face->indices[0][0]);
                    if (nbtAttrIdx == -1) {
                        GXNormal1x16(face->indices[0][1]);
                    } else {
                        MakeCalcNBT(objPtr, face, 0, 1);
                    }
                    if (matP->vtxMode == 5) {
                        colorIdx = face->indices[0][2];
                        GXColor1x16(colorIdx);
                        if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                            Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                        }
                    }
                    if (stF != 0) {
                        GXTexCoord1x16(face->indices[0][3]);
                    }
                    GXPosition1x16(face->indices[2][0]);
                    if (nbtAttrIdx == -1) {
                        GXNormal1x16(face->indices[2][1]);
                    } else {
                        MakeNBT(objPtr, face, 2, 0);
                    }
                    if (matP->vtxMode == 5) {
                        colorIdx = face->indices[2][2];
                        GXColor1x16(colorIdx);
                        if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                            Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                        }
                    }
                    if (stF != 0) {
                        GXTexCoord1x16(face->indices[2][3]);
                    }
                    GXPosition1x16(face->indices[3][0]);
                    if (nbtAttrIdx == -1) {
                        GXNormal1x16(face->indices[3][1]);
                    } else {
                        MakeNBT(objPtr, face, 3, 2);
                    }
                    if (matP->vtxMode == 5) {
                        colorIdx = face->indices[3][2];
                        GXColor1x16(colorIdx);
                        if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                            Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                        }
                    }
                    if (stF != 0) {
                        GXTexCoord1x16(face->indices[3][3]);
                    }
                    GXPosition1x16(face->indices[1][0]);
                    if (nbtAttrIdx == -1) {
                        GXNormal1x16(face->indices[1][1]);
                    } else {
                        MakeNBT(objPtr, face, 1, 3);
                    }
                    if (matP->vtxMode == 5) {
                        colorIdx = face->indices[1][2];
                        GXColor1x16(colorIdx);
                        if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                            Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                        }
                    }
                    if (stF != 0) {
                        GXTexCoord1x16(face->indices[1][3]);
                    }
                }
                faceCnt = faceNumBuf[drawCnt] / 4;
                break;
            case HSF_FACE_TRISTRIP:
                GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, faceNumBuf[drawCnt]);
                GXPosition1x16(face->indices[0][0]);
                if (nbtAttrIdx == -1) {
                    GXNormal1x16(face->indices[0][1]);
                } else {
                    MakeCalcNBT(objPtr, face, 0, 1);
                }
                if (matP->vtxMode == 5) {
                    colorIdx = face->indices[0][2];
                    GXColor1x16(colorIdx);
                    if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                        Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                    }
                }
                if (stF != 0) {
                    GXTexCoord1x16(face->indices[0][3]);
                }
                GXPosition1x16(face->indices[2][0]);
                if (nbtAttrIdx == -1) {
                    GXNormal1x16(face->indices[2][1]);
                } else {
                    MakeNBT(objPtr, face, 2, 0);
                }
                if (matP->vtxMode == 5) {
                    colorIdx = face->indices[2][2];
                    GXColor1x16(colorIdx);
                    if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                        Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                    }
                }
                if (stF != 0) {
                    GXTexCoord1x16(face->indices[2][3]);
                }
                GXPosition1x16(face->indices[1][0]);
                if (nbtAttrIdx == -1) {
                    GXNormal1x16(face->indices[1][1]);
                } else {
                    MakeNBT(objPtr, face, 1, 2);
                }
                if (matP->vtxMode == 5) {
                    colorIdx = face->indices[1][2];
                    GXColor1x16(colorIdx);
                    if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                        Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                    }
                }
                if (stF != 0) {
                    GXTexCoord1x16(face->indices[1][3]);
                }
                stripPtr = face->strip.data;
                for (i = 0; i < face->strip.count; i++, stripPtr += 4) {
                    GXPosition1x16(stripPtr[0]);
                    if (nbtAttrIdx == -1) {
                        GXNormal1x16(stripPtr[1]);
                    } else {
                        MakeCalcNBT(objPtr, face, 0, 1);
                    }
                    if (matP->vtxMode == 5) {
                        colorIdx = stripPtr[2];
                        GXColor1x16(colorIdx);
                        if (VTX_COLOR(objPtr, colorIdx)->a != 0xFF) {
                            Hu3DObjInfoP->attr |= HU3D_CONST_XLUVERTEX|HU3D_CONST_XLU;
                        }
                    }
                    if (stF != 0) {
                        GXTexCoord1x16(stripPtr[3]);
                    }
                }
                faceCnt = face->strip.count + 1;
                break;
        }
        dlSize = GXEndDisplayList();
        DrawData[drawCnt].dlSize = dlSize;
        DrawData[drawCnt].polyCnt = faceCnt;
        totalSize += dlSize;
        drawCnt++;
        DLBufP = (u8*) DLBufP + dlSize;
    }
}

#undef VTX_COLOR

static s32 MakeCalcNBT(HSFOBJECT *objPtr, HSFFACE *face, s16 endVtx, s16 startVtx) {
    HuVecF NBT;
    HuVecF *normal;
    HuVecF *vertex;
    s8 (*s8Normal)[3];
    s16 endVtxIdx;
    s16 startVtxIdx;
    s16 normalIdx;

    vertex = objPtr->mesh.vertex->data;
    normalIdx = face->indices[endVtx][1];
    endVtxIdx = face->indices[endVtx][0];
    startVtxIdx = face->indices[startVtx][0];
    if (objPtr->mesh.cenvNum != 0) {
        normal = objPtr->mesh.normal->data;
        NBT.x = normal[normalIdx].x;
        NBT.y = normal[normalIdx].y;
        NBT.z = normal[normalIdx].z;
    } else {
        s8Normal = objPtr->mesh.normal->data;
        NBT.x = s8Normal[normalIdx][0];
        NBT.y = s8Normal[normalIdx][1];
        NBT.z = s8Normal[normalIdx][2];
        VECNormalize(&NBT, &NBT);
    }
    NBTB.x = vertex[endVtxIdx].x - vertex[startVtxIdx].x;
    NBTB.y = vertex[endVtxIdx].y - vertex[startVtxIdx].y;
    NBTB.z = vertex[endVtxIdx].z - vertex[startVtxIdx].z;
    VECNormalize(&NBTB, &NBTB);
    VECCrossProduct(&NBTB, &NBT, &NBTT);
    GXNormal3s16(NBT.x * 256.0f, NBT.y * 256.0f, NBT.z * 256.0f);
    GXNormal3s16(NBTB.x * 256.0f, NBTB.y * 256.0f, NBTB.z * 256.0f);
    GXNormal3s16(NBTT.x * 256.0f, NBTT.y * 256.0f, NBTT.z * 256.0f);
}

static s32 MakeNBT(HSFOBJECT *objPtr, HSFFACE *face, s16 endVtx, s16 startVtx) {
    Vec NBT;
    Vec *normal;
    Vec *vertex;
    HSFS8VEC *s8Normal;
    s16 normalIdx;

    vertex = objPtr->mesh.vertex->data;
    normalIdx = face->indices[endVtx][1];
    if (objPtr->mesh.cenvNum != 0) {
        normal = objPtr->mesh.normal->data;
        NBT.x = normal[normalIdx].x;
        NBT.y = normal[normalIdx].y;
        NBT.z = normal[normalIdx].z;
    } else {
        s8Normal = objPtr->mesh.normal->data;
        NBT.x = s8Normal[normalIdx].x;
        NBT.y = s8Normal[normalIdx].y;
        NBT.z = s8Normal[normalIdx].z;
        VECNormalize(&NBT, &NBT);
    }
    GXNormal3s16(NBT.x * 256.0f, NBT.y * 256.0f, NBT.z * 256.0f);
    GXNormal3s16(NBTB.x * 256.0f, NBTB.y * 256.0f, NBTB.z * 256.0f);
    GXNormal3s16(NBTT.x * 256.0f, NBTT.y * 256.0f, NBTT.z * 256.0f);
}

static void MDFaceCnt(HSFOBJECT *objPtr, HSFFACE *face) {
    HSFMATERIAL *matP;
    s16 i;

    matP = &objPtr->mesh.material[face->mat & 0xFFF];
    // Bug? Likely to be polyTypeBak != (arg1->unk00 & 7)
    if (matP != materialBak || ((polyTypeBak != face->type) & 7) || (face->type & 7) == 4) {
        polySize = 4;
        polyTypeBak = face->type & 7;
        materialBak = matP;
        matChgCnt++;
        if (DLFirstF != 0) {
            drawCnt++;
            faceNumBuf[drawCnt] = 0;
            DLTotalNum = ((DLTotalNum + 0x20) & ~0x1F) + 0x20;
        } else {
            DLFirstF = 1;
        }
        if (matP->attrNum != 0) {
            polySize += 2;
            for (i = 0; i < matP->attrNum; i++) {
                if (objPtr->mesh.attribute[matP->attr[i]].nbtTpLvl != 0.0) {
                    polySize += 0x12;
                }
            }
        }
        if (matP->vtxMode == 5) {
            polySize += 2;
        }
    }
    switch (face->type & 7) {
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
            faceNumBuf[drawCnt] += face->strip.count + 3;
            DLTotalNum += polySize * 3;
            DLTotalNum += polySize * face->strip.count;
            break;
        default:
            OSReport("Error\n");
            break;
    }
}

void mtxTransCat(Mtx mtx, float x, float y, float z) {
    if (x != 0.0f || y != 0.0f || z != 0.0f) {
        mtx[0][3] += x;
        mtx[1][3] += y;
        mtx[2][3] += z;
    }
}

void mtxRotCat(Mtx mtx, float x, float y, float z) {
    Mtx temp;

    if (x != 0.0f) {
        MTXRotRad(temp, 'X', MTXDegToRad(x));
        MTXConcat(temp, mtx, mtx);
    }
    if (y != 0.0f) {
        MTXRotRad(temp, 'Y', MTXDegToRad(y));
        MTXConcat(temp, mtx, mtx);
    }
    if (z != 0.0f) {
        MTXRotRad(temp, 'Z', MTXDegToRad(z));
        MTXConcat(temp, mtx, mtx);
    }
}

void mtxRot(Mtx mtx, float x, float y, float z) {
    Mtx rotY;
    Mtx rotZ;

    if (x != 0.0f) {
        MTXRotRad(mtx, 'X', MTXDegToRad(x));
    } else {
        MTXIdentity(mtx);
    }
    if (y != 0.0f) {
        MTXRotRad(rotY, 'Y', MTXDegToRad(y));
        MTXConcat(rotY, mtx, mtx);
    }
    if (z != 0.0f) {
        MTXRotRad(rotZ, 'Z', MTXDegToRad(z));
        MTXConcat(rotZ, mtx, mtx);
    }
}

void mtxScaleCat(Mtx mtx, float x, float y, float z) {
    mtx[0][0] *= x;
    mtx[1][0] *= x;
    mtx[2][0] *= x;
    mtx[0][1] *= y;
    mtx[1][1] *= y;
    mtx[2][1] *= y;
    mtx[0][2] *= z;
    mtx[1][2] *= z;
    mtx[2][2] *= z;
}

s16 HmfInverseMtxF3X3(Mtx src, Mtx dst) {
    float detA;
    float detB;
    float detC;
    float det;

    detA = src[1][1] * src[2][2] - src[2][1] * src[1][2];
    detB = src[2][1] * src[0][2] - src[0][1] * src[2][2];
    detC = src[0][1] * src[1][2] - src[1][1] * src[0][2];
    det = src[0][0] * detA + src[1][0] * detB + src[2][0] * detC;
    if (det == 0.0f) {
        return 0;
    }
    det = 1.0f / det;
    dst[0][0] = detA * det;
    dst[0][1] = detB * det;
    dst[0][2] = detC * det;
    dst[1][0] = det * (src[2][0] * src[1][2] - src[1][0] * src[2][2]);
    dst[2][0] = det * (src[1][0] * src[2][1] - src[2][0] * src[1][1]);
    dst[1][1] = det * (src[0][0] * src[2][2] - src[2][0] * src[0][2]);
    dst[2][1] = det * (src[2][0] * src[0][1] - src[0][0] * src[2][1]);
    dst[1][2] = det * (src[1][0] * src[0][2] - src[0][0] * src[1][2]);
    dst[2][2] = det * (src[0][0] * src[1][1] - src[1][0] * src[0][1]);
    dst[0][3] = dst[1][3] = dst[2][3] = 0.0f;
    return 1;
}

static void SetDefLightInlineFunc(GXLightObj *lightObj, u8 colorR, u8 colorG, u8 colorB, u8 ambR, u8 ambG, u8 ambB, u8 matR, u8 matG, u8 matB) {
    GXColor color;

    color.r = colorR;
    color.g = colorG;
    color.b = colorB;
    color.a = 0xFF;
    GXInitLightColor(lightObj, color);
    GXLoadLightObjImm(lightObj, GX_LIGHT0);
    color.r = ambR;
    color.g = ambG;
    color.b = ambB;
    GXSetChanAmbColor(GX_COLOR0A0, color);
    color.r = matR;
    color.g = matG;
    color.b = matB;
    GXSetChanMatColor(GX_COLOR0A0, color);
}

void SetDefLight(Vec *pos, Vec *dir, u8 colorR, u8 colorG, u8 colorB, u8 ambR, u8 ambG, u8 ambB, u8 matR, u8 matG, u8 matB) {
    GXLightObj lightObj;

    GXInitLightAttn(&lightObj, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    GXInitLightSpot(&lightObj, 20.0f, GX_SP_COS);
    GXInitLightPos(&lightObj, pos->x, pos->y, pos->z);
    GXInitLightDir(&lightObj, dir->x, dir->y, dir->z);
    SetDefLightInlineFunc(&lightObj, colorR, colorG, colorB, ambR, ambG, ambB, matR, matG, matB);
}

void Hu3DModelObjPosGet(HU3DMODELID modelId, char *objName, Vec *pos) {
    Mtx mtx;

    Hu3DModelObjMtxGet(modelId, objName, mtx);
    pos->x = mtx[0][3];
    pos->y = mtx[1][3];
    pos->z = mtx[2][3];
    if (PGFinishF == 0) {
        OSReport("Error: Not Found %s for ObjPosGet\n", objName);
        pos->x = pos->y = pos->z = 0.0f;
    }
}

void Hu3DModelObjMtxGet(HU3DMODELID modelId, char *objName, Mtx mtx) {
    HU3DMODEL *modelP;
    HSFDATA *hsf;
    Mtx scale;
    Mtx rot;

    modelP = &Hu3DData[modelId];
    hsf = modelP->hsf;
    mtxRot(rot, modelP->rot.x, modelP->rot.y, modelP->rot.z);
    MTXScale(scale, modelP->scale.x, modelP->scale.y, modelP->scale.z);
    MTXConcat(rot, scale, MTXBuf[0]);
    mtxTransCat(MTXBuf[0], modelP->pos.x, modelP->pos.y, modelP->pos.z);
    PGMaxPos.x = PGMaxPos.y = PGMaxPos.z = -1000000.0f;
    PGMinPos.x = PGMinPos.y = PGMinPos.z = 1000000.0f;
    MTXIdx = 1;
    CancelTRXF = FALSE;
    PGFinishF = FALSE;
    hookIdx = HU3D_MODELID_NONE;
    PGName = HuMemDirectMallocNum(HEAP_HEAP, 0x200, HU_MEMNUM_OVL);
    strcpy((char*) PGName, MakeObjectName(objName));
    if (modelP->motId != -1) {
        attachMotionF = 1;
    } else {
        attachMotionF = 0;
    }
    PGObjCall(modelP, hsf->root);
    MTXCopy(MTXBuf[MTXIdx - 1], mtx);
    if (PGFinishF == 0 && *PGName != 0) {
        OSReport("Error: Not Found %s for ObjPosGet\n", objName);
        MTXIdentity(MTXBuf[MTXIdx]);
    }
    HuMemDirectFree(PGName);
}

void PGObjCall(HU3DMODEL *model, HSFOBJECT *object) {
    switch (object->type) {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 9:
            PGObjCalc(model, object);
            break;
        case 1:
            PGObjReplica(model, object);
            break;
    }
}

void PGObjCalc(HU3DMODEL *model, HSFOBJECT *object) {
    Vec pos;
    s16 hookIdxOld;
    s16 applyF;
    s16 i;
    HSFOBJECT *obj;
    HSFCONSTDATA *constDataP;
    HSFTRANSFORM *transformP;
    HU3DMODEL *hookMdlP;
    Mtx mtx;
    Mtx rot;

    if (CancelTRXF == 0) {
        if (attachMotionF == 0) {
            transformP = &object->mesh.base;
        } else {
            transformP = &object->mesh.curr;
        }
        mtxRot(rot, transformP->rot.x, transformP->rot.y, transformP->rot.z);
        MTXScale(mtx, transformP->scale.x, transformP->scale.y, transformP->scale.z);
        MTXConcat(rot, mtx, mtx);
        mtxTransCat(mtx, transformP->pos.x, transformP->pos.y, transformP->pos.z);
        MTXConcat(MTXBuf[MTXIdx - 1], mtx, MTXBuf[MTXIdx]);
        MTXIdx++;
        applyF = 1;
    } else {
        CancelTRXF = 0;
        applyF = 0;
    }
    if (strcmp((char*) PGName, object->name) == 0) {
        PGFinishF = 1;
        return;
    }
    constDataP = object->constData;
    if (constDataP && constDataP->hookMdlId != HU3D_MODELID_NONE) {
        hookMdlP = &Hu3DData[constDataP->hookMdlId];
        if (!(hookMdlP->attr & HU3D_ATTR_DISPOFF)) {
            i = attachMotionF;
            if (hookMdlP->motId != HU3D_MOTID_NONE) {
                attachMotionF = TRUE;
            } else {
                attachMotionF = FALSE;
            }
            hookIdxOld = hookIdx;
            hookIdx = constDataP->hookMdlId;
            MTXScale(mtx, hookMdlP->scale.x, hookMdlP->scale.y, hookMdlP->scale.z);
            mtxRotCat(mtx, hookMdlP->rot.x, hookMdlP->rot.y, hookMdlP->rot.z);
            mtxTransCat(mtx, hookMdlP->pos.x, hookMdlP->pos.y, hookMdlP->pos.z);
            MTXConcat(mtx, hookMdlP->mtx, mtx);
            MTXConcat(MTXBuf[MTXIdx - 1], mtx, MTXBuf[MTXIdx]);
            MTXIdx++;
            PGObjCall(hookMdlP, hookMdlP->hsf->root);
            MTXIdx--;
            hookIdx = hookIdxOld;
            attachMotionF = i;
        }
    }
    if (*PGName == 0 && object->type == 2) {
        obj = object;
        MTXMultVec(MTXBuf[MTXIdx - 1], (Vec*) &obj->mesh.mesh.min, &pos);
        if (pos.x < PGMinPos.x) {
            PGMinPos.x = pos.x;
        }
        if (pos.y < PGMinPos.y) {
            PGMinPos.y = pos.y;
        }
        if (pos.z < PGMinPos.z) {
            PGMinPos.z = pos.z;
        }
        if (pos.x > PGMaxPos.x) {
            PGMaxPos.x = pos.x;
        }
        if (pos.y > PGMaxPos.y) {
            PGMaxPos.y = pos.y;
        }
        if (pos.z > PGMaxPos.z) {
            PGMaxPos.z = pos.z;
        }
        MTXMultVec(MTXBuf[MTXIdx - 1], (Vec*) &obj->mesh.mesh.max, &pos);
        if (pos.x < PGMinPos.x) {
            PGMinPos.x = pos.x;
        }
        if (pos.y < PGMinPos.y) {
            PGMinPos.y = pos.y;
        }
        if (pos.z < PGMinPos.z) {
            PGMinPos.z = pos.z;
        }
        if (pos.x > PGMaxPos.x) {
            PGMaxPos.x = pos.x;
        }
        if (pos.y > PGMaxPos.y) {
            PGMaxPos.y = pos.y;
        }
        if (pos.z > PGMaxPos.z) {
            PGMaxPos.z = pos.z;
        }
    }
    for (i = 0; i < object->mesh.childrenCount; i++) {
        PGObjCall(model, object->mesh.children[i]);
        if (PGFinishF) {
            return;
        }
    }
    if (applyF) {
        MTXIdx--;
    }
}

void PGObjReplica(HU3DMODEL *model, HSFOBJECT *object) {
    HSFTRANSFORM *transformP;
    Mtx mtx;
    Mtx rot;

    if (attachMotionF == FALSE) {
        transformP = &object->mesh.base;
    } else {
        transformP = &object->mesh.curr;
    }
    mtxRot(rot, transformP->rot.x, transformP->rot.y, transformP->rot.z);
    MTXScale(mtx, transformP->scale.x, transformP->scale.y, transformP->scale.z);
    MTXConcat(rot, mtx, mtx);
    mtxTransCat(mtx, transformP->pos.x, transformP->pos.y, transformP->pos.z);
    MTXConcat(MTXBuf[MTXIdx - 1], mtx, MTXBuf[MTXIdx]);
    MTXIdx++;
    CancelTRXF = TRUE;
    PGObjCall(model, object->mesh.replica);
    if (PGFinishF == FALSE) {
        CancelTRXF = FALSE;
        MTXIdx--;
    }
}

HSFOBJECT *Hu3DObjDuplicate(HSFDATA *hsf, u32 mallocNo) {
    HSFOBJECT *objBuf;
    HSFOBJECT *srcObj;
    HSFOBJECT *objPtr;
    s16 i;
    s16 j;

    objPtr = HuMemDirectMallocNum(HEAP_MODEL, hsf->objectNum * sizeof(HSFOBJECT), mallocNo);
    objBuf = objPtr;
    srcObj = hsf->object;
    memcpy(objBuf, srcObj, hsf->objectNum * sizeof(HSFOBJECT));
    for (i = 0; i < hsf->objectNum; i++, objPtr++, srcObj++) {
        if (objPtr->type != HSF_OBJ_LIGHT && objPtr->type != HSF_OBJ_CAMERA) {
            if (objPtr->mesh.parent) {
                objPtr->mesh.parent = (HSFOBJECT*) ((u8*) objBuf + ((u32) srcObj->mesh.parent - (u32) hsf->object));
            }
            objPtr->mesh.children = HuMemDirectMallocNum(HEAP_MODEL, srcObj->mesh.childrenCount * sizeof(HSFOBJECT *), mallocNo);
            if (srcObj->constData) {
                objPtr->constData = HuMemDirectMallocNum(HEAP_MODEL, sizeof(HSFCONSTDATA), mallocNo);
                memcpy(objPtr->constData, srcObj->constData, sizeof(HSFCONSTDATA));
            }
            for (j = 0; j < srcObj->mesh.childrenCount; j++) {
                objPtr->mesh.children[j] = (HSFOBJECT*) ((u8*) objBuf + ((u32) srcObj->mesh.children[j] - (u32) hsf->object));
            }
        }
    }
    return objBuf;
}

void Hu3DModelObjDrawInit(void) {
    s16 i;

    GXSetCullMode(GX_CULL_BACK);
    for (i = 0; i < 8; i++) {
        BmpPtrBak[i] = PTR_INVALID;
    }
    CancelTRXF = 0;
    hookIdx = HU3D_MODELID_NONE;
    shadingBak = -1;
    vtxModeBak = -1;
    materialBak = PTR_INVALID;
    attachMotionF = 0;
}

void Hu3DModelObjDraw(HU3DMODELID modelId, char *objName, Mtx mtx) {
    HU3DDRAWOBJ drawObj;
    HSFCONSTDATA *constData;
    HSFOBJECT *objPTR;

    drawObj.model = &Hu3DData[modelId];
    drawObj.object = objPTR = Hu3DModelObjPtrGet(modelId, objName);
    constData = objPTR->constData;
    MTXCopy(mtx, drawObj.matrix);
    drawObj.scale.x = drawObj.scale.y = drawObj.scale.z = 1.0f;
    ObjDraw(&drawObj);
}
