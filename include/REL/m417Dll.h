#ifndef REL_M417DLL_H
#define REL_M417DLL_H

#include "game/object.h"
#include "game/process.h"

typedef struct UnkM417Struct2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
} UnkM417Struct2; /* size = 0x10 */

void fn_1_5B0(omObjData *object);
void fn_1_800(omObjData *object);
u32 fn_1_26F8(void);
u32 fn_1_2710(void);
void fn_1_2728(u32 arg0);
s32 fn_1_2740(s32 arg0);
void fn_1_2770(s32 arg0);
void fn_1_27A0(s32 arg0);
s32 fn_1_27D0(void);
void fn_1_2808(s32 arg0, s32 arg1, s32 arg2);
float fn_1_2F08(float arg8, float arg9, float argA);
float fn_1_3024(float arg8, float arg9);
void fn_1_3274(Process *arg0);
void fn_1_33B4(void);
void fn_1_7510(float arg8, float arg9, float argA, float argB);
float fn_1_75BC(void);
float fn_1_78BC(float arg8, float arg9, float argA);
UnkM417Struct2 *fn_1_7A28(void);
void fn_1_7A34(Process *arg0);
omObjFunc fn_1_BCAC(Process *arg0);
omObjFunc fn_1_C658(Process *arg0, omObjData *object);

#endif
