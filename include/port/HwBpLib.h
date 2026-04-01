/* HwBpLib.h - Hardware Breakpoint Library (C translation) */
/*
MIT License

Copyright (c) 2019 Artem Tokmakov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#pragma once
#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/* ── Enums ────────────────────────────────────────────────────────────────── */

typedef enum {
    HWBP_SUCCESS,
    HWBP_CANT_GET_THREAD_CONTEXT,
    HWBP_CANT_SET_THREAD_CONTEXT,
    HWBP_NO_AVAILABLE_REGISTERS,
    HWBP_BAD_WHEN,
    HWBP_BAD_SIZE
} HwBpResult;

typedef enum {
    HWBP_WHEN_READ_OR_WRITTEN,
    HWBP_WHEN_WRITTEN,
    HWBP_WHEN_EXECUTED
} HwBpWhen;

/* ── Breakpoint struct ────────────────────────────────────────────────────── */

typedef struct {
    uint8_t   registerIndex;
    HwBpResult error;
} HwBpBreakpoint;

static HwBpBreakpoint HwBp_MakeFailed(HwBpResult result) {
    HwBpBreakpoint bp;
    bp.registerIndex = 0;
    bp.error         = result;
    return bp;
}

/* ── DR7 bit helpers ──────────────────────────────────────────────────────── */

static inline void dr7_set(uint64_t* dr7, int bit, bool value) {
    if (value)
        *dr7 |=  (UINT64_C(1) << bit);
    else
        *dr7 &= ~(UINT64_C(1) << bit);
}

static inline bool dr7_get(uint64_t dr7, int bit) {
    return (dr7 >> bit) & 1;
}

/* ── Internal context helper ──────────────────────────────────────────────── */

/* Callback signatures */
typedef HwBpBreakpoint (*HwBp_ActionFn)(CONTEXT* ctx, const bool busyRegs[4], void* userData);
typedef HwBpBreakpoint (*HwBp_FailureFn)(HwBpResult code);

static HwBpBreakpoint HwBp_UpdateThreadContext(
    HwBp_ActionFn  action,
    HwBp_FailureFn failure,
    void*          userData)
{
    CONTEXT ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    if (GetThreadContext(GetCurrentThread(), &ctx) == FALSE)
        return failure(HWBP_CANT_GET_THREAD_CONTEXT);

    bool busyRegs[4] = { false, false, false, false };
    if (ctx.Dr7 &  1) busyRegs[0] = true;
    if (ctx.Dr7 &  4) busyRegs[1] = true;
    if (ctx.Dr7 & 16) busyRegs[2] = true;
    if (ctx.Dr7 & 64) busyRegs[3] = true;

    HwBpBreakpoint result = action(&ctx, busyRegs, userData);

    if (SetThreadContext(GetCurrentThread(), &ctx) == FALSE)
        return failure(HWBP_CANT_SET_THREAD_CONTEXT);

    return result;
}

/* ── Set ──────────────────────────────────────────────────────────────────── */

typedef struct {
    const void* onPointer;
    uint8_t     size;
    HwBpWhen    when;
} HwBp_SetParams;

static HwBpBreakpoint HwBp_SetAction(CONTEXT* ctx, const bool busyRegs[4], void* userData) {
    HwBp_SetParams* p = (HwBp_SetParams*)userData;

    /* Find a free debug register */
    int regIdx = -1;
    for (int i = 0; i < 4; i++) {
        if (!busyRegs[i]) { regIdx = i; break; }
    }
    if (regIdx < 0)
        return HwBp_MakeFailed(HWBP_NO_AVAILABLE_REGISTERS);

    /* Assign the address to the appropriate DR register */
    DWORD_PTR addr = (DWORD_PTR)(uintptr_t)p->onPointer;
    switch (regIdx) {
        case 0: ctx->Dr0 = addr; break;
        case 1: ctx->Dr1 = addr; break;
        case 2: ctx->Dr2 = addr; break;
        case 3: ctx->Dr3 = addr; break;
        default:
            assert(!"Impossible: register index out of range");
            exit(EXIT_FAILURE);
    }

    uint64_t dr7 = 0;
    memcpy(&dr7, &ctx->Dr7, sizeof(dr7));

    /* Enable local breakpoint for this register */
    dr7_set(&dr7, regIdx * 2, true);

    /* Condition (R/W) bits — bits 16+regIdx*4 and 16+regIdx*4+1 */
    switch (p->when) {
        case HWBP_WHEN_READ_OR_WRITTEN:
            dr7_set(&dr7, 16 + regIdx * 4,     true);
            dr7_set(&dr7, 16 + regIdx * 4 + 1, true);
            break;
        case HWBP_WHEN_WRITTEN:
            dr7_set(&dr7, 16 + regIdx * 4,     true);
            dr7_set(&dr7, 16 + regIdx * 4 + 1, false);
            break;
        case HWBP_WHEN_EXECUTED:
            dr7_set(&dr7, 16 + regIdx * 4,     false);
            dr7_set(&dr7, 16 + regIdx * 4 + 1, false);
            break;
        default:
            return HwBp_MakeFailed(HWBP_BAD_WHEN);
    }

    /* Size (LEN) bits — bits 16+regIdx*4+2 and 16+regIdx*4+3 */
    switch (p->size) {
        case 1:
            dr7_set(&dr7, 16 + regIdx * 4 + 2, false);
            dr7_set(&dr7, 16 + regIdx * 4 + 3, false);
            break;
        case 2:
            dr7_set(&dr7, 16 + regIdx * 4 + 2, true);
            dr7_set(&dr7, 16 + regIdx * 4 + 3, false);
            break;
        case 8:
            dr7_set(&dr7, 16 + regIdx * 4 + 2, false);
            dr7_set(&dr7, 16 + regIdx * 4 + 3, true);
            break;
        case 4:
            dr7_set(&dr7, 16 + regIdx * 4 + 2, true);
            dr7_set(&dr7, 16 + regIdx * 4 + 3, true);
            break;
        default:
            return HwBp_MakeFailed(HWBP_BAD_SIZE);
    }

    memcpy(&ctx->Dr7, &dr7, sizeof(dr7));

    HwBpBreakpoint bp;
    bp.registerIndex = (uint8_t)regIdx;
    bp.error         = HWBP_SUCCESS;
    return bp;
}

static HwBpBreakpoint HwBp_DefaultFailure(HwBpResult code) {
    return HwBp_MakeFailed(code);
}

static inline HwBpBreakpoint HwBp_Set(const void* onPointer, uint8_t size, HwBpWhen when) {
    HwBp_SetParams params;
    params.onPointer = onPointer;
    params.size      = size;
    params.when      = when;
    return HwBp_UpdateThreadContext(HwBp_SetAction, HwBp_DefaultFailure, &params);
}

/* ── Remove ───────────────────────────────────────────────────────────────── */

static HwBpBreakpoint HwBp_RemoveAction(CONTEXT* ctx, const bool busyRegs[4], void* userData) {
    (void)busyRegs;
    HwBpBreakpoint* bp = (HwBpBreakpoint*)userData;

    uint64_t dr7 = 0;
    memcpy(&dr7, &ctx->Dr7, sizeof(dr7));

    dr7_set(&dr7, bp->registerIndex * 2, false);

    memcpy(&ctx->Dr7, &dr7, sizeof(dr7));

    HwBpBreakpoint empty;
    empty.registerIndex = 0;
    empty.error         = HWBP_SUCCESS;
    return empty;
}

static inline void HwBp_Remove(const HwBpBreakpoint* bp) {
    if (bp->error != HWBP_SUCCESS)
        return;

    HwBp_UpdateThreadContext(HwBp_RemoveAction, HwBp_DefaultFailure, (void*)bp);
}