#include "game/object.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/hsfmotion.h"
#include "game/init.h"
#include "game/minigame_seq.h"
#include "game/chrman.h"
#include "game/sprite.h"
#include "game/window.h"
#include "ext_math.h"

#include "REL/E3SetupDLL.h"

#ifndef __MWERKS__
void HuSysVWaitSet(s16 vcount);
#endif

static struct {
	s16 playerCnt;
	s16 rumble;
	s16 mode;
	s16 board;
	s16 port[4];
	s16 character[4];
} configE3;

E3Pad e3PadData[4];
s16 e3PadCtrl;
s16 e3ConfigPlayerCnt;
static s32 e3EvtNo;
s32 e3ExitEnableF;
s32 lbl_2_bss_B0;
OverlayID e3NextOvl;
s32 e3NextEvent;
u32 e3ExitMode;
static s32 needCharKill;
float e3CameraFov;
omObjData *e3MenuMainObj;
omObjData *e3ViewObj;
omObjData *e3OvlWatchObj;
static omObjData *cameraObj;
static omObjData *lbl_2_bss_84[2];
static omObjData *configModeObj[4];
omObjData *e3BGObj;
omObjData *lbl_2_bss_6C;
static s16 lightE3;
s16 lbl_2_bss_62[4];
s16 lbl_2_bss_60;
Vec lbl_2_bss_54;
Vec lbl_2_bss_48;
float lbl_2_bss_44;
s16 lbl_2_bss_40;
s32 lbl_2_bss_3C;
s16 lbl_2_bss_3A;
s16 lbl_2_bss_38;
s16 lbl_2_bss_36;
s16 lbl_2_bss_34;
s16 lbl_2_bss_2A[5];
static s16 repBtn;

static Vec shadowPos = {
	0, 12000, 0
};

static Vec shadowTarget = {
	0, 0, 0
};

static Vec shadowUp = {
	0, 0, -1
};

Vec lbl_2_data_274[] = {
	477.5, 500, -425,
	-477.5, 500, -425,
	477.5, 500, 425,
	-477.5, 500, 425,
	0.11, -1, -0.22,
	-0.11, -1, -0.22,
	0.11, -1, 0.22,
	-0.11, -1, 0.22,
};

static s16 playerCntTbl[] = {
	1, 2, 3, 4
};

static s16 charTbl[] = {
	0, 1, 2, 3,
	-1, -1, 6, 7
};

static s32 charSfxTbl[] = {
	295,
	359,
	423,
	487,
	551,
	615,
	679,
	743
};

void ObjectSetup(void)
{
	e3EvtNo = omovlevtno;
	HuAudSndGrpSetSet(0);
	e3ExitEnableF = 0;
	lbl_2_bss_B0 = 0;
	e3PadCtrl = 0;
	e3NextOvl = 0;
	e3NextEvent = 0;
	e3ExitMode = 0;
	switch(e3EvtNo) {
		default:
		case 0:
			repBtn = 0;
			needCharKill = 1;
			E3MainInit();
			break;
			
		case 1:
			repBtn = 1;
			needCharKill = 0;
			E3MGSelectInit();
			break;
	}
}

static void InitCamera(omObjData *object);
static void InitMenuControl(omObjData *object);
static void InitPlayerCnt(omObjData *object);
static void InitCharSel(omObjData *object);
static void InitRumbleCfg(omObjData *object);
static void InitModeSel(omObjData *object);

void E3MainInit(void)
{
	s32 idx = E3PadRead();
	s32 port;
	Process *objman;
	if(idx == 0) {
		OSReport("No pad detected\n");
		idx++;
	}
	e3ConfigPlayerCnt = idx;
	configE3.playerCnt = idx-1;
	port = (GWRumbleGet()) ? 1 : 0;
	configE3.rumble = port;
	configE3.mode = 0;
	configE3.board = 0;
	for(port=0,idx=0; port<4; idx++, port++) {
		while(idx < 8) {
			if(charTbl[idx] >= 0) {
				break;
			}
			idx++;
		}
		configE3.character[port] = idx;
	}
	for(port=0,idx=0; port<4; port++) {
		if(!e3PadData[port].enable) {
			configE3.port[idx] = port;
			if(idx == 0) {
				e3PadCtrl = port;
			}
			idx++;
		}
	}
	for(port=0; port<4; port++) {
		if(e3PadData[port].enable) {
			configE3.port[idx] = port;
			idx++;
		}
	}
	HuSysVWaitSet(1);
	objman = omInitObjMan(80, 8192);
	
	HuWinInit(1);
	CRot.x = -4;
	CRot.y = 0;
	CRot.z = 0;
	Center.x = 0;
	Center.y = 160;
	Center.z = 0;
	CZoom = 1960;
	e3CameraFov = 40;
	Hu3DCameraCreate(1);
	Hu3DCameraPerspectiveSet(1, e3CameraFov, 100, 25000, 4.0f/3.0f);
	Hu3DShadowCreate(e3CameraFov*0.3f, 100, 25000);
	Hu3DShadowTPLvlSet(0.6f);
	Hu3DShadowPosSet(&shadowPos, &shadowUp, &shadowTarget);
	e3ViewObj = omAddObjEx(objman, 32730, 0, 0, -1, omOutView);
	cameraObj = omAddObjEx(objman, 199, 0, 0, -1, InitCamera);
	e3OvlWatchObj = omAddObjEx(objman, 200, 0, 0, -1, E3OvlWatchInit);
	e3MenuMainObj = omAddObjEx(objman, 10, 0, 0, -1, InitMenuControl);
	e3BGObj = omAddObjEx(objman, 20, 0, 0, -1, E3BGCreate);
	configModeObj[0] = omAddObjEx(objman, 30, 0, 0, -1, InitPlayerCnt);
	configModeObj[0]->work[0] = 1;
	configModeObj[1] = omAddObjEx(objman, 30, 0, 0, -1, InitCharSel);
	configModeObj[2] = omAddObjEx(objman, 30, 0, 0, -1, InitRumbleCfg);
	configModeObj[3] = omAddObjEx(objman, 30, 0, 0, -1, InitModeSel);
	E3LightInit();
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
}

void E3LightInit(void)
{
	s32 i;
	lightE3 = lbl_2_bss_60 = -1;
	for(i=0; i<4; i++) {
		lbl_2_bss_62[i] = -1;
	}
	lbl_2_bss_54.x = 0;
	lbl_2_bss_54.y = 1500;
	lbl_2_bss_54.z = 0;
	lbl_2_bss_48.x = 0;
	lbl_2_bss_48.y = -1;
	lbl_2_bss_48.z = 0;
	lbl_2_bss_44 = 26;
	lbl_2_bss_40 = 4;
	lightE3 = Hu3DGLightCreate(0, 1500, 0, 0, -1, 0, 255, 255, 255);
	Hu3DGLightStaticSet(lightE3, 1);
	Hu3DGLightInfinitytSet(lightE3);
}

static float GetStickX(s8 value)
{
	float new_value;
	if(value > 69) {
		value = 69;
	} else if(value < -69) {
		value = -69;
	}
	new_value = value;
	new_value /= 69;
	return new_value;
}

static s16 GetStickY(s8 value)
{
	float new_value;
	if(value > 69) {
		value = 69;
	} else if(value < -69) {
		value = -69;
	}
	new_value = value;
	new_value *= 255.0f/69;
	return new_value;
}

static u16 GetBtn(s16 player)
{
	u16 value;
	if(repBtn) {
		value = HuPadDStkRep[player];
		value |= HuPadBtnRep[player];
	} else {
		value = HuPadDStk[player];
		value |= HuPadBtn[player];
	}
	return value;
}

static u16 GetBtnDown(u16 button, u16 buttonLast)
{
	u16 down = PADButtonUp(button, buttonLast);
	return down;
}

u16 E3PadUpdate(s16 player, E3Pad *pad)
{
	pad->enable = HuPadStatGet(player);
	if(!pad->enable) {
		u16 btn = GetBtn(player);
		pad->btnDown = PADButtonUp(btn, pad->btn);
		pad->btn = btn;
	} else {
		pad->btnDown = pad->btn = 0;
	}
	return pad->btnDown;
}

s16 E3PadRead(void)
{
	s16 i;
	s16 players;
	for(i=0, players=0; i<4; i++) {
		E3PadUpdate(i, &e3PadData[i]);
		if(!e3PadData[i].enable) {
			players++;
		}
	}
	return players;
}

float MotionMaxTimeGet(s16 arg0)
{
    MotionData *temp_r31 = &Hu3DMotion[arg0];
    HsfMotion *temp_r30;
    s16 temp_r29;

    temp_r30 = temp_r31->hsfData->motion;
    temp_r29 = temp_r30->len;
    return temp_r29;
}


float MotionShiftTimeGet(s16 arg0)
{
    ModelData *temp_r31 = &Hu3DData[arg0];

    return temp_r31->unk_84;
}

static void UpdateMenuControl(omObjData *object);

static void InitMenuControl(omObjData *object)
{
	HuAudSeqPlay(43);
	lbl_2_bss_3C = 0;
	lbl_2_bss_3A = -1;
	lbl_2_bss_36 = 30;
	lbl_2_bss_34 = 0;
	object->func = UpdateMenuControl;
	worstVcount = 0;
	object->work[0] = 0;
	object->work[1] = 0;
	object->work[3] = 0;
}

static void UpdateMenuControl(omObjData *object)
{
	s32 pos;
	
	if(e3ExitEnableF) {
		return;
	}
	E3PadRead();
	pos = object->work[1];
	if(pos < 4) {
		omObjData *config = configModeObj[pos];
		if(config->work[0] == 0) {
			if(config->work[3]) {
				pos++;
			} else {
				pos--;
				if(pos < 0) {
					omOvlHisData *his;
					pos=0;
					his = omOvlHisGet(1);
					omOvlHisChg(1, his->overlay, 1, his->stat);
					e3ExitMode = 0;
					e3NextOvl = 0;
					e3NextEvent = 0;
					e3ExitEnableF = 1;
				}
			}
			
			if(pos < 4) {
				configModeObj[pos]->work[0] = 1;
			}
		}
		object->work[1] = pos;
	}
	if(pos >= 4) {
		s32 playerCnt;
		e3ExitMode = 2;
		if(configE3.mode != 0) {
			e3NextOvl = OVL_E3SETUP;
			e3NextEvent = 1;
		} else {
			if(configE3.board != 0) {
				e3NextOvl = OVL_W02;
			} else {
				e3NextOvl = OVL_W01;
			}
		}
		GWRumbleSet(configE3.rumble);
		playerCnt = playerCntTbl[configE3.playerCnt];
		for(pos=0; pos<4; pos++) {
			s16 character;
			GWPlayerCfg[pos].pad_idx = configE3.port[pos];
			character = configE3.character[pos];
			GWPlayerCfg[pos].character = character;
			if(configE3.mode == 0) {
				HuAudFXPlay(charSfxTbl[character]);
			}
			GWPlayerCfg[pos].group = pos;
			if(pos < playerCnt) {
				GWPlayerCfg[pos].iscom = 0;
			} else {
				GWPlayerCfg[pos].iscom = 1;
			}
		}
		e3ExitEnableF = 1;
	}
}

static void UpdateOvlWatch(omObjData *object)
{
	s32 i;
	if(WipeStatGet()) {
		return;
	}
	if(!MGSeqDoneCheck()) {
		return;
	}
	HuSysVWaitSet(1);
	if(needCharKill) {
		CharKill(-1);
		for(i=0; i<4; i++) {
			CharARAMOpen(GWPlayerCfg[i].character);
		}
	}
	if(e3ExitMode == 1) {
		omOvlGotoEx(e3NextOvl, 1, e3NextEvent, 0);
	} else if(e3ExitMode == 2) {
		omOvlCallEx(e3NextOvl, 1, e3NextEvent, 0);
	} else {
		omOvlReturnEx(e3NextOvl+1, 1);
	}
}

void E3OvlWatchInit(omObjData *object)
{
	if(e3ExitEnableF) {
		HuAudSeqAllFadeOut(2500);
		WipeColorSet(0, 0, 0);
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
		MGSeqKillAll();
		object->func = UpdateOvlWatch;
	}
}

typedef struct e3_player_cnt_work {
	AnimData *frame[3];
	AnimData *arrow;
	AnimData *arrowHilite;
	Vec2f winSize;
	s16 frameGroup;
	s16 arrowGroupL;
	s16 arrowGroupR;
	s16 unk22[6];
	s16 winHeader;
	s16 winPlayer;
	s16 playerCnt;
	s16 playerCntOld;
} E3PlayerCntWork;

static s16 lbl_2_data_31E[] = {
	35, 38, 41, 44
};

static u32 playerCntMessTbl[] = {
	MAKE_MESSID(0x22, 0x02),
	MAKE_MESSID(0x22, 0x03),
	MAKE_MESSID(0x22, 0x04),
	MAKE_MESSID(0x22, 0x01)
};

static void UpdatePlayerCnt(omObjData *object)
{
	E3PlayerCntWork *work = object->data;
	s32 i;
	u16 btnDown;
	u32 mess;
	if(object->work[1] != object->work[0]) {
		if(object->work[0] == 0) {
			object->work[2] = 4;
		} else {
			object->work[2] = 3;
		}
		object->work[1] = object->work[0];
	}
	btnDown = e3PadData[e3PadCtrl].btnDown;
	switch(object->work[2]) {
		case 0:
			break;
		case 1:
			if(btnDown & PAD_BUTTON_A) {
				HuAudFXPlay(1);
				configE3.playerCnt = work->playerCnt;
				object->work[0] = 0;
				object->work[3] = 1;
			} else if(btnDown & PAD_BUTTON_B) {
				HuAudFXPlay(3);
				work->playerCnt = configE3.playerCnt;
				object->work[0] = 0;
				object->work[3] = 0;
			} else {
				if(e3ConfigPlayerCnt) {
					if(btnDown & PAD_BUTTON_LEFT) {
						HuAudFXPlay(0);
						work->playerCnt--;
						if(work->playerCnt < 0) {
							work->playerCnt = e3ConfigPlayerCnt-1;
							if(work->playerCnt < 0) {
								work->playerCnt = 0;
							}
						}
					} else if(btnDown & PAD_BUTTON_RIGHT) {
						HuAudFXPlay(0);
						work->playerCnt++;
						if(work->playerCnt >= e3ConfigPlayerCnt) {
							work->playerCnt = 0;
						}
					}
				} else {
					work->playerCnt = 0;
				}
			}
			break;
			
		case 3:
			HuSprAttrSet(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			if(e3ConfigPlayerCnt > 1) {
				for(i=0; i<2; i++) {
					HuSprAttrReset(work->arrowGroupL, i, HUSPR_ATTR_DISPOFF);
					HuSprAttrReset(work->arrowGroupR, i, HUSPR_ATTR_DISPOFF);
				}
			}
			object->work[2] = 1;
			break;
			
		case 4:
			HuSprAttrReset(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			for(i=0; i<2; i++) {
				HuSprAttrSet(work->arrowGroupL, i, HUSPR_ATTR_DISPOFF);
				HuSprAttrSet(work->arrowGroupR, i, HUSPR_ATTR_DISPOFF);
			}
			object->work[2] = 0;
			break;
	}
	if(work->playerCntOld != work->playerCnt) {
		float size[2];
		mess = playerCntMessTbl[work->playerCnt];
		HuWinMesMaxSizeGet(1, size, mess);
		HuWinCenterPosSet(work->winPlayer, (work->winSize.x-size[0])/-2.0f, (work->winSize.y-size[1])/-2.0f);
		HuWinMesSet(work->winPlayer, mess);
		work->playerCntOld = work->playerCnt;
	}
}

static void InitPlayerCnt(omObjData *object)
{
	E3PlayerCntWork *work;
	s16 index2;
	s32 index;
	s16 group;
	AnimData *anim;
	u32 mess;
	float sizeMax[2]; //FIXME: Change to Vec2f
	float size[2]; //FIXME: Change to Vec2f
	
	omSetStatBit(object, 0x100);
	object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(E3PlayerCntWork), MEMORY_DEFAULT_NUM);
	work = object->data;
	index = 0;
	group = HuSprGrpCreate(3);
	work->frameGroup = group;
	HuSprGrpPosSet(group, 288, 80);
	anim = HuSprAnimRead(HuDataReadNum(2, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 30008, 0);
	HuSprGrpMemberSet(group, index, index2);
	HuSprTPLvlSet(group, index, 0.5f);
	index++;
	anim = HuSprAnimRead(HuDataReadNum(1, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 30000, 0);
	HuSprGrpMemberSet(group, index, index2);
	index++;
	anim = HuSprAnimRead(HuDataReadNum(3, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 1, 0);
	HuSprGrpMemberSet(group, index, index2);
	HuSprTPLvlSet(group, index, 0.4f);
	anim = HuSprAnimRead(HuDataReadNum(12, MEMORY_DEFAULT_NUM));
	work->arrow = anim;
	work->arrowHilite = HuSprAnimRead(HuDataReadNum(13, MEMORY_DEFAULT_NUM));
	group = HuSprGrpCreate(2);
	work->arrowGroupL = group;
	HuSprGrpPosSet(group, 140, 96);
	index2 = HuSprCreate(anim, 4, 0);
	HuSprGrpMemberSet(group, 0, index2);
	index2 = HuSprCreate(work->arrowHilite, 6, 0);
	HuSprGrpMemberSet(group, 1, index2);
	HuSprTPLvlSet(group, 1, 0.5f);
	HuSprPosSet(group, 1, 0, -4);
	group = HuSprGrpCreate(2);
	work->arrowGroupR = group;
	HuSprGrpPosSet(group, 436, 96);
	index2 = HuSprCreate(anim, 4, 1);
	HuSprGrpMemberSet(group, 0, index2);
	index2 = HuSprCreate(work->arrowHilite, 6, 1);
	HuSprGrpMemberSet(group, 1, index2);
	HuSprTPLvlSet(group, 1, 0.5f);
	HuSprPosSet(group, 1, 0, -4);
	index2 = work->arrowGroupL;
	for(index=0; index<2; index++) {
		HuSprAttrSet(group, index, HUSPR_ATTR_DISPOFF);
		HuSprAttrSet(index2, index, HUSPR_ATTR_DISPOFF);
	}
	HuWinMesMaxSizeGet(1, sizeMax, MAKE_MESSID(0x22, 0x00));
	index2 = HuWinCreate(-10000, 26, sizeMax[0], sizeMax[1], 0);
	work->winHeader = index2;
	HuWinMesColSet(index2, 4);
	HuWinBGTPLvlSet(index2, 0);
	HuWinMesSpeedSet(index2, 0);
	HuWinMesSet(index2, MAKE_MESSID(0x22, 0x00));
	work->playerCntOld = work->playerCnt = configE3.playerCnt;
	mess = playerCntMessTbl[work->playerCnt];
	HuWinMesMaxSizeGet(4, sizeMax, MAKE_MESSID(0x22, 0x01), MAKE_MESSID(0x22, 0x02), MAKE_MESSID(0x22, 0x03), MAKE_MESSID(0x22, 0x04));
	index2 = HuWinCreate(-10000, 58, sizeMax[0], sizeMax[1], 0);
	work->winPlayer = index2;
	work->winSize = *(Vec2f *)(sizeMax); //FIXME: Remove Cast
	HuWinBGTPLvlSet(index2, 0);
	HuWinMesSpeedSet(index2, 0);
	HuWinMesMaxSizeGet(1, size, mess);
	HuWinCenterPosSet(index2, (sizeMax[0]-size[0])/-2.0f, (sizeMax[1]-size[1])/-2.0f);
	HuWinMesSet(index2, mess);
	if(object->work[0] == 1) {
		HuSprAttrSet(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
		if(e3ConfigPlayerCnt > 1) {
			group = work->arrowGroupR;
			index2 = work->arrowGroupL;
			for(index=0; index<2; index++) {
				HuSprAttrReset(group, index, HUSPR_ATTR_DISPOFF);
				HuSprAttrReset(index2, index, HUSPR_ATTR_DISPOFF);
			}
		}
		object->work[1] = 1;
		object->work[2] = 1;
	}
	object->func = UpdatePlayerCnt;
	(void)object;
}

typedef struct e3_char_sel_work {
	AnimData *anims[24];
	s16 frameGroup;
	s16 charGroup;
	s16 cursorGroup;
	s16 hiliteGroup;
	s16 unk68[6];
	s16 cursorPos[4];
	s16 cursorStat[4];
	s16 currPlayer;
} E3CharSelWork;

static Vec2f charPosTbl[] = {
	85, 248,
	143, 248,
	201, 248,
	259, 248,
	317, 248,
	375, 248,
	433, 248,
	491, 248
};

static s32 charComSfxTbl[] = {
	294,
	358,
	422,
	486,
	550,
	614,
	678,
	742
};

static void UpdateCharSelCursor(omObjData *object, s32 backF)
{
	s32 i;
	E3CharSelWork *work;
	s16 cursorPos;
	s16 cursorGroup;
	s16 playerSpr;
	s16 playerCnt;
	s16 hiliteGroup;
	work = object->data;
	cursorGroup = work->cursorGroup;
	hiliteGroup = work->hiliteGroup;
	if(!backF) {
		for(i=0; i<7; i++) {
			HuSprAttrSet(cursorGroup, i, HUSPR_ATTR_DISPOFF);
			HuSprAttrSet(hiliteGroup, i, HUSPR_ATTR_DISPOFF);
		}
		return;
	}
	playerCnt = playerCntTbl[configE3.playerCnt];
	for(i=0; i<playerCnt; i++) {
		cursorPos = 0;
		if(work->cursorStat[i]) {
			cursorPos = 1;
		}
		HuSprBankSet(cursorGroup, i, cursorPos);
		cursorPos = work->cursorPos[i];
		HuSprPosSet(cursorGroup, i, charPosTbl[cursorPos].x, charPosTbl[cursorPos].y);
		HuSprAttrReset(cursorGroup, i, HUSPR_ATTR_DISPOFF);
	}
	for(; i<4; i++) {
		cursorPos = 0;
		playerSpr = (4+i)-(s32)playerCnt;
		if(work->cursorStat[i] != 0) {
			if(work->cursorStat[i] == 3) {
				cursorPos = 1;
			}
			HuSprBankSet(cursorGroup, playerSpr, cursorPos);
			cursorPos = work->cursorPos[i];
			HuSprPosSet(cursorGroup, playerSpr, charPosTbl[cursorPos].x, charPosTbl[cursorPos].y);
			HuSprAttrReset(cursorGroup, playerSpr, HUSPR_ATTR_DISPOFF);
		} else {
			HuSprAttrSet(cursorGroup, playerSpr, HUSPR_ATTR_DISPOFF);
		}
	}
}

static s32 UpdateCharSelPlayerCursor(omObjData *object)
{
	E3CharSelWork *temp_r31;
	s32 temp_r30;
	s16 temp_r29;
	s32 temp_r28;
	s16 temp_r27;
	s32 temp_r26;
	s16 temp_r25;
	s16 temp_r24;
	s16 temp_r23;
	s32 temp_r22;
	s16 temp_r21;
	s16 temp_r20;
	s16 temp_r19;
	s16 temp_r18;
	s16 sp8[8];
	temp_r31 = object->data;
	temp_r22 = 0;
	temp_r23 = playerCntTbl[configE3.playerCnt];
	temp_r24 = 0;
	temp_r20 = 0;
	for(temp_r30=0; temp_r30 < temp_r23; temp_r30++) {
		temp_r19 = configE3.port[temp_r30];
		if(e3PadData[temp_r19].enable) {
			if(temp_r31->cursorStat[temp_r30] == 0) {
				temp_r31->cursorStat[temp_r30] = 1;
			}
			temp_r24++;
			continue;
		}
		temp_r25 = e3PadData[temp_r19].btnDown;
		if(temp_r25 & PAD_BUTTON_A) {
			HuAudFXPlay(1);
			temp_r28 = charTbl[temp_r31->cursorPos[temp_r30]];
			HuAudFXPlay(charComSfxTbl[temp_r28]);
			temp_r31->cursorStat[temp_r30] = 1;
		} else if(temp_r25 & PAD_BUTTON_B) {
			HuAudFXPlay(3);
			if(temp_r30 == e3PadCtrl && temp_r31->cursorStat[temp_r30] == 0) {
				temp_r20 = 1;
			}
			temp_r31->cursorStat[temp_r30] = 0;
		}
		if(temp_r31->cursorStat[temp_r30] != 0) {
			temp_r24++;
			continue;
		}
		if(temp_r25 & (PAD_BUTTON_LEFT|PAD_BUTTON_RIGHT)) {
			temp_r27 = 0;
			for(temp_r28=0; temp_r28<8; temp_r28++) {
				if(charTbl[temp_r28] >= 0) {
					if(temp_r28 == temp_r31->cursorPos[temp_r30]) {
						temp_r29 = temp_r27;
						sp8[temp_r27++] = temp_r28;
					} else {
						for(temp_r26=0; temp_r26<temp_r23; temp_r26++) {
							if(temp_r30 == temp_r26) {
								continue;
							}
							if(temp_r31->cursorPos[temp_r26] == temp_r28) {
								break;
							}
						}
						if(temp_r26 >= temp_r23) {
							sp8[temp_r27++] = temp_r28;
						}
					}
				}
			}
			sp8[temp_r27] = -1;
			temp_r21 = temp_r27;
			temp_r18 = temp_r29;
			if(temp_r21 > 1) {
				if(temp_r25 & PAD_BUTTON_LEFT) {
					HuAudFXPlay(26);
					temp_r29--;
					if(temp_r29 < 0) {
						temp_r29 = temp_r21-1;
					}
				} else if(temp_r25 & PAD_BUTTON_RIGHT) {
					HuAudFXPlay(26);
					temp_r29++;
					if(temp_r29 >= temp_r21) {
						temp_r29 = 0;
					}
				}
				if(temp_r18 != temp_r29) {
					temp_r31->cursorPos[temp_r30] = sp8[temp_r29];
				}
			}
		}
	}
	if(temp_r24 >= temp_r23) {
		temp_r22 = 1;
	}
	if(temp_r20) {
		temp_r22 = -1;
	}
	return temp_r22;
}

static s32 UpdateCharSelComCursor(omObjData *object)
{
	E3CharSelWork *temp_r31;
	s16 temp_r30;
	s16 temp_r29;
	s32 temp_r28;
	s32 temp_r27;
	s16 temp_r26;
	s16 temp_r25;
	s32 temp_r24;
	s16 temp_r23;
	s16 temp_r22;
	s32 temp_r21;
	s16 temp_r20;
	s16 temp_r19;
	s16 sp8[8];
	temp_r31 = object->data;
	temp_r21 = 0;
	temp_r20 = playerCntTbl[configE3.playerCnt];
	temp_r19 = 4-temp_r20;
	temp_r30 = temp_r20+temp_r31->currPlayer-1;
	temp_r31->cursorStat[temp_r30] = 1;
	temp_r26 = temp_r31->cursorPos[temp_r30];
	for(temp_r28=0; temp_r28<temp_r30; temp_r28++) {
		if(temp_r31->cursorPos[temp_r28] == temp_r26) {
			break;
		}
	}
	if(temp_r28<temp_r30) {
		temp_r26 = -1;
	}
	temp_r25 = 0;
	for(temp_r27=0; temp_r27<8; temp_r27++) {
		if(charTbl[temp_r27] >= 0) {
			if(temp_r27 == temp_r26) {
				temp_r29 = temp_r25;
				sp8[temp_r25++] = temp_r27;
			} else {
				for(temp_r24=0; temp_r24<temp_r30; temp_r24++) {
					if(temp_r31->cursorPos[temp_r24] == temp_r27) {
						break;
					}
				}
				if(temp_r24 >= temp_r30) {
					sp8[temp_r25++] = temp_r27;
				}
			}
		}
	}
	temp_r22 = temp_r25;
	if(temp_r26 < 0) {
		temp_r29 = 0;
		temp_r31->cursorPos[temp_r30] = sp8[temp_r29];
	}
	temp_r23 = e3PadData[e3PadCtrl].btnDown;
	if(temp_r23 & PAD_BUTTON_A) {
		HuAudFXPlay(1);
		HuAudFXPlay(charComSfxTbl[charTbl[temp_r31->cursorPos[temp_r30]]]);
		temp_r31->cursorStat[temp_r30] = 3;
		if(temp_r31->currPlayer >= temp_r19) {
			temp_r21 = 1;
		} else {
			temp_r31->currPlayer++;
		}
	} else if(temp_r23 & PAD_BUTTON_B) {
		HuAudFXPlay(3);
		temp_r31->cursorStat[temp_r30] = 0;
		temp_r31->currPlayer--;
		if(temp_r31->currPlayer != 0) {
			temp_r30--;
			temp_r31->cursorStat[temp_r30] = 1;
		} else {
			for(temp_r28=0; temp_r28<4; temp_r28++) {
				temp_r31->cursorStat[temp_r28] = 0;
			}
		}
	} else if(temp_r23 & (PAD_BUTTON_LEFT|PAD_BUTTON_RIGHT)) {
		temp_r26 = temp_r29;
		if(temp_r22 > 1) {
			if(temp_r23 & PAD_BUTTON_LEFT) {
				HuAudFXPlay(26);
				temp_r29--;
				if(temp_r29 < 0) {
					temp_r29 = temp_r22-1;
				}
			} else if(temp_r23 & PAD_BUTTON_RIGHT) {
				HuAudFXPlay(26);
				temp_r29++;
				if(temp_r29 >= temp_r22) {
					temp_r29 = 0;
				}
			}
			if(temp_r26 != temp_r29) {
				temp_r31->cursorPos[temp_r28] = sp8[temp_r29];
			}
		}
	}
	return temp_r21;
}

static s32 CheckCharSel(omObjData *object)
{
	E3CharSelWork *work;
	s32 result;
	work = object->data;
	result = 0;
	if(work->currPlayer == 0) {
		result = UpdateCharSelPlayerCursor(object);
		if(result == 1) {
			if(playerCntTbl[configE3.playerCnt] < 4) {
				result = 0;
				work->currPlayer++;
			}
		}
	} else {
		result = UpdateCharSelComCursor(object);
	}
	return result;
}

static void UpdateCharSel(omObjData *object)
{
	s32 i;
	E3CharSelWork *work;
	u16 btnDown;
	work = object->data;
	if(object->work[1] != object->work[0]) {
		if(object->work[0] == 0) {
			object->work[2] = 4;
		} else {
			object->work[2] = 3;
		}
		object->work[1] = object->work[0];
	}
	btnDown = e3PadData[e3PadCtrl].btnDown;
	switch(object->work[2]) {
		case 0:
			break;
			
		case 1:
			i = CheckCharSel(object);
			if(i == 1) {
				for(i=0; i<4; i++) {
					configE3.character[i] = work->cursorPos[i];
				}
				object->work[0] = 0;
				object->work[3] = 1;
			} else {
				if(i < 0) {
					for(i=0; i<4; i++) {
						work->cursorPos[i] = configE3.character[i];
					}
					object->work[0] = 0;
					object->work[3] = 0;
				}
			}
			UpdateCharSelCursor(object, 1);
			break;
			
		case 3:
			HuSprAttrSet(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			object->work[2] = 1;
			if(work->currPlayer != 0) {
				i = work->currPlayer+(i = playerCntTbl[configE3.playerCnt]-1);
				OSReport("selmode %d %d\n", work->currPlayer, i);
				work->cursorStat[i] = 0;
			} else {
				for(i=0; i<4; i++) {
					work->cursorStat[i] = 0;
				}
			}
			UpdateCharSelCursor(object, 1);
			break;
			
		case 4:
			HuSprAttrReset(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			object->work[2] = 0;
			UpdateCharSelCursor(object, object->work[3]);
			break;
	}
}

static s32 charSpriteTbl[] = {
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32
};

static s32 cursorSpriteTbl[] = {
	14,
	15,
	16,
	17,
	18
};

static s32 hiliteSprTbl[] = {
	19,
	20,
	21,
	22,
	23
};

static void InitCharSel(omObjData *object)
{
	E3CharSelWork *work;
	s32 i;
	s16 member;
	s16 group;
	AnimData *anim;
	s16 sprite;
	s16 j;
	s16 x;
	omSetStatBit(object, 0x100);
	object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(E3CharSelWork), MEMORY_DEFAULT_NUM);
	work = object->data;
	i=0;
	member=0;
	group = HuSprGrpCreate(3);
	work->frameGroup = group;
	HuSprGrpPosSet(group, 288, 200);
	anim = HuSprAnimRead(HuDataReadNum(2, MEMORY_DEFAULT_NUM));
	work->anims[member] = anim;
	sprite = HuSprCreate(anim, 30008, 0);
	HuSprGrpMemberSet(group, member, sprite);
	HuSprTPLvlSet(group, member, 0.5f);
	member++;
	anim = HuSprAnimRead(HuDataReadNum(1, MEMORY_DEFAULT_NUM));
	work->anims[member] = anim;
	sprite = HuSprCreate(anim, 30000, 0);
	HuSprGrpMemberSet(group, member, sprite);
	member++;
	anim = HuSprAnimRead(HuDataReadNum(3, MEMORY_DEFAULT_NUM));
	work->anims[member] = anim;
	sprite = HuSprCreate(anim, 1, 0);
	HuSprGrpMemberSet(group, member, sprite);
	HuSprTPLvlSet(group, member, 0.4f);
	member++;
	group = HuSprGrpCreate(16);
	work->charGroup = group;
	HuSprGrpPosSet(group, 288, 200);
	x = -203;
	for(j=0; j<8; j++, member++) {
		anim = HuSprAnimRead(HuDataReadNum(charSpriteTbl[j], MEMORY_DEFAULT_NUM));
		work->anims[member] = anim;
		sprite = HuSprCreate(anim, 28010, 0);
		HuSprGrpMemberSet(group, j, sprite);
		HuSprPosSet(group, j, x, 0);
		x += 58;
	}
	anim = HuSprAnimRead(HuDataReadNum(24, MEMORY_DEFAULT_NUM));
	work->anims[member] = anim;
	member++;
	x = -203;
	for(i=0; i<8; i++) {
		if(charTbl[i] < 0){ 
			sprite = HuSprCreate(anim, 28000, 0);
			HuSprGrpMemberSet(group, j, sprite);
			HuSprPosSet(group, j, x, 0);
			HuSprTPLvlSet(group, j, 0.5f);
			j++;
		}
		x += 58;
	}
	group = HuSprGrpCreate(7);
	work->cursorGroup = group;
	HuSprGrpPosSet(group, 0, 0);
	for(i=0; i<7; i++) {
		if(i < 5) {
			anim = HuSprAnimRead(HuDataReadNum(cursorSpriteTbl[i], MEMORY_DEFAULT_NUM));
			work->anims[member] = anim;
			member++;
		}
		sprite = HuSprCreate(anim, 10010, 0);
		HuSprGrpMemberSet(group, i, sprite);
		HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
	}
	group = HuSprGrpCreate(7);
	work->hiliteGroup = group;
	HuSprGrpPosSet(group, 0, 0);
	for(i=0; i<7; i++) {
		if(i < 5) {
			anim = HuSprAnimRead(HuDataReadNum(hiliteSprTbl[i], MEMORY_DEFAULT_NUM));
			work->anims[member] = anim;
			member++;
		}
		sprite = HuSprCreate(anim, 10000, 0);
		HuSprGrpMemberSet(group, i, sprite);
		HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
	}
	for(i=0; i<4; i++) {
		work->cursorPos[i] = configE3.character[i];
		work->cursorStat[i] = 0;
	}
	work->currPlayer = 0;
	object->work[1] = 0;
	object->work[2] = 0;
	object->work[3] = 0;
	object->func = UpdateCharSel;
}

typedef struct e3_rumble_cfg_work {
	AnimData *frame[3];
	AnimData *arrow;
	AnimData *arrowHilite;
	Vec2f winSize;
	s16 frameGroup;
	s16 arrowGroupL;
	s16 arrowGroupR;
	s16 unk22[6];
	s16 winHeader;
	s16 winValue;
	s16 rumbleVal;
	s16 rumbleValOld;
} E3RumbleCfgWork;

static u32 rumbleMess[] = {
	MAKE_MESSID(0x22, 0x08),
	MAKE_MESSID(0x22, 0x07)
};

static void UpdateRumbleCfg(omObjData *object)
{
	E3RumbleCfgWork *work;
	s32 i;
	u16 btnDown;
	
	work = object->data;
	if(object->work[1] != object->work[0]) {
		if(object->work[0] == 0) {
			object->work[2] = 4;
		} else {
			object->work[2] = 3;
		}
		object->work[1] = object->work[0];
	}
	btnDown = e3PadData[e3PadCtrl].btnDown;
	switch(object->work[2]) {
		
		case 0:
			break;
			
		case 1:
			if(btnDown & PAD_BUTTON_A) {
				HuAudFXPlay(1);
				configE3.rumble = work->rumbleVal;
				object->work[0] = 0;
				object->work[3] = 1;
			} else if(btnDown & PAD_BUTTON_B) {
				HuAudFXPlay(3);
				work->rumbleVal = configE3.rumble;
				object->work[0] = 0;
				object->work[3] = 0;
			} else if(btnDown & PAD_BUTTON_LEFT) {
				HuAudFXPlay(0);
				work->rumbleVal--;
				if(work->rumbleVal < 0) {
					work->rumbleVal = 1;
				}
			} else if(btnDown & PAD_BUTTON_RIGHT) {
				HuAudFXPlay(0);
				work->rumbleVal++;
				if(work->rumbleVal > 1) {
					work->rumbleVal = 0;
				}
			}
			break;
			
		case 3:
			HuSprAttrSet(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			for(i=0; i<2; i++) {
				HuSprAttrReset(work->arrowGroupL, i, HUSPR_ATTR_DISPOFF);
				HuSprAttrReset(work->arrowGroupR, i, HUSPR_ATTR_DISPOFF);
			}
			object->work[2] = 1;
			break;
			
		case 4:
			HuSprAttrReset(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			for(i=0; i<2; i++) {
				HuSprAttrSet(work->arrowGroupL, i, HUSPR_ATTR_DISPOFF);
				HuSprAttrSet(work->arrowGroupR, i, HUSPR_ATTR_DISPOFF);
			}
			object->work[2] = 0;
			break;
	}
	if(work->rumbleValOld != work->rumbleVal) {
		u32 mess;
		float size[2];
		mess = rumbleMess[work->rumbleVal];
		HuWinMesMaxSizeGet(1, size, mess);
		HuWinCenterPosSet(work->winValue, (work->winSize.x-size[0])/-2.0f, (work->winSize.y-size[1])/-2.0f);
		HuWinMesSet(work->winValue, mess);
		work->rumbleValOld = work->rumbleVal;
	}
}

static void InitRumbleCfg(omObjData *object)
{
	E3RumbleCfgWork *work;
	s16 index2;
	s16 group;
	s32 index;
	AnimData *anim;
	u32 mess;
	float sizeMax[2]; //FIXME: Change to Vec2f
	float size[2]; //FIXME: Change to Vec2f
	
	omSetStatBit(object, 0x100);
	object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(E3RumbleCfgWork), MEMORY_DEFAULT_NUM);
	work = object->data;
	index = 0;
	group = HuSprGrpCreate(3);
	work->frameGroup = group;
	HuSprGrpPosSet(group, 288, 303);
	anim = HuSprAnimRead(HuDataReadNum(8, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 30008, 0);
	HuSprGrpMemberSet(group, index, index2);
	HuSprTPLvlSet(group, index, 0.5f);
	index++;
	anim = HuSprAnimRead(HuDataReadNum(7, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 30000, 0);
	HuSprGrpMemberSet(group, index, index2);
	index++;
	anim = HuSprAnimRead(HuDataReadNum(9, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 1, 0);
	HuSprGrpMemberSet(group, index, index2);
	HuSprTPLvlSet(group, index, 0.4f);
	anim = HuSprAnimRead(HuDataReadNum(12, MEMORY_DEFAULT_NUM));
	work->arrow = anim;
	work->arrowHilite = HuSprAnimRead(HuDataReadNum(13, MEMORY_DEFAULT_NUM));
	group = HuSprGrpCreate(2);
	work->arrowGroupL = group;
	HuSprGrpPosSet(group, 240, 319);
	index2 = HuSprCreate(anim, 4, 0);
	HuSprGrpMemberSet(group, 0, index2);
	index2 = HuSprCreate(work->arrowHilite, 6, 0);
	HuSprGrpMemberSet(group, 1, index2);
	HuSprTPLvlSet(group, 1, 0.5f);
	HuSprPosSet(group, 1, 0, -4);
	group = HuSprGrpCreate(2);
	work->arrowGroupR = group;
	HuSprGrpPosSet(group, 336, 319);
	index2 = HuSprCreate(anim, 4, 1);
	HuSprGrpMemberSet(group, 0, index2);
	index2 = HuSprCreate(work->arrowHilite, 6, 1);
	HuSprGrpMemberSet(group, 1, index2);
	HuSprTPLvlSet(group, 1, 0.5f);
	HuSprPosSet(group, 1, 0, -4);
	index2 = work->arrowGroupL;
	for(index=0; index<2; index++) {
		HuSprAttrSet(group, index, HUSPR_ATTR_DISPOFF);
		HuSprAttrSet(index2, index, HUSPR_ATTR_DISPOFF);
	}
	HuWinMesMaxSizeGet(1, sizeMax, MAKE_MESSID(0x22, 0x06));
	index2 = HuWinCreate(-10000, 267, sizeMax[0], sizeMax[1], 0);
	work->winHeader = index2;
	HuWinMesColSet(index2, 4);
	HuWinBGTPLvlSet(index2, 0);
	HuWinMesSpeedSet(index2, 0);
	HuWinMesSet(index2, MAKE_MESSID(0x22, 0x06));
	work->rumbleValOld = work->rumbleVal = configE3.rumble;
	mess = rumbleMess[work->rumbleVal];
	HuWinMesMaxSizeGet(2, sizeMax, MAKE_MESSID(0x22, 0x07), MAKE_MESSID(0x22, 0x08));
	index2 = HuWinCreate(-10000, 299, sizeMax[0], sizeMax[1], 0);
	work->winValue = index2;
	work->winSize = *(Vec2f *)(sizeMax); //FIXME: Remove Cast
	HuWinBGTPLvlSet(index2, 0);
	HuWinMesSpeedSet(index2, 0);
	HuWinMesMaxSizeGet(1, size, mess);
	HuWinCenterPosSet(index2, (sizeMax[0]-size[0])/-2.0f, 0);
	HuWinMesSet(index2, mess);
	object->work[1] = 0;
	object->work[2] = 0;
	object->work[3] = 0;
	object->func = UpdateRumbleCfg;
	(void)object;
}

typedef struct e3_mode_sel_work {
	AnimData *frame[7];
	Vec2f winSizeMode;
	Vec2f winSizeBoard;
	s16 frameGroup;
	s16 arrowGroupL;
	s16 arrowGroupR;
	s16 cursorGroup;
	s16 unk34[6];
	s16 winMode;
	s16 winBoard;
	s16 mode;
	s16 modeOld;
	s16 board;
	s16 boardOld;
} E3ModeSelWork;

static Vec2f modeSelCursorPosTbl[] = {
	144, 418,
	288, 418
};

static Vec2f boardSelCursorPosTbl[] = {
	94, 418,
	284, 418
};

static void UpdateModeSel(omObjData *object)
{
	E3ModeSelWork *work;
	u16 btnDown;
	float winSize[2];
	
	work = object->data;
	if(object->work[1] != object->work[0]) {
		if(object->work[0] == 0) {
			object->work[2] = 4;
		} else {
			object->work[2] = 3;
		}
		object->work[1] = object->work[0];
	}
	btnDown = e3PadData[e3PadCtrl].btnDown;
	switch(object->work[2]) {
		case 0:
			break;
			
		case 1:
			if(btnDown & PAD_BUTTON_A) {
				HuAudFXPlay(1);
				configE3.mode = work->mode;
				if(work->mode != 0) {
					object->work[0] = 0;
					object->work[3] = 1;
				} else {
					object->work[2] = 2;
					work->boardOld = -1;
					HuWinMesColSet(work->winMode, 4);
					HuWinMesMaxSizeGet(1, winSize, MAKE_MESSID(0x22, 0x0F));
					HuWinCenterPosSet(work->winMode, (work->winSizeMode.x-winSize[0])/-2.0f, (work->winSizeMode.y-winSize[1])/-2.0f);
					HuWinMesSet(work->winMode, MAKE_MESSID(0x22, 0x0F));
					HuWinMesMaxSizeGet(1, winSize, MAKE_MESSID(0x22, 0x10));
					HuWinCenterPosSet(work->winBoard, (work->winSizeBoard.x-winSize[0])/-2.0f, (work->winSizeBoard.y-winSize[1])/-2.0f);
					HuWinMesSet(work->winBoard, MAKE_MESSID(0x22, 0x10));
				}
			} else if(btnDown & PAD_BUTTON_B) {
				HuAudFXPlay(3);
				work->mode = configE3.mode;
				object->work[0] = 0;
				object->work[3] = 0;
			} else if(btnDown & PAD_BUTTON_LEFT) {
				HuAudFXPlay(0);
				work->mode--;
				if(work->mode < 0) {
					work->mode = 1;
				}
			} else if(btnDown & PAD_BUTTON_RIGHT) {
				HuAudFXPlay(0);
				work->mode++;
				if(work->mode > 1) {
					work->mode = 0;
				}
			}
			break;
			
		case 2:
			if(btnDown & PAD_BUTTON_A) {
				HuAudFXPlay(1);
				configE3.board = work->board;
				object->work[0] = 0;
				object->work[3] = 1;
			} else if(btnDown & PAD_BUTTON_B) {
				HuAudFXPlay(3);
				work->boardOld = work->board;
				work->modeOld = -1;
				object->work[2] = 1;
				HuWinMesColSet(work->winMode, 4);
				HuWinMesMaxSizeGet(1, winSize, MAKE_MESSID(0x22, 0x09));
				HuWinCenterPosSet(work->winMode, (work->winSizeMode.x-winSize[0])/-2.0f, (work->winSizeMode.y-winSize[1])/-2.0f);
				HuWinMesSet(work->winMode, MAKE_MESSID(0x22, 0x09));
				HuWinMesMaxSizeGet(1, winSize, MAKE_MESSID(0x22, 0x0A));
				HuWinCenterPosSet(work->winBoard, (work->winSizeBoard.x-winSize[0])/-2.0f, (work->winSizeBoard.y-winSize[1])/-2.0f);
				HuWinMesSet(work->winBoard, MAKE_MESSID(0x22, 0x0A));
			} else if(btnDown & PAD_BUTTON_LEFT) {
				HuAudFXPlay(0);
				work->board--;
				if(work->board < 0) {
					work->board = 1;
				}
			} else if(btnDown & PAD_BUTTON_RIGHT) {
				HuAudFXPlay(0);
				work->board++;
				if(work->board > 1) {
					work->board = 0;
				}
			}
			break;
			
		case 3:
			HuSprAttrSet(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			HuSprAttrReset(work->cursorGroup, 0, HUSPR_ATTR_DISPOFF);
			HuSprAttrReset(work->cursorGroup, 1, HUSPR_ATTR_DISPOFF);
			object->work[2] = 1;
			break;
			
		case 4:
			HuSprAttrReset(work->frameGroup, 2, HUSPR_ATTR_DISPOFF);
			HuSprAttrSet(work->cursorGroup, 0, HUSPR_ATTR_DISPOFF);
			HuSprAttrSet(work->cursorGroup, 1, HUSPR_ATTR_DISPOFF);
			object->work[2] = 0;
			break;
	}
	if(object->work[0]) {
		if(work->modeOld != work->mode) {
			HuSprGrpPosSet(work->cursorGroup, modeSelCursorPosTbl[work->mode].x, modeSelCursorPosTbl[work->mode].y);
			work->modeOld = work->mode;
		}
		if(work->boardOld != work->board) {
			HuSprGrpPosSet(work->cursorGroup, boardSelCursorPosTbl[work->board].x, boardSelCursorPosTbl[work->board].y);
			work->boardOld = work->board;
		}
	}
}

static void InitModeSel(omObjData *object)
{
	E3ModeSelWork *work;
	s16 index2;
	s32 index;
	s16 group;	
	AnimData *anim;
	float size[2]; //FIXME: Change to Vec2f
	
	omSetStatBit(object, 0x100);
	object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(E3ModeSelWork), MEMORY_DEFAULT_NUM);
	work = object->data;
	index = 0;
	group = HuSprGrpCreate(3);
	work->frameGroup = group;
	HuSprGrpPosSet(group, 288, 398);
	anim = HuSprAnimRead(HuDataReadNum(5, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 30008, 0);
	HuSprGrpMemberSet(group, index, index2);
	HuSprTPLvlSet(group, index, 0.5f);
	index++;
	anim = HuSprAnimRead(HuDataReadNum(4, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 30000, 0);
	HuSprGrpMemberSet(group, index, index2);
	index++;
	anim = HuSprAnimRead(HuDataReadNum(6, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 1, 0);
	HuSprGrpMemberSet(group, index, index2);
	HuSprTPLvlSet(group, index, 0.4f);
	index++;
	work->modeOld = work->mode = configE3.mode;
	work->board = work->boardOld = 0;
	group = HuSprGrpCreate(2);
	work->cursorGroup = group;
	HuSprGrpPosSet(group, modeSelCursorPosTbl[work->mode].x, modeSelCursorPosTbl[work->mode].y);
	anim = HuSprAnimRead(HuDataReadNum(10, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 10000, 0);
	HuSprGrpMemberSet(group, 0, index2);
	index++;
	anim = HuSprAnimRead(HuDataReadNum(11, MEMORY_DEFAULT_NUM));
	work->frame[index] = anim;
	index2 = HuSprCreate(anim, 10008, 0);
	HuSprGrpMemberSet(group, 1, index2);
	HuSprTPLvlSet(group, 1, 0.5f);
	HuSprPosSet(group, 1, 0, -4);
	index++;
	HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
	HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
	HuWinMesMaxSizeGet(2, &work->winSizeMode.x, MAKE_MESSID(0x22, 0x09), MAKE_MESSID(0x22, 0x0F));
	index2 = HuWinCreate(-10000, 350, work->winSizeMode.x, work->winSizeMode.y, 0);
	work->winMode = index2;
	HuWinMesColSet(index2, 4);
	HuWinBGTPLvlSet(index2, 0);
	HuWinMesSpeedSet(index2, 0);
	HuWinMesMaxSizeGet(1, size, MAKE_MESSID(0x22, 0x09));
	HuWinCenterPosSet(index2, (work->winSizeMode.x-size[0])/-2.0f, (work->winSizeMode.y-size[1])/-2.0f);
	HuWinMesSet(index2, MAKE_MESSID(0x22, 0x09));
	HuWinMesMaxSizeGet(2, &work->winSizeBoard.x, MAKE_MESSID(0x22, 0x0A), MAKE_MESSID(0x22, 0x10));
	index2 = HuWinCreate(-10000, 390, work->winSizeBoard.x, work->winSizeBoard.y, 0);
	work->winBoard = index2;
	HuWinBGTPLvlSet(index2, 0);
	HuWinMesSpeedSet(index2, 0);
	HuWinMesMaxSizeGet(1, size, MAKE_MESSID(0x22, 0x0A));
	HuWinCenterPosSet(index2, (work->winSizeBoard.x-size[0])/-2.0f, (work->winSizeBoard.y-size[1])/-2.0f);
	HuWinMesSet(index2, MAKE_MESSID(0x22, 0x0A));
	object->work[0] = 0;
	object->work[1] = 0;
	object->work[2] = 0;
	object->work[3] = 0;
	object->func = UpdateModeSel;
}

#define E3_BG_SPEED 0.5f
#define E3_BG_TILE_W 128
#define E3_BG_TILE_H 128
#define E3_BG_TILE_COL 6
#define E3_BG_TILE_ROW 5
#define E3_BG_MAX_TILE (E3_BG_TILE_COL*E3_BG_TILE_ROW)

typedef struct e3_bg_tile {
	Vec2f pos;
	s16 sprite;
} E3BGTile;

typedef struct e3_bg_work {
	AnimData *anim;
	s16 group;
	E3BGTile tiles[E3_BG_MAX_TILE];
} E3BGWork;

static void E3BGUpdate(omObjData *object)
{
	E3BGTile *tile;
	s32 i;
	E3BGWork *work;
	s16 group;
	work = object->data;
	tile = &work->tiles[0];
	group = work->group;
	for(i=0; i<E3_BG_MAX_TILE; i++, tile++) {
		tile->pos.x -= E3_BG_SPEED;
		if(tile->pos.x <= -(E3_BG_TILE_W/2)) {
			tile->pos.x += E3_BG_TILE_W*E3_BG_TILE_COL;
		}
		tile->pos.y -= E3_BG_SPEED;
		if(tile->pos.y <= -(E3_BG_TILE_H/2)) {
			tile->pos.y += E3_BG_TILE_H*E3_BG_TILE_ROW;
		}
		HuSprPosSet(group, i, tile->pos.x, tile->pos.y);
	}
}

void E3BGCreate(omObjData *object)
{
	E3BGTile *tile;
	E3BGWork *work;
	s32 tile_idx;
	s16 group;
	s16 col;
	s16 row;
	AnimData *anim;
	s16 sprite;
	float x;
	float y;
	
	omSetStatBit(object, 0x100);
	object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(E3BGWork), MEMORY_DEFAULT_NUM);
	work = object->data;
	group = HuSprGrpCreate(E3_BG_MAX_TILE);
	work->group = group;
	anim = HuSprAnimRead(HuDataReadNum(0, MEMORY_DEFAULT_NUM));
	work->anim =anim;
	tile = &work->tiles[0];
	tile_idx = 0;
	y = E3_BG_TILE_H/2;
	for(row=0; row<E3_BG_TILE_ROW; row++) {
		x = E3_BG_TILE_W/2;
		for(col=0; col<E3_BG_TILE_COL; col++) {
			sprite = HuSprCreate(anim, -1, 0);
			HuSprGrpMemberSet(group, tile_idx, sprite);
			HuSprPosSet(group, tile_idx, x, y);
			tile->sprite = sprite;
			tile->pos.x = x;
			tile->pos.y = y;
			tile++;
			tile_idx++;
			x += E3_BG_TILE_W;
		}
		y += E3_BG_TILE_H;
	}
	object->work[0] = 0;
	object->work[1] = 0;
	object->work[2] = 0;
	object->work[3] = 0;
	object->func = E3BGUpdate;
}

typedef struct camera_view_params {
	Vec rot;
	Vec pos;
	float zoom;
	float fov;
} CameraViewParams;

static CameraViewParams camViewTbl[] = {
	{
		-42, 0, 0,
		0, 50, -57,
		2488,
		30
	},
	{
		-90, 0, 0,
		0, 50, 0,
		2990,
		30
	},
	{
		-13, 0, 0,
		0, 50, -1025,
		2488,
		30
	}
};

static void UpdateCamera(omObjData *object);

static void InitCamera(omObjData *object)
{
	u32 *work;
	object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 3*sizeof(u32), MEMORY_DEFAULT_NUM);
	work = object->data;
	work[0] = 0;
	object->work[0] = 0;
	object->work[1] = 0;
	object->work[2] = 0;
	object->work[3] = 0;
	object->func = UpdateCamera;
}

static void UpdateCamera(omObjData *object)
{
	u32 *work = object->data;
	if(object->work[0]) {
		if((s32)object->work[0] != 1) {
			(void)object;
		} else {
			CameraViewParams *view = &camViewTbl[object->work[1]];
			CRot = view->rot;
			Center = view->pos;
			CZoom = view->zoom;
			if(e3CameraFov != view->fov) {
				e3CameraFov = view->fov;
				Hu3DCameraPerspectiveSet(1, e3CameraFov, 100, 25000, 4.0f/3.0f);
			}
		}
		object->work[0] = 0;
	}
	if(object->work[2]) {
		(void)object;
	}
}

Vec lbl_2_data_478[] = {
	-90, 0, 2990,
	-42, -57, 2488,
	9999, 9999, 9999
};

Vec lbl_2_data_49C[] = {
	-42, -57, 2488,
	-13, -1025, 2350,
	9999, 9999, 9999
};

struct unkstruct_4C0 {
	Vec *unk0;
	float unk4;
};

struct unkstruct_4C0 lbl_2_data_4C0[] = {
	lbl_2_data_478, 60,
	lbl_2_data_49C, 60
};
