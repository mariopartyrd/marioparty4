#ifndef _SRC_IMGUI_H_
#define _SRC_IMGUI_H_

#include <aurora/aurora.h>

#ifdef __cplusplus
extern "C"
{
#endif

void imgui_main(const AuroraInfo* info);
void frame_limiter();
const char* imgui_get_image_path_from_popup();

#ifdef __cplusplus
}
#endif

#endif
