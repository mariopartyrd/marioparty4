#ifndef _GAME_SAVELOAD_H
#define _GAME_SAVELOAD_H

#include "dolphin.h"
#include "game/gamework_data.h"

#define SAVE_BUF_SIZE 16384

typedef struct save_buf_data {
	u8 comment[CARD_COMMENT_SIZE];
	u8 banner[CARD_BANNER_WIDTH*CARD_BANNER_HEIGHT];
	u8 bannerTlut[512];
	u8 icon[CARD_ICON_WIDTH*CARD_ICON_HEIGHT*4];
	u8 iconTlut[512];
	GameStat stat;
	SystemState system;
	PlayerState player[4];
	SystemState systemStory;
	PlayerState playerStory[4];
} SaveBufData;

typedef union save_buf_all {
	SaveBufData data;
	u8 ATTRIBUTE_ALIGN(32) buf[SAVE_BUF_SIZE];
} SaveBufAll;

SHARED_SYM extern char *SaveFileNameTbl[];
SHARED_SYM extern CARDFileInfo curFileInfo;
SHARED_SYM extern SaveBufAll saveBuf;
extern u64 SLSerialNo;
extern s32 saveExecF;
extern u8 curBoxNo;
SHARED_SYM extern s16 curSlotNo;

s32 SLFileOpen(char *fileName);
s32 SLFileCreate(char *fileName, u32 size, void *addr);
s32 SLFileWrite(s32 length, void *addr);
s32 SLFileRead(s32 length, void *addr);
s32 SLFileClose(void);
void SLCurSlotNoSet(s16 slotno);
void SLCurBoxNoSet(s16 boxno);
void SLSaveFlagSet(s32 flag);
s32 SLSaveFlagGet(void);
void SLSaveDataMake(s32 erase, OSTime *time);
void SLSaveDataInfoSet(OSTime *time);
void SLCommonSet(void);
void SLSaveBoard(void);
void SLSaveBoardStory(void);
s32 SLSave(void);
s32 SLLoad(void);
void SLLoadGameStat(void);
void SLLoadBoard(void);
void SLLoadBoardStory(void);
s32 SLSerialNoGet(void);
BOOL SLSerialNoCheck(void);
BOOL SLCheckSumCheck(void);
u16 SLCheckSumGet(void);
void SLCheckSumSet(void);
s32 SLStatSet(s32 reportF);
s32 SLCardMount(s16 slotNo);
s32 SLFormat(s16 slotNo);
s16 SLMessOut(s16 mess);

#endif
