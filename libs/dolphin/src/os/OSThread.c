#include <dolphin/os/OSPriv.h>

static vu32 RunQueueBits;
static volatile BOOL RunQueueHint;
static vs32 Reschedule;

static OSThreadQueue RunQueue[32];
static OSThread IdleThread;
static OSThread DefaultThread;
static OSContext IdleContext;
static void DefaultSwitchThreadCallback(OSThread *from, OSThread *to);
static OSSwitchThreadCallback SwitchThreadCallback = DefaultSwitchThreadCallback;

OSThread *__OSCurrentThread : OS_BASE_CACHED + 0x00E4;
OSThreadQueue __OSActiveThreadQueue : OS_BASE_CACHED + 0x00DC;
volatile OSContext __OSCurrentContext : OS_BASE_CACHED + 0x00D4;
volatile OSContext *__OSFPUContext : OS_BASE_CACHED + 0x00D8;

static void DefaultSwitchThreadCallback(OSThread *from, OSThread *to) { }

extern u8 _stack_addr[];
extern u8 _stack_end[];

#define AddTail(queue, thread, link)                                                                                                                 \
    do {                                                                                                                                             \
        OSThread *prev;                                                                                                                              \
                                                                                                                                                     \
        prev = (queue)->tail;                                                                                                                        \
        if (prev == NULL)                                                                                                                            \
            (queue)->head = (thread);                                                                                                                \
        else                                                                                                                                         \
            prev->link.next = (thread);                                                                                                              \
        (thread)->link.prev = prev;                                                                                                                  \
        (thread)->link.next = NULL;                                                                                                                  \
        (queue)->tail = (thread);                                                                                                                    \
    } while (0)

#define AddPrio(queue, thread, link)                                                                                                                 \
    do {                                                                                                                                             \
        OSThread *prev, *next;                                                                                                                       \
                                                                                                                                                     \
        for (next = (queue)->head; next && next->priority <= thread->priority; next = next->link.next)                                               \
            ;                                                                                                                                        \
        if (next == NULL)                                                                                                                            \
            AddTail(queue, thread, link);                                                                                                            \
        else {                                                                                                                                       \
            (thread)->link.next = next;                                                                                                              \
            prev = next->link.prev;                                                                                                                  \
            next->link.prev = (thread);                                                                                                              \
            (thread)->link.prev = prev;                                                                                                              \
            if (prev == NULL)                                                                                                                        \
                (queue)->head = (thread);                                                                                                            \
            else                                                                                                                                     \
                prev->link.next = (thread);                                                                                                          \
        }                                                                                                                                            \
    } while (0)

#define RemoveItem(queue, thread, link)                                                                                                              \
    do {                                                                                                                                             \
        OSThread *next, *prev;                                                                                                                       \
        next = (thread)->link.next;                                                                                                                  \
        prev = (thread)->link.prev;                                                                                                                  \
        if (next == NULL)                                                                                                                            \
            (queue)->tail = prev;                                                                                                                    \
        else                                                                                                                                         \
            next->link.prev = prev;                                                                                                                  \
        if (prev == NULL)                                                                                                                            \
            (queue)->head = next;                                                                                                                    \
        else                                                                                                                                         \
            prev->link.next = next;                                                                                                                  \
    } while (0)

#define RemoveHead(queue, thread, link)                                                                                                              \
    do {                                                                                                                                             \
        OSThread *__next;                                                                                                                            \
        (thread) = (queue)->head;                                                                                                                    \
        __next = (thread)->link.next;                                                                                                                \
        if (__next == NULL)                                                                                                                          \
            (queue)->tail = NULL;                                                                                                                    \
        else                                                                                                                                         \
            __next->link.prev = NULL;                                                                                                                \
        (queue)->head = __next;                                                                                                                      \
    } while (0)

static inline void OSInitMutexQueue(OSMutexQueue *queue)
{
    queue->head = queue->tail = NULL;
}

static inline void OSSetCurrentThread(OSThread *thread)
{
    __OSCurrentThread = thread;
}

void __OSThreadInit()
{
    OSThread *thread = &DefaultThread;
    int prio;

    thread->state = OS_THREAD_STATE_RUNNING;
    thread->attr = OS_THREAD_ATTR_DETACH;
    thread->priority = thread->base = 16;
    thread->suspend = 0;
    thread->val = (void *)-1;
    thread->mutex = NULL;
    OSInitThreadQueue(&thread->queueJoin);
    OSInitMutexQueue(&thread->queueMutex);

    __OSFPUContext = &thread->context;

    OSClearContext(&thread->context);
    OSSetCurrentContext(&thread->context);
    thread->stackBase = (void *)_stack_addr;
    thread->stackEnd = (void *)_stack_end;
    *(thread->stackEnd) = OS_THREAD_STACK_MAGIC;

    OSSetCurrentThread(thread);
    RunQueueBits = 0;
    RunQueueHint = FALSE;
    for (prio = OS_PRIORITY_MIN; prio <= OS_PRIORITY_MAX; ++prio) {
        OSInitThreadQueue(&RunQueue[prio]);
    }

    OSInitThreadQueue(&__OSActiveThreadQueue);
    AddTail(&__OSActiveThreadQueue, thread, linkActive);
    OSClearContext(&IdleContext);
    Reschedule = 0;
}

void OSInitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = NULL;
}

OSThread *OSGetCurrentThread()
{
    return __OSCurrentThread;
}

s32 OSDisableScheduler()
{
    BOOL enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    count = Reschedule++;
    OSRestoreInterrupts(enabled);
    return count;
}

s32 OSEnableScheduler()
{
    BOOL enabled;
    s32 count;

    enabled = OSDisableInterrupts();
    count = Reschedule--;
    OSRestoreInterrupts(enabled);
    return count;
}

static void SetRun(OSThread *thread)
{
    thread->queue = &RunQueue[thread->priority];
    AddTail(thread->queue, thread, link);
    RunQueueBits |= 1u << (OS_PRIORITY_MAX - thread->priority);
    RunQueueHint = TRUE;
}
#pragma dont_inline on
static void UnsetRun(OSThread *thread)
{
    OSThreadQueue *queue;
    queue = thread->queue;
    RemoveItem(queue, thread, link);
    if (queue->head == 0)
        RunQueueBits &= ~(1u << (OS_PRIORITY_MAX - thread->priority));
    thread->queue = NULL;
}
#pragma dont_inline reset

OSPriority __OSGetEffectivePriority(OSThread *thread)
{
    OSPriority priority;
    OSMutex *mutex;
    OSThread *blocked;

    priority = thread->base;
    for (mutex = thread->queueMutex.head; mutex; mutex = mutex->link.next) {
        blocked = mutex->queue.head;
        if (blocked && blocked->priority < priority) {
            priority = blocked->priority;
        }
    }
    return priority;
}

static OSThread *SetEffectivePriority(OSThread *thread, OSPriority priority)
{
    switch (thread->state) {
        case OS_THREAD_STATE_READY:
            UnsetRun(thread);
            thread->priority = priority;
            SetRun(thread);
            break;
        case OS_THREAD_STATE_WAITING:
            RemoveItem(thread->queue, thread, link);
            thread->priority = priority;
            AddPrio(thread->queue, thread, link);
            if (thread->mutex) {
                return thread->mutex->thread;
            }
            break;
        case OS_THREAD_STATE_RUNNING:
            RunQueueHint = TRUE;
            thread->priority = priority;
            break;
    }
    return NULL;
}

static void UpdatePriority(OSThread *thread)
{
    OSPriority priority;

    do {
        if (0 < thread->suspend) {
            break;
        }
        priority = __OSGetEffectivePriority(thread);
        if (thread->priority == priority) {
            break;
        }
        thread = SetEffectivePriority(thread, priority);
    } while (thread);
}

static void __OSSwitchThread(OSThread *nextThread)
{
    OSSetCurrentThread(nextThread);
    OSSetCurrentContext(&nextThread->context);
    OSLoadContext(&nextThread->context);
}

static OSThread *SelectThread(BOOL yield)
{
    OSContext *currentContext;
    OSThread *currentThread;
    OSThread *nextThread;
    OSPriority priority;
    OSThreadQueue *queue;

    if (0 < Reschedule) {
        return 0;
    }

    currentContext = OSGetCurrentContext();
    currentThread = OSGetCurrentThread();
    if (currentContext != &currentThread->context) {
        return 0;
    }

    if (currentThread) {
        if (currentThread->state == OS_THREAD_STATE_RUNNING) {
            if (!yield) {
                priority = __cntlzw(RunQueueBits);
                if (currentThread->priority <= priority) {
                    return 0;
                }
            }
            currentThread->state = OS_THREAD_STATE_READY;
            SetRun(currentThread);
        }

        if (!(currentThread->context.state & OS_CONTEXT_STATE_EXC) && OSSaveContext(&currentThread->context)) {
            return 0;
        }
    }

    OSSetCurrentThread(NULL);
    if (RunQueueBits == 0) {
        OSSetCurrentContext(&IdleContext);
        do {
            OSEnableInterrupts();
            while (RunQueueBits == 0)
                ;
            OSDisableInterrupts();
        } while (RunQueueBits == 0);

        OSClearContext(&IdleContext);
    }

    RunQueueHint = FALSE;

    priority = __cntlzw(RunQueueBits);
    queue = &RunQueue[priority];
    RemoveHead(queue, nextThread, link);
    if (queue->head == 0) {
        RunQueueBits &= ~(1u << (OS_PRIORITY_MAX - priority));
    }
    nextThread->queue = NULL;
    nextThread->state = OS_THREAD_STATE_RUNNING;
    __OSSwitchThread(nextThread);
    return nextThread;
}

void __OSReschedule()
{
    if (!RunQueueHint) {
        return;
    }

    SelectThread(FALSE);
}

void OSYieldThread(void)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    SelectThread(TRUE);
    OSRestoreInterrupts(enabled);
}

int OSCreateThread(struct OSThread * thread, void * (* func)(void *), void * param, void * stack, unsigned long stackSize, long priority, unsigned short attr) {
    int enabled;
    unsigned long sp;

    // why check this for an assert just to check it again right after?
    if ((priority < 0) || (priority > 0x1F)) {
        return 0;
    }

    thread->state = 1;
    thread->attr = attr & 1U;
    thread->base = priority;
    thread->priority = priority;
    thread->suspend = 1;
    thread->val = (void*)-1;
    thread->mutex = 0;
    OSInitThreadQueue(&thread->queueJoin);
    OSInitThreadQueue((void*)&thread->queueMutex); // why
    sp = (u32)stack;
    sp &= ~7;
    sp -= 8;
    ((u32*)sp)[0] = 0; 
    ((u32*)sp)[1] = 0;
    OSInitContext(&thread->context, (u32)func, sp);
    thread->context.lr = (unsigned long)&OSExitThread;
    thread->context.gpr[3] = (unsigned long)param;
    thread->stackBase = stack;
    thread->stackEnd = (void*)((unsigned int)stack - stackSize);
    *thread->stackEnd = 0xDEADBABE;
    enabled = OSDisableInterrupts();

    AddTail(&__OSActiveThreadQueue, thread, linkActive);

    OSRestoreInterrupts(enabled);
    return 1;
}

void OSExitThread(void *val)
{
    int enabled = OSDisableInterrupts();
    struct OSThread *currentThread = OSGetCurrentThread();

    OSClearContext(&currentThread->context);
    if (currentThread->attr & 1) {
        RemoveItem(&__OSActiveThreadQueue, currentThread, linkActive);
        currentThread->state = 0;
    }
    else {
        currentThread->state = 8;
        currentThread->val = val;
    }
    __OSUnlockAllMutex(currentThread);
    OSWakeupThread(&currentThread->queueJoin);
    RunQueueHint = 1;
    if (RunQueueHint != 0) {
        SelectThread(0);
    }
    OSRestoreInterrupts(enabled);
}

void OSCancelThread(OSThread *thread)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();

    switch (thread->state) {
        case OS_THREAD_STATE_READY:
            if (!(0 < thread->suspend)) {
                UnsetRun(thread);
            }
            break;
        case OS_THREAD_STATE_RUNNING:
            RunQueueHint = TRUE;
            break;
        case OS_THREAD_STATE_WAITING:
            RemoveItem(thread->queue, thread, link);
            thread->queue = NULL;
            if (!(0 < thread->suspend) && thread->mutex) {
                UpdatePriority(thread->mutex->thread);
            }
            break;
        default:
            OSRestoreInterrupts(enabled);
            return;
    }

    OSClearContext(&thread->context);
    if (thread->attr & OS_THREAD_ATTR_DETACH) {
        RemoveItem(&__OSActiveThreadQueue, thread, linkActive);
        thread->state = 0;
    }
    else {
        thread->state = OS_THREAD_STATE_MORIBUND;
    }

    __OSUnlockAllMutex(thread);

    OSWakeupThread(&thread->queueJoin);

    __OSReschedule();
    OSRestoreInterrupts(enabled);

    return;
}

s32 OSResumeThread(OSThread *thread)
{
    BOOL enabled;
    s32 suspendCount;

    enabled = OSDisableInterrupts();
    suspendCount = thread->suspend--;
    if (thread->suspend < 0) {
        thread->suspend = 0;
    }
    else if (thread->suspend == 0) {
        switch (thread->state) {
            case OS_THREAD_STATE_READY:
                thread->priority = __OSGetEffectivePriority(thread);
                SetRun(thread);
                break;
            case OS_THREAD_STATE_WAITING:
                RemoveItem(thread->queue, thread, link);
                thread->priority = __OSGetEffectivePriority(thread);
                AddPrio(thread->queue, thread, link);
                if (thread->mutex) {
                    UpdatePriority(thread->mutex->thread);
                }
                break;
        }
        __OSReschedule();
    }
    OSRestoreInterrupts(enabled);
    return suspendCount;
}

s32 OSSuspendThread(OSThread *thread)
{
    BOOL enabled;
    s32 suspendCount;

    enabled = OSDisableInterrupts();
    suspendCount = thread->suspend++;
    if (suspendCount == 0) {
        switch (thread->state) {
            case OS_THREAD_STATE_RUNNING:
                RunQueueHint = TRUE;
                thread->state = OS_THREAD_STATE_READY;
                break;
            case OS_THREAD_STATE_READY:
                UnsetRun(thread);
                break;
            case OS_THREAD_STATE_WAITING:
                RemoveItem(thread->queue, thread, link);
                thread->priority = 32;
                AddTail(thread->queue, thread, link);
                if (thread->mutex) {
                    UpdatePriority(thread->mutex->thread);
                }
                break;
        }

        __OSReschedule();
    }
    OSRestoreInterrupts(enabled);
    return suspendCount;
}

void OSSleepThread(OSThreadQueue *queue)
{
    BOOL enabled;
    OSThread *currentThread;

    enabled = OSDisableInterrupts();
    currentThread = OSGetCurrentThread();

    currentThread->state = OS_THREAD_STATE_WAITING;
    currentThread->queue = queue;
    AddPrio(queue, currentThread, link);
    RunQueueHint = TRUE;
    __OSReschedule();
    OSRestoreInterrupts(enabled);
}

void OSWakeupThread(OSThreadQueue *queue)
{
    BOOL enabled;
    OSThread *thread;

    enabled = OSDisableInterrupts();
    while (queue->head) {
        RemoveHead(queue, thread, link);
        thread->state = OS_THREAD_STATE_READY;
        if (!(0 < thread->suspend)) {
            SetRun(thread);
        }
    }
    __OSReschedule();
    OSRestoreInterrupts(enabled);
}

void OSClearStack(u8 val)
{
    register u32 sp;
    register u32 *p;
    register u32 pattern;

    pattern = ((u32)val << 24) | ((u32)val << 16) | ((u32)val << 8) | (u32)val;
    sp = OSGetStackPointer();
    for (p = __OSCurrentThread->stackEnd + 1; p < (u32 *)sp; ++p) {
        *p = pattern;
    }
}

struct OSThread *OSSetIdleFunction(void (*idleFunction)(void *), void *param, void *stack, unsigned long stackSize)
{
    if (idleFunction) {
        if (IdleThread.state == 0) {
            OSCreateThread(&IdleThread, (void *)idleFunction, param, stack, stackSize, 0x1F, 1);
            OSResumeThread(&IdleThread);
            return &IdleThread;
        }
    }
    else if (IdleThread.state != 0) {
        OSCancelThread(&IdleThread);
    }
    return NULL;
}
