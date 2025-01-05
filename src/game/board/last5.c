#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/audio.h"
#include "game/board/window.h"
#include "game/board/ui.h"
#include "game/board/space.h"
#include "game/board/star.h"
#include "game/audio.h"
#include "game/objsub.h"
#include "game/pad.h"

#include "game/data.h"
#include "game/wipe.h"

#include "ext_math.h"

static s16 stopWin = -1;
static s16 wheelMdl = -1;
s16 lbl_801D3854 = -1;
static s16 focusMdl = -1;
static s32 messBase = -1;

static s32 hostMotTbl[][8] = {
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 23),
		DATA_MAKE_NUM(DATADIR_BLAST5, 24),
		DATA_MAKE_NUM(DATADIR_BLAST5, 25),
		DATA_MAKE_NUM(DATADIR_BLAST5, 26),
		DATA_MAKE_NUM(DATADIR_BLAST5, 27),
		DATA_MAKE_NUM(DATADIR_BLAST5, 28),
		DATA_MAKE_NUM(DATADIR_BLAST5, 29),
		DATA_MAKE_NUM(DATADIR_BLAST5, 30)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 31),
		DATA_MAKE_NUM(DATADIR_BLAST5, 32),
		DATA_MAKE_NUM(DATADIR_BLAST5, 33),
		DATA_MAKE_NUM(DATADIR_BLAST5, 34),
		DATA_MAKE_NUM(DATADIR_BLAST5, 35),
		DATA_MAKE_NUM(DATADIR_BLAST5, 36),
		DATA_MAKE_NUM(DATADIR_BLAST5, 37),
		DATA_MAKE_NUM(DATADIR_BLAST5, 38)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 39),
		DATA_MAKE_NUM(DATADIR_BLAST5, 40),
		DATA_MAKE_NUM(DATADIR_BLAST5, 41),
		DATA_MAKE_NUM(DATADIR_BLAST5, 42),
		DATA_MAKE_NUM(DATADIR_BLAST5, 43),
		DATA_MAKE_NUM(DATADIR_BLAST5, 44),
		DATA_MAKE_NUM(DATADIR_BLAST5, 45),
		DATA_MAKE_NUM(DATADIR_BLAST5, 46)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 47),
		DATA_MAKE_NUM(DATADIR_BLAST5, 48),
		DATA_MAKE_NUM(DATADIR_BLAST5, 49),
		DATA_MAKE_NUM(DATADIR_BLAST5, 50),
		DATA_MAKE_NUM(DATADIR_BLAST5, 51),
		DATA_MAKE_NUM(DATADIR_BLAST5, 52),
		DATA_MAKE_NUM(DATADIR_BLAST5, 53),
		DATA_MAKE_NUM(DATADIR_BLAST5, 54)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 55),
		DATA_MAKE_NUM(DATADIR_BLAST5, 56),
		DATA_MAKE_NUM(DATADIR_BLAST5, 57),
		DATA_MAKE_NUM(DATADIR_BLAST5, 58),
		DATA_MAKE_NUM(DATADIR_BLAST5, 59),
		DATA_MAKE_NUM(DATADIR_BLAST5, 60),
		DATA_MAKE_NUM(DATADIR_BLAST5, 61),
		DATA_MAKE_NUM(DATADIR_BLAST5, 62)
	},
	{ 
		DATA_MAKE_NUM(DATADIR_BLAST5, 63),
		DATA_MAKE_NUM(DATADIR_BLAST5, 64),
		DATA_MAKE_NUM(DATADIR_BLAST5, 65),
		DATA_MAKE_NUM(DATADIR_BLAST5, 66),
		DATA_MAKE_NUM(DATADIR_BLAST5, 67),
		DATA_MAKE_NUM(DATADIR_BLAST5, 68),
		DATA_MAKE_NUM(DATADIR_BLAST5, 69),
		DATA_MAKE_NUM(DATADIR_BLAST5, 70)
	},
	{ 
		-1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	},
	{ 
		-1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	},
	{ 
		-1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	},
};

static s32 messBaseTbl[] = {
	MAKE_MESSID(14, 0),
	MAKE_MESSID(14, 24),
	MAKE_MESSID(14, 48),
	MAKE_MESSID(14, 72),
	MAKE_MESSID(14, 96),
	MAKE_MESSID(14, 120),
	0,
	0,
	0,
};

static float playerOfsTbl[][2] = {
	{ -94, 0 },
	{ 0, 0 },
	{ 94, 0 }
};

static char *plateObjNameTbl[] = {
	"plate",
	"plate1",
	"plate2",
	"plate3"
};

static char *hiliteObjNameTbl[] = {
	"lite",
	"lite1",
	"lite2",
	"lite3"
};

static char *faceObjNameTbl[] = {
	"kao",
	"kao1",
	"kao2",
	"kao3"
};

static s32 resultRankFX12Tbl[] = {
	0x122,
	0x162,
	0x1A2,
	0x1E2,
	0x222,
	0x262,
	0x2A2,
	0x2E2
};

static s32 resultRankFX3Tbl[] = {
	0x12A,
	0x16A,
	0x1AA,
	0x1EA,
	0x22A,
	0x26A,
	0x2AA,
	0x2EA
};

static s32 resultRankFX4Tbl[] = {
	0x12E,
	0x16E,
	0x1AE,
	0x1EE,
	0x22E,
	0x26E,
	0x2AE,
	0x2EE
};

static s32 impactFXTbl[] = {
	0x119,
	0x159,
	0x199,
	0x1D9,
	0x219,
	0x259,
	0x299,
	0x2D9
};

static s32 lotteryWheelMdlTbl[] = {
	DATA_MAKE_NUM(DATADIR_BLAST5, 13),
	DATA_MAKE_NUM(DATADIR_BLAST5, 14),
	DATA_MAKE_NUM(DATADIR_BLAST5, 15),
	DATA_MAKE_NUM(DATADIR_BLAST5, 16),
	DATA_MAKE_NUM(DATADIR_BLAST5, 17),
	DATA_MAKE_NUM(DATADIR_BLAST5, 18),
	DATA_MAKE_NUM(DATADIR_BLAST5, 19),
	DATA_MAKE_NUM(DATADIR_BLAST5, 20),
};

static s16 teamSprPrioTbl[] = {
	1520,
	1510,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1500,
	1490,
	1490,
	1500,
	1500
};

static s32 teamSprTbl[] = {
	DATA_MAKE_NUM(DATADIR_BOARD, 39),
	DATA_MAKE_NUM(DATADIR_BOARD, 38),
	DATA_MAKE_NUM(DATADIR_BOARD, 41),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 45),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 40),
	DATA_MAKE_NUM(DATADIR_BOARD, 44),
	DATA_MAKE_NUM(DATADIR_BOARD, 42),
	DATA_MAKE_NUM(DATADIR_BOARD, 42),
};

static float teamSprPosTbl[][2] = {
	{ 0, -35 },
	{ 0, 0 },
	{ -68, -38 },
	{ 80, -22 },
	{ 64, -22 },
	{ 48, -22 },
	{ 26, -22 },
	{ 80, -48 },
	{ 64, -48 },
	{ 48, -48 },
	{ 26, -48 },
	{ -18, -40 },
	{ -18, 32 },
	{ -16, -72 },
	{ -16, 0 }
};

static s32 teamCharSprTbl[] = {
	DATA_MAKE_NUM(DATADIR_BOARD, 46),
	DATA_MAKE_NUM(DATADIR_BOARD, 47),
	DATA_MAKE_NUM(DATADIR_BOARD, 48),
	DATA_MAKE_NUM(DATADIR_BOARD, 49),
	DATA_MAKE_NUM(DATADIR_BOARD, 50),
	DATA_MAKE_NUM(DATADIR_BOARD, 51),
	DATA_MAKE_NUM(DATADIR_BOARD, 52),
	DATA_MAKE_NUM(DATADIR_BOARD, 53),
};

static s8 currTicket;
static s8 numTickets;
static s8 last5Player;
static s16 last5Space;
static s16 hostMdl;
static omObjData *last5RouletteObj;
static Process *last5Proc;
static omObjData *teamResultObj;
static omObjData *hostMoveObj;
static omObjData *lotteryDrawObj;
static omObjData *lotteryDrawWheelObj;

static Vec spacePos;
static Vec focusPos;
static Vec hostPos;
static s16 hostMot[8];
static omObjData *lotteryTicketObj[4];

static void DestroyLast5(void);

static void ExecLast5(void);
static void CreateLast5(void);
static void KillLast5(void);

static void InitHost(void);
static void KillHost(void);

static void Last5Main(void);

static s32 CheckJump(s32 player);

static void CreateLotteryDrawWheel(void);
static void CreateLotteryDraw(Vec *pos);
static void UpdateLotteryDraw(omObjData *object);
static void SetLotteryDrawState(s32 state);
static s32 GetLotteryDrawState();
static void KillLotteryDrawWheel(void);
static void UpdateLotteryDrawWheel(omObjData *object);
static void SetLotteryDrawWheelState(s32 state);
static void ExecLotteryDraw(void);

static void KillLotteryTicket(void);
static void InitLotteryTicket(void);
static void UpdateLotteryTicket(omObjData *object);
static void SetLotteryTicketState(s32 player, s32 state);
static s32 GetLotteryTicketPlayer(void);
static s32 CheckLotteryTicket(void);
static void UpdateLotteryTicketMatch(s32 progress, s32 character);

static void StartHostMove(Vec *from, Vec *to, s16 time);
static void ExecHostMove(omObjData *object);
static s32 CheckHostMove(void);

static void CreateStopWin(void);

static void CreateLast5Roulette(void);
static void UpdateLast5Roulette(omObjData *object);

static void SetLast5RouletteFade(s32 flag);
static void SetLast5RouletteState(s32 state);
static s32 GetLast5RouletteState(void);
static s32 GetLast5RouletteResult(void);

static void CreateTeamResult(void);
static void GetTeamResultTarget(s32 team, Vec *pos);
static void SetTeamResultTarget(s32 team, Vec *pos);
static void KillTeamResult(void);
static void UpdateTeamResult(omObjData *object);

void BoardLast5Exec()
{
	GWSystem.player_curr = -1;
	last5Proc = HuPrcChildCreate(ExecLast5, 8200, 14336, 0, boardMainProc);
	HuPrcDestructorSet2(last5Proc, DestroyLast5);
	while(last5Proc != NULL) {
		HuPrcVSleep();
	}
	GWSystem.player_curr = 0;
}

static void DestroyLast5(void)
{
	KillLast5();
	HuDataDirClose(DATADIR_BLAST5);
	last5Proc = NULL;
}

static void ExecLast5(void)
{
	s32 i;
	messBase = messBaseTbl[GWBoardGet()];
	CreateLast5();
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	_ClearFlag(0x1001C);
	BoardLast5GfxInit();
	BoardAudSeqFadeOut(0, 1000);
	BoardMusStart(1, 8, 127, 0);
	BoardWinCreate(2, messBase, BoardWinPortraitGetStar());
	BoardWinWait();
	BoardWinKill();
	ExecLotteryDraw();
	Last5Main();
	BoardAudSeqFadeOut(1, 1000);
	_SetFlag(0x1001C);
	_SetFlag(0x1000E);
	WipeColorSet(255, 255, 255);
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	BoardModelMotionStart(hostMdl, 1, 0x40000001);
	BoardCameraMoveSet(0);
	BoardCameraViewSet(2);
	BoardCameraMotionWait();
	BoardCameraMoveSet(1);
	for(i=0; i<4; i++) {
		BoardModelVisibilitySet(BoardPlayerModelGet(i), 1);
		BoardPlayerCornerPosSet(i);
		BoardPlayerRotYSet(i, 0.0f);
	}
	BoardStatusItemSet(0);
	HuPrcSleep(60);
	HuPrcEnd();
}

static void CreateLast5(void)
{
	Vec rot;
	s32 i;
	last5Space = BoardSpaceFlagPosGet(0, 0x80000000, &spacePos);
	for(i=0; i<4; i++) {
		BoardModelVisibilitySet(BoardPlayerModelGet(i), 0);
	}
	BoardStatusItemSet(0);
	focusPos.x = 150.0f+spacePos.x;
	focusPos.y = 100.0f+spacePos.y;
	focusPos.z = -150.0f+spacePos.z;
	focusMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 0);
	BoardModelVisibilitySet(focusMdl, 0);
	BoardModelPosSetV(focusMdl, &focusPos);
	rot.x = -10.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;
	BoardCameraMoveSet(0);
	BoardCameraMotionStartEx(focusMdl, &rot, NULL, 1480.0f, 25.0f, 1);
	BoardCameraMotionWait();
	BoardCameraMoveSet(1);
	InitHost();
	CreateLotteryDrawWheel();
	InitLotteryTicket();
}

static void KillLast5(void)
{
	if(stopWin != -1) {
		HuWinKill(stopWin);
		stopWin = -1;
	}
	BoardConfettiKill();
	KillHost();
	KillLotteryDrawWheel();
	KillLotteryTicket();
}

static void InitHost(void)
{
	Vec pos;
	s32 i;
	s32 board = GWBoardGet();
	hostMdl = BoardStarHostMdlGet();
	BoardModelPosGet(hostMdl, &hostPos);
	for(i=0; i<8; i++) {
		hostMot[i] = BoardModelMotionCreate(hostMdl, hostMotTbl[board][i]);
	}
	BoardModelMotionStart(hostMdl, 1, 0x40000001);
	pos.x = 150.0f+spacePos.x;
	pos.y = spacePos.y;
	pos.z = (150.0f+spacePos.z)-50.0f;
	BoardModelPosSetV(hostMdl, &pos);
}

static void KillHost(void)
{
	s32 i;
	for(i=0; i<8; i++) {
		if(hostMot[i] != -1) {
			BoardModelMotionKill(hostMdl, hostMot[i]);
			hostMot[i] = -1;
		}
	}
	BoardModelRotYSet(hostMdl, 0.0f);
	BoardModelPosSetV(hostMdl, &hostPos);
}

static void Last5Main(void)
{
	float temp_f31;
	s32 temp_r31;
	s32 temp_r30;
	s32 temp_r29;
	s32 temp_r27;
	s32 temp_r26;
	s32 temp_r25;
	s32 temp_r24;
	s32 temp_r23;
	s32 temp_r22;
	s32 temp_r21;
	s32 temp_r20;
	s32 temp_r19;
	s32 temp_r18;
	Vec sp6C[4];
	Vec sp60;
	Vec sp54;
	Vec sp48;
	Vec sp3C;
	float sp2C[4];
	s8 sp28[4];
	s8 sp24[4];
	s8 sp20[4];
	
	
	
	temp_r18 = -1;
	for(temp_r26=temp_r27=0; temp_r27<=3; temp_r27++) {
		for(temp_r25=temp_r31=0; temp_r31<4; temp_r31++) {
			if(GWPlayer[temp_r31].rank == temp_r27) {
				sp28[temp_r26] = temp_r31;
				sp24[temp_r26] = temp_r27;
				temp_r26++;
				if(temp_r27 > temp_r18) {
					sp20[temp_r25] = temp_r31;
					temp_r25++;
				}
			}
		}
		if(temp_r25 != 0) {
			temp_r21 = temp_r25;
		}
	}
	BoardWinCreate(2, messBase+10, BoardWinPortraitGetStar());
	BoardWinWait();
	BoardModelMotionShiftSet(hostMdl, hostMot[5], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
	HuPrcVSleep(8);
	BoardModelMotionShiftSet(hostMdl, hostMot[6], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
	for(temp_r31=0; temp_r31<4; temp_r31++) {
		temp_r30 = sp28[temp_r31];
		temp_r27 = sp24[temp_r31];
		temp_r23 = GWPlayer[temp_r30].character;
		sp6C[temp_r31].x = -122.0f;
		sp6C[temp_r31].y = (temp_r31*74)+80;
		sp6C[temp_r31].z = 0.0f;
		BoardStatusPosSet(temp_r30, &sp6C[temp_r31]);
		HuPrcVSleep();
		BoardStatusShowSet(temp_r30, 1);
		sp2C[temp_r31] = (122.0f-sp6C[temp_r31].x)/15.0f;
		for(temp_r29=0; temp_r29<15; temp_r29++) {
			sp6C[temp_r31].x += sp2C[temp_r31];
			BoardStatusPosSet(temp_r30, &sp6C[temp_r31]);
			HuPrcVSleep();
		}
		switch(temp_r27) {
			case 0:
			case 1:
				temp_r22 = resultRankFX12Tbl[temp_r23];
				break;
				
			case 2:
				temp_r22 = resultRankFX3Tbl[temp_r23];
				break;
				
			case 3:
				temp_r22 = resultRankFX4Tbl[temp_r23];
				break;
		}
		HuAudFXPlay(temp_r22);
		temp_r24 = 11+messBase+temp_r27;
		BoardWinCreate(2, temp_r24, BoardWinPortraitGetStar());
		BoardWinInsertMesSet(BoardPlayerGetCharMess(temp_r30), temp_r27);
		BoardWinWait();
	}
	if((s32)GWSystem.team != 0) {
		CreateTeamResult();
		for(temp_r31=0; temp_r31<4; temp_r31++) {
			sp2C[temp_r31] = (-122.0f-sp6C[temp_r31].x)/15.0f;
		}
		for(temp_r29=0; temp_r29<15; temp_r29++) {
			for(temp_r31=0; temp_r31<4; temp_r31++) {
				temp_r30 = sp28[temp_r31];
				sp6C[temp_r31].x += sp2C[temp_r31];
				BoardStatusPosSet(temp_r30, &sp6C[temp_r31]);
			}
			HuPrcVSleep();
		}
		BoardStatusItemSet(0);
		temp_r24 = MAKE_MESSID(14, 144) + GWBoardGet();
		BoardWinCreate(2, temp_r24, BoardWinPortraitGetStar());
		BoardWinWait();
		for(temp_r31=0; temp_r31<2; temp_r31++) {
			GetTeamResultTarget(temp_r31, &sp6C[temp_r31]);
			sp2C[temp_r31] = (122.0f-sp6C[temp_r31].x)/15.0f;
			for(temp_r29=0; temp_r29<15; temp_r29++) {
				sp6C[temp_r31].x += sp2C[temp_r31];
				SetTeamResultTarget(temp_r31, &sp6C[temp_r31]);
				HuPrcVSleep();
			}
		}
	}
	BoardModelMotionStart(hostMdl, hostMot[5], 0x40000004);
	HuPrcVSleep(8);
	BoardModelMotionShiftSet(hostMdl, 1, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
	BoardWinCreate(2, messBase+15, BoardWinPortraitGetStar());
	BoardWinWait();
	if((s32)GWSystem.team != 0) {
		for(temp_r31=0; temp_r31<2; temp_r31++) {
			sp2C[temp_r31] = (-122.0f-sp6C[temp_r31].x)/15.0f;
		}
		for(temp_r29=0; temp_r29<15; temp_r29++) {
			for(temp_r31=0; temp_r31<2; temp_r31++) {
				GetTeamResultTarget(temp_r31, &sp6C[temp_r31]);
				sp6C[temp_r31].x += sp2C[temp_r31];
				SetTeamResultTarget(temp_r31, &sp6C[temp_r31]);
			}
			HuPrcVSleep();
		}
		KillTeamResult();
	} else {
		for(temp_r31=0; temp_r31<4; temp_r31++) {
			sp2C[temp_r31] = (-122.0f-sp6C[temp_r31].x)/15.0f;
		}
		for(temp_r29=0; temp_r29<15; temp_r29++) {
			for(temp_r31=0; temp_r31<4; temp_r31++) {
				temp_r30 = sp28[temp_r31];
				sp6C[temp_r31].x += sp2C[temp_r31];
				BoardStatusPosSet(temp_r30, &sp6C[temp_r31]);
			}
			HuPrcVSleep();
		}
		BoardStatusItemSet(0);
	}
	BoardModelPosGet(hostMdl, &sp60);
	sp54.x = sp60.x+100.0f;
	sp54.y = sp60.y;
	sp54.z = sp60.z;
	StartHostMove(&sp60, &sp54, 25);
	while(!CheckHostMove()) {
		HuPrcVSleep();
	}
	BoardModelMotionShiftSet(hostMdl, 1, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
	HuPrcSleep(8);
	if((s32)GWSystem.team != 0) {
		temp_r30 = last5Player;
	} else {
		if(temp_r21 == 1) {
			temp_r30 = sp20[0];
		} else {
			temp_r30 = sp20[BoardRandMod(temp_r21)];
		}
	}
	sp48.x = sp60.x-100.0f;
	sp48.y = sp60.y;
	sp48.z = sp60.z;
	sp48.y += 700.0f;
	BoardPlayerPosSetV(temp_r30, &sp48);
	BoardPlayerMotionStart(temp_r30, 6, 0x40000001);
	BoardPlayerVoiceEnableSet(temp_r30, 6, 0);
	BoardPlayerRotYSet(temp_r30, 0);
	BoardModelVisibilitySet(BoardPlayerModelGet(temp_r30), 1);
	BoardWinCreate(2, messBase+16, BoardWinPortraitGetStar());
	BoardWinInsertMesSet(BoardPlayerGetCharMess(temp_r30), 3);
	BoardWinWait();
	BoardModelMotionShiftSet(hostMdl, hostMot[5], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
	HuPrcVSleep(8);
	BoardModelMotionShiftSet(hostMdl, hostMot[6], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
	temp_r19 = 0;
	temp_r29 = 3;
	for(temp_f31=0; temp_r29>0; temp_f31++) {
		sp48.y += (float)(5.0+((-9.8/120)*temp_f31*temp_f31));
		if(sp60.y > sp48.y) {
			omVibrate(temp_r30, 12, 6, 6);
			if(!temp_r19) {
				HuAudFXPlay(impactFXTbl[GWPlayer[temp_r30].character]);
				temp_r19 = 1;
			}
			sp48.y = sp60.y;
			sp48.y += temp_r29*10;
			temp_r29--;
			temp_f31 = 0.0f;
		}
		BoardPlayerPosSetV(temp_r30, &sp48);
		HuPrcVSleep();
	}
	HuPrcSleep(20);
	BoardPlayerIdleSet(temp_r30);
	sp3C = sp48;
	BoardModelMotionStart(hostMdl, hostMot[5], 0x40000004);
	HuPrcVSleep(8);
	BoardModelMotionShiftSet(hostMdl, 1, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
	CreateLast5Roulette();
	SetLast5RouletteFade(1);
	SetLast5RouletteState(2);
	CreateStopWin();
	sp48.x = sp60.x-100.0f;
	sp48.y = sp60.y;
	sp48.z = sp60.z;
	CreateLotteryDraw(&sp48);
	SetLotteryDrawState(2);
	while(GetLotteryDrawState() != 0) {
		HuPrcVSleep();
	}
	while(!CheckJump(temp_r30)) {
		HuPrcVSleep();
	}
	BoardPlayerDiceJumpStart(temp_r30);
	while(!BoardPlayerDiceJumpCheck(temp_r30)) {
		HuPrcVSleep();
	}
	SetLotteryDrawState(1);
	SetLast5RouletteState(3);
	while(GWPlayer[temp_r30].jump) {
		HuPrcVSleep();
	}
	while(GetLast5RouletteState() != 0) {
		HuPrcVSleep();
	}
	HuWinDispOff(stopWin);
	SetLotteryDrawState(3);
	temp_r20 = GetLast5RouletteResult();
	GWSystem.last5_effect = temp_r20;
	if(GWSystem.last5_effect == 2) {
		BoardSpaceTypeForce(2, 3);
	}
	if(GWSystem.last5_effect == 3) {
		BoardSpaceTypeForce(2, 7);
	}
	temp_r24 = 18+messBase+temp_r20;
	BoardWinCreate(2, temp_r24, BoardWinPortraitGetStar());
	BoardWinWait();
	StartHostMove(&sp54, &sp60, 25);
	BoardPlayerPosGet(temp_r30, &sp48);
	sp48 = sp3C;
	sp3C.x = sp48.x-300.0f;
	sp3C.y = sp48.y;
	sp3C.z = sp48.z;
	BoardPlayerPosLerpStart(temp_r30, &sp48, &sp3C, 25);
	while(GWPlayer[temp_r30].moving) {
		HuPrcVSleep();
	}
	BoardPlayerIdleSet(temp_r30);
	BoardModelVisibilitySet(BoardPlayerModelGet(temp_r30), 0);
	SetLast5RouletteFade(0);
	BoardModelMotionShiftSet(hostMdl, 1, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
	BoardWinCreate(2, messBase+23, BoardWinPortraitGetStar());
	BoardWinWait();
	BoardModelMotionShiftSet(hostMdl, hostMot[4], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
	HuPrcSleep(8);
	while(!BoardModelMotionEndCheck(hostMdl)) {
		HuPrcVSleep();
	}
	BoardModelMotionShiftSet(hostMdl, hostMot[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
	SetLotteryDrawState(4);
}

static s32 CheckJump(s32 player)
{
	s32 sp8 = 0;
	if(GWPlayer[player].com) {
		if(BoardRandMod(100) >= 90) {
			return 1;
		}
	} else if(HuPadBtnDown[GWPlayer[player].port] == PAD_BUTTON_A) {
		return 1;
	}
	return 0;
}

typedef struct draw_wheel_mdl {
	s16 plate[4];
	s16 face[4];
	s16 center;
} DrawWheelMdl;

typedef struct draw_wheel_work {
	struct {
		u8 kill : 1;
	};
	s8 state;
	s8 hilite;
	u16 timer;
	u8 hilite_vel;
	u8 hilite_accel;
	DrawWheelMdl *mdl;
} DrawWheelWork;

typedef struct lottery_draw_work {
	struct {
		u8 kill : 1;
	};
	u8 state;
	s16 block_mdl;
	float min_y;
} LotteryDrawWork;

static void CreateLotteryDrawWheel(void)
{
	omObjData *object;
	DrawWheelWork *work;
	DrawWheelMdl *mdl;
	s32 i;
	object = omAddObjEx(boardObjMan, 257, 0, 0, -1, UpdateLotteryDrawWheel);
	lotteryDrawWheelObj = object;
	work = OM_GET_WORK_PTR(object, DrawWheelWork);
	work->kill = 0;
	work->state = 0;
	work->mdl = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(DrawWheelMdl), MEMORY_DEFAULT_NUM);
	work->hilite = 0;
	work->hilite_vel = 2;
	work->hilite_accel = 5;
	mdl = work->mdl;
	object->trans.x = spacePos.x + -300.0f;
	object->trans.y = spacePos.y;
	object->trans.z = spacePos.z + -50.0f;
	wheelMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BLAST5, 12), NULL, 0);
	BoardModelPosSet(wheelMdl, object->trans.x, object->trans.y, object->trans.z);
	mdl->center = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BLAST5, 22), NULL, 0);
	BoardModelVisibilitySet(mdl->center, 0);
	for(i=0; i<4; i++) {
		s32 character = GWPlayer[i].character;
		mdl->face[i] = BoardModelCreate(lotteryWheelMdlTbl[character], NULL, 0);
		BoardModelPosSet(mdl->face[i], 0, 0, -10);
		mdl->plate[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BLAST5, 21), NULL, 1);
		BoardModelHookSet(wheelMdl, faceObjNameTbl[i], mdl->face[i]);
		BoardModelHookSet(wheelMdl, plateObjNameTbl[i], mdl->plate[i]);
	}
}

static void CreateLotteryDraw(Vec *pos)
{
	omObjData *object;
	LotteryDrawWork *work;
	object = omAddObjEx(boardObjMan, 257, 0, 0, -1, UpdateLotteryDraw);
	lotteryDrawObj = object;
	work = OM_GET_WORK_PTR(object, LotteryDrawWork);
	work->kill = 0;
	work->state = 0;
	work->block_mdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BLAST5, 11), NULL, 0);
	work->min_y = pos->y+300.0f;
	pos->y += 700.0f;
	BoardModelPosSetV(work->block_mdl, pos);
	object->trans.x = 1.0f;
	BoardModelAlphaSet(work->block_mdl, 255);
}

static void UpdateLotteryDraw(omObjData *object)
{
	LotteryDrawWork *work = OM_GET_WORK_PTR(object, LotteryDrawWork);
	Vec pos;
	if(work->kill || BoardIsKill()) {
		BoardModelKill(work->block_mdl);
		lotteryDrawObj = NULL;
		omDelObjEx(HuPrcCurrentGet(), object);
		return;
	}
	switch(work->state) {
		case 1:
			BoardModelPosGet(work->block_mdl, &pos);
			pos.y += 50.0f;
			BoardModelPosSetV(work->block_mdl, &pos);
			SetLotteryDrawState(2);
			break;
			
		case 2:
			BoardModelPosGet(work->block_mdl, &pos);
			if(pos.y < work->min_y) {
				pos.y = work->min_y;
				SetLotteryDrawState(0);
			}
			pos.y -= 20.0f;
			BoardModelPosSetV(work->block_mdl, &pos);
			break;
			
		case 3:
			object->trans.x -= 0.1f;
			if(object->trans.x < 0.0f) {
				object->trans.x = 0;
				SetLotteryDrawState(0);
			}
			BoardModelAlphaSet(work->block_mdl, 255.0f*object->trans.x);
			break;
			
		case 0:
			break;
			
		default:
			break;
	}
}

static void SetLotteryDrawState(s32 state)
{
	LotteryDrawWork *work;
	if(!lotteryDrawObj) {
		return;
	}
	work = OM_GET_WORK_PTR(lotteryDrawObj, LotteryDrawWork);
	work->state = state;
	if(state == 4) {
		work->kill = 1;
	}
	if(state == 3) {
		lotteryDrawObj->trans.x = 1.0f;
	}
	if(state == 1) {
		HuAudFXPlay(780);
	}
}

static s32 GetLotteryDrawState(void)
{
	LotteryDrawWork *work = OM_GET_WORK_PTR(lotteryDrawObj, LotteryDrawWork);
	return work->state;
}

static void KillLotteryDrawWheel(void)
{
	SetLotteryDrawWheelState(5);
}

static void UpdateLotteryDrawWheel(omObjData *object)
{
	DrawWheelWork *work = OM_GET_WORK_PTR(object, DrawWheelWork);
	DrawWheelMdl *mdl = work->mdl;
	s32 i;
	if(work->kill || BoardIsKill()) {
		BoardModelHookReset(wheelMdl);
		for(i=0; i<4; i++) {
			if(mdl->face[i] != -1) {
				BoardModelKill(mdl->face[i]);
			}
			if(mdl->plate[i] != -1) {
				BoardModelKill(mdl->plate[i]);
			}
		}
		if(wheelMdl != -1) {
			BoardModelKill(wheelMdl);
			wheelMdl = -1;
		}
		if(lbl_801D3854 != -1) {
			BoardModelKill(lbl_801D3854);
			lbl_801D3854 = -1;
		}
		if(mdl->center != -1) {
			BoardModelKill(mdl->center);
		}
		HuMemDirectFree(work->mdl);
		lotteryDrawWheelObj = NULL;
		omDelObjEx(HuPrcCurrentGet(), object);
		return;
	}
	switch(work->state) {
		case 4:
			if(work->timer == 0) {
				work->hilite_vel += work->hilite_accel;
				work->hilite_accel++;
				if(work->hilite_vel > 60 || (work->hilite_vel > 40 && BoardRandMod(100) > 80)) {
					BoardModelMotionStart(mdl->center, 0, 0x40000001);
					HuAudFXPlay(870);
					SetLotteryDrawWheelState(0);
					break;
				}
			}
			
		case 3:
			if(work->timer < work->hilite_vel) {
				work->timer++;
			} else {
				BoardModelHookObjReset(wheelMdl, hiliteObjNameTbl[work->hilite]);
				work->hilite = (work->hilite+1)  & 0x3;
				HuAudFXPlay(855);
				BoardModelHookSet(wheelMdl, hiliteObjNameTbl[work->hilite], mdl->center);
				work->timer = 0;
			}
			break;
		
		case 1:
		case 2:
			if(work->timer != 0) {
				object->trans.x += object->rot.x;
				object->trans.z += object->rot.z;
				work->timer--;
			} else {
				BoardModelMotionSpeedSet(wheelMdl, 0);
				work->state = 0;
			}
			break;
			
		case 0:
			break;
			
		default:
			break;
	}
	BoardModelPosSet(wheelMdl, object->trans.x, object->trans.y, object->trans.z);
}

static void SetLotteryDrawWheelState(s32 state)
{
	DrawWheelWork *work;
	DrawWheelMdl *mdl;
	Vec pos_wheel, pos_space, dist;
	if(!lotteryDrawWheelObj) {
		return;
	}
	work = OM_GET_WORK_PTR(lotteryDrawWheelObj, DrawWheelWork);
	
	work->state = state;
	mdl = work->mdl;
	switch(state) {
		case 5:
			work->kill = 1;
			break;
		
		case 3:
			work->timer = 0;
			work->hilite = 0;
			work->hilite_vel = 2;
			BoardModelVisibilitySet(mdl->center, 1);
			BoardModelMotionStart(mdl->center, 0, 0);
			BoardModelMotionSpeedSet(mdl->center, 0.0f);
			BoardModelMotionTimeSet(mdl->center, 3.0f);
			BoardModelHookSet(wheelMdl, hiliteObjNameTbl[work->hilite], mdl->center);
			break;
			
		default:
			if(state == 2 || state == 1) {
				BoardModelPosGet(wheelMdl, &pos_wheel);
				if(state == 2) {
					pos_space = spacePos;
				} else {
					pos_space.x = -300.0f+pos_wheel.x;
					pos_space.y = pos_wheel.y;
					pos_space.z = -50.0f+pos_wheel.z;
				}
				VECSubtract(&pos_space, &pos_wheel, &dist);
				lotteryDrawWheelObj->rot.x = dist.x/26.0f;
				lotteryDrawWheelObj->rot.z = dist.z/26.0f;
				BoardModelMotionStart(wheelMdl, 0, 0x40000001);
				BoardModelMotionSpeedSet(wheelMdl, 3.0f);
				work->timer = 26;
			}
			break;
	}
}

static s32 GetLotteryDrawWheelState()
{
	DrawWheelWork *work;
	if(!lotteryDrawWheelObj) {
		return -1;
	}
	work = OM_GET_WORK_PTR(lotteryDrawWheelObj, DrawWheelWork);
	return work->state;
}

static s32 GetLotteryDrawWheelResult()
{
	DrawWheelWork *work;
	if(!lotteryDrawWheelObj) {
		return -1;
	}
	work = OM_GET_WORK_PTR(lotteryDrawWheelObj, DrawWheelWork);
	return GWPlayer[work->hilite].character;
}

static void ExecLotteryDraw(void)
{
	s32 ticket;
	s32 valid;
	s32 character;
	s32 stream;
	s32 player;
	Vec rot;
	Vec offset;
	Vec confetti_pos;
	Vec pos;
	Vec star_pos;
	Vec host_end;
	Vec host_start;
	Vec player_end;
	Vec player_start;

	if(GWPlayer[0].draw_ticket || GWPlayer[1].draw_ticket || GWPlayer[2].draw_ticket || GWPlayer[3].draw_ticket) {
		BoardWinCreate(2, messBase+1, BoardWinPortraitGetStar());
		BoardWinWait();
		BoardModelPosGet(hostMdl, &host_end);
		250.0f+host_end.y;
		CreateLotteryDraw(&host_end);
		SetLotteryDrawState(2);
		SetLotteryDrawWheelState(2);
		for(ticket=0; ticket<4; ticket++) {
			SetLotteryTicketState(ticket, 3);
		}
		HuPrcSleep(15);
		while(GetLotteryDrawWheelState() != 0) {
			HuPrcVSleep();
		}
		offset.x = 50.0f;
		offset.z = 0.0f;
		offset.y = 100.0f;
		valid = 0;
		for(currTicket=ticket=0; ticket<3; ticket++, currTicket++) {
			BoardCameraBackup();
			SetLotteryDrawWheelState(3);
			BoardWinCreate(2, 2+messBase+ticket, BoardWinPortraitGetStar());
			BoardWinWait();
			BoardModelMotionShiftSet(hostMdl, hostMot[7], 0, 8, HU3D_MOTATTR_NONE);
			HuPrcSleep(8);
			while(BoardModelMotionTimeGet(hostMdl) < 26.0f) {
				HuPrcVSleep();
			}
			SetLotteryDrawState(1);
			HuPrcSleep(BoardRandMod(20));
			SetLotteryDrawWheelState(4);
			BoardCameraMotionStartEx(wheelMdl, NULL, &offset, 700, -1, 21);
			while(!BoardModelMotionEndCheck(hostMdl)) {
				HuPrcVSleep();
			}
			BoardModelMotionShiftSet(hostMdl, 1, 0, 8, HU3D_MOTATTR_LOOP);
			while(GetLotteryDrawWheelState() != 0) {
				HuPrcVSleep();
			}
			character = GetLotteryDrawWheelResult();
			UpdateLotteryTicketMatch(ticket, character);
			HuPrcSleep(120);
			if(CheckLotteryTicket()) {
				valid = 1;
				break;
			}
			if(ticket == 2) {
				player = GetLotteryTicketPlayer();
				BoardModelPosGet(hostMdl, &confetti_pos);
				confetti_pos.y += 400.0f;
				BoardConfettiCreate(&confetti_pos, 100, 200.0f);
				break;
			}
			BoardCameraRestore();
			BoardCameraMotionWait();
		}
		rot.x = -10.0f;
		rot.y = 0.0f;
		rot.z = 0.0f;
		BoardCameraMotionStartEx(focusMdl, &rot, NULL, 1480.0f, 25.0f, 20);
		if(valid) {
			BoardWinCreate(2, 9+messBase, BoardWinPortraitGetStar());
			BoardWinWait();
			SetLotteryDrawState(3);
			SetLotteryDrawWheelState(1);
			for(ticket=0; ticket<4; ticket++) {
				SetLotteryTicketState(ticket, 4);
			}
		} else {
			BoardAudSeqPause(1, 1, 1000);
			BoardModelMotionShiftSet(hostMdl, hostMot[3], 0, 8, HU3D_MOTATTR_LOOP);
			stream = HuAudSStreamPlay(10);
			while(HuAudSStreamStatGet(stream)) {
				HuPrcVSleep();
			}
			BoardAudSeqPause(1, 0, 1000);
			BoardWinCreate(2, 5+messBase, BoardWinPortraitGetStar());
			BoardWinWait();
			BoardCameraRestore();
			BoardCameraMotionWait();
			SetLotteryDrawState(3);
			SetLotteryDrawWheelState(1);
			for(ticket=0; ticket<4; ticket++) {
				SetLotteryTicketState(ticket, 4);
			}
			player_end.x = spacePos.x + -300.0f;
			player_end.y = spacePos.y;
			player_end.z = spacePos.z + -50.0f;
			BoardPlayerPosSetV(player, &player_end);
			BoardModelVisibilitySet(BoardPlayerModelGet(player), 1);
			BoardModelPosGet(hostMdl, &host_end);
			player_start = host_end;
			host_start.x = host_end.x+200.0f;
			host_start.y = host_end.y;
			host_start.z = host_end.z;
			StartHostMove(&host_end, &host_start, 25);
			BoardPlayerPosLerpStart(player, &player_end, &player_start, 25);
			while(GWPlayer[player].moving) {
				HuPrcVSleep();
			}
			BoardPlayerIdleSet(player);
			BoardModelMotionShiftSet(hostMdl, hostMot[0], 0, 8, HU3D_MOTATTR_LOOP);
			while(!CheckHostMove()) {
				HuPrcVSleep();
			}
			BoardModelMotionShiftSet(hostMdl, 1, 0, 8, HU3D_MOTATTR_LOOP);
			BoardStatusShowSetForce(player);
			BoardStatusShowSet(player, 1);
			BoardPlayerMotBlendSet(player, 0, 7);
			while(!BoardPlayerMotBlendCheck(player)) {
				HuPrcVSleep();
			}
			BoardWinCreate(2, 6+messBase, BoardWinPortraitGetStar());
			BoardWinWait();
			BoardAudSeqPause(1, 1, 1000);
			BoardModelMotionShiftSet(hostMdl, hostMot[1], 0, 8, HU3D_MOTATTR_NONE);
			star_pos.x = host_start.x;
			star_pos.y = 60.0f+host_start.y;
			star_pos.z = host_start.z;
			HuPrcSleep(30);
			BoardStarGive(player, &star_pos);
			BoardAudSeqPause(1, 0, 1000);
			BoardStatusShowSet(player, 0);
			StartHostMove(&host_start, &host_end, 25);
			BoardPlayerPosLerpStart(player, &player_start, &player_end, 25);
			BoardModelMotionShiftSet(hostMdl, hostMot[0], 0, 8, HU3D_MOTATTR_LOOP);
			while(!CheckHostMove()) {
				HuPrcVSleep();
			}
			BoardModelMotionShiftSet(hostMdl, 1, 0, 8, HU3D_MOTATTR_LOOP);
			while(GWPlayer[player].moving) {
				HuPrcVSleep();
			}
			BoardPlayerIdleSet(player);
			BoardModelVisibilitySet(BoardPlayerModelGet(player), 0);
			BoardConfettiStop();
			BoardModelVisibilitySet(wheelMdl, 0);
		}
		SetLotteryDrawState(4);
		BoardWinCreate(2, 7+messBase, BoardWinPortraitGetStar());
		BoardWinWait();
		BoardWinKill();
	}
}

static void KillLotteryTicket(void)
{
	s32 i;
	for(i=0; i<numTickets; i++) {
		SetLotteryTicketState(i, 5);
	}
}

typedef struct ticket_work {
	struct {
		u8 kill : 1;
		u8 player : 2;
		u8 done : 1;
		u8 index : 2;
	};
	s8 state;
	u8 unk02;
	s8 character[3];
	u16 angle;
	s16 group;
} TicketWork;

static void InitLotteryTicket(void)
{
	s32 i;
	s32 j;
	s32 playerSprTbl[] = {
		DATA_MAKE_NUM(DATADIR_BLAST5, 0),
		DATA_MAKE_NUM(DATADIR_BLAST5, 1),
		DATA_MAKE_NUM(DATADIR_BLAST5, 2),
		DATA_MAKE_NUM(DATADIR_BLAST5, 3),
		DATA_MAKE_NUM(DATADIR_BLAST5, 4),
		DATA_MAKE_NUM(DATADIR_BLAST5, 5),
		DATA_MAKE_NUM(DATADIR_BLAST5, 6),
		DATA_MAKE_NUM(DATADIR_BLAST5, 7),
	};
	s32 ownerSprTbl[] = {
		DATA_MAKE_NUM(DATADIR_BOARD, 46),
		DATA_MAKE_NUM(DATADIR_BOARD, 47),
		DATA_MAKE_NUM(DATADIR_BOARD, 48),
		DATA_MAKE_NUM(DATADIR_BOARD, 49),
		DATA_MAKE_NUM(DATADIR_BOARD, 50),
		DATA_MAKE_NUM(DATADIR_BOARD, 51),
		DATA_MAKE_NUM(DATADIR_BOARD, 52),
		DATA_MAKE_NUM(DATADIR_BOARD, 53),
	};
	s32 character;
	s16 sprite;
	s32 member;
	u8 ticket_player;
	omObjData *object;
	TicketWork *work;
	currTicket = 0;
	lotteryTicketObj[0] = lotteryTicketObj[1] = lotteryTicketObj[2] = lotteryTicketObj[3] = NULL;
	for(numTickets=i=0; i<4; i++) {
		if(!GWPlayer[i].draw_ticket) {
			continue;
		}
		object = omAddObjEx(boardObjMan, 257, 0, 0, -1, UpdateLotteryTicket);
		lotteryTicketObj[numTickets] = object;
		work = OM_GET_WORK_PTR(object, TicketWork);
		work->kill = 0;
		work->player = i;
		work->index = numTickets;
		work->angle = 0;
		work->unk02 = 0;
		work->done = 0;
		work->group = HuSprGrpCreate(6);
		object->trans.x = 680.0f;
		object->trans.y = 64.0f+(82.0f*numTickets);
		object->rot.x = 0.0f;
		object->rot.y = 0.0f;
		HuSprGrpPosSet(work->group, object->trans.x, object->trans.y);
		HuSprGrpScaleSet(work->group, 0.4f, 0.4f);
		BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BLAST5, 9), 2000, NULL, &sprite);
		HuSprGrpMemberSet(work->group, 0, sprite);
		HuSprAttrSet(work->group, 0, HUSPR_ATTR_LINEAR);
		HuSprScaleSet(work->group, 0, 2.5f, 2.5f);
		character = GWPlayer[i].character;
		BoardSpriteCreate(ownerSprTbl[character], 1200, NULL, &sprite);
		HuSprGrpMemberSet(work->group, 5, sprite);
		HuSprAttrSet(work->group, 5, HUSPR_ATTR_LINEAR);
		HuSprScaleSet(work->group, 5, 2.5f, 2.5f);
		HuSprPosSet(work->group, 5, -200, -32);
		HuSprScaleSet(work->group, 5, 1.75f, 1.75f);
		BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BLAST5, 8), 1200, NULL, &sprite);
		HuSprGrpMemberSet(work->group, 4, sprite);
		HuSprAttrSet(work->group, 4, HUSPR_ATTR_LINEAR);
		HuSprAttrSet(work->group, 4, HUSPR_ATTR_DISPOFF);
		HuSprAttrSet(work->group, 4, HUSPR_ATTR_ADDCOL);
		HuSprScaleSet(work->group, 4, 1.3f, 1.3f);
		ticket_player = GWPlayer[i].ticket_player;
		j=3;
		while(j>=0) {
			s32 player_spr;
			
			j--;
			work->character[j] = GWPlayer[ticket_player & 0x3].character;
			player_spr = playerSprTbl[work->character[j]];
			member = j+1;
			BoardSpriteCreate(player_spr, 1500, NULL, &sprite);
			HuSprGrpMemberSet(work->group, member, sprite);
			HuSprAttrSet(work->group, member, HUSPR_ATTR_LINEAR);
			HuSprPosSet(work->group, member, playerOfsTbl[j][0], playerOfsTbl[j][1]);
			ticket_player >>= 2;
		}
		numTickets++;
	}
}

static void UpdateLotteryTicket(omObjData *object)
{
	TicketWork *work = OM_GET_WORK_PTR(object, TicketWork);
	if(work->kill || BoardIsKill()) {
		HuSprGrpKill(work->group);
		omDelObjEx(HuPrcCurrentGet(), object);
		lotteryTicketObj[work->index] = NULL;
		return;
	}
	switch(work->state) {
		case 2:
			if(work->angle < 540) {
				float scale = 0.4f+(0.1f*sind((float)(work->angle%180)));
				HuSprGrpScaleSet(work->group, scale, scale);
				work->angle += 9;
			} else {
				work->angle = 0;
				work->state = 0;
				HuSprGrpScaleSet(work->group, 0.4f, 0.4f);
			}
			break;
			
		case 1:
			if(work->angle > 96) {
				u16 color = work->angle;
				HuSprColorSet(work->group, 0, color, color, color);
				HuSprColorSet(work->group, 1, color, color, color);
				HuSprColorSet(work->group, 2, color, color, color);
				HuSprColorSet(work->group, 3, color, color, color);
				HuSprColorSet(work->group, 5, color, color, color);
				work->angle -= 3;
			} else {
				work->angle = 0;
				work->state = 0;
			}
			break;
			
		case 3:
		case 4:
			if(work->angle != 0) {
				object->trans.x += object->rot.x;
				
				HuSprGrpPosSet(work->group, object->trans.x, object->trans.y);
				work->angle--;
			} else {
				if(work->state == 4) {
					BoardModelVisibilitySet(wheelMdl, 0);
				}
				SetLotteryTicketState(work->player, 0);
			}
			break;
			
		case 0:
			break;
		
		default:
			break;
			
			
	}
}

static void SetLotteryTicketState(s32 player, s32 state)
{
	TicketWork *work;
	omObjData *object;
	s32 i;
	for(i=0; i<numTickets; i++) {
		object = lotteryTicketObj[i];
		if(!object) {
			continue;
		}
		work = OM_GET_WORK_PTR(object, TicketWork);
		if(work->player == player) {
			work->state = state;
			work->angle = 0;
			switch(state) {
				case 2:
					HuSprAttrReset(work->group, 4, HUSPR_ATTR_DISPOFF);
					HuSprPosSet(work->group, 4, playerOfsTbl[currTicket][0], playerOfsTbl[currTicket][1]);
					break;
					
				case 1:
					work->angle = 255;
					work->done = 1;
					HuSprAttrSet(work->group, 4, HUSPR_ATTR_DISPOFF);
					break;
					
				case 3:
					object->rot.x = 472.0f-object->trans.x;
					object->rot.x /= 15.0f;
					work->angle = 15;
					break;
					
				case 4:
					object->rot.x = 680.0f-object->trans.x;
					object->rot.x /= 15.0f;
					work->angle = 15;
					break;
					
				case 5:
					work->kill = 1;
					
				default:
					break;
			}
			return;
		}
		
	}
}

static s32 GetLotteryTicketPlayer(void)
{
	s32 i;
	for(i=0; i<numTickets; i++) {
		omObjData *object = lotteryTicketObj[i];
		TicketWork *work = OM_GET_WORK_PTR(object, TicketWork);
		if(!work->done) {
			return work->player;
		}
	}
	return -1;
}

static s32 CheckLotteryTicket(void)
{
	TicketWork *work;
	omObjData *object;
	
	s32 i;
	for(i=0; i<numTickets; i++) {
		object = lotteryTicketObj[i];
		work = OM_GET_WORK_PTR(object, TicketWork);
		if(!work->done) {
			return 0;
		}
	}
	return 1;
}

static void UpdateLotteryTicketMatch(s32 progress, s32 character)
{
	s32 i;
	TicketWork *work;
	omObjData *object;
	s32 match_state;
	
	for(i=0; i<numTickets; i++) {
		object = lotteryTicketObj[i];
		work = OM_GET_WORK_PTR(object, TicketWork);
		if(!work->done) {
			if(work->character[progress] == character) {
				match_state = 2;
			} else {
				match_state = 1;
			}
			SetLotteryTicketState(work->player, match_state);
		}
	}
}

typedef struct host_move_work {
	struct {
		u8 kill : 1;
		u8 finish : 1;
	};
	u8 state;
	s16 time;
	s16 angle;
	s16 angle_end;
} HostMoveWork;

static void StartHostMove(Vec *from, Vec *to, s16 time)
{
	HostMoveWork *work;
	omObjData *object;
	float duration;
	float angle;
	if(time <= 0) {
		time = 1;
	}
	object = omAddObjEx(boardObjMan, 257, 0, 0, -1, ExecHostMove);
	hostMoveObj = object;
	work = OM_GET_WORK_PTR(object, HostMoveWork);
	work->kill = 0;
	work->finish = 0;
	work->time = time;
	work->state = 0;
	OSs16tof32(&time, &duration);
	omSetTra(object, from->x, from->y, from->z);
	omSetRot(object, (to->x-from->x)/duration, 0.0f, (to->z-from->z)/duration);
	omSetSca(object, to->x, to->y, to->z);
	angle = atan2d(object->rot.x, object->rot.z);
	work->angle = 0;
	OSf32tos16(&angle, &work->angle_end);
	BoardModelMotionShiftSet(hostMdl, hostMot[0], 0, 8, HU3D_MOTATTR_LOOP);
	BoardModelMotionSpeedSet(hostMdl, 3.0f);
}

static void ExecHostMove(omObjData *object)
{
	HostMoveWork *work = OM_GET_WORK_PTR(object, HostMoveWork);
	float angle;
	float angle_end;
	if(work->kill || BoardIsKill()) {
		hostMoveObj = NULL;
		omDelObjEx(HuPrcCurrentGet(), object);
		return;
	}
	OSs16tof32(&work->angle, &angle);
	OSs16tof32(&work->angle_end, &angle_end);
	switch(work->state) {
		case 0:
			if(BoardDAngleCalcRange(&angle, angle_end, 10.0f)) {
				if(work->finish) {
					work->kill = 1;
				} else {
					work->state = 1;
				}
				BoardModelMotionSpeedSet(hostMdl, 1.0f);
			}
			OSf32tos16(&angle, &work->angle);
			BoardModelRotYSet(hostMdl, angle);
			break;
			
		case 1:
			if(work->time) {
				work->time--;
				object->trans.x += object->rot.x;
				object->trans.y += object->rot.y;
				object->trans.z += object->rot.z;
			} else {
				object->trans.x = object->scale.x;
				object->trans.y = object->scale.y;
				object->trans.z = object->scale.z;
				work->angle_end = 0;
				work->finish = 1;
				work->state = 0;
				BoardModelMotionSpeedSet(hostMdl, 3.0f);
			}
			break;
			
		default:
			break;
	}
	BoardModelPosSet(hostMdl, object->trans.x, object->trans.y, object->trans.z);
}

static s32 CheckHostMove(void)
{
	if(hostMoveObj) {
		return 0;
	} else {
		return 1;
	}
}

static void CreateStopWin(void)
{
	s32 mess = MAKE_MESSID(0x12, 0x11);
	float size[2];
	float pos_x, pos_y;
	HuWinMesMaxSizeGet(1, size, mess);
	pos_x = -10000;
	pos_y = 352;
	stopWin = HuWinCreate(pos_x, pos_y, size[0], size[1], 0);
	HuWinBGTPLvlSet(stopWin, 0.0f);
	HuWinMesSpeedSet(stopWin, 0);
	HuWinMesSet(stopWin, mess);
}

typedef struct last5_roulette_work {
	struct {
		u8 kill : 1;
		u8 state : 3;
	};
	s8 choice;
	s8 fade_speed;
	s8 choices[4];
	s16 alpha;
	u16 switch_timer;
	u8 switch_vel;
	u8 switch_accel;
	s16 model;
} Last5RouletteWork;

static void CreateLast5Roulette(void)
{
	Last5RouletteWork *work;
	omObjData *object;
	s32 choice1, choice2;
	Vec pos;
	object = omAddObjEx(boardObjMan, 257, 0, 0, -1, UpdateLast5Roulette);
	last5RouletteObj = object;
	work = OM_GET_WORK_PTR(object, Last5RouletteWork);
	work->kill = 0;
	work->choice = 0;
	work->switch_timer = 0;
	work->switch_vel = 4;
	work->state = 2;
	work->alpha = 0;
	work->fade_speed = 0;
	work->switch_accel = 5;
	choice1 = BoardRandMod(3)+2;
	do {
		choice2 = BoardRandMod(3)+2;
	} while(choice1 == choice2);
	work->choices[0] = 1;
	work->choices[1] = 1;
	work->choices[2] = choice1;
	work->choices[3] = choice2;
	work->model = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BLAST5, 10), NULL, 0);
	pos.x = 150.0f+spacePos.x;
	pos.y = 177.0f+spacePos.y;
	pos.z = -135.0f+spacePos.z;
	BoardModelPosSetV(work->model, &pos);
	BoardModelMotionStart(work->model, 0, 0);
	BoardModelMotionSpeedSet(work->model, 0);
}

static void UpdateLast5Roulette(omObjData *object)
{
	Last5RouletteWork *work = OM_GET_WORK_PTR(object, Last5RouletteWork);
	if(work->kill || BoardIsKill()) {
		BoardModelHookReset(wheelMdl);
		if(work->model != -1) {
			BoardModelKill(work->model);
		}
		last5RouletteObj = NULL;
		omDelObjEx(HuPrcCurrentGet(), object);
		return;
	}
	
	switch(work->state) {
		case 3:
			if(work->switch_timer == 0) {
				work->switch_vel += work->switch_accel;
				work->switch_accel++;
				if(work->switch_vel > 60 || (work->switch_vel > 40 && BoardRandMod(100) > 80)) {
					if((GWBoardGet() == BOARD_ID_MAIN1 || GWBoardGet() == BOARD_ID_MAIN3) && work->choices[work->choice] == 2) {
						work->switch_timer++;
						return;
					} else {
						HuAudFXPlay(870);
						SetLast5RouletteState(0);
						break;
					}
				}
			}
			
		case 2:
			if(work->switch_timer < work->switch_vel) {
				work->switch_timer++;
			} else {
				s32 choice = work->choices[work->choice];
				float time;
				do {
					work->choice = BoardRandMod(4);
				} while(work->choices[work->choice] == choice);
				OSs8tof32(&work->choices[work->choice], &time);
				HuAudFXPlay(855);
				BoardModelMotionTimeSet(work->model, 0.1f+time);
				work->switch_timer = 0;
			}
			break;
			
		case 0:
			break;
			
		default:
			break;
	}
	if(work->fade_speed) {
		work->alpha += work->fade_speed;
		if(work->alpha >= 255) {
			work->alpha = 255;
			work->fade_speed = 0;
		}
		if(work->alpha < 0) {
			work->alpha = 0;
			work->fade_speed = 0;
		}
		BoardModelAlphaSet(work->model, work->alpha);
	}
}

static void SetLast5RouletteFade(s32 flag)
{
	Last5RouletteWork *work;
	if(!last5RouletteObj) {
		return;
	}
	work = OM_GET_WORK_PTR(last5RouletteObj, Last5RouletteWork);
	if(flag) {
		work->fade_speed = 4;
	} else {
		work->fade_speed = -4;
	}
}

static void SetLast5RouletteState(s32 state)
{
	Last5RouletteWork *work;
	if(!last5RouletteObj) {
		return;
	}
	work = OM_GET_WORK_PTR(last5RouletteObj, Last5RouletteWork);
	work->state = state;
}

static s32 GetLast5RouletteState(void)
{
	Last5RouletteWork *work;
	if(!last5RouletteObj) {
		return -1;
	}
	work = OM_GET_WORK_PTR(last5RouletteObj, Last5RouletteWork);
	return work->state;
}

static s32 GetLast5RouletteResult(void)
{
	Last5RouletteWork *work;
	if(!last5RouletteObj) {
		return -1;
	}
	work = OM_GET_WORK_PTR(last5RouletteObj, Last5RouletteWork);
	return work->choices[work->choice];
}

typedef struct team_result_work {
	struct {
		u8 kill : 1;
	};
	u8 delay;
	u8 player[2][2];
	s16 group[2];
} TeamResultWork;

static void CreateTeamResultWork(TeamResultWork *work);

static void CreateTeamResult(void)
{
	TeamResultWork *work;
	omObjData *object;
	s32 i;
	s32 j;
	s32 coins[2];
	s32 stars[2];
	u32 score[2];
	s32 team, player;
	s32 rank1, rank2;
	object = omAddObjEx(boardObjMan, 268, 0, 0, -1, UpdateTeamResult);
	teamResultObj = object;
	work = OM_GET_WORK_PTR(object, TeamResultWork);
	CreateTeamResultWork(work);
	coins[0] = coins[1] = stars[0] = stars[1] = 0;
	for(i=0; i<2; i++) {
		for(j=0; j<2; j++) {
			coins[i] += BoardPlayerCoinsGet(work->player[i][j]);
			stars[i] += GWStarsGet(work->player[i][j]);
		}
	}
	for(i=0; i<2; i++) {
		score[i] = coins[i]+(stars[i] << 11);
	}
	team = BoardRandMod(2);
	player = BoardRandMod(2);
	if(score[0] >= score[1]) {
		object->trans.x = -108.0f;
		object->trans.y = 152.0f;
		object->rot.x = -108.0f;
		object->rot.y = 302.0f;
		if(score[0] == score[1]) {
			last5Player = work->player[team][player];
		} else {
			rank1 = GWPlayer[work->player[1][0]].rank;
			rank2 = GWPlayer[work->player[1][1]].rank;
			if(rank1 == rank2) {
				last5Player = work->player[1][player];
			} else {
				if(rank1 < rank2) {
					last5Player = work->player[1][1];
				} else {
					last5Player = work->player[1][0];
				}
			}
		}
	} else {
		object->rot.x = -108.0f;
		object->rot.y = 152.0f;
		object->trans.x = -108.0f;
		object->trans.y = 302.0f;
		rank1 = GWPlayer[work->player[0][0]].rank;
		rank2 = GWPlayer[work->player[0][1]].rank;
		if(rank1 == rank2) {
			last5Player = work->player[0][player];
		} else {
			if(rank1 < rank2) {
				last5Player = work->player[0][1];
			} else {
				last5Player = work->player[0][0];
			}
		}
	}
}

static void CreateTeamResultWork(TeamResultWork *work)
{
	GXColor color = { 128, 128, 128, 0 };
	s32 i;
	s32 character;
	s16 group;
	s32 j;
	s32 team1_idx, team2_idx;
	s16 sprite;
	s32 spr_file;
	s16 prio;
	float x, y;
	for(team1_idx=team2_idx=i=0; i<4; i++) {
		s32 team = GWPlayer[i].team;
		if(team == 0) {
			work->player[0][team1_idx] = i;
			team1_idx++;
		} else {
			work->player[1][team2_idx] = i;
			team2_idx++;
		}
	}
	for(j=0; j<2; j++) {
		group = HuSprGrpCreate(15);
		work->group[j] = group;
		for(i=0; i<13; i++) {
			spr_file = teamSprTbl[i];
			prio = teamSprPrioTbl[i];
			
			BoardSpriteCreate(spr_file, prio, NULL, &sprite);
			HuSprGrpMemberSet(group, i, sprite);
			HuSprAttrSet(group, i, HUSPR_ATTR_NOANIM);
			HuSprAttrSet(group, i, HUSPR_ATTR_LINEAR);
			HuSprPosSet(group, i, teamSprPosTbl[i][0], teamSprPosTbl[i][1]);
		}
		HuSprTPLvlSet(group, 0, 0.7f);
		HuSprScaleSet(group, 0, 1.0f, 2.5f);
		HuSprColorSet(group, 0, color.r, color.g, color.b);
		if(!GWPlayer[work->player[j][0]].com) {
			HuSprAttrSet(group, 11, HUSPR_ATTR_DISPOFF);
		}
		if(!GWPlayer[work->player[j][1]].com) {
			HuSprAttrSet(group, 12, HUSPR_ATTR_DISPOFF);
		}
		if(j == 0) {
			HuSprBankSet(group, 1, 2);
		} else {
			HuSprBankSet(group, 1, 1);
		}
		for(i=0; i<2; i++) {
			character = GWPlayer[work->player[j][i]].character;
			BoardSpriteCreate(teamCharSprTbl[character], 1500, NULL, &sprite);
			HuSprGrpMemberSet(group, i+13, sprite);
			HuSprAttrSet(group, i+13, HUSPR_ATTR_LINEAR);
			x = teamSprPosTbl[i+13][0];
			y = teamSprPosTbl[i+13][1];
			HuSprPosSet(group, i+13, x, y);
		}
	}
}

static void SetTeamResultTarget(s32 team, Vec *pos)
{
	if(!teamResultObj || !pos) {
		return;
	}
	if(team) {
		teamResultObj->rot.x = pos->x;
		teamResultObj->rot.y = pos->y;
	} else {
		teamResultObj->trans.x = pos->x;
		teamResultObj->trans.y = pos->y;
	}
}

static void GetTeamResultTarget(s32 team, Vec *pos)
{
	if(!teamResultObj || !pos) {
		return;
	}
	if(team) {
		pos->x = teamResultObj->rot.x;
		pos->y = teamResultObj->rot.y;
	} else {
		pos->x = teamResultObj->trans.x;
		pos->y = teamResultObj->trans.y;
	}
}

static void KillTeamResult(void)
{
	TeamResultWork *work;
	if(!teamResultObj) {
		return;
	}
	work = OM_GET_WORK_PTR(teamResultObj, TeamResultWork);
	work->kill = 1;
}

static void UpdateTeamResult(omObjData *object)
{
	TeamResultWork *work;
	s32 i, j;
	work = OM_GET_WORK_PTR(object, TeamResultWork);
	if(work->kill || BoardIsKill()) {
		HuSprGrpKill(work->group[0]);
		HuSprGrpKill(work->group[1]);
		teamResultObj = NULL;
		omDelObjEx(HuPrcCurrentGet(), object);
		return;
	}
	if(work->delay) {
		work->delay--;
		return;
	}
	{
		s8 rank[2];
		u32 score[2];
		s32 coins[2];
		s32 stars[2];
		
		
		
		coins[0] = coins[1] = stars[0] = stars[1] = 0;
		for(i=0; i<2; i++) {
			for(j=0; j<2; j++) {
				coins[i] += BoardPlayerCoinsGet(work->player[i][j]);
				stars[i] += GWStarsGet(work->player[i][j]);
			}
		}
		for(i=0; i<2; i++) {
			s32 star_val;
			s32 coin_val;
			
			score[i] = coins[i]+(stars[i] << 11);
			coin_val = coins[i];
			if(coin_val > 999) {
				coin_val = 999;
			}
			star_val = stars[i];
			if(star_val > 999) {
				star_val = 999;
			}
			BoardSpriteDigitUpdate(work->group[i], 3, coin_val);
			BoardSpriteDigitUpdate(work->group[i], 7, star_val);
		}
		if(score[0] == score[1]) {
			rank[0] = rank[1] = 0;
		} else if(score[0] > score[1]) {
			rank[0] = 0;
			rank[1] = 1;
		} else {
			rank[1] = 0;
			rank[0] = 1;
		}
		HuSprBankSet(work->group[0], 2, rank[0]);
		HuSprBankSet(work->group[1], 2, rank[1]);
		HuSprGrpPosSet(work->group[0], object->trans.x, object->trans.y);
		HuSprGrpPosSet(work->group[1], object->rot.x, object->rot.y);
	}
}
