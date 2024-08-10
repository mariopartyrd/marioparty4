#include "game/data.h"
#include "game/esprite.h"

#include "REL/m442Dll.h"

s32 fn_1_9520(s32 arg0);
void fn_1_9550(omObjData *object);
void fn_1_970C(void);
void fn_1_9784(void);
void fn_1_980C(void);

typedef void (*M442ScoreFunc)(void);

M442ScoreFunc lbl_1_data_268[3] = { fn_1_970C, fn_1_9784, fn_1_980C };

Process *lbl_1_bss_11F4C;
omObjData *lbl_1_bss_11F48;

typedef struct M442ScoreWork {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C[6];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x0E */ s32 unk_1C;
    /* 0x20 */ float unk_20;
} M442ScoreWork; /* size = 0x24 */

s32 fn_1_91AC(Process *arg0, s16 arg1)
{
    M442ScoreWork *var_r31;
    u32 var_r30;

    lbl_1_bss_11F4C = arg0;
    lbl_1_bss_11F48 = omAddObjEx(lbl_1_bss_11F4C, 0x800, 0, 0, 7, fn_1_9550);
    lbl_1_bss_11F48->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M442ScoreWork), MEMORY_DEFAULT_NUM);
    var_r31 = lbl_1_bss_11F48->data;
    var_r31->unk_08 = arg1;
    var_r31->unk_0A = 0;
    var_r31->unk_18 = espEntry(0x610023, 2, 0);
    espTPLvlSet(var_r31->unk_18, 0.5f);
    espPosSet(var_r31->unk_18, 508.0f, 64.0f);
    espColorSet(var_r31->unk_18, 0, 0, 0);
    var_r31->unk_1A = espEntry(0x610037, 1, 0);
    espPosSet(var_r31->unk_1A, 480.0f, 56.0f);
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        var_r31->unk_0C[var_r30] = espEntry(0x610030, 0, 0);
        espPosSet(var_r31->unk_0C[var_r30], (var_r30 * 0x10) + 0x1F4, 56.0f);
        espDispOff(var_r31->unk_0C[var_r30]);
    }
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        var_r31->unk_0C[var_r30 + 3] = espEntry(0x610031, 1, 0);
        espPosSet(var_r31->unk_0C[var_r30 + 3], (var_r30 * 0x10) + 0x1F4, 74.0f);
    }
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        espDispOff(var_r31->unk_0C[var_r30]);
    }
    HuDataDirClose(0x610000);
    return fn_1_9520(0);
}

void fn_1_9438(void)
{
    s32 var_r31;
    M442ScoreWork *var_r30;

    var_r30 = lbl_1_bss_11F48->data;
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        espKill(var_r30->unk_0C[var_r31]);
    }
    HuMemDirectFree(lbl_1_bss_11F48->data);
}

void fn_1_94AC(s32 arg0)
{
    switch (arg0) {
        case 0:
            fn_1_9520(1);
            break;
        case 1:
            fn_1_9520(2);
            break;
        default:
            break;
    }
}

void fn_1_94FC(void)
{
    fn_1_9520(0);
}

s32 fn_1_9520(s32 arg0)
{
    M442ScoreWork *var_r31;

    var_r31 = lbl_1_bss_11F48->data;
    var_r31->unk_00 = arg0;
    var_r31->unk_04 = 0;
}

void fn_1_9550(omObjData *arg0)
{
    s16 temp_r31;
    M442ScoreWork* temp_r30;

    temp_r30 = lbl_1_bss_11F48->data;
    lbl_1_data_268[temp_r30->unk_00]();
    temp_r31 = temp_r30->unk_08;
    espBankSet(temp_r30->unk_0C[0], temp_r31 / 100);
    temp_r31 = (temp_r31 - ((temp_r31 / 100) * 100));
    espBankSet(temp_r30->unk_0C[1], (temp_r31 / 10));
    temp_r31 =  (temp_r31 - ((temp_r31 / 10) * 10));
    espBankSet(temp_r30->unk_0C[2], temp_r31);
    temp_r31 = temp_r30->unk_0A;
    espBankSet(temp_r30->unk_0C[3], (temp_r31 / 100));
    temp_r31 = (temp_r31 - ((temp_r31 / 100) * 100));
    espBankSet(temp_r30->unk_0C[4],  (temp_r31 / 10));
    temp_r31 = (temp_r31 - ((temp_r31 / 10) * 10));
    espBankSet(temp_r30->unk_0C[5], temp_r31);
}

void fn_1_970C(void)
{
    M442ScoreWork *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_11F48->data;
    if (var_r31->unk_04 == 0) {
        for (var_r30 = 0; var_r30 < 8; var_r30++) {
            espDispOff(var_r31->unk_0C[var_r30]);
        }
        var_r31->unk_04++;
    }
}

void fn_1_9784(void)
{
    s16 var_r30;
    M442ScoreWork *var_r31;

    var_r31 = lbl_1_bss_11F48->data;
    if (var_r31->unk_04 == 0) {
        for (var_r30 = 0; var_r30 < 8; var_r30++) {
            espDispOn(var_r31->unk_0C[var_r30]);
        }
        var_r31->unk_04++;
    }
    var_r31->unk_0A = fn_1_90EC();
}

void fn_1_980C(void)
{
    M442ScoreWork *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_11F48->data;
    if (var_r31->unk_04 == 0) {
        var_r31->unk_1C = 0;
        var_r31->unk_20 = 1.0f;
        if (var_r31->unk_0A > var_r31->unk_08) {
            var_r31->unk_08 = var_r31->unk_0A;
        }
        var_r31->unk_04++;
    }
    if (var_r31->unk_1C == 0) {
        if ((var_r31->unk_20 += 0.02f) >= 1.2f) {
            var_r31->unk_20 = 1.2f;
            var_r31->unk_1C = 1;
        }
    }
    else {
        if ((var_r31->unk_20 -= 0.04f) <= 1.0f) {
            var_r31->unk_20 = 1.0f;
            var_r31->unk_1C = 0;
        }
    }
    for (var_r30 = 0; var_r30 <= 2; var_r30++) {
        espScaleSet(var_r31->unk_0C[var_r30], var_r31->unk_20, var_r31->unk_20);
    }
    espScaleSet(var_r31->unk_1A, var_r31->unk_20, var_r31->unk_20);
}
