#ifndef REL_MENTDLL_H
#define REL_MENTDLL_H

#include "game/object.h"
extern s32 menuSoundFXTbl[][4];

// the prev and current struct member might be vice versa
typedef struct MentDllUnkBss64Struct {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ void (*func2)(float arg9);
    /* 0x08 */ Vec center;
    /* 0x14 */ Vec prevCenter;
    /* 0x20 */ Vec rot;
    /* 0x2C */ Vec prevRot;
    /* 0x38 */ float zoom;
    /* 0x3C */ float prevZoom;
    /* 0x40 */ s32 frames;
} MenuCamera; /* size = 0x44 */
extern MenuCamera menuCamera;

float LerpClamped(float start, float end, float weight, float max_weight);
float WeightedBlend(float start, float end, float weight);
float CosEaseClamped(float start, float end, float progress, float maxProgress);
float SinEaseClamped(float start, float end, float progress, float maxProgress);
float SinOscillateClamped(float start, float end, float progress, float maxProgress);
void MenuPrcSleep(s32 time);
void MenuPrcVSleep(void);
void MenuLightInit(void);
void MenuShadowInit(s32 eventNo);
void MenuWinInit(void);
s32 OpenWindowBottom(s32 xAlign, s32 arg1, s32 arg2);
void DestroyWin(s32 winId);
void WinSetMessAndWait(s32 winId, s32 mess, s32 maxWaits, s32 sleepDur);
s32 OpenConfirmDlgYesDef(s32 mess, s32 mode, s32 arg2);
s32 OpenConfirmDlgNoDef(s32 mess, s32 mode, s32 arg2);
s32 OpenAvailControlsWin(s32 mess);
void destroyAvailControlsWin(s32 arg0);
void moveCameraWithMethod(void (*cameraMoveMethod)(void));
void MenuCameraInit(HUPROCESS *objman, void (*cameraIntroMethod)(void));
void MenuCameraSnapshot(MenuCamera *menuCamera);
void MenuCameraSinEaseFollow(MenuCamera *srcCamera, MenuCamera *targetCamera, f32 progress, f32 maxProgress, f32 weight);
void MenuCameraCosEaseFollow(MenuCamera *srcCamera, MenuCamera *targetCamera, f32 progress, f32 maxProgress, f32 weight);
void motionShift(OMOBJ *obj, s32 mdlId, s32 mtnId, s32 shiftTime, s32 attr);
void motionShiftIfChanged(OMOBJ *obj, s32 mdlId, s32 mtnId, s32 shiftTime, s32 attr);
void motionShiftTick(OMOBJ *obj);
void WaitAnimEnd(OMOBJ *obj, s32 mdlId, s32 initialDelay);
void MenuMoveChar(OMOBJ *obj, s32 mdlId, Vec targePos, float endRotAngle, float speed, float rotDur, s32 enableMove, s32 enableRot);
void sprPosSetYPad(s32 grpId, s32 memberNo, float posX, float posY);
void MenuMain(HUPROCESS *objman);

#endif
