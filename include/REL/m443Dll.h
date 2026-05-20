#ifndef REL_M443DLL_H
#define REL_M443DLL_H

#include "game/object.h"

typedef struct M443DllCameraStruct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u32 unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    Vec unk_1C;
    Vec unk_28;
    float unk_34;
    s32 unk_38;
    s32 unk_3C;
    float unk_40;
    float unk_44;
    float unk_48;
    float unk_4C;
    float unk_50;
    Vec unk_54;
    char unk_60[0xC];
    float unk_6C;
    float unk_70;
    char unk74[0x4];
    float unk_78;
    float unk_7C;
    float unk_80;
    char unk84[0x1C];
    u32 unk_A0;
} M443DllCameraStruct; /* size = 0xA4 */

void fn_1_3FE8(u32 arg0);
u32 fn_1_3FFC(void);
M443DllCameraStruct *fn_1_40AC(s32 arg0);
M443DllCameraStruct *fn_1_4148(u32 arg0);
M443DllCameraStruct *fn_1_41B0(u32 arg0);
void fn_1_421C(s32 arg0, s32 arg1);
u32 fn_1_42CC(void);
u32 fn_1_42E4(void);
u32 fn_1_42FC(void);
void fn_1_4314(s32 arg0, float arg8);
s32 fn_1_4368(s32 arg0);
void fn_1_43AC(s32 arg0);
void fn_1_43DC(s32 arg0);
float fn_1_488C(float arg8, float arg9, float argA);
void fn_1_4A5C(Process *arg0);
void fn_1_4AB0(void);
void fn_1_5444(Process *arg0);
void fn_1_565C(void);

#endif
