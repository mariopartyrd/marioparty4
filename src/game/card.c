#include "dolphin.h"
#include "game/memory.h"
#include "game/card.h"

static void *cardWork;
u8 UnMountCnt;

static void MountCallBack(s32 chan, s32 result);

void HuCardInit(void)
{
	CARDInit();
	cardWork = HuMemDirectMalloc(HEAP_SYSTEM, CARD_WORKAREA_SIZE);
}

s32 HuCardCheck(void)
{
	s32 ret = 0;
	s32 memSize, sectorSize;
	s32 result;
	do {
		result = CARDProbeEx(0, &memSize, &sectorSize);
	} while(result == CARD_RESULT_BUSY);
	if(result == CARD_RESULT_READY) {
		ret |= 1;
		OSReport("SlotA Card MemSize %x,Sector Size %x\n", memSize, sectorSize);
		HuCardMount(0);
	}
	do {
		result = CARDProbeEx(1, &memSize, &sectorSize);
	} while(result == CARD_RESULT_BUSY);
	if(result == CARD_RESULT_READY) {
		ret |= 2;
		OSReport("SlotB Card MemSize %x,Sector Size %x\n", memSize, sectorSize);
		HuCardMount(1);
	}
	return ret;
}

s32 HuCardSlotCheck(s16 slot)
{
	s32 memSize, sectorSize;
	s32 result;
	do {
		result = CARDProbeEx(slot, &memSize, &sectorSize);
	} while(result == CARD_RESULT_BUSY);
	if(result < 0) {
		return result;
	} else {
		return sectorSize;
	}
}

s32 HuCardMount(s16 slot)
{
	s32 memSize, sectorSize;
	s32 result;
	do {
		result = CARDProbeEx(slot, &memSize, &sectorSize);
	} while(result == CARD_RESULT_BUSY);
	if(result < 0) {
		return result;
	} else {
		result = CARDMount(slot, cardWork, MountCallBack);
		if(result == CARD_RESULT_FATAL_ERROR || result == CARD_RESULT_IOERROR) {
			return CARD_RESULT_FATAL_ERROR;
		}
		if(result == CARD_RESULT_ENCODING) {
			return CARD_RESULT_BROKEN;
		}
		if(result < 0 && result != CARD_RESULT_BROKEN) {
			return result;
		}
		result = CARDCheck(slot);
		if(result == CARD_RESULT_FATAL_ERROR || result == CARD_RESULT_IOERROR) {
			return CARD_RESULT_FATAL_ERROR;
		}
		if(result == CARD_RESULT_ENCODING) {
			return CARD_RESULT_BROKEN;
		}
		return result;
	}
}

void HuCardUnMount(s16 slot)
{
	CARDUnmount(slot);
}

s32 HuCardFormat(s16 slot)
{
	s32 result = CARDFormat(slot);
	if(result == CARD_RESULT_FATAL_ERROR || result == CARD_RESULT_IOERROR) {
		return CARD_RESULT_FATAL_ERROR;
	}
	return result;
}

static void MountCallBack(s32 chan, s32 result)
{
	#if VERSION_ENG
	UnMountCnt = (1 << chan);
	#else
	UnMountCnt |= (1 << chan);
	#endif
}

s32 HuCardOpen(s16 slot, const char *fileName, CARDFileInfo *fileInfo)
{
	s32 result = CARDOpen(slot, fileName, fileInfo);
	if(result == CARD_RESULT_FATAL_ERROR || result == CARD_RESULT_IOERROR) {
		return CARD_RESULT_FATAL_ERROR;
	}
	if(result == CARD_RESULT_ENCODING) {
		return CARD_RESULT_BROKEN;
	}
	return result;
}

s32 HuCardRead(CARDFileInfo *fileInfo, void *addr, s32 length, s32 offset)
{
	s32 result = CARDRead(fileInfo, addr, length, offset);
	if(result == CARD_RESULT_FATAL_ERROR || result == CARD_RESULT_IOERROR) {
		return CARD_RESULT_FATAL_ERROR;
	}
	return result;
}

s32 HuCardCreate(s16 slot, const char *fileName, s32 size, CARDFileInfo *fileInfo)
{
	s32 sectorSize;
	s32 byteNotUsed, filesNotUsed;
	s32 result;
	result = CARDGetSectorSize(slot, (u32 *)&sectorSize);
	if(result == CARD_RESULT_FATAL_ERROR || result == CARD_RESULT_NOCARD) {
		return result;
	}
	if(size % sectorSize) {
		size = sectorSize*(size+((sectorSize-1)/sectorSize));
	}
	result = CARDFreeBlocks(slot, &byteNotUsed, &filesNotUsed);
	if(result != 0) {
		return result;
	}
	if(filesNotUsed <= 0 || byteNotUsed < size) {
		return CARD_RESULT_INSSPACE;
	}
	result = CARDCreate(slot, fileName, size, fileInfo);
	return result;
}

s32 HuCardClose(CARDFileInfo *fileInfo)
{
	s32 result = CARDClose(fileInfo);
	return result;
}

s32 HuCardWrite(CARDFileInfo *fileInfo, const void *addr, s32 length, s32 offset)
{
	s32 result = CARDWrite(fileInfo, addr, length, offset);
	return result;
}

s32 HuCardDelete(s16 slot, const char *fileName)
{
	s32 result = CARDDelete(slot, fileName);
	return result;
}

s32 HuCardSectorSizeGet(s16 slot)
{
	u32 sectorSize;
	s32 result = CARDGetSectorSize(slot, &sectorSize);
	if(result < 0) {
		return result;
	} else {
		return sectorSize;
	}
}

s32 HuCardFreeSpaceGet(s16 slot, u32 *byteNotUsed, u32 *filesNotUsed)
{
	s32 result = CARDFreeBlocks(slot, (s32 *)byteNotUsed, (s32 *)filesNotUsed);
	return result;
}