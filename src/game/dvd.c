#include "game/dvd.h"
#include "game/data.h"

#include "dolphin/dvd.h"
#include "dolphin/os.h"


static DVDDiskID correctDiskID = {
    { 'M', 'P', 'G', 'C' }, //gameName
    { 'H', 'U' }, //company
    1, //diskNumber 
    1, //gameVersion
    1, //streaming
    0, //streamingBufSize
};


static int CallBackStatus;
static s32 beforeDvdStatus;

static void HuDVDReadAsyncCallBack(s32 result, DVDFileInfo* fileInfo)
{
    CallBackStatus = 1;
}

static void *HuDvdDataReadWait(DVDFileInfo *file, int heap, int mode, int num, DVDCallback cb, BOOL async)
{
    u32 len;
    void *buf;
    if(mode != 0 && mode != 1 && mode != 2) {
        OSReport("dvd.c: HuDvdDataReadWait Mode Error");
        buf = NULL;
        len = 0;
    }
    len = file->length;
    DirDataSize = len;
    if(mode == 1) {
        buf = HuMemDirectMallocNum(heap, OSRoundUp32B(len), num);
    } else {
        buf = HuMemDirectMalloc(heap, OSRoundUp32B(len));
    }
    if(!buf) {
        OSReport("dvd.c: Memory Allocation Error (Length %x) (mode %d)\n", len, mode);
        OSReport("Rest Memory %x\n", HuMemHeapSizeGet(3)-HuMemUsedMallocSizeGet(3));
        OSPanic("dvd.c", 75, "\n");
        return NULL;
    }
    
    DCInvalidateRange(buf, OSRoundUp32B(len));
    OSReport("Rest Memory %x\n", HuMemHeapSizeGet(3)-HuMemUsedMallocSizeGet(3));
    CallBackStatus = 0;
    DVDReadAsync(file, buf, OSRoundUp32B(len), 0, cb);
    if(!async) {
        while(!CallBackStatus) {
            HuDvdErrorWatch();
        }
        HuDvdErrorWatch();
    }
    
    return buf;
}

void *HuDvdDataRead(char *path)
{
    DVDFileInfo file;
    void *data = NULL;
    if(!DVDOpen(path, &file)) {
        OSPanic("dvd.c", 146, "dvd.c: File Open Error");
    } else {
        data = HuDvdDataReadWait(&file, HEAP_DVD, 0, 0, HuDVDReadAsyncCallBack, FALSE);
        DVDClose(&file);
    }
    return data;
}

void **HuDvdDataReadMulti(char **paths)
{
    DVDFileInfo file;
    int i;
    u32 count;
    void **file_ptrs;
    count = 0;
    while(paths[count]) {
        count++;
    }
    file_ptrs = HuMemDirectMalloc(0, count*sizeof(void *));
    for(i=0; i<count; i++) {
        if(!DVDOpen(paths[i], &file)) {
            OSPanic("dvd.c", 183, "dvd.c: File Open Error");
            return NULL;
        } else {
            file_ptrs[i] = HuDvdDataReadWait(&file, HEAP_DVD, 0, 0, HuDVDReadAsyncCallBack, FALSE);
            DVDClose(&file);
        }
    }
    return file_ptrs;
}

void *HuDvdDataReadDirect(char *path, HeapID heap)
{
    DVDFileInfo file;
    void *data = NULL;
    if(!DVDOpen(path, &file)) {
        OSPanic("dvd.c", 202, "dvd.c: File Open Error");
    } else {
        data = HuDvdDataReadWait(&file, heap, 2, 0, HuDVDReadAsyncCallBack, FALSE);
        DVDClose(&file);
    }
    return data;
}

void *HuDvdDataFastRead(s32 entrynum)
{
    DVDFileInfo file;
    void *data = NULL;
    if(!DVDFastOpen(entrynum, &file)) {
        OSPanic("dvd.c", 243, "dvd.c: File Open Error");
    } else {
        data = HuDvdDataReadWait(&file, HEAP_DVD, 0, 0, HuDVDReadAsyncCallBack, FALSE);
        DVDClose(&file);
    }
    return data;
}

void *HuDvdDataFastReadNum(s32 entrynum, s32 num)
{
    DVDFileInfo file;
    void *data = NULL;
    if(!DVDFastOpen(entrynum, &file)) {
        (void)num;
        OSPanic("dvd.c", 258, "dvd.c: File Open Error");
    } else {
        data = HuDvdDataReadWait(&file, HEAP_DVD, 1, num, HuDVDReadAsyncCallBack, FALSE);
        DVDClose(&file);
    }
    return data;
}

void *HuDvdDataFastReadAsync(s32 entrynum, HUDATASTAT *stat)
{
    DVDFileInfo file;
    void *data = NULL;
    if(!DVDFastOpen(entrynum, &stat->dvdFile)) {
        OSPanic("dvd.c", 274, "dvd.c: File Open Error");
    } else {
        data = HuDvdDataReadWait(&stat->dvdFile, HEAP_DVD, 0, 0, HuDataDirReadAsyncCallBack, TRUE);
    }
    return data;
}

void HuDvdDataClose(void *ptr)
{
    if(ptr) {
        HuMemDirectFree(ptr);
    }
}

void HuDvdErrorWatch()
{
    int status = DVDGetDriveStatus();
    if(status == beforeDvdStatus) {
        return;
    }
    beforeDvdStatus = status;
    switch(status+1) {
        case 0:
            OSReport("DVD ERROR:Fatal error occurred\n***HALT***");
            while(1);
            break;
            
        case 5:
            OSReport("DVD ERROR:No disk\n");
            break;
            
        case 6:
            OSReport("DVD ERROR:Cover open\n");
            break;
            
        case 7:
            OSReport("DVD ERROR:Wrong disk\n");
            break;
            
        case 12:
            OSReport("DVD ERROR:Please retry\n");
            break;
            
        default:
            break;
    }
}