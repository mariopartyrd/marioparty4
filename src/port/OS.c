#include <stdio.h>
#include <stdlib.h>

#include <dolphin.h>

// Credits: Super Monkey Ball

#define MEM_SIZE (64 * 1024 * 1024)

u8 LC_CACHE_BASE[4096];

void OSInit()
{
    puts("OSInit is a stub");
    u8 *arena = malloc(MEM_SIZE);

    OSSetArenaLo(arena);
    OSSetArenaHi(arena + MEM_SIZE);
}

OSTime OSGetTime(void)
{
    return 0;
}

OSTick OSGetTick(void)
{
    return 0;
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
