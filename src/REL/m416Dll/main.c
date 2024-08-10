#include "game/object.h"
#include "game/objsub.h"
#include "game/hsfman.h"
#include "game/hsfanim.h"
#include "game/hsfmotion.h"
#include "game/audio.h"
#include "game/wipe.h"
#include "game/sprite.h"
#include "game/chrman.h"
#include "game/pad.h"
#include "game/gamework_data.h"
#include "game/minigame_seq.h"
#include "game/frand.h"

#include "math.h"
#include "ext_math.h"


#include "REL/m416Dll.h"

#include "rel_sqrt_consts.h"

typedef struct camera_view_params {
	float zoom;
	Vec pos;
	Vec rot;
} CameraViewParams;

CameraViewParams lbl_1_data_0[2] = {
	{ 1676.6, { 0, 172, 123 }, { -18, 0, 0 } },
	{ 1200, { 0, 0, -600 }, { -24, 0, 0 } }
};

GXColor lbl_1_data_38 = { 255, 255, 255, 255 };
GXColor lbl_1_data_3C = { 255, 160, 96, 255 };

typedef struct struct_bss_14 {
	float unk0;
	float unk4;
	u8 unk8;
	float unkC;
} StructBss14;

s32 lbl_1_bss_960;
s16 lbl_1_bss_95C;
omObjData *lbl_1_bss_958;
omObjData *lbl_1_bss_954;
omObjData *lbl_1_bss_950;
omObjData *lbl_1_bss_930[2][4];
s16 lbl_1_bss_92E;
s16 lbl_1_bss_92A[2];
s16 lbl_1_bss_928;
s16 lbl_1_bss_926;
s16 lbl_1_bss_924;
float lbl_1_bss_920;
s16 lbl_1_bss_91A[2];
s16 lbl_1_bss_918;
AnimData *lbl_1_bss_914;
StructBss14 lbl_1_bss_14[12][12];
s16 lbl_1_bss_12;
s16 lbl_1_bss_10;
s32 lbl_1_bss_4[3];
s32 lbl_1_bss_0;

void fn_1_458(omObjData *object);
void fn_1_4FC(omObjData *object);

void fn_1_1260(Process *objman);
void fn_1_6E5C(omObjData *object);

void ObjectSetup(void)
{
	Process *objman;
	Vec pos;
	Vec up;
	Vec target;
	OSReport("******* M416ObjectSetup *********\n");
	objman = omInitObjMan(50, 8192);
	omGameSysInit(objman);
	Hu3DCameraCreate(1);
	Hu3DCameraPerspectiveSet(1, 30, 20, 25000, 1.2);
	Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
	lbl_1_bss_950 = omAddObjEx(objman, 32730, 0, 0, -1, omOutView);
	lbl_1_bss_958 = omAddObjEx(objman, 0, 0, 0, -1, fn_1_458);
	fn_1_1260(objman);
	lbl_1_bss_954 = omAddObjEx(objman, 10, 0, 0, -1, fn_1_6E5C);
	pos.x = 0;
	pos.y = 3000;
	pos.z  = 1;
	up.x = 0;
	up.y = 1;
	up.z = 0;
	target.x = 0;
	target.y = 0;
	target.z = 0;
	Hu3DShadowCreate(30, 20, 25000);
	Hu3DShadowTPLvlSet(0.9f);
	Hu3DShadowPosSet(&pos, &up, &target);
	Hu3DLightAllKill();
	lbl_1_bss_91A[0] = Hu3DGLightCreate(-700, 1200, 700, 0, -0.5, -1, lbl_1_data_38.r, lbl_1_data_38.g, lbl_1_data_38.b);
	Hu3DGLightStaticSet(lbl_1_bss_91A[0], 1);
	Hu3DGLightInfinitytSet(lbl_1_bss_91A[0]);
	lbl_1_bss_91A[1] = Hu3DGLightCreate(0, 0, 0, 0, 0, 0, 0, 0, 0);
	Hu3DGLightStaticSet(lbl_1_bss_91A[1], 1);
	Hu3DGLightPointSet(lbl_1_bss_91A[1], 0, 0, 3);
	lbl_1_bss_918 = 0;
	HuAudSndGrpSet(41);
	Hu3DBGColorSet(0, 0, 0);
	fn_1_79D0(objman);
}

void fn_1_458(omObjData *object)
{
	lbl_1_bss_928 = 30;
	lbl_1_bss_926 = 60;
	fn_1_1250(0);
	lbl_1_bss_924 = -1;
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
	lbl_1_bss_920 = 1;
	fn_1_8FF4(1);
	object->func = fn_1_4FC;
}

typedef struct bss_930_work_4c {
	u8 field_0_bit0 : 1;
	float unk4;
	float unk8;
	float unkC;
	s16 unk10;
} Bss930Work4C;

typedef struct bss_930_work {
	 u8 field_0_bit0 : 1;
	 u8 field_0_bit1 : 1;
	 u8 field_0_bit2 : 1;
	 u8 field_0_bit3 : 1;
	 u8 field_0_bit4 : 1;
	 s16 unk02;
	 s16 unk04;
	 s8 unk06;
	 s8 unk07;
	 u16 unk08;
	 u16 unk0A;
	 s16 unk0C;
	 s16 unk0E;
	 s16 unk10;
	 s16 unk12;
	 s16 unk14;
	 float unk18;
	 Vec unk1C;
	 s32 unk28;
	 s32 unk2C;
	 u32 unk30;
	 u32 unk34;
	 float unk38;
	 u32 unk3C;
	 s16 unk40;
	 s16 unk42;
	 s16 unk44;
	 s16 unk46;
	 omObjFunc unk48;
	 Bss930Work4C *unk4C;
	 s16 unk50;
	 Vec unk54;
	 s16 unk60;
	 Vec unk64;
	 s16 unk70;
	 Vec unk74;
	 float unk80;
	 float unk84;
} Bss930Work;

s32 lbl_1_data_64 = -1;

void fn_1_11E8(omObjData *object);
s32 fn_1_14E8(void);
void fn_1_52BC(void);

void fn_1_4FC(omObjData *object)
{
	Bss930Work *temp_r31;
	s32 temp_r30;
	s16 temp_r29;
	Vec sp1C;
	Vec sp10;
	s16 sp8[4];
	
	switch(fn_1_1240()) {
		case 0:
			if(!WipeStatGet()) {
				HuAudFXPlay(1471);
				fn_1_1250(1);
				lbl_1_bss_95C = 30;
			}
			break;
			
		case 1:
			if(--lbl_1_bss_95C == 0) {
				fn_1_1250(2);
				lbl_1_bss_95C = 84;
			}
			break;
			
		case 2:
			if(lbl_1_bss_95C) {
				if(--lbl_1_bss_95C == 0) {
					HuAudFXPlay(1470);
				}
			} else {
				if(lbl_1_bss_920 > 0) {
					lbl_1_bss_920 -= 0.020000001f;
					if(lbl_1_bss_920 < 0) {
						lbl_1_bss_920 = 0;
					}
					Hu3DGLightColorSet(lbl_1_bss_91A[0], lbl_1_data_38.r*lbl_1_bss_920, lbl_1_data_38.g*lbl_1_bss_920, lbl_1_data_38.b*lbl_1_bss_920, 255);
				}
				if(lbl_1_bss_920 < 0.1f) {
					if(lbl_1_bss_0 == 0) {
						temp_r31 = lbl_1_bss_930[0][0]->data;
						HuAudCharVoicePlay(temp_r31->unk0C, 296);
						lbl_1_bss_0 = 1;
					}
				}
				if(lbl_1_bss_920 <= 0.0f) {
					fn_1_1250(3);
					lbl_1_bss_95C = 60;
				}
			}
			break;
			
		case 3:
			if(--lbl_1_bss_95C == 0) {
				fn_1_1250(4);
				lbl_1_bss_95C = 60;
				Hu3DGLightColorSet(lbl_1_bss_91A[1], lbl_1_data_3C.r, lbl_1_data_3C.g, lbl_1_data_3C.b, lbl_1_data_3C.a);
				fn_1_8FF4(0.0625f);
				Hu3DShadowData.unk_08.x = 135;
				MTXLightPerspective(Hu3DShadowData.unk_68, Hu3DShadowData.unk_08.x, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
				lbl_1_bss_918 = 1;
				HuAudFXEmiterPlay(1464, &lbl_1_bss_930[0][0]->trans);
			}
			break;
			
		case 4:
			if(--lbl_1_bss_95C == 0) {
				fn_1_1250(5);
				lbl_1_bss_12 = MGSeqStartCreate();
			}
			break;
			
		case 5:
			if(MGSeqStatGet(lbl_1_bss_12) == 0) {
				lbl_1_bss_10 = MGSeqTimerCreate(30);
				fn_1_1250(6);
			}
			if(lbl_1_data_64 < 0 && (MGSeqStatGet(lbl_1_bss_12) & 0x10)) {
				lbl_1_data_64 = HuAudSeqPlay(73);
			}
			break;
			
		case 6:
			if(--lbl_1_bss_926 == 0) {
				lbl_1_bss_928--;
				MGSeqParamSet(lbl_1_bss_10, 1, lbl_1_bss_928);
				lbl_1_bss_926 = 60;
			}
			if(lbl_1_bss_928 == 0 || lbl_1_bss_924 >= 0) {
				lbl_1_bss_12 = MGSeqFinishCreate();
				fn_1_1250(7);
				HuAudSeqAllFadeOut(100);
			}
			break;
			
		case 7:
			if(lbl_1_bss_10 >= 0) {
				MGSeqParamSet(lbl_1_bss_10, 2, -1);
				lbl_1_bss_10 = -1;
			}
			if(MGSeqStatGet(lbl_1_bss_12) == 0) {
				lbl_1_bss_95C = 60;
				fn_1_1250(8);
			}
			break;
			
		case 8:
			if(lbl_1_bss_95C) {
				if(--lbl_1_bss_95C == 0) {
					Hu3DShadowData.unk_08.x = 30;
					MTXLightPerspective(Hu3DShadowData.unk_68, Hu3DShadowData.unk_08.x, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
					lbl_1_bss_918 = 0;
					sp1C.x = 0;
					sp1C.y = 3000;
					sp1C.z = 1;
					sp10.x = 0;
					sp10.y = 0;
					sp10.z = 0;
					Hu3DShadowPosSet(&sp1C, &Hu3DShadowData.unk_2C, &sp10);
					HuAudFXPlay(1470);
				}
			} else {
				lbl_1_bss_920 += 0.020000001f;
				if(lbl_1_bss_920 >= 1.0f) {
					lbl_1_bss_920 = 1.0f;
					fn_1_1250(9);
					lbl_1_bss_95C = 60;
					fn_1_52BC();
				}
				fn_1_8FF4(lbl_1_bss_920);
				Hu3DGLightColorSet(lbl_1_bss_91A[0], lbl_1_data_38.r*lbl_1_bss_920, lbl_1_data_38.g*lbl_1_bss_920, lbl_1_data_38.b*lbl_1_bss_920, 255);
				if(lbl_1_bss_91A[1] >= 0) {
					Hu3DGLightColorSet(lbl_1_bss_91A[1], lbl_1_data_3C.r*(1.0f-lbl_1_bss_920), lbl_1_data_3C.g*(1.0f-lbl_1_bss_920), lbl_1_data_3C.b*(1.0f-lbl_1_bss_920), lbl_1_data_3C.a*(1.0f-lbl_1_bss_920));
				}
			}
			break;
			
		case 9:
			if(fn_1_14E8()) {
				if(--lbl_1_bss_95C == 0) {
					fn_1_1250(10);
					lbl_1_bss_95C = 210;
					for(temp_r30=0; temp_r30<4; temp_r30++) {
						sp8[temp_r30] = -1;
					}
					temp_r29 = 0;
					if(lbl_1_bss_924 < 0) {
						temp_r31 = lbl_1_bss_930[0][0]->data;
						sp8[temp_r29++] = temp_r31->unk0C;
						GWPlayerCoinWinSet(temp_r31->unk02, 10);
					} else {
						for(temp_r30=0; temp_r30<3; temp_r30++) {
							temp_r31 = lbl_1_bss_930[1][temp_r30]->data;
							sp8[temp_r29++] = temp_r31->unk0C;
							GWPlayerCoinWinSet(temp_r31->unk02, 10);
						}
					}
					lbl_1_bss_12  = MGSeqWinCreate(sp8[0], sp8[1], sp8[2], sp8[3]);
					HuAudSStreamPlay(1);
				}
			}
			break;
			
		case 10:
			if(--lbl_1_bss_95C == 0) {
				WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
				object->func = fn_1_11E8;
			}
			break;
	}
	if(omSysExitReq && !WipeStatGet()) {
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
		object->func = fn_1_11E8;
	}
	fn_1_8F60(lbl_1_bss_920);
}

void fn_1_11E8(omObjData *object)
{
	if(!WipeStatGet()) {
		MGSeqKillAll();
		HuAudFadeOut(1);
		fn_1_7A54();
		omOvlReturnEx(1, 1);
		OSReport("******* M416Exit *********\n");
	}
}

s32 fn_1_1240(void)
{
	return lbl_1_bss_960;
}

void fn_1_1250(s32 arg0)
{
	lbl_1_bss_960 = arg0;
}

void fn_1_156C(omObjData *object);
void fn_1_2930(omObjData *object);

void fn_1_1260(Process *objman)
{
	s32 i;
	s32 j;
	
	lbl_1_bss_92E = 0;
	lbl_1_bss_92A[0] = lbl_1_bss_92A[1] = 0;
	omMakeGroupEx(objman, 0, 4);
	for(i=0; i<4; i++) {
		omAddObjEx(objman, 5, 5, 50, 0, fn_1_156C);
	}
	lbl_1_bss_914 = HuSprAnimReadFile(0x2F0005);
	memset(lbl_1_bss_14, 0, sizeof(lbl_1_bss_14));
	for(i=0; i<10; i++) {
		for(j=0; j<10; j++) {
			lbl_1_bss_14[i+1][j+1].unk0 = ((0.5f+(j-5))*1100)/9;
			lbl_1_bss_14[i+1][j+1].unk4 = ((0.5f+(i-5))*1100)/9;
		}
	}
	omAddObjEx(objman, 6, 0, 0, -1, fn_1_2930);
}

void fn_1_5D18(omObjData *object);

void fn_1_1480(void)
{
	s32 i;
	omObjData **group;
	group = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
	if(group == NULL) {
		return;
	}
	for(i=0; i<4; i++) {
		fn_1_5D18(group[i]);
	}
}

s32 fn_1_14E8(void)
{
	s32 i;
	omObjData **group;
	group = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
	for(i=0; i<4; i++) {
		Bss930Work *work = group[i]->data;
		if(!work->field_0_bit3) {
			return 0;
		}
	}
	return 1;
}

void fn_1_1964(omObjData *object);
void fn_1_1ADC(omObjData *object);
void fn_1_1D84(omObjData *object);

void fn_1_6AE8(ModelData *model, ParticleData *particle, Mtx matrix);

float lbl_1_data_B0[4][4] = {
	0, 0, -400, 0,
	-340, 0, 200, 155,
	0, 0, 400, 180,
	340, 0, 200, 205
};

void fn_1_156C(omObjData *object)
{
	Bss930Work *work;
	s32 player;
	work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Bss930Work), MEMORY_DEFAULT_NUM);
	object->data = work;
	memset(work, 0, sizeof(Bss930Work));
	work->unk02 = lbl_1_bss_92E++;
	work->unk04 = GWPlayerCfg[work->unk02].pad_idx;
	work->unk0C = GWPlayerCfg[work->unk02].character;
	work->unk0E = GWPlayerCfg[work->unk02].diff;
	work->unk10 = GWPlayerCfg[work->unk02].group;
	object->model[0] = CharModelCreate(work->unk0C, 4);
	Hu3DModelAttrSet(object->model[0], 0x40000001);
	Hu3DModelShadowSet(object->model[0]);
	work->field_0_bit2 = 1;
	work->field_0_bit4 = 1;
	work->unk28 = 0;
	work->unk2C = -1;
	work->unk34 = 0;
	work->unk38 = 50;
	if(!work->unk10) {
		fn_1_1964(object);
		lbl_1_bss_930[0][lbl_1_bss_92A[0]] = object;
		player = lbl_1_bss_92A[0];
		work->unk12 = lbl_1_bss_92A[0];
		lbl_1_bss_92A[0]++;
	} else {
		fn_1_1ADC(object);
		lbl_1_bss_930[1][lbl_1_bss_92A[1]] = object;
		player = lbl_1_bss_92A[1]+1;
		work->unk12 = lbl_1_bss_92A[1];
		lbl_1_bss_92A[1]++;
	}
	Hu3DModelHookSet(object->model[0], "test11_tex_we-itemhook-r", object->model[1]);
	Hu3DModelShadowSet(object->model[1]);
	Hu3DModelLayerSet(object->model[0], 3);
	Hu3DModelLayerSet(object->model[1], 3);
	fn_1_8EB4(object->model[0]);
	fn_1_8EB4(object->model[1]);
	Hu3DMotionSet(object->model[0], object->motion[0]);
	Hu3DModelAttrSet(object->model[0], 0x40000001);
	CharModelMotionIndexSet(work->unk0C, object->motion[1], 0x5F0002);
	CharModelMotionIndexSet(work->unk0C, object->motion[2], 0x5F0002);
	CharModelMotionDataClose(work->unk0C);
	object->model[4] = Hu3DParticleCreate(lbl_1_bss_914, 2);
	Hu3DParticleHookSet(object->model[4], fn_1_6AE8);
	Hu3DParticleBlendModeSet(object->model[4], 1);
	Hu3DModelLayerSet(object->model[4], 6);
	Hu3DModelAttrSet(object->model[4], 1);
	object->trans.x = lbl_1_data_B0[player][0];
	object->trans.y = lbl_1_data_B0[player][1];
	object->trans.z = lbl_1_data_B0[player][2];
	object->rot.y = lbl_1_data_B0[player][3];
	object->rot.x = object->rot.z = 0;
	object->scale.x = object->scale.y = object->scale.z = 1;
	work->unk84 = object->rot.y;
	object->func = fn_1_1D84;
}

u32 lbl_1_data_10C[9][2] = {
	0x002F0008, 1,
	0x002F0010, 1,
	0x002F0018, 1,
	0x002F0020, 1,
	0, 0,
	0x005F0000, 0,
	0x005F0017, 0,
	0x005F0018, 0,
	0x005F0002, 0
};

void fn_1_29DC(omObjData *object);




void fn_1_1964(omObjData *object)
{
	Bss930Work *work;
	s32 i;
	work = object->data;
	for(i=0; i<9; i++) {
		if(!lbl_1_data_10C[i][1]) {
			object->motion[i] = CharModelMotionCreate(work->unk0C, lbl_1_data_10C[i][0]);
		} else {
			object->motion[i] = CharModelMotionCreate(work->unk0C, work->unk0C+lbl_1_data_10C[i][0]);
		}
	}
	object->model[1] = Hu3DModelCreateFile(0x2F0003);
	object->model[2] = Hu3DParticleCreate(HuSprAnimReadFile(0x2F0006), 100);
	Hu3DParticleHookSet(object->model[2], fn_1_613C);
	Hu3DParticleBlendModeSet(object->model[2], 1);
	Hu3DModelLayerSet(object->model[2], 6);
	Hu3DModelAttrSet(object->model[2], 2);
	Hu3DModelAttrSet(object->model[2], 1);
	work->unk44 = 5;
	work->unk48 = fn_1_29DC;
}

void fn_1_2EA4(omObjData *object);
void fn_1_6640(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_6DEC(s16 arg0, u32 arg1);

s32 lbl_1_data_154[9] = {
	0x005F0030,
	0x005F0031,
	0x005F0032,
	0x005F002D,
	0x005F002E,
	0x005F0000,
	0x005F0017,
	0x005F0018,
	0x005F0002
};


void fn_1_1ADC(omObjData *object)
{
	Bss930Work *work;
	s32 i;
	work = object->data;
	for(i=0; i<9; i++) {
		object->motion[i] = CharModelMotionCreate(work->unk0C, lbl_1_data_154[i]);
	}
	object->model[1] = Hu3DModelCreateFile(0x2F0004);
	object->model[2] = Hu3DModelCreateFile(0x2F0002);
	Hu3DModelLayerSet(object->model[2], 3);
	fn_1_6DEC(object->model[2], 16);
	Hu3DModelAttrSet(object->model[2], 1);
	Hu3DMotionSpeedSet(object->model[2], 0);
	Hu3DAnimCreate(HuDataReadNum(0x2F0007, MEMORY_DEFAULT_NUM), object->model[2], "sb00");
	object->model[3] = Hu3DParticleCreate(lbl_1_bss_914, 50);
	Hu3DParticleHookSet(object->model[3], fn_1_6640);
	Hu3DModelLayerSet(object->model[3], 3);
	Hu3DModelAttrSet(object->model[3], 1);
	work->unk4C = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Bss930Work4C), MEMORY_DEFAULT_NUM);
	memset(work->unk4C, 0, sizeof(Bss930Work4C));
	
	work->unk48 = fn_1_2EA4;
}

float fn_1_1C80(float arg1, float arg2, float arg3)
{
	float temp_f31;
	float temp_f30;
	temp_f31 = fmod(arg2-arg1, 360);
	if(temp_f31 < 0.0f) {
		temp_f31 += 360.0f;
	}
	if(temp_f31 > 180.0f) {
		temp_f31 -= 360.0f;
	}
	temp_f30 = fmod(arg1+(arg3*temp_f31), 360);
	if(temp_f30 < 0.0f) {
		temp_f30 += 360.0f;
	}
	return temp_f30;
}

void fn_1_389C(omObjData *object);
s32 fn_1_5530(omObjData *arg0, Vec *arg1, Vec *arg2);

void fn_1_1D84(omObjData *object)
{
	float temp_f31;
	float temp_f30;
	float temp_f28;
	float temp_f27;
	float temp_f23;
	Bss930Work *temp_r31;
	s32 temp_r29;
	u32 temp_r28;
	s32 temp_r27;
	Vec sp40;
	Vec sp34;
	temp_r31 = object->data;
	temp_r29 = temp_r31->unk28;
	temp_r28 = temp_r31->unk30;
	switch(temp_r31->unk14) {
		case 0:
			if(fn_1_1240() >= 6) {
				if(fn_1_1240() == 7) {
					temp_r31->unk14 = 1;
					temp_r31->unk40 = 60;
					temp_r31->unk08 = temp_r31->unk0A = 0;
					temp_r31->unk06 = temp_r31->unk07 = 0;
				} else {
					if(!GWPlayerCfg[temp_r31->unk02].iscom) {
						temp_r31->unk06 = HuPadStkX[temp_r31->unk04];
						temp_r31->unk07 = HuPadStkY[temp_r31->unk04];
						temp_r31->unk08 = HuPadBtn[temp_r31->unk04];
						temp_r31->unk0A = HuPadBtnDown[temp_r31->unk04];
					} else {
						temp_r31->unk08 = temp_r31->unk0A = 0;
						temp_r31->unk06 = temp_r31->unk07 = 0;
						fn_1_389C(object);
					}
					temp_f31 = temp_r31->unk06;
					temp_f30 = -(float)temp_r31->unk07;
					if(temp_r31->field_0_bit1) {
						temp_f31 = temp_f30 = 0;
					}
					temp_f28 = sqrtf((temp_f31*temp_f31)+(temp_f30*temp_f30));
					if(temp_f28 > 0) {
						temp_f31 /= temp_f28;
						temp_f30 /= temp_f28;
						if(temp_f28 > 72) {
							temp_f28 = 72;
						}
						temp_r31->unk18 = (10*temp_f28)/72;
						temp_r31->unk1C.x = temp_f31*temp_r31->unk18;
						temp_r31->unk1C.z = temp_f30*temp_r31->unk18;
						object->rot.y = fn_1_1C80(object->rot.y, atan2d(temp_r31->unk1C.x, temp_r31->unk1C.z), 0.4f);
						if(temp_r31->unk18 < 7.5f) {
							temp_r29 = 1;
						} else {
							temp_r29 = 2;
						}
						temp_r28 = 0x40000001;
					} else {
						temp_r31->unk1C.x = temp_r31->unk1C.z = 0;
						temp_r29 = 0;
						temp_r28 = 0x40000001;
					}
					object->trans.x += temp_r31->unk1C.x;
					object->trans.z += temp_r31->unk1C.z;
				}
			}
			break;
			
		case 1:
			if(fn_1_1240() == 9) {
				if(--temp_r31->unk40 == 0){ 
					temp_r31->unk14 = 2;
					temp_r31->unk40 = 300;
					temp_r31->unk2C = -1;
				}
			}
			if(!temp_r31->field_0_bit2) {
				temp_r29 = 5;
			} else {
				temp_r29 = 0;
			}
			temp_r28 = 0x40000001;
			break;
			
		case 2:
			if(fn_1_1240() == 10) {
				temp_r31->unk14 = 3;
			} else {
				VECSubtract(&temp_r31->unk64, &object->trans, &sp34);
				temp_f28 = VECMag(&sp34);
				if(temp_f28 < 20 || temp_r31->unk40 == 0) {
					temp_r29 = 5;
					temp_r28 = 0x40000001;
					object->rot.y = fn_1_1C80(object->rot.y, 0, 0.2f);
					temp_r31->field_0_bit3 = 1;
				} else {
					if(!temp_r31->field_0_bit3) {
						temp_r27 = fn_1_5530(object, &temp_r31->unk64, &sp40);
					} else {
						sp40.x = temp_r31->unk64.x;
						sp40.y = temp_r31->unk64.y;
						sp40.z = temp_r31->unk64.z;
						temp_r27 = 0;
					}
					VECSubtract(&sp40, &object->trans, &sp34);
					object->rot.y = fn_1_1C80(object->rot.y, atan2d(sp34.x, sp34.z), 0.2f);
					if(!temp_r27) {
						if(temp_f28 < 100.0f) {
							temp_f23 = 7.5f*(temp_f28/100.0f);
						} else {
							temp_f23 = 7.5f;
						}
					} else {
						temp_f23 = 3.75f;
					}
					temp_r31->unk1C.x = temp_f23*sind(object->rot.y);
					temp_r31->unk1C.z = temp_f23*cosd(object->rot.y);
					object->trans.x += temp_r31->unk1C.x;
					object->trans.z += temp_r31->unk1C.z;
					temp_r29 = 8;
					temp_r28 = 0x40000001;
					
				}
				if(temp_r31->unk40) {
					temp_r31->unk40--;
				}
			}
			break;
			
		case 3:
			if(fn_1_1240() < 10) {
				temp_r29 = 0;
				temp_r28 = 0x40000001;
			} else {
				if((!temp_r31->unk10 && lbl_1_bss_924 < 0) || (temp_r31->unk10 && lbl_1_bss_924 >= 0)) {
					temp_r29 = 6;
				} else {
					temp_r29 = 7;
				}
				temp_r28 = 0;
				object->rot.y = fn_1_1C80(object->rot.y, 0, 0.2f);
				Hu3DModelAttrReset(object->model[0], 0x40000001);
			}
			break;
	}
	if(temp_r31->unk2C >= 0) {
		temp_r29 = temp_r31->unk2C;
		temp_r28 = temp_r31->unk34;
	}
	if((temp_r29 >= 0 && temp_r29 != temp_r31->unk28) || temp_r28 != temp_r31->unk30) {
		temp_r31->unk28 = temp_r29;
		temp_r31->unk30 = temp_r28;
		CharModelMotionShiftSet(temp_r31->unk0C, object->motion[temp_r31->unk28], 0, 8, temp_r28);
	}
}

void fn_1_5004(void);

void fn_1_361C(omObjData *object);

void fn_1_2930(omObjData *object)
{
	Bss930Work *temp_r31;
	s32 temp_r30;
	omObjData *temp_r29;
	omObjData **temp_r28;
	temp_r28 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
	fn_1_5004();
	for(temp_r30=0; temp_r30<4; temp_r30++) {
		temp_r29 = temp_r28[temp_r30];
		temp_r31 = temp_r29->data;
		if(temp_r31->unk48 != NULL) {
			temp_r31->unk48(temp_r29);
		}
		if(temp_r31->field_0_bit4) {
			fn_1_361C(temp_r29);
		}
	}
}

float lbl_1_data_180[6] = {
	0,
	0.3,
	0.7,
	1.0,
	1.3,
	1.6
};

float lbl_1_data_198[6][2] = {
	100.0f, 0.75f,
	110.0f, 0.8f,
	120.000008f, 0.85f,
	130.0f, 0.9f,
	140.0f, 0.95f,
	150.0f, 0.99f
};

void fn_1_29DC(omObjData *object)
{
	Mtx sp50;
	Mtx sp20;
	Vec sp14;
	Vec sp8;
	Bss930Work *temp_r31;
	ModelData *temp_r29;
	temp_r31 = object->data;
	if(temp_r31->unk44 > 0 && temp_r31->field_0_bit0) {
		if(--temp_r31->unk44 == 0) {
			lbl_1_bss_924 = 1;
			Hu3DGLightKill(lbl_1_bss_91A[1]);
			lbl_1_bss_91A[1] = -1;
			Hu3DModelAttrSet(object->model[2], 1);
			HuAudFXEmiterPlay(1469, &object->trans);
			HuAudCharVoicePlay(temp_r31->unk0C, 291);
		} else {
			HuAudFXEmiterPlay(1466, &object->trans);
			HuAudCharVoicePlay(temp_r31->unk0C, 296);
		}
		temp_r31->field_0_bit0 = 0;
		temp_r31->field_0_bit1 = 1;
		temp_r31->unk2C = 3;
		temp_r31->unk34 = 0;
		temp_r31->unk46 = 60;
		temp_r31->unk60 = 30;
		omVibrate(temp_r31->unk02, 12, 6, 6);
	}
	if(temp_r31->unk46 > 0) {
		if(temp_r31->unk60) {
			if(--temp_r31->unk60 == 0) {
				temp_r31->unk2C = -1;
				temp_r31->field_0_bit1 = 0;
			}
		} else {
			if((temp_r31->unk46 & 0x2) == 0) {
				Hu3DModelAttrReset(object->model[0], 1);
			} else {
				Hu3DModelAttrSet(object->model[0], 1);
			}
			temp_r31->unk46--;
		}
	}
	if(temp_r31->field_0_bit2) {
		Hu3DModelObjMtxGet(object->model[0], "test11_tex_we-itemhook-r", sp50);
		MTXTrans(sp20, 0, 52, 0);
		MTXConcat(sp50, sp20, sp50);
		Hu3DModelPosSet(object->model[2], sp50[0][3], sp50[1][3], sp50[2][3]);
		Hu3DModelScaleSet(object->model[2], lbl_1_data_180[temp_r31->unk44], lbl_1_data_180[temp_r31->unk44], lbl_1_data_180[temp_r31->unk44]);
	}
	if(fn_1_1240() >= 4 && fn_1_1240() <= 8 && lbl_1_bss_91A[1] >= 0) {
		Hu3DGLightPointSet(lbl_1_bss_91A[1], (15*sind(object->work[0]))+lbl_1_data_198[temp_r31->unk44][0], lbl_1_data_198[temp_r31->unk44][1], 3);
		temp_r29 = &Hu3DData[object->model[2]];
		sp8 = temp_r29->pos;
		sp14 = sp8;
		sp14.y = 800;
		sp8.y = 0;
		sp14.z += 1;
		Hu3DGLightPosSet(lbl_1_bss_91A[1], temp_r29->pos.x, 140, temp_r29->pos.z, 0, 1, 0);
		if(lbl_1_bss_918) {
			Hu3DShadowPosSet(&sp14, &Hu3DShadowData.unk_2C, &sp8);
		}
		object->work[0] += 10.0f;
		Hu3DModelAttrReset(object->model[2], 1);
	} else {
		Hu3DModelAttrSet(object->model[2], 1);
	}
}

void fn_1_5C34(omObjData *object);


void fn_1_2EA4(omObjData *object)
{
	Bss930Work *temp_r30;
	Bss930Work4C *temp_r29;
	ParticleData *temp_r28;
	ModelData *temp_r27;
	Mtx sp3C;
	Mtx spC;
	temp_r30 = object->data;
	temp_r29 = temp_r30->unk4C;
	switch(temp_r30->unk50) {
		case 0:
			if(temp_r30->unk0A & PAD_BUTTON_A) {
				temp_r30->field_0_bit1 = 1;
				temp_r30->unk50 = 1;
				temp_r30->unk60 = 15;
				temp_r30->unk2C = 3;
				temp_r30->unk34 = 0;
				HuAudFXEmiterPlay(1465, &object->trans);
			}
			break;
			
		case 1:
			if(--temp_r30->unk60 == 0) {
				Hu3DModelObjMtxGet(object->model[0], "test11_tex_we-itemhook-r", sp3C);
				MTXTrans(spC, 0, 2, 50);
				MTXConcat(sp3C, spC, sp3C);
				Hu3DModelPosSet(object->model[2], sp3C[0][3], sp3C[1][3], sp3C[2][3]);
				Hu3DModelScaleSet(object->model[2], 0.5f, 0.5f, 0.5f);
				Hu3DModelAttrReset(object->model[2], 1);
				Hu3DMotionTimeSet(object->model[2], 0);
				Hu3DMotionSpeedSet(object->model[2], 2.0f);
				Hu3DModelRotSet(object->model[2], 0, 180.0f+object->rot.y, 0);
				Hu3DData[object->model[2]].unk_94 = 0;
				Hu3DData[object->model[2]].unk_98 = 2;
				Hu3DModelAttrReset(object->model[3], 1);
				Hu3DModelPosSet(object->model[3], sp3C[0][3], sp3C[1][3], sp3C[2][3]);
				temp_r27 = &Hu3DData[object->model[3]];
				temp_r28 = temp_r27->unk_120;
				temp_r28->unk_00 = 0;
				temp_r28->unk_04.x = sp3C[0][3];
				temp_r28->unk_04.y = sp3C[1][3];
				temp_r28->unk_04.z = sp3C[2][3];
				temp_r28->unk_10.x = object->rot.y;
				temp_r28->unk_3C = 30-(sqrtf((2.0f*temp_r28->unk_04.y)/1.0000001f)/2.0f);
				temp_r29->field_0_bit0 = 1;
				temp_r30->unk50 = 2;
				temp_r30->unk60 = 20;
			}
			break;
			
		case 2:
			if(--temp_r30->unk60 == 0) {
				temp_r30->unk2C = 4;
				temp_r30->unk34 = 0;
				temp_r29->field_0_bit0 = 0;
				temp_r30->unk50 = 3;
				temp_r30->unk60 = 30;
			}
			Hu3DModelObjMtxGet(object->model[0], "test11_tex_we-itemhook-r", sp3C);
			MTXTrans(spC, 0, 2, 50);
			MTXConcat(sp3C, spC, sp3C);
			Hu3DModelPosSet(object->model[2], sp3C[0][3], sp3C[1][3], sp3C[2][3]);
			Hu3DModelPosSet(object->model[3], sp3C[0][3], sp3C[1][3], sp3C[2][3]);
			fn_1_5C34(object);
			break;
			
		case 3:
			if(--temp_r30->unk60 == 0) {
				Hu3DModelAttrSet(object->model[2], 1);
				Hu3DData[object->model[2]].unk_0E = -1;
				temp_r30->field_0_bit1 = 0;
				temp_r30->unk2C = -1;
				temp_r30->unk50 = 0;
			}
			break;
	}
	if(temp_r30->unk50 && fn_1_1240() > 6 && lbl_1_bss_924 < 0) {
		temp_r29->field_0_bit0 = 0;
		Hu3DModelAttrSet(object->model[2], 1);
		Hu3DModelAttrSet(object->model[3], 1);
	}
	if(temp_r29->field_0_bit0) {
		temp_r29->unk4 = object->trans.x+(((float)temp_r29->unk10*(200*sind(object->rot.y)))/4);
		temp_r29->unk8 = 75;
		temp_r29->unkC = object->trans.z+(((float)temp_r29->unk10*(200*cosd(object->rot.y)))/4);
		temp_r29->unk4 = object->trans.x+(200.0*sind(object->rot.y));
		temp_r29->unk8 = 120.00001f;
		temp_r29->unkC = object->trans.z+(200.0*cosd(object->rot.y));
		if(temp_r29->unk10 < 4) {
			temp_r29->unk10++;
		}
	}
	
}

void fn_1_361C(omObjData *object)
{
	Bss930Work *temp_r30;
	ModelData *temp_r29;
	temp_r30 = object->data;
	if(temp_r30->field_0_bit2) {
		if(fn_1_1240() == 9) {
			temp_r30->field_0_bit2 = 0;
			temp_r30->unk48 = 0;
			temp_r30->unk54.x = 6*sind(object->rot.y);
			temp_r30->unk54.y = 20;
			temp_r30->unk54.z = 6*cosd(object->rot.y);
			temp_r30->unk60 = 30;
			temp_r29 = &Hu3DData[object->model[1]];
			temp_r29->rot.y = object->rot.y;
			Hu3DModelObjPosGet(object->model[0], "test11_tex_we-itemhook-r", &temp_r29->pos);
			Hu3DModelHookReset(object->model[0]);
			Hu3DModelAttrReset(object->model[1], 0x8000);
			Hu3DModelShadowReset(object->model[1]);
			Hu3DModelAttrReset(object->model[0], 1);
		}
	} else {
		temp_r29 = &Hu3DData[object->model[1]];
		temp_r29->pos.x += temp_r30->unk54.x;
		temp_r29->pos.y += temp_r30->unk54.y;
		temp_r29->pos.z += temp_r30->unk54.z;
		temp_r30->unk54.y += -1.0000001f;
		temp_r29->rot.x += 30.0f;
		if(--temp_r30->unk60 == 0) {
			Hu3DModelAttrSet(object->model[1], 1);
			Hu3DModelPosSet(object->model[4], temp_r29->pos.x, temp_r29->pos.y, temp_r29->pos.z);
			Hu3DModelAttrReset(object->model[4], 1);
			if(!temp_r30->unk10) {
				HuAudFXPlay(1468);
			}
			temp_r30->field_0_bit4 = 0;
		}
	}
}

void fn_1_38F0(omObjData *object);
void fn_1_49C4(omObjData *object);

void fn_1_389C(omObjData *object)
{
	Bss930Work *temp_r30;
	temp_r30 = object->data;
	if(!temp_r30->unk10) {
		fn_1_38F0(object);
	} else {
		fn_1_49C4(object);
	}
}

typedef struct unkstruct_38F0 {
	s16 unk0;
	s16 unk2;
} UnkStruct38F0;

UnkStruct38F0 lbl_1_data_1C8[8] = {
	-1, -1,
	0, -1,
	1, -1,
	1, 0,
	1, 1,
	0, 1,
	-1, 1,
	-1, 0
};


void fn_1_38F0(omObjData *object)
{
	float temp_f31;
	float temp_f30;
	float temp_f26;
	float temp_f25;
	float temp_f22;
	
	s32 temp_r31;
	s32 temp_r30;
	Bss930Work *temp_r29;
	s16 temp_r27;
	s32 temp_r26;
	s16 temp_r25;
	s16 temp_r24;
	u8 temp_r23;
	
	UnkStruct38F0 sp80[100];
	UnkStruct38F0 sp58[10];
	UnkStruct38F0 sp30[10];
	UnkStruct38F0 sp20[4];
	
	temp_r29 = object->data;
	temp_f25 = 1;
	sp20[3].unk0 = 1+(5+((9*object->trans.x)/1100));
	sp20[3].unk2 = 1+(5+((9*object->trans.z)/1100));
	for(temp_r31=1; temp_r31<11; temp_r31++) {
		for(temp_r30=1; temp_r30<11; temp_r30++) {
			lbl_1_bss_14[temp_r31][temp_r30].unk8 = 0;
			temp_f22 = VECMagPoint(lbl_1_bss_14[temp_r31][temp_r30].unk0, lbl_1_bss_14[temp_r31][temp_r30].unk4, 0);
			if(temp_f22 <= 550) {
				lbl_1_bss_14[temp_r31][temp_r30].unkC = 0;
				for(temp_r26=0; temp_r26<lbl_1_bss_92A[1]; temp_r26++) {
					temp_f31 = lbl_1_bss_14[temp_r31][temp_r30].unk0-lbl_1_bss_930[1][temp_r26]->trans.x;
					temp_f30 = lbl_1_bss_14[temp_r31][temp_r30].unk4-lbl_1_bss_930[1][temp_r26]->trans.z;
					temp_f22 = VECMagPoint(temp_f31, temp_f30, 0);
					if(temp_f22 <= 1100) {
						temp_f26 = cosd(90*(temp_f22/1100));
						temp_f26 = temp_f26*temp_f26;
						if(temp_f26 > lbl_1_bss_14[temp_r31][temp_r30].unkC) {
							lbl_1_bss_14[temp_r31][temp_r30].unkC = temp_f26;
						}
					}
				}
			} else {
				lbl_1_bss_14[temp_r31][temp_r30].unkC = -1;
			}
		}
	}
	lbl_1_bss_14[sp20[3].unk2][sp20[3].unk0].unk8 = 1;
	sp80[0] = sp20[3];
	temp_r27=0;
	temp_r25=1;
	do {
		for(temp_r31=0; temp_r31<8u; temp_r31++) {
			sp20[2].unk0 = sp80[temp_r27].unk0+lbl_1_data_1C8[temp_r31].unk0;
			sp20[2].unk2 = sp80[temp_r27].unk2+lbl_1_data_1C8[temp_r31].unk2;
			if(sp20[2].unk0 < 1 || sp20[2].unk0 >= 11 || sp20[2].unk2 < 1 || sp20[2].unk2 >= 11) {
				continue;
			}
			if(lbl_1_bss_14[sp20[2].unk2][sp20[2].unk0].unk8) {
				continue;
			}
			if(lbl_1_bss_14[sp20[2].unk2][sp20[2].unk0].unkC >= 0) {
				lbl_1_bss_14[sp20[2].unk2][sp20[2].unk0].unk8 = lbl_1_bss_14[sp80[temp_r27].unk2][sp80[temp_r27].unk0].unk8+1;
				sp80[temp_r25].unk0 = sp20[2].unk0;
				sp80[temp_r25].unk2 = sp20[2].unk2;
				temp_r25++;
			}
		}
		temp_r27++;
	} while(temp_r27 != temp_r25);
	temp_f25 = 1.0f;
	sp20[0].unk0 = -1;
	for(temp_r31=1; temp_r31<11; temp_r31++) {
		for(temp_r30=1; temp_r30<11; temp_r30++) {
			if(lbl_1_bss_14[temp_r31][temp_r30].unk8 == 0 || lbl_1_bss_14[temp_r31][temp_r30].unk8 > 5) {
				continue;
			}
			if(lbl_1_bss_14[temp_r31][temp_r30].unkC >= 0.0f && lbl_1_bss_14[temp_r31][temp_r30].unkC < temp_f25) {
				temp_f25 = lbl_1_bss_14[temp_r31][temp_r30].unkC;
				sp20[0].unk0 = temp_r30;
				sp20[0].unk2 = temp_r31;
			}
		}
	}
	temp_r23 = lbl_1_bss_14[sp20[0].unk2][sp20[0].unk0].unk8;
	if(temp_r23 == 1) {
		if(lbl_1_bss_14[sp20[3].unk2][sp20[3].unk0].unkC > 0.8f) {
			temp_f25 = 1.0f;
			for(temp_r31=0; temp_r31<8u; temp_r31++) {
				sp20[2].unk0 = sp20[3].unk0+lbl_1_data_1C8[temp_r31].unk0;
				sp20[2].unk2 = sp20[3].unk2+lbl_1_data_1C8[temp_r31].unk2;
				if(lbl_1_bss_14[sp20[2].unk2][sp20[2].unk0].unkC >= 0.0f && lbl_1_bss_14[sp20[2].unk2][sp20[2].unk0].unkC < temp_f25) {
					temp_f25 = lbl_1_bss_14[sp20[2].unk2][sp20[2].unk0].unkC;
					sp20[1] = sp20[2];
				}
			}
			sp30[1].unk0 = sp20[1].unk0;
			sp30[1].unk2 = sp20[1].unk2;
		} else {
			return;
		}
	} else {
		for(temp_r31=1; temp_r31<11; temp_r31++) {
			for(temp_r30=1; temp_r30<11; temp_r30++) {
				if(lbl_1_bss_14[temp_r31][temp_r30].unk8 >= temp_r23) {
					lbl_1_bss_14[temp_r31][temp_r30].unk8 = 0;
				}
			}
		}
		lbl_1_bss_14[sp20[0].unk2][sp20[0].unk0].unk8 = temp_r23;
		sp80[0] = sp20[3];
		temp_r24 = 1;
		temp_f25 = 1.0f;
		do {
			sp20[1] = sp80[--temp_r24];
			sp58[lbl_1_bss_14[sp20[1].unk2][sp20[1].unk0].unk8 -1] = sp20[1];
			if(sp20[1].unk0 == sp20[0].unk0 && sp20[1].unk2 == sp20[0].unk2) {
				temp_f26 = 0;
				for(temp_r31=1; temp_r31<temp_r23; temp_r31++) {
					if(lbl_1_bss_14[sp58[temp_r31].unk2][sp58[temp_r31].unk0].unkC > temp_f26) {
						temp_f26 = lbl_1_bss_14[sp58[temp_r31].unk2][sp58[temp_r31].unk0].unkC;
					}
				}
				if(temp_f26 < temp_f25) {
					temp_f25 = temp_f26;
					memcpy(sp30, sp58, temp_r23*sizeof(UnkStruct38F0));
					
				}
				continue;
			}
			for(temp_r31=0; temp_r31<8u; temp_r31++) {
				sp20[2].unk0 = sp20[1].unk0+lbl_1_data_1C8[temp_r31].unk0;
				sp20[2].unk2 = sp20[1].unk2+lbl_1_data_1C8[temp_r31].unk2;
				if(lbl_1_bss_14[sp20[2].unk2][sp20[2].unk0].unk8-1 == lbl_1_bss_14[sp20[1].unk2][sp20[1].unk0].unk8) {
					sp80[temp_r24++] = sp20[2];
				}
			}
		} while(temp_r24);
	}
	if(sp20[0].unk0 >= 0) {
		temp_f31 = lbl_1_bss_14[sp30[1].unk2][sp30[1].unk0].unk0-object->trans.x;
		temp_f30 = lbl_1_bss_14[sp30[1].unk2][sp30[1].unk0].unk4-object->trans.z;
		temp_f22 = VECMagPoint(temp_f31, temp_f30, 0);
		if(temp_f22 >= 50.0f) {
			temp_r29->unk84 = fn_1_1C80(temp_r29->unk84, atan2d(temp_f31, temp_f30), 0.1f);
			temp_r29->unk06 = (69.0f+temp_r29->unk0E)*sind(temp_r29->unk84);
			temp_r29->unk07 = (69.0f+temp_r29->unk0E)*-cosd(temp_r29->unk84);
		}
	}
}

void fn_1_49C4(omObjData *object)
{
	float temp_f31;
	float temp_f28;
	float temp_f27;
	Vec sp2C;
	Vec sp20;
	Vec sp14;
	Vec sp8;
	
	Bss930Work *temp_r31;
	omObjData *temp_r30;
	Bss930Work *temp_r28;
	temp_r30 = lbl_1_bss_930[0][0];
	temp_r31 = object->data;
	temp_r28 = temp_r30->data;
	if(temp_r31->field_0_bit1) {
		return;
	}
	switch(temp_r31->unk70) {
		case 0:
			temp_f28 = (frand16()*360)>>16;
			temp_f31 = (frand16()*550)>>16;
			temp_r31->unk74.x = temp_f31*sind(temp_f28);
			temp_r31->unk74.y = 0;
			temp_r31->unk74.z = temp_f31*cosd(temp_f28);
			temp_r31->unk70 = 1;
			temp_r31->unk80 = 0;
		
		case 1:
			sp20.x = temp_r30->trans.x+((60.0f*temp_r28->unk1C.x)/4.0f);
			sp20.z = temp_r30->trans.z+((60.0f*temp_r28->unk1C.z)/4.0f);
			sp2C.x = temp_r31->unk74.x+(temp_r31->unk80*(sp20.x-temp_r31->unk74.x));
			sp2C.y = 0;
			sp2C.z = temp_r31->unk74.z+(temp_r31->unk80*(sp20.z-temp_r31->unk74.z));
			VECSubtract(&sp2C, &object->trans, &sp14);
			temp_f31 = VECMag(&sp14);
			if(temp_f31 > 0.0f) {
				if(temp_r31->unk80 < 1.0f) {
					if(temp_f31 < 10.0f) {
						temp_r31->unk80 += (10.0f/temp_f31);
					} else {
						temp_r31->unk80 += (2.0f/temp_f31);
					}
					if(temp_r31->unk80 > 1.0f) {
						temp_r31->unk80 = 1.0f;
					}
				} else {
					if(((s32)frand() & 0x1F) == 0) {
						temp_r31->unk70 = 0;
					}
				}
			}
			temp_f27 = 60.0f+(2.0f*temp_r31->unk0E);
			temp_r31->unk84 = fn_1_1C80(temp_r31->unk84, atan2d(sp14.x, sp14.z), 0.1f);
			temp_r31->unk06 = temp_f27*sind(temp_r31->unk84);
			temp_r31->unk07 = temp_f27*-cosd(temp_r31->unk84);
			VECSubtract(&temp_r30->trans, &object->trans, &sp14);
			if(VECMag(&sp14) < 200.0f) {
				VECNormalize(&sp14, &sp14);
				sp8.x = sind(object->rot.y);
				sp8.y = 0;
				sp8.z = cosd(object->rot.y);
				if(VECDotProduct(&sp14, &sp8) >= 0.8f) {
					temp_r31->unk0A |= PAD_BUTTON_A;
					temp_r31->unk70 = 0;
				}
			}
			if(((s32)frand() & 0x3FF) < 4-temp_r31->unk0E) {
				temp_r31->unk0A |= PAD_BUTTON_A;
				temp_r31->unk70 = 0;
			}
			break;
	}
}

s32 fn_1_5058(void);

void fn_1_5004(void)
{
	s32 i = 0;
	omObjData **sp8 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
	while(fn_1_5058() && i < 50) {
		i++;
	}
}

s32 fn_1_5058(void)
{
	Vec sp14[4];
	Vec sp8;
	float temp_f31;
	float temp_f30;
	s32 temp_r31;
	omObjData *temp_r30;
	s32 temp_r29;
	omObjData **temp_r28;
	s32 temp_r27;
	omObjData *temp_r26;
	omObjData *temp_r25;
	temp_r27 = 0;
	temp_r28 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
	for(temp_r31=0; temp_r31<4; temp_r31++) {
		sp14[temp_r31].x = sp14[temp_r31].y = sp14[temp_r31].z = 0;
	}
	for(temp_r31=0; temp_r31<3; temp_r31++) {
		temp_r26 = temp_r28[temp_r31];
		for(temp_r29=temp_r31+1; temp_r29<4; temp_r29++) {
			temp_r25 = temp_r28[temp_r29];
			VECSubtract(&temp_r26->trans, &temp_r25->trans, &sp8);
			temp_f31 = VECMag(&sp8);
			if(temp_f31 < 100.0) {
				VECNormalize(&sp8, &sp8);
				temp_f30 = 0.0001f+(0.5f*(100.0-temp_f31));
				VECScale(&sp8, &sp8, temp_f30);
				VECAdd(&sp14[temp_r31], &sp8, &sp14[temp_r31]);
				VECSubtract(&sp14[temp_r29], &sp8, &sp14[temp_r29]);
				temp_r27++;
			}
		}
	}
	for(temp_r31=0; temp_r31<4; temp_r31++) {
		temp_r30 = temp_r28[temp_r31];
		VECAdd(&temp_r30->trans, &sp14[temp_r31], &temp_r30->trans);
		sp8.x = temp_r30->trans.x;
		sp8.y = 0;
		sp8.z = temp_r30->trans.z;
		temp_f31 = VECMag(&sp8);
		if(temp_f31 > 500.0) {
			VECNormalize(&sp8, &sp8);
			temp_r30->trans.x = 500.0*sp8.x;
			temp_r30->trans.z = 500.0*sp8.z;
		}
	}
	return temp_r27;
}

Vec lbl_1_data_1E8 = { 0, 0, 200 };
Vec lbl_1_data_1F4[3] = {
	{ -300, 0, -200 },
	{ 0, 0, -200 },
	{ 300, 0, -200 }
};
s32 lbl_1_data_218[6][3] = {
	{ 0, 1, 2 },
	{ 0, 2, 1 },
	{ 1, 0, 2 },
	{ 1, 2, 0 },
	{ 2, 0, 1 },
	{ 2, 1, 0 }
};

void fn_1_52BC(void)
{
	float sp14[3];
	Vec sp8;
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	
	s32 temp_r31;
	s32 temp_r30;
	Bss930Work *temp_r29;
	s32 temp_r28;
	temp_r29 = lbl_1_bss_930[0][0]->data;
	temp_r29->unk64 = lbl_1_data_1E8;
	temp_f29 = -1;
	for(temp_r30=0; temp_r30<6; temp_r30++) {
		temp_f31 = 0;
		for(temp_r31=0; temp_r31<3; temp_r31++) {
			VECSubtract(&lbl_1_data_1F4[temp_r31], &lbl_1_bss_930[1][lbl_1_data_218[temp_r30][temp_r31]]->trans, &sp8);
			sp14[temp_r31] = VECMag(&sp8);
			temp_f31 += sp14[temp_r31];
		}
		temp_f28 = temp_f31/3;
		temp_f30 = 0;
		for(temp_r31=0; temp_r31<3; temp_r31++) {
			temp_f30 += fabs(sp14[temp_r31]-temp_f28);
		}
		if(temp_f29 < 0 || temp_f30+temp_f31 < temp_f29) {
			temp_f29 = temp_f30+temp_f31;
			temp_r28 = temp_r30;
		}
	}
	for(temp_r30=0; temp_r30<3; temp_r30++) {
		temp_r29 = lbl_1_bss_930[1][lbl_1_data_218[temp_r28][temp_r30]]->data;
		temp_r29->unk64 = lbl_1_data_1F4[temp_r30];
	}
}

typedef struct unkstruct_5530 {
	s32 unk0;
	float unk4;
	float unk8;
	Vec unkC;
} UnkStruct5530;

s32 fn_1_5530(omObjData *arg0, Vec *arg1, Vec *arg2)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	
	s32 temp_r30;
	s32 temp_r29;
	omObjData *temp_r28;
	s32 temp_r27;
	
	omObjData **temp_r24;
	s32 temp_r23;
	
	UnkStruct5530 spB4[4];
	Mtx sp84;
	Vec sp78;
	Vec sp6C;
	Vec sp60;
	Vec sp54;
	Vec sp48;
	Vec sp3C;
	Vec sp30;
	Vec sp24;
	s32 sp14[4];
	float spC[2];
	Bss930Work *sp8;
	sp8 = arg0->data;
	temp_r24 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
	temp_r23 = 0;
	sp54.x = arg1->x;
	sp54.y = arg1->y;
	sp54.z = arg1->z;
	VECSubtract(&sp54, &arg0->trans, &sp48);
	temp_f30 = VECMag(&sp48);
	for(temp_r30=0; temp_r30<4; temp_r30++) {
		sp14[temp_r30] = 0;
	}
	while(1) {
		for(temp_r30=0, temp_r29=0; temp_r30<4; temp_r30++) {
			temp_r28 = temp_r24[temp_r30];
			if(arg0 == temp_r28 || sp14[temp_r30]) {
				continue;
			}
			temp_f31 = ((temp_r28->trans.x*sp48.x)-(arg0->trans.x*sp48.x)+(temp_r28->trans.y*sp48.y)-(arg0->trans.y*sp48.y)+(temp_r28->trans.z*sp48.z)-(arg0->trans.z*sp48.z))/VECMag2Point(&sp48);
			if(temp_f31 < 0.0f || temp_f31 >= 1.0f) {
				continue;
			}
			VECSubtract(&temp_r28->trans, &arg0->trans, &sp3C);
			VECCrossProduct(&sp48, &sp3C, &sp24);
			sp60.x = (temp_f31*sp48.x)+arg0->trans.x;
			sp60.y = (temp_f31*sp48.y)+arg0->trans.y;
			sp60.z = (temp_f31*sp48.z)+arg0->trans.z;
			spB4[temp_r29].unkC = sp60;
			VECSubtract(&temp_r28->trans, &sp60, &sp3C);
			if(sp24.y < 0.0f) {
				spB4[temp_r29].unk8 = VECMag(&sp3C);
			} else {
				spB4[temp_r29].unk8 = -VECMag(&sp3C);
			}
			VECSubtract(&sp60, &arg0->trans, &sp3C);
			spB4[temp_r29].unk4 = VECMag(&sp3C);
			spB4[temp_r29].unk0 = temp_r30;
			temp_r29++;
		}
		if(temp_r29 == 0) {
			break;
		}
		for(temp_r30=0; temp_r30<temp_r29-1; temp_r30++) {
			for(temp_r27=temp_r30+1; temp_r27<temp_r29; temp_r27++) {
				if(spB4[temp_r30].unk4 > spB4[temp_r27].unk4) {
					spB4[3] = spB4[temp_r30];
					spB4[temp_r30] = spB4[temp_r27];
					spB4[temp_r27] = spB4[3];
				}
			}
		}
		for(temp_r30=0; temp_r30<temp_r29; temp_r30++) {
			if(fabs(spB4[temp_r30].unk8) < 100.0 && spB4[temp_r30].unk4 > 50.0) {
				sp14[spB4[temp_r30].unk0] = 1;
				VECSubtract(&temp_r24[spB4[temp_r30].unk0]->trans, &arg0->trans, &sp3C);
				temp_f28 = VECMag(&sp3C);
				if(0.0f != temp_f28) {
					VECNormalize(&sp3C, &sp3C);
					temp_f31 = 100.0/temp_f28;
					if(temp_f31 < 0.0f) {
						temp_f31 = 0.0f;
					} else if(temp_f31 > 1.0f) {
						temp_f31 = 1.0f;
					}
					temp_f29 = asinf(temp_f31);
					MTXRotRad(sp84, 'Y', -temp_f29);
					MTXMultVec(sp84, &sp3C, &sp30);
					sp6C.x = arg0->trans.x+(sp30.x*temp_f30);
					sp6C.y = arg0->trans.y+(sp30.y*temp_f30);
					sp6C.z = arg0->trans.z+(sp30.z*temp_f30);
					VECSubtract(&sp54, &sp6C, &sp30);
					spC[0] = VECMag(&sp30);
					MTXRotRad(sp84, 'Y', temp_f29);
					MTXMultVec(sp84, &sp3C, &sp30);
					sp78.x = arg0->trans.x+(sp30.x*temp_f30);
					sp78.y = arg0->trans.y+(sp30.y*temp_f30);
					sp78.z = arg0->trans.z+(sp30.z*temp_f30);
					VECSubtract(&sp54, &sp78, &sp30);
					spC[1] = VECMag(&sp30);
					if(spC[0] < spC[1]) {
						sp54 = sp6C;
					} else {
						sp54 = sp78;
					}
					temp_r23 = 1;
					break;
				}
			}
		}
		if(temp_r30 >= temp_r29) {
			break;
		}
		VECSubtract(&sp54, &arg0->trans, &sp48);
	}
	arg2->x = sp54.x;
	arg2->y = sp54.y;
	arg2->z = sp54.z;
	return temp_r23;
}

float fn_1_5D78(float arg8, float arg9, float argA, float argB, float argC, float argD, float argE);

void fn_1_5C34(omObjData *object)
{
	float temp_f31;
	omObjData *temp_r31;
	Bss930Work4C *temp_r30;
	Bss930Work *temp_r28;
	Bss930Work *temp_r27;
	temp_r31 = lbl_1_bss_930[0][0];
	temp_r27 = object->data;
	temp_r28 = temp_r31->data;
	temp_r30 = temp_r27->unk4C;
	if(temp_r28->unk46 > 0 || !temp_r30->field_0_bit0) {
		return;
	}
	temp_f31 = fn_1_5D78(object->trans.x, object->trans.z, temp_r30->unk4, temp_r30->unkC, temp_r31->trans.x, temp_r31->trans.z, 50.0f);
	if(temp_f31 >= 0.0f && temp_f31 < 1.0f) {
		temp_r28->field_0_bit0 = 1;
	}
}

void fn_1_5D18(omObjData *object)
{
	Bss930Work *temp_r31;
	temp_r31 = object->data;
	CharModelKill(temp_r31->unk0C);
	if(temp_r31->unk4C != NULL) {
		HuMemDirectFree(temp_r31->unk4C);
	}
	HuMemDirectFree(temp_r31);
	temp_r31 = NULL;
}

float fn_1_5D78(float arg8, float arg9, float argA, float argB, float argC, float argD, float argE)
{
	float spC;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	float temp_f27;
	float temp_f26;
	float temp_f25;
	temp_f26 = (arg9 * arg9) + (((argB * argB) + ((arg8 * arg8) + ((argA * argA) - (2.0f * arg8 * argA)))) - (2.0f * arg9 * argB));
    temp_f27 = 2.0f * (((arg9 * argD) + (((arg9 * argB) + (((arg8 * argC) + ((arg8 * argA) - (argA * argC))) - (arg8 * arg8))) - (argB * argD))) - (arg9 * arg9));
    temp_f25 = ((argD * argD) + (((arg9 * arg9) + ((argC * argC) + ((arg8 * arg8) - (2.0f * arg8 * argC)))) - (2.0f * arg9 * argD))) - (argE * argE);
	if(0.0f == temp_f26) {
		if(0.0f != temp_f27) {
			return -temp_f25/temp_f27;
		} else {
			return -1;
		}
	} else {
		temp_f30 = (temp_f27 * temp_f27) - (4.0f * temp_f26 * temp_f25);
		if(temp_f30 < 0.0) {
			return -1;
		}
		temp_f30 = sqrtf(temp_f30);
		temp_f29 = (-temp_f27 + temp_f30) / (2.0f * temp_f26);
		temp_f28 = (-temp_f27 - temp_f30) / (2.0f * temp_f26);
		if(temp_f29 < temp_f28) {
			if(temp_f29 >= 0.0f && temp_f29 < 1.0f) {
				return temp_f29;
			} else {
				if(temp_f28 >= 0.0f && temp_f28 < 1.0f) {
					return temp_f28;
				}
			}
		} else {
			if(temp_f28 >= 0.0f && temp_f28 < 1.0f) {
				return temp_f28;
			} else {
				if(temp_f29 >= 0.0f && temp_f29 < 1.0f) {
					return temp_f29;
				}
			}
		}
		return -1;
	}
}

void fn_1_613C(ModelData *model, ParticleData *particle, Mtx matrix)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	HsfanimStruct01 *temp_r31;
	s32 temp_r29;
	
	if(!particle->unk_00) {
		particle->unk_00 = 1;
		temp_r31 = particle->unk_48;
		for(temp_r29=0; temp_r29<particle->unk_30; temp_r31++, temp_r29++) {
			temp_r31->unk08.x = (4.0f*((1.0f/256.0f)*frand8()))+8;
			temp_r31->unk34.x = (4.0f*(((1.0f/256.0f)*((s32)frand() & 0x1FF))-1));
			temp_r31->unk34.y = (64.0f*((1.0f/256.0f)*frand8()));
			temp_r31->unk34.z = (4.0f*(((1.0f/256.0f)*((s32)frand() & 0x1FF))-1));
			temp_r31->unk30 = 360.0f*((1.0f/256.0f)*frand8());
			temp_r31->unk00_s16 = frand8();
			temp_r31->unk02 = (frand() & 0x3)+4;
		}
		temp_f29 = temp_f28 = 0;
	} else {
		temp_f29 = (particle->unk_04.x-model->pos.x);
		temp_f28 = (particle->unk_04.z-model->pos.z);
	}
	temp_r31 = particle->unk_48;
	for(temp_r29=0; temp_r29<particle->unk_30; temp_r31++, temp_r29++) {
		temp_f30 = temp_r31->unk00_s16/255.0f;
		temp_f31 = temp_f30*temp_f30;
		temp_r31->unk34.x += temp_f29*temp_f31;
		temp_r31->unk34.y = 60.0f*temp_f30;
		temp_r31->unk34.z += temp_f28*temp_f31;
		temp_r31->unk40.a = 255.0f*(1.0f-temp_f30);
		temp_f31 = 0.5*(1+sind(270.0f*temp_f30));
		temp_r31->unk2C = temp_f31*(temp_r31->unk08.x*temp_f31);
		temp_r31->unk00_s16 += temp_r31->unk02;
		if(temp_r31->unk00_s16 > 255) {
			temp_r31->unk34.x = (4.0f*(((1.0f/256.0f)*((s32)frand() & 0x1FF))-1));
			temp_r31->unk34.y = 0;
			temp_r31->unk34.z = (4.0f*(((1.0f/256.0f)*((s32)frand() & 0x1FF))-1));
			temp_r31->unk00_s16 = 0;
		}
	}
	DCStoreRangeNoSync(particle->unk_48, particle->unk_30*sizeof(HsfanimStruct01));
	particle->unk_04.x = model->pos.x;
	particle->unk_04.z = model->pos.z;
}

void fn_1_6640(ModelData *model, ParticleData *particle, Mtx matrix)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	HsfanimStruct01 *temp_r31;
	s32 temp_r28;
	s32 temp_r27;
	GXColor sp8 = { 0, 0, 0, 255 };
	if(!particle->unk_00) {
		particle->unk_00 = 1;
		temp_r31 = particle->unk_48;
		for(temp_r28=0; temp_r28<particle->unk_30; temp_r31++, temp_r28++) {
			temp_r31->unk2C = 15;
			temp_r31->unk34.x = temp_r31->unk34.y = temp_r31->unk34.z = 0;
			temp_f31 = particle->unk_10.x+(10.0f*(((1.0f/256.0f)*((s32)frand() & 0x1FF))-1.0f));
			temp_f30 = 100.0f*(0.1f*((1.0f/256.0f)*((s32)frand() & 0xFF)))+10;
			temp_r31->unk08.x = temp_f30*sind(temp_f31);
			temp_r31->unk08.y = 100.0f*(0.02f*(((1.0f/256.0f)*((s32)frand() & 0x1FF))-1.0f));
			temp_r31->unk08.z = temp_f30*cosd(temp_f31);
			temp_r31->unk40.r = temp_r31->unk40.g = temp_r31->unk40.b = 255;
			temp_r31->unk40.a = 0;
			temp_r31->unk00_s16 = ((float)particle->unk_3C)*((float)temp_r28/(float)particle->unk_30);
		}
	} else {
		temp_f29 = (particle->unk_04.x-model->pos.x);
		temp_f28 = (particle->unk_04.z-model->pos.z);
	}
	temp_r27 = 0;
	temp_r31 = particle->unk_48;
	for(temp_r28=0; temp_r28<particle->unk_30; temp_r31++, temp_r28++) {
		if(temp_r31->unk00_s16 >= 0) {
			if(temp_r31->unk00_s16 == 0) {
				temp_r31->unk34.x += temp_r31->unk08.x+temp_f29;
				temp_r31->unk34.y += temp_r31->unk08.y;
				temp_r31->unk34.z += temp_r31->unk08.z+temp_f28;
				temp_r31->unk08.y += -1.0000001f;
				if(temp_r31->unk40.a) {
					if(--temp_r31->unk40.a == 0) {
						temp_r31->unk00_s16 = -1;
					}
				}
				if(temp_r31->unk34.y < 0.0f) {
					temp_r31->unk34.y = 0;
					temp_r31->unk00_s16 = -1;
					temp_r31->unk40.a = 0;
				}
			} else {
				if(--temp_r31->unk00_s16 == 0) {
					temp_r31->unk40.a = 255;
				}
			}
		} else {
			temp_r27++;
		}
	}
	if(temp_r27 == particle->unk_30) {
		model->attr |= 0x1;
	}
	DCStoreRangeNoSync(particle->unk_48, particle->unk_30*sizeof(HsfanimStruct01));
	particle->unk_04.x = model->pos.x;
	particle->unk_04.z = model->pos.z;
}

void fn_1_6AE8(ModelData *model, ParticleData *particle, Mtx matrix)
{
	HsfanimStruct01 *temp_r31;
	s32 temp_r29;
	s16 temp_r28;
	s32 temp_r27; // ! - uninitialized
	
	if(!particle->unk_00) {
		particle->unk_00 = 1;
		temp_r31 = particle->unk_48;
		for(temp_r29=0; temp_r29<particle->unk_30; temp_r31++, temp_r29++) {
			temp_r31->unk2C = 50;
			temp_r31->unk34.x = 0;
			temp_r31->unk34.y = 0;
			temp_r31->unk34.z = 0;
			temp_r31->unk08.x = 100.0f*(0.05f*(((1.0f/256.0f)*((s32)frand() & 0x1FF))-1.0f));
			temp_r31->unk08.y = 100.0f*(0.05f*(((1.0f/256.0f)*((s32)frand() & 0x1FF))-1.0f));
			temp_r31->unk08.z = 100.0f*(0.05f*(((1.0f/256.0f)*((s32)frand() & 0x1FF))-1.0f));
			temp_r31->unk40.a = 128;
			temp_r31->unk00_s16 = 0;
		}
	}
	temp_r31 = particle->unk_48;
	for(temp_r29=0; temp_r29<particle->unk_30; temp_r29++, temp_r31++) {
		if(temp_r31->unk00_s16 < 0) {
			temp_r27++;
			continue;
		}
		temp_r31->unk34.x += temp_r31->unk08.x;
		temp_r31->unk34.y += temp_r31->unk08.y;
		temp_r31->unk34.z += temp_r31->unk08.z;
		temp_r31->unk08.x *= 0.92f;
		temp_r31->unk08.y *= 0.92f;
		temp_r31->unk08.z *= 0.92f;
		temp_r28 = temp_r31->unk40.a;
		temp_r28 -= 4;
		if(temp_r28 < 0) {
			temp_r31->unk00_s16 = -1;
			temp_r28 = 0;
		}
		temp_r31->unk40.a = temp_r28;
	}
	if(temp_r27 == particle->unk_30) {
		model->attr |= 0x1;
	}
	DCStoreRangeNoSync(particle->unk_48, particle->unk_30*sizeof(HsfanimStruct01));
}

void fn_1_6DEC(s16 arg0, u32 arg1)
{
	HsfData *temp_r31;
	HsfMaterial *temp_r30;
	s32 temp_r29;
	ModelData *temp_r28;
	temp_r28 = &Hu3DData[arg0];
	temp_r31 = temp_r28->hsfData;
	temp_r30 = temp_r31->material;
	for(temp_r29=0; temp_r29<temp_r31->materialCnt; temp_r29++, temp_r30++) {
		temp_r30->flags |= arg1;
	}
	
}

void fn_1_709C(s32 arg0, s32 arg1, float arg2);

void fn_1_72EC(omObjData *object);

void fn_1_6E5C(omObjData *object)
{
	Vec sp14;
	Vec sp8;
	
	fn_1_709C(0, 0, 0);
	sp14.x = (((sind(CRot.y)*cosd(CRot.x))*CZoom)+Center.x);
	sp14.y = (-sind(CRot.x)*CZoom)+Center.y;
	sp14.z = ((cosd(CRot.y)*cosd(CRot.x))*CZoom)+Center.z;
	VECSubtract(&Center, &sp14, &sp8);
	VECNormalize(&sp8, &sp8);
	HuAudFXListnerSetEX(&sp14, &sp8, 10000, 566.6667, 0, 300, 300);
	object->func = fn_1_72EC;
}

void fn_1_709C(s32 arg0, s32 arg1, float arg2)
{
	CZoom = lbl_1_data_0[arg0].zoom+(arg2*(lbl_1_data_0[arg1].zoom-lbl_1_data_0[arg0].zoom));
	Center.x = lbl_1_data_0[arg0].pos.x+(arg2*(lbl_1_data_0[arg1].pos.x-lbl_1_data_0[arg0].pos.x));
	Center.y = lbl_1_data_0[arg0].pos.y+(arg2*(lbl_1_data_0[arg1].pos.y-lbl_1_data_0[arg0].pos.y));
	Center.z = lbl_1_data_0[arg0].pos.z+(arg2*(lbl_1_data_0[arg1].pos.z-lbl_1_data_0[arg0].pos.z));
	CRot.x = lbl_1_data_0[arg0].rot.x+(arg2*(lbl_1_data_0[arg1].rot.x-lbl_1_data_0[arg0].rot.x));
	CRot.y = lbl_1_data_0[arg0].rot.y+(arg2*(lbl_1_data_0[arg1].rot.y-lbl_1_data_0[arg0].rot.y));
	CRot.z = lbl_1_data_0[arg0].rot.z+(arg2*(lbl_1_data_0[arg1].rot.z-lbl_1_data_0[arg0].rot.z));
}

float lbl_1_data_260[2] = { 0, 0 };

void fn_1_72EC(omObjData *object)
{
	Vec sp14;
	Vec sp8;
	switch(fn_1_1240()) {
		case 2:
			fn_1_709C(0, 1, sind(90.0f*lbl_1_data_260[0]));
			if(lbl_1_data_260[0] < 1.0f) {
				lbl_1_data_260[0] += 5.0f/240.0f;
				if(lbl_1_data_260[0] > 1.0f) {
					lbl_1_data_260[0] = 1.0f;
				}
			}
			break;
			
		case 5:
			fn_1_709C(1, 0, sind(90.0f*lbl_1_data_260[1]));
			if(lbl_1_data_260[1] < 1.0f) {
				lbl_1_data_260[1] += 10.0f/360.0f;
				if(lbl_1_data_260[1] > 1.0f) {
					lbl_1_data_260[1] = 1.0f;
				}
			}
			break;
	}
	sp14.x = (((sind(CRot.y)*cosd(CRot.x))*CZoom)+Center.x);
	sp14.y = (-sind(CRot.x)*CZoom)+Center.y;
	sp14.z = ((cosd(CRot.y)*cosd(CRot.x))*CZoom)+Center.z;
	VECSubtract(&Center, &sp14, &sp8);
	VECNormalize(&sp8, &sp8);
	HuAudFXListnerUpdate(&sp14, &sp8);
}
