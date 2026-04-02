#ifndef _DOLPHIN_AI
#define _DOLPHIN_AI

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef void (*AISCallback)(u32 count);
typedef void (*AIDCallback)();

#define AI_STREAM_START 1
#define AI_STREAM_STOP 0

#define AI_SAMPLERATE_32KHZ  0
#define AI_SAMPLERATE_48KHZ  1

AIDCallback AIRegisterDMACallback(AIDCallback callback);
void AIInitDMA(u32 start_addr, u32 length);
BOOL AIGetDMAEnableFlag();
void AIStartDMA();
void AIStopDMA();
u32 AIGetDMABytesLeft();
u32 AIGetDMAStartAddr();
u32 AIGetDMALength();
u32 AIGetDSPSampleRate();
void AISetDSPSampleRate(u32 rate);
AISCallback AIRegisterStreamCallback(AISCallback callback);
u32 AIGetStreamSampleCount();
void AIResetStreamSampleCount();
void AISetStreamTrigger(u32 trigger);
u32 AIGetStreamTrigger();
void AISetStreamPlayState(u32 state);
u32 AIGetStreamPlayState();
void AISetStreamSampleRate(u32 rate);
u32 AIGetStreamSampleRate();
void AISetStreamVolLeft(u8 vol);
void AISetStreamVolRight(u8 vol);
u8 AIGetStreamVolLeft();
u8 AIGetStreamVolRight();
void AIInit(u8* stack);
BOOL AICheckInit();
void AIReset();

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_AI
