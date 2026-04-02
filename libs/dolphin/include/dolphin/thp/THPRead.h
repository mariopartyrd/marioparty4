#ifndef _THP_THPREAD_H
#define _THP_THPREAD_H

#include "dolphin/thp/THPBuffer.h"
#include "dolphin/os.h"

static void* Reader(void* arg);

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

BOOL CreateReadThread(OSPriority priority);
void ReadThreadStart();
void ReadThreadCancel();
OSMessage PopReadedBuffer();
BOOL PushReadedBuffer(OSMessage*);
OSMessage PopFreeReadBuffer();
BOOL PushFreeReadBuffer(OSMessage*);
OSMessage PopReadedBuffer2();
BOOL PushReadedBuffer2(OSMessage*);

extern u8 gTHPReaderDvdAccess;
#ifdef __cplusplus
};
#endif

#endif
