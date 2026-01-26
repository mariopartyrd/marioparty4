#include "game/process.h"
#include "dolphin/os.h"
#include "game/memory.h"

#ifdef __MWERKS__
#include "game/jmp.h"
#endif

#define FAKE_RETADDR 0xA5A5A5A5

#define EXEC_NORMAL 0
#define EXEC_SLEEP 1
#define EXEC_CHILDWATCH 2
#define EXEC_KILLED 3

#ifdef TARGET_PC
static cothread_t processthread;
static u8 thread_arg;
#else
static jmp_buf processjmpbuf;
#endif
static Process *processtop;
static Process *processcur;
static u16 processcnt;
u32 procfunc;

void HuPrcInit(void)
{
    processcnt = 0;
    processtop = NULL;
}

static void LinkProcess(Process **root, Process *process)
{
    Process *src_process = *root;

    if (src_process && (src_process->prio >= process->prio)) {
        while (src_process->next && src_process->next->prio >= process->prio) {
            src_process = src_process->next;
        }

        process->next = src_process->next;
        process->prev = src_process;
        src_process->next = process;
        if (process->next) {
            process->next->prev = process;
        }
    }
    else {
        process->next = (*root);
        process->prev = NULL;
        *root = process;
        if (src_process) {
            src_process->prev = process;
        }
    }
}
static void UnlinkProcess(Process **root, Process *process)
{
    if (process->next) {
        process->next->prev = process->prev;
    }
    if (process->prev) {
        process->prev->next = process->next;
    }
    else {
        *root = process->next;
    }
}

Process *HuPrcCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size)
{
    Process *process;
    s32 alloc_size;
    void *heap;
    if (stack_size == 0) {
        stack_size = 2048;
    }
#ifdef TARGET_PC
    stack_size *= 2;
    alloc_size = HuMemMemoryAllocSizeGet(sizeof(Process)) + HuMemMemoryAllocSizeGet(extra_size);
#else
    alloc_size = HuMemMemoryAllocSizeGet(sizeof(Process)) + HuMemMemoryAllocSizeGet(stack_size) + HuMemMemoryAllocSizeGet(extra_size);
#endif
    if (!(heap = HuMemDirectMalloc(HEAP_SYSTEM, alloc_size))) {
        OSReport("process> malloc error size %d\n", alloc_size);
        return NULL;
    }
    HuMemHeapInit(heap, alloc_size);
    process = HuMemMemoryAlloc(heap, sizeof(Process), FAKE_RETADDR);
    process->heap = heap;
    process->exec = EXEC_NORMAL;
    process->stat = 0;
    process->prio = prio;
    process->sleep_time = 0;
#ifdef TARGET_PC
    process->thread = co_create(stack_size, func);
#else
    process->base_sp = ((uintptr_t)HuMemMemoryAlloc(heap, stack_size, FAKE_RETADDR)) + stack_size - 8;
    gcsetjmp(&process->jump);
    process->jump.lr = (u32)func;
    process->jump.sp = process->base_sp;
#endif
    process->dtor = NULL;
    process->user_data = NULL;
    LinkProcess(&processtop, process);
    process->child = NULL;
    process->parent = NULL;
    processcnt++;
    return process;
}

void HuPrcChildLink(Process *parent, Process *child)
{
    HuPrcChildUnlink(child);
    if (parent->child) {
        parent->child->first_child = child;
    }
    child->next_child = parent->child;
    child->first_child = NULL;
    parent->child = child;
    child->parent = parent;
}

void HuPrcChildUnlink(Process *process)
{
    if (process->parent) {
        if (process->next_child) {
            process->next_child->first_child = process->first_child;
        }
        if (process->first_child) {
            process->first_child->next_child = process->next_child;
        }
        else {
            process->parent->child = process->next_child;
        }
        process->parent = NULL;
    }
}

Process *HuPrcChildCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size, Process *parent)
{
    Process *child = HuPrcCreate(func, prio, stack_size, extra_size);
    HuPrcChildLink(parent, child);
    return child;
}

void HuPrcChildWatch()
{
    Process *curr = HuPrcCurrentGet();
    if (curr->child) {
        curr->exec = EXEC_CHILDWATCH;

#ifdef TARGET_PC
        thread_arg = 1;
        co_switch(processthread);
#else
        if (gcsetjmp(&curr->jump) == 0)
        {
            gclongjmp(&processjmpbuf, 1);
        }
#endif
    }
}

Process *HuPrcCurrentGet()
{
    return processcur;
}

static s32 SetKillStatusProcess(Process *process)
{
    if (process->exec != EXEC_KILLED) {
        HuPrcWakeup(process);
        process->exec = EXEC_KILLED;
        return 0;
    }
    else {
        return -1;
    }
}

s32 HuPrcKill(Process *process)
{
    if (process == NULL) {
        process = HuPrcCurrentGet();
    }
    HuPrcChildKill(process);
    HuPrcChildUnlink(process);
    return SetKillStatusProcess(process);
}

void HuPrcChildKill(Process *process)
{
    Process *child = process->child;
    while (child) {
        if (child->child) {
            HuPrcChildKill(child);
        }
        SetKillStatusProcess(child);
        child = child->next_child;
    }
    process->child = NULL;
}

static void gcTerminateProcess(Process *process)
{
    if (process->dtor) {
        process->dtor();
    }
    UnlinkProcess(&processtop, process);
    processcnt--;
#ifdef TARGET_PC
    thread_arg = 2;
    co_switch(processthread);
#else
    gclongjmp(&processjmpbuf, 2);
#endif
}

void HuPrcEnd()
{
    Process *process = HuPrcCurrentGet();
    HuPrcChildKill(process);
    HuPrcChildUnlink(process);
    gcTerminateProcess(process);
}

void HuPrcSleep(s32 time)
{
    Process *process = HuPrcCurrentGet();
    if (time != 0 && process->exec != EXEC_KILLED) {
        process->exec = EXEC_SLEEP;
        process->sleep_time = time;
    }
#ifdef TARGET_PC
    thread_arg = 1;
    co_switch(processthread);
#else
    if (gcsetjmp(&process->jump) == 0) {
        gclongjmp(&processjmpbuf, 1);
    }
#endif
}

void HuPrcVSleep()
{
    HuPrcSleep(0);
}

void HuPrcWakeup(Process *process)
{
    process->sleep_time = 0;
}

void HuPrcDestructorSet2(Process *process, void (*func)(void))
{
    process->dtor = func;
}

void HuPrcDestructorSet(void (*func)(void))
{
    Process *process = HuPrcCurrentGet();
    process->dtor = func;
}

void HuPrcCall(s32 tick)
{
    Process *process;
    s32 ret;
    processcur = processtop;
#ifdef TARGET_PC
    thread_arg = ret = 0;
    processthread = co_active();
    while (1) {
        ret = thread_arg;
        switch (ret) {
            case 2:
                co_delete(processcur->thread);
#else
    ret = gcsetjmp(&processjmpbuf);
    while (1) {
        switch (ret) {
            case 2:
#endif
                HuMemDirectFree(processcur->heap);
            case 1:
                #ifdef NON_MATCHING
                // avoid dereferencing NULL
                if (!processcur) {
                    break;
                }
                #endif
                // memory_block->magic
                if (((u8 *)(processcur->heap))[4] != 165) {
                    printf("stack overlap error.(process pointer %x)\n", processcur);
                    while (1)
                        ;
                }
                else {
                    processcur = processcur->next;
                }
                break;
        }
        process = processcur;
        if (!process) {
            return;
        }
#ifdef __MWERKS__
        // unused
        procfunc = process->jump.lr;
#endif
        if ((process->stat & (PROCESS_STAT_PAUSE | PROCESS_STAT_UPAUSE)) && process->exec != EXEC_KILLED) {
#ifdef TARGET_PC
            thread_arg = 1;
#endif
            ret = 1;
            continue;
        }
        switch (process->exec) {
            case EXEC_SLEEP:
                if (process->sleep_time > 0) {
                    process->sleep_time -= tick;
                    if (process->sleep_time <= 0) {
                        process->sleep_time = 0;
                        process->exec = EXEC_NORMAL;
                    }
                }
#ifdef TARGET_PC
                thread_arg = 1;
#endif
                ret = 1;
                break;

            case EXEC_CHILDWATCH:
                if (process->child) {
#ifdef TARGET_PC
                    thread_arg = 1;
#endif
                    ret = 1;
                }
                else {
                    process->exec = EXEC_NORMAL;
#ifdef TARGET_PC
                    thread_arg = 0;
#endif
                    ret = 0;
                }
                break;

            case EXEC_KILLED:
#ifdef TARGET_PC
                HuPrcEnd();
                break;
#else
                process->jump.lr = (u32)HuPrcEnd;
#endif
            case EXEC_NORMAL:
#ifdef TARGET_PC
                co_switch(process->thread);
#else
                gclongjmp(&process->jump, 1);
#endif
                break;
        }
    }
}

void *HuPrcMemAlloc(s32 size)
{
    Process *process = HuPrcCurrentGet();
    return HuMemMemoryAlloc(process->heap, size, FAKE_RETADDR);
}

void HuPrcMemFree(void *ptr)
{
    HuMemMemoryFree(ptr, FAKE_RETADDR);
}

void HuPrcSetStat(Process *process, u16 value)
{
    process->stat |= value;
}

void HuPrcResetStat(Process *process, u16 value)
{
    process->stat &= ~value;
}

void HuPrcAllPause(s32 flag)
{
    Process *process = processtop;
    if (flag) {
        while (process != NULL) {
            if (!(process->stat & PROCESS_STAT_PAUSE_EN)) {
                HuPrcSetStat(process, PROCESS_STAT_PAUSE);
            }

            process = process->next;
        }
    }
    else {
        while (process != NULL) {
            if (process->stat & PROCESS_STAT_PAUSE) {
                HuPrcResetStat(process, PROCESS_STAT_PAUSE);
            }

            process = process->next;
        }
    }
}

void HuPrcAllUPause(s32 flag)
{
    Process *process = processtop;
    if (flag) {
        while (process != NULL) {
            if (!(process->stat & PROCESS_STAT_UPAUSE_EN)) {
                HuPrcSetStat(process, PROCESS_STAT_UPAUSE);
            }

            process = process->next;
        }
    }
    else {
        while (process != NULL) {
            if (process->stat & PROCESS_STAT_UPAUSE) {
                HuPrcResetStat(process, PROCESS_STAT_UPAUSE);
            }

            process = process->next;
        }
    }
}