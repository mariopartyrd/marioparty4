#ifndef _GAME_ARMEM_H
#define _GAME_ARMEM_H

#include "dolphin.h"
#include "game/memory.h"
#include "game/data.h"

#define HU_AMEM_BASE 0x808000

typedef u32 AMEM_PTR;

void HuARInit(void);
AMEM_PTR HuARMalloc(u32 size);
void HuARFree(AMEM_PTR amemptr);
void HuAMemDump(void);
AMEM_PTR HuAR_DVDtoARAM(u32 dir);
AMEM_PTR HuAR_MRAMtoARAM(s32 dir);
AMEM_PTR HuAR_MRAMtoARAM2(void *dir_ptr);
void HuAR_ARAMtoMRAM(AMEM_PTR amemptr);
void *HuAR_ARAMtoMRAMNum(AMEM_PTR amemptr, s32 num);
s32 HuARDMACheck(void);
AMEM_PTR HuARDirCheck(u32 dir);
void HuARDirFree(u32 dir);
void *HuAR_ARAMtoMRAMFileRead(u32 dir, u32 num, HeapID heap);

#endif
