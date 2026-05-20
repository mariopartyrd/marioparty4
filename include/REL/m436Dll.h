#ifndef REL_M436DLL_H
#define REL_M436DLL_H

#include "game/object.h"

#include "dolphin.h"

// For future reference: m436 has many functions and structs in common with m437.

typedef struct {
    /* 0x00 */ void (*unk00)(void);
    /* 0x04 */ s32 (*unk04)(void);
    /* 0x08 */ s32 unk08;
} StructData1E8; // Size 0xC

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ StructData1E8* unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ void (*unk10)(void);
    /* 0x14 */ s32 (*unk14)(void);
} StructBssC0; // Size 0x18

typedef struct {
    /* 0x00 */ void (*unk00)(void);
    /* 0x04 */ float unk04;
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
    /* 0x40 */ s32 unk40[7];
    /* 0x5C */ float unk5C[7];
} StructBss32C; // Size 0x78

float fn_1_110FC(float arg0, float arg1, float arg2);
float fn_1_1113C(float arg0, float arg1, float arg2, float arg3);
float fn_1_11164(float arg0, float arg1, float arg2, float arg3);
float fn_1_1122C(float arg0, float arg1, float arg2, float arg3);
float fn_1_112F4(float arg0, float arg1, float arg2, float arg3);
void fn_1_113CC(omObjData* arg0, s32 arg1, omObjData* arg2, s32 arg3);
s32 fn_1_11708(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_11818(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_11990(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_11B18(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_11D18(StructBssC0* arg0, StructData1E8* arg1);
s32 fn_1_11D74(StructBssC0* arg0);
s32 fn_1_11E70(StructBssC0* arg0, s32 arg1);
s32 fn_1_11F04(StructBssC0* arg0, s32 arg1);
void fn_1_12294(StructBss32C* arg0);
void fn_1_125F4(StructBss32C* arg0, float arg1);
void fn_1_13C48(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3, float arg4);
void fn_1_14D24(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3, float arg4);

#endif
