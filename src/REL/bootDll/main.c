#include "game/gamework_data.h"
#include "game/process.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/sprite.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/memory.h"
#include "game/hsfman.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/window.h"
#include "game/thpmain.h"
#include "game/msm.h"
#include "math.h"
#include "ext_math.h"

#include "rel_sqrt_consts.h"

#include "data_num/title.h"

#define HU_PAD_BTN_ALL (HuPadBtn[0] | HuPadBtn[1] | HuPadBtn[2] | HuPadBtn[3])
#define HU_PAD_BTNDOWN_ALL (HuPadBtnDown[0] | HuPadBtnDown[1] | HuPadBtnDown[2] | HuPadBtnDown[3])
#define HU_PAD_DSTK_ALL (HuPadDStkRep[0] | HuPadDStkRep[1] | HuPadDStkRep[2] | HuPadDStkRep[3])

extern int SystemInitF;

static Process *objman[2];
Vec lbl_1_bss_3C[2];
Vec lbl_1_bss_24[2];
float lbl_1_bss_1C[2];

Vec lbl_1_bss_10;

static s16 demoWin;

static s16 titleModel[3];
static s16 titleGroup;

s16 lbl_1_bss_4;
s32 lbl_1_bss_0;

static void BootProc(void);
static void UpdateDemoMess(void);
static void ProgressiveProc(void);
static void TitleInit(void);
static BOOL TitleProc(void);

void *logoReadNintendo(void);

void ObjectSetup(void)
{
	omOvlHisData *history;
	OSReport("******* Boot ObjectSetup *********\n");
	objman[0] = omInitObjMan(50, 8192);
	lbl_1_bss_3C[0].x = -67;
	lbl_1_bss_3C[0].y = 40;
	lbl_1_bss_3C[0].z = 0;
	lbl_1_bss_24[0].x = 260;
	lbl_1_bss_24[0].y = -103;
	lbl_1_bss_24[0].z = -18;
	lbl_1_bss_1C[0] = 2885;
	Hu3DCameraCreate(1);
	Hu3DCameraPerspectiveSet(1, 30, 20, 15000, 1.2);
	Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
	HuPrcCreate(BootProc, 100, 12288, 0);
	Hu3DBGColorSet(0, 0, 0);
	history = omOvlHisGet(0);
	omOvlHisChg(0, history->overlay, 1, history->stat);
}

static void BootProc(void)
{
	AnimData *data;
	s16 group;
	s16 sprite_nintendo;
	s16 sprite_hudson;
	s16 i;
	OSTick tick_prev;
	Process *curr = HuPrcCurrentGet();
	if(omovlevtno == 0) {
		ProgressiveProc();
	}
	group = HuSprGrpCreate(2);
	data = HuSprAnimRead(logoReadNintendo());
	sprite_nintendo = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 0, sprite_nintendo);
	HuSprPosSet(group, 0, 288, 240);
	HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
	if(omovlevtno != 0) {
		HuAudSndGrpSetSet(0);
		data = HuSprAnimReadFile(TITLE_HUDSON_ANM);
		sprite_hudson = HuSprCreate(data, 0, 0);
		HuSprGrpMemberSet(group, 1, sprite_hudson);
		HuSprPosSet(group, 1, 288, 240);
		HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
		HuWinInit(1);
		TitleInit();
		SystemInitF = 1;
	} else {
		s16 group_thp;
		BOOL skip_wait;
		float win_size[2];
		s16 sprite_thp;
		for(i=0; i<4; i++) {
			GWPlayerCfg[i].pad_idx = i;
		}
		repeat:
		HuSprAttrReset(group, 0, HUSPR_ATTR_DISPOFF);
		WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		WipeColorSet(255, 255, 255);
		if(!SystemInitF) {
			tick_prev = OSGetTick();
			CharManInit();
			HuWindowInit();
			MGSeqInit();
			HuWinInit(1);
			TitleInit();
			data = HuSprAnimReadFile(TITLE_HUDSON_ANM);
			sprite_hudson = HuSprCreate(data, 0, 0);
			HuSprGrpMemberSet(group, 1, sprite_hudson);
			HuSprPosSet(group, 1, 288, 240);
			HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
			while(OSTicksToMilliseconds(OSGetTick()-tick_prev) < 3000) {
				HuPrcVSleep();
			}
		} else {
			for(i=0; i<180; i++) {
				if(HuPadBtnDown[0] & (PAD_BUTTON_START|PAD_BUTTON_A)) {
					break;
				}
				HuPrcVSleep();
			}
		}
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
		HuSprAttrReset(group, 1, HUSPR_ATTR_DISPOFF);
		HuPrcSleep(60);
		WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		if(!SystemInitF) {
			void *group_samp;
			tick_prev = OSGetTick();
			group_samp = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(0));
			msmSysLoadGroup(0, group_samp, 0);
			HuMemDirectFree(group_samp);
			while(OSTicksToMilliseconds(OSGetTick()-tick_prev) < 3000) {
				HuPrcVSleep();
			}
		} else {
			for(i=0; i<180; i++) {
				if(HuPadBtnDown[0] & (PAD_BUTTON_START|PAD_BUTTON_A)) {
					break;
				}
				HuPrcVSleep();
			}
		}
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		tick_prev = OSGetTick();
		if(!SystemInitF) {
			HuAudSndGrpSetSet(0);
			SystemInitF = 1;
		}
		while(OSTicksToMilliseconds(OSGetTick()-tick_prev) < 1000) {
			HuPrcVSleep();
		}
		HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
		HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
		group_thp = HuSprGrpCreate(1);
		sprite_thp = HuTHPSprCreateVol("movie/opmov_a00.thp", 0, 100, 122);
		HuSprGrpMemberSet(group_thp, 0, sprite_thp);
		HuSprPosSet(group_thp, 0, 288, 240);
		HuWinMesMaxSizeBetGet(win_size, MAKE_MESSID(54, 0), MAKE_MESSID(54, 4));
		demoWin = HuWinCreate(-10000, 448-win_size[1], win_size[0], win_size[1], 0);
		HuWinMesSpeedSet(demoWin, 0);
		HuWinBGTPLvlSet(demoWin, 0);
		HuWinPriSet(demoWin, 10);
		HuWinAttrSet(demoWin, 0x800);
		HuPrcSleep(5);
		WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		skip_wait = FALSE;
		while(!HuTHPEndCheck()) {
			UpdateDemoMess();
			if(HuPadBtnDown[0] & (PAD_BUTTON_START|PAD_BUTTON_A)) {
				skip_wait = TRUE;
				break;
			}
			HuPrcVSleep();
		}
		WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
		while(WipeStatGet()) {
			HuPrcVSleep();
		}
		HuWinKill(demoWin);
		HuTHPClose();
		HuPrcVSleep();
		HuSprGrpKill(group_thp);
		if(!skip_wait) {
			HuPrcSleep(60);
		}
		skip_wait = FALSE;
	}
	if(!TitleProc()) {
		HuPrcSleep(60);
		goto repeat;
	}
	WipeColorSet(255, 255, 255);
	HuAudSStreamAllFadeOut(500);
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuPrcVSleep();
	if(omSysExitReq) {
		omOvlReturnEx(1, 1);
	} else {
		omOvlCallEx(OVL_MODESEL, 1, 0, 0);
	}
	for(i=0; i<4; i++) {
		GWPlayerCfg[i].character = -1;
	}
	HuPrcEnd();
	do {
		HuPrcVSleep();
	} while(1);
}

static s16 demoTimingTbl[] = {
	1686, 1785,
	1850, 1936,
	1993, 2097,
	2135, 2245,
	2258, 2320,
	-1, -1,
};

static void UpdateDemoMess(void)
{
	int frame = HuTHPFrameGet();
	int i;
	for(i=0; demoTimingTbl[i*2] != -1; i++) {
		if(frame == demoTimingTbl[i*2]) {
			HuWinMesSet(demoWin, MAKE_MESSID(54, i));
		}
		if(frame == demoTimingTbl[(i*2)+1]) {
			HuWinHomeClear(demoWin);
		}
	}
}

static u16 progressivePosTbl[] = {
	236, 313,
	353, 313
};

static void ProgressiveProc(void)
{
	s16 i;
	s16 option;
	s16 group;
	s16 sprite;
	AnimData *data;
	option = 0;
	if(OSGetResetCode() != OS_RESET_RESTART) {
		return;
	}
	if(VIGetDTVStatus() != VI_NON_INTERLACE) {
		OSSetProgressiveMode(OS_PROGRESSIVE_MODE_OFF);
		return;
	}
	if(OSGetProgressiveMode() == OS_PROGRESSIVE_MODE_OFF && !(HU_PAD_BTN_ALL & PAD_BUTTON_B)) {
		return;
	}
	if(OSGetProgressiveMode() == OS_PROGRESSIVE_MODE_ON) {
		VIConfigure(&GXNtsc480IntDf);
		VIFlush();
	}
	group = HuSprGrpCreate(3);
	data = HuSprAnimReadFile(TITLE_PROGRESSIVE_CHOOSE_ANM);
	sprite = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 0, sprite);
	HuSprPosSet(group, 0, 288, 240);
	data = HuSprAnimReadFile(TITLE_PROGRESSIVE_CURSOR_ON_ANM);
	sprite = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 1, sprite);
	HuSprPosSet(group, 1, progressivePosTbl[option*2], progressivePosTbl[(option*2)+1]);
	data = HuSprAnimReadFile(TITLE_PROGRESSIVE_CURSOR_OFF_ANM);
	sprite = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 2, sprite);
	HuSprPosSet(group, 2, progressivePosTbl[option*2], progressivePosTbl[(option*2)+1]);
	HuSprAttrSet(group, 2, HUSPR_ATTR_DISPOFF);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	for(i=0; i<600; i++) {
		if(HU_PAD_DSTK_ALL & (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT)) {
			option ^= 1;
			HuSprPosSet(group, 1, progressivePosTbl[option*2], progressivePosTbl[(option*2)+1]);
			i=0;
		}
		if(HU_PAD_BTNDOWN_ALL & PAD_BUTTON_A) {
			HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
			HuSprPosSet(group, 2, progressivePosTbl[option*2], progressivePosTbl[(option*2)+1]);
			HuSprAttrReset(group, 2, HUSPR_ATTR_DISPOFF);
			break;
		}
		HuPrcVSleep();
	}
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	if(!option) {
		OSSetProgressiveMode(OS_PROGRESSIVE_MODE_ON);
		VIConfigure(&GXNtsc480Prog);
		VIFlush();
		HuPrcSleep(100);
	} else {
		OSSetProgressiveMode(OS_PROGRESSIVE_MODE_OFF);
	}
	HuSprGrpKill(group);
	group = HuSprGrpCreate(1);
	if(!option) {
		data = HuSprAnimReadFile(TITLE_PROGRESSIVE_ON_ANM);
	} else {
		data = HuSprAnimReadFile(TITLE_PROGRESSIVE_OFF_ANM);
	}
	sprite = HuSprCreate(data, 0, 0);
	HuSprGrpMemberSet(group, 0, sprite);
	HuSprPosSet(group, 0, 288, 240);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuPrcSleep(60);
	for(i=0; i<180; i++) {
		if(HU_PAD_BTNDOWN_ALL & PAD_BUTTON_A) {
			break;
		}
		HuPrcVSleep();
	}
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuSprGrpKill(group);
	HuPrcSleep(30);
}

u16 lbl_1_data_58[] = {
	1, 2
};

void fn_1_1178(void)
{
	s16 i;
	for(i=0; i<1; i++) {
		Vec pos, target, up;
		float x, y, z;
		
		x = lbl_1_bss_3C[i].x;
		y = lbl_1_bss_3C[i].y;
		z = lbl_1_bss_3C[i].z;
		
		pos.x = (((sind(y)*cosd(x))*lbl_1_bss_1C[i])+lbl_1_bss_24[i].x);
		pos.y = (-sind(x)*lbl_1_bss_1C[i])+lbl_1_bss_24[i].y;
		pos.z = ((cosd(y)*cosd(x))*lbl_1_bss_1C[i])+lbl_1_bss_24[i].z;
		target.x = lbl_1_bss_24[i].x;
		target.y = lbl_1_bss_24[i].y;
		target.z = lbl_1_bss_24[i].z;
		up.x = sind(y)*sind(x);
		up.y = cosd(x);
		up.z = cosd(y)*sind(x);
		Hu3DCameraPosSet(lbl_1_data_58[i], pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
	}
}

void fn_1_152C(void) {
    Vec pos;
    Vec offset;
    Vec dir;
    Vec y_offset;
    
    f32 z_rot;
    s8 stick_pos;

    if ((HuPadBtnDown[0] & 0x800)) {
        lbl_1_bss_0 = (lbl_1_bss_0) ? 0 : 1;
    }
    if (lbl_1_bss_0 != 0) {
        lbl_1_bss_3C[0].y += 0.1f * HuPadStkX[0];
        lbl_1_bss_3C[0].x += 0.1f * HuPadStkY[0];
        lbl_1_bss_1C[0] += HuPadTrigL[0] / 2;
        lbl_1_bss_1C[0] -= HuPadTrigR[0] / 2;
        if (lbl_1_bss_1C[0] < 100.0f) {
            lbl_1_bss_1C[0] = 100.0f;
        }
        pos.x = lbl_1_bss_24[0].x + (lbl_1_bss_1C[0] * (sind(lbl_1_bss_3C[0].y) * cosd(lbl_1_bss_3C[0].x)));
        pos.y = (lbl_1_bss_24[0].y + (lbl_1_bss_1C[0] * -sind(lbl_1_bss_3C[0].x)));
        pos.z = (lbl_1_bss_24[0].z + (lbl_1_bss_1C[0] * (cosd(lbl_1_bss_3C[0].y) * cosd(lbl_1_bss_3C[0].x))));
        offset.x = lbl_1_bss_24[0].x - pos.x;
        offset.y = lbl_1_bss_24[0].y - pos.y;
        offset.z = lbl_1_bss_24[0].z - pos.z;
        dir.x = (sind(lbl_1_bss_3C[0].y) * sind(lbl_1_bss_3C[0].x));
        dir.y = cosd(lbl_1_bss_3C[0].x);
        dir.z = (cosd(lbl_1_bss_3C[0].y) * sind(lbl_1_bss_3C[0].x));
        z_rot = lbl_1_bss_3C[0].z;
        y_offset.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * cosd(z_rot))
              + dir.y * (offset.x * offset.y * (1.0f - cosd(z_rot)) - offset.z * sind(z_rot))
              + dir.z * (offset.x * offset.z * (1.0f - cosd(z_rot)) + offset.y * sind(z_rot));

        y_offset.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * cosd(z_rot))
              + dir.x * (offset.x * offset.y * (1.0f - cosd(z_rot)) + offset.z * sind(z_rot))
              + dir.z * (offset.y * offset.z * (1.0f - cosd(z_rot)) - offset.x * sind(z_rot));
        
        y_offset.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * cosd(z_rot))
                      + (dir.x * (offset.x * offset.z * (1.0 - cosd(z_rot)) - offset.y * sind(z_rot))
                      + dir.y * (offset.y * offset.z * (1.0 - cosd(z_rot)) + offset.x * sind(z_rot)));

        PSVECCrossProduct(&dir, &offset, &offset);
        PSVECNormalize(&offset, &offset);
        stick_pos = (HuPadSubStkX[0] & 0xF8);
        if (stick_pos != 0) {
            lbl_1_bss_24[0].x += 0.05f * (offset.x * stick_pos);
            lbl_1_bss_24[0].y += 0.05f * (offset.y * stick_pos);
            lbl_1_bss_24[0].z += 0.05f * (offset.z * stick_pos);
        }
        PSVECNormalize(&y_offset, &offset);
        stick_pos = -(HuPadSubStkY[0] & 0xF8);
        if (stick_pos != 0) {
            lbl_1_bss_24[0].x += 0.05f * (offset.x * stick_pos);
            lbl_1_bss_24[0].y += 0.05f * (offset.y * stick_pos);
            lbl_1_bss_24[0].z += 0.05f * (offset.z * stick_pos);
        }
    }
}

static void TitleInit(void)
{
	s16 model;
	s16 sprite;
	AnimData *sprite_data;
	titleModel[0] = model = Hu3DModelCreateFile(TITLE_CHAR_HSF);
	Hu3DModelAttrSet(model, 1);
	Hu3DModelAttrSet(model, 0x40000001);
	titleModel[1] = model = Hu3DModelCreateFile(TITLE_CUBE_HSF);
	Hu3DModelAttrSet(model, 1);
	Hu3DModelAttrSet(model, 0x40000001);
	titleModel[2] = model = Hu3DModelCreateFile(TITLE_SKY_HSF);
	Hu3DModelAttrSet(model, 1);
	Hu3DModelAttrSet(model, 0x40000001);
	Hu3DModelCameraInfoSet(model, 1);
	Hu3DModelLightInfoSet(model, 1);
	titleGroup = HuSprGrpCreate(4);
	sprite_data = HuSprAnimReadFile(TITLE_BG_ANM);
	sprite = HuSprCreate(sprite_data, 0, 0);
	HuSprGrpMemberSet(titleGroup, 0, sprite);
	HuSprAttrSet(titleGroup, 0, HUSPR_ATTR_DISPOFF);
	HuSprDrawNoSet(titleGroup, 0, 127);
	HuSprPosSet(titleGroup, 0, 288, 240);
	sprite_data = HuSprAnimReadFile(TITLE_COPYRIGHT_ANM);
	sprite = HuSprCreate(sprite_data, 1, 0);
	HuSprGrpMemberSet(titleGroup, 1, sprite);
	HuSprAttrSet(titleGroup, 1, HUSPR_ATTR_DISPOFF);
	HuSprPosSet(titleGroup, 1, 288, 420);
	sprite_data = HuSprAnimReadFile(TITLE_PRESS_START_ANM);
	sprite = HuSprCreate(sprite_data, 2, 0);
	HuSprGrpMemberSet(titleGroup, 2, sprite);
	HuSprAttrSet(titleGroup, 2, HUSPR_ATTR_DISPOFF|HUSPR_ATTR_LINEAR);
	HuSprPosSet(titleGroup, 2, 288, 380);
	sprite_data = HuSprAnimReadFile(TITLE_LOGO_ANM);
	sprite = HuSprCreate(sprite_data, 0, 0);
	HuSprGrpMemberSet(titleGroup, 3, sprite);
	HuSprAttrSet(titleGroup, 3, HUSPR_ATTR_DISPOFF|HUSPR_ATTR_LINEAR);
	HuSprPosSet(titleGroup, 3, 288, 200);
}

static BOOL TitleProc(void)
{
	float scale;
	float scale_time;
	s32 y_offset[32];
	s16 i;
	Hu3DModelAttrReset(titleModel[0], 1);
	Hu3DModelAttrReset(titleModel[1], 1);
	HuSprAttrReset(titleGroup, 0, HUSPR_ATTR_DISPOFF);
	HuSprAttrReset(titleGroup, 1, HUSPR_ATTR_DISPOFF);
	OSReport(">>>>>>>>MSM_SE_SEL_01 %d\n", msmSeGetEntryID(2092, y_offset));
	OSReport(">>>>>>>>SE Num %d\n", msmSeGetNumPlay(0));
	HuAudSStreamPlay(20);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	HuSprAttrReset(titleGroup, 3, HUSPR_ATTR_DISPOFF);
	for(i=1; i<=50; i++) {
		scale = (cosd(i*1.8)*10.0)+1.0;
		HuSprScaleSet(titleGroup, 3, scale, scale);
		HuSprTPLvlSet(titleGroup, 3, i/50.0);
		HuPrcVSleep();
	}
	HuSprAttrReset(titleGroup, 2, HUSPR_ATTR_DISPOFF);
	for(i=scale_time=0; i<1800; i++) {
		if(i <= 10) {
			HuSprTPLvlSet(titleGroup, 2, i/10.0);
		}
		if(HuPadBtnDown[0] & PAD_BUTTON_START) {
			s32 ret = HuAudFXPlay(2092);
			if(ret < 0) {
				OSReport(">>>>>Error %d\n", ret);
			}
			HuSprAttrSet(titleGroup, 2, HUSPR_ATTR_DISPOFF);
			return 1;
		}
		scale = (sind(i*scale_time)*0.1)+0.9;
		scale_time += 0.05;
		if(scale_time > 5) {
			scale_time = 5;
		}
		HuSprScaleSet(titleGroup, 2, scale, scale);
		HuPrcVSleep();
	}
	WipeColorSet(255, 255, 255);
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
	while(WipeStatGet()) {
		HuPrcVSleep();
	}
	Hu3DModelAttrSet(titleModel[0], 1);
	Hu3DModelAttrSet(titleModel[1], 1);
	Hu3DModelAttrSet(titleModel[2], 1);
	HuSprAttrSet(titleGroup, 0, HUSPR_ATTR_DISPOFF);
	HuSprAttrSet(titleGroup, 1, HUSPR_ATTR_DISPOFF);
	HuSprAttrSet(titleGroup, 2, HUSPR_ATTR_DISPOFF);
	HuSprAttrSet(titleGroup, 3, HUSPR_ATTR_DISPOFF);
	return 0;
}
