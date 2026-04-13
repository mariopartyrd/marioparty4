#ifndef _GAME_HSFDRAW_H
#define _GAME_HSFDRAW_H

#include "game/hsfman.h"
#include "dolphin.h"

typedef struct model_data ModelData;

typedef struct hsfdraw_struct_01 {
    /* 0x00 */ u16 attr;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ Vec rot;
    /* 0x20 */ Vec trans3D;
    /* 0x2C */ HsfVector2f scale;
    /* 0x34 */ HsfVector2f trans;
    /* 0x3C */ HsfBitmap *unk3C;
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
    AnimData *hiliteMap;
} HsfConstData;

typedef struct hsf_draw_object {
    /* 0x00 */ ModelData *model;
    /* 0x04 */ HsfObject *object;
    /* 0x08 */ float z;
    /* 0x0C */ Mtx matrix;
    /* 0x3C */ Vec scale;
} HsfDrawObject;


void Hu3DDrawPreInit(void);
void Hu3DDraw(ModelData *arg0, Mtx arg1, Vec *arg2);
s32 ObjCullCheck(HsfData *arg0, HsfObject *arg1, Mtx arg2);
void Hu3DDrawPost(void);
void MakeDisplayList(s16 arg0, uintptr_t arg1);
HsfConstData *ObjConstantMake(HsfObject *arg0, uintptr_t arg1);
void mtxTransCat(Mtx arg0, float arg1, float arg2, float arg3);
void mtxRotCat(Mtx arg0, float arg1, float arg2, float arg3);
void mtxRot(Mtx arg0, float arg1, float arg2, float arg3);
void mtxScaleCat(Mtx arg0, float arg1, float arg2, float arg3);
s16 HmfInverseMtxF3X3(Mtx arg0, Mtx arg1);
void SetDefLight(Vec *arg0, Vec *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA);
void Hu3DModelObjPosGet(s16 arg0, char *arg1, Vec *arg2);
void Hu3DModelObjMtxGet(s16 arg0, char *arg1, Mtx arg2);
void PGObjCall(ModelData *arg0, HsfObject *arg1);
void PGObjCalc(ModelData *arg0, HsfObject *arg1);
void PGObjReplica(ModelData *arg0, HsfObject *arg1);
HsfObject *Hu3DObjDuplicate(HsfData *arg0, uintptr_t arg1);
void Hu3DModelObjDrawInit(void);
void Hu3DModelObjDraw(s16 arg0, char *arg1, Mtx arg2);

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

#endif
