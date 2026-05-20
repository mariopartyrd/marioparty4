#include "REL/m446Dll.h"
#include "game/audio.h"
#include "game/hsfman.h"
#include "game/pad.h"

// bss
unkStruct3 *lbl_1_bss_28;

s32 fn_1_3924(void)
{
    lbl_1_bss_28 = NULL;
    return 1;
}

void fn_1_393C(void)
{
    unkStruct3 *var_r31;
    unkStruct6 *var_r30;

    var_r31 = lbl_1_bss_28;
    if (var_r31) {
        do {
            var_r30 = var_r31->unk0;
            fn_1_3B4C(var_r30);
            var_r31 = var_r31->unk8;
        } while (var_r31);
    }
}

void fn_1_3994(void)
{
    unkStruct4 *sp8;
    unkStruct3 *var_r31;

    var_r31 = lbl_1_bss_28;
    if (var_r31) {
        do {
            sp8 = var_r31->unk0;
            var_r31 = var_r31->unk8;
        } while (var_r31);
    }
}

unkStruct6 *fn_1_39D0(void)
{
    s32 var_r30;
    unkStruct3 *var_r29;
    unkStruct6 *var_r31;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x70, MEMORY_DEFAULT_NUM);
    if (!var_r31) {
        return NULL;
    }
    var_r31->unk4 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M446, 0x05));
    Hu3DModelAmbSet(var_r31->unk4, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowMapSet(var_r31->unk4);
    Hu3DModelLayerSet(var_r31->unk4, 0);
    var_r31->unk0 = m446CursorCreate(0);
    fn_1_7884(var_r31->unk0);
    var_r31->unk60 = 10;
    var_r31->unk5C = 0;
    var_r31->unk6C = 0;

    for (var_r30 = 0; var_r30 < 21; var_r30++) {
        var_r31->unk8[var_r30] = NULL;
    }
    fn_1_46AC(var_r31);
    var_r29 = fn_1_1DF4(var_r31);
    if (!var_r29) {
        OSReport("[!] m446TableCreate ERROR...\n");
        HuMemDirectFree(var_r31);
        return NULL;
    }
    if (lbl_1_bss_28) {
        fn_1_1EC8(lbl_1_bss_28, var_r29);
    }
    else {
        lbl_1_bss_28 = var_r29;
    }
    return var_r31;
}

void fn_1_3B4C(unkStruct6 *arg0)
{
    unkStruct3 *var_r31;

    var_r31 = lbl_1_bss_28;
    do {
        if (arg0 == var_r31->unk0) {
            if (var_r31 == lbl_1_bss_28) {
                lbl_1_bss_28 = var_r31->unk8;
            }
            fn_1_1F04(var_r31);
            fn_1_1E5C(var_r31);
            Hu3DModelKill(arg0->unk4);
            fn_1_76E8(arg0->unk0);
            HuMemDirectFree(arg0);
            return;
        }
        var_r31 = var_r31->unk8;
    } while (var_r31);
}

s32 fn_1_3BF0(unkStruct6 *arg0, unkStruct4 *arg1, s32 arg2)
{
    Vec sp18;
    Vec spC;
    s32 temp_r29;

    if (arg0->unk5C >= 21) {
        return 0;
    }
    do {
        temp_r29 = fn_1_38F0() % 21;
    } while (arg0->unk8[temp_r29] != 0);
    arg0->unk8[temp_r29] = arg1;
    arg0->unk5C++;
    sp18.x = -60.0f + (20.0f * (temp_r29 % 7));
    sp18.y = 85.0f;
    sp18.z = -20.0f + (20.0f * (temp_r29 / 7));
    spC = arg1->unk34;
    switch (arg2) {
        case 3:
        case 4:
            spC.z = 720.0f;
            arg1->unk34 = spC;
            spC.z = 0.0f;
            fn_1_27FC(arg1, &sp18, 0x3C);
            fn_1_2928(arg1, &spC, 0x3C);
            fn_1_29B4(arg1, 1.0f, 0x3C);
            break;
        case 0:
            spC.y = 0.0f;
            arg1->unk10 = sp18;
            arg1->unk34 = spC;
            arg1->unk58 = 1.0f;
            break;
        case 2:
            break;
        case 1:
            spC.y = 0.0f;
            fn_1_27FC(arg1, &sp18, 0x3C);
            fn_1_2928(arg1, &spC, 0x3C);
            break;
    }
    return 1;
}

s32 fn_1_3EB4(unkStruct6 *arg0, unkStruct4 *arg1, s32 arg2)
{
    Vec spC;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x15; var_r31++) {
        if (arg0->unk8[var_r31] == arg1) {
            arg0->unk8[var_r31] = NULL;
            arg0->unk5C--;
            break;
        }
    }
    if (var_r31 == 0x15) {
        OSReport("m446TableRemoveCard ERROR...\n");
        return 0;
    }
    switch (arg2) {
        case 3:
            spC = arg1->unk10;
            spC.y = 90.0f;
            fn_1_272C(arg1);
            fn_1_27FC(arg1, &spC, 0x1E);
            fn_1_29B4(arg1, 1.5f, 0x1E);
            HuAudFXPlay(0x76C);
    }
    return 1;
}

s32 fn_1_3FD0(unkStruct6 *arg0, s32 arg1, unkStruct4 **arg2)
{
    if ((arg1 < 0) || (arg1 >= 0x15)) {
        return 0;
    }
    *arg2 = arg0->unk8[arg1];
    return 1;
}

void fn_1_4000(unkStruct6 *arg0, s32 arg1)
{
    s32 var_r31;
    unkStruct4 *var_r30;

    for (var_r31 = 0; var_r31 < 21; var_r31++) {
        if (arg1 != 0) {
            var_r30 = arg0->unk8[20 - var_r31];
        }
        else {
            var_r30 = arg0->unk8[var_r31];
        }
        if ((var_r30) && (var_r30->unk64 == 0)) {
            if (arg1 != 0) {
                arg0->unk60 = (0x14 - var_r31);
                return;
            }
            else {
                arg0->unk60 = var_r31;
                return;
            }
        }
    }
}

s32 fn_1_4088(unkStruct6 *arg0, u8 arg1, u8 arg2, s32 arg3, unkStruct4 **arg4, s32 arg5)
{
    Vec sp10;
    s32 var_r28;
    s32 var_r27;
    unkStruct4 *temp_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 temp_r22;
    s32 temp_r21;

    var_r25 = 0;
    var_r24 = 0;
    var_r28 = 0;
    var_r27 = 0;
    var_r23 = 0;
    *arg4 = NULL;
    if (arg2 >= 4) {
        if (arg0->unk6C == 0) {
            arg0->unk64 = (s32)(fn_1_38F0() % 21);
            do {
                if (!(temp_r26 = arg0->unk8[arg0->unk64]) || temp_r26->unk64 != 0) {
                    arg0->unk64 = ++arg0->unk64 % 21;
                }
                else
                    break;
                (void)temp_r26;
            } while (TRUE);
            arg0->unk6C = 1;
            arg0->unk68 = 0x1E;
        }
        if ((arg0->unk68 > 0) && (arg5 == 0)) {
            arg0->unk68--;
        }
        else {
            var_r28 = (arg0->unk64 / 7) < (arg0->unk60 / 7);
            var_r27 = (arg0->unk64 / 7) > (arg0->unk60 / 7);
            if ((var_r28 == 0) && (var_r27 == 0)) {
                var_r25 = (arg0->unk64) < (arg0->unk60);
                var_r24 = (arg0->unk64) > (arg0->unk60);
            }
            var_r23 = arg0->unk64 == arg0->unk60;
            arg0->unk68 = 0x12;
        }
    }
    else if (arg5 == 0) {
        var_r25 = (HuPadDStkRep[arg2] & 1) != 0;
        var_r24 = (HuPadDStkRep[arg2] & 2) != 0;
        var_r28 = (HuPadDStkRep[arg2] & 8) != 0;
        var_r27 = (HuPadDStkRep[arg2] & 4) != 0;
        var_r23 = (HuPadBtnDown[arg2] & 0x100) != 0;
    }
    if (var_r25 != 0) {
        if ((arg0->unk60 % 7) == 0) {
            arg0->unk60 = (arg0->unk60 + 6);
        }
        else {
            arg0->unk60 = (arg0->unk60 - 1);
        }
        HuAudFXPlay(0);
    }
    if (var_r24 != 0) {
        if ((arg0->unk60 % 7) == 6) {
            arg0->unk60 = (arg0->unk60 - 6);
        }
        else {
            arg0->unk60 = (arg0->unk60 + 1);
        }
        HuAudFXPlay(0);
    }
    if (var_r28 != 0) {
        if ((arg0->unk60 / 7) == 0) {
            arg0->unk60 = (arg0->unk60 + 0xE);
        }
        else {
            arg0->unk60 = (arg0->unk60 - 7);
        }
        HuAudFXPlay(0);
    }
    if (var_r27 != 0) {
        if ((arg0->unk60 / 7) == 2) {
            arg0->unk60 = (arg0->unk60 - 0xE);
        }
        else {
            arg0->unk60 = (arg0->unk60 + 7);
        }
        HuAudFXPlay(0);
    }
    temp_r22 = arg0->unk60 % 7;
    temp_r21 = arg0->unk60 / 7;
    sp10.x = -60.0f + (20.0f * temp_r22);
    sp10.y = 86.0f;
    sp10.z = -20.0f + (20.0f * temp_r21);
    arg0->unk0->unk20 = sp10;
    if (arg0->unk0->field00_bit0 == 0) {
        fn_1_77C8(arg0->unk0, arg1);
        arg0->unk0->field00_bit2 = arg3;
    }
    if ((var_r23 != 0) || (arg5 == 2)) {
        *arg4 = arg0->unk8[((temp_r22 + (temp_r21 * 7)))];
        if (*arg4) {
            if ((*arg4)->unk64 == 0) {
                HuAudFXPlay(0x76A);
                fn_1_7884(arg0->unk0);
                arg0->unk6C = 0;
                return 1;
            }
            HuAudFXPlay(4);
        }
        else {
            HuAudFXPlay(4);
        }
    }
    return 0;
}

void fn_1_46AC(unkStruct6 *arg0)
{
    arg0->unk8[0] = (unkStruct4 *)-1;
    arg0->unk8[6] = (unkStruct4 *)-1;
    arg0->unk8[14] = (unkStruct4 *)-1;
    arg0->unk8[20] = (unkStruct4 *)-1;
}

void fn_1_46D0(unkStruct6 *arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 21; var_r31++) {
        if (arg0->unk8[var_r31] == (unkStruct4 *)-1) {
            arg0->unk8[var_r31] = 0;
        }
    }
}

s32 fn_1_4720(unkStruct6 *arg0, s32 arg1)
{
    s32 var_r29;
    s32 var_r30;
    unkStruct4 *temp_r31;

    for (var_r29 = 0, var_r30 = 0; var_r30 < 21; var_r30++) {
        temp_r31 = arg0->unk8[var_r30];
        if ((temp_r31) && (temp_r31->unk64 == 0) && ((temp_r31->unk0 == arg1) || (arg1 == 5))) {
            var_r29++;
        }
    }
    return var_r29;
}

void fn_1_4798(unkStruct6 *arg0)
{
    unkStruct4 *temp_r31;
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 0x15; var_r30++) {
        temp_r31 = arg0->unk8[var_r30];
        if (temp_r31 && (temp_r31->unk64 != 0)) {
            fn_1_2794(temp_r31);
        }
    }
}
