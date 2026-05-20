#ifndef _BOARD_BOO_H
#define _BOARD_BOO_H

#include "dolphin.h"
#include "game/object.h"

s16 BoardBooCreate(s32 arg0, Vec *arg1);
void BoardBooKill(void);
s32 BoardBooStealTypeSet(s32 arg0);
s32 BoardBooStealMain(void);
s32 BoardBooStealValueGet(s16 *arg0, s16 *arg1);
BOOL BoardBooStealLightCheck(void);

#endif
