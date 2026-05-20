#ifndef _BOARD_ITEM_H
#define _BOARD_ITEM_H

#include "dolphin/types.h"

void BoardItemStart(s32 arg0, s32 arg1);
BOOL BoardItemDoneCheck(void);
void BoardItemBagItemSet(s16 *arg0);
#ifndef __MWERKS__
void BoardItemPlayerRestore(s32 arg0, s32 arg1);
#endif

#endif
