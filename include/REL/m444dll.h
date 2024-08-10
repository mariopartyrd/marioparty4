#ifndef M444DLL_H
#define M444DLL_H

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

void fn_1_8180(s16 view);
void fn_1_8424(void);
void fn_1_861C(s16 arg0);
s16 fn_1_8DD0(s16 arg0);

void fn_1_9418(s16 arg0);
void fn_1_9CAC(s16 arg0, s16 arg1);

void fn_1_A060(void);
void fn_1_C214(void);


void fn_1_D1E0(s16 model);
void fn_1_D558(DataListModel *model_list);
void fn_1_D818(DataListSprite *sprite_list);
void fn_1_D950(void);
void fn_1_D9C8(void);

extern s16 lbl_1_bss_199C2[90];
extern s16 lbl_1_bss_1990E[90];
extern s16 lbl_1_bss_1990A[2];
extern s16 lbl_1_bss_19908;

extern Vec lbl_1_bss_34C[3];
extern Vec lbl_1_bss_328[3];
extern s16 lbl_1_bss_320[4];
extern Vec lbl_1_bss_2F0;
extern Vec lbl_1_bss_2E4;
extern float lbl_1_bss_2E0;
extern s16 lbl_1_bss_2DC;
extern s16 lbl_1_bss_2DA;
extern s16 lbl_1_bss_2D8;
extern s16 lbl_1_bss_2D6;
extern s16 lbl_1_bss_2D4;
extern s16 lbl_1_bss_2D2;
extern s16 lbl_1_bss_2D0;
extern s16 lbl_1_bss_2C0[8];
extern Vec lbl_1_bss_2A8[2];
extern Vec lbl_1_bss_290[2];
extern float lbl_1_bss_288[2];

extern DataListModel lbl_1_data_470[];

#endif