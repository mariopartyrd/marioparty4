#include "REL/mgmodedll.h"

DataListModel lbl_1_data_490[] = {
	{ 0x620000, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620001, 0x40000001, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620002, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620003, 0, 1, -1, 2, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620004, 0, 1, -1, 2, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x62005E, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x62005F, 0, 1, -1, 5, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620060, 0, 1, -1, 5, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620061, 0, 1, -1, 5, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620005, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620006, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620007, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x620008, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ -1, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
};

DataListSprite lbl_1_data_768[] = {
	{ 0x62000C, 0, 10, 288, -200, { 255, 255, 255, 255 } },
	{ 0x620009, 0, 10, 288, -200, { 255, 255, 255, 255 } },
	{ 0x62000A, 0, 10, 288, -200, { 255, 255, 255, 255 } },
	{ 0x62000D, 4, 100, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620018, 4, 200, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62001A, 4, 20, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62001B, 4, 30, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62001C, 4, 40, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62001D, 4, 50, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62001E, 4, 50, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62001F, 4, 50, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620020, 4, 50, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620021, 4, 50, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620025, 4, 200, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62000E, 4, 210, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62000F, 4, 210, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620019, 4, 200, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620028, 4, 10, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620028, 4, 10, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62002A, 4, 10, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62002E, 4, 200, 288, 240, { 255, 255, 255, 255 } },
	{ 0x62002F, 4, 200, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620032, 4, 5, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620031, 4, 4, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620030, 4, 4, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620029, 4, 4, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620029, 4, 4, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620033, 4, 50, 288, 240, { 255, 255, 255, 255 } },
	{ 0x620034, 4, 50, 288, 256, { 255, 255, 255, 255 } },
	{ 0, 0, 0, 0, 0, { 0, 0, 0, 0 } },
};

void fn_1_267E8(DataListModel *model_list)
{
	DataListModel *list;
	s16 i;
	s16 model;
	s16 clear_i;
	ModelData *model_ptr;
	void *data;
	list = model_list;
	for(clear_i=0; clear_i<13; clear_i++) {
		lbl_1_bss_2C80[clear_i] = lbl_1_bss_2C66[clear_i] = -1;
	}
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 0) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			model = Hu3DModelCreate(data);
			lbl_1_bss_2C80[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
			model_ptr = &Hu3DData[model];
			if(model_ptr->unk_08 != -1) {
				lbl_1_bss_2C66[i] = model_ptr->unk_08;
			}
		} else if(list->type == 1) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			lbl_1_bss_2C66[i] = Hu3DJointMotion(lbl_1_bss_2C80[list->mot_link], data);
			
		}
		(void)i;
	}
	list = model_list;
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 2) {
			model = Hu3DModelLink(lbl_1_bss_2C80[list->link]);
			lbl_1_bss_2C80[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
		}
		if(list->type == 0 && list->mot_link != -1) {
			Hu3DMotionSet(lbl_1_bss_2C80[i], lbl_1_bss_2C66[list->mot_link]);
		}
		(void)i;
	}
}

void fn_1_26A78(DataListSprite *sprite_list)
{
	DataListSprite *list;
	s16 sprite;
	s16 clear_i;
	s16 i;
	list = sprite_list;
	for(clear_i=0; clear_i<29; clear_i++) {
		lbl_1_bss_2C2C[clear_i] = -1;
	}
	for(i=0; list->datanum; i++, list++) {
		sprite = espEntry(list->datanum, 100, 0);
		lbl_1_bss_2C2C[i] = sprite;
		espPosSet(sprite, list->x, list->y);
		espColorSet(sprite, list->color.r, list->color.g, list->color.b);
		espTPLvlSet(sprite, list->color.a/255.0f);
		espPriSet(sprite, list->prio);
		espAttrSet(sprite, list->attr);
	}
}

void fn_1_26BB0(void)
{
	s16 i;
	for(i=0; i<29; i++) {
		if(lbl_1_bss_2C2C[i] != -1) {
			espKill(lbl_1_bss_2C2C[i]);
		}
	}
}