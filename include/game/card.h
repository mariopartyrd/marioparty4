#ifndef _GAME_CARD_H
#define _GAME_CARD_H

#include "dolphin.h"
#include "version.h"

SHARED_SYM extern u8 UnMountCnt;

void HuCardInit(void);
s32 HuCardCheck(void);
s32 HuCardSlotCheck(s16 slot);
s32 HuCardMount(s16 slot);
void HuCardUnMount(s16 slot);
s32 HuCardFormat(s16 slot);
s32 HuCardOpen(s16 slot, const char *fileName, CARDFileInfo *fileInfo);
s32 HuCardRead(CARDFileInfo *fileInfo, void *addr, s32 length, s32 offset);
s32 HuCardCreate(s16 slot, const char *fileName, s32 size, CARDFileInfo *fileInfo);
s32 HuCardClose(CARDFileInfo *fileInfo);
s32 HuCardWrite(CARDFileInfo *fileInfo, const void *addr, s32 length, s32 offset);
s32 HuCardDelete(s16 slot, const char *fileName);
s32 HuCardSectorSizeGet(s16 slot);
s32 HuCardFreeSpaceGet(s16 slot, u32 *byteNotUsed, u32 *filesNotUsed);

#endif