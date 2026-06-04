#ifndef REL_OPTION_H
#define REL_OPTION_H

#include "game/object.h"

#include "dolphin/types.h"

typedef struct {
    /* 0x00 */ HUPROCESS *process;
    /* 0x04 */ s16 window;
    /* 0x08 */ s32 id;
    /* 0x0C */ BOOL visible;
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

OMOBJ *OptionCameraCreate(void);
void OptionCameraKill(OMOBJ *object);
void OptionCameraTargetSet(OMOBJ *object, float x, float y, float z, s32 duration);
void OptionCameraFocusSet(OMOBJ *object, float x, float y, float z, s32 duration);
void OptionCameraViewSet(OMOBJ *object, float zoom, float rot, float y, s32 duration);
float OptionCameraZoomGet(OMOBJ *object);
float OptionCameraRotGet(OMOBJ *object);
void OptionCameraPosGet(OMOBJ *object, float *x, float *y, float *z);

void OptionCameraTargetGet(OMOBJ *object, float *x, float *y, float *z);
s32 OptionCameraDoneCheck(OMOBJ *object);

OMOBJ *OptionRoomCreate(void);
void OptionRoomKill(OMOBJ *object);
void OptionRoomExecModeSet(OMOBJ *object, s32 execMode);
s32 OptionRoomExecModeGet(OMOBJ *object);

OMOBJ *OptionGuideCreate(void);
void OptionGuideKill(OMOBJ *object);
void OptionGuideWalkExec(OMOBJ *object, float angleEnd, float camDist, s32 duration);

OMOBJ *OptionStateCreate(void);
void OptionStateKill(OMOBJ *object);

OMOBJ *OptionRumbleCreate(void);
void OptionRumbleKill(OMOBJ *object);
void OptionRumbleExecModeSet(OMOBJ *object, s32 execMode);
s32 OptionRumbleExecModeGet(OMOBJ *object);
void OptionRumbleMotionShowStart(OMOBJ *object);
void OptionRumbleMotionHideStart(OMOBJ *object);
BOOL OptionRumbleMotionCheck(OMOBJ *object);

OMOBJ *OptionSoundCreate(void);
void OptionSoundKill(OMOBJ *object);
void OptionSoundExecModeSet(OMOBJ *object, s32 execMode);
s32 OptionSoundExecModeGet(OMOBJ *object);

OMOBJ *OptionRecordCreate(void);
void OptionRecordKill(OMOBJ *object);
void OptionRecordExecModeSet(OMOBJ *object, s32 execMode);
s32 OptionRecordExecModeGet(OMOBJ *object);

OptionWindow *OptionWinCreate(s32 id);
void OptionWinKill(OptionWindow *work);
void OptionWinAnimIn(OptionWindow *work);
void OptionWinAnimOut(OptionWindow *work);
void OptionWinMesSet(OptionWindow *work, s32 mess);
void OptionWinInsertMesSet(OptionWindow *work, s32 mess, s16 index);
void OptionWinPosSet(OptionWindow *work, float x, float y);
void OptionWinDispOn(OptionWindow *work);
void OptionWinDispOff(OptionWindow *work);
void OptionWinChoiceSet(OptionWindow *work, s32 choice);
void fn_1_A860(OptionWindow *work);
void fn_1_A880(OptionWindow *work, s32 choice);

extern HUPROCESS *optionObjMan;
extern OMOBJ *optionCamera;
extern OMOBJ *optionRoom;
extern OMOBJ *optionGuide;
extern OMOBJ *optionState;
extern OMOBJ *optionRumble;
extern OMOBJ *optionSound;
extern OMOBJ *optionRecord;

#endif
