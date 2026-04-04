#ifndef _GAME_MEMORY_H
#define _GAME_MEMORY_H

#include "dolphin/types.h"

#define MEMORY_DEFAULT_NUM 0x10000000

typedef enum {
    HEAP_SYSTEM,
    HEAP_MUSIC,
    HEAP_DATA,
    HEAP_DVD,
    HEAP_MISC,
    HEAP_MAX
} HeapID;

void HuMemInitAll(void);
void *HuMemInit(void *ptr, size_t size);
void HuMemDCFlushAll();
void HuMemDCFlush(HeapID heap);
void *HuMemDirectMalloc(HeapID heap, size_t size);
void *HuMemDirectMallocNum(HeapID heap, size_t size, uintptr_t num);
void HuMemDirectFree(void *ptr);
void HuMemDirectFreeNum(HeapID heap, uintptr_t num);
size_t HuMemUsedMallocSizeGet(HeapID heap);
size_t HuMemUsedMallocBlockGet(HeapID heap);
size_t HuMemHeapSizeGet(HeapID heap);
void *HuMemHeapPtrGet(HeapID heap);

void *HuMemHeapInit(void *ptr, size_t size);
void *HuMemMemoryAlloc(void *heap_ptr, size_t size, uintptr_t retaddr);
void *HuMemMemoryAllocNum(void *heap_ptr, size_t size, uintptr_t num, uintptr_t retaddr);
void HuMemMemoryFree(void *ptr, uintptr_t retaddr);
void HuMemMemoryFreeNum(void *heap_ptr, uintptr_t num, uintptr_t retaddr);
size_t HuMemUsedMemorySizeGet(void *heap_ptr);
s32 HuMemUsedMemoryBlockGet(void *heap_ptr);
size_t HuMemMemorySizeGet(void *ptr);
size_t HuMemMemoryAllocSizeGet(size_t size);
void HuMemHeapDump(void *heap_ptr, s16 status);

#endif
