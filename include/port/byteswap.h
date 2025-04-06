#ifndef _SRC_BYTESWAP_H_
#define _SRC_BYTESWAP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "game/animdata.h"

void byteswap_u32(u32 *src);
void byteswap_s32(s32 *src);
void byteswap_animdata(void *src, AnimData* dest);
void byteswap_animbankdata(void *src, AnimBankData *dest);
void byteswap_animpatdata(void *src, AnimPatData *dest);
void byteswap_animbmpdata(void *src, AnimBmpData *dest);
void byteswap_animframedata(AnimFrameData *src);
void byteswap_animlayerdata(AnimLayerData *src);

#ifdef __cplusplus
}
#endif

#endif
