#ifndef OS_DOLPHIN_DOLPHIN_TRK_GLUE_H
#define OS_DOLPHIN_DOLPHIN_TRK_GLUE_H

#include "dolphin/os.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*DBCommFunc)(void);
typedef u32 (*DBPollFunc)(void);
typedef void (*DBCommInitFunc)(volatile u8**, __OSInterruptHandler);
typedef int (*DBCommReadFunc)(void*, size_t);
typedef int (*DBCommWriteFunc)(const void*, size_t);

typedef struct DBCommTable {
	DBCommInitFunc initialize_func;
	DBCommFunc init_interrupts_func;
	DBPollFunc peek_func;
	DBCommReadFunc read_func;
	DBCommWriteFunc write_func;
	DBCommFunc open_func;
	DBCommFunc close_func;
} DBCommTable;

DSError TRKInitializeIntDrivenUART(u32 param_0, u32 param_1, u32 param_2,
                                   volatile u8** param_3);

void UnreserveEXI2Port(void);
void ReserveEXI2Port(void);
int TRKPollUART(void);
UARTError TRKReadUARTN(void* bytes, u32 length);
UARTError TRKWriteUARTN(const void* bytes, u32 length);
void TRKLoadContext(OSContext* ctx, u32 r4);
int InitMetroTRKCommTable(int hwId);
void EnableEXI2Interrupts(void);
void TRK_board_display(char* str);

#ifdef __cplusplus
}
#endif

#endif /* OS_DOLPHIN_DOLPHIN_TRK_GLUE_H */
