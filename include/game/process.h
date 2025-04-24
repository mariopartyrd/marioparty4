#ifndef _GAME_PROCESS_H
#define _GAME_PROCESS_H

#include "dolphin/types.h"

#ifdef TARGET_PC
#include <stdio.h>
#include "libco.h"
#else
#include "game/jmp.h"
#endif

#define PROCESS_STAT_PAUSE 0x1
#define PROCESS_STAT_UPAUSE 0x2
#define PROCESS_STAT_PAUSE_EN 0x4
#define PROCESS_STAT_UPAUSE_EN 0x8

typedef struct process {
    struct process *next;
    struct process *prev;
    struct process *child;
    struct process *parent;
    struct process *next_child;
    struct process *first_child;
    void *heap;
    u16 exec;
    u16 stat;
    u16 prio;
    s32 sleep_time;
#ifdef TARGET_PC
    cothread_t thread;
#else
    uintptr_t base_sp;
    jmp_buf jump;
#endif
    void (*dtor)(void);
    void *user_data;
} Process;

void HuPrcInit(void);
void HuPrcEnd(void);
Process *HuPrcCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size);
void HuPrcChildLink(Process *parent, Process *child);
void HuPrcChildUnlink(Process *process);
Process *HuPrcChildCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size, Process *parent);
void HuPrcChildWatch(void);
Process *HuPrcCurrentGet(void);
s32 HuPrcKill(Process *process);
void HuPrcChildKill(Process *process);
void HuPrcSleep(s32 time);
void HuPrcVSleep();
void HuPrcWakeup(Process *process);
void HuPrcDestructorSet2(Process *process, void (*func)(void));
void HuPrcDestructorSet(void (*func)(void));
void HuPrcCall(s32 tick);
void *HuPrcMemAlloc(s32 size);
void HuPrcMemFree(void *ptr);
void HuPrcSetStat(Process *process, u16 value);
void HuPrcResetStat(Process *process, u16 value);
void HuPrcAllPause(s32 flag);
void HuPrcAllUPause(s32 flag);

#endif
