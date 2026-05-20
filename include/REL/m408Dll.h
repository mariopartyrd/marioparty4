#ifndef REL_M408DLL_H
#define REL_M408DLL_H

#include "game/object.h"

typedef struct work_2FAC {
	u16 unk0;
	u16 unk2;
	u32 unk4;
	u32 unk8;
	float unkC;
	u32 unk10;
	u32 unk14;
	u32 unk18;
	Vec unk1C;
	Vec unk28;
	Vec unk34;
	Vec unk40;
	Vec unk4C;
	Vec unk58;
	float unk64;
	Vec unk68;
	u32 unk74;
	u32 unk78;
	float unk7C[2];
	float unk84[2];
	s16 unk8C;
	u16 unk8E;
	float unk90;
	Vec unk94;
	Vec unkA0;
	Vec unkAC;
	Vec unkB8;
} Work2FAC;

void fn_1_67C4(u16 arg0, u16 arg1);
u32 fn_1_6878(void);
float fn_1_6888(void);
Work2FAC *fn_1_68A8(s32 arg0);
void fn_1_817C(Vec *arg0, Vec *arg1);
void fn_1_84C4(float arg0, float arg1, float arg2, float arg3, float arg4, float arg5);
float fn_1_883C(float arg0, float arg1, float arg2);
void fn_1_C3C0(Vec *arg0, Vec *arg1);
u32 fn_1_C43C(void);
s32 fn_1_CE68(void);
void fn_1_CEEC(void);
void fn_1_8958(Process *objman);
void fn_1_C44C(Process *objman);
s32 fn_1_11670(void);
void fn_1_118D0(Process *objman);
s32 fn_1_162CC(Vec *arg0, Vec *arg1);

extern s32 lbl_1_bss_44;
extern s32 lbl_1_bss_40;

#endif
