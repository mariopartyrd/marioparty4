#ifndef GAME_HSFANIM_H
#define GAME_HSFANIM_H

#include "game/hsfformat.h"
#include "game/hsfman.h"
#include "game/animdata.h"

// TODO move these to hu3d.h

typedef struct Hu3DModel_s HU3DMODEL;
typedef struct Hu3DParticle_s HU3DPARTICLE;

typedef void (*HU3DPARTICLEHOOK)(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);

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

extern HU3DTEXANIM Hu3DTexAnimData[256];
extern HU3DTEXSCROLL Hu3DTexScrData[16];

#endif
