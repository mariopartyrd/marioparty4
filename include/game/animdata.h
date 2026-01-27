#ifndef _GAME_ANIMDATA_H
#define _GAME_ANIMDATA_H

#include "dolphin.h"

#define ANIM_BMP_RGBA8 0
#define ANIM_BMP_RGB5A3 1
#define ANIM_BMP_RGB5A3_DUPE 2
#define ANIM_BMP_C8 3
#define ANIM_BMP_C4 4
#define ANIM_BMP_IA8 5
#define ANIM_BMP_IA4 6
#define ANIM_BMP_I8 7
#define ANIM_BMP_I4 8
#define ANIM_BMP_A8 9
#define ANIM_BMP_CMPR 10

#define ANIM_BMP_FMTMASK 0xF
#define ANIM_BMP_ALLOC 0x8000
#define ANIM_BMP_NUM_MASK 0x7FFF

#define ANIM_LAYER_FLIPX 0x1
#define ANIM_LAYER_FLIPY 0x2

typedef struct anim_frame_data {
    s16 pat;
    s16 time;
    s16 shiftX;
    s16 shiftY;
    s16 flip;
    s16 pad;
} AnimFrameData;

typedef struct anim_bank_data {
    s16 timeNum;
    s16 unk;
    AnimFrameData *frame;
} AnimBankData;

typedef struct anim_layer_data {
    u8 alpha;
    u8 flip;
    s16 bmpNo;
    s16 startX;
    s16 startY;
    s16 sizeX;
    s16 sizeY;
    s16 shiftX;
    s16 shiftY;
    s16 vtx[8];
} AnimLayerData;

typedef struct anim_pat_data {
    s16 layerNum;
    s16 centerX;
    s16 centerY;
    s16 sizeX;
    s16 sizeY;
    AnimLayerData *layer;
} AnimPatData;

typedef struct anim_bmp_data {
    u8 pixSize;
    u8 dataFmt;
    s16 palNum;
    s16 sizeX;
    s16 sizeY;
    u32 dataSize;
    void *palData;
    void *data;
} AnimBmpData;

typedef struct anim_data {
/* 0x00 */ s16 bankNum;
/* 0x02 */ s16 patNum;
/* 0x04 */ s16 bmpNum;
/* 0x06 */ s16 useNum;
/* 0x08 */ AnimBankData *bank;
/* 0x0C */ AnimPatData *pat;
/* 0x10 */ AnimBmpData *bmp;
#ifdef BYTESWAPPING
    u32 valid;
#endif
} AnimData; //sizeof 0x14

#ifdef BYTESWAPPING
#define ANIM_DATA_ALLOCATION_VALID 0xD3D3D3D3
#endif

#endif
