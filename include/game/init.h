#ifndef _GAME_INIT_H
#define _GAME_INIT_H

#include "dolphin.h"
#include "version.h"

extern GXRenderModeObj *RenderMode;
extern OSHeapHandle currentHeapHandle;

extern void *DemoFrameBuffer1;
extern void *DemoFrameBuffer2;
extern void *DemoCurrentBuffer;
extern u32 minimumVcount;
extern float minimumVcountf;
SHARED_SYM extern u32 worstVcount;

void HuSysInit(GXRenderModeObj *mode);
void HuSysBeforeRender();
void HuSysDoneRender(s32 retrace_count);

#endif