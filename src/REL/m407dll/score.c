#include "game/esprite.h"
#include "game/object.h"
#include "game/process.h"
#include "game/sprite.h"

#include "REL/m407dll.h"

typedef struct unkDominationData6 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C[8]; // what size is this??
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ f32 unk_20;
} unkDominationData6; // sizeof 0x24

// func signatures
void fn_1_61A0(void);
void fn_1_6218(void);
void fn_1_62A0(void);
void fn_1_5FE4(omObjData *arg0);
void fn_1_5FB4(s32 arg0);
s16 fn_1_28D4(void);

// bss
Process *lbl_1_bss_398C;
omObjData *lbl_1_bss_3988;

// data
VoidFuncs lbl_1_data_360[] = { fn_1_61A0, fn_1_6218, fn_1_62A0 };

void fn_1_5C5C(Process *arg0, s16 arg1)
{
    unkDominationData6 *temp_r31;
    u32 i;

    lbl_1_bss_398C = arg0;
    lbl_1_bss_3988 = omAddObjEx(lbl_1_bss_398C, 0x800, 0, 0, 7, fn_1_5FE4);
    lbl_1_bss_3988->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkDominationData6), MEMORY_DEFAULT_NUM);
    temp_r31 = lbl_1_bss_3988->data;
    temp_r31->unk_08 = arg1;
    temp_r31->unk_0A = 0;
    temp_r31->unk_0C[6] = espEntry(DATA_MAKE_NUM(DATADIR_M407, 0x25), 2, 0);
    espTPLvlSet(temp_r31->unk_0C[6], 0.5f);
    espPosSet(temp_r31->unk_0C[6], 508.0f, 64.0f);
    temp_r31->unk_0C[7] = espEntry(DATA_MAKE_NUM(DATADIR_M407, 0x22), 1, 0);
    espPosSet(temp_r31->unk_0C[7], 480.0f, 56.0f);

    for (i = 0; i < 3; i++) {
        temp_r31->unk_0C[i] = espEntry(DATA_MAKE_NUM(DATADIR_M407, 0x1F), 0, 0);
        espPosSet(temp_r31->unk_0C[i], i * 16 + 0x1F4, 56.0f);
        espDispOff(temp_r31->unk_0C[i]);
    }

    for (i = 0; i < 3; i++) {
        temp_r31->unk_0C[i + 3] = espEntry(DATA_MAKE_NUM(DATADIR_M407, 0x20), 1, 0);
        espPosSet(temp_r31->unk_0C[i + 3], i * 16 + 0x1F4, 74.0f);
    }

    for (i = 0; i < 8; i++) {
        espDispOff(temp_r31->unk_0C[i]);
    }

    fn_1_5FB4(0);
}

void fn_1_5ECC(void)
{
    s32 i;
    unkDominationData6 *temp_r30;

    temp_r30 = lbl_1_bss_3988->data;
    for (i = 0; i < 7; i++) {
        espKill(temp_r30->unk_0C[i]);
    }

    HuMemDirectFree(lbl_1_bss_3988->data);
}

void fn_1_5F40(s32 arg0)
{
    switch (arg0) {
        case 0:
            fn_1_5FB4(1);
            break;
        case 1:
            fn_1_5FB4(2);
            break;
    }
}

void fn_1_5F90(void)
{
    fn_1_5FB4(0);
}

void fn_1_5FB4(s32 arg0)
{
    unkDominationData6 *temp_r31;

    temp_r31 = lbl_1_bss_3988->data;
    temp_r31->unk_00 = arg0;
    temp_r31->unk_04 = 0;
}

void fn_1_5FE4(omObjData *arg0)
{
    s16 temp_r31;
    unkDominationData6 *temp_r30;

    temp_r30 = lbl_1_bss_3988->data;
    lbl_1_data_360[temp_r30->unk_00]();
    temp_r31 = temp_r30->unk_08;
    espBankSet(temp_r30->unk_0C[0], temp_r31 / 100);
    temp_r31 = (temp_r31 - ((temp_r31 / 100) * 100));
    espBankSet(temp_r30->unk_0C[1], (temp_r31 / 10));
    temp_r31 = (temp_r31 - ((temp_r31 / 10) * 10));
    espBankSet(temp_r30->unk_0C[2], temp_r31);
    temp_r31 = temp_r30->unk_0A;
    espBankSet(temp_r30->unk_0C[3], (temp_r31 / 100));
    temp_r31 = (temp_r31 - ((temp_r31 / 100) * 100));
    espBankSet(temp_r30->unk_0C[4], (temp_r31 / 10));
    temp_r31 = (temp_r31 - ((temp_r31 / 10) * 10));
    espBankSet(temp_r30->unk_0C[5], temp_r31);
}

void fn_1_61A0(void)
{
    s32 i;
    unkDominationData6 *temp_r31;

    temp_r31 = lbl_1_bss_3988->data;

    if (temp_r31->unk_04 == 0) {
        for (i = 0; i < ARRAY_COUNT(temp_r31->unk_0C); i++) {
            espDispOff(temp_r31->unk_0C[i]);
        }
        temp_r31->unk_04++;
    }
}

void fn_1_6218(void)
{
    s16 i;
    unkDominationData6 *temp_r31;

    temp_r31 = lbl_1_bss_3988->data;

    if (temp_r31->unk_04 == 0) {
        for (i = 0; i < ARRAY_COUNT(temp_r31->unk_0C); i++) {
            espDispOn(temp_r31->unk_0C[i]);
        }
        temp_r31->unk_04++;
    }

    temp_r31->unk_0A = fn_1_28D4();
}

void fn_1_62A0(void)
{
    s32 i;
    unkDominationData6 *temp_r31;

    temp_r31 = lbl_1_bss_3988->data;

    if (temp_r31->unk_04 == 0) {
        temp_r31->unk_1C = 0;
        temp_r31->unk_20 = 1.0f;
        if (temp_r31->unk_0A > temp_r31->unk_08) {
            temp_r31->unk_08 = temp_r31->unk_0A;
        }
        temp_r31->unk_04++;
    }

    if (temp_r31->unk_1C == 0) {
        if ((temp_r31->unk_20 += 0.02f) >= 1.2f) {
            temp_r31->unk_20 = 1.2f;
            temp_r31->unk_1C = 1;
        }
    }
    else {
        if ((temp_r31->unk_20 -= 0.04f) <= 1.0f) {
            temp_r31->unk_20 = 1.0f;
            temp_r31->unk_1C = 0;
        }
    }

    for (i = 0; i <= 2; i++) {
        espScaleSet(temp_r31->unk_0C[i], temp_r31->unk_20, temp_r31->unk_20);
    }

    espScaleSet(temp_r31->unk_0C[7], temp_r31->unk_20, temp_r31->unk_20);
}
