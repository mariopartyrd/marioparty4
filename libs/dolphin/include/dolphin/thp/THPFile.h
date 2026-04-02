#ifndef _THP_THPFILE_H
#define _THP_THPFILE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Size 0x30
typedef struct THPHeader {
	char mMagic[4];             // _00
	u32 mVersion;               // _04
	u32 mBufferSize;            // _08
	u32 mAudioMaxSamples;       // _0C
	f32 mFrameRate;             // _10
	u32 mNumFrames;             // _14
	u32 mFirstFrameSize;        // _18
	u32 mMovieDataSize;         // _1C
	u32 mCompInfoDataOffsets;   // _20
	u32 mOffsetDataOffsets;     // _24
	u32 mMovieDataOffsets;      // _28
	u32 mFinalFrameDataOffsets; // _2C
} THPHeader;

#ifdef __cplusplus
}
#endif

#endif