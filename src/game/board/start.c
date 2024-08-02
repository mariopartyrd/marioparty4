#include "game/board/start.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/flag.h"
#include "game/hsfanim.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/board/audio.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/roll.h"
#include "game/board/space.h"
#include "game/board/star.h"
#include "game/board/tutorial.h"
#include "game/board/ui.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "string.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 3;
        u8 unk00_field2 : 2;
        u8 unk00_field3 : 1;
        u8 unk00_field4 : 1;
    };
    u8 unk01;
    u8 unk02;
    s8 unk03;
    s8 unk04;
    char unk05[1];
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s16 unk0C;
    s8 unk0E;
} PlayerStartWork;

static void DestroyStart(void);
static void ExecStart(void);
static void ShowLogo(void);
static void FocusStart(void);
static void CreatePlayerStart(void);
static void ExecPlayerStart(omObjData *arg0);
static void PlayerFall(omObjData *arg0, PlayerStartWork *arg1);
static void PlayerWaitSpeak(omObjData *arg0, PlayerStartWork *arg1);
static void PlayerDiceFall(omObjData *arg0, PlayerStartWork *arg1);
static void PlayerDiceRoll(omObjData *arg0, PlayerStartWork *arg1);
static void PlayerDiceNumShow(omObjData *arg0, PlayerStartWork *arg1);
static void PlayerDiceNumHide(omObjData *arg0, PlayerStartWork *arg1);
static void SetPlayerStartState(s32 arg0, s32 arg1);
static s32 GetPlayerStartState(s32 arg0);
static void ExecStartRoll(void);
static void InitCamera(void);
static void InitHost(void);
static void CreateTapWin(void);
static void OrderPlayers(void);

static Vec spacePos;
static Vec camStartFocusPos;

static s16 hostMdl;
static s16 startSpace;
static s8 playerOrderNew[4];
static s8 playerOrderOld[4];
static Process *startProc;

static s16 logoSprGrp = -1;
static s16 logoSpr = -1;
static s16 camFocus = -1;
static s16 tapWin = -1;
static s32 streamStatus = -1;

static s8 tutorialRollTbl[] = {
    0x02, 0x08, 0x06, 0x00
};

static omObjData *playerStartObj[4] = {
    NULL, NULL, NULL, NULL
};

static s32 hitFX[4] = {
    -1, -1, -1, -1
};

//mod: extend for custom data
static s32 startMesTbl[10][5] = {
    { 0x00150001, 0x00150007, 0x0015000D, 0x00150016, 0x0015001C },
    { 0x00150002, 0x00150008, 0x0015000E, 0x00150017, 0x0015001D },
    { 0x00150003, 0x00150009, 0x0015000F, 0x00150018, 0x0015001E },
    { 0x00150004, 0x0015000A, 0x00150010, 0x00150019, 0x0015001F },
    { 0x00150005, 0x0015000B, 0x00150011, 0x0015001A, 0x00150020 },
    { 0x00150006, 0x0015000C, 0x00150012, 0x0015001B, 0x00150021 },
    { 0x00150001, 0x00150007, 0x0015000D, 0x00150016, 0x0015001C },
    { 0x00150033, 0x00150034, 0x00150035, 0x00150036, 0x00150037 },
    { 0x0015003B, 0x0015003C, 0x0015003D, 0x0015003E, 0x0015003F },
    //Mod TODO: fix for custom board data
    { 0x0015003B, 0x0015003C, 0x0015003D, 0x0015003E, 0x0015003F }
};

//mod: extend for custom board
static s32 logoSprTbl[] = {
    0x00070057,
    0x00070058,
    0x00070059,
    0x0007005A,
    0x0007005B,
    0x0007005C,
    0x00070057,
    0x0007005D,
    0x0007005E,
    //Mod TODO: custom board data
    0x0007005E
};

void BoardStartExec(void) {
    startProc = HuPrcChildCreate(ExecStart, 0x2007, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(startProc, DestroyStart);
    while (startProc != NULL) {
        HuPrcVSleep();
    }
}

static void DestroyStart(void) {
    if (tapWin != -1) {
        HuWinKill(tapWin);
        tapWin = -1;
    }
    if (logoSprGrp != -1) {
        HuSprGrpKill(logoSprGrp);
        logoSprGrp = -1;
    }
    if (camFocus != -1) {
        BoardModelKill(camFocus);
        camFocus = -1;
    }
    BoardCameraNearFarSet(100.0f, 13000.0f);
    startProc = NULL;
}

static void ExecStart(void) {
    Vec sp8;
    s32 i;

    BoardCameraNearFarSet(100.0f, 23000.0f);
    GWSystem.player_curr = -1;
    startSpace = BoardSpaceFlagPosGet(0, 0x80000000, &spacePos);
    if ((GWBoardGet() == BOARD_ID_MAIN3 || GWBoardGet() == BOARD_ID_MAIN6) && boardLightResetHook) {
        boardLightResetHook();
    }
    for (i = 0; i < 4; i++) {
        BoardModelVisibilitySet(BoardPlayerModelGet(i), 0);
    }
    InitCamera();
    CreateTapWin();
    InitHost();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    _ClearFlag(FLAG_ID_MAKE(1, 28));
    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        streamStatus = HuAudSStreamPlay(5);
        ShowLogo();
        FocusStart();
        if ((GWBoardGet() == BOARD_ID_MAIN3 || GWBoardGet() == BOARD_ID_MAIN6) && boardLightSetHook) {
            boardLightSetHook();
        }
        BoardCameraMotionWait();
    } else {
        BoardMusStart(0, 0x28, 0x7F, 0);
    }
    CreatePlayerStart();
    ExecStartRoll();
    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardAudSeqFadeOut(0, 0x1F4);
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardTutorialHookExec(4, 0);
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        for (i = 0; i < 4; i++) {
            BoardPlayerCornerPosSet(i);
        }
        BoardSpacePosGet(0, GWPlayer->space_curr, &sp8);
        BoardPlayerPosSetV(0, &sp8);
        BoardCameraMoveSet(0);
        BoardCameraViewSet(2);
        BoardCameraMotionWait();
        BoardCameraTargetPlayerSet(0);
        BoardCameraMotionWait();
        BoardCameraMoveSet(1);
        BoardModelVisibilitySet(BoardStarHostMdlGet(), 0);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        HuPrcEnd();
    }
    BoardCameraNearFarSet(100.0f, 13000.0f);
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        GWSystem.player_curr = 0;
        BoardModelVisibilitySet(hostMdl, 0);
        BoardStatusItemSet(1);
        BoardPlayerCornerPosSet(0);
        BoardPlayerCornerPosSet(1);
        BoardPlayerCornerPosSet(2);
        BoardPlayerCornerPosSet(3);
        BoardPlayerPosSetV(0, &spacePos);
        BoardCameraMoveSet(0);
        BoardCameraViewSet(2);
        BoardCameraMotionWait();
        BoardCameraMoveSet(1);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
    } else {
        BoardStarShowNext(-1);
    }
    HuPrcEnd();
}

static void ShowLogo(void) {
    float temp_f28;
    float var_f27;
    s16 spA;
    s16 sp8;

    logoSprGrp = HuSprGrpCreate(1);
    BoardSpriteCreate(logoSprTbl[GWBoardGet()], 1000, 0, &logoSpr);
    HuSprGrpMemberSet(logoSprGrp, 0, logoSpr);
    HuSprAttrSet(logoSprGrp, 0, 1);
    HuSprAttrSet(logoSprGrp, 0, 8);
    HuSprScaleSet(logoSprGrp, 0, 0.01f, 0.01f);
    HuSprGrpPosSet(logoSprGrp, 288.0f, 240.0f);
    for (spA = 0; spA < 90; spA += 4) {
        OSs16tof32(&spA, &var_f27);
        temp_f28 = sin(var_f27 * M_PI / 180.0);
        HuSprScaleSet(logoSprGrp, 0, temp_f28, temp_f28);
        HuPrcVSleep();
    }
    HuSprScaleSet(logoSprGrp, 0, 1.0f, 1.0f);
    for (spA = 0; spA < 540; spA += 4) {
        sp8 = spA % 180;
        OSs16tof32(&sp8, &var_f27);
        temp_f28 = 1.0 + 0.699999988079071 * sin(var_f27 * M_PI / 180.0);
        HuSprScaleSet(logoSprGrp, 0, temp_f28, temp_f28);
        HuPrcVSleep();
    }
    HuSprScaleSet(logoSprGrp, 0, 1.0f, 1.0f);
    HuPrcSleep(0x78);
    for (spA = 0; spA < 90; spA += 4) {
        OSs16tof32(&spA, &var_f27);
        temp_f28 = cos(var_f27 * M_PI / 180.0);
        HuSprScaleSet(logoSprGrp, 0, temp_f28, temp_f28);
        HuPrcVSleep();
    }
    HuSprGrpKill(logoSprGrp);
    logoSprGrp = -1;
}

static void FocusStart(void) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    u32 var_r31;

    for (var_f31 = 14000.0f; var_f31 >= 2000.0f; var_f31 -= 50.0f) {
        BoardCameraZoomSet(var_f31);
        HuPrcVSleep();
    }
    BoardCameraZoomSet(2000.0f);
    BoardModelPosGet(camFocus, &sp2C);
    sp20.x = spacePos.x + 150.0f;
    sp20.y = spacePos.y + 100.0f;
    sp20.z = spacePos.z + 150.0f;
    PSVECSubtract(&sp20, &sp2C, &sp14);
    sp14.x /= 120.0f;
    sp14.y /= 120.0f;
    sp14.z /= 120.0f;
    HuAudSStreamFadeOut(streamStatus, 0x1388);
    for (var_r31 = 0; var_r31 < 120; var_r31++) {
        PSVECAdd(&sp14, &sp2C, &sp2C);
        BoardModelPosSetV(camFocus, &sp2C);
        HuPrcVSleep();
    }
    BoardModelPosSetV(camFocus, &sp20);
    sp8.x = -22.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(camFocus, &sp8, NULL, 1500.0f, -1.0f, 21);
}

static void CreatePlayerStart(void) {
    Vec spC;
    float temp_f30;
    omObjData *var_r29;
    PlayerStartWork *var_r30;
    s8 i;

    BoardModelPosGet(camFocus, &spC);
    for (i = 0; i < 4; i++) {
        playerOrderOld[i] = i;
        var_r29 = omAddObjEx(boardObjMan, 0x100, 0, 0, -1, ExecPlayerStart);
        playerStartObj[i] = var_r29;
        var_r30 = OM_GET_WORK_PTR(var_r29, PlayerStartWork);
        var_r30->unk00_field0 = 0;
        var_r30->unk00_field2 = i;
        var_r30->unk03 = -1;
        var_r30->unk0A = -1;
        var_r30->unk0C = -1;
        var_r30->unk00_field1 = 1;
        var_r30->unk01 = i * 30;
        var_r30->unk00_field3 = 0;
        var_r30->unk00_field4 = 0;
        var_r30->unk06 = 2;
        var_r30->unk04 = 1;
        var_r30->unk0E = 0x3C;
        var_r30->unk08 = BoardModelCreate(0x70018, NULL, 0);
        BoardModelVisibilitySet(var_r30->unk08, 0);
        BoardModelMotionSpeedSet(var_r30->unk08, 0.0f);
        OSs8tof32(&i, &temp_f30);
        temp_f30 = 135.0f * (temp_f30 - 2.0f + 0.5f);
        BoardModelVisibilitySet(BoardPlayerModelGet(playerOrderOld[var_r30->unk00_field2]), 1);
        var_r29->trans.x = spC.x + temp_f30;
        var_r29->trans.y = spC.y + 700.0f;
        var_r29->trans.z = spC.z + 100.0f;
        BoardPlayerPosSet(playerOrderOld[var_r30->unk00_field2], var_r29->trans.x, var_r29->trans.y, var_r29->trans.z);
        BoardPlayerMotionShiftSet(playerOrderOld[var_r30->unk00_field2], 4, 10.0f, 1.0f, 0);
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardMusStart(0, 0xC, 0x7F, 0);
    }
    while (GetPlayerStartState(3) != 0) {
        HuPrcVSleep();
    }
}

static void ExecPlayerStart(omObjData *arg0) {
    PlayerStartWork *temp_r31 = OM_GET_WORK_PTR(arg0, PlayerStartWork);

    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        if (hitFX[temp_r31->unk00_field2] != -1) {
            HuAudFXStop(hitFX[temp_r31->unk00_field2]);
            hitFX[temp_r31->unk00_field2] = -1;
        }
        playerStartObj[temp_r31->unk00_field2] = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r31->unk01 != 0) {
        temp_r31->unk01--;
        return;
    }
    switch (temp_r31->unk00_field1) {
        case 0:
            break;
        case 1:
            PlayerFall(arg0, temp_r31);
            break;
        case 2:
            PlayerWaitSpeak(arg0, temp_r31);
            break;
        case 3:
            PlayerDiceFall(arg0, temp_r31);
            break;
        case 4:
            PlayerDiceRoll(arg0, temp_r31);
            break;
        case 5:
            PlayerDiceNumShow(arg0, temp_r31);
            break;
        case 6:
            PlayerDiceNumHide(arg0, temp_r31);
            break;
    }
}

static void PlayerFall(omObjData *arg0, PlayerStartWork *arg1) {
    float temp_f31;

    if (arg1->unk00_field3 != 0) {
        SetPlayerStartState(playerOrderOld[arg1->unk00_field2], 0);
        BoardPlayerIdleSet(playerOrderOld[arg1->unk00_field2]);
        if (_CheckFlag(FLAG_ID_MAKE(1, 11)) && arg1->unk00_field2 == 3) {
            BoardTutorialHookExec(0, 0);
        }
        return;
    }
    if (arg1->unk02 > 200) {
        arg1->unk02 = -56;
    }
    OSu8tof32(&arg1->unk02, &temp_f31);
    arg0->trans.y += -0.08166667f * temp_f31 * temp_f31;
    if (arg0->trans.y < spacePos.y) {
        arg0->trans.y = spacePos.y;
        arg1->unk02 = 0;
        BoardPlayerMotionShiftSet(playerOrderOld[arg1->unk00_field2], 5, 0.0f, 4.0f, 0);
        arg1->unk01 = 0xC;
        arg1->unk00_field3 = 1;
    }
    arg1->unk02++;
    BoardPlayerPosSet(playerOrderOld[arg1->unk00_field2], arg0->trans.x, arg0->trans.y, arg0->trans.z);
}

static void PlayerWaitSpeak(omObjData *arg0, PlayerStartWork *arg1) {
    float var_f31;

    if (arg1->unk02 == 0) {
        var_f31 = 180.0f + BoardPlayerRotYGet(playerOrderOld[arg1->unk00_field2]);
        BoardPlayerMotBlendSet(playerOrderOld[arg1->unk00_field2], var_f31, 0xF);
        arg1->unk02 = 1;
        return;
    }
    if (BoardPlayerMotBlendCheck(playerOrderOld[arg1->unk00_field2])) {
        BoardPlayerIdleSet(playerOrderOld[arg1->unk00_field2]);
        SetPlayerStartState(playerOrderOld[arg1->unk00_field2], 0);
    }
}

static void PlayerDiceFall(omObjData *arg0, PlayerStartWork *arg1) {
    Vec sp8;
    float var_f31;
    float var_f30;
    s32 i;

    if (arg1->unk02 == 0) {
        HuAudFXPlay(0x302);
        BoardPlayerPosGet(playerOrderOld[arg1->unk00_field2], &sp8);
        var_f30 = 250.0f;
        var_f31 = 700.0f;
        arg0->rot.x = (var_f30 - var_f31) / 30.0f;
        sp8.y += var_f31;
        BoardModelPosSetV(arg1->unk08, &sp8);
        BoardModelVisibilitySet(arg1->unk08, 1);
    } else {
        if (arg1->unk02 > 30.0f) {
            if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
                if (arg1->unk00_field2 == 3) {
                    BoardTutorialHookExec(1, 0);
                    for (i = 0; i < 4; i++) {
                        SetPlayerStartState(playerOrderOld[i], 4);
                    }
                }
                return;
            }
            SetPlayerStartState(playerOrderOld[arg1->unk00_field2], 4);
            return;
        }
        BoardModelPosGet(arg1->unk08, &sp8);
        sp8.y += arg0->rot.x;
        BoardModelPosSetV(arg1->unk08, &sp8);
    }
    arg1->unk02++;
}

static s32 digitMdlTbl[9] = {
    0x0007000D, 0x0007000E, 0x0007000F,
    0x00070010, 0x00070011, 0x00070012,
    0x00070013, 0x00070014, 0x00070015
};

static s32 playerOrderMesTbl[3] = {
    0x00150013,
    0x00150014,
    0x00150015
};

static void PlayerDiceRoll(omObjData *arg0, PlayerStartWork *arg1) {
    Vec sp8;
    float var_f30;
    u32 var_r28;
    s8 var_r29;
    s8 temp_r26;

    var_r28 = 0;
    if (arg1->unk02 > arg1->unk06) {
        arg1->unk02 = 0;
        temp_r26 = arg1->unk04;
        do {
            arg1->unk04 = BoardRandMod(9);
        } while (arg1->unk04 == temp_r26);
        OSs8tof32(&arg1->unk04, &var_f30);
        BoardModelMotionTimeSet(arg1->unk08, var_f30 + 0.5f);
    }
    if (arg1->unk00_field4 == 0) {
        if (GWPlayer[playerOrderOld[arg1->unk00_field2]].com) {
            if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
                if (arg1->unk0E != 0) {
                    arg1->unk0E--;
                } else {
                    var_r28 = 0x100;
                }
            } else if (BoardRandMod(100) < 5) {
                var_r28 = 0x100;
            }
        } else {
            var_r28 = HuPadBtnDown[GWPlayer[playerOrderOld[arg1->unk00_field2]].port];
        }
        if (var_r28 == 0x100) {
            BoardPlayerDiceJumpStart(playerOrderOld[arg1->unk00_field2]);
            arg1->unk00_field4 = 1;
        }
    } else {
        if (BoardPlayerDiceJumpCheck(playerOrderOld[arg1->unk00_field2])) {
            SetPlayerStartState(playerOrderOld[arg1->unk00_field2], 5);
            arg1->unk06 = 360;
            arg0->rot.x = arg0->rot.y = 1.0f;
            arg1->unk04 = BoardRandMod(9);
            HuAudFXPlay(0x303);
            if (hitFX[arg1->unk00_field2] != -1) {
                HuAudFXStop(hitFX[arg1->unk00_field2]);
                hitFX[arg1->unk00_field2] = -1;
            }
            var_r29 = 0;
            while (var_r29 < 4) {
                if (playerOrderNew[var_r29] == arg1->unk04 && var_r29 != playerOrderOld[arg1->unk00_field2]) {
                    arg1->unk04 = BoardRandMod(9);
                    var_r29 = 0;
                } else {
                    var_r29++;
                }
            }
            if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
                arg1->unk04 = tutorialRollTbl[arg1->unk00_field2];
            }
            playerOrderNew[playerOrderOld[arg1->unk00_field2]] = arg1->unk04;
            arg1->unk0A = BoardModelCreate(digitMdlTbl[arg1->unk04], NULL, 0);
            BoardModelPosGet(arg1->unk08, &sp8);
            sp8.x += 50.0 * sin(0.0);
            sp8.z += 50.0 * cos(0.0);
            BoardModelPosSetV(arg1->unk0A, &sp8);
            BoardModelMotionStart(arg1->unk0A, 0, 0);
            BoardModelMotionSpeedSet(arg1->unk0A, 0.0f);
            BoardModelMotionTimeSet(arg1->unk0A, 0.0f);
            BoardModelLayerSet(arg1->unk0A, 2);
            arg1->unk0C = BoardDiceEffectCreate();
            Hu3DParManPosSet(arg1->unk0C, sp8.x, sp8.y, sp8.z);
            Hu3DParManTimeLimitSet(arg1->unk0C, 0x96);
            BoardModelVisibilitySet(arg1->unk08, 0);
            return;
        }
    }
    arg1->unk02++;
}

static void PlayerDiceNumShow(omObjData *arg0, PlayerStartWork *arg1) {
    float var_f30;

    arg1->unk06 -= 18;
    if (arg1->unk06 < 0) {
        arg1->unk06 = 0;
        SetPlayerStartState(playerOrderOld[arg1->unk00_field2], 0);
        if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
            BoardTutorialHookExec(2, 0);
        }
    }
    OSs16tof32(&arg1->unk06, &var_f30);
    BoardModelRotYSet(arg1->unk0A, var_f30);
}

static void PlayerDiceNumHide(omObjData *arg0, PlayerStartWork *arg1) {
    float var_f28;

    switch (arg1->unk02) {
        case 0:
            arg1->unk06 += 18;
            if (arg1->unk06 > 360) {
                arg1->unk06 = 0;
                arg1->unk02 = 1;
                arg0->rot.x = 1.0f;
                arg0->rot.y = 1.0f;
            }
            OSs16tof32(&arg1->unk06, &var_f28);
            BoardModelRotYSet(arg1->unk0A, var_f28);
            return;
        case 1:
            arg1->unk06 += 9;
            if (arg1->unk06 > 180) {
                arg1->unk06 = 0;
                arg1->unk02 = 2;
            }
            OSs16tof32(&arg1->unk06, &var_f28);
            arg0->rot.x = 1.0 + 1.2999999523162842 * sin(var_f28 * M_PI / 180.0);
            break;
        case 2:
            arg1->unk06 += 9;
            if (arg1->unk06 > 180) {
                arg1->unk06 = 179;
                arg1->unk02 = 3;
            }
            OSs16tof32(&arg1->unk06, &var_f28);
            arg0->rot.x = cos(0.5f * var_f28 * M_PI / 180.0);
            arg0->rot.y = 1.0 + 1.2999999523162842 * sin(var_f28 * M_PI / 180.0);
            break;
        case 3:
            BoardModelVisibilitySet(arg1->unk0A, 0);
            arg1->unk00_field0 = 1;
            return;
    }
    BoardModelScaleSet(arg1->unk0A, arg0->rot.x, arg0->rot.y, 1.0f);
}

static void SetPlayerStartState(s32 arg0, s32 arg1) {
    PlayerStartWork *temp_r31;
    omObjData *temp_r30;

    temp_r30 = playerStartObj[arg0];
    temp_r31 = OM_GET_WORK_PTR(temp_r30, PlayerStartWork);
    temp_r31->unk00_field1 = arg1;
    temp_r31->unk02 = 0;
    temp_r31->unk01 = 0;
    switch (arg1) {
        case 4:
            hitFX[arg0] = HuAudFXPlay(0x300);
            break;
        case 5:
            break;
        case 6:
            temp_r31->unk06 = 0;
            break;
    }
}

static s32 GetPlayerStartState(s32 arg0) {
    PlayerStartWork *temp_r31;
    omObjData *temp_r30;

    temp_r30 = playerStartObj[arg0];
    temp_r31 = OM_GET_WORK_PTR(temp_r30, PlayerStartWork);
    return temp_r31->unk00_field1;
}

static void ExecStartRoll(void) {
    s32 sp84[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 var_r29;
    s32 var_r23;
    s32 var_r22;
    s32 var_r24;
    s32 i;

    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        for (i = 0; i < 4; i++) {
            SetPlayerStartState(i, 2);
        }
        while (GetPlayerStartState(3) != 0) {
            HuPrcVSleep();
        }
        _CheckFlag(FLAG_ID_MAKE(1, 11));
        var_r29 = startMesTbl[GWBoardGet()][0];
        BoardWinCreate(2, var_r29, BoardWinPortraitGetStar());
        BoardWinWait();
        var_r29 = startMesTbl[GWBoardGet()][1];
        BoardWinCreate(2, var_r29, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
        for (i = 0; i < 4; i++) {
            SetPlayerStartState(i, 2);
        }
        while (GetPlayerStartState(3) != 0) {
            HuPrcVSleep();
        }
    }
    for (i = 0; i < 4; i++) {
        SetPlayerStartState(i, 3);
    }
    if (tapWin != -1) {
        HuWinDispOn(tapWin);
    }
    while (1) {
        if (GetPlayerStartState(0) == 0 && GetPlayerStartState(1) == 0
            && GetPlayerStartState(2) == 0 && GetPlayerStartState(3) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    if (tapWin != -1) {
        HuWinDispOff(tapWin);
    }
    HuPrcSleep(30);
    HuPadRumbleAllStop();
    OrderPlayers();
    BoardStatusKill();
    BoardStatusCreate();
    BoardStatusItemSet(0);
    HuPrcVSleep();
    for (i = 0; i < 4; i++) {
        if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
            BoardTutorialHookExec(3, i);
        } else {
            if (i == 0) {
                var_r29 = startMesTbl[GWBoardGet()][2];
            } else {
                var_r29 = playerOrderMesTbl[i - 1];
            }
            BoardWinCreate(0, var_r29, -1);
            BoardWinInsertMesSet(BoardPlayerGetCharMess(i), i);
            BoardWinWait();
        }
        BoardStatusShowSet(i, 1);
        SetPlayerStartState(playerOrderOld[i], 6);
        BoardPlayerMotionShiftSet(i, 7, 0.0f, 8.0f, 0);
        HuPrcSleep(8);
        while (!BoardPlayerMotionEndCheck(i)) {
            HuPrcVSleep();
        }
    }
    BoardWinKill();
    for (i = 0; i < 4; i++) {
        BoardPlayerIdleSet(i);
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        var_r29 = startMesTbl[GWBoardGet()][3];
        BoardWinCreate(2, var_r29, BoardWinPortraitGetStar());
        BoardWinWait();
        HuPrcSleep(30);
        if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
            var_r22 = 100;
            var_r23 = 1;
        } else {
            var_r22 = 10;
            var_r23 = 6;
        }
        for (i = 0; i < var_r22; i++) {
            for (var_r24 = 0; var_r24 < 4; var_r24++) {
                BoardPlayerCoinsAdd(var_r24, 1);
            }
            HuAudFXPlay(7);
            HuPrcSleep(var_r23);
        }
        for (i = 0; i < 4; i++) {
            BoardPlayerMotionShiftSet(i, 7, 0.0f, 8.0f, 0);
        }
        HuAudFXPlay(0xF);
        while (1) {
            if (BoardPlayerMotionEndCheck(0) && BoardPlayerMotionEndCheck(1)
                && BoardPlayerMotionEndCheck(2) && BoardPlayerMotionEndCheck(3)) {
                break;
            }
            HuPrcVSleep();
        }
        HuPrcSleep(60);
        for (i = 0; i < 4; i++) {
            BoardPlayerIdleSet(i);
        }
        var_r29 = startMesTbl[GWBoardGet()][4];
        BoardWinCreate(2, var_r29, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
    }
}

static void InitCamera(void) {
    Vec sp14;
    Vec sp8;

    camStartFocusPos.x = 0.0f;
    camStartFocusPos.y = 100.0f;
    camStartFocusPos.z = 500.0f;
    switch (GWBoardGet()) {
        case BOARD_ID_MAIN1:
            camStartFocusPos.z -= 200.0f;
            camStartFocusPos.x -= 150.0f;
            break;
        case BOARD_ID_MAIN4:
            camStartFocusPos.z -= 250.0f;
            camStartFocusPos.x -= 150.0f;
            break;
        case BOARD_ID_MAIN5:
            camStartFocusPos.z -= 400.0f;
            camStartFocusPos.x -= 150.0f;
            break;
        case BOARD_ID_MAIN6:
            camStartFocusPos.z -= 500.0f;
            break;
        case BOARD_ID_EXTRA1:
            camStartFocusPos.z -= 520.0f;
            camStartFocusPos.x -= 150.0f;
            break;
        case BOARD_ID_EXTRA2:
            camStartFocusPos.z -= 250.0f;
            camStartFocusPos.x -= 150.0f;
            break;
    }
    camFocus = BoardModelCreate(0x7000A, NULL, 0);
    BoardModelVisibilitySet(camFocus, 0);
    BoardModelPosSetV(camFocus, &camStartFocusPos);
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardCameraMoveSet(0);
        sp14.x = spacePos.x + 150.0f;
        sp14.y = spacePos.y + 100.0f;
        sp14.z = spacePos.z + 150.0f;
        BoardModelPosSetV(camFocus, &sp14);
        sp8.x = -22.0f;
        sp8.y = 0.0f;
        sp8.z = 0.0f;
        sp14.x = sp14.y = sp14.z = 0.0f;
        BoardCameraMotionStartEx(camFocus, &sp8, NULL, 1500.0f, -1.0f, 1);
        BoardCameraMotionWait();
        BoardCameraMoveSet(1);
    } else {
        sp14.x = 0.0f;
        sp14.y = 0.0f;
        sp14.z = 0.0f;
        sp8.x = -70.0f;
        sp8.y = 0.0f;
        sp8.z = 0.0f;
        BoardCameraMoveSet(0);
        BoardCameraMotionStartEx(camFocus, &sp8, &sp14, 14000.0f, -1.0f, 1);
        BoardCameraMotionWait();
        BoardCameraMoveSet(1);
    }
}

static void InitHost(void) {
    Vec sp8;

    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        hostMdl = BoardStarHostMdlGet();
        sp8.x = spacePos.x + 150.0f;
        sp8.y = spacePos.y;
        sp8.z = spacePos.z - 50.0f;
        BoardModelPosSetV(hostMdl, &sp8);
        BoardModelVisibilitySet(hostMdl, 1);
        BoardModelMotionStart(hostMdl, 1, 0x40000001);
    }
}

static void CreateTapWin(void) {
    float sp8[2];
    float var_f31;
    float var_f30;
    s32 var_r31;

    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        var_r31 = 0x120014;
        HuWinMesMaxSizeGet(1, sp8, var_r31);
        var_f31 = -10000.0f;
        var_f30 = 368.0f;
        tapWin = HuWinCreate(var_f31, var_f30, sp8[0], sp8[1], 0);
        HuWinBGTPLvlSet(tapWin, 0.0f);
        HuWinMesSpeedSet(tapWin, 0);
        HuWinMesSet(tapWin, var_r31);
        HuWinDispOff(tapWin);
    }
}

static void OrderPlayers(void) {
    s32 temp_r29;
    PlayerConfig *temp_r28;
    PlayerState *temp_r27;
    s32 i;
    s32 j;

    temp_r28 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(GWPlayerCfg), MEMORY_DEFAULT_NUM);
    temp_r27 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(GWPlayer), MEMORY_DEFAULT_NUM);
    for (i = 0; i < 4; i++) {
        playerOrderOld[i] = i;
        memcpy(temp_r28 + i, &GWPlayerCfg[i], sizeof(PlayerConfig));
        memcpy(temp_r27 + i, &GWPlayer[i], sizeof(PlayerState));
    }
    for (i = 0; i < 3; i++) {
        for (j = 3; j > i; j--) {
            if (playerOrderNew[j - 1] < playerOrderNew[j]) {
                temp_r29 = playerOrderNew[j];
                playerOrderNew[j] = playerOrderNew[j - 1];
                playerOrderNew[j - 1] = temp_r29;
                temp_r29 = playerOrderOld[j];
                playerOrderOld[j] = playerOrderOld[j - 1];
                playerOrderOld[j - 1] = temp_r29;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        memcpy(&GWPlayerCfg[i], temp_r28 + playerOrderOld[i], sizeof(PlayerConfig));
        memcpy(&GWPlayer[i], temp_r27 + playerOrderOld[i], sizeof(PlayerState));
        GWPlayer[i].port = GWPlayerCfg[i].pad_idx;
        GWPlayerCfg[i].pad_idx = GWPlayerCfg[i].pad_idx;
    }
    HuMemDirectFree(temp_r28);
    HuMemDirectFree(temp_r27);
}
