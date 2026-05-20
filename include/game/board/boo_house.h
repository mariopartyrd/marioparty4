#ifndef BOO_HOUSE_H
#define BOO_HOUSE_H

#include "dolphin/types.h"


void BoardBooHouseHostSet(s16);
s16 BoardBooHouseHostGet(void);
void BoardBooHouseCreate(void);
void BoardBooHouseExec(s32);
void BoardBooHouseKill(void);

s32 BoardBooComUseCheck(s32);
void BoardBooHouseTutorialExec(void);

#endif
