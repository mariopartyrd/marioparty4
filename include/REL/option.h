#ifndef REL_OPTION_H
#define REL_OPTION_H

#include "game/object.h"

#include "dolphin/types.h"

typedef struct {
    /* 0x00 */ Process *process;
    /* 0x04 */ s16 window;
    /* 0x08 */ s32 id;
    /* 0x0C */ s32 visible;
    /* 0x10 */ BOOL messWaitSignal;
    /* 0x14 */ BOOL choiceSignal;
    /* 0x18 */ u32 messToBeSet;
    /* 0x1C */ s32 choice;
    /* 0x20 */ s32 state; // TODO add defines
} OptionWindow; // Size 0x24

void OptionFadeSprite(s16 sprite, BOOL inF, s32 duration);
void OptionFadeModel(s16 model, BOOL inF, s32 duration);

BOOL OptionPadCheck(u16 btn);
BOOL OptionPadDStkRepCheck(u16 arg0);
BOOL OptionPadDStkCheck(u16 arg0);

omObjData *OptionCameraCreate(void);
void OptionCameraKill(omObjData *object);
void OptionCameraTargetSet(omObjData *object, float x, float y, float z, s32 duration);
void OptionCameraFocusSet(omObjData *object, float x, float y, float z, s32 duration);
void OptionCameraViewSet(omObjData *object, float zoom, float rot, float y, s32 duration);
float OptionCameraZoomGet(omObjData *object);
float OptionCameraRotGet(omObjData *object);
void OptionCameraPosGet(omObjData *object, float *x, float *y, float *z);

void OptionCameraTargetGet(omObjData *object, float *x, float *y, float *z);
s32 OptionCameraDoneCheck(omObjData *object);

omObjData *OptionRoomCreate(void);
void OptionRoomKill(omObjData *object);
void OptionRoomExecModeSet(omObjData *object, s32 execMode);
s32 OptionRoomExecModeGet(omObjData *object);

omObjData *OptionGuideCreate(void);
void OptionGuideKill(omObjData *object);
void OptionGuideWalkExec(omObjData *object, float angleEnd, float camDist, s32 duration);

omObjData *OptionStateCreate(void);
void OptionStateKill(omObjData *object);

omObjData *OptionRumbleCreate(void);
void OptionRumbleKill(omObjData *object);
void OptionRumbleExecModeSet(omObjData *object, s32 execMode);
s32 OptionRumbleExecModeGet(omObjData *object);
void OptionRumbleMotionShowStart(omObjData *object);
void OptionRumbleMotionHideStart(omObjData *object);
BOOL OptionRumbleMotionCheck(omObjData *object);

omObjData *OptionSoundCreate(void);
void OptionSoundKill(omObjData *object);
void OptionSoundExecModeSet(omObjData *object, s32 execMode);
s32 OptionSoundExecModeGet(omObjData *object);

omObjData *OptionRecordCreate(void);
void OptionRecordKill(omObjData *object);
void OptionRecordExecModeSet(omObjData *object, s32 execMode);
s32 OptionRecordExecModeGet(omObjData *object);

OptionWindow *OptionWinCreate(s32 id);
void OptionWinKill(OptionWindow *work);
void OptionWinAnimIn(OptionWindow *work);
void OptionWinAnimOut(OptionWindow *work);
void OptionWinMesSet(OptionWindow *work, s32 mess);
void OptionWinInsertMesSet(OptionWindow *work, s32 mess, s16 index);
void OptionWinPosSet(OptionWindow *work, float x, float y);
void OptionWinDispOn(OptionWindow *work);
void OptionWinDispOff(OptionWindow *work);
void fn_1_A860(OptionWindow *work);
void fn_1_A880(OptionWindow *work, s32 choice);

extern Process *optionObjMan;
extern omObjData *optionCamera;
extern omObjData *optionRoom;
extern omObjData *optionGuide;
extern omObjData *optionState;
extern omObjData *optionRumble;
extern omObjData *optionSound;
extern omObjData *optionRecord;

#endif
