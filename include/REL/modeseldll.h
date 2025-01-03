#ifndef MODESELDLL_H
#define MODESELDLL_H

#include "game/data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "game/sprite.h"

typedef struct datalist_model {
	s32 datanum;
	u32 attr;
	s16 type;
	s16 link;
	s16 mot_link;
	Vec pos;
	Vec rot;
	Vec scale;
} DataListModel;

typedef struct datalist_sprite {
	u32 datanum;
	s16 attr;
	s16 prio;
	float x;
	float y;
	GXColor color;
} DataListSprite;

// void fn_1_1EC0(s16 view);

s32 fn_1_2490(void);
s32 fn_1_37DC(void);

void fn_1_BED8(DataListModel *model_list);
void fn_1_C168(DataListSprite *sprite_list);
void fn_1_C2BC(void);

extern s16 lbl_1_bss_19A[24];
extern s16 lbl_1_bss_16A[24];
extern s16 lbl_1_bss_152[12];
extern s16 lbl_1_bss_150;
extern s16 lbl_1_data_100;
extern DataListModel lbl_1_data_428[];
extern DataListSprite lbl_1_data_93C[];

#endif
