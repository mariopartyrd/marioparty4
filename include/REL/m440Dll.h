#ifndef REL_M440DLL_H
#define REL_M440DLL_H

#include "dolphin/types.h"
#include "game/hu3d.h"

#include "version.h"

#include "game/object.h"
extern s32 rand8(void);

////// TYPES //////
typedef void (*m440Func5)(HU3DMODEL *, struct _unkStruct5 *, Mtx);
typedef void (*m440Func6)(struct _unkStruct6 *);
typedef void (*m440Func14)(struct _unkStruct14 *);

typedef struct _unkStruct {
    float zoom;
    Vec center;
    Vec rot;
} unkStruct;

typedef struct _unkStruct2 {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    char unk10[0xC];
    s16 unk1C;
    char unk20[0x4];
    float unk24;
    char unk28[0x4];
    s16 unk2C;
    s16 unk2E;
    float unk30;
} unkStruct2;

typedef struct _unkStruct3 {
    char unk0[0x34];
    float unk34;
    char unk38[0x8];
    float unk40;
} unkStruct3;

typedef struct _unkStruct4 {
    Vec unk0;
    char unkC[0xC];
    float unk18;
    float unk1C;
    char unk20[0x4];
    float unk24;
    float unk28;
    float unk2C;
    float unk30;
    s16 unk34;
    s16 unk36;
    char unk38[0x4];
    s32 unk3C;
    s16 unk40;
    s16 unk42;
    float unk44;
    Vec unk48;
    Vec unk54;
    s16 unk60;
    s8 unk62;
} unkStruct4; // sizeof 0x64

typedef struct _unkStruct5 {
    s16 unk0;
    s16 unk2;
    u32 unk4;
    u8 unk8;
    m440Func5 unkC;
    ANIMDATA *unk10;
    s16 unk14;
    unkStruct4 *unk18;
    Vec *unk1C;
    HuVec2f *unk20;
    GXColor *unk24;
    void *unk28;
    Vec unk2C;
    Vec unk38;
    Vec unk44;
    Vec unk50;
    HuVec2f *unk5C;
    float unk60;
    float unk64;
} unkStruct5;

typedef struct _unkStruct6 {
    s16 unk0;
    u16 unk2;
    s16 unk4;
    s16 unk6;
    u32 unk8;
    Vec *unkC;
    Vec *unk10;
    Vec *unk14;
    Vec *unk18;
    HuVec2f *unk1C;
    s32 unk20;
    struct _unkStruct8 *unk24;
    HSFMATERIAL *unk28;
    HSFATTRIBUTE *unk2C;
    void *unk30;
    u32 unk34;
    m440Func6 unk38;
    s16 unk3C;
    s16 unk3E;
} unkStruct6; // sizeof 0x40

typedef struct _unkStruct7 {
    GXColor unk0;
    Vec unk4;
} unkStruct7; // sizeof 0x10

typedef struct _unkStruct11 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} unkStruct11;

typedef struct _unkStruct8 {
    unkStruct11 unk0[3];
    s16 unk18[3];
    s16 unk1E;
    unkStruct11 unk20[3];
    char unk38[0x30];
    float unk68[5];
    Vec unk7C;
    Vec unk88;
    Vec unk94;
    Vec unkA0;
    Vec unkAC;
    Vec unkB8;
    Vec unkC4;
} unkStruct8; // sizeof 0xD0

typedef struct _unkStruct10 {
    s16 unk0;
    s16 unk2;
    unkStruct11 unk4[3];
    u32 unk1C;
    unkStruct11 *unk20;
    char unk24[0xC];
} unkStruct10; // sizeof 0x30

typedef struct _unkStruct12 {
    char unk0[0xA];
    u8 unkA;
    u8 unkB[3];
    u8 unkE[3];
    char unk12[0x2];
    float unk14;
    char unk18[0x4];
    float unk1C;
    char unk20[0x10];
    u32 unk30;
    u32 unk34;
    s32 *unk38;
} unkStruct12;

typedef struct _unkStruct13 {
    char unk0[0xA];
    u8 unkA;
    char unkB[0x15];
    float unk20;
    char unk24[0x40];
    u32 unk64;
    u32 unk68;
    char unk6C[0x14];
    struct _unkStruct15 *unk80;
} unkStruct13; // sizeof 0x84
typedef struct _unkStruct14 {
    s16 unk0;
    s16 unk2;
    char unk4[0x8];
    void *unkC;
    char unk10[0x4];
    void *unk14;
    unkStruct4 *unk18;
    void *unk1C;
    char unk20[0x4];
    GXColor *unk24;
    HSFMATERIAL *unk28;
    HSFATTRIBUTE *unk2C;
    void *unk30;
    u32 unk34;
    m440Func14 unk38;
    s16 unk3C;
} unkStruct14;

typedef struct _unkStruct15 {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s32 unkC;
} unkStruct15;

// object.c
typedef struct _unkObjStruct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    Vec unk18;
    Vec unk24;
    Vec unk30;
    Vec unk3C;
    u8 unk48;
    s16 unk4A;
    float unk4C;
    s16 unk50;
    s16 unk52;
    s16 unk54;
    s16 unk56;
    s16 unk58;
    s16 unk5A;
    float unk5C;
    s16 unk60;
    s16 unk62;
    char unk64[0x4];
    float unk68;
    float unk6C;
    float unk70;
} unkObjStruct;

////// BSS //////
extern OMOBJ *lbl_1_bss_C0[4];

////// DATA //////
// main.c
extern float lbl_1_data_0[5];
extern s16 lbl_1_data_14[6];
// object.c
extern s16 lbl_1_data_1D8;

////// FUNCTIONS //////
// main.c
void ObjectSetup(void);
void fn_1_3C4(OMOBJ *object);
void fn_1_434(OMOBJ *object);
s32 fn_1_4A4(void);
s32 fn_1_6C8(void);
void fn_1_8F0(OMOBJ *object);
void fn_1_AE0(OMOBJ *object);
u8 fn_1_E14(OMOBJ *object);
u8 fn_1_1138(OMOBJ *object);
void fn_1_16D8(void);
void fn_1_1708(void);
void fn_1_1768(void);
s16 fn_1_17CC(void);
s16 fn_1_17F4(void);
void fn_1_181C(void);
u8 fn_1_1890(void);
void fn_1_18E0(void);
u8 fn_1_1954(void);
void fn_1_19B0(void);
void fn_1_1CAC(void);
void fn_1_2240(HU3DMODEL *data, unkStruct5 *, Mtx);
u16 fn_1_23E4(u16);
void fn_1_2428(u16, u16);
void fn_1_2470(OMOBJ *object);
void fn_1_2A74(OMOBJ *object);
void fn_1_2AB4(OMOBJ *object);
void fn_1_2B04(OMOBJ *object);
void fn_1_2CA8(OMOBJ *object);
void fn_1_2D28(OMOBJ *object);
void fn_1_33D4(OMOBJ *object);
void fn_1_3DD8(OMOBJ *object);
void fn_1_4558(OMOBJ *object);
void fn_1_45BC(OMOBJ *object);
void fn_1_4660(OMOBJ *object);
void fn_1_46E0(OMOBJ *object);
void fn_1_4A20(OMOBJ *object);
void fn_1_4B44(OMOBJ *object);
void fn_1_4E00(s16, float);
s16 fn_1_4E2C(void);
s16 fn_1_4E54(s16);
u16 fn_1_4EA8(u16);
void fn_1_4EEC(u16, u16);
void fn_1_4F34(unkStruct6 *);
void fn_1_5010(unkStruct6 *, Vec *, float);
void fn_1_57B4(unkStruct6 *);
void fn_1_5C2C(s16, HSFOBJECT *, unkStruct6 *, u16);
void fn_1_6554(unkStruct6 *, HSFOBJECT *);
void fn_1_6B58(unkStruct6 *, HSFOBJECT *);
void fn_1_71FC(unkStruct6 *, Vec *, s16, Vec);
void fn_1_7934(unkStruct6 *, unkStruct8 *, Vec *);
void fn_1_7D60(HSFBITMAP *, HSFATTRIBUTE *, s16);
void fn_1_806C(HU3DMODEL *, Mtx);
void fn_1_8470(HSFMATERIAL *, HSFATTRIBUTE *);
void fn_1_8AC4(Mtx);
void fn_1_8D1C(void);
void fn_1_91A4(Vec *, Vec *, Vec *, float[5]);
float fn_1_927C(float, float, float);
void fn_1_9344(Mtx, Mtx);
float fn_1_93C0(float, float, float);
float fn_1_93D0(float, float, float, float);
unkStruct4 *fn_1_942C(s16, Vec *, Vec *, float, GXColor *);
s16 fn_1_956C(ANIMDATA *, s16, float, s16, s16);
void fn_1_9AB0(s16);
unkStruct5 *fn_1_9B10(s16);
unkStruct4 *fn_1_9B3C(s16, s16);
void fn_1_9B94(s16, m440Func5);
void fn_1_9BCC(s16, u8);
void fn_1_9C04(HU3DMODEL *, Mtx);
void fn_1_A1B8(HuVec2f *, s16, s16, float, float);
void fn_1_A284(HuVec2f *, HuVec2f *, s16, float, float);
void fn_1_A328(Vec *, Vec *, Vec *, s16);
void fn_1_A390(HU3DMODEL *, Mtx);
void fn_1_AA94(void);
// object.c
void fn_1_AE08(HUPROCESS *);
void fn_1_AEE4(OMOBJ *);
void fn_1_B17C(OMOBJ *);
void fn_1_B180(OMOBJ *);
void fn_1_B3A4(OMOBJ *);
void fn_1_B884(OMOBJ *, unkObjStruct *);
void fn_1_C1D4(OMOBJ *, unkObjStruct *);
void fn_1_C944(OMOBJ *, unkObjStruct *);
s16 fn_1_CFAC(unkObjStruct *, u8);
void fn_1_D24C(unkObjStruct *, float, float);
void fn_1_D34C(OMOBJ *, unkObjStruct *);
void fn_1_D7F8(OMOBJ *, unkObjStruct *);
void fn_1_E034(OMOBJ *, unkObjStruct *);
u8 fn_1_E8AC(OMOBJ *, unkObjStruct *);
s32 fn_1_ED88(OMOBJ *, s16, u32);
void fn_1_EE78(void);
void fn_1_EF50(void);
s16 fn_1_F0FC(void);
void fn_1_F168(void);
void fn_1_F228(void);
u16 fn_1_F4C0(unkObjStruct *, u16);
void fn_1_F4D4(unkObjStruct *, u16, u16);
s32 fn_1_F4FC(s32);

#endif
