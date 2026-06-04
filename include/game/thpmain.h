#ifndef _GAME_THPMAIN_H
#define _GAME_THPMAIN_H

#include "dolphin/types.h"
#include "game/process.h"


s16 HuTHPSprCreateVol(char *path, s16 loop, s16 prio, float volume);
s16 HuTHPSprCreate(char *path, s16 loop, s16 prio);
s16 HuTHP3DCreateVol(char *path, s16 loop, float volume);
s16 HuTHP3DCreate(char *path, s16 loop);
void HuTHPStop(void);
void HuTHPClose(void);
void HuTHPRestart(void);
BOOL HuTHPEndCheck(void);
s32 HuTHPFrameGet(void);
s32 HuTHPTotalFrameGet(void);
void HuTHPSetVolume(s32 left, s32 right);

extern HUPROCESS *THPProc;


#endif