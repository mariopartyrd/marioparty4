#ifndef _GAME_HSFMAN_H
#define _GAME_HSFMAN_H

#include "game/data.h"
#include "game/hsfanim.h"
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

#define Hu3DModelCreateFile(data_id) (Hu3DModelCreate(HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))

typedef s16 HU3DMODELID;
typedef s16 HU3DMOTID;
typedef s16 HU3DPROJID;
typedef s16 HU3DLIGHTID;
typedef s16 HU3DLLIGHTID;
typedef s16 HU3DPARMANID;
typedef s16 HU3DANIMID;
typedef s16 HU3DTEXSCRID;

typedef struct Hu3DModel_s HU3DMODEL;
typedef struct Hu3DParticle_s HU3DPARTICLE;

typedef void (*HU3DLAYERHOOK)(s16 layerNo);
typedef void (*HU3DMODELHOOK)(HU3DMODEL *, Mtx);

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

extern void GXWaitDrawDone(); /* extern */
extern void GXInitSpecularDir(GXLightObj *, float, float, float);

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

#endif
