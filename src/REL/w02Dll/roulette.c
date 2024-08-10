#include "REL/w02Dll.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/chrman.h"
#include "game/pad.h"

#include "ext_math.h"


/* DATA */
s32 lbl_1_data_4D0[] = {
	-1, 2, 2, 2,
	-1, 1, 1, 1,
	-1, 0, 0, 0,
	-1, 3, 3, 3
};

Process *lbl_1_bss_38C;
s16 lbl_1_bss_388;
s32 lbl_1_bss_384;
float lbl_1_bss_380;

//Local Functions
void fn_1_D3AC(void);
s32 fn_1_D8C4(void);
void fn_1_DF48(void);

s32 fn_1_E2AC(void);
void fn_1_E310(f32);

// Unknown Structures
typedef struct UnkPoint {
    f32 unk00;
    Vec point;
} UnkPoint;


/* FUNCTIONS */
void fn_1_BC1C(void) {
    Point3d sp8;

    BoardModelPosGet(lbl_1_bss_30[15], &sp8);
    sp8.z -= 90.0f;
    sp8.y += 50.0f;
    BoardModelPosSetV(lbl_1_bss_30[6], &sp8);
    BoardModelAttrSet(lbl_1_bss_30[5], 0x40000002);
    BoardModelMotionTimeSet(lbl_1_bss_30[5], 0.0f);
    BoardModelRotGet(lbl_1_bss_30[15], &sp8);
    sp8.y = 0.0f;
    BoardModelRotSetV(lbl_1_bss_30[15], &sp8);
}

void fn_1_BCFC(void) {
    s32 spaceLinkFlags;
    s32 temp_r30;
    s32 temp_r29;
    
    BoardRollDispSet(0);
    spaceLinkFlags = BoardSpaceLinkFlagSearch(0, (s32) GWPlayer[lbl_1_bss_388].space_curr, 2U);
    BoardPlayerMoveToAsync(lbl_1_bss_388, spaceLinkFlags);
    while (GWPlayer[lbl_1_bss_388].moving) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(lbl_1_bss_388);
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    BoardPlayerMotBlendSet((s32) lbl_1_bss_388, 0x5A, 0xF);
    while (BoardPlayerMotBlendCheck((s32) lbl_1_bss_388) == 0) {
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_bss_30[15], -90.0f);
    fn_1_121C(0x130000);
    HuAudFXPlay(0x44);
    temp_r29 = fn_1_BE88();
    BoardStatusShowSetAll(0);
    fn_1_121C(0x130001);
    temp_r30 = fn_1_C108(temp_r29);
    fn_1_CD04(temp_r30);
    BoardCameraViewSet(1);
    BoardStatusShowSetAll(1);
    BoardCameraMotionWait();
    BoardRollDispSet(1);
    HuPrcKill(NULL);
    while(TRUE) {
      HuPrcVSleep();  
    }
}

s32 fn_1_BE74(void) {
    lbl_1_bss_38C = 0;
}

s32 fn_1_BE88(void) {
    s32 coinAmount;
    s32 var_r30;
    s16 playerCoinRegion;
    s32 bribeChoice;
    s32 i;
    s32 rouletteChoice;
    s32 mesg;

    var_r30 = -1;
    coinAmount = BoardPlayerCoinsGet((s32) lbl_1_bss_388);
    if (coinAmount < 5) {
        return var_r30;
    }
    fn_1_121C(0x130002);

    do {
        BoardWinCreateChoice(2, MAKE_MESSID(19, 29), 4, 0);
        /* COM has 50% to bribe goomba */
        if (GWPlayer[lbl_1_bss_388].com) {
            if (frandBool()) {
                BoardComKeySetRight();
            } else {
                BoardComKeySetLeft();
            }
        }
        BoardWinWait();
        BoardWinKill();
        rouletteChoice = BoardWinChoiceGet();
        // If chose to play roulette
        if (rouletteChoice == 0) {
            BoardWinCreateChoice(1, MAKE_MESSID(19, 3), 4, 0);
            playerCoinRegion = 3;
            if (coinAmount < 0x14) {
                BoardWinChoiceDisable(0);
                playerCoinRegion--;
            }
            if (coinAmount < 0xA) {
                BoardWinChoiceDisable(1);
                playerCoinRegion--;
            }
            /* COM always bribes max unless it has 20 or
               more coins. Then 50% max, 50% 10 coin bribe. */
            if (GWPlayer[lbl_1_bss_388].com) {
                if (playerCoinRegion < 2) {
                    BoardComKeySetUp();
                } else if (frandBool()) {
                    BoardComKeySetUp();
                } else {
                    BoardComKeySetDown();
                }
            }
            BoardWinWait();
            BoardWinKill();
            bribeChoice = BoardWinChoiceGet();
            if (bribeChoice == -1 || 
                bribeChoice == 3) {
                continue;
            }

            // Coin amount is now the bribe amount in coins
            switch (bribeChoice) {
            case 0:
                mesg = 0x130004;
                coinAmount = 0x14;
                var_r30 = 0x5A; // 90%
                break;
            case 1:
                mesg = 0x130005;
                coinAmount = 0xA;
                var_r30 = 0x3C; // 60%
                break;
            case 2:
                mesg = 0x130006;
                coinAmount = 5;
                var_r30 = 0x1E; // 30%
                break;
            }
            fn_1_121C(mesg);

            
            for (i = 0; i < coinAmount; i++) {
                BoardPlayerCoinsAdd(lbl_1_bss_388, -1);
                HuAudFXPlay(0xE);
                HuPrcSleep(6);
            }
            HuAudFXPlay(0xF);
        // If chose to view map
        } else if (rouletteChoice == 2) {
            BoardViewMapExec(lbl_1_bss_388);
        }
    } while (rouletteChoice == 2); // While viewing map
    if (var_r30 == -1) {
        fn_1_121C(0x130007);
    }
    return var_r30;
}

s32 fn_1_C108(s32 arg0) {
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;


    f32 var_f27;
    f32 var_f26;
    f32 var_f25;
    f32 var_f28;
    f32 var_f29;
    f64 var_f30;
    f32 var_f31;

    s32 var_r26;
    s32 var_r27;
    s16 var_r28;
    s32 var_r30;
    s32 var_r29;
    s32 i;

    if ((s32) frandmod(0x64U) < arg0) {
        s32 temp_r25 = fn_1_E2AC();
        var_r27 = 4;
        var_r29 = frandmod(3U);
        if ((s32) frandmod(0x64U) < 0x14) {
            var_r29 += 1;
        }
        var_r29 = var_r29 + (3 - temp_r25) * 4;
    } else {
        var_r29 = frandmod(0x10U);
        var_r27 = frandmod(4U);
    }
    BoardModelPosGet(lbl_1_bss_30[4], &sp10);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    var_r26 = BoardSpaceFlagSearch(0, 0x800U);
    BoardCameraTargetSpaceSet(var_r26);
    BoardPlayerMotBlendSet(lbl_1_bss_388, 0xB4, 0xF);
    BoardModelRotGet(lbl_1_bss_30[15], &sp34);

    for (i = 0; i < 0xF; i++) {
        sp34.y -= 6.0f;
        BoardModelRotSetV(lbl_1_bss_30[15], &sp34);
        HuPrcVSleep();
    }

    sp34.y = 180.0f;
    BoardModelRotSetV(lbl_1_bss_30[15], &sp34);
    BoardCameraMotionWait();
    lbl_1_bss_384 = HuAudFXPlay(0x41D);
    var_r28 = -0x1FFF;
    var_f29 = 0.0f;
    for (i = 0; i < 0x3C; i++) {
        var_f29 -= 0.375f;
        fn_1_E310(var_f29);
        var_r28 += 136.51666f;
        HuAudFXPitchSet(lbl_1_bss_384, var_r28);
        HuPrcVSleep();
    }
    
    var_f29 = -22.5f;
    HuAudFXPitchSet(lbl_1_bss_384, 0);
    BoardModelMotionStart(lbl_1_bss_30[15], 2, 0x40000001);
    BoardModelPosGet(lbl_1_bss_30[15], &sp34);

    for (i = 0; i < 0x1E; i++) {
        sp34.z += 2.1f;
        BoardModelPosSetV(lbl_1_bss_30[15], &sp34);
        fn_1_E310(var_f29);
        HuPrcVSleep();
    }
    BoardModelMotionStart(lbl_1_bss_30[15], 1, 0x40000001);
    while (var_r29) {
        fn_1_E310(var_f29);
        HuPrcVSleep();
        var_r29 -= 1;
    }
    BoardModelMotionStart(lbl_1_bss_30[15], 3, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_bss_30[15], 4.0f);
    
    for (i = 0; i < 0xA; i++) {
        sp34.z -= 6.2999997f;
        BoardModelPosSetV(lbl_1_bss_30[15], &sp34);
        fn_1_E310(var_f29);
        HuPrcVSleep();
    }
    BoardModelMotionStart(lbl_1_bss_30[15], 1, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_bss_30[15], 1.0f);
    HuAudFXPlay(0x41F);
    HuAudFXPlay(0x42D);
    omVibrate(lbl_1_bss_388, 0xC, 6, 6);
    var_f31 = 0.0f;
    var_f27 = 16.0f;
    sp1C.x = 0.0f;
    sp1C.z = -50.0f;

    // Roulette motion and ball ?
    while(TRUE) {
        sp1C.y = var_f27 - (0.55833334f * (0.25f * (var_f31 * var_f31)));
        var_f31 += 1.0f;
        BoardModelPosGet(lbl_1_bss_30[6], &sp28);
        PSVECAdd(&sp28, &sp1C, &sp28);
        var_f25 = VECDistanceXZ(&sp28, &sp10);
        if (var_f25 >= 430.0f) {
            if (sp28.y <= (55.0f + sp10.y)) {
                PSVECSubtract(&sp28, &sp10, (Vec* ) &sp1C);
                PSVECNormalize((Vec* ) &sp1C, (Vec* ) &sp1C);
                sp1C.y = 0.0f;
                PSVECScale((Vec* ) &sp1C, (Vec* ) &sp1C, 429.0f);
                PSVECAdd((Vec* ) &sp1C, &sp10, (Vec* ) &sp1C);
                sp28.x = sp1C.x;
                sp28.z = sp1C.z;
                sp1C.x = -5.0f;
                sp1C.z = 10.0f;
            }
        }

        if (sp28.y < sp10.y) {
            sp28.y = sp10.y;
            if (var_r27 >=  3) {
                break;
            }
            //var_f31 = ((1.0f/255.0f) * (6.0f * frand8()));
            var_f27 = 6.0f + ((1.0f/255.0f) * (6.0f * frand8()));
            var_f31 = 1.0f;
            var_r27 += 1;
            //var_f31 = ((1.0f/255.0f) * (5.0f * frand8()));
            sp1C.x = 15.0f + ((1.0f/255.0f) * (5.0f * frand8()));
            sp1C.z = 15.0f + ((1.0f/255.0f) * (5.0f * frand8()));
            HuAudFXPlay(0x41E);
        }
        
        BoardModelPosSetV(lbl_1_bss_30[6], (Vec* ) &sp28);
        fn_1_E310(var_f29);
        HuPrcVSleep();
    }

    HuAudFXPlay(0x41E);
    PSVECSubtract(&sp28, &sp10, (Vec* ) &sp1C);
    PSVECNormalize((Vec* ) &sp1C, (Vec* ) &sp1C);
    var_f31 = atan2d(-sp1C.z, sp1C.x);
    BoardModelRotGet(lbl_1_bss_30[4], &sp34);
    var_f31 = var_f31 - sp34.y;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    var_r30 = (s32) (var_f31 / 22.5f);
    if (fmod(var_f31, 22.5) > 11.25) {
        var_r30 += 1;
    }
    if (var_r30 >= 0x10) {
        var_r30 -= 0x10;
    }
    sp1C.y = 0.0f;

    while(TRUE) {
        fn_1_E310(var_f29);
        BoardModelRotGet(lbl_1_bss_30[4], &sp34);
        var_f31 = (22.5f * var_r30) + sp34.y; // TODO: Update rodata for asm change
        sp1C.x = cosd(var_f31);
        sp1C.z = -sind(var_f31);
        PSVECScale(&sp1C, &sp1C, 429.0f);
        PSVECAdd(&sp1C, &sp10, &sp1C);
        sp28.x = sp1C.x;
        sp28.z = sp1C.z;
        BoardModelPosSetV(lbl_1_bss_30[6], &sp28);
        if (sp34.y >= 292.5f &&
            sp34.y < 315.0f) {
            break;
        }
        HuPrcVSleep();
    }

    for (i = 0; i < 0x3C; i++) {
        var_f29 += 0.375f;
        fn_1_E310(var_f29);
        BoardModelRotGet(lbl_1_bss_30[4], &sp34);
        var_f31 = (22.5f * (f32) var_r30) + sp34.y;
        sp1C.x = cosd(var_f31);
        sp1C.z = -sind(var_f31);
        PSVECScale(&sp1C, &sp1C, 429.0f);
        PSVECAdd((Vec* ) &sp1C, &sp10, (Vec* ) &sp1C);
        sp28.x = sp1C.x;
        sp28.z = sp1C.z;
        BoardModelPosSetV(lbl_1_bss_30[6], (Vec* ) &sp28);
        var_r28 += -136.51666f;
        HuAudFXPitchSet(lbl_1_bss_384, var_r28);
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_bss_30[4], 0.0f);
    HuAudFXStop(lbl_1_bss_384);
    return lbl_1_data_4D0[var_r30];
}

// Place player on space post roulette?
void fn_1_CD04(s32 arg0) {
    Vec sp24;
    Vec sp18;
    Vec spC;

    f32 temp_f30;
    f32 temp_f29;
    f32 var_f31;
    
    s16 var_r25;
    u32 var_r26;
    s32 var_r27;
    s32 var_r29;
    s32 var_r28;
    s32 var_r30;
    BoardSpace* temp_r31;

    if (arg0 < 0) {
        fn_1_D3AC();
        arg0 = fn_1_D8C4();
    }
    temp_r31 = BoardSpaceGet(0, BoardSpaceFlagSearch(0, 0x800));
    
    for (var_r28 = 0; var_r28 < temp_r31->link_cnt; var_r28++) {
        var_r29 = temp_r31->link[var_r28];
        var_r26 = ( (BoardSpaceFlagGet(0, var_r29) & 0xE) >> 1U);
        if ( var_r26 == (arg0 + 2)) {
            break;
        }
    }
    BoardSpacePosGet(0, var_r29, &sp24);
    BoardModelAttrReset(lbl_1_bss_30[5], 0x40000002);
    HuAudFXPlay(0x420);
    if (BoardPlayerSizeGet(lbl_1_bss_388) == 2) {
        while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < 25.0f) {
            HuPrcVSleep();
        }
        BoardPlayerScaleGet(lbl_1_bss_388, &spC);

        while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < 30.0f) {
            spC.x -= 0.25f;
            spC.y -= 0.25f;
            //temp_f1 = spC.z;
            spC.z = spC.z - 0.25f;
            BoardPlayerScaleSetV(lbl_1_bss_388, &spC);
            HuPrcVSleep();
        }

        spC.x = spC.y = spC.z = 1.25f;
        BoardPlayerScaleSetV(lbl_1_bss_388, &spC);
    }

    while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < 30.0f) {
        HuPrcVSleep();
    }
    if (GWPlayer[lbl_1_bss_388].bowser_suit) {
        BoardModelVisibilitySet(BoardBowserSuitModelGet(), 0);
        BoardModelVisibilitySet(BoardBowserSuitPlayerModelGet(), 0);
    } else {
        BoardModelVisibilitySet(BoardPlayerModelGet(lbl_1_bss_388), 0);
    }
    HuAudFXPlay(0x421);
    omVibrate(lbl_1_bss_388, 0xC, 4, 2);

    while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < 60.0f) {
        HuPrcVSleep();
    }

    BoardModelPosGet(lbl_1_bss_30[5], &sp18);
    temp_f30 = atan2d(sp24.x - sp18.x, sp24.z - sp18.z)/30;

    while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < 90.0f) {
        BoardModelRotYSet(lbl_1_bss_30[5], temp_f30 + BoardModelRotYGet(lbl_1_bss_30[5]));
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_bss_30[5], atan2d(sp24.x - sp18.x, sp24.z - sp18.z));
    omVibrate(lbl_1_bss_388, 0xC, 4, 2);
    if (GWPlayer[lbl_1_bss_388].bowser_suit) {

        BoardModelVisibilitySet(BoardBowserSuitModelGet(),1);
        BoardModelVisibilitySet(BoardBowserSuitPlayerModelGet(),1);
    } else {
        BoardModelVisibilitySet(BoardPlayerModelGet(lbl_1_bss_388), 1);
    }
    GWPlayer[lbl_1_bss_388].space_curr =(s16) var_r29;
    BoardPlayerPosSetV(lbl_1_bss_388, &sp24);
    temp_r31 = BoardSpaceGet(0, var_r29);
    
    for ( var_r30 = 0; var_r30 < (s32) temp_r31->link_cnt; var_r30++) {
        if (BoardSpaceTypeGet(0, temp_r31->link[var_r30])) {
            break;
        }
    }

    if (var_r30 != (s32) temp_r31->link_cnt) {
        BoardSpacePosGet(0, temp_r31->link[var_r30], &sp18);
        BoardPlayerRotYSet(lbl_1_bss_388, atan2d(sp18.x - sp24.x, sp18.z - sp24.z));
    }
    if (BoardPlayerSizeGet(lbl_1_bss_388) == 2) {
        var_f31 = spC.x;

        while (var_f31 < 2.5f) {
            var_f31 += 0.104166664f;
            if (var_f31 > 2.5f) {
                var_f31 = 2.5f;
            }
            spC.z = var_f31;
            spC.y = var_f31;
            spC.x = var_f31;
            BoardPlayerScaleSetV(lbl_1_bss_388, &spC);
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x42A);
    while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < BoardModelMotionMaxTimeGet(lbl_1_bss_30[5])) {
        HuPrcVSleep();
    }
    HuPrcCreate(fn_1_DF48, 0x2004, 0x1000, 0);
}

void fn_1_D3AC(void)
{
	float temp_f31;
	float temp_f30;
	s32 temp_r31;
	s32 temp_r30;
	s16 sp38[20];
	Vec sp2C;
	Vec sp20;
	Vec sp14;
	float sp8[3] = { 1.0f, 0.3f, 2.5f };
	fn_1_121C(0x130008);
	BoardStatusShowSetAll(1);
	BoardPlayerMotBlendSet(lbl_1_bss_388, 0, 15);
	BoardPlayerPosGet(lbl_1_bss_388, &sp14);
	for(temp_r31=0; temp_r31<20; temp_r31++) {
		sp38[temp_r31] = BoardModelCreate(0x7000A, NULL, 1);
		sp2C.x = (sp14.x-25.0f)+((1.0f/255.0f)*(frand8()*50.0f));
		sp2C.y = (sp14.y+1200.0f)+(temp_r31*130.0f)+((1.0f/255.0f)*(frand8()*60.0f));
		sp2C.z = (sp14.z-25.0f)+((1.0f/255.0f)*(frand8()*50.0f));
		BoardModelPosSetV(sp38[temp_r31], &sp2C);
		sp20.x = sp20.z = 0;
		sp20.y = (1.0f/255.0f)*(frand8()*360.0f);
		BoardModelRotSetV(sp38[temp_r31], &sp20);
	}
	temp_f31 = -4;
	temp_r30 = 0;
	temp_f30 = sp8[BoardPlayerSizeGet(lbl_1_bss_388)];
	while(1) {
		for(temp_r31=0; temp_r31<20; temp_r31++) {
			if(temp_r31 < temp_r30) {
				continue;
			}
			BoardModelPosGet(sp38[temp_r31], &sp2C);
			BoardModelRotGet(sp38[temp_r31], &sp20);
			sp2C.y += temp_f31;
			sp20.y += 45.0f;
			BoardModelPosSetV(sp38[temp_r31], &sp2C);
			BoardModelRotSetV(sp38[temp_r31], &sp20);
			if(sp2C.y <= sp14.y+(180.0f*temp_f30)) {
				CharModelCoinEffectCreate(1, &sp2C);
				BoardModelVisibilitySet(sp38[temp_r31], 0);
				temp_r30++;
				BoardPlayerCoinsAdd(lbl_1_bss_388, 1);
				HuAudFXPlay(7);
				omVibrate(lbl_1_bss_388, 12, 6, 6);
				
			}
		}
		temp_f31 *= 1.05f;
		if(temp_f31 < -40.0f) {
			temp_f31 = -40.0f;
		}
		if(temp_r30 == 20) {
			BoardPlayerMotionShiftSet(lbl_1_bss_388, 7, 0, 10, 0);
			break;
		}
		HuPrcVSleep();
	}
	while(!BoardPlayerMotionEndCheck(lbl_1_bss_388)) {
		HuPrcVSleep();
	}
	for(temp_r31=0; temp_r31<20; temp_r31++) {
		BoardModelKill(sp38[temp_r31]);
	}
	HuPrcSleep(60);
	BoardPlayerMotBlendSet(lbl_1_bss_388, 180, 15);
	BoardStatusShowSetAll(0);
	while(!BoardPlayerMotBlendCheck(lbl_1_bss_388)) {
		HuPrcVSleep();
	}
}

s32 fn_1_D8C4(void)
{
	Vec sp40;
	Vec sp34;
	Vec sp28;
	Vec sp1C;
	s16 sp14[4];
	float spC[2];
	s32 sp8;
	
	float temp_f31;
	float temp_f30;
	
	s32 temp_r31;
	s16 temp_r30;
	BoardSpace *temp_r29;
	s32 temp_r28;
	s16 temp_r27;
	s16 temp_r26;
	s32 temp_r25;
	s16 temp_r24;
	s16 temp_r23;
	s16 temp_r22;
	
	u32 temp_r21;
	fn_1_121C(0x130009);
	temp_r29 = BoardSpaceGet(0, BoardSpaceFlagSearch(0, 0x800));
	BoardModelPosGet(lbl_1_bss_30[3], &sp40);
	for(temp_r31=0; temp_r31<4; temp_r31++) {
		sp14[temp_r31] = BoardModelCreate(0x70000, NULL, 1);
		BoardModelLayerSet(sp14[temp_r31], 2);
		for(temp_r28=0; temp_r28<temp_r29->link_cnt; temp_r28++) {
			temp_r21 = (BoardSpaceFlagGet(0, temp_r29->link[temp_r28]) & 0xE) >> 1;
			if(temp_r21 == temp_r31+2) {
				break;
			}
		}
		sp8 = BoardSpacePosGet(0, temp_r29->link[temp_r28], &sp28);
		VECSubtract(&sp28, &sp40, &sp34);
		BoardModelRotYSet(sp14[temp_r31], atan2d(sp34.x, sp34.z));
		VECNormalize(&sp34, &sp34);
		VECScale(&sp34, &sp34, 400);
		VECAdd(&sp34, &sp40, &sp34);
		sp34.y += 300.0f;
		BoardModelPosSetV(sp14[temp_r31], &sp34);
		sp1C.x = sp1C.y = sp1C.z = 3;
		BoardModelScaleSetV(sp14[temp_r31], &sp1C);
	}
	temp_r25 = fn_1_E2AC();
	HuWinMesMaxSizeGet(1, spC, 0x13001E);
	temp_r30 = HuWinCreate(-10000, 356, spC[0], spC[1], 0);
	HuWinMesSet(temp_r30, 0x13001E);
	HuWinBGTPLvlSet(temp_r30, 0);
	HuWinMesSpeedSet(temp_r30, 0);
	temp_r23 = GWPlayer[lbl_1_bss_388].port;
	temp_f30 = 0;
	temp_r22 = frandmod(20)+20;
	restart:
	while(1) {
		if(GWPlayer[lbl_1_bss_388].com) {
			temp_r27 = 0;
			temp_r26 = 0;
			if(temp_r22) {
				temp_r22--;
				temp_r24 = 0;
			} else {
				temp_r24 = PAD_BUTTON_A;
			}
			break;
		}
		temp_r24 = HuPadBtnDown[temp_r23];
		temp_r27 = HuPadStkX[temp_r23];
		temp_r26 = HuPadStkY[temp_r23];
		if(!(temp_r24 & PAD_TRIGGER_Z)) {
			break;
		}
		HuAudFXPlay(1);
		for(temp_r31=0; temp_r31<4; temp_r31++) {
			BoardModelVisibilitySet(sp14[temp_r31], 0);
		}
		HuWinDispOff(temp_r30);
		BoardViewMapExec(lbl_1_bss_388);
		HuWinDispOn(temp_r30);
		for(temp_r31=0; temp_r31<4; temp_r31++) {
			BoardModelVisibilitySet(sp14[temp_r31], 1);
		}
	}
	if(!(temp_r24 & PAD_BUTTON_A)) {
		if(abs(temp_r27) < 10) {
			temp_r27 = 0;
		}
		if(abs(temp_r26) < 10) {
			temp_r26 = 0;
		}
		if(temp_r27 != 0 || temp_r26 != 0) {
			temp_f31 = atan2d(-temp_r27, -temp_r26);
			if(temp_f31 < 0.0f) {
				temp_f31 += 360.0f;
			}
			temp_r31 = temp_f31/90.0f;
			temp_f31 = fmod(temp_f31, 90.0);
			if(temp_r31 != temp_r25 && temp_f31 >= 20.0f && temp_f31 <= 70.0f){ 
				temp_f30 = 0;
				temp_r25 = temp_r31;
				HuAudFXPlay(0);
			}
			
		}
		for(temp_r31=0; temp_r31<4; temp_r31++) {
			if(temp_r31 == temp_r25) {
				sp1C.x = sp1C.y = sp1C.z = sind(temp_f30)+3.0;
				temp_f30 += 8.0f;
				if(temp_f30 > 180.0f) {
					temp_f30 -= 180.0f;
				}
			} else {
				sp1C.x = sp1C.y = sp1C.z = 3.0f;
			}
			
			
			BoardModelScaleSetV(sp14[temp_r31], &sp1C);
		}
		HuPrcVSleep();
		goto restart;
	} else {
		HuAudFXPlay(2);
		for(temp_r31=0; temp_r31<4; temp_r31++) {
			BoardModelKill(sp14[temp_r31]);
		}
		HuWinKill(temp_r30);
		return temp_r25;
	}
}

void fn_1_DF48(void)
{
	Vec sp14;
	Vec sp8;
	s32 temp_r31;
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	BoardModelMotionTimeSet(lbl_1_bss_30[5], 0);
	BoardModelAttrSet(lbl_1_bss_30[5], 0x40000002);
	temp_f31 = BoardModelRotYGet(lbl_1_bss_30[5]);
	temp_f29 = -temp_f31/20.0f;
	temp_f30 = BoardModelRotYGet(lbl_1_bss_30[15]);
	temp_f28 = -temp_f30/20.0f;
	BoardModelScaleGet(lbl_1_bss_30[6], &sp14);
	for(temp_r31=0; temp_r31<10; temp_r31++) {
		sp14.x = sp14.y = sp14.z = 1.0f-(temp_r31*0.1f);
		if(sp14.x < 0.0f) {
			sp14.x = sp14.y = sp14.z = 0.0f;
		}
		BoardModelScaleSetV(lbl_1_bss_30[6], &sp14);
		temp_f31 += temp_f29;
		BoardModelRotYSet(lbl_1_bss_30[5], temp_f31);
		temp_f30 += temp_f28;
		BoardModelRotYSet(lbl_1_bss_30[15], temp_f30);
		HuPrcVSleep();
	}
	BoardModelPosGet(lbl_1_bss_30[15], &sp8);
	sp8.z -= 90.0f;
	sp8.y += 50.0f;
	BoardModelPosSetV(lbl_1_bss_30[6], &sp8);
	for(temp_r31=0; temp_r31<10; temp_r31++) {
		sp14.x = sp14.y = sp14.z = temp_r31*0.1f;
		if(sp14.x > 1.0f) {
			sp14.x = sp14.y = sp14.z = 1.0f;
		}
		BoardModelScaleSetV(lbl_1_bss_30[6], &sp14);
		temp_f31 += temp_f29;
		BoardModelRotYSet(lbl_1_bss_30[5], temp_f31);
		temp_f30 += temp_f28;
		BoardModelRotYSet(lbl_1_bss_30[15], temp_f30);
		HuPrcVSleep();
	}
	sp14.x = sp14.y = sp14.z = 1.0f;
	BoardModelScaleSetV(lbl_1_bss_30[6], &sp14);
	BoardModelRotYSet(lbl_1_bss_30[5], 0);
	BoardModelRotYSet(lbl_1_bss_30[15], 0);
	HuPrcEnd();
}

s32 fn_1_E2AC(void)
{
	switch(GWSystem.star_pos) {
		case 0:
			return 3;
			
		case 1:
		case 2:
			return 0;
			
		case 3:
		case 4:
			return 1;
			
		case 5:
		case 6:
		case 7:
			return 2;
			
		default:
			return -1;
	}
}

/* Rotate (yaw) of model 4 */
void fn_1_E310(f32 degrees) {
    Point3d spC;
    lbl_1_bss_380 += degrees;
    if (lbl_1_bss_380 >= 360.0f) {
        lbl_1_bss_380 -= 360.0f;
    }
    if (lbl_1_bss_380 < 0.0f) {
        lbl_1_bss_380 += 360.0f;
    }
    BoardModelRotGet(lbl_1_bss_30[4], &spC);
    spC.y = lbl_1_bss_380;
    BoardModelRotSetV(lbl_1_bss_30[4], &spC);
}

void fn_1_E41C(void)
{
	lbl_1_bss_388 = GWSystem.player_curr;
	OSReport("Roulette Player %d\n", lbl_1_bss_388);
	lbl_1_bss_38C = HuPrcChildCreate(fn_1_BCFC, 8195, 8192, 0, boardMainProc);
	HuPrcDestructorSet2(lbl_1_bss_38C, (void *)fn_1_BE74); //fn_1_BE74 requires implicit return
	while(lbl_1_bss_38C) {
		HuPrcVSleep();
	}
}