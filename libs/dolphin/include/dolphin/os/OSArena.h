#ifndef _DOLPHIN_OSARENA
#define _DOLPHIN_OSARENA

#include <dolphin/types.h>

void* OSGetArenaHi(void);
void* OSGetArenaLo(void);
void OSSetArenaHi(void* addr);
void OSSetArenaLo(void* addr);
void* OSAllocFromArenaLo(u32 size, u32 align);
void* OSAllocFromArenaLo(u32 size, u32 align);

#endif // _DOLPHIN_OSARENA
