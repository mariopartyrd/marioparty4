#include "REL/mstory2Dll.h"
#include "game/armem.h"
#include "game/board/main.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#ifndef __MWERKS__
#include "game/audio.h"
#include "game/saveload.h"
#include "game/thpmain.h"
#endif

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
} StructBssC0C; // Size 0x104

StructBssC0C lbl_1_bss_C0C;
StructBss16C lbl_1_bss_BE4;
StructBss16C lbl_1_bss_BBC;
StructBss16C lbl_1_bss_B94;
StructBss16C lbl_1_bss_B6C;
StructBss16C lbl_1_bss_B44;
BOOL lbl_1_bss_B40;
BOOL lbl_1_bss_B3C;
Process *lbl_1_bss_B38;

s32 lbl_1_data_EF8[2][2] = { 20, 70, 1, 1 };
s32 lbl_1_data_F08 = -1;
s32 lbl_1_data_F0C[2] = { -1, -1 };
s32 lbl_1_data_F14 = 127;

void fn_1_19F14(void);
void fn_1_1A160(void);
void fn_1_1A538(omObjData *arg0, StructBss16C *arg1);
void fn_1_1A578(void);
void fn_1_1A9D0(omObjData *arg0, StructBss16C *arg1);
void fn_1_1AAB4(void);
void fn_1_1AFD4(omObjData *arg0, StructBss16C *arg1);
void fn_1_1B0E4(void);
void fn_1_1AD3C(int arg0);
void fn_1_1B318(void);
void fn_1_1B3A4(void);
void fn_1_1B430(void);

void fn_1_186D0(void)
{
    int i;
    while (1) {
        HuPrcVSleep();
        if (lbl_1_data_F08 != -1 && lbl_1_data_F0C[0] != -1 && lbl_1_data_F0C[1] != -1 && lbl_1_data_F0C[0] == Hu3DMotionIDGet(lbl_1_data_F08)) {
            for (i = 0; i < 2; i++) {
                if (lbl_1_data_EF8[1][i] != -1) {
                    if (Hu3DMotionTimeGet(lbl_1_data_F08) >= lbl_1_data_EF8[0][i]) {
                        OSReport("KE-System  TIME:%d\n", lbl_1_data_EF8[0][i]);
                        HuAudFXPlayVol(81, lbl_1_data_F14);
                        lbl_1_data_EF8[1][i] = -1;
                    }
                }
            }
            if (Hu3DMotionTimeGet(lbl_1_data_F08) <= 10) {
                for (i = 0; i < 2; i++) {
                    lbl_1_data_EF8[1][i] = 1;
                }
            }
        }
        if (lbl_1_bss_B3C == 1) {
            lbl_1_data_F14--;
            if (lbl_1_data_F14 <= 0) {
                lbl_1_data_F14 = 0;
            }
        }
        if (lbl_1_bss_B3C == 2) {
            break;
        }
    }
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_188F0(Process *arg0, s32 arg1)
{
    lbl_1_bss_B38 = arg0;
    if (GWSystem.diff_story == 2) {
        GWGameStat.field10E_bit4 = TRUE;
    }
    lbl_1_bss_C0C.unk0C = arg1;
    fn_1_C30();
    fn_1_3668(255);
    fn_1_2828(lbl_1_bss_B38, fn_1_1B318);
    fn_1_3754();
    fn_1_1AD3C(arg1);
    HuPrcChildCreate(fn_1_1B0E4, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_1A160, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_1AAB4, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_1A578, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_19F14, 100, 12288, 0, HuPrcCurrentGet());
}

void fn_1_18A34(omObjData *object)
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

void fn_1_18AC0(void)
{
    int posX = 16;
    int posY = 40;
    GXColor winColor = { 0, 0, 128, 128 };
    int i;
    while (1) {
        fn_1_BC8();
        fontcolor = FONT_COLOR_WHITE;
        printWin(posX, posY, 220, 130, &winColor);
        if (lbl_1_bss_BE4.unk04 == NULL) {
            print8(posX, posY, 1, "PROC_MAIN   -> FALSE");
        }
        else {
            print8(posX, posY, 1, "PROC_MAIN   -> TRUE");
        }
        if (lbl_1_bss_BBC.unk04 == NULL) {
            print8(posX, posY + 10, 1, "PROC_MAP    -> FALSE");
        }
        else {
            print8(posX, posY + 10, 1, "PROC_MAP    -> TRUE");
        }
        if (lbl_1_bss_B94.unk04 == NULL) {
            print8(posX, posY + 20, 1, "PROC_PLAYER -> FALSE");
        }
        else {
            print8(posX, posY + 20, 1, "PROC_PLAYER -> TRUE");
        }
        if (lbl_1_bss_B6C.unk04 == NULL) {
            print8(posX, posY + 30, 1, "PROC_SUB    -> FALSE");
        }
        else {
            print8(posX, posY + 30, 1, "PROC_SUB    -> TRUE");
        }
        if (lbl_1_bss_B44.unk04 == NULL) {
            print8(posX, posY + 40, 1, "PROC_KOOPA  -> FALSE");
        }
        else {
            print8(posX, posY + 40, 1, "PROC_KOOPA  -> TRUE");
        }

        print8(posX, posY + 60, 1, "P:%d W:%d", lbl_1_bss_C0C.unk00, lbl_1_bss_C0C.unk0C);
        print8(posX, posY + 80, 1, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(posX, posY + 90 + (i * 10), 1, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i, lbl_1_bss_C0C.unk30[i].unk00, lbl_1_bss_C0C.unk30[i].unk04,
                lbl_1_bss_C0C.unk30[i].unk08, lbl_1_bss_C0C.unk30[i].unk0C, lbl_1_bss_C0C.unk30[i].unk14, lbl_1_bss_C0C.unk30[i].unk10);
        }
    }
}

void fn_1_18E7C(void)
{
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    fn_1_BE8(60);
}

void fn_1_18EC4(void)
{
    lbl_1_bss_C0C.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_C0C.unk0C);
    HuAudFXPlay(lbl_1_data_0[6][1]);
    fn_1_1D18(lbl_1_bss_C0C.unk04, 0x1F001E);
    fn_1_1AFC(lbl_1_bss_C0C.unk04, -1);
    fn_1_1D18(lbl_1_bss_C0C.unk04, 0x250004);
    fn_1_1A94(lbl_1_bss_C0C.unk04);
    lbl_1_bss_B44.unk04 = (void *)fn_1_1A538;
    lbl_1_bss_B3C = 1;
    fn_1_BE8(60);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    fn_1_BE8(60);
    lbl_1_bss_B44.unk04 = NULL;
    lbl_1_bss_B3C = 2;
    fn_1_1DFC(lbl_1_bss_B44.unk00, 1, 1, 0, 1);
    fn_1_2750(fn_1_1B3A4);
    Hu3DModelAttrReset(lbl_1_bss_BBC.unk00->model[1], 1);
    Hu3DModelAttrReset(lbl_1_bss_BBC.unk00->model[2], 1);
    Hu3DModelAttrReset(lbl_1_bss_BBC.unk00->model[4], 1);
    Hu3DModelAttrReset(lbl_1_bss_B6C.unk00->model[1], 1);
    Hu3DModelAttrReset(lbl_1_bss_B94.unk00->model[1], 1);
    Hu3DModelAttrSet(lbl_1_bss_B44.unk00->model[1], 1);
    Hu3DModelPosSet(lbl_1_bss_BBC.unk00->model[1], 0, 0, 0);
    fn_1_BE8(60);
    lbl_1_bss_78[0] = HuAudSeqPlay(56);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    if (0) {
        fn_1_BC8();
    }
}

void fn_1_19138(void)
{
    fn_1_1DFC(lbl_1_bss_BBC.unk00, 2, 3, 0, 0);
    fn_1_2264(lbl_1_bss_BBC.unk00, 2, 3, 0);
    lbl_1_bss_B94.unk04 = (void *)fn_1_1AFD4;
    lbl_1_bss_B6C.unk04 = (void *)fn_1_1A9D0;
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_1B430);
    fn_1_BE8(30);
    fn_1_1DFC(lbl_1_bss_BBC.unk00, 2, 2, 0, 0);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_B94.unk04 == NULL) {
            break;
        }
    }
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_B6C.unk04 == NULL) {
            break;
        }
    }
    lbl_1_bss_C0C.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_C0C.unk0C);
    HuAudFXPlay(lbl_1_data_0[0][2]);
    fn_1_1DFC(lbl_1_bss_B6C.unk00, 1, 3, 15, 1);
    fn_1_1D18(lbl_1_bss_C0C.unk04, 0x1F001F);
    fn_1_1AFC(lbl_1_bss_C0C.unk04, -1);
    fn_1_1D18(lbl_1_bss_C0C.unk04, 0x1F0020);
    fn_1_1AFC(lbl_1_bss_C0C.unk04, -1);
    fn_1_1D18(lbl_1_bss_C0C.unk04, 0x250004);
    fn_1_1DFC(lbl_1_bss_B6C.unk00, 1, 1, 15, 1);
    fn_1_1A94(lbl_1_bss_C0C.unk04);
    fn_1_BE8(60);
}

char *lbl_1_data_10E4[8] = { "movie/endmov_ma0.thp", "movie/endmov_lu0.thp", "movie/endmov_pe0.thp", "movie/endmov_yo0.thp", "movie/endmov_wa0.thp",
    "movie/endmov_do0.thp", "movie/endmov_da0.thp", "movie/endmov_wl0.thp" };

void fn_1_19334(void)
{
    lbl_1_bss_C0C.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_C0C.unk0C);
    HuAudFXPlay(lbl_1_data_0[0][2]);
    fn_1_1DFC(lbl_1_bss_B6C.unk00, 1, 3, 0, 1);
    fn_1_1D4C(lbl_1_bss_C0C.unk04, lbl_1_bss_C0C.unk30[lbl_1_bss_C0C.unk00].unk10, 0);
    fn_1_1D18(lbl_1_bss_C0C.unk04, 0x1F0024);
    fn_1_1AFC(lbl_1_bss_C0C.unk04, -1);
    fn_1_1D18(lbl_1_bss_C0C.unk04, 0x250004);
    fn_1_1DFC(lbl_1_bss_B6C.unk00, 1, 1, 0, 1);
    fn_1_1A94(lbl_1_bss_C0C.unk04);
    fn_1_1DFC(lbl_1_bss_B94.unk00, 1, 4, 15, 0);
    fn_1_2264(lbl_1_bss_B94.unk00, 1, 4, 15);
    fn_1_1DFC(lbl_1_bss_B94.unk00, 1, 3, 15, 1);
    fn_1_BE8(60);
    lbl_1_bss_C0C.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_C0C.unk0C);
    fn_1_1DFC(lbl_1_bss_B6C.unk00, 1, 3, 0, 1);
    fn_1_6D78(lbl_1_bss_C0C.unk04, 0x1F0023, 0, -1);
    fn_1_1D18(lbl_1_bss_C0C.unk04, 0x250004);
    fn_1_1DFC(lbl_1_bss_B6C.unk00, 1, 1, 0, 1);
    HuAudFXPlay(lbl_1_data_0[0][3]);
    fn_1_1A94(lbl_1_bss_C0C.unk04);
    fn_1_BE8(60);
    HuAudFXPlay(152);
    Hu3DModelAttrSet(lbl_1_bss_BBC.unk00->model[1], 1);
    Hu3DModelAttrSet(lbl_1_bss_BBC.unk00->model[2], 1);
    Hu3DModelAttrSet(lbl_1_bss_BBC.unk00->model[4], 1);
    Hu3DModelAttrSet(lbl_1_bss_B6C.unk00->model[1], 1);
    Hu3DModelAttrSet(lbl_1_bss_B94.unk00->model[1], 1);
    HuAudSeqFadeOut(lbl_1_bss_78[0], 100);
    lbl_1_bss_B3C = 2;
    GWGameStat.field10E_bit6 = TRUE;
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    lbl_1_bss_BBC.unk04 = NULL;
    lbl_1_bss_B94.unk04 = NULL;
    lbl_1_bss_B44.unk04 = NULL;
    lbl_1_bss_B6C.unk04 = NULL;

    CharModelKill(-1);
    Hu3DAllKill();
    fn_1_BE8(60);
    {
        int time = 0;
#if VERSION_PAL
        s32 languageOffset = 0;
#endif
        int gid = HuSprGrpCreate(3);
        int sprid = HuTHPSprCreate(lbl_1_data_10E4[lbl_1_bss_C0C.unk30[lbl_1_bss_C0C.unk00].unk10], FALSE, 1000);
        HuSprGrpMemberSet(gid, 0, sprid);
        HuSprPosSet(gid, 0, 288, 240);
#if VERSION_PAL
        switch (GWGameStat.language) {
            case 2:
                languageOffset = 1;
                break;
            case 3:
                languageOffset = 2;
                break;
            case 4:
                languageOffset = 3;
                break;
            case 5:
                languageOffset = 4;
                break;
        }
        sprid = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x60) + languageOffset, MEMORY_DEFAULT_NUM)), 950, 0);
#else
        sprid = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x60), MEMORY_DEFAULT_NUM)), 950, 0);
#endif
        HuSprGrpMemberSet(gid, 1, sprid);
        HuSprPosSet(gid, 1, 288, 226);
        HuSprAttrSet(gid, 1, HUSPR_ATTR_DISPOFF);
        sprid = HuSprCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x61 : 0x65), MEMORY_DEFAULT_NUM)), 950, 0);
        HuSprGrpMemberSet(gid, 2, sprid);
        HuSprBankSet(gid, 2, lbl_1_bss_C0C.unk30[lbl_1_bss_C0C.unk00].unk10);
        if (GWLanguageGet() == 0 && lbl_1_bss_C0C.unk30[lbl_1_bss_C0C.unk00].unk10 == 5) {
            HuSprBankSet(gid, 2, 8);
        }
        HuSprPosSet(gid, 2, 288, 254);
        HuSprAttrSet(gid, 2, HUSPR_ATTR_DISPOFF);
        HuPrcSleep(5);
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        while (!HuTHPEndCheck()) {
            if (time >= (VERSION_NTSC ? 3300 : 2725)) {
                HuSprAttrReset(gid, 1, HUSPR_ATTR_DISPOFF);
                HuSprAttrReset(gid, 2, HUSPR_ATTR_DISPOFF);
            }
            else {
                time++;
            }
            HuPrcVSleep();
        }
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        HuTHPClose();
        HuPrcVSleep();
        HuSprGrpKill(gid);
    }
}

void fn_1_199A0(void)
{
    float sp8[2];
    s32 temp_r30;
    s32 var_r29;
    s32 var_r31;
    s32 var_r28;
    temp_r30 = 1;
    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    if (SLSaveFlagGet() == 0) {
        lbl_1_bss_B40 = 1;
        HuPrcEnd();
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    espInit();
    HuPrcVSleep();
    var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_WIN, 32), 5000, 0);
    espPosSet(var_r29, 288.0f, 240.0f);
    espAttrReset(var_r29, 4);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_BE8(60);
    var_r28 = GWUnkB1Get();
    GWSystem.unk0B |= 1 << var_r28;
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
            GWGameStat.story_continue = FALSE;
            SLCommonSet();
            SLSaveBoardStory();
            SLSave();
        }
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_B40 = 1;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_19BE8(void)
{
    omOvlHisData *his;
    fn_1_BE8(120);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    CharModelKill(-1);
    HuAudFadeOut(1);
    his = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MSTORY2, 20, 1);
    omOvlCallEx(OVL_STAFF, 1, 0, 0);
    while (1) {
        fn_1_BC8();
    }
}

void fn_1_19C6C(omObjData *arg0, StructBss16C *arg1)
{
    int temp = 0;
    fn_1_18E7C();
    fn_1_18EC4();
    fn_1_19138();
    fn_1_19334();
    fn_1_19BE8();
    arg1->unk04 = NULL;
}

void fn_1_19F14(void)
{
    omObjData *obj;
    lbl_1_bss_BE4.unk00 = obj = omAddObjEx(lbl_1_bss_B38, 256, 16, 16, -1, NULL);
    lbl_1_bss_BE4.unk04 = (void *)fn_1_19C6C;
    lbl_1_bss_BE4.unk00->data = &lbl_1_bss_BE4;
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_BE4.unk04 != NULL) {
            lbl_1_bss_BE4.unk04(obj, &lbl_1_bss_BE4);
        }
    }
}

void fn_1_19FC8(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x50));
    object->motion[0] = Hu3DMotionIDGet(object->model[1]);
    fn_1_1DFC(object, 1, 0, 0, 2);
    Hu3DModelShadowMapObjSet(object->model[1], "base_fix9-base");
    Hu3DModelAttrSet(object->model[1], 1);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x53));
    object->motion[2] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x54));
    object->motion[3] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x55));
    Hu3DModelAttrSet(object->model[2], 1);
    fn_1_1DFC(object, 2, 3, 0, 2);
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x51));
    Hu3DModelAttrSet(object->model[4], 1);
    Hu3DModelPosSet(object->model[1], 0, -1000, 0);
}

void fn_1_1A160(void)
{
    omObjData *obj;
    lbl_1_bss_BBC.unk00 = obj = omAddObjEx(lbl_1_bss_B38, 256, 16, 16, -1, NULL);
    lbl_1_bss_BBC.unk04 = NULL;
    fn_1_19FC8(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_BBC.unk04 != NULL) {
            lbl_1_bss_BBC.unk04(obj, &lbl_1_bss_BBC);
        }
    }
}

void fn_1_1A368(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x62 : 0x66));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x63 : 0x67));
    object->motion[2] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x70 : 0x71));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x71 : 0x72));
    Hu3DModelPosSet(object->model[1], 0, 0, 600);
    Hu3DModelRotSet(object->model[1], 0, 180, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    fn_1_1DFC(object, 1, 3, 0, 1);
    lbl_1_data_F08 = object->model[1];
    lbl_1_data_F0C[0] = object->motion[3];
    lbl_1_data_F0C[1] = object->motion[3];
    HuPrcChildCreate(fn_1_186D0, 100, 8192, 0, HuPrcCurrentGet());
}

void fn_1_1A538(omObjData *arg0, StructBss16C *arg1)
{
    Hu3DData[lbl_1_bss_B44.unk00->model[1]].pos.z -= 2.5f;
}

void fn_1_1A578(void)
{
    omObjData *obj;
    lbl_1_bss_B44.unk00 = obj = omAddObjEx(lbl_1_bss_B38, 256, 16, 16, -1, NULL);
    lbl_1_bss_B44.unk04 = NULL;
    fn_1_1A368(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_B44.unk04 != NULL) {
            lbl_1_bss_B44.unk04(obj, &lbl_1_bss_B44);
        }
        if (obj->work[0]) {
            fn_1_6704(obj);
        }
    }
}

void fn_1_1A7CC(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x72 : 0x73));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x73 : 0x74));
    object->motion[2] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x75));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x76));
    object->motion[4] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x7C : 0x7A));
    object->motion[5] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x79 : 0x77));
    Hu3DModelPosSet(object->model[1], 0, 0, 460);
    Hu3DModelRotSet(object->model[1], 0, 0, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelAttrSet(object->model[1], 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 5, 0, 1);
    CharModelEffectNpcInit(object->model[1], object->motion[2], 1, 9);
}

void fn_1_1A9D0(omObjData *arg0, StructBss16C *arg1)
{
    Vec pos = { -120, 0, 800 };
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, 90, 60, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_1AAB4(void)
{
    omObjData *obj;
    lbl_1_bss_B6C.unk00 = obj = omAddObjEx(lbl_1_bss_B38, 256, 16, 16, -1, NULL);
    lbl_1_bss_B6C.unk04 = NULL;
    fn_1_1A7CC(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_B6C.unk04 != NULL) {
            lbl_1_bss_B6C.unk04(obj, &lbl_1_bss_B6C);
        }
        if (obj->work[0]) {
            fn_1_6704(obj);
        }
    }
}

void fn_1_1AD3C(int arg0)
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
            lbl_1_bss_C0C.unk00 = i;
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_357C(&lbl_1_bss_C0C.unk30[i], order[i]);
    }
}

void fn_1_1AE20(omObjData *object)
{
    int charNo = lbl_1_bss_C0C.unk30[lbl_1_bss_C0C.unk00].unk10;
    object->model[1] = CharModelCreate(charNo, 1);
    object->motion[1] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
    object->motion[2] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x35));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x10) + charNo);
    object->motion[4] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x08) + charNo);
    CharModelMotionDataClose(charNo);
    Hu3DModelPosSet(object->model[1], 120, 0, 800);
    Hu3DModelRotSet(object->model[1], 0, -135, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelAttrSet(object->model[1], 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
}

void fn_1_1AFD4(omObjData *arg0, StructBss16C *arg1)
{
    int i;
    fn_1_1DFC(arg0, 1, 2, 0, 0);
    fn_1_BC8();
    Hu3DMotionTimeSet(arg0->model[1], 60);
    for (i = 0; i < 60; i++) {
        fn_1_BC8();
        Hu3DData[arg0->model[1]].rot.y = fn_1_864(-135, -90, i, 60);
    }
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_1B0E4(void)
{
    omObjData *obj;
    lbl_1_bss_B94.unk00 = obj = omAddObjEx(lbl_1_bss_B38, 256, 16, 16, -1, NULL);
    lbl_1_bss_B94.unk04 = NULL;
    fn_1_1AE20(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_B94.unk04 != NULL) {
            lbl_1_bss_B94.unk04(obj, &lbl_1_bss_B94);
        }
        if (obj->work[0]) {
            fn_1_6704(obj);
        }
    }
}

void fn_1_1B318(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    work->unk08.x = 0;
    work->unk08.y = 120;
    work->unk08.z = 0;
    work->unk20.x = 0;
    work->unk20.y = 0;
    work->unk20.z = 0;
    work->unk38 = 1400;
}

void fn_1_1B3A4(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    work->unk08.x = 0;
    work->unk08.y = 125;
    work->unk08.z = 0;
    work->unk20.x = -4.9f;
    work->unk20.y = 0;
    work->unk20.z = 0;
    work->unk38 = 1750;
}

void fn_1_1B430(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    StructBss24 temp;
    temp.unk08.x = 0;
    temp.unk08.y = 100;
    temp.unk08.z = 0;
    temp.unk20.x = 0;
    temp.unk20.y = 0;
    temp.unk20.z = 0;
    temp.unk38 = 1400;
    fn_1_42A0(work, &temp, work->unk40++, 60, 10);
    if (0.0f != lbl_1_bss_C0C.unk100) {
        work->unk08.y = 125 + lbl_1_bss_C0C.unk100;
    }
}
