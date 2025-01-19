#ifndef MSTORY3DLL_H
#define MSTORY3DLL_H

#include "game/object.h"
#include "game/process.h"

#include "dolphin.h"

// For future reference: seems to be identical to StructFn352C in mstoryDll.
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ char unk30[4];
} StructFn352C; // Size 0x34

// For future reference: seems to be identical to StructBss4 in mstoryDll.
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
    /* 0x00 */ omObjData* unk00;
    /* 0x04 */ void (*unk04)(omObjData*, ...);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ char unk20[8];
} StructBss1530; // Size 0x28

// main.c
float fn_1_5D4(float arg8, float arg9, float argA, float argB);
float fn_1_5FC(float arg8, float arg9, float argA);
float fn_1_61C(float arg0, float arg1, float arg2, float arg3);
float fn_1_6F4(float arg0, float arg1, float arg2, float arg3);
float fn_1_7BC(float arg0, float arg1, float arg2, float arg3);
float fn_1_878(float arg0, float arg1, float arg2, float arg3);
void fn_1_938(void);
void fn_1_958(s32 arg0);
void fn_1_9A0(void);
void fn_1_9C4(void);
s32 fn_1_1624(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 fn_1_1834(u32 arg0, s32 arg1);
void fn_1_1A24(s32 arg0);
void fn_1_1AB0(s32 arg0);
void fn_1_1B18(s32 arg0, s32 arg1);
void fn_1_1D44(s32 arg0, s32 arg1);
void fn_1_1E28(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_2280(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_2310(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_2420(s32 arg0, s32 arg1);
void fn_1_2834(void (*arg0)(void));
void fn_1_290C(Process* arg0, void (*arg1)(void));
void fn_1_2DD4(omObjData* arg0, s32 arg1, Vec arg2, float arg3, float arg4, float arg5);
void fn_1_35C8(s16 arg0);
void fn_1_3650(StructFn352C* arg0, s32 arg1);
s32 fn_1_36E4(void);
s32 fn_1_373C(void);
s32 fn_1_37C8(s32 arg0);
void fn_1_38B4(void);
void fn_1_39B4(StructBss4* arg0);
void fn_1_4400(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3, float arg4);
void fn_1_4CC0(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3);
void fn_1_514C(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3, float arg4);

// result_seq.c
void fn_1_6E34(Process* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

// result.c
void fn_1_157F0(Process* arg0, s32 arg1, s32 arg2, s32 arg3);

extern StructBss4 lbl_1_bss_4;
extern s32 lbl_1_data_0[][4];

#endif
