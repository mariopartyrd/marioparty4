#include "game/object.h"
#include "game/hsfman.h"
#include "game/hsfload.h"
#include "game/hsfdraw.h"
#include "game/printfunc.h"

#include "game/hsfmotion.h"

#include "game/wipe.h"
#include "game/audio.h"
#include "game/msm.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/gamework_data.h"

#include "math.h"
#include "ext_math.h"

typedef struct unk_bss_a18 {
	u32 unk0;
	Vec unk4;
	Vec unk10;
	u8 unk1C[0x88];
} UnkBssA18;

omObjData *lbl_1_bss_AC4;
omObjData *lbl_1_bss_AC0;
omObjData *lbl_1_bss_ABC;
UnkBssA18 lbl_1_bss_A18;
s32 lbl_1_bss_A14;
float lbl_1_bss_A10;
float lbl_1_bss_A0C;
s16 lbl_1_bss_A08;
Process *lbl_1_bss_A04;
Process *lbl_1_bss_A00;

void fn_1_4DF8(omObjData *object);
void fn_1_5A60(omObjData *object);
void fn_1_5DA8(void);
void fn_1_6AE0(ModelData *model, Mtx mtx);
void fn_1_83B4(void);


static const Vec lbl_1_rodata_1C8 = {0.0f, 0.0f, 0.0f};
static const Vec lbl_1_rodata_1D4 = {0.0f, 0.0f, -1.0f};

void fn_1_4AC8(void)
{
	Vec sp14;
	Vec sp8;
	Process *objman;
	OSReport("******* MODELTESTObjectSetup *********\n");
	objman = omInitObjMan(50, 8192);
	CRot.x = -22;
	CRot.y = 0;
	CRot.z = 0;
	Center.x = 0;
	Center.y = 100;
	Center.z = 0;
	CZoom = 400;
	Hu3DCameraCreate(1);
	lbl_1_bss_A0C = 45;
	Hu3DCameraPerspectiveSet(1, lbl_1_bss_A0C, 20, 5000, 1.2f);
	Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
	Hu3DCameraScissorSet(1, 0, 0, 640, 480);
	lbl_1_bss_ABC = omAddObjEx(objman, 0, 32, 32, -1, fn_1_4DF8);
	lbl_1_bss_AC0 = omAddObjEx(objman, 32730, 0, 0, -1, fn_1_5A60);
	lbl_1_bss_A00 = HuPrcCreate(fn_1_5DA8, 100, 8192, 0);
	Hu3DBGColorSet(16, 16, 16);
	Hu3DHookFuncCreate(fn_1_6AE0);
	HuPrcChildCreate(fn_1_83B4, 100, 12288, 0, objman);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
	sp14 = lbl_1_rodata_1C8;
	sp8 = lbl_1_rodata_1D4;
	lbl_1_bss_A18.unk0 = 64;
	lbl_1_bss_A18.unk10.x = 0;
	lbl_1_bss_A18.unk10.y = 0;
	lbl_1_bss_A18.unk10.z = 0;
	msmSeSetListener(&sp14, &sp8, 2000, 1000, 0);
}

void fn_1_4DF8(omObjData *object)
{
	float temp_f31;
	Vec pos;
    Vec offset;
    Vec dir;
    Vec y_offset;

	s8 temp_r31;
	
	if(HuPadBtnDown[0] & PAD_BUTTON_START) {
		if(lbl_1_bss_A00) {
			HuPrcKill(lbl_1_bss_A00);
		}
		if(lbl_1_bss_A04) {
			HuPrcKill(lbl_1_bss_A04);
		}
		HuAudFXListnerKill();
		omOvlReturnEx(1, 1);
		return;
	}
	CRot.y += 0.1f*HuPadStkX[0];
	CRot.x += 0.1f*HuPadStkY[0];
	CZoom += HuPadTrigL[0]/2;
	CZoom -= HuPadTrigR[0]/2;
	if(CZoom < 100) {
		CZoom = 100;
	}
	if(CZoom > 2000) {
		CZoom = 2000;
	}
	pos.x = Center.x + (CZoom * (sind(CRot.y) * cosd(CRot.x)));
	pos.y = (Center.y + (CZoom * -sind(CRot.x)));
	pos.z = (Center.z + (CZoom * (cosd(CRot.y) * cosd(CRot.x))));
	offset.x = Center.x - pos.x;
	offset.y = Center.y - pos.y;
	offset.z = Center.z - pos.z;
	dir.x = (sind(CRot.y) * sind(CRot.x));
	dir.y = cosd(CRot.x);
	dir.z = (cosd(CRot.y) * sind(CRot.x));
	temp_f31 = CRot.z;
	y_offset.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * cosd(temp_f31))
		  + dir.y * (offset.x * offset.y * (1.0f - cosd(temp_f31)) - offset.z * sind(temp_f31))
		  + dir.z * (offset.x * offset.z * (1.0f - cosd(temp_f31)) + offset.y * sind(temp_f31));

	y_offset.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * cosd(temp_f31))
		  + dir.x * (offset.x * offset.y * (1.0f - cosd(temp_f31)) + offset.z * sind(temp_f31))
		  + dir.z * (offset.y * offset.z * (1.0f - cosd(temp_f31)) - offset.x * sind(temp_f31));
	
	y_offset.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * cosd(temp_f31))
				  + (dir.x * (offset.x * offset.z * (1.0 - cosd(temp_f31)) - offset.y * sind(temp_f31))
				  + dir.y * (offset.y * offset.z * (1.0 - cosd(temp_f31)) + offset.x * sind(temp_f31)));
	VECCrossProduct(&dir, &offset, &offset);
	VECNormalize(&offset, &offset);
	temp_r31 = (HuPadSubStkX[0] & 0xF8);
	if (temp_r31 != 0) {
		Center.x += 0.05f * (offset.x * temp_r31);
		Center.y += 0.05f * (offset.y * temp_r31);
		Center.z += 0.05f * (offset.z * temp_r31);
	}
	VECNormalize(&y_offset, &offset);
	temp_r31 = -(HuPadSubStkY[0] & 0xF8);
	if (temp_r31 != 0) {
		Center.x += 0.05f * (offset.x * temp_r31);
		Center.y += 0.05f * (offset.y * temp_r31);
		Center.z += 0.05f * (offset.z * temp_r31);
	}
	Hu3DCameraPerspectiveSet(1, lbl_1_bss_A0C, 20, 5000, 1.2f);
}

void fn_1_5A60(omObjData *object)
{
	Mtx rotAxis;
	Vec pos, target, up;
	float x, y, z;
	
	x = CRot.x;
	y = CRot.y;
	z = CRot.z;
	
	pos.x = (((sind(y)*cosd(x))*CZoom)+Center.x);
	pos.y = (-sind(x)*CZoom)+Center.y;
	pos.z = ((cosd(y)*cosd(x))*CZoom)+Center.z;
	target.x = Center.x;
	target.y = Center.y;
	target.z = Center.z;
	up.x = sind(y)*sind(x);
	up.y = cosd(x);
	up.z = cosd(y)*sind(x);
	Hu3DCameraPosSet(1, pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
	MTXRotDeg(rotAxis, 'y', -y);
	MTXMultVec(rotAxis, &pos, &up);
	VECSubtract(&target, &pos, &up);
	VECNormalize(&up, &up);
	HuAudFXListnerUpdate(&pos, &up);
}

u32 lbl_1_data_3B0[] = {
	0x005D0000, 0x00000000, 
	0x005E0000, 0x00000000, 
	0x005E0001, 0x00000000, 
	0x005F0006, 0x00000001, 
	0x005F0000, 0x00000001, 
	0x005F0002, 0x00000001, 
	0x005F0003, 0x00000001, 
	0x005F0005, 0x00000000, 
	0x005F0017, 0x00000000, 
	0x005F0018, 0x00000000, 
	0x00000000, 0x00000000
};

u32 lbl_1_data_408[] = {
	0x00170000, 0x00000000, 
	0x00170002, 0x00000000, 
	0x00170003, 0x00000000, 
	0x0017000D, 0x00000001, 
	0x00170005, 0x00000001, 
	0x00170007, 0x00000001, 
	0x00170008, 0x00000001, 
	0x0017000C, 0x00000000, 
	0x00170028, 0x00000000, 
	0x00170029, 0x00000000, 
	0x00000000, 0x00000000
};

u32 lbl_1_data_460[] = {
	0x006A0000, 0x00000000, 
	0x006A0002, 0x00000000, 
	0x006A0003, 0x00000000, 
	0x006A000D, 0x00000001, 
	0x006A0005, 0x00000001, 
	0x006A0007, 0x00000001, 
	0x006A0008, 0x00000001, 
	0x006A000C, 0x00000000, 
	0x006A0028, 0x00000000, 
	0x006A0029, 0x00000000, 
	0x00000000, 0x00000000
};

u32 lbl_1_data_4B8[] = {
	0x00870000, 0x00000000, 
	0x00870002, 0x00000000, 
	0x00870003, 0x00000000, 
	0x0087000D, 0x00000001, 
	0x00870005, 0x00000001, 
	0x00870007, 0x00000001, 
	0x00870008, 0x00000001, 
	0x0087000C, 0x00000000, 
	0x00870028, 0x00000000, 
	0x00870029, 0x00000000, 
	0x00000000, 0x00000000
};

u32 lbl_1_data_510[] = {
	0x00820000, 0x00000000, 
	0x00820002, 0x00000000, 
	0x00820003, 0x00000000, 
	0x0082000D, 0x00000001, 
	0x00820005, 0x00000001, 
	0x00820007, 0x00000001, 
	0x00820008, 0x00000001, 
	0x0082000C, 0x00000000, 
	0x00820028, 0x00000000, 
	0x00820029, 0x00000000, 
	0x00000000, 0x00000000
};

u32 lbl_1_data_568[] = {
	0x000E0000, 0x00000000, 
	0x000E0002, 0x00000000, 
	0x000E0003, 0x00000000, 
	0x000E000D, 0x00000001, 
	0x000E0005, 0x00000001, 
	0x000E0007, 0x00000001, 
	0x000E0008, 0x00000001, 
	0x000E000C, 0x00000000, 
	0x000E0028, 0x00000000, 
	0x000E0029, 0x00000000, 
	0x00000000, 0x00000000
};

u32 lbl_1_data_5C0[] = {
	0x000A0000, 0x00000000, 
	0x000A0002, 0x00000000, 
	0x000A0003, 0x00000000, 
	0x000A000D, 0x00000001, 
	0x000A0005, 0x00000001, 
	0x000A0007, 0x00000001, 
	0x000A0008, 0x00000001, 
	0x000A000C, 0x00000000, 
	0x000A0028, 0x00000000, 
	0x000A0029, 0x00000000, 
	0x00000000, 0x00000000
};

u32 lbl_1_data_618[] = {
	0x007E0000, 0x00000000, 
	0x007E0002, 0x00000000, 
	0x007E0003, 0x00000000, 
	0x007E000D, 0x00000001, 
	0x007E0005, 0x00000001, 
	0x007E0007, 0x00000001, 
	0x007E0008, 0x00000001, 
	0x007E000C, 0x00000000, 
	0x007E0028, 0x00000000, 
	0x007E0029, 0x00000000, 
	0x00000000, 0x00000000
};

u32 *lbl_1_data_670[] = {
	lbl_1_data_3B0,
	lbl_1_data_408,
	lbl_1_data_460,
	lbl_1_data_4B8,
	lbl_1_data_510,
	lbl_1_data_568,
	lbl_1_data_5C0,
	lbl_1_data_618
};

void fn_1_69C8(s16 arg0, s16 arg1, s16 arg2);

void fn_1_5DA8(void)
{
	u32 *temp_r31;
	s16 temp_r30;
	s16 temp_r29;
	s16 temp_r28;
	s16 temp_r27;
	s16 temp_r26;
	s16 temp_r25;
	
	s32 temp_r24 = 0;
	s16 sp40[3][32];
	Vec sp34;
	
	Vec sp28 = { 0, 0, 0 };
	Vec sp1C = { 0, 1, 0 };
	s16 sp16[3];
	s16 sp10[3];
	float spC;
	s16 sp8 = 0;
	Hu3DGLightCreate(0, 500, 1000, 0, -0.5, -1, 255, 255, 255);
	temp_r28 = GWPlayerCfg[0].character;
	temp_r31 = lbl_1_data_670[temp_r28];
	sp16[0] = Hu3DModelCreateFile(temp_r31[0]);
	sp16[1] = Hu3DModelCreateFile(temp_r31[2]);
	sp16[2] = Hu3DModelCreateFile(temp_r31[4]);
	HuDataDirClose(temp_r31[0]);
	HuDataDirClose(temp_r31[2]);
	HuDataDirClose(temp_r31[4]);
	temp_r27 = 0;
	temp_r29 = 0;
	while(1) {
		if(temp_r31[(temp_r29*2)+8] == 0) {
			if(temp_r27 == 0) {
				temp_r27 = temp_r29;
			}
			break;
		}
		if(temp_r31[(temp_r29*2)+8] == 0xFFFFFFFF) {
			temp_r27 = temp_r29;
		} else {
			sp40[0][temp_r29] = Hu3DJointMotionFile(sp16[0], temp_r31[(temp_r29*2)+8]);
			sp40[1][temp_r29] = Hu3DJointMotionFile(sp16[1], temp_r31[(temp_r29*2)+8]);
			sp40[2][temp_r29] = Hu3DJointMotionFile(sp16[2], temp_r31[(temp_r29*2)+8]);
		}
		temp_r29++;
	}
	sp10[0] = Hu3DJointMotionFile(sp16[0], temp_r31[6]);
	sp10[1] = Hu3DJointMotionFile(sp16[1], temp_r31[6]);
	sp10[2] = Hu3DJointMotionFile(sp16[2], temp_r31[6]);
	temp_r26 = 0;
	temp_r30 = 0;
	Hu3DMotionSet(sp16[0], sp40[0][temp_r30]);
	Hu3DModelAttrSet(sp16[0], 0x40000001);
	Hu3DMotionSet(sp16[1], sp40[1][temp_r30]);
	Hu3DModelAttrSet(sp16[1], 0x40000001);
	Hu3DMotionSet(sp16[2], sp40[2][temp_r30]);
	Hu3DModelAttrSet(sp16[2], 0x40000001);
	Hu3DModelAttrSet(sp16[1], 0x1);
	Hu3DModelAttrSet(sp16[2], 0x1);
	while(1) {
		temp_r25 = 0;
		if(HuPadBtnDown[0] & PAD_BUTTON_X) {
			temp_r30++;
			if(temp_r30 >= temp_r27) {
				temp_r30 = 0;
			}
			Hu3DMotionSet(sp16[0], sp40[0][temp_r30]);
			Hu3DMotionSet(sp16[1], sp40[1][temp_r30]);
			Hu3DMotionSet(sp16[2], sp40[2][temp_r30]);
			if(temp_r31[(temp_r30*2)+9] != 0) {
				Hu3DModelAttrSet(sp16[0], 0x40000001);
				Hu3DModelAttrSet(sp16[1], 0x40000001);
				Hu3DModelAttrSet(sp16[2], 0x40000001);
			} else {
				Hu3DModelAttrReset(sp16[0], 0x40000001);
				Hu3DModelAttrReset(sp16[1], 0x40000001);
				Hu3DModelAttrReset(sp16[2], 0x40000001);
			}
			fn_1_69C8(temp_r28, sp16[0], 0);
			fn_1_69C8(temp_r28, sp16[1], 1);
			fn_1_69C8(temp_r28, sp16[2], 2);
			temp_r25 = 1;
		}
		if(HuPadBtnDown[0] & PAD_BUTTON_Y) {
			temp_r30--;
			if(temp_r30 < 0) {
				temp_r30 = temp_r27-1;
			}
			Hu3DMotionSet(sp16[0], sp40[0][temp_r30]);
			Hu3DMotionSet(sp16[1], sp40[1][temp_r30]);
			Hu3DMotionSet(sp16[2], sp40[2][temp_r30]);
			if(temp_r31[(temp_r30*2)+9] != 0) {
				Hu3DModelAttrSet(sp16[0], 0x40000001);
				Hu3DModelAttrSet(sp16[1], 0x40000001);
				Hu3DModelAttrSet(sp16[2], 0x40000001);
			} else {
				Hu3DModelAttrReset(sp16[0], 0x40000001);
				Hu3DModelAttrReset(sp16[1], 0x40000001);
				Hu3DModelAttrReset(sp16[2], 0x40000001);
			}
			fn_1_69C8(temp_r28, sp16[0], 0);
			fn_1_69C8(temp_r28, sp16[1], 1);
			fn_1_69C8(temp_r28, sp16[2], 2);
			temp_r25 = 1;
		}
		if(temp_r31[(temp_r30*2)+9] == 0) {
			if(HuPadBtn[0] & PAD_BUTTON_A) {
				Hu3DModelAttrSet(sp16[0], 0x40000001);
				Hu3DModelAttrSet(sp16[1], 0x40000001);
				Hu3DModelAttrSet(sp16[2], 0x40000001);
				temp_r25 = 1;
			} else {
				if(temp_r30 != 3 && temp_r30 != 2) {
					Hu3DModelAttrReset(sp16[0], 0x40000001);
					Hu3DModelAttrReset(sp16[1], 0x40000001);
					Hu3DModelAttrReset(sp16[2], 0x40000001);
				}
			}
		}
		if(temp_r25 != 0) {
			if(temp_r30 == 3) {
				Hu3DMotionSet(sp16[0], sp40[0][temp_r30]);
				Hu3DMotionSet(sp16[1], sp40[1][temp_r30]);
				Hu3DMotionSet(sp16[2], sp40[2][temp_r30]);
				Hu3DModelAttrReset(sp16[0], 0x40000001);
				Hu3DModelAttrReset(sp16[1], 0x40000001);
				Hu3DModelAttrReset(sp16[2], 0x40000001);
				for(temp_r29=0; temp_r29<=30; temp_r29++) {
					Hu3DModelPosSet(sp16[0], 0, sind(temp_r29*6.0f)*150, 0);
					Hu3DModelPosSet(sp16[1], 0, sind(temp_r29*6.0f)*150, 0);
					Hu3DModelPosSet(sp16[2], 0, sind(temp_r29*6.0f)*150, 0);
					if(temp_r29 == 25) {
						Hu3DMotionSet(sp16[0], sp10[0]);
						Hu3DMotionSet(sp16[1], sp10[1]);
						Hu3DMotionSet(sp16[2], sp10[2]);
					}
					HuPrcVSleep();
				}
				while(!Hu3DMotionEndCheck(sp16[0])) {
					HuPrcVSleep();
				}
				fn_1_69C8(temp_r28, sp16[0], 0);
				fn_1_69C8(temp_r28, sp16[1], 1);
				fn_1_69C8(temp_r28, sp16[2], 2);
				Hu3DMotionShiftSet(sp16[0], sp40[0][0], 0, 16, 0x40000001);
				Hu3DMotionShiftSet(sp16[1], sp40[1][0], 0, 16, 0x40000001);
				Hu3DMotionShiftSet(sp16[2], sp40[2][0], 0, 16, 0x40000001);
			}
			temp_r24 = 0;
		}
		sp34.x = Center.x + (CZoom * (sind(CRot.y) * cosd(CRot.x)));
		sp34.y = (Center.y + (CZoom * -sind(CRot.x)));
		sp34.z = (Center.z + (CZoom * (cosd(CRot.y) * cosd(CRot.x))));
		
		spC = VECMag(&sp34);
		if(HuPadBtnDown[0] & PAD_BUTTON_B) {
			temp_r26++;
			if(temp_r26 >= 3) {
				temp_r26 = 0;
			}
		}
		Hu3DModelAttrSet(sp16[0], 1);
		Hu3DModelAttrSet(sp16[1], 1);
		Hu3DModelAttrSet(sp16[2], 1);
		switch(temp_r26) {
			case 0:
				Hu3DModelAttrReset(sp16[0], 1);
				break;
				
			case 1:
				Hu3DModelAttrReset(sp16[1], 1);
				break;
				
			case 2:
				Hu3DModelAttrReset(sp16[2], 1);
				break;
		}
		HuPrcVSleep();
	}
}

char *lbl_1_data_6F4[] = {
	"s3_mario_eyes_1",
	"mario_eyes_2",
	"mario_eyes_2",
	"S3c001m0_eye",
	"S3c001m1_eye",
	"c001m3_eye",
	"GC-eyes",
	"s3tc_GC-eyes_2",
	"s3tc_GC-eyes_2",
	"S3c003m1",
	"S3c003m1",
	"S3c003m1",
	"GC-eyes",
	"s3tc_GC-eyes_2",
	"s3tc_GC-eyes_2",
	"GC-eyes",
	"s3tc_GC-eyes_2",
	"s3tc_GC-eyes_2",
	"GC-eyes",
	"s3tc_GC-eyes_2",
	"s3tc_GC-eyes_2",
	"GC-eyes",
	"s3tc_GC-eyes_2",
	"s3tc_GC-eyes_2",
};

void fn_1_69C8(s16 arg0, s16 arg1, s16 arg2)
{
	HsfdrawStruct01 *temp_r31;
	HsfAttribute *temp_r30;
	ModelData *temp_r29;
	s16 temp_r28;
	char *temp_r27;
	temp_r29 = &Hu3DData[arg1];
	temp_r30 = temp_r29->hsfData->attribute;
	temp_r27 = MakeObjectName(lbl_1_data_6F4[arg2+(arg0*3)]);
	for(temp_r28=0; temp_r28<temp_r29->hsfData->attributeCnt; temp_r28++, temp_r30++) {
		if(temp_r30->bitmap->name[0] == temp_r27[0] && strcmp(temp_r30->bitmap->name, temp_r27) == 0 && temp_r30->unk04) {
			temp_r31 = temp_r30->unk04;
			temp_r31->unk08 = temp_r31->unk0C = temp_r31->unk10 = 0;
			temp_r31->unk14 = temp_r31->unk18 = temp_r31->unk1C = 0;
		}
	}
}

s32 lbl_1_data_754 = 20;

void fn_1_6AE0(ModelData *model, Mtx mtx)
{
	s32 temp_r31;
	u8 temp_r30, temp_r29, temp_r28;
	s32 sp84 = 0;
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_RGB8, 0);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
	GXLoadPosMtxImm(mtx, GX_PNMTX0);
	GXBegin(GX_LINES, GX_VTXFMT0, (lbl_1_data_754+1)*4);
	for(temp_r31=0; temp_r31<=lbl_1_data_754; temp_r31++) {
		temp_r30 = temp_r29 = temp_r28 = 255;
		GXPosition3f32((temp_r31*100)-((lbl_1_data_754/2)*100), 0, (-(lbl_1_data_754/2))*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32((temp_r31*100)-((lbl_1_data_754/2)*100), 0, (lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32(-(lbl_1_data_754/2)*100, 0, (temp_r31*100)-((lbl_1_data_754/2)*100));
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32((lbl_1_data_754/2)*100, 0, (temp_r31*100)-((lbl_1_data_754/2)*100));
		GXColor3u8(temp_r30, temp_r29, temp_r28);
	}
	GXBegin(GX_LINES, GX_VTXFMT0, (lbl_1_data_754+1)*4);
	for(temp_r31=0; temp_r31<=lbl_1_data_754; temp_r31++) {
		temp_r30 = temp_r29 = temp_r28 = 255;
		GXPosition3f32((temp_r31*100)-((lbl_1_data_754/2)*100), lbl_1_data_754*100, (-(lbl_1_data_754/2))*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32((temp_r31*100)-((lbl_1_data_754/2)*100), 0, -(lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32(-(lbl_1_data_754/2)*100, temp_r31*100, -(lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32((lbl_1_data_754/2)*100, temp_r31*100, -(lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
	}
	GXBegin(GX_LINES, GX_VTXFMT0, (lbl_1_data_754+1)*4);
	for(temp_r31=0; temp_r31<=lbl_1_data_754; temp_r31++) {
		temp_r30 = temp_r29 = temp_r28 = 255;
		GXPosition3f32((temp_r31*100)-((lbl_1_data_754/2)*100), lbl_1_data_754*100, (lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32((temp_r31*100)-((lbl_1_data_754/2)*100), 0, (lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32(-(lbl_1_data_754/2)*100, temp_r31*100, (lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32((lbl_1_data_754/2)*100, temp_r31*100, (lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
	}
	GXBegin(GX_LINES, GX_VTXFMT0, (lbl_1_data_754+1)*4);
	for(temp_r31=0; temp_r31<=lbl_1_data_754; temp_r31++) {
		temp_r30 = temp_r29 = temp_r28 = 255;
		GXPosition3f32((lbl_1_data_754/2)*100, lbl_1_data_754*100, (temp_r31*100)-((lbl_1_data_754/2)*100));
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32((lbl_1_data_754/2)*100, 0, (temp_r31*100)-((lbl_1_data_754/2)*100));
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32((lbl_1_data_754/2)*100, temp_r31*100, -(lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32((lbl_1_data_754/2)*100, temp_r31*100, (lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
	}
	GXBegin(GX_LINES, GX_VTXFMT0, (lbl_1_data_754+1)*4);
	for(temp_r31=0; temp_r31<=lbl_1_data_754; temp_r31++) {
		temp_r30 = temp_r29 = temp_r28 = 255;
		GXPosition3f32(-(lbl_1_data_754/2)*100, lbl_1_data_754*100, (temp_r31*100)-((lbl_1_data_754/2)*100));
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32(-(lbl_1_data_754/2)*100, 0, (temp_r31*100)-((lbl_1_data_754/2)*100));
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32(-(lbl_1_data_754/2)*100, temp_r31*100, -(lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
		GXPosition3f32(-(lbl_1_data_754/2)*100, temp_r31*100, (lbl_1_data_754/2)*100);
		GXColor3u8(temp_r30, temp_r29, temp_r28);
	}
}

s16 lbl_1_data_758[] = {
	1,
	3,
	2,
	13,
	14,
	15,
	16,
	68,
	-1
};

s16 lbl_1_data_76A[] = {
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	-1
};

void fn_1_814C(void)
{
	s16 temp_r31 = 0;
	s16 temp_r30 = 0;
	s16 temp_r29 = 0;
	s16 temp_r28;
	Vec sp8 = { 0, 0, 0 };
	while(1) {
		lbl_1_bss_A14 = HuAudFXEmiterPlay(1282, &sp8);
		HuPrcSleep(60);
		if(HuPadBtnDown[1] & PAD_BUTTON_A) {
			HuAudSeqFadeOut(temp_r28, 60);
			temp_r28 = HuAudSeqPlay(lbl_1_data_758[temp_r31]);
			temp_r31++;
			if(lbl_1_data_758[temp_r31] == -1) {
				temp_r31 = 0;
			}
			temp_r29 = 30;
		}
		if(HuPadBtnDown[1] & PAD_BUTTON_B) {
			HuAudFXPlay(lbl_1_data_76A[temp_r30]);
			temp_r30++;
			if(lbl_1_data_76A[temp_r30] == -1) {
				temp_r30 = 0;
			}
			temp_r29 = 30;
		}
		if(temp_r29) {
			temp_r29--;
			print8(16, 430, 2.0f, "MusicNo:%d SENo:%d", temp_r31, temp_r30);
		}
		HuPrcVSleep();
	}
}

s16 lbl_1_data_7AC = -1;

u32 fn_1_82C8(void)
{
	s16 temp_r31;
	temp_r31 = HuPadBtn[0];
	if(lbl_1_bss_A08) {
		lbl_1_bss_A08--;
		if(!temp_r31) {
			lbl_1_bss_A08 = 0;
		} else {
			temp_r31 = 0;
		}
	} else if(temp_r31) {
		if(lbl_1_data_7AC == temp_r31) {
			lbl_1_bss_A08 = 3;
		} else {
			lbl_1_bss_A08 = 20;
		}
		lbl_1_data_7AC = temp_r31;
	} else {
		lbl_1_data_7AC = 0;
	}
	return temp_r31;
}

void fn_1_83B4(void)
{
	u32 temp_r29;
	Process *temp_r28;
	temp_r28 = HuPrcCurrentGet();
	HuPrcSetStat(temp_r28, 0xC);
	while(1) {
		temp_r29 = fn_1_82C8();
		if(HuPadBtn[0] & PAD_BUTTON_RIGHT) {
			while(1) {
				temp_r29 = fn_1_82C8();
				if(HuPadBtn[0] & PAD_BUTTON_LEFT) {
					break;
				}
				if(!temp_r29) {
					HuPrcAllPause(1);
					Hu3DPauseSet(1);
				} else {
					HuPrcAllPause(0);
					Hu3DPauseSet(0);
				}
				HuPrcVSleep();
			}
			HuPrcAllPause(0);
			Hu3DPauseSet(0);
		}
		if(temp_r29 & PAD_BUTTON_UP) {
			if(lbl_1_bss_A0C < 120.0f) {
				lbl_1_bss_A0C++;
			}
		}
		if(temp_r29 & PAD_BUTTON_DOWN) {
			if(lbl_1_bss_A0C > 5.0f) {
				lbl_1_bss_A0C--;
			}
		}
		HuPrcVSleep();
	}
}