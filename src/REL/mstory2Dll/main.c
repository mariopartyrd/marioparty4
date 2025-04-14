#include "REL/mstory2Dll.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/hsfdraw.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/sprite.h"

#include "ext_math.h"

s32 lbl_1_bss_68[3]; // unused
StructBss24 lbl_1_bss_24;
s32 lbl_1_bss_4[8];
Process* lbl_1_bss_0;

s32 lbl_1_data_0[][4] = {
    { 0x37, 0x38, 0x36, 0x39 },
    { 0x43, 0x45, 0x44, 0x43 },
    { 0x40, 0x42, 0x41, 0x40 },
    { 0x4B, 0x4D, 0x4C, 0x4B },
    { 0x46, 0x48, 0x47, 0x46 },
    { 0x3E, 0x3F, 0x3E, 0x3E },
    {0x3A, 0x3B, 0x3C, 0xFFFFFFFF}
};

char* lbl_1_data_144[] = {
    "K-1 : KOOPA STORY - BOARD ENTRANCE EVENT",
    "K-3 : KOOPA STORY - BOARD CLEAR EVENT",
    "K-4 : KOOPA STORY - BOARD MISS EVENT",
    "K-5 : KOOPA STORY - MINIGAME CLEAR EVENT",
    "K-6 : KOOPA STORY - MINIGAME MISS EVENT",
    "--- : ENDING"
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
    s32 var_r30;
    s32 var_r31;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 i;

    var_r30 = 0;
    omAddObjEx(lbl_1_bss_0, 0x2000, 0, 0, -1, fn_1_4C);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    while (TRUE) {
        if (WipeStatGet() == 0) {
            break;
        }
        fn_1_BC8();
    }
    while (TRUE) {
        if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            break;
        }
        if (HuPadStkY[0] <= -30) {
            fn_1_BE8(5);
            var_r30++;
            if (var_r30 >= 6) {
                var_r30 = 0;
            }
            
        }
        if (HuPadStkY[0] >= 30) {
            fn_1_BE8(5);
            var_r30--;
            if (var_r30 < 0) {
                var_r30 = 5;
            }
        }
        fontcolor = FONT_COLOR_WHITE;
        print8(24, 100, 1.5f, ">>>>> MPGC STORY 2 - EVENT SELECT <<<<<");
        for (i = 0; i < 6; i++) {
            fontcolor = FONT_COLOR_WHITE;
            if (var_r30 == i) {
                fontcolor = FONT_COLOR_CYAN;
            }
            print8(24, 130 + i * 15, 1.5f, "%s", lbl_1_data_144[i]);
        }
        fn_1_BC8();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (TRUE) {
        if (WipeStatGet() == 0) {
            break;
        }
        fn_1_BC8();
    }
    GWSystem.board = 5;
    switch (var_r30) {
        case 0:
            fn_1_7F54(lbl_1_bss_0, 0);
            break;
        case 1:
            fn_1_B3E4(lbl_1_bss_0, 0);
            break;
        case 2:
            fn_1_EA2C(lbl_1_bss_0, 0);
            break;
        case 3:
            fn_1_1256C(lbl_1_bss_0, 0);
            break;
        case 4:
            fn_1_16060(lbl_1_bss_0, 0);
            break;
        case 5:
            fn_1_188F0(lbl_1_bss_0, 0);
            break;
    }
    while (TRUE) {
        fn_1_BC8();
    }
}

#ifdef __MWERKS__
#include "src/REL/executor.c"
#endif

void fn_1_3E4(void)
{
    int gid = HuSprGrpCreate(1);
    int sprid = HuTHPSprCreate("movie/endmov_ma0.thp", FALSE, 10);
    HuSprGrpMemberSet(gid, 0, sprid);
    HuSprPosSet(gid, 0, 288, 240);
    HuPrcSleep(5);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    while(WipeStatGet()) {
        HuPrcVSleep();
    }
    while(!HuTHPEndCheck()) {
        HuPrcVSleep();
    }
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
    while(WipeStatGet()) {
        HuPrcVSleep();
    }
    HuTHPClose();
    HuPrcVSleep();
    HuSprGrpKill(gid);
    while(1) {
        fn_1_BC8();
    }
}

void fn_1_4F4(void) {
    s32 i;

    lbl_1_bss_0 = omInitObjMan(62, 0x2000);
    switch (omovlevtno) {
        case 0:
            fn_1_7F54(lbl_1_bss_0, 0);
            break;
            
        case 1:
            for (i = 0; i < 4; i++) {
                if (GWPlayerCfg[i].character == GWStoryCharGet()) {
                    break;
                }
            }
            fn_1_B3E4(lbl_1_bss_0, i);
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                if (GWPlayerCfg[i].character == GWStoryCharGet()) {
                    break;
                }
            }
            fn_1_EA2C(lbl_1_bss_0, i);
            break;
        case 3:
            if (GWPlayerCoinWinGet(0) >= 10) {
                fn_1_1256C(lbl_1_bss_0, 0);
            } else {
                fn_1_16060(lbl_1_bss_0, 0);
            }
            break;
        case 4:
            fn_1_188F0(lbl_1_bss_0, 0);
            break;
            
        case 20:
            fn_1_1B90C(lbl_1_bss_0);
            break;
    }
}

void ObjectSetup(void) {
    fn_1_4F4();
}

float fn_1_864(float arg0, float arg1, float arg2, float arg3) {
    if (arg3 <= arg2) {
        return arg1;
    }
    return arg0 + (arg2 / arg3) * (arg1 - arg0);
}

float fn_1_88C(float arg0, float arg1, float arg2) {
    return (arg1 + arg0 * (arg2 - 1.0f)) / arg2;
}

float fn_1_8AC(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * (1.0 - cosd((90.0f / arg3) * arg2));
}

float fn_1_984(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * sind((90.0f / arg3) * arg2);
}

float fn_1_A4C(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg0;
    }
    return arg0 + (arg1 - arg0) * sind((180.0f / arg3) * arg2);
}

float fn_1_B08(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg0;
    }
    return arg0 + (arg1 - arg0) * sind((360.0f / arg3) * arg2);
}

void fn_1_BC4(void) {
}

void fn_1_BC8(void) {
    HuPrcVSleep();
}

void fn_1_BE8(s32 arg0) {
    HuPrcSleep(arg0);
}

void fn_1_C10(void) {
    HuPrcEnd();
}

void fn_1_C30(void) {
    HuWinInit(1);
}

void fn_1_C54(void) {
}

void fn_1_C58(s32 arg0, float arg1, float arg2, s32 arg3) {
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
                var_f23 = fn_1_984(temp_f31, temp_f29, i, 10.0f);
                var_f21 = fn_1_984(temp_f27, 1.0f, i, 10.0f);;
            } else {
                var_f22 = fn_1_984(temp_f30, temp_f28, i - 10, 5.0f);
                var_f20 = fn_1_984(temp_f26, 1.0f, i - 10, 5.0f);
            }
        } else {
            if (i <= 10) {
                var_f22 = fn_1_984(temp_f28, temp_f30, i, 10.0f);
                var_f20 = fn_1_984(1.0f, temp_f26, i, 10.0f);
            } else {
                var_f23 = fn_1_984(temp_f29, temp_f31, i - 10, 5.0f);
                var_f21 = fn_1_984(1.0f, temp_f27, i - 10, 5.0f);
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

s32 fn_1_16A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, float arg4, float arg5, s32 arg6) {
    s32 temp_r31;

    arg2 = arg2 * 21 + 16;
    arg3 = arg3 * 26 + 16;
    if (arg0 == 0) {
        arg0 = 550 - arg2;
    } else {
        arg0 = 1.0f + (576.0f - arg2) / 2.0f;
    }
    if (arg1 == 0) {
        arg1 = 430 - arg3;
    }
    temp_r31 = HuWinExCreateStyled(arg0, arg1, arg2, arg3, -1, 1);
    HuWinMesPalSet(temp_r31, 7, 0, 0, 0);
    if (arg6 != -1) {
        arg6 = GWPlayerCfg[arg6].pad_idx;
        winData[temp_r31].active_pad = (1 << arg6);
    } else {
        winData[temp_r31].active_pad = 0xF;
    }
    
    fn_1_C58(temp_r31, arg4, arg5, 1);
    return temp_r31;
}

s32 fn_1_185C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return fn_1_16A0(arg0, arg1, arg2, arg3, 0.5f, 0.5f, arg4);
}

void fn_1_1A34(s32 arg0, float arg1, float arg2) {
    HuWinMesSet(arg0, MAKE_MESSID(37, 4));
    HuPrcVSleep();
    fn_1_C58(arg0, arg1, arg2, 0);
    HuWinExCleanup(arg0);
}

void fn_1_1A94(s32 arg0) {
    fn_1_1A34(arg0, 0.5f, 0.5f);
}

void fn_1_1AFC(s32 arg0, s32 arg1) {
    s32 i;

    if (arg1 > 0) {
        HuPrcSleep(arg1);
        return;
    }
    HuWinComKeyReset();
    if (winData[arg0].active_pad == 0xF) {
        for (i = 0; i < 10; i++) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWMessDelayGet());
        }
    }
    HuWinMesWait(arg0);
    HuWinComKeyReset();
}

BOOL fn_1_1BA8(s32 arg0, s32 arg1) {
    s32 var_r31;
    s32 i;

    HuWinComKeyReset();
    if (winData[arg0].active_pad == 0xF) {
        for (i = 0; i < 10; i++) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWMessDelayGet());
        }
    }
    var_r31 = HuWinChoiceGet(arg0, arg1);
    HuWinComKeyReset();
    if (var_r31 != 0) {
        var_r31 = FALSE;
    } else {
        var_r31 = TRUE;
    }
    return var_r31;
}

BOOL fn_1_1C64(s32 arg0) {
    return fn_1_1BA8(arg0, 0);
}

void fn_1_1D18(s32 arg0, s32 arg1) {
    HuWinMesSet(arg0, arg1);
}

void fn_1_1D4C(s32 arg0, s32 arg1, s32 arg2) {
    HuWinInsertMesSet(arg0, arg1, arg2);
}

void fn_1_1D8C(s16 arg0) {
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

void fn_1_1DFC(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
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
    arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
}

void fn_1_1F84(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->motion[arg2] == Hu3DMotionIDGet(arg0->model[arg1])) {
        return;
    }
    if (arg0->motion[arg2] == Hu3DMotionShiftIDGet(arg0->model[arg1])) {
        return;
    }
    fn_1_1F84(arg0, arg1, arg2, arg3, arg4);
}

void fn_1_2264(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3) {
    HuPrcSleep(arg3 + 1);
    do {
        HuPrcVSleep();
    } while (arg0->motion[arg2] != Hu3DMotionIDGet(arg0->model[arg1]) || !Hu3DMotionEndCheck(arg0->model[arg1]));
}

s32 fn_1_22F4(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0 == GWPlayerCfg[i].group) {
            break;
        }
    }
    return i;
}

void fn_1_233C(s32 arg0, s32 arg1) {
    while (TRUE) {
        if (arg1 & HuPadBtnDown[arg0]) {
            break;
        }
        HuPrcVSleep();
    }
}

void fn_1_2390(void) {
    StructBss24* var_r31;

    var_r31 = &lbl_1_bss_24;
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

void fn_1_2750(void (*arg0)(void)) {
    lbl_1_bss_24.unk00 = arg0;
}

void fn_1_2760(void (*arg0)(void)) {
    lbl_1_bss_24.unk04 = arg0;
}

void fn_1_2770(omObjData* arg0) {
    StructBss24* var_r31;

    var_r31 = &lbl_1_bss_24;
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

void fn_1_2828(Process* arg0, void (*arg1)(void)) {
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 42.0f, 0.1f, 10000.0f, 1.2f);
    lbl_1_bss_24.unk00 = arg1;
    lbl_1_bss_24.unk04 = fn_1_2390;
    omAddObjEx(arg0, 0x7FDA, 0, 0, -1, omOutView);
    omAddObjEx(arg0, 0x7FD9, 0, 0, -1, fn_1_2770);
}

void fn_1_2948(omObjData* arg0, s32 arg1, Vec arg2, float arg3, float arg4, float arg5) {
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
    arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
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

void fn_1_2D00(omObjData* arg0, s32 arg1, Vec arg2, float arg3, float arg4, float arg5) {
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
        sp24.y = fn_1_88C(sp24.y, sp30.y, 10.0f);
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
        sp24.y = fn_1_864(sp24.y, sp18.y, i, temp_r27);
        Hu3DModelRotSet(arg0->model[1], sp24.x, sp24.y, sp24.z);
        HuPrcVSleep();
    }
}

void fn_1_34F4(s16 arg0) {
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

void fn_1_357C(StructFn357C* arg0, s32 arg1) {
    arg0->unk00 = arg1;
    arg0->unk04 = GWPlayerCfg[arg0->unk00].group;
    arg0->unk08 = GWPlayerCfg[arg0->unk00].iscom;
    arg0->unk0C = GWPlayerCfg[arg0->unk00].diff;
    arg0->unk10 = GWPlayerCfg[arg0->unk00].character;
    arg0->unk14 = GWPlayerCfg[arg0->unk00].pad_idx;
}

s32 fn_1_3610(void) {
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

s32 fn_1_3668(s32 arg0) {
    s32 temp_r3 = 0;

    temp_r3 = Hu3DGLightCreate(0.0f, 700.0f, 1200.0f, 0.0f, -1.0f, 0.0f, arg0, arg0, arg0);
    Hu3DGLightPosAimSet(temp_r3, 0.0f, 700.0f, 1200.0f, 0.0f, 0.0f, 640.0f);
    Hu3DGLightInfinitytSet(temp_r3);
    return temp_r3;
}

void fn_1_3754(void) {
    Vec sp20 = { 0.0f, 3000.0f, 800.0f };
    Vec sp14 = { 0.0f, 0.0f, 640.0f };
    Vec sp8 = { 0.0f, 1.0f, 0.0f };

    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);
}

void fn_1_3818(StructBss24* arg0) {
    arg0->unk08.x = arg0->unk14;
    arg0->unk08.y = arg0->unk18;
    arg0->unk08.z = arg0->unk1C;
    arg0->unk20.x = arg0->unk2C;
    arg0->unk20.y = arg0->unk30;
    arg0->unk20.z = arg0->unk34;
    arg0->unk38 = arg0->unk3C;
}

void fn_1_3854(StructBss24* arg0) {
    arg0->unk40 = 0;
    arg0->unk14 = arg0->unk08.x;
    arg0->unk18 = arg0->unk08.y;
    arg0->unk1C = arg0->unk08.z;
    arg0->unk2C = arg0->unk20.x;
    arg0->unk30 = arg0->unk20.y;
    arg0->unk34 = arg0->unk20.z;
    arg0->unk3C = arg0->unk38;
}

void fn_1_3898(StructBss24* arg0, StructBss24* arg1, float arg3) {
    arg0->unk08.x = fn_1_88C(arg0->unk08.x, arg1->unk14, arg3);
    arg0->unk08.y = fn_1_88C(arg0->unk08.y, arg1->unk18, arg3);
    arg0->unk08.z = fn_1_88C(arg0->unk08.z, arg1->unk1C, arg3);
    arg0->unk20.x = fn_1_88C(arg0->unk20.x, arg1->unk2C, arg3);
    arg0->unk20.y = fn_1_88C(arg0->unk20.y, arg1->unk30, arg3);
    arg0->unk20.z = fn_1_88C(arg0->unk20.z, arg1->unk34, arg3);
    arg0->unk38 = fn_1_88C(arg0->unk38, arg1->unk3C, arg3);
}

void fn_1_3B04(StructBss24* arg0, float arg1) {
    fn_1_3898(arg0, arg0, arg1);
}

void fn_1_3D70(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3) {
    arg1->unk14 = fn_1_864(arg0->unk14, arg1->unk08.x, arg2, arg3);
    arg1->unk18 = fn_1_864(arg0->unk18, arg1->unk08.y, arg2, arg3);
    arg1->unk1C = fn_1_864(arg0->unk1C, arg1->unk08.z, arg2, arg3);
    arg1->unk2C = fn_1_864(arg0->unk2C, arg1->unk20.x, arg2, arg3);
    arg1->unk30 = fn_1_864(arg0->unk30, arg1->unk20.y, arg2, arg3);
    arg1->unk34 = fn_1_864(arg0->unk34, arg1->unk20.z, arg2, arg3);
    arg1->unk3C = fn_1_864(arg0->unk3C, arg1->unk38, arg2, arg3);
}

void fn_1_3FEC(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3) {
    fn_1_3D70(arg0, arg1, arg2, arg3);
    arg0->unk08.x = arg1->unk14;
    arg0->unk08.y = arg1->unk18;
    arg0->unk08.z = arg1->unk1C;
    arg0->unk20.x = arg1->unk2C;
    arg0->unk20.y = arg1->unk30;
    arg0->unk20.z = arg1->unk34;
    arg0->unk38 = arg1->unk3C;
}

void fn_1_42A0(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3, float arg4) {
    fn_1_3D70(arg0, arg1, arg2, arg3);
    fn_1_3898(arg0, arg1, arg4);
}

void fn_1_470C(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3) {
    arg1->unk14 = fn_1_984(arg0->unk14, arg1->unk08.x, arg2, arg3);
    arg1->unk18 = fn_1_984(arg0->unk18, arg1->unk08.y, arg2, arg3);
    arg1->unk1C = fn_1_984(arg0->unk1C, arg1->unk08.z, arg2, arg3);
    arg1->unk2C = fn_1_984(arg0->unk2C, arg1->unk20.x, arg2, arg3);
    arg1->unk30 = fn_1_984(arg0->unk30, arg1->unk20.y, arg2, arg3);
    arg1->unk34 = fn_1_984(arg0->unk34, arg1->unk20.z, arg2, arg3);
    arg1->unk3C = fn_1_984(arg0->unk3C, arg1->unk38, arg2, arg3);
}

void fn_1_4B60(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3) {
    fn_1_470C(arg0, arg1, arg2, arg3);
    arg0->unk08.x = arg1->unk14;
    arg0->unk08.y = arg1->unk18;
    arg0->unk08.z = arg1->unk1C;
    arg0->unk20.x = arg1->unk2C;
    arg0->unk20.y = arg1->unk30;
    arg0->unk20.z = arg1->unk34;
    arg0->unk38 = arg1->unk3C;
}

void fn_1_4FEC(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3, float arg4) {
    fn_1_470C(arg0, arg1, arg2, arg3);
    fn_1_3898(arg0, arg1, arg4);
}

void fn_1_5644(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3) {
    arg1->unk14 = fn_1_8AC(arg0->unk14, arg1->unk08.x, arg2, arg3);
    arg1->unk18 = fn_1_8AC(arg0->unk18, arg1->unk08.y, arg2, arg3);
    arg1->unk1C = fn_1_8AC(arg0->unk1C, arg1->unk08.z, arg2, arg3);
    arg1->unk2C = fn_1_8AC(arg0->unk2C, arg1->unk20.x, arg2, arg3);
    arg1->unk30 = fn_1_8AC(arg0->unk30, arg1->unk20.y, arg2, arg3);
    arg1->unk34 = fn_1_8AC(arg0->unk34, arg1->unk20.z, arg2, arg3);
    arg1->unk3C = fn_1_8AC(arg0->unk3C, arg1->unk38, arg2, arg3);
}

void fn_1_5B08(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3) {
    fn_1_5644(arg0, arg1, arg2, arg3);
    arg0->unk08.x = arg1->unk14;
    arg0->unk08.y = arg1->unk18;
    arg0->unk08.z = arg1->unk1C;
    arg0->unk20.x = arg1->unk2C;
    arg0->unk20.y = arg1->unk30;
    arg0->unk20.z = arg1->unk34;
    arg0->unk38 = arg1->unk3C;
}

void fn_1_6004(StructBss24* arg0, StructBss24* arg1, float arg2, float arg3, float arg4) {
    fn_1_5644(arg0, arg1, arg2, arg3);
    fn_1_3898(arg0, arg1, arg4);
}

int fn_1_66CC(int modelId)
{
    return Hu3DMotionMaxTimeGet(modelId);
}

void fn_1_6704(omObjData* arg0) {
    s32 var_r30;
    if(arg0->work[0] == 0) {
        return;
    }
    if (arg0->work[2] != 0) {
        arg0->work[2]--;
        return;
    }
    if (arg0->work[2] == 0 && Hu3DMotionEndCheck(arg0->model[1])) {
        var_r30 = arg0->work[1];
        Hu3DMotionShiftSet(arg0->model[1], arg0->motion[var_r30], 0.0f, 15.0f, 0x40000001U);
        arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
        arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
    }
}

void fn_1_67D8(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    fn_1_1DFC(arg0, 1, arg1, arg3, arg4);
    if (arg4 == 0) {
        arg0->work[0] = 1;
        arg0->work[1] = arg2;
        arg0->work[2] = arg3 + 1;
    }
}

void fn_1_6970(s32 arg0, s32 arg1) {
    HuWinMesSet(arg0, arg1);
}

void fn_1_69A4(s32 arg0, s32 arg1, s32 arg2) {
    HuWinInsertMesSet(arg0, arg1, arg2);
}

void fn_1_69E4(s32 arg0, s32 arg1) {
    fn_1_1AFC(arg0, arg1);
}

void fn_1_6A90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_r27 = 0;
    s32 var_r29 = 0;
    s32 var_r23 = 0;
    s32 var_r26;
    s32 i;
    if(arg2 == -1) {
        var_r23 = 1;
        arg2 = 0;
    }
    HuWinMesSet(arg0, arg1);
    var_r27 = HuWinKeyWaitNumGet(arg1);
    if (arg2 == -1 || arg2 >= var_r27 - 1) {
        arg2 = var_r27 - 1;
    }
    HuWinComKeyReset();
    if (winData[arg0].active_pad == 0xF) {
        for (i = 0; i < 10; i++) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWMessDelayGet());
        }
    }
    HuWinMesSet(arg0, arg1);
    for (i = 0; i < var_r27; i++) {
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
                    if(arg3 != -1) {
                        if(arg4 != -1) {
                            i=0;
                            do {
                                HuPrcVSleep();
                                if(i++ == 25) {
                                    HuAudFXPlay(lbl_1_data_0[6][0]);
                                }
                            } while(!Hu3DMotionEndCheck(arg3));
                            Hu3DMotionShiftSet(arg3, arg4, 0, 1, 0);
                            HuPrcSleep(15);
                        }
                        var_r26 = fn_1_66CC(arg3)-15;
                        if(var_r23 == 1) {
                            for(i=0; i<var_r26; i++) {
                                HuPrcVSleep();
                                if(i == 25) {
                                    HuAudFXPlay(lbl_1_data_0[6][0]);
                                }
                            }
                        } else {
                            if(var_r26 > 0) {
                                HuPrcSleep(var_r26);
                            }
                        }
                    } else {
                        HuPrcSleep(60);
                    }
                    HuWinAttrReset(arg0, 0x400);
                    HuWinKeyWaitEntry(arg0);
                    break;
                }
            } else if (HuWinStatGet(arg0) != 1) {
                break;
            }
        }
    }
    fn_1_1AFC(arg0, 0);
    HuWinMesSet(arg0, MAKE_MESSID(37, 4));
    HuWinComKeyReset();
}

void fn_1_6D78(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    fn_1_6A90(arg0, arg1, arg2, arg3, -1);
}

void fn_1_6DBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r28 = 0;
    s32 var_r29 = 0;
    s32 i;
    
    HuWinMesSet(arg0, arg1);
    temp_r28 = HuWinKeyWaitNumGet(arg1);
    if (arg2 == -1 || arg2 >= temp_r28 - 1) {
        arg2 = temp_r28 - 1;
    }
    HuWinComKeyReset();
    if (winData[arg0].active_pad == 0xF) {
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
    fn_1_1AFC(arg0, 0);
    HuWinMesSet(arg0, MAKE_MESSID(37, 4));
    HuWinComKeyReset();
}

BOOL fn_1_6FB0(s32 arg0) {
    return fn_1_1BA8(arg0, 0);
}

s32 fn_1_7064(s32 arg0, s32 arg1) {
    float spC[2];
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    s32 var_r31;

    HuWinMesMaxSizeGet(1, spC, arg0);
    var_f31 = spC[0];
    var_f30 = spC[1];
    var_f29 = 550.0f - var_f31;
    var_f28 = 430.0f - var_f30;
    var_r31 = HuWinExCreateStyled(var_f29, var_f28, var_f31, var_f30, -1, 1);
    if (arg1 != -1) {
        arg1 = GWPlayerCfg[arg1].pad_idx;
        winData[var_r31].active_pad = (1 << arg1);
    } else {
        winData[var_r31].active_pad = 0xF;
    }
    HuWinMesPalSet(var_r31, 7, 0, 0, 0);
    fn_1_C58(var_r31, 0.5f, 0.5f, 1);
    return var_r31;
}

void fn_1_71DC(s32 arg0) {
    fn_1_1A34(arg0, 0.5f, 0.5f);
}

char *lbl_1_data_308[8] = {
    "c000m1-ske_head",
    "c001m1-ske_head",
    "c002m1-ske_head",
    "c003m1-ske_head",
    "c004m1-ske_head",
    "c005m1-ske_head",
    "c006m1-ske_head",
    "c007m1-ske_head"
};

s32 lbl_1_data_328[8][2] = {
    0x200, 0,
    0x200, 0,
    0x200, 0,
    0x200, 0,
    0x200, 0,
    0x200, 0,
    0x200, 0,
    0x200, 0,
};

float lbl_1_data_368[8] = {
    194,
    191,
    87.2,
    50.1,
    72,
    83.5,
    87.2,
    64.5
};

void fn_1_7244(s16 modelId, char *objName, u32 constFlags, float ofs)
{
    HsfObject *obj = Hu3DModelObjPtrGet(modelId, objName);
    HsfConstData *constData;
    if(!obj->constData) {
        constData = ObjConstantMake(obj, Hu3DData[modelId].unk_48);
    } else {
        constData = obj->constData;
    }
    constData->flags |= constFlags;
    if(constFlags & 0x10) {
        obj->data.curr.pos.x += ofs;
    }
    if(constFlags & 0x20) {
        obj->data.curr.pos.y += ofs;
    }
    if(constFlags & 0x40) {
        obj->data.curr.pos.z += ofs;
    }
    if(constFlags & 0x80) {
        obj->data.curr.rot.x += ofs;
    }
    if(constFlags & 0x100) {
        obj->data.curr.rot.y += ofs;
    }
    if(constFlags & 0x200) {
        obj->data.curr.rot.z += ofs;
    }
}

void fn_1_7384(int modelId, int charNo, float ofs, s32 maxTime, BOOL flag)
{
    float var_f31 = 0;
    float var_f30 = ofs;
    s32 i;
    if(charNo == 7) {
        var_f30 *= 2.5f;
    }
    if(lbl_1_data_328[charNo][1] == 0) {
        var_f30 *= -1;
    }
    if(flag) {
        for(i=0; i<maxTime; i++) {
            HuPrcVSleep();
            var_f31 = fn_1_864(0, var_f30, i, maxTime);
            fn_1_7244(modelId, lbl_1_data_308[charNo], lbl_1_data_328[charNo][0], var_f31);
            if(charNo == 2) {
                fn_1_7244(modelId, "c002m1-ske_hair1", lbl_1_data_328[charNo][0], -var_f31);
            } else if(charNo == 6) {
                
            }
        }
        fn_1_7244(modelId, lbl_1_data_308[charNo], lbl_1_data_328[charNo][0], var_f30);
        if(charNo == 2) {
            fn_1_7244(modelId, "c002m1-ske_hair1", lbl_1_data_328[charNo][0], -var_f30);
        }
        OSReport("\n");
    } else {
        for(i=0; i<maxTime; i++) {
            HuPrcVSleep();
            var_f31 = fn_1_864(0, var_f30, i, maxTime);
            fn_1_7244(modelId, lbl_1_data_308[charNo], lbl_1_data_328[charNo][0], -var_f31);
            if(charNo == 2) {
                fn_1_7244(modelId, "c002m1-ske_hair1", lbl_1_data_328[charNo][0], var_f31);
            } else if(charNo == 6) {
                
            }
        }
        Hu3DMotionNoMotReset(modelId, lbl_1_data_308[charNo], lbl_1_data_328[charNo][0]);
        if(charNo == 2) {
            Hu3DMotionNoMotReset(modelId, "c002m1-ske_hair1", lbl_1_data_328[charNo][0]);
        }
    }
}
