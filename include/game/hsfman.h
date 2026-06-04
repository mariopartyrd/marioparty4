#ifndef _GAME_HSFMAN_H
#define _GAME_HSFMAN_H

#include "game/data.h"
#include "game/hsfformat.h"
#include "game/memory.h"

// TODO rename to hu3d.h

//Max for model properties
#define HU3D_CLUSTER_MAX 4
#define HU3D_MODEL_LLIGHT_MAX 8

//Max for layer properties
#define HU3D_LAYER_HOOK_MAX 16
#define HU3D_LAYER_MAX 8
#define HU3D_LAYER_HOOK_POST 8

//Max for global buffers
#define HU3D_MODEL_MAX 512
#define HU3D_GLIGHT_MAX 8
#define HU3D_LLIGHT_MAX 48
#define HU3D_PROJ_MAX 4
#define HU3D_MOTION_MAX 256
#define HU3D_TEXANIM_MAX 256
#define HU3D_TEXSCROLL_MAX 16
#define HU3D_PARMAN_MAX 64
#define HU3D_WAVE_MAX 32

//Motion attributes
#define HU3D_MOTATTR 0x40000000
#define HU3D_MOTATTR_NONE 0
#define HU3D_MOTATTR_LOOP 0x40000001
#define HU3D_MOTATTR_PAUSE 0x40000002
#define HU3D_MOTATTR_REV 0x40000004
#define HU3D_MOTATTR_SHIFT_LOOP 0x40000008
#define HU3D_MOTATTR_SHIFT_PAUSE 0x40000010
#define HU3D_MOTATTR_SHIFT_REV 0x40000020
#define HU3D_MOTATTR_SHAPE_LOOP 0x40000040
#define HU3D_MOTATTR_SHAPE_PAUSE 0x40000080
#define HU3D_MOTATTR_SHAPE_REV 0x40000100
#define HU3D_MOTATTR_OVL_LOOP 0x40000200
#define HU3D_MOTATTR_OVL_PAUSE 0x40000400
#define HU3D_MOTATTR_OVL_REV 0x40000800

#define HU3D_CLUSTER_ATTR ((s32)0xC0000000)
#define HU3D_CLUSTER_ATTR_LOOP ((s32)0xC0000001)
#define HU3D_CLUSTER_ATTR_PAUSE ((s32)0xC0000002)
#define HU3D_CLUSTER_ATTR_REV ((s32)0xC0000004)

#define HU3D_ATTR_NONE 0

#define HU3D_ATTR_DISPOFF 0x1
#define HU3D_ATTR_ZWRITE_OFF 0x2
#define HU3D_ATTR_SHADOW 0x4
#define HU3D_ATTR_MOTION_OFF 0x8
#define HU3D_ATTR_HOOKFUNC 0x10
#define HU3D_ATTR_PARTICLE_KILL 0x20
#define HU3D_ATTR_TEX_NEAR 0x40
#define HU3D_ATTR_ENVELOPE_OFF 0x80
#define HU3D_ATTR_MOT_SLOW 0x100
#define HU3D_ATTR_TOON_MAP 0x200
#define HU3D_ATTR_CLUSTER_ON 0x400
#define HU3D_ATTR_MOT_EXEC 0x800
#define HU3D_ATTR_LLIGHT 0x1000
#define HU3D_ATTR_CAMERA_MOTON 0x2000
#define HU3D_ATTR_NOCULL 0x4000
#define HU3D_ATTR_HOOK 0x8000
#define HU3D_ATTR_CAMERA 0x10000
#define HU3D_ATTR_HILITE 0x20000
#define HU3D_ATTR_TPLVL_SET 0x40000
#define HU3D_ATTR_CURVE_MOTOFF 0x80000
#define HU3D_ATTR_LINK 0x100000
#define HU3D_ATTR_NOPAUSE 0x200000
#define HU3D_ATTR_ZCMP_OFF 0x400000
#define HU3D_ATTR_CULL_FRONT 0x800000

#define HU3D_CAM0 (1 << 0)
#define HU3D_CAM1 (1 << 1)
#define HU3D_CAM2 (1 << 2)
#define HU3D_CAM3 (1 << 3)
#define HU3D_CAM4 (1 << 4)
#define HU3D_CAM5 (1 << 5)
#define HU3D_CAM6 (1 << 6)
#define HU3D_CAM7 (1 << 7)
#define HU3D_CAM8 (1 << 8)
#define HU3D_CAM9 (1 << 9)
#define HU3D_CAM10 (1 << 10)
#define HU3D_CAM11 (1 << 11)
#define HU3D_CAM12 (1 << 12)
#define HU3D_CAM13 (1 << 13)
#define HU3D_CAM14 (1 << 14)
#define HU3D_CAM15 (1 << 15)
#define HU3D_CAM_MAX 16

//Reflection types
#define HU3D_REFLECT_TYPE_NONE -1
#define HU3D_REFLECT_TYPE_METAL 0
#define HU3D_REFLECT_TYPE_GROUND 1
#define HU3D_REFLECT_TYPE_ROOM 2
#define HU3D_REFLECT_TYPE_OCEAN 3
#define HU3D_REFLECT_TYPE_LAND 4

//Particle Blend Modes
#define HU3D_PARTICLE_BLEND_NORMAL 0
#define HU3D_PARTICLE_BLEND_ADDCOL 1
#define HU3D_PARTICLE_BLEND_INVCOL 2

//Special IDs
#define HU3D_MODELID_NONE -1
#define HU3D_MOTID_NONE -1
#define HU3D_LIGHTID_NONE -1
#define HU3D_PROJID_NONE -1
#define HU3D_ANIMID_NONE -1
#define HU3D_TEXSCRID_NONE -1
#define HU3D_CLUSTER_NONE -1
#define HU3D_PARMANID_NONE -1

//HSFCONSTDATA attribute values
#define HU3D_CONST_NONE 0
#define HU3D_CONST_XLU (1 << 0)
#define HU3D_CONST_KCOLOR_XLU (1 << 1)
#define HU3D_CONST_REFLECT (1 << 2)
#define HU3D_CONST_SHADOW_MAP (1 << 3)
#define HU3D_CONST_FORCE_POSX (1 << 4)
#define HU3D_CONST_FORCE_POSY (1 << 5)
#define HU3D_CONST_FORCE_POSZ (1 << 6)
#define HU3D_CONST_FORCE_ROTX (1 << 7)
#define HU3D_CONST_FORCE_ROTY (1 << 8)
#define HU3D_CONST_FORCE_ROTZ (1 << 9)
#define HU3D_CONST_SHADOW (1 << 10)
#define HU3D_CONST_ALTBLEND (1 << 11)
#define HU3D_CONST_LOCK (1 << 12)
#define HU3D_CONST_DISPOFF (1 << 13)
#define HU3D_CONST_XLUVERTEX (1 << 14)
#define HU3D_CONST_HILITE (1 << 15)
#define HU3D_CONST_NEAR (1 << 16)
#define HU3D_CONST_MATHOOK (1 << 17)
#define HU3D_CONST_REFLECTMODEL (1 << 18)

#define HU3D_LIGHT_TYPE_SPOT 0
#define HU3D_LIGHT_TYPE_INFINITYT 1
#define HU3D_LIGHT_TYPE_POINT 2
#define HU3D_LIGHT_TYPE_STATIC 0x8000
#define HU3D_LIGHT_TYPE_NONE -1

#define Hu3DModelCreateFile(data_id) (Hu3DModelCreate(HuDataSelHeapReadNum((data_id), HU_MEMNUM_OVL, HEAP_MODEL)))
#define Hu3DMotionCreateFile(data_id) (Hu3DMotionCreate(HuDataSelHeapReadNum((data_id), HU_MEMNUM_OVL, HEAP_MODEL)))
#define Hu3DJointMotionFile(model, data_id) (Hu3DJointMotion((model), HuDataSelHeapReadNum((data_id), HU_MEMNUM_OVL, HEAP_MODEL)))


//Typedefs for various IDs
typedef s16 HU3DMODELID;
typedef s16 HU3DMOTID;
typedef s16 HU3DPROJID;
typedef s16 HU3DLIGHTID;
typedef s16 HU3DLLIGHTID;
typedef s16 HU3DPARMANID;
typedef s16 HU3DANIMID;
typedef s16 HU3DTEXSCRID;

//Forward declarations
typedef struct Hu3DModel_s HU3DMODEL;
typedef struct Hu3DDrawObj_s HU3DDRAWOBJ;
typedef struct Hu3DParticle_s HU3DPARTICLE;

//Function pointer declarations
typedef void (*HU3DLAYERHOOK)(s16 layerNo);
typedef void (*HU3DMODELHOOK)(HU3DMODEL *modelP, Mtx mtx);
typedef void (*HU3DTIMINGHOOK)(HU3DMODELID modelId, HU3DMOTID motId, BOOL lagF);
typedef void (*HU3DMATHOOK)(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material);
typedef void (*HU3DPARTICLEHOOK)(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);

typedef struct hsf_draw_object {
    /* 0x00 */ HU3DMODEL *model;
    /* 0x04 */ HSFOBJECT *object;
    /* 0x08 */ float z;
    /* 0x0C */ Mtx matrix;
    /* 0x3C */ Vec scale;
} HU3DDRAWOBJ;

typedef struct hsfdraw_struct_01 {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ HSFBITMAP *unk3C;
    /* 0x40 */ char unk40[4];
} HsfdrawStruct01; // Size 0x44

typedef struct hsf_draw_data {
    s32 dlOfs;
    s32 dlSize;
    u16 polyCnt;
    u32 flags;
} HsfDrawData;

typedef struct hsf_const_data {
    u32 flags;
    s16 hook;
    HsfDrawData *drawData;
    void *dlBuf;
    Mtx matrix;
    ANIMDATA *hiliteMap;
} HsfConstData;

typedef struct Hu3DMotWork_s {
    float time;
    float speed;
    float start;
    float end;
} HU3DMOTWORK;

struct Hu3DModel_s {
    u8 tick;
    u8 camInfoBit;
    u8 projBit;
    u8 hiliteIdx;
    s8 reflectType;
    s16 layerNo;
    s16 motId;
    s16 motIdOvl;
    s16 motIdShift;
    s16 motIdShape;
    s16 motIdCluster[HU3D_CLUSTER_MAX];
    s16 clusterAttr[HU3D_CLUSTER_MAX];
    s16 motIdSrc;
    u16 cameraBit;
    s16 linkMdlId;
    u16 lightNum;
    u16 lightId[HU3D_GLIGHT_MAX];
    s16 lLightId[HU3D_MODEL_LLIGHT_MAX];
    u32 mallocNo;
    u32 mallocNoLink;
    u32 attr;
    u32 motAttr;
    float ambR;
    float ambB;
    float ambG;
    HU3DMOTWORK motWork;
    HU3DMOTWORK motOvlWork;
    HU3DMOTWORK motShiftWork;
    HU3DMOTWORK motShapeWork;
    float clusterTime[HU3D_CLUSTER_MAX];
    float clusterSpeed[HU3D_CLUSTER_MAX];
    union {
        HSFDATA *hsf;
        HU3DMODELHOOK hookFunc;
    };
    HSFDATA *hsfLink;
    HuVecF pos;
    HuVecF rot;
    HuVecF scale;
    Mtx mtx;
    void *hookData;
}; // sizeof 0x124

typedef struct Hu3DCamera_s {
    float fov;
    float near;
    float far;
    float aspect;
    float upRot;
    HuVecF pos;
    HuVecF up;
    HuVecF target;
    s16 scissorX;
    s16 scissorY;
    s16 scissorW;
    s16 scissorH;
    float viewportX;
    float viewportY;
    float viewportW;
    float viewportH;
    float viewportNear;
    float viewportFar;
} HU3DCAMERA; // sizeof 0x58

typedef struct Hu3DProjection_s {
    u8 alpha;
    ANIMDATA *anim;
    float fov;
    float nnear;
    float ffar;
    HuVecF camPos;
    HuVecF camTarget;
    HuVecF camUp;
    Mtx lookAtMtx;
    Mtx projMtx;
} HU3DPROJECTION; // sizeof 0x98

typedef struct Hu3DShadow_s {
    u8 alpha;
    u16 size;
    void *buf;
    float fov;
    float nnear;
    float ffar;
    HuVecF camPos;
    HuVecF camTarget;
    HuVecF camUp;
    Mtx lookAtMtx;
    Mtx projMtx;
} HU3DSHADOW; // sizeof 0x98

typedef struct Hu3DLight_s {
    s16 type;
    s16 func;
    float cutoff;
    float brightness;
    char unk_0C[16];
    HuVecF pos;
    HuVecF dir;
    HuVecF unk_34;
    GXColor color;
} HU3DLIGHT;

typedef struct motion_data {
    s16 unk_00;
    s16 unk_02;
    HSFDATA *unk_04;
} MotionData;

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ HSFBITMAP *unk04;
} UnknownHsfMotionStruct01; // Size 8

typedef struct Hu3DParticleData_s {
    /* 0x00 */ s16 time;
    /* 0x02 */ s16 parManId;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 cameraBit;
    /* 0x08 */ HuVecF vel;
    /* 0x14 */ HuVecF accel;
    /* 0x20 */ float speedDecay;
    /* 0x24 */ float colorIdx;
    /* 0x28 */ float scaleBase;
    /* 0x2C */ float scale;
    /* 0x30 */ float zRot;
    /* 0x34 */ HuVecF pos;
    /* 0x40 */ GXColor color;
} HU3DPARTICLEDATA; // Size 0x44

struct Hu3DParticle_s {
    /* 0x00 */ s16 dataCnt;
    /* 0x02 */ s16 emitCnt;
    /* 0x04 */ HuVecF pos;
    /* 0x04 */ HuVecF unk_10;
    /* 0x1C */ void *work;
    /* 0x20 */ s16 animBank;
    /* 0x22 */ s16 animNo;
    /* 0x24 */ float animSpeed;
    /* 0x28 */ float animTime;
    /* 0x2C */ u8 blendMode;
    /* 0x2D */ u8 attr;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 maxCnt;
    /* 0x34 */ u32 count;
    /* 0x38 */ s32 prevCounter;
    /* 0x3C */ u32 prevCount;
    /* 0x40 */ u32 dlSize;
    /* 0x44 */ ANIMDATA *anim;
    /* 0x48 */ HU3DPARTICLEDATA *data;
    /* 0x4C */ HuVecF *vtxBuf;
    /* 0x50 */ void *dlBuf;
    /* 0x54 */ HU3DPARTICLEHOOK hook;
}; // Size 0x58

typedef struct Hu3DParmanParam_s {
    /* 0x00 */ s16 maxTime;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ float accelRange;
    /* 0x08 */ float scaleRange;
    /* 0x0C */ float angleRange;
    /* 0x10 */ HuVecF gravity;
    /* 0x1C */ float speedBase;
    /* 0x20 */ float speedDecay;
    /* 0x24 */ float scaleBase;
    /* 0x28 */ float scaleDecay;
    /* 0x2C */ s16 colorNum;
    /* 0x2E */ GXColor colorStart[4];
    /* 0x3E */ GXColor colorEnd[4];
} HU3DPARMANPARAM; // Size 0x4E

typedef struct Hu3DTexAnim_s {
    /* 0x00 */ u16 attr;
    /* 0x02 */ s16 bank;
    /* 0x04 */ s16 anmNo;
    /* 0x06 */ s16 modelId;
    /* 0x08 */ float time;
    /* 0x0C */ float speed;
    /* 0x10 */ ANIMDATA *anim;
} HU3DTEXANIM; // Size 0x14

typedef struct Hu3DTexScroll_s {
    /* 0x00 */ u16 attr;
    /* 0x02 */ s16 modelId;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF scale;
    /* 0x1C */ HuVecF posMove;
    /* 0x28 */ HuVecF scaleMove;
    /* 0x34 */ float rot;
    /* 0x38 */ float rotMove;
    /* 0x3C */ Mtx texMtx;
} HU3DTEXSCROLL; // Size 0x6C

extern void GXWaitDrawDone(); /* extern */
extern void GXInitSpecularDir(GXLightObj *, float, float, float);

void Hu3DDrawPreInit(void);
void Hu3DDraw(HU3DMODEL *arg0, Mtx arg1, Vec *arg2);
s32 ObjCullCheck(HSFDATA *arg0, HSFOBJECT *arg1, Mtx arg2);
void Hu3DDrawPost(void);
void MakeDisplayList(s16 arg0, u32 arg1);
HsfConstData *ObjConstantMake(HSFOBJECT *arg0, u32 arg1);
void mtxTransCat(Mtx arg0, float arg1, float arg2, float arg3);
void mtxRotCat(Mtx arg0, float arg1, float arg2, float arg3);
void mtxRot(Mtx arg0, float arg1, float arg2, float arg3);
void mtxScaleCat(Mtx arg0, float arg1, float arg2, float arg3);
s16 HmfInverseMtxF3X3(Mtx arg0, Mtx arg1);
void SetDefLight(Vec *arg0, Vec *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA);
void Hu3DModelObjPosGet(s16 arg0, char *arg1, Vec *arg2);
void Hu3DModelObjMtxGet(s16 arg0, char *arg1, Mtx arg2);
void PGObjCall(HU3DMODEL *arg0, HSFOBJECT *arg1);
void PGObjCalc(HU3DMODEL *arg0, HSFOBJECT *arg1);
void PGObjReplica(HU3DMODEL *arg0, HSFOBJECT *arg1);
HSFOBJECT *Hu3DObjDuplicate(HSFDATA *arg0, u32 arg1);
void Hu3DModelObjDrawInit(void);
void Hu3DModelObjDraw(s16 arg0, char *arg1, Mtx arg2);

void Hu3DInit(void);
void Hu3DPreProc(void);
void Hu3DExec(void);
void Hu3DAllKill(void);
void Hu3DBGColorSet(u8 r, u8 g, u8 b);
void Hu3DLayerHookSet(s16 layerNo, HU3DLAYERHOOK hookFunc);
void Hu3DPauseSet(BOOL pauseF);
void Hu3DNoSyncSet(BOOL noSync);
s16 Hu3DModelCreate(void *);
s16 Hu3DModelLink(s16);
s16 Hu3DHookFuncCreate(HU3DMODELHOOK);
void Hu3DModelKill(s16);
void Hu3DModelAllKill(void);
void Hu3DModelPosSet(s16, float, float, float);
void Hu3DModelPosSetV(s16, HuVecF *);
void Hu3DModelRotSet(s16, float, float, float);
void Hu3DModelRotSetV(s16, HuVecF *);
void Hu3DModelScaleSet(s16, float, float, float);
void Hu3DModelScaleSetV(s16, HuVecF *);
void Hu3DModelAttrSet(s16, u32);
void Hu3DModelAttrReset(s16, u32);
u32 Hu3DModelAttrGet(s16);
u32 Hu3DModelMotionAttrGet(s16);
void Hu3DModelClusterAttrSet(s16, s16, s32);
void Hu3DModelClusterAttrReset(s16, s16, s32);
void Hu3DModelCameraSet(s16, u16);
void Hu3DModelLayerSet(s16, s16);
HSFOBJECT *Hu3DModelObjPtrGet(s16, char *);
void Hu3DModelTPLvlSet(s16, float);
void Hu3DModelHiliteMapSet(s16, ANIMDATA *);
void Hu3DModelShadowSet(s16);
void Hu3DModelShadowReset(s16);
void Hu3DModelShadowDispOn(s16);
void Hu3DModelShadowDispOff(s16);
void Hu3DModelShadowMapSet(s16);
void Hu3DModelShadowMapObjSet(s16, char *);
void Hu3DModelAmbSet(s16, float, float, float);
void Hu3DModelHookSet(s16, char *, s16);
void Hu3DModelHookReset(s16);
void Hu3DModelHookObjReset(s16, char *);
void Hu3DModelProjectionSet(s16, s16);
void Hu3DModelProjectionReset(s16, s16);
void Hu3DModelHiliteTypeSet(s16, s16);
void Hu3DModelReflectTypeSet(s16, s16);
void Hu3DCameraCreate(s32);
void Hu3DCameraPerspectiveSet(s32, float, float, float, float);
void Hu3DCameraViewportSet(s32, float, float, float, float, float, float);
void Hu3DCameraScissorSet(s32, u32, u32, u32, u32);
void Hu3DCameraPosSet(s32, float, float, float, float, float, float, float, float, float);
void Hu3DCameraPosSetV(s32 cam, HuVecF *pos, HuVecF *up, HuVecF *target);
void Hu3DCameraKill(s32);
void Hu3DCameraAllKill(void);
void Hu3DCameraSet(s32, Mtx);
BOOL Hu3DModelCameraInfoSet(s16, u16);
s16 Hu3DModelCameraCreate(s16, u16);
void Hu3DCameraMotionOn(s16, s8);
void Hu3DCameraMotionStart(s16, u16);
void Hu3DCameraMotionOff(s16);
void Hu3DLighInit(void);
s16 Hu3DGLightCreate(float, float, float, float, float, float, u8, u8, u8);
s16 Hu3DGLightCreateV(HuVecF *, HuVecF *, GXColor *);
s16 Hu3DLLightCreate(s16, float, float, float, float, float, float, u8, u8, u8);
s16 Hu3DLLightCreateV(s16, HuVecF *, HuVecF *, GXColor *);
void Hu3DGLightSpotSet(s16, float, u16);
void Hu3DLLightSpotSet(s16, s16, float, u16);
void Hu3DGLightInfinitytSet(s16);
void Hu3DLLightInfinitytSet(s16, s16);
void Hu3DGLightPointSet(s16, float, float, u16);
void Hu3DLLightPointSet(s16, s16, float, float, u16);
void Hu3DGLightKill(s16);
void Hu3DLLightKill(s16, s16);
void Hu3DLightAllKill(void);
void Hu3DGLightColorSet(s16, u8, u8, u8, u8);
void Hu3DLLightColorSet(s16, s16, u8, u8, u8, u8);
void Hu3DGLightPosSetV(s16, HuVecF *, HuVecF *);
void Hu3DLLightPosSetV(s16, s16, HuVecF *, HuVecF *);
void Hu3DGLightPosSet(s16, float, float, float, float, float, float);
void Hu3DLLightPosSet(s16, s16, float, float, float, float, float, float);
void Hu3DGLightPosAimSetV(s16, HuVecF *, HuVecF *);
void Hu3DLLightPosAimSetV(s16, s16, HuVecF *, HuVecF *);
void Hu3DGLightPosAimSet(s16, float, float, float, float, float, float);
void Hu3DLLightPosAimSet(s16, s16, float, float, float, float, float, float);
void Hu3DGLightStaticSet(s16, s32);
void Hu3DLLightStaticSet(s16, s16, s32);
s32 Hu3DModelLightInfoSet(s16, s16);
s16 Hu3DLightSet(HU3DMODEL *, Mtx *, Mtx *, float);
void lightSet(HU3DLIGHT *arg0, s16 arg1, Mtx *arg2, Mtx *arg3, float arg8);
#ifndef __MWERKS__
void Hu3DReflectMapSet(ANIMDATA* arg0);
#endif
void Hu3DReflectNoSet(s16 arg0);
void Hu3DFogSet(float, float, u8, u8, u8);
void Hu3DFogClear(void);
void Hu3DShadowCreate(float, float, float);
void Hu3DShadowPosSet(HuVecF *, HuVecF *, HuVecF *);
void Hu3DShadowTPLvlSet(float);
void Hu3DShadowSizeSet(u16);
void Hu3DShadowExec(void);
s16 Hu3DProjectionCreate(void *, float, float, float);
void Hu3DProjectionKill(s16);
void Hu3DProjectionPosSet(s16, HuVecF *, HuVecF *, HuVecF *);
void Hu3DProjectionTPLvlSet(s16, float);
void Hu3DMipMapSet(char *, s16, char *, float);

void Hu3DMotionInit(void);
s16 Hu3DMotionCreate(void *arg0);
s16 Hu3DMotionModelCreate(s16 arg0);
s32 Hu3DMotionKill(s16 arg0);
void Hu3DMotionAllKill(void);
void Hu3DMotionSet(s16 arg0, s16 arg1);
void Hu3DMotionOverlaySet(s16 arg0, s16 arg1);
void Hu3DMotionOverlayReset(s16 arg0);
float Hu3DMotionOverlayTimeGet(s16 arg0);
void Hu3DMotionOverlayTimeSet(s16 arg0, float arg1);
void Hu3DMotionOverlaySpeedSet(s16 arg0, float arg1);
void Hu3DMotionShiftSet(s16 arg0, s16 arg1, float arg2, float arg3, u32 arg4);
void Hu3DMotionShapeSet(s16 arg0, s16 arg1);
s16 Hu3DMotionShapeIDGet(s16 arg0);
void Hu3DMotionShapeSpeedSet(s16 arg0, float arg1);
void Hu3DMotionShapeTimeSet(s16 arg0, float arg1);
float Hu3DMotionShapeMaxTimeGet(s16 arg0);
void Hu3DMotionShapeStartEndSet(s16 arg0, float arg1, float arg2);
s16 Hu3DMotionClusterSet(s16 arg0, s16 arg1);
s16 Hu3DMotionClusterNoSet(s16 arg0, s16 arg1, s16 arg2);
void Hu3DMotionShapeReset(s16 arg0);
void Hu3DMotionClusterReset(s16 arg0, s16 arg1);
s16 Hu3DMotionIDGet(s16 arg0);
s16 Hu3DMotionShiftIDGet(s16 arg0);
void Hu3DMotionTimeSet(s16 arg0, float arg1);
float Hu3DMotionTimeGet(s16 arg0);
float Hu3DMotionShiftTimeGet(s16 arg0);
float Hu3DMotionMaxTimeGet(s16 arg0);
float Hu3DMotionShiftMaxTimeGet(s16 arg0);
void Hu3DMotionShiftStartEndSet(s16 arg0, float arg1, float arg2);
float Hu3DMotionMotionMaxTimeGet(s16 arg0);
void Hu3DMotionStartEndSet(s16 arg0, float arg1, float arg2);
s32 Hu3DMotionEndCheck(s16 arg0);
void Hu3DMotionSpeedSet(s16 arg0, float arg1);
void Hu3DMotionShiftSpeedSet(s16 arg0, float arg1);
void Hu3DMotionNoMotSet(s16 arg0, char *arg1, u32 arg2);
void Hu3DMotionNoMotReset(s16 arg0, char *arg1, u32 arg2);
void Hu3DMotionForceSet(s16 arg0, char *arg1, u32 arg2, float arg3);
void Hu3DMotionNext(s16 arg0);
void Hu3DMotionExec(s16 arg0, s16 arg1, float arg2, s32 arg3);
void Hu3DCameraMotionExec(s16 arg0);
void Hu3DSubMotionExec(s16 arg0);
float *GetObjTRXPtr(HSFOBJECT *arg0, u16 arg1);
void SetObjMatMotion(s16 arg0, HSFTRACK *arg1, float arg2);
void SetObjAttrMotion(s16 arg0, HSFTRACK *arg1, float arg2);
void SetObjCameraMotion(s16 arg0, HSFTRACK *arg1, float arg2);
void SetObjLightMotion(s16 arg0, HSFTRACK *arg1, float arg2);
float GetCurve(HSFTRACK *arg0, float arg1);
float GetConstant(s32 arg0, float *arg1, float arg2);
float GetLinear(s32 arg0, float arg1[][2], float arg2);
float GetBezier(s32 arg0, HSFTRACK *arg1, float arg2);
HSFBITMAP *GetBitMap(s32 arg0, UnknownHsfMotionStruct01 *arg1, float arg2);
s16 Hu3DJointMotion(s16 arg0, void *arg1);
void JointModel_Motion(s16 arg0, s16 arg1);
void Hu3DMotionCalc(s16 arg0);

void Hu3DAnimInit(void);
s16 Hu3DAnimCreate(void *dataP, s16 modelId, char *bmpName);
s16 Hu3DAnimLink(s16 linkAnimId, s16 modelId, char *bmpName);
void Hu3DAnimKill(s16 animId);
void Hu3DAnimModelKill(s16 modelId);
void Hu3DAnimAllKill(void);
void Hu3DAnimAttrSet(s16 animId, u16 attr);
void Hu3DAnimAttrReset(s16 animId, s32 attr);
void Hu3DAnimSpeedSet(s16 animId, float speed);
void Hu3DAnimBankSet(s16 animId, s32 bank);
void Hu3DAnmNoSet(s16 animId, u16 anmNo);
s32 Hu3DAnimSet(HU3DMODEL *arg0, HSFATTRIBUTE *arg1, s16 arg2);
void Hu3DAnimExec(void);
s16 Hu3DTexScrollCreate(s16 modelId, char *bmpName);
void Hu3DTexScrollKill(s16 texSrcId);
void Hu3DTexScrollAllKill(void);
void Hu3DTexScrollPosSet(s16 texScrId, float posX, float posY, float posZ);
void Hu3DTexScrollPosMoveSet(s16 texScrId, float posX, float posY, float posZ);
void Hu3DTexScrollRotSet(s16 texScrId, float rot);
void Hu3DTexScrollRotMoveSet(s16 texScrId, float rot);
void Hu3DTexScrollPauseDisableSet(s16 texScrId, BOOL pauseDisableF);
s16 Hu3DParticleCreate(ANIMDATA *anim, s16 maxCnt);
void Hu3DParticleScaleSet(s16 modelId, float scale);
void Hu3DParticleZRotSet(s16 modelId, float zRot);
void Hu3DParticleColSet(s16 modelId, u8 r, u8 g, u8 b);
void Hu3DParticleTPLvlSet(s16 modelId, float tpLvl);
void Hu3DParticleBlendModeSet(s16 modelId, u8 blendMode);
void Hu3DParticleHookSet(s16 modelId, HU3DPARTICLEHOOK hook);
void Hu3DParticleAttrSet(s16 modelId, u8 attr);
void Hu3DParticleAttrReset(s16 modelId, u8 attr);
void Hu3DParticleCntSet(s16 modelId, s16 count);
void Hu3DParticleAnimModeSet(s16 modelId, s16 animBank);
void Hu3DParManInit(void);
s16 Hu3DParManCreate(ANIMDATA *anim, s16 maxCnt, HU3DPARMANPARAM *param);
s16 Hu3DParManLink(s16 linkParManId, HU3DPARMANPARAM *param);
void Hu3DParManKill(s16 parManId);
void Hu3DParManAllKill(void);
void *Hu3DParManPtrGet(s16 parManId);
void Hu3DParManPosSet(s16 parManId, float posX, float posY, float posZ);
void Hu3DParManVecSet(s16 parManId, float x, float y, float z);
void Hu3DParManRotSet(s16 parManId, float rotX, float rotY, float rotZ);
void Hu3DParManAttrSet(s16 parManId, s32 attr);
void Hu3DParManAttrReset(s16 parManId, s32 attr);
s16 Hu3DParManModelIDGet(s16 parManId);
void Hu3DParManTimeLimitSet(s16 parManId, s32 timeLimit);
void Hu3DParManVacumeSet(s16 parManId, float x, float y, float z, float speed);
void Hu3DParManColorSet(s16 parManId, s16 color);

extern Vec PGMaxPos;
extern Vec PGMinPos;
extern u32 totalPolyCnt;
extern u32 totalPolyCnted;
extern u32 totalMatCnt;
extern u32 totalMatCnted;
extern u32 totalTexCnt;
extern u32 totalTexCnted;
extern u32 totalTexCacheCnt;
extern u32 totalTexCacheCnted;

extern HU3DMODEL Hu3DData[0x200];
extern HU3DCAMERA Hu3DCamera[0x10];
extern ANIMDATA *reflectAnim[5];
extern ANIMDATA *hiliteAnim[4];
extern HU3DPROJECTION Hu3DProjection[4];
extern HU3DSHADOW Hu3DShadowData;
extern Mtx Hu3DCameraMtx;
extern Mtx Hu3DCameraMtxXPose;
extern HU3DLIGHT Hu3DGlobalLight[0x8];
extern s16 reflectMapNo;
extern ANIMDATA *toonAnim;
extern s16 Hu3DShadowCamBit;
extern s32 Hu3DShadowF;
extern s32 shadowModelDrawF;
extern s16 Hu3DCameraNo;
extern s16 Hu3DCameraBit;
extern s16 Hu3DPauseF;
extern GXColor BGColor;

extern MotionData Hu3DMotion[256];

extern HU3DTEXANIM Hu3DTexAnimData[HU3D_TEXANIM_MAX];
extern HU3DTEXSCROLL Hu3DTexScrData[HU3D_TEXSCROLL_MAX];

#endif
