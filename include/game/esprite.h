#ifndef _GAME_ESPRITE_H
#define _GAME_ESPRITE_H

#include "dolphin.h"

void espInit(void);
s16 espEntry(unsigned int dataNum, s16 prio, s16 bank);
void espKill(s16 espId);
s16 espGrpIDGet(void);
void espDispOn(s16 espId);
void espDispOff(s16 espId);
void espAttrSet(s16 espId, u16 attr);
void espAttrReset(s16 espId, u16 attr);
void espPosSet(s16 espId, float posX, float posY);
void espScaleSet(s16 espId, float scaleX, float scaleY);
void espZRotSet(s16 espId, float zRot);
void espTPLvlSet(s16 espId, float tpLvl);
void espColorSet(s16 espId, u8 r, u8 g, u8 b);
void espSpeedSet(s16 espId, float speed);
void espBankSet(s16 espId, s16 bank);
void espDrawNoSet(s16 espId, s16 drawNo);
void espPriSet(s16 espId, s16 pri);

#endif
