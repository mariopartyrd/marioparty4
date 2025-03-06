#ifndef METROTRK_PORTABLE_MSG_H
#define METROTRK_PORTABLE_MSG_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "dolphin/types.h"

typedef struct _TRK_Msg {
	u8 _00[8];
	u32 m_msgLength;
	u32 _0C;
	u8 m_msg[4]; // TODO: unknown array length
} TRK_Msg;

#ifdef __cplusplus
extern "C" {
#endif

DSError TRKMessageSend(TRK_Msg* msg);

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_MSG_H */
