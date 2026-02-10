#include "game/audio.h"
#include "game/data.h"
#include "game/hsfman.h"
#include "game/process.h"
#include "game/hsfmotion.h"
#include "game/esprite.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

typedef struct ModelSetupEntry {
/* 0x00 */ u32 dataNum;
/* 0x04 */ s16 attr;
/* 0x06 */ s16 type;
/* 0x08 */ s16 linkIdx;
/* 0x0A */ s16 motionIdx;
/* 0x0C */ Vec pos;
/* 0x18 */ Vec rot;
/* 0x24 */ Vec scale;
} ModelSetupEntry;

typedef struct FootstepWork {
    s16 tableIdx;
    s16 animIdx;
    s16 modelIdx;
    s16 motionId;
} FootstepWork;

//func signatures
void fn_8004040C();

//bss
s16 modelTable[0x80];
s16 motionTable[0x80];
s16 spriteTable[0x80];

//sbss
char lbl_801D3DA0[8];

//data
s16 stepFrames0[] = {
    0x000D, 0x0026,
    0x0008, 0x0017
};

s16 stepFrames1[] = {
    0x0005, 0x001E,
    0x0001, 0x000F
};

s16 stepFrames2[] = {
    0x000D, 0x0019,
    0x000B, 0x001A
};

s16 stepFrames3[] = {
    0x000C, 0x0022,
    0x000A, 0x001B
};

s16* stepFrameTable[] = {
    stepFrames0,
    stepFrames1,
    stepFrames2,
    stepFrames0,
    stepFrames3,
    stepFrames0,
    stepFrames0,
    stepFrames0
};

void fn_8003FF68(ModelSetupEntry* setupList) {
    ModelData* modelData;
    s16 modelId;
    s16 j, i;
    ModelSetupEntry* entry;
    void* data;

    entry = setupList;
    for (i = 0; i < ARRAY_COUNT(modelTable); i++) {
        modelTable[i] = motionTable[i] = -1;      
    }

    for (j = 0; entry->dataNum != -1U; entry++, j++) {
        if (entry->type == 0) {
            data = HuDataSelHeapReadNum(entry->dataNum, MEMORY_DEFAULT_NUM, HEAP_DATA);
            modelId = Hu3DModelCreate(data);
            modelTable[j] = modelId;
            Hu3DModelAttrSet(modelId, entry->attr);
            Hu3DModelPosSetV(modelId, &entry->pos);
            Hu3DModelRotSetV(modelId, &entry->rot);
            Hu3DModelScaleSetV(modelId, &entry->scale);
            modelData = &Hu3DData[modelId];
            if (modelData->unk_08 != -1) {
                motionTable[j] = modelData->unk_08;
            }
        } else if (entry->type == 1) {
            data = HuDataSelHeapReadNum(entry->dataNum, MEMORY_DEFAULT_NUM, HEAP_DATA);
            motionTable[j] = Hu3DMotionCreate(data);
        }        
    }

    entry = setupList;

    for (j = 0; entry->dataNum != 0; entry++, j++) {
        if (entry->type == 2) {
            modelId = Hu3DModelLink(modelTable[entry->linkIdx]);
            modelTable[j] = modelId;
            Hu3DModelAttrSet(modelId, entry->attr);
            Hu3DModelPosSetV(modelId, &entry->pos);
            Hu3DModelRotSetV(modelId, &entry->rot);
            Hu3DModelScaleSetV(modelId, &entry->scale);
        }
        if (entry->motionIdx != -1) {
            Hu3DMotionSet(modelTable[j], motionTable[entry->motionIdx]);
        }        
    }
    //reg alloc hack
    (void)j;
    (void)j;
    (void)j;
}

typedef struct SpriteSetupEntry {
    u32 dataNum;
    s16 attr;
    s16 prio;
    f32 posX;
    f32 posY;
    u8 r;
    u8 g;
    u8 b;
    u8 alpha;
} SpriteSetupEntry;

void fn_800401D0(SpriteSetupEntry* setupList) {
    s16 spriteId;
    s16 j;
    s16 i;
    SpriteSetupEntry* entry;

    entry = setupList;
    
    for (i = 0; i < ARRAY_COUNT(spriteTable); i++) {
        spriteTable[i] = -1;
    }

    for (j = 0; entry->dataNum != 0; j++, entry++) {
        spriteId = espEntry(entry->dataNum, 100, 0);
        spriteTable[j] = spriteId;
        espPosSet(spriteId, entry->posX, entry->posY);
        espColorSet(spriteId, entry->r, entry->g, entry->b);
        espTPLvlSet(spriteId, entry->alpha / 255.0f);
        espPriSet(spriteId, entry->prio);
        espAttrSet(spriteId, entry->attr);        
    }
}

void fn_800402FC(void) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(spriteTable); i++) {
        if (spriteTable[i] != -1) {
            espKill(spriteTable[i]);
        }        
    }
}

void fn_80040374(s16 tableIdx, s16 animIdx, s16 modelIdx, s16 motionId) {
    Process* process;
    FootstepWork* work;

    process = HuPrcChildCreate(fn_8004040C, 1, 0x1000, 0, HuPrcCurrentGet());
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(FootstepWork), MEMORY_DEFAULT_NUM);
    process->user_data = work;
    work->tableIdx = tableIdx;
    work->animIdx = animIdx;
    work->modelIdx = modelIdx;
    work->motionId = motionId;
}

void fn_8004040C(void) {
    ModelData* modelData;
    s16* frames;
    FootstepWork* work;
    Process* process;

    process = HuPrcCurrentGet();
    work = (FootstepWork*)process->user_data;
    modelData = &Hu3DData[work->modelIdx];
    frames = stepFrameTable[work->tableIdx];

    while (1) {
        if (modelData->unk_08 == work->motionId &&
            (modelData->unk_64 == (frames[work->animIdx * 2] & 0xFFE) ||
            modelData->unk_64 == (frames[work->animIdx * 2 + 1] & 0xFFE))) {
            HuAudFXPlay(0);
        }
        HuPrcVSleep();        
    }
}
