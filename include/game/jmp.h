#ifndef _GAME_JMP_H
#define _GAME_JMP_H

#include "dolphin.h"

typedef struct jump_buf {
    u32 lr;
    u32 cr;
    u32 sp;
    u32 r2;
    u32 pad;
    u32 regs[19];
    double flt_regs[19];
} jmp_buf;

s32 gcsetjmp(jmp_buf *jump);
s32 gclongjmp(jmp_buf *jump, s32 status);

#endif