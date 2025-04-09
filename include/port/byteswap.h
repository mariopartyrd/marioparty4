#ifndef _SRC_BYTESWAP_H_
#define _SRC_BYTESWAP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "game/animdata.h"
#include "game/hsfformat.h"

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

typedef struct HsfObject32b {
    u32 name;
    u32 type;
    u32 constData;
    u32 flags;
    // TODO PC
    union {
        HsfObjectData data;
        HsfCamera camera;
        HsfLight light;
    };
} HsfObject32b;

void byteswap_u16(u16 *src);
void byteswap_s16(s16 *src);
void byteswap_u32(u32 *src);
void byteswap_s32(s32 *src);
void byteswap_hsfvec3f(HsfVector3f *src);
void byteswap_hsfvec2f(HsfVector2f *src);

void byteswap_animdata(void *src, AnimData* dest);
void byteswap_animbankdata(void *src, AnimBankData *dest);
void byteswap_animpatdata(void *src, AnimPatData *dest);
void byteswap_animbmpdata(void *src, AnimBmpData *dest);
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
void byteswap_hsfcenvsingle(HsfCenvSingle *src);
void byteswap_hsfcenv(HsfCenv32b *src, HsfCenv *dest);
void byteswap_hsfobject(HsfObject32b *src, HsfObject *dest);

#ifdef __cplusplus
}
#endif

#endif
