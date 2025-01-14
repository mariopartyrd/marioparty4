#ifndef MSMSTREAM_H
#define MSMSTREAM_H

#include "dolphin/types.h"

void msmStreamPeriodicProc(void);
void msmStreamSetOutputMode(s32);
void msmStreamAmemFree(void);
s32 msmStreamAmemAlloc(void);
s32 msmStreamInit(char *);

#endif
