#ifndef REL_MODESELDLL_H
#define REL_MODESELDLL_H

#include "game/data.h"
#include "game/hu3d.h"

#include "game/sprite.h"

typedef struct datalist_model {
	s32 datanum;
	u32 attr;
	s16 type;
	s16 link;
	s16 mot_link;
	Vec pos;
	Vec rot;
	Vec scale;
} DataListModel;

typedef struct datalist_sprite {
	u32 datanum;
	s16 attr;
	s16 prio;
	float x;
	float y;
	GXColor color;
} DataListSprite;

#ifndef __MWERKS__
void ModeSelCameraViewSet(s16 view);
#endif

s32 ModeSelExec(void);
s32 FileSelectExec(void);

void ModeSelModelCreate(DataListModel *model_list);
void ModeSelSpriteCreate(DataListSprite *sprite_list);
void ModeSelSpriteKill(void);

extern s16 modeSelMdlId[24];
extern s16 modeSelMotId[24];
extern s16 modeSelSprId[12];
extern s16 modeSelSprGrpId;
extern s16 fileSelectFxId;
extern DataListModel modeSelModelTbl[];
extern DataListSprite modeSelSpriteTbl[];

#endif
