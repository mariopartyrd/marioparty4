#include "TRK_MINNOW_DOLPHIN/Os/dolphin/targcont.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.h"
#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"

DSError TRKTargetContinue(void)
{
	TRKTargetSetStopped(0);
	UnreserveEXI2Port();
	TRKSwapAndGo();
	ReserveEXI2Port();
	return 0;
}
