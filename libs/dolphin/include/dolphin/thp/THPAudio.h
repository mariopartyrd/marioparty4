#ifndef _DOLPHIN_THPAUDIO
#define _DOLPHIN_THPAUDIO

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct THPAudioRecordHeader {
  u32 offsetNextChannel;
  u32 sampleSize;
  s16 lCoef[8][2];
  s16 rCoef[8][2];
  s16 lYn1;
  s16 lYn2;
  s16 rYn1;
  s16 rYn2;
} THPAudioRecordHeader;

typedef struct THPAudioDecodeInfo {
  u8* encodeData;
  u32 offsetNibbles;
  u8 predictor;
  u8 scale;
  s16 yn1;
  s16 yn2;
} THPAudioDecodeInfo;

u32 THPAudioDecode(s16* audioBuffer, u8* audioFrame, s32 flag);
static s32 __THPAudioGetNewSample(THPAudioDecodeInfo* info);
static void __THPAudioInitialize(THPAudioDecodeInfo* info, u8* ptr);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_THPAUDIO
