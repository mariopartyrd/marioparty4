#ifndef _THP_THPPLAYER_H
#define _THP_THPPLAYER_H

#include "types.h"
#include <dolphin/dvd.h>
#include "dolphin/os.h"
#include "dolphin/gx.h"
#include "dolphin/thp/THPBuffer.h"
#include "dolphin/thp/THPFile.h"
#include "dolphin/thp/THPInfo.h"

#ifdef __cplusplus
extern "C" {
#endif

// Size: 0x1D0
typedef struct THPPlayer {
	DVDFileInfo mFileInfo;            // _00
	THPHeader mHeader;                // _3C
	THPFrameCompInfo mCompInfo;       // _6C
	THPVideoInfo mVideoInfo;          // _80
	THPAudioInfo mAudioInfo;          // _8C
	void* mThpWorkArea;               // _9C
	BOOL mIsOpen;                     // _A0
	u8 mState;                        // _A4
	u8 mInternalState;                // _A5
	u8 mPlayFlag;                     // _A6
	u8 mAudioExist;                   // _A7
	s32 mDvdError;                    // _A8
	s32 mVideoError;                  // _AC
	BOOL mIsOnMemory;                 // _B0
	u8* mMovieData;                   // _B4
	s32 mInitOffset;                  // _B8
	s32 mInitReadSize;                // _BC
	s32 mInitReadFrame;               // _C0
	u32 mCurField;                    // _C4
	s64 mRetraceCount;                // _C8
	s32 mPrevCount;                   // _D0
	s32 mCurCount;                    // _D4
	s32 mVideoDecodeCount;            // _D8
	f32 mCurVolume;                   // _DC
	f32 mTargetVolume;                // _E0
	f32 mDeltaVolume;                 // _E4
	s32 mRampCount;                   // _E8
	s32 mCurAudioTrack;               // _EC
	s32 mCurVideoNumber;              // _F0
	s32 mCurAudioNumber;              // _F4
	THPTextureSet* mDispTextureSet;   // _F8
	THPAudioBuffer* mPlayAudioBuffer; // _FC
	THPReadBuffer mReadBuffer[10];    // _100
	THPTextureSet mTextureSet[3];     // _178
	THPAudioBuffer mAudioBuffer[3];   // _1A8
} THPPlayer;

extern THPPlayer ActivePlayer;

BOOL THPPlayerInit(int _);
void THPPlayerQuit();
BOOL THPPlayerOpen(const char* fileName, BOOL onMemory);
BOOL THPPlayerClose();
BOOL THPPlayerPlay();
void THPPlayerStop();
BOOL THPPlayerPause();
BOOL THPPlayerPrepare(int offset, u8 flag, int audioTrack);

BOOL THPPlayerSetBuffer(u8* data);

u32 THPPlayerCalcNeedMemory();

BOOL THPPlayerGetVideoInfo(void* dst);
BOOL THPPlayerGetAudioInfo(void* dst);
// f32 THPPlayerGetFrameRate();
BOOL THPPlayerSetVolume(int vol, int duration);

int THPPlayerDrawCurrentFrame(GXRenderModeObj* obj, int x, int y, int polyWidth,
                              int polyHeight); // TODO, parameter names from dwarf info if it exists
u32 THPPlayerGetTotalFrame();
u8 THPPlayerGetState();

void THPPlayerDrawDone();
void THPPlayerPostDrawDone();

// this should go in a dolphin THP header eventually
BOOL THPInit(void);

#ifdef __cplusplus
}
#endif

void PrepareReady(int msg);

#endif /* _THP_THPPLAYER_H */
