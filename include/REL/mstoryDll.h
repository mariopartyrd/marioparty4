#ifndef MSTORYDLL_H
#define MSTORYDLL_H

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
} StructBss4; // Size 0x44

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ char unk1C[0x18];
} StructFn352C; // Size 0x34

typedef struct {
    /* 0x00 */ omObjData* unk00;
    /* 0x04 */ void (*unk04)(omObjData*, ...);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ char unk10[0x18];
} StructBss19C; // Size 0x28

// main.c
float fn_1_828(float arg0, float arg1, float arg2, float arg3);
float fn_1_870(float arg0, float arg1, float arg2, float arg3);
float fn_1_948(float arg0, float arg1, float arg2, float arg3);
float fn_1_ACC(float arg0, float arg1, float arg2, float arg3);
void fn_1_B8C(void);
void fn_1_BAC(s32 arg0);
void fn_1_BF4(void);
s32 fn_1_1834(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_1A64(s32 arg0);
void fn_1_1ACC(s32 arg0, s32 arg1);
BOOL fn_1_1B78(s32 arg0, s32 arg1);
BOOL fn_1_1C34(s32 arg0);
void fn_1_1CE8(s32 arg0, s32 arg1);
void fn_1_1D1C(s32 arg0, s32 arg1, s32 arg2);
void fn_1_1DCC(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_2224(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_2710(void (*arg0)(void));
void fn_1_27E8(Process* arg0, void (*arg1)(void));
void fn_1_2908(omObjData* arg0, s32 arg1, Vec arg2, float arg3, float arg4, float arg5);
void fn_1_2CB0(omObjData* arg0, s32 arg1, Vec arg2, float arg3, float arg4, float arg5);
void fn_1_352C(StructFn352C* arg0, s32 arg1);
s32 fn_1_3618(s32 arg0);
void fn_1_3704(void);
void fn_1_3804(StructBss4* arg0);
void fn_1_3ABC(StructBss4* arg0, float arg1);
void fn_1_51D0(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3, float arg4);
void fn_1_61E8(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3, float arg4);
void fn_1_6C1C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 fn_1_6EB8(s32 arg0, s32 arg1);
void fn_1_7028(s32 arg0);

// board_clear.c
void fn_1_79B8(Process* arg0, s32 arg1, s32 arg2);

// board_miss.c
void fn_1_ACFC(Process* arg0, s32 arg1, s32 arg2);

// mg_clear.c
void fn_1_E710(Process* arg0, s32 arg1, s32 arg2);

// mg_miss.c
void fn_1_11624(Process* arg0, s32 arg1, s32 arg2);

// save.c
void fn_1_14150(Process* arg0);

extern s32 lbl_1_bss_68;
extern s32 lbl_1_bss_58[];
extern StructBss4 lbl_1_bss_4;
extern s32 lbl_1_data_0[][4];

#endif
