#ifndef METROTRK_PORTABLE_NOTIFY_H
#define METROTRK_PORTABLE_NOTIFY_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C" {
#endif

DSError TRKDoNotifyStopped(MessageCommandID cmd);

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_NOTIFY_H */
