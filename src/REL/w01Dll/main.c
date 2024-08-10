#include "REL/w01Dll.h"
#include "REL/board_executor.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/board/audio.h"
#include "game/board/boo_house.h"
#include "game/board/com.h"
#include "game/board/lottery.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/shop.h"
#include "game/board/space.h"
#include "game/board/star.h"
#include "game/board/ui.h"
#include "game/board/view.h"
#include "game/board/window.h"
#include "game/board/map_object.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
} Bss10Work;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 3;
        u8 unk00_field2 : 1;
        u8 unk00_field3 : 1;
    };
    u8 unk01;
    u8 unk02;
    char unk03[1];
    s16 unk04;
    char unk06[2];
    float unk08;
} Bss18Work;

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ float unk08;
    /* 0x0C */ char unk0C[4];
    /* 0x10 */ float unk10;
    /* 0x14 */ Vec unk14;
    /* 0x20 */ Mtx unk20;
} BssCData; // Size 0x50

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    s8 unk01;
    char unk02[2];
    BssCData *unk04;
} BssCWork;

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ float unk04;
    /* 0x08 */ Vec unk08;
    /* 0x14 */ Vec unk14;
} Bss20Data; // Size 0x20

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    u8 unk01;
    char unk02[2];
    Bss20Data *unk04;
} Bss20Work;

static void fn_1_730(void);
static void fn_1_774(void);
static s32 fn_1_778(void);
static s32 fn_1_814(void);
static void fn_1_9E8(void);
static void fn_1_D00(void);
static void fn_1_D04(void);
static void fn_1_1254(void);
static void fn_1_128C(void);
static void fn_1_130C(void);
static s32 fn_1_157C(void);
static void fn_1_1670(void);
static void fn_1_1700(void);
static void fn_1_1990(void);
static void fn_1_1AD8(BoardCameraData *camera);
static void fn_1_1B3C(void);
static void fn_1_1EE4(void);
static void fn_1_1F2C(omObjData *arg0);
static void fn_1_1FA4(void);
static float fn_1_2524(void);
static void fn_1_276C(void);
static void fn_1_2F18(void);
static void fn_1_3350(void);
static void fn_1_3514(s32 arg0);
static void fn_1_35B4(s32 arg0);
static void fn_1_3624(void);
static void fn_1_45F4(void);
static void fn_1_4774(void);
static void fn_1_4864(void);
static s32 fn_1_48B4(void);
static void fn_1_4E14(void);
static void fn_1_4FA8(void);
static void fn_1_4FD8(void);
static void fn_1_50D4(void);
static void fn_1_53B8(void);
static void fn_1_543C(void);
static void fn_1_5694(s32 arg0);
static void fn_1_586C(s32 arg0, s32 arg1);
static void fn_1_592C(void);
static void fn_1_5B2C(void);
static void fn_1_5B40(void);
static BOOL fn_1_5CD0(void);
static void fn_1_5D08(void);
static void fn_1_6098(omObjData *arg0);
static void fn_1_6194(Bss18Work *arg0, omObjData *arg1);
static void fn_1_63F0(Bss18Work *arg0, omObjData *arg1);
static void fn_1_6A14(Bss18Work *arg0, omObjData *arg1);
static void fn_1_6BC0(Bss18Work *arg0, omObjData *arg1);
static void fn_1_6FB4(Bss18Work *arg0, omObjData *arg1);
static void fn_1_7528(s32 arg0, s32 arg1);
static void fn_1_77EC(s32 arg0, s32 arg1);
static void fn_1_7894(void);
static void fn_1_7A64(void);
static void fn_1_852C(void);
static void fn_1_87AC(void);
static void fn_1_87E0(omObjData *arg0);
static void fn_1_8988(BssCData *arg0, omObjData *arg1);
static void fn_1_8A50(BssCData *arg0, omObjData *arg1);
static void fn_1_8B6C(BssCData *arg0, omObjData *arg1);
static void fn_1_8DDC(BssCData *arg0, omObjData *arg1);
static void fn_1_918C(BssCData *arg0, omObjData *arg1);
static void fn_1_927C(BssCData *arg0, omObjData *arg1);
static void fn_1_932C(BssCData *arg0);
static s32 fn_1_94A8(BssCData *arg0);
static void fn_1_95F4(BssCData *arg0);
static void fn_1_97F4(void);
static void fn_1_98EC(void);
static void fn_1_9920(omObjData *arg0);
static void fn_1_9A24(Bss20Work *arg0);
static void fn_1_9BBC(Bss20Work *arg0);


static BoardMapObject lbl_1_data_0[MAPOBJ_MAX] = {
    { {      0.0f,   0.0f,      0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 8)    },
    { {      0.0f, 700.0f,    300.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 9)    },
    { {  -2025.0f, 100.0f,   1950.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 0) },
    { {   1725.0f, 200.0f,  -1650.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 0) },
    { { 2757.974f, 200.0f, -536.781f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 0) },
    { {  -2750.0f, 300.0f,  -2150.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_BGUEST, 0) },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 12)   },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 13)   },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 14)   },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 15)   },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 16)   },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 16)   },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 16)   },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 17)   },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 18)   },
    { {  -2550.0f, 300.0f,  -2250.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 18)   },
    { {   3000.0f, 200.0f,   -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 21)   },
    { {   3000.0f, 200.0f,   -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 22)   },
    { {   3000.0f, 200.0f,   -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 23)   },
    { {   3000.0f, 200.0f,   -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 24)   },
    { {   3000.0f, 200.0f,   -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 25)   },
    { {   3000.0f, 200.0f,   -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 26)   },
    { {   3000.0f, 200.0f,   -450.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 27)   },
    { {   1200.0f,   0.0f,   1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 3)    },
    { {   1200.0f,   0.0f,   1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4)    },
    { {   1200.0f,   0.0f,   1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4)    },
    { {   1200.0f,   0.0f,   1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4)    },
    { {   1200.0f,   0.0f,   1200.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 5)    },
    { {  -1800.0f, 200.0f,   -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 3)    },
    { {  -1800.0f, 200.0f,   -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4)    },
    { {  -1800.0f, 200.0f,   -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4)    },
    { {  -1800.0f, 200.0f,   -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 4)    },
    { {  -1800.0f, 200.0f,   -900.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DATA_MAKE_NUM(DATADIR_W01, 5)    }
};

s16 lbl_1_bss_6C4[MAPOBJ_MAX];

static s32 *lbl_1_bss_6C0;
static s16 lbl_1_bss_6B6[5];
static s8 lbl_1_bss_6B4;
static s8 lbl_1_bss_6B3;
static s8 lbl_1_bss_6B2;
static s8 lbl_1_bss_6B1;
static s8 lbl_1_bss_6B0;
static s16 lbl_1_bss_6AE;
static s16 lbl_1_bss_6AC;
static float lbl_1_bss_6A8;
static Mtx lbl_1_bss_678;
static float lbl_1_bss_674;
static float lbl_1_bss_670;
static float lbl_1_bss_66C;
static Vec lbl_1_bss_660;
static Vec lbl_1_bss_654;
static Vec lbl_1_bss_648;
static float lbl_1_bss_644;
static float lbl_1_bss_640;
static float lbl_1_bss_63C;
static Vec lbl_1_bss_630;
static Vec lbl_1_bss_624;
static Vec lbl_1_bss_618;
static s8 lbl_1_bss_600[24];
static s16 lbl_1_bss_5D0[24];
static s16 lbl_1_bss_5CC[2];
static s8 lbl_1_bss_2C[1440];
static s8 lbl_1_bss_2A[2]; // padding
static s8 lbl_1_bss_29;
static s8 lbl_1_bss_28;
static s16 lbl_1_bss_26;
static s16 lbl_1_bss_24;
static omObjData *lbl_1_bss_20;
static s8 lbl_1_bss_1C;
static omObjData *lbl_1_bss_18;
static Process *lbl_1_bss_14;
static omObjData *lbl_1_bss_10;
static omObjData *lbl_1_bss_C;
static Process *lbl_1_bss_8;
static Process *lbl_1_bss_4;
UnkBoardDataStruct *lbl_1_bss_0;

static s16 lbl_1_data_528 = -1;
static s16 lbl_1_data_52A = -1;
static s16 lbl_1_data_52C = -1;
static s16 lbl_1_data_52E = -1;
static s16 lbl_1_data_530 = -1;

static s32 lbl_1_data_534[] = {
    DATA_MAKE_NUM(DATADIR_W01, 30),
    -1
};

static s32 lbl_1_data_53C[] = {
    DATA_MAKE_NUM(DATADIR_BGUEST, 1),
    -1
};

void BoardCreate(void) {
    BoardMapObject *temp_r30;
    s32 sp8;
    s32 i;

    sp8 = GWBoardGet();
    lbl_1_bss_0 = (UnkBoardDataStruct*) GWSystem.board_data;
    BoardSpaceInit(DATA_MAKE_NUM(DATADIR_W01, 0));
    lbl_1_data_528 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 1), NULL, 0);
    fn_8006DDE8(lbl_1_data_528, -1.0f);
    BoardModelPosSet(lbl_1_data_528, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_528, 0, 0x40000001);
    lbl_1_data_52A = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 2), NULL, 0);
    fn_8006DDE8(lbl_1_data_52A, -1.0f);
    BoardModelPosSet(lbl_1_data_52A, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_52A, 0, 0x40000001);
    lbl_1_data_52C = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 29), lbl_1_data_534, 0);
    BoardModelPosSet(lbl_1_data_52C, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_52C, 1, 0x40000001);
    lbl_1_data_52E = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 0), lbl_1_data_53C, 0);
    BoardModelPosSet(lbl_1_data_52E, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_52E, 1, 0x40000001);
    lbl_1_data_530 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 11), NULL, 0);
    BoardModelMotionStart(lbl_1_data_530, 0, 0x40000001);
    BoardLightHookSet(fn_1_730, fn_1_774);
    for (i = 0; i < MAPOBJ_MAX; i++) {
        temp_r30 = &lbl_1_data_0[i];
        if (temp_r30->data_num != -1) {
            if (i == 2 || i == 3 || i == 4 || i == 5) {
                lbl_1_bss_6C0 = lbl_1_data_53C;
            } else {
                lbl_1_bss_6C0 = NULL;
            }
            lbl_1_bss_6C4[i] = BoardModelCreate(temp_r30->data_num, lbl_1_bss_6C0, 0);
            BoardModelPosSetV(lbl_1_bss_6C4[i], &temp_r30->pos);
            BoardModelRotSetV(lbl_1_bss_6C4[i], &temp_r30->rot);
            BoardModelScaleSetV(lbl_1_bss_6C4[i], &temp_r30->scale);
            BoardModelVisibilitySet(lbl_1_bss_6C4[i], 1);
        }
    }
    BoardModelMotionStart(lbl_1_bss_6C4[2], 1, 0x40000001);
    BoardModelMotionStart(lbl_1_bss_6C4[3], 1, 0x40000001);
    BoardModelMotionStart(lbl_1_bss_6C4[4], 1, 0x40000001);
    BoardModelMotionStart(lbl_1_bss_6C4[5], 1, 0x40000001);
    fn_1_543C();
    fn_1_9E8();
    fn_1_1700();
    BoardSpaceWalkEventFuncSet(fn_1_814);
    BoardSpaceWalkMiniEventFuncSet(fn_1_157C);
    BoardSpaceLandEventFuncSet(fn_1_778);
    BoardStarHostSet(lbl_1_data_52C);
    BoardBooHouseHostSet(lbl_1_data_52E);
    BoardLotteryHostSet(lbl_1_data_52E);
    BoardShopHostSet(lbl_1_data_52E);
    BoardJunctionMaskSet(0xC000);
    BoardJunctionMaskSet(0x3000);
}

void BoardDestroy(void) {
    s32 i;

    fn_1_4864();
    fn_1_D00();
    for (i = 0; i < 33; i++) {
        if (lbl_1_bss_6C4[i] != 0) {
            BoardModelKill(lbl_1_bss_6C4[i]);
            lbl_1_bss_6C4[i] = 0;
        }
    }
    if (lbl_1_data_530 != -1) {
        BoardModelKill(lbl_1_data_530);
        lbl_1_data_530 = -1;
    }
    if (lbl_1_data_52E != -1) {
        BoardModelKill(lbl_1_data_52E);
        lbl_1_data_52E = -1;
    }
    if (lbl_1_data_52C != -1) {
        BoardModelKill(lbl_1_data_52C);
        lbl_1_data_52C = -1;
    }
    if (lbl_1_data_528 != -1) {
        BoardModelKill(lbl_1_data_528);
        lbl_1_data_528 = -1;
    }
    if (lbl_1_data_52A != -1) {
        BoardModelKill(lbl_1_data_52A);
        lbl_1_data_52A = -1;
    }
    BoardSpaceDestroy();
}

static void fn_1_730(void) {
    s16 var_r31;

    var_r31 = BoardModelIDGet(lbl_1_data_528);
    Hu3DModelLightInfoSet(var_r31, 1);
}

static void fn_1_774(void) {
}

static s32 fn_1_778(void) {
    s32 temp_r31;
    s32 temp_r30;
    u32 temp_r29;

    temp_r31 = GWSystem.player_curr;
    temp_r30 = GWPlayer[temp_r31].space_curr;
    temp_r29 = BoardSpaceFlagGet(0, temp_r30);
    if (temp_r29 & 0x800) {
        fn_1_77EC(temp_r31, temp_r30);
    } else if (temp_r29 & 0x400) {
        fn_1_7528(temp_r31, temp_r30);
    }
}

static s32 fn_1_814(void) {
    s32 temp_r27;
    s32 var_r30;
    s32 var_r29;
    s32 var_r26;
    BoardSpace *temp_r31;
    BoardSpace *temp_r28;

    temp_r27 = GWSystem.player_curr;
    temp_r31 = BoardSpaceGet(0, GWPlayer[temp_r27].space_curr);
    if (temp_r31->flag & 0x3000) {
        if (BoardPlayerSizeGet(temp_r27) == 2 || GWPlayer[temp_r27].bowser_suit) {
            return 0;
        }
        if (temp_r31->flag & 0x2000) {
            if (lbl_1_bss_0->unk00_field0 != 0) {
                return 0;
            }
        } else if (temp_r31->flag & 0x1000) {
            if (lbl_1_bss_0->unk00_field0 != 1) {
                return 0;
            }
        }
        fn_1_4FD8();
        return 1;
    }
    var_r29 = -1;
    for (var_r30 = 0; var_r30 < temp_r31->link_cnt; var_r30++) {
        if (temp_r31->link[var_r30] != -1) {
            temp_r28 = BoardSpaceGet(0, temp_r31->link[var_r30]);
            if (temp_r28->flag & 0x8000) {
                var_r29 = 0;
                var_r26 = temp_r31->link[var_r30];
                break;
            } else if (temp_r28->flag & 0x4000) {
                var_r29 = 1;
                var_r26 = temp_r31->link[var_r30];
                break;
            }
        }
    }
    if (var_r29 != -1) {
        fn_1_586C(var_r29, var_r26);
        return 1;
    }
    return 0;
}

static void fn_1_9E8(void) {
    BoardModelVisibilitySet(lbl_1_bss_6C4[6], 1);
    BoardModelVisibilitySet(lbl_1_bss_6C4[7], 0);
    BoardModelVisibilitySet(lbl_1_bss_6C4[8], 0);
    BoardModelVisibilitySet(lbl_1_bss_6C4[9], 0);
    BoardModelVisibilitySet(lbl_1_bss_6C4[10], 0);
    BoardModelVisibilitySet(lbl_1_bss_6C4[11], 0);
    BoardModelVisibilitySet(lbl_1_bss_6C4[12], 0);
    BoardModelVisibilitySet(lbl_1_bss_6C4[13], 0);
    BoardModelVisibilitySet(lbl_1_bss_6C4[14], 1);
    BoardModelVisibilitySet(lbl_1_bss_6C4[15], 1);
    BoardModelMotionStart(lbl_1_bss_6C4[6], 0, 0);
    BoardModelMotionSpeedSet(lbl_1_bss_6C4[6], 0.0f);
    BoardModelMotionStart(lbl_1_bss_6C4[14], 0, 0x40000001);
    BoardModelMotionStart(lbl_1_bss_6C4[15], 0, 0x40000001);
    BoardModelHookSet(lbl_1_bss_6C4[6], "amida_ban_07-sirenr", lbl_1_bss_6C4[14]);
    BoardModelHookSet(lbl_1_bss_6C4[6], "amida_ban_07-sirenl", lbl_1_bss_6C4[15]);
    BoardModelVisibilitySet(lbl_1_bss_6C4[16], 1);
    BoardModelVisibilitySet(lbl_1_bss_6C4[17], 1);
    BoardModelVisibilitySet(lbl_1_bss_6C4[18], 1);
    BoardModelVisibilitySet(lbl_1_bss_6C4[19], 0);
    BoardModelVisibilitySet(lbl_1_bss_6C4[20], 0);
    BoardModelVisibilitySet(lbl_1_bss_6C4[21], 1);
    BoardModelVisibilitySet(lbl_1_bss_6C4[22], 1);
    BoardModelMotionStart(lbl_1_bss_6C4[21], 0, 0);
    BoardModelMotionSpeedSet(lbl_1_bss_6C4[21], 0.0f);
    BoardModelMotionStart(lbl_1_bss_6C4[18], 0, 0);
    BoardModelMotionSpeedSet(lbl_1_bss_6C4[18], 0.0f);
    BoardModelExistDupe(lbl_1_bss_6C4[16], 0);
    BoardModelMotionStart(lbl_1_bss_6C4[16], 0, 0x40000001);
    BoardModelMotionStart(lbl_1_bss_6C4[17], 0, 0x40000001);
    BoardModelMotionStart(lbl_1_bss_6C4[22], 0, 0x40000001);
    BoardModelHookSet(lbl_1_bss_6C4[21], "m_goraund_01-flag1", lbl_1_bss_6C4[22]);
}

static void fn_1_D00(void) {
}

static void fn_1_D04(void) {
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    s8 sp8[4];
    s32 temp_r28;
    s32 temp_r3;
    s32 var_r26;
    s32 var_r25;
    s32 temp_r30;
    s32 i;
    s32 j;

    temp_r30 = GWSystem.player_curr;
    var_r26 = 0;
    if (BoardPlayerItemCount(temp_r30) == 3) {
        BoardWinCreate(0, MAKE_MESSID(10, 9), 0);
        BoardWinWait();
        BoardWinKill();
        HuPrcEnd();
    }
    lbl_1_bss_6B6[0] = 0;
    i = 1;
    while (i < 4) {
        lbl_1_bss_6B6[i] = frandmod(14);
        if (lbl_1_bss_6B6[i] != 10 && lbl_1_bss_6B6[i] != 13) {
            for (j = 0; j < i; j++) {
                if (lbl_1_bss_6B6[i] == lbl_1_bss_6B6[j]) {
                    lbl_1_bss_6B6[i] = -1;
                }
            }
            if (lbl_1_bss_6B6[i] != -1) {
                i++;
            }
        }
    }
    fn_1_D740(lbl_1_bss_6B6);
    for (i = 0; i < 4; i++) {
        sp8[i] = lbl_1_bss_6B6[i];
    }
    if (BoardComPreferItemGet(temp_r30, sp8, 4) != -1) {
        var_r26 = 1;
    }
    HuAudFXPlay(0x40D);
    HuAudFXPlay(0x40E);
    BoardModelAttrReset(lbl_1_bss_6C4[21], 0x40000004);
    BoardModelMotionStart(lbl_1_bss_6C4[21], 0, 0);
    temp_r28 = GWPlayer[temp_r30].space_curr;
    temp_r3 = BoardSpaceLinkFlagSearch(0, temp_r28, 0x02000000);
    BoardSpacePosGet(0, temp_r3, &sp3C);
    sp30.x = 150.0f;
    sp30.y = 0.0f;
    sp30.z = 0.0f;
    sp24.x = -45.0f;
    sp24.y = 0.0f;
    sp24.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_6C4[4], &sp24, &sp30, 1880.0f, -1.0f, 21);
    BoardCameraMotionWait();
    BoardWinCreateChoice(2, MAKE_MESSID(10, 0), 0, 0);
    if (GWPlayer[temp_r30].com) {
        if (var_r26 != 0) {
            BoardComKeySetLeft();
        } else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    var_r25 = BoardWinChoiceGet();
    if (var_r25 != 0) {
        BoardWinCreate(2, MAKE_MESSID(10, 4), 0);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        HuAudFXPlay(0x40F);
        BoardModelMotionStart(lbl_1_bss_6C4[21], 0, 0x40000004);
        while (!BoardModelMotionEndCheck(lbl_1_bss_6C4[21])) {
            HuPrcVSleep();
        }
        BoardModelMotionSpeedSet(lbl_1_bss_6C4[21], 0.0f);
        BoardModelAttrReset(lbl_1_bss_6C4[21], 0x40000004);
        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        fn_1_DD84();
        HuPrcEnd();
    }
    BoardPlayerMoveBetween(temp_r30, temp_r28, temp_r3);
    while (GWPlayer[temp_r30].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r30, 1, 0x40000001);
    sp18.x = 0.0f;
    sp18.y = 0.0f;
    sp18.z = 0.0f;
    spC.x = -45.0f;
    spC.y = 0.0f;
    spC.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_6C4[21], &spC, &sp18, 1200.0f, -1.0f, 21);
    BoardCameraMotionWait();
    fn_1_DE94();
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    BoardAudSeqPause(0, 0, 1000);
    while (GWPlayer[temp_r30].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r30, 1, 0x40000001);
    HuPrcEnd();
}

static void fn_1_1254(void) {
    BoardWinKill();
    CharModelDataClose(-1);
    lbl_1_bss_4 = NULL;
}

static void fn_1_128C(void) {
    lbl_1_bss_4 = HuPrcChildCreate(fn_1_D04, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_4, fn_1_1254);
    while (lbl_1_bss_4) {
        HuPrcVSleep();
    }
}

static void fn_1_130C(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 temp_r31;
    s32 var_r28;
    s32 temp_r30;
    s32 temp_r3;

    temp_r31 = GWSystem.player_curr;
    BoardWinCreateChoice(2, MAKE_MESSID(11, 0), 0, 0);
    if (GWPlayer[temp_r31].com) {
        BoardComKeySetLeft();
    }
    BoardWinWait();
    BoardWinKill();
    var_r28 = BoardWinChoiceGet();
    if (var_r28 != 0) {
        BoardWinCreate(2, MAKE_MESSID(11, 4), 0);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        return;
    }
    BoardModelMotionStart(lbl_1_bss_6C4[6], 0, 0);
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 170.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_6C4[6], &sp14, &sp8, 1200.0f, 25.0f, 21);
    temp_r30 = GWPlayer[temp_r31].space_curr;
    temp_r3 = BoardSpaceLinkFlagSearch(0, temp_r30, 0x02000000);
    BoardSpacePosGet(0, temp_r3, &sp20);
    BoardPlayerMoveBetween(temp_r31, temp_r30, temp_r3);
    BoardPlayerMotionStart(temp_r31, 1, 0x40000001);
    BoardAudSeqPause(0, 1, 1000);
    fn_1_9DD8();
    while (GWPlayer[temp_r31].moving) {
        HuPrcVSleep();
    }
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 1000);
    while (GWPlayer[temp_r31].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(temp_r31, 1, 0x40000001);
}

static s32 fn_1_157C(void) {
    s32 temp_r31;
    s16 temp_curr;

    temp_curr = GWPlayer[GWSystem.player_curr].space_curr;
    temp_r31 = BoardSpaceFlagGet(0, temp_curr) & 0x600000;
    BoardRollDispSet(0);
    if (temp_r31 == 0x200000) {
        fn_1_130C();
    } else if (temp_r31 == 0x400000) {
        fn_1_128C();
    }
    BoardRollDispSet(1);
}

static void fn_1_1670(void) {
    if (lbl_1_bss_0->unk00_field0 == 0) {
        BoardModelVisibilitySet(lbl_1_bss_6C4[2], 1);
        BoardModelVisibilitySet(lbl_1_bss_6C4[3], 0);
    } else {
        BoardModelVisibilitySet(lbl_1_bss_6C4[2], 0);
        BoardModelVisibilitySet(lbl_1_bss_6C4[3], 1);
    }
}

static void fn_1_1700(void) {
    Vec sp8;
    Mtx sp14;

    lbl_1_bss_6B1 = 0;
    lbl_1_bss_6AE = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 10), NULL, 0);
    lbl_1_bss_644 = BoardModelMotionMaxTimeGet(lbl_1_bss_6AE);
    BoardModelVisibilitySet(lbl_1_bss_6AE, 0);
    memset(lbl_1_bss_2C, 0, sizeof(lbl_1_bss_2C));
    if (BoardSpaceRead(1, DATA_MAKE_NUM(DATADIR_W01, 6)) == 0) {
        if (lbl_1_bss_0->unk00_field0 == 0) {
            BoardSpaceFlagPosGet(1, 0x2000, &sp8);
            BoardModelMotionTimeSet(lbl_1_bss_6AE, lbl_1_bss_644);
            lbl_1_bss_63C = -90.0f;
        } else {
            BoardSpaceFlagPosGet(1, 0x1000, &sp8);
            BoardModelMotionTimeSet(lbl_1_bss_6AE, 0.0f);
            lbl_1_bss_63C = 90.0f;
        }
        lbl_1_bss_654 = sp8;
        BoardModelPosSetV(lbl_1_bss_6C4[0], &sp8);
        BoardModelRotSet(lbl_1_bss_6C4[0], 0.0f, lbl_1_bss_63C, 0.0f);
        BoardModelExistDupe(lbl_1_bss_6C4[0], 1);
        BoardModelExistDupe(lbl_1_bss_6C4[1], 1);
        fn_8006DDE8(lbl_1_bss_6C4[1], 500.0f);
        PSMTXIdentity(sp14);
        BoardModelMtxSet(lbl_1_bss_6C4[0], &sp14);
        fn_1_1670();
    }
}

static void fn_1_1990(void) {
    Vec sp10;
    float var_f31;
    s32 var_r29;
    s32 var_r30;
    s16 sp8[3];
    BoardSpace *temp_r31;
    BoardSpace *temp_r3;

    var_r29 = lbl_1_bss_6AC;
    var_f31 = 0.0f;
    while (TRUE) {
        temp_r31 = BoardSpaceGet(1, var_r29);
        if (lbl_1_bss_0->unk00_field0 == 0) {
            var_r30 = temp_r31->link[0];
        } else {
            BoardSpaceLinkTargetListGet(1, var_r29, sp8);
            var_r30 = sp8[0];
        }
        if (var_r30 == 0) {
            break;
        }
        temp_r3 = BoardSpaceGet(1, var_r30);
        if (!temp_r3) {
            temp_r3 = temp_r31;
            break;
        }
        PSVECSubtract(&temp_r3->pos, &temp_r31->pos, &sp10);
        var_f31 += PSVECMag(&sp10);
        if (var_f31 >= lbl_1_bss_640) {
            break;
        }
        var_r29 = var_r30;
    }
    if (temp_r31->flag & 8) {
        lbl_1_bss_6B3 = 1;
    } else {
        lbl_1_bss_6B3 = 0;
    }
}

static void fn_1_1AD8(BoardCameraData *camera) {
    camera->pos = lbl_1_bss_630;
    camera->up = lbl_1_bss_624;
    camera->target = lbl_1_bss_618;
}

static void fn_1_1B3C(void) {
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    Mtx sp48;

    PSVECSubtract(&lbl_1_bss_654, &lbl_1_bss_648, &sp30);
    if (lbl_1_bss_6B3 != 0) {
        BoardModelPosGet(lbl_1_bss_6C4[1], &sp3C);
        PSVECSubtract(&sp3C, &lbl_1_bss_654, &sp18);
        PSVECNormalize(&sp18, &sp18);
        sp24 = lbl_1_bss_648;
        spC = lbl_1_bss_654;
        BoardMTXCalcLookAt(sp48, &spC, &sp18, &sp24);
        PSMTXTranspose(sp48, lbl_1_bss_678);
        PSMTXRotRad(sp48, 'z', MTXDegToRad(lbl_1_bss_660.z));
        PSMTXConcat(lbl_1_bss_678, sp48, lbl_1_bss_678);
    } else {
        if (sp30.z != 0.0f || sp30.x != 0.0f) {
            lbl_1_bss_660.y = atan2d(sp30.x, sp30.z);
            lbl_1_bss_660.x = -atan2d(sp30.y, VECMagXZ(&sp30));
        } else {
            lbl_1_bss_660.x = lbl_1_bss_660.y = 0.0f;
        }
        PSMTXRotRad(lbl_1_bss_678, 'z', MTXDegToRad(lbl_1_bss_660.z));
        PSMTXRotRad(sp48, 'x', MTXDegToRad(lbl_1_bss_660.x));
        PSMTXConcat(sp48, lbl_1_bss_678, lbl_1_bss_678);
        PSMTXRotRad(sp48, 'y', MTXDegToRad(lbl_1_bss_660.y));
        PSMTXConcat(sp48, lbl_1_bss_678, lbl_1_bss_678);
    }
}

static void fn_1_1EE4(void) {
    Bss10Work *temp_r31;

    if (lbl_1_bss_10) {
        temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_10, Bss10Work);
        temp_r31->unk00_field0 = 1;
    }
}

static void fn_1_1F2C(omObjData *arg0) {
    Bss10Work *temp_r31 = OM_GET_WORK_PTR(arg0, Bss10Work);

    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        omDelObjEx(HuPrcCurrentGet(), arg0);
        lbl_1_bss_10 = NULL;
        return;
    }
    fn_1_1FA4();
}

static void fn_1_1FA4(void) {
    Vec sp18;
    Vec spC;
    float temp_f28;
    float temp_f29;
    float var_f27;

    spC.x = lbl_1_bss_648.x;
    spC.y = lbl_1_bss_648.y + 200.0f;
    spC.z = lbl_1_bss_648.z;
    PSVECSubtract(&spC, &lbl_1_bss_618, &spC);
    PSVECScale(&spC, &spC, 0.08f);
    PSVECAdd(&spC, &lbl_1_bss_618, &lbl_1_bss_618);
    PSVECSubtract(&lbl_1_bss_654, &lbl_1_bss_648, &spC);
    if (spC.x != 0.0f || spC.z != 0.0f) {
        temp_f29 = atan2f(spC.y, VECMagXZ(&spC));
        temp_f28 = atan2f(-spC.x, -spC.z);
    } else {
        temp_f29 = temp_f28 = 0.0f;
        return;
    }
    temp_f29 += -0.27925268f;
    if (lbl_1_bss_6B3 != 0) {
        if (lbl_1_bss_66C < 0.08f) {
            lbl_1_bss_66C -= 0.00033333333f;
        }
        BoardModelPosGet(lbl_1_bss_6C4[1], &sp18);
        if (lbl_1_bss_0->unk00_field0 == 0) {
            var_f27 = -2500.0f;
        } else {
            var_f27 = 2500.0f;
        }
        sp18.x = sp18.x + var_f27 * sin(1.4137166738510132); // TODO: should be sind(81)
        sp18.y = sp18.y + -150.0f;
        sp18.z = sp18.z + var_f27 * cos(1.4137166738510132); // TODO: should be cosd(81)
        PSVECSubtract(&sp18, &lbl_1_bss_630, &spC);
        PSVECScale(&spC, &spC, lbl_1_bss_66C);
        PSVECAdd(&spC, &lbl_1_bss_630, &lbl_1_bss_630);
    } else {
        if (lbl_1_bss_66C < 0.08f) {
            lbl_1_bss_66C += 0.00066666666f;
        }
        spC.x = 400.0 * (sin(temp_f28) * cos(temp_f29));
        spC.y = 400.0 * -sin(temp_f29);
        spC.z = 400.0 * (cos(temp_f28) * cos(temp_f29));
        PSVECAdd(&lbl_1_bss_618, &spC, &spC);
        PSVECSubtract(&spC, &lbl_1_bss_630, &spC);
        PSVECScale(&spC, &spC, lbl_1_bss_66C);
        PSVECAdd(&spC, &lbl_1_bss_630, &lbl_1_bss_630);
    }
}

static float fn_1_2524(void) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f30;
    s16 sp8;
    s32 var_r29;
    s32 i;

    sp24 = lbl_1_bss_654;
    if (GWPlayer[lbl_1_bss_6B4].com) {
        if (lbl_1_bss_6B3 != 0) {
            return 0.0f;
        }
        for (i = 0; i < 24; i++) {
            if (lbl_1_bss_600[i] == 0) {
                BoardModelPosGet(lbl_1_bss_5D0[i], &sp18);
                PSVECSubtract(&sp18, &sp24, &spC);
                if (!(PSVECMag(&spC) > 400.0f)) {
                    break;
                }
            }
        }
        if (i == 24) {
            return 0.0f;
        }
        PSVECSubtract(&sp18, &sp24, &spC);
        var_f30 = atan2d(spC.x, spC.z);
        if (var_f30 > 0.0f) {
            var_f30 = 45.0f;
        } else {
            var_f30 = -45.0f;
        }
    } else {
        var_r29 = GWPlayer[lbl_1_bss_6B4].port;
        sp8 = HuPadStkX[var_r29];
        OSs16tof32(&sp8, &var_f30);
        var_f30 = var_f30 * 0.625f;
    }
    return var_f30;
}

static void fn_1_276C(void) {
    Vec sp58;
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    float temp_f26;
    float var_f27;
    Mtx sp70;

    fn_1_1B3C();
    if (lbl_1_bss_6B1 != 0) {
        lbl_1_bss_660.z = 0.0f;
        return;
    }
    var_f27 = fn_1_2524();
    BoardDAngleCalcRange(&lbl_1_bss_660.z, var_f27, 5.0f);
    temp_f26 = 6.0f + 6.0f * (lbl_1_bss_660.z / 45.0f) - 1.0f;
    if (lbl_1_bss_660.z > 22.5f) {
        BoardPlayerMotionStart(lbl_1_bss_6B4, lbl_1_bss_5CC[1], 0);
        BoardPlayerMotionTimeSet(lbl_1_bss_6B4, temp_f26);
    } else if (lbl_1_bss_660.z < -22.5f) {
        BoardPlayerMotionStart(lbl_1_bss_6B4, lbl_1_bss_5CC[1], 0);
        BoardPlayerMotionTimeSet(lbl_1_bss_6B4, temp_f26);
    } else {
        BoardPlayerMotionShiftSet(lbl_1_bss_6B4, lbl_1_bss_5CC[0], 0.0f, 10.0f, 0x40000001);
    }
    fn_1_2F18();
}

static void fn_1_2F18(void) {
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f29;
    Mtx spD8;
    Mtx spA8;
    Mtx sp78;
    Mtx sp48;
    s32 i;

    if (lbl_1_bss_6B3 == 0) {
        var_f29 = lbl_1_bss_660.z;
        if (var_f29 > 180.0f) {
            var_f29 -= 360.0f;
        }
        BoardModelPosGet(lbl_1_bss_6C4[0], &spC);
        PSVECSubtract(&lbl_1_bss_654, &lbl_1_bss_648, &sp18);
        if (sp18.z != 0.0f || sp18.x != 0.0f) {
            sp24.y = atan2d(sp18.x, sp18.z);
            sp24.x = -atan2d(sp18.y, VECMagXZ(&sp18));
        } else {
            sp24.x = sp24.y = 0.0f;
        }
        PSMTXTrans(spD8, 0.0f, 180.0f, 0.0f);
        PSMTXRotRad(spA8, 'x', MTXDegToRad(sp24.x));
        PSMTXRotRad(sp78, 'y', MTXDegToRad(sp24.y));
        PSMTXRotRad(sp48, 'z', MTXDegToRad(var_f29));
        PSMTXConcat(spA8, sp48, sp48);
        PSMTXConcat(sp78, sp48, sp48);
        PSMTXConcat(sp48, spD8, spD8);
        sp30.x = spD8[0][3];
        sp30.y = spD8[1][3];
        sp30.z = spD8[2][3];
        PSVECAdd(&sp30, &spC, &sp30);
        if (var_f29 < 27.000002f && var_f29 > -27.000002f) {
            return;
        }
        for (i = 0; i < 24; i++) {
            if (lbl_1_bss_600[i] == 0) {
                BoardModelPosGet(lbl_1_bss_5D0[i], &sp3C);
                if (BoardVecMaxDistXZCheck(&sp3C, &sp30, 180.0f)) {
                    CharModelLayerSetAll(2);
                    CharModelCoinEffectCreate(1, &sp3C);
                    BoardModelVisibilitySet(lbl_1_bss_5D0[i], 0);
                    BoardPlayerCoinsAdd(lbl_1_bss_6B4, 1);
                    HuAudFXPlay(7);
                    lbl_1_bss_600[i] = 1;
                    break;
                }
            }
        }
    }
}

static s16 lbl_1_data_580 = -1;

static void fn_1_3350(void) {
    Vec sp8;
    s16 temp_r3;
    ModelData *temp_r30;
    HsfObject *temp_r31;

    lbl_1_bss_674 += 0.002f;
    if (lbl_1_bss_670 > 0.18f) {
        lbl_1_bss_670 = 0.18f;
    } else if (lbl_1_bss_670 < 0.18f) {
        lbl_1_bss_670 += lbl_1_bss_674;
    }
    temp_r3 = BoardModelIDGet(lbl_1_bss_6AE);
    temp_r30 = &Hu3DData[temp_r3];
    Hu3DMotionExec(temp_r3, temp_r30->unk_08, temp_r30->unk_64, 0);
    temp_r31 = Hu3DModelObjPtrGet(temp_r3, "looppath-cube1");
    lbl_1_bss_648 = lbl_1_bss_654;
    lbl_1_bss_654.x = temp_r31->data.curr.pos.x;
    lbl_1_bss_654.y = temp_r31->data.curr.pos.y;
    lbl_1_bss_654.z = temp_r31->data.curr.pos.z;
    PSVECSubtract(&lbl_1_bss_648, &lbl_1_bss_654, &sp8);
    lbl_1_bss_640 += PSVECMag(&sp8);
}

static s32 lbl_1_data_594[8][2] = {
    { DATA_MAKE_NUM(DATADIR_W01, 34), DATA_MAKE_NUM(DATADIR_W01, 42) },
    { DATA_MAKE_NUM(DATADIR_W01, 35), DATA_MAKE_NUM(DATADIR_W01, 43) },
    { DATA_MAKE_NUM(DATADIR_W01, 36), DATA_MAKE_NUM(DATADIR_W01, 44) },
    { DATA_MAKE_NUM(DATADIR_W01, 37), DATA_MAKE_NUM(DATADIR_W01, 45) },
    { DATA_MAKE_NUM(DATADIR_W01, 38), DATA_MAKE_NUM(DATADIR_W01, 46) },
    { DATA_MAKE_NUM(DATADIR_W01, 39), DATA_MAKE_NUM(DATADIR_W01, 47) },
    { DATA_MAKE_NUM(DATADIR_W01, 40), DATA_MAKE_NUM(DATADIR_W01, 48) },
    { DATA_MAKE_NUM(DATADIR_W01, 41), DATA_MAKE_NUM(DATADIR_W01, 49) }
};

static void fn_1_3514(s32 arg0) {
    s32 temp_r30;
    s32 i;

    temp_r30 = GWPlayer[arg0].character;
    for (i = 0; i < 2; i++) {
        lbl_1_bss_5CC[i] = BoardPlayerMotionCreate(arg0, lbl_1_data_594[temp_r30][i]);
    }
}

static void fn_1_35B4(s32 arg0) {
    s32 i;

    for (i = 0; i < 2; i++) {
        BoardPlayerMotionKill(arg0, lbl_1_bss_5CC[i]);
        lbl_1_bss_5CC[i] = -1;
    }
}

static void fn_1_3624(void) {
    Mtx sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    float temp_f28;
    float var_f30;
    float var_f29;
    s32 temp_r19;
    Bss10Work *temp_r18;
    s16 sp10;
    s16 var_r25;
    s16 i;

    lbl_1_bss_674 = lbl_1_bss_670 = 0.0f;
    lbl_1_bss_640 = 0.0f;
    lbl_1_bss_660.x = 0.0f;
    lbl_1_bss_660.y = 0.0f;
    lbl_1_bss_660.z = 0.0f;
    lbl_1_bss_6A8 = 0.0f;
    lbl_1_bss_6B3 = 0;
    lbl_1_bss_624.x = 0.0f;
    lbl_1_bss_624.z = 0.0f;
    lbl_1_bss_624.y = 1.0f;
    lbl_1_bss_66C = 0.08f;
    fn_1_3514(lbl_1_bss_6B4);
    BoardPlayerMotionStart(lbl_1_bss_6B4, lbl_1_bss_5CC[0], 0x40000001);
    BoardSpaceAttrSet(0, 1);
    fn_1_97F4();
    BoardModelMotionStart(lbl_1_bss_6AE, 0, 0);
    if (lbl_1_bss_0->unk00_field0 == 0) {
        BoardModelMotionTimeSet(lbl_1_bss_6AE, lbl_1_bss_644);
        lbl_1_bss_63C = -90.0f;
        lbl_1_bss_6AC = BoardSpaceFlagPosGet(1, 0x2000, &sp3C);
        var_r25 = BoardSpaceFlagSearch(0, 0x1000);
        var_f30 = -1.0f;
    } else {
        BoardModelMotionTimeSet(lbl_1_bss_6AE, 0.0f);
        lbl_1_bss_63C = 90.0f;
        lbl_1_bss_6AC = BoardSpaceFlagPosGet(1, 0x1000, &sp3C);
        var_r25 = BoardSpaceFlagSearch(0, 0x2000);
        var_f30 = 1.0f;
    }
    lbl_1_bss_654 = sp3C;
    lbl_1_bss_648 = lbl_1_bss_654;
    BoardModelMotionSpeedSet(lbl_1_bss_6AE, lbl_1_bss_670);
    BoardPlayerPosSetV(lbl_1_bss_6B4, &lbl_1_bss_654);
    BoardCameraPosCalcFuncSet(fn_1_1AD8);
    lbl_1_bss_10 = omAddObjEx(boardObjMan, 0x7E02, 0, 0, -1, fn_1_1F2C);
    temp_r18 = OM_GET_WORK_PTR(lbl_1_bss_10, Bss10Work);
    temp_r18->unk00_field0 = 0;
    sp30.x = -40.0f;
    sp30.z = 0.0f;
    sp30.y = -lbl_1_bss_63C;
    BoardCameraMotionStartEx(lbl_1_bss_6C4[0], &sp30, NULL, 150.0f, -1.0f, 2);
    BoardCameraMotionWait();
    BoardModelPosGet(lbl_1_bss_6C4[0], &lbl_1_bss_618);
    lbl_1_bss_630.x = lbl_1_bss_618.x + 1000.0 * (sind(sp30.y) * cosd(sp30.x));
    lbl_1_bss_630.y = lbl_1_bss_618.y + 1000.0 * -sind(sp30.x);
    lbl_1_bss_630.z = lbl_1_bss_618.z + 1000.0 * (cosd(sp30.y) * cosd(sp30.x));
    PSMTXRotRad(lbl_1_bss_678, 'y', MTXDegToRad(lbl_1_bss_63C));
    BoardModelMtxSet(lbl_1_bss_6C4[0], &lbl_1_bss_678);
    BoardPlayerMtxSet(lbl_1_bss_6B4, &lbl_1_bss_678);
    BoardModelRotSet(lbl_1_bss_6C4[0], 0.0f, 0.0f, 0.0f);
    BoardPlayerRotSet(lbl_1_bss_6B4, 0.0f, 0.0f, 0.0f);
    BoardPlayerExistCheck(lbl_1_bss_6B4, 0);
    BoardMusStart(1, 0x10, 0x7F, 0);
    fn_1_50D4();
    BoardStatusShowSetForce(lbl_1_bss_6B4);
    BoardStatusShowSet(lbl_1_bss_6B4, 1);
    while (!BoardStatusStopCheck(lbl_1_bss_6B4)) {
        HuPrcVSleep();
    }
    temp_r19 = HuAudFXPlay(0x40C);
    fn_1_4774();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    lbl_1_bss_6B0 = 1;
    HuAudFXPlay(0x413);
    while (TRUE) {
        fn_1_1990();
        fn_1_3350();
        fn_1_276C();
        BoardModelPosSetV(lbl_1_bss_6C4[0], &lbl_1_bss_654);
        BoardPlayerPosSetV(lbl_1_bss_6B4, &lbl_1_bss_654);
        if (BoardPlayerSizeGet(lbl_1_bss_6B4) != 1) {
            PSMTXTrans(sp48, 0.0f, 30.0f, 0.0f);
        } else {
            PSMTXTrans(sp48, 0.0f, 400.0f, 250.0f);
        }
        BoardModelMtxSet(lbl_1_bss_6C4[0], &lbl_1_bss_678);
        PSMTXConcat(lbl_1_bss_678, sp48, sp48);
        BoardPlayerMtxSet(lbl_1_bss_6B4, &sp48);
        if (lbl_1_bss_0->unk00_field0 == 0) {
            var_f29 = -lbl_1_bss_670;
        } else {
            var_f29 = lbl_1_bss_670;
        }
        BoardModelMotionSpeedSet(lbl_1_bss_6AE, var_f29);
        if (lbl_1_bss_0->unk00_field0 == 0) {
            if (BoardModelMotionTimeGet(lbl_1_bss_6AE) <= 0.0f) {
                break;
            }
        } else {
            if (BoardModelMotionTimeGet(lbl_1_bss_6AE) >= lbl_1_bss_644) {
                break;
            }
        }
        HuPrcVSleep();
    }
    PSMTXIdentity(lbl_1_bss_678);
    fn_1_4864();
    HuAudFXStop(temp_r19);
    fn_1_1EE4();
    fn_1_98EC();
    if (BoardPlayerSizeGet(lbl_1_bss_6B4) == 1) {
        PSMTXTrans(sp48, 0.0f, 400.0f, 250.0f);
    } else {
        PSMTXTrans(sp48, 0.0f, 30.0f, 0.0f);
    }
    BoardModelMtxSet(lbl_1_bss_6C4[0], &lbl_1_bss_678);
    BoardPlayerMtxSet(lbl_1_bss_6B4, &sp48);
    lbl_1_bss_660.x = lbl_1_bss_660.z = 0.0f;
    BoardAudSeqFadeOut(1, 1000);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    HuAudFXPlay(0x401);
    temp_f28 = (-lbl_1_bss_63C - lbl_1_bss_660.y) / 30.0f;
    for (i = 0; i < 30; i++) {
        BoardModelRotSetV(lbl_1_bss_6C4[0], &lbl_1_bss_660);
        BoardPlayerRotSetV(lbl_1_bss_6B4, &lbl_1_bss_660);
        lbl_1_bss_660.y += temp_f28 * var_f30;
        HuPrcVSleep();
    }
    lbl_1_bss_660.y = -lbl_1_bss_63C;
    BoardModelRotSetV(lbl_1_bss_6C4[0], &lbl_1_bss_660);
    BoardPlayerRotSetV(lbl_1_bss_6B4, &lbl_1_bss_660);
    BoardStatusShowSet(lbl_1_bss_6B4, 0);
    BoardSpaceAttrReset(0, 1);
    fn_1_53B8();
    BoardCameraMoveSet(0);
    BoardCameraTargetPlayerSet(lbl_1_bss_6B4);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    do {
        HuPrcVSleep();
    } while (WipeStatGet() != 0);
    BoardPlayerIdleSet(lbl_1_bss_6B4);
    BoardPlayerMtxSet(lbl_1_bss_6B4, &lbl_1_bss_678);
    BoardCameraPosCalcFuncSet(NULL);
    BoardPlayerExistCheck(lbl_1_bss_6B4, 1);
    BoardSpacePosGet(0, var_r25, &sp3C);
    GWPlayer[lbl_1_bss_6B4].space_curr = var_r25;
    BoardPlayerPosSetV(lbl_1_bss_6B4, &sp3C);
    fn_1_35B4(lbl_1_bss_6B4);
    lbl_1_bss_6B2 = 1;
}

static void fn_1_45F4(void) {
    if (lbl_1_bss_6B2 != 0) {
        if (lbl_1_bss_0->unk00_field0 == 0) {
            lbl_1_bss_0->unk00_field0 = 1;
        } else {
            lbl_1_bss_0->unk00_field0 = 0;
        }
        lbl_1_bss_6B2 = 0;
        fn_1_1670();
    }
    fn_1_87AC();
    while (lbl_1_bss_C) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 1000);
    BoardCameraMoveSet(1);
    BoardCameraMotionWait();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardStatusShowSetAll(1);
}

static void fn_1_4774(void) {
    float sp8[2];
    float var_f31;
    float var_f30;

    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(13, 5));
    var_f31 = -10000.0f;
    var_f30 = 352.0f;
    lbl_1_data_580 = HuWinCreate(var_f31, var_f30, sp8[0], sp8[1], 0);
    HuWinBGTPLvlSet(lbl_1_data_580, 0.0f);
    HuWinMesSpeedSet(lbl_1_data_580, 0);
    HuWinMesSet(lbl_1_data_580, MAKE_MESSID(13, 5));
}

static void fn_1_4864(void) {
    if (lbl_1_data_580 != -1) {
        HuWinKill(lbl_1_data_580);
        lbl_1_data_580 = -1;
    }
}

static s32 fn_1_48B4(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    u32 var_r31;
    s32 i;
    s32 temp_r28;
    s32 temp_r30;

    var_r31 = 0;
    lbl_1_bss_6B0 = 0;
    lbl_1_bss_6B1 = 0;
    lbl_1_bss_6B2 = 0;
    lbl_1_bss_6B4 = GWSystem.player_curr;
    temp_r30 = GWPlayer[lbl_1_bss_6B4].space_curr;
    BoardPlayerMotionShiftSet(lbl_1_bss_6B4, 1, 0.0f, 14.0f, 0x40000001);
    BoardWinCreateChoice(0, MAKE_MESSID(13, 0), -1, 0);
    if (GWPlayer[lbl_1_bss_6B4].com) {
        fn_1_9D00(lbl_1_bss_6B4);
    }
    BoardWinWait();
    if (BoardWinChoiceGet() != 0) {
        return 0;
    }
    BoardWinCreate(2, 0xD0006, 0);
    BoardWinWait();
    temp_r28 = BoardSpaceLinkFlagSearch(0, temp_r30, 0x02000000);
    BoardSpacePosGet(0, temp_r30, &sp20);
    BoardSpacePosGet(0, temp_r28, &sp14);
    PSVECSubtract(&sp14, &sp20, &sp8);
    PSVECNormalize(&sp8, &sp8);
    var_f31 = atan2d(-sp8.x, -sp8.z);
    BoardPlayerRotSet(lbl_1_bss_6B4, 0.0f, var_f31, 0.0f);
    BoardPlayerMoveBetween(lbl_1_bss_6B4, temp_r30, temp_r28);
    while (GWPlayer[lbl_1_bss_6B4].moving) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(lbl_1_bss_6B4);
    while (TRUE) {
        BoardWinCreateChoice(1, MAKE_MESSID(13, 1), 0, 0);
        BoardWinAttrSet(0x10);
        if (GWPlayer[lbl_1_bss_6B4].com) {
            if (BoardPlayerCoinsGet(lbl_1_bss_6B4) >= 5) {
                BoardComKeySetUp();
            } else {
                BoardComKeySetDown();
            }
        }
        BoardWinWait();
        if (BoardWinChoiceGet() == 1) {
            var_r31 = MAKE_MESSID(13, 3);
            break;
        }
        if (BoardWinChoiceGet() == 2) {
            BoardViewMapExec(lbl_1_bss_6B4);
            continue;
        }
        if (BoardPlayerCoinsGet(lbl_1_bss_6B4) < 5) {
            var_r31 = MAKE_MESSID(13, 4);
            break;
        }
        for (i = 0; i < 5; i++) {
            BoardPlayerCoinsAdd(lbl_1_bss_6B4, -1);
            HuAudFXPlay(0xE);
            HuPrcSleep(6);
        }
        HuAudFXPlay(0xF);
        BoardWinCreate(2, MAKE_MESSID(13, 2), 0);
        BoardWinWait();
        BoardWinKill();
        BoardAudSeqPause(0, 1, 1000);
        HuAudFXPlay(0x402);
        BoardStatusShowSetAll(0);
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        fn_1_852C();
        return 1;
    }
    if (var_r31 != 0) {
        BoardWinCreate(1, var_r31, 0);
        BoardWinWait();
        BoardWinKill();
    }
    BoardCameraTargetPlayerSet(lbl_1_bss_6B4);
    PSVECSubtract(&sp20, &sp14, &sp8);
    PSVECNormalize(&sp8, &sp8);
    var_f31 = atan2d(-sp8.x, -sp8.z);
    BoardPlayerRotSet(lbl_1_bss_6B4, 0.0f, var_f31, 0.0f);
    BoardPlayerMoveBetween(lbl_1_bss_6B4, temp_r28, temp_r30);
    while (GWPlayer[lbl_1_bss_6B4].moving) {
        HuPrcVSleep();
    }
    return 0;
}

static void fn_1_4E14(void) {
    if (fn_1_48B4() != 0) {
        fn_1_3624();
        fn_1_45F4();
    }
    HuPrcEnd();
}

static void fn_1_4FA8(void) {
    BoardWinKill();
    lbl_1_bss_8 = NULL;
}

static void fn_1_4FD8(void) {
    lbl_1_bss_6B4 = GWSystem.player_curr;
    BoardRollDispSet(0);
    if (BoardPlayerSizeGet(lbl_1_bss_6B4) == 2 || GWPlayer[lbl_1_bss_6B4].bowser_suit) {
        return;
    }
    lbl_1_bss_8 = HuPrcChildCreate(fn_1_4E14, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_8, fn_1_4FA8);
    while (lbl_1_bss_8) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

static void fn_1_50D4(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f30;
    float var_f31;
    BoardSpace *temp_r31;
    s32 var_r27;
    s32 var_r26;
    s32 var_r29;
    s32 var_r28;
    s32 i;

    for (i = 0; i < 24; i++) {
        lbl_1_bss_5D0[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 9), NULL, 0);
        BoardModelVisibilitySet(lbl_1_bss_5D0[i], 0);
        BoardModelMotionStart(lbl_1_bss_5D0[i], 0, 0x40000001);
        lbl_1_bss_600[i] = 0;
    }
    temp_f30 = 180.0f;
    var_r28 = BoardSpaceFlagPosGet(1, 0x2000, &sp20);
    var_r27 = BoardRand() & 1;
    var_r29 = i = 0;
    while (i < 24) {
        temp_r31 = BoardSpaceGet(1, var_r28);
        var_r28 = temp_r31->link[0];
        if (var_r28 == -1 || temp_r31->link_cnt == 0) {
            break;
        }
        if (!(temp_r31->flag & 0x80)) {
            sp14 = temp_r31->pos;
        } else {
            if (var_r29 >= 3) {
                if (BoardRandFloat() < 0.5f) {
                    var_r26 = 1;
                } else {
                    var_r26 = 0;
                }
                var_r27 = var_r26;
                var_r29 = 0;
            }
            PSVECSubtract(&sp14, &temp_r31->pos, &sp8);
            PSVECNormalize(&sp8, &sp8);
            var_f31 = atan2d(sp8.z, sp8.x);
            if (var_r27 != 0) {
                var_f31 += 180.0f;
            }
            sp20.x = temp_r31->pos.x + temp_f30 * sind(var_f31);
            sp20.y = temp_r31->pos.y + 80.0f;
            sp20.z = temp_r31->pos.z + temp_f30 * cosd(var_f31);
            BoardModelPosSetV(lbl_1_bss_5D0[i], &sp20);
            BoardModelVisibilitySet(lbl_1_bss_5D0[i], 1);
            sp14 = temp_r31->pos;
            i++;
            var_r29++;
        }
    }
}

static void fn_1_53B8(void) {
    s32 i;

    for (i = 0; i < 24; i++) {
        if (lbl_1_bss_5D0[i] != -1) {
            BoardModelKill(lbl_1_bss_5D0[i]);
            lbl_1_bss_5D0[i] = -1;
        }
    }
}

static s32 lbl_1_data_5D4 = -1;
static s32 lbl_1_data_5D8 = -1;

static s16 lbl_1_data_5DC[2][4] = {
    { 24, 25, 26, 27 },
    { 29, 30, 31, 32 }
};

static char *lbl_1_data_604[] = {
    "chara1", "chara2", "chara3"
};

static float lbl_1_data_610[2][2] = {
    { 90.0f,   0.0f },
    {  0.0f, 270.0f }
};

static void fn_1_543C(void) {
    float var_f31;
    s16 temp_r28;
    s16 temp_r29;
    s32 i;
    s32 j;
    char *sp10[] = { "cup1", "cup2", "cup3", "ya1" };
    s32 sp8[] = { 23, 28 };

    for (i = 0; i < 2; i++) {
        temp_r28 = lbl_1_bss_6C4[sp8[i]];
        BoardModelMotionStart(temp_r28, 0, 0x40000001);
        BoardModelExistDupe(temp_r28, 0);
        for (j = 0; j < 4; j++) {
            temp_r29 = lbl_1_bss_6C4[lbl_1_data_5DC[i][j]];
            BoardModelExistDupe(temp_r29, 1);
            BoardModelHookSet(temp_r28, sp10[j], temp_r29);
            BoardModelMotionStart(temp_r29, 0, 0x40000001);
            BoardModelRotSet(temp_r29, 0.0f, 360.0f * BoardRandFloat(), 0.0f);
        }
    }
    if (lbl_1_bss_0->unk01[0] != 0) {
        var_f31 = 0.0f;
    } else {
        var_f31 = 90.0f;
    }
    BoardModelRotSet(lbl_1_bss_6C4[27], 0.0f, var_f31, 0.0f);
    if (lbl_1_bss_0->unk01[1] != 0) {
        var_f31 = -90.0f;
    } else {
        var_f31 = 0.0f;
    }
    BoardModelRotSet(lbl_1_bss_6C4[32], 0.0f, var_f31, 0.0f);
}

static void fn_1_5694(s32 arg0) {
    s16 temp_r29;
    s16 temp_r30;
    s16 i;
    s32 spC[] = { 23, 28 };

    temp_r29 = lbl_1_bss_6C4[spC[lbl_1_bss_29]];
    if (arg0 != 0) {
        BoardModelMotionSpeedSet(temp_r29, 1.0f);
        BoardModelAttrReset(temp_r29, 0x40000002);
        for (i = 0; i < 3; i++) {
            temp_r30 = lbl_1_bss_6C4[lbl_1_data_5DC[lbl_1_bss_29][i]];
            BoardModelMotionSpeedSet(temp_r30, 1.0f);
            BoardModelAttrReset(temp_r30, 0x40000002);
        }
    } else {
        BoardModelMotionSpeedSet(temp_r29, 0.0f);
        BoardModelAttrSet(temp_r29, 0x40000002);
        for (i = 0; i < 3; i++) {
            temp_r30 = lbl_1_bss_6C4[lbl_1_data_5DC[lbl_1_bss_29][i]];
            BoardModelMotionSpeedSet(temp_r30, 0.0f);
            BoardModelAttrSet(temp_r30, 0x40000002);
        }
    }
}

static void fn_1_586C(s32 arg0, s32 arg1) {
    lbl_1_bss_29 = arg0;
    lbl_1_bss_26 = arg1;
    BoardRollDispSet(0);
    lbl_1_bss_14 = HuPrcChildCreate(fn_1_592C, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_14, fn_1_5B2C);
    while (lbl_1_bss_14) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

static void fn_1_592C(void) {
    s16 temp_r30;
    s16 var_r28;

    lbl_1_data_5D4 = -1;
    lbl_1_data_5D8 = -1;
    BoardPlayerIdleSet(GWSystem.player_curr);
    if (lbl_1_bss_29 == 0) {
        var_r28 = lbl_1_bss_6C4[23];
    } else {
        var_r28 = lbl_1_bss_6C4[28];
    }
    BoardCameraTargetModelSet(var_r28);
    BoardCameraOffsetSet(0.0f, 0.0f, 0.0f);
    fn_1_5D08();
    while (!fn_1_5CD0()) {
        HuPrcVSleep();
    }
    fn_1_5B40();
    fn_1_5694(1);
    BoardCameraTargetPlayerSet(GWSystem.player_curr);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    HuPrcEnd();
}

static void fn_1_5B2C(void) {
    lbl_1_bss_14 = NULL;
}

static void fn_1_5B40(void) {
    s16 spC[] = { 27, 32 };
    s16 temp_r30;
    s32 temp_r31;
    float sp8;
    float temp_f31;

    temp_r31 = lbl_1_bss_0->unk01[lbl_1_bss_29];
    lbl_1_bss_0->unk01[lbl_1_bss_29] ^= 1;
    temp_r30 = lbl_1_bss_6C4[spC[lbl_1_bss_29]];
    sp8 = lbl_1_data_610[lbl_1_bss_29][temp_r31];
    temp_f31 = lbl_1_data_610[lbl_1_bss_29][temp_r31 ^ 1];
    HuAudFXPlay(0x403);
    while (TRUE) {
        HuPrcVSleep();
        if (BoardDAngleCalcRange(&sp8, temp_f31, 3.0f) != 0) {
            break;
        }
        BoardModelRotSet(temp_r30, 0.0f, sp8, 0.0f);
    }
}

static BOOL fn_1_5CD0(void) {
    return lbl_1_bss_18 ? FALSE : TRUE;
}

static void fn_1_5D08(void) {
    Bss18Work *temp_r31;
    float var_f30;
    float var_f31;
    s16 var_r28;
    s16 var_r25;
    s32 i;

    if (lbl_1_bss_29 == 0) {
        var_r28 = lbl_1_bss_6C4[23];
    } else {
        var_r28 = lbl_1_bss_6C4[28];
    }
    while (TRUE) {
        var_f30 = BoardModelMotionTimeGet(var_r28);
        if (var_f30 >= 209.0f && var_f30 <= 211.0f) {
            break;
        }
        if (var_f30 >= 129.0f && var_f30 <= 131.0f) {
            break;
        }
        if (var_f30 >= 49.0f && var_f30 <= 51.0f) {
            break;
        }
        HuPrcVSleep();
    }
    var_f31 = 1.0f;
    while (var_f31 > 0.01f) {
        var_f31 *= 0.9f;
        if (var_f31 <= 0.01f) {
            var_f31 = 0.0f;
        }
        BoardModelMotionSpeedSet(var_r28, var_f31);
        for (i = 0; i < 3; i++) {
            var_r25 = lbl_1_bss_6C4[lbl_1_data_5DC[lbl_1_bss_29][i]];
            BoardModelMotionSpeedSet(var_r25, var_f31);
        }
        HuPrcVSleep();
    }
    fn_1_5694(0);
    lbl_1_bss_18 = omAddObjEx(boardObjMan, 0x103, 0, 0, -1, fn_1_6098);
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_18, Bss18Work);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk01 = 0;
    temp_r31->unk02 = 0;
    temp_r31->unk00_field2 = 0;
    temp_r31->unk04 = var_r28;
    if (BoardPlayerSizeGet(GWSystem.player_curr) == 2) {
        temp_r31->unk00_field3 = 1;
    } else {
        temp_r31->unk00_field3 = 0;
    }
}

static void fn_1_6098(omObjData *arg0) {
    Bss18Work *temp_r31 = OM_GET_WORK_PTR(arg0, Bss18Work);
    s32 temp_r0;

    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        lbl_1_bss_18 = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r31->unk02 != 0) {
        temp_r31->unk02--;
        return;
    }
    switch (temp_r31->unk00_field1) {
        case 0:
            fn_1_6194(temp_r31, arg0);
            break;
        case 2:
            fn_1_63F0(temp_r31, arg0);
            break;
        case 3:
            fn_1_6BC0(temp_r31, arg0);
            break;
        case 1:
            fn_1_6FB4(temp_r31, arg0);
            break;
    }
}

static void fn_1_6194(Bss18Work *arg0, omObjData *arg1) {
    Mtx sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    float var_f30;
    s32 var_r28;
    s32 i;

    BoardPlayerPosGet(GWSystem.player_curr, &sp20);
    var_f30 = 1000000.0f;
    for (i = 0; i < 3; i++) {
        Hu3DModelObjPosGet(BoardModelIDGet(arg0->unk04), lbl_1_data_604[i], &sp8);
        temp_f31 = PSVECSquareDistance(&sp8, &sp20);
        if (temp_f31 < var_f30) {
            var_f30 = temp_f31;
            lbl_1_bss_28 = i;
            sp2C = sp8;
        }
    }
    Hu3DModelObjMtxGet(BoardModelIDGet(arg0->unk04), lbl_1_data_604[lbl_1_bss_28], sp38);
    Hu3DMtxRotGet(&sp38, &sp14);
    sp14.y = 180.0f;
    PSVECSubtract(&sp2C, &sp20, &sp8);
    arg1->trans.x = sp8.x / 25.0f;
    arg1->trans.z = sp8.z / 25.0f;
    var_r28 = BoardPlayerRotYGet(GWSystem.player_curr);
    arg1->trans.y = BoardDAngleCalc(sp14.y - var_r28) / 25.0f;
    arg1->scale.x = sp2C.x;
    arg1->scale.y = sp2C.y;
    arg1->scale.z = sp2C.z;
    BoardPlayerMotionShiftSet(GWSystem.player_curr, 4, 15.0f, 5.0f, 0);
    arg0->unk00_field1 = 2;
    arg0->unk01 = 0;
}

static void fn_1_63F0(Bss18Work *arg0, omObjData *arg1) {
    Vec sp10;
    float temp_f29;
    float var_f27;
    float var_f28;
    s16 var_r24;

    if (arg0->unk01 >= 55) {
        BoardPlayerRotSet(GWSystem.player_curr, 0.0f, 0.0f, 0.0f);
        BoardPlayerIdleSet(GWSystem.player_curr);
        if (GWPlayer[GWSystem.player_curr].bowser_suit) {
            BoardModelHookSet(arg0->unk04, lbl_1_data_604[lbl_1_bss_28], BoardBowserSuitModelGet());
        } else {
            BoardModelHookSet(arg0->unk04, lbl_1_data_604[lbl_1_bss_28], BoardPlayerModelGet(GWSystem.player_curr));
        }
        var_r24 = lbl_1_bss_6C4[lbl_1_data_5DC[lbl_1_bss_29][lbl_1_bss_28]];
        if (arg0->unk00_field3 != 0) {
            BoardModelScaleSet(var_r24, 1.0f, 0.1f, 1.0f);
        }
        fn_1_5694(1);
        lbl_1_data_5D4 = HuAudFXPlay(0x410);
        arg0->unk01 = 0;
        arg0->unk00_field1 = 1;
        return;
    }
    if (arg0->unk01 == 25) {
        BoardPlayerPosSet(GWSystem.player_curr, arg1->scale.x, arg1->scale.y, arg1->scale.z);
        BoardPlayerMotionShiftSet(GWSystem.player_curr, 5, 0.0f, 8.0f, 0);
    }
    if (arg0->unk01 < 25) {
        OSu8tof32(&arg0->unk01, &temp_f29);
        BoardPlayerPosGet(GWSystem.player_curr, &sp10);
        sp10.x += arg1->trans.x;
        sp10.z += arg1->trans.z;
        sp10.y += 15.0f + -0.08166667f * temp_f29 * temp_f29;
        if (sp10.y <= arg1->scale.y) {
            sp10.y = arg1->scale.y;
        }
        var_f27 = arg1->trans.y + BoardPlayerRotYGet(GWSystem.player_curr);
        BoardPlayerRotYSet(GWSystem.player_curr, var_f27);
        BoardPlayerPosSetV(GWSystem.player_curr, &sp10);
        if (arg0->unk01 > 12 && arg0->unk00_field3 != 0) {
            if (lbl_1_data_5D8 == -1) {
                lbl_1_data_5D8 = HuAudFXPlay(0x411);
            }
            OSu8tof32(&arg0->unk01, &temp_f29);
            temp_f29 -= 12.0f;
            temp_f29 = 90.0f * (temp_f29 / 12.5f);
            var_f28 = cosd(temp_f29);
            if (var_f28 < 0.1f) {
                var_f28 = 0.1f;
            }
            var_r24 = lbl_1_bss_6C4[lbl_1_data_5DC[lbl_1_bss_29][lbl_1_bss_28]];
            BoardModelScaleSet(var_r24, 1.0f, var_f28, 1.0f);
        }
    }
    arg0->unk01++;
}

static void fn_1_6A14(Bss18Work *arg0, omObjData *arg1) {
    Vec sp20;
    Vec sp14;
    Vec sp8;

    BoardModelHookObjReset(arg0->unk04, lbl_1_data_604[lbl_1_bss_28]);
    Hu3DModelObjPosGet(BoardModelIDGet(arg0->unk04), lbl_1_data_604[lbl_1_bss_28], &sp14);
    BoardPlayerPosSetV(GWSystem.player_curr, &sp14);
    BoardSpacePosGet(0, lbl_1_bss_24, &sp20);
    PSVECSubtract(&sp20, &sp14, &sp8);
    arg1->trans.x = sp8.x / 25.0f;
    arg1->trans.z = sp8.z / 25.0f;
    arg1->scale.x = sp20.x;
    arg1->scale.y = sp20.y;
    arg1->scale.z = sp20.z;
    BoardPlayerMotionShiftSet(GWSystem.player_curr, 4, 15.0f, 5.0f, 0);
    BoardPlayerRotYSet(GWSystem.player_curr, atan2d(sp8.x, sp8.z));
    arg0->unk00_field1 = 3;
    arg0->unk01 = 0;
}

static void fn_1_6BC0(Bss18Work *arg0, omObjData *arg1) {
    Vec sp14;
    Vec sp8;
    float var_f28;
    float temp_f29;
    s16 var_r27;

    if (arg0->unk01 >= 55) {
        BoardSpacePosGet(0, lbl_1_bss_24, &sp8);
        GWPlayer[GWSystem.player_curr].space_curr = lbl_1_bss_24;
        BoardPlayerPosSetV(GWSystem.player_curr, &sp8);
        BoardPlayerIdleSet(GWSystem.player_curr);
        var_r27 = lbl_1_bss_6C4[lbl_1_data_5DC[lbl_1_bss_29][lbl_1_bss_28]];
        if (arg0->unk00_field3 != 0) {
            BoardModelScaleSet(var_r27, 1.0f, 1.0f, 1.0f);
        }
        arg0->unk00_field0 = 1;
    }
    if (arg0->unk01 == 25) {
        BoardPlayerPosSet(GWSystem.player_curr, arg1->scale.x, arg1->scale.y, arg1->scale.z);
        BoardPlayerMotionShiftSet(GWSystem.player_curr, 5, 0.0f, 8.0f, 0);
    }
    if (arg0->unk01 < 25) {
        OSu8tof32(&arg0->unk01, &temp_f29);
        BoardPlayerPosGet(GWSystem.player_curr, &sp14);
        sp14.x += arg1->trans.x;
        sp14.z += arg1->trans.z;
        sp14.y += 15.0f + -0.08166667f * temp_f29 * temp_f29;
        if (sp14.y <= arg1->scale.y) {
            sp14.y = arg1->scale.y;
        }
        BoardPlayerPosSetV(GWSystem.player_curr, &sp14);
        if (arg0->unk01 > 12 && arg0->unk00_field3 != 0) {
            OSu8tof32(&arg0->unk01, &temp_f29);
            temp_f29 -= 12.0f;
            temp_f29 = 90.0f * (temp_f29 / 12.5f);
            var_f28 = sind(temp_f29);
            if (var_f28 < 0.1f) {
                var_f28 = 0.1f;
            }
            var_r27 = lbl_1_bss_6C4[lbl_1_data_5DC[lbl_1_bss_29][lbl_1_bss_28]];
            BoardModelScaleSet(var_r27, 1.0f, var_f28, 1.0f);
        }
    }
    arg0->unk01++;
}

static void fn_1_6FB4(Bss18Work *arg0, omObjData *arg1) {
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float var_f31;
    BoardSpace *temp_r29;
    s16 var_r22;
    u32 temp_r3;
    s32 var_r24;
    s32 i;

    if (arg0->unk00_field2 != 0) {
        arg0->unk08 *= 0.9f;
        if (arg0->unk08 <= 0.01f) {
            arg0->unk08 = 0.0f;
            fn_1_5694(0);
            if (lbl_1_data_5D4 != -1) {
                HuAudFXStop(lbl_1_data_5D4);
                lbl_1_data_5D4 = -1;
            }
            fn_1_6A14(arg0, arg1);
        }
        BoardModelMotionSpeedSet(arg0->unk04, arg0->unk08);
        for (i = 0; i < 3; i++) {
            var_r22 = lbl_1_bss_6C4[lbl_1_data_5DC[lbl_1_bss_29][i]];
            BoardModelMotionSpeedSet(var_r22, arg0->unk08);
        }
        return;
    }
    if (lbl_1_bss_29 == 0) {
        var_r24 = lbl_1_bss_0->unk01[lbl_1_bss_29] ^ 1;
    } else {
        var_r24 = lbl_1_bss_0->unk01[lbl_1_bss_29];
    }
    temp_r29 = BoardSpaceGet(0, lbl_1_bss_26);
    lbl_1_bss_24 = -1;
    for (i = 0; i < temp_r29->link_cnt; i++) {
        if (temp_r29->link[i] != -1) {
            temp_r3 = BoardSpaceFlagGet(0, temp_r29->link[i]);
            if ((temp_r3 & 0x200) && var_r24 == 0) {
                lbl_1_bss_24 = temp_r29->link[i];
            }
            if ((temp_r3 & 0x100) && var_r24 != 0) {
                lbl_1_bss_24 = temp_r29->link[i];
            }
        }
    }
    BoardSpacePosGet(0, lbl_1_bss_24, &sp40);
    Hu3DModelObjPosGet(BoardModelIDGet(arg0->unk04), lbl_1_data_604[lbl_1_bss_28], &sp34);
    var_f31 = BoardVecDistXZCalc(&sp40, &sp34);
    if (var_f31 <= 300.0f) {
        arg0->unk00_field2 = 1;
        arg0->unk08 = 1.0f;
    }
}

static void fn_1_7528(s32 arg0, s32 arg1) {
    Vec sp30;
    Vec sp24;
    Vec sp18;
    float temp_f31;
    float temp_f30;
    s16 sp14[] = { 23, 28 };

    BoardPlayerIdleSet(GWSystem.player_curr);
    BoardSpacePosGet(0, arg1, &sp30);
    BoardModelPosGet(lbl_1_bss_6C4[23], &sp24);
    BoardModelPosGet(lbl_1_bss_6C4[28], &sp18);
    temp_f31 = PSVECDistance(&sp24, &sp30);
    temp_f30 = PSVECDistance(&sp18, &sp30);
    if (temp_f31 < temp_f30) {
        lbl_1_bss_29 = 0;
    } else {
        lbl_1_bss_29 = 1;
    }
    BoardCameraTargetModelSet(lbl_1_bss_6C4[sp14[lbl_1_bss_29]]);
    BoardCameraMotionWait();
    HuPrcSleep(42);
    fn_1_5B40();
    BoardCameraTargetPlayerSet(GWSystem.player_curr);
    BoardCameraMotionWait();
    HuPrcSleep(12);
}

static void fn_1_77EC(s32 arg0, s32 arg1) {
    lbl_1_bss_6B4 = arg0;
    lbl_1_bss_6B0 = 0;
    lbl_1_bss_8 = HuPrcChildCreate(fn_1_7894, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_8, fn_1_4FA8);
    while (lbl_1_bss_8) {
        HuPrcVSleep();
    }
}

static void fn_1_7894(void) {
    lbl_1_bss_6B1 = 1;
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_7A64();
    fn_1_45F4();
    HuPrcEnd();
}

static void fn_1_7A64(void) {
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float var_f30;
    s16 var_r20;
    s32 temp_r19;
    s32 var_r28;

    var_r28 = 0;
    lbl_1_bss_674 = lbl_1_bss_670 = 0.18f;
    lbl_1_bss_640 = 0.0f;
    lbl_1_bss_660.x = 0.0f;
    lbl_1_bss_660.y = 0.0f;
    lbl_1_bss_660.z = 0.0f;
    lbl_1_bss_6A8 = 0.0f;
    lbl_1_bss_6B3 = 0;
    lbl_1_bss_624.x = 0.0f;
    lbl_1_bss_624.z = 0.0f;
    lbl_1_bss_624.y = 1.0f;
    lbl_1_bss_66C = 0.04f;
    BoardSpaceAttrSet(0, 1);
    fn_1_97F4();
    BoardModelMotionStart(lbl_1_bss_6AE, 0, 0);
    if (lbl_1_bss_0->unk00_field0 == 0) {
        BoardModelMotionTimeSet(lbl_1_bss_6AE, lbl_1_bss_644);
        lbl_1_bss_63C = -90.0f;
        lbl_1_bss_6AC = BoardSpaceFlagPosGet(1, 0x2000, &sp34);
        var_r20 = BoardSpaceFlagSearch(1, 0x1000);
    } else {
        BoardModelMotionTimeSet(lbl_1_bss_6AE, 0.0f);
        lbl_1_bss_63C = 90.0f;
        lbl_1_bss_6AC = BoardSpaceFlagPosGet(1, 0x1000, &sp34);
        var_r20 = BoardSpaceFlagSearch(1, 0x2000);
    }
    lbl_1_bss_654 = sp34;
    BoardCameraMotionStartEx(lbl_1_bss_6C4[0], NULL, NULL, 2400.0f, -1.0f, 2);
    PSMTXRotRad(lbl_1_bss_678, 'y', MTXDegToRad(lbl_1_bss_63C));
    BoardModelMtxSet(lbl_1_bss_6C4[0], &lbl_1_bss_678);
    BoardModelRotSet(lbl_1_bss_6C4[0], 0.0f, 0.0f, 0.0f);
    fn_1_3350();
    lbl_1_bss_648 = lbl_1_bss_654;
    lbl_1_bss_618 = lbl_1_bss_654;
    lbl_1_bss_630 = lbl_1_bss_654;
    fn_1_852C();
    BoardModelMotionSpeedSet(lbl_1_bss_6AE, lbl_1_bss_670);
    BoardCameraMotionWait();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    lbl_1_bss_6B0 = 1;
    temp_r19 = HuAudFXPlay(0x412);
    while (TRUE) {
        fn_1_1990();
        fn_1_3350();
        fn_1_276C();
        BoardModelPosSetV(lbl_1_bss_6C4[0], &lbl_1_bss_654);
        BoardModelMtxSet(lbl_1_bss_6C4[0], &lbl_1_bss_678);
        if (lbl_1_bss_0->unk00_field0 == 0) {
            var_f30 = -lbl_1_bss_670;
        } else {
            var_f30 = lbl_1_bss_670;
        }
        BoardModelMotionSpeedSet(lbl_1_bss_6AE, var_f30);
        if (lbl_1_bss_0->unk00_field0 == 0) {
            if (BoardModelMotionTimeGet(lbl_1_bss_6AE) <= 20.0f && var_r28 == 0) {
                WipeColorSet(0, 0, 0);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
                var_r28 = 1;
            }
        } else {
            if (BoardModelMotionTimeGet(lbl_1_bss_6AE) >= lbl_1_bss_644 - 20.0f && var_r28 == 0) {
                WipeColorSet(0, 0, 0);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
                var_r28 = 1;
            }
        }
        if (var_r28 != 0 && WipeStatGet() == 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuAudFXStop(temp_r19);
    fn_1_98EC();
    fn_1_87AC();
    while (lbl_1_bss_C) {
        HuPrcVSleep();
    }
    PSMTXIdentity(lbl_1_bss_678);
    BoardModelMtxSet(lbl_1_bss_6C4[0], &lbl_1_bss_678);
    lbl_1_bss_660.x = 0.0f;
    lbl_1_bss_660.z = 0.0f;
    lbl_1_bss_660.y = -lbl_1_bss_63C;
    BoardModelRotSetV(lbl_1_bss_6C4[0], &lbl_1_bss_660);
    BoardSpacePosGet(1, var_r20, &sp34);
    BoardModelPosSetV(lbl_1_bss_6C4[0], &sp34);
    BoardSpaceAttrReset(0, 1);
    BoardCameraMoveSet(0);
    BoardCameraTargetPlayerSet(lbl_1_bss_6B4);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    lbl_1_bss_6B2 = 1;
}

static s8 lbl_1_data_633 = -1;

static void fn_1_852C(void) {
    BssCWork *temp_r30;
    BssCData *temp_r31;
    Vec spC;
    float temp_f31;
    s16 sp8;
    s16 var_r28;
    s16 i;
    u32 var_r27;

    lbl_1_bss_C = omAddObjEx(boardObjMan, 0x103, 0, 0, -1, fn_1_87E0);
    temp_r30 = OM_GET_WORK_PTR(lbl_1_bss_C, BssCWork);
    temp_r30->unk00_field0 = 0;
    temp_r30->unk04 = HuMemDirectMallocNum(HEAP_SYSTEM, 4 * sizeof(BssCData), MEMORY_DEFAULT_NUM);
    memset(temp_r30->unk04, 0, 4 * sizeof(BssCData));
    lbl_1_data_633 = -1;
    lbl_1_bss_1C = 0;
    for (temp_r30->unk01 = i = 0; i < 4; i++) {
        temp_r31 = &temp_r30->unk04[temp_r30->unk01];
        var_r28 = GWPlayer[i].space_curr;
        sp8 = GWPlayer[i].character;
        var_r27 = BoardSpaceFlagGet(0, var_r28);
        if (!(var_r27 & 1)) {
            temp_r31->unk00 = -1;
            continue;
        }
        temp_r31->unk00 = 0;
        temp_r31->unk01 = i;
        temp_r31->unk02 = 0;
        BoardPlayerPosGet(temp_r31->unk01, &spC);
        temp_r31->unk04 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 10), NULL, 0);
        temp_f31 = BoardModelMotionMaxTimeGet(temp_r31->unk04);
        BoardModelVisibilitySet(temp_r31->unk04, 0);
        fn_1_95F4(temp_r31);
        BoardModelMotionStart(temp_r31->unk04, 0, 0);
        BoardModelMotionSpeedSet(temp_r31->unk04, 0.0f);
        if (lbl_1_bss_0->unk00_field0 == 0) {
            temp_r31->unk08 = -0.18f;
            BoardModelMotionTimeSet(temp_r31->unk04, temp_f31);
        } else {
            temp_r31->unk08 = 0.18f;
            BoardModelMotionTimeSet(temp_r31->unk04, 0.0f);
        }
        fn_1_932C(temp_r31);
        temp_r30->unk01++;
    }
    BoardCameraMoveSet(1);
    BoardCameraTargetModelSet(lbl_1_bss_6C4[0]);
}

static void fn_1_87AC(void) {
    if (lbl_1_bss_C) {
        OM_GET_WORK_PTR(lbl_1_bss_C, BssCWork)->unk00_field0 = 1;
    }
}

static void fn_1_87E0(omObjData *arg0) {
    BssCWork *temp_r30 = OM_GET_WORK_PTR(arg0, BssCWork);
    BssCData *temp_r31;
    s32 i;

    if (temp_r30->unk00_field0 != 0 || BoardIsKill()) {
        for (i = 0; i < temp_r30->unk01; i++) {
            temp_r31 = &temp_r30->unk04[i];
        }
        HuMemDirectFree(temp_r30->unk04);
        lbl_1_bss_C = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (lbl_1_bss_6B0 == 0) {
        return;
    }
    for (i = 0; i < temp_r30->unk01; i++) {
        temp_r31 = &temp_r30->unk04[i];
        if (temp_r31->unk02 != 0) {
            temp_r31->unk02--;
        } else {
            switch (temp_r31->unk00) {
                case 0:
                    fn_1_8988(temp_r31, arg0);
                    break;
                case 1:
                    fn_1_8A50(temp_r31, arg0);
                    break;
                case 2:
                    fn_1_8B6C(temp_r31, arg0);
                    break;
                case 3:
                    fn_1_8DDC(temp_r31, arg0);
                    break;
                case 4:
                    fn_1_918C(temp_r31, arg0);
                    break;
                case 5:
                    fn_1_927C(temp_r31, arg0);
                    break;
            }
        }
    }
}

static void fn_1_8988(BssCData *arg0, omObjData *arg1) {
    Vec sp20;
    Vec sp14;
    Vec sp8;

    if (arg0->unk10 - lbl_1_bss_640 > 900.0f) {
        return;
    }
    BoardModelPosGet(*lbl_1_bss_6C4, &sp20);
    BoardPlayerPosGet(arg0->unk01, &sp14);
    PSVECSubtract(&sp20, &sp14, &sp8);
    BoardPlayerRotYSet(arg0->unk01, atan2d(sp8.x, sp8.z));
    arg0->unk00 = 1;
}

static s32 lbl_1_data_634[8] = {
    0x00000123,
    0x00000163,
    0x000001A3,
    0x000001E3,
    0x00000223,
    0x00000263,
    0x000002A3,
    0x000002E3
};

static void fn_1_8A50(BssCData *arg0, omObjData *arg1) {
    if (lbl_1_data_633 == -1) {
        BoardCameraTargetPlayerSet(arg0->unk01);
        lbl_1_data_633 = arg0->unk01;
    }
    HuAudFXPlay(lbl_1_data_634[GWPlayer[arg0->unk01].character]);
    BoardPlayerMotionStart(arg0->unk01, 9, 0);
    BoardPlayerMotionSpeedSet(arg0->unk01, 2.0f);
    arg0->unk02 = lbl_1_bss_1C * 3 + 9;
    arg0->unk00 = 2;
    lbl_1_bss_1C++;
    omVibrate(arg0->unk01, 12, 4, 2);
}

static void fn_1_8B6C(BssCData *arg0, omObjData *arg1) {
    ModelData *temp_r29;
    HsfObject *var_r30;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f30;
    float var_f31;
    s16 var_r28;

    BoardPlayerPosGet(arg0->unk01, &arg0->unk14);
    BoardModelPosGet(lbl_1_bss_6C4[0], &sp20);
    PSVECSubtract(&sp20, &arg0->unk14, &sp14);
    BoardPlayerRotYSet(arg0->unk01, -atan2d(sp14.x, sp14.z));
    BoardPlayerMotionStart(arg0->unk01, 3, 0x40000001);
    BoardPlayerMotionSpeedSet(arg0->unk01, 2.0f);
    temp_f30 = BoardModelMotionTimeGet(lbl_1_bss_6AE);
    var_r28 = BoardModelIDGet(lbl_1_bss_6AE);
    temp_r29 = &Hu3DData[var_r28];
    Hu3DMotionExec(var_r28, temp_r29->unk_08, temp_r29->unk_64, 0);
    var_r30 = Hu3DModelObjPtrGet(var_r28, "looppath-cube1");
    sp8.x = var_r30->data.curr.pos.x;
    sp8.y = var_r30->data.curr.pos.y;
    sp8.z = var_r30->data.curr.pos.z;
    var_f31 = lbl_1_bss_640;
    while (TRUE) {
        Hu3DMotionExec(var_r28, temp_r29->unk_08, temp_r29->unk_64, 0);
        var_r30 = Hu3DModelObjPtrGet(var_r28, "looppath-cube1");
        sp14.x = sp8.x - var_r30->data.curr.pos.x;
        sp14.y = sp8.y - var_r30->data.curr.pos.y;
        sp14.z = sp8.z - var_r30->data.curr.pos.z;
        var_f31 += PSVECMag(&sp14);
        if (var_f31 >= arg0->unk10) {
            break;
        }
        sp8.x = var_r30->data.curr.pos.x;
        sp8.y = var_r30->data.curr.pos.y;
        sp8.z = var_r30->data.curr.pos.z;
        temp_r29->unk_64 += arg0->unk08;
    }
    BoardModelMotionStart(arg0->unk04, 0, 0);
    BoardModelMotionTimeSet(arg0->unk04, temp_r29->unk_64);
    BoardModelMotionSpeedSet(arg0->unk04, temp_r29->unk_68);
    arg0->unk00 = 3;
    BoardModelMotionTimeSet(lbl_1_bss_6AE, temp_f30);
}

static void fn_1_8DDC(BssCData *arg0, omObjData *arg1) {
    ModelData *temp_r29;
    HsfObject *var_r30;
    Vec *var_r27;
    Vec *var_r26;
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    Mtx sp54;
    s16 var_r28;

    var_r28 = BoardModelIDGet(arg0->unk04);
    temp_r29 = &Hu3DData[var_r28];
    Hu3DMotionExec(var_r28, temp_r29->unk_08, temp_r29->unk_64, 0);
    var_r30 = Hu3DModelObjPtrGet(var_r28, "looppath-cube1");
    sp30.x = var_r30->data.curr.pos.x;
    sp30.y = var_r30->data.curr.pos.y;
    sp30.z = var_r30->data.curr.pos.z;
    PSVECSubtract(&sp30, &arg0->unk14, &sp24);
    if (fn_1_94A8(arg0) != 0) {
        BoardModelPosGet(lbl_1_bss_6C4[1], &sp18);
        PSVECSubtract(&sp18, &sp30, &sp48);
        PSVECNormalize(&sp48, &sp48);
        var_r27 = &arg0->unk14;
        var_r26 = &sp30;
        BoardMTXCalcLookAt(sp54, var_r26, &sp48, var_r27);
        PSMTXTranspose(sp54, arg0->unk20);
    } else {
        if (sp24.z != 0.0f || sp24.x != 0.0f) {
            sp3C.y = atan2d(sp24.x, sp24.z);
            sp3C.x = -atan2d(sp24.y, VECMagXZ(&sp24));
        } else {
            sp3C.x = sp3C.y = 0.0f;
        }
        PSMTXRotRad(sp54, 'x', MTXDegToRad(sp3C.x));
        PSMTXRotRad(arg0->unk20, 'y', MTXDegToRad(sp3C.y));
        PSMTXConcat(arg0->unk20, sp54, arg0->unk20);
    }
    BoardPlayerPosSetV(arg0->unk01, &sp30);
    BoardPlayerRotSet(arg0->unk01, 0.0f, 0.0f, 0.0f);
    BoardPlayerMtxSet(arg0->unk01, &arg0->unk20);
    arg0->unk14 = sp30;
    BoardSpacePosGet(0, arg0->unk06, &spC);
    if (BoardVecMaxDistXZCheck(&spC, &sp30, 200.0f)) {
        arg0->unk00 = 4;
    }
}

static void fn_1_918C(BssCData *arg0, omObjData *arg1) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 var_r30;

    PSMTXIdentity(arg0->unk20);
    var_r30 = BoardSpaceLinkFlagSearch(0, arg0->unk06, 0x40);
    BoardSpacePosGet(0, var_r30, &sp20);
    BoardPlayerPosGet(arg0->unk01, &sp14);
    BoardPlayerMtxSet(arg0->unk01, &arg0->unk20);
    PSVECSubtract(&sp20, &sp14, &sp8);
    BoardPlayerRotYSet(arg0->unk01, atan2d(-sp8.z, -sp8.x));
    BoardPlayerPosLerpStart(arg0->unk01, &sp14, &sp20, 20);
    arg0->unk00 = 5;
}

static void fn_1_927C(BssCData *arg0, omObjData *arg1) {
    s32 temp_r3;

    if (!GWPlayer[arg0->unk01].moving) {
        BoardPlayerIdleSet(arg0->unk01);
        temp_r3 = BoardSpaceLinkFlagSearch(0, arg0->unk06, 0x40);
        GWPlayer[arg0->unk01].space_curr = temp_r3;
        arg0->unk00 = -1;
        BoardPlayerMoveAwayStartCurr(temp_r3, 0);
    }
}

static void fn_1_932C(BssCData *arg0) {
    BoardSpace *temp_r30;
    BoardSpace *var_r26;
    Vec sp20[2];
    Vec sp14;
    float spC[2];
    s16 sp8[2];
    s32 var_r29;
    s32 var_r28;
    s32 i;

    for (var_r28 = i = 0; i < BoardSpaceCountGet(0); i++) {
        temp_r30 = BoardSpaceGet(0, i + 1);
        for (var_r29 = 0; var_r29 < temp_r30->link_cnt; var_r29++) {
            var_r26 = BoardSpaceGet(0, temp_r30->link[var_r29]);
            if (var_r26->flag & 0x40) {
                sp8[var_r28] = i + 1;
                BoardSpacePosGet(0, temp_r30->link[var_r29], &sp20[var_r28]);
                var_r28++;
            }
        }
        if (var_r28 >= 2) {
            break;
        }
    }
    if (lbl_1_bss_0->unk00_field0 == 0) {
        BoardSpaceFlagPosGet(0, 0x1000, &sp14);
    } else {
        BoardSpaceFlagPosGet(0, 0x2000, &sp14);
    }
    for (i = 0; i < 2; i++) {
        spC[i] = PSVECSquareDistance(&sp14, &sp20[i]);
    }
    if (spC[0] < spC[1]) {
        arg0->unk06 = sp8[0];
    } else {
        arg0->unk06 = sp8[1];
    }
}

static s32 fn_1_94A8(BssCData *arg0) {
    Vec sp14;
    s16 spC[4];
    float sp8;
    s32 var_r30;
    s32 var_r29;
    s32 var_r26;
    BoardSpace *var_r31;
    BoardSpace *var_r27;
    BoardSpace *var_r28;

    BoardPlayerPosGet(arg0->unk01, &sp14);
    var_r28 = NULL;
    var_r26 = -1;
    var_r30 = lbl_1_bss_6AC;
    sp8 = 0.0f;
    while (TRUE) {
        var_r31 = BoardSpaceGet(1, var_r30);
        if (lbl_1_bss_0->unk00_field0 == 0) {
            var_r29 = var_r31->link[0];
        } else {
            BoardSpaceLinkTargetListGet(1, var_r30, spC);
            var_r29 = spC[0];
        }
        var_r27 = BoardSpaceGet(1, var_r29);
        if (!var_r27) {
            var_r27 = var_r31;
            break;
        }
        if (BoardVecMaxDistXZCheck(&var_r31->pos, &sp14, 200.0f)) {
            if (BoardVecMaxDistXZCheck(&var_r31->pos, &sp14, 100.0f)) {
                break;
            }
            if (var_r28) {
                var_r31 = var_r28;
                break;
            } else {
                var_r28 = var_r31;
            }
        }
        var_r26 = var_r30;
        var_r30 = var_r29;
    }
    if (var_r31->flag & 8) {
        return 1;
    } else {
        return 0;
    }
}

static void fn_1_95F4(BssCData *arg0) {
    HsfObject *var_r30;
    ModelData *temp_r29;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f30;
    float var_f31;
    s16 var_r28;

    temp_f30 = BoardModelMotionMaxTimeGet(arg0->unk04);
    if (lbl_1_bss_0->unk00_field0 == 0) {
        BoardModelMotionTimeSet(arg0->unk04, temp_f30);
        BoardModelMotionSpeedSet(arg0->unk04, -0.18f);
    } else {
        BoardModelMotionTimeSet(arg0->unk04, 0.0f);
        BoardModelMotionSpeedSet(arg0->unk04, 0.18f);
    }
    BoardPlayerPosGet(arg0->unk01, &sp14);
    var_r28 = BoardModelIDGet(arg0->unk04);
    temp_r29 = &Hu3DData[var_r28];
    Hu3DMotionExec(var_r28, temp_r29->unk_08, temp_r29->unk_64, 0);
    var_r30 = Hu3DModelObjPtrGet(var_r28, "looppath-cube1");
    sp20.x = var_r30->data.curr.pos.x;
    sp20.y = var_r30->data.curr.pos.y;
    sp20.z = var_r30->data.curr.pos.z;
    var_f31 = 0.0f;
    while (TRUE) {
        Hu3DMotionExec(var_r28, temp_r29->unk_08, temp_r29->unk_64, 0);
        var_r30 = Hu3DModelObjPtrGet(var_r28, "looppath-cube1");
        sp2C.x = var_r30->data.curr.pos.x;
        sp2C.y = var_r30->data.curr.pos.y;
        sp2C.z = var_r30->data.curr.pos.z;
        PSVECSubtract(&sp2C, &sp20, &sp8);
        var_f31 += PSVECMag(&sp8);
        if (BoardVecMinDistCheck(&sp14, &sp2C, 150.0f)) {
            break;
        }
        sp20 = sp2C;
        temp_r29->unk_64 += temp_r29->unk_68;
    }
    arg0->unk10 = var_f31;
}

static void fn_1_97F4(void) {
    Bss20Work *temp_r30;
    Bss20Data *var_r31;
    s32 i;

    if (lbl_1_bss_20) {
        return;
    }
    lbl_1_bss_20 = omAddObjEx(boardObjMan, 0x101, 1, 0, -1, fn_1_9920);
    temp_r30 = OM_GET_WORK_PTR(lbl_1_bss_20, Bss20Work);
    temp_r30->unk00_field0 = 0;
    temp_r30->unk04 = HuMemDirectMallocNum(HEAP_SYSTEM, 20 * sizeof(Bss20Data), MEMORY_DEFAULT_NUM);
    var_r31 = temp_r30->unk04;
    for (i = 0; i < 20; var_r31++, i++) {
        var_r31->unk00 = -1;
        var_r31->unk02 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 7), NULL, 0);
        BoardModelVisibilitySet(var_r31->unk02, 0);
    }
}

static void fn_1_98EC(void) {
    if (lbl_1_bss_20) {
        OM_GET_WORK_PTR(lbl_1_bss_20, Bss20Work)->unk00_field0 = 1;
    }
}

static void fn_1_9920(omObjData *arg0) {
    Bss20Work *temp_r31;
    s32 i;

    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_20, Bss20Work);
    if (temp_r31->unk00_field0 != 0 || BoardIsKill()) {
        for (i = 0; i < 20; i++) {
            BoardModelKill(temp_r31->unk04[i].unk02);
        }
        HuMemDirectFree(temp_r31->unk04);
        lbl_1_bss_20 = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (lbl_1_bss_640 < 10.0f) {
        return;
    }
    if (temp_r31->unk01 != 0) {
        temp_r31->unk01--;
    } else {
        temp_r31->unk01 = 2;
        fn_1_9A24(temp_r31);
    }
    fn_1_9BBC(temp_r31);
}

static void fn_1_9A24(Bss20Work *arg0) {
    Bss20Data *temp_r31;
    Mtx sp8;
    s32 i;
    s32 j;

    if (lbl_1_bss_6B1 != 0) {
        PSMTXTrans(sp8, 0.0f, 50.0f, -100.0f);
    } else {
        PSMTXTrans(sp8, 0.0f, 70.0f, -100.0f);
    }
    PSMTXConcat(lbl_1_bss_678, sp8, sp8);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 20; j++) {
            temp_r31 = &arg0->unk04[j];
            if (temp_r31->unk00 == -1) {
                temp_r31->unk00 = 10;
                Hu3DMtxTransGet(sp8, &temp_r31->unk08);
                PSVECAdd(&lbl_1_bss_654, &temp_r31->unk08, &temp_r31->unk08);
                temp_r31->unk14.x = 0.0f;
                temp_r31->unk14.y = 0.0f;
                temp_r31->unk14.z = 0.001f;
                temp_r31->unk04 = 1.0f;
                BoardModelVisibilitySet(temp_r31->unk02, 1);
                BoardModelLayerSet(temp_r31->unk02, 2);
                BoardModelPosSetV(temp_r31->unk02, &temp_r31->unk08);
                break;
            }
        }
    }
}

static void fn_1_9BBC(Bss20Work *arg0) {
    Bss20Data *temp_r31;
    s32 i;

    for (i = 0; i < 20; i++) {
        temp_r31 = &arg0->unk04[i];
        if (temp_r31->unk00 == -1) {
            continue;
        }
        temp_r31->unk00--;
        if (temp_r31->unk00 == 0) {
            temp_r31->unk00 = -1;
            BoardModelVisibilitySet(temp_r31->unk02, 0);
        } else {
            if (temp_r31->unk00 <= 3) {
                temp_r31->unk04 = sind(30.0f * temp_r31->unk00);
            }
            PSVECAdd(&temp_r31->unk08, &temp_r31->unk14, &temp_r31->unk08);
            BoardModelMtxSet(temp_r31->unk02, &lbl_1_bss_678);
            BoardModelPosSetV(temp_r31->unk02, &temp_r31->unk08);
            BoardModelScaleSet(temp_r31->unk02, temp_r31->unk04, temp_r31->unk04, temp_r31->unk04);
        }
    }
}
