#ifndef _GAME_PROCESS_H
#define _GAME_PROCESS_H

#include "game/jmp.h"
#include "dolphin/types.h"

#ifndef __MWERKS__
#include <stdio.h>
#endif

#define PROCESS_STAT_PAUSE 0x1
#define PROCESS_STAT_UPAUSE 0x2
#define PROCESS_STAT_PAUSE_EN 0x4
#define PROCESS_STAT_UPAUSE_EN 0x8

#define HUPRC_EXEC_NORMAL 0
#define HUPRC_EXEC_SLEEP 1
#define HUPRC_EXEC_CHILDWATCH 2
#define HUPRC_EXEC_KILLED 3

typedef struct Process_s HUPROCESS;

typedef struct Process_s {
    HUPROCESS *next;
    HUPROCESS *prev;
    HUPROCESS *child;
    HUPROCESS *parent;
    HUPROCESS *next_child;
    HUPROCESS *first_child;
    void *heap;
    u16 exec;
    u16 stat;
    u16 prio;
    s32 sleep_time;
    u32 base_sp;
    jmp_buf jump;
    void (*dtor)(void);
    void *user_data; // TODO rename to property
} HUPROCESS;

void HuPrcInit(void);
void HuPrcEnd(void);
HUPROCESS *HuPrcCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size);
void HuPrcChildLink(HUPROCESS *parent, HUPROCESS *child);
void HuPrcChildUnlink(HUPROCESS *process);
HUPROCESS *HuPrcChildCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size, HUPROCESS *parent);
void HuPrcChildWatch(void);
HUPROCESS *HuPrcCurrentGet(void);
s32 HuPrcKill(HUPROCESS *process);
void HuPrcChildKill(HUPROCESS *process);
void HuPrcSleep(s32 time);
void HuPrcVSleep();
void HuPrcWakeup(HUPROCESS *process);
void HuPrcDestructorSet2(HUPROCESS *process, void (*func)(void));
void HuPrcDestructorSet(void (*func)(void));
void HuPrcCall(s32 tick);
void *HuPrcMemAlloc(s32 size);
void HuPrcMemFree(void *ptr);
void HuPrcSetStat(HUPROCESS *process, u16 value);
void HuPrcResetStat(HUPROCESS *process, u16 value);
void HuPrcAllPause(s32 flag);
void HuPrcAllUPause(s32 flag);

#endif
