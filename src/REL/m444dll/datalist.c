#include "REL/m444dll.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#endif

s16 lbl_1_bss_199C2[90];
s16 lbl_1_bss_1990E[90];
s16 lbl_1_bss_1990A[2];
s16 lbl_1_bss_19908;

DataListModel lbl_1_data_470[] = {
	{ 0x4B0000, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0000, 0, 0, 0, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0000, 0, 0, 0, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0001, 0, 0, -1, -1, { 0, 150, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0002, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0003, 0, 0, -1, -1, { 0, 150, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0004, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0005, 0, 0, -1, -1, { 0, 150, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0006, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0007, 0x40000002, 0, -1, 10, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0008, 0, 1, -1, 9, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0015, 0x40000002, 0, -1, 12, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0016, 0, 1, -1, 11, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0017, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0018, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0014, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0020, 0x40000001, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B001F, 0x40000001, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B002C, 0x40000001, 0, -1, 19, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B002D, 0, 1, -1, 18, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B002E, 0, 1, -1, 18, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B002F, 0, 1, -1, 18, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0030, 0x40000001, 0, -1, 23, { 200, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0031, 0, 1, -1, 22, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0032, 0, 1, -1, 22, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0033, 0, 1, -1, 22, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0034, 0x40000001, 0, -1, 27, { 400, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0035, 0, 1, -1, 26, { -200, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0036, 0, 1, -1, 26, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0037, 0, 1, -1, 26, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0038, 0x40000001, 0, -1, 31, { -200, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0039, 0, 1, -1, 30, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B003A, 0, 1, -1, 30, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B003B, 0, 1, -1, 30, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B003C, 0x40000001, 0, -1, 35, { -400, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B003D, 0, 1, -1, 34, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B003E, 0, 1, -1, 34, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B003F, 0, 1, -1, 34, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0040, 0x40000001, 0, -1, 43, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0040, 0x40000001, 0, -1, 43, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0040, 0x40000001, 0, -1, 43, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0040, 0x40000001, 0, -1, 43, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0040, 0x40000001, 0, -1, 43, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0041, 0, 1, -1, 38, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0042, 0, 1, -1, 38, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0043, 0, 1, -1, 38, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0044, 0, 1, -1, 38, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0024, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0024, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0024, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0024, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0024, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0024, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0024, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0024, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0009, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0009, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0009, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0019, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0019, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B0019, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B001A, 0, 1, -1, 58, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B001B, 0, 1, -1, 58, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B001C, 0, 1, -1, 58, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B001E, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B001D, 0x40000002, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B001D, 0x40000002, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B001D, 0x40000002, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B000A, 0x40000002, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B000A, 0x40000002, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B000A, 0x40000002, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } },
	{ 0x4B000B, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.15f, 0.15f, 0.15f } },
	{ 0x4B000B, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.15f, 0.15f, 0.15f } },
	{ 0x4B000B, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.15f, 0.15f, 0.15f } },
	{ 0x4B0024, 0x1, 2, 47, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B0024, 0x1, 2, 48, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B0024, 0x1, 2, 49, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B0024, 0x1, 2, 50, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B000F, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B0011, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B000D, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B0010, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B000E, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B000C, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B000C, 0x1, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 0.4f, 0.4f, 0.4f } },
	{ 0x4B0021, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
	{ 0x4B0021, 0, 2, 85, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
	{ 0x4B0021, 0, 2, 85, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
	{ 0x4B0021, 0, 2, 85, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
	{ 0x4B0021, 0, 0, 85, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
	{ -1, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
};

void fn_1_D588(DataListModel *model_list)
{
	DataListModel *list;
	s16 i;
	s16 model;
	s16 clear_i;
	ModelData *model_ptr;
	void *data;
	list = model_list;
	for(clear_i=0; clear_i<90; clear_i++) {
		lbl_1_bss_199C2[clear_i] = lbl_1_bss_1990E[clear_i] = -1;
	}
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 0) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			model = Hu3DModelCreate(data);
			lbl_1_bss_199C2[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
			model_ptr = &Hu3DData[model];
			if(model_ptr->unk_08 != -1) {
				lbl_1_bss_1990E[i] = model_ptr->unk_08;
			}
		} else if(list->type == 1) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			lbl_1_bss_1990E[i] = Hu3DJointMotion(lbl_1_bss_199C2[list->mot_link], data);
			
		}
		(void)i;
	}
	list = model_list;
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 2) {
			model = Hu3DModelLink(lbl_1_bss_199C2[list->link]);
			lbl_1_bss_199C2[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
		}
		if(list->type == 0 && list->mot_link != -1) {
			Hu3DMotionSet(lbl_1_bss_199C2[i], lbl_1_bss_1990E[list->mot_link]);
		}
		(void)i;
	}
}

void fn_1_D818(DataListSprite *sprite_list)
{
	DataListSprite *list;
	s16 sprite;
	s16 clear_i;
	s16 i;
	list = sprite_list;
	for(clear_i=0; clear_i<1; clear_i++) {
		lbl_1_bss_1990A[clear_i] = -1;
	}
	for(i=0; list->datanum; i++, list++) {
		sprite = espEntry(list->datanum, 100, 0);
		lbl_1_bss_1990A[i] = sprite;
		espPosSet(sprite, list->x, list->y);
		espColorSet(sprite, list->color.r, list->color.g, list->color.b);
		espTPLvlSet(sprite, list->color.a/255.0f);
		espPriSet(sprite, list->prio);
		espAttrSet(sprite, list->attr);
	}
}

void fn_1_D950(void)
{
	s16 i;
	for(i=0; i<1; i++) {
		if(lbl_1_bss_1990A[i] != -1) {
			espKill(lbl_1_bss_1990A[i]);
		}
	}
}
