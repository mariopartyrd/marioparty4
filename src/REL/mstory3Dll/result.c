#include "REL/mstory3Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ char unk1C[0x18];
    /* 0x34 */ s32 unk34[4][2];
    /* 0x54 */ s32 unk54;
    /* 0x58 */ char unk58[4];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ char unk60[4];
    /* 0x64 */ s32 unk64;
    /* 0x68 */ char unk68[4];
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ char unk70[4];
    /* 0x74 */ s32 unk74;
    /* 0x78 */ char unk78[4];
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ char unk80[4];
    /* 0x84 */ s32 unk84;
    /* 0x88 */ char unk88[4];
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ char unk90[4];
} StructUnk38Bss1A0C; // Size 0x94

typedef struct {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ s32 unk18;
    /* 0x01C */ char unk1C[8];
    /* 0x024 */ s32 unk24;
    /* 0x028 */ char unk28[0x10];
    /* 0x038 */ StructUnk38Bss1A0C unk38[4];
    /* 0x288 */ Vec unk288[5];
    /* 0x2C4 */ s32 unk2C4;
    /* 0x2C8 */ s32 unk2C8;
    /* 0x2CC */ s32 unk2CC;
    /* 0x2D0 */ s32 unk2D0;
    /* 0x2D4 */ s32 unk2D4;
} StructBss1A0C; // Size 0x2D8

void fn_1_15C0C(void);
void fn_1_16ED4(void);
void fn_1_18080(void);
void fn_1_184E8(void);
void fn_1_18558(void);
void fn_1_18F98(void);
void fn_1_19144(void);
void fn_1_19214(void);
void fn_1_194A0(void);
void fn_1_197B4(s32 arg0);
void fn_1_1C2F4(void);
void fn_1_1C460(void);
void fn_1_1CA98(void);
void fn_1_1CB7C(void);
void fn_1_1CC5C(void);
void fn_1_1CD60(void);
void fn_1_1D63C(void);
void fn_1_1D77C(void);
void fn_1_1D964(void);
void fn_1_1DA64(void);
void fn_1_1DAAC(void);
void fn_1_1DE4C(void);

StructBss1A0C lbl_1_bss_1A0C;
StructBss1530 lbl_1_bss_19E4;
StructBss1530 lbl_1_bss_19BC;
StructBss1530 lbl_1_bss_1994;
StructBss1530 lbl_1_bss_18F4[4];
AnimData* lbl_1_bss_18EC[2];
AnimData* lbl_1_bss_18E4[2];
AnimData* lbl_1_bss_18D8[3];
s32 lbl_1_bss_18D4;
Process* lbl_1_bss_18D0;

void fn_1_157F0(Process* arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r31;

    lbl_1_bss_18D0 = arg0;
    lbl_1_bss_1A0C.unk00 = arg1;
    lbl_1_bss_1A0C.unk08 = GWSystem.max_turn;
    arg3 = lbl_1_bss_1A0C.unk14 = fn_1_373C();
    lbl_1_bss_1A0C.unk2D4 = arg2;
    lbl_1_bss_1A0C.unk2CC = GWSystem.team;
    if (_CheckFlag(FLAG_ID_MAKE(1, 29))) {
        lbl_1_bss_1A0C.unk2D0 = 0;
    } else {
        lbl_1_bss_1A0C.unk2D0 = 1;
    }
    fn_1_9A0();
    fn_1_37C8(0xFF);
    fn_1_290C(lbl_1_bss_18D0, fn_1_1DE4C);
    fn_1_15C0C();
    fn_1_197B4(arg3);
    fn_1_194A0();
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuPrcChildCreate(fn_1_1CC5C, 100, 0x2000, 0, HuPrcCurrentGet());
    }
    HuPrcChildCreate(fn_1_19214, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_1DAAC, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_18080, 90, 0x2000, 0, HuPrcCurrentGet());
}

void fn_1_159A4(void) {
    s32 var_r29;
    s32 var_r30;
    s32 i;

    for (i = 0; i < 4; i++) {
        var_r29 = GWPlayer[i].stars - GWPlayerHandicapGet(i);
        if (var_r29 <= 0) {
            var_r29 = 0;
        }
        GWTotalStarsAdd(var_r29);
    }
    GWBoardPlayCountAdd(lbl_1_bss_1A0C.unk00, 1);
    if (lbl_1_bss_1A0C.unk2CC == 1) {
        if (lbl_1_bss_1A0C.unk38[0].unk08 == 0) {
            GWBoardWinCountInc(lbl_1_bss_1A0C.unk38[0].unk10, lbl_1_bss_1A0C.unk00);
        }
        if (lbl_1_bss_1A0C.unk38[1].unk08 == 0) {
            GWBoardWinCountInc(lbl_1_bss_1A0C.unk38[1].unk10, lbl_1_bss_1A0C.unk00);
        }
    } else if (lbl_1_bss_1A0C.unk38[0].unk08 == 0) {
        GWBoardWinCountInc(lbl_1_bss_1A0C.unk38[0].unk10, lbl_1_bss_1A0C.unk00);
    }
    for (i = 0; i < 4; i++) {
        var_r30 = GWPlayer[i].stars_max - GWPlayerHandicapGet(i);
        if (var_r30 <= 0) {
            var_r30 = 0;
        }
        if (GWBoardMaxStarsGet(lbl_1_bss_1A0C.unk00) <= var_r30 && !GWPlayer[i].com) {
            GWBoardMaxStarsSet(lbl_1_bss_1A0C.unk00, var_r30);
        }
    }
    for (i = 0; i < 4; i++) {
        if (GWBoardMaxCoinsGet(lbl_1_bss_1A0C.unk00) <= GWPlayer[i].coins_max && !GWPlayer[i].com) {
            GWBoardMaxCoinsSet(lbl_1_bss_1A0C.unk00, GWPlayer[i].coins_max);
        }
    }
}

void fn_1_15C0C(void) {
    lbl_1_bss_18EC[0] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 95), MEMORY_DEFAULT_NUM));
    lbl_1_bss_18EC[1] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 96), MEMORY_DEFAULT_NUM));
    lbl_1_bss_18D8[0] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 93), MEMORY_DEFAULT_NUM));
    lbl_1_bss_18D8[1] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 94), MEMORY_DEFAULT_NUM));
    lbl_1_bss_18D8[2] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 97), MEMORY_DEFAULT_NUM));
    lbl_1_bss_18E4[0] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 136), MEMORY_DEFAULT_NUM));
    lbl_1_bss_18E4[1] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 137), MEMORY_DEFAULT_NUM));
}

void fn_1_15D08(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    HuSprPosSet(arg0, arg1, arg2 + arg4 / 2, arg3 + arg5 / 2);
}

void fn_1_15DC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 var_r31;
    s32 temp_r28;

    var_r31 = 0;
    if (arg7 < 2) {
        if ((temp_r28 = arg2 / 100) == 0) {
            if (arg7 != 0) {
                var_r31++;
            }
            HuSprBankSet(arg0, arg1, temp_r28);
            fn_1_15D08(arg0, arg1, -1000, -1000, arg5, arg6);
        } else {
            HuSprBankSet(arg0, arg1, temp_r28);
            fn_1_15D08(arg0, arg1, arg3 + arg5 * var_r31, arg4, arg5, arg6);
            var_r31++;
        }
    } else {
        arg1--;
    }
    if ((temp_r28 = (arg2 % 100) / 10) == 0 && arg2 / 100 == 0) {
        if (arg7 != 0) {
            var_r31++;
        }
        HuSprBankSet(arg0, arg1 + 1, temp_r28);
        fn_1_15D08(arg0, arg1 + 1, -1000, -1000, arg5, arg6);
    } else {
        HuSprBankSet(arg0, arg1 + 1, temp_r28);
        fn_1_15D08(arg0, arg1 + 1, arg3 + arg5 * var_r31, arg4, arg5, arg6);
        var_r31++;
    }
    temp_r28 = arg2 % 10;
    HuSprBankSet(arg0, arg1 + 2, temp_r28);
    fn_1_15D08(arg0, arg1 + 2, arg3 + arg5 * var_r31, arg4, arg5, arg6);
    var_r31++;
}

void fn_1_161B8(void) {
    s32 var_r30 = 16;
    s32 var_r29 = 40;
    s32 var_r28 = 0;
    GXColor sp10 = { 0x00, 0x00, 0x80, 0x80 };
    s32 i;

    while (TRUE) {
        fn_1_938();
        if (HuPadBtnDown[0] & PAD_TRIGGER_R) {
            var_r28++;
            var_r28 %= 2;
        }
        if (var_r28 == 0) {
            continue;
        }
        printWin(var_r30, var_r29, 220, 150, &sp10);
        if (lbl_1_bss_19E4.unk04 == NULL) {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> FALSE");
        } else {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> TRUE");
        }
        if (lbl_1_bss_19BC.unk04 == NULL) {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP     -> FALSE");
        } else {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP     -> TRUE");
        }
        if (lbl_1_bss_1994.unk04 == NULL) {
            print8(var_r30, var_r29 + 20, 1.0f, "PROC_SUB     -> FALSE");
        } else {
            print8(var_r30, var_r29 + 20, 1.0f, "PROC_SUB     -> TRUE");
        }
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_18F4[i].unk04 == NULL) {
                print8(var_r30, var_r29 + 30 + i * 10, 1.0f, "PROC_PLAYER%d -> FALSE", i);
            } else {
                print8(var_r30, var_r29 + 30 + i * 10, 1.0f, "PROC_PLAYER%d -> TRUE", i);
            }
        }
        print8(var_r30, var_r29 + 80, 1.0f, "M:%d P:%d W:%d", lbl_1_bss_1A0C.unk00, lbl_1_bss_1A0C.unk04, lbl_1_bss_1A0C.unk14);
        print8(var_r30, var_r29 + 100, 1.0f, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(var_r30, var_r29 + 110 + i * 10, 1.0f, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i,
                lbl_1_bss_1A0C.unk38[i].unk00, lbl_1_bss_1A0C.unk38[i].unk04, lbl_1_bss_1A0C.unk38[i].unk08,
                lbl_1_bss_1A0C.unk38[i].unk0C, lbl_1_bss_1A0C.unk38[i].unk14, lbl_1_bss_1A0C.unk38[i].unk10);
        }
    }
}

void fn_1_16574(void) {
    fn_1_958(30);
    fn_1_16ED4();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_938();
    } while (WipeStatGet() != 0);
    fn_1_958(60);
}

void fn_1_165C8(void) {
    s32 sp8[5];
    s32 i;

    for (i = 0; i < 5; i++) {
        sp8[i] = 0;
        fn_1_1E28(lbl_1_bss_1994.unk00, i * 3 + 1, i * 3 + 2, 0, 1);
        Hu3DData[lbl_1_bss_1994.unk00->model[i * 3 + 1]].rot.y = -90.0f;
    }
    do {
        fn_1_938();
        for (i = 0; i < 5; i++) {
            if (sp8[i] == 0) {
                lbl_1_bss_1A0C.unk288[i].x -= 5.0f;
                if (i == 0) {
                    if (lbl_1_bss_1A0C.unk288[i].x <= -175.0f) {
                        sp8[i] = 1;
                        lbl_1_bss_1A0C.unk288[i].x = -175.0f;
                        fn_1_1E28(lbl_1_bss_1994.unk00, i * 3 + 1, i * 3 + 1, 15, 1);
                    }
                } else {
                    if (lbl_1_bss_1A0C.unk288[i].x <= -240.0f) {
                        sp8[i] = 1;
                        lbl_1_bss_1A0C.unk288[i].x = -240.0f;
                        fn_1_1E28(lbl_1_bss_1994.unk00, i * 3 + 1, i * 3 + 1, 15, 1);
                    }
                }
            } else if (sp8[i] == 1) {
                Hu3DData[lbl_1_bss_1994.unk00->model[i * 3 + 1]].rot.y = fn_1_5FC(Hu3DData[lbl_1_bss_1994.unk00->model[i * 3 + 1]].rot.y, 17.5f, 10.0f);
                if (Hu3DData[lbl_1_bss_1994.unk00->model[i * 3 + 1]].rot.y >= 14.9f) {
                    sp8[i] = 2;
                }
            }
        }
        for (i = 0; i < 5; i++) {
            if (sp8[i] != 2) {
                break;
            }
        }
    } while (i != 5);
    lbl_1_bss_1A0C.unk0C = fn_1_1834(MAKE_MESSID(38, 12), 0);
}

s32 fn_1_16924(void) {
    s32 var_r31;
    s32 var_r30;

    var_r31 = 0;
    var_r30 = 0;
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_1A0C.unk14 != -1) {
            if (HuPadBtnDown[lbl_1_bss_1A0C.unk38[lbl_1_bss_1A0C.unk04].unk14] & PAD_BUTTON_A) {
                HuAudFXPlay(0x1C);
                break;
            } else if (HuPadBtnDown[lbl_1_bss_1A0C.unk38[lbl_1_bss_1A0C.unk04].unk14] & PAD_BUTTON_MENU) {
                HuAudFXPlay(1);
                var_r31 = 1;
                break;
            }
        } else if (var_r30++ >= 300) {
            var_r31 = 1;
            break;
        }
    }
    if (var_r31 == 0) {
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSS, 1);
        while (TRUE) {
            if (WipeStatGet() == 0) {
                break;
            }
            fn_1_938();
        }
        fn_1_1A24(lbl_1_bss_1A0C.unk0C);
        fn_1_1C460();
        fn_1_1CA98();
        fn_1_18558();
        fn_1_18F98();
        fn_1_1D77C();
        fn_1_1D964();
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSS, -1);
        while (TRUE) {
            if (WipeStatGet() == 0) {
                break;
            }
            fn_1_938();
        }
        lbl_1_bss_1A0C.unk10 = fn_1_1834(-1, 1);
    }
}

void fn_1_16AD4(void) {
    lbl_1_bss_1A0C.unk24 = 1;
    fn_1_1D44(lbl_1_bss_1A0C.unk10, MAKE_MESSID(38, lbl_1_bss_1A0C.unk2C8));
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_1A0C.unk24++ > 5 && (HuPadBtnDown[lbl_1_bss_1A0C.unk38[lbl_1_bss_1A0C.unk04].unk14] & PAD_BUTTON_B)) {
            HuAudFXPlay(3);
            break;
        }
        if (HuPadStkX[lbl_1_bss_1A0C.unk38[lbl_1_bss_1A0C.unk04].unk14] >= 5 || (HuPadBtn[lbl_1_bss_1A0C.unk38[lbl_1_bss_1A0C.unk04].unk14] & PAD_BUTTON_RIGHT)) {
            if (lbl_1_bss_1A0C.unk2C8 != 11) {
                lbl_1_bss_1A0C.unk24 = 0;
            }
            lbl_1_bss_1A0C.unk2C4++;
            if (lbl_1_bss_1A0C.unk2C4 >= 6) {
                lbl_1_bss_1A0C.unk2C4 = 5;
            }
            lbl_1_bss_1A0C.unk2C8++;
            if (lbl_1_bss_1A0C.unk2C8 >= 12) {
                lbl_1_bss_1A0C.unk2C8 = 11;
            } else {
                fn_1_1CD60();
                fn_1_1D44(lbl_1_bss_1A0C.unk10, MAKE_MESSID(38, lbl_1_bss_1A0C.unk2C8));
                HuAudFXPlay(0);
                fn_1_958(10);
            }
        }
        if (HuPadStkX[lbl_1_bss_1A0C.unk38[lbl_1_bss_1A0C.unk04].unk14] <= -5 || (HuPadBtn[lbl_1_bss_1A0C.unk38[lbl_1_bss_1A0C.unk04].unk14] & PAD_BUTTON_LEFT)) {
            if (lbl_1_bss_1A0C.unk2C8 != 0) {
                lbl_1_bss_1A0C.unk24 = 0;
            }
            lbl_1_bss_1A0C.unk2C4--;
            if (lbl_1_bss_1A0C.unk2C4 < 0) {
                lbl_1_bss_1A0C.unk2C4 = 0;
            }
            lbl_1_bss_1A0C.unk2C8--;
            if (lbl_1_bss_1A0C.unk2C8 < 0) {
                lbl_1_bss_1A0C.unk2C8 = 0;
            } else {
                fn_1_1CD60();
                fn_1_1D44(lbl_1_bss_1A0C.unk10, MAKE_MESSID(38, lbl_1_bss_1A0C.unk2C8));
                HuAudFXPlay(0);
                fn_1_958(10);
            }
        }
    }
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSS, 1);
    while (TRUE) {
        if (WipeStatGet() == 0) {
            break;
        }
        fn_1_938();
    }
    fn_1_1A24(lbl_1_bss_1A0C.unk10);
    fn_1_1CB7C();
    fn_1_1C2F4();
    fn_1_19144();
    fn_1_184E8();
    fn_1_1DA64();
    fn_1_1D63C();
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSS, -1);
    while (TRUE) {
        if (WipeStatGet() == 0) {
            break;
        }
        fn_1_938();
    }
    lbl_1_bss_1A0C.unk0C = fn_1_1834(MAKE_MESSID(38, 12), 0);
}

void fn_1_16ED4(void) {
    s32 var_r30;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == 0) {
            lbl_1_bss_1A0C.unk288[i].x = 1800.0f;
            lbl_1_bss_1A0C.unk288[i].y = 157.5f;
        } else if (lbl_1_bss_1A0C.unk2CC == 1) {
            if (i <= 2) {
                var_r30 = 0;
            } else {
                var_r30 = 2;
            }
            lbl_1_bss_1A0C.unk288[i].x = 900.0f - 100.0f * var_r30;
            lbl_1_bss_1A0C.unk288[i].y = 75.0f - 82.5f * (i - 1);
        } else {
            lbl_1_bss_1A0C.unk288[i].x = 900.0f - 100.0f * i;
            lbl_1_bss_1A0C.unk288[i].y = 75.0f - 82.5f * (i - 1);
        }
    }
    lbl_1_bss_1A0C.unk2C4 = 0;
    lbl_1_bss_1A0C.unk2C8 = 0;
    fn_1_1CB7C();
    fn_1_1C2F4();
    fn_1_19144();
    fn_1_184E8();
    fn_1_1DA64();
    fn_1_1D63C();
}

void fn_1_1712C(void) {
    s32 temp_r3;

    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    if (SLSaveFlagGet() == 0) {
        saveExecF = 0;
        lbl_1_bss_18D4 = 1;
        HuPrcEnd();
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    espInit();
    HuPrcVSleep();
    temp_r3 = espEntry(DATA_MAKE_NUM(DATADIR_WIN, 32), 5000, 0);
    espPosSet(temp_r3, 288.0f, 240.0f);
    espAttrReset(temp_r3, 4);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_159A4();
    if (saveExecF == 1) {
        GWGameStat.party_continue = 0;
    }
    SLCommonSet();
    if (SLSaveFlagGet() == 1) {
        SLSave();
    }
    saveExecF = 0;
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_18D4 = 1;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_1728C(void) {
    float sp8[2];
    s32 temp_r30 = 1;
    s32 var_r29;
    s32 var_r31;

    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    if (SLSaveFlagGet() == 0) {
        lbl_1_bss_18D4 = 1;
        HuPrcEnd();
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    espInit();
    HuPrcVSleep();
    espPosSet(var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_WIN, 32), 5000, 0), 288.0f, 240.0f);
    espAttrReset(var_r29, HUSPR_ATTR_DISPOFF);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    if (SLSaveFlagGet() == 1) {
        HuWinInit(1);
        HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(30, 22));
        var_r31 = HuWinExCreateStyled(-10000.0f, 150.0f, sp8[0], sp8[1], -1, 2);
        winData[var_r31].active_pad = 1;
        HuWinAttrSet(var_r31, 0x10);
        HuWinExAnimIn(var_r31);
        HuWinMesSet(var_r31, MAKE_MESSID(30, 22));
        temp_r30 = HuWinChoiceGet(var_r31, 0);
        HuWinExAnimOut(var_r31);
        HuWinExCleanup(var_r31);
        if (SLSaveFlagGet() == 1 && temp_r30 == 0) {
#if VERSION_REV1 || VERSION_REV2
            GWGameStat.story_continue = 1;
#endif
            SLCommonSet();
            SLSaveBoardStory();
            SLSave();
        }
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_18D4 = 1;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 fn_1_17484(s32 arg0) {
    if (arg0 == 0 && _CheckFlag(FLAG_ID_MAKE(0, 2))) {
         return 1;
    }
    if (arg0 == 1 && _CheckFlag(FLAG_ID_MAKE(0, 3))) {
        return 1;
    }
    if (arg0 == 2 && _CheckFlag(FLAG_ID_MAKE(0, 4))) {
        return 1;
    }
    if (arg0 == 3 && _CheckFlag(FLAG_ID_MAKE(0, 5))) {
        return 1;
    }
    if (arg0 == 4 && _CheckFlag(FLAG_ID_MAKE(0, 6))) {
        return 1;
    }
    if (arg0 == 5 && _CheckFlag(FLAG_ID_MAKE(0, 7))) {
        return 1;
    }
    return 0;
}

void fn_1_17570(void) {
    s32 var_r30;
    s32 i;

    var_r30 = 0;
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_938();
    } while (WipeStatGet() != 0);
    CharModelKill(-1);
    HuAudSeqAllFadeOut(1000);
    HuAudSStreamAllFadeOut(1000);
    lbl_1_bss_19E4.unk04 = NULL;
    lbl_1_bss_19BC.unk04 = NULL;
    lbl_1_bss_1994.unk04 = NULL;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_18F4[i].unk04 = NULL;
    }
    if (GWPartyGet() == 1) {
        HuPrcChildCreate(fn_1_1712C, 100, 0x2000, 0, HuPrcCurrentGet());
        do {
            fn_1_938();
        } while (lbl_1_bss_18D4 != 1);
        fn_1_958(30);
        omOvlReturnEx(1, 1);
    } else {
        fn_1_159A4();
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1A0C.unk38[i].unk10 != GWStoryCharGet()) {
                continue;
            }
            _SetFlag(9);
            switch (lbl_1_bss_1A0C.unk00) {
                case 0:
                    if (_CheckFlag(2) == 0) {
                        _SetFlag(2);
                        var_r30 = 1;
                    }
                    break;
                case 1:
                    if (_CheckFlag(3) == 0) {
                        _SetFlag(3);
                        var_r30 = 1;
                    }
                    break;
                case 2:
                    if (_CheckFlag(4) == 0) {
                        _SetFlag(4);
                        var_r30 = 1;
                    }
                    break;
                case 3:
                    if (_CheckFlag(5) == 0) {
                        _SetFlag(5);
                        var_r30 = 1;
                    }
                    break;
                case 4:
                    if (_CheckFlag(6) == 0) {
                        _SetFlag(6);
                        var_r30 = 1;
                    }
                    break;
                case 5:
                    if (_CheckFlag(7) == 0) {
                        _SetFlag(7);
                        var_r30 = 1;
                    }
                    break;
            }
            if (var_r30 == 1) {
                if (lbl_1_bss_1A0C.unk38[i].unk18 == 0) {
                    if (lbl_1_bss_1A0C.unk00 == 5) {
                        GWGameStat.open_w06 = 1;
                    }
                    _ClearFlag(9);
                    OSReport("########## Next to BoardClear Event 10 -> MapNo:%d, MapFlg:%d, MgFlg:%d\n", GWSystem.board, _CheckFlag(2), _CheckFlag(9));
                    fn_1_958(120);
                    HuPrcChildCreate(fn_1_1728C, 100, 0x2000, 0, HuPrcCurrentGet());
                    do {
                        fn_1_938();
                    } while (lbl_1_bss_18D4 != 1);
                    if (lbl_1_bss_1A0C.unk00 != 5) {
                        omOvlGotoEx(OVL_MSTORY, 1, 0, 0);
                    } else {
                        omOvlGotoEx(OVL_MSTORY2, 1, 1, 0);
                    }
                } else {
                    switch (lbl_1_bss_1A0C.unk00) {
                        case 0:
                            _ClearFlag(2);
                            break;
                        case 1:
                            _ClearFlag(3);
                            break;
                        case 2:
                            _ClearFlag(4);
                            break;
                        case 3:
                            _ClearFlag(5);
                            break;
                        case 4:
                            _ClearFlag(6);
                            break;
                        case 5:
                            _ClearFlag(7);
                            break;
                    }
                    OSReport("########## Next to BoardMiss Event 01 -> MapNo:%d, MapFlg:%d, MgFlg:%d\n", GWSystem.board, fn_1_17484(GWSystem.board), _CheckFlag(9));
                    fn_1_958(120);
                    HuPrcChildCreate(fn_1_1728C, 100, 0x2000, 0, HuPrcCurrentGet());
                    do {
                        fn_1_938();
                    } while (lbl_1_bss_18D4 != 1);
                    if (lbl_1_bss_1A0C.unk00 != 5) {
                        omOvlGotoEx(OVL_MSTORY, 1, 1, 0);
                    } else {
                        omOvlGotoEx(OVL_MSTORY2, 1, 2, 0);
                    }
                }
            } else {
                GWPlayerCfg->group = 0;
                GWPlayerCfg->character = lbl_1_bss_1A0C.unk38[lbl_1_bss_1A0C.unk04].unk10;
                GWPlayerCfg->pad_idx = lbl_1_bss_1A0C.unk38[lbl_1_bss_1A0C.unk04].unk14;
                GWPlayerCfg->iscom = 0;
                for (i = 0; i < 4; i++) {
                    GWPlayer[i].character = GWPlayerCfg[i].character;
                    GWPlayer[i].port = GWPlayerCfg[i].pad_idx;
                    GWPlayer[i].com = GWPlayerCfg[i].iscom;
                    GWPlayer[i].team = GWPlayerCfg[i].group;
                }
                OSReport("########## Next to MapSelect Event 11 -> MapNo:%d, MapFlg:%d, MgFlg:%d\n", GWSystem.board, fn_1_17484(GWSystem.board), _CheckFlag(9));
                fn_1_958(120);
                HuPrcChildCreate(fn_1_1728C, 100, 0x2000, 0, HuPrcCurrentGet());
                do {
                    fn_1_938();
                } while (lbl_1_bss_18D4 != 1);
                omOvlGotoEx(OVL_MENT, 1, 10, 0);
            }
        }
    }
    while (TRUE) {
        fn_1_938();
    }
}

void fn_1_17DC0(omObjData* arg0, StructBss1530* arg1) {
    fn_1_16574();
    fn_1_165C8();
    while (TRUE) {
        fn_1_938();
        if (fn_1_16924() != 0) {
            break;
        }
        fn_1_16AD4();
    }
    fn_1_17570();
    arg1->unk04 = 0;
}

void fn_1_18080(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_18D0, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_19E4.unk00 = temp_r3;
    lbl_1_bss_19E4.unk04 = (void*) fn_1_17DC0;
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_19E4.unk04 != NULL) {
            lbl_1_bss_19E4.unk04(temp_r3, &lbl_1_bss_19E4);
        }
    }
}

void fn_1_1811C(omObjData* arg0, s32 arg1) {
    s32 var_r29;
    s32 i;

    arg0->work[0] = HuSprGrpCreate(1);
    var_r29 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 75) + arg1, MEMORY_DEFAULT_NUM)), 1000, 0);
    HuSprGrpMemberSet(arg0->work[0], 0, var_r29);
    // TODO: figure out the actual args of this fn_1_15D08 call.
    // It will match as long as the values (arg2 + arg4 / 2) and (arg3 + arg5 / 2) are preserved.
    fn_1_15D08(arg0->work[0], 0, 288, 240, 0, 0);
    HuSprGrpPosSet(arg0->work[0], 0.0f, 0.0f);
    HuSprGrpDrawNoSet(arg0->work[0], 0x7F);
    {
        s32 spC[] = {
            DATA_MAKE_NUM(DATADIR_MSTORY3, 104),
            DATA_MAKE_NUM(DATADIR_MSTORY3, 105),
            DATA_MAKE_NUM(DATADIR_MSTORY3, 106),
            DATA_MAKE_NUM(DATADIR_MSTORY3, 107),
            DATA_MAKE_NUM(DATADIR_MSTORY3, 108),
            DATA_MAKE_NUM(DATADIR_MSTORY3, 109),
            DATA_MAKE_NUM(DATADIR_MSTORY3, 106)
        };

        for (i = 0; i < 7; i++) {
            arg0->model[i + 1] = Hu3DModelCreateFile(spC[i]);
            Hu3DModelPosSet(arg0->model[i + 1], -122.5 + 42.5 * i, 185.0f, -10.0f);
            Hu3DModelRotSet(arg0->model[i + 1], 0.0f, 1980.0f, 0.0f);
        }
    }
}

void fn_1_18334(omObjData* arg0, s32* arg1) {
    s32 sp8 = 0;
    s32 i;

    for (i = 0; i < 7; i++) {
        if (arg1[2] == 0 && Hu3DData[arg0->model[i + 1]].pos.x >= lbl_1_bss_1A0C.unk288[0].x) {
            Hu3DData[arg0->model[i + 1]].rot.y = fn_1_5FC(Hu3DData[arg0->model[i + 1]].rot.y, 0.0f, 20.0f);
        } else if (arg1[2] == 1 && Hu3DData[arg0->model[i + 1]].pos.x <= lbl_1_bss_1A0C.unk288[0].x) {
            Hu3DData[arg0->model[i + 1]].rot.y = fn_1_5FC(Hu3DData[arg0->model[i + 1]].rot.y, 1980.0f, 20.0f);
        }
    }
}

void fn_1_184E8(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        Hu3DModelAttrReset(lbl_1_bss_19BC.unk00->model[i + 1], HU3D_ATTR_DISPOFF);
    }
    lbl_1_bss_19BC.unk04 = (void*) fn_1_18334;
}

void fn_1_18558(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        Hu3DModelAttrSet(lbl_1_bss_19BC.unk00->model[i + 1], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 7; i++) {
        if (lbl_1_bss_19BC.unk08 != 0) {
            Hu3DData[lbl_1_bss_19BC.unk00->model[i + 1]].rot.y = 1980.0f;
        } else {
            Hu3DData[lbl_1_bss_19BC.unk00->model[i + 1]].rot.y = 0.0f;
        }
    }
    lbl_1_bss_19BC.unk04 = NULL;
}

void fn_1_18668(omObjData* arg0, s32 arg1) {
    s32 var_r30;
    s32 i;

    // TODO: figure out the actual args of fn_1_15D08 calls.
    // It will match as long as the values (arg2 + arg4 / 2) and (arg3 + arg5 / 2) are preserved.
    arg0->work[1] = HuSprGrpCreate(8);
    var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 116), MEMORY_DEFAULT_NUM)), 900, 0);
    HuSprGrpMemberSet(arg0->work[1], 0, var_r30);
    fn_1_15D08(arg0->work[1], 0, 368, 171, 0, 0);
    var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 117), MEMORY_DEFAULT_NUM)), 600, 0);
    HuSprGrpMemberSet(arg0->work[1], 1, var_r30);
    fn_1_15D08(arg0->work[1], 1, 292, 168, 0, 0);
    var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 118), MEMORY_DEFAULT_NUM)), 500, 0);
    HuSprGrpMemberSet(arg0->work[1], 2, var_r30);
    fn_1_15D08(arg0->work[1], 2, 292, 168, 0, 0);
    var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 119), MEMORY_DEFAULT_NUM)), 500, 0);
    HuSprGrpMemberSet(arg0->work[1], 3, var_r30);
    fn_1_15D08(arg0->work[1], 3, 292, 168, 0, 0);
    var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(arg1 + DATA_MAKE_NUM(DATADIR_MSTORY3, 110), MEMORY_DEFAULT_NUM)), 500, 0);
    HuSprGrpMemberSet(arg0->work[1], 4, var_r30);
    fn_1_15D08(arg0->work[1], 4, 96, 53, 0, 0);
    var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 138), MEMORY_DEFAULT_NUM)), 500, 0);
    HuSprGrpMemberSet(arg0->work[1], 5, var_r30);
    fn_1_15D08(arg0->work[1], 5, 407, 37, 0, 0);
    for (i = 0; i < 2; i++) {
        var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 139), MEMORY_DEFAULT_NUM)), 500, 0);
        HuSprGrpMemberSet(arg0->work[1], i + 6, var_r30);
    }
    // TODO: figure out the actual value of arg7. It will match as long as arg7 >= 2.
    fn_1_15DC8(arg0->work[1], 6, lbl_1_bss_1A0C.unk08, 293, 19, 36, 36, 2);
    arg0->work[2] = HuSprGrpCreate(2);
    var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 120), MEMORY_DEFAULT_NUM)), 800, 0);
    HuSprGrpMemberSet(arg0->work[2], 0, var_r30);
    fn_1_15D08(arg0->work[2], 0, 34, 119, 0, 0);
    var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 121), MEMORY_DEFAULT_NUM)), 400, 0);
    HuSprGrpMemberSet(arg0->work[2], 1, var_r30);
    fn_1_15D08(arg0->work[2], 1, 36, 121, 0, 0);
    arg0->work[3] = HuSprGrpCreate(12);
    for (i = 0; i < 12; i++) {
        var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(i + DATA_MAKE_NUM(DATADIR_MSTORY3, 124), MEMORY_DEFAULT_NUM)), 700, 0);
        HuSprGrpMemberSet(arg0->work[3], i, var_r30);
        fn_1_15D08(arg0->work[3], i, i * 66, 16, 58, 0);
    }
    HuSprGrpPosSet(arg0->work[2], 164 + lbl_1_bss_1A0C.unk2C4 * 66, 78.0f);
    HuSprGrpDrawNoSet(arg0->work[1], 0x7F);
    HuSprGrpDrawNoSet(arg0->work[2], 0x7F);
    HuSprGrpDrawNoSet(arg0->work[3], 0x7F);
}

void fn_1_18CFC(omObjData* arg0) {
    float temp_f31;
    float var_f30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r30;

    var_r28 = lbl_1_bss_1A0C.unk2C8 - lbl_1_bss_1A0C.unk2C4;
    if (var_r28 < 0) {
        var_r28 = 0;
    }
    temp_f31 = HuSprGrpData[arg0->work[2]].x;
    var_f30 = 164 + lbl_1_bss_1A0C.unk2C4 * 66;
    temp_f31 = fn_1_5FC(temp_f31, var_f30, 2.0f);
    HuSprGrpPosSet(arg0->work[1], -5.0f, 25.0f);
    HuSprGrpPosSet(arg0->work[2], temp_f31, 78.0f);
    HuSprGrpPosSet(arg0->work[3], 169 - var_r28 * 66, 82.0f);
    for (var_r30 = 0; var_r30 < 12; var_r30++) {
        if (var_r30 < var_r28 || var_r30 > var_r28 + 5) {
            HuSprAttrSet(arg0->work[3], var_r30, HUSPR_ATTR_DISPOFF);
        } else {
            HuSprAttrReset(arg0->work[3], var_r30, HUSPR_ATTR_DISPOFF);
        }
    }
    var_r29 = lbl_1_bss_1A0C.unk2C8 - lbl_1_bss_1A0C.unk2C4;
    if (var_r29 < 0) {
        var_r29 = 0;
    }
    if (var_r29 == 0) {
        HuSprBankSet(lbl_1_bss_19BC.unk00->work[1], 2, 2);
    } else if (var_r29 == 1) {
        HuSprBankSet(lbl_1_bss_19BC.unk00->work[1], 2, 0);
    }
    if (var_r29 == 6) {
        HuSprBankSet(lbl_1_bss_19BC.unk00->work[1], 3, 2);
    } else if (var_r29 == 5) {
        HuSprBankSet(lbl_1_bss_19BC.unk00->work[1], 3, 0);
    }
}

void fn_1_18F98(void) {
    s32 var_r30;
    s32 i;

    for (i = 0; i < 8; i++) {
        HuSprAttrReset(lbl_1_bss_19BC.unk00->work[1], i, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 2; i++) {
        HuSprAttrReset(lbl_1_bss_19BC.unk00->work[2], i, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 12; i++) {
        HuSprAttrReset(lbl_1_bss_19BC.unk00->work[3], i, HUSPR_ATTR_DISPOFF);
    }
    var_r30 = lbl_1_bss_1A0C.unk2C8 - lbl_1_bss_1A0C.unk2C4;
    if (var_r30 < 0) {
        var_r30 = 0;
    }
    if (var_r30 == 0) {
        HuSprBankSet(lbl_1_bss_19BC.unk00->work[1], 2, 2);
    } else if (var_r30 == 1) {
        HuSprBankSet(lbl_1_bss_19BC.unk00->work[1], 2, 0);
    }
    if (var_r30 == 6) {
        HuSprBankSet(lbl_1_bss_19BC.unk00->work[1], 3, 2);
    } else if (var_r30 == 5) {
        HuSprBankSet(lbl_1_bss_19BC.unk00->work[1], 3, 0);
    }
    lbl_1_bss_19BC.unk04 = (void*) fn_1_18CFC;
}

void fn_1_19144(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        HuSprAttrSet(lbl_1_bss_19BC.unk00->work[1], i, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 2; i++) {
        HuSprAttrSet(lbl_1_bss_19BC.unk00->work[2], i, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 12; i++) {
        HuSprAttrSet(lbl_1_bss_19BC.unk00->work[3], i, HUSPR_ATTR_DISPOFF);
    }
    lbl_1_bss_19BC.unk04 = NULL;
}

void fn_1_19214(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_18D0, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_19BC.unk00 = temp_r3;
    lbl_1_bss_19BC.unk04 = NULL;
    fn_1_1811C(temp_r3, lbl_1_bss_1A0C.unk00);
    fn_1_18668(temp_r3, lbl_1_bss_1A0C.unk00);
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_19BC.unk04 != NULL) {
            lbl_1_bss_19BC.unk04(temp_r3, &lbl_1_bss_19BC);
        }
    }
}

void fn_1_194A0(void) {
    s32 var_r29;
    s32 i;
    s32 j;

    for (i = 0; i < 12; i++) {
        var_r29 = 0;
        for (j = 0; j < 4; j++) {
            if (var_r29 <= lbl_1_bss_1A0C.unk38[j].unk34[i][0]) {
                var_r29 = lbl_1_bss_1A0C.unk38[j].unk34[i][0];
            }
        }
        if (var_r29 > 0) {
            for (j = 0; j < 4; j++) {
                if (var_r29 == lbl_1_bss_1A0C.unk38[j].unk34[i][0]) {
                    lbl_1_bss_1A0C.unk38[j].unk34[i][1] = 1;
                }
            }
        }
    }
}

void fn_1_19590(StructUnk38Bss1A0C* arg0, s32 arg1, s32 arg2) {
    arg0->unk00 = arg1;
    arg0->unk04 = GWPlayerCfg[arg0->unk00].group;
    arg0->unk08 = GWPlayerCfg[arg0->unk00].iscom;
    arg0->unk0C = GWPlayerCfg[arg0->unk00].diff;
    arg0->unk10 = GWPlayerCfg[arg0->unk00].character;
    arg0->unk14 = GWPlayerCfg[arg0->unk00].pad_idx;
    arg0->unk18 = GWPlayer[arg0->unk00].rank;
    arg0->unk34[0][0] = GWPlayer[arg0->unk00].stars;
    arg0->unk34[1][0] = GWPlayer[arg0->unk00].coins;
    arg0->unk34[2][0] = GWPlayer[arg0->unk00].coins_mg;
    arg0->unk34[3][0] = GWPlayer[arg0->unk00].coins_max;
    arg0->unk54 = GWPlayer[arg0->unk00].blue_count;
    arg0->unk5C = GWPlayer[arg0->unk00].red_count;
    arg0->unk64 = GWPlayer[arg0->unk00].question_count;
    arg0->unk6C = GWPlayer[arg0->unk00].fortune_count;
    arg0->unk74 = GWPlayer[arg0->unk00].bowser_count;
    arg0->unk7C = GWPlayer[arg0->unk00].battle_count;
    arg0->unk84 = GWPlayer[arg0->unk00].mushroom_count;
    arg0->unk8C = GWPlayer[arg0->unk00].warp_count;
}

void fn_1_197B4(s32 arg0) {
    s32 sp74[4][2];
    s32 sp54[4][2];
    s32 sp44[4];
    s32 sp34[4];
    s32 sp24[4];
    s32 var_r28;
    s32 var_r29;
    s32 j;
    s32 i;

    var_r28 = 0;
    sp44[0] = 0;
    for (i = 1; i < 4; i++) {
        sp44[i] = sp44[i - 1] + 1;
        if (sp44[i] >= 4) {
            sp44[i] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        sp34[i] = GWPlayer[sp44[i]].rank;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == sp34[j]) {
                sp74[var_r28][0] = sp44[j];
                sp74[var_r28][1] = sp34[j];
                var_r28++;
            }
        }
    }
    if (lbl_1_bss_1A0C.unk2CC == 1) {
        var_r29 = lbl_1_bss_1A0C.unk2D0;
        for (i = 0; i < 4; i++) {
            sp24[0] = GWPlayer[sp74[0][0]].team;
            sp24[1] = GWPlayer[sp74[1][0]].team;
            sp24[2] = GWPlayer[sp74[2][0]].team;
            sp24[3] = GWPlayer[sp74[3][0]].team;
            sp54[i][0] = sp74[i][0];
            sp54[i][1] = sp74[i][1];
        }
        OSReport("########## Sort Start WIN:%d  IDX (%d,%d,%d), (%d,%d,%d), (%d,%d,%d), (%d,%d,%d)\n", var_r29,
            sp24[0], sp74[0][0], sp74[0][1], sp24[1], sp74[1][0], sp74[1][1],
            sp24[2], sp74[2][0], sp74[2][1], sp24[3], sp74[3][0], sp74[3][1]);
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (sp24[j] != -1 && var_r29 == sp24[j]) {
                    sp24[j] = -1;
                    sp74[i][0] = sp54[j][0];
                    sp74[i][1] = sp54[j][1];
                    break;
                }
            }
            if (i == 1) {
                var_r29++;
                var_r29 %= 2;
            }
        }
        OSReport("########## Sort End WIN:%d  IDX %d, %d, %d, %d\n", var_r29, sp74[0][0], sp74[1][0], sp74[2][0], sp74[3][0]);
        OSReport("########## Sort End RANK %d, %d, %d, %d,\n", sp74[0][1], sp74[1][1], sp74[2][1], sp74[3][1]);
    }
    for (i = 0; i < 4; i++) {
        fn_1_19590(&lbl_1_bss_1A0C.unk38[i], sp74[i][0], sp74[i][1]);
        if (arg0 == sp74[i][0]) {
            lbl_1_bss_1A0C.unk04 = i;
        }
    }
}

void fn_1_1A008(omObjData* arg0, s32 arg1) {
    s32 spDC;
    s32 spD8;
    s32 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    StructUnk38Bss1A0C* temp_r27;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    // TODO: figure out the actual args of fn_1_15D08 calls.
    // It will match as long as the values (arg2 + arg4 / 2) and (arg3 + arg5 / 2) are preserved.
    temp_r27 = &lbl_1_bss_1A0C.unk38[arg1];
    if (lbl_1_bss_1A0C.unk2CC == 1) {
        spD4 = lbl_1_bss_1A0C.unk2D0;
        if (arg1 > 1) {
            spD4++;
            spD4 %= 2;
        }
        arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 140) + spD4);
        arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 142) + spD4);
        arg0->motion[2] = Hu3DMotionIDGet(arg0->model[2]);
        if (arg1 <= 1) {
            spD4 = 0;
        } else {
            spD4 = 1;
        }
        arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 100) + spD4);
        Hu3DModelHookSet(arg0->model[1], "results_flag04-hook_cubes", arg0->model[3]);
    } else {
        arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 98));
        arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 99));
        arg0->motion[2] = Hu3DMotionIDGet(arg0->model[2]);
        arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 100) + temp_r27->unk18);
        Hu3DModelHookSet(arg0->model[1], "results_flag04-hook_cubes", arg0->model[3]);
    }
    arg0->work[0] = HuSprGrpCreate(12);
    if (lbl_1_bss_1A0C.unk2CC == 1) {
        spD0 = 35;
        spCC = 10;
        spC8 = 65;
        if (arg1 <= 1) {
            var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 81), MEMORY_DEFAULT_NUM)), 900, 0);
        } else {
            var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 82), MEMORY_DEFAULT_NUM)), 900, 0);
        }
        HuSprGrpMemberSet(arg0->work[0], 0, var_r30);
        fn_1_15D08(arg0->work[0], 0, 40, spD0 + 36, 0, 0);
        var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 85) + temp_r27->unk10, MEMORY_DEFAULT_NUM)), 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 1, var_r30);
        if (arg1 % 2 == 0) {
            fn_1_15D08(arg0->work[0], 1, 119, spD0 + 34, 0, 0);
        } else {
            fn_1_15D08(arg0->work[0], 1, 189, -spD0 + 24, 0, 0);
        }
        var_r30 = HuSprCreate(lbl_1_bss_18D8[0], 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 2, var_r30);
        fn_1_15D08(arg0->work[0], 2, 262, spCC + 29, 0, 0);
        var_r30 = HuSprCreate(lbl_1_bss_18D8[2], 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 3, var_r30);
        fn_1_15D08(arg0->work[0], 3, 312, spCC + 29, 0, 0);
        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            spDC = lbl_1_bss_1A0C.unk38[0].unk34[0][0] + lbl_1_bss_1A0C.unk38[1].unk34[0][0];
            spD8 = lbl_1_bss_1A0C.unk38[2].unk34[0][0] + lbl_1_bss_1A0C.unk38[3].unk34[0][0];
            if (arg1 <= 1) {
                if (spDC >= spD8) {
                    var_r30 = HuSprCreate(lbl_1_bss_18EC[1], 900, 0);
                } else {
                    var_r30 = HuSprCreate(lbl_1_bss_18EC[0], 900, 0);
                }
            } else {
                if (spDC <= spD8) {
                    var_r30 = HuSprCreate(lbl_1_bss_18EC[1], 900, 0);
                } else {
                    var_r30 = HuSprCreate(lbl_1_bss_18EC[0], 900, 0);
                }
            }
            HuSprGrpMemberSet(arg0->work[0], var_r28 + 4, var_r30);
        }
        if (arg1 <= 1) {
            var_r29 = lbl_1_bss_1A0C.unk38[0].unk34[0][0] + lbl_1_bss_1A0C.unk38[1].unk34[0][0];
            if (var_r29 >= 999) {
                var_r29 = 999;
            }
            fn_1_15DC8(arg0->work[0], 4, var_r29, 340, spCC + 11, 26, 36, 0);
        } else {
            var_r29 = lbl_1_bss_1A0C.unk38[2].unk34[0][0] + lbl_1_bss_1A0C.unk38[3].unk34[0][0];
            if (var_r29 >= 999) {
                var_r29 = 999;
            }
            fn_1_15DC8(arg0->work[0], 4, var_r29, 340, spCC + 11, 26, 36, 0);
        }
        var_r30 = HuSprCreate(lbl_1_bss_18D8[1], 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 7, var_r30);
        fn_1_15D08(arg0->work[0], 7, 262, spC8 + 29, 0, 0);
        var_r30 = HuSprCreate(lbl_1_bss_18D8[2], 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 8, var_r30);
        fn_1_15D08(arg0->work[0], 8, 312, spC8 + 29, 0, 0);
        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            spDC = lbl_1_bss_1A0C.unk38[0].unk34[1][0] + lbl_1_bss_1A0C.unk38[1].unk34[1][0];
            spD8 = lbl_1_bss_1A0C.unk38[2].unk34[1][0] + lbl_1_bss_1A0C.unk38[3].unk34[1][0];
            if (arg1 <= 1) {
                if (spDC >= spD8) {
                    var_r30 = HuSprCreate(lbl_1_bss_18EC[1], 900, 0);
                } else {
                    var_r30 = HuSprCreate(lbl_1_bss_18EC[0], 900, 0);
                }
            } else {
                if (spDC <= spD8) {
                    var_r30 = HuSprCreate(lbl_1_bss_18EC[1], 900, 0);
                } else {
                    var_r30 = HuSprCreate(lbl_1_bss_18EC[0], 900, 0);
                }
            }
            HuSprGrpMemberSet(arg0->work[0], var_r28 + 9, var_r30);
        }
        if (arg1 <= 1) {
            var_r29 = lbl_1_bss_1A0C.unk38[0].unk34[1][0] + lbl_1_bss_1A0C.unk38[1].unk34[1][0];
            if (var_r29 >= 999) {
                var_r29 = 999;
            }
            fn_1_15DC8(arg0->work[0], 9, var_r29, 340, spC8 + 11, 26, 36, 0);
        } else {
            var_r29 = lbl_1_bss_1A0C.unk38[2].unk34[1][0] + lbl_1_bss_1A0C.unk38[3].unk34[1][0];
            if (var_r29 >= 999) {
                var_r29 = 999;
            }
            fn_1_15DC8(arg0->work[0], 9, var_r29, 340, spC8 + 11, 26, 36, 0);
        }
    } else {
        var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 81) + temp_r27->unk18, MEMORY_DEFAULT_NUM)), 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 0, var_r30);
        fn_1_15D08(arg0->work[0], 0, 25, 37, 0, 0);
        var_r30 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 85) + temp_r27->unk10, MEMORY_DEFAULT_NUM)), 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 1, var_r30);
        fn_1_15D08(arg0->work[0], 1, 87, 29, 0, 0);
        var_r30 = HuSprCreate(lbl_1_bss_18D8[0], 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 2, var_r30);
        fn_1_15D08(arg0->work[0], 2, 144, 29, 0, 0);
        var_r30 = HuSprCreate(lbl_1_bss_18D8[2], 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 3, var_r30);
        fn_1_15D08(arg0->work[0], 3, 178, 29, 0, 0);
        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            var_r30 = HuSprCreate(lbl_1_bss_18EC[temp_r27->unk34[0][1]], 900, 0);
            HuSprGrpMemberSet(arg0->work[0], (var_r28 + 4), var_r30);
        }
        fn_1_15DC8(arg0->work[0], 4, temp_r27->unk34[0][0], 190, 11, 26, 36, 0);
        var_r30 = HuSprCreate(lbl_1_bss_18D8[1], 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 7, var_r30);
        fn_1_15D08(arg0->work[0], 7, 304, 29, 0, 0);
        var_r30 = HuSprCreate(lbl_1_bss_18D8[2], 900, 0);
        HuSprGrpMemberSet(arg0->work[0], 8, var_r30);
        fn_1_15D08(arg0->work[0], 8, 338, 29, 0, 0);
        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            var_r30 = HuSprCreate(lbl_1_bss_18EC[temp_r27->unk34[1][1]], 900, 0);
            HuSprGrpMemberSet(arg0->work[0], var_r28 + 9, var_r30);
        }
        fn_1_15DC8(arg0->work[0], 9, temp_r27->unk34[1][0], 350, 11, 26, 36, 0);
    }
    lbl_1_bss_18F4[var_r28].unk14 = 1000 + rand8() * 5;
}

void fn_1_1BEFC(omObjData* arg0, StructBss1530* arg1) {
    Mtx sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 var_r29;

    if (lbl_1_bss_1A0C.unk2CC == 1) {
        if (arg1->unk08 % 2 == 1) {
            Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF);
            for (var_r29 = 0; var_r29 < 12; var_r29++) {
                HuSprAttrSet(arg0->work[0], var_r29, 4);
            }
        }
        HuSprAttrReset(arg0->work[0], 1, HUSPR_ATTR_DISPOFF);
        Hu3DModelPosSet(arg0->model[1], lbl_1_bss_1A0C.unk288[arg1->unk08 + 1].x + 15.0f, lbl_1_bss_1A0C.unk288[arg1->unk08 + 1].y + 25.0f - 35.0f, lbl_1_bss_1A0C.unk288[arg1->unk08 + 1].z);
    } else {
        Hu3DModelPosSet(arg0->model[1], lbl_1_bss_1A0C.unk288[arg1->unk08 + 1].x + 15.0f, lbl_1_bss_1A0C.unk288[arg1->unk08 + 1].y + 25.0f, lbl_1_bss_1A0C.unk288[arg1->unk08 + 1].z);
    }
    if (Hu3DData[arg0->model[1]].pos.x <= -195.0f) {
        Hu3DData[arg0->model[1]].pos.x = -195.0f;
    }
    Hu3DModelObjMtxGet(arg0->model[1], "results_flag04-hook_flag", sp2C);
    Hu3DModelPosSet(arg0->model[2], sp2C[0][3], sp2C[1][3], sp2C[2][3]);
    if (arg1->unk0C++ >= arg1->unk14) {
        arg1->unk0C = 0;
        arg1->unk14 = rand8() * 5 + 1000;
        fn_1_1E28(arg0, 2, 2, 0, 0);
    }
    Hu3DModelRotSet(arg0->model[3], 0.0f, arg1->unk10 += 3, 0.0f);
    if (arg1->unk10 >= 360) {
        arg1->unk10 -= 360;
    }
    sp8.x = Hu3DData[arg0->model[1]].pos.x;
    sp8.y = lbl_1_bss_1A0C.unk288[arg1->unk08 + 1].y + 25.0f;
    sp8.z = Hu3DData[arg0->model[1]].pos.z;
    sp20.x = sp8.x + 24.0f;
    sp20.y = sp8.y + 40.0f;
    sp20.z = sp8.z;
    Hu3D3Dto2D(&sp20, 1, &sp14);
    HuSprGrpPosSet(arg0->work[0], sp14.x, sp14.y);
}

void fn_1_1C2F4(void) {
    s32 var_r30;
    s32 var_r31;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            Hu3DModelAttrReset(lbl_1_bss_18F4[var_r30].unk00->model[var_r31 + 1], HU3D_ATTR_DISPOFF);
        }
        if (lbl_1_bss_1A0C.unk2CC == 1) {
            if (var_r30 % 2 == 0) {
                for (var_r31 = 0; var_r31 < 12; var_r31++) {
                    HuSprAttrReset(lbl_1_bss_18F4[var_r30].unk00->work[0], var_r31, HUSPR_ATTR_DISPOFF);
                }
            }
            HuSprAttrReset(lbl_1_bss_18F4[var_r30].unk00->work[0], 1, HUSPR_ATTR_DISPOFF);
        } else {
            for (var_r31 = 0; var_r31 < 12; var_r31++) {
                HuSprAttrReset(lbl_1_bss_18F4[var_r30].unk00->work[0], var_r31, HUSPR_ATTR_DISPOFF);
            }
        }
        lbl_1_bss_18F4[var_r30].unk04 = (void*) fn_1_1BEFC;
    }
}

void fn_1_1C460(void) {
    s32 var_r30;
    s32 var_r31;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            Hu3DModelAttrSet(lbl_1_bss_18F4[var_r30].unk00->model[var_r31 + 1], HU3D_ATTR_DISPOFF);
        }
        for (var_r31 = 0; var_r31 < 12; var_r31++) {
            HuSprAttrSet(lbl_1_bss_18F4[var_r30].unk00->work[0], var_r31, HUSPR_ATTR_DISPOFF);
        }
        lbl_1_bss_18F4[var_r30].unk04 = NULL;
    }
}

void fn_1_1C534(omObjData* arg0, s32 arg1) {
    StructUnk38Bss1A0C* temp_r25;
    s32 var_r22;
    s32 i;
    s32 j;

    temp_r25 = &lbl_1_bss_1A0C.unk38[arg1];
    arg0->work[1] = HuSprGrpCreate(1);
    var_r22 = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY3, 122), MEMORY_DEFAULT_NUM)), 700, 0);
    HuSprGrpMemberSet(arg0->work[1], 0, var_r22);
    HuSprBankSet(arg0->work[1], 0, temp_r25->unk10);
    // TODO: figure out the actual args of this fn_1_15D08 call.
    // It will match as long as the values (arg2 + arg4 / 2) and (arg3 + arg5 / 2) are preserved. 
    fn_1_15D08(arg0->work[1], 0, 66, 21, 0, 0);
    arg0->work[2] = HuSprGrpCreate(0x24);
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 3; j++) {
            var_r22 = HuSprCreate(lbl_1_bss_18E4[temp_r25->unk34[i][1]], 700, 0);
            HuSprGrpMemberSet(arg0->work[2], j + i * 3, var_r22);
        }
        fn_1_15DC8(arg0->work[2], i * 3, temp_r25->unk34[i][0], i * 66, 0, 20, 32, 1);
    }
    HuSprGrpDrawNoSet(arg0->work[1], 0x7F);
    HuSprGrpDrawNoSet(arg0->work[2], 0x7F);
}

void fn_1_1C914(omObjData* arg0, StructBss1530* arg1) {
    s32 i;
    s32 j;
    s32 var_r28;

    var_r28 = lbl_1_bss_1A0C.unk2C8 - lbl_1_bss_1A0C.unk2C4;
    if (var_r28 < 0) {
        var_r28 = 0;
    }
    HuSprGrpPosSet(arg0->work[1], 17.0f, arg1->unk08 * 48 + 118);
    HuSprGrpPosSet(arg0->work[2], 169 - var_r28 * 66, arg1->unk08 * 48 + 123);
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 3; j++) {
            if (i < var_r28 || i > var_r28 + 5) {
                HuSprAttrSet(arg0->work[2], j + i * 3, HUSPR_ATTR_DISPOFF);
            } else {
                HuSprAttrReset(arg0->work[2], j + i * 3, HUSPR_ATTR_DISPOFF);
            }
        }
    }
}

void fn_1_1CA98(void) {
    s32 i, j, k;

    for (i = 0; i < 4; i++) {
        HuSprAttrReset(lbl_1_bss_18F4[i].unk00->work[1], 0, HUSPR_ATTR_DISPOFF);
        for (j = 0; j < 12; j++) {
            for (k = 0; k < 3; k++) {
                HuSprAttrReset(lbl_1_bss_18F4[i].unk00->work[2], k + j * 3, HUSPR_ATTR_DISPOFF);
            }
        }
        lbl_1_bss_18F4[i].unk04 = (void*) fn_1_1C914;
    }
}

void fn_1_1CB7C(void) {
    s32 i, j, k;

    for (i = 0; i < 4; i++) {
        HuSprAttrSet(lbl_1_bss_18F4[i].unk00->work[1], 0, HUSPR_ATTR_DISPOFF);
        for (j = 0; j < 12; j++) {
            for (k = 0; k < 3; k++) {
                HuSprAttrSet(lbl_1_bss_18F4[i].unk00->work[2], k + j * 3, HUSPR_ATTR_DISPOFF);
            }
        }
        lbl_1_bss_18F4[i].unk04 = NULL;
    }
}

void fn_1_1CC5C(void) {
    omObjData* temp_r3;
    s32 temp_r31;

    temp_r31 = lbl_1_bss_1A0C.unk18++;
    temp_r3 = omAddObjEx(lbl_1_bss_18D0, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_18F4[temp_r31].unk00 = temp_r3;
    lbl_1_bss_18F4[temp_r31].unk04 = NULL;
    lbl_1_bss_18F4[temp_r31].unk08 = temp_r31;
    fn_1_1A008(temp_r3, temp_r31);
    fn_1_1C534(temp_r3, temp_r31);
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_18F4[temp_r31].unk04 != NULL) {
            lbl_1_bss_18F4[temp_r31].unk04(temp_r3, &lbl_1_bss_18F4[temp_r31]);
        }
    }
}

void fn_1_1CD60(void) {
    if (lbl_1_bss_1994.unk00->work[0] != 1) {
        fn_1_1E28(lbl_1_bss_1994.unk00, 4, 6, 15, 0);
        lbl_1_bss_1994.unk00->work[0] = 1;
        lbl_1_bss_1994.unk00->work[1] = 4;
        lbl_1_bss_1994.unk00->work[2] = 16;
    }
}

void fn_1_1CDF0(omObjData* arg0) {
    s32 sp20[] = {
        DATA_MAKE_NUM(DATADIR_MSTORY3, 46),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 40),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 52),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 58),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 64)
    };
    s32 sp34[][3] = {
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 47), DATA_MAKE_NUM(DATADIR_MSTORY3, 48), DATA_MAKE_NUM(DATADIR_MSTORY3, 49) },
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 41), DATA_MAKE_NUM(DATADIR_MSTORY3, 42), DATA_MAKE_NUM(DATADIR_MSTORY3, 43) },
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 53), DATA_MAKE_NUM(DATADIR_MSTORY3, 54), DATA_MAKE_NUM(DATADIR_MSTORY3, 55) },
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 59), DATA_MAKE_NUM(DATADIR_MSTORY3, 60), DATA_MAKE_NUM(DATADIR_MSTORY3, 61) },
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 65), DATA_MAKE_NUM(DATADIR_MSTORY3, 66), DATA_MAKE_NUM(DATADIR_MSTORY3, 67) }
    };
    s32 i;

    for (i = 0; i < 5; i++) {
        arg0->model[i * 3 + 1] = Hu3DModelCreateFile(sp20[i]);
        arg0->motion[i * 3 + 1] = Hu3DJointMotionFile(arg0->model[i * 3 + 1], sp34[i][0]);
        arg0->motion[i * 3 + 2] = Hu3DJointMotionFile(arg0->model[i * 3 + 1], sp34[i][1]);
        arg0->motion[i * 3 + 3] = Hu3DJointMotionFile(arg0->model[i * 3 + 1], sp34[i][2]);
        Hu3DModelRotSet(arg0->model[i * 3 + 1], 17.5f, 0.0f, 0.0f);
        Hu3DModelScaleSet(arg0->model[i * 3 + 1], 0.575f, 0.575f, 0.575f);
        fn_1_1E28(arg0, i * 3 + 1, i * 3 + 1, 0, 1);
        {
            s32 sp8[] = { 9, 14, 10, 11, 12, 13 };

            if (i != 3) {
                CharModelEffectNpcInit(arg0->model[i * 3 + 1], arg0->motion[i * 3 + 2], 1, sp8[i]);
                CharModelEffectEnableSet(sp8[i], 0);
            }
        }
    }
}

void fn_1_1D124(omObjData* arg0, StructBss1530* arg1) {
    s32 i;

    for (i = 0; i < 5; i++) {
        Hu3DModelPosSet(arg0->model[i * 3 + 1], lbl_1_bss_1A0C.unk288[i].x, lbl_1_bss_1A0C.unk288[i].y, lbl_1_bss_1A0C.unk288[i].z);
        if (i == 3) {
            Hu3DData[arg0->model[i * 3 + 1]].pos.y += 20.0f;
        }
    }
    if (arg1->unk08++ >= 3000) {
        arg1->unk08 = 0;
        arg1->unk0C = 1;
        lbl_1_bss_19BC.unk08++;
        lbl_1_bss_19BC.unk08 %= 2;
        fn_1_1E28(lbl_1_bss_1994.unk00, 1, 2, 15, 1);
    }
    if (arg1->unk0C == 1) {
        lbl_1_bss_1A0C.unk288[0].x += -5.0f + 10.0f * lbl_1_bss_19BC.unk08;
        if (lbl_1_bss_19BC.unk08 != 0) {
            Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y = fn_1_5FC(Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y, 90.0f, 5.0f);
            if (lbl_1_bss_1A0C.unk288[0].x >= 185.0f) {
                arg1->unk0C = 2;
                lbl_1_bss_1A0C.unk288[0].x = 185.0f;
                fn_1_1E28(lbl_1_bss_1994.unk00, 1, 1, 15, 1);
            }
        } else {
            Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y = fn_1_5FC(Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y, -90.0f, 5.0f);
            if (lbl_1_bss_1A0C.unk288[0].x <= -175.0f) {
                arg1->unk0C = 2;
                lbl_1_bss_1A0C.unk288[0].x = -175.0f;
                fn_1_1E28(lbl_1_bss_1994.unk00, 1, 1, 15, 1);
            }
        }
    } else if (arg1->unk0C == 2) {
        if (lbl_1_bss_19BC.unk08 != 0) {
            Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y = fn_1_5FC(Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y, -15.0f, 15.0f);
            if (Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y <= -14.9f) {
                arg1->unk0C = 0;
            }
        } else {
            Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y = fn_1_5FC(Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y, 15.0f, 15.0f);
            if (Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y >= 14.9f) {
                arg1->unk0C = 0;
            }
        }
    }
}

void fn_1_1D63C(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        Hu3DModelAttrReset(lbl_1_bss_1994.unk00->model[(i * 3) + 1], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelRotSet(lbl_1_bss_1994.unk00->model[4], 17.5f, 15.0f, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_1994.unk00->model[4], 0.575f, 0.575f, 0.575f);
    fn_1_1E28(lbl_1_bss_1994.unk00, 4, 4, 0, 1);
    lbl_1_bss_1994.unk00->work[0] = lbl_1_bss_1994.unk00->work[1] = lbl_1_bss_1994.unk00->work[2] = 0;
    lbl_1_bss_1994.unk04 = (void*) fn_1_1D124;
}

void fn_1_1D77C(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        Hu3DModelAttrSet(lbl_1_bss_1994.unk00->model[i * 3 + 1], HU3D_ATTR_DISPOFF);
    }
    fn_1_1E28(lbl_1_bss_1994.unk00, 1, 1, 0, 1);
    if (lbl_1_bss_19BC.unk08 != 0) {
        lbl_1_bss_1A0C.unk288[0].x = 185.0f;
        Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y = -15.0f;
    } else {
        lbl_1_bss_1A0C.unk288[0].x = -175.0f;
        Hu3DData[lbl_1_bss_1994.unk00->model[1]].rot.y = 15.0f;
    }
    lbl_1_bss_1994.unk0C = 0;
    lbl_1_bss_1994.unk04 = NULL;
}

void fn_1_1D8CC(omObjData* arg0, StructBss1530* arg1) {
    if (arg0->work[0] != 0) {
        if (arg0->work[2] != 0) {
            arg0->work[2]--;
            return;
        }
        if (arg0->work[2] == 0 && Hu3DMotionEndCheck(arg0->model[4])) {
            fn_1_1E28(arg0, 4, arg0->work[1], 15, 1);
            arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
        }
    }
}

void fn_1_1D964(void) {
    Hu3DModelAttrReset(lbl_1_bss_1994.unk00->model[4], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(lbl_1_bss_1994.unk00->model[4], -185.0f, -225.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_1994.unk00->model[4], 0.0f, 15.0f, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_1994.unk00->model[4], 1.0f, 1.0f, 1.0f);
    lbl_1_bss_1994.unk04 = (void*) fn_1_1D8CC;
}

void fn_1_1DA64(void) {
    Hu3DModelAttrSet(lbl_1_bss_1994.unk00->model[4], HU3D_ATTR_DISPOFF);
    lbl_1_bss_1994.unk04 = NULL;
}

void fn_1_1DAAC(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_18D0, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_1994.unk00 = temp_r3;
    lbl_1_bss_1994.unk04 = NULL;
    fn_1_1CDF0(temp_r3);
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_1994.unk04 != NULL) {
            lbl_1_bss_1994.unk04(temp_r3, &lbl_1_bss_1994);
        }
    }
}

void fn_1_1DE4C(void) {
    StructBss4* var_r31;

    var_r31 = &lbl_1_bss_4;
    var_r31->unk08.x = 0.0f;
    var_r31->unk08.y = 0.0f;
    var_r31->unk08.z = 0.0f;
    var_r31->unk20.x = 0.0f;
    var_r31->unk20.y = 0.0f;
    var_r31->unk20.z = 0.0f;
    var_r31->unk38 = 650.0f;
}
