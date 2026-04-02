#ifndef _THP_THPBUFFER_H
#define _THP_THPBUFFER_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Size 0x10
typedef struct THPTextureSet {
	u8* mYTexture;    // _00
	u8* mUTexture;    // _04
	u8* mVTexture;    // _08
	s32 mFrameNumber; // _0C
} THPTextureSet;

// Size 0xC
typedef struct THPAudioBuffer {
	s16* mBuffer;     // _00
	s16* mCurPtr;     // _04
	u32 mValidSample; // _08
} THPAudioBuffer;

// Size 0xC
typedef struct THPReadBuffer {
	u8* mPtr;         // _00
	s32 mFrameNumber; // _04
	BOOL mIsValid;    // _08
} THPReadBuffer;

#ifdef __cplusplus
}
#endif

#endif