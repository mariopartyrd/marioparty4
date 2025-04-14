#ifndef _GAME_PRINTFUNC_H
#define _GAME_PRINTFUNC_H

#include "dolphin.h"
#include "version.h"

#define FONT_COLOR_BLACK 0
#define FONT_COLOR_DARK_BLUE 1
#define FONT_COLOR_DARK_RED 2
#define FONT_COLOR_DARK_MAGENTA 3
#define FONT_COLOR_DARK_GREEN 4
#define FONT_COLOR_DARK_CYAN 5
#define FONT_COLOR_DARK_YELLOW 6
#define FONT_COLOR_GRAY 7
#define FONT_COLOR_TRANSLUCENT_GRAY 8
#define FONT_COLOR_BLUE 9
#define FONT_COLOR_RED 10
#define FONT_COLOR_MAGENTA 11
#define FONT_COLOR_GREEN 12
#define FONT_COLOR_CYAN 13
#define FONT_COLOR_YELLOW 14
#define FONT_COLOR_WHITE 15

void pfInit(void);
void pfClsScr(void);
s16 print8(s16 x, s16 y, float scale, char *str, ...);
s16 printWin(s16 x, s16 y, s16 w, s16 h, GXColor *color);
void pfDrawFonts(void);

extern BOOL saftyFrameF;
extern u16 strlinecnt;
extern u16 empstrline;
SHARED_SYM extern int fontcolor;
extern u32 procfunc;

#endif