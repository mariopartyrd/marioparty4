#include "game/data.h"
#include "game/hsfman.h"
#include "game/process.h"
#include "game/hsfmotion.h"
#include "game/esprite.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

typedef struct unkArg0 {
/* 0x00 */ u32 unk_00;
/* 0x04 */ s16 unk_04;
/* 0x06 */ s16 unk_06;
/* 0x08 */ s16 unk_08;
/* 0x0A */ s16 unk_0A;
/* 0x0C */ Vec pos;
/* 0x18 */ Vec rot;
/* 0x24 */ Vec scale;
} unkArg0;

typedef struct unkCode_8003FF68 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} unkCode_8003FF68;

//func signatures
void fn_8004040C();

//bss
s16 lbl_80192060[0x80];
s16 lbl_80192160[0x80];
s16 lbl_80192260[0x80];

//sbss
char lbl_801D3DA0[8];

//data
s16 lbl_801D35C0[] = {
    0x000D, 0x0026,
    0x0008, 0x0017
};

s16 lbl_801D35C8[] = {
    0x0005, 0x001E,
    0x0001, 0x000F
};

s16 lbl_801D35D0[] = {
    0x000D, 0x0019,
    0x000B, 0x001A
};

s16 lbl_801D35D8[] = {
    0x000C, 0x0022,
    0x000A, 0x001B
};

s16* lbl_80130100[] = {
    lbl_801D35C0,
    lbl_801D35C8,
    lbl_801D35D0,
    lbl_801D35C0,
    lbl_801D35D8,
    lbl_801D35C0,
    lbl_801D35C0,
    lbl_801D35C0
};

void fn_8003FF68(unkArg0* arg0) {
    ModelData* temp_r27;
    s16 model;
    s16 j, i;
    unkArg0* var_r31;
    void* temp;

    var_r31 = arg0;
    for (i = 0; i < ARRAY_COUNT(lbl_80192060); i++) {
        lbl_80192060[i] = lbl_80192160[i] = -1;      
    }

    for (j = 0; var_r31->unk_00 != -1U; var_r31++, j++) {
        if (var_r31->unk_06 == 0) {
            temp = HuDataSelHeapReadNum(var_r31->unk_00, MEMORY_DEFAULT_NUM, HEAP_DATA);
            model = Hu3DModelCreate(temp);
            lbl_80192060[j] = model;
            Hu3DModelAttrSet(model, var_r31->unk_04);
            Hu3DModelPosSetV(model, &var_r31->pos);
            Hu3DModelRotSetV(model, &var_r31->rot);
            Hu3DModelScaleSetV(model, &var_r31->scale);
            temp_r27 = &Hu3DData[model];
            if (temp_r27->unk_08 != -1) {
                lbl_80192160[j] = temp_r27->unk_08;
            }
        } else if (var_r31->unk_06 == 1) {
            temp = HuDataSelHeapReadNum(var_r31->unk_00, MEMORY_DEFAULT_NUM, HEAP_DATA);
            lbl_80192160[j] = Hu3DMotionCreate(temp);
        }        
    }

    var_r31 = arg0;

    for (j = 0; var_r31->unk_00 != 0; var_r31++, j++) {
        if (var_r31->unk_06 == 2) {
            model = Hu3DModelLink(lbl_80192060[var_r31->unk_08]);
            lbl_80192060[j] = model;
            Hu3DModelAttrSet(model, var_r31->unk_04);
            Hu3DModelPosSetV(model, &var_r31->pos);
            Hu3DModelRotSetV(model, &var_r31->rot);
            Hu3DModelScaleSetV(model, &var_r31->scale);
        }
        if (var_r31->unk_0A != -1) {
            Hu3DMotionSet(lbl_80192060[j], lbl_80192160[var_r31->unk_0A]);
        }        
    }
    //reg alloc hack
    (void)j;
    (void)j;
    (void)j;
}

typedef struct unkArg0_2 {
    u32 unk0;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} unkArg0_2;

void fn_800401D0(unkArg0_2* arg0) {
    s16 spr;
    s16 j;
    s16 i;
    unkArg0_2* var_r31;

    var_r31 = arg0;
    
    for (i = 0; i < ARRAY_COUNT(lbl_80192260); i++) {
        lbl_80192260[i] = -1;
    }

    for (j = 0; var_r31->unk0 != 0; j++, var_r31++) {
        spr = espEntry(var_r31->unk0, 100, 0);
        lbl_80192260[j] = spr;
        espPosSet(spr, var_r31->unk8, var_r31->unkC);
        espColorSet(spr, var_r31->unk10, var_r31->unk11, var_r31->unk12);
        espTPLvlSet(spr, var_r31->unk13 / 255.0f);
        espPriSet(spr, var_r31->unk6);
        espAttrSet(spr, var_r31->unk4);        
    }
}

void fn_800402FC(void) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(lbl_80192260); i++) {
        if (lbl_80192260[i] != -1) {
            espKill(lbl_80192260[i]);
        }        
    }
}

void fn_80040374(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Process* process;
    unkCode_8003FF68* temp_r3;

    process = HuPrcChildCreate(fn_8004040C, 1, 0x1000, 0, HuPrcCurrentGet());
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkCode_8003FF68), MEMORY_DEFAULT_NUM);
    process->user_data = temp_r3;
    temp_r3->unk0 = arg0;
    temp_r3->unk2 = arg1;
    temp_r3->unk4 = arg2;
    temp_r3->unk6 = arg3;
}

typedef struct UnkUserData {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} UnkUserData;

void fn_8004040C(void) {
    ModelData* temp_r30;
    s16* temp_r29;
    UnkUserData* temp_r31;
    Process* process;

    process = HuPrcCurrentGet();
    temp_r31 = (UnkUserData*)process->user_data;
    temp_r30 = &Hu3DData[temp_r31->unk4];
    temp_r29 = lbl_80130100[temp_r31->unk0];

    while (1) {
        if (temp_r30->unk_08 == temp_r31->unk6 &&
            (temp_r30->unk_64 == (temp_r29[temp_r31->unk2 * 2] & 0xFFE) ||
            temp_r30->unk_64 == (temp_r29[temp_r31->unk2 * 2 + 1] & 0xFFE))) {
            HuAudFXPlay(0);
        }
        HuPrcVSleep();        
    }
}
