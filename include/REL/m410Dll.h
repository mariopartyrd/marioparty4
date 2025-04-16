#ifndef M410DLL_H
#define M410DLL_H

#include "dolphin.h"

typedef struct UnkM410Struct {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    u32 unk_14;
    s32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    s32 unk_24;
    u32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} UnkM410Struct; // size 0x38

typedef struct UnkM410Struct2 {
    struct {
        u8 unk_00_field0 : 1;
        u8 unk_00_field1 : 1;
        u8 unk_00_field2 : 1;
        u8 unk_00_field3 : 1;
        u8 unk_00_field4 : 1;
        u8 unk_00_field5 : 1;
        u8 unk_00_field6 : 1;
        u8 unk_00_field7 : 1;
    };
    Vec unk_04;
    Vec unk_10;
    Vec unk_1C;
    float unk_28;
    float unk_2C;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    struct UnkM410Struct2 *unk_38;
    s16 unk_3C;
    void *unk_40;
    s16 unk_44;
    s16 unk46;
} UnkM410Struct2; // size 0x48

typedef struct UnkM410Struct3 {
    s32 unk00[6];
    Vec unk_18;
} UnkM410Struct3; // size unknown TODO is this even a thing?

typedef struct UnkM410Struct4 {
    s32 unk_00;
    u8 unk_04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    UnkM410Struct2 *unk_08;
    union {
        UnkM410Struct2 *unk_0C_unk;
        omObjData *unk_0C_obj;
    };
} UnkM410Struct4; // size 0x10

typedef struct UnkM410Struct5 {
    s32 unk_00;
    u32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    u16 unk_34;
    s16 unk_36;
    s16 unk_38;
    s16 unk40;
    float unk_3C;
    float unk_40;
    float unk_44;
    float unk_48;
    float unk_4C;
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    Vec unk_58;
    float unk_64;
    float unk_68;
    float unk_6C;
    Vec unk_70;
    Vec unk_7C;
    Vec unk_88;
} UnkM410Struct5; // size 0x94

typedef struct UnkM410Struct6 {
    float unk_00[4];
} UnkM410Struct6; // size 0x10

typedef struct UnkM410Struct7 {
    u32 unk_00[4];
} UnkM410Struct7; // size 0x10

typedef struct UnkM410Struct8 {
    u16 unk_00;
    u16 unk_02;
    float unk_04;
    float unk_08;
    float unk_0C;
    Vec unk_10;
} UnkM410Struct8; // size 0x1C

typedef struct UnkM410Struct9 {
    s32 unk_00;
    s32 unk_04;
    u32 unk_08;
    float unk_0C;
    float unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk28;
    float unk_2C[2];
    s32 unk34[2];
    s16 unk_3C[2];
    s16 unk_40;
    s16 unk_42;
    s16 unk_44;
    s16 unk46;
} UnkM410Struct9; // size 0x48

typedef struct UnkM410Struct10 {
    float unk_00;
    float unk04;
    float unk_08;
    s32 unk_0C;
} UnkM410Struct10; // size 0x10

typedef struct UnkM410Struct11 {
    float unk_00;
    float unk_04;
    float unk08;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    float unk20;
    float unk_24;
    float unk_28;
    float unk2C;
    float unk_30;
    float unk_34;
    float unk38;
} UnkM410Struct11; // size 0x3C

typedef struct UnkM410Struct12 {
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    float unk_20;
    float unk_24;
} UnkM410Struct12; // size 0x28

typedef struct UnkM410Struct13 {
    UnkM410Struct8 unk_00[16];
    UnkM410Struct11 unk_1C0[32];
    UnkM410Struct12 unk_940[32];
    GXColor unk_E40[5];
    s32 unk_E54;
    u32 unk_E58;
    void *unk_E5C;
} UnkM410Struct13; // size 0xE60

typedef struct UnkM410Struct14 {
    UnkM410Struct9 unk_00[4];
    UnkM410Struct13 unk_120;
    u32 unk_F80;
    void *unk_F84;
    char unkF88[0x2E98];
} UnkM410Struct14; // size 0x3E20

s32 fn_1_27EC(void);
u32 fn_1_2804(void);
u32 fn_1_281C(void);
u32 fn_1_2834(void);
void fn_1_284C(s32 arg0);
u32 fn_1_2864(void);
void fn_1_287C(s32 arg0);
void fn_1_28AC(s32 arg0);
s32 fn_1_28DC(void);
float fn_1_2FD4(float arg8, float arg9, float argA);
float fn_1_30F0(float arg8, float arg9);
void fn_1_31A4(Process *process);
void fn_1_31F8(void);
void fn_1_33A8(Process *objman);
void fn_1_3484(void);
s32 fn_1_76B8(Vec arg0, Vec arg1, u16 arg2);
void fn_1_77E8(void *arg0);
void fn_1_77F8(u16 arg0, Vec *arg1);
void fn_1_7840(u16 arg0, Vec *arg1);
void fn_1_7888(u16 arg0, u16 arg1, Vec *arg2);
s32 fn_1_79F8(s16 arg0, char *arg1, Mtx arg2);
void fn_1_7AC4(HsfObject *arg0, Mtx arg1, char *arg2, Mtx arg3);
void fn_1_7E30(Process *objman);
void fn_1_806C(void);

#endif
