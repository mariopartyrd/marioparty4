#ifndef _GAME_GAMEWORK_H
#define _GAME_GAMEWORK_H

#include "dolphin.h"

#define GW_PLAYER_MAX 4

void GWInit(void);
void GWGameStatReset(void);
s32 GWMessSpeedGet(void);
s32 GWMessDelayGet(void);
void GWMGRecordSet(s32 index, s32 value);
s32 GWMGRecordGet(s32 index);
void GWCharColorGet(s32 character, GXColor *color);
void GWBoardPlayCountSet(s32 board, u8 value);
void GWBoardPlayCountAdd(s32 board, u8 value);
u8 GWBoardPlayCountGet(s32 board);
void GWBoardMaxStarsSet(s32 board, s32 value);
u16 GWBoardMaxStarsGet(s32 board);
void GWBoardMaxCoinsSet(s32 board, s32 value);
u16 GWBoardMaxCoinsGet(s32 board);
s32 GWBoardWinCountInc(s32 character, s32 board);
s32 GWBoardWinCountGet(s32 character, s32 board);
void GWBoardWinCountSet(s32 character, s32 board, s32 value);
s32 GWMGAvailGet(s32 id);
s32 GWMGAvailSet(s32 id);
s32 GWMGCustomGet(s32 id);
void GWMGCustomSet(s32 id);
void GWMGCustomReset(s32 id);
s16 GWCoinsGet(s32 player);
void GWCoinsSet(s32 player, s16 value);
void GWCoinsAdd(s32 player, s16 amount);
void GWStarsSet(s32 player, s16 value);
void GWStarsAdd(s32 player, s16 amount);
s32 GWStarsGet(s32 player);
void GWTotalStarsSet(s16 value);
void GWTotalStarsAdd(s16 amount);
u16 GWTotalStarsGet(void);

#endif