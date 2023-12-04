#ifndef _HSF_FORMAT_H
#define _HSF_FORMAT_H

#include "dolphin.h"

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
    GXColor unk0;
    f32 unk4;
    f32 unk8;
    u32 unkC;
} HsfScene;

typedef struct hsf_bitmap {
    char *name;
    s32 maxLod;
    u8 dataFmt;
    u8 pixSize;
    u16 w;
    u16 h;
    u16 palSize;
    GXColor tint;
    void *palData;
    u32 unk;
    void *data;
} HsfBitmap;

typedef struct hsf_palette {
    char *name;
    int unk;
    int palSize;
    void *data;
} HsfPalette;

typedef struct hsf_attribute {
    char *name;
    u8 unk[124];
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
    HsfAttribute **attrs;
} HsfMaterial;

typedef struct hsf_vertex_buf {
    char *name;
    u32 count;
    void *data;
} HsfVertexBuf;

typedef struct hsf_face {
    u16 type;
    u16 mat;
    u16 indices[12];
    union {
        struct {
            u32 count;
            u16 *data;
        } strip;
        u16 ext_indices[4];
    };
} HSFFace;

typedef struct hsf_face_buf {
    char *name;
    u32 count;
    HSFFace *data;
} HsfFaceBuf;

typedef struct hsf_const_data {
    u32 flags;
    u8 unk[64];
} HsfConstData;

typedef struct hsf_transform {
    Vec pos;
    Vec rot;
    Vec scale;
} HsfTransform;

typedef struct hsf_object {
    char *name;
    u32 type;
    HsfConstData *constData;
    u32 flags;
    u32 idx;
    u32 childrenCount;
    struct hsf_object **children;
    HsfTransform base;
    HsfTransform curr;
    Vec min;
    Vec max;
    u8 unk[136];
    HsfFaceBuf *face;
    HsfVertexBuf *vertex;
    HsfVertexBuf *normal;
    HsfVertexBuf *st;
    HsfVertexBuf *color;
    HsfMaterial *material;
    HsfAttribute *attribute;
    u8 unk2[36];
} HsfObject;

typedef struct hsf_cenv {
    u8 unk[36];
} HsfCenv;

typedef struct hsf_part {
    char *name;
    u32 count;
    u16 *data;
} HsfPart;

typedef struct hsf_cluster {
    char *name[3];
    HsfPart *part;
    u8 unk[144];
} HsfCluster;

typedef struct hsf_shape {
    char *name;
    u16 count1;
    u16 morphTargetCnt;
    HsfVertexBuf **morphTargets;
} HsfShape;

typedef struct hsf_skeleton {
    char *name;
    HsfTransform transform;
} HsfSkeleton;

typedef struct hsf_track {
    u8 mode;
    u8 value;
    s16 idx;
    s16 type;
    s16 effect;
    s16 curveType;
    s16 numKeyframes;
    void *data;
} HsfTrack;

typedef struct hsf_motion {
    char *name;
    u32 numTracks;
    HsfTrack *track;
    float len;
} HsfMotion;

typedef struct hsf_map_attr {
    u8 unk[16];
    void *unk10;
    u8 unk2[4];
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
    HsfVertexBuf *vertex;
    HsfVertexBuf *normal;
    HsfVertexBuf *st;
    HsfVertexBuf *color;
    HsfFaceBuf *face;
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