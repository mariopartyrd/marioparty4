#include "game/memory.h"
#include "dolphin/os.h"

#define DATA_GET_BLOCK(ptr) ((struct memory_block *)(((char *)(ptr)) - 32))
#define BLOCK_GET_DATA(block) (((char *)(block)) + 32)

#define MEM_ALLOC_SIZE(size) (((size) + 63) & 0xFFFFFFE0)

struct memory_block {
    s32 size;
    u8 magic;
    u8 flag;
    struct memory_block *prev;
    struct memory_block *next;
    u32 num;
    uintptr_t retaddr;
};

static void *HuMemMemoryAlloc2(void *heap_ptr, s32 size, u32 num, uintptr_t retaddr);

void *HuMemHeapInit(void *ptr, s32 size)
{
    struct memory_block *block = ptr;
    block->size = size;
    block->magic = 205;
    block->flag = 0;
    block->prev = block;
    block->next = block;
    block->num = -256;
    block->retaddr = 0xCDCDCDCD;
    return block;
}

void *HuMemMemoryAllocNum(void *heap_ptr, s32 size, u32 num, uintptr_t retaddr)
{
    return HuMemMemoryAlloc2(heap_ptr, size, num, retaddr);
}

void *HuMemMemoryAlloc(void *heap_ptr, s32 size, uintptr_t retaddr)
{
    return HuMemMemoryAlloc2(heap_ptr, size, -256, retaddr);
}

static void *HuMemMemoryAlloc2(void *heap_ptr, s32 size, u32 num, uintptr_t retaddr)
{
    s32 alloc_size = MEM_ALLOC_SIZE(size);
    struct memory_block *block = heap_ptr;
    do {
        if (!block->flag && block->size >= alloc_size) {
            if (block->size - alloc_size > 32u) {
#ifdef TARGET_PC
                struct memory_block *new_block = (struct memory_block *)(((char *)block) + alloc_size);
#else
                struct memory_block *new_block = (struct memory_block *)(((u32)block) + alloc_size);
#endif
                new_block->size = block->size - alloc_size;
                new_block->magic = 205;
                new_block->flag = 0;
                new_block->retaddr = retaddr;
                block->next->prev = new_block;
                new_block->next = block->next;
                block->next = new_block;
                new_block->prev = block;
                block->size = alloc_size;
            }
            block->flag = 1;
            block->magic = 165;
            block->num = num;
            block->retaddr = retaddr;
            return BLOCK_GET_DATA(block);
        }
        block = block->next;
    } while (block != heap_ptr);
    OSReport("HuMem>memory alloc error %08x(%08X): Call %08x\n", size, num, retaddr);
    HuMemHeapDump(heap_ptr, -1);
    return NULL;
}

void HuMemMemoryFreeNum(void *heap_ptr, u32 num, uintptr_t retaddr)
{
    struct memory_block *block = heap_ptr;
    do {
        struct memory_block *block_next = block->next;
        if (block->flag && block->num == num) {
            HuMemMemoryFree(BLOCK_GET_DATA(block), retaddr);
        }
        block = block_next;
    } while (block != heap_ptr);
}

static void HuMemTailMemoryAlloc2() // Required for string literal
{
    OSReport("memory allocation(tail) error.\n");
}

void HuMemMemoryFree(void *ptr, uintptr_t retaddr)
{
    struct memory_block *block;
    if (!ptr) {
        return;
    }
    block = DATA_GET_BLOCK(ptr);
    if (block->magic != 165) {
        OSReport("HuMem>memory free error. %08x( call %08x)\n", ptr, retaddr);
        return;
    }
    if (block->prev < block && !block->prev->flag) {
        block->flag = 0;
        block->magic = 205;
        block->next->prev = block->prev;
        block->prev->next = block->next;
        block->prev->size += block->size;
        block = block->prev;
    }
    if (block->next > block && !block->next->flag) {
        block->next->next->prev = block;
        block->size += block->next->size;
        block->next = block->next->next;
    }
    block->flag = 0;
    block->magic = 205;
    block->retaddr = retaddr;
}

s32 HuMemUsedMemorySizeGet(void *heap_ptr)
{
    struct memory_block *block = heap_ptr;
    s32 size = 0;
    do {
        if (block->flag == 1) {
            size += block->size;
        }
        block = block->next;
    } while (block != heap_ptr);
    return size;
}

s32 HuMemUsedMemoryBlockGet(void *heap_ptr)
{
    struct memory_block *block = heap_ptr;
    s32 num_blocks = 0;
    do {
        if (block->flag == 1) {
            num_blocks++;
        }
        block = block->next;
    } while (block != heap_ptr);
    return num_blocks;
}

s32 HuMemMemoryAllocSizeGet(s32 size)
{
    return MEM_ALLOC_SIZE(size);
}

void HuMemHeapDump(void *heap_ptr, s16 status)
{
    struct memory_block *block = heap_ptr;
    s32 size = 0;
    s32 inactive_size = 0;
    s32 num_blocks = 0;
    s32 num_unused_blocks = 0;
    u8 dump_type;

    if (status < 0) {
        dump_type = 10;
    }
    else if (status == 0) {
        dump_type = 0;
    }
    else {
        dump_type = 1;
    }
    OSReport("======== HuMem heap dump %08x ========\n", heap_ptr);
    OSReport("MCB-----+Size----+MG+FL+Prev----+Next----+UNum----+Body----+Call----\n");
    do {
        if (dump_type == 10 || block->flag == dump_type) {
            OSReport("%08x %08x %02x %02x %08x %08x %08x %08x %08x\n", block, block->size, block->magic, block->flag, block->prev, block->next,
                block->num, BLOCK_GET_DATA(block), block->retaddr);
        }
        if (block->flag == 1) {
            size += block->size;
            num_blocks++;
        }
        else {
            inactive_size += block->size;
            num_unused_blocks++;
        }

        block = block->next;
    } while (block != heap_ptr);
    OSReport("MCB:%d(%d/%d) MEM:%08x(%08x/%08x)\n", num_blocks + num_unused_blocks, num_blocks, num_unused_blocks, size + inactive_size, size,
        inactive_size);
    OSReport("======== HuMem heap dump %08x end =====\n", heap_ptr);
}

s32 HuMemMemorySizeGet(void *ptr)
{
    struct memory_block *block;
    if (!ptr) {
        return 0;
    }
    block = DATA_GET_BLOCK(ptr);
    if (block->flag == 1 && block->magic == 165) {
        return block->size - 32;
    }
    else {
        return 0;
    }
}
