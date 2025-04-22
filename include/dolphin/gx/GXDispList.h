#ifndef _DOLPHIN_GXDISPLIST
#define _DOLPHIN_GXDISPLIST

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef AURORA
#define GXCALLDISPLAYLISTLE GXCallDisplayListLE
#else
#define GXCALLDISPLAYLISTLE GXCallDisplayList
#endif

void GXBeginDisplayList(void* list, u32 size);
u32 GXEndDisplayList(void);
void GXCallDisplayListLE(const void* list, u32 nbytes);
void GXCallDisplayList(const void* list, u32 nbytes);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXDISPLIST
