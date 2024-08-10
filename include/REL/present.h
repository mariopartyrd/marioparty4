#ifndef PRESENT_H
#define PRESENT_H

#include "game/object.h"
// #include "REL/option.h" // this causes problems because of the extern bsses

typedef struct UnkWindowDataStruct {
    /* 0x00 */ Process *process;
    /* 0x04 */ s16 window;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u32 unk18;
    /* 0x1C */ s32 choice;
    /* 0x20 */ s32 unk_20;
} UnkWindowDataStruct; // this already exists in option.h

typedef struct UnkPresentStruct {
    /* 0x00 */ UnkWindowDataStruct *unk_00;
    /* 0x04 */ s32 unk_04;
} UnkPresentStruct;

typedef struct UnkPresentStruct2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ omObjData *unk_10[134];
    /* 0x228 */ UnkWindowDataStruct *unk_228;
    /* 0x22C */ UnkWindowDataStruct *unk_22C;
    /* 0x230 */ s16 sprite;
    /* 0x234 */ s32 unk_234;
    /* 0x238 */ s32 unk_238;
    /* 0x23C */ float unk_23C;
    /* 0x240 */ float unk_240;
    /* 0x244 */ float unk_244;
    /* 0x248 */ float unk_248;
    /* 0x24C */ float unk_24C;
    /* 0x250 */ float unk_250;
    /* 0x254 */ float unk_254;
    /* 0x258 */ float unk_258;
    /* 0x25C */ float unk_25C;
    /* 0x260 */ float unk_260;
    /* 0x264 */ float unk_264;
    /* 0x268 */ float unk_268;
    /* 0x26C */ float unk_26C;
    /* 0x270 */ s32 unk_270[60];
} UnkPresentStruct2;

typedef struct UnkPresentStruct3 {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ GXColor unk_18;
} UnkPresentStruct3;

typedef struct UnkPresentStruct4 {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec unk_18;
} UnkPresentStruct4;

typedef struct UnkPresentStruct5 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ float x;
    /* 0x0C */ float y;
    /* 0x10 */ float z;
    /* 0x14 */ float unk_14;
    /* 0x18 */ s32 unk18[2];
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ float unk_30;
    /* 0x34 */ float unk_34;
    /* 0x38 */ float unk_38;
    /* 0x3C */ s32 unk3C[3];
    /* 0x48 */ float unk_48;
    /* 0x4C */ float unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
} UnkPresentStruct5;

typedef struct UnkPresentStruct6 {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
} UnkPresentStruct6; // looks like a struct in option/scene.c

typedef struct UnkPresentStruct6Weird {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
} UnkPresentStruct6Weird; // looks like a struct in option/scene.c

typedef struct UnkPresentCameraStruct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec target;
    /* 0x18 */ Vec up;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ Vec unk_2C;
    /* 0x38 */ Vec unk_38;
    /* 0x44 */ float unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ float unk_50;
    /* 0x54 */ float unk_54;
    /* 0x58 */ Vec unk_58;
    /* 0x64 */ Vec unk_64;
    /* 0x70 */ float unk70;
    /* 0x74 */ float unk74;
    /* 0x78 */ float unk78;
    /* 0x7C */ float unk_7C;
    /* 0x80 */ float unk_80;
    /* 0x84 */ float unk_84;
    /* 0x88 */ float unk_88;
    /* 0x8C */ float unk_8C;
    /* 0x90 */ float unk_90;
    /* 0x94 */ float unk_94;
    /* 0x98 */ float unk_98;
} UnkPresentCameraStruct;

typedef struct UnkPresentNestedInnerStruct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk_0C;
} UnkPresentNestedInnerStruct;

typedef struct UnkPresentNestedOuterStruct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ UnkPresentNestedInnerStruct unk_04[11];
} UnkPresentNestedOuterStruct;

typedef struct UnkPresentStruct7 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ float unk_04;
} UnkPresentStruct7;

extern omObjData *lbl_1_bss_10;
extern omObjData *lbl_1_bss_8;
extern Process *lbl_1_bss_4;

void fn_1_144(s16 arg0, s32 arg1, s32 arg2);
void fn_1_334(s16 arg0, s32 arg1, float arg8, s32 arg2);
omObjData *fn_1_6B4();
void fn_1_920(omObjData *object, float arg8, float arg9, float argA, s32 arg1);
void fn_1_9A4(omObjData *object, float arg8, float arg9, float argA, s32 arg1);
void fn_1_BF8(omObjData *object);
omObjData *fn_1_1458(void);
void fn_1_180C(omObjData *object, s32 arg1);
s32 fn_1_1850(omObjData *object);
omObjData *fn_1_39A8(void);
UnkWindowDataStruct *fn_1_3EA4(s32 arg0);
void fn_1_4080(UnkWindowDataStruct *windowData);
void fn_1_4098(UnkWindowDataStruct *windowData);
void fn_1_40B0(UnkWindowDataStruct *windowData, u32 mess);
omObjData *fn_1_42F4(void);
void fn_1_45C0(omObjData *arg0, s32 arg1);
s32 fn_1_4604(omObjData *object);

#endif
