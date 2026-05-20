#ifndef REL_M421DLL_H
#define REL_M421DLL_H

#include "game/object.h"

typedef struct UnkM421DllStruct {
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0C;
} UnkM421DllStruct;

typedef struct M421DllCameraStruct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u32 unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    Vec unk_1C;
    Vec unk_28;
    float unk_34;
    s32 unk_38;
    s32 unk_3C;
    float unk_40;
    UnkM421DllStruct unk_44;
    float unk_54;
    float unk_58;
    float unk_5C;
    float unk_60;
    float unk_64;
    float unk_68;
    char unk6C[0x18];
    float unk_84;
    char unk88[0x4];
    float unk_8C;
    float unk_90;
    u32 unk_94;
    char unk98[0xC];
} M421DllCameraStruct; /* size = 0xA4 */ // same as M443DllCameraStruct and M460

M421DllCameraStruct *fn_1_3C14(s32 arg0);
u32 fn_1_3E34(void);
u32 fn_1_3E4C(void);
u32 fn_1_3E64(void);
s32 fn_1_3E7C(s32 arg0);
s32 fn_1_3EF8(s32 arg0);
void fn_1_3F28(s32 arg0, s32 arg1, s32 arg2);
void fn_1_3F68(s32 arg0);
void fn_1_3F98(s32 arg0);
void fn_1_3FC8(s32 arg0);
s32 fn_1_3FF8(void);
float fn_1_4478(float arg8, float arg9, float argA);

void fn_1_4648(Process *process);
void fn_1_48B0(void);
void fn_1_B15C(Process *process);
void fn_1_B1BC(void);
void fn_1_B39C(void);

#endif
