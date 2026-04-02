#ifndef _DOLPHIN_VI
#define _DOLPHIN_VI

#include <dolphin/gx/GXStruct.h>
#include <dolphin/vifuncs.h>

#ifdef __cplusplus
extern "C" {
#endif

void VIInit(void);
void VIConfigure(const GXRenderModeObj* rm);
void VIFlush(void);
u32 VIGetTvFormat(void);
void VISetNextFrameBuffer(void* fb);
void VIWaitForRetrace(void);
void VISetBlack(BOOL black);
void VIConfigurePan(u16 xOrg, u16 yOrg, u16 width, u16 height);

#ifdef TARGET_PC
void VISetWindowTitle(const char* title);
void VISetWindowFullscreen(bool fullscreen);
bool VIGetWindowFullscreen();
#endif



#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_VI
