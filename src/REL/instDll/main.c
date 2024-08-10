#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfdraw.h"
#include "game/printfunc.h"
#include "game/frand.h"

#include "game/hsfmotion.h"

#include "game/wipe.h"
#include "game/flag.h"
#include "game/minigame_seq.h"
#include "game/data.h"
#include "game/audio.h"
#include "game/window.h"
#include "game/sprite.h"
#include "game/chrman.h"

#include "math.h"
#include "ext_math.h"

#include "rel_sqrt_consts.h"

#include "REL/instDll.h"

static s16 lbl_1_data_0 = 1;

static omObjData *lbl_1_bss_60;
static omObjData *lbl_1_bss_5C;
static Process *lbl_1_bss_58;
static Vec lbl_1_bss_40[2];
static Vec lbl_1_bss_28[2];
static float lbl_1_bss_20[2];
static s32 lbl_1_bss_1C;
static AnimData *lbl_1_bss_18;
static u16 lbl_1_bss_14;
static u16 lbl_1_bss_12;
static u16 lbl_1_bss_10;
static float lbl_1_bss_C;
static u8 lbl_1_bss_8;
static u16 lbl_1_bss_6;
static u16 lbl_1_bss_4;
static s32 lbl_1_bss_0;

static void fn_1_994(void);
static void fn_1_17E4(void);
static void fn_1_220C(void);
static void fn_1_2804(void);
static void fn_1_2FA0(void);
static void fn_1_4174(omObjData *object);
static void fn_1_4528(omObjData *object);

void ObjectSetup(void)
{
	s32 i;
	omOvlHisData *his;
	s32 light;
	OSReport("******* INST ObjectSetup *********\n");
	lbl_1_bss_58 = omInitObjMan(50, 8192);
	omGameSysInit(lbl_1_bss_58);
	lbl_1_bss_8 = GWLanguageGet();
	lbl_1_bss_14 = GWSystem.mg_next;
	lbl_1_bss_10 = 0;
	lbl_1_bss_4 = 0;
	_ClearFlag(0x1000C);
	for(i=0; HuSndGrpTbl[i].ovl != OVL_INVALID; i++) {
		if(HuSndGrpTbl[i].ovl == mgInfoTbl[lbl_1_bss_14].ovl) {
			break;
		}
	}
	if(HuSndGrpTbl[i].ovl != OVL_INVALID) {
		HuAudSndGrpSetSet(HuSndGrpTbl[i].grpset);
	}
	if(mgInfoTbl[lbl_1_bss_14].ovl == OVL_M411) {
		if(GWMGTypeGet() == -1) {
			GWMGTypeSet(frandmod(3)); 
		}
	} else {
		GWMGTypeSet(-1);
	}
	HuDataDirClose(mgInfoTbl[lbl_1_bss_14].data_dir);
	his = omOvlHisGet(0);
	omOvlHisChg(0, OVL_RESULT, his->event, his->stat);
	if(omovlevtno == 0 && mgInfoTbl[lbl_1_bss_14].ovl == OVL_M430) {
		s32 team_cnt[2];
		s32 team_players[2][2];
		team_cnt[0] = team_cnt[1] = 0;
		for(i=0; i<4; i++) {
			team_players[GWPlayerCfg[i].group][team_cnt[GWPlayerCfg[i].group]++] = i;
		}
		if(frandBool()) {
			GWPlayerCfg[team_players[0][0]].group = 0;
			GWPlayerCfg[team_players[0][1]].group = 1;
		} else {
			GWPlayerCfg[team_players[0][0]].group = 1;
			GWPlayerCfg[team_players[0][1]].group = 0;
		}
		if(frandBool()) {
			GWPlayerCfg[team_players[1][0]].group = 2;
			GWPlayerCfg[team_players[1][1]].group = 3;
		} else {
			GWPlayerCfg[team_players[1][0]].group = 3;
			GWPlayerCfg[team_players[1][1]].group = 2;
		}
	}
	if(mgInfoTbl[lbl_1_bss_14].type == 3
		|| mgInfoTbl[lbl_1_bss_14].type == 5
		|| mgInfoTbl[lbl_1_bss_14].type == 6
		|| mgInfoTbl[lbl_1_bss_14].type == 8
		|| !_CheckFlag(FLAG_ID_MAKE(0, 11))) {
			HuDataDirClose(DATADIR_INST);
			omSysPauseEnable(1);
			omOvlCallEx(mgInfoTbl[lbl_1_bss_14].ovl, 1, 0, 0);
			return;
		}
	lbl_1_bss_40[0].x = -67.0f;
	lbl_1_bss_40[0].y = 40.0f;
	lbl_1_bss_40[0].z = 0.0f;
	lbl_1_bss_28[0].x = 260.0f;
	lbl_1_bss_28[0].y = -103.0f;
	lbl_1_bss_28[0].z = -18.0f;
	lbl_1_bss_20[0] = 2885.0f;
	lbl_1_bss_C = 20.0f;
	lbl_1_bss_12 = GWSystem.board;
	if(mgBoardHostEnableF) {
		lbl_1_bss_12 = 1;
	}
	lbl_1_bss_40[1].x = lbl_1_bss_40[1].y = lbl_1_bss_40[1].z = 0.0f;
	lbl_1_bss_28[1].x = lbl_1_bss_28[1].y = lbl_1_bss_28[1].z = 0.0f;
	lbl_1_bss_20[1] = 1000.0f;
	omSysPauseEnable(0);
	Hu3DCameraCreate(3);
	Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 15000.0f, 1.2f);
	Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
	Hu3DCameraPerspectiveSet(2, 30.0f, 20.0f, 15000.0f, 1.2f);
	Hu3DCameraViewportSet(2, 0, 0, 640, 480, 0, 1);
	light = Hu3DGLightCreate(0, 100, 1000, 0, -0.5, -1, 255, 255, 255);
	Hu3DGLightInfinitytSet(light);
	HuPrcChildCreate(fn_1_994, 100, 12288, 0, lbl_1_bss_58);
	HuPrcChildCreate(fn_1_17E4, 100, 12288, 0, lbl_1_bss_58);
	HuPrcChildCreate(fn_1_220C, 100, 12288, 0, lbl_1_bss_58);
	HuPrcChildCreate(fn_1_2804, 100, 12288, 0, lbl_1_bss_58);
	HuPrcChildCreate(fn_1_2FA0, 100, 12288, 0, lbl_1_bss_58);
	lbl_1_bss_5C = omAddObjEx(lbl_1_bss_58, 32730, 0, 0, -1, fn_1_4174);
	omAddObjEx(lbl_1_bss_58, 0, 32, 32, -1, fn_1_4528);
	HuAudSeqPlay(59);
	Hu3DBGColorSet(0, 0, 0);
	HuWinInit(1);
}

static s8 lbl_1_data_26[] = {
	3, 2, 1, 0,
	1, 1, 1, 0,
	1, 1, 0, 0,
	0, 1, 2, 3,
	3, 2, 1, 0,
	0, -1, -1, -1,
	0, -1, -1, -1,
	3, 2, 1, 0
};

static s8 lbl_1_data_46[] = {
	4,
	4,
	4,
	4,
	4,
	1,
	1,
	4
};

static s32 lbl_1_data_50[] = {
	DATA_MAKE_NUM(DATADIR_INST, 0),
	DATA_MAKE_NUM(DATADIR_INST, 1),
	DATA_MAKE_NUM(DATADIR_INST, 2),
	DATA_MAKE_NUM(DATADIR_INST, 3),
	DATA_MAKE_NUM(DATADIR_INST, 4),
	DATA_MAKE_NUM(DATADIR_INST, 0),
	DATA_MAKE_NUM(DATADIR_INST, 5),
	DATA_MAKE_NUM(DATADIR_INST, 0),
};

static s32 lbl_1_data_70[] = {
	DATA_MAKE_NUM(DATADIR_INST, 9),
	DATA_MAKE_NUM(DATADIR_INST, 10),
	DATA_MAKE_NUM(DATADIR_INST, 11),
	DATA_MAKE_NUM(DATADIR_INST, 12),
	DATA_MAKE_NUM(DATADIR_INST, 13),
	DATA_MAKE_NUM(DATADIR_INST, 14),
	DATA_MAKE_NUM(DATADIR_INST, 14),
	DATA_MAKE_NUM(DATADIR_INST, 9),
};

static void fn_1_50B0(ModelData *model, Mtx mtx);
static void fn_1_5B64(ModelData *model, Mtx mtx);

static void fn_1_994(void)
{
	
	Vec pos;
	Vec target;
	Vec up;
	
	Vec spC;
	Process *process;
	
	s16 i;
	s16 model;
	s16 num_coms;
	s16 j;
	s16 btns;
	s32 status;
	s32 done;
	s16 group;
	s32 pic;
	omOvlHisData *his;
	s16 sprite;
		AnimData *anim;
	float pos_z;
	float time;
	float fov_vel;
	float rot_x;
	
	
	process = HuPrcCurrentGet();
	status = -1;
	group = HuSprGrpCreate(1);
	anim = HuSprAnimRead(HuDataReadNum(lbl_1_data_70[mgInfoTbl[lbl_1_bss_14].type], MEMORY_DEFAULT_NUM));
	sprite = HuSprCreate(anim, 0, 0);
	HuSprGrpMemberSet(group, 0, sprite);
	HuSprGrpDrawNoSet(group, 127);
	HuSprPosSet(group, 0, 288, 240);
	if(GWMGTypeGet() == -1) {
		pic = mgInfoTbl[lbl_1_bss_14].inst_pic[0];
	} else {
		pic = mgInfoTbl[lbl_1_bss_14].inst_pic[GWMGTypeGet()];
	}
	lbl_1_bss_18 = HuSprAnimRead(HuDataReadNumHeapShortForce(pic, MEMORY_DEFAULT_NUM, HEAP_DATA));
	Hu3DShadowCreate(20, 500, 8000);
	Hu3DShadowTPLvlSet(0);
	Hu3DShadowSizeSet(192);
	target.x = target.y = target.z  = 0;
	pos.x = pos.z = 100.0f;
	pos.y = 7000.0f;
	up.x = up.y = 0.0f;
	up.z = 1.0f;
	Hu3DShadowPosSet(&pos, &up, &target);
	model = Hu3DModelCreateFile(lbl_1_data_50[mgInfoTbl[lbl_1_bss_14].type]);
	lbl_1_bss_1C = model;
	Hu3DModelPosSet(model, 0, 2000, 0);
	Hu3DModelAttrSet(model, 0x40000002);
	Hu3DModelCameraSet(model, 1);
	Hu3DModelShadowSet(model);
	i = Hu3DHookFuncCreate(fn_1_5B64);
	Hu3DModelPosSet(i, 0, -200, 0);
	Hu3DModelCameraSet(i, 1);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	pos_z = -500.0f;
	for(i=0; i<=50; i++) {
		Hu3DModelPosSet(model, 0.0f, 2500.0*cosd(i*1.8f)-200.0, pos_z);
		Hu3DModelRotSet(model, 0, 0, 45.0f*(1.0f-(i/50.0f)));
		pos_z += 50.0/7.0;
		Hu3DShadowTPLvlSet(0.5*(i/50.0f));
		HuPrcVSleep();
	}
	HuAudFXPlay(1211);
	Hu3DModelAttrReset(model, 0x40000002);
	for(i=1; i<=20; i++) {
		Hu3DModelPosSet(model, 0.0f, (200.0*(sind(i*2.25f)*(1.0/sind(45))))-200.0, pos_z);
		rot_x = (20-i)*cosd(i*13.5f);
		Hu3DModelRotSet(model, rot_x, 0.0f, 0.0f);
		pos_z += 50.0/7.0;
		HuPrcVSleep();
	}
	Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
	Hu3DModelAttrSet(model, 0x40000002);
	HuPrcSleep(10);
	HuAudFXPlay(1212);
	Hu3DModelAttrReset(model, 0x40000002);
	i = Hu3DHookFuncCreate(fn_1_50B0);
	
	Hu3DModelCameraSet(i, 1);
	Hu3DModelPosSet(i, 0, 415, 0);
	lbl_1_data_0 = 0;
	while(Hu3DMotionTimeGet(model) < 80.0f) {
		if(Hu3DMotionTimeGet(model) > 30.0f) {
			lbl_1_data_0 = 2;
		}
		HuPrcVSleep();
	}
	Hu3DModelAttrSet(model, 0x40000002);
	HuDataDirClose(DATADIR_INST);
	status = HuDataDirReadAsync(mgInfoTbl[lbl_1_bss_14].data_dir);
	while(lbl_1_data_0 != 1) {
		HuPrcVSleep();
	}
	done = 0;
	for(i=num_coms=0; i<4; i++) {
		if(GWPlayerCfg[i].iscom) {
			num_coms++;
		}
	}
	i=0;
	while(1) {
		if(!done) {
			for(btns=j=0; j<4; j++) {
				if(!GWPlayerCfg[j].iscom) {
					btns |= HuPadBtnDown[GWPlayerCfg[j].pad_idx];
				}
			}
			if((btns == PAD_BUTTON_START) || omSysExitReq || (num_coms == 4 && i > 60)) {
				HuAudFXPlay(2);
				done = 1;
			}
			if(btns == PAD_TRIGGER_Z) {
				HuAudFXPlay(1);
				done = 1;
				his = omOvlHisGet(0);
				omOvlHisChg(0, OVL_INST, 1, his->stat);
				_SetFlag(0x1000C);
			}
			if(mgInstExitEnableF &&  (btns & PAD_BUTTON_B)) {
				HuAudFXPlay(3);
				if(status != -1) {
					while(!HuDataGetAsyncStat(status)) {
						HuPrcVSleep();
					}
				}
				WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
				HuAudSeqAllFadeOut(500);
				while(WipeStatGet()) {
					HuPrcVSleep();
				}
				HuDataDirClose(mgInfoTbl[lbl_1_bss_14].data_dir);
				if(mgInfoTbl[lbl_1_bss_14].ovl == OVL_M430) {
					for(num_coms=0; num_coms<4; num_coms++) {
						GWPlayerCfg[num_coms].group = GWPlayerCfg[num_coms].group/2;
					}
				}
				omOvlReturnEx(1, 1);
				HuPrcEnd();
				while(1) {
					HuPrcVSleep();
				}
			}
		}
		if(!lbl_1_bss_4 || !done) {
			HuPrcVSleep();
			i++;
			continue;
		} else {
			break;
		}
	}
	if(status != -1) {
		while(!HuDataGetAsyncStat(status)) {
			HuPrcVSleep();
		}
	}
	spC = lbl_1_bss_40[0];
	pos = lbl_1_bss_28[0];
	pos_z = lbl_1_bss_20[0];
	WipeColorSet(255, 255, 255);
	lbl_1_data_0 = 3;
	HuPrcSleep(20);
	lbl_1_data_0 = 4;
	HuPrcSleep(10);
	
	Hu3DModelAttrReset(model, 0x40000002);
	HuPrcSleep(10);
	fov_vel = 0;
	for(i=0; i<=60; i++) {
		time = i/60.0f;
		lbl_1_bss_40[0].x = spC.x+((-65.0f-spC.x)*time);
		lbl_1_bss_40[0].y = spC.y+((8.0f-spC.y)*time);
		lbl_1_bss_40[0].z = spC.z+(-spC.z)*time;
		lbl_1_bss_28[0].x = pos.x+((17.0f-pos.x)*time);
		lbl_1_bss_28[0].y = pos.y+((5.0f-pos.y)*time);
		lbl_1_bss_28[0].z = pos.z+((-188.0f-pos.z)*time);
		lbl_1_bss_20[0] = pos_z+((1173.0f-pos_z)*time);
		if(i == 30) {
			HuAudFXPlay(1210);
			WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
			HuAudSeqAllFadeOut(1000);
		}
		if(i == 40) {
			Hu3DModelAttrSet(model, 0x40000002);
		}
		if(i > 20) {
			lbl_1_bss_C += fov_vel;
			fov_vel += 0.04;
		}
		HuPrcVSleep();
	}
	while(WipeStatGet()) {
		lbl_1_bss_C += fov_vel;
		fov_vel += 0.04;
		HuPrcVSleep();
	}
	lbl_1_data_0 = 6;
	HuPrcVSleep();
	omSysPauseEnable(1);
	if(omSysExitReq) {
		HuDataDirClose(mgInfoTbl[lbl_1_bss_14].data_dir);
		omOvlReturnEx(1, 1);
	} else {
		omOvlCallEx(mgInfoTbl[lbl_1_bss_14].ovl, 1, 0, 0);
	}
	HuPrcEnd();
	while(1) {
		HuPrcVSleep();
	}
}

static char *lbl_1_data_B0[] = {
	"p_pos_a",
	"p_pos_b",
	"p_pos_c",
	"p_pos_d"
};

static u8 lbl_1_data_C0[] = {
	8,
	0,
	12,
	4
};

static void fn_1_17E4(void)
{
	float tplvl;
	s16 i;
	s16 j;
	s16 time;
	s16 player_cnt;
	s16 order;
	s16 type;
	s16 group_type;
	s16 group;
	ModelData *model;
	s16 player_mdl[4];
	s16 char_tbl[4];
	s16 platform_mdl[4];
	s16 player_order[4];
	s16 mot_tbl[4][3];
	Vec player_pos[4];
	
	type = mgInfoTbl[lbl_1_bss_14].type;
	player_cnt = lbl_1_data_46[type];
	for(i=0; i<player_cnt; i++) {
		player_order[i] = -1;
	}
	if(mgInfoTbl[lbl_1_bss_14].ovl != OVL_M430) {
		group_type = type;
	} else {
		group_type = 0;
	}
	for(i=0; i<player_cnt; i++) {
		group = lbl_1_data_26[(group_type*4)+i];
		for(j=0; j<4; j++) {
			if(group == GWPlayerCfg[j].group) {
				for(order=0; order<i; order++) {
					if(j == player_order[order]) {
						break;
					}
				}
				if(order == i) {
					player_order[i] = j;
					break;
				}
			}
		}
	}
	for(i=0; i<player_cnt; i++) {
		if(player_order[i] == -1) {
			for(j=0; j<player_cnt; j++) {
				player_order[j] = j;
			}
			break;
		}
	}
	for(i=0; i<player_cnt; i++) {
		char_tbl[i] = GWPlayerCfg[player_order[i]].character;
		player_mdl[i] = CharModelCreate(char_tbl[i], 2);
		Hu3DModelPosSet(player_mdl[i], 5000.0f, 0.0f, 0.0f);
		Hu3DModelRotSet(player_mdl[i], 0.0f, 180.0f, 0.0f);
		Hu3DModelCameraSet(player_mdl[i], 1);
		mot_tbl[i][0] = CharModelMotionCreate(char_tbl[i], DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
		mot_tbl[i][1] = CharModelMotionCreate(char_tbl[i], DATA_MAKE_NUM(DATADIR_MARIOMOT, 5));
		mot_tbl[i][2] = CharModelMotionCreate(char_tbl[i], DATA_MAKE_NUM(DATADIR_MARIOMOT, 6));
		CharModelVoiceEnableSet(char_tbl[i], mot_tbl[i][1], 0);
		CharModelMotionSet(char_tbl[i], mot_tbl[i][1]);
		CharModelDataClose(-1);
		platform_mdl[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_INST, 7));
		Hu3DModelTPLvlSet(platform_mdl[i], 0.0f);
		Hu3DModelScaleSet(platform_mdl[i], 0.0f, 0.0f, 0.0f);
	}
	while(lbl_1_data_0 != 2) {
		HuPrcVSleep();
	}
	for(i=0; i<player_cnt; i++) {
		Hu3DModelObjPosGet(lbl_1_bss_1C, lbl_1_data_B0[i], &player_pos[i]);
		Hu3DModelPosSet(platform_mdl[i], player_pos[i].x, 10+player_pos[i].y, player_pos[i].z);
	}
	HuPrcSleep(10);
	for(i=0; i<=50; i++) {
		for(j=0; j<player_cnt; j++) {
			time = i-lbl_1_data_C0[j];
			if(time < 0) {
				continue;
			}
			if(time == 15) {
				CharModelMotionSet(char_tbl[j], mot_tbl[j][2]);
			}
			if(time == 30) {
				CharModelMotionShiftSet(char_tbl[j], mot_tbl[j][0], 0, 10, 0x40000001);
			}
			if(time <= 20) {
				Hu3DModelPosSet(player_mdl[j], player_pos[j].x, player_pos[j].y+(1000.0*cos(M_PI*(time*4.5f)/180.0)), player_pos[j].z);
				time -= 10;
				if(time >= 0) {
					tplvl = 0.1*time;
					Hu3DModelTPLvlSet(platform_mdl[j], 0.5*tplvl);
					Hu3DModelScaleSet(platform_mdl[j], tplvl, tplvl, tplvl);
				}
			}
		}
		HuPrcVSleep();
	}
	model = &Hu3DData[player_mdl[0]];
	while(lbl_1_data_0 != 4) {
		HuPrcVSleep();
	}
	for(i=0; i<=45; i++) {
		for(j=0; j<player_cnt; j++) {
			time = i-lbl_1_data_C0[j];
			if(time < 0) {
				continue;
			}
			if(time == 0) {
				Hu3DModelAttrReset(player_mdl[j], 0x40000001);
				CharModelVoiceEnableSet(char_tbl[i], mot_tbl[i][1], 1);
				CharModelMotionSet(char_tbl[j], mot_tbl[j][1]);
			}
			if(time <= 30) {
				Hu3DModelPosSet(player_mdl[j], player_pos[j].x, player_pos[j].y+(300.0*sind(time*9.0f)), player_pos[j].z-(time*20));
				if(time <= 10) {
					tplvl = 1-(0.1*time);
					Hu3DModelTPLvlSet(platform_mdl[j], 0.5*tplvl);
					Hu3DModelScaleSet(platform_mdl[j], tplvl, tplvl, tplvl);
				}
			}
		}
		HuPrcVSleep();
	}
	HuPrcEnd();
	while(1) {
		HuPrcVSleep();
	}
}

static s32 lbl_1_data_C4[] = {
	DATA_MAKE_NUM(DATADIR_INST, 19), 
	DATA_MAKE_NUM(DATADIR_INST, 20),
	DATA_MAKE_NUM(DATADIR_INST, 21),
	DATA_MAKE_NUM(DATADIR_INST, 22), 
	DATA_MAKE_NUM(DATADIR_INST, 23),
	DATA_MAKE_NUM(DATADIR_INST, 24),
	DATA_MAKE_NUM(DATADIR_INST, 25), 
	DATA_MAKE_NUM(DATADIR_INST, 26),
	DATA_MAKE_NUM(DATADIR_INST, 27),
	DATA_MAKE_NUM(DATADIR_INST, 28), 
	DATA_MAKE_NUM(DATADIR_INST, 29),
	DATA_MAKE_NUM(DATADIR_INST, 30),
	DATA_MAKE_NUM(DATADIR_INST, 31), 
	DATA_MAKE_NUM(DATADIR_INST, 32),
	DATA_MAKE_NUM(DATADIR_INST, 33),
	DATA_MAKE_NUM(DATADIR_INST, 34), 
	DATA_MAKE_NUM(DATADIR_INST, 35),
	DATA_MAKE_NUM(DATADIR_INST, 36),
};

static u16 lbl_1_data_10C[] = {
	55,
	57,
	68,
	67,
	64,
	65,
	75,
	76,
	70,
	71,
	62,
	62
};

static void fn_1_220C(void)
{
	float ofs_x;
	s16 i;
	s16 model;
	s16 motion[2];
	ModelData *model_ptr;
	model = Hu3DModelCreateFile(lbl_1_data_C4[lbl_1_bss_12*3]);
	motion[0] = Hu3DJointMotionFile(model, lbl_1_data_C4[(lbl_1_bss_12*3)+1]);
	motion[1] = Hu3DJointMotionFile(model, lbl_1_data_C4[(lbl_1_bss_12*3)+2]);
	Hu3DMotionSet(model, motion[1]);
	if(lbl_1_bss_12 == 3) {
		ofs_x = 50;
	} else {
		ofs_x = 0;
	}
	Hu3DModelPosSet(model, -353.0f+ofs_x, -150, 356);
	Hu3DModelRotSet(model, 0, 90, 0);
	Hu3DModelCameraSet(model, 2);
	while(lbl_1_data_0 != 2) {
		HuPrcVSleep();
	}
	HuPrcSleep(30);
	Hu3DMotionTimeSet(model, 40);
	HuAudFXPlay(lbl_1_data_10C[lbl_1_bss_12*2]);
	for(i=0; i<=20; i++) {
		Hu3DModelPosSet(model, -153.0f-(100.0f-(100.0f*(i/20.0f))), (100.0*sind(i*9.0f)) + -150.0 + ofs_x, 356.0f);
		HuPrcVSleep();
	}
	for(i=0; i<=10; i++) {
		Hu3DModelPosSet(model, -153.0f, (15.0*sind(i*18.0f)) + -150.f + ofs_x, 356.0f);
		Hu3DModelRotSet(model, 0.0f, 90-((i/10.0f)*70), 0);
		HuPrcVSleep();
	}
	Hu3DMotionShiftSet(model, motion[0], 0, 10, 0x40000001);
	model_ptr = &Hu3DData[model];
	while(1) {
		fontcolor = FONT_COLOR_RED;
		if(lbl_1_data_0 == 3) {
			break;
		}
		HuPrcVSleep();
	}
	Hu3DMotionSet(model, motion[1]);
	HuPrcSleep(20);
	HuAudFXPlay(lbl_1_data_10C[(lbl_1_bss_12*2)+1]);
	for(i=0; i<=30; i++) {
		Hu3DModelPosSet(model, (i*5)-153, (50.0*sind(i*9.0f)) + -150.0 + ofs_x, (i*20)+356);
		HuPrcVSleep();
	}
	HuPrcEnd();
	while(1) {
		HuPrcVSleep();
	}
}

static void fn_1_2804(void)
{
	float pos_x;
	s16 i;
	s16 window;
	s16 window_other;
	s16 j;
	s16 insert_idx;
	s16 rtrig;
	s16 groupCnt[4];
	s16 charTbl[4][4];
	
	window = HuWinExCreateStyled(640, 320, 412, 120, -1, 1);
	while(lbl_1_data_0 != 0) {
		HuPrcVSleep();
	}
	HuWinDispOn(window);
	HuWinMesSet(window, mgInfoTbl[lbl_1_bss_14].inst_mess[0]);
	HuWinMesPalSet(window, 7, 0, 0, 192);
	HuWinMesSpeedSet(window, 0);
	window_other = HuWinExCreateStyled(640, 320, 412, 120, -1, 1);
	HuWinDispOn(window_other);
	HuWinMesSpeedSet(window_other, 0);
	HuWinPosSet(window_other, 142.0f, 640.0f);
	lbl_1_bss_6 = 0;
	for(i=0; i<4; i++) {
		groupCnt[i] = 0;
	}
	
	for(i=0; i<4; i++) {
		charTbl[GWPlayerCfg[i].group][groupCnt[GWPlayerCfg[i].group]] = GWPlayerCfg[i].character;
		groupCnt[GWPlayerCfg[i].group]++;
	}
	for(i=insert_idx=0; i<4; i++) {
		for(j=0; j<groupCnt[i]; j++) {
			HuWinInsertMesSet(window, charTbl[i][j], (s16)insert_idx);
			insert_idx++;
		}
	}
	while(lbl_1_data_0 != 2) {
		HuPrcVSleep();
	}
	HuPrcSleep(40);
	for(i=0; i<=20; i++) {
		pos_x = 500.0*cosd(i*4.5f)+142.0;
		HuWinPosSet(window, pos_x, 320);
		HuPrcVSleep();
	}
	lbl_1_data_0 = 1;
	while(lbl_1_data_0 != 3) {
		for(i=rtrig=0; i<4; i++) {
			if(!GWPlayerCfg[i].iscom) {
				rtrig |= HuPadTrigR[GWPlayerCfg[i].pad_idx] & 0xC0;
			}
		}
		if(rtrig) {
			HuAudFXPlay(1213);
			lbl_1_bss_4 = 0;
			HuWinMesSet(window_other, mgInfoTbl[lbl_1_bss_14].inst_mess[lbl_1_bss_6]);
			HuWinMesPalSet(window_other, 7, 0, 0, 192);
			lbl_1_bss_6++;
			if(mgInfoTbl[lbl_1_bss_14].inst_mess[lbl_1_bss_6] == 0) {
				lbl_1_bss_6++;
			}
			if(lbl_1_bss_6 >= 4) {
				lbl_1_bss_6 = 0;
			}
			HuWinMesSet(window, mgInfoTbl[lbl_1_bss_14].inst_mess[lbl_1_bss_6]);
			HuWinMesPalSet(window, 7, 0, 0, 192);
			HuWinPosSet(window_other, 142.0f, 320.0f);
			for(i=0; i<=10; i++) {
				HuWinPosSet(window_other, 30.0*sind(i*9.0f)+142.0, 160.0*(1.0-cosd(i*9.0f))+320.0);
				HuPrcVSleep();
			}
			HuPrcSleep(5);
		}
		lbl_1_bss_4 = 1;
		HuPrcVSleep();
	}
	for(i=0; i<=20; i++) {
		pos_x = 500.0*(1.0-cosd(i*4.5f))+142.0;
		HuWinPosSet(window, pos_x, 320);
		HuPrcVSleep();
	}
	HuWinAllKill();
	HuPrcEnd();
	while(1) {
		HuPrcVSleep();
	}
}

static float lbl_1_data_124[] = {
	420,
	70,
	488,
	186,
	476,
	242,
	400,
	292
};

static void fn_1_2FA0(void)
{
	float temp_f31;
	float temp_f30;
	float temp_f29;
	float temp_f28;
	float temp_f27;
	s16 temp_r31;
	s16 temp_r30;
	char *temp_r29;
	AnimData *temp_r28;
	s16 temp_r27;
	s16 temp_r26;
	s16 temp_r25;
	s16 temp_r24;
	s16 temp_r23;
	s16 temp_r22;
	u16 temp_r21;
	char *temp_r20;
	s16 temp_r17;
	s16 spA;
	s16 sp8;
	
	s16 spC[2];
	s16 sp10[4];
	SeqWork work;
	temp_r21 = 0;
	for(temp_r31=0; temp_r31<16; temp_r31++) {
		work.sprite[temp_r31] = work.spr_grp[temp_r31] = -1;
	}
	temp_r20 = MessData_MesPtrGet(messDataPtr, mgInfoTbl[lbl_1_bss_14].name_mess);
	temp_r29 = temp_r20;
	temp_r31 = 0;
	temp_r26 = 0;
	while(1) {
		if(*temp_r29 == 0 || *temp_r29 == 10) {
			if(*temp_r29 == 0) {
				temp_r31 = 1;
			}
			*temp_r29 = 0;
			fn_1_5EA4(&work, temp_r20, (lbl_1_bss_8 == 0) ? 1 : 0);
			HuSprGrpPosSet(work.spr_grp[temp_r26], 288.0f, 240.0f);
			spC[temp_r26] = work.alt_word_len;
			temp_r26++;
			if(temp_r31) {
				break;
			}
			temp_r20 = temp_r29+1;
		}
		
		temp_r29++;
	}
	if(temp_r26 == 1) {
		temp_r22 = spC[0];
		temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 18));
		temp_f29 = ((576.0f-temp_r22)-24.0f)-16.0f+227.0f;
		temp_f28 = 78;
		temp_f27 = 0.5f;
	} else {
		temp_r22 = (spC[0] > spC[1]) ? spC[0] : spC[1];
		temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 15));
		temp_f29 = ((576.0f-temp_r22)-24.0f)-16.0f+172.0f;
		temp_f28 = 84;
		temp_f27 = 1.0f;
	}
	temp_r25 = HuSprGrpCreate(1);
	temp_r17 = HuSprCreate(temp_r28, 0, 0);
	HuSprGrpMemberSet(temp_r25, 0, temp_r17);
	HuSprPriSet(temp_r25, 0, 100);
	HuSprGrpPosSet(temp_r25, 10000, 70);
	HuSprScaleSet(temp_r25, 0, 1.0f, temp_f27);
	for(temp_r31=0; temp_r31<temp_r26; temp_r31++) {
		HuSprGrpPosSet(work.spr_grp[temp_r31], 1000, 70);
	}
	temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 16));
	temp_r24 = HuSprGrpCreate(1);
	spA = HuSprCreate(temp_r28, 0, 0);
	HuSprGrpMemberSet(temp_r24, 0, spA);
	HuSprGrpPosSet(temp_r24, 1000, 186);
	HuSprPriSet(temp_r24, 0, 1000);
	sp10[0] = HuWinCreate(1000, 186, 456, 42, 0);
	HuWinMesSet(sp10[0], MAKE_MESSID(0x24, lbl_1_bss_10));
	HuWinBGTPLvlSet(sp10[0], 0.0f);
	temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 17));
	temp_r23 = HuSprGrpCreate(1);
	sp8 = HuSprCreate(temp_r28, 0, 0);
	HuSprGrpMemberSet(temp_r23, 0, sp8);
	HuSprGrpPosSet(temp_r23, 1000, 242);
	HuSprPriSet(temp_r23, 0, 1000);
	sp10[1] = HuWinCreate(1000, 242, 456, 42, 0);
	HuWinMesSet(sp10[1], lbl_1_bss_10+MAKE_MESSID(0x24, 0x01));
	HuWinBGTPLvlSet(sp10[1], 0.0f);
	temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 18));
	sp10[2] = HuWinCreate(1000, 292, 456, 42, 0);
	HuWinMesSet(sp10[2], lbl_1_bss_10+MAKE_MESSID(0x24, 0x02));
	HuWinBGTPLvlSet(sp10[2], 0.0f);
	HuWinMesSpeedSet(sp10[2], 0);
	temp_r31 = HuWinAnimSet(sp10[2], temp_r28, 0, 201, 18);
	HuWinSprPriSet(sp10[2], temp_r31, 1000);
	temp_r27 = HuWinCreate(1000, 292, 456, 42, 0);
	HuWinBGTPLvlSet(temp_r27, 0.0f);
	HuWinMesSpeedSet(temp_r27, 0);
	HuWinMesSet(temp_r27, lbl_1_bss_10+MAKE_MESSID(0x24, 0x02));
	temp_r31 = HuWinAnimSet(temp_r27, temp_r28, 0, 201, 18);
	HuWinPriSet(temp_r27, 10);
	HuWinSprPriSet(temp_r27, temp_r31, 11);
	while(lbl_1_data_0 != 0) {
		HuPrcVSleep();
	}
	for(temp_r31=0; temp_r31<36; temp_r31++) {
		temp_f30 = temp_r31;
		if(temp_f30 <= 20.0f) {
			temp_f31 = 300.0*cosd(4.5f*temp_f30)+temp_f29;
			HuSprGrpPosSet(temp_r25, temp_f31, temp_f28);
			temp_f31 = 300.0*cosd(4.5f*temp_f30)+(576.0f-(temp_r22/2)-24.0f);
			for(temp_r30=0; temp_r30<temp_r26; temp_r30++) {
				HuSprGrpPosSet(work.spr_grp[temp_r30], temp_f31, (temp_r30*28)+70);
			}
		}
		temp_f30 = temp_r31-3;
		if(temp_f30 > 0.0f) {
			if(temp_f30 <= 20.0f) {
				temp_f31 = 300.0*cosd(4.5f*temp_f30)+lbl_1_data_124[2];
				HuSprGrpPosSet(temp_r24, temp_f31, 186.0f);
				temp_f31 = 300.0*cosd(4.5f*temp_f30)+(lbl_1_data_124[2]-88.0f);
				HuWinPosSet(sp10[0], 16.0f+temp_f31, 168.0f);
			}
		}
		temp_f30 = temp_r31-6;
		if(temp_f30 > 0.0f) {
			if(temp_f30 <= 20.0f) {
				temp_f31 = 300.0*cosd(4.5f*temp_f30)+lbl_1_data_124[4];
				HuSprGrpPosSet(temp_r23, temp_f31, 242.0f);
				temp_f31 = 300.0*cosd(4.5f*temp_f30)+(lbl_1_data_124[4]-100.0f);
				HuWinPosSet(sp10[1], 16.0f+temp_f31, 224.0f);
			}
		}
		temp_f30 = temp_r31-9;
		if(temp_f30 > 0.0f) {
			if(temp_f30 <= 20.0f) {
				temp_f31 = 300.0*cosd(4.5f*temp_f30)+(lbl_1_data_124[6]-217.0f);
				HuWinPosSet(sp10[2], 16.0f+temp_f31, 274.0f);
			}
		}
		HuPrcVSleep();
	}
	while(lbl_1_data_0 != 3) {
		if(temp_r21 != lbl_1_bss_6) {
			temp_f31 = 16.0f+(lbl_1_data_124[6]-217.0f);
			HuWinMesSet(temp_r27, MAKE_MESSID(0x24, 0x02)+lbl_1_bss_10+temp_r21);
			temp_r21 = lbl_1_bss_6;
			if(lbl_1_bss_6 == 1) {
				if(mgInfoTbl[lbl_1_bss_14].inst_mess[2]) {
					HuWinMesSet(sp10[2], MAKE_MESSID(0x24, 0x02)+lbl_1_bss_10+lbl_1_bss_6);
				} else {
					HuWinMesSet(sp10[2], MAKE_MESSID(0x24, 0x06)+lbl_1_bss_10);
				}
			} else {
				HuWinMesSet(sp10[2], MAKE_MESSID(0x24, 0x02)+lbl_1_bss_10+lbl_1_bss_6);
			}
			for(temp_r31=0; temp_r31<=10; temp_r31++) {
				HuWinPosSet(temp_r27, 30.0*sind(temp_r31*9.0f)+temp_f31, 200.0*(1.0-cosd(temp_r31*9.0f))+274.0);
				HuPrcVSleep();
			}
		}
		HuPrcVSleep();
	}
	for(temp_r31=0; temp_r31<20; temp_r31++) {
		temp_f30 = 1.0-cosd(temp_r31*4.5f);
		temp_f31 = temp_f29+(500.0f*temp_f30);
		HuSprGrpPosSet(temp_r25, temp_f31, temp_f28);
		temp_f31 = ((576.0f-(work.alt_word_len/2))-24.0f)+(500.0f*temp_f30);
		for(temp_r30=0; temp_r30<temp_r26; temp_r30++) {
			HuSprGrpPosSet(work.spr_grp[temp_r30], temp_f31, (temp_r30*28)+70);
		}
		temp_f31 = lbl_1_data_124[2]+(300.0f*temp_f30);
		HuSprGrpPosSet(temp_r24, temp_f31, 186.0f);
		temp_f31 = (lbl_1_data_124[2]-88.0f)+(300.0f*temp_f30);
		HuWinPosSet(sp10[0], 16.0f+temp_f31, 168);
		temp_f31 = lbl_1_data_124[4]+(300.0f*temp_f30);
		HuSprGrpPosSet(temp_r23, temp_f31, 242.0f);
		temp_f31 = (lbl_1_data_124[4]-100.0f)+(300.0f*temp_f30);
		HuWinPosSet(sp10[1], 16.0f+temp_f31, 224);
		temp_f31 = (lbl_1_data_124[6]-184.0f)+(400.0f*temp_f30);
		HuWinPosSet(sp10[2], 16.0f+temp_f31, 274);
		HuPrcVSleep();
	}
	MGSeqSprKill(&work);
	HuPrcEnd();
	while(1) {
		HuPrcVSleep();
	}
}

static u16 lbl_1_data_144[2] = {
	1,
	2
};

static void fn_1_4174(omObjData *object)
{
	s16 i;
	for(i=0; i<2; i++) {
		Vec pos, target, up;
		float x, y, z;
		
		x = lbl_1_bss_40[i].x;
		y = lbl_1_bss_40[i].y;
		z = lbl_1_bss_40[i].z;
		
		pos.x = (((sind(y)*cosd(x))*lbl_1_bss_20[i])+lbl_1_bss_28[i].x);
		pos.y = (-sind(x)*lbl_1_bss_20[i])+lbl_1_bss_28[i].y;
		pos.z = ((cosd(y)*cosd(x))*lbl_1_bss_20[i])+lbl_1_bss_28[i].z;
		target.x = lbl_1_bss_28[i].x;
		target.y = lbl_1_bss_28[i].y;
		target.z = lbl_1_bss_28[i].z;
		up.x = sind(y)*sind(x);
		up.y = cosd(x);
		up.z = cosd(y)*sind(x);
		Hu3DCameraPosSet(lbl_1_data_144[i], pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
	}
}


static void fn_1_4528(omObjData *object)
{
	Vec pos;
    Vec offset;
    Vec dir;
    Vec y_offset;
    
    f32 z_rot;
    s8 stick_pos;

    if (lbl_1_bss_0 != 0) {
        lbl_1_bss_40[0].y += 0.1f * HuPadStkX[0];
        lbl_1_bss_40[0].x += 0.1f * HuPadStkY[0];
        lbl_1_bss_20[0] += HuPadTrigL[0] / 2;
        lbl_1_bss_20[0] -= HuPadTrigR[0] / 2;
        if (lbl_1_bss_20[0] < 100.0f) {
            lbl_1_bss_20[0] = 100.0f;
        }
		pos.x = lbl_1_bss_28[0].x + (lbl_1_bss_20[0] * (sind(lbl_1_bss_40[0].y) * cosd(lbl_1_bss_40[0].x)));
        pos.y = (lbl_1_bss_28[0].y + (lbl_1_bss_20[0] * -sind(lbl_1_bss_40[0].x)));
        pos.z = (lbl_1_bss_28[0].z + (lbl_1_bss_20[0] * (cosd(lbl_1_bss_40[0].y) * cosd(lbl_1_bss_40[0].x))));
        offset.x = lbl_1_bss_28[0].x - pos.x;
        offset.y = lbl_1_bss_28[0].y - pos.y;
        offset.z = lbl_1_bss_28[0].z - pos.z;
        dir.x = (sind(lbl_1_bss_40[0].y) * sind(lbl_1_bss_40[0].x));
        dir.y = cosd(lbl_1_bss_40[0].x);
        dir.z = (cosd(lbl_1_bss_40[0].y) * sind(lbl_1_bss_40[0].x));
        z_rot = lbl_1_bss_40[0].z;
        y_offset.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * cosd(z_rot))
              + dir.y * (offset.x * offset.y * (1.0f - cosd(z_rot)) - offset.z * sind(z_rot))
              + dir.z * (offset.x * offset.z * (1.0f - cosd(z_rot)) + offset.y * sind(z_rot));

        y_offset.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * cosd(z_rot))
              + dir.x * (offset.x * offset.y * (1.0f - cosd(z_rot)) + offset.z * sind(z_rot))
              + dir.z * (offset.y * offset.z * (1.0f - cosd(z_rot)) - offset.x * sind(z_rot));
        
        y_offset.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * cosd(z_rot))
                      + (dir.x * (offset.x * offset.z * (1.0 - cosd(z_rot)) - offset.y * sind(z_rot))
                      + dir.y * (offset.y * offset.z * (1.0 - cosd(z_rot)) + offset.x * sind(z_rot)));

        VECCrossProduct(&dir, &offset, &offset);
        VECNormalize(&offset, &offset);
        stick_pos = (HuPadSubStkX[0] & 0xF8);
        if (stick_pos != 0) {
            lbl_1_bss_28[0].x += 0.05f * (offset.x * stick_pos);
            lbl_1_bss_28[0].y += 0.05f * (offset.y * stick_pos);
            lbl_1_bss_28[0].z += 0.05f * (offset.z * stick_pos);
        }
        VECNormalize(&y_offset, &offset);
        stick_pos = -(HuPadSubStkY[0] & 0xF8);
        if (stick_pos != 0) {
            lbl_1_bss_28[0].x += 0.05f * (offset.x * stick_pos);
            lbl_1_bss_28[0].y += 0.05f * (offset.y * stick_pos);
            lbl_1_bss_28[0].z += 0.05f * (offset.z * stick_pos);
        }
    }
}

static float lbl_1_data_148 = 842;
static float lbl_1_data_14C = 34;

static void fn_1_50B0(ModelData *model, Mtx mtx)
{
	Mtx final;
	Mtx inv_camera;
	Mtx lookatlight;
	Mtx light;
	Mtx lookat;
	Vec pos;
	Vec up;
	Vec target;

	s32 x;
	s32 y;
	u8 r;
	u8 g;
	u8 b;
	s16 row;
	
	s32 sp8 = 0;
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_RGB8, 0);
	GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	target.x = target.z = 0.0f;
	target.x = lbl_1_data_14C*sind(lbl_1_bss_40[0].y);
	target.z = lbl_1_data_14C*cosd(lbl_1_bss_40[0].y);
	target.y = 415.0f;
	pos.x = (sind(lbl_1_bss_40[0].y)*cosd(lbl_1_bss_40[0].x)*lbl_1_bss_20[0])+lbl_1_bss_28[0].x;
	pos.y = (-sind(lbl_1_bss_40[0].x)*lbl_1_bss_20[0])+lbl_1_bss_28[0].y;
	pos.z = (cos(M_PI*lbl_1_bss_40[0].y/180.0)*cosd(lbl_1_bss_40[0].x)*lbl_1_bss_20[0])+lbl_1_bss_28[0].z;
	up.x = -sind(lbl_1_bss_40[0].y);
	up.z = -cosd(lbl_1_bss_40[0].y);
	up.y = 0;
	MTXLookAt(lookat, &pos, &up, &target);
	MTXLightPerspective(light, lbl_1_bss_C, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
	HuSprTexLoad(lbl_1_bss_18, 0, 0, GX_CLAMP, GX_CLAMP, GX_NEAR);
	MTXInverse(Hu3DCameraMtx, inv_camera);
	MTXConcat(inv_camera, mtx, final);
	MTXConcat(light, lookat, lookatlight);
	MTXConcat(lookatlight, final, final);
	GXLoadTexMtxImm(final, GX_TEXMTX0, GX_MTX3x4);
	GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0);
	GXSetTevOrder(GX_TEVSTAGE0,  GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
	GXSetNumTexGens(1);
	GXSetNumTevStages(1);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	GXLoadPosMtxImm(mtx, GX_PNMTX0);
	MTXInvXpose(mtx, final);
	GXLoadNrmMtxImm(final, GX_PNMTX0);
	GXBegin(GX_TRIANGLES, GX_VTXFMT0, 2400);
	row = 0;
	for(y=-310; y<310; y += 31) {
		for(x=-310; x<310; x += 31) {
			if(row++ & 0x1) {
				r = g = 0;
				b = 255;
			} else {
				r = 255;
				g = b = 0;
			}
			GXPosition3f32(x, 0.0f, y);
			GXPosition3f32(0.0f, 1.0f, 0.0f);
			GXColor3u8(r, g, b);
			GXPosition3f32(x+31, 0.0f, y);
			GXPosition3f32(0.0f, 1.0f, 0.0f);
			GXColor3u8(r, g, b);
			GXPosition3f32(x+31, 0.0f, y+31);
			GXPosition3f32(0.0f, 1.0f, 0.0f);
			GXColor3u8(r, g, b);
			GXPosition3f32(x, 0.0f, y);
			GXPosition3f32(0.0f, 1.0f, 0.0f);
			GXColor3u8(r, g, b);
			GXPosition3f32(x+31, 0.0f, y+31);
			GXPosition3f32(0.0f, 1.0f, 0.0f);
			GXColor3u8(r, g, b);
			GXPosition3f32(x, 0.0f, y+31);
			GXPosition3f32(0.0f, 1.0f, 0.0f);
			GXColor3u8(r, g, b);
		}
		row++;
	}
	GXEnd();
}

static void fn_1_5B64(ModelData *model, Mtx mtx)
{
	s32 sp8 = 0;
	GXTexObj tex;
	Mtx final;
	Mtx inv_camera;
	Mtx shadow;
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXInitTexObj(&tex, Hu3DShadowData.unk_04, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
	GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex, 0);
	MTXInverse(Hu3DCameraMtx, inv_camera);
	MTXConcat(inv_camera, mtx, final);
	MTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, shadow);
	MTXConcat(shadow, final, final);
	GXLoadTexMtxImm(final, GX_TEXMTX9, GX_MTX3x4);
	GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX9);
	GXSetTevOrder(GX_TEVSTAGE0,  GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
	GXSetNumTexGens(1);
	GXSetNumTevStages(1);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	GXLoadPosMtxImm(mtx, GX_PNMTX0);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(-2000.0f, 0, -2000.0f);
	GXPosition3f32(2000.0f, 0, -2000.0f);
	GXPosition3f32(2000.0f, 0, 2000.0f);
	GXPosition3f32(-2000.0f, 0, 2000.0f);
	GXEnd();
}
