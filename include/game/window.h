#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include "game/animdata.h"
#include "dolphin.h"
#include "version.h"

#define MAKE_MESSID(bank, mess) (((bank) << 16)+(mess))
#define MAKE_MESSID_PTR(ptr) ((u32)(ptr))

typedef struct {
    /* 0x00 */ u8 color;
    /* 0x01 */ u8 fade;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 character;
} WinChar; // Size 8

typedef struct {
    /* 0x00 */ u8 stat;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
} WinChoice; // Size 6

typedef struct {
    /* 0x000 */ u8 stat;
    /* 0x001 */ u8 active_pad;
    /* 0x002 */ u8 player_disable;
    /* 0x003 */ u8 color_key;
    /* 0x004 */ s16 group;
    /* 0x006 */ s16 sprite_id[30];
    /* 0x042 */ s16 speed;
    /* 0x044 */ s16 mess_time;
    /* 0x046 */ s16 advance_sprite;
    /* 0x048 */ s16 prio;
    /* 0x04C */ u32 attr;
    /* 0x050 */ AnimData *frame;
    /* 0x054 */ s16 mess_rect_x;
    /* 0x056 */ s16 mess_rect_w;
    /* 0x058 */ s16 mess_rect_y;
    /* 0x05A */ s16 mess_rect_h;
    /* 0x05C */ s16 mess_x;
    /* 0x05E */ s16 mess_y;
    /* 0x060 */ s16 mess_color;
    /* 0x062 */ s16 mess_shadow_color;
    /* 0x064 */ s16 spacing_x;
    /* 0x066 */ s16 spacing_y;
    /* 0x068 */ s16 w;
    /* 0x06A */ s16 h;
    /* 0x06C */ float pos_x;
    /* 0x070 */ float pos_y;
    /* 0x074 */ float scale_x;
    /* 0x078 */ float scale_y;
    /* 0x07C */ float z_rot;
    /* 0x080 */ s16 num_chars;
    /* 0x082 */ s16 max_chars;
    /* 0x084 */ WinChar *char_data;
    /* 0x088 */ s16 mess_stackptr;
    /* 0x08C */ s32 unk8C;
    /* 0x090 */ u8 *mess;
    /* 0x094 */ u8 *mess_stack[8];
    /* 0x0B4 */ u8 *insert_mess[8];
    /* 0x0D4 */ s16 num_choices;
    /* 0x0D6 */ s16 choice;
    /* 0x0D8 */ s16 cursor_sprite;
    /* 0x0DA */ u8 choice_disable[16];
    /* 0x0EA */ WinChoice choice_data[16];
    /* 0x14A */ s16 scissor_x;
    /* 0x14C */ s16 scissor_y;
    /* 0x14E */ s16 scissor_w;
    /* 0x150 */ s16 scissor_h;
    /* 0x152 */ s16 tab_w;
    /* 0x154 */ s16 push_key;
    /* 0x156 */ s16 key_down;
    /* 0x158 */ s16 key_auto;
    /* 0x160 */ u8 ATTRIBUTE_ALIGN(32) mess_pal[10][3];
} WindowData; // Size 0x180

SHARED_SYM extern WindowData winData[32];
SHARED_SYM extern void *messDataPtr;

void HuWindowInit(void);
void HuWinInit(s32 mess_data_no);
s16 HuWinCreate(float x, float y, s16 w, s16 h, s16 frame);
void HuWinKill(s16 window);
void HuWinAllKill(void);
void HuWinHomeClear(s16 window);
void HuWinKeyWaitEntry(s16 window);
u32 HuWinActivePadGet(WindowData *window);
u32 HuWinActiveKeyGetX(WindowData *window);
void HuWinPosSet(s16 window, float x, float y);
void HuWinScaleSet(s16 window, float x, float y);
void HuWinZRotSet(s16 window, float z_rot);
void HuWinCenterPosSet(s16 window, float x, float y);
void HuWinDrawNoSet(s16 window, s16 draw_no);
void HuWinScissorSet(s16 window, s16 x, s16 y, s16 w, s16 h);
void HuWinPriSet(s16 window, s16 prio);
void HuWinAttrSet(s16 window, u32 attr);
void HuWinAttrReset(s16 window, u32 attr);
s16 HuWinStatGet(s16 window);
void HuWinMesColSet(s16 window, u8 color);
void HuWinMesPalSet(s16 window, u8 index, u8 r, u8 g, u8 b);
void HuWinBGTPLvlSet(s16 window, float tp_level);
void HuWinBGColSet(s16 window, GXColor *bg_color);
void HuWinMesSpeedSet(s16 window, s16 speed);
void HuWinMesRead(s32 mess_data_no);
void HuWinMesSet(s16 window, u32 mess);
void HuWinInsertMesSet(s16 window, u32 mess, s16 index);
s16 HuWinChoiceGet(s16 window, s16 start_choice);
s16 HuWinChoiceNumGet(s16 window);
void HuWinChoiceDisable(s16 window, s16 choice);
s16 HuWinChoiceNowGet(s16 window);
void HuWinMesWait(s16 window);
s16 HuWinAnimSet(s16 window, AnimData *anim, s16 bank, float x, float y);
s16 HuWinSprSet(s16 window, s16 sprite, float x, float y);
void HuWinSprPosSet(s16 window, s16 index, float x, float y);
void HuWinSprPriSet(s16 window, s16 index, s16 prio);
s16 HuWinSprIDGet(s16 window, s16 index);
void HuWinSprKill(s16 window, s16 index);
void HuWinDispOff(s16 window);
void HuWinDispOn(s16 window);
void HuWinComKeyWait(s32 player_1, s32 player_2, s32 player_3, s32 player_4, s16 delay);
void HuWinComKeySet(s32 player_1, s32 player_2, s32 player_3, s32 player_4);
void _HuWinComKeySet(s32 player_1, s32 player_2, s32 player_3, s32 player_4, s16 delay);
void HuWinComKeyGet(s16 window, u32 *data);
void HuWinComKeyReset(void);
void HuWinMesMaxSizeGet(s16 mess_num, float *size, ...);
void HuWinInsertMesSizeGet(u32 mess, s16 index);
void HuWinMesSizeCancelCRSet(s32 cancel_cr);
void HuWinMesMaxSizeBetGet(float *size, u32 start, u32 end);
s16 HuWinKeyWaitNumGet(u32 mess);
void HuWinPushKeySet(s16 window, s16 push_key);
void HuWinDisablePlayerSet(s16 window, u8 player);
void HuWinDisablePlayerReset(s16 window, u8 player);
s16 HuWinExCreate(float x, float y, s16 w, s16 h, s16 portrait);
s16 HuWinExCreateStyled(float x, float y, s16 w, s16 h, s16 portrait, s16 frame);
void HuWinExAnimIn(s16 window);
void HuWinExAnimOut(s16 window);
void HuWinExCleanup(s16 window);
void HuWinExAnimPopIn(s16 window, s16 portrait);
void *MessData_MesPtrGet(void *data, u32 index);

#endif
