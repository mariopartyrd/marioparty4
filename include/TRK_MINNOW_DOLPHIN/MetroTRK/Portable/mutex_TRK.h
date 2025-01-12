#ifndef METROTRK_PORTABLE_MUTEX_TRK_H
#define METROTRK_PORTABLE_MUTEX_TRK_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

DSError TRKInitializeMutex(void*);
DSError TRKAcquireMutex(void*);
DSError TRKReleaseMutex(void*);

#endif /* METROTRK_PORTABLE_MUTEX_TRK_H */
