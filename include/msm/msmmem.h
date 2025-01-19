#ifndef MSMMEM_H
#define MSMMEM_H

#include "dolphin/types.h"

void msmMemFree(void *ptr);
void *msmMemAlloc(u32 sze);
void msmMemInit(void *ptr, u32 size);

#endif
