#include "game/THPSimple.h"
#include "game/THPDraw.h"
#include <string.h>

#define ALIGN32(val) (((val) + 0x1F) & ~0x1F)

static void __THPSimpleDVDCallback(s32 result, DVDFileInfo *fileInfo);
static s32 VideoDecode(void *arg0);
static void THPAudioMixCallback(void);

UnkThpStruct10 SimpleControl;
static u8 SoundBuffer[2][0x280];
static u8 WorkBuffer[0x40] ATTRIBUTE_ALIGN(32);

static s32 SoundBufferIndex;
static void *LastAudioBuffer;
static void *CurAudioBuffer;
static s32 bufIdx;
static s32 AudioSystem;
static void (*OldAIDCallback)();
static s32 Initialized;

s32 THPSimpleInit(s32 arg0) {
    s32 temp_r31;

    memset(&SimpleControl, 0, sizeof(SimpleControl));
    LCEnable();
    if (THPInit() == 0) {
        return 0;
    }
    temp_r31 = OSDisableInterrupts();
    AudioSystem = arg0;
    SoundBufferIndex = 0;
    LastAudioBuffer = NULL;
    CurAudioBuffer = NULL;
    OldAIDCallback = AIRegisterDMACallback(THPAudioMixCallback);
    if (OldAIDCallback == NULL && AudioSystem != 0) {
        AIRegisterDMACallback(NULL);
        OSRestoreInterrupts(temp_r31);
        return 0;
    }
    OSRestoreInterrupts(temp_r31);
    if (AudioSystem == 0) {
        memset(SoundBuffer, 0, sizeof(SoundBuffer));
        DCFlushRange(SoundBuffer, sizeof(SoundBuffer));
        AIInitDMA((u32) &SoundBuffer[SoundBufferIndex], sizeof(SoundBuffer[0]));
        AIStartDMA();
    }
    Initialized = 1;
    return 1;
}

void THPSimpleQuit(void) {
    s32 temp_r31;

    LCDisable();
    temp_r31 = OSDisableInterrupts();
    if (OldAIDCallback) {
        AIRegisterDMACallback(OldAIDCallback);
    }
    OSRestoreInterrupts(temp_r31);
    Initialized = 0;
}

s32 THPSimpleOpen(char *arg0) {
    s32 var_r31;
    s32 i;

    if (Initialized == 0) {
        return 0;
    }
    if (SimpleControl.unk98 != 0) {
        return 0;
    }
    memset(&SimpleControl.unk80, 0, sizeof(SimpleControl.unk80));
    memset(SimpleControl.unk88, 0, sizeof(SimpleControl.unk88));
    if (DVDOpen(arg0, &SimpleControl.unk00) == 0) {
        return 0;
    }
    if (DVDReadPrio(&SimpleControl.unk00, &WorkBuffer, 0x40, 0, 2) < 0) {
        DVDClose(&SimpleControl.unk00);
        return 0;
    }
    memcpy(&SimpleControl.unk3C, &WorkBuffer, sizeof(SimpleControl.unk3C));
    if (strcmp(SimpleControl.unk3C.mMagic, "THP") != 0) {
        DVDClose(&SimpleControl.unk00);
        return 0;
    }
    if (SimpleControl.unk3C.mVersion != 0x10000) {
        DVDClose(&SimpleControl.unk00);
        return 0;
    }
    var_r31 = SimpleControl.unk3C.mCompInfoDataOffsets;
    if (DVDReadPrio(&SimpleControl.unk00, &WorkBuffer, 0x20, var_r31, 2) < 0) {
        DVDClose(&SimpleControl.unk00);
        return 0;
    }
    memcpy(&SimpleControl.unk6C, &WorkBuffer, sizeof(SimpleControl.unk6C));
    var_r31 += sizeof(SimpleControl.unk6C);
    SimpleControl.unk9F = 0;
    for (i = 0; i < SimpleControl.unk6C.mNumComponents; i++) {
        switch (SimpleControl.unk6C.mFrameComp[i]) {
            case 0:
                if (DVDReadPrio(&SimpleControl.unk00, &WorkBuffer, 0x20, var_r31, 2) < 0) {
                    DVDClose(&SimpleControl.unk00);
                    return 0;
                }
                memcpy(&SimpleControl.unk80, &WorkBuffer, sizeof(SimpleControl.unk80));
                var_r31 += sizeof(SimpleControl.unk80);
                break;
            case 1:
                if (DVDReadPrio(&SimpleControl.unk00, &WorkBuffer, 0x20, var_r31, 2) < 0) {
                    DVDClose(&SimpleControl.unk00);
                    return 0;
                }
                memcpy(SimpleControl.unk88, &WorkBuffer, sizeof(SimpleControl.unk88));
                SimpleControl.unk9F = 1;
                var_r31 += sizeof(SimpleControl.unk88);
                break;
            default:
                return 0;
        }
    }
    SimpleControl.unkA0 = SimpleControl.unk3C.mMovieDataOffsets;
    SimpleControl.unkB4 = SimpleControl.unk3C.mFirstFrameSize;
    SimpleControl.unkB0 = 0;
    SimpleControl.unkB8 = 0;
    SimpleControl.unkA4 = 0;
    SimpleControl.unk144[0].unk0C = -1;
    SimpleControl.unkAC = 0;
    SimpleControl.unk194 = 0;
    SimpleControl.unk198 = 0;
    SimpleControl.unk9C = 0;
    SimpleControl.unk9D = 0;
    SimpleControl.unk9E = 0;
    SimpleControl.unk98 = 1;
    SimpleControl.unkC0 = SimpleControl.unkBC;
    SimpleControl.unkC8 = 0;
    return 1;
}

s32 THPSimpleClose(void) {
    if (SimpleControl.unk98 != 0 && SimpleControl.unk9C == 0) {
        if (SimpleControl.unk9F != 0) {
            if (SimpleControl.unk9D == 1) {
                return 0;
            }
        } else {
            SimpleControl.unk9D = 0;
        }
        if (SimpleControl.unkA8 == 0) {
            SimpleControl.unk98 = 0;
            DVDClose(&SimpleControl.unk00);
            return 1;
        }
    }
    return 0;
}

s32 THPSimpleCalcNeedMemory(void) {
    s32 var_r31;

    if (SimpleControl.unk98 != 0) {
        var_r31 = ALIGN32(SimpleControl.unk3C.mBufferSize) * 10;
        var_r31 += ALIGN32(SimpleControl.unk80.unk00 * SimpleControl.unk80.unk04);
        var_r31 += ALIGN32(SimpleControl.unk80.unk00 * SimpleControl.unk80.unk04 / 4);
        var_r31 += ALIGN32(SimpleControl.unk80.unk00 * SimpleControl.unk80.unk04 / 4);
        var_r31 += ALIGN32(SimpleControl.unk80.unk00 * SimpleControl.unk80.unk04);
        var_r31 += ALIGN32(SimpleControl.unk80.unk00 * SimpleControl.unk80.unk04 / 4);
        var_r31 += ALIGN32(SimpleControl.unk80.unk00 * SimpleControl.unk80.unk04 / 4);
        if (SimpleControl.unk9F != 0) {
            var_r31 += ALIGN32(SimpleControl.unk3C.mAudioMaxSamples * 4) * 4;
        }
        var_r31 += 0x1000;
        return var_r31;
    }
    return 0;
}

s32 THPSimpleSetBuffer(void *arg0) {
    u8 *var_r31;
    u32 temp_r28;
    u32 temp_r29;
    u32 i;

    if (SimpleControl.unk98 != 0 && SimpleControl.unk9C == 0) {
        if (SimpleControl.unk9D == 1) {
            return 0;
        }
        temp_r28 = ALIGN32(SimpleControl.unk80.unk00 * SimpleControl.unk80.unk04);
        temp_r29 = ALIGN32(SimpleControl.unk80.unk00 * SimpleControl.unk80.unk04 / 4);
        var_r31 = arg0;
        for (i = 0; i < 2; i++) {
            SimpleControl.unk144[i].unk00 = var_r31;
            DCInvalidateRange(var_r31, temp_r28);
            var_r31 += temp_r28;
            SimpleControl.unk144[i].unk04 = var_r31;
            DCInvalidateRange(var_r31, temp_r29);
            var_r31 += temp_r29;
            SimpleControl.unk144[i].unk08 = var_r31;
            DCInvalidateRange(var_r31, temp_r29);
            var_r31 += temp_r29;
        }
        for (i = 0; i < 10; i++) {
            SimpleControl.unkCC[i].unk00 = (s32*) var_r31;
            var_r31 += ALIGN32(SimpleControl.unk3C.mBufferSize);
            SimpleControl.unkCC[i].unk08 = 0;
        }
        if (SimpleControl.unk9F != 0) {
            for (i = 0; i < 4; i++) {
                SimpleControl.unk164[i].unk00 = var_r31;
                SimpleControl.unk164[i].unk04 = var_r31;
                SimpleControl.unk164[i].unk08 = 0;
                var_r31 += ALIGN32(SimpleControl.unk3C.mAudioMaxSamples * 4);
            }
        }
        SimpleControl.unk94 = var_r31;
    }
    return 1;
}

static inline void THPSimpleInlineFunc(void) {
    if (SimpleControl.unkB8 > SimpleControl.unk3C.mNumFrames - 1) {
        if (SimpleControl.unk9E != 1) {
            return;
        }
        SimpleControl.unkB8 = 0;
        SimpleControl.unkA0 = SimpleControl.unk3C.mMovieDataOffsets;
        SimpleControl.unkB4 = SimpleControl.unk3C.mFirstFrameSize;
    }
    SimpleControl.unkA8 = 1;
    if (DVDReadAsyncPrio(&SimpleControl.unk00, SimpleControl.unkCC[SimpleControl.unkB0].unk00, SimpleControl.unkB4, SimpleControl.unkA0, __THPSimpleDVDCallback, 2) != 1) {
        SimpleControl.unkA8 = 0;
        SimpleControl.unkA4 = 1;
    }
}

static void __THPSimpleDVDCallback(s32 result, DVDFileInfo *fileInfo) {
    s32 var_r31;

    if (result == -1) {
        SimpleControl.unkA4 = 1;
        return;
    }
    if (result != -3) {
        SimpleControl.unkA8 = 0;
        SimpleControl.unkCC[SimpleControl.unkB0].unk04 = SimpleControl.unkB8;
        SimpleControl.unkB8++;
        SimpleControl.unkCC[SimpleControl.unkB0].unk08 = 1;
        SimpleControl.unkA0 += SimpleControl.unkB4;
        SimpleControl.unkB4 = *SimpleControl.unkCC[SimpleControl.unkB0].unk00;
        if (SimpleControl.unkB0 + 1 >= 10) {
            var_r31 = 0;
        } else {
            var_r31 = SimpleControl.unkB0 + 1;
        }
        SimpleControl.unkB0 = var_r31;
        if (SimpleControl.unkCC[SimpleControl.unkB0].unk08 == 0 && SimpleControl.unkA4 == 0 && SimpleControl.unk9C == 1) {
            THPSimpleInlineFunc();
        }
    }
}

s32 THPSimplePreLoad(s32 arg0) {
    u32 var_r30;
    s32 var_r29;
    s32 i;

    if (SimpleControl.unk98 != 0 && SimpleControl.unk9C == 0) {
        var_r30 = 10;
        if (arg0 == 0 && SimpleControl.unk3C.mNumFrames < 10) {
            var_r30 = SimpleControl.unk3C.mNumFrames;
        }
        for (i = 0; i < var_r30; i++) {
            if (DVDReadPrio(&SimpleControl.unk00, SimpleControl.unkCC[SimpleControl.unkB0].unk00, SimpleControl.unkB4, SimpleControl.unkA0, 2) < 0) {
                SimpleControl.unkA4 = 1;
                return 0;
            }
            SimpleControl.unkA0 += SimpleControl.unkB4;
            SimpleControl.unkB4 = *SimpleControl.unkCC[SimpleControl.unkB0].unk00;
            SimpleControl.unkCC[SimpleControl.unkB0].unk08 = 1;
            SimpleControl.unkCC[SimpleControl.unkB0].unk04 = SimpleControl.unkB8;
            if (SimpleControl.unkB0 + 1 >= 10) {
                var_r29 = 0;
            } else {
                var_r29 = SimpleControl.unkB0 + 1;
            }
            SimpleControl.unkB0 = var_r29;
            SimpleControl.unkB8++;
            if (SimpleControl.unkB8 > SimpleControl.unk3C.mNumFrames - 1 && SimpleControl.unk9E == 1) {
                SimpleControl.unkB8 = 0;
                SimpleControl.unkA0 = SimpleControl.unk3C.mMovieDataOffsets;
                SimpleControl.unkB4 = SimpleControl.unk3C.mFirstFrameSize;
            }
        }
        SimpleControl.unk9E = arg0;
        SimpleControl.unk9C = 1;
        return 1;
    }
    return 0;
}

void THPSimpleAudioStart(void) {
    SimpleControl.unk9D = 1;
}

void THPSimpleAudioStop(void) {
    SimpleControl.unk9D = 0;
}

s32 THPSimpleLoadStop(void) {
    s32 i;

    if (SimpleControl.unk98 != 0 && SimpleControl.unk9D == 0) {
        SimpleControl.unk9C = 0;
        if (SimpleControl.unkA8 != 0) {
            DVDCancel(&SimpleControl.unk00.cb);
            SimpleControl.unkA8 = 0;
        }
        for (i = 0; i < 10; i++) {
            SimpleControl.unkCC[i].unk08 = 0;
        }
        for (i = 0; i < 4; i++) {
            SimpleControl.unk164[i].unk08 = 0;
        }
        SimpleControl.unk144[0].unk0C = -1;
        SimpleControl.unkA0 = SimpleControl.unk3C.mMovieDataOffsets;
        SimpleControl.unkB4 = SimpleControl.unk3C.mFirstFrameSize;
        SimpleControl.unkB0 = 0;
        SimpleControl.unkB8 = 0;
        SimpleControl.unkA4 = 0;
        SimpleControl.unkAC = 0;
        SimpleControl.unk194 = 0;
        SimpleControl.unk198 = 0;
        SimpleControl.unkBC = SimpleControl.unkC0;
        SimpleControl.unkC8 = 0;
        return 1;
    }
    return 0;
}

s32 THPSimpleDecode(void) {
    u8 *var_r29;
    s32 *var_r30;
    s32 temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    s32 var_r28;
    s32 i;

    if (SimpleControl.unkCC[SimpleControl.unkAC].unk08 != 0) {
        var_r30 = SimpleControl.unkCC[SimpleControl.unkAC].unk00 + 2;
        var_r29 = (u8*) (&SimpleControl.unkCC[SimpleControl.unkAC].unk00[SimpleControl.unk6C.mNumComponents] + 2);
        if (SimpleControl.unk9F != 0) {
            if (SimpleControl.unk164[SimpleControl.unk194].unk08 == 0) {
                for (i = 0; i < SimpleControl.unk6C.mNumComponents; var_r29 += *var_r30, var_r30++, i++) {
                    switch (SimpleControl.unk6C.mFrameComp[i]) {
                        case 0:
                            if (VideoDecode(var_r29) == 0) {
                                return 1;
                            }
                            break;
                        case 1:
                            temp_r26 = THPAudioDecode(SimpleControl.unk164[SimpleControl.unk194].unk00, var_r29, 0);
                            temp_r27 = OSDisableInterrupts();
                            SimpleControl.unk164[SimpleControl.unk194].unk08 = temp_r26;
                            SimpleControl.unk164[SimpleControl.unk194].unk04 = SimpleControl.unk164[SimpleControl.unk194].unk00;
                            OSRestoreInterrupts(temp_r27);
                            SimpleControl.unk194++;
                            if (SimpleControl.unk194 >= 4) {
                                SimpleControl.unk194 = 0;
                            }
                            break;
                    }
                }
            } else {
                return 3;
            }
        } else {
            for (i = 0; i < SimpleControl.unk6C.mNumComponents; var_r29 += *var_r30, var_r30++, i++) {
                if ((s32) SimpleControl.unk6C.mFrameComp[i] != 0) {
                    (void) i; // required to match. Optimized out unreachable code?
                } else if (VideoDecode(var_r29) == 0) {
                    return 1;
                }
            }
        }
        SimpleControl.unkCC[SimpleControl.unkAC].unk08 = 0;
        if (SimpleControl.unkAC + 1 >= 10) {
            var_r28 = 0;
        } else {
            var_r28 = SimpleControl.unkAC + 1;
        }
        SimpleControl.unkAC = var_r28;
        temp_r25 = OSDisableInterrupts();
        if (SimpleControl.unkCC[SimpleControl.unkB0].unk08 == 0 && SimpleControl.unkA8 == 0 && SimpleControl.unkA4 == 0 && SimpleControl.unk9C == 1) {
            THPSimpleInlineFunc();
        }
        OSRestoreInterrupts(temp_r25);
        return 0;
    } else {
        return 2;
    }
}

static s32 VideoDecode(void *arg0) {
    s32 temp_r31;

    bufIdx = (bufIdx + 1) & 1;
    temp_r31 = THPVideoDecode(arg0, SimpleControl.unk144[bufIdx].unk00, SimpleControl.unk144[bufIdx].unk04, SimpleControl.unk144[bufIdx].unk08, SimpleControl.unk94);
    if (temp_r31 == 0) {
        SimpleControl.unk144[0].unk0C = SimpleControl.unkCC[SimpleControl.unkAC].unk04;
        return 1;
    }
    return 0;
}

s32 THPSimpleDrawCurrentFrame(GXRenderModeObj *arg0, GXColor *arg1, Mtx arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (SimpleControl.unk144[0].unk0C >= 0) {
        THPGXYuv2RgbSetup(arg0, arg1, arg2);
        THPGXYuv2RgbDraw(SimpleControl.unk144[bufIdx].unk00, SimpleControl.unk144[bufIdx].unk04, SimpleControl.unk144[bufIdx].unk08, arg3, arg4, SimpleControl.unk80.unk00, SimpleControl.unk80.unk04, arg5, arg6);
        THPGXRestore();
        return SimpleControl.unk144[0].unk0C;
    }
    return -1;
}

static u16 VolumeTable[] = {
    0x0000, 0x0002, 0x0008, 0x0012, 0x0020, 0x0032, 0x0049, 0x0063,
    0x0082, 0x00A4, 0x00CB, 0x00F5, 0x0124, 0x0157, 0x018E, 0x01C9,
    0x0208, 0x024B, 0x0292, 0x02DD, 0x032C, 0x037F, 0x03D7, 0x0432,
    0x0492, 0x04F5, 0x055D, 0x05C9, 0x0638, 0x06AC, 0x0724, 0x07A0,
    0x0820, 0x08A4, 0x092C, 0x09B8, 0x0A48, 0x0ADD, 0x0B75, 0x0C12,
    0x0CB2, 0x0D57, 0x0DFF, 0x0EAC, 0x0F5D, 0x1012, 0x10CA, 0x1187,
    0x1248, 0x130D, 0x13D7, 0x14A4, 0x1575, 0x164A, 0x1724, 0x1801,
    0x18E3, 0x19C8, 0x1AB2, 0x1BA0, 0x1C91, 0x1D87, 0x1E81, 0x1F7F,
    0x2081, 0x2187, 0x2291, 0x239F, 0x24B2, 0x25C8, 0x26E2, 0x2801,
    0x2923, 0x2A4A, 0x2B75, 0x2CA3, 0x2DD6, 0x2F0D, 0x3048, 0x3187,
    0x32CA, 0x3411, 0x355C, 0x36AB, 0x37FF, 0x3956, 0x3AB1, 0x3C11,
    0x3D74, 0x3EDC, 0x4048, 0x41B7, 0x432B, 0x44A3, 0x461F, 0x479F,
    0x4923, 0x4AAB, 0x4C37, 0x4DC7, 0x4F5C, 0x50F4, 0x5290, 0x5431,
    0x55D6, 0x577E, 0x592B, 0x5ADC, 0x5C90, 0x5E49, 0x6006, 0x61C7,
    0x638C, 0x6555, 0x6722, 0x68F4, 0x6AC9, 0x6CA2, 0x6E80, 0x7061,
    0x7247, 0x7430, 0x761E, 0x7810, 0x7A06, 0x7C00, 0x7DFE, 0x8000
};

static void MixAudio(void *arg0, void *arg1, u32 arg2) {
    s32 var_r31;
    u32 var_r27;
    u32 var_r28;
    s32 i;
    u16 temp_r24;
    s16 *var_r26;
    s16 *var_r30;
    s16 *var_r29;

    if (arg1) {
        if (SimpleControl.unk98 != 0 && SimpleControl.unk9D == 1 && SimpleControl.unk9F != 0) {
            var_r28 = arg2;
            var_r30 = arg0;
            var_r26 = arg1;
            while (1) {
                if (SimpleControl.unk164[SimpleControl.unk198].unk08 == 0) {
                    break;
                }
                if (SimpleControl.unk164[SimpleControl.unk198].unk08 >= var_r28) {
                    var_r27 = var_r28;
                } else {
                    var_r27 = SimpleControl.unk164[SimpleControl.unk198].unk08;
                }
                var_r29 = SimpleControl.unk164[SimpleControl.unk198].unk04;
                for (i = 0; i < var_r27; i++) {
                    if (SimpleControl.unkC8 != 0) {
                        SimpleControl.unkC8--;
                        SimpleControl.unkBC += SimpleControl.unkC4;
                    } else {
                        SimpleControl.unkBC = SimpleControl.unkC0;
                    }
                    temp_r24 = VolumeTable[(s32) SimpleControl.unkBC];
                    var_r31 = *var_r26 + ((temp_r24 * *var_r29) >> 0xF);
                    if (var_r31 < -0x8000) {
                        var_r31 = -0x8000;
                    }
                    if (var_r31 > 0x7FFF) {
                        var_r31 = 0x7FFF;
                    }
                    *var_r30 = var_r31;
                    var_r30++;
                    var_r26++;
                    var_r29++;
                    var_r31 = *var_r26 + ((temp_r24 * *var_r29) >> 0xF);
                    if (var_r31 < -0x8000) {
                        var_r31 = -0x8000;
                    }
                    if (var_r31 > 0x7FFF) {
                        var_r31 = 0x7FFF;
                    }
                    *var_r30 = var_r31;
                    var_r30++;
                    var_r26++;
                    var_r29++;
                }
                var_r28 -= var_r27;
                SimpleControl.unk164[SimpleControl.unk198].unk08 -= var_r27;
                SimpleControl.unk164[SimpleControl.unk198].unk04 = var_r29;
                if (SimpleControl.unk164[SimpleControl.unk198].unk08 == 0) {
                    SimpleControl.unk198++;
                    if (SimpleControl.unk198 >= 4) {
                        SimpleControl.unk198 = 0;
                    }
                }
                if (var_r28 == 0) {
                    return;
                }
            }
            memcpy(var_r30, var_r26, var_r28 * 4);
        } else {
            memcpy(arg0, arg1, arg2 * 4);
        }
    } else if (SimpleControl.unk98 != 0 && SimpleControl.unk9D == 1 && SimpleControl.unk9F != 0) {
        var_r28 = arg2;
        var_r30 = arg0;
        while (1) {
            if (SimpleControl.unk164[SimpleControl.unk198].unk08 == 0) {
                break;
            }
            if (SimpleControl.unk164[SimpleControl.unk198].unk08 >= var_r28) {
                var_r27 = var_r28;
            } else {
                var_r27 = SimpleControl.unk164[SimpleControl.unk198].unk08;
            }
            var_r29 = SimpleControl.unk164[SimpleControl.unk198].unk04;
            for (i = 0; i < var_r27; i++) {
                if (SimpleControl.unkC8 != 0) {
                    SimpleControl.unkC8--;
                    SimpleControl.unkBC += SimpleControl.unkC4;
                } else {
                    SimpleControl.unkBC = SimpleControl.unkC0;
                }
                temp_r24 = VolumeTable[(s32) SimpleControl.unkBC];
                var_r31 = (temp_r24 * *var_r29) >> 0xF;
                if (var_r31 < -0x8000) {
                    var_r31 = -0x8000;
                }
                if (var_r31 > 0x7FFF) {
                    var_r31 = 0x7FFF;
                }
                *var_r30 = var_r31;
                var_r30++;
                var_r29++;
                var_r31 = (temp_r24 * *var_r29) >> 0xF;
                if (var_r31 < -0x8000) {
                    var_r31 = -0x8000;
                }
                if (var_r31 > 0x7FFF) {
                    var_r31 = 0x7FFF;
                }
                *var_r30 = var_r31;
                var_r30++;
                var_r29++;
            }
            var_r28 -= var_r27;
            SimpleControl.unk164[SimpleControl.unk198].unk08 -= var_r27;
            SimpleControl.unk164[SimpleControl.unk198].unk04 = var_r29;
            if (SimpleControl.unk164[SimpleControl.unk198].unk08 == 0) {
                SimpleControl.unk198++;
                if (SimpleControl.unk198 >= 4) {
                    SimpleControl.unk198 = 0;
                }
            }
            if (var_r28 == 0) {
                return;
            }
        }
        memset(var_r30, 0, var_r28 * 4);
    } else {
        memset(arg0, 0, arg2 * 4);
    }
}

s32 THPSimpleGetVideoInfo(UnkThpStruct04 *arg0) {
    if (SimpleControl.unk98 != 0) {
        memcpy(arg0, &SimpleControl.unk80, 8);
        return 1;
    }
    return 0;
}

s32 THPSimpleGetTotalFrame(void) {
    if (SimpleControl.unk98 != 0) {
        return SimpleControl.unk3C.mNumFrames;
    }
    return 0;
}

static void THPAudioMixCallback(void) {
    s32 temp_r31;

    if (AudioSystem == 0) {
        SoundBufferIndex ^= 1;
        AIInitDMA((u32) SoundBuffer[SoundBufferIndex], sizeof(SoundBuffer[0]));
        temp_r31 = OSEnableInterrupts();
        MixAudio(SoundBuffer[SoundBufferIndex], 0, 0xA0);
        DCFlushRange(SoundBuffer[SoundBufferIndex], sizeof(SoundBuffer[0]));
        OSRestoreInterrupts(temp_r31);
    } else {
        if (AudioSystem == 1) {
            if (LastAudioBuffer) {
                CurAudioBuffer = LastAudioBuffer;
            }
            OldAIDCallback();
            LastAudioBuffer = (u8*) AIGetDMAStartAddr() + 0x80000000;
        } else {
            OldAIDCallback();
            CurAudioBuffer = (u8*) AIGetDMAStartAddr() + 0x80000000;
        }
        SoundBufferIndex ^= 1;
        AIInitDMA((u32) SoundBuffer[SoundBufferIndex], sizeof(SoundBuffer[0]));
        temp_r31 = OSEnableInterrupts();
        if (CurAudioBuffer) {
            DCInvalidateRange(CurAudioBuffer, sizeof(SoundBuffer[0]));
        }
        MixAudio(SoundBuffer[SoundBufferIndex], CurAudioBuffer, 0xA0);
        DCFlushRange(SoundBuffer[SoundBufferIndex], sizeof(SoundBuffer[0]));
        OSRestoreInterrupts(temp_r31);
    }
}

s32 THPSimpleSetVolume(s32 left, s32 right) {
    s32 temp_r29;

    if (SimpleControl.unk98 != 0 && SimpleControl.unk9F != 0) {
        if (left > 127) {
            left = 127;
        }
        if (left < 0) {
            left = 0;
        }
        if (right > 60000) {
            right = 60000;
        }
        if (right < 0) {
            right = 0;
        }
        temp_r29 = OSDisableInterrupts();
        SimpleControl.unkC0 = left;
        if (right != 0) {
            SimpleControl.unkC8 = (right << 5);
            SimpleControl.unkC4 = (SimpleControl.unkC0 - SimpleControl.unkBC) / SimpleControl.unkC8;
        } else {
            SimpleControl.unkC8 = 0;
            SimpleControl.unkBC = SimpleControl.unkC0;
        }
        OSRestoreInterrupts(temp_r29);
        return 1;
    }
    return 0;
}
