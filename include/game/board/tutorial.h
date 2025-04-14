#ifndef _BOARD_TUTORIAL_H
#define _BOARD_TUTORIAL_H

#include "dolphin/types.h"
#include "version.h"

void BoardTutorialInit(void);
void BoardTutorialKill(void);
void BoardTutorialHookSet(void *arg0);
void BoardTutorialHookExec(s16 arg0, s32 arg1);
void BoardTutorialPlayerInit(void);
void BoardTutorialWorkSave(void);
void BoardTutorialWorkRestore(void);
void BoardTutorialDirInputSet(s8 arg0, s8 arg1, s16 arg2);
void BoardTutorialBlockSetPos(s32 arg0, s8 arg1);
void BoardTutorialItemSet(s8 arg0);
void BoardTutorialHostSet(s16 arg0);
void BoardTutorialHostHide(s8 arg0);

SHARED_SYM extern s32 boardTutorialData[4];
extern s8 boardTutorialDirInputX;
extern s8 boardTutorialDirInputY;
extern s16 boardTutorialDirInputTime;
extern s32 boardTutorialBlockPos;
extern s8 boardTutorialBlockItem;
extern s8 boardTutorialBlockF;
extern s8 boardTutorialUseItem;
SHARED_SYM extern s8 boardTutorialF;

#endif
