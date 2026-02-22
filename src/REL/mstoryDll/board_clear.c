#include "REL/mstoryDll.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/printfunc.h"

#ifndef __MWERKS__
#include "game/audio.h"
#include "game/minigame_seq.h"
#endif

#include "game/window.h"
#include "game/wipe.h"

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ char unk0C[4];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ char unk18[0x1C];
    /* 0x34 */ StructFn352C unk34[4];
} StructBss1C4; // Size 0x104

void fn_1_8A44(void);
void fn_1_8DC0(omObjData* arg0, StructBss19C* arg1);
void fn_1_8E6C(omObjData* arg0, StructBss19C* arg1);
void fn_1_8F68(void);
void fn_1_92D4(s32 arg0);
void fn_1_9718(omObjData* arg0, StructBss19C* arg1);
void fn_1_98A4(omObjData* arg0, StructBss19C* arg1);
void fn_1_992C(void);
void fn_1_A008(omObjData* arg0, StructBss19C* arg1);
void fn_1_A0EC(void);
void fn_1_A478(void);
void fn_1_A504(void);
void fn_1_A5F4(void);

StructBss1C4 lbl_1_bss_1C4;
StructBss19C lbl_1_bss_19C;
StructBss19C lbl_1_bss_174;
StructBss19C lbl_1_bss_D4[4];
StructBss19C lbl_1_bss_AC;
Process* lbl_1_bss_A8;

s32 lbl_1_data_190[][4] = {
    { MAKE_MESSID(30, 17), MAKE_MESSID(30, 23), MAKE_MESSID(30, 62), MAKE_MESSID(30, 63) },
    { MAKE_MESSID(30, 18), MAKE_MESSID(30, 24), MAKE_MESSID(30, 64), MAKE_MESSID(30, 65) },
    { MAKE_MESSID(30, 19), MAKE_MESSID(30, 25), MAKE_MESSID(30, 66), MAKE_MESSID(30, 67) },
    { MAKE_MESSID(30, 20), MAKE_MESSID(30, 26), MAKE_MESSID(30, 68), MAKE_MESSID(30, 69) },
    { MAKE_MESSID(30, 21), MAKE_MESSID(30, 27), MAKE_MESSID(30, 70), MAKE_MESSID(30, 71) }
};

s32 lbl_1_data_1E0[][3] = {
    { MAKE_MESSID(30, 101), MAKE_MESSID(30, 102), MAKE_MESSID(30, 103) },
    { MAKE_MESSID(30, 104), MAKE_MESSID(30, 105), MAKE_MESSID(30, 106) },
    { MAKE_MESSID(30, 107), MAKE_MESSID(30, 108), MAKE_MESSID(30, 109) },
    { MAKE_MESSID(30, 110), MAKE_MESSID(30, 111), MAKE_MESSID(30, 112) },
    { MAKE_MESSID(30, 113), MAKE_MESSID(30, 114), MAKE_MESSID(30, 115) }
};

void fn_1_7090(s32 arg0, StructBss19C* arg1) {
    fn_1_BAC(10);
    fn_1_1DCC(lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk00, 1, 5, 15, 0);
    fn_1_BAC(5);
    HuAudCharVoicePlay(lbl_1_bss_1C4.unk34[lbl_1_bss_1C4.unk04].unk10, 0x128);
    fn_1_BAC(25);
    arg1->unk04 = 0;
}

void fn_1_7134(s32 arg0, StructBss19C* arg1) {
    float temp_f31;
    float temp_f30;
    float temp_f29;
    s32 i;

    temp_f29 = Hu3DData[lbl_1_bss_174.unk00->model[7]].pos.y;
    for (i = 0; i <= 30; i++) {
        fn_1_B8C();
        temp_f31 = fn_1_870(temp_f29, 1000.0f, i, 30.0f);
        temp_f30 = fn_1_870(0.0f, 1800.0f, i, 30.0f);
        Hu3DModelPosSet(lbl_1_bss_174.unk00->model[7], 0.0f, temp_f31, 800.0f);
        Hu3DModelRotSet(lbl_1_bss_174.unk00->model[7], 0.0f, temp_f30, 0.0f);
        Hu3DModelPosSet(lbl_1_bss_174.unk00->model[8], 0.0f, temp_f31 + 15.0f, 775.0f);
    }
    arg1->unk04 = 0;
}

void fn_1_731C(s32 arg0) {
    float temp_f31;
    float temp_f30;
    s32 var_r30;
    s32 i;

    var_r30 = arg0;
    Hu3DModelAttrReset(lbl_1_bss_174.unk00->model[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_174.unk00->model[6], HU3D_ATTR_DISPOFF);
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_1C4.unk34[i].unk00 != lbl_1_bss_1C4.unk34[lbl_1_bss_1C4.unk04].unk00) {
            Hu3DModelAttrSet(lbl_1_bss_D4[i].unk00->model[1], HU3D_ATTR_DISPOFF);
        }
        Hu3DModelAttrSet(lbl_1_bss_D4[i].unk00->model[2], HU3D_ATTR_DISPOFF);
    }
    lbl_1_bss_1C4.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_1C4.unk10);
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 3, 15, 1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, lbl_1_data_1E0[var_r30][0]);
    fn_1_1ACC(lbl_1_bss_1C4.unk08, -1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, MAKE_MESSID(37, 4));
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 1, 15, 1);
    fn_1_1A64(lbl_1_bss_1C4.unk08);
    Hu3DModelPosSet(lbl_1_bss_174.unk00->model[7], 0.0f, 1000.0f, 640.0f);
    Hu3DModelAttrReset(lbl_1_bss_174.unk00->model[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_174.unk00->model[8], HU3D_ATTR_DISPOFF);
    for (i = 0; i <= 180; i++) {
        fn_1_B8C();
        temp_f31 = fn_1_948(1000.0f, 150.0f, i, 180.0f);
        temp_f30 = fn_1_948(1800.0f, 0.0f, i, 180.0f);
        Hu3DModelPosSet(lbl_1_bss_174.unk00->model[7], 0.0f, temp_f31, 800.0f);
        Hu3DModelRotSet(lbl_1_bss_174.unk00->model[7], 0.0f, temp_f30, 0.0f);
        Hu3DModelPosSet(lbl_1_bss_174.unk00->model[8], 0.0f, temp_f31 + 15.0f, 775.0f);
    }
    lbl_1_bss_174.unk04 = (void*) fn_1_8E6C;
    fn_1_1DCC(lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk00, 1, 6, 15, 0);
    lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk04 = (void*) fn_1_98A4;
    fn_1_BAC(40);
    HuAudSeqFadeOut(lbl_1_bss_58[0], 1000);
    fn_1_BAC(50);
    lbl_1_bss_58[1] = HuAudSeqPlay(0x35);
    lbl_1_bss_1C4.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_1C4.unk10);
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 3, 15, 1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, lbl_1_data_1E0[var_r30][1]);
    fn_1_1ACC(lbl_1_bss_1C4.unk08, -1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, MAKE_MESSID(37, 4));
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 1, 15, 1);
    fn_1_1A64(lbl_1_bss_1C4.unk08);
    fn_1_BAC(30);
    fn_1_1DCC(lbl_1_bss_174.unk00, 2, 3, 0, 0);
    lbl_1_bss_174.unk04 = (void*) fn_1_8DC0;
    fn_1_BAC(30);
    lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk04 = (void*) fn_1_7090;
    fn_1_BAC(90);
    lbl_1_bss_AC.unk04 = (void*) fn_1_7134;
    lbl_1_bss_1C4.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_1C4.unk10);
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 5, 15, 1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, lbl_1_data_1E0[lbl_1_bss_1C4.unk00][2]);
    fn_1_1ACC(lbl_1_bss_1C4.unk08, -1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, MAKE_MESSID(37, 4));
    fn_1_1A64(lbl_1_bss_1C4.unk08);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1C4.unk00][3]);
}

void fn_1_79B8(Process* arg0, s32 arg1, s32 arg2) {
    s32 i;

    lbl_1_bss_A8 = arg0;
    lbl_1_bss_1C4.unk00 = arg1;
    lbl_1_bss_1C4.unk10 = arg2;
    fn_1_BF4();
    fn_1_3618(0xFF);
    fn_1_27E8(lbl_1_bss_A8, fn_1_A478);
    fn_1_3704();
    fn_1_92D4(arg2);
    HuPrcChildCreate(fn_1_8F68, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_A0EC, 100, 0x2000, 0, HuPrcCurrentGet());
    for (i = 0; i < 4; i++) {
        HuPrcChildCreate(fn_1_992C, 100, 0x2000, 0, HuPrcCurrentGet());
    }
    HuPrcChildCreate(fn_1_8A44, 100, 0x2000, 0, HuPrcCurrentGet());
}

void fn_1_7AE0(void) {
    s32 var_r30 = 16;
    s32 var_r29 = 40;
    GXColor sp10 = { 0x00, 0x00, 0x80, 0x80 };
    s32 i;

    while (TRUE) {
        fn_1_B8C();
        fontcolor = FONT_COLOR_WHITE;
        printWin(var_r30, var_r29, 220, 150, &sp10);
        if (lbl_1_bss_19C.unk04 == NULL) {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> FALSE");
        } else {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> TRUE");
        }
        if (lbl_1_bss_174.unk04 == NULL) {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP     -> FALSE");
        } else {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP     -> TRUE");
        }
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_D4[i].unk04 == NULL) {
                print8(var_r30, i * 10 + (var_r29 + 20), 1.0f, "PROC_PLAYER%d -> FALSE", i);
            } else {
                print8(var_r30, i * 10 + (var_r29 + 20), 1.0f, "PROC_PLAYER%d -> TRUE", i);
            }
        }
        if (lbl_1_bss_AC.unk04 == NULL) {
            print8(var_r30, var_r29 + 60, 1.0f, "PROC_SUB     -> FALSE");
        } else {
            print8(var_r30, var_r29 + 60, 1.0f, "PROC_SUB     -> TRUE");
        }
        print8(var_r30, var_r29 + 80, 1.0f, "M:%d P:%d W:%d", lbl_1_bss_1C4.unk00, lbl_1_bss_1C4.unk04, lbl_1_bss_1C4.unk10);
        print8(var_r30, var_r29 + 100, 1.0f, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(var_r30, var_r29 + 110 + i * 10, 1.0f, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i,
                lbl_1_bss_1C4.unk34[i].unk00, lbl_1_bss_1C4.unk34[i].unk04, lbl_1_bss_1C4.unk34[i].unk08,
                lbl_1_bss_1C4.unk34[i].unk0C, lbl_1_bss_1C4.unk34[i].unk14, lbl_1_bss_1C4.unk34[i].unk10);
        }
    }
}

void fn_1_7E70(void) {
    lbl_1_bss_58[0] = HuAudSeqPlay(0x33);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    fn_1_BAC(60);
}

void fn_1_7ECC(void) {
    s32 spC = 0;
    s32 sp8 = 0;

    lbl_1_bss_1C4.unk08 = fn_1_1834(0, 0, 21, 2, lbl_1_bss_1C4.unk10);
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 3, 15, 1);
    fn_1_1D1C(lbl_1_bss_1C4.unk08, lbl_1_bss_1C4.unk34[lbl_1_bss_1C4.unk04].unk10, 0);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, lbl_1_data_190[lbl_1_bss_1C4.unk00][0]);
    fn_1_1ACC(lbl_1_bss_1C4.unk08, -1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, MAKE_MESSID(37, 4));
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 1, 15, 1);
    fn_1_1A64(lbl_1_bss_1C4.unk08);
    lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk04 = (void*) fn_1_9718;
    fn_1_3804(&lbl_1_bss_4);
    fn_1_2710(fn_1_A504);
    do {
        fn_1_B8C();
    } while (lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk04 != NULL);
    do {
        fn_1_B8C();
    } while (lbl_1_bss_AC.unk04 != NULL);
}

void fn_1_8090(void) {
    lbl_1_bss_1C4.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_1C4.unk10);
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 3, 15, 1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, lbl_1_data_190[lbl_1_bss_1C4.unk00][2]);
    fn_1_1ACC(lbl_1_bss_1C4.unk08, -1);
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 1, 15, 1);
    fn_1_1A64(lbl_1_bss_1C4.unk08);
    fn_1_1DCC(lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk00, 1, 6, 15, 0);
    lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk04 = (void*) fn_1_98A4;
    Hu3DModelAttrReset(lbl_1_bss_174.unk00->model[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_174.unk00->model[6], HU3D_ATTR_DISPOFF);
    fn_1_BAC(180);
    HuAudSeqFadeOut(lbl_1_bss_58[0], 1000);
    fn_1_1DCC(lbl_1_bss_174.unk00, 2, 3, 0, 0);
    fn_1_BAC(75);
    lbl_1_bss_58[1] = HuAudSeqPlay(0x35);
    lbl_1_bss_1C4.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_1C4.unk10);
    fn_1_1DCC(lbl_1_bss_AC.unk00, 1, 4, 15, 1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, lbl_1_data_190[lbl_1_bss_1C4.unk00][3]);
    lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk04 = NULL;
    lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk04 = (void*) fn_1_7090;
    fn_1_1ACC(lbl_1_bss_1C4.unk08, -1);
    fn_1_1CE8(lbl_1_bss_1C4.unk08, MAKE_MESSID(37, 4));
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1C4.unk00][3]);
    fn_1_1A64(lbl_1_bss_1C4.unk08);
    do {
        fn_1_B8C();
    } while (lbl_1_bss_D4[lbl_1_bss_1C4.unk04].unk04 != NULL);
}

void fn_1_83B0(void) {
    fn_1_BAC(60);
    HuAudSeqFadeOut(lbl_1_bss_58[1], 3000);
    fn_1_3804(&lbl_1_bss_4);
    fn_1_2710(fn_1_A5F4);
    fn_1_BAC(150);
}

void fn_1_8408(void) {
    omOvlHisData* var_r30;
    u16 sp8[] = { 53, 56, 55, 54, 57 };
    s32 sp14[] = { 9, 14, 10, 11, 12 };
    s32 var_r29;
    s32 var_r28;
    s32 i;

    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    CharModelKill(-1);
    MGSeqKillAll();
    var_r29 = lbl_1_bss_1C4.unk34[lbl_1_bss_1C4.unk04].unk10;
    var_r28 = lbl_1_bss_1C4.unk34[lbl_1_bss_1C4.unk04].unk14;
    GWPlayerCfg[lbl_1_bss_1C4.unk04].character = GWPlayerCfg->character;
    GWPlayerCfg[lbl_1_bss_1C4.unk04].pad_idx = GWPlayerCfg->pad_idx;
    GWPlayerCfg[lbl_1_bss_1C4.unk04].group = GWPlayerCfg->group;
    GWPlayerCfg[lbl_1_bss_1C4.unk04].iscom = GWPlayerCfg->iscom;
    GWPlayerCfg->character = var_r29;
    GWPlayerCfg->pad_idx = var_r28;
    GWPlayerCfg->group = 0;
    GWPlayerCfg->iscom = 0;
    for (i = 0; i < 4; i++) {
        GWPlayer[i].character = GWPlayerCfg[i].character;
        GWPlayer[i].port = GWPlayerCfg[i].pad_idx;
        GWPlayer[i].com = GWPlayerCfg[i].iscom;
        GWPlayer[i].team = GWPlayerCfg[i].group;
    }
    GWPlayerCfg[1].character = sp14[GWSystem.board];
    for (i = 1; i < 4; i++) {
        GWPlayerCfg[i].iscom = GWPlayerCfg[i].group = 1;
    }
    var_r30 = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MSTORY, 2, var_r30->stat);
    OSReport("########## dllno - %d\n", sp8[GWSystem.board], GWSystem.board);
    HuAudSeqAllFadeOut(1000);
    HuAudSStreamAllFadeOut(1000);
    omOvlCallEx(sp8[GWSystem.board], 1, 0, 0);
    while (TRUE) {
        fn_1_B8C();
    }
}

void fn_1_87DC(s32 arg0, StructBss19C* arg1) {
    fn_1_7E70();
    fn_1_7ECC();
    fn_1_731C(lbl_1_bss_1C4.unk00);
    fn_1_83B0();
    fn_1_8408();
    arg1->unk04 = NULL;
}

void fn_1_8A44(void) {
    omObjData* var_r31;

    var_r31 = omAddObjEx(lbl_1_bss_A8, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_19C.unk00 = var_r31;
    lbl_1_bss_19C.unk04 = (void*) fn_1_87DC;
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_19C.unk04 != NULL) {
            lbl_1_bss_19C.unk04(var_r31, &lbl_1_bss_19C);
        }
    }
}

void fn_1_8AE0(omObjData* arg0) {
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 56));
    arg0->motion[0] = Hu3DMotionIDGet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 0, 0, 2);
    Hu3DModelShadowMapObjSet(arg0->model[1], "base_fix9-base");
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 59));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY, 60));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY, 61));
    fn_1_1DCC(arg0, 2, 2, 0, 2);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 57));
    arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 76 + lbl_1_bss_1C4.unk00));
    arg0->motion[5] = Hu3DMotionIDGet(arg0->model[5]);
    Hu3DModelPosSet(arg0->model[5], 0.0f, 80.0f, 460.0f);
    Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(arg0->model[5]);
    fn_1_1DCC(arg0, 5, 5, 0, 2);
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 75));
    arg0->motion[6] = Hu3DMotionIDGet(arg0->model[6]);
    Hu3DModelHookSet(arg0->model[5], "stargbox_fix-effect_fook1", arg0->model[6]);
    Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF);
    fn_1_1DCC(arg0, 6, 6, 0, 2);
    arg0->model[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 81));
    Hu3DModelAttrSet(arg0->model[7], HU3D_ATTR_DISPOFF);
    arg0->model[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 96));
    arg0->motion[8] = Hu3DMotionIDGet(arg0->model[8]);
    Hu3DModelAttrSet(arg0->model[8], HU3D_ATTR_DISPOFF);
    fn_1_1DCC(arg0, 8, 8, 0, 1);
}

void fn_1_8DC0(omObjData* arg0, StructBss19C* arg1) {
    Hu3DData[arg0->model[5]].pos.y = fn_1_ACC(80.0f, 90.0f, arg0->work[0]++, 360.0f);
    if (arg0->work[0] >= 360) {
        arg0->work[0] = 0;
    }
}

void fn_1_8E6C(omObjData* arg0, StructBss19C* arg1) {
    Hu3DData[arg0->model[7]].pos.y += fn_1_ACC(0.0f, 0.25f, arg0->work[0]++, 360.0f);
    Hu3DData[arg0->model[8]].pos.y = Hu3DData[arg0->model[7]].pos.y + 15.0f;
    if (arg0->work[0] >= 360) {
        arg0->work[0] = 0;
    }
}

void fn_1_8F68(void) {
    omObjData* temp_r31;

    temp_r31 = omAddObjEx(lbl_1_bss_A8, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_174.unk00 = temp_r31;
    lbl_1_bss_174.unk04 = (void*) fn_1_8DC0;
    lbl_1_bss_174.unk00->data = &lbl_1_bss_174;
    fn_1_8AE0(temp_r31);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_174.unk04 != NULL) {
            lbl_1_bss_174.unk04(temp_r31, &lbl_1_bss_174);
        }
    }
}

void fn_1_92D4(s32 arg0) {
    s32 spC[4];
    s32 i;

    spC[0] = 0;
    for (i = 1; i < 4; i++) {
        spC[i] = spC[i - 1] + 1;
        if (spC[i] >= 4) {
            spC[i] = 0;
        }
        if (arg0 == spC[i]) {
            lbl_1_bss_1C4.unk04 = i;
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_352C(&lbl_1_bss_1C4.unk34[i], spC[i]);
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_1C4.unk34[i].unk18 = GWPlayer[spC[i]].rank + 1;
    }
}

Vec lbl_1_data_354[] = {
    { -300.0f,   0.0f, 460.0f },
    { -100.0f, -30.0f, 460.0f },
    {  100.0f, -60.0f, 460.0f },
    {  300.0f, -90.0f, 460.0f }
};

void fn_1_9408(omObjData* arg0, s32 arg1) {
    s32 var_r30;
    s32 temp_r29;

    var_r30 = arg1;
    temp_r29 = lbl_1_bss_1C4.unk34[var_r30].unk10;
    arg0->model[1] = CharModelCreate(temp_r29, 4);
    arg0->motion[1] = CharModelMotionCreate(temp_r29, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
    arg0->motion[2] = CharModelMotionCreate(temp_r29, DATA_MAKE_NUM(DATADIR_MARIOMOT, 3));
    arg0->motion[3] = CharModelMotionCreate(temp_r29, DATA_MAKE_NUM(DATADIR_MARIOMOT, 5));
    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_MSTORY, 48 + temp_r29));
    arg0->motion[5] = CharModelMotionCreate(temp_r29, DATA_MAKE_NUM(DATADIR_MARIOMOT, 109));
    arg0->motion[6] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_MSTORY, 40 + temp_r29));
    CharModelMotionDataClose(temp_r29);
    Hu3DModelPosSet(arg0->model[1], lbl_1_data_354[var_r30].x, lbl_1_data_354[lbl_1_bss_1C4.unk34[var_r30].unk18 - 1].y + 90.0f, lbl_1_data_354[var_r30].z - 15.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelShadowSet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 1, 0, 1);
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 62));
    Hu3DModelPosSet(arg0->model[2], lbl_1_data_354[var_r30].x, lbl_1_data_354[lbl_1_bss_1C4.unk34[var_r30].unk18 - 1].y, lbl_1_data_354[var_r30].z);
    if (lbl_1_bss_1C4.unk34[var_r30].unk18 == 4) {
        Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelShadowMapSet(arg0->model[2]);
    Hu3DModelScaleSet(arg0->model[2], 1.5f, 1.0f, 1.5f);
}

void fn_1_9718(omObjData* arg0, StructBss19C* arg1) {
    Vec sp20 = { 120.0f, 0.0f, 670.0f };

    fn_1_2908(arg0, 1, sp20, -1.0f, 30.0f, 10.0f);
    lbl_1_bss_AC.unk04 = (void*) fn_1_A008;
    fn_1_1DCC(lbl_1_bss_174.unk00, 2, 2, 0, 0);
    fn_1_1DCC(arg0, 1, 2, 15, 1);
    fn_1_2CB0(arg0, 1, sp20, -45.0f, 30.0f, 10.0f);
    fn_1_1DCC(arg0, 1, 1, 15, 1);
    fn_1_2224(lbl_1_bss_174.unk00, 2, 2, 0);
    arg1->unk04 = 0;
}

void fn_1_98A4(omObjData* arg0, StructBss19C* arg1) {
    if (arg0->motion[6] == Hu3DMotionIDGet(arg0->model[1]) && Hu3DMotionEndCheck(arg0->model[1])) {
        fn_1_1DCC(arg0, 1, 4, 15, 1);
        arg1->unk04 = 0;
    }
}

void fn_1_992C(void) {
    omObjData* temp_r3;
    s32 temp_r30;

    temp_r30 = lbl_1_bss_1C4.unk14++;
    temp_r3 = omAddObjEx(lbl_1_bss_A8, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_D4[temp_r30].unk00 = temp_r3;
    lbl_1_bss_D4[temp_r30].unk04 = NULL;
    lbl_1_bss_D4[temp_r30].unk00->data = &lbl_1_bss_D4[temp_r30];
    fn_1_9408(temp_r3, temp_r30);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_D4[temp_r30].unk04 != NULL) {
            lbl_1_bss_D4[temp_r30].unk04(temp_r3, &lbl_1_bss_D4[temp_r30]);
        }
    }
}

void fn_1_9D08(omObjData* arg0, s32 arg1) {
    s32 sp1C[] = {
        DATA_MAKE_NUM(DATADIR_MSTORY, 97),
        DATA_MAKE_NUM(DATADIR_MSTORY, 108),
        DATA_MAKE_NUM(DATADIR_MSTORY, 116),
        DATA_MAKE_NUM(DATADIR_MSTORY, 124),
        DATA_MAKE_NUM(DATADIR_MSTORY, 131)
    };
    s32 sp30[][5] = {
        { DATA_MAKE_NUM(DATADIR_MSTORY, 98), DATA_MAKE_NUM(DATADIR_MSTORY, 100), DATA_MAKE_NUM(DATADIR_MSTORY, 101), DATA_MAKE_NUM(DATADIR_MSTORY, 103), DATA_MAKE_NUM(DATADIR_MSTORY, 104) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 109), DATA_MAKE_NUM(DATADIR_MSTORY, 111), DATA_MAKE_NUM(DATADIR_MSTORY, 112), DATA_MAKE_NUM(DATADIR_MSTORY, 114), DATA_MAKE_NUM(DATADIR_MSTORY, 115) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 117), DATA_MAKE_NUM(DATADIR_MSTORY, 119), DATA_MAKE_NUM(DATADIR_MSTORY, 120), DATA_MAKE_NUM(DATADIR_MSTORY, 122), DATA_MAKE_NUM(DATADIR_MSTORY, 123) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 125), DATA_MAKE_NUM(DATADIR_MSTORY, 126), DATA_MAKE_NUM(DATADIR_MSTORY, 127), DATA_MAKE_NUM(DATADIR_MSTORY, 129), DATA_MAKE_NUM(DATADIR_MSTORY, 130) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 132), DATA_MAKE_NUM(DATADIR_MSTORY, 134), DATA_MAKE_NUM(DATADIR_MSTORY, 135), DATA_MAKE_NUM(DATADIR_MSTORY, 137), DATA_MAKE_NUM(DATADIR_MSTORY, 138) }
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
    fn_1_1DCC(arg0, 1, 5, 0, 1);
    {
        s32 sp8[] = { 9, 14, 10, 11, 12 };

        if (arg1 != 3) {
            CharModelEffectNpcInit(arg0->model[1], arg0->motion[2], 1, sp8[arg1]);
        }
    }
}

void fn_1_A008(omObjData* arg0, StructBss19C* arg1) {
    Vec sp14 = { -120.0f, 0.0f, 670.0f };

    fn_1_1DCC(arg0, 1, 2, 15, 1);
    fn_1_2CB0(arg0, 1, sp14, 45.0f, 60.0f, 10.0f);
    fn_1_1DCC(arg0, 1, 1, 15, 1);
    arg1->unk04 = 0;
}

void fn_1_A0EC(void) {
    omObjData* temp_r3;
    s32 temp_r30;

    temp_r3 = omAddObjEx(lbl_1_bss_A8, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_AC.unk00 = temp_r3;
    lbl_1_bss_AC.unk04 = NULL;
    lbl_1_bss_AC.unk00->data = &lbl_1_bss_AC;
    temp_r30 = lbl_1_bss_1C4.unk00;
    fn_1_9D08(temp_r3, temp_r30);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_AC.unk04 != NULL) {
            lbl_1_bss_AC.unk04(temp_r3, &lbl_1_bss_AC);
        }
    }
}

void fn_1_A478(void) {
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

void fn_1_A504(void) {
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
}

void fn_1_A5F4(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    if (var_r31->unk40 == 50) {
        fn_1_1DCC(lbl_1_bss_174.unk00, 5, 5, 0, 0);
        fn_1_1DCC(lbl_1_bss_174.unk00, 6, 6, 0, 0);
        HuAudFXPlay(0xA1);
    }
    sp8.unk08.x = 0.0f;
    sp8.unk08.y = 130.0f;
    sp8.unk08.z = 460.0f;
    sp8.unk20.x = 0.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 150.0f;
    fn_1_51D0(var_r31, &sp8, var_r31->unk40, 180.0f, 10.0f);
    if (var_r31->unk40++ >= 90) {
        if (var_r31->unk40 == 91) {
            lbl_1_bss_68 = HuAudFXPlay(0x21);
        }
        var_r31->unk20.x = fn_1_828(var_r31->unk20.x, -45.0f, var_r31->unk40 - 90, 90.0f);
        Hu3DData[lbl_1_bss_174.unk00->model[5]].rot.x = fn_1_828(0.0f, 45.0f, var_r31->unk40 - 90, 90.0f);
    }
}
