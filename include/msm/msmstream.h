#ifndef MSMSTREAM_H
#define MSMSTREAM_H

#include "game/msm.h"

s32 msmStreamGetStatus(int streamNo);
void msmStreamSetMasterVolume(s32 arg0);
void msmStreamStopAll(s32 speed);
s32 msmStreamStop(int streamNo, s32 speed);
int msmStreamPlay(int streamId, MSM_STREAMPARAM* streamParam);
void msmStreamPeriodicProc(void);
void msmStreamSetOutputMode(s32 arg0);
void msmStreamAmemFree(void);
s32 msmStreamAmemAlloc(void);
s32 msmStreamInit(char* arg0);
void msmStreamPauseOff(s32 arg0);
void msmStreamPauseOn(s32 streamNo, s32 arg1);
s32 msmStreamPackStartStereo(s32 arg0, MSM_STREAMPARAM* arg1, s32 arg2);
s32 msmStreamPackStartMono(s32 arg0, MSM_STREAMPARAM* arg1, s32 arg2);
void msmStreamSlotOff(s32 streamNo);

#endif
