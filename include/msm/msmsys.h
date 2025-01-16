#ifndef MSMSYS_H
#define MSMSYS_H

#include "game/msm.h" // TODO remove, only for decomp

#include "dolphin.h"

#define MSM_AUX_REVERBHI 0
#define MSM_AUX_REVERBSTD 1
#define MSM_AUX_CHORUS 2
#define MSM_AUX_DELAY 3

#define MSM_AUXNO_NULL -2
#define MSM_AUXNO_UNSET -1

typedef union {
    SND_AUX_REVERBHI revHi;
    SND_AUX_REVERBSTD revStd;
    SND_AUX_CHORUS chorus;
    SND_AUX_DELAY delay;
} MSM_AUX; // Size 0x1E0

typedef struct MSMGrpWork_s {
    s8 grpId;
    s8 baseGrpF;
    u32 num;
    void *buf;
} MSM_GRP_STACK;

typedef struct MSMSys_s {
    s32 msmEntryNum;
    s8 outputMode;
    s8 unk5;
    s8 unk6;
    s8 arInitF;
    s32 aramP;
    MSM_HEADER *header;
    MSM_INFO *info;
    MSM_AUXPARAM *auxParam;
    s8 auxParamNo[2];
    MSM_AUX aux[2]; // 0: userA, 1: userB
    s8 grpMax;
    s32 grpNum;
    u32 sampSize;
    u32 sampSizeBase;
    MSM_GRP_INFO *grpInfo;
    MSM_GRP_SET *grpSet;
    s8 baseGrpNum;
    MSM_GRP_HEAD *grpData[15];
    s8 grpStackAMax;
    u8 grpStackADepth;
    s8 grpStackAOfs;
    void *grpBufA;
    MSM_GRP_STACK grpStackA[4];
    s8 grpStackBMax;
    u8 grpStackBDepth;
    s8 grpStackBOfs;
    void *grpBufB;
    MSM_GRP_STACK grpStackB[10];
    s32 irqDepth;
    BOOL irqState;
    AIDCallback oldAIDCallback;
    s32 timer;
} MSM_SYS;

s32 msmSysSearchGroupStack(s32 arg0, s32 arg1);
s32 msmSysGroupInit(DVDFileInfo *arg0);
void msmSysIrqDisable(void);
void msmSysIrqEnable(void);
BOOL msmSysCheckBaseGroup(s32 arg0);
void *msmSysGetGroupDataPtr(s32 arg0);
BOOL msmSysCheckLoadGroupID(s32 arg0);
void msmSysRegularProc(void);
s32 msmSysGetOutputMode(void);
BOOL msmSysSetOutputMode(SND_OUTPUTMODE mode);
s32 msmSysGetSampSize(BOOL baseGrp);
s32 msmSysDelGroupAll(void);
s32 msmSysDelGroupBase(s32 grpNum);
s32 msmSysLoadGroupBase(s32 arg0, void *arg1);
s32 msmSysLoadGroupSet(s32 arg0, void *arg1);
void msmSysCheckInit(void);
s32 msmSysInit(MSM_INIT *init, MSM_ARAM *aram);

#endif
