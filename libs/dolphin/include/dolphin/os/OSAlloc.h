#ifndef _DOLPHIN_OSALLOC
#define _DOLPHIN_OSALLOC

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef int OSHeapHandle;
typedef void (*OSAllocVisitor)(void *obj, u32 size);
void *OSInitAlloc(void *arenaStart, void *arenaEnd, int maxHeaps);
uintptr_t OSCreateHeap(void *start, void *end);
void OSDestroyHeap(OSHeapHandle heap);
void OSAddToHeap(OSHeapHandle heap, void *start, void *end);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap);
void *OSAllocFromHeap(int heap, unsigned long size);
void *OSAllocFixed(void **rstart, void **rend);
void OSFreeToHeap(OSHeapHandle heap, void *ptr);
long OSCheckHeap(OSHeapHandle heap);
void OSDumpHeap(OSHeapHandle heap);
unsigned long OSReferentSize(void *ptr);
void OSVisitAllocated(void (*visitor)(void *, unsigned long));
extern volatile OSHeapHandle __OSCurrHeap;
#define OSAlloc(size) OSAllocFromHeap(__OSCurrHeap, (size))
#define OSFree(ptr) OSFreeToHeap(__OSCurrHeap, (ptr))
#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSALLOC
