#ifndef RESULTDLL_H
#define RESULTDLL_H

#include "game/data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "game/sprite.h"

typedef struct StageModel_s {
	s32 datanum;
	u32 attr;
	s16 type;
	s16 link;
	s16 mot_link;
	Vec pos;
	Vec rot;
	Vec scale;
} StageModel;

typedef struct StageSprite_s {
	u32 datanum;
	s16 attr;
	s16 prio;
	float x;
	float y;
	GXColor color;
} StageSprite;

void ResultBoardDataRead(void);
void ResultCoinAdd(void);
void ResultCoinNumGet(s16 *coinNum);

void ResultBattleMain(void);

void StageModelCreate(StageModel *model_list);
void StageSpriteCreate(StageSprite *sprite_list);
void StageSpriteKill(void);

extern s16 stageMdlId[32];
extern s16 stageMotId[32];
extern s16 stageSprId[33];
extern s16 lbl_1_bss_1A18;
extern s32 resultReadEndF;
extern s32 resultFastF;
extern s16 resultBonusPlayer;

#endif