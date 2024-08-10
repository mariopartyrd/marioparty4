#include "game/armem.h"
#include "game/sprite.h"
#include "game/process.h"
#include "game/gamework_data.h"
#include "game/objsub.h"
#include "game/object.h"
#include "game/hsfman.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/minigame_seq.h"

#include "math.h"

#include "stdarg.h"

#undef abs

#define ABS(x) (((x) < 0) ? -(x) : (x))


extern s16 HuSysVWaitGet(s16 param);

typedef struct seq_info {
	SeqInitFunc init;
	SeqUpdateFunc update;
	float x;
	float y;
	float scale_x;
	float scale_y;
	s32 time_max;
} SeqInfo;

static s32 SeqInitTimer(SeqWork *work, va_list params);
static s32 SeqUpdateTimer(SeqWork *work);

static s32 SeqInitType2(SeqWork *work, va_list params);
static s32 SeqUpdateType2(SeqWork *work);

static s32 SeqInitMGBasic(SeqWork *work, va_list params);
static s32 SeqUpdateMGBasic(SeqWork *work);
static s32 SeqInitMGCommon(SeqWork *work, va_list params);
static s32 SeqUpdateMG1vs3(SeqWork *work);
static s32 SeqUpdateMGBattle(SeqWork *work);
static s32 SeqUpdateMGStory(SeqWork *work);
static s32 SeqUpdateMG2vs2(SeqWork *work);
static s32 SeqUpdateMGBowser(SeqWork *work);

static s32 SeqInitWin(SeqWork *work, va_list params);
static s32 SeqUpdateWin(SeqWork *work);
static s32 SeqInitDraw(SeqWork *work, va_list params);
static s32 SeqUpdateDraw(SeqWork *work);
static s32 SeqInitRecord(SeqWork *work, va_list params);
static s32 SeqUpdateRecord(SeqWork *work);

static s32 SeqInitFlip(SeqWork *work, va_list params);
static s32 SeqUpdateFlip(SeqWork *work);

OverlayID mgSeqOvlPrev = OVL_INVALID;

static SeqInfo seqInfoTbl[] = {
	{ NULL, NULL, 292.0f, 240.0f, 1.0f, 1.0f, 60 },
	{ SeqInitTimer, SeqUpdateTimer, 292.0f, 64.0f, 1.0f, 1.0f, 60 },
	{ SeqInitType2, SeqUpdateType2, 292.0f, 240.0f, 0.5f, 0.5f, 60 },
	{ SeqInitMGBasic, SeqUpdateMGBasic, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMG1vs3, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitWin, SeqUpdateWin, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMGBattle, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMGStory, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGBasic, SeqUpdateMGBasic, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMG2vs2, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitFlip, SeqUpdateFlip, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitMGCommon, SeqUpdateMGBowser, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitWin, SeqUpdateWin, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ SeqInitDraw, SeqUpdateDraw, 292.0f, 240.0f, 1.0f, 1.0f, 60 },
	{ SeqInitRecord, SeqUpdateRecord, 292.0f, 240.0f, 1.0f, 1.0f, 180 },
	{ NULL, NULL, 292.0f, 240.0f, 1.0f, 1.0f, 60 },
	{ NULL, NULL, 292.0f, 240.0f, 1.0f, 1.0f, 60 },
};

static s32 seqType2SprTbl[6] = {
	0, 0, 0, 0, 0, 0
};

static s16 mgSeqTypeTbl[9] = {
	MG_SEQ_TYPE_4P,
	MG_SEQ_TYPE_1VS3,
	MG_SEQ_TYPE_2VS2,
	MG_SEQ_TYPE_BOWSER,
	MG_SEQ_TYPE_BATTLE,
	MG_SEQ_TYPE_PINBALL,
	MG_SEQ_TYPE_STORY,
	MG_SEQ_TYPE_BOWSER,
	MG_SEQ_TYPE_STORY
};

static char lbl_8012F336[] = {
	"ｱｲｳｴｵｶｷｸ"
	"ｹｺｻｼｽｾｿﾀ"
	"ﾁﾂﾃﾄﾅﾆﾇﾈ"
	"ﾉﾊﾋﾌﾍﾎﾏﾐ"
	"ﾑﾒﾓﾔﾕﾖﾗﾘ"
	"ﾙﾚﾛﾜｦﾝｧｨ"
	"ｩｪｫｬｭｮｯｶ"
	"ｷｸｺｻｼｽｾｿ"
	"ﾀﾁﾂﾃﾄﾊﾋﾌ"
	"ﾍﾎﾊﾋﾌﾍﾎ"
	"!?ｰ"
};

static char lbl_8012F389[] = "x first\n";
static char lbl_8012F392[] = "y first\n";

static SeqWork seqWorkData[8];

static s16 seqTimer;
static u8 seqDoneF;
u8 lbl_801D3D94;
static s16 seqSpeed;
static s16 seqPauseF;
static int seqRecordVal;
static s32 pauseWaitF;
static s32 pauseExitF;
static s32 pauseActiveF;
static Process *pauseProcess;
static s32 seqLanguage;

void fn_80036BC8(void);


void MGSeqInit(void)
{
	s32 i;
	SeqWork *work;
	work = &seqWorkData[0];
	for(i=8; i!=0; i--, work++) {
		work->seq_no = 0;
		work->data = NULL;
	}
	seqPauseF = 0;
	seqDoneF = 0;
	lbl_801D3D94 = 0;
	seqTimer = 30;
	HuAR_DVDtoARAM(DATADIR_GAMEMES);
	HuAR_DVDtoARAM(DATADIR_MGCONST);
	while(HuARDMACheck());
	fn_80036BC8();
	mgSeqOvlPrev = -1;
	seqLanguage = GWLanguageGet();
}

void MGSeqMain(void)
{
	SeqInfo *info;
	s32 i;
	s32 j;
	s32 alive_flag;
	u8 stat;
	SeqWork *work;
	
	seqSpeed = HuSysVWaitGet(seqSpeed);
	if(Hu3DPauseF) {
		return;
	}
	alive_flag = 0;
	stat = 0;
	work = &seqWorkData[0];
	for(i=0; i<8; i++, work++) {
		if(work->stat == 0) {
			continue;
		}
		if(work->update) {
			alive_flag = work->update(work);
		} else {
			info = &seqInfoTbl[work->seq_no];
			if(work->seq_no != 0 && NULL != info->update) {
				alive_flag = info->update(work);
			}
		}
		if(!alive_flag) {
			work->stat = 0;
			if(!lbl_801D3D94) {
				for(j=0; j<8; j++) {
					if(seqWorkData[j].stat) {
						break;
					}
				}
			}
			if(!work->data) {
				HuMemDirectFree(work->data);
				work->data = NULL;
			}
		}
		stat |= work->stat;
	}
	if(!stat || stat & 0x4) {
		if(seqTimer > 0) {
			seqTimer -= seqSpeed;
		}
	}
}

static s16 CreateSeq(s16 seq_no, va_list params)
{
	SeqWork *work;
	SeqInfo *info;
	s32 i;
	s32 temp;
	work = seqWorkData;
	info = &seqInfoTbl[(u8)seq_no];
	for(i=0; i<8; i++, work++) {
		if(work->stat == 0) {
			break;
		}
	}
	if(i >= 8) {
		return -1;
	}
	work->stat |= 0x1;
	if(work->data) {
		HuMemDirectFree(work->data);
	}
	work->data = NULL;
	work->seq_no = (u8)seq_no;
	work->time = 0;
	work->x = info->x;
	work->y = info->y;
	work->scale_x = info->scale_x;
	work->scale_y = info->scale_y;
	work->unk_18 = 0.0f;
	work->unk_7D = 255;
	work->time_max = info->time_max;
	work->timer_val = work->state = work->alt_word_len = work->word_len = 0;
	work->angle = work->win_scale = 0.0f;
	work->param[0] = work->param[1] = 0;
	for(temp=0; temp<16; temp++) {
		work->sprite[temp] = work->spr_grp[temp] = -1;
	}
	if(NULL != info->init) {
		temp = info->init(work, params);
		if(temp == 0) {
			work->stat = 0;
			return -1;
		} 
	}
	seqTimer = 30;
	return i;
}

s16 MGSeqCreate(s16 type, ...)
{
	s16 ret;
	va_list params;
	va_start(params, type);
	if(type == MG_SEQ_TYPE_AUTO) {
		if(GWSystem.mg_next == 0xFFFF) {
			type = MG_SEQ_TYPE_4P;
		} else {
			type = mgSeqTypeTbl[mgInfoTbl[GWSystem.mg_next].type];
		}
	}
	ret = CreateSeq(type, params);
	va_end(params);
	return ret;
}

u8 MGSeqStatGet(s16 id)
{
	SeqWork *work;
	u8 ret = 0;
	if(id < 0) {
		s32 i;
		work = seqWorkData;
		for(i=8; i != 0; i--, work++) {
			ret |= work->stat;
		}
	} else {
		if(id < 8) {
			ret = seqWorkData[id].stat;
		}
	}
	return ret;
}

void MGSeqPosSet(s16 id, float x, float y)
{
	if(id >= 0 && id < 8) {
		seqWorkData[id].x = x;
		seqWorkData[id].y = y;
	}
}

void MGSeqParamSet(s16 id, s16 param1, s16 param2)
{
	if(id >= 0 && id < 8) {
		seqWorkData[id].param[0] = param1;
		seqWorkData[id].param[1] = param2;
	}
}

void MGSeqKill(s16 id)
{
	if(id >= 0 && id < 8) {
		if(seqWorkData[id].stat != 0) {
			seqWorkData[id].stat = 8;
		}
	}
}

void MGSeqKillAll(void)
{
	seqDoneF = 1;
	MGSeqMain();
	seqDoneF = 0;
	MGSeqStub();
	lbl_801D3D94 = 0;
}

s32 MGSeqDoneCheck(void)
{
	u8 stat = MGSeqStatGet(-1);
	if(stat == 0 || (stat & 0xC)) {
		if(seqTimer <= 0 || (stat & 0x8)) {
			return 1;
		}
	}
	return 0;
}

void MGSeqStub(void)
{
	
}

void MGSeqSprKill(SeqWork *work)
{
	s32 i;
	for(i=0; i<16; i++) {
		if(work->spr_grp[i] >= 0) {
			HuSprGrpKill(work->spr_grp[i]);
		}
		if(work->sprite[i] >= 0) {
			HuSprKill(work->sprite[i]);
		}
	}
}

static void *SeqReadFile(s32 file)
{
	return HuAR_ARAMtoMRAMFileRead(file, MEMORY_DEFAULT_NUM, HEAP_DATA);
}

static s32 SeqInitTimer(SeqWork *work, va_list params)
{
	AnimData *spr_anim;
	s16 sprite;
	s16 spr_grp;
	int duration, x, y;
	s16 i;
	
	duration = va_arg(params, int);
	x = va_arg(params, int);
	y = va_arg(params, int);
	if(duration <= 0 && duration > 99) {
		duration = 99;
	}
	work->timer_val = duration;
	if(x >= 0) {
		work->x = x;
	}
	if(y >= 0) {
		work->y = y;
	}
	work->alt_word_len = 0;
	work->state = 2;
	work->angle = 0;
	work->spr_grp[0] = spr_grp = HuSprGrpCreate(4);
	HuSprGrpScaleSet(spr_grp, work->scale_x, work->scale_y);
	spr_anim = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 2)));
	x = 12;
	for(i=0; i<2; i++) {
		sprite = HuSprCreate(spr_anim, 5, 0);
		HuSprGrpMemberSet(spr_grp, i, sprite);
		HuSprSpeedSet(spr_grp, i, 0);
		HuSprPosSet(spr_grp, i, x, 0);
		HuSprColorSet(spr_grp, i, 112, 233, 255);
		x -= 24;
		(void)i; //Hack for Matching
	}
	spr_anim = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 1)));
	sprite = HuSprCreate(spr_anim, 7, 0);
	HuSprGrpMemberSet(spr_grp, 2, sprite);
	HuSprPosSet(spr_grp, 2, 0, 0);
	HuSprTPLvlSet(spr_grp, 2, 0.5f);
	HuSprColorSet(spr_grp, 2, 0, 0, 0);
	spr_anim = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 0)));
	sprite = HuSprCreate(spr_anim, 6, 0);
	HuSprGrpMemberSet(spr_grp, 3, sprite);
	HuSprPosSet(spr_grp, 3, 0, 0);
	if(seqPauseF) {
		work->state = 1;
		for(i=0; i<2; i++) {
			HuSprAttrSet(spr_grp, i, HUSPR_ATTR_DISPOFF);
			(void)i; //Hack for Matching
		}		
	}
	return 1;
}

static s32 SeqUpdateTimer(SeqWork *work)
{
	float scale;
	float tp_lvl;
	u8 digits[2];
	s16 i;
	s16 spr_grp = work->spr_grp[0];
	if(work->param[0] != 0 && work->state != -1) {
		switch(work->param[0]) {
			case 2:
				switch(work->param[1]) {
					case -1:
						work->stat |= 0x4;
						work->state = -1;
						work->angle = 0.0f;
						break;
						
					case 0:
						work->state = 2;
						work->angle = 0.0f;
						break;
						
					case 1:
						work->state = 3;
						work->angle = 0.0f;
						break;
						
					default:
						break;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				if(work->param[1] < 0 && !(work->stat & 0x4)) {
					work->stat |= 0x4;
					work->state = -1;
					work->angle = 0.0f;
				} else {
					if(work->param[1] > 99) {
						work->timer_val = 99;
					} else {
						if(work->timer_val != work->param[1]) {
							work->timer_val = work->param[1];
							if(work->param[1] <= 5) {
								HuAudFXPlay(6);
								work->state = 3;
								work->angle = 0.0f;
								HuSprColorSet(spr_grp, 0, 255, 112, 160);
								HuSprColorSet(spr_grp, 1, 255, 112, 160);
							} else {
								HuSprColorSet(spr_grp, 0, 112, 233, 255);
								HuSprColorSet(spr_grp, 1, 112, 233, 255);
							}
						}
					}
				}
				work->param[0] = 0;
				break;
				
			case 3:
				for(i=0; i<2; i++) {
					HuSprAttrReset(spr_grp, i, HUSPR_ATTR_DISPOFF);
				}
				work->state = 3;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->state == 1) {
		return 1;
	}
	if(work->timer_val > 99) {
		digits[0] = digits[1] = 9;
	} else {
		s32 value;
		value = work->timer_val/10;
		digits[1] = value;
		digits[0] = work->timer_val-(value*10);
	}
	HuSprGrpPosSet(spr_grp, work->x, work->y);
	HuSprGrpScaleSet(spr_grp, work->scale_x, work->scale_y);
	for(i=0; i<2; i++) {
		HuSprBankSet(spr_grp, i, digits[i]);
	}
	if(work->state != 0) {
		switch(work->state) {
			case 2:
			{
				float scale_x, scale_y;
				scale = fabs(((sin((work->angle*M_PI)/180)*5.0f)+1.0f)-(sin((130*M_PI)/180)*5.0f));
				scale_x = work->scale_x*scale;
				scale_y = work->scale_y*scale;
				work->angle += seqSpeed*5.0f;
				if(work->angle > 130.0f) {
					work->state = 0;
					break;
				}
				HuSprGrpScaleSet(spr_grp, scale_x, scale_y);
			}
				break;
				
			case 3:
			{
				scale = sin((work->angle*M_PI)/180)+1.0;
				tp_lvl = 1.0-(sin((work->angle*M_PI)/180)*0.5);
				work->angle += seqSpeed*18.0f;
				if(work->angle > 180.0f) {
					work->state = 0;
					scale = 1.0f;
					tp_lvl = 1.0f;
				}
				for(i=0; i<2; i++) {
					HuSprScaleSet(spr_grp, i, scale, scale);
					HuSprTPLvlSet(spr_grp, i, tp_lvl);
				}
			}
				break;
				
			case -1:
				HuSprGrpScaleSet(spr_grp, work->scale_x, work->scale_y);
				for(i=0; i<2; i++) {
					HuSprScaleSet(spr_grp, i, 1.0f, 1.0f);
				}
				work->angle += 1.0f;
				if(work->angle < 60.0f) {
					break;
				}
				tp_lvl = 1.0-((work->angle-60.0f)/20.0f);
				if(tp_lvl <= 0.0f) {
					tp_lvl = 0.0f;
					work->state = 0;
					work->stat |= 0x8;
				}
				
				for(i=0; i<4; i++) {
					HuSprTPLvlSet(spr_grp, i, tp_lvl);
				}
				break;
				
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	} else {
		return 1;
	}
}

static s32 SeqInitType2(SeqWork *work, va_list params)
{
	s16 spr_idx;
	s16 spr_grp;
	AnimData *anim_tbl[6];
	s32 i;
	s16 len;
	char *str;
	char c;
	int time_max;
	int x, y;
	work->data = va_arg(params, void *);
	time_max = va_arg(params, int);
	x = va_arg(params, int);
	y = va_arg(params, int);
	if(time_max < 0) {
		time_max = -1;
	}
	work->time_max = time_max;
	if(x >= 0) {
		work->x = x;
	}
	if(y >= 0) {
		work->y = y;
	}
	work->state = 0;
	work->angle = 0.0f;
	x = 0;
	len = 0;
	str=work->data;
	while(c=*str++) {
		if(c >= '0' && c <= '9') {
			x |= 1;
			len++;
		} else if(c >= 'A' && c <= 'Z') {
			x |= 2;
			len++;
		} else if(c >= 'a' && c <= 'z') {
			x |= 4;
			len++;
		} else if(c == '!' || c == '?') {
			x |= 8;
			len++;
		}
	}
	work->word_len = len;
	for(i=0; i<6; i++) {
		if(x & (1 << i)) {
			anim_tbl[i] = HuSprAnimRead(SeqReadFile(seqType2SprTbl[i]));
		} else {
			anim_tbl[i] = NULL;
		}
	}
	work->spr_grp[0] = spr_grp = HuSprGrpCreate(len);
	x = 0;
	spr_idx = 0;
	str=work->data;
	while(c=*str++) {
		i = -2;
		if(c >= '0' && c <= '9') {
			c -= '0';
			i = 0;
		} else if(c >= 'A' && c <= 'Z') {
			c -= 'A';
			i = 1;
		} else if(c >= 'a' && c <= 'z') {
			c -= 'a';
			i = 2;
		} else if(c == '!' || c == '?') {
			if(c == '!') {
				c = 0;
			} else {
				c = 1;
			}
			i = 3;
		} else if(c == ' ') {
			i = -1;
		}
		work->alt_word_len = x;
		if(i == -1) {
			x += 32;
		} else if(i >= 0) {
			s16 sprite = HuSprCreate(anim_tbl[i], 5, c);
			HuSprGrpMemberSet(spr_grp, spr_idx, sprite);
			HuSprSpeedSet(spr_grp, spr_idx, 0.0f);
			HuSprPosSet(spr_grp, spr_idx, x, 0.0f);
			spr_idx++;
			x += 64;
		}
	}
	if(seqPauseF) {
		work->state = 1;
		for(i=0; i<work->word_len; i++) {
			HuSprAttrSet(spr_grp, i, HUSPR_ATTR_DISPOFF);
		}
	}
	return 1;
}

static s32 SeqUpdateType2(SeqWork *work)
{
	float tp_lvl;
	s16 spr_grp;
	spr_grp = work->spr_grp[0];
	HuSprGrpPosSet(spr_grp, work->x-((0.5f*work->scale_x)*work->alt_word_len), work->y);
	HuSprGrpScaleSet(spr_grp, work->scale_x, work->scale_y);
	if(work->param[0] != 0 && work->state != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->state = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
			{
				s32 i;
				for(i=0; i<work->word_len; i++) {
					HuSprAttrReset(spr_grp, i, HUSPR_ATTR_DISPOFF);
					(void)i;
				}
				work->state = 0;
				work->param[0] = 0;
			}
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->state == 1) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->state != -1) {
		work->stat |= 0x4;
		work->state = -1;
		work->angle = 0.0f;
	}
	if(work->state != 0) {
		if(work->state != -1) {
			(void)work; //HACK: to introduce extra branch
		} else {
			s16 i;
			work->angle += seqSpeed*0.1f;
			tp_lvl = 1.0f-work->angle;
			if(tp_lvl <= 0.0f) {
				tp_lvl = 0.0f;
				work->state = 0;
				work->stat |= 0x8;
			}
			for(i=0; i<work->word_len; i++) {
				HuSprTPLvlSet(spr_grp, i, tp_lvl);
				(void)i;
			}
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	} else {
		return 1;
	}
}


static char seqFontAlphaTbl[] = {
	"ABCDEFGH"
	"IJKLMNOP"
	"QRSTUVWX"
	"YZabcdef"
	"ghijklmn"
	"opqrstuv"
	"wxyz"
};

static char seqFontKanaTbl[] = {
	"ｱｲｳｴｵｶｷｸ"
	"ｹｺｻｼｽｾｿﾀ"
	"ﾁﾂﾃﾄﾅﾆﾇﾈ"
	"ﾉﾊﾋﾌﾍﾎﾏﾐ"
	"ﾑﾒﾓﾔﾕﾖﾗﾘ"
	"ﾙﾚﾛﾜｦﾝｧｨ"
	"ｩｪｫｬｭｮｯｶ"
	"ｷｸｹｺｻｼｽｾ"
	"ｿﾀﾁﾂﾃﾄﾊﾋ"
	"ﾌﾍﾎﾊﾋﾌﾍﾎ"
	"ｰ"
};

static char seqFontNumTbl[] = "0123456789";

static s32 *letterBufTbl[5] = { };

static char wordStartE[] = "START!";

static char seqPunctTbl[] = "!?";

static char wordStartJ[] = "ｽﾀｰﾄ!";

static char wordFinishJ[] = "ﾌｨﾆｯｼｭ!";

static char wordDrawJ[] = "ﾋｷﾜｹ!";

static char wordFinishE[] = "FINISH!";
static char wordDrawE[] = "DRAW!";

static char *wordMgTbl[6] = {
	wordStartJ, wordFinishJ, wordDrawJ,
	wordStartE, wordFinishE, wordDrawE,
};

void fn_80036BC8(void)
{
	if(!letterBufTbl[0]) {
		letterBufTbl[0] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqFontAlphaTbl));
		memset(letterBufTbl[0], 0, sizeof(s32)*strlen(seqFontAlphaTbl));
	}
	if(!letterBufTbl[1]) {
		letterBufTbl[1] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqFontKanaTbl));
		memset(letterBufTbl[1], 0, sizeof(s32)*strlen(seqFontKanaTbl));
	}
	if(!letterBufTbl[2]) {
		letterBufTbl[2] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqFontKanaTbl));
		memset(letterBufTbl[2], 0, sizeof(s32)*strlen(seqFontKanaTbl));
	}
	if(!letterBufTbl[3]) {
		letterBufTbl[3] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqFontNumTbl));
		memset(letterBufTbl[3], 0, sizeof(s32)*strlen(seqFontNumTbl));
	}
	if(!letterBufTbl[4]) {
		letterBufTbl[4] = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s32)*strlen(seqPunctTbl));
		memset(letterBufTbl[4], 0, sizeof(s32)*strlen(seqPunctTbl));
	}
}

static AnimData *SeqLoadFontChar(char *str, s16 flags);

static s32 SeqMakeWord(SeqWork *work, char *str, s16 flags)
{
	s16 *char_pos;
	char *str_ptr;
	s16 spr_grp;
	s16 i;
	s16 x;
	s16 grp_idx;
	s16 len;
	AnimData **char_anim;
	for(grp_idx=0; grp_idx<16; grp_idx++) {
		if(work->spr_grp[grp_idx] == -1) {
			break;
		}
	}
	if(grp_idx == 16) {
		return -1;
	}
	char_anim = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(AnimData *)*100);
	char_pos = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s16)*100);
	str_ptr = str;
	x = 0;
	len = 0;
	while(*str_ptr != 0) {
		char_anim[len] = SeqLoadFontChar(str_ptr, flags);
		if(char_anim[len]) {
			char_pos[len] = x;
			x += 56;
			len++;
		}
		str_ptr++;
	}
	work->spr_grp[grp_idx] = spr_grp = HuSprGrpCreate(len);
	x = (x/2)-28;
	for(i=0; i<len; i++) {
		s16 sprite = HuSprCreate(char_anim[i], 5, 0);
		HuSprGrpMemberSet(spr_grp, i, sprite);
		HuSprPosSet(spr_grp, i, char_pos[i]-x, 0.0f);
	}
	work->word_len = len;
	HuMemDirectFree(char_anim);
	HuMemDirectFree(char_pos);
	return grp_idx;
}

static AnimData *SeqLoadFontChar(char *str, s16 flags)
{
	s32 data_num;
	s16 id;
	char *list;
	char c = *str;
	if(c == 222 || c == 223) {
		return NULL;
	}
	if(c == 32) {
		return HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 10)));
	}
	for(id = 0, list=seqFontAlphaTbl; *list != 0; id++, list++) {
		if(*list == c) {
			data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+21);
			return HuSprAnimRead(SeqReadFile(data_num));
		}
	}
	for(id = 0, list=seqFontNumTbl; *list != 0; id++, list++) {
		if(*list == c) {
			data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+11);
			return HuSprAnimRead(SeqReadFile(data_num));
		}
	}
	for(id = 0, list=seqPunctTbl; *list != 0; id++, list++) {
		if(*list == c) {
			data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+154);
			return HuSprAnimRead(SeqReadFile(data_num));
		}
	}
	if(str[1] == 222) { //゛
		list = seqFontKanaTbl;
		list += 55;
		id = 55;
	} else if(str[1] == 223) { //゜
		list = seqFontKanaTbl;
		list += 75;
		id = 75;
	} else {
		list = seqFontKanaTbl;
		id = 0;
	}
	while(*list != 0) {
		if(*list == c) {
			if(flags & 0x1) {
				data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+156);
			} else {
				data_num = DATA_MAKE_NUM(DATADIR_GAMEMES, id+73);
			}
			return HuSprAnimRead(SeqReadFile(data_num));
		}
		id++;
		list++;
	}
	return NULL;
}

static float ForceDefine480()
{
	return 480.0f;
}

static void SeqPlayStartFX(void);

static s32 SeqInitMGBasic(SeqWork *work, va_list params)
{
	s16 i;
	s16 word_grp;
	
	work->state = va_arg(params, int);
	if(work->state == 2) {
		return SeqInitDraw(work, params);
	}
	work->type = 0;
	work->angle = 0;
	
	{
		s32 word_katakana;
		s32 word_flag;
		s32 word_ofs;
		word_katakana = 0;
		if(work->state == 2 && seqLanguage == 0) {
			word_katakana = 1;
		}
		if(word_katakana) {
			word_flag = 1;
		} else {
			word_flag = 0;
		}
		if(seqLanguage == 0) {
			word_ofs = 0;
		} else {
			word_ofs = 3;
		}
		word_grp = SeqMakeWord(work, wordMgTbl[work->state+word_ofs], word_flag);
	}
	HuSprGrpPosSet(work->spr_grp[word_grp], 0.0f, 0.0f);
	
	for(i=0; i<work->word_len; i++) {
		HuSprTPLvlSet(work->spr_grp[word_grp], i, 1.0f);
		HuSprPosSet(work->spr_grp[word_grp], i, -100.0f, 240.0f);
	}
	if(seqPauseF) {
		work->type = 2;
		HuSprAttrSet(word_grp, 0, HUSPR_ATTR_DISPOFF);
	} else {
		work->param[0] = 3;
	}
	return 1;
}

static s32 SeqUpdateMGBasic(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->type = -1;
		work->angle = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float pos_x;
				float time;
				s16 i;
				if(work->state == 0) {
					if(work->time <= 40) {
						for(i=0; i<work->word_len; i++) {
							time = work->time-((20/work->word_len)*(work->word_len-i-1));
							if(time < 0 || time > 20.0f) {
								continue;
							}
							pos_x = (work->x-(0.5f*(work->word_len*56)))+28.0f+(i*56);
							if(time == 20.0f) {
								HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
								HuSprZRotSet(work->spr_grp[0], i, 0.0f);
							} else {
								HuSprPosSet(work->spr_grp[0], i, pos_x-(((1.0-sin(((time*4.5f)*M_PI)/180.0))*(work->word_len*56*2))), work->y);
								HuSprZRotSet(work->spr_grp[0], i, (time/20.0f)*390.0f);
							}
						}
					} else {
						time = work->time-40;
						scale = work->scale_x+(0.5*sin(((time*9.0f)*M_PI)/180.0));
						for(i=0; i<work->word_len; i++) {
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->word_len*56)))))+(scale*(i*56));
							HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], i, scale, work->scale_y+sin(((time*9.0f)*M_PI)/180.0));
						}
					}
					if(work->time == 40) {
						idx = HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 60) {
						SeqPlayStartFX();
						work->stat |= 0x4;
					}
					if(work->time >= 60) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->state == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						time = work->time;
						scale = work->scale_x+(0.5*sin(((time*9.0f)*M_PI)/180.0));
						for(i=0; i<work->word_len; i++) {
							HuSprAttrReset(work->spr_grp[0], i, HUSPR_ATTR_DISPOFF);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->word_len*56)))))+(scale*(i*56));
							HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], i, work->scale_x+sin(((time*9.0f)*M_PI)/180.0), work->scale_y+sin(((time*9.0f)*M_PI)/180.0));
						}
						if(time == 20.0f) {
							for(i=0; i<work->word_len; i++) {
								HuSprAttrReset(work->spr_grp[0], i, HUSPR_ATTR_DISPOFF);
							}
						}
					} else {
						if(work->time > 80) {
							for(i=0; i<work->word_len; i++) {
								time = (work->time-80)-((20/work->word_len)*(work->word_len-i-1));
								if(time < 0.0f || time > 20.0f) {
									continue;
								}
								pos_x = (28.0f+(work->x-(0.5f*(work->word_len*56))))+(i*56);
								if(time == 20.0f) {
									HuSprAttrSet(work->spr_grp[0], i, HUSPR_ATTR_DISPOFF);
								} else {
									HuSprPosSet(work->spr_grp[0], i, pos_x+((1.0-cos(((time*4.5f)*M_PI)/180.0f))*(work->word_len*56*2)), work->y);
									HuSprZRotSet(work->spr_grp[0], i, (time/20.0f)*390.0f);
								}
							}
						}
					}
					if(work->time == 110) {
						work->stat |= 0x4;
					}
					if(work->time >= 110) {
						work->type = 0;
						work->stat |= 8;
					}
				}
			}
				break;
				
			case -1:
			{
				work->angle += seqSpeed*0.1f;
				scale = 1.0f-work->angle;
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->state == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->word_len; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
				break;
				
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static s32 SeqInitMGCommon(SeqWork *work, va_list params)
{
	s16 i;
	float tp_lvl;
	s16 j;
	s16 word_grp;
	
	work->state = va_arg(params, int);
	if(work->state == 2) {
		return SeqInitDraw(work, params);
	}
	work->type = 0;
	work->angle = 0;
	tp_lvl = 1.0f;
	for(i=0; i<4; i++) {
		if(i == 0)
		{
			s32 word_katakana;
			s32 word_flag;
			s32 word_ofs;
			word_katakana = 0;
			if(work->state == 2 && seqLanguage == 0) {
				word_katakana = 1;
			}
			if(word_katakana) {
				word_flag = 1;
			} else {
				word_flag = 0;
			}
			if(seqLanguage == 0) {
				word_ofs = 0;
			} else {
				word_ofs = 3;
			}
			word_grp = SeqMakeWord(work, wordMgTbl[work->state+word_ofs], word_flag);
		} else {
			s16 grp_idx;
			s32 new_grp;
			for(grp_idx=0; grp_idx<16; grp_idx++) {
				if(work->spr_grp[grp_idx] == -1) {
					break;
				}
			}
			if(grp_idx == 16) {
				new_grp = -1;
			} else {
				work->spr_grp[grp_idx] = HuSprGrpCopy(work->spr_grp[word_grp]);
				new_grp = grp_idx;
			}
			(void)new_grp;
			word_grp = new_grp;
		}
		HuSprGrpPosSet(work->spr_grp[word_grp], 0.0f, 0.0f);
		for(j=0; j<work->word_len; j++) {
			HuSprTPLvlSet(work->spr_grp[word_grp], j, tp_lvl);
			HuSprPosSet(work->spr_grp[word_grp], j, -100.0f, 240.0f);
			HuSprPriSet(work->spr_grp[word_grp], j, i+5);
			HuSprAttrSet(work->spr_grp[word_grp], i, HUSPR_ATTR_LINEAR);
		}
		if(i == 0) {
			tp_lvl -= 0.5;
		} else {
			tp_lvl -= 0.1f;
		}
	}
	if(seqPauseF) {
		work->type = 2;
		HuSprAttrSet(word_grp, 0, HUSPR_ATTR_DISPOFF);
	} else {
		work->param[0] = 3;
	}
	return 1;
}

static s32 SeqUpdateMGBattle(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->angle = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				s16 i, j;
				float time;
				float pos_x;
				if(work->state == 0) {
					if(work->time < 45) {
						if(work->time > 10 && work->time <= 40) {
							time = work->time-10;
							scale = 10.0f*(1.0f-(time/30.0f));
							pos_x = (work->x-(0.5f*(work->word_len*56)))+28.0f;
							HuSprPosSet(work->spr_grp[0], 0, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], 0, work->scale_x+scale, work->scale_y+scale);
							scale = time/30.0f;
							HuSprTPLvlSet(work->spr_grp[0], 0, scale);
						}
						for(i=0; i<4; i++) {
							time = work->time-i;
							if(time < 0 || time > 40) {
								continue;
							}
							for(j=1; j<work->word_len; j++) {
								pos_x = (28.0f+(work->x-(0.5f*(work->word_len*56))))+(j*56);
								if(time == 40.0f) {
									HuSprPosSet(work->spr_grp[i], j, pos_x, work->y);
									HuSprZRotSet(work->spr_grp[i], j, 0.0f);
									HuSprScaleSet(work->spr_grp[i], j, work->scale_x, work->scale_y);
									if(i != 0) {
										HuSprAttrSet(work->spr_grp[i], j, HUSPR_ATTR_DISPOFF);
									}
								} else {
									s16 discard_cnt;
									static float letterOfs[] = {
										30, 20,
										20, 3,
										-4, 20,
										-30, 20,
										20, 20,
										-30, 20,
										-10, 40,
										10, -40
									};
									float x, y;
									float ofs_x, ofs_y;
									float zrot, scale_ang;
									x = pos_x;
									y = work->y;
									ofs_x = letterOfs[((j-1)&0x7)*2];
									ofs_y = letterOfs[(((j-1)&0x7)*2)+1];
									zrot = 0.0f;
									discard_cnt = 0;
									scale_ang = 0.0f;
									for(idx=0; idx<40.0f-time; idx++) {
										if(x+ofs_x > 576 || x+ofs_x < 0) {
											ofs_x = -ofs_x;
											discard_cnt++;
										}
										if(y+ofs_y > 480 || y+ofs_y < 0) {
											ofs_y = -ofs_y;
											discard_cnt++;
										}
										if(discard_cnt) {
											zrot += 20.0f;
											scale_ang = 0.0f;
										}
										x += ofs_x;
										y += ofs_y;
									}
									HuSprPosSet(work->spr_grp[i], j, x, y);
									HuSprScaleSet(work->spr_grp[i], j, work->scale_x*cos((M_PI*scale_ang)/180.0), work->scale_y);
									HuSprZRotSet(work->spr_grp[i], j, zrot);
								}
							}
						}
					} else {
						if(work->time > 60) {
							time = work->time-60;
							scale = 0.5*sin((M_PI*(time*9.0f))/180.0);
							for(j=0; j<work->word_len; j++) {
								pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->word_len*56)*(scale+work->scale_x))))+((j*56)*(scale+work->scale_x));
								HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
								HuSprScaleSet(work->spr_grp[0], j, work->scale_x+scale, work->scale_y+scale);
							}
						}
					}
					if(work->time == 60) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 80) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 80) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->state == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(i=1; i<4; i++) {
							for(j=0; j<work->word_len; j++) {
								HuSprAttrSet(work->spr_grp[i], j, HUSPR_ATTR_DISPOFF);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin((M_PI*(time*9.0f))/180.0));
						for(j=0; j<work->word_len; j++) {
							HuSprAttrReset(work->spr_grp[0], j, HUSPR_ATTR_DISPOFF);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->word_len*56)))))+(scale*(j*56));
							HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], j, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f) {
							for(j=0; j<work->word_len; j++) {
								HuSprAttrReset(work->spr_grp[0], j, HUSPR_ATTR_DISPOFF);
							}
						}
					} else {
						if(work->time > 80 && work->time <= 95) {
							time = work->time-80;
							for(j=0; j<work->word_len; j++) {
								pos_x = (28.0f+(work->x-(0.5f*(work->word_len*56))))+(j*56);
								HuSprPosSet(work->spr_grp[0], j, pos_x+((288.0f-pos_x)*(1.0-cos((M_PI*(time*6.0))/180.0))), work->y);
							}
							if(time == 15.0f) {
								for(j=0; j<work->word_len; j++) {
									HuSprAttrReset(work->spr_grp[1], j, HUSPR_ATTR_DISPOFF);
									HuSprPosSet(work->spr_grp[1], j, 288.0f, work->y);
									HuSprTPLvlSet(work->spr_grp[1], j, 1.0f);
								}
							}
						} else {
							if(work->time > 105) {
								for(j=0; j<work->word_len; j++) {
									time = work->time-105;
									time -= j*3;
									if(time < 0) {
										continue;
									}
									scale = 1.0f-(time/15.0f);
									if(scale < 0.0f) {
										scale = 0.0f;
									}
									HuSprPosSet(work->spr_grp[0], j, 288.0f, work->y+((-100.0f-work->y)*(time/20.0f)));
									HuSprTPLvlSet(work->spr_grp[0], j, scale);
									HuSprPosSet(work->spr_grp[1], j, 288.0f, work->y+((580.0f-work->y)*(time/20.0f)));
									HuSprTPLvlSet(work->spr_grp[1], j, scale);
								}
							}
						}
					}
					if(work->time == 130) {
						work->stat |= 0x4;
					}
					if(work->time >= 130) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
				
			}
				break;
				
			case -1:
			{
				work->angle += seqSpeed*0.1f;
				scale = 1.0f-work->angle;
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->state == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->word_len; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
				break;
				
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static s32 SeqUpdateMG1vs3(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->angle = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float time;
				float scale_x, scale_y;
				float pos_x, pos_y;
				s16 i;
				s16 j;
				if(work->state == 0) {
					if(work->time <= 10) {
						scale = work->time/10.0f;
						time = work->time;
						for(idx=0; idx<work->word_len; idx++) {
							scale_x = 0.3*work->scale_x;
							scale_y = 0.3*work->scale_y;
							pos_x = ((28.0f*scale_x)+(work->x-(0.5f*(scale_x*(work->word_len*56)))))+(scale_x*(idx*56));
							pos_y = work->y-(150.0*sin((M_PI*(((16.0f/3.0f)*time)+20.0f))/180.0));
							HuSprPosSet(work->spr_grp[0], idx, pos_x, pos_y);
							HuSprScaleSet(work->spr_grp[0], idx, scale_x, scale_y*cos(M_PI*(12.0f*time)/180.0));
							HuSprTPLvlSet(work->spr_grp[0], idx, scale);
						}
					} else {
						if(work->time <= 60) {
							for(i=0; i<4; i++) {
								for(idx=0; idx<work->word_len; idx++) {
									time = (work->time-10)-(idx*3)-i;
									if(time < 0.0f) {
										time = 0.0f;
									} else {
										if(time > 30.0f) {
											continue;
										}
									}
									scale = 0.3+(0.7*(1.0-cos((M_PI*(time*3.0f))/180.0)));
									scale_x = work->scale_x*scale;
									scale_y = work->scale_y*scale;
									pos_x = ((28.0f*scale_x)+(work->x-(0.5f*(scale_x*(work->word_len*56)))))+(scale_x*(idx*56));
									pos_y = work->y-(150.0*sin((M_PI*(((16.0f/3.0f)*time)+20.0f))/180.0));
									HuSprPosSet(work->spr_grp[i], idx, pos_x, pos_y);
									HuSprScaleSet(work->spr_grp[i], idx, scale_x, scale_y*cos(M_PI*(12.0f*time)/180.0));
								}
							}
							if(work->time == 60) {
								for(i=1; i<4; i++) {
									for(j=0; j<work->word_len; j++) {
										HuSprAttrSet(work->spr_grp[i], j, HUSPR_ATTR_DISPOFF);
									}
								}
							}
						} else {
							if(work->time > 70) {
								time = work->time-70;
								scale = 0.5*sin((M_PI*(time*9.0f))/180.0);
								for(j=0; j<work->word_len; j++) {
									pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->word_len*56)*(scale+work->scale_x))))+((j*56)*(scale+work->scale_x));
									HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
									HuSprScaleSet(work->spr_grp[0], j, work->scale_x+scale, work->scale_y+scale);
								}
							}
						}
					}
					if(work->time == 70) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 90) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 90) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->state == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(i=1; i<4; i++) {
							for(j=0; j<work->word_len; j++) {
								HuSprAttrSet(work->spr_grp[i], j, HUSPR_ATTR_DISPOFF);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin((M_PI*(time*9.0f))/180.0));
						for(j=0; j<work->word_len; j++) {
							HuSprAttrReset(work->spr_grp[0], j, HUSPR_ATTR_DISPOFF);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->word_len*56)))))+(scale*(j*56));
							HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], j, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f) {
							for(i=1; i<4; i++) {
								for(j=0; j<work->word_len; j++) {
									HuSprAttrReset(work->spr_grp[i], j, HUSPR_ATTR_DISPOFF);
								}
							}
						}
					} else {
						if(work->time > 80 || work->time < 140) {
							for(i=0; i<4; i++) {
								for(j=0; j<work->word_len; j++) {
									time = (work->time-80)-i-j;
									if(time < 0 || time > 40) {
										continue;
									}
									if(time <= 20) {
										float pos_base = (28.0f+(work->x-(0.5f*(work->word_len*56))))+(j*56);
										pos_x = (28.0f+(work->x-(0.5f*(work->word_len*56))))+((work->word_len-j-1)*56);
										HuSprPosSet(work->spr_grp[i], j, pos_base+((time/20.0f)*(pos_x-pos_base)), work->y+((440.0f-work->y)*(time/20.0f)));
									} else {
										time -= 20.0f;
										pos_x = (28.0f+(work->x-(0.5f*(work->word_len*56))))+((work->word_len-j-1)*56);
										pos_y = 440.0f;
										HuSprPosSet(work->spr_grp[i], j, pos_x, pos_y+((-40.0f-pos_y)*(time/20.0f)));
									}
								}
							}
						}
					}
					if(work->time == 140) {
						work->stat |= 0x4;
					}
					if(work->time >= 140) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->angle += seqSpeed*0.1f;
				scale = 1.0f-work->angle;
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->state == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->word_len; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static s32 SeqUpdateMGStory(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->angle = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float pos_x, pos_y;
				float time;
				s16 i;
				s16 j;
				if(work->state == 0) {
					if(work->time <= 30) {
						for(idx=0; idx<work->word_len; idx++) {
							time = (work->time-(idx*2));
							if(time < 0.0f || time > 15.0f) {
								continue;
							}
							pos_x = -50.0f;
							HuSprPosSet(work->spr_grp[0], idx, pos_x+((288.0f-pos_x)*(time/15.0f)), work->y);
							HuSprTPLvlSet(work->spr_grp[0], idx, 1.0f);
							HuSprZRotSet(work->spr_grp[0], idx, (1.0-(time/15.0f))*180.0);
							pos_x = 626.0f;
							HuSprPosSet(work->spr_grp[1], idx, pos_x+((288.0f-pos_x)*(time/15.0f)), work->y);
							HuSprTPLvlSet(work->spr_grp[1], idx, 1.0f);
							HuSprZRotSet(work->spr_grp[1], idx, (1.0-(time/15.0f))*-180.0);
						}
						if(work->time == 30) {
							for(j=0; j<work->word_len; j++) {
								HuSprAttrSet(work->spr_grp[1], j, HUSPR_ATTR_DISPOFF);
							}
						}
					} else {
						if(work->time > 35 && work->time <= 45) {
							time = work->time-35;
							for(idx=0; idx<work->word_len; idx++) {
								pos_x = (work->x-(0.5f*(work->word_len*56)))+28.0f+(idx*56);
								HuSprPosSet(work->spr_grp[0], idx, 288.0f+((pos_x-288.0f)*(time/10.0f)), work->y);
							}
						} else {
							if(work->time > 55) {
								time = work->time-55;
								scale = 0.5*sin(M_PI*(9.0f*time)/180.0);
								for(j=0; j<work->word_len; j++) {
									pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->word_len*56)*(scale+work->scale_x))))+((j*56)*(scale+work->scale_x));
									HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
									HuSprScaleSet(work->spr_grp[0], j, work->scale_x+scale, work->scale_y+scale);
								}
							}
						}
					}
					if(work->time == 55) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 75) {
						SeqPlayStartFX();
						work->stat |= 0x4;
					}
					if(work->time >= 75) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->state == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(i=1; i<4; i++) {
							for(j=0; j<work->word_len; j++) {
								HuSprAttrSet(work->spr_grp[i], j, HUSPR_ATTR_DISPOFF);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin((M_PI*(time*9.0f))/180.0));
						for(j=0; j<work->word_len; j++) {
							HuSprAttrReset(work->spr_grp[0], j, HUSPR_ATTR_DISPOFF);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->word_len*56)))))+(scale*(j*56));
							HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], j, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f){ 
							for(i=1; i<4; i++) {
								for(j=0; j<work->word_len; j++) {
									HuSprAttrReset(work->spr_grp[i], j, HUSPR_ATTR_DISPOFF);
								}
							}
						}
					} else if(work->time > 80 && work->time < 160) {
						for(i=0; i<4; i++) {
							for(j=0; j<work->word_len; j++) {
								s16 initF;
								float dx, dy;
								time = (work->time-80)-i;
								if(time < 0 || time > 60) {
									continue;
								}
								pos_x = (28.0f+(work->x-(0.5f*(work->word_len*56))))+(j*56);
								dx = 28.0f+(work->x-(0.5f*(work->word_len*56)));
								pos_y = work->y;
								for(idx=initF=0; idx<time; idx++) {
									if(!initF) {
										pos_x -= 20.0f;
										if(pos_x <= dx) {
											pos_x = 28.0f+(work->x-(0.5f*(work->word_len*56)));
											initF = 1;
											dy = 25.0f;
											dx = 10.0f;
										}
										
									} else {
										pos_x += dx;
										pos_y += dy;
										dx += 0.1;
										dy -= 2.0f;
										if(pos_y < 0.0f) {
											break;
										}
									}
								}
								
								HuSprPosSet(work->spr_grp[i], j, pos_x, pos_y);
							}
						}
					}
					if(work->time == 160) {
						work->stat |= 0x4;
					}
					if(work->time >= 160) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->angle += seqSpeed*0.1f;
				scale = 1.0f-work->angle;
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->state == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->word_len; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static s32 SeqUpdateMG2vs2(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->angle = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				static s16 letterOfs[] = {
					-10, -50,
					0, -30,
					5, -60,
					-10, 60,
					8, -40,
					5, 50,
					-10, 20
				};
				
				float pos_x;
				float time;
				s16 i;
				s16 j;
				if(work->state == 0) {
					if(work->time <= 30) {
						time = work->time;
						for(idx=0; idx<work->word_len; idx++) {
							pos_x = (28.0f+(work->x-(0.5f*(work->scale_x*(work->word_len*56)))))+(idx*56);
							HuSprPosSet(work->spr_grp[0], idx, pos_x+((1.0f-(time/30.0f))*letterOfs[(idx*2)]), work->y+((1.0f-(time/30.0f))*letterOfs[(idx*2)+1])); 
							HuSprTPLvlSet(work->spr_grp[0], idx, time/30.0f);
						}
					} else {
						if(work->time > 40 && work->time <= 60) {
							time = work->time-40;
							scale = 0.5*sin(((time*9.0f)*M_PI)/180.0);
							for(j=0; j<work->word_len; j++) {
								pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->word_len*56)*(scale+work->scale_x))))+((j*56)*(scale+work->scale_x));
								HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
								HuSprScaleSet(work->spr_grp[0], j, work->scale_x+scale, work->scale_y+scale);
							}
						}
					}
					if(work->time == 40) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 60) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 60) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->state == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(i=1; i<4; i++) {
							for(j=0; j<work->word_len; j++) {
								HuSprAttrSet(work->spr_grp[i], j, HUSPR_ATTR_DISPOFF);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin((M_PI*(time*9.0f))/180.0));
						for(j=0; j<work->word_len; j++) {
							HuSprAttrReset(work->spr_grp[0], j, HUSPR_ATTR_DISPOFF);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->word_len*56)))))+(scale*(j*56));
							HuSprPosSet(work->spr_grp[0], j, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], j, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f) {
							for(i=1; i<4; i++) {
								for(j=0; j<work->word_len; j++) {
									HuSprAttrReset(work->spr_grp[i], j, HUSPR_ATTR_DISPOFF);
								}
							}
						}
					} else {
						if(work->time > 80 && work->time < 140) {
							time = work->time-80;
							for(idx=0; idx<work->word_len; idx++) {
								float radius = (idx*56)-(((work->word_len-1)*56)/2);
								float angle = (1.0f+(1.0f-(ABS(radius)/320.0f)))*720.0f;
								float new_scale;
								radius *= 1.0-(time/60.0f);
								HuSprPosSet(work->spr_grp[0], idx, (radius*sin(M_PI*(((time/60.0f)*angle)+90.0f)/180.0))+work->x, (radius*cos(M_PI*(((time/60.0f)*angle)+90.0f)/180.0))+work->y);
								HuSprZRotSet(work->spr_grp[0], idx, -(time/60.0f)*720.0f);
								new_scale = 0.5+(0.5*(1.0f-(time/60.0f)));
								HuSprScaleSet(work->spr_grp[0], idx, new_scale, new_scale);
								HuSprTPLvlSet(work->spr_grp[0], idx, 1.0f-(time/60.0f));
							}
						}
					}
					if(work->time == 140) {
						work->stat |= 0x4;
					}
					if(work->time >= 150) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->angle += seqSpeed*0.1f;
				scale = 1.0f-work->angle;
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->state == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->word_len; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
			break;
			
			default:
				
				break;
				
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static s32 SeqInitFlip(SeqWork *work, va_list params)
{
	s16 i;
	s16 word_grp;
	s16 word_ofs;
	work->state = va_arg(params, int);
	if(work->state == 2) {
		return SeqInitDraw(work, params);
	}
	work->type = 0;
	work->angle = 0;
	{
		s32 word_ofs_temp;
		s32 word_katakana;
		s32 word_flag;

		if(seqLanguage == 0) {
			word_ofs_temp = 3;
		} else {
			word_ofs_temp = 0;
		}
		word_ofs = word_ofs_temp;
		word_katakana = 0;
		if(work->state == 2 && word_ofs == 0) {
			word_katakana = 1;
		}
		if(word_katakana) {
			word_flag = 1;
		} else {
			word_flag = 0;
		}
		
		word_grp = SeqMakeWord(work, wordMgTbl[work->state+word_ofs], word_flag);
	}
	HuSprGrpPosSet(work->spr_grp[word_grp], 0.0f, 0.0f);
	for(i=0; i<work->word_len; i++) {
		HuSprTPLvlSet(work->spr_grp[word_grp], i, 0.0f);
		HuSprPosSet(work->spr_grp[word_grp], i, (28.0f+(work->x-(0.5f*(work->word_len*56))))+(i*56), work->y);
		HuSprAttrSet(work->spr_grp[word_grp], i, HUSPR_ATTR_LINEAR);
		HuSprAttrReset(work->spr_grp[word_grp], i, HUSPR_ATTR_DISPOFF);
	}
	work->alt_word_len = work->word_len;
	{
		s32 word_ofs_temp;
		s32 word_katakana;
		s32 word_flag;
		
		if(seqLanguage == 0) {
			word_ofs_temp = 0;
		} else {
			word_ofs_temp = 3;
		}
		word_ofs = word_ofs_temp;
		word_katakana = 0;
		if(work->state == 2 && word_ofs == 0) {
			word_katakana = 1;
		}
		if(word_katakana) {
			word_flag = 1;
		} else {
			word_flag = 0;
		}
		
		word_grp = SeqMakeWord(work, wordMgTbl[work->state+word_ofs], word_flag);
	}
	HuSprGrpPosSet(work->spr_grp[word_grp], 0.0f, 0.0f);
	for(i=0; i<work->word_len; i++) {
		HuSprTPLvlSet(work->spr_grp[word_grp], i, 0.0f);
		HuSprPosSet(work->spr_grp[word_grp], i, (28.0f+(work->x-(0.5f*(work->word_len*56))))+(i*56), work->y);
		HuSprAttrSet(work->spr_grp[word_grp], i, HUSPR_ATTR_LINEAR);
		HuSprAttrReset(work->spr_grp[word_grp], i, HUSPR_ATTR_DISPOFF);
	}
	if(seqPauseF) {
		work->type = 2;
		HuSprAttrSet(word_grp, 0, HUSPR_ATTR_DISPOFF);
	} else {
		work->param[0] = 3;
	}
	return 1;
}

static s32 SeqUpdateFlip(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->angle = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float time;
				float pos_x;
				s16 i;
				if(work->state == 0) {
					if(work->time <= 10) {
						for(idx=0; idx<work->alt_word_len; idx++) {
							HuSprTPLvlSet(work->spr_grp[0], idx, work->time/10.0f);
						}
					} else {
						if(work->time <= 30) {
							time = work->time-10;
							if(time <= 10) {
								for(idx=0; idx<work->alt_word_len; idx++) {
									HuSprScaleSet(work->spr_grp[0], idx, cos(M_PI*((time/10.0f)*90.0f)/180.0), 1.0f);
								}
							} else {
								time -= 10.0f;
								for(idx=0; idx<work->word_len; idx++) {
									HuSprTPLvlSet(work->spr_grp[1], idx, 1.0f);
									HuSprScaleSet(work->spr_grp[1], idx, sin(M_PI*((time/10.0f)*90.0f)/180.0), 1.0f);
								}
							}
						} else {
							if(work->time > 35 && work->time <= 55) {
								time = work->time-35;
								scale = 0.5*sin(((time*9.0f)*M_PI)/180.0);
								for(i=0; i<work->word_len; i++) {
									pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->word_len*56)*(scale+work->scale_x))))+((i*56)*(scale+work->scale_x));
									HuSprPosSet(work->spr_grp[1], i, pos_x, work->y);
									HuSprScaleSet(work->spr_grp[1], i, work->scale_x+scale, work->scale_y+scale);
								}
							}
						}
					}
					if(work->time == 35) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 55) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 75) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->state == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						time = work->time;
						scale = 0.5*sin(M_PI*(9.0f*time)/180.0);
						for(i=0; i<work->word_len; i++) {
							HuSprTPLvlSet(work->spr_grp[1], i, 1.0f);
							pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->word_len*56)*(scale+work->scale_x))))+((i*56)*(scale+work->scale_x));
							HuSprPosSet(work->spr_grp[1], i, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[1], i, work->scale_x+scale, work->scale_y+scale);
						}
					} else {
						if(work->time > 80 && work->time <= 160) {
							time = work->time-80;
							for(idx=0; idx<work->word_len; idx++) {
								scale = time-(idx*2);
								if(scale < 0 || scale > 15.0f) {
									continue;
								}
								HuSprScaleSet(work->spr_grp[1], idx, cos(M_PI*((scale/15.0f)*90.0f)/180.0), 1.0f);
							}
							for(idx=0; idx<work->alt_word_len; idx++) {
								scale = (time-15.0f)-(idx*2);
								if(scale < 0 || scale > 30.0f) {
									continue;
								}
								HuSprTPLvlSet(work->spr_grp[0], idx, 1.0f);
								HuSprScaleSet(work->spr_grp[0], idx, sin(M_PI*((scale/30.0f)*180.0f)/180.0), 1.0f);
							}
						}
					}
					if(work->time == 160) {
						work->stat |= 0x4;
					}
					if(work->time >= 160) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->angle += seqSpeed*0.1f;
				scale = 1.0f-work->angle;
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->state == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->word_len; idx++) {
					HuSprTPLvlSet(work->spr_grp[1], idx, scale);
				}
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static s32 SeqUpdateMGBowser(SeqWork *work)
{
	s16 idx;
	float scale;
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	if(work->type == 2) {
		return 1;
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->angle = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				s16 i;
				s16 j;
				float angle;
				float time_angle;
				float time;
				float pos_x, pos_y;
				
				float temp_f25;
				float center_x;
				s16 spr_idx[16];
				float scale_arr[16];
				
				
				if(work->state == 0) {
					if(work->time <= 60) {
						center_x = (0.5*(work->word_len*56))+20.0;
						for(idx=0; idx<work->word_len; idx++) {
							time = work->time-idx;
							if(time < 0) {
								scale_arr[idx] = 0.0f;
								spr_idx[idx] = idx;
							} else {
								if(time > 50.0f) {
									time = 50.0f;
								}
								time_angle = 540.0*(1.0f-(time/50.0f));
								pos_x = (28.0f+(0.5f*-(work->word_len*56)))+(idx*56);
								angle = 180.0*(atan2(pos_x, center_x)/M_PI);
								pos_x = work->x+(center_x*sin(M_PI*(angle+time_angle)/180.0));
								pos_y = work->y-(240.0*(1.0-(time/50.0f)));
								HuSprPosSet(work->spr_grp[0], idx, pos_x, pos_y);
								temp_f25 = 0.9+(0.1*cos(M_PI*(angle+time_angle)/180.0));
								HuSprScaleSet(work->spr_grp[0], idx, temp_f25*cos(M_PI*(angle+time_angle)/180.0), temp_f25);
								scale_arr[idx] = cos(M_PI*(angle+time_angle)/180.0);
								spr_idx[idx] = idx;
							}
						}
						for(i=1; i<work->word_len; i++) {
							for(idx=0; idx<work->word_len-i; idx++) {
								if(scale_arr[idx] > scale_arr[idx+1]) {
									 j= spr_idx[idx];
									spr_idx[idx] = spr_idx[idx+1];
									spr_idx[idx+1] = j;
									angle = scale_arr[idx];
									scale_arr[idx] = scale_arr[idx+1];
									scale_arr[idx+1] = angle;
								}
							}
						}
						for(idx=0; idx<work->word_len; idx++) {
							HuSprPriSet(work->spr_grp[0], spr_idx[idx], idx+5);
						}
					} else {
						if(work->time > 60 && work->time <= 80) {
							time = work->time-60;
							scale = 0.5*sin(((time*9.0f)*M_PI)/180.0);
							for(i=0; i<work->word_len; i++) {
								pos_x = (28.0f*(scale+work->scale_x))+(work->x-(0.5f*((work->word_len*56)*(scale+work->scale_x))))+((i*56)*(scale+work->scale_x));
								HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
								HuSprScaleSet(work->spr_grp[0], i, work->scale_x+scale, work->scale_y+scale);
							}
						}
						
					}
					if(work->time == 60) {
						HuAudFXPlay(36);
						work->stat |= 0x10;
					}
					if(work->time == 80) {
						work->stat |= 0x4;
						SeqPlayStartFX();
					}
					if(work->time >= 100) {
						work->type = 0;
					}
				} else {
					if(work->time == 1) {
						if(work->state == 1) {
							HuAudFXPlay(37);
						} else {
							HuAudFXPlay(40);
						}
						MGSeqPauseEnableCtrl(0);
						work->stat |= 0x10;
					}
					if(work->time <= 20) {
						for(j=1; j<4; j++) {
							for(i=0; i<work->word_len; i++) {
								HuSprAttrSet(work->spr_grp[j], i, HUSPR_ATTR_DISPOFF);
							}
						}
						time = work->time;
						scale = work->scale_x+(0.5*sin(((time*9.0f)*M_PI)/180.0));
						for(i=0; i<work->word_len; i++) {
							HuSprAttrReset(work->spr_grp[0], i, HUSPR_ATTR_DISPOFF);
							pos_x = ((28.0f*scale)+(work->x-(0.5f*(scale*(work->word_len*56)))))+(scale*(i*56));
							HuSprPosSet(work->spr_grp[0], i, pos_x, work->y);
							HuSprScaleSet(work->spr_grp[0], i, work->scale_x+(sin((M_PI*(time*9.0f))/180.0)), work->scale_y+(sin((M_PI*(time*9.0f))/180.0)));
						}
						if(time == 20.0f) {
							for(j=1; j<4; j++) {
								for(i=0; i<work->word_len; i++) {
									HuSprAttrReset(work->spr_grp[j], i, HUSPR_ATTR_DISPOFF);
								}
							}
						}
					} else {
						if(work->time > 80 && work->time <= 125) {
							static float letterOfs[] = {
								-30, -30,
								606, -30,
								340, 510,
								606, 510,
								-30, 450,
								606, 120,
								450, -30,
							};
							for(i=0; i<4; i++) {
								time = work->time-80-i;
								if(time < 0.0f || time > 15.0f) {
									continue;
								}
								for(idx=0; idx<work->word_len; idx++) {
									pos_x = (28.0f+(work->x-(0.5f*(work->word_len*56))))+(idx*56);
									pos_x += (time/15.0f)*(letterOfs[(idx*2)]-pos_x);
									pos_y = work->y+((time/15.0f)*(letterOfs[(idx*2)+1]-work->y));
									HuSprPosSet(work->spr_grp[i], idx, pos_x, pos_y);
								}
							}
						}
					}
					if(work->time == 125) {
						work->stat |= 0x4;
					}
					if(work->time >= 135) {
						work->type = 0;
						work->stat |= 0x8;
					}
				}
			}
			break;
			
			case -1:
			{
				work->angle += seqSpeed*0.1f;
				scale = 1.0f-work->angle;
				if(scale <= 0.0f) {
					scale = 0.0f;
					work->type = 0;
					work->stat |= 0x8;
					if(work->state == 0) {
						MGSeqPauseEnableCtrl(1);
					}
				}
				for(idx=0; idx<work->word_len; idx++) {
					HuSprTPLvlSet(work->spr_grp[0], idx, scale);
				}
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static s32 SeqInitDraw(SeqWork *work, va_list params)
{
	s16 word_grp;
	work->state = 2;
	work->seq_no = 13;
	work->type = 0;
	work->angle = 0.0f;
	{
		s32 word_flag;
		s32 word_ofs;

		if(seqLanguage == 0) {
			word_flag = 1;
		} else {
			word_flag = 0;
		}
		if(seqLanguage == 0) {
			word_ofs = 0;
		} else {
			word_ofs = 3;
		}
		
		word_grp = SeqMakeWord(work, wordMgTbl[2+word_ofs], word_flag);
	}
	HuSprGrpPosSet(work->spr_grp[word_grp], 288.0f, 240.0f);
	work->param[0] = 3;
	return 1;
}

static s32 SeqUpdateDraw(SeqWork *work)
{
	s16 idx;
	float scale;
	s16 group = work->spr_grp[0];
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->angle = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float time;
				float scale;
				float zrot;
				if(work->time <= 20) {
					time = work->time;
					zrot = 365.0f*(time/20.0f);
					scale = 1.3f*sin(M_PI*(90.0f*(time/20.0f))/180.0);
					HuSprGrpScaleSet(group, scale, scale);
					HuSprGrpZRotSet(group, zrot);
				}
				if(work->time > 20 && work->time <= 25) {
					HuSprGrpZRotSet(group, 0.0f);
					time = work->time-20;
					scale = 1.0+(0.3*cos(M_PI*(90.0f*(time/5.0f))/180.0));
					HuSprGrpScaleSet(group, scale, scale);
				}
				if(work->time == 5) {
					HuAudFXPlay(40);
				}
				if(work->time == 60) {
					work->type = 0;
				}
			}
			break;
			
			case -1:
			{
				float tp_lvl;
				work->angle += seqSpeed*0.1f;
				tp_lvl = 1.0f-work->angle;
				if(tp_lvl <= 0.0f) {
					tp_lvl = 0.0f;
					work->state = 0;
					work->stat |= 0x8;
				}
				HuSprGrpTPLvlSet(group, tp_lvl);
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static char *winCharNameTbl[] = {
	"ﾏﾘｵ",
	"MARIO",
	"ﾙｲｰｼﾞ",
	"LUIGI",
	"ﾋﾟｰﾁ",
	"PEACH",
	"ﾖｯｼｰ",
	"YOSHI",
	"ﾜﾘｵ",
	"WARIO",
	"ﾄﾞﾝｷｰ",
	" DK ",
	"ﾃﾞｲｼﾞｰ",
	"DAISY",
	"ﾜﾙｲｰｼﾞ",
	"WALUIGI",
	"ｸｯﾊﾟ",
	"BOWSER",
	"ｷﾉﾋﾟｵ",
	"TOAD",
	"ﾍｲﾎｰ",
	"SHY GUY",
	"ﾃﾚｻ",
	"BOO",
	"ﾉｺﾉｺ",
	"KOOPA",
	"ﾐﾆｸｯﾊﾟ",
	"KOOPA KID",
	"ｸﾘﾎﾞｰ",
	"GOOMBA"
};

static char *winWordTbl[] = {
	"ｶﾁ",
	"WON!",
	"ﾊｲﾎﾞｸ",
	"LOSE",
	"ﾕｳｼｮｳ!",
	"CHAMPION!"
};

static s16 winPosOfs[][5][2] = {
	{
		{ 114, 0 },
		{ -144, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 }
	},
	{
		{ 0, 35 },
		{ -144, -35 },
		{ 144, -35 },
		{ 0, 0 },
		{ 0, 0 }
	},
	{
		{ 0, 105 },
		{ 0, -105 },
		{ -144, 0 },
		{ 144, 0 },
		{ 0, 0 }
	},
	{
		{ 0, 105 },
		{ -144, -105 },
		{ 144, -105 },
		{ -144, 0 },
		{ 144, 0 }
	}
};

static s16 winnerNameW[8];

#define GET_LANG_IDX() ((seqLanguage == 0) ? 0 : 1)
#define GET_WIN_KANAF() ((seqLanguage == 0) ? 1 : 0)


static s32 SeqInitWin(SeqWork *work, va_list params)
{
	int win_type = va_arg(params, int);
	s16 word_idx;
	s16 word_grp;
	s32 i;
	s32 j;
	s32 num_winners;
	float word_w;
	float word_x;
	if(win_type < 0 && win_type >= 6) {
		return 0;
	}
	if(win_type == 3) {
		word_idx = GET_LANG_IDX();
	} else {
		if(win_type == 4) {
			word_idx = GET_LANG_IDX()+2;
		} else {
			word_idx = GET_LANG_IDX()+4;
		}
	}
	word_grp = SeqMakeWord(work, winWordTbl[word_idx], GET_WIN_KANAF());
	winnerNameW[0] = work->word_len*50;
	for(i=0; i<work->word_len; i++) {
		HuSprPosSet(work->spr_grp[word_grp], i, 25.0f+((i*50)-(0.5f*(work->word_len*50))), 0.0f);
		HuSprAttrSet(work->spr_grp[word_grp], i, HUSPR_ATTR_LINEAR);
	}
	num_winners = 0;
	work->win_scale = 1.0f;
	for(j=0; j<4; j++) {
		int winner = va_arg(params, int);
		if(winner < 0) {
			continue;
		}
		word_grp = SeqMakeWord(work, winCharNameTbl[(winner*2)+GET_LANG_IDX()], 0);
		if(seqLanguage != 0) {
			char *name = winCharNameTbl[(winner*2)+GET_LANG_IDX()];
			word_w = 0.0f;
			for(i=word_w; i<work->word_len; i++, name++) {
				if(*name == ' ') {
					word_w += 30.0f;
				} else {
					word_w += 50.0f;
				}
			}
			name = winCharNameTbl[(winner*2)+GET_LANG_IDX()];
			word_x = 0.0f;
			for(i=word_x; i<work->word_len; i++, name++) {
				HuSprPosSet(work->spr_grp[word_grp], i, 25.0+(word_x-(0.5*word_w)), 0.0f);
				HuSprAttrSet(work->spr_grp[word_grp], i, HUSPR_ATTR_LINEAR);
				if(*name == ' ') {
					word_x += 30.0f;
				} else {
					word_x += 50.0f;
				}
			}
			if(work->win_scale == 0.6f || winner == 7 || winner == 13 || winner == 10) {
				work->win_scale = 0.6f;
			} else {
				work->win_scale = 0.75f;
			}
			winnerNameW[num_winners+1] = word_w;
		} else {
			if(winner == 7 || winner == 13) {
				for(i=0;i<work->word_len; i++) {
					HuSprPosSet(work->spr_grp[word_grp], i, 26.0f+((i*52)-(0.5f*(work->word_len*52))), 0.0f);
					HuSprAttrSet(work->spr_grp[word_grp], i, HUSPR_ATTR_LINEAR);
				}
				work->win_scale = 0.8f;
				winnerNameW[num_winners+1] = work->word_len*52;
			} else {
				work->win_scale = 1.0f;
				winnerNameW[num_winners+1] = work->word_len*56;
			}
			
		}
		num_winners++;
	}
	if(num_winners == 0) {
		return 0;
	}
	work->state = 0;
	work->word_len = num_winners+1;
	work->angle = 0.0f;
	work->type = 0;
	for(j=0; j<num_winners+1; j++) {
		if(num_winners == 1) {
			word_x = 32.0f+((float)winnerNameW[0]+(winnerNameW[1]*work->win_scale));
			if(j == 0) {
				word_x = (((576.0f-word_x)/2.0f)+(word_x-(winnerNameW[0]/2)))-288.0f;
			} else {
				word_x = (((576.0f-word_x)/2.0f)+(winnerNameW[1]/2))-288.0f;
			}
		} else {
			if(abs(winPosOfs[num_winners-1][j][0]) == 144.0f) {
				if(winnerNameW[j]+32 < 288.0f) {
					word_x = 176.0f;
				} else {
					word_x = 32.0f+((winnerNameW[j]*work->win_scale)/2.0f);
				}
				if(winPosOfs[num_winners-1][j][0] < 0) {
					word_x = -(288.0f-word_x);
				} else {
					word_x = (576.0f-word_x)-288.0f;
				}
			} else {
				word_x = winPosOfs[num_winners-1][j][0];
			}
		}
		HuSprGrpPosSet(work->spr_grp[j], 288.0f+word_x, 240.0f+winPosOfs[num_winners-1][j][1]);
	}
	if(seqPauseF) {
		work->type = 1;
		num_winners++;
		for(j=0; j<num_winners; j++) {
			HuSprAttrSet(work->spr_grp[j], 0, HUSPR_ATTR_DISPOFF);
		}
	} else {
		work->param[0] = 3;
	}
	return 1;
}


static s32 SeqUpdateWin(SeqWork *work)
{
	s32 idx;
	float tp_lvl;
	s16 group = work->spr_grp[0];
	if(work->param[0] != 0 && work->type != -1) {
		switch(work->param[0]) {
			case 2:
				if(work->param[1] != -1) {
					(void)work; //HACK: to introduce extra branch
				} else {
					work->type = -1;
					work->angle = 0.0f;
				}
				work->param[0] = 0;
				break;
				
			case 1:
				work->time_max = work->param[1];
				work->param[0] = 0;
				break;
				
			case 3:
				work->type = 1;
				work->param[0] = 0;
				break;
				
			default:
				work->param[0] = 0;
				break;
		}
	}
	work->time += seqSpeed;
	if(work->time >= work->time_max && work->type != -1) {
		work->stat |= 0x4;
		work->type = -1;
		work->angle = 0.0f;
	}
	if(work->type) {
		switch(work->type) {
			case 1:
			{
				float time;
				float scale;
				float zrot;
				if(work->time <= 20) {
					time = work->time;
					zrot = 365.0f*(time/20.0f);
					scale = sin(M_PI*(90.0f*(time/20.0f))/180.0);
					HuSprGrpScaleSet(work->spr_grp[0], scale, scale);
					HuSprGrpZRotSet(work->spr_grp[0], zrot);
					scale = 1.0+(5.0*cos(M_PI*(90.0f*(time/20.0f))/180.0));
					tp_lvl = time/20.0f;
					for(idx=1; idx<work->word_len; idx++) {
						HuSprGrpTPLvlSet(work->spr_grp[idx], tp_lvl);
						HuSprGrpScaleSet(work->spr_grp[idx], scale*work->win_scale, scale);
					}
				}
				if(work->time > 20 && work->time <= 22) {
					HuSprGrpZRotSet(work->spr_grp[0], 0.0f);
					for(idx=1; idx<work->word_len; idx++) {
						float pos_x;
						float ofs[2];
						if(work->time == 21) {
							ofs[0] = ((idx & 0x1)*2)-1;
							ofs[1] = (idx & 0x2) ? 2 : -1;
						} else {
							ofs[0] = ofs[1] = 0.0f;
						}
						if(work->word_len == 2) {
							pos_x = winnerNameW[1]+winnerNameW[0]+32;
							pos_x = (((576.0f-pos_x)/2.0f)+(winnerNameW[1]/2))-288.0f;
						} else {
							if(abs(winPosOfs[work->word_len-2][idx][0]) == 144.0f) {
								if(winnerNameW[idx]+32 < 288.0f) {
									pos_x = 176.0f;
								} else {
									pos_x = 32.0f+((winnerNameW[idx]*work->win_scale)/2.0f);
								}
								if(winPosOfs[work->word_len-2][idx][0] < 0) {
									pos_x = -(288.0f-pos_x);
								} else {
									pos_x = (576.0f-pos_x)-288.0f;
								}
							} else {
								pos_x = winPosOfs[work->word_len-2][idx][0];
							}
						}
						HuSprGrpPosSet(work->spr_grp[idx], (288.0f+pos_x)+ofs[0], ofs[1]+(240.0f+winPosOfs[work->word_len-2][idx][1]));
					}
				}
				if(work->time == 125) {
					work->type = 0;
				}
			}
			break;
			
			case -1:
			{
				work->angle += seqSpeed*0.1f;
				tp_lvl = 1.0f-work->angle;
				if(tp_lvl <= 0.0f) {
					tp_lvl = 0.0f;
					work->state = 0;
					work->stat |= 0x8;
				}
				for(idx=0; idx<work->word_len; idx++) {
					HuSprGrpTPLvlSet(work->spr_grp[idx], tp_lvl);
				}
			}
			break;
			
			default:
				break;
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static s32 SeqInitRecord(SeqWork *work, va_list params)
{
	AnimData *spr_data;
	s16 spr_grp;
	s16 time_pos[2];
	s16 i;
	s16 sprite;
	s16 digit_idx;
	s32 digit;
	seqRecordVal = va_arg(params, int);
	work->type = 0;
	work->angle = 0.0f;
	work->spr_grp[0] = spr_grp = HuSprGrpCreate(10);
	spr_data = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 9)));
	sprite = HuSprCreate(spr_data, 0, 0);
	HuSprGrpMemberSet(spr_grp, 0, sprite);
	HuSprPosSet(spr_grp, 0, 0.0f, -32.0f);
	spr_data = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 8)));
	sprite = HuSprCreate(spr_data, 0, 0);
	HuSprGrpMemberSet(spr_grp, 1, sprite);
	spr_data = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 7)));
	for(i=0; i<8; i++) {
		sprite = HuSprCreate(spr_data, 0, 0);
		HuSprGrpMemberSet(spr_grp, i+2, sprite);
	}
	if(omcurovl == OVL_M407 || omcurovl == OVL_M453 || omcurovl == OVL_M459 || omcurovl == OVL_M460 || omcurovl == OVL_M462 || omcurovl == OVL_M442) {
		digit_idx = 0;
		if(seqRecordVal > 9999) {
			seqRecordVal = 9999;
		}
		digit = seqRecordVal/1000;
		if(digit != 0) {
			HuSprBankSet(spr_grp, digit_idx+2, digit);
			seqRecordVal -= digit*1000;
			digit_idx++;
		}
		
		digit = seqRecordVal/100;
		if(digit != 0 || digit_idx != 0) {
			HuSprBankSet(spr_grp, digit_idx+2, digit);
			seqRecordVal -= digit*100;
			digit_idx++;
		}
		digit = seqRecordVal/10;
		if(digit != 0 || digit_idx != 0) {
			HuSprBankSet(spr_grp, digit_idx+2, digit);
			seqRecordVal -= digit*10;
			digit_idx++;
		}
		HuSprBankSet(spr_grp, digit_idx+2, seqRecordVal);
		digit_idx++;
		for(i=digit_idx; i<8; i++) {
			HuSprAttrSet(spr_grp, i+2, HUSPR_ATTR_DISPOFF);
		}
		HuSprPosSet(spr_grp, 1, (-((digit_idx*44)+48)/2)+24, 32.0f);
		for(i=0; i<digit_idx; i++) {
			HuSprPosSet(spr_grp, i+2, (-((digit_idx*44)+48)/2)+70+(i*44), 32.0f);
		}
	} else {
		s16 x;
		digit_idx = 0;
		digit = seqRecordVal/36000;
		if(digit != 0) {
			HuSprBankSet(spr_grp, digit_idx+2, digit);
			seqRecordVal -= digit*36000;
			digit_idx++;
		}
		digit = seqRecordVal/3600;
		HuSprBankSet(spr_grp, digit_idx+2, digit);
		seqRecordVal -= digit*3600;
		digit_idx++;
		HuSprBankSet(spr_grp, digit_idx+2, 10);
		time_pos[0] = digit_idx;
		digit_idx++;
		digit = seqRecordVal/600;
		HuSprBankSet(spr_grp, digit_idx+2, digit);
		seqRecordVal -= digit*600;
		digit_idx++;
		digit = seqRecordVal/60;
		HuSprBankSet(spr_grp, digit_idx+2, digit);
		seqRecordVal -= digit*60;
		digit_idx++;
		HuSprBankSet(spr_grp, digit_idx+2, 11);
		time_pos[1] = digit_idx;
		digit_idx++;
		if(omcurovl == OVL_M405 || omcurovl == OVL_M432 || omcurovl == OVL_M461) {
			seqRecordVal = (float)seqRecordVal*(203.0/120.0);
		} else {
			seqRecordVal = (float)seqRecordVal*(200.0/120.0);
		}
		digit = seqRecordVal/10;
		HuSprBankSet(spr_grp, digit_idx+2, digit);
		seqRecordVal -= digit*10;
		digit_idx++;
		HuSprBankSet(spr_grp, digit_idx+2, seqRecordVal);
		digit_idx++;
		for(i=digit_idx; i<8; i++) {
			HuSprAttrSet(spr_grp, i+2, HUSPR_ATTR_DISPOFF);
		}
		HuSprPosSet(spr_grp, 1, (-((digit_idx*44)+4)/2)+24, 32.0f);
		x = (-((digit_idx*44)+4)/2)+70;
		for(i=0; i<digit_idx; i++) {
			HuSprPosSet(spr_grp, i+2, x, 32.0f);
			if(time_pos[0] == i || time_pos[1] == i) {
				x += 22;
			} else {
				x += 44;
			}
		}
	}
	HuSprGrpPosSet(spr_grp, 288.0f, 240.0f);
	work->param[0] = 3;
	return 1;
}

static s32 SeqUpdateRecord(SeqWork *work)
{
	s16 group;
	if(_CheckFlag(FLAG_ID_MAKE(1, 12))) {
		work->state = 0;
		work->stat |= 0xC;
	} else {
		group = work->spr_grp[0];
		if(work->param[0] != 0 && work->type != -1) {
			switch(work->param[0]) {
				case 2:
					if(work->param[1] != -1) {
						(void)work; //HACK: to introduce extra branch
					} else {
						work->type = -1;
						work->angle = 0.0f;
					}
					work->param[0] = 0;
					break;
					
				case 1:
					work->time_max = work->param[1];
					work->param[0] = 0;
					break;
					
				case 3:
					work->type = 1;
					work->param[0] = 0;
					break;
					
				default:
					work->param[0] = 0;
					break;
			}
		}
		work->time += seqSpeed;
		if(work->time >= work->time_max && work->type != -1) {
			work->stat |= 0x4;
			work->type = -1;
			work->angle = 0.0f;
		}
		if(work->type) {
			switch(work->type) {
				case 1:
				{
					if(work->time <= 10) {
						HuSprGrpTPLvlSet(group, work->time/10.0);
					}
					if(work->time == 5) {
						HuAudFXPlay(38);
					}
					if(work->time == 30) {
						work->type = 0;
					}
				}
				break;
				
				case -1:
				{
					float tp_lvl;
					work->angle += seqSpeed*0.1f;
					tp_lvl = 1.0f-work->angle;
					if(tp_lvl <= 0.0f) {
						tp_lvl = 0.0f;
						work->state = 0;
						work->stat |= 0x8;
					}
					HuSprGrpTPLvlSet(group, tp_lvl);
				}
				break;
				
				default:
					break;
			}
		}
	}
	if(seqDoneF || (work->stat & 0x8)) {
		MGSeqSprKill(work);
		return 0;
	}
	return 1;
}

static void PauseProc(void);

void MGSeqPauseInit(void)
{
	MGSeqPauseEnableCtrl(0);
	HuWinInit(1);
	pauseProcess = HuPrcCreate(PauseProc, 100, 4096, 0);
	HuPrcSetStat(pauseProcess, PROCESS_STAT_PAUSE_EN|PROCESS_STAT_UPAUSE_EN);
	pauseActiveF = 1;
	pauseExitF = 0;
	pauseWaitF = 0;
}

static void PauseProc(void)
{
	s16 mg;
	s16 i;
	s16 j;
	
	s16 char_mess_map[4];
	s16 char_mess[4][4];
	s16 window[3] = { -1, -1, -1 };
	
	SeqWork work;
	static char *pauseStr[] = {
		"ﾎﾟｰｽﾞ",
		"PAUSE"
	};
	float ratio;
	
	HuAudFXPlay(5);
	for(i=0; i<16; i++) {
		work.sprite[i] = work.spr_grp[i] = -1;
	}
	SeqMakeWord(&work, pauseStr[GET_LANG_IDX()], 0);
	for(i=0; i<work.word_len; i++) {
		HuSprPriSet(work.spr_grp[0], i, 0);
	}
	for(i=0; i<4; i++) {
		char_mess_map[i] = 0;
	}
	for(i=0; i<4; i++) {
		char_mess[GWPlayerCfg[i].group][char_mess_map[GWPlayerCfg[i].group]] = GWPlayerCfg[i].character;
		char_mess_map[GWPlayerCfg[i].group]++;
	}
	mg = omMgIndexGet(omcurovl);
	if(mgInfoTbl[mg].inst_mess[1] == 0 && mgInfoTbl[mg].inst_mess[2] == 0) {
		for(i=1; i<=20; i++) {
			ratio = sin(M_PI*(i*4.5f)/180.0);
			HuSprGrpPosSet(work.spr_grp[0], 288.0f, (ratio*290)-50.0f);
			HuPrcVSleep();
		}
	} else {
		if(mgPracticeEnableF && !_CheckFlag(FLAG_ID_MAKE(1, 12))) {
			window[2] = HuWinExCreateStyled(-10000.0f, 400.0f, 412, 42, -1, 0);
			HuWinPriSet(window[2], 0);
			HuWinDispOn(window[2]);
			HuWinMesSpeedSet(window[2], 0);
			HuWinAttrSet(window[2], 0x800);
			HuWinMesSet(window[2], MAKE_MESSID(0x33, 0xA1));
		}
		if(mgInfoTbl[mg].inst_mess[2]) {
			s16 insert_idx;
			window[0] = HuWinExCreateStyled(-10000.0f, 140.0f, 412, 120, -1, 0);
			HuWinPriSet(window[0], 0);
			HuWinDispOn(window[0]);
			HuWinMesSpeedSet(window[0], 0);
			HuWinMesSet(window[0], mgInfoTbl[mg].inst_mess[1]);
			window[1] = HuWinExCreateStyled(-10000.0f, 276.0f, 412, 120, -1, 0);
			HuWinPriSet(window[1], 0);
			HuWinDispOn(window[1]);
			HuWinMesSpeedSet(window[1], 0);
			HuWinMesSet(window[1], mgInfoTbl[mg].inst_mess[2]);
			for(i=insert_idx=0; i<4; i++) {
				for(j=0; j<char_mess_map[i]; j++) {
					HuWinInsertMesSet(window[0], char_mess[i][j], (s16)insert_idx);
					HuWinInsertMesSet(window[1], char_mess[i][j], (s16)insert_idx);
					insert_idx++;
				}
			}
			for(i=1; i<=20; i++) {
				ratio = sin(M_PI*(i*4.5f)/180.0);
				HuSprGrpPosSet(work.spr_grp[0], 288.0f, (ratio*150)-50.0f);
				HuWinPosSet(window[0], (482*ratio)-400, 140);
				HuWinPosSet(window[1], 400+(ratio*-318), 272);
				if(window[2] != -1) {
					HuWinPosSet(window[2], 82, 404+(100*(1.0-ratio)));
				}
				HuPrcVSleep();
			}
		} else {
			window[0] = HuWinExCreateStyled(-10000.0f, 170.0f, 412, 120, -1, 0);
			HuWinPriSet(window[0], 0);
			HuWinDispOn(window[0]);
			HuWinMesSpeedSet(window[0], 0);
			HuWinMesSet(window[0], mgInfoTbl[mg].inst_mess[1]);
			for(i=1; i<=20; i++) {
				ratio = sin(M_PI*(i*4.5f)/180.0);
				HuSprGrpPosSet(work.spr_grp[0], 288.0f, (ratio*150)-50.0f);
				HuWinPosSet(window[0], (482*ratio)-400, 170);
				if(window[2] != -1) {
					HuWinPosSet(window[2], 400+(ratio*-318), 404);
				}
				HuPrcVSleep();
			}
		}
	}
	MGSeqPauseEnableCtrl(1);
	pauseWaitF = 1;
	while(!pauseExitF) {
		HuPrcVSleep();
	}
	pauseWaitF = 0;
	if(window[0] == -1 && window[1] == -1) {
		for(i=1; i<=10; i++) {
			ratio = cos(M_PI*(i*9.0f)/180.0);
			HuSprGrpPosSet(work.spr_grp[0], 288.0f, (ratio*290)-50.0f);
			HuPrcVSleep();
		}
	} else {
		if(window[1] != -1) {
			for(i=1; i<=10; i++) {
				ratio = cos(M_PI*(i*9.0f)/180.0);
				HuSprGrpPosSet(work.spr_grp[0], 288.0f, (ratio*150)-50.0f);
				HuWinPosSet(window[0], (482*ratio)-400, 140);
				HuWinPosSet(window[1], 400+(ratio*-318), 272);
				if(window[2] != -1) {
					HuWinPosSet(window[2], 82, 404+(100*(1.0-ratio)));
				}
				HuPrcVSleep();
			}
		} else {
			for(i=1; i<=10; i++) {
				ratio = cos(M_PI*(i*9.0f)/180.0);
				HuSprGrpPosSet(work.spr_grp[0], 288.0f, (ratio*150)-50.0f);
				HuWinPosSet(window[0], (482*ratio)-400, 170);
				if(window[2] != -1) {
					HuWinPosSet(window[2], 400+(ratio*-318), 404);
				}
				HuPrcVSleep();
			}
		}
	}
	omSysPauseCtrl(0);
	if(window[0] != -1) {
		HuWinKill(window[0]);
	}
	if(window[1] != -1) {
		HuWinKill(window[1]);
	}
	if(window[2] != -1) {
		HuWinKill(window[2]);
	}
	HuSprGrpKill(work.spr_grp[0]);
	pauseProcess = NULL;
	pauseActiveF = 0;
	HuPrcEnd();
	do {
		HuPrcVSleep();
	} while(1);
}

void MGSeqPauseKill(void)
{
	pauseExitF = 1;
}

void MGSeqPauseEnableCtrl(s32 flag)
{
	if(!_CheckFlag(FLAG_ID_MAKE(1, 8))) {
		omSysPauseEnable(flag);
	}
}

static void PracticeProc(void);

static s16 practiceTbl[][2] = {
	OVL_M401, 1,
	OVL_M402, 1,
	OVL_M403, 1,
	OVL_M405, 1,
	OVL_M406, 0,
	OVL_M407, 1,
	OVL_M408, 0,
	OVL_M409, 0,
	OVL_M410, 1,
	OVL_M411, 2,
	OVL_M412, 1,
	OVL_M413, 0,
	OVL_M414, 2,
	OVL_M415, 1,
	OVL_M443, 2,
	OVL_M416, 1,
	OVL_M417, 1,
	OVL_M418, 1,
	OVL_M419, 1,
	OVL_M420, 1,
	OVL_M421, 1,
	OVL_M422, 1,
	OVL_M423, 1,
	OVL_M424, 1,
	OVL_M425, 1,
	OVL_M426, 1,
	OVL_M427, 0,
	OVL_M428, 0,
	OVL_M429, 2,
	OVL_M430, 1,
	OVL_M431, 1,
	OVL_M432, 1,
	OVL_M433, 0,
	OVL_M434, 1,
	OVL_M404, 0,
	OVL_M438, 1,
	OVL_M439, 2,
	OVL_M440, 1,
	OVL_M441, 1,
	OVL_M442, 1,
	OVL_M455, 0,
	OVL_M456, 0,
	OVL_INVALID, 0,
};

void MGSeqPracticeInit(void)
{
	Process *process;
	s16 i;
	process = HuPrcCurrentGet();
	if(!_CheckFlag(FLAG_ID_MAKE(1, 12))) {
		return;
	}
	wipeFadeInF = 0;
	for(i=0; practiceTbl[i][0] != OVL_INVALID; i++) {
		if(omcurovl == practiceTbl[i][0]) {
			break;
		}
	}
	if(practiceTbl[i][0] != -1) {
		HuPrcChildCreate(PracticeProc, 10, 8192, 0, process);
	}
}

static void PracticeProc(void)
{
	
	s16 group;
	s16 sprite;
	AnimData *anim;
	s16 i;
	s16 *practice;
	float time;
	static float yPosTbl[] = {
		53,
		424,
		240
	};
	time = 0.0f;
	for(i=0; practiceTbl[i][0] != OVL_INVALID; i++) {
		if(omcurovl == practiceTbl[i][0]) {
			break;
		}
	}
	practice = &practiceTbl[i][0];
	group = HuSprGrpCreate(1);
	HuSprGrpPosSet(group, 0, 0);
	anim = HuSprAnimRead(SeqReadFile(DATA_MAKE_NUM(DATADIR_GAMEMES, 5)));
	sprite = HuSprCreate(anim, 1, 0);
	HuSprGrpMemberSet(group, 0, sprite);
	HuSprPosSet(group, 0, 288.0f, yPosTbl[practice[1]]);
	do {
		if(!wipeFadeInF || WipeStatGet()) {
			HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
			HuPrcVSleep();
			continue;
		}
		HuSprAttrReset(group, 0, HUSPR_ATTR_DISPOFF);
		for(i=0; i<4; i++) {
			if(!(HuPadBtnDown[GWPlayerCfg[i].pad_idx] & PAD_TRIGGER_Z)) {
				continue;;
			}
			if(!GWPlayerCfg[i].iscom) {
				break;
			}
		}
		if(i != 4) {
			break;
		}
		HuSprTPLvlSet(group, 0, fabs(sin(M_PI*time/180.0)));
		time += 2.0f;
		HuPrcVSleep();
	} while(1);
	omSysExitReq = 1;
	HuPrcEnd();
	do {
		HuPrcVSleep();
	} while(1);
}

static s16 seqStartFXTbl[][2] = {
	OVL_M401, 17,
	OVL_M402, 16,
	OVL_M403, 12,
	OVL_M404, 12,
	OVL_M405, 17,
	OVL_M406, 12,
	OVL_M407, 16,
	OVL_M408, 12,
	OVL_M409, 16,
	OVL_M410, 12,
	OVL_M411, 16,
	OVL_M412, 12,
	OVL_M413, 16,
	OVL_M414, 16,
	OVL_M415, 16,
	OVL_M416, 16,
	OVL_M417, 17,
	OVL_M418, 16,
	OVL_M419, 16,
	OVL_M420, 16,
	OVL_M421, 16,
	OVL_M422, 12,
	OVL_M423, 12,
	OVL_M424, 16,
	OVL_M425, 16,
	OVL_M426, 16,
	OVL_M427, 12,
	OVL_M428, 12,
	OVL_M429, 16,
	OVL_M430, 12,
	OVL_M431, 16,
	OVL_M432, 12,
	OVL_M433, 12,
	OVL_M434, 16,
	OVL_M435, 12,
	OVL_M436, 16,
	OVL_M437, 12,
	OVL_M438, 16,
	OVL_M439, 12,
	OVL_M440, 16,
	OVL_M441, 16,
	OVL_M442, 16,
	OVL_M443, -1,
	OVL_M444, -1,
	OVL_M445, 12,
	OVL_M446, -1,
	OVL_M447, 12,
	OVL_M448, -1,
	OVL_M449, 16,
	OVL_M450, 12,
	OVL_M455, 17,
	OVL_M456, 17,
	OVL_M457, 12,
	OVL_M458, 12,
	OVL_M459, 17,
	OVL_M460, 12,
	OVL_M461, 12,
	OVL_M462, 12,
	OVL_INVALID, 0
};

static void SeqPlayStartFX(void)
{
	s16 i;
	for(i=0; seqStartFXTbl[i][0] != OVL_INVALID; i++) {
		if(omcurovl == seqStartFXTbl[i][0]) {
			break;
		}
	}
	if(seqStartFXTbl[i][0] == OVL_INVALID || seqStartFXTbl[i][1] == -1) {
		return;
	}
	HuAudFXPlay(seqStartFXTbl[i][1]);
}

void MGSeqPracticeExitCheck(omObjData *object)
{
	s16 input;
	s16 i;
	mgQuitExtraF = 0;
	if(object->work[0] == 0) {
		if(omMgIndexGet(omcurovl) == -1) {
			omDelObjEx(HuPrcCurrentGet(), object);
			return;
		}
		object->work[0]++;
	}
	if(!omPauseChk() || _CheckFlag(FLAG_ID_MAKE(1, 12)) || !pauseWaitF) {
		return;
	}
	for(i=input=0; i<4; i++) {
		input |= HuPadBtnDown[i];
	}
	if(input & PAD_TRIGGER_Z) {
		HuAudFXPlay(3);
		pauseExitF = 1;
		omSysPauseCtrl(0);
		omSysExitReq = 1;
		mgQuitExtraF = 1;
		omDelObjEx(HuPrcCurrentGet(), object);
	}
}
