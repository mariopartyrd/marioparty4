#ifndef MSMMUS_H
#define MSMMUS_H

#include "game/msm.h"
#include "msm/msmsys.h"

#include "dolphin.h"

void msmMusFdoutEnd(void);
void msmMusPeriodicProc(void);
s32 msmMusGetMidiCtrl(int musNo, s32 channel, s32 ctrl);
s32 msmMusGetNumPlay(BOOL baseGrp);
s32 msmMusGetStatus(int musNo);
void msmMusSetMasterVolume(s32 arg0);
s32 msmMusSetParam(s32 arg0, MSM_MUSPARAM* arg1);
void msmMusPauseAll(BOOL pause, s32 speed);
s32 msmMusPause(int musNo, BOOL pause, s32 speed);
void msmMusStopAll(BOOL checkGrp, s32 speed);
s32 msmMusStop(int musNo, s32 speed);
int msmMusPlay(int musId, MSM_MUSPARAM* musParam);
s32 msmMusInit(sysData* arg0, DVDFileInfo* arg1);

#endif
