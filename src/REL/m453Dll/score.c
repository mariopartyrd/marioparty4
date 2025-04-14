#include "game/esprite.h"
#include "game/flag.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"

#include "REL/m453Dll.h"

typedef struct M453ScoreUnkStruct {
    s32 unk_00;
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C[4];
    s16 unk_14;
    s16 unk_16;
    s32 unk_18;
    float unk_1C;
} M453ScoreUnkStruct; /* size = 0x20 */

typedef void (*M453ScoreUnkFunc)(void);

void fn_1_92C0(s32 arg0);
void fn_1_92F0(omObjData *object);
void fn_1_940C(void);
void fn_1_9484(void);
void fn_1_9510(void);

M453ScoreUnkFunc lbl_1_data_BC0[3] = { fn_1_940C, fn_1_9484, fn_1_9510 };

Process *lbl_1_bss_C4;
omObjData *lbl_1_bss_C0;

void fn_1_8F48(Process *arg0, s16 arg1)
{
    M453ScoreUnkStruct *var_r31;
    u32 var_r30;

    lbl_1_bss_C4 = arg0;
    lbl_1_bss_C0 = omAddObjEx(lbl_1_bss_C4, 0x800, 0, 0, 7, fn_1_92F0);
    lbl_1_bss_C0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M453ScoreUnkStruct), MEMORY_DEFAULT_NUM);
    var_r31 = lbl_1_bss_C0->data;
    var_r31->unk_08 = arg1;
    var_r31->unk_0A = 0;
    var_r31->unk_14 = espEntry(0x530000, 2, 0);
    espTPLvlSet(var_r31->unk_14, 0.5f);
    espPosSet(var_r31->unk_14, 520.0f, 64.0f);
    espColorSet(var_r31->unk_14, 0, 0, 0);
    var_r31->unk_16 = espEntry(0x610037, 1, 0);
    espPosSet(var_r31->unk_16, 501.0f, 55.0f);
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31->unk_0C[var_r30] = espEntry(0x610030, 0, 0);
        espPosSet(var_r31->unk_0C[var_r30], (var_r30 * 0x12) + 0x20A, 56.0f);
        espDispOff(var_r31->unk_0C[var_r30]);
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31->unk_0C[var_r30 + 2] = espEntry(0x610031, 1, 0);
        espPosSet(var_r31->unk_0C[var_r30 + 2], (var_r30 * 0x12) + 0x20A, 72.0f);
    }
    for (var_r30 = 0; var_r30 < 6; var_r30++) {
        espDispOff(var_r31->unk_0C[var_r30]);
    }
    HuDataDirClose(0x530000);
    HuDataDirClose(0x610000);
    fn_1_92C0(0);
}

void fn_1_91D8(void)
{
    s32 var_r31;
    M453ScoreUnkStruct *var_r30 = lbl_1_bss_C0->data;

    for (var_r31 = 0; var_r31 < 7; var_r31++) {
        espKill(var_r30->unk_0C[var_r31]);
    }
    HuMemDirectFree(lbl_1_bss_C0->data);
}

void fn_1_924C(s32 arg0)
{
    switch (arg0) {
        case 0:
            fn_1_92C0(1);
            break;
        case 1:
            fn_1_92C0(2);
            break;
    }
}

void fn_1_929C(void)
{
    fn_1_92C0(0);
}

void fn_1_92C0(s32 arg0)
{
    M453ScoreUnkStruct *var_r31 = lbl_1_bss_C0->data;

    var_r31->unk_00 = arg0;
    var_r31->unk_04 = 0;
}

void fn_1_92F0(omObjData *arg0)
{
    s16 var_r30;

    M453ScoreUnkStruct *var_r31 = lbl_1_bss_C0->data;

    lbl_1_data_BC0[var_r31->unk_00]();
    var_r30 = var_r31->unk_08;
    espBankSet(var_r31->unk_0C[0], var_r30 / 10);
    var_r30 -= (var_r30 / 10) * 10;
    espBankSet(var_r31->unk_0C[1], var_r30);
    var_r30 = var_r31->unk_0A;
    espBankSet(var_r31->unk_0C[2], var_r30 / 10);
    var_r30 -= (var_r30 / 10) * 10;
    espBankSet(var_r31->unk_0C[3], var_r30);
}

void fn_1_940C(void)
{
    s32 var_r30;

    M453ScoreUnkStruct *var_r31 = lbl_1_bss_C0->data;
    if (var_r31->unk_04 == 0) {
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            espDispOff(var_r31->unk_0C[var_r30]);
        }
        var_r31->unk_04 = var_r31->unk_04 + 1;
    }
}

void fn_1_9484(void)
{
    s16 var_r30;
    M453ScoreUnkStruct *var_r31 = lbl_1_bss_C0->data;

    if (var_r31->unk_04 == 0) {
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            espDispOn(var_r31->unk_0C[var_r30]);
        }
        var_r31->unk_04 = var_r31->unk_04 + 1;
    }
    var_r31->unk_0A = fn_1_639C();
}

void fn_1_9510(void)
{
    s32 var_r30;
    M453ScoreUnkStruct *var_r31 = lbl_1_bss_C0->data;

    if (var_r31->unk_04 == 0) {
        var_r31->unk_18 = 0;
        var_r31->unk_1C = 1.0f;
        if (var_r31->unk_0A > var_r31->unk_08) {
            var_r31->unk_08 = var_r31->unk_0A;
        }
        var_r31->unk_04 = var_r31->unk_04 + 1;
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
    espScaleSet(var_r31->unk_16, var_r31->unk_1C, var_r31->unk_1C);
}
