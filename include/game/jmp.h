#ifndef _GAME_JMP_H
#define _GAME_JMP_H

#ifdef TARGET_PC
#include <setjmp.h>
#include <stdint.h>


#define SETJMP setjmp
#define LONGJMP longjmp

#ifndef _JMP_BUF_DEFINED
#if defined(_M_IX86) || defined(__i386__)
typedef struct __JUMP_BUFFER {
    uint32_t Ebp;
    uint32_t Ebx;
    uint32_t Edi;
    uint32_t Esi;
    uint32_t Esp;
    uint32_t Eip;
    uint32_t Registration;
    uint32_t TryLevel;
    uint32_t Cookie;
    uint32_t UnwindFunc;
    uint32_t UnwindData[6];
} _JUMP_BUFFER;
#elif defined(_M_X64) || defined(__x86_64__)
#ifndef SETJMP_FLOAT128
// TODO do we need to align this?
typedef struct _SETJMP_FLOAT128 {
    uint64_t Part[2];
} SETJMP_FLOAT128;
#endif
typedef struct _JUMP_BUFFER {
    uint64_t Frame;
    uint64_t Rbx;
    uint64_t Rsp;
    uint64_t Rbp;
    uint64_t Rsi;
    uint64_t Rdi;
    uint64_t R12;
    uint64_t R13;
    uint64_t R14;
    uint64_t R15;
    uint64_t Rip;
    uint32_t MxCsr;
    uint16_t FpCsr;
    uint16_t Spare;

    SETJMP_FLOAT128 Xmm6;
    SETJMP_FLOAT128 Xmm7;
    SETJMP_FLOAT128 Xmm8;
    SETJMP_FLOAT128 Xmm9;
    SETJMP_FLOAT128 Xmm10;
    SETJMP_FLOAT128 Xmm11;
    SETJMP_FLOAT128 Xmm12;
    SETJMP_FLOAT128 Xmm13;
    SETJMP_FLOAT128 Xmm14;
    SETJMP_FLOAT128 Xmm15;
} _JUMP_BUFFER;
#elif defined(_M_ARM) || defined(__arm__)
typedef struct _JUMP_BUFFER {
    uint32_t Frame;

    uint32_t R4;
    uint32_t R5;
    uint32_t R6;
    uint32_t R7;
    uint32_t R8;
    uint32_t R9;
    uint32_t R10;
    uint32_t R11;

    uint32_t Sp;
    uint32_t Pc;
    uint32_t Fpscr;
    uint32_t long D[8]; // D8-D15 VFP/NEON regs
} _JUMP_BUFFER;
#elif defined(_M_ARM64) || defined(__aarch64__)
typedef struct _JUMP_BUFFER {
    uint64_t Frame;
    uint64_t Reserved;
    uint64_t X19; // x19 -- x28: callee saved registers
    uint64_t X20;
    uint64_t X21;
    uint64_t X22;
    uint64_t X23;
    uint64_t X24;
    uint64_t X25;
    uint64_t X26;
    uint64_t X27;
    uint64_t X28;
    uint64_t Fp; // x29 frame pointer
    uint64_t Lr; // x30 link register
    uint64_t Sp; // x31 stack pointer
    uint32_t Fpcr; // fp control register
    uint32_t Fpsr; // fp status register

    double D[8]; // D8-D15 FP regs
} _JUMP_BUFFER;
#elif defined(__riscv)
typedef struct _JUMP_BUFFER {
    uint32_t ra;
    uint32_t sp;
    uint32_t s0;
    uint32_t s1; 
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
    uint32_t s8;
    uint32_t s9;
    uint32_t s10;
    uint32_t s11;

    #if __riscv_xlen == 64
    uint64_t fs0;
    uint64_t fs1;
    uint64_t fs2;
    uint64_t fs3;
    uint64_t fs4;
    uint64_t fs5;
    uint64_t fs6;
    uint64_t fs7;
    uint64_t fs8;
    uint64_t fs9;
    uint64_t fs10;
    uint64_t fs11;
    #endif
} _JUMP_BUFFER;
#endif
#endif

#if defined(_M_IX86) || defined(__i386__) || defined(_M_X64) || defined(__x86_64__)
#define SETJMP_SET_IP(jump, func) ((_JUMP_BUFFER *)((jump)))->Eip = (size_t)func
#define SETJMP_SET_SP(jump, sp) ((_JUMP_BUFFER *)((jump)))->Esp = (size_t)sp
#elif defined(_M_ARM) || defined(__arm__)
#define SETJMP_SET_IP(jump, func) ((_JUMP_BUFFER *)((jump)))->Pc = (size_t)func
#define SETJMP_SET_SP(jump, sp) ((_JUMP_BUFFER *)((jump)))->Sp = (size_t)sp
#elif defined(_M_ARM64) || defined(__aarch64__)
#define SETJMP_SET_IP(jump, func) ((_JUMP_BUFFER *)((jump)))->Lr = (size_t)func
#define SETJMP_SET_SP(jump, sp) ((_JUMP_BUFFER *)((jump)))->Sp = (size_t)sp
#elif defined(__riscv)
#define SETJMP_SET_IP(jump, func) ((_JUMP_BUFFER *)((jump)))->ra = (size_t)func
#define SETJMP_SET_SP(jump, sp) ((_JUMP_BUFFER *)((jump)))->sp = (size_t)sp
#endif

#else
#include "dolphin.h"

typedef struct jmp_buf {
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

#define SETJMP(jump) gcsetjmp(&(jump))
#define SETJMP(jump, status) gclongjump(&(jump), (status))

#define SETJMP_SET_IP(jump, func) jmp_buf->lr = (u32)func
#define SETJMP_SET_IP(jump, sp) jmp_buf->sp = (u32)sp
#endif

#endif
