#ifndef REL_MPEXDLL_H
#define REL_MPEXDLL_H

#include "game/object.h"

typedef void (*MpexDllUnkFunc)(void);

typedef struct MpexDllUnkStruct {
    /* 0x00 */ MpexDllUnkFunc unk_00;
    /* 0x04 */ void *unk_04; // func, unknown args
    /* 0x08 */ Vec unk_08;
    /* 0x14 */ Vec unk_14;
    /* 0x20 */ Vec unk_20;
    /* 0x2C */ Vec unk_2C;
    /* 0x38 */ float unk_38;
    /* 0x3C */ float unk_3C;
    /* 0x40 */ s32 unk_40;
} MpexDllUnkStruct; /* size = 0x44 */

void fn_1_374(void);
void fn_1_298(void);
void fn_1_910(MpexDllUnkFunc arg0);
void fn_1_25C4(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_28E0(omObjData *arg0, s32 arg1, Vec arg2, float arg8, float arg9, float argA, s32 arg3, s32 arg4);
Process *fn_1_3044(Process *arg0);

void fn_1_1264C(Process *arg0);
s32 fn_1_140B0(s32 arg0, s32 arg1);
void fn_1_148BC(s32 arg0);
void fn_1_148E4(s32 arg0);
void fn_1_1A5A4(s32 arg0);
float fn_1_1B714(float arg8, float arg9, float argA, float argB);
void fn_1_1B810(void);
void fn_1_1B834(void);
void fn_1_1B9F4(void);
void fn_1_1BA78(u32 arg0, s32 arg1, s32 arg2);
void fn_1_1BB4C(u32 arg0, s32 arg1);
s32 fn_1_1BBA4(s32 arg0);
void fn_1_1BD00(u32 arg0, s32 arg1);
void fn_1_1BF1C(u32 arg0);
void fn_1_1C120(void);

void fn_1_1B7D0(s32 arg0);

s32 fn_1_1D02C(s32 arg0);

extern u8 lbl_1_bss_6AC;
extern s32 lbl_1_bss_63C[0x1C];
extern MpexDllUnkStruct lbl_1_bss_64;

#endif
