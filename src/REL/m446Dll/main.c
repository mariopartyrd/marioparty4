#include "REL/m446Dll.h"
#include "math.h"

#include "game/audio.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/window.h"
#include "game/wipe.h"

// bss
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
Process *lbl_1_bss_C;
omObjData *lbl_1_bss_8;
s32 lbl_1_bss_4;
unkStruct *lbl_1_bss_0;

// data
Vec lbl_1_data_0 = { 0.0f, 90.0f, 0.0f };
Vec lbl_1_data_C = { -40.0f, 40.0f, 0.0f };
f32 lbl_1_data_18 = 1260.0f;
Vec lbl_1_data_1C = { 0.0f, 90.0f, 0.0f };
Vec lbl_1_data_28 = { -90.0f, 0.0f, 0.0f };
f32 lbl_1_data_34 = 260.0f;
Vec lbl_1_data_38[2] = { { 0.0f, 100.0f, 120.0f }, { 0.0f, 100.0f, 120.0f } };
Vec lbl_1_data_50[2] = { { -30.0f, 0.0f, 0.0f }, { -30.0f, 0.0f, 0.0f } };
f32 lbl_1_data_68[2] = { 600.0f, 600.0f };
s32 lbl_1_data_70[2][2] = { { 0x46, 0x1A4 }, { 0x1F4, 0x3C } };

void ObjectSetup(void)
{
    lbl_1_bss_C = omInitObjMan(5, 0x2000);
    omGameSysInit(lbl_1_bss_C);
    lbl_1_bss_8 = omAddObjEx(lbl_1_bss_C, 0x3E8, 0x32U, 0x32U, 0, fn_1_13C);
    omSetStatBit(lbl_1_bss_8, 0x100U);
    lbl_1_bss_4 = 0;
}

void fn_1_13C(omObjData *arg0)
{
    switch (lbl_1_bss_4) {
        case 0:
            HuWinInit(1);
            Hu3DLighInit();
            frand();
            fn_1_38E0();
            fn_1_6778();
            fn_1_7BF0();
            fn_1_2064();
            fn_1_480C();
            fn_1_3924();
            fn_1_72E0();
            lbl_1_bss_0 = m446FlowCreate();
            lbl_1_bss_4 = 1;
            break;
        case 1:
            fn_1_4B4(lbl_1_bss_0);
            fn_1_7C60();
            fn_1_487C();
            fn_1_3994();
            fn_1_7350();
            fn_1_20D4();
            fn_1_68DC();
            if (lbl_1_bss_0->unk0 != 5)
                break;
            lbl_1_bss_4 = 3;
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        case 2:
            break;
        case 3:
            if (WipeStatGet() == 0) {
                lbl_1_bss_4 = 4;
            }
            break;
        case 4:
            HuAudFadeOut(0x64);
            fn_1_3FC(lbl_1_bss_0);
            fn_1_72F8();
            fn_1_4824();
            fn_1_393C();
            fn_1_207C();
            fn_1_7C08();
            fn_1_68D8();
            omOvlReturnEx(1, 1);
            break;
    }
}

unkStruct *m446FlowCreate(void)
{
    s32 var_r30;
    unkStruct *temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkStruct), MEMORY_DEFAULT_NUM);
    if (temp_r3 == 0) {
        OSReport("[!] m446FlowCreate() ERROR...\n");
        return NULL;
    }
    temp_r3->unk4 = -1;
    temp_r3->unk6 = -1;
    temp_r3->unk1C = 0;
    temp_r3->unk0 = 0;
    temp_r3->unk10 = 0;
    temp_r3->unk98 = NULL;
    temp_r3->unk18 = -1;

    for (var_r30 = 0; var_r30 < 23; var_r30++) {
        temp_r3->unk38[var_r30] = 0;
    }
    temp_r3->unk24 = m446StageCreate();
    temp_r3->unk20 = fn_1_39D0();
    lbl_1_bss_10 = 0;

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        temp_r3->unk2C[var_r30] = m446PlayerCreate(var_r30, temp_r3->unk20);
        if (temp_r3->unk2C[var_r30]->unk68 != 0) {
            lbl_1_bss_10 += 1;
        }
    }
    temp_r3->unk28 = fn_1_3064();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    return temp_r3;
}

void fn_1_3FC(unkStruct *arg0)
{
    s32 var_r30;

    if (arg0->unk98) {
        HuPrcKill(arg0->unk98);
    }
    if (arg0->unk4 == -1) {
        fn_1_183C(arg0);
    }
    if (arg0->unk6 == -1) {
        MGSeqParamSet(arg0->unk6, 2, -1);
    }

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        fn_1_509C(arg0->unk2C[var_r30]);
    }
    fn_1_3B4C(arg0->unk20);
    fn_1_3180(&arg0->unk28->unk0);
    fn_1_83F0(arg0->unk24);
    HuMemDirectFree(arg0);
}

m446Func1 lbl_1_data_A0[5] = { fn_1_53C, fn_1_B78, fn_1_CA0, fn_1_C0C, fn_1_958 };

void fn_1_4B4(unkStruct *arg0)
{
    if (lbl_1_data_A0[arg0->unk0]) {
        lbl_1_data_A0[arg0->unk0](arg0);
    }
    if (omSysExitReq != 0) {
        arg0->unk0 = 5;
    }
}

void fn_1_53C(unkStruct *arg0)
{
    s32 var_r30;
    s32 var_r29;

    switch (arg0->unk10) {
        case 0:
            fn_1_6EA0(&lbl_1_data_0);
            fn_1_6EC4(&lbl_1_data_C);
            fn_1_6EE8(lbl_1_data_18);
            arg0->unk10 = 1;
            arg0->unk14 = 0;
            HuAudFXPlay(0x773);
            break;
        case 1:
            if (arg0->unk14 == 20) {
                fn_1_84AC(arg0->unk24);
            }
            if (arg0->unk14++ < 0xB4)
                break;
            arg0->unk18 = HuAudSeqPlay(0x3D);
            if (arg0->unk2C[1]->unk64 == 8) {
                arg0->unk10 = 2;
            }
            else {
                arg0->unk10 = 4;
            }
            break;
        case 2:
            arg0->unk98 = HuPrcChildCreate(fn_1_19D4, 0x64, 0x2000, 0, lbl_1_bss_C);
            lbl_1_bss_14 = 1;
            arg0->unk10 = 3;
            break;
        case 3:
            if (lbl_1_bss_14 == 0) {
                arg0->unk98 = NULL;
                arg0->unk10 = 4;
            }
            break;
        case 4:
            fn_1_6EF8(&lbl_1_data_1C, &lbl_1_data_28, &lbl_1_data_34, 0xB4);
            arg0->unk10 = 5;
            break;
        case 5:
            if (fn_1_708C())
                break;
            fn_1_860C(arg0->unk24);
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                fn_1_637C(arg0->unk2C[var_r30], 1);
            }
            arg0->unk10 = 6;
            break;
        case 6:
            fn_1_31D8(&arg0->unk28->unk0, &arg0->unk38[0], &arg0->unk94, 1);
            arg0->unk10 = 7;
            arg0->unk14 = 0;
            break;
        case 7:
            if (arg0->unk14++ < 0x78)
                break;
            fn_1_34A0(arg0->unk28, &arg0->unk38[0], arg0->unk94, 1);
            arg0->unk10 = 8;
            arg0->unk14 = 0;
            break;
        case 8:
            if (arg0->unk14++ < 0x78)
                break;

            for (var_r29 = 0; var_r29 < 2; var_r29++) {
                for (var_r30 = 0; var_r30 < 3; var_r30++) {
                    m446DeckPopCard(&arg0->unk28->unk0, &arg0->unk34);
                    m446PlayerAppendCard(arg0->unk2C[var_r29], arg0->unk34, 1);
                    fn_1_2EC0(arg0->unk34, 0);
                }
            }
            HuAudFXPlay(0x767);
            arg0->unk10 = 9;
            break;
        case 9:
            if (arg0->unk34->unk70 != 0)
                break;
            if (arg0->unk34->unk78 != 0)
                break;
            if (arg0->unk34->unk74 != 0)
                break;
            if (arg0->unk34->unk4 != 0)
                break;

            for (var_r29 = 0; var_r29 < 2; var_r29++) {
                for (var_r30 = 0; var_r30 < 3; var_r30++) {
                    fn_1_5648(arg0->unk2C[var_r29], var_r30, &arg0->unk34);
                    fn_1_272C(arg0->unk34);
                }
            }
            arg0->unk10 = 10;
            break;
        case 10:
            if (arg0->unk34->unk70 != 0)
                break;
            if (arg0->unk34->unk78 != 0)
                break;
            if (arg0->unk34->unk74 != 0)
                break;
            if (arg0->unk34->unk4 != 0)
                break;
            fn_1_46AC(arg0->unk20);

            while (m446DeckPopCard(&arg0->unk28->unk0, &arg0->unk34) != 0) {
                fn_1_3BF0(arg0->unk20, arg0->unk34, 1);
            }
            fn_1_46D0(arg0->unk20);
            if (arg0->unk18 != -1) {
                HuAudSeqFadeOut(arg0->unk18, 0x7D0);
            }
            arg0->unk10 = 11;
            arg0->unk14 = 0;
            break;
        case 11:
            if (arg0->unk14++ < 0x78)
                break;
            arg0->unk0 = 1;
            arg0->unk10 = 0;
            break;
    }
}

void fn_1_958(unkStruct *arg0)
{
    s32 var_r30;

    switch (arg0->unk10) {
        case 0:
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                fn_1_637C(arg0->unk2C[var_r30], 0);
            }
            fn_1_6EF8(&lbl_1_data_38[arg0->unk1C], &lbl_1_data_50[arg0->unk1C], &lbl_1_data_68[arg0->unk1C], 0x4E);
            arg0->unk10 = 1;
            arg0->unk14 = 0;
            break;
        case 1:
            if (arg0->unk14++ >= 0x1E) {
                fn_1_5CEC(arg0->unk2C[0]);
                arg0->unk10 = 2;
                arg0->unk14 = 0;
            }
            break;
        case 2:
            if (arg0->unk14++ >= 0x36) {
                if ((arg0->unk2C[0]->unk24 == 0) && (arg0->unk2C[1]->unk24 == 0)) {
                    fn_1_5C10(arg0->unk2C[0]);
                    if (arg0->unk2C[1]->unk64 == 8) {
                        fn_1_5B34(arg0->unk2C[1]);
                        HuAudSStreamPlay(3);
                    }
                    else {
                        fn_1_5C10(arg0->unk2C[1]);
                        HuAudSStreamPlay(4);
                    }
                }
                else if (arg0->unk2C[0]->unk24 != 0) {
                    fn_1_5B34(arg0->unk2C[0]);
                    fn_1_5C10(arg0->unk2C[1]);
                    HuAudSStreamPlay(1);
                }
                else if (arg0->unk2C[1]->unk24 != 0) {
                    fn_1_5B34(arg0->unk2C[1]);
                    fn_1_5C10(arg0->unk2C[0]);
                    if (arg0->unk2C[1]->unk64 == 8) {
                        HuAudSStreamPlay(3);
                    }
                    else {
                        HuAudSStreamPlay(1);
                    }
                }
                arg0->unk10 = 3;
                arg0->unk14 = 0;
                return;
            }
            break;
        case 3:
            if (arg0->unk14++ >= 0xD2) {
                arg0->unk0 = 5;
            }
            break;
    }
}

void fn_1_B78(unkStruct *arg0)
{
    switch (arg0->unk10) {
        case 0:
            arg0->unk18 = HuAudSeqPlay(0x3F);
            fn_1_1874(arg0);
            arg0->unk10 = 1;
            arg0->unk14 = 0;
            break;
        case 1:
            if (!fn_1_17FC(arg0)) {
                fn_1_183C(arg0);
                arg0->unk0 = 2;
                arg0->unk10 = 0;
            }
            break;
    }
}

void fn_1_C0C(unkStruct *arg0)
{
    switch (arg0->unk10) {
        case 0:
            HuAudSeqFadeOut(arg0->unk18, 0x64);
            fn_1_18B0(arg0);
            arg0->unk10 = 1;
            arg0->unk14 = 0;
            break;
        case 1:
            if (fn_1_17FC(arg0) == 0) {
                fn_1_183C(arg0);
                arg0->unk0 = 4;
                arg0->unk10 = 0;
            }
            break;
    }
}

void fn_1_CA0(unkStruct *arg0)
{
    s32 var_r29;
    unkStruct8 *var_r30;

    var_r30 = arg0->unk2C[arg0->unk1C];
    switch (arg0->unk10) {
        case 0:
            arg0->unk1C = 0;
            arg0->unk10 = 1;
            break;
        case 1:
            arg0->unkC = 300;
            arg0->unk6 = MGSeqCreate(1, arg0->unkC / 60, -1, -1);
            MGSeqPosSet(arg0->unk6, lbl_1_data_70[arg0->unk1C][0], lbl_1_data_70[arg0->unk1C][1]);
            arg0->unk10 = 2;
        case 2:
            if (fn_1_5678(var_r30, &arg0->unk34, 0) == 0) {
                if ((--arg0->unkC % 60) == 0) {
                    MGSeqParamSet(arg0->unk6, 1, arg0->unkC / 60);
                }
                if (arg0->unkC == 0) {
                    arg0->unk10 = 3;
                    arg0->unk14 = 0;
                }
            }
            else {
                arg0->unk10 = 4;
            }
            break;
        case 3:
            if (arg0->unk14++ >= 60) {
                fn_1_5678(var_r30, &arg0->unk34, 1);
                arg0->unk10 = 4;
            }
            break;
        case 4:
            MGSeqParamSet(arg0->unk6, 2, -1);
            arg0->unk6 = -1;
            m446PlayerRemoveCard(var_r30, arg0->unk34, 3);
            arg0->unk10 = 5;
            break;
        case 5:
            if (arg0->unk34->unk70 == 0 && arg0->unk34->unk78 == 0 && arg0->unk34->unk74 == 0 && arg0->unk34->unk4 == 0) {
                fn_1_3BF0(arg0->unk20, arg0->unk34, 4);
                arg0->unk10 = 6;
            }
            break;
        case 6:
            if (arg0->unk34->unk70 == 0 && arg0->unk34->unk78 == 0 && arg0->unk34->unk74 == 0 && arg0->unk34->unk4 == 0) {
                fn_1_2EC0(arg0->unk34, 1);
                arg0->unkC = 300;
                arg0->unk6 = MGSeqCreate(1, arg0->unkC / 60, -1, -1);
                MGSeqPosSet(arg0->unk6, lbl_1_data_70[arg0->unk1C][0], lbl_1_data_70[arg0->unk1C][1]);
                fn_1_4000(arg0->unk20, arg0->unk1C == 1 >> 5);
                arg0->unk10 = 7;
            }
            else
                break;
        case 7:
            if (fn_1_4088(arg0->unk20, var_r30->unk64, var_r30->unk66, arg0->unk1C == 1, &arg0->unk34, 0) == 0) {
                if ((--arg0->unkC % 60) == 0) {
                    MGSeqParamSet(arg0->unk6, 1, arg0->unkC / 60);
                }
                if (arg0->unkC <= 0) {
                    if (fn_1_4088(arg0->unk20, var_r30->unk64, var_r30->unk66, arg0->unk1C == 1, &arg0->unk34, 2) == 0) {
                        fn_1_4000(arg0->unk20, arg0->unk1C == 1 >> 5);
                        arg0->unk10 = 8;
                        arg0->unk14 = 0;
                        break;
                    }
                }
                else
                    break;
            }
            arg0->unk10 = 9;
            break;
        case 8:
            fn_1_4088(arg0->unk20, var_r30->unk64, var_r30->unk66, arg0->unk1C == 1, &arg0->unk34, 1);
            if (arg0->unk14++ >= 0x1E) {
                fn_1_4088(arg0->unk20, var_r30->unk64, var_r30->unk66, arg0->unk1C == 1, &arg0->unk34, 2);
                arg0->unk10 = 9;
            }
            break;
        case 9:
            MGSeqParamSet(arg0->unk6, 2, -1);
            arg0->unk6 = -1;
            fn_1_2EC0(arg0->unk34, 0);
            fn_1_3EB4(arg0->unk20, arg0->unk34, 3);
            arg0->unk10 = 10;
            break;
        case 10:
            if (arg0->unk34->unk70 == 0 && arg0->unk34->unk78 == 0 && arg0->unk34->unk74 == 0 && arg0->unk34->unk4 == 0) {
                if (arg0->unk34->unk0 == 4) {
                    arg0->unk10 = 13;
                }
                else {
                    m446PlayerAppendCard(var_r30, arg0->unk34, 4);
                    arg0->unk10 = 11;
                }
            }
            break;
        case 11:
            if (arg0->unk34->unk70 == 0 && arg0->unk34->unk78 == 0 && arg0->unk34->unk74 == 0 && arg0->unk34->unk4 == 0) {
                if (var_r30->unk24 != 0) {
                    arg0->unk10 = 24;
                }
                else {
                    arg0->unk10 = 12;
                }
            }
            break;
        case 12:
            if (fn_1_4720(arg0->unk20, 5) == 0) {
                arg0->unk1C = 1;
                arg0->unk10 = 25;
                break;
            }
            else if (arg0->unk1C == 0) {
                arg0->unk1C = 1;
            }
            else {
                arg0->unk1C = 0;
            }
            arg0->unk10 = 1;
            break;
        case 13:
            fn_1_64BC(var_r30, 0, 60);
            HuAudFXPlay(0x4E);
            arg0->unk10 = 14;
        case 14:
            fn_1_2A94(arg0->unk34);
            arg0->unk10 = 15;
            break;
        case 15:
            if (arg0->unk34->unk70 == 0 && arg0->unk34->unk78 == 0 && arg0->unk34->unk74 == 0 && arg0->unk34->unk4 == 0) {
                fn_1_3EB4((unkStruct6 *)var_r30, arg0->unk34, 4);
                fn_1_2688(arg0->unk34);
                for (var_r29 = 0; var_r29 < 3; var_r29++) {
                    fn_1_5648(var_r30, var_r29, &arg0->unk34);
                    if (arg0->unk34) {
                        m446PlayerRemoveCard(var_r30, arg0->unk34, 4);
                        fn_1_3BF0(arg0->unk20, arg0->unk34, 3);
                    }
                }

                arg0->unk10 = 16;
                arg0->unk14 = 0;
            }
            break;
        case 16:
            if (arg0->unk14++ >= 60) {
                for (var_r29 = 0; var_r29 < 21; var_r29++) {
                    fn_1_3FD0(arg0->unk20, var_r29, &arg0->unk34);
                    if (arg0->unk34) {
                        fn_1_2794(arg0->unk34);
                        fn_1_2EC0(arg0->unk34, 1);
                    }
                }
                arg0->unk10 = 17;
                arg0->unk14 = 0;
            }
            break;
        case 17:
            if (arg0->unk14++ >= 60) {
                for (var_r29 = 0; var_r29 < 21; var_r29++) {
                    fn_1_3FD0(arg0->unk20, var_r29, &arg0->unk34);
                    if (arg0->unk34) {
                        fn_1_3EB4(arg0->unk20, arg0->unk34, 4);
                        m446DeckPushCard(arg0->unk28, arg0->unk34, 2);
                    }
                }
                arg0->unk10 = 18;
                arg0->unk14 = 0;
            }
            break;
        case 18:
            if (arg0->unk14++ >= 60) {
                fn_1_31D8((unkStruct2 **)arg0->unk28, &arg0->unk38[0], &arg0->unk94, 1);
                arg0->unk10 = 19;
                arg0->unk14 = 0;
            }
            break;
        case 19:
            if (arg0->unk14++ >= 120) {
                fn_1_34A0(arg0->unk28, &arg0->unk38[0], arg0->unk94, 1);
                arg0->unk10 = 20;
                arg0->unk14 = 0;
            }
            break;
        case 20:
            if (arg0->unk14++ >= 120) {
                for (var_r29 = 0; var_r29 < 3; var_r29++) {
                    m446DeckPopCard((unkStruct2 **)arg0->unk28, &arg0->unk34);
                    m446PlayerAppendCard(var_r30, arg0->unk34, 1);
                    fn_1_2EC0(arg0->unk34, 0);
                }
                HuAudFXPlay(0x767);
                arg0->unk10 = 21;
            }
            break;
        case 21:
            if (arg0->unk34->unk70 == 0 && arg0->unk34->unk78 == 0 && arg0->unk34->unk74 == 0 && arg0->unk34->unk4 == 0) {
                for (var_r29 = 0; var_r29 < 3; var_r29++) {
                    fn_1_5648(var_r30, var_r29, &arg0->unk34);
                    fn_1_272C(arg0->unk34);
                }

                arg0->unk10 = 22;
            }
            break;
        case 22:
            if (arg0->unk34->unk70 == 0 && arg0->unk34->unk78 == 0 && arg0->unk34->unk74 == 0 && arg0->unk34->unk4 == 0) {
                fn_1_46AC(arg0->unk20);

                while (m446DeckPopCard((unkStruct2 **)arg0->unk28, &arg0->unk34)) {
                    fn_1_3BF0(arg0->unk20, arg0->unk34, 1);
                }
                fn_1_46D0(arg0->unk20);
                arg0->unk10 = 23;
                arg0->unk14 = 0;
            }
            break;
        case 23:
            if (arg0->unk14++ >= 120) {
                arg0->unk10 = 12;
            }
            break;
        case 24:
            for (var_r29 = 0; var_r29 < 3; var_r29++) {
                fn_1_5648(var_r30, var_r29, &arg0->unk34);
                if (arg0->unk34) {
                    fn_1_2D94(arg0->unk34);
                }
            }
            GWPlayerCoinWinAdd(arg0->unk1C, 10);
        case 25:
            arg0->unk0 = 3;
            arg0->unk10 = 0;
            break;
    }
}

s32 fn_1_17FC(unkStruct *arg0)
{
    return MGSeqStatGet(arg0->unk4) != 0;
}

void fn_1_183C(unkStruct *arg0)
{
    MGSeqKill(arg0->unk4);
    arg0->unk4 = -1;
}

void fn_1_1874(unkStruct *arg0)
{
    arg0->unk4 = MGSeqCreate(3, 0);
}

void fn_1_18B0(unkStruct *arg0)
{
    arg0->unk4 = MGSeqCreate(3, 1);
}

void fn_1_18EC(s16 arg0, s32 arg1)
{
    HuWinComKeyReset();
    if (lbl_1_bss_10 == 2) {
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, arg1);
    }
    winData[arg0].active_pad = 1;
    HuWinMesWait(arg0);
}

s32 fn_1_1970(s16 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    if (lbl_1_bss_10 == 2) {
        HuPrcSleep(arg3);
        return arg2;
    }
    else {
        return HuWinChoiceGet(arg0, arg1);
    }
}

static const s32 lbl_1_rodata_18[12] = { MAKE_MESSID(0x18, 0x03), MAKE_MESSID(0x18, 0x04), MAKE_MESSID(0x18, 0x05), MAKE_MESSID(0x18, 0x06),
    MAKE_MESSID(0x18, 0x07), MAKE_MESSID(0x18, 0x08), MAKE_MESSID(0x18, 0x09), MAKE_MESSID(0x18, 0x0A), MAKE_MESSID(0x18, 0x0B),
    MAKE_MESSID(0x18, 0x0C), MAKE_MESSID(0x18, 0x0D), 0 };

void fn_1_19D4(void)
{
    s16 temp_r3;
    s16 var_r30;
    s32 var_r29;
    u32 temp_r27;

    temp_r3 = HuWinExCreateStyled(-10000.0f, 40.0f, 0x138, 0x78, -1, 1);
    HuWinExAnimIn(temp_r3);
    HuWinBGTPLvlSet(temp_r3, 0.8f);
    HuWinMesSpeedSet(temp_r3, 1);
    HuWinMesColSet(temp_r3, 0);
    HuWinMesSet(temp_r3, MAKE_MESSID(0x18, 0x01));
    fn_1_18EC(temp_r3, 0x3C);
    if (lbl_1_bss_10 < 2) {
        HuWinMesColSet(temp_r3, 0);
        HuWinMesSet(temp_r3, MAKE_MESSID(0x18, 0x02));
        var_r30 = fn_1_1970(temp_r3, 0, 1, 0x3C);
    }
    else {
        var_r30 = 1;
    }
    if (var_r30 == 0) {
        var_r29 = 0;
        while ((temp_r27 = lbl_1_rodata_18[var_r29++]) != 0) {
            HuWinMesColSet(temp_r3, 0);
            HuWinMesSet(temp_r3, temp_r27);
            fn_1_18EC(temp_r3, 0x3C);
        }
    }
    else {
        HuWinMesColSet(temp_r3, 0);
        HuWinMesSet(temp_r3, MAKE_MESSID(0x18, 0x0D));
        fn_1_18EC(temp_r3, 0x3C);
    }
    HuWinExAnimOut(temp_r3);
    HuWinExCleanup(temp_r3);
    lbl_1_bss_14 = 0;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}
