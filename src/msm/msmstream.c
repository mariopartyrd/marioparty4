#include "msm/msmstream.h"
#include "msm/msmmem.h"
#include "msm/msmsys.h"

typedef struct {
    /* 0x00 */ SND_STREAMID unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ u8 unk08;
    /* 0x09 */ u8 unk09;
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 unk0D;
    /* 0x0E */ s8 unk0E;
    /* 0x0F */ s8 unk0F;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ volatile s32 unk14;
    /* 0x18 */ volatile s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ char unk20[4];
    /* 0x24 */ volatile s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s8 unk2C;
    /* 0x2D */ s8 unk2D;
    /* 0x2E */ s8 unk2E;
    /* 0x2F */ char unk2F[1];
    /* 0x30 */ void* unk30;
    /* 0x34 */ u32 unk34;
    /* 0x38 */ u32 unk38;
    /* 0x3C */ struct {
        volatile u8 unk3C_0 : 1;
        volatile u8 unk3C_1 : 1;
        u8 unk3C_2 : 1;
        u8 unk3C_3 : 1;
        volatile u8 unk3C_4 : 1;
        volatile u8 unk3C_5 : 1;
        volatile u8 unk3C_6 : 1;
    };
    /* 0x3D */ char unk3D[3];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ SND_ADPCMSTREAM_INFO* unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ u32 unk4C;
    /* 0x50 */ u32 unk50;
    /* 0X54 */ s32 unk54;
    /* 0x58 */ u32 unk58;
    /* 0x5C */ void* unk5C;
    /* 0X60 */ s32 unk60;
    /* 0x64 */ u32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ DVDFileInfo unk70;
} msmStreamUnk20Struct; // Size 0xAC

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ char unk13[1];
    /* 0x14 */ u32* unk14;
    /* 0x18 */ s8* unk18;
    /* 0x1C */ SND_ADPCMSTREAM_INFO* unk1C;
    /* 0x20 */ msmStreamUnk20Struct* unk20;
    /* 0x24 */ char unk24[0x1C];
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
} msmStreamStruct; // Size 0x60

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
} StructSlotInitInnerArg1; // Size 8

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 unk0C;
    /* 0x10 */ StructSlotInitInnerArg1 unk10[2];
} StructSlotInitArg1; // Size unknown

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[3];
    /* 0x08 */ s32 unk08;
} StructSlotInitArg2; // Size unknown

static void msmStreamPauseFade(s32 arg0);
static void msmStreamFade(s32 arg0);
static void msmStreamDvdCallback(s32 result, DVDFileInfo* fileInfo);
static void msmStreamStopSub(s32 streamNo, s32 speed);
static void msmStreamDvdCallback2(s32 arg0, DVDFileInfo* arg1);
static u32 msmStreamUpdateFunc(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user);
static s32 msmStreamSlotInit(msmStreamUnk20Struct* arg0, StructSlotInitArg1* arg1, StructSlotInitArg2* arg2, s32 arg3);

static msmStreamStruct StreamInfo ATTRIBUTE_ALIGN(32);

static inline void msmStreamInline00(s32 streamNo) {
    msmStreamUnk20Struct* temp_ptr;

    temp_ptr = &StreamInfo.unk20[streamNo];
    DVDClose(&temp_ptr->unk70);
    temp_ptr->unk06 = 0;
}

s32 msmStreamGetStatus(int streamNo) {
    msmStreamUnk20Struct* temp_r3;
    s32 var_r4;

    if (streamNo < 0 || streamNo >= StreamInfo.unk44) {
        return 0;
    }
    temp_r3 = &StreamInfo.unk20[streamNo];
    switch (temp_r3->unk06) {
        case 4:
            var_r4 = 2;
            break;
        case 2:
        case 3:
            var_r4 = 4;
            break;
        case 5:
            var_r4 = 1;
            break;
        default:
            var_r4 = 0;
            break;
    }
    if (temp_r3->unk3C_5 == 1) {
        var_r4 = 3;
    }
    if (var_r4 == 0 && temp_r3->unk0E != -1) {
        var_r4 = msmStreamGetStatus(temp_r3->unk0E);
    }
    return var_r4;
}

static inline void msmStreamInline04(msmStreamUnk20Struct* arg0) {
    s32 var_r10;
    s32 temp_var;

    if (StreamInfo.unk12 != 0) {
        var_r10 = arg0->unk0C + arg0->unk0D - 0x40;
        if (var_r10 < 0) {
            var_r10 = 0;
        }
        if (var_r10 > 0x7F) {
            var_r10 = 0x7F;
        }
    } else {
        var_r10 = 0x40;
    }
    temp_var = arg0->unk08 * arg0->unk09 * arg0->unk0A * arg0->unk0B / 2048383;
    sndStreamMixParameterEx(arg0->unk00, temp_var * StreamInfo.unk11 / 127, var_r10, arg0->unk2C, arg0->unk2D, arg0->unk2E);
}

void msmStreamSetMasterVolume(s32 arg0) {
    s32 var_r27;

    StreamInfo.unk11 = arg0 & 0x7F;
    for (var_r27 = 0; var_r27 < StreamInfo.unk44; var_r27++) {
        if (StreamInfo.unk20[var_r27].unk06 != 0) {
            msmStreamInline04(&StreamInfo.unk20[var_r27]);
        }
    }
}

static inline BOOL msmStreamInline01(msmStreamUnk20Struct* arg0) {
    if (arg0->unk06 != 0 || arg0->unk3C_5 != 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void msmStreamStopAll(s32 speed) {
    msmStreamUnk20Struct* temp_r29;
    s32 var_r28;

    msmSysIrqDisable();
    for (var_r28 = 0; var_r28 < StreamInfo.unk44; var_r28++) {
        if (var_r28 >= 0 && var_r28 < StreamInfo.unk44) {
            temp_r29 = &StreamInfo.unk20[var_r28];
            if (msmStreamInline01(temp_r29)) {
                msmSysIrqDisable();
                msmStreamStopSub(var_r28, speed);
                if (temp_r29->unk0E != -1) {
                    msmStreamStopSub(temp_r29->unk0E, speed);
                }
                if (temp_r29->unk0F != -1) {
                    msmStreamStopSub(temp_r29->unk0F, speed);
                }
                msmSysIrqEnable();
            }
        }
    }
    msmSysIrqEnable();
}

static inline void msmStreamInline03(int streamNo, s32 speed) {
    msmStreamUnk20Struct* temp_ptr = &StreamInfo.unk20[streamNo];

    if (temp_ptr->unk3C_5 != 0) {
        temp_ptr->unk3C_5 = 0;
        speed = 0;
    }
    temp_ptr->unk24 = speed / 15;
    if (temp_ptr->unk24 != 0) {
        temp_ptr->unk28 = temp_ptr->unk24;
        temp_ptr->unk0A = 0x7F;
    } else {
        msmStreamSlotOff(streamNo);
    }
}

s32 msmStreamStop(int streamNo, s32 speed) {
    msmStreamUnk20Struct* temp_r31;
    s32 unused;

    if (streamNo < 0 || streamNo >= StreamInfo.unk44) {
        return MSM_ERR_8C;
    }
    temp_r31 = &StreamInfo.unk20[streamNo];
    if (msmStreamInline01(temp_r31)) {
        msmSysIrqDisable();
        msmStreamInline03(streamNo, speed);
        if (temp_r31->unk0E != -1) {
            msmStreamInline03(temp_r31->unk0E, speed);
        }
        if (temp_r31->unk0F != -1) {
            msmStreamInline03(temp_r31->unk0F, speed);
        }
        msmSysIrqEnable();
    }
    return 0;
}

int msmStreamPlay(int streamId, MSM_STREAMPARAM* streamParam) {
    if (streamId < 0 || streamId >= StreamInfo.unk42) {
        return MSM_ERR_INVALIDID;
    }
    if (StreamInfo.unk14[streamId] == 0) {
        return MSM_ERR_REMOVEDID;
    }
    if (StreamInfo.unk18[StreamInfo.unk14[streamId] - StreamInfo.unk58] & 1) {
        return msmStreamPackStartStereo(streamId, streamParam, 0);
    } else {
        return msmStreamPackStartMono(streamId, streamParam, 0);
    }
}

void msmStreamPeriodicProc(void) {
    msmStreamUnk20Struct* temp_r28;
    s32 var_r27;

    StreamInfo.unk10 = 0;
    for (var_r27 = 0; var_r27 < StreamInfo.unk44; var_r27++) {
        temp_r28 = &StreamInfo.unk20[var_r27];
        msmStreamFade(var_r27);
        msmStreamPauseOff(var_r27);
        msmStreamPauseFade(var_r27);
        if (temp_r28->unk06 != 0) {
            StreamInfo.unk10++;
        }
    }
}

void msmStreamSetOutputMode(s32 arg0) {
    s32 var_r27;

    StreamInfo.unk12 = arg0;
    for (var_r27 = 0; var_r27 < StreamInfo.unk44; var_r27++) {
        if (StreamInfo.unk20[var_r27].unk06 != 0) {
            msmStreamInline04(&StreamInfo.unk20[var_r27]);
        }
    }
}

void msmStreamAmemFree(void) {
    u32 var_r29;

    for (var_r29 = 0; var_r29 < StreamInfo.unk44; var_r29++) {
        sndStreamFree(StreamInfo.unk20[var_r29].unk00);
    }
}

s32 msmStreamAmemAlloc(void) {
    u32 var_r25;
    msmStreamUnk20Struct* temp_r24;

    for (var_r25 = 0; var_r25 < StreamInfo.unk44; var_r25++) {
        temp_r24 = &StreamInfo.unk20[var_r25];
        temp_r24->unk06 = 0;
        temp_r24->unk0F = -1;
        temp_r24->unk0E = -1;
        temp_r24->unk30 = msmMemAlloc(StreamInfo.unk04);
        if (temp_r24->unk30 == NULL) {
            return MSM_ERR_OUTOFMEM;
        }
        temp_r24->unk34 = StreamInfo.unk04;
        temp_r24->unk38 = StreamInfo.unk08;
        temp_r24->unk00 = sndStreamAllocEx(0xFF, temp_r24->unk30, temp_r24->unk38, StreamInfo.unk48, 0, 0x40, 0, 0, 0, 0, 0x30001, msmStreamUpdateFunc, var_r25, NULL);
        if (temp_r24->unk00 == -1) {
            return MSM_ERR_STREAMALLOC_FAIL;
        }
    }
    return StreamInfo.unk04 * StreamInfo.unk44;
}

s32 msmStreamInit(char* arg0) {
    DVDFileInfo spC;
    s32 temp_r27;

    StreamInfo.unk42 = 0;
    StreamInfo.unk44 = 0;
    StreamInfo.unk11 = 0x7F;
    StreamInfo.unk10 = 0;
    if (arg0 == NULL) {
        return 0;
    }
    StreamInfo.unk0C = DVDConvertPathToEntrynum(arg0);
    if (StreamInfo.unk0C == -1) {
        return MSM_ERR_OPENFAIL;
    }
    if (!msmFioOpen(StreamInfo.unk0C, &spC)) {
        return MSM_ERR_OPENFAIL;
    }
    if (msmFioRead(&spC, &StreamInfo.unk40, 0x20, 0) < 0) {
        msmFioClose(&spC);
        return MSM_ERR_READFAIL;
    }
    if (StreamInfo.unk40 != 1) {
        msmFioClose(&spC);
        return MSM_ERR_INVALIDFILE;
    }
    if (StreamInfo.unk42 != 0) {
        temp_r27 = (StreamInfo.unk54 - StreamInfo.unk50 + 0x1F) & ~0x1F;
        StreamInfo.unk14 = msmMemAlloc(temp_r27);
        if (StreamInfo.unk14 == NULL) {
            msmFioClose(&spC);
            return MSM_ERR_OUTOFMEM;
        }
        if (msmFioRead(&spC, StreamInfo.unk14, temp_r27, StreamInfo.unk50) < 0) {
            msmFioClose(&spC);
            return MSM_ERR_READFAIL;
        }
        temp_r27 = (StreamInfo.unk5C - StreamInfo.unk58 + 0x1F) & ~0x1F;
        StreamInfo.unk18 = msmMemAlloc(temp_r27);
        if (StreamInfo.unk18 == NULL) {
            msmFioClose(&spC);
            return MSM_ERR_OUTOFMEM;
        }
        if (msmFioRead(&spC, StreamInfo.unk18, temp_r27, StreamInfo.unk58) < 0) {
            msmFioClose(&spC);
            return MSM_ERR_READFAIL;
        }
        temp_r27 = StreamInfo.unk58 - StreamInfo.unk54;
        StreamInfo.unk1C = msmMemAlloc(temp_r27);
        if (StreamInfo.unk1C == NULL) {
            msmFioClose(&spC);
            return MSM_ERR_OUTOFMEM;
        }
        if (msmFioRead(&spC, StreamInfo.unk1C, temp_r27, StreamInfo.unk54) < 0) {
            msmFioClose(&spC);
            return MSM_ERR_READFAIL;
        }
    }
    msmFioClose(&spC);
    StreamInfo.unk00 = (StreamInfo.unk48 + 13) / 14;
    StreamInfo.unk04 = (8 * StreamInfo.unk00 * StreamInfo.unk4C + 0x3F) & ~0x3F;
    StreamInfo.unk08 = (StreamInfo.unk04 / 8) * 14;
    StreamInfo.unk20 = msmMemAlloc(StreamInfo.unk44 * sizeof(*StreamInfo.unk20));
    memset(StreamInfo.unk20, 0, StreamInfo.unk44 * sizeof(*StreamInfo.unk20));
    return 0;
}

void msmStreamPauseOff(s32 arg0) {
    msmStreamUnk20Struct* temp_r31;
    u32 temp_r3;
    u32 var_r30;

    temp_r31 = &StreamInfo.unk20[arg0];
    if (temp_r31->unk14 == 0) {
        return;
    }
    if (temp_r31->unk3C_5 == 0) {
        temp_r31->unk14 = 0;
        return;
    }
    if (temp_r31->unk18 != 0) {
        temp_r31->unk18 = -(temp_r31->unk14 + 1);
        if (temp_r31->unk18 == 0) {
            temp_r31->unk0B = 0x7F;
            msmStreamInline04(temp_r31);
        }
        temp_r31->unk14 = 0;
        temp_r31->unk3C_5 = 0;
    } else if (temp_r31->unk06 == 0 && DVDFastOpen(StreamInfo.unk0C, &temp_r31->unk70) == TRUE) {
        if (--temp_r31->unk14 != 0) {
            temp_r31->unk18 = -temp_r31->unk14;
            temp_r31->unk1C = 0;
            temp_r31->unk0B = 0;
        } else {
            temp_r31->unk0B = 0x7F;
        }
        temp_r31->unk14 = 0;
        temp_r31->unk3C_1 = 1;
        temp_r31->unk3C_2 = 0;
        temp_r31->unk3C_4 = 0;
        temp_r31->unk3C_5 = 0;
        temp_r31->unk3C_6 = 0;
        temp_r31->unk3C_0 = 1;
        temp_r31->unk64 = temp_r31->unk68 = (temp_r31->unk10 / 8) * 14;
        temp_r31->unk6C = 0;
        temp_r31->unk4C = temp_r31->unk10;
        var_r30 = temp_r31->unk34 / 2;
        if ((temp_r3 = temp_r31->unk50 - temp_r31->unk4C) < temp_r31->unk34 / 2) {
            var_r30 = temp_r3;
            temp_r31->unk58 = temp_r31->unk34 / 2 - temp_r3;
            temp_r31->unk5C = (void*) ((u32) temp_r31->unk30 + temp_r3);
            memset(temp_r31->unk5C, 0, temp_r31->unk58);
        }
        temp_r31->unk06 = 2;
        temp_r31->unk4C += var_r30;
        temp_r31->unk3C_3 = 1;
        DVDReadAsync(&temp_r31->unk70, temp_r31->unk30, var_r30, temp_r31->unk48 + (temp_r31->unk4C - var_r30), msmStreamDvdCallback);
    }
}

static inline void msmStreamInline05(s32 streamNo) {
    msmStreamUnk20Struct* temp_r31;

    temp_r31 = &StreamInfo.unk20[streamNo];
    switch (temp_r31->unk06) {
        case 2:
            temp_r31->unk3C_4 = 1;
            temp_r31->unk06 = 5;
            break;
        case 3:
            msmStreamInline00(streamNo);
            break;
        case 4:
            if (temp_r31->unk3C_2 == 0) {
                sndStreamMixParameterEx(temp_r31->unk00, 0, 0x40, 0, 0, 0);
                temp_r31->unk3C_2 = 1;
                temp_r31->unk06 = 5;
            }
            break;
    }
}

void msmStreamPauseOn(s32 streamNo, s32 arg1) {
    msmStreamUnk20Struct* temp_r31;

    temp_r31 = &StreamInfo.unk20[streamNo];
    temp_r31->unk14 = 0;
    if (temp_r31->unk3C_5 != 0) {
        return;
    }
    temp_r31->unk3C_5 = 1;
    temp_r31->unk18 = arg1 / 15;
    if (temp_r31->unk18 != 0) {
        temp_r31->unk1C = temp_r31->unk18;
        temp_r31->unk0B = 0x7F;
        return;
    }
    temp_r31->unk10 = ((temp_r31->unk64 / 7) * 4) & ~7;
    if (temp_r31->unk07 != 0) {
        if (temp_r31->unk10 >= temp_r31->unk50 - temp_r31->unk34 / 4) {
            temp_r31->unk10 = 0;
        }
    } else if (temp_r31->unk10 >= temp_r31->unk50) {
        temp_r31->unk3C_5 = 0;
    }
    msmStreamInline05(streamNo);
}

static void msmStreamPauseFade(s32 arg0) {
    msmStreamUnk20Struct* temp_r5;

    temp_r5 = &StreamInfo.unk20[arg0];
    if (temp_r5->unk06 != 4) {
        return;
    }
    if (temp_r5->unk18 > 0) {
        if (--temp_r5->unk1C == 0) {
            temp_r5->unk18 = 0;
            temp_r5->unk3C_5 = 0;
            msmStreamPauseOn(arg0, 0);
        } else {
            temp_r5->unk0B = temp_r5->unk1C * 0x7F / temp_r5->unk18;
            msmStreamInline04(temp_r5);
        }
    } else if (temp_r5->unk18 < 0) {
        if (++temp_r5->unk1C >= -temp_r5->unk18) {
            temp_r5->unk18 = 0;
            temp_r5->unk0B = 0x7F;
            msmStreamInline04(temp_r5);
        } else {
            temp_r5->unk0B = temp_r5->unk1C * 0x7F / -temp_r5->unk18;
            msmStreamInline04(temp_r5);
        }
    }
}

static void msmStreamFade(s32 arg0) {
    msmStreamUnk20Struct* temp_r5;

    temp_r5 = &StreamInfo.unk20[arg0];
    if (temp_r5->unk06 != 4) {
        return;
    }
    if (temp_r5->unk24 > 0) {
        if (--temp_r5->unk28 == 0) {
            temp_r5->unk24 = 0;
            msmStreamInline03(arg0, 0);
        } else {
            temp_r5->unk0A = temp_r5->unk28 * 0x7F / temp_r5->unk24;
            msmStreamInline04(temp_r5);
        }
    } else if (temp_r5->unk24 < 0) {
        if (++temp_r5->unk28 >= -temp_r5->unk24) {
            temp_r5->unk24 = 0;
            temp_r5->unk0A = 0x7F;
            msmStreamInline04(temp_r5);
        } else {
            temp_r5->unk0A = temp_r5->unk28 * 0x7F / -temp_r5->unk24;
            msmStreamInline04(temp_r5);
        }
    }
}

static void msmStreamStopSub(s32 streamNo, s32 speed) {
    msmStreamUnk20Struct* temp_r31;
    s32 var_r4;

    var_r4 = speed;
    temp_r31 = &StreamInfo.unk20[streamNo];
    if (temp_r31->unk3C_5 != 0) {
        temp_r31->unk3C_5 = 0;
        var_r4 = 0;
    }
    temp_r31->unk24 = var_r4 / 15;
    if (temp_r31->unk24 != 0) {
        temp_r31->unk28 = temp_r31->unk24;
        temp_r31->unk0A = 0x7F;
        return;
    }
    msmStreamInline05(streamNo);
}

static void msmStreamSetParamSub(msmStreamUnk20Struct* arg0) {
    int var_r10;
    s32 temp_var;

    if (StreamInfo.unk12 != 0) {
        var_r10 = arg0->unk0C + arg0->unk0D - 0x40;
        if (var_r10 < 0) {
            var_r10 = 0;
        }
        if (var_r10 > 0x7F) {
            var_r10 = 0x7F;
        }
    } else {
        var_r10 = 0x40;
    }
    temp_var = arg0->unk08 * arg0->unk09 * arg0->unk0A * arg0->unk0B / 2048383;
    sndStreamMixParameterEx(arg0->unk00, temp_var * StreamInfo.unk11 / 127, var_r10, arg0->unk2C, arg0->unk2D, arg0->unk2E);
}

s32 msmStreamPackStartStereo(s32 arg0, MSM_STREAMPARAM* arg1, s32 arg2) {
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    u32 temp_r3_3;
    u32 temp_r3_4;
    StructSlotInitArg2 sp1C;
    msmStreamUnk20Struct* temp_r25;
    msmStreamUnk20Struct* temp_r24;
    StructSlotInitArg1* temp_r23;

    var_r29 = (arg1 != NULL) ? arg1->flag : 0;
    if (var_r29 & MSM_STREAMPARAM_CHAN) {
        var_r28 = arg1->chan;
        var_r27 = arg1->chan + 1;
        if (var_r28 < 0 || var_r28 >= StreamInfo.unk44) {
            return MSM_ERR_6E;
        }
        if (var_r27 < 0 || var_r27 >= StreamInfo.unk44) {
            return MSM_ERR_6E;
        }
        if (msmStreamInline01(&StreamInfo.unk20[var_r28])) {
            return MSM_ERR_6E;
        }
        if (msmStreamInline01(&StreamInfo.unk20[var_r27])) {
            return MSM_ERR_6E;
        }
    } else {
        for (var_r28 = 0; var_r28 < StreamInfo.unk44; var_r28++) {
            if (!msmStreamInline01(&StreamInfo.unk20[var_r28])) {
                break;
            }
        }
        for (var_r27 = var_r28 + 1; var_r27 < StreamInfo.unk44; var_r27++) {
            if (!msmStreamInline01(&StreamInfo.unk20[var_r27])) {
                break;
            }
        }
        if (var_r28 == StreamInfo.unk44 || var_r27 == StreamInfo.unk44) {
            return MSM_ERR_6E;
        }
    }
    temp_r25 = &StreamInfo.unk20[var_r28];
    temp_r24 = &StreamInfo.unk20[var_r27];
    temp_r23 = (StructSlotInitArg1*) ((u32) StreamInfo.unk18 + (StreamInfo.unk14[arg0] - StreamInfo.unk58));
    sp1C.unk00 = (var_r29 & MSM_STREAMPARAM_VOL) ? arg1->vol : 0x7F;
    sp1C.unk02 = (var_r29 & MSM_STREAMPARAM_SPAN) ? arg1->span : (s32) temp_r23->unk03;
    sp1C.unk03 = (var_r29 & MSM_STREAMPARAM_AUXA) ? arg1->auxA : (s32) temp_r23->unk04;
    sp1C.unk04 = (var_r29 & MSM_STREAMPARAM_AUXB) ? arg1->auxB : (s32) temp_r23->unk05;
    sp1C.unk08 = arg2;
    msmSysIrqDisable();
    sp1C.unk01 = 0;
    temp_r3_3 = msmStreamSlotInit(temp_r25, temp_r23, &sp1C, 0);
    sp1C.unk01 = 0x7F;
    temp_r3_4 = msmStreamSlotInit(temp_r24, temp_r23, &sp1C, 1);
    temp_r25->unk04 = arg0;
    temp_r24->unk04 = -1;
    temp_r25->unk0E = var_r27;
    temp_r24->unk0F = var_r28;
    if ((var_r29 & MSM_STREAMPARAM_FADESPEED) && arg1->fadeSpeed != 0) {
        temp_r25->unk24 = temp_r24->unk24 = -arg1->fadeSpeed / 15;
        temp_r25->unk28 = temp_r24->unk28 = 0;
        temp_r25->unk0A = temp_r24->unk0A = 0;
    }
    msmSysIrqEnable();
    if (temp_r3_3 == 0) {
        return 0;
    }
    if (var_r29 & MSM_STREAMPARAM_PAUSE) {
        temp_r25->unk3C_5 = temp_r24->unk3C_5 = 1;
        temp_r25->unk06 = temp_r24->unk06 = 0;
        return var_r28;
    }
    if (DVDFastOpen(StreamInfo.unk0C, &temp_r25->unk70) != 1) {
        return MSM_ERR_OPENFAIL;
    }
    if (DVDFastOpen(StreamInfo.unk0C, &temp_r24->unk70) != 1) {
        DVDClose(&temp_r25->unk70);
        return MSM_ERR_OPENFAIL;
    }
    temp_r25->unk4C += temp_r3_3;
    temp_r24->unk4C += temp_r3_4;
    temp_r25->unk3C_3 = 1;
    DVDReadAsync(&temp_r25->unk70, temp_r25->unk30, temp_r3_3, temp_r25->unk48 + (temp_r25->unk4C - temp_r3_3), msmStreamDvdCallback);
    temp_r24->unk3C_3 = 1;
    DVDReadAsync(&temp_r24->unk70, temp_r24->unk30, temp_r3_4, temp_r24->unk48 + (temp_r24->unk4C - temp_r3_4), msmStreamDvdCallback);
    return var_r28;
}

s32 msmStreamPackStartMono(s32 arg0, MSM_STREAMPARAM* arg1, s32 arg2) {
    s32 var_r30;
    s32 var_r29;
    u32 temp_r3_2;
    StructSlotInitArg2 sp18;
    msmStreamUnk20Struct* temp_r27;
    StructSlotInitArg1* temp_r25;

    var_r30 = (arg1 != NULL) ? arg1->flag : 0;
    if (var_r30 & MSM_STREAMPARAM_CHAN) {
        var_r29 = arg1->chan;
        if (var_r29 < 0 || var_r29 >= StreamInfo.unk44) {
            return MSM_ERR_6E;
        }
        if (msmStreamInline01(&StreamInfo.unk20[var_r29])) {
            return MSM_ERR_6E;
        }
    } else {
        for (var_r29 = 0; var_r29 < StreamInfo.unk44; var_r29++) {
            if (!msmStreamInline01(&StreamInfo.unk20[var_r29])) {
                break;
            }
        }
        if (var_r29 == StreamInfo.unk44) {
            return MSM_ERR_6E;
        }
    }
    temp_r27 = &StreamInfo.unk20[var_r29];
    temp_r25 = (StructSlotInitArg1*) ((u32) StreamInfo.unk18 + (StreamInfo.unk14[arg0] - StreamInfo.unk58));
    sp18.unk00 = (var_r30 & MSM_STREAMPARAM_VOL) ? arg1->vol : 0x7F;
    sp18.unk01 = (var_r30 & MSM_STREAMPARAM_PAN) ? arg1->pan : 0x40;
    sp18.unk02 = (var_r30 & MSM_STREAMPARAM_SPAN) ? arg1->span : (s32) temp_r25->unk03;
    sp18.unk03 = (var_r30 & MSM_STREAMPARAM_AUXA) ? arg1->auxA : (s32) temp_r25->unk04;
    sp18.unk04 = (var_r30 & MSM_STREAMPARAM_AUXB) ? arg1->auxB : (s32) temp_r25->unk05;
    sp18.unk08 = arg2;
    msmSysIrqDisable();
    temp_r3_2 = msmStreamSlotInit(temp_r27, temp_r25, &sp18, 0);
    temp_r27->unk04 = arg0;
    if ((var_r30 & MSM_STREAMPARAM_FADESPEED) && arg1->fadeSpeed != 0) {
        temp_r27->unk24 = -arg1->fadeSpeed / 15;
        temp_r27->unk28 = 0;
        temp_r27->unk0A = 0;
    }
    msmSysIrqEnable();
    if (temp_r3_2 == 0) {
        return 0;
    }
    if (var_r30 & MSM_STREAMPARAM_PAUSE) {
        temp_r27->unk3C_5 = 1;
        temp_r27->unk06 = 0;
        return var_r29;
    }
    if (DVDFastOpen(StreamInfo.unk0C, &temp_r27->unk70) != 1) {
        return MSM_ERR_OPENFAIL;
    }
    temp_r27->unk4C += temp_r3_2;
    temp_r27->unk3C_3 = 1;
    DVDReadAsync(&temp_r27->unk70, temp_r27->unk30, temp_r3_2, temp_r27->unk48 + (temp_r27->unk4C - temp_r3_2), msmStreamDvdCallback);
    return var_r29;
}

// Note: identical to msmStreamInline05.
void msmStreamSlotOff(s32 streamNo) {
    msmStreamUnk20Struct* temp_r31;

    temp_r31 = &StreamInfo.unk20[streamNo];
    switch (temp_r31->unk06) {
        case 2:
            temp_r31->unk3C_4 = 1;
            temp_r31->unk06 = 5;
            break;
        case 3:
            msmStreamInline00(streamNo);
            break;
        case 4:
            if (temp_r31->unk3C_2 == 0) {
                sndStreamMixParameterEx(temp_r31->unk00, 0, 0x40, 0, 0, 0);
                temp_r31->unk3C_2 = 1;
                temp_r31->unk06 = 5;
            }
            break;
    }
}

static inline void msmStreamInline06(s32 streamNo) {
    msmStreamUnk20Struct* temp_r25;

    temp_r25 = &StreamInfo.unk20[streamNo];
    msmStreamSlotOff(streamNo);
    sndStreamDeactivate(temp_r25->unk00);
    if (temp_r25->unk3C_3 == 0) {
        msmStreamInline00(streamNo);
    } else {
        temp_r25->unk3C_4 = 1;
    }
}

static void msmStreamData(s32 arg0) {
    s32 temp_r5;
    u32 var_r28;
    void* var_r27;
    msmStreamUnk20Struct* temp_r26;
    s32 var_r24;

    temp_r26 = &StreamInfo.unk20[arg0];
    var_r28 = temp_r5 = temp_r26->unk34 / 2;
    var_r27 = (temp_r26->unk3C_0 != 0)
        ? (void*) ((u32) temp_r26->unk30 + temp_r5)
        :  temp_r26->unk30;
    temp_r26->unk58 = var_r24 = 0;
    if (temp_r26->unk4C + var_r28 > temp_r26->unk50) {
        if (temp_r26->unk50 > temp_r26->unk4C) {
            var_r28 = temp_r26->unk50 - temp_r26->unk4C;
            temp_r26->unk58 = temp_r5 - var_r28;
            temp_r26->unk5C = (void*) ((u32) var_r27 + var_r28);
        } else if (temp_r26->unk07 != 0) {
            temp_r26->unk4C = temp_r26->unk60;
        } else {
            memset(var_r27, 0, temp_r5);
            if (temp_r26->unk3C_0 != 0) {
                var_r24 = temp_r26->unk38 / 2;
            }
            sndStreamARAMUpdate(temp_r26->unk00, var_r24, temp_r26->unk38 / 2, 0, 0);
            var_r28 = 0;
        }
    }
    if (var_r28 != 0) {
        if (DVDGetCommandBlockStatus(&temp_r26->unk70.cb) != 0) {
            if (temp_r26->unk3C_6 != 1) {
                temp_r26->unk3C_6 = 1;
                sndStreamMixParameterEx(temp_r26->unk00, 0, 0x40, 0x40, 0, 0);
                memset(temp_r26->unk30, 0, temp_r26->unk34);
                sndStreamARAMUpdate(temp_r26->unk00, 0, temp_r26->unk38, 0, 0);
            }
        } else {
            if (temp_r26->unk3C_6 == 1) {
                temp_r26->unk3C_6 = 0;
                msmStreamInline04(temp_r26);
            }
            temp_r26->unk4C += var_r28;
            temp_r26->unk3C_3 = 1;
            DVDReadAsync(&temp_r26->unk70, var_r27, var_r28, temp_r26->unk48 + (temp_r26->unk4C - var_r28), msmStreamDvdCallback);
        }
    } else if (temp_r26->unk3C_1 != 0) {
        temp_r26->unk3C_1= 0;
    } else {
        msmStreamInline06(arg0);
    }
    temp_r26->unk3C_0 ^= 1;
}

static inline BOOL msmStreamInline02(s32 streamNo) {
    msmStreamUnk20Struct* temp_ptr;

    temp_ptr = &StreamInfo.unk20[streamNo];
    msmStreamSetParamSub(temp_ptr);
    sndStreamFrq(temp_ptr->unk00, temp_ptr->unk40);
    sndStreamADPCMParameter(temp_ptr->unk00, temp_ptr->unk44);
    sndStreamARAMUpdate(temp_ptr->unk00, 0, temp_ptr->unk38 / 2, 0, 0);
    if (sndStreamActivate(temp_ptr->unk00)) {
        temp_ptr->unk06 = 4;
        msmStreamData(streamNo);
        return TRUE;
    } else {
        msmStreamInline00(streamNo);
        return FALSE;
    }
}

static void msmStreamDvdCallback(s32 arg0, DVDFileInfo* arg1) {
    s32 var_r28;
    msmStreamUnk20Struct* temp_r27;

    for (var_r28 = 0; var_r28 < StreamInfo.unk44; var_r28++) {
        if (&StreamInfo.unk20[var_r28].unk70 == arg1) {
            break;
        }
    }
    if (var_r28 == StreamInfo.unk44) {
        return;
    }
    temp_r27 = &StreamInfo.unk20[var_r28];
    temp_r27->unk3C_3 = 0;
    if (temp_r27->unk3C_4 != 0) {
        temp_r27->unk3C_4 = 0;
        msmStreamInline00(var_r28);
        return;
    }
    if (DVDGetCommandBlockStatus(&arg1->cb) == 0) {
        switch (temp_r27->unk06) {
            case 2:
                if (temp_r27->unk0E != -1) {
                    if (StreamInfo.unk20[temp_r27->unk0E].unk06 != 3) {
                        temp_r27->unk06 = 3;
                        break;
                    }
                    if (!msmStreamInline02(temp_r27->unk0E)) {
                        temp_r27->unk0E = -1;
                    }
                }
                if (temp_r27->unk0F != -1) {
                    if (StreamInfo.unk20[temp_r27->unk0F].unk06 != 3) {
                        temp_r27->unk06 = 3;
                        break;
                    }
                    if (!msmStreamInline02(temp_r27->unk0F)) {
                        temp_r27->unk0F = -1;
                    }
                }
                if (!msmStreamInline02(var_r28)) {
                    if (temp_r27->unk0E != -1) {
                        StreamInfo.unk20[temp_r27->unk0E].unk0F = -1;
                    }
                    if (temp_r27->unk0F != -1) {
                        StreamInfo.unk20[temp_r27->unk0F].unk0E = -1;
                    }
                }
                break;
            case 4:
                if (temp_r27->unk4C >= temp_r27->unk50) {
                    if (temp_r27->unk07 != 0) {
                        temp_r27->unk4C = temp_r27->unk60;
                        if (temp_r27->unk58 != 0) {
                            temp_r27->unk3C_3 = 1;
                            DVDReadAsync(arg1, temp_r27->unk5C, temp_r27->unk58, temp_r27->unk48 + temp_r27->unk4C, msmStreamDvdCallback2);
                            temp_r27->unk4C += temp_r27->unk58;
                            break;
                        }
                    } else if (temp_r27->unk58 != 0) {
                        memset(temp_r27->unk5C, 0, temp_r27->unk58);
                    }
                }
                sndStreamARAMUpdate(temp_r27->unk00, (temp_r27->unk3C_0 != 0) ? 0 : temp_r27->unk38 / 2, temp_r27->unk38 / 2, 0, 0);
                break;
            case 5:
                temp_r27->unk3C_4 = 0;
                msmStreamInline00(var_r28);
                break;
        }
    } else {
        if (temp_r27->unk06 == 4) {
            sndStreamDeactivate(temp_r27->unk00);
        }
        msmStreamInline00(var_r28);
        if (temp_r27->unk0E != -1) {
            StreamInfo.unk20[temp_r27->unk0E].unk0F = -1;
        }
        if (temp_r27->unk0F != -1) {
            StreamInfo.unk20[temp_r27->unk0F].unk0E = -1;
        }
    }
}

static void msmStreamDvdCallback2(s32 arg0, DVDFileInfo* arg1) {
    msmStreamUnk20Struct* var_r30;
    s32 var_r28;

    for (var_r28 = 0; var_r28 < StreamInfo.unk44; var_r28++) {
        var_r30 = &StreamInfo.unk20[var_r28];
        if (&var_r30->unk70 == arg1) {
            break;
        }
    }
    if (var_r28 == StreamInfo.unk44) {
        return;
    }
    var_r30->unk3C_3 = 0;
    if (var_r30->unk3C_4 != 0) {
        var_r30->unk3C_4 = 0;
        msmStreamInline00(var_r28);
    } else if (DVDGetCommandBlockStatus(&arg1->cb) == 0) {
        sndStreamARAMUpdate(var_r30->unk00, (var_r30->unk3C_0 != 0) ? 0 : var_r30->unk38 / 2, var_r30->unk38 / 2, 0, 0);
    } else {
        if (var_r30->unk06 == 4) {
            sndStreamDeactivate(var_r30->unk00);
        }
        msmStreamInline00(var_r28);
        if (var_r30->unk0E != -1) {
            StreamInfo.unk20[var_r30->unk0E].unk0F = -1;
        }
        if (var_r30->unk0F != -1) {
            StreamInfo.unk20[var_r30->unk0F].unk0E = -1;
        }
    }
}

static u32 msmStreamUpdateFunc(void* buffer1, u32 len1, void* buffer2, u32 len2, u32 user) {
    msmStreamUnk20Struct* temp_r31;
    s32 temp_r4;
    s32 temp_r0;
    s32 var_r3;

    temp_r31 = &StreamInfo.unk20[user];
    if (temp_r31->unk3C_2 != 0) {
        msmStreamInline06(user);
        return 0;
    }
    temp_r0 = temp_r31->unk38 / 2;
    if (len1 < temp_r0) {
        var_r3 = 0;
        temp_r31->unk64 = temp_r31->unk68 + (len1 - temp_r31->unk6C);
    } else {
        msmStreamData(user);
        var_r3 = temp_r0;
        temp_r4 = temp_r31->unk68 + (temp_r0 - temp_r31->unk6C);
        temp_r31->unk68 = temp_r4;
        temp_r31->unk64 = temp_r4;
        temp_r31->unk6C = 0;
    }
    if (temp_r31->unk64 >= temp_r31->unk54) {
        if (temp_r31->unk07 != 0) {
            temp_r31->unk68 = 0;
            temp_r31->unk64 -= temp_r31->unk54;
            if (len1 < temp_r0) {
                temp_r31->unk6C = len1 - temp_r31->unk64;
            }
        } else {
            temp_r31->unk3C_2 = 1;
            temp_r31->unk3C_5 = 0;
        }
    }
    return var_r3;
}

static s32 msmStreamSlotInit(msmStreamUnk20Struct* arg0, StructSlotInitArg1* arg1, StructSlotInitArg2* arg2, s32 arg3) {
    StructSlotInitInnerArg1* temp_r10;
    s32 temp_r3;
    s32 var_r30;

    temp_r10 = &arg1->unk10[arg3];
    arg0->unk08 = arg1->unk01;
    arg0->unk09 = arg2->unk00;
    arg0->unk0A = arg0->unk0B = 0x7F;
    arg0->unk0C = arg1->unk02;
    arg0->unk0D = arg2->unk01;
    arg0->unk2C = arg2->unk02;
    arg0->unk2D = arg2->unk03;
    arg0->unk2E = arg2->unk04;
    arg0->unk07 = (arg1->unk00 >> 1) & 1;
    arg0->unk48 = temp_r10->unk00;
    arg0->unk60 = (arg1->unk0C >> 1) & ~7;
    arg0->unk40 = arg1->unk06;
    arg0->unk44 = &StreamInfo.unk1C[temp_r10->unk04];
    arg0->unk24 = 0;
    arg0->unk18 = 0;
    arg0->unk14 = 0;
    arg0->unk10 = 0;
    arg0->unk3C_1 = 1;
    arg0->unk3C_2 = 0;
    arg0->unk3C_4 = 0;
    arg0->unk3C_5 = 0;
    arg0->unk3C_6 = 0;
    arg0->unk3C_0 = 1;
    arg0->unk34 = (StreamInfo.unk48 * StreamInfo.unk4C * 8 / 14 + 0x3F) & ~0x3F;
    if (arg0->unk34 > StreamInfo.unk04) {
        arg0->unk34 = StreamInfo.unk04;
    }
    arg0->unk38 = (arg0->unk34 / 8) * 14;
    arg0->unk50 = (arg1->unk08 >> 1) & ~0x1F;
    arg0->unk54 = (arg0->unk50 / 8) * 14;
    arg0->unk64 = arg0->unk68 = 0;
    arg0->unk6C = 0;
    arg0->unk0E = -1;
    arg0->unk0F = -1;
    arg0->unk4C = arg2->unk08;
    var_r30 = arg0->unk34 / 2;
    if ((temp_r3 = arg0->unk50 - arg0->unk4C) < arg0->unk34 / 2) {
        var_r30 = temp_r3;
        arg0->unk58 = arg0->unk34 / 2 - temp_r3;
        arg0->unk5C = (void*) ((u32) arg0->unk30 + temp_r3);
        memset(arg0->unk5C, 0, arg0->unk58);
    }
    arg0->unk06 = 2;
    return var_r30;
}
