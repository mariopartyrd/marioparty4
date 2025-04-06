#ifndef _DOLPHIN_OS
#define _DOLPHIN_OS

#include <dolphin/gx.h>
#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Upper words of the masks, since UIMM is only 16 bits
#define OS_CACHED_REGION_PREFIX 0x8000
#define OS_UNCACHED_REGION_PREFIX 0xC000
#define OS_PHYSICAL_MASK 0x3FFF

#define OS_BASE_CACHED (OS_CACHED_REGION_PREFIX << 16)
#define OS_BASE_UNCACHED (OS_UNCACHED_REGION_PREFIX << 16)

#ifdef __MWERKS__
#define AT_ADDRESS(xyz) : (xyz)
#else
#define AT_ADDRESS(xyz)
#endif
typedef s64 OSTime;
typedef u32 OSTick;
u32 __OSBusClock AT_ADDRESS(OS_BASE_CACHED | 0x00F8); // sync with OSLoMem.h
u32 __OSCoreClock AT_ADDRESS(OS_BASE_CACHED | 0x00FC); // sync with OSLoMem.h
#define OS_BUS_CLOCK (u32) __OSBusClock
#define OS_CORE_CLOCK __OSCoreClock
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

#ifndef _DEBUG
#define OSPhysicalToCached(paddr) ((void *)((u32)(paddr) + OS_BASE_CACHED))
#define OSPhysicalToUncached(paddr) ((void *)((u32)(paddr) + OS_BASE_UNCACHED))
#define OSCachedToPhysical(caddr) ((u32)((u8 *)(caddr)-OS_BASE_CACHED))
#define OSUncachedToPhysical(ucaddr) ((u32)((u8 *)(ucaddr)-OS_BASE_UNCACHED))
#define OSCachedToUncached(caddr) ((void *)((u8 *)(caddr) + (OS_BASE_UNCACHED - OS_BASE_CACHED)))
#define OSUncachedToCached(ucaddr) ((void *)((u8 *)(ucaddr) - (OS_BASE_UNCACHED - OS_BASE_CACHED)))
#else
u32 OSPhysicalToCached(void *paddr);
u32 OSPhysicalToUncached(void *paddr);
u32 OSCachedToPhysical(void *caddr);
u32 OSUncachedToPhysical(void *ucaddr);
u32 OSCachedToUncached(void *caddr);
u32 OSUncachedToCached(void *ucaddr);
#endif

#define OSTicksToCycles(ticks) (((ticks) * ((OS_CORE_CLOCK * 2) / OS_TIMER_CLOCK)) / 2)
#define OSTicksToSeconds(ticks) ((ticks) / OS_TIMER_CLOCK)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))
#define OSTicksToMicroseconds(ticks) (((ticks)*8) / (OS_TIMER_CLOCK / 125000))
#define OSTicksToNanoseconds(ticks) (((ticks)*8000) / (OS_TIMER_CLOCK / 125000))
#define OSSecondsToTicks(sec) ((sec)*OS_TIMER_CLOCK)
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)
#define OSNanosecondsToTicks(nsec) (((nsec) * (OS_TIMER_CLOCK / 125000)) / 8000)

#define OSDiffTick(tick1, tick0) ((s32)(tick1) - (s32)(tick0))

#define OSRoundUp32B(x) (((size_t)(x) + 0x1F) & ~(0x1F))
#define OSRoundDown32B(x) (((size_t)(x)) & ~(0x1F))

#define OSRoundUp(x, align) (((x) + (align)-1) & (-(align)))
#define OSRoundUpPtr(x, align) ((void*)((((u32)(x)) + (align)-1) & (~((align)-1))))

#define OSRoundDown(x, align) ((x) & (-(align)))
#define OSRoundDownPtr(x, align) ((void*)(((u32)(x)) & (~((align)-1))))

void OSInit();

OSTime OSGetTime();
OSTick OSGetTick();

typedef struct OSCalendarTime {
    int sec; // seconds after the minute [0, 61]
    int min; // minutes after the hour [0, 59]
    int hour; // hours since midnight [0, 23]
    int mday; // day of the month [1, 31]
    int mon; // month since January [0, 11]
    int year; // years in AD [1, ...]
    int wday; // days since Sunday [0, 6]
    int yday; // days since January 1 [0, 365]

    int msec; // milliseconds after the second [0,999]
    int usec; // microseconds after the millisecond [0,999]
} OSCalendarTime;

OSTime OSCalendarTimeToTicks(OSCalendarTime *td);
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime *td);

typedef struct OSStopwatch {
    char *name;
    OSTime total;
    u32 hits;
    OSTime min;
    OSTime max;
    OSTime last;
    BOOL running;
} OSStopwatch;

void OSInitStopwatch(OSStopwatch *sw, char *name);
void OSStartStopwatch(OSStopwatch *sw);
void OSStopStopwatch(OSStopwatch *sw);
OSTime OSCheckStopwatch(OSStopwatch *sw);
void OSResetStopwatch(OSStopwatch *sw);
void OSDumpStopwatch(OSStopwatch *sw);

#define OS_CONSOLE_MASK 0xf0000000
#define OS_CONSOLE_RETAIL 0x00000000
#define OS_CONSOLE_DEVELOPMENT 0x10000000
#define OS_CONSOLE_TDEV 0x20000000

#define OS_CONSOLE_RETAIL4 0x00000004
#define OS_CONSOLE_RETAIL3 0x00000003
#define OS_CONSOLE_RETAIL2 0x00000002
#define OS_CONSOLE_RETAIL1 0x00000001
#define OS_CONSOLE_TDEVHW4 0x20000007
#define OS_CONSOLE_TDEVHW3 0x20000006
#define OS_CONSOLE_TDEVHW2 0x20000005
#define OS_CONSOLE_TDEVHW1 0x20000004
#define OS_CONSOLE_DEVHW4 0x10000007
#define OS_CONSOLE_DEVHW3 0x10000006
#define OS_CONSOLE_DEVHW2 0x10000005
#define OS_CONSOLE_DEVHW1 0x10000004
#define OS_CONSOLE_MINNOW 0x10000003
#define OS_CONSOLE_ARTHUR 0x10000002
#define OS_CONSOLE_PC_EMULATOR 0x10000001
#define OS_CONSOLE_EMULATOR 0x10000000

u32 OSGetConsoleType();

#define OS_SOUND_MODE_MONO 0u
#define OS_SOUND_MODE_STEREO 1u

u32 OSGetSoundMode(void);
void OSSetSoundMode(u32 mode);

#define OS_PROGRESSIVE_MODE_OFF 0u
#define OS_PROGRESSIVE_MODE_ON 1u

u32 OSGetProgressiveMode(void);
void OSSetProgressiveMode(u32 on);

#define OS_LANG_ENGLISH 0u
#define OS_LANG_GERMAN 1u
#define OS_LANG_FRENCH 2u
#define OS_LANG_SPANISH 3u
#define OS_LANG_ITALIAN 4u
#define OS_LANG_DUTCH 5u

u8 OSGetLanguage(void);
void OSSetLanguage(u8 language);

#define OS_EURGB60_OFF 0u
#define OS_EURGB60_ON 1u

u32 OSGetEuRgb60Mode(void);
void OSSetEuRgb60Mode(u32 on);

void OSRegisterVersion(const char *id);

BOOL OSDisableInterrupts(void);
BOOL OSEnableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);

#define OSHalt(msg) OSPanic(__FILE__, __LINE__, msg)

#ifdef _DEBUG

#ifndef ASSERT
#define ASSERT(exp) (void)((exp) || (OSPanic(__FILE__, __LINE__, "Failed assertion " #exp), 0))
#endif

#ifndef ASSERTMSG
#if defined(__STDC_VERSION__) && (199901L <= __STDC_VERSION__) || defined(__MWERKS__) || defined(__SN__)
#define ASSERTMSG(exp, ...) (void)((exp) || (OSPanic(__FILE__, __LINE__, __VA_ARGS__), 0))
#else
#define ASSERTMSG(exp, msg) (void)((exp) || (OSPanic(__FILE__, __LINE__, (msg)), 0))
#endif
#endif

#ifndef ASSERTMSG1
#define ASSERTMSG1(exp, msg, param1) (void)((exp) || (OSPanic(__FILE__, __LINE__, (msg), (param1)), 0))
#endif

#ifndef ASSERTMSG2
#define ASSERTMSG2(exp, msg, param1, param2) (void)((exp) || (OSPanic(__FILE__, __LINE__, (msg), (param1), (param2)), 0))
#endif

#ifndef ASSERTMSG3
#define ASSERTMSG3(exp, msg, param1, param2, param3) (void)((exp) || (OSPanic(__FILE__, __LINE__, (msg), (param1), (param2), (param3)), 0))
#endif

#ifndef ASSERTMSG4
#define ASSERTMSG4(exp, msg, param1, param2, param3, param4)                                                                                         \
    (void)((exp) || (OSPanic(__FILE__, __LINE__, (msg), (param1), (param2), (param3), (param4)), 0))
#endif

#else // _DEBUG

#ifndef ASSERT
#define ASSERT(exp) ((void)0)
#endif

#ifndef ASSERTMSG
#if defined(__STDC_VERSION__) && (199901L <= __STDC_VERSION__) || defined(__MWERKS__) || defined(__SN__)
#define ASSERTMSG(exp, ...) ((void)0)
#else
#define ASSERTMSG(exp, msg) ((void)0)
#endif
#endif

#ifndef ASSERTMSG1
#define ASSERTMSG1(exp, msg, param1) ((void)0)
#endif
#ifndef ASSERTMSG2
#define ASSERTMSG2(exp, msg, param1, param2) ((void)0)
#endif
#ifndef ASSERTMSG3
#define ASSERTMSG3(exp, msg, param1, param2, param3) ((void)0)
#endif
#ifndef ASSERTMSG4
#define ASSERTMSG4(exp, msg, param1, param2, param3, param4) ((void)0)
#endif

#endif // _DEBUG

__declspec(dllexport) void OSReport(const char *msg, ...);
void OSPanic(const char *file, int line, const char *msg, ...);
void OSFatal(GXColor fg, GXColor bg, const char *msg);

u32 OSGetPhysicalMemSize(void);
u32 OSGetConsoleSimulatedMemSize(void);

#ifdef __cplusplus
}
#endif

#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSAlloc.h>
#include <dolphin/os/OSArena.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSException.h>
#include <dolphin/os/OSExpansion.h>
#include <dolphin/os/OSFastCast.h>
#include <dolphin/os/OSFont.h>
#include <dolphin/os/OSIC.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSMemory.h>
#include <dolphin/os/OSMessage.h>
#include <dolphin/os/OSModule.h>
#include <dolphin/os/OSMutex.h>
#include <dolphin/os/OSReset.h>
#include <dolphin/os/OSResetSW.h>
#include <dolphin/os/OSSerial.h>
#include <dolphin/os/OSThread.h>
#endif // _DOLPHIN_OS
