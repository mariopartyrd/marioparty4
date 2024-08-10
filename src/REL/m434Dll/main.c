#include "game/object.h"
#include "game/objsub.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/audio.h"
#include "game/wipe.h"

#include "game/minigame_seq.h"
#include "game/gamework_data.h"
#include "REL/m434Dll.h"
#include "math.h"
#include "ext_math.h"

#include "rel_sqrt_consts.h"


typedef struct camera_view {
	float zoom;
	Vec pos;
	Vec rot;
} CameraView;

Vec lbl_1_data_0 = { -700, 2500, -700 };
Vec lbl_1_data_C = { 0.3, -0.8, 0.3 };
Vec lbl_1_data_18 = { 34.75, -24.75, 3500 };
GXColor lbl_1_data_24 = { 255, 255, 255, 255 };
Vec lbl_1_data_28 = { -700, 2500, 700 };
Vec lbl_1_data_34 = { 0, 1, 0 };
Vec lbl_1_data_40 = { 0, 0, 0 };


omObjData *lbl_1_bss_3D4;
omObjData *lbl_1_bss_3D0;
omObjData *lbl_1_bss_3CC;
omObjData *lbl_1_bss_3C8;
omObjData *lbl_1_bss_3C4;
s16 lbl_1_bss_3C2;
s16 lbl_1_bss_3C0;
s32 lbl_1_bss_3BC;
s32 lbl_1_bss_3B8;
s16 lbl_1_bss_3B2[3];
s16 lbl_1_bss_3B0;
s16 lbl_1_bss_3AC[2];
s16 lbl_1_bss_3AA;
s16 lbl_1_bss_3A8;
s16 lbl_1_bss_3A0[4];
s32 lbl_1_bss_39C;
CameraView lbl_1_bss_1C[32];
s32 lbl_1_bss_18;
s32 lbl_1_bss_10[2];
s32 lbl_1_bss_8[2];
s32 lbl_1_bss_4;
float lbl_1_bss_0;

void fn_1_4FC(omObjData *object);
void fn_1_CC8(omObjData *object);
s32 fn_1_10F4(void);
void fn_1_1104(Process *objman);
void fn_1_1684(void);
void fn_1_16B4(void);

void ObjectSetup(void)
{
	s32 i;
	Process *objman;
	OSReport("******* M434ObjectSetup *********\n");
	objman = omInitObjMan(50, 8192);
	omGameSysInit(objman);
	CZoom = 2097.6f;
	Center.x = 0;
	Center.y = 172;
	Center.z = 361;
	CRot.x = -32;
	CRot.y = 0;
	CRot.z = 0;
	for(i=0; i<4; i++) {
		CZoomM[i] = CZoom;
		CenterM[i] = Center;
		CRotM[i] = CRot;
	}
	fn_1_16B4();
	Hu3DCameraCreate(15);
	Hu3DCameraPerspectiveSet(2, 30, 20, 25000, 1.2f);
	Hu3DCameraViewportSet(2, 0, 0, 320, 240, 0, 1);
	Hu3DCameraPerspectiveSet(13, 30, 20, 25000, 1.2f);
	Hu3DCameraViewportSet(13, 0, 0, 640, 480, 0, 1);
	lbl_1_bss_3CC = omAddObjEx(objman, 32730, 0, 0, -1, omOutViewMulti);
	lbl_1_bss_3CC->work[0] = 4;
	HuAudSndGrpSet(59);
	lbl_1_data_C.x = -lbl_1_data_0.x;
	lbl_1_data_C.y = -lbl_1_data_0.y;
	lbl_1_data_C.z = -lbl_1_data_0.z;
	VECNormalize(&lbl_1_data_C, &lbl_1_data_C);
	lbl_1_bss_3B0 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
	Hu3DGLightInfinitytSet(lbl_1_bss_3B0);
	Hu3DGLightStaticSet(lbl_1_bss_3B0, 1);
	for(i=0; i<4; i++) {
		lbl_1_bss_3A0[i] = GWPlayerCfg[i].group;
	}
	lbl_1_bss_3D4 = omAddObjEx(objman, 0, 0, 0, -1, fn_1_4FC);
	lbl_1_bss_3D0 = omAddObjEx(objman, 0, 1, 0, -1, fn_1_CC8);
	fn_1_1DB0(objman);
	fn_1_4854(objman);
	fn_1_6860(objman);
	fn_1_1104(objman);
}

void fn_1_558(omObjData *object);

void fn_1_4FC(omObjData *object)
{
	fn_1_1D64(0);
	lbl_1_bss_3AA = 0;
	lbl_1_bss_3A8 = 0;
	object->func = fn_1_558;
}

s32 lbl_1_data_70 = -1;

void fn_1_C64(omObjData *object);
void fn_1_1638(s32 arg0);

void fn_1_558(omObjData *object)
{
	s32 temp_r31;
	s32 temp_r29;
	s32 sp10[2][4];
	s32 sp8[2];
	
	switch(fn_1_1D54()) {
		case 0:
			lbl_1_bss_3C2 = 60;
			lbl_1_bss_3C0 = 60;
			fn_1_1D64(1);
			lbl_1_bss_10[1] = 60;
			WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
			HuAudFXPlay(1736);
			break;
		
		case 1:
			if(fn_1_10F4() == 2) {
				if(lbl_1_bss_10[1] != 0) {
					if(--lbl_1_bss_10[1] == 0) {
						lbl_1_bss_3BC = MGSeqStartCreate();
						HuAudStreamPlay("sound/mu_047a.adp", 1);
					}
				} else {
					if(MGSeqStatGet(lbl_1_bss_3BC) == 0) {
						fn_1_1D64(2);
						HuAudFXPlay(1738);
						lbl_1_bss_3B8 = MGSeqTimerCreate(60);
						fn_1_1638(1);
					}
					if(lbl_1_data_70 < 0 && (MGSeqStatGet(lbl_1_bss_3BC) & 0x10)) {
						lbl_1_data_70 = HuAudSeqPlay(67);
					}
				}
			}
			break;
			
		case 2:
			if(--lbl_1_bss_3C0 == 0) {
				lbl_1_bss_3C2--;
				MGSeqParamSet(lbl_1_bss_3B8, 1, lbl_1_bss_3C2);
				lbl_1_bss_3C0 = 60;
			}
			if(!lbl_1_bss_3C2 || lbl_1_bss_3A8 == 1) {
				fn_1_1D64(3);
				lbl_1_bss_10[1] = 60;
				lbl_1_bss_3BC = MGSeqFinishCreate();
				HuAudStreamFadeOut(30);
				HuAudSeqFadeOut(lbl_1_data_70, 100);
			}
			break;
			
		case 3:
			if(lbl_1_bss_3B8 >= 0) {
				MGSeqParamSet(lbl_1_bss_3B8, 2, -1);
				lbl_1_bss_3B8 = -1;
			}
			if(MGSeqStatGet(lbl_1_bss_3BC) == 0) {
				fn_1_1D64(4);
				lbl_1_bss_10[1] = 60;
			}
			break;
			
		case 4:
			if(--lbl_1_bss_10[1] == 0) {
				sp8[0] = sp8[1] = 0;
				for(temp_r31=0; temp_r31<4; temp_r31++) {
					temp_r29 = fn_1_1D74(temp_r31);
					sp10[temp_r29][sp8[temp_r29]++] = temp_r31;
				}
				lbl_1_bss_3AA = fn_1_1CB8();
				switch(lbl_1_bss_3AA) {
					case -1:
						lbl_1_bss_3AC[0] = GWPlayerCfg[sp10[0][0]].character;
						lbl_1_bss_3AC[1] = GWPlayerCfg[sp10[0][1]].character;
						MGSeqWinCreate(lbl_1_bss_3AC[0], lbl_1_bss_3AC[1], -1, -1);
						GWPlayerCoinWinSet(sp10[0][0], 10);
						GWPlayerCoinWinSet(sp10[0][1], 10);
						HuAudSStreamPlay(1);
						break;
						
					case 0:
						MGSeqDrawCreate();
						HuAudSStreamPlay(4);
						break;
						
					case 1:
						lbl_1_bss_3AC[0] = GWPlayerCfg[sp10[1][0]].character;
						lbl_1_bss_3AC[1] = GWPlayerCfg[sp10[1][1]].character;
						MGSeqWinCreate(lbl_1_bss_3AC[0], lbl_1_bss_3AC[1], -1, -1);
						GWPlayerCoinWinSet(sp10[1][0], 10);
						GWPlayerCoinWinSet(sp10[1][1], 10);
						HuAudSStreamPlay(1);
						break;
				}
				fn_1_1D64(5);
				lbl_1_bss_10[1] = 210;
			}
			break;
			
		case 5:
			if(--lbl_1_bss_10[1] == 0) {
				WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
				object->func = fn_1_C64;
			}
			
			break;
	}
	for(temp_r31=0; temp_r31<4; temp_r31++) {
		CZoomM[temp_r31] = CZoom;
		CRotM[temp_r31] = CRot;
		CenterM[temp_r31] = Center;
		
	}
	if(omSysExitReq && !WipeStatGet()) {
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
		object->func = fn_1_C64;
	}
}

void fn_1_C64(omObjData *object)
{
	if(WipeStatGet()) {
		return;
	}
	fn_1_1E44();
	fn_1_4964();
	fn_1_6A84();
	fn_1_1684();
	MGSeqKillAll();
	HuAudFadeOut(1);
	omOvlReturnEx(1, 1);
	OSReport("******* M434Exit *********\n");
}

void fn_1_E44(omObjData *object);
void fn_1_16D8(void);
void fn_1_1950(float arg0, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6);
void fn_1_1A00(s32 arg0);
void fn_1_1A10(float arg0);

void fn_1_CC8(omObjData *object)
{
	lbl_1_bss_8[0] = 0;
	lbl_1_bss_8[1] = 140;
	fn_1_16D8();
	fn_1_1950(302, 0, 125, -188, -24, 28, 0);
	fn_1_1A00(1);
	object->func = fn_1_E44;
	omSetStatBit(object, 0x100);
	object->model[0] = Hu3DModelCreateFile(0x410007);
	Hu3DModelCameraSet(object->model[0], 4);
	Hu3DModelLayerSet(object->model[0], 4);
	Hu3DModelPosSet(object->model[0], -50, -40, -540);
	Hu3DMotionSpeedSet(object->model[0], 1);
	Hu3DModelRotSet(object->model[0], 0, 70, 0);
	
}

s32 lbl_1_data_A4[] = { 74, 98 };
float lbl_1_data_AC[] = { -120, -267.9 };

void fn_1_10BC(omObjData *object);

void fn_1_E44(omObjData *object)
{
	ModelData *temp_r31;
	s32 temp_r30;
	Vec sp8;
	switch(lbl_1_bss_8[0]) {
		case 0:
			if(--lbl_1_bss_8[1] == 0) {
				Hu3DModelAttrSet(object->model[0], 1);
				lbl_1_bss_8[0] = 1;
			}
			for(temp_r30=0; temp_r30<2u; temp_r30++) {
				if(lbl_1_bss_4 == lbl_1_data_A4[temp_r30]) {
					temp_r31 = &Hu3DData[object->model[0]];
					sp8.x = temp_r31->pos.x+(lbl_1_data_AC[temp_r30]*cosd(temp_r31->rot.y));
					sp8.y = -15.000001f;
					sp8.z = temp_r31->pos.z-(lbl_1_data_AC[temp_r30]*sind(temp_r31->rot.y));
					if(temp_r30 == 0) {
						fn_1_47EC(&sp8);
						HuAudFXPlay(1731);
					} else {
						fn_1_43AC(&sp8);
						HuAudFXPlay(1739);
					}
				}
			}
			lbl_1_bss_4++;
			break;
			
		case 1:
			lbl_1_bss_0 += 0.02f;
			if(lbl_1_bss_0 >= 1.0f) {
				lbl_1_bss_8[0] = 2;
				lbl_1_bss_0 = 1.0f;
				object->func = fn_1_10BC;
			}
			fn_1_1A10(lbl_1_bss_0);
			break;
	}
}

void fn_1_1788(void);

void fn_1_10BC(omObjData *object)
{
	fn_1_1788();
	fn_1_1788();
	object->func = NULL;
}

s32 fn_1_10F4(void)
{
	return lbl_1_bss_8[0];
}

void fn_1_1150(omObjData *object);

u16 lbl_1_data_B4[6] = {
	0, 1, 2, 3, 4, 4
};

float lbl_1_data_C0[6][2] = {
	0,0,
	0,0,
	-33,-2,
	-9,-2,
	11,-2,
	31,-2
};

float lbl_1_data_F0[2][2] = {
	104, 56,
	472, 56
};

typedef struct work_1150 {
	s32 unk0;
	s16 unk4;
	s16 unk6[6];
	u16 unk12;
} Work1150;

void fn_1_1104(Process *objman)
{
	lbl_1_bss_3C4 = omAddObjEx(objman, 0, 0, 0, -1, fn_1_1150);
}

void fn_1_1470(omObjData *object);

void fn_1_1150(omObjData *object)
{
	Work1150 *temp_r31;
	u32 temp_r30;
	s32 temp_r29;
	temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, 2*sizeof(Work1150), MEMORY_DEFAULT_NUM);
	object->data = temp_r31;
	memset(object->data, 0, 2*sizeof(Work1150));
	for(temp_r29=0; temp_r29<2; temp_r31++, temp_r29++) {
		for(temp_r30=0; temp_r30<6; temp_r30++) {
			switch(lbl_1_data_B4[temp_r30]) {
				case 0:
					temp_r31->unk6[temp_r30] = espEntry(0x61001D, 1, 0);
					espPriSet(temp_r31->unk6[temp_r30], 256);
					espColorSet(temp_r31->unk6[temp_r30], 0, 0, 0);
					espTPLvlSet(temp_r31->unk6[temp_r30], 0.5);
					break;
					
				case 1:
					temp_r31->unk6[temp_r30] = espEntry((temp_r29 == 0) ? 0x61001B : 0x61001C, 1, 0);
					espPriSet(temp_r31->unk6[temp_r30], 256);
					break;
					
				case 2:
					temp_r31->unk6[temp_r30] = espEntry(0x41000C, 1, 0);
					espPriSet(temp_r31->unk6[temp_r30], 256);
					espScaleSet(temp_r31->unk6[temp_r30], 0.75, 0.75);
					break;
					
				case 3:
					temp_r31->unk6[temp_r30] = espEntry(0x41000D, 1, 0);
					espPriSet(temp_r31->unk6[temp_r30], 256);
					break;
					
				case 4:
					temp_r31->unk6[temp_r30] = espEntry(0x610033, 1, 0);
					espPriSet(temp_r31->unk6[temp_r30], 255);
					break;
			}
			espDispOff(temp_r31->unk6[temp_r30]);
			espDrawNoSet(temp_r31->unk6[temp_r30], 0);
			espAttrSet(temp_r31->unk6[temp_r30], 1);
			espPosSet(temp_r31->unk6[temp_r30], lbl_1_data_F0[temp_r29][0]+lbl_1_data_C0[temp_r30][0], lbl_1_data_F0[temp_r29][1]+lbl_1_data_C0[temp_r30][1]);
		}
		temp_r31->unk0 = -1;
	}
	HuDataDirClose(0x610000);
	object->func = fn_1_1470;
}

void fn_1_1470(omObjData *object)
{
	float temp_f31;
	Work1150 *temp_r31;
	s32 temp_r30;
	s32 temp_r29;
	temp_r31 = object->data;
	for(temp_r29=0; temp_r29<2; temp_r29++, temp_r31++) {
		if(temp_r31->unk0 >= 0) {
			if(temp_r31->unk0 == 0) {
				for(temp_r30=0; temp_r30<6; temp_r30++) {
					espDispOn(temp_r31->unk6[temp_r30]);
				}
				temp_r31->unk0++;
			}
			if(temp_r31->unk12) {
				temp_r31->unk12--;
				temp_f31 = (0.5*sind((180.0f*temp_r31->unk12)/16.0f))+1.0;
				espScaleSet(temp_r31->unk6[4], temp_f31, temp_f31);
				espScaleSet(temp_r31->unk6[5], temp_f31, temp_f31);
			}
			espBankSet(temp_r31->unk6[4], temp_r31->unk4/10);
			espBankSet(temp_r31->unk6[5], temp_r31->unk4%10);
		}
	}
}

void fn_1_1638(s32 arg0)
{
	Work1150 *temp_r31;
	s32 temp_r30;
	temp_r31 = lbl_1_bss_3C4->data;
	for(temp_r30=0; temp_r30<2; temp_r30++, temp_r31++) {
		temp_r31->unk0 = 0;
	}
}

void fn_1_1684(void)
{
	HuMemDirectFree(lbl_1_bss_3C4->data);
}

void fn_1_16B4(void)
{
	lbl_1_bss_39C = 0;
	lbl_1_bss_18 = 0;
}

void fn_1_16D8(void)
{
	CameraView *temp_r31 = &lbl_1_bss_1C[lbl_1_bss_39C++];
	temp_r31->zoom = CZoom;
	temp_r31->pos.x = Center.x;
	temp_r31->pos.y = Center.y;
	temp_r31->pos.z = Center.z;
	temp_r31->rot.x = CRot.x;
	temp_r31->rot.y = CRot.y;
	temp_r31->rot.z = CRot.z;
}

void fn_1_1788(void)
{
	CameraView *temp_r31 = &lbl_1_bss_1C[--lbl_1_bss_39C];
	CZoom = temp_r31->zoom;
	Center.x = temp_r31->pos.x;
	Center.y = temp_r31->pos.y;
	Center.z = temp_r31->pos.z;
	CRot.x = temp_r31->rot.x;
	CRot.y = temp_r31->rot.y;
	CRot.z = temp_r31->rot.z;
}

void fn_1_1838(CameraView *arg0)
{
	CameraView *temp_r30;
	CameraView sp8;
	sp8 = lbl_1_bss_1C[lbl_1_bss_39C++];
	temp_r30 = &sp8;
	memcpy(temp_r30, arg0, sizeof(CameraView));
	CZoom = arg0->zoom;
	Center.x = arg0->pos.x;
	Center.y = arg0->pos.y;
	Center.z = arg0->pos.z;
	CRot.x = arg0->rot.x;
	CRot.y = arg0->rot.y;
	CRot.z = arg0->rot.z;
}

void fn_1_1950(float arg0, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6)
{
	CameraView *temp_r31 = &lbl_1_bss_1C[lbl_1_bss_39C++];
	temp_r31->zoom = CZoom = arg0;
	temp_r31->pos.x = Center.x = arg1;
	temp_r31->pos.y = Center.y = arg2;
	temp_r31->pos.z = Center.z = arg3;
	temp_r31->rot.x = CRot.x = arg4;
	temp_r31->rot.y = CRot.y = arg5;
	temp_r31->rot.z = CRot.z = arg6;
}

void fn_1_1A00(s32 arg0)
{
	lbl_1_bss_18 = arg0;
}

#define LERP_PARAM(view1, view2, field, weight) ((view1)->field+)

void fn_1_1A10(float arg0)
{
	float weight;
	CameraView *view1 = &lbl_1_bss_1C[lbl_1_bss_39C-1];
	CameraView *view2 = view1-1;
	if(lbl_1_bss_39C < 2) {
		return;
	}
	switch(lbl_1_bss_18) {
		case 0:
			weight = arg0;
			break;
			
		case 1:
			weight = sind(90.0f*arg0);
			break;
			
		case 2:
			weight = sind(90.0f*arg0);
			weight *= weight;
			break;
	}
	
	CZoom = view1->zoom+(weight*(view2->zoom-view1->zoom));
	Center.x = view1->pos.x+(weight*(view2->pos.x-view1->pos.x));
	Center.y = view1->pos.y+(weight*(view2->pos.y-view1->pos.y));
	Center.z = view1->pos.z+(weight*(view2->pos.z-view1->pos.z));
	CRot.x = view1->rot.x+(weight*(view2->rot.x-view1->rot.x));
	CRot.y = view1->rot.y+(weight*(view2->rot.y-view1->rot.y));
	CRot.z = view1->rot.z+(weight*(view2->rot.z-view1->rot.z));
}

void fn_1_1C44(s32 arg0, s32 arg1)
{
	Work1150 *temp_r31 = &((Work1150 *)lbl_1_bss_3C4->data)[arg0];
	temp_r31->unk4 += arg1;
	temp_r31->unk12 = 16;
}

s32 fn_1_1C88(s32 arg0)
{
	Work1150 *temp_r31 = &((Work1150 *)lbl_1_bss_3C4->data)[arg0];
	return temp_r31->unk4;
}

s32 fn_1_1CB8(void)
{
	s32 temp_r31 = fn_1_1C88(0);
	s32 temp_r30 = fn_1_1C88(1);
	if(temp_r31 == temp_r30) {
		return 0;
	}
	if(temp_r31 > temp_r30) {
		return -1;
	} else {
		return 1;
	}
}

s16 fn_1_1D44(void)
{
	return lbl_1_bss_3C2;
}

s32 fn_1_1D54(void)
{
	return lbl_1_bss_10[0];
}

void fn_1_1D64(s32 arg0)
{
	lbl_1_bss_10[0] = arg0;
}

s32 fn_1_1D74(s32 arg0)
{
	return lbl_1_bss_3A0[arg0];
}

s32 fn_1_1D8C(void)
{
	return lbl_1_bss_3AA;
}

void fn_1_1D9C(void)
{
	lbl_1_bss_3A8 = 1;
}
