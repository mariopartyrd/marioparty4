#ifndef _DOLPHIN_DTK
#define _DOLPHIN_DTK

#include <dolphin/dvd.h>
#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef void (*DTKCallback)(u32 eventMask);
typedef void (*DTKFlushCallback)(void);

typedef struct DTKTrack {
  struct DTKTrack* prev;
  struct DTKTrack* next;
  char* fileName;
  u32 eventMask;
  DTKCallback callback;
  DVDFileInfo dvdFileInfo;

} DTKTrack;

void DTKInit(void);
void DTKShutdown(void);
u32 DTKQueueTrack(char* fileName, DTKTrack* track, u32 eventMask, DTKCallback callback);
u32 DTKRemoveTrack(DTKTrack* track);
void DTKFlushTracks(DTKFlushCallback callback);
void DTKSetSampleRate(u32 samplerate);
u32 DTKGetSampleRate(void);
void DTKSetInterruptFrequency(u32 samples);
u32 DTKGetInterruptFrequency(void);
void DTKSetRepeatMode(u32 repeat);
u32 DTKGetRepeatMode(void);
void DTKSetState(u32 state);
u32 DTKGetState(void);
void DTKNextTrack(void);
void DTKPrevTrack(void);
u32 DTKGetPosition(void);
DTKTrack* DTKGetCurrentTrack(void);
void DTKSetVolume(u8 left, u8 right);
u16 DTKGetVolume(void);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_DTK
