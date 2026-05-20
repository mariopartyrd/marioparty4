#ifndef REL_M435DLL_H
#define REL_M435DLL_H

#include "game/object.h"

#include "dolphin.h"

// For future reference: m435 has many functions and structs in common with m436 and m437.

typedef struct {
    /* 0x00 */ void (*unk00)(void);
    /* 0x04 */ s32 (*unk04)(void);
    /* 0x08 */ s32 unk08;
} StructData3A0; // Size 0xC

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ StructData3A0* unk0C;
    /* 0x10 */ void (*unk10)(void);
    /* 0x14 */ s32 (*unk14)(void);
} StructBss84; // Size 0x18

typedef struct {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ void (*unk04)(void);
    /* 0x08 */ void (*unk08)(void);
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
    /* 0x40 */ float unk40;
    /* 0x44 */ float unk44;
    /* 0x48 */ s32 unk48[7];
    /* 0x64 */ float unk64[7];
} StructBssE08; // Size 0x80

typedef struct {
    /* 0x000 */ omObjData* unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ char unk0C[4];
    /* 0x010 */ char unk10[1024]; // Actual char array (unsure about length)
    /* 0x410 */ s32 unk410;
    /* 0x414 */ s32 unk414[20];
    /* 0x464 */ s32 unk464;
    /* 0x468 */ s32 unk468;
    /* 0x46C */ s32 unk46C;
    /* 0x470 */ float unk470;
    /* 0x474 */ float unk474;
    /* 0x478 */ float unk478;
    /* 0x47C */ float unk47C;
} StructFn19894; // Size 0x480

float fn_1_1526C(float arg0, float arg1, float arg2, float arg3);
float fn_1_15294(float arg0, float arg1, float arg2);
float fn_1_152D4(float arg0, float arg1, float arg2, float arg3);
float fn_1_1539C(float arg0, float arg1, float arg2, float arg3);
void fn_1_154C4(StructBss84* arg0, StructData3A0* arg1);
s32 fn_1_15520(StructBss84* arg0);
void fn_1_1561C(StructBss84* arg0, s32 arg1);
s32 fn_1_15670(StructBss84* arg0, s32 arg1);
s32 fn_1_156AC(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_157BC(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_15934(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_15E50(StructBssE08* arg0);
void fn_1_161B0(StructBssE08* arg0, float arg1);
void fn_1_169F4(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3, float arg4);
void fn_1_17804(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3, float arg4);
void fn_1_188E0(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3, float arg4);
void fn_1_19530(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6);
void fn_1_195F4(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6);
void fn_1_19658(omObjData* arg0, s32 arg1, float arg2, s32 arg3);
void fn_1_19894(StructFn19894* arg0, s32 arg1);
void fn_1_198F8(StructFn19894* arg0, s32 arg1);
void fn_1_19960(StructFn19894* arg0, s32 arg1);
void fn_1_19968(StructFn19894* arg0, s32 arg1);
void fn_1_19974(StructFn19894* arg0, s32 arg1);
void fn_1_1A33C(Process* arg0, StructFn19894* arg1, s32 arg2, char* arg3, s32 arg4, s32 arg5);

#endif
