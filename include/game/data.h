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

#include "dolphin/types.h"


struct data_read_stat {
    s32 dir_id;
    void *dir;
    void *file;
    u32 raw_len;
    u32 comp_type;
    BOOL used;
    s32 num;
    u32 status;
    DVDFileInfo file_info;
};

void HuDataInit(void);
s32 HuDataReadChk(s32 data_num);
DataReadStat *HuDataGetStatus(void *dir_ptr);
void *HuDataGetDirPtr(s32 data_num);
DataReadStat *HuDataDirRead(s32 data_num);
DataReadStat *HuDataDirReadNum(s32 data_num, s32 num);
DataReadStat *HuDataDirSet(void *dir_ptr, s32 data_num);
void HuDataDirReadAsyncCallBack(s32 result, DVDFileInfo* fileInfo);
s32 HuDataDirReadAsync(s32 data_num);
s32 HuDataDirReadNumAsync(s32 data_num, s32 num);
BOOL HuDataGetAsyncStat(s32 status);
void *HuDataRead(s32 data_num);
void *HuDataReadNum(s32 data_num, s32 num);
void *HuDataSelHeapRead(s32 data_num, HeapID heap);
void *HuDataSelHeapReadNum(s32 data_num, s32 num, HeapID heap);
void **HuDataReadMulti(s32 *data_ids);
s32 HuDataGetSize(s32 data_num);
void HuDataClose(void *ptr);
void HuDataCloseMulti(void **ptrs);
void HuDataDirClose(s32 data_id);
void HuDataDirCloseNum(s32 num);
void *HuDataReadNumHeapShortForce(s32 data_id, s32 num, HeapID heap);

void HuDecodeData(void *src, void *dst, u32 size, s32 decode_type);

extern u32 DirDataSize;

#endif
