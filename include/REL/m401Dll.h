#ifndef REL_M401DLL_H
#define REL_M401DLL_H

#include "game/object.h"
#include "dolphin.h"

extern float lbl_2_bss_12C;
extern float lbl_2_bss_128;
extern float lbl_2_bss_124;
extern s16 lbl_2_bss_120;
extern Vec lbl_2_bss_6C;
extern Vec lbl_2_bss_60;
extern float lbl_2_bss_50;
extern OMOBJ **lbl_2_bss_118;

typedef struct m401_work_player {
	s16 unk0;
	s32 unk4;
	s32 unk8;
	Vec pos;
	Vec unk18;
	Vec unk24;
	Vec unk30;
	Vec unk3C;
	OMOBJ *unk48;
	OMOBJ *unk4C;
	OMOBJ *unk50;
	OMOBJ *unk54;
	Vec unk58;
	float unk64;
	s16 unk68;
	s16 unk6A;
	s16 unk6C;
	s16 unk6E;
	s16 unk70;
	s16 coinCnt;
	s16 unk74;
	s16 unk76;
	s16 unk78;
	s16 unk7A;
	s16 unk7C;
	s16 unk7E;
	float unk80;
	s16 unk84;
	s16 unk86;
	float swimSpeed;
	s16 unk8C;
	s16 unk8E;
	s16 unk90;
	s16 unk92;
	Vec unk94;
	s8 unkA0;
	s8 unkA1;
} M401WorkPlayer;

typedef struct unkwork_10A88 {
	Vec unk0;
	OMOBJ *unkC;
	s16 unk10;
	s16 unk12;
	s16 unk14;
	s32 unk18;
	float unk1C;
} UnkWork10A88;

void fn_2_169C(s16 arg0);

void fn_2_A8A4(OMOBJ *object, float x, float y, float z);

void fn_2_10240(Vec *arg0, Vec *arg1);
void fn_2_1041C(void);
void fn_2_10710(void);

void fn_2_1079C(void);
OMOBJ *fn_2_10A88(Vec *arg0, s16 arg1);

OMOBJ *fn_2_141B0(void);
OMOBJ *fn_2_14640(HUPROCESS *objman);

#endif
