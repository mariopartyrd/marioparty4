#ifndef _GAME_CHRMAN_H
#define _GAME_CHRMAN_H

#include "dolphin.h"
#include "game/armem.h"
#include "game/hsfman.h"
#include "game/humath.h"


#define CHARNO_NONE -1
#define CHARNO_MAX  8

#define CHAR_MODEL0 (1 << 0)
#define CHAR_MODEL1 (1 << 1)
#define CHAR_MODEL2 (1 << 2)
#define CHAR_MODEL3 (1 << 3)
#define CHAR_MODEL_MAX 4

#define CHAR_MOT_MAX 32

#define CHAR_NPC_MAX 7
#define CHAR_NPC_NONE -1

#define CHAR_EFFECT_AND_PARTICLE_MAX 8

void CharInit(void);
AMEM_PTR CharMotionAMemPGet(s16 charNo);
void CharMotionInit(s16 charNo);
void CharMotionClose(s16 charNo);
void CharDataClose(s16 charNo);
void CharClose(void);
HU3DMODELID CharModelCreate(s16 charNo, s16 model);
HU3DMOTID CharMotionCreate(s16 charNo, s32 data_num);
void CharMotionNoSet(s16 charNo, HU3DMOTID motId, s32 motNo);
void CharMotionKill(s16 charNo, u32 motId);
void CharMotionDataClose(s16 charNo);
void CharModelDataClose(s16 charNo);
void CharModelKill(s16 charNo);
void CharMotionSet(s16 charNo, HU3DMOTID motId);
char **CharModelEyeBmpGet(s16 charNo, s16 model);
char *CharModelItemHookGet(s16 charNo, s16 model, s16 hookNo);
void CharMotionTimeSet(s16 charNo, float time);
float CharMotionTimeGet(s16 charNo);
float CharMotionMaxTimeGet(s16 charNo);
s32 CharMotionEndCheck(s16 charNo);
s16 CharMotionShiftIDGet(s16 charNo);
void CharMotionShiftSet(s16 charNo, HU3DMOTID motId, float start, float end, u32 attr);
float CharMotionShiftTimeGet(s16 charNo);
void CharMotionSpeedSet(s16 charNo, float speed);
void CharEffectLayerSet(s16 layerNo);
void CharModelHookDustCreate(s16 charNo, char *objName);
void CharEffectSmokeCreate(s16 cameraBit, HuVecF *pos);
void CharEffectCoinGlowCreate(s16 cameraBit, HuVecF *pos);
void CharModelHitCreate(s16 charNo);
void CharEffectHitCreate(s16 cameraBit, HuVecF *pos, HuVecF *rot);
void CharModelShoeHitCreate(s16 charNo);
void CharEffectShoeHitCreate(s16 cameraBit, HuVecF *pos, HuVecF *rot);
void CharModelLayerSetAll2(s16 layerNo);
void CharMotionVoiceOnSet(s16 charNo, s16 motion, BOOL voiceOn);
void CharModelVoicePanAutoSet(s16 charNo, BOOL voicePanAuto);
void CharModelFxFlagSet(s16 charNo, BOOL fxFlag);
s32 CharNpcDustSet(HU3DMODELID modelId, HU3DMOTID motId, s16 type, s16 npcNo);
s32 CharNpcDustVoiceOffSet(HU3DMODELID modelId, HU3DMOTID motId, s16 type);
void CharModelStepFxSet(s16 charNo, s32 stepFx);

#endif
