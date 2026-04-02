#ifndef _DOLPHIN_DEMOINIT
#define _DOLPHIN_DEMOINIT

#include <dolphin/gx.h>

extern void *DemoFrameBuffer1;
extern void *DemoFrameBuffer2;
extern void *DemoCurrentBuffer;

void DEMOInit(struct _GXRenderModeObj *mode);
void DEMOBeforeRender();
void DEMODoneRender();
void DEMOSwapBuffers();
void DEMOSetTevColorIn(enum _GXTevStageID stage, enum _GXTevColorArg a, enum _GXTevColorArg b, enum _GXTevColorArg c, enum _GXTevColorArg d);
void DEMOSetTevOp(enum _GXTevStageID id, enum _GXTevMode mode);
struct _GXRenderModeObj *DEMOGetRenderModeObj();
u32 DEMOGetCurrentBuffer(void);
void DEMOEnableBypassWorkaround(unsigned long timeoutFrames);
void DEMOReInit(struct _GXRenderModeObj *mode);

#endif
