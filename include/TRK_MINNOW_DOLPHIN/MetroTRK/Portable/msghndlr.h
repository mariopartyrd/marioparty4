#ifndef METROTRK_PORTABLE_MSGHNDLR_H
#define METROTRK_PORTABLE_MSGHNDLR_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

void SetTRKConnected(BOOL);
BOOL GetTRKConnected(void);
DSError TRKDoUnsupported(TRKBuffer*);
DSError TRKDoSetOption(TRKBuffer*);
DSError TRKDoStop(TRKBuffer*);
DSError TRKDoStep(TRKBuffer*);
DSError TRKDoContinue(TRKBuffer*);
DSError TRKDoWriteRegisters(TRKBuffer*);
DSError TRKDoReadRegisters(TRKBuffer*);
DSError TRKDoFlushCache(TRKBuffer*);
DSError TRKDoWriteMemory(TRKBuffer*);
DSError TRKDoReadMemory(TRKBuffer*);
DSError TRKDoSupportMask(TRKBuffer*);
DSError TRKDoVersions(TRKBuffer*);
DSError TRKDoSupportMask(TRKBuffer*);
DSError TRKDoCPUType(TRKBuffer*);
DSError TRKDoOverride(TRKBuffer*);
DSError TRKDoReset(TRKBuffer*);
DSError TRKDoDisconnect(TRKBuffer*);
DSError TRKDoConnect(TRKBuffer*);
DSError TRKStandardACK(TRKBuffer* buffer, MessageCommandID commandID,
                       DSReplyError replyError);

void OutputData(void* data, int length);

#endif /* METROTRK_PORTABLE_MSGHNDLR_H */
