#ifndef _BOARD_BASIC_SPACE_H
#define _BOARD_BASIC_SPACE_H

#include "dolphin.h"

void BoardLandBlueExec(s32 player, s32 space);
void BoardLandRedExec(s32 player, s32 space);
void BoardEventLandBlue(s32, s32);
void BoardEventLandRed(s32, s32);
s8 BoardCoinChgCreate(Vec*, s8);
s32 BoardCoinChgExist(s32);
void BoardCoinChgHide(s32);

#endif
