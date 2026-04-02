#ifndef _DOLPHIN_VIFUNCS
#define _DOLPHIN_VIFUNCS

#include <dolphin/types.h>

#include <dolphin/vitypes.h>

#ifdef __cplusplus
extern "C" {
#endif

u32 VIGetNextField(void);
u32 VIGetRetraceCount();
VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback callback);
VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback);
void __VIGetCurrentPosition(s16* x, s16* y);
u32 VIGetDTVStatus(void);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_VIFUNCS
