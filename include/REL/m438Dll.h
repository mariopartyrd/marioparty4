#ifndef M438DLL_H
#define M438DLL_H

#include "game/animdata.h"
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

typedef struct M438UnkSubStruct {
    s32 unk_00;
    char unk01[0x20];
    u8 unk_24;
    float unk_28;
    float unk_2C;
} M438UnkSubStruct;

typedef struct M438UnkStruct {
    Vec unk_00;
    Vec unk_0C;
    Vec unk_18;
    Vec unk_24;
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
    u8 unk_34;
    u32 unk_38;
    s16 unk_3C;
    void* unk_40;
    Vec* unk_44;
    GXColor* unk_48;
    Vec* unk_4C;
    GXColor unk_50;
    GXColor unk_54;
    M438UnkSubStruct* unk_58;
    u8 unk_5C;
    char unk5D[0x3];
    Vec unk_60;
    Vec unk_6C;
    s16 unk_78;
    s16 unk_7A;
    char unk7C[0x1C];
} M438UnkStruct; /* size = 0x98 */

typedef struct M438UnkStruct2 {
    s16 unk_00;
    s16 unk_02;
    u8 unk_04;
    u32 unk_08;
    Vec unk_0C;
    Vec unk_18;
    Vec unk_24;
    void (*unk_30)(struct M438UnkStruct2*);
    s16 unk_34[4];
    M438UnkStruct *unk_3C;
    char unk40[0x20];
    u8 unk_60;
    char unk61[0x3];
    char unk64[0x18];
    s16 unk_7C;
    s16 unk_7E;
    float unk_80;
    float unk_84;
    float unk_88;
    float unk_8C;
    float unk_90;
    char unk94[0x28];
} M438UnkStruct2; /* size = 0xBC */

typedef struct M438UnkStruct3 {
    AnimData* unk_00;
    s16 unk_04;
    s16 unk_06;
    s32 unk_08;
    Vec unk_0C;
    Mtx unk_18;
    char unk48[0x1C];
} M438UnkStruct3; /* size = 0x64 */

typedef struct M438StructBssDE4 {
    Mtx unk_00;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    s16 unk_38;
    s16 unk_3A;
    M438UnkStruct3 *unk_3C;
    M438UnkStruct2 *unk_40;
} M438StructBssDE4; /* size =  */

extern M438StructBssDE4 lbl_1_bss_DE4;

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
