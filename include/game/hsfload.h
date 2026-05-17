#ifndef _GAME_HSFLOAD_H
#define _GAME_HSFLOAD_H

#include "game/hsfformat.h"

HSFDATA *LoadHSF(void *data);
void ClusterAdjustObject(HSFDATA *model, HSFDATA *src_model);
char *SetName(u32 *str_ofs);
char *MakeObjectName(char *name);
s32 CmpObjectName(char *name1, char *name2);

#endif
