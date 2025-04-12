#ifndef _SRC_BYTESWAP_H_
#define _SRC_BYTESWAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "game/animdata.h"
#include "game/hsfformat.h"

typedef struct AnimData32b {
    s16 bankNum;
    s16 patNum;
    s16 bmpNum;
    s16 useNum;

    u32 bank;
    u32 pat;
    u32 bmp;
} AnimData32b;

typedef struct AnimBankData32b {
    s16 timeNum;
    s16 unk;
    u32 frame;
} AnimBankData32b;

typedef struct AnimPatData32b {
    s16 layerNum;
    s16 centerX;
    s16 centerY;
    s16 sizeX;
    s16 sizeY;
    u32 layer;
} AnimPatData32b;

typedef struct AnimBmpData32b {
    u8 pixSize;
    u8 dataFmt;
    s16 palNum;
    s16 sizeX;
    s16 sizeY;
    u32 dataSize;
    u32 palData;
    u32 data;
} AnimBmpData32b;

typedef struct HsfCluster32b {
    u32 name[2];
    u32 targetName;
    u32 part;
    float index;
    float weight[32];
    u8 adjusted;
    u8 unk95;
    u16 type;
    u32 vertexCnt;
    u32 vertex;
} HsfCluster32b;

typedef struct HsfAttribute32b {
    u32 name;
    u32 unk04;
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
    u32 bitmap;
} HsfAttribute32b;

typedef struct HsfMaterial32b {
    u32 name;
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
    u32 attrs;
} HsfMaterial32b;

typedef struct HsfMapAttr32b {
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    u32 data;
    u32 dataLen;
} HsfMapAttr32b;

typedef struct HsfBuffer32b {
    u32 name;
    s32 count;
    u32 data;
} HsfBuffer32b;

typedef struct HsfPalette32b {
    u32 name;
    s32 unk;
    u32 palSize;
    u32 data;
} HsfPalette32b;

typedef struct HsfBitmap32b {
    u32 name;
    u32 maxLod;
    u8 dataFmt;
    u8 pixSize;
    s16 sizeX;
    s16 sizeY;
    s16 palSize;
    GXColor tint;
    u32 palData;
    u32 unk;
    u32 data;
} HsfBitmap32b;

typedef struct HsfPart32b {
    u32 name;
    u32 count;
    u32 vertex;
} HsfPart32b;

typedef struct HsfSkeleton32b {
    u32 name;
    HsfTransform transform;
} HsfSkeleton32b;

typedef struct HsfShape32b {
    u32 name;
    union {
        u16 count16[2];
        u32 vertexCnt;
    };
    u32 vertex;
} HsfShape32b;

typedef struct HsfCenv32b {
    u32 name;
    u32 singleData;
    u32 dualData;
    u32 multiData;
    u32 singleCount;
    u32 dualCount;
    u32 multiCount;
    u32 vtxCount;
    u32 copyCount;
} HsfCenv32b;

typedef struct HsfObjectData32b {
    u32 parent;
    u32 childrenCount;
    u32 children;
    HsfTransform base;
    HsfTransform curr;
    union {
        struct {
            HsfVector3f min;
            HsfVector3f max;
            float baseMorph;
            float morphWeight[33];
        } mesh;
        u32 replica;
    };

    u32 face;
    u32 vertex;
    u32 normal;
    u32 color;
    u32 st;
    u32 material;
    u32 attribute;
    u8 unk120[2];
    u8 shapeType;
    u8 unk123;
    u32 vertexShapeCnt;
    u32 vertexShape;
    u32 clusterCnt;
    u32 cluster;
    u32 cenvCnt;
    u32 cenv;
    u32 file[2];
} HsfObjectData32b;

typedef struct HsfObject32b {
    u32 name;
    u32 type;
    u32 constData;
    u32 flags;
    HsfObjectData32b data;
} HsfObject32b;

typedef struct HsfTrack32b {
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
        u32 data;
    };
} HsfTrack32b;

typedef struct HsfMotion32b {
    u32 name;
    s32 numTracks;
    u32 track;
    float len;
} HsfMotion32b;

typedef struct HsfBitmapKey32b {
    float time;
    u32 data;
} HsfBitmapKey32b;

typedef struct HsfFace32b {
    s16 type;
    s16 mat;
    union {
        struct {
            s16 indices[3][4];
            u32 count;
            u32 data;
        } strip;
        s16 indices[4][4];
    };
    Vec nbt;
} HsfFace32b;

void byteswap_u16(u16 *src);
void byteswap_s16(s16 *src);
void byteswap_u32(u32 *src);
void byteswap_s32(s32 *src);
void byteswap_hsfvec3f(HsfVector3f *src);
void byteswap_hsfvec2f(HsfVector2f *src);

void byteswap_animdata(void *src, AnimData *dest);
void byteswap_animbankdata(AnimBankData32b *src, AnimBankData *dest);
void byteswap_animpatdata(AnimPatData32b *src, AnimPatData *dest);
void byteswap_animbmpdata(AnimBmpData32b *src, AnimBmpData *dest);
void byteswap_animframedata(AnimFrameData *src);
void byteswap_animlayerdata(AnimLayerData *src);

void byteswap_hsfheader(HsfHeader *src);
void byteswap_hsfcluster(HsfCluster32b *src, HsfCluster *dest);
void byteswap_hsfattribute(HsfAttribute32b *src, HsfAttribute *dest);
void byteswap_hsfmaterial(HsfMaterial32b *src, HsfMaterial *dest);
void byteswap_hsfscene(HsfScene *src);
void byteswap_hsfbuffer(HsfBuffer32b *src, HsfBuffer *dest);
void byteswap_hsfmatrix(HsfMatrix *src);
void byteswap_hsfpalette(HsfPalette32b *src, HsfPalette *dest);
void byteswap_hsfpart(HsfPart32b *src, HsfPart *dest);
void byteswap_hsfbitmap(HsfBitmap32b *src, HsfBitmap *dest);
void byteswap_hsfmapattr(HsfMapAttr32b *src, HsfMapAttr *dest);
void byteswap_hsfskeleton(HsfSkeleton32b *src, HsfSkeleton *dest);
void byteswap_hsfshape(HsfShape32b *src, HsfShape *dest);
void byteswap_hsfcenv_single(HsfCenvSingle *src);
void byteswap_hsfcenv(HsfCenv32b *src, HsfCenv *dest);
void byteswap_hsfobject(HsfObject32b *src, HsfObject *dest);
void byteswap_hsfbitmapkey(HsfBitmapKey32b *src, HsfBitmapKey *dest);
void byteswap_hsftrack(HsfTrack32b *src, HsfTrack *dest);
void byteswap_hsfmotion(HsfMotion32b *src, HsfMotion *dest);
void byteswap_hsfface(HsfFace32b *src, HsfFace *dest);

#ifdef __cplusplus
}
#endif

#endif
