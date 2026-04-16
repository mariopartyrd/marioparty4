#ifndef _BOARD_ROLL_H
#define _BOARD_ROLL_H

#include "dolphin/types.h"

s32 BoardRollExec(s32 playerNo);
void BoardRollKill(void);
void BoardRollUPauseSet(s32 arg0);
void BoardRollWinDispSet(s32 arg0);
s16 BoardDiceEffectCreate(void);
void BoardDicePauseAll(void);
BOOL BoardDiceDoneCheck(void);
void BoardDiceStop(s32 arg0);
void BoardDiceVisibleSet(s32 arg0, s32 arg1);
void BoardDiceValueSet(s32 arg0, s32 arg1);
void BoardRollTutorialSet(s16 *arg0);

#endif
