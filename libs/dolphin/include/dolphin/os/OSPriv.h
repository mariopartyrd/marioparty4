#ifndef _DOLPHIN_OSPRIV
#define _DOLPHIN_OSPRIV

#include "dolphin/os.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OFFSET(addr, align) (((u32)(addr) & ((align)-1)))

// OSAudioSystem.c
void __OSInitAudioSystem(void);
void __OSStopAudioSystem(void);

// OSCache.c
void __OSCacheInit(void);

// OSContext.c
void __OSContextInit(void);

// OSMutex.c
void __OSUnlockAllMutex(struct OSThread *thread);

// OSInterrupt.c
extern void __RAS_OSDisableInterrupts_begin(void);
extern void __RAS_OSDisableInterrupts_end(void);
void __OSInterruptInit(void);
void __OSModuleInit(void);

void __OSInitSystemCall(void);

// OSThread.c
void __OSThreadInit(void);
void __OSReschedule(void);

typedef void (*OSExceptionHandler)(__OSException, OSContext*);
OSExceptionHandler __OSSetExceptionHandler(__OSException exception, OSExceptionHandler handler);
__OSExceptionHandler __OSGetExceptionHandler(__OSException exception);
OSTime __OSGetSystemTime();
OSTime __OSTimeToSystemTime(OSTime);

// OSReset.c
void __OSDoHotReset(s32);

// OSReboot
void __OSReboot(u32 resetCode, u32 bootDol);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSPRIV
