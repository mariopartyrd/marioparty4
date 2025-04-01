#ifndef _GAME_MINIGAME_SEQ_H
#define _GAME_MINIGAME_SEQ_H

#include "game/object.h"
#include "stdarg.h"

#define MG_SEQ_TYPE_TIMER 1
#define MG_SEQ_TYPE_AUTO 3
#define MG_SEQ_TYPE_1VS3 4
#define MG_SEQ_TYPE_WIN 5
#define MG_SEQ_TYPE_BATTLE 6
#define MG_SEQ_TYPE_STORY 7
#define MG_SEQ_TYPE_4P 8
#define MG_SEQ_TYPE_2VS2 9
#define MG_SEQ_TYPE_PINBALL 10
#define MG_SEQ_TYPE_BOWSER 11
#define MG_SEQ_TYPE_ALTWIN 12
#define MG_SEQ_TYPE_DRAW 13
#define MG_SEQ_TYPE_RECORD 14

#define MG_SEQ_WIN_TYPE_WIN 3
#define MG_SEQ_WIN_TYPE_LOSE 4
#define MG_SEQ_WIN_TYPE_CHAMPION 5

#define MG_SEQ_WORD_START 0
#define MG_SEQ_WORD_FINISH 1
#define MG_SEQ_WORD_DRAW 2

#define MGSeqTimerCreate(value) MGSeqCreate(MG_SEQ_TYPE_TIMER, (value), -1, -1)
#define MGSeqTimerCreateXY(value, x, y) MGSeqCreate(MG_SEQ_TYPE_TIMER, (value), (int)(x), (int)(y))
#define MGSeqStartCreate() MGSeqCreate(MG_SEQ_TYPE_AUTO, MG_SEQ_WORD_START)
#define MGSeqFinishCreate() MGSeqCreate(MG_SEQ_TYPE_AUTO, MG_SEQ_WORD_FINISH)
#define MGSeqDrawCreate() MGSeqCreate(MG_SEQ_TYPE_AUTO, MG_SEQ_WORD_DRAW)
#define MGSeqStartCreateType(type) MGSeqCreate((type), MG_SEQ_WORD_START)
#define MGSeqFinishCreateType(type) MGSeqCreate((type), MG_SEQ_WORD_FINISH)
#define MGSeqDrawCreateType(type) MGSeqCreate((type), MG_SEQ_WORD_DRAW)
#define MGSeqWinCreate(player_1, player_2, player_3, player_4) MGSeqCreate(MG_SEQ_TYPE_WIN, MG_SEQ_WIN_TYPE_WIN, (player_1), (player_2), (player_3), (player_4))
#define MGSeqLoseCreate(player_1, player_2, player_3, player_4) MGSeqCreate(MG_SEQ_TYPE_WIN, MG_SEQ_WIN_TYPE_LOSE, (player_1), (player_2), (player_3), (player_4))
#define MGSeqChampionCreate(player_1, player_2, player_3, player_4) MGSeqCreate(MG_SEQ_TYPE_ALTWIN, MG_SEQ_WIN_TYPE_CHAMPION, (player_1), (player_2), (player_3), (player_4))
#define MGSeqAltWinCreate(player_1, player_2, player_3, player_4) MGSeqCreate(MG_SEQ_TYPE_ALTWIN, MG_SEQ_WIN_TYPE_WIN, (player_1), (player_2), (player_3), (player_4))

#define MGSeqRecordCreate(value) MGSeqCreate(MG_SEQ_TYPE_RECORD, (value))



typedef struct seq_work SeqWork;

typedef s32 (*SeqUpdateFunc)(SeqWork *work);
typedef s32 (*SeqInitFunc)(SeqWork *work, va_list params);

struct seq_work {
	SeqUpdateFunc update;
	char *data;
	float x;
	float y;
	float scale_x;
	float scale_y;
	float unk_18;
	float angle;
	float win_scale;
	float unk_24;
	s16 time;
	s16 time_max;
	s16 timer_val;
	s16 state;
	s16 alt_word_len;
	s16 word_len;
	s16 param[2];
	s16 type;
	s16 spr_grp[16];
	s16 sprite[16];
	u8 seq_no;
	u8 stat;
	u8 unk_7C;
	u8 unk_7D;
};

void MGSeqInit(void);
void MGSeqMain(void);
s16 MGSeqCreate(s16 type, ...);
u8 MGSeqStatGet(s16 id);
void MGSeqPosSet(s16 id, float x, float y);
void MGSeqParamSet(s16 id, s16 param1, s16 param2);
void MGSeqSprKill(SeqWork *work);
void MGSeqKill(s16 id);
void MGSeqKillAll(void);
s32 MGSeqDoneCheck(void);
void MGSeqStub(void);
void MGSeqPauseInit(void);
void MGSeqPauseEnableCtrl(s32 flag);
void MGSeqPracticeInit(void);
void MGSeqPracticeExitCheck(omObjData *object);

s32 MGSeqInitTimer(SeqWork *work, va_list params);
s32 MGSeqUpdateTimer(SeqWork *work);

s32 MGSeqInitType2(SeqWork *work, va_list params);
s32 MGSeqUpdateType2(SeqWork *work);

s32 MGSeqUpdateMGBattle(SeqWork *work);

s32 MGSeqInitMGBasic(SeqWork *work, va_list params);
s32 MGSeqUpdateMGBasic(SeqWork *work);
s32 MGSeqInitMGCommon(SeqWork *work, va_list params);
s32 MGSeqUpdateMG1vs3(SeqWork *work);
s32 MGSeqUpdateMGStory(SeqWork *work);
s32 MGSeqUpdateMG2vs2(SeqWork *work);
s32 MGSeqUpdateMGBowser(SeqWork *work);

s32 MGSeqInitWin(SeqWork *work, va_list params);
s32 MGSeqUpdateWin(SeqWork *work);
s32 MGSeqInitDraw(SeqWork *work, va_list params);
s32 MGSeqUpdateDraw(SeqWork *work);
s32 MGSeqInitRecord(SeqWork *work, va_list params);
s32 MGSeqUpdateRecord(SeqWork *work);

s32 MGSeqInitFlip(SeqWork *work, va_list params);
s32 MGSeqUpdateFlip(SeqWork *work);

extern OverlayID mgSeqOvlPrev;

#endif
