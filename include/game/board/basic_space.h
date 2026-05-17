#ifndef _BOARD_BASIC_SPACE_H
#define _BOARD_BASIC_SPACE_H

#include "dolphin.h"

void BoardEventLandBlue(s32, s32);
void BoardEventLandRed(s32, s32);
s8 BoardCoinChgCreate(Vec*, s8);
s32 BoardCoinChgKillCheck(s32);
void BoardCoinChgKill(s32);

#endif
