#include "game/board/main.h"
#include "REL/mentDll.h"
#include "ext_math.h"
#include "game/armem.h"
#include "game/chrman.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

typedef struct MentDllUnkBssE4Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
} MentDllUnkBssE4Struct; /* size = 0x1C */

typedef struct MentDllUnkBss16C4Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
    /* 0x1C */ float unk_1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
} MentDllUnkBss16C4Struct; /* size = 0x30 */

typedef void (*MentDllUnkFunc)(omObjData *, ...);

typedef struct MentDllUnkBss3114Struct {
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ MentDllUnkFunc unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char pad_10[0x48]; /* maybe part of unk_0C[0x13]? */
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ s32 unk_68;
    /* 0x6C */ s32 unk_6C;
    /* 0x70 */ s32 unk_70[4];
    /* 0x80 */ s32 unk_80[4];
} MentDllUnkBss3114Struct; /* size = 0x90 */

typedef struct MentDllUnkBss33ACStruct { // maybe the same as the other one?
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ MentDllUnkFunc unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char pad_10[0x20];
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ char pad_38[0x20];
} MentDllUnkBss33ACStruct; /* size = 0x58 */

typedef struct MentDllUnkBss35BCStruct {
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ MentDllUnkFunc unk_04;
    /* 0x08 */ s32 unk_08[5];
    /* 0x1C */ s32 unk_1C[5];
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44[5];
} MentDllUnkBss35BCStruct; /* size = 0x58 */

void fn_1_116F4(void);
void fn_1_1184C(omObjData *arg0, MentDllUnkBss35BCStruct *arg1);
void fn_1_11908(omObjData *arg0, s32 arg1);
void fn_1_121D8(void);
void fn_1_127FC(omObjData *arg0, MentDllUnkBss33ACStruct *arg1);
void fn_1_12E40(void);
void fn_1_134A8(void);
void fn_1_13970(void);
void fn_1_13D60(void);
void fn_1_13DEC(void);
void fn_1_13EDC(void);
void fn_1_13F68(void);
void fn_1_14058(void);
void fn_1_14148(void);
void fn_1_14238(void);
void fn_1_14328(void);
void fn_1_14418(void);
void fn_1_146D0(void);
void fn_1_147C0(void);
void fn_1_148B0(void);
void fn_1_149A0(void);
void fn_1_14A2C(void);
void fn_1_14AB8(void);
void fn_1_14BA8(void);
void fn_1_14CE0(void);
void fn_1_15098(void);
void fn_1_151B8(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_15950(void);
void fn_1_15CB4(omObjData *arg0, MentDllUnkBss3114Struct *arg1);
s32 fn_1_1648C(MentDllUnkBss3114Struct *arg0);
void fn_1_16B68(omObjData *arg0, MentDllUnkBss3114Struct *arg1);
void fn_1_173FC(MentDllUnkBss3114Struct *arg0);
void fn_1_17914(MentDllUnkBss3114Struct *arg0);
void fn_1_179DC(void);
void fn_1_17CC8(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_1811C(void);
void fn_1_1850C(void);
void fn_1_1872C(void);
void fn_1_18788(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_18A54(s32 arg0);
void fn_1_18DCC(void);
void fn_1_18F74(omObjData *arg0, MentDllUnkBss35BCStruct *arg1);
void fn_1_190E8(void);
void fn_1_19C98(omObjData *arg0, MentDllUnkBss35BCStruct *arg1);
void fn_1_1BB2C(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_1C554(void);
void fn_1_1C674(void);
void fn_1_1C754(void);
void fn_1_1C990(void);
void fn_1_1CF68(void);
void fn_1_1D4FC(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_1DED8(void);
void fn_1_1DF48(void);
void fn_1_1DFB8(void);
void fn_1_1E1B4(void);
void fn_1_1E404(omObjData *arg0, MentDllUnkBss3114Struct *arg1);
void fn_1_1E8A4(omObjData *arg0, MentDllUnkBss35BCStruct *arg1);
void fn_1_1F6B8(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_1F868(void);
void fn_1_1FA34(void);
void fn_1_1FC54(void);
void fn_1_1FF4C(omObjData *arg0, MentDllUnkBss35BCStruct *arg1);
void fn_1_2055C(s32 arg0);
void fn_1_207BC(void);
void fn_1_208F4(void);
void fn_1_20A24(void);
void fn_1_20B54(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_21724(omObjData *object);
void fn_1_2342C(omObjData *object);
void fn_1_C174(s32 arg0);
void fn_1_E654(s32 arg0);
void fn_1_E71C(s32 arg0);

Vec lbl_1_data_D8[6] = {
    { 0.0f, 0.0f, 460.0f },
    { -240.0f, 0.0f, 460.0f },
    { -120.0f, 0.0f, 460.0f },
    { 120.0f, 50.0f, 460.0f },
    { 240.0f, 0.0f, 460.0f },
    { 1200.0f, 0.0f, 460.0f },
};

float lbl_1_data_120[6] = { 0.0f, 20.0f, 10.0f, -10.0f, -20.0f, 0.0f };

MentDllUnkBss35BCStruct lbl_1_bss_366C;
MentDllUnkBss35BCStruct lbl_1_bss_35BC[2];
MentDllUnkBss33ACStruct lbl_1_bss_33AC[6];
MentDllUnkBss33ACStruct lbl_1_bss_3354;
MentDllUnkBss3114Struct lbl_1_bss_3114[4];
omObjData *lbl_1_bss_3108[3];
omObjData *lbl_1_bss_3104;
MentDllUnkBss16C4Struct lbl_1_bss_16C4[0x8C];
MentDllUnkBssE4Struct lbl_1_bss_E4[0xC8];
s32 lbl_1_bss_E0;
s32 lbl_1_bss_DC;
s32 lbl_1_bss_D8;
s32 lbl_1_bss_D4;
s32 lbl_1_bss_D0;
s32 lbl_1_bss_CC;
Process *lbl_1_bss_C8;
s32 lbl_1_bss_A8[8];
MentDllUnkBss64Struct lbl_1_bss_64;
s32 lbl_1_bss_24[16];
s32 lbl_1_bss_14[4];
s32 lbl_1_bss_8[3];

void fn_1_658C(Process *arg0)
{
    s32 var_r31;

    lbl_1_bss_C8 = arg0;
    fn_1_6D0();
    fn_1_50C();
    fn_1_5E8(lbl_1_bss_A8[0]);
    if (lbl_1_bss_A8[0] != 0xB) {
        CharKill(-1);
    }
    lbl_1_bss_A8[4] = GWGameStat.open_w06;
    lbl_1_bss_A8[5] = GWGameStat.veryHardUnlock;
    lbl_1_bss_A8[6] = GWGameStat.customPackEnable;
    switch (lbl_1_bss_A8[0]) {
        case 0:
            HuAudSndGrpSetSet(7);
            if (lbl_1_bss_A8[1] == 0) {
                fn_1_2844(lbl_1_bss_C8, fn_1_13D60);
            }
            else {
                fn_1_2844(lbl_1_bss_C8, fn_1_13EDC);
            }
            for (var_r31 = 0; var_r31 < 2; var_r31++) {
                HuPrcChildCreate(fn_1_121D8, 0x64, 0x3000, 0, HuPrcCurrentGet());
            }
            for (var_r31 = 0; var_r31 < 6; var_r31++) {
                HuPrcChildCreate(fn_1_12E40, 0x64, 0x3000, 0, HuPrcCurrentGet());
            }
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                HuPrcChildCreate(fn_1_13970, 0x64, 0x3000, 0, HuPrcCurrentGet());
            }
            if (lbl_1_bss_A8[1] == 0) {
                lbl_1_bss_3108[0] = omAddObjEx(lbl_1_bss_C8, 0x1000, 0x8D, 0x10, -1, fn_1_21724);
            }
            break;
        case 1:
            HuAudSndGrpSetSet(7);
            if (lbl_1_bss_A8[1] == 0) {
                fn_1_2844(lbl_1_bss_C8, fn_1_13D60);
            }
            else {
                fn_1_2844(lbl_1_bss_C8, fn_1_13EDC);
            }
            HuPrcChildCreate(fn_1_121D8, 0x64, 0x3000, 0, HuPrcCurrentGet());
            for (var_r31 = 0; var_r31 < 5; var_r31++) {
                HuPrcChildCreate(fn_1_12E40, 0x64, 0x3000, 0, HuPrcCurrentGet());
            }
            HuPrcChildCreate(fn_1_13970, 0x64, 0x3000, 0, HuPrcCurrentGet());
            if (lbl_1_bss_A8[1] == 0) {
                lbl_1_bss_3108[0] = omAddObjEx(lbl_1_bss_C8, 0x1000, 0x8D, 0x10, -1, fn_1_21724);
            }
            lbl_1_bss_3104 = omAddObjEx(lbl_1_bss_C8, 0x1000, 0xC9, 0x10, -1, fn_1_2342C);
            break;
        case 3:
            HuAudSndCommonGrpSet(0x56, 1);
            HuAudSndCommonGrpSet(0x6B, 0);
            fn_1_2844(lbl_1_bss_C8, fn_1_13D60);
            HuPrcChildCreate(fn_1_121D8, 0x64, 0x3000, 0, HuPrcCurrentGet());
            lbl_1_bss_D0 = 4;
            HuPrcChildCreate(fn_1_12E40, 0x64, 0x3000, 0, HuPrcCurrentGet());
            lbl_1_bss_3108[0] = omAddObjEx(lbl_1_bss_C8, 0x1000, 0x8D, 0x10, -1, fn_1_21724);
            break;
        case 4:
            HuAudSndGrpSetSet(3);
            fn_1_2844(lbl_1_bss_C8, fn_1_13D60);
            HuPrcChildCreate(fn_1_121D8, 0x64, 0x3000, 0, HuPrcCurrentGet());
            lbl_1_bss_D0 = 2;
            HuPrcChildCreate(fn_1_12E40, 0x64, 0x3000, 0, HuPrcCurrentGet());
            lbl_1_bss_3108[0] = omAddObjEx(lbl_1_bss_C8, 0x1000, 0x8D, 0x10, -1, fn_1_21724);
            break;
        case 5:
            fn_1_2844(lbl_1_bss_C8, fn_1_13D60);
            HuPrcChildCreate(fn_1_121D8, 0x64, 0x3000, 0, HuPrcCurrentGet());
            lbl_1_bss_D0 = 3;
            HuPrcChildCreate(fn_1_12E40, 0x64, 0x3000, 0, HuPrcCurrentGet());
            lbl_1_bss_3108[0] = omAddObjEx(lbl_1_bss_C8, 0x1000, 0x8D, 0x10, -1, fn_1_21724);
            break;
        case 10:
            HuAudSndGrpSetSet(7);
            fn_1_2844(lbl_1_bss_C8, fn_1_149A0);
            HuPrcChildCreate(fn_1_121D8, 0x64, 0x3000, 0, HuPrcCurrentGet());
            for (var_r31 = 0; var_r31 < 5; var_r31++) {
                HuPrcChildCreate(fn_1_12E40, 0x64, 0x3000, 0, HuPrcCurrentGet());
            }
            HuPrcChildCreate(fn_1_13970, 0x64, 0x3000, 0, HuPrcCurrentGet());
            break;
        case 11:
            lbl_1_bss_CC = 1;
            HuAudSndGrpSetSet(7);
            fn_1_2844(lbl_1_bss_C8, fn_1_14A2C);
            HuPrcChildCreate(fn_1_121D8, 0x64, 0x3000, 0, HuPrcCurrentGet());
            HuPrcChildCreate(fn_1_134A8, 0x64, 0x3000, 0, HuPrcCurrentGet());
            fn_1_4B0(2);
            HuDataDirClose(DATADIR_MENT);
            HuPrcChildCreate(fn_1_13970, 0x64, 0x3000, 0, HuPrcCurrentGet());
            break;
    }
    HuPrcChildCreate(fn_1_116F4, 0xC8, 0x3000, 0, HuPrcCurrentGet());
}

void fn_1_6C4C(void)
{
    s32 var_r31;
    s32 var_r30 = 0x10;
    s32 var_r29 = 0x28;
    s32 var_r28 = 0;
    {
        GXColor sp10 = { 0x00, 0x00, 0x80, 0x80 };
        while (1) {
            fn_1_4D8();
            if (HuPadBtnDown[0] & PAD_TRIGGER_R) {
                var_r28++;
                var_r28 = var_r28 % 2;
            }
            if (var_r28 == 0) {
                continue;
            }
            printWin(var_r30, var_r29, 0xDC, 0x122, &sp10);
            if (lbl_1_bss_366C.unk_04 == NULL) {
                print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> FALSE");
            }
            else {
                print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> TRUE");
            }
            for (var_r31 = 0; var_r31 < 2; var_r31++) {
                if (lbl_1_bss_35BC[var_r31].unk_04 == NULL) {
                    print8(var_r30, var_r29 + 0x14 + (var_r31 * 0xA), 1.0f, "PROC_MAP%d    -> FALSE", var_r31);
                }
                else {
                    print8(var_r30, var_r29 + 0x14 + (var_r31 * 0xA), 1.0f, "PROC_MAP%d    -> TRUE", var_r31);
                }
            }
            for (var_r31 = 0; var_r31 < 6; var_r31++) {
                if (lbl_1_bss_33AC[var_r31].unk_04 == NULL) {
                    print8(var_r30, var_r29 + 0x32 + (var_r31 * 0xA), 1.0f, "PROC_SUB%d    -> FALSE", var_r31);
                }
                else {
                    print8(var_r30, var_r29 + 0x32 + (var_r31 * 0xA), 1.0f, "PROC_SUB%d    -> TRUE", var_r31);
                }
            }
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (lbl_1_bss_3114[var_r31].unk_04 == NULL) {
                    print8(var_r30, var_r29 + 0x78 + (var_r31 * 0xA), 1.0f, "PROC_PLAYER%d -> FALSE", var_r31);
                }
                else {
                    print8(var_r30, var_r29 + 0x78 + (var_r31 * 0xA), 1.0f, "PROC_PLAYER%d -> TRUE", var_r31);
                }
            }
            print8(var_r30, var_r29 + 0xAA, 1.0f, "MODE:%d MAP:%d", lbl_1_bss_A8[0], lbl_1_bss_A8[2]);
            print8(var_r30, var_r29 + 0xBE, 1.0f, "NO) IDX:GRP:COM:DIF:PAD:CHR");
            for (var_r31 = 0; var_r31 < 4; var_r31++) {

                print8(var_r30, var_r29 + 0xC8 + (var_r31 * 0xA), 1.0f, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", var_r31, lbl_1_bss_3114[var_r31].unk_58,
                    lbl_1_bss_3114[var_r31].unk_5C, lbl_1_bss_3114[var_r31].unk_60, lbl_1_bss_3114[var_r31].unk_64, lbl_1_bss_3114[var_r31].unk_6C, lbl_1_bss_3114[var_r31].unk_68);
            }
            print8(var_r30, var_r29 + 0xF0, 1.0f, "NO) FG0:FG1:FG2:FG3");
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                print8(var_r30, var_r29 + 0xFA + (var_r31 * 0xA), 1.0f, "%2d) %3d:%3d:%3d:%3d", var_r31, lbl_1_bss_3114[var_r31].unk_70[0],
                    lbl_1_bss_3114[var_r31].unk_70[1], lbl_1_bss_3114[var_r31].unk_70[2], lbl_1_bss_3114[var_r31].unk_70[3]);
            }
        }
    }
}

s32 fn_1_7124(void)
{
    s32 var_r31 = 0;

    if (_CheckFlag(FLAG_ID_MAKE(0, 2)) != 0) {
        var_r31++;
    }
    if (_CheckFlag(FLAG_ID_MAKE(0, 3)) != 0) {
        var_r31++;
    }
    if (_CheckFlag(FLAG_ID_MAKE(0, 4)) != 0) {
        var_r31++;
    }
    if (_CheckFlag(FLAG_ID_MAKE(0, 5)) != 0) {
        var_r31++;
    }
    if (_CheckFlag(FLAG_ID_MAKE(0, 6)) != 0) {
        var_r31++;
    }
    if (_CheckFlag(FLAG_ID_MAKE(0, 7)) != 0) {
        var_r31++;
    }
    OSReport("DIF OMAKASE MAP %d\n", var_r31);
    var_r31 = var_r31 / 2;
    if (var_r31 < 0) {
        var_r31 = 0;
    }
    else if (var_r31 > 3) {
        var_r31 = 3;
    }
    OSReport("DIF OMAKASE DIF %d\n", var_r31);
    return var_r31;
}

s32 lbl_1_data_2B4[0xF] = {
    DATADIR_W01,
    DATADIR_W02,
    DATADIR_W03,
    DATADIR_W04,
    DATADIR_W05,
    DATADIR_W06,
    DATADIR_W10,
    DATADIR_MARIOMDL1,
    DATADIR_LUIGIMDL1,
    DATADIR_PEACHMDL1,
    DATADIR_YOSHIMDL1,
    DATADIR_WARIOMDL1,
    DATADIR_DONKEYMDL1,
    DATADIR_DAISYMDL1,
    DATADIR_WALUIGIMDL1,
};

void fn_1_7218(void)
{
    s32 var_r31 = HuDataDirReadAsync(DATADIR_BOARD);

    if (var_r31 != -1) {
        while (HuDataGetAsyncStat(var_r31) == 0) {
            HuPrcVSleep();
        }
    }
    HuAR_MRAMtoARAM(DATADIR_BOARD);
    while (HuARDMACheck() != 0) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATADIR_BOARD);
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        var_r31 = HuDataDirReadAsync(DATADIR_W10);
    }
    else {
        var_r31 = HuDataDirReadAsync(lbl_1_data_2B4[GWSystem.board]);
    }
    if (var_r31 != -1) {
        while (HuDataGetAsyncStat(var_r31) == 0) {
            HuPrcVSleep();
        }
    }
    lbl_1_bss_D8 = 1;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_7304(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        lbl_1_bss_3114[var_r31].unk_68 = -1;
        lbl_1_bss_3114[var_r31].unk_6C = var_r31;
        lbl_1_bss_3114[var_r31].unk_60 = 1;
    }
    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        do {
            lbl_1_bss_3114[var_r31].unk_68 = rand8() % 8;
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                if ((var_r31 != var_r29) && (lbl_1_bss_3114[var_r29].unk_68 != -1)
                    && (lbl_1_bss_3114[var_r31].unk_68 == lbl_1_bss_3114[var_r29].unk_68)) {
                    break;
                }
            }
        } while (var_r29 != 4);
    }
    GWSystem.diff_story = lbl_1_bss_35BC[0].unk_1C[0];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_3114[var_r31].unk_64 = GWSystem.diff_story;
        if (GWSystem.diff_story == 4) {
            lbl_1_bss_3114[var_r31].unk_64 = fn_1_7124();
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GWPlayerCfg[var_r31].character = lbl_1_bss_3114[var_r31].unk_68;
        GWPlayerCfg[var_r31].pad_idx = lbl_1_bss_3114[var_r31].unk_6C;
        GWPlayerCfg[var_r31].diff = lbl_1_bss_3114[var_r31].unk_64;
        GWPlayerCfg[var_r31].group = 0;
        GWPlayerCfg[var_r31].iscom = lbl_1_bss_3114[var_r31].unk_60;
    }
    BoardSaveInit(lbl_1_bss_A8[2]);
    CharKill(-1);
}

void fn_1_7684(void)
{
    s32 spC[7] = { 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F };
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_4D8();
    }
    CharModelKill(-1);
    MGSeqKillAll();
    {
        omOvlHisData *sp8 = omOvlHisGet(0);
    }
    omOvlHisChg(0, OVL_MSTORY3, 0, 0);
    do {
        fn_1_4D8();
    } while (lbl_1_bss_D8 != 1);
    HuAudSeqAllFadeOut(0x3E8);
    HuAudSStreamAllFadeOut(0x3E8);
    CharARAMOpen(GWPlayerCfg[0].character);
    CharARAMOpen(GWPlayerCfg[1].character);
    CharARAMOpen(GWPlayerCfg[2].character);
    CharARAMOpen(GWPlayerCfg[3].character);
    omOvlCallEx(spC[GWSystem.board], 1, 0, 0);
    while (1) {
        fn_1_4D8();
    }
}

void fn_1_77C0(void)
{
    s32 var_r31;

    fn_1_2808(fn_1_13DEC);
    fn_1_4B0(0xF0);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        Hu3DModelAttrReset(lbl_1_bss_33AC[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
    }
    lbl_1_bss_3108[0]->work[0] = 1;
    fn_1_2808(fn_1_13F68);
    fn_1_4B0(0x8C);
}

void fn_1_7858(void)
{
    s32 var_r31;

    fn_1_4B0(0x3C);
    lbl_1_bss_14[0] = HuAudSeqPlay(0x30);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        Hu3DModelAttrReset(lbl_1_bss_33AC[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
    }
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_4B0(0x3C);
}

void fn_1_7900(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = lbl_1_bss_DC;
    sp8.center.y = 60.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = 0.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 850.0f;
    fn_1_4138(var_r31, &sp8, var_r31->unk_40++, 10.0f, 5.0f);
}

s32 lbl_1_data_2F0 = -1;

void fn_1_7A14(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    _ClearFlag(2);
    _ClearFlag(3);
    _ClearFlag(4);
    _ClearFlag(5);
    _ClearFlag(6);
    _ClearFlag(7);
    _ClearFlag(1);
    _ClearFlag(9);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        fn_1_59A0(lbl_1_bss_33AC[var_r31].unk_00, 1, 6, 5, 1);
    }
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 3, 0, 0);
    lbl_1_bss_3104->work[0] = 1;
    var_r29 = -1;
    var_r29 = HuAudFXPlay(0x43);
    HuAudFXPanning(var_r29, 0x20);
    var_r29 = HuAudFXPlay(0x40);
    HuAudFXPanning(var_r29, 0x30);
    var_r29 = HuAudFXPlay(0x37);
    HuAudFXPanning(var_r29, 0x40);
    var_r29 = HuAudFXPlay(0x4B);
    HuAudFXPanning(var_r29, 0x4C);
    var_r29 = HuAudFXPlay(0x46);
    HuAudFXPanning(var_r29, 0x60);
    HuAudFXPlay(0x9A);
    HuAudFXPlay(0x306);
    fn_1_4B0(0x96);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    fn_1_4B0(0x1E);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_33AC[var_r31].unk_08 = 0;
        lbl_1_bss_33AC[var_r31].unk_04 = (MentDllUnkFunc)fn_1_127FC;
    }
    lbl_1_bss_33AC->unk_08 = 1;
    fn_1_4B0(0x3C);
    for (var_r31 = 1; var_r31 < 5; var_r31++) {
        fn_1_59A0(lbl_1_bss_33AC[var_r31].unk_00, 1, 1, 0x1E, 1);
    }
    var_r30 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
    HuWinInsertMesSet(var_r30, lbl_1_bss_3114->unk_68, 0);
    fn_1_1968(var_r30, 0x1E005F, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r30);
    fn_1_4B0(0x1E);
    for (var_r31 = 1; var_r31 < 5; var_r31++) {
        lbl_1_bss_33AC[var_r31].unk_08 = 0;
    }
    lbl_1_bss_33AC[3].unk_08 = 1;
    lbl_1_bss_64.unk_40 = 0;
    lbl_1_bss_DC = lbl_1_data_D8[3].x;
    fn_1_2808(fn_1_7900);
    fn_1_4B0(0x1E);
    var_r30 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 6, 0xF, 1);
    fn_1_1968(var_r30, 0x1E0060, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r30);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_33AC[var_r31].unk_08 = 0;
    }
    lbl_1_bss_33AC[1].unk_08 = 1;
    lbl_1_bss_64.unk_40 = 0;
    lbl_1_bss_DC = lbl_1_data_D8[1].x;
    fn_1_4B0(0x1E);
    var_r30 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[1].unk_00, 1, 6, 0xF, 1);
    fn_1_1968(var_r30, 0x1E0061, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[1].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r30);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_33AC[var_r31].unk_08 = 0;
    }
    lbl_1_bss_33AC[4].unk_08 = 1;
    lbl_1_bss_64.unk_40 = 0;
    lbl_1_bss_DC = lbl_1_data_D8[4].x;
    fn_1_4B0(0x1E);
    var_r30 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[4].unk_00, 1, 6, 0xF, 1);
    fn_1_1968(var_r30, 0x1E0062, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[4].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r30);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_33AC[var_r31].unk_08 = 0;
    }
    lbl_1_bss_33AC[2].unk_08 = 1;
    lbl_1_bss_64.unk_40 = 0;
    lbl_1_bss_DC = lbl_1_data_D8[2].x;
    fn_1_4B0(0x1E);
    var_r30 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[2].unk_00, 1, 1, 0xF, 1);
    fn_1_1968(var_r30, 0x1E0063, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[2].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r30);
    lbl_1_bss_3104->work[0] = 3;
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_33AC[var_r31].unk_08 = 0;
    }
    lbl_1_bss_33AC->unk_08 = 1;
    fn_1_2808(fn_1_13F68);
    fn_1_4B0(0x3C);
    var_r30 = fn_1_1434(0, 0, 0);
    lbl_1_data_2F0 = var_r30;
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r30, 0x1E0064, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_33AC[var_r31].unk_04 = NULL;
    }
}

void fn_1_81A8(omObjData *arg0, void *arg1, void *arg2)
{
    fn_1_1F868();
    lbl_1_bss_3114->unk_04 = NULL;
}

void fn_1_81D8(void)
{
    lbl_1_bss_3114[0].unk_04 = (MentDllUnkFunc)fn_1_81A8;
}

void fn_1_81F0(void)
{
    fn_1_4B0(0x3C);
    HuAudSStreamPlay(0xC);
    OSReport("########### ME_MainProcFunc000\n");
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
}

void fn_1_824C(void)
{
    s32 var_r31;

    fn_1_4B0(0x3C);
    lbl_1_bss_14[0] = HuAudSeqPlay(0x30);
    if (lbl_1_bss_A8[0] == 0) {
        for (var_r31 = 0; var_r31 < 6; var_r31++) {
            Hu3DModelAttrReset(lbl_1_bss_33AC[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
        }
    }
    else {
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            Hu3DModelAttrReset(lbl_1_bss_33AC[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
        }
    }
    Hu3DModelPosSet(lbl_1_bss_33AC[0].unk_00->model[1], 0.0f, 0.0f, 560.0f);
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 2, 0, 2);
    Hu3DModelAttrSet(lbl_1_bss_35BC[0].unk_00->model[2], HU3D_ATTR_DISPOFF);
    OSReport("########### ME_MainProcFunc400\n");
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_4B0(0x3C);
}

void fn_1_83CC(void)
{
    s32 var_r31;

    Vec sp14 = { 0.0f, 0.0f, 560.0f };
    fn_1_2808(fn_1_13DEC);
    fn_1_4B0(0x5A);
    if (lbl_1_bss_A8[0] == 0) {
        for (var_r31 = 0; var_r31 < 6; var_r31++) {
            Hu3DModelAttrReset(lbl_1_bss_33AC[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
        }
    }
    else {
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            Hu3DModelAttrReset(lbl_1_bss_33AC[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
        }
    }
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 3, 0, 0);
    fn_1_4B0(0x96);
    lbl_1_bss_3108[0]->work[0] = 1;
    fn_1_2808(fn_1_13F68);
    fn_1_4B0(0x5A);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 2, 0xF, 1);
    fn_1_5D38(lbl_1_bss_33AC[0].unk_00, 1, sp14, 0.0f, 3.0f, 0.0f, 1, 0);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    Hu3DModelAttrSet(lbl_1_bss_35BC[0].unk_00->model[2], HU3D_ATTR_DISPOFF);
    fn_1_4B0(0x1E);
}

void fn_1_85C8(void)
{
    s32 var_r31;
    s32 var_r30;

    lbl_1_bss_14[0] = HuAudSeqPlay(0x30);
    var_r31 = fn_1_1434(0, 0, 0);
    HuAudFXPlay(lbl_1_data_0[0][0]);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r31, 0x1A0000, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r31);
    saveExecF = 0;
    if (GWGameStat.party_continue == 1) {
        var_r31 = fn_1_1434(0, 0, 0);
        while (1) {
            fn_1_4D8();
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
            fn_1_1968(var_r31, 0x1A0001, -1, 5);
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
            var_r30 = fn_1_1A5C(0x1E0035, 3, 0);
            if (var_r30 == -1) {
                fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
                fn_1_1968(var_r31, 0x1A0003, -1, 5);
                fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
                var_r30 = fn_1_1DD8(0x1E0035, 3, 0);
                if (var_r30 == 0) {
                    fn_1_16AC(var_r31);
                    fn_1_C174(0);
                }
                continue;
            }
            if (var_r30 == 0) {
                HuAudFXPlay(lbl_1_data_0[0][3]);
                saveExecF = 1;
                SLLoadBoard();
                HuDataDirClose(DATADIR_MENT);
                HuPrcChildCreate(fn_1_7218, 0x64, 0x3000, 0, lbl_1_bss_C8);
                fn_1_16AC(var_r31);
                fn_1_C174(1);
                continue;
            }
            if (var_r30 == 1) {
                break;
            }
        }
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(var_r31, 0x1A0002, -1, -1);
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
        fn_1_16AC(var_r31);
    }
}

void fn_1_88A4(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = fn_1_1434(0, 0, 0);
    HuAudFXPlay(lbl_1_data_0[0][3]);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r30, 0x1A0004, -1, 5);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    var_r29 = fn_1_1DD8(0x1E0035, 3, 0);
    fn_1_16AC(var_r30);
    if (var_r29 == 0) {
        s32 spC[4] = { 3, 0, 2, 4 };
        _SetFlag(0x1000B);
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            GWPlayerCfg[var_r31].character = spC[var_r31];
            GWPlayerCfg[var_r31].pad_idx = var_r31;
            GWPlayerCfg[var_r31].diff = 0;
            GWPlayerCfg[var_r31].group = 0;
            GWPlayerCfg[var_r31].iscom = 1;
            OSReport("ID-%d CHR-%d PAD-%d DIF-%d GRP-%d COM-%d\n", var_r31, GWPlayerCfg[var_r31].character, GWPlayerCfg[var_r31].pad_idx,
                GWPlayerCfg[var_r31].diff, GWPlayerCfg[var_r31].group, GWPlayerCfg[var_r31].iscom);
        }
        BoardSaveInit(6);
        GWSystem.max_turn = 0x14;
        HuDataDirClose(DATADIR_MENT);
        HuPrcChildCreate(fn_1_7218, 0x64, 0x3000, 0, lbl_1_bss_C8);
        {
            omOvlHisData *sp8 = omOvlHisGet(0);
        }
        omOvlHisChg(0, OVL_MENT, 0, 1);
        fn_1_C174(2);
    }
    else {
        _ClearFlag(0x1000B);
    }
    fn_1_14BA8();
}

void fn_1_8B40(s32 arg0)
{
    fn_1_2055C(arg0);
}

s32 fn_1_8B68(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r26;
    s32 var_r27;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    var_r30 = 0;
    var_r23 = 0;
    var_r28 = 0;
    if (lbl_1_bss_A8[0] == 5) {
        var_r28 = 3;
    }
    var_r27 = fn_1_1434(0, 0, 0);
    HuAudFXPlay(lbl_1_data_0[var_r28][2]);
    while (1) {
        fn_1_4D8();
        fn_1_4D8();
        fn_1_5818(lbl_1_bss_33AC[var_r28].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(var_r27, 0x1A0005, -1, -1);
        fn_1_5818(lbl_1_bss_33AC[var_r28].unk_00, 1, 1, 0xF, 1);
        fn_1_2154(0x1A0021);
        fn_1_208F4();
        lbl_1_bss_35BC[0].unk_04 = (MentDllUnkFunc)fn_1_1FF4C;
        var_r25 = 0x63;
        var_r23 = 0;
        while (1) {
            fn_1_4D8();
            var_r30 = 0;
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (lbl_1_bss_3114[var_r31].unk_70[3] == 0) {
                    var_r30++;
                }
            }
            if (var_r25 != var_r30) {
                var_r25 = var_r30;
                fn_1_1968(var_r27, var_r30 + 0x1A001B, -1, -0x3E7);
            }
            if (lbl_1_bss_35BC[0].unk_1C[0] != 0) {
                continue;
            }
            if (HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_A) {
                var_r29 = 1;
                HuAudFXPlay(2);
                lbl_1_bss_35BC[0].unk_04 = NULL;
                fn_1_4B0(2);
                var_r26 = 0;
                var_r30 = var_r26;
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    if (lbl_1_bss_3114[var_r31].unk_60 == 0) {
                        var_r26++;
                    }
                }
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    if (var_r30 < var_r26) {
                        if (HuPadStatGet(var_r31) != -1) {
                            var_r30++;
                            lbl_1_bss_3114[var_r31].unk_60 = 0;
                        }
                        else {
                            lbl_1_bss_3114[var_r31].unk_60 = 1;
                        }
                    }
                }
                break;
            }
            else if (HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_B) {
                var_r29 = 0;
                HuAudFXPlay(3);
                break;
            }
        }
        fn_1_20A24();
        lbl_1_bss_35BC[0].unk_04 = NULL;
        fn_1_2318(0);
        if (var_r29 == 0) {
            fn_1_59A0(lbl_1_bss_33AC[var_r28].unk_00, 1, 4, 0xF, 1);
            fn_1_1968(var_r27, 0x1A0003, -1, 5);
            fn_1_59A0(lbl_1_bss_33AC[var_r28].unk_00, 1, 1, 0xF, 1);
            var_r24 = fn_1_1DD8(0x1E0035, 3, 0);
            if (var_r24 == 0) {
                fn_1_16AC(var_r27);
                fn_1_C174(0);
            }
        }
        else if (var_r29 == 1) {
            break;
        }
    }
    fn_1_16AC(var_r27);
    var_r30 = 0;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_3114[var_r31].unk_60 == 0) {
            var_r30++;
        }
    }
    if (var_r30 == 0) {
        var_r29 = 2;
    }
    else {
        var_r29 = 1;
    }
    return var_r29;
}

void fn_1_8F44(void)
{
    s32 var_r31;

    fn_1_207BC();
    fn_1_15950();
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_3114[var_r31].unk_68 = var_r31;
    }
}

void fn_1_8F98(void)
{
    fn_1_14CE0();
}

s32 fn_1_8FB8(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r26 = 0;
    var_r29 = 0;
    if (lbl_1_bss_A8[0] == 5) {
        var_r29 = 3;
    }
    fn_1_15950();
    var_r27 = fn_1_1434(0, 0, 0);
    HuWinPushKeySet(var_r27, 0x300);
    HuAudFXPlay(lbl_1_data_0[var_r29][2]);
    fn_1_4D8();
    fn_1_5818(lbl_1_bss_33AC[var_r29].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r27, 0x1A0009, -1, -1);
    fn_1_5818(lbl_1_bss_33AC[var_r29].unk_00, 1, 1, 0xF, 1);
    fn_1_2154(0x1A0020);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_3114[var_r31].unk_60 == 0) {
            lbl_1_bss_3114[var_r31].unk_04 = (MentDllUnkFunc)fn_1_15CB4;
        }
    }
    while (1) {
        fn_1_4D8();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if ((lbl_1_bss_3114[var_r31].unk_60 == 0) && (HuPadBtnDown[lbl_1_bss_3114[var_r31].unk_6C] & PAD_BUTTON_A)) {
                var_r26 = 1;
            }
        }
        if ((lbl_1_bss_3114[0].unk_70[0] == 0) && (HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_B)) {
            HuAudFXPlay(3);
            var_r30 = 0;
            break;
        }
        else {
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if ((lbl_1_bss_3114[var_r31].unk_60 == 0) && (lbl_1_bss_3114[var_r31].unk_70[0] != 1)) {
                    break;
                }
            }
            if (var_r31 == 4) {
                var_r30 = 2;
                break;
            }
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_3114[var_r31].unk_04 = NULL;
    }
    fn_1_2318(0);
    fn_1_16AC(var_r27);
    if (var_r30 == 2) {
        var_r28 = 0;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_3114[var_r31].unk_60 != 0) {
                lbl_1_bss_3114[var_r31].unk_68 = 0;
                var_r28++;
            }
        }
        if (var_r28 == 0) {
            var_r30 = 3;
        }
        else {
            var_r30 = 2;
        }
    }
    else {
        var_r30 = 0;
    }
    return var_r30;
}

s32 fn_1_92CC(void)
{
    s32 sp8;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    var_r30 = -1;
    var_r26 = -1;
    var_r24 = -1;
    sp8 = 0;
    var_r25 = 0;
    if (lbl_1_bss_A8[0] == 5) {
        var_r25 = 3;
    }
    var_r27 = fn_1_1434(0, 0, 0);
    HuAudFXPlay(lbl_1_data_0[var_r25][3]);
    var_r28 = 0;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_3114[var_r31].unk_60 != 0) {
            var_r28++;
        }
    }
    HuWinInsertMesSet(var_r27, var_r28 + 0x1A0023, 1);
    fn_1_59A0(lbl_1_bss_33AC[var_r25].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r27, 0x1A0007, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[var_r25].unk_00, 1, 1, 0xF, 1);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_3114[var_r31].unk_60 != 0) {
            lbl_1_bss_3114[var_r31].unk_68 = lbl_1_bss_3114[var_r31].unk_64 = 0;
        }
    }
    while (1) {
        fn_1_4D8();
        fn_1_2154(0x1A0020);
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if ((lbl_1_bss_3114[var_r31].unk_60 != 0) && (lbl_1_bss_3114[var_r31].unk_70[0] == 0)) {
                var_r30 = var_r31;
                lbl_1_bss_3114[var_r31].unk_70[1] = var_r26;
                fn_1_173FC(&lbl_1_bss_3114[var_r31]);
                lbl_1_bss_3114[var_r31].unk_04 = (MentDllUnkFunc)fn_1_16B68;
                break;
            }
        }
        while (1) {
            fn_1_4D8();
            if ((var_r24 != lbl_1_bss_3114[var_r30].unk_68) && (lbl_1_bss_3114[var_r30].unk_70[0] == 0)) {
                var_r24 = lbl_1_bss_3114[var_r30].unk_68;
                fn_1_1968(var_r27, lbl_1_bss_3114[var_r30].unk_68 + 0x1B0008, -1, -0x3E7);
            }
            if ((HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_B) && (lbl_1_bss_3114[var_r30].unk_70[0] == 0)) {
                HuAudFXPlay(3);
                if (var_r26 == -1) {
                    var_r29 = 0;
                }
                else {
                    var_r29 = 1;
                }
                break;
            }
            else if (lbl_1_bss_3114[var_r30].unk_70[0] == 1) {
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    if (lbl_1_bss_3114[var_r31].unk_70[0] == 0) {
                        lbl_1_bss_3114[var_r31].unk_68 = 0;
                    }
                }
                lbl_1_bss_3114[var_r30].unk_04 = NULL;
                fn_1_1968(var_r27, 0x1A0022, -1, -0x3E7);
                fn_1_2154(0x1A0023);
                var_r29 = fn_1_1648C(&lbl_1_bss_3114[var_r30]);
                if (var_r29 == 1) {
                    lbl_1_bss_3114[var_r30].unk_70[2] = 1;
                    var_r29 = 4;
                    var_r26 = var_r30;
                }
                else {
                    lbl_1_bss_3114[var_r30].unk_70[2] = 0;
                    var_r29 = 4;
                    lbl_1_bss_3114[var_r30].unk_70[0] = 0;
                    fn_1_17914(&lbl_1_bss_3114[var_r30]);
                    fn_1_173FC(&lbl_1_bss_3114[var_r30]);
                }
                break;
            }
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            lbl_1_bss_3114[var_r31].unk_04 = NULL;
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_3114[var_r31].unk_70[0] == 0) {
                break;
            }
        }
        if (var_r31 == 4) {
            var_r29 = 3;
            break;
        }
        else {
            if (var_r29 == 1) {
                fn_1_173FC(&lbl_1_bss_3114[var_r30]);
                fn_1_17914(&lbl_1_bss_3114[var_r30]);
                fn_1_173FC(&lbl_1_bss_3114[lbl_1_bss_3114[var_r30].unk_70[1]]);
                var_r26 = lbl_1_bss_3114[lbl_1_bss_3114[var_r30].unk_70[1]].unk_70[1];
                lbl_1_bss_3114[lbl_1_bss_3114[var_r30].unk_70[1]].unk_70[0] = 0;
            }
            else if (var_r29 == 4) {
            }
            else if (var_r29 == 0) {
                fn_1_17914(&lbl_1_bss_3114[var_r30]);
                break;
            }
            else {
                break;
            }
        }
        var_r24 = -1;
    }
    fn_1_2318(0);
    fn_1_16AC(var_r27);
    if (var_r29 == 0) {
        var_r28 = 0;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_3114[var_r31].unk_60 == 0) {
                var_r28++;
            }
        }
        if (var_r28 != 0) {
            var_r29 = 1;
        }
        else {
            var_r29 = 0;
        }
    }
    return var_r29;
}

void fn_1_98E4(void)
{
    s32 var_r31;
    s32 var_r30;

    fn_1_15098();
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            if (lbl_1_bss_3114[var_r31].unk_60 == 1) {
                lbl_1_bss_3114[var_r31].unk_70[var_r30] = 0;
                lbl_1_bss_3114[var_r31].unk_80[var_r30] = 0;
                fn_1_17914(&lbl_1_bss_3114[var_r31]);
            }
        }
    }
}

void fn_1_99AC(void)
{
    fn_1_1811C();
}

s32 fn_1_99CC(void)
{
    s32 var_r26;
    s32 temp_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    s32 i;

    s32 sp8[6] = {
        0x00000001,
        0x00000002,
        0x00000000,
        0x00000003,
        0x00000004,
        0x00000005,
    };

    var_r30 = 2;
    temp_r27 = fn_1_1434(0, 0, 0);
    while (1) {
        fn_1_4D8();
        var_r28 = 0;
        lbl_1_bss_33AC->unk_34 = 1;
        HuAudFXPlay(lbl_1_data_0[0][3]);
        fn_1_59A0(lbl_1_bss_33AC[sp8[var_r30]].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(temp_r27, 0x1A0008U, -1, -1);
        fn_1_59A0(lbl_1_bss_33AC[sp8[var_r30]].unk_00, 1, 1, 0xF, 1);
        fn_1_2154(0x1A0020U);

        for (i = 0; i < 6; i++) {
            lbl_1_bss_33AC[i].unk_08 = 0;
            lbl_1_bss_33AC[i].unk_04 = (void (*)(omObjData *, ...))fn_1_127FC;
        }

        lbl_1_bss_33AC[sp8[var_r30]].unk_08 = 1;
        lbl_1_bss_35BC->unk_04 = (void (*)(omObjData *, ...))fn_1_18F74;
        while (1) {
            fn_1_4D8();
            for (i = 0; i < 6; i++) {
                if (lbl_1_bss_33AC[i].unk_08 != 2) {
                    break;
                }
            }

            if (i == 6 && var_r28 >= 0x15) {
                if ((HuPadBtnDown[lbl_1_bss_3114->unk_6C] & 0x200)) {
                    HuAudFXPlay(3);
                    var_r29 = 0;
                    break;
                }
                else if ((HuPadBtnDown[lbl_1_bss_3114->unk_6C] & 0x100)) {
                    HuAudFXPlay(2);
                    var_r29 = 2;
                    break;
                }
                else {
                    if ((HuPadStkX[lbl_1_bss_3114->unk_6C] >= 50) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 2))) {
                        if (lbl_1_bss_A8[4] == 1) {
                            if (++var_r30 > 5) {
                                var_r30 = 5;
                            }
                            else {
                                var_r28 = 0;
                            }
                        }
                        else {
                            if (++var_r30 > 4) {
                                var_r30 = 4;
                            }
                            else {
                                var_r28 = 0;
                            }
                        }
                    }
                    else if ((HuPadStkX[lbl_1_bss_3114->unk_6C] <= -50) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 1))) {
                        if (--var_r30 < 0) {
                            var_r30 = 0;
                        }
                        else {
                            var_r28 = 0;
                        }
                    }
                }
            }
            if (var_r28 == 0) {
                if (var_r30 != 5) {
                    fn_1_2808(fn_1_14058);
                }
                else {
                    fn_1_2808(fn_1_14148);
                }
                for (i = 0; i < 6; i++) {
                    lbl_1_bss_33AC[i].unk_08 = 0;
                }
                lbl_1_bss_33AC[sp8[var_r30]].unk_08 = 1;
            }
            if (var_r28++ == 0x14) {
                var_r28 = 0x15;
                fn_1_18A54(sp8[var_r30]);
                fn_1_1968(temp_r27, sp8[var_r30] + 0x1B0001, -1, -999);
                if ((s32)sp8[var_r30] != 0) {
                    HuAudFXPlay(lbl_1_data_0[sp8[var_r30]][0]);
                }
                else {
                    HuAudFXPlay(lbl_1_data_0[sp8[var_r30]][2]);
                }
            }
        }
        fn_1_2318(0);
        if (var_r29 == 0) {
            fn_1_2808(fn_1_14058);
            if (var_r30 != 2) {
                var_r30 = 2;
                for (i = 0; i < 6; i++) {
                    lbl_1_bss_33AC[i].unk_08 = 0;
                }

                lbl_1_bss_33AC[sp8[var_r30]].unk_08 = 1;
            }
            fn_1_18DCC();
            fn_1_4B0(0x1E);
        }
        else if (var_r29 == 1) {
            fn_1_2808(fn_1_14058);
            if (var_r30 != 2) {
                var_r30 = 2;
                for (i = 0; i < 6; i++) {
                    lbl_1_bss_33AC[i].unk_08 = 0;
                }
                lbl_1_bss_33AC[sp8[var_r30]].unk_08 = 1;
            }
            fn_1_18DCC();
            fn_1_4B0(0x1E);
            fn_1_59A0(lbl_1_bss_33AC->unk_00, 1, 4, 0xF, 1);
            fn_1_1968(temp_r27, 0x1A0003U, -1, 5);
            fn_1_59A0(lbl_1_bss_33AC->unk_00, 1, 1, 0xF, 1);
            var_r26 = fn_1_1DD8(0x1E0035U, 3, 0);
            if (var_r26 == 0) {
                fn_1_16AC(temp_r27);
                fn_1_C174(0);
            }
            continue;
        }
        else if (var_r29 == 2) {
            for (i = 0; i < 6; i++) {
                lbl_1_bss_33AC[i].unk_04 = NULL;
            }
            lbl_1_bss_A8[2] = sp8[var_r30];
        }
        else {
            continue;
        }
        break;
    }

    fn_1_16AC(temp_r27);

    if (var_r29 == 0) {
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_3114[i].unk_60 != 0) {
                break;
            }
        }
        if (i != 4) {
            var_r29 = 2;
        }
        else {
            var_r29 = 1;
        }
    }
    else {
        var_r29 = 3;
    }
    return var_r29;
}

void fn_1_A0A4(void)
{
    fn_1_1850C();
}

void fn_1_A0C4(void)
{
    s32 var_r31;

    var_r31 = lbl_1_bss_A8[2];
    fn_1_1850C();
    HuAudFXPlay(lbl_1_data_0[var_r31][3]);
    if (var_r31 != 5) {
        Vec sp2C = { -350.0f, 0.0f, 800.0f };
        fn_1_2808(fn_1_14238);
        fn_1_5818(lbl_1_bss_33AC[var_r31].unk_00, 1, 3, 0xF, 1);
        fn_1_5D38(lbl_1_bss_33AC[var_r31].unk_00, 1, sp2C, 30.0f, 6.0f, 10.0f, 1, 1);
        fn_1_5818(lbl_1_bss_33AC[var_r31].unk_00, 1, 1, 0xF, 1);
        Hu3DModelAttrReset(lbl_1_bss_35BC[0].unk_00->model[2], HU3D_ATTR_DISPOFF);
        fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 2, 0, 0);
        fn_1_5CDC(lbl_1_bss_35BC[0].unk_00, 2, 0);
    }
    else {
        Vec sp20 = { 850.0f, 0.0f, 800.0f };
        fn_1_2808(fn_1_14328);
        fn_1_5818(lbl_1_bss_33AC[var_r31].unk_00, 1, 3, 0xF, 1);
        fn_1_5D38(lbl_1_bss_33AC[var_r31].unk_00, 1, sp20, 30.0f, 6.0f, 10.0f, 1, 1);
        fn_1_5818(lbl_1_bss_33AC[var_r31].unk_00, 1, 1, 0xF, 1);
        Hu3DModelAttrReset(lbl_1_bss_35BC[1].unk_00->model[2], HU3D_ATTR_DISPOFF);
        fn_1_5818(lbl_1_bss_35BC[1].unk_00, 2, 2, 0, 0);
        fn_1_5CDC(lbl_1_bss_35BC[1].unk_00, 2, 0);
    }
}

void fn_1_A39C(void)
{
    fn_1_1C754();
}

s32 fn_1_A3BC(void)
{
    char sp8[10];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r27 = -1;
    var_r26 = -1;
    var_r30 = lbl_1_bss_A8[2];
    var_r31 = fn_1_1434(0, 0, 0);
    if (var_r30 == 0) {
        HuAudFXPlay(lbl_1_data_0[var_r30][2]);
    }
    else {
        HuAudFXPlay(lbl_1_data_0[var_r30][0]);
    }
loop_3:
    fn_1_4D8();
    var_r27 = var_r26 = -1;
    fn_1_59A0(lbl_1_bss_33AC[var_r30].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r31, var_r30 + 0x1A000A, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[var_r30].unk_00, 1, 1, 0xF, 1);
    fn_1_2154(0x1A0021);
    lbl_1_bss_35BC[0].unk_08[1] = 0;
    fn_1_1C554();
    lbl_1_bss_35BC[1].unk_04 = (MentDllUnkFunc)fn_1_19C98;
loop_4:
    fn_1_4D8();
    if ((var_r27 != lbl_1_bss_35BC[1].unk_08[0]) || var_r26 != lbl_1_bss_35BC[1].unk_1C[lbl_1_bss_35BC[1].unk_08[0]]) {
        var_r27 = lbl_1_bss_35BC[1].unk_08[0];
        var_r26 = lbl_1_bss_35BC[1].unk_1C[lbl_1_bss_35BC[1].unk_08[0]];
        switch (lbl_1_bss_35BC[1].unk_08[0]) {
            case 0:
                switch (lbl_1_bss_35BC[1].unk_1C[0]) {
                    case 0:
                        fn_1_1968(var_r31, 0x1B0015, -1, -0x3E7);
                        break;
                    case 1:
                        HuWinInsertMesSet(var_r31, 0x1B001E, 0);
                        HuWinInsertMesSet(var_r31, 0x1B001F, 1);
                        HuWinInsertMesSet(var_r31, 0x1B0020, 2);
                        fn_1_1968(var_r31, 0x1B0016, -1, -0x3E7);
                        break;
                    case 2:
                        HuWinInsertMesSet(var_r31, 0x1B001F, 0);
                        HuWinInsertMesSet(var_r31, 0x1B001E, 1);
                        HuWinInsertMesSet(var_r31, 0x1B0020, 2);
                        fn_1_1968(var_r31, 0x1B0016, -1, -0x3E7);
                        break;
                    case 3:
                        HuWinInsertMesSet(var_r31, 0x1B0020, 0);
                        HuWinInsertMesSet(var_r31, 0x1B001E, 1);
                        HuWinInsertMesSet(var_r31, 0x1B001F, 2);
                        fn_1_1968(var_r31, 0x1B0016, -1, -0x3E7);
                        break;
                }
                break;
            case 1:
                sprintf(sp8, "%d", lbl_1_bss_35BC[1].unk_1C[1]);
                HuWinInsertMesSet(var_r31, MAKE_MESSID_PTR(sp8), 0);
                fn_1_1968(var_r31, 0x1B0017, -1, -0x3E7);
                break;
            case 2:
                fn_1_1968(var_r31, lbl_1_bss_35BC[1].unk_1C[2] + 0x1B0018, -1, -0x3E7);
                break;
            case 3:
                fn_1_1968(var_r31, lbl_1_bss_35BC[1].unk_1C[3] + 0x1B001B, -1, -0x3E7);
                break;
            case 4:
                HuWinInsertMesSet(var_r31, lbl_1_bss_3114[lbl_1_bss_35BC[1].unk_1C[4]].unk_68, 0);
                fn_1_1968(var_r31, 0x1B001D, -1, -0x3E7);
                break;
        }
    }
    if (lbl_1_bss_35BC[0].unk_08[3] != 0) {
        goto loop_4;
    }
    if (lbl_1_bss_35BC[0].unk_08[1] == -1) {
        fn_1_1C674();
        var_r29 = 0;
    }
    else if (lbl_1_bss_35BC[0].unk_08[1] == 1) {
        fn_1_1C674();
        var_r29 = 2;
    }
    else {
        goto loop_4;
    }
    fn_1_2318(0);
    lbl_1_bss_35BC[1].unk_04 = NULL;
    fn_1_1C674();
    if (var_r29 == 0) {
        var_r29 = 1;
    }
    else if (var_r29 == 1) {
        fn_1_59A0(lbl_1_bss_33AC[var_r30].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(var_r31, 0x1A0003, -1, 5);
        fn_1_59A0(lbl_1_bss_33AC[var_r30].unk_00, 1, 1, 0xF, 1);
        var_r28 = fn_1_1DD8(0x1E0035, 3, 0);
        if (var_r28 == 0) {
            fn_1_16AC(var_r31);
            fn_1_C174(0);
        }
        goto loop_3;
    }
    else if (var_r29 == 2) {
        HuAudFXPlay(lbl_1_data_0[var_r30][2]);
        fn_1_1968(var_r31, 0x1B0000, -1, 5);
        var_r28 = fn_1_1A5C(0x1E0035, 3, 0);
        if (var_r28 == 0) {
            var_r29 = 0x63;
        }
        else {
            fn_1_1968(var_r31, 0x1B0007, -1, 5);
            var_r28 = fn_1_1DD8(0x1E0035, 3, 0);
            if (var_r28 == 0) {
                var_r29 = 0;
            }
            else {
                goto loop_3;
            }
        }
    }
    else {
        goto loop_3;
    }
    fn_1_16AC(var_r31);
    return var_r29;
}

void fn_1_A990(void)
{
    fn_1_1C990();
}

void fn_1_A9B0(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r30 = lbl_1_bss_A8[2];
    {
        Vec sp14 = { -120.0f, 0.0f, 670.0f };
        if (lbl_1_bss_A8[2] == 5) {
            var_r31 = 1;
        }
        else {
            var_r31 = 0;
        }
        for (var_r29 = 0; var_r29 < 6; var_r29++) {
            Hu3DModelAttrSet(lbl_1_bss_33AC[var_r29].unk_00->model[1], HU3D_ATTR_DISPOFF);
        }
        Hu3DModelAttrReset(lbl_1_bss_33AC[var_r30].unk_00->model[1], HU3D_ATTR_DISPOFF);
        fn_1_11908(lbl_1_bss_35BC[var_r31].unk_00, lbl_1_bss_A8[2]);
        Hu3DModelAttrReset(lbl_1_bss_35BC[var_r31].unk_00->model[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_35BC[var_r31].unk_00->model[5], HU3D_ATTR_DISPOFF);
        lbl_1_bss_35BC[var_r31].unk_04 = (MentDllUnkFunc)fn_1_1184C;
        if (var_r30 == 5) {
            sp14.x += 1200.0f;
        }
        fn_1_5818(lbl_1_bss_33AC[var_r30].unk_00, 1, 3, 0xF, 1);
        fn_1_5D38(lbl_1_bss_33AC[var_r30].unk_00, 1, sp14, 5.0f, 6.0f, 10.0f, 1, 1);
        fn_1_5818(lbl_1_bss_33AC[var_r30].unk_00, 1, 1, 0xF, 1);
        HuDataDirClose(DATADIR_MENT);
        HuPrcChildCreate(fn_1_7218, 0x64, 0x3000, 0, lbl_1_bss_C8);
        fn_1_4B0(0x1E);
        fn_1_5818(lbl_1_bss_35BC[var_r31].unk_00, 2, 3, 0, 0);
        var_r28 = fn_1_1434(0, 0, 0);
        HuAudFXPlay(lbl_1_data_0[var_r30][0]);
        fn_1_59A0(lbl_1_bss_33AC[var_r30].unk_00, 1, 5, 0xF, 1);
        fn_1_1968(var_r28, var_r30 + 0x1A0010, -1, -1);
        fn_1_16AC(var_r28);
        HuAudSeqFadeOut(lbl_1_bss_14[0], 0xBB8);
        fn_1_5CDC(lbl_1_bss_35BC[var_r31].unk_00, 2, 0);
        Hu3DModelAttrSet(lbl_1_bss_35BC[var_r31].unk_00->model[2], HU3D_ATTR_DISPOFF);
        fn_1_2808(fn_1_14418);
        fn_1_4B0(0xA);
        HuAudFXPlay(GWPlayerCfg->character + 0x75);
        HuAudFXPlay(GWPlayerCfg[1].character + 0x75);
        HuAudFXPlay(GWPlayerCfg[2].character + 0x75);
        HuAudFXPlay(GWPlayerCfg[3].character + 0x75);
        fn_1_4B0(0x8C);
    }
}

void fn_1_AD78(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    s32 sp20[6] = { 1, 2, 0, 3, 4, 5 };
    var_r30 = lbl_1_bss_A8[2];
    var_r29 = lbl_1_bss_A8[2];
    if (var_r30 != 5) {
        var_r28 = 0;
    }
    else {
        var_r28 = 1;
    }
    fn_1_5818(lbl_1_bss_35BC[var_r28].unk_00, 2, 3, 0, 0);
    fn_1_5CDC(lbl_1_bss_35BC[var_r28].unk_00, 2, 0);
    Hu3DModelAttrSet(lbl_1_bss_35BC[0].unk_00->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_35BC[1].unk_00->model[2], HU3D_ATTR_DISPOFF);
    if (var_r30 != 5) {
        fn_1_2808(fn_1_146D0);
    }
    else {
        fn_1_2808(fn_1_147C0);
    }
    {
        Vec sp14 = { 0.0f, 0.0f, 560.0f };
        sp14.x = lbl_1_data_D8[var_r30].x;
        fn_1_5818(lbl_1_bss_33AC[var_r30].unk_00, 1, 3, 0xF, 1);
        fn_1_5D38(lbl_1_bss_33AC[var_r30].unk_00, 1, sp14, lbl_1_data_120[var_r30], 6.0f, 10.0f, 1, 1);
        fn_1_5818(lbl_1_bss_33AC[var_r30].unk_00, 1, 1, 0xF, 1);
        for (var_r31 = 0; var_r31 < 6; var_r31++) {
            lbl_1_bss_33AC[var_r31].unk_08 = 0;
            lbl_1_bss_33AC[var_r31].unk_04 = (MentDllUnkFunc)fn_1_127FC;
        }
        lbl_1_bss_33AC[sp20[var_r29]].unk_08 = 1;
        fn_1_2808(fn_1_14058);
        if (var_r29 != 2) {
            var_r29 = 2;
            for (var_r31 = 0; var_r31 < 6; var_r31++) {
                lbl_1_bss_33AC[var_r31].unk_08 = 0;
            }
            lbl_1_bss_33AC[sp20[var_r29]].unk_08 = 1;
        }
        fn_1_18DCC();
        fn_1_4B0(0x1E);
    }
}

void fn_1_B084(void)
{
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    float sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r31;
    MentDllUnkBss3114Struct *var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    MentDllUnkBss3114Struct *var_r26;
    MentDllUnkBss33ACStruct *var_r25;
    MentDllUnkBss35BCStruct *var_r24;

    var_r28 = lbl_1_bss_A8[2];
    if (var_r28 != 5) {
        var_r27 = 0;
    }
    else {
        var_r27 = 1;
    }
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (var_r31 != var_r28) {
            Hu3DModelAttrSet(lbl_1_bss_33AC[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
        }
    }
    fn_1_5818(lbl_1_bss_35BC[var_r27].unk_00, 2, 3, 0, 0);
    fn_1_5CDC(lbl_1_bss_35BC[var_r27].unk_00, 2, 0);
    if (var_r28 != 5) {
        fn_1_2808(fn_1_146D0);
    }
    else {
        fn_1_2808(fn_1_147C0);
    }
    {
        Vec sp2C = { 0.0f, 0.0f, 460.0f };

        if (var_r28 == 5) {
            sp2C.x = 1200.0f;
        }
        fn_1_5818(lbl_1_bss_33AC[var_r28].unk_00, 1, 3, 0xF, 1);
        fn_1_5D38(lbl_1_bss_33AC[var_r28].unk_00, 1, sp2C, 0.0f, 6.0f, 10.0f, 1, 1);
        fn_1_5818(lbl_1_bss_33AC[var_r28].unk_00, 1, 1, 0xF, 1);
        fn_1_5818(lbl_1_bss_35BC[var_r27].unk_00, 2, 2, 0, 0);
        fn_1_5CDC(lbl_1_bss_35BC[var_r27].unk_00, 2, 0);
        fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 3, 0, 2);
        Hu3DModelAttrReset(lbl_1_bss_35BC[0].unk_00->model[2], HU3D_ATTR_DISPOFF);
        if (var_r28 == 5) {
            fn_1_2808(fn_1_14058);
        }
        fn_1_4B0(0x1E);
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            var_r30 = &lbl_1_bss_3114[var_r31];
            var_r26 = &lbl_1_bss_3114[var_r31];
            var_r30->unk_58 = var_r31;
            var_r30->unk_5C = 0;
            var_r30->unk_60 = var_r30->unk_58;
            if (var_r30->unk_60 > 0) {
                var_r30->unk_60 = 1;
            }
            var_r30->unk_64 = 0;
            var_r30->unk_68 = var_r30->unk_58;
            var_r30->unk_6C = var_r30->unk_58;
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                var_r30->unk_70[0] = var_r30->unk_70[1] = 0;
            }
            for (var_r29 = 0; var_r29 < 5; var_r29++) {
                var_r26->unk_08 = var_r26->unk_0C = 0;
            }
        }
        for (var_r31 = 0; var_r31 < 6; var_r31++) {
            var_r25 = &lbl_1_bss_33AC[var_r31];
            for (var_r29 = 0; var_r29 < 5; var_r29++) {
                var_r25->unk_08 = var_r25->unk_0C = 0;
            }
            Hu3DModelPosSet(lbl_1_bss_33AC[var_r31].unk_00->model[1], lbl_1_data_D8[var_r31].x, lbl_1_data_D8[var_r31].y, lbl_1_data_D8[var_r31].z);
            Hu3DModelRotSet(lbl_1_bss_33AC[var_r31].unk_00->model[1], 0.0f, lbl_1_data_120[var_r31], 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_33AC[var_r31].unk_00->model[1], HU3D_ATTR_DISPOFF);
        }
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            var_r24 = &lbl_1_bss_35BC[var_r31];
            for (var_r29 = 0; var_r29 < 5; var_r29++) {
                var_r24->unk_08[0] = var_r24->unk_08[1] = 0;
            }
            Hu3DModelAttrSet(lbl_1_bss_35BC[1].unk_00->model[2], HU3D_ATTR_DISPOFF);
        }
        fn_1_14BA8();
        fn_1_179DC();
        fn_1_1872C();
        fn_1_190E8();
        fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 3, 0, 0);
        fn_1_5CDC(lbl_1_bss_35BC[0].unk_00, 2, 0);
        Hu3DModelAttrSet(lbl_1_bss_35BC[0].unk_00->model[2], HU3D_ATTR_DISPOFF);
        {
            Vec sp20 = { 0.0f, 0.0f, 560.0f };
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 2, 0xF, 1);
            fn_1_5D38(lbl_1_bss_33AC[0].unk_00, 1, sp20, 0.0f, 3.0f, 0.0f, 1, 0);
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
        }
    }
}

void fn_1_B654(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;

    var_r30 = 0xA;
    var_r29 = 0;
    if (lbl_1_bss_A8[1] == 0) {
        fn_1_81F0();
        fn_1_83CC();
        fn_1_85C8();
        fn_1_88A4();
    }
    else {
        fn_1_824C();
        fn_1_88A4();
    }
    do {
        fn_1_4D8();
        switch (var_r30) {
            case 10:
                var_r30 = 0;
                fn_1_2055C(var_r29);
                var_r29 = fn_1_8B68();
                fn_1_8F44();
                break;
            case 0:
                var_r30 = 1;
                fn_1_14CE0();
                while (1) {
                    fn_1_4D8();
                    switch (var_r29) {
                        case 1:
                            var_r29 = fn_1_8FB8();
                            break;
                        case 2:
                            var_r29 = fn_1_92CC();
                            break;
                    }
                    if (var_r29 == 0) {
                        var_r30 = 0xA;
                        break;
                    }
                    else if (var_r29 == 3) {
                        break;
                    }
                }
                fn_1_98E4();
                break;
            case 1:
                var_r30 = 2;
                fn_1_1811C();
                var_r29 = fn_1_99CC();
                if (var_r29 != 3) {
                    fn_1_1850C();
                    var_r30 = 0;
                }
                else {
                    fn_1_A0C4();
                }
                break;
            case 2:
                fn_1_1C754();
                var_r30 = fn_1_A3BC();
                fn_1_1C990();
                switch (var_r30) {
                    case 0:
                        var_r30 = 0xA;
                        var_r29 = 0;
                        fn_1_B084();
                        break;
                    case 1:
                        var_r30 = 1;
                        fn_1_AD78();
                        break;
                }
                break;
        }
    } while (var_r30 != 0x63);
    if (lbl_1_bss_35BC[1].unk_1C[0] == 0) {
        var_r21 = 0;
    }
    else {
        var_r21 = 1;
    }
    if (lbl_1_bss_35BC[1].unk_1C[3] == 0) {
        var_r20 = 1;
    }
    else {
        var_r20 = 0;
    }
    switch (lbl_1_bss_35BC[1].unk_1C[2]) {
        case 0:
            var_r22 = 0;
            break;
        case 1:
            var_r22 = 1;
            break;
        case 2:
            var_r22 = 2;
            break;
        default:
            var_r22 = 0;
            break;
    }
    {
        s32 var_r19 = lbl_1_bss_35BC[1].unk_1C[1];
        s32 var_r18 = lbl_1_bss_35BC[1].unk_08[1];
        s32 var_r17 = lbl_1_bss_35BC[1].unk_08[2];
        s32 sp18 = lbl_1_bss_35BC[1].unk_08[3];
        s32 sp14 = lbl_1_bss_35BC[1].unk_08[4];
        BoardPartyConfigSet(var_r21, var_r20, var_r22, var_r19, var_r18, var_r17, sp18, sp14);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GWPlayerCfg[var_r31].character = lbl_1_bss_3114[var_r31].unk_68;
        GWPlayerCfg[var_r31].pad_idx = lbl_1_bss_3114[var_r31].unk_6C;
        GWPlayerCfg[var_r31].diff = lbl_1_bss_3114[var_r31].unk_64;
        GWPlayerCfg[var_r31].group = 0;
        GWPlayerCfg[var_r31].iscom = lbl_1_bss_3114[var_r31].unk_60;
    }
    if (var_r21 == 1) {
        switch (lbl_1_bss_35BC[1].unk_1C[0]) {
            case 1:
                GWPlayerCfg[2].group = GWPlayerCfg[3].group = 1;
                break;
            case 2:
                GWPlayerCfg[1].group = GWPlayerCfg[3].group = 1;
                break;
            case 3:
                GWPlayerCfg[1].group = GWPlayerCfg[2].group = 1;
                break;
            default:
                GWPlayerCfg[2].group = GWPlayerCfg[3].group = 1;
                break;
        }
    }
    BoardSaveInit(lbl_1_bss_A8[2]);
    fn_1_A9B0();
    if (lbl_1_bss_A8[2] != 5) {
        WipeColorSet(0xFF, 0xFF, 0xFF);
    }
    else {
        WipeColorSet(0, 0, 0);
    }
    fn_1_C174(3);
}

void fn_1_C174(s32 arg0)
{
    s32 spC[7] = { 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F };
    if (arg0 == 0 || arg0 == 1 || arg0 == 2) {
        fn_1_4B0(0x3C);
        HuAudSeqFadeOut(lbl_1_bss_14[0], 0x3E8);
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);

    while (WipeStatGet() != 0) {
        fn_1_4D8();
    }
    CharModelKill(-1);
    MGSeqKillAll();

    if (arg0 != 0) {
        if (arg0 == 1 || arg0 == 3) {
            omOvlHisData *sp8 = omOvlHisGet(0);
            omOvlHisChg(0, OVL_MSTORY3, 0, 0);
        }
        do {
            fn_1_4D8();
        } while (lbl_1_bss_D8 != 1);
        CharARAMOpen(GWPlayerCfg[0].character);
        CharARAMOpen(GWPlayerCfg[1].character);
        CharARAMOpen(GWPlayerCfg[2].character);
        CharARAMOpen(GWPlayerCfg[3].character);
        HuAudSeqAllFadeOut(0x3E8);
        HuAudSStreamAllFadeOut(0x3E8);
    }

    switch (arg0) {
        case 0:
            omOvlReturnEx(1, 1);
            break;
        case 2:
            omOvlCallEx(spC[6], 1, 0, 0);
            break;
        case 1:
        case 3:
            omOvlCallEx(spC[GWSystem.board], 1, 0, 0);
            break;
    }
    while (1) {
        fn_1_4D8();
    }
}

s32 fn_1_C354(s32 arg0)
{
    if (arg0 == 0 && _CheckFlag(FLAG_ID_MAKE(0, 2)) != 0) {
        return 1;
    }
    if (arg0 == 1 && _CheckFlag(FLAG_ID_MAKE(0, 3)) != 0) {
        return 1;
    }
    if (arg0 == 2 && _CheckFlag(FLAG_ID_MAKE(0, 4)) != 0) {
        return 1;
    }
    if (arg0 == 3 && _CheckFlag(FLAG_ID_MAKE(0, 5)) != 0) {
        return 1;
    }
    if (arg0 == 4 && _CheckFlag(FLAG_ID_MAKE(0, 6)) != 0) {
        return 1;
    }
    if (arg0 == 5 && _CheckFlag(FLAG_ID_MAKE(0, 7)) != 0) {
        return 1;
    }
    return 0;
}

s32 fn_1_C440(void)
{
    if ((_CheckFlag(FLAG_ID_MAKE(0, 2)) != 0) && (_CheckFlag(FLAG_ID_MAKE(0, 3)) != 0) && (_CheckFlag(FLAG_ID_MAKE(0, 4)) != 0)
        && (_CheckFlag(FLAG_ID_MAKE(0, 5)) != 0) && (_CheckFlag(FLAG_ID_MAKE(0, 6)) != 0)) {
        return 1;
    }
    return 0;
}

void fn_1_C4B8(void)
{
    s32 var_r31;
    s32 var_r28;

    var_r31 = fn_1_1434(0, 0, 0);
    lbl_1_bss_14[0] = HuAudSeqPlay(0x30);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r31, 0x1E005C, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r31);
    saveExecF = 0;
    if (GWGameStat.story_continue != 1) {
        return;
    }
    var_r31 = fn_1_1434(0, 0, 0);
    while (1) {
        fn_1_4D8();
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(var_r31, 0x1E0001, -1, 5);
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
        var_r28 = fn_1_1A5C(0x1E0035, 3, 0);
        if (var_r28 == -1) {
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
            fn_1_1968(var_r31, 0x1E0003, -1, 5);
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
            var_r28 = fn_1_1DD8(0x1E0035, 3, 0);
            if (var_r28 == 0) {
                fn_1_16AC(var_r31);
                fn_1_C174(0);
            }
            continue;
        }
        if (var_r28 == 0) {
            fn_1_16AC(var_r31);
            SLLoadBoardStory();
            if (_CheckFlag(FLAG_ID_MAKE(0, 7)) != 0 && _CheckFlag(FLAG_ID_MAKE(0, 9)) != 0) {
                OSReport("########## Next to Ending\n");
                fn_1_E654(1);
                omOvlGotoEx(OVL_MSTORY2, 1, 4, 0);
            }
            else {
                if (_CheckFlag(0x10000) != 0) {
                    OSReport("########### Next to Turn\n");
                    HuDataDirClose(DATADIR_MENT);
                    HuPrcChildCreate(fn_1_7218, 0x64, 0x3000, 0, lbl_1_bss_C8);
                    fn_1_4D8();
                    fn_1_E71C(0);
                }
                else {
                    if (fn_1_C354(GWSystem.board) != 0) {
                        if (_CheckFlag(FLAG_ID_MAKE(0, 9)) != 0) {
                            if (fn_1_C440() != 0) {
                                OSReport("########## Next to MapSelect KoopaEvent\n");
                                fn_1_E654(1);
                                omOvlGotoEx(OVL_MSTORY2, 1, 0, 0);
                            }
                            else {
                                OSReport("########## Next to MapSelect NormalEvent\n");
                                fn_1_E654(1);
                                omOvlGotoEx(OVL_MENT, 1, 0xA, 0);
                            }
                        }
                        else if (GWSystem.board == 5) {
                            OSReport("########## Next to BoardClear KoopaEvent\n");
                            fn_1_E654(0);
                            omOvlGotoEx(OVL_MSTORY2, 1, 1, 0);
                        }
                        else {
                            OSReport("########## Next to BoardClear NormalEvent\n");
                            fn_1_E654(0);
                            omOvlGotoEx(OVL_MSTORY, 1, 0, 0);
                        }
                    }
                    else {
                        if (_CheckFlag(FLAG_ID_MAKE(0, 9)) != 0) {
                            if (GWSystem.board == 5) {
                                OSReport("########## Next to BoardMiss KoopaEvent\n");
                                fn_1_E654(0);
                                omOvlGotoEx(OVL_MSTORY2, 1, 2, 0);
                            }
                            else {
                                OSReport("########### Next to BoardMiss NormalEvent\n");
                                fn_1_E654(0);
                                omOvlGotoEx(OVL_MSTORY, 1, 1, 0);
                            }
                        }
                        else {
                            OSReport("########### Next to Turn\n");
                            HuDataDirClose(DATADIR_MENT);
                            HuPrcChildCreate(fn_1_7218, 0x64, 0x3000, 0, lbl_1_bss_C8);
                            fn_1_4D8();
                            fn_1_E71C(0);
                        }
                    }
                }
            }
            while (1) {
                fn_1_4D8();
            }
        }
        if (var_r28 == 1) {
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
            fn_1_1968(var_r31, 0x1E0002, -1, -1);
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
            fn_1_16AC(var_r31);
            break;
        }
    }
}

void fn_1_CAE4(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r30, 0x1A0004, -1, 5);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    var_r29 = fn_1_1DD8(0x1E0035, 3, 0);
    fn_1_16AC(var_r30);
    if (var_r29 == 0) {
        s32 spC[4] = { 3, 0, 2, 4 };
        _SetFlag(0x1000B);
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            GWPlayerCfg[var_r31].character = spC[var_r31];
            GWPlayerCfg[var_r31].pad_idx = var_r31;
            GWPlayerCfg[var_r31].diff = 0;
            GWPlayerCfg[var_r31].group = 0;
            GWPlayerCfg[var_r31].iscom = 1;
            OSReport("ID-%d CHR-%d PAD-%d DIF-%d GRP-%d COM-%d\n", var_r31, GWPlayerCfg[var_r31].character, GWPlayerCfg[var_r31].pad_idx,
                GWPlayerCfg[var_r31].diff, GWPlayerCfg[var_r31].group, GWPlayerCfg[var_r31].iscom);
        }
        BoardSaveInit(6);
        GWSystem.max_turn = 0x14;
        HuDataDirClose(DATADIR_MENT);
        HuPrcChildCreate(fn_1_7218, 0x64, 0x3000, 0, lbl_1_bss_C8);
        {
            omOvlHisData *sp8 = omOvlHisGet(0);
        }
        omOvlHisChg(0, OVL_MENT, 1, 1);
        fn_1_C174(2);
    }
    else {
        _ClearFlag(0x1000B);
    }
}

void fn_1_CD6C(void)
{
    fn_1_1DFB8();
}

s32 fn_1_CD8C(void)
{
    s32 sp8;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    sp8 = 0;
    fn_1_1CF68();
    var_r31 = fn_1_1434(0, 0, 0);
    while (1) {
        fn_1_4D8();
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(var_r31, 0x1E005E, -1, -1);
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
        fn_1_2154(0x1A0020);
        lbl_1_bss_3114->unk_04 = (MentDllUnkFunc)fn_1_1E404;
        while (1) {
            if (lbl_1_bss_3114->unk_70[0] == 1) {
                var_r30 = 1;
                break;
            }
            else if ((HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_B) != 0) {
                HuAudFXPlay(3);
                lbl_1_bss_3114->unk_04 = NULL;
                var_r30 = 0;
                break;
            }
            else {
                fn_1_4D8();
            }
        }
        lbl_1_bss_3114->unk_04 = NULL;
        fn_1_2318(0);
        if (var_r30 != 0) {
            break;
        }
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(var_r31, 0x1E0005, -1, 5);
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
        var_r29 = fn_1_1DD8(0x1E0035, 3, 0);
        if (var_r29 == 0) {
            fn_1_16AC(var_r31);
            fn_1_C174(0);
        }
    }
    fn_1_16AC(var_r31);
    fn_1_4B0(0x1E);
    return var_r30;
}

s32 fn_1_CF8C(void)
{
    s32 sp8;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    sp8 = 0;
    var_r28 = -1;
    var_r27 = -1;
    var_r31 = fn_1_1434(0, 0, 0);
    while (1) {
        fn_1_4D8();
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(var_r31, 0x1E0009, -1, -1);
        fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
        fn_1_2154(0x1A0021);
        lbl_1_bss_35BC[1].unk_08[1] = 0;
        fn_1_1DED8();
        lbl_1_bss_35BC[0].unk_04 = (MentDllUnkFunc)fn_1_1E8A4;
        while (1) {
            fn_1_4D8();
            if ((var_r28 != lbl_1_bss_35BC[0].unk_08[0]) || (var_r27 != lbl_1_bss_35BC[0].unk_1C[lbl_1_bss_35BC[0].unk_08[0] - 1])) {
                var_r28 = lbl_1_bss_35BC[0].unk_08[0];
                var_r27 = lbl_1_bss_35BC[0].unk_1C[lbl_1_bss_35BC[0].unk_08[0] - 1];
                switch (lbl_1_bss_35BC[0].unk_08[0]) {
                    case 1:
                        HuWinInsertMesSet(var_r31, lbl_1_bss_35BC[0].unk_1C[0] + 0x1B0028, 0);
                        fn_1_1968(var_r31, 0x1B0027, -1, -0x3E7);
                        break;
                    case 2:
                        fn_1_1968(var_r31, lbl_1_bss_35BC[0].unk_1C[1] + 0x1B0018, -1, -0x3E7);
                        break;
                }
            }
            if (lbl_1_bss_35BC[0].unk_08[3] != 0) {
                continue;
            }
            if (lbl_1_bss_35BC[1].unk_08[1] == 1) {
                var_r30 = 2;
                break;
            }
            else if (lbl_1_bss_35BC[1].unk_08[1] == -1) {
                var_r30 = 0;
                break;
            }
        }
        fn_1_1DF48();
        lbl_1_bss_35BC[0].unk_04 = NULL;
        fn_1_2318(0);
        if (var_r30 == 1) {
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
            fn_1_1968(var_r31, 0x1E0005, -1, 5);
            fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
            var_r29 = fn_1_1DD8(0x1E0035, 3, 0);
            if (var_r29 == 0) {
                fn_1_16AC(var_r31);
                fn_1_C174(0);
            }
        }
        else if (var_r30 == 2) {
            fn_1_1968(var_r31, 0x1B0000, -1, 5);
            var_r29 = fn_1_1A5C(0x1E0035, 3, 0);
            if (var_r29 == 0) {
                break;
            }
            fn_1_1968(var_r31, 0x1B0007, -1, 5);
            var_r29 = fn_1_1DD8(0x1E0035, 3, 0);
            if (var_r29 == 0) {
                fn_1_1CF68();
                var_r30 = 0;
                break;
            }
            else {
                var_r28 = -1;
                var_r27 = -1;
            }
        }
        else {
            var_r30 = 0;
            break;
        }
    }
    lbl_1_bss_E0 = lbl_1_bss_35BC[0].unk_1C[1];
    fn_1_16AC(var_r31);
    return var_r30;
}

void fn_1_D310(void)
{
    fn_1_1E1B4();
}

void fn_1_D330(void)
{
    fn_1_1F868();
}

void fn_1_D350(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    fn_1_4B0(0x3C);
    var_r29 = fn_1_1434(0, 0, 0);
    lbl_1_bss_3104->work[0] = 1;
    var_r31 = -1;
    var_r31 = HuAudFXPlay(0x43);
    HuAudFXPanning(var_r31, 0x20);
    var_r31 = HuAudFXPlay(0x40);
    HuAudFXPanning(var_r31, 0x30);
    var_r31 = HuAudFXPlay(0x37);
    HuAudFXPanning(var_r31, 0x40);
    var_r31 = HuAudFXPlay(0x4B);
    HuAudFXPanning(var_r31, 0x4C);
    var_r31 = HuAudFXPlay(0x46);
    HuAudFXPanning(var_r31, 0x60);
    HuAudFXPlay(0x9A);
    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        fn_1_59A0(lbl_1_bss_33AC[var_r30].unk_00, 1, 6, 5, 1);
    }
    HuWinInsertMesSet(var_r29, lbl_1_bss_3114->unk_68, 0);
    fn_1_1968(var_r29, 0x1E0006, 0, 0xB4);
    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        fn_1_59A0(lbl_1_bss_33AC[var_r30].unk_00, 1, 1, 0xF, 1);
    }
    fn_1_4B0(0x1E);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
    HuWinInsertMesSet(var_r29, lbl_1_bss_3114->unk_68, 0);
    fn_1_1968(var_r29, 0x1E0007, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    fn_1_2808(fn_1_148B0);
    HuAudFXPlay(0x39);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r29, 0x1E0008, 0, 0x78);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
    fn_1_2808(fn_1_13F68);
    fn_1_16AC(var_r29);
    fn_1_4B0(0x78);
    lbl_1_bss_3104->func = NULL;
    _ClearFlag(2);
    _ClearFlag(3);
    _ClearFlag(4);
    _ClearFlag(5);
    _ClearFlag(6);
    _ClearFlag(7);
    _ClearFlag(1);
    _ClearFlag(9);
}

void fn_1_D634(void)
{
    s32 var_r31;
    s32 i;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    s32 sp8[6] = { 1, 2, 0, 3, 4, 5 };
    var_r28 = 0;
    var_r31 = 2;

    if (lbl_1_data_2F0 == -1) {
        var_r29 = fn_1_1434(0, 0, 0);
    }
    else {
        var_r29 = lbl_1_data_2F0;
        lbl_1_data_2F0 = -1;
    }
    while (1) {
        fn_1_4D8();
        var_r28 = 0;
        lbl_1_bss_33AC[0].unk_34 = 1;
        HuAudFXPlay(lbl_1_data_0[0][3]);
        fn_1_59A0(lbl_1_bss_33AC[sp8[var_r31]].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(var_r29, 0x1A0008, -1, -1);
        fn_1_59A0(lbl_1_bss_33AC[sp8[var_r31]].unk_00, 1, 1, 0xF, 1);
        fn_1_2154(0x1A0020);
        for (i = 0; i < 5; i++) {
            lbl_1_bss_33AC[i].unk_08 = 0;
            lbl_1_bss_33AC[i].unk_04 = (MentDllUnkFunc)fn_1_127FC;
        }
        lbl_1_bss_33AC[sp8[var_r31]].unk_08 = 1;
        lbl_1_bss_35BC[0].unk_04 = (MentDllUnkFunc)fn_1_18F74;
        while (1) {
            fn_1_4D8();
            for (i = 0; i < 5; i++) {
                if (lbl_1_bss_33AC[i].unk_08 != 2) {
                    break;
                }
            }
            if (i == 5 && var_r28 >= 0x15) {
                if ((HuPadBtnDown[lbl_1_bss_3114->unk_6C] & 0x100)) {
                    HuAudFXPlay(2);
                    var_r26 = 2;
                    break;
                }

                if ((HuPadStkX[lbl_1_bss_3114[0].unk_6C] >= 0x32) || ((HuPadBtn[lbl_1_bss_3114[0].unk_6C] & PAD_BUTTON_RIGHT) != 0)) {
                    var_r31++;
                    if (var_r31 > 4) {
                        var_r31 = 4;
                    }
                    else {
                        var_r28 = 0;
                    }
                }
                else if ((HuPadStkX[lbl_1_bss_3114[0].unk_6C] <= -50) || ((HuPadBtn[lbl_1_bss_3114[0].unk_6C] & PAD_BUTTON_LEFT) != 0)) {
                    var_r31--;
                    if (var_r31 < 0) {
                        var_r31 = 0;
                    }
                    else {
                        var_r28 = 0;
                    }
                }
                else if ((HuPadBtnDown[0] & 0x200)) {
                    var_r26 = 1;
                    break;
                }
            }
            if (var_r28 == 0) {
                for (i = 0; i < 5; i++) {
                    lbl_1_bss_33AC[i].unk_08 = 0;
                }
                lbl_1_bss_33AC[sp8[var_r31]].unk_08 = 1;
            }
            if (var_r28++ == 0x14) {
                var_r28 = 0x15;
                fn_1_18A54(sp8[var_r31]);
                fn_1_1968(var_r29, sp8[var_r31] + 0x1B0001, -1, -0x3E7);
                if (sp8[var_r31] != 0) {
                    HuAudFXPlay(lbl_1_data_0[sp8[var_r31]][0]);
                }
                else {
                    HuAudFXPlay(lbl_1_data_0[sp8[var_r31]][2]);
                }
            }
        }
        fn_1_2318(0);
        if (var_r26 == 1) {
            fn_1_2808(fn_1_14058);
            if (var_r31 != 2) {
                var_r31 = 2;
                for (i = 0; i < 5; i++) {
                    lbl_1_bss_33AC[i].unk_08 = 0;
                }
                lbl_1_bss_33AC[sp8[var_r31]].unk_08 = 1;
                lbl_1_bss_33AC[sp8[var_r31]].unk_34 = 1;
            }
            fn_1_18DCC();
            fn_1_4B0(0x1E);
            fn_1_1968(var_r29, 0x1E0005, -1, 5);
            var_r27 = fn_1_1DD8(0x1E0035, 3, 0);
            if (var_r27 == 0) {
                fn_1_16AC(var_r29);
                fn_1_C174(0);
            }
            continue;
        }
        if (var_r26 != 2) {
            continue;
        }
        if (((sp8[var_r31] == 0) && (_CheckFlag(FLAG_ID_MAKE(0, 2)) != 0)) || ((sp8[var_r31] == 1) && (_CheckFlag(FLAG_ID_MAKE(0, 3)) != 0))
            || ((sp8[var_r31] == 2) && (_CheckFlag(FLAG_ID_MAKE(0, 4)) != 0)) || ((sp8[var_r31] == 3) && (_CheckFlag(FLAG_ID_MAKE(0, 5)) != 0))
            || ((sp8[var_r31] == 4) && (_CheckFlag(FLAG_ID_MAKE(0, 6)) != 0))) {
            fn_1_59A0(lbl_1_bss_33AC[sp8[var_r31]].unk_00, 1, 4, 0xF, 1);
            HuWinInsertMesSet(var_r29, sp8[var_r31] + 0x1B0021, 1);
            fn_1_1968(var_r29, sp8[var_r31] + 0x1E0052, -1, -1);
            fn_1_1968(var_r29, sp8[var_r31] + 0x1E0057, -1, 5);
            fn_1_59A0(lbl_1_bss_33AC[sp8[var_r31]].unk_00, 1, 1, 0xF, 1);
            var_r27 = fn_1_1DD8(0x1E0035, 3, 0);
            if (var_r27 == 0) {
                for (i = 0; i < 5; i++) {
                    lbl_1_bss_33AC[i].unk_04 = NULL;
                }
                lbl_1_bss_A8[2] = sp8[var_r31];
            }
            else {
                if (var_r31 != 2) {
                    var_r31 = 2;
                    for (i = 0; i < 5; i++) {
                        lbl_1_bss_33AC[i].unk_08 = 0;
                    }
                    lbl_1_bss_33AC[sp8[var_r31]].unk_08 = 1;
                    lbl_1_bss_33AC[sp8[var_r31]].unk_34 = 1;
                }
                fn_1_18DCC();
                fn_1_4B0(0x1E);
                continue;
            }
        }
        else {
            for (i = 0; i < 5; i++) {
                lbl_1_bss_33AC[i].unk_04 = NULL;
            }
            lbl_1_bss_A8[2] = sp8[var_r31];
        }
        break;
    }
    fn_1_16AC(var_r29);
}

void fn_1_DE60(void)
{
    s32 var_r31 = lbl_1_bss_A8[2];
    {
        Vec sp14 = { -120.0f, 0.0f, 670.0f };

        fn_1_1FA34();
        fn_1_2808(fn_1_14238);
        fn_1_5818(lbl_1_bss_33AC[var_r31].unk_00, 1, 3, 0xF, 1);
        fn_1_5D38(lbl_1_bss_33AC[var_r31].unk_00, 1, sp14, 5.0f, 6.0f, 10.0f, 1, 1);
        fn_1_5818(lbl_1_bss_33AC[var_r31].unk_00, 1, 1, 0xF, 1);
        Hu3DModelAttrReset(lbl_1_bss_35BC[0].unk_00->model[2], HU3D_ATTR_DISPOFF);
        fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 2, 0, 0);
        fn_1_5CDC(lbl_1_bss_35BC[0].unk_00, 2, 0);
        fn_1_4B0(0x3C);
    }
}

void fn_1_DFDC(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r31 = 0;
    var_r29 = lbl_1_bss_A8[2];
    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        Hu3DModelAttrSet(lbl_1_bss_33AC[var_r30].unk_00->model[1], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrReset(lbl_1_bss_33AC[var_r29].unk_00->model[1], HU3D_ATTR_DISPOFF);
    fn_1_11908(lbl_1_bss_35BC[var_r31].unk_00, lbl_1_bss_A8[2]);
    Hu3DModelAttrReset(lbl_1_bss_35BC[var_r31].unk_00->model[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_35BC[var_r31].unk_00->model[5], HU3D_ATTR_DISPOFF);
    lbl_1_bss_35BC[var_r31].unk_04 = (MentDllUnkFunc)fn_1_1184C;
    HuDataDirClose(DATADIR_MENT);
    HuPrcChildCreate(fn_1_7218, 0x64, 0x3000, 0, lbl_1_bss_C8);
    fn_1_5818(lbl_1_bss_35BC[var_r31].unk_00, 2, 3, 0, 0);
    var_r28 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[var_r29].unk_00, 1, 5, 0xF, 1);
    fn_1_1968(var_r28, var_r29 + 0x1E000C, -1, -1);
    fn_1_16AC(var_r28);
    fn_1_5CDC(lbl_1_bss_35BC[var_r31].unk_00, 2, 0);
    Hu3DModelAttrSet(lbl_1_bss_35BC[var_r31].unk_00->model[2], HU3D_ATTR_DISPOFF);
    HuAudSeqFadeOut(lbl_1_bss_14[0], 0xBB8);
    fn_1_2808(fn_1_14418);
    fn_1_4B0(0xA);
    HuAudFXPlay(GWPlayerCfg->character + 0x75);
    fn_1_4B0(0x8C);
}

void fn_1_E244(void)
{
    lbl_1_bss_14[0] = HuAudSeqPlay(0x30);
    OSReport("########### ME_MainProcFunc200\n");
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_4D8();
    }
    fn_1_4B0(0x3C);
}

void fn_1_E2B4(void)
{
    Vec sp14 = { 0.0f, 0.0f, 560.0f };
    Hu3DModelAttrReset(lbl_1_bss_35BC[0].unk_00->model[2], HU3D_ATTR_DISPOFF);
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 3, 0, 0);
    fn_1_5CDC(lbl_1_bss_35BC[0].unk_00, 2, 0);
    fn_1_D330();
    fn_1_2808(fn_1_146D0);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 2, 0xF, 1);
    fn_1_5D38(lbl_1_bss_33AC[0].unk_00, 1, sp14, 0.0f, 3.0f, 0.0f, 1, 0);
    fn_1_59A0(lbl_1_bss_33AC[0].unk_00, 1, 1, 0xF, 1);
}

void fn_1_E3FC(void)
{
    lbl_1_bss_14[0] = HuAudSeqPlay(6);
    OSReport("########### ME_MainProcFunc300\n");
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_4D8();
    }
    fn_1_D330();
    lbl_1_bss_35BC[1].unk_04 = (MentDllUnkFunc)fn_1_18F74;
    fn_1_18A54(5);
    fn_1_4B0(0x3C);
}

void fn_1_E48C(void)
{
    s32 var_r31;

    lbl_1_bss_A8[2] = 5;
    var_r31 = fn_1_1434(0, 0, 0);
    HuAudFXPlay(lbl_1_data_0[6][2]);
    fn_1_1968(var_r31, 0x1F0008, 0, 0x3C);
    fn_1_59A0(lbl_1_bss_3354.unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r31);
    fn_1_1FC54();
    fn_1_4B0(0x3C);
    Hu3DModelAttrReset(lbl_1_bss_35BC[1].unk_00->model[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_35BC[1].unk_00->model[5], HU3D_ATTR_DISPOFF);
    fn_1_7304();
    HuDataDirClose(DATADIR_MENT);
    HuPrcChildCreate(fn_1_7218, 0x64, 0x3000, 0, lbl_1_bss_C8);
    fn_1_59A0(lbl_1_bss_3354.unk_00, 1, 2, 0xF, 1);
    fn_1_5818(lbl_1_bss_35BC[1].unk_00, 2, 3, 0, 0);
    fn_1_4B0(0x3C);
    HuAudFXPlay(lbl_1_data_0[6][0]);
    fn_1_5CDC(lbl_1_bss_35BC[1].unk_00, 2, 0);
    Hu3DModelAttrSet(lbl_1_bss_35BC[1].unk_00->model[2], HU3D_ATTR_DISPOFF);
    HuAudSeqFadeOut(lbl_1_bss_14[0], 0xBB8);
    fn_1_2808(fn_1_14418);
    fn_1_4B0(0xA);
    fn_1_4B0(0x8C);
}

void fn_1_E654(s32 arg0)
{
    fn_1_4B0(0x3C);
    HuAudSeqFadeOut(lbl_1_bss_14[0], 0x3E8);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_4D8();
    }
    CharModelKill(-1);
    MGSeqKillAll();
    HuAudAllStop();
    HuDataDirClose(DATADIR_MENT);
    CharARAMOpen(GWPlayerCfg[0].character);
    if (arg0 == 0) {
        CharARAMOpen(GWPlayerCfg[1].character);
        CharARAMOpen(GWPlayerCfg[2].character);
        CharARAMOpen(GWPlayerCfg[3].character);
    }
}

void fn_1_E71C(s32 arg0)
{
    s32 spC[7] = { 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F };
    fn_1_4B0(0x3C);
    HuAudSeqFadeOut(lbl_1_bss_14[0], 0x3E8);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_4D8();
    }
    CharModelKill(-1);
    MGSeqKillAll();
    {
        omOvlHisData *sp8 = omOvlHisGet(0);
    }
    omOvlHisChg(0, OVL_MSTORY3, 0, 0);
    do {
        fn_1_4D8();
    } while (lbl_1_bss_D8 != 1);
    CharARAMOpen(GWPlayerCfg[0].character);
    CharARAMOpen(GWPlayerCfg[1].character);
    CharARAMOpen(GWPlayerCfg[2].character);
    CharARAMOpen(GWPlayerCfg[3].character);
    HuAudSeqAllFadeOut(0x3E8);
    HuAudSStreamAllFadeOut(0x3E8);
    omOvlCallEx(spC[GWSystem.board], 1, 0, 0);
    while (1) {
        fn_1_4D8();
    }
}

void fn_1_E874(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    s32 var_r31;
    s32 var_r29;
    s32 var_r27;
    s32 var_r25;
    s32 var_r24;
    s32 var_r18;

    var_r25 = 0;
    if (lbl_1_bss_A8[1] == 0) {
        fn_1_81F0();
        fn_1_77C0();
        fn_1_C4B8();
        fn_1_CAE4();
    }
    else {
        fn_1_7858();
        fn_1_CAE4();
    }
    fn_1_1DFB8();
    do {
        fn_1_4D8();
        switch (var_r25) {
            case 0:
                var_r25 = fn_1_CD8C();
                break;
            case 1:
                var_r25 = fn_1_CF8C();
                break;
        }
    } while (var_r25 != 2);
    fn_1_D310();
    fn_1_81D8();
    fn_1_7A14();
    fn_1_D634();
    fn_1_DE60();
    switch (lbl_1_bss_E0) {
        case 0:
            var_r24 = 0;
            break;
        case 1:
            var_r24 = 1;
            break;
        case 2:
            var_r24 = 2;
            break;
        default:
            var_r24 = 0;
            break;
    }
    if (lbl_1_bss_35BC[0].unk_1C[0] == 4) {
        var_r18 = 1;
    }
    else {
        var_r18 = 0;
    }
    BoardStoryConfigSet(var_r24, var_r18);
    GWStoryCharSet(lbl_1_bss_3114[0].unk_68);
    // looks a bit similar to fn_1_7304
    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        lbl_1_bss_3114[var_r31].unk_68 = -1;
        lbl_1_bss_3114[var_r31].unk_6C = var_r31;
        lbl_1_bss_3114[var_r31].unk_60 = 1;
    }
    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        do {
            lbl_1_bss_3114[var_r31].unk_68 = rand8() % 8;
            for (var_r27 = 0; var_r27 < 4; var_r27++) {
                if ((var_r31 != var_r27) && (lbl_1_bss_3114[var_r27].unk_68 != -1)
                    && (lbl_1_bss_3114[var_r31].unk_68 == lbl_1_bss_3114[var_r27].unk_68)) {
                    break;
                }
            }
        } while (var_r27 != 4);
    }
    GWSystem.diff_story = lbl_1_bss_35BC[0].unk_1C[0];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_3114[var_r31].unk_64 = GWSystem.diff_story;
        if (GWSystem.diff_story == 4) {
            lbl_1_bss_3114[var_r31].unk_64 = fn_1_7124();
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = lbl_1_bss_3114[var_r31].unk_68;
        GWPlayer[var_r31].port = GWPlayerCfg[var_r31].pad_idx = lbl_1_bss_3114[var_r31].unk_6C;
        GWPlayer[var_r31].diff = GWPlayerCfg[var_r31].diff = lbl_1_bss_3114[var_r31].unk_64;
        GWPlayerCfg[var_r31].group = 0;
        GWPlayer[var_r31].com = GWPlayerCfg[var_r31].iscom = lbl_1_bss_3114[var_r31].unk_60;
    }
    BoardSaveInit(lbl_1_bss_A8[2]);
    fn_1_DFDC();
    fn_1_E71C(0);
}

void fn_1_F83C(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    _ClearFlag(FLAG_ID_MAKE(0, 9));
    lbl_1_bss_35BC[0].unk_1C[0] = GWSystem.diff_story;
    fn_1_E244();
    fn_1_E2B4();
    fn_1_D634();
    fn_1_DE60();
    fn_1_7304();
    fn_1_DFDC();
    WipeColorSet(0xFF, 0xFF, 0xFF);
    fn_1_7684();
}

void fn_1_FEAC(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    _ClearFlag(9);
    lbl_1_bss_35BC[0].unk_1C[0] = GWSystem.diff_story;
    fn_1_E3FC();
    fn_1_E48C();
    WipeColorSet(0, 0, 0);
    fn_1_7684();
}

void fn_1_10234(void)
{
    s32 var_r31;

    Vec sp2C = { 0.0f, 0.0f, 560.0f };
    Vec sp20 = { -120.0f, 0.0f, 670.0f };
    fn_1_2808(fn_1_13DEC);
    fn_1_4B0(0x5A);
    Hu3DModelAttrReset(lbl_1_bss_33AC[4].unk_00->model[1], HU3D_ATTR_DISPOFF);
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 3, 0, 0);
    fn_1_4B0(0x96);
    lbl_1_bss_3108[0]->work[0] = 1;
    fn_1_2808(fn_1_13F68);
    fn_1_4B0(0x5A);
    fn_1_59A0(lbl_1_bss_33AC[4].unk_00, 1, 2, 0xF, 1);
    fn_1_5D38(lbl_1_bss_33AC[4].unk_00, 1, sp2C, 0.0f, 3.0f, 0.0f, 1, 0);
    fn_1_59A0(lbl_1_bss_33AC[4].unk_00, 1, 1, 0xF, 1);
    fn_1_4B0(0x1E);
    HuAudSeqPlay(0x2D);
    var_r31 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[4].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r31, 0x2F0000, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[4].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r31);
    fn_1_5818(lbl_1_bss_33AC[4].unk_00, 1, 3, 0xF, 1);
    fn_1_5D38(lbl_1_bss_33AC[4].unk_00, 1, sp20, 5.0f, 6.0f, 10.0f, 1, 1);
    fn_1_5818(lbl_1_bss_33AC[4].unk_00, 1, 1, 0xF, 1);
    fn_1_4B0(0x1E);
    fn_1_5818(lbl_1_bss_33AC[4].unk_00, 1, 5, 0xF, 1);
    fn_1_2808(fn_1_14AB8);
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 1, 0, 0, 0);
}

void fn_1_1053C(void)
{
    fn_1_4B0(0x6E);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_4D8();
    }
    CharModelKill(-1);
    MGSeqKillAll();
    HuAudFXAllStop();
    HuAudSStreamAllStop();
    omOvlGotoEx(OVL_OPTION, 1, 0, 0);
    while (1) {
        fn_1_4D8();
    }
}

void fn_1_105B8(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    fn_1_81F0();
    fn_1_10234();
    fn_1_1053C();
}

void fn_1_10954(void)
{
    s32 var_r31;

    Vec sp2C = { 0.0f, 0.0f, 560.0f };
    Vec sp20 = { -120.0f, 0.0f, 670.0f };
    fn_1_2808(fn_1_13DEC);
    fn_1_4B0(0x5A);
    Hu3DModelAttrReset(lbl_1_bss_33AC[2].unk_00->model[1], HU3D_ATTR_DISPOFF);
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 3, 0, 0);
    fn_1_4B0(0x96);
    lbl_1_bss_3108[0]->work[0] = 1;
    fn_1_2808(fn_1_13F68);
    fn_1_4B0(0x5A);
    fn_1_59A0(lbl_1_bss_33AC[2].unk_00, 1, 2, 0xF, 1);
    fn_1_5D38(lbl_1_bss_33AC[2].unk_00, 1, sp2C, 0.0f, 3.0f, 0.0f, 1, 0);
    fn_1_59A0(lbl_1_bss_33AC[2].unk_00, 1, 1, 0xF, 1);
    fn_1_4B0(0x1E);
    HuAudSeqPlay(0x2F);
    var_r31 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[2].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r31, 0x320000, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[2].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r31);
    fn_1_5818(lbl_1_bss_33AC[2].unk_00, 1, 3, 0xF, 1);
    fn_1_5D38(lbl_1_bss_33AC[2].unk_00, 1, sp20, 5.0f, 6.0f, 10.0f, 1, 1);
    fn_1_5818(lbl_1_bss_33AC[2].unk_00, 1, 1, 0xF, 1);
    fn_1_4B0(0x1E);
    fn_1_5818(lbl_1_bss_33AC[2].unk_00, 1, 5, 0xF, 1);
    fn_1_2808(fn_1_14AB8);
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 1, 0, 0, 0);
}

void fn_1_10C5C(void)
{
    fn_1_4B0(0x6E);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_4D8();
    }
    CharModelKill(-1);
    MGSeqKillAll();
    HuAudFXAllStop();
    HuAudSStreamAllStop();
    omOvlGotoEx(OVL_PRESENT, 1, 0, 0);
    while (1) {
        fn_1_4D8();
    }
}

void fn_1_10CD8(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    fn_1_81F0();
    fn_1_10954();
    fn_1_10C5C();
}

void fn_1_11074(void)
{
    s32 var_r31;
    s32 var_r30;

    Vec sp14 = { 0.0f, 0.0f, 560.0f };
    fn_1_2808(fn_1_13DEC);
    fn_1_4B0(0x5A);
    Hu3DModelAttrReset(lbl_1_bss_33AC[3].unk_00->model[1], HU3D_ATTR_DISPOFF);
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 2, 3, 0, 0);
    fn_1_4B0(0x96);
    lbl_1_bss_3108[0]->work[0] = 1;
    fn_1_2808(fn_1_13F68);
    fn_1_4B0(0x5A);
    fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 2, 0xF, 1);
    fn_1_5D38(lbl_1_bss_33AC[3].unk_00, 1, sp14, 0.0f, 3.0f, 0.0f, 1, 0);
    fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 1, 0xF, 1);
    fn_1_4B0(0x1E);
    var_r31 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r31, 0x330000, -1, -1);
    fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 1, 0xF, 1);
    fn_1_16AC(var_r31);
    var_r31 = fn_1_1434(0, 0, 0);
    fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 4, 0xF, 1);
    fn_1_1968(var_r31, 0x330001, -1, 5);
    fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 1, 0xF, 1);
    var_r30 = fn_1_1A5C(0x1E0035, 3, 0);
    fn_1_16AC(var_r31);
    if (var_r30 == 0) {
        var_r31 = fn_1_1434(0, 0, 0);
        fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 4, 0xF, 1);
        fn_1_1968(var_r31, 0x330002, -1, -1);
        fn_1_59A0(lbl_1_bss_33AC[3].unk_00, 1, 1, 0xF, 1);
        fn_1_16AC(var_r31);
    }
}

void fn_1_11368(void)
{

    Vec sp14 = { -120.0f, 0.0f, 670.0f };
    fn_1_5818(lbl_1_bss_33AC[3].unk_00, 1, 3, 0xF, 1);
    fn_1_5D38(lbl_1_bss_33AC[3].unk_00, 1, sp14, 5.0f, 6.0f, 10.0f, 1, 1);
    fn_1_5818(lbl_1_bss_33AC[3].unk_00, 1, 1, 0xF, 1);
    fn_1_4B0(0x1E);
    fn_1_5818(lbl_1_bss_33AC[3].unk_00, 1, 5, 0xF, 1);
    fn_1_2808(fn_1_14AB8);
    fn_1_5818(lbl_1_bss_35BC[0].unk_00, 1, 0, 0, 0);
}

void fn_1_114A0(void)
{
    fn_1_4B0(0x6E);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_4D8();
    }
    CharModelKill(-1);
    MGSeqKillAll();
    HuAudFadeOut(1);
    omOvlReturnEx(1, 1);
    while (1) {
        fn_1_4D8();
    }
}

void fn_1_11514(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    s32 spC = 0xA;
    s32 sp8 = 0;
    fn_1_81F0();
    fn_1_11074();
    fn_1_11368();
    fn_1_114A0();
}

void fn_1_116F4(void)
{
    omObjData *var_r31;

    var_r31 = omAddObjEx(lbl_1_bss_C8, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_366C.unk_00 = var_r31;
    switch (lbl_1_bss_A8[0]) {
        case 0:
        case 20:
            lbl_1_bss_366C.unk_04 = (MentDllUnkFunc)fn_1_B654;
            break;
        case 1:
            lbl_1_bss_366C.unk_04 = (MentDllUnkFunc)fn_1_E874;
            break;
        case 3:
            lbl_1_bss_366C.unk_04 = (MentDllUnkFunc)fn_1_105B8;
            break;
        case 4:
            lbl_1_bss_366C.unk_04 = (MentDllUnkFunc)fn_1_10CD8;
            break;
        case 5:
            lbl_1_bss_366C.unk_04 = (MentDllUnkFunc)fn_1_11514;
            break;
        case 10:
            lbl_1_bss_366C.unk_04 = (MentDllUnkFunc)fn_1_F83C;
            break;
        case 11:
            lbl_1_bss_366C.unk_04 = (MentDllUnkFunc)fn_1_FEAC;
            break;
    }
    while (1) {
        fn_1_4D8();
        if (lbl_1_bss_366C.unk_04 == NULL) {
            continue;
        }
        lbl_1_bss_366C.unk_04(var_r31, &lbl_1_bss_366C);
    }
}

void fn_1_1184C(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    Hu3DData[arg0->model[4]].pos.y = fn_1_3F4(80.0f, 90.0f, arg1->unk_1C[0]++, 360.0f);
    if (arg1->unk_1C[0] >= 0x168) {
        arg1->unk_1C[0] = 0;
    }
}

void fn_1_11908(omObjData *arg0, s32 arg1)
{
    arg0->model[4] = Hu3DModelCreateFile(arg1 + DATA_MAKE_NUM(DATADIR_MENT, 0xD));
    if (arg1 != 5) {
        arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x13));
    }
    else {
        arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x14));
    }
    arg0->motion[4] = Hu3DMotionIDGet(arg0->model[4]);
    arg0->motion[5] = Hu3DMotionIDGet(arg0->model[5]);
    fn_1_59A0(arg0, 4, 4, 0, 2);
    fn_1_59A0(arg0, 5, 5, 0, 2);
    if (arg1 != 5) {
        Hu3DModelPosSet(arg0->model[4], 0.0f, 80.0f, 460.0f);
        Hu3DModelHookSet(arg0->model[4], "partybox_fix2-effect_fook1", arg0->model[5]);
    }
    else {
        Hu3DModelPosSet(arg0->model[4], 1200.0f, 80.0f, 460.0f);
        Hu3DModelHookSet(arg0->model[4], "koopabox_fix-effect_fook2", arg0->model[5]);
    }
    Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(arg0->model[4]);
}

void fn_1_11AD0(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x61));
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x69));
    if (lbl_1_bss_A8[0] < 0xA) {
        object->model[3] = Hu3DModelCreateFile(lbl_1_bss_A8[0] + DATA_MAKE_NUM(DATADIR_MENT, 0x63));
    }
    else {
        object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x64));
    }
    if ((lbl_1_bss_A8[4] == 1) && ((lbl_1_bss_A8[0] == 0) || (lbl_1_bss_A8[0] == 0x14))) {
        object->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x6C));
        Hu3DModelLayerSet(object->model[6], 2);
        Hu3DModelPosSet(object->model[6], 50.0f, 0.0f, -100.0f);
        object->model[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x6D));
        Hu3DModelLayerSet(object->model[7], 2);
        Hu3DModelPosSet(object->model[7], 1150.0f, 0.0f, -100.0f);
    }
    object->motion[0] = Hu3DMotionIDGet(object->model[1]);
    object->motion[1] = Hu3DMotionIDGet(object->model[3]);
    object->motion[2] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MENT, 0x6A));
    object->motion[3] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MENT, 0x6B));
    if (lbl_1_bss_A8[0] == 0xA) {
        fn_1_59A0(object, 2, 3, 0, 2);
    }
    else {
        fn_1_59A0(object, 2, 3, 0, 2);
    }
    fn_1_59A0(object, 3, 1, 0, 1);
    fn_1_59A0(object, 1, 0, 0, 2);
    Hu3DModelShadowMapObjSet(object->model[1], "base_fix9-base");
}

void fn_1_11DA4(omObjData *object, s32 arg1, s32 arg2, s32 arg3)
{

    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x62));
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x69));
    object->motion[1] = Hu3DMotionIDGet(object->model[1]);
    object->motion[2] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MENT, 0x6A));
    object->motion[3] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MENT, 0x6B));
    if (lbl_1_bss_A8[0] == 0xB) {
        fn_1_59A0(object, 2, 3, 0, 2);
    }
    else {
        fn_1_59A0(object, 2, 2, 0, 2);
        Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    }
    fn_1_59A0(object, 1, 1, 0, 1);
    Hu3DModelPosSet(object->model[1], 1200.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[2], 1200.0f, 0.0f, 0.0f);
    if (lbl_1_bss_A8[0] == 3) {
        object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x12));
        object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x14));
        object->motion[4] = Hu3DMotionIDGet(object->model[4]);
        object->motion[5] = Hu3DMotionIDGet(object->model[5]);
        fn_1_59A0(object, 4, 4, 0, 2);
        fn_1_59A0(object, 5, 5, 0, 2);
        Hu3DModelPosSet(object->model[4], 1200.0f, 80.0f, 460.0f);
        Hu3DModelHookSet(object->model[4], "koopabox_fix-effect_fook2", object->model[5]);
        Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF);
        Hu3DModelShadowSet(object->model[4]);
        Hu3DModelAttrReset(object->model[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(object->model[5], HU3D_ATTR_DISPOFF);
        lbl_1_bss_35BC[1].unk_04 = (MentDllUnkFunc)fn_1_1184C;
    }
    Hu3DModelShadowMapObjSet(object->model[1], "base_story-base");
    if (lbl_1_bss_A8[0] == 0xB) {
        object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x12));
        object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x14));
        object->motion[4] = Hu3DMotionIDGet(object->model[4]);
        object->motion[5] = Hu3DMotionIDGet(object->model[5]);
        fn_1_59A0(object, 4, 4, 0, 2);
        fn_1_59A0(object, 5, 5, 0, 2);
        Hu3DModelPosSet(object->model[4], 1200.0f, 80.0f, 460.0f);
        Hu3DModelHookSet(object->model[4], "koopabox_fix-effect_fook2", object->model[5]);
        Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF);
        Hu3DModelShadowSet(object->model[4]);
    }
}

void fn_1_121D8(void)
{
    omObjData *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = lbl_1_bss_CC;
    lbl_1_bss_CC = var_r30 + 1;
    var_r31 = omAddObjEx(lbl_1_bss_C8, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_35BC[var_r30].unk_00 = var_r31;
    lbl_1_bss_35BC[var_r30].unk_04 = NULL;
    if (var_r30 == 0) {
        fn_1_11AD0(var_r31);
        switch (lbl_1_bss_A8[0]) {
            case 0:
                fn_1_20B54(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                fn_1_151B8(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                fn_1_17CC8(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                fn_1_18788(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                fn_1_1BB2C(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                break;
            case 1:
                fn_1_1D4FC(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                fn_1_1F6B8(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                fn_1_18788(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                break;
            case 10:
                if (GWSystem.mg_list == 3) {
                    GWSystem.mg_list = 0;
                }
                var_r29 = GWSystem.mg_list;
                lbl_1_bss_35BC[0].unk_1C[1] = var_r29;
                lbl_1_bss_35BC[0].unk_1C[0] = GWPlayerCfg[0].diff;
                fn_1_1F6B8(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                fn_1_18788(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                break;
            case 5:
                fn_1_20B54(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                fn_1_151B8(&lbl_1_bss_35BC[var_r30], 0, 0, 0);
                break;
        }
    }
    else {
        fn_1_11DA4(var_r31, 0, 0, 0);
        if (lbl_1_bss_A8[0] == 0xB) {
            fn_1_1F6B8(lbl_1_bss_35BC, 0, 0, 0);
            fn_1_18788(lbl_1_bss_35BC, 0, 0, 0);
        }
    }
    while (1) {
        fn_1_4D8();
        if (lbl_1_bss_35BC[var_r30].unk_04 == NULL) {
            continue;
        }
        lbl_1_bss_35BC[var_r30].unk_04(var_r31, &lbl_1_bss_35BC[var_r30]);
    }
}

void fn_1_127FC(omObjData *arg0, MentDllUnkBss33ACStruct *arg1)
{
    float var_f31;
    float var_f30;

    var_f31 = 0.0f;
    var_f30 = 0.0f;
    var_f31 = Hu3DData[arg0->model[1]].pos.z;
    var_f30 = Hu3DData[arg0->model[1]].rot.y;
    if (arg1->unk_08 == 1) {
        if (var_f31 > 560.0f) {
            arg1->unk_08 = 2;
            fn_1_59A0(arg0, 1, 1, 0xF, 1);
        }
        else {
            var_f31 += 5.0f;
            fn_1_59A0(arg0, 1, 2, 0xF, 1);
            var_f30 = fn_1_234(var_f30, 0.0f, 10.0f);
        }
    }
    else if (arg1->unk_08 == 0) {
        if (var_f31 <= 460.0f) {
            arg1->unk_08 = 2;
            fn_1_59A0(arg0, 1, 1, 0xF, 1);
        }
        else {
            var_f31 -= 5.0f;
            fn_1_59A0(arg0, 1, 2, 0xF, 1);
            var_f30 = fn_1_234(var_f30, lbl_1_data_120[arg1->unk_30], 10.0f);
        }
    }
    Hu3DData[arg0->model[1]].pos.z = var_f31;
    Hu3DData[arg0->model[1]].rot.y = var_f30;
}

void fn_1_12A0C(omObjData *object, s32 arg1)
{
    s32 sp20[6] = {
        DATA_MAKE_NUM(DATADIR_MENT, 0x6E),
        DATA_MAKE_NUM(DATADIR_MENT, 0x75),
        DATA_MAKE_NUM(DATADIR_MENT, 0x7C),
        DATA_MAKE_NUM(DATADIR_MENT, 0x83),
        DATA_MAKE_NUM(DATADIR_MENT, 0x89),
        DATA_MAKE_NUM(DATADIR_MENT, 0x90),
    };
    s32 sp38[6][6] = {
        DATA_MAKE_NUM(DATADIR_MENT, 0x6F),
        DATA_MAKE_NUM(DATADIR_MENT, 0x70),
        DATA_MAKE_NUM(DATADIR_MENT, 0x71),
        DATA_MAKE_NUM(DATADIR_MENT, 0x72),
        DATA_MAKE_NUM(DATADIR_MENT, 0x73),
        DATA_MAKE_NUM(DATADIR_MENT, 0x74),
        DATA_MAKE_NUM(DATADIR_MENT, 0x76),
        DATA_MAKE_NUM(DATADIR_MENT, 0x77),
        DATA_MAKE_NUM(DATADIR_MENT, 0x78),
        DATA_MAKE_NUM(DATADIR_MENT, 0x79),
        DATA_MAKE_NUM(DATADIR_MENT, 0x7A),
        DATA_MAKE_NUM(DATADIR_MENT, 0x7B),
        DATA_MAKE_NUM(DATADIR_MENT, 0x7D),
        DATA_MAKE_NUM(DATADIR_MENT, 0x7E),
        DATA_MAKE_NUM(DATADIR_MENT, 0x7F),
        DATA_MAKE_NUM(DATADIR_MENT, 0x80),
        DATA_MAKE_NUM(DATADIR_MENT, 0x81),
        DATA_MAKE_NUM(DATADIR_MENT, 0x82),
        DATA_MAKE_NUM(DATADIR_MENT, 0x84),
        DATA_MAKE_NUM(DATADIR_MENT, 0x85),
        DATA_MAKE_NUM(DATADIR_MENT, 0x85),
        DATA_MAKE_NUM(DATADIR_MENT, 0x86),
        DATA_MAKE_NUM(DATADIR_MENT, 0x87),
        DATA_MAKE_NUM(DATADIR_MENT, 0x88),
        DATA_MAKE_NUM(DATADIR_MENT, 0x8A),
        DATA_MAKE_NUM(DATADIR_MENT, 0x8B),
        DATA_MAKE_NUM(DATADIR_MENT, 0x8C),
        DATA_MAKE_NUM(DATADIR_MENT, 0x8D),
        DATA_MAKE_NUM(DATADIR_MENT, 0x8E),
        DATA_MAKE_NUM(DATADIR_MENT, 0x8F),
        DATA_MAKE_NUM(DATADIR_MENT, 0x91),
        DATA_MAKE_NUM(DATADIR_MENT, 0x92),
        DATA_MAKE_NUM(DATADIR_MENT, 0x93),
        DATA_MAKE_NUM(DATADIR_MENT, 0x94),
        DATA_MAKE_NUM(DATADIR_MENT, 0x95),
        DATA_MAKE_NUM(DATADIR_MENT, 0x91),
    };
    object->model[1] = Hu3DModelCreateFile(sp20[arg1]);
    object->motion[1] = Hu3DJointMotionFile(object->model[1], sp38[arg1][0]);
    object->motion[2] = Hu3DJointMotionFile(object->model[1], sp38[arg1][1]);
    object->motion[3] = Hu3DJointMotionFile(object->model[1], sp38[arg1][2]);
    object->motion[4] = Hu3DJointMotionFile(object->model[1], sp38[arg1][3]);
    object->motion[5] = Hu3DJointMotionFile(object->model[1], sp38[arg1][4]);
    object->motion[6] = Hu3DJointMotionFile(object->model[1], sp38[arg1][5]);
    {
        s32 sp8[6] = { 9, 14, 10, 11, 12, 13 };
        if (arg1 != 3) {
            CharModelEffectNpcInit(object->model[1], object->motion[2], 0, sp8[arg1]);
            CharModelEffectNpcInit(object->model[1], object->motion[3], 1, sp8[arg1]);
        }
    }
    fn_1_59A0(object, 1, 1, 0, 1);
    Hu3DModelPosSet(object->model[1], lbl_1_data_D8[arg1].x, lbl_1_data_D8[arg1].y, lbl_1_data_D8[arg1].z);
    Hu3DModelRotSet(object->model[1], 0.0f, lbl_1_data_120[arg1], 0.0f);
    if (lbl_1_bss_A8[0] >= 2 && lbl_1_bss_A8[0] < 0xA) {
        Hu3DModelPosSet(object->model[1], lbl_1_data_D8[0].x, lbl_1_data_D8[0].y, lbl_1_data_D8[0].z);
        Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
        if (lbl_1_bss_A8[0] == 5) {
            Hu3DModelPosSet(object->model[1], lbl_1_data_D8[0].x, 50.0f + lbl_1_data_D8[0].y, lbl_1_data_D8[0].z);
        }
    }
    if (lbl_1_bss_A8[0] < 0xA) {
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelShadowSet(object->model[1]);
    Hu3DModelLayerSet(object->model[1], 2);
}

void fn_1_12E40(void)
{
    omObjData *var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_D0;
    lbl_1_bss_D0 = var_r30 + 1;
    var_r31 = omAddObjEx(lbl_1_bss_C8, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_33AC[var_r30].unk_00 = var_r31;
    lbl_1_bss_33AC[var_r30].unk_04 = NULL;
    lbl_1_bss_33AC[var_r30].unk_30 = var_r30;
    fn_1_12A0C(var_r31, var_r30);
    while (1) {
        fn_1_4D8();
        if (lbl_1_bss_33AC[var_r30].unk_04 != NULL) {
            lbl_1_bss_33AC[var_r30].unk_04(var_r31, &lbl_1_bss_33AC[var_r30]);
        }
        if (var_r31->work[0] != 1) {
            continue;
        }
        fn_1_5C08(var_r31);
    }
}

void fn_1_13348(omObjData *arg0)
{
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x96));
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_MENT, 0x97));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_MENT, 0x98));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_MENT, 0x99));
    fn_1_59A0(arg0, 1, 3, 0, 1);
    Hu3DModelPosSet(arg0->model[1], 1020.0f, 0.0f, 800.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, 60.0f, 0.0f);
    Hu3DModelShadowSet(arg0->model[1]);
    Hu3DModelLayerSet(arg0->model[1], 2);
}

void fn_1_134A8(void)
{
    omObjData *var_r31;

    var_r31 = omAddObjEx(lbl_1_bss_C8, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_3354.unk_00 = var_r31;
    lbl_1_bss_3354.unk_04 = NULL;
    fn_1_13348(var_r31);
    while (1) {
        fn_1_4D8();
        if (lbl_1_bss_3354.unk_04 != NULL) {
            lbl_1_bss_3354.unk_04(var_r31, &lbl_1_bss_3354);
        }
        if (var_r31->work[0] != 1) {
            continue;
        }
        fn_1_5C08(var_r31);
    }
}

void fn_1_1368C(omObjData *arg0, s32 arg1)
{
    MentDllUnkBss3114Struct *var_r31;

    var_r31 = &lbl_1_bss_3114[arg1];
    var_r31->unk_58 = arg1;
    var_r31->unk_5C = 0;
    var_r31->unk_60 = var_r31->unk_58;
    if (var_r31->unk_60 > 0) {
        var_r31->unk_60 = 1;
    }
    var_r31->unk_64 = 0;
    var_r31->unk_68 = var_r31->unk_58;
    var_r31->unk_6C = var_r31->unk_58;
}

void fn_1_136F0(omObjData *arg0, s32 arg1)
{
    MentDllUnkBss3114Struct *var_r31;

    var_r31 = &lbl_1_bss_3114[arg1];
    var_r31->unk_58 = arg1;
    var_r31->unk_5C = GWPlayerCfg[var_r31->unk_58].group;
    var_r31->unk_60 = GWPlayerCfg[var_r31->unk_58].iscom;
    var_r31->unk_64 = GWPlayerCfg[var_r31->unk_58].diff;
    var_r31->unk_68 = GWPlayerCfg[var_r31->unk_58].character;
    var_r31->unk_6C = GWPlayerCfg[var_r31->unk_58].pad_idx;
}

void fn_1_137A4(omObjData *arg0, s32 arg1)
{
    MentDllUnkBss3114Struct *var_r31;

    var_r31 = &lbl_1_bss_3114[arg1];
    var_r31->unk_58 = arg1;
    var_r31->unk_5C = GWPlayerCfg[var_r31->unk_58].group;
    var_r31->unk_60 = GWPlayerCfg[var_r31->unk_58].iscom;
    var_r31->unk_64 = GWPlayerCfg[var_r31->unk_58].diff;
    var_r31->unk_68 = GWPlayerCfg[var_r31->unk_58].character;
    var_r31->unk_6C = GWPlayerCfg[var_r31->unk_58].pad_idx;
    arg0->model[1] = CharModelCreate(var_r31->unk_68, 1);
    arg0->motion[1] = CharModelMotionCreate(var_r31->unk_68, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[1], var_r31->unk_68 + DATA_MAKE_NUM(DATADIR_MENT, 0x00));
    fn_1_59A0(arg0, 1, 2, 0, 1);
    Hu3DModelPosSet(arg0->model[1], 1320.0f, 0.0f, 800.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, -60.0f, 0.0f);
    Hu3DModelShadowSet(arg0->model[1]);
    Hu3DModelLayerSet(arg0->model[1], 2);
}

void fn_1_13970(void)
{
    MentDllUnkBss3114Struct *var_r28;
    omObjData *var_r27;
    s32 var_r26;

    var_r26 = lbl_1_bss_D4;
    lbl_1_bss_D4 = var_r26 + 1;
    var_r27 = omAddObjEx(lbl_1_bss_C8, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_3114[var_r26].unk_00 = var_r27;
    lbl_1_bss_3114[var_r26].unk_04 = NULL;
    if (lbl_1_bss_A8[0] <= 1) {
        fn_1_1368C(var_r27, var_r26);
    }
    else if (lbl_1_bss_A8[0] == 0xA) {
        fn_1_136F0(var_r27, 0);
    }
    else if (lbl_1_bss_A8[0] == 0xB) {
        fn_1_137A4(var_r27, 0);
    }
    else {
        fn_1_1368C(var_r27, var_r26);
    }
    while (1) {
        fn_1_4D8();
        if (lbl_1_bss_3114[var_r26].unk_04 == NULL) {
            continue;
        }
        lbl_1_bss_3114[var_r26].unk_04(var_r27, &lbl_1_bss_3114[var_r26]);
    }
}

void fn_1_13D60(void)
{
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    var_r31->center.x = 0.0f;
    var_r31->center.y = 0.0f;
    var_r31->center.z = 0.0f;
    var_r31->rot.x = -10.0f;
    var_r31->rot.y = 0.0f;
    var_r31->rot.z = 0.0f;
    var_r31->zoom = 2900.0f;
}

void fn_1_13DEC(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 0.0f;
    sp8.center.y = 0.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = -10.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 1150.0f;
    fn_1_4138(var_r31, &sp8, var_r31->unk_40++, 180.0f, 15.0f);
}

void fn_1_13EDC(void)
{
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    var_r31->center.x = 0.0f;
    var_r31->center.y = 215.0f;
    var_r31->center.z = 0.0f;
    var_r31->rot.x = 0.0f;
    var_r31->rot.y = 0.0f;
    var_r31->rot.z = 0.0f;
    var_r31->zoom = 1600.0f;
}

void fn_1_13F68(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 0.0f;
    sp8.center.y = 215.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = 0.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 1600.0f;
    fn_1_4138(var_r31, &sp8, var_r31->unk_40++, 60.0f, 10.0f);
}

void fn_1_14058(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 0.0f;
    sp8.center.y = 215.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = 0.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 1600.0f;
    fn_1_4138(var_r31, &sp8, var_r31->unk_40++, 10.0f, 5.0f);
}

void fn_1_14148(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 1200.0f;
    sp8.center.y = 215.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = 0.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 1600.0f;
    fn_1_4138(var_r31, &sp8, var_r31->unk_40++, 10.0f, 5.0f);
}

void fn_1_14238(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 0.0f;
    sp8.center.y = 125.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = -5.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 1750.0f;
    fn_1_4138(var_r31, &sp8, var_r31->unk_40++, 30.0f, 10.0f);
}

void fn_1_14328(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 1200.0f;
    sp8.center.y = 125.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = -5.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 1750.0f;
    fn_1_4138(var_r31, &sp8, var_r31->unk_40++, 30.0f, 10.0f);
}

void fn_1_14418(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_A8[2] / 5;
    var_r31 = &lbl_1_bss_64;
    if (var_r31->unk_40 == 0x32) {
        fn_1_5818(lbl_1_bss_35BC[var_r30].unk_00, 4, 4, 0, 0);
        fn_1_5818(lbl_1_bss_35BC[var_r30].unk_00, 5, 5, 0, 0);
        HuAudFXPlay(0x7D);
    }
    sp8.center.x = 0.0f;
    if (var_r30 == 1) {
        sp8.center.x = 1200.0f;
    }
    sp8.center.y = 100.0f;
    sp8.center.z = 460.0f;
    sp8.rot.x = 0.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 125.0f;
    fn_1_4138(var_r31, &sp8, var_r31->unk_40, 180.0f, 10.0f);
    if (var_r31->unk_40++ >= 90) {
        if (var_r31->unk_40 == 91) {
            if (var_r30 == 0) {
                lbl_1_bss_24[10] = HuAudFXPlay(0x22);
            }
            else {
                lbl_1_bss_24[10] = HuAudFXPlay(0x23);
            }
        }
        var_r31->rot.x = fn_1_20C(var_r31->rot.x, -45.0f, var_r31->unk_40 - 0x5A, 90.0f);
        Hu3DData[lbl_1_bss_35BC[var_r30].unk_00->model[4]].rot.x = fn_1_20C(0.0f, 45.0f, var_r31->unk_40 - 0x5A, 90.0f);
    }
}

void fn_1_146D0(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 0.0f;
    sp8.center.y = 215.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = 0.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 1600.0f;
    fn_1_5150(var_r31, &sp8, var_r31->unk_40++, 30.0f, 10.0f);
}

void fn_1_147C0(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 1200.0f;
    sp8.center.y = 215.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = 0.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 1600.0f;
    fn_1_5150(var_r31, &sp8, var_r31->unk_40++, 30.0f, 10.0f);
}

void fn_1_148B0(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 0.0f;
    sp8.center.y = 30.0f;
    sp8.center.z = 0.0f;
    sp8.rot.x = -5.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 1100.0f;
    fn_1_4138(var_r31, &sp8, var_r31->unk_40++, 10.0f, 5.0f);
}

void fn_1_149A0(void)
{
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    var_r31->center.x = 0.0f;
    var_r31->center.y = 125.0f;
    var_r31->center.z = 0.0f;
    var_r31->rot.x = -5.0f;
    var_r31->rot.y = 0.0f;
    var_r31->rot.z = 0.0f;
    var_r31->zoom = 1750.0f;
}

void fn_1_14A2C(void)
{
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    var_r31->center.x = 1200.0f;
    var_r31->center.y = 125.0f;
    var_r31->center.z = 0.0f;
    var_r31->rot.x = -5.0f;
    var_r31->rot.y = 0.0f;
    var_r31->rot.z = 0.0f;
    var_r31->zoom = 1750.0f;
}

void fn_1_14AB8(void)
{
    MentDllUnkBss64Struct sp8;
    MentDllUnkBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    sp8.center.x = 0.0f;
    sp8.center.y = 125.0f;
    sp8.center.z = 460.0f;
    sp8.rot.x = 0.0f;
    sp8.rot.y = 0.0f;
    sp8.rot.z = 0.0f;
    sp8.zoom = 125.0f;
    fn_1_5150(var_r31, &sp8, var_r31->unk_40++, 120.0f, 10.0f);
}

void fn_1_14BA8(void)
{
    s32 var_r31;
    s32 var_r30;
    var_r30 = lbl_1_bss_35BC[0].unk_30;
    for (var_r31 = 0; var_r31 < 0x35; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, HUSPR_ATTR_DISPOFF);
    }
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        HuSprBankSet(var_r30, var_r31, 0);
        HuSprAttrReset(var_r30, var_r31, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r30, var_r31 + 8, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(var_r30, 0x28, HUSPR_ATTR_DISPOFF);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprBankSet(var_r30, var_r31 + 0x10, 0);
        HuSprBankSet(var_r30, var_r31 + 0x14, 0);
        HuSprAttrReset(var_r30, var_r31 + 0x29, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r30, var_r31 + 0x2D, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpPosSet(var_r30, 0.0f, -500.0f);
}

s32 lbl_1_data_57C[4][4] = {
    { 0xA8, 0x5A, 0x78, 0x33 },
    { 0xF8, 0xBE, 0x1CA, 0x33 },
    { 0x148, 0x5A, 0x78, 0xDE },
    { 0x198, 0xBE, 0x1CA, 0xDE },
};
s32 lbl_1_data_5BC[4][2] = {
    { 0x1B, 0x18 },
    { 0x49, 0x18 },
    { 0x77, 0x18 },
    { 0xA5, 0x18 },
};

#if VERSION_NTSC
float lbl_1_data_5DC[5][5] = {
    { 262.0f, 119.0f, 1.3f, 227.0f, 455.0f },
    { 314.0f, 168.0f, 0.75f, 265.0f, 416.0f },
    { 366.0f, 204.0f, 0.75f, 240.0f, 440.0f },
    { 418.0f, 240.0f, 0.75f, 300.0f, 381.0f },
    { -1.0f, 289.0f, 1.3f, 220.0f, 460.0f },
};
#else
float lbl_1_data_5DC[5][5] = {
    { 262.0f, 119.0f, 1.3f, 227.0f, 455.0f },
    { 314.0f, 168.0f, 0.75f, 300.0f, 381.0f },
    { 366.0f, 204.0f, 0.75f, 240.0f, 440.0f },
    { 418.0f, 240.0f, 0.75f, 300.0f, 381.0f },
    { -1.0f, 289.0f, 1.3f, 220.0f, 460.0f },
};
#endif

s32 lbl_1_data_640[4][5] = {
    { 0xB4, 0x60, 0x87, 0, 0 },
    { 0xFC, 0xB8, 0xF6, 0xD4, 0x1D4 },
    { 0x144, 0x60, 0x11A, 0xE6, 0x1C2 },
    { 0x18C, 0xB8, 0, 0, 0 },
};
s32 lbl_1_data_690[4][4] = {
    { 0xB1, 0x68, 0x78, 0x37 },
    { 0xFB, 0x68, 0x1CA, 0x37 },
    { 0x145, 0x68, 0x78, 0x8E },
    { 0x18F, 0x68, 0x1CA, 0x8E },
};

void fn_1_14CE0(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_35BC[0].unk_30;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_3114[var_r31].unk_60 != 0) {
            HuSprAttrSet(var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0x10, HUSPR_ATTR_DISPOFF);
            HuSprAttrSet(var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0x14, HUSPR_ATTR_DISPOFF);
        }
        else {
            HuSprAttrReset(var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0x10, HUSPR_ATTR_DISPOFF);
            HuSprAttrReset(var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0x14, HUSPR_ATTR_DISPOFF);
        }
        HuSprPosSet(var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0x10, lbl_1_data_57C[lbl_1_bss_3114[var_r31].unk_68 % 4][0],
            lbl_1_data_57C[lbl_1_bss_3114[var_r31].unk_68 / 4][1]);
        HuSprPosSet(var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0x14, lbl_1_data_57C[lbl_1_bss_3114[var_r31].unk_68 % 4][0],
            lbl_1_data_57C[lbl_1_bss_3114[var_r31].unk_68 / 4][1]);
    }
    for (var_r31 = 0; var_r31 <= 60; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0x32) {
            var_f31 = fn_1_32C(-500.0f, 10.0f, var_r31, 50.0f);
        }
        else {
            var_f31 = fn_1_254(10.0f, 2.06f, var_r31 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_30, 0.0f, var_f31);
    }
}

void fn_1_15098(void)
{
    float var_f31;
    s32 var_r31;

    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_32C(2.06f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_254(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_30, 0.0f, var_f31);
    }
}

void fn_1_151B8(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    AnimData *var_r26;
    AnimData *var_r25;
    AnimData *var_r24;
    AnimData *var_r23;
    AnimData *var_r22;

    var_r30 = HuSprGrpCreate(0x35);
    arg0->unk_30 = var_r30;
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x22));
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        var_r29 = HuSprCreate(HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MENT, 0x1A)), 0x3E8, 0);
        HuSprGrpMemberSet(var_r30, var_r31, var_r29);
        HuSprPosSet(var_r30, var_r31, lbl_1_data_57C[var_r31 % 4][0], lbl_1_data_57C[var_r31 / 4][1]);
        var_r29 = HuSprCreate(var_r26, 0x3F2, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 8, var_r29);
        HuSprTPLvlSet(var_r30, var_r31 + 8, 0.5f);
        HuSprPosSet(var_r30, var_r31 + 8, lbl_1_data_57C[var_r31 % 4][0] + 1, lbl_1_data_57C[var_r31 / 4][1] + 2);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = HuSprCreate(HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MENT, 0x23)), 0, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x10, var_r29);
        var_r29 = HuSprCreate(HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MENT, 0x28)), 0xA, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x14, var_r29);
    }
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x27));
    var_r25 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x2C));
    var_r24 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x2D));
    var_r23 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x2F));
    var_r22 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x2E));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = HuSprCreate(var_r26, 0, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x18, var_r29);
        var_r29 = HuSprCreate(var_r25, 0x1E, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x1C, var_r29);
        var_r29 = HuSprCreate(var_r24, 0xA, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x20, var_r29);
        var_r29 = HuSprCreate(var_r23, 0x14, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x24, var_r29);
        HuSprTPLvlSet(var_r30, var_r31 + 0x24, 0.5f);
        var_r29 = HuSprCreate(var_r22, 0x14, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x31, var_r29);
    }
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x17)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r30, 0x28, var_r29);
    HuSprTPLvlSet(var_r30, 0x28, 0.8f);
    fn_1_6534(var_r30, 0x28, 288.0f, 240.0f);
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x18));
    var_r25 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x19));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = HuSprCreate(var_r26, 0x7BC, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x29, var_r29);
        HuSprBankSet(var_r30, var_r31 + 0x29, var_r31);
        fn_1_6534(var_r30, var_r31 + 0x29, lbl_1_data_57C[var_r31][2], lbl_1_data_57C[var_r31][3]);
        var_r29 = HuSprCreate(var_r25, 0x7C6, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x2D, var_r29);
        HuSprBankSet(var_r30, var_r31 + 0x2D, var_r31);
        HuSprTPLvlSet(var_r30, var_r31 + 0x2D, 0.5f);
        fn_1_6534(var_r30, var_r31 + 0x2D, lbl_1_data_57C[var_r31][2] + 1, lbl_1_data_57C[var_r31][3] + 6);
    }
    var_r27 = lbl_1_bss_35BC[0].unk_30;
    for (var_r28 = 0; var_r28 < 0x35; var_r28++) {
        HuSprAttrSet(var_r27, var_r28, HUSPR_ATTR_DISPOFF);
    }
    for (var_r28 = 0; var_r28 < 8; var_r28++) {
        HuSprBankSet(var_r27, var_r28, 0);
        HuSprAttrReset(var_r27, var_r28, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r27, var_r28 + 8, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(var_r27, 0x28, HUSPR_ATTR_DISPOFF);
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        HuSprBankSet(var_r27, var_r28 + 0x10, 0);
        HuSprBankSet(var_r27, var_r28 + 0x14, 0);
        HuSprAttrReset(var_r27, var_r28 + 0x29, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r27, var_r28 + 0x2D, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpPosSet(var_r27, 0.0f, -500.0f);
}

void fn_1_15950(void)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    MentDllUnkBss3114Struct *var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r29 = lbl_1_bss_35BC[0].unk_30;
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        HuSprBankSet(var_r29, var_r31, 0);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprBankSet(var_r29, var_r31 + 0x10, 0);
        HuSprBankSet(var_r29, var_r31 + 0x14, 0);
        HuSprBankSet(var_r29, var_r31 + 0x18, 0);
        HuSprBankSet(var_r29, var_r31 + 0x1C, 0);
        HuSprBankSet(var_r29, var_r31 + 0x20, 0);
    }
    for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
        fn_1_4D8();
        for (var_r28 = 0; var_r28 < 4; var_r28++) {
            var_r30 = &lbl_1_bss_3114[var_r28];
            var_f31 = fn_1_32C(lbl_1_data_57C[var_r30->unk_68 % 4][0], lbl_1_data_57C[var_r30->unk_58 % 4][0], var_r31, 10.0f);
            var_f30 = fn_1_32C(lbl_1_data_57C[var_r30->unk_68 / 4][1], lbl_1_data_57C[var_r30->unk_58 / 4][1], var_r31, 10.0f);
            HuSprPosSet(var_r29, var_r30->unk_58 + 0x10, var_f31, var_f30);
            HuSprPosSet(var_r29, var_r30->unk_58 + 0x14, var_f31, var_f30);
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_3114[var_r31].unk_68 = lbl_1_bss_3114[var_r31].unk_58;
        lbl_1_bss_3114[var_r31].unk_70[0] = 0;
    }
}

void fn_1_15CB4(omObjData *arg0, MentDllUnkBss3114Struct *arg1)
{
    float var_f31;
    float var_f30;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    var_r25 = lbl_1_bss_35BC[0].unk_30;
    var_r27 = 0;
    var_r26 = 0;
    var_r30 = arg1->unk_68 % 4;
    var_r24 = var_r30;
    var_r29 = arg1->unk_68 / 4;
    var_r23 = var_r29;
    if (arg1->unk_70[0] == 0) {
        if ((HuPadBtnDown[arg1->unk_6C] & PAD_BUTTON_A) != 0) {
            arg1->unk_70[0] = 1;
            HuSprBankSet(var_r25, arg1->unk_68, 1);
            HuSprBankSet(var_r25, arg1->unk_58 + 0x10, 1);
            HuSprBankSet(var_r25, arg1->unk_58 + 0x14, 1);
            HuAudFXPlay(arg1->unk_68 + 0x6D);
        }
        else {
            if ((HuPadStkX[arg1->unk_6C] >= 5) || ((HuPadBtn[arg1->unk_6C] & 2) != 0)) {
                var_r30++;
                var_r27 = 1;
                if (var_r30 > 3) {
                    var_r30 = 3;
                }
            }
            else if ((HuPadStkX[arg1->unk_6C] <= -5) || ((HuPadBtn[arg1->unk_6C] & 1) != 0)) {
                var_r30--;
                var_r27 = -1;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
            }
            if ((HuPadStkY[arg1->unk_6C] <= -5) || ((HuPadBtn[arg1->unk_6C] & 4) != 0)) {
                var_r29++;
                var_r26 = 1;
                if (var_r29 > 1) {
                    var_r29 = 1;
                }
            }
            else if ((HuPadStkY[arg1->unk_6C] >= 5) || ((HuPadBtn[arg1->unk_6C] & 8) != 0)) {
                var_r29--;
                var_r26 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
    }
    else if ((HuPadBtnDown[arg1->unk_6C] & PAD_BUTTON_B) != 0) {
        arg1->unk_70[0] = 0;
        HuSprBankSet(var_r25, arg1->unk_68, 0);
        HuSprBankSet(var_r25, arg1->unk_58 + 0x10, 0);
        HuSprBankSet(var_r25, arg1->unk_58 + 0x14, 0);
        HuAudFXPlay(3);
    }
    if (arg1->unk_68 != (var_r30 + (var_r29 * 4))) {
        do {
            for (var_r28 = 0; var_r28 < 4; var_r28++) {
                if ((var_r28 != arg1->unk_58) && (lbl_1_bss_3114[var_r28].unk_60 == 0)
                    && ((var_r30 + (var_r29 * 4)) == lbl_1_bss_3114[var_r28].unk_68)) {
                    if ((var_r27 == 0) || (var_r26 == 0)) {
                        if (((var_r30 + var_r27) > 3) || ((var_r30 + var_r27) < 0)) {
                            var_r30 = var_r24;
                        }
                        else {
                            var_r30 += var_r27;
                        }
                        if (((var_r29 + var_r26) > 1) || ((var_r29 + var_r26) < 0)) {
                            var_r29 = var_r23;
                        }
                        else {
                            var_r29 += var_r26;
                        }
                    }
                    else if (((var_r30 + var_r27) <= 3) && ((var_r30 + var_r27) >= 0)) {
                        var_r30 += var_r27;
                    }
                    else if (((var_r29 + var_r26) <= 1) && ((var_r29 + var_r26) >= 0)) {
                        var_r29 += var_r26;
                    }
                    else {
                        var_r30 = var_r24;
                        var_r29 = var_r23;
                    }
                    break;
                }
            }
        } while (var_r28 != 4);
        if (arg1->unk_68 != (var_r30 + (var_r29 * 4))) {
            arg1->unk_68 = var_r30 + (var_r29 * 4);
            HuAudFXPlay(0);
            for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                fn_1_4D8();
                var_f31 = fn_1_32C(lbl_1_data_57C[var_r24][0], lbl_1_data_57C[var_r30][0], var_r28, 10.0f);
                var_f30 = fn_1_32C(lbl_1_data_57C[var_r23][1], lbl_1_data_57C[var_r29][1], var_r28, 10.0f);
                HuSprPosSet(var_r25, arg1->unk_58 + 0x10, var_f31, var_f30);
                HuSprPosSet(var_r25, arg1->unk_58 + 0x14, var_f31, var_f30);
            }
        }
    }
}

void fn_1_162A0(MentDllUnkBss3114Struct *arg0)
{
    s32 var_r30;

    var_r30 = lbl_1_bss_35BC[0].unk_30;
    arg0->unk_64 = 0;
    HuSprBankSet(var_r30, arg0->unk_58 + 0x20, arg0->unk_64);
    HuSprPosSet(var_r30, arg0->unk_58 + 0x20, lbl_1_data_57C[arg0->unk_68 % 4][0], lbl_1_data_57C[arg0->unk_68 / 4][1] + 0x23);
    HuSprPosSet(var_r30, arg0->unk_58 + 0x24, lbl_1_data_57C[arg0->unk_68 % 4][0] + 1, lbl_1_data_57C[arg0->unk_68 / 4][1] + 0x25);
    HuSprAttrReset(var_r30, arg0->unk_58 + 0x20, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(var_r30, arg0->unk_58 + 0x24, HUSPR_ATTR_DISPOFF);
}

s32 fn_1_1648C(MentDllUnkBss3114Struct *arg0)
{
    float var_f31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r28 = 0;
    var_r29 = lbl_1_bss_35BC[0].unk_30;
    while (1) {
        fn_1_4D8();
        var_r28 = 0;
        var_r26 = arg0->unk_64;
        if (HuPadStkX[lbl_1_bss_3114->unk_6C] >= 5 || (HuPadBtn[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_RIGHT)) {
            if (lbl_1_bss_A8[5] == 1) {
                arg0->unk_64++;
                var_r28 = 1;
                if (arg0->unk_64 > 3) {
                    arg0->unk_64 = 0;
                }
            }
            else {
                arg0->unk_64++;
                var_r28 = 1;
                if (arg0->unk_64 > 2) {
                    arg0->unk_64 = 0;
                }
            }
        }
        else if (HuPadStkX[lbl_1_bss_3114->unk_6C] <= -5 || (HuPadBtn[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_LEFT)) {
            if (lbl_1_bss_A8[5] == 1) {
                arg0->unk_64--;
                var_r28 = -1;
                if (arg0->unk_64 < 0) {
                    arg0->unk_64 = 3;
                }
            }
            else {
                arg0->unk_64--;
                var_r28 = -1;
                if (arg0->unk_64 < 0) {
                    arg0->unk_64 = 2;
                }
            }
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            var_r27 = 1;
            HuAudFXPlay(2);
            break;
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            var_r27 = 0;
            HuAudFXPlay(3);
            break;
        }
        if (arg0->unk_64 != var_r26) {
            HuAudFXPlay(0);
            for (var_r30 = 0; var_r30 <= 5; var_r30++) {
                fn_1_4D8();
                var_f31 = fn_1_32C(lbl_1_data_57C[arg0->unk_68 % 4][0], lbl_1_data_57C[arg0->unk_68 % 4][0] + (var_r28 * 10), var_r30, 5);
                HuSprPosSet(var_r29, arg0->unk_58 + 32, var_f31, lbl_1_data_57C[arg0->unk_68 / 4][1] + 35);
                HuSprPosSet(var_r29, arg0->unk_58 + 36, 1 + var_f31, lbl_1_data_57C[arg0->unk_68 / 4][1] + 37);
            }
            HuSprBankSet(var_r29, arg0->unk_58 + 32, arg0->unk_64);
            for (var_r30 = 0; var_r30 <= 5; var_r30++) {
                fn_1_4D8();
                var_f31 = fn_1_32C(lbl_1_data_57C[arg0->unk_68 % 4][0] + (var_r28 * 10), lbl_1_data_57C[arg0->unk_68 % 4][0], var_r30, 5);
                HuSprPosSet(var_r29, arg0->unk_58 + 32, var_f31, lbl_1_data_57C[arg0->unk_68 / 4][1] + 35);
                HuSprPosSet(var_r29, arg0->unk_58 + 36, 1 + var_f31, lbl_1_data_57C[arg0->unk_68 / 4][1] + 37);
            }
        }
    }
    if (var_r27 == 1) {
        HuSprPosSet(var_r29, arg0->unk_58 + 49, lbl_1_data_57C[arg0->unk_68 % 4][0], lbl_1_data_57C[arg0->unk_68 / 4][1] + 35);
        HuSprBankSet(var_r29, arg0->unk_58 + 49, arg0->unk_64);
        HuSprAttrReset(var_r29, arg0->unk_58 + 49, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(var_r29, arg0->unk_58 + 32, HUSPR_ATTR_DISPOFF);
    }

    return var_r27;
}

void fn_1_16B68(omObjData *arg0, MentDllUnkBss3114Struct *arg1)
{
    s32 sp8;
    float var_f31;
    float var_f30;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r23;
    s32 var_r22;

    var_r27 = lbl_1_bss_35BC[0].unk_30;
    var_r26 = 0;
    var_r25 = 0;
    sp8 = arg1->unk_64;
    var_r23 = var_r30 = arg1->unk_68 % 4;
    var_r29 = arg1->unk_68 / 4;
    var_r22 = var_r29;
    if (arg1->unk_70[0] == 0) {
        if ((HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_A) != 0) {
            arg1->unk_70[0] = 1;
            HuSprBankSet(var_r27, arg1->unk_68, 1);
            HuSprBankSet(var_r27, arg1->unk_58 + 0x18, 1);
            HuSprBankSet(var_r27, arg1->unk_58 + 0x1C, 1);
            HuAudFXPlay(arg1->unk_68 + 0x6D);
            fn_1_162A0(arg1);
        }
        else {
            if ((HuPadStkX[lbl_1_bss_3114->unk_6C] >= 5) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 2) != 0)) {
                var_r30++;
                var_r26 = 1;
                if (var_r30 > 3) {
                    var_r30 = 3;
                }
            }
            else if ((HuPadStkX[lbl_1_bss_3114->unk_6C] <= -5) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 1) != 0)) {
                var_r30--;
                var_r26 = -1;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
            }
            if ((HuPadStkY[lbl_1_bss_3114->unk_6C] <= -5) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 4) != 0)) {
                var_r29++;
                var_r25 = 1;
                if (var_r29 > 1) {
                    var_r29 = 1;
                }
            }
            else if ((HuPadStkY[lbl_1_bss_3114->unk_6C] >= 5) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 8) != 0)) {
                var_r29--;
                var_r25 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
    }
    else if ((HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_B) != 0) {
        arg1->unk_70[0] = arg1->unk_70[2] = 0;
        HuSprBankSet(var_r27, arg1->unk_68, 0);
        HuSprBankSet(var_r27, arg1->unk_58 + 0x18, 0);
        HuSprBankSet(var_r27, arg1->unk_58 + 0x1C, 0);
        HuSprAttrSet(var_r27, arg1->unk_58 + 0x20, 4);
        HuSprAttrSet(var_r27, arg1->unk_58 + 0x24, 4);
        HuAudFXPlay(3);
    }
    if (arg1->unk_68 != (var_r30 + (var_r29 * 4))) {
        do {
            for (var_r28 = 0; var_r28 < 4; var_r28++) {
                if ((var_r28 != arg1->unk_58) && (lbl_1_bss_3114[var_r28].unk_70[0] == 1)
                    && ((var_r30 + (var_r29 * 4)) == lbl_1_bss_3114[var_r28].unk_68)) {
                    if ((var_r26 == 0) || (var_r25 == 0)) {
                        if (((var_r30 + var_r26) > 3) || ((var_r30 + var_r26) < 0)) {
                            var_r30 = var_r23;
                        }
                        else {
                            var_r30 += var_r26;
                        }
                        if (((var_r29 + var_r25) > 1) || ((var_r29 + var_r25) < 0)) {
                            var_r29 = var_r22;
                        }
                        else {
                            var_r29 += var_r25;
                        }
                    }
                    else if (((var_r30 + var_r26) <= 3) && ((var_r30 + var_r26) >= 0)) {
                        var_r30 += var_r26;
                    }
                    else if (((var_r29 + var_r25) <= 1) && ((var_r29 + var_r25) >= 0)) {
                        var_r29 += var_r25;
                    }
                    else {
                        var_r30 = var_r23;
                        var_r29 = var_r22;
                    }
                    break;
                }
            }
        } while (var_r28 != 4);
        if (arg1->unk_68 != (var_r30 + (var_r29 * 4))) {
            arg1->unk_68 = var_r30 + (var_r29 * 4);
            HuAudFXPlay(0);
            for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                fn_1_4D8();
                var_f31 = fn_1_32C(lbl_1_data_57C[var_r23][0], lbl_1_data_57C[var_r30][0], var_r28, 10.0f);
                var_f30 = fn_1_32C(lbl_1_data_57C[var_r22][1], lbl_1_data_57C[var_r29][1], var_r28, 10.0f);
                HuSprPosSet(var_r27, arg1->unk_58 + 0x18, var_f31, var_f30);
                HuSprPosSet(var_r27, arg1->unk_58 + 0x1C, var_f31, var_f30);
                HuSprPosSet(var_r27, arg1->unk_58 + 0x20, var_f31, 35.0f + var_f30);
                HuSprPosSet(var_r27, arg1->unk_58 + 0x24, 1.0f + var_f31, 37.0f + var_f30);
            }
        }
    }
    (void)var_r30;
}

void fn_1_173FC(MentDllUnkBss3114Struct *arg0)
{
    s32 var_r30;
    s32 var_r29;

    var_r30 = lbl_1_bss_35BC[0].unk_30;
    do {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if ((var_r29 != arg0->unk_58) && (lbl_1_bss_3114[var_r29].unk_70[0] == 1) && (arg0->unk_68 == lbl_1_bss_3114[var_r29].unk_68)) {
                arg0->unk_68++;
                break;
            }
        }
    } while (var_r29 != 4);
    arg0->unk_64 = 0;
    HuSprBankSet(var_r30, arg0->unk_68, 0);
    HuSprBankSet(var_r30, arg0->unk_58 + 0x18, 0);
    HuSprBankSet(var_r30, arg0->unk_58 + 0x1C, 0);
    HuSprBankSet(var_r30, arg0->unk_58 + 0x20, arg0->unk_64);
    HuSprBankSet(var_r30, arg0->unk_58 + 0x31, arg0->unk_64);
    HuSprPosSet(var_r30, arg0->unk_58 + 0x18, lbl_1_data_57C[arg0->unk_68 % 4][0], lbl_1_data_57C[arg0->unk_68 / 4][1]);
    HuSprPosSet(var_r30, arg0->unk_58 + 0x1C, lbl_1_data_57C[arg0->unk_68 % 4][0], lbl_1_data_57C[arg0->unk_68 / 4][1]);
    HuSprPosSet(var_r30, arg0->unk_58 + 0x20, lbl_1_data_57C[arg0->unk_68 % 4][0], lbl_1_data_57C[arg0->unk_68 / 4][1] + 0x23);
    HuSprPosSet(var_r30, arg0->unk_58 + 0x24, lbl_1_data_57C[arg0->unk_68 % 4][0] + 1, lbl_1_data_57C[arg0->unk_68 / 4][1] + 0x25);
    HuSprPosSet(var_r30, arg0->unk_58 + 0x31, lbl_1_data_57C[arg0->unk_68 % 4][0] + 1, lbl_1_data_57C[arg0->unk_68 / 4][1] + 0x25);
    arg0->unk_70[2] = 0;
    HuSprAttrReset(var_r30, arg0->unk_58 + 0x18, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(var_r30, arg0->unk_58 + 0x1C, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(var_r30, arg0->unk_58 + 0x20, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(var_r30, arg0->unk_58 + 0x24, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(var_r30, arg0->unk_58 + 0x31, HUSPR_ATTR_DISPOFF);
}

void fn_1_17914(MentDllUnkBss3114Struct *arg0)
{
    s32 var_r30;

    var_r30 = lbl_1_bss_35BC[0].unk_30;
    HuSprBankSet(var_r30, arg0->unk_68, 0);
    HuSprAttrSet(var_r30, arg0->unk_58 + 0x18, 4);
    HuSprAttrSet(var_r30, arg0->unk_58 + 0x1C, 4);
    HuSprAttrSet(var_r30, arg0->unk_58 + 0x20, 4);
    HuSprAttrSet(var_r30, arg0->unk_58 + 0x24, 4);
    HuSprAttrSet(var_r30, arg0->unk_58 + 0x31, 4);
}

void fn_1_179DC(void)
{
    MentDllUnkBss3114Struct *var_r31;
    s32 var_r29;
    s32 var_r30;

    var_r30 = lbl_1_bss_35BC[0].unk_34;
    for (var_r29 = 0; var_r29 < 0x11; var_r29++) {
        HuSprAttrSet(var_r30, var_r29, HUSPR_ATTR_DISPOFF);
    }
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        var_r31 = &lbl_1_bss_3114[var_r29];
        HuSprPosSet(var_r30, var_r31->unk_68, lbl_1_data_5BC[var_r31->unk_58][0], lbl_1_data_5BC[var_r31->unk_58][1]);
        HuSprAttrReset(var_r30, var_r31->unk_68, HUSPR_ATTR_DISPOFF);
        if (var_r31->unk_60 == 0) {
            HuSprBankSet(var_r30, var_r31->unk_58 + 8, var_r31->unk_58);
            HuSprPosSet(var_r30, var_r31->unk_58 + 8, lbl_1_data_5BC[var_r31->unk_58][0], lbl_1_data_5BC[var_r31->unk_58][1] + 0x19);
            HuSprAttrReset(var_r30, var_r31->unk_58 + 8, HUSPR_ATTR_DISPOFF);
        }
        else {
            HuSprBankSet(var_r30, var_r31->unk_58 + 0xC, var_r31->unk_64);
            HuSprPosSet(var_r30, var_r31->unk_58 + 0xC, lbl_1_data_5BC[var_r31->unk_58][0], lbl_1_data_5BC[var_r31->unk_58][1] + 0x19);
            HuSprAttrReset(var_r30, var_r31->unk_58 + 0xC, HUSPR_ATTR_DISPOFF);
        }
    }
    HuSprAttrReset(var_r30, 0x10, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(var_r30, 16.0f, -500.0f);
}

void fn_1_17CC8(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    MentDllUnkBss3114Struct *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    AnimData *var_r25;
    AnimData *var_r24;

    var_r26 = HuSprGrpCreate(0x11);
    arg0->unk_34 = var_r26;
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        var_r27 = HuSprCreate(HuSprAnimReadFile(var_r30 + DATA_MAKE_NUM(DATADIR_MENT, 0x31)), 0x3E8, 0);
        HuSprGrpMemberSet(var_r26, var_r30, var_r27);
    }
    var_r25 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3A));
    var_r24 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3B));
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r27 = HuSprCreate(var_r25, 0x3DE, 0);
        HuSprGrpMemberSet(var_r26, var_r30 + 8, var_r27);
        var_r27 = HuSprCreate(var_r24, 0x3DE, 0);
        HuSprGrpMemberSet(var_r26, var_r30 + 0xC, var_r27);
    }
    var_r27 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x30)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r26, 0x10, var_r27);
    HuSprTPLvlSet(var_r26, 0x10, 0.8f);
    HuSprPosSet(var_r26, 0x10, 96.0f, 32.0f);
    var_r29 = lbl_1_bss_35BC[0].unk_34;
    for (var_r28 = 0; var_r28 < 0x11; var_r28++) {
        HuSprAttrSet(var_r29, var_r28, HUSPR_ATTR_DISPOFF);
    }
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        var_r31 = &lbl_1_bss_3114[var_r28];
        HuSprPosSet(var_r29, var_r31->unk_68, lbl_1_data_5BC[var_r31->unk_58][0], lbl_1_data_5BC[var_r31->unk_58][1]);
        HuSprAttrReset(var_r29, var_r31->unk_68, HUSPR_ATTR_DISPOFF);
        if (var_r31->unk_60 == 0) {
            HuSprBankSet(var_r29, var_r31->unk_58 + 8, var_r31->unk_58);
            HuSprPosSet(var_r29, var_r31->unk_58 + 8, lbl_1_data_5BC[var_r31->unk_58][0], lbl_1_data_5BC[var_r31->unk_58][1] + 0x19);
            HuSprAttrReset(var_r29, var_r31->unk_58 + 8, HUSPR_ATTR_DISPOFF);
        }
        else {
            HuSprBankSet(var_r29, var_r31->unk_58 + 0xC, var_r31->unk_64);
            HuSprPosSet(var_r29, var_r31->unk_58 + 0xC, lbl_1_data_5BC[var_r31->unk_58][0], lbl_1_data_5BC[var_r31->unk_58][1] + 0x19);
            HuSprAttrReset(var_r29, var_r31->unk_58 + 0xC, HUSPR_ATTR_DISPOFF);
        }
    }
    HuSprAttrReset(var_r29, 0x10, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(var_r29, 16.0f, -500.0f);
}

void fn_1_1811C(void)
{
    float var_f31;
    MentDllUnkBss3114Struct *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r30 = lbl_1_bss_35BC[0].unk_34;
    for (var_r29 = 0; var_r29 < 0x11; var_r29++) {
        HuSprAttrSet(var_r30, var_r29, HUSPR_ATTR_DISPOFF);
    }
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        var_r31 = &lbl_1_bss_3114[var_r29];
        HuSprPosSet(var_r30, var_r31->unk_68, lbl_1_data_5BC[var_r31->unk_58][0], lbl_1_data_5BC[var_r31->unk_58][1]);
        HuSprAttrReset(var_r30, var_r31->unk_68, HUSPR_ATTR_DISPOFF);
        if (var_r31->unk_60 == 0) {
            HuSprBankSet(var_r30, var_r31->unk_58 + 8, var_r31->unk_58);
            HuSprPosSet(var_r30, var_r31->unk_58 + 8, lbl_1_data_5BC[var_r31->unk_58][0], lbl_1_data_5BC[var_r31->unk_58][1] + 0x19);
            HuSprAttrReset(var_r30, var_r31->unk_58 + 8, HUSPR_ATTR_DISPOFF);
        }
        else {
            HuSprBankSet(var_r30, var_r31->unk_58 + 0xC, var_r31->unk_64);
            HuSprPosSet(var_r30, var_r31->unk_58 + 0xC, lbl_1_data_5BC[var_r31->unk_58][0], lbl_1_data_5BC[var_r31->unk_58][1] + 0x19);
            HuSprAttrReset(var_r30, var_r31->unk_58 + 0xC, HUSPR_ATTR_DISPOFF);
        }
    }
    HuSprAttrReset(var_r30, 0x10, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(var_r30, 16.0f, -500.0f);
    for (var_r28 = 0; var_r28 <= 0x3C; var_r28++) {
        fn_1_4D8();
        if (var_r28 <= 0x32) {
            var_f31 = fn_1_32C(-500.0f, 50.0f, var_r28, 50.0f);
        }
        else {
            var_f31 = fn_1_254(50.0f, 40.0f, var_r28 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_34, 16.0f, var_f31);
    }
}

void fn_1_1850C(void)
{
    float var_f31;
    s32 var_r31;

    lbl_1_bss_35BC[0].unk_08[0] = -1;
    lbl_1_bss_35BC[0].unk_04 = NULL;
    for (var_r31 = 0; var_r31 <= 0x4B; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_32C(40.0f, 50.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_254(50.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_34, 16.0f, var_f31);
        if (var_r31 >= 0xF) {
            var_f31 = fn_1_254(210.0f, -500.0f, var_r31 - 0xF, 60.0f);
            HuSprGrpData[lbl_1_bss_35BC[0].unk_38].y = (s32)fn_1_234(HuSprGrpData[lbl_1_bss_35BC[0].unk_38].y, var_f31, 10.0f);
        }
    }
}

void fn_1_1872C(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_35BC[0].unk_38;
    for (var_r31 = 0; var_r31 < 7; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
}

void fn_1_18788(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r31 = HuSprGrpCreate(7);
    arg0->unk_38 = var_r31;
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3C)), 0x7DA, 0);
    HuSprGrpMemberSet(var_r31, 0, var_r30);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3D)), 0x7C6, 0);
    HuSprGrpMemberSet(var_r31, 1, var_r30);
    HuSprPosSet(var_r31, 1, 0.0f, -80.0f);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3E)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r31, 2, var_r30);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3F)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r31, 3, var_r30);
    HuSprPosSet(var_r31, 3, 0.0f, -80.0f);
    if (lbl_1_bss_A8[0] != 0) {
        var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x5A)), 0x7BC, 0);
        HuSprGrpMemberSet(var_r31, 4, var_r30);
        HuSprPosSet(var_r31, 4, -140.0f, -86.0f);
        var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x5B)), 0x7BC, 0);
        HuSprGrpMemberSet(var_r31, 5, var_r30);
        var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x5C)), 0x7D0, 0);
        HuSprGrpMemberSet(var_r31, 6, var_r30);
        HuSprScaleSet(var_r31, 6, 1.0f, 0.875f);
        HuSprTPLvlSet(var_r31, 6, 0.5f);
    }
    HuSprExecLayerSet(0x40, 1);
    HuSprGrpDrawNoSet(var_r31, 0x40);
    var_r28 = lbl_1_bss_35BC[0].unk_38;
    for (var_r29 = 0; var_r29 < 7; var_r29++) {
        HuSprAttrSet(var_r28, var_r29, 4);
    }
}

void fn_1_18A54(s32 arg0)
{
    float var_f31;
    float var_f30;
    s32 var_r31;

    var_r31 = lbl_1_bss_35BC[0].unk_38;
    if (arg0 != 5) {
        HuSprBankSet(var_r31, 0, arg0);
        HuSprBankSet(var_r31, 1, arg0);
        HuSprAttrSet(var_r31, 2, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(var_r31, 3, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r31, 0, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r31, 1, HUSPR_ATTR_DISPOFF);
        if (lbl_1_bss_A8[0] != 0) {
            if ((arg0 == 0 && _CheckFlag(FLAG_ID_MAKE(0, 2)) != 0) || (arg0 == 1 && _CheckFlag(FLAG_ID_MAKE(0, 3)) != 0)
                || (arg0 == 2 && _CheckFlag(FLAG_ID_MAKE(0, 4)) != 0) || (arg0 == 3 && (_CheckFlag(FLAG_ID_MAKE(0, 5)) != 0))
                || (arg0 == 4 && (_CheckFlag(FLAG_ID_MAKE(0, 6)) != 0))) {
                HuSprAttrReset(var_r31, 4, HUSPR_ATTR_DISPOFF);
                HuSprAttrReset(var_r31, 5, HUSPR_ATTR_DISPOFF);
                HuSprTPLvlSet(var_r31, 5, 0.8f);
                HuSprAttrReset(var_r31, 6, HUSPR_ATTR_DISPOFF);
                HuSprTPLvlSet(var_r31, 6, 0.5f);
            }
            else {
                HuSprAttrSet(var_r31, 4, 4);
                HuSprAttrSet(var_r31, 5, 4);
                HuSprAttrSet(var_r31, 6, 4);
            }
        }
    }
    else {
        HuSprAttrSet(var_r31, 0, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(var_r31, 1, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r31, 2, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r31, 3, HUSPR_ATTR_DISPOFF);
    }
    lbl_1_bss_35BC[0].unk_08[0] = arg0;
    lbl_1_bss_35BC[0].unk_1C[1] = (rand8() % 10) * 0x24;
    HuSprGrpScaleSet(var_r31, 0.0f, 0.0f);
    for (arg0 = 0; arg0 <= 0xF; arg0++) {
        fn_1_4D8();
        if (arg0 <= 0xA) {
            var_f31 = fn_1_32C(0.0f, 1.0f, arg0, 10.0f);
            var_f30 = 0.01f;
        }
        else {
            var_f31 = 1.0f;
            var_f30 = fn_1_32C(0.01f, 1.0f, arg0 - 0xA, 5.0f);
        }
        HuSprGrpScaleSet(var_r31, var_f31, var_f30);
    }
}

void fn_1_18DCC(void)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r29 = lbl_1_bss_35BC[0].unk_38;
    for (var_r31 = 0; var_r31 <= 0xF; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0xA) {
            var_f31 = 1.0f;
            var_f30 = fn_1_32C(1.0f, 0.01f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_32C(1.0f, 0.0f, var_r31 - 0xA, 5.0f);
            var_f30 = 0.01f;
        }
        HuSprGrpScaleSet(var_r29, var_f31, var_f30);
    }
    var_r28 = lbl_1_bss_35BC[0].unk_38;
    for (var_r30 = 0; var_r30 < 7; var_r30++) {
        HuSprAttrSet(var_r28, var_r30, 4);
    }
    lbl_1_bss_35BC[0].unk_08[0] = -1;
    lbl_1_bss_35BC[0].unk_04 = NULL;
}

void fn_1_18F74(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    Vec sp14;
    Vec sp8;
    s32 var_r31;

    var_r31 = lbl_1_bss_35BC[0].unk_38;
    if (lbl_1_bss_35BC[0].unk_08[0] != -1) {
        sp14.x = lbl_1_data_D8[lbl_1_bss_35BC[0].unk_08[0]].x;
        sp14.y = 0.0f;
        sp14.z = lbl_1_data_D8[lbl_1_bss_35BC[0].unk_08[0]].z;
        Hu3D3Dto2D(&sp14, 1, &sp8);
        sp8.y = fn_1_3F4(210.0f, 220.0f, lbl_1_bss_35BC[0].unk_1C[1]++, 360.0f);
        if (lbl_1_bss_35BC[0].unk_1C[1] >= 0x168) {
            lbl_1_bss_35BC[0].unk_1C[1] = 0;
        }
        HuSprGrpPosSet(var_r31, sp8.x, (s32)sp8.y);
    }
}

#if VERSION_PAL

#define POSX1 353
#define POSX2 325

#else

#define POSX1 321
#define POSX2 295

#endif

void fn_1_190E8(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_35BC[0].unk_3C;
    for (var_r31 = 0; var_r31 < 0x5B; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, HUSPR_ATTR_DISPOFF);
    }
    if (lbl_1_bss_A8[2] != 5) {
        HuSprBankSet(var_r30, 0, lbl_1_bss_A8[2]);
        HuSprAttrReset(var_r30, 0, HUSPR_ATTR_DISPOFF);
    }
    else {
        HuSprAttrReset(var_r30, 1, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(var_r30, 2, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(var_r30, 2, 288.0f, lbl_1_data_5DC[0][1]);
    HuSprScaleSet(var_r30, 2, 1.0f, lbl_1_data_5DC[0][2]);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 3, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(var_r30, var_r31 + 3, lbl_1_data_5DC[0][var_r31 + 3], lbl_1_data_5DC[0][1]);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprAttrReset(var_r30, lbl_1_bss_3114[var_r31].unk_68 + 7, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(var_r30, lbl_1_bss_3114[var_r31].unk_68 + 7, lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], lbl_1_data_5DC[0][1]);
        HuSprAttrReset(var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0xF, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(
            var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0xF, 1.0f + lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], 2.0f + lbl_1_data_5DC[0][1]);
        HuSprAttrReset(var_r30, lbl_1_bss_3114[var_r31].unk_68 + 0x1F, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(var_r30, lbl_1_bss_3114[var_r31].unk_68 + 0x1F, lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], lbl_1_data_5DC[4][1] - 9.0f);
        HuSprAttrReset(var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0x27, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(
            var_r30, lbl_1_bss_3114[var_r31].unk_58 + 0x27, 1.0f + lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], lbl_1_data_5DC[4][1] - 7.0f);
        if (lbl_1_bss_3114[var_r31].unk_60 != 0) {
            HuSprAttrReset(var_r30, var_r31 + 0x1B, HUSPR_ATTR_DISPOFF);
            HuSprBankSet(var_r30, var_r31 + 0x1B, lbl_1_bss_3114[var_r31].unk_64);
            HuSprPosSet(var_r30, var_r31 + 0x1B, lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], 21.0f + lbl_1_data_5DC[0][1]);
        }
        else {
            HuSprAttrReset(var_r30, var_r31 + 0x17, HUSPR_ATTR_DISPOFF);
            HuSprBankSet(var_r30, var_r31 + 0x17, lbl_1_bss_3114[var_r31].unk_58);
            HuSprPosSet(var_r30, var_r31 + 0x17, lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0] - 8.0f, lbl_1_data_5DC[0][1] - 21.0f);
        }
        HuSprPosSet(var_r30, var_r31 + 0x2F, lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], 20.0f + lbl_1_data_5DC[4][1]);
        HuSprAttrReset(var_r30, var_r31 + 0x2F, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(var_r30, var_r31 + 0x33, 10.0f + lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], 21.0f + lbl_1_data_5DC[4][1]);
        HuSprAttrReset(var_r30, var_r31 + 0x33, HUSPR_ATTR_DISPOFF);
        HuSprBankSet(var_r30, var_r31 + 0x33, 0);
        HuSprPosSet(var_r30, lbl_1_bss_3114[var_r31].unk_68 + 0x37, lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], lbl_1_data_5DC[4][1] - 7.0f);
        HuSprPosSet(var_r30, var_r31 + 0x3F, lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], 23.0f + lbl_1_data_5DC[4][1]);
        HuSprPosSet(var_r30, var_r31 + 0x43, 14.0f + lbl_1_data_5DC[lbl_1_bss_3114[var_r31].unk_58][0], 24.0f + lbl_1_data_5DC[4][1]);
        HuSprBankSet(var_r30, var_r31 + 0x43, 0);
    }
    HuSprPosSet(var_r30, 0x47, 340.0f, lbl_1_data_5DC[0][1]);
    HuSprScaleSet(var_r30, 0x47, 0.0f, 0.0f);
    HuSprAttrReset(var_r30, 0x47, HUSPR_ATTR_DISPOFF);
    #if VERSION_NTSC
    HuSprAttrReset(var_r30, 0x48, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(var_r30, 0x48, 366.0f, lbl_1_data_5DC[1][1]);
    HuSprAttrReset(var_r30, 0x49, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(var_r30, 0x49, 367.0f, 2.0f + lbl_1_data_5DC[1][1]);
    #endif
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 0x4A, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(var_r30, var_r31 + 0x4A, POSX1 - (var_r31 * (POSX1-POSX2)), lbl_1_data_5DC[1][1]);
        HuSprBankSet(var_r30, var_r31 + 0x4A, var_r31);
        HuSprAttrReset(var_r30, var_r31 + 0x4C, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(var_r30, var_r31 + 0x4C, POSX1+1 - (var_r31 * (POSX1-POSX2)), 2.0f + lbl_1_data_5DC[1][1]);
        HuSprBankSet(var_r30, var_r31 + 0x4C, var_r31);
    }
    HuSprAttrReset(var_r30, 0x4E, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(var_r30, 0x4E, 340.0f, lbl_1_data_5DC[2][1]);
    HuSprBankSet(var_r30, 0x4E, 0);
    HuSprAttrReset(var_r30, 0x4F, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(var_r30, 0x4F, 341.0f, 2.0f + lbl_1_data_5DC[2][1]);
    HuSprBankSet(var_r30, 0x4F, 0);
    HuSprAttrReset(var_r30, 0x50, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(var_r30, 0x50, 340.0f, lbl_1_data_5DC[3][1]);
    HuSprBankSet(var_r30, 0x50, 0);
    HuSprAttrReset(var_r30, 0x51, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(var_r30, 0x51, 341.0f, 2.0f + lbl_1_data_5DC[3][1]);
    HuSprBankSet(var_r30, 0x51, 0);
    HuSprAttrReset(var_r30, 0x52, HUSPR_ATTR_DISPOFF);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 0x53, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r30, var_r31 + 0x57, HUSPR_ATTR_DISPOFF);
    }
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        HuWinPosSet(lbl_1_bss_35BC[0].unk_44[var_r31], 100.0f, -500.0f + (lbl_1_data_5DC[var_r31][1] - 21.0f));
    }
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_35BC[1].unk_08[var_r31] = lbl_1_bss_35BC[1].unk_1C[var_r31] = 0;
    }
    lbl_1_bss_35BC[1].unk_1C[1] = 0x14;
    HuSprBankSet(var_r30, 0x4A, 0);
    HuSprBankSet(var_r30, 0x4C, 0);
    HuSprBankSet(var_r30, 0x4B, 2);
    HuSprBankSet(var_r30, 0x4D, 2);
    HuSprGrpPosSet(var_r30, 0.0f, -500.0f);
}

void fn_1_19C98(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    float sp8[2];
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r26 = 0;
    var_r30 = lbl_1_bss_35BC[0].unk_3C;
    {
        s32 sp10[4][4] = {
            { 0x106, 0x106, 0x106, 0x106 },
            { 0x13A, 0x133, 0x175, 0x175 },
            { 0x16E, 0x175, 0x133, 0x1A2 },
            { 0x1A2, 0x1A2, 0x1A2, 0x133 },
        };
        lbl_1_bss_35BC[0].unk_08[3] = 0;
        var_r27 = arg1->unk_08[0];
        sp8[0] = HuSprData[HuSprGrpData[var_r30].members[3]].x;
        sp8[1] = HuSprData[HuSprGrpData[var_r30].members[4]].x;
        if ((HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_A) != 0) {
            arg1->unk_08[0]++;
            HuAudFXPlay(2);
            if (arg1->unk_08[0] > 4) {
                lbl_1_bss_35BC[0].unk_08[1] = 1;
                arg1->unk_08[0] = 4;
                fn_1_1C674();
            }
            lbl_1_bss_35BC[0].unk_08[3] = 1;
        }
        else if ((HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_B) != 0) {
            arg1->unk_08[0]--;
            HuAudFXPlay(3);
            if (arg1->unk_08[0] < 0) {
                lbl_1_bss_35BC[0].unk_08[1] = -1;
                arg1->unk_08[0] = 0;
                fn_1_1C674();
            }
            lbl_1_bss_35BC[0].unk_08[3] = 1;
        }
        else if ((HuPadStkX[lbl_1_bss_3114->unk_6C] >= 5) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_RIGHT) != 0)) {
            var_r26 = 1;
            lbl_1_bss_35BC[0].unk_08[3] = 1;
            HuAudFXPlay(0);
            switch (arg1->unk_08[0]) {
                case 0:
                    arg1->unk_1C[0] += 1;
                    if (arg1->unk_1C[0] > 3) {
                        arg1->unk_1C[0] = 0;
                    }
                    break;
                case 1:
                    arg1->unk_1C[1] += 5;
                    if (arg1->unk_1C[1] > 0x32) {
                        arg1->unk_1C[1] = 0xA;
                    }
                    break;
                case 2:
                    if (lbl_1_bss_A8[6] == 1) {
                        arg1->unk_1C[2]++;
                        if (arg1->unk_1C[2] > 2) {
                            arg1->unk_1C[2] = 0;
                        }
                    }
                    else {
                        arg1->unk_1C[2]++;
                        if (arg1->unk_1C[2] > 1) {
                            arg1->unk_1C[2] = 0;
                        }
                    }
                    break;
                case 3:
                    arg1->unk_1C[3]++;
                    if (arg1->unk_1C[3] > 1) {
                        arg1->unk_1C[3] = 0;
                    }
                    break;
                case 4:
                    arg1->unk_1C[4] += 1;
                    if (arg1->unk_1C[4] > 3) {
                        arg1->unk_1C[4] = 0;
                    }
                    break;
            }
        }
        else if ((HuPadStkX[lbl_1_bss_3114->unk_6C] <= -5) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_LEFT) != 0)) {
            var_r26 = -1;
            lbl_1_bss_35BC[0].unk_08[3] = 1;
            HuAudFXPlay(0);
            switch (arg1->unk_08[0]) {
                case 0:
                    arg1->unk_1C[0] -= 1;
                    if (arg1->unk_1C[0] < 0) {
                        arg1->unk_1C[0] = 3;
                    }
                    break;
                case 1:
                    arg1->unk_1C[1] -= 5;
                    if (arg1->unk_1C[1] < 0xA) {
                        arg1->unk_1C[1] = 0x32;
                    }
                    break;
                case 2:
                    if (lbl_1_bss_A8[6] == 1) {
                        arg1->unk_1C[2]--;
                        if (arg1->unk_1C[2] < 0) {
                            arg1->unk_1C[2] = 2;
                        }
                    }
                    else {
                        arg1->unk_1C[2]--;
                        if (arg1->unk_1C[2] < 0) {
                            arg1->unk_1C[2] = 1;
                        }
                    }
                    break;
                case 3:
                    arg1->unk_1C[3]--;
                    if (arg1->unk_1C[3] < 0) {
                        arg1->unk_1C[3] = 1;
                    }
                    break;
                case 4:
                    arg1->unk_1C[4] -= 1;
                    if (arg1->unk_1C[4] < 0) {
                        arg1->unk_1C[4] = 3;
                    }
                    break;
            }
        }
        else if (arg1->unk_08[0] == 4) {
            if ((HuPadStkY[lbl_1_bss_3114->unk_6C] >= 0x1E) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_UP) != 0)) {
                lbl_1_bss_35BC[0].unk_08[3] = 1;
                HuAudFXPlay(0);
                for (var_r29 = 0; var_r29 <= 0xA; var_r29++) {
                    fn_1_4D8();
                    if (var_r29 <= 5) {
                        var_f29 = fn_1_32C(0.0f, 10.0f, var_r29, 5.0f);
                    }
                    else {
                        var_f29 = fn_1_32C(10.0f, 0.0f, var_r29 - 5, 5.0f);
                    }
                    HuSprPosSet(var_r30, 5, lbl_1_data_5DC[arg1->unk_1C[4]][0], (lbl_1_data_5DC[4][1] - 48.0f) - var_f29);
                    if (var_r29 == 3) {
                        arg1->unk_08[arg1->unk_1C[4] + 1]--;
                        if (arg1->unk_08[arg1->unk_1C[4] + 1] < 0) {
                            arg1->unk_08[arg1->unk_1C[4] + 1] = 9;
                        }
                        HuSprBankSet(var_r30, arg1->unk_1C[4] + 0x33, arg1->unk_08[arg1->unk_1C[4] + 1]);
                        HuSprBankSet(var_r30, arg1->unk_1C[4] + 0x43, arg1->unk_08[arg1->unk_1C[4] + 1]);
                    }
                }
            }
            else if ((HuPadStkY[lbl_1_bss_3114->unk_6C] <= -0x1E) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 4) != 0)) {
                lbl_1_bss_35BC[0].unk_08[3] = 1;
                HuAudFXPlay(0);
                for (var_r29 = 0; var_r29 <= 0xA; var_r29++) {
                    fn_1_4D8();
                    if (var_r29 <= 5) {
                        var_f29 = fn_1_32C(0.0f, 10.0f, var_r29, 5.0f);
                    }
                    else {
                        var_f29 = fn_1_32C(10.0f, 0.0f, var_r29 - 5, 5.0f);
                    }
                    HuSprPosSet(var_r30, 6, lbl_1_data_5DC[arg1->unk_1C[4]][0], 49.0f + lbl_1_data_5DC[4][1] + var_f29);
                    if (var_r29 == 3) {
                        arg1->unk_08[arg1->unk_1C[4] + 1]++;
                        if (arg1->unk_08[arg1->unk_1C[4] + 1] > 9) {
                            arg1->unk_08[arg1->unk_1C[4] + 1] = 0;
                        }
                        HuSprBankSet(var_r30, arg1->unk_1C[4] + 0x33, arg1->unk_08[arg1->unk_1C[4] + 1]);
                        HuSprBankSet(var_r30, arg1->unk_1C[4] + 0x43, arg1->unk_08[arg1->unk_1C[4] + 1]);
                    }
                }
            }
        }
        if (var_r26 != 0) {
            for (var_r29 = 0; var_r29 <= 0xA; var_r29++) {
                fn_1_4D8();
                if (var_r29 <= 5) {
                    var_f31 = fn_1_32C(0.0f, 10.0f, var_r29, 5.0f);
                    var_f30 = fn_1_32C(1.0f, 0.0f, var_r29, 5.0f);
                }
                else {
                    var_f31 = fn_1_32C(10.0f, 0.0f, var_r29 - 5, 5.0f);
                    var_f30 = fn_1_32C(0.0f, 1.0f, var_r29 - 5, 5.0f);
                }
                if (arg1->unk_08[0] != 4) {
                    if (var_r26 == 1) {
                        HuSprPosSet(var_r30, 4, var_f31 + lbl_1_data_5DC[arg1->unk_08[0]][4], lbl_1_data_5DC[arg1->unk_08[0]][1]);
                    }
                    else {
                        HuSprPosSet(var_r30, 3, lbl_1_data_5DC[arg1->unk_08[0]][3] - var_f31, lbl_1_data_5DC[arg1->unk_08[0]][1]);
                    }
                }
                switch (arg1->unk_08[0]) {
                    case 0:
                        var_r27 = arg1->unk_1C[0] - var_r26;
                        if (var_r27 > 3) {
                            var_r27 = 0;
                        }
                        else if (var_r27 < 0) {
                            var_r27 = 3;
                        }
                        if (arg1->unk_1C[0] != 0) {
                            var_f30 = fn_1_32C(0.0f, 1.0f, var_r29, 10.0f);
                        }
                        else {
                            var_f30 = fn_1_32C(1.0f, 0.0f, var_r29, 10.0f);
                        }
                        HuSprScaleSet(var_r30, 0x47, var_f30, var_f30);
                        for (var_r28 = 0; var_r28 < 4; var_r28++) {
                            var_f31 = fn_1_32C(
                                sp10[lbl_1_bss_3114[var_r28].unk_58][var_r27], sp10[lbl_1_bss_3114[var_r28].unk_58][arg1->unk_1C[0]], var_r29, 10.0f);
                            HuSprPosSet(var_r30, lbl_1_bss_3114[var_r28].unk_68 + 7, var_f31, lbl_1_data_5DC[0][1]);
                            HuSprPosSet(var_r30, lbl_1_bss_3114[var_r28].unk_68 + 0xF, 1.0f + var_f31, 2.0f + lbl_1_data_5DC[0][1]);
                            if (lbl_1_bss_3114[var_r28].unk_60 != 0) {
                                HuSprPosSet(var_r30, var_r28 + 0x1B, var_f31, 21.0f + lbl_1_data_5DC[0][1]);
                            }
                            else {
                                HuSprPosSet(var_r30, var_r28 + 0x17, var_f31 - 8.0f, lbl_1_data_5DC[0][1] - 21.0f);
                            }
                        }
                        break;
                    case 1:
                        if (var_r26 == 1) {
                            #if VERSION_NTSC
                            HuSprPosSet(var_r30, 0x48, 366.0f + var_f31, lbl_1_data_5DC[1][1]);
                            HuSprPosSet(var_r30, 0x49, 367.0f + var_f31, 2.0f + lbl_1_data_5DC[1][1]);
                            #endif
                            HuSprPosSet(var_r30, 0x4A, POSX1 + var_f31, lbl_1_data_5DC[1][1]);
                            HuSprPosSet(var_r30, 0x4C, POSX1+1 + var_f31, 2.0f + lbl_1_data_5DC[1][1]);
                            HuSprPosSet(var_r30, 0x4B, POSX2 + var_f31, lbl_1_data_5DC[1][1]);
                            HuSprPosSet(var_r30, 0x4D, POSX2+1 + var_f31, 2.0f + lbl_1_data_5DC[1][1]);
                        }
                        else {
                            #if VERSION_NTSC
                            HuSprPosSet(var_r30, 0x48, 366.0f - var_f31, lbl_1_data_5DC[1][1]);
                            HuSprPosSet(var_r30, 0x49, 367.0f - var_f31, 2.0f + lbl_1_data_5DC[1][1]);
                            #endif
                            HuSprPosSet(var_r30, 0x4A, POSX1 - var_f31, lbl_1_data_5DC[1][1]);
                            HuSprPosSet(var_r30, 0x4C, POSX1+1 - var_f31, 2.0f + lbl_1_data_5DC[1][1]);
                            HuSprPosSet(var_r30, 0x4B, POSX2 - var_f31, lbl_1_data_5DC[1][1]);
                            HuSprPosSet(var_r30, 0x4D, POSX2+1 - var_f31, 2.0f + lbl_1_data_5DC[1][1]);
                        }
                        #if VERSION_NTSC
                        HuSprScaleSet(var_r30, 0x48, 1.0f, var_f30);
                        HuSprScaleSet(var_r30, 0x49, 1.0f, var_f30);
                        #endif
                        HuSprScaleSet(var_r30, 0x4A, 1.0f, var_f30);
                        HuSprScaleSet(var_r30, 0x4C, 1.0f, var_f30);
                        HuSprScaleSet(var_r30, 0x4B, 1.0f, var_f30);
                        HuSprScaleSet(var_r30, 0x4D, 1.0f, var_f30);
                        break;
                    case 2:
                        if (var_r26 == 1) {
                            HuSprPosSet(var_r30, 0x4E, 340.0f + var_f31, lbl_1_data_5DC[2][1]);
                            HuSprPosSet(var_r30, 0x4F, 341.0f + var_f31, 2.0f + lbl_1_data_5DC[2][1]);
                        }
                        else {
                            HuSprPosSet(var_r30, 0x4E, 340.0f - var_f31, lbl_1_data_5DC[2][1]);
                            HuSprPosSet(var_r30, 0x4F, 341.0f - var_f31, 2.0f + lbl_1_data_5DC[2][1]);
                        }
                        HuSprScaleSet(var_r30, 0x4E, 1.0f, var_f30);
                        HuSprScaleSet(var_r30, 0x4F, 1.0f, var_f30);
                        break;
                    case 3:
                        if (var_r26 == 1) {
                            HuSprPosSet(var_r30, 0x50, 340.0f + var_f31, lbl_1_data_5DC[3][1]);
                            HuSprPosSet(var_r30, 0x51, 341.0f + var_f31, 2.0f + lbl_1_data_5DC[3][1]);
                        }
                        else {
                            HuSprPosSet(var_r30, 0x50, 340.0f - var_f31, lbl_1_data_5DC[3][1]);
                            HuSprPosSet(var_r30, 0x51, 341.0f - var_f31, 2.0f + lbl_1_data_5DC[3][1]);
                        }
                        HuSprScaleSet(var_r30, 0x50, 1.0f, var_f30);
                        HuSprScaleSet(var_r30, 0x51, 1.0f, var_f30);
                        break;
                    case 4:
                        var_f31 = fn_1_32C(sp8[0], lbl_1_data_5DC[arg1->unk_1C[4]][0] - 32.0f, var_r29, 10.0f);
                        HuSprPosSet(var_r30, 3, var_f31, lbl_1_data_5DC[4][1]);
                        var_f31 = fn_1_32C(sp8[1], 33.0f + lbl_1_data_5DC[arg1->unk_1C[4]][0], var_r29, 10.0f);
                        HuSprPosSet(var_r30, 4, var_f31, lbl_1_data_5DC[4][1]);
                        var_f31 = fn_1_32C(32.0f + sp8[0], lbl_1_data_5DC[arg1->unk_1C[4]][0], var_r29, 10.0f);
                        HuSprPosSet(var_r30, 5, var_f31, lbl_1_data_5DC[4][1] - 48.0f);
                        HuSprPosSet(var_r30, 6, var_f31, 49.0f + lbl_1_data_5DC[4][1]);
                        if (var_r29 == 3) {
                            for (var_r28 = 0; var_r28 < 4; var_r28++) {
                                HuSprAttrSet(var_r30, lbl_1_bss_3114[var_r28].unk_68 + 0x37, HUSPR_ATTR_DISPOFF);
                                HuSprAttrSet(var_r30, var_r28 + 0x3F, HUSPR_ATTR_DISPOFF);
                                HuSprAttrSet(var_r30, var_r28 + 0x43, HUSPR_ATTR_DISPOFF);
                            }
                            HuSprAttrReset(var_r30, lbl_1_bss_3114[arg1->unk_1C[4]].unk_68 + 0x37, HUSPR_ATTR_DISPOFF);
                            HuSprAttrReset(var_r30, arg1->unk_1C[4] + 0x3F, HUSPR_ATTR_DISPOFF);
                            HuSprAttrReset(var_r30, arg1->unk_1C[4] + 0x43, HUSPR_ATTR_DISPOFF);
                        }
                        break;
                }
                if (var_r29 == 6) {
                    switch (arg1->unk_08[0]) {
                        case 1:
                            HuSprBankSet(var_r30, 0x4A, arg1->unk_1C[1] % 10);
                            HuSprBankSet(var_r30, 0x4C, arg1->unk_1C[1] % 10);
                            HuSprBankSet(var_r30, 0x4B, arg1->unk_1C[1] / 10);
                            HuSprBankSet(var_r30, 0x4D, arg1->unk_1C[1] / 10);
                            break;
                        case 2:
                            HuSprBankSet(var_r30, 0x4E, arg1->unk_1C[2]);
                            HuSprBankSet(var_r30, 0x4F, arg1->unk_1C[2]);
                            break;
                        case 3:
                            HuSprBankSet(var_r30, 0x50, arg1->unk_1C[3]);
                            HuSprBankSet(var_r30, 0x51, arg1->unk_1C[3]);
                            break;
                    }
                }
            }
        }
        else if (var_r27 != arg1->unk_08[0]) {
            for (var_r29 = 0; var_r29 <= 0xA; var_r29++) {
                fn_1_4D8();
                var_f29 = fn_1_32C(lbl_1_data_5DC[var_r27][1], lbl_1_data_5DC[arg1->unk_08[0]][1], var_r29, 10.0f);
                var_f30 = fn_1_32C(lbl_1_data_5DC[var_r27][2], lbl_1_data_5DC[arg1->unk_08[0]][2], var_r29, 10.0f);
                HuSprPosSet(var_r30, 2, 288.0f, var_f29);
                HuSprScaleSet(var_r30, 2, 1.0f, var_f30);
                if (arg1->unk_08[0] != 4) {
                    var_f31 = fn_1_32C(sp8[0], lbl_1_data_5DC[arg1->unk_08[0]][3], var_r29, 10.0f);
                    HuSprPosSet(var_r30, 3, var_f31, var_f29);
                    var_f31 = fn_1_32C(sp8[1], lbl_1_data_5DC[arg1->unk_08[0]][4], var_r29, 10.0f);
                    HuSprPosSet(var_r30, 4, var_f31, var_f29);
                    var_f30 = fn_1_32C(1.0f, 0.0f, var_r29, 10.0f);
                    HuSprTPLvlSet(var_r30, 5, var_f30);
                    HuSprTPLvlSet(var_r30, 6, var_f30);
                    var_f29 = fn_1_32C(0.0f, 20.0f, var_r29, 10.0f);
                    HuSprPosSet(var_r30, 5, lbl_1_data_5DC[arg1->unk_1C[4]][0], (lbl_1_data_5DC[4][1] - var_f29) - 48.0f);
                    HuSprPosSet(var_r30, 6, lbl_1_data_5DC[arg1->unk_1C[4]][0], 49.0f + (lbl_1_data_5DC[4][1] + var_f29));
                    for (var_r28 = 0; var_r28 < 4; var_r28++) {
                        HuSprAttrSet(var_r30, lbl_1_bss_3114[var_r28].unk_68 + 0x37, HUSPR_ATTR_DISPOFF);
                        HuSprAttrSet(var_r30, var_r28 + 0x3F, HUSPR_ATTR_DISPOFF);
                        HuSprAttrSet(var_r30, var_r28 + 0x43, HUSPR_ATTR_DISPOFF);
                    }
                }
                else {
                    var_f31 = fn_1_32C(sp8[0], lbl_1_data_5DC[arg1->unk_1C[4]][0] - 32.0f, var_r29, 10.0f);
                    HuSprPosSet(var_r30, 3, var_f31, var_f29);
                    var_f31 = fn_1_32C(sp8[1], 33.0f + lbl_1_data_5DC[arg1->unk_1C[4]][0], var_r29, 10.0f);
                    HuSprPosSet(var_r30, 4, var_f31, var_f29);
                    HuSprAttrReset(var_r30, 5, HUSPR_ATTR_DISPOFF);
                    HuSprAttrReset(var_r30, 6, HUSPR_ATTR_DISPOFF);
                    var_f30 = fn_1_32C(0.0f, 1.0f, var_r29, 10.0f);
                    HuSprTPLvlSet(var_r30, 5, var_f30);
                    HuSprTPLvlSet(var_r30, 6, var_f30);
                    var_f29 = fn_1_32C(20.0f, 0.0f, var_r29, 10.0f);
                    HuSprPosSet(var_r30, 5, lbl_1_data_5DC[arg1->unk_1C[4]][0], (lbl_1_data_5DC[4][1] - var_f29) - 48.0f);
                    HuSprPosSet(var_r30, 6, lbl_1_data_5DC[arg1->unk_1C[4]][0], 49.0f + (lbl_1_data_5DC[4][1] + var_f29));
                    if (var_r29 == 3) {
                        HuSprAttrReset(var_r30, lbl_1_bss_3114[arg1->unk_1C[4]].unk_68 + 0x37, HUSPR_ATTR_DISPOFF);
                        HuSprAttrReset(var_r30, arg1->unk_1C[4] + 0x3F, HUSPR_ATTR_DISPOFF);
                        HuSprAttrReset(var_r30, arg1->unk_1C[4] + 0x43, HUSPR_ATTR_DISPOFF);
                    }
                }
            }
            if (arg1->unk_08[0] != 4) {
                HuSprAttrSet(var_r30, 5, HUSPR_ATTR_DISPOFF);
                HuSprAttrSet(var_r30, 6, HUSPR_ATTR_DISPOFF);
            }
        }
        lbl_1_bss_35BC[0].unk_08[3] = 0;
    }
}

#undef POSX2
#undef POSX1

void fn_1_1BB2C(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r28;
    AnimData *var_r26;
    AnimData *var_r25;

    s32 sp8[4][2] = {
        { 0x00000070, 0x00000060 },
        { 0x000001D2, 0x00000060 },
        { 0x00000070, 0x0000012D },
        { 0x000001D2, 0x0000012D },
    };
    var_r29 = HuSprGrpCreate(0x5B);
    arg0->unk_3C = var_r29;
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3D)), 0x7C6, 0);
    HuSprGrpMemberSet(var_r29, 0, var_r30);
    HuSprPosSet(var_r29, 0, 288.0f, 54.0f);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3F)), 0x7C6, 0);
    HuSprGrpMemberSet(var_r29, 1, var_r30);
    HuSprPosSet(var_r29, 1, 288.0f, 54.0f);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x41)), 0x7BC, 0);
    HuSprGrpMemberSet(var_r29, 2, var_r30);
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x42));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 3, var_r30);
        HuSprBankSet(var_r29, var_r31 + 3, var_r31);
    }
    var_r25 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x39));
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        var_r28 = HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MENT, 0x31));
        var_r26 = HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MENT, 0x4E));
        var_r30 = HuSprCreate(var_r28, 0x3E8, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 7, var_r30);
        var_r30 = HuSprCreate(var_r25, 0x3F2, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0xF, var_r30);
        var_r30 = HuSprCreate(var_r28, 0x3E8, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x1F, var_r30);
        var_r30 = HuSprCreate(var_r25, 0x3F2, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x27, var_r30);
        var_r30 = HuSprCreate(var_r26, 0x3DE, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x37, var_r30);
    }
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3A));
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x3B));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x3DE, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x17, var_r30);
        var_r30 = HuSprCreate(var_r26, 0x3DE, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x1B, var_r30);
    }
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x43)), 0x3DE, 0);
    HuSprGrpMemberSet(var_r29, 0x47, var_r30);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x44)), 0x3E8, 0);
    HuSprGrpMemberSet(var_r29, 0x48, var_r30);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x46)), 0x3F2, 0);
    HuSprGrpMemberSet(var_r29, 0x49, var_r30);
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x45));
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x47));
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x3E8, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x4A, var_r30);
        var_r30 = HuSprCreate(var_r26, 0x3F2, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x4C, var_r30);
    }
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x48)), 0x3E8, 0);
    HuSprGrpMemberSet(var_r29, 0x4E, var_r30);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x49)), 0x3F2, 0);
    HuSprGrpMemberSet(var_r29, 0x4F, var_r30);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x4A)), 0x3E8, 0);
    HuSprGrpMemberSet(var_r29, 0x50, var_r30);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x4B)), 0x3F2, 0);
    HuSprGrpMemberSet(var_r29, 0x51, var_r30);
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x4C));
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x4D));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x3DE, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x2F, var_r30);
        var_r30 = HuSprCreate(var_r26, 0x3D4, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x33, var_r30);
    }
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x56));
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x57));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x3CA, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x3F, var_r30);
        var_r30 = HuSprCreate(var_r26, 0x3C0, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x43, var_r30);
    }
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x40)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r29, 0x52, var_r30);
    HuSprTPLvlSet(var_r29, 0x52, 0.8f);
    fn_1_6534(var_r29, 0x52, 288.0f, 240.0f);
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x18));
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x19));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x7BC, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x53, var_r30);
        HuSprBankSet(var_r29, var_r31 + 0x53, var_r31);
        fn_1_6534(var_r29, var_r31 + 0x53, sp8[var_r31][0], sp8[var_r31][1]);
        var_r30 = HuSprCreate(var_r26, 0x7C6, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x57, var_r30);
        HuSprBankSet(var_r29, var_r31 + 0x57, var_r31);
        HuSprTPLvlSet(var_r29, var_r31 + 0x57, 0.5f);
        fn_1_6534(var_r29, var_r31 + 0x57, sp8[var_r31][0] + 1, sp8[var_r31][1] + 6);
    }
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        arg0->unk_44[var_r31] = HuWinExCreateStyled(0.0f, 0.0f, 0xC8, 0xC8, -1, 1);
        HuWinBGTPLvlSet(arg0->unk_44[var_r31], 0.0f);
        HuWinMesSet(arg0->unk_44[var_r31], var_r31 + 0x1B0010);
        HuWinMesSpeedSet(arg0->unk_44[var_r31], 0);
        HuWinDispOn(arg0->unk_44[var_r31]);
        winData[arg0->unk_44[var_r31]].mess_shadow_color = 0;
    }
    fn_1_190E8();
}

void fn_1_1C554(void)
{
    s32 var_r31;
    s32 var_r30;
    MentDllUnkBss35BCStruct *var_r29;

    var_r30 = lbl_1_bss_35BC[0].unk_3C;
    var_r29 = &lbl_1_bss_35BC[1];
    HuSprAttrReset(var_r30, 2, HUSPR_ATTR_DISPOFF);
    if (lbl_1_bss_35BC[1].unk_08[0] == 4) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            HuSprAttrReset(var_r30, var_r31 + 3, HUSPR_ATTR_DISPOFF);
        }
        HuSprAttrReset(var_r30, lbl_1_bss_3114[var_r29->unk_1C[4]].unk_68 + 0x37, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r30, var_r29->unk_1C[4] + 0x3F, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r30, var_r29->unk_1C[4] + 0x43, HUSPR_ATTR_DISPOFF);
        return;
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 3, HUSPR_ATTR_DISPOFF);
    }
}

void fn_1_1C674(void)
{
    MentDllUnkBss35BCStruct *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = lbl_1_bss_35BC[0].unk_3C;
    var_r31 = &lbl_1_bss_35BC[1];
    HuSprAttrSet(var_r30, 2, HUSPR_ATTR_DISPOFF);
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        HuSprAttrSet(var_r30, var_r29 + 3, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrSet(var_r30, lbl_1_bss_3114[var_r31->unk_1C[4]].unk_68 + 0x37, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(var_r30, var_r31->unk_1C[4] + 0x3F, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(var_r30, var_r31->unk_1C[4] + 0x43, HUSPR_ATTR_DISPOFF);
}

void fn_1_1C754(void)
{
    float var_f31;
    s32 var_r31;
    MentDllUnkBss35BCStruct *var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    fn_1_190E8();
    var_r28 = lbl_1_bss_35BC[0].unk_3C;
    var_r30 = &lbl_1_bss_35BC[1];
    HuSprAttrSet(var_r28, 2, 4);
    for (var_r27 = 0; var_r27 < 4; var_r27++) {
        HuSprAttrSet(var_r28, var_r27 + 3, 4);
    }
    HuSprAttrSet(var_r28, lbl_1_bss_3114[var_r30->unk_1C[4]].unk_68 + 0x37, 4);
    HuSprAttrSet(var_r28, var_r30->unk_1C[4] + 0x3F, 4);
    HuSprAttrSet(var_r28, var_r30->unk_1C[4] + 0x43, 4);
    for (var_r31 = 0; var_r31 <= 60; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0x32) {
            var_f31 = fn_1_32C(-500.0f, 10.0f, var_r31, 50.0f);
        }
        else {
            var_f31 = fn_1_254(10.0f, 0.0f, var_r31 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_3C, 0.0f, var_f31);
        for (var_r29 = 0; var_r29 < 5; var_r29++) {
            HuWinPosSet(lbl_1_bss_35BC->unk_44[var_r29], 100.0f, lbl_1_data_5DC[var_r29][1] - 21.0f + var_f31);
        }
    }
}

void fn_1_1C990(void)
{
    float var_f31;
    s32 var_r31;
    MentDllUnkBss35BCStruct *var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r28 = lbl_1_bss_35BC[0].unk_3C;
    var_r30 = &lbl_1_bss_35BC[1];
    HuSprAttrSet(var_r28, 2, 4);
    for (var_r27 = 0; var_r27 < 4; var_r27++) {
        HuSprAttrSet(var_r28, var_r27 + 3, 4);
    }
    HuSprAttrSet(var_r28, lbl_1_bss_3114[var_r30->unk_1C[4]].unk_68 + 0x37, 4);
    HuSprAttrSet(var_r28, var_r30->unk_1C[4] + 0x3F, 4);
    HuSprAttrSet(var_r28, var_r30->unk_1C[4] + 0x43, 4);
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_32C(0.0f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_254(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_3C, 0.0f, var_f31);
        for (var_r29 = 0; var_r29 < 5; var_r29++) {
            HuWinPosSet(lbl_1_bss_35BC->unk_44[var_r29], 100.0f, lbl_1_data_5DC[var_r29][1] - 21.0f + var_f31);
        }
    }
}

void fn_1_1CBC8(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_35BC[0].unk_30;
    for (var_r31 = 0; var_r31 < 0x22; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(var_r30, 0, HUSPR_ATTR_DISPOFF);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 1, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r30, var_r31 + 5, HUSPR_ATTR_DISPOFF);
    }
    HuSprPosSet(var_r30, 0x1B, 288.0f, lbl_1_data_640[1][2]);
    HuSprScaleSet(var_r30, 0x1B, 1.0f, 0.75f);
    HuSprPosSet(var_r30, 0x1C, lbl_1_data_640[1][3], lbl_1_data_640[1][2]);
    HuSprPosSet(var_r30, 0x1D, lbl_1_data_640[1][4], lbl_1_data_640[1][2]);
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        HuSprBankSet(var_r30, var_r31 + 9, 0);
        HuSprAttrReset(var_r30, var_r31 + 9, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r30, var_r31 + 0x11, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(var_r30, 0x19, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(var_r30, 0x1A, HUSPR_ATTR_DISPOFF);
    HuSprBankSet(var_r30, 0x1E, 0);
    HuSprAttrReset(var_r30, 0x1E, HUSPR_ATTR_DISPOFF);
    HuSprBankSet(var_r30, 0x1F, 0);
    HuSprAttrReset(var_r30, 0x1F, HUSPR_ATTR_DISPOFF);
    HuSprBankSet(var_r30, 0x20, 0);
    HuSprAttrReset(var_r30, 0x20, HUSPR_ATTR_DISPOFF);
    HuSprBankSet(var_r30, 0x21, 0);
    HuSprAttrReset(var_r30, 0x21, HUSPR_ATTR_DISPOFF);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        HuWinPosSet(lbl_1_bss_35BC->unk_44[var_r31], 100.0f, lbl_1_data_640[var_r31][2] - 0x209);
    }
    lbl_1_bss_35BC[0].unk_08[0] = 1;
    lbl_1_bss_35BC[0].unk_1C[0] = lbl_1_bss_35BC[0].unk_1C[0] = 0;
    HuSprGrpPosSet(var_r30, 0.0f, -500.0f);
}

void fn_1_1CF68(void)
{
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_35BC[0].unk_30;
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        HuSprBankSet(var_r31, var_r30 + 9, 0);
    }
    HuSprBankSet(var_r31, 0x19, 0);
    HuSprBankSet(var_r31, 0x1A, 0);
    HuSprPosSet(var_r31, 0x1B, 288.0f, lbl_1_data_640[1][2]);
    HuSprScaleSet(var_r31, 0x1B, 1.0f, 0.75f);
    HuSprPosSet(var_r31, 0x1C, lbl_1_data_640[1][3], lbl_1_data_640[1][2]);
    HuSprPosSet(var_r31, 0x1D, lbl_1_data_640[1][4], lbl_1_data_640[1][2]);
    for (var_r30 = 0; var_r30 <= 0xA; var_r30++) {
        fn_1_4D8();
        if (var_r30 <= 5) {
            var_f31 = fn_1_32C(1.0f, 0.0f, var_r30, 5.0f);
        }
        else {
            var_f31 = fn_1_32C(0.0f, 1.0f, var_r30 - 5, 5.0f);
        }
        if (lbl_1_bss_3114->unk_68 != 0) {
            var_f30 = fn_1_32C(lbl_1_data_640[lbl_1_bss_3114->unk_68 % 4][0], lbl_1_data_640[0][0], var_r30, 10.0f);
            var_f29 = fn_1_32C(lbl_1_data_640[lbl_1_bss_3114->unk_68 / 4][1], lbl_1_data_640[0][1], var_r30, 10.0f);
            HuSprPosSet(var_r31, 0x19, var_f30, var_f29);
            HuSprPosSet(var_r31, 0x1A, var_f30, var_f29);
        }
        if (lbl_1_bss_35BC[0].unk_1C[0] != 0) {
            HuSprScaleSet(var_r31, 0x1E, 1.0f, var_f31);
            HuSprScaleSet(var_r31, 0x1F, 1.0f, var_f31);
        }
        if (lbl_1_bss_35BC[0].unk_1C[1] != 0) {
            HuSprScaleSet(var_r31, 0x20, 1.0f, var_f31);
            HuSprScaleSet(var_r31, 0x21, 1.0f, var_f31);
        }
        if (var_r30 == 6) {
            HuSprBankSet(var_r31, 0x1E, 0);
            HuSprBankSet(var_r31, 0x1F, 0);
            HuSprBankSet(var_r31, 0x20, 0);
            HuSprBankSet(var_r31, 0x21, 0);
        }
    }
    lbl_1_bss_3114[0].unk_70[0] = lbl_1_bss_3114[0].unk_68 = 0;
    lbl_1_bss_35BC[0].unk_08[0] = 1;
    lbl_1_bss_35BC[0].unk_1C[0] = lbl_1_bss_35BC[0].unk_1C[1] = 0;
}

void fn_1_1D4FC(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r27;
    AnimData *var_r26;

    s32 sp8[4][2] = {
        { 0x00000070, 0x00000037 },
        { 0x000001D2, 0x00000037 },
        { 0x00000070, 0x0000011A },
        { 0x000001D2, 0x0000011A },
    };
    arg0->unk_30 = var_r30 = (s16)HuSprGrpCreate(0x22);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x58)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r30, 0, var_r29);
    HuSprTPLvlSet(var_r30, 0, 0.8f);
    fn_1_6534(var_r30, 0, 288.0f, 240.0f);
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x18));
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x19));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = HuSprCreate(var_r27, 0x7BC, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 1, var_r29);
        HuSprBankSet(var_r30, var_r31 + 1, var_r31);
        fn_1_6534(var_r30, var_r31 + 1, sp8[var_r31][0], sp8[var_r31][1]);
        var_r29 = HuSprCreate(var_r26, 0x7C6, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 5, var_r29);
        HuSprBankSet(var_r30, var_r31 + 5, var_r31);
        HuSprTPLvlSet(var_r30, var_r31 + 5, 0.5f);
        fn_1_6534(var_r30, var_r31 + 5, sp8[var_r31][0] + 1, sp8[var_r31][1] + 6);
    }
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x41)), 0x7BC, 0);
    HuSprGrpMemberSet(var_r30, 0x1B, var_r29);
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x42));
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r29 = HuSprCreate(var_r27, 0, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x1C, var_r29);
        HuSprBankSet(var_r30, var_r31 + 0x1C, var_r31);
    }
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x22));
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        var_r29 = HuSprCreate(HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MENT, 0x1A)), 0x3E8, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 9, var_r29);
        HuSprPosSet(var_r30, var_r31 + 9, lbl_1_data_640[var_r31 % 4][0], lbl_1_data_640[var_r31 / 4][1]);
        var_r29 = HuSprCreate(var_r27, 0x3F2, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 0x11, var_r29);
        HuSprTPLvlSet(var_r30, var_r31 + 0x11, 0.5f);
        HuSprPosSet(var_r30, var_r31 + 0x11, lbl_1_data_640[var_r31 % 4][0] + 1, lbl_1_data_640[var_r31 / 4][1] + 2);
    }
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x23)), 0, 0);
    HuSprGrpMemberSet(var_r30, 0x19, var_r29);
    HuSprPosSet(var_r30, 0x19, lbl_1_data_640[0][0], lbl_1_data_640[0][1]);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x28)), 0xA, 0);
    HuSprGrpMemberSet(var_r30, 0x1A, var_r29);
    HuSprPosSet(var_r30, 0x1A, lbl_1_data_640[0][0], lbl_1_data_640[0][1]);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x5D)), 0x3E8, 0);
    HuSprGrpMemberSet(var_r30, 0x1E, var_r29);
    HuSprPosSet(var_r30, 0x1E, 340.0f, lbl_1_data_640[1][2]);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x5E)), 0x3F2, 0);
    HuSprGrpMemberSet(var_r30, 0x1F, var_r29);
    HuSprTPLvlSet(var_r30, 0x1F, 0.5f);
    HuSprPosSet(var_r30, 0x1F, 341.0f, lbl_1_data_640[1][2] + 2);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x48)), 0x3E8, 0);
    HuSprGrpMemberSet(var_r30, 0x20, var_r29);
    HuSprPosSet(var_r30, 0x20, 340.0f, lbl_1_data_640[2][2]);
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x49)), 0x3F2, 0);
    HuSprGrpMemberSet(var_r30, 0x21, var_r29);
    HuSprTPLvlSet(var_r30, 0x21, 0.5f);
    HuSprPosSet(var_r30, 0x21, 341.0f, lbl_1_data_640[2][2] + 2);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        arg0->unk_44[var_r31] = HuWinExCreateStyled(0.0f, 0.0f, 0xC8, 0xC8, -1, 1);
        HuWinBGTPLvlSet(arg0->unk_44[var_r31], 0.0f);
        HuWinMesSet(arg0->unk_44[var_r31], var_r31 + 0x1B002D);
        HuWinMesSpeedSet(arg0->unk_44[var_r31], 0);
        HuWinDispOn(arg0->unk_44[var_r31]);
        if (var_r31 == 0) {
            HuWinDispOff(arg0->unk_44[var_r31]);
        }
        winData[arg0->unk_44[var_r31]].mess_shadow_color = 0;
    }
    fn_1_1CBC8();
}

void fn_1_1DED8()
{
    s32 var_r30;
    s32 var_r31;

    var_r30 = lbl_1_bss_35BC[0].unk_30;
    HuSprAttrReset(var_r30, 0x1B, HUSPR_ATTR_DISPOFF);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 0x1C, HUSPR_ATTR_DISPOFF);
    }
}

void fn_1_1DF48(void)
{
    s32 var_r30;
    s32 var_r31;

    var_r30 = lbl_1_bss_35BC[0].unk_30;
    HuSprAttrSet(var_r30, 0x1B, 4);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrSet(var_r30, var_r31 + 0x1C, 4);
    }
}

void fn_1_1DFB8(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    fn_1_1CBC8();
    var_r28 = lbl_1_bss_35BC[0].unk_30;
    HuSprAttrSet(var_r28, 0x1B, 4);
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        HuSprAttrSet(var_r28, var_r29 + 0x1C, 4);
    }
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0x32) {
            var_f31 = fn_1_32C(-500.0f, 10.0f, var_r31, 50.0f);
        }
        else {
            var_f31 = fn_1_254(10.0f, 0.0f, var_r31 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_30, 0.0f, var_f31);
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            HuWinPosSet(lbl_1_bss_35BC[0].unk_44[var_r30], 100.0f, lbl_1_data_640[var_r30][2] - 0x15 + var_f31);
        }
    }
}

void fn_1_1E1B4(void)
{
    float var_f31;
    s32 var_r31;
    MentDllUnkBss35BCStruct *var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r28 = lbl_1_bss_35BC[0].unk_3C;
    var_r30 = &lbl_1_bss_35BC[1];
    HuSprAttrSet(var_r28, 2, 4);
    for (var_r27 = 0; var_r27 < 4; var_r27++) {
        HuSprAttrSet(var_r28, var_r27 + 3, 4);
    }
    HuSprAttrSet(var_r28, lbl_1_bss_3114[var_r30->unk_1C[4]].unk_68 + 0x37, 4);
    HuSprAttrSet(var_r28, var_r30->unk_1C[4] + 0x3F, 4);
    HuSprAttrSet(var_r28, var_r30->unk_1C[4] + 0x43, 4);
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_32C(0.0f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_254(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_30, 0.0f, var_f31);
        for (var_r29 = 0; var_r29 < 3; var_r29++) {
            HuWinPosSet(lbl_1_bss_35BC->unk_44[var_r29], 100.0f, lbl_1_data_640[var_r29][2] - 0x15 + var_f31);
        }
    }
}

void fn_1_1E404(omObjData *arg0, MentDllUnkBss3114Struct *arg1)
{
    float var_f31;
    float var_f30;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    var_r28 = lbl_1_bss_35BC[0].unk_30;
    var_r26 = 0;
    var_r25 = 0;
    var_r30 = arg1->unk_68 % 4;
    var_r24 = var_r30;
    var_r29 = arg1->unk_68 / 4;
    var_r23 = var_r29;
    if (arg1->unk_70[0] == 0) {
        if (HuPadBtnDown[arg1->unk_6C] & PAD_BUTTON_A) {
            arg1->unk_70[0] = 1;
            HuSprBankSet(var_r28, arg1->unk_68 + 9, 1);
            HuSprBankSet(var_r28, 0x19, 1);
            HuSprBankSet(var_r28, 0x1A, 1);
            HuAudFXPlay(arg1->unk_68 + 0x6D);
        }
        else {
            if ((HuPadStkX[arg1->unk_6C] >= 5) || ((HuPadBtn[arg1->unk_6C] & 2) != 0)) {
                var_r30++;
                var_r26 = 1;
                if (var_r30 > 3) {
                    var_r30 = 3;
                }
            }
            else if ((HuPadStkX[arg1->unk_6C] <= -5) || ((HuPadBtn[arg1->unk_6C] & 1) != 0)) {
                var_r30--;
                var_r26 = -1;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
            }
            if ((HuPadStkY[arg1->unk_6C] <= -5) || ((HuPadBtn[arg1->unk_6C] & 4) != 0)) {
                var_r29++;
                var_r25 = 1;
                if (var_r29 > 1) {
                    var_r29 = 1;
                }
            }
            else if ((HuPadStkY[arg1->unk_6C] >= 5) || ((HuPadBtn[arg1->unk_6C] & 8) != 0)) {
                var_r29--;
                var_r25 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
    }
    else if ((HuPadBtnDown[arg1->unk_6C] & 0x200) != 0) {
        arg1->unk_70[0] = 0;
        HuSprBankSet(var_r28, arg1->unk_68 + 9, 0);
        HuSprBankSet(var_r28, 0x19, 0);
        HuSprBankSet(var_r28, 0x1A, 0);
        HuAudFXPlay(3);
    }
    if (arg1->unk_68 != (var_r30 + (var_r29 * 4))) {
        arg1->unk_68 = var_r30 + (var_r29 * 4);
        HuAudFXPlay(0);
        for (var_r27 = 0; var_r27 <= 0xA; var_r27++) {
            fn_1_4D8();
            var_f31 = fn_1_32C(lbl_1_data_640[var_r24][0], lbl_1_data_640[var_r30][0], var_r27, 10.0f);
            var_f30 = fn_1_32C(lbl_1_data_640[var_r23][1], lbl_1_data_640[var_r29][1], var_r27, 10.0f);
            HuSprPosSet(var_r28, 0x19, var_f31, var_f30);
            HuSprPosSet(var_r28, 0x1A, var_f31, var_f30);
        }
    }
}

void fn_1_1E8A4(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    var_r30 = arg1->unk_30;
    var_r28 = 0;
    var_r27 = arg1->unk_08[0];
    lbl_1_bss_35BC[0].unk_08[3] = 0;
    if (HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_A) {
        lbl_1_bss_35BC[0].unk_08[3] = 1;
        arg1->unk_08[0]++;
        if (arg1->unk_08[0] > 2) {
            arg1->unk_08[0] = 2;
            lbl_1_bss_35BC[1].unk_08[1] = 1;
            var_r24 = lbl_1_bss_35BC[0].unk_30;
            HuSprAttrSet(var_r24, 0x1B, 4);
            for (var_r26 = 0; var_r26 < 2; var_r26++) {
                HuSprAttrSet(var_r24, var_r26 + 0x1C, 4);
            }
        }
        HuAudFXPlay(2);
    }
    else if (HuPadBtnDown[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_B) {
        lbl_1_bss_35BC[0].unk_08[3] = 1;
        arg1->unk_08[0]--;
        if (arg1->unk_08[0] < 1) {
            arg1->unk_08[0] = 1;
            lbl_1_bss_35BC[1].unk_08[1] = -1;
            var_r23 = lbl_1_bss_35BC[0].unk_30;
            HuSprAttrSet(var_r23, 0x1B, 4);
            for (var_r25 = 0; var_r25 < 2; var_r25++) {
                HuSprAttrSet(var_r23, var_r25 + 0x1C, 4);
            }
        }
        HuAudFXPlay(3);
    }
    else if ((HuPadStkX[lbl_1_bss_3114->unk_6C] >= 5) || (HuPadBtn[lbl_1_bss_3114->unk_6C] & PAD_BUTTON_RIGHT)) {
        var_r28 = 1;
        lbl_1_bss_35BC[0].unk_08[3] = 1;
        switch (arg1->unk_08[0]) {
            case 1:
                if (lbl_1_bss_A8[5] == 1) {
                    arg1->unk_1C[0] += 1;
                    if (arg1->unk_1C[0] > 4) {
                        arg1->unk_1C[0] = 0;
                    }
                }
                else {
                    arg1->unk_1C[0] += 1;
                    if (arg1->unk_1C[0] > 4) {
                        arg1->unk_1C[0] = 0;
                    }
                    if (arg1->unk_1C[0] == 3) {
                        arg1->unk_1C[0] = 4;
                    }
                }
                break;
            case 2:
                if (lbl_1_bss_A8[6] == 1) {
                    arg1->unk_1C[1]++;
                    if (arg1->unk_1C[1] > 2) {
                        arg1->unk_1C[1] = 0;
                    }
                }
                else {
                    arg1->unk_1C[1]++;
                    if (arg1->unk_1C[1] > 1) {
                        arg1->unk_1C[1] = 0;
                    }
                }
                break;
        }
        HuAudFXPlay(0);
    }
    else if ((HuPadStkX[lbl_1_bss_3114->unk_6C] <= -5) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 1) != 0)) {
        var_r28 = -1;
        lbl_1_bss_35BC[0].unk_08[3] = 1;
        switch (arg1->unk_08[0]) {
            case 1:
                if (lbl_1_bss_A8[5] == 1) {
                    arg1->unk_1C[0] -= 1;
                    if (arg1->unk_1C[0] < 0) {
                        arg1->unk_1C[0] = 4;
                    }
                }
                else {
                    arg1->unk_1C[0] -= 1;
                    if (arg1->unk_1C[0] < 0) {
                        arg1->unk_1C[0] = 4;
                    }
                    if (arg1->unk_1C[0] == 3) {
                        arg1->unk_1C[0] = 2;
                    }
                }
                break;
            case 2:
                if (lbl_1_bss_A8[6] == 1) {
                    arg1->unk_1C[1]--;
                    if (arg1->unk_1C[1] < 0) {
                        arg1->unk_1C[1] = 2;
                    }
                }
                else {
                    arg1->unk_1C[1]--;
                    if (arg1->unk_1C[1] < 0) {
                        arg1->unk_1C[1] = 1;
                    }
                }
                break;
        }
        HuAudFXPlay(0);
    }
    if (var_r27 != arg1->unk_08[0]) {
        for (var_r29 = 0; var_r29 < 0xB; var_r29++) {
            fn_1_4D8();
            var_f29 = fn_1_32C(lbl_1_data_640[var_r27][2], lbl_1_data_640[arg1->unk_08[0]][2], var_r29, 10.0f);
            HuSprPosSet(var_r30, 0x1B, 288.0f, var_f29);
            var_f31 = fn_1_32C(lbl_1_data_640[var_r27][3], lbl_1_data_640[arg1->unk_08[0]][3], var_r29, 10.0f);
            HuSprPosSet(var_r30, 0x1C, var_f31, var_f29);
            var_f31 = fn_1_32C(lbl_1_data_640[var_r27][4], lbl_1_data_640[arg1->unk_08[0]][4], var_r29, 10.0f);
            HuSprPosSet(var_r30, 0x1D, var_f31, var_f29);
        }
    }
    else if (var_r28 != 0) {
        for (var_r29 = 0; var_r29 <= 0xA; var_r29++) {
            fn_1_4D8();
            if (var_r29 <= 5) {
                var_f31 = fn_1_32C(0.0f, 10.0f, var_r29, 5.0f);
                var_f30 = fn_1_32C(1.0f, 0.0f, var_r29, 5.0f);
            }
            else {
                var_f31 = fn_1_32C(10.0f, 0.0f, var_r29 - 5, 5.0f);
                var_f30 = fn_1_32C(0.0f, 1.0f, var_r29 - 5, 5.0f);
            }
            if (var_r28 == 1) {
                HuSprPosSet(var_r30, 0x1D, var_f31 + lbl_1_data_640[arg1->unk_08[0]][4], lbl_1_data_640[arg1->unk_08[0]][2]);
            }
            else {
                HuSprPosSet(var_r30, 0x1C, lbl_1_data_640[arg1->unk_08[0]][3] - var_f31, lbl_1_data_640[arg1->unk_08[0]][2]);
            }
            switch (arg1->unk_08[0]) {
                case 1:
                    if (var_r28 == 1) {
                        HuSprPosSet(var_r30, 0x1E, 340.0f + var_f31, lbl_1_data_640[1][2]);
                        HuSprPosSet(var_r30, 0x1F, 340.0f + var_f31, lbl_1_data_640[1][2] + 2);
                    }
                    else {
                        HuSprPosSet(var_r30, 0x1E, 341.0f - var_f31, lbl_1_data_640[1][2]);
                        HuSprPosSet(var_r30, 0x1F, 341.0f - var_f31, lbl_1_data_640[1][2] + 2);
                    }
                    HuSprScaleSet(var_r30, 0x1E, 1.0f, var_f30);
                    HuSprScaleSet(var_r30, 0x1F, 1.0f, var_f30);
                    break;
                case 2:
                    if (var_r28 == 1) {
                        HuSprPosSet(var_r30, 0x20, 340.0f + var_f31, lbl_1_data_640[2][2]);
                        HuSprPosSet(var_r30, 0x21, 340.0f + var_f31, lbl_1_data_640[2][2] + 2);
                    }
                    else {
                        HuSprPosSet(var_r30, 0x20, 341.0f - var_f31, lbl_1_data_640[2][2]);
                        HuSprPosSet(var_r30, 0x21, 341.0f - var_f31, lbl_1_data_640[2][2] + 2);
                    }
                    HuSprScaleSet(var_r30, 0x20, 1.0f, var_f30);
                    HuSprScaleSet(var_r30, 0x21, 1.0f, var_f30);
                    break;
            }
            if (var_r29 == 6) {
                switch (arg1->unk_08[0]) {
                    case 1:
                        HuSprBankSet(var_r30, 0x1E, arg1->unk_1C[0]);
                        HuSprBankSet(var_r30, 0x1F, arg1->unk_1C[0]);
                        break;
                    case 2:
                        HuSprBankSet(var_r30, 0x20, arg1->unk_1C[1]);
                        HuSprBankSet(var_r30, 0x21, arg1->unk_1C[1]);
                        break;
                }
            }
        }
    }
    lbl_1_bss_35BC[0].unk_08[3] = 0;
}

void fn_1_1F5F0(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_35BC[0].unk_34;
    for (var_r30 = 0; var_r30 < 9; var_r30++) {
        HuSprAttrSet(var_r31, var_r30, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(var_r31, 0, HUSPR_ATTR_DISPOFF);
    HuSprBankSet(var_r31, 0, lbl_1_bss_35BC[0].unk_1C[0]);
    HuSprAttrReset(var_r31, lbl_1_bss_3114->unk_68 + 1, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(var_r31, 16.0f, -500.0f);
}

void fn_1_1F6B8(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r29 = HuSprGrpCreate(9);
    arg0->unk_34 = var_r29;
    var_r27 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x59)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r29, 0, var_r27);
    fn_1_6534(var_r29, 0, 75.0f, 25.0f);
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        var_r27 = HuSprCreate(HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MENT, 0x31)), 0x3E8, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 1, var_r27);
        HuSprPosSet(var_r29, var_r31 + 1, 24.0f, 25.0f);
    }
    var_r30 = lbl_1_bss_35BC[0].unk_34;
    for (var_r28 = 0; var_r28 < 9; var_r28++) {
        HuSprAttrSet(var_r30, var_r28, 4);
    }
    HuSprAttrReset(var_r30, 0, HUSPR_ATTR_DISPOFF);
    HuSprBankSet(var_r30, 0, lbl_1_bss_35BC[0].unk_1C[0]);
    HuSprAttrReset(var_r30, lbl_1_bss_3114->unk_68 + 1, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(var_r30, 16.0f, -500.0f);
}

void fn_1_1F868(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = lbl_1_bss_35BC[0].unk_34;
    for (var_r29 = 0; var_r29 < 9; var_r29++) {
        HuSprAttrSet(var_r30, var_r29, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(var_r30, 0, HUSPR_ATTR_DISPOFF);
    HuSprBankSet(var_r30, 0, lbl_1_bss_35BC[0].unk_1C[0]);
    HuSprAttrReset(var_r30, lbl_1_bss_3114->unk_68 + 1, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(var_r30, 16.0f, -500.0f);
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0x32) {
            var_f31 = fn_1_32C(-500.0f, 50.0f, var_r31, 50.0f);
        }
        else {
            var_f31 = fn_1_254(50.0f, 40.0f, var_r31 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_34, 16.0f, var_f31);
    }
}

void fn_1_1FA34(void)
{
    float var_f31;
    s32 var_r31;

    lbl_1_bss_35BC[0].unk_08[0] = -1;
    lbl_1_bss_35BC[0].unk_04 = NULL;
    for (var_r31 = 0; var_r31 <= 0x4B; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_32C(40.0f, 50.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_254(50.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_34, 16.0f, var_f31);
        if (var_r31 >= 0xF) {
            var_f31 = fn_1_254(210.0f, -500.0f, var_r31 - 0xF, 60.0f);
            HuSprGrpData[lbl_1_bss_35BC[0].unk_38].y = (s32)fn_1_234(HuSprGrpData[lbl_1_bss_35BC[0].unk_38].y, var_f31, 10.0f);
        }
    }
}

void fn_1_1FC54(void)
{
    float var_f31;
    s32 var_r31;

    lbl_1_bss_35BC[0].unk_08[0] = -1;
    lbl_1_bss_35BC[0].unk_04 = NULL;
    for (var_r31 = 0; var_r31 <= 0x28; var_r31++) {
        fn_1_4D8();
        var_f31 = fn_1_254(40.0f, -500.0f, var_r31, 40.0f);
        HuSprGrpPosSet(lbl_1_bss_35BC[0].unk_34, 16.0f, var_f31);
        var_f31 = fn_1_254(210.0f, -500.0f, var_r31, 40.0f);
        HuSprGrpData[lbl_1_bss_35BC[0].unk_38].y = (s32)fn_1_234(HuSprGrpData[lbl_1_bss_35BC[0].unk_38].y, var_f31, 10.0f);
    }
}

void fn_1_1FE08(void)
{
    s32 sp8;
    s32 var_r31;
    s32 var_r30;

    sp8 = 0;
    var_r30 = lbl_1_bss_35BC[0].unk_40;
    for (var_r31 = 0; var_r31 < 0x13; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprBankSet(var_r30, var_r31, 0);
        lbl_1_bss_3114[var_r31].unk_70[3] = lbl_1_bss_3114[var_r31].unk_60 = 0;
        HuSprAttrReset(var_r30, var_r31, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r30, var_r31 + 4, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(var_r30, 0xA, HUSPR_ATTR_DISPOFF);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 0xB, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r30, var_r31 + 0xF, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpPosSet(var_r30, 0.0f, -500.0f);
}

void fn_1_1FF4C(omObjData *arg0, MentDllUnkBss35BCStruct *arg1)
{
    s32 sp8;
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    sp8 = 0;
    var_r28 = lbl_1_bss_35BC[0].unk_40;
    var_r29 = var_r27 = var_r26 = var_r25 = 0;
    lbl_1_bss_35BC[0].unk_1C[0] = 0;
    var_r29 = 1;
    for (var_r30 = 1; var_r30 < 4; var_r30++) {
        if (lbl_1_bss_3114[var_r30].unk_60 == 0) {
            var_r29++;
        }
    }
    var_r27 = 1;
    for (var_r30 = 1; var_r30 < 4; var_r30++) {
        if (HuPadStatGet(var_r30) != -1) {
            var_r27++;
        }
    }
    if (var_r27 >= 2) {
        fn_1_208F4();
        if ((HuPadStkX[lbl_1_bss_3114->unk_6C] >= 5) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 2) != 0)) {
            var_r29++;
            var_r26 = 1;
        }
        else if ((HuPadStkX[lbl_1_bss_3114->unk_6C] <= -5) || ((HuPadBtn[lbl_1_bss_3114->unk_6C] & 1) != 0)) {
            var_r29--;
            var_r26 = -1;
        }
    }
    else {
        fn_1_20A24();
    }
    if (var_r29 < 1) {
        var_r29 = var_r27;
    }
    else if (var_r29 > var_r27) {
        if (var_r26 == 0) {
            var_r29 = var_r27;
            var_r25 = 1;
        }
        else {
            var_r29 = 1;
        }
    }
    if ((var_r26 != 0) || (var_r25 != 0)) {
        lbl_1_bss_35BC[0].unk_1C[0] = 1;
        HuAudFXPlay(0);
        for (var_r30 = 0; var_r30 <= 0xA; var_r30++) {
            if (var_r30 <= 5) {
                var_f30 = fn_1_32C(0.0f, 10.0f, var_r30, 5.0f);
                var_f31 = fn_1_32C(1.0f, 0.0f, var_r30, 5.0f);
            }
            else {
                var_f30 = fn_1_32C(10.0f, 0.0f, var_r30 - 5, 5.0f);
                var_f31 = fn_1_32C(0.0f, 1.0f, var_r30 - 5, 5.0f);
            }
            if (var_r26 == 1) {
                HuSprPosSet(var_r28, 9, (lbl_1_data_690[3][0] + 0x32) + var_f30, lbl_1_data_690[0][1]);
            }
            else if (var_r26 == -1) {
                HuSprPosSet(var_r28, 8, (lbl_1_data_690[0][0] - 0x32) - var_f30, lbl_1_data_690[0][1]);
            }
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if ((var_r31 < var_r29) && (lbl_1_bss_3114[var_r31].unk_60 == 1)) {
                    lbl_1_bss_3114[var_r31].unk_70[3] = 0;
                    HuSprScaleSet(var_r28, var_r31, var_f31, 1.0f);
                    HuSprScaleSet(var_r28, var_r31 + 4, var_f31, 1.0f);
                    if (var_r30 == 5) {
                        HuSprBankSet(var_r28, var_r31, 0);
                    }
                }
                else if ((var_r31 >= var_r29) && (lbl_1_bss_3114[var_r31].unk_60 == 0)) {
                    lbl_1_bss_3114[var_r31].unk_70[3] = 1;
                    HuSprScaleSet(var_r28, var_r31, var_f31, 1.0f);
                    HuSprScaleSet(var_r28, var_r31 + 4, var_f31, 1.0f);
                    if (var_r30 == 5) {
                        HuSprBankSet(var_r28, var_r31, 1);
                    }
                }
            }
            fn_1_4D8();
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (var_r31 < var_r29) {
                lbl_1_bss_3114[var_r31].unk_60 = 0;
            }
            else {
                lbl_1_bss_3114[var_r31].unk_60 = 1;
            }
        }
    }
    lbl_1_bss_35BC[0].unk_1C[0] = 0;
}

void fn_1_2055C(s32 arg0)
{
    s32 spC;
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_35BC[0].unk_40;
    if (arg0 == 0) {
        spC = 0;
        var_r30 = lbl_1_bss_35BC[0].unk_40;
        for (var_r31 = 0; var_r31 < 0x13; var_r31++) {
            HuSprAttrSet(var_r30, var_r31, HUSPR_ATTR_DISPOFF);
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            HuSprBankSet(var_r30, var_r31, 0);
            lbl_1_bss_3114[var_r31].unk_70[3] = lbl_1_bss_3114[var_r31].unk_60 = 0;
            HuSprAttrReset(var_r30, var_r31, HUSPR_ATTR_DISPOFF);
            HuSprAttrReset(var_r30, var_r31 + 4, HUSPR_ATTR_DISPOFF);
        }
        HuSprAttrReset(var_r30, 0xA, HUSPR_ATTR_DISPOFF);
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            HuSprAttrReset(var_r30, var_r31 + 0xB, HUSPR_ATTR_DISPOFF);
            HuSprAttrReset(var_r30, var_r31 + 0xF, HUSPR_ATTR_DISPOFF);
        }
        HuSprGrpPosSet(var_r30, 0.0f, -500.0f);
    }
    for (var_r29 = 0; var_r29 <= 0x3C; var_r29++) {
        fn_1_4D8();
        if (var_r29 <= 0x32) {
            var_f31 = fn_1_32C(-500.0f, 10.0f, var_r29, 50.0f);
        }
        else {
            var_f31 = fn_1_254(10.0f, 2.06f, var_r29 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r28, 0.0f, var_f31);
    }
}

void fn_1_207BC(void)
{
    s32 spC;
    s32 sp8;
    float var_f31;
    s32 var_r31;
    s32 var_r30;

    spC = 0;
    sp8 = 0;
    var_r30 = lbl_1_bss_35BC[0].unk_40;
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_4D8();
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_32C(2.06f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_254(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(var_r30, 0.0f, var_f31);
    }
}

void fn_1_208F4(void)
{
    s32 var_r31;

    var_r31 = lbl_1_bss_35BC[0].unk_40;
    HuSprAttrReset(var_r31, 8, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(var_r31, 8, lbl_1_data_690[0][0] - 0x32, lbl_1_data_690[0][1]);
    HuSprAttrReset(var_r31, 9, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(var_r31, 9, lbl_1_data_690[3][0] + 0x32, lbl_1_data_690[0][1]);
}

void fn_1_20A24(void)
{
    s32 var_r31;

    var_r31 = lbl_1_bss_35BC[0].unk_40;
    HuSprAttrSet(var_r31, 8, 4);
    HuSprPosSet(var_r31, 8, lbl_1_data_690[0][0] - 0x32, lbl_1_data_690[0][1]);
    HuSprAttrSet(var_r31, 9, 4);
    HuSprPosSet(var_r31, 9, lbl_1_data_690[3][0] + 0x32, lbl_1_data_690[0][1]);
}

void fn_1_20B54(MentDllUnkBss35BCStruct *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 sp8;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    AnimData *var_r26;
    AnimData *var_r25;

    var_r29 = HuSprGrpCreate(0x13);
    arg0->unk_40 = var_r29;
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x22));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r28 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x16)), 0x3E8, 0);
        HuSprGrpMemberSet(var_r29, var_r31, var_r28);
        HuSprPosSet(var_r29, var_r31, lbl_1_data_690[var_r31 % 4][0], lbl_1_data_690[0][1]);
        var_r28 = HuSprCreate(var_r26, 0x3F2, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 4, var_r28);
        HuSprTPLvlSet(var_r29, var_r31 + 4, 0.5f);
        HuSprPosSet(var_r29, var_r31 + 4, lbl_1_data_690[var_r31 % 4][0] + 1, lbl_1_data_690[0][1] + 2);
    }
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x42));
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r28 = HuSprCreate(var_r26, 0, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 8, var_r28);
        HuSprBankSet(var_r29, var_r31 + 8, var_r31);
    }
    var_r28 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x15)), 0x7D0, 0);
    HuSprGrpMemberSet(var_r29, 0xA, var_r28);
    HuSprTPLvlSet(var_r29, 0xA, 0.8f);
    fn_1_6534(var_r29, 0xA, 288.0f, 240.0f);
    var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x18));
    var_r25 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MENT, 0x19));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r28 = HuSprCreate(var_r26, 0x7BC, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0xB, var_r28);
        HuSprBankSet(var_r29, var_r31 + 0xB, var_r31);
        fn_1_6534(var_r29, var_r31 + 0xB, lbl_1_data_690[var_r31][2], lbl_1_data_690[var_r31][3]);
        var_r28 = HuSprCreate(var_r25, 0x7C6, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0xF, var_r28);
        HuSprBankSet(var_r29, var_r31 + 0xF, var_r31);
        HuSprTPLvlSet(var_r29, var_r31 + 0xF, 0.5f);
        fn_1_6534(var_r29, var_r31 + 0xF, lbl_1_data_690[var_r31][2] + 1, lbl_1_data_690[var_r31][3] + 6);
    }
    sp8 = 0;
    var_r27 = lbl_1_bss_35BC[0].unk_40;
    for (var_r30 = 0; var_r30 < 0x13; var_r30++) {
        HuSprAttrSet(var_r27, var_r30, HUSPR_ATTR_DISPOFF);
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        HuSprBankSet(var_r27, var_r30, 0);
        lbl_1_bss_3114[var_r30].unk_70[3] = lbl_1_bss_3114[var_r30].unk_60 = 0;
        HuSprAttrReset(var_r27, var_r30, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r27, var_r30 + 4, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(var_r27, 0xA, HUSPR_ATTR_DISPOFF);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        HuSprAttrReset(var_r27, var_r30 + 0xB, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(var_r27, var_r30 + 0xF, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpPosSet(var_r27, 0.0f, -500.0f);
}

void fn_1_21134(omObjData *object)
{
    float var_f31;
    s32 var_r31;
    MentDllUnkBss64Struct *var_r29;

    var_r29 = &lbl_1_bss_64;
    for (var_r31 = 1; var_r31 < 0xA; var_r31++) {
        if ((var_r29->zoom <= 1200.0f) || (lbl_1_bss_16C4[var_r31].unk_1C == -200.0f)) {
            if (lbl_1_bss_16C4[var_r31].unk_1C >= -100.0f) {
                lbl_1_bss_16C4[var_r31].unk_00 = 0;
                lbl_1_bss_16C4[var_r31].unk_1C = -200.0f;
                lbl_1_bss_16C4[var_r31].unk_24 = -99.0f;
                lbl_1_bss_16C4[var_r31].unk_04 = rand8() + 0xB4;
            }
            var_f31 = fn_1_254(lbl_1_bss_16C4[var_r31].unk_10, 1000.0f, lbl_1_bss_16C4[var_r31].unk_00++, lbl_1_bss_16C4[var_r31].unk_04);
            Hu3DData[object->model[var_r31]].pos.y = fn_1_234(Hu3DData[object->model[var_r31]].pos.y, var_f31, 30.0f);
            Hu3DData[object->model[var_r31]].pos.x
                = fn_1_234(Hu3DData[object->model[var_r31]].pos.x, lbl_1_bss_16C4[var_r31].unk_18 + Hu3DData[object->model[var_r31]].pos.x, 5.0f);
        }
    }
    for (var_r31 = 0xA; var_r31 < 0x8C; var_r31++) {
        Hu3DData[object->model[var_r31]].pos.y = fn_1_3F4(
            lbl_1_bss_16C4[var_r31].unk_10, lbl_1_bss_16C4[var_r31].unk_1C, lbl_1_bss_16C4[var_r31].unk_00++, lbl_1_bss_16C4[var_r31].unk_04);
        if (lbl_1_bss_16C4[var_r31].unk_00 >= lbl_1_bss_16C4[var_r31].unk_04) {
            lbl_1_bss_16C4[var_r31].unk_00 = 0;
        }
    }
    for (var_r31 = 0xA; var_r31 < 0x8C; var_r31++) {
        if ((lbl_1_bss_16C4[var_r31].unk_24 == 0.0f) && (lbl_1_bss_16C4[var_r31].unk_14 > (var_r29->zoom - 400.0f))
            && (lbl_1_bss_16C4[var_r31].unk_0C < (200.0f + var_r29->center.x)) && (lbl_1_bss_16C4[var_r31].unk_0C > (var_r29->center.x - 200.0f))) {
            if (var_r29->center.x >= lbl_1_bss_16C4[var_r31].unk_0C) {
                lbl_1_bss_16C4[var_r31].unk_24 = -300.0f;
            }
            else {
                lbl_1_bss_16C4[var_r31].unk_24 = 300.0f;
            }
        }
        if (lbl_1_bss_16C4[var_r31].unk_24 != -99.0f) {
            Hu3DData[object->model[var_r31]].pos.x
                = fn_1_234(Hu3DData[object->model[var_r31]].pos.x, lbl_1_bss_16C4[var_r31].unk_0C + lbl_1_bss_16C4[var_r31].unk_24, 30.0f);
        }
    }
    if (object->work[0] == 1) {
        for (var_r31 = 0xA; var_r31 < 0x8C; var_r31++) {
            Hu3DModelAttrSet(object->model[var_r31], HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_1_21724(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x08));
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x09));
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x0A));
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 0x0B));
    Hu3DModelLayerSet(object->model[1], 3);
    Hu3DModelLayerSet(object->model[2], 3);
    Hu3DModelLayerSet(object->model[3], 3);
    Hu3DModelLayerSet(object->model[4], 3);
    for (var_r30 = 5; var_r30 < 0x8C; var_r30++) {
        object->model[var_r30] = Hu3DModelLink(object->model[rand8() % 4 + 1]);
    }
    for (var_r30 = 1; var_r30 < 0xA; var_r30++) {
        var_r28 = 0;
        do {
            Hu3DData[object->model[var_r30]].pos.x = var_f31 = 50.0f + rand8();
            if ((var_r30 % 2) != 0) {
                lbl_1_bss_16C4[var_r30].unk_0C = Hu3DData[object->model[var_r30]].pos.x *= -1.0f;
            }
            Hu3DData[object->model[var_r30]].pos.y = var_f30 = 50.0f + rand8();
            Hu3DData[object->model[var_r30]].pos.z = var_f29 = 750.0f + (var_r30 * 5);
            for (var_r29 = 1; var_r29 < 0xA; var_r29++) {
                if ((var_r30 != var_r29) && (lbl_1_bss_16C4[var_r29].unk_08 == 1)) {
                    var_f31 = Hu3DData[object->model[var_r30]].pos.x - Hu3DData[object->model[var_r29]].pos.x;
                    var_f30 = Hu3DData[object->model[var_r30]].pos.y - Hu3DData[object->model[var_r29]].pos.y;
                    var_f29 = Hu3DData[object->model[var_r30]].pos.z - Hu3DData[object->model[var_r29]].pos.z;
                    if (sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) <= 100.0f) {
                        break;
                    }
                }
            }
            var_r28++;
        } while (var_r29 != 0xA && var_r28 < 0x32);
        lbl_1_bss_16C4[var_r30].unk_08 = 1;
        lbl_1_bss_16C4[var_r30].unk_0C = lbl_1_bss_16C4[var_r30].unk_18 = Hu3DData[object->model[var_r30]].pos.x;
        lbl_1_bss_16C4[var_r30].unk_10 = lbl_1_bss_16C4[var_r30].unk_1C = Hu3DData[object->model[var_r30]].pos.y;
        lbl_1_bss_16C4[var_r30].unk_14 = lbl_1_bss_16C4[var_r30].unk_20 = Hu3DData[object->model[var_r30]].pos.z;
        lbl_1_bss_16C4[var_r30].unk_18 = 0.025f * lbl_1_bss_16C4[var_r30].unk_0C;
        Hu3DModelScaleSet(object->model[var_r30], 0.5f, 0.5f, 0.5f);
        Hu3DModelLayerSet(object->model[var_r30], 3);
    }
    for (var_r30 = 0xA; var_r30 < 0x8C; var_r30++) {
        var_r28 = 0;
        do {
            Hu3DData[object->model[var_r30]].pos.x = var_f31 = rand8() * 2;
            if ((var_r30 % 2) != 0) {
                Hu3DData[object->model[var_r30]].pos.x *= -1.0f;
            }

            Hu3DData[object->model[var_r30]].pos.y = var_f30 = (rand8() * 2) + 0x7D;
            Hu3DData[object->model[var_r30]].pos.z = var_f29 = 800.0f + (var_r30 * 0xA);
            for (var_r29 = 0xA; var_r29 < 0x8C; var_r29++) {
                if ((var_r30 != var_r29) && (lbl_1_bss_16C4[var_r29].unk_08 == 1)) {
                    var_f31 = Hu3DData[object->model[var_r30]].pos.x - Hu3DData[object->model[var_r29]].pos.x;
                    var_f30 = Hu3DData[object->model[var_r30]].pos.y - Hu3DData[object->model[var_r29]].pos.y;
                    var_f29 = Hu3DData[object->model[var_r30]].pos.z - Hu3DData[object->model[var_r29]].pos.z;
                    if (sqrtf((var_f29 * var_f29) + ((var_f31 * var_f31) + (var_f30 * var_f30))) <= 100.0f) {
                        break;
                    }
                }
            }
            var_r28++;
        } while (var_r29 != 0x8C && var_r28 < 0x32);

        lbl_1_bss_16C4[var_r30].unk_08 = 1;
        Hu3DModelLayerSet(object->model[var_r30], 3);
        lbl_1_bss_16C4[var_r30].unk_0C = lbl_1_bss_16C4[var_r30].unk_18 = Hu3DData[object->model[var_r30]].pos.x;
        lbl_1_bss_16C4[var_r30].unk_10 = lbl_1_bss_16C4[var_r30].unk_1C = Hu3DData[object->model[var_r30]].pos.y;
        lbl_1_bss_16C4[var_r30].unk_14 = lbl_1_bss_16C4[var_r30].unk_20 = Hu3DData[object->model[var_r30]].pos.z;
        if ((rand8() % 2) == 0) {
            lbl_1_bss_16C4[var_r30].unk_18 += rand8() % 30;
        }
        else {
            lbl_1_bss_16C4[var_r30].unk_18 -= rand8() % 30;
        }
        lbl_1_bss_16C4[var_r30].unk_1C += (rand8() % 30) + 0xA;
        if ((rand8() % 2) == 0) {
            lbl_1_bss_16C4[var_r30].unk_20 += rand8() % 30;
        }
        else {
            lbl_1_bss_16C4[var_r30].unk_20 -= rand8() % 30;
        }
        lbl_1_bss_16C4[var_r30].unk_24 = lbl_1_bss_16C4[var_r30].unk_28 = lbl_1_bss_16C4[var_r30].unk_2C = 0.0f;
        lbl_1_bss_16C4[var_r30].unk_04 = ((rand8() * 2) % 360) + 0x168;
        lbl_1_bss_16C4[var_r30].unk_00 = rand8();
    }
    object->func = fn_1_21134;
}

void fn_1_225F4(omObjData *object)
{
    s32 var_r30;

    if (object->work[0] == 0) {
        return;
    }
    for (var_r30 = 0; var_r30 < 0xC8; var_r30++) {
        switch (lbl_1_bss_E4[var_r30].unk_04) {
            case 0:
                Hu3DData[object->model[var_r30]].pos.x = rand8() + rand8() % 50;
                if ((var_r30 % 2) == 0) {
                    Hu3DData[object->model[var_r30]].pos.x *= -1.0f;
                }
                Hu3DData[object->model[var_r30]].pos.y = 500.0f + rand8() + rand8();
                Hu3DData[object->model[var_r30]].pos.z = 700.0f + rand8() % 128;
                lbl_1_bss_E4[var_r30].unk_18 = 1.0f;
                lbl_1_bss_E4[var_r30].unk_00 = (rand8() % 30) + 0x1E;
                lbl_1_bss_E4[var_r30].unk_0C = 0.01f * (25.0f + (rand8() % 50));
                if ((rand8() % 2) == 0) {
                    lbl_1_bss_E4[var_r30].unk_0C *= -1.0f;
                }
                lbl_1_bss_E4[var_r30].unk_10 = rand8() % 2;
                lbl_1_bss_E4[var_r30].unk_14 = 0.01f * ((rand8() % 100) - 0x32);
                lbl_1_bss_E4[var_r30].unk_08 = (rand8() % 5) + 5;
                if ((rand8() % 2) == 0) {
                    lbl_1_bss_E4[var_r30].unk_08 *= -1;
                }
                lbl_1_bss_E4[var_r30].unk_04 = 1;
                break;
            case 1:
                if (Hu3DData[object->model[var_r30]].pos.y <= 0.5f) {
                    Hu3DData[object->model[var_r30]].pos.y = 0.5f;
                    if (lbl_1_bss_E4[var_r30].unk_10 > 0.0f) {
                        Hu3DData[object->model[var_r30]].rot.x = fn_1_234(Hu3DData[object->model[var_r30]].rot.x, 180.0f, 5.0f);
                    }
                    else {
                        Hu3DData[object->model[var_r30]].rot.x = fn_1_234(Hu3DData[object->model[var_r30]].rot.x, 0.0f, 5.0f);
                    }
                    Hu3DData[object->model[var_r30]].rot.z = fn_1_234(Hu3DData[object->model[var_r30]].rot.z, 0.0f, 5.0f);
                    lbl_1_bss_E4[var_r30].unk_18 -= 0.025f;
                    if (lbl_1_bss_E4[var_r30].unk_18 <= 0.0f) {
                        lbl_1_bss_E4[var_r30].unk_18 = 0.0f;
                        lbl_1_bss_E4[var_r30].unk_04 = 0;
                        if (object->work[0] == 3) {
                            lbl_1_bss_E4[var_r30].unk_04 = 2;
                        }
                    }
                }
                else {
                    if (lbl_1_bss_E4[var_r30].unk_00-- <= 0) {
                        lbl_1_bss_E4[var_r30].unk_00 = (rand8() % 30) + 0x1E;
                        lbl_1_bss_E4[var_r30].unk_0C = 0.01f * (25.0f + (rand8() % 50));
                        if ((rand8() % 2) == 0) {
                            lbl_1_bss_E4[var_r30].unk_0C *= -1.0f;
                        }
                        lbl_1_bss_E4[var_r30].unk_10 = rand8() % 2;
                        lbl_1_bss_E4[var_r30].unk_14 = 0.01f * ((rand8() % 100) - 0x32);
                        lbl_1_bss_E4[var_r30].unk_08 = (rand8() % 5) + 5;
                        if ((rand8() % 2) == 0) {
                            lbl_1_bss_E4[var_r30].unk_08 *= -1;
                        }
                    }
                    Hu3DModelAttrReset(object->model[var_r30], HU3D_ATTR_DISPOFF);
                    Hu3DData[object->model[var_r30]].pos.x += lbl_1_bss_E4[var_r30].unk_0C;
                    Hu3DData[object->model[var_r30]].pos.y -= (var_r30 % 3) + 2;
                    Hu3DData[object->model[var_r30]].pos.z += lbl_1_bss_E4[var_r30].unk_14;
                    Hu3DData[object->model[var_r30]].rot.x += lbl_1_bss_E4[var_r30].unk_08;
                    Hu3DData[object->model[var_r30]].rot.y += lbl_1_bss_E4[var_r30].unk_08;
                    Hu3DData[object->model[var_r30]].rot.z += lbl_1_bss_E4[var_r30].unk_08;
                    if (Hu3DData[object->model[var_r30]].rot.x >= 360.0f) {
                        Hu3DData[object->model[var_r30]].rot.x -= 360.0f;
                    }
                    else if (Hu3DData[object->model[var_r30]].rot.x <= 0.0f) {
                        Hu3DData[object->model[var_r30]].rot.x += 360.0f;
                    }
                    if (Hu3DData[object->model[var_r30]].rot.y >= 360.0f) {
                        Hu3DData[object->model[var_r30]].rot.y -= 360.0f;
                    }
                    else if (Hu3DData[object->model[var_r30]].rot.y <= 0.0f) {
                        Hu3DData[object->model[var_r30]].rot.y += 360.0f;
                    }
                    if (Hu3DData[object->model[var_r30]].rot.z >= 360.0f) {
                        Hu3DData[object->model[var_r30]].rot.z -= 360.0f;
                    }
                    else if (Hu3DData[object->model[var_r30]].rot.z <= 0.0f) {
                        Hu3DData[object->model[var_r30]].rot.z += 360.0f;
                    }
                }
                break;
            case 2:
                Hu3DModelAttrSet(object->model[var_r30], HU3D_ATTR_DISPOFF);
                break;
        }
    }
}

void fn_1_2342C(omObjData *object)
{
    float var_f30;
    float var_f31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MENT, 12));
    for (var_r30 = 0; var_r30 < 0xC8; var_r30++) {
        object->model[var_r30] = Hu3DModelLink(object->model[0]);
    }
    for (var_r30 = 0; var_r30 < 0xC8; var_r30++) {
        Hu3DModelAttrSet(object->model[var_r30], HU3D_ATTR_DISPOFF);
        Hu3DData[object->model[var_r30]].pos.x = rand8() + rand8();
        if (rand8() == 0) {
            Hu3DData[object->model[var_r30]].pos.x *= -1.0f;
        }
        Hu3DData[object->model[var_r30]].pos.y = 500.0f + rand8() + rand8();
        Hu3DData[object->model[var_r30]].pos.z = 700.0f + (rand8() % 128);
        var_f31 = 1.0f + (0.1f * (rand8() % 5));
        Hu3DModelScaleSet(object->model[var_r30], var_f31, var_f31, var_f31);
        lbl_1_bss_E4[var_r30].unk_0C = 0.01f * (25.0f + (rand8() % 50));
        if ((rand8() % 2) == 0) {
            lbl_1_bss_E4[var_r30].unk_0C *= -1.0f;
        }
        lbl_1_bss_E4[var_r30].unk_10 = rand8() % 2;
        lbl_1_bss_E4[var_r30].unk_14 = 0.01f * ((rand8() % 100) - 0x32);
        lbl_1_bss_E4[var_r30].unk_08 = (rand8() % 5) + 5;
        if ((rand8() % 2) == 0) {
            lbl_1_bss_E4[var_r30].unk_08 *= -1;
        }
        var_r29 = rand8() % 4;
        switch (var_r29) {
            case 0:
                Hu3DModelAmbSet(object->model[var_r30], 1.0f, 1.0f, 1.0f);
                break;
            case 1:
                Hu3DModelAmbSet(object->model[var_r30], 1.0f, 0.0f, 0.0f);
                break;
            case 2:
                Hu3DModelAmbSet(object->model[var_r30], 0.0f, 1.0f, 0.0f);
                break;
            case 3:
                Hu3DModelAmbSet(object->model[var_r30], 0.0f, 0.0f, 1.0f);
                break;
        }
        lbl_1_bss_E4[var_r30].unk_04 = 0;
    }
    object->func = fn_1_225F4;
}
