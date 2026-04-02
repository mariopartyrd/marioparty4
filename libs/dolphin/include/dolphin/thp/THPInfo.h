#ifndef _THP_THPINFO_H
#define _THP_THPINFO_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Size 0xC
typedef struct THPVideoInfo {
	u32 mXSize;     // _00
	u32 mYSize;     // _04
	u32 mVideoType; // _08
} THPVideoInfo;

// Size 0x10
typedef struct THPAudioInfo {
	u32 mSndChannels;   // _00
	u32 mSndFrequency;  // _04
	u32 mSndNumSamples; // _08
	u32 mSndNumTracks;  // _0C
} THPAudioInfo;

// Size 0x14
typedef struct THPFrameCompInfo {
	u32 mNumComponents; // _00
	u8 mFrameComp[16];  // _04
} THPFrameCompInfo;

#ifdef __cplusplus
}
#endif

#endif
