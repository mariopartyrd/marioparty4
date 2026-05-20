#ifndef REL_M460DLL_H
#define REL_M460DLL_H

#include "game/object.h"

typedef struct UnkM460DllStruct {
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0C;
} UnkM460DllStruct;

typedef struct M460DllCameraStruct {
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
    UnkM460DllStruct unk_44;
    char unk54[0x30];
    float unk_84;
    char unk88[0x4];
    float unk_8C;
    float unk_90;
    s32 unk_94;
    char unk98[0xC];
} M460DllCameraStruct; /* size = 0xA4 */ // same as M443DllCameraStruct

void fn_1_3E68(u32 arg0);
M460DllCameraStruct *fn_1_3E90(s32 arg0);
M460DllCameraStruct *fn_1_3F2C(s32 arg0);
u32 fn_1_414C(void);
u32 fn_1_4164(void);
s32 fn_1_419C(void);
void fn_1_41B4(s32 arg0, s32 arg1, s32 arg2);
void fn_1_41F4(s32 arg0);
void fn_1_4224(s32 arg0);
void fn_1_42BC(u32 arg0);
s32 fn_1_42F0(void);
void fn_1_4308(void);
s32 fn_1_4324(void);
void fn_1_433C(void);
s32 fn_1_4358(void);
u32 fn_1_4370(void);
float fn_1_47D0(float arg8, float arg9, float argA);

void fn_1_49A0(Process *process);
void fn_1_4BE4(void);
void fn_1_67B4(Process *process);
void fn_1_6814(void);
void fn_1_8BA0(float arg8);
void fn_1_8CAC(Process *process, s16 arg1);
void fn_1_8F38(void);
void fn_1_8FAC(s32 arg0);

#endif
