#include "game/board/ui.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/board/com.h"
#include "game/board/item.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/tutorial.h"

#include "ext_math.h"

typedef struct {
    /* 0x00 */ struct {
        u8 unk00_bit0 : 1;
        u8 unk00_bit1 : 1;
        u8 unk00_bit2 : 1;
        u8 unk00_bit3 : 1;
        u8 unk00_bit4 : 1;
        u8 unk00_bit5 : 1;
        u8 unk00_bit6 : 1;
    };
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ Vec unk04;
    /* 0x10 */ Vec unk10;
} UnkUiStatusStruct; // Size 0x1C

typedef struct {
    /* 0x00 */ s8 unk00[6];
    /* 0x06 */ s16 unk06[6];
    /* 0x12 */ s16 unk12[6];
    /* 0x1E */ s16 unk1E[6];
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ Vec unk2C[6];
    /* 0x74 */ Vec unk74[6];
} UnkUiWindowStruct; // Size 0xBC

typedef struct {
    struct {
        u8 unk00_bit0 : 1;
        u8 unk00_bit3 : 3;
        u8 unk00_bit5 : 2;
        u8 unk00_bit6 : 1;
        u8 unk00_bit7 : 1;
    };
    s8 unk01;
    s8 unk02;
    u8 unk03;
    s16 unk04;
    s16 unk06;
} UnkUiWork01;

typedef struct {
    struct {
        u8 unk00_bit0 : 1;
        u8 unk00_bit3 : 3;
        u8 unk00_bit5 : 2;
    };
    s8 unk01;
    char unk02[2];
    float unk04;
} UnkUiWork02;

typedef struct {
    struct {
        u8 unk00_bit0 : 1;
        u8 unk00_bit1 : 1;
    };
    s8 unk01;
    s8 unk02;
    s8 unk03;
    Vec *unk04;
} UnkUiWork03;

typedef struct {
    struct {
        u8 unk00_bit0 : 1;
    };
    s8 unk01;
    s8 unk02;
    s8 unk03;
    UnkUiWindowStruct *unk04;
} UnkUiWork04;

void BoardPlayerSparkSet(s32);
void BoardBowserSuitMotionCreate(void);
s16 BoardBowserSuitPlayerModelGet(void);

static void KillAllBoardStatus(void);
static void CreateBoardStatusSprite(s32 arg0, UnkUiStatusStruct *arg1);
static s32 UpdateBoardStatus(void);
static void BoardStatusProc(void);
static void MoveBoardStatus(s32 arg0);
static void UpdateStatusItem(UnkUiStatusStruct *arg0, s32 arg1, s32 arg2);
static void UpdatePicker(omObjData *arg0);
static void UpdatePickerInput(UnkUiWork01 *arg0, omObjData *arg1);
static void MovePicker(UnkUiWork01 *arg0, omObjData *arg1);
static void UpdateComPickerButton(UnkUiWork01 *arg0, omObjData *arg1, s32 *arg2);
static BOOL CheckPickerButton(UnkUiWork01 *arg0, omObjData *arg1, u32 arg2);
static void UpdateYourTurn(omObjData *arg0);
static void GrowYourTurn(UnkUiWork02 *arg0, omObjData *arg1);
static void WaitYourTurn(UnkUiWork02 *arg0, omObjData *arg1);
static void ShrinkYourTurn(UnkUiWork02 *arg0, omObjData *arg1);
static void ItemUseTeamProc(s32 arg0);
static void ItemUseProc(void);
static void FinishItemUse(s16 arg0, s32 arg1);
static void DestroyItemUse(void);
static void TeamItemPosSet(s32 arg0, s32 arg1, Vec *arg2);
static void ExecItemPick(void);
static void UpdateItemPick(omObjData *arg0);
static void MakeItemPickSpace(UnkUiWork03 *arg0);
static void SetItemUIStatus(s32 arg0);
static void ItemGetPos(s32 arg0, Vec *arg1);
static void UpdateItemPickGfx(omObjData *arg0);
static void UpdateItemPickup(omObjData *arg0);
static BOOL CheckItemWindow(void);
static void HideItemWindow(void);
static void CreateItemWindow(s32 arg0, s32 arg1);
static BOOL CheckItemWindowSlide(void);
static void KillItemWindow(void);
static void SetItemWindowCurr(s32 arg0);
static void UpdateItemWindow(omObjData *arg0);
static void CreatePickerWindow(UnkUiWork01 *arg0, s32 arg1);
static void KillPickerWindow(UnkUiWork01 *arg0);

static s16 itemMdlId[4][3];
static Vec pickerPos[4];
static Vec itemPosTemp[6];

static s8 itemTeam;
static s8 itemTeamF;
s8 boardItemUser;
static s8 pickerChoice;
static s8 pickerChoiceDefault;
static s32 pickerBackF;
s32 lbl_801D40D0;
static s16 yourTurnSpr;
static s8 itemPlayer;
static s8 itemUsed;
static s8 teamItemPlayer;
static s16 itemRandTbl[3];
static float itemPickupPos;
static omObjData *itemPickObj;
static Process *itemUseProc;
static omObjData *yourTurnObj;
static omObjData *pickerObj;
static omObjData *itemWindowObj;
static Process *statusProc;

static s16 itemPickupMdlId = -1;
static s16 yourTurnSprGrp = -1;

static UnkUiStatusStruct uiStatus[4] = { 0 };

static s32 statusSprTbl[11] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x27),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x26),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x29),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x28),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x28),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x28),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x2D),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x28),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x28),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x28),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x2C)
};

static s16 statusSprPrioTbl[12] = {
    0x05F0, 0x05E6, 0x05DC, 0x05D2,
    0x05DC, 0x05DC, 0x05DC, 0x05DC,
    0x05DC, 0x05DC, 0x05DC, 0x05DC
};

static float statusHideOfsTbl[4] = {
    -230.0f, 230.0f, -230.0f, 230.0f
};

static float statusPosTbl[4][2] = {
    { 114.0f, 84.0f },
    { 462.0f, 84.0f },
    { 114.0f, 396.0f },
    { 462.0f, 396.0f }
};

static u8 statusColTbl[4][4] = {
    { 0x80, 0x80, 0x80, 0x00 },
    { 0x1A, 0x84, 0xFF, 0x00 },
    { 0xFF, 0x1A, 0x2D, 0x00 },
    { 0x0A, 0xB4, 0x3C, 0x00 }
};

static float statusSprPosTbl[17][2] = {
    {   0.0f,   0.0f },
    {   0.0f,   0.0f },
    { -68.0f,   0.0f },
    {  80.0f,  14.0f },
    {  64.0f,  14.0f },
    {  48.0f,  14.0f },
    {  26.0f,  14.0f },
    {  80.0f, -12.0f },
    {  64.0f, -12.0f },
    {  48.0f, -12.0f },
    {  26.0f, -12.0f },
    { -16.0f,   0.0f },
    { -18.0f,  32.0f },
    {  24.0f, -34.0f },
    {  48.0f, -34.0f },
    {  72.0f, -34.0f },
    { -32.0f, -16.0f }
};

static float statusItemPosTbl[6][2] = {
    { -56.0f,   0.0f },
    { -58.0f,  32.0f },
    {  -2.0f,   4.0f },
    {  34.0f,  -8.0f },
    {  70.0f,   4.0f },
    { -56.0f, -16.0f }
};

static s32 itemMdlTbl[14] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x83),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x84),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x85),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x86),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x87),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x88),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x89),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x8A),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x8B),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x8C),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x8D),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x8E),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x8F),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x90)
};

static Vec teamItemStatusPosTbl[2] = {
    { 190.0f, 116.0f, 0.0f },
    { 386.0f, 116.0f, 0.0f }
};

s32 BoardItemModelGet(s32 arg0) {
    s32 sp8[14] = {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x6D),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x6E),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x6F),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x70),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x71),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x72),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x73),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x74),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x76),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x77),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x78),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x79),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x7A),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x7B)
    };

    return sp8[arg0];
}

s32 BoardItemNameGet(s32 arg0) {
    s32 sp8[15] = {
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x00),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x01),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x02),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x03),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x04),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x05),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x06),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x07),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x08),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x09),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x0A),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x0B),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x0C),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x0D),
        DATA_MAKE_NUM(DATADIR_EFFECT, 0x0E)
    };

    return sp8[arg0];
}

BOOL BoardStatusStopCheck(s32 arg0) {
    return (uiStatus[arg0].unk00_bit2) ? FALSE : TRUE;
}

s32 BoardStatusVisibleGet(s32 arg0) {
    return uiStatus[arg0].unk00_bit1;
}

void BoardStatusShowSetAll(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        BoardStatusShowSet(i, arg0);
    }
}

void BoardStatusItemSet(s32 arg0) {
    UnkUiStatusStruct *temp_r31;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        temp_r31 = &uiStatus[i];
        BoardStatusShowSet(i, arg0);
        temp_r31->unk04.x = temp_r31->unk10.x;
        temp_r31->unk04.y = temp_r31->unk10.y;
        temp_r31->unk00_bit2 = 0;
        HuSprGrpPosSet(temp_r31->unk02, temp_r31->unk04.x, temp_r31->unk04.y);
        for (j = 0; j < 3; j++) {
            if (itemMdlId[i][j] != -1) {
                BoardModelVisibilitySet(itemMdlId[i][j], arg0);
            }
        }
    }
}

void BoardStatusShowSetForce(s32 arg0) {
    uiStatus[arg0].unk00_bit3 = 1;
}

void BoardStatusGraySet(s32 arg0, s32 arg1) {
    UnkUiStatusStruct *temp_r31;
    s16 sp10[9] = { 3, 4, 5, 7, 8, 9, 2, 6, 10 };
    s16 var_r28;
    u8 var_r29;
    s32 i;

    temp_r31 = &uiStatus[arg0];
    if (arg1 != 0) {
        var_r29 = 0xFF;
        temp_r31->unk00_bit4 = 1;
        var_r28 = 1500;
    } else {
        var_r29 = 0x3F;
        temp_r31->unk00_bit4 = 0;
        var_r28 = 1530;
    }
    for (i = 0; i < 9; i++) {
        HuSprPriSet(temp_r31->unk02, sp10[i], var_r28);
        HuSprColorSet(temp_r31->unk02, sp10[i], var_r29, var_r29, var_r29);
    }
}

void BoardStatusShowSet(s32 arg0, s32 arg1) {
    UnkUiStatusStruct *temp_r31 = &uiStatus[arg0];

    if (temp_r31->unk00_bit3) {
        arg0 = 0;
    }
    if (arg1 == 0) {
        if (temp_r31->unk00_bit1) {
            temp_r31->unk00_bit1 = 0;
            temp_r31->unk10.x = statusPosTbl[arg0][0] + statusHideOfsTbl[arg0];
            temp_r31->unk10.y = statusPosTbl[arg0][1];
            temp_r31->unk00_bit3 = 0;
        }
    } else {
        if (!temp_r31->unk00_bit1) {
            temp_r31->unk00_bit1 = 1;
            temp_r31->unk10.x = statusPosTbl[arg0][0];
            temp_r31->unk10.y = statusPosTbl[arg0][1];
            temp_r31->unk04.x = statusPosTbl[arg0][0] + statusHideOfsTbl[arg0];
            temp_r31->unk04.y = statusPosTbl[arg0][1];
        }
    }
}

void BoardStatusItemHideSet(s32 arg0, s32 arg1) {
    UnkUiStatusStruct *temp_r31 = &uiStatus[arg0];

    if (arg1 != 0) {
        temp_r31->unk00_bit5 = 1;
    } else {
        temp_r31->unk00_bit5 = 0;
    }
}

void BoardStatusTargetPosSet(s32 arg0, Vec *arg1) {
    UnkUiStatusStruct *temp_r31 = &uiStatus[arg0];

    temp_r31->unk10.x = arg1->x;
    temp_r31->unk10.y = arg1->y;
    temp_r31->unk00_bit2 = 1;
}

void BoardStatusPosGet(s32 arg0, Vec *arg1) {
    UnkUiStatusStruct *temp_r31 = &uiStatus[arg0];

    arg1->x = temp_r31->unk04.x;
    arg1->y = temp_r31->unk04.y;
}

void BoardStatusPosSet(s32 arg0, Vec *arg1) {
    UnkUiStatusStruct *temp_r30 = &uiStatus[arg0];

    temp_r30->unk04.x = arg1->x;
    temp_r30->unk04.y = arg1->y;
    BoardStatusTargetPosSet(arg0, arg1);
}

void BoardStatusHammerCreate(s32 arg0) {
    UnkUiStatusStruct *temp_r31 = &uiStatus[arg0];
    float spC[2];
    s32 var_r30;
    s32 temp_r29;
    s16 sp8;

    temp_r29 = BoardPlayerAutoSizeGet(arg0);
    switch (temp_r29) {
        case 0:
            return;
        case 2:
            var_r30 = DATA_MAKE_NUM(DATADIR_BOARD, 0x93);
            break;
        case 1:
            var_r30 = DATA_MAKE_NUM(DATADIR_BOARD, 0x92);
            break;
    }
    if (!temp_r31->unk00_bit6) {
        BoardSpriteCreate(var_r30, 0x5DC, NULL, &sp8);
        spC[0] = statusSprPosTbl[16][0];
        spC[1] = statusSprPosTbl[16][1];
        HuSprGrpMemberSet(temp_r31->unk02, 0x10, sp8);
        HuSprPosSet(temp_r31->unk02, 0x10, spC[0], spC[1]);
        HuSprScaleSet(temp_r31->unk02, 0x10, 2.0f, 2.0f);
        HuSprAttrSet(temp_r31->unk02, 0x10, 2);
        HuSprAttrSet(temp_r31->unk02, 0x10, 8);
        HuSprDrawNoSet(temp_r31->unk02, 0x10, 0x40);
        temp_r31->unk00_bit6 = 1;
    }
}

void BoardStatusHammerShowSet(s32 arg0, s32 arg1) {
    UnkUiStatusStruct *temp_r31 = &uiStatus[arg0];

    if (temp_r31->unk00_bit6) {
        if (arg1 != 0) {
            HuSprAttrSet(temp_r31->unk02, 0x10, 2);
        } else {
            HuSprAttrReset(temp_r31->unk02, 0x10, 2);
            HuSprAttrSet(temp_r31->unk02, 0x10, 1);
        }
    }
}

void BoardStatusHammerKill(s32 arg0) {
    UnkUiStatusStruct *temp_r31 = &uiStatus[arg0];

    if (temp_r31->unk00_bit6) {
        HuSprGrpMemberKill(temp_r31->unk02, 0x10);
        temp_r31->unk00_bit6 = 0;
    }
}

void BoardStatusKill(void) {
    UnkUiStatusStruct *temp_r31;
    s32 i;

    for (i = 0; i < 4; i++) {
        temp_r31 = &uiStatus[i];
        if (temp_r31->unk00_bit0) {
            if (temp_r31->unk02 != -1) {
                HuSprGrpKill(temp_r31->unk02);
                temp_r31->unk02 = -1;
            }
            temp_r31->unk00_bit6 = 0;
        }
    }
}

void BoardStatusCreate(void) {
    s32 i;

    memset(uiStatus, 0, 0x70);
    for (i = 0; i < 4; i++) {
        CreateBoardStatusSprite(i, &uiStatus[i]);
        uiStatus[i].unk00_bit0 = 1;
        uiStatus[i].unk00_bit2 = 0;
        uiStatus[i].unk00_bit3 = 0;
        uiStatus[i].unk00_bit4 = 1;
        uiStatus[i].unk00_bit5 = 1;
        uiStatus[i].unk00_bit6 = 0;
        uiStatus[i].unk01 = 9;
        uiStatus[i].unk04.x = statusPosTbl[i][0] + statusHideOfsTbl[i];
        uiStatus[i].unk04.y = statusPosTbl[i][1];
        uiStatus[i].unk04.z = 0.0f;
        uiStatus[i].unk10 = uiStatus[i].unk04;
        HuSprGrpDrawNoSet(uiStatus[i].unk02, 0x40);
    }
    HuSprExecLayerSet(0x40, 5);
    if (statusProc == 0) {
        statusProc = HuPrcChildCreate(BoardStatusProc, 0x1FFF, 0x4000, 0, HuPrcCurrentGet());
        HuPrcDestructorSet2(statusProc, KillAllBoardStatus);
    }
}

static void KillAllBoardStatus(void) {
    BoardStatusKill();
    statusProc = NULL;
}

static void CreateBoardStatusSprite(s32 arg0, UnkUiStatusStruct *arg1) {
    float var_f31;
    float var_f30;
    s16 sp8;
    s32 temp_r28;
    s32 temp_r27;
    s16 temp_r26;
    s32 spC[] = {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2E),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x2F),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x30),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x31),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x32),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x33),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x34),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x35)
    };
    s32 i;

    temp_r28 = GWPlayerCfg[arg0].character;
    arg1->unk02 = HuSprGrpCreate(0x11);
    for (i = 0; i < 11; i++) {
        temp_r27 = statusSprTbl[i];
        temp_r26 = statusSprPrioTbl[i];
        BoardSpriteCreate(temp_r27, temp_r26, NULL, &sp8);
        HuSprGrpMemberSet(arg1->unk02, i, sp8);
        HuSprAttrSet(arg1->unk02, i, 1);
        HuSprAttrSet(arg1->unk02, i, 8);
        HuSprPosSet(arg1->unk02, i, statusSprPosTbl[i][0], statusSprPosTbl[i][1]);
    }
    if ((s32) GWSystem.team != 0) {
        if (GWPlayerTeamGet(arg0) == 0) {
            HuSprBankSet(arg1->unk02, 1, 2);
        } else {
            HuSprBankSet(arg1->unk02, 1, 1);
        }
    }
    BoardSpriteCreate(spC[temp_r28], 0x5DC, NULL, &sp8);
    HuSprGrpMemberSet(arg1->unk02, 0xB, sp8);
    HuSprAttrSet(arg1->unk02, 0xB, 8);
    var_f31 = statusSprPosTbl[11][0];
    var_f30 = statusSprPosTbl[11][1];
    HuSprPosSet(arg1->unk02, 11, var_f31, var_f30);
    BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x2A), 0x5DC, NULL, &sp8);
    HuSprGrpMemberSet(arg1->unk02, 0xC, sp8);
    var_f31 = statusSprPosTbl[12][0];
    var_f30 = statusSprPosTbl[12][1];
    HuSprPosSet(arg1->unk02, 12, var_f31, var_f30);
    HuSprAttrSet(arg1->unk02, 0xC, 8);
    for (i = 0; i < 3; i++) {
        BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x91), 0x5DC, NULL, &sp8);
        HuSprGrpMemberSet(arg1->unk02, i + 0xD, sp8);
        HuSprAttrSet(arg1->unk02, i + 0xD, 1);
        HuSprAttrSet(arg1->unk02, i + 0xD, 8);
    }
    arg1->unk00_bit6 = 0;
    HuSprTPLvlSet(arg1->unk02, 0, 0.7f);
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        HuSprAttrSet(arg1->unk02, 7, 4);
        HuSprAttrSet(arg1->unk02, 8, 4);
        HuSprAttrSet(arg1->unk02, 9, 4);
        HuSprAttrSet(arg1->unk02, 0xA, 4);
    }
}

void BoardSpriteCreate(s32 file, s32 prio, AnimData **anim, s16 *sprite) {
    s16 temp_r28;
    void *temp_r27;
    AnimData *temp_r31;

    temp_r27 = HuDataSelHeapReadNum(file, MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r31 = HuSprAnimRead(temp_r27);
    temp_r28 = HuSprCreate(temp_r31, prio, 0);
    if (anim) {
        *anim = temp_r31;
    }
    if (sprite) {
        *sprite = temp_r28;
    }
}

static s32 UpdateBoardStatus(void) {
    UnkUiStatusStruct *temp_r31;
    u8 *temp_r28;
    s32 temp_r27;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        temp_r31 = &uiStatus[i];
        if (temp_r31->unk02 == -1) {
            return -1;
        }
        GWPlayer[i].rank = BoardPlayerRankCalc(i);
        HuSprBankSet(temp_r31->unk02, 2, GWPlayer[i].rank);
        BoardSpriteDigitUpdate(temp_r31->unk02, 3, BoardPlayerCoinsGet(i));
        BoardSpriteDigitUpdate(temp_r31->unk02, 7, GWStarsGet(i));
        for (j = 0; j < 3; j++) {
            temp_r27 = GWPlayer[i].items[j];
            if (temp_r27 != -1 && temp_r31->unk00_bit5) {
                UpdateStatusItem(temp_r31, j, temp_r27);
                HuSprAttrReset(temp_r31->unk02, j + 0xD, 4);
            } else {
                HuSprAttrSet(temp_r31->unk02, j + 0xD, 4);
            }
        }
        if (GWPlayer[i].com) {
            HuSprAttrReset(temp_r31->unk02, 0xC, 4);
        } else {
            HuSprAttrSet(temp_r31->unk02, 0xC, 4);
        }
        temp_r28 = statusColTbl[GWPlayer[i].color];
        HuSprColorSet(temp_r31->unk02, 0, temp_r28[0], temp_r28[1], temp_r28[2]);
        MoveBoardStatus(i);
        HuSprGrpPosSet(temp_r31->unk02, temp_r31->unk04.x, temp_r31->unk04.y);
    }
    return 0;
}

static void BoardStatusProc(void) {
    while (1) {
        if (omSysExitReq != 0 || UpdateBoardStatus() != 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

static void MoveBoardStatus(s32 arg0) {
    UnkUiStatusStruct *temp_r30 = &uiStatus[arg0];
    float var_f30;
    Vec spC;

    VECSubtract(&temp_r30->unk10, &temp_r30->unk04, &spC);
    if (ABS(spC.x) < 1.0f && ABS(spC.y) < 1.0f) {
        spC = temp_r30->unk10;
        temp_r30->unk00_bit2 = 0;
    } else {
        OSs8tof32(&temp_r30->unk01, &var_f30);
        var_f30 /= 32;
        VECScale(&spC, &spC, var_f30);
        VECAdd(&temp_r30->unk04, &spC, &spC);
        temp_r30->unk00_bit2 = 1;
    }
    temp_r30->unk04.x = spC.x;
    temp_r30->unk04.y = spC.y;
}

void BoardSpriteDigitUpdate(s16 arg0, s16 arg1, s32 arg2) {
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;

    temp_r29 = arg2 / 100;
    temp_r28 = (arg2 - temp_r29 * 100) / 10;
    temp_r27 = (arg2 - (temp_r29 * 100 + temp_r28 * 10)) % 10;
    if (temp_r29 == 0) {
        HuSprBankSet(arg0, arg1 + 2, 0xA);
    } else {
        HuSprBankSet(arg0, arg1 + 2, temp_r29);
    }
    if (temp_r28 == 0 && temp_r29 == 0) {
        HuSprBankSet(arg0, arg1 + 1, temp_r27);
        HuSprAttrSet(arg0, arg1, 4);
    } else {
        HuSprBankSet(arg0, arg1 + 1, temp_r28);
        HuSprBankSet(arg0, arg1, temp_r27);
        HuSprAttrReset(arg0, arg1, 4);
    }
}

static void UpdateStatusItem(UnkUiStatusStruct *arg0, s32 arg1, s32 arg2) {
    float temp_f31;
    float temp_f30;

    temp_f31 = statusSprPosTbl[arg1 + 0xD][0];
    temp_f30 = statusSprPosTbl[arg1 + 0xD][1];
    HuSprBankSet(arg0->unk02, arg1 + 0xD, arg2);
    HuSprPosSet(arg0->unk02, arg1 + 0xD, temp_f31, temp_f30);
}

void BoardPickerCreate(s32 arg0, s8 arg1, void *arg2, s8 arg3) {
    UnkUiWork01 *temp_r31;
    omObjData *temp_r30;
    s32 temp_r28;
    s16 sp12;
    s32 sp14[] = {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x1E),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x1F),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x20),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x21),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x22),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x23),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x24),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x25)
    };

    temp_r28 = GWPlayer[arg0].character;
    temp_r30 = omAddObjEx(boardObjMan, 0x107, 0, 0, -1, &UpdatePicker);
    pickerObj = temp_r30;
    temp_r31 = OM_GET_WORK_PTR(temp_r30, UnkUiWork01);
    temp_r31->unk00_bit0 = 0;
    temp_r31->unk00_bit6 = 0;
    temp_r31->unk00_bit5 = arg0;
    temp_r31->unk01 = arg3;
    temp_r31->unk00_bit7 = 0;
    temp_r31->unk02 = 0;
    temp_r31->unk00_bit3 = 0;
    temp_r31->unk03 = 0xA;
    pickerBackF = 0;
    pickerChoiceDefault = arg1;
    memset(&pickerPos, 0, sizeof(pickerPos));
    memcpy(&pickerPos, arg2, pickerChoiceDefault * sizeof(Vec));
    temp_r31->unk04 = HuSprGrpCreate(1);
    pickerChoice = -1;
    temp_r30->trans.x = temp_r30->rot.x = pickerPos[temp_r31->unk02].x;
    temp_r30->trans.y = temp_r30->rot.y = pickerPos[temp_r31->unk02].y;
    temp_r30->trans.z = temp_r30->rot.z = 0.0f;
    BoardSpriteCreate(sp14[temp_r28], 90, NULL, &sp12);
    HuSprGrpMemberSet(temp_r31->unk04, 0, sp12);
    HuSprPosSet(temp_r31->unk04, 0, temp_r30->trans.x, temp_r30->trans.y);
    HuSprBankSet(temp_r31->unk04, 0, 0);
    HuSprAttrSet(temp_r31->unk04, 0, 1);
    HuSprAttrSet(temp_r31->unk04, 0, 2);
    HuSprAttrSet(temp_r31->unk04, 0, 8);
    CreatePickerWindow(temp_r31, 1);
}

void BoardPickerBackFlagSet(s32 arg0) {
    if (pickerObj) {
        if (arg0 != 0) {
            pickerBackF = 0;
        } else {
            pickerBackF = 1;
        }
        if (arg0 == 0) {
            KillPickerWindow(OM_GET_WORK_PTR(pickerObj, UnkUiWork01));
            CreatePickerWindow(OM_GET_WORK_PTR(pickerObj, UnkUiWork01), 0);
        }
    }
}

BOOL BoardPickerDoneCheck(void) {
    if (pickerObj) {
        return FALSE;
    } else {
        return TRUE;
    }
}

s32 BoardPickerPosGet(Vec *arg0) {
    if (pickerObj == 0 || arg0 == 0) {
        return -1;
    }
    arg0->x = pickerObj->trans.x;
    arg0->y = pickerObj->trans.y;
    arg0->z = pickerObj->trans.z;
    return 0;
}

s32 BoardPickerChoiceGet(void) {
    return pickerChoice;
}

static void UpdatePicker(omObjData *arg0) {
    UnkUiWork01 *temp_r31 = OM_GET_WORK_PTR(arg0, UnkUiWork01);

    if (temp_r31->unk00_bit0 || BoardIsKill()) {
        HuWinKill(temp_r31->unk06);
        HuSprGrpKill(temp_r31->unk04);
        pickerObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
    } else {
        if (temp_r31->unk03 != 0) {
            temp_r31->unk03--;
        } else if (pickerChoice != -1 || temp_r31->unk00_bit7) {
            temp_r31->unk00_bit0 = 1;
        } else {
            UpdatePickerInput(temp_r31, arg0);
        }
        MovePicker(temp_r31, arg0);
        HuSprPosSet(temp_r31->unk04, 0, arg0->trans.x, arg0->trans.y);
    }
}

static void UpdatePickerInput(UnkUiWork01 *arg0, omObjData *arg1) {
    s32 sp8;
    s32 temp_r29;

    if (!arg0->unk00_bit6) {
        sp8 = 0;
        if (GWPlayer[arg0->unk00_bit5].com && arg0->unk01 != -1) {
            UpdateComPickerButton(arg0, arg1, &sp8);
        } else {
            temp_r29 = GWPlayer[arg0->unk00_bit5].port;
            sp8 = HuPadDStkRep[temp_r29] | HuPadBtnDown[temp_r29];
        }
        if (CheckPickerButton(arg0, arg1, sp8) != 0) {
            arg1->rot.x = pickerPos[arg0->unk02].x;
            arg1->rot.y = pickerPos[arg0->unk02].y;
            arg1->rot.z = pickerPos[arg0->unk02].z;
        }
    }
}

static void MovePicker(UnkUiWork01 *arg0, omObjData *arg1) {
    float temp_f31 = 0.5f;
    Vec sp14;
    Vec sp8;

    sp8.x = arg1->rot.x;
    sp8.y = arg1->rot.y;
    sp8.z = arg1->rot.z;
    sp14.x = arg1->trans.x;
    sp14.y = arg1->trans.y;
    sp14.z = arg1->trans.z;
    VECSubtract(&sp8, &sp14, &sp8);
    if (VECMag(&sp8) < 1.0f) {
        arg1->trans.x = arg1->rot.x;
        arg1->trans.y = arg1->rot.y;
        arg1->trans.z = arg1->rot.z;
        arg0->unk00_bit6 = 0;
    } else {
        VECScale(&sp8, &sp8, temp_f31);
        VECAdd(&sp14, &sp8, &sp8);
        arg1->trans.x = sp8.x;
        arg1->trans.y = sp8.y;
        arg1->trans.z = sp8.z;
        arg0->unk00_bit6 = 1;
    }
}

static void UpdateComPickerButton(UnkUiWork01 *arg0, omObjData *arg1, s32 *arg2) {
    if (arg0->unk02 == arg0->unk01) {
        *arg2 = 0x100;
    } else {
        *arg2 = 2;
    }
}

static BOOL CheckPickerButton(UnkUiWork01 *arg0, omObjData *arg1, u32 arg2) {
    BOOL var_r30 = FALSE;

    if (arg2 == 0x100) {
        pickerChoice = arg0->unk02;
        HuAudFXPlay(2);
        var_r30 = TRUE;
    } else if (arg2 == 0x200 && pickerBackF == 0) {
        arg0->unk00_bit0 = 1;
        arg0->unk00_bit7 = 1;
        pickerChoice = -1;
        HuAudFXPlay(3);
        var_r30 = TRUE;
    } else if (arg2 & 1) {
        var_r30 = TRUE;
        if (pickerChoiceDefault > 1) {
            HuAudFXPlay(0);
        }
        arg0->unk02--;
    } else if (arg2 & 2) {
        var_r30 = TRUE;
        if (pickerChoiceDefault > 1) {
            HuAudFXPlay(0);
        }
        arg0->unk02++;
    }
    if (arg0->unk02 < 0) {
        arg0->unk02 = pickerChoiceDefault - 1;
    }
    if (arg0->unk02 >= pickerChoiceDefault) {
        arg0->unk02 = 0;
    }
    if (GWPlayer[arg0->unk00_bit5].com && var_r30 != 0) {
        arg0->unk03 = GWMessDelayGet();
    }
    return var_r30;
}

void BoardYourTurnExec(s32 arg0) {
    s32 temp_r29;
    UnkUiWork02 *temp_r31;
    s32 sp8[] = {
        DATA_MAKE_NUM(DATADIR_BOARD, 0x43),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x44),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x45),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x46),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x47),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x48),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x49),
        DATA_MAKE_NUM(DATADIR_BOARD, 0x4A)
    };

    temp_r29 = GWPlayer[arg0].character;
    yourTurnObj = omAddObjEx(boardObjMan, 0x10B, 0, 0, -1, &UpdateYourTurn);
    temp_r31 = OM_GET_WORK_PTR(yourTurnObj, UnkUiWork02);
    temp_r31->unk00_bit0 = 0;
    temp_r31->unk00_bit5 = arg0;
    temp_r31->unk00_bit3 = 0;
    temp_r31->unk01 = 0;
    yourTurnSprGrp = HuSprGrpCreate(3);
    BoardSpriteCreate(sp8[temp_r29], 0x5DC, NULL, &yourTurnSpr);
    HuSprGrpMemberSet(yourTurnSprGrp, 0, yourTurnSpr);
    HuSprPosSet(yourTurnSprGrp, 0, 0.0f, 0.0f);
    HuSprAttrSet(yourTurnSprGrp, 0, 1);
    HuSprScaleSet(yourTurnSprGrp, 0, 0.001f, 0.001f);
    HuSprAttrSet(yourTurnSprGrp, 0, 8);
    HuSprGrpPosSet(yourTurnSprGrp, 288.0f, 240.0f);
    HuAudFXPlay(0x307);
    while (yourTurnObj) {
        HuPrcVSleep();
    }
}

static void UpdateYourTurn(omObjData *arg0) {
    UnkUiWork02 *temp_r31 = OM_GET_WORK_PTR(arg0, UnkUiWork02);

    if (temp_r31->unk00_bit0 || BoardIsKill()) {
        HuSprGrpKill(yourTurnSprGrp);
        yourTurnSprGrp = -1;
        yourTurnObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
    } else {
        switch (temp_r31->unk00_bit3) {
            case 0:
                GrowYourTurn(temp_r31, arg0);
                break;
            case 2:
                WaitYourTurn(temp_r31, arg0);
                break;
            case 1:
                ShrinkYourTurn(temp_r31, arg0);
                break;
        }
    }
}

static void GrowYourTurn(UnkUiWork02 *arg0, omObjData *arg1) {
    float temp_f30;

    arg0->unk01 += 7;
    if (arg0->unk01 > 90) {
        arg0->unk01 = 90;
        arg0->unk00_bit3 = 1;
    }
    OSs8tof32(&arg0->unk01, &temp_f30);
    temp_f30 = 1.3f * sind(temp_f30);
    HuSprScaleSet(yourTurnSprGrp, 0, temp_f30, temp_f30);
}

static void WaitYourTurn(UnkUiWork02 *arg0, omObjData *arg1) {
    float temp_f30;

    arg0->unk01 += 7;
    if (arg0->unk01 > 90) {
        arg0->unk01 = 90;
        arg0->unk00_bit0 = 1;
    }
    OSs8tof32(&arg0->unk01, &temp_f30);
    temp_f30 = sind(temp_f30);
    HuSprScaleSet(yourTurnSprGrp, 0, 1.3f + temp_f30, 1.3f + temp_f30);
    HuSprTPLvlSet(yourTurnSprGrp, 0, 1.0f - temp_f30);
}

static void ShrinkYourTurn(UnkUiWork02 *arg0, omObjData *arg1) {
    s32 temp_r30 = GWPlayer[arg0->unk00_bit5].port;

    if ((HuPadBtnDown[temp_r30] & 0x100) || GWPlayer[arg0->unk00_bit5].com || _CheckFlag(FLAG_ID_MAKE(1, 11))) {
        arg0->unk00_bit3 = 2;
        arg0->unk01 = 0;
        arg0->unk04 = 1.0f;
    }
}

s32 BoardItemUseExec(s32 arg0) {
    BoardPauseDisableSet(1);
    itemPlayer = arg0;
    itemUseProc = HuPrcChildCreate(ItemUseProc, 0x2004, 0x4000, 0, boardMainProc);
    HuPrcDestructorSet2(itemUseProc, DestroyItemUse);
    while (itemUseProc) {
        HuPrcVSleep();
    }
    return itemUsed;
}

static void ItemUseTeamProc(s32 arg0) {
    UnkUiStatusStruct *temp_r22;
    Vec sp40;
    Vec sp34;
    s32 sp2C[2];
    s32 i;
    s32 j;

    if (GWTeamGet()) {
        if (arg0 != 0) {
            teamItemPlayer = BoardPlayerSameTeamFind(itemPlayer);
            if (itemTeamF != 0) {
                BoardStatusTargetPosSet(itemPlayer, &teamItemStatusPosTbl[0]);
                BoardStatusTargetPosSet(teamItemPlayer, &teamItemStatusPosTbl[1]);
            } else {
                BoardStatusTargetPosSet(itemPlayer, (Vec*) statusPosTbl[0]);
                BoardStatusTargetPosSet(teamItemPlayer, (Vec*) statusPosTbl[1]);
            }
            sp2C[0] = BoardPlayerTeamFind(itemPlayer);
            sp2C[1] = BoardPlayerSameTeamFind(sp2C[0]);
            for (i = 0; i < 2; i++) {
                sp40.x = statusPosTbl[sp2C[i]][0] + statusHideOfsTbl[sp2C[i]];
                sp40.y = statusPosTbl[sp2C[i]][1];
                BoardStatusTargetPosSet(sp2C[i], &sp40);
            }
            while (!BoardStatusStopCheck(itemPlayer) || !BoardStatusStopCheck(teamItemPlayer)) {
                HuPrcVSleep();
            }
        } else {
            for (i = 0; i < 4; i++) {
                sp40.x = statusPosTbl[i][0];
                sp40.y = statusPosTbl[i][1];
                BoardStatusTargetPosSet(i, &sp40);
            }
            while (!BoardStatusStopCheck(0)
                || !BoardStatusStopCheck(1)
                || !BoardStatusStopCheck(2)
                || !BoardStatusStopCheck(3)) {
                sp34.z = 0.0f;
                for (i = 0; i < 4; i++) {
                    temp_r22 = &uiStatus[i];
                    sp40.x = temp_r22->unk04.x;
                    sp40.y = temp_r22->unk04.y;
                    for (j = 0; j < BoardPlayerItemCount(i); j++) {
                        sp34.x = sp40.x + statusItemPosTbl[j + 2][0];
                        sp34.y = sp40.y + statusItemPosTbl[j + 2][1];
                        TeamItemPosSet(i, j, &sp34);
                    }
                }
                HuPrcVSleep();
            }
        }
    }
}

static void ItemUseProc(void) {
    s32 var_r24;
    s16 temp_r23;
    s32 var_r25;
    s32 var_r27;
    s32 i;

    var_r27 = -1;
    itemTeam = GWPlayerTeamGet(itemPlayer);
    if (GWTeamGet()) {
        itemTeamF = 1;
    } else {
        itemTeamF = 0;
    }
    for (i = 0; i < 4; i++) {
        GWPlayer[i].show_next = 0;
    }
    for (var_r25 = i = 0; i < 3; i++) {
        if (GWPlayer[itemPlayer].items[i] == 8) {
            var_r25++;
        }
    }
    temp_r23 = GWPlayer[itemPlayer].space_curr;
    ItemUseTeamProc(1);
    BoardFilterFadeInit(0x1E, 0xA0);
    ExecItemPick();
    ItemUseTeamProc(0);
    itemTeamF = 0;
    BoardFilterFadeOut(0x1E);
    if (itemUsed == 0xA) {
        var_r27 = DATADIR_BKOOPASUIT;
    }
    if (itemUsed == 0xB) {
        var_r27 = DATADIR_BYOKODORI;
    }
    if (var_r27 != -1) {
        var_r24 = BoardDataDirReadAsync(var_r27);
        BoardDataAsyncWait(var_r24);
    }
    HideItemWindow();
    BoardItemPrevSet(itemUsed);
    if (itemUsed != -1) {
        switch (itemUsed) {
            case 13:
                BoardMakeRandomItem();
                break;
            case 11:
                SetItemUIStatus(3);
                break;
            case 12:
                SetItemUIStatus(3);
                HuPrcSleep(0xA);
                BoardStatusShowSetAll(0);
                _SetFlag(0x1001C);
                _SetFlag(0x1000E);
                break;
        }
        BoardItemStart(itemPlayer, itemUsed);
        while (BoardItemDoneCheck() == 0) {
            HuPrcVSleep();
        }
        if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
            BoardTutorialHookExec(0x17, 0);
        }
        FinishItemUse(temp_r23, var_r25);
    }
    if (itemUsed != 0xB && itemUsed != 0xC) {
        SetItemUIStatus(3);
    }
    while (itemPickObj) {
        HuPrcVSleep();
    }
    while (!BoardFilterFadePauseCheck()) {
        HuPrcVSleep();
    }
    HuPrcEnd();
}

static void FinishItemUse(s16 arg0, s32 arg1) {
    s32 var_r30;
    s32 var_r31;
    s16 temp_r29;

    switch (itemUsed) {
        case 12:
            temp_r29 = BoardModelIDGet(BoardPlayerModelGet(itemPlayer));
            Hu3DModelShadowReset(temp_r29);
            _ClearFlag(0x1001C);
            _ClearFlag(0x1000E);
            Hu3DShadowF = 0;
            break;
        case 10:
            HuPrcSleep(2);
            BoardBowserSuitMotionCreate();
            BoardPlayerIdleSet(itemPlayer);
            BoardModelLayerSet(BoardBowserSuitModelGet(), 0);
            BoardModelLayerSet(BoardBowserSuitPlayerModelGet(), 0);
            break;
        case 7:
            BoardPlayerSparkSet(itemPlayer);
            break;
        case 8:
            for (var_r30 = var_r31 = 0; var_r31 < 3; var_r31++) {
                if (GWPlayer[itemPlayer].items[var_r31] == 8) {
                    var_r30++;
                }
            }
            if (var_r30 == arg1) {
                itemUsed = -1;
            }
            break;
    }
}

static void DestroyItemUse(void) {
    s32 i;

    CharModelLayerSetAll(1);
    for (i = 0; i < 4; i++) {
        GWPlayer[i].show_next = 1;
    }
    HuDataDirClose(DATADIR_BKOOPASUIT);
    HuDataDirClose(DATADIR_BYOKODORI);
    itemUseProc = NULL;
}

void BoardMakeRandomItem(void) {
    s32 chosenItemIndex;
    s32 i;

    for (i = 0; i < 3; i++) {
        chosenItemIndex = BoardRandMod(0xE);
        if (chosenItemIndex != 0xA && chosenItemIndex != 0xD) {
            itemRandTbl[i] = chosenItemIndex;
        }
    }
    BoardItemBagItemSet(itemRandTbl);
}

static inline void TeamItemPosSetInlineFunc01(s32 arg0, s32 arg1, Vec *arg2) {
    UnkUiWork03 *temp_r29 = OM_GET_WORK_PTR(itemPickObj, UnkUiWork03);
    Vec (*temp_r31)[6] = (void*) temp_r29->unk04;

    temp_r31[arg0][arg1 + 2].x = arg2->x;
    temp_r31[arg0][arg1 + 2].y = arg2->y;
    temp_r31[arg0][arg1 + 2].z = arg2->z;
}

static inline void TeamItemPosSetInlineFunc02(s32 arg0, s32 arg1, Vec *arg2) {
    UnkUiWork03 *temp_r29 = OM_GET_WORK_PTR(itemPickObj, UnkUiWork03);
    Vec (*temp_r31)[6] = (void*) temp_r29->unk04;

    (temp_r31 + 4)[arg0][arg1 + 2].x = arg2->x;
    (temp_r31 + 4)[arg0][arg1 + 2].y = arg2->y;
    (temp_r31 + 4)[arg0][arg1 + 2].z = arg2->z;
}

static void TeamItemPosSet(s32 arg0, s32 arg1, Vec *arg2) {
    TeamItemPosSetInlineFunc01(arg0, arg1, arg2);
    TeamItemPosSetInlineFunc02(arg0, arg1, arg2);
}

static inline void ExecItemPickInlineFunc01(Vec (*arg0)[6]) {
    Vec sp1C;
    Vec sp28;
    Vec sp34;
    s16 temp_r24;
    s32 sp14;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            sp14 = GWPlayer[i].items[j];
            if (sp14 == -1) {
                itemMdlId[i][j] = -1;
            } else {
                BoardCameraRotGet(&sp1C);
                temp_r24 = BoardModelCreate(itemMdlTbl[sp14], 0, 0);
                itemMdlId[i][j] = temp_r24;
                sp28.x = arg0[i][j + 2].x;
                sp28.y = arg0[i][j + 2].y;
                sp28.z = 4000.0f;
                Hu3D2Dto3D(&sp28, 1, &sp34);
                BoardModelPosSetV(temp_r24, &sp34);
                BoardModelLayerSet(temp_r24, 5);
                BoardModelRotSet(temp_r24, sp1C.x, 0.0f, 0.0f);
                BoardModelScaleSet(temp_r24, 1.0f, 1.0f, 1.0f);
                BoardModelMotionStart(temp_r24, 0, 0x400000);
                BoardModelMotionStartEndSet(temp_r24, 0, 0x27);
                BoardModelMotionSpeedSet(temp_r24, 0.0f);
            }
        }
    }
}

static inline void ExecItemPickInlineFunc02(s32 arg0, s8 arg1, s32 arg2) {
    UnkUiWork03 *sp10;

    BoardPickerCreate(arg0, arg1, itemPosTemp, arg2);
    CreateItemWindow(arg0, arg1);
    sp10 = OM_GET_WORK_PTR(pickerObj, UnkUiWork03);
    pickerObj->func = UpdateItemPickGfx;
    while (!CheckItemWindow()) {
        HuPrcVSleep();
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardTutorialHostHide(1);
    }
}

static void ExecItemPick(void) {
    Vec sp40;
    s32 sp18;
    s32 var_r22;
    s32 var_r23;
    s32 i;
    s32 j;
    UnkUiWork03 *temp_r27;
    Vec (*temp_r28)[6];

    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardTutorialHostHide(0);
    }
    itemPickObj = omAddObjEx(boardObjMan, 0x7E03, 0, 0, -1, &UpdateItemPick);
    temp_r27 = OM_GET_WORK_PTR(itemPickObj, UnkUiWork03);
    temp_r27->unk04 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x240, MEMORY_DEFAULT_NUM);
    temp_r27->unk00_bit0 = 0;
    temp_r27->unk01 = 0;
    temp_r27->unk02 = 0;
    temp_r27->unk03 = 0;
    temp_r27->unk00_bit1 = 0;
    BoardStatusItemHideSet(0, 0);
    BoardStatusItemHideSet(1, 0);
    BoardStatusItemHideSet(2, 0);
    BoardStatusItemHideSet(3, 0);
    temp_r28 = (void*) temp_r27->unk04;
    for (var_r22 = i = 0; i < 4; i++) {
        if (itemTeamF != 0) {
            if (itemTeam == GWPlayerTeamGet(i)) {
                if (itemPlayer == i) {
                    var_r22 = 0;
                } else {
                    var_r22 = 1;
                }
                sp40.x = teamItemStatusPosTbl[var_r22].x;
                sp40.y = teamItemStatusPosTbl[var_r22].y;
            } else {
                sp40.x = statusPosTbl[i][0] + statusHideOfsTbl[i];
                sp40.y = statusPosTbl[i][1];
            }
        } else {
            sp40.x = statusPosTbl[i][0];
            sp40.y = statusPosTbl[i][1];
        }
        for (j = 0; j < 6; j++) {
            temp_r28[i][j].x = statusSprPosTbl[j + 0xB][0];
            temp_r28[i][j].y = statusSprPosTbl[j + 0xB][1];
            (temp_r28 + 4)[i][j].x = statusItemPosTbl[j][0];
            (temp_r28 + 4)[i][j].y = statusItemPosTbl[j][1];
            if (j >= 2 && j <= 4) {
                temp_r28[i][j].x += sp40.x;
                temp_r28[i][j].y += sp40.y;
                (temp_r28 + 4)[i][j].x += sp40.x;
                (temp_r28 + 4)[i][j].y += sp40.y;
            }
            (temp_r28 + 4)[i][j].z = temp_r28[i][j].z = 0.0f;
        }
    }
    ExecItemPickInlineFunc01((void*) temp_r27->unk04);
    memset(itemPosTemp, 0, 0x48);
    var_r23 = BoardPlayerItemCount(itemPlayer);
    ItemGetPos(itemPlayer, &itemPosTemp[0]);
    if (GWTeamGet()) {
        ItemGetPos(teamItemPlayer, &itemPosTemp[var_r23]);
        var_r23 += BoardPlayerItemCount(teamItemPlayer);
    }
    for (j = 0; j < var_r23; j++) {
        itemPosTemp[j].x -= 8.0f;
        itemPosTemp[j].y += 16.0f;
    }
    sp18 = BoardComUseItemSlotGet(itemPlayer);
    ExecItemPickInlineFunc02(itemPlayer, var_r23, sp18);
}

static void UpdateItemPick(omObjData *arg0) {
    UnkUiWork03 *temp_r28 = OM_GET_WORK_PTR(arg0, UnkUiWork03);
    UnkUiStatusStruct *temp_r26;
    Vec (*temp_r27)[6];
    Vec sp14;
    Vec sp8;
    float temp_f30;
    s32 i;
    s32 j;

    if (temp_r28->unk00_bit0 || BoardIsKill()) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                if (itemMdlId[i][j] != -1) {
                    BoardModelKill(itemMdlId[i][j]);
                    itemMdlId[i][j] = -1;
                }
            }
        }
        BoardStatusItemHideSet(0, 1);
        BoardStatusItemHideSet(1, 1);
        BoardStatusItemHideSet(2, 1);
        BoardStatusItemHideSet(3, 1);
        HuMemDirectFree(temp_r28->unk04);
        itemPickObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
    } else {
        if (temp_r28->unk02 != 0) {
            temp_r28->unk02--;
        } else {
            switch (temp_r28->unk01) {
                case 3:
                    temp_r28->unk00_bit1 = 1;
                    /* fallthrough */
                case 0:
                    temp_r28->unk01 = 1;
                    break;
                case 1:
                    break;
                default:
                    return;
            }
        }
        MakeItemPickSpace(temp_r28);
        temp_r27 = (void*) temp_r28->unk04;
        for (i = 0; i < 4; i++) {
            temp_r26 = &uiStatus[i];
            for (j = 0; j < 6; j++) {
                if (j != 5 || temp_r26->unk00_bit6) {
                    HuSprPosSet(temp_r26->unk02, j + 0xB, temp_r27[i][j].x, temp_r27[i][j].y);
                }
            }
            for (j = 0; j < 3; j++) {
                if (itemMdlId[i][j] != -1) {
                    OSs8tof32(&temp_r28->unk03, &temp_f30);
                    temp_f30 = 1.0 + 0.5 * sind(temp_f30);
                    BoardModelScaleSet(itemMdlId[i][j], temp_f30, temp_f30, temp_f30);
                    sp14.x = temp_r27[i][j + 2].x;
                    sp14.y = temp_r27[i][j + 2].y;
                    sp14.z = 4000.0f;
                    Hu3D2Dto3D(&sp14, 1, &sp8);
                    BoardModelPosSetV(itemMdlId[i][j], &sp8);
                }
            }
        }
    }
}

static void MakeItemPickSpace(UnkUiWork03 *arg0) {
    Vec sp8;
    float var_f29;
    s32 i;
    s32 j;
    Vec (*temp_r28)[6];

    temp_r28 = (void*) arg0->unk04;
    if (!arg0->unk00_bit1) {
        if (arg0->unk03 < 90) {
            if (arg0->unk03 == 0) {
                for (j = 0; j < 4; j++) {
                    BoardStatusGraySet(j, 0);
                }
            }
            arg0->unk03 += 6;
            if (arg0->unk03 > 90) {
                arg0->unk03 = 90;
            }
        }
    } else {
        if (arg0->unk03 > 0) {
            arg0->unk03 -= 6;
            if (arg0->unk03 < 0) {
                arg0->unk03 = 0;
            }
            if (arg0->unk03 == 0) {
                for (j = 0; j < 4; j++) {
                    BoardStatusGraySet(j, 1);
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            VECSubtract(&(temp_r28 + 4)[i][j], &temp_r28[i][j], &sp8);
            if (ABS(sp8.x) < 1.0f && ABS(sp8.y) < 1.0f) {
                sp8 = (temp_r28 + 4)[i][j];
                if (arg0->unk00_bit1 && arg0->unk03 == 0) {
                    arg0->unk00_bit0 = 1;
                }
            } else {
                var_f29 = 0.3f;
                VECScale(&sp8, &sp8, var_f29);
                VECAdd(&temp_r28[i][j], &sp8, &sp8);
            }
            temp_r28[i][j].x = sp8.x;
            temp_r28[i][j].y = sp8.y;
        }
    }
}

static void SetItemUIStatus(s32 arg0) {
    UnkUiWork03 *temp_r27 = OM_GET_WORK_PTR(itemPickObj, UnkUiWork03);
    Vec (*temp_r28)[6] = (void*) temp_r27->unk04;
    float var_f31;
    float var_f30;
    s32 i;
    s32 j;

    switch (arg0) {
        case 3:
        case 0:
            for (i = 0; i < 4; i++) {
                var_f31 = statusPosTbl[i][0];
                var_f30 = statusPosTbl[i][1];
                for (j = 0; j < 6; j++) {
                    (temp_r28 + 4)[i][j].x = statusSprPosTbl[j + 0xB][0];
                    (temp_r28 + 4)[i][j].y = statusSprPosTbl[j + 0xB][1];
                    if (j + 0xB >= 0xD && j + 0xB <= 0xF) {
                        (temp_r28 + 4)[i][j].x += var_f31;
                        (temp_r28 + 4)[i][j].y += var_f30;
                    }
                }
            }
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                var_f31 = statusPosTbl[i][0];
                var_f30 = statusPosTbl[i][1];
                for (j = 0; j < 6; j++) {
                    (temp_r28 + 4)[i][j].x = statusItemPosTbl[j][0];
                    (temp_r28 + 4)[i][j].y = statusItemPosTbl[j][1];
                    if ((j >= 2) && (j <= 4)) {
                        (temp_r28 + 4)[i][j].x += var_f31;
                        (temp_r28 + 4)[i][j].y += var_f30;
                    }
                }
            }
            break;
        default:
            return;
    }
    temp_r27->unk01 = arg0;
}

void BoardItemGetDestPos(s32 arg0, Vec *arg1) {
    Vec spC;
    s32 i;

    spC.x = statusPosTbl[arg0][0];
    spC.y = statusPosTbl[arg0][1];
    spC.z = 0.0f;
    for (i = 0; i < 3; i++) {
        VECAdd((Vec*) &statusItemPosTbl[i + 2], &spC, &arg1[i]);
    }
}

static void ItemGetPos(s32 arg0, Vec *arg1) {
    Vec spC;
    s32 var_r29;
    s32 i;

    if (itemTeamF != 0) {
        if (itemPlayer == arg0) {
            var_r29 = 0;
        } else {
            var_r29 = 1;
        }
        spC.x = teamItemStatusPosTbl[var_r29].x;
        spC.y = teamItemStatusPosTbl[var_r29].y;
    } else {
        spC.x = statusPosTbl[arg0][0];
        spC.y = statusPosTbl[arg0][1];
    }
    spC.z = 0.0f;
    for (i = 0; i < 3; i++) {
        VECAdd((Vec*) statusItemPosTbl[i + 2], &spC, &arg1[i]);
    }
}

void BoardItemStatusKill(s32 arg0) {
    Vec sp68[3];
    Vec sp44[3];
    Vec sp20[3];
    Vec sp14;
    Vec sp8;
    s16 temp_r28;
    s16 temp_r25;
    s16 i;

    if (itemPickObj) {
        if (itemTeamF != 0) {
            if (arg0 == itemPlayer) {
                sp8.x = teamItemStatusPosTbl[0].x;
                sp8.y = teamItemStatusPosTbl[0].y;
            } else {
                sp8.x = teamItemStatusPosTbl[1].x;
                sp8.y = teamItemStatusPosTbl[1].y;
            }
        } else {
            sp8.x = statusPosTbl[arg0][0];
            sp8.y = statusPosTbl[arg0][1];
        }
        sp8.z = 0.0f;
        for (i = 0; i < 3; i++) {
            VECAdd((Vec*) statusItemPosTbl[i + 2], &sp8, &sp68[i]);
            if (itemMdlId[arg0][i] != -1) {
                BoardModelRotGet(itemMdlId[arg0][i], &sp44[i]);
                BoardModelScaleGet(itemMdlId[arg0][i], &sp20[i]);
                BoardModelKill(itemMdlId[arg0][i]);
                itemMdlId[arg0][i] = -1;
            }
        }
        for (i = 0; i < 3; i++) {
            temp_r25 = GWPlayer[arg0].items[i];
            if (temp_r25 != -1) {
                temp_r28 = BoardModelCreate(itemMdlTbl[temp_r25], 0, 0);
                itemMdlId[arg0][i] = temp_r28;
                BoardCameraRotGet(&sp14);
                BoardModelPosSetV(temp_r28, &sp68[i]);
                BoardModelRotSet(temp_r28, sp14.x, 0.0f, 0.0f);
                BoardModelScaleSetV(temp_r28, &sp20[i]);
                BoardModelLayerSet(temp_r28, 6);
                BoardModelMotionStart(temp_r28, 0, 0x400000);
                BoardModelMotionSpeedSet(temp_r28, 0.0f);
                TeamItemPosSet(arg0, i, &sp68[i]);
            }
        }
    }
}

static void UpdateItemPickGfx(omObjData *arg0) {
    UnkUiWork01 *temp_r30 = OM_GET_WORK_PTR(arg0, UnkUiWork01);

    if (temp_r30->unk00_bit0 || BoardIsKill()) {
        HuWinKill(temp_r30->unk06);
        HuSprGrpKill(temp_r30->unk04);
        pickerObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
    } else {
        if (temp_r30->unk03 != 0) {
            temp_r30->unk03--;
        } else {
            if (!CheckItemWindowSlide()) {
                temp_r30->unk00_bit6 = 1;
            }
            UpdatePickerInput(temp_r30, arg0);
        }
        MovePicker(temp_r30, arg0);
        SetItemWindowCurr(temp_r30->unk02);
        if (pickerChoice != -1 || temp_r30->unk00_bit7) {
            KillItemWindow();
            if (!temp_r30->unk00_bit7) {
                temp_r30->unk00_bit3 = 1;
                HuSprBankSet(temp_r30->unk04, 0, 1);
                HuSprAttrSet(temp_r30->unk04, 0, 2);
                HuSprAttrReset(temp_r30->unk04, 0, 1);
                arg0->func = UpdateItemPickup;
                HuWinDispOff(temp_r30->unk06);
            } else {
                itemUsed = -1;
            }
        }
        HuSprPosSet(temp_r30->unk04, 0, arg0->trans.x, arg0->trans.y);
    }
}

static void UpdateItemPickup(omObjData *arg0) {
    UnkUiWork01 *temp_r31 = OM_GET_WORK_PTR(arg0, UnkUiWork01);
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s16 var_r29;
    s16 var_r28;
    s16 var_r27;
    s16 var_r25;
    s16 var_r26;

    if (temp_r31->unk00_bit0 || BoardIsKill()) {
        HuWinKill(temp_r31->unk06);
        BoardModelKill(itemPickupMdlId);
        itemPickupMdlId = -1;
        HuSprGrpKill(temp_r31->unk04);
        pickerObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
    } else if (temp_r31->unk03 != 0) {
        temp_r31->unk03--;
    } else if (pickerChoice == -1) {
        temp_r31->unk00_bit0 = 1;
    } else {
        var_r29 = temp_r31->unk00_bit5;
        var_r28 = pickerChoice;
        if (GWTeamGet() && pickerChoice >= BoardPlayerItemCount(temp_r31->unk00_bit5)) {
            var_r29 = teamItemPlayer;
            var_r28 -= BoardPlayerItemCount(temp_r31->unk00_bit5);
        }
        switch (temp_r31->unk00_bit3) {
            case 1:
                BoardModelVisibilitySet(itemMdlId[var_r29][var_r28], 0);
                BoardModelPosGet(itemMdlId[var_r29][var_r28], &sp50);
                BoardModelRotGet(itemMdlId[var_r29][var_r28], &sp38);
                BoardModelScaleGet(itemMdlId[var_r29][var_r28], &sp44);
                itemUsed = GWPlayer[var_r29].items[var_r28];
                boardItemUser = var_r29;
                itemPickupMdlId = BoardModelCreate(itemMdlTbl[itemUsed], NULL, 0);
                BoardModelPosSetV(itemPickupMdlId, &sp50);
                BoardModelRotSetV(itemPickupMdlId, &sp38);
                BoardModelScaleSetV(itemPickupMdlId, &sp44);
                BoardModelLayerSet(itemPickupMdlId, 6);
                BoardModelMotionStart(itemPickupMdlId, 0, 0x400000);
                BoardModelMotionSpeedSet(itemPickupMdlId, 0.0f);
                temp_r31->unk00_bit3 = 2;
                break;
            case 2:
                var_r27 = 0x27;
                var_r25 = var_r27 + 0x27;
                BoardModelMotionStart(itemPickupMdlId, 0, 0);
                BoardModelMotionTimeSet(itemPickupMdlId, var_r27);
                BoardModelMotionStartEndSet(itemPickupMdlId, var_r27, var_r25);
                HuSprBankSet(temp_r31->unk04, 0, 1);
                HuSprAttrSet(temp_r31->unk04, 0, 2);
                HuSprSpeedSet(temp_r31->unk04, 0, 1.0f);
                itemPickupPos = 1.0f;
                temp_r31->unk00_bit3 = 3;
                HuAudFXPlay(0x30E);
                break;
            case 3:
                var_r26 = 0x27;
                if (BoardModelMotionTimeGet(itemPickupMdlId) < var_r26 + 0x17) {
                    arg0->trans.x -= itemPickupPos;
                    arg0->trans.y += itemPickupPos;
                    itemPickupPos *= 0.98f;
                } else {
                    sp50.x = arg0->trans.x;
                    sp50.y = arg0->trans.y;
                    sp50.z = 3200.0f;
                    Hu3D2Dto3D(&sp50, 1, &sp50);
                    BoardModelPosSetV(itemPickupMdlId, &sp50);
                    itemPickupPos = 4.0f;
                    temp_r31->unk00_bit3 = 4;
                    HuAudFXPlay(0x30F);
                }
                break;
            case 4:
                var_r26 = 0x4E;
                if (BoardModelMotionTimeGet(itemPickupMdlId) >= var_r26) {
                    temp_r31->unk03 = 0x12;
                    BoardPlayerItemRemove(var_r29, var_r28);
                    temp_r31->unk00_bit3 = 5;
                } else {
                    arg0->trans.x -= itemPickupPos;
                    arg0->trans.y += itemPickupPos;
                    itemPickupPos *= 0.9f;
                    sp50.x = arg0->trans.x;
                    sp50.y = arg0->trans.y;
                    sp50.z = 3200.0f;
                    Hu3D2Dto3D(&sp50, 1, &sp50);
                    BoardModelPosSetV(itemPickupMdlId, &sp50);
                }
                break;
            case 5:
                BoardPlayerPosGet(temp_r31->unk00_bit5, &sp2C);
                sp2C.y += 300.0f;
                sp8 = sp2C;
                Hu3D3Dto2D(&sp2C, 1, &sp2C);
                sp20.x = arg0->trans.x;
                sp20.y = arg0->trans.y;
                VECSubtract(&sp2C, &sp20, &sp14);
                if (ABS(sp14.x) < 1.0f && ABS(sp14.y) < 1.0f) {
                    HuSprAttrSet(temp_r31->unk04, 0, 4);
                    temp_r31->unk00_bit3 = 6;
                } else {
                    VECScale(&sp14, &sp14, 0.1f);
                    VECAdd(&sp20, &sp14, &sp50);
                    sp50.z = 3200.0f;
                    arg0->trans.x = sp50.x;
                    arg0->trans.y = sp50.y;
                    Hu3D2Dto3D(&sp50, 1, &sp50);
                    BoardModelPosSetV(itemPickupMdlId, &sp50);
                }
                break;
            case 6:
                break;
        }
        HuSprPosSet(temp_r31->unk04, 0, arg0->trans.x, arg0->trans.y);
    }
}

static BOOL CheckItemWindow(void) {
    UnkUiWork01 *temp_r31;

    if (pickerObj == 0) {
        return TRUE;
    }
    temp_r31 = OM_GET_WORK_PTR(pickerObj, UnkUiWork01);
    if (temp_r31->unk00_bit3 == 6) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static void HideItemWindow(void) {
    UnkUiWork01 *temp_r31;

    if (pickerObj) {
        temp_r31 = OM_GET_WORK_PTR(pickerObj, UnkUiWork01);
        temp_r31->unk00_bit0 = 1;
    }
}

static void CreateItemWindow(s32 arg0, s32 arg1) {
    Vec sp10;
    float sp8[2];
    float temp_f31;
    float var_f30;
    s32 var_r27;
    s32 temp_r28;
    s32 i;
    omObjData *temp_r26;
    UnkUiWork04 *temp_r29;
    UnkUiWindowStruct *temp_r31;

    temp_f31 = 0.25f;
    temp_r26 = omAddObjEx(boardObjMan, 0x107, 0, 0, -1, UpdateItemWindow);
    itemWindowObj = temp_r26;
    temp_r29 = OM_GET_WORK_PTR(temp_r26, UnkUiWork04);
    temp_r29->unk00_bit0 = 0;
    temp_r29->unk01 = 0;
    temp_r29->unk03 = 0;
    temp_r29->unk02 = arg1;
    temp_r29->unk04 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkUiWindowStruct), MEMORY_DEFAULT_NUM);
    temp_r26->trans.x = 0.0f;
    if (GWTeamGet()) {
        var_f30 = 32.0f;
    } else {
        var_f30 = 0.0f;
    }
    temp_r31 = temp_r29->unk04;
    for (i = 0; i < arg1; i++) {
        var_r27 = i;
        if (GWTeamGet() && i >= BoardPlayerItemCount(itemPlayer)) {
            arg0 = teamItemPlayer;
            var_r27 -= BoardPlayerItemCount(itemPlayer);
        }
        temp_r28 = GWPlayer[arg0].items[var_r27];
        if (temp_r28 == -1) {
            temp_r31->unk12[i] = temp_r31->unk1E[i]
                = temp_r31->unk06[i] = temp_r31->unk00[i] = -1;
        } else {
            temp_r31->unk00[i] = temp_r28;
            temp_r31->unk74[i].x = i * 576.0f + 36.0f;
            temp_r31->unk74[i].y = var_f30 + 240.0f;
            temp_r31->unk74[i].z = 0.0f;
            temp_r31->unk2C[i] = temp_r31->unk74[i];
            temp_r31->unk12[i] = HuWinCreate(temp_r31->unk2C[i].x, temp_r31->unk2C[i].y, 0x1F8, 0x60, 0);
            HuWinDrawNoSet(temp_r31->unk12[i], 0x40);
            HuWinCenterPosSet(temp_r31->unk12[i], 0.0f, 48.0f);
            HuWinMesSpeedSet(temp_r31->unk12[i], 0);
            HuWinMesSet(temp_r31->unk12[i], BoardItemNameGet(temp_r28));
            HuWinMesMaxSizeGet(1, sp8, temp_r28 + MAKE_MESSID(0x08, 0x0E));
            temp_r31->unk1E[i] = HuWinCreate(temp_r31->unk2C[i].x, temp_r31->unk2C[i].y - (-94.0f), sp8[0], sp8[1], 0);
            HuWinDrawNoSet(temp_r31->unk1E[i], 0x40);
            HuWinMesSpeedSet(temp_r31->unk1E[i], 0);
            HuWinMesSet(temp_r31->unk1E[i], temp_r28 + MAKE_MESSID(0x08, 0x0E));
            sp10.x = temp_r31->unk2C[i].x + 48.0f;
            sp10.y = temp_r31->unk2C[i].y;
            sp10.z = 400.0f;
            Hu3D2Dto3D(&sp10, 1, &sp10);
            temp_r31->unk06[i] = BoardModelCreate(BoardItemModelGet(temp_r28), NULL, 0);
            BoardModelLayerSet(temp_r31->unk06[i], 6);
            BoardModelPosSetV(temp_r31->unk06[i], &sp10);
            BoardModelScaleSet(temp_r31->unk06[i], temp_f31, temp_f31, temp_f31);
            if (temp_r28 == 4) {
                BoardModelMotionStart(temp_r31->unk06[i], 0, 0x40000001);
                BoardModelMotionSpeedSet(temp_r31->unk06[i], 0.033333335f);
            }
        }
    }
    for (; i < 6; i++) {
        temp_r31->unk06[i] = -1;
        temp_r31->unk12[i] = -1;
        temp_r31->unk1E[i] = -1;
    }
}

static BOOL CheckItemWindowSlide(void) {
    UnkUiWork04 *temp_r31;

    if (itemWindowObj == 0) {
        return TRUE;
    }
    temp_r31 = OM_GET_WORK_PTR(itemWindowObj, UnkUiWork04);
    return (temp_r31->unk03 != 0) ? FALSE : TRUE;
}

static void KillItemWindow(void) {
    UnkUiWork04 *temp_r31;

    if (itemWindowObj) {
        temp_r31 = OM_GET_WORK_PTR(itemWindowObj, UnkUiWork04);
        temp_r31->unk00_bit0 = 1;
    }
}

static void SetItemWindowCurr(s32 arg0) {
    UnkUiWork04 *temp_r31;
    UnkUiWindowStruct *temp_r30;

    if (itemWindowObj) {
        temp_r31 = OM_GET_WORK_PTR(itemWindowObj, UnkUiWork04);
        if (temp_r31->unk02 > 1 && arg0 != temp_r31->unk01) {
            temp_r30 = temp_r31->unk04;
            temp_r30->unk74[temp_r31->unk01].x = -576.0f;
            temp_r30->unk74[arg0].x = temp_r30->unk2C[temp_r31->unk01].x;
            temp_r30->unk2C[arg0].x = 576.0f;
            temp_r31->unk01 = arg0;
        }
    }
}

static void UpdateItemWindow(omObjData *arg0) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    UnkUiWork04 *temp_r29;
    UnkUiWindowStruct *temp_r31;
    s32 var_r27;
    s32 i;
    Mtx sp5C;
    Mtx sp2C;

    temp_r29 = OM_GET_WORK_PTR(arg0, UnkUiWork04);
    temp_r31 = temp_r29->unk04;
    if (temp_r29->unk00_bit0 || (BoardIsKill() != 0)) {
        for (i = 0; i < temp_r29->unk02; i++) {
            if (temp_r31->unk12[i] != -1) {
                HuWinKill(temp_r31->unk12[i]);
            }
            if (temp_r31->unk1E[i] != -1) {
                HuWinKill(temp_r31->unk1E[i]);
            }
            if (temp_r31->unk06[i] != -1) {
                BoardModelKill(temp_r31->unk06[i]);
            }
        }
        HuMemDirectFree(temp_r29->unk04);
        itemWindowObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
    } else {
        var_r27 = 0;
        for (i = 0; i < temp_r29->unk02; i++) {
            if ((temp_r31->unk06[i] != -1) && (temp_r31->unk12[i] != -1)) {
                VECSubtract(&temp_r31->unk74[i], &temp_r31->unk2C[i], &sp20);
                if (VECMag(&sp20) <= 1.0f) {
                    temp_r31->unk2C[i] = temp_r31->unk74[i];
                } else {
                    VECScale(&sp20, &sp20, 0.3f);
                    VECAdd(&sp20, &temp_r31->unk2C[i], &temp_r31->unk2C[i]);
                    var_r27 = 1;
                }
                HuWinPosSet(temp_r31->unk12[i], temp_r31->unk2C[i].x, temp_r31->unk2C[i].y);
                HuWinPosSet(temp_r31->unk1E[i], temp_r31->unk2C[i].x, temp_r31->unk2C[i].y + (-94.0f));
                sp14.x = temp_r31->unk2C[i].x + 48.0f;
                sp14.y = temp_r31->unk2C[i].y;
                sp14.z = 400.0f;
                if (temp_r31->unk00[i] == 5) {
                    sp14.y += 35.0f;
                }
                Hu3D2Dto3D(&sp14, 1, &sp14);
                BoardModelPosSetV(temp_r31->unk06[i], &sp14);
                BoardCameraRotGet(&sp8);
                PSMTXRotRad(sp2C, 'y', MTXDegToRad(arg0->trans.x));
                PSMTXRotRad(sp5C, 'x', MTXDegToRad(sp8.x + 10.0f));
                PSMTXConcat(sp5C, sp2C, sp2C);
                BoardModelMtxSet(temp_r31->unk06[i], &sp2C);
                BoardModelRotSet(temp_r31->unk06[i], 0.0f, 0.0f, 0.0f);
            }
        }
        temp_r29->unk03 = var_r27;
        arg0->trans.x = BoardDAngleCalc(arg0->trans.x + 2.0f);
    }
}

static void CreatePickerWindow(UnkUiWork01 *arg0, s32 arg1) {
    float spC[2];
    float var_f31;
    float var_f30;
    float var_f29;
    s32 var_r30;

    switch (GWGameStat.language) {
        case 1:
            var_f31 = 0.0f;
            break;
        case 0:
            var_f31 = 0.0f;
            break;
    }
    if (arg1 != 0) {
        var_r30 = MAKE_MESSID(0x10, 0x1A);
    } else {
        var_r30 = MAKE_MESSID(0x10, 0x1B);
    }
    HuWinMesMaxSizeGet(1, spC, var_r30);
    var_f30 = -10000.0f;
    var_f29 = var_f31 + 352.0f;
    arg0->unk06 = HuWinCreate(var_f30, var_f29, spC[0], spC[1], 0);
    HuWinBGTPLvlSet(arg0->unk06, 0.0f);
    HuWinMesSpeedSet(arg0->unk06, 0);
    HuWinMesSet(arg0->unk06, var_r30);
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        HuWinDispOff(arg0->unk06);
    }
}

static void KillPickerWindow(UnkUiWork01 *arg0) {
    if (arg0->unk06 != -1) {
        HuWinKill(arg0->unk06);
        arg0->unk06 = -1;
    }
}
