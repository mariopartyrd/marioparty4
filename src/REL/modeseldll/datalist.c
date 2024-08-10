#include "REL/modeseldll.h"

s16 lbl_1_bss_19A[24];
s16 lbl_1_bss_16A[24];
s16 lbl_1_bss_152[12];
s16 lbl_1_bss_150;

DataListModel lbl_1_data_428[] = {
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

DataListSprite lbl_1_data_93C[] = {
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

void fn_1_BED8(DataListModel *model_list)
{
	DataListModel *list;
	s16 i;
	s16 model;
	s16 clear_i;
	ModelData *model_ptr;
	void *data;
	list = model_list;
	for(clear_i=0; clear_i<24; clear_i++) {
		lbl_1_bss_19A[clear_i] = lbl_1_bss_16A[clear_i] = -1;
	}
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 0) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			model = Hu3DModelCreate(data);
			lbl_1_bss_19A[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
			model_ptr = &Hu3DData[model];
			if(model_ptr->unk_08 != -1) {
				lbl_1_bss_16A[i] = model_ptr->unk_08;
			}
		} else if(list->type == 1) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			lbl_1_bss_16A[i] = Hu3DJointMotion(lbl_1_bss_19A[list->mot_link], data);
			
		}
		(void)i;
	}
	list = model_list;
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 2) {
			model = Hu3DModelLink(lbl_1_bss_19A[list->link]);
			lbl_1_bss_19A[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
		}
		if(list->type == 0 && list->mot_link != -1) {
			Hu3DMotionSet(lbl_1_bss_19A[i], lbl_1_bss_16A[list->mot_link]);
		}
		(void)i;
	}
}

void fn_1_C168(DataListSprite *sprite_list)
{
	DataListSprite *list;
	s16 sprite;
	s16 clear_i;
	s16 i;
	list = sprite_list;
	for(clear_i=0; clear_i<11; clear_i++) {
		lbl_1_bss_152[clear_i] = -1;
	}
	for(i=0; list->datanum; i++, list++) {
		sprite = espEntry(list->datanum, 100, 0);
		lbl_1_bss_152[i] = sprite;
		espPosSet(sprite, list->x, list->y);
		espColorSet(sprite, list->color.r, list->color.g, list->color.b);
		espTPLvlSet(sprite, list->color.a/255.0f);
		espPriSet(sprite, list->prio);
		espAttrSet(sprite, list->attr);
	}
	HuSprGrpScissorSet(espGrpIDGet(), 0, 16, 640, 448);
}

void fn_1_C2BC(void)
{
	s16 i;
	for(i=0; i<11; i++) {
		if(lbl_1_bss_152[i] != -1) {
			espKill(lbl_1_bss_152[i]);
		}
	}
}
