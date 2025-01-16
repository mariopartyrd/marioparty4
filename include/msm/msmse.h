#ifndef MSMSE_H
#define MSMSE_H

#include "game/msm.h"
#include "msm/msmsys.h"

void msmSePeriodicProc(void);
MSMSE* msmSeGetIndexPtr(s32 arg0);
void msmSeDelListener(void);
s32 msmSeUpdataListener(Vec* pos, Vec* heading);
s32 msmSeSetListener(Vec* pos, Vec* heading, float sndDist, float sndSpeed, MSM_SELISTENER* listener);
s32 msmSeGetEntryID(s32 seId, int* seNo);
s32 msmSeGetNumPlay(BOOL baseGrp);
s32 msmSeGetStatus(int seNo);
void msmSeSetMasterVolume(s32 arg0);
s32 msmSeSetParam(int seNo, MSM_SEPARAM* param);
void msmSePauseAll(BOOL pause, s32 speed);
void msmSeStopAll(BOOL checkGrp, s32 speed);
s32 msmSeStop(int seNo, s32 speed);
int msmSePlay(int seId, MSM_SEPARAM* param);
s32 msmSeInit(sysData* arg0, DVDFileInfo* arg1);

#endif
