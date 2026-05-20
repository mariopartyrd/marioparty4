#ifndef REL_M406DLL_H
#define REL_M406DLL_H

#include "game/object.h"
#include "game/process.h"

typedef struct UnkM406Struct2 {
    /* 0x00 */ float unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ Vec unk_08;
    /* 0x14 */ Vec unk_14;
} UnkM406Struct2; /* size = 0x20 */

s32 fn_1_122C(void);
void fn_1_123C(void);
void fn_1_1274(s32 arg0);
void fn_1_1284(void);
void fn_1_12BC(void);

omObjData *fn_1_2308(Process *arg0);
void fn_1_2BEC(void);
void fn_1_3064(s32 arg0);
void fn_1_696C(float arg8);
void fn_1_6B5C(void);
void fn_1_69C0(Vec *arg0);
s32 fn_1_6A44(Vec arg0);
void fn_1_6BB4(Vec *arg0);
void fn_1_82C8(Mtx arg0, s32 arg1, float arg8);
s32 fn_1_94C0(Mtx arg0, s32 arg1, s32 arg2);
void fn_1_B104(float arg8);
void fn_1_B25C(void);
void fn_1_B41C(void);
void fn_1_D65C(Process *arg0);
void fn_1_D8B0(void);

extern UnkM406Struct2 *lbl_1_bss_B8;
extern s32 lbl_1_bss_B4;

#endif
