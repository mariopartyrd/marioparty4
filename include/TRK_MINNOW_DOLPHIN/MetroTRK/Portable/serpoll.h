#ifndef METROTRK_PORTABLE_SERPOLL_H
#define METROTRK_PORTABLE_SERPOLL_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C" {
#endif

DSError TRKInitializeSerialHandler(void);
DSError TRKTerminateSerialHandler(void);

void TRKGetInput(void);
MessageBufferID TRKTestForPacket();
void TRKProcessInput(int bufferIdx);

extern void* gTRKInputPendingPtr;

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_SERPOLL_H */
