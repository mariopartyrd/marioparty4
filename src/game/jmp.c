#include "game/jmp.h"

s32 gcsetjmp(register jmp_buf *jump)
{
    // clang-format off
    asm {
        mflr r5
        mfcr r6
        stw r5, jump->lr
        stw r6, jump->cr
        stw r1, jump->sp
        stw r2, jump->r2
        stmw r13, jump->regs[0]
        mffs f0
        stfd f14, jump->flt_regs[0]
        stfd f15, jump->flt_regs[1]
        stfd f16, jump->flt_regs[2]
        stfd f17, jump->flt_regs[3]
        stfd f18, jump->flt_regs[4]
        stfd f19, jump->flt_regs[5]
        stfd f20, jump->flt_regs[6]
        stfd f21, jump->flt_regs[7]
        stfd f22, jump->flt_regs[8]
        stfd f23, jump->flt_regs[9]
        stfd f24, jump->flt_regs[10]
        stfd f25, jump->flt_regs[11]
        stfd f26, jump->flt_regs[12]
        stfd f27, jump->flt_regs[13]
        stfd f28, jump->flt_regs[14]
        stfd f29, jump->flt_regs[15]
        stfd f30, jump->flt_regs[16]
        stfd f31, jump->flt_regs[17]
        stfd f0, jump->flt_regs[18]
    }
    // clang-format on
    return 0;
}

// clang-format off
asm s32 gclongjmp(register jmp_buf *jump, register s32 status) {
    nofralloc
    lwz r5, jump->lr
    lwz r6, jump->cr
    mtlr r5
    mtcrf 255, r6
    lwz r1, jump->sp
    lwz r2, jump->r2
    lmw r13, jump->regs[0]
    lfd f14, jump->flt_regs[0]
    lfd f15, jump->flt_regs[1]
    lfd f16, jump->flt_regs[2]
    lfd f17, jump->flt_regs[3]
    lfd f18, jump->flt_regs[4]
    lfd f19, jump->flt_regs[5]
    lfd f20, jump->flt_regs[6]
    lfd f21, jump->flt_regs[7]
    lfd f22, jump->flt_regs[8]
    lfd f23, jump->flt_regs[9]
    lfd f24, jump->flt_regs[10]
    lfd f25, jump->flt_regs[11]
    lfd f26, jump->flt_regs[12]
    lfd f27, jump->flt_regs[13]
    lfd f28, jump->flt_regs[14]
    lfd f29, jump->flt_regs[15]
    lfd f30, jump->flt_regs[16]
    lfd f0, jump->flt_regs[18]
    lfd f31, jump->flt_regs[17]
    cmpwi status, 0
    mr r3, status
    mtfsf 255, f0
    bnelr
    li r3, 1
    blr
}
// clang-format on
