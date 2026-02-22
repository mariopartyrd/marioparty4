#include "ext_math.h"
#include "game/board/main.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/audio.h"
#include "game/hsfex.h"
#include "stdio.h"
#endif

#include "REL/mpexDll.h"

typedef void (*MpexDllUnkFunc2)(omObjData *, ...);

typedef struct MpexDllUnkStruct3 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} MpexDllUnkStruct3; /* size = 0x14 */

typedef struct MpexDllUnkStruct4 {
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ MpexDllUnkFunc2 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ char unk14[0x14];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ char unk2C[0x1C];
} MpexDllUnkStruct4; /* size = 0x48 */

extern s32 rand8(void);
float fn_1_1B52C(float arg8, float arg9, float argA, float argB);
float fn_1_1B574(float arg0, float arg1, float arg2, float arg3);
float fn_1_1B64C(float arg0, float arg1, float arg2, float arg3);

void fn_1_1015C(void);
void fn_1_10228(void);
void fn_1_10268(s32 arg0);
void fn_1_1045C(void);
void fn_1_107EC(void);
void fn_1_1085C(void);
void fn_1_10ABC(void);
void fn_1_10C30(void);
void fn_1_110F8(void);
void fn_1_114D4(void);
void fn_1_115A0(void);
void fn_1_115E0(s32 arg0);
void fn_1_117D4(void);
void fn_1_11930(void);
void fn_1_11984(void);
void fn_1_119E0(void);
void fn_1_11A3C(s32 arg0);
void fn_1_11E28(void);
void fn_1_11FC0(omObjData *object, MpexDllUnkStruct4 *arg1);
void fn_1_121E8(void);
void fn_1_125DC(float *arg0, s32 arg1);
void fn_1_32D8(void);
void fn_1_5D40(omObjData *arg0, MpexDllUnkStruct4 *arg1);
void fn_1_7D80(void);
void fn_1_7FC4(omObjData *arg0, MpexDllUnkStruct4 *arg1);
void fn_1_8320(void);
void fn_1_8ADC(void);
void fn_1_901C(omObjData *arg0, MpexDllUnkStruct4 *arg1);
void fn_1_9430(omObjData *arg0, MpexDllUnkStruct4 *arg1);
void fn_1_96B4(void);
void fn_1_A608(void);
void fn_1_AD34(void);
void fn_1_B004(void);
void fn_1_B210(void);
s32 fn_1_B248(s32 arg0, s32 arg1);
void fn_1_B2E4(s32 arg0);
void fn_1_B7F4(s32 arg0);
void fn_1_B870(s32 arg0);
void fn_1_B9A8(s32);
void fn_1_BC18(void);
void fn_1_BCD8(void);
u32 fn_1_BD10(s32 arg0, s32 arg1);
void fn_1_BD78(s32 arg0, s32 arg1);
void fn_1_C0DC(s32 arg0, s32);
void fn_1_C4D4(s32);
void fn_1_C544(void);
void fn_1_C860(void);
s32 fn_1_C898(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_CF10(s32 arg0);
void fn_1_D3AC(s32 arg0);
void fn_1_D468(s32 arg0);
void fn_1_D6AC(s32 arg0);
void fn_1_DBD0(s32 arg0);
void fn_1_E174(void);
void fn_1_E384(void);
void fn_1_E568(void);
void fn_1_EB1C(void);
void fn_1_ED78(s32 arg0, s32 arg1);
void fn_1_F0C0(void);
void fn_1_F40C(void);
void fn_1_F47C(void);
void fn_1_F730(void);
void fn_1_F8A4(void);
void fn_1_FDA0(void);

float lbl_1_data_240[21] = {
    0.0f,
    0.0f,
    0.0f,
    -250.0f,
    0.0f,
    0.0f,
    250.0f,
    0.0f,
    0.0f,
    0.0f,
    500.0f,
    0.0f,
    -1000.0f,
    0.0f,
    0.0f,
    1000.0f,
    0.0f,
    0.0f,
    0.0f,
    1000.0f,
    0.0f,
};

MpexDllUnkStruct4 lbl_1_bss_3F8;
MpexDllUnkStruct4 lbl_1_bss_3B0;
MpexDllUnkStruct4 lbl_1_bss_2D8[3];
MpexDllUnkStruct4 lbl_1_bss_1B8[4];
s32 lbl_1_bss_1B4;
s32 lbl_1_bss_1B0;
s32 lbl_1_bss_1AC;
s32 lbl_1_bss_180[0xB];
MpexDllUnkStruct3 lbl_1_bss_130[4];
char lbl_1_bss_120[16];
char lbl_1_bss_118[8];
char lbl_1_bss_110[8];
s32 lbl_1_bss_10C;
s32 lbl_1_bss_108;
s32 lbl_1_bss_104;
char lbl_1_bss_FC[8];
char lbl_1_bss_F4[8];
char lbl_1_bss_EC[8];
char lbl_1_bss_E4[8];
s32 lbl_1_bss_E0;
s32 lbl_1_bss_C8[6];
s32 lbl_1_bss_C4;
s32 lbl_1_bss_C0;
s32 lbl_1_bss_BC;
float lbl_1_bss_B8;
s32 lbl_1_bss_B4;
s32 lbl_1_bss_B0;
u32 lbl_1_bss_AC;
Process *lbl_1_bss_A8;

Process *fn_1_3044(Process *arg0)
{
    s32 var_r31;

    lbl_1_bss_A8 = arg0;
    if (omovlevtno == 0) {
        mgGameStatBackup = GWGameStat;
    }
    fn_1_298();
    fn_1_374();
    fn_1_1B810();
    fn_1_910(fn_1_96B4);
    lbl_1_bss_180[0] = 1;
    lbl_1_bss_180[1] = 1;
    lbl_1_bss_180[2] = GWMGAvailGet(omMgIndexGet(0x40) + 0x191);
    lbl_1_bss_180[3] = GWMGAvailGet(omMgIndexGet(0xB) + 0x191);
    lbl_1_bss_180[4] = GWMGAvailGet(omMgIndexGet(0x13) + 0x191);
    lbl_1_bss_180[5] = 1;
    lbl_1_bss_180[6] = 1;
    lbl_1_bss_180[7] = 1;
    lbl_1_bss_180[8] = 1;
    lbl_1_bss_180[9] = GWMGAvailGet(omMgIndexGet(0x1B) + 0x191);
    fn_1_121E8();
    for (var_r31 = 0; var_r31 < 0xA; var_r31++) {
        if (lbl_1_bss_180[var_r31] == 0) {
            break;
        }
    }
    if (var_r31 == 0xA) {
        lbl_1_bss_180[0xA] = 1;
    }
    else {
        lbl_1_bss_180[0xA] = 0;
    }
    if (omovlevtno == 1) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            HuPrcChildCreate(fn_1_8320, 0x7D0, 0x2000, 0, HuPrcCurrentGet());
        }
    }
    HuPrcChildCreate(fn_1_7D80, 0x7D0, 0x2000, 0, HuPrcCurrentGet());
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuPrcChildCreate(fn_1_8ADC, 0x7D0, 0x2000, 0, HuPrcCurrentGet());
    }
    fn_1_1264C(lbl_1_bss_A8);

    return HuPrcChildCreate(fn_1_32D8, 0x3E8, 0x2000, 0, HuPrcCurrentGet());
}

void fn_1_32D8(void)
{
    omObjData *var_r31;

    var_r31 = NULL;
    var_r31 = omAddObjEx(lbl_1_bss_A8, 0x2000, 0x10, 0x10, -1, NULL);
    lbl_1_bss_3F8.unk_00 = var_r31;
    lbl_1_bss_3F8.unk_04 = (MpexDllUnkFunc2)fn_1_5D40;
    while (TRUE) {
        fn_1_1B7D0(1);
        if (lbl_1_bss_3F8.unk_04 == NULL) {
            continue;
        }
        lbl_1_bss_3F8.unk_04(lbl_1_bss_3F8.unk_00, &lbl_1_bss_3F8);
    }
}

void fn_1_3384(void)
{
    fn_1_1B7D0(0x1E);
    HuAudFadeOut(0x3E8);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);

    while (WipeStatGet() != 0) {
        fn_1_1B7D0(1);
    }
    HuAudAllStop();
    omOvlReturnEx(1, 1);

    while (TRUE) {
        fn_1_1B7D0(1);
    }
}

void fn_1_33F8(void)
{
    s16 var_r31;

    if (SLSaveFlagGet() != 0) {
        Hu3DAllKill();
        HuSprClose();
        HuSprInit();
        espInit();
        HuPrcVSleep();
        var_r31 = espEntry(0x860020, 0x1388, 0);
        espPosSet(var_r31, 288.0f, 240.0f);
        espAttrReset(var_r31, HUSPR_ATTR_DISPOFF);
        Hu3DBGColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        SLCommonSet();
        if (SLSave() == 0) {
            GWSystem.save_mode = 1;
        }
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
    }
}

void fn_1_3508(void)
{
    s16 var_r31;

    fn_1_1B7D0(0x1E);
    HuAudFadeOut(0x3E8);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);

    while (WipeStatGet() != 0) {
        fn_1_1B7D0(1);
    }

    HuAudAllStop();
    CharModelKill(-1);
    MGSeqKillAll();
    if (omovlevtno != 0) {
        fn_1_1B7D0(0x3C);
        fn_1_33F8();
    }
    mgQuitExtraF = 0;
    omOvlReturnEx(1, 1);

    while (TRUE) {
        fn_1_1B7D0(1);
    }
}

void fn_1_36A4(void)
{
    omOvlHisData *sp8;

    fn_1_1B7D0(0x1E);
    HuAudSStreamAllFadeOut(0x3E8);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_1B7D0(1);
    }
    CharModelKill(-1);
    MGSeqKillAll();
    sp8 = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MPEX, 2, 0);
    mgQuitExtraF = 0;
    omOvlCallEx(OVL_ZTAR, 1, 0, 0);
    while (TRUE) {
        fn_1_1B7D0(1);
    }
}

void fn_1_3758(s32 arg0, s32 arg1)
{
    s32 spC[10][3] = {
        { 0x60, 0x01, 0x00 },
        { 0x61, 0x01, 0x01 },
        { 0x45, 0x01, 0x02 },
        { 0x3C, 0x01, 0x03 },
        { 0x3B, 0x01, 0x04 },
        { 0x32, 0x01, 0x05 },
        { 0x41, 0x01, 0x06 },
        { 0x42, 0x01, 0x07 },
        { 0x43, 0x01, 0x08 },
        { 0x44, 0x01, 0x09 },
    };
    omOvlHisData *sp8;
    s32 var_r29;

    fn_1_1B7D0(0x1E);
    HuAudSeqAllFadeOut(0x3E8);
    HuAudSStreamAllFadeOut(0x3E8);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_1B7D0(1);
    }
    if (arg0 == 0 || arg0 == 1) {
        var_r29 = (arg1 * 0xA) + 0xA;
        BoardPartyConfigSet(0, 0, 0, var_r29, 0, 0, 0, 0);
        BoardSaveInit(arg0 + 7);
        spC[arg0][2] += (arg1 * 0xA);
    }
    else if (arg0 == 4) {
        GWSystem.mg_type = arg1;
        spC[arg0][2] += (arg1 * 0xA);
    }

    sp8 = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MPEX, spC[arg0][1], spC[arg0][2]);
    HuDataDirClose(DATA_MAKE_NUM(DATADIR_MPEX, 0x00));
    HuDataDirClose(0x150000);
    CharModelKill(-1);
    CharKill(-1);
    CharARAMOpen(GWPlayerCfg[0].character);
    CharARAMOpen(GWPlayerCfg[1].character);
    CharARAMOpen(GWPlayerCfg[2].character);
    CharARAMOpen(GWPlayerCfg[3].character);
    HuAudAllStop();
    if (arg0 > 1) {
        mgPracticeEnableF = 1;
    }
    mgQuitExtraF = 0;
    omOvlCallEx(spC[arg0][0], 1, 0, 0);
    while (TRUE) {
        fn_1_1B7D0(1);
    }
}

s32 lbl_1_data_294 = -1;
s32 lbl_1_data_298 = -1;

void fn_1_397C(void)
{
    if (omovlevtno != 2) {
        lbl_1_data_298 = HuAudSeqPlay(0x2E);
    }
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_1B7D0(1);
    }
    fn_1_1B7D0(0x3C);
}

void fn_1_39F4(void)
{
    fn_1_1B834();
    fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 3, 0xF, 1);
    fn_1_1BA78(0x330000, -1, -1);
    fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 1, 0xF, 1);
    fn_1_1B9F4();
    fn_1_1B7D0(0x3C);
    fn_1_1B834();
    fn_1_1BA78(0x330001, 5, -1);
    if (fn_1_1BBA4(1) == 0) {
        fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 3, 0xF, 1);
        fn_1_1BA78(0x330002, -1, -1);
        fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 1, 0xF, 1);
    }
    fn_1_1B9F4();
    fn_1_1B7D0(0x3C);
}

void fn_1_3AF8(void)
{
    s16 var_r29;
    s32 var_r30;
    s32 var_r31;

    var_r31 = -1;
    var_r30 = 0;
    fn_1_1B834();
    while (TRUE) {
        fn_1_1B7D0(1);
        fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 3, 0xF, 1);
        fn_1_1BA78(0x330003, -1, -1);
        fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 1, 0xF, 1);
        fn_1_1BF1C(0x33004C);
        var_r31 = -1;
        lbl_1_bss_3B0.unk_08 = 0;
        lbl_1_bss_3B0.unk_04 = (MpexDllUnkFunc2)fn_1_11FC0;
        while (TRUE) {
            fn_1_1B7D0(1);
            if (var_r31 != lbl_1_bss_3B0.unk_08) {
                HuAudFXPlay(0);
                fn_1_11A3C(var_r31);
                var_r31 = lbl_1_bss_3B0.unk_08;
                switch (lbl_1_bss_3B0.unk_08) {
                    case 0:
                        fn_1_1BA78(0x330005, -1, 1);
                        break;
                    case 1:
                        fn_1_1BA78(0x330012, -1, 1);
                        break;
                    case 2:
                        fn_1_1BA78(0x330023, -1, 1);
                        break;
                }
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                HuAudFXPlay(2);
                var_r30 = 1;
                break;
            }
            else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                var_r30 = 0;
                break;
            }
            else {
                if (lbl_1_bss_180[0xA] == 1) {
                    if (HuPadStkX[0] <= -0x1E) {
                        lbl_1_bss_3B0.unk_08 = 0;
                    }
                    else if (HuPadStkX[0] >= 0x1E) {
                        lbl_1_bss_3B0.unk_08 = 1;
                    }
                    else if (HuPadStkY[0] >= 0x1E) {
                        lbl_1_bss_3B0.unk_08 = 2;
                    }
                    else if ((HuPadStkY[0] <= -0x1E) && (lbl_1_bss_3B0.unk_08 == 2)) {
                        if (HuPadStkX[0] >= 5) {
                            lbl_1_bss_3B0.unk_08 = 1;
                        }
                        else {
                            lbl_1_bss_3B0.unk_08 = 0;
                        }
                    }
                }
                else if (HuPadStkX[0] <= -0x1E) {
                    lbl_1_bss_3B0.unk_08 = 0;
                }
                else if (HuPadStkX[0] >= 0x1E) {
                    lbl_1_bss_3B0.unk_08 = 1;
                }
            }
        }
        lbl_1_bss_3B0.unk_04 = NULL;
        fn_1_1C120();
        if (var_r30 == 0) {
            fn_1_11E28();
            fn_1_1BA78(0x330004, 5, -1);
            if (fn_1_1BBA4(1) == 0) {
                fn_1_1B9F4();
                fn_1_3508();
            }
            continue;
        }
        break;
    }
    fn_1_11E28();
    fn_1_1B9F4();
    lbl_1_bss_1B4 = lbl_1_bss_3B0.unk_08;
}

void fn_1_4014(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_2D8[var_r31].unk_04 = (MpexDllUnkFunc2)fn_1_901C;
    }
    do {
        fn_1_1B7D0(1);
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            if (lbl_1_bss_2D8[var_r31].unk_04 != NULL) {
                break;
            }
        }
    } while (var_r31 != 3);
}

void fn_1_40AC(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_2D8[var_r31].unk_04 = (MpexDllUnkFunc2)fn_1_9430;
    }
    do {
        fn_1_1B7D0(1);
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            if (lbl_1_bss_2D8[var_r31].unk_04 != NULL) {
                break;
            }
        }
    } while (var_r31 != 3);
}

s32 fn_1_4144(s32 arg0)
{
    s32 var_r31;

    var_r31 = 1;
    var_r31 = fn_1_140B0(0, arg0);
    return var_r31;
}

s32 fn_1_4184(s32 arg0)
{
    s32 var_r31 = 0;
    s32 var_r30 = -1;
    if (arg0 == 0) {
        fn_1_148BC(lbl_1_bss_1B4);
    }
    fn_1_F8A4();
    fn_1_1B834();
    if (lbl_1_data_294 == -1) {
        fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 3, 0xF, 1);
        fn_1_1BA78(0x330007, -1, -1);
        fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 1, 0xF, 1);
    }
    else {
        lbl_1_bss_3B0.unk_0C = lbl_1_data_294;
        lbl_1_data_294 = -1;
    }
    fn_1_1B7D0(1);
    fn_1_1BF1C(0x33004D);
    fn_1_1015C();
    while (TRUE) {
        fn_1_1B7D0(1);
        if (var_r30 != lbl_1_bss_3B0.unk_0C) {
            var_r30 = lbl_1_bss_3B0.unk_0C;
            HuAudFXPlay(0);
            if (lbl_1_bss_180[lbl_1_bss_3B0.unk_0C] == 1) {
                fn_1_1BA78(lbl_1_bss_3B0.unk_0C + MAKE_MESSID(0x33, 0x08), -1, 1);
            }
            else {
                fn_1_1BA78(0x33002E, -1, 1);
            }
            fn_1_1B7D0(1);
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            if (lbl_1_bss_180[lbl_1_bss_3B0.unk_0C] == 1) {
                HuAudFXPlay(2);
                lbl_1_data_294 = lbl_1_bss_3B0.unk_0C;
                var_r31 = 1;
                break;
            }
            else {
                HuAudFXPlay(4);
            }
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            var_r31 = 0;
            break;
        }
        else {
            if (HuPadStkY[0] >= 0x1E) {
                fn_1_10268(-1);
            }
            else if (HuPadStkY[0] <= -0x1E) {
                fn_1_10268(1);
            }
        }
    }
    fn_1_10228();
    fn_1_1C120();
    fn_1_1B9F4();
    fn_1_FDA0();
    if (var_r31 == 0) {
        fn_1_148E4(lbl_1_bss_1B4);
    }
    lbl_1_bss_1B0 = lbl_1_bss_3B0.unk_0C;
    return var_r31;
}

s32 fn_1_444C(s32 arg0)
{
    s32 var_r31;

    var_r31 = 1;
    if (arg0 == 0) {
        lbl_1_bss_3B0.unk_10 = 0;
        fn_1_D6AC(lbl_1_bss_1B0);
    }
    while (TRUE) {
        fn_1_1B7D0(1);
        if (HuPadBtnDown[0] & PAD_BUTTON_START) {
            HuAudFXPlay(2);
            var_r31 = 1;
            break;
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            var_r31 = 0;
            break;
        }
    }
    if (var_r31 == 0) {
        fn_1_DBD0(lbl_1_bss_1B0);
    }
    return var_r31;
}

s32 fn_1_4514(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r31 = 1;
    var_r30 = lbl_1_bss_3B0.unk_10;
    if ((lbl_1_bss_1B0 == 0) || (lbl_1_bss_1B0 == 1) || (lbl_1_bss_1B0 == 4)) {
        if (lbl_1_bss_1B0 == 4) {
            fn_1_E568();
        }
        else {
            fn_1_E174();
        }
        while (TRUE) {
            fn_1_1B7D0(1);
            if (lbl_1_bss_3B0.unk_10 != var_r30) {
                HuAudFXPlay(0);
                fn_1_ED78(lbl_1_bss_3B0.unk_10, var_r30);
                var_r30 = lbl_1_bss_3B0.unk_10;
            }
            if (HuPadStkY[0] <= -0x1E) {
                lbl_1_bss_3B0.unk_10++;
                if (lbl_1_bss_3B0.unk_10 > 2) {
                    lbl_1_bss_3B0.unk_10 = 0;
                }
                continue;
            }
            if (HuPadStkY[0] >= 0x1E) {
                lbl_1_bss_3B0.unk_10--;
                if (lbl_1_bss_3B0.unk_10 < 0) {
                    lbl_1_bss_3B0.unk_10 = 2;
                }
                continue;
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_START) {
                HuAudFXPlay(2);
                var_r31 = 1;
                break;
            }
            else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                var_r31 = 0;
                break;
            }
        }
        lbl_1_bss_1AC = lbl_1_bss_3B0.unk_10;
    }
    else {
        var_r31 = 1;
    }
    if (var_r31 == 0) {
        if (lbl_1_bss_1B0 == 4) {
            fn_1_EB1C();
        }
        else {
            fn_1_E384();
        }
    }
    return var_r31;
}

s32 fn_1_4730(s32 arg0)
{
    s32 var_r31;

    var_r31 = 1;
    var_r31 = fn_1_140B0(1, arg0);
    return var_r31;
}

s32 fn_1_4770(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = -1;
    if (arg0 == 0) {
        fn_1_148BC(lbl_1_bss_1B4);
    }
    fn_1_10C30();
    fn_1_1B834();
    if (lbl_1_data_294 == -1) {
        HuAudFXPlay(0x4A);
        fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 3, 0xF, 1);
        fn_1_1BA78(0x330014, -1, -1);
        fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 1, 0xF, 1);
    }
    else {
        lbl_1_bss_3B0.unk_0C = lbl_1_data_294;
        lbl_1_data_294 = -1;
    }
    fn_1_1B7D0(1);
    fn_1_1BF1C(0x33004D);
    fn_1_114D4();
    while (TRUE) {
        fn_1_1B7D0(1);
        if (var_r30 != lbl_1_bss_3B0.unk_0C) {
            var_r30 = lbl_1_bss_3B0.unk_0C;
            HuAudFXPlay(0);
            if (lbl_1_bss_180[lbl_1_bss_3B0.unk_0C + 4] == 1) {
                fn_1_1BA78(lbl_1_bss_3B0.unk_0C + 0x330015, -1, 1);
            }
            else {
                fn_1_1BA78(0x33002E, -1, 1);
            }
            fn_1_1B7D0(1);
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            if (lbl_1_bss_180[lbl_1_bss_3B0.unk_0C + 4] == 1) {
                HuAudFXPlay(2);
                lbl_1_data_294 = lbl_1_bss_3B0.unk_0C;
                var_r31 = 1;
                break;
            }
            else {
                HuAudFXPlay(4);
            }
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            var_r31 = 0;
            break;
        }
        else {
            if (HuPadStkY[0] >= 0x1E) {
                fn_1_115E0(-1);
            }
            else if (HuPadStkY[0] <= -0x1E) {
                fn_1_115E0(1);
            }
        }
    }
    fn_1_115A0();
    fn_1_1C120();
    fn_1_1B9F4();
    fn_1_110F8();
    if (var_r31 == 0) {
        fn_1_148E4(lbl_1_bss_1B4);
    }
    lbl_1_bss_1B0 = lbl_1_bss_3B0.unk_0C + (lbl_1_bss_1B4 * 4);
    return var_r31;
}

s32 fn_1_4A58(s32 arg0)
{
    s32 var_r31 = 1;
    var_r31 = fn_1_444C(arg0);
    return var_r31;
}

s32 fn_1_4B3C(s32 arg0)
{
    s32 var_r31 = 1;
    var_r31 = fn_1_4514(arg0);
    return var_r31;
}

s32 fn_1_4B78(s32 arg0)
{
    s32 var_r30;

    var_r30 = 1;
    lbl_1_bss_1B0 = 0xA;
    var_r30 = fn_1_444C(arg0);
    return var_r30;
}

void fn_1_4C6C(void)
{
    s32 var_r31;

    Hu3DModelPosSet(lbl_1_bss_2D8[0].unk_00->model[1], -400.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[1].unk_00->model[1], 1000.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[2].unk_00->model[1], 0.0f, 1000.0f, 0.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        Hu3DModelPosSet(lbl_1_bss_1B8[var_r31].unk_00->model[1], -225.0f + (150.0f * var_r31), 0.0f, 0.0f);
        Hu3DModelAttrReset(lbl_1_bss_1B8[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
    }
}

void fn_1_4DF8(void)
{
    s32 var_r31;

    Hu3DModelPosSet(lbl_1_bss_2D8[0].unk_00->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[1].unk_00->model[1], 1000.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[2].unk_00->model[1], 0.0f, 1000.0f, 0.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        Hu3DModelPosSet(lbl_1_bss_1B8[var_r31].unk_00->model[1], -225.0f + (150.0f * var_r31), 0.0f, 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_1B8[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
    }
}

void fn_1_4F84(void)
{
    s32 var_r31;
    s32 var_r30;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_130[var_r31].unk_00 = GWPlayerCfg[var_r31].group;
        lbl_1_bss_130[var_r31].unk_04 = GWPlayerCfg[var_r31].iscom;
        lbl_1_bss_130[var_r31].unk_08 = GWPlayerCfg[var_r31].diff;
        lbl_1_bss_130[var_r31].unk_0C = GWPlayerCfg[var_r31].character;
        lbl_1_bss_130[var_r31].unk_10 = GWPlayerCfg[var_r31].pad_idx;
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (var_r30 == lbl_1_bss_130[var_r31].unk_10) {
                GWPlayer[var_r30].team = GWPlayerCfg[var_r30].group = lbl_1_bss_130[var_r31].unk_00;
                GWPlayer[var_r30].com = GWPlayerCfg[var_r30].iscom = lbl_1_bss_130[var_r31].unk_04;
                GWPlayer[var_r30].diff = GWPlayerCfg[var_r30].diff = lbl_1_bss_130[var_r31].unk_08;
                GWPlayer[var_r30].character = GWPlayerCfg[var_r30].character = lbl_1_bss_130[var_r31].unk_0C;
                GWPlayer[var_r30].port = GWPlayerCfg[var_r30].pad_idx = lbl_1_bss_130[var_r31].unk_10;
                break;
            }
        }
    }
}

s32 fn_1_5238(void)
{
    s32 var_r29 = 0;
    if (lbl_1_bss_1B0 != 2) {
        fn_1_A608();
    }
    fn_1_4F84();
    fn_1_1B7D0(0x3C);
    var_r29 = 0;
    return var_r29;
}

void fn_1_5530(void)
{
    Vec sp14 = { 0.0f, 0.0f, 0.0f };
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1B8[var_r31].unk_04 = (MpexDllUnkFunc2)fn_1_7FC4;
    }
    do {
        fn_1_1B7D0(1);
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_1B8[var_r31].unk_04 != NULL) {
                break;
            }
        }
    } while (var_r31 != 4);
    Hu3DModelAttrReset(lbl_1_bss_3B0.unk_00->model[5], HU3D_MOTATTR_PAUSE);
    fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 2, 0xF, 1);
    fn_1_28E0(lbl_1_bss_2D8[0].unk_00, 1, sp14, 0.0f, 9.0f, 0.0f, 1, 0);
    fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 1, 0xF, 1);
    fn_1_1B7D0(0x3C);
}

void fn_1_56B8(void)
{
    Hu3DModelPosSet(lbl_1_bss_2D8[0].unk_00->model[1], -1000.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[1].unk_00->model[1], -400.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[2].unk_00->model[1], 0.0f, 1000.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_1B8[0].unk_00->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1B8[0].unk_00->model[1], HU3D_ATTR_DISPOFF);
}

s32 fn_1_57E0(void)
{
    s32 var_r31 = 0;
    fn_1_AD34();
    fn_1_1B7D0(0x3C);
    var_r31 = 0;
    return var_r31;
}

// similar to fn_1_5530
void fn_1_581C(void)
{
    Vec sp14 = { 0.0f, 0.0f, 0.0f };

    lbl_1_bss_1B8[0].unk_04 = (MpexDllUnkFunc2)fn_1_7FC4;

    do {
        fn_1_1B7D0(1);
    } while (lbl_1_bss_1B8[0].unk_04 != NULL);

    Hu3DModelAttrReset(lbl_1_bss_3B0.unk_00->model[5], HU3D_MOTATTR_PAUSE);
    fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 2, 0xF, 1);
    fn_1_28E0(lbl_1_bss_2D8[1].unk_00, 1, sp14, 0.0f, 9.0f, 0.0f, 1, 0);
    fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 1, 0xF, 1);
    fn_1_1B7D0(0x3C);
}

void fn_1_595C(void)
{
    fn_1_3508();
}

void fn_1_5AF8(void)
{
    s32 var_r31;

    Hu3DModelPosSet(lbl_1_bss_2D8[0].unk_00->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[1].unk_00->model[1], 1000.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[2].unk_00->model[1], 0.0f, 1000.0f, 0.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        Hu3DModelAttrSet(lbl_1_bss_1B8[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
    }
    fn_1_C544();
    fn_1_D468(lbl_1_bss_1B0);
}

void fn_1_5C1C(void)
{
    s32 var_r31;

    Hu3DModelPosSet(lbl_1_bss_2D8[0].unk_00->model[1], -1000.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[1].unk_00->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_2D8[2].unk_00->model[1], 0.0f, 1000.0f, 0.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        Hu3DModelAttrSet(lbl_1_bss_1B8[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
    }
    fn_1_C544();
    fn_1_D468(lbl_1_bss_1B0);
}

void fn_1_5D40(omObjData *object, MpexDllUnkStruct4 *arg1)
{
    s32 var_r31 = 0;
    s32 var_r29 = 0;
    s32 var_r30 = 0;

    if (omovlevtno == 1) {
        lbl_1_bss_1B0 = omovlstat % 10;
        if (lbl_1_bss_1B0 <= 3) {
            lbl_1_bss_1B4 = 0;
        }
        else {
            lbl_1_bss_1B4 = 1;
        }
        lbl_1_bss_1AC = omovlstat / 10;
        if (mgQuitExtraF == 1) {
            mgQuitExtraF = 0;
            Hu3DMotionTimeSet(lbl_1_bss_3B0.unk_00->model[5], Hu3DMotionMotionMaxTimeGet(lbl_1_bss_3B0.unk_00->model[5]) - 5.0f);
            if (lbl_1_bss_1B0 <= 3) {
                fn_1_4F84();
                lbl_1_data_294 = lbl_1_bss_1B0;
                fn_1_5AF8();
                var_r31 = 0x320;
            }
            else {
                lbl_1_data_294 = lbl_1_bss_1B0 - 4;
                fn_1_5C1C();
                var_r31 = 0x384;
            }
        }
        else if (lbl_1_bss_1B0 <= 3) {
            lbl_1_data_294 = lbl_1_bss_1B0;
            if (lbl_1_bss_1B0 == 2) {
                Hu3DMotionTimeSet(lbl_1_bss_3B0.unk_00->model[5], Hu3DMotionMotionMaxTimeGet(lbl_1_bss_3B0.unk_00->model[5]) - 5.0f);
                fn_1_4DF8();
                var_r31 = 0x1FE;
            }
            else {
                Hu3DMotionTimeSet(lbl_1_bss_3B0.unk_00->model[5], 33.0f);
                fn_1_4C6C();
                var_r31 = 0x1F4;
            }
        }
        else {
            lbl_1_data_294 = lbl_1_bss_1B0 - 4;
            Hu3DMotionTimeSet(lbl_1_bss_3B0.unk_00->model[5], 33.0f);
            fn_1_56B8();
            var_r31 = 0x258;
        }
    }
    else if (omovlevtno == 2) {
        lbl_1_bss_1B0 = 0;
        lbl_1_bss_1B4 = 0;
        var_r31 = 1;
    }
    else {
        var_r31 = 0;
    }
    while (TRUE) {
        fn_1_1B7D0(1);
        switch (var_r31) {
            case 0x0:
                fn_1_397C();
                fn_1_25C4(lbl_1_bss_3B0.unk_00, 5, 5, 0, 0);
                fn_1_1B7D0(0x3C);
                fn_1_39F4();
                var_r31 = 0x64;
                break;
            case 0x1:
                Hu3DMotionTimeSet(lbl_1_bss_3B0.unk_00->model[5], Hu3DMotionMotionMaxTimeGet(lbl_1_bss_3B0.unk_00->model[5]) - 5.0f);
                fn_1_397C();
                var_r31 = 0x64;
                break;
            case 0x64:
                fn_1_117D4();
                fn_1_3AF8();
                fn_1_11930();
                var_r30 = 0;
                var_r31 = 0x65;
                break;
            case 0x65:
                fn_1_4014();

                if (lbl_1_bss_1B4 == 2) {
                    var_r31 = (lbl_1_bss_1B4 * 0x64) + 0xC9;
                }
                else {
                    var_r31 = (lbl_1_bss_1B4 * 0x64) + 0xC8;
                }
                break;
            case 0x66:
                fn_1_40AC();
                var_r31 = 0x64;
                break;
            case 0xC8:
                var_r29 = fn_1_4144(var_r30);
                if (var_r29 != 0) {
                    var_r30 = 0;
                    var_r31 = 0xC9;
                }
                else {
                    var_r30 = 1;
                    var_r31 = 0x66;
                }
                break;
            case 0xC9:
                fn_1_F0C0();
                var_r29 = fn_1_4184(var_r30);
                fn_1_F40C();
                if (var_r29 != 0) {
                    fn_1_C544();
                    var_r30 = 0;
                    var_r31 = 0xCA;
                }
                else {
                    var_r30 = 1;
                    var_r31 = 0x66;
                }
                break;
            case 0xCA:
                var_r29 = fn_1_444C(var_r30);
                if (var_r29 != 0) {
                    var_r30 = 0;
                    var_r31 = 0xCB;
                }
                else {
                    fn_1_C860();
                    var_r30 = 1;
                    var_r31 = 0xC9;
                }
                break;
            case 0xCB:
                var_r29 = fn_1_4514(var_r30);
                if (var_r29 != 0) {
                    var_r30 = 0;
                    var_r31 = 0xCC;
                }
                else {
                    var_r30 = 1;
                    var_r31 = 0xCA;
                }
                break;
            case 0xCC:
                fn_1_3758(lbl_1_bss_1B0, lbl_1_bss_1AC);
                var_r31 = -1;
                break;
            case 0x12C:
                var_r29 = fn_1_4730(var_r30);
                if (var_r29 != 0) {
                    var_r30 = 0;
                    var_r31 = 0x12D;
                }
                else {
                    var_r30 = 1;
                    var_r31 = 0x66;
                }
                break;
            case 0x12D:
                fn_1_1045C();
                var_r29 = fn_1_4770(var_r30);
                fn_1_107EC();
                if (var_r29 != 0) {
                    fn_1_C544();
                    var_r30 = 0;
                    var_r31 = 0x12E;
                }
                else {
                    var_r30 = 1;
                    var_r31 = 0x66;
                }
                break;
            case 0x12E:
                var_r29 = fn_1_4A58(var_r30);
                if (var_r29 != 0) {
                    var_r30 = 0;
                    var_r31 = 0x12F;
                }
                else {
                    fn_1_C860();
                    var_r30 = 1;
                    var_r31 = 0x12D;
                }
                break;
            case 0x12F:
                var_r29 = fn_1_4B3C(var_r30);
                if (var_r29 != 0) {
                    var_r30 = 0;
                    var_r31 = 0x130;
                }
                else {
                    var_r30 = 1;
                    var_r31 = 0x12E;
                }
                break;
            case 0x130:
                fn_1_3758(lbl_1_bss_1B0, lbl_1_bss_1AC);
                var_r31 = -1;
                continue;
            case 0x191:
                fn_1_C544();
                var_r29 = fn_1_4B78(var_r30);
                if (var_r29 != 0) {
                    var_r30 = 0;
                    var_r31 = 0x192;
                }
                else {
                    fn_1_C860();
                    var_r30 = 1;
                    var_r31 = 0x66;
                }
                break;
            case 0x192:
                fn_1_36A4();
            case 0x1F4:
                fn_1_397C();
                var_r29 = fn_1_5238();
                if (var_r29 == 1) {
                    var_r31 = 0xCC;
                }
                else if (var_r29 == 0) {
                    var_r31 = 0x1F5;
                }
                else {
                    var_r31 = 0x2BC;
                }
                break;
            case 0x1F5:
                fn_1_5530();
                var_r31 = 0xC9;
                break;
            case 0x1FE:
                fn_1_397C();
                var_r31 = 0xC9;
                break;
            case 0x258:
                fn_1_397C();
                var_r29 = fn_1_57E0();
                if (var_r29 == 1) {
                    var_r31 = 0x130;
                }
                else if (var_r29 == 0) {
                    var_r31 = 0x259;
                }
                else {
                    var_r31 = 0x2BC;
                }
                break;
            case 0x259:
                fn_1_581C();
                var_r31 = 0x12D;
                break;
            case 0x2BC:
                fn_1_3508();
            case 0x320:
                fn_1_397C();
                var_r31 = 0xCA;
                var_r30 = 1;
                break;
            case 0x384:
                fn_1_397C();
                var_r31 = 0x12E;
                var_r30 = 1;
                break;
            default:
                break;
        }
    }
}

void fn_1_7BC8(omObjData *object)
{
    s32 var_r30;

    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x00));
    object->motion[1] = Hu3DMotionIDGet(object->model[1]);
    Hu3DModelShadowMapObjSet(object->model[1], "extra_ent_fix0-obj41");
    fn_1_25C4(object, 1, 1, 0, 1);
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        object->model[var_r30 + 1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x02));
        Hu3DModelAttrSet(object->model[var_r30 + 1], HU3D_ATTR_DISPOFF);
    }
    object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x01));
    object->motion[5] = Hu3DMotionIDGet(object->model[5]);
    Hu3DModelPosSet(object->model[5], 0.0f, 0.0f, 270.0f);
    if (omovlevtno == 2) {
        fn_1_25C4(object, 5, 5, 0, 0);
        return;
    }
    if (omovlevtno == 1) {
        Hu3DModelAttrSet(object->model[5], HU3D_MOTATTR_PAUSE);
        return;
    }
    fn_1_25C4(object, 5, 5, 0, 2);
}

void fn_1_7D80(void)
{
    omObjData *var_r29;
    omObjData *var_r31;
    s32 var_r30;

    var_r29 = NULL;
    var_r29 = omAddObjEx(lbl_1_bss_A8, 0x2000, 0x10, 0x10, -1, NULL);
    lbl_1_bss_3B0.unk_00 = var_r29;
    lbl_1_bss_3B0.unk_04 = NULL;
    var_r31 = lbl_1_bss_3B0.unk_00;
    fn_1_7BC8(var_r31);
    while (TRUE) {
        fn_1_1B7D0(1);
        if (lbl_1_bss_3B0.unk_04 == NULL) {
            continue;
        }
        lbl_1_bss_3B0.unk_04(lbl_1_bss_3B0.unk_00, &lbl_1_bss_3B0);
    }
}

void fn_1_7FC4(omObjData *object, MpexDllUnkStruct4 *arg1)
{
    Vec sp14 = { 700.0f, 0.0f, 0.0f };
    fn_1_1B7D0((4 - object->work[0]) * 5);
    fn_1_25C4(object, 1, 2, 0xA, 1);
    object->work[1] = 0;
    while (object->work[1] <= 0xA) {
        fn_1_1B7D0(1);
        Hu3DData[object->model[1]].rot.y = fn_1_1B52C(0.0f, 90.0f, object->work[1], 10.0f);
        object->work[1]++;
    }

    fn_1_25C4(object, 1, 3, 0xA, 1);
    fn_1_28E0(object, 1, sp14, 0.0f, 9.0f, 0.0f, 1, 0);
    fn_1_25C4(object, 1, 1, 0xA, 1);
    arg1->unk_04 = NULL;
}

void fn_1_816C(omObjData *object, s32 arg1)
{
    s32 var_r30 = GWPlayerCfg[arg1].character;
    object->model[1] = CharModelCreate(var_r30, 4);
    object->motion[1] = CharModelMotionCreate(var_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
    object->motion[2] = CharModelMotionCreate(var_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02));
    object->motion[3] = CharModelMotionCreate(var_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03));
    object->motion[4] = CharModelMotionCreate(var_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x48));
    object->motion[5] = CharModelMotionCreate(var_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x49));
    Hu3DModelPosSet(object->model[1], -150.0f + (100.0f * arg1), 0.0f, 0.0f);
    Hu3DModelShadowSet(object->model[1]);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
    CharModelLayerSetAll2(2);
    fn_1_25C4(object, 1, 1, 0, 1);
    CharKill(var_r30);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x02));
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
}

void fn_1_8320(void)
{
    MpexDllUnkStruct4 *temp_r5;
    omObjData *var_r28;
    omObjData *var_r31;
    s16 var_r29;
    u32 var_r30;

    var_r30 = lbl_1_bss_AC;
    lbl_1_bss_AC = var_r30 + 1;
    var_r28 = NULL;
    var_r28 = omAddObjEx(lbl_1_bss_A8, 0x2000, 0x10, 0x10, -1, NULL);
    lbl_1_bss_1B8[var_r30].unk_00 = var_r28;
    lbl_1_bss_1B8[var_r30].unk_04 = NULL;
    lbl_1_bss_1B8[var_r30].unk_00->work[0] = var_r30;
    var_r31 = lbl_1_bss_1B8[var_r30].unk_00;
    fn_1_816C(var_r31, var_r30);
    while (TRUE) {
        fn_1_1B7D0(1);
        if (lbl_1_bss_1B8[var_r30].unk_04 == NULL) {
            continue;
        }
        lbl_1_bss_1B8[var_r30].unk_04(lbl_1_bss_1B8[var_r30].unk_00, &lbl_1_bss_1B8[var_r30]);
    }
}

void fn_1_85C4(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x03));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x04));
    object->motion[2] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x06));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x06));
    object->motion[4] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x07));
    object->motion[5] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x08));
    Hu3DModelPosSet(object->model[1], -200.0f, 0.0f, 0.0f);
    Hu3DModelShadowSet(object->model[1]);
    CharModelEffectNpcInit(object->model[1], object->motion[2], 0, 0xF);
    fn_1_25C4(object, 1, 1, 0, 1);
}

void fn_1_8758(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x09));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x0A));
    object->motion[2] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x0B));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x0C));
    object->motion[4] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x0D));
    object->motion[5] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x0E));
    Hu3DModelPosSet(object->model[1], 200.0f, 0.0f, 0.0f);
    Hu3DModelShadowSet(object->model[1]);
    CharModelEffectNpcInit(object->model[1], object->motion[2], 0, 0x10);
    fn_1_25C4(object, 1, 1, 0, 1);
}

void fn_1_88EC(omObjData *object)
{
    float var_f31;

    var_f31 = 0.0f;
    var_f31 = fn_1_1B714(0.0f, 1.0f, object->work[3], 180.0f);
    Hu3DData[object->model[1]].pos.y += var_f31;
    if (object->work[3]++ >= 0xB4) {
        object->work[3] -= 0xB4;
    }
}

void fn_1_89C4(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x0F));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x10));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MPEX, 0x11));
    Hu3DModelPosSet(object->model[1], 0.0f, 400.0f, 0.0f);
    if (lbl_1_bss_180[0xA] == 0) {
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
    }
    fn_1_25C4(object, 1, 1, 0, 1);
    object->func = fn_1_88EC;
}

void fn_1_8ADC(void)
{
    omObjData *var_r31;
    omObjData *var_r30;
    omObjData *var_r29;
    s32 var_r28;
    omObjData *var_r27;

    var_r28 = lbl_1_bss_B0;
    lbl_1_bss_B0 = var_r28 + 1;
    var_r27 = NULL;
    var_r27 = omAddObjEx(lbl_1_bss_A8, 0x2000, 0x10, 0x10, -1, NULL);
    lbl_1_bss_2D8[var_r28].unk_00 = var_r27;
    lbl_1_bss_2D8[var_r28].unk_04 = 0;
    lbl_1_bss_2D8[var_r28].unk_00->work[0] = var_r28;
    switch (var_r28) {
        case 0:
            var_r31 = lbl_1_bss_2D8[var_r28].unk_00;
            fn_1_85C4(var_r31);
            break;
        case 1:
            var_r30 = lbl_1_bss_2D8[var_r28].unk_00;
            fn_1_8758(var_r30);
            break;
        case 2:
            var_r29 = lbl_1_bss_2D8[var_r28].unk_00;
            fn_1_89C4(var_r29);
            break;
    }
    while (TRUE) {
        fn_1_1B7D0(1);
        if (lbl_1_bss_2D8[var_r28].unk_04 == NULL) {
            continue;
        }
        lbl_1_bss_2D8[var_r28].unk_04(lbl_1_bss_2D8[var_r28].unk_00, &lbl_1_bss_2D8[var_r28]);
    }
}

void fn_1_901C(omObjData *object, MpexDllUnkStruct4 *arg1)
{
    float var_f31;

    s32 var_r30;
    s32 *var_r29;
    s32 *var_r28;
    s32 *var_r27;
    s32 *var_r26;
    void *var_r25;

    Vec sp50 = { 0.0f, 0.0f, 0.0f };
    Vec sp44 = { -1000.0f, 0.0f, 0.0f };
    Vec sp38 = { 1000.0f, 0.0f, 0.0f };
    switch (object->work[0]) {
        case 0:
            fn_1_25C4(object, 1, 3, 0xF, 1);
            if (lbl_1_bss_1B4 == 0) {
                fn_1_28E0(object, 1, sp50, 0.0f, 9.0f, 0.0f, 1, 0);
            }
            else {
                fn_1_28E0(object, 1, sp44, 0.0f, 9.0f, 0.0f, 1, 0);
            }
            fn_1_25C4(object, 1, 1, 0xF, 1);
            break;
        case 1:
            fn_1_25C4(object, 1, 2, 0xF, 1);
            if (lbl_1_bss_1B4 == 1) {
                fn_1_28E0(object, 1, sp50, 0.0f, 9.0f, 0.0f, 1, 0);
            }
            else {
                fn_1_28E0(object, 1, sp38, 0.0f, 9.0f, 0.0f, 1, 0);
            }
            fn_1_25C4(object, 1, 1, 0xF, 1);
            break;
        case 2:
            if (lbl_1_bss_1B4 == 2) {
                var_f31 = Hu3DData[object->model[1]].pos.y;
                for (var_r30 = 0; var_r30 <= 0x78; var_r30++) {
                    fn_1_1B7D0(1);
                    Hu3DData[object->model[1]].pos.y = fn_1_1B64C(var_f31, 250.0f, var_r30, 120.0f);
                }
            }
            else {
                var_f31 = Hu3DData[object->model[1]].pos.y;
                for (var_r30 = 0; var_r30 <= 0x78; var_r30++) {
                    fn_1_1B7D0(1);
                    Hu3DData[object->model[1]].pos.y = fn_1_1B64C(var_f31, 1000.0f, var_r30, 120.0f);
                }
            }
            break;
    }
    arg1->unk_04 = 0;
}

void fn_1_9430(omObjData *object, MpexDllUnkStruct4 *arg1)
{
    float var_f31;
    s32 var_r30;
    s32 *var_r29;
    s32 *var_r28;

    Vec sp38 = { 0.0f, 0.0f, 0.0f };
    Vec sp2C = { -200.0f, 0.0f, 0.0f };
    Vec sp20 = { 200.0f, 0.0f, 0.0f };
    switch (object->work[0]) {
        case 0:
            fn_1_25C4(object, 1, 2, 0xF, 1);
            fn_1_28E0(object, 1, sp2C, 0.0f, 9.0f, 0.0f, 1, 0);
            fn_1_25C4(object, 1, 1, 0xF, 1);
            break;
        case 1:
            fn_1_25C4(object, 1, 2, 0xF, 1);
            fn_1_28E0(object, 1, sp20, 0.0f, 9.0f, 0.0f, 1, 0);
            fn_1_25C4(object, 1, 1, 0xF, 1);
            break;
        case 2:
            var_f31 = Hu3DData[object->model[1]].pos.y;
            for (var_r30 = 0; var_r30 <= 0x78; var_r30++) {
                fn_1_1B7D0(1);
                Hu3DData[object->model[1]].pos.y = fn_1_1B574(var_f31, 400.0f, var_r30, 120.0f);
            }
            break;
    }
    arg1->unk_04 = 0;
}

void fn_1_96B4(void)
{
    MpexDllUnkStruct *var_r31 = &lbl_1_bss_64;
    var_r31->unk_08.x = 0.0f;
    var_r31->unk_08.y = 165.0f;
    var_r31->unk_08.z = 0.0f;
    var_r31->unk_20.x = 0.0f;
    var_r31->unk_20.y = 0.0f;
    var_r31->unk_20.z = 0.0f;
    var_r31->unk_38 = 1200.0f;
}

s32 lbl_1_data_2B4[4] = { -1, -1, -1, -1 };
s32 lbl_1_data_2C4 = -1;

void fn_1_9740(s32 arg0)
{
    s32 spC[4];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r29 = 0;
    var_r30 = 0;
    lbl_1_bss_B4 = 0;
    lbl_1_data_2B4[0] = lbl_1_data_2B4[1] = lbl_1_data_2B4[2] = lbl_1_data_2B4[3] = -1;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        spC[var_r31] = fn_1_B248(arg0, var_r31);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (spC[var_r31] >= var_r30) {
            var_r30 = spC[var_r31];
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r30 == spC[var_r31]) {
            lbl_1_bss_B4++;
            lbl_1_data_2B4[var_r29++] = var_r31;
        }
    }
    lbl_1_data_2C4 = var_r30;
}

void fn_1_9890(void)
{
    fn_1_1B834();
    fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 3, 0xF, 1);
    fn_1_1BA78(0x33000C, -1, -1);
    fn_1_25C4(lbl_1_bss_2D8[0].unk_00, 1, 1, 0xF, 1);
    fn_1_1B9F4();
}

void fn_1_9908(void)
{
    fn_1_1B834();
    HuAudFXPlay(0x4A);
    fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 3, 0xF, 1);
    fn_1_1BA78(0x33001B, -1, -1);
    fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 1, 0xF, 1);
    fn_1_1B9F4();
}

void fn_1_9988(s32 arg0)
{
    s32 var_r31;
    u32 var_r30;
    u32 var_r29;

    fn_1_1B834();
    if (((mgRecordExtra == 0) && (arg0 != 4)) || ((mgRecordExtra >= 600*REFRESH_RATE) && (arg0 == 4))) {
        HuAudFXPlay(0x4A);
        fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 3, 0xF, 1);
        fn_1_1BA78(arg0 + 0x330096, -1, -1);
        fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 1, 0xF, 1);
    }
    else {
        if ((arg0 == 4) || (arg0 == 8)) {
            var_r31 = mgRecordExtra;
            var_r30 = var_r31 / (600*REFRESH_RATE);
            var_r31 -= var_r30 * (600*REFRESH_RATE);
            var_r29 = var_r31 / (60*REFRESH_RATE);
            var_r31 -= var_r29 * (60*REFRESH_RATE);
            sprintf(lbl_1_bss_120, "%d", var_r29);
            fn_1_1BB4C((u32)&lbl_1_bss_120, 0);
            var_r30 = var_r31 / (10*REFRESH_RATE);
            var_r31 -= var_r30 * (10*REFRESH_RATE);
            var_r29 = var_r31 / REFRESH_RATE;
            var_r31 -= var_r29 * REFRESH_RATE;
            sprintf(lbl_1_bss_118, "%d%d", var_r30, var_r29);
            fn_1_1BB4C((u32)lbl_1_bss_118, 1);
            if (arg0 == 8) {
                var_r31 = (101.5/REFRESH_RATE) * (float)var_r31;
            }
            else {
                var_r31 = (100.0/REFRESH_RATE) * (float)var_r31;
            }
            var_r30 = var_r31 / 10;
            var_r31 -= var_r30 * 0xA;
            var_r29 = var_r31;
            sprintf(lbl_1_bss_110, "%d%d", var_r30, var_r29);
            fn_1_1BB4C((u32)lbl_1_bss_110, 2);
        }
        else {
            sprintf(lbl_1_bss_110, "%d", mgRecordExtra);
            fn_1_1BB4C((u32)lbl_1_bss_110, 0);
        }
        HuAudFXPlay(0x4A);
        fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 3, 0xF, 1);
        fn_1_1BA78(arg0 + 0x330018, -1, -1);
        fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 1, 0xF, 1);
    }
    fn_1_1B9F4();
}

void fn_1_9CD4(s32 arg0)
{
    fn_1_1B834();
    fn_1_1BB4C(fn_1_BD10(arg0, mgRecordExtra), 3);
    fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 3, 0xF, 1);
    fn_1_1BA78(0x330090, -1, -1);
    fn_1_25C4(lbl_1_bss_2D8[1].unk_00, 1, 1, 0xF, 1);
    fn_1_1B9F4();
}

void fn_1_9D6C(void)
{
    fn_1_1B834();
    switch (lbl_1_bss_B4) {
        case 1:
            fn_1_1BB4C(GWPlayerCfg[lbl_1_data_2B4[0]].character, 0);
            fn_1_1BA78(0x33000D, -1, -1);
            break;
        case 2:
            fn_1_1BB4C(GWPlayerCfg[lbl_1_data_2B4[0]].character, 0);
            fn_1_1BB4C(GWPlayerCfg[lbl_1_data_2B4[1]].character, 1);
            fn_1_1BA78(0x33000E, -1, -1);
            break;
        case 3:
            fn_1_1BB4C(GWPlayerCfg[lbl_1_data_2B4[0]].character, 0);
            fn_1_1BB4C(GWPlayerCfg[lbl_1_data_2B4[1]].character, 1);
            fn_1_1BB4C(GWPlayerCfg[lbl_1_data_2B4[2]].character, 2);
            fn_1_1BA78(0x33000F, -1, -1);
            break;
        case 4:
            fn_1_1BA78(0x330010, -1, -1);
            break;
    }
    fn_1_1B9F4();
}

void fn_1_9F10(omObjData *object, MpexDllUnkStruct4 *arg1)
{
    float var_f31;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_f31 = 30.0 * sind(8.0f * (lbl_1_bss_B8 + (var_r31 * 0x78)));
        Hu3DModelPosSet(object->model[var_r31 + 1], -200.0f + (200.0f * var_r31), 850.0f, 0.0f);
        Hu3DModelRotSet(object->model[var_r31 + 1], 0.0f, 0.0f, var_f31);
        Hu3DModelScaleSet(object->model[var_r31 + 1], 1.5f, 2.0f, 1.5f);
    }
    lbl_1_bss_B8 += 0.5f;
}

void fn_1_A0E4(omObjData *object, MpexDllUnkStruct4 *arg_1)
{
    float var_f31;
    float var_f30;
    s32 var_r30;

    Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelTPLvlSet(object->model[2], 0.0f);
    for (var_r30 = 0; var_r30 <= 0xF; var_r30++) {
        fn_1_1B7D0(1);
        var_f30 = fn_1_1B52C(0.0f, 0.5f, var_r30, 15.0f);
        var_f31 = fn_1_1B52C(0.0f, 1.5f, var_r30, 15.0f);
        Hu3DModelPosSet(object->model[2], Hu3DData[object->model[1]].pos.x, 850.0f, Hu3DData[object->model[1]].pos.z);
        Hu3DModelScaleSet(object->model[2], var_f31, 2.0f, var_f31);
        Hu3DModelTPLvlSet(object->model[2], var_f30);
    }
    arg_1->unk_04 = NULL;
}

void fn_1_A2AC(omObjData *object, MpexDllUnkStruct4 *arg1)
{
    float var_f31;
    s32 var_r30;

    for (var_r30 = 0; var_r30 <= 0xF; var_r30++) {
        fn_1_1B7D0(1);
        var_f31 = fn_1_1B52C(0.5f, 0.0f, var_r30, 15.0f);
        Hu3DModelTPLvlSet(object->model[2], var_f31);
    }
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelTPLvlSet(object->model[2], 0.0f);
    arg1->unk_04 = NULL;
}

void fn_1_A3A4(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;

    lbl_1_bss_3B0.unk_04 = (MpexDllUnkFunc2)fn_1_9F10;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        Hu3DModelAttrReset(lbl_1_bss_3B0.unk_00->model[var_r31 + 1], HU3D_ATTR_DISPOFF);
        Hu3DModelTPLvlSet(lbl_1_bss_3B0.unk_00->model[var_r31 + 1], 0.0f);
    }
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_1B7D0(1);
        var_f31 = fn_1_1B52C(0.0f, 0.5f, var_r31, 60.0f);
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            Hu3DModelTPLvlSet(lbl_1_bss_3B0.unk_00->model[var_r30 + 1], var_f31);
        }
    }
    fn_1_1B7D0(0x5A);
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_1B7D0(1);
        var_f31 = fn_1_1B52C(0.5f, 0.0f, var_r31, 60.0f);
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            Hu3DModelTPLvlSet(lbl_1_bss_3B0.unk_00->model[var_r30 + 1], var_f31);
        }
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        Hu3DModelAttrSet(lbl_1_bss_3B0.unk_00->model[var_r31 + 1], HU3D_ATTR_DISPOFF);
        Hu3DModelTPLvlSet(lbl_1_bss_3B0.unk_00->model[var_r31 + 1], 0.0f);
    }
    lbl_1_bss_3B0.unk_04 = NULL;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_A608(void)
{
    s32 var_r31;
    s32 var_r29;

    fn_1_9740(lbl_1_bss_1B0);
    OSReport("CNT:%d, WIN:%d %d %d %d\n", lbl_1_bss_B4, lbl_1_data_2B4[0], lbl_1_data_2B4[1], lbl_1_data_2B4[2], lbl_1_data_2B4[3]);
    fn_1_9890();
    if (lbl_1_data_298 != -1) {
        HuAudSeqPause(lbl_1_data_298, 1, 0x1F4);
    }
    HuPrcChildCreate(fn_1_A3A4, 0x3E8, 0x1000, 0, HuPrcCurrentGet());
    fn_1_1B7D0(0xF);
    HuAudFXPlay(0x9E);
    fn_1_1B7D0(0xA5);
    HuAudFXPlay(0x9F);
    HuAudFXPlay(0xA8);
    HuAudFXPlay(0x9A);
    if (lbl_1_data_298 != -1) {
        HuAudSeqPause(lbl_1_data_298, 0, 0x7D0);
    }
    if ((lbl_1_bss_B4 >= 1) && (lbl_1_data_2C4 != 0)) {
        for (var_r31 = 0; var_r31 < lbl_1_bss_B4; var_r31++) {
            lbl_1_bss_1B8[lbl_1_data_2B4[var_r31]].unk_04 = (MpexDllUnkFunc2)fn_1_A0E4;
            OSReport("CNT:%d, WIN:%d %d %d %d\n", lbl_1_bss_B4, lbl_1_data_2B4[0], lbl_1_data_2B4[1], lbl_1_data_2B4[2], lbl_1_data_2B4[3]);
        }
        fn_1_9D6C();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                if (var_r31 == lbl_1_data_2B4[var_r29]) {
                    fn_1_25C4(lbl_1_bss_1B8[var_r31].unk_00, 1, 4, 0xF, 0);
                    break;
                }
            }
            if (var_r29 == 4) {
                fn_1_25C4(lbl_1_bss_1B8[var_r31].unk_00, 1, 5, 0xF, 0);
            }
        }
    }
    else {
        fn_1_1B834();
        fn_1_25C4(lbl_1_bss_2D8->unk_00, 1, 3, 0xF, 1);
        fn_1_1BA78(lbl_1_bss_1B0 + MAKE_MESSID(0x33, 0x96), -1, -1);
        fn_1_25C4(lbl_1_bss_2D8->unk_00, 1, 1, 0xF, 1);
        fn_1_1B9F4();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            fn_1_25C4(lbl_1_bss_1B8[var_r31].unk_00, 1, 5, 0xF, 0);
        }
    }
    fn_1_1B7D0(0x3C);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_1_25C4(lbl_1_bss_1B8[var_r31].unk_00, 1, 1, 0xF, 1);
    }
    fn_1_B004();
    fn_1_1B7D0(1);
    fn_1_B870(lbl_1_bss_1B0);
    fn_1_1B7D0(0x3C);
    fn_1_1B7D0(0x3C);
    fn_1_1BD00(0x240007, 1);
    do {
        fn_1_1B7D0(1);
    } while ((HuPadBtnDown[0] & 0x100) == 0);
    HuAudFXPlay(2);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1B8[var_r31].unk_04 = (MpexDllUnkFunc2)fn_1_A2AC;
    }
    fn_1_1C120();
    fn_1_B9A8(lbl_1_bss_1B0);
    fn_1_1B7D0(1);
    fn_1_B210();
}

void fn_1_AD34(void)
{
    fn_1_9908();
    fn_1_1B7D0(0x3C);
    fn_1_9988(lbl_1_bss_1B0);
    if (lbl_1_data_298 != -1) {
        HuAudSeqPause(lbl_1_data_298, 1, 0x1F4);
    }
    fn_1_1B7D0(0xF);
    HuAudFXPlay(0x9E);
    fn_1_1B7D0(0xA5);
    lbl_1_bss_1B8[0].unk_04 = (MpexDllUnkFunc2)fn_1_A0E4;
    #if VERSION_NTSC
    if (((mgRecordExtra == 0) && (lbl_1_bss_1B0 != 4)) || ((mgRecordExtra >= 600*REFRESH_RATE) && (lbl_1_bss_1B0 == 4))) {
        fn_1_25C4(lbl_1_bss_1B8[0].unk_00, 1, 5, 0xF, 0);
    }
    else {
        fn_1_25C4(lbl_1_bss_1B8[0].unk_00, 1, 4, 0xF, 0);
    }
    #else
    if (((mgRecordExtra == 0) && (lbl_1_bss_1B0 != 4)) || ((mgRecordExtra >= 500*REFRESH_RATE) && (lbl_1_bss_1B0 == 4))) {
        fn_1_25C4(lbl_1_bss_1B8[0].unk_00, 1, 5, 0xF, 0);
    }
    else {
        fn_1_25C4(lbl_1_bss_1B8[0].unk_00, 1, 4, 0xF, 0);
    } 
    #endif
    fn_1_BC18();
    fn_1_1B7D0(1);
    HuAudFXPlay(0x9F);
    HuAudFXPlay(0xA8);
    HuAudFXPlay(0x9A);
    if (lbl_1_data_298 != -1) {
        HuAudSeqPause(lbl_1_data_298, 0, 0x7D0);
    }
    fn_1_C0DC(lbl_1_bss_1B0, rand8());
    fn_1_1B7D0(0x3C);
    fn_1_25C4(lbl_1_bss_1B8[0].unk_00, 1, 1, 0xF, 1);
    fn_1_9CD4(lbl_1_bss_1B0);
    lbl_1_bss_1B8[0].unk_04 = (MpexDllUnkFunc2)fn_1_A2AC;
    fn_1_C4D4(lbl_1_bss_1B0);
    fn_1_1B7D0(1);
    fn_1_BCD8();
}

void fn_1_B004(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r28;

    var_r29 = HuSprGrpCreate(0x1B);
    lbl_1_bss_10C = var_r29;
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x37)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r29, 0, var_r30);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x38)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r29, 1, var_r30);
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        var_r30 = HuSprCreate(HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MPEX, 0x3E)), 0x7D0, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 2, var_r30);
    }
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x3B));
    for (var_r31 = 0; var_r31 < 0xC; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x384, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0xA, var_r30);
    }
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x3C));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x384, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x16, var_r30);
    }
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x3D)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r29, 0x1A, var_r30);
    fn_1_B2E4(0);
    fn_1_B7F4(0);
}

void fn_1_B210(void)
{
    s32 var_r31;

    var_r31 = lbl_1_bss_10C;
    HuSprGrpKill(var_r31);
}

s32 fn_1_B248(s32 arg0, s32 arg1)
{
    s32 var_r31 = 0;
    if (lbl_1_bss_1B0 <= 1) {
        var_r31 = GWPlayer[arg1].coins;
    }
    else {
        var_r31 = GWPlayerCoinWinGet(arg1);
        OSReport("########## %d:%d\n", arg1, var_r31);
    }
    return var_r31;
}

void fn_1_B2E4(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r24;

    var_r30 = lbl_1_bss_10C;
    for (var_r31 = 0; var_r31 < 0x1B; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    if (arg0 != -1) {
        HuSprAttrReset(var_r30, 0, 4);
        HuSprPosSet(var_r30, 0, 288.0f, 148.0f);
        HuSprAttrReset(var_r30, 1, 4);
        HuSprPosSet(var_r30, 1, 288.0f, 156.0f);
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            HuSprAttrReset(var_r30, GWPlayerCfg[var_r31].character + 2, 4);
            HuSprPosSet(var_r30, GWPlayerCfg[var_r31].character + 2, 201.0f, (var_r31 * 0x2A) + 0x60);
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            for (var_r29 = 0; var_r29 < 3; var_r29++) {
                HuSprAttrReset(var_r30, 0xA + var_r29 + (var_r31 * 3), 4);
                HuSprPosSet(var_r30, 0xA + var_r29 + (var_r31 * 3), (var_r29 * 0x1C) + 0xF7, (var_r31 * 0x2A) + 0x60);
            }
            var_r24 = fn_1_B248(0, var_r31);
            var_r28 = var_r24 / 100;
            if (var_r28 == 0) {
                HuSprAttrSet(var_r30, (var_r31 * 3) + 0xA, 4);
            }
            HuSprBankSet(var_r30, (var_r31 * 3) + 0xA, var_r28);
            var_r28 = (var_r24 % 100) / 10;
            if ((var_r28 == 0) && ((var_r24 / 100) == 0)) {
                HuSprAttrSet(var_r30, (var_r31 * 3) + 0xB, 4);
            }
            HuSprBankSet(var_r30, (var_r31 * 3) + 0xB, var_r28);
            var_r28 = var_r24 % 10;
            HuSprBankSet(var_r30, (var_r31 * 3) + 0xC, var_r28);
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            HuSprAttrReset(var_r30, var_r31 + 0x16, 4);
            HuSprPosSet(var_r30, var_r31 + 0x16, 358.0f, (var_r31 * 0x2A) + 0x60);
            switch (arg0) {
                case 0:
                case 1:
                    HuSprBankSet(var_r30, var_r31 + 0x16, 0);
                    break;
                case 3:
                    HuSprBankSet(var_r30, var_r31 + 0x16, 1);
                    break;
                case 2:
                    break;
            }
        }
        HuSprAttrReset(var_r30, 0x1A, 4);
        HuSprPosSet(var_r30, 0x1A, 288.0f, 55.0f);
        switch (arg0) {
            case 2:
                break;
            case 0:
                HuSprBankSet(var_r30, 0x1A, 0);
                break;
            case 1:
                HuSprBankSet(var_r30, 0x1A, 1);
                break;
            case 3:
                HuSprBankSet(var_r30, 0x1A, 2);
                break;
        }
        HuSprGrpPosSet(var_r30, 0.0f, -500.0f);
    }
    (void)var_r29;
}

void fn_1_B7F4(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_10C;
    for (var_r31 = 0; var_r31 < 0x1B; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprGrpPosSet(var_r30, 0.0f, -500.0f);
}

void fn_1_B870(s32 arg0)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30 = lbl_1_bss_10C;

    fn_1_B2E4(arg0);
    for (var_r31 = 0; var_r31 < 0x3C; var_r31++) {
        fn_1_1B7D0(1);
        if (var_r31 <= 0x32) {
            var_f31 = fn_1_1B64C(-500.0f, 10.0f, var_r31, 50.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, 0.0f, var_r31 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r30, 0.0f, var_f31);
    }
}

void fn_1_B9A8(s32 arg0)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_10C;
    for (var_r31 = 0; var_r31 < 0x3C; var_r31++) {
        fn_1_1B7D0(1);
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_1B64C(0.0f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(var_r28, 0.0f, var_f31);
    }
    var_r29 = lbl_1_bss_10C;
    for (var_r30 = 0; var_r30 < 0x1B; var_r30++) {
        HuSprAttrSet(var_r29, var_r30, 4);
    }
    HuSprGrpPosSet(var_r29, 0.0f, -500.0f);
}

void fn_1_BB34(s32 arg0, s32 arg1)
{
    float sp10[2];
    s32 var_r31;
    HuSprGrp *var_r30;
    HuSprite *var_r29;

    var_r30 = &HuSprGrpData[winData[arg0].group];
    HuWinMesMaxSizeGet(1, sp10, arg1);
    for (var_r31 = 0; var_r31 < var_r30->capacity; var_r31++) {
        var_r29 = &HuSprData[var_r30->members[var_r31]];
        var_r29->x -= sp10[0] / 2;
        var_r29->y -= 30.0f;
    }
}

void fn_1_BC18(void)
{
    s32 var_r31;
    s32 var_r30 = HuSprGrpCreate(2);

    lbl_1_bss_108 = var_r30;
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x39)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r30, 0, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x3A)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r30, 1, var_r31);
    fn_1_BD78(-1, 0);
}

void fn_1_BCD8(void)
{
    s32 var_r31 = lbl_1_bss_108;
    HuSprGrpKill(var_r31);
}

u32 fn_1_BD10(s32 arg0, s32 arg1)
{
    s32 var_r31 = fn_1_C898(arg1, arg0, lbl_1_bss_1AC, 0);
    return ((arg0 - 4) * 0xA) + MAKE_MESSID(0x33, 0x00) + var_r31 + 0x51;
}

void fn_1_BD78(s32 arg0, s32 arg1)
{
    float sp10[2];
    s32 var_r31;
    s32 var_r30;
    u32 var_r25;

    var_r31 = lbl_1_bss_108;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        HuSprAttrSet(var_r31, var_r30, 4);
    }
    if (arg0 != -1) {
        HuSprAttrReset(var_r31, 0, 4);
        HuSprAttrReset(var_r31, 1, 4);
        HuSprBankSet(var_r31, 1, arg0 - 4);
        HuSprGrpPosSet(var_r31, 288.0f, 100.0f);
        HuSprGrpScaleSet(var_r31, 0.0f, 0.0f);
        OSReport("#################### SCORE(%d-%d) : %d\n", arg0, lbl_1_bss_1AC, mgRecordExtra);
        var_r25 = fn_1_BD10(arg0, mgRecordExtra);
        HuWinMesMaxSizeGet(1, sp10, var_r25);
        lbl_1_bss_104 = HuWinCreate(0.0f, 0.0f, sp10[0], sp10[1], 0);
        HuWinBGTPLvlSet(lbl_1_bss_104, 0.0f);
        HuWinMesSpeedSet(lbl_1_bss_104, 0);
        HuWinDispOn(lbl_1_bss_104);
        fn_1_BB34(lbl_1_bss_104, var_r25);
        HuWinMesSet(lbl_1_bss_104, var_r25);
        HuWinPosSet(lbl_1_bss_104, 296.0f, 100.0f);
    }
}

void fn_1_C06C(void)
{
    s32 var_r31;
    s32 var_r30 = lbl_1_bss_108;
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuWinKill(lbl_1_bss_104);
}

void fn_1_C0DC(s32 arg0, s32 arg1)
{
    float var_f31;
    float var_f30;
    s32 var_r30;
    s32 var_r24;
    s32 var_r22;

    var_r30 = 0;
    var_r22 = lbl_1_bss_108;
    var_f30 = 1.5f;
    fn_1_BD78(arg0, arg1);
    for (var_r24 = 0; var_r24 < 0xA; var_r24++) {
        fn_1_1B7D0(1);
        var_f31 = fn_1_1B64C(var_f30, 1.0f, var_r30, 5.0f);
        if (++var_r30 == 5) {
            if (var_f30 > 1.0f) {
                var_f30 -= 0.1f;
            }
            var_r30 = 0;
        }
        HuSprGrpScaleSet(var_r22, var_f31, var_f31);
        HuWinScaleSet(lbl_1_bss_104, var_f31, var_f31);
    }
}

void fn_1_C4D4(s32 arg0)
{
    fn_1_C06C();
}

s32 lbl_1_data_324 = 0xFFFFFFFF;
s32 lbl_1_data_328 = -1;
s32 lbl_1_data_32C[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

void fn_1_C544(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r28;

    var_r29 = HuSprGrpCreate(0x25);
    lbl_1_data_324 = var_r29;
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x1B)), 0x1388, 0);
    HuSprGrpMemberSet(var_r29, 0, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x1C)), 0x1388, 0);
    HuSprGrpMemberSet(var_r29, 0x23, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x1D)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r29, 1, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x1E)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r29, 2, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x1F)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r29, 3, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x20)), 0x76C, 0);
    HuSprGrpMemberSet(var_r29, 4, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x21)), 0x834, 0);
    HuSprGrpMemberSet(var_r29, 6, var_r31);
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        var_r31 = HuSprCreate(HuSprAnimReadFile(var_r30 + DATA_MAKE_NUM(DATADIR_MPEX, 0x2F)), 0xA, 0);
        HuSprGrpMemberSet(var_r29, var_r30 + 7, var_r31);
    }
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        var_r31 = HuSprCreate(HuSprAnimReadFile(var_r30 + DATA_MAKE_NUM(DATADIR_MPEX, 0x32)), 0xA, 0);
        HuSprGrpMemberSet(var_r29, var_r30 + 0xA, var_r31);
    }
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x35));
    for (var_r30 = 0; var_r30 < 0x15; var_r30++) {
        var_r31 = HuSprCreate(var_r28, 9, 0);
        HuSprGrpMemberSet(var_r29, var_r30 + 0xD, var_r31);
    }
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x15)), 8, 0);
    HuSprGrpMemberSet(var_r29, 0x22, var_r31);
    fn_1_CF10(-1);
    fn_1_D3AC(-1);
}

void fn_1_C860(void)
{
    s32 var_r31 = lbl_1_data_324;
    HuSprGrpKill(var_r31);
}

s32 fn_1_C898(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    #if VERSION_NTSC
    s32 sp88[5][9] = {
        { 0x64, 0xC8, 0x12C, 0x136, 0x140, 0x14A, 0x154, 0x15E, 0x168 },
        { 0x05, 0x0A, 0x0F, 0x14, 0x19, 0x1E, 0x23, 0x28, 0x32 },
        { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 },
        { 0xE10, 0x1C20, 0x2A30, 0x3840, 0x4650, 0x5460, 0x6270, 0x7080, 0x7E90 },
        { 0x0A, 0x14, 0x1E, 0x23, 0x28, 0x2D, 0x32, 0x35, 0x37 },
    };
    s32 sp1C[3][9] = {
        { 0x4650, 0x3840, 0x2A30, 0x1C20, 0x0E10, 0, 0, 0, 0 },
        { 0x4650, 0x3840, 0x2A30, 0x1C20, 0x1770, 0x12C0, 0x0E10, 0, 0 },
        { 0x4650, 0x3840, 0x2A30, 0x2328, 0x1C20, 0x19C8, 0x1770, 0x1644, 0x1518 },
    };
    #else
    s32 sp88[5][9] = {
        { 0x32, 0x64, 0xC8, 0x12C, 0x136, 0x140, 0x14A, 0x154, 0x15E },
        { 0x05, 0x0A, 0x0F, 0x14, 0x19, 0x1E, 0x23, 0x28, 0x32 },
        { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 },
        { 60*REFRESH_RATE, 120*REFRESH_RATE, 180*REFRESH_RATE, 240*REFRESH_RATE, 300*REFRESH_RATE,
            360*REFRESH_RATE, 420*REFRESH_RATE, 480*REFRESH_RATE, 540*REFRESH_RATE },
        { 0x0A, 0xF, 0x14, 0x19, 0x1E, 0x23, 0x28, 0x2B, 0x2D },
    };
    s32 sp1C[3][9] = {
        { 300*REFRESH_RATE, 240*REFRESH_RATE, 180*REFRESH_RATE, 120*REFRESH_RATE, 60*REFRESH_RATE, 0, 0, 0, 0 },
        { 300*REFRESH_RATE, 240*REFRESH_RATE, 180*REFRESH_RATE, 120*REFRESH_RATE, 110*REFRESH_RATE, 100*REFRESH_RATE, 90*REFRESH_RATE, 0, 0 },
        { 300*REFRESH_RATE, 240*REFRESH_RATE, 180*REFRESH_RATE, 170*REFRESH_RATE, 124*REFRESH_RATE, 150*REFRESH_RATE, 140*REFRESH_RATE, 130*REFRESH_RATE, 120*REFRESH_RATE },
    };
    #endif
    s32 sp10[3];
    s32 var_r31;
    s32 var_r30;

    if (arg1 >= 5) {
        for (var_r31 = 0; var_r31 < 9; var_r31++) {
            if (arg0 < sp88[arg1 - 5][var_r31]) {
                break;
            }
        }
    }
    else if (arg3 != 0) {
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            OSReport("#################### HI-SCORE(%d-%d) : %d\n", arg1, var_r30, GWGameStat.mg_record[var_r30 + 6]);
            arg0 = GWGameStat.mg_record[var_r30 + 6];
            for (var_r31 = 0; var_r31 < 9; var_r31++) {
                if (arg0 >= sp1C[var_r30][var_r31]) {
                    break;
                }
            }
            sp10[var_r30] = var_r31;
        }
        if (sp10[0] <= sp10[1]) {
            var_r31 = sp10[1];
        }
        else {
            var_r31 = sp10[0];
        }
        if (var_r31 <= sp10[2]) {
            var_r31 = sp10[2];
        }
    }
    else {
        for (var_r31 = 0; var_r31 < 9; var_r31++) {
            if (arg0 >= sp1C[arg2][var_r31]) {
                break;
            }
        }
    }
    return var_r31;
}

void fn_1_CA98(s32 arg0, u32 arg1)
{
    s32 sp8[11] = {
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0x00000009,
        0xFFFFFFFF,
        0x00000004,
        0x0000000B,
        0x0000000C,
        0x0000000D,
        0x0000000E,
        0xFFFFFFFF,
    };
    s32 var_r31;
    u32 var_r29;
    u32 var_r28;

    switch (arg1) {
        case 0:
        case 1:
        case 2:
        case 10:
            break;
        case 4:
            var_r31 = fn_1_C898(-1, arg1, 0, 1);
            HuWinInsertMesSet(arg0, ((arg1 - 4) * 0xA) + 0x330000 + var_r31 + 0x51, 3);
            break;
        case 5:
        case 6:
        case 7:
        case 9:
            var_r31 = fn_1_C898(GWGameStat.mg_record[sp8[arg1]], arg1, 0, 0);
            HuWinInsertMesSet(arg0, ((arg1 - 4) * 0xA) + 0x330000 + var_r31 + 0x51, 3);
        case 3:
            OSReport("#################### HI-SCORE(%d) : %d\n", arg1, GWGameStat.mg_record[sp8[arg1]]);
            var_r31 = GWGameStat.mg_record[sp8[arg1]];
            #if VERSION_NTSC
            if (var_r31 < 0xA) {
                sprintf(lbl_1_bss_FC, "  %d", var_r31);
            }
            else if (var_r31 < 0x64) {
                sprintf(lbl_1_bss_FC, " %d", var_r31);
            }
            else {
                sprintf(lbl_1_bss_FC, "%d", var_r31);
            }
            #else
            sprintf(lbl_1_bss_FC, " %d", var_r31);
            #endif
            HuWinInsertMesSet(arg0, (u32)lbl_1_bss_FC, 0);
            break;
        case 8:
            OSReport("#################### HI-SCORE(%d) : %d\n", arg1, GWGameStat.mg_record[sp8[arg1]]);
            var_r31 = GWGameStat.mg_record[sp8[arg1]];
            var_r29 = var_r31 / (600 *REFRESH_RATE);
            var_r31 -= var_r29 * (600 *REFRESH_RATE);
            var_r28 = var_r31 / (60 *REFRESH_RATE);
            var_r31 -= var_r28 * (60 *REFRESH_RATE);
            sprintf(lbl_1_bss_F4, " %d", var_r28);
            HuWinInsertMesSet(arg0, (u32)lbl_1_bss_F4, 0);
            var_r29 = var_r31 / (10 *REFRESH_RATE);
            var_r31 -= var_r29 * (10 *REFRESH_RATE);
            var_r28 = var_r31 / REFRESH_RATE;
            var_r31 -= var_r28 * REFRESH_RATE;
            sprintf(lbl_1_bss_EC, "%d%d", var_r29, var_r28);
            HuWinInsertMesSet(arg0, (u32)lbl_1_bss_EC, 1);
            var_r31 = (101.5/REFRESH_RATE) * (float)var_r31;
            var_r29 = var_r31 / 10;
            var_r31 -= var_r29 * 0xA;
            var_r28 = var_r31;
            if (GWGameStat.mg_record[sp8[arg1]] >= ((600*REFRESH_RATE)-1)) {
                sprintf(lbl_1_bss_E4, "99");
            }
            else {
                sprintf(lbl_1_bss_E4, "%d%d", var_r29, var_r28);
            }
            HuWinInsertMesSet(arg0, (u32)lbl_1_bss_E4, 2);
            var_r31 = fn_1_C898(GWGameStat.mg_record[sp8[arg1]], arg1, 0, 0);
            HuWinInsertMesSet(arg0, ((arg1 - 4) * 0xA) + 0x330000 + var_r31 + 0x51, 3);
            break;
        default:
            break;
    }
}

void fn_1_CF10(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r28;

    var_r31 = lbl_1_data_324;
    for (var_r30 = 0; var_r30 < 0x25; var_r30++) {
        HuSprAttrSet(var_r31, var_r30, 4);
    }
    if (arg0 != -1) {
        s32 sp8[11][4] = {
            { 0x00370000, 0x00370001, 0x00370002, 0x0017003E },
            { 0x00370003, 0x00370004, 0x00370005, 0x0017003F },
            { 0x00370006, 0x00370007, 0x00370008, 0x0017003D },
            { 0x00370009, 0x0037000A, 0x0037000B, 0x00170034 },
            { 0x0037000C, 0x0037000D, 0x0037000E, 0x00170033 },
            { 0x0037000F, 0x00370010, 0x00370011, 0x0017002A },
            { 0x00370012, 0x00370013, 0x00370014, 0x00170039 },
            { 0x00370015, 0x00370016, 0x00370017, 0x0017003A },
            { 0x00370018, 0x00370019, 0x0037001A, 0x0017003B },
            { 0x0037001B, 0x0037001C, 0x0037001D, 0x0017003C },
            { 0x0037001E, 0x0037001F, 0x00370020, 0x00170021 },
        };
        var_r28 = HuSprCreate(HuSprAnimReadFile(arg0 + DATA_MAKE_NUM(DATADIR_MPEX, 0x22)), 0x7D0, 0);
        HuSprGrpMemberSet(var_r31, 5, var_r28);
        lbl_1_data_328 = fn_1_1D02C(sp8[arg0][3]);
        HuSprGrpPosSet(lbl_1_data_328, 288.0f, -437.0f);
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            lbl_1_data_32C[var_r30] = HuWinCreate(0.0f, 0.0f, 0x136, 0x78, 0);
            HuWinBGTPLvlSet(lbl_1_data_32C[var_r30], 0.0f);
            HuWinMesSpeedSet(lbl_1_data_32C[var_r30], 0);
            HuWinDispOn(lbl_1_data_32C[var_r30]);
            if (sp8[arg0][var_r30] != -1) {
                if (var_r30 == 2) {
                    fn_1_CA98(lbl_1_data_32C[2], arg0);
                }
                HuWinMesSet(lbl_1_data_32C[var_r30], sp8[arg0][var_r30]);
            }
            HuWinPosSet(lbl_1_data_32C[var_r30], -485.0f, (var_r30 << 7) + 0x70);
        }
        if (arg0 != 0xA) {
            HuSprAttrReset(var_r31, 0, 4);
            HuSprPosSet(var_r31, 0, 288.0f, 240.0f);
            HuSprTPLvlSet(var_r31, 0, 0.0f);
        }
        else {
            HuSprAttrReset(var_r31, 0x23, 4);
            HuSprPosSet(var_r31, 0x23, 288.0f, 240.0f);
            HuSprTPLvlSet(var_r31, 0x23, 0.0f);
        }
        HuSprAttrReset(var_r31, 1, 4);
        HuSprPosSet(var_r31, 1, -331.0f, 272.0f);
        HuSprAttrReset(var_r31, 2, 4);
        HuSprPosSet(var_r31, 2, 452.0f, 911.0f);
        HuSprAttrReset(var_r31, 3, 4);
        HuSprPosSet(var_r31, 3, 288.0f, -437.0f);
        HuSprAttrReset(var_r31, 4, 4);
        HuSprPosSet(var_r31, 4, 952.0f, 212.0f);
        HuSprAttrReset(var_r31, 5, 4);
        HuSprPosSet(var_r31, 5, 952.0f, 212.0f);
        HuSprScaleSet(var_r31, 5, 0.5f, 0.5f);
        HuSprAttrReset(var_r31, 6, 4);
        HuSprPosSet(var_r31, 6, 952.0f, 212.0f);
    }
}

void fn_1_D3AC(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_data_324;
    for (var_r31 = 0; var_r31 < 0x25; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    if (arg0 != -1) {
        HuSprGrpMemberKill(var_r30, 5);
        HuSprGrpKill(lbl_1_data_328);
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            HuWinKill(lbl_1_data_32C[var_r31]);
        }
    }
}

void fn_1_D468(s32 arg0)
{
    s32 var_r28;
    s32 var_r30;
    s32 var_r31;

    var_r31 = lbl_1_data_324;
    fn_1_CF10(arg0);
    if (arg0 != 0xA) {
        HuSprTPLvlSet(var_r31, 0, 1.0f);
    }
    else {
        HuSprTPLvlSet(var_r31, 0x23, 1.0f);
    }
    HuSprPosSet(var_r31, 3, 288.0f, 63.0f);
    HuSprGrpPosSet(lbl_1_data_328, 288.0f, 63.0f);
    HuSprPosSet(var_r31, 1, 169.0f, 272.0f);
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        HuWinPosSet(lbl_1_data_32C[var_r30], 14.0f, (var_r30 << 7) + 0x70);
    }
    HuSprPosSet(var_r31, 4, 452.0f, 212.0f);
    HuSprPosSet(var_r31, 5, 452.0f, 212.0f);
    HuSprPosSet(var_r31, 6, 452.0f, 212.0f);
    HuSprPosSet(var_r31, 2, 452.0f, 411.0f);
    var_r28 = lbl_1_bss_63C[2];
    if (arg0 <= 3) {
        fn_1_1A5A4(0);
    }
    else {
        fn_1_1A5A4(1);
    }
    HuSprGrpPosSet(var_r28, 452.0f, 355.0f);
}

void fn_1_D6AC(s32 arg0)
{
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r26;

    var_r30 = lbl_1_data_324;
    fn_1_CF10(arg0);
    for (var_r31 = 0; var_r31 <= 0x1E; var_r31++) {
        fn_1_1B7D0(1);
        var_f31 = fn_1_1B64C(0.0f, 1.0f, var_r31, 30.0f);
        if (arg0 != 0xA) {
            HuSprTPLvlSet(var_r30, 0, var_f31);
        }
        else {
            HuSprTPLvlSet(var_r30, 0x23, var_f31);
        }
    }
    if (arg0 != 0xA) {
        HuSprTPLvlSet(var_r30, 0, 1.0f);
    }
    else {
        HuSprTPLvlSet(var_r30, 0x23, 1.0f);
    }
    for (var_r31 = 0; var_r31 <= 0x1E; var_r31++) {
        fn_1_1B7D0(1);
        var_r29 = fn_1_1B64C(-500.0f, 0.0f, var_r31, 30.0f);
        HuSprPosSet(var_r30, 3, 288.0f, var_r29 + 0x3F);
        HuSprGrpPosSet(lbl_1_data_328, 288.0f, var_r29 + 0x3F);
        HuSprPosSet(var_r30, 1, var_r29 + 0xA9, 272.0f);
        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            HuWinPosSet(lbl_1_data_32C[var_r28], var_r29 + 0xE, (var_r28 << 7) + 0x70);
        }
        var_r29 = fn_1_1B64C(500.0f, 0.0f, var_r31, 30.0f);
        HuSprPosSet(var_r30, 4, var_r29 + 0x1C4, 212.0f);
        HuSprPosSet(var_r30, 5, var_r29 + 0x1C4, 212.0f);
        HuSprPosSet(var_r30, 6, var_r29 + 0x1C4, 212.0f);
        HuSprPosSet(var_r30, 2, 452.0f, var_r29 + 0x19B);
        if (arg0 != 0xA) {
            var_r26 = lbl_1_bss_63C[2];
            var_f30 = fn_1_1B64C(112.0f, 452.0f, var_r31, 30.0f);
            var_f29 = fn_1_1B64C(72.0f, 355.0f, var_r31, 30.0f);
            HuSprGrpPosSet(var_r26, var_f30, var_f29);
        }
    }
}

void fn_1_DBD0(s32 arg0)
{
    float var_f31;
    float var_f30;
    float var_f29;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r25;
    s32 var_r24;

    var_r30 = lbl_1_data_324;
    for (var_r31 = 0; var_r31 <= 0x1E; var_r31++) {
        fn_1_1B7D0(1);
        var_r29 = fn_1_1B574(0.0f, -500.0f, var_r31, 30.0f);
        HuSprPosSet(var_r30, 3, 288.0f, var_r29 + 0x3F);
        HuSprGrpPosSet(lbl_1_data_328, 288.0f, var_r29 + 0x3F);
        HuSprPosSet(var_r30, 1, var_r29 + 0xA9, 272.0f);
        for (var_r27 = 0; var_r27 < 3; var_r27++) {
            HuWinPosSet(lbl_1_data_32C[var_r27], var_r29 + 0xE, (var_r27 << 7) + 0x70);
        }
        var_r29 = fn_1_1B574(0.0f, 500.0f, var_r31, 30.0f);
        HuSprPosSet(var_r30, 4, var_r29 + 0x1C4, 212.0f);
        HuSprPosSet(var_r30, 5, var_r29 + 0x1C4, 212.0f);
        HuSprPosSet(var_r30, 6, var_r29 + 0x1C4, 212.0f);
        HuSprPosSet(var_r30, 2, 452.0f, var_r29 + 0x19B);
        if (arg0 != 0xA) {
            var_r24 = lbl_1_bss_63C[2];
            var_f30 = fn_1_1B574(452.0f, 112.0f, var_r31, 30.0f);
            var_f29 = fn_1_1B574(355.0f, 72.0f, var_r31, 30.0f);
            HuSprGrpPosSet(var_r24, var_f30, var_f29);
        }
    }
    for (var_r31 = 0; var_r31 <= 0x1E; var_r31++) {
        fn_1_1B7D0(1);
        var_f31 = fn_1_1B574(1.0f, 0.0f, var_r31, 30.0f);
        if (arg0 != 0xA) {
            HuSprTPLvlSet(var_r30, 0, var_f31);
        }
        else {
            HuSprTPLvlSet(var_r30, 0x23, var_f31);
        }
    }
    if (arg0 != 0xA) {
        HuSprTPLvlSet(var_r30, 0, 0.0f);
    }
    else {
        HuSprTPLvlSet(var_r30, 0x23, 0.0f);
    }
    var_r25 = lbl_1_data_324;
    for (var_r28 = 0; var_r28 < 0x25; var_r28++) {
        HuSprAttrSet(var_r25, var_r28, 4);
    }
    if (arg0 != -1) {
        HuSprGrpMemberKill(var_r25, 5);
        HuSprGrpKill(lbl_1_data_328);
        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            HuWinKill(lbl_1_data_32C[var_r28]);
        }
    }
}

void fn_1_E174(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = lbl_1_data_324;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 7, 4);
        HuSprPosSet(var_r30, var_r31 + 7, 788.0f, (var_r31 * 0x38) + 0xB8);
    }
    for (var_r29 = 0; var_r29 <= 0x3C; var_r29++) {
        fn_1_1B7D0(1);
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            var_f31 = fn_1_1B64C(1000.0f, 0.0f, var_r29, 0x3C - ((2 - var_r31) * 5));
            HuSprPosSet(var_r30, var_r31 + 7, 288.0f + var_f31, (var_r31 * 0x38) + 0xB8);
        }
    }
    HuSprAttrReset(var_r30, 0x22, 4);
    HuSprPosSet(var_r30, 0x22, 185.0f, (lbl_1_bss_3B0.unk_10 * 0x38) + 0xA0);
}

void fn_1_E384(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = lbl_1_data_324;
    HuSprAttrSet(var_r30, 0x22, 4);
    HuSprPosSet(var_r30, 0x22, 125.0f, 190.0f);
    for (var_r29 = 0; var_r29 <= 0x3C; var_r29++) {
        fn_1_1B7D0(1);
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            var_f31 = fn_1_1B574(0.0f, -1000.0f, var_r29, 0x3C - ((2 - var_r31) * 5));
            HuSprPosSet(var_r30, var_r31 + 7, 288.0f + var_f31, (var_r31 * 0x38) + 0xB8);
        }
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r30, var_r31 + 7, 4);
        HuSprPosSet(var_r30, var_r31 + 7, 288.0f, (var_r31 * 0x38) + 0xB8);
    }
}

void fn_1_E568(void)
{
    s32 sp10;
    s32 spC;
    s32 sp8;
    float var_f31;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    u32 var_r27;
    u32 var_r26;
    s32 var_r25;

    var_r29 = lbl_1_data_324;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        sp10 = rand8() % 10;
        spC = rand8() % 60;
        sp8 = rand8() % 100;
        HuSprAttrReset(var_r29, var_r31 + 0xA, 4);
        HuSprPosSet(var_r29, var_r31 + 0xA, 1288.0f, (var_r31 * 0x38) + 0xB8);
        for (var_r28 = 0; var_r28 < 7; var_r28++) {
            HuSprAttrReset(var_r29, 0xD + var_r28 + (var_r31 * 7), 4);
            HuSprPosSet(var_r29, 0x0D + var_r28 + (var_r31 * 7), (var_r28 * 0x14) + 0x512, (var_r31 * 0x38) + 0xBA);
        }
        var_r30 = GWGameStat.mg_record[var_r31 + 6];
        var_r27 = var_r30 / (600*REFRESH_RATE);
        var_r30 -= var_r27 * (600*REFRESH_RATE);
        var_r26 = var_r30 / (60*REFRESH_RATE);
        var_r30 -= var_r26 * (60*REFRESH_RATE);
        HuSprBankSet(var_r29, (var_r31 * 7) + 0xD, var_r26);
        HuSprBankSet(var_r29, (var_r31 * 7) + 0xE, 0xA);
        var_r27 = var_r30 / (10*REFRESH_RATE);
        var_r30 -= var_r27 * (10*REFRESH_RATE);
        var_r26 = var_r30 / REFRESH_RATE;
        var_r30 -= var_r26 * REFRESH_RATE;
        HuSprBankSet(var_r29, (var_r31 * 7) + 0xF, var_r27);
        HuSprBankSet(var_r29, (var_r31 * 7) + 0x10, var_r26);
        HuSprBankSet(var_r29, (var_r31 * 7) + 0x11, 0xB);
        var_r30 = (100.0/REFRESH_RATE) * (float)var_r30;
        var_r27 = var_r30 / 10;
        var_r30 -= var_r27 * 0xA;
        var_r26 = var_r30;
        if (GWGameStat.mg_record[var_r31 + 6] == ((600*REFRESH_RATE)-1)) {
            HuSprBankSet(var_r29, (var_r31 * 7) + 0x12, 9);
            HuSprBankSet(var_r29, (var_r31 * 7) + 0x13, 9);
        }
        else {
            HuSprBankSet(var_r29, (var_r31 * 7) + 0x12, var_r27);
            HuSprBankSet(var_r29, (var_r31 * 7) + 0x13, var_r26);
        }
    }
    for (var_r25 = 0; var_r25 <= 0x3C; var_r25++) {
        fn_1_1B7D0(1);
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            var_f31 = fn_1_1B64C(1000.0f, 0.0f, var_r25, 0x3C - ((2 - var_r31) * 5));
            HuSprPosSet(var_r29, var_r31 + 0xA, 288.0f + var_f31, (var_r31 * 0x38) + 0xB8);
            for (var_r28 = 0; var_r28 < 7; var_r28++) {
                HuSprPosSet(var_r29, 0xD + var_r28 + (var_r31 * 7), var_f31 + ((var_r28 * 0x14) + 0x12A), (var_r31 * 0x38) + 0xBA);
            }
        }
    }
    HuSprAttrReset(var_r29, 0x22, 4);
    HuSprPosSet(var_r29, 0x22, 110.0f, (lbl_1_bss_3B0.unk_10 * 0x38) + 0xA0);
}

void fn_1_EB1C(void)
{
    float var_f31;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;

    var_r29 = lbl_1_data_324;
    HuSprAttrSet(var_r29, 0x22, 4);
    HuSprPosSet(var_r29, 0x22, 125.0f, 184.0f);
    for (var_r28 = 0; var_r28 <= 0x3C; var_r28++) {
        fn_1_1B7D0(1);
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            var_f31 = fn_1_1B574(0.0f, -1000.0f, var_r28, 0x3C - ((2 - var_r31) * 5));
            HuSprPosSet(var_r29, var_r31 + 0xA, 288.0f + var_f31, (var_r31 * 0x38) + 0xB8);
            for (var_r30 = 0; var_r30 < 7; var_r30++) {
                HuSprPosSet(var_r29, 0xD + var_r30 + (var_r31 * 7), var_f31 + ((var_r30 * 0x14) + 0x12A), (var_r31 * 0x38) + 0xBA);
            }
        }
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r29, var_r31 + 0xA, 4);
        for (var_r30 = 0; var_r30 < 7; var_r30++) {
            HuSprAttrSet(var_r29, 0xD + var_r30 + (var_r31 * 7), 4);
        }
    }
}

void fn_1_ED78(s32 arg0, s32 arg1)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = lbl_1_data_324;
    {
        s32 spC[3] = { 4, 11, 12 };
        for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
            fn_1_1B7D0(1);
            if (var_r31 <= 5) {
                var_f30 = fn_1_1B64C(1.0f, 0.0f, var_r31, 5.0f);
            }
            else {
                var_f30 = fn_1_1B64C(0.0f, 1.0f, var_r31, var_r31 - 5);
            }
            if (lbl_1_bss_1B0 == 4) {
                HuSprTPLvlSet(var_r30, 5, var_f30);
            }
            var_f31 = fn_1_1B64C((arg1 * 0x38) + 0xA0, (arg0 * 0x38) + 0xA0, var_r31, 10.0f);
            if (lbl_1_bss_1B0 == 4) {
                HuSprPosSet(var_r30, 0x22, 110.0f, var_f31);
            }
            else {
                HuSprPosSet(var_r30, 0x22, 185.0f, var_f31);
            }
            if ((lbl_1_bss_1B0 == 4) && (var_r31 == 5)) {
                HuSprGrpMemberKill(var_r30, 5);
                var_r29 = HuSprCreate(HuSprAnimReadFile(spC[arg0] + DATA_MAKE_NUM(DATADIR_MPEX, 0x22)), 0x7D0, 0);
                HuSprGrpMemberSet(var_r30, 5, var_r29);
                HuSprPosSet(var_r30, 5, 452.0f, 212.0f);
                HuSprScaleSet(var_r30, 5, 0.5f, 0.5f);
                HuSprTPLvlSet(var_r30, 5, 0.0f);
            }
        }
    }
}

void fn_1_F0C0(void)
{
    float sp8[2];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = HuSprGrpCreate(3);
    lbl_1_bss_E0 = var_r30;
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x16)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r30, 0, var_r29);
    HuSprPosSet(var_r30, 0, 0.0f, 88.0f);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x18)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r30, 1, var_r29);
    HuSprPosSet(var_r30, 1, 0.0f, 25.0f);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x1A)), 0x3E8, 0);
    HuSprGrpMemberSet(var_r30, 2, var_r29);
    HuSprPosSet(var_r30, 2, 0.0f, 0.0f);
    HuSprScaleSet(var_r30, 2, 0.9f, 0.65f);
    HuSprTPLvlSet(var_r30, 2, 0.8f);
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x2F));
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x30));
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x31));
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x32));
        lbl_1_bss_C8[var_r31] = HuWinCreate(0.0f, 0.0f, sp8[0], sp8[1], 0);
        HuWinBGTPLvlSet(lbl_1_bss_C8[var_r31], 0.0f);
        HuWinMesSpeedSet(lbl_1_bss_C8[var_r31], 0);
        HuWinDispOff(lbl_1_bss_C8[var_r31]);
        HuWinPosSet(lbl_1_bss_C8[var_r31], 304.0f, 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1F)) - 500.0f));
    }
    fn_1_F47C();
    fn_1_F730();
}

void fn_1_F40C(void)
{
    s32 var_r31;
    s32 var_r30 = lbl_1_bss_E0;
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        HuWinKill(lbl_1_bss_C8[var_r31]);
    }
    HuSprGrpKill(var_r30);
}

void fn_1_F47C(void)
{
    float sp8[2];
    s32 var_r31;

    s32 var_r30 = lbl_1_bss_E0;
    lbl_1_bss_3B0.unk_0C = 0;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprAttrReset(var_r30, 0, 4);
    HuSprPosSet(var_r30, 0, 0.0f, 92.0f);
    HuSprAttrReset(var_r30, 1, 4);
    HuSprPosSet(var_r30, 1, 0.0f, 25.0f);
    lbl_1_bss_3B0.unk_0C = 0;
    HuSprPosSet(var_r30, 2, -3.0f, (lbl_1_bss_3B0.unk_0C * 0x19) + 0x3C);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuWinDispOn(lbl_1_bss_C8[var_r31]);
        if (lbl_1_bss_180[var_r31] == 1) {
            HuWinMesSet(lbl_1_bss_C8[var_r31], var_r31 + MAKE_MESSID(0x33, 0x2F));
        }
        else {
            HuWinMesSet(lbl_1_bss_C8[var_r31], MAKE_MESSID(0x33, 0x2E));
        }
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x33, 0x30));
        HuWinPosSet(lbl_1_bss_C8[var_r31], 288.0f - (sp8[0] / 2), 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1F)) - 500.0f));
    }
    HuSprGrpPosSet(var_r30, 288.0f, -460.0f);
}

void fn_1_F730(void)
{
    float sp8[2];
    s32 var_r31;

    s32 var_r30 = lbl_1_bss_E0;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuWinDispOff(lbl_1_bss_C8[var_r31]);
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x33, 0x30));
        HuWinPosSet(lbl_1_bss_C8[var_r31], 288.0f - (sp8[0] / 2), 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1F)) - 500.0f));
    }
    HuSprGrpPosSet(var_r30, 288.0f, -460.0f);
}

void fn_1_F8A4(void)
{
    float sp10[2];
    float sp8[2];
    float var_f31;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    s32 var_r27 = lbl_1_bss_E0;
    sp10[0] = sp10[1] = 0.0f;
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x2E));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x2F));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x30));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x31));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x32));
    var_r30 = lbl_1_bss_E0;
    lbl_1_bss_3B0.unk_0C = 0;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprAttrReset(var_r30, 0, 4);
    HuSprPosSet(var_r30, 0, 0.0f, 92.0f);
    HuSprAttrReset(var_r30, 1, 4);
    HuSprPosSet(var_r30, 1, 0.0f, 25.0f);
    lbl_1_bss_3B0.unk_0C = 0;
    HuSprPosSet(var_r30, 2, -3.0f, (lbl_1_bss_3B0.unk_0C * 0x19) + 0x3C);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuWinDispOn(lbl_1_bss_C8[var_r31]);
        if (lbl_1_bss_180[var_r31] == 1) {
            HuWinMesSet(lbl_1_bss_C8[var_r31], var_r31 + MAKE_MESSID(0x33, 0x2F));
        }
        else {
            HuWinMesSet(lbl_1_bss_C8[var_r31], MAKE_MESSID(0x33, 0x2E));
        }
        HuWinMesMaxSizeGet(1, sp8, 0x330030);
        HuWinPosSet(lbl_1_bss_C8[var_r31], 288.0f - (sp8[0] / 2), 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1F)) - 500.0f));
    }
    HuSprGrpPosSet(var_r30, 288.0f, -460.0f);
    for (var_r29 = 0; var_r29 < 0x3C; var_r29++) {
        fn_1_1B7D0(1);
        if (var_r29 <= 0x32) {
            var_f31 = fn_1_1B64C(-500.0f, 10.0f, var_r29, 50.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, 0.0f, var_r29 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r27, 288.0f, 64.0f + (40.0f + var_f31));
        for (var_r28 = 0; var_r28 < 4; var_r28++) {
            HuWinPosSet(lbl_1_bss_C8[var_r28], 288.0f - (sp10[0] / 2), 64.0f + (40.0f + (var_f31 + ((60.0f - (sp10[1] / 2)) + (var_r28 * 0x1F)))));
        }
    }
}

void fn_1_FDA0(void)
{
    float sp10[2];
    float sp8[2];
    float var_f31;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    s32 var_r27 = lbl_1_bss_E0;
    sp10[0] = sp10[1] = 0.0f;

    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x2E));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x2F));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x30));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x31));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x32));
    for (var_r30 = 0; var_r30 < 0x3C; var_r30++) {
        fn_1_1B7D0(1);
        if (var_r30 <= 0xA) {
            var_f31 = fn_1_1B64C(0.0f, 10.0f, var_r30, 10.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, -500.0f, var_r30 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(var_r27, 288.0f, 64.0f + (40.0f + var_f31));
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            HuWinPosSet(lbl_1_bss_C8[var_r29], 288.0f - (sp10[0] / 2), 64.0f + (40.0f + (var_f31 + ((60.0f - (sp10[1] / 2)) + (var_r29 * 0x1F)))));
        }
    }
    var_r28 = lbl_1_bss_E0;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r28, var_r31, 4);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuWinDispOff(lbl_1_bss_C8[var_r31]);
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x33, 0x30));
        HuWinPosSet(lbl_1_bss_C8[var_r31], 288.0f - (sp8[0] / 2), 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1F)) - 500.0f));
    }
    HuSprGrpPosSet(var_r28, 288.0f, -460.0f);
}

void fn_1_1015C(void)
{
    float sp8[2];
    s32 var_r31 = lbl_1_bss_E0;
    HuWinMesMaxSizeGet(1, sp8, 0x330030);
    HuSprAttrReset(var_r31, 2, 4);
    HuSprPosSet(var_r31, 2, 0.0f, 40.0f + ((60.0f - sp8[1]) + (lbl_1_bss_3B0.unk_0C * 0x1F)));
}

void fn_1_10228(void)
{
    s32 var_r31 = lbl_1_bss_E0;
    HuSprAttrSet(var_r31, 2, 4);
}

void fn_1_10268(s32 arg0)
{
    float spC[2];
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    s32 var_r28 = lbl_1_bss_E0;
    HuWinMesMaxSizeGet(1, spC, MAKE_MESSID(0x33, 0x30));
    var_r29 = lbl_1_bss_3B0.unk_0C;
    var_r31 = lbl_1_bss_3B0.unk_0C + arg0;
    if (var_r31 > 3) {
        var_r31 = 0;
    }
    else if (var_r31 < 0) {
        var_r31 = 3;
    }
    for (var_r30 = 0; var_r30 <= 5; var_r30++) {
        fn_1_1B7D0(1);
        var_f31 = 40.0f + ((60.0f - spC[1]) + (var_r29 * 0x1F));
        var_f30 = 40.0f + ((60.0f - spC[1]) + (var_r31 * 0x1F));
        var_f29 = fn_1_1B64C(var_f31, var_f30, var_r30, 5.0f);
        HuSprPosSet(var_r28, 2, -4.0f, var_f29);
    }
    lbl_1_bss_3B0.unk_0C = var_r31;
}

void fn_1_1045C(void)
{
    float sp8[2];
    s32 var_r31;
    s32 var_r29;

    s32 var_r30 = HuSprGrpCreate(3);
    lbl_1_bss_C4 = var_r30;
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x17)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r30, 0, var_r29);
    HuSprPosSet(var_r30, 0, 0.0f, 118.0f);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x19)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r30, 1, var_r29);
    HuSprPosSet(var_r30, 1, 0.0f, 25.0f);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x1A)), 0x3E8, 0);
    HuSprGrpMemberSet(var_r30, 2, var_r29);
    HuSprPosSet(var_r30, 2, 0.0f, 0.0f);
    HuSprPosSet(var_r30, 2, 0.0f, 0.0f);
    HuSprScaleSet(var_r30, 2, 0.9f, 0.65f);
    HuSprTPLvlSet(var_r30, 2, 0.8f);
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x33));
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x34));
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x35));
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x36));
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x37));
        fn_1_125DC(sp8, MAKE_MESSID(0x33, 0x38));
        lbl_1_bss_C8[var_r31] = HuWinCreate(0.0f, 0.0f, sp8[0], sp8[1], 0);
        HuWinBGTPLvlSet(lbl_1_bss_C8[var_r31], 0.0f);
        HuWinMesSpeedSet(lbl_1_bss_C8[var_r31], 0);
        HuWinDispOff(lbl_1_bss_C8[var_r31]);
        HuWinPosSet(lbl_1_bss_C8[var_r31], 304.0f, 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1D)) - 500.0f));
    }
    fn_1_1085C();
    fn_1_10ABC();
    (void)var_r31;
}

void fn_1_107EC(void)
{
    s32 var_r30;
    s32 var_r31;

    var_r30 = lbl_1_bss_C4;
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        HuWinKill(lbl_1_bss_C8[var_r31]);
    }
    HuSprGrpKill(var_r30);
}

void fn_1_1085C(void)
{
    float sp8[2];
    s32 var_r31;

    s32 var_r30 = lbl_1_bss_C4;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprAttrReset(var_r30, 0, 4);
    HuSprAttrReset(var_r30, 1, 4);
    lbl_1_bss_3B0.unk_0C = 0;
    HuSprPosSet(var_r30, 2, -3.0f, (lbl_1_bss_3B0.unk_0C * 0x19) + 0x3C);
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        HuWinDispOn(lbl_1_bss_C8[var_r31]);
        if (lbl_1_bss_180[var_r31 + 4] == 1) {
            HuWinMesSet(lbl_1_bss_C8[var_r31], var_r31 + MAKE_MESSID(0x33, 0x33));
        }
        else {
            HuWinMesSet(lbl_1_bss_C8[var_r31], MAKE_MESSID(0x33, 0x2E));
        }
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x33, 0x33));
        HuWinPosSet(lbl_1_bss_C8[var_r31], 288.0f - (sp8[0] / 2), 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1D)) - 500.0f));
    }
    HuSprGrpPosSet(var_r30, 288.0f, -460.0f);
}

void fn_1_10ABC(void)
{
    float sp8[2];
    s32 var_r31;

    s32 var_r30 = lbl_1_bss_C4;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        HuWinDispOff(lbl_1_bss_C8[var_r31]);
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x33, 0x33));
        HuWinPosSet(lbl_1_bss_C8[var_r31], 288.0f - (sp8[0] / 2), 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1D)) - 500.0f));
    }
    HuSprGrpPosSet(var_r30, 288.0f, -460.0f);
}

void fn_1_10C30(void)
{
    float sp10[2];
    float sp8[2];
    float var_f31;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r27 = lbl_1_bss_C4;
    sp10[0] = sp10[1] = 0.0f;
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x2E));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x33));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x34));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x35));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x36));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x37));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x38));
    var_r28 = lbl_1_bss_C4;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r28, var_r31, 4);
    }
    HuSprAttrReset(var_r28, 0, 4);
    HuSprAttrReset(var_r28, 1, 4);
    lbl_1_bss_3B0.unk_0C = 0;
    HuSprPosSet(var_r28, 2, -3.0f, (lbl_1_bss_3B0.unk_0C * 0x19) + 0x3C);
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        HuWinDispOn(lbl_1_bss_C8[var_r31]);
        if (lbl_1_bss_180[var_r31 + 4] == 1) {
            HuWinMesSet(lbl_1_bss_C8[var_r31], var_r31 + MAKE_MESSID(0x33, 0x33));
        }
        else {
            HuWinMesSet(lbl_1_bss_C8[var_r31], MAKE_MESSID(0x33, 0x2E));
        }
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x33, 0x33));
        HuWinPosSet(lbl_1_bss_C8[var_r31], 288.0f - (sp8[0] / 2), 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1D)) - 500.0f));
    }
    HuSprGrpPosSet(var_r28, 288.0f, -460.0f);
    for (var_r30 = 0; var_r30 < 0x3C; var_r30++) {
        fn_1_1B7D0(1);
        if (var_r30 <= 0x32) {
            var_f31 = fn_1_1B64C(-500.0f, 10.0f, var_r30, 50.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, 0.0f, var_r30 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r27, 288.0f, 64.0f + (40.0f + var_f31));
        for (var_r29 = 0; var_r29 < 6; var_r29++) {
            HuWinPosSet(lbl_1_bss_C8[var_r29], 288.0f - (sp10[0] / 2), 64.0f + (40.0f + (var_f31 + ((60.0f - (sp10[1] / 2)) + (var_r29 * 0x1D)))));
        }
    }
}

void fn_1_110F8(void)
{
    float sp10[2];
    float sp8[2];
    float var_f31;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r27 = lbl_1_bss_C4;
    sp10[0] = sp10[1] = 0.0f;
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x2E));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x33));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x34));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x35));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x36));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x37));
    fn_1_125DC(sp10, MAKE_MESSID(0x33, 0x38));
    for (var_r30 = 0; var_r30 < 0x3C; var_r30++) {
        fn_1_1B7D0(1);
        if (var_r30 <= 0xA) {
            var_f31 = fn_1_1B64C(0.0f, 10.0f, var_r30, 10.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, -500.0f, var_r30 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(var_r27, 288.0f, 64.0f + (40.0f + var_f31));
        for (var_r29 = 0; var_r29 < 6; var_r29++) {
            HuWinPosSet(lbl_1_bss_C8[var_r29], 288.0f - (sp10[0] / 2), 64.0f + (40.0f + (var_f31 + ((60.0f - (sp10[1] / 2)) + (var_r29 * 0x1D)))));
        }
    }
    var_r28 = lbl_1_bss_C4;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r28, var_r31, 4);
    }
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        HuWinDispOff(lbl_1_bss_C8[var_r31]);
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x33, 0x33));
        HuWinPosSet(lbl_1_bss_C8[var_r31], 288.0f - (sp8[0] / 2), 40.0f + (((60.0f - (sp8[1] / 2)) + (var_r31 * 0x1D)) - 500.0f));
    }
    HuSprGrpPosSet(var_r28, 288.0f, -460.0f);
}

void fn_1_114D4(void)
{
    float sp8[2];
    s32 var_r31 = lbl_1_bss_C4;
    HuWinMesMaxSizeGet(1, sp8, 0x330033);
    HuSprAttrReset(var_r31, 2, 4);
    HuSprPosSet(var_r31, 2, 0.0f, 40.0f + ((60.0f - sp8[1]) + (lbl_1_bss_3B0.unk_0C * 0x1D)));
}

void fn_1_115A0(void)
{
    s32 var_r31 = lbl_1_bss_C4;
    HuSprAttrSet(var_r31, 2, 4);
}

void fn_1_115E0(s32 arg0)
{
    float spC[2];
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_C4;
    HuWinMesMaxSizeGet(1, spC, MAKE_MESSID(0x33, 0x33));
    var_r29 = lbl_1_bss_3B0.unk_0C;
    var_r31 = lbl_1_bss_3B0.unk_0C + arg0;
    if (var_r31 > 5) {
        var_r31 = 0;
    }
    else if (var_r31 < 0) {
        var_r31 = 5;
    }
    for (var_r30 = 0; var_r30 <= 5; var_r30++) {
        fn_1_1B7D0(1);
        var_f31 = 40.0f + ((60.0f - spC[1]) + (var_r29 * 0x1D));
        var_f30 = 40.0f + ((60.0f - spC[1]) + (var_r31 * 0x1D));
        var_f29 = fn_1_1B64C(var_f31, var_f30, var_r30, 5.0f);
        HuSprPosSet(var_r28, 2, -4.0f, var_f29);
    }
    lbl_1_bss_3B0.unk_0C = var_r31;
}

void fn_1_117D4(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = HuSprGrpCreate(3);
    lbl_1_bss_C0 = var_r30;
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x12)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r30, 0, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x13)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r30, 1, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x14)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r30, 2, var_r31);
    var_r29 = HuSprGrpCreate(1);
    lbl_1_bss_BC = var_r29;
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x15)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r29, 0, var_r31);
    HuSprAttrSet(var_r29, 0, 4);
    fn_1_11984();
    fn_1_119E0();
}

void fn_1_11930(void)
{
    s32 var_r31 = lbl_1_bss_C0;
    s32 var_r30 = lbl_1_bss_BC;
    HuSprGrpKill(var_r31);
    HuSprGrpKill(var_r30);
}

void fn_1_11984(void)
{
    s32 var_r31;
    s32 var_r30 = lbl_1_bss_C0;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
}

void fn_1_119E0(void)
{
    s32 var_r31;
    s32 var_r30 = lbl_1_bss_C0;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
}

void fn_1_11A3C(s32 arg0)
{
    float var_f31;
    float var_f30;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r26;

    var_r29 = lbl_1_bss_C0;
    var_r28 = lbl_1_bss_BC;
    {
        s32 sp8[3][2] = {
            { 0x72, 0xFA },
            { 0x144, 0xE1 },
            { 0xEF, 0x5A },
        };
        var_r26 = lbl_1_bss_C0;
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            HuSprAttrSet(var_r26, var_r30, 4);
        }
        if (lbl_1_bss_3B0.unk_08 != 2) {
            HuSprAttrReset(var_r29, lbl_1_bss_3B0.unk_08, 4);
        }
        HuSprGrpScaleSet(var_r29, 0.0f, 0.0f);
        for (var_r31 = 0; var_r31 <= 0xF; var_r31++) {
            fn_1_1B7D0(1);
            if (var_r31 <= 0xA) {
                var_f31 = fn_1_1B64C(0.0f, 1.0f, var_r31, 10.0f);
                var_f30 = 0.01f;
            }
            else {
                var_f31 = 1.0f;
                var_f30 = fn_1_1B64C(0.01f, 1.0f, var_r31 - 0xA, 5.0f);
            }
            HuSprGrpScaleSet(var_r29, var_f31, var_f30);
            if (arg0 != -1) {
                var_f31 = fn_1_1B64C(sp8[arg0][0], sp8[lbl_1_bss_3B0.unk_08][0], var_r31, 15.0f);
                var_f30 = fn_1_1B64C(sp8[arg0][1], sp8[lbl_1_bss_3B0.unk_08][1], var_r31, 15.0f);
                HuSprGrpPosSet(var_r28, var_f31, var_f30);
            }
        }
        HuSprAttrReset(var_r28, 0, 4);
        if (arg0 == -1) {
            HuSprGrpPosSet(var_r28, sp8[0][0], sp8[0][1]);
        }
    }
}

void fn_1_11E28(void)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r29 = lbl_1_bss_C0;
    var_r28 = lbl_1_bss_BC;
    HuSprAttrSet(var_r28, 0, 4);
    for (var_r31 = 0; var_r31 <= 0xF; var_r31++) {
        fn_1_1B7D0(1);
        if (var_r31 <= 0xA) {
            var_f30 = fn_1_1B64C(1.0f, 0.01f, var_r31, 10.0f);
            var_f31 = 1.0f;
        }
        else {
            var_f30 = 0.01f;
            var_f31 = fn_1_1B64C(1.0f, 0.01f, var_r31 - 0xA, 5.0f);
        }
        HuSprGrpScaleSet(var_r29, var_f31, var_f30);
    }
    var_r27 = lbl_1_bss_C0;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        HuSprAttrSet(var_r27, var_r30, 4);
    }
}

void fn_1_11FC0(omObjData *object, MpexDllUnkStruct4 *arg1)
{
    Vec sp20;
    Vec sp14;

    s32 var_r31 = lbl_1_bss_C0;
    s32 sp8[3] = { 0x64, 0x64, 0xE1 };
    sp20.x = Hu3DData[lbl_1_bss_2D8[lbl_1_bss_3B0.unk_08].unk_00->model[1]].pos.x;
    sp20.y = 0.0f;
    sp20.z = Hu3DData[lbl_1_bss_2D8[lbl_1_bss_3B0.unk_08].unk_00->model[1]].pos.z;
    Hu3D3Dto2D(&sp20, 1, &sp14);
    sp14.y = fn_1_1B714(sp8[lbl_1_bss_3B0.unk_08], 10.0f + sp8[lbl_1_bss_3B0.unk_08], lbl_1_bss_3B0.unk_28++, 360.0f);
    if (lbl_1_bss_3B0.unk_28 >= 0x168) {
        lbl_1_bss_3B0.unk_28 = 0;
    }
    HuSprGrpPosSet(var_r31, sp14.x, (s32)sp14.y);
}

void fn_1_121E8(void)
{
    OSReport("\n\n####################### HI SCORE #######################\n");
    OSReport("HIScore 453(0-99):%d\n", GWGameStat.mg_record[9]);
    if (GWGameStat.mg_record[9] == 0) {
        GWGameStat.mg_record[9] = 0;
    }
    else if (GWGameStat.mg_record[9] >= 0x63) {
        GWGameStat.mg_record[9] = 0x63;
    }
    #if VERSION_NTSC
    OSReport("HIScore 451A(0-35999):%d\n", GWGameStat.mg_record[6]);
    #else
    OSReport("HIScore 451A(0-29999):%d\n", GWGameStat.mg_record[6]);
    #endif
    if (GWGameStat.mg_record[6] == 0) {
        GWGameStat.mg_record[6] = 0;
    }
    else if (GWGameStat.mg_record[6] >= ((REFRESH_RATE*600)-1)) {
        GWGameStat.mg_record[6] = ((REFRESH_RATE*600)-1);
    }
    #if VERSION_NTSC
    OSReport("HIScore 451B(0-35999):%d\n", GWGameStat.mg_record[7]);
    #else
    OSReport("HIScore 451B(0-29999):%d\n", GWGameStat.mg_record[7]);
    #endif
    if (GWGameStat.mg_record[7] == 0) {
        GWGameStat.mg_record[7] = 0;
    }
    else if (GWGameStat.mg_record[7] >= ((REFRESH_RATE*600)-1)) {
        GWGameStat.mg_record[7] = ((REFRESH_RATE*600)-1);
    }
    #if VERSION_NTSC
    OSReport("HIScore 451C(0-35999):%d\n", GWGameStat.mg_record[8]);
    #else
    OSReport("HIScore 451C(0-29999):%d\n", GWGameStat.mg_record[8]);
    #endif
    if (GWGameStat.mg_record[8] == 0) {
        GWGameStat.mg_record[8] = 0;
    }
    else if (GWGameStat.mg_record[8] >= ((REFRESH_RATE*600)-1)) {
        GWGameStat.mg_record[8] = ((REFRESH_RATE*600)-1);
    }
    OSReport("HIScore 442(0-999):%d\n", GWGameStat.mg_record[4]);
    if (GWGameStat.mg_record[4] == 0) {
        GWGameStat.mg_record[4] = 0;
    }
    else if (GWGameStat.mg_record[4] >= 0x3E7) {
        GWGameStat.mg_record[4] = 0x3E7;
    }
    OSReport("HIScore 459(0-99):%d\n", GWGameStat.mg_record[0xB]);
    if (GWGameStat.mg_record[0xB] == 0) {
        GWGameStat.mg_record[0xB] = 0;
    }
    else if (GWGameStat.mg_record[0xB] >= 0x63) {
        GWGameStat.mg_record[0xB] = 0x63;
    }
    OSReport("HIScore 460(0-99):%d\n", GWGameStat.mg_record[0xC]);
    if (GWGameStat.mg_record[0xC] == 0) {
        GWGameStat.mg_record[0xC] = 0;
    }
    else if (GWGameStat.mg_record[0xC] >= 0x63) {
        GWGameStat.mg_record[0xC] = 0x63;
    }
    #if VERSION_NTSC
    OSReport("HIScore 461(0-35999):%d\n", GWGameStat.mg_record[13]);
    #else
    OSReport("HIScore 461(0-29999):%d\n", GWGameStat.mg_record[13]);
    #endif
    if (GWGameStat.mg_record[0xD] == 0) {
        GWGameStat.mg_record[0xD] = 0;
    }
    else if (GWGameStat.mg_record[0xD] >= ((REFRESH_RATE*600)-1)) {
        GWGameStat.mg_record[0xD] = ((REFRESH_RATE*600)-1);
    }
    OSReport("HIScore 462(0-99):%d\n", GWGameStat.mg_record[0xE]);
    if (GWGameStat.mg_record[0xE] == 0) {
        GWGameStat.mg_record[0xE] = 0;
    }
    else if (GWGameStat.mg_record[0xE] >= 0x63) {
        GWGameStat.mg_record[0xE] = 0x63;
    }
    OSReport("########################################################\n\n");
}

void fn_1_125DC(float *arg0, s32 arg1)
{
    float spC[2];

    HuWinMesMaxSizeGet(1, spC, arg1);
    if (spC[0] > arg0[0]) {
        arg0[0] = spC[0];
    }
    if (spC[1] > arg0[1]) {
        arg0[1] = spC[1];
    }
}
