#include "REL/mstory3Dll.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/window.h"
#include "game/wipe.h"

#ifndef __MWERKS__
#include "game/objsub.h"
#endif

#include "ext_math.h"

u8 lbl_1_bss_48[0x10]; // unused
StructBss4 lbl_1_bss_4;
Process* lbl_1_bss_0;

s32 lbl_1_data_0[][4] = {
    { 0x37, 0x38, 0x36, 0x39 },
    { 0x43, 0x45, 0x44, 0x43 },
    { 0x40, 0x42, 0x41, 0x40 },
    { 0x4B, 0x4D, 0x4C, 0x4B },
    { 0x46, 0x48, 0x47, 0x46 },
    { 0x3E, 0x3F, 0x3E, 0x3E },
    { 0x3A, 0x3B, 0x3C,   -1 }
};

char* lbl_1_data_A4[] = {
    "S-1 : ALL STORY - BOARD RESULT EVENT",
    "--- : RESULT"
};

void fn_1_0(omObjData* arg0) {
    if (WipeStatGet() == 0) {
        arg0->func = NULL;
        omOvlReturnEx(1, 1);
    }
}

void fn_1_4C(omObjData* arg0) {
    if (omSysExitReq != 0) {
        arg0->func = fn_1_0;
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    }
}

void fn_1_A4(void) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;

    sp14 = 0;
    var_r30 = 0;
    var_r31 = 0;
    sp10 = 1;
    spC = 1;
    sp8 = 1;
    omAddObjEx(lbl_1_bss_0, 0x2000, 0, 0, -1, fn_1_4C);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    while (TRUE) {
        if (WipeStatGet() == 0) {
            break;
        }
        fn_1_938();
    }
    while (TRUE) {
        if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            break;
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_DOWN) {
            var_r30++;
            if (var_r30 >= 2) {
                var_r30 = 0;
            }
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_UP) {
            var_r30--;
            if (var_r30 < 0) {
                var_r30 = 1;
            }
        }
        if (HuPadStkX[0] <= -30) {
            var_r31++;
            if (var_r31 > 6) {
                var_r31 = 0;
            }
        }
        if (HuPadStkX[0] >= 30) {
            var_r31--;
            if (var_r31 < 0) {
                var_r31 = 5;
            }
        }
        fontcolor = FONT_COLOR_WHITE;
        print8(24, 100, 1.5f, ">>>>> MPGC STORY 3 - EVENT SELECT <<<<<");
        print8(24, 130, 1.5f, "MAP NUMBER : %d", var_r31 + 1);
        for (var_r29 = 0; var_r29 < 2; var_r29++) {
            fontcolor = FONT_COLOR_WHITE;
            if (var_r30 == var_r29) {
                fontcolor = FONT_COLOR_CYAN;
            }
            print8(24, 160 + var_r29 * 15, 1.5f, "%s", lbl_1_data_A4[var_r29]);
        }
        fn_1_938();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (TRUE) {
        if (WipeStatGet() == 0) {
            break;
        }
        fn_1_938();
    }
    GWSystem.board = var_r31;
    switch (var_r30) {         
        case 0:
            fn_1_6E34(lbl_1_bss_0, var_r31, 1, 0, 0);
            break;
        case 1:
            fn_1_157F0(lbl_1_bss_0, var_r31, 0, 0);
            break;
    }
    while (TRUE) {
        fn_1_938();
    }
}

#ifdef __MWERKS__
#include "src/REL/executor.c"
#endif

void fn_1_40C(void) {
    lbl_1_bss_0 = omInitObjMan(62, 0x2000);
    omGameSysInit(lbl_1_bss_0);
    switch (omovlevtno) {
        case 0:
            fn_1_6E34(lbl_1_bss_0, GWSystem.board, GWSystem.bonus_star, GWSystem.party, 0);
            break;
        case 1:
            fn_1_157F0(lbl_1_bss_0, GWSystem.board, GWSystem.party, 0);
            break;
    }
}

void ObjectSetup(void) {
    fn_1_40C();
}

float fn_1_5D4(float arg8, float arg9, float argA, float argB) {
    if (argB <= argA) {
        return arg9;
    }
    return arg8 + (argA / argB) * (arg9 - arg8);
}

float fn_1_5FC(float arg8, float arg9, float argA) {
    return (arg9 + arg8 * (argA - 1.0f)) / argA;
}

float fn_1_61C(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * (1.0 - cosd((90.0f / arg3) * arg2));
}

float fn_1_6F4(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * sind((90.0f / arg3) * arg2);
}

float fn_1_7BC(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg0;
    }
    return arg0 + (arg1 - arg0) * sind((180.0f / arg3) * arg2);
}

float fn_1_878(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg0;
    }
    return arg0 + (arg1 - arg0) * sind((360.0f / arg3) * arg2);
}

void fn_1_934(void) {
}

void fn_1_938(void) {
    HuPrcVSleep();
}

void fn_1_958(s32 arg0) {
    HuPrcSleep(arg0);
}

void fn_1_980(void) {
    HuPrcEnd();
}

void fn_1_9A0(void) {
    HuWinInit(1);
}

void fn_1_9C4(void) {
    HuWinAllKill();
}

void fn_1_9E4(s32 arg0, float arg1, float arg2, s32 arg3) {
    WindowData* temp_r29;
    float temp_f29;
    float temp_f28;
    float temp_f25;
    float temp_f24;
    float temp_f31;
    float temp_f27;
    float temp_f30;
    float temp_f26;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f20;
    s32 i;

    temp_r29 = &winData[arg0];
    temp_f29 = temp_r29->pos_x;
    temp_f28 = temp_r29->pos_y;
    temp_f25 = temp_r29->w;
    temp_f24 = temp_r29->h;
    temp_f31 = temp_f29 + temp_f25 * arg1;
    temp_f27 = 4.0f / temp_f25;
    if (temp_f31 + 4.0f - (temp_f29 + temp_f25) >= 0.0f) {
        temp_f31 = (temp_f29 + temp_f25) - 4.0f;
    } else if (temp_f29 - (temp_f31 - 2.0f) >= 0.0f) {
        temp_f31 = temp_f29;
    } else {
        temp_f31 -= 2.0f;
    }
    temp_f30 = temp_f28 + temp_f24 * arg2;
    temp_f26 = 4.0f / temp_f24;
    if (temp_f30 + 4.0f - (temp_f28 + temp_f24) >= 0.0f) {
        temp_f30 = (temp_f28 + temp_f24) - 4.0f;
    } else if (temp_f28 - (temp_f30 - 2.0f) >= 0.0f) {
        temp_f30 = temp_f28;
    } else {
        temp_f30 -= 2.0f;
    }
    if (arg3 != 0) {
        HuWinPosSet(arg0, temp_f31, temp_f30);
        HuWinScaleSet(arg0, temp_f27, temp_f26);
        var_f23 = temp_f31;
        var_f21 = temp_f27;
        var_f22 = temp_f30;
        var_f20 = temp_f26;
    } else {
        HuWinPosSet(arg0, temp_f29, temp_f28);
        HuWinScaleSet(arg0, 1.0f, 1.0f);
        var_f23 = temp_f29;
        var_f21 = 1.0f;
        var_f22 = temp_f28;
        var_f20 = 1.0f;
    }
    HuWinDispOn(arg0);
    for (i = 0; i <= 15; i++) {
        HuPrcVSleep();
        if (arg3 != 0) {
            if (i <= 10) {
                var_f23 = fn_1_6F4(temp_f31, temp_f29, i, 10.0f);
                var_f21 = fn_1_6F4(temp_f27, 1.0f, i, 10.0f);;
            } else {
                var_f22 = fn_1_6F4(temp_f30, temp_f28, i - 10, 5.0f);
                var_f20 = fn_1_6F4(temp_f26, 1.0f, i - 10, 5.0f);
            }
        } else {
            if (i <= 10) {
                var_f22 = fn_1_6F4(temp_f28, temp_f30, i, 10.0f);
                var_f20 = fn_1_6F4(1.0f, temp_f26, i, 10.0f);
            } else {
                var_f23 = fn_1_6F4(temp_f29, temp_f31, i - 10, 5.0f);
                var_f21 = fn_1_6F4(1.0f, temp_f27, i - 10, 5.0f);
            }
        }
        HuWinPosSet(arg0, var_f23, var_f22);
        HuWinScaleSet(arg0, var_f21, var_f20);
    }
    if (arg3 != 0) {
        HuWinPosSet(arg0, temp_f29, temp_f28);
        HuWinScaleSet(arg0, 1.0f, 1.0f);
    } else {
        HuWinPosSet(arg0, temp_f31, temp_f30);
        HuWinScaleSet(arg0, temp_f27, temp_f26);
    }
    HuPrcVSleep();
}

s32 fn_1_142C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, float arg8, float arg9, s32 arg4) {
    s32 temp_r3;

    arg2 = arg2 * 21 + 16;
    arg3 = arg3 * 26 + 16;
    if (arg0 == 0) {
        arg0 = 550 - arg2;
    } else {
        arg0 = 1.0f + (576.0f - arg2) / 2;
    }
    if (arg1 == 0) {
        arg1 = 430 - arg3;
    } else {
        arg1 = 445 - arg3;
    }
    temp_r3 = HuWinExCreateStyled(arg0, arg1, arg2, arg3, -1, 1);
    HuWinMesPalSet(temp_r3, 7, 0, 0, 0);
    if (arg4 != -1) {
        if (GWSystem.party != 1) {
            winData[temp_r3].active_pad = 1;
        } else {
            winData[temp_r3].active_pad = 0xF;
        }
    } else {
        winData[temp_r3].active_pad = 0xFF;
    }
    fn_1_9E4(temp_r3, arg8, arg9, 1);
    if (arg1 != 0) {
        HuWinPriSet(temp_r3, 50);
    }
    return temp_r3;
}

s32 fn_1_1624(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return fn_1_142C(arg0, arg1, arg2, arg3, 0.5f, 0.5f, arg4);
}

s32 fn_1_1834(u32 arg0, s32 arg1) {
    float sp8[2];
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    s32 temp_r3;

    if (arg1 == 0) {
        HuWinMesMaxSizeGet(1, sp8, arg0);
    }
    var_f31 = sp8[0];
    var_f30 = sp8[1];
    var_f29 = (576.0f - var_f31) / 2;
    var_f28 = 445.0f - var_f30;
    if (arg1 != 0) {
        var_f31 = 352.0f;
        var_f30 = 94.0f;
        var_f29 = 550.0f - var_f31;
        var_f28 = 445.0f - var_f30;
    }
    temp_r3 = HuWinExCreateStyled(var_f29, var_f28, var_f31, var_f30, -1, 1);
    HuWinMesPalSet(temp_r3, 7, 0, 0, 0);
    if (arg1 == 0) {
        HuWinBGTPLvlSet(temp_r3, 0.0f);
        HuWinMesSet(temp_r3, arg0);
        HuWinMesSpeedSet(temp_r3, 0);
        HuWinDispOn(temp_r3);
        HuWinMesPalSet(temp_r3, 7, 0xFF, 0xFF, 0xFF);
    } else {
        HuWinPriSet(temp_r3, 50);
        fn_1_9E4(temp_r3, 0.5f, 0.5f, 1);
        HuWinMesSpeedSet(temp_r3, 0);
    }
    return temp_r3;
}

void fn_1_1A24(s32 arg0) {
    HuWinExCleanup(arg0);
}

void fn_1_1A50(s32 arg0, float arg1, float arg2) {
    HuWinMesSet(arg0, MAKE_MESSID(37, 4));
    HuPrcVSleep();
    fn_1_9E4(arg0, arg1, arg2, 0);
    HuWinExCleanup(arg0);
}

void fn_1_1AB0(s32 arg0) {
    fn_1_1A50(arg0, 0.5f, 0.5f);
}

void fn_1_1B18(s32 arg0, s32 arg1) {
    s32 i;

    if (arg1 > 0) {
        HuPrcSleep(arg1);
        return;
    }
    HuWinComKeyReset();
    if (winData[arg0].active_pad == 0xFF) {
        for (i = 0; i < 10; i++) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWMessDelayGet());
        }
    }
    HuWinMesWait(arg0);
    HuWinComKeyReset();
}

s32 fn_1_1BC4(s32 arg0, s32 arg1) {
    s32 spC;
    s32 temp_r31;
    s32 var_r30;

    spC = 0;
    HuWinComKeyReset();
    if (winData[arg0].active_pad == 0xFF) {
        for (var_r30 = 0; var_r30 < 10; var_r30++) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWMessDelayGet());
        }
    }
    temp_r31 = HuWinChoiceGet(arg0, arg1);
    HuWinComKeyReset();
    if (temp_r31 != 0) {
        temp_r31 = 0;
    } else {
        temp_r31 = 1;
    }
    return temp_r31;
}

s32 fn_1_1C88(s32 arg0) {
    return fn_1_1BC4(arg0, 0);
}

void fn_1_1D44(s32 arg0, s32 arg1) {
    HuWinMesSet(arg0, arg1);
}

void fn_1_1D78(s32 arg0, s32 arg1, s32 arg2) {
    HuWinInsertMesSet(arg0, arg1, arg2);
}

void fn_1_1DB8(s16 arg0) {
    ModelData* var_r28;
    HsfMaterial* var_r31;
    HsfData* temp_r30;
    s16 var_r27;
    s32 i;

    var_r28 = &Hu3DData[arg0];
    temp_r30 = var_r28->hsfData;
    var_r27 = temp_r30->materialCnt;
    var_r31 = temp_r30->material;
    for (i = 0; i < var_r27; var_r31++, i++) {
        var_r31->vtxMode = 1;
    }
}

void fn_1_1E28(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    switch (arg4) {
        case 0:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, HU3D_MOTATTR_NONE);
            break;
        case 1:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, HU3D_MOTATTR_LOOP);
            break;
        case 2:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, HU3D_MOTATTR_PAUSE);
            break;
    }
}

void fn_1_1FA0(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->motion[arg2] == Hu3DMotionIDGet(arg0->model[arg1])) {
        return;
    }
    if (arg0->motion[arg2] == Hu3DMotionShiftIDGet(arg0->model[arg1])) {
        return;
    }
    fn_1_1FA0(arg0, arg1, arg2, arg3, arg4);
}

void fn_1_2280(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3) {
    HuPrcSleep(arg3 + 1);
    do {
        HuPrcVSleep();
    } while (arg0->motion[arg2] != Hu3DMotionIDGet(arg0->model[arg1]) || !Hu3DMotionEndCheck(arg0->model[arg1]));
}

void fn_1_2310(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3) {
    HuPrcSleep(arg3 + 1);
    do {
        HuPrcVSleep();
    } while (arg0->motion[arg2] != Hu3DMotionIDGet(arg0->model[arg1]) || !(Hu3DMotionMaxTimeGet(arg0->model[arg1]) - 20.0f <= Hu3DMotionTimeGet(arg0->model[arg1])));
}

s32 fn_1_23D8(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0 == GWPlayerCfg[i].group) {
            break;
        }
    }
    return i;
}

void fn_1_2420(s32 arg0, s32 arg1) {
    while (TRUE) {
        if (arg1 & HuPadBtnDown[arg0]) {
            break;
        }
        HuPrcVSleep();
    }
}

void fn_1_2474(void) {
    StructBss4* var_r31;

    var_r31 = &lbl_1_bss_4;
    if (HuPadBtn[0] & PAD_BUTTON_B) {
        if (HuPadBtn[0] & PAD_TRIGGER_R) {
            var_r31->unk08.z -= HuPadStkY[0] / 10.0f;
        } else {
            var_r31->unk08.x += HuPadStkX[0] / 10.0f;
            var_r31->unk08.y += HuPadStkY[0] / 10.0f;
        }
    }
    if (HuPadBtn[0] & PAD_BUTTON_Y) {
        var_r31->unk20.x -= HuPadStkY[0] / 100.0f;
        var_r31->unk20.y += HuPadStkX[0] / 100.0f;
        if (var_r31->unk20.x < 0.0f) {
            var_r31->unk20.x += 360.0f;
        }
        if (var_r31->unk20.x >= 360.0f) {
            var_r31->unk20.x -= 360.0f;
        }
        if (var_r31->unk20.y < 0.0f) {
            var_r31->unk20.y += 360.0f;
        }
        if (var_r31->unk20.y >= 360.0f) {
            var_r31->unk20.y -= 360.0f;
        }
    }
    if (HuPadBtn[0] & PAD_BUTTON_X) {
        var_r31->unk38 -= HuPadStkY[0] / 10.0f;
    }
    print8(24, 40, 1.5f, "CENTER : %.2f, %.2f, %.2f", var_r31->unk08.x, var_r31->unk08.y, var_r31->unk08.z);
    print8(24, 55, 1.5f, "ROT    : %.2f, %.2f, %.2f", var_r31->unk20.x, var_r31->unk20.y, var_r31->unk20.z);
    print8(24, 70, 1.5f, "ZOOM   : %.2f", var_r31->unk38);
}

void fn_1_2834(void (*arg0)(void)) {
    lbl_1_bss_4.unk00 = arg0;
}

void fn_1_2844(void (*arg0)(void)) {
    lbl_1_bss_4.unk04 = arg0;
}

void fn_1_2854(omObjData* arg0) {
    StructBss4* var_r31;

    var_r31 = &lbl_1_bss_4;
    if (var_r31->unk00 != NULL) {
        var_r31->unk00();
    }
    Center.x = var_r31->unk08.x;
    Center.y = var_r31->unk08.y;
    Center.z = var_r31->unk08.z;
    CRot.x = var_r31->unk20.x;
    CRot.y = var_r31->unk20.y;
    CRot.z = var_r31->unk20.z;
    CZoom = var_r31->unk38;
}

void fn_1_290C(Process* arg0, void (*arg1)(void)) {
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 42.0f, 1.0f, 2000.0f, 1.2f);
    lbl_1_bss_4.unk00 = arg1;
    lbl_1_bss_4.unk04 = fn_1_2474;
    omAddObjEx(arg0, 0x7FDA, 0, 0, -1, omOutView);
    omAddObjEx(arg0, 0x7FD9, 0, 0, -1, fn_1_2854);
}

void fn_1_2A2C(omObjData* arg0, s32 arg1, Vec arg2, float arg3, float arg4, float arg5) {
    Vec sp4C;
    Vec sp40;
    Vec sp34;
    Vec sp28;
    float sp24;
    float sp20;
    float sp1C;
    s32 sp18;
    s32 sp14;
    float var_f31;

    sp40.x = Hu3DData[arg0->model[arg1]].pos.x;
    sp4C.y = sp40.y = Hu3DData[arg0->model[arg1]].pos.y;
    sp40.z = Hu3DData[arg0->model[arg1]].pos.z;
    sp34.x = arg2.x;
    sp34.y = arg2.y;
    sp34.z = arg2.z;
    sp18 = arg4;
    sp28.x = Hu3DData[arg0->model[arg1]].rot.x;
    sp28.y = Hu3DData[arg0->model[arg1]].rot.y;
    sp28.z = Hu3DData[arg0->model[arg1]].rot.z;
    sp1C = 0.0f;
    sp20 = arg3;
    sp24 = 0.0f;
    sp14 = arg5;
    var_f31 = -1.1025f;
    Hu3DMotionShiftSet(arg0->model[1], arg0->motion[3], 0.0f, 5.0f, 0U);
    HuPrcSleep(10);
    while (TRUE) {
        if (var_f31 >= 1.7f) {
            var_f31 = 1.7f;
        }
        sp4C.y += var_f31 * var_f31 * (var_f31 >= 0.0f ? -17.5f : 17.5f);
        if (sp4C.y <= 0.0f && var_f31 > 0.0f) {
            sp4C.y = 0.0f;
        }
        sp4C.x = sp40.x += 6.0 * sind(sp28.y);
        sp4C.z = sp40.z += 6.0 * cosd(sp28.y);
        Hu3DModelPosSet(arg0->model[1], sp4C.x, sp4C.y, sp4C.z);
        Hu3DModelRotSet(arg0->model[1], sp28.x, sp28.y, sp28.z);
        HuPrcVSleep();
        if (sp4C.y <= arg2.y && var_f31 > 0.0f) {
            break;
        }
        var_f31 += 0.11f;
    }
}

void fn_1_2DD4(omObjData* arg0, s32 arg1, Vec arg2, float arg3, float arg4, float arg5) {
    Vec sp54;
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    s32 sp14;
    s32 temp_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 i;

    var_r26 = 0;
    var_r25 = 0;
    sp48.x = Hu3DData[arg0->model[arg1]].pos.x;
    sp48.y = Hu3DData[arg0->model[arg1]].pos.y;
    sp48.z = Hu3DData[arg0->model[arg1]].pos.z;
    sp3C.x = arg2.x;
    sp3C.y = arg2.y;
    sp3C.z = arg2.z;
    sp14 = arg4;
    sp24.x = Hu3DData[arg0->model[arg1]].rot.x;
    sp24.y = Hu3DData[arg0->model[arg1]].rot.y;
    sp24.z = Hu3DData[arg0->model[arg1]].rot.z;
    sp18.x = 0.0f;
    sp18.y = arg3;
    sp18.z = 0.0f;
    if (sp3C.x - sp48.x >= 0.0f) {
        var_r24 = 1;
    } else {
        var_r24 = 0;
    }
    if (sp3C.z - sp48.z >= 0.0f) {
        var_r23 = 1;
    } else {
        var_r23 = 0;
    }
    temp_r27 = arg5;
    do {
        sp30.y = -(atan2d(sp3C.z - sp48.z, sp3C.x - sp48.x) - 90.0);
        if (sp30.y < 0.0f) {
            sp30.y += 360.0f;
        } else if (sp30.y >= 360.0f) {
            sp30.y -= 360.0f;
        }
        if (sp30.y >= 180.0f) {
            if (sp24.y - sp30.y >= 180.0f) {
                sp24.y -= 360.0f;
            }
            if (sp24.y - sp30.y < -180.0f) {
                sp24.y += 360.0f;
            }
        } else {
            if (sp24.y - sp30.y > 180.0f) {
                sp24.y -= 360.0f;
            }
            if (sp24.y - sp30.y <= -180.0f) {
                sp24.y += 360.0f;
            }
        }
        sp54.x = sp48.x += 6.0 * sind(sp30.y);
        sp54.z = sp48.z += 6.0 * cosd(sp30.y);
        if (var_r24 != 0) {
            if (sp48.x >= sp3C.x) {
                sp54.x = sp48.x = sp3C.x;
                var_r26 = 1;
            }
        } else {
            if (sp48.x <= sp3C.x) {
                sp54.x = sp48.x = sp3C.x;
                var_r26 = 1;
            }
        }
        if (var_r23 != 0) {
            if (sp48.z >= sp3C.z) {
                sp54.z = sp48.z = sp3C.z;
                var_r25 = 1;
            }
        } else {
            if (sp48.z <= sp3C.z) {
                sp54.z = sp48.z = sp3C.z;
                var_r25 = 1;
            }
        }
        sp24.y = fn_1_5FC(sp24.y, sp30.y, 10.0f);
        Hu3DModelPosSet(arg0->model[1], sp54.x, sp48.y, sp54.z);
        Hu3DModelRotSet(arg0->model[1], sp24.x, sp24.y, sp24.z);
        HuPrcVSleep();
    } while (var_r25 != 1 || var_r26 != 1);
    sp24.y = Hu3DData[arg0->model[arg1]].rot.y;
    for (i = 0; i <= temp_r27; i++) {
        if (sp18.y >= 180.0f) {
            if (sp24.y - sp18.y >= 180.0f) {
                sp24.y -= 360.0f;
            }
            if (sp24.y - sp18.y < -180.0f) {
                sp24.y += 360.0f;
            }
        } else {
            if (sp24.y - sp18.y > 180.0f) {
                sp24.y -= 360.0f;
            }
            if (sp24.y - sp18.y <= -180.0f) {
                sp24.y += 360.0f;
            }
        }
        sp24.y = fn_1_5D4(sp24.y, sp18.y, i, temp_r27);
        Hu3DModelRotSet(arg0->model[1], sp24.x, sp24.y, sp24.z);
        HuPrcVSleep();
    }
}

void fn_1_35C8(s16 arg0) {
    ModelData* var_r28;
    HsfData* temp_r30;
    HsfMaterial* var_r31;
    s16 var_r27;
    s32 i;

    var_r28 = &Hu3DData[arg0];
    temp_r30 = var_r28->hsfData;
    var_r27 = temp_r30->materialCnt;
    var_r31 = temp_r30->material;
    for (i = 0; i < var_r27; var_r31++, i++) {
        var_r31->vtxMode = 1;
        var_r31->litColor[0] = 0xFF;
        var_r31->litColor[1] = 0xFF;
        var_r31->litColor[2] = 0xFF;
    }
}

void fn_1_3650(StructFn352C* arg0, s32 arg1) {
    arg0->unk00 = arg1;
    arg0->unk04 = GWPlayerCfg[arg0->unk00].group;
    arg0->unk08 = GWPlayerCfg[arg0->unk00].iscom;
    arg0->unk0C = GWPlayerCfg[arg0->unk00].diff;
    arg0->unk10 = GWPlayerCfg[arg0->unk00].character;
    arg0->unk14 = GWPlayerCfg[arg0->unk00].pad_idx;
}

s32 fn_1_36E4(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (!GWPlayerCfg[i].iscom) {
            break;
        }
    }
    if (i == 4) {
        return -1;
    }
    return i;
}

s32 fn_1_373C(void) {
    s32 var_r30;
    s32 var_r31;

    var_r30 = 0;
    do {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (var_r30 == GWPlayerCfg[var_r31].pad_idx) {
                break;
            }
        }
        if (!GWPlayerCfg[var_r31].iscom) {
            break;
        }
        var_r30++;
    } while (var_r30 != 5);
    if (var_r30 == 5) {
        return -1;
    }
    return var_r31;
}

s32 fn_1_37C8(s32 arg0) {
    s32 temp_r3 = 0;

    temp_r3 = Hu3DGLightCreate(0.0f, 700.0f, 1200.0f, 0.0f, -1.0f, 0.0f, arg0, arg0, arg0);
    Hu3DGLightPosAimSet(temp_r3, 0.0f, 700.0f, 1200.0f, 0.0f, 0.0f, 640.0f);
    Hu3DGLightInfinitytSet(temp_r3);
    return temp_r3;
}

void fn_1_38B4(void) {
    Vec sp20 = { 0.0f, 3000.0f, 800.0f };
    Vec sp14 = { 0.0f, 0.0f, 640.0f };
    Vec sp8 = { 0.0f, 1.0f, 0.0f };

    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);
}

void fn_1_3978(StructBss4* arg0) {
    arg0->unk08.x = arg0->unk14;
    arg0->unk08.y = arg0->unk18;
    arg0->unk08.z = arg0->unk1C;
    arg0->unk20.x = arg0->unk2C;
    arg0->unk20.y = arg0->unk30;
    arg0->unk20.z = arg0->unk34;
    arg0->unk38 = arg0->unk3C;
}

void fn_1_39B4(StructBss4* arg0) {
    arg0->unk40 = 0;
    arg0->unk14 = arg0->unk08.x;
    arg0->unk18 = arg0->unk08.y;
    arg0->unk1C = arg0->unk08.z;
    arg0->unk2C = arg0->unk20.x;
    arg0->unk30 = arg0->unk20.y;
    arg0->unk34 = arg0->unk20.z;
    arg0->unk3C = arg0->unk38;
}

void fn_1_39F8(StructBss4* arg0, StructBss4* arg1, float arg2) {
    arg0->unk08.x = fn_1_5FC(arg0->unk08.x, arg1->unk14, arg2);
    arg0->unk08.y = fn_1_5FC(arg0->unk08.y, arg1->unk18, arg2);
    arg0->unk08.z = fn_1_5FC(arg0->unk08.z, arg1->unk1C, arg2);
    arg0->unk20.x = fn_1_5FC(arg0->unk20.x, arg1->unk2C, arg2);
    arg0->unk20.y = fn_1_5FC(arg0->unk20.y, arg1->unk30, arg2);
    arg0->unk20.z = fn_1_5FC(arg0->unk20.z, arg1->unk34, arg2);
    arg0->unk38 = fn_1_5FC(arg0->unk38, arg1->unk3C, arg2);
}

void fn_1_3C64(StructBss4* arg0, float arg1) {
    fn_1_39F8(arg0, arg0, arg1);
}

void fn_1_3ED0(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3) {
    arg1->unk14 = fn_1_5D4(arg0->unk14, arg1->unk08.x, arg2, arg3);
    arg1->unk18 = fn_1_5D4(arg0->unk18, arg1->unk08.y, arg2, arg3);
    arg1->unk1C = fn_1_5D4(arg0->unk1C, arg1->unk08.z, arg2, arg3);
    arg1->unk2C = fn_1_5D4(arg0->unk2C, arg1->unk20.x, arg2, arg3);
    arg1->unk30 = fn_1_5D4(arg0->unk30, arg1->unk20.y, arg2, arg3);
    arg1->unk34 = fn_1_5D4(arg0->unk34, arg1->unk20.z, arg2, arg3);
    arg1->unk3C = fn_1_5D4(arg0->unk3C, arg1->unk38, arg2, arg3);
}

void fn_1_414C(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3) {
    fn_1_3ED0(arg0, arg1, arg2, arg3);
    arg0->unk08.x = arg1->unk14;
    arg0->unk08.y = arg1->unk18;
    arg0->unk08.z = arg1->unk1C;
    arg0->unk20.x = arg1->unk2C;
    arg0->unk20.y = arg1->unk30;
    arg0->unk20.z = arg1->unk34;
    arg0->unk38 = arg1->unk3C;
}

void fn_1_4400(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3, float arg4) {
    fn_1_3ED0(arg0, arg1, arg2, arg3);
    fn_1_39F8(arg0, arg1, arg4);
}

void fn_1_486C(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3) {
    arg1->unk14 = fn_1_6F4(arg0->unk14, arg1->unk08.x, arg2, arg3);
    arg1->unk18 = fn_1_6F4(arg0->unk18, arg1->unk08.y, arg2, arg3);
    arg1->unk1C = fn_1_6F4(arg0->unk1C, arg1->unk08.z, arg2, arg3);
    arg1->unk2C = fn_1_6F4(arg0->unk2C, arg1->unk20.x, arg2, arg3);
    arg1->unk30 = fn_1_6F4(arg0->unk30, arg1->unk20.y, arg2, arg3);
    arg1->unk34 = fn_1_6F4(arg0->unk34, arg1->unk20.z, arg2, arg3);
    arg1->unk3C = fn_1_6F4(arg0->unk3C, arg1->unk38, arg2, arg3);
}

void fn_1_4CC0(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3) {
    fn_1_486C(arg0, arg1, arg2, arg3);
    arg0->unk08.x = arg1->unk14;
    arg0->unk08.y = arg1->unk18;
    arg0->unk08.z = arg1->unk1C;
    arg0->unk20.x = arg1->unk2C;
    arg0->unk20.y = arg1->unk30;
    arg0->unk20.z = arg1->unk34;
    arg0->unk38 = arg1->unk3C;
}

void fn_1_514C(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3, float arg4) {
    fn_1_486C(arg0, arg1, arg2, arg3);
    fn_1_39F8(arg0, arg1, arg4);
}

void fn_1_57A4(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3) {
    arg1->unk14 = fn_1_61C(arg0->unk14, arg1->unk08.x, arg2, arg3);
    arg1->unk18 = fn_1_61C(arg0->unk18, arg1->unk08.y, arg2, arg3);
    arg1->unk1C = fn_1_61C(arg0->unk1C, arg1->unk08.z, arg2, arg3);
    arg1->unk2C = fn_1_61C(arg0->unk2C, arg1->unk20.x, arg2, arg3);
    arg1->unk30 = fn_1_61C(arg0->unk30, arg1->unk20.y, arg2, arg3);
    arg1->unk34 = fn_1_61C(arg0->unk34, arg1->unk20.z, arg2, arg3);
    arg1->unk3C = fn_1_61C(arg0->unk3C, arg1->unk38, arg2, arg3);
}

void fn_1_5C68(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3) {
    fn_1_57A4(arg0, arg1, arg2, arg3);
    arg0->unk08.x = arg1->unk14;
    arg0->unk08.y = arg1->unk18;
    arg0->unk08.z = arg1->unk1C;
    arg0->unk20.x = arg1->unk2C;
    arg0->unk20.y = arg1->unk30;
    arg0->unk20.z = arg1->unk34;
    arg0->unk38 = arg1->unk3C;
}

void fn_1_6164(StructBss4* arg0, StructBss4* arg1, float arg2, float arg3, float arg4) {
    fn_1_57A4(arg0, arg1, arg2, arg3);
    fn_1_39F8(arg0, arg1, arg4);
}

void fn_1_682C(omObjData* arg0) {
    s32 var_r30;

    if (arg0->work[0] == 0) {
        return;
    }
    if (arg0->work[2] != 0) {
        arg0->work[2]--;
        return;
    }
    if (arg0->work[2] == 0 && Hu3DMotionEndCheck(arg0->model[1])) {
        var_r30 = arg0->work[1];
        Hu3DMotionShiftSet(arg0->model[1], arg0->motion[var_r30], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
        arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
    }
}

void fn_1_68F0(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fn_1_1E28(arg0, 1, arg1, arg3, arg4);
    if (arg4 == 0) {
        arg0->work[0] = 1;
        arg0->work[1] = arg2;
        arg0->work[2] = arg3 + 1;
    }
}

void fn_1_6A78(s32 arg0, s32 arg1) {
    HuWinMesSet(arg0, arg1);
}

void fn_1_6AAC(s32 arg0, s32 arg1, s32 arg2) {
    HuWinInsertMesSet(arg0, arg1, arg2);
}

void fn_1_6AEC(s32 arg0, s32 arg1) {
    fn_1_1B18(arg0, arg1);
}

void fn_1_6B98(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r28 = 0;
    s32 var_r29 = 0;
    s32 i;

    temp_r28 = HuWinKeyWaitNumGet(arg1);
    if (arg2 == -1 || arg2 >= temp_r28 - 1) {
        arg2 = temp_r28 - 1;
    }
    HuWinComKeyReset();
    if (winData[arg0].active_pad == 0xFF) {
        for (i = 0; i < 10; i++) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWMessDelayGet());
        }
    }
    HuWinMesSet(arg0, arg1);
    for (i = 0; i < temp_r28; i++) {
        var_r29 = 0;
        do {
            HuPrcVSleep();
        } while (HuWinStatGet(arg0) != 1);
        if (i == arg2) {
            HuWinAttrSet(arg0, 0x400);
            var_r29 = 1;
        }
        while (TRUE) {
            HuPrcVSleep();
            if (var_r29 != 0) {
                if (var_r29 == 1 && HuWinStatGet(arg0) != 1) {
                    var_r29 = 2;
                } else if (var_r29 == 2) {
                    HuPrcSleep(arg3);
                    HuWinAttrReset(arg0, 0x400);
                    HuWinKeyWaitEntry(arg0);
                    break;
                }
            } else if (HuWinStatGet(arg0) != 1) {
                break;
            }
        }
    }
    fn_1_6AEC(arg0, 0);
    HuWinMesSet(arg0, MAKE_MESSID(37, 4));
    HuWinComKeyReset();
}

BOOL fn_1_6D80(s32 arg0) {
    s32 var_r31;
    s32 i;

    HuWinComKeyReset();
    if (winData[arg0].active_pad == 0xFF) {
        for (i = 0; i < 10; i++) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWMessDelayGet());
        }
    }
    var_r31 = HuWinChoiceGet(arg0, 0);
    HuWinComKeyReset();
    if (var_r31 != 0) {
        var_r31 = FALSE;
    } else {
        var_r31 = TRUE;
    }
    return var_r31;
}
