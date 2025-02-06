#include "ext_math.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/mpexDll.h"

typedef void (*MpexDllUnkFunc2)(omObjData *, ...);

typedef struct MpexDllUnkStruct4 {
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ MpexDllUnkFunc2 unk_04;
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
} MpexDllUnkStruct4; /* size = 0x60 */

void fn_1_1490C(void);
void fn_1_14B28(void);
void fn_1_14E54(void);
void fn_1_14EF0(void);
void fn_1_151C8(void);
void fn_1_154A4(void);
void fn_1_15774(void);
void fn_1_157C4(void);
void fn_1_15D48(void);
void fn_1_16320(void);
void fn_1_16600(s32 arg0);
void fn_1_16874(s32);
void fn_1_168F0(s32 arg0, s32 arg1);
void fn_1_16D3C(s32 arg0);
void fn_1_17170(s32);
void fn_1_17374(void);
void fn_1_17B04(omObjData *arg0, MpexDllUnkStruct4 *arg1);
void fn_1_18610(MpexDllUnkStruct4 *arg0);
void fn_1_18D30(MpexDllUnkStruct4 *arg0);
void fn_1_18DCC(omObjData *arg0, MpexDllUnkStruct4 *arg1);
s32 fn_1_19A98(MpexDllUnkStruct4 *arg0);
void fn_1_1A3BC(void);
void fn_1_1A5A4(s32 arg0);
void fn_1_1AEFC(s32);
void fn_1_1AF78(s32 arg0);
void fn_1_1B0DC(s32);
void fn_1_1B294(void);
void fn_1_1B338(void);
s32 fn_1_1B42C(s32 arg0);
s32 fn_1_1B4AC(s32 arg0);
float fn_1_1B52C(float, float, float, float); // seems implicit in main.c
float fn_1_1B554(float, float, float); // seems implicit in main.c
float fn_1_1B574(float, float, float, float); // seems implicit in main.c
float fn_1_1B64C(float, float, float, float); // seems implcit in main.c
void fn_1_1B834(void);
void fn_1_1B9F4(void);
void fn_1_1BA78(u32 arg0, s32 arg1, s32 arg2);
void fn_1_1BB4C(u32 arg0, s32 arg1);
void fn_1_1BF1C(u32 arg0);
void fn_1_1C120(void);
void fn_1_1C174(void);
void fn_1_1C478(void);
void fn_1_1C77C(void);
void fn_1_1CABC(s32 arg0);

u8 lbl_1_bss_6AC;
s32 lbl_1_bss_63C[0x1C];
MpexDllUnkStruct4 lbl_1_bss_5DC;
MpexDllUnkStruct4 lbl_1_bss_45C[4];
s32 lbl_1_bss_448[5];
s32 lbl_1_bss_444;
Process *lbl_1_bss_440;

void fn_1_1264C(Process *arg0)
{
    s32 var_r31;

    lbl_1_bss_440 = arg0;
    fn_1_1490C();
    fn_1_16320();
    fn_1_1A3BC();
    HuPrcChildCreate(fn_1_1B294, 0x3E8, 0x2000, 0, lbl_1_bss_440);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuPrcChildCreate(fn_1_1B338, 0x3E8, 0x2000, 0, lbl_1_bss_440);
    }
}

s32 fn_1_126EC(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r29 = -1;
    fn_1_14EF0();
    fn_1_1B834();
    fn_1_1BA78(0x1A0005, -1, -1);
    fn_1_1B7D0(1);
    fn_1_1BF1C(0x330091);
    lbl_1_bss_5DC.unk_04 = (MpexDllUnkFunc2)fn_1_157C4;
    var_r29 = -1;
    while (TRUE) {
        fn_1_1B7D0(1);
        var_r30 = 0;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_45C[var_r31].unk_14 == 0) {
                var_r30++;
            }
        }
        if (var_r29 != var_r30) {
            var_r29 = var_r30;
            fn_1_1BA78(var_r30 + 0x1A001B, -1, 1);
        }
        if (lbl_1_bss_5DC.unk_28 != 0) {
            continue;
        }
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
    fn_1_15774();
    lbl_1_bss_5DC.unk_04 = NULL;
    fn_1_1C120();
    if (var_r28 == 1) {
        var_r27 = 0;
        var_r26 = 0;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_45C[var_r31].unk_50 == 0) {
                var_r27++;
            }
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (var_r26 < var_r27) {
                if (HuPadStatGet(var_r31) != -1) {
                    lbl_1_bss_45C[var_r31].unk_50 = 0;
                    var_r26++;
                }
                else {
                    lbl_1_bss_45C[var_r31].unk_50 = 1;
                }
            }
            else {
                lbl_1_bss_45C[var_r31].unk_50 = 1;
            }
        }
    }
    fn_1_1B9F4();
    fn_1_154A4();
    return var_r28;
}

s32 fn_1_12910(s32 arg0, s32 arg1)
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
            lbl_1_bss_45C[var_r31].unk_50 = 1;
        }
    }
    else {
        var_r30 = 4;
    }
    fn_1_17374();
    if (arg0 == 0) {
        fn_1_16D3C(0);
    }
    fn_1_1B834();
    fn_1_1B7D0(1);
    if (arg1 == 1) {
        fn_1_1BA78(0x1E005E, -1, -1);
    }
    else {
        fn_1_1BA78(0x1A0009, -1, -1);
    }
    fn_1_1BF1C(0x330092);
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        if (lbl_1_bss_45C[var_r31].unk_50 == 0) {
            lbl_1_bss_45C[var_r31].unk_04 = (MpexDllUnkFunc2)fn_1_17B04;
        }
    }
    while (TRUE) {
        fn_1_1B7D0(1);
        if ((lbl_1_bss_45C->unk_08 == 0) && ((*HuPadBtnDown & 0x200) != 0)) {
            HuAudFXPlay(3);
            if (lbl_1_bss_5DC.unk_10 == 1) {
                lbl_1_bss_5DC.unk_10 = 0;
                continue;
            }
            var_r27 = 0;
            break;
        }
        else {
            for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
                if (lbl_1_bss_45C[var_r31].unk_50 == 0 && lbl_1_bss_45C[var_r31].unk_08 != 1) {
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
        lbl_1_bss_45C[var_r31].unk_04 = NULL;
    }
    fn_1_1C120();
    fn_1_1B9F4();
    if (var_r27 == 0) {
        fn_1_17170(0);
        return 0;
    }
    var_r29 = 0;
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        if (lbl_1_bss_45C[var_r31].unk_50 != 0) {
            lbl_1_bss_45C[var_r31].unk_5C = 0;
            var_r29++;
        }
    }
    if ((var_r29 == 0) || ((arg1 == 2) && (var_r29 == 2))) {
        fn_1_17170(0);
        return 2;
    }
    if (arg1 == 2) {
        lbl_1_bss_45C[1].unk_4C = 0;
    }
    return 1;
}

void fn_1_12BEC(s32 arg0)
{
    fn_1_12910(arg0, 4);
}

s32 fn_1_12C18(s32 arg0, s32 arg1)
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
            fn_1_168F0(0, 2);
        }
        else {
            fn_1_168F0(0, 1);
        }
    }
    fn_1_1B834();
    while (TRUE) {
        fn_1_1B7D0(1);
        var_r25 = 0;
        for (var_r31 = 0; var_r31 < arg1; var_r31++) {
            if ((lbl_1_bss_45C[var_r31].unk_50 != 0) && (lbl_1_bss_45C[var_r31].unk_08 == 0)) {
                var_r25++;
            }
        }
        if (var_r26 == -1) {
            fn_1_1BB4C(var_r25 + 0x1A0023, 1);
            fn_1_1BA78(0x1A0028, -1, var_r26);
        }
        else {
            fn_1_1BB4C(var_r25 + 0x1A0023, 1);
            fn_1_1BA78(0x1A0028, -1, var_r26);
        }
        var_r26 = 1;
        fn_1_1BF1C(0x330092);
        for (var_r31 = 0; var_r31 < arg1; var_r31++) {
            if ((lbl_1_bss_45C[var_r31].unk_50 != 0) && (lbl_1_bss_45C[var_r31].unk_08 == 0)) {
                var_r30 = var_r31;
                lbl_1_bss_45C[var_r31].unk_0C = var_r27;
                fn_1_18610(&lbl_1_bss_45C[var_r31]);
                lbl_1_bss_45C[var_r31].unk_04 = (MpexDllUnkFunc2)fn_1_18DCC;
                break;
            }
        }
        while (TRUE) {
            fn_1_1B7D0(1);
            if (((HuPadBtnDown[lbl_1_bss_45C->unk_58] & 0x200) != 0) && (lbl_1_bss_45C[var_r30].unk_08 == 0) && (lbl_1_bss_5DC.unk_30 == 0)) {
                HuAudFXPlay(3);
                if (var_r27 == -1) {
                    var_r29 = 0;
                }
                else {
                    var_r29 = 1;
                }
                break;
            }
            else if (lbl_1_bss_45C[var_r30].unk_08 == 1) {
                for (var_r31 = 0; var_r31 < arg1; var_r31++) {
                    if (lbl_1_bss_45C[var_r31].unk_08 == 0) {
                        lbl_1_bss_45C[var_r31].unk_5C = 0;
                    }
                }
                lbl_1_bss_45C[var_r30].unk_04 = NULL;
                fn_1_1BA78(0x1A0022, -1, 1);
                fn_1_1B7D0(1);
                fn_1_1BF1C(0x330093);
                var_r29 = fn_1_19A98(&lbl_1_bss_45C[var_r30]);
                if (var_r29 == 1) {
                    HuAudFXPlay(2);
                    lbl_1_bss_45C[var_r30].unk_10 = 1;
                    var_r29 = 4;
                    var_r27 = var_r30;
                }
                else {
                    HuAudFXPlay(3);
                    lbl_1_bss_45C[var_r30].unk_10 = 0;
                    var_r29 = 4;
                    lbl_1_bss_45C[var_r30].unk_08 = 0;
                    fn_1_18D30(&lbl_1_bss_45C[var_r30]);
                    fn_1_18610(&lbl_1_bss_45C[var_r30]);
                }
                break;
            }
        }
        for (var_r31 = 0; var_r31 < arg1; var_r31++) {
            lbl_1_bss_45C[var_r31].unk_04 = NULL;
        }
        for (var_r31 = 0; var_r31 < arg1; var_r31++) {
            if (lbl_1_bss_45C[var_r31].unk_08 == 0) {
                break;
            }
        }
        if (var_r31 == arg1) {
            var_r29 = 3;
            break;
        }
        else {
            if (var_r29 == 1) {
                fn_1_18610(&lbl_1_bss_45C[var_r30]);
                fn_1_18D30(&lbl_1_bss_45C[var_r30]);
                fn_1_18610(&lbl_1_bss_45C[lbl_1_bss_45C[var_r30].unk_0C]);
                var_r27 = lbl_1_bss_45C[lbl_1_bss_45C[var_r30].unk_0C].unk_0C;
                lbl_1_bss_45C[lbl_1_bss_45C[var_r30].unk_0C].unk_08 = 0;
            }
            else if (var_r29 != 4) {
                if (var_r29 == 0) {
                    fn_1_18D30(&lbl_1_bss_45C[var_r30]);
                }
                break;
            }
        }
        var_r24 = -1;
    }
    fn_1_1C120();
    fn_1_1B9F4();
    if (var_r29 != 0) {
        fn_1_17170(0);
    }
    return var_r29;
}

void fn_1_13130(s32 arg0)
{
    fn_1_12C18(arg0, 4);
}

void fn_1_1315C(void)
{
    fn_1_12910(0, 1);
}

s32 fn_1_13184(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r26 = -1;
    fn_1_151C8();
    fn_1_1B834();
    fn_1_1BA78(0x1A0005, -1, -1);
    fn_1_1B7D0(1);
    fn_1_1BF1C(0x330091);
    lbl_1_bss_5DC.unk_04 = (MpexDllUnkFunc2)fn_1_15D48;

    while (TRUE) {
        fn_1_1B7D0(1);
        var_r30 = 0;
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            if (lbl_1_bss_45C[var_r31].unk_14 == 0) {
                var_r30++;
            }
        }
        if (var_r26 != var_r30) {
            var_r26 = var_r30;
            fn_1_1BA78(var_r30 + 0x330093, -1, 1);
        }
        if (lbl_1_bss_5DC.unk_28 != 0) {
            continue;
        }
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
    fn_1_15774();
    lbl_1_bss_5DC.unk_04 = NULL;
    fn_1_1C120();
    if (var_r28 == 1) {
        var_r29 = 0;
        var_r27 = 0;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_45C[var_r31].unk_50 == 0) {
                var_r29++;
            }
        }
        if (var_r29 >= 2) {
            var_r29 = 2;
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (var_r27 < var_r29) {
                if (HuPadStatGet(var_r31) != -1) {
                    lbl_1_bss_45C[var_r31].unk_50 = 0;
                    lbl_1_bss_45C[var_r31].unk_4C = 0;
                    var_r27++;
                }
                else {
                    lbl_1_bss_45C[var_r31].unk_50 = 1;
                    lbl_1_bss_45C[var_r31].unk_4C = 1;
                }
            }
            else {
                lbl_1_bss_45C[var_r31].unk_50 = 1;
                lbl_1_bss_45C[var_r31].unk_4C = 1;
            }
        }
    }
    fn_1_1B9F4();
    fn_1_154A4();
    return var_r28;
}

void fn_1_133F8(s32 arg0)
{
    fn_1_12910(arg0, 2);
}

void fn_1_13424(s32 arg0)
{
    fn_1_12C18(arg0, 2);
}

void fn_1_13450(void)
{
    fn_1_126EC(0);
}

s32 fn_1_13474(s32 arg0)
{
    s32 spC[2];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    spC[1] = 0;
    spC[0] = 0;
    var_r30 = 4;
    var_r28 = 4;
    if (var_r28 == 1) {
        var_r30 = 1;
        for (var_r31 = 1; var_r31 < 4; var_r31++) {
            lbl_1_bss_45C[var_r31].unk_50 = 1;
        }
    }
    else {
        var_r30 = 4;
    }
    fn_1_17374();
    if (arg0 == 0) {
        fn_1_16D3C(3);
    }
    fn_1_1B834();
    fn_1_1B7D0(1);
    fn_1_1BA78(0x1A0009, -1, -1);
    fn_1_1BF1C(0x330092);
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        if (lbl_1_bss_45C[var_r31].unk_50 == 0) {
            lbl_1_bss_45C[var_r31].unk_04 = (MpexDllUnkFunc2)fn_1_17B04;
        }
    }
    while (TRUE) {
        fn_1_1B7D0(1);
        if ((lbl_1_bss_45C->unk_08 == 0) && (HuPadBtnDown[0] & PAD_BUTTON_B)) {
            HuAudFXPlay(3);
            if (lbl_1_bss_5DC.unk_10 == 1) {
                lbl_1_bss_5DC.unk_10 = 0;
                continue;
            }
            var_r27 = 0;
            break;
        }
        else {
            for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
                if (lbl_1_bss_45C[var_r31].unk_50 == 0 && lbl_1_bss_45C[var_r31].unk_08 != 1) {
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
        lbl_1_bss_45C[var_r31].unk_04 = NULL;
    }
    fn_1_1C120();
    fn_1_1B9F4();
    if (var_r27 == 0) {
        fn_1_17170(0);
        return 0;
    }
    var_r29 = 0;
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        if (lbl_1_bss_45C[var_r31].unk_50 != 0) {
            lbl_1_bss_45C[var_r31].unk_5C = 1;
            var_r29++;
        }
    }
    if ((var_r29 == 0) || ((var_r28 == 2) && (var_r29 == 2))) {
        fn_1_17170(3);
        return 2;
    }
    if (var_r28 == 2) {
        lbl_1_bss_45C[1].unk_4C = 0;
    }
    return 1;
}

s32 fn_1_13730(s32 arg0)
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
        fn_1_168F0(3, 3);
    }
    fn_1_1B834();
    while (TRUE) {
        fn_1_1B7D0(1);
        var_r25 = 0;
        for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
            if ((lbl_1_bss_45C[var_r31].unk_50 != 0) && (lbl_1_bss_45C[var_r31].unk_08 == 0)) {
                var_r25++;
            }
        }
        if (var_r26 == -1) {
            fn_1_1BB4C(var_r25 + 0x1A0023, 1);
            fn_1_1BA78(0x1A0028, -1, var_r26);
        }
        else {
            fn_1_1BB4C(var_r25 + 0x1A0023, 1);
            fn_1_1BA78(0x1A0028, -1, var_r26);
        }
        var_r26 = 1;
        fn_1_1BF1C(0x330092);
        for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
            if ((lbl_1_bss_45C[var_r31].unk_50 != 0) && (lbl_1_bss_45C[var_r31].unk_08 == 0)) {
                var_r30 = var_r31;
                lbl_1_bss_45C[var_r31].unk_0C = var_r27;
                fn_1_18610(&lbl_1_bss_45C[var_r31]);
                lbl_1_bss_45C[var_r31].unk_04 = (MpexDllUnkFunc2)fn_1_18DCC;
                break;
            }
        }
        while (TRUE) {
            fn_1_1B7D0(1);
            if (((HuPadBtnDown[lbl_1_bss_45C->unk_58] & PAD_BUTTON_B) != 0) && (lbl_1_bss_45C[var_r30].unk_08 == 0) && (lbl_1_bss_5DC.unk_30 == 0)) {
                HuAudFXPlay(3);
                if (var_r27 == -1) {
                    var_r29 = 0;
                }
                else {
                    var_r29 = 1;
                }
                break;
            }
            else if (lbl_1_bss_45C[var_r30].unk_08 == 1) {
                for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
                    if (lbl_1_bss_45C[var_r31].unk_08 == 0) {
                        lbl_1_bss_45C[var_r31].unk_5C = 1;
                    }
                }
                lbl_1_bss_45C[var_r30].unk_04 = NULL;
                fn_1_1BA78(0x1A0022, -1, 1);
                fn_1_1B7D0(1);
                fn_1_1BF1C(0x330093);
                var_r29 = fn_1_19A98(&lbl_1_bss_45C[var_r30]);
                if (var_r29 == 1) {
                    HuAudFXPlay(2);
                    lbl_1_bss_45C[var_r30].unk_10 = 1;
                    var_r29 = 4;
                    var_r27 = var_r30;
                }
                else {
                    HuAudFXPlay(3);
                    lbl_1_bss_45C[var_r30].unk_10 = 0;
                    var_r29 = 4;
                    lbl_1_bss_45C[var_r30].unk_08 = 0;
                    fn_1_18D30(&lbl_1_bss_45C[var_r30]);
                    fn_1_18610(&lbl_1_bss_45C[var_r30]);
                }
                break;
            }
        }
        for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
            lbl_1_bss_45C[var_r31].unk_04 = NULL;
        }
        for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
            if (lbl_1_bss_45C[var_r31].unk_08 == 0) {
                break;
            }
        }
        if (var_r31 == var_r28) {
            var_r29 = 3;
            break;
        }
        else {
            if (var_r29 == 1) {
                fn_1_18610(&lbl_1_bss_45C[var_r30]);
                fn_1_18D30(&lbl_1_bss_45C[var_r30]);
                fn_1_18610(&lbl_1_bss_45C[lbl_1_bss_45C[var_r30].unk_0C]);
                var_r27 = lbl_1_bss_45C[lbl_1_bss_45C[var_r30].unk_0C].unk_0C;
                lbl_1_bss_45C[lbl_1_bss_45C[var_r30].unk_0C].unk_08 = 0;
            }
            else if (var_r29 != 4) {
                if (var_r29 == 0) {
                    fn_1_18D30(&lbl_1_bss_45C[var_r30]);
                }
                break;
            }
            var_r24 = -1;
        }
    }
    fn_1_1C120();
    fn_1_1B9F4();
    if (var_r29 != 0) {
        fn_1_17170(3);
    }
    return var_r29;
}

void fn_1_13C30(s32 arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GWPlayer[var_r31].team = GWPlayerCfg[var_r31].group = lbl_1_bss_45C[var_r31].unk_4C;
        GWPlayer[var_r31].com = GWPlayerCfg[var_r31].iscom = lbl_1_bss_45C[var_r31].unk_50;
        GWPlayer[var_r31].diff = GWPlayerCfg[var_r31].diff = lbl_1_bss_45C[var_r31].unk_54;
        if (lbl_1_bss_444 != 0) {
            if (lbl_1_bss_45C[var_r31].unk_5C <= 5) {
                GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = lbl_1_bss_45C[var_r31].unk_5C - 1;
            }
            else if (lbl_1_bss_45C[var_r31].unk_5C <= 0xB) {
                GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = lbl_1_bss_45C[var_r31].unk_5C - 3;
            }
            else {
                GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = fn_1_1B4AC(lbl_1_bss_45C[var_r31].unk_5C - 4);
            }
        }
        else if (arg0 == 1) {
            if (var_r31 != 0) {
                lbl_1_bss_45C[var_r31].unk_5C = lbl_1_bss_45C[var_r31 - 1].unk_5C + 1;
                if (lbl_1_bss_45C[var_r31].unk_5C >= 8) {
                    lbl_1_bss_45C[var_r31].unk_5C = 0;
                }
            }
            GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = lbl_1_bss_45C[var_r31].unk_5C;
        }
        else {
            GWPlayer[var_r31].character = GWPlayerCfg[var_r31].character = lbl_1_bss_45C[var_r31].unk_5C;
        }
        GWPlayer[var_r31].port = GWPlayerCfg[var_r31].pad_idx = lbl_1_bss_45C[var_r31].unk_58;
    }
    OSReport("\n\n#################### SET PLAYERDATA ####################\n");
    OSReport("ID) GRP:COM:DIF:CHR:PAD\n");
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        OSReport("%2d) %3d:%3d:%3d:%3d:%3d\n", var_r31, GWPlayerCfg[var_r31].group, GWPlayerCfg[var_r31].iscom, GWPlayerCfg[var_r31].diff,
            GWPlayerCfg[var_r31].character, GWPlayerCfg[var_r31].pad_idx);
    }
    OSReport("########################################################\n");
}

s32 fn_1_140B0(s32 arg0, s32 arg1)
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
        lbl_1_bss_444 = 1;
    }
    else {
        lbl_1_bss_444 = 0;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_45C[var_r31].unk_48 = var_r31;
        lbl_1_bss_45C[var_r31].unk_4C = 0;
        lbl_1_bss_45C[var_r31].unk_50 = 0;
        lbl_1_bss_45C[var_r31].unk_54 = 0;
        if (lbl_1_bss_444 != 0) {
            lbl_1_bss_45C[var_r31].unk_5C = var_r31 + 1;
        }
        else {
            lbl_1_bss_45C[var_r31].unk_5C = var_r31;
        }
        lbl_1_bss_45C[var_r31].unk_58 = var_r31;
    }
    if (arg1 == 1) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            lbl_1_bss_45C[var_r31].unk_48 = var_r31;
            lbl_1_bss_45C[var_r31].unk_4C = GWPlayerCfg[var_r31].group;
            lbl_1_bss_45C[var_r31].unk_50 = GWPlayerCfg[var_r31].iscom;
            lbl_1_bss_45C[var_r31].unk_54 = GWPlayerCfg[var_r31].diff;
            lbl_1_bss_45C[var_r31].unk_5C = GWPlayerCfg[var_r31].character;
            lbl_1_bss_45C[var_r31].unk_58 = GWPlayerCfg[var_r31].pad_idx;
            lbl_1_bss_45C[var_r31].unk_08 = lbl_1_bss_45C[var_r31].unk_0C = lbl_1_bss_45C[var_r31].unk_10 = lbl_1_bss_45C[var_r31].unk_14 = 0;
            lbl_1_bss_45C[var_r31].unk_28 = lbl_1_bss_45C[var_r31].unk_2C = lbl_1_bss_45C[var_r31].unk_30 = lbl_1_bss_45C[var_r31].unk_34 = 0;

            switch (arg0) {
                case 0:
                    if (lbl_1_bss_45C[var_r31].unk_50 == 0) {
                        lbl_1_bss_45C[var_r31].unk_08 = 1;
                    }
                    else {
                        var_r27 = 1;
                    }
                    break;
                case 2:
                    if (lbl_1_bss_45C[var_r31].unk_50 == 0) {
                        lbl_1_bss_45C[var_r31].unk_08 = 1;
                        var_r26++;
                    }
                    else {
                        var_r27 = 1;
                    }
                    break;
                case 3:
                    if (lbl_1_bss_45C[var_r31].unk_50 == 0) {
                        lbl_1_bss_45C[var_r31].unk_08 = 1;
                        var_r26++;
                    }
                    else {
                        var_r27 = 1;
                    }
                    if (lbl_1_bss_45C[var_r31].unk_5C <= 3) {
                        lbl_1_bss_45C[var_r31].unk_5C += 1;
                    }
                    else if (lbl_1_bss_45C[var_r31].unk_5C <= 7) {
                        lbl_1_bss_45C[var_r31].unk_5C += 3;
                    }
                    else {
                        lbl_1_bss_45C[var_r31].unk_5C = fn_1_1B42C(lbl_1_bss_45C[var_r31].unk_5C) + 4;
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
        fn_1_1B7D0(1);
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
                var_r28 = fn_1_126EC(var_r30);
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
                var_r23 = fn_1_12910(var_r30, 4);
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
                var_r22 = fn_1_12C18(var_r30, 4);
                var_r28 = var_r22;
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
                var_r21 = fn_1_12910(0, 1);
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
                var_r28 = fn_1_13184();
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
                var_r20 = fn_1_12910(var_r30, 2);
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
                var_r19 = fn_1_12C18(var_r30, 2);
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
                var_r18 = fn_1_126EC(0);
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
                var_r28 = fn_1_13474(var_r30);
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
                var_r28 = fn_1_13730(var_r30);
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
                fn_1_13C30(arg0);
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

void fn_1_148BC(s32 arg0)
{
    fn_1_1AF78(arg0);
}

void fn_1_148E4(s32 arg0)
{
    fn_1_1B0DC(arg0);
}

s32 lbl_1_data_5C4[4][2] = { { -0x69, 0 }, { -0x23, 0 }, { 0x23, 0 }, { 0x69, 0 } };
s32 lbl_1_data_5E4[8][2] = {
    { -0x7B, -0x34 },
    { -0x29, -0x34 },
    { 0x29, -0x34 },
    { 0x7B, -0x34 },
    { -0x7B, 0x34 },
    { -0x29, 0x34 },
    { 0x29, 0x34 },
    { 0x7B, 0x34 },
};
s32 lbl_1_data_624[0xE][2] = {
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
s32 lbl_1_data_694[0x12][2] = {
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
s32 lbl_1_data_724[4][2] = { { -0x45, -8 }, { -0x17, -8 }, { 0x17, -8 }, { 0x45, -8 } };
s32 lbl_1_data_744[2] = { 0x00, 0xFFFFFFF8 };
s32 lbl_1_data_74C[2][2] = { { -0x17, -8 }, { 0x17, -8 } };
s32 lbl_1_data_75C[4][2] = { { -0x59, -8 }, { -0x2B, -8 }, { 0x2B, -8 }, { 0x59, -8 } };
s32 lbl_1_data_77C = -1;
s32 lbl_1_data_780[2] = {-1, 0};

void fn_1_1490C(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r28;

    var_r30 = HuSprGrpCreate(0xB);
    *lbl_1_bss_63C = var_r30;
    var_r29 = HuSprCreate(HuSprAnimReadFile(0x640046), 0xBB8, 0);
    HuSprGrpMemberSet(var_r30, 0, var_r29);
    HuSprPosSet(var_r30, 0, 0.0f, 0.0f);
    var_r28 = HuSprAnimReadFile(0x640047);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r29 = HuSprCreate(var_r28, 0x3E8, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 1, var_r29);
        HuSprBankSet(var_r30, var_r31 + 1, var_r31);
    }
    var_r28 = HuSprAnimReadFile(0x640048);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = HuSprCreate(var_r28, 0x76C, 0);
        HuSprGrpMemberSet(var_r30, var_r31 + 3, var_r29);
        HuSprPosSet(var_r30, var_r31 + 3, lbl_1_data_5C4[var_r31 % 4][0], lbl_1_data_5C4[0][1]);
        HuSprBankSet(var_r30, var_r31 + 3, 0);
    }
    fn_1_14B28();
    fn_1_14E54();
}

void fn_1_14B28(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = *lbl_1_bss_63C;
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprAttrReset(var_r30, 0, 4);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 3, 4);
        HuSprPosSet(var_r30, var_r31 + 3, lbl_1_data_5C4[var_r31 % 4][0], lbl_1_data_5C4[0][1]);
        HuSprBankSet(var_r30, var_r31 + 3, 0);
    }
    HuSprGrpPosSet(var_r30, 288.0f, -390.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_45C[var_r31].unk_14 = lbl_1_bss_45C[var_r31].unk_50 = 0;
    }
}

void fn_1_14CBC(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = *lbl_1_bss_63C;
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprAttrReset(var_r30, 0, 4);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrReset(var_r30, var_r31 + 3, 4);
        HuSprPosSet(var_r30, var_r31 + 3, lbl_1_data_5C4[var_r31 % 4 + 1][0], lbl_1_data_5C4[0][1]);
        HuSprBankSet(var_r30, var_r31 + 3, 0);
    }
    HuSprGrpPosSet(var_r30, 288.0f, -390.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_45C[var_r31].unk_14 = lbl_1_bss_45C[var_r31].unk_50 = 0;
    }
}

void fn_1_14E54(void)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = *lbl_1_bss_63C;
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprGrpPosSet(var_r30, 288.0f, 110.0f);
    HuSprGrpScaleSet(var_r30, 1.0f, 1.0f);
}

void fn_1_14EF0(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = *lbl_1_bss_63C;
    var_r29 = *lbl_1_bss_63C;
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r29, var_r31, 4);
    }
    HuSprAttrReset(var_r29, 0, 4);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprAttrReset(var_r29, var_r31 + 3, 4);
        HuSprPosSet(var_r29, var_r31 + 3, lbl_1_data_5C4[var_r31 % 4][0], lbl_1_data_5C4[0][1]);
        HuSprBankSet(var_r29, var_r31 + 3, 0);
    }
    HuSprGrpPosSet(var_r29, 288.0f, -390.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_45C[var_r31].unk_14 = lbl_1_bss_45C[var_r31].unk_50 = 0;
    }
    for (var_r30 = 0; var_r30 <= 0x3C; var_r30++) {
        fn_1_1B7D0(1);
        if (var_r30 <= 0x32) {
            var_f31 = fn_1_1B64C(-500.0f, 10.0f, var_r30, 50.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, 0.0f, var_r30 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r28, 288.0f, 110.0f + var_f31);
    }
    HuSprGrpPosSet(var_r28, 288.0f, 110.0f);
    fn_1_1B7D0(0xA);
}

void fn_1_151C8(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = *lbl_1_bss_63C;
    var_r29 = *lbl_1_bss_63C;
    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        HuSprAttrSet(var_r29, var_r31, 4);
    }
    HuSprAttrReset(var_r29, 0, 4);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        HuSprAttrReset(var_r29, var_r31 + 3, 4);
        HuSprPosSet(var_r29, var_r31 + 3, lbl_1_data_5C4[var_r31 % 4 + 1][0], lbl_1_data_5C4[0][1]);
        HuSprBankSet(var_r29, var_r31 + 3, 0);
    }
    HuSprGrpPosSet(var_r29, 288.0f, -390.0f);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_45C[var_r31].unk_14 = lbl_1_bss_45C[var_r31].unk_50 = 0;
    }
    for (var_r30 = 0; var_r30 <= 0x3C; var_r30++) {
        fn_1_1B7D0(1);
        if (var_r30 <= 0x32) {
            var_f31 = fn_1_1B64C(-500.0f, 10.0f, var_r30, 50.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, 0.0f, var_r30 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r28, 288.0f, 110.0f + var_f31);
    }
    HuSprGrpPosSet(var_r28, 288.0f, 110.0f);
    fn_1_1B7D0(0xA);
}

void fn_1_154A4(void)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28 = *lbl_1_bss_63C;

    fn_1_1B7D0(0xA);
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_1B7D0(1);
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_1B64C(0.0f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(var_r28, 288.0f, 110.0f + var_f31);
    }
    HuSprGrpPosSet(var_r28, 288.0f, -390.0f);
    var_r29 = *lbl_1_bss_63C;
    for (var_r30 = 0; var_r30 < 0xB; var_r30++) {
        HuSprAttrSet(var_r29, var_r30, 4);
    }
    HuSprGrpPosSet(var_r29, 288.0f, 110.0f);
    HuSprGrpScaleSet(var_r29, 1.0f, 1.0f);
}

void fn_1_15684(s32 arg0)
{
    s32 var_r31;

    var_r31 = *lbl_1_bss_63C;
    HuSprAttrReset(var_r31, 1, 4);
    HuSprAttrReset(var_r31, 2, 4);
    HuSprPosSet(var_r31, 1, -155.0f, 0.0f);
    HuSprPosSet(var_r31, 2, 155.0f, 0.0f);
    if (arg0 == 2) {
        HuSprPosSet(var_r31, 1, -80.0f, 0.0f);
        HuSprPosSet(var_r31, 2, 80.0f, 0.0f);
    }
}

void fn_1_15774(void)
{
    s32 var_r31;

    var_r31 = *lbl_1_bss_63C;
    HuSprAttrSet(var_r31, 1, 4);
    HuSprAttrSet(var_r31, 2, 4);
}

void fn_1_157C4(void)
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

    var_r27 = lbl_1_bss_63C[0];
    var_r29 = var_r28 = var_r26 = var_r24 = 0;
    lbl_1_bss_5DC.unk_28 = 0;
    var_r29 = 1;
    for (var_r31 = 1; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_45C[var_r31].unk_50 == 0) {
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
        var_r25 = lbl_1_bss_63C[0];
        HuSprAttrReset(var_r25, 1, 4);
        HuSprAttrReset(var_r25, 2, 4);
        HuSprPosSet(var_r25, 1, -155.0f, 0.0f);
        HuSprPosSet(var_r25, 2, 155.0f, 0.0f);
        if (*HuPadStkX >= 5) {
            var_r29++;
            var_r26 = 1;
        }
        else if (*HuPadStkX <= -5) {
            var_r29--;
            var_r26 = -1;
        }
    }
    else {
        var_r23 = lbl_1_bss_63C[0];
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
        lbl_1_bss_5DC.unk_28 = 1;
        HuAudFXPlay(0);
        for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
            if (var_r31 <= 5) {
                var_f31 = fn_1_1B64C(0.0f, 10.0f, var_r31, 5.0f);
                var_f30 = fn_1_1B64C(1.0f, 0.0f, var_r31, 5.0f);
            }
            else {
                var_f31 = fn_1_1B64C(10.0f, 0.0f, var_r31 - 5, 5.0f);
                var_f30 = fn_1_1B64C(0.0f, 1.0f, var_r31 - 5, 5.0f);
            }
            if (var_r26 == 1) {
                HuSprPosSet(var_r27, 2, 3.0f + (155.0f + var_f31), 0.0f);
            }
            else if (var_r26 == -1) {
                HuSprPosSet(var_r27, 1, (-155.0f - var_f31) - 3.0f, 0.0f);
            }
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                if ((var_r30 < var_r29) && (lbl_1_bss_45C[var_r30].unk_50 == 1)) {
                    lbl_1_bss_45C[var_r30].unk_14 = 0;
                    HuSprScaleSet(var_r27, var_r30 + 3, var_f30, 1.0f);
                    if (var_r31 == 5) {
                        HuSprBankSet(var_r27, var_r30 + 3, 0);
                    }
                }
                else if ((var_r30 >= var_r29) && (lbl_1_bss_45C[var_r30].unk_50 == 0)) {
                    lbl_1_bss_45C[var_r30].unk_14 = 1;
                    HuSprScaleSet(var_r27, var_r30 + 3, var_f30, 1.0f);
                    if (var_r31 == 5) {
                        HuSprBankSet(var_r27, var_r30 + 3, 1);
                    }
                }
            }
            fn_1_1B7D0(1);
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            if (var_r30 < var_r29) {
                lbl_1_bss_45C[var_r30].unk_50 = 0;
            }
            else {
                lbl_1_bss_45C[var_r30].unk_50 = 1;
            }
        }
    }
    lbl_1_bss_5DC.unk_28 = 0;
}

void fn_1_15D48(void)
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

    var_r27 = lbl_1_bss_63C[0];
    var_r29 = var_r28 = var_r26 = var_r24 = 0;
    lbl_1_bss_5DC.unk_28 = 0;
    var_r29 = 1;
    for (var_r31 = 1; var_r31 < 2; var_r31++) {
        if (lbl_1_bss_45C[var_r31].unk_50 == 0) {
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
        var_r25 = lbl_1_bss_63C[0];
        HuSprAttrReset(var_r25, 1, 4);
        HuSprAttrReset(var_r25, 2, 4);
        HuSprPosSet(var_r25, 1, -155.0f, 0.0f);
        HuSprPosSet(var_r25, 2, 155.0f, 0.0f);
        HuSprPosSet(var_r25, 1, -80.0f, 0.0f);
        HuSprPosSet(var_r25, 2, 80.0f, 0.0f);
        if (*HuPadStkX >= 5) {
            var_r29++;
            var_r26 = 1;
        }
        else if (*HuPadStkX <= -5) {
            var_r29--;
            var_r26 = -1;
        }
    }
    else {
        var_r23 = lbl_1_bss_63C[0];
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
        lbl_1_bss_5DC.unk_28 = 1;
        HuAudFXPlay(0);
        for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
            if (var_r31 <= 5) {
                var_f31 = fn_1_1B64C(0.0f, 10.0f, var_r31, 5.0f);
                var_f30 = fn_1_1B64C(1.0f, 0.0f, var_r31, 5.0f);
            }
            else {
                var_f31 = fn_1_1B64C(10.0f, 0.0f, var_r31 - 5, 5.0f);
                var_f30 = fn_1_1B64C(0.0f, 1.0f, var_r31 - 5, 5.0f);
            }
            if (var_r26 == 1) {
                HuSprPosSet(var_r27, 2, 3.0f + (77.0f + var_f31), 0.0f);
            }
            else if (var_r26 == -1) {
                HuSprPosSet(var_r27, 1, (-77.0f - var_f31) - 3.0f, 0.0f);
            }
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                if ((var_r30 < var_r29) && (lbl_1_bss_45C[var_r30].unk_50 == 1)) {
                    lbl_1_bss_45C[var_r30].unk_14 = 0;
                    HuSprScaleSet(var_r27, var_r30 + 3, var_f30, 1.0f);
                    if (var_r31 == 5) {
                        HuSprBankSet(var_r27, var_r30 + 3, 0);
                    }
                }
                else if ((var_r30 >= var_r29) && (lbl_1_bss_45C[var_r30].unk_50 == 0)) {
                    lbl_1_bss_45C[var_r30].unk_14 = 1;
                    HuSprScaleSet(var_r27, var_r30 + 3, var_f30, 1.0f);
                    if (var_r31 == 5) {
                        HuSprBankSet(var_r27, var_r30 + 3, 1);
                    }
                }
            }
            fn_1_1B7D0(1);
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            if (var_r30 < var_r29) {
                lbl_1_bss_45C[var_r30].unk_50 = 0;
            }
            else {
                lbl_1_bss_45C[var_r30].unk_50 = 1;
            }
        }
    }
    lbl_1_bss_5DC.unk_28 = 0;
}

void fn_1_16320(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r28;
    AnimData *var_r27;

    var_r29 = HuSprGrpCreate(0x36);
    lbl_1_bss_63C[1] = var_r29;
    var_r30 = HuSprCreate(HuSprAnimReadFile(0x64004A), 0xBB8, 0);
    HuSprGrpMemberSet(var_r29, 0, var_r30);
    HuSprPosSet(var_r29, 0, 0.0f, 0.0f);
    var_r28 = HuSprAnimReadFile(0x64005A);
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        var_r30 = HuSprCreate(HuSprAnimReadFile(var_r31 + 0x64004C), 0x76C, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 2, var_r30);
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(HuSprAnimReadFile(var_r31 + 0x64005B), 0x384, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x1E, var_r30);
        var_r30 = HuSprCreate(HuSprAnimReadFile(var_r31 + 0x640060), 0x3E8, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x22, var_r30);
    }
    var_r28 = HuSprAnimReadFile(0x64005F);
    var_r27 = HuSprAnimReadFile(0x640064);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x384, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x26, var_r30);
        var_r30 = HuSprCreate(var_r27, 0x3E8, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x2A, var_r30);
    }
    var_r28 = HuSprAnimReadFile(0x640065);
    var_r27 = HuSprAnimReadFile(0x640066);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x384, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x2E, var_r30);
        var_r30 = HuSprCreate(var_r27, 0x320, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x32, var_r30);
    }
    fn_1_16600(0);
    fn_1_16874(0);
}

void fn_1_16600(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_63C[1];
    for (var_r31 = 0; var_r31 < 0x36; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    if (arg0 != 3) {
        HuSprAttrReset(var_r30, 0, 4);
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_5E4[var_r31][0], lbl_1_data_5E4[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    else {
        HuSprAttrReset(var_r30, 1, 4);
        HuSprPosSet(var_r30, 1, 2.0f, 0.0f);
        for (var_r31 = 0; var_r31 < 0xE; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_624[var_r31][0], lbl_1_data_624[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    HuSprGrpPosSet(var_r30, 288.0f, -331.0f);
}

void fn_1_16874(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_63C[1];
    for (var_r31 = 0; var_r31 < 0x36; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprGrpPosSet(var_r30, 288.0f, -331.0f);
}

void fn_1_168F0(s32 arg0, s32 arg1)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_63C[1];
    var_r30 = lbl_1_bss_63C[1];
    for (var_r31 = 0; var_r31 < 0x36; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    if (arg0 != 3) {
        HuSprAttrReset(var_r30, 0, 4);
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_5E4[var_r31][0], lbl_1_data_5E4[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    else {
        HuSprAttrReset(var_r30, 1, 4);
        HuSprPosSet(var_r30, 1, 2.0f, 0.0f);
        for (var_r31 = 0; var_r31 < 0xE; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_624[var_r31][0], lbl_1_data_624[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    HuSprGrpPosSet(var_r30, 288.0f, -331.0f);
    if (arg1 == 1) {
        fn_1_1C174();
    }
    if (arg1 == 2) {
        fn_1_1C478();
    }
    if (arg1 == 3) {
        fn_1_1C77C();
    }
    for (var_r29 = 0; var_r29 <= 0x3C; var_r29++) {
        fn_1_1B7D0(1);
        if (var_r29 <= 0x32) {
            var_f31 = fn_1_1B64C(-500.0f, 10.0f, var_r29, 50.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, 0.0f, var_r29 - 0x32, 10.0f);
        }
        if (lbl_1_bss_444 != 0) {
            HuSprGrpPosSet(var_r28, 288.0f, 20.0f + (169.0f + var_f31));
        }
        else {
            HuSprGrpPosSet(var_r28, 288.0f, 169.0f + var_f31);
        }
    }
    if (lbl_1_bss_444 != 0) {
        HuSprGrpPosSet(var_r28, 288.0f, 189.0f);
        return;
    }
    HuSprGrpPosSet(var_r28, 288.0f, 169.0f);
}

void fn_1_16D3C(s32 arg0)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = lbl_1_bss_63C[1];
    var_r30 = lbl_1_bss_63C[1];
    for (var_r31 = 0; var_r31 < 0x36; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    if (arg0 != 3) {
        HuSprAttrReset(var_r30, 0, 4);
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_5E4[var_r31][0], lbl_1_data_5E4[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    else {
        HuSprAttrReset(var_r30, 1, 4);
        HuSprPosSet(var_r30, 1, 2.0f, 0.0f);
        for (var_r31 = 0; var_r31 < 0xE; var_r31++) {
            HuSprBankSet(var_r30, var_r31 + 2, 0);
            HuSprAttrReset(var_r30, var_r31 + 2, 4);
            HuSprPosSet(var_r30, var_r31 + 2, lbl_1_data_624[var_r31][0], lbl_1_data_624[var_r31][1]);
            HuSprBankSet(var_r30, var_r31 + 2, 0);
        }
    }
    HuSprGrpPosSet(var_r30, 288.0f, -331.0f);
    for (var_r29 = 0; var_r29 <= 0x3C; var_r29++) {
        fn_1_1B7D0(1);
        if (var_r29 <= 0x32) {
            var_f31 = fn_1_1B64C(-500.0f, 10.0f, var_r29, 50.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, 0.0f, var_r29 - 0x32, 10.0f);
        }
        if (lbl_1_bss_444 != 0) {
            HuSprGrpPosSet(var_r28, 288.0f, 20.0f + (169.0f + var_f31));
        }
        else {
            HuSprGrpPosSet(var_r28, 288.0f, 169.0f + var_f31);
        }
    }
    if (lbl_1_bss_444 != 0) {
        HuSprGrpPosSet(var_r28, 288.0f, 189.0f);
        return;
    }
    HuSprGrpPosSet(var_r28, 288.0f, 169.0f);
}

void fn_1_17170(s32 arg0)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r29 = lbl_1_bss_63C[1];
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_1B7D0(1);
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_1B64C(0.0f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        if (lbl_1_bss_444 != 0) {
            HuSprGrpPosSet(var_r29, 288.0f, 20.0f + (169.0f + var_f31));
        }
        else {
            HuSprGrpPosSet(var_r29, 288.0f, 169.0f + var_f31);
        }
    }
    HuSprGrpPosSet(var_r29, 288.0f, -331.0f);
    var_r28 = lbl_1_bss_63C[1];
    for (var_r30 = 0; var_r30 < 0x36; var_r30++) {
        HuSprAttrSet(var_r28, var_r30, 4);
    }
    HuSprGrpPosSet(var_r28, 288.0f, -331.0f);
}

void fn_1_17374(void)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = lbl_1_bss_63C[1];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprBankSet(var_r30, var_r31 + 0x1E, 0);
        HuSprBankSet(var_r30, var_r31 + 0x22, 0);
        HuSprBankSet(var_r30, var_r31 + 0x26, 0);
        HuSprBankSet(var_r30, var_r31 + 0x2A, 0);
        HuSprBankSet(var_r30, var_r31 + 0x2E, 0);
        HuSprBankSet(var_r30, var_r31 + 0x32, 0);
    }
    if (lbl_1_bss_444 != 0) {
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
        fn_1_1B7D0(1);
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if (lbl_1_bss_444 != 0) {
                var_f31 = fn_1_1B64C(lbl_1_data_694[lbl_1_bss_45C[var_r29].unk_5C][0], lbl_1_data_694[var_r29 + 1][0], var_r31, 10.0f);
                var_f30 = fn_1_1B64C(lbl_1_data_694[lbl_1_bss_45C[var_r29].unk_5C][1], lbl_1_data_694[1][1], var_r31, 10.0f);
            }
            else {
                var_f31 = fn_1_1B64C(lbl_1_data_5E4[lbl_1_bss_45C[var_r29].unk_5C % 4][0], lbl_1_data_5E4[var_r29][0], var_r31, 10.0f);
                var_f30 = fn_1_1B64C(lbl_1_data_5E4[(lbl_1_bss_45C[var_r29].unk_5C / 4) * 4][1], lbl_1_data_5E4[0][1], var_r31, 10.0f);
            }
            HuSprPosSet(var_r30, var_r29 + 0x1E, var_f31, var_f30);
            HuSprPosSet(var_r30, var_r29 + 0x22, var_f31, var_f30);
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_444 != 0) {
            HuSprPosSet(var_r30, var_r31 + 0x1E, lbl_1_data_694[var_r31 + 1][0], lbl_1_data_694[var_r31 + 1][1]);
            HuSprPosSet(var_r30, var_r31 + 0x22, lbl_1_data_694[var_r31 + 1][0], lbl_1_data_694[var_r31 + 1][1]);
            lbl_1_bss_45C[var_r31].unk_5C = var_r31 + 1;
            lbl_1_bss_45C[var_r31].unk_48 = var_r31;
            lbl_1_bss_45C[var_r31].unk_08 = 0;
        }
        else {
            HuSprPosSet(var_r30, var_r31 + 0x1E, lbl_1_data_5E4[var_r31][0], lbl_1_data_5E4[var_r31][1]);
            HuSprPosSet(var_r30, var_r31 + 0x22, lbl_1_data_5E4[var_r31][0], lbl_1_data_5E4[var_r31][1]);
            lbl_1_bss_45C[var_r31].unk_48 = var_r31;
            lbl_1_bss_45C[var_r31].unk_5C = var_r31;
            lbl_1_bss_45C[var_r31].unk_08 = 0;
        }
    }
}

void fn_1_17B04(omObjData *arg0, MpexDllUnkStruct4 *arg1)
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

    var_r24 = lbl_1_bss_63C[1];
    var_r27 = 0;
    var_r26 = 0;
    HuSprAttrReset(var_r24, arg1->unk_48 + 0x1E, 4);
    HuSprAttrReset(var_r24, arg1->unk_48 + 0x22, 4);
    if (lbl_1_bss_444 != 0) {
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
            if (lbl_1_bss_444 != 0) {
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
                fn_1_1CABC(var_r21);
                HuSprBankSet(var_r24, var_r21 + 2, 1);
            }
            else {
                fn_1_1CABC(arg1->unk_5C);
                HuSprBankSet(var_r24, arg1->unk_5C + 2, 1);
            }
            HuSprBankSet(var_r24, arg1->unk_48 + 0x1E, 1);
            HuSprBankSet(var_r24, arg1->unk_48 + 0x22, 1);
        }
        else if (lbl_1_bss_444 != 0) {
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
    else if (HuPadBtnDown[arg1->unk_48] & PAD_BUTTON_B) {
        arg1->unk_08 = 0;
        lbl_1_bss_5DC.unk_10 = 1;
        HuAudFXPlay(3);
        if (lbl_1_bss_444 != 0) {
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
    if (lbl_1_bss_444 != 0) {
        var_r25 = var_r30 + (var_r29 * 6);
    }
    else {
        var_r25 = var_r30 + (var_r29 * 4);
    }
    if (arg1->unk_5C != var_r25) {
        if (lbl_1_bss_444 != 0) {
            while (TRUE) {
                var_r25 = var_r30 + (var_r29 * 6);
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    if (((var_r28 != arg1->unk_48) && (lbl_1_bss_45C[var_r28].unk_50 == 0) && (var_r25 == lbl_1_bss_45C[var_r28].unk_5C))
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
                }
                if (var_r28 == 4) {
                    break;
                }
            }
        }
        else {
            do {
                var_r25 = var_r30 + (var_r29 * 4);
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    if ((var_r28 != arg1->unk_48) && (lbl_1_bss_45C[var_r28].unk_50 == 0) && (var_r25 == lbl_1_bss_45C[var_r28].unk_5C)) {
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
                        }
                        else if (((var_r30 + var_r27) <= 3) && ((var_r30 + var_r27) >= 0)) {
                            var_r30 += var_r27;
                        }
                        else if (((var_r29 + var_r26) <= 1) && ((var_r29 + var_r26) >= 0)) {
                            var_r29 += var_r26;
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
        if (lbl_1_bss_444 != 0) {
            var_r25 = var_r30 + (var_r29 * 6);
        }
        else {
            var_r25 = var_r30 + (var_r29 * 4);
        }
        if (arg1->unk_5C != var_r25) {
            HuAudFXPlay(0);
            var_r19 = arg1->unk_5C;
            arg1->unk_5C = var_r25;
            if (lbl_1_bss_444 != 0) {
                for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                    fn_1_1B7D0(1);
                    var_f31 = fn_1_1B64C(lbl_1_data_694[var_r19][0], lbl_1_data_694[var_r25][0], var_r28, 10.0f);
                    var_f30 = fn_1_1B64C(lbl_1_data_694[var_r19][1], lbl_1_data_694[var_r25][1], var_r28, 10.0f);
                    HuSprPosSet(var_r24, arg1->unk_48 + 0x1E, var_f31, var_f30);
                    HuSprPosSet(var_r24, arg1->unk_48 + 0x22, var_f31, var_f30);
                }
                return;
            }
            for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                fn_1_1B7D0(1);
                var_f31 = fn_1_1B64C(*lbl_1_data_5E4[var_r23], *lbl_1_data_5E4[var_r30], var_r28, 10.0f);
                var_f30 = fn_1_1B64C(lbl_1_data_5E4[var_r22 * 4][1], lbl_1_data_5E4[var_r29 * 4][1], var_r28, 10.0f);
                HuSprPosSet(var_r24, arg1->unk_48 + 0x1E, var_f31, var_f30);
                HuSprPosSet(var_r24, arg1->unk_48 + 0x22, var_f31, var_f30);
            }
        }
    }
}

void fn_1_18610(MpexDllUnkStruct4 *arg0)
{
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r30 = lbl_1_bss_63C[1];
    do {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if ((var_r29 != arg0->unk_48) && (lbl_1_bss_45C[var_r29].unk_08 == 1) && (arg0->unk_5C == lbl_1_bss_45C[var_r29].unk_5C)) {
                arg0->unk_5C += 1;
                break;
            }
        }
    } while (var_r29 != 4);
    arg0->unk_54 = 0;
    if (lbl_1_bss_444 != 0) {
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
    if (lbl_1_bss_444 != 0) {
        HuSprPosSet(var_r30, arg0->unk_48 + 0x26, *lbl_1_data_694[arg0->unk_5C], lbl_1_data_694[arg0->unk_5C][1]);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x2A, *lbl_1_data_694[arg0->unk_5C], lbl_1_data_694[arg0->unk_5C][1]);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x2E, *lbl_1_data_694[arg0->unk_5C], lbl_1_data_694[arg0->unk_5C][1] + 0x23);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x32, *lbl_1_data_694[arg0->unk_5C], lbl_1_data_694[arg0->unk_5C][1] + 0x23);
    }
    else {
        HuSprPosSet(var_r30, arg0->unk_48 + 0x26, *lbl_1_data_5E4[arg0->unk_5C % 4], lbl_1_data_5E4[(arg0->unk_5C / 4) * 4][1]);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x2A, *lbl_1_data_5E4[arg0->unk_5C % 4], lbl_1_data_5E4[(arg0->unk_5C / 4) * 4][1]);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x2E, *lbl_1_data_5E4[arg0->unk_5C % 4], lbl_1_data_5E4[(arg0->unk_5C / 4) * 4][1] + 0x23);
        HuSprPosSet(var_r30, arg0->unk_48 + 0x32, *lbl_1_data_5E4[arg0->unk_5C % 4], lbl_1_data_5E4[(arg0->unk_5C / 4) * 4][1] + 0x23);
    }
    arg0->unk_10 = 0;
    HuSprAttrReset(var_r30, arg0->unk_48 + 0x26, 4);
    HuSprAttrReset(var_r30, arg0->unk_48 + 0x2A, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x2E, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x32, 4);
}

void fn_1_18D30(struct MpexDllUnkStruct4 *arg0)
{
    s32 var_r30;

    var_r30 = lbl_1_bss_63C[1];
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x26, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x2A, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x2E, 4);
    HuSprAttrSet(var_r30, arg0->unk_48 + 0x32, 4);
}

void fn_1_18DCC(omObjData *arg0, MpexDllUnkStruct4 *arg1)
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
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;

    var_r27 = lbl_1_bss_63C[1];
    var_r26 = 0;
    var_r25 = 0;
    sp8 = arg1->unk_54;
    lbl_1_bss_5DC.unk_30 = 0;
    if (lbl_1_bss_444 != 0) {
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
        if (HuPadBtnDown[lbl_1_bss_45C->unk_58] & PAD_BUTTON_A) {
            arg1->unk_08 = 1;
            HuSprBankSet(var_r27, arg1->unk_48 + 0x26, 1);
            HuSprBankSet(var_r27, arg1->unk_48 + 0x2A, 1);
            if (lbl_1_bss_444 != 0) {
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
                fn_1_1CABC(var_r21);
            }
            else {
                HuSprBankSet(var_r27, arg1->unk_5C + 2, 1);
                fn_1_1CABC(arg1->unk_5C);
            }
            arg1->unk_54 = 0;
            HuSprBankSet(var_r27, arg1->unk_48 + 0x2E, arg1->unk_54);
            if (lbl_1_bss_444 != 0) {
                HuSprPosSet(var_r27, arg1->unk_48 + 0x2E, lbl_1_data_694[arg1->unk_5C][0], lbl_1_data_694[arg1->unk_5C][1] + 0x23);
            }
            else {
                HuSprPosSet(var_r27, arg1->unk_48 + 0x2E, lbl_1_data_5E4[arg1->unk_5C % 4][0], lbl_1_data_5E4[(arg1->unk_5C / 4) * 4][1] + 0x23);
            }
            HuSprAttrReset(var_r27, arg1->unk_48 + 0x2E, 4);
        }
        else if (lbl_1_bss_444 != 0) {
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
            if (HuPadStkY[0] <= -5) {
                var_r29++;
                var_r25 = 1;
                if (var_r29 > 2) {
                    var_r29 = 2;
                }
            }
            else if (HuPadStkY[0] >= 5) {
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
            if (HuPadStkY[0] <= -5) {
                var_r29++;
                var_r25 = 1;
                if (var_r29 > 1) {
                    var_r29 = 1;
                }
            }
            else if (HuPadStkY[0] >= 5) {
                var_r29--;
                var_r25 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
    }
    else if (HuPadBtnDown[lbl_1_bss_45C->unk_58] & PAD_BUTTON_B) {
        arg1->unk_08 = arg1->unk_10 = 0;
        if (lbl_1_bss_444 != 0) {
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
    if (lbl_1_bss_444 != 0) {
        var_r24 = var_r30 + (var_r29 * 6);
    }
    else {
        var_r24 = var_r30 + (var_r29 * 4);
    }
    if (arg1->unk_5C != var_r24) {
        if (lbl_1_bss_444 != 0) {
            while (TRUE) {
                fn_1_1B7D0(1);
                var_r24 = var_r30 + (var_r29 * 6);
                for (var_r28 = 0; var_r28 < 4; var_r28++) {
                    if (((var_r28 != arg1->unk_48) && (lbl_1_bss_45C[var_r28].unk_08 == 1) && (var_r24 == lbl_1_bss_45C[var_r28].unk_5C))
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
                    if ((var_r28 != arg1->unk_48) && (lbl_1_bss_45C[var_r28].unk_08 == 1) && (var_r24 == lbl_1_bss_45C[var_r28].unk_5C)) {
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
        if (lbl_1_bss_444 != 0) {
            var_r24 = var_r30 + (var_r29 * 6);
        }
        else {
            var_r24 = var_r30 + (var_r29 * 4);
        }
        if (arg1->unk_5C != var_r24) {
            var_r19 = arg1->unk_5C;
            arg1->unk_5C = var_r24;
            HuAudFXPlay(0);
            if (lbl_1_bss_444 != 0) {
                for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                    fn_1_1B7D0(1);
                    var_f31 = fn_1_1B64C(lbl_1_data_694[var_r19][0], lbl_1_data_694[var_r24][0], var_r28, 10.0f);
                    var_f30 = fn_1_1B64C(lbl_1_data_694[var_r19][1], lbl_1_data_694[var_r24][1], var_r28, 10.0f);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x26, var_f31, var_f30);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x2A, var_f31, var_f30);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x2E, var_f31, 35.0f + var_f30);
                }
            }
            else {
                for (var_r28 = 0; var_r28 <= 0xA; var_r28++) {
                    fn_1_1B7D0(1);
                    var_f31 = fn_1_1B64C(lbl_1_data_5E4[var_r23][0], lbl_1_data_5E4[var_r30][0], var_r28, 10.0f);
                    var_f30 = fn_1_1B64C(lbl_1_data_5E4[var_r22 * 4][1], lbl_1_data_5E4[var_r29 * 4][1], var_r28, 10.0f);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x26, var_f31, var_f30);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x2A, var_f31, var_f30);
                    HuSprPosSet(var_r27, arg1->unk_48 + 0x2E, var_f31, 35.0f + var_f30);
                }
            }
        }
    }
    lbl_1_bss_5DC.unk_30 = 0;
}

s32 fn_1_19A98(MpexDllUnkStruct4 *arg0)
{
    float var_f31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r28 = 0;
    var_r29 = lbl_1_bss_63C[1];
    while (TRUE) {
        fn_1_1B7D0(1);
        var_r28 = 0;
        var_r26 = arg0->unk_54;
        if (HuPadStkX[lbl_1_bss_45C->unk_58] < 5) {
            if ((HuPadBtn[lbl_1_bss_45C->unk_58] & PAD_BUTTON_RIGHT) == 0) {
                // TODO remove gotos
                goto block_2;
            }
        }
        if (GWGameStat.veryHardUnlock == 1) {
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
            goto block_1;
        block_2:
            if (HuPadStkX[lbl_1_bss_45C->unk_58] <= -5 || HuPadBtn[lbl_1_bss_45C->unk_58] & PAD_BUTTON_LEFT) {
                if (GWGameStat.veryHardUnlock == 1) {
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
        }
    block_1:
        if (arg0->unk_54 != var_r26) {
            HuAudFXPlay(0);
            for (var_r30 = 0; var_r30 <= 5; var_r30++) {
                fn_1_1B7D0(1);
                if (lbl_1_bss_444 != 0) {
                    var_f31 = fn_1_1B64C(lbl_1_data_694[arg0->unk_5C][0], lbl_1_data_694[arg0->unk_5C][0] + (var_r28 * 0xA), var_r30, 5.0f);
                    HuSprPosSet(var_r29, arg0->unk_48 + 0x2E, var_f31, lbl_1_data_694[arg0->unk_5C][1] + 0x23);
                }
                else {
                    var_f31 = fn_1_1B64C(lbl_1_data_5E4[arg0->unk_5C % 4][0], lbl_1_data_5E4[arg0->unk_5C % 4][0] + (var_r28 * 0xA), var_r30, 5.0f);
                    HuSprPosSet(var_r29, arg0->unk_48 + 0x2E, var_f31, lbl_1_data_5E4[(arg0->unk_5C / 4) * 4][1] + 0x23);
                }
            }
            HuSprBankSet(var_r29, arg0->unk_48 + 0x2E, arg0->unk_54);
            for (var_r30 = 0; var_r30 <= 5; var_r30++) {
                fn_1_1B7D0(1);
                if (lbl_1_bss_444 != 0) {
                    var_f31 = fn_1_1B64C(lbl_1_data_694[arg0->unk_5C][0] + (var_r28 * 0xA), lbl_1_data_694[arg0->unk_5C][0], var_r30, 5.0f);
                    HuSprPosSet(var_r29, arg0->unk_48 + 0x2E, var_f31, lbl_1_data_694[arg0->unk_5C][1] + 0x23);
                }
                else {
                    var_f31 = fn_1_1B64C(lbl_1_data_5E4[arg0->unk_5C % 4][0] + (var_r28 * 0xA), lbl_1_data_5E4[arg0->unk_5C % 4][0], var_r30, 5.0f);
                    HuSprPosSet(var_r29, arg0->unk_48 + 0x2E, var_f31, lbl_1_data_5E4[(arg0->unk_5C / 4) * 4][1] + 0x23);
                }
            }
        }
    }
    if (var_r27 == 1) {
        if (lbl_1_bss_444 != 0) {
            HuSprPosSet(var_r29, arg0->unk_48 + 0x32, lbl_1_data_694[arg0->unk_5C][0], lbl_1_data_694[arg0->unk_5C][1] + 0x23);
        }
        else {
            HuSprPosSet(var_r29, arg0->unk_48 + 0x32, lbl_1_data_5E4[arg0->unk_5C % 4][0], lbl_1_data_5E4[(arg0->unk_5C / 4) * 4][1] + 0x23);
        }
        HuSprBankSet(var_r29, arg0->unk_48 + 0x32, arg0->unk_54);
        HuSprAttrReset(var_r29, arg0->unk_48 + 0x32, 4);
        HuSprAttrSet(var_r29, arg0->unk_48 + 0x2E, 4);
    }
    return var_r27;
}

void fn_1_1A3BC(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    AnimData *var_r28;
    AnimData *var_r27;

    var_r29 = HuSprGrpCreate(0x1B);
    lbl_1_bss_63C[2] = var_r29;
    var_r30 = HuSprCreate(HuSprAnimReadFile(0x640067), 0x64, 0);
    HuSprGrpMemberSet(var_r29, 0, var_r30);
    var_r30 = HuSprCreate(HuSprAnimReadFile(0x640069), 0x64, 0);
    HuSprGrpMemberSet(var_r29, 2, var_r30);
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        var_r30 = HuSprCreate(HuSprAnimReadFile(var_r31 + 0x64006B), 0x5A, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 4, var_r30);
    }
    var_r28 = HuSprAnimReadFile(0x640079);
    var_r27 = HuSprAnimReadFile(0x64007A);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = HuSprCreate(var_r28, 0x50, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x12, var_r30);
        var_r30 = HuSprCreate(var_r27, 0x50, 0);
        HuSprGrpMemberSet(var_r29, var_r31 + 0x16, var_r30);
    }
    var_r30 = HuSprCreate(HuSprAnimReadFile(0x64007B), 0x46, 0);
    HuSprGrpMemberSet(var_r29, 0x1A, var_r30);
    fn_1_1A5A4(0);
    fn_1_1AEFC(0);
}

void fn_1_1A5A4(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;

    var_r30 = lbl_1_bss_63C[2];
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
                HuSprPosSet(var_r30, var_r28 + 4, lbl_1_data_724[var_r31][0], lbl_1_data_724[var_r31][1]);
                if (GWPlayerCfg[var_r31].iscom != 0) {
                    HuSprAttrReset(var_r30, var_r31 + 0x16, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x16, var_r25);
                    HuSprPosSet(var_r30, var_r31 + 0x16, lbl_1_data_724[var_r31][0], lbl_1_data_724[var_r31][1] + 0x14);
                }
                else {
                    HuSprAttrReset(var_r30, var_r31 + 0x12, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x12, var_r31);
                    HuSprPosSet(var_r30, var_r31 + 0x12, lbl_1_data_724[var_r31][0], lbl_1_data_724[var_r31][1] + 0x14);
                }
            }
            break;
        case 1:
            HuSprAttrReset(var_r30, 0, 4);
            var_r27 = GWPlayerCfg->character;
            var_r24 = GWPlayerCfg->diff;
            HuSprAttrReset(var_r30, var_r27 + 4, 4);
            HuSprPosSet(var_r30, var_r27 + 4, 0.0f, lbl_1_data_744[1]);
            if (GWPlayerCfg->iscom != 0) {
                HuSprAttrReset(var_r30, 0x16, 4);
                HuSprBankSet(var_r30, 0x16, var_r24);
                HuSprPosSet(var_r30, var_r31 + 0x16, 0.0f, lbl_1_data_744[1] + 0x14);
            }
            else {
                HuSprAttrReset(var_r30, 0x12, 4);
                HuSprBankSet(var_r30, 0x12, 0);
                HuSprPosSet(var_r30, 0x12, 0.0f, lbl_1_data_744[1] + 0x14);
            }
            break;
        case 2:
            HuSprAttrReset(var_r30, 1, 4);
            for (var_r31 = 0; var_r31 < 2; var_r31++) {
                var_r26 = GWPlayerCfg[var_r31].character;
                var_r23 = GWPlayerCfg[var_r31].diff;
                HuSprAttrReset(var_r30, var_r26 + 4, 4);
                HuSprPosSet(var_r30, var_r26 + 4, lbl_1_data_74C[var_r31][0], lbl_1_data_74C[var_r31][1]);
                if (GWPlayerCfg[var_r31].iscom != 0) {
                    HuSprAttrReset(var_r30, var_r31 + 0x16, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x16, var_r23);
                    HuSprPosSet(var_r30, var_r31 + 0x16, lbl_1_data_74C[var_r31][0], lbl_1_data_74C[var_r31][1] + 0x19);
                }
                else {
                    HuSprAttrReset(var_r30, var_r31 + 0x12, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x12, var_r31);
                    HuSprPosSet(var_r30, var_r31 + 0x12, lbl_1_data_74C[var_r31][0], lbl_1_data_74C[var_r31][1] + 0x19);
                }
            }
            break;
        case 3:
            HuSprAttrReset(var_r30, 1, 4);
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                var_r29 = GWPlayerCfg[var_r31].character;
                var_r22 = GWPlayerCfg[var_r31].diff;
                var_r29 = fn_1_1B42C(var_r29);
                HuSprAttrReset(var_r30, var_r29 + 4, 4);
                HuSprPosSet(var_r30, var_r29 + 4, lbl_1_data_75C[var_r31][0], lbl_1_data_75C[var_r31][1]);
                if (GWPlayerCfg[var_r31].iscom != 0) {
                    HuSprAttrReset(var_r30, var_r31 + 0x16, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x16, var_r22);
                    HuSprPosSet(var_r30, var_r31 + 0x16, lbl_1_data_75C[var_r31][0], lbl_1_data_75C[var_r31][1] + 0x19);
                }
                else {
                    HuSprAttrReset(var_r30, var_r31 + 0x12, 4);
                    HuSprBankSet(var_r30, var_r31 + 0x12, var_r31);
                    HuSprPosSet(var_r30, var_r31 + 0x12, lbl_1_data_75C[var_r31][0], lbl_1_data_75C[var_r31][1] + 0x19);
                }
            }
            HuSprAttrReset(var_r30, 0x1A, 4);
            break;
    }
    HuSprGrpPosSet(var_r30, 112.0f, -428.0f);
}

void fn_1_1AEFC(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_63C[2];
    for (var_r31 = 0; var_r31 < 0x1B; var_r31++) {
        HuSprAttrSet(var_r30, var_r31, 4);
    }
    HuSprGrpPosSet(var_r30, 112.0f, -428.0f);
}

void fn_1_1AF78(s32 arg0)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;

    var_r30 = lbl_1_bss_63C[2];
    fn_1_1A5A4(arg0);
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_1B7D0(1);
        if (var_r31 <= 0x32) {
            var_f31 = fn_1_1B64C(-500.0f, 10.0f, var_r31, 50.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, 0.0f, var_r31 - 0x32, 10.0f);
        }
        HuSprGrpPosSet(var_r30, 112.0f, 72.0f + var_f31);
    }
    HuSprGrpPosSet(var_r30, 112.0f, 72.0f);
}

void fn_1_1B0DC(s32 arg0)
{
    float var_f31;
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r29 = lbl_1_bss_63C[2];
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        fn_1_1B7D0(1);
        if (var_r31 <= 0xA) {
            var_f31 = fn_1_1B64C(0.0f, 10.0f, var_r31, 10.0f);
        }
        else {
            var_f31 = fn_1_1B574(10.0f, -500.0f, var_r31 - 0xA, 50.0f);
        }
        HuSprGrpPosSet(var_r29, 112.0f, 72.0f + var_f31);
    }
    HuSprGrpPosSet(var_r29, 112.0f, -428.0f);
    var_r28 = lbl_1_bss_63C[2];
    for (var_r30 = 0; var_r30 < 0x1B; var_r30++) {
        HuSprAttrSet(var_r28, var_r30, 4);
    }
    HuSprGrpPosSet(var_r28, 112.0f, -428.0f);
}

void fn_1_1B294(void)
{
    omObjData *var_r31;

    var_r31 = NULL;
    var_r31 = omAddObjEx(lbl_1_bss_440, 0x1000, 8, 8, -1, NULL);
    lbl_1_bss_5DC.unk_00 = var_r31;
    lbl_1_bss_5DC.unk_04 = NULL;
    while (TRUE) {
        HuPrcVSleep();
        if (lbl_1_bss_5DC.unk_04 == NULL) {
            continue;
        }
        lbl_1_bss_5DC.unk_04(lbl_1_bss_5DC.unk_00, &lbl_1_bss_5DC);
    }
}

void fn_1_1B338(void)
{
    s32 var_r31;
    omObjData *var_r30;

    var_r31 = lbl_1_bss_448[0];
    lbl_1_bss_448[0] = var_r31 + 1;
    var_r30 = NULL;
    var_r30 = omAddObjEx(lbl_1_bss_440, 0x1000, 8, 8, -1, NULL);
    lbl_1_bss_45C[var_r31].unk_00 = var_r30;
    lbl_1_bss_45C[var_r31].unk_04 = NULL;

    while (TRUE) {
        HuPrcVSleep();
        if (lbl_1_bss_45C[var_r31].unk_04 == NULL) {
            continue;
        }
        lbl_1_bss_45C[var_r31].unk_04(lbl_1_bss_45C[var_r31].unk_00, &lbl_1_bss_45C[var_r31]);
    }
}

s32 fn_1_1B42C(s32 arg0)
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

s32 fn_1_1B4AC(s32 arg0)
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

float fn_1_1B52C(float arg8, float arg9, float argA, float argB)
{
    if (argB <= argA) {
        return arg9;
    }
    return arg8 + ((argA / argB) * (arg9 - arg8));
}

float fn_1_1B554(float arg0, float arg1, float arg2)
{
    return (arg1 + (arg0 * (arg2 - 1.0f))) / arg2;
}

float fn_1_1B574(float arg0, float arg1, float arg2, float arg3)
{
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + ((arg1 - arg0) * (1.0 - cosd(((90.0f / arg3) * arg2))));
}

float fn_1_1B64C(float arg0, float arg1, float arg2, float arg3)
{
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + ((arg1 - arg0) * sind(((90.0f / arg3) * arg2)));
}

float fn_1_1B714(float arg8, float arg9, float argA, float argB)
{
    if (argA >= argB) {
        return arg8;
    }
    return arg8 + ((arg9 - arg8) * sind(((360.0f / argB) * argA)));
}

void fn_1_1B7D0(s32 arg0)
{
    if (arg0 <= 1) {
        HuPrcVSleep();
        return;
    }
    HuPrcSleep(arg0);
}

void fn_1_1B810(void)
{
    HuWinInit(1);
}

void fn_1_1B834(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    if (lbl_1_data_77C == -1) {
        var_r31 = 0x1C9;
        var_r30 = 0x44;
        var_r29 = 1.0f + ((576.0f - var_r31) / 2);
        var_r28 = 445.0f - var_r30;
        lbl_1_data_77C = HuWinExCreateStyled(var_r29, var_r28, var_r31, var_r30, -1, 1);
        winData[lbl_1_data_77C].active_pad = 1;
        HuWinMesPalSet(lbl_1_data_77C, 7, 0, 0, 0);
        HuWinExAnimIn(lbl_1_data_77C);
    }
}

void fn_1_1B9F4(void)
{
    if (lbl_1_data_77C != -1) {
        HuWinMesSet(lbl_1_data_77C, 0x250004);
        HuWinExAnimOut(lbl_1_data_77C);
        HuWinExCleanup(lbl_1_data_77C);
        lbl_1_data_77C = -1;
    }
}

void fn_1_1BA78(u32 arg0, s32 arg1, s32 arg2)
{
    if (lbl_1_data_77C != -1) {
        if (arg2 == 1) {
            HuWinMesSpeedSet(lbl_1_data_77C, 0);
        }
        else {
            HuWinMesSpeedSet(lbl_1_data_77C, 1);
        }
        HuWinMesSet(lbl_1_data_77C, arg0);
        if (arg1 <= 0) {
            HuWinMesWait(lbl_1_data_77C);
            return;
        }
        if (arg1 <= 1) {
            HuPrcVSleep();
            return;
        }
        HuPrcSleep(arg1);
    }
}

void fn_1_1BB4C(u32 arg0, s32 arg1)
{
    if (lbl_1_data_77C != -1) {
        HuWinInsertMesSet(lbl_1_data_77C, arg0, arg1);
    }
}

s32 fn_1_1BBA4(s32 arg0)
{
    float spC[2];
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    HuWinMesMaxSizeGet(1, spC, 0x1E0035);
    var_r30 = spC[0];
    var_r29 = spC[1];
    var_r27 = 0x22C - var_r30;
    var_r26 = 0x1BD - var_r29;
    var_r31 = HuWinExCreateStyled(var_r27, var_r26, var_r30, var_r29, -1, 1);
    winData[var_r31].active_pad = 1;
    HuWinMesPalSet(var_r31, 7, 0, 0, 0);
    HuWinExAnimIn(var_r31);
    HuWinMesSpeedSet(var_r31, 0);
    HuWinMesSet(var_r31, 0x1E0035);
    var_r28 = HuWinChoiceGet(var_r31, arg0);
    HuWinMesSet(var_r31, 0x250004);
    HuWinExAnimOut(var_r31);
    HuWinExCleanup(var_r31);
    return var_r28;
}

void fn_1_1BD00(u32 arg0, s32 arg1)
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
    if (lbl_1_data_780[0] != -1) {
        fn_1_1C120();
        lbl_1_data_780[0] = HuWinExCreateStyled(var_r28, var_r30, var_r29, var_r31, -1, 1);
    }
    else {
        lbl_1_data_780[0] = HuWinExCreateStyled(var_r28, var_r30, var_r29, var_r31, -1, 1);
    }
    HuWinBGTPLvlSet(lbl_1_data_780[0], 0.0f);
    HuWinDispOn(lbl_1_data_780[0]);
    HuWinMesSet(lbl_1_data_780[0], arg0);
    HuWinMesSpeedSet(lbl_1_data_780[0], 0);
}

void fn_1_1BF1C(u32 arg0)
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
    if (lbl_1_data_780[0] != -1) {
        fn_1_1C120();
        lbl_1_data_780[0] = HuWinExCreateStyled(var_r28, var_r29, var_r30, var_r31, -1, 1);
    }
    else {
        lbl_1_data_780[0] = HuWinExCreateStyled(var_r28, var_r29, var_r30, var_r31, -1, 1);
    }
    HuWinBGTPLvlSet(lbl_1_data_780[0], 0.0f);
    HuWinDispOn(lbl_1_data_780[0]);
    HuWinMesSet(lbl_1_data_780[0], arg0);
    HuWinMesSpeedSet(lbl_1_data_780[0], 0);
}

void fn_1_1C120(void)
{
    if (lbl_1_data_780[0] != -1) {
        HuWinExCleanup(lbl_1_data_780[0]);
        lbl_1_data_780[0] = -1;
    }
}

void fn_1_1C174(void)
{
    s32 var_r30;
    s32 var_r31;

    var_r30 = lbl_1_bss_63C[1];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_45C[var_r31].unk_08 == 1) {
            HuSprBankSet(var_r30, lbl_1_bss_45C[var_r31].unk_5C + 2, 1);
            HuSprBankSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x1E, 1);
            HuSprBankSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x22, 1);
            HuSprAttrReset(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x1E, 4);
            HuSprAttrReset(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x22, 4);
            HuSprPosSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x1E, lbl_1_data_5E4[lbl_1_bss_45C[var_r31].unk_5C % 4][0],
                lbl_1_data_5E4[(lbl_1_bss_45C[var_r31].unk_5C / 4) * 4][1]);
            HuSprPosSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x22, lbl_1_data_5E4[lbl_1_bss_45C[var_r31].unk_5C % 4][0],
                lbl_1_data_5E4[(lbl_1_bss_45C[var_r31].unk_5C / 4) * 4][1]);
        }
        else {
            lbl_1_bss_45C[var_r31].unk_5C = 0;
        }
    }
}

void fn_1_1C478(void)
{
    s32 var_r30;
    s32 var_r31;

    var_r30 = lbl_1_bss_63C[1];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_45C[var_r31].unk_08 == 1) {
            HuSprBankSet(var_r30, lbl_1_bss_45C[var_r31].unk_5C + 2, 1);
            HuSprBankSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x1E, 1);
            HuSprBankSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x22, 1);
            HuSprAttrReset(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x1E, 4);
            HuSprAttrReset(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x22, 4);
            HuSprPosSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x1E, lbl_1_data_5E4[lbl_1_bss_45C[var_r31].unk_5C % 4][0],
                lbl_1_data_5E4[(lbl_1_bss_45C[var_r31].unk_5C / 4) * 4][1]);
            HuSprPosSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x22, lbl_1_data_5E4[lbl_1_bss_45C[var_r31].unk_5C % 4][0],
                lbl_1_data_5E4[(lbl_1_bss_45C[var_r31].unk_5C / 4) * 4][1]);
        }
        else {
            lbl_1_bss_45C[var_r31].unk_5C = 0;
        }
    }
}

void fn_1_1C77C(void)
{
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;

    var_r30 = lbl_1_bss_63C[1];
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_45C[var_r31].unk_08 == 1) {
            if (lbl_1_bss_45C[var_r31].unk_5C <= 5) {
                var_r29 = lbl_1_bss_45C[var_r31].unk_5C - 1;
            }
            else if (lbl_1_bss_45C[var_r31].unk_5C <= 0xB) {
                var_r29 = lbl_1_bss_45C[var_r31].unk_5C - 3;
            }
            else {
                var_r29 = lbl_1_bss_45C[var_r31].unk_5C - 4;
            }
            HuSprBankSet(var_r30, var_r29 + 2, 1);
            HuSprBankSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x1E, 1);
            HuSprBankSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x22, 1);
            HuSprAttrReset(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x1E, 4);
            HuSprAttrReset(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x22, 4);
            HuSprPosSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x1E, lbl_1_data_694[lbl_1_bss_45C[var_r31].unk_5C][0],
                lbl_1_data_694[lbl_1_bss_45C[var_r31].unk_5C][1]);
            HuSprPosSet(var_r30, lbl_1_bss_45C[var_r31].unk_48 + 0x22, lbl_1_data_694[lbl_1_bss_45C[var_r31].unk_5C][0],
                lbl_1_data_694[lbl_1_bss_45C[var_r31].unk_5C][1]);
        }
        else {
            lbl_1_bss_45C[var_r31].unk_5C = 1;
        }
    }
}

void fn_1_1CABC(s32 arg0)
{
    s32 sp8[] = { 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x39, 0x40, 0x4B, 0x46, 0x3E, 0x3A };

    if ((arg0 < 0) || (arg0 > 0xD)) {
        return;
    }
    HuAudFXPlay(sp8[arg0]);
}
