#include "REL/mstoryDll.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/objsub.h"

#ifndef __MWERKS__
#include "game/audio.h"
#include "game/hsfdraw.h"
#include "game/msm.h"
#endif

#include "game/printfunc.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

typedef struct {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ char unk0C[4];
    /* 0x010 */ s32 unk10;
    /* 0x014 */ char unk14[0x20];
    /* 0x034 */ StructFn352C unk34[4];
    /* 0x104 */ s32 unk104;
} StructBss608; // Size 0x108

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
} StructData570; // Size 0x14

void fn_1_FD1C(void);
void fn_1_10298(omObjData* arg0, StructBss19C* arg1);
void fn_1_10384(omObjData* arg0, StructBss19C* arg1);
void fn_1_10450(omObjData* arg0, StructBss19C* arg1);
void fn_1_1054C(void);
void fn_1_108F8(void);
void fn_1_10C6C(s32 arg0);
void fn_1_10FD0(void);
void fn_1_112A0(void);
void fn_1_1132C(void);
void fn_1_1141C(void);
void fn_1_11534(void);

StructBss608 lbl_1_bss_608;
StructBss19C lbl_1_bss_5E0;
StructBss19C lbl_1_bss_5B8;
StructBss19C lbl_1_bss_590;
StructBss19C lbl_1_bss_568;
AnimData* lbl_1_bss_560[2];
s32 lbl_1_bss_55C;
Process* lbl_1_bss_558;

StructData570 lbl_1_data_570[] = {
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x00), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x01), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x02), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x03), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x04), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x05), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x06), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x07), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x08), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x09), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0A), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0B), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0C), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0D), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0E), 1, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0F), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x10), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x11), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x12), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x13), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x14), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x15), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x16), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x17), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x18), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x19), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1A), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1B), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1C), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1D), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1E), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1F), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x20), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x21), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x22), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x23), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x24), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x25), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x26), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x27), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x28), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x29), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2A), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2B), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2C), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2D), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2E), 0, 0, 0, 1 },
    { DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2F), 0, 0, 0, 1 }
};

s32 lbl_1_data_930[][4] = {
    { MAKE_MESSID(30, 72), MAKE_MESSID(30, 73) },
    { MAKE_MESSID(30, 74), MAKE_MESSID(30, 75) },
    { MAKE_MESSID(30, 76), MAKE_MESSID(30, 77) },
    { MAKE_MESSID(30, 78), MAKE_MESSID(30, 79) },
    { MAKE_MESSID(30, 80), MAKE_MESSID(30, 81) }
};

void fn_1_E710(Process* arg0, s32 arg1, s32 arg2) {
    lbl_1_bss_558 = arg0;
    lbl_1_bss_608.unk00 = arg1;
    lbl_1_bss_608.unk10 = arg2;
    fn_1_BF4();
    lbl_1_bss_608.unk104 = fn_1_3618(0xFF);
    fn_1_27E8(lbl_1_bss_558, fn_1_112A0);
    fn_1_3704();
    fn_1_10C6C(arg2);
    HuPrcChildCreate(fn_1_1054C, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_108F8, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_10FD0, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_FD1C, 100, 0x2000, 0, HuPrcCurrentGet());
}

void fn_1_E828(omObjData* arg0) {
    if (arg0->work[2] != 0) {
        arg0->work[2]--;
        return;
    }
    if (arg0->work[2] == 0 && Hu3DMotionEndCheck(arg0->model[1])) {
        fn_1_1DCC(arg0, 1, arg0->work[1], 15, 1);
        arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
    }
}

void fn_1_E8B4(void) {
    s32 var_r30 = 16;
    s32 var_r29 = 40;
    GXColor sp10 = { 0x00, 0x00, 0x80, 0x80 };
    s32 i;

    while (TRUE) {
        fn_1_B8C();
        printWin(var_r30, var_r29, 220, 130, &sp10);
        if (lbl_1_bss_5E0.unk04 == NULL) {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN   -> FALSE");
        } else {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN   -> TRUE");
        }
        if (lbl_1_bss_5B8.unk04 == NULL) {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP    -> FALSE");
        } else {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP    -> TRUE");
        }
        if (lbl_1_bss_590.unk04 == NULL) {
            print8(var_r30, var_r29 + 20, 1.0f, "PROC_SUB    -> FALSE");
        } else {
            print8(var_r30, var_r29 + 20, 1.0f, "PROC_SUB    -> TRUE");
        }
        if (lbl_1_bss_568.unk04 == NULL) {
            print8(var_r30, var_r29 + 30, 1.0f, "PROC_PLAYER -> FALSE");
        } else {
            print8(var_r30, var_r29 + 30, 1.0f, "PROC_PLAYER -> TRUE");
        }
        print8(var_r30, var_r29 + 60, 1.0f, "M:%d P:%d W:%d", lbl_1_bss_608.unk00, lbl_1_bss_608.unk04, lbl_1_bss_608.unk10);
        print8(var_r30, var_r29 + 80, 1.0f, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(var_r30, var_r29 + 90 + i * 10, 1.0f, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i,
                lbl_1_bss_608.unk34[i].unk00, lbl_1_bss_608.unk34[i].unk04, lbl_1_bss_608.unk34[i].unk08,
                lbl_1_bss_608.unk34[i].unk0C, lbl_1_bss_608.unk34[i].unk14, lbl_1_bss_608.unk34[i].unk10);
        }
    }
}

void fn_1_EC00(void) {
    lbl_1_bss_58[0] = HuAudSeqPlay(0x36);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    fn_1_BAC(60);
}

void fn_1_EC5C(void) {
    lbl_1_bss_608.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_608.unk10);
    fn_1_1D1C(lbl_1_bss_608.unk08, lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10, 0);
    fn_1_1CE8(lbl_1_bss_608.unk08, lbl_1_data_930[lbl_1_bss_608.unk00][0]);
    fn_1_1ACC(lbl_1_bss_608.unk08, -1);
    fn_1_1DCC(lbl_1_bss_590.unk00, 1, 1, 15, 1);
    fn_1_1A64(lbl_1_bss_608.unk08);
    fn_1_1DCC(lbl_1_bss_5B8.unk00, 2, 2, 0, 0);
    fn_1_BAC(90);
    fn_1_1DCC(lbl_1_bss_590.unk00, 1, 4, 15, 0);
    fn_1_BAC(30);
    fn_1_1DCC(lbl_1_bss_568.unk00, 1, 4, 15, 0);
    fn_1_2224(lbl_1_bss_5B8.unk00, 2, 2, 0);
    fn_1_BAC(60);
    fn_1_1DCC(lbl_1_bss_568.unk00, 1, 1, 84, 1);
    fn_1_1DCC(lbl_1_bss_590.unk00, 1, 1, 84, 1);
    fn_1_3804(&lbl_1_bss_4);
    fn_1_2710(fn_1_1132C);
    lbl_1_bss_5B8.unk04 = (void*) fn_1_10450;
    do {
        fn_1_B8C();
    } while (lbl_1_bss_5B8.unk04 != NULL);
    fn_1_BAC(10);
    lbl_1_bss_608.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_608.unk10);
    fn_1_1DCC(lbl_1_bss_590.unk00, 1, 3, 15, 1);
    if (lbl_1_bss_608.unk00 == 0) {
        HuAudFXPlay(lbl_1_data_0[lbl_1_bss_608.unk00][2]);
    } else {
        HuAudFXPlay(lbl_1_data_0[lbl_1_bss_608.unk00][0]);
    }
    fn_1_1D1C(lbl_1_bss_608.unk08, MAKE_MESSID(50, lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10 * 6 + 5) + lbl_1_bss_608.unk00, 2);
    fn_1_1CE8(lbl_1_bss_608.unk08, lbl_1_data_930[lbl_1_bss_608.unk00][1]);
    fn_1_1ACC(lbl_1_bss_608.unk08, -1);
    fn_1_1DCC(lbl_1_bss_590.unk00, 1, 1, 15, 1);
    fn_1_1A64(lbl_1_bss_608.unk08);
}

void fn_1_EFE0(s32 arg0, StructBss19C* arg1) {
    s32 temp_r31;

    temp_r31 = HuAudSStreamPlay(7);
    do {
        fn_1_B8C();
    } while (HuAudSStreamStatGet(temp_r31) != 0);
    HuAudSeqPause(lbl_1_bss_58[0], 0, 1000);
    arg1->unk04 = 0;
}

void fn_1_F050(omObjData* arg0, StructBss19C* arg1) {
    s32 temp_r31;

    temp_r31 = lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10 * 6 + lbl_1_bss_608.unk00;
    fn_1_BAC(150);
    OSReport("########## PRESENT_SE : %d\n", temp_r31);
    HuAudFXPlay(0x8D4 + temp_r31);
    if (lbl_1_data_570[lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10 * 6 + lbl_1_bss_608.unk00].unk04 == 1) {
        fn_1_1DCC(lbl_1_bss_5B8.unk00, 7, 7, 0, 0);
        fn_1_BAC(60);
        fn_1_1DCC(lbl_1_bss_5B8.unk00, 7, 12, 0, 1);
    } else {
        fn_1_1DCC(lbl_1_bss_5B8.unk00, 7, 7, 1, 0);
    }
    arg1->unk04 = 0;
}

void fn_1_F19C(void) {
    s32 i;

    fn_1_1DCC(lbl_1_bss_568.unk00, 1, 2, 15, 1);
    for (i = 0; i < 30; i++) {
        fn_1_B8C();
        if (lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10 != 5) {
            Hu3DData[lbl_1_bss_568.unk00->model[1]].pos.x = fn_1_828(120.0f, 80.0f, i, 30.0f);
        }
        Hu3DData[lbl_1_bss_568.unk00->model[1]].rot.y = fn_1_828(-60.0f, -90.0f, i, 30.0f);
    }
    fn_1_1DCC(lbl_1_bss_568.unk00, 1, 5, 5, 0);
    while (TRUE) {
        fn_1_B8C();
        if (Hu3DMotionTimeGet(lbl_1_bss_568.unk00->model[1]) >= 35.0f) {
            break;
        }
    }
    Hu3DModelPosSet(lbl_1_bss_5B8.unk00->model[5], 0.0f, 0.0f, 0.0f);
    Hu3DModelHookReset(lbl_1_bss_5B8.unk00->model[9]);
    Hu3DModelHookSet(lbl_1_bss_568.unk00->model[1], CharModelHookNameGet(lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10, 1, 1), lbl_1_bss_5B8.unk00->model[5]);
    fn_1_BAC(60);
    lbl_1_bss_5B8.unk04 = (void*) fn_1_10298;
    HuAudFXPlay(0xA3);
    HuAudCharVoicePlay(lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10, 0x128);
    fn_1_1DCC(lbl_1_bss_5B8.unk00, 6, 6, 0, 0);
    Hu3DModelAttrReset(lbl_1_bss_5B8.unk00->model[6], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_5B8.unk00->model[5], HU3D_ATTR_DISPOFF);
    fn_1_1DCC(lbl_1_bss_568.unk00, 1, 6, 5, 0);
    HuAudSeqPause(lbl_1_bss_58[0], 1, 1000);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    Hu3DMotionSpeedSet(lbl_1_bss_568.unk00->model[1], 0.0f);
    Hu3DMotionTimeSet(lbl_1_bss_568.unk00->model[1], 50.0f);
    Hu3DModelAttrReset(lbl_1_bss_5B8.unk00->model[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_5B8.unk00->model[8], HU3D_ATTR_DISPOFF);
    fn_1_1DCC(lbl_1_bss_5B8.unk00, 8, 8, 0, 1);
    fn_1_BAC(30);
    HuAudFXPlay(0xA9);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    fn_1_3804(&lbl_1_bss_4);
    fn_1_2710(fn_1_11534);
    fn_1_BAC(60);
    lbl_1_bss_568.unk04 = (void*) fn_1_F050;
    lbl_1_bss_608.unk08 = fn_1_1834(1, 0, 21, 2, lbl_1_bss_608.unk10);
    lbl_1_bss_590.unk04 = (void*) fn_1_EFE0;
    fn_1_1D1C(lbl_1_bss_608.unk08, MAKE_MESSID(50, lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10 * 6 + 6) + lbl_1_bss_608.unk00, 0);
    fn_1_6C1C(lbl_1_bss_608.unk08, MAKE_MESSID(50, 134), 0, 300);
    fn_1_1CE8(lbl_1_bss_608.unk08, MAKE_MESSID(37, 4));
    fn_1_1A64(lbl_1_bss_608.unk08);
    fn_1_3804(&lbl_1_bss_4);
    fn_1_2710(fn_1_1141C);
    lbl_1_bss_5B8.unk04 = (void*) fn_1_10384;
    fn_1_BAC(30);
    Hu3DMotionSpeedSet(lbl_1_bss_568.unk00->model[1], 0.1f);
    fn_1_BAC(180);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
}

s32 fn_1_F780(s32 arg0) {
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

void fn_1_F86C(void) {
    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_BAC(60);
    SLCommonSet();
    SLSaveBoardStory();
    if (SLSaveFlagGet() == 1) {
        SLSave();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_55C = 1;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_F910(void) {
    omOvlHisData* var_r31;

    msmSeStopAll(FALSE, 1000);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    fn_1_BAC(60);
    CharModelKill(-1);
    HuAudFXAllStop();
    HuAudSStreamAllStop();
    {
        s32 sp8[] = { 53, 56, 55, 54, 57 };

        GWMGAvailSet(omMgIndexGet(sp8[lbl_1_bss_608.unk00]) + 0x191);
    }
    GWGameStat.present[lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10 * 6 + lbl_1_bss_608.unk00] = 1;
    OSReport("########## PRESENTFLG CHR:%d, MAP:%d, PRESENT:%d\n", lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10, lbl_1_bss_608.unk00, lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10 * 6 + lbl_1_bss_608.unk00);
    var_r31 = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MSTORY, 20, var_r31->stat);
    omOvlCallEx(OVL_PRESENT, 1, lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10 * 6 + lbl_1_bss_608.unk00 + 1, 0);
}

void fn_1_FAE4(omObjData* arg0, StructBss19C* arg1) {
    s32 sp8 = 0;

    lbl_1_bss_58[0] = HuAudSeqPlay(0x36);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_B8C();
    } while (WipeStatGet() != 0);
    fn_1_BAC(60);
    fn_1_EC5C();
    fn_1_F19C();
    fn_1_F910();
    arg1->unk04 = 0;
}

void fn_1_FD1C(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_558, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_5E0.unk00 = temp_r3;
    lbl_1_bss_5E0.unk04 = (void*) fn_1_FAE4;
    lbl_1_bss_5E0.unk00->data = &lbl_1_bss_5E0;
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_5E0.unk04 != NULL) {
            lbl_1_bss_5E0.unk04(temp_r3, &lbl_1_bss_5E0);
        }
    }
}

void fn_1_FDD0(omObjData* arg0, s32 arg1) {
    s32 temp_r29;

    temp_r29 = lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10;
    arg0->model[7] = Hu3DModelCreateFile(lbl_1_data_570[temp_r29 * 6 + arg1].unk00);
    arg0->motion[7] = Hu3DMotionIDGet(arg0->model[7]);
    if (lbl_1_data_570[temp_r29 * 6 + arg1].unk04 == 1) {
        arg0->motion[12] = Hu3DJointMotionFile(arg0->model[7], DATA_MAKE_NUM(DATADIR_MSTORY4, 48));
    }
    Hu3DModelPosSet(arg0->model[7], 0.0f, 180.0f, 825.0f);
    Hu3DModelAttrSet(arg0->model[7], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(arg0->model[7]);
    fn_1_1DCC(arg0, 7, 7, 0, 2);
    HuDataDirClose(DATADIR_MSTORY4);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 56));
    arg0->motion[0] = Hu3DMotionIDGet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 0, 0, 2);
    Hu3DModelShadowMapObjSet(arg0->model[1], "base_fix9-base");
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 59));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY, 60));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY, 61));
    fn_1_1DCC(arg0, 2, 2, 0, 2);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 57));
    arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 81));
    Hu3DModelShadowSet(arg0->model[5]);
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 83));
    arg0->motion[6] = Hu3DMotionIDGet(arg0->model[6]);
    Hu3DModelPosSet(arg0->model[6], 25.0f, 125.0f, 900.0f);
    Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF);
    fn_1_1DCC(arg0, 6, 6, 0, 2);
    arg0->model[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 96));
    arg0->motion[8] = Hu3DMotionIDGet(arg0->model[8]);
    Hu3DModelAttrSet(arg0->model[8], HU3D_ATTR_DISPOFF);
    fn_1_1DCC(arg0, 8, 8, 0, 2);
    arg0->model[9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY, 84));
    arg0->motion[9] = Hu3DMotionIDGet(arg0->model[9]);
    Hu3DModelPosSet(arg0->model[9], 0.0f, 0.0f, 460.0f);
    Hu3DModelShadowSet(arg0->model[9]);
    fn_1_1DCC(arg0, 9, 9, 0, 2);
    Hu3DModelHookSet(arg0->model[9], "carrier2-target0", arg0->model[5]);
    lbl_1_bss_560[0] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY, 85 + arg1 * 2), MEMORY_DEFAULT_NUM));
    lbl_1_bss_560[1] = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY, 86 + arg1 * 2), MEMORY_DEFAULT_NUM));
    Hu3DAnimCreate(lbl_1_bss_560[0], lbl_1_bss_5B8.unk00->model[5], "cylinder3");
    Hu3DAnimCreate(lbl_1_bss_560[1], lbl_1_bss_5B8.unk00->model[5], "wakuwaku");
}

void fn_1_10298(omObjData* arg0, StructBss19C* arg1) {
    Mtx sp8;

    Hu3DData[arg0->model[7]].pos.y = fn_1_ACC(180.0f, 185.0f, arg1->unk08++, 360.0f);
    Hu3DModelObjMtxGet(arg0->model[7], "effect", sp8);
    Hu3DModelPosSet(arg0->model[8], sp8[0][3], sp8[1][3], sp8[2][3]);
    if (arg1->unk08 >= 360) {
        arg1->unk08 = 0;
    }
}

void fn_1_10384(omObjData* arg0, StructBss19C* arg1) {
    Mtx sp8;

    Hu3DData[arg0->model[7]].pos.y += arg1->unk0C / 100.0f;
    Hu3DModelObjMtxGet(arg0->model[7], "effect", sp8);
    Hu3DModelPosSet(arg0->model[8], sp8[0][3], sp8[1][3], sp8[2][3]);
    arg1->unk0C += 2;
}

void fn_1_10450(omObjData* arg0, StructBss19C* arg1) {
    fn_1_1DCC(arg0, 9, 9, 0, 1);
    while (TRUE) {
        fn_1_B8C();
        Hu3DData[arg0->model[9]].pos.z += 2.5f;
        if (Hu3DData[arg0->model[9]].pos.z >= 670.0f) {
            break;
        }
    }
    Hu3DData[arg0->model[9]].pos.z = 670.0f;
    Hu3DMotionSpeedSet(arg0->model[9], 0.0f);
    arg1->unk04 = 0;
}

void fn_1_1054C(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_558, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_5B8.unk00 = temp_r3;
    lbl_1_bss_5B8.unk04 = NULL;
    fn_1_FDD0(temp_r3, lbl_1_bss_608.unk00);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_5B8.unk04 != NULL) {
            lbl_1_bss_5B8.unk04(temp_r3, &lbl_1_bss_5B8);
        }
    }
}

void fn_1_105F8(omObjData* arg0, s32 arg1) {
    s32 sp1C[] = {
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x0061),
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x006C),
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x0074),
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x007C),
        DATA_MAKE_NUM(DATADIR_MSTORY, 0x0083)
    };
    s32 sp30[][5] = {
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x0062), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0064), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0065), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0067), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0068) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x006D), DATA_MAKE_NUM(DATADIR_MSTORY, 0x006F), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0070), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0072), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0073) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x0075), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0077), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0078), DATA_MAKE_NUM(DATADIR_MSTORY, 0x007A), DATA_MAKE_NUM(DATADIR_MSTORY, 0x007B) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x007D), DATA_MAKE_NUM(DATADIR_MSTORY, 0x007E), DATA_MAKE_NUM(DATADIR_MSTORY, 0x007F), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0081), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0082) },
        { DATA_MAKE_NUM(DATADIR_MSTORY, 0x0084), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0086), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0087), DATA_MAKE_NUM(DATADIR_MSTORY, 0x0089), DATA_MAKE_NUM(DATADIR_MSTORY, 0x008A) }
    };

    arg0->model[1] = Hu3DModelCreateFile(sp1C[arg1]);
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][0]);
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][1]);
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][2]);
    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][3]);
    arg0->motion[5] = Hu3DJointMotionFile(arg0->model[1], sp30[arg1][4]);
    Hu3DModelPosSet(arg0->model[1], -120.0f, 0.0f, 670.0f);
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

void fn_1_108F8(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_558, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_590.unk00 = temp_r3;
    lbl_1_bss_590.unk04 = NULL;
    fn_1_105F8(temp_r3, lbl_1_bss_608.unk00);
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_590.unk04 != NULL) {
            lbl_1_bss_590.unk04(temp_r3, &lbl_1_bss_590);
        }
    }
}

void fn_1_10C6C(s32 arg0) {
    s32 spC[4];
    s32 i;

    spC[0] = 0;
    for (i = 1; i < 4; i++) {
        spC[i] = spC[i - 1] + 1;
        if (spC[i] >= 4) {
            spC[i] = 0;
        }
        if (arg0 == spC[i]) {
            lbl_1_bss_608.unk04 = i;
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_352C(&lbl_1_bss_608.unk34[i], spC[i]);
    }
}

void fn_1_10D50(omObjData* arg0, s32 arg1) {
    s32 temp_r30;

    temp_r30 = lbl_1_bss_608.unk34[lbl_1_bss_608.unk04].unk10;
    arg0->model[1] = CharModelCreate(temp_r30, 1);
    arg0->motion[1] = CharModelMotionCreate(temp_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
    arg0->motion[2] = CharModelMotionCreate(temp_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 2));
    arg0->motion[3] = CharModelMotionCreate(temp_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 53));
    arg0->motion[4] = CharModelMotionCreate(temp_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 109));
    arg0->motion[5] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_MSTORY, 24 + temp_r30));
    arg0->motion[6] = Hu3DJointMotionFile(arg0->model[1], DATA_MAKE_NUM(DATADIR_MSTORY, 32 + temp_r30));
    CharModelMotionDataClose(temp_r30);
    Hu3DModelPosSet(arg0->model[1], 120.0f, 0.0f, 670.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, -60.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelShadowSet(arg0->model[1]);
    fn_1_1DCC(arg0, 1, 1, 0, 1);
}

void fn_1_10F24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fn_1_1DCC(lbl_1_bss_568.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_568.unk00->work[0] = arg4;
    lbl_1_bss_568.unk00->work[1] = arg1;
    lbl_1_bss_568.unk00->work[2] = arg2 + 1;
}

void fn_1_10FD0(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_558, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_568.unk00 = temp_r3;
    lbl_1_bss_568.unk04 = NULL;
    lbl_1_bss_568.unk00->data = &lbl_1_bss_568;
    fn_1_10D50(temp_r3, lbl_1_bss_608.unk04); // Second argument required to match.
    while (TRUE) {
        fn_1_B8C();
        if (lbl_1_bss_568.unk04 != NULL) {
            lbl_1_bss_568.unk04(temp_r3, &lbl_1_bss_568);
        }
        if (temp_r3->work[0] != 0) {
            fn_1_E828(temp_r3);
        }
    }
}

void fn_1_112A0(void) {
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

void fn_1_1132C(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = 0.0f;
    sp8.unk08.y = 100.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = 0.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1400.0f;
    fn_1_51D0(var_r31, &sp8, var_r31->unk40++, 120.0f, 10.0f);
}

void fn_1_1141C(void) {
    StructBss4* var_r31;

    var_r31 = &lbl_1_bss_4;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = Hu3DData[lbl_1_bss_5B8.unk00->model[7]].pos.y;
    var_r31->unk1C = 0.0f;
    var_r31->unk2C = 0.0f;
    var_r31->unk30 = 0.0f;
    var_r31->unk34 = 0.0f;
    var_r31->unk3C = fn_1_828(1100.0f, 1400.0f, var_r31->unk40++, 240.0f);
    fn_1_3ABC(var_r31, 30.0f);
}

void fn_1_11534(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = 0.0f;
    sp8.unk08.y = 160.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = 0.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1100.0f;
    fn_1_61E8(var_r31, &sp8, var_r31->unk40++, 10.0f, 5.0f);
}
