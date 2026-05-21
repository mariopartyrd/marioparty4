#ifndef _GAME_DATA_H
#define _GAME_DATA_H

#include "game/dvd.h"

#include "datadir_enum.h"

#define DATA_DECODE_NONE 0
#define DATA_DECODE_LZ 1
#define DATA_DECODE_SLIDE 2
#define DATA_DECODE_FSLIDE_ALT 3
#define DATA_DECODE_FSLIDE 4
#define DATA_DECODE_RLE 5

#define DATA_NUM_LISTEND -1U
#define HU_DATANUM_NONE -1
#define HU_DATA_STAT_NONE -1

#include "dolphin/types.h"


struct HuDataStat_s {
    s32 dirId;
    void *dirP;
    void *fileDataP;
    u32 rawLen;
    u32 decodeType;
    BOOL used;
    s32 num;
    u32 status;
    DVDFileInfo dvdFile;
};

void HuDataInit(void);
s32 HuDataReadChk(s32 dirNum);
HUDATASTAT *HuDataGetStatus(void *dirP);
void *HuDataGetDirPtr(s32 dirNum);
HUDATASTAT *HuDataDirRead(s32 dataNum);
HUDATASTAT *HuDataDirSet(void *dirP, s32 dataNum);
void HuDataDirReadAsyncCallBack(s32 result, DVDFileInfo* fileInfo);
s32 HuDataDirReadAsync(s32 dataNum);
s32 HuDataDirReadNumAsync(s32 dataNum, s32 num);
BOOL HuDataGetAsyncStat(s32 statId);
void *HuDataRead(s32 dataNum);
void *HuDataReadNum(s32 dataNum, s32 num);
void *HuDataSelHeapRead(s32 dataNum, HeapID heap);
void *HuDataSelHeapReadNum(s32 dataNum, s32 num, HeapID heap);
void **HuDataReadMulti(s32 *dataNum);
s32 HuDataGetSize(s32 dataNum);
void HuDataClose(void *ptr);
void HuDataCloseMulti(void **ptrs);
void HuDataDirClose(s32 dataNum);
void HuDataDirCloseNum(s32 num);
void *HuDataReadNumHeapShortForce(s32 dataNum, s32 num, HeapID heap);

void HuDecodeData(void *src, void *dst, u32 size, s32 decodeType);

extern u32 DirDataSize;

#endif
