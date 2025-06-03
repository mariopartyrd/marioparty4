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
#include "ext_math.h"
#include "string.h"

typedef struct {
    struct {
        u8 isBoardVisible : 1;
        u8 state : 3;
        u8 index : 2;
        u8 isActionable : 1;
        u8 hasRolled : 1;
    };
    u8 delay;
    u8 time;
    s8 _unused;
    s8 digit;
    s16 yRot;
    s16 diceMdl;
    s16 model;
    s16 diceParManId;
    s8 tutJumpCountdown;
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

static s32 startMesTbl[9][5] = {
    { MAKE_MESSID(0x15, 0x01), MAKE_MESSID(0x15, 0x07), MAKE_MESSID(0x15, 0x0D), MAKE_MESSID(0x15, 0x16), MAKE_MESSID(0x15, 0x1C) },
    { MAKE_MESSID(0x15, 0x02), MAKE_MESSID(0x15, 0x08), MAKE_MESSID(0x15, 0x0E), MAKE_MESSID(0x15, 0x17), MAKE_MESSID(0x15, 0x1D) },
    { MAKE_MESSID(0x15, 0x03), MAKE_MESSID(0x15, 0x09), MAKE_MESSID(0x15, 0x0F), MAKE_MESSID(0x15, 0x18), MAKE_MESSID(0x15, 0x1E) },
    { MAKE_MESSID(0x15, 0x04), MAKE_MESSID(0x15, 0x0A), MAKE_MESSID(0x15, 0x10), MAKE_MESSID(0x15, 0x19), MAKE_MESSID(0x15, 0x1F) },
    { MAKE_MESSID(0x15, 0x05), MAKE_MESSID(0x15, 0x0B), MAKE_MESSID(0x15, 0x11), MAKE_MESSID(0x15, 0x1A), MAKE_MESSID(0x15, 0x20) },
    { MAKE_MESSID(0x15, 0x06), MAKE_MESSID(0x15, 0x0C), MAKE_MESSID(0x15, 0x12), MAKE_MESSID(0x15, 0x1B), MAKE_MESSID(0x15, 0x21) },
    { MAKE_MESSID(0x15, 0x01), MAKE_MESSID(0x15, 0x07), MAKE_MESSID(0x15, 0x0D), MAKE_MESSID(0x15, 0x16), MAKE_MESSID(0x15, 0x1C) },
    { MAKE_MESSID(0x15, 0x33), MAKE_MESSID(0x15, 0x34), MAKE_MESSID(0x15, 0x35), MAKE_MESSID(0x15, 0x36), MAKE_MESSID(0x15, 0x37) },
    { MAKE_MESSID(0x15, 0x3B), MAKE_MESSID(0x15, 0x3C), MAKE_MESSID(0x15, 0x3D), MAKE_MESSID(0x15, 0x3E), MAKE_MESSID(0x15, 0x3F) }
};

static s32 logoSprTbl[] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x57), DATA_MAKE_NUM(DATADIR_BOARD, 0x58), DATA_MAKE_NUM(DATADIR_BOARD, 0x59),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x5A), DATA_MAKE_NUM(DATADIR_BOARD, 0x5B), DATA_MAKE_NUM(DATADIR_BOARD, 0x5C),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x57), DATA_MAKE_NUM(DATADIR_BOARD, 0x5D), DATA_MAKE_NUM(DATADIR_BOARD, 0x5E)
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
    Vec pos;
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
        BoardSpacePosGet(0, GWPlayer->space_curr, &pos);
        BoardPlayerPosSetV(0, &pos);
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
    float scale;
    float angleF;
    s16 angleS;
    s16 anglePosY;

    logoSprGrp = HuSprGrpCreate(1);
    BoardSpriteCreate(logoSprTbl[GWBoardGet()], 1000, 0, &logoSpr);
    HuSprGrpMemberSet(logoSprGrp, 0, logoSpr);
    HuSprAttrSet(logoSprGrp, 0, 1);
    HuSprAttrSet(logoSprGrp, 0, 8);
    HuSprScaleSet(logoSprGrp, 0, 0.01f, 0.01f);
    HuSprGrpPosSet(logoSprGrp, 288.0f, 240.0f);
    for (angleS = 0; angleS < 90; angleS += 4) {
        OSs16tof32(&angleS, &angleF);
        scale = sind(angleF);
        HuSprScaleSet(logoSprGrp, 0, scale, scale);
        HuPrcVSleep();
    }
    HuSprScaleSet(logoSprGrp, 0, 1.0f, 1.0f);
    for (angleS = 0; angleS < 540; angleS += 4) {
        anglePosY = angleS % 180;
        OSs16tof32(&anglePosY, &angleF);
        scale = 1.0 + 0.7f * sind(angleF);
        HuSprScaleSet(logoSprGrp, 0, scale, scale);
        HuPrcVSleep();
    }
    HuSprScaleSet(logoSprGrp, 0, 1.0f, 1.0f);
    HuPrcSleep(0x78);
    for (angleS = 0; angleS < 90; angleS += 4) {
        OSs16tof32(&angleS, &angleF);
        scale = cosd(angleF);
        HuSprScaleSet(logoSprGrp, 0, scale, scale);
        HuPrcVSleep();
    }
    HuSprGrpKill(logoSprGrp);
    logoSprGrp = -1;
}

static void FocusStart(void) {
    Vec boardPos;
    Vec offset;
    Vec offset2;
    Vec camRot;
    float zoom;
    u32 i;

    for (zoom = 14000.0f; zoom >= 2000.0f; zoom -= 50.0f) {
        BoardCameraZoomSet(zoom);
        HuPrcVSleep();
    }
    BoardCameraZoomSet(2000.0f);
    BoardModelPosGet(camFocus, &boardPos);
    offset.x = spacePos.x + 150.0f;
    offset.y = spacePos.y + 100.0f;
    offset.z = spacePos.z + 150.0f;
    VECSubtract(&offset, &boardPos, &offset2);
    offset2.x /= 120.0f;
    offset2.y /= 120.0f;
    offset2.z /= 120.0f;
    HuAudSStreamFadeOut(streamStatus, 0x1388);
    for (i = 0; i < 120; i++) {
        VECAdd(&offset2, &boardPos, &boardPos);
        BoardModelPosSetV(camFocus, &boardPos);
        HuPrcVSleep();
    }
    BoardModelPosSetV(camFocus, &offset);
    camRot.x = -22.0f;
    camRot.y = 0.0f;
    camRot.z = 0.0f;
    BoardCameraMotionStartEx(camFocus, &camRot, NULL, 1500.0f, -1.0f, 21);
}

static void CreatePlayerStart(void) {
    Vec boardPos;
    float offsetX;
    omObjData *boardObj;
    PlayerStartWork *boardData;
    s8 i;

    BoardModelPosGet(camFocus, &boardPos);
    for (i = 0; i < 4; i++) {
        playerOrderOld[i] = i;
        boardObj = omAddObjEx(boardObjMan, 0x100, 0, 0, -1, ExecPlayerStart);
        playerStartObj[i] = boardObj;
        boardData = OM_GET_WORK_PTR(boardObj, PlayerStartWork);
        boardData->isBoardVisible = 0;
        boardData->index = i;
        boardData->_unused = -1;
        boardData->model = -1;
        boardData->diceParManId = -1;
        boardData->state = 1;
        boardData->delay = i * 30;
        boardData->isActionable = 0;
        boardData->hasRolled = 0;
        boardData->yRot = 2;
        boardData->digit = 1;
        boardData->tutJumpCountdown = 0x3C;
        boardData->diceMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x18), NULL, 0);
        BoardModelVisibilitySet(boardData->diceMdl, 0);
        BoardModelMotionSpeedSet(boardData->diceMdl, 0.0f);
        OSs8tof32(&i, &offsetX);
        offsetX = 135.0f * (offsetX - 2.0f + 0.5f);
        BoardModelVisibilitySet(BoardPlayerModelGet(playerOrderOld[boardData->index]), 1);
        boardObj->trans.x = boardPos.x + offsetX;
        boardObj->trans.y = boardPos.y + 700.0f;
        boardObj->trans.z = boardPos.z + 100.0f;
        BoardPlayerPosSet(playerOrderOld[boardData->index], boardObj->trans.x, boardObj->trans.y, boardObj->trans.z);
        BoardPlayerMotionShiftSet(playerOrderOld[boardData->index], 4, 10.0f, 1.0f, HU3D_MOTATTR_NONE);
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardMusStart(0, 0xC, 0x7F, 0);
    }
    while (GetPlayerStartState(3) != 0) {
        HuPrcVSleep();
    }
}

static void ExecPlayerStart(omObjData *object) {
    PlayerStartWork *data = OM_GET_WORK_PTR(object, PlayerStartWork);

    if (data->isBoardVisible != 0 || BoardIsKill()) {
        if (hitFX[data->index] != -1) {
            HuAudFXStop(hitFX[data->index]);
            hitFX[data->index] = -1;
        }
        playerStartObj[data->index] = NULL;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }
    if (data->delay != 0) {
        data->delay--;
        return;
    }
    switch (data->state) {
        case 0:
            break;
        case 1:
            PlayerFall(object, data);
            break;
        case 2:
            PlayerWaitSpeak(object, data);
            break;
        case 3:
            PlayerDiceFall(object, data);
            break;
        case 4:
            PlayerDiceRoll(object, data);
            break;
        case 5:
            PlayerDiceNumShow(object, data);
            break;
        case 6:
            PlayerDiceNumHide(object, data);
            break;
    }
}

static void PlayerFall(omObjData *object, PlayerStartWork *data) {
    float fall_duration;

    if (data->isActionable != 0) {
        SetPlayerStartState(playerOrderOld[data->index], 0);
        BoardPlayerIdleSet(playerOrderOld[data->index]);
        if (_CheckFlag(FLAG_ID_MAKE(1, 11)) && data->index == 3) {
            BoardTutorialHookExec(0, 0);
        }
        return;
    }
    if (data->time > 200) {
        data->time = -56;
    }
    OSu8tof32(&data->time, &fall_duration);
    object->trans.y += -0.08166667f * fall_duration * fall_duration;
    if (object->trans.y < spacePos.y) {
        object->trans.y = spacePos.y;
        data->time = 0;
        BoardPlayerMotionShiftSet(playerOrderOld[data->index], 5, 0.0f, 4.0f, HU3D_MOTATTR_NONE);
        data->delay = 0xC;
        data->isActionable = 1;
    }
    data->time++;
    BoardPlayerPosSet(playerOrderOld[data->index], object->trans.x, object->trans.y, object->trans.z);
}

static void PlayerWaitSpeak(omObjData *object, PlayerStartWork *data) {
    float yRot;

    if (data->time == 0) {
        yRot = 180.0f + BoardPlayerRotYGet(playerOrderOld[data->index]);
        BoardPlayerMotBlendSet(playerOrderOld[data->index], yRot, 0xF);
        data->time = 1;
        return;
    }
    if (BoardPlayerMotBlendCheck(playerOrderOld[data->index])) {
        BoardPlayerIdleSet(playerOrderOld[data->index]);
        SetPlayerStartState(playerOrderOld[data->index], 0);
    }
}

static void PlayerDiceFall(omObjData *object, PlayerStartWork *data) {
    Vec boardPos;
    float max;
    float min;
    s32 i;

    if (data->time == 0) {
        HuAudFXPlay(0x302);
        BoardPlayerPosGet(playerOrderOld[data->index], &boardPos);
        min = 250.0f;
        max = 700.0f;
        object->rot.x = (min - max) / 30.0f;
        boardPos.y += max;
        BoardModelPosSetV(data->diceMdl, &boardPos);
        BoardModelVisibilitySet(data->diceMdl, 1);
    } else {
        if (data->time > 30.0f) {
            if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
                if (data->index == 3) {
                    BoardTutorialHookExec(1, 0);
                    for (i = 0; i < 4; i++) {
                        SetPlayerStartState(playerOrderOld[i], 4);
                    }
                }
                return;
            }
            SetPlayerStartState(playerOrderOld[data->index], 4);
            return;
        }
        BoardModelPosGet(data->diceMdl, &boardPos);
        boardPos.y += object->rot.x;
        BoardModelPosSetV(data->diceMdl, &boardPos);
    }
    data->time++;
}

static s32 digitMdlTbl[9] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x0D), DATA_MAKE_NUM(DATADIR_BOARD, 0x0E), DATA_MAKE_NUM(DATADIR_BOARD, 0x0F),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x10), DATA_MAKE_NUM(DATADIR_BOARD, 0x11), DATA_MAKE_NUM(DATADIR_BOARD, 0x12),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x13), DATA_MAKE_NUM(DATADIR_BOARD, 0x14), DATA_MAKE_NUM(DATADIR_BOARD, 0x15)
};

static s32 playerOrderMesTbl[3] = {
    MAKE_MESSID(0x15, 0x13),
    MAKE_MESSID(0x15, 0x14),
    MAKE_MESSID(0x15, 0x15)
};

static void PlayerDiceRoll(omObjData *object, PlayerStartWork *data) {
    Vec boardPos;
    float time;
    u32 jumpCheck;
    s8 player;
    s8 digit;

    jumpCheck = 0;
    if (data->time > data->yRot) {
        data->time = 0;
        digit = data->digit;
        do {
            data->digit = BoardRandMod(9);
        } while (data->digit == digit);
        OSs8tof32(&data->digit, &time);
        BoardModelMotionTimeSet(data->diceMdl, time + 0.5f);
    }
    if (data->hasRolled == 0) {
        if (GWPlayer[playerOrderOld[data->index]].com) {
            if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
                if (data->tutJumpCountdown != 0) {
                    data->tutJumpCountdown--;
                } else {
                    jumpCheck = PAD_BUTTON_A;
                }
            } else if (BoardRandMod(100) < 5) {
                jumpCheck = PAD_BUTTON_A;
            }
        } else {
            jumpCheck = HuPadBtnDown[GWPlayer[playerOrderOld[data->index]].port];
        }
        if (jumpCheck == PAD_BUTTON_A) {
            BoardPlayerDiceJumpStart(playerOrderOld[data->index]);
            data->hasRolled = 1;
        }
    } else {
        if (BoardPlayerDiceJumpCheck(playerOrderOld[data->index])) {
            SetPlayerStartState(playerOrderOld[data->index], 5);
            data->yRot = 360;
            object->rot.x = object->rot.y = 1.0f;
            data->digit = BoardRandMod(9);
            HuAudFXPlay(0x303);
            if (hitFX[data->index] != -1) {
                HuAudFXStop(hitFX[data->index]);
                hitFX[data->index] = -1;
            }
            player = 0;
            while (player < 4) {
                if (playerOrderNew[player] == data->digit && player != playerOrderOld[data->index]) {
                    data->digit = BoardRandMod(9);
                    player = 0;
                } else {
                    player++;
                }
            }
            if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
                data->digit = tutorialRollTbl[data->index];
            }
            playerOrderNew[playerOrderOld[data->index]] = data->digit;
            data->model = BoardModelCreate(digitMdlTbl[data->digit], NULL, 0);
            BoardModelPosGet(data->diceMdl, &boardPos);
            boardPos.x += 50.0 * sin(0.0);
            boardPos.z += 50.0 * cos(0.0);
            BoardModelPosSetV(data->model, &boardPos);
            BoardModelMotionStart(data->model, 0, 0);
            BoardModelMotionSpeedSet(data->model, 0.0f);
            BoardModelMotionTimeSet(data->model, 0.0f);
            BoardModelLayerSet(data->model, 2);
            data->diceParManId = BoardDiceEffectCreate();
            Hu3DParManPosSet(data->diceParManId, boardPos.x, boardPos.y, boardPos.z);
            Hu3DParManTimeLimitSet(data->diceParManId, 0x96);
            BoardModelVisibilitySet(data->diceMdl, 0);
            return;
        }
    }
    data->time++;
}

static void PlayerDiceNumShow(omObjData *object, PlayerStartWork *data) {
    float yRot;

    data->yRot -= 18;
    if (data->yRot < 0) {
        data->yRot = 0;
        SetPlayerStartState(playerOrderOld[data->index], 0);
        if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
            BoardTutorialHookExec(2, 0);
        }
    }
    OSs16tof32(&data->yRot, &yRot);
    BoardModelRotYSet(data->model, yRot);
}

static void PlayerDiceNumHide(omObjData *object, PlayerStartWork *data) {
    float yRot;

    switch (data->time) {
        case 0:
            data->yRot += 18;
            if (data->yRot > 360) {
                data->yRot = 0;
                data->time = 1;
                object->rot.x = 1.0f;
                object->rot.y = 1.0f;
            }
            OSs16tof32(&data->yRot, &yRot);
            BoardModelRotYSet(data->model, yRot);
            return;
        case 1:
            data->yRot += 9;
            if (data->yRot > 180) {
                data->yRot = 0;
                data->time = 2;
            }
            OSs16tof32(&data->yRot, &yRot);
            object->rot.x = 1.0 + 1.3f * sind(yRot);
            break;
        case 2:
            data->yRot += 9;
            if (data->yRot > 180) {
                data->yRot = 179;
                data->time = 3;
            }
            OSs16tof32(&data->yRot, &yRot);
            object->rot.x = cosd(0.5f * yRot);
            object->rot.y = 1.0 + 1.3f * sind(yRot);
            break;
        case 3:
            BoardModelVisibilitySet(data->model, 0);
            data->isBoardVisible = 1;
            return;
    }
    BoardModelScaleSet(data->model, object->rot.x, object->rot.y, 1.0f);
}

static void SetPlayerStartState(s32 player, s32 state) {
    PlayerStartWork *data;
    omObjData *object;

    object = playerStartObj[player];
    data = OM_GET_WORK_PTR(object, PlayerStartWork);
    data->state = state;
    data->time = 0;
    data->delay = 0;
    switch (state) {
        case 4:
            hitFX[player] = HuAudFXPlay(0x300);
            break;
        case 5:
            break;
        case 6:
            data->yRot = 0;
            break;
    }
}

static s32 GetPlayerStartState(s32 player) {
    PlayerStartWork *data;
    omObjData *object;

    object = playerStartObj[player];
    data = OM_GET_WORK_PTR(object, PlayerStartWork);
    return data->state;
}

static void ExecStartRoll(void) {
    s32 sp84[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 id;
    s32 time;
    s32 coinCount;
    s32 j;
    s32 i;

    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        for (i = 0; i < 4; i++) {
            SetPlayerStartState(i, 2);
        }
        while (GetPlayerStartState(3) != 0) {
            HuPrcVSleep();
        }
        _CheckFlag(FLAG_ID_MAKE(1, 11));
        id = startMesTbl[GWBoardGet()][0];
        BoardWinCreate(2, id, BoardWinPortraitGetStar());
        BoardWinWait();
        id = startMesTbl[GWBoardGet()][1];
        BoardWinCreate(2, id, BoardWinPortraitGetStar());
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
                id = startMesTbl[GWBoardGet()][2];
            } else {
                id = playerOrderMesTbl[i - 1];
            }
            BoardWinCreate(0, id, -1);
            BoardWinInsertMesSet(BoardPlayerGetCharMess(i), i);
            BoardWinWait();
        }
        BoardStatusShowSet(i, 1);
        SetPlayerStartState(playerOrderOld[i], 6);
        BoardPlayerMotionShiftSet(i, 7, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
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
        id = startMesTbl[GWBoardGet()][3];
        BoardWinCreate(2, id, BoardWinPortraitGetStar());
        BoardWinWait();
        HuPrcSleep(30);
        if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
            coinCount = 100;
            time = 1;
        } else {
            coinCount = 10;
            time = 6;
        }
        for (i = 0; i < coinCount; i++) {
            for (j = 0; j < 4; j++) {
                BoardPlayerCoinsAdd(j, 1);
            }
            HuAudFXPlay(7);
            HuPrcSleep(time);
        }
        for (i = 0; i < 4; i++) {
            BoardPlayerMotionShiftSet(i, 7, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
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
        id = startMesTbl[GWBoardGet()][4];
        BoardWinCreate(2, id, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
    }
}

static void InitCamera(void) {
    Vec offset;
    Vec rotTarget;

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
    camFocus = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x0A), NULL, 0);
    BoardModelVisibilitySet(camFocus, 0);
    BoardModelPosSetV(camFocus, &camStartFocusPos);
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardCameraMoveSet(0);
        offset.x = spacePos.x + 150.0f;
        offset.y = spacePos.y + 100.0f;
        offset.z = spacePos.z + 150.0f;
        BoardModelPosSetV(camFocus, &offset);
        rotTarget.x = -22.0f;
        rotTarget.y = 0.0f;
        rotTarget.z = 0.0f;
        offset.x = offset.y = offset.z = 0.0f;
        BoardCameraMotionStartEx(camFocus, &rotTarget, NULL, 1500.0f, -1.0f, 1);
        BoardCameraMotionWait();
        BoardCameraMoveSet(1);
    } else {
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = 0.0f;
        rotTarget.x = -70.0f;
        rotTarget.y = 0.0f;
        rotTarget.z = 0.0f;
        BoardCameraMoveSet(0);
        BoardCameraMotionStartEx(camFocus, &rotTarget, &offset, 14000.0f, -1.0f, 1);
        BoardCameraMotionWait();
        BoardCameraMoveSet(1);
    }
}

static void InitHost(void) {
    Vec newPos;

    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        hostMdl = BoardStarHostMdlGet();
        newPos.x = spacePos.x + 150.0f;
        newPos.y = spacePos.y;
        newPos.z = spacePos.z - 50.0f;
        BoardModelPosSetV(hostMdl, &newPos);
        BoardModelVisibilitySet(hostMdl, 1);
        BoardModelMotionStart(hostMdl, 1, 0x40000001);
    }
}

static void CreateTapWin(void) {
    float dimensions[2];
    float x;
    float y;
    s32 id;

    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        id = MAKE_MESSID(0x12, 0x14);
        HuWinMesMaxSizeGet(1, dimensions, id);
        x = -10000.0f;
        y = 368.0f;
        tapWin = HuWinCreate(x, y, dimensions[0], dimensions[1], 0);
        HuWinBGTPLvlSet(tapWin, 0.0f);
        HuWinMesSpeedSet(tapWin, 0);
        HuWinMesSet(tapWin, id);
        HuWinDispOff(tapWin);
    }
}

static void OrderPlayers(void) {
    s32 pOrderTemp;
    PlayerConfig *playerCfg;
    PlayerState *state;
    s32 i;
    s32 j;

    playerCfg = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(GWPlayerCfg), MEMORY_DEFAULT_NUM);
    state = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(GWPlayer), MEMORY_DEFAULT_NUM);
    for (i = 0; i < 4; i++) {
        playerOrderOld[i] = i;
        memcpy(playerCfg + i, &GWPlayerCfg[i], sizeof(PlayerConfig));
        memcpy(state + i, &GWPlayer[i], sizeof(PlayerState));
    }
    for (i = 0; i < 3; i++) {
        for (j = 3; j > i; j--) {
            if (playerOrderNew[j - 1] < playerOrderNew[j]) {
                pOrderTemp = playerOrderNew[j];
                playerOrderNew[j] = playerOrderNew[j - 1];
                playerOrderNew[j - 1] = pOrderTemp;
                pOrderTemp = playerOrderOld[j];
                playerOrderOld[j] = playerOrderOld[j - 1];
                playerOrderOld[j - 1] = pOrderTemp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        memcpy(&GWPlayerCfg[i], playerCfg + playerOrderOld[i], sizeof(PlayerConfig));
        memcpy(&GWPlayer[i], state + playerOrderOld[i], sizeof(PlayerState));
        GWPlayer[i].port = GWPlayerCfg[i].pad_idx;
        GWPlayerCfg[i].pad_idx = GWPlayerCfg[i].pad_idx;
    }
    HuMemDirectFree(playerCfg);
    HuMemDirectFree(state);
}
