#include "REL/w02Dll.h"
#include "game/audio.h"
#include "game/pad.h"
#include "game/objsub.h"
#include "game/frand.h"
#include "game/chrman.h"

#include "ext_math.h"


Process *lbl_1_bss_378;
Process *lbl_1_bss_374;
s16 lbl_1_bss_370;
s16 lbl_1_bss_36E;
s16 lbl_1_bss_36C;
s16 lbl_1_bss_36A;
s16 lbl_1_bss_34C[15];
Vec lbl_1_bss_298[15];
Vec lbl_1_bss_1E4[15];
s16 lbl_1_bss_1C4[15];
s16 lbl_1_bss_1C0[2];
float lbl_1_bss_1BC;
Vec lbl_1_bss_1B0;
s16 lbl_1_bss_1AC;
Vec lbl_1_bss_1A0;

s32 lbl_1_data_490[8] = {
	0x0076002E,
	0x0076002F,
	0x00760030,
	0x00760031,
	0x00760032,
	0x00760033,
	0x00760034,
	0x00760035
};

s32 lbl_1_data_4B0[8] = {
	0x00760026,
	0x00760027,
	0x00760028,
	0x00760029,
	0x0076002A,
	0x0076002B,
	0x0076002C,
	0x0076002D
};

s32 fn_1_9250(void)
{
	s32 temp_r31;
	Vec sp14;
	Vec sp8;
	BoardModelVisibilitySet(lbl_1_bss_30[13], 1);
	BoardModelVisibilitySet(lbl_1_bss_30[14], 1);
	sp8.x = sp8.y = sp8.z = 0;
	BoardModelRotSetV(lbl_1_bss_30[13], &sp8);
	BoardModelRotSetV(lbl_1_bss_30[14], &sp8);
	BoardModelPosSetV(lbl_1_bss_30[13], &lbl_1_bss_20);
	BoardModelPosSetV(lbl_1_bss_30[14], &lbl_1_bss_14);
	BoardModelVisibilitySet(lbl_1_bss_2E, 1);
	BoardModelVisibilitySet(lbl_1_bss_2C, 1);
	temp_r31 = BoardSpaceFlagSearch(0, 0x200);
	BoardSpacePosGet(0, temp_r31, &sp14);
	BoardModelPosSetV(lbl_1_bss_2E, &sp14);
	BoardModelRotSetV(lbl_1_bss_2E, &sp8);
	temp_r31 = BoardSpaceFlagSearch(0, 0x400);
	BoardSpacePosGet(0, temp_r31, &sp14);
	BoardModelPosSetV(lbl_1_bss_2C, &sp14);
	BoardModelRotSetV(lbl_1_bss_2C, &sp8);
	return 1;
}

s32 fn_1_94AC(void);
void fn_1_94C0(void);

void fn_1_93C8(u32 arg0)
{
	BoardEventFlagSet();
	if(arg0 < 2) {
		lbl_1_bss_370 = 0;
	} else {
		lbl_1_bss_370 = 1;
	}
	lbl_1_bss_36E = GWSystem.player_curr;
	BoardPlayerPostTurnHookSet(lbl_1_bss_36E, fn_1_9250);
	lbl_1_bss_378 = HuPrcCreate(fn_1_94C0, 8196, 8192, 0);
	HuPrcDestructorSet2(lbl_1_bss_378, (void *)fn_1_94AC);
	while(lbl_1_bss_378) {
		HuPrcVSleep();
	}
	BoardEventFlagReset();
}

s32 fn_1_94AC(void)
{
	lbl_1_bss_378 = NULL;
}

void fn_1_98D8(void);
void fn_1_9EC4(void);
void fn_1_A558(void);
void fn_1_A8E8(void);
void fn_1_B450(s32 arg0);

void fn_1_94C0(void)
{
	s32 temp_r31;
	s32 temp_r30;
	Vec sp10;
	float sp8[2];
	if(lbl_1_bss_370) {
		BoardModelVisibilitySet(lbl_1_bss_2E, 0);
		BoardModelVisibilitySet(lbl_1_bss_30[13], 0);
		lbl_1_bss_36A = lbl_1_bss_30[14];
		lbl_1_bss_36C = lbl_1_bss_2C;
		sp10.x = sp10.z = 0;
		sp10.y = -90;
		temp_r30 = BoardSpaceFlagSearch(0, 0x40);
	} else {
		BoardModelVisibilitySet(lbl_1_bss_2C, 0);
		BoardModelVisibilitySet(lbl_1_bss_30[14], 0);
		lbl_1_bss_36A = lbl_1_bss_30[13];
		lbl_1_bss_36C = lbl_1_bss_2E;
		sp10.x = sp10.z = 0;
		sp10.y = 90;
		temp_r30 = BoardSpaceFlagSearch(0, 0x100);
	}
	lbl_1_bss_1C0[0] = BoardPlayerMotionCreate(lbl_1_bss_36E, lbl_1_data_490[GWPlayer[lbl_1_bss_36E].character]);
	lbl_1_bss_1C0[1] = BoardPlayerMotionCreate(lbl_1_bss_36E, lbl_1_data_4B0[GWPlayer[lbl_1_bss_36E].character]);
	fn_1_98D8();
	BoardModelRotSetV(lbl_1_bss_36A, &sp10);
	BoardCameraMoveSet(0);
	BoardCameraTargetPlayerSet(lbl_1_bss_36E);
	BoardCameraRotSet(-10, -sp10.y);
	BoardCameraZoomSet(900);
	BoardStatusShowSetAll(0);
	HuWinMesMaxSizeGet(1, sp8, 0x13001C);
	lbl_1_bss_1AC = HuWinCreate(-10000, 400, sp8[0], sp8[1], 0);
	HuWinMesSet(lbl_1_bss_1AC, 0x13001C);
	HuWinBGTPLvlSet(lbl_1_bss_1AC, 0);
	HuWinMesSpeedSet(lbl_1_bss_1AC, 0);
	fn_1_9EC4();
	BoardAudSeqPause(0, 1, 1000);
	HuPrcSleep(45);
	BoardCameraTargetGet(&lbl_1_bss_1A0);
	BoardCameraTargetModelSet(-1);
	fn_1_A558();
	HuAudPlayerVoicePlay(lbl_1_bss_36E, 291);
	fn_1_A8E8();
	HuPrcKill(lbl_1_bss_374);
	for(temp_r31=0; temp_r31<15; temp_r31++) {
		BoardModelKill(lbl_1_bss_34C[temp_r31]);
		
	}
	BoardStatusShowSetAll(1);
	BoardCameraMoveSet(0);
	BoardCameraViewSet(1);
	BoardCameraMotionWait();
	BoardCameraMoveSet(1);
	BoardAudSeqPause(0, 0, 1000);
	fn_1_B450(temp_r30);
	BoardPlayerMotionKill(lbl_1_bss_36E, lbl_1_bss_1C0[0]);
	BoardPlayerMotionKill(lbl_1_bss_36E, lbl_1_bss_1C0[1]);
	HuPrcEnd();
}

void fn_1_98D8(void)
{
	Vec sp1C;
	Vec sp10;
	float temp_f27;
	float temp_f26;
	float temp_f23;
	float temp_f22;
	BoardModelPosGet(lbl_1_bss_36C, &lbl_1_bss_1B0);
	BoardPlayerPosGet(lbl_1_bss_36E, &sp1C);
	temp_f23 = atan2d(lbl_1_bss_1B0.x-sp1C.x, lbl_1_bss_1B0.z-sp1C.z);
	BoardPlayerMotBlendSet(lbl_1_bss_36E, temp_f23, 15);
	while(!BoardPlayerMotBlendCheck(lbl_1_bss_36E)) {
		HuPrcVSleep();
	}
	BoardCameraTargetModelSet(-1);
	temp_f26 = VECDistanceXZ(&lbl_1_bss_1B0, &sp1C);
	VECSubtract(&lbl_1_bss_1B0, &sp1C, &sp10);
	VECNormalize(&sp10, &sp10);
	VECScale(&sp10, &sp10, temp_f26/45.0f);
	BoardPlayerMotionStart(lbl_1_bss_36E, 4, 0);
	
	temp_f27 = 0;
	temp_f22 = 15;
	while(1) {
		sp10.y = temp_f22-(0.075f*(0.25f*(temp_f27*temp_f27)));
		temp_f27++;
		VECAdd(&sp1C, &sp10, &sp1C);
		temp_f26 = VECDistanceXZ(&lbl_1_bss_1B0, &sp1C);
		if(temp_f26 < 5.0f) {
			sp10.x = sp10.z = 0;
			sp1C.x = lbl_1_bss_1B0.x;
			sp1C.z = lbl_1_bss_1B0.z;
		}
		if(sp1C.y <= lbl_1_bss_1B0.y+8.5f) {
			sp1C.y = lbl_1_bss_1B0.y+8.5f;
			break;
		}
		BoardPlayerPosSetV(lbl_1_bss_36E, &sp1C);
		HuPrcVSleep();
	}
	BoardPlayerPosSetV(lbl_1_bss_36E, &sp1C);
	BoardPlayerIdleSet(lbl_1_bss_36E);
	HuPrcSleep(8);
	if(lbl_1_bss_370) {
		BoardPlayerMotBlendSet(lbl_1_bss_36E, -90, 15);
	} else {
		BoardPlayerMotBlendSet(lbl_1_bss_36E, 90, 15);
	}
	while(!BoardPlayerMotBlendCheck(lbl_1_bss_36E)) {
		HuPrcVSleep();
	}
	BoardPlayerMotionShiftSet(lbl_1_bss_36E, lbl_1_bss_1C0[0], 0, 10, 0x40000001);
	HuPrcSleep(20);
	
}

void fn_1_BB30(void);

void fn_1_9EC4(void)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	float temp_f27;
	
	s32 sp80[15];
	float sp44[15];
	float sp8[15];
	s32 temp_r31;
	s32 temp_r30;
	for(temp_r31=0; temp_r31<15; temp_r31++) {
		lbl_1_bss_34C[temp_r31] = BoardModelCreate(0x7000A, NULL, 1);
		BoardModelVisibilitySet(lbl_1_bss_34C[temp_r31], 0);
		lbl_1_bss_1C4[temp_r31] = 1;
	}
	temp_f31 = ((1.0f/255.0f)*(90.0f*frand8()))+45;
	if(frandBool()) {
		temp_f31 += 180.0f;
	}
	if(lbl_1_bss_370) {
		temp_f30 = 1430;
		temp_f29 = -1730;
	} else {
		temp_f30 = -1730;
		temp_f29 = 1430;
	}
	temp_f27 = (temp_f29-temp_f30)/15.0f;
	for(temp_r31=0; temp_r31<15; temp_r31++) {
		lbl_1_bss_298[temp_r31].x = temp_f30+(temp_f27*temp_r31);
		lbl_1_bss_298[temp_r31].z = -2100+(190*sind(temp_f31));
		lbl_1_bss_298[temp_r31].y = (500.0f+(50.0f+lbl_1_bss_1B0.y))+(temp_r31*50)+(400.0f*((1.0f/255.0f)*frand8()));
		temp_f31 += 60.0f;
		lbl_1_bss_1E4[temp_r31].x = lbl_1_bss_1E4[temp_r31].z = 0;
		lbl_1_bss_1E4[temp_r31].y = (360.0f*((1.0f/255.0f)*frand8()));
		BoardModelVisibilitySet(lbl_1_bss_34C[temp_r31], 1);
		BoardModelPosSetV(lbl_1_bss_34C[temp_r31], &lbl_1_bss_298[temp_r31]);
		BoardModelRotSetV(lbl_1_bss_34C[temp_r31], &lbl_1_bss_1E4[temp_r31]);
	}
	lbl_1_bss_374 = HuPrcCreate(fn_1_BB30, 8196, 2048, 0);
	for(temp_r31=0; temp_r31<15; temp_r31++) {
		sp8[temp_r31] = sp44[temp_r31] = 0;
		sp80[temp_r31] = 1;
	}
	while(1) {
		temp_r30 = 0;
		for(temp_r31=0; temp_r31<15; temp_r31++) {
			if(sp80[temp_r31] == 1) {
				temp_f28 = sp44[temp_r31]-((1.0f/15.0f)*(0.25f*(sp8[temp_r31]*sp8[temp_r31])));
				lbl_1_bss_298[temp_r31].y += temp_f28;
				if(lbl_1_bss_298[temp_r31].y <= 50.0f+lbl_1_bss_1B0.y) {
					lbl_1_bss_298[temp_r31].y = 50.0f+lbl_1_bss_1B0.y;
					sp44[temp_r31] = -temp_f28*0.2f;
					sp8[temp_r31] = 0;
					if(sp44[temp_r31] < 5.0f) {
						sp44[temp_r31] = 0;
						sp80[temp_r31] = 0;
					}
					HuAudFXPlay(18);
				}
				BoardModelPosSetV(lbl_1_bss_34C[temp_r31], &lbl_1_bss_298[temp_r31]);
				sp8[temp_r31]++;
			} else {
				temp_r30++;
			}
		}
		if(temp_r30 == 15) {
			break;
		}
		HuPrcVSleep();
	}
}

void fn_1_A558(void)
{
	Vec sp2C;
	Vec sp20;
	Vec sp14;
	Vec sp8;
	float temp_f31;
	s32 temp_r31;
	BoardMusStart(1, 20, 127, 0);
	BoardModelPosGet(lbl_1_bss_36A, &sp2C);
	BoardModelMotionStart(lbl_1_bss_36A, 2, 0x40000001);
	for(temp_r31=0; temp_r31<60; temp_r31++) {
		if(lbl_1_bss_370) {
			sp2C.x += 5.0f;
		} else {
			sp2C.x -= 5.0f;
		}
		BoardModelPosSetV(lbl_1_bss_36A, &sp2C);
		HuPrcVSleep();
	}
	BoardModelRotGet(lbl_1_bss_36A, &sp14);
	BoardPlayerPosGet(lbl_1_bss_36E, &sp20);
	VECSubtract(&sp20, &sp2C, &sp8);
	temp_f31 = VECMag(&sp8);
	sp14.y = atan2d(lbl_1_bss_298[0].x-sp20.x, lbl_1_bss_298[0].z-sp20.z);
	sp2C.x = sp20.x+(temp_f31*sind(sp14.y-180.0f));
	sp2C.z = sp20.z+(temp_f31*cosd(sp14.y-180.0f));
	BoardModelPosSetV(lbl_1_bss_36A, &sp2C);
	BoardModelRotSetV(lbl_1_bss_36A, &sp14);
	lbl_1_bss_1BC = sp14.y;
	HuPrcSleep(20);
	BoardModelMotionStart(lbl_1_bss_36A, 3, 0x40000001);
	BoardModelMotionSpeedSet(lbl_1_bss_36A, 4.0f);
	VECSubtract(&sp20, &sp2C, &sp8);
	temp_f31 = ((VECMag(&sp8)-50)-50)/20;
	VECNormalize(&sp8, &sp8);
	VECScale(&sp8, &sp8, temp_f31);
	for(temp_r31=0; temp_r31<20; temp_r31++) {
		VECAdd(&sp2C, &sp8, &sp2C);
		BoardModelPosSetV(lbl_1_bss_36A, &sp2C);
		HuPrcVSleep();
	}
	BoardModelMotionStart(lbl_1_bss_36A, 1, 0x40000001);
	BoardModelMotionSpeedSet(lbl_1_bss_36A, 1.0f);
	omVibrate(lbl_1_bss_36E, 12, 4, 2);
	HuAudFXPlay(1069);
}

void fn_1_B8A8(s8 *arg0);

void fn_1_A8E8(void)
{
	Vec sp28;
	Vec sp1C;
	Vec sp10;
	s8 sp8;
	float temp_f29;
	float temp_f28;
	float temp_f27;
	float temp_f26;
	float temp_f25;
	s16 temp_r31;
	s8 temp_r30;
	s16 temp_r29;
	temp_r29 = GWPlayer[lbl_1_bss_36E].port;
	if(lbl_1_bss_370) {
		temp_f27 = 2430;
		temp_f26 = -1830;
	} else {
		temp_f27 = -2730;
		temp_f26 = 1530;
	}
	temp_f25 = (temp_f26-temp_f27)/2;
	while(1) {
		temp_r30 = 0;
		BoardPlayerPosGet(lbl_1_bss_36E, &sp28);
		if(GWPlayer[lbl_1_bss_36E].com) {
			fn_1_B8A8(&sp8);
		} else {
			sp8 = HuPadStkX[temp_r29];
		}
		temp_f28 = -sp8*0.025f;
		if(lbl_1_bss_370) {
			if(lbl_1_bss_1BC < -90.0f) {
				lbl_1_bss_1BC += temp_f28;
				if(lbl_1_bss_1BC < -165.0f) {
					lbl_1_bss_1BC = -165.0f;
				}
				if(lbl_1_bss_1BC > -105.0f) {
					lbl_1_bss_1BC = -105.0f;
				}
			} else {
				lbl_1_bss_1BC += temp_f28;
				if(lbl_1_bss_1BC < -75.0f) {
					lbl_1_bss_1BC = -75.0f;
				}
				if(lbl_1_bss_1BC > -15.0f) {
					lbl_1_bss_1BC = -15.0f;
				}
			}
		} else {
			if(lbl_1_bss_1BC > 90.0f) {
				lbl_1_bss_1BC += temp_f28;
				if(lbl_1_bss_1BC > 165.0f) {
					lbl_1_bss_1BC = 165.0f;
				}
				if(lbl_1_bss_1BC < 105.0f) {
					lbl_1_bss_1BC = 105.0f;
				}
			} else {
				lbl_1_bss_1BC += temp_f28;
				if(lbl_1_bss_1BC > 75.0f) {
					lbl_1_bss_1BC = 75.0f;
				}
				if(lbl_1_bss_1BC < 15.0f) {
					lbl_1_bss_1BC = 15.0f;
				}
			}
		}
		temp_f29 = 4.0+(15.0*(1.0-fabs((sp28.x-(temp_f25+temp_f27))/temp_f25)));
		sp28.x += temp_f29*sind(lbl_1_bss_1BC);
		sp28.z += temp_f29*cosd(lbl_1_bss_1BC);
		if(lbl_1_bss_370) {
			if(sp28.z-50 < -2340) {
				sp28.z = -2290;
				lbl_1_bss_1BC = (-90-lbl_1_bss_1BC)+-90;
				temp_r30 = 1;
			} else if(sp28.z+50 > -1860) {
				lbl_1_bss_1BC = (-90-lbl_1_bss_1BC)+-90;
				sp28.z = -1910;
				temp_r30 = 1;
			}
		} else {
			if(sp28.z-50 < -2340) {
				sp28.z = -2290;
				lbl_1_bss_1BC = (90-lbl_1_bss_1BC)+90;
				temp_r30 = 1;
			} else if(sp28.z+50 > -1860) {
				lbl_1_bss_1BC = (90-lbl_1_bss_1BC)+90;
				sp28.z = -1910;
				temp_r30 = 1;
			}
		}
		BoardPlayerPosSetV(lbl_1_bss_36E, &sp28);
		sp28.y -= 8.5f;
		BoardModelPosSetV(lbl_1_bss_36C, &sp28);
		if(temp_r30) {
			HuAudFXPlay(1060);
		}
		BoardPlayerRotGet(lbl_1_bss_36E, &sp1C);
		sp1C.y += 1.25f*temp_f29;
		if(sp1C.y >= 360.0f) {
			sp1C.y -= 360.0f;
		}
		BoardPlayerRotSetV(lbl_1_bss_36E, &sp1C);
		BoardModelRotGet(lbl_1_bss_36C, &sp1C);
		sp1C.y += 1.25f*temp_f29;
		if(sp1C.y >= 360.0f) {
			sp1C.y -= 360.0f;
		}
		BoardModelRotSetV(lbl_1_bss_36C, &sp1C);
		for(temp_r31=0; temp_r31<15; temp_r31++) {
			if(lbl_1_bss_1C4[temp_r31] == 0) {
				continue;
			}
			BoardModelPosGet(lbl_1_bss_34C[temp_r31], &sp10);
			if(VECDistanceXZ(&sp10, &sp28) < 100.0f) {
				lbl_1_bss_1C4[temp_r31] = 0;
				BoardModelVisibilitySet(lbl_1_bss_34C[temp_r31], 0);
				CharModelCoinEffectCreate(1, &sp10);
				BoardPlayerCoinsAdd(lbl_1_bss_36E, 1);
				HuAudFXPlay(7);
			}
		}
		lbl_1_bss_1A0.x = sp28.x;
		BoardCameraTargetSet(lbl_1_bss_1A0.x, lbl_1_bss_1A0.y, lbl_1_bss_1A0.z);
		if(temp_f29 <= 3.0f) {
			break;
		}
		HuPrcVSleep();
	}
	HuWinKill(lbl_1_bss_1AC);
	BoardPlayerMotionStart(lbl_1_bss_36E, lbl_1_bss_1C0[1], 0);
	BoardPlayerMotionEndWait(lbl_1_bss_36E);
	BoardPlayerMotionShiftSet(lbl_1_bss_36E, 6, 0, 15, 0x40000001);
	HuPrcSleep(40);
	BoardAudSeqFadeOut(1, 1000);
	HuPrcSleep(70);
	BoardPlayerMotBlendSet(lbl_1_bss_36E, 0, 1);
}

void fn_1_B450(s32 arg0)
{
	float temp_f27;
	float temp_f26;
	float temp_f23;
	Vec sp28;
	Vec sp1C;
	Vec sp10;
	BoardSpacePosGet(0, arg0, &sp28);
	BoardPlayerPosGet(lbl_1_bss_36E, &sp1C);
	HuAudPlayerVoicePlay(lbl_1_bss_36E, 290);
	temp_f26 = VECDistanceXZ(&sp28, &sp1C);
	VECSubtract(&sp28, &sp1C, &sp10);
	VECNormalize(&sp10, &sp10);
	VECScale(&sp10, &sp10, temp_f26/45.0f);
	BoardPlayerMotionStart(lbl_1_bss_36E, 4, 0);
	temp_f27 = 0;
	temp_f23 = 15;
	while(1) {
		sp10.y = temp_f23-(0.075f*(0.25f*(temp_f27*temp_f27)));
		temp_f27++;
		VECAdd(&sp1C, &sp10, &sp1C);
		temp_f26 = VECDistanceXZ(&sp28, &sp1C);
		if(temp_f26 < 5.0f) {
			sp10.x = sp10.z = 0;
			sp1C.x = sp28.x;
			sp1C.z = sp28.z;
		}
		if(sp1C.y <= sp28.y) {
			sp1C.y = sp28.y;
			break;
		}
		BoardPlayerPosSetV(lbl_1_bss_36E, &sp1C);
		HuPrcVSleep();
	}
	BoardPlayerPosSetV(lbl_1_bss_36E, &sp1C);
	GWPlayer[lbl_1_bss_36E].space_curr = arg0;
	BoardPlayerIdleSet(lbl_1_bss_36E);
	HuPrcSleep(8);
	HuPrcSleep(20);
}

void fn_1_B8A8(s8 *arg0)
{
	float temp_f29;
	float temp_f28;
	Vec spC;
	s32 temp_r31;
	s32 temp_r29;
	*arg0 = 0;
	BoardPlayerPosGet(lbl_1_bss_36E, &spC);
	temp_f29 = -1000;
	temp_r29 = -1;
	for(temp_r31=0; temp_r31<15; temp_r31++) {
		if(lbl_1_bss_1C4[temp_r31] == 0) {
			continue;
		}
		temp_f28 = VECDistanceXZ(&spC, &lbl_1_bss_298[temp_r31]);
		if(temp_f28 > temp_f29) {
			temp_f29 = temp_f28;
			temp_r29 = temp_r31;
		}
	}
	if(temp_r29 >= 0) {
		if(spC.z > lbl_1_bss_298[temp_r31].z) {
			*arg0 = -70;
		} else {
			*arg0 = 70;
		}
		if(lbl_1_bss_370) {
			*arg0 = -(*arg0);
		}
	}
}

void fn_1_BB30(void)
{
	s32 temp_r31;
	while(1) {
		for(temp_r31=0; temp_r31<15; temp_r31++) {
			if(lbl_1_bss_1C4[temp_r31] == 0) {
				continue;
			}
			lbl_1_bss_1E4[temp_r31].y += 10.0f;
			if(lbl_1_bss_1E4[temp_r31].y >= 360.0f) {
				lbl_1_bss_1E4[temp_r31].y -= 360.0f;
			}
			BoardModelRotSetV(lbl_1_bss_34C[temp_r31], &lbl_1_bss_1E4[temp_r31]);
		}
		HuPrcVSleep();
	}
	
}