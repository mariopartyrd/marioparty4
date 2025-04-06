#ifndef _GAME_WIPE_H
#define _GAME_WIPE_H

#include "dolphin.h"
#include "version.h"

#define WIPE_TYPE_PREV -1
#define WIPE_TYPE_NORMAL 0
#define WIPE_TYPE_CROSS 1
#define WIPE_TYPE_DUMMY 2
#define WIPE_MODE_IN 1
#define WIPE_MODE_OUT 2
#define WIPE_MODE_BLANK 3

typedef struct wipe_state {
	u32 unk00;
	u32 unk04;
	void *copy_data;
	u32 unk0C;
	void *unk10[8];
    float time;
    float duration;
    u32 unk38;
	u16 w;
	u16 h;
	u16 x;
	u16 y;
	GXColor color;
	volatile u8 type;
    u8 mode;
	u8 stat;
	u8 keep_copy;
} WipeState;

void WipeInit(GXRenderModeObj *rmode);
void WipeExecAlways(void);
void WipeCreate(s16 mode, s16 type, s16 duration);
void WipeColorSet(u8 r, u8 g, u8 b);
u8 WipeStatGet(void);

SHARED_SYM extern WipeState wipeData;
extern BOOL wipeFadeInF;

#endif
