#ifndef _GAME_HSFMOTION_H
#define _GAME_HSFMOTION_H

#include "dolphin.h"
#include "game/hsfformat.h"

#define Hu3DMotionCreateFile(data_id) (Hu3DMotionCreate(HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))

#define Hu3DJointMotionFile(model, data_id) (Hu3DJointMotion((model), HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))


typedef struct motion_data {
    s16 attr;
    s16 modelId;
    HsfData *hsfData;
} MotionData;

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ HsfBitmap *unk04;
} UnknownHsfMotionStruct01; // Size 8

void Hu3DMotionInit(void);
s16 Hu3DMotionCreate(void *arg0);
s16 Hu3DMotionModelCreate(s16 arg0);
s32 Hu3DMotionKill(s16 arg0);
void Hu3DMotionAllKill(void);
void Hu3DMotionSet(s16 arg0, s16 arg1);
void Hu3DMotionOverlaySet(s16 arg0, s16 arg1);
void Hu3DMotionOverlayReset(s16 arg0);
float Hu3DMotionOverlayTimeGet(s16 arg0);
void Hu3DMotionOverlayTimeSet(s16 arg0, float arg1);
void Hu3DMotionOverlaySpeedSet(s16 arg0, float arg1);
void Hu3DMotionShiftSet(s16 arg0, s16 arg1, float arg2, float arg3, u32 arg4);
void Hu3DMotionShapeSet(s16 arg0, s16 arg1);
s16 Hu3DMotionShapeIDGet(s16 arg0);
void Hu3DMotionShapeSpeedSet(s16 arg0, float arg1);
void Hu3DMotionShapeTimeSet(s16 arg0, float arg1);
float Hu3DMotionShapeMaxTimeGet(s16 arg0);
void Hu3DMotionShapeStartEndSet(s16 arg0, float arg1, float arg2);
s16 Hu3DMotionClusterSet(s16 arg0, s16 arg1);
s16 Hu3DMotionClusterNoSet(s16 arg0, s16 arg1, s16 arg2);
void Hu3DMotionShapeReset(s16 arg0);
void Hu3DMotionClusterReset(s16 arg0, s16 arg1);
s16 Hu3DMotionIDGet(s16 arg0);
s16 Hu3DMotionShiftIDGet(s16 arg0);
void Hu3DMotionTimeSet(s16 arg0, float arg1);
float Hu3DMotionTimeGet(s16 arg0);
float Hu3DMotionShiftTimeGet(s16 arg0);
float Hu3DMotionMaxTimeGet(s16 arg0);
float Hu3DMotionShiftMaxTimeGet(s16 arg0);
void Hu3DMotionShiftStartEndSet(s16 arg0, float arg1, float arg2);
float Hu3DMotionMotionMaxTimeGet(s16 arg0);
void Hu3DMotionStartEndSet(s16 arg0, float arg1, float arg2);
s32 Hu3DMotionEndCheck(s16 arg0);
void Hu3DMotionSpeedSet(s16 arg0, float arg1);
void Hu3DMotionShiftSpeedSet(s16 arg0, float arg1);
void Hu3DMotionNoMotSet(s16 arg0, char *arg1, u32 arg2);
void Hu3DMotionNoMotReset(s16 arg0, char *arg1, u32 arg2);
void Hu3DMotionForceSet(s16 arg0, char *arg1, u32 arg2, float arg3);
void Hu3DMotionNext(s16 arg0);
void Hu3DMotionExec(s16 arg0, s16 arg1, float arg2, s32 arg3);
void Hu3DCameraMotionExec(s16 arg0);
void Hu3DSubMotionExec(s16 arg0);
float *GetObjTRXPtr(HsfObject *arg0, u16 arg1);
void SetObjMatMotion(s16 arg0, HsfTrack *arg1, float arg2);
void SetObjAttrMotion(s16 arg0, HsfTrack *arg1, float arg2);
void SetObjCameraMotion(s16 arg0, HsfTrack *arg1, float arg2);
void SetObjLightMotion(s16 arg0, HsfTrack *arg1, float arg2);
float GetCurve(HsfTrack *arg0, float arg1);
float GetConstant(s32 arg0, float *arg1, float arg2);
float GetLinear(s32 arg0, float arg1[][2], float arg2);
float GetBezier(s32 arg0, HsfTrack *arg1, float arg2);
HsfBitmap *GetBitMap(s32 arg0, UnknownHsfMotionStruct01 *arg1, float arg2);
s16 Hu3DJointMotion(s16 arg0, void *arg1);
void JointModel_Motion(s16 arg0, s16 arg1);
void Hu3DMotionCalc(s16 arg0);

extern MotionData Hu3DMotion[256];

#endif
