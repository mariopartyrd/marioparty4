#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/chrman.h"

#include "game/object.h"
#include "game/objsub.h"
#include "game/audio.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/minigame_seq.h"
#include "game/gamework_data.h"

#include "ext_math.h"
#include "REL/m431Dll.h"

typedef struct bss_struct_62C {
	u8 unk0;
	float unk4;
} BssStruct62C;

BssStruct62C lbl_1_bss_62C[10];
omObjData *lbl_1_bss_61C[4];
Bss12CStruct lbl_1_bss_12C[4];
s32 lbl_1_bss_AC[16][2];
u32 lbl_1_bss_9C[4];
s8 lbl_1_bss_98;

float lbl_1_data_1D0 = 18;
float lbl_1_data_1D4[8] = {
	30.000002f,
	0,
	20.0f,
	0,
	20.0f,
	50.0f,
	20.0f,
	30.000002f
};

u32 lbl_1_data_1F4[8] = {
	DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
	DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02),
	DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
	-1,
	DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x48),
	DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x49),
	DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
	DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x72)
};

char *lbl_1_data_230[8] = {
	"test11_tex_we-itemhook-r",
	"test11_tex_we-itemhook-r",
	"test11_tex_we-itemhook-r",
	"test11_tex_we-itemhook-r",
	"test11_tex_we-itemhook-r",
	"test11_tex_we-itemhook-r",
	"test11_tex_we-itemhook-r",
	"test11_tex_we-itemhook-r"
};

void fn_1_858C(omObjData *object);
void fn_1_9440(omObjData *object);

void fn_1_B384(Process *objman);

void fn_1_7ABC(Process *objman)
{
	Vec sp20;
	Vec sp14;
	Vec sp8;
	Bss12CStruct *temp_r31;
	s16 temp_r30;
	s16 temp_r29;
	BssStruct62C *temp_r28;
	omObjData *temp_r26;
	omMakeGroupEx(objman, 0, 4);
	omGetGroupMemberListEx(objman, 0);
	memset(lbl_1_bss_12C, 0, sizeof(lbl_1_bss_12C));
	for(temp_r30=0, temp_r29=0; temp_r30<4; temp_r30++) {
		temp_r31 = &lbl_1_bss_12C[GWPlayerCfg[temp_r30].group];
		if(GWPlayerCfg[temp_r30].group != 0 && GWPlayerCfg[temp_r30].group != 1) {
			break;
		}
		temp_r31->unk0[temp_r31->unk8++] = temp_r30;
		if(temp_r31->unk8 == 2) {
			temp_r29++;
		}
	}
	if(temp_r29 != 2) {
		GWPlayerCfg[0].group = GWPlayerCfg[1].group = 0;
		GWPlayerCfg[2].group = GWPlayerCfg[3].group = 1;
		lbl_1_bss_12C[0].unk0[0] = 0;
		lbl_1_bss_12C[0].unk0[1] = 1;
		lbl_1_bss_12C[0].unk8 = 2;
		lbl_1_bss_12C[1].unk0[0] = 2;
		lbl_1_bss_12C[1].unk0[1] = 3;
		lbl_1_bss_12C[1].unk8 = 2;
	}
	for(temp_r30=0, temp_r28 = &lbl_1_bss_62C[0]; temp_r30<10; temp_r30++, temp_r28++) {
		temp_r28->unk0 = 1;
		temp_r28->unk4 = lbl_1_data_1D0+(temp_r30*36.0f);
	}
	lbl_1_bss_12C[0].unkC.x = -317;
	lbl_1_bss_12C[1].unkC.x = 317;
	lbl_1_bss_12C[0].unkC.y = lbl_1_bss_12C[1].unkC.y = 0;
	lbl_1_bss_12C[0].unkC.z = lbl_1_bss_12C[1].unkC.z = 100;
	lbl_1_bss_12C[0].unk18 = lbl_1_bss_12C[1].unk18 = 230;
	for(temp_r30=0, temp_r31 = &lbl_1_bss_12C[0]; temp_r30<2; temp_r30++, temp_r31++) {
		sp8.x = temp_r31->unkC.x;
		sp8.y = temp_r31->unkC.y;
		sp8.z = temp_r31->unkC.z;
		for(temp_r29=0; temp_r29<10; temp_r29++) {
			sp14.x = sp20.x = (temp_r31->unk18*sind(lbl_1_bss_62C[temp_r29].unk4))+sp8.x;
			sp14.z = sp20.z = (temp_r31->unk18*cosd(lbl_1_bss_62C[temp_r29].unk4))+sp8.z;
			sp14.y = sp8.y;
			sp20.y = sp8.y-50;
			fn_1_6184(&sp8, &temp_r31->unk1C[temp_r29]);
			temp_r31->unkE4[temp_r29][0] = sp14.x;
			temp_r31->unkE4[temp_r29][1] = sp14.z;
		}
		temp_r31->unk138[0] = 0;
	}
	for(temp_r30=0; temp_r30<4; temp_r30++) {
		OSReport("PNo:%d Grp:%d\n", temp_r30, GWPlayerCfg[temp_r30].group);
		temp_r26 = omAddObjEx(objman, 99, 0, 0, -1, fn_1_858C);
		lbl_1_bss_61C[temp_r30] = omAddObjEx(objman, 100, 9, 8, 0, fn_1_9440);
		lbl_1_bss_61C[temp_r30]->work[0] = temp_r26->work[0] = temp_r30;
		
	}
	fn_1_B384(objman);
}

s16 lbl_1_data_260[4] = { 0, 0, 0, 0 };
s16 lbl_1_data_268[2] = { 0, 9 };

s16 fn_1_8AD4(Bss61CWork *arg0, s16 arg1, s16 arg2, s16 *arg3, u8 arg4);
void fn_1_8CC0(omObjData *object);

s16 fn_1_B4F8(float arg0);
s16 fn_1_B530(s16 arg0);

s32 fn_1_7FB8(s16 arg0)
{
	Bss61CWork *temp_r31;
	Bss12CStruct *temp_r30 = &lbl_1_bss_12C[arg0];
	s16 sp18[4] = { 0, 9, 9, 0};
	
	s16 sp14[2];
	s16 sp10[2];
	s16 spC[2];
	s16 spA;
	s16 temp_r29;
	s32 temp_r28;
	if(lbl_1_bss_98 != 0) {
		(void)lbl_1_bss_98;
	} else {
		for(temp_r29=0, temp_r28=0; temp_r29<2; temp_r29++) {
			temp_r31 = lbl_1_bss_61C[temp_r30->unk0[temp_r29]]->data;
			if((temp_r31->unk0 & 0xC0) || (temp_r31->unk0 & 0x600)) {
				temp_r28 = 1;
			}
			fn_1_8CC0(lbl_1_bss_61C[temp_r30->unk0[temp_r29]]);
			sp10[temp_r29] = temp_r31->unk40 = fn_1_B4F8(temp_r31->unk44.y);
			spC[temp_r29] = fn_1_B530(temp_r31->unk40);
			
		}
		if(temp_r28 != 0) {
			return 0;
		}
		if(spC[0] != spC[1]) {
			if(spC[0] == 0) {
				temp_r31 = lbl_1_bss_61C[temp_r30->unk0[0]]->data;
				temp_r31->unk84 = lbl_1_data_268[0];
				temp_r31->unk14->unk84 = lbl_1_data_268[1];
			} else {
				temp_r31 = lbl_1_bss_61C[temp_r30->unk0[1]]->data;
				temp_r31->unk84 = lbl_1_data_268[0];
				temp_r31->unk14->unk84 = lbl_1_data_268[1];
			}
		} else {
			if(spC[0] == 0) {
				if(sp10[0] < sp10[1]) {
					temp_r31 = lbl_1_bss_61C[temp_r30->unk0[0]]->data;
					temp_r31->unk84 = lbl_1_data_268[1];
					temp_r31->unk14->unk84 = lbl_1_data_268[0];
				} else {
					temp_r31 = lbl_1_bss_61C[temp_r30->unk0[1]]->data;
					temp_r31->unk84 = lbl_1_data_268[1];
					temp_r31->unk14->unk84 = lbl_1_data_268[0];
				}
			} else {
				if(sp10[0] > sp10[1]) {
					temp_r31 = lbl_1_bss_61C[temp_r30->unk0[0]]->data;
					temp_r31->unk84 = lbl_1_data_268[0];
					temp_r31->unk14->unk84 = lbl_1_data_268[1];
				} else {
					temp_r31 = lbl_1_bss_61C[temp_r30->unk0[1]]->data;
					temp_r31->unk84 = lbl_1_data_268[0];
					temp_r31->unk14->unk84 = lbl_1_data_268[1];
				}
			}
		}
		lbl_1_bss_98++;
	}
	for(temp_r29=0; temp_r29<2; temp_r29++) {
		temp_r31 = lbl_1_bss_61C[temp_r30->unk0[temp_r29]]->data;
		temp_r31->unkC = 0;
		temp_r31->unk86 = 1;
		temp_r31->unkB4 = 0;
		temp_r31->unkB5 = 0;
		sp14[temp_r29] = fn_1_8AD4(temp_r31, temp_r31->unk40, temp_r31->unk84, &spA, 0);
		if(sp14[temp_r29] != 0) {
			temp_r31->unkB4 = (spA == 0) ? 50 : -50;
		} else {
			temp_r31->unk86 = 0;
		}
		fn_1_8CC0(lbl_1_bss_61C[temp_r30->unk0[temp_r29]]);
		sp14[temp_r29] = (temp_r31->unk0 & 0xC0) ? 1 : 0;
		if(temp_r31->unk0 & 0x600) {
			sp14[temp_r29] = 1;
		}
	}
	if(sp14[0] == 0 && sp14[1] == 0) {
		return 1;
	}
	return 0;
}

s32 fn_1_8474(s16 arg0)
{
	s32 spC[2];
	s32 temp_r31;
	Bss61CWork *temp_r30;
	Bss12CStruct *temp_r29;
	temp_r29 = &lbl_1_bss_12C[arg0];
	for(temp_r31=0; temp_r31<2; temp_r31++) {
		temp_r30 = lbl_1_bss_61C[temp_r29->unk0[temp_r31]]->data;
		fn_1_8CC0(lbl_1_bss_61C[temp_r29->unk0[temp_r31]]);
		if((temp_r30->unk0 & 0xC0) || (temp_r30->unk0 & 0x600) || (temp_r30->unk0 & 0x20)) {
			spC[temp_r31] = 1;
		} else {
			spC[temp_r31] = 0;
		}
	}
	if(spC[0] == 0 && spC[1] == 0) {
		return 1;
	}
	return 0;
}

void fn_1_8790(omObjData *object);
Bss61CWork *fn_1_AAF0(omObjData *object);
u32 fn_1_ABA0(omObjData *object, u32 arg1);

void fn_1_858C(omObjData *object)
{
	Bss61CWork *temp_r31;
	u16 temp_r29;
	if(lbl_1_data_260[object->work[0]] == 0) {
		return;
	}
	temp_r31 = lbl_1_bss_61C[object->work[0]]->data;
	temp_r31->unkB0 = HuPadBtn[temp_r31->unk6];
	temp_r31->unkB2 = HuPadBtnDown[temp_r31->unk6];
	temp_r31->unkB4 = HuPadStkX[temp_r31->unk6];
	temp_r31->unkB5 = HuPadStkY[temp_r31->unk6];
	if(fn_1_2090(1) != 0) {
		return;
	}
	temp_r29 = fn_1_2090(28);
	if(temp_r29 == 12 || temp_r29 == 16) {
		if(fn_1_ABA0(lbl_1_bss_61C[object->work[0]], 0x600) == 0 && lbl_1_data_260[object->work[0]] != 0) {
			temp_r31 = lbl_1_bss_61C[object->work[0]]->data;
			if(temp_r31->unk14 == 0) {
				temp_r31->unk14 = fn_1_AAF0(lbl_1_bss_61C[object->work[0]]);
			}
			if(GWPlayerCfg[temp_r31->unk4].iscom) {
				fn_1_8790(lbl_1_bss_61C[object->work[0]]);
			}
			fn_1_8CC0(lbl_1_bss_61C[object->work[0]]);
		}
		
	}
}

void fn_1_8790(omObjData *object)
{
	Bss61CWork *temp_r31;
	s16 temp_r30;
	s16 temp_r29;
	s16 temp_r28;
	u32 temp_r26;
	s16 sp18[9];
	s16 sp8[8];
	temp_r31 = object->data;
	temp_r31->unkB4 = temp_r31->unkB5 = 0;
	temp_r31->unkB2 = 0;
	if(fn_1_2090(224)) {
		return;
	}
	sp18[8] = 999;
	for(temp_r30=0, temp_r28=0, temp_r29=8; temp_r30<temp_r31->unk6E; temp_r30++) {
		temp_r26 = fn_1_4738(temp_r31->unkA, temp_r31->unk5E[temp_r30]);
		if(temp_r26 & 0x1) {
			temp_r31->unk5E[temp_r30] = -1;
		}
		sp18[temp_r30] = fn_1_8AD4(temp_r31, temp_r31->unk40, temp_r31->unk5E[temp_r30], &sp8[temp_r30], 1);
		if(sp18[temp_r30] < sp18[temp_r29]) {
			temp_r29 = temp_r30;
		}
		if(temp_r31->unk5E[temp_r30] == -1) {
			temp_r28++;
		}
	}
	if(temp_r28 == temp_r31->unk6E) {
		return;
	}
	if(temp_r31->unk70 < temp_r31->unk72 && temp_r29 < 4) {
		for(temp_r30=4; temp_r30<temp_r31->unk6E; temp_r30++) {
			if(sp18[temp_r30] < 10) {
				temp_r29 = temp_r30;
				break;
			}
		}
	}
	if(temp_r31->unk7C == 0) {
		if(GWPlayerCfg[temp_r31->unk14->unk4].iscom) {
			if(temp_r31->unk4 > temp_r31->unk14->unk4 && (temp_r31->unk0 & 0x20)) {
				temp_r31->unk7C = 1;
			}
		} else {
			if(temp_r31->unk0 & 0x20) {
				temp_r31->unk7C = 1;
			}
		}
	}
	if(temp_r31->unk7C && temp_r28 == temp_r31->unk6E-1) {
		if(++temp_r31->unk7C > 120) {
			temp_r31->unk7C = 0;
		}
		if((temp_r31->unk14->unk0 & 0xC0) == 0x40) {
			sp8[temp_r29] = 0;
		} else {
			if((temp_r31->unk14->unk0 & 0xC0) == 0x80) {
				sp8[temp_r29] = 1;
			} else {
				temp_r31->unk7C = 0;
			}
		}
	}
	if(sp18[temp_r29] != -1) {
		temp_r31->unkB4 = (sp8[temp_r29] == 0) ? 50 : -50;
	} else {
		if(temp_r31->unk44.z <= 15.0f) {
			temp_r31->unkB2 = PAD_BUTTON_A;
		}
	}
}

s16 fn_1_8AD4(Bss61CWork *arg0, s16 arg1, s16 arg2, s16 *arg3, u8 arg4)
{
	s16 temp_r31;
	s16 temp_r29;
	s16 temp_r28;
	s16 temp_r27;
	s16 temp_r26;
	s16 temp_r25;
	
	if(arg2 == -1) {
		*arg3 = rand16()%2;
		temp_r29 = 99;
	} else if(arg1 == arg2) {
		*arg3 = -1;
		temp_r29 = (arg4) ? -1 : 0;
	} else {
		temp_r28 = temp_r27 = temp_r26 = temp_r25 = 0;
		temp_r31 = arg1;
		do {
			temp_r31++;
			temp_r28++;
			if(temp_r31 >= 10) {
				temp_r31 = 0;
			}
			if(arg4 && temp_r31 == arg0->unk14->unk40) {
				temp_r26 = 99;
				break;
			}
		} while(temp_r31 != arg2);
		temp_r31 = arg1;
		do {
			temp_r31--;
			temp_r27++;
			if(temp_r31 < 0) {
				temp_r31 = 9;
			}
			if(arg4 && temp_r31 == arg0->unk14->unk40) {
				temp_r25 = 99;
				break;
			}
		} while(temp_r31 != arg2);
		if(temp_r26 != temp_r25)  {
			temp_r28 += temp_r26;
			temp_r27 += temp_r25;
			if(temp_r28 < temp_r27) {
				*arg3 = 0;
				temp_r29 = temp_r28;
			} else {
				*arg3 = 1;
				temp_r29 = temp_r27;
			}
		} else {
			if(temp_r28 < temp_r27) {
				*arg3 = 0;
				temp_r29 = temp_r28;
			} else {
				*arg3 = 1;
				temp_r29 = temp_r27;
			}
			temp_r29 += 10;
		}
	}
	return temp_r29;
}

s16 fn_1_938C(omObjData *object);
void fn_1_ABC0(omObjData *object, u32 arg1, u32 arg2);

void fn_1_8CC0(omObjData *object)
{
	float temp_f31;
	float temp_f30;
	float temp_f28;
	
	Bss61CWork *temp_r31;
	s16 temp_r30;
	s16 temp_r29;
	s16 temp_r28;
	s16 temp_r27;
	s16 temp_r26;
	
	
	Vec sp10;
	u16 sp8;
	Bss12CInner *temp_r25;
	temp_r31 = object->data;
	if(temp_r31->unk38 == 3 || temp_r31->unk38 == 5) {
		return;
	}
	sp8 = fn_1_2090(28);
	if((temp_r31->unk0 & 0x20) || (fn_1_2090(28) != 12 && temp_r31->unk86 == 0)) {
		temp_r28 = temp_r26 = 0;
	} else {
		temp_r28 = temp_r31->unkB4;
		temp_r26 = temp_r31->unkB5;
	}
	temp_r30 = temp_r29 = 0;
	if(temp_r31->unk52 == 0) {
		switch(temp_r31->unkC) {
			case 0:
				if(temp_r28 > 10) {
					temp_r30 = 1;
				} else if(temp_r28 < -10) {
					temp_r29 = 1;
				}
				break;
				
			case 1:
				if(ABS(temp_r28) >= 10 || ABS(temp_r26) >= 10) {
					temp_r25 = &lbl_1_bss_12C[temp_r31->unkA].unk1C[temp_r31->unk40];
					sp10.x = temp_r28+lbl_1_bss_12C[temp_r31->unkA].unkE4[temp_r31->unk40][0];
					sp10.z = lbl_1_bss_12C[temp_r31->unkA].unkE4[temp_r31->unk40][1]-temp_r26;
					temp_f28 = (temp_r25->unk0.x*sp10.x)+(temp_r25->unk0.z*sp10.z)-temp_r25->unkC;
					if(temp_f28 > 0.0f) {
						if(temp_r31->unk50 != temp_r31->unk40) {
							if(temp_r31->unk54 == 128) {
								temp_r31->unk52 = 1;
							}
						} else {
							temp_r30 = 1;
						}
					} else {
						if(temp_f28 < 0.0f) {
							if(temp_r31->unk50 != temp_r31->unk40) {
								if(temp_r31->unk54 == 64) {
									temp_r31->unk52 = 1;
								}
								
							} else {
								temp_r29 = 1;
							}
						}
					}
				}
				break;
		}
	} else {
		if(temp_r31->unk58 != temp_r28 || temp_r31->unk5A != temp_r26) {
			temp_r31->unk52 = 0;
		}
	}
	temp_f31 = temp_r31->unk24.x-temp_r31->unk14->unk24.x;
	temp_f30 = temp_r31->unk24.z-temp_r31->unk14->unk24.z;
	temp_f28 = VECMagPoint(temp_f31, 0, temp_f30);
	if(temp_f28 < 90 && (temp_r31->unk0 & 0x20) == 0) {
		if(fn_1_938C(object) == 0) {
			temp_r30 = 0;
			temp_r29 = 1;
		} else {
			temp_r30 = 1;
			temp_r29 = 0;
		}
		temp_r31->unk0 |= 0x20;
	} else {
		if(temp_r31->unk54 == 64) {
			temp_r27 = temp_r31->unk42-temp_r31->unk40;
			if(temp_r27 < 0) {
				temp_r27 += 10;
			}
			if(temp_r27 > 1) {
				temp_r31->unk42 = 1;
			}
		} else {
			temp_r27 = temp_r31->unk40-temp_r31->unk42;
			if(temp_r27 < 0) {
				temp_r27 += 10;
			}
			if(temp_r27 > 1) {
				temp_r31->unk42 = 9;
			}
		}
	}
	if(temp_r30) {
		temp_r30 = 0;
		if(temp_r31->unk54 == 64) {
			if(temp_r31->unk44.z <= 2.0f) {
				temp_r30 = 1;
			}
		} else if(temp_r31->unk54 == 128) {
			if(temp_r31->unk40 != temp_r31->unk42) {
				temp_r31->unk40 = temp_r31->unk42;
			}
			temp_r30 = 1;
		} else {
			temp_r30 = 1;
		}
		if(temp_r30) {
			fn_1_ABC0(object, 192, 64);
			temp_r31->unk42 = temp_r31->unk40+1;
			if(temp_r31->unk42 >= 10) {
				temp_r31->unk42 = 0;
			}
		}
	} else if(temp_r29) {
		temp_r29 = 0;
		if(temp_r31->unk54 == 128) {
			if(temp_r31->unk44.z <= 2.0f) {
				temp_r29 = 1;
			}
		} else if(temp_r31->unk54 == 64) {
			if(temp_r31->unk40 != temp_r31->unk42) {
				temp_r31->unk40 = temp_r31->unk42;
			}
			temp_r29 = 1;
		} else {
			temp_r29 = 1;
		}
		if(temp_r29) {
			fn_1_ABC0(object, 192, 128);
			temp_r31->unk42 = temp_r31->unk40-1;
			if(temp_r31->unk42 < 0) {
				temp_r31->unk42 = 9;
			}
		}
	}
	temp_r31->unk50 = temp_r31->unk40;
	temp_r31->unk54 = fn_1_ABA0(object, 192);
	temp_r31->unk58 = temp_r28;
	temp_r31->unk5A = temp_r26;
}

s16 fn_1_938C(omObjData *object)
{
	Bss61CWork *temp_r31;
	float temp_f31;
	temp_r31 = object->data;
	temp_f31 = temp_r31->unk44.y-temp_r31->unk14->unk44.y;
	if(temp_f31 > 180.0f) {
		temp_f31 -= 360.0f;
	} else if(temp_f31 < -180.0f) {
		temp_f31 = 360.0f+temp_f31;
	}
	return (temp_f31 <= 0.0f) ? 0 : 1;
}

void fn_1_98D4(omObjData *object);

void fn_1_B0E8(omObjData *object, s16 arg1, u32 arg2);

void fn_1_9440(omObjData *object)
{
	Bss61CWork *temp_r31;
	Bss12CStruct *temp_r29;
	s16 temp_r28;
	object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Bss61CWork), MEMORY_DEFAULT_NUM);
	temp_r31 = object->data;
	memset(temp_r31, 0, sizeof(Bss61CWork));
	object->stat |= 0x100;
	temp_r31->unk4 = object->work[0];
	temp_r31->unk6 = GWPlayerCfg[temp_r31->unk4].pad_idx;
	temp_r31->unk8 = GWPlayerCfg[temp_r31->unk4].character;
	temp_r31->unkA = GWPlayerCfg[temp_r31->unk4].group;
	temp_r31->unkC = (GWPlayerCfg[temp_r31->unk4].iscom) ? 0 : 1;
	temp_r31->unkAC = 0;
	object->model[0] = CharModelCreate(temp_r31->unk8, 2);
	Hu3DModelLayerSet(object->model[0], 0);
	Hu3DModelShadowSet(object->model[0]);
	CharModelStepTypeSet(temp_r31->unk8, 0);
	for(temp_r28=0; temp_r28<8; temp_r28++) {
		if(lbl_1_data_1F4[temp_r28] != -1) {
			object->motion[temp_r28] = CharModelMotionCreate(temp_r31->unk8, lbl_1_data_1F4[temp_r28]);
		} else {
			object->motion[temp_r28] = Hu3DJointMotionFile(object->model[0], DATA_MAKE_NUM(DATADIR_M431, 0x21)+temp_r31->unk8);
		}
		if(temp_r28 == 4 || temp_r28 == 5) {
			CharModelVoiceEnableSet(temp_r31->unk8, object->motion[temp_r28], 0);
		}
	}
	CharModelMotionDataClose(temp_r31->unk8);
	temp_r29 = &lbl_1_bss_12C[temp_r31->unkA];
	for(temp_r28=0; temp_r28<8; temp_r28++) {
		temp_r31->unk5E[temp_r28] = -1;
	}
	if(temp_r31->unkA == 0) {
		if(temp_r29->unk0[0] == object->work[0]) {
			temp_r31->unk44.y = lbl_1_bss_62C[9].unk4;
		} else {
			temp_r31->unk44.y = lbl_1_bss_62C[4].unk4;
		}
	} else {
		if(temp_r29->unk0[0] == object->work[0]) {
			temp_r31->unk44.y = lbl_1_bss_62C[5].unk4;
		} else {
			temp_r31->unk44.y = lbl_1_bss_62C[0].unk4;
		}
	}
	temp_r31->unk40 = (temp_r31->unk44.y/360.0f)*10.0f;
	temp_r31->unk42 = temp_r31->unk40;
	temp_r31->unk10 = lbl_1_data_1D4[temp_r31->unk8];
	temp_r31->unk24.x = ((temp_r29->unk18+temp_r31->unk10)*sind(temp_r31->unk44.y))+temp_r29->unkC.x;
	temp_r31->unk24.y = temp_r29->unkC.y;
	temp_r31->unk24.z = ((temp_r29->unk18+temp_r31->unk10)*cosd(temp_r31->unk44.y))+temp_r29->unkC.z;
	temp_r31->unk30 = atan2d(temp_r29->unkC.x-temp_r31->unk24.x, temp_r29->unkC.z-temp_r31->unk24.z);
	Hu3DModelPosSet(object->model[0], temp_r31->unk24.x, temp_r31->unk24.y, temp_r31->unk24.z);
	Hu3DModelRotSet(object->model[0], 0, temp_r31->unk30, 0);
	temp_r31->unk38 = temp_r31->unk3A = -1;
	fn_1_B0E8(object, 0, 10);
	lbl_1_data_260[object->work[0]] = 1;
	object->func = fn_1_98D4;
}

void fn_1_9A04(omObjData *object);
void fn_1_9C5C(omObjData *object);
void fn_1_A0F8(omObjData *object);
void fn_1_A450(omObjData *object);

void fn_1_AA40(omObjData *object);

void fn_1_B130(omObjData *object, s16 arg1, u32 arg2);
void fn_1_B150(omObjData *object, omObjFunc arg1);

void fn_1_B18C(omObjData *object);

s32 fn_1_B494(s32 arg0, s32 arg1);

void fn_1_98D4(omObjData *object)
{
	Vec sp8;
	
	Bss61CWork *temp_r31;
	ModelData *temp_r29;
	temp_r31 = object->data;
	temp_r29 = &Hu3DData[object->model[0]];
	sp8.x = temp_r31->unk24.x-temp_r29->pos.x;
	sp8.z = temp_r31->unk24.z-temp_r29->pos.z;
	if((temp_r31->unk0 & 0x600) == 0 || 0.0f != sp8.x || 0.0f != sp8.z || (temp_r31->unk0 & 0x20)) {
		fn_1_9A04(object);
		fn_1_9C5C(object);
		fn_1_A0F8(object);
	} else {
		fn_1_A450(object);
	}
	fn_1_B18C(object);
	Hu3DModelPosSet(object->model[0], temp_r31->unk24.x, temp_r31->unk24.y, temp_r31->unk24.z);
	Hu3DModelRotSet(object->model[0], 0, temp_r31->unk30, 0);
	
}

void fn_1_9A04(omObjData *object)
{
	Bss61CWork *temp_r31;
	ModelData *temp_r29;
	
	temp_r29 = &Hu3DData[object->model[0]];
	temp_r31 = object->data;
	if(fn_1_2090(28) != 12 || fn_1_2090(224) != 0) {
		return;
	}
	if(fn_1_4724() == 2) {
		return;
	}
	if(fn_1_ABA0(object, 192) != 0) {
		return;
	}
	if(temp_r31->unk38 == 0) {
		if(temp_r29->unk_0C == -1 && temp_r31->unkB2 == PAD_BUTTON_A) {
			if(fn_1_4CDC(temp_r31->unkA, temp_r31->unk40)) {
				fn_1_B0E8(object, 3, 4);
				fn_1_B130(object, 0, 8);
			}
		}
	} else {
		if(temp_r31->unk38 == 3) {
			if(temp_r29->unk_0C == -1 && temp_r29->unk_64 == 14.0f) {
				temp_r31->unk5C = fn_1_4B14(temp_r31->unkA, temp_r31->unk40, &temp_r31->unk7E);
				if(temp_r31->unk5C != -1) {
					if(temp_r31->unkA == 0) {
						HuAudFXPlay(1668);
					} else {
						HuAudFXPlay(1673);
					}
					if(temp_r31->unk7E != 0) {
						omVibrate(temp_r31->unk4, 12, 6, 6);
						if(temp_r31->unkA == 0) {
							fn_1_B494(1666, 30);
						} else {
							fn_1_B494(1671, 30);
						}
					} else {
						if(temp_r31->unkA == 0) {
							fn_1_B494(1667, 30);
						} else {
							fn_1_B494(1672, 30);
						}
					}
					temp_r31->unk70++;
					Hu3DModelPosSet(temp_r31->unk5C, 0, 0, 0);
					Hu3DModelHookSet(object->model[0], lbl_1_data_230[temp_r31->unk8], temp_r31->unk5C);
					fn_1_B150(object, fn_1_AA40);
				}
			}
		}
	}
}

void fn_1_9C5C(omObjData *object)
{
	float temp_f31;
	Bss61CWork *temp_r31;
	Bss12CStruct *temp_r30;
	s8 temp_r29;
	u32 temp_r27;
	temp_r31 = object->data;
	temp_r30 = &lbl_1_bss_12C[temp_r31->unkA];
	temp_r29 = 0;
	if((temp_r27 = fn_1_ABA0(object, 192)) == 0) {
		return;
	}
	if(temp_r27 == 192) {
		temp_r29 = 1;
	} else if(temp_r27 == 64) {
		temp_r31->unk44.x += 0.3f;
		if(temp_r31->unk44.x > 1.5f) {
			temp_r31->unk44.x = 1.5f;
		}
		temp_r31->unk44.y += temp_r31->unk44.x;
		temp_f31 = lbl_1_bss_62C[temp_r31->unk42].unk4;
		if(temp_r31->unk40 == 9 && temp_r31->unk42 == 0) {
			temp_f31 += 360.0f;
		} else {
			if(temp_r31->unk44.y >= 360.0f) {
				temp_r31->unk44.y -= 360.0f;
			}
		}
		temp_r31->unk44.z = ABS(temp_r31->unk44.y-temp_f31);
		if(temp_r31->unk44.y >= temp_f31) {
			temp_r29 = 1;
		}
	} else {
		temp_r31->unk44.x -= 0.3f;
		if(temp_r31->unk44.x < -1.5f) {
			temp_r31->unk44.x = -1.5f;
		}
		temp_r31->unk44.y += temp_r31->unk44.x;
		temp_f31 = lbl_1_bss_62C[temp_r31->unk42].unk4;
		if(temp_r31->unk42 == 9 && temp_r31->unk40 == 0) {
			if(temp_r31->unk44.y < 0.0f) {
				temp_r31->unk44.y += 360.0f;
			} else {
				temp_f31 -= 360.0f;
			}
		} else {
			if(temp_r31->unk42 == 0 || temp_r31->unk40 == 0) {
				if(temp_r31->unk44.y < 0.0f) {
					temp_r31->unk44.y += 360.0f;
					temp_f31 += 360.0f;
				}
			} else {
				if(temp_r31->unk44.y < 0.0f) {
					temp_r31->unk44.y += 360.0f;
				}
			}
		}
		temp_r31->unk44.z = ABS(temp_r31->unk44.y-temp_f31);
		if(temp_r31->unk44.y <= temp_f31) {
			temp_r29 = 1;
		}
	}
	if(temp_r29 != 0) {
		temp_r31->unk44.x = 0;
		temp_r31->unk44.y = lbl_1_bss_62C[temp_r31->unk42].unk4;
		temp_r31->unk0 &= ~0xE0;
	}
	temp_r31->unk40 = (temp_r31->unk44.y/360.0f)*10.0f;
	if(temp_r31->unk40 >= 10) {
		temp_r31->unk40 -= 10;
	}
	temp_r31->unk24.x = ((temp_r30->unk18+temp_r31->unk10)*sind(temp_r31->unk44.y))+temp_r30->unkC.x;
	temp_r31->unk24.y = temp_r30->unkC.y;
	temp_r31->unk24.z = ((temp_r30->unk18+temp_r31->unk10)*cosd(temp_r31->unk44.y))+temp_r30->unkC.z;
	fn_1_B0E8(object, 2, 8);
}

void fn_1_A0F8(omObjData *object)
{
	Vec sp8;
	Bss61CWork *temp_r31;
	ModelData *temp_r29;
	Bss12CStruct *temp_r28;
	s32 temp_r27;
	temp_r29 = &Hu3DData[object->model[0]];
	temp_r31 = object->data;
	temp_r28 = &lbl_1_bss_12C[temp_r31->unkA];
	temp_r27 = 0;
	if(temp_r31->unk38 == 3 || temp_r31->unk38 == 5) {
		return;
	}
	sp8.x = temp_r31->unk24.x-temp_r29->pos.x;
	sp8.z = temp_r31->unk24.z-temp_r29->pos.z;
	if(0.0f == sp8.x && 0.0f == sp8.z) {
		if(fn_1_2090(224) == 0 && temp_r31->unk38 == 2 && (temp_r31->unkB0 & PAD_BUTTON_A)) {
			temp_r31->unk7A = 1;
		}
		if(temp_r31->unk78 == 0) {
			sp8.x = temp_r28->unkC.x-temp_r31->unk24.x;
			sp8.z = temp_r28->unkC.z-temp_r31->unk24.z;
			temp_r31->unk8C.x = temp_r31->unk30;
			temp_r31->unk8C.y = atan2d(sp8.x, sp8.z);
			temp_r31->unk8C.z = 0;
			if(temp_r31->unk8C.y < 0.0f) {
				temp_r31->unk8C.y += 360.0f;
			}
			temp_r31->unk78 = 1;
		}
		temp_r31->unk8C.z += 0.1f;
		if(temp_r31->unk8C.z >= 1.0f) {
			temp_r31->unk8C.z = 1.0f;
			if(temp_r31->unk7A == 0) {
				fn_1_B0E8(object, 0, 8);
			} else {
				if(fn_1_4CDC(temp_r31->unkA, temp_r31->unk40) && fn_1_2090(28) == 12 && fn_1_2090(224) == 0 && fn_1_4724() < 2) {
					fn_1_B0E8(object, 3, 4);
					fn_1_B130(object, 0, 8);
					temp_r27 = 1;
				}
				if(temp_r27 == 0) {
					fn_1_B0E8(object, 0, 8);
				}
			}
			temp_r31->unk7A = 0;
		}
		temp_r31->unk30 = fn_1_6504(temp_r31->unk8C.x, temp_r31->unk8C.y, temp_r31->unk8C.z);
	} else {
		temp_r31->unk78 = temp_r31->unk7A = 0;
		temp_r31->unk30 = atan2d(sp8.x, sp8.z);
		if(temp_r31->unk30 < 0.0f) {
			temp_r31->unk30 += 360.0f;
		}
		
	}
	lbl_1_bss_9C[object->work[0]] = temp_r31->unk0 & 0xC0;
}

void fn_1_A450(omObjData *object)
{
	float temp_f31;
	Bss61CWork *temp_r31;
	s32 temp_r29;
	ModelData *temp_r28;
	temp_r28 = &Hu3DData[object->model[0]];
	temp_r31 = object->data;
	if(temp_r31->unk38 == 3) {
		return;
	}
	temp_r31->unk7A = 0;
	switch(temp_r31->unk80) {
		case 0:
			temp_r31->unk9C.y += 0.05f;
			if(temp_r31->unk9C.y > 1.0f) {
				temp_r31->unk9C.y = 1.0f;
				temp_r31->unk80++;
			}
			temp_r29 = fn_1_2090(28);
			if(temp_r29 >= 16 && lbl_1_bss_4) {
				temp_f31 = CRot.y;
			} else {
				temp_f31 = 0.0f;
			}
			if(temp_f31 < 0.0f) {
				temp_f31 += 360.0f;
			} else if(temp_f31 >= 360.0f) {
				temp_f31 -= 360.0f;
			}
			temp_r31->unk30 = fn_1_6504(temp_r31->unk9C.x, temp_f31, temp_r31->unk9C.y);
			fn_1_B0E8(object, 2, 8);
			break;
			
		case 1:
			temp_r31->unk3A = -1;
			temp_r29 = fn_1_2090(28);
			if(temp_r29 >= 16 && lbl_1_bss_4) {
				if(temp_r31->unkAC == 0) {
					fn_1_B0E8(object, 6, 4);
				} else {
					fn_1_B0E8(object, 7, 4);
				}
				temp_r31->unk80 = 99;
			} else {
				fn_1_B0E8(object, 4, 4);
				HuAudCharVoicePlay(temp_r31->unk8, 290);
				temp_r31->unk80++;
			}
			break;
			
		case 2:
			if(temp_r28->unk_0C == -1) {
				if(Hu3DMotionTimeGet(object->model[0]) >= Hu3DMotionMaxTimeGet(object->model[0])-1.0f){ 
					fn_1_B0E8(object, 1, 8);
					temp_r31->unk9C.y = 0;
					temp_r31->unk80++;
				}
			}
			break;
			
		case 3:
			temp_r31->unk9C.y += 0.05f;
			if(temp_r31->unk9C.y > 1.0f) {
				if(fn_1_2090(1)) {
					fn_1_2050(2, 2);
				}
				fn_1_B0E8(object, 0, 8);
				fn_1_ABC0(object, 0x600, 0);
				temp_r31->unk9C.y = 1.0f;
				temp_r31->unk80++;
			}
			if(!temp_r31->unkAC) {
				temp_r31->unk30 = fn_1_6504(0, temp_r31->unk9C.x, temp_r31->unk9C.y);
			}
			break;
	}
}

void fn_1_A7D0(s16 arg0)
{
	Bss61CWork *temp_r31;
	Bss12CStruct *temp_r30;
	s16 temp_r29;
	s16 temp_r28;
	temp_r30 = &lbl_1_bss_12C[arg0];
	if(arg0 == -1) {
		return;
	}
	for(temp_r29=0; temp_r29<1; temp_r29++) {
		if(temp_r29 == 0) {
			temp_r30 = &lbl_1_bss_12C[arg0];
		} else {
			temp_r30 = &lbl_1_bss_12C[arg0^1];
		}
		for(temp_r28=0; temp_r28<temp_r30->unk8; temp_r28++) {
			temp_r31 = lbl_1_bss_61C[temp_r30->unk0[temp_r28]]->data;
			temp_r31->unk80 = 0;
			temp_r31->unk9C.x = temp_r31->unk30;
			temp_r31->unk9C.y = 0;
			temp_r31->unk0 &= ~0x600;
			
			if(temp_r29 == 0) {
				temp_r31->unk0 |= 0x200;
			} else {
				temp_r31->unk0 |= 0x400;
			}
		}
	}
}

void fn_1_A904(s16 arg0)
{
	Bss61CWork *temp_r31;
	Bss12CStruct *temp_r30;
	s16 temp_r29;
	s16 temp_r28;
	temp_r30 = &lbl_1_bss_12C[arg0];
	if(arg0 == -1) {
		return;
	}
	for(temp_r29=0; temp_r29<1; temp_r29++) {
		if(temp_r29 == 0) {
			temp_r30 = &lbl_1_bss_12C[arg0];
		} else {
			temp_r30 = &lbl_1_bss_12C[arg0^1];
		}
		for(temp_r28=0; temp_r28<temp_r30->unk8; temp_r28++) {
			temp_r31 = lbl_1_bss_61C[temp_r30->unk0[temp_r28]]->data;
			temp_r31->unk80 = 1;
			temp_r31->unk9C.x = temp_r31->unk30;
			temp_r31->unk9C.y = 0;
			temp_r31->unk0 &= ~0x600;
			
			if(temp_r29 == 0) {
				temp_r31->unk0 |= 0x200;
			} else {
				temp_r31->unk0 |= 0x400;
			}
			temp_r31->unkAC = 1;
		}
	}
}

void fn_1_AC80(omObjData *object, Vec *arg1);
void fn_1_B16C(omObjData *object);

void fn_1_AA40(omObjData *object)
{
	Vec sp8;
	Bss61CWork *temp_r30;
	temp_r30 = object->data;
	fn_1_AC80(object, &sp8);
	fn_1_5B70(sp8.x, sp8.y, sp8.z, 20, NULL, -1);
	Hu3DModelAttrSet(temp_r30->unk5C, 1);
	Hu3DModelHookReset(object->model[0]);
	temp_r30->unk5C = -1;
	if(temp_r30->unk7E == 0) {
		fn_1_B0E8(object, 5, 4);
		fn_1_B130(object, 0, 8);
	}
	fn_1_B16C(object);
}

Bss61CWork *fn_1_AAF0(omObjData *object)
{
	Bss12CStruct *temp_r31;
	s16 temp_r30;
	Bss61CWork *temp_r29 = object->data;
	s32 sp8 = 0;
	
	temp_r31= &lbl_1_bss_12C[temp_r29->unkA];
	for(temp_r30=0; temp_r30<temp_r31->unk8; temp_r30++) {
		if(object->work[temp_r30] != temp_r31->unk0[temp_r30]) {
			return lbl_1_bss_61C[temp_r31->unk0[temp_r30]]->data;
		}
	}
	return NULL;
}

u32 fn_1_ABA0(omObjData *object, u32 arg1)
{
	Bss61CWork *temp_r31 = object->data;
	return temp_r31->unk0 & arg1;
}

void fn_1_ABC0(omObjData *object, u32 arg1, u32 arg2)
{
	Bss61CWork *temp_r31 = object->data;
	temp_r31->unk0 &= ~arg1;
	temp_r31->unk0 |= arg2;
}

void fn_1_ABF0(s16 arg0, u32 arg1, u32 arg2)
{
	Bss12CStruct *temp_r31;
	Bss61CWork *temp_r30;
	s16 temp_r29;
	temp_r31= &lbl_1_bss_12C[arg0];
	for(temp_r29=0; temp_r29<temp_r31->unk8; temp_r29++) {
		temp_r30 = lbl_1_bss_61C[temp_r31->unk0[temp_r29]]->data;
		temp_r30->unk0 &= ~arg1;
		temp_r30->unk0 |= arg2;
	}
}

void fn_1_AC80(omObjData *object, Vec *arg1)
{
	Bss61CWork *temp_r31;
	float temp_f31;
	temp_r31 = object->data;
	temp_f31 = lbl_1_bss_62C[temp_r31->unk40].unk4;
	arg1->x = temp_r31->unk24.x-(50.0*sind(temp_f31));
	arg1->y = temp_r31->unk24.y+100;
	arg1->z = temp_r31->unk24.z-(50.0*cosd(temp_f31));
}

float fn_1_AD88(s8 arg0)
{
	float temp_f31;
	if(arg0 > 65) {
		arg0 = 65;
	} else if(arg0 < -65) {
		arg0 = -65;
	}
	temp_f31 = arg0;
	temp_f31 /= 65.0f;
	return temp_f31;
}

float fn_1_AE04(s8 arg0, s8 arg1)
{
	float temp_f30;
	temp_f30 = 0.01539*VECMagPoint(arg0, arg1, 0);
	if(temp_f30 > 1.0f) {
		temp_f30 = 1.0f;
	}
	return temp_f30;
}

void fn_1_B0E8(omObjData *object, s16 arg1, u32 arg2)
{
	Bss61CWork *temp_r31 = object->data;
	if(temp_r31->unk38 != arg1) {
		temp_r31->unk0 &= ~0xF;
		temp_r31->unk38 = arg1;
		temp_r31->unk0 |= arg2;
	}
}

void fn_1_B130(omObjData *object, s16 arg1, u32 arg2)
{
	Bss61CWork *temp_r31 = object->data;
	temp_r31->unk3A = arg1;
	temp_r31->unk3C = arg2;
}

void fn_1_B150(omObjData *object, omObjFunc arg1)
{
	Bss61CWork *temp_r31 = object->data;
	temp_r31->unk34 = arg1;
}

void fn_1_B16C(omObjData *object)
{
	fn_1_B150(object, NULL);
}

void fn_1_B18C(omObjData *object)
{
	Bss61CWork *temp_r31;
	u32 temp_r28;
	ModelData *temp_r27;
	omObjFunc temp_r25;
	temp_r27 = &Hu3DData[object->model[0]];
	temp_r31 = object->data;
	if(temp_r31->unk0 & 0x1) {
		if(temp_r31->unk3A != -1 && temp_r27->unk_0C == -1) {
			if(Hu3DMotionTimeGet(object->model[0]) >= Hu3DMotionMaxTimeGet(object->model[0])) {
				fn_1_B0E8(object, temp_r31->unk3A, temp_r31->unk3C);
				temp_r31->unk3A = -1;
				if(temp_r31->unk34) {
					temp_r25 = temp_r31->unk34;
					temp_r25(object);
				}
			}
		} else {
			return;
		}
	} else {
		Hu3DModelAttrReset(object->model[0], 0x40000007);
		switch(temp_r31->unk0 & 0xC) {
			case 0:
				temp_r28 = 0x40000002;
				break;
				
			case 4:
				temp_r28 = 0;
				break;
				
			case 8:
				temp_r28 = 0x40000001;
				break;
		}
		if(temp_r31->unk0 & 0x2) {
			Hu3DMotionSet(object->model[0], object->motion[temp_r31->unk38]);
			Hu3DModelAttrSet(object->model[0], temp_r28);
		} else {
			Hu3DMotionShiftSet(object->model[0], object->motion[temp_r31->unk38], 0, 8, temp_r28);
		}
		temp_r31->unk0 |= 0x1;
	}
}

void fn_1_B404(omObjData *object);

void fn_1_B384(Process *objman)
{
	s32 *temp_r31;
	s32 temp_r30;
	omAddObjEx(objman, 100, 0, 0, -1, fn_1_B404);
	temp_r31 = &lbl_1_bss_AC[0][0];
	for(temp_r30=0; temp_r30<16; temp_r30++, temp_r31 += 2) {
		temp_r31[0] = -1;
		temp_r31[1] = -1;
	}
}

void fn_1_B404(omObjData *object)
{
	s32 *temp_r31;
	s32 temp_r30;
	temp_r31 = &lbl_1_bss_AC[0][0];
	for(temp_r30=0; temp_r30<16; temp_r30++, temp_r31 += 2) {
		if(temp_r31[0] >= 0 && temp_r31[1] > 0) {
			if(--temp_r31[1] <= 0) {
				HuAudFXPlay(temp_r31[0]);
				temp_r31[0] = -1;
				temp_r31[1] = -1;
			}
		}
	}
}

s32 fn_1_B494(s32 arg0, s32 arg1)
{
	s32 *temp_r31;
	s32 temp_r30;
	temp_r31 = &lbl_1_bss_AC[0][0];
	for(temp_r30=0; temp_r30<16; temp_r30++, temp_r31 += 2) {
		if(temp_r31[0] == -1) {
			break;
		}
	}
	if(temp_r30 >= 16) {
		return -1;
	}
	temp_r31[0] = arg0;
	temp_r31[1] = arg1;
	return temp_r30;
}

s16 fn_1_B4F8(float arg0)
{
	return 10.0f*(arg0/360.0f);
}

s16 fn_1_B530(s16 arg0)
{
	if(arg0 >= 0 && arg0 <= 4) {
		return 0;
	}
	return 1;
}
