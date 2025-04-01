#ifndef GAME_HSFANIM_H
#define GAME_HSFANIM_H

#include "game/hsfformat.h"
#include "game/hsfman.h"
#include "game/animdata.h"

typedef struct model_data ModelData;
typedef struct particle_data ParticleData;

typedef void (*ParticleHook)(ModelData *model, ParticleData *particle, Mtx matrix);

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ Vec unk08;
    /* 0x14 */ Vec unk14;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ Vec unk34;
    /* 0x40 */ GXColor unk40;
} HsfanimStruct01; // Size 0x44

struct particle_data {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec unk_04;
    /* 0x04 */ Vec unk_10;
    /* 0x1C */ void *unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ char unk_32[2];
    /* 0x34 */ u32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ u32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ AnimData *unk_44;
    /* 0x48 */ HsfanimStruct01 *unk_48;
    /* 0x4C */ Vec *unk_4C;
    /* 0x50 */ void *unk_50;
    /* 0x54 */ ParticleHook unk_54;
}; // Size 0x58

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ GXColor unk2E[4];
    /* 0x3E */ GXColor unk3E[4];
} HsfanimStruct00; // Size (min:0x4E, max:0x50)

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ AnimData *unk10;
} Hu3DTexAnimDataStruct; // Size 0x14

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ Vec unk04;
    /* 0x10 */ char unk10[0xC];
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ char unk28[0xC];
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ Mtx unk3C;
} Hu3DTexScrDataStruct; // Size 0x6C

void Hu3DAnimInit(void);
s16 Hu3DAnimCreate(void *arg0, s16 arg1, char *arg2);
s16 Hu3DAnimLink(s16 arg0, s16 arg1, char *arg2);
void Hu3DAnimKill(s16 arg0);
void Hu3DAnimModelKill(s16 arg0);
void Hu3DAnimAllKill(void);
void Hu3DAnimAttrSet(s16 arg0, u16 arg1);
void Hu3DAnimAttrReset(s16 arg0, s32 arg1);
void Hu3DAnimSpeedSet(s16 arg0, float arg1);
void Hu3DAnimBankSet(s16 arg0, s32 arg1);
void Hu3DAnmNoSet(s16 arg0, u16 arg1);
s32 Hu3DAnimSet(ModelData *arg0, HsfAttribute *arg1, s16 arg2);
void Hu3DAnimExec(void);
s16 Hu3DTexScrollCreate(s16 arg0, char *arg1);
void Hu3DTexScrollKill(s16 arg0);
void Hu3DTexScrollAllKill(void);
void Hu3DTexScrollPosSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DTexScrollPosMoveSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DTexScrollRotSet(s16 arg0, float arg1);
void Hu3DTexScrollRotMoveSet(s16 arg0, float arg1);
void Hu3DTexScrollPauseDisableSet(s16 arg0, s32 arg1);
s16 Hu3DParticleCreate(AnimData *arg0, s16 arg1);
void Hu3DParticleScaleSet(s16 arg0, float arg1);
void Hu3DParticleZRotSet(s16 arg0, float arg1);
void Hu3DParticleColSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3);
void Hu3DParticleTPLvlSet(s16 arg0, float arg1);
void Hu3DParticleBlendModeSet(s16 arg0, u8 arg1);
void Hu3DParticleHookSet(s16 arg0, ParticleHook arg1);
void Hu3DParticleAttrSet(s16 arg0, u8 arg1);
void Hu3DParticleAttrReset(s16 arg0, u8 arg1);
void Hu3DParticleCntSet(s16 arg0, s16 arg1);
void Hu3DParticleAnimModeSet(s16 arg0, s16 arg1);
void Hu3DParManInit(void);
s16 Hu3DParManCreate(AnimData *arg0, s16 arg1, HsfanimStruct00 *arg2);
s16 Hu3DParManLink(s16 arg0, HsfanimStruct00 *arg1);
void Hu3DParManKill(s16 arg0);
void Hu3DParManAllKill(void);
void *Hu3DParManPtrGet(s16 arg0);
void Hu3DParManPosSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DParManVecSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DParManRotSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DParManAttrSet(s16 arg0, s32 arg1);
void Hu3DParManAttrReset(s16 arg0, s32 arg1);
s16 Hu3DParManModelIDGet(s16 arg0);
void Hu3DParManTimeLimitSet(s16 arg0, s32 arg1);
void Hu3DParManVacumeSet(s16 arg0, float arg1, float arg2, float arg3, float arg4);
void Hu3DParManColorSet(s16 arg0, s16 arg1);

extern Hu3DTexAnimDataStruct Hu3DTexAnimData[256];
extern Hu3DTexScrDataStruct Hu3DTexScrData[16];

#endif
