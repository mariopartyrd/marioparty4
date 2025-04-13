#include <stdio.h>
#include <stdlib.h>

#include <dolphin.h>

#ifndef _WIN32
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#if __APPLE__
#include <mach/mach_time.h>
#endif
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#if __APPLE__
static u64 MachToDolphinNum;
static u64 MachToDolphinDenom;
#elif _WIN32
static LARGE_INTEGER PerfFrequency;
#endif

// Credits: Super Monkey Ball

#define MEM_SIZE (64 * 1024 * 1024)

u8 LC_CACHE_BASE[4096];

static u64 GetGCTicks()
{
#if __APPLE__
    return mach_absolute_time() * MachToDolphinNum / MachToDolphinDenom;
#elif __linux__ || __FreeBSD__
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);

    return ((tp.tv_sec * 1000000000ull) + tp.tv_nsec) * OS_CORE_CLOCK / 1000000000ull;
#elif _WIN32
    LARGE_INTEGER perf;
    QueryPerformanceCounter(&perf);
    perf.QuadPart *= OS_CORE_CLOCK;
    perf.QuadPart /= PerfFrequency.QuadPart;
    return perf.QuadPart;
#else
    return 0;
#endif
}

void OSInit()
{
    puts("OSInit is a stub");
    u8 *arena = malloc(MEM_SIZE);

    OSSetArenaLo(arena);
    OSSetArenaHi(arena + MEM_SIZE);

    #if __APPLE__
    mach_timebase_info_data_t timebase;
    mach_timebase_info(&timebase);
    MachToDolphinNum = OS_CORE_CLOCK * timebase.numer;
    MachToDolphinDenom = 1000000000ull * timebase.denom;
#elif _WIN32
    QueryPerformanceFrequency(&PerfFrequency);
#endif
}

OSTime OSGetTime(void)
{
    return (OSTime)GetGCTicks();
}

OSTick OSGetTick(void)
{
    return (OSTick)GetGCTicks();
}

u32 OSGetPhysicalMemSize(void)
{
    puts("OSGetPhysicalMemSize is a stub");
    return MEM_SIZE;
}

u32 OSGetConsoleSimulatedMemSize(void)
{
    puts("OSGetSimulatedMemSize is a stub");
    return MEM_SIZE;
}
