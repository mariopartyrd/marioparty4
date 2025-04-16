#include "datadir_enum.h"
#include "game/data.h"

#include "REL/m460Dll.h"
#include "game/memory.h"

#include "game/esprite.h"
#ifndef __MWERKS__
#endif

typedef struct UnkM460DllScoreWork {
    s32 unk_00;
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C[6];
    s32 unk_18;
    float unk_1C;
} UnkM460DllScoreWork; /* size = 0x20 */

typedef void (*UnkM460DllScoreFunc)(void);

void fn_1_9020(s32 arg0);
void fn_1_9050(omObjData *object);
void fn_1_916C(void);
void fn_1_91E4(void);
void fn_1_9270(void);

UnkM460DllScoreFunc lbl_1_data_380[3] = { fn_1_916C, fn_1_91E4, fn_1_9270 };

Process *lbl_1_bss_54;
omObjData *lbl_1_bss_50;
// ? lbl_1_rodata_3D0;

void fn_1_8CAC(Process *process, s16 arg1)
{
    UnkM460DllScoreWork *var_r31;
    u32 var_r30;

    lbl_1_bss_54 = process;
    lbl_1_bss_50 = omAddObjEx(lbl_1_bss_54, 0x800, 0, 0, 7, fn_1_9050);
    lbl_1_bss_50->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM460DllScoreWork), MEMORY_DEFAULT_NUM);
    var_r31 = lbl_1_bss_50->data;
    var_r31->unk_08 = arg1;
    var_r31->unk_0A = 0;
    var_r31->unk_0C[4] = espEntry(0x590024, 2, 0);
    espColorSet(var_r31->unk_0C[4], 0, 0, 0);
    espTPLvlSet(var_r31->unk_0C[4], 0.5f);
    espPosSet(var_r31->unk_0C[4], 508.0f, 64.0f);
    var_r31->unk_0C[5] = espEntry(0x610037, 1, 0);
    espPosSet(var_r31->unk_0C[5], 490.0f, 56.0f);
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31->unk_0C[var_r30] = espEntry(0x610030, 0, 0);
        espPosSet(var_r31->unk_0C[var_r30], (var_r30 * 0x10) + 0x1FE, 56.0f);
        espDispOff(var_r31->unk_0C[var_r30]);
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31->unk_0C[var_r30 + 2] = espEntry(0x610031, 1, 0);
        espPosSet(var_r31->unk_0C[var_r30 + 2], (var_r30 * 0x10) + 0x1FE, 74.0f);
    }
    for (var_r30 = 0; var_r30 < 6; var_r30++) {
        espDispOff(var_r31->unk_0C[var_r30]);
    }
    HuDataDirClose(DATA_MAKE_NUM(DATADIR_MGCONST, 0));
    fn_1_9020(0);
}

void fn_1_8F38(void)
{
    s32 var_r31;
    UnkM460DllScoreWork *var_r30 = lbl_1_bss_50->data;
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        espKill(var_r30->unk_0C[var_r31]);
    }
    HuMemDirectFree(lbl_1_bss_50->data);
}

void fn_1_8FAC(s32 arg0)
{
    switch (arg0) {
        case 0:
            fn_1_9020(1);
            break;
        case 1:
            fn_1_9020(2);
            break;
    }
}

void fn_1_8FFC(void)
{
    fn_1_9020(0);
}

void fn_1_9020(s32 arg0)
{
    UnkM460DllScoreWork *var_r31;

    var_r31 = lbl_1_bss_50->data;
    var_r31->unk_00 = arg0;
    var_r31->unk_04 = 0;
}

void fn_1_9050(omObjData *arg0)
{
    UnkM460DllScoreWork *var_r31;
    s16 var_r30;

    var_r31 = lbl_1_bss_50->data;
    lbl_1_data_380[var_r31->unk_00]();
    var_r30 = var_r31->unk_08;
    espBankSet(var_r31->unk_0C[0], var_r30 / 10);
    var_r30 -= (var_r30 / 10) * 10;
    espBankSet(var_r31->unk_0C[1], var_r30);
    var_r30 = var_r31->unk_0A;
    espBankSet(var_r31->unk_0C[2], var_r30 / 10);
    var_r30 -= (var_r30 / 10) * 10;
    espBankSet(var_r31->unk_0C[3], var_r30);
}

void fn_1_916C(void)
{
    UnkM460DllScoreWork *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_50->data;
    if (var_r31->unk_04 == 0) {
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            espDispOff(var_r31->unk_0C[var_r30]);
        }
        var_r31->unk_04++;
    }
}

void fn_1_91E4(void)
{
    UnkM460DllScoreWork *var_r31;
    s16 var_r30;

    var_r31 = lbl_1_bss_50->data;
    if (var_r31->unk_04 == 0) {
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            espDispOn(var_r31->unk_0C[var_r30]);
        }
        var_r31->unk_04++;
    }
    var_r31->unk_0A = fn_1_4370();
}

void fn_1_9270(void)
{
    UnkM460DllScoreWork *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_50->data;
    if (var_r31->unk_04 == 0) {
        var_r31->unk_18 = 0;
        var_r31->unk_1C = 1.0f;
        if (var_r31->unk_0A > var_r31->unk_08) {
            var_r31->unk_08 = var_r31->unk_0A;
        }
        var_r31->unk_04++;
    }
    if (var_r31->unk_18 == 0) {
        if ((var_r31->unk_1C += 0.02f) >= 1.2f) {
            var_r31->unk_1C = 1.2f;
            var_r31->unk_18 = 1;
        }
    }
    else {
        if ((var_r31->unk_1C -= 0.04f) <= 1.0f) {
            var_r31->unk_1C = 1.0f;
            var_r31->unk_18 = 0;
        }
    }
    for (var_r30 = 0; var_r30 <= 1; var_r30++) {
        espScaleSet(var_r31->unk_0C[var_r30], var_r31->unk_1C, var_r31->unk_1C);
    }
    espScaleSet(var_r31->unk_0C[5], var_r31->unk_1C, var_r31->unk_1C);
}
