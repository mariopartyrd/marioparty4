#include "REL/mstory2Dll.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/board/main.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"


typedef struct {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ char unk18[0x18];
    /* 0x030 */ StructFn357C unk30[4];
    /* 0x100 */ float unk100;
} StructBss688; // Size 0x104

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ char unk0C[4];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} StructBss4E8; // Size 0x18

StructBss688 lbl_1_bss_688;
StructBss16C lbl_1_bss_660;
StructBss16C lbl_1_bss_638;
StructBss16C lbl_1_bss_610;
StructBss16C lbl_1_bss_5E8;
StructBss16C lbl_1_bss_548[4];
StructBss4E8 lbl_1_bss_4E8[4];
BOOL lbl_1_bss_4E4;
Process *lbl_1_bss_4E0;

s32 lbl_1_data_698[7] = {
    DATADIR_W01,
    DATADIR_W02,
    DATADIR_W03,
    DATADIR_W04,
    DATADIR_W05,
    DATADIR_W06,
    DATADIR_W10,
};

s32 lbl_1_data_6B4[8] = { DATADIR_MARIOMDL1, DATADIR_LUIGIMDL1, DATADIR_PEACHMDL1, DATADIR_YOSHIMDL1, DATADIR_WARIOMDL1, DATADIR_DONKEYMDL1,
    DATADIR_DAISYMDL1, DATADIR_WALUIGIMDL1 };

void fn_1_FDFC(void);
void fn_1_10194(void);
void fn_1_106B0(omObjData *arg0, StructBss16C *arg1);
void fn_1_1094C(void);
void fn_1_10DF4(int arg0, int arg1, int arg2, int arg3, int arg4);
void fn_1_10EA0(omObjData *arg0, StructBss16C *arg1);
void fn_1_1112C(void);
void fn_1_11418(int arg0);
void fn_1_11934(omObjData *arg0, StructBss16C *arg1);
void fn_1_11A98(omObjData *arg0, StructBss16C *arg1);
void fn_1_11BB0(void);
void fn_1_11FD0(void);
void fn_1_1205C(void);
void fn_1_1218C(void);

void fn_1_E570(void)
{
    int statId = HuDataDirReadAsync(DATADIR_BOARD);
    if (statId != -1) {
        while (!HuDataGetAsyncStat(statId)) {
            HuPrcVSleep();
        }
    }
    HuAR_MRAMtoARAM(DATADIR_BOARD);
    while (HuARDMACheck()) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATADIR_BOARD);
    statId = HuDataDirReadAsync(lbl_1_data_698[GWSystem.board]);
    if (statId != -1) {
        while (!HuDataGetAsyncStat(statId)) {
            HuPrcVSleep();
        }
    }
    lbl_1_bss_4E4 = TRUE;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_E638(void)
{
    int i, j;
    lbl_1_bss_4E8[0].unk00 = 0;
    lbl_1_bss_4E8[0].unk04 = 0;
    lbl_1_bss_4E8[0].unk10 = lbl_1_bss_688.unk30[lbl_1_bss_688.unk00].unk10;
    lbl_1_bss_4E8[0].unk14 = lbl_1_bss_688.unk30[lbl_1_bss_688.unk00].unk14;
    lbl_1_bss_4E8[0].unk08 = 0;
    for (i = 1; i < 4; i++) {
        lbl_1_bss_4E8[i].unk10 = -1;
        lbl_1_bss_4E8[i].unk14 = i;
        lbl_1_bss_4E8[i].unk08 = 1;
    }
    for (i = 1; i < 4; i++) {
        do {
            lbl_1_bss_4E8[i].unk10 = rand8() % 8;
            for (j = 0; j < 4; j++) {
                if (i != j && lbl_1_bss_4E8[j].unk10 != -1 && lbl_1_bss_4E8[i].unk10 == lbl_1_bss_4E8[j].unk10) {
                    break;
                }
            }
        } while (j != 4);
    }
    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].character = lbl_1_bss_4E8[i].unk10;
        GWPlayerCfg[i].pad_idx = lbl_1_bss_4E8[i].unk14;
        GWPlayerCfg[i].group = 0;
        GWPlayerCfg[i].iscom = lbl_1_bss_4E8[i].unk08;
    }
    BoardSaveInit(GWSystem.board);
    CharKill(-1);
    HuDataDirClose(DATADIR_MSTORY2);
    HuPrcChildCreate(fn_1_E570, 100, 12288, 0, lbl_1_bss_4E0);
}

void fn_1_E8EC(void)
{
    int ovlTbl[7] = { OVL_W01, OVL_W02, OVL_W03, OVL_W04, OVL_W05, OVL_W06, OVL_W10 };
    omOvlHisData *his;
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet()) {
        fn_1_BC8();
    }
    CharModelKill(-1);
    MGSeqKillAll();
    his = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MSTORY3, 0, his->stat);
    do {
        fn_1_BC8();
    } while (lbl_1_bss_4E4 != 1);
    CharARAMOpen(GWPlayerCfg[0].character);
    CharARAMOpen(GWPlayerCfg[1].character);
    CharARAMOpen(GWPlayerCfg[2].character);
    CharARAMOpen(GWPlayerCfg[3].character);
    HuAudSeqAllFadeOut(1000);
    HuAudSStreamAllFadeOut(1000);
    omOvlCallEx(ovlTbl[GWSystem.board], 1, 0, 0);
    while (1) {
        fn_1_BC8();
    }
}

void fn_1_EA2C(Process *arg0, s32 arg1)
{
    int i;
    lbl_1_bss_4E0 = arg0;
    lbl_1_bss_688.unk0C = arg1;
    fn_1_C30();
    fn_1_3668(255);
    fn_1_2828(lbl_1_bss_4E0, fn_1_11FD0);
    fn_1_3754();
    fn_1_11418(arg1);
    HuPrcChildCreate(fn_1_10194, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_1094C, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_1112C, 100, 8192, 0, HuPrcCurrentGet());
    for (i = 0; i < 4; i++) {
        HuPrcChildCreate(fn_1_11BB0, 100, 8192, 0, HuPrcCurrentGet());
    }
    HuPrcChildCreate(fn_1_FDFC, 100, 8192, 0, HuPrcCurrentGet());
}

void fn_1_EB60(omObjData *object)
{
    if (object->work[2]) {
        object->work[2]--;
        return;
    }
    if (object->work[2] == 0 && Hu3DMotionEndCheck(object->model[1])) {
        fn_1_1DFC(object, 1, object->work[1], 15, 1);
        object->work[0] = object->work[1] = object->work[2] = 0;
    }
}

void fn_1_EBEC(void)
{
    int posX = 16;
    int posY = 40;
    GXColor winColor = { 0, 0, 128, 128 };
    int i;
    while (1) {
        fn_1_BC8();
        printWin(posX, posY, 220, 160, &winColor);
        if (lbl_1_bss_660.unk04 == NULL) {
            print8(posX, posY, 1, "PROC_MAIN    -> FALSE");
        }
        else {
            print8(posX, posY, 1, "PROC_MAIN    -> TRUE");
        }
        if (lbl_1_bss_638.unk04 == NULL) {
            print8(posX, posY + 10, 1, "PROC_MAP     -> FALSE");
        }
        else {
            print8(posX, posY + 10, 1, "PROC_MAP     -> TRUE");
        }
        if (lbl_1_bss_610.unk04 == NULL) {
            print8(posX, posY + 20, 1, "PROC_KOOPA   -> FALSE");
        }
        else {
            print8(posX, posY + 20, 1, "PROC_KOOPA   -> TRUE");
        }
        if (lbl_1_bss_5E8.unk04 == NULL) {
            print8(posX, posY + 30, 1, "PROC_MKOOPA  -> FALSE");
        }
        else {
            print8(posX, posY + 30, 1, "PROC_MKOOPA  -> TRUE");
        }
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_548[i].unk04 == NULL) {
                print8(posX, posY + 40 + (i * 10), 1, "PROC_PLAYER%d -> FALSE", i);
            }
            else {
                print8(posX, posY + 40 + (i * 10), 1, "PROC_PLAYER%d -> TRUE", i);
            }
        }
        print8(posX, posY + 90, 1, "P:%d W:%d", lbl_1_bss_688.unk00, lbl_1_bss_688.unk0C);
        print8(posX, posY + 110, 1, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(posX, posY + 120 + (i * 10), 1, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i, lbl_1_bss_688.unk30[i].unk00, lbl_1_bss_688.unk30[i].unk04,
                lbl_1_bss_688.unk30[i].unk08, lbl_1_bss_688.unk30[i].unk0C, lbl_1_bss_688.unk30[i].unk14, lbl_1_bss_688.unk30[i].unk10);
        }
    }
}

void fn_1_EFCC(void)
{
    lbl_1_bss_78[0] = HuAudSeqPlay(52);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    fn_1_BE8(60);
}

void fn_1_F028(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_548[i].unk04 = (void *)fn_1_11934;
    }
    do {
        fn_1_BC8();
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_548[i].unk04 != NULL) {
                break;
            }
        }
    } while (i != 4);
    lbl_1_bss_548[lbl_1_bss_688.unk00].unk04 = (void *)fn_1_11A98;
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_1205C);
    do {
        fn_1_BC8();
    } while (lbl_1_bss_548[lbl_1_bss_688.unk00].unk04 != NULL);
    do {
        fn_1_BC8();
    } while (lbl_1_bss_5E8.unk04 != NULL);
    fn_1_BE8(30);
    if (0) {
        // Dummy code to stop this function from inlining
        do {
            fn_1_BC8();
            for (i = 0; i < 4; i++) {
                if (lbl_1_bss_548[i].unk04 != NULL) {
                    break;
                }
            }
        } while (i != 4);
        lbl_1_bss_548[lbl_1_bss_688.unk00].unk04 = (void *)fn_1_11A98;
        fn_1_3854(&lbl_1_bss_24);
        fn_1_2750(fn_1_1205C);
        do {
            fn_1_BC8();
        } while (lbl_1_bss_548[lbl_1_bss_688.unk00].unk04 != NULL);
        do {
            fn_1_BC8();
        } while (lbl_1_bss_5E8.unk04 != NULL);
        fn_1_BE8(30);
    }
}

void fn_1_F150(void)
{
    lbl_1_bss_688.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_688.unk0C);
    HuAudFXPlay(lbl_1_data_0[5][0]);
    fn_1_10DF4(3, -1, 15, 1, 0);
    fn_1_1D18(lbl_1_bss_688.unk04, 0x1F0009);
    fn_1_1AFC(lbl_1_bss_688.unk04, -1);
    fn_1_1D18(lbl_1_bss_688.unk04, 0x250004);
    fn_1_10DF4(1, -1, 15, 1, 0);
    fn_1_1A94(lbl_1_bss_688.unk04);
}

int fn_1_F22C(void)
{
    int result = 0;
    fn_1_1D18(lbl_1_bss_688.unk04, 0x1E0021);
    fn_1_1AFC(lbl_1_bss_688.unk04, 5);
    lbl_1_bss_688.unk08 = fn_1_7064(0x1E0035, lbl_1_bss_688.unk0C);
    fn_1_1D18(lbl_1_bss_688.unk08, 0x1E0035);
    result = fn_1_1C64(lbl_1_bss_688.unk08);
    fn_1_1D18(lbl_1_bss_688.unk08, 0x250004);
    fn_1_71DC(lbl_1_bss_688.unk08);
    return result;
}

int fn_1_F2FC(void)
{
    int result = 0;
    fn_1_1D18(lbl_1_bss_688.unk04, 0x1E0005);
    fn_1_1AFC(lbl_1_bss_688.unk04, 5);
    lbl_1_bss_688.unk08 = fn_1_7064(0x1E0035, lbl_1_bss_688.unk0C);
    fn_1_1D18(lbl_1_bss_688.unk08, 0x1E0035);
    result = fn_1_1BA8(lbl_1_bss_688.unk08, 1);
    fn_1_1D18(lbl_1_bss_688.unk08, 0x250004);
    fn_1_71DC(lbl_1_bss_688.unk08);
    return result;
}

void fn_1_F3D0(void)
{
    lbl_1_bss_5E8.unk04 = (void *)fn_1_10EA0;
    lbl_1_bss_688.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_688.unk0C);
    HuAudFXPlay(lbl_1_data_0[5][0]);
    fn_1_1D18(lbl_1_bss_688.unk04, 0x1F000A);
    fn_1_1AFC(lbl_1_bss_688.unk04, -1);
    fn_1_1D18(lbl_1_bss_688.unk04, 0x250004);
    fn_1_1A94(lbl_1_bss_688.unk04);
    HuAudSeqFadeOut(lbl_1_bss_78[0], 1000);
    do {
        fn_1_BC8();
    } while (lbl_1_bss_5E8.unk04 != NULL);
    lbl_1_bss_610.unk04 = (void *)fn_1_106B0;
    do {
        fn_1_BC8();
    } while (lbl_1_bss_610.unk04 != NULL);
    fn_1_7384(lbl_1_bss_548[lbl_1_bss_688.unk00].unk00->model[1], lbl_1_bss_688.unk30[lbl_1_bss_688.unk00].unk10, 1, 20, 1);
    lbl_1_bss_78[1] = HuAudSeqPlay(6);
    fn_1_BE8(30);
    fn_1_1DFC(lbl_1_bss_610.unk00, 1, 4, 30, 0);
    fn_1_BE8(30);
    lbl_1_bss_688.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_688.unk0C);
    HuAudFXPlay(lbl_1_data_0[6][0]);
    HuWinAttrSet(lbl_1_bss_688.unk04, 0x400);
    HuWinMesSet(lbl_1_bss_688.unk04, 0x1F000B);
    fn_1_2264(lbl_1_bss_610.unk00, 1, 4, 10);
    fn_1_1DFC(lbl_1_bss_610.unk00, 1, 1, 10, 1);
    HuWinAttrReset(lbl_1_bss_688.unk04, 0x400);
    HuWinKeyWaitEntry(lbl_1_bss_688.unk04);
    fn_1_BC8();
    fn_1_1AFC(lbl_1_bss_688.unk04, -1);
    fn_1_1D18(lbl_1_bss_688.unk04, 0x250004);
    fn_1_1A94(lbl_1_bss_688.unk04);
    fn_1_BE8(60);
    fn_1_E638();
    Hu3DModelAttrReset(lbl_1_bss_638.unk00->model[5], 1);
    Hu3DModelAttrReset(lbl_1_bss_638.unk00->model[6], 1);
    fn_1_1DFC(lbl_1_bss_610.unk00, 1, 4, 15, 1);
    fn_1_1DFC(lbl_1_bss_638.unk00, 2, 3, 0, 0);
    fn_1_BE8(45);
    HuAudFXPlay(lbl_1_data_0[6][0]);
    fn_1_BE8(15);
    fn_1_1DFC(lbl_1_bss_548[lbl_1_bss_688.unk00].unk00, 1, 5, 0, 0);
    fn_1_BC8();
    fn_1_7384(lbl_1_bss_548[lbl_1_bss_688.unk00].unk00->model[1], lbl_1_bss_688.unk30[lbl_1_bss_688.unk00].unk10, 1, 10, 0);
    fn_1_2264(lbl_1_bss_638.unk00, 2, 3, 0);
    HuAudSeqFadeOut(lbl_1_bss_78[1], 3000);
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_1218C);
    fn_1_BE8(150);
}

void fn_1_F838(void) { }

void fn_1_F83C(void)
{
    fn_1_BE8(60);
    HuAudSeqFadeOut(lbl_1_bss_78[0], 1000);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    CharModelKill(-1);
    HuAudFadeOut(1);
    omOvlReturnEx(1, 1);
}

void fn_1_F8B4(omObjData *arg0, StructBss16C *arg1)
{
    int mode = 0;
    int i;
    fn_1_EFCC();
    fn_1_F028();
    fn_1_F150();
    lbl_1_bss_688.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_688.unk0C);
    while (1) {
        fn_1_BC8();
        if (fn_1_F22C()) {
            mode = 0;
            break;
        }
        else if (fn_1_F2FC()) {
            mode = 1;
            break;
        }
    }

    fn_1_1A94(lbl_1_bss_688.unk04);
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_688.unk30[i].unk00 != lbl_1_bss_688.unk30[lbl_1_bss_688.unk00].unk00) {
            Hu3DModelAttrSet(lbl_1_bss_548[i].unk00->model[1], 1);
        }
        Hu3DModelAttrSet(lbl_1_bss_548[i].unk00->model[2], 1);
    }
    switch (mode) {
        case 0:
            fn_1_F3D0();
            break;
        case 1:
            break;
    }
    switch (mode) {
        case 0:
            fn_1_E8EC();
            break;

        case 1:
            fn_1_F83C();
            break;
    }
    arg1->unk04 = NULL;
}

void fn_1_FDFC(void)
{
    omObjData *obj;
    lbl_1_bss_660.unk00 = obj = omAddObjEx(lbl_1_bss_4E0, 256, 16, 16, -1, NULL);
    lbl_1_bss_660.unk04 = (void *)fn_1_F8B4;
    lbl_1_bss_660.unk00->data = &lbl_1_bss_660;
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_660.unk04 != NULL) {
            lbl_1_bss_660.unk04(obj, &lbl_1_bss_660);
        }
    }
}

void fn_1_FEB0(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(0x660052);
    object->motion[1] = Hu3DMotionIDGet(object->model[1]);
    Hu3DModelShadowMapObjSet(object->model[1], "base_story-base");
    fn_1_1DFC(object, 1, 1, 0, 1);
    object->model[2] = Hu3DModelCreateFile(0x660053);
    object->motion[2] = Hu3DJointMotionFile(object->model[2], 0x660054);
    object->motion[3] = Hu3DJointMotionFile(object->model[2], 0x660055);
    fn_1_1DFC(object, 2, 2, 0, 2);
    object->model[5] = Hu3DModelCreateFile(0x660057);
    object->motion[5] = Hu3DMotionIDGet(object->model[5]);
    Hu3DModelPosSet(object->model[5], 0, 80, 460);
    Hu3DModelAttrSet(object->model[5], 1);
    Hu3DModelShadowSet(object->model[5]);
    fn_1_1DFC(object, 5, 5, 0, 2);
    object->model[6] = Hu3DModelCreateFile(0x660058);
    object->motion[6] = Hu3DMotionIDGet(object->model[6]);
    Hu3DModelHookSet(object->model[5], "koopabox_fix-effect_fook2", object->model[6]);
    Hu3DModelAttrSet(object->model[6], 1);
    fn_1_1DFC(object, 6, 6, 0, 2);
}

void fn_1_100D8(omObjData *arg0, StructBss16C *arg1)
{
    Hu3DData[arg0->model[5]].pos.y = fn_1_B08(80, 90, arg1->unk08++, 360);
    if (arg1->unk08 >= 360) {
        arg1->unk08 = 0;
    }
}

void fn_1_10194(void)
{
    omObjData *obj;
    lbl_1_bss_638.unk00 = obj = omAddObjEx(lbl_1_bss_4E0, 256, 16, 16, -1, NULL);
    lbl_1_bss_638.unk04 = (void *)fn_1_100D8;
    lbl_1_bss_638.unk00->data = &lbl_1_bss_638;
    fn_1_FEB0(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_638.unk04 != NULL) {
            lbl_1_bss_638.unk04(obj, &lbl_1_bss_638);
        }
    }
}

void fn_1_10448(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(0x660062);
    object->motion[1] = Hu3DJointMotionFile(object->model[1], 0x660063);
    object->motion[2] = Hu3DJointMotionFile(object->model[1], 0x660065);
    object->motion[3] = Hu3DJointMotionFile(object->model[1], 0x660069);
    object->motion[4] = Hu3DJointMotionFile(object->model[1], 0x660066);
    Hu3DModelPosSet(object->model[1], -180, 0, 800);
    Hu3DModelRotSet(object->model[1], 0, 60, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelAttrSet(object->model[1], 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
}

void fn_1_10604(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_610.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_610.unk00->work[0] = arg4;
    lbl_1_bss_610.unk00->work[1] = arg1;
    lbl_1_bss_610.unk00->work[2] = arg2 + 1;
}

void fn_1_106B0(omObjData *arg0, StructBss16C *arg1)
{
    int i = 0;
    float speed = 50;

    HuAudFXPlay(153);
    fn_1_10604(2, 1, 0, 0, 1);
    fn_1_BE8(5);
    Hu3DMotionTimeSet(lbl_1_bss_610.unk00->model[1], 100);
    fn_1_BC8();
    Hu3DModelAttrReset(arg0->model[1], 1);
    while (1) {
        fn_1_BC8();
        if (Hu3DMotionTimeGet(lbl_1_bss_610.unk00->model[1]) >= 137) {
            break;
        }
    }
    HuAudFXPlay(156);
    omVibrate(lbl_1_bss_688.unk0C, 45, 12, 0);
    fn_1_67D8(lbl_1_bss_548[lbl_1_bss_688.unk00].unk00, 6, 1, 5, 0);
    for (i = 0; i < 60; i++) {
        float posY;
        fn_1_BC8();
        posY = fn_1_B08(0, speed, i % 15, 15);
        speed = fn_1_88C(speed, 0, 30);
        lbl_1_bss_688.unk100 = fn_1_88C(lbl_1_bss_688.unk100, posY, 5);
    }
    lbl_1_bss_688.unk100 = 0;
    arg1->unk04 = NULL;
}

void fn_1_1094C(void)
{
    omObjData *obj;
    lbl_1_bss_610.unk00 = obj = omAddObjEx(lbl_1_bss_4E0, 256, 16, 16, -1, NULL);
    lbl_1_bss_610.unk04 = NULL;
    lbl_1_bss_610.unk00->data = &lbl_1_bss_638;
    fn_1_10448(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_610.unk04 != NULL) {
            lbl_1_bss_610.unk04(obj, &lbl_1_bss_610);
        }
        if (obj->work[0]) {
            if (obj->work[2]) {
                obj->work[2]--;
            }
            else if (obj->work[2] == 0 && Hu3DMotionEndCheck(obj->model[1])) {
                fn_1_1DFC(obj, 1, obj->work[1], 15, 1);
                obj->work[0] = obj->work[1] = obj->work[2] = 0;
            }
        }
    }
}

void fn_1_10C00(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(0x66007D);
    object->motion[1] = Hu3DJointMotionFile(object->model[1], 0x66007E);
    object->motion[2] = Hu3DJointMotionFile(object->model[1], 0x660080);
    object->motion[3] = Hu3DJointMotionFile(object->model[1], 0x660081);
    object->motion[4] = Hu3DJointMotionFile(object->model[1], 0x660084);
    object->motion[5] = Hu3DJointMotionFile(object->model[1], 0x660085);
    Hu3DModelPosSet(object->model[1], -300, 0, 890);
    Hu3DModelRotSet(object->model[1], 0, 30, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
    CharModelEffectNpcInit(object->model[1], object->motion[2], 1, 13);
}

void fn_1_10DF4(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_5E8.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_5E8.unk00->work[0] = arg4;
    lbl_1_bss_5E8.unk00->work[1] = arg1;
    lbl_1_bss_5E8.unk00->work[2] = arg2 + 1;
}

void fn_1_10EA0(omObjData *arg0, StructBss16C *arg1)
{
    Vec pos = { -600, 0, 800 };
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, -90, 60, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_10F84(omObjData *arg0, StructBss16C *arg1)
{
    int i;
    for (i = 0; i < 15; i++) {
        fn_1_BC8();
        Hu3DData[arg0->model[1]].rot.y = fn_1_864(0, 135, i, 15);
    }
    arg1->unk04 = NULL;
}

void fn_1_11048(omObjData *arg0, StructBss16C *arg1)
{
    Vec pos = { -120, 0, 800 };
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, 60, 60, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_1112C(void)
{
    omObjData *obj;
    lbl_1_bss_5E8.unk00 = obj = omAddObjEx(lbl_1_bss_4E0, 256, 16, 16, -1, NULL);
    lbl_1_bss_5E8.unk04 = NULL;
    lbl_1_bss_5E8.unk00->data = &lbl_1_bss_5E8;
    fn_1_10C00(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_5E8.unk04 != NULL) {
            lbl_1_bss_5E8.unk04(obj, &lbl_1_bss_5E8);
        }
        if (obj->work[0]) {
            if (obj->work[2]) {
                obj->work[2]--;
            }
            else if (obj->work[2] == 0 && Hu3DMotionEndCheck(obj->model[1])) {
                fn_1_1DFC(obj, 1, obj->work[1], 15, 1);
                obj->work[0] = obj->work[1] = obj->work[2] = 0;
            }
        }
    }
}

void fn_1_11418(int arg0)
{
    int i;
    int order[4];
    order[0] = 0;
    for (i = 1; i < 4; i++) {
        order[i] = order[i - 1] + 1;
        if (order[i] >= 4) {
            order[i] = 0;
        }
        if (arg0 == order[i]) {
            lbl_1_bss_688.unk00 = i;
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_357C(&lbl_1_bss_688.unk30[i], order[i]);
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_688.unk30[i].unk18 = GWPlayer[order[i]].rank + 1;
    }
}

Vec lbl_1_data_81C[4] = {
    { -300, 0, 460 },
    { -100, -30, 460 },
    { 100, -60, 460 },
    { 300, -90, 460 },
};

void fn_1_1154C(omObjData *object, int player)
{
    int playerNo = player;
    int charNo = lbl_1_bss_688.unk30[playerNo].unk10;
    object->model[1] = CharModelCreate(charNo, 4);
    object->motion[1] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
    object->motion[2] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03));
    object->motion[3] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05));
    object->motion[4] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1A));
    object->motion[5] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x6D));
    object->motion[6] = Hu3DJointMotionFile(object->model[1], 0x660018 + charNo);
    CharModelMotionDataClose(charNo);
    Hu3DModelPosSet(
        object->model[1], lbl_1_data_81C[playerNo].x, lbl_1_data_81C[lbl_1_bss_688.unk30[playerNo].unk18 - 1].y + 90, lbl_1_data_81C[playerNo].z);
    Hu3DModelRotSet(object->model[1], 0, 0, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
    object->model[2] = Hu3DModelCreateFile(0x660056);
    Hu3DModelPosSet(
        object->model[2], lbl_1_data_81C[playerNo].x, lbl_1_data_81C[lbl_1_bss_688.unk30[playerNo].unk18 - 1].y, lbl_1_data_81C[playerNo].z);
    if (lbl_1_bss_688.unk30[playerNo].unk18 == 4) {
        Hu3DModelAttrSet(object->model[2], 1);
    }
    Hu3DModelScaleSet(object->model[2], 1.5, 1, 1.5);
    Hu3DModelShadowMapSet(object->model[2]);
}

void fn_1_11838(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_548[lbl_1_bss_688.unk00].unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_548[lbl_1_bss_688.unk00].unk00->work[0] = arg4;
    lbl_1_bss_548[lbl_1_bss_688.unk00].unk00->work[1] = arg1;
    lbl_1_bss_548[lbl_1_bss_688.unk00].unk00->work[2] = arg2 + 1;
}

void fn_1_11934(omObjData *arg0, StructBss16C *arg1)
{
    float posY = Hu3DData[arg0->model[1]].pos.y;
    int i;
    for (i = 0; i < 60; i++) {
        fn_1_BC8();
        Hu3DData[arg0->model[1]].pos.y = fn_1_984(posY, 0, i, 60);
        Hu3DData[arg0->model[2]].pos.y = fn_1_984(posY - 90, -90, i, 60);
    }
    Hu3DModelAttrSet(arg0->model[2], 1);
    arg1->unk04 = NULL;
}

void fn_1_11A98(omObjData *arg0, StructBss16C *arg1)
{
    Vec pos = { 120, 0, 800 };
    lbl_1_bss_5E8.unk04 = (void *)fn_1_11048;
    fn_1_1DFC(lbl_1_bss_638.unk00, 2, 2, 0, 0);
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, -60, 30, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_11BB0(void)
{
    omObjData *obj;
    int playerNo = lbl_1_bss_688.unk10++;
    lbl_1_bss_548[playerNo].unk00 = obj = omAddObjEx(lbl_1_bss_4E0, 256, 16, 16, -1, NULL);
    lbl_1_bss_548[playerNo].unk04 = NULL;
    lbl_1_bss_548[playerNo].unk00->data = &lbl_1_bss_548[0];
    fn_1_1154C(obj, playerNo);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_548[playerNo].unk04 != NULL) {
            lbl_1_bss_548[playerNo].unk04(obj, &lbl_1_bss_548[playerNo]);
        }
        if (obj->work[0]) {
            if (obj->work[2]) {
                obj->work[2]--;
            }
            else if (obj->work[2] == 0 && Hu3DMotionEndCheck(obj->model[1])) {
                fn_1_1DFC(obj, 1, obj->work[1], 15, 1);
                obj->work[0] = obj->work[1] = obj->work[2] = 0;
            }
        }
    }
}

void fn_1_11FD0(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    work->unk08.x = 0;
    work->unk08.y = 170;
    work->unk08.z = 0;
    work->unk20.x = -5;
    work->unk20.y = 0;
    work->unk20.z = 0;
    work->unk38 = 1700;
}

void fn_1_1205C(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    StructBss24 temp;
    temp.unk08.x = 0;
    temp.unk08.y = 125;
    temp.unk08.z = 0;
    temp.unk20.x = -5;
    temp.unk20.y = 0;
    temp.unk20.z = 0;
    temp.unk38 = 1750;
    fn_1_4FEC(work, &temp, work->unk40++, 60, 30);
    if (0.0f != lbl_1_bss_688.unk100) {
        work->unk08.y = lbl_1_bss_688.unk100 + 125;
    }
}

void fn_1_1218C(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    StructBss24 temp;
    if (work->unk40 == 50) {
        fn_1_1DFC(lbl_1_bss_638.unk00, 5, 5, 0, 0);
        fn_1_1DFC(lbl_1_bss_638.unk00, 6, 6, 0, 0);
        HuAudFXPlay(161);
    }
    temp.unk08.x = 0;
    temp.unk08.y = 100;
    temp.unk08.z = 460;
    temp.unk20.x = 0;
    temp.unk20.y = 0;
    temp.unk20.z = 0;
    temp.unk38 = 125;
    fn_1_4FEC(work, &temp, work->unk40, 180, 10);
    if (work->unk40++ >= 90) {
        if (work->unk40 == 91) {
            lbl_1_bss_88[0] = HuAudFXPlay(32);
        }
        work->unk20.x = fn_1_864(work->unk20.x, -45, work->unk40 - 90, 90);
        Hu3DData[lbl_1_bss_638.unk00->model[5]].rot.x = fn_1_864(0, 45, work->unk40 - 90, 90);
    }
}
