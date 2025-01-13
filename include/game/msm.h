#ifndef MSM_H
#define MSM_H

#include "dolphin.h"
#include "musyx/musyx.h"

#define MSM_SEPARAM_NONE 0
#define MSM_SEPARAM_VOL (1 << 0)
#define MSM_SEPARAM_PAN (1 << 1)
#define MSM_SEPARAM_PITCH (1 << 2)
#define MSM_SEPARAM_SPAN (1 << 3)
#define MSM_SEPARAM_AUXVOLA (1 << 4)
#define MSM_SEPARAM_AUXVOLB (1 << 5)
#define MSM_SEPARAM_POS (1 << 6)

#define MSM_LISTENER_NONE 0
#define MSM_LISTENER_STARTDIS (1 << 0)
#define MSM_LISTENER_FRONTSURDIS (1 << 1)
#define MSM_LISTENER_BACKSURDIS (1 << 2)

#define MSM_MUSPARAM_NONE 0
#define MSM_MUSPARAM_CHAN (1 << 0)
#define MSM_MUSPARAM_VOL (1 << 1)
#define MSM_MUSPARAM_PAUSE (1 << 2)
#define MSM_MUSPARAM_FADESPEED (1 << 3)
#define MSM_MUSPARAM_SPEED (1 << 4)

#define MSM_STREAMPARAM_NONE 0
#define MSM_STREAMPARAM_VOL (1 << 0)
#define MSM_STREAMPARAM_PAN (1 << 1)
#define MSM_STREAMPARAM_SPAN (1 << 2)
#define MSM_STREAMPARAM_AUXA (1 << 4)
#define MSM_STREAMPARAM_AUXB (1 << 5)
#define MSM_STREAMPARAM_FADESPEED (1 << 8)
#define MSM_STREAMPARAM_CHAN (1 << 9)
#define MSM_STREAMPARAM_PAUSE (1 << 10)

#define MSM_ERR_OPENFAIL -1
#define MSM_ERR_READFAIL -2
#define MSM_ERR_OUTOFMEM -10
#define MSM_ERR_OUTOFAMEM -20
#define MSM_ERR_INITFAIL -20
#define MSM_ERR_INVALID_AUXPARAM -31
#define MSM_ERR_PLAYFAIL -33
#define MSM_ERR_22 -34
#define MSM_ERR_STREAMALLOC_FAIL -35
#define MSM_ERR_INSTALLED -36
#define MSM_ERR_GRP_NOTLOADED -103
#define MSM_ERR_6F -111
#define MSM_ERR_INVALIDID -120
#define MSM_ERR_INVALIDFILE -121
#define MSM_ERR_REMOVEDID -122
#define MSM_ERR_MUSGRP_NOTLOADED -123
#define MSM_ERR_OUTOFMUS -130

#define MSM_VOL_MAX 127
#define MSM_PAN_LEFT 32
#define MSM_PAN_CENTER 64
#define MSM_PAN_RIGHT 96

#define MSM_SE_DONE 0
#define MSM_SE_PLAY 1
#define MSM_SE_PAUSEIN 2
#define MSM_SE_PAUSEOUT 3

#define MSM_MUS_DONE 0
#define MSM_MUS_STOP 1
#define MSM_MUS_PLAY 2
#define MSM_MUS_PAUSE 3

#define MSM_STREAM_DONE 0
#define MSM_STREAM_STOP 1
#define MSM_STREAM_PLAY 2
#define MSM_STREAM_PAUSEIN 3
#define MSM_STREAM_PAUSEOUT 4
#define MSM_STREAM_DVDERROR 5

#define MSM_MUS_MAX 4

#define MSM_STREAM_NONE -1

#define MSM_AUXA_DEFAULT 0
#define MSM_AUXB_DEFAULT 1
#define MSM_AUX_NONE -1

#define MSM_ENTRY_SENO_MAX 32

typedef BOOL (*MSM_OPEN)(s32 entrynum, DVDFileInfo *fileInfo);
typedef BOOL (*MSM_READ)(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset, s32 prio);
typedef BOOL (*MSM_CLOSE)(DVDFileInfo *fileInfo);


typedef struct msmAram_s {
	BOOL skipARInit;
	union {
		struct {
			u32 aramEnd;
		};
		struct {
			u32 numEntries;
			u32 *stackIndex;
		};
	};
} MSM_ARAM;

typedef struct msmInit_s {
	char *msmPath;
	char *pdtPath;
	MSM_OPEN open;
	MSM_READ read;
	MSM_CLOSE close;
	void *heap;
	u32 heapSize;
} MSM_INIT;

typedef struct msmSeParam_s {
	s32 flag;
	s8 vol;
	s8 pan;
	s16 pitch;
	u8 span;
	s8 auxAVol;
	s8 auxBVol;
	s32 pad;
	Vec pos;
} MSM_SEPARAM;

typedef struct msmSe_s {
	u16 groupId;
	u16 fxId;
	s8 vol;
	s8 pan;
	s16 pitchBend;
	u8 span;
	u8 reverb;
	u8 chorus;
	u8 doppler;
	s8 comp;
	u8 pad[3];
} MSMSE;

typedef  struct msmSeListener_s {
	s32 flag;
	float startDis;
	float frontSurDis;
	float backSurDis;
} MSM_SELISTENER;

typedef struct msmMusParam_s {
	s32 flag;
	s8 chan;
	s8 vol;
	u16 fadeSpeed;
	u16 speed;
} MSM_MUSPARAM;

typedef struct msmStreamParam_s {
	s32 flag;
	s8 vol;
	s8 pan;
	s8 span;
	s8 auxA;
	s8 auxB;
	s8 chan;
	u16 fadeSpeed;
} MSM_STREAMPARAM;

s32 msmSysInit(MSM_INIT *init, MSM_ARAM *aram);
void msmSysSetOutputMode(SND_OUTPUTMODE mode);
s32 msmSysDelGroupAll(void);
s32 msmSysLoadGroup(s32 grp, void *buf, BOOL flag);
s32 msmSysGetSampSize(BOOL baseGrp);
s32 msmSysDelGroupBase(s32 grpNum);

s32 msmSeSetParam(int seNo, MSM_SEPARAM *param);
int msmSePlay(int seId, MSM_SEPARAM *param);
s32 msmSeStop(int seNo, s32 speed);
void msmSePauseAll(BOOL pause, s32 speed);
s32 msmSePause(int seNo, BOOL pause, s32 speed);
void msmSeStopAll(BOOL checkGrp, s32 speed);
s32 msmSeSetListener(Vec *pos, Vec *heading, float sndDist, float sndSpeed, MSM_SELISTENER *listener);
s32 msmSeUpdataListener(Vec *pos, Vec *heading);
void msmSeDelListener(void);
s32 msmSeGetStatus(int seNo);
s32 msmSeGetNumPlay(BOOL baseGrp);
s32 msmSeGetEntryID(s32 seId, int *seNo);

int msmMusPlay(int musId, MSM_MUSPARAM *musParam);
s32 msmMusStop(int musNo, s32 speed);
s32 msmMusPauseAll(BOOL pause, s32 speed);
s32 msmMusPause(int musNo, BOOL pause, s32 speed);
s32 msmMusGetMidiCtrl(int musNo, s32 channel, s32 ctrl);
void msmMusStopAll(BOOL checkGrp, s32 speed);
s32 msmMusGetStatus(int musNo);
s32 msmMusGetNumPlay(BOOL baseGrp);

int msmStreamPlay(int streamId, MSM_STREAMPARAM *streamParam);
s32 msmStreamStop(int streamNo, s32 speed);
s32 msmStreamPauseAll(BOOL pause, s32 speed);
s32 msmStreamPause(int streamNo, BOOL pause, s32 speed);

void msmStreamStopAll(s32 speed);
s32 msmStreamGetStatus(int streamNo);

#endif
