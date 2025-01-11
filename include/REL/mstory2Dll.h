#ifndef MSTORY2DLL_H
#define MSTORY2DLL_H

#include "game/object.h"
#include "game/process.h"

#include "dolphin/types.h"

typedef struct {
    /* 0x00 */ void (*unk00)(void);
    /* 0x04 */ void (*unk04)(void);
    /* 0x08 */ Vec unk08;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ Vec unk20;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ s32 unk40;
} StructBss24; // Size 0x44

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ char unk1C[0x18];
} StructFn357C; // Size 0x34

typedef struct {
    /* 0x00 */ omObjData* unk00;
    /* 0x04 */ void (*unk04)(omObjData*, ...);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ char unk10[0x18];
} StructBss16C; // Size 0x28

// main.c
float fn_1_864(float arg0, float arg1, float arg2, float arg3);
float fn_1_88C(float arg0, float arg1, float arg2);
float fn_1_8AC(float arg0, float arg1, float arg2, float arg3);
float fn_1_984(float arg0, float arg1, float arg2, float arg3);
float fn_1_A4C(float arg0, float arg1, float arg2, float arg3);
float fn_1_B08(float arg0, float arg1, float arg2, float arg3);
void fn_1_BC8(void);
void fn_1_BE8(s32 arg0);
void fn_1_C30(void);
s32 fn_1_185C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_1A94(s32 arg0);
void fn_1_1AFC(s32 arg0, s32 arg1);
BOOL fn_1_1BA8(s32 arg0, s32 arg1);
BOOL fn_1_1C64(s32 arg0);
void fn_1_1D18(s32 arg0, s32 arg1);
void fn_1_1D4C(s32 arg0, s32 arg1, s32 arg2);
void fn_1_1DFC(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_2264(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_2750(void (*arg0)(void));
void fn_1_2828(Process* arg0, void (*arg1)(void));
void fn_1_2948(omObjData* arg0, s32 arg1, Vec arg2, float arg3, float arg4, float arg5);
void fn_1_2D00(omObjData* arg0, s32 arg1, Vec arg2, float arg3, float arg4, float arg5);
void fn_1_357C(StructFn357C* arg0, s32 arg1);
void fn_1_42A0(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3, float arg4);
s32 fn_1_3668(s32 arg0);
void fn_1_3754(void);
void fn_1_3854(StructBss24* arg0);
void fn_1_3B04(StructBss24* arg0, float arg1);
void fn_1_4FEC(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3, float arg4);
void fn_1_6004(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3, float arg4);
int fn_1_66CC(int modelId);

void fn_1_6704(omObjData* arg0);
void fn_1_67D8(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_6A90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_6D78(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_6DBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 fn_1_7064(s32 arg0, s32 arg1);
void fn_1_71DC(s32 arg0);
void fn_1_7244(s16 modelId, char *objName, u32 constAttr, float ofs);
void fn_1_7384(int modelId, int charNo, float ofs, s32 maxTime, BOOL flag);

// board_clear.c
void fn_1_7F54(Process* arg0, s32 arg1);

// board_clear.c
void fn_1_B3E4(Process* arg0, s32 arg1);

// board_miss.c
void fn_1_EA2C(Process* arg0, s32 arg1);

// mg_clear.c
void fn_1_1256C(Process* arg0, s32 arg1);

// mg_miss.c
void fn_1_16060(Process* arg0, s32 arg1);

// ending.c
void fn_1_188F0(Process* arg0, s32 arg1);

// ending.c
void fn_1_1B90C(Process* arg0);

extern s32 lbl_1_bss_88[16];
extern s32 lbl_1_bss_78[4];
extern s32 lbl_1_bss_68[];
extern StructBss24 lbl_1_bss_24;
extern s32 lbl_1_data_0[][4];

#endif
