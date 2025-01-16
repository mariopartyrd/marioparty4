#include "msm/msmstream.h"
#include "msm/msmmem.h"
#include "msm/msmsys.h"

typedef struct {
    /* 0x00 */ SND_STREAMID stid;
    /* 0x04 */ s16 streamId;
    /* 0x06 */ u8 status;
    /* 0x07 */ u8 stereoF;
    /* 0x08 */ u8 volBase;
    /* 0x09 */ u8 vol;
    /* 0x0A */ u8 volFade;
    /* 0x0B */ u8 pauseVol;
    /* 0x0C */ u8 panBase;
    /* 0x0D */ u8 pan;
    /* 0x0E */ s8 slotL;
    /* 0x0F */ s8 slotR;
    /* 0x10 */ u32 pauseLen;
    /* 0x14 */ volatile s32 pauseTime;
    /* 0x18 */ volatile s32 pauseTimeMax;
    /* 0x1C */ s32 fadeVol;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ volatile s32 fadeMaxTime;
    /* 0x28 */ s32 fadeTime;
    /* 0x2C */ s8 span;
    /* 0x2D */ s8 auxA;
    /* 0x2E */ s8 auxB;
    /* 0x30 */ void* streamBuf;
    /* 0x34 */ u32 streamBufSize;
    /* 0x38 */ u32 streamFrq;
    /* 0x3C */ struct {
        volatile u8 bufNo : 1;
        volatile u8 firstF : 1;
        u8 streamOffF : 1;
        u8 readBusyF : 1;
        volatile u8 shutdownF : 1;
        volatile u8 pauseF : 1;
        volatile u8 updateAramF : 1;
    };
    s32 frq;
    /* 0x44 */ SND_ADPCMSTREAM_INFO* adpcmInfo;
    /* 0x48 */ s32 streamBaseOfs;
    /* 0x4C */ u32 streamPos;
    /* 0x50 */ u32 loopLen;
    /* 0X54 */ s32 loopEndOfs;
    /* 0x58 */ u32 streamReadSize;
    /* 0x5C */ void* streamReadBuf;
    /* 0X60 */ s32 streamPosStart;
    /* 0x64 */ u32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ DVDFileInfo file;
} MSM_STREAM_SLOT; // Size 0xAC

static struct {
    /* 0x00 */ s32 sampleFrq;
    /* 0x04 */ u32 bufSize;
    /* 0x08 */ s32 frq;
    /* 0x0C */ s32 pdtEntryNum;
    /* 0x10 */ s8 time;
    /* 0x11 */ u8 masterVol;
    /* 0x12 */ u8 outputMode;
    /* 0x14 */ u32* streamPackList;
    /* 0x18 */ s8* streamPackFlag;
    /* 0x1C */ SND_ADPCMSTREAM_INFO* adpcmParam;
    /* 0x20 */ MSM_STREAM_SLOT* slot;
    MSM_STREAM_HEADER header ATTRIBUTE_ALIGN(32);
} StreamInfo; // Size 0x60

typedef struct {
    /* 0x00 */ u8 vol;
    /* 0x01 */ u8 pan;
    /* 0x02 */ u8 span;
    /* 0x03 */ u8 auxA;
    /* 0x04 */ u8 auxB;
    /* 0x08 */ s32 sampleOfs;
} STREAM_PARAM;

static void msmStreamPauseFade(s32 streamNo);
static void msmStreamFade(s32 streamNo);
static void msmStreamDvdCallback(s32 result, DVDFileInfo* fileInfo);
static void msmStreamStopSub(s32 streamNo, s32 speed);
static void msmStreamDvdCallback2(s32 result, DVDFileInfo* fileInfo);
static u32 msmStreamUpdateFunc(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user);
static s32 msmStreamSlotInit(MSM_STREAM_SLOT* arg0, MSM_STREAM_PACK* arg1, STREAM_PARAM* arg2, s32 arg3);
static void msmStreamPauseOff(s32 streamNo);
static void msmStreamPauseOn(s32 streamNo, s32 arg1);
static s32 msmStreamPackStartStereo(s32 streamId, MSM_STREAMPARAM *param, s32 sampleOfs);
static s32 msmStreamPackStartMono(s32 streamId, MSM_STREAMPARAM *param, s32 sampleOfs);
static void msmStreamSlotOff(s32 streamNo);

static inline void msmStreamClose(s32 streamNo) {
    MSM_STREAM_SLOT* slot;

    slot = &StreamInfo.slot[streamNo];
    DVDClose(&slot->file);
    slot->status = 0;
}

s32 msmStreamGetStatus(int streamNo) {
    MSM_STREAM_SLOT* slot;
    s32 status;

    if (streamNo < 0 || streamNo >= StreamInfo.header.chanMax) {
        return 0;
    }
    slot = &StreamInfo.slot[streamNo];
    switch (slot->status) {
        case 4:
            status = MSM_STREAM_PLAY;
            break;
        case 2:
        case 3:
            status = MSM_STREAM_PAUSEOUT;
            break;
        case 5:
            status = MSM_STREAM_STOP;
            break;
        default:
            status = MSM_STREAM_DONE;
            break;
    }
    if (slot->pauseF == TRUE) {
        status = MSM_STREAM_PAUSEIN;
    }
    if (status == MSM_STREAM_DONE && slot->slotL != -1) {
        status = msmStreamGetStatus(slot->slotL);
    }
    return status;
}

static void msmStreamUpdateBaseParam(MSM_STREAM_SLOT* slot) {
    s32 pan;
    s32 vol;

    if (StreamInfo.outputMode != 0) {
        pan = slot->panBase + slot->pan - 64;
        if (pan < 0) {
            pan = 0;
        }
        if (pan > 127) {
            pan = 127;
        }
    } else {
        pan = 64;
    }
    vol = slot->volBase * slot->vol * slot->volFade * slot->pauseVol / (127*127*127);
    sndStreamMixParameterEx(slot->stid, vol * StreamInfo.masterVol / 127, pan, slot->span, slot->auxA, slot->auxB);
}

void msmStreamSetMasterVolume(s32 vol) {
    s32 i;

    StreamInfo.masterVol = vol & 127;
    for (i = 0; i < StreamInfo.header.chanMax; i++) {
        if (StreamInfo.slot[i].status != 0) {
            msmStreamUpdateBaseParam(&StreamInfo.slot[i]);
        }
    }
}

static inline BOOL msmStreamIsPlay(MSM_STREAM_SLOT* slot) {
    if (slot->status != 0 || slot->pauseF != 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void msmStreamStopAll(s32 speed)
{
    MSM_STREAM_SLOT* slot;
    s32 i;

    msmSysIrqDisable();
    for (i = 0; i < StreamInfo.header.chanMax; i++) {
        if (i >= 0 && i < StreamInfo.header.chanMax) {
            slot = &StreamInfo.slot[i];
            if (msmStreamIsPlay(slot)) {
                msmSysIrqDisable();
                msmStreamStopSub(i, speed);
                if (slot->slotL != -1) {
                    msmStreamStopSub(slot->slotL, speed);
                }
                if (slot->slotR != -1) {
                    msmStreamStopSub(slot->slotR, speed);
                }
                msmSysIrqEnable();
            }
        }
    }
    msmSysIrqEnable();
}

static inline void msmStreamSetFade(int streamNo, s32 speed) {
    MSM_STREAM_SLOT* slot = &StreamInfo.slot[streamNo];

    if (slot->pauseF != 0) {
        slot->pauseF = 0;
        speed = 0;
    }
    slot->fadeMaxTime = speed / 15;
    if (slot->fadeMaxTime != 0) {
        slot->fadeTime = slot->fadeMaxTime;
        slot->volFade = 127;
    } else {
        msmStreamSlotOff(streamNo);
    }
}

s32 msmStreamStop(int streamNo, s32 speed) {
    MSM_STREAM_SLOT* slot;
    s32 unused;

    if (streamNo < 0 || streamNo >= StreamInfo.header.chanMax) {
        return MSM_ERR_RANGE_STREAM;
    }
    slot = &StreamInfo.slot[streamNo];
    if (msmStreamIsPlay(slot)) {
        msmSysIrqDisable();
        msmStreamSetFade(streamNo, speed);
        if (slot->slotL != -1) {
            msmStreamSetFade(slot->slotL, speed);
        }
        if (slot->slotR != -1) {
            msmStreamSetFade(slot->slotR, speed);
        }
        msmSysIrqEnable();
    }
    return 0;
}

int msmStreamPlay(int streamId, MSM_STREAMPARAM* streamParam) {
    if (streamId < 0 || streamId >= StreamInfo.header.streamMax) {
        return MSM_ERR_INVALIDID;
    }
    if (StreamInfo.streamPackList[streamId] == 0) {
        return MSM_ERR_REMOVEDID;
    }
    if (StreamInfo.streamPackFlag[StreamInfo.streamPackList[streamId] - StreamInfo.header.streamPackOfs] & MSM_STREAM_FLAG_STEREO) {
        return msmStreamPackStartStereo(streamId, streamParam, 0);
    } else {
        return msmStreamPackStartMono(streamId, streamParam, 0);
    }
}

void msmStreamPeriodicProc(void) {
    MSM_STREAM_SLOT* slot;
    s32 i;

    StreamInfo.time = 0;
    for (i = 0; i < StreamInfo.header.chanMax; i++) {
        slot = &StreamInfo.slot[i];
        msmStreamFade(i);
        msmStreamPauseOff(i);
        msmStreamPauseFade(i);
        if (slot->status != 0) {
            StreamInfo.time++;
        }
    }
}

void msmStreamSetOutputMode(s32 outputMode) {
    s32 i;

    StreamInfo.outputMode = outputMode;
    for (i = 0; i < StreamInfo.header.chanMax; i++) {
        if (StreamInfo.slot[i].status != 0) {
            msmStreamUpdateBaseParam(&StreamInfo.slot[i]);
        }
    }
}

void msmStreamAmemFree(void) {
    u32 i;

    for (i = 0; i < StreamInfo.header.chanMax; i++) {
        sndStreamFree(StreamInfo.slot[i].stid);
    }
}

s32 msmStreamAmemAlloc(void) {
    u32 i;
    MSM_STREAM_SLOT* slot;

    for (i = 0; i < StreamInfo.header.chanMax; i++) {
        slot = &StreamInfo.slot[i];
        slot->status = 0;
        slot->slotR = -1;
        slot->slotL = -1;
        slot->streamBuf = msmMemAlloc(StreamInfo.bufSize);
        if (slot->streamBuf == NULL) {
            return MSM_ERR_OUTOFMEM;
        }
        slot->streamBufSize = StreamInfo.bufSize;
        slot->streamFrq = StreamInfo.frq;
        slot->stid = sndStreamAllocEx(0xFF, slot->streamBuf, slot->streamFrq, StreamInfo.header.sampleFrq, 0, 64, 0, 0, 0, 0, 0x30001, msmStreamUpdateFunc, i, NULL);
        if (slot->stid == -1) {
            return MSM_ERR_STREAMALLOC_FAIL;
        }
    }
    return StreamInfo.bufSize * StreamInfo.header.chanMax;
}

s32 msmStreamInit(char *pdtPath) {
    DVDFileInfo file;
    s32 size;

    StreamInfo.header.streamMax = 0;
    StreamInfo.header.chanMax = 0;
    StreamInfo.masterVol = 127;
    StreamInfo.time = 0;
    if (pdtPath == NULL) {
        return 0;
    }
    StreamInfo.pdtEntryNum = DVDConvertPathToEntrynum(pdtPath);
    if (StreamInfo.pdtEntryNum == -1) {
        return MSM_ERR_OPENFAIL;
    }
    if (!msmFioOpen(StreamInfo.pdtEntryNum, &file)) {
        return MSM_ERR_OPENFAIL;
    }
    if (msmFioRead(&file, &StreamInfo.header, 0x20, 0) < 0) {
        msmFioClose(&file);
        return MSM_ERR_READFAIL;
    }
    if (StreamInfo.header.version != MSM_PDT_FILE_VERSION) {
        msmFioClose(&file);
        return MSM_ERR_INVALIDFILE;
    }
    if (StreamInfo.header.streamMax != 0) {
        size = (StreamInfo.header.adpcmParamOfs - StreamInfo.header.streamPackListOfs + 0x1F) & ~0x1F;
        StreamInfo.streamPackList = msmMemAlloc(size);
        if (StreamInfo.streamPackList == NULL) {
            msmFioClose(&file);
            return MSM_ERR_OUTOFMEM;
        }
        if (msmFioRead(&file, StreamInfo.streamPackList, size, StreamInfo.header.streamPackListOfs) < 0) {
            msmFioClose(&file);
            return MSM_ERR_READFAIL;
        }
        size = (StreamInfo.header.sampleOfs - StreamInfo.header.streamPackOfs + 0x1F) & ~0x1F;
        StreamInfo.streamPackFlag = msmMemAlloc(size);
        if (StreamInfo.streamPackFlag == NULL) {
            msmFioClose(&file);
            return MSM_ERR_OUTOFMEM;
        }
        if (msmFioRead(&file, StreamInfo.streamPackFlag, size, StreamInfo.header.streamPackOfs) < 0) {
            msmFioClose(&file);
            return MSM_ERR_READFAIL;
        }
        size = StreamInfo.header.streamPackOfs - StreamInfo.header.adpcmParamOfs;
        StreamInfo.adpcmParam = msmMemAlloc(size);
        if (StreamInfo.adpcmParam == NULL) {
            msmFioClose(&file);
            return MSM_ERR_OUTOFMEM;
        }
        if (msmFioRead(&file, StreamInfo.adpcmParam, size, StreamInfo.header.adpcmParamOfs) < 0) {
            msmFioClose(&file);
            return MSM_ERR_READFAIL;
        }
    }
    msmFioClose(&file);
    StreamInfo.sampleFrq = (StreamInfo.header.sampleFrq + (SND_STREAM_ADPCM_BLKSIZE-1)) / SND_STREAM_ADPCM_BLKSIZE ;
    StreamInfo.bufSize = (8 * StreamInfo.sampleFrq * StreamInfo.header.maxBufs + 0x3F) & ~0x3F;
    StreamInfo.frq = (StreamInfo.bufSize / SND_STREAM_ADPCM_BLKBYTES ) * SND_STREAM_ADPCM_BLKSIZE;
    StreamInfo.slot = msmMemAlloc(StreamInfo.header.chanMax * sizeof(*StreamInfo.slot));
    memset(StreamInfo.slot, 0, StreamInfo.header.chanMax * sizeof(*StreamInfo.slot));
    return 0;
}

static void msmStreamPauseOff(s32 streamNo) {
    MSM_STREAM_SLOT* slot;
    u32 ofs;
    u32 readSize;

    slot = &StreamInfo.slot[streamNo];
    if (slot->pauseTime == 0) {
        return;
    }
    if (slot->pauseF == 0) {
        slot->pauseTime = 0;
        return;
    }
    if (slot->pauseTimeMax != 0) {
        slot->pauseTimeMax = -(slot->pauseTime + 1);
        if (slot->pauseTimeMax == 0) {
            slot->pauseVol = 127;
            msmStreamUpdateBaseParam(slot);
        }
        slot->pauseTime = 0;
        slot->pauseF = 0;
    } else if (slot->status == 0 && DVDFastOpen(StreamInfo.pdtEntryNum, &slot->file) == TRUE) {
        if (--slot->pauseTime != 0) {
            slot->pauseTimeMax = -slot->pauseTime;
            slot->fadeVol = 0;
            slot->pauseVol = 0;
        } else {
            slot->pauseVol = 127;
        }
        slot->pauseTime = 0;
        slot->firstF = TRUE;
        slot->streamOffF = 0;
        slot->shutdownF = 0;
        slot->pauseF = 0;
        slot->updateAramF = 0;
        slot->bufNo = 1;
        slot->unk64 = slot->unk68 = (slot->pauseLen / SND_STREAM_ADPCM_BLKBYTES) * SND_STREAM_ADPCM_BLKSIZE;
        slot->unk6C = 0;
        slot->streamPos = slot->pauseLen;
        readSize = slot->streamBufSize / 2;
        if ((ofs = slot->loopLen - slot->streamPos) < slot->streamBufSize / 2) {
            readSize = ofs;
            slot->streamReadSize = slot->streamBufSize / 2 - ofs;
            slot->streamReadBuf = (void*) ((u32) slot->streamBuf + ofs);
            memset(slot->streamReadBuf, 0, slot->streamReadSize);
        }
        slot->status = 2;
        slot->streamPos += readSize;
        slot->readBusyF = TRUE;
        DVDReadAsync(&slot->file, slot->streamBuf, readSize, slot->streamBaseOfs + (slot->streamPos - readSize), msmStreamDvdCallback);
    }
}

static inline void msmStreamOff(s32 streamNo) {
    MSM_STREAM_SLOT* slot;

    slot = &StreamInfo.slot[streamNo];
    switch (slot->status) {
        case 2:
            slot->shutdownF = TRUE;
            slot->status = 5;
            break;
        case 3:
            msmStreamClose(streamNo);
            break;
        case 4:
            if (slot->streamOffF == FALSE) {
                sndStreamMixParameterEx(slot->stid, 0, 64, 0, 0, 0);
                slot->streamOffF = TRUE;
                slot->status = 5;
            }
            break;
    }
}

static void msmStreamPauseOn(s32 streamNo, s32 speed) {
    MSM_STREAM_SLOT* slot;

    slot = &StreamInfo.slot[streamNo];
    slot->pauseTime = 0;
    if (slot->pauseF != 0) {
        return;
    }
    slot->pauseF = TRUE;
    slot->pauseTimeMax = speed / 15;
    if (slot->pauseTimeMax != 0) {
        slot->fadeVol = slot->pauseTimeMax;
        slot->pauseVol = 127;
        return;
    }
    slot->pauseLen = ((slot->unk64 / 7) * 4) & ~7;
    if (slot->stereoF != 0) {
        if (slot->pauseLen >= slot->loopLen - slot->streamBufSize / 4) {
            slot->pauseLen = 0;
        }
    } else if (slot->pauseLen >= slot->loopLen) {
        slot->pauseF = 0;
    }
    msmStreamOff(streamNo);
}

static void msmStreamPauseFade(s32 streamNo) {
    MSM_STREAM_SLOT* slot;

    slot = &StreamInfo.slot[streamNo];
    if (slot->status != 4) {
        return;
    }
    if (slot->pauseTimeMax > 0) {
        if (--slot->fadeVol == 0) {
            slot->pauseTimeMax = 0;
            slot->pauseF = 0;
            msmStreamPauseOn(streamNo, 0);
        } else {
            slot->pauseVol = slot->fadeVol * 127 / slot->pauseTimeMax;
            msmStreamUpdateBaseParam(slot);
        }
    } else if (slot->pauseTimeMax < 0) {
        if (++slot->fadeVol >= -slot->pauseTimeMax) {
            slot->pauseTimeMax = 0;
            slot->pauseVol = 127;
            msmStreamUpdateBaseParam(slot);
        } else {
            slot->pauseVol = slot->fadeVol * 127 / -slot->pauseTimeMax;
            msmStreamUpdateBaseParam(slot);
        }
    }
}

static void msmStreamFade(s32 streamNo) {
    MSM_STREAM_SLOT* slot;

    slot = &StreamInfo.slot[streamNo];
    if (slot->status != 4) {
        return;
    }
    if (slot->fadeMaxTime > 0) {
        if (--slot->fadeTime == 0) {
            slot->fadeMaxTime = 0;
            msmStreamSetFade(streamNo, 0);
        } else {
            slot->volFade = slot->fadeTime * 127 / slot->fadeMaxTime;
            msmStreamUpdateBaseParam(slot);
        }
    } else if (slot->fadeMaxTime < 0) {
        if (++slot->fadeTime >= -slot->fadeMaxTime) {
            slot->fadeMaxTime = 0;
            slot->volFade = 127;
            msmStreamUpdateBaseParam(slot);
        } else {
            slot->volFade = slot->fadeTime * 127 / -slot->fadeMaxTime;
            msmStreamUpdateBaseParam(slot);
        }
    }
}

static void msmStreamStopSub(s32 streamNo, s32 speed) {
    MSM_STREAM_SLOT* slot;
    s32 time;

    time = speed;
    slot = &StreamInfo.slot[streamNo];
    if (slot->pauseF != 0) {
        slot->pauseF = 0;
        time = 0;
    }
    slot->fadeMaxTime = time / 15;
    if (slot->fadeMaxTime != 0) {
        slot->fadeTime = slot->fadeMaxTime;
        slot->volFade = 127;
        return;
    }
    msmStreamOff(streamNo);
}

static void msmStreamSetParamSub(MSM_STREAM_SLOT* slot) {
    int pan;
    s32 vol;

    if (StreamInfo.outputMode != 0) {
        pan = slot->panBase + slot->pan - 64;
        if (pan < 0) {
            pan = 0;
        }
        if (pan > 127) {
            pan = 127;
        }
    } else {
        pan = 64;
    }
    vol = slot->volBase * slot->vol * slot->volFade * slot->pauseVol / (127*127*127);
    sndStreamMixParameterEx(slot->stid, vol * StreamInfo.masterVol / 127, pan, slot->span, slot->auxA, slot->auxB);
}

static s32 msmStreamPackStartStereo(s32 streamId, MSM_STREAMPARAM *param, s32 sampleOfs) {
    s32 flag;
    s32 chanL;
    s32 chanR;
    u32 sizeL;
    u32 sizeR;
    STREAM_PARAM streamParam;
    MSM_STREAM_SLOT* slotL;
    MSM_STREAM_SLOT* slotR;
    MSM_STREAM_PACK* pack;

    flag = (param != NULL) ? param->flag : 0;
    if (flag & MSM_STREAMPARAM_CHAN) {
        chanL = param->chan;
        chanR = param->chan + 1;
        if (chanL < 0 || chanL >= StreamInfo.header.chanMax) {
            return MSM_ERR_CHANLIMIT;
        }
        if (chanR < 0 || chanR >= StreamInfo.header.chanMax) {
            return MSM_ERR_CHANLIMIT;
        }
        if (msmStreamIsPlay(&StreamInfo.slot[chanL])) {
            return MSM_ERR_CHANLIMIT;
        }
        if (msmStreamIsPlay(&StreamInfo.slot[chanR])) {
            return MSM_ERR_CHANLIMIT;
        }
    } else {
        for (chanL = 0; chanL < StreamInfo.header.chanMax; chanL++) {
            if (!msmStreamIsPlay(&StreamInfo.slot[chanL])) {
                break;
            }
        }
        for (chanR = chanL + 1; chanR < StreamInfo.header.chanMax; chanR++) {
            if (!msmStreamIsPlay(&StreamInfo.slot[chanR])) {
                break;
            }
        }
        if (chanL == StreamInfo.header.chanMax || chanR == StreamInfo.header.chanMax) {
            return MSM_ERR_CHANLIMIT;
        }
    }
    slotL = &StreamInfo.slot[chanL];
    slotR = &StreamInfo.slot[chanR];
    pack = (MSM_STREAM_PACK*) ((u32) StreamInfo.streamPackFlag + (StreamInfo.streamPackList[streamId] - StreamInfo.header.streamPackOfs));
    streamParam.vol = (flag & MSM_STREAMPARAM_VOL) ? param->vol : 127;
    streamParam.span = (flag & MSM_STREAMPARAM_SPAN) ? param->span : (s32) pack->span;
    streamParam.auxA = (flag & MSM_STREAMPARAM_AUXA) ? param->auxA : (s32) pack->auxA;
    streamParam.auxB = (flag & MSM_STREAMPARAM_AUXB) ? param->auxB : (s32) pack->auxB;
    streamParam.sampleOfs = sampleOfs;
    msmSysIrqDisable();
    streamParam.pan = 0;
    sizeL = msmStreamSlotInit(slotL, pack, &streamParam, 0);
    streamParam.pan = 127;
    sizeR = msmStreamSlotInit(slotR, pack, &streamParam, 1);
    slotL->streamId = streamId;
    slotR->streamId = -1;
    slotL->slotL = chanR;
    slotR->slotR = chanL;
    if ((flag & MSM_STREAMPARAM_FADESPEED) && param->fadeSpeed != 0) {
        slotL->fadeMaxTime = slotR->fadeMaxTime = -param->fadeSpeed / 15;
        slotL->fadeTime = slotR->fadeTime = 0;
        slotL->volFade = slotR->volFade = 0;
    }
    msmSysIrqEnable();
    if (sizeL == 0) {
        return 0;
    }
    if (flag & MSM_STREAMPARAM_PAUSE) {
        slotL->pauseF = slotR->pauseF = 1;
        slotL->status = slotR->status = 0;
        return chanL;
    }
    if (DVDFastOpen(StreamInfo.pdtEntryNum, &slotL->file) != 1) {
        return MSM_ERR_OPENFAIL;
    }
    if (DVDFastOpen(StreamInfo.pdtEntryNum, &slotR->file) != 1) {
        DVDClose(&slotL->file);
        return MSM_ERR_OPENFAIL;
    }
    slotL->streamPos += sizeL;
    slotR->streamPos += sizeR;
    slotL->readBusyF = 1;
    DVDReadAsync(&slotL->file, slotL->streamBuf, sizeL, slotL->streamBaseOfs + (slotL->streamPos - sizeL), msmStreamDvdCallback);
    slotR->readBusyF = 1;
    DVDReadAsync(&slotR->file, slotR->streamBuf, sizeR, slotR->streamBaseOfs + (slotR->streamPos - sizeR), msmStreamDvdCallback);
    return chanL;
}

static s32 msmStreamPackStartMono(s32 streamId, MSM_STREAMPARAM *param, s32 sampleOfs) {
    s32 flag;
    s32 chan;
    u32 size;
    STREAM_PARAM streamParam;
    MSM_STREAM_SLOT* slot;
    MSM_STREAM_PACK* pack;

    flag = (param != NULL) ? param->flag : 0;
    if (flag & MSM_STREAMPARAM_CHAN) {
        chan = param->chan;
        if (chan < 0 || chan >= StreamInfo.header.chanMax) {
            return MSM_ERR_CHANLIMIT;
        }
        if (msmStreamIsPlay(&StreamInfo.slot[chan])) {
            return MSM_ERR_CHANLIMIT;
        }
    } else {
        for (chan = 0; chan < StreamInfo.header.chanMax; chan++) {
            if (!msmStreamIsPlay(&StreamInfo.slot[chan])) {
                break;
            }
        }
        if (chan == StreamInfo.header.chanMax) {
            return MSM_ERR_CHANLIMIT;
        }
    }
    slot = &StreamInfo.slot[chan];
    pack = (MSM_STREAM_PACK*) ((u32) StreamInfo.streamPackFlag + (StreamInfo.streamPackList[streamId] - StreamInfo.header.streamPackOfs));
    streamParam.vol = (flag & MSM_STREAMPARAM_VOL) ? param->vol : 127;
    streamParam.pan = (flag & MSM_STREAMPARAM_PAN) ? param->pan : 64;
    streamParam.span = (flag & MSM_STREAMPARAM_SPAN) ? param->span : (s32) pack->span;
    streamParam.auxA = (flag & MSM_STREAMPARAM_AUXA) ? param->auxA : (s32) pack->auxA;
    streamParam.auxB = (flag & MSM_STREAMPARAM_AUXB) ? param->auxB : (s32) pack->auxB;
    streamParam.sampleOfs = sampleOfs;
    msmSysIrqDisable();
    size = msmStreamSlotInit(slot, pack, &streamParam, 0);
    slot->streamId = streamId;
    if ((flag & MSM_STREAMPARAM_FADESPEED) && param->fadeSpeed != 0) {
        slot->fadeMaxTime = -param->fadeSpeed / 15;
        slot->fadeTime = 0;
        slot->volFade = 0;
    }
    msmSysIrqEnable();
    if (size == 0) {
        return 0;
    }
    if (flag & MSM_STREAMPARAM_PAUSE) {
        slot->pauseF = TRUE;
        slot->status = 0;
        return chan;
    }
    if (DVDFastOpen(StreamInfo.pdtEntryNum, &slot->file) != 1) {
        return MSM_ERR_OPENFAIL;
    }
    slot->streamPos += size;
    slot->readBusyF = TRUE;
    DVDReadAsync(&slot->file, slot->streamBuf, size, slot->streamBaseOfs + (slot->streamPos - size), msmStreamDvdCallback);
    return chan;
}

// Note: identical to msmStreamOff.
static void msmStreamSlotOff(s32 streamNo) {
    MSM_STREAM_SLOT* slot;

    slot = &StreamInfo.slot[streamNo];
    switch (slot->status) {
        case 2:
            slot->shutdownF = 1;
            slot->status = 5;
            break;
        case 3:
            msmStreamClose(streamNo);
            break;
        case 4:
            if (slot->streamOffF == 0) {
                sndStreamMixParameterEx(slot->stid, 0, 64, 0, 0, 0);
                slot->streamOffF = TRUE;
                slot->status = 5;
            }
            break;
    }
}

static void msmStreamShutdown(s32 streamNo) {
    MSM_STREAM_SLOT* slot;

    slot = &StreamInfo.slot[streamNo];
    msmStreamSlotOff(streamNo);
    sndStreamDeactivate(slot->stid);
    if (slot->readBusyF == 0) {
        msmStreamClose(streamNo);
    } else {
        slot->shutdownF = 1;
    }
}

static void msmStreamData(s32 streamNo) {
    s32 dataSize;
    u32 readSize;
    void* dataPtr;
    MSM_STREAM_SLOT* slot;
    s32 off1;

    slot = &StreamInfo.slot[streamNo];
    readSize = dataSize = slot->streamBufSize / 2;
    dataPtr = (slot->bufNo != 0)
        ? (void*) ((u32) slot->streamBuf + dataSize)
        :  slot->streamBuf;
    slot->streamReadSize = off1 = 0;
    if (slot->streamPos + readSize > slot->loopLen) {
        if (slot->loopLen > slot->streamPos) {
            readSize = slot->loopLen - slot->streamPos;
            slot->streamReadSize = dataSize - readSize;
            slot->streamReadBuf = (void*) ((u32) dataPtr + readSize);
        } else if (slot->stereoF != 0) {
            slot->streamPos = slot->streamPosStart;
        } else {
            memset(dataPtr, 0, dataSize);
            if (slot->bufNo != 0) {
                off1 = slot->streamFrq / 2;
            }
            sndStreamARAMUpdate(slot->stid, off1, slot->streamFrq / 2, 0, 0);
            readSize = 0;
        }
    }
    if (readSize != 0) {
        if (DVDGetCommandBlockStatus(&slot->file.cb) != 0) {
            if (slot->updateAramF != TRUE) {
                slot->updateAramF = TRUE;
                sndStreamMixParameterEx(slot->stid, 0, 64, 64, 0, 0);
                memset(slot->streamBuf, 0, slot->streamBufSize);
                sndStreamARAMUpdate(slot->stid, 0, slot->streamFrq, 0, 0);
            }
        } else {
            if (slot->updateAramF == TRUE) {
                slot->updateAramF = FALSE;
                msmStreamUpdateBaseParam(slot);
            }
            slot->streamPos += readSize;
            slot->readBusyF = 1;
            DVDReadAsync(&slot->file, dataPtr, readSize, slot->streamBaseOfs + (slot->streamPos - readSize), msmStreamDvdCallback);
        }
    } else if (slot->firstF != 0) {
        slot->firstF= 0;
    } else {
        msmStreamShutdown(streamNo);
    }
    slot->bufNo ^= 1;
}

static BOOL msmStreamActivateStream(s32 streamNo) {
    MSM_STREAM_SLOT* slot;

    slot = &StreamInfo.slot[streamNo];
    msmStreamSetParamSub(slot);
    sndStreamFrq(slot->stid, slot->frq);
    sndStreamADPCMParameter(slot->stid, slot->adpcmInfo);
    sndStreamARAMUpdate(slot->stid, 0, slot->streamFrq / 2, 0, 0);
    if (sndStreamActivate(slot->stid)) {
        slot->status = 4;
        msmStreamData(streamNo);
        return TRUE;
    } else {
        msmStreamClose(streamNo);
        return FALSE;
    }
}

static void msmStreamDvdCallback(s32 result, DVDFileInfo* fileInfo) {
    s32 readSize;
    MSM_STREAM_SLOT* slot;

    for (readSize = 0; readSize < StreamInfo.header.chanMax; readSize++) {
        if (&StreamInfo.slot[readSize].file == fileInfo) {
            break;
        }
    }
    if (readSize == StreamInfo.header.chanMax) {
        return;
    }
    slot = &StreamInfo.slot[readSize];
    slot->readBusyF = 0;
    if (slot->shutdownF != 0) {
        slot->shutdownF = 0;
        msmStreamClose(readSize);
        return;
    }
    if (DVDGetCommandBlockStatus(&fileInfo->cb) == 0) {
        switch (slot->status) {
            case 2:
                if (slot->slotL != -1) {
                    if (StreamInfo.slot[slot->slotL].status != 3) {
                        slot->status = 3;
                        break;
                    }
                    if (!msmStreamActivateStream(slot->slotL)) {
                        slot->slotL = -1;
                    }
                }
                if (slot->slotR != -1) {
                    if (StreamInfo.slot[slot->slotR].status != 3) {
                        slot->status = 3;
                        break;
                    }
                    if (!msmStreamActivateStream(slot->slotR)) {
                        slot->slotR = -1;
                    }
                }
                if (!msmStreamActivateStream(readSize)) {
                    if (slot->slotL != -1) {
                        StreamInfo.slot[slot->slotL].slotR = -1;
                    }
                    if (slot->slotR != -1) {
                        StreamInfo.slot[slot->slotR].slotL = -1;
                    }
                }
                break;
            case 4:
                if (slot->streamPos >= slot->loopLen) {
                    if (slot->stereoF != 0) {
                        slot->streamPos = slot->streamPosStart;
                        if (slot->streamReadSize != 0) {
                            slot->readBusyF = 1;
                            DVDReadAsync(fileInfo, slot->streamReadBuf, slot->streamReadSize, slot->streamBaseOfs + slot->streamPos, msmStreamDvdCallback2);
                            slot->streamPos += slot->streamReadSize;
                            break;
                        }
                    } else if (slot->streamReadSize != 0) {
                        memset(slot->streamReadBuf, 0, slot->streamReadSize);
                    }
                }
                sndStreamARAMUpdate(slot->stid, (slot->bufNo != 0) ? 0 : slot->streamFrq / 2, slot->streamFrq / 2, 0, 0);
                break;
            case 5:
                slot->shutdownF = 0;
                msmStreamClose(readSize);
                break;
        }
    } else {
        if (slot->status == 4) {
            sndStreamDeactivate(slot->stid);
        }
        msmStreamClose(readSize);
        if (slot->slotL != -1) {
            StreamInfo.slot[slot->slotL].slotR = -1;
        }
        if (slot->slotR != -1) {
            StreamInfo.slot[slot->slotR].slotL = -1;
        }
    }
}

static void msmStreamDvdCallback2(s32 result, DVDFileInfo* fileInfo) {
    MSM_STREAM_SLOT* slot;
    s32 readSize;

    for (readSize = 0; readSize < StreamInfo.header.chanMax; readSize++) {
        slot = &StreamInfo.slot[readSize];
        if (&slot->file == fileInfo) {
            break;
        }
    }
    if (readSize == StreamInfo.header.chanMax) {
        return;
    }
    slot->readBusyF = FALSE;
    if (slot->shutdownF != 0) {
        slot->shutdownF = FALSE;
        msmStreamClose(readSize);
    } else if (DVDGetCommandBlockStatus(&fileInfo->cb) == 0) {
        sndStreamARAMUpdate(slot->stid, (slot->bufNo != 0) ? 0 : slot->streamFrq / 2, slot->streamFrq / 2, 0, 0);
    } else {
        if (slot->status == 4) {
            sndStreamDeactivate(slot->stid);
        }
        msmStreamClose(readSize);
        if (slot->slotL != -1) {
            StreamInfo.slot[slot->slotL].slotR = -1;
        }
        if (slot->slotR != -1) {
            StreamInfo.slot[slot->slotR].slotL = -1;
        }
    }
}

static u32 msmStreamUpdateFunc(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user) {
    MSM_STREAM_SLOT* slot;
    s32 len3;
    s32 updateLen;
    s32 len;

    slot = &StreamInfo.slot[user];
    if (slot->streamOffF != 0) {
        msmStreamShutdown(user);
        return 0;
    }
    updateLen = slot->streamFrq / 2;
    if (len1 < updateLen) {
        len = 0;
        slot->unk64 = slot->unk68 + (len1 - slot->unk6C);
    } else {
        msmStreamData(user);
        len = updateLen;
        len3 = slot->unk68 + (updateLen - slot->unk6C);
        slot->unk68 = len3;
        slot->unk64 = len3;
        slot->unk6C = 0;
    }
    if (slot->unk64 >= slot->loopEndOfs) {
        if (slot->stereoF != 0) {
            slot->unk68 = 0;
            slot->unk64 -= slot->loopEndOfs;
            if (len1 < updateLen) {
                slot->unk6C = len1 - slot->unk64;
            }
        } else {
            slot->streamOffF = 1;
            slot->pauseF = 0;
        }
    }
    return len;
}

static s32 msmStreamSlotInit(MSM_STREAM_SLOT *slot, MSM_STREAM_PACK* pack, STREAM_PARAM* param, s32 no) {
    MSM_STREAM *stream;
    s32 temp_r3;
    s32 ret;

    stream = &pack->stream[no];
    slot->volBase = pack->vol;
    slot->vol = param->vol;
    slot->volFade = slot->pauseVol = 127;
    slot->panBase = pack->pan;
    slot->pan = param->pan;
    slot->span = param->span;
    slot->auxA = param->auxA;
    slot->auxB = param->auxB;
    slot->stereoF = (pack->flag >> 1) & 1;
    slot->streamBaseOfs = stream->sampleOfs;
    slot->streamPosStart = (pack->loopOfsStart >> 1) & ~7;
    slot->frq = pack->frq;
    slot->adpcmInfo = &StreamInfo.adpcmParam[stream->adpcmParamIdx];
    slot->fadeMaxTime = 0;
    slot->pauseTimeMax = 0;
    slot->pauseTime = 0;
    slot->pauseLen = 0;
    slot->firstF = 1;
    slot->streamOffF = 0;
    slot->shutdownF = 0;
    slot->pauseF = 0;
    slot->updateAramF = 0;
    slot->bufNo = 1;
    slot->streamBufSize = (StreamInfo.header.sampleFrq * StreamInfo.header.maxBufs * SND_STREAM_ADPCM_BLKBYTES / SND_STREAM_ADPCM_BLKSIZE + 0x3F) & ~0x3F;
    if (slot->streamBufSize > StreamInfo.bufSize) {
        slot->streamBufSize = StreamInfo.bufSize;
    }
    slot->streamFrq = (slot->streamBufSize / SND_STREAM_ADPCM_BLKBYTES) * SND_STREAM_ADPCM_BLKSIZE;
    slot->loopLen = (pack->loopOfsEnd >> 1) & ~0x1F;
    slot->loopEndOfs = (slot->loopLen / SND_STREAM_ADPCM_BLKBYTES) * SND_STREAM_ADPCM_BLKSIZE;
    slot->unk64 = slot->unk68 = 0;
    slot->unk6C = 0;
    slot->slotL = -1;
    slot->slotR = -1;
    slot->streamPos = param->sampleOfs;
    ret = slot->streamBufSize / 2;
    if ((temp_r3 = slot->loopLen - slot->streamPos) < slot->streamBufSize / 2) {
        ret = temp_r3;
        slot->streamReadSize = slot->streamBufSize / 2 - temp_r3;
        slot->streamReadBuf = (void*) ((u32) slot->streamBuf + temp_r3);
        memset(slot->streamReadBuf, 0, slot->streamReadSize);
    }
    slot->status = 2;
    return ret;
}
