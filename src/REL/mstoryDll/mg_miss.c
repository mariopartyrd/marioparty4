#include "REL/mstoryDll.h"
#include "game/chrman.h"

#ifndef __MWERKS__
#include "game/audio.h"
#endif

#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/printfunc.h"
#include "game/window.h"
#include "game/wipe.h"

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ char unk14[0x20];
    /* 0x34 */ StructFn352C unk34[4];
} StructBss7B4; // Size 0x104

void fn_1_12630(void);
void fn_1_129D4(void);
void fn_1_12C94(s32 arg0);
void fn_1_12F20(omObjData* arg0, StructBss19C* arg1);
void fn_1_12FA8(omObjData*, StructBss19C* arg1);
void fn_1_130C0(void);
void fn_1_13570(void);
void fn_1_13880(void);
void fn_1_1390C(void);

StructBss7B4 lbl_1_bss_7B4;
StructBss19C lbl_1_bss_78C;
StructBss19C lbl_1_bss_764;
StructBss19C lbl_1_bss_73C;
StructBss19C lbl_1_bss_714;
Process* lbl_1_bss_710;

s32 lbl_1_data_AF8[][3] = {
    { MAKE_MESSID(30, 40), MAKE_MESSID(30, 45), MAKE_MESSID(30, 5) },
    { MAKE_MESSID(30, 41), MAKE_MESSID(30, 45), MAKE_MESSID(30, 5) },
    { MAKE_MESSID(30, 42), MAKE_MESSID(30, 45), MAKE_MESSID(30, 5) },
    { MAKE_MESSID(30, 43), MAKE_MESSID(30, 45), MAKE_MESSID(30, 5) },
    { MAKE_MESSID(30, 44), MAKE_MESSID(30, 45), MAKE_MESSID(30, 5) }
};

void fn_1_11624(Process* arg0, s32 arg1, s32 arg2) {
    lbl_1_bss_710 = arg0;
    lbl_1_bss_7B4.unk00 = arg1;
    lbl_1_bss_7B4.unk10 = arg2;
    fn_1_BF4();
    fn_1_3618(0xFF);
    fn_1_27E8(lbl_1_bss_710, fn_1_13880);
    fn_1_3704();
    fn_1_12C94(arg2);
    HuPrcChildCreate(fn_1_129D4, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_130C0, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_13570, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_12630, 100, 0x2000, 0, HuPrcCurrentGet());
}

void fn_1_11730(void) {
    s32 var_r31 = 16;
    s32 var_r30 = 40;
    GXColor sp10 = { 0x00, 0x00, 0x80, 0x80 };
    s32 i;

    while (TRUE) {
        fn_1_B8C();
        fontcolor = FONT_COLOR_WHITE;
        printWin(var_r31, var_r30, 220, 120, &sp10);
        if (lbl_1_bss_78C.unk04 == NULL) {
            print8(var_r31, var_r30, 1.0f, "PROC_MAIN   -> FALSE");
        } else {
            print8(var_r31, var_r30, 1.0f, "PROC_MAIN   -> TRUE");
        }
        if (lbl_1_bss_764.unk04 == NULL) {
            print8(var_r31, var_r30 + 10, 1.0f, "PROC_MAP    -> FALSE");
        } else {
            print8(var_r31, var_r30 + 10, 1.0f, "PROC_MAP    -> TRUE");
        }
        if (lbl_1_bss_73C.unk04 == NULL) {
            print8(var_r31, var_r30 + 20, 1.0f, "PROC_PLAYER -> FALSE");
        } else {
            print8(var_r31, var_r30 + 20, 1.0f, "PROC_PLAYER -> TRUE");
        }
        if (lbl_1_bss_714.unk04 == NULL) {
            print8(var_r31, var_r30 + 30, 1.0f, "PROC_SUB    -> FALSE");
        } else {
            print8(var_r31, var_r30 + 30, 1.0f, "PROC_SUB    -> TRUE");
        }
        print8(var_r31, var_r30 + 50, 1.0f, "M:%d P:%d W:%d", lbl_1_bss_7B4.unk00, lbl_1_bss_7B4.unk04, lbl_1_bss_7B4.unk10);
        print8(var_r31, var_r30 + 70, 1.0f, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(var_r31, var_r30 + 80 + i * 10, 1.0f, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i,
                lbl_1_bss_7B4.unk34[i].unk00, lbl_1_bss_7B4.unk34[i].unk04, lbl_1_bss_7B4.unk34[i].unk08,
                lbl_1_bss_7B4.unk34[i].unk0C, lbl_1_bss_7B4.unk34[i].unk14, lbl_1_bss_7B4.unk34[i].unk10);
        }
    }
}

void fn_1_11A8C(void) {
    lbl_1_bss_58[0] = HuAudSeqPlay(0x34);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    fn_1_BAC(60);
}

void fn_1_11AE8(void) {
    s32 spC = 0;
    s32 sp8 = 0;

    fn_1_1DCC(lbl_1_bss_73C.unk00, 1, 2, 15, 0);
    lbl_1_bss_73C.unk04 = (void*) fn_1_12F20;
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_7B4.unk00][1]);
    HuAudCharVoicePlay(lbl_1_bss_7B4.unk34[lbl_1_bss_7B4.unk04].unk10, 0x12E);
    lbl_1_bss_7B4.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_7B4.unk10);
    fn_1_1DCC(lbl_1_bss_714.unk00, 1, 2, 15, 1);
    fn_1_1CE8(lbl_1_bss_7B4.unk08, lbl_1_data_AF8[lbl_1_bss_7B4.unk00][0]);
    fn_1_1ACC(lbl_1_bss_7B4.unk08, -1);
    fn_1_1CE8(lbl_1_bss_7B4.unk08, MAKE_MESSID(37, 4));
    fn_1_1DCC(lbl_1_bss_714.unk00, 1, 1, 15, 1);
    fn_1_1A64(lbl_1_bss_7B4.unk08);
}

BOOL fn_1_11C6C(void) {
    BOOL temp_r31 = FALSE;

    HuWinInsertMesSet(lbl_1_bss_7B4.unk08, MAKE_MESSID(30, 54) + lbl_1_bss_7B4.unk00, 3);
    fn_1_1CE8(lbl_1_bss_7B4.unk08, lbl_1_data_AF8[lbl_1_bss_7B4.unk00][1]);
    fn_1_1ACC(lbl_1_bss_7B4.unk08, 5);
    lbl_1_bss_7B4.unk0C = fn_1_6EB8(MAKE_MESSID(30, 53), lbl_1_bss_7B4.unk10);
    fn_1_1CE8(lbl_1_bss_7B4.unk0C, MAKE_MESSID(30, 53));
    temp_r31 = fn_1_1C34(lbl_1_bss_7B4.unk0C);
    fn_1_1CE8(lbl_1_bss_7B4.unk0C, MAKE_MESSID(37, 4));
    fn_1_7028(lbl_1_bss_7B4.unk0C);
    if (temp_r31) {
        fn_1_1DCC(lbl_1_bss_73C.unk00, 1, 4, 15, 0);
        lbl_1_bss_73C.unk04 = NULL;
        fn_1_1DCC(lbl_1_bss_714.unk00, 1, 3, 15, 1);
    }
    return temp_r31;
}

BOOL fn_1_11DD8(void) {
    s32 temp_r31 = FALSE;

    fn_1_1CE8(lbl_1_bss_7B4.unk08, lbl_1_data_AF8[lbl_1_bss_7B4.unk00][2]);
    fn_1_1ACC(lbl_1_bss_7B4.unk08, 5);
    lbl_1_bss_7B4.unk0C = fn_1_6EB8(MAKE_MESSID(30, 53), lbl_1_bss_7B4.unk10);
    fn_1_1CE8(lbl_1_bss_7B4.unk0C, MAKE_MESSID(30, 53));
    temp_r31 = fn_1_1B78(lbl_1_bss_7B4.unk0C, 1);
    fn_1_1CE8(lbl_1_bss_7B4.unk0C, MAKE_MESSID(37, 4));
    fn_1_7028(lbl_1_bss_7B4.unk0C);
    return temp_r31;
}

void fn_1_11EC4(void) {
    lbl_1_bss_73C.unk04 = (void*) fn_1_12FA8;
    HuAudSeqFadeOut(lbl_1_bss_58[0], 3000);
    fn_1_3804(&lbl_1_bss_4);
    fn_1_2710(fn_1_1390C);
    fn_1_BAC(150);
}

void fn_1_11F28(void) {
}

void fn_1_11F2C(s32 arg0) {
    omOvlHisData* var_r30;
    OverlayID sp8[] = { OVL_M445, OVL_M448, OVL_M447, OVL_M446, OVL_M449 };

    if (arg0 != 0) {
        fn_1_BAC(60);
        HuAudSeqFadeOut(lbl_1_bss_58[0], 1000);
    }
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    fn_1_BAC(60);
    CharModelKill(-1);
    var_r30 = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MSTORY, 2, var_r30->stat);
    if (arg0 == 0) {
        HuAudSeqAllFadeOut(1000);
        HuAudSStreamAllFadeOut(1000);
        omOvlCallEx(sp8[GWSystem.board], 1, 0, 0);
    } else {
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_12070(omObjData* arg0, StructBss19C* arg1) {
    s32 var_r31;

    fn_1_11A8C();
    fn_1_11AE8();
    lbl_1_bss_7B4.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_7B4.unk10);
    while (TRUE) {
        fn_1_B8C();
        if (fn_1_11C6C()) {
            var_r31 = 0;
            break;
        }
        if (fn_1_11DD8()) {
            var_r31 = 1;
            break;
        }
    }
    fn_1_1A64(lbl_1_bss_7B4.unk08);
    fn_1_BAC(60);
    switch (var_r31) {
        case 0:
            fn_1_11EC4();
            break;
        case 1:
            fn_1_11F28();
            break;
    }
    fn_1_11F2C(var_r31);
    arg1->unk04 = NULL;
}

void fn_1_12630(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_710, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_78C.unk00 = temp_r3;
    lbl_1_bss_78C.unk04 = (void*) fn_1_12070;
    lbl_1_bss_78C.unk00->data = &lbl_1_bss_78C;
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_78C.unk04 != NULL) {
            lbl_1_bss_78C.unk04(temp_r3, &lbl_1_bss_78C);
        }
    }
}

void fn_1_126E4(omObjData* arg0) {
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 56));
    arg0->motion[0] = Hu3DMotionIDGet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 0, 0, 2);
    Hu3DModelShadowMapObjSet(arg0->model[1], "base_fix9-base");
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 59));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY, 60));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY, 61));
    fn_1_1DCC(arg0, 2, 2, 0, 2);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 57));
    arg0->model[5] = Hu3DModelCreateFile(lbl_1_bss_7B4.unk00 + DATA_MAKE_NUM(DATADIR_MSTORY, 76));
    arg0->motion[5] = Hu3DMotionIDGet(arg0->model[5]);
    Hu3DModelPosSet(arg0->model[5], 0.0f, 80.0f, 460.0f);
    Hu3DModelShadowSet(arg0->model[5]);
    fn_1_1DCC(arg0, 5, 5, 0, 2);
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 75));
    arg0->motion[6] = Hu3DMotionIDGet(arg0->model[6]);
    Hu3DModelHookSet(arg0->model[5], "stargbox_fix-effect_fook1", arg0->model[6]);
    fn_1_1DCC(arg0, 6, 6, 0, 2);
}

void fn_1_12918(omObjData* arg0, StructBss19C* arg1) {
    Hu3DData[arg0->model[5]].pos.y = fn_1_ACC(80.0f, 90.0f, arg1->unk08++, 360.0f);
    if (arg1->unk08 >= 360) {
        arg1->unk08 = 0;
    }
}

void fn_1_129D4(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_710, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_764.unk00 = temp_r3;
    lbl_1_bss_764.unk04 = (void*) fn_1_12918;
    lbl_1_bss_764.unk00->data = &lbl_1_bss_764;
    fn_1_126E4(temp_r3);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_764.unk04 != NULL) {
            lbl_1_bss_764.unk04(temp_r3, &lbl_1_bss_764);
        }
    }
}

void fn_1_12C94(s32 arg0) {
    s32 spC[4];
    s32 i;

    spC[0] = 0;
    for (i = 1; i < 4; i++) {
        spC[i] = spC[i - 1] + 1;
        if (spC[i] >= 4) {
            spC[i] = 0;
        }
        if (arg0 == spC[i]) {
            lbl_1_bss_7B4.unk04 = i;
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_352C(&lbl_1_bss_7B4.unk34[i], spC[i]);
    }
}

void fn_1_12D78(omObjData* arg0) {
    s32 temp_r30;

    temp_r30 = lbl_1_bss_7B4.unk34[lbl_1_bss_7B4.unk04].unk10;
    arg0->model[1] = CharModelCreate(temp_r30, 1);
    arg0->motion[1] = CharModelMotionCreate(temp_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
    arg0->motion[2] = CharModelMotionCreate(temp_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 24));
    arg0->motion[3] = CharModelMotionCreate(temp_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 52));
    arg0->motion[4] = CharModelMotionCreate(temp_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 72));
    arg0->motion[5] = CharModelMotionCreate(temp_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 53));
    CharModelVoiceEnableSet(temp_r30, arg0->motion[2], 0);
    CharModelMotionDataClose(temp_r30);
    Hu3DModelPosSet(arg0->model[1], 120.0f, 0.0f, 670.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, -45.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelShadowSet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 1, 0, 1);
}

void fn_1_12F20(omObjData* arg0, StructBss19C* arg1) {
    if (arg0->motion[2] == Hu3DMotionIDGet(arg0->model[1]) && Hu3DMotionEndCheck(arg0->model[1])) {
        fn_1_1DCC(arg0, 1, 3, 15, 1);
        arg1->unk04 = 0;
    }
}

void fn_1_12FA8(omObjData* arg0, StructBss19C* arg1) {
    s32 i;

    fn_1_BAC(10);
    fn_1_1DCC(arg0, 1, 5, 15, 0);
    fn_1_B8C();
    Hu3DMotionTimeSet(arg0->model[1], 60.0f);
    for (i = 0; i < 50; i++) {
        fn_1_B8C();
        Hu3DData[arg0->model[1]].rot.y = fn_1_828(-60.0f, -120.0f, i, 60.0f);
    }
    fn_1_1DCC(arg0, 1, 1, 15, 1);
    arg1->unk04 = 0;
}

void fn_1_130C0(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_710, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_73C.unk00 = temp_r3;
    lbl_1_bss_73C.unk04 = NULL;
    lbl_1_bss_73C.unk00->data = &lbl_1_bss_73C;
    fn_1_12D78(temp_r3);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_73C.unk04 != NULL) {
            lbl_1_bss_73C.unk04(temp_r3, &lbl_1_bss_73C);
        }
    }
}

void fn_1_132EC(omObjData* arg0, s32 arg1) {
    s32 sp8[] = {
        DATA_MAKE_NUM(DATADIR_MSTORY, 97),
        DATA_MAKE_NUM(DATADIR_MSTORY, 108),
        DATA_MAKE_NUM(DATADIR_MSTORY, 116),
        DATA_MAKE_NUM(DATADIR_MSTORY, 124),
        DATA_MAKE_NUM(DATADIR_MSTORY, 131)
    };
    s32 sp1C[][3] = {
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x62), DATA_MAKE_NUM(DATADIR_MSTORY, 0x65), DATA_MAKE_NUM(DATADIR_MSTORY, 0x67) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x6D), DATA_MAKE_NUM(DATADIR_MSTORY, 0x70), DATA_MAKE_NUM(DATADIR_MSTORY, 0x72) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x75), DATA_MAKE_NUM(DATADIR_MSTORY, 0x78), DATA_MAKE_NUM(DATADIR_MSTORY, 0x7A) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x7D), DATA_MAKE_NUM(DATADIR_MSTORY, 0x7F), DATA_MAKE_NUM(DATADIR_MSTORY, 0x81) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x84), DATA_MAKE_NUM(DATADIR_MSTORY, 0x87), DATA_MAKE_NUM(DATADIR_MSTORY, 0x89) }
    };

    arg0->model[1] = Hu3DModelCreateFile(sp8[arg1]);
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[1], sp1C[arg1][0]);
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[1], sp1C[arg1][1]);
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[1], sp1C[arg1][2]);
    Hu3DModelPosSet(arg0->model[1], -120.0f, 0.0f, 670.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, 45.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    if (arg1 == 3) {
        Hu3DData[arg0->model[1]].pos.y = 50.0f;
    }
    Hu3DModelShadowSet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 1, 0, 1);
}

void fn_1_13570(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_710, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_714.unk00 = temp_r3;
    lbl_1_bss_714.unk04 = NULL;
    lbl_1_bss_714.unk00->data = &lbl_1_bss_714;
    fn_1_132EC(temp_r3, lbl_1_bss_7B4.unk00);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_714.unk04 != NULL) {
            lbl_1_bss_714.unk04(temp_r3, &lbl_1_bss_714);
        }
    }
}

void fn_1_13880(void) {
    StructBss4* var_r31;

    var_r31 = &lbl_1_bss_4;
    var_r31->unk08.x = 0.0f;
    var_r31->unk08.y = 125.0f;
    var_r31->unk08.z = 0.0f;
    var_r31->unk20.x = -5.0f;
    var_r31->unk20.y = 0.0f;
    var_r31->unk20.z = 0.0f;
    var_r31->unk38 = 1750.0f;
}

void fn_1_1390C(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    if (var_r31->unk40 == 50) {
        fn_1_1DCC(lbl_1_bss_764.unk00, 5, 5, 0, 0);
        fn_1_1DCC(lbl_1_bss_764.unk00, 6, 6, 0, 0);
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
        Hu3DData[lbl_1_bss_764.unk00->model[5]].rot.x = fn_1_828(0.0f, 45.0f, var_r31->unk40 - 90, 90.0f);
    }
}
