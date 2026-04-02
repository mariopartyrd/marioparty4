#ifndef _DOLPHIN_PAD
#define _DOLPHIN_PAD

#include <dolphin/types.h>

extern u32 __PADFixBits;

#define PAD_SPEC_0 0
#define PAD_SPEC_1 1
#define PAD_SPEC_2 2
#define PAD_SPEC_3 3
#define PAD_SPEC_4 4
#define PAD_SPEC_5 5

#define PAD_CHAN0 0
#define PAD_CHAN1 1
#define PAD_CHAN2 2
#define PAD_CHAN3 3
#define PAD_CHANMAX 4

#define PAD_MOTOR_STOP 0
#define PAD_MOTOR_RUMBLE 1
#define PAD_MOTOR_STOP_HARD 2

#define PAD_ERR_NONE 0
#define PAD_ERR_NO_CONTROLLER -1
#define PAD_ERR_NOT_READY -2
#define PAD_ERR_TRANSFER -3

#define PAD_BUTTON_LEFT 0x0001
#define PAD_BUTTON_RIGHT 0x0002
#define PAD_BUTTON_DOWN 0x0004
#define PAD_BUTTON_UP 0x0008
#define PAD_TRIGGER_Z 0x0010
#define PAD_TRIGGER_R 0x0020
#define PAD_TRIGGER_L 0x0040
#define PAD_BUTTON_A 0x0100
#define PAD_BUTTON_B 0x0200
#define PAD_BUTTON_X 0x0400
#define PAD_BUTTON_Y 0x0800
#define PAD_BUTTON_MENU 0x1000
#define PAD_BUTTON_START 0x1000

#define PAD_CHAN0_BIT 0x80000000
#define PAD_CHAN1_BIT 0x40000000
#define PAD_CHAN2_BIT 0x20000000
#define PAD_CHAN3_BIT 0x10000000

#define PADButtonDown(buttonLast, button) ((((buttonLast) ^ (button)) & (button)))

#define PADButtonUp(buttonLast, button) ((((buttonLast) ^ (button)) & (buttonLast)))

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*PADSamplingCallback)(void);

typedef struct PADStatus {
  u16 button;
  s8 stickX;
  s8 stickY;
  s8 substickX;
  s8 substickY;
  u8 triggerL;
  u8 triggerR;
  u8 analogA;
  u8 analogB;
  s8 err;
} PADStatus;

BOOL PADInit();
u32 PADRead(PADStatus* status);
BOOL PADReset(u32 mask);
BOOL PADRecalibrate(u32 mask);
void PADClamp(PADStatus* status);
void PADClampCircle(PADStatus* status);
void PADControlMotor(s32 chan, u32 cmd);
void PADSetSpec(u32 spec);
void PADControlAllMotors(const u32* cmdArr);
void PADSetAnalogMode(u32 mode);
PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback);

#ifdef TARGET_PC
/* New API to facilitate controller interactions */
typedef struct PADDeadZones {
  BOOL emulateTriggers;
  BOOL useDeadzones;
  u16 stickDeadZone;
  u16 substickDeadZone;
  u16 leftTriggerActivationZone;
  u16 rightTriggerActivationZone;
} PADDeadZones;

typedef u16 PADButton;

typedef struct PADButtonMapping {
  u32 nativeButton;
  PADButton padButton;
} PADButtonMapping;

/* Returns the total number of controllers */
u32 PADCount();
/* Returns the controller name for the given index into the controller map */
const char* PADGetNameForControllerIndex(u32 idx);
void PADSetPortForIndex(u32 index, s32 port);
s32 PADGetIndexForPort(u32 port);
void PADGetVidPid(u32 port, u32* vid, u32* pid);
void PADClearPort(u32 port);
const char* PADGetName(u32 port);
void PADSetButtonMapping(u32 port, PADButtonMapping mapping);
void PADSetAllButtonMappings(u32 port, PADButtonMapping buttons[12]);
PADButtonMapping* PADGetButtonMappings(u32 port, u32* buttonCount);
void PADSerializeMappings();
PADDeadZones* PADGetDeadZones(u32 port);
const char* PADGetButtonName(PADButton);
const char* PADGetNativeButtonName(u32 button);
/* Returns any pressed native button */
s32 PADGetNativeButtonPressed(u32 port);
void PADRestoreDefaultMapping(u32 port);
void PADBlockInput(BOOL block);
#endif

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_PAD
