#include "game/board/roll.h"
#include "game/audio.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/pause.h"
#include "game/board/player.h"
#include "game/board/tutorial.h"
#include "game/disp.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"

#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        u8 unk00_field2 : 3;
        u8 unk00_field3 : 2;
    };
    s8 unk01;
    s8 unk02;
    char unk03[1];
    s16 unk04;
    s16 unk06;
} DiceWork;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        u8 unk00_field2 : 1;
        u8 unk00_field3 : 2;
    };
    s8 unk01;
    s16 unk02;
    s16 unk04[2];
    float unk08;
} DiceDigitWork;

static void RollMain(void);
static void DiceCreate(s32 arg0);
static void DoInput(s32 arg0);
static void DiceWaitFull(s32 arg0);
static void DiceSetHit(s32 arg0);
static void RollDestroy(void);
static void DiceMain(omObjData *arg0);
static void DicePause(s32 arg0);
static void DicePauseAll(void);
static void DiceHideEffect(s32 arg0, s32 arg1);
static void DiceDigitMain(omObjData *arg0);
static void DiceDigitKill(DiceDigitWork *arg0);
static void DiceKill(void);
static void DiceDigitMove(DiceDigitWork *arg0, s32 arg1);
static void DiceDigitRotate(DiceDigitWork *arg0, s32 arg1);
static void SameRollExec(void);
static s32 GetBtnRoll(s32 arg0);
static s32 GetComBtnRoll(s32 arg0);

static s32 tutorialRoll[3];

static s8 diceValue[3];
static s8 rollPlayer;
static s8 numDice;
static s8 inputTimer;
static s8 maxRoll;
static s8 destMode;
static s8 diceSize;
s32 lbl_801D4098;
static char sameRollCoinStr[8];
static s8 tutorialRollF;
static Process *rollProc;

static s16 diceMdl[3] = { -1, -1, -1 };
static s16 diceEff[3] = { -1, -1, -1 };
static s16 rollWin = -1;

static omObjData *diceObj[3] = { NULL, NULL, NULL };
static omObjData *diceDigitObj[3] = { NULL, NULL, NULL };
static s32 diceSndStatus[3] = { -1, -1, -1 };

static HsfanimStruct00 diceEffParam = { 0x0096, { 0x00, 0x00 }, // padding?
    50.0f, 0.0f, 65.0f, { 0.0f, -0.195f, 0.0f }, 100.0f, 0.99f, 40.0f, 0.999f, 0x0004,
    { { 0xFF, 0xFF, 0x20, 0xFF }, { 0xFF, 0xFF, 0x00, 0xFF }, { 0xFF, 0xFF, 0x80, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { 0xFF, 0xFF, 0xFF, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 } } };

static s32 diceDigitMdlTbl[10] = { DATA_MAKE_NUM(DATADIR_BOARD, 0x0C), DATA_MAKE_NUM(DATADIR_BOARD, 0x0D), DATA_MAKE_NUM(DATADIR_BOARD, 0x0E),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x0F), DATA_MAKE_NUM(DATADIR_BOARD, 0x10), DATA_MAKE_NUM(DATADIR_BOARD, 0x11), DATA_MAKE_NUM(DATADIR_BOARD, 0x12),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x13), DATA_MAKE_NUM(DATADIR_BOARD, 0x14), DATA_MAKE_NUM(DATADIR_BOARD, 0x15) };

s32 BoardRollExec(s32 arg0)
{
    rollPlayer = arg0;
    inputTimer = 0;
    numDice = 1;
    diceSize = 0;
    maxRoll = 0xA;
    switch (BoardItemPrevGet()) {
        case 0:
            numDice = 1;
            break;
        case 2:
            numDice = 2;
            break;
        case 1:
            numDice = 2;
            break;
        case 3:
            numDice = 3;
            break;
    }
    if (BoardPlayerSizeGet(arg0) == 1) {
        diceSize = 1;
        maxRoll = 5;
    }
    else if (BoardPlayerSizeGet(arg0) == 2) {
        diceSize = 2;
        maxRoll = 10;
        if (BoardMegaDoubleDiceCheck() != 0) {
            numDice = 2;
        }
    }
    if (GWPlayer[rollPlayer].bowser_suit != 0) {
        diceSize = 3;
    }
    GWPlayer[arg0].num_dice = numDice;
    rollProc = HuPrcChildCreate(RollMain, 0x2005, 0x6000, 0, boardMainProc);
    HuPrcDestructorSet2(rollProc, RollDestroy);
    while (rollProc != NULL) {
        HuPrcVSleep();
    }
    while (diceObj[0] || diceObj[1] || diceObj[2]) {
        HuPrcVSleep();
    }
    return destMode;
}

static void RollWinCreate(s32 playerNo)
{
    float sp8[2];
    float posX;
    float posY;
    s32 var_r29;
    s32 var_r27;
    s32 temp_r25;
    
    if (!_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        var_r27 = BoardPlayerItemCount(playerNo);
        if (GWTeamGet()) {
            temp_r25 = BoardPlayerSameTeamFind(playerNo);
            var_r27 += BoardPlayerItemCount(temp_r25);
        }
        if (BoardItemPrevGet() != -1 || var_r27 == 0 || _CheckFlag(FLAG_ID_MAKE(1, 9)) || BoardMegaDoubleDiceCheck()) {
            var_r29 = MAKE_MESSID(0x09, 0x04);
        }
        else {
            var_r29 = MAKE_MESSID(0x09, 0x02);
        }
        if (inputTimer != 0) {
            var_r29 = MAKE_MESSID(0x30, 0x25);
        }
        HuWinMesMaxSizeGet(1, sp8, var_r29);
        #if VERSION_PAL
        posY = HU_DISP_HEIGHT - 176; 
        switch (GWGameStat.language) {
            case 0:
            case 4:
                posX = -10000.0f;
                break;
            
            case 3:
                posX = HU_DISP_CENTERX - (sp8[0] / 2 - 32.0f);
                break;
            
            case 5:
                posX = HU_DISP_CENTERX - (sp8[0] / 2 - 16.0f);
                posY = 258; 
                break;
            
            default:
                posX = HU_DISP_CENTERX - (sp8[0] / 2 - 16.0f);
                break;
        }
        #else
        switch (GWGameStat.language) {
            case 0:
                posX = -10000.0f;
                break;
            case 1:
                posX = HU_DISP_CENTERX - (sp8[0] / 2 - 16.0f);
                break;
        }
        posY = HU_DISP_HEIGHT - 176; 
        #endif
        
        rollWin = HuWinCreate(posX, posY, sp8[0], sp8[1], 0);
        HuWinBGTPLvlSet(rollWin, 0.0f);
        HuWinMesSpeedSet(rollWin, 0);
        HuWinMesSet(rollWin, var_r29);
    }
}

void BoardRollKill(void)
{
    if (rollProc) {
        HuPrcKill(rollProc);
    }
    DicePauseAll();
    DiceKill();
}

void BoardRollUPauseSet(s32 arg0)
{
    if (!rollProc) {
        return;
    }
    BoardRollWinDispSet(arg0);
    BoardDiceVisibleSet(0, arg0);
    BoardDiceVisibleSet(1, arg0);
    BoardDiceVisibleSet(2, arg0);
    DiceHideEffect(0, arg0);
    DiceHideEffect(1, arg0);
    DiceHideEffect(2, arg0);
}

void BoardRollWinDispSet(s32 arg0)
{
    if (rollWin == -1) {
        return;
    }
    if (arg0 != 0) {
        HuWinDispOn(rollWin);
    }
    else {
        HuWinDispOff(rollWin);
    }
}

static void RollMain(void)
{
    
    s32 var_r28;
    
    s32 var_r30;
    
    s32 i;

    diceValue[0] = diceValue[1] = diceValue[2] = 0;
    if (BoardPlayerSizeGet(rollPlayer) == 2 || GWPlayer[rollPlayer].bowser_suit != 0) {
        BoardCameraViewSet(2);
    }
    BoardCameraMotionWait();
    BoardCameraTargetModelSet(-1);
    for (i = 0; i < numDice; i++) {
        RollWinCreate(rollPlayer);
        DiceCreate(i);
        DiceWaitFull(i);
        DoInput(i);
        if (rollWin != -1) {
            HuWinKill(rollWin);
            rollWin = -1;
        }
        if (destMode == -2 || destMode == -1 || destMode == -3 || destMode == -4) {
            HuPrcEnd();
        }
        BoardPlayerDiceJumpStart(rollPlayer);
        while (!BoardPlayerDiceJumpCheck(rollPlayer)) {
            HuPrcVSleep();
        }
        DiceSetHit(i);
        while (GWPlayer[rollPlayer].jump != 0) {
            HuPrcVSleep();
        }
    }
    for (var_r30 = i = 0; i < numDice; i++) {
        var_r30 += diceValue[i];
    }
    var_r28 = 0;
    switch (numDice) {
        case 2:
            if (diceValue[0] == diceValue[1]) {
                var_r28 = 1;
            }
            break;
        case 3:
            if (diceValue[0] == diceValue[1] && diceValue[0] == diceValue[2]) {
                var_r28 = 1;
            }
            break;
    }
    if (var_r28 != 0) {
        SameRollExec();
    }
    BoardDicePauseAll();
    while (!BoardDiceDoneCheck()) {
        HuPrcVSleep();
    }
    for (i = 0; i < numDice; i++) {
        BoardDiceStop(i);
    }
    destMode = var_r30;
    GWPlayer[rollPlayer].roll = var_r30;
    BoardRollCreate(rollPlayer, 1);
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardTutorialHookExec(6, 0);
    }
    if (tutorialRollF != 0) {
        tutorialRollF = 0;
    }
    HuPrcEnd();
}

static void DiceCreate(s32 arg0)
{
    Vec sp1C;
    float temp_f30;
    float var_f31;
    omObjData *temp_r31;
    DiceWork *temp_r30;
    s32 sp8;
    s32 spC[4] = { DATA_MAKE_NUM(DATADIR_BOARD, 0x18), DATA_MAKE_NUM(DATADIR_BOARD, 0x19), DATA_MAKE_NUM(DATADIR_BOARD, 0x1A),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x1B) };

    sp8 = 0;
    diceMdl[arg0] = BoardModelCreate(spC[diceSize], NULL, 0);
    temp_f30 = BoardRandMod(maxRoll) + 0.5f;
    BoardPlayerPosGet(rollPlayer, &sp1C);
    HuAudFXPlay(0x302);
    BoardModelMotionStart(diceMdl[arg0], 0, 0);
    BoardModelMotionSpeedSet(diceMdl[arg0], 0.0f);
    BoardModelMotionTimeSet(diceMdl[arg0], temp_f30);
    BoardModelScaleSet(diceMdl[arg0], 0.001f, 0.001f, 0.001f);
    temp_r31 = omAddObjEx(boardObjMan, 0x102, 0, 0, -1, DiceMain);
    temp_r30 = OM_GET_WORK_PTR(temp_r31, DiceWork);
    temp_r30->unk00_field0 = 0;
    temp_r30->unk00_field1 = 0;
    temp_r30->unk00_field2 = 0;
    temp_r30->unk00_field3 = arg0;
    temp_r30->unk04 = 0;
    temp_r30->unk01 = 4;
    temp_r30->unk02 = 0;
    diceObj[arg0] = temp_r31;
    var_f31 = 250.0f;
    if (diceSize == 2) {
        var_f31 = 625.0f;
    }
    else if (GWPlayer[rollPlayer].bowser_suit != 0) {
        var_f31 = 575.0f;
    }
    sp1C.y += var_f31;
    temp_r31->trans.x = sp1C.x;
    temp_r31->trans.y = sp1C.y;
    temp_r31->trans.z = sp1C.z;
    temp_r31->scale.x = 0.1f;
    temp_r31->scale.y = 0.1f;
    temp_r31->scale.z = 0.1f;
    sp1C.z += 70.0f;
}

static void DoInput(s32 arg0)
{
    s32 var_r31;
    s32 var_r30;
    u16 sp8[1];

    destMode = 0;
    lbl_801D4098 = 0;
    while (1) {
        HuPrcVSleep();
        *sp8 = GetBtnRoll(rollPlayer);
        if (BoardPauseActiveCheck()) {
            *sp8 = 0;
            continue;
        }
        if (*sp8 == 0x100) {
            inputTimer++;
            break;
        }
        if (inputTimer == 0) {
            if (*sp8 == 0x10) {
                destMode = -3;
                HuAudFXPlay(1);
                break;
            }
            if (*sp8 == 0x20) {
                destMode = -4;
                HuAudFXPlay(1);
                break;
            }
            var_r31 = BoardPlayerItemCount(rollPlayer);
            if (GWTeamGet()) {
                var_r30 = BoardPlayerSameTeamFind(rollPlayer);
                var_r31 += BoardPlayerItemCount(var_r30);
            }
            if (var_r31 == 0 || BoardItemPrevGet() != -1 || BoardMegaDoubleDiceCheck() || _CheckFlag(FLAG_ID_MAKE(1, 9))) {
                if (_CheckFlag(FLAG_ID_MAKE(1, 9)) && GWBoardGet() == BOARD_ID_MAIN6 && *sp8 == 0x200 && var_r31 != 0) {
                    HuAudFXPlay(4);
                }
            }
            else if (*sp8 == 0x200) {
                destMode = -2;
                HuAudFXPlay(3);
                BoardPauseDisableSet(1);
                break;
            }
        }
    }
}

static void DiceWaitFull(s32 arg0)
{
    DiceWork *temp_r31 = OM_GET_WORK_PTR(diceObj[arg0], DiceWork);

    while (temp_r31->unk00_field2 != 1) {
        HuPrcVSleep();
    }
}

static void DiceSetHit(s32 arg0)
{
    DiceWork *temp_r30 = OM_GET_WORK_PTR(diceObj[arg0], DiceWork);

    temp_r30->unk00_field2 = 2;
    temp_r30->unk04 = 0;
    BoardModelMotionSpeedSet(diceMdl[arg0], 0.0f);
    diceValue[arg0] = (s32)BoardModelMotionTimeGet(diceMdl[arg0]) + 1;
    if (tutorialRollF != 0 && tutorialRoll[arg0] != -1) {
        BoardModelMotionTimeSet(diceMdl[arg0], tutorialRoll[arg0] - 1);
        diceValue[arg0] = tutorialRoll[arg0];
    }
}

static void RollDestroy(void)
{
    if (rollWin != -1) {
        HuWinKill(rollWin);
        rollWin = -1;
    }
    if (rollProc) {
        HuPrcKill(rollProc);
    }
    DicePauseAll();
    DiceKill();
    BoardConfettiKill();
    rollProc = NULL;
}

static void DiceMain(omObjData *arg0)
{
    DiceWork *temp_r29 = OM_GET_WORK_PTR(arg0, DiceWork);
    float temp_f29;
    float var_f28;
    float var_f27;
    s16 temp_r26;
    s16 temp_r27;

    if (temp_r29->unk00_field0 != 0 || BoardIsKill()) {
        if (diceSndStatus[temp_r29->unk00_field3] != -1) {
            HuAudFXStop(diceSndStatus[temp_r29->unk00_field3]);
            diceSndStatus[temp_r29->unk00_field3] = -1;
        }
        if (diceMdl[temp_r29->unk00_field3] != -1) {
            BoardModelKill(diceMdl[temp_r29->unk00_field3]);
            diceMdl[temp_r29->unk00_field3] = -1;
        }
        if (diceEff[temp_r29->unk00_field3] != -1) {
            Hu3DParManKill(diceEff[temp_r29->unk00_field3]);
            diceEff[temp_r29->unk00_field3] = -1;
        }
        DicePause(temp_r29->unk00_field3);
        diceObj[temp_r29->unk00_field3] = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    switch (temp_r29->unk00_field2) {
        case 0:
            if (temp_r29->unk06 >= 0x438) {
                temp_r29->unk00_field2 = 1;
                arg0->scale.x = arg0->scale.y = arg0->scale.z = 1.0f;
                arg0->rot.y = temp_r29->unk04 = 0;
            }
            else {
                if (temp_r29->unk04 == 0 && diceSndStatus[temp_r29->unk00_field3] == -1) {
                    diceSndStatus[temp_r29->unk00_field3] = HuAudFXPlay(0x300);
                }
                arg0->rot.y = temp_r29->unk06 % 360;
                temp_r29->unk06 += 0x19;
                if (temp_r29->unk04 < 0xB4) {
                    var_f27 = 0.0f;
                    var_f28 = 1.0f;
                }
                else {
                    var_f27 = 1.0f;
                    var_f28 = 0.5f;
                }
                arg0->scale.x = var_f27 + var_f28 * sind((float)(temp_r29->unk04 % 180));
                arg0->scale.y = arg0->scale.x;
                arg0->scale.z = arg0->scale.x;
                if (temp_r29->unk04 <= 360) {
                    if (temp_r29->unk04 < 0xB4) {
                        temp_r29->unk04 += 6;
                    }
                    else {
                        temp_r29->unk04 += 0x12;
                    }
                    if (temp_r29->unk04 > 360) {
                        temp_r29->unk04 = 360;
                    }
                }
            }
            break;
        case 1:
            temp_r29->unk04 += 4;
            if (temp_r29->unk04 > 360) {
                temp_r29->unk04 -= 360;
            }
            OSs16tof32(&temp_r29->unk04, &temp_f29);
            arg0->trans.y += 0.2f * sind(temp_f29);
            break;
        case 2:
            temp_r29->unk04++;
            if (temp_r29->unk04 >= 8) {
                if (diceSndStatus[temp_r29->unk00_field3] != -1) {
                    HuAudFXStop(diceSndStatus[temp_r29->unk00_field3]);
                    diceSndStatus[temp_r29->unk00_field3] = -1;
                }
                HuAudFXPlay(0x303);
                HuAudFXPlay(0x30C);
                temp_r29->unk00_field2 = 3;
                temp_r29->unk04 = 0;
                BoardDiceValueSet(temp_r29->unk00_field3, diceValue[temp_r29->unk00_field3]);
                diceEff[temp_r29->unk00_field3] = BoardDiceEffectCreate();
                Hu3DParManPosSet(diceEff[temp_r29->unk00_field3], arg0->trans.x, arg0->trans.y, arg0->trans.z);
                BoardModelVisibilitySet(diceMdl[temp_r29->unk00_field3], 0);
            }
            else {
                OSs16tof32(&temp_r29->unk04, &temp_f29);
                if (temp_r29->unk04 < 4) {
                    arg0->trans.y += 10.0f + (0.5f * temp_f29);
                    arg0->scale.x += 0.1f * sind(4.0f * temp_f29);
                    arg0->scale.y = arg0->scale.x;
                    arg0->scale.z = arg0->scale.x;
                }
                else {
                    BoardModelAlphaSet(diceMdl[temp_r29->unk00_field3], 0xFF - (temp_r29->unk04 << 5));
                }
                arg0->trans.y += -0.49f * temp_f29 * temp_f29;
            }
            break;
        case 3:
            break;
    }
    if (diceEff[temp_r29->unk00_field3] != -1 && ++temp_r29->unk04 >= 150) {
        temp_r29->unk00_field0 = 1;
        DiceHideEffect(temp_r29->unk00_field3, 0);
    }
    if (temp_r29->unk00_field1 == 0 || temp_r29->unk00_field2 != 3) {
        if (temp_r29->unk02++ > temp_r29->unk01) {
            temp_r29->unk02 = 0;
            temp_r26 = BoardModelMotionTimeGet(diceMdl[temp_r29->unk00_field3]);
            do {
                temp_r27 = BoardRandMod(maxRoll);
            } while (temp_r27 == temp_r26);
            BoardModelMotionTimeSet(diceMdl[temp_r29->unk00_field3], temp_r27 + 0.5f);
        }
    }
    BoardModelPosSet(diceMdl[temp_r29->unk00_field3], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotSet(diceMdl[temp_r29->unk00_field3], arg0->rot.x, arg0->rot.y, arg0->rot.z);
    BoardModelScaleSet(diceMdl[temp_r29->unk00_field3], arg0->scale.x, arg0->scale.y, arg0->scale.z);
}

static void DicePause(s32 arg0)
{
    omObjData *temp_r31 = diceObj[arg0];

    if (temp_r31) {
        OM_GET_WORK_PTR(temp_r31, DiceWork)->unk00_field0 = 1;
    }
}

static void DicePauseAll(void)
{
    DicePause(0);
    DicePause(1);
    DicePause(2);
}

s16 BoardDiceEffectCreate(void)
{
    s16 temp_r31;
    s16 temp_r30;
    AnimData *temp_r29;
    void *temp_r28;

    temp_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_BOARD, 0x6B), MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r29 = HuSprAnimRead(temp_r28);
    temp_r31 = Hu3DParManCreate(temp_r29, 0x64, &diceEffParam);
    Hu3DParManAttrSet(temp_r31, 0x108);
    Hu3DParManRotSet(temp_r31, 0.0f, 0.0f, 0.0f);
    Hu3DParManVecSet(temp_r31, 0.0f, 0.4f, 0.2f);
    Hu3DParManTimeLimitSet(temp_r31, 0x96);
    temp_r30 = Hu3DParManModelIDGet(temp_r31);
    Hu3DModelLayerSet(temp_r30, 1);
    Hu3DParticleBlendModeSet(temp_r30, 0);
    return temp_r31;
}

static void DiceHideEffect(s32 arg0, s32 arg1)
{
    s16 temp_r31;

    if (diceEff[arg0] == -1) {
        return;
    }
    temp_r31 = Hu3DParManModelIDGet(diceEff[arg0]);
    if (arg1 != 0) {
        Hu3DModelAttrReset(temp_r31, HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(temp_r31, HU3D_ATTR_DISPOFF);
    }
}

void BoardDicePauseAll(void)
{
    DiceDigitWork *temp_r30;
    s32 i;

    for (i = 0; i < numDice; i++) {
        if (diceDigitObj[i]) {
            temp_r30 = OM_GET_WORK_PTR(diceDigitObj[i], DiceDigitWork);
            temp_r30->unk00_field1 = 1;
            temp_r30->unk00_field2 = 1;
            temp_r30->unk02 = 0;
        }
    }
}

BOOL BoardDiceDoneCheck(void)
{
    DiceDigitWork *temp_r30;
    s32 i;

    for (i = 0; i < numDice; i++) {
        if (diceDigitObj[i]) {
            temp_r30 = OM_GET_WORK_PTR(diceDigitObj[i], DiceDigitWork);
            if (temp_r30->unk00_field2 != 0) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

void BoardDiceStop(s32 arg0)
{
    DiceDigitWork *temp_r31;

    if (!diceDigitObj[arg0]) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(diceDigitObj[arg0], DiceDigitWork);
    temp_r31->unk00_field0 = 1;
}

void BoardDiceVisibleSet(s32 arg0, s32 arg1)
{
    DiceDigitWork *temp_r31;

    if (!diceDigitObj[arg0]) {
        return;
    }
    temp_r31 = OM_GET_WORK_PTR(diceDigitObj[arg0], DiceDigitWork);
    if ((temp_r31->unk01 / 10) == 0) {
        BoardModelVisibilitySet(temp_r31->unk04[1], 0);
    }
    else {
        BoardModelVisibilitySet(temp_r31->unk04[1], arg1);
    }
    BoardModelVisibilitySet(temp_r31->unk04[0], arg1);
}

void BoardDiceValueSet(s32 arg0, s32 arg1)
{
    omObjData *temp_r27;
    DiceDigitWork *temp_r31;
    Vec spC;
    s16 sp8[2];
    s16 temp_r30;
    s16 i;

    if (arg1 > 0x63) {
        arg1 = 0x63;
    }
    sp8[0] = (arg1 % 10);
    sp8[1] = (arg1 / 10);
    BoardPlayerPosGet(GWSystem.player_curr, &spC);
    spC.y += 300.0f;
    temp_r27 = omAddObjEx(boardObjMan, 0x102, 0, 0, -1, DiceDigitMain);
    temp_r31 = OM_GET_WORK_PTR(temp_r27, DiceDigitWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field1 = 0;
    temp_r31->unk00_field2 = 0;
    temp_r31->unk00_field3 = arg0;
    temp_r31->unk08 = 0.3f;
    temp_r31->unk01 = arg1;
    temp_r31->unk02 = 360;
    for (i = 0; i < 2; i++) {
        temp_r30 = BoardModelCreate(diceDigitMdlTbl[sp8[i]], NULL, 0);
        BoardModelPosSetV(temp_r30, &spC);
        BoardModelMotionStart(temp_r30, 0, 0);
        BoardModelMotionSpeedSet(temp_r30, 0.0f);
        BoardModelMotionTimeSet(temp_r30, 0.0f);
        BoardModelScaleSet(temp_r30, 0.143f, 0.143f, 0.143f);
        temp_r31->unk04[i] = temp_r30;
    }
    if (sp8[1] == 0) {
        BoardModelVisibilitySet(temp_r31->unk04[1], 0);
    }
    diceDigitObj[arg0] = temp_r27;
}

static void DiceDigitMain(omObjData *arg0)
{
    DiceDigitWork *temp_r31 = OM_GET_WORK_PTR(arg0, DiceDigitWork);

    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        DiceDigitKill(temp_r31);
        diceDigitObj[temp_r31->unk00_field3] = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    DiceDigitMove(temp_r31, temp_r31->unk00_field1);
    DiceDigitRotate(temp_r31, temp_r31->unk00_field1);
}

static void DiceDigitKill(DiceDigitWork *arg0)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        if (arg0->unk04[i] != -1) {
            BoardModelKill(arg0->unk04[i]);
        }
    }
}

static void DiceKill(void)
{
    DiceDigitWork *temp_r29;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (diceDigitObj[i]) {
            temp_r29 = OM_GET_WORK_PTR(diceDigitObj[i], DiceDigitWork);
            DiceDigitKill(temp_r29);
        }
    }
}

static void DiceDigitMove(DiceDigitWork *arg0, s32 arg1)
{
    s32 sp8 = 0;
    Vec sp30;
    Vec sp24;
    Vec sp54[2];
    Vec sp18 = { (HU_DISP_WIDTH / 2), (HU_DISP_HEIGHT * 155) / 480, 240.0f };
    Vec sp3C[2]
        = { { (HU_DISP_WIDTH * 1) / 4, (HU_DISP_HEIGHT * 155) / 480, 240.0f }, { (HU_DISP_WIDTH * 3) / 4, (HU_DISP_HEIGHT * 155) / 480, 240.0f } };
    Vec sp6C[3] = { { (HU_DISP_WIDTH * 1) / 4, (HU_DISP_HEIGHT * 155) / 480, 240.0f },
        { (HU_DISP_WIDTH * 3) / 4, (HU_DISP_HEIGHT * 155) / 480, 240.0f }, { (HU_DISP_WIDTH / 2), (HU_DISP_HEIGHT * 155) / 480, 240.0f } };
    Vec spC = { (HU_DISP_WIDTH / 2), (HU_DISP_HEIGHT * 176) / 480, 240.0f };
    Vec *var_r29;
    float var_f31;
    s16 var_r27;
    s16 i;

    var_r27 = (arg0->unk01 / 10);
    if (arg1 != 0) {
        var_r29 = &spC;
        var_f31 = -20.0f * arg0->unk00_field3;
    }
    else {
        switch (numDice) {
            case 1:
                var_r29 = &sp18;
                break;
            case 2:
                var_r29 = &sp3C[arg0->unk00_field3];
                break;
            case 3:
                var_r29 = &sp6C[arg0->unk00_field3];
                break;
        }
        var_f31 = 0.0f;
    }
    for (i = 0; i < 2; i++) {
        if (var_r27 == 0) {
            sp54[i].x = var_r29->x;
        }
        else if (i != 0) {
            sp54[i].x = var_r29->x - 30.0f;
        }
        else {
            sp54[i].x = var_r29->x + 30.0f;
        }
        sp54[i].y = var_r29->y;
        sp54[i].z = var_r29->z + var_f31;
    }
    for (i = 0; i < 2; i++) {
        BoardModelPosGet(arg0->unk04[i], &sp30);
        Hu3D2Dto3D(&sp54[i], 1, &sp54[i]);
        VECSubtract(&sp54[i], &sp30, &sp24);
        if (VECMag(&sp24) < 0.01f) {
            arg0->unk00_field2 = 0;
            if (arg1 != 0 && arg0->unk00_field3 != 0) {
                BoardModelVisibilitySet(arg0->unk04[i], 0);
            }
        }
        else {
            arg0->unk00_field2 = 1;
        }
        VECScale(&sp24, &sp24, arg0->unk08);
        VECAdd(&sp30, &sp24, &sp30);
        BoardModelPosSetV(arg0->unk04[i], &sp30);
    }
}

static void DiceDigitRotate(DiceDigitWork *arg0, s32 arg1)
{
    float var_f30;
    s32 i;

    if (arg1 != 0) {
        arg0->unk02 += 0x12;
        if (arg0->unk02 >= 360) {
            arg0->unk02 = 360;
        }
    }
    else {
        arg0->unk02 -= 0x12;
        if (arg0->unk02 <= 0) {
            arg0->unk02 = 0;
        }
    }
    OSs16tof32(&arg0->unk02, &var_f30);
    for (i = 0; i < 2; i++) {
        if (arg0->unk04[i] != -1) {
            BoardModelRotSet(arg0->unk04[i], 0.0f, var_f30, 0.0f);
        }
    }
}

static void SameRollExec(void)
{
    Vec sp8;
    float var_f31;
    s32 var_r28;
    s32 temp_r27;
    s32 var_r31;
    s32 i;
    s32 var_r29;

    temp_r27 = -1;
    BoardPauseDisableSet(1);
    var_r28 = 0x50;
    switch (numDice) {
        case 2:
            if (diceValue[0] == 7) {
                var_r31 = 0x1E;
            }
            else {
                var_r31 = 0xA;
            }
            break;
        case 3:
            if (diceValue[0] == 7) {
                var_r31 = 0x32;
                var_r28 = 0x118;
            }
            else if (diceValue[0] & 1) {
                var_r31 = 0x1E;
            }
            else {
                var_r31 = 0xA;
            }
            break;
        default:
            return;
    }
    sprintf(sameRollCoinStr, "%d", var_r31);
    BoardPlayerPosGet(rollPlayer, &sp8);
    if (BoardPlayerSizeGet(rollPlayer) == 2 || GWPlayer[rollPlayer].bowser_suit != 0) {
        sp8.y += 700.0f;
        var_f31 = 450.0f;
    }
    else {
        sp8.y += 600.0f;
        var_f31 = 300.0f;
    }
    BoardConfettiCreate(&sp8, var_r28, var_f31);
    BoardAudSeqPause(0, 1, 0x3E8);
    HuPrcSleep(0xA);
    temp_r27 = HuAudSStreamPlay(9);
    while (HuAudSStreamStatGet(temp_r27) != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 0x3E8);
    BoardWinCreate(0, MAKE_MESSID(9, 0), -1);
    BoardWinInsertMesSet(sameRollCoinStr, 0);
    BoardWinWait();
    BoardWinKill();
    if (var_r31 >= 0x32) {
        var_r29 = 1;
    }
    else if (var_r31 >= 0x14) {
        var_r29 = 3;
    }
    else {
        var_r29 = 6;
    }
    for (i = 0; i < var_r31; i++) {
        BoardPlayerCoinsAdd(rollPlayer, 1);
        HuAudFXPlay(7);
        HuPrcSleep(var_r29);
    }
    HuAudFXPlay(0xF);
    BoardConfettiStop();
    BoardPauseDisableSet(0);
}

static s32 GetBtnRoll(s32 arg0)
{
    s32 var_r31 = 0;
    s32 var_r29;

    if (boardTutorialUseItem >= 0 && boardTutorialUseItem <= 0xD) {
        var_r31 = 0x200;
        return var_r31;
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        var_r31 = 0x100;
        return var_r31;
    }
    if (!GWPlayer[arg0].com) {
        var_r29 = GWPlayer[arg0].port;
        var_r31 = HuPadBtnDown[var_r29];
        return var_r31;
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 9)) || BoardItemPrevGet() != -1) {
        return 0x100;
    }
    var_r31 = GetComBtnRoll(arg0);
    return var_r31;
}

static s32 GetComBtnRoll(s32 arg0)
{
    if (BoardItemPrevGet() != -1 || BoardPlayerItemCount(arg0) == 0 || BoardMegaDoubleDiceCheck() || _CheckFlag(FLAG_ID_MAKE(1, 9))) {
        return 0x100;
    }
    if (BoardComUseItemCheck(arg0)) {
        return 0x200;
    }
    return 0x100;
}

void BoardRollTutorialSet(s16 *arg0)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        tutorialRoll[i] = arg0[i];
    }
    tutorialRollF = 1;
}
