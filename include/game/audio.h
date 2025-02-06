#ifndef _GAME_AUDIO_H
#define _GAME_AUDIO_H

#include "dolphin.h"

typedef struct sndGrpTbl_s {
    s16 ovl;
    s16 grpSet;
    s32 auxANo;
    s32 auxBNo;
    s8 auxAVol;
    s8 auxBVol;
} SNDGRPTBL;


void HuAudInit(void);
s32 HuAudStreamPlay(char *name, BOOL flag);
void HuAudStreamVolSet(s16 vol);
void HuAudStreamPauseOn(void);
void HuAudStreamPauseOff(void);
void HuAudStreamFadeOut(s32 streamNo);
void HuAudAllStop(void);
void HuAudFadeOut(s32 speed);
int HuAudFXPlay(int seId);
int HuAudFXPlayVol(int seId, s16 vol);
int HuAudFXPlayVolPan(int seId, s16 vol, s16 pan);
void HuAudFXStop(int seNo);
void HuAudFXAllStop(void);
void HuAudFXFadeOut(int seNo, s32 speed);
void HuAudFXPanning(int seNo, s16 pan);
void HuAudFXListnerSet(Vec *pos, Vec *heading, float sndDist, float sndSpeed);
void HuAudFXListnerSetEX(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis);
void HuAudFXListnerUpdate(Vec *pos, Vec *heading);
int HuAudFXEmiterPlay(int seId, Vec *pos);
void HuAudFXEmiterUpDate(int seNo, Vec *pos);
void HuAudFXListnerKill(void);
void HuAudFXPauseAll(s32 pause);
s32 HuAudFXStatusGet(int seNo);
s32 HuAudFXPitchSet(int seNo, s16 pitch);
s32 HuAudFXVolSet(int seNo, s16 vol);
s32 HuAudSeqPlay(s16 musId);
void HuAudSeqStop(s32 musNo);
void HuAudSeqFadeOut(s32 musNo, s32 speed);
void HuAudSeqAllFadeOut(s32 speed);
void HuAudSeqAllStop(void);
void HuAudSeqPauseAll(s32 pause);
void HuAudSeqPause(s32 musNo, s32 pause, s32 speed);
s32 HuAudSeqMidiCtrlGet(s32 musNo, s8 channel, s8 ctrl);
s32 HuAudSStreamPlay(s16 streamId);
void HuAudSStreamStop(s32 seNo);
void HuAudSStreamFadeOut(s32 seNo, s32 speed);
void HuAudSStreamAllFadeOut(s32 speed);
void HuAudSStreamAllStop(void);
s32 HuAudSStreamStatGet(s32 seNo);
void HuAudDllSndGrpSet(u16 ovl);
void HuAudSndGrpSetSet(s16 data_size);
void HuAudSndGrpSet(s16 grpId);
void HuAudSndCommonGrpSet(s16 grpId, s32 groupCheck);
void HuAudAUXSet(s32 auxA, s32 auxB);
void HuAudAUXVolSet(s8 auxA, s8 auxB);
void HuAudVoiceInit(s16 ovl);
s32 HuAudPlayerVoicePlay(s16 player, s16 seId);
s32 HuAudPlayerVoicePlayPos(s16 player, s16 seId, Vec *pos);
void HuAudPlayerVoicePlayEntry(s16 player, s16 seId);
s32 HuAudCharVoicePlay(s16 charNo, s16 seId);
s32 HuAudCharVoicePlayPos(s16 charNo, s16 seId, Vec *pos);
void HuAudCharVoicePlayEntry(s16 charNo, s16 seId);

extern float Snd3DBackSurDisOffset;
extern float Snd3DFrontSurDisOffset;
extern float Snd3DStartDisOffset;
extern float Snd3DSpeedOffset;
extern float Snd3DDistOffset;
extern s32 musicOffF;
extern u8 fadeStat;

extern SNDGRPTBL sndGrpTable[];

#endif
