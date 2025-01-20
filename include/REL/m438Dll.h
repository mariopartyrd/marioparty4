#ifndef M438DLL_H
#define M438DLL_H

#include "game/animdata.h"
#include "game/hsfformat.h"
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
    s8 unk_00;
    s8 unk_01;
    char unk02[0x2];
    f32 unk_04;
    f32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
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
    s16 unk_78[0x10];
} M438UnkStruct; /* size = 0x98 */

typedef struct M438FireStruct {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    Vec unk24;
} M438FireStruct; // sizeof 0x30

typedef struct M438FireStruct2 {
    GXColor unk0;
    GXColor unk4;
    GXColor unk8;
    GXColor unkC;
} M438FireStruct2; // sizeof 0x10

typedef struct M438FireStruct3 {
    HsfVector2f unk0;
    HsfVector2f unk8;
    HsfVector2f unk10;
    HsfVector2f unk18;
} M438FireStruct3; // sizeof 0x20

typedef struct M438UnkStruct2 {
    s16 unk_00;
    s16 unk_02;
    u8 unk_04;
    u32 unk_08;
    Vec unk_0C;
    Vec unk_18;
    Vec unk_24;
    void (*unk_30)(struct M438UnkStruct2*);
    s16* unk_34;
    char unk_38[0x4];
    M438UnkStruct *unk_3C;
    char unk40[0x8];
    s16 unk_48;
    void* unk_4C;
    Vec* unk_50;
    GXColor* unk_54;
    Vec* unk_58;
    M438UnkSubStruct* unk_5C;
    u8 unk_60;
    char unk61[0x3];
    Vec unk_64;
    Vec unk_70;
    union {
        s16 unk_7Ca[0x20];
        struct {
            s16 unk_7C;
            s16 unk_7E;
            float unk_80;
            float unk_84;
            float unk_88;
            float unk_8C;
            float unk_90;
            char unk94[0x28];
        };
    };
} M438UnkStruct2; /* size = 0xBC */

typedef struct M438UnkStruct3 {
    AnimData* unk_00;
    s16 unk_04;
    s16 unk_06;
    u32 unk_08;
    Vec unk_0C;
    Mtx unk_18;
    GXColor unk_48;
    u8 unk_4C;
    u8 unk_4D;
    s16 unk_4E;
    s16 unk_50;
    char unk52[0x2];
    f32 unk_54;
    f32 unk_58;
    f32 unk_5C;
    f32 unk_60;
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
s16 fn_1_10258(u8 arg0, u8 arg1);
void fn_1_107BC(s16 arg0);
void fn_1_108E4(s16 arg0, s16 arg1, u8 arg2);
s16 fn_1_10910(u32 arg0, s16 arg1, s16 arg2);
u8 fn_1_11018(s16 arg0, u8 arg1, u32 arg2);
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
void fn_1_12174(s16 arg0, u32 arg1);
void fn_1_12378(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5);
void fn_1_124CC(s16 arg0, u8 arg1);
void fn_1_12538(s16 arg0, s16 arg1, u8 arg2);
void fn_1_1274C(s16 arg0, s16 arg1, u8 arg2, u8 arg3);
void fn_1_128C8(s16 arg0, s16 arg1, u8 arg2, float arg8);

#endif
