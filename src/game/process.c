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

static jmp_buf processjmpbuf;
static HUPROCESS *processtop;
static HUPROCESS *processcur;
static u16 processcnt;
u32 procfunc;

void HuPrcInit(void)
{
    processcnt = 0;
    processtop = NULL;
}

static void LinkProcess(HUPROCESS** root, HUPROCESS* process) {
    HUPROCESS* src_process = *root;

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
    } else {
        process->next = (*root);
        process->prev = NULL;
        *root = process;
        if (src_process) {
            src_process->prev = process;
        }
    }
}
static void UnlinkProcess(HUPROCESS **root, HUPROCESS *process) {
    if (process->next) {
        process->next->prev = process->prev;
    }
    if (process->prev) {
        process->prev->next = process->next;
    } else {
        *root = process->next;
    }
}

HUPROCESS *HuPrcCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size)
{
    HUPROCESS *process;
    s32 alloc_size;
    void *heap;
    if(stack_size == 0) {
        stack_size = 2048;
    }
    alloc_size = HuMemMemoryAllocSizeGet(sizeof(HUPROCESS))
                    +HuMemMemoryAllocSizeGet(stack_size)
                    +HuMemMemoryAllocSizeGet(extra_size);
    if(!(heap = HuMemDirectMalloc(HEAP_HEAP, alloc_size))) {
        OSReport("process> malloc error size %d\n", alloc_size);
        return NULL;
    }
    HuMemHeapInit(heap, alloc_size);
    process = HuMemMemoryAlloc(heap, sizeof(HUPROCESS), FAKE_RETADDR);
    process->heap = heap;
    process->exec = EXEC_NORMAL;
    process->stat = 0;
    process->prio = prio;
    process->sleep_time = 0;
    process->base_sp = ((u32)HuMemMemoryAlloc(heap, stack_size, FAKE_RETADDR))+stack_size-8;
    gcsetjmp(&process->jump);
    process->jump.lr = (u32)func;
    process->jump.sp = process->base_sp;
    process->dtor = NULL;
    process->user_data = NULL;
    LinkProcess(&processtop, process);
    process->child = NULL;
    process->parent = NULL;
    processcnt++;
    return process;
}

void HuPrcChildLink(HUPROCESS *parent, HUPROCESS *child)
{
    HuPrcChildUnlink(child);
    if(parent->child) {
        parent->child->first_child = child;
    }
    child->next_child = parent->child;
    child->first_child = NULL;
    parent->child = child;
    child->parent = parent;
}

void HuPrcChildUnlink(HUPROCESS *process)
{
    if(process->parent) {
        if(process->next_child) {
            process->next_child->first_child = process->first_child;
        }
        if(process->first_child) {
            process->first_child->next_child = process->next_child;
        } else {
            process->parent->child = process->next_child;
        }
        process->parent = NULL;
    }
}

HUPROCESS *HuPrcChildCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size, HUPROCESS *parent)
{
    HUPROCESS *child = HuPrcCreate(func, prio, stack_size, extra_size);
    HuPrcChildLink(parent, child);
    return child;
}

void HuPrcChildWatch()
{
    HUPROCESS *curr = HuPrcCurrentGet();
    if(curr->child) {
        curr->exec = EXEC_CHILDWATCH;
        if(!gcsetjmp(&curr->jump)) {
            gclongjmp(&processjmpbuf, 1);
        }
    }
}

HUPROCESS *HuPrcCurrentGet()
{
    return processcur;
}

static s32 SetKillStatusProcess(HUPROCESS *process)
{
    if(process->exec != EXEC_KILLED) {
        HuPrcWakeup(process);
        process->exec = EXEC_KILLED;
        return 0;
    } else {
        return -1;
    }
}

s32 HuPrcKill(HUPROCESS *process)
{
    if(process == NULL) {
        process = HuPrcCurrentGet();
    }
    HuPrcChildKill(process);
    HuPrcChildUnlink(process);
    return SetKillStatusProcess(process);
}

void HuPrcChildKill(HUPROCESS *process)
{
    HUPROCESS *child = process->child;
    while(child) {
        if(child->child) {
            HuPrcChildKill(child);
        }
        SetKillStatusProcess(child);
        child = child->next_child;
    }
    process->child = NULL;
}

static void gcTerminateProcess(HUPROCESS *process)
{
    if(process->dtor) {
        process->dtor();
    }
    UnlinkProcess(&processtop, process);
    processcnt--;
    gclongjmp(&processjmpbuf, 2);
}

void HuPrcEnd()
{
    HUPROCESS *process = HuPrcCurrentGet();
    HuPrcChildKill(process);
    HuPrcChildUnlink(process);
    gcTerminateProcess(process);
}

void HuPrcSleep(s32 time)
{
    HUPROCESS *process = HuPrcCurrentGet();
    if(time != 0 && process->exec != EXEC_KILLED) {
        process->exec = EXEC_SLEEP;
        process->sleep_time = time;
    }
    if(!gcsetjmp(&process->jump)) {
        gclongjmp(&processjmpbuf, 1);
    }
}

void HuPrcVSleep()
{
    HuPrcSleep(0);
}

void HuPrcWakeup(HUPROCESS *process)
{
    process->sleep_time = 0;
}

void HuPrcDestructorSet2(HUPROCESS *process, void (*func)(void))
{
    process->dtor = func;
}

void HuPrcDestructorSet(void (*func)(void))
{
    HUPROCESS *process = HuPrcCurrentGet();
    process->dtor = func;
}

void HuPrcCall(s32 tick)
{
    HUPROCESS *process;
    s32 ret;
    processcur = processtop;
    ret = gcsetjmp(&processjmpbuf);
    while(1) {
        switch(ret) {
            case 2:
                HuMemDirectFree(processcur->heap);
            case 1:
                if(((u8 *)(processcur->heap))[4] != 165) {
                    printf("stack overlap error.(process pointer %x)\n", processcur);
                    while(1);
                } else {
                    processcur = processcur->next;
                }
                break;
        }
        process = processcur;
        if(!process) {
            return;
        }
        procfunc = process->jump.lr;
        if((process->stat & (PROCESS_STAT_PAUSE|PROCESS_STAT_UPAUSE)) && process->exec != EXEC_KILLED) {
            ret = 1;
            continue;
        }
        switch(process->exec) {
            case EXEC_SLEEP:
                if(process->sleep_time > 0) {
                    process->sleep_time -= tick;
                    if(process->sleep_time <= 0) {
                        process->sleep_time = 0;
                        process->exec = EXEC_NORMAL;
                    }
                }
                ret = 1;
                break;
                
            case EXEC_CHILDWATCH:
                if(process->child) {
                    ret = 1;
                } else {
                    process->exec = EXEC_NORMAL;
                    ret = 0;
                }
                break;
                
            case EXEC_KILLED:
                process->jump.lr = (u32)HuPrcEnd;
            case EXEC_NORMAL:
                gclongjmp(&process->jump, 1);
                break;
        }
    }
}

void *HuPrcMemAlloc(s32 size)
{
    HUPROCESS *process = HuPrcCurrentGet();
    return HuMemMemoryAlloc(process->heap, size, FAKE_RETADDR);
}

void HuPrcMemFree(void *ptr)
{
    HuMemMemoryFree(ptr, FAKE_RETADDR);
}

void HuPrcSetStat(HUPROCESS *process, u16 value)
{
    process->stat |= value;
}

void HuPrcResetStat(HUPROCESS *process, u16 value)
{
    process->stat &= ~value;
}

void HuPrcAllPause(s32 flag)
{
    HUPROCESS *process = processtop;
    if(flag) {
        while(process != NULL) {
            if(!(process->stat & PROCESS_STAT_PAUSE_EN)) {
                HuPrcSetStat(process, PROCESS_STAT_PAUSE);
            }
            
            process = process->next;
        }
    } else {
        while(process != NULL) {
            if(process->stat & PROCESS_STAT_PAUSE) {
                HuPrcResetStat(process, PROCESS_STAT_PAUSE);
            }
            
            process = process->next;
        }
    }
}

void HuPrcAllUPause(s32 flag)
{
    HUPROCESS *process = processtop;
    if(flag) {
        while(process != NULL) {
            if(!(process->stat & PROCESS_STAT_UPAUSE_EN)) {
                HuPrcSetStat(process, PROCESS_STAT_UPAUSE);
            }
            
            process = process->next;
        }
    } else {
        while(process != NULL) {
            if(process->stat & PROCESS_STAT_UPAUSE) {
                HuPrcResetStat(process, PROCESS_STAT_UPAUSE);
            }
            
            process = process->next;
        }
    }
}
