#include "game/audio.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/present.h"

omObjData *lbl_1_bss_20;

UnkPresentStruct4 lbl_1_data_F0 = { { 0.0f, 3000.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };

void fn_1_3B8C(omObjData *object);
void fn_1_3DB8(omObjData *object);
void fn_1_4040(UnkWindowDataStruct *arg0);
void fn_1_4190(UnkWindowDataStruct *arg0);
void fn_1_41E0(void);
void fn_1_41BC(UnkWindowDataStruct *arg0, s32 arg1);

omObjData *fn_1_39A8(void)
{
    omObjData *object;
    UnkPresentStruct *var_r30;

    object = omAddObjEx(lbl_1_bss_4, 1000, 0, 0, 4, NULL);
    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkPresentStruct), MEMORY_DEFAULT_NUM);
    object->data = var_r30;
    var_r30->unk_04 = 0;
    lbl_1_bss_8 = fn_1_6B4();
    lbl_1_bss_10 = fn_1_1458();
    lbl_1_bss_20 = fn_1_42F4();
    var_r30->unk_00 = fn_1_3EA4(0);
    Hu3DShadowCreate(30.0f, 20.0f, 5000.0f);
    Hu3DShadowTPLvlSet(0.45f);
    Hu3DShadowPosSet(&lbl_1_data_F0.unk_00, &lbl_1_data_F0.unk_0C, &lbl_1_data_F0.unk_18);
    if (omovlevtno > 0) {
        OSReport("*** PRESENTROOM ( PRESENT GET MODE ) ***\n");
        object->func = fn_1_3DB8;
        object->unk10 = 0;
    } else {
        OSReport("*** PRESENTROOM ( PRESENT VIEW MODE ) ***\n");
        object->func = fn_1_3B8C;
        object->unk10 = 0;
    }

    return object;
}

void fn_1_3B18(omObjData *object)
{
    UnkWindowDataStruct **var_r31;

    var_r31 = object->data;
    fn_1_8F0(lbl_1_bss_8);
    fn_1_1784(lbl_1_bss_10);
    fn_1_4534(lbl_1_bss_20);
    fn_1_4040(*var_r31);
    HuMemDirectFree(var_r31);
}

void fn_1_3B8C(omObjData *object)
{
    UnkPresentStruct *var_r30;

    var_r30 = object->data;

    switch (object->unk10) {
    case 0:
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
        object->unk10 = 1;
    case 1:
        if (WipeStatGet()) {
            return;
        }
        object->unk10 = 2;
    case 2:
        fn_1_180C(lbl_1_bss_10, 1);
        object->unk10 = 3;
    case 3:
        if (fn_1_1850(lbl_1_bss_10)) {
            return;
        }
        object->unk10 = 4;
    case 4:
        fn_1_45C0(lbl_1_bss_20, 1);
        object->unk10 = 5;
    case 5:
        if (fn_1_4604(lbl_1_bss_20)) {
            return;
        }
        object->unk10 = 6;
    case 6:
        HuAudFXPlay(66);
        fn_1_4080(var_r30->unk_00);
        fn_1_40B0(var_r30->unk_00, 0x320002);
        object->unk10 = 7;
    case 7:
        if (var_r30->unk_00->unk_20) {
            return;
        }
        fn_1_41BC(var_r30->unk_00, 1);
        object->unk10 = 8;
    case 8:
        if (var_r30->unk_00->unk_20) {
            return;
        }
        fn_1_4098(var_r30->unk_00);
        if (!var_r30->unk_00->choice) {
            var_r30->unk_04 = 0;
            object->unk10 = 11;
            return;
        } else {
            object->unk10 = 9;
            return;
        }
    case 9:
        fn_1_45C0(lbl_1_bss_20, 2);
        object->unk10 = 10;
        return;
    case 10:
        if (fn_1_4604(lbl_1_bss_20)) {
            return;
        }
        object->unk10 = 2;
        return;
    case 11:
        object->unk10 = 12;
        var_r30->unk_04 = 0;
    case 12:
        if (var_r30->unk_00->unk_20) {
            return;
        }
        if (var_r30->unk_04++ >= 60) {
            omSysExitReq = 1;
            object->func = NULL;
            object->unk10 = 0;
        }
    default:
        break;
    }
}

void fn_1_3DB8(omObjData *arg0)
{
    void *sp8;

    sp8 = arg0->data;
    switch (arg0->unk10) {
    case 0:
        fn_1_186C(lbl_1_bss_10, omovlevtno - 1);
        arg0->unk10 = 1;
    case 1:
        fn_1_180C(lbl_1_bss_10, 3);
        arg0->unk10 = 2;
    case 2:
        if (!fn_1_1850(lbl_1_bss_10)) {
            arg0->unk10 = 3;
        } else {
            break;
        }
    case 3:
        arg0->unk10 = 4;
    case 4:
        omSysExitReq = 1;
        arg0->func = NULL;
        arg0->unk10 = 0;
        break;
    default:
        break;
    }
}

UnkWindowDataStruct *fn_1_3EA4(s32 arg0)
{
    UnkWindowDataStruct *var_r31;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkWindowDataStruct), MEMORY_DEFAULT_NUM);
    var_r31->unk18 = 0;
    var_r31->unk10 = 0;
    var_r31->unk14 = 0;
    var_r31->unk_20 = 0;
    var_r31->process = HuPrcChildCreate(fn_1_41E0, 1000, 8192, 0, lbl_1_bss_4);
    var_r31->process->user_data = var_r31;
    var_r31->unk08 = arg0;
    switch (arg0) {
    case 0:
        var_r31->window = HuWinExCreateStyled(-10000.0f, 360.0f, 480, 80, -1, 1);
        HuWinBGTPLvlSet(var_r31->window, 0.8f);
        HuWinMesSpeedSet(var_r31->window, 0);
        HuWinMesPalSet(var_r31->window, 7, 0, 0, 0);
        break;
    case 1:
        var_r31->window = HuWinExCreateStyled(-10000.0f, 326.0f, 500, 40, -1, 0);
        HuWinAttrSet(var_r31->window, 2048);
        HuWinBGTPLvlSet(var_r31->window, 0.0f);
        HuWinMesSpeedSet(var_r31->window, 0);
        break;
    }
    HuWinDrawNoSet(var_r31->window, 63);
    fn_1_4190(var_r31);
    HuSprExecLayerSet(63, 2);
    return var_r31;
}

void fn_1_4040(UnkWindowDataStruct *windowData)
{
    HuWinExCleanup(windowData->window);
    HuPrcKill(windowData->process);
    HuMemDirectFree(windowData);
}

void fn_1_4080(UnkWindowDataStruct *windowData)
{
    if (!windowData->unk0C) {
        windowData->unk_20 = 1;
    }
}

void fn_1_4098(UnkWindowDataStruct *windowData)
{
    if (windowData->unk0C) {
        windowData->unk_20 = 2;
    }
}

void fn_1_40B0(UnkWindowDataStruct *windowData, u32 mess)
{
    if (!windowData->unk_20) {
        HuWinMesSet(windowData->window, mess);
        return;
    }
    windowData->unk18 = mess;
}

void fn_1_4104(UnkWindowDataStruct *windowData, u32 mess, s16 index)
{
    HuWinInsertMesSet(windowData->window, mess, index);
}

void fn_1_4144(UnkWindowDataStruct *windowData, float x, float y)
{
    HuWinPosSet(windowData->window, x, y);
}

void fn_1_4184(UnkWindowDataStruct *windowData)
{
    windowData->unk0C = 1;
}

void fn_1_4190(UnkWindowDataStruct *windowData)
{
    windowData->unk0C = 0;
}

void fn_1_419C(UnkWindowDataStruct *windowData)
{
    if (!windowData->unk_20) {
        windowData->unk_20 = 3;
    }
    windowData->unk10 = 1;
}

void fn_1_41BC(UnkWindowDataStruct *windowData, s32 arg1)
{
    if (!windowData->unk_20) {
        windowData->unk_20 = 4;
    }
    windowData->unk14 = 1;
    windowData->choice = arg1;
}

void fn_1_41E0(void)
{
    UnkWindowDataStruct *windowData;

    windowData = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        switch (windowData->unk_20) {
        case 1:
            windowData->unk0C = 1;
            HuWinExAnimIn(windowData->window);
            break;
        case 2:
            HuWinExAnimOut(windowData->window);
            windowData->unk0C = 0;
            break;
        case 3:
            winData[windowData->window].active_pad = 1;
            HuWinMesWait(windowData->window);
            windowData->unk10 = 0;
            break;
        case 4:
            windowData->choice = HuWinChoiceGet(windowData->window, windowData->choice);
            windowData->unk14 = 0;
            break;
        }
        if (windowData->unk18 != 0) {
            HuWinMesSet(windowData->window, windowData->unk18);
            windowData->unk18 = 0;
        }
        windowData->unk_20 = 0;
        if (windowData->unk10 != 0) {
            windowData->unk_20 = 3;
        }
        if (windowData->unk14 != 0) {
            windowData->unk_20 = 4;
        }
        HuPrcVSleep();
    }
}
