#ifndef _GAME_PAD_H
#define _GAME_PAD_H

#include "dolphin.h"
#include "version.h"

#define PAD_BUTTON_DIR (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT | PAD_BUTTON_UP | PAD_BUTTON_DOWN)

#define PAD_BUTTON_TRIGGER_L 0x4000
#define PAD_BUTTON_TRIGGER_R 0x2000

SHARED_SYM extern u16 HuPadBtn[4];
SHARED_SYM extern u16 HuPadBtnDown[4];
SHARED_SYM extern u16 HuPadBtnRep[4];
SHARED_SYM extern s8 HuPadStkX[4];
SHARED_SYM extern s8 HuPadStkY[4];
SHARED_SYM extern s8 HuPadSubStkX[4];
SHARED_SYM extern s8 HuPadSubStkY[4];
SHARED_SYM extern u8 HuPadTrigL[4];
SHARED_SYM extern u8 HuPadTrigR[4];
SHARED_SYM extern u8 HuPadDStk[4];
SHARED_SYM extern u8 HuPadDStkRep[4];
extern s8 HuPadErr[4];
extern u16 _PadBtn[4];
extern u16 _PadBtnDown[4];
extern s32 VCounter;

void HuPadInit(void);
void HuPadRead(void);
void HuPadRumbleSet(s16 pad, s16 duration, s16 off, s16 on);
void HuPadRumbleStop(s16 pad);
void HuPadRumbleAllStop(void);
s16 HuPadStatGet(s16 pad);
u32 HuPadRumbleGet(void);

#endif
