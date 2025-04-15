#ifndef _GAME_HSFFORMAT_H
#define _GAME_HSFFORMAT_H

#include "dolphin.h"
#include "game/animdata.h"

#define HSF_OBJ_NULL1 0
#define HSF_OBJ_REPLICA 1
#define HSF_OBJ_MESH 2
#define HSF_OBJ_ROOT 3
#define HSF_OBJ_JOINT 4
#define HSF_OBJ_NULL2 5
#define HSF_OBJ_NULL3 6
#define HSF_OBJ_NONE1 7
#define HSF_OBJ_NONE2 8
#define HSF_OBJ_MAP 9

#define HSF_TRACK_TRANSFORM 2
#define HSF_TRACK_MORPH 3
#define HSF_TRACK_CLUSTER 5
#define HSF_TRACK_CLUSTER_WEIGHT 6
#define HSF_TRACK_MATERIAL 9
#define HSF_TRACK_ATTRIBUTE 10

#define HSF_CURVE_STEP 0
#define HSF_CURVE_LINEAR 1
#define HSF_CURVE_BEZIER 2
#define HSF_CURVE_BITMAP 3
#define HSF_CURVE_CONST 4

typedef struct hsf_vector3f {
    float x;
    float y;
    float z;
} HsfVector3f;

typedef struct hsf_vector2f {
    float x;
    float y;
} HsfVector2f;

typedef struct hsf_section {
    s32 ofs;
    s32 count;
} HsfSection;

typedef struct hsf_header {
    char magic[8];
    HsfSection scene;
    HsfSection color;
    HsfSection material;
    HsfSection attribute;
    HsfSection vertex;
    HsfSection normal;
    HsfSection st;
    HsfSection face;
    HsfSection object;
    HsfSection bitmap;
    HsfSection palette;
    HsfSection motion;
    HsfSection cenv;
    HsfSection skeleton;
    HsfSection part;
    HsfSection cluster;
    HsfSection shape;
    HsfSection mapAttr;
    HsfSection matrix;
    HsfSection symbol;
    HsfSection string;
} HsfHeader;

typedef struct hsf_scene {
    GXFogType fogType;
    f32 start;
    f32 end;
    GXColor color;
} HsfScene;

typedef struct hsf_bitmap {
    char *name;
    u32 maxLod;
    u8 dataFmt;
    u8 pixSize;
    s16 sizeX;
    s16 sizeY;
    s16 palSize;
    GXColor tint;
    void *palData;
    u32 unk;
    void *data;
} HsfBitmap;

typedef struct hsf_palette {
    char *name;
    s32 unk;
    u32 palSize;
    u16 *data;
} HsfPalette;

typedef struct hsf_attribute {
    char *name;
    struct hsfdraw_struct_01 *unk04;
    u8 unk8[4];
    float unk0C;
    u8 unk10[4];
    float unk14;
    u8 unk18[8];
    float unk20;
    u8 unk24[4];
    float unk28;
    float unk2C;
    float unk30;
    float unk34;
    u8 unk38[44];
    u32 wrap_s;
    u32 wrap_t;
    u8 unk6C[12];
    u32 unk78;
    u32 flag;
    HsfBitmap *bitmap;
} HsfAttribute;

typedef struct hsf_material {
    char *name;
    u8 unk4[4];
    u16 pass;
    u8 vtxMode;
    u8 litColor[3];
    u8 color[3];
    u8 shadowColor[3];
    float hilite_scale;
    float unk18;
    float invAlpha;
    float unk20[2];
    float refAlpha;
    float unk2C;
    u32 flags;
    u32 numAttrs;
    s32 *attrs;
} HsfMaterial;

typedef struct hsf_vertex_buf {
    char *name;
    s32 count;
    void *data;
} HsfBuffer;

typedef struct hsf_face {
    s16 type;
    s16 mat;
    union {
        struct {
            s16 indices[3][4];
            u32 count;
            s16 *data;
        } strip;
        s16 indices[4][4];
    };
    Vec nbt;
} HsfFace;

typedef struct hsf_transform {
    Vec pos;
    Vec rot;
    Vec scale;
} HsfTransform;

typedef struct hsf_cenv_single {
    u32 target;
    u16 pos;
    u16 posCnt;
    u16 normal;
    u16 normalCnt;
} HsfCenvSingle;

typedef struct hsf_cenv_dual_weight {
    float weight;
    u16 pos;
    u16 posCnt;
    u16 normal;
    u16 normalCnt;
} HsfCenvDualWeight;

typedef struct hsf_cenv_dual {
    u32 target1;
    u32 target2;
    u32 weightCnt;
    HsfCenvDualWeight *weight;
} HsfCenvDual;

typedef struct hsf_cenv_multi_weight {
    u32 target;
    float value;
} HsfCenvMultiWeight;

typedef struct hsf_cenv_multi {
    u32 weightCnt;
    u16 pos;
    u16 posCnt;
    u16 normal;
    u16 normalCnt;
    HsfCenvMultiWeight *weight;
} HsfCenvMulti;

typedef struct hsf_cenv {
    char *name;
    HsfCenvSingle *singleData;
    HsfCenvDual *dualData;
    HsfCenvMulti *multiData;
    u32 singleCount;
    u32 dualCount;
    u32 multiCount;
    u32 vtxCount;
    u32 copyCount;
} HsfCenv;

typedef struct hsf_part {
    char *name;
    u32 count;
    u16 *vertex;
} HsfPart;

typedef struct hsf_cluster {
    char *name[2];
    union {
        char *targetName;
        s32 target;
    };
    HsfPart *part;
    float index;
    float weight[32]; // unknown array size
    u8 adjusted;
    u8 unk95;
    u16 type;
    u32 vertexCnt;
    HsfBuffer **vertex;
} HsfCluster;

typedef struct hsf_shape {
    char *name;
    union {
        u16 count16[2];
        u32 vertexCnt;
    };
    HsfBuffer **vertex;
} HsfShape;

typedef struct hsf_object_data {
    struct hsf_object *parent;
    u32 childrenCount;
    struct hsf_object **children;
    HsfTransform base;
    HsfTransform curr;
    union {
        struct {
            HsfVector3f min;
            HsfVector3f max;
            float baseMorph;
            float morphWeight[33];
        } mesh;
        struct hsf_object *replica;
    };

    HsfBuffer *face;
    HsfBuffer *vertex;
    HsfBuffer *normal;
    HsfBuffer *color;
    HsfBuffer *st;
    HsfMaterial *material;
    HsfAttribute *attribute;
    u8 unk120[2];
    u8 shapeType;
    u8 unk123;
    u32 vertexShapeCnt;
    HsfBuffer **vertexShape;
    u32 clusterCnt;
    HsfCluster **cluster;
    u32 cenvCnt;
    HsfCenv *cenv;
    HsfVector3f *vtxtop;
    HsfVector3f *normtop;
} HsfObjectData;

typedef struct hsf_camera {
    HsfVector3f target;
    HsfVector3f pos;
    float aspect_dupe;
    float fov;
    float nnear;
    float ffar;
} HsfCamera;

typedef struct hsf_light {
    HsfVector3f pos;
    HsfVector3f target;
    u8 type;
    u8 r;
    u8 g;
    u8 b;
    float unk2C;
    float ref_distance;
    float ref_brightness;
    float cutoff;
} HsfLight;

typedef struct hsf_object {
    char *name;
    u32 type;
    void *constData;
    u32 flags;
    union {
        HsfObjectData data;
        HsfCamera camera;
        HsfLight light;
    };
} HsfObject;

typedef struct hsf_skeleton {
    char *name;
    HsfTransform transform;
} HsfSkeleton;

typedef struct hsf_bitmap_keyframe {
    float time;
    HsfBitmap *data;
} HsfBitmapKey;

typedef struct hsf_track {
    u8 type;
    u8 start;
    union {
        u16 target;
        s16 target_s16;
    };
    union {
        s32 unk04;
        struct {
            union {
                s16 param;
                u16 param_u16;
            };
            union {
                u16 channel;
                s16 channel_s16;
            };
        };
    };
    u16 curveType;
    u16 numKeyframes;
    union {
        float value;
        void *data;
    };
#ifdef TARGET_PC
    void *dataTop;
#endif
} HsfTrack;

typedef struct hsf_motion {
    char *name;
    s32 numTracks;
    HsfTrack *track;
    float len;
} HsfMotion;

typedef struct hsf_map_attr {
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    u16 *data;
    u32 dataLen;
} HsfMapAttr;

typedef struct hsf_matrix {
    u32 base_idx;
    u32 count;
    Mtx *data;
} HsfMatrix;

typedef struct hsf_data {
    u8 magic[8];
    HsfScene *scene;
    HsfAttribute *attribute;
    HsfMaterial *material;
    HsfBuffer *vertex;
    HsfBuffer *normal;
    HsfBuffer *st;
    HsfBuffer *color;
    HsfBuffer *face;
    HsfBitmap *bitmap;
    HsfPalette *palette;
    HsfObject *root;
    HsfCenv *cenv;
    HsfSkeleton *skeleton;
    HsfCluster *cluster;
    HsfPart *part;
    HsfShape *shape;
    HsfMotion *motion;
    HsfObject *object;
    HsfMapAttr *mapAttr;
    HsfMatrix *matrix;
#ifdef TARGET_PC
    void **symbol;
#endif
    s16 sceneCnt;
    s16 attributeCnt;
    s16 materialCnt;
    s16 vertexCnt;
    s16 normalCnt;
    s16 stCnt;
    s16 colorCnt;
    s16 faceCnt;
    s16 bitmapCnt;
    s16 paletteCnt;
    s16 objectCnt;
    s16 cenvCnt;
    s16 skeletonCnt;
    s16 clusterCnt;
    s16 partCnt;
    s16 shapeCnt;
    s16 mapAttrCnt;
    s16 motionCnt;
    s16 matrixCnt;
} HsfData;

#endif
