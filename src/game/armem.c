#include "game/armem.h"
#include "game/data.h"

#include <port/byteswap.h>

typedef struct armem_block {
    /* 0x00 */ u8 flag;
    /* 0x02 */ u16 dir;
    /* 0x04 */ u32 amemptr;
    /* 0x08 */ u32 size;
    /* 0x0C */ struct armem_block *next;
} ARMemBlock; // Size 0x10

typedef struct ar_que_req {
    /* 0x00 */ ARQRequest req;
    /* 0x20 */ s32 dir;
    /* 0x24 */ void *dst;
} ARQueReq; // Size 0x28

static void ArqCallBack(u32 pointerToARQRequest);
static void ArqCallBackAM(u32 pointerToARQRequest);
static void ArqCallBackAMFileRead(u32 pointerToARQRequest);

static s32 ATTRIBUTE_ALIGN(32) preLoadBuf[16];
static ARQueReq ARQueBuf[16];
static ARQRequest arqReq;
static ARMemBlock ARInfo[64];

static s32 ARBase;
static volatile s32 arqCnt;
static s16 arqIdx;

void HuARInit(void) {
    s32 size;
    s16 i;

    if (!ARCheckInit()) {
        ARInit(NULL, 0);
        ARQInit();
    }
    for (i = 0; i < 64; i++) {
        ARInfo[i].amemptr = 0;
    }
#ifdef TARGET_PC
    size = ARGetSize() - 0x20;
    ARBase = 0x20;
#else
    size = ARGetSize() - 0x808000;
    ARBase = 0x808000;
#endif
    ARInfo[0].amemptr = ARBase;
    ARInfo[0].size = size;
    ARInfo[0].flag = 0;
    ARInfo[0].next = &ARInfo[1];
    ARInfo[0].dir = 0xFFFF;
    ARInfo[1].amemptr = -1;
    ARInfo[1].size = 0;
    ARInfo[1].flag = 1;
    ARInfo[1].next = 0;
    ARInfo[1].dir = 0xFFFF;
    arqCnt = 0;
}

u32 HuARMalloc(u32 size) {
    ARMemBlock *prev;
    ARMemBlock *next;
    ARMemBlock *curr;
    s16 i;

    size = OSRoundUp32B(size);
    curr = prev = ARInfo;
    while (curr->next != 0) {
        if (curr->flag == 0 && curr->size >= size) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr->next == 0) {
        OSReport("Can't ARAM Allocated %x\n", size);
        HuAMemDump();
        return 0;
    }
    curr->flag = 1;
    if (curr->size == size && prev != curr) {
        curr->dir = 0xFFFF;
    } else {
        next = &ARInfo[1];
        for (i = 0; i < 63; i++, next++) {
            if (!next->amemptr) {
                break;
            }
        }
        if (i == 63) {
            OSReport("Can't ARAM Allocated %x\n", size);
            return 0;
        }
        next->next = curr->next;
        curr->next = next;
        next->size = curr->size - size;
        next->amemptr = curr->amemptr + size;
        curr->size = size;
        curr->dir = next->dir = 0xFFFF;
        next->flag = 0;
    }
    return curr->amemptr;
}

void HuARFree(u32 amemptr) {
    ARMemBlock *prev;
    ARMemBlock *next;
    ARMemBlock *curr;

    curr = prev = ARInfo;
    while (curr->next) {
        if (curr->amemptr == amemptr) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr->flag != 0) {
        if (!curr->next && curr->amemptr != amemptr) {
            OSReport("Can't ARAM Free %x\n", amemptr);
            return;
        }
        next = curr->next;
        if (next->next && next->flag == 0) {
            if (curr->amemptr > next->amemptr) {
                curr->amemptr = next->amemptr;
            }
            curr->size += next->size;
            curr->next = next->next;
            next->amemptr = 0;
        }
        if (prev != curr && prev->next != 0 && prev->flag == 0) {
            if (prev->amemptr > curr->amemptr) {
                prev->amemptr = curr->amemptr;
            }
            prev->size += curr->size;
            prev->next = curr->next;
            curr->amemptr = 0;
        }
        curr->flag = 0;
        curr->dir = 0xFFFF;
    }
}

static u32 HuARSizeGet(u32 amemptr) {
    ARMemBlock *curr;
    ARMemBlock *prev;

    curr = prev = ARInfo;
    while (curr->next != 0) {
        if (curr->amemptr == amemptr) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr->next == 0 && curr->amemptr != amemptr) {
        OSReport("Can't Find ARAM %x\n", amemptr);
        return 0;
    } else {
        return curr->size;
    }
}

static ARMemBlock *HuARInfoGet(u32 amemptr) {
    ARMemBlock *curr;
    ARMemBlock *prev;

    curr = prev = ARInfo;
    while (curr->next != 0) {
        if (curr->amemptr == amemptr) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr->next == 0 && curr->amemptr != amemptr) {
        OSReport("Can't Find ARAM %x\n", amemptr);
        return NULL;
    } else {
        return curr;
    }
}

void HuAMemDump(void) {
    ARMemBlock *curr;

    OSReport("ARAM DUMP ======================\n");
    OSReport("AMemPtr  Stat Length\n");
    for (curr = ARInfo; curr->next; curr = curr->next) {
        OSReport("%08x:%04x,%08x,%08x\n", curr->amemptr, curr->flag, curr->size, curr->dir);
    }
    OSReport("%08x:%04x,%08x\n", curr->amemptr, curr->flag, curr->size);
    OSReport("================================\n");
}

u32 HuAR_DVDtoARAM(u32 dir) {
    DataReadStat *stat;
    ARMemBlock *block;
    u32 amemptr;

    amemptr = HuARDirCheck(dir);
    if (amemptr) {
        return amemptr;
    }
    stat = HuDataDirRead(dir);
    DirDataSize = OSRoundUp32B(DirDataSize);
    amemptr = HuARMalloc(DirDataSize);
    if (!amemptr) {
        return 0;
    }
    block = HuARInfoGet(amemptr);
    block->dir = (dir >> 16);
    arqCnt++;
    ARQPostRequest(&arqReq, 0x1234, 0, 0, (u32) stat->dir, amemptr, DirDataSize, ArqCallBack);
    OSReport("ARAM Trans %x\n", amemptr);
    while (HuARDMACheck());
    HuDataDirClose(dir);
    return amemptr;
}

static void ArqCallBack(u32 pointerToARQRequest) {
    arqCnt--;
    (void)pointerToARQRequest; // required to match (return?)
}

u32 HuAR_MRAMtoARAM(s32 dir) {
    return HuAR_MRAMtoARAM2(HuDataGetDirPtr(dir));
}

u32 HuAR_MRAMtoARAM2(void *dir_ptr) {
    ARMemBlock *block;
    DataReadStat *status;
    u32 size;
    u32 amemptr;

    status = HuDataGetStatus(dir_ptr);
    amemptr = HuARDirCheck(status->dir_id << 16);
    if (amemptr) {
        return amemptr;
    }
    size = HuMemMemorySizeGet(dir_ptr);
    size = OSRoundUp32B(size);
    amemptr = HuARMalloc(size);
    if (!amemptr) {
        return 0;
    }
    block = HuARInfoGet(amemptr);
    block->dir = status->dir_id;
    arqCnt++;
    ARQPostRequest(&arqReq, 0x1234, 0, 0, (u32)dir_ptr, amemptr, size, ArqCallBack);
    return amemptr;
}

void HuAR_ARAMtoMRAM(u32 src) {
    HuAR_ARAMtoMRAMNum(src, 0);
}

void *HuAR_ARAMtoMRAMNum(u32 src, s32 num) {
    ARMemBlock *block;
    s32 size;
    void *dst;

    block = HuARInfoGet(src);
    if (HuDataReadChk(block->dir << 16) >= 0) {
#ifdef NON_MATCHING
        return 0;
#else
        return;
#endif
    }
    size = HuARSizeGet(src);
    dst = HuMemDirectMallocNum(HEAP_DVD, size, num);
    if (!dst) {
        return 0;
    }
    DCFlushRangeNoSync(dst, size);
    ARQueBuf[arqIdx].dir = (block->dir << 16);
    ARQueBuf[arqIdx].dst = dst;
    arqCnt++;
    PPCSync();
    ARQPostRequest(&ARQueBuf[arqIdx].req, 0x1234, 1, 0, src, (uintptr_t) dst, size, ArqCallBackAM);
    arqIdx++;
    arqIdx &= 0xF;
    return dst;
}

static void ArqCallBackAM(u32 pointerToARQRequest) {
    ARQueReq *req_ptr = (ARQueReq*) pointerToARQRequest;

    arqCnt--;
    HuDataDirSet(req_ptr->dst, req_ptr->dir);
}

s32 HuARDMACheck(void) {
    return arqCnt;
}

u32 HuARDirCheck(u32 dir) {
    ARMemBlock *curr;

    curr = ARInfo;
    dir >>= 16;
    while (curr->next != 0) {
        if (curr->flag == 1 && curr->dir == dir) {
            return curr->amemptr;
        }
        curr = curr->next;
    }

    return 0;
}

void HuARDirFree(u32 dir) {
    ARMemBlock *curr;

    curr = ARInfo;
    dir >>= 16;
    while (curr->next != 0) {
        if (curr->dir == dir) {
            HuARFree(curr->amemptr);
            break;
        }
        curr = curr->next;
    }
}

#ifdef TARGET_PC
#define DIR_DATA (dir_data_pc)
#else
#define DIR_DATA (dir_data)
#endif

void *HuAR_ARAMtoMRAMFileRead(u32 dir, u32 num, HeapID heap) {
    s32 *dir_data;
    void *dst;
    void *dvd_data;
    u32 amem_src;
    s32 count;
    s32 size;
    u32 amemptr;
#ifdef TARGET_PC
    s32 dir_data_pc[2];
    s32 i;
#endif

    if ((amemptr = HuARDirCheck(dir)) == 0) {
        OSReport("Error: data none on ARAM %0x\n", dir);
        HuAMemDump();
        return 0;
    }
    DCInvalidateRange(&preLoadBuf, sizeof(preLoadBuf));
    amem_src = amemptr + (u32)((((dir & 0xFFFF) + 1) * 4) & 0xFFFFFFFE0);
    arqCnt++;
    ARQPostRequest(&ARQueBuf[arqIdx].req, 0x1234, 1, 0, amem_src, (uintptr_t) &preLoadBuf, sizeof(preLoadBuf), ArqCallBackAMFileRead);
    arqIdx++;
    arqIdx &= 0xF;
    while (HuARDMACheck());
    dir_data = &preLoadBuf[(dir + 1) & 7];
#ifdef TARGET_PC
    for (i = 0; i < 2; i++) {
        dir_data_pc[i] = dir_data[i];
        byteswap_s32(&dir_data_pc[i]);
    }
#endif
    count = DIR_DATA[0];
    amem_src = amemptr + (u32)(count & 0xFFFFFFFE0);
    if (DIR_DATA[1] - count < 0) {
        size = (HuARSizeGet(amemptr) - count + 0x3F) & 0xFFFFFFFE0;
    } else {
        size = (DIR_DATA[1] - count + 0x3F) & 0xFFFFFFFE0;
    }
    dvd_data = HuMemDirectMalloc(HEAP_DVD, size);
    if (!dvd_data) {
        return 0;
    }
    DCFlushRangeNoSync(dvd_data, size);
    arqCnt++;
    PPCSync();
    ARQPostRequest(&ARQueBuf[arqIdx].req, 0x1234, 1, 0, amem_src, (uintptr_t) dvd_data, (u32) size, ArqCallBackAMFileRead);
    arqIdx++;
    arqIdx &= 0xF;
    while (HuARDMACheck());
    dir_data = (s32*) ((u8*) dvd_data + (count & 0x1F));
#ifdef TARGET_PC
    for (i = 0; i < 2; i++) {
        dir_data_pc[i] = dir_data[i];
        byteswap_s32(&dir_data_pc[i]);
    }
#endif
    dst = HuMemDirectMallocNum(heap, (DIR_DATA[0] + 1) & ~1, num);
    if (!dst) {
        return 0;
    }
    HuDecodeData(&dir_data[2], dst, DIR_DATA[0], DIR_DATA[1]);
    HuMemDirectFree(dvd_data);
    return dst;
}

#undef DIR_DATA

static void ArqCallBackAMFileRead(u32 pointerToARQRequest) {
    arqCnt--;
    (void)pointerToARQRequest; // required to match (return?)
}
