#include "REL/mstoryDll.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/board/main.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

extern s32 rand8(void);

typedef struct {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ char unk18[0x1C];
    /* 0x034 */ StructFn352C unk34[4];
    /* 0x104 */ float unk104;
} StructBss450; // Size 0x108

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ char unk0C[4];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} StructBss2D0; // Size 0x18

void fn_1_C360(void);
void fn_1_C7C4(void);
void fn_1_CE48(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_CEF4(omObjData* arg0, StructBss19C* arg1);
void fn_1_D180(void);
void fn_1_D57C(s32 arg0);
void fn_1_DAA4(omObjData* arg0, StructBss19C* arg1);
void fn_1_DC08(omObjData* arg0, StructBss19C* arg1);
void fn_1_DD20(omObjData* arg0, StructBss19C* arg1);
void fn_1_DE04(void);
void fn_1_E228(void);
void fn_1_E2B4(void);
void fn_1_E3E4(void);
void fn_1_E620(void);

StructBss450 lbl_1_bss_450;
StructBss19C lbl_1_bss_428;
StructBss19C lbl_1_bss_400;
StructBss19C lbl_1_bss_3D8;
StructBss19C lbl_1_bss_338[4];
AnimData* lbl_1_bss_330[2];
StructBss2D0 lbl_1_bss_2D0[4];
s32 lbl_1_bss_2CC;
Process* lbl_1_bss_2C8;

s32 lbl_1_data_388[][4] = {
    { MAKE_MESSID(30, 28), MAKE_MESSID(30, 33), MAKE_MESSID(30, 34), MAKE_MESSID(30, 5) },
    { MAKE_MESSID(30, 29), MAKE_MESSID(30, 33), MAKE_MESSID(30, 34), MAKE_MESSID(30, 5) },
    { MAKE_MESSID(30, 30), MAKE_MESSID(30, 33), MAKE_MESSID(30, 34), MAKE_MESSID(30, 5) },
    { MAKE_MESSID(30, 31), MAKE_MESSID(30, 33), MAKE_MESSID(30, 34), MAKE_MESSID(30, 5) },
    { MAKE_MESSID(30, 32), MAKE_MESSID(30, 33), MAKE_MESSID(30, 34), MAKE_MESSID(30, 5) }
};

s32 lbl_1_data_3D8[] = {
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
    DATADIR_WALUIGIMDL1
};

void fn_1_A830(void) {
    s32 temp_r3;

    temp_r3 = HuDataDirReadAsync(DATADIR_BOARD);
    if (temp_r3 != -1) {
        while (HuDataGetAsyncStat(temp_r3) == 0) {
            HuPrcVSleep();
        }
    }
    HuAR_MRAMtoARAM(DATADIR_BOARD);
    while (HuARDMACheck()) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATADIR_BOARD);
    temp_r3 = HuDataDirReadAsync(lbl_1_data_3D8[GWSystem.board]);
    if (temp_r3 != -1) {
        while (HuDataGetAsyncStat(temp_r3) == 0) {
            HuPrcVSleep();
        }
    }
    lbl_1_bss_2CC = 1;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_A8F8(void) {
    s32 i;
    s32 j;

    lbl_1_bss_2D0[0].unk00 = 0;
    lbl_1_bss_2D0[0].unk04 = 0;
    lbl_1_bss_2D0[0].unk10 = lbl_1_bss_450.unk34[lbl_1_bss_450.unk04].unk10;
    lbl_1_bss_2D0[0].unk14 = lbl_1_bss_450.unk34[lbl_1_bss_450.unk04].unk14;
    lbl_1_bss_2D0[0].unk08 = 0;
    for (i = 1; i < 4; i++) {
        lbl_1_bss_2D0[i].unk10 = -1;
        lbl_1_bss_2D0[i].unk14 = i;
        lbl_1_bss_2D0[i].unk08 = 1;
    }
    for (i = 1; i < 4; i++) {
        do {
            lbl_1_bss_2D0[i].unk10 = rand8() % 8;
            for (j = 0; j < 4; j++) {
                if (i != j && lbl_1_bss_2D0[j].unk10 != -1 && lbl_1_bss_2D0[i].unk10 == lbl_1_bss_2D0[j].unk10) {
                    break;
                }
            }
        } while (j != 4);
    }
    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].character = lbl_1_bss_2D0[i].unk10;
        GWPlayerCfg[i].pad_idx = lbl_1_bss_2D0[i].unk14;
        GWPlayerCfg[i].group = 0;
        GWPlayerCfg[i].iscom = lbl_1_bss_2D0[i].unk08;
    }
    BoardSaveInit(GWSystem.board);
    CharKill(-1);
    HuDataDirClose(DATADIR_MSTORY);
    HuPrcChildCreate(fn_1_A830, 100, 0x3000, 0, lbl_1_bss_2C8);
}

void fn_1_ABAC(void) {
    omOvlHisData* var_r30;
    s32 sp8[] = { OVL_W01, OVL_W02, OVL_W03, OVL_W04, OVL_W05, OVL_W06, OVL_W10 };

    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        fn_1_B8C();
    }
    CharModelKill(-1);
    MGSeqKillAll();
    var_r30 = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MSTORY3, 0, var_r30->stat);
    do {
        fn_1_B8C();
    } while (lbl_1_bss_2CC != 1);
    CharARAMOpen(GWPlayerCfg[0].character);
    CharARAMOpen(GWPlayerCfg[1].character);
    CharARAMOpen(GWPlayerCfg[2].character);
    CharARAMOpen(GWPlayerCfg[3].character);
    HuAudSeqAllFadeOut(1000);
    HuAudSStreamAllFadeOut(1000);
    omOvlCallEx(sp8[GWSystem.board], 1, 0, 0);
    while (TRUE) {
        fn_1_B8C();
    }
}

void fn_1_ACFC(Process* arg0, s32 arg1, s32 arg2) {
    s32 i;

    lbl_1_bss_2C8 = arg0;
    lbl_1_bss_450.unk04 = arg2;
    lbl_1_bss_450.unk10 = arg2;
    lbl_1_bss_450.unk00 = arg1;
    fn_1_BF4();
    fn_1_3618(0xFF);
    fn_1_27E8(lbl_1_bss_2C8, fn_1_E228);
    fn_1_3704();
    fn_1_D57C(arg2);
    HuPrcChildCreate(fn_1_C7C4, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_D180, 100, 0x2000, 0, HuPrcCurrentGet());
    for (i = 0; i < 4; i++) {
        HuPrcChildCreate(fn_1_DE04, 100, 0x2000, 0, HuPrcCurrentGet());
    }
    HuPrcChildCreate(fn_1_C360, 100, 0x2000, 0, HuPrcCurrentGet());
}

void fn_1_AE30(omObjData* arg0) {
    if (arg0->work[2] != 0) {
        arg0->work[2]--;
        return;
    }
    if (arg0->work[2] == 0 && Hu3DMotionEndCheck(arg0->model[1])) {
        fn_1_1DCC(arg0, 1, arg0->work[1], 15, 1);
        arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
    }
}

void fn_1_AEBC(void) {
    s32 var_r30 = 16;
    s32 var_r29 = 40;
    GXColor sp10 = { 0x00, 0x00, 0x80, 0x80 };
    s32 i;

    while (TRUE) {
        fn_1_B8C();
        printWin(var_r30, var_r29, 220, 160, &sp10);
        if (lbl_1_bss_428.unk04 == NULL) {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> FALSE");
        } else {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> TRUE");
        }
        if (lbl_1_bss_400.unk04 == NULL) {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP     -> FALSE");
        } else {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP     -> TRUE");
        }
        if (lbl_1_bss_3D8.unk04 == NULL) {
            print8(var_r30, var_r29 + 30, 1.0f, "PROC_MKOOPA  -> FALSE");
        } else {
            print8(var_r30, var_r29 + 30, 1.0f, "PROC_MKOOPA  -> TRUE");
        }
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_338[i].unk04 == NULL) {
                print8(var_r30, i * 10 + (var_r29 + 40), 1.0f, "PROC_PLAYER%d -> FALSE", i);
            } else {
                print8(var_r30, i * 10 + (var_r29 + 40), 1.0f, "PROC_PLAYER%d -> TRUE", i);
            }
        }
        print8(var_r30, var_r29 + 90, 1.0f, "P:%d W:%d", lbl_1_bss_450.unk04, lbl_1_bss_450.unk10);
        print8(var_r30, var_r29 + 110, 1.0f, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(var_r30, var_r29 + 120 + i * 10, 1.0f, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i,
                lbl_1_bss_450.unk34[i].unk00, lbl_1_bss_450.unk34[i].unk04, lbl_1_bss_450.unk34[i].unk08,
                lbl_1_bss_450.unk34[i].unk0C, lbl_1_bss_450.unk34[i].unk14, lbl_1_bss_450.unk34[i].unk10);
        }
    }
}

void fn_1_B230(void) {
    lbl_1_bss_58[0] = HuAudSeqPlay(0x34);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    fn_1_BAC(60);
}

void fn_1_B28C(void) {
    s32 i;

    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_450.unk00][1]);
    lbl_1_bss_450.unk08 = fn_1_1834(0, 0, 21, 2, lbl_1_bss_450.unk10);
    fn_1_CE48(3, -1, 15, 1, 0);
    fn_1_1CE8(lbl_1_bss_450.unk08, lbl_1_data_388[lbl_1_bss_450.unk00][0]);
    fn_1_1ACC(lbl_1_bss_450.unk08, -1);
    fn_1_1CE8(lbl_1_bss_450.unk08, MAKE_MESSID(37, 4));
    fn_1_CE48(1, -1, 15, 1, 0);
    fn_1_1A64(lbl_1_bss_450.unk08);
    for (i = 0; i < 4; i++) {
        lbl_1_bss_338[i].unk04 = (void*) fn_1_DAA4;
    }
    do {
        fn_1_B8C();
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_338[i].unk04 != NULL) {
                break;
            }
        }
    } while (i != 4);
    lbl_1_bss_338[lbl_1_bss_450.unk04].unk04 = (void*) fn_1_DC08;
    fn_1_3804(&lbl_1_bss_4);
    fn_1_2710(fn_1_E2B4);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_338[lbl_1_bss_450.unk04].unk04 == NULL) {
            break;
        }
    }
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_3D8.unk04 == NULL) {
            break;
        }
    }
    fn_1_BAC(30);
}

BOOL fn_1_B4A0(void) {
    BOOL temp_r31 = FALSE;

    fn_1_1CE8(lbl_1_bss_450.unk08, lbl_1_data_388[lbl_1_bss_450.unk00][1]);
    fn_1_1ACC(lbl_1_bss_450.unk08, 5);
    lbl_1_bss_450.unk0C = fn_1_6EB8(MAKE_MESSID(30, 53), lbl_1_bss_450.unk10);
    fn_1_1CE8(lbl_1_bss_450.unk0C, MAKE_MESSID(30, 53));
    temp_r31 = fn_1_1C34(lbl_1_bss_450.unk0C);
    fn_1_1CE8(lbl_1_bss_450.unk0C, MAKE_MESSID(37, 4));
    fn_1_7028(lbl_1_bss_450.unk0C);
    return temp_r31;
}

BOOL fn_1_B588(void) {
    BOOL temp_r31 = FALSE;

    fn_1_1CE8(lbl_1_bss_450.unk08, lbl_1_data_388[lbl_1_bss_450.unk00][2]);
    fn_1_1ACC(lbl_1_bss_450.unk08, 5);
    lbl_1_bss_450.unk0C = fn_1_6EB8(MAKE_MESSID(30, 53), lbl_1_bss_450.unk10);
    fn_1_1CE8(lbl_1_bss_450.unk0C, MAKE_MESSID(30, 53));
    temp_r31 = fn_1_1C34(lbl_1_bss_450.unk0C);
    fn_1_1CE8(lbl_1_bss_450.unk0C, MAKE_MESSID(37, 4));
    fn_1_7028(lbl_1_bss_450.unk0C);
    return temp_r31;
}

BOOL fn_1_B670(void) {
    BOOL temp_r31 = FALSE;

    fn_1_CE48(3, -1, 15, 1, 0);
    fn_1_1CE8(lbl_1_bss_450.unk08, lbl_1_data_388[lbl_1_bss_450.unk00][3]);
    fn_1_1ACC(lbl_1_bss_450.unk08, 5);
    fn_1_CE48(1, -1, 15, 1, 0);
    lbl_1_bss_450.unk0C = fn_1_6EB8(MAKE_MESSID(30, 53), lbl_1_bss_450.unk10);
    fn_1_1CE8(lbl_1_bss_450.unk0C, MAKE_MESSID(30, 53));
    temp_r31 = fn_1_1B78(lbl_1_bss_450.unk0C, 1);
    fn_1_1CE8(lbl_1_bss_450.unk0C, MAKE_MESSID(37, 4));
    fn_1_7028(lbl_1_bss_450.unk0C);
    return temp_r31;
}

void fn_1_B78C(void) {
    fn_1_BAC(60);
    fn_1_A8F8();
    Hu3DModelAttrReset(lbl_1_bss_400.unk00->model[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_400.unk00->model[6], HU3D_ATTR_DISPOFF);
    fn_1_1DCC(lbl_1_bss_400.unk00, 2, 3, 0, 0);
    fn_1_BAC(30);
    fn_1_1DCC(lbl_1_bss_3D8.unk00, 1, 4, 15, 0);
    fn_1_BAC(30);
    fn_1_1DCC(lbl_1_bss_338[lbl_1_bss_450.unk04].unk00, 1, 3, 15, 0);
    fn_1_2224(lbl_1_bss_400.unk00, 2, 3, 0);
    fn_1_BAC(60);
    HuAudSeqFadeOut(lbl_1_bss_58[0], 3000);
    fn_1_3804(&lbl_1_bss_4);
    fn_1_2710(fn_1_E3E4);
    fn_1_BAC(150);
}

void fn_1_B8C8(void) {
}

void fn_1_B8CC(void) {
    fn_1_1DCC(lbl_1_bss_400.unk00, 2, 3, 0, 0);
    fn_1_2224(lbl_1_bss_400.unk00, 2, 3, 0);
    fn_1_3804(&lbl_1_bss_4);
    fn_1_2710(fn_1_E620);
    lbl_1_bss_3D8.unk04 = (void*) fn_1_CEF4;
    lbl_1_bss_338[lbl_1_bss_450.unk04].unk04 = (void*) fn_1_DD20;
    do {
        fn_1_B8C();
    } while (lbl_1_bss_3D8.unk04 != NULL);
    fn_1_1DCC(lbl_1_bss_400.unk00, 2, 2, 0, 0);
    fn_1_2224(lbl_1_bss_400.unk00, 2, 2, 0);
}

void fn_1_B9D0(s32 arg0) {
    s32 i;

    fn_1_BAC(60);
    HuAudSeqFadeOut(lbl_1_bss_58[0], 1000);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (TRUE) {
        fn_1_B8C();
        if (WipeStatGet() == 0) {
            break;
        }
    }
    CharModelKill(-1);
    HuAudFadeOut(1);
    if (arg0 == 1) {
        omOvlReturnEx(1, 1);
    } else {
        GWPlayerCfg->group = 0;
        GWPlayerCfg->character = lbl_1_bss_450.unk34[lbl_1_bss_450.unk04].unk10;
        GWPlayerCfg->pad_idx = lbl_1_bss_450.unk34[lbl_1_bss_450.unk04].unk14;
        GWPlayerCfg->iscom = 0;
        for (i = 0; i < 4; i++) {
            GWPlayer[i].character = GWPlayerCfg[i].character;
            GWPlayer[i].port = GWPlayerCfg[i].pad_idx;
            GWPlayer[i].com = GWPlayerCfg[i].iscom;
            GWPlayer[i].team = GWPlayerCfg[i].group;
        }
        omOvlGotoEx(OVL_MENT, 1, 10, 0);
    }
    while (TRUE) {
        fn_1_B8C();
    }
}

void fn_1_BBD8(s32 arg0, StructBss19C* arg1) {
    s32 i;
    s32 var_r30 = 0;

    fn_1_B230();
    fn_1_B28C();
    lbl_1_bss_450.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_450.unk10);
    while (TRUE) {
        fn_1_B8C();
        if (fn_1_B4A0()) {
            var_r30 = 0;
            break;
        }
        if (fn_1_B588()) {
            var_r30 = 2;
            break;
        }
        if (fn_1_B670()) {
            var_r30 = 1;
            break;
        }
    }
    fn_1_1A64(lbl_1_bss_450.unk08);
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_450.unk34[i].unk00 != lbl_1_bss_450.unk34[lbl_1_bss_450.unk04].unk00) {
            Hu3DModelAttrSet(lbl_1_bss_338[i].unk00->model[1], HU3D_ATTR_DISPOFF);
        }
        Hu3DModelAttrSet(lbl_1_bss_338[i].unk00->model[2], HU3D_ATTR_DISPOFF);
    }
    switch (var_r30) {
        case 1:
            fn_1_B8C8();
            break;
        case 0:
            fn_1_B78C();
            break;
        case 2:
            fn_1_B8CC();
            break;
    }
    switch (var_r30) {
        case 0:
            fn_1_ABAC();
            break;
        case 1:
        case 2:
            fn_1_B9D0(var_r30);
            /* fallthrough */
        default:
            arg1->unk04 = 0;
            break;
    }
}

void fn_1_C360(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_2C8, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_428.unk00 = temp_r3;
    lbl_1_bss_428.unk04 = (void*) fn_1_BBD8;
    lbl_1_bss_428.unk00->data = &lbl_1_bss_428;
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_428.unk04 != NULL) {
            lbl_1_bss_428.unk04(temp_r3, &lbl_1_bss_428);
        }
    }
}

void fn_1_C414(omObjData* arg0, s32 arg1) {
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 56));
    arg0->motion[0] = Hu3DMotionIDGet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 0, 0, 2);
    Hu3DModelShadowMapObjSet(arg0->model[1], "base_fix9-base");
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 59));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY, 60));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY, 61));
    fn_1_1DCC(arg0, 2, 2, 0, 2);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 57));
    arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 63));
    arg0->motion[5] = Hu3DMotionIDGet(arg0->model[5]);
    Hu3DModelPosSet(arg0->model[5], 0.0f, 80.0f, 460.0f);
    Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(arg0->model[5]);
    fn_1_1DCC(arg0, 5, 5, 0, 2);
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 64));
    arg0->motion[6] = Hu3DMotionIDGet(arg0->model[6]);
    Hu3DModelHookSet(arg0->model[5], "partybox_fix2-effect_fook1", arg0->model[6]);
    Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF);
    fn_1_1DCC(arg0, 6, 6, 0, 2);
    lbl_1_bss_330[0] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY, 65 + arg1 * 2), MEMORY_DEFAULT_NUM));
    lbl_1_bss_330[1] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY, 66 + arg1 * 2), MEMORY_DEFAULT_NUM));
    Hu3DAnimCreate(lbl_1_bss_330[0], lbl_1_bss_400.unk00->model[5], "ys26_p0");
    Hu3DAnimCreate(lbl_1_bss_330[1], lbl_1_bss_400.unk00->model[5], "ys26_p1");
}

void fn_1_C708(omObjData* arg0, StructBss19C* arg1) {
    Hu3DData[arg0->model[5]].pos.y = fn_1_ACC(80.0f, 90.0f, arg1->unk08++, 360.0f);
    if (arg1->unk08 >= 360) {
        arg1->unk08 = 0;
    }
}

void fn_1_C7C4(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_2C8, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_400.unk00 = temp_r3;
    lbl_1_bss_400.unk04 = (void*) fn_1_C708;
    lbl_1_bss_400.unk00->data = &lbl_1_bss_400;
    fn_1_C414(temp_r3, lbl_1_bss_450.unk00);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_400.unk04 != NULL) {
            lbl_1_bss_400.unk04(temp_r3, &lbl_1_bss_400);
        }
    }
}

void fn_1_CB48(omObjData* arg0, s32 arg1) {
    s32 sp1C[] = {
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x61),
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x6C),
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x74),
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x7C),
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x83)
    };
    s32 sp30[][5] = {
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x62), DATA_MAKE_NUM(DATADIR_MSTORY, 0x64), DATA_MAKE_NUM(DATADIR_MSTORY, 0x65), DATA_MAKE_NUM(DATADIR_MSTORY, 0x67), DATA_MAKE_NUM(DATADIR_MSTORY, 0x68) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x6D), DATA_MAKE_NUM(DATADIR_MSTORY, 0x6F), DATA_MAKE_NUM(DATADIR_MSTORY, 0x70), DATA_MAKE_NUM(DATADIR_MSTORY, 0x72), DATA_MAKE_NUM(DATADIR_MSTORY, 0x73) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x75), DATA_MAKE_NUM(DATADIR_MSTORY, 0x77), DATA_MAKE_NUM(DATADIR_MSTORY, 0x78), DATA_MAKE_NUM(DATADIR_MSTORY, 0x7A), DATA_MAKE_NUM(DATADIR_MSTORY, 0x7B) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x7D), DATA_MAKE_NUM(DATADIR_MSTORY, 0x7E), DATA_MAKE_NUM(DATADIR_MSTORY, 0x7F), DATA_MAKE_NUM(DATADIR_MSTORY, 0x81), DATA_MAKE_NUM(DATADIR_MSTORY, 0x82) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x84), DATA_MAKE_NUM(DATADIR_MSTORY, 0x86), DATA_MAKE_NUM(DATADIR_MSTORY, 0x87), DATA_MAKE_NUM(DATADIR_MSTORY, 0x89), DATA_MAKE_NUM(DATADIR_MSTORY, 0x8A) }
    };

    arg0->model[1] = Hu3DModelCreateFile(sp1C[arg1]);
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][0]);
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][1]);
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][2]);
    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][3]);
    arg0->motion[5] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][4]);
    Hu3DModelPosSet(arg0->model[1], -300.0f, 0.0f, 890.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, 30.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    if (arg1 == 3) {
        Hu3DData[arg0->model[1]].pos.y = 50.0f;
    }
    Hu3DModelShadowSet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 1, 0, 1);
    {
        s32 sp8[] = { 9, 14, 10, 11, 12 };

        if (arg1 != 3) {
            CharModelEffectNpcInit(arg0->model[1], arg0->motion[2], 1, sp8[arg1]);
        }
    }
}

void fn_1_CE48(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fn_1_1DCC(lbl_1_bss_3D8.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_3D8.unk00->work[0] = arg4;
    lbl_1_bss_3D8.unk00->work[1] = arg1;
    lbl_1_bss_3D8.unk00->work[2] = arg2 + 1;
}

void fn_1_CEF4(omObjData* arg0, StructBss19C* arg1) {
    Vec sp14 = { 0.0f, 0.0f, 460.0f };

    fn_1_1DCC(arg0, 1, 2, 15, 1);
    fn_1_2CB0(arg0, 1, sp14, 0.0f, 60.0f, 10.0f);
    fn_1_1DCC(arg0, 1, 1, 15, 1);
    arg1->unk04 = 0;
}

void fn_1_CFD8(omObjData* arg0, StructBss19C* arg1) {
    s32 i;

    for (i = 0; i < 15; i++) {
        fn_1_B8C();
        Hu3DData[arg0->model[1]].rot.y = fn_1_828(0.0f, 135.0f, i, 15.0f);
    }
    arg1->unk04 = 0;
}

void fn_1_D09C(omObjData* arg0, StructBss19C* arg1) {
    Vec sp14 = { -120.0f, 0.0f, 670.0f };

    fn_1_1DCC(arg0, 1, 2, 15, 1);
    fn_1_2CB0(arg0, 1, sp14, 45.0f, 60.0f, 10.0f);
    fn_1_1DCC(arg0, 1, 1, 15, 1);
    arg1->unk04 = 0;
}

void fn_1_D180(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_2C8, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_3D8.unk00 = temp_r3;
    lbl_1_bss_3D8.unk04 = NULL;
    lbl_1_bss_3D8.unk00->data = &lbl_1_bss_3D8;
    fn_1_CB48(temp_r3, lbl_1_bss_450.unk00);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_3D8.unk04 != NULL) {
            lbl_1_bss_3D8.unk04(temp_r3, &lbl_1_bss_3D8);
        }
        if (temp_r3->work[0] != 0) {
            fn_1_AE30(temp_r3);
        }
    }
}

void fn_1_D57C(s32 arg0) {
    s32 spC[4];
    s32 i;

    spC[0] = 0;
    for (i = 1; i < 4; i++) {
        spC[i] = spC[i - 1] + 1;
        if (spC[i] >= 4) {
            spC[i] = 0;
        }
        if (arg0 == spC[i]) {
            lbl_1_bss_450.unk04 = i;
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_352C(&lbl_1_bss_450.unk34[i], spC[i]);
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_450.unk34[i].unk18 = GWPlayer[spC[i]].rank + 1;
    }
}

Vec lbl_1_data_540[] = {
    { -300.0f,   0.0f, 460.0f },
    { -100.0f, -30.0f, 460.0f },
    {  100.0f, -60.0f, 460.0f },
    {  300.0f, -90.0f, 460.0f }
};

void fn_1_D6B0(omObjData* arg0, s32 arg1) {
    s32 var_r30;
    s32 temp_r28;

    var_r30 = arg1;
    temp_r28 = lbl_1_bss_450.unk34[var_r30].unk10;
    arg0->model[1] = CharModelCreate(lbl_1_bss_450.unk34[arg1].unk10, 4);
    arg0->motion[1] = CharModelMotionCreate(lbl_1_bss_450.unk34[arg1].unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
    arg0->motion[2] = CharModelMotionCreate(lbl_1_bss_450.unk34[arg1].unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 3));
    arg0->motion[3] = CharModelMotionCreate(lbl_1_bss_450.unk34[arg1].unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 109));
    CharModelMotionDataClose(temp_r28);
    Hu3DModelPosSet(arg0->model[1], lbl_1_data_540[var_r30].x, 90.0f + lbl_1_data_540[lbl_1_bss_450.unk34[var_r30].unk18 - 1].y, lbl_1_data_540[var_r30].z - 15.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelShadowSet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 1, 0, 1);
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 62));
    Hu3DModelPosSet(arg0->model[2], lbl_1_data_540[var_r30].x, lbl_1_data_540[lbl_1_bss_450.unk34[var_r30].unk18 - 1].y, lbl_1_data_540[var_r30].z);
    if (lbl_1_bss_450.unk34[var_r30].unk18 == 4) {
        Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelScaleSet(arg0->model[2], 1.5f, 1.0f, 1.5f);
    Hu3DModelShadowMapSet(arg0->model[2]);
}

void fn_1_D9A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fn_1_1DCC(lbl_1_bss_338[lbl_1_bss_450.unk04].unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_338[lbl_1_bss_450.unk04].unk00->work[0] = arg4;
    lbl_1_bss_338[lbl_1_bss_450.unk04].unk00->work[1] = arg1;
    lbl_1_bss_338[lbl_1_bss_450.unk04].unk00->work[2] = arg2 + 1;
}

void fn_1_DAA4(omObjData* arg0, StructBss19C* arg1) {
    float temp_f31;
    s32 i;

    temp_f31 = Hu3DData[arg0->model[1]].pos.y;
    for (i = 0; i < 60; i++) {
        fn_1_B8C();
        Hu3DData[arg0->model[1]].pos.y = fn_1_948(temp_f31, 0.0f, i, 60.0f);
        Hu3DData[arg0->model[2]].pos.y = fn_1_948(temp_f31 - 90.0f, -90.0f, i, 60.0f);
    }
    Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
    arg1->unk04 = 0;
}

void fn_1_DC08(omObjData* arg0, StructBss19C* arg1) {
    Vec sp14 = { 120.0f, 0.0f, 670.0f };

    lbl_1_bss_3D8.unk04 = (void*) fn_1_D09C;
    fn_1_1DCC(lbl_1_bss_400.unk00, 2, 2, 0, 0);
    fn_1_1DCC(arg0, 1, 2, 15, 1);
    fn_1_2CB0(arg0, 1, sp14, -45.0f, 30.0f, 10.0f);
    fn_1_1DCC(arg0, 1, 1, 15, 1);
    arg1->unk04 = 0;
}

void fn_1_DD20(omObjData* arg0, StructBss19C* arg1) {
    Vec sp14 = { 600.0f, 0.0f, 700.0f };

    fn_1_1DCC(arg0, 1, 2, 15, 1);
    fn_1_2CB0(arg0, 1, sp14, -45.0f, 30.0f, 10.0f);
    fn_1_1DCC(arg0, 1, 1, 15, 1);
    arg1->unk04 = 0;
}

void fn_1_DE04(void) {
    omObjData* temp_r3;
    s32 temp_r30;

    temp_r30 = lbl_1_bss_450.unk14++;
    temp_r3 = omAddObjEx(lbl_1_bss_2C8, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_338[temp_r30].unk00 = temp_r3;
    lbl_1_bss_338[temp_r30].unk04 = NULL;
    lbl_1_bss_338[temp_r30].unk00->data = lbl_1_bss_338;
    fn_1_D6B0(temp_r3, temp_r30);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_338[temp_r30].unk04 != NULL) {
            lbl_1_bss_338[temp_r30].unk04(temp_r3, &lbl_1_bss_338[temp_r30]);
        }
        if (temp_r3->work[0] != 0) {
            fn_1_AE30(temp_r3);
        }
    }
}

void fn_1_E228(void) {
    StructBss4* var_r31;

    var_r31 = &lbl_1_bss_4;
    var_r31->unk08.x = 0.0f;
    var_r31->unk08.y = 170.0f;
    var_r31->unk08.z = 0.0f;
    var_r31->unk20.x = -5.0f;
    var_r31->unk20.y = 0.0f;
    var_r31->unk20.z = 0.0f;
    var_r31->unk38 = 1700.0f;
}

void fn_1_E2B4(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = 0.0f;
    sp8.unk08.y = 125.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = -5.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1750.0f;
    fn_1_51D0(var_r31, &sp8, var_r31->unk40++, 60.0f, 30.0f);
    if (lbl_1_bss_450.unk104 != 0.0f) {
        var_r31->unk08.y = 125.0f + lbl_1_bss_450.unk104;
    }
}

void fn_1_E3E4(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    if (var_r31->unk40 == 50) {
        fn_1_1DCC(lbl_1_bss_400.unk00, 5, 5, 0, 0);
        fn_1_1DCC(lbl_1_bss_400.unk00, 6, 6, 0, 0);
        HuAudFXPlay(0xA1);
    }
    sp8.unk08.x = 0.0f;
    sp8.unk08.y = 100.0f;
    sp8.unk08.z = 460.0f;
    sp8.unk20.x = 0.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 125.0f;
    fn_1_51D0(var_r31, &sp8, var_r31->unk40, 180.0f, 10.0f);
    if (var_r31->unk40++ >= 90) {
        if (var_r31->unk40 == 91) {
            lbl_1_bss_68 = HuAudFXPlay(0x21);
        }
        var_r31->unk20.x = fn_1_828(var_r31->unk20.x, -45.0f, var_r31->unk40 - 90, 90.0f);
        Hu3DData[lbl_1_bss_400.unk00->model[5]].rot.x = fn_1_828(0.0f, 45.0f, var_r31->unk40 - 90, 90.0f);
    }
}

void fn_1_E620(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = 0.0f;
    sp8.unk08.y = 220.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = 0.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1600.0f;
    fn_1_51D0(var_r31, &sp8, var_r31->unk40++, 60.0f, 30.0f);
}
