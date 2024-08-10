#include "ext_math.h"
#include "game/chrman.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/ztardll.h"

typedef void (*ZtarUnkFunc)(omObjData *, ...);

typedef struct ZtarDllUnkStruct2 {
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ ZtarUnkFunc unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ char pad_18[0x10]; /* maybe part of unk_14[5]? */
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ char pad_38[0x10]; /* maybe part of unk_34[5]? */
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
} ZtarDllUnkStruct2; /* size = 0x60 */

void fn_1_106E8(s32 arg0);
void fn_1_10764(s32 arg0);
void fn_1_108C8(s32);
void fn_1_10A80(void);
void fn_1_10B24(void);
s32 fn_1_10C18(s32 arg0);
s32 fn_1_10C98(s32 arg0);
float fn_1_10D60(float arg8, float arg9, float argA, float argB);
float fn_1_10E38(float arg8, float arg9, float argA, float argB);
void fn_1_10FBC(s32 arg0);
void fn_1_11960(void);
void fn_1_11C64(void);
void fn_1_11F68(void);
void fn_1_122A8(s32 arg0);
void fn_1_A02C(void);
void fn_1_A248(void);
void fn_1_A574(void);
void fn_1_A610(void);
void fn_1_A8E8(void);
void fn_1_ABC4(void);
void fn_1_AE94(void);
void fn_1_AEE4(omObjData *object, ZtarDllUnkStruct2 *arg1);
void fn_1_B468(omObjData *object, ZtarDllUnkStruct2 *arg1);
void fn_1_BA40(void);
void fn_1_BD7C(s32 arg0);
void fn_1_BFF0(s32 arg0);
void fn_1_C06C(s32 arg0, s32 arg1);
void fn_1_C4B8(s32 arg0);
void fn_1_C8EC(s32 arg0);
void fn_1_CAF0(void);
void fn_1_D280(omObjData *arg0, ZtarDllUnkStruct2 *arg1);
void fn_1_DD8C(ZtarDllUnkStruct2 *arg0);
void fn_1_E4AC(ZtarDllUnkStruct2 *arg0);
void fn_1_E548(omObjData *arg0, ZtarDllUnkStruct2 *arg1);
s32 fn_1_F214(ZtarDllUnkStruct2 *arg0);
void fn_1_FB38(void);
void fn_1_FD90(s32 arg0);

extern s16 lbl_1_bss_4;

s32 lbl_1_data_3C8[8] = {
    DATADIR_MARIOMOT,
    DATADIR_LUIGIMOT,
    DATADIR_PEACHMOT,
    DATADIR_YOSHIMOT,
    DATADIR_WARIOMOT,
    DATADIR_DONKEYMOT,
    DATADIR_DAISYMOT,
    DATADIR_WALUIGIMOT,
};
s32 lbl_1_data_3E8[8] = {
    DATADIR_MARIOMDL1,
    DATADIR_LUIGIMDL1,
    DATADIR_PEACHMDL1,
    DATADIR_YOSHIMDL1,
    DATADIR_WARIOMDL1,
    DATADIR_DONKEYMDL1,
    DATADIR_DAISYMDL1,
    DATADIR_WALUIGIMDL1,
};

s32 lbl_1_bss_26C[0x1B];
ZtarDllUnkStruct2 lbl_1_bss_20C;
ZtarDllUnkStruct2 lbl_1_bss_8C[4];
s32 lbl_1_bss_78[5];
s32 lbl_1_bss_74;
Process *lbl_1_bss_70;

void fn_1_7C00(void)
{
    s16 var_r31;
    s32 var_r30;

    CharKill(-1);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayerCfg[var_r31].character < 8) {
            var_r30 = HuDataDirReadAsync(lbl_1_data_3C8[GWPlayerCfg[var_r31].character]);
            if (var_r30 != -1) {
                while (HuDataGetAsyncStat(var_r30) == 0) {
                    HuPrcVSleep();
                }
            }
            CharARAMOpen(GWPlayerCfg[var_r31].character);
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayerCfg[var_r31].character < 8) {
            var_r30 = HuDataDirReadAsync(lbl_1_data_3E8[GWPlayerCfg[var_r31].character]);
            if (var_r30 != -1) {
                while (HuDataGetAsyncStat(var_r30) == 0) {
                    HuPrcVSleep();
                }
            }
        }
    }
    lbl_1_bss_4 = 0;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_7D6C(Process *arg0)
{
    s32 var_r31;

    lbl_1_bss_70 = arg0;
    fn_1_A02C();
    fn_1_BA40();
    fn_1_FB38();
    HuPrcChildCreate(fn_1_10A80, 0x3E8, 0x2000, 0, lbl_1_bss_70);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuPrcChildCreate(fn_1_10B24, 0x3E8, 0x2000, 0, lbl_1_bss_70);
    }
}

s32 fn_1_7E0C(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r29 = -1;
    fn_1_A610();
    fn_1_11020();
    fn_1_11264(MAKE_MESSID(0x1A, 0x05), -1, -1);
    fn_1_10FBC(1);
    fn_1_11708(MAKE_MESSID(0x33, 0x91));
    lbl_1_bss_20C.unk_04 = (ZtarUnkFunc)fn_1_AEE4;
    var_r29 = -1;
    while (TRUE) {
        fn_1_10FBC(1);
        var_r30 = 0;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_8C[var_r31].unk_14 == 0) {
                var_r30++;
            }
        }
        if (var_r29 != var_r30) {
            var_r29 = var_r30;
            fn_1_11264(var_r30 + MAKE_MESSID(0x1A, 0x1B), -1, 1);
        }
        if (lbl_1_bss_20C.unk_28 == 0) {
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                HuAudFXPlay(2);
                var_r28 = 1;
                break;
            }
            else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                var_r28 = 0;
                break;
            }
        }
    }
    fn_1_AE94();
    lbl_1_bss_20C.unk_04 = NULL;
    fn_1_1190C();
    if (var_r28 == 1) {
        var_r27 = 0;
        var_r26 = 0;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_8C[var_r31].unk_50 == 0) {
                var_r27++;
            }
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (var_r26 < var_r27) {
                if (HuPadStatGet(var_r31) != -1) {
                    lbl_1_bss_8C[var_r31].unk_50 = 0;
                    var_r26++;
                }
                else {
                    lbl_1_bss_8C[var_r31].unk_50 = 1;
                }
            }
            else {
                lbl_1_bss_8C[var_r31].unk_50 = 1;
            }
        }
    }
    fn_1_111E0();
    fn_1_ABC4();
    return var_r28;
}

s32 fn_1_8030(s32 arg0, s32 arg1)
{
    s32 sp10;
    s32 spC;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r27;

    sp10 = 0;
    spC = 0;
    var_r30 = 0;
    if (arg1 == 1) {
        var_r30 = 1;
        for (var_r31 = 1; var_r31 < 4; var_r31++) {
            lbl_1_bss_8C[var_r31].unk_50 = 1;
        }
    }
    else {
        var_r30 = 4;
    }
    fn_1_CAF0();
    if (arg0 == 0) {
        fn_1_C4B8(0);
    }
    fn_1_11020();
    fn_1_10FBC(1);
    if (arg1 == 1) {
        fn_1_11264(MAKE_MESSID(0x1E, 0x5E), -1, -1);
    }
    else {
        fn_1_11264(MAKE_MESSID(0x1A, 0x09), -1, -1);
    }
    fn_1_11708(MAKE_MESSID(0x33, 0x92));
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        if (lbl_1_bss_8C[var_r31].unk_50 == 0) {
            lbl_1_bss_8C[var_r31].unk_04 = (ZtarUnkFunc)fn_1_D280;
        }
    }
    while (TRUE) {
        fn_1_10FBC(1);
        if ((lbl_1_bss_8C[0].unk_08 == 0) && (HuPadBtnDown[0] & PAD_BUTTON_B) != 0) {
            HuAudFXPlay(3);
            if (lbl_1_bss_20C.unk_10 == 1) {
                lbl_1_bss_20C.unk_10 = 0;
                continue;
            }
            var_r27 = 0;
            break;
        }
        else {
            for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
                if ((lbl_1_bss_8C[var_r31].unk_50 == 0) && (lbl_1_bss_8C[var_r31].unk_08 != 1)) {
                    break;
                }
            }
            if (var_r31 == var_r30) {
                var_r27 = 2;
                break;
            }
        }
    }
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        lbl_1_bss_8C[var_r31].unk_04 = NULL;
    }
    fn_1_1190C();
    fn_1_111E0();
    if (var_r27 == 0) {
        fn_1_C8EC(0);
        return 0;
    }
    var_r29 = 0;
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        if (lbl_1_bss_8C[var_r31].unk_50 != 0) {
            lbl_1_bss_8C[var_r31].unk_5C = 0;
            var_r29++;
        }
    }
    if ((var_r29 == 0) || ((arg1 == 2) && (var_r29 == 2))) {
        fn_1_C8EC(0);
        return 2;
    }
    if (arg1 == 2) {
        lbl_1_bss_8C[1].unk_4C = 0;
    }
    return 1;
}

void fn_1_830C(s32 arg0)
{
    fn_1_8030(arg0, 4);
}

s32 fn_1_8338(s32 arg0, s32 arg1)
{
    s32 spC;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    var_r30 = -1;
    var_r27 = -1;
    var_r26 = -1;
    var_r24 = -1;
    spC = 0;
    if (arg0 != 0) {
        if (arg1 == 2) {
            fn_1_C06C(0, 2);
        }
        else {
            fn_1_C06C(0, 1);
        }
    }
    fn_1_11020();
    while (TRUE) {
        fn_1_10FBC(1);
        var_r25 = 0;
        for (var_r31 = 0; var_r31 < arg1; var_r31++) {
            if ((lbl_1_bss_8C[var_r31].unk_50 != 0) && (lbl_1_bss_8C[var_r31].unk_08 == 0)) {
                var_r25++;
            }
        }
        if (var_r26 == -1) {
            fn_1_11338(var_r25 + MAKE_MESSID(0x1A, 0x23), 1);
            fn_1_11264(MAKE_MESSID(0x1A, 0x28), -1, var_r26);
        }
        else {
            fn_1_11338(var_r25 + MAKE_MESSID(0x1A, 0x23), 1);
            fn_1_11264(MAKE_MESSID(0x1A, 0x28), -1, var_r26);
        }
        var_r26 = 1;
        fn_1_11708(MAKE_MESSID(0x33, 0x92));
        for (var_r31 = 0; var_r31 < arg1; var_r31++) {
            if ((lbl_1_bss_8C[var_r31].unk_50 != 0) && (lbl_1_bss_8C[var_r31].unk_08 == 0)) {
                var_r30 = var_r31;
                lbl_1_bss_8C[var_r31].unk_0C = var_r27;
                fn_1_DD8C(&lbl_1_bss_8C[var_r31]);
                lbl_1_bss_8C[var_r31].unk_04 = (ZtarUnkFunc)fn_1_E548;
                break;
            }
        }
        while (TRUE) {
            fn_1_10FBC(1);
            if (((HuPadBtnDown[lbl_1_bss_8C[0].unk_58] & 0x200) != 0) && (lbl_1_bss_8C[var_r30].unk_08 == 0) && (lbl_1_bss_20C.unk_30 == 0)) {
                HuAudFXPlay(3);
                if (var_r27 == -1) {
                    var_r29 = 0;
                }
                else {
                    var_r29 = 1;
                }
                break;
            }
            else if (lbl_1_bss_8C[var_r30].unk_08 == 1) {
                for (var_r31 = 0; var_r31 < arg1; var_r31++) {
                    if (lbl_1_bss_8C[var_r31].unk_08 == 0) {
                        lbl_1_bss_8C[var_r31].unk_5C = 0;
                    }
                }
                lbl_1_bss_8C[var_r30].unk_04 = NULL;
                fn_1_11264(MAKE_MESSID(0x1A, 0x22), -1, 1);
                fn_1_10FBC(1);
                fn_1_11708(MAKE_MESSID(0x33, 0x93));
                var_r29 = fn_1_F214(&lbl_1_bss_8C[var_r30]);
                if (var_r29 == 1) {
                    HuAudFXPlay(2);
                    lbl_1_bss_8C[var_r30].unk_10 = 1;
                    var_r29 = 4;
                    var_r27 = var_r30;
                }
                else {
                    HuAudFXPlay(3);
                    lbl_1_bss_8C[var_r30].unk_10 = 0;
                    var_r29 = 4;
                    lbl_1_bss_8C[var_r30].unk_08 = 0;
                    fn_1_E4AC(&lbl_1_bss_8C[var_r30]);
                    fn_1_DD8C(&lbl_1_bss_8C[var_r30]);
                }
                break;
            }
        }
        for (var_r31 = 0; var_r31 < arg1; var_r31++) {
            lbl_1_bss_8C[var_r31].unk_04 = NULL;
        }
        for (var_r31 = 0; var_r31 < arg1; var_r31++) {
            if (lbl_1_bss_8C[var_r31].unk_08 == 0) {
                break;
            }
        }
        if (var_r31 == arg1) {
            var_r29 = 3;
            break;
        }
        else {
            if (var_r29 == 1) {
                fn_1_DD8C(&lbl_1_bss_8C[var_r30]);
                fn_1_E4AC(&lbl_1_bss_8C[var_r30]);
                fn_1_DD8C(&lbl_1_bss_8C[lbl_1_bss_8C[var_r30].unk_0C]);
                var_r27 = lbl_1_bss_8C[lbl_1_bss_8C[var_r30].unk_0C].unk_0C;
                lbl_1_bss_8C[lbl_1_bss_8C[var_r30].unk_0C].unk_08 = 0;
            }
            else if (var_r29 != 4) {
                if (var_r29 == 0) {
                    fn_1_E4AC(&lbl_1_bss_8C[var_r30]);
                }
                break;
            }
            var_r24 = -1;
        }
    }

    fn_1_1190C();
    fn_1_111E0();
    if (var_r29 != 0) {
        fn_1_C8EC(0);
    }
    return var_r29;
}

void fn_1_8850(s32 arg0)
{
    fn_1_8338(arg0, 4);
}

void fn_1_887C(void)
{
    fn_1_8030(0, 1);
}

s32 fn_1_88A4(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r26 = -1;
    fn_1_A8E8();
    fn_1_11020();
    fn_1_11264(MAKE_MESSID(0x1A, 0x05), -1, -1);
    fn_1_10FBC(1);
    fn_1_11708(MAKE_MESSID(0x33, 0x91));
    lbl_1_bss_20C.unk_04 = (ZtarUnkFunc)fn_1_B468;
    while (TRUE) {
        fn_1_10FBC(1);
        var_r30 = 0;
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            if (lbl_1_bss_8C[var_r31].unk_14 == 0) {
                var_r30++;
            }
        }
        if (var_r26 != var_r30) {
            var_r26 = var_r30;
            fn_1_11264(var_r30 + MAKE_MESSID(0x33, 0x93), -1, 1);
        }
        if (lbl_1_bss_20C.unk_28 != 0) {
            continue;
        }
        if ((*HuPadBtnDown & PAD_BUTTON_A) != 0) {
            HuAudFXPlay(2);
            var_r28 = 1;
            break;
        }
        else if ((*HuPadBtnDown & PAD_BUTTON_B) != 0) {
            HuAudFXPlay(3);
            var_r28 = 0;
            break;
        }
    }
    fn_1_AE94();
    lbl_1_bss_20C.unk_04 = NULL;
    fn_1_1190C();
    if (var_r28 == 1) {
        var_r29 = 0;
        var_r27 = 0;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_8C[var_r31].unk_50 == 0) {
                var_r29++;
            }
        }
        if (var_r29 >= 2) {
            var_r29 = 2;
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (var_r27 < var_r29) {
                if (HuPadStatGet(var_r31) != -1) {
                    lbl_1_bss_8C[var_r31].unk_50 = 0;
                    lbl_1_bss_8C[var_r31].unk_4C = 0;
                    var_r27++;
                }
                else {
                    lbl_1_bss_8C[var_r31].unk_50 = 1;
                    lbl_1_bss_8C[var_r31].unk_4C = 1;
                }
            }
            else {
                lbl_1_bss_8C[var_r31].unk_50 = 1;
                lbl_1_bss_8C[var_r31].unk_4C = 1;
            }
        }
    }
    fn_1_111E0();
    fn_1_ABC4();
    return var_r28;
}

void fn_1_8B18(s32 arg0)
{
    fn_1_8030(arg0, 2);
}

void fn_1_8B44(s32 arg0)
{
    fn_1_8338(arg0, 2);
}

void fn_1_8B70(void)
{
    fn_1_7E0C(0);
}

s32 fn_1_8B94(s32 arg0)
{
    s32 sp10;
    s32 spC;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    sp10 = 0;
    spC = 0;
    var_r30 = 4;
    var_r28 = 4;
    if (var_r28 == 1) {
        var_r30 = 1;
        for (var_r31 = 1; var_r31 < 4; var_r31++) {
            lbl_1_bss_8C[var_r31].unk_50 = 1;
        }
    }
    else {
        var_r30 = 4;
    }
    fn_1_CAF0();
    if (arg0 == 0) {
        fn_1_C4B8(3);
    }
    fn_1_11020();
    fn_1_10FBC(1);
    fn_1_11264(MAKE_MESSID(0x1A, 0x09), -1, -1);
    fn_1_11708(MAKE_MESSID(0x33, 0x92));
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        if (lbl_1_bss_8C[var_r31].unk_50 == 0) {
            lbl_1_bss_8C[var_r31].unk_04 = (ZtarUnkFunc)fn_1_D280;
        }
    }
    while (TRUE) {
        fn_1_10FBC(1);
        if ((lbl_1_bss_8C[0].unk_08 == 0) && ((*HuPadBtnDown & 0x200) != 0)) {
            HuAudFXPlay(3);
            if (lbl_1_bss_20C.unk_10 == 1) {
                lbl_1_bss_20C.unk_10 = 0;
                continue;
            }
            var_r27 = 0;
            break;
        }
        else {
            for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
                if ((lbl_1_bss_8C[var_r31].unk_50 == 0) && (lbl_1_bss_8C[var_r31].unk_08 != 1)) {
                    break;
                }
            }
            if (var_r31 == var_r30) {
                var_r27 = 2;
                break;
            }
        }
    }
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        lbl_1_bss_8C[var_r31].unk_04 = NULL;
    }
    fn_1_1190C();
    fn_1_111E0();
    if (var_r27 == 0) {
        fn_1_C8EC(0);
        return 0;
    }
    var_r29 = 0;
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        if (lbl_1_bss_8C[var_r31].unk_50 != 0) {
            lbl_1_bss_8C[var_r31].unk_5C = 1;
            var_r29++;
        }
    }
    if ((var_r29 == 0) || ((var_r28 == 2) && (var_r29 == 2))) {
        fn_1_C8EC(3);
        return 2;
    }
    if (var_r28 == 2) {
        lbl_1_bss_8C[1].unk_4C = 0;
    }
    return 1;
}

s32 fn_1_8E50(s32 arg0)
{
    s32 spC;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    var_r30 = -1;
    var_r27 = -1;
    var_r26 = -1;
    var_r28 = 4;
    var_r24 = -1;
    spC = 0;
    if (arg0 != 0) {
        fn_1_C06C(3, 3);
    }
    fn_1_11020();
    while (TRUE) {
        fn_1_10FBC(1);
        var_r25 = 0;
        for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
            if ((lbl_1_bss_8C[var_r31].unk_50 != 0) && (lbl_1_bss_8C[var_r31].unk_08 == 0)) {
                var_r25++;
            }
        }
        if (var_r26 == -1) {
            fn_1_11338(var_r25 + MAKE_MESSID(0x1A, 0x23), 1);
            fn_1_11264(MAKE_MESSID(0x1A, 0x28), -1, var_r26);
        }
        else {
            fn_1_11338(var_r25 + MAKE_MESSID(0x1A, 0x23), 1);
            fn_1_11264(MAKE_MESSID(0x1A, 0x28), -1, var_r26);
        }
        var_r26 = 1;
        fn_1_11708(MAKE_MESSID(0x33, 0x92));
        for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
            if ((lbl_1_bss_8C[var_r31].unk_50 != 0) && (lbl_1_bss_8C[var_r31].unk_08 == 0)) {
                var_r30 = var_r31;
                lbl_1_bss_8C[var_r31].unk_0C = var_r27;
                fn_1_DD8C(&lbl_1_bss_8C[var_r31]);
                lbl_1_bss_8C[var_r31].unk_04 = (ZtarUnkFunc)fn_1_E548;
                break;
            }
        }
        while (TRUE) {
            fn_1_10FBC(1);
            if ((HuPadBtnDown[lbl_1_bss_8C[0].unk_58] & PAD_BUTTON_B) && (lbl_1_bss_8C[var_r30].unk_08 == 0) && (lbl_1_bss_20C.unk_30 == 0)) {
                HuAudFXPlay(3);
                if (var_r27 == -1) {
                    var_r29 = 0;
                }
                else {
                    var_r29 = 1;
                }
                break;
            }
            else if (lbl_1_bss_8C[var_r30].unk_08 == 1) {
                for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
                    if (lbl_1_bss_8C[var_r31].unk_08 == 0) {
                        lbl_1_bss_8C[var_r31].unk_5C = 1;
                    }
                }
                lbl_1_bss_8C[var_r30].unk_04 = NULL;
                fn_1_11264(MAKE_MESSID(0x1A, 0x22), -1, 1);
                fn_1_10FBC(1);
                fn_1_11708(MAKE_MESSID(0x33, 0x93));
                var_r29 = fn_1_F214(&lbl_1_bss_8C[var_r30]);
                if (var_r29 == 1) {
                    HuAudFXPlay(2);
                    lbl_1_bss_8C[var_r30].unk_10 = 1;
                    var_r29 = 4;
                    var_r27 = var_r30;
                }
                else {
                    HuAudFXPlay(3);
                    lbl_1_bss_8C[var_r30].unk_10 = 0;
                    var_r29 = 4;
                    lbl_1_bss_8C[var_r30].unk_08 = 0;
                    fn_1_E4AC(&lbl_1_bss_8C[var_r30]);
                    fn_1_DD8C(&lbl_1_bss_8C[var_r30]);
                }
                break;
            }
        }
        for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
            lbl_1_bss_8C[var_r31].unk_04 = NULL;
        }
        for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
            if (lbl_1_bss_8C[var_r31].unk_08 == 0) {
                break;
            }
        }
        if (var_r31 == var_r28) {
            var_r29 = 3;
            break;
        }
        else {
            if (var_r29 == 1) {
                fn_1_DD8C(&lbl_1_bss_8C[var_r30]);
                fn_1_E4AC(&lbl_1_bss_8C[var_r30]);
                fn_1_DD8C(&lbl_1_bss_8C[lbl_1_bss_8C[var_r30].unk_0C]);
                var_r27 = lbl_1_bss_8C[lbl_1_bss_8C[var_r30].unk_0C].unk_0C;
                lbl_1_bss_8C[lbl_1_bss_8C[var_r30].unk_0C].unk_08 = 0;
            }
            else if (var_r29 == 4) {
            }
            else if (var_r29 == 0) {
                fn_1_E4AC(&lbl_1_bss_8C[var_r30]);
                break;
            }
            else {
                break;
            }
            var_r24 = -1;
        }
    }
    fn_1_1190C();
    fn_1_111E0();
    if (var_r29 != 0) {
        fn_1_C8EC(3);
    }
    return var_r29;
}

void fn_1_9350(s32 arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GWPlayer[var_r31].team = GWPlayerCfg[var_r31].group = lbl_1_bss_8C[var_r31].unk_4C;
        GWPlayer[var_r31].com = GWPlayerCfg[var_r31].iscom = lbl_1_bss_8C[var_r31].unk_50;
        GWPlayer[var_r31].diff = GWPlayerCfg[var_r31].diff = lbl_1_bss_8C[var_r31].unk_54;
        if (lbl_1_bss_74 != 0) {
            if (lbl_1_bss_8C[var_r31].unk_5C <= 5) {
                GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = lbl_1_bss_8C[var_r31].unk_5C - 1;
            }
            else if (lbl_1_bss_8C[var_r31].unk_5C <= 0xB) {
                GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = lbl_1_bss_8C[var_r31].unk_5C - 3;
            }
            else {
                GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = fn_1_10C98(lbl_1_bss_8C[var_r31].unk_5C - 4);
            }
        }
        else if (arg0 == 1) {
            if (var_r31 != 0) {
                lbl_1_bss_8C[var_r31].unk_5C = lbl_1_bss_8C[var_r31 - 1].unk_5C + 1;
                if (lbl_1_bss_8C[var_r31].unk_5C >= 8) {
                    lbl_1_bss_8C[var_r31].unk_5C = 0;
                }
            }
            GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = lbl_1_bss_8C[var_r31].unk_5C;
        }
        else {
            GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = lbl_1_bss_8C[var_r31].unk_5C;
        }
        GWPlayer[var_r31].port = GWPlayerCfg[var_r31].pad_idx = lbl_1_bss_8C[var_r31].unk_58;
    }
    OSReport("\n\n#################### SET PLAYERDATA ####################\n");
    OSReport("ID) GRP:COM:DIF:CHR:PAD\n");
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        OSReport("%2d) %3d:%3d:%3d:%3d:%3d\n", var_r31, GWPlayerCfg[var_r31].group, GWPlayerCfg[var_r31].iscom, GWPlayerCfg[var_r31].diff,
            GWPlayerCfg[var_r31].character, GWPlayerCfg[var_r31].pad_idx);
    }
    OSReport("########################################################\n");
}

s32 lbl_1_data_4B4[4][2] = {
    { -0x69, 0 },
    { -0x23, 0 },
    { 0x23, 0 },
    { 0x69, 0 },
};
s32 lbl_1_data_4D4[8][2] = {
    { -0x7B, -0x34 },
    { -0x29, -0x34 },
    { 0x29, -0x34 },
    { 0x7B, -0x34 },
    { -0x7B, 0x34 },
    { -0x29, 0x34 },
    { 0x29, 0x34 },
    { 0x7B, 0x34 },
};
s32 lbl_1_data_514[0xE][2] = {
    { -0x7B, -0x66 },
    { -0x29, -0x66 },
    { 0x29, -0x66 },
    { 0x7B, -0x66 },
    { -0x7B, 0 },
    { -0x29, 0 },
    { 0x29, 0 },
    { 0x7B, 0 },
    { -0xCD, 0x66 },
    { -0x7B, 0x66 },
    { -0x29, 0x66 },
    { 0x29, 0x66 },
    { 0x7B, 0x66 },
    { 0xCD, 0x66 },
};
s32 lbl_1_data_584[0x12][2] = {
    { 0, 0 },
    { -0x7B, -0x66 },
    { -0x29, -0x66 },
    { 0x29, -0x66 },
    { 0x7B, -0x66 },
    { 0, 0 },
    { 0, 0 },
    { -0x7B, 0 },
    { -0x29, 0 },
    { 0x29, 0 },
    { 0x7B, 0 },
    { 0, 0 },
    { -0xCD, 0x66 },
    { -0x7B, 0x66 },
    { -0x29, 0x66 },
    { 0x29, 0x66 },
    { 0x7B, 0x66 },
    { 0xCD, 0x66 },
};
s32 lbl_1_data_614[4][2] = {
    { -0x45, -8 },
    { -0x17, -8 },
    { 0x17, -8 },
    { 0x45, -8 },
};
s32 lbl_1_data_634[2] = { 0, 0xFFFFFFF8 };
s32 lbl_1_data_63C[2][2] = {
    { -0x17, -8 },
    { 0x17, -8 },
};
s32 lbl_1_data_64C[4][2] = {
    { -0x59, -8 },
    { -0x2B, -8 },
    { 0x2B, -8 },
    { 0x59, -8 },
};
s32 lbl_1_data_66C = -1;
s32 lbl_1_data_670 = -1;

s32 fn_1_97D0(s32 arg0, s32 arg1)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;
    s32 var_r18;

    var_r30 = 0;
    var_r27 = 0;
    var_r26 = 0;
    var_r29 = arg0;
    if (arg0 == 3) {
        lbl_1_bss_74 = 1;
    }
    else {
        lbl_1_bss_74 = 0;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_8C[var_r31].unk_48 = var_r31;
        lbl_1_bss_8C[var_r31].unk_4C = 0;
        lbl_1_bss_8C[var_r31].unk_50 = 0;
        lbl_1_bss_8C[var_r31].unk_54 = 0;
        if (lbl_1_bss_74 != 0) {
            lbl_1_bss_8C[var_r31].unk_5C = var_r31 + 1;
        }
        else {
            lbl_1_bss_8C[var_r31].unk_5C = var_r31;
        }
        lbl_1_bss_8C[var_r31].unk_58 = var_r31;
    }
    if (arg1 == 1) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            lbl_1_bss_8C[var_r31].unk_48 = var_r31;
            lbl_1_bss_8C[var_r31].unk_4C = GWPlayerCfg[var_r31].group;
            lbl_1_bss_8C[var_r31].unk_50 = GWPlayerCfg[var_r31].iscom;
            lbl_1_bss_8C[var_r31].unk_54 = GWPlayerCfg[var_r31].diff;
            lbl_1_bss_8C[var_r31].unk_5C = GWPlayerCfg[var_r31].character;
            lbl_1_bss_8C[var_r31].unk_58 = GWPlayerCfg[var_r31].pad_idx;
            lbl_1_bss_8C[var_r31].unk_08 = lbl_1_bss_8C[var_r31].unk_0C = lbl_1_bss_8C[var_r31].unk_10 = lbl_1_bss_8C[var_r31].unk_14 = 0;
            lbl_1_bss_8C[var_r31].unk_28 = lbl_1_bss_8C[var_r31].unk_2C = lbl_1_bss_8C[var_r31].unk_30 = lbl_1_bss_8C[var_r31].unk_34 = 0;
            switch (arg0) {
                case 0:
                    if (lbl_1_bss_8C[var_r31].unk_50 == 0) {
                        lbl_1_bss_8C[var_r31].unk_08 = 1;
                    }
                    else {
                        var_r27 = 1;
                    }
                    break;
                case 2:
                    if (lbl_1_bss_8C[var_r31].unk_50 == 0) {
                        lbl_1_bss_8C[var_r31].unk_08 = 1;
                        var_r26++;
                    }
                    else {
                        var_r27 = 1;
                    }
                    break;
                case 3:
                    if (lbl_1_bss_8C[var_r31].unk_50 == 0) {
                        lbl_1_bss_8C[var_r31].unk_08 = 1;
                        var_r26++;
                    }
                    else {
                        var_r27 = 1;
                    }
                    if (lbl_1_bss_8C[var_r31].unk_5C <= 3) {
                        lbl_1_bss_8C[var_r31].unk_5C++;
                    }
                    else if (lbl_1_bss_8C[var_r31].unk_5C <= 7) {
                        lbl_1_bss_8C[var_r31].unk_5C += 3;
                    }
                    else {
                        lbl_1_bss_8C[var_r31].unk_5C = fn_1_10C18(lbl_1_bss_8C[var_r31].unk_5C) + 4;
                    }
                    break;
            }
        }
        switch (arg0) {
            case 0:
                if (var_r27 == 1) {
                    var_r29 = 0x66;
                    var_r30 = 1;
                }
                else {
                    var_r29 = 0x65;
                    var_r30 = 0;
                }
                break;
            case 1:
                var_r29 = 0xC8;
                break;
            case 2:
                if ((var_r27 == 1) && (var_r26 == 1)) {
                    var_r29 = 0x12E;
                    var_r30 = 1;
                }
                else {
                    var_r29 = 0x12D;
                    var_r30 = 0;
                }
                break;
            case 3:
                if (var_r27 == 1) {
                    var_r29 = 0x192;
                    var_r30 = 1;
                }
                else {
                    var_r29 = 0x191;
                    var_r30 = 0;
                }
                break;
        }
    }
    while (TRUE) {
        fn_1_10FBC(1);
        if (var_r28 == 0x3E7) {
            break;
        }
        switch (var_r29) {
            case 0x0:
                var_r29 = 0x64;
                break;
            case 0x1:
                var_r29 = 0xC8;
                break;
            case 0x2:
                var_r29 = 0x12C;
                break;
            case 0x3:
                var_r29 = 0x190;
                break;
            case 0x64:
                var_r28 = fn_1_7E0C(var_r30);
                if (var_r28 != 0) {
                    var_r29 = 0x65;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x385;
                    var_r30 = 1;
                }
                break;
            case 0x65:
                var_r23 = fn_1_8030(var_r30, 4);
                var_r28 = var_r23;
                if (var_r28 == 1) {
                    var_r29 = 0x66;
                    var_r30 = 0;
                }
                else if (var_r28 == 2) {
                    var_r29 = 0x384;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x64;
                    var_r30 = 1;
                }
                break;
            case 0x66:
                var_r22 = fn_1_8338(var_r30, 4);
                var_r28 = var_r22;
                var_r28 = var_r28;
                if (var_r28 != 0) {
                    var_r29 = 0x384;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x65;
                    var_r30 = 1;
                }
                break;
            case 0xC8:
                var_r21 = fn_1_8030(0, 1);
                var_r28 = var_r21;
                if (var_r28 != 0) {
                    var_r29 = 0x384;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x385;
                    var_r30 = 1;
                }
                break;
            case 0x12C:
                var_r28 = fn_1_88A4();
                if (var_r28 != 0) {
                    var_r29 = 0x12D;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x385;
                    var_r30 = 1;
                }
                break;
            case 0x12D:
                var_r20 = fn_1_8030(var_r30, 2);
                var_r28 = var_r20;
                if (var_r28 == 1) {
                    var_r29 = 0x12E;
                    var_r30 = 0;
                }
                else if (var_r28 == 2) {
                    var_r29 = 0x384;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x12C;
                    var_r30 = 1;
                }
                break;
            case 0x12E:
                var_r19 = fn_1_8338(var_r30, 2);
                var_r28 = var_r19;
                if (var_r28 != 0) {
                    var_r29 = 0x384;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x12D;
                    var_r30 = 1;
                }
                break;
            case 0x190:
                var_r18 = fn_1_7E0C(0);
                var_r28 = var_r18;
                if (var_r28 != 0) {
                    var_r29 = 0x191;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x385;
                    var_r30 = 1;
                }
                break;
            case 0x191:
                var_r28 = fn_1_8B94(var_r30);
                if (var_r28 == 1) {
                    var_r29 = 0x192;
                    var_r30 = 0;
                }
                else if (var_r28 == 2) {
                    var_r29 = 0x384;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x190;
                    var_r30 = 1;
                }
                break;
            case 0x192:
                var_r28 = fn_1_8E50(var_r30);
                if (var_r28 != 0) {
                    var_r29 = 0x384;
                    var_r30 = 0;
                }
                else {
                    var_r29 = 0x191;
                    var_r30 = 1;
                }
                break;
            case 0x384:
                fn_1_9350(arg0);
                var_r24 = 1;
                var_r28 = 0x3E7;
                break;
            case 0x385:
                var_r24 = 0;
                var_r28 = 0x3E7;
                break;
        }
    }
    return var_r24;
}

void fn_1_9FDC(s32 arg0)
{
    fn_1_10764(arg0);
}

void fn_1_A004(s32 arg0)
{
    fn_1_108C8(arg0);
}

void fn_1_A02C(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r28;

    var_r30 = HuSprGrpCreate(0xB);
    lbl_1_bss_26C[0] = var_r30;
    var_r29 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x46)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r30, 0, var_r29);
    HuSprPosSet(var_r30, 0, 0.0f, 0.0f);
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x47));
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r29 = HuSprCreate(var_r28, 0x3E8, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 1, var_r29);
        HuSprBankSet(var_r30, var_r31 + 1, var_r31);
    }
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x48));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = HuSprCreate(var_r28, 0x76C, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 3, var_r29);
        HuSprPosSet(var_r30, var_r31 + 3, lbl_1_data_4B4[var_r31 % 4][0], lbl_1_data_4B4[0][1]);
        HuSprBankSet(var_r30, var_r31 + 3, 0);
    }
    fn_1_A248();
    fn_1_A574();
}

void fn_1_A248(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_26C[0];
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprAttrReset(var_r30, 0, 4);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 3, 4);
        HuSprPosSet(var_r30, var_r31 + 3, lbl_1_data_4B4[var_r31 % 4][0], lbl_1_data_4B4[0][1]);
        HuSprBankSet(var_r30, var_r31 + 3, 0);
    }
    HuSprGrpPosSet(var_r30, 288.0f, -390.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_8C[var_r31].unk_14 = lbl_1_bss_8C[var_r31].unk_50 = 0;
    }
}

void fn_1_A3DC(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_26C[0];
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprAttrReset(var_r30, 0, 4);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 3, 4);
        HuSprPosSet(var_r30, var_r31 + 3, lbl_1_data_4B4[var_r31 % 4 + 1][0], lbl_1_data_4B4[0][1]);
        HuSprBankSet(var_r30, var_r31 + 3, 0);
    }
    HuSprGrpPosSet(var_r30, 288.0f, -390.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_8C[var_r31].unk_14 = lbl_1_bss_8C[var_r31].unk_50 = 0;
    }
}

void fn_1_A574(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_26C[0];
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprGrpPosSet(var_r30, 288.0f, 110.0f);
    HuSprGrpScaleSet(var_r30, 1.0f, 1.0f);
}

void fn_1_A610(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_26C[0];
    var_r29 = lbl_1_bss_26C[0];
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r29, var_r31, 4);
    }
    HuSprAttrReset(var_r29, 0, 4);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprAttrReset(var_r29, var_r31 + 3, 4);
        HuSprPosSet(var_r29, var_r31 + 3, lbl_1_data_4B4[var_r31 % 4][0], lbl_1_data_4B4[0][1]);
        HuSprBankSet(var_r29, var_r31 + 3, 0);
    }
    HuSprGrpPosSet(var_r29, 288.0f, -390.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_8C[var_r31].unk_14 = lbl_1_bss_8C[var_r31].unk_50 = 0;
    }
    for (var_r30 = 0; var_r30 <= 0x3C; var_r30++) {
        fn_1_10FBC(1);
        if (var_r30 <= 0x32) {
            var_f31 = fn_1_10E38(-500.0f, 10.0f, var_r30, 50.0f);
        }
        else {
            var_f31 = fn_1_10D60(10.0f, 0.0f, var_r30 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r28, 288.0f, 110.0f + var_f31);
    }
    HuSprGrpPosSet(var_r28, 288.0f, 110.0f);
    fn_1_10FBC(0xA);
}

void fn_1_A8E8(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_26C[0];
    var_r29 = lbl_1_bss_26C[0];
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r29, var_r31, 4);
    }
    HuSprAttrReset(var_r29, 0, 4);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrReset(var_r29, var_r31 + 3, 4);
        HuSprPosSet(var_r29, var_r31 + 3, lbl_1_data_4B4[var_r31 % 4 + 1][0], lbl_1_data_4B4[0][1]);
        HuSprBankSet(var_r29, var_r31 + 3, 0);
    }
    HuSprGrpPosSet(var_r29, 288.0f, -390.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_8C[var_r31].unk_14 = lbl_1_bss_8C[var_r31].unk_50 = 0;
    }
    for (var_r30 = 0; var_r30 <= 0x3C; var_r30++) {
        fn_1_10FBC(1);
        if (var_r30 <= 0x32) {
            var_f31 = fn_1_10E38(-500.0f, 10.0f, var_r30, 50.0f);
        }
        else {
            var_f31 = fn_1_10D60(10.0f, 0.0f, var_r30 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r28, 288.0f, 110.0f + var_f31);
    }
    HuSprGrpPosSet(var_r28, 288.0f, 110.0f);
    fn_1_10FBC(0xA);
}
void fn_1_ABC4(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_26C[0];
    fn_1_10FBC(0xA);
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_10FBC(1);
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_10E38(0.0f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_10D60(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(var_r28, 288.0f, 110.0f + var_f31);
    }
    HuSprGrpPosSet(var_r28, 288.0f, -390.0f);
    var_r29 = lbl_1_bss_26C[0];
    for (var_r30 = 0; var_r30 < 0xB; var_r30++) {
        HuSprAttrSet(var_r29, var_r30, 4);
    }
    HuSprGrpPosSet(var_r29, 288.0f, 110.0f);
    HuSprGrpScaleSet(var_r29, 1.0f, 1.0f);
}

void fn_1_ADA4(s32 arg0)
{
    s32 var_r31 = lbl_1_bss_26C[0];
    HuSprAttrReset(var_r31, 1, 4);
    HuSprAttrReset(var_r31, 2, 4);
    HuSprPosSet(var_r31, 1, -155.0f, 0.0f);
    HuSprPosSet(var_r31, 2, 155.0f, 0.0f);
    if (arg0 == 2) {
        HuSprPosSet(var_r31, 1, -80.0f, 0.0f);
        HuSprPosSet(var_r31, 2, 80.0f, 0.0f);
    }
}

void fn_1_AE94(void)
{
    s32 var_r31 = lbl_1_bss_26C[0];
    HuSprAttrSet(var_r31, 1, 4);
    HuSprAttrSet(var_r31, 2, 4);
}

void fn_1_AEE4(omObjData *object, ZtarDllUnkStruct2 *arg1)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    var_r27 = lbl_1_bss_26C[0];
    var_r29 = var_r28 = var_r26 = var_r24 = 0;
    lbl_1_bss_20C.unk_28 = 0;
    var_r29 = 1;
    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_8C[var_r31].unk_50 == 0) {
            var_r29++;
        }
    }
    var_r28 = 1;
    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        if (HuPadStatGet(var_r31) != -1) {
            var_r28++;
        }
    }
    if (var_r28 >= 2) {
        var_r25 = lbl_1_bss_26C[0];
        HuSprAttrReset(var_r25, 1, 4);
        HuSprAttrReset(var_r25, 2, 4);
        HuSprPosSet(var_r25, 1, -155.0f, 0.0f);
        HuSprPosSet(var_r25, 2, 155.0f, 0.0f);
        if (HuPadStkX[0] >= 5) {
            var_r29++;
            var_r26 = 1;
        }
        else if (HuPadStkX[0] <= -5) {
            var_r29--;
            var_r26 = -1;
        }
    }
    else {
        var_r23 = lbl_1_bss_26C[0];
        HuSprAttrSet(var_r23, 1, 4);
        HuSprAttrSet(var_r23, 2, 4);
    }
    if (var_r29 < 1) {
        var_r29 = var_r28;
    }
    else if (var_r29 > var_r28) {
        if (var_r26 == 0) {
            var_r29 = var_r28;
            var_r24 = 1;
        }
        else {
            var_r29 = 1;
        }
    }
    if ((var_r26 != 0) || (var_r24 != 0)) {
        lbl_1_bss_20C.unk_28 = 1;
        HuAudFXPlay(0);
        for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
            if (var_r31 <= 5) {
                var_f31 = fn_1_10E38(0.0f, 10.0f, var_r31, 5.0f);
                var_f30 = fn_1_10E38(1.0f, 0.0f, var_r31, 5.0f);
            }
            else {
                var_f31 = fn_1_10E38(10.0f, 0.0f, var_r31 - 5, 5.0f);
                var_f30 = fn_1_10E38(0.0f, 1.0f, var_r31 - 5, 5.0f);
            }
            if (var_r26 == 1) {
                HuSprPosSet(var_r27, 2, 3.0f + (155.0f + var_f31), 0.0f);
            }
            else if (var_r26 == -1) {
                HuSprPosSet(var_r27, 1, (-155.0f - var_f31) - 3.0f, 0.0f);
            }
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                if ((var_r30 < var_r29) && (lbl_1_bss_8C[var_r30].unk_50 == 1)) {
                    lbl_1_bss_8C[var_r30].unk_14 = 0;
                    HuSprScaleSet(var_r27, var_r30 + 3, var_f30, 1.0f);
                    if (var_r31 == 5) {
                        HuSprBankSet(var_r27, var_r30 + 3, 0);
                    }
                }
                else if ((var_r30 >= var_r29) && (lbl_1_bss_8C[var_r30].unk_50 == 0)) {
                    lbl_1_bss_8C[var_r30].unk_14 = 1;
                    HuSprScaleSet(var_r27, var_r30 + 3, var_f30, 1.0f);
                    if (var_r31 == 5) {
                        HuSprBankSet(var_r27, var_r30 + 3, 1);
                    }
                }
            }
            fn_1_10FBC(1);
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            if (var_r30 < var_r29) {
                lbl_1_bss_8C[var_r30].unk_50 = 0;
            }
            else {
                lbl_1_bss_8C[var_r30].unk_50 = 1;
            }
        }
    }
    lbl_1_bss_20C.unk_28 = 0;
}

void fn_1_B468(omObjData *object, ZtarDllUnkStruct2 *arg1)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    var_r27 = lbl_1_bss_26C[0];
    var_r29 = var_r28 = var_r26 = var_r24 = 0;
    lbl_1_bss_20C.unk_28 = 0;
    var_r29 = 1;
    for (var_r31 = 1; var_r31 < 2; var_r31++) {
        if (lbl_1_bss_8C[var_r31].unk_50 == 0) {
            var_r29++;
        }
    }
    var_r28 = 1;
    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        if (HuPadStatGet(var_r31) != -1) {
            var_r28++;
        }
    }
    if (var_r28 > 2) {
        var_r28 = 2;
    }
    if (var_r28 >= 2) {
        var_r25 = lbl_1_bss_26C[0];
        HuSprAttrReset(var_r25, 1, 4);
        HuSprAttrReset(var_r25, 2, 4);
        HuSprPosSet(var_r25, 1, -155.0f, 0.0f);
        HuSprPosSet(var_r25, 2, 155.0f, 0.0f);
        HuSprPosSet(var_r25, 1, -80.0f, 0.0f);
        HuSprPosSet(var_r25, 2, 80.0f, 0.0f);
        if (HuPadStkX[0] >= 5) {
            var_r29++;
            var_r26 = 1;
        }
        else if (HuPadStkX[0] <= -5) {
            var_r29--;
            var_r26 = -1;
        }
    }
    else {
        var_r23 = lbl_1_bss_26C[0];
        HuSprAttrSet(var_r23, 1, 4);
        HuSprAttrSet(var_r23, 2, 4);
    }
    if (var_r29 < 1) {
        var_r29 = var_r28;
    }
    else if (var_r29 > var_r28) {
        if (var_r26 == 0) {
            var_r29 = var_r28;
            var_r24 = 1;
        }
        else {
            var_r29 = 1;
        }
    }
    if ((var_r26 != 0) || (var_r24 != 0)) {
        lbl_1_bss_20C.unk_28 = 1;
        HuAudFXPlay(0);
        for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
            if (var_r31 <= 5) {
                var_f31 = fn_1_10E38(0.0f, 10.0f, var_r31, 5.0f);
                var_f30 = fn_1_10E38(1.0f, 0.0f, var_r31, 5.0f);
            }
            else {
                var_f31 = fn_1_10E38(10.0f, 0.0f, var_r31 - 5, 5.0f);
                var_f30 = fn_1_10E38(0.0f, 1.0f, var_r31 - 5, 5.0f);
            }
            if (var_r26 == 1) {
                HuSprPosSet(var_r27, 2, 3.0f + (77.0f + var_f31), 0.0f);
            }
            else if (var_r26 == -1) {
                HuSprPosSet(var_r27, 1, (-77.0f - var_f31) - 3.0f, 0.0f);
            }
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                if ((var_r30 < var_r29) && (lbl_1_bss_8C[var_r30].unk_50 == 1)) {
                    lbl_1_bss_8C[var_r30].unk_14 = 0;
                    HuSprScaleSet(var_r27, var_r30 + 3, var_f30, 1.0f);
                    if (var_r31 == 5) {
                        HuSprBankSet(var_r27, var_r30 + 3, 0);
                    }
                }
                else if ((var_r30 >= var_r29) && (lbl_1_bss_8C[var_r30].unk_50 == 0)) {
                    lbl_1_bss_8C[var_r30].unk_14 = 1;
                    HuSprScaleSet(var_r27, var_r30 + 3, var_f30, 1.0f);
                    if (var_r31 == 5) {
                        HuSprBankSet(var_r27, var_r30 + 3, 1);
                    }
                }
            }
            fn_1_10FBC(1);
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            if (var_r30 < var_r29) {
                lbl_1_bss_8C[var_r30].unk_50 = 0;
            }
            else {
                lbl_1_bss_8C[var_r30].unk_50 = 1;
            }
        }
    }
    lbl_1_bss_20C.unk_28 = 0;
}

void fn_1_BA40(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r28;
    AnimData *var_r27;

    var_r29 = HuSprGrpCreate(0x36);
    lbl_1_bss_26C[1] = var_r29;
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x4A)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r29, 0, var_r30);
    HuSprPosSet(var_r29, 0, 0.0f, 0.0f);
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x4B)), 0xBB8, 0);
    HuSprGrpMemberSet(var_r29, 1, var_r30);
    HuSprPosSet(var_r29, 1, 0.0f, 0.0f);
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x5A));
    for (var_r31 = 0; var_r31 < 0xE; var_r31++) {
        var_r30 = HuSprCreate(HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MPEX, 0x4C)), 0x76C, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 2, var_r30);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MPEX, 0x5B)), 0x384, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x1E, var_r30);
        var_r30 = HuSprCreate(HuSprAnimReadFile(var_r31 + DATA_MAKE_NUM(DATADIR_MPEX, 0x60)), 0x3E8, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x22, var_r30);
    }
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x5F));
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x64));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x384, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x26, var_r30);
        var_r30 = HuSprCreate(var_r27, 0x3E8, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x2A, var_r30);
    }
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x65));
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x66));
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x384, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x2E, var_r30);
        var_r30 = HuSprCreate(var_r27, 0x320, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x32, var_r30);
    }
    fn_1_BD7C(0);
    fn_1_BFF0(0);
}

void fn_1_BD7C(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_26C[1];
    for (var_r31 = 0; var_r31 < 0x36; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    if (arg0 != 3) {
        HuSprAttrReset(var_r30, 0, 4);
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_4D4[var_r31][0], lbl_1_data_4D4[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    else {
        HuSprAttrReset(var_r30, 1, 4);
        HuSprPosSet(var_r30, 1, 2.0f, 0.0f);
        for (var_r31 = 0; var_r31 < 0xE; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_514[var_r31][0], lbl_1_data_514[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    HuSprGrpPosSet(var_r30, 288.0f, -331.0f);
}

void fn_1_BFF0(s32 arg0)
{
    s32 var_r31;
    s32 var_r30 = lbl_1_bss_26C[1];
    for (var_r31 = 0; var_r31 < 0x36; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprGrpPosSet(var_r30, 288.0f, -331.0f);
}
void fn_1_C06C(s32 arg0, s32 arg1)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_26C[1];
    var_r30 = lbl_1_bss_26C[1];
    for (var_r31 = 0; var_r31 < 0x36; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    if (arg0 != 3) {
        HuSprAttrReset(var_r30, 0, 4);
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_4D4[var_r31][0], lbl_1_data_4D4[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    else {
        HuSprAttrReset(var_r30, 1, 4);
        HuSprPosSet(var_r30, 1, 2.0f, 0.0f);
        for (var_r31 = 0; var_r31 < 0xE; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_514[var_r31][0], lbl_1_data_514[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    HuSprGrpPosSet(var_r30, 288.0f, -331.0f);
    if (arg1 == 1) {
        fn_1_11960();
    }
    if (arg1 == 2) {
        fn_1_11C64();
    }
    if (arg1 == 3) {
        fn_1_11F68();
    }
    for (var_r29 = 0; var_r29 <= 0x3C; var_r29++) {
        fn_1_10FBC(1);
        if (var_r29 <= 0x32) {
            var_f31 = fn_1_10E38(-500.0f, 10.0f, var_r29, 50.0f);
        }
        else {
            var_f31 = fn_1_10D60(10.0f, 0.0f, var_r29 - 0x32, 10.0f);
        }
        if (lbl_1_bss_74 != 0) {
            HuSprGrpPosSet(var_r28, 288.0f, 20.0f + (169.0f + var_f31));
        }
        else {
            HuSprGrpPosSet(var_r28, 288.0f, 169.0f + var_f31);
        }
    }
    if (lbl_1_bss_74 != 0) {
        HuSprGrpPosSet(var_r28, 288.0f, 189.0f);
        return;
    }
    HuSprGrpPosSet(var_r28, 288.0f, 169.0f);
}

void fn_1_C4B8(s32 arg0)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_26C[1];
    var_r30 = lbl_1_bss_26C[1];
    for (var_r31 = 0; var_r31 < 0x36; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    if (arg0 != 3) {
        HuSprAttrReset(var_r30, 0, 4);
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_4D4[var_r31][0], lbl_1_data_4D4[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    else {
        HuSprAttrReset(var_r30, 1, 4);
        HuSprPosSet(var_r30, 1, 2.0f, 0.0f);
        for (var_r31 = 0; var_r31 < 0xE; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_514[var_r31][0], lbl_1_data_514[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    HuSprGrpPosSet(var_r30, 288.0f, -331.0f);
    for (var_r29 = 0; var_r29 <= 0x3C; var_r29++) {
        fn_1_10FBC(1);
        if (var_r29 <= 0x32) {
            var_f31 = fn_1_10E38(-500.0f, 10.0f, var_r29, 50.0f);
        }
        else {
            var_f31 = fn_1_10D60(10.0f, 0.0f, var_r29 - 0x32, 10.0f);
        }
        if (lbl_1_bss_74 != 0) {
            HuSprGrpPosSet(var_r28, 288.0f, 20.0f + (169.0f + var_f31));
        }
        else {
            HuSprGrpPosSet(var_r28, 288.0f, 169.0f + var_f31);
        }
    }
    if (lbl_1_bss_74 != 0) {
        HuSprGrpPosSet(var_r28, 288.0f, 189.0f);
        return;
    }
    HuSprGrpPosSet(var_r28, 288.0f, 169.0f);
}

void fn_1_C8EC(s32 arg0)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r29 = lbl_1_bss_26C[1];
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_10FBC(1);
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_10E38(0.0f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_10D60(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        if (lbl_1_bss_74 != 0) {
            HuSprGrpPosSet(var_r29, 288.0f, 20.0f + (169.0f + var_f31));
        }
        else {
            HuSprGrpPosSet(var_r29, 288.0f, 169.0f + var_f31);
        }
    }
    HuSprGrpPosSet(var_r29, 288.0f, -331.0f);
    var_r28 = lbl_1_bss_26C[1];
    for (var_r30 = 0; var_r30 < 0x36; var_r30++) {
        HuSprAttrSet(var_r28, var_r30, 4);
    }
    HuSprGrpPosSet(var_r28, 288.0f, -331.0f);
}

void fn_1_CAF0(void)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = lbl_1_bss_26C[1];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprBankSet(var_r30, var_r31 + 0x1E, 0);
        HuSprBankSet(var_r30, var_r31 + 0x22, 0);
        HuSprBankSet(var_r30, var_r31 + 0x26, 0);
        HuSprBankSet(var_r30, var_r31 + 0x2A, 0);
        HuSprBankSet(var_r30, var_r31 + 0x2E, 0);
        HuSprBankSet(var_r30, var_r31 + 0x32, 0);
    }
    if (lbl_1_bss_74 != 0) {
        for (var_r31 = 0; var_r31 < 0xE; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    else {
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
        fn_1_10FBC(1);
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if (lbl_1_bss_74 != 0) {
                var_f31 = fn_1_10E38(lbl_1_data_584[lbl_1_bss_8C[var_r29].unk_5C][0], lbl_1_data_584[var_r29 + 1][0], var_r31, 10.0f);
                var_f30 = fn_1_10E38(lbl_1_data_584[lbl_1_bss_8C[var_r29].unk_5C][1], lbl_1_data_584[1][1], var_r31, 10.0f);
            }
            else {
                var_f31 = fn_1_10E38(lbl_1_data_4D4[lbl_1_bss_8C[var_r29].unk_5C % 4][0], lbl_1_data_4D4[var_r29][0], var_r31, 10.0f);
                var_f30 = fn_1_10E38(lbl_1_data_4D4[(lbl_1_bss_8C[var_r29].unk_5C / 4) * 4][1], lbl_1_data_4D4[0][1], var_r31, 10.0f);
            }
            HuSprPosSet(var_r30, var_r29 + 0x1E, var_f31, var_f30);
            HuSprPosSet(var_r30, var_r29 + 0x22, var_f31, var_f30);
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_74 != 0) {
            HuSprPosSet(var_r30, var_r31 + 0x1E, *lbl_1_data_584[var_r31 + 1], lbl_1_data_584[var_r31 + 1][1]);
            HuSprPosSet(var_r30, var_r31 + 0x22, *lbl_1_data_584[var_r31 + 1], lbl_1_data_584[var_r31 + 1][1]);
            lbl_1_bss_8C[var_r31].unk_5C = var_r31 + 1;
            lbl_1_bss_8C[var_r31].unk_48 = var_r31;
            lbl_1_bss_8C[var_r31].unk_08 = 0;
        }
        else {
            HuSprPosSet(var_r30, var_r31 + 0x1E, lbl_1_data_4D4[var_r31][0], lbl_1_data_4D4[var_r31][1]);
            HuSprPosSet(var_r30, var_r31 + 0x22, lbl_1_data_4D4[var_r31][0], lbl_1_data_4D4[var_r31][1]);
            lbl_1_bss_8C[var_r31].unk_48 = var_r31;
            lbl_1_bss_8C[var_r31].unk_5C = var_r31;
            lbl_1_bss_8C[var_r31].unk_08 = 0;
        }
    }
}

void fn_1_D280(omObjData *arg0, ZtarDllUnkStruct2 *arg1)
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
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;

    var_r24 = lbl_1_bss_26C[1];
    var_r27 = 0;
    var_r26 = 0;
    HuSprAttrReset(var_r24, arg1->unk_48 + 0x1E, 4);
    HuSprAttrReset(var_r24, arg1->unk_48 + 0x22, 4);
    if (lbl_1_bss_74 != 0) {
        var_r30 = arg1->unk_5C % 6;
        var_r23 = var_r30;
        var_r29 = arg1->unk_5C / 6;
        var_r22 = var_r29;
    }
    else {
        var_r30 = arg1->unk_5C % 4;
        var_r23 = var_r30;
        var_r29 = arg1->unk_5C / 4;
        var_r22 = var_r29;
    }
    if (arg1->unk_08 == 0) {
        if (HuPadBtnDown[arg1->unk_48] & PAD_BUTTON_A) {
            arg1->unk_08 = 1;
            if (lbl_1_bss_74 != 0) {
                var_r21 = 0;
                if (arg1->unk_5C <= 5) {
                    var_r21 = arg1->unk_5C - 1;
                }
                else if (arg1->unk_5C <= 0xB) {
                    var_r21 = arg1->unk_5C - 3;
                }
                else {
                    var_r21 = arg1->unk_5C - 4;
                }
                fn_1_122A8(var_r21);
                HuSprBankSet(var_r24, var_r21 + 2, 1);
            }
            else {
                fn_1_122A8(arg1->unk_5C);
                HuSprBankSet(var_r24, arg1->unk_5C + 2, 1);
            }
            HuSprBankSet(var_r24, arg1->unk_48 + 0x1E, 1);
            HuSprBankSet(var_r24, arg1->unk_48 + 0x22, 1);
        }
        else if (lbl_1_bss_74 != 0) {
            if (HuPadStkX[arg1->unk_48] >= 5) {
                var_r30++;
                var_r27 = 1;
                if (var_r30 > 5) {
                    var_r30 = 5;
                }
            }
            else if (HuPadStkX[arg1->unk_48] <= -5) {
                var_r30--;
                var_r27 = -1;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
            }
            if (HuPadStkY[arg1->unk_48] <= -5) {
                var_r29++;
                var_r26 = 1;
                if (var_r29 > 2) {
                    var_r29 = 2;
                }
            }
            else if (HuPadStkY[arg1->unk_48] >= 5) {
                var_r29--;
                var_r26 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
        else {
            if (HuPadStkX[arg1->unk_48] >= 5) {
                var_r30++;
                var_r27 = 1;
                if (var_r30 > 3) {
                    var_r30 = 3;
                }
            }
            else if (HuPadStkX[arg1->unk_48] <= -5) {
                var_r30--;
                var_r27 = -1;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
            }
            if (HuPadStkY[arg1->unk_48] <= -5) {
                var_r29++;
                var_r26 = 1;
                if (var_r29 > 1) {
                    var_r29 = 1;
                }
            }
            else if (HuPadStkY[arg1->unk_48] >= 5) {
                var_r29--;
                var_r26 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
    }
    else if ((HuPadBtnDown[arg1->unk_48] & PAD_BUTTON_B) != 0) {
        arg1->unk_08 = 0;
        lbl_1_bss_20C.unk_10 = 1;
        HuAudFXPlay(3);
        if (lbl_1_bss_74 != 0) {
            var_r20 = 0;
            if (arg1->unk_5C <= 5) {
                var_r20 = arg1->unk_5C - 1;
            }
            else if (arg1->unk_5C <= 0xB) {
                var_r20 = arg1->unk_5C - 3;
            }
            else {
                var_r20 = arg1->unk_5C - 4;
            }
            HuSprBankSet(var_r24, var_r20 + 2, 0);
        }
        else {
            HuSprBankSet(var_r24, arg1->unk_5C + 2, 0);
        }
        HuSprBankSet(var_r24, arg1->unk_48 + 0x1E, 0);
        HuSprBankSet(var_r24, arg1->unk_48 + 0x22, 0);
    }
    if (lbl_1_bss_74 != 0) {
        var_r25 = var_r30 + (var_r29 * 6);
    }
    else {
        var_r25 = var_r30 + (var_r29 * 4);
    }
    if (arg1->unk_5C != var_r25) {
        if (lbl_1_bss_74 != 0) {
            while (1) {
                var_r25 = var_r30 + (var_r29 * 6);
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    if (((var_r28 != arg1->unk_48) && (lbl_1_bss_8C[var_r28].unk_50 == 0) && (var_r25 == lbl_1_bss_8C[var_r28].unk_5C))
                        || (var_r25 == 0) || (var_r25 == 5) || (var_r25 == 6) || (var_r25 == 0xB)) {
                        if ((var_r27 == 0) || (var_r26 == 0)) {
                            if (((var_r30 + var_r27) > 5) || ((var_r30 + var_r27) < 0)) {
                                var_r30 = var_r23;
                            }
                            else {
                                var_r30 += var_r27;
                            }
                            if (((var_r29 + var_r26) > 2) || ((var_r29 + var_r26) < 0)) {
                                var_r29 = var_r22;
                            }
                            else {
                                var_r29 += var_r26;
                            }
                        }
                        else if (((var_r30 + var_r27) <= 5) && ((var_r30 + var_r27) >= 0)) {
                            var_r30 += var_r27;
                        }
                        else if (((var_r29 + var_r26) <= 2) && ((var_r29 + var_r26) >= 0)) {
                            var_r29 += var_r26;
                        }
                        else {
                            var_r30 = var_r23;
                            var_r29 = var_r22;
                        }
                        break;
                    }
                    else {
                    }
                }
                if (var_r28 == 4) {
                    break;
                }
            }
        }
        else {
            while (1) {
                var_r25 = var_r30 + (var_r29 * 4);
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    if ((var_r28 != arg1->unk_48) && (lbl_1_bss_8C[var_r28].unk_50 == 0) && (var_r25 == lbl_1_bss_8C[var_r28].unk_5C)) {
                        if ((var_r27 == 0) || (var_r26 == 0)) {
                            if (((var_r30 + var_r27) > 3) || ((var_r30 + var_r27) < 0)) {
                                var_r30 = var_r23;
                            }
                            else {
                                var_r30 += var_r27;
                            }
                            if (((var_r29 + var_r26) > 1) || ((var_r29 + var_r26) < 0)) {
                                var_r29 = var_r22;
                            }
                            else {
                                var_r29 += var_r26;
                            }
                            break;
                        }
                        else if (((var_r30 + var_r27) <= 3) && ((var_r30 + var_r27) >= 0)) {
                            var_r30 += var_r27;
                            break;
                        }
                        else if (((var_r29 + var_r26) <= 1) && ((var_r29 + var_r26) >= 0)) {
                            var_r29 += var_r26;
                            break;
                        }
                        else {
                            var_r30 = var_r23;
                            var_r29 = var_r22;
                            break;
                        }
                    }
                    else {
                        continue;
                    }
                }
                if (var_r28 == 4) {
                    break;
                }
            }
        }
        if (lbl_1_bss_74 != 0) {
            var_r25 = var_r30 + (var_r29 * 6);
        }
        else {
            var_r25 = var_r30 + (var_r29 * 4);
        }
        if (arg1->unk_5C != var_r25) {
            HuAudFXPlay(0);
            var_r19 = arg1->unk_5C;
            arg1->unk_5C = var_r25;
            if (lbl_1_bss_74 != 0) {
                for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                    fn_1_10FBC(1);
                    var_f31 = fn_1_10E38(lbl_1_data_584[var_r19][0], lbl_1_data_584[var_r25][0], var_r28, 10.0f);
                    var_f30 = fn_1_10E38(lbl_1_data_584[var_r19][1], lbl_1_data_584[var_r25][1], var_r28, 10.0f);
                    HuSprPosSet(var_r24, arg1->unk_48 + 0x1E, var_f31, var_f30);
                    HuSprPosSet(var_r24, arg1->unk_48 + 0x22, var_f31, var_f30);
                }
                return;
            }
            for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                fn_1_10FBC(1);
                var_f31 = fn_1_10E38(*lbl_1_data_4D4[var_r23], *lbl_1_data_4D4[var_r30], var_r28, 10.0f);
                var_f30 = fn_1_10E38(lbl_1_data_4D4[var_r22 * 4][1], lbl_1_data_4D4[var_r29 * 4][1], var_r28, 10.0f);
                HuSprPosSet(var_r24, arg1->unk_48 + 0x1E, var_f31, var_f30);
                HuSprPosSet(var_r24, arg1->unk_48 + 0x22, var_f31, var_f30);
            }
        }
    }
}

void fn_1_DD8C(ZtarDllUnkStruct2 *arg0)
{
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r30 = lbl_1_bss_26C[1];
    do {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if ((var_r29 != arg0->unk_48) && (lbl_1_bss_8C[var_r29].unk_08 == 1) && (arg0->unk_5C == lbl_1_bss_8C[var_r29].unk_5C)) {
                arg0->unk_5C += 1;
                break;
            }
        }
    } while (var_r29 != 4);
    arg0->unk_54 = 0;
    if (lbl_1_bss_74 != 0) {
        var_r28 = 0;
        if (arg0->unk_5C <= 5) {
            var_r28 = arg0->unk_5C - 1;
        }
        else if (arg0->unk_5C <= 0xB) {
            var_r28 = arg0->unk_5C - 3;
        }
        else {
            var_r28 = arg0->unk_5C - 4;
        }
        HuSprBankSet(var_r30, var_r28 + 2, 0);
    }
    else {
        HuSprBankSet(var_r30, arg0->unk_5C + 2, 0);
    }
    HuSprBankSet(var_r30, arg0->unk_48 + 0x26, 0);
    HuSprBankSet(var_r30, arg0->unk_48 + 0x2A, 0);
    HuSprBankSet(var_r30, arg0->unk_48 + 0x2E, arg0->unk_54);
    HuSprBankSet(var_r30, arg0->unk_48 + 0x32, arg0->unk_54);
    if (lbl_1_bss_74 != 0) {
        HuSprPosSet(var_r30, arg0->unk_48 + 0x26, *lbl_1_data_584[arg0->unk_5C], lbl_1_data_584[arg0->unk_5C][1]);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x2A, *lbl_1_data_584[arg0->unk_5C], lbl_1_data_584[arg0->unk_5C][1]);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x2E, *lbl_1_data_584[arg0->unk_5C], lbl_1_data_584[arg0->unk_5C][1] + 0x23);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x32, *lbl_1_data_584[arg0->unk_5C], lbl_1_data_584[arg0->unk_5C][1] + 0x23);
    }
    else {
        HuSprPosSet(var_r30, arg0->unk_48 + 0x26, *lbl_1_data_4D4[arg0->unk_5C % 4], lbl_1_data_4D4[(arg0->unk_5C / 4) * 4][1]);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x2A, *lbl_1_data_4D4[arg0->unk_5C % 4], lbl_1_data_4D4[(arg0->unk_5C / 4) * 4][1]);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x2E, *lbl_1_data_4D4[arg0->unk_5C % 4], lbl_1_data_4D4[(arg0->unk_5C / 4) * 4][1] + 0x23);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x32, *lbl_1_data_4D4[arg0->unk_5C % 4], lbl_1_data_4D4[(arg0->unk_5C / 4) * 4][1] + 0x23);
    }
    arg0->unk_10 = 0;
    HuSprAttrReset(var_r30, arg0->unk_48 + 0x26, 4);
    HuSprAttrReset(var_r30, arg0->unk_48 + 0x2A, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x2E, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x32, 4);
}

void fn_1_E4AC(ZtarDllUnkStruct2 *arg0)
{
    s32 var_r30 = lbl_1_bss_26C[1];
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x26, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x2A, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x2E, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x32, 4);
}

void fn_1_E548(omObjData *arg0, ZtarDllUnkStruct2 *arg1)
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
    s32 var_r24;
    s32 var_r23;
    u32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;

    var_r27 = lbl_1_bss_26C[1];
    var_r26 = 0;
    var_r25 = 0;
    sp8 = arg1->unk_54;
    lbl_1_bss_20C.unk_30 = 0;
    if (lbl_1_bss_74 != 0) {
        var_r30 = arg1->unk_5C % 6;
        var_r23 = var_r30;
        var_r29 = arg1->unk_5C / 6;
        var_r22 = var_r29;
    }
    else {
        var_r30 = arg1->unk_5C % 4;
        var_r23 = var_r30;
        var_r29 = arg1->unk_5C / 4;
        var_r22 = var_r29;
    }
    if (arg1->unk_08 == 0) {
        if (HuPadBtnDown[lbl_1_bss_8C[0].unk_58] & PAD_BUTTON_A) {
            arg1->unk_08 = 1;
            HuSprBankSet(var_r27, arg1->unk_48 + 0x26, 1);
            HuSprBankSet(var_r27, arg1->unk_48 + 0x2A, 1);
            if (lbl_1_bss_74 != 0) {
                var_r21 = 0;
                if (arg1->unk_5C <= 5) {
                    var_r21 = arg1->unk_5C - 1;
                }
                else if (arg1->unk_5C <= 0xB) {
                    var_r21 = arg1->unk_5C - 3;
                }
                else {
                    var_r21 = arg1->unk_5C - 4;
                }
                HuSprBankSet(var_r27, var_r21 + 2, 1);
                fn_1_122A8(var_r21);
            }
            else {
                HuSprBankSet(var_r27, arg1->unk_5C + 2, 1);
                fn_1_122A8(arg1->unk_5C);
            }
            arg1->unk_54 = 0;
            HuSprBankSet(var_r27, arg1->unk_48 + 0x2E, arg1->unk_54);
            if (lbl_1_bss_74 != 0) {
                HuSprPosSet(var_r27, arg1->unk_48 + 0x2E, lbl_1_data_584[arg1->unk_5C][0], lbl_1_data_584[arg1->unk_5C][1] + 0x23);
            }
            else {
                HuSprPosSet(var_r27, arg1->unk_48 + 0x2E, lbl_1_data_4D4[arg1->unk_5C % 4][0], lbl_1_data_4D4[(arg1->unk_5C / 4) * 4][1] + 0x23);
            }
            HuSprAttrReset(var_r27, arg1->unk_48 + 0x2E, 4);
        }
        else if (lbl_1_bss_74 != 0) {
            if (HuPadStkX[0] >= 5) {
                var_r30++;
                var_r26 = 1;
                if (var_r30 > 5) {
                    var_r30 = 5;
                }
            }
            else if (HuPadStkX[0] <= -5) {
                var_r30--;
                var_r26 = -1;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
            }
            if (*HuPadStkY <= -5) {
                var_r29++;
                var_r25 = 1;
                if (var_r29 > 2) {
                    var_r29 = 2;
                }
            }
            else if (*HuPadStkY >= 5) {
                var_r29--;
                var_r25 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
        else {
            if (HuPadStkX[0] >= 5) {
                var_r30++;
                var_r26 = 1;
                if (var_r30 > 3) {
                    var_r30 = 3;
                }
            }
            else if (HuPadStkX[0] <= -5) {
                var_r30--;
                var_r26 = -1;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
            }
            if (*HuPadStkY <= -5) {
                var_r29++;
                var_r25 = 1;
                if (var_r29 > 1) {
                    var_r29 = 1;
                }
            }
            else if (*HuPadStkY >= 5) {
                var_r29--;
                var_r25 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
    }
    else if (HuPadBtnDown[lbl_1_bss_8C[0].unk_58] & PAD_BUTTON_B) {
        arg1->unk_08 = arg1->unk_10 = 0;
        if (lbl_1_bss_74 != 0) {
            var_r20 = 0;
            if (arg1->unk_5C <= 5) {
                var_r20 = arg1->unk_5C - 1;
            }
            else if (arg1->unk_5C <= 0xB) {
                var_r20 = arg1->unk_5C - 3;
            }
            else {
                var_r20 = arg1->unk_5C - 4;
            }
            HuSprBankSet(var_r27, var_r20 + 2, 0);
        }
        else {
            HuSprBankSet(var_r27, arg1->unk_5C + 2, 0);
        }
        HuSprBankSet(var_r27, arg1->unk_48 + 0x26, 0);
        HuSprBankSet(var_r27, arg1->unk_48 + 0x2A, 0);
        HuSprAttrSet(var_r27, arg1->unk_48 + 0x2E, 4);
        HuAudFXPlay(3);
    }
    if (lbl_1_bss_74 != 0) {
        var_r24 = var_r30 + (var_r29 * 6);
    }
    else {
        var_r24 = var_r30 + (var_r29 * 4);
    }
    if (arg1->unk_5C != var_r24) {
        if (lbl_1_bss_74 != 0) {
            while (1) {
                fn_1_10FBC(1);
                var_r24 = var_r30 + (var_r29 * 6);
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    if (((var_r28 != arg1->unk_48) && (lbl_1_bss_8C[var_r28].unk_08 == 1) && (var_r24 == lbl_1_bss_8C[var_r28].unk_5C))
                        || (var_r24 == 0) || (var_r24 == 5) || (var_r24 == 6) || (var_r24 == 0xB)) {
                        if ((var_r26 == 0) || (var_r25 == 0)) {
                            if (((var_r30 + var_r26) > 5) || ((var_r30 + var_r26) < 0)) {
                                var_r30 = var_r23;
                            }
                            else {
                                var_r30 += var_r26;
                            }
                            if (((var_r29 + var_r25) > 2) || ((var_r29 + var_r25) < 0)) {
                                var_r29 = var_r22;
                            }
                            else {
                                var_r29 += var_r25;
                            }
                        }
                        else if (((var_r30 + var_r26) <= 5) && ((var_r30 + var_r26) >= 0)) {
                            var_r30 += var_r26;
                        }
                        else if (((var_r29 + var_r25) <= 2) && ((var_r29 + var_r25) >= 0)) {
                            var_r29 += var_r25;
                        }
                        else {
                            var_r30 = var_r23;
                            var_r29 = var_r22;
                        }
                        break;
                    }
                }
                if (var_r28 == 4) {
                    break;
                }
            }
        }
        else {
            do {
                var_r24 = var_r30 + (var_r29 * 4);
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    if ((var_r28 != arg1->unk_48) && (lbl_1_bss_8C[var_r28].unk_08 == 1) && (var_r24 == lbl_1_bss_8C[var_r28].unk_5C)) {
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
        }
        if (lbl_1_bss_74 != 0) {
            var_r24 = var_r30 + (var_r29 * 6);
        }
        else {
            var_r24 = var_r30 + (var_r29 * 4);
        }
        if (arg1->unk_5C != var_r24) {
            var_r19 = arg1->unk_5C;
            arg1->unk_5C = var_r24;
            HuAudFXPlay(0);
            if (lbl_1_bss_74 != 0) {
                for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                    fn_1_10FBC(1);
                    var_f31 = fn_1_10E38(lbl_1_data_584[var_r19][0], lbl_1_data_584[var_r24][0], var_r28, 10.0f);
                    var_f30 = fn_1_10E38(lbl_1_data_584[var_r19][1], lbl_1_data_584[var_r24][1], var_r28, 10.0f);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x26, var_f31, var_f30);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x2A, var_f31, var_f30);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x2E, var_f31, 35.0f + var_f30);
                }
            }
            else {
                for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                    fn_1_10FBC(1);
                    var_f31 = fn_1_10E38(lbl_1_data_4D4[var_r23][0], lbl_1_data_4D4[var_r30][0], var_r28, 10.0f);
                    var_f30 = fn_1_10E38(lbl_1_data_4D4[var_r22 * 4][1], lbl_1_data_4D4[var_r29 * 4][1], var_r28, 10.0f);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x26, var_f31, var_f30);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x2A, var_f31, var_f30);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x2E, var_f31, 35.0f + var_f30);
                }
            }
        }
    }
    lbl_1_bss_20C.unk_30 = 0;
}

s32 fn_1_F214(ZtarDllUnkStruct2 *arg0)
{
    float var_f31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r28 = 0;
    var_r29 = lbl_1_bss_26C[1];
    while (1) {
        fn_1_10FBC(1);
        var_r28 = 0;
        var_r26 = arg0->unk_54;
        if (HuPadStkX[lbl_1_bss_8C[0].unk_58] >= 5 || (HuPadBtn[lbl_1_bss_8C[0].unk_58] & PAD_BUTTON_RIGHT)) {
            if (GWGameStat.field10E_bit4 == 1) {
                arg0->unk_54++;
                var_r28 = 1;
                if (arg0->unk_54 > 3) {
                    arg0->unk_54 = 0;
                }
            }
            else {
                arg0->unk_54++;
                var_r28 = 1;
                if (arg0->unk_54 > 2) {
                    arg0->unk_54 = 0;
                }
            }
        }
        else if (HuPadStkX[lbl_1_bss_8C[0].unk_58] <= -5 || (HuPadBtn[lbl_1_bss_8C[0].unk_58] & PAD_BUTTON_LEFT)) {
            if (GWGameStat.field10E_bit4 == 1) {
                arg0->unk_54--;
                var_r28 = -1;
                if (arg0->unk_54 < 0) {
                    arg0->unk_54 = 3;
                }
            }
            else {
                arg0->unk_54--;
                var_r28 = -1;
                if (arg0->unk_54 < 0) {
                    arg0->unk_54 = 2;
                }
            }
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            var_r27 = 1;
            break;
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            var_r27 = 0;
            HuAudFXPlay(3);
            break;
        }
        if (arg0->unk_54 != var_r26) {
            HuAudFXPlay(0);
            for (var_r30 = 0; var_r30 <= 5; var_r30++) {
                fn_1_10FBC(1);
                if (lbl_1_bss_74) {
                    var_f31 = fn_1_10E38(lbl_1_data_584[arg0->unk_5C][0], lbl_1_data_584[arg0->unk_5C][0] + (var_r28 * 10), var_r30, 5.0f);
                    HuSprPosSet(var_r29, arg0->unk_48 + 46, var_f31, lbl_1_data_584[arg0->unk_5C][1] + 35);
                }
                else {
                    var_f31 = fn_1_10E38(lbl_1_data_4D4[arg0->unk_5C % 4][0], lbl_1_data_4D4[arg0->unk_5C % 4][0] + (var_r28 * 10), var_r30, 5.0f);
                    HuSprPosSet(var_r29, arg0->unk_48 + 46, var_f31, lbl_1_data_4D4[(arg0->unk_5C / 4) * 4][1] + 35);
                }
            }
            HuSprBankSet(var_r29, arg0->unk_48 + 46, arg0->unk_54);
            for (var_r30 = 0; var_r30 <= 5; var_r30++) {
                fn_1_10FBC(1);
                if (lbl_1_bss_74) {
                    var_f31 = fn_1_10E38(lbl_1_data_584[arg0->unk_5C][0] + (var_r28 * 10), lbl_1_data_584[arg0->unk_5C][0], var_r30, 5.0f);
                    HuSprPosSet(var_r29, arg0->unk_48 + 46, var_f31, lbl_1_data_584[arg0->unk_5C][1] + 35);
                }
                else {
                    var_f31 = fn_1_10E38(lbl_1_data_4D4[arg0->unk_5C % 4][0] + (var_r28 * 10), lbl_1_data_4D4[arg0->unk_5C % 4][0], var_r30, 5.0f);
                    HuSprPosSet(var_r29, arg0->unk_48 + 46, var_f31, lbl_1_data_4D4[(arg0->unk_5C / 4) * 4][1] + 35);
                }
            }
        }
    }
    if (var_r27 == 1) {
        if (lbl_1_bss_74) {
            HuSprPosSet(var_r29, arg0->unk_48 + 50, lbl_1_data_584[arg0->unk_5C][0], lbl_1_data_584[arg0->unk_5C][1] + 35);
        }
        else {
            HuSprPosSet(var_r29, arg0->unk_48 + 50, lbl_1_data_4D4[arg0->unk_5C % 4][0], lbl_1_data_4D4[(arg0->unk_5C / 4) * 4][1] + 35);
        }
        HuSprBankSet(var_r29, arg0->unk_48 + 50, arg0->unk_54);
        HuSprAttrReset(var_r29, arg0->unk_48 + 50, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(var_r29, arg0->unk_48 + 46, HUSPR_ATTR_DISPOFF);
    }
    return var_r27;
}

void fn_1_FB38(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r28;
    AnimData *var_r27;

    var_r29 = HuSprGrpCreate(0x1B);
    lbl_1_bss_26C[2] = var_r29;
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x67)), 0x64, 0);
    HuSprGrpMemberSet(var_r29, 0, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x68)), 0x64, 0);
    HuSprGrpMemberSet(var_r29, 1, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x69)), 0x64, 0);
    HuSprGrpMemberSet(var_r29, 2, var_r31);
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x6A)), 0x64, 0);
    HuSprGrpMemberSet(var_r29, 3, var_r31);
    for (var_r30 = 0; var_r30 < 0xE; var_r30++) {
        var_r31 = HuSprCreate(HuSprAnimReadFile(var_r30 + DATA_MAKE_NUM(DATADIR_MPEX, 0x6B)), 0x5A, 0);
        HuSprGrpMemberSet(var_r29, var_r30 + 4, var_r31);
    }
    var_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x79));
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x7A));
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r31 = HuSprCreate(var_r28, 0x50, 0);
        HuSprGrpMemberSet(var_r29, var_r30 + 0x12, var_r31);
        var_r31 = HuSprCreate(var_r27, 0x50, 0);
        HuSprGrpMemberSet(var_r29, var_r30 + 0x16, var_r31);
    }
    var_r31 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MPEX, 0x7B)), 0x46, 0);
    HuSprGrpMemberSet(var_r29, 0x1A, var_r31);
    fn_1_FD90(0);
    fn_1_106E8(0);
}

void fn_1_FD90(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s16 var_r28;
    s16 var_r27;
    s16 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;

    var_r30 = lbl_1_bss_26C[2];
    for (var_r31 = 0; var_r31 < 0x1B; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    switch (arg0) {
        case 0:
            HuSprAttrReset(var_r30, 2, 4);
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                var_r28 = GWPlayerCfg[var_r31].character;
                var_r25 = GWPlayerCfg[var_r31].diff;
                HuSprAttrReset(var_r30, var_r28 + 4, 4);
                HuSprPosSet(var_r30, var_r28 + 4, lbl_1_data_614[var_r31][0], lbl_1_data_614[var_r31][1]);
                if (GWPlayerCfg[var_r31].iscom != 0) {
                    HuSprAttrReset(var_r30, var_r31 + 0x16, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x16, var_r25);
                    HuSprPosSet(var_r30, var_r31 + 0x16, lbl_1_data_614[var_r31][0], lbl_1_data_614[var_r31][1] + 0x14);
                }
                else {
                    HuSprAttrReset(var_r30, var_r31 + 0x12, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x12, var_r31);
                    HuSprPosSet(var_r30, var_r31 + 0x12, lbl_1_data_614[var_r31][0], lbl_1_data_614[var_r31][1] + 0x14);
                }
            }
            break;
        case 1:
            HuSprAttrReset(var_r30, 0, 4);
            var_r27 = GWPlayerCfg->character;
            var_r24 = GWPlayerCfg->diff;
            HuSprAttrReset(var_r30, var_r27 + 4, 4);
            HuSprPosSet(var_r30, var_r27 + 4, 0.0f, lbl_1_data_634[1]);
            if (GWPlayerCfg->iscom != 0) {
                HuSprAttrReset(var_r30, 0x16, 4);
                HuSprBankSet(var_r30, 0x16, var_r24);
                HuSprPosSet(var_r30, var_r31 + 0x16, 0.0f, lbl_1_data_634[1] + 0x14);
            }
            else {
                HuSprAttrReset(var_r30, 0x12, 4);
                HuSprBankSet(var_r30, 0x12, 0);
                HuSprPosSet(var_r30, 0x12, 0.0f, lbl_1_data_634[1] + 0x14);
            }
            break;
        case 2:
            HuSprAttrReset(var_r30, 1, 4);
            for (var_r31 = 0; var_r31 < 2; var_r31++) {
                var_r26 = GWPlayerCfg[var_r31].character;
                var_r23 = GWPlayerCfg[var_r31].diff;
                HuSprAttrReset(var_r30, var_r26 + 4, 4);
                HuSprPosSet(var_r30, var_r26 + 4, lbl_1_data_63C[var_r31][0], lbl_1_data_63C[var_r31][1]);
                if (GWPlayerCfg[var_r31].iscom != 0) {
                    HuSprAttrReset(var_r30, var_r31 + 0x16, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x16, var_r23);
                    HuSprPosSet(var_r30, var_r31 + 0x16, lbl_1_data_63C[var_r31][0], lbl_1_data_63C[var_r31][1] + 0x19);
                }
                else {
                    HuSprAttrReset(var_r30, var_r31 + 0x12, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x12, var_r31);
                    HuSprPosSet(var_r30, var_r31 + 0x12, lbl_1_data_63C[var_r31][0], lbl_1_data_63C[var_r31][1] + 0x19);
                }
            }
            break;
        case 3:
            HuSprAttrReset(var_r30, 1, 4);
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                var_r29 = GWPlayerCfg[var_r31].character;
                var_r22 = GWPlayerCfg[var_r31].diff;
                var_r29 = fn_1_10C18(var_r29);
                HuSprAttrReset(var_r30, var_r29 + 4, 4);
                HuSprPosSet(var_r30, var_r29 + 4, lbl_1_data_64C[var_r31][0], lbl_1_data_64C[var_r31][1]);
                if (GWPlayerCfg[var_r31].iscom != 0) {
                    HuSprAttrReset(var_r30, var_r31 + 0x16, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x16, var_r22);
                    HuSprPosSet(var_r30, var_r31 + 0x16, lbl_1_data_64C[var_r31][0], lbl_1_data_64C[var_r31][1] + 0x19);
                }
                else {
                    HuSprAttrReset(var_r30, var_r31 + 0x12, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x12, var_r31);
                    HuSprPosSet(var_r30, var_r31 + 0x12, lbl_1_data_64C[var_r31][0], lbl_1_data_64C[var_r31][1] + 0x19);
                }
            }
            HuSprAttrReset(var_r30, 0x1A, 4);
            break;
    }
    HuSprGrpPosSet(var_r30, 112.0f, -428.0f);
}

void fn_1_106E8(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_26C[2];
    for (var_r31 = 0; var_r31 < 0x1B; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprGrpPosSet(var_r30, 112.0f, -428.0f);
}

void fn_1_10764(s32 arg0)
{
    float var_f31;
    s32 var_r30;
    s32 var_r31;

    var_r30 = lbl_1_bss_26C[2];
    fn_1_FD90(arg0);
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_10FBC(1);
        if (var_r31 <= 0x32) {
            var_f31 = fn_1_10E38(-500.0f, 10.0f, var_r31, 50.0f);
        }
        else {
            var_f31 = fn_1_10D60(10.0f, 0.0f, var_r31 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r30, 112.0f, 72.0f + var_f31);
    }
    HuSprGrpPosSet(var_r30, 112.0f, 72.0f);
}

void fn_1_108C8(s32 arg0)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r29 = lbl_1_bss_26C[2];
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_10FBC(1);
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_10E38(0.0f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_10D60(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(var_r29, 112.0f, 72.0f + var_f31);
    }
    HuSprGrpPosSet(var_r29, 112.0f, -428.0f);
    var_r28 = lbl_1_bss_26C[2];
    for (var_r30 = 0; var_r30 < 0x1B; var_r30++) {
        HuSprAttrSet(var_r28, var_r30, 4);
    }
    HuSprGrpPosSet(var_r28, 112.0f, -428.0f);
}

void fn_1_10A80(void)
{
    omObjData *var_r31;

    var_r31 = NULL;
    var_r31 = omAddObjEx(lbl_1_bss_70, 0x1000, 8, 8, -1, NULL);
    lbl_1_bss_20C.unk_00 = var_r31;
    lbl_1_bss_20C.unk_04 = NULL;
    while (TRUE) {
        HuPrcVSleep();
        if (lbl_1_bss_20C.unk_04 != NULL) {
            lbl_1_bss_20C.unk_04(lbl_1_bss_20C.unk_00, &lbl_1_bss_20C);
        }
    }
}

void fn_1_10B24(void)
{
    s32 var_r31;
    omObjData *var_r30;

    var_r31 = lbl_1_bss_78[0];
    lbl_1_bss_78[0] = var_r31 + 1;
    var_r30 = NULL;
    var_r30 = omAddObjEx(lbl_1_bss_70, 0x1000, 8, 8, -1, NULL);
    lbl_1_bss_8C[var_r31].unk_00 = var_r30;
    lbl_1_bss_8C[var_r31].unk_04 = NULL;

    while (TRUE) {
        HuPrcVSleep();
        if (lbl_1_bss_8C[var_r31].unk_04 != NULL) {
            lbl_1_bss_8C[var_r31].unk_04(lbl_1_bss_8C[var_r31].unk_00, &lbl_1_bss_8C[var_r31]);
        }
    }
}

s32 fn_1_10C18(s32 arg0)
{
    s32 var_r31;

    switch (arg0) {
        case 9:
            var_r31 = 8;
            break;
        case 10:
            var_r31 = 9;
            break;
        case 11:
            var_r31 = 0xA;
            break;
        case 12:
            var_r31 = 0xB;
            break;
        case 13:
            var_r31 = 0xC;
            break;
        case 8:
            var_r31 = 0xD;
            break;
        default:
            var_r31 = -1;
            break;
    }
    return var_r31;
}

s32 fn_1_10C98(s32 arg0)
{
    s32 var_r31;

    switch (arg0) {
        case 8:
            var_r31 = 9;
            break;
        case 9:
            var_r31 = 0xA;
            break;
        case 10:
            var_r31 = 0xB;
            break;
        case 11:
            var_r31 = 0xC;
            break;
        case 12:
            var_r31 = 0xD;
            break;
        case 13:
            var_r31 = 8;
            break;
        default:
            var_r31 = -1;
            break;
    }
    return var_r31;
}

float fn_1_10D18(float arg8, float arg9, float argA, float argB)
{
    if (argB <= argA) {
        return arg9;
    }
    return arg8 + ((argA / argB) * (arg9 - arg8));
}

float fn_1_10D40(float arg8, float arg9, float argA)
{
    return (arg9 + (arg8 * (argA - 1.0f))) / argA;
}

float fn_1_10D60(float arg8, float arg9, float argA, float argB)
{
    if (argA >= argB) {
        return arg9;
    }
    return arg8 + ((arg9 - arg8) * (1.0 - cosd(((90.0f / argB) * argA))));
}

float fn_1_10E38(float arg8, float arg9, float argA, float argB)
{
    if (argA >= argB) {
        return arg9;
    }
    return arg8 + ((arg9 - arg8) * sind(((90.0f / argB) * argA)));
}

float fn_1_10F00(float arg8, float arg9, float argA, float argB)
{
    if (argA >= argB) {
        return arg8;
    }
    return arg8 + ((arg9 - arg8) * sind(((360.0f / argB) * argA)));
}

void fn_1_10FBC(s32 arg0)
{
    if (arg0 <= 1) {
        HuPrcVSleep();
        return;
    }
    HuPrcSleep(arg0);
}

void fn_1_10FFC(void)
{
    HuWinInit(1);
}

void fn_1_11020(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    if (lbl_1_data_66C == -1) {
        var_r31 = 0x1C9;
        var_r30 = 0x44;
        var_r29 = 1.0f + ((576.0f - var_r31) / 2.0f);
        var_r28 = 445.0f - var_r30;
        lbl_1_data_66C = HuWinExCreateStyled(var_r29, var_r28, var_r31, var_r30, -1, 1);
        winData[lbl_1_data_66C].active_pad = 1;
        HuWinMesPalSet(lbl_1_data_66C, 7, 0, 0, 0);
        HuWinExAnimIn(lbl_1_data_66C);
    }
}

void fn_1_111E0(void)
{
    if (lbl_1_data_66C != -1) {
        HuWinMesSet(lbl_1_data_66C, MAKE_MESSID(0x25, 0x04));
        HuWinExAnimOut(lbl_1_data_66C);
        HuWinExCleanup(lbl_1_data_66C);
        lbl_1_data_66C = -1;
    }
}

void fn_1_11264(s32 arg0, s32 arg1, s32 arg2)
{
    if (lbl_1_data_66C != -1) {
        if (arg2 == 1) {
            HuWinMesSpeedSet(lbl_1_data_66C, 0);
        }
        else {
            HuWinMesSpeedSet(lbl_1_data_66C, 1);
        }
        HuWinMesSet(lbl_1_data_66C, arg0);
        if (arg1 <= 0) {
            HuWinMesWait(lbl_1_data_66C);
            return;
        }
        if (arg1 <= 1) {
            HuPrcVSleep();
            return;
        }
        HuPrcSleep(arg1);
    }
}

void fn_1_11338(u32 arg0, s32 arg1)
{
    if (lbl_1_data_66C != -1) {
        HuWinInsertMesSet(lbl_1_data_66C, arg0, arg1);
    }
}

s32 fn_1_11390(s32 arg0)
{
    float spC[2];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    HuWinMesMaxSizeGet(1, spC, MAKE_MESSID(0x1E, 0x35));
    var_r30 = spC[0];
    var_r29 = spC[1];
    var_r27 = 0x22C - var_r30;
    var_r26 = 0x1BD - var_r29;
    var_r31 = HuWinExCreateStyled(var_r27, var_r26, var_r30, var_r29, -1, 1);
    winData[var_r31].active_pad = 1;
    HuWinMesPalSet(var_r31, 7, 0, 0, 0);
    HuWinExAnimIn(var_r31);
    HuWinMesSpeedSet(var_r31, 0);
    HuWinMesSet(var_r31, MAKE_MESSID(0x1E, 0x35));
    var_r28 = HuWinChoiceGet(var_r31, arg0);
    HuWinMesSet(var_r31, MAKE_MESSID(0x25, 0x04));
    HuWinExAnimOut(var_r31);
    HuWinExCleanup(var_r31);

    return var_r28;
}

void fn_1_114EC(u32 arg0, s32 arg1)
{
    float spC[2];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    HuWinMesMaxSizeGet(1, spC, arg0);
    var_r29 = spC[0];
    var_r31 = spC[1];
    var_r28 = (0x240 - var_r29) / 2.0f;
    if (arg1 == 1) {
        var_r30 = 0x1BD - var_r31;
    }
    else {
        var_r30 = 0x181 - var_r31;
    }
    if (lbl_1_data_670 != -1) {
        fn_1_1190C();
        lbl_1_data_670 = HuWinExCreateStyled(var_r28, var_r30, var_r29, var_r31, -1, 1);
    }
    else {
        lbl_1_data_670 = HuWinExCreateStyled(var_r28, var_r30, var_r29, var_r31, -1, 1);
    }
    HuWinBGTPLvlSet(lbl_1_data_670, 0.0f);
    HuWinDispOn(lbl_1_data_670);
    HuWinMesSet(lbl_1_data_670, arg0);
    HuWinMesSpeedSet(lbl_1_data_670, 0);
}

void fn_1_11708(u32 arg0)
{
    float sp8[2];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    HuWinMesMaxSizeGet(1, sp8, arg0);
    var_r30 = sp8[0];
    var_r31 = sp8[1];
    var_r28 = (0x240 - var_r30) / 2.0f;
    var_r29 = 0x181 - var_r31;
    if (lbl_1_data_670 != -1) {
        fn_1_1190C();
        lbl_1_data_670 = HuWinExCreateStyled(var_r28, var_r29, var_r30, var_r31, -1, 1);
    }
    else {
        lbl_1_data_670 = HuWinExCreateStyled(var_r28, var_r29, var_r30, var_r31, -1, 1);
    }
    HuWinBGTPLvlSet(lbl_1_data_670, 0.0f);
    HuWinDispOn(lbl_1_data_670);
    HuWinMesSet(lbl_1_data_670, arg0);
    HuWinMesSpeedSet(lbl_1_data_670, 0);
}

void fn_1_1190C(void)
{
    if (lbl_1_data_670 != -1) {
        HuWinExCleanup(lbl_1_data_670);
        lbl_1_data_670 = -1;
    }
}

void fn_1_11960(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_26C[1];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_8C[var_r31].unk_08 == 1) {
            HuSprBankSet(var_r30, lbl_1_bss_8C[var_r31].unk_5C + 2, 1);
            HuSprBankSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x1E, 1);
            HuSprBankSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x22, 1);
            HuSprAttrReset(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x1E, 4);
            HuSprAttrReset(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x22, 4);
            HuSprPosSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x1E, *lbl_1_data_4D4[lbl_1_bss_8C[var_r31].unk_5C % 4],
                lbl_1_data_4D4[(lbl_1_bss_8C[var_r31].unk_5C / 4) * 4][1]);
            HuSprPosSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x22, *lbl_1_data_4D4[lbl_1_bss_8C[var_r31].unk_5C % 4],
                lbl_1_data_4D4[(lbl_1_bss_8C[var_r31].unk_5C / 4) * 4][1]);
        }
        else {
            lbl_1_bss_8C[var_r31].unk_5C = 0;
        }
    }
}

void fn_1_11C64(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_26C[1];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_8C[var_r31].unk_08 == 1) {
            HuSprBankSet(var_r30, lbl_1_bss_8C[var_r31].unk_5C + 2, 1);
            HuSprBankSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x1E, 1);
            HuSprBankSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x22, 1);
            HuSprAttrReset(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x1E, 4);
            HuSprAttrReset(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x22, 4);
            HuSprPosSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x1E, *lbl_1_data_4D4[lbl_1_bss_8C[var_r31].unk_5C % 4],
                lbl_1_data_4D4[(lbl_1_bss_8C[var_r31].unk_5C / 4) * 4][1]);
            HuSprPosSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x22, *lbl_1_data_4D4[lbl_1_bss_8C[var_r31].unk_5C % 4],
                lbl_1_data_4D4[(lbl_1_bss_8C[var_r31].unk_5C / 4) * 4][1]);
        }
        else {
            lbl_1_bss_8C[var_r31].unk_5C = 0;
        }
    }
}

void fn_1_11F68(void)
{
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;

    var_r30 = lbl_1_bss_26C[1];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_8C[var_r31].unk_08 == 1) {
            if (lbl_1_bss_8C[var_r31].unk_5C <= 5) {
                var_r29 = lbl_1_bss_8C[var_r31].unk_5C - 1;
            }
            else if (lbl_1_bss_8C[var_r31].unk_5C <= 0xB) {
                var_r29 = lbl_1_bss_8C[var_r31].unk_5C - 3;
            }
            else {
                var_r29 = lbl_1_bss_8C[var_r31].unk_5C - 4;
            }
            HuSprBankSet(var_r30, var_r29 + 2, 1);
            HuSprBankSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x1E, 1);
            HuSprBankSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x22, 1);
            HuSprAttrReset(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x1E, 4);
            HuSprAttrReset(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x22, 4);
            HuSprPosSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x1E, *lbl_1_data_584[lbl_1_bss_8C[var_r31].unk_5C],
                lbl_1_data_584[lbl_1_bss_8C[var_r31].unk_5C][1]);
            HuSprPosSet(var_r30, lbl_1_bss_8C[var_r31].unk_48 + 0x22, *lbl_1_data_584[lbl_1_bss_8C[var_r31].unk_5C],
                lbl_1_data_584[lbl_1_bss_8C[var_r31].unk_5C][1]);
        }
        else {
            lbl_1_bss_8C[var_r31].unk_5C = 1;
        }
    }
}

void fn_1_122A8(s32 arg0)
{
    s32 sp8[14] = {
        0x0000006D,
        0x0000006E,
        0x0000006F,
        0x00000070,
        0x00000071,
        0x00000072,
        0x00000073,
        0x00000074,
        0x00000039,
        0x00000040,
        0x0000004B,
        0x00000046,
        0x0000003E,
        0x0000003A,
    };

    if ((arg0 < 0) || (arg0 > 0xD)) {
        return;
    }
    HuAudFXPlay(sp8[arg0]);
}
