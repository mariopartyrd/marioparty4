#ifndef M438DLL_H
#define M438DLL_H

#include "game/object.h"

typedef struct M438MainWork4 {
    u8 unk_00;
    char unk01[0x3];
    s32 unk_04;
    float unk_08;
    float unk_0C;
    Vec unk_10;
    Vec unk_1C;
    Vec unk_28;
    Vec unk_34;
    char unk40[0xC];
} M438MainWork4; /* size = 0x4C */

void fn_1_B4D8(Process *arg0);
void fn_1_B548();
s32 fn_1_DA64(float arg8);
s32 fn_1_DEA0(float arg8);
float fn_1_E488(float arg8, float arg9, float argA);
float fn_1_E5A4(float arg8, float arg9);

void fn_1_E658(s16 arg0, s16 arg1);
s16 fn_1_10258(s32 arg0, s32 arg1);
void fn_1_107BC(s16 arg0);
void fn_1_108E4(s16 arg0, s32 arg1, s32 arg2);
s16 fn_1_10910(u32 arg0, s16 arg1, s16 arg2);
s8 fn_1_11018(s16 arg0, u8 arg1, u32 arg2);
void fn_1_11658(void);
void fn_1_11890(s16 arg0, float arg8, float arg9, float argA);
void fn_1_118FC(s16 arg0, s16 arg1, float arg8, float arg9, float argA);
void fn_1_11B78(s16 arg0, s16 arg1, float arg8, float arg9, float argA);
void fn_1_11CC8(s16 arg0, s16 arg1, float arg8, float arg9, float argA);
void fn_1_11E18(s16 arg0, s16 arg1, float arg8, float arg9, float argA);
void fn_1_11F68(s16 arg0, s16 arg1, float arg8, float arg9, float argA);
void fn_1_1204C(s16 arg0, s32 arg1);
void fn_1_12090(s16 arg0, s16 arg1, s32 arg2);
void fn_1_12100(s16 arg0, s32 arg1);
void fn_1_12174(s16 arg0, s32 arg1);
void fn_1_12378(s16 arg0, s16 arg1, s8 arg2, s8 arg3, s8 arg4, u8 arg5);
void fn_1_124CC(s16 arg0, s8 arg1);
void fn_1_12538(s16 arg0, s16 arg1, s8 arg2);
void fn_1_1274C(s16 arg0, s16 arg1, u8 arg2, s8 arg3);
void fn_1_128C8(s16 arg0, s16 arg1, u8 arg2, float arg8);

#endif
