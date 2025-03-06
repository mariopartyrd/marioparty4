#include "REL/resultdll.h"

s16 stageMdlId[32];
s16 stageMotId[32];
s16 stageSprId[33];
s16 lbl_1_bss_1A18;

void StageModelCreate(StageModel *model_list)
{
	StageModel *list;
	s16 i;
	s16 model;
	s16 clear_i;
	ModelData *model_ptr;
	void *data;
	list = model_list;
	for(clear_i=0; clear_i<32; clear_i++) {
		stageMdlId[clear_i] = stageMotId[clear_i] = -1;
	}
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 0) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			model = Hu3DModelCreate(data);
			stageMdlId[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
			model_ptr = &Hu3DData[model];
			if(model_ptr->unk_08 != -1) {
				stageMotId[i] = model_ptr->unk_08;
			}
		} else if(list->type == 1) {
			data = HuDataSelHeapReadNum(list->datanum, MEMORY_DEFAULT_NUM, HEAP_DATA);
			stageMotId[i] = Hu3DJointMotion(stageMdlId[list->mot_link], data);
			
		}
		(void)i;
	}
	list = model_list;
	for(i=0; list->datanum != DATA_NUM_LISTEND; list++, i++) {
		if(list->type == 2) {
			model = Hu3DModelLink(stageMdlId[list->link]);
			stageMdlId[i] = model;
			Hu3DModelAttrSet(model, list->attr);
			Hu3DModelPosSetV(model, &list->pos);
			Hu3DModelRotSetV(model, &list->rot);
			Hu3DModelScaleSetV(model, &list->scale);
		}
		if(list->mot_link != -1) {
			Hu3DMotionSet(stageMdlId[i], stageMotId[list->mot_link]);
		}
		(void)i;
	}
}

void StageSpriteCreate(StageSprite *sprite_list)
{
	StageSprite *list;
	s16 sprite;
	s16 clear_i;
	s16 i;
	list = sprite_list;
	for(clear_i=0; clear_i<32; clear_i++) {
		stageSprId[clear_i] = -1;
	}
	for(i=0; list->datanum; i++, list++) {
		sprite = espEntry(list->datanum, 100, 0);
		stageSprId[i] = sprite;
		espPosSet(sprite, list->x, list->y);
		espColorSet(sprite, list->color.r, list->color.g, list->color.b);
		espTPLvlSet(sprite, list->color.a/255.0f);
		espPriSet(sprite, list->prio);
		espAttrSet(sprite, list->attr);
	}
}

void StageSpriteKill(void)
{
	s16 i;
	for(i=0; i<32; i++) {
		if(stageSprId[i] != -1) {
			espKill(stageSprId[i]);
		}
	}
}