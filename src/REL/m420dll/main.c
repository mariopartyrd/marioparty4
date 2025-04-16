#include "ext_math.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/wipe.h"

#include "REL/m420dll.h"
#include "version.h"

#ifndef __MWERKS__
#include "game/audio.h"
#endif

s32 fn_1_198(void);
void fn_1_3D4(void);
void fn_1_43C(void);
void fn_1_D14(s32 arg0, s32 arg1);
s32 fn_1_D98(void);
void fn_1_F48(void);
void fn_1_F74(const Vec *arg0, s32 arg1);
void fn_1_1030(const Vec *arg0, s32 arg1);
void fn_1_10EC(float arg8, s32 arg0);
void fn_1_118(void);

s32 lbl_1_bss_2C;
Process *lbl_1_bss_28;
M420DllPlayerStruct *lbl_1_bss_18[4];
s16 lbl_1_bss_14;
s16 lbl_1_bss_12;
s16 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
Process *lbl_1_bss_4;
Process *lbl_1_bss_0;

static const M420DllUnkStruct lbl_1_rodata_10[3] = {
    { { 0.0f, 1040.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 680.0f },
    { { 0.0f, 800.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 680.0f },
    { { 0.0f, 310.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, 1950.0f },
};

void ObjectSetup(void)
{
    lbl_1_bss_4 = omInitObjMan(1, 0x2000);
    omGameSysInit(lbl_1_bss_4);
    lbl_1_bss_0 = HuPrcChildCreate(fn_1_118, 0x3E8, 0x4000, 0, lbl_1_bss_4);
    fn_1_198();
}

void fn_1_118(void)
{
    while (omSysExitReq == 0) {
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFadeOut(0x64);
    fn_1_3D4();
    HuPrcVSleep();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

s32 fn_1_198(void)
{
    s32 sp8[3];
    s32 var_r31;
    s32 var_r30;

    Vec sp14[3] = { { 0.0f, 4000.0f, 100.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
    frand();
    fn_1_8934();
    fn_1_4964();
    fn_1_D98();
    fn_1_D14(0, 1);
    Hu3DShadowCreate(30.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&sp14[0], &sp14[1], &sp14[2]);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        sp8[var_r31] = 0;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        switch (GWPlayerCfg[var_r31].group) {
            case 0:
                lbl_1_bss_18[0] = fn_1_1B8C(var_r31, 0);
                break;

            default:
                do {
                    var_r30 = fn_1_8944() % 3;
                } while (sp8[var_r30] != 0);
                sp8[var_r30] = 1;
                lbl_1_bss_18[var_r30 + 1] = fn_1_1B8C(var_r31, var_r30 + 1);
                break;
        }
    }
    lbl_1_bss_18[1]->unk_E8 = NULL;
    lbl_1_bss_18[2]->unk_E8 = lbl_1_bss_18[1];
    lbl_1_bss_18[3]->unk_E8 = lbl_1_bss_18[2];
    lbl_1_bss_28 = HuPrcChildCreate(fn_1_43C, 0x3E9, 0x4000, 0, lbl_1_bss_4);
    return 1;
}

void fn_1_3D4(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_1_1E14(lbl_1_bss_18[var_r31]);
    }
    fn_1_596C();
    fn_1_F48();
    HuPrcKill(lbl_1_bss_28);
}

void fn_1_43C(void)
{
    s32 var_r31;
    s32 var_r30;

    lbl_1_bss_C = 0;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 0x3C);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_59F4(0);
    fn_1_D14(1, 0x50);
    HuPrcSleep(0x4E);
    fn_1_D14(2, 0x3C);
    HuPrcSleep(0xB4);
    fn_1_59F4(2);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_18[var_r31]->unk_48 = 9;
    }
    lbl_1_bss_8 = HuAudSeqPlay(0x48);
    lbl_1_bss_10 = MGSeqCreate(3, 0);

    while (MGSeqStatGet(lbl_1_bss_10) != 0) {
        HuPrcVSleep();
    }
    MGSeqKill(lbl_1_bss_10);
    lbl_1_bss_12 = 60 * REFRESH_RATE;
    lbl_1_bss_14 = MGSeqCreate(1, lbl_1_bss_12 / REFRESH_RATE, -1, -1);
    var_r30 = 1;
    while (TRUE) {
        if (lbl_1_bss_18[0]->unk_48 == 0) {
            lbl_1_bss_18[0]->unk_48 = 1;
        }
        if ((lbl_1_bss_18[var_r30]->unk_48 == 0) && (lbl_1_bss_12 > 5)) {
            lbl_1_bss_18[var_r30]->unk_48 = 3;
        }
        if ((lbl_1_bss_18[var_r30]->unk_00_field1) && (var_r30 != 1)) {
            lbl_1_bss_18[var_r30 - 1]->unk_48 = 4;
        }
        if (lbl_1_bss_18[var_r30]->unk_48 == 6) {
            var_r30++;
            if (var_r30 > 3) {
                var_r30 = 1;
                lbl_1_bss_18[3]->unk_48 = 0;
            }
        }
        if (lbl_1_bss_12 >= 0) {
            if (((--lbl_1_bss_12) % REFRESH_RATE) == 0) {
                MGSeqParamSet(lbl_1_bss_14, 1, lbl_1_bss_12 / REFRESH_RATE);
            }
        }
        if ((fn_1_67E8(0) == 0) && (fn_1_67E8(1) == 0) && (lbl_1_bss_12 > 0)) {
            HuPrcVSleep();
        }
        else {
            break;
        }
    }
    if ((fn_1_67E8(0) != 0) && (fn_1_67E8(1) != 0)) {
        lbl_1_bss_C = 3;
    }
    else if (fn_1_67E8(0) != 0) {
        lbl_1_bss_C = 1;
    }
    else if (fn_1_67E8(1) != 0) {
        lbl_1_bss_C = 2;
    }
    else {
        lbl_1_bss_C = 3;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_18[var_r31]->unk_48 = 0xB;
    }
    HuPrcVSleep();
    MGSeqParamSet(lbl_1_bss_14, 2, -1);
    HuAudSeqFadeOut(lbl_1_bss_8, 0x64);
    lbl_1_bss_10 = MGSeqCreate(3, 1);

    while (MGSeqStatGet(lbl_1_bss_10) != 0) {
        HuPrcVSleep();
    }
    MGSeqKill(lbl_1_bss_10);
    fn_1_6728();
    HuPrcSleep(0x3C);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_18[var_r31]->unk_48 = 0xA;
    }
    HuPrcSleep(0x3C);
    if (lbl_1_bss_C == 3) {
        lbl_1_bss_10 = MGSeqCreate(3, 2);
        HuAudSStreamPlay(4);
        lbl_1_bss_18[0]->unk_48 = 8;
        lbl_1_bss_18[1]->unk_48 = 8;
        lbl_1_bss_18[2]->unk_48 = 8;
        lbl_1_bss_18[3]->unk_48 = 8;
    }
    else {
        fn_1_59F4(1);
        while (fn_1_6810() == 0) {
            HuPrcVSleep();
        }
        if (lbl_1_bss_C == 1) {
            lbl_1_bss_10 = MGSeqCreate(5, 3, lbl_1_bss_18[0]->unk_0A, -1, -1, -1);
            HuAudSStreamPlay(1);
            lbl_1_bss_18[0]->unk_48 = 7;
            lbl_1_bss_18[1]->unk_48 = 8;
            lbl_1_bss_18[2]->unk_48 = 8;
            lbl_1_bss_18[3]->unk_48 = 8;
            GWPlayerCoinWinAdd(lbl_1_bss_18[0]->unk_04, 10);
        }
        else {
            lbl_1_bss_10 = MGSeqCreate(5, 3, lbl_1_bss_18[1]->unk_0A, lbl_1_bss_18[2]->unk_0A, lbl_1_bss_18[3]->unk_0A, -1);
            HuAudSStreamPlay(1);
            lbl_1_bss_18[0]->unk_48 = 8;
            lbl_1_bss_18[1]->unk_48 = 7;
            lbl_1_bss_18[2]->unk_48 = 7;
            lbl_1_bss_18[3]->unk_48 = 7;
            GWPlayerCoinWinAdd(lbl_1_bss_18[1]->unk_04, 10);
            GWPlayerCoinWinAdd(lbl_1_bss_18[2]->unk_04, 10);
            GWPlayerCoinWinAdd(lbl_1_bss_18[3]->unk_04, 10);
        }
    }
    HuPrcSleep(0xD2);
    omSysExitReq = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_D14(s32 arg0, s32 arg1)
{
    fn_1_F74(&lbl_1_rodata_10[arg0].unk_00, arg1);
    fn_1_1030(&lbl_1_rodata_10[arg0].unk_0C, arg1);
    fn_1_10EC(lbl_1_rodata_10[arg0].unk_18, arg1);
}
