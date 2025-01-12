#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/notify.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msgbuf.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/support.h"
#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"

DSError TRKDoNotifyStopped(MessageCommandID cmd)
{
	DSError err;
	int reqIdx;
	int bufIdx;
	TRKBuffer* msg;

	err = TRKGetFreeBuffer(&bufIdx, &msg);
	if (err == DS_NoError) {
		if (msg->position >= 0x880) {
			err = DS_MessageBufferOverflow;
		} else {
			msg->data[msg->position++] = cmd;
			++msg->length;
			err = 0;
		}

		if (err == DS_NoError) {
			if (cmd == DSMSG_NotifyStopped) {
				TRKTargetAddStopInfo(msg);
			} else {
				TRKTargetAddExceptionInfo(msg);
			}
		}

		err = TRKRequestSend(msg, &reqIdx, 2, 3, 1);
		if (err == DS_NoError) {
			TRKReleaseBuffer(reqIdx);
		}
		TRKReleaseBuffer(bufIdx);
	}

	return err;
}
