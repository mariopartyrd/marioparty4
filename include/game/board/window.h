#ifndef _BOARD_WINDOW_H
#define _BOARD_WINDOW_H

#include "game/window.h"

typedef void (*BoardWinComKeyFunc)();

void BoardWinInit(void);
void BoardWinUnusedArraySet(f32*);
void BoardWinKillAll(void);
void BoardWinDestroy(void);
void BoardWinProc(void);
s32 BoardWinChoiceGet(void);
void BoardWinPause(void);
void BoardWinCreateChoice(s32 pos, u32 mess, s32 portrait, s32 choice);
void BoardWinCreate(s32 pos, u32 mess, s32 portrait);
void BoardWinInsertMesSet(u32 value, s32 index);
void BoardWinWait(void);
void BoardWinKill(void);
void BoardWinAttrSet(s32 attr);
void BoardWinAttrReset(s32 attr);
void BoardWinChoiceDisable(s32 choice);
void BoardWinKeyWait(void);
s32 BoardWinSpeedGet(void);
void BoardWinSpeedSet(s32 value);
s16 BoardWinChoiceNowGet(void);
void BoardWinPriSet(s16 prio);
s16 BoardWinChoiceNowGet2(void);
s32 BoardWinPortraitGet(void);
s32 BoardWinPortraitGetStar(void);
void BoardWinPlayerSet(s32 player);
void BoardWinStartComKeySet(void);
void BoardWinComKeyFuncSet(BoardWinComKeyFunc func);
s16 BoardWinIDGet(void);

#if TARGET_PC
void BoardWinInsertMesSetPtr(uintptr_t value, s32 index);
#define BOARD_WIN_MES_SET_PTR BoardWinInsertMesSetPtr
#else
#define BOARD_WIN_MES_SET_PTR BoardWinInsertMesSet
#endif

#endif