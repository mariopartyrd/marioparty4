#include "game/data.h"
#include "game/armem.h"
#include "game/process.h"
#include "dolphin/dvd.h"

#define STAT_ID_ARAM 0x10000

#define PTR_OFFSET(ptr, offset) (void *)(((u8 *)(ptr)+(u32)(offset)))
#define DATA_EFF_SIZE(size) (((size)+1) & ~0x1)

void **HuDataReadMultiSub(s32 *dataNum, BOOL use_num, s32 num);

#define DATA_MAX_READSTAT 128

#define DATADIR(name, path) { path, -1 },

static FileListEntry DataDirStat[] = {
    #include "datadir_table.h"
    { NULL, -1 }
};

#undef DATADIR

u32 DirDataSize;
static u32 DataDirMax;
static s32 shortAccessSleep;
static HUDATASTAT ATTRIBUTE_ALIGN(32) ReadDataStat[DATA_MAX_READSTAT];

void HuDataInit(void)
{
    s32 i = 0;
    FileListEntry *dir_stat = DataDirStat;
    HUDATASTAT *read_stat;
    while(dir_stat->name) {
        if((dir_stat->entryNum = DVDConvertPathToEntrynum(dir_stat->name)) == -1) {
            OSReport("data.c: Data File Error(%s)\n", dir_stat->name);
            OSPanic("data.c", 65, "\n");
        }
        i++;
        dir_stat++;
    }
    DataDirMax = i;
    for(i=0, read_stat = ReadDataStat; i<DATA_MAX_READSTAT; i++, read_stat++) {
        read_stat->dirId = -1;
        read_stat->used = FALSE;
        read_stat->status = 0;
    }
}

static s32 HuDataReadStatusGet(void)
{
    s32 i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dirId == -1) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        i = -1;
    }
    return i;
}

s32 HuDataReadChk(s32 dirNum)
{
    s32 i;
    dirNum >>= 16;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dirId == dirNum && ReadDataStat[i].status != 1) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        i = HU_DATA_STAT_NONE;
    }
    return i;
}

HUDATASTAT *HuDataGetStatus(void *dirP)
{
    s32 i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dirP == dirP) {
            break;
        }
    }
    if(i > DATA_MAX_READSTAT) {
        return NULL;
    }
    return &ReadDataStat[i];
}

void *HuDataGetDirPtr(s32 dirNum)
{
    s32 status = HuDataReadChk(dirNum);
    if(status < 0) {
        return NULL;
    }
    return ReadDataStat[status].dirP;
}

HUDATASTAT *HuDataDirRead(s32 dataNum)
{
    HUDATASTAT *readStat;
    s32 statId;
    s32 dirId;
    dirId  = dataNum >> 16;
    if(DataDirMax <= dirId) {
        OSReport("data.c: Data Number Error(%d)\n", dataNum);
        return NULL;
    }

    if((statId = HuDataReadChk(dataNum)) < 0) {
        AMEM_PTR dirAMemP;
        if(dirAMemP = HuARDirCheck(dataNum)) {
            HuAR_ARAMtoMRAM(dirAMemP);
            while(HuARDMACheck());
            statId = HuDataReadChk(dataNum);
            readStat = &ReadDataStat[statId];
        } else {
            if((statId = HuDataReadStatusGet()) == -1) {
                OSReport("data.c: Data Work Max Error\n");
                return NULL;
            }
            readStat = &ReadDataStat[statId];
            readStat->dirP = HuDvdDataFastRead(DataDirStat[dirId].entryNum);
            if(readStat->dirP) {
                readStat->dirId = dirId;
            }
        }
    } else {
        readStat = &ReadDataStat[statId];
    }
    return readStat;
}

static HUDATASTAT *HuDataDirReadNum(s32 dataNum, s32 num)
{
    HUDATASTAT *readStat;
    s32 statId;
    s32 dirId;
    dirId  = dataNum >> 16;
    if(DataDirMax <= dirId) {
        OSReport("data.c: Data Number Error(%d)\n", dataNum);
        return NULL;
    }

    if((statId = HuDataReadChk(dataNum)) < 0) {
        u32 dir_aram;
        if((dir_aram = HuARDirCheck(dataNum))) {
            OSReport("ARAM data num %x\n", dataNum);
            HuAR_ARAMtoMRAMNum(dir_aram, num);
            while(HuARDMACheck());
            statId = HuDataReadChk(dataNum);
            readStat = &ReadDataStat[statId];
            readStat->used = TRUE;
            readStat->num = num;
        } else {
            OSReport("data num %x\n", dataNum);
            if((statId = HuDataReadStatusGet()) == -1) {
                OSReport("data.c: Data Work Max Error\n");
                return NULL;
            }
            readStat = &ReadDataStat[statId];
            readStat->dirP = HuDvdDataFastReadNum(DataDirStat[dirId].entryNum, num);
            if(readStat->dirP) {
                readStat->dirId = dirId;
                readStat->used = TRUE;
                readStat->num = num;
            }
        }
    } else {
        readStat = &ReadDataStat[statId];
    }
    return readStat;
}

HUDATASTAT *HuDataDirSet(void *dirP, s32 dataNum)
{
    HUDATASTAT *readStat = HuDataGetStatus(dirP);
    s32 statId;
    if((statId = HuDataReadChk(readStat->dirId << 16)) >= 0) {
        HuDataDirClose(dataNum);
    }
    if((statId = HuDataReadStatusGet()) == -1) {
        OSReport("data.c: Data Work Max Error\n");
        return NULL;
    } else {
        readStat = &ReadDataStat[statId];
        readStat->dirP = dirP;
        readStat->dirId = dataNum >>16;
        return readStat;
    }
}

void HuDataDirReadAsyncCallBack(s32 result, DVDFileInfo* fileInfo)
{
    HUDATASTAT *readStat;
    s32 i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].status == 1 && ReadDataStat[i].dvdFile.startAddr == fileInfo->startAddr) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        OSPanic("data.c", 358, "dvd.c AsyncCallBack Error");
    }
    readStat = &ReadDataStat[i];
    readStat->status = 0;
    DVDClose(&readStat->dvdFile);
}

s32 HuDataDirReadAsync(s32 dataNum)
{
    HUDATASTAT *readstat;
    s32 statId;
    s32 dirId;
    dirId  = dataNum >> 16;
    if(DataDirMax <= dirId) {
        OSReport("data.c: Data Number Error(%d)\n", dataNum);
        return -1;
    }
    if((statId = HuDataReadChk(dataNum)) < 0) {
        u32 dir_aram;
        if(dir_aram = HuARDirCheck(dataNum)) {
            OSReport("ARAM data num %x\n", dataNum);
            HuAR_ARAMtoMRAM(dir_aram);
            statId = 0x10000;
        } else {
            statId = HuDataReadStatusGet();
            if(statId == -1) {
                OSReport("data.c: Data Work Max Error\n");
                return -1;
            }
            readstat = &ReadDataStat[statId];
            readstat->status = 1;
            readstat->dirId = dirId;
            readstat->dirP = HuDvdDataFastReadAsync(DataDirStat[dirId].entryNum, readstat);
        }
    } else {
        statId = -1;
    }
    return statId;
}

s32 HuDataDirReadNumAsync(s32 dataNum, s32 num)
{
    HUDATASTAT *readStat;
    s32 statId;
    s32 dirId;
    dirId  = dataNum >> 16;
    if(DataDirMax <= dirId) {
        OSReport("data.c: Data Number Error(%d)\n", dataNum);
        return -1;
    }
    if((statId = HuDataReadChk(dataNum)) < 0) {
        if((statId = HuDataReadStatusGet()) == -1) {
            OSReport("data.c: Data Work Max Error\n");
            return -1;
        }
        ReadDataStat[statId].status = TRUE;
        ReadDataStat[statId].dirId = dirId;
        readStat = &ReadDataStat[statId];
        readStat->used = TRUE;
        readStat->num = num;
        readStat->dirP = HuDvdDataFastReadAsync(DataDirStat[dirId].entryNum, readStat);
    } else {
        statId = -1;
    }
    return statId;
}

BOOL HuDataGetAsyncStat(s32 statId)
{
    if(statId == STAT_ID_ARAM) {
        return HuARDMACheck() == 0;
    } else {
        return ReadDataStat[statId].status == 0;
    }
}

static void GetFileInfo(HUDATASTAT *readStat, s32 fileNum)
{
    u32 *ptr;
    ptr = (u32 *)PTR_OFFSET(readStat->dirP, (fileNum * 4))+1;
    readStat->fileDataP = PTR_OFFSET(readStat->dirP, *ptr);
    ptr = readStat->fileDataP;
    readStat->rawLen = *ptr++;
    readStat->decodeType = *ptr++;
    readStat->fileDataP = ptr;
}

void *HuDataRead(s32 dataNum)
{
    HUDATASTAT *readStat;
    s32 statId;
    void *buf;
    if(!HuDataDirRead(dataNum)) {
        (void)dataNum;
        return NULL;
    }
    if((statId = HuDataReadChk(dataNum)) == -1) {
        return NULL;
    }
    readStat = &ReadDataStat[statId];
    GetFileInfo(readStat, dataNum & 0xFFFF);
    buf = HuMemDirectMalloc(0, DATA_EFF_SIZE(readStat->rawLen));
    if(buf) {
        HuDecodeData(readStat->fileDataP, buf, readStat->rawLen, readStat->decodeType);
    }
    return buf;
}

void *HuDataReadNum(s32 dataNum, s32 num)
{
    HUDATASTAT *readStat;
    s32 statId;
    void *buf;
    if(!HuDataDirReadNum(dataNum, num)) {
        return NULL;
    }
    if((statId = HuDataReadChk(dataNum)) == -1) {
        return NULL;
    }
    readStat = &ReadDataStat[statId];
    GetFileInfo(readStat, dataNum & 0xFFFF);
    buf = HuMemDirectMallocNum(0, DATA_EFF_SIZE(readStat->rawLen), num);
    if(buf) {
        HuDecodeData(readStat->fileDataP, buf, readStat->rawLen, readStat->decodeType);
    }
    return buf;
}

void *HuDataSelHeapRead(s32 dataNum, HeapID heap)
{
    HUDATASTAT *readStat;
    s32 statId;
    void *buf;
    if(!HuDataDirRead(dataNum)) {
        return NULL;
    }
    if((statId = HuDataReadChk(dataNum)) == -1) {
        return NULL;
    }
    readStat = &ReadDataStat[statId];
    GetFileInfo(readStat, dataNum & 0xFFFF);
    switch(heap) {
        case HEAP_SOUND:
            buf = HuMemDirectMalloc(HEAP_SOUND, DATA_EFF_SIZE(readStat->rawLen));
            break;

        case HEAP_MODEL:
            buf = HuMemDirectMalloc(HEAP_MODEL, DATA_EFF_SIZE(readStat->rawLen));
            break;

        case HEAP_DVD:
            buf = HuMemDirectMalloc(HEAP_DVD, DATA_EFF_SIZE(readStat->rawLen));
            break;

        default:
            buf = HuMemDirectMalloc(HEAP_HEAP, DATA_EFF_SIZE(readStat->rawLen));
            break;
    }
    if(buf) {
        HuDecodeData(readStat->fileDataP, buf, readStat->rawLen, readStat->decodeType);
    }
    return buf;
}

void *HuDataSelHeapReadNum(s32 dataNum, s32 num, HeapID heap)
{
    HUDATASTAT *readStat;
    s32 statId;
    void *buf;
    if(!HuDataDirReadNum(dataNum, num)) {
        return NULL;
    }
    if((statId = HuDataReadChk(dataNum)) == -1) {
        return NULL;
    }
    readStat = &ReadDataStat[statId];
    GetFileInfo(readStat, dataNum & 0xFFFF);
    switch(heap) {
        case HEAP_SOUND:
            buf = HuMemDirectMalloc(HEAP_SOUND, DATA_EFF_SIZE(readStat->rawLen));
            break;

        case HEAP_MODEL:
            buf = HuMemDirectMallocNum(HEAP_MODEL, DATA_EFF_SIZE(readStat->rawLen), num);
            break;

        case HEAP_DVD:
            buf = HuMemDirectMallocNum(HEAP_DVD, DATA_EFF_SIZE(readStat->rawLen), num);
            break;

        default:
            buf = HuMemDirectMallocNum(HEAP_HEAP, DATA_EFF_SIZE(readStat->rawLen), num);
            break;
    }
    if(buf) {
        HuDecodeData(readStat->fileDataP, buf, readStat->rawLen, readStat->decodeType);
    }
    return buf;
}

void **HuDataReadMulti(s32 *dataNum)
{
    return HuDataReadMultiSub(dataNum, FALSE, 0);
}

void **HuDataReadMultiSub(s32 *dataNum, BOOL use_num, s32 num)
{
    s32 *dirIds;
    char **pathTbl;
    void **dirP;
    void **outList;
    s32 i, count, numFiles;
    u32 dirId;
    for(i=0, count=0; dataNum[i] != HU_DATANUM_NONE; i++) {
        dirId = dataNum[i] >> 16;
        if(DataDirMax <= dirId) {
            OSReport("data.c: Data Number Error(%d)\n", dataNum[i]);
            return NULL;
        }
        if(HuDataReadChk(dataNum[i]) < 0) {
            count++;
        }
    }
    numFiles = i;
    dirIds = HuMemDirectMalloc(HEAP_HEAP, (count+1)*sizeof(s32));
    for(i=0; i<count+1; i++) {
        dirIds[i] = HU_DATANUM_NONE;
    }
    pathTbl = HuMemDirectMalloc(HEAP_HEAP, (count+1)*sizeof(char *));
    for(i=0, count=0; dataNum[i] != HU_DATANUM_NONE; i++) {
        dirId = dataNum[i] >> 16;
        if(HuDataReadChk(dataNum[i]) < 0) {
            s32 j;
            for(j=0; dirIds[j] != HU_DATANUM_NONE; j++) {
                if(dirIds[j] == dirId){
                    break;
                }
            }
            if(dirIds[j] == HU_DATANUM_NONE) {
                dirIds[j] = dirId;
                pathTbl[count++] = DataDirStat[dirId].name;
            }
        }
    }
    dirP = HuDvdDataReadMulti(pathTbl);
    for(i=0; dirIds[i] != HU_DATANUM_NONE; i++) {
        s32 status;
        if((status = HuDataReadStatusGet()) == HU_DATA_STAT_NONE) {
            OSReport("data.c: Data Work Max Error\n");
            (void)count; //HACK to match HuDataReadMultiSub
            HuMemDirectFree(dirIds);
            HuMemDirectFree(pathTbl);
            return NULL;
        } else {
            ReadDataStat[status].dirP = dirP[i];
            ReadDataStat[status].dirId = dirIds[i];
        }
    }
    HuMemDirectFree(dirIds);
    HuMemDirectFree(pathTbl);
    HuMemDirectFree(dirP);
    if(use_num) {
        outList = HuMemDirectMallocNum(HEAP_HEAP, (numFiles+1)*sizeof(void *), num);
    } else {
        outList = HuMemDirectMalloc(HEAP_HEAP, (numFiles+1)*sizeof(void *));
    }
    for(i=0; dataNum[i] != HU_DATANUM_NONE; i++) {
        if(use_num) {
            outList[i] = HuDataReadNum(dataNum[i], num);
        } else {
            outList[i] = HuDataRead(dataNum[i]);
        }
    }
    outList[i] = NULL;
    return outList;
}

s32 HuDataGetSize(s32 dataNum)
{
    HUDATASTAT *readStat;
    s32 statId;
    if((statId = HuDataReadChk(dataNum)) == HU_DATA_STAT_NONE) {
        return -1;
    }
    readStat = &ReadDataStat[statId];
    GetFileInfo(readStat, dataNum & 0xFFFF);
    return DATA_EFF_SIZE(readStat->rawLen);
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

void HuDataDirClose(s32 dataNum)
{
    HUDATASTAT *readStat;
    s32 i;
    s32 dirId = dataNum >> 16;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].dirId == dirId) {
            break;
        }
    }
    if(i >= DATA_MAX_READSTAT) {
        return;
    }
    readStat = &ReadDataStat[i];
    if(readStat->status == 1) {
        OSPanic("data.c", 812, "data.c: Async Close Error\n");
    }
    readStat->dirId = HU_DATANUM_NONE;
    HuDvdDataClose(readStat->dirP);
    readStat->dirP = NULL;
    readStat->used = FALSE;
    readStat->status = 0;
}

void HuDataDirCloseNum(s32 num)
{
    s32 i;
    for(i=0; i<DATA_MAX_READSTAT; i++) {
        if(ReadDataStat[i].used == TRUE && ReadDataStat[i].num == num) {
            HuDataDirClose(ReadDataStat[i].dirId << 16);
        }
    }
}

static s32 HuDataDVDdirDirectOpen(s32 dataNum, DVDFileInfo *fileInfo)
{
	s32 dir = dataNum >> 16;
	if(dir >= (s32)DataDirMax) {
		OSReport("data.c: Data Number Error(0x%08x)\n", dataNum);
		return 0;
	}
	if(!DVDFastOpen(DataDirStat[dir].entryNum, fileInfo)) {
		char panic_str[48];
		sprintf(panic_str, "HuDataDVDdirDirectOpen: File Open Error(%08x)", dataNum);
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

static void *HuDataDecodeIt(void *bufP, s32 bufOfs, s32 num, HeapID heap)
{
	void *dataStart;
	s32 *buf;
	s32 rawLen, decodeType;

	void *dest;
	buf =  (s32 *)((u8 *)bufP+bufOfs);
	if((u32)buf & 0x3) {
		u8 *data = (u8 *)buf;
		rawLen = *data++ << 24;
		rawLen += *data++ << 16;
		rawLen += *data++ << 8;
		rawLen += *data++;
		decodeType = *data++ << 24;
		decodeType += *data++ << 16;
		decodeType += *data++ << 8;
		decodeType += *data++;
		dataStart = data;
	} else {
		s32 *data = buf;
		rawLen = *data++;
		decodeType = *data++;
		dataStart = data;
	}
	switch(heap) {
        case HEAP_SOUND:
            dest = HuMemDirectMalloc(HEAP_SOUND, DATA_EFF_SIZE(rawLen));
            break;

        case HEAP_MODEL:
            dest = HuMemDirectMallocNum(HEAP_MODEL, DATA_EFF_SIZE(rawLen), num);
            break;

        case HEAP_DVD:
            dest = HuMemDirectMallocNum(HEAP_DVD, DATA_EFF_SIZE(rawLen), num);
            break;

        default:
            dest = HuMemDirectMallocNum(HEAP_HEAP, DATA_EFF_SIZE(rawLen), num);
            break;
    }
    if(dest) {
        HuDecodeData(dataStart, dest, rawLen, decodeType);
    }
    return dest;
}


void *HuDataReadNumHeapShortForce(s32 dataNum, s32 num, HeapID heap)
{
	DVDFileInfo fileInfo;
	s32 *dataHdr;
	s32 *fileData;
	void *fileBuf;
	s32 readLen;
	s32 fileNum;
	s32 fileOfs;
	s32 readOfs;
	s32 dataOfs;
	void *ret;
	s32 dir;
	s32 dvdLen;
	s32 fileNumMax;

	if(!HuDataDVDdirDirectOpen(dataNum, &fileInfo)) {
		return NULL;
	}
	dir = (dataNum >> 16) & 0xFFFF0000;
	fileNum = dataNum & 0xFFFF;
	fileOfs = (fileNum*4)+4;
	dvdLen = OSRoundUp32B(fileOfs+8);
	fileData = HuMemDirectMalloc(HEAP_HEAP, dvdLen);
	if(!HuDataDVDdirDirectRead(&fileInfo, fileData, dvdLen, 0)) {
		HuMemDirectFree(fileData);
		DVDClose(&fileInfo);
		return NULL;
	}
	fileNumMax = *fileData;
	if(fileNumMax <= fileNum) {
		HuMemDirectFree(fileData);
		OSReport("data.c%d: Data Number Error(0x%08x)\n", 1005, dataNum);
		DVDClose(&fileInfo);
		return NULL;
	}
	dataHdr = fileData;
	dataHdr += fileNum+1;
	fileOfs = *dataHdr;
	readOfs = OSRoundDown32B(fileOfs);
	if(fileNumMax <= fileNum+1) {
		readLen = fileInfo.length;
		dataOfs = readLen-readOfs;
	} else {
		dataHdr++;
		dataOfs = (*dataHdr)-readOfs;
		readLen = fileInfo.length;
	}
	readLen = OSRoundUp32B(dataOfs);
	HuMemDirectFree(fileData);
	fileBuf = HuMemDirectMalloc(HEAP_HEAP, (readLen+4) & ~0x3);
	if(fileBuf == NULL) {
		OSReport("data.c: couldn't allocate read buffer(0x%08x)\n", dataNum);
		DVDClose(&fileInfo);
		return NULL;
	}
	if(!HuDataDVDdirDirectRead(&fileInfo, fileBuf, readLen, readOfs)) {
		HuMemDirectFree(fileBuf);
		DVDClose(&fileInfo);
		return NULL;
	}
	DVDClose(&fileInfo);
	dataOfs = fileOfs-readOfs;
	ret = HuDataDecodeIt(fileBuf, dataOfs, num, heap);
	HuMemDirectFree(fileBuf);
    return ret;
}

char lbl_8011FDA6[] = "** dcnt %d tmp %08x sp1 %08x\n";
char lbl_8011FDC4[] = "** dcnt %d lastNum %08x\n";
