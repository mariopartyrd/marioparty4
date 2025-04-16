#include "REL/m447dll.h"
#include "REL/executor.h"
#include "game/esprite.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/window.h"
#include "game/wipe.h"

#include "math.h"

#ifndef __MWERKS__
#include "game/audio.h"
#endif

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
} UnkM447Struct_03; // Size 0xC

void fn_1_12C(void);
UnkM447Struct_00* fn_1_1B8(void);
void fn_1_43C(UnkM447Struct_00* arg0);
BOOL fn_1_490(UnkM447Struct_00* arg0);
void fn_1_4A0(UnkM447Struct_00* arg0, s32 arg1);
void fn_1_4B0(void);
void fn_1_544(UnkM447Struct_00* arg0);
void fn_1_7A8(UnkM447Struct_00* arg0);
void fn_1_B5C(UnkM447Struct_00* arg0);
void fn_1_F34(UnkM447Struct_00* arg0);
void fn_1_1068(UnkM447Struct_00* arg0);
void fn_1_1394(UnkM447Struct_00* arg0, s16 arg1, s32 arg2);
s32 fn_1_141C(UnkM447Struct_00* arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_1484(void);
void fn_1_1754(UnkM447Struct_00* arg0);
void fn_1_1830(UnkM447Struct_00* arg0);
void fn_1_1884(UnkM447Struct_00* arg0);
void fn_1_1AFC(UnkM447Struct_00* arg0, s32 arg1, s32 arg2);
void fn_1_1BF8(void);
void fn_1_1CE0(UnkM447Struct_00* arg0);
void fn_1_1D34(UnkM447Struct_00* arg0);

UnkM447Struct_06* lbl_1_bss_10;
char lbl_1_bss_C_pad[4];
UnkM447Struct_00* lbl_1_bss_8;
Process* lbl_1_bss_4;
Process* lbl_1_bss_0;

const s32 lbl_1_rodata_10[] = {
    DATA_MAKE_NUM(DATADIR_M447, 53),
    DATA_MAKE_NUM(DATADIR_M447, 53),
    DATA_MAKE_NUM(DATADIR_M447, 54),
    DATA_MAKE_NUM(DATADIR_M447, 54),
    DATA_MAKE_NUM(DATADIR_M447, 55),
    DATA_MAKE_NUM(DATADIR_M447, 55),
    DATA_MAKE_NUM(DATADIR_M447, 55),
    DATA_MAKE_NUM(DATADIR_M447, 56),
    DATA_MAKE_NUM(DATADIR_M447, 56),
    DATA_MAKE_NUM(DATADIR_M447, 56),
    DATA_MAKE_NUM(DATADIR_M447, 55),
    DATA_MAKE_NUM(DATADIR_M447, 55),
    DATA_MAKE_NUM(DATADIR_M447, 55),
    DATA_MAKE_NUM(DATADIR_M447, 56),
    DATA_MAKE_NUM(DATADIR_M447, 56),
    DATA_MAKE_NUM(DATADIR_M447, 56),
    DATA_MAKE_NUM(DATADIR_M447, 44),
    DATA_MAKE_NUM(DATADIR_M447, 45),
    DATA_MAKE_NUM(DATADIR_M447, 46),
    DATA_MAKE_NUM(DATADIR_M447, 47),
    DATA_MAKE_NUM(DATADIR_M447, 48),
    DATA_MAKE_NUM(DATADIR_M447, 49),
    DATA_MAKE_NUM(DATADIR_M447, 50),
    DATA_MAKE_NUM(DATADIR_M447, 51),
    DATA_MAKE_NUM(DATADIR_M447, 52)
};

void ObjectSetup(void) {
    lbl_1_bss_4 = omInitObjMan(10, 0x2000);
    omGameSysInit(lbl_1_bss_4);
    HuWinInit(1);
    lbl_1_bss_0 = HuPrcChildCreate(fn_1_12C, 1000, 0x2000, 0, lbl_1_bss_4);
    lbl_1_bss_8 = fn_1_1B8();
}

void fn_1_12C(void) {
    while (omSysExitReq == 0) {
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFadeOut(100);
    fn_1_43C(lbl_1_bss_8);
    HuPrcVSleep();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

UnkM447Struct_00* fn_1_1B8(void) {
    Vec sp2C;
    Vec sp20 = { 0.0f, 3000.0f, 1.0f };
    Vec sp14 = { 0.0f, 1.0f, 0.0f };
    Vec sp8 = { 0.0f, 0.0f, 0.0f };
    UnkM447Struct_00* temp_r3;
    s32 i;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r3), MEMORY_DEFAULT_NUM);
    if (!temp_r3) {
        OSReport("M447FlowCreate ERROR...\n");
        return NULL;
    }
    Hu3DShadowCreate(30.0f, 20.0f, 5000.0f);
    Hu3DShadowTPLvlSet(0.45f);
    Hu3DShadowPosSet(&sp20, &sp14, &sp8);
    fn_1_A230(frand());
    temp_r3->unk08 = 0;
    fn_1_3130();
    lbl_1_bss_10 = fn_1_1D90();
    sp2C.x = 0.0f;
    sp2C.y = -1000.0f;
    sp2C.z = 0.0f;
    for (i = 0; i < 5; i++) {
        lbl_1_bss_A4[i] = fn_1_8DF8();
        lbl_1_bss_A4[i]->unk10 = sp2C;
    }
    fn_1_3F84();
    for (i = 0; i < 2; i++) {
        lbl_1_bss_98[i] = fn_1_3FC4(i);
    }
    fn_1_1D34(temp_r3);
    fn_1_1754(temp_r3);
    temp_r3->unk14 = 0;
    temp_r3->unk1C = 0;
    temp_r3->unk24 = 0;
    temp_r3->unk28 = 0;
    temp_r3->unk2C = 0;
    temp_r3->unk10 = 0;
    temp_r3->unk70 = -1;
    temp_r3->unk30 = -1;
    temp_r3->unk32 = -1;
    temp_r3->unk00 = HuPrcChildCreate(fn_1_4B0, 100, 0x4000, 0, lbl_1_bss_4);
    temp_r3->unk00->user_data = temp_r3;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    return temp_r3;
}

void fn_1_43C(UnkM447Struct_00* arg0) {
    fn_1_1830(arg0);
    fn_1_1E70(lbl_1_bss_10);
    fn_1_32E0();
    HuPrcKill(arg0->unk00);
    HuMemDirectFree(arg0);
}

BOOL fn_1_490(UnkM447Struct_00* arg0) {
    return arg0->unk08 == 0;
}

void fn_1_4A0(UnkM447Struct_00* arg0, s32 arg1) {
    arg0->unk14 = arg1;
    arg0->unk1C = 0;
}

void (*lbl_1_data_1C[])(UnkM447Struct_00*) = {
	fn_1_544,
	fn_1_7A8,
	fn_1_B5C,
	fn_1_F34,
	fn_1_1068
};

void fn_1_4B0(void) {
    UnkM447Struct_00* temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    while (omSysExitReq == 0 || !fn_1_490(temp_r31)) {
        lbl_1_data_1C[temp_r31->unk14](temp_r31);
        HuPrcVSleep();
    }
    omSysExitReq = 1;
    temp_r31->unk08 = 1;
    HuPrcEnd();
}

const Vec lbl_1_rodata_B0[2] = {
    {   0.0f, 300.0f, 0.0f },
    { -0.12f, 176.0f, 0.0f }
};

void fn_1_544(UnkM447Struct_00* arg0) {
    s32 i;

    switch (arg0->unk1C) {
        case 0:
            arg0->unk20 = 0;
            arg0->unk1C = 1;
            break;
        case 1:
            WipeStatGet();
            arg0->unk1C = 2;
            break;
        case 2:
            if (arg0->unk20++ >= 60) {
                arg0->unk1C = 3;
            }
            break;
        case 3:
            fn_1_1EB0(lbl_1_bss_10, 1);
            arg0->unk20 = 0;
            arg0->unk1C = 4;
            break;
        case 4:
            if (!fn_1_1EC0(lbl_1_bss_10)) {
                arg0->unk1C = 5;
            }
            break;
        case 5:
            if (lbl_1_bss_98[1]->unk18 == 8) {
                arg0->unk70 = HuAudSeqPlay(0x3D);
            }
            fn_1_3484(860.0f, 60);
            fn_1_330C(&lbl_1_rodata_B0[1], 60);
            arg0->unk20 = 0;
            arg0->unk1C = 6;
            break;
        case 6:
            if (arg0->unk20++ >= 60) {
                if (lbl_1_bss_98[1]->unk18 == 8) {
                    arg0->unk1C = 7;
                } else {
                    arg0->unk1C = 9;
                }
            }
            break;
        case 7:
            arg0->unk04 = HuPrcChildCreate(fn_1_1484, 100, 0x2000, 0, lbl_1_bss_4);
            arg0->unk04->user_data = arg0;
            arg0->unk0C = 1;
            arg0->unk1C = 8;
            break;
        case 8:
            if (arg0->unk0C != 0) {
                break;
            }
            arg0->unk04 = NULL;
            arg0->unk1C = 9;
            /* fallthrough */
        case 9:
            if (arg0->unk70 != -1) {
                HuAudSeqFadeOut(arg0->unk70, 1000);
            }
            fn_1_3484(1150.0f, 60);
            fn_1_330C(&lbl_1_rodata_B0[0], 60);
            for (i = 0; i < 2; i++) {
                fn_1_43CC(lbl_1_bss_98[i], 6);
            }
            fn_1_4A0(arg0, 1);
            break;
    }
}

void fn_1_7A8(UnkM447Struct_00* arg0) {
    Vec sp14;
    Vec sp8;
    s32 temp_r29;
    s32 temp_r28;
    s32 i;

    switch (arg0->unk1C) {
        case 0:
            arg0->unk1C = 1;
            /* fallthrough */
        case 1:
            fn_1_1EB0(lbl_1_bss_10, 3);
            arg0->unk20 = 0;
            arg0->unk1C = 2;
            /* fallthrough */
        case 2:
            if (arg0->unk20++ < 110) {
                break;
            }
            arg0->unk1C = 3;
            /* fallthrough */
        case 3:
            fn_1_90FC(fn_1_A240() % 10 > 5);
            temp_r29 = arg0->unk2C * 2 + fn_1_A240() % 2;
            temp_r28 = fn_1_A240() % 5;
            for (i = 0; i < 5; i++) {
                fn_1_9004(lbl_1_bss_A4[i], temp_r29, temp_r28 == i);
                fn_1_1ED4(i, &sp8);
                lbl_1_bss_A4[i]->unk10 = sp8;
                sp14.x = fn_1_A240() % 360;
                sp14.y = 0.0f;
                sp14.z = fn_1_A240() % 360;
                lbl_1_bss_A4[i]->unk1C = sp14;
                fn_1_8FF4(lbl_1_bss_A4[i], 1);
            }
            arg0->unk20 = 0;
            arg0->unk1C = 4;
            /* fallthrough */
        case 4:
            if (arg0->unk20++ < 60) {
                break;
            }
            for (i = 0; i < 5; i++) {
                fn_1_8FF4(lbl_1_bss_A4[i], 2);
            }
            /* fallthrough */
            arg0->unk1C = 5;
        case 5:
            fn_1_1EB0(lbl_1_bss_10, 4);
            arg0->unk20 = 0;
            arg0->unk1C = 6;
            /* fallthrough */
        case 6:
            if (!fn_1_1EC0(lbl_1_bss_10)) {
                if (arg0->unk10 != 0) {
                    arg0->unk1C = 9;
                } else {
                    arg0->unk1C = 7;
                }
            }
            break;
        case 7:
            arg0->unk70 = HuAudSeqPlay(0x3E);
            arg0->unk30 = MGSeqStartCreate();
            arg0->unk1C = 8;
            /* fallthrough */
        case 8:
            if (MGSeqStatGet(arg0->unk30) != 0) {
                break;
            }
            arg0->unk10 = 1;
            arg0->unk1C = 9;
            /* fallthrough */
        case 9:
            fn_1_4A0(arg0, 2);
            break;
    }
}

void fn_1_B5C(UnkM447Struct_00* arg0) {
    s32 temp_r26;
    s32 var_r27;
    s32 i;

    switch (arg0->unk1C) {
        case 0:
            fn_1_1884(arg0);
            arg0->unk24 = 900;
            arg0->unk32 = MGSeqCreate(1, arg0->unk24 / 60, -1, -1);
            for (i = 0; i < 2; i++) {
                fn_1_43CC(lbl_1_bss_98[i], 1);
                lbl_1_bss_98[i]->unk04 = 1;
            }
            arg0->unk1C = 1;
            /* fallthrough */
        case 1:
            temp_r26 = fn_1_1F9C(lbl_1_bss_10);
            if (arg0->unk24 > 0 && temp_r26 > 0 && --arg0->unk24 % 60 == 0) {
                MGSeqParamSet(arg0->unk32, 1, arg0->unk24 / 60);
            }
            if (arg0->unk24 > 0 && temp_r26 > 0) {
                break;
            }
            arg0->unk1C = 2;
            /* fallthrough */
        case 2:
            for (i = 0; i < 2; i++) {
                lbl_1_bss_98[i]->unk04 = 0;
                fn_1_7A6C(lbl_1_bss_98[i]);
            }
            arg0->unk1C = 3;
            break;
        case 3:
            if (arg0->unk32 != -1) {
                MGSeqParamSet(arg0->unk32, 2, -1);
                arg0->unk32 = -1;
            }
            for (i = 0; i < 2; i++) {
                if (lbl_1_bss_98[i]->unk24 != 1 && lbl_1_bss_98[i]->unk24 != 0) {
                    return;
                }
            }
            for (i = 0; i < 5; i++) {
                if (lbl_1_bss_A4[i]->unk04 != 0 && lbl_1_bss_A4[i]->unk04 != 2) {
                    return;
                }
            }
            arg0->unk1C = 4;
            /* fallthrough */
        case 4:
            for (i = 0; i < 2; i++) {
                if (lbl_1_bss_98[i]->unk14 != 0) {
                    fn_1_1AFC(arg0, i, lbl_1_bss_98[i]->unk1B - 1);
                }
            }
            arg0->unk2C++;
            for (i = 0, var_r27 = 0; i < 2; i++) {
                if (lbl_1_bss_98[i]->unk1B > var_r27) {
                    var_r27 = lbl_1_bss_98[i]->unk1B;
                }
            }
            if (var_r27 >= 3 || arg0->unk2C >= 5) {
                fn_1_4A0(lbl_1_bss_8, 4);
            } else {
                fn_1_4A0(lbl_1_bss_8, 3);
            }
            break;
    }
}

void fn_1_F34(UnkM447Struct_00* arg0) {
    s32 i;

    switch (arg0->unk1C) {
        case 0:
            for (i = 0; i < 2; i++) {
                fn_1_43CC(lbl_1_bss_98[i], 6);
            }
            arg0->unk1C = 1;
            /* fallthrough */
        case 1:
            for (i = 0; i < 5; i++) {
                if (lbl_1_bss_A4[i]->unk04 != 0) {
                    fn_1_8FF4(lbl_1_bss_A4[i], 4);
                }
            }
            arg0->unk20 = 0;
            arg0->unk1C = 2;
            /* fallthrough */
        case 2:
            if (arg0->unk20++ < 160) {
                break;
            }
            arg0->unk1C = 3;
            /* fallthrough */
        case 3:
            fn_1_4A0(lbl_1_bss_8, 1);
            break;
    }
}

const Vec lbl_1_rodata_D8 = { 0.0f, 150.0f, 0.0f };
const Vec lbl_1_rodata_E4 = { 6.0f,   0.0f, 0.0f };

void fn_1_1068(UnkM447Struct_00* arg0) {
    s32 temp_r29;
    s32 temp_r28;
    s32 i;

    switch (arg0->unk1C) {
        case 0:
            for (i = 0; i < 5; i++) {
                if (lbl_1_bss_A4[i]->unk04 != 0) {
                    fn_1_8FF4(lbl_1_bss_A4[i], 4);
                }
            }
            arg0->unk1C = 1;
            /* fallthrough */
        case 1:
            // Bug: HuAudSeqFadeOut takes two arguments.
#ifdef TARGET_PC
            // TODO PC
            HuAudSeqFadeOut(arg0->unk70, 100);
#else
            HuAudSeqFadeOut(arg0->unk70);
#endif
            arg0->unk30 = MGSeqCreate(3, 1);
            arg0->unk1C = 2;
            /* fallthrough */
        case 2:
            if (MGSeqStatGet(arg0->unk30) != 0) {
                break;
            }
            arg0->unk1C = 3;
            /* fallthrough */
        case 3:
            for (i = 0; i < 2; i++) {
                fn_1_43CC(lbl_1_bss_98[i], 7);
            }
            fn_1_330C(&lbl_1_rodata_D8, 180);
            fn_1_3484(300.0f, 180);
            fn_1_33C8(&lbl_1_rodata_E4, 180);
            arg0->unk20 = 0;
            arg0->unk1C = 4;
            /* fallthrough */
        case 4:
            if (arg0->unk20++ < 180) {
                break;
            }
            arg0->unk1C = 5;
            /* fallthrough */
        case 5:
            temp_r29 = lbl_1_bss_98[0]->unk1B;
            temp_r28 = lbl_1_bss_98[1]->unk1B;
            if (lbl_1_bss_98[1]->unk18 != 8 && temp_r29 == temp_r28) {
                fn_1_43CC(lbl_1_bss_98[0], 10);
                fn_1_43CC(lbl_1_bss_98[1], 10);
                HuAudSStreamPlay(4);
            } else if (temp_r29 > temp_r28) {
                fn_1_43CC(lbl_1_bss_98[0], 9);
                fn_1_43CC(lbl_1_bss_98[1], 10);
                GWPlayerCoinWinAdd(0, 10);
                HuAudSStreamPlay(1);
            } else {
                fn_1_43CC(lbl_1_bss_98[0], 10);
                fn_1_43CC(lbl_1_bss_98[1], 9);
                GWPlayerCoinWinAdd(1, 10);
                if (lbl_1_bss_98[1]->unk18 == 8) {
                    HuAudSStreamPlay(3);
                } else {
                    HuAudSStreamPlay(1);
                }
            }
            arg0->unk20 = 0;
            arg0->unk1C = 6;
            /* fallthrough */
        case 6:
            if (arg0->unk20++ < 210) {
                break;
            }
            arg0->unk1C = 7;
            /* fallthrough */
        case 7:
            omSysExitReq = 1;
            arg0->unk08 = 1;
            break;
    }
}

void fn_1_1394(UnkM447Struct_00* arg0, s16 arg1, s32 arg2) {
    HuWinComKeyReset();
    if (arg0->unk18 == 2) {
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, arg2);
    }
    winData[arg1].active_pad = 1;
    HuWinMesWait(arg1);
}

s32 fn_1_141C(UnkM447Struct_00* arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->unk18 == 2) {
        HuPrcSleep(arg4);
        return arg3;
    }
    return HuWinChoiceGet(arg1, arg2);
}

const s32 lbl_1_rodata_F4[] = {
    MAKE_MESSID(42, 3),
    MAKE_MESSID(42, 4),
    MAKE_MESSID(42, 5),
    MAKE_MESSID(42, 6),
    MAKE_MESSID(42, 7),
    0
};

void fn_1_1484(void) {
    UnkM447Struct_00* temp_r30;
    s16 temp_r3;
    s16 var_r29;
    s32 var_r28;
    u32 temp_r26;

    temp_r30 = HuPrcCurrentGet()->user_data;
    temp_r3 = HuWinExCreateStyled(-10000.0f, 40.0f, 280, 120, -1, 1);
    HuWinExAnimIn(temp_r3);
    HuWinBGTPLvlSet(temp_r3, 0.8f);
    HuWinMesSpeedSet(temp_r3, 1);
    HuWinMesColSet(temp_r3, 0);
    HuWinMesSet(temp_r3, MAKE_MESSID(42, 1));
    fn_1_1394(temp_r30, temp_r3, 60);
    if (temp_r30->unk18 < 2) {
        HuWinMesColSet(temp_r3, 0);
        HuWinMesSet(temp_r3, MAKE_MESSID(42, 2));
        var_r29 = fn_1_141C(temp_r30, temp_r3, 0, 1, 60);
    } else {
        var_r29 = 1;
    }
    if (var_r29 == 0) {
        var_r28 = 0;
        while ((temp_r26 = lbl_1_rodata_F4[var_r28++]) != 0) {
            HuWinMesColSet(temp_r3, 0);
            HuWinMesSet(temp_r3, temp_r26);
            fn_1_1394(temp_r30, temp_r3, 60);
        }
        HuWinMesColSet(temp_r3, 0);
        HuWinMesSet(temp_r3, MAKE_MESSID(42, 8));
        fn_1_1394(temp_r30, temp_r3, 60);
    } else {
        HuWinMesColSet(temp_r3, 0);
        HuWinMesSet(temp_r3, MAKE_MESSID(42, 9));
        fn_1_1394(temp_r30, temp_r3, 60);
    }
    HuWinExAnimOut(temp_r3);
    HuWinExCleanup(temp_r3);
    temp_r30->unk0C = 0;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_1754(UnkM447Struct_00* arg0) {
    s32 i;

    for (i = 0; i < 25; i++) {
        arg0->unk34[i] = espEntry(lbl_1_rodata_10[i], 0, 0);
        espDispOff(arg0->unk34[i]);
        espPriSet(arg0->unk34[i], 100);
    }
    espPriSet(arg0->unk34[7], 99);
    espPriSet(arg0->unk34[8], 99);
    espPriSet(arg0->unk34[9], 99);
    espPriSet(arg0->unk34[13], 99);
    espPriSet(arg0->unk34[14], 99);
    espPriSet(arg0->unk34[15], 99);
}

void fn_1_1830(UnkM447Struct_00* arg0) {
    s32 i;

    for (i = 0; i < 25; i++) {
        espKill(arg0->unk34[i]);
    }
}

void fn_1_1884(UnkM447Struct_00* arg0) {
    s16 temp_r28;
    s32 sp8;
    s32 i;
    s32 j;

    espDispOn(arg0->unk34[0]);
    espPosSet(arg0->unk34[0], 96.0f, 64.0f);
    espDispOn(arg0->unk34[2]);
    espPosSet(arg0->unk34[2], 96.0f, 63.0f);
    espTPLvlSet(arg0->unk34[2], 0.5f);
    espColorSet(arg0->unk34[2], 0, 0, 0);
    espDispOn(arg0->unk34[1]);
    espPosSet(arg0->unk34[1], 480.0f, 64.0f);
    espDispOn(arg0->unk34[3]);
    espPosSet(arg0->unk34[3], 480.0f, 63.0f);
    espTPLvlSet(arg0->unk34[3], 0.5f);
    espColorSet(arg0->unk34[3], 0, 0, 0);
    for (i = 0; i < 2; i++) {
        temp_r28 = lbl_1_bss_98[i]->unk18 + 16;
        espDispOn(arg0->unk34[temp_r28]);
        espPosSet(arg0->unk34[temp_r28], i * 384 + 46, 63.0f);
    }
    for (j = 0; j < 2; j++) {
        sp8 = lbl_1_bss_98[j]->unk1B;
        for (i = 0; i < 3; i++) {
            temp_r28 = i + 4 + j * 6;
            espDispOn(arg0->unk34[temp_r28]);
            espPosSet(arg0->unk34[temp_r28], j * 384 + 80 + i * 32, 63.0f);
        }
    }
}

void fn_1_1AFC(UnkM447Struct_00* arg0, s32 arg1, s32 arg2) {
    UnkM447Struct_03* temp_r3;
    Process* var_r30;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r3), MEMORY_DEFAULT_NUM);
    temp_r3->unk00 = arg0->unk34[arg2 + 7 + arg1 * 6];
    espPosSet(temp_r3->unk00, arg1 * 384 + 80 + arg2 * 32, 63.0f);
    temp_r3->unk04 = 0.0f;
    temp_r3->unk08 = 0.05f;
    var_r30 = HuPrcChildCreate(fn_1_1BF8, 100, 0x1000, 0, lbl_1_bss_4);
    var_r30->user_data = temp_r3;
}

void fn_1_1BF8(void) {
    float temp_f31;
    UnkM447Struct_03* temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    espDispOn(temp_r31->unk00);
    while (TRUE) {
        if ((temp_r31->unk04 += temp_r31->unk08) > 1.0f) {
            temp_r31->unk04 = 1.0f;
            break;
        }
        temp_f31 = 1.0f + 1.5f * (1.0f - temp_r31->unk04);
        espScaleSet(temp_r31->unk00, temp_f31, temp_f31);
        HuPrcVSleep();
    }
    espScaleSet(temp_r31->unk00, 1.0f, 1.0f);
    HuAudFXPlay(9);
    HuMemDirectFree(temp_r31);
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_1CE0(UnkM447Struct_00* arg0) {
    s32 i;

    for (i = 0; i <= 25; i++) {
        espDispOff(arg0->unk34[i]);
    }
}

void fn_1_1D34(UnkM447Struct_00* arg0) {
    s32 i;

    arg0->unk18 = 0;
    for (i = 0; i < 2; i++) {
        if (lbl_1_bss_98[i]->unk08 != 0) {
            arg0->unk18++;
        }
    }
}
