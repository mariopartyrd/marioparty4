#ifndef _DOLPHIN_GXPERF
#define _DOLPHIN_GXPERF

#include <dolphin/types.h>
#include <dolphin/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1);
extern void GXClearGPMetric();
extern void GXReadXfRasMetric(u32* xfWaitIn, u32* xfWaitOut, u32* rasBusy, u32* clocks);

// Unused/inlined in P2.
extern void GXReadGPMetric(u32* count0, u32* count1);
extern u32 GXReadGP0Metric();
extern u32 GXReadGP1Metric();
extern void GXReadMemMetric(u32* cpReq, u32* tcReq, u32* cpuReadReq, u32* cpuWriteReq, u32* dspReq, u32* ioReq, u32* viReq, u32* peReq,
                            u32* rfReq, u32* fiReq);
extern void GXClearMemMetric();
extern void GXReadPixMetric(u32* topIn, u32* topOut, u32* bottomIn, u32* bottomOut, u32* clearIn, u32* copyClocks);
extern void GXClearPixMetric();
extern void GXSetVCacheMetric(GXVCachePerf attr);
extern void GXReadVCacheMetric(u32* check, u32* miss, u32* stall);
extern void GXClearVCacheMetric();
extern void GXInitXfRasMetric();
extern u32 GXReadClksPerVtx();


#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXPERF
