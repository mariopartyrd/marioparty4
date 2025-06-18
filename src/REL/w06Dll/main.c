#include "REL/w06Dll.h"
#include "REL/board_executor.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/process.h"
#include "game/board/boo_house.h"
#include "game/board/lottery.h"
#include "game/board/main.h"
#include "game/board/map_object.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/shop.h"
#include "game/board/space.h"
#include "game/board/star.h"

#include "dolphin.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    s8 unk01[10];
} Bss8Work;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ Vec unk04;
} Data108Struct; // Size 0x10

static void fn_1_730(void);
static void fn_1_79C(void);
static s32 fn_1_7BC(void);
static s32 fn_1_900(void);
static s32 fn_1_984(void);
static void fn_1_9C0(void);
static void fn_1_B28(void);
static void fn_1_B5C(omObjData *arg0);

s16 lbl_1_bss_C[MAPOBJ_MAX];

static BoardMapObject lbl_1_data_0[MAPOBJ_MAX] = {
    { {   450.0f, 200.0f, -2950.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W06, 6) },
    { { -1650.0f,   0.0f,  2100.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W06, 8) },
    { {  2700.0f, 100.0f, -1950.0f }, { 0.0f, -89.999985f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W06, 5) },
    { { -3000.0f,   0.0f,  2550.0f }, { 0.0f,  89.999985f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W06, 5) },
    { { -1800.0f,   0.0f,  2250.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 33) },
    { {   300.0f, 200.0f, -2850.0f }, { 0.0f,        0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 33) }
};

static omObjData *lbl_1_bss_8;
static s32 lbl_1_bss_4;
UnkW06BoardData *lbl_1_bss_0;

static s16 lbl_1_data_F0 = -1;
static s16 lbl_1_data_F2 = -1;
static s16 lbl_1_data_F4 = -1;
static s16 lbl_1_data_F6 = -1;

static s32 lbl_1_data_F8[] = {
    DATA_MAKE_NUM(DATADIR_W06, 18),
    -1
};

static s32 lbl_1_data_100[] = {
    DATA_MAKE_NUM(DATADIR_BGUEST, 34),
    -1
};

static Data108Struct lbl_1_data_108[] = {
    0x00000002, { -3359.9998f, 170.0f, -3559.9998f },
    0x0000002A, {  3540.0002f, 170.0f,     1320.0f },
    0x00000052, {     -710.0f, 170.0f,    -4580.0f },
    0x0000007A, {    -3670.0f, 170.0f,     1020.0f },
    0x000000A2, {  1970.0001f, 170.0f, -3840.0002f },
    0x000000CA, {    -3160.0f, 170.0f,    -3770.0f },
    0x000000F2, {    -3500.0f, 170.0f,    -2340.0f },
    0x0000011A, {    -3700.0f, 170.0f, -810.00005f },
    0x00000142, {      100.0f, 170.0f,    -4100.0f },
    0x0000016A, {  3290.0002f, 170.0f,     -340.0f }
};

void BoardCreate(void) {
    BoardMapObject *temp_r30;
    s32 *var_r29;
    s32 i;

    lbl_1_bss_0 = (UnkW06BoardData*) GWSystem.board_data;
    BoardSpaceInit(DATA_MAKE_NUM(DATADIR_W06, 0));
    lbl_1_data_F0 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 1), NULL, 0);
    fn_8006DDE8(lbl_1_data_F0, -1.0f);
    BoardModelMotionStart(lbl_1_data_F0, 0, 0x40000001);
    lbl_1_data_F2 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 2), NULL, 0);
    fn_8006DDE8(lbl_1_data_F2, -1.0f);
    BoardModelPosSet(lbl_1_data_F2, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_F2, 0, 0x40000001);
    lbl_1_data_F4 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 17), lbl_1_data_F8, 0);
    BoardModelPosSet(lbl_1_data_F4, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_F4, 1, 0x40000001);
    lbl_1_data_F6 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 33), lbl_1_data_100, 0);
    BoardModelPosSet(lbl_1_data_F6, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_F6, 1, 0x40000001);
    for (i = 0; i < MAPOBJ_MAX; i++) {
        temp_r30 = &lbl_1_data_0[i];
        if (temp_r30->data_num != -1) {
            if (i == 4 || i == 5) {
                var_r29 = lbl_1_data_100;
            } else {
                var_r29 = NULL;
            }
            lbl_1_bss_C[i] = BoardModelCreate(temp_r30->data_num, var_r29, 0);
            BoardModelPosSetV(lbl_1_bss_C[i], &temp_r30->pos);
            BoardModelRotSetV(lbl_1_bss_C[i], &temp_r30->rot);
            BoardModelScaleSetV(lbl_1_bss_C[i], &temp_r30->scale);
            BoardModelVisibilitySet(lbl_1_bss_C[i], 1);
        }
    }
    BoardModelMotionStart(lbl_1_bss_C[4], 1, 0x40000001);
    BoardModelMotionStart(lbl_1_bss_C[5], 1, 0x40000001);
    BoardModelMotionStart(lbl_1_bss_C[2], 0, 0);
    BoardModelMotionSpeedSet(lbl_1_bss_C[2], 0.0f);
    BoardModelLayerSet(lbl_1_bss_C[2], 1);
    BoardModelMotionStart(lbl_1_bss_C[3], 0, 0);
    BoardModelMotionSpeedSet(lbl_1_bss_C[3], 0.0f);
    BoardModelLayerSet(lbl_1_bss_C[3], 1);
    fn_1_D70();
    fn_1_4878();
    fn_1_7BB0();
    fn_1_8F20();
    BoardLightHookSet(fn_1_730, fn_1_79C);
    BoardSpaceWalkEventFuncSet(fn_1_7BC);
    BoardSpaceWalkMiniEventFuncSet(fn_1_900);
    BoardSpaceLandEventFuncSet(fn_1_984);
    BoardStarHostSet(lbl_1_data_F4);
    BoardBooHouseHostSet(lbl_1_data_F6);
    BoardLotteryHostSet(lbl_1_data_F6);
    BoardShopHostSet(lbl_1_data_F6);
    BoardJunctionMaskSet(0x3000);
    boardTurnFunc = fn_1_C2B4;
    boardStarShowNextHook = fn_1_CD0C;
    boardTurnStartFunc = fn_1_9294;
    boardStarGiveHook = fn_1_CC90;
    boardBowserHook = fn_1_C108;
    fn_1_9C0();
}

void BoardDestroy(void) {
    s32 i;

    fn_1_B28();
#ifdef __MWERKS__
    boardTurnFunc
        = (void*) boardStarShowNextHook
        = (void*) boardTurnStartFunc
        = (void*) boardStarGiveHook
        = (void*) boardBowserHook = NULL;
#else
    boardTurnFunc = NULL;
    boardStarShowNextHook = NULL;
    boardTurnStartFunc = NULL;
    boardStarGiveHook = NULL;
    boardBowserHook = NULL;
#endif
    fn_1_91D8();
    fn_1_7F3C();
    fn_1_F6C();
    fn_1_4A10();
    for (i = 0; i < MAPOBJ_MAX; i++) {
        BoardModelKill(lbl_1_bss_C[i]);
        lbl_1_bss_C[i] = -1;
    }
    if (lbl_1_data_F6 != -1) {
        BoardModelKill(lbl_1_data_F6);
        lbl_1_data_F6 = -1;
    }
    if (lbl_1_data_F4 != -1) {
        BoardModelKill(lbl_1_data_F4);
        lbl_1_data_F4 = -1;
    }
    if (lbl_1_data_F0 != -1) {
        BoardModelKill(lbl_1_data_F0);
        lbl_1_data_F0 = -1;
    }
    if (lbl_1_data_F2 != -1) {
        BoardModelKill(lbl_1_data_F2);
        lbl_1_data_F2 = -1;
    }
}

static void fn_1_730(void) {
    s16 var_r31;

    var_r31 = BoardModelIDGet(lbl_1_data_F0);
    Hu3DModelLightInfoSet(var_r31, 1);
    Hu3DFogSet(4200.0f, 30000.0f, 0xF8, 0x30, 0);
}

static void fn_1_79C(void) {
    Hu3DFogClear();
}

static s32 fn_1_7BC(void) {
    s32 sp10[] = { 0, 1 };
    s32 sp8[] = { 0x300, 0xC0 };
    BoardSpace *temp_r31;
    s16 temp_r28;
    s32 temp_r27;
    s32 i;
    s32 j;

    temp_r27 = GWSystem.player_curr;
    temp_r28 = GWPlayer[temp_r27].space_curr;
    if (fn_1_92D8(temp_r27, temp_r28) != 0) {
        return 1;
    }
    for (i = 0; i < 2; i++) {
        if (BoardSpaceLinkFlagSearch(0, temp_r28, sp8[i]) == -1) {
            continue;
        }
        temp_r31 = BoardSpaceGet(0, temp_r28);
        for (j = 0; j < temp_r31->link_cnt; j++) {
            if ((BoardSpaceFlagGet(0, temp_r31->link[j]) & 0x04000000) == 0) {
                fn_1_8264(sp10[i], temp_r31->link[j]);
                return 1;
            }
        }
    }
    return 0;
}

static s32 fn_1_900(void) {
    s16 var_r30;
    s32 temp_r31;

    var_r30 = GWPlayer[GWSystem.player_curr].space_curr;
    temp_r31 = BoardSpaceFlagGet(0, var_r30) & 0x600000;
    if (temp_r31 == 0x200000) {
        fn_1_1054();
    } else if (temp_r31 == 0x400000) {
        fn_1_4A60();
    }
}

static s32 fn_1_984(void) {
    if (BoardPlayerSizeGet(GWSystem.player_curr) != 2) {
        fn_1_6EF0();
    }
}

static void fn_1_9C0(void) {
    Vec sp14;
    Vec sp8;
    omObjData *temp_r3;
    Bss8Work *temp_r30;
    s32 i;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_B5C);
    lbl_1_bss_8 = temp_r3;
    temp_r30 = OM_GET_WORK_PTR(temp_r3, Bss8Work);
    temp_r30->unk00_field0 = 0;
    BoardCameraPosGet(&sp14);
    BoardCameraDirGet(&sp8);
    HuAudFXListnerSetEX(&sp14, &sp8, 6600.0f, 36000.0f, 0.0f, 1650.0f, 1650.0f);
    for (i = 0; i < 10; i++) {
        temp_r30->unk01[i] = 0;
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 16))) {
        if (lbl_1_bss_4 == 0) {
            HuAudFXPauseAll(1);
            lbl_1_bss_4 = 1;
        }
    } else if (lbl_1_bss_4 != 0) {
        HuAudFXPauseAll(0);
        lbl_1_bss_4 = 0;
    }
}

static void fn_1_B28(void) {
    if (lbl_1_bss_8) {
        OM_GET_WORK_PTR(lbl_1_bss_8, Bss8Work)->unk00_field0 = 1;
    }
}

static void fn_1_B5C(omObjData *arg0) {
    Bss8Work *temp_r30;
    Vec sp14;
    Vec sp8;
    s16 temp_r28;
    s16 var_r29;
    s16 i;

    temp_r30 = OM_GET_WORK_PTR(arg0, Bss8Work);
    if (temp_r30->unk00_field0 != 0 || BoardIsKill()) {
        HuAudFXListnerKill();
        lbl_1_bss_8 = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    temp_r28 = BoardModelMotionTimeGet(lbl_1_data_F0);
    BoardCameraDirGet(&sp8);
    BoardCameraTargetGet(&sp14);
    sp14.y += 2000.0f;
    if (!_CheckFlag(FLAG_ID_MAKE(1, 16))) {
        if (lbl_1_bss_4 == 0) {
            HuAudFXPauseAll(1);
            lbl_1_bss_4 = 1;
        }
    } else if (lbl_1_bss_4 != 0) {
        HuAudFXPauseAll(0);
        lbl_1_bss_4 = 0;
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 28))) {
        for (var_r29 = i = 0; i < 10; i++) {
            if (temp_r30->unk01[i] != 0) {
                var_r29++;
            } else if (temp_r28 == lbl_1_data_108[i].unk00) {
                HuAudFXEmiterPlay(0x4A1, &lbl_1_data_108[i].unk04);
                temp_r30->unk01[i] = 1;
                goto block_20;
            }
        }
        if (var_r29 < 10) {
            return;
        }
        for (i = 0; i < 10; i++) {
            temp_r30->unk01[i] = 0;
        }
    }
block_20:
    HuAudFXListnerUpdate(&sp14, &sp8);
}
