#include "game/object.h"
#include "game/objsub.h"
#include "game/wipe.h"
#include "game/chrman.h"
#include "game/minigame_seq.h"
#include "game/pad.h"

#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/sprite.h"

#include "game/audio.h"
#include "game/gamework_data.h"

#include "REL/m408Dll.h"

#include "math.h"
#include "ext_math.h"

typedef struct struct_data_20C {
	s32 unk0;
	float unk4;
	float unk8;
} StructData20C;

typedef struct struct_bss_da4 {
	s32 unk0;
	s32 unk4;
	s32 unk8;
	Vec unkC;
	Vec unk18;
	Vec unk24;
	float unk30;
	Vec unk34;
	float unk40[2];
	float unk48;
	float unk4C;
	s32 unk50;
	s32 unk54;
	s32 unk58;
	s32 unk5C;
	s32 unk60;
	float unk64;
} StructBssDA4;

void fn_1_12C6C(StructBssDA4 *arg0);
void fn_1_1305C(StructBssDA4 *arg0);
void fn_1_134D8(StructBssDA4 *arg0);
void fn_1_13820(StructBssDA4 *arg0);
void fn_1_13D88(StructBssDA4 *arg0);
void fn_1_1406C(StructBssDA4 *arg0);
void fn_1_144D0(StructBssDA4 *arg0);
void fn_1_14DB4(StructBssDA4 *arg0);
void fn_1_151A4(StructBssDA4 *arg0);

s32 lbl_1_data_1A0[9] = {
	0x00270012,
	0x00270012,
	0x00270012,
	0x00270012,
	0x00270012,
	0x00270014,
	0x00270014,
	0x00270016,
	0x00270017
};

s32 lbl_1_data_1C4[9] = {
	0x00270013,
	0x00270013,
	0x00270013,
	0x00270013,
	0x00270013,
	0x00270015,
	0x00270015,
	0,
	0
};

typedef void (*BssDA4Func)(StructBssDA4 *arg0);

BssDA4Func lbl_1_data_1E8[9] = {
	fn_1_12C6C,
	fn_1_1305C,
	fn_1_134D8,
	fn_1_13820,
	fn_1_13D88,
	fn_1_1406C,
	fn_1_144D0,
	fn_1_14DB4,
	fn_1_151A4
};

StructData20C lbl_1_data_20C[] = {
	{ 0, 10600, 100 },
	{ 0, 10600, 290 },
	{ 7, 10500, 0 },
	{ 7, 10400, 72 },
	{ 7, 10300, 144 },
	{ 7, 10200, 216 },
	{ 7, 10100, 288 },
	{ 5, 9600, 0 },
	{ 7, 9000, 0 },
	{ 7, 9000, 72 },
	{ 7, 9000, 144 },
	{ 7, 9000, 216 },
	{ 7, 9000, 288 },
	{ 1, 8600, 150 },
	{ 7, 8500, 216 },
	{ 7, 8400, 288 },
	{ 7, 8300, 0 },
	{ 7, 8200, 72 },
	{ 7, 8100, 144 },
	{ 6, 7700, 0 },
	{ 6, 7700, 180 },
	{ 7, 7500, 165 },
	{ 7, 7500, 285 },
	{ 7, 7500, 45 },
	{ 8, 7000, 225 },
	{ 8, 7000, 345 },
	{ 8, 7000, 105 },
	{ 7, 6500, 165 },
	{ 7, 6500, 285 },
	{ 7, 6500, 45 },
	{ 4, 5500, 0 },
	{ 4, 5500, 120 },
	{ 4, 5500, 240 },
	{ 7, 4700, 0 },
	{ 7, 4700, 72 },
	{ 7, 4700, 144 },
	{ 7, 4700, 216 },
	{ 7, 4700, 288 },
	{ 5, 4500, 120 },
	{ 7, 4250, 165 },
	{ 7, 4250, 285 },
	{ 7, 4250, 45 },
	{ 5, 4000, 120 },
	{ 7, 3750, 225 },
	{ 7, 3750, 345 },
	{ 7, 3750, 105 },
	{ 5, 3500, 240 },
	{ 7, 3250, 165 },
	{ 7, 3250, 285 },
	{ 7, 3250, 45 },
	{ 7, 2100, 36 },
	{ 7, 2100, 108 },
	{ 7, 2100, 180 },
	{ 7, 2100, 252 },
	{ 7, 2100, 324 },
	{ 3, 1500, 0 },
	{ 3, 1500, 120 },
	{ 3, 1500, 240 },
	{ 8, 1300, 165 },
	{ 8, 1300, 285 },
	{ 8, 1300, 45 },
	{ -1, 10000, 0 },
};

GXColor lbl_1_data_4F4[4] = {
	{ 255, 255, 255, 255 },
	{ 255, 255, 0, 255 },
	{ 0, 255, 255, 255 },
	{ 255, 200, 200, 255 }
};

u8 lbl_1_data_504[] = {
	5, 3, 1, 0
};

float lbl_1_data_508[3] = {
	72, 120, 0
};

float lbl_1_data_514[3] = {
	0, 60, 0
};

float lbl_1_data_520[3] = {
	30, 60, 90
};

Vec lbl_1_data_52C[3] = {
	{ 1500, 2500, 1500 },
	{ 0, 1, 0 },
	{ 0, 0, 0 }
};

omObjData *lbl_1_bss_75A8;
omObjData *lbl_1_bss_75A4;
StructBssDA4 lbl_1_bss_DA4[256];
s32 lbl_1_bss_DA0;
s32 lbl_1_bss_D9C;
Vec lbl_1_bss_D6C[4];
Vec lbl_1_bss_16C[256];
u32 lbl_1_bss_168;

void fn_1_11960(omObjData *object);
void fn_1_15BCC(omObjData *object);

void fn_1_118D0(Process *objman)
{
	lbl_1_bss_168 = 0;
	lbl_1_bss_75A8 = omAddObjEx(objman, 40, 256, 1, -1, fn_1_11960);
	lbl_1_bss_75A4 = omAddObjEx(objman, 41, 4, 0, -1, fn_1_15BCC);
}

void fn_1_11E3C(StructBssDA4 *arg0, s32 arg1);
void fn_1_12354(omObjData *object);
void fn_1_123C8(omObjData *object);

void fn_1_155E0(s16 arg0, s16 arg1);
void fn_1_15658(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_1_11960(omObjData *object)
{
	StructBssDA4 *temp_r31;
	s32 temp_r29;
	s16 temp_r28;
	s16 temp_r27;
	s16 temp_r26;
	s16 temp_r25;
	s16 temp_r24;
	s16 temp_r23;
	s16 temp_r22;
	temp_r31 = &lbl_1_bss_DA4[0];
	lbl_1_bss_DA0 = 0;
	lbl_1_bss_D9C = 0;
	while(lbl_1_data_20C[lbl_1_bss_DA0].unk0 != -1) {
		if(lbl_1_data_20C[lbl_1_bss_DA0].unk0 == 7) {
			lbl_1_bss_D9C++;
		}
		lbl_1_bss_DA0++;
	}
	object->stat |= 0x100;
	temp_r27 = temp_r26 = temp_r25 = temp_r24 = -1;
	for(temp_r29=0; temp_r29<lbl_1_bss_DA0; temp_r29++, temp_r31++) {
		fn_1_11E3C(temp_r31, temp_r29);
		switch(temp_r31->unk0) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				if(temp_r27 < 0) {
					temp_r27 = Hu3DModelCreateFile(lbl_1_data_1A0[temp_r31->unk0]);
					temp_r23 = Hu3DJointMotionFile(temp_r27, lbl_1_data_1C4[temp_r31->unk0]);
					Hu3DModelAttrSet(temp_r27, 0x40000001);
					Hu3DMotionSet(temp_r27, temp_r23);
					temp_r28 = temp_r27;
				} else {
					temp_r28 = Hu3DModelLink(temp_r27);
				}
				break;
				
			case 5:
			case 6:
				if(temp_r26 < 0) {
					temp_r26 = Hu3DModelCreateFile(lbl_1_data_1A0[temp_r31->unk0]);
					temp_r22 = Hu3DJointMotionFile(temp_r26, lbl_1_data_1C4[temp_r31->unk0]);
					Hu3DModelAttrSet(temp_r26, 0x40000001);
					Hu3DMotionSet(temp_r26, temp_r22);
					temp_r28 = temp_r26;
				} else {
					temp_r28 = Hu3DModelLink(temp_r26);
				}
				break;
			
			case 7:
				if(temp_r25 < 0) {
					temp_r25 = Hu3DModelCreateFile(lbl_1_data_1A0[temp_r31->unk0]);
					temp_r28 = temp_r25;
				} else {
					temp_r28 = Hu3DModelLink(temp_r25);
				}
				break;
				
			case 8:
				if(temp_r24 < 0) {
					temp_r24 = Hu3DModelCreateFile(lbl_1_data_1A0[temp_r31->unk0]);
					temp_r28 = temp_r24;
				} else {
					temp_r28 = Hu3DModelLink(temp_r24);
				}
				break;
				
			default:
				break;
		}
		object->model[temp_r29] = temp_r28;
		Hu3DModelPosSetV(object->model[temp_r29], &temp_r31->unkC);
		Hu3DModelRotSetV(object->model[temp_r29], &temp_r31->unk34);
		Hu3DModelScaleSet(object->model[temp_r29], 0.15f, 0.15f, 0.15f);
		Hu3DModelCameraSet(object->model[temp_r29], 1);
		Hu3DModelAttrSet(object->model[temp_r29], 1);
		if(temp_r31->unk0 < 7) {
			Hu3DModelAttrSet(object->model[temp_r29], 0x40000001);
		}
	}
	for(temp_r29=lbl_1_bss_DA0; temp_r29<lbl_1_bss_DA0+lbl_1_bss_D9C; temp_r29++) {
		temp_r28 = Hu3DParticleCreate(HuSprAnimReadFile(0x270018), 32);
		object->model[temp_r29] = temp_r28;
		Hu3DModelAttrSet(temp_r28, 1);
		Hu3DModelLayerSet(temp_r28, 6);
		Hu3DParticleColSet(temp_r28, 255, 255, 255);
		Hu3DParticleHookSet(temp_r28, fn_1_15658);
		Hu3DModelPosSet(temp_r28, 0, 0, 0);
		fn_1_155E0(temp_r28, 0);
	}
	object->func = fn_1_12354;
}

void fn_1_11E3C(StructBssDA4 *arg0, s32 arg1)
{
	float temp_f31;
	float temp_f30;
	s32 temp_r29;
	temp_r29 = 0;
	temp_f30 = 40;
	temp_f31 = 20;
	arg0->unk0 = lbl_1_data_20C[arg1].unk0;
	arg0->unk4 = arg1;
	arg0->unk8 = -1;
	arg0->unk18.x = arg0->unkC.x = 0;
	arg0->unk18.y = arg0->unkC.y = lbl_1_data_20C[arg1].unk4;
	arg0->unk18.z = arg0->unkC.z = 0;
	arg0->unk24.x = arg0->unk24.y = arg0->unk24.z = 0;
	arg0->unk48 = 180;
	arg0->unk34.x = arg0->unk34.z = arg0->unk34.y = 0;
	arg0->unk40[0] = arg0->unk40[1] = 0;
	arg0->unk30 = 0;
	arg0->unk4C = 1;
	arg0->unk50 = 1;
	arg0->unk54 = 0;
	arg0->unk5C = 1;
	arg0->unk58 = 0;
	arg0->unk60 = 0;
	arg0->unk64 = 0;
	switch(arg0->unk0) {
		case 0:
			arg0->unk64 = temp_f31+(rand8()%(int)temp_f30);
			arg0->unk30 = lbl_1_data_20C[arg1].unk8;
			arg0->unk34.y  = 180+(-arg0->unk30+90);
			
			break;
			
		case 1:
			arg0->unk34.y = arg0->unk40[0] = 180+(-arg0->unk30+90);
			arg0->unk30 = rand8()%360;
			break;
			
		case 2:
			arg0->unk30 = lbl_1_data_20C[arg1].unk8;
			arg0->unk34.y  = 90+(180+(-arg0->unk30+90));
			break;
			
		case 3:
			arg0->unk30 = lbl_1_data_20C[arg1].unk8;
			arg0->unk34.y  = (180+(-arg0->unk30+90))-90;
			break;
			
		case 4:
			arg0->unk30 = lbl_1_data_20C[arg1].unk8;
			arg0->unk34.y  = 180+(-arg0->unk30+90);
			break;
			
		case 5:
			arg0->unk30 = rand8()%360;
			arg0->unk34.y  = 180+(-arg0->unk30+90);
			arg0->unk48 = 0;
			break;
			
		case 6:
			arg0->unk30 = lbl_1_data_20C[arg1].unk8;
			arg0->unk34.y  = -arg0->unk30+90;
			break;
			

			
		case 7:
		case 8:
			arg0->unk30 = lbl_1_data_20C[arg1].unk8;
			arg0->unk8 = lbl_1_bss_DA0+temp_r29;
			temp_r29++;
			break;
	}
	if(arg0->unk34.y > 360) {
		arg0->unk34.y -= 360;
	} else {
		if(arg0->unk34.y < 0) {
			arg0->unk34.y += 360;
		}
	}
}

void fn_1_12354(omObjData *object)
{
	s32 temp_r31;
	u32 temp_r30;
	temp_r30 = fn_1_6878();
	if(temp_r30 == 2) {
		for(temp_r31=0; temp_r31<lbl_1_bss_DA0; temp_r31++);
		object->func =fn_1_123C8;
	}
	
}

void fn_1_12670(omObjData *object);
float fn_1_12674(StructBssDA4 *object);
void fn_1_127A0(StructBssDA4 *object);

void fn_1_123C8(omObjData *object)
{
	StructBssDA4 *temp_r31;
	s32 temp_r29;
	u32 temp_r28;
	temp_r31 = &lbl_1_bss_DA4[0];
	lbl_1_bss_168 = 0;
	for(temp_r29=0; temp_r29<lbl_1_bss_DA0; temp_r29++, temp_r31++) {
		if(temp_r31->unk50 == 1) {
			lbl_1_data_1E8[temp_r31->unk0](temp_r31);
			if(temp_r31->unk5C == 0) {
				fn_1_127A0(temp_r31);
			}
			Hu3DModelPosSetV(object->model[temp_r29], &temp_r31->unkC);
			Hu3DModelRotSetV(object->model[temp_r29], &temp_r31->unk34);
			Hu3DModelScaleSet(object->model[temp_r29], 0.15f*temp_r31->unk4C, 0.15f*temp_r31->unk4C, 0.15f*temp_r31->unk4C);
			if(temp_r31->unkC.y > fn_1_6888()-1000 && temp_r31->unkC.y < fn_1_6888()+200) {
				Hu3DModelAttrReset(object->model[temp_r29], 1);
			} else {
				Hu3DModelAttrSet(object->model[temp_r29], 1);
			}
			if(temp_r31->unk0 == 7 || temp_r31->unk0 == 8) {
				if(temp_r31->unkC.y > fn_1_6888()-150 && temp_r31->unkC.y < fn_1_6888()+10) {
					lbl_1_bss_16C[lbl_1_bss_168++] = temp_r31->unkC;
					
				}
			}
		} else {
			Hu3DModelAttrSet(object->model[temp_r29], 1);
		}
	}
	temp_r28 = fn_1_6878();
	if(temp_r28 == 5) {
		for(temp_r29=0; temp_r29<lbl_1_bss_DA0; temp_r29++, temp_r31++) {
			Hu3DModelAttrSet(object->model[temp_r29], 1);
		}
		object->func = fn_1_12670;
	}
	
}

void fn_1_12670(omObjData *object)
{
	
}

void fn_1_15618(s16 arg0, float arg1, float arg2, float arg3);
void fn_1_15B50(s16 arg0);

float fn_1_12674(StructBssDA4 *arg0)
{
	Vec sp8;
	float temp_f31;
	float temp_f30;
	float temp_f29;
	Work2FAC *temp_r31;
	s32 temp_r30;
	temp_f30 = -1;
	temp_f29 = 10000;
	for(temp_r30=0; temp_r30<4; temp_r30++) {
		temp_r31 = fn_1_68A8(temp_r30);
		if(temp_r31->unk4 & 0x10) {
			continue;
		}
		sp8.x = temp_r31->unk1C.x-arg0->unk24.x;
		sp8.y = 0;
		sp8.z = temp_r31->unk1C.z-arg0->unk24.z;
		temp_f31 = VECMag(&sp8);
		if(temp_f31 < temp_f29) {
			temp_f30 = atan2d(sp8.x, sp8.z);
			temp_f29 = temp_f31;
		}
	}
	return temp_f30;
}

void fn_1_127A0(StructBssDA4 *arg0)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f26;
	float temp_f23;
	Work2FAC *temp_r31;
	s32 temp_r29;
	temp_f23 = 14;
	for(temp_r29=0; temp_r29<4; temp_r29++) {
		temp_r31 = fn_1_68A8(temp_r29);
		if(temp_r31->unk4 & 0x12) {
			continue;
		}
		switch(arg0->unk0) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 7:
			case 8:
				temp_f31 = temp_r31->unk1C.x-arg0->unk24.x;
				temp_f29 = temp_r31->unk1C.y-arg0->unk24.y;
				temp_f30 = temp_r31->unk1C.z-arg0->unk24.z;
				temp_f26 = VECMagPoint(temp_f31, temp_f29, temp_f30);
				break;
				
			case 5:
			case 6:
				temp_f31 = temp_r31->unk1C.x-arg0->unk24.x;
				temp_f30 = temp_r31->unk1C.z-arg0->unk24.z;
				temp_f26 = VECMagPoint(temp_f31, 0, temp_f30);
				break;
		}
		if(temp_f26 < temp_f23 && 0.0f != temp_f26) {
			if(arg0->unk0 != 7 && arg0->unk0 != 8) {
				temp_r31->unk4 |= 0x1;
				temp_r31->unk40.x = temp_f31;
				temp_r31->unk40.z = temp_f30;
				lbl_1_bss_D6C[temp_r29].x = (0.5f*temp_f31)+arg0->unk24.x;
				lbl_1_bss_D6C[temp_r29].z = (0.5f*temp_f30)+arg0->unk24.z;
				lbl_1_bss_D6C[temp_r29].y = temp_r31->unk1C.y;
				lbl_1_bss_75A4->work[0] = temp_r29;
			} else {
				arg0->unk58 = 1;
				if(arg0->unk0 == 8) {
					temp_r31->unk14 += 5;
					fn_1_67C4(temp_r29, 5);
				} else {
					temp_r31->unk14 += 1;
					fn_1_67C4(temp_r29, 1);
				}
			}
		}
	}
}

void fn_1_12C6C(StructBssDA4 *arg0)
{
	Work2FAC *temp_r30;
	float temp_f31;
	float temp_f30;
	float temp_f26;
	float temp_f25;
	temp_f26 = cosd(arg0->unk30);
	temp_f25 = sind(arg0->unk30);
	arg0->unkC.x = temp_f26*arg0->unk64;
	arg0->unkC.z = temp_f25*arg0->unk64;
	temp_f30 = fn_1_6888();
	switch(arg0->unk54) {
		case 0:
			if(arg0->unkC.y > temp_f30) {
				arg0->unk60 = 0;
				arg0->unk54 = 1;
			}
			arg0->unk34.x = fn_1_883C(arg0->unk34.x, -30, 0.1f);
			arg0->unk5C = 1;
			break;
			
		case 1:
			arg0->unk5C = 0;
			arg0->unkC.y = temp_f30;
			arg0->unk24.x = arg0->unkC.x;
			arg0->unk24.y = arg0->unkC.y+5.0f;
			arg0->unk24.z = arg0->unkC.z;
			temp_f31 = fn_1_12674(arg0);
			if(temp_f31 >= 0) {
				arg0->unk34.y = fn_1_883C(arg0->unk34.y, temp_f31, 0.1f);
			}
			arg0->unk34.x = fn_1_883C(arg0->unk34.x, 0, 0.1f);
			if(arg0->unk60 < 90.0f) {
				arg0->unk60++;
			} else {
				arg0->unk54 = 3;
			}
			break;
			
		case 3:
			arg0->unk34.x = fn_1_883C(arg0->unk34.x, -30, 0.1f);
			arg0->unk5C = 1;
			if(arg0->unkC.y-15.0f > Center.y+CZoom) {
				arg0->unk54 = 4;
				arg0->unk50 = 0;
				Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			}
			break;
			
		case 4:
			break;
	}
}

void fn_1_1305C(StructBssDA4 *arg0)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	float temp_f27;
	float temp_f26;
	arg0->unk48 += 1.5f;
	if(arg0->unk48 > 360.0f) {
		arg0->unk48 -= 360.0f;
	}
	temp_f29 = cosd(arg0->unk30);
	temp_f28 = sind(arg0->unk30);
	arg0->unk18.x = temp_f29*arg0->unk64;
	arg0->unk18.z = temp_f28*arg0->unk64;
	temp_f31 = sind(arg0->unk48);
	arg0->unkC.x = temp_f29*(60*temp_f31);
	arg0->unkC.z = temp_f28*(60*temp_f31);
	temp_f30 = -arg0->unk30-90;
	if(temp_f31 < 0) {
		temp_f30 += 180;
	}
	arg0->unk34.y = fn_1_883C(arg0->unk34.y, temp_f30, 0.05f);
	temp_f30 = fabs(temp_f31);
	arg0->unk34.x = -30*temp_f30;
	temp_f26 = fn_1_6888();
	switch(arg0->unk54) {
		case 0:
			if(arg0->unkC.y > temp_f26) {
				arg0->unk60 = 0;
				arg0->unk54 = 1;
			}
			arg0->unk5C = 1;
			if(temp_f31 >= sind(75.0f)) {
				temp_f27 = (arg0->unk48-75)/30;
				arg0->unk40[1] = 180+arg0->unk40[0];
			} else if(temp_f31 <= sind(255.0f)) {
				temp_f27 = (arg0->unk48-255)/30;
				arg0->unk40[1] = 180+arg0->unk40[0];
			} else {
				temp_f27 = 0;
				if(arg0->unk40[1] > 360.0f) {
					arg0->unk40[1] -= 360.0f;
				}
				arg0->unk40[0] = arg0->unk40[1];
			}
			break;
			
		case 1:
			arg0->unk5C = 0;
			arg0->unkC.y = temp_f26;
			arg0->unk24.x = arg0->unkC.x;
			arg0->unk24.y = arg0->unkC.y+5;
			arg0->unk24.z = arg0->unkC.z;
			if(arg0->unk60 < 120.0f) {
				arg0->unk60++;
			} else {
				arg0->unk54 = 3;
			}
			break;
			
		case 3:
			arg0->unk5C = 1;
			if(arg0->unkC.y-15.0f > Center.y+CZoom) {
				arg0->unk54 = 4;
				arg0->unk50 = 0;
				Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			}
			break;
			
		case 4:
			break;
	}
}

void fn_1_134D8(StructBssDA4 *arg0)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	arg0->unk30 += 1.8f;
	if(arg0->unk30 > 360.0f) {
		arg0->unk30 -= 360.0f;
	}
	temp_f30 = cosd(arg0->unk30);
	temp_f29 = sind(arg0->unk30);
	arg0->unk64 = 64;
	arg0->unkC.x = temp_f30*arg0->unk64;
	arg0->unkC.z = temp_f29*arg0->unk64*0.7f;
	temp_f31 = fn_1_6888();
	switch(arg0->unk54) {
		case 0:
			if(arg0->unkC.y > temp_f31) {
				arg0->unk60 = 0;
				arg0->unk54 = 1;
			}
			arg0->unk5C = 1;
			arg0->unk34.y = -arg0->unk30;
			if(arg0->unk34.y > 360.0f) {
				arg0->unk34.y -= 360.0f;
			} else if(arg0->unk34.y < 0.0f) {
				arg0->unk34.y += 360.0f;
			}
			break;
			
		case 1:
			arg0->unk5C = 0;
			arg0->unkC.y = temp_f31;
			arg0->unk24.x = arg0->unkC.x;
			arg0->unk24.y = arg0->unkC.y+5;
			arg0->unk24.z = arg0->unkC.z;
			arg0->unk34.y -= 10.0f;
			if(arg0->unk34.y > 360.0f) {
				arg0->unk34.y -= 360.0f;
			}
			if(arg0->unk60 < 120.0f) {
				arg0->unk60++;
			} else {
				arg0->unk54 = 3;
			}
			break;
			
		case 3:
			arg0->unk5C = 1;
			if(arg0->unkC.y-15.0f > Center.y+CZoom) {
				arg0->unk54 = 4;
				arg0->unk50 = 0;
				Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			}
			break;
			
		case 4:
			break;
	}
}

void fn_1_13820(StructBssDA4 *arg0)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	float temp_f27;
	float temp_f26;
	float temp_f25;
	float temp_f24;
	float temp_f23;
	float temp_f22;
	float temp_f21;
	float temp_f20;
	float temp_f19;
	float sp8;
	arg0->unk30 += 2.0f;
	if(arg0->unk30 > 360.0f) {
		arg0->unk30 -= 360.0f;
	}
	temp_f26 = cosd(arg0->unk30);
	temp_f25 = sind(arg0->unk30);
	arg0->unk40[1] = 270.0f;
	temp_f29 = arg0->unk18.y;
	switch(arg0->unk54) {
		case 0:
			temp_f31 = 10;
			temp_f28 = temp_f26*temp_f31;
			temp_f27 = temp_f25*temp_f31;
			temp_f29 = arg0->unk18.y;
			arg0->unk40[0] = 0;
			arg0->unk34.x = fn_1_883C(arg0->unk34.x, -30, 0.1);
			arg0->unk34.y = 180.0f+(90.0f+ -arg0->unk30);
			temp_f30 = fn_1_6888();
			if(temp_f30 < 5.0f+temp_f29) {
				arg0->unk48 = 0;
				arg0->unk54 = 1;
				arg0->unk40[0] = 8;
			}
			arg0->unk5C = 1;
			break;
			
		case 1:
			arg0->unk48 += 2.0f;
			if(arg0->unk48 > 180.0f) {
				arg0->unk54 = 3;
			}
			arg0->unk40[0] = 0;
			arg0->unk34.x = fn_1_883C(arg0->unk34.x, 40, 0.1);
			arg0->unk34.y = fn_1_883C(arg0->unk34.y, -arg0->unk30, 0.1);
			temp_f23 = cosd(arg0->unk48*0.5f);
			temp_f31 = (-100*temp_f23)+110;
			temp_f30 = fn_1_6888();
			temp_f28 = temp_f26*temp_f31;
			temp_f27 = temp_f25*temp_f31;
			temp_f29 = temp_f30;
			arg0->unk24.x = temp_f28;
			arg0->unk24.y = temp_f30;
			arg0->unk24.z = temp_f27;
			arg0->unk5C = 0;
			break;
			
		case 3:
			arg0->unk5C = 1;
			arg0->unk54 = 4;
			arg0->unk50 = 0;
			Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			break;
			
		case 4:
			break;
	}
	if(arg0->unk34.y > 360) {
		arg0->unk34.y -= 360;
	} else if(arg0->unk34.y  < 0) {
		arg0->unk34.y += 360;
	}
	sp8 = 0;
	temp_f22 = -cosd(arg0->unk34.x)*5;
	temp_f24 = -sind(arg0->unk34.x)*5;
	temp_f21 = temp_f24*sind(arg0->unk34.y);
	temp_f20 = temp_f22;
	temp_f19 = temp_f24*cosd(arg0->unk34.y);
	arg0->unkC.x = temp_f21+temp_f28;
	arg0->unkC.y = temp_f20+temp_f29;
	arg0->unkC.z = temp_f19+temp_f27;
}

void fn_1_13D88(StructBssDA4 *arg0)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	arg0->unk30 += 3.0f;
	if(arg0->unk30 > 360.0f) {
		arg0->unk30 -= 360.0f;
	}
	temp_f31 = cosd(arg0->unk30);
	temp_f30 = sind(arg0->unk30);
	temp_f29 = fn_1_6888();
	arg0->unk34.y = (90+(-arg0->unk30))+180+90;
	arg0->unkC.x = 1.5f*(10.0f*temp_f31)+arg0->unk18.x;
	arg0->unkC.z = 1.5f*(10.0f*temp_f30)+arg0->unk18.z;
	arg0->unk24.x = arg0->unkC.x;
	arg0->unk24.y = arg0->unkC.y+5;
	arg0->unk24.z = arg0->unkC.z;
	if(arg0->unkC.y > 5.0f+temp_f29) {
		arg0->unk5C = 1;
	} else {
		arg0->unk5C = 0;
	}
	if(arg0->unk5C == 1 && arg0->unkC.y-15.0f > Center.y+CZoom) {
		arg0->unk50 = 0;
		Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
	}
	if(arg0->unk34.y  > 360.0f) {
		arg0->unk34.y -= 360.0f;
	} else if(arg0->unk34.y  < 0.0f) {
		arg0->unk34.y += 360.0f;
	}
	arg0->unk34.x = fn_1_883C(arg0->unk34.x, -35, 0.1f);
}

void fn_1_1406C(StructBssDA4 *arg0)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	float temp_f27;
	float temp_f26;
	float temp_f25;
	float temp_f24;
	float temp_f23;
	float temp_f22;
	float temp_f21;
	temp_f30 = 1;
	temp_f26 = fn_1_6888();
	switch(arg0->unk54) {
		case 0:
			temp_f29 = cosd(arg0->unk30);
			temp_f28 = sind(arg0->unk30);
			arg0->unkC.x = temp_f29*(80.0f-(10.0f*temp_f30));
			arg0->unkC.z = temp_f28*(80.0f-(10.0f*temp_f30))*0.7f;
			temp_f24 = temp_f26;
			if(arg0->unkC.y > temp_f24) {
				arg0->unk54 = 1;
				arg0->unk18.x = arg0->unkC.x;
				arg0->unk18.z = arg0->unkC.z;
			}
			arg0->unk5C = 1;
			arg0->unk48 = 0;
			break;
			
		case 1:
			arg0->unk48 += 1.5f;
			if(arg0->unk48 > 180.0f) {
				arg0->unk54 = 3;
				Hu3DMotionSpeedSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			}
			
			temp_f31 = 180+arg0->unk30;
			if(temp_f31 > 360.0f) {
				temp_f31 -= 360.0f;
			}
			temp_f29 = cosd(temp_f31);
			temp_f28 = sind(temp_f31);
			temp_f25 = cosd(arg0->unk48*0.5f);
			temp_f27 = 180.0f;
			temp_f30 = temp_f27+(temp_f25*(-temp_f27));
			temp_f23 = arg0->unk18.x+(temp_f29*temp_f30);
			temp_f21 = arg0->unk18.z+(temp_f28*temp_f30);
			temp_f22 = temp_f26;
			arg0->unkC.x = temp_f23;
			arg0->unkC.y = temp_f22;
			arg0->unkC.z = temp_f21;
			arg0->unk24.x = arg0->unkC.x;
			arg0->unk24.y = arg0->unkC.y+5;
			arg0->unk24.z = arg0->unkC.z;
			if(arg0->unk34.x < 30.0f) {
				arg0->unk34.x += 4.0f;
			} else {
				arg0->unk34.x = 30.0f;
			}
			Hu3DMotionSpeedSet(lbl_1_bss_75A8->model[arg0->unk4], 2);
			arg0->unk5C = 0;
			break;
			
		case 3:
			Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			arg0->unk5C = 1;
			arg0->unk50 = 0;
			arg0->unk54++;
			break;
			
		case 4:
			break;
	}
}

void fn_1_144D0(StructBssDA4 *arg0)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	float temp_f27;
	float temp_f26;
	float temp_f25;
	float temp_f24;
	float temp_f23;
	float temp_f22;
	float temp_f21;
	float temp_f20;
	float temp_f19;
	float temp_f18;
	float spC;
	float sp8;
	
	arg0->unk30 += 2.0f;
	if(arg0->unk30 > 360.0f) {
		arg0->unk30 -= 360.0f;
	}
	switch(arg0->unk54) {
		case 0:
			arg0->unk5C = 1;
			temp_f31 = cosd(arg0->unk30);
			temp_f30 = sind(arg0->unk30);
			arg0->unkC.x = 15.0f*temp_f31;
			arg0->unkC.z = 15.0f*temp_f30;
			arg0->unk34.y = -arg0->unk30+90.0f;
			temp_f24 = fn_1_6888();
			temp_f21 = -680.00006f+temp_f24;
			if(arg0->unkC.y > temp_f21) {
				arg0->unk54 = 1;
				arg0->unk60 = 0;
			}
			break;
			
		case 1:
			if(arg0->unk60 < 102.0f) {
				arg0->unk60++;
				temp_f27 = arg0->unk60/102.0f;
				temp_f29 = 15+(35*temp_f27);
				temp_f22 = 90*temp_f27;
				temp_f31 = cosd(arg0->unk30);
				temp_f30 = sind(arg0->unk30);
				arg0->unkC.x = temp_f31*temp_f29;
				arg0->unkC.z = temp_f30*temp_f29;
				arg0->unk34.y = (-arg0->unk30+90.0f)-temp_f22;
			} else {
				arg0->unk54 = 2;
				arg0->unk60 = 0;
				Hu3DMotionSpeedSet(lbl_1_bss_75A8->model[arg0->unk4], 2);
			}
			break;
			
		case 2:
			temp_f31 = cosd(arg0->unk30);
			temp_f30 = sind(arg0->unk30);
			temp_f24 = fn_1_6888();
			temp_f26 = 50*temp_f31;
			temp_f28 = temp_f24;
			temp_f25 = 50*temp_f30;
			arg0->unkC.x = temp_f26;
			arg0->unkC.y = temp_f28;
			arg0->unkC.z = temp_f25;
			if(arg0->unk34.x < 30.0f) {
				arg0->unk34.x += 4.0f;
			} else {
				arg0->unk34.x = 30.0f;
			}
			arg0->unk34.y = (-arg0->unk30+90.0f)-90.0f;
			if(arg0->unk60 < 180.0f) {
				arg0->unk60++;
			} else {
				arg0->unk54 = 3;
				arg0->unk60 = 0;
				arg0->unk18.y = temp_f28;
				Hu3DMotionSpeedSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			}
			arg0->unk24.x = temp_f26;
			arg0->unk24.y = 5.0f+temp_f28;
			arg0->unk24.z = temp_f25;
			arg0->unk5C = 0;
			break;
			
		case 3:
			if(arg0->unk60 < 150.0f) {
				arg0->unk60++; 
			} else {
				arg0->unk54 = 4;
				Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			}
			temp_f27 = 0;
			temp_f29 = 50+(40*temp_f27);
			temp_f31 = cosd(arg0->unk30);
			temp_f30 = sind(arg0->unk30);
			temp_f26 = temp_f31*temp_f29;
			temp_f28 = arg0->unk18.y;
			temp_f25 = temp_f30*temp_f29;
			spC = 0;
			temp_f20 = -cosd(arg0->unk34.x)*5;
			temp_f23 = -sind(arg0->unk34.x)*5;
			temp_f19 = temp_f23*sind(arg0->unk34.y);
			temp_f18 = temp_f20;
			sp8 = temp_f23*cosd(arg0->unk34.y);
			arg0->unkC.x = temp_f19+temp_f26;
			arg0->unkC.y = temp_f18+temp_f28;
			arg0->unkC.z = sp8+temp_f25;
			if(arg0->unk34.y > 360.0f) {
				arg0->unk34.y -= 360.0f;
			}
			arg0->unk34.y = (-arg0->unk30+90.0f)-90.0f;
			arg0->unk5C = 1;
			break;
			
		case 4:
			if(arg0->unk5C == 1 && arg0->unkC.y-15.0f > Center.y+CZoom) {
				arg0->unk50 = 0;
				Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			}
			break;
	}
	if(arg0->unk34.y > 360.0f) {
		arg0->unk34.y -= 360.0f;
	} else if(arg0->unk34.y < 0.0f) {
		arg0->unk34.y += 360.0f;
	}
}

void fn_1_14DB4(StructBssDA4 *arg0)
{
	s32 temp_r30;
	float temp_f31;
	float temp_f30;
	float temp_f29;
	temp_f30 = cosd(arg0->unk30);
	temp_f29 = sind(arg0->unk30);
	arg0->unkC.x = 32.0f*temp_f30;
	arg0->unkC.z = 32.0f*temp_f29;
	temp_f31 = fn_1_6888();
	switch(arg0->unk54) {
		case 0:
			if(arg0->unkC.y > temp_f31) {
				arg0->unk54 = 1;
				arg0->unk60 = 0;
			}
			arg0->unk34.x += 4.0f;
			arg0->unk5C = 1;
			break;
			
		case 1:
			arg0->unk5C = 0;
			if(arg0->unk58) {
				arg0->unk5C = 1;
				arg0->unk54 = 4;
				arg0->unk60 = 0;
				temp_r30 = lbl_1_bss_75A8->model[arg0->unk8];
				Hu3DModelAttrReset(temp_r30, 1);
				fn_1_15B50(temp_r30);
				fn_1_155E0(temp_r30, 1);
				fn_1_15618(temp_r30, arg0->unkC.x, arg0->unkC.y, arg0->unkC.z);
				HuAudFXPlay(7);
			} else {
				if(arg0->unk60 < 72.0f) {
					arg0->unk60++;
					arg0->unkC.y = temp_f31;
				} else {
					arg0->unk54 = 3;
				}
				arg0->unk34.x += 8.0f;
				arg0->unk34.y += 8.0f;
			}
			break;
			
		case 3:
			arg0->unk34.x += 4.0f;
			arg0->unk5C = 1;
			break;
			
		case 4:
			if(arg0->unk60 < 30.0f) {
				arg0->unk34.x = 90;
				arg0->unk34.y += 32.0f;
				if(arg0->unk60 > 5) {
					fn_1_155E0(lbl_1_bss_75A8->model[arg0->unk8], 0);
				}
				arg0->unk4C *= 0.8f;
				arg0->unk60++;
			} else {
				arg0->unk50 = 0;
				Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			}
			break;
	}
	if(arg0->unk34.x > 360.0f) {
		arg0->unk34.x  -= 360.0f;
	}
	if(arg0->unk34.y > 360.0f) {
		arg0->unk34.y  -= 360.0f;
	}
	arg0->unk24.x = arg0->unkC.x;
	arg0->unk24.y = arg0->unkC.y;
	arg0->unk24.z = arg0->unkC.z;
}

void fn_1_151A4(StructBssDA4 *arg0)
{
	s32 temp_r30;
	float temp_f31;
	float temp_f30;
	float temp_f29;
	
	arg0->unk48 += 6.0000005f;
	if(arg0->unk48 >= 360.0f) {
		arg0->unk48 -= 360.0f;
	}
	arg0->unk34.z = 30*sind(arg0->unk48);
	temp_f30 = cosd(arg0->unk30);
	temp_f29 = sind(arg0->unk30);
	arg0->unkC.x = 32.0f*temp_f30;
	arg0->unkC.z = 32.0f*temp_f29;
	temp_f31 = fn_1_6888();
	switch(arg0->unk54) {
		case 0:
			if(arg0->unkC.y > temp_f31) {
				arg0->unk54 = 1;
				arg0->unk60 = 0;
			}
			arg0->unk34.x = -45;
			arg0->unk34.y = 0;
			arg0->unk5C = 1;
			break;
			
		case 1:
			arg0->unk5C = 0;
			if(arg0->unk58) {
				arg0->unk5C = 1;
				arg0->unk54 = 4;
				arg0->unk60 = 0;
				temp_r30 = lbl_1_bss_75A8->model[arg0->unk8];
				Hu3DModelAttrReset(temp_r30, 1);
				fn_1_15B50(temp_r30);
				fn_1_155E0(temp_r30, 1);
				fn_1_15618(temp_r30, arg0->unkC.x, arg0->unkC.y, arg0->unkC.z);
				HuAudFXPlay(19);
			} else {
				if(arg0->unk60 < 72.0f) {
					arg0->unk60++;
					arg0->unkC.y = temp_f31;
				} else {
					arg0->unk54 = 3;
				}
				
			}
			break;
			
		case 3:
			arg0->unk5C = 1;
			break;
			
		case 4:
			if(arg0->unk60 < 30.0f) {
				arg0->unk34.x = 90;
				arg0->unk34.y += 32.0f;
				if(arg0->unk60 > 5) {
					fn_1_155E0(lbl_1_bss_75A8->model[arg0->unk8], 0);
				}
				arg0->unk4C *= 0.8f;
				arg0->unk60++;
			} else {
				arg0->unk50 = 0;
				Hu3DModelAttrSet(lbl_1_bss_75A8->model[arg0->unk4], 1);
			}
			break;
	}
	if(arg0->unk34.x > 360.0f) {
		arg0->unk34.x  -= 360.0f;
	}
	if(arg0->unk34.y > 360.0f) {
		arg0->unk34.y  -= 360.0f;
	}
	arg0->unk24.x = arg0->unkC.x;
	arg0->unk24.y = arg0->unkC.y;
	arg0->unk24.z = arg0->unkC.z;
}

void fn_1_155E0(s16 arg0, s16 arg1)
{
	ModelData *temp_r31;
	ParticleData *temp_r30;
	temp_r31 = &Hu3DData[arg0];
	temp_r30 = temp_r31->unk_120;
	temp_r30->unk_00 = arg1;
}

void fn_1_15618(s16 arg0, float arg1, float arg2, float arg3)
{
	ParticleData *temp_r31;
	ModelData *temp_r30;
	temp_r30 = &Hu3DData[arg0];
	temp_r31 = temp_r30->unk_120;
	temp_r31->unk_04.x = arg1;
	temp_r31->unk_04.y = arg2;
	temp_r31->unk_04.z = arg3;
}

void fn_1_15658(ModelData *model, ParticleData *particle, Mtx matrix)
{
	float temp_f31;
	float temp_f30;
	HsfanimStruct01 *temp_r31;
	u32 temp_r29;
	s32 temp_r28;
	s16 temp_r27;
	GXColor *temp_r26;
	if(particle->unk_34 == 0) {
		temp_f31 = 90;
		particle->unk_02 = 0;
		particle->unk_10.y = 3;
		temp_r31 = particle->unk_48;
		for(temp_r28=0; temp_r28<particle->unk_30; temp_r28++, temp_r31++) {
			temp_r31->unk2C = 0;
			temp_r31->unk40.a = 0;
		}
	}
	if(particle->unk_00) {
		particle->unk_02--;
		if(particle->unk_02 <= 0.0f) {
			particle->unk_02 = 2;
			temp_r27 = 4;
			temp_r31 = particle->unk_48;
			for(temp_r28=0; temp_r28<particle->unk_30; temp_r28++, temp_r31++) {
				if(temp_r31->unk2C != 0) {
					continue;
				}
				temp_r31->unk34.x = particle->unk_04.x;
				temp_r31->unk34.y = particle->unk_04.y;
				temp_r31->unk34.z = particle->unk_04.z;
				temp_f30 = frandmod(360);
				temp_r29 = frandmod(12);
				temp_r29 += 4.0f;
				temp_r31->unk34.x = temp_r31->unk34.x+(temp_r29*sind(temp_f30));
				temp_r31->unk34.z = temp_r31->unk34.z+(temp_r29*cosd(temp_f30));
				temp_r31->unk20 = 0;
				temp_r31->unk24 = particle->unk_10.y;
				temp_r29 = 1;
				if(temp_r29 == 1) {
					temp_r31->unk14.x = 0.97643f;
				} else {
					temp_r31->unk14.x = 0.96666664f;
				}
				temp_r31->unk00 = 60;
				temp_r31->unk2C = 8;
				temp_r29 = frand()&0x1;
				temp_r26 = &lbl_1_data_4F4[temp_r29];
				temp_r31->unk40.r = temp_r26->r;
				temp_r31->unk40.g = temp_r26->g;
				temp_r31->unk40.b = temp_r26->b;
				temp_r31->unk40.a = 0;
				temp_r31->unk02 = temp_r29;
				temp_r27--;
				if(temp_r27 == 0) {
					break;
				}
			}
		}
	}
	temp_r27 = 0;
	temp_r31 = particle->unk_48;
	for(temp_r28=0; temp_r28<particle->unk_30; temp_r28++, temp_r31++) {
		if(temp_r31->unk2C == 0) {
			continue;
		}
		temp_r27++;
		temp_r31->unk34.y -= 4.0f;
		temp_f31 = 1.0+cosd(temp_r31->unk20);
		temp_f31 *= 0.5f;
		temp_r31->unk40.a = temp_f31*255;
		temp_r31->unk20 += temp_r31->unk24;
		temp_r31->unk30 = temp_r31->unk20;
		temp_r31->unk2C *= temp_r31->unk14.x;
		temp_r31->unk02 ^= 0x3;
		if(temp_r31->unk02 & 0x1) {
			temp_r31->unk40.b = 0;
			temp_r31->unk40.g = 200;
		} else {
			temp_r31->unk40.b = 200;
			temp_r31->unk40.g = 200;
		}
		if(temp_r31->unk02 & 0x2) {
			temp_r29 = temp_r31->unk40.a+64;
			if(temp_r29 > 255) {
				temp_r29 -= 128;
			}
			temp_r31->unk40.a = temp_r29;
		}
		temp_r31->unk00_s16--;
		if(temp_r31->unk00_s16 <= 0) {
			temp_r31->unk2C = 0;
		}
	}
	DCStoreRange(particle->unk_48, particle->unk_30*sizeof(HsfanimStruct01));
	if(particle->unk_00 == 0 && temp_r27 == 0) {
		model->attr |= 0x1;
	}
}

void fn_1_15B50(s16 arg0)
{
	ParticleData *temp_r31;
	HsfanimStruct01 *temp_r30;
	s32 temp_r29;
	ModelData *temp_r28 = &Hu3DData[arg0];
	temp_r31 = temp_r28->unk_120;
	temp_r31->unk_34 = 0;
	temp_r30 = temp_r31->unk_48;
	for(temp_r29=0; temp_r29<temp_r31->unk_30; temp_r29++, temp_r30++) {
		temp_r30->unk2C = 0;
	}
}

void fn_1_15CA4(omObjData *object);
void fn_1_15D64(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_1_15BCC(omObjData *object)
{
	s16 temp_r30;
	s32 temp_r29;
	omSetStatBit(object, 0x100);
	for(temp_r29=0; temp_r29<4; temp_r29++) {
		temp_r30 = Hu3DParticleCreate(HuSprAnimReadFile(0x270019), 9);
		object->model[temp_r29] = temp_r30;
		Hu3DModelAttrSet(temp_r30, 1);
		Hu3DModelLayerSet(temp_r30, 7);
		Hu3DParticleColSet(temp_r30, 255, 255, 255);
		Hu3DParticleHookSet(temp_r30, fn_1_15D64);
	}
	object->work[0] = -1;
	object->func = fn_1_15CA4;
}

void fn_1_15CA4(omObjData *object)
{
	s32 temp_r31;
	s16 temp_r29;
	ModelData *temp_r28;
	ParticleData *temp_r27;
	temp_r31 = object->work[0];
	if(temp_r31 <= -1) {
		return;
	}
	object->work[0] = -1;
	temp_r29 = object->model[temp_r31];
	temp_r28 = &Hu3DData[temp_r29];
	temp_r27 = temp_r28->unk_120;
	Hu3DModelAttrReset(temp_r29, 1);
	Hu3DModelPosSet(temp_r29, lbl_1_bss_D6C[temp_r31].x, lbl_1_bss_D6C[temp_r31].y, lbl_1_bss_D6C[temp_r31].z);
	temp_r27->unk_34 = 0;
	
}

void fn_1_15D64(ModelData *model, ParticleData *particle, Mtx matrix)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	HsfanimStruct01 *temp_r31;
	s32 temp_r29;
	u32 temp_r28;
	s16 temp_r27;
	s16 temp_r26;
	if(particle->unk_34 == 0) {
		temp_f31 = 72;
		particle->unk_00 = 1;
		particle->unk_02 = 0;
		particle->unk_10.y = 22.5f;
		temp_r31 = particle->unk_48;
		for(temp_r29=0; temp_r29<particle->unk_30; temp_r29++, temp_r31++) {
			temp_r31->unk2C = 0;
			temp_r31->unk40.a = 0;
		}
	}
	if(particle->unk_00) {
		particle->unk_00 = 0;
		particle->unk_02--;
		if(particle->unk_02 <= 0.0f) {
			particle->unk_02 =30;
			temp_r31 = particle->unk_48;
			temp_r26 = -1;
			temp_r27 = 0;
			for(temp_r29=0; temp_r29<particle->unk_30; temp_r29++, temp_r31++) {
				if(temp_r31->unk2C != 0) {
					continue;
				}
				if(temp_r27 <= 0) {
					temp_r26++;
					if(temp_r26 >= 3) {
						break;
					}
					temp_f30 = lbl_1_data_514[temp_r26];
					temp_f28 = lbl_1_data_508[temp_r26];
					temp_f29 = lbl_1_data_520[temp_r26];
					temp_r27 = lbl_1_data_504[temp_r26];
				}
				temp_r27--;
				temp_r31->unk34.x = temp_r31->unk34.y = temp_r31->unk34.z = 0;
				if(90.0f == temp_f29) {
					temp_r31->unk08.z = 5;
					temp_r31->unk08.x = temp_r31->unk08.y = 0;
				} else {
					temp_f31 = 5*cosd(temp_f29);
					temp_r31->unk08.z = 5.0*sind(temp_f29);
					temp_r31->unk08.x = temp_f31*sind(temp_f30);
					temp_r31->unk08.y = temp_f31*cosd(temp_f30);
				}
				temp_r31->unk20 = 0;
				temp_r31->unk24 = particle->unk_10.y;
				temp_r28 = 1;
				temp_r31->unk00 = 8;
				temp_r31->unk2C = 10;
				temp_r31->unk14.x = 1.125f;
				temp_r28 = frand()&0x1;
				temp_r31->unk02 = temp_r28;
				temp_r31->unk40.r = 255;
				temp_r31->unk40.g = 255;
				temp_r31->unk40.b = 255;
				temp_r31->unk40.a = 0;
				if(temp_r28) {
					temp_r31->unk40.b = 0;
					temp_r31->unk40.g = 0;
				}
				temp_f30 += temp_f28;
			}
		}
	}
	temp_r27 = 0;
	temp_r31 = particle->unk_48;
	for(temp_r29=0; temp_r29<particle->unk_30; temp_r29++, temp_r31++) {
		if(temp_r31->unk2C == 0) {
			continue;
		}
		temp_r27++;
		VECAdd(&temp_r31->unk08, &temp_r31->unk34, &temp_r31->unk34);
		temp_f31 = 1.0+cosd(temp_r31->unk20);
		temp_f31 *= 0.45f;
		temp_r31->unk40.a = temp_f31*255;
		temp_r31->unk20 += temp_r31->unk24;
		temp_r31->unk2C -= temp_r31->unk14.x;
		temp_r31->unk02 ^= 0x3;
		if(temp_r31->unk02 & 0x1) {
			temp_r31->unk40.b = 0;
			temp_r31->unk40.g = 100;
		} else {
			temp_r31->unk40.b = 0;
			temp_r31->unk40.g = 200;
		}
		if(temp_r31->unk02 & 0x2) {
			temp_r28 = temp_r31->unk40.a+64;
			if(temp_r28 > 255) {
				temp_r28 -= 128;
			}
			temp_r31->unk40.a = temp_r28;
		}
		temp_r31->unk00_s16--;
		if(temp_r31->unk00_s16 <= 0) {
			temp_r31->unk2C = 0;
		}
	}
	DCStoreRange(particle->unk_48, particle->unk_30*sizeof(HsfanimStruct01));
	if(particle->unk_00 == 0 && temp_r27 == 0) {
		model->attr |= 0x1;
	}
}

s32 fn_1_162CC(Vec *arg0, Vec *arg1)
{
	Vec spC;
	s32 temp_r31;
	float temp_f31;
	float temp_f30;
	temp_f30 = 1000;
	if(!lbl_1_bss_168) {
		return 0;
	}
	for(temp_r31=0; temp_r31<lbl_1_bss_168; temp_r31++) {
		VECSubtract(&lbl_1_bss_16C[temp_r31], arg0, &spC);
		temp_f31 = VECMag(&spC);
		if(temp_f31 < temp_f30) {
			temp_f30 = temp_f31;
			*arg1 = lbl_1_bss_16C[temp_r31];
		}
	}
	return 1;
}