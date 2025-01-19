#ifndef _MSM_DATA_H
#define _MSM_DATA_H

#include "dolphin.h"
#include "musyx/musyx.h"

#define MSM_STREAM_FLAG_STEREO 0x1
#define MSM_STREAM_FLAG_LOOP 0x2

#define MSM_FILE_VERSION 2
#define MSM_PDT_FILE_VERSION 1

typedef struct MSMHeader_s {
    s32 magic;
    s32 version;
    s32 endOfs;
    s32 endSize;
    s32 infoOfs; 
    u32 infoSize;
    s32 auxParamOfs;
    u32 auxParamSize;
    s32 grpInfoOfs;
    s32 grpInfoSize;
    s32 musOfs;
    s32 musSize;
    s32 seOfs;
    s32 seSize;
    s32 grpDataOfs;
    s32 grpDataSize;
    s32 sampOfs;
    s32 sampSize;
    s32 dummyMusOfs;
    s32 dummyMusSize;
    s32 grpSetOfs;
    s32 grpSetSize;
    s32 pad[2];
} MSM_HEADER; // sizeof 0x60

typedef struct MSMInfo_s {
    s8 voices;
    s8 music;
    s8 sfx;
    s8 grpMax;
    s16 musMax;
    s16 seMax;
    s8 musChanMax;
    s8 stackDepthA;
    s8 stackDepthB;
    s8 surroundF;
    s8 unkC[2];
    s8 auxParamA;
    s8 auxParamB;
    s32 minMem;
    s32 aramSize;
    s32 grpBufSizeA;
    s32 grpBufSizeB;
    s32 dummyMusSize;
    s32 unk24;
    s8 baseGrpNum;
    s8 baseGrp[23];
} MSM_INFO;

typedef struct {
    u32 tempDisableFX;
    f32 coloration;
    f32 mix;
    f32 time;
    f32 damping;
    f32 preDelay;
    f32 crosstalk;
} MSM_AUXPARAM_REVERBHI;

typedef struct {
    u32 tempDisableFX;
    f32 coloration;
    f32 mix;
    f32 time;
    f32 damping;
    f32 preDelay;
    f32 crosstalk;
} MSM_AUXPARAM_REVERBSTD;

typedef struct {
    u32 baseDelay;
    u32 variation;
    u32 period;
} MSM_AUXPARAM_CHORUS;

typedef struct {
    u32 delay[3];
    u32 feedback[3];
    u32 output[3];
} MSM_AUXPARAM_DELAY;

typedef struct MSMAuxParam_s {
    s8 type;
	u8 pad[3];
    union {
        MSM_AUXPARAM_REVERBHI revHi;
        MSM_AUXPARAM_REVERBSTD revStd;
        MSM_AUXPARAM_CHORUS chorus;
        MSM_AUXPARAM_DELAY delay;
    };
} MSM_AUXPARAM;

typedef struct MSMSe_s {
	SND_GROUPID gid;
	SND_FXID fxId;
	s8 vol;
	s8 pan;
	s16 pitchBend;
	u8 span;
	u8 reverb;
	u8 chorus;
	s8 emitterF;
	s8 emiComp;
	u8 pad[3];
} MSM_SE;

typedef struct MSMMus_s {
    SND_GROUPID sgid;
	SND_SONGID sid;
	s32 songOfs;
	s32 songSize;
	s8 songGrp;
	s8 vol;
	u8 pad[2];
} MSM_MUS; // Size 0x10

typedef struct MSMGrpHead_s {
    s32 poolOfs;
    s32 projOfs;
    s32 sdirOfs;
    s32 sngOfs;
} MSM_GRP_HEAD;

typedef struct MSMGrpInfo_s {
    SND_GROUPID gid;
    s8 stackNo;
    s8 subGrpId;
    s32 dataOfs;
    s32 dataSize;
    s32 sampOfs;
    s32 sampSize;
    u8 pad[12];
} MSM_GRP_INFO;

typedef struct MSMGrpSet_s {
    s8 numGrpSet;
    s8 grpSetW;
    s8 data[1];
} MSM_GRP_SET;

typedef struct MSMStreamHeader_s {
	s16 version;
	s16 streamMax;
	s32 chanMax;
	s32 sampleFrq;
	s32 maxBufs;
	u32 streamPackListOfs;
	u32 adpcmParamOfs;
	u32 streamPackOfs;
	u32 sampleOfs;
} MSM_STREAM_HEADER;

typedef struct MSMStream_s {
    s32 sampleOfs;
    s16 adpcmParamIdx;
    u16 pad;
} MSM_STREAM; 

typedef struct MSMStreamPack_s {
    s8 flag;
    s8 vol;
    s8 pan;
    s8 span;
    s8 auxA;
    s8 auxB;
    u16 frq;
    u32 loopOfsEnd;
    u32 loopOfsStart;
    MSM_STREAM stream[2];
} MSM_STREAM_PACK; // Size unknown

#endif
