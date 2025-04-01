#include "game/hsfdraw.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/process.h"
#include "math.h"

#include "REL/m407dll.h"

typedef struct unkDominationData4 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s32 unk_1C;
} unkDominationData4; // size of 0x20

// function signatures
void fn_1_4858(omObjData *arg0);
void fn_1_485C(omObjData *arg0);
void fn_1_46EC(omObjData *arg0);
void fn_1_465C(omObjData *arg0, s32 arg1);
void fn_1_4808(omObjData *arg0);

// bss
Process *lbl_1_bss_3970;
omObjData *lbl_1_bss_37E0[100];

// data
s32 lbl_1_data_288[] = { DATA_MAKE_NUM(DATADIR_M407, 0x15), DATA_MAKE_NUM(DATADIR_M407, 0x16), DATA_MAKE_NUM(DATADIR_M407, 0x17),
    DATA_MAKE_NUM(DATADIR_M407, 0x18), DATA_MAKE_NUM(DATADIR_M407, 0x19) };

ObjFuncs lbl_1_data_29C[] = {
    fn_1_4858,
    fn_1_485C,
};

void fn_1_41CC(Process *arg0)
{
    Process *sp8;
    u32 i;
    u32 temp_r30;

    lbl_1_bss_3970 = arg0;
    temp_r30 = 0;

    for (i = 0; i < 40; i++) {
        lbl_1_bss_37E0[i] = omAddObjEx(lbl_1_bss_3970, 0x800, 1, 0, 5, fn_1_46EC);
        lbl_1_bss_37E0[i]->work[0] = i;
        lbl_1_bss_37E0[i]->work[1] = 0;
    }

    temp_r30 += i;

    for (i = 0; i < 4; i++) {
        lbl_1_bss_37E0[temp_r30 + i] = omAddObjEx(lbl_1_bss_3970, 0x800, 1, 0, 5, fn_1_46EC);
        lbl_1_bss_37E0[temp_r30 + i]->work[0] = temp_r30 + i;
        lbl_1_bss_37E0[temp_r30 + i]->work[1] = 1;
    }

    temp_r30 += i;

    for (i = 0; i < 30; i++) {
        lbl_1_bss_37E0[temp_r30 + i] = omAddObjEx(lbl_1_bss_3970, 0x800, 1, 0, 5, fn_1_46EC);
        lbl_1_bss_37E0[temp_r30 + i]->work[0] = temp_r30 + i;
        lbl_1_bss_37E0[temp_r30 + i]->work[1] = 2;
    }

    temp_r30 += i;

    for (i = 0; i < 4; i++) {
        lbl_1_bss_37E0[temp_r30 + i] = omAddObjEx(lbl_1_bss_3970, 0x800, 1, 0, 5, fn_1_46EC);
        lbl_1_bss_37E0[temp_r30 + i]->work[0] = temp_r30 + i;
        lbl_1_bss_37E0[temp_r30 + i]->work[1] = 3;
    }

    temp_r30 += i;

    for (i = 0; i < 22; i++) {
        lbl_1_bss_37E0[temp_r30 + i] = omAddObjEx(lbl_1_bss_3970, 0x800, 1, 0, 5, fn_1_46EC);
        lbl_1_bss_37E0[temp_r30 + i]->work[0] = temp_r30 + i;
        lbl_1_bss_37E0[temp_r30 + i]->work[1] = 4;
    }
}

void fn_1_44F4(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(lbl_1_bss_37E0); i++) {
        fn_1_4808(lbl_1_bss_37E0[i]);
    }
}

void fn_1_4544(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4)
{
    omObjData *temp_r29;
    unkDominationData4 *temp_r31;
    u32 i;

    if ((arg4 < (Center.z - 2000.0f)) || (arg4 > (2000.0f + Center.z))) {
        return;
    }

    for (i = 0; i < ARRAY_COUNT(lbl_1_bss_37E0); i++) {
        temp_r29 = lbl_1_bss_37E0[i];
        temp_r31 = temp_r29->data;
        if ((temp_r31->unk_08 == arg0) && (temp_r31->unk_0C == 0)) {
            temp_r31->unk_04 = arg1;
            temp_r31->unk_10 = arg2;
            temp_r31->unk_14 = arg3;
            temp_r31->unk_18 = arg4;
            fn_1_465C(temp_r29, 1);
            return;
        }
    }
}

void fn_1_465C(omObjData *arg0, s32 arg1)
{
    unkDominationData4 *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk_0C = arg1;
    temp_r31->unk_1C = 0;
}

void fn_1_4680(omObjData *arg0)
{
    unkDominationData4 *temp_r31;

    temp_r31 = arg0->data;
    lbl_1_data_29C[temp_r31->unk_0C](arg0);
    omSetTra(arg0, temp_r31->unk_10, temp_r31->unk_14, temp_r31->unk_18);
}

void fn_1_46EC(omObjData *arg0)
{
    unkDominationData4 *temp_r30;

    arg0->func = fn_1_4680;
    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkDominationData4), MEMORY_DEFAULT_NUM);
    temp_r30 = arg0->data;
    temp_r30->unk_00 = arg0->work[0];
    temp_r30->unk_08 = arg0->work[1];
    temp_r30->unk_1C = 0;
    arg0->model[0] = Hu3DModelCreateFile(lbl_1_data_288[temp_r30->unk_08]);
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
    temp_r30->unk_10 = 0.0f;
    temp_r30->unk_14 = 0.0f;
    temp_r30->unk_18 = 0.0f;
    fn_1_465C(arg0, 0);
}

void fn_1_4808(omObjData *arg0)
{
    unkDominationData4 *sp8;
    sp8 = arg0->data;

    Hu3DModelKill(arg0->model[0]);

    if (arg0->data) {
        HuMemDirectFree(arg0->data);
    }
}

void fn_1_4858(omObjData *arg0) { }

void fn_1_485C(omObjData *arg0)
{
    unkDominationData4 *temp_r30;

    temp_r30 = arg0->data;
    if (temp_r30->unk_04 != 0) {
        temp_r30->unk_04--;
    }

    if (temp_r30->unk_1C == 0) {
        Hu3DMotionTimeSet(*arg0->model, 0.0f);
        Hu3DModelAttrReset(*arg0->model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(*arg0->model, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(*arg0->model, HU3D_MOTATTR_LOOP);
        temp_r30->unk_1C++;
    }
    else if (temp_r30->unk_1C == 1) {
        Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
        temp_r30->unk_1C++;
    }

    if (Hu3DMotionEndCheck(*arg0->model) != 0) {
        Hu3DModelAttrSet(*arg0->model, HU3D_ATTR_DISPOFF);
        fn_1_465C(arg0, 0);
    }
}
