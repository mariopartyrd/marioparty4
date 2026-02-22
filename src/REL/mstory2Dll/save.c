#include "REL/mstory2Dll.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

s32 lbl_1_bss_D14;
Process *lbl_1_bss_D10;

s32 fn_1_1B560(s32 arg0)
{
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

void fn_1_1B64C(void)
{
    float sp8[2];
    s32 temp_r30;
    s32 var_r29;
    s32 var_r31;

    temp_r30 = 1;
    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    if (SLSaveFlagGet() == 0) {
        lbl_1_bss_D14 = 1;
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
#if VERSION_REV1
            GWGameStat.story_continue = 1;
#endif
            if (omovlstat) {
                GWGameStat.story_continue = 0;
            }
            SLCommonSet();
            SLSaveBoardStory();
            SLSave();
        }
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_D14 = 1;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_1B870(void)
{
    _SetFlag(9);
    HuPrcChildCreate(fn_1_1B64C, 100, 0x2000, 0, HuPrcCurrentGet());
    do {
        fn_1_BC8();
    } while (lbl_1_bss_D14 != 1);
    if (omovlstat == 0) {
        omOvlGotoEx(OVL_MSTORY2, 1, 4, 0);
    }
    else {
        omOvlReturnEx(omovlhisidx, 1);
    }
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_1B90C(Process *arg0)
{
    lbl_1_bss_D10 = arg0;
    HuPrcChildCreate(fn_1_1B870, 100, 0x2000, 0, HuPrcCurrentGet());
}
