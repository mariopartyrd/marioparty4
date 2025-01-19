#ifndef M430DLL_H
#define M430DLL_H

#include "game/object.h"

typedef struct M433DllWork {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    s32 unk_24;
    u32 unk_28;
    s32 unk_2C[2];
    u32 unk_34;
    s32 unk_38;
    s32 unk_3C;
} M433DllWork; /* size = 0x40 */

void fn_1_584(omObjData *object);
void fn_1_618(omObjData *object);
u32 fn_1_216C(void);
u32 fn_1_2184(void);
void fn_1_219C(s32 arg0, s32 arg1, s32 arg2);
void fn_1_21E4(s32 arg0);
void fn_1_2214(s32 arg0);
s32 fn_1_2244(void);
float fn_1_26C4(float arg8, float arg9, float argA);

void fn_1_2894(Process *process);
void fn_1_2984(void);
omObjFunc fn_1_29A4(Process *process, omObjData *object);
void fn_1_58D8(s32);

void fn_1_5904(Process *process);
void fn_1_5B74(void);
s32 fn_1_10FA4(s32 arg0);

#endif
