#ifndef _GAME_HSFLOAD_H
#define _GAME_HSFLOAD_H

#include "game/hsfformat.h"

HsfData *LoadHSF(void *data);
void ClusterAdjustObject(HsfData *model, HsfData *src_model);
char *SetName(u32 *str_ofs);
char *MakeObjectName(char *name);
s32 CmpObjectName(char *name1, char *name2);
#ifdef TARGET_PC
void KillHSF(HsfData *data);
#endif

#endif