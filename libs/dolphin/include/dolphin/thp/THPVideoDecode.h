#ifndef _DOLPHIN_THPVIDEODECODE
#define _DOLPHIN_THPVIDEODECODE

#include "dolphin/thp/THPRead.h"

static void* VideoDecoder(void*);
static void* VideoDecoderForOnMemory(void*);
static void VideoDecode(THPReadBuffer*);

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus
s32 THPVideoDecode(void* file, void* tileY, void* tileU, void* tileV, void* work);
BOOL CreateVideoDecodeThread(OSPriority priority, void* task);
void VideoDecodeThreadStart();
void VideoDecodeThreadCancel();
OSMessage PopFreeTextureSet();
BOOL PushFreeTextureSet(OSMessage*);
OSMessage PopDecodedTextureSet(s32 flags);
BOOL PushDecodedTextureSet(OSMessage*);

extern BOOL VideoDecodeThreadCreated;
extern OSMessageQueue FreeTextureSetQueue;
extern OSMessageQueue DecodedTextureSetQueue;
extern OSThread VideoDecodeThread;

#ifdef __cplusplus
};
#endif

#endif // _DOLPHIN_THPVIDEODECODE
