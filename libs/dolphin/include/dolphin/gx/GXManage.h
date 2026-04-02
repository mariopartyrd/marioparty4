#ifndef _DOLPHIN_GXMANAGE
#define _DOLPHIN_GXMANAGE

#include <dolphin/gx/GXFifo.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GXDrawDoneCallback)(void);
typedef void (*GXDrawSyncCallback)(u16 token);

GXFifoObj* GXInit(void* base, u32 size);
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb);
void GXSetDrawSync(u16 token);
GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback callback);

void GXDrawDone(void);
void GXSetDrawDone(void);
void GXFlush(void);
void GXPixModeSync(void);
void GXSetMisc(GXMiscToken token, u32 val);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXMANAGE
