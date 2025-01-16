#ifndef METROTRK_PORTABLE_NUBINIT_H
#define METROTRK_PORTABLE_NUBINIT_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C" {
#endif

void TRKNubWelcome(void);
void TRKNubMainLoop(void);
DSError TRKTerminateNub(void);
DSError TRKInitializeNub(void);

extern BOOL gTRKBigEndian;

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_NUBINIT_H */
