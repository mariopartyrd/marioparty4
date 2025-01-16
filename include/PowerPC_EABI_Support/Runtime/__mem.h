#ifndef _RUNTIME_MEM_H
#define _RUNTIME_MEM_H

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

__declspec(section ".init") void* memcpy(void* dest, const void* src, size_t n);
__declspec(section ".init") void* memset(void* dest, int val, size_t count);

#ifdef __cplusplus
}
#endif

#endif
