#ifndef _BOARD_UI_H
#define _BOARD_UI_H

#include "game/sprite.h"

s32 BoardItemModelGet(s32 arg0);
s32 BoardItemNameGet(s32 arg0);
BOOL BoardStatusStopCheck(s32 arg0);
s32 BoardStatusVisibleGet(s32 arg0);
void BoardStatusShowSetAll(s32 arg0);
void BoardStatusItemSet(s32 arg0);
void BoardStatusShowSetForce(s32 arg0);
void BoardStatusGraySet(s32 arg0, s32 arg1);
void BoardStatusShowSet(s32 arg0, s32 arg1);
void BoardStatusItemHideSet(s32 arg0, s32 arg1);
void BoardStatusTargetPosSet(s32 arg0, Vec *arg1);
void BoardStatusPosGet(s32 arg0, Vec *arg1);
void BoardStatusPosSet(s32 arg0, Vec *arg1);
void BoardStatusHammerCreate(s32 arg0);
void BoardStatusHammerShowSet(s32 arg0, s32 arg1);
void BoardStatusHammerKill(s32 arg0);
void BoardStatusKill(void);
void BoardStatusCreate(void);
void BoardSpriteCreate(s32 file, s32 prio, ANIMDATA **anim, s16 *sprite);
void BoardSpriteDigitUpdate(s16 arg0, s16 arg1, s32 arg2);
void BoardPickerCreate(s32 arg0, s8 arg1, void *arg2, s8 arg3);
void BoardPickerBackFlagSet(s32 arg0);
BOOL BoardPickerDoneCheck(void);
s32 BoardPickerPosGet(Vec *arg0);
s32 BoardPickerChoiceGet(void);
void BoardYourTurnExec(s32 arg0);
s32 BoardItemUseExec(s32 arg0);
void BoardMakeRandomItem(void);
void BoardItemGetDestPos(s32 arg0, Vec *arg1);
void BoardItemStatusKill(s32 arg0);

extern s8 boardItemUser;

#endif
