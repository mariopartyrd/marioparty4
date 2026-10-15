#include "REL/modeseldll.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#endif

s16 modeSelMdlId[24];
s16 modeSelMotId[24];
s16 modeSelSprId[12];
s16 modeSelSprGrpId;

DataListModel modeSelModelTbl[] = {
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x1, 2, 0, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x01), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x01), 0x1, 2, 2, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x02), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x02), 0x1, 2, 4, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x03), 0x1, 1, -1, 4, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x04), 0x1, 1, -1, 4, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x05), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x05), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x05), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x06), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x06), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x06), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x26), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x27), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x28), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x29), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x2A), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x2B), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x2C), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x2D), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x2E), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x07), 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ -1, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
};

DataListSprite modeSelSpriteTbl[] = {
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x09), 4, 2000, 288, 240, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x08), 4, 2000, 288, 100, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x0A), 4, 2000, 288, 300, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x0B), 4, 2000, 288, 300, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x0C), 4, 2000, 288, 300, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x1F), 4, 2000, 288, 300, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x20), 4, 2000, 288, 300, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x21), 4, 2000, 288, 300, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x22), 4, 2000, 288, 300, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x2F), 4, 2000, 288, 240, { 255, 255, 255, 255 } },
	{ DATA_MAKE_NUM(DATADIR_MODESEL, 0x3C), 4, 2000, 288, 240, { 255, 255, 255, 255 } },
	{ 0, 0, 0, 0, 0, { 0, 0, 0, 0 } },
};

void ModeSelModelCreate(DataListModel *model_list)
{
	DataListModel *list;
	s16 i;
	s16 model;
	s16 clear_i;
	HU3DMODEL *model_ptr;
	void *data;
	list = model_list;
	for(clear_i=0; clear_i<24; clear_i++) {
		modeSelMdlId[clear_i] = modeSelMotId[clear_i] = -1;
	}
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 0) {
			data = HuDataSelHeapReadNum(list->datanum, HU_MEMNUM_OVL, HEAP_MODEL);
			model = Hu3DModelCreate(data);
			modeSelMdlId[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
			model_ptr = &Hu3DData[model];
			if(model_ptr->motId != -1) {
				modeSelMotId[i] = model_ptr->motId;
			}
		} else if(list->type == 1) {
			data = HuDataSelHeapReadNum(list->datanum, HU_MEMNUM_OVL, HEAP_MODEL);
			modeSelMotId[i] = Hu3DJointMotion(modeSelMdlId[list->mot_link], data);
			
		}
		(void)i;
	}
	list = model_list;
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 2) {
			model = Hu3DModelLink(modeSelMdlId[list->link]);
			modeSelMdlId[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
		}
		if(list->type == 0 && list->mot_link != -1) {
			Hu3DMotionSet(modeSelMdlId[i], modeSelMotId[list->mot_link]);
		}
		(void)i;
	}
}

void ModeSelSpriteCreate(DataListSprite *sprite_list)
{
	DataListSprite *list;
	s16 sprite;
	s16 clear_i;
	s16 i;
	list = sprite_list;
	for(clear_i=0; clear_i<11; clear_i++) {
		modeSelSprId[clear_i] = -1;
	}
	for(i=0; list->datanum; i++, list++) {
		sprite = espEntry(list->datanum, 100, 0);
		modeSelSprId[i] = sprite;
		espPosSet(sprite, list->x, list->y);
		espColorSet(sprite, list->color.r, list->color.g, list->color.b);
		espTPLvlSet(sprite, list->color.a/255.0f);
		espPriSet(sprite, list->prio);
		espAttrSet(sprite, list->attr);
	}
	HuSprGrpScissorSet(espGrpIDGet(), 0, 16, 640, 448);
}

void ModeSelSpriteKill(void)
{
	s16 i;
	for(i=0; i<11; i++) {
		if(modeSelSprId[i] != -1) {
			espKill(modeSelSprId[i]);
		}
	}
}
