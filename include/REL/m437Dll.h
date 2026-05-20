#ifndef REL_M437DLL_H
#define REL_M437DLL_H

#include "game/object.h"

#include "dolphin.h"

typedef struct {
    /* 0x00 */ void (*unk00)(void);
    /* 0x04 */ s32 (*unk04)(void);
    /* 0x08 */ s32 unk08;
} StructData204; // Size 0xC

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ StructData204* unk04;
    /* 0x08 */ void (*unk08)(void);
    /* 0x0C */ s32 (*unk0C)(void);
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} StructBss50; // Size 0x18

typedef struct {
    /* 0x00 */ void (*unk00)(void);
    /* 0x04 */ void (*unk04)(void);
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44[7];
    /* 0x60 */ float unk60[7];
} StructBss160; // Size 0x7C

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ char unk04[128];
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ s32 unk94[20];
    /* 0xE4 */ omObjData* unkE4;
} StructFn15CD0; // Size 0xE8

float fn_1_11348(float arg0, float arg1, float arg2, float arg3);
float fn_1_11370(float arg0, float arg1, float arg2);
float fn_1_113B0(float arg0, float arg1, float arg2, float arg3);
float fn_1_11478(float arg0, float arg1, float arg2, float arg3);
float fn_1_11540(float arg0, float arg1, float arg2, float arg3);
void fn_1_11668(StructBss50* arg0, StructData204* arg1);
s32 fn_1_116C4(StructBss50* arg0);
s32 fn_1_117C0(StructBss50* arg0, s32 arg1);
s32 fn_1_11854(StructBss50* arg0, s32 arg1);
s32 fn_1_11890(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_119A0(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_11B18(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 fn_1_11CE0(omObjData* arg0, Vec arg1, float arg2, float arg3, float arg4, float arg5, s32 arg6);
void fn_1_12ABC(StructBss160* arg0);
void fn_1_12E14(StructBss160* arg0, float arg1);
void fn_1_13658(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3, float arg4);
void fn_1_15544(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3, float arg4);
void fn_1_15CD0(StructFn15CD0* arg0, s32 arg1);
void fn_1_15DC8(StructFn15CD0* arg0);
void fn_1_164B0(Process* arg0, StructFn15CD0* arg1, s32 arg2, const char* arg3);
void fn_1_1660C(Process* arg0, StructFn15CD0* arg1, s32 arg2, s32 arg3);

#endif
