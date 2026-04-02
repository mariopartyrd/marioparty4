#include "dolphin/dsp.h"
#include "dolphin/hw_regs.h"

DSPTaskInfo *__DSP_curr_task;
DSPTaskInfo *__DSP_first_task;
DSPTaskInfo *__DSP_last_task;
DSPTaskInfo *__DSP_tmp_task;
DSPTaskInfo *__DSP_rude_task;

BOOL __DSP_rude_task_pending;

void __DSPHandler(__OSInterrupt, OSContext *context)
{
    DSPTaskInfo *tmp_task;
    OSContext exceptionContext;
    u16 tmp;
    u32 mail;

    tmp = __DSPRegs[5];
    tmp = (u16)(tmp & ~0x28) | 0x80;
    __DSPRegs[5] = tmp;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    while (!DSPCheckMailFromDSP())
        ;
    mail = DSPReadMailFromDSP();

    if ((__DSP_curr_task->flags & DSP_TASK_FLAG_CANCEL) && (mail == 0xDCD10002)) {
        mail = 0xDCD10003;
    }

    switch (mail) {
        case 0xDCD10000:
            __DSP_curr_task->state = DSP_TASK_STATE_RUN;

            if (__DSP_curr_task->init_cb) {
                (*(__DSP_curr_task->init_cb))((void *)(__DSP_curr_task));
            }
            break;
        case 0xDCD10001:
            __DSP_curr_task->state = DSP_TASK_STATE_RUN;
            if (__DSP_curr_task->res_cb) {
                (*(__DSP_curr_task->res_cb))((void *)(__DSP_curr_task));
            }
            break;
        case 0xDCD10002:
            if (__DSP_rude_task_pending) {

                if (__DSP_curr_task == __DSP_rude_task) {
                    DSPSendMailToDSP(0xCDD10003);
                    while (DSPCheckMailToDSP()) { }

                    __DSP_rude_task = NULL;
                    __DSP_rude_task_pending = FALSE;

                    if (__DSP_curr_task->res_cb) {
                        (*(__DSP_curr_task->res_cb))((void *)(__DSP_curr_task));
                    }

                    break;
                }
                else {
                    DSPSendMailToDSP(0xCDD10001);
                    while (DSPCheckMailToDSP())
                        ;
                    __DSP_exec_task(__DSP_curr_task, __DSP_rude_task);

                    __DSP_curr_task->state = DSP_TASK_STATE_YIELD;
                    __DSP_curr_task = __DSP_rude_task;

                    __DSP_rude_task = NULL;
                    __DSP_rude_task_pending = FALSE;

                    break;
                }
            }

            if (__DSP_curr_task->next == NULL) {

                if (__DSP_curr_task == __DSP_first_task) {

                    DSPSendMailToDSP(0xCDD10003);
                    while (DSPCheckMailToDSP())
                        ;

                    if (__DSP_curr_task->res_cb) {
                        (*(__DSP_curr_task->res_cb))((void *)(__DSP_curr_task));
                    }
                }
                else {
                    DSPSendMailToDSP(0xCDD10001);
                    while (DSPCheckMailToDSP()) { }

                    __DSP_exec_task(__DSP_curr_task, __DSP_first_task);

                    __DSP_curr_task->state = DSP_TASK_STATE_YIELD;
                    __DSP_curr_task = __DSP_first_task;
                }
            }
            else {

                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP()) { }

                __DSP_exec_task(__DSP_curr_task, __DSP_curr_task->next);

                __DSP_curr_task->state = DSP_TASK_STATE_YIELD;
                __DSP_curr_task = __DSP_curr_task->next;
            }
            break;
        case 0xDCD10003:
            if (__DSP_rude_task_pending) {

                if (__DSP_curr_task->done_cb) {
                    (*(__DSP_curr_task->done_cb))((void *)(__DSP_curr_task));
                }

                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP())
                    ;

                __DSP_exec_task(NULL, __DSP_rude_task);

                __DSP_remove_task(__DSP_curr_task);
                __DSP_curr_task = __DSP_rude_task;

                __DSP_rude_task = NULL;
                __DSP_rude_task_pending = FALSE;

                break;
            }

            if (__DSP_curr_task->next == NULL) {

                if (__DSP_curr_task == __DSP_first_task) {

                    if (__DSP_curr_task->done_cb) {
                        (*(__DSP_curr_task->done_cb))((void *)(__DSP_curr_task));
                    }

                    DSPSendMailToDSP(0xCDD10002);
                    while (DSPCheckMailToDSP())
                        ;

                    __DSP_curr_task->state = DSP_TASK_STATE_DONE;

                    __DSP_remove_task(__DSP_curr_task);
                }
                else {

                    if (__DSP_curr_task->done_cb) {
                        (*(__DSP_curr_task->done_cb))((void *)(__DSP_curr_task));
                    }

                    DSPSendMailToDSP(0xCDD10001);
                    while (DSPCheckMailToDSP())
                        ;

                    __DSP_curr_task->state = DSP_TASK_STATE_DONE;
                    __DSP_exec_task(NULL, __DSP_first_task);

                    __DSP_curr_task = __DSP_first_task;
                    __DSP_remove_task(__DSP_last_task);
                }
            }
            else {
                if (__DSP_curr_task->done_cb) {
                    (*(__DSP_curr_task->done_cb))((void *)(__DSP_curr_task));
                }
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP())
                    ;

                __DSP_curr_task->state = DSP_TASK_STATE_DONE;
                __DSP_exec_task(NULL, __DSP_curr_task->next);

                __DSP_curr_task = __DSP_curr_task->next;
                __DSP_remove_task(__DSP_curr_task->prev);
            }
            break;

        case 0xDCD10004:

            if (__DSP_curr_task->req_cb) {
                (*(__DSP_curr_task->req_cb))((void *)(__DSP_curr_task));
            }
            break;
        default:
            break;
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

void __DSP_exec_task(DSPTaskInfo *curr, DSPTaskInfo *next)
{
    if (curr) {
        DSPSendMailToDSP((u32)(curr->dram_mmem_addr));
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP((u32)(curr->dram_length));
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP((u32)(curr->dram_addr));
        while (DSPCheckMailToDSP())
            ;
    }
    else {

        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP())
            ;
    }

    DSPSendMailToDSP((u32)(next->iram_mmem_addr));
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP((u32)(next->iram_length));
    while (DSPCheckMailToDSP())
        ;
    DSPSendMailToDSP((u32)(next->iram_addr));
    while (DSPCheckMailToDSP())
        ;

    if (DSP_TASK_STATE_INIT == next->state) {
        DSPSendMailToDSP((u32)(next->dsp_init_vector));
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP())
            ;
    }
    else {
        DSPSendMailToDSP((u32)(next->dsp_resume_vector));
        while (DSPCheckMailToDSP())
            ;
        DSPSendMailToDSP((u32)(next->dram_mmem_addr));
        while (DSPCheckMailToDSP())
            ;

        DSPSendMailToDSP((u32)(next->dram_length));
        while (DSPCheckMailToDSP())
            ;

        DSPSendMailToDSP((u32)(next->dram_addr));
        while (DSPCheckMailToDSP())
            ;
    }
}

#define MSG_BASE 0x80F30000
void __DSP_boot_task(DSPTaskInfo *task)
{

    volatile u32 mail;

    while (!DSPCheckMailFromDSP())
        ;

    mail = DSPReadMailFromDSP();

    DSPSendMailToDSP(MSG_BASE | 0xA001);
    while (DSPCheckMailToDSP()) { }
    DSPSendMailToDSP((u32)(task->iram_mmem_addr));
    while (DSPCheckMailToDSP()) { }

    DSPSendMailToDSP(MSG_BASE | 0xC002);
    while (DSPCheckMailToDSP()) { }
    DSPSendMailToDSP((u32)(task->iram_addr & 0xffff));
    while (DSPCheckMailToDSP()) { }

    DSPSendMailToDSP(MSG_BASE | 0xA002);
    while (DSPCheckMailToDSP()) { }
    DSPSendMailToDSP(task->iram_length);
    while (DSPCheckMailToDSP()) { }

    DSPSendMailToDSP(MSG_BASE | 0xB002);
    while (DSPCheckMailToDSP()) { }
    DSPSendMailToDSP(0x00000000);
    while (DSPCheckMailToDSP()) { }

    DSPSendMailToDSP(MSG_BASE | 0xD001);
    while (DSPCheckMailToDSP()) { }
    DSPSendMailToDSP((u32)(0xffff & task->dsp_init_vector));
    while (DSPCheckMailToDSP()) { }

    __DSP_debug_printf("DSP is booting task: 0x%08X\n", task);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM MMEM ADDR: 0x%08X\n", (u32)(task->iram_mmem_addr));
    __DSP_debug_printf("__DSP_boot_task()  : IRAM DSP ADDR : 0x%08X\n", (u32)(task->iram_addr));
    __DSP_debug_printf("__DSP_boot_task()  : IRAM LENGTH   : 0x%08X\n", (u32)(task->iram_length));
    __DSP_debug_printf("__DSP_boot_task()  : DRAM MMEM ADDR: 0x%08X\n", (u32)(task->dram_length));
    __DSP_debug_printf("__DSP_boot_task()  : Start Vector  : 0x%08X\n", (u32)(task->dsp_init_vector));
}

void __DSP_insert_task(DSPTaskInfo *task)
{

    DSPTaskInfo *temp;

    if (__DSP_first_task == NULL) {
        __DSP_first_task = __DSP_last_task = __DSP_curr_task = task;
        task->next = task->prev = NULL;
    }
    else {
        temp = __DSP_first_task;

        while (temp) {
            if (task->priority < temp->priority) {
                task->prev = temp->prev;
                temp->prev = task;
                task->next = temp;
                if (task->prev == NULL) {
                    __DSP_first_task = task;
                }
                else {
                    (task->prev)->next = task;
                }
                break;
            }
            temp = temp->next;
        }

        if (temp == NULL) {
            __DSP_last_task->next = task;
            task->next = NULL;
            task->prev = __DSP_last_task;
            __DSP_last_task = task;
        }
    }
}

void __DSP_add_task(DSPTaskInfo *task)
{
    if (__DSP_last_task == NULL) {
        __DSP_first_task = __DSP_last_task = __DSP_curr_task = task;
        task->next = task->prev = NULL;
    }
    else {
        __DSP_last_task->next = task;
        task->next = NULL;
        task->prev = __DSP_last_task;
        __DSP_last_task = task;
    }

    task->state = DSP_TASK_STATE_INIT;

    __DSP_debug_printf("__DSP_add_task() : Added task    : 0x%08X\n", task);
}

void __DSP_remove_task(DSPTaskInfo *task)
{

    task->flags = DSP_TASK_FLAG_CLEARALL;
    task->state = DSP_TASK_STATE_DONE;

    if (__DSP_first_task == task) {
        if (task->next) {
            __DSP_first_task = (task->next);
            task->next->prev = NULL;
        }
        else {
            __DSP_first_task = __DSP_last_task = __DSP_curr_task = NULL;
        }
    }
    else if (__DSP_last_task == task) {
        __DSP_last_task = (task->prev);
        task->prev->next = NULL;
        __DSP_curr_task = __DSP_first_task;
    }
    else {
        __DSP_curr_task = task->next;
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }
}
