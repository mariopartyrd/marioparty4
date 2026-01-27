#ifndef _GAME_HSFMAN_H
#define _GAME_HSFMAN_H

#include "game/data.h"
#include "game/hsfanim.h"
#include "game/hsfformat.h"
#include "game/memory.h"
#include "version.h"

#define HU3D_MODEL_MAX 512
#define HU3D_MOTION_MAX 256
#define HU3D_TEXANIM_MAX 256
#define HU3D_TEXSCROLL_MAX 16

#define HU3D_MOTATTR_NONE 0
#define HU3D_MOTATTR 0x40000000

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

#define Hu3DModelCreateFile(data_id) (Hu3DModelCreate(HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))

typedef struct model_data ModelData;
typedef struct particle_data ParticleData;

typedef void (*ModelHookFunc)(struct model_data *, Mtx);

struct model_data {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    s8 unk_04;
    s8 unk_05;
    s16 layer;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10[4];
    s16 cluster_attr[4];
    s16 unk_20;
    u16 camera;
    s16 unk_24;
    u16 unk_26;
    u16 unk_28[8];
    s16 unk_38[8];
    uintptr_t unk_48;
    uintptr_t unk_4C;
    u32 attr;
    u32 motion_attr;
    Vec unk_58;
    float unk_64;
    float unk_68;
    float unk_6C;
    float unk_70;
    float unk_74;
    float unk_78;
    float unk_7C;
    float unk_80;
    float unk_84;
    float unk_88;
    float unk_8C;
    float unk_90;
    float unk_94;
    float unk_98;
    float unk_9C;
    float unk_A0;
    float unk_A4[4];
    float unk_B4[4];
    union {
        HsfData *hsfData;
        ModelHookFunc hook;
    };
    HsfData *unk_C8;
    Vec pos;
    Vec rot;
    Vec scale;
    Mtx unk_F0;
    void *unk_120;
}; // sizeof 0x124
typedef struct camera_data {
    float fov;
    float nnear;
    float ffar;
    float aspect;
    float aspect_dupe;
    Vec pos;
    Vec up;
    Vec target;
    s16 scissor_x;
    s16 scissor_y;
    s16 scissor_w;
    s16 scissor_h;
    float viewport_x;
    float viewport_y;
    float viewport_w;
    float viewport_h;
    float near_z;
    float far_z;
} CameraData; // sizeof 0x58
typedef struct ThreeDProjectionStruct {
    u8 unk_00;
    char unk_01[0x3];
    void *unk_04;
    Vec unk_08;
    Vec unk_14;
    Vec unk_20;
    Vec unk_2C;
    Mtx unk_38;
    Mtx unk_68;
} ThreeDProjectionStruct; // sizeof 0x98
typedef struct shadow_data {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    void *unk_04;
    Vec unk_08;
    Vec unk_14;
    Vec unk_20;
    Vec unk_2C;
    Mtx unk_38;
    Mtx unk_68;
} ShadowData; // sizeof 0x98
typedef struct light_data {
    s16 unk_00;
    s16 unk_02;
    float unk_04;
    float unk_08;
    char unk_0C[0x10];
    Vec unk_1C;
    Vec unk_28;
    Vec unk_34;
    GXColor color;
} LightData;

extern void GXWaitDrawDone(); /* extern */
extern void GXInitSpecularDir(GXLightObj *, float, float, float);

void Hu3DInit(void);
void Hu3DPreProc(void);
void Hu3DExec(void);
void Hu3DAllKill(void);
void Hu3DBGColorSet(u8, u8, u8);
void Hu3DLayerHookSet(s16, void (*)(s16));
void Hu3DPauseSet(s32);
void Hu3DNoSyncSet(s32);
s16 Hu3DModelCreate(void *);
s16 Hu3DModelLink(s16);
s16 Hu3DHookFuncCreate(ModelHookFunc);
void Hu3DModelKill(s16);
void Hu3DModelAllKill(void);
void Hu3DModelPosSet(s16, float, float, float);
void Hu3DModelPosSetV(s16, Vec *);
void Hu3DModelRotSet(s16, float, float, float);
void Hu3DModelRotSetV(s16, Vec *);
void Hu3DModelScaleSet(s16, float, float, float);
void Hu3DModelScaleSetV(s16, Vec *);
void Hu3DModelAttrSet(s16, u32);
void Hu3DModelAttrReset(s16, u32);
u32 Hu3DModelAttrGet(s16);
u32 Hu3DModelMotionAttrGet(s16);
void Hu3DModelClusterAttrSet(s16, s16, s32);
void Hu3DModelClusterAttrReset(s16, s16, s32);
void Hu3DModelCameraSet(s16, u16);
void Hu3DModelLayerSet(s16, s16);
HsfObject *Hu3DModelObjPtrGet(s16, char *);
void Hu3DModelTPLvlSet(s16, float);
void Hu3DModelHiliteMapSet(s16, AnimData *);
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
void Hu3DCameraPosSetV(s32 cam, Vec *pos, Vec *up, Vec *target);
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
s16 Hu3DGLightCreateV(Vec *, Vec *, GXColor *);
s16 Hu3DLLightCreate(s16, float, float, float, float, float, float, u8, u8, u8);
s16 Hu3DLLightCreateV(s16, Vec *, Vec *, GXColor *);
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
void Hu3DGLightPosSetV(s16, Vec *, Vec *);
void Hu3DLLightPosSetV(s16, s16, Vec *, Vec *);
void Hu3DGLightPosSet(s16, float, float, float, float, float, float);
void Hu3DLLightPosSet(s16, s16, float, float, float, float, float, float);
void Hu3DGLightPosAimSetV(s16, Vec *, Vec *);
void Hu3DLLightPosAimSetV(s16, s16, Vec *, Vec *);
void Hu3DGLightPosAimSet(s16, float, float, float, float, float, float);
void Hu3DLLightPosAimSet(s16, s16, float, float, float, float, float, float);
void Hu3DGLightStaticSet(s16, s32);
void Hu3DLLightStaticSet(s16, s16, s32);
s32 Hu3DModelLightInfoSet(s16, s16);
s16 Hu3DLightSet(ModelData *, Mtx *, Mtx *, float);
void lightSet(LightData *arg0, s16 arg1, Mtx *arg2, Mtx *arg3, float arg8);
#ifndef __MWERKS__
void Hu3DReflectMapSet(AnimData* arg0);
#endif
void Hu3DReflectNoSet(s16 arg0);
void Hu3DFogSet(float, float, u8, u8, u8);
void Hu3DFogClear(void);
void Hu3DShadowCreate(float, float, float);
void Hu3DShadowPosSet(Vec *, Vec *, Vec *);
void Hu3DShadowTPLvlSet(float);
void Hu3DShadowSizeSet(u16);
void Hu3DShadowExec(void);
s16 Hu3DProjectionCreate(void *, float, float, float);
void Hu3DProjectionKill(s16);
void Hu3DProjectionPosSet(s16, Vec *, Vec *, Vec *);
void Hu3DProjectionTPLvlSet(s16, float);
void Hu3DMipMapSet(char *, s16, s32, float);

SHARED_SYM extern ModelData Hu3DData[0x200];
SHARED_SYM extern CameraData Hu3DCamera[0x10];
extern AnimData *reflectAnim[5];
SHARED_SYM extern AnimData *hiliteAnim[4];
extern ThreeDProjectionStruct Hu3DProjection[4];
SHARED_SYM extern ShadowData Hu3DShadowData;
SHARED_SYM extern Mtx Hu3DCameraMtx;
SHARED_SYM extern Mtx Hu3DCameraMtxXPose;
SHARED_SYM extern LightData Hu3DGlobalLight[0x8];
extern s16 reflectMapNo;
extern AnimData *toonAnim;
SHARED_SYM extern s16 Hu3DShadowCamBit;
SHARED_SYM extern s32 Hu3DShadowF;
SHARED_SYM extern s32 shadowModelDrawF;
SHARED_SYM extern s16 Hu3DCameraNo;
extern s16 Hu3DCameraBit;
extern s16 Hu3DPauseF;
SHARED_SYM extern GXColor BGColor;

#endif
