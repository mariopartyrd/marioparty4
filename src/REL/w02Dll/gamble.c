#include "REL/w02Dll.h"
#include "game/audio.h"
#include "game/pad.h"
#include "game/objsub.h"

#include "game/board/basic_space.h"

s32 lbl_1_bss_54;
Process* lbl_1_bss_50;

void fn_1_2D04(void)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	
	m02GenDice spEC;
	m02GenDice sp4C;
	s32 sp24[10] = {
		DATA_MAKE_NUM(DATADIR_W02, 0x1C),
		DATA_MAKE_NUM(DATADIR_W02, 0x1D),
		DATA_MAKE_NUM(DATADIR_W02, 0x1E),
		DATA_MAKE_NUM(DATADIR_W02, 0x1F),
		DATA_MAKE_NUM(DATADIR_W02, 0x20),
		DATA_MAKE_NUM(DATADIR_W02, 0x21),
		DATA_MAKE_NUM(DATADIR_W02, 0x22),
		DATA_MAKE_NUM(DATADIR_W02, 0x23),
		DATA_MAKE_NUM(DATADIR_W02, 0x24),
		DATA_MAKE_NUM(DATADIR_W02, 0x25)
	};
	Vec sp18;
	Vec spC;
	BoardSpace *sp8;
	s32 temp_r31;
	s16 temp_r30;
	s32 temp_r29;
	s16 temp_r28;
	s32 temp_r27;
	s32 temp_r26;
	s32 temp_r25;
	u16 temp_r24;
	temp_r31 = GWSystem.player_curr;
	OSReport("gamble start %d\n", temp_r31);
	sp8 = BoardSpaceGet(0, GWPlayer[temp_r31].space_curr);
	BoardRollDispSet(0);
	temp_r28 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x0F), NULL, 0);
	BoardModelVisibilitySet(temp_r28, 0);
	switch(lbl_1_bss_54) {
		case 0:
			temp_r30 = lbl_1_bss_30[0];
			break;
			
		case 1:
			temp_r30 = lbl_1_bss_30[1];
			break;
			
		case 2:
			temp_r30 = lbl_1_bss_30[2];
			break;
	}
	BoardPlayerIdleSet(temp_r31);
	BoardPlayerMotBlendSet(temp_r31, -90, 30);
	while(!BoardPlayerMotBlendCheck(temp_r31)) {
		HuPrcVSleep();
	}
	BoardCameraViewSet(3);
	BoardCameraMotionWait();
	BoardModelMotionStart(lbl_1_data_286, 1, 0x40000001);
	BoardModelHookSet(temp_r30, "kuri", lbl_1_data_286);
	BoardModelVisibilitySet(lbl_1_data_286, 1);
	BoardModelMotionTimeSet(temp_r30, 0);
	BoardModelAttrReset(temp_r30, 0x40000002);
	HuAudFXPlay(813);
	while(BoardModelMotionTimeGet(temp_r30) < 30.0f) {
		HuPrcVSleep();
	}
	BoardModelAttrSet(temp_r30, 0x40000002);
	BoardModelHookReset(temp_r30);
	BoardModelPosGet(temp_r30, &sp18);
	BoardModelPosSetV(lbl_1_data_286, &sp18);
	fn_1_121C(MAKE_MESSID(0x13, 0x0A));
	spEC.unk00 = 1;
	spEC.unk04 = DATA_MAKE_NUM(DATADIR_W02, 0x1B);
	spEC.unk08 = sp24;
	spEC.unk0C = sp18;
	spEC.unk18 = 1;
	spEC.unk1A = 10;
	spEC.unk22 = 0;
	spEC.unk24 = 1;
	temp_r25 = frandmod(100);
	if(temp_r25 <= 59) {
		spEC.unk1C[0] = frandmod(4)+4;
	} else if(temp_r25 <= 89) {
		if(temp_r25 & 0x1) {
			spEC.unk1C[0] = 2;
		} else {
			spEC.unk1C[0] = 8;
		}
		spEC.unk1C[0] += frand() & 0x1;
	} else {
		if(temp_r25 & 0x1) {
			spEC.unk1C[0] = 1;
		} else {
			spEC.unk1C[0] = 10;
		}
	}
	fn_1_1254(&spEC);
	while(!fn_1_17F4(&spEC)) {
		HuPrcVSleep();
	}
	temp_r29 = frandmod(45)+45;
	HuPrcSleep(temp_r29);
	BoardModelPosGet(lbl_1_data_286, &spC);
	BoardModelMotionStart(lbl_1_data_286, 4, 0);
	temp_f29 = 15;
	temp_f31 = 0;
	while(1) {
		temp_f30 = temp_f29-(0.08166667f*(0.25f*(temp_f31*temp_f31)));
		temp_f31++;
		spC.y += temp_f30;
		if(spC.y >= (250.0f+sp18.y)-130.0f) {
			spC.y = (250.0f+sp18.y)-130.0f;
			temp_f29 = -10;
			temp_f31 = 0;
			spEC.unk9C = 1;
		}
		if(spC.y <= sp18.y) {
			spC.y = sp18.y;
			spEC.unk9C = 0;
			break;
		}
		BoardModelPosSetV(lbl_1_data_286, &spC);
		HuPrcVSleep();
	}
	BoardModelPosSetV(lbl_1_data_286, &sp18);
	BoardModelMotionStart(lbl_1_data_286, 1, 0x40000001);
	while(spEC.unk28 == 0) {
		HuPrcVSleep();
	}
	temp_r27 = spEC.unk94;
	if(temp_r27 == 10) {
		HuAudPlayerVoicePlay(temp_r31, 302);
		fn_1_121C(MAKE_MESSID(0x13, 0x10));
	} else {
		fn_1_121C(MAKE_MESSID(0x13, 0x0C));
	}
	BoardPlayerMotBlendSet(temp_r31, 0, 15);
	while(!BoardPlayerMotBlendCheck(temp_r31)) {
		HuPrcVSleep();
	}
	BoardCameraTargetModelSet(-1);
	if(temp_r27 != 10) {
		sp4C = spEC;
		BoardPlayerPosGet(temp_r31, &sp4C.unk0C);
		sp4C.unk24 = 1;
		sp4C.unk1C[0] = frandmod(10)+1;
		if(sp4C.unk1C[0] == temp_r27) {
			if(sp4C.unk1C[0] == 9) {
				sp4C.unk1C[0]--;
			} else {
				sp4C.unk1C[0]++;
			}
		}
		fn_1_1254(&sp4C);
		while(!fn_1_17F4(&sp4C)) {
			HuPrcVSleep();
		}
		temp_r24 = 0;
		while(!(temp_r24 & PAD_BUTTON_A)) {
			HuPrcVSleep();
			if(GWPlayer[temp_r31].com) {
				temp_r29 = frandmod(45)+20;
				HuPrcSleep(temp_r29);
				temp_r24 = PAD_BUTTON_A;
			} else {
				temp_r24 = HuPadBtnDown[GWPlayer[temp_r31].port];
			}
		}
		BoardPlayerDiceJumpStart(temp_r31);
		while(!BoardPlayerDiceJumpCheck(temp_r31)) {
			HuPrcVSleep();
		}
		sp4C.unk9C = 1;
		while(GWPlayer[temp_r31].jump) {
			HuPrcVSleep();
		}
		sp4C.unk9C = 0;
		while(sp4C.unk28 == 0) {
			HuPrcVSleep();
		}
		if(sp4C.unk94 > temp_r27) {
			fn_1_121C(MAKE_MESSID(0x13, 0x0D));
		} else {
			HuAudPlayerVoicePlay(temp_r31, 302);
			fn_1_121C(MAKE_MESSID(0x13, 0x0F));
		}
	} else {
		sp4C.unk94 = 0;
	}
	fn_1_1518(&spEC);
	if(temp_r27 != 10) {
		fn_1_1518(&sp4C);
	}
	BoardPlayerPosGet(temp_r31, &spC);
	if(sp4C.unk94 > temp_r27) {
		spC.y += 250.0f;
		HuAudFXPlay(839);
		temp_r29 = BoardCoinChgCreate(&spC, 10);
		while(!BoardCoinChgExist(temp_r29)) {
			HuPrcVSleep();
		}
		for(temp_r29=0; temp_r29<10; temp_r29++) {
			BoardPlayerCoinsAdd(temp_r31, 1);
			HuAudFXPlay(7);
			HuPrcSleep(6);
		}
		fn_1_121C(MAKE_MESSID(0x13, 0x0E));
	} else {
		temp_r26 = GWPlayer[temp_r31].space_curr;
		BoardCameraTargetSpaceSet(temp_r26);
		BoardPlayerMotionShiftSet(temp_r31, 6, 0, 5, 0x40000001);
		HuPrcSleep(60);
		HuPrcSleep(30);
		BoardModelPosSetV(temp_r28, &spC);
		BoardModelMotionTimeSet(temp_r28, 0);
		BoardModelVisibilitySet(temp_r28, 1);
		HuAudFXPlay(1058);
		while(BoardModelMotionTimeGet(temp_r28) < BoardModelMotionMaxTimeGet(temp_r28)) {
			HuPrcVSleep();
		}
		omVibrate(temp_r31, 12, 4, 2);
		temp_f30 = -4;
		for(temp_r29=0; temp_r29<30; temp_r29++) {
			spC.y += temp_f30;
			temp_f30 *= 1.08f;
			BoardPlayerPosSetV(temp_r31, &spC);
			HuPrcVSleep();
		}
		temp_r26 = BoardSpaceFlagSearch(0, 0x80000000);
		BoardCameraMoveSet(0);
		BoardCameraTargetSpaceSet(temp_r26);
		HuPrcVSleep();
		BoardCameraMoveSet(1);
		BoardSpacePosGet(0, temp_r26, &sp18);
		spC = sp18;
		spC.y -= 180.0f;
		BoardPlayerPosSetV(temp_r31, &spC);
		GWPlayer[temp_r31].space_curr = temp_r26;
		HuPrcSleep(15);
		BoardModelPosSetV(temp_r28, &sp18);
		BoardModelMotionTimeSet(temp_r28, 0);
		HuAudFXPlay(1058);
		while(BoardModelMotionTimeGet(temp_r28) < BoardModelMotionMaxTimeGet(temp_r28)) {
			HuPrcVSleep();
		}
		HuPrcSleep(15);
		temp_f29 = 22;
		temp_f31 = 1;
		while(1) {
			temp_f30 = temp_f29-((90.0f/1200.0f)*(0.25f*(temp_f31*temp_f31)));
			temp_f31++;
			spC.y += temp_f30;
			if(spC.y >= sp18.y) {
				BoardModelAttrSet(temp_r28, 0x40000004);
			}
			if(temp_f30 < 0 && spC.y <= sp18.y) {
				omVibrate(temp_r31, 12, 4, 2);
				temp_f29 = -temp_f30*0.31f;
				temp_f31 = 1;
				HuAudFXPlay(1068);
				if(fabs(temp_f29) <= 5.0) {
					break;
				}
				spC.y = sp18.y;
			}
			
			BoardPlayerPosSetV(temp_r31, &spC);
			HuPrcVSleep();
		}
		BoardPlayerPosSetV(temp_r31, &sp18);
		HuPrcSleep(90);
		BoardPlayerIdleSet(temp_r31);
		HuPrcSleep(9);
		BoardCameraTargetPlayerSet(temp_r31);
	}
	BoardModelHookSet(temp_r30, "kuri", lbl_1_data_286);
	BoardModelAttrReset(temp_r30, 0x40000002);
	if(sp4C.unk94 > temp_r27) {
		HuPrcSleep(10);
		HuAudFXPlay(815);
	}
	while(BoardModelMotionTimeGet(temp_r30) < BoardModelMotionMaxTimeGet(temp_r30)) {
		HuPrcVSleep();
	}
	BoardModelHookReset(temp_r30);
	BoardCameraViewSet(1);
	BoardCameraMotionWait();
	BoardRollDispSet(1);
	BoardModelVisibilitySet(lbl_1_data_286, 0);
	BoardModelKill(temp_r28);
	HuPrcKill(NULL);
	while(1) {
		HuPrcVSleep();
	}
}


void fn_1_3938(void) {
    lbl_1_bss_50 = NULL;
}


void fn_1_394C(s32 arg0) {
    s32 currPlayer;
    currPlayer = GWSystem.player_curr;

    lbl_1_bss_54 = arg0;
    lbl_1_bss_50 = HuPrcChildCreate(fn_1_2D04, 0x2003U, 0x2000U, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_50, fn_1_3938);
    while (lbl_1_bss_50) {
        HuPrcVSleep();
    }
}
