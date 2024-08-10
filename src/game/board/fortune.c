#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/tutorial.h"
#include "game/board/audio.h"
#include "game/board/ui.h"
#include "game/board/space.h"

#include "game/wipe.h"

static Vec camTargetFortune;
static Vec camPosFortune;

typedef struct platform_work {
    struct {
        u8 kill : 1;
		u8 state : 2;
    };
    s16 unk02;
    s16 model;
} PlatformWork;

static u32 comPrizeMessTbl[] = {
	MAKE_MESSID(0x1C, 0x09),
	MAKE_MESSID(0x1C, 0x0A),
	MAKE_MESSID(0x1C, 0x0B),
	MAKE_MESSID(0x1C, 0x0D),
	MAKE_MESSID(0x1C, 0x0C),
	MAKE_MESSID(0x1C, 0x0E)
};

static s8 currPlayer;
static s8 comPlayer2;
static s8 comPlayer1;
static s8 comPrize;
static s8 comCoin;
static s8 comStar;
static omObjData *fortunePlatformObj;
static Process *fortuneProc;

static void FortuneExec(void);
static void DestroyFortune(void);
static void FortuneMain(void);
static void FortunePostMG(void);

static void CreateFortunePlatform(void);
static void ExecFortunePlatform(omObjData *object);

static void CameraCalcFortune(BoardCameraData *camera);

static void ExecComFortuneWin(void);

static void ConfigComFortune(void);

static void ComFortuneAddStar(s32 player1, s32 player2, s32 max_stars);
static void ComFortuneAddCoin(s32 player1, s32 player2, s32 max_coins);
static void ComFortuneSwapCoin(s32 player1, s32 player2);
static void ComFortuneSwapStar(s32 player1, s32 player2);

void BoardFortuneExec(s32 player, s32 space)
{
	if(_CheckFlag(FLAG_ID_MAKE(1, 11))) {
		HuAudFXPlay(842);
		BoardCameraViewSet(2);
		BoardPlayerMotBlendSet(player, 0, 15);
		while(!BoardPlayerMotBlendCheck(player)) {
			HuPrcVSleep();
		}
		BoardCameraMotionWait();
		BoardTutorialHookExec(17, 0);
		GWPlayer[player].color = 3;
		return;
	}
	if(BoardPlayerSizeGet(player) == 2) {
		return;
	}
	fortuneProc = HuPrcChildCreate(FortuneExec, 8195, 14336, 0, boardMainProc);
	HuPrcDestructorSet2(fortuneProc, DestroyFortune);
	currPlayer = player;
	while(fortuneProc) {
		HuPrcVSleep();
	}
	GWPlayer[player].color = 3;
}

static void FortuneExec(void)
{
	BoardAudSeqFadeOut(0, 1000);
	if(!_CheckFlag(FLAG_ID_MAKE(1, 5))) {
		GWPlayer[currPlayer].show_next = 0;
		FortuneMain();
	} else {
		FortunePostMG();
	}
	HuPrcEnd();
}

static void DestroyFortune(void)
{
	fortuneProc = NULL;
}

static void FortuneMain(void)
{
	s32 i;
	s32 sp8 = -1;
	s32 dir_table[] = {
		DATADIR_W01,
		DATADIR_W02,
		DATADIR_W03,
		DATADIR_W04,
		DATADIR_W05,
		DATADIR_W06,
		DATADIR_W10,
		DATADIR_W20,
		DATADIR_W21
	};
	HuAudFXPlay(842);
	BoardPlayerMotBlendSet(currPlayer, 0, 15);
	while(!BoardPlayerMotBlendCheck(currPlayer)) {
		HuPrcVSleep();
	}
	for(i=0; i<4; i++) {
		if(GWPlayerTeamGet(i)) {
			GWPlayer[i].team_backup = 1;
		} else {
			GWPlayer[i].team_backup = 0;
		}
		if(i == currPlayer) {
			GWPlayerCfg[i].group = 0;
		} else {
			GWPlayerCfg[i].group = 1;
		}
	}
	BoardCameraViewSet(3);
	BoardCameraMotionWait();
	CreateFortunePlatform();
	omVibrate(currPlayer, 60, 6, 6);
	BoardCameraPosCalcFuncSet(CameraCalcFortune);
	HuPrcSleep(60);
	_SetFlag(0x1001C);
	WipeColorSet(255, 255, 255);
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuAudFXAllStop();
	BoardAudSeqFadeOutAll();
	_SetFlag(0x1000E);
	BoardCameraPosCalcFuncSet(NULL);
	if(fortunePlatformObj) {
		OM_GET_WORK_PTR(fortunePlatformObj, PlatformWork)->kill = 1;
	}
	while(fortunePlatformObj) {
		HuPrcVSleep();
	}
	if(GWPlayer[GWSystem.player_curr].com && !GWMGShowComGet()) {
		HuPrcSleep(60);
		for(i=0; i<4; i++) {
			s32 bit11 = GWPlayer[i].team_backup;
			GWPlayer[i].team = bit11;
			GWPlayerCfg[i].group = bit11;
		}
		ConfigComFortune();
		FortunePostMG();
		BoardMusStartBoard();
		ExecComFortuneWin();
		return;
	} else {
		GWMGAvailSet(444);
		GWSystem.mg_next = 43;
		_SetFlag(0x10005);
		BoardNextOvlSet(OVL_M444);
	}
}

static void FortunePostMG(void)
{
	s16 space;
	Vec pos;
	BoardStatusItemSet(1);
	space = GWPlayer[GWSystem.player_curr].space_curr;
	BoardSpacePosGet(0, space, &pos);
	BoardPlayerPosSetV(GWSystem.player_curr, &pos);
	BoardCameraMoveSet(0);
	BoardCameraViewSet(2);
	BoardCameraMotionWait();
	BoardCameraMoveSet(1);
	GWPlayer[currPlayer].show_next = 1;
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	_ClearFlag(0x1001C);
	HuPrcSleep(12);
}

static void CreateFortunePlatform(void)
{
	PlayerState *player;
	Vec pos, rot;
	PlatformWork *work;
	fortunePlatformObj = omAddObjEx(boardObjMan, 257, 0, 0, -1, ExecFortunePlatform);
	work = OM_GET_WORK_PTR(fortunePlatformObj, PlatformWork);
	work->kill = 0;
	work->unk02 = 0;
	work->model = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 3), NULL, 0);
	BoardSpacePosGet(0, GWPlayer[currPlayer].space_curr, &pos);
	BoardSpaceRotGet(0, GWPlayer[currPlayer].space_curr, &rot);
	BoardModelPosSetV(work->model, &pos);
	BoardCameraTargetModelSet(work->model);
	BoardModelHookSet(work->model, "player", BoardPlayerModelGet(currPlayer));
	BoardModelMotionStart(work->model, 0, 0);
	BoardCameraPosGet(&camPosFortune);
	BoardCameraTargetGet(&camTargetFortune);
	HuAudFXPlay(834);
}

static void CameraCalcFortune(BoardCameraData *camera)
{
	camera->pos = camPosFortune;
	camera->up.x = 0;
	camera->up.y = 1;
	camera->up.z = 0;
	camera->target = camTargetFortune;
}

static void ExecFortunePlatform(omObjData *object)
{
	PlatformWork *work = OM_GET_WORK_PTR(object, PlatformWork);
	if(work->kill || BoardIsKill()) {
		Vec pos;
		fortunePlatformObj = NULL;
		BoardModelHookReset(work->model);
		BoardSpacePosGet(0, GWPlayer[currPlayer].space_curr, &pos);
		BoardPlayerPosSetV(currPlayer, &pos);
		BoardModelKill(work->model);
		omDelObjEx(HuPrcCurrentGet(), object);
		return;
	}
	switch(work->state) {
		case 0:
		{
			s16 model;
			ModelData *model_ptr;
			HsfObject *focus_obj;
			if(BoardModelMotionEndCheck(work->model)) {
				work->state = 1;
			}
			model = BoardModelIDGet(work->model);
			model_ptr = &Hu3DData[model];
			Hu3DMotionExec(model, model_ptr->unk_08, model_ptr->unk_64, 0);
			focus_obj = Hu3DModelObjPtrGet(model, "player");
			BoardModelPosGet(work->model, &camTargetFortune);
			camTargetFortune.x += focus_obj->data.curr.pos.x;
			camTargetFortune.y += focus_obj->data.curr.pos.y;
			camTargetFortune.z += focus_obj->data.curr.pos.z;
		}
			
			break;
			
		case 1:
			break;
			
		default:
			break;
	}
}

static void ExecComFortuneWin(void)
{
	s32 player_curr = GWSystem.player_curr;
	u32 mess_player1;
	u32 mess_player2;
	u32 mess_main;
	u32 mess_prize;

	GWSystem.player_curr = -1;
	mess_player1 = BoardPlayerGetCharMess(comPlayer1);
	mess_player2 = BoardPlayerGetCharMess(comPlayer2);
	mess_prize = comPrizeMessTbl[comPrize];
	if(comPrize == 0 || comPrize == 5 || comPrize == 3) {
		mess_main = MAKE_MESSID(0x1C, 0x12);
	} else {
		if(comPrize == 2) {
			if(comCoin == 0) {
				mess_main = MAKE_MESSID(0x1C, 0x13);
			} else {
				mess_main = MAKE_MESSID(0x1C, 0x11);
			}
		} else {
			if(comPrize == 1 || comPrize == 4) {
				if(comStar == 0) {
					mess_main = MAKE_MESSID(0x1C, 0x14);
				} else {
					mess_main = MAKE_MESSID(0x1C, 0x11);
				}
			}
		}
	}
	BoardWinCreate(2, mess_main, -1);
	BoardWinInsertMesSet(mess_player1, 0);
	BoardWinInsertMesSet(mess_prize, 1);
	BoardWinInsertMesSet(mess_player2, 2);
	BoardWinWait();
	BoardWinKill();
	GWSystem.player_curr = player_curr;
}

static void ConfigComFortune(void)
{
	s32 type;
	s32 random;
	s8 prizeTbl[] = { 5, 3, 0, 1, 4 };
	random = BoardRandMod(100);
	if(random > 95) {
		type = 0;
	} else if(random > 60) {
		type = 1;
	} else {
		type = 2;
	}
	switch(type) {
		case 0:
			comPrize = prizeTbl[BoardRandMod(2)];
			break;
			
		case 1:
			comPrize = prizeTbl[BoardRandMod(3)+2];
			break;
			
		case 2:
			comPrize = 2;
			break;

		default:
			break;
	}
	comPlayer1 = BoardRandMod(4);
	comPlayer2 = comPlayer1;
	while(comPlayer2 == comPlayer1) {
		comPlayer2 = BoardRandMod(4);
	}
	switch(comPrize) {
		case 4:
			ComFortuneAddStar(comPlayer1, comPlayer2, 2);
			break;
			
		case 1:
			ComFortuneAddStar(comPlayer1, comPlayer2, 1);
			break;
			
		case 2:
			ComFortuneAddCoin(comPlayer1, comPlayer2, 20);
			break;
			
		case 3:
			ComFortuneSwapCoin(comPlayer1, comPlayer2);
			ComFortuneSwapStar(comPlayer1, comPlayer2);
			break;
			
		case 0:
			ComFortuneSwapCoin(comPlayer1, comPlayer2);
			break;
			
		case 5:
			ComFortuneSwapStar(comPlayer1, comPlayer2);
			break;
	}
}

static void ComFortuneAddStar(s32 player1, s32 player2, s32 max_stars)
{
	s32 stars = GWStarsGet(player1);
	comStar = stars;
	if(stars > max_stars) {
		stars = max_stars;
	}
	BoardPlayerStarsAdd(player1, -stars);
	BoardPlayerStarsAdd(player2, stars);
}

static void ComFortuneAddCoin(s32 player1, s32 player2, s32 max_stars)
{
	s32 stars = BoardPlayerCoinsGet(player1);
	comCoin = stars;
	if(stars > max_stars) {
		stars = max_stars;
	}
	BoardPlayerCoinsAdd(player1, -stars);
	BoardPlayerCoinsAdd(player2, stars);
}

static void ComFortuneSwapCoin(s32 player1, s32 player2)
{
	s32 temp;
	temp = BoardPlayerCoinsGet(player1);
	BoardPlayerCoinsSet(player1, BoardPlayerCoinsGet(player2));
	BoardPlayerCoinsSet(player2, temp);
}

static void ComFortuneSwapStar(s32 player1, s32 player2)
{
	s32 temp;
	temp = GWStarsGet(player1);
	GWStarsSet(player1, GWStarsGet(player2));
	GWStarsSet(player2, temp);
}
