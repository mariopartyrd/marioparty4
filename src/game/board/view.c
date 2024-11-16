#include "game/board/view.h"
#include "game/audio.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfex.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/disp.h"

#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    u8 unk01;
    s16 unk02;
    s16 unk04;
} OverheadWork;

static void ExecMapView(void);
static void ExecStarView(void);
static void ExecOverheadView(void);
static void DestroyView(void);
static void SetTargetView(void);
static void DestroyFocus(void);
static void CreateButtonWin(void);
static void DestroyButtonWin(void);
static void InitOverheadView(void);
static void DestroyOverheadView(void);
static void UpdateOverheadView(omObjData *arg0);
static void WaitOverheadView(void);

static Vec focusPos;
static Vec focusPosTarget;

static s8 viewControls;
static s8 viewPlayer;
static s8 viewMoveF;
static s8 focusDestroyF;
static u16 focusTimer;
static omObjData *overheadObj;
static s8 pauseDisableF;
static Process *viewProc;

static s16 buttonWin = -1;
static s16 focusMdl = -1;

static float overhead2DPos[][2] = {
    {  48.0f,  72.0f },
    { HU_DISP_WIDTH-48,  72.0f },
    {  48.0f, HU_DISP_HEIGHT-72 },
    { HU_DISP_WIDTH-48, HU_DISP_HEIGHT-72 },
    { HU_DISP_CENTERX,  72.0f }
};

static float mapViewMinZ[] = {
    -2000.0f, -1500.0f, -2200.0f,
    -1800.0f, -2100.0f, -3000.0f,
    -3000.0f, -1800.0f, -1800.0f
};

static float mapViewMaxZ[] = {
    2300.0f, 2500.0f, 2600.0f,
    2000.0f, 2300.0f, 2500.0f,
    2500.0f, 2000.0f, 2000.0f
};

static float mapViewMinX[] = {
    -3000.0f, -3000.0f, -3000.0f,
    -3000.0f, -3000.0f, -3000.0f,
    -3000.0f, -2000.0f, -2000.0f
};

static float mapViewMaxX[] = {
    3000.0f, 3000.0f, 3000.0f,
    3000.0f, 3000.0f, 3000.0f,
    3000.0f, 1600.0f, 2000.0f
};

static float overheadCamZoom[] = {
    14370.0f, 14500.0f, 15000.0f,
    15000.0f, 13000.0f, 15000.0f,
      100.0f, 10000.0f, 10000.0f
};

static float overheadCamPosZ[] = {
    0.0f,    0.0f, 0.0f,
    0.0f,    0.0f, 0.0f,
    0.0f, -160.0f, 0.0f
};

void BoardViewOverheadExec(s32 arg0) {
    if (BoardPauseDisableGet() == 0) {
        BoardPauseDisableSet(1);
        pauseDisableF = 1;
    } else {
        pauseDisableF = 0;
    }
    _SetFlag(0x1001C);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSS, 1);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    viewProc = HuPrcChildCreate(ExecOverheadView, 0x200A, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(viewProc, DestroyView);
    viewControls = 2;
    viewPlayer = arg0;
    focusTimer = 1;
    viewMoveF = 0;
    BoardPlayerPosGet(arg0, &focusPos);
    BoardStatusItemSet(0);
    while (viewProc != NULL) {
        HuPrcVSleep();
    }
    BoardStatusItemSet(1);
    HuPrcSleep(3);
    WaitOverheadView();
    _ClearFlag(0x1001C);
}

void BoardViewFocusGetPos(Vec *arg0) {
    if (arg0) {
        BoardModelPosGet(focusMdl, arg0);
    }
}

static inline void BoardViewInlineFunc00(Vec *arg0, Vec *arg1, u16 arg2) {
    if (arg2 == 0) {
        arg2 = 1;
    }
    viewControls = 1;
    viewPlayer = -1;
    focusTimer = arg2;
    viewMoveF = 1;
    if (arg0) {
        focusPos = *arg0;
    }
    if (arg1) {
        focusPosTarget = *arg1;
    }
}

void BoardViewFocusSet(Vec *arg0, u16 arg1) {
    u16 var_r31;

    if (BoardPauseDisableGet() == 0) {
        BoardPauseDisableSet(1);
        pauseDisableF = 1;
    } else {
        pauseDisableF = 0;
    }
    focusDestroyF = 1;
    BoardViewInlineFunc00(NULL, arg0, arg1);
    HuPrcSleep(2);
}

void BoardViewMoveStart(Vec *arg0, Vec *arg1, u16 arg2) {
    u16 var_r31;

    if (BoardPauseDisableGet() == 0) {
        BoardPauseDisableSet(1);
        pauseDisableF = 1;
    } else {
        pauseDisableF = 0;
    }
    viewProc = HuPrcChildCreate(ExecStarView, 0x200A, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(viewProc, DestroyView);
    focusDestroyF = 0;
    BoardViewInlineFunc00(arg0, arg1, arg2);
    HuPrcSleep(2);
}

BOOL BoardViewMoveCheck(void) {
    return (viewMoveF != 0) ? TRUE : FALSE;
}

void BoardViewMoveEnd(void) {
    viewMoveF = 0;
}

void BoardViewWait(void) {
    viewMoveF = 0;
    while (viewProc != NULL) {
        HuPrcVSleep();
    }
}

void BoardViewMapExec(s32 arg0) {
    if (BoardPauseDisableGet() == 0) {
        BoardPauseDisableSet(1);
        pauseDisableF = 1;
    } else {
        pauseDisableF = 0;
    }
    viewProc = HuPrcChildCreate(ExecMapView, 0x200A, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(viewProc, DestroyView);
    viewControls = 0;
    viewPlayer = arg0;
    focusTimer = 1;
    viewMoveF = 0;
    BoardPlayerPosGet(arg0, &focusPos);
    while (viewProc != NULL) {
        HuPrcVSleep();
    }
}

static void ExecMapView(void) {
    Vec spC;
    float var_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    float temp_f24;
    u32 var_r28;
    s8 sp9;
    s8 sp8;

    SetTargetView();
    CreateButtonWin();
    temp_f25 = mapViewMaxZ[GWBoardGet()];
    temp_f24 = mapViewMinZ[GWBoardGet()];
    temp_f27 = mapViewMaxX[GWBoardGet()];
    temp_f26 = mapViewMinX[GWBoardGet()];
    while (1) {
        var_r28 = HuPadBtnDown[GWPlayer[viewPlayer].port];
        if (var_r28 == 0x200) {
            HuAudFXPlay(3);
            break;
        }
        if (HuPadBtn[GWPlayer[viewPlayer].port] & 0x100) {
            var_f29 = 40.0f;
        } else {
            var_f29 = 20.0f;
        }
        spC.x = spC.y = spC.z = 0.0f;
        sp9 = HuPadStkX[GWPlayer[viewPlayer].port];
        sp8 = HuPadStkY[GWPlayer[viewPlayer].port];
        if (sp9 != 0 || sp8 != 0) {
            OSs8tof32(&sp9, &spC.x);
            OSs8tof32(&sp8, &spC.z);
            temp_f28 = 180.0 * (atan2(spC.x, -spC.z) / M_PI);
            spC.x = var_f29 * sin(temp_f28 * M_PI / 180.0);
            spC.z = var_f29 * cos(temp_f28 * M_PI / 180.0);
        }
        VECAdd(&spC, &focusPos, &focusPos);
        if (focusPos.x < temp_f26) {
            focusPos.x = temp_f26;
        }
        if (focusPos.x > temp_f27) {
            focusPos.x = temp_f27;
        }
        if (focusPos.z < temp_f24) {
            focusPos.z = temp_f24;
        }
        if (focusPos.z > temp_f25) {
            focusPos.z = temp_f25;
        }
        BoardModelPosSetV(focusMdl, &focusPos);
        HuPrcVSleep();
    }
    DestroyFocus();
    DestroyButtonWin();
    HuPrcEnd();
}

static void ExecStarView(void) {
    Vec sp8;
    float temp_f30;

    SetTargetView();
    do {
        OSu16tof32(&focusTimer, &temp_f30);
        VECSubtract(&focusPosTarget, &focusPos, &sp8);
        sp8.x /= temp_f30;
        sp8.y /= temp_f30;
        sp8.z /= temp_f30;
        viewMoveF = 1;
        while (viewMoveF != 0) {
            HuPrcVSleep();
        }
        focusDestroyF = 0;
        while (focusTimer != 0) {
            VECAdd(&sp8, &focusPos, &focusPos);
            BoardModelPosSetV(focusMdl, &focusPos);
            HuPrcVSleep();
            focusTimer--;
        }
        BoardModelPosSetV(focusMdl, &focusPosTarget);
        BoardCameraMotionWait();
        viewMoveF = 1;
        while (viewMoveF != 0 && focusDestroyF == 0) {
            HuPrcVSleep();
        }
    } while (focusDestroyF != 0);
    DestroyFocus();
    HuPrcEnd();
}

static void ExecOverheadView(void) {
    u32 var_r31;

    if ((GWBoardGet() == BOARD_ID_MAIN3 || GWBoardGet() == BOARD_ID_MAIN6) && boardLightResetHook) {
        boardLightResetHook();
    }
    InitOverheadView();
    CreateButtonWin();
    HuPrcVSleep();
    SetTargetView();
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSS, 10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    while (1) {
        var_r31 = HuPadBtnDown[GWPlayer[viewPlayer].port];
        if (var_r31 == 0x200) {
            HuAudFXPlay(3);
            break;
        }
        HuPrcVSleep();
    }
    if ((GWBoardGet() == BOARD_ID_MAIN3 || GWBoardGet() == BOARD_ID_MAIN6) && boardLightSetHook) {
        boardLightSetHook();
    }
    DestroyButtonWin();
    DestroyFocus();
    HuPrcEnd();
}

static void DestroyView(void) {
    if (focusMdl != -1) {
        BoardModelKill(focusMdl);
        focusMdl = -1;
    }
    DestroyOverheadView();
    DestroyButtonWin();
    viewMoveF = 0;
    focusTimer = 0;
    viewPlayer = -1;
    if (pauseDisableF != 0) {
        BoardPauseDisableSet(0);
        pauseDisableF = 0;
    }
    viewProc = NULL;
}

static void SetTargetView(void) {
    Vec sp14;
    Vec sp8;

    BoardCameraBackup();
    focusMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x0A), 0, 0);
    BoardModelVisibilitySet(focusMdl, 0);
    BoardModelPosSetV(focusMdl, &focusPos);
    BoardCameraNearFarSet(10.0f, 30000.0f);
    if (viewControls != 2) {
        sp8.x = -45.0f;
        sp8.y = 0.0f;
        sp8.z = 0.0f;
        BoardCameraMotionStartEx(focusMdl, &sp8, NULL, 3000.0f, -1.0f, 21);
        BoardCameraMotionWait();
    } else {
        BoardModelPosSet(focusMdl, 0.0f, 0.0f, 0.0f);
        sp14.x = 0.0f;
        sp14.y = 0.0f;
        sp14.z = 0.0f;
        sp8.x = -78.0f;
        sp8.y = 0.0f;
        sp8.z = 0.0f;
        sp14.z = overheadCamPosZ[GWBoardGet()];
        BoardCameraMoveSet(0);
        BoardCameraMotionStartEx(focusMdl, &sp8, &sp14, overheadCamZoom[GWBoardGet()], -1.0f, 1);
        BoardCameraMotionWait();
        BoardCameraMoveSet(1);
    }
}

static void DestroyFocus(void) {
    if (focusMdl != -1) {
        BoardModelKill(focusMdl);
        focusMdl = -1;
    }
    BoardCameraMoveSet(0);
    BoardCameraRestore();
    BoardCameraMoveSet(1);
}

static void CreateButtonWin(void) {
    float sp8[2];
    float posX;
    float posY;
    s32 var_r31;

    if (viewControls != 2) {
        var_r31 = MAKE_MESSID(0x09, 0x05);
        #if VERSION_PAL
        HuWinMesMaxSizeGet(1, sp8, var_r31);
        posX = 288-((sp8[0]/2)-32);
        #endif
        posY = 286.0f;
    } else {
        var_r31 = MAKE_MESSID(0x10, 0x4D);
        #if VERSION_PAL
        posX = -10000.0f;
        posY = 324.0f;
        #else
        posY = 328.0f;
        #endif
        
    }
    HuWinMesMaxSizeGet(1, sp8, var_r31);
    #if VERSION_NTSC
    posX = -10000.0f;
    #endif
    buttonWin = HuWinCreate(posX, posY, sp8[0], sp8[1], 0);
    HuWinBGTPLvlSet(buttonWin, 0.0f);
    HuWinMesSpeedSet(buttonWin, 0);
    HuWinMesSet(buttonWin, var_r31);
}

static void DestroyButtonWin(void) {
    if (buttonWin != -1) {
        HuWinKill(buttonWin);
        buttonWin = -1;
    }
}

static void InitOverheadView(void) {
    Vec sp10;
    GXColor spA;
    s16 sp8;
    omObjData *temp_r26;
    OverheadWork *temp_r31;
    float *temp_r30;
    s32 i;
    s32 sp1C[8] = {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2E),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2F),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x30),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x31),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x32),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x33),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x34),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x35)
    };

    temp_r26 = omAddObjEx(boardObjMan, 0x1000, 0, 0, -1, UpdateOverheadView);
    overheadObj = temp_r26;
    temp_r31 = OM_GET_WORK_PTR(temp_r26, OverheadWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk01 = 1;
    temp_r31->unk02 = HuSprGrpCreate(9);
    for (i = 0; i < 4; i++) {
        temp_r30 = overhead2DPos[i];
        BoardSpriteCreate(sp1C[GWPlayer[i].character], 0x1388, 0, &sp8);
        HuSprGrpMemberSet(temp_r31->unk02, i, sp8);
        HuSprAttrSet(temp_r31->unk02, i, 1);
        HuSprAttrSet(temp_r31->unk02, i, 8);
        HuSprPosSet(temp_r31->unk02, i, temp_r30[0], temp_r30[1]);
        if (GWPlayer[i].character == 7) {
            spA.r = 0x50;
            spA.g = 0x50;
            spA.b = 0x50;
        } else {
            GWCharColorGet(GWPlayer[i].character, &spA);
        }
        BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x6C), 0x1770, 0, &sp8);
        HuSprGrpMemberSet(temp_r31->unk02, i + 4, sp8);
        HuSprPosSet(temp_r31->unk02, i + 4, temp_r30[0], temp_r30[1]);
        HuSprColorSet(temp_r31->unk02, i + 4, spA.r, spA.g, spA.b);
    }
    temp_r30 = overhead2DPos[4];
    temp_r31->unk04 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x08), NULL, 0);
    BoardModelMotionSpeedSet(temp_r31->unk04, 0.0f);
    BoardModelLayerSet(temp_r31->unk04, 6);
    BoardModelScaleSet(temp_r31->unk04, 0.4f, 0.4f, 0.4f);
    BoardModelPassSet(temp_r31->unk04, 1);
    sp10.x = temp_r30[0];
    sp10.y = temp_r30[1];
    sp10.z = 1000.0f;
    spA.r = 0xF8;
    spA.g = 0xF0;
    spA.b = 0x80;
    BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x6C), 0x1770, 0, &sp8);
    HuSprGrpMemberSet(temp_r31->unk02, 8, sp8);
    HuSprPosSet(temp_r31->unk02, 8, temp_r30[0], temp_r30[1]);
    HuSprColorSet(temp_r31->unk02, 8, spA.r, spA.g, spA.b);
    Hu3D2Dto3D(&sp10, 1, &sp10);
    BoardModelPosSetV(temp_r31->unk04, &sp10);
    HuSprGrpDrawNoSet(temp_r31->unk02, 0x40);
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        BoardModelVisibilitySet(temp_r31->unk04, 0);
        HuSprTPLvlSet(temp_r31->unk02, 8, 0.0f);
    }
}

static void DestroyOverheadView(void) {
    if (overheadObj) {
        OM_GET_WORK_PTR(overheadObj, OverheadWork)->unk00_field0 = 1;
    }
}

static void UpdateOverheadView(omObjData *arg0) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    float temp_f30;
    float *var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 i;
    u32 var_r26;
    OverheadWork *temp_r31;
    Mtx sp5C;
    Mtx sp2C;

    temp_r31 = OM_GET_WORK_PTR(arg0, OverheadWork);
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        if (temp_r31->unk02 != -1) {
            HuSprGrpKill(temp_r31->unk02);
        }
        if (temp_r31->unk04 != -1) {
            BoardModelKill(temp_r31->unk04);
        }
        overheadObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    var_r26 = HuPadBtnDown[GWPlayer[viewPlayer].port];
    if (var_r26 == 0x20) {
        temp_r31->unk01 ^= 1;
        HuAudFXPlay(0x1C);
    }
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        var_r27 = 1;
    } else {
        var_r27 = 0;
    }
    for (i = 0; i < 5; i++) {
        var_r29 = overhead2DPos[i];
        sp20.x = var_r29[0] - HU_DISP_CENTERX;
        sp20.y = var_r29[1] - 240.0f;
        sp20.z = 1000.0f;
        if (i != 4) {
            BoardSpacePosGet(0, GWPlayer[i].space_curr, &sp14);
        } else if (var_r27 != 0) {
            sp14.x = sp14.y = sp14.z = 0.0f;
        } else {
            BoardSpacePosGet(0, BoardSpaceStarGetCurr(), &sp14);
        }
        Hu3D3Dto2D(&sp14, 1, &sp14);
        sp14.x -= HU_DISP_CENTERX;
        sp14.y -= 240.0f;
        VECSubtract(&sp20, &sp14, &sp8);
        sp8.z = 0.0f;
        temp_f30 = BoardDAngleCalc(180.0 * (atan2(sp8.y, sp8.x) / M_PI) - 90.0);
        temp_f31 = VECMag(&sp8) / 32;
        if (i != 4) {
            var_r28 = i + 4;
        } else {
            var_r28 = 8;
        }
        HuSprZRotSet(temp_r31->unk02, var_r28, temp_f30);
        HuSprScaleSet(temp_r31->unk02, var_r28, 0.5f, temp_f31);
        HuSprPosSet(temp_r31->unk02, var_r28, var_r29[0], var_r29[1]);
        if (i == 4 && (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2)) {
            BoardModelVisibilitySet(temp_r31->unk04, 0);
        } else if (temp_r31->unk01 != 0) {
            if (i != 4) {
                HuSprAttrReset(temp_r31->unk02, i, 4);
            }
            HuSprAttrReset(temp_r31->unk02, var_r28, 4);
            BoardModelVisibilitySet(temp_r31->unk04, 1);
        } else {
            if (i != 4) {
                HuSprAttrSet(temp_r31->unk02, i, 4);
            }
            HuSprAttrSet(temp_r31->unk02, var_r28, 4);
            BoardModelVisibilitySet(temp_r31->unk04, 0);
        }
    }
    sp20.x = var_r29[0];
    sp20.y = var_r29[1];
    sp20.z = 1000.0f;
    BoardCameraRotGet(&sp8);
    PSMTXRotRad(sp5C, 'x', MTXDegToRad(sp8.x));
    PSMTXRotRad(sp2C, 'y', MTXDegToRad(sp8.y));
    PSMTXConcat(sp2C, sp5C, sp2C);
    BoardModelMtxSet(temp_r31->unk04, &sp2C);
    Hu3D2Dto3D(&sp20, 1, &sp20);
    BoardModelPosSetV(temp_r31->unk04, &sp20);
}

static void WaitOverheadView(void) {
    while (overheadObj) {
        HuPrcVSleep();
    }
}
