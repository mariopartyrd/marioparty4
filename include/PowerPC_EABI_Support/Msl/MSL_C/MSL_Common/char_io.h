#ifndef _MSL_COMMON_CHAR_IO_H
#define _MSL_COMMON_CHAR_IO_H

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"

#ifdef __cplusplus
extern "C" {
#endif

int fputs(const char* str, FILE* stream);
int __put_char(int c, FILE* stream);

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_CHAR_IO_H */
