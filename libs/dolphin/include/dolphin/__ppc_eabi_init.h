#ifndef _DOLPHIN__PPC_EABI_INIT
#define _DOLPHIN__PPC_EABI_INIT

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
__declspec(section ".init") void __init_hardware(void);
__declspec(section ".init") void __flush_cache(register void* address, register unsigned int size);

void __init_user(void);
void __init_cpp(void);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN__PPC_EABI_INIT
