#include "REL/w02Dll.h"
#include "game/audio.h"
#include "game/pad.h"
#include "game/objsub.h"

#include "game/board/basic_space.h"

#include "game/printfunc.h"

s32 lbl_1_bss_54;
Process* lbl_1_bss_50;

/**
 * @brief Starts the gamble minigame sequence
 * 
 * @details The player and Goomba roll dice, with the player winning coins or
 * being sent back to start based on the outcome.
 * 
 *   * Spawns the Goomba model
 *   * Plays the Goomba animation
 *   * Rolls dice for the Goomba with weighted probabilities
 *   * Rolls dice for the player
 *   * Compares the results and gives coins or sends player to start
 * 
 * @return void
 */
void GambleExec(void)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	
	m02GenDice goombaDie;
	m02GenDice playerDie;
	s32 diceOptions[10] = {
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
	BoardSpace *playerBoardSpace;	// Seemingly goes unused?
	s32 currPlayer;
	s16 temp_r30; // ? Is this the Goomba model hook? Not sure what to name it
	s32 tmpValue; // Used for various temporary storage, sleep times, for loops, etc
	s16 temp_r28;
	s32 goombaDieResult;
	s32 playerBoardSpaceID;
	s32 randomNumber;
	u16 buttonState;
	currPlayer = GWSystem.player_curr;
	OSReport("gamble start %d\n", currPlayer);
	playerBoardSpace = BoardSpaceGet(0, GWPlayer[currPlayer].space_curr);
	BoardRollDispSet(0);
	temp_r28 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x0F), NULL, 0);
	BoardModelVisibilitySet(temp_r28, 0);

	// Determine which gamble space model to use
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
	
	BoardPlayerIdleSet(currPlayer);
	BoardPlayerMotBlendSet(currPlayer, -90, 30);
	while(!BoardPlayerMotBlendCheck(currPlayer)) {
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
	W02MesExec(MAKE_MESSID(0x13, 0x0A));
	goombaDie.unk00 = 1;
	goombaDie.unk04 = DATA_MAKE_NUM(DATADIR_W02, 0x1B);
	goombaDie.unk08 = diceOptions;
	goombaDie.unk0C = sp18;
	goombaDie.unk18 = 1;
	goombaDie.unk1A = 10;
	goombaDie.unk22 = 0;
	goombaDie.unk24 = 1;

	// Generate dice roll with weighted probabilities for the Goomba
	// 60% chance for 4-7
	// 30% chance for 2,3,8,9
	// 10% chance for 1,10
	randomNumber = frandmod(100);
	if(randomNumber <= 59) {
		goombaDie.unk1C[0] = frandmod(4)+4;
	} 
	else if(randomNumber <= 89) {
		if(randomNumber & 0x1) {
			goombaDie.unk1C[0] = 2;
		} 
		else {
			goombaDie.unk1C[0] = 8;
		}
		goombaDie.unk1C[0] += frand() & 0x1;
	} 
	else {
		if(randomNumber & 0x1) {
			goombaDie.unk1C[0] = 1;
		} else {
			goombaDie.unk1C[0] = 10;
		}
	}

	// Start dice roll
	fn_1_1254(&goombaDie);
	while(!fn_1_17F4(&goombaDie)) {
		HuPrcVSleep();
	}

	// Add delay before dice is hit, then move the Goomba model
	tmpValue = frandmod(45)+45;
	HuPrcSleep(tmpValue);
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
			goombaDie.unk9C = 1;
		}
		if(spC.y <= sp18.y) {
			spC.y = sp18.y;
			goombaDie.unk9C = 0;
			break;
		}
		BoardModelPosSetV(lbl_1_data_286, &spC);
		HuPrcVSleep();
	}
	BoardModelPosSetV(lbl_1_data_286, &sp18);
	BoardModelMotionStart(lbl_1_data_286, 1, 0x40000001);
	while(goombaDie.unk28 == 0) {
		HuPrcVSleep();
	}
	goombaDieResult = goombaDie.unk94;

	// Announce Goomba's roll, if 10 then play player's disappointment sound
	if(goombaDieResult == 10) {
		HuAudPlayerVoicePlay(currPlayer, 302);
		W02MesExec(MAKE_MESSID(0x13, 0x10));
	} else {
		W02MesExec(MAKE_MESSID(0x13, 0x0C));
	}

	BoardPlayerMotBlendSet(currPlayer, 0, 15);
	while(!BoardPlayerMotBlendCheck(currPlayer)) {
		HuPrcVSleep();
	}
	BoardCameraTargetModelSet(-1);
	if(goombaDieResult != 10) {
		playerDie = goombaDie; // Save on resources, just use Goomba's die
		BoardPlayerPosGet(currPlayer, &playerDie.unk0C);
		playerDie.unk24 = 1;

		// Generate player's die roll, ensuring it is not the same as Goomba's
		playerDie.unk1C[0] = frandmod(10)+1;
		if(playerDie.unk1C[0] == goombaDieResult) {
			if(playerDie.unk1C[0] == 9) {
				playerDie.unk1C[0]--; // Player loses if both roll 9
			} else {
				playerDie.unk1C[0]++; // Player wins if both roll 1-8
			}
		}
		
		fn_1_1254(&playerDie);
		while(!fn_1_17F4(&playerDie)) {
			HuPrcVSleep();
		}
		
		// Handle player/CPU input to hit die
		buttonState = 0;
		while(!(buttonState & PAD_BUTTON_A)) {
			HuPrcVSleep();

			// If CPU player, simulate button press after short delay
			if(GWPlayer[currPlayer].com) {
				tmpValue = frandmod(45)+20;
				HuPrcSleep(tmpValue);
				buttonState = PAD_BUTTON_A;
			} 
			// Wait for player to press A button
			else {
				// Get the state of the player's buttons
				buttonState = HuPadBtnDown[GWPlayer[currPlayer].port];
			}
		}

		// Perform player jump animation to hit die
		BoardPlayerDiceJumpStart(currPlayer);
		while(!BoardPlayerDiceJumpCheck(currPlayer)) {
			HuPrcVSleep();
		}

		playerDie.unk9C = 1;
		while(GWPlayer[currPlayer].jump) {
			HuPrcVSleep();
		}
		playerDie.unk9C = 0;
		while(playerDie.unk28 == 0) {
			HuPrcVSleep();
		}

		// Announce player's roll and outcome, extra voice line if player loses
		if(playerDie.unk94 > goombaDieResult) {
			W02MesExec(MAKE_MESSID(0x13, 0x0D));
		} else {
			HuAudPlayerVoicePlay(currPlayer, 302);
			W02MesExec(MAKE_MESSID(0x13, 0x0F));
		}
	} else {
		playerDie.unk94 = 0;
	}
	fn_1_1518(&goombaDie);
	if(goombaDieResult != 10) {
		fn_1_1518(&playerDie);
	}
	BoardPlayerPosGet(currPlayer, &spC);

	// If the player wins, award 10 coins
	if(playerDie.unk94 > goombaDieResult) {
		spC.y += 250.0f;
		HuAudFXPlay(839);
		tmpValue = BoardCoinChgCreate(&spC, 10);
		while(!BoardCoinChgExist(tmpValue)) {
			HuPrcVSleep();
		}
		for(tmpValue=0; tmpValue<10; tmpValue++) {
			BoardPlayerCoinsAdd(currPlayer, 1);
			HuAudFXPlay(7);
			HuPrcSleep(6);
		}
		W02MesExec(MAKE_MESSID(0x13, 0x0E));
	} 
	// If the Goomba wins, send the player back to start
	else {
		playerBoardSpaceID = GWPlayer[currPlayer].space_curr;
		BoardCameraTargetSpaceSet(playerBoardSpaceID);
		BoardPlayerMotionShiftSet(currPlayer, 6, 0, 5, HU3D_MOTATTR_LOOP);
		HuPrcSleep(60);
		HuPrcSleep(30);
		BoardModelPosSetV(temp_r28, &spC);
		BoardModelMotionTimeSet(temp_r28, 0);
		BoardModelVisibilitySet(temp_r28, 1);
		HuAudFXPlay(1058);
		while(BoardModelMotionTimeGet(temp_r28) < BoardModelMotionMaxTimeGet(temp_r28)) {
			HuPrcVSleep();
		}
		omVibrate(currPlayer, 12, 4, 2);
		temp_f30 = -4;
		for(tmpValue=0; tmpValue<30; tmpValue++) {
			spC.y += temp_f30;
			temp_f30 *= 1.08f;
			BoardPlayerPosSetV(currPlayer, &spC);
			HuPrcVSleep();
		}
		playerBoardSpaceID = BoardSpaceFlagSearch(0, 0x80000000);
		BoardCameraMoveSet(0);
		BoardCameraTargetSpaceSet(playerBoardSpaceID);
		HuPrcVSleep();
		BoardCameraMoveSet(1);
		BoardSpacePosGet(0, playerBoardSpaceID, &sp18);
		spC = sp18;
		spC.y -= 180.0f;
		BoardPlayerPosSetV(currPlayer, &spC);
		GWPlayer[currPlayer].space_curr = playerBoardSpaceID;
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
				omVibrate(currPlayer, 12, 4, 2);
				temp_f29 = -temp_f30*0.31f;
				temp_f31 = 1;
				HuAudFXPlay(1068);
				if(fabs(temp_f29) <= 5.0) {
					break;
				}
				spC.y = sp18.y;
			}
			
			BoardPlayerPosSetV(currPlayer, &spC);
			HuPrcVSleep();
		}
		BoardPlayerPosSetV(currPlayer, &sp18);
		HuPrcSleep(90);
		BoardPlayerIdleSet(currPlayer);
		HuPrcSleep(9);
		BoardCameraTargetPlayerSet(currPlayer);
	}
	BoardModelHookSet(temp_r30, "kuri", lbl_1_data_286);
	BoardModelAttrReset(temp_r30, 0x40000002);
	if(playerDie.unk94 > goombaDieResult) {
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

/**
 * @brief Removes the child process reference for the gamble minigame.
 */
void GambleDestroy(void) {
    lbl_1_bss_50 = NULL;
}

/**
 * @brief Bootstraps the gamble board minigame.
 * 
 * @details This function handles the initialization and execution of the 
 * gamble board minigame. It handles creating the child process that runs
 * the minigame logic, and waits for its completion before terminating and
 * returning.
 * 
 * @param actorIndex The index of the actor model (Gambling Goomba) to be used.
 */
void GambleMain(s32 actorIndex) {
    s32 currPlayer;
    currPlayer = GWSystem.player_curr; // Unused?

    lbl_1_bss_54 = actorIndex;
    lbl_1_bss_50 = HuPrcChildCreate(GambleExec, 0x2003U, 0x2000U, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_50, GambleDestroy);
    while (lbl_1_bss_50) {
        HuPrcVSleep();
    }
}
