#include "game/armem.h"
#include "game/data.h"

#define ARMEM_BLOCK_MAX 64

typedef struct ARMemBlock_s ARMEM_BLOCK;

struct ARMemBlock_s {
    /* 0x00 */ u8 flag;
    /* 0x02 */ u16 dir;
    /* 0x04 */ AMEM_PTR aMemP;
    /* 0x08 */ u32 size;
    /* 0x0C */ ARMEM_BLOCK *next;
}; // Size 0x10

typedef struct ARQueReq_s {
    /* 0x00 */ ARQRequest req;
    /* 0x20 */ s32 dir;
    /* 0x24 */ void *dst;
} ARQUEREQ; // Size 0x28

static void ArqCallBack(u32 pointerToARQRequest);
static void ArqCallBackAM(u32 pointerToARQRequest);
static void ArqCallBackAMFileRead(u32 pointerToARQRequest);

static s32 ATTRIBUTE_ALIGN(32) preLoadBuf[16];
static ARQUEREQ ARQueBuf[16];
static ARQRequest arqReq;
static ARMEM_BLOCK ARInfo[ARMEM_BLOCK_MAX];

static AMEM_PTR ARBase;
static volatile s32 arqCnt;
static s16 arqIdx;

void HuARInit(void) {
    s32 size;
    s16 i;

    if (!ARCheckInit()) {
        ARInit(NULL, 0);
        ARQInit();
    }
    for (i = 0; i < ARMEM_BLOCK_MAX; i++) {
        ARInfo[i].aMemP = 0;
    }
    size = ARGetSize() - HU_AMEM_BASE;
    ARBase = HU_AMEM_BASE;
    ARInfo[0].aMemP = ARBase;
    ARInfo[0].size = size;
    ARInfo[0].flag = 0;
    ARInfo[0].next = &ARInfo[1];
    ARInfo[0].dir = 0xFFFF;
    ARInfo[1].aMemP = -1;
    ARInfo[1].size = 0;
    ARInfo[1].flag = 1;
    ARInfo[1].next = 0;
    ARInfo[1].dir = 0xFFFF;
    arqCnt = 0;
}

AMEM_PTR HuARMalloc(u32 size) {
    ARMEM_BLOCK *prev;
    ARMEM_BLOCK *next;
    ARMEM_BLOCK *curr;
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
        for (i = 0; i < ARMEM_BLOCK_MAX - 1; i++, next++) {
            if (!next->aMemP) {
                break;
            }
        }
        if (i == ARMEM_BLOCK_MAX - 1) {
            OSReport("Can't ARAM Allocated %x\n", size);
            return 0;
        }
        next->next = curr->next;
        curr->next = next;
        next->size = curr->size - size;
        next->aMemP = curr->aMemP + size;
        curr->size = size;
        curr->dir = next->dir = 0xFFFF;
        next->flag = 0;
    }
    return curr->aMemP;
}

void HuARFree(AMEM_PTR aMemP) {
    ARMEM_BLOCK *prev;
    ARMEM_BLOCK *next;
    ARMEM_BLOCK *curr;

    curr = prev = ARInfo;
    while (curr->next) {
        if (curr->aMemP == aMemP) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr->flag != 0) {
        if (!curr->next && curr->aMemP != aMemP) {
            OSReport("Can't ARAM Free %x\n", aMemP);
            return;
        }
        next = curr->next;
        if (next->next && next->flag == FALSE) {
            if (curr->aMemP > next->aMemP) {
                curr->aMemP = next->aMemP;
            }
            curr->size += next->size;
            curr->next = next->next;
            next->aMemP = 0;
        }
        if (prev != curr && prev->next != 0 && prev->flag == FALSE) {
            if (prev->aMemP > curr->aMemP) {
                prev->aMemP = curr->aMemP;
            }
            prev->size += curr->size;
            prev->next = curr->next;
            curr->aMemP = 0;
        }
        curr->flag = 0;
        curr->dir = 0xFFFF;
    }
}

static u32 HuARSizeGet(AMEM_PTR aMemP) {
    ARMEM_BLOCK *curr;
    ARMEM_BLOCK *prev;

    curr = prev = ARInfo;
    while (curr->next != 0) {
        if (curr->aMemP == aMemP) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr->next == 0 && curr->aMemP != aMemP) {
        OSReport("Can't Find ARAM %x\n", aMemP);
        return 0;
    } else {
        return curr->size;
    }
}

static ARMEM_BLOCK *HuARInfoGet(u32 aMemP) {
    ARMEM_BLOCK *curr;
    ARMEM_BLOCK *prev;

    curr = prev = ARInfo;
    while (curr->next != 0) {
        if (curr->aMemP == aMemP) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr->next == 0 && curr->aMemP != aMemP) {
        OSReport("Can't Find ARAM %x\n", aMemP);
        return NULL;
    } else {
        return curr;
    }
}

void HuAMemDump(void) {
    ARMEM_BLOCK *curr;

    OSReport("ARAM DUMP ======================\n");
    OSReport("AMemPtr  Stat Length\n");
    for (curr = ARInfo; curr->next; curr = curr->next) {
        OSReport("%08x:%04x,%08x,%08x\n", curr->aMemP, curr->flag, curr->size, curr->dir);
    }
    OSReport("%08x:%04x,%08x\n", curr->aMemP, curr->flag, curr->size);
    OSReport("================================\n");
}

u32 HuAR_DVDtoARAM(u32 dir) {
    DataReadStat *stat;
    ARMEM_BLOCK *block;
    AMEM_PTR aMemP;

    aMemP = HuARDirCheck(dir);
    if (aMemP) {
        return aMemP;
    }
    stat = HuDataDirRead(dir);
    DirDataSize = OSRoundUp32B(DirDataSize);
    aMemP = HuARMalloc(DirDataSize);
    if (!aMemP) {
        return 0;
    }
    block = HuARInfoGet(aMemP);
    block->dir = (dir >> 16);
    arqCnt++;
    ARQPostRequest(&arqReq, 0x1234, 0, 0, (u32) stat->dir, aMemP, DirDataSize, ArqCallBack);
    OSReport("ARAM Trans %x\n", aMemP);
    while (HuARDMACheck());
    HuDataDirClose(dir);
    return aMemP;
}

static void ArqCallBack(u32 pointerToARQRequest) {
    arqCnt--;
    (void)pointerToARQRequest; // required to match (return?)
}

AMEM_PTR HuAR_MRAMtoARAM(s32 dir) {
    return HuAR_MRAMtoARAM2(HuDataGetDirPtr(dir));
}

AMEM_PTR HuAR_MRAMtoARAM2(void *dirPtr) {
    ARMEM_BLOCK *block;
    DataReadStat *status;
    u32 size;
    AMEM_PTR aMemP;

    status = HuDataGetStatus(dirPtr);
    aMemP = HuARDirCheck(status->dir_id << 16);
    if (aMemP) {
        return aMemP;
    }
    size = HuMemMemorySizeGet(dirPtr);
    size = OSRoundUp32B(size);
    aMemP = HuARMalloc(size);
    if (!aMemP) {
        return 0;
    }
    block = HuARInfoGet(aMemP);
    block->dir = status->dir_id;
    arqCnt++;
    ARQPostRequest(&arqReq, 0x1234, 0, 0, (u32)dirPtr, aMemP, size, ArqCallBack);
    return aMemP;
}

void HuAR_ARAMtoMRAM(AMEM_PTR aMemP) {
    HuAR_ARAMtoMRAMNum(aMemP, 0);
}

void *HuAR_ARAMtoMRAMNum(AMEM_PTR aMemP, s32 num) {
    ARMEM_BLOCK *block;
    s32 size;
    void *dst;

    block = HuARInfoGet(aMemP);
    if (HuDataReadChk(block->dir << 16) >= 0) {
        return;
    }
    size = HuARSizeGet(aMemP);
    dst = HuMemDirectMallocNum(HEAP_DVD, size, num);
    if (!dst) {
        return 0;
    }
    DCFlushRangeNoSync(dst, size);
    ARQueBuf[arqIdx].dir = (block->dir << 16);
    ARQueBuf[arqIdx].dst = dst;
    arqCnt++;
    PPCSync();
    ARQPostRequest(&ARQueBuf[arqIdx].req, 0x1234, 1, 0, aMemP, (u32) dst, size, ArqCallBackAM);
    arqIdx++;
    arqIdx &= 0xF;
    return dst;
}

static void ArqCallBackAM(u32 pointerToARQRequest) {
    ARQUEREQ *req_ptr = (ARQUEREQ*) pointerToARQRequest;

    arqCnt--;
    HuDataDirSet(req_ptr->dst, req_ptr->dir);
}

s32 HuARDMACheck(void) {
    return arqCnt;
}

u32 HuARDirCheck(u32 dir) {
    ARMEM_BLOCK *curr;

    curr = ARInfo;
    dir >>= 16;
    while (curr->next != 0) {
        if (curr->flag == 1 && curr->dir == dir) {
            return curr->aMemP;
        }
        curr = curr->next;
    }

    return 0;
}

void HuARDirFree(u32 dir) {
    ARMEM_BLOCK *curr;

    curr = ARInfo;
    dir >>= 16;
    while (curr->next != 0) {
        if (curr->dir == dir) {
            HuARFree(curr->aMemP);
            break;
        }
        curr = curr->next;
    }
}

void *HuAR_ARAMtoMRAMFileRead(u32 dir, u32 num, HeapID heap) {
    s32 *dirBuf;
    void *dst;
    void *dvdBuf;
    AMEM_PTR srcAMemP;
    s32 count;
    s32 size;
    AMEM_PTR aMemP;

    if ((aMemP = HuARDirCheck(dir)) == 0) {
        OSReport("Error: data none on ARAM %0x\n", dir);
        HuAMemDump();
        return 0;
    }
    DCInvalidateRange(&preLoadBuf, sizeof(preLoadBuf));
    srcAMemP = aMemP + (u32)((u32)(((u16)dir + 1) * 4) & 0xFFFFFFFE0);
    arqCnt++;
    ARQPostRequest(&ARQueBuf[arqIdx].req, 0x1234, 1, 0, srcAMemP, (u32) &preLoadBuf, sizeof(preLoadBuf), ArqCallBackAMFileRead);
    arqIdx++;
    arqIdx &= 0xF;
    while (HuARDMACheck());
    dirBuf = &preLoadBuf[(dir + 1) & 7];
    count = dirBuf[0];
    srcAMemP = aMemP + (u32)(count & 0xFFFFFFFE0);
    if (dirBuf[1] - count < 0) {
        size = (HuARSizeGet(aMemP) - count + 0x3F) & 0xFFFFFFFE0;
    } else {
        size = (dirBuf[1] - count + 0x3F) & 0xFFFFFFFE0;
    }
    dvdBuf = HuMemDirectMalloc(HEAP_DVD, size);
    if (!dvdBuf) {
        return 0;
    }
    DCFlushRangeNoSync(dvdBuf, size);
    arqCnt++;
    PPCSync();
    ARQPostRequest(&ARQueBuf[arqIdx].req, 0x1234, 1, 0, srcAMemP, (u32) dvdBuf, (u32) size, ArqCallBackAMFileRead);
    arqIdx++;
    arqIdx &= 0xF;
    while (HuARDMACheck());
    dirBuf = (s32*) ((u8*) dvdBuf + (count & 0x1F));
    dst = HuMemDirectMallocNum(heap, (dirBuf[0] + 1) & ~1, num);
    if (!dst) {
        return 0;
    }
    HuDecodeData(&dirBuf[2], dst, dirBuf[0], dirBuf[1]);
    HuMemDirectFree(dvdBuf);
    return dst;
}

static void ArqCallBackAMFileRead(u32 pointerToARQRequest) {
    arqCnt--;
    (void)pointerToARQRequest; // required to match (return?)
}
