#ifndef _BOARD_MODEL_H
#define _BOARD_MODEL_H

#include "game/hsfman.h"
#include "game/data.h"

typedef struct board_model_param {
	s32 data_num;
	struct {
		u8 field04_bit0 : 2;
		u8 visible : 1;
		u8 link : 1;
		u8 start_mot : 1;
		u8 pause : 1;
	} unk4;
	s16 unk6;
} BoardModelParam;

void BoardModelInit(void);
void BoardModelKillAll(void);
void BoardModelDummyUpdate(void);
void BoardModelVisibilityUpdate(void);
void BoardModelHideSetAll(s32 flag);
void BoardModelAmbSetAll(float r, float g, float b);
void BoardModelCameraSetAll(u16 camera);
s16 BoardModelCreate(s32 data_num, s32 *mot_list, s32 link);
s16 BoardModelCreateCharacter(s32 character, s32 data_num, s32 *mot_list, s32 link);
s16 BoardModelCreateParam(BoardModelParam *param, Vec *pos, Vec *rot);
void BoardModelKill(s16 model);
s16 BoardModelIDGet(s16 model);
s32 fn_8006DC1C(s16 model, s32 arg1);
s32 BoardModelPassSet(s16 model, s32 pass);
s32 BoardModelAmbSet(s16 model, float r, float g, float b);
s32 BoardModelExistCheck(s16 model, s32 arg1);
s32 BoardModelExistDupe(s16 model, s32 arg1);
s32 fn_8006DDE8(s16 model, float arg1);
s32 BoardModelMotionCreate(s16 model, s32 data_num);
s32 BoardModelMotionKill(s16 model, s32 motion);
s32 BoardModelMotionStartEndSet(s16 model, s16 start, s16 end);
s32 BoardModelMotionUpdateSet(s16 model, s32 flag);
s32 BoardModelVoiceEnableSet(s16 model, s32 motion, s32 flag);
s32 BoardModelMotionStart(s16 model, s32 slot, u32 attr);
s32 BoardModelMotionShiftSet(s16 model, s32 motion, float time, float shift_time, u32 attr);
s32 BoardModelMotionShiftIDGet(s16 model);
s32 BoardModelAttrSet(s16 model, u32 attr);
s32 BoardModelAttrReset(s16 model, u32 attr);
s32 BoardModelMotionTimeSet(s16 model, float time);
float BoardModelMotionTimeGet(s16 model);
float BoardModelMotionMaxTimeGet(s16 model);
float BoardModelMotionSpeedGet(s16 model);
s32 BoardModelMotionSpeedSet(s16 model, float speed);
s32 BoardModelMotionEndCheck(s16 model);
s32 BoardModelAlphaSet(s16 model, u8 alpha);
s32 BoardModelMtxSet(s16 model, Mtx *src);
s32 BoardModelRotYSet(s16 model, float rot);
float BoardModelRotYGet(s16 model);
s32 BoardModelPosSet(s16 model, float x, float y, float z);
s32 BoardModelPosSetV(s16 model, Vec *pos);
s32 BoardModelRotSet(s16 model, float x, float y, float z);
s32 BoardModelRotSetV(s16 model, Vec *rot);
s32 BoardModelScaleSet(s16 model, float x, float y, float z);
s32 BoardModelScaleSetV(s16 model, Vec *scale);
s32 BoardModelPosGet(s16 model, Vec *dst);
s32 BoardModelRotGet(s16 model, Vec *dst);
s32 BoardModelScaleGet(s16 model, Vec *dst);
s32 BoardModelVisibilitySet(s16 model, s32 flag);
s32 BoardModelVisibilityGet(s16 model);
s32 BoardModelCameraSet(s16 model, u16 camera);
s32 BoardModelLayerSet(s16 model, u8 layer);
s32 BoardModelLayerGet(s16 model);
void BoardModelLayerSetAll(s32 layer);
s32 BoardModelHookSet(s16 model, char *name, s16 hook);
s32 BoardModelHookReset(s16 model);
s32 BoardModelHookObjReset(s16 model, char *name);

#endif