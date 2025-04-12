#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/os/OSPriv.h>
#include <stdlib.h>

#define ALIGNMENT 32

#define InRange(cell, arenaStart, arenaEnd) ((u32)arenaStart <= (u32)cell) && ((u32)cell < (u32)arenaEnd)

#define HEADERSIZE 32u
#define MINOBJSIZE 64u

struct Cell {
    struct Cell *prev;
    struct Cell *next;
    long size;
};

struct HeapDesc {
    long size;
    struct Cell *free;
    struct Cell *allocated;
};

volatile int __OSCurrHeap = -1;

static struct HeapDesc *HeapArray;
static int NumHeaps;
static void *ArenaStart;
static void *ArenaEnd;

// functions
static struct Cell *DLAddFront(struct Cell *list, struct Cell *cell);
static struct Cell *DLLookup(struct Cell *list, struct Cell *cell);
static struct Cell *DLExtract(struct Cell *list, struct Cell *cell);
static struct Cell *DLInsert(struct Cell *list, struct Cell *cell);
static int DLOverlap(struct Cell *list, void *start, void *end);
static long DLSize(struct Cell *list);

static struct Cell *DLAddFront(struct Cell *list, struct Cell *cell)
{
    cell->next = list;
    cell->prev = 0;
    if (list) {
        list->prev = cell;
    }
    return cell;
}

static struct Cell *DLLookup(struct Cell *list, struct Cell *cell)
{
    for (; list; list = list->next) {
        if (list == cell) {
            return list;
        }
    }
    return NULL;
}

static struct Cell *DLExtract(struct Cell *list, struct Cell *cell)
{
    if (cell->next) {
        cell->next->prev = cell->prev;
    }
    if (cell->prev == NULL) {
        return cell->next;
    }
    cell->prev->next = cell->next;
    return list;
}

static struct Cell *DLInsert(struct Cell *list, struct Cell *cell)
{
    struct Cell *prev;
    struct Cell *next;

    for (next = list, prev = NULL; next != 0; prev = next, next = next->next) {
        if (cell <= next) {
            break;
        }
    }

    cell->next = next;
    cell->prev = prev;
    if (next) {
        next->prev = cell;
        if ((u8 *)cell + cell->size == (u8 *)next) {
            cell->size += next->size;
            next = next->next;
            cell->next = next;
            if (next) {
                next->prev = cell;
            }
        }
    }
    if (prev) {
        prev->next = cell;
        if ((u8 *)prev + prev->size == (u8 *)cell) {
            prev->size += cell->size;
            prev->next = next;
            if (next) {
                next->prev = prev;
            }
        }
        return list;
    }
    return cell;
}

static int DLOverlap(struct Cell *list, void *start, void *end)
{
    struct Cell *cell = list;

    while (cell) {
        if (((start <= cell) && (cell < end)) || ((start < (void *)((u8 *)cell + cell->size)) && ((void *)((u8 *)cell + cell->size) <= end))) {
            return 1;
        }
        cell = cell->next;
    }
    return 0;
}

static long DLSize(struct Cell *list)
{
    struct Cell *cell;
    long size;

    size = 0;
    cell = list;

    while (cell) {
        size += cell->size;
        cell = cell->next;
    }

    return size;
}

void *OSAllocFromHeap(int heap, unsigned long size)
{
#ifdef TARGET_PC
    return malloc(size);
#endif
    struct HeapDesc *hd;
    struct Cell *cell;
    struct Cell *newCell;
    long leftoverSize;
    long requested;

    requested = size;
    ASSERTMSG1(0x14D, HeapArray, "OSAllocFromHeap(): heap is not initialized.");
    ASSERTMSG1(0x14E, (signed long)size > 0, "OSAllocFromHeap(): invalid size.");
    ASSERTMSG1(0x14F, heap >= 0 && heap < NumHeaps, "OSAllocFromHeap(): invalid heap handle.");
    ASSERTMSG1(0x150, HeapArray[heap].size >= 0, "OSAllocFromHeap(): invalid heap handle.");

    hd = &HeapArray[heap];
    size += 0x20;
    size = (size + 0x1F) & ~0x1F;

    for (cell = hd->free; cell != NULL; cell = cell->next) {
        if ((signed)size <= (signed)cell->size) {
            break;
        }
    }

    if (cell == NULL) {
        return NULL;
    }
    ASSERTMSG1(0x168, !((s32)cell & 0x1F), "OSAllocFromHeap(): heap is broken.");

    leftoverSize = cell->size - size;
    if (leftoverSize < 0x40U) {
        hd->free = DLExtract(hd->free, cell);
    }
    else {
        cell->size = size;
        newCell = (void *)((u8 *)cell + size);
        newCell->size = leftoverSize;
        newCell->prev = cell->prev;
        newCell->next = cell->next;
        if (newCell->next != NULL) {
            newCell->next->prev = newCell;
        }
        if (newCell->prev != NULL) {
            newCell->prev->next = newCell;
        }
        else {
            ASSERTMSG1(0x186, hd->free == cell, "OSAllocFromHeap(): heap is broken.");
            hd->free = newCell;
        }
    }

    hd->allocated = DLAddFront(hd->allocated, cell);
    return (u8 *)cell + 0x20;
}

void *OSAllocFixed(void **rstart, void **rend)
{
    int i;
    struct Cell *cell;
    struct Cell *newCell;
    struct HeapDesc *hd;
    void *start;
    void *end;
    void *cellEnd;

    start = (void *)((*(uintptr_t *)rstart) & ~((32) - 1));
    end = (void *)((*(uintptr_t *)rend + 0x1FU) & ~((32) - 1));

    ASSERTMSG1(0x1B0, HeapArray, "OSAllocFixed(): heap is not initialized.");
    ASSERTMSG1(0x1B1, (uintptr_t)start < (uintptr_t)end, "OSAllocFixed(): invalid range.");
    ASSERTMSG1(0x1B3, ((uintptr_t)ArenaStart <= (uintptr_t)start) && ((uintptr_t)start <= (uintptr_t)ArenaEnd), "OSAllocFixed(): invalid range.");

    for (i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i];
        if (hd->size >= 0) {
            if (DLOverlap(hd->allocated, start, end)) {
                return NULL;
            }
        }
    }

    for (i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i];
        if (hd->size >= 0) {
            for (cell = hd->free; cell; cell = cell->next) {
                cellEnd = ((u8 *)cell + cell->size);
                if (cellEnd > start) {
                    if (end <= cell) {
                        break;
                    }
                    if ((char *)start - 0x20 <= (char *)cell && cell < end && (start <= cellEnd) && (cellEnd < ((char *)end + 0x40))) {
                        if (cell < start) {
                            start = cell;
                        }
                        if (end < cellEnd) {
                            end = cellEnd;
                        }
                        hd->free = DLExtract(hd->free, cell);
                        hd->size -= cell->size;
                    }
                    else if ((char *)start - 0x20 <= (char *)cell && cell < end) {
                        if (cell < start) {
                            start = cell;
                        }
                        ASSERTMSG(0x1F3, MINOBJSIZE <= (char *)cellEnd - (char *)end);
                        newCell = (struct Cell *)end;

                        newCell->size = (uintptr_t)((char *)cellEnd - (char *)end);
                        newCell->next = cell->next;
                        if (newCell->next) {
                            newCell->next->prev = newCell;
                        }
                        newCell->prev = cell->prev;
                        if (newCell->prev) {
                            newCell->prev->next = newCell;
                        }
                        else {
                            hd->free = newCell;
                        }
                        hd->size -= ((char *)end - (char *)cell);
                        break;
                    }
                    else {
                        if ((start <= cellEnd) && (cellEnd < ((char *)end + 0x40U))) {
                            if (end < cellEnd) {
                                end = cellEnd;
                            }
                            ASSERTMSG(0x20C, MINOBJSIZE <= (char *)start - (char *)cell);
                            hd->size -= ((char *)cellEnd - (char *)start);
                            cell->size = ((char *)start - (char *)cell);
                        }
                        else {
                            ASSERTMSG(0x213, MINOBJSIZE <= (char *)cellEnd - (char *)end);
                            newCell = (struct Cell *)end;
                            newCell->size = ((char *)cellEnd - (char *)end);
                            newCell->next = cell->next;
                            if (newCell->next) {
                                newCell->next->prev = newCell;
                            }
                            newCell->prev = cell;
                            cell->next = newCell;
                            cell->size = ((char *)start - (char *)cell);
                            hd->size -= ((char *)end - (char *)start);
                            break;
                        }
                    }
                }
            }
            ASSERTMSG(0x222, 0 <= hd->size);
        }
    }
    ASSERTMSG(0x225, OFFSET(start, ALIGNMENT) == 0);
    ASSERTMSG(0x226, OFFSET(end, ALIGNMENT) == 0);
    ASSERTMSG(0x227, start < end);
    *(uintptr_t *)rstart = (uintptr_t)start;
    *(uintptr_t *)rend = (uintptr_t)end;
    return (void *)*(uintptr_t *)rstart;
}

void OSFreeToHeap(int heap, void *ptr)
{
#ifdef TARGET_PC
    free(ptr);
#else
    struct HeapDesc *hd;
    struct Cell *cell;

    ASSERTMSG1(0x23D, HeapArray, "OSFreeToHeap(): heap is not initialized.");
    ASSERTMSG1(0x23F, ((u32)ArenaStart + 0x20) <= (u32)ptr && (u32)ptr < (u32)ArenaEnd, "OSFreeToHeap(): invalid pointer.");
    ASSERTMSG1(0x240, OFFSET(ptr, ALIGNMENT) == 0, "OSFreeToHeap(): invalid pointer.");
    ASSERTMSG1(0x241, HeapArray[heap].size >= 0, "OSFreeToHeap(): invalid heap handle.");
    cell = (void *)((u32)ptr - 0x20);
    hd = &HeapArray[heap];
    ASSERTMSG1(0x247, DLLookup(hd->allocated, cell), "OSFreeToHeap(): invalid pointer.");
    hd->allocated = DLExtract(hd->allocated, cell);
    hd->free = DLInsert(hd->free, cell);
#endif
}

int OSSetCurrentHeap(int heap)
{
    int prev;

    ASSERTMSG1(0x267, HeapArray, "OSSetCurrentHeap(): heap is not initialized.");
    ASSERTMSG1(0x268, (heap >= 0) && (heap < NumHeaps), "OSSetCurrentHeap(): invalid heap handle.");
    ASSERTMSG1(0x269, HeapArray[heap].size >= 0, "OSSetCurrentHeap(): invalid heap handle.");
    prev = __OSCurrHeap;
    __OSCurrHeap = heap;
    return prev;
}

void *OSInitAlloc(void *arenaStart, void *arenaEnd, int maxHeaps)
{
    unsigned long arraySize;
    int i;
    struct HeapDesc *hd;

    ASSERTMSG1(0x283, maxHeaps > 0, "OSInitAlloc(): invalid number of heaps.");
    ASSERTMSG1(0x285, (uintptr_t)arenaStart < (uintptr_t)arenaEnd, "OSInitAlloc(): invalid range.");
    ASSERTMSG1(0x288, maxHeaps <= (((uintptr_t)arenaEnd - (uintptr_t)arenaStart) / 24U), "OSInitAlloc(): too small range.");
    arraySize = maxHeaps * sizeof(struct HeapDesc);
    HeapArray = arenaStart;
    NumHeaps = maxHeaps;

    for (i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i];
        hd->size = -1;
        hd->free = hd->allocated = 0;
    }
    __OSCurrHeap = -1;
    arenaStart = (void *)((uintptr_t)((char *)HeapArray + arraySize));
    arenaStart = (void *)(((uintptr_t)arenaStart + 0x1F) & ~0x1F);
    ArenaStart = arenaStart;
    ArenaEnd = (void *)((uintptr_t)arenaEnd & ~0x1F);
    ASSERTMSG1(0x2A4, ((uintptr_t)ArenaEnd - (uintptr_t)ArenaStart) >= 0x40U, "OSInitAlloc(): too small range.");
    return arenaStart;
}

uintptr_t OSCreateHeap(void *start, void *end)
{
    s32 heap;
    struct HeapDesc *hd;
    struct Cell *cell;

    ASSERTMSG1(0x2BD, HeapArray, "OSCreateHeap(): heap is not initialized.");
    ASSERTMSG1(0x2BE, start < end, "OSCreateHeap(): invalid range.");

    start = (void *)(((uintptr_t)start + 0x1FU) & ~((32) - 1));
    end = (void *)(((uintptr_t)end) & ~((32) - 1));

    ASSERTMSG1(0x2C1, (uintptr_t)start < (uintptr_t)end, "OSCreateHeap(): invalid range.");
    ASSERTMSG1(0x2C3, (uintptr_t)ArenaStart <= (uintptr_t)start && (uintptr_t)end <= (uintptr_t)ArenaEnd, "OSCreateHeap(): invalid range.");
    ASSERTMSG1(0x2C5, ((uintptr_t)end - (uintptr_t)start) >= 0x40U, "OSCreateHeap(): too small range.");

    for (heap = 0; heap < NumHeaps; heap++) {
        hd = &HeapArray[heap];
        if (hd->size < 0) {
            hd->size = (uintptr_t)end - (uintptr_t)start;
            cell = start;
            cell->prev = 0;
            cell->next = 0;
            cell->size = hd->size;
            hd->free = cell;
            hd->allocated = 0;
            return heap;
        }
    }
    return -1;
}

void OSDestroyHeap(int heap)
{
    struct HeapDesc *hd;
    long size;

    ASSERTMSG1(0x30A, HeapArray, "OSDestroyHeap(): heap is not initialized.");
    ASSERTMSG1(0x30B, (heap >= 0) && (heap < NumHeaps), "OSDestroyHeap(): invalid heap handle.");
    ASSERTMSG1(0x30C, HeapArray[heap].size >= 0, "OSDestroyHeap(): invalid heap handle.");

    hd = &HeapArray[heap];
    hd->size = -1;
}

void OSAddToHeap(int heap, void *start, void *end)
{
    struct HeapDesc *hd;
    struct Cell *cell;
    int i;

    ASSERTMSG1(0x339, HeapArray, "OSAddToHeap(): heap is not initialized.");
    ASSERTMSG1(0x33A, (heap >= 0) && (heap < NumHeaps), "OSAddToHeap(): invalid heap handle.");
    ASSERTMSG1(0x33B, HeapArray[heap].size >= 0, "OSAddToHeap(): invalid heap handle.");

    hd = &HeapArray[heap];

    ASSERTMSG1(0x33F, (u32)start < (u32)end, "OSAddToHeap(): invalid range.");

    start = (void *)(((u32)start + 0x1F) & ~((32) - 1));
    end = (void *)(((u32)end) & ~((32) - 1));

    ASSERTMSG1(0x343, ((u32)end - (u32)start) >= 0x40U, "OSAddToHeap(): too small range.");
    ASSERTMSG1(0x345, (u32)ArenaStart <= (u32)start && (u32)end <= (u32)ArenaEnd, "OSAddToHeap(): invalid range.");

    cell = (struct Cell *)start;
    cell->size = ((char *)end - (char *)start);
    hd->size += cell->size;
    hd->free = DLInsert(hd->free, cell);
}

// custom macro for OSCheckHeap
#define ASSERTREPORT(line, cond)                                                                                                                     \
    if (!(cond)) {                                                                                                                                   \
        OSReport("OSCheckHeap: Failed " #cond " in %d", line);                                                                                       \
        return -1;                                                                                                                                   \
    }

long OSCheckHeap(int heap)
{
    struct HeapDesc *hd;
    struct Cell *cell;
    long total = 0;
    long free = 0;

    ASSERTREPORT(0x37D, HeapArray);
    ASSERTREPORT(0x37E, 0 <= heap && heap < NumHeaps);
    hd = &HeapArray[heap];
    ASSERTREPORT(0x381, 0 <= hd->size);

    ASSERTREPORT(0x383, hd->allocated == NULL || hd->allocated->prev == NULL);

    for (cell = hd->allocated; cell; cell = cell->next) {
        ASSERTREPORT(0x386, InRange(cell, ArenaStart, ArenaEnd));
        ASSERTREPORT(0x387, OFFSET(cell, ALIGNMENT) == 0);
        ASSERTREPORT(0x388, cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(0x389, MINOBJSIZE <= cell->size);
        ASSERTREPORT(0x38A, OFFSET(cell->size, ALIGNMENT) == 0);
        total += cell->size;
        ASSERTREPORT(0x38D, 0 < total && total <= hd->size);
    }

    ASSERTREPORT(0x395, hd->free == NULL || hd->free->prev == NULL);

    for (cell = hd->free; cell; cell = cell->next) {
        ASSERTREPORT(0x398, InRange(cell, ArenaStart, ArenaEnd));
        ASSERTREPORT(0x399, OFFSET(cell, ALIGNMENT) == 0);
        ASSERTREPORT(0x39A, cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(0x39B, MINOBJSIZE <= cell->size);
        ASSERTREPORT(0x39C, OFFSET(cell->size, ALIGNMENT) == 0);
        /* clang-format off*/
        ASSERTREPORT(0x39D, cell->next == NULL || (char*) cell + cell->size < (char*) cell->next);
        /* clang-format on*/
        total += cell->size;
        free = (cell->size + free);
        free -= HEADERSIZE;
        ASSERTREPORT(0x3A1, 0 < total && total <= hd->size);
    }
    ASSERTREPORT(0x3A8, total == hd->size);
    return free;
}

unsigned long OSReferentSize(void *ptr)
{
    struct Cell *cell;

    ASSERTMSG1(0x3BB, HeapArray, "OSReferentSize(): heap is not initialized.");
    ASSERTMSG1(0x3BD, InRange(ptr, ArenaStart + HEADERSIZE, ArenaEnd), "OSReferentSize(): invalid pointer.");
    ASSERTMSG1(0x3BE, !OFFSET(ptr, 32), "OSReferentSize(): invalid pointer.");
    cell = (void *)((u32)ptr - HEADERSIZE);
    return (long)((u32)cell->size - HEADERSIZE);
}

void OSDumpHeap(int heap)
{
    struct HeapDesc *hd;
    struct Cell *cell;

    OSReport("\nOSDumpHeap(%d):\n", heap);
    ASSERTMSG1(0x3DE, HeapArray, "OSDumpHeap(): heap is not initialized.");
    ASSERTMSG1(0x3DF, (heap >= 0) && (heap < NumHeaps), "OSDumpHeap(): invalid heap handle.");
    hd = &HeapArray[heap];
    if (hd->size < 0) {
        OSReport("--------Inactive\n");
        return;
    }
    ASSERTMSG1(0x3E8, OSCheckHeap(heap) >= 0, "OSDumpHeap(): heap is broken.");
    OSReport("addr	size		end	prev	next\n");
    OSReport("--------Allocated\n");

    ASSERTMSG1(0x3F5, hd->allocated == NULL || hd->allocated->prev == NULL, "OSDumpHeap(): heap is broken.");

    for (cell = hd->allocated; cell; cell = cell->next) {
        OSReport("%x	%d	%x	%x	%x\n", cell, cell->size, (char *)cell + cell->size, cell->prev, cell->next);
    }
    OSReport("--------Free\n");
    for (cell = hd->free; cell; cell = cell->next) {
        OSReport("%x	%d	%x	%x	%x\n", cell, cell->size, (char *)cell + cell->size, cell->prev, cell->next);
    }
}

void OSVisitAllocated(void (*visitor)(void *, unsigned long))
{
    unsigned long heap;
    struct Cell *cell;

    for (heap = 0; heap < NumHeaps; heap++) {
        if (HeapArray[heap].size >= 0) {
            for (cell = HeapArray[heap].allocated; cell; cell = cell->next) {
                visitor((char *)cell + HEADERSIZE, cell->size);
            }
        }
    }
}
