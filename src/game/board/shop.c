#include "game/board/shop.h"
#include "game/audio.h"
#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/board/com_path.h"
#include "game/board/item.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/tutorial.h"
#include "game/board/ui.h"
#include "game/board/view.h"
#include "game/board/window.h"
#include "game/disp.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"


#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 4;
    };
    u8 unk01;
    s8 unk02;
    s8 unk03;
    s8 unk04;
    char unk05[1];
    s16 unk06;
} ShopWinWork;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 3;
    };
    char unk01[1];
    s16 unk02;
    u16 unk04;
} ItemGiveWork;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 2;
    };
    u8 unk01;
    s8 unk02;
    s8 unk03;
    u8 unk04;
    u8 unk05;
    s16 unk06;
} ItemChoiceWork;

static void ExecShop(void);
static void DestroyShop(void);
static void PopupShop(void);
static void CloseShop(void);
static void CreateShopWin(void);
static void UpdateShopWin(omObjData *arg0);
static void SetShopWinItem(ShopWinWork *arg0, omObjData *arg1);
static void PauseShopWin(void);
static void StartItemGive(void);
static void ExecItemGive(omObjData *arg0);
static void MoveItemGive(omObjData *arg0, ItemGiveWork *arg1);
static void ShrinkItemGive(omObjData *arg0, ItemGiveWork *arg1);
static void WaitItemGive(omObjData *arg0, ItemGiveWork *arg1);
static void GetShopItems(s32 arg0);
static void GetDefaultShopItems(s32 arg0);
static void SortShopItems(void);
static void DecideComEnter(s32 arg0);
static void DecideComBuy(s32 arg0);
static s32 GetComItemChoice(s32 arg0);
static void WaitItemChoice(void);
static void CreateShopItemChoice(s32 arg0, s32 arg1);
static s32 GetShopItemChoice(void);
static s32 GetShopItemWinChoice(void);
static void MoveShopItemChoice(omObjData *arg0, ItemChoiceWork *arg1);
static void UpdateShopItemChoice(omObjData *arg0);
static void GetShopItemChoiceInput(ItemChoiceWork *arg0, omObjData *arg1, u32 *arg2);

static s32 activeItemTbl[5];
static s32 choiceEnableTbl[6];

static s16 shopMdlIdx[2][1];
static s16 *shopMdlPtr;
static s8 shopPlayer;
static s16 angleVal;
static s32 comF;
static omObjData *itemChoiceObj;
static omObjData *itemGiveObj;
static omObjData *shopWinObj;
static Process *shopProc;

static s16 itemMdl = -1;
static s8 itemChoice = -1;

static BoardModelParam shopMdlParam[1] = { { 0x00070094, { 0, 1, 0, 0, 0 }, -1 } };

static s16 hostMdl = -1;
static s16 shopMot[3] = { -1, -1, -1 };
static s8 itemCurChoice = -1;

static s8 defaultItemTbl[5] = { 0x05, 0x07, 0x02, 0x03, 0x00 };

static s32 hostMessTbl[] = { MAKE_MESSID(0x0F, 0x04), MAKE_MESSID(0x0F, 0x07), MAKE_MESSID(0x0F, 0x0A), MAKE_MESSID(0x0F, 0x0D),
    MAKE_MESSID(0x0F, 0x10), MAKE_MESSID(0x0F, 0x13), MAKE_MESSID(0x0F, 0x04), MAKE_MESSID(0x0F, 0x24), MAKE_MESSID(0x0F, 0x24) };

static s8 itemPriceTbl[] = { 5, 5, 15, 15, 10, 10, 15, 15, 15, 15, 0, 25, 30, 30, 0, 0 };

static s32 shopMotTbl[9][3] = { { DATA_MAKE_NUM(DATADIR_BGUEST, 0x01), DATA_MAKE_NUM(DATADIR_BGUEST, 0x03), DATA_MAKE_NUM(DATADIR_BGUEST, 0x04) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x09), DATA_MAKE_NUM(DATADIR_BGUEST, 0x0B), DATA_MAKE_NUM(DATADIR_BGUEST, 0x0C) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x0E), DATA_MAKE_NUM(DATADIR_BGUEST, 0x10), DATA_MAKE_NUM(DATADIR_BGUEST, 0x11) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x18), DATA_MAKE_NUM(DATADIR_BGUEST, 0x1A), DATA_MAKE_NUM(DATADIR_BGUEST, 0x1B) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x1D), DATA_MAKE_NUM(DATADIR_BGUEST, 0x1F), DATA_MAKE_NUM(DATADIR_BGUEST, 0x20) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x22), DATA_MAKE_NUM(DATADIR_BGUEST, 0x24), DATA_MAKE_NUM(DATADIR_BGUEST, 0x25) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x09), DATA_MAKE_NUM(DATADIR_BGUEST, 0x0B), DATA_MAKE_NUM(DATADIR_BGUEST, 0x0C) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x2A), DATA_MAKE_NUM(DATADIR_BGUEST, 0x2C), DATA_MAKE_NUM(DATADIR_BGUEST, 0x2D) },
    { DATA_MAKE_NUM(DATADIR_BGUEST, 0x2A), DATA_MAKE_NUM(DATADIR_BGUEST, 0x2C), DATA_MAKE_NUM(DATADIR_BGUEST, 0x2D) } };

void BoardShopHostSet(s16 arg0)
{
    hostMdl = arg0;
}

s16 BoardShopHostGet(void)
{
    return hostMdl;
}

void BoardShopInit(void)
{
    BoardModelParam *var_r29;
    Vec sp1C;
    Vec sp10;
    s32 j;
    s32 i;
    s32 sp8[2] = { 0x00080000, 0x00100000 };

    for (i = 0; i < 2; i++) {
        BoardSpaceLinkTransformGet(sp8[i], &sp1C, &sp10, 0);
        sp1C.y -= 5.0f;
        for (j = 0; j < 1; j++) {
            var_r29 = &shopMdlParam[j];
            shopMdlIdx[i][j] = BoardModelCreateParam(var_r29, &sp1C, &sp10);
        }
    }
    BoardModelVisibilitySet(hostMdl, 0);
}

void BoardShopKill(void)
{
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 1; j++) {
            if (shopMdlIdx[i][j] != -1) {
                BoardModelKill(shopMdlIdx[i][j]);
                shopMdlIdx[i][j] = -1;
            }
        }
    }
}

void BoardShopExec(s32 player, s32 space)
{
    if (BoardPlayerSizeGet(GWSystem.player_curr) == 2) {
        return;
    }
    shopPlayer = player;
    BoardRollDispSet(0);
    shopProc = HuPrcChildCreate(ExecShop, 0x2003, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(shopProc, DestroyShop);
    while (shopProc) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

static void ExecShop(void)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f30;
    float temp_f31;
    s16 temp_r25;
    s16 temp_r28;
    u32 var_r30;
    s32 var_r29;
    s32 temp_r27;
    s32 temp_r26;
    s32 temp_r24;
    s32 var_r23;
    s32 i;

    itemCurChoice = -1;
    temp_r27 = GWBoardGet();
    temp_r26 = BoardWinPortraitGet();
    comF = 0;
    temp_r28 = GWPlayer[shopPlayer].space_curr;
    if (BoardSpaceFlagGet(0, temp_r28) & 0x80000) {
        shopMdlPtr = shopMdlIdx[0];
    }
    else {
        shopMdlPtr = shopMdlIdx[1];
    }
    BoardPlayerIdleSet(shopPlayer);
    var_r30 = 0;
    if (BoardPlayerCoinsGet(shopPlayer) < 5) {
        var_r30 = MAKE_MESSID(15, 3);
    }
    if (BoardPlayerItemCount(shopPlayer) == 3) {
        var_r30 = MAKE_MESSID(15, 2);
    }
    if (GWSystem.turn == GWSystem.max_turn) {
        var_r30 = MAKE_MESSID(15, 1);
    }
    if (var_r30 != 0) {
        BoardWinCreate(0, var_r30, -1);
        BoardWinWait();
        BoardWinKill();
        HuPrcEnd();
    }
    BoardWinCreateChoice(0, MAKE_MESSID(15, 0), -1, 0);
    DecideComEnter(shopPlayer);
    BoardWinWait();
    if (BoardWinChoiceGet() != 0) {
        HuPrcEnd();
    }
    BoardWinKill();
    BoardAudSeqPause(0, 1, 1000);
    BoardStatusShowSetAll(0);
    temp_r25 = BoardSpaceLinkFlagSearch(0, temp_r28, 0x02000000);
    BoardSpacePosGet(0, temp_r28, &sp38);
    BoardSpacePosGet(0, temp_r25, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    VECNormalize(&sp20, &sp20);
    temp_f31 = atan2d(-sp20.x, -sp20.z);
    sp14.x = -10.0f;
    sp14.y = temp_f31;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 170.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(shopMdlPtr[0], &sp14, &sp8, 1360.0f, -1.0f, 27);
    HuAudFXPlay(0x330);
    HuAudFXPlay(0x32D);
    PopupShop();
    BoardModelMotionShiftSet(BoardShopHostGet(), shopMot[2], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(4);
    BoardPlayerRotSet(shopPlayer, 0.0f, temp_f31, 0.0f);
    BoardPlayerMoveBetween(shopPlayer, temp_r28, temp_r25);
    BoardPlayerIdleSet(shopPlayer);
    BoardMusStart(1, 3, 0x7F, 0);
    while (!BoardModelMotionEndCheck(BoardShopHostGet())) {
        HuPrcVSleep();
    }
    BoardModelMotionStart(BoardShopHostGet(), shopMot[0], 0x40000001);
    BoardStatusShowSetForce(shopPlayer);
    BoardStatusShowSet(shopPlayer, 1);
    GetShopItems(shopPlayer);
    SortShopItems();
    while (1) {
        BoardWinCreateChoice(1, hostMessTbl[temp_r27], temp_r26, 0);
        BoardWinAttrSet(0x10);
        DecideComBuy(shopPlayer);
        BoardWinWait();
        var_r29 = BoardWinChoiceGet();
        if (var_r29 == 1) {
            BoardWinCreate(2, hostMessTbl[temp_r27] + 1, temp_r26);
            BoardWinWait();
            BoardWinKill();
            break;
        }
        if (var_r29 != 0) {
            BoardViewMapExec(shopPlayer);
            continue;
        }
        CreateShopWin();
        BoardWinCreate(1, hostMessTbl[temp_r27] + 2, temp_r26);
        BoardWinPriSet(1000);
        for (i = 0; i < 5; i++) {
            var_r30 = MAKE_MESSID(15, activeItemTbl[i]);
            var_r30 += 0x16;
            BoardWinInsertMesSet(var_r30, i);
            var_r29 = itemPriceTbl[activeItemTbl[i]];
            if (var_r29 > BoardPlayerCoinsGet(shopPlayer)) {
                BoardWinChoiceDisable(i);
                choiceEnableTbl[i] = 0;
            }
            else {
                choiceEnableTbl[i] = 1;
            }
        }
        choiceEnableTbl[5] = 1;
        BoardWinSpeedSet(0);
        BoardWinPause();
        BoardWinAttrSet(0x10);
        HuPrcSleep(0xF);
        var_r29 = GetComItemChoice(shopPlayer);
        CreateShopItemChoice(shopPlayer, var_r29);
        WaitItemChoice();
        itemCurChoice = GetShopItemChoice();
        BoardWinKill();
        HuPrcSleep(0xF);
        if (itemCurChoice == -1 || itemCurChoice == 5 || itemCurChoice == 0x7F) {
            PauseShopWin();
        }
        else {
            PauseShopWin();
            while (!BoardStatusStopCheck(shopPlayer)) {
                HuPrcVSleep();
            }
            if (itemCurChoice == 5) {
                BoardWinCreate(2, hostMessTbl[temp_r27] + 1, temp_r26);
                BoardWinWait();
                BoardWinKill();
                break;
            }
            temp_r24 = itemPriceTbl[activeItemTbl[itemCurChoice]];
            if (temp_r24 >= 20) {
                var_r23 = 3;
            }
            else {
                var_r23 = 6;
            }
            var_f30 = BoardDAngleCalc(180.0f + BoardPlayerRotYGet(shopPlayer));
            BoardPlayerMotBlendSet(shopPlayer, var_f30, 0xF);
            for (i = 0; i < temp_r24; i++) {
                BoardPlayerCoinsAdd(shopPlayer, -1);
                HuAudFXPlay(0xE);
                HuPrcSleep(var_r23);
            }
            HuAudFXPlay(0xF);
            StartItemGive();
            while (!BoardPlayerMotBlendCheck(shopPlayer)) {
                HuPrcVSleep();
            }
            while (itemGiveObj) {
                HuPrcVSleep();
            }
            if (activeItemTbl[itemCurChoice] != 0xD) {
                BoardPlayerItemAdd(shopPlayer, activeItemTbl[itemCurChoice]);
            }
            BoardPlayerMotionShiftSet(shopPlayer, 0xC, 0.0f, 4.0f, HU3D_MOTATTR_NONE);
            HuPrcSleep(5);
            BoardPlayerMotionEndWait(shopPlayer);
            HuPrcSleep(15);
            break;
        }
    }
    BoardAudSeqFadeOut(1, 1000);
    BoardModelVisibilitySet(itemMdl, 0);
    BoardModelMotionShiftSet(BoardShopHostGet(), shopMot[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    BoardStatusShowSet(shopPlayer, 0);
    BoardCameraTargetPlayerSet(shopPlayer);
    BoardCameraMotionWait();
    BoardCameraViewSet(1);
    BoardPlayerRotSet(shopPlayer, 0.0f, temp_f31, 0.0f);
    BoardPlayerMoveBetween(shopPlayer, temp_r25, temp_r28);
    BoardPlayerIdleSet(shopPlayer);
    BoardStatusShowSetAll(1);
    BoardCameraMotionWait();
    BoardAudSeqPause(0, 0, 1000);
    CloseShop();
    HuPrcEnd();
}

static void DestroyShop(void)
{
    s16 temp_r30;
    s32 i;

    for (i = 0; i < 2; i++) {
        BoardModelHookReset(shopMdlIdx[0][i]);
    }
    temp_r30 = BoardShopHostGet();
    for (i = 0; i < 3; i++) {
        if (shopMot[i] != -1) {
            BoardModelMotionKill(temp_r30, shopMot[i]);
            shopMot[i] = -1;
        }
    }
    PauseShopWin();
    if (itemMdl != -1) {
        BoardModelKill(itemMdl);
        itemMdl = -1;
    }
    shopProc = NULL;
}

static void PopupShop(void)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        BoardModelHookSet(shopMdlIdx[i][0], "shop_noko", BoardShopHostGet());
    }
    for (i = 0; i < 3; i++) {
        shopMot[i] = BoardModelMotionCreate(BoardShopHostGet(), shopMotTbl[GWBoardGet()][i]);
    }
    BoardModelMotionStart(BoardShopHostGet(), shopMot[0], 0x40000001);
    BoardModelVisibilitySet(BoardShopHostGet(), 1);
    BoardModelMotionStart(BoardShopHostGet(), 1, 0x40000001);
    BoardModelMotionStart(shopMdlPtr[0], 0, 0);
    BoardModelMotionSpeedSet(shopMdlPtr[0], 1.0f);
    omVibrate(shopPlayer, 0xC, 6, 6);
    HuAudFXPlay(0x32D);
    HuAudFXPlay(0x344);
    while (BoardModelMotionTimeGet(shopMdlPtr[0]) < 14.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x32E);
    while (BoardModelMotionTimeGet(shopMdlPtr[0]) < 28.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x32F);
    while (!BoardModelMotionEndCheck(shopMdlPtr[0])) {
        HuPrcVSleep();
    }
}

static void CloseShop(void)
{
    BoardModelMotionStart(shopMdlPtr[0], 0, 0x40000004);
    while (BoardModelMotionTimeGet(shopMdlPtr[0]) > 28.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x32F);
    while (BoardModelMotionEndCheck(shopMdlPtr[0]) == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x32E);
    BoardModelAttrReset(shopMdlPtr[0], 0x40000004);
    BoardModelMotionSpeedSet(shopMdlPtr[0], 0.0f);
    BoardModelVisibilitySet(BoardShopHostGet(), 0);
}

static void CreateShopWin(void)
{
    Vec sp8;
    omObjData *var_r31;
    ShopWinWork *var_r30;

    var_r31 = omAddObjEx(boardObjMan, 0x109, 0, 0, -1, UpdateShopWin);
    var_r30 = OM_GET_WORK_PTR(var_r31, ShopWinWork);
    var_r30->unk00_field0 = 0;
    var_r30->unk06 = -1;
    var_r30->unk00_field1 = 0xFF;
    var_r30->unk02 = -1;
    var_r30->unk03 = -1;
    var_r30->unk01 = 0xC;
    var_r30->unk04 = 0;
    shopWinObj = var_r31;
    var_r30->unk06 = HuWinCreate(36.0f, HU_DISP_HEIGHT - 136, 0x1F8, 0x60, 0);
    HuWinMesSpeedSet(var_r30->unk06, 0);
    HuWinDrawNoSet(var_r30->unk06, 0x40);
    HuWinExAnimIn(var_r30->unk06);
    sp8.x = 84.0f;
    sp8.y = HU_DISP_HEIGHT - 88;
    sp8.z = 400.0f;
    var_r31->scale.x = var_r31->scale.y = var_r31->scale.z = 0.25f;
    Hu3D2Dto3D(&sp8, 1, &sp8);
    var_r31->trans.x = sp8.x;
    var_r31->trans.y = sp8.y;
    var_r31->trans.z = sp8.z;
    var_r31->scale.x = var_r31->scale.y = var_r31->scale.z = 1.0f;
}

static void UpdateShopWin(omObjData *arg0)
{
    Vec spC;
    float var_f29;
    float var_f28;
    ShopWinWork *temp_r28;
    Mtx sp48;
    Mtx sp18;

    temp_r28 = OM_GET_WORK_PTR(arg0, ShopWinWork);
    if (temp_r28->unk00_field0 != 0 || BoardIsKill()) {
        if (temp_r28->unk06 != -1) {
            HuWinKill(temp_r28->unk06);
        }
        shopWinObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r28->unk01 != 0) {
        temp_r28->unk01--;
        return;
    }
    temp_r28->unk02 = GetShopItemWinChoice();
    if (temp_r28->unk02 != -1) {
        if (temp_r28->unk04 == 90 && temp_r28->unk03 != temp_r28->unk02) {
            if (temp_r28->unk02 == 5) {
                HuWinDispOff(temp_r28->unk06);
                if (temp_r28->unk00_field0 == 0) {
                    BoardModelVisibilitySet(itemMdl, 0);
                }
            }
            else {
                HuWinDispOn(temp_r28->unk06);
                SetShopWinItem(temp_r28, arg0);
                BoardModelVisibilitySet(itemMdl, 1);
                temp_r28->unk04 = 0;
            }
            temp_r28->unk03 = temp_r28->unk02;
        }
        if (itemChoice == 0x7F) {
            BoardModelVisibilitySet(itemMdl, 0);
            HuWinDispOff(temp_r28->unk06);
        }
        var_f29 = 0.0f;
        if (temp_r28->unk04 < 90) {
            temp_r28->unk04 += 15;
            if (temp_r28->unk04 > 90) {
                temp_r28->unk04 = 90;
            }
            OSs8tof32(&temp_r28->unk04, &var_f28);
            arg0->scale.x = arg0->scale.y = arg0->scale.z = 0.25 * sind(var_f28);
        }
        if (temp_r28->unk00_field1 == 5) {
            var_f29 = -12.5f;
        }
        arg0->rot.y = BoardDAngleCalc(arg0->rot.y + 2.0f);
        BoardCameraRotGet(&spC);
        RotRad(sp48, 'y', MTXDegToRad(arg0->rot.y));
        RotRad(sp18, 'x', MTXDegToRad(spC.x + 10.0f));
        Concat(sp18, sp48, sp48);
        BoardModelMtxSet(itemMdl, &sp48);
        BoardModelRotSet(itemMdl, 0.0f, 0.0f, 0.0f);
        BoardModelPosSet(itemMdl, arg0->trans.x, arg0->trans.y + var_f29, arg0->trans.z);
        BoardModelScaleSet(itemMdl, arg0->scale.x, arg0->scale.y, arg0->scale.z);
        OSf32tos16(&arg0->rot.y, &angleVal);
    }
}

static void SetShopWinItem(ShopWinWork *arg0, omObjData *arg1)
{
    Vec spC;
    s32 var_r26;
    s8 temp_r28;

    temp_r28 = activeItemTbl[arg0->unk02];
    if (arg0->unk00_field1 != temp_r28) {
        if (itemMdl != -1) {
            BoardModelKill(itemMdl);
            itemMdl = -1;
        }
        var_r26 = BoardItemModelGet(temp_r28);
        itemMdl = BoardModelCreate(var_r26, NULL, 0);
        BoardModelLayerSet(itemMdl, 6);
        HuWinMesSet(arg0->unk06, BoardItemNameGet(temp_r28));
        arg0->unk04 = 0;
        arg0->unk00_field1 = temp_r28;
        if (temp_r28 == 4) {
            BoardModelMotionStart(itemMdl, 0, 0x40000001);
            BoardModelMotionSpeedSet(itemMdl, 0.033333335f);
        }
        BoardCameraDirGet(&spC);
        arg1->rot.y = BoardDAngleCalc(atan2d(-spC.x, -spC.z));
        OSf32tos16(&arg1->rot.y, &angleVal);
    }
}

static void PauseShopWin(void)
{
    if (shopWinObj) {
        OM_GET_WORK_PTR(shopWinObj, ShopWinWork)->unk00_field0 = 1;
        shopWinObj = NULL;
    }
}

void StartItemGive(void)
{
    Vec sp14;
    Vec sp8;
    omObjData *temp_r30;
    ItemGiveWork *temp_r29;
    Mtx sp20;

    temp_r30 = omAddObjEx(boardObjMan, 0x109, 0, 0, -1, ExecItemGive);
    itemGiveObj = temp_r30;
    temp_r29 = OM_GET_WORK_PTR(temp_r30, ItemGiveWork);
    temp_r29->unk00_field0 = 0;
    temp_r29->unk00_field1 = 0;
    temp_r29->unk04 = 0;
    temp_r29->unk02 = 0;
    BoardModelMotionStart(itemMdl, 0, 0);
    BoardModelMotionSpeedSet(itemMdl, 0.0f);
    BoardModelPosGet(itemMdl, &sp14);
    Identity(sp20);
    BoardModelMtxSet(itemMdl, &sp20);
    OSs16tof32(&angleVal, &temp_r30->scale.z);
    temp_r30->scale.z = -temp_r30->scale.z / 40.0f;
    temp_r30->scale.x = 0.25f;
    temp_r30->scale.y = 0.015f;
    BoardPlayerPosGet(shopPlayer, &sp8);
    temp_r30->trans.x = sp14.x;
    temp_r30->trans.y = sp14.y;
    temp_r30->trans.z = sp14.z;
    temp_r30->rot.y = sp8.y + 250.0f;
    temp_r30->rot.x = (sp8.x - sp14.x) / 50.0f;
    temp_r30->rot.z = (sp8.z - sp14.z) / 50.0f;
    itemGiveObj = temp_r30;
}

static void ExecItemGive(omObjData *arg0)
{
    ItemGiveWork *temp_r29;
    float var_f30;

    temp_r29 = OM_GET_WORK_PTR(arg0, ItemGiveWork);
    if (temp_r29->unk00_field0 != 0 || BoardIsKill()) {
        itemGiveObj = NULL;
        BoardModelVisibilitySet(itemMdl, 0);
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r29->unk04 != 0) {
        temp_r29->unk04--;
        return;
    }
    switch (temp_r29->unk00_field1) {
        case 0:
            MoveItemGive(arg0, temp_r29);
            break;
        case 1:
            ShrinkItemGive(arg0, temp_r29);
            break;
        case 2:
            WaitItemGive(arg0, temp_r29);
            break;
    }
    OSs16tof32(&angleVal, &var_f30);
    BoardModelPosSet(itemMdl, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelScaleSet(itemMdl, arg0->scale.x, arg0->scale.x, arg0->scale.x);
    BoardModelRotYSet(itemMdl, var_f30);
}

static void MoveItemGive(omObjData *arg0, ItemGiveWork *arg1)
{
    Vec sp1C;
    Vec sp10;
    float temp_f27;
    float var_f26;

    if (arg1->unk02 >= 50.0f) {
        arg1->unk02 = 0;
        if (activeItemTbl[itemCurChoice] == 0xD) {
            arg1->unk00_field1 = 2;
            BoardMakeRandomItem();
            BoardItemStart(GWSystem.player_curr, 0xD);
        }
        else {
            arg1->unk00_field1 = 1;
            arg1->unk04 = 0xF;
            BoardPlayerPosGet(shopPlayer, &sp1C);
            if (BoardPlayerSizeGet(shopPlayer) == 1) {
                arg0->rot.x = (sp1C.y + 30.0f - arg0->trans.y) / 22.5f;
            }
            else {
                arg0->rot.x = (sp1C.y + 70.0f - arg0->trans.y) / 22.5f;
            }
            arg0->trans.y = arg0->rot.y;
            arg0->scale.x = 1.0f;
        }
        return;
    }
    OSs16tof32(&arg1->unk02, &temp_f27);
    arg0->trans.y += 12.0f;
    if (arg1->unk02 >= 40.0f) {
        BoardPlayerPosGet(shopPlayer, &sp1C);
        arg0->scale.x = 1.0f;
        arg0->trans.x = sp1C.x;
        arg0->trans.z = sp1C.z;
        temp_f27 = 40.0f - (50.0f - temp_f27);
        temp_f27 = -0.08166667f * temp_f27 * temp_f27;
        arg0->trans.y += temp_f27;
        BoardCameraDirGet(&sp10);
        var_f26 = BoardDAngleCalc(atan2d(-sp10.x, -sp10.z));
        OSf32tos16(&var_f26, &angleVal);
    }
    else {
        arg0->scale.x += arg0->scale.y;
        arg0->trans.x += arg0->rot.x;
        arg0->trans.z += arg0->rot.z;
        OSs16tof32(&angleVal, &var_f26);
        var_f26 += arg0->scale.z;
        OSf32tos16(&var_f26, &angleVal);
    }
    if (arg0->trans.y < arg0->rot.y) {
        arg0->trans.y = arg0->rot.y;
    }
    arg1->unk02++;
}

static void ShrinkItemGive(omObjData *arg0, ItemGiveWork *arg1)
{
    float var_f30;

    if (arg1->unk02 == 0) {
        HuAudFXPlay(0x30D);
    }
    if (arg1->unk02 >= 90) {
        arg1->unk00_field0 = 1;
        BoardModelVisibilitySet(itemMdl, 0);
        return;
    }
    OSs16tof32(&arg1->unk02, &var_f30);
    if (BoardPlayerSizeGet(shopPlayer) != 1) {
        var_f30 *= 1.5f;
    }
    if (var_f30 > 90.0f) {
        var_f30 = 90.0f;
    }
    arg0->scale.x = cosd(var_f30);
    arg0->trans.y += arg0->rot.x;
    angleVal += 8;
    if (angleVal > 360) {
        angleVal -= 360;
    }
    arg1->unk02 += 4;
}

static void WaitItemGive(omObjData *arg0, ItemGiveWork *arg1)
{
    if (arg1->unk02 > 20) {
        BoardModelVisibilitySet(itemMdl, 0);
    }
    else {
        arg1->unk02++;
    }
    if (BoardItemDoneCheck()) {
        arg1->unk00_field0 = 1;
    }
}

static s8 itemPrioTbl[2][5][14] = { { { 0x14, 0x14, 0x0F, 0x0F, 0x05, 0x07, 0x05, 0x05, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00 },
                                        { 0x0F, 0x0F, 0x0D, 0x0A, 0x0A, 0x0A, 0x0A, 0x05, 0x00, 0x07, 0x00, 0x05, 0x00, 0x00 },
                                        { 0x07, 0x07, 0x0E, 0x0C, 0x0A, 0x0A, 0x0A, 0x08, 0x05, 0x09, 0x00, 0x08, 0x00, 0x00 },
                                        { 0x0A, 0x0A, 0x0D, 0x0C, 0x0A, 0x0A, 0x07, 0x0A, 0x05, 0x05, 0x00, 0x08, 0x00, 0x00 },
                                        { 0x07, 0x07, 0x0D, 0x0A, 0x0D, 0x07, 0x0A, 0x0A, 0x07, 0x08, 0x00, 0x08, 0x00, 0x00 } },
    { { 0x0F, 0x0F, 0x12, 0x0F, 0x05, 0x05, 0x05, 0x05, 0x00, 0x05, 0x00, 0x02, 0x05, 0x05 },
        { 0x0F, 0x0F, 0x0D, 0x0A, 0x07, 0x0A, 0x07, 0x03, 0x00, 0x07, 0x00, 0x00, 0x05, 0x08 },
        { 0x05, 0x04, 0x0D, 0x0C, 0x0A, 0x05, 0x0A, 0x08, 0x05, 0x05, 0x00, 0x05, 0x08, 0x0A },
        { 0x07, 0x04, 0x0D, 0x0C, 0x08, 0x08, 0x07, 0x0A, 0x05, 0x05, 0x00, 0x05, 0x08, 0x08 },
        { 0x03, 0x02, 0x0D, 0x0A, 0x0D, 0x03, 0x08, 0x08, 0x07, 0x07, 0x00, 0x08, 0x08, 0x0A } } };

static s8 rankItemGroupTbl[2][4][3] = { { { 0x00, 0x01, 0x03 }, { 0x00, 0x02, 0x04 }, { 0x00, 0x02, 0x04 }, { 0x00, 0x02, 0x04 } },
    { { 0x00, 0x01, 0x03 }, { 0x00, 0x02, 0x04 }, { 0x00, 0x02, 0x04 }, { 0x00, 0x02, 0x04 } } };

static float cursorPosTbl[6][2]
    = { { 190.0f, 182.0f }, { 190.0f, 208.0f }, { 190.0f, 234.0f }, { 190.0f, 260.0f }, { 190.0f, 286.0f }, { 190.0f, 312.0f } };

static void GetShopItems(s32 arg0)
{
    s32 temp_r25;
    s32 temp_r20;
    s32 temp_r19;
    s32 temp_r18;
    s32 var_r24;
    s32 var_r23;
    s32 temp_r22;
    s32 var_r27;
    s32 var_r26;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;

    temp_r22 = 3.0f * ((float)GWSystem.turn / GWSystem.max_turn);
    if (BoardPlayerCoinsGet(arg0) < 30) {
        var_r27 = 0;
    }
    else {
        var_r27 = 1;
    }
    temp_r19 = rankItemGroupTbl[var_r27][GWPlayer[arg0].rank][temp_r22];
    activeItemTbl[0] = activeItemTbl[1] = activeItemTbl[2] = activeItemTbl[3] = activeItemTbl[4] = -1;
    temp_r20 = BoardPlayerCoinsGet(shopPlayer);
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        GetDefaultShopItems(arg0);
        return;
    }
    var_r23 = 0;
    var_r29 = 0;
    while (var_r29 < 5) {
        temp_r18 = BoardRandMod(100);
        var_r26 = 0;
        for (var_r30 = 13; var_r30 >= 0; var_r30--) {
            temp_r25 = itemPrioTbl[var_r27][temp_r19][var_r30];
            if (temp_r25 != 0) {
                var_r26 += temp_r25;
                if (temp_r18 <= var_r26) {
                    var_r24 = 0;
                    for (var_r28 = 0; var_r28 < var_r29; var_r28++) {
                        if (var_r30 == activeItemTbl[var_r28]) {
                            var_r24 = 1;
                            break;
                        }
                    }
                    if (var_r24 == 0 && (temp_r20 >= itemPriceTbl[var_r30] || var_r23 != 0)) {
                        var_r23 = 1;
                        activeItemTbl[var_r29] = var_r30;
                        break;
                    }
                }
            }
        }
        if (activeItemTbl[var_r29] != -1) {
            var_r29++;
        }
    }
}

static void GetDefaultShopItems(s32 arg0)
{
    s32 temp_r29;
    s32 var_r31;
    s32 var_r30;

    temp_r29 = BoardRandMod(100);
    if (temp_r29 > 90) {
        var_r30 = 3;
    }
    else if (temp_r29 > 40) {
        var_r30 = BoardRandMod(2) + 1;
    }
    else {
        var_r30 = 0;
    }
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        activeItemTbl[var_r31] = defaultItemTbl[var_r30];
    }
}

static void SortShopItems(void)
{
    s32 sp8[5];
    s32 var_r29;
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        sp8[i] = itemPriceTbl[activeItemTbl[i]];
    }
    for (i = 0; i < 4; i++) {
        for (j = 4; j >= i + 1; j--) {
            if (sp8[j] < sp8[j - 1]) {
                var_r29 = activeItemTbl[j];
                activeItemTbl[j] = activeItemTbl[j - 1];
                activeItemTbl[j - 1] = var_r29;
                var_r29 = sp8[j];
                sp8[j] = sp8[j - 1];
                sp8[j - 1] = var_r29;
            }
        }
    }
}

static void DecideComEnter(s32 arg0)
{
    s32 temp_r27;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r26;
    u32 var_r28;

    if (!GWPlayer[arg0].com) {
        return;
    }
    temp_r26 = GWPlayer[arg0].roll;
    switch (GWPlayer[arg0].diff) {
        case 0:
            var_r28 = 40;
            break;
        case 1:
            var_r28 = 20;
            break;
        case 2:
            var_r28 = 4;
            break;
        case 3:
            var_r28 = 0;
            break;
    }
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        if (BoardPlayerCoinsGet(arg0) < 15) {
            BoardComKeySetRight();
            return;
        }
    }
    else {
        temp_r27 = GWPlayer[arg0].space_curr;
        temp_r30 = BoardComPathShortcutLenGet(temp_r27, 8, 0);
        temp_r29 = BoardComPathShortcutLenGet(temp_r27, 8, 1);
        if ((temp_r30 != 0 || temp_r29 != 0) && (BoardPlayerCoinsGet(arg0) >= 17 || (temp_r29 >= temp_r26 && temp_r30 >= temp_r26))
            && BoardPlayerCoinsGet(arg0) < 40 && ((temp_r30 < 20 && temp_r30 > 0) || (temp_r29 < 10 && temp_r29 > 0))
            && BoardRandMod(100) > var_r28) {
            BoardComKeySetRight();
            return;
        }
    }
    BoardComKeySetLeft();
}

static void DecideComBuy(s32 arg0)
{
    if (!GWPlayer[arg0].com) {
        return;
    }
    if (comF != 0) {
        BoardComKeySetDown();
    }
    else {
        BoardComKeySetUp();
    }
}

static s32 GetComItemChoice(s32 arg0)
{
    s16 sp8;
    s32 temp_r26;
    s32 var_r28 = 0;
    s8 var_r25;
    s8 var_r27;
    s8 var_r30;
    s32 i;

    if (!GWPlayer[arg0].com) {
        return 0;
    }
    sp8 = GWPlayer[arg0].space_curr;
    temp_r26 = BoardPlayerCoinsGet(arg0);
    for (var_r27 = i = 0; i < 5; i++) {
        if (temp_r26 >= itemPriceTbl[activeItemTbl[i]]) {
            var_r30 = BoardComItemWeightGet(arg0, activeItemTbl[i]);
        }
        else {
            var_r30 = 0;
        }
        if (BoardPlayerItemFind(arg0, activeItemTbl[i]) != -1) {
            var_r30 = 0;
        }
        if (var_r30 > var_r27) {
            var_r27 = var_r30;
            var_r25 = i;
        }
    }
    if (var_r27 == 0) {
        comF = 1;
        var_r28 = 5;
    }
    else {
        var_r28 = var_r25;
    }
    return var_r28;
}

static void WaitItemChoice(void)
{
    while (itemChoiceObj) {
        HuPrcVSleep();
    }
}

static void CreateShopItemChoice(s32 arg0, s32 arg1)
{
    omObjData *temp_r30;
    ItemChoiceWork *var_r31;
    s16 spC;
    s16 i;
#if VERSION_PAL
    for (i = 0; i < 6; i++) {
        cursorPosTbl[i][0] = 190;
    }
#endif
    temp_r30 = omAddObjEx(boardObjMan, 0x7E01, 0, 0, -1, UpdateShopItemChoice);
    itemChoiceObj = temp_r30;
    itemChoice = -1;
    var_r31 = OM_GET_WORK_PTR(temp_r30, ItemChoiceWork);
    var_r31->unk00_field0 = 0;
    var_r31->unk00_field1 = arg0;
    var_r31->unk01 = 0xA;
    var_r31->unk05 = 0;
    var_r31->unk02 = 0;
    var_r31->unk03 = arg1;
    var_r31->unk06 = HuSprGrpCreate(1);
#if VERSION_PAL
    if (GWLanguageGet() != 0) {
        s16 winId = BoardWinIDGet();
        if (winId != -1) {
            WindowData *winP = &winData[winId];
            for (i = 0; i < 6; i++) {
                cursorPosTbl[i][0] = winP->pos_x + 96;
            }
        }
        else {
            for (i = 0; i < 6; i++) {
                cursorPosTbl[i][0] = 166;
            }
        }
    }
    temp_r30->trans.x = cursorPosTbl[0][0];
    temp_r30->trans.y = cursorPosTbl[0][1];
#else
    temp_r30->trans.x = cursorPosTbl[0][0];
    temp_r30->trans.y = cursorPosTbl[0][1];
    if (GWLanguageGet() != 0) {
        temp_r30->trans.x -= 24.0f;
    }
#endif
    if (GWPlayer[arg0].com) {
        var_r31->unk01 = GWMessDelayGet();
    }
    BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x55), 0x3DE, NULL, &spC);
    HuSprGrpMemberSet(var_r31->unk06, 0, spC);
    HuSprAttrSet(var_r31->unk06, 0, 8);
    HuSprPosSet(var_r31->unk06, 0, temp_r30->trans.x, temp_r30->trans.y);
}

static s32 GetShopItemChoice(void)
{
    return itemChoice;
}

static s32 GetShopItemWinChoice(void)
{
    ItemChoiceWork *var_r31;

    if (!itemChoiceObj) {
        return -1;
    }
    var_r31 = OM_GET_WORK_PTR(itemChoiceObj, ItemChoiceWork);
    return var_r31->unk02;
}

static void MoveShopItemChoice(omObjData *arg0, ItemChoiceWork *arg1)
{
    u32 sp8;
    s32 temp_r28;
    s32 temp_r29;

    temp_r28 = arg1->unk02;
    arg0->trans.x = cursorPosTbl[arg1->unk02][0];
    arg0->trans.y = cursorPosTbl[arg1->unk02][1];
#if VERSION_NTSC
    if (GWLanguageGet() != 0) {
        arg0->trans.x -= 24.0f;
    }
#endif
    if (GWPlayer[arg1->unk00_field1].com) {
        GetShopItemChoiceInput(arg1, arg0, &sp8);
    }
    else {
        temp_r29 = GWPlayer[arg1->unk00_field1].port;
        sp8 = HuPadDStkRep[temp_r29] | HuPadBtnDown[temp_r29];
    }
    if (sp8 == 0x100) {
        if (choiceEnableTbl[arg1->unk02] == 0) {
            HuAudFXPlay(4);
            return;
        }
        if (arg1->unk02 != 5) {
            itemChoice = arg1->unk02;
        }
        HuAudFXPlay(2);
        if (GWPlayer[arg1->unk00_field1].com) {
            arg1->unk05 = 0x32;
        }
        else {
            arg1->unk05 = 5;
        }
        return;
    }
    if (sp8 == 0x200) {
        itemChoice = 0x7F;
        arg1->unk05 = 5;
        HuAudFXPlay(3);
    }
    if (sp8 == 4) {
        arg1->unk02++;
    }
    if (sp8 == 8) {
        arg1->unk02--;
    }
    if (arg1->unk02 < 0) {
        arg1->unk02 = 0;
    }
    if (arg1->unk02 >= 6) {
        arg1->unk02 = 5;
    }
    if (arg1->unk02 != temp_r28) {
        HuAudFXPlay(0);
        arg1->unk04 = 4;
    }
}

static void UpdateShopItemChoice(omObjData *arg0)
{
    ItemChoiceWork *temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, ItemChoiceWork);
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        HuSprGrpKill(temp_r31->unk06);
        itemChoiceObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r31->unk05 != 0) {
        temp_r31->unk05--;
        if (temp_r31->unk05 == 0) {
            temp_r31->unk00_field0 = 1;
        }
    }
    else if (temp_r31->unk01 != 0) {
        temp_r31->unk01--;
    }
    else if (temp_r31->unk04 != 0) {
        temp_r31->unk04--;
    }
    else {
        MoveShopItemChoice(arg0, temp_r31);
    }
    HuSprPosSet(temp_r31->unk06, 0, arg0->trans.x, arg0->trans.y);
}

static void GetShopItemChoiceInput(ItemChoiceWork *arg0, omObjData *arg1, u32 *arg2)
{
    if (arg0->unk02 == arg0->unk03) {
        *arg2 = 0x100;
    }
    else {
        *arg2 = 4;
    }
}

void BoardShopTutorialExec(s32 arg0)
{
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    s32 sp14;
    s32 sp10;
    s16 sp8;
    float temp_f31;
    s16 temp_r27;
    s32 i;

    sp14 = GWBoardGet();
    sp10 = BoardWinPortraitGet();
    if (BoardSpaceFlagGet(0, arg0) & 0x80000) {
        shopMdlPtr = shopMdlIdx[0];
    }
    else {
        shopMdlPtr = shopMdlIdx[1];
    }
    temp_r27 = BoardSpaceLinkFlagSearch(0, arg0, 0x02000000);
    BoardSpacePosGet(0, arg0, &sp48);
    BoardSpacePosGet(0, temp_r27, &sp3C);
    VECSubtract(&sp3C, &sp48, &sp30);
    VECNormalize(&sp30, &sp30);
    temp_f31 = atan2d(-sp30.x, -sp30.z);
    sp24.x = -10.0f;
    sp24.y = temp_f31;
    sp24.z = 0.0f;
    sp18.x = 0.0f;
    sp18.y = 170.0f;
    sp18.z = 0.0f;
    BoardCameraMotionStartEx(shopMdlPtr[0], &sp24, &sp18, 1360.0f, -1.0f, 21);
    HuAudFXPlay(0x330);
    HuAudFXPlay(0x32D);
    PopupShop();
    BoardModelMotionShiftSet(BoardShopHostGet(), shopMot[2], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(4);
    while (!BoardModelMotionEndCheck(BoardShopHostGet())) {
        HuPrcVSleep();
    }
    BoardModelMotionStart(BoardShopHostGet(), shopMot[0], 0x40000001);
    BoardTutorialHookExec(0x1C, 0);
    BoardModelMotionShiftSet(BoardShopHostGet(), shopMot[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    HuPrcSleep(30);
    CloseShop();
    for (i = 0; i < 2; i++) {
        BoardModelHookReset(shopMdlIdx[0][i]);
    }
    sp8 = BoardShopHostGet();
    for (i = 0; i < 3; i++) {
        if (shopMot[i] != -1) {
            BoardModelMotionKill(sp8, shopMot[i]);
            shopMot[i] = -1;
        }
    }
    PauseShopWin();
    if (itemMdl != -1) {
        BoardModelKill(itemMdl);
        itemMdl = -1;
    }
}
