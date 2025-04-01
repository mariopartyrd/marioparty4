#ifndef MENTDLL_H
#define MENTDLL_H

#include "game/object.h"
extern s32 lbl_1_data_0[][4];

// the prev and current struct member might be vice versa
typedef struct MentDllUnkBss64Struct {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ void (*func2)(float arg9);
    /* 0x08 */ Vec center;
    /* 0x14 */ Vec prevCenter;
    /* 0x20 */ Vec rot;
    /* 0x2C */ Vec prevRot;
    /* 0x38 */ float zoom;
    /* 0x3C */ float prevZoom;
    /* 0x40 */ s32 unk_40;
} MentDllUnkBss64Struct; /* size = 0x44 */
extern MentDllUnkBss64Struct lbl_1_bss_64;

float fn_1_20C(float arg8, float arg9, float argA, float argB);
float fn_1_234(float arg8, float arg9, float argA);
float fn_1_254(float arg8, float arg9, float argA, float argB);
float fn_1_32C(float arg8, float arg9, float argA, float argB);
float fn_1_3F4(float arg8, float arg9, float argA, float argB);
void fn_1_4B0(s32 arg0);
void fn_1_4D8(void);
void fn_1_50C(void);
void fn_1_5E8(s32 arg0);
void fn_1_6D0(void);
s32 fn_1_1434(s32 arg0, s32 arg1, s32 arg2);
void fn_1_16AC(s32 arg0);
void fn_1_1968(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 fn_1_1A5C(s32 arg0, s32 arg1, s32 arg2);
s32 fn_1_1DD8(s32 arg0, s32 arg1, s32 arg2);
s32 fn_1_2154(s32 arg0);
void fn_1_2318(s32 arg0);
void fn_1_2808(void (*arg0)(void));
void fn_1_2844(Process *arg0, void (*arg1)(void));
void fn_1_29A0(MentDllUnkBss64Struct *arg0);
void fn_1_4138(MentDllUnkBss64Struct *arg0, MentDllUnkBss64Struct *arg1, float arg8, float arg9, float argA);
void fn_1_5150(MentDllUnkBss64Struct *arg0, MentDllUnkBss64Struct *arg1, float arg8, float arg9, float argA);
void fn_1_5818(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_59A0(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_5C08(omObjData *arg0);
void fn_1_5CDC(omObjData *arg0, s32 arg1, s32 arg2);
void fn_1_5D38(omObjData *arg0, s32 arg1, Vec arg2, float arg8, float arg9, float argA, s32 arg3, s32 arg4);
void fn_1_6534(s32, s32, float, float);
void fn_1_658C(Process *arg0);

#endif
