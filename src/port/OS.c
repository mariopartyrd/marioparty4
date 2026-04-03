#include <stdio.h>
#include <stdlib.h>

#include <dolphin.h>

#define MEM_SIZE (64 * 1024 * 1024)

u8 LC_CACHE_BASE[4096];

u32 OSGetConsoleSimulatedMemSize(void)
{
    puts("OSGetSimulatedMemSize is a stub");
    return 60000000;
}


#define ALIGNMENT 32

#define InRange(cell, arenaStart, arenaEnd) ((uintptr_t)arenaStart <= (uintptr_t)cell) && ((uintptr_t)cell < (uintptr_t)arenaEnd)

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
        if ((((struct Cell*)start <= cell) && (cell < (struct Cell*)end)) || ((start < (void *)((u8 *)cell + cell->size)) && ((void *)((u8 *)cell + cell->size) <= end))) {
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

void *OSAllocFromHeap(int heap, u32 size)
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
                    if (end <= (void*)cell) {
                        break;
                    }
                    if ((char *)start - 0x20 <= (char *)cell && (void*)cell < end && (start <= cellEnd) && ((char*)cellEnd < ((char *)end + 0x40))) {
                        if ((void*)cell < start) {
                            start = cell;
                        }
                        if (end < cellEnd) {
                            end = cellEnd;
                        }
                        hd->free = DLExtract(hd->free, cell);
                        hd->size -= cell->size;
                    }
                    else if ((char *)start - 0x20 <= (char *)cell && (void*)cell < end) {
                        if ((void*)cell < start) {
                            start = cell;
                        }
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
                        if ((start <= cellEnd) && ((char*)cellEnd < ((char *)end + 0x40U))) {
                            if (end < cellEnd) {
                                end = cellEnd;
                            }
                            hd->size -= ((char *)cellEnd - (char *)start);
                            cell->size = ((char *)start - (char *)cell);
                        }
                        else {
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
        }
    }
    *(uintptr_t *)rstart = (uintptr_t)start;
    *(uintptr_t *)rend = (uintptr_t)end;
    return (void *)*(uintptr_t *)rstart;
}

void OSFreeToHeap(int heap, void *ptr)
{
    free(ptr);
}

int OSSetCurrentHeap(int heap)
{
    int prev;

    prev = __OSCurrHeap;
    __OSCurrHeap = heap;
    return prev;
}

void *OSInitAlloc(void *arenaStart, void *arenaEnd, int maxHeaps)
{
    unsigned long arraySize;
    int i;
    struct HeapDesc *hd;

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
    return arenaStart;
}

s32 OSCreateHeap(void *start, void *end)
{
    s32 heap;
    struct HeapDesc *hd;
    struct Cell *cell;

    start = (void *)(((uintptr_t)start + 0x1FU) & ~((32) - 1));
    end = (void *)(((uintptr_t)end) & ~((32) - 1));

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

    hd = &HeapArray[heap];
    hd->size = -1;
}

void OSAddToHeap(int heap, void *start, void *end)
{
    struct HeapDesc *hd;
    struct Cell *cell;
    int i;

    hd = &HeapArray[heap];

    start = (void *)(((uintptr_t)start + 0x1F) & ~((32) - 1));
    end = (void *)(((uintptr_t)end) & ~((32) - 1));

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

s32 OSCheckHeap(int heap)
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

u32 OSReferentSize(void *ptr)
{
    struct Cell *cell;

    cell = (void *)((u32)ptr - HEADERSIZE);
    return (long)((u32)cell->size - HEADERSIZE);
}

void OSDumpHeap(int heap)
{
    struct HeapDesc *hd;
    struct Cell *cell;

    OSReport("\nOSDumpHeap(%d):\n", heap);
    hd = &HeapArray[heap];
    if (hd->size < 0) {
        OSReport("--------Inactive\n");
        return;
    }
    OSReport("addr	size		end	prev	next\n");
    OSReport("--------Allocated\n");

    for (cell = hd->allocated; cell; cell = cell->next) {
        OSReport("%x	%d	%x	%x	%x\n", cell, cell->size, (char *)cell + cell->size, cell->prev, cell->next);
    }
    OSReport("--------Free\n");
    for (cell = hd->free; cell; cell = cell->next) {
        OSReport("%x	%d	%x	%x	%x\n", cell, cell->size, (char *)cell + cell->size, cell->prev, cell->next);
    }
}

void OSVisitAllocated(void (*visitor)(void *, u32))
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


void OSInitStopwatch(struct OSStopwatch *sw, char *name)
{
    sw->name = name;
    sw->total = 0;
    sw->hits = 0;
    sw->min = 0x00000000FFFFFFFF;
    sw->max = 0;
}

void OSStartStopwatch(struct OSStopwatch *sw)
{
    sw->running = 1;
    sw->last = OSGetTime();
}

void OSStopStopwatch(struct OSStopwatch *sw)
{
    long long interval;

    if (sw->running != 0) {
        interval = OSGetTime() - sw->last;
        sw->total += interval;
        sw->running = 0;
        sw->hits++;
        if (sw->max < interval) {
            sw->max = interval;
        }
        if (interval < sw->min) {
            sw->min = interval;
        }
    }
}

OSTime OSCheckStopwatch(OSStopwatch *sw)
{
    long long currTotal;

    currTotal = sw->total;
    if (sw->running != 0) {
        currTotal += OSGetTime() - sw->last;
    }
    return currTotal;
}

void OSResetStopwatch(struct OSStopwatch *sw)
{
    OSInitStopwatch(sw, sw->name);
}

void OSDumpStopwatch(struct OSStopwatch *sw)
{
    OSReport("Stopwatch [%s]	:\n", sw->name);
    OSReport("\tTotal= %lld us\n", OSTicksToMicroseconds(sw->total));
    OSReport("\tHits = %d \n", sw->hits);
    OSReport("\tMin  = %lld us\n", OSTicksToMicroseconds(sw->min));
    OSReport("\tMax  = %lld us\n", OSTicksToMicroseconds(sw->max));
    OSReport("\tMean = %lld us\n", OSTicksToMicroseconds(sw->total / sw->hits));
}
