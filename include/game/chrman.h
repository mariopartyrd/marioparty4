#ifndef _GAME_CHRMAN_H
#define _GAME_CHRMAN_H

#include "dolphin.h"

void CharManInit(void);
void *CharAMemPtrGet(s16 character);
void CharARAMOpen(s16 character);
void CharARAMClose(s16 character);
void CharKill(s16 arg0);
void CharKillAll(void);
s16 CharModelCreate(s16 character, s16 lod);
s16 CharModelMotionCreate(s16 character, s32 data_num);
void CharModelMotionIndexSet(s16 character, s16 arg1, s32 arg2);
void CharModelMotionKill(s16 character, u32 motion);
void CharModelMotionDataClose(s16 character);
void CharModelDataClose(s16 arg0);
void CharModelKill(s16 character);
void CharModelMotionSet(s16 character, s16 motion);
void CharModelTexAnimSet(s16 character);
char **CharModelTexNameGet(s16 arg0, s16 arg1);
char *CharModelHookNameGet(s16 arg0, s16 arg1, s16 arg2);
void CharModelMotionTimeSet(s16 character, float time);
float CharModelMotionTimeGet(s16 character);
float CharModelMotionMaxTimeGet(s16 character);
s32 CharModelMotionEndCheck(s16 character);
s16 CharModelMotionShiftIDGet(s16 character);
void CharModelMotionShiftSet(s16 character, s16 motion, float time, float shift_time, u32 attr);
float CharModelMotionShiftTimeGet(s16 character);
void CharModelMotionSpeedSet(s16 character, float speed);
void CharModelLayerSetAll(s16 arg0);
void CharModelItemHookCreate(s16 character, char *arg1);
void CharModelEffectCreate(s16 arg0, Vec *arg1);
void CharModelCoinEffectCreate(s16 arg0, Vec *arg1);
void fn_8004EC74(s16 character);
void fn_8004EDA4(s16 arg0, Vec *arg1, Vec *arg2);
void fn_8004F058(s16 character);
void fn_8004F13C(s16 arg0, Vec *arg1, Vec *arg2);
void CharModelLayerSetAll2(s16 arg0);
void CharModelVoiceEnableSet(s16 character, s16 motion, s32 flag);
void fn_8004F52C(s16 character, s32 arg1);
void CharModelEffectEnableSet(s16 character, s32 arg1);
s32 CharModelEffectNpcInit(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
s32 CharModelEffectNpcInitSilent(s16 arg0, s16 arg1, s16 arg2);
void CharModelStepTypeSet(s16 character, s32 arg1);

#define CHARNO_MAX  8
#define CHAR_NPC_MAX 7
#define CHAR_EFFECT_AND_PARTICLE_MAX 8

#endif
