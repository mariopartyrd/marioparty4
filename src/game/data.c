#include "game/data.h"
#include "game/armem.h"
#include "game/process.h"
#include "dolphin/dvd.h"

#define PTR_OFFSET(ptr, offset) (void *)(((u8 *)(ptr)+(u32)(offset)))
#define DATA_EFF_SIZE(size) (((size)+1) & ~0x1)

void **HuDataReadMultiSub(s32 *data_ids, BOOL use_num, s32 num);

#define DATA_MAX_READSTAT 128

#define DATADIR_DEFINE(name, path) { path, -1 },

static FileListEntry DataDirStat[] = {
    #include "datadir_table.h"
    { NULL, -1 }
};

#undef DATADIR_DEFINE

u32 DirDataSize;
static u32 DataDirMax;
static s32 shortAccessSleep;
static DataReadStat ATTRIBUTE_ALIGN(32) ReadDataStat[DATA_MAX_READSTAT];

void HuDataInit(void)
{
    s32 i = 0;
    FileListEntry *dir_stat = DataDirStat;
    DataReadStat *read_stat;
    while(dir_stat->name) {
        if((dir_stat->file_id = DVDConvertPathToEntrynum(dir_stat->name)) == -1) {
            OSReport("data.c: Data File Error(%s)\n", dir_stat->name);
            OSPanic("data.c", 65, "\n");
        }
        i++;
        dir_stat++;
    }
    DataDirMax = i;
    for(i=0, read_stat = ReadDataStat; i<DATA_MAX_READSTAT; i++, read_stat++) {
        read_stat->dir_id = -1;
        read_stat->used = FALSE;
        read_stat->status = 0;
    }
}

static s32 HuDataReadStatusGet(void)
{
    s32 i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dir_id == -1) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        i = -1;
    }
    return i;
}

s32 HuDataReadChk(s32 data_num)
{
    s32 i;
    data_num >>= 16;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dir_id == data_num && ReadDataStat[i].status != 1) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        i = -1;
    }
    return i;
}

DataReadStat *HuDataGetStatus(void *dir_ptr)
{
    s32 i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dir == dir_ptr) {
            break;
        }
    }
    if(i > DATA_MAX_READSTAT) {
        return NULL;
    }
    return &ReadDataStat[i];
}

void *HuDataGetDirPtr(s32 data_num)
{
    s32 status = HuDataReadChk(data_num);
    if(status < 0) {
        return NULL;
    }
    return ReadDataStat[status].dir;
}

DataReadStat *HuDataDirRead(s32 data_num)
{
    DataReadStat *read_stat;
    s32 status;
    s32 dir_id;
    dir_id  = data_num >> 16;
    if(DataDirMax <= dir_id) {
        OSReport("data.c: Data Number Error(%d)\n", data_num);
        return NULL;
    }
    
    if((status = HuDataReadChk(data_num)) < 0) {
        u32 dir_aram;
        if(dir_aram = HuARDirCheck(data_num)) {
            HuAR_ARAMtoMRAM(dir_aram);
            while(HuARDMACheck());
            status = HuDataReadChk(data_num);
            read_stat = &ReadDataStat[status];
        } else {
            if((status = HuDataReadStatusGet()) == -1) {
                OSReport("data.c: Data Work Max Error\n");
                return NULL;
            }
            read_stat = &ReadDataStat[status];
            read_stat->dir = HuDvdDataFastRead(DataDirStat[dir_id].file_id);
            if(read_stat->dir) {
                read_stat->dir_id = dir_id;
            }
        }
    } else {
        read_stat = &ReadDataStat[status];
    }
    return read_stat;
}

static DataReadStat *HuDataDirReadNum(s32 data_num, s32 num)
{
    DataReadStat *read_stat;
    s32 status;
    s32 dir_id;
    dir_id  = data_num >> 16;
    if(DataDirMax <= dir_id) {
        OSReport("data.c: Data Number Error(%d)\n", data_num);
        return NULL;
    }
    
    if((status = HuDataReadChk(data_num)) < 0) {
        u32 dir_aram;
        if((dir_aram = HuARDirCheck(data_num))) {
            OSReport("ARAM data num %x\n", data_num);
            HuAR_ARAMtoMRAMNum(dir_aram, num);
            while(HuARDMACheck());
            status = HuDataReadChk(data_num);
            read_stat = &ReadDataStat[status];
            read_stat->used = TRUE;
            read_stat->num = num;
        } else {
            OSReport("data num %x\n", data_num);
            if((status = HuDataReadStatusGet()) == -1) {
                OSReport("data.c: Data Work Max Error\n");
                return NULL;
            }
            read_stat = &ReadDataStat[status];
            read_stat->dir = HuDvdDataFastReadNum(DataDirStat[dir_id].file_id, num);
            if(read_stat->dir) {
                read_stat->dir_id = dir_id;
                read_stat->used = TRUE;
                read_stat->num = num;
            }
        }
    } else {
        read_stat = &ReadDataStat[status];
    }
    return read_stat;
}

DataReadStat *HuDataDirSet(void *dir_ptr, s32 data_num)
{
    DataReadStat *read_stat = HuDataGetStatus(dir_ptr);
    s32 status;
    if((status = HuDataReadChk(read_stat->dir_id << 16)) >= 0) {
        HuDataDirClose(data_num);
    }
    if((status = HuDataReadStatusGet()) == -1) {
        OSReport("data.c: Data Work Max Error\n");
        return NULL;
    } else {
        read_stat = &ReadDataStat[status];
        read_stat->dir = dir_ptr;
        read_stat->dir_id = data_num >>16;
        return read_stat;
    }
}

void HuDataDirReadAsyncCallBack(s32 result, DVDFileInfo* fileInfo)
{
    DataReadStat *read_stat;
    s32 i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].status == 1 && ReadDataStat[i].file_info.startAddr == fileInfo->startAddr) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        OSPanic("data.c", 358, "dvd.c AsyncCallBack Error");
    }
    read_stat = &ReadDataStat[i];
    read_stat->status = 0;
    DVDClose(&read_stat->file_info);
}

s32 HuDataDirReadAsync(s32 data_num)
{
    DataReadStat *read_stat;
    s32 status;
    s32 dir_id;
    dir_id  = data_num >> 16;
    if(DataDirMax <= dir_id) {
        OSReport("data.c: Data Number Error(%d)\n", data_num);
        return -1;
    }
    if((status = HuDataReadChk(data_num)) < 0) {
        u32 dir_aram;
        if(dir_aram = HuARDirCheck(data_num)) {
            OSReport("ARAM data num %x\n", data_num);
            HuAR_ARAMtoMRAM(dir_aram);
            status = 0x10000;
        } else {
            status = HuDataReadStatusGet();
            if(status == -1) {
                OSReport("data.c: Data Work Max Error\n");
                return -1;
            }
            read_stat = &ReadDataStat[status];
            read_stat->status = 1;
            read_stat->dir_id = dir_id;
            read_stat->dir = HuDvdDataFastReadAsync(DataDirStat[dir_id].file_id, read_stat);
        }
    } else {
        status = -1;
    }
    return status;
}

s32 HuDataDirReadNumAsync(s32 data_num, s32 num)
{
    DataReadStat *read_stat;
    s32 status;
    s32 dir_id;
    dir_id  = data_num >> 16;
    if(DataDirMax <= dir_id) {
        OSReport("data.c: Data Number Error(%d)\n", data_num);
        return -1;
    }
    if((status = HuDataReadChk(data_num)) < 0) {
        if((status = HuDataReadStatusGet()) == -1) {
            OSReport("data.c: Data Work Max Error\n");
            return -1;
        }
        ReadDataStat[status].status = TRUE;
        ReadDataStat[status].dir_id = dir_id;
        read_stat = &ReadDataStat[status];
        read_stat->used = TRUE;
        read_stat->num = num;
        read_stat->dir = HuDvdDataFastReadAsync(DataDirStat[dir_id].file_id, read_stat);
    } else {
        status = -1;
    }
    return status;
}

BOOL HuDataGetAsyncStat(s32 status)
{
    if(status == 0x10000) {
        return HuARDMACheck() == 0;
    } else {
        return ReadDataStat[status].status == 0;
    }
}

static void GetFileInfo(DataReadStat *read_stat, s32 file_num)
{
    u32 *temp_ptr;
    temp_ptr = (u32 *)PTR_OFFSET(read_stat->dir, (file_num * 4))+1;
#ifdef TARGET_PC
    byteswap_u32(temp_ptr);
#endif
    read_stat->file = PTR_OFFSET(read_stat->dir, *temp_ptr);
    temp_ptr = read_stat->file;
    read_stat->raw_len = *temp_ptr++;
    read_stat->comp_type = *temp_ptr++;
    read_stat->file = temp_ptr;
#ifdef TARGET_PC
    byteswap_u32(&read_stat->raw_len);
    byteswap_u32(&read_stat->comp_type);
#endif
}

void *HuDataRead(s32 data_num)
{
    DataReadStat *read_stat;
    s32 status;
    void *buf;
    if(!HuDataDirRead(data_num)) {
        (void)data_num;
        return NULL;
    }
    if((status = HuDataReadChk(data_num)) == -1) {
        return NULL;
    }
    read_stat = &ReadDataStat[status];
    GetFileInfo(read_stat, data_num & 0xFFFF);
    buf = HuMemDirectMalloc(0, DATA_EFF_SIZE(read_stat->raw_len));
    if(buf) {
        HuDecodeData(read_stat->file, buf, read_stat->raw_len, read_stat->comp_type);
    }
    return buf;
}

void *HuDataReadNum(s32 data_num, s32 num)
{
    DataReadStat *read_stat;
    s32 status;
    void *buf;
    if(!HuDataDirReadNum(data_num, num)) {
        return NULL;
    }
    if((status = HuDataReadChk(data_num)) == -1) {
        return NULL;
    }
    read_stat = &ReadDataStat[status];
    GetFileInfo(read_stat, data_num & 0xFFFF);
    buf = HuMemDirectMallocNum(0, DATA_EFF_SIZE(read_stat->raw_len), num);
    if(buf) {
        HuDecodeData(read_stat->file, buf, read_stat->raw_len, read_stat->comp_type);
    }
    return buf;
}

void *HuDataSelHeapRead(s32 data_num, HeapID heap)
{
    DataReadStat *read_stat;
    s32 status;
    void *buf;
    if(!HuDataDirRead(data_num)) {
        return NULL;
    }
    if((status = HuDataReadChk(data_num)) == -1) {
        return NULL;
    }
    read_stat = &ReadDataStat[status];
    GetFileInfo(read_stat, data_num & 0xFFFF);
    switch(heap) {
        case HEAP_MUSIC:
            buf = HuMemDirectMalloc(HEAP_MUSIC, DATA_EFF_SIZE(read_stat->raw_len));
            break;
            
        case HEAP_DATA:
            buf = HuMemDirectMalloc(HEAP_DATA, DATA_EFF_SIZE(read_stat->raw_len));
            break;
            
        case HEAP_DVD:
            buf = HuMemDirectMalloc(HEAP_DVD, DATA_EFF_SIZE(read_stat->raw_len));
            break;
            
        default:
            buf = HuMemDirectMalloc(HEAP_SYSTEM, DATA_EFF_SIZE(read_stat->raw_len));
            break;
    }
    if(buf) {
        HuDecodeData(read_stat->file, buf, read_stat->raw_len, read_stat->comp_type);
    }
    return buf;
}

void *HuDataSelHeapReadNum(s32 data_num, s32 num, HeapID heap)
{
    DataReadStat *read_stat;
    s32 status;
    void *buf;
    if(!HuDataDirReadNum(data_num, num)) {
        return NULL;
    }
    if((status = HuDataReadChk(data_num)) == -1) {
        return NULL;
    }
    read_stat = &ReadDataStat[status];
    GetFileInfo(read_stat, data_num & 0xFFFF);
    switch(heap) {
        case HEAP_MUSIC:
            buf = HuMemDirectMalloc(HEAP_MUSIC, DATA_EFF_SIZE(read_stat->raw_len));
            break;
            
        case HEAP_DATA:
            buf = HuMemDirectMallocNum(HEAP_DATA, DATA_EFF_SIZE(read_stat->raw_len), num);
            break;
            
        case HEAP_DVD:
            buf = HuMemDirectMallocNum(HEAP_DVD, DATA_EFF_SIZE(read_stat->raw_len), num);
            break;
            
        default:
            buf = HuMemDirectMallocNum(HEAP_SYSTEM, DATA_EFF_SIZE(read_stat->raw_len), num);
            break;
    }
    if(buf) {
        HuDecodeData(read_stat->file, buf, read_stat->raw_len, read_stat->comp_type);
    }
    return buf;
}

void **HuDataReadMulti(s32 *data_ids)
{
    return HuDataReadMultiSub(data_ids, FALSE, 0);
}

void **HuDataReadMultiSub(s32 *data_ids, BOOL use_num, s32 num)
{
    s32 *dir_ids;
    char **paths;
    void **dir_ptrs;
    void **out_ptrs;
    s32 i, count, total_files;
    u32 dir_id;
    for(i=0, count=0; data_ids[i] != -1; i++) {
        dir_id = data_ids[i] >> 16;
        if(DataDirMax <= dir_id) {
            OSReport("data.c: Data Number Error(%d)\n", data_ids[i]);
            return NULL;
        }
        if(HuDataReadChk(data_ids[i]) < 0) {
            count++;
        }
    }
    total_files = i;
    dir_ids = HuMemDirectMalloc(HEAP_SYSTEM, (count+1)*sizeof(s32));
    for(i=0; i<count+1; i++) {
        dir_ids[i] = -1;
    }
    paths = HuMemDirectMalloc(HEAP_SYSTEM, (count+1)*sizeof(char *));
    for(i=0, count=0; data_ids[i] != -1; i++) {
        dir_id = data_ids[i] >> 16;
        if(HuDataReadChk(data_ids[i]) < 0) {
            s32 j;
            for(j=0; dir_ids[j] != -1; j++) {
                if(dir_ids[j] == dir_id){
                    break;
                }
            }
            if(dir_ids[j] == -1) {
                dir_ids[j] = dir_id;
                paths[count++] = DataDirStat[dir_id].name;
            }
        }
    }
    dir_ptrs = HuDvdDataReadMulti(paths);
    for(i=0; dir_ids[i] != -1; i++) {
        s32 status;
        if((status = HuDataReadStatusGet()) == -1) {
            OSReport("data.c: Data Work Max Error\n");
            (void)count; //HACK to match HuDataReadMultiSub
            HuMemDirectFree(dir_ids);
            HuMemDirectFree(paths);
            return NULL;
        } else {
            ReadDataStat[status].dir = dir_ptrs[i];
            ReadDataStat[status].dir_id = dir_ids[i];
        }
    }
    HuMemDirectFree(dir_ids);
    HuMemDirectFree(paths);
    HuMemDirectFree(dir_ptrs);
    if(use_num) {
        out_ptrs = HuMemDirectMallocNum(HEAP_SYSTEM, (total_files+1)*sizeof(void *), num);
    } else {
        out_ptrs = HuMemDirectMalloc(HEAP_SYSTEM, (total_files+1)*sizeof(void *));
    }
    for(i=0; data_ids[i] != -1; i++) {
        if(use_num) {
            out_ptrs[i] = HuDataReadNum(data_ids[i], num);
        } else {
            out_ptrs[i] = HuDataRead(data_ids[i]);
        }
    }
    out_ptrs[i] = NULL;
    return out_ptrs;
}

s32 HuDataGetSize(s32 data_num)
{
    DataReadStat *read_stat;
    s32 status;
    if((status = HuDataReadChk(data_num)) == -1) {
        return -1;
    }
    read_stat = &ReadDataStat[status];
    GetFileInfo(read_stat, data_num & 0xFFFF);
    return DATA_EFF_SIZE(read_stat->raw_len);
}

void HuDataClose(void *ptr)
{
    if(ptr) {
        HuMemDirectFree(ptr);
    }
}

void HuDataCloseMulti(void **ptrs)
{
    s32 i;
    for(i=0; ptrs[i]; i++) {
        void *ptr = ptrs[i];
        if(ptr) {
            HuMemDirectFree(ptr);
        }
    }
    if(ptrs) {
        HuMemDirectFree(ptrs);
    }
}

void HuDataDirClose(s32 data_id)
{
    DataReadStat *read_stat;
    s32 i;
    s32 dir_id = data_id >> 16;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dir_id == dir_id) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        return;
    }
    read_stat = &ReadDataStat[i];
    if(read_stat->status == 1) {
        OSPanic("data.c", 812, "data.c: Async Close Error\n");
    }
    read_stat->dir_id = -1;
    HuDvdDataClose(read_stat->dir);
    read_stat->dir = NULL;
    read_stat->used = FALSE;
    read_stat->status = 0;
}

void HuDataDirCloseNum(s32 num)
{
    s32 i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].used == TRUE && ReadDataStat[i].num == num) {
            HuDataDirClose(ReadDataStat[i].dir_id << 16);
        }
    }
}

static s32 HuDataDVDdirDirectOpen(s32 data_id, DVDFileInfo *fileInfo)
{
	s32 dir = data_id >> 16;
	if(dir >= (s32)DataDirMax) {
		OSReport("data.c: Data Number Error(0x%08x)\n", data_id);
		return 0;
	}
	if(!DVDFastOpen(DataDirStat[dir].file_id, fileInfo)) {
		char panic_str[48];
		sprintf(panic_str, "HuDataDVDdirDirectOpen: File Open Error(%08x)", data_id);
		OSPanic("data.c", 895, panic_str);
	}
	return 1;
}

static s32 HuDataDVDdirDirectRead(DVDFileInfo *fileInfo, void *dest, s32 len, s32 offset)
{
	s32 result = DVDReadAsync(fileInfo, dest, len, offset, NULL);
	if(result != 1) {
		OSPanic("data.c", 904, "HuDataDVDdirDirectRead: File Read Error");
	}
	while(DVDGetCommandBlockStatus(&fileInfo->cb)) {
		if(shortAccessSleep) {
			HuPrcVSleep();
		}
	}
	return result;
}

static void *HuDataDecodeIt(void *buf_start, s32 buf_ofs, s32 num, HeapID heap)
{
	void *data_start;
	s32 *buf;
	s32 raw_len, comp_type;
	
	void *dest;
	buf =  (s32 *)((u8 *)buf_start+buf_ofs);
	if((u32)buf & 0x3) {
		u8 *data = (u8 *)buf;
		raw_len = *data++ << 24;
		raw_len += *data++ << 16;
		raw_len += *data++ << 8;
		raw_len += *data++;
		comp_type = *data++ << 24;
		comp_type += *data++ << 16;
		comp_type += *data++ << 8;
		comp_type += *data++;
		data_start = data;
	} else {
		s32 *data = buf;
		raw_len = *data++;
		comp_type = *data++;
		data_start = data;
	}
	switch(heap) {
        case HEAP_MUSIC:
            dest = HuMemDirectMalloc(HEAP_MUSIC, DATA_EFF_SIZE(raw_len));
            break;
            
        case HEAP_DATA:
            dest = HuMemDirectMallocNum(HEAP_DATA, DATA_EFF_SIZE(raw_len), num);
            break;
            
        case HEAP_DVD:
            dest = HuMemDirectMallocNum(HEAP_DVD, DATA_EFF_SIZE(raw_len), num);
            break;
            
        default:
            dest = HuMemDirectMallocNum(HEAP_SYSTEM, DATA_EFF_SIZE(raw_len), num);
            break;
    }
    if(dest) {
        HuDecodeData(data_start, dest, raw_len, comp_type);
    }
    return dest;
}


//Still to be decompiled
void *HuDataReadNumHeapShortForce(s32 data_id, s32 num, HeapID heap)
{
	DVDFileInfo fileInfo;
	s32 *data_hdr;
	s32 *file_data;
	void *file_raw_buf;
	s32 read_len;
	s32 file_id;
	s32 file_ofs;
	s32 read_ofs;
	s32 data_ofs;
	void *ret;
	s32 dir;
	s32 data_len;
	s32 file_max;

	if(!HuDataDVDdirDirectOpen(data_id, &fileInfo)) {
		return NULL;
	}
	dir = (data_id >> 16) & 0xFFFF0000;
	file_id = data_id & 0xFFFF;
	file_ofs = (file_id*4)+4;
	data_len = OSRoundUp32B(file_ofs+8);
	file_data = HuMemDirectMalloc(HEAP_SYSTEM, data_len);
	if(!HuDataDVDdirDirectRead(&fileInfo, file_data, data_len, 0)) {
		HuMemDirectFree(file_data);
		DVDClose(&fileInfo);
		return NULL;
	}
	file_max = *file_data;
	if(file_max <= file_id) {
		HuMemDirectFree(file_data);
		OSReport("data.c%d: Data Number Error(0x%08x)\n", 1005, data_id);
		DVDClose(&fileInfo);
		return NULL;
	}
	data_hdr = file_data;
	data_hdr += file_id+1;
	file_ofs = *data_hdr;
	read_ofs = OSRoundDown32B(file_ofs);
	if(file_max <= file_id+1) {
		read_len = fileInfo.length;
		data_ofs = read_len-read_ofs;
	} else {
		data_hdr++;
		data_ofs = (*data_hdr)-read_ofs;
		read_len = fileInfo.length;
	}
	read_len = OSRoundUp32B(data_ofs);
	HuMemDirectFree(file_data);
	file_raw_buf = HuMemDirectMalloc(HEAP_SYSTEM, (read_len+4) & ~0x3);
	if(file_raw_buf == NULL) {
		OSReport("data.c: couldn't allocate read buffer(0x%08x)\n", data_id);
		DVDClose(&fileInfo);
		return NULL;
	}
	if(!HuDataDVDdirDirectRead(&fileInfo, file_raw_buf, read_len, read_ofs)) {
		HuMemDirectFree(file_raw_buf);
		DVDClose(&fileInfo);
		return NULL;
	}
	DVDClose(&fileInfo);
	data_ofs = file_ofs-read_ofs;
	ret = HuDataDecodeIt(file_raw_buf, data_ofs, num, heap);
	HuMemDirectFree(file_raw_buf);
    return ret;
}

char lbl_8011FDA6[] = "** dcnt %d tmp %08x sp1 %08x\n";
char lbl_8011FDC4[] = "** dcnt %d lastNum %08x\n";