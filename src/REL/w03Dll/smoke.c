#include "dolphin.h"
#include "game/object.h"
#include "REL/w03Dll.h"
#include "game/board/main.h"
#include "game/board/model.h"

typedef struct w03UnkWorkStruct {
    s16 unk_00[5];
    char unk_0A[2];
    f32 unk_0C;
} w03UnkWorkStruct;

extern w03State* lbl_1_bss_0;
omObjData* lbl_1_bss_138[2];
extern Process *boardObjMan;
extern s16 lbl_1_data_1E0;

void fn_1_79E0(omObjData* arg0);

char* kemuri_strings[] = {
	"kemuri1", "kemuri2", "kemuri3",
	"kemuri4", "kemuri5"
};

void fn_1_785C(void) {
    f32 var_f31;
    s32 i;
    w03UnkWorkStruct* temp_r31;
    char* temp_r29;

    lbl_1_bss_138[0] = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, fn_1_79E0);
    temp_r31 = (w03UnkWorkStruct*)&lbl_1_bss_138[0]->work[0];
    for (i = 0; i < ARRAY_COUNT(temp_r31->unk_00); i++) {
        temp_r31->unk_00[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W03, 0x08), NULL, 0);
        temp_r29 = kemuri_strings[i];

        if (0.0f == temp_r31->unk_0C) {
            temp_r31->unk_0C = BoardModelMotionMaxTimeGet(temp_r31->unk_00[i]);
        }

        var_f31 = temp_r31->unk_0C * BoardRandFloat();

        if (var_f31 < 1.0f) {
            var_f31 = 1.0f;
        }

        BoardModelHookSet(lbl_1_data_1E0, temp_r29, temp_r31->unk_00[i]);
        BoardModelMotionStart(temp_r31->unk_00[i], 0, 0x40000001);
        BoardModelMotionTimeSet(temp_r31->unk_00[i], var_f31);
        BoardModelLayerSet(temp_r31->unk_00[i], 2);
        BoardModelPassSet(temp_r31->unk_00[i], 0);        
    }
}

void fn_1_79E0(omObjData* arg0) {
    s32 var_r29;
    s32 i;
    w03UnkWorkStruct* temp_r30;

    temp_r30 = (w03UnkWorkStruct*)&arg0->work[0];

    if (BoardIsKill() != 0) {
        for (i = 0; i < 5; i++) {
            BoardModelKill(temp_r30->unk_00[i]);
        }
        lbl_1_bss_138[0] = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }

    if (lbl_1_bss_0->unk3 != 0) {
        var_r29 = 0;
    } else {
        var_r29 = 1;
    }

    for (i = 0; i < ARRAY_COUNT(temp_r30->unk_00); i++) {
        BoardModelVisibilitySet(temp_r30->unk_00[i], var_r29);
    }
}
