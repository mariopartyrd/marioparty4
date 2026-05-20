#ifndef REL_M420DLL_H
#define REL_M420DLL_H

#include "game/object.h"

typedef struct M420DllUnkStruct {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ float unk_18;
} M420DllUnkStruct; /* size = 0x1C */ // same as in m447dll/camera.c

typedef struct M420DllPlayerStruct {
    /* 0x00 */ struct {
        s8 unk_00_field0 : 1;
        s8 unk_00_field1 : 1;
        s8 unk_00_field2 : 1;
    };
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u8 unk_0C;
    /* 0x10 */ Vec unk_10;
    /* 0x1C */ Vec unk_1C;
    /* 0x28 */ Vec unk_28;
    /* 0x34 */ Vec unk_34;
    /* 0x40 */ Process *unk_40;
    /* 0x44 */ char unk44[4];
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ char unk52[6];
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C[0xA];
    /* 0x84 */ s32 unk_84[0xA];
    /* 0xAC */ s16 unk_AC;
    /* 0xAE */ s16 unk_AE[0xB];
    /* 0xC4 */ s16 unk_C4[0xA];
    /* 0xD8 */ s16 unk_D8;
    /* 0xDC */ float unk_DC;
    /* 0xE0 */ float unk_E0;
    /* 0xE4 */ s32 unk_E4;
    /* 0xE8 */ struct M420DllPlayerStruct *unk_E8;
} M420DllPlayerStruct; /* size = 0xEC */

void fn_1_1184(void);

s32 fn_1_4964(void);
void fn_1_596C(void);
s32 fn_1_59F4(s32);
s32 fn_1_5AA8(s32 arg0, float arg1);
s32 fn_1_60F0(void);
void fn_1_6268(void);
void fn_1_636C(void);
void fn_1_63EC(void);
void fn_1_6554(void);
s16 fn_1_6660(void);
void fn_1_669C(s32 arg0);
void fn_1_6728(void);
s32 fn_1_67E8(s32);
s32 fn_1_6810(void);
void fn_1_8934(void);
s32 fn_1_8944(void);
M420DllPlayerStruct *fn_1_1B8C(s32, s32);
void fn_1_1E14(M420DllPlayerStruct *);

extern Process *lbl_1_bss_4;

#endif
