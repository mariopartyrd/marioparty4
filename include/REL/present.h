#ifndef REL_PRESENT_H
#define REL_PRESENT_H

#include "game/object.h"

typedef struct PresentWindow {
    /* 0x00 */ HUPROCESS *process;
    /* 0x04 */ s16 window;
    /* 0x08 */ s32 id;
    /* 0x0C */ BOOL visible;
    /* 0x10 */ s32 messWaitSignal;
    /* 0x14 */ s32 choiceSignal;
    /* 0x18 */ u32 messToBeSet;
    /* 0x1C */ s32 choice;
    /* 0x20 */ s32 state;
} PresentWindow; /* size 0x24 */ // this already exists in option.h

#define PRESENT_GUIDE_MODE_NONE 0
#define PRESENT_GUIDE_MODE_ENTER 1
#define PRESENT_GUIDE_MODE_LEAVE 2

#define PRESENT_MODE_NONE 0
#define PRESENT_MODE_SELECT_ROOM 1
#define PRESENT_MODE_SELECT_PRESENT 2
#define PRESENT_MODE_GET 3

extern OMOBJ *present;
extern OMOBJ *presentCamera;
extern HUPROCESS *presentObjMan;

void PresentFadeSprite(s16 sprite, BOOL inF, s32 duration);
void FadeSpriteWithMultiplier(s16 model, BOOL inF, float tpMultiplier, s32 duration);
BOOL PresentPadCheck(u16 btn);
BOOL PresentPadDStkRepCheck(u16 dir);
BOOL PresentPadDStkCheck(u16 dir);
OMOBJ *PresentCameraCreate();
void PresentCameraKill(OMOBJ *object);
void PresentCameraTargetSet(OMOBJ *object, float x, float y, float z, s32 duration);
void PresentCameraFocusSet(OMOBJ *object, float x, float y, float z, s32 duration);
s32 PresentCameraDoneCheck(OMOBJ *object);
OMOBJ *PresentCreate(void);
void PresentKill(OMOBJ *object);
void PresentExecModeSet(OMOBJ *object, s32 execMode);
s32 PresentExecModeGet(OMOBJ *object);
void PresentSelectedIDSet(OMOBJ *object, s32 id);
void PresentStateKill(OMOBJ *object);
OMOBJ *PresentStateCreate(void);
PresentWindow *PresentWinCreate(s32 id);
void PresentWinKill(PresentWindow *work);
void PresentWinAnimIn(PresentWindow *work);
void PresentWinAnimOut(PresentWindow *work);
void PresentWinMesSet(PresentWindow *work, u32 mess);
void PresentWinInsertMesSet(PresentWindow *work, u32 mess, s16 index);
void PresentWinMesWait(PresentWindow *work);
OMOBJ *PresentGuideCreate(void);
void PresentGuideKill(OMOBJ *object);
void PresentGuideExecModeSet(OMOBJ *object, s32 execMode);
s32 PresentGuideExecModeGet(OMOBJ *object);

#endif
