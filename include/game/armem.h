#ifndef _GAME_ARMEM_H
#define _GAME_ARMEM_H

#include "dolphin.h"
#include "game/memory.h"
#include "game/data.h"

void HuARInit(void);
uintptr_t HuARMalloc(u32 size);
void HuARFree(uintptr_t amemptr);
void HuAMemDump(void);
uintptr_t HuAR_DVDtoARAM(u32 dir);
uintptr_t HuAR_MRAMtoARAM(s32 dir);
uintptr_t HuAR_MRAMtoARAM2(void *dir_ptr);
void HuAR_ARAMtoMRAM(uintptr_t amemptr);
void *HuAR_ARAMtoMRAMNum(uintptr_t amemptr, s32 num);
s32 HuARDMACheck(void);
uintptr_t HuARDirCheck(u32 dir);
void HuARDirFree(u32 dir);
void *HuAR_ARAMtoMRAMFileRead(u32 dir, u32 num, HeapID heap);

#endif
