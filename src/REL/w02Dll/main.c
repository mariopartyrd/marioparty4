#include "REL/w02Dll.h"
#include "game/frand.h"

// Temporary defines
#define BOARD_ITEM_MINI           0x0
#define BOARD_ITEM_MEGA           0x1
#define BOARD_ITEM_SUPERMINI      0x2
#define BOARD_ITEM_SUPERMEGA      0x3
#define BOARD_ITEM_HAMMER         0x4
#define BOARD_ITEM_PIPE           0x5
#define BOARD_ITEM_CARD           0x6
#define BOARD_ITEM_SPARKY         0x7 
#define BOARD_ITEM_GADDLIGHT      0x8  
#define BOARD_ITEM_CHOMPCALL      0x9
#define BOARD_ITEM_SUIT           0xA
#define BOARD_ITEM_BOO            0xB
#define BOARD_ITEM_LAMP           0xC
#define BOARD_ITEM_BAG            0xD
#define BOARD_ITEM_MAX            0xE
#define BOARD_ITEM_NONE            -1

/* BSS */
s16 lbl_1_bss_30[0x10]; // Model List
s16 lbl_1_bss_2E;
s16 lbl_1_bss_2C;
Vec lbl_1_bss_20;
Vec lbl_1_bss_14;
s32* lbl_1_bss_10;
s16 lbl_1_bss_8[4]; // Item List
Process* lbl_1_bss_4;
u8* lbl_1_bss_0;

/* DATA */
static BoardMapObject lbl_1_data_0[0x10] = {
   {{2550.0f,  0.0f,  -450.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x000C)},
   {{-3150.0f, 0.0f, -1350.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x000D)},
   {{-3150.0f, 0.0f,  1650.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x000E)},
   {{-150.0f,  0.0f,   900.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x0008)},
   {{-150.0f,  0.0f,   900.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x0009)},
   {{-150.0f,  0.0f,   900.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x000A)},
   {{-150.0f,  0.0f,   900.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x000B)},
   {{1350.0f,  0.0f,  -300.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x0011)},
   {{1350.0f,  0.0f,  -300.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x0012)},
   {{1350.0f,  0.0f,  -300.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x0015)},
   {{-300.0f,  0.0f,  -900.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_W02, 0x0016)},
   {{1175.0f,  0.0f,  -125.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_BGUEST, 0x0005)},
   {{-525.0f,  0.0f,  -825.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_BGUEST, 0x0005)},
   {{-2225.0f, 0.0f, -2100.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_BGUEST, 0x0005)},
   {{1925.0f,  0.0f, -2100.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_BGUEST, 0x0005)},
   {{150.0f,   0.0f,  1650.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, DATA_MAKE_NUM(DATADIR_BGUEST, 0x0005)}
};

// Special Models
s16 lbl_1_data_280 = -1;
s16 lbl_1_data_282 = -1;
s16 lbl_1_data_284 = -1;
s16 lbl_1_data_286 = -1;

s32 lbl_1_data_288[] = {
    DATA_MAKE_NUM(DATADIR_W02, 0x0004),
    DATA_NUM_LISTEND
};
s32 lbl_1_data_290[] = {
    DATA_MAKE_NUM(DATADIR_BGUEST, 0x0009),
    DATA_MAKE_NUM(DATADIR_BGUEST, 0x0006),
    DATA_MAKE_NUM(DATADIR_BGUEST, 0x0007),
    DATA_MAKE_NUM(DATADIR_BGUEST, 0x0008),
    DATA_NUM_LISTEND,
    0x00000000 // Padding
};

/* Functions */
//Actual externs
extern void BoardMusStart(s32, s32, s32, s32);
extern void BoardAudSeqPause(s32, s32, s32);
s8 BoardComPreferItemCheck(s32, s8, s8, s8);
extern void BoardComKeySetLeft();
extern void BoardComKeySetRight();
extern void CharModelDataClose(s16);

// function is probably global. only inlined in rels?
inline s32 get_current_board(void) {
    return GWSystem.board;
}

void BoardCreate(void) {
    s32 i, boardData;
    BoardMapObject* modelTransform;

    boardData = get_current_board();
    lbl_1_bss_0 = GWSystem.board_data;
    BoardSpaceInit(DATA_MAKE_NUM(DATADIR_W02, 0x00));
    lbl_1_data_280 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x01), NULL, 0);
    fn_8006DDE8(lbl_1_data_280, -1.0f);
    BoardModelPosSet(lbl_1_data_280, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_280, 0, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_data_280, 0.1f);
    lbl_1_data_282 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x02), NULL, 0);
    fn_8006DDE8(lbl_1_data_282, -1.0f);
    BoardModelPosSet(lbl_1_data_282, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_282, 0, 0x40000001);
    lbl_1_data_284 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x03), lbl_1_data_288, 0);
    BoardModelPosSet(lbl_1_data_284, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_284, 1, 0x40000001);
    lbl_1_data_286 = BoardModelCreate(0x20005, lbl_1_data_290, 0);
    BoardModelMotionStart(lbl_1_data_286, 1, 0x40000001);
    BoardLightHookSet(fn_1_72C, fn_1_770);

    for(i = 0; i < 0x10; i++) {
        modelTransform = &lbl_1_data_0[i];
        if (modelTransform->data_num != -1) {
            if ((i == 0xB) || (i == 0xC) || (i == 0xD) || (i == 0xE) || (i == 0xF)) {
                lbl_1_bss_10 = lbl_1_data_290;
            } else {
                lbl_1_bss_10 = NULL;
            }
            lbl_1_bss_30[i] = BoardModelCreate(modelTransform->data_num, lbl_1_bss_10, 0);
            BoardModelPosSetV(lbl_1_bss_30[i], &modelTransform->pos);
            BoardModelRotSetV(lbl_1_bss_30[i], &modelTransform->rot);
            BoardModelScaleSetV(lbl_1_bss_30[i], &modelTransform->scale);
            BoardModelVisibilitySet(lbl_1_bss_30[i], 1);
            if (lbl_1_bss_10 != NULL) {
                BoardModelMotionStart(lbl_1_bss_30[i], 1, 0x40000001);
            }
        }
    }

    BoardModelAttrSet(lbl_1_bss_30[0], 0x40000002);
    BoardModelAttrSet(lbl_1_bss_30[1], 0x40000002);
    BoardModelAttrSet(lbl_1_bss_30[2], 0x40000002);
    fn_1_BC1C();
    fn_1_92C();
    BoardModelPosGet(lbl_1_bss_30[13], &lbl_1_bss_20);
    BoardModelPosGet(lbl_1_bss_30[14], &lbl_1_bss_14);
    lbl_1_bss_2E = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x10), NULL, 1);
    lbl_1_bss_2C = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x10), NULL, 1);
    fn_1_9250();
    BoardSpaceWalkEventFuncSet(fn_1_800);
    BoardSpaceWalkMiniEventFuncSet(fn_1_1128);
    BoardSpaceLandEventFuncSet(fn_1_774);
    BoardStarHostSet(lbl_1_data_284);
    BoardBooHouseHostSet(lbl_1_data_286);
    BoardLotteryHostSet(lbl_1_data_286);
    BoardShopHostSet(lbl_1_data_286);
    BoardJunctionMaskSet(0xE);
    BoardJunctionMaskSet(0x30);
}

void BoardDestroy(void) {
    /* Kill Model List */
    s32 i;
    for (i = 0; i < 0x10; i++) {
        if (lbl_1_bss_30[i] != 0) {
            BoardModelKill(lbl_1_bss_30[i]);
            lbl_1_bss_30[i] = 0;
        }
    }

    /* Kill Special Models */
    if (lbl_1_data_286 != -1) {
        BoardModelKill(lbl_1_data_286);
        lbl_1_data_286 = -1;
    }
    if (lbl_1_data_284 != -1) {
        BoardModelKill(lbl_1_data_284);
        lbl_1_data_284 = -1;
    }
    if (lbl_1_data_280 != -1) {
        BoardModelKill(lbl_1_data_280);
        lbl_1_data_280 = -1;
    }
    if (lbl_1_data_282 != -1) {
        BoardModelKill(lbl_1_data_282);
        lbl_1_data_282 = -1;
    }
    BoardSpaceDestroy();
}

void fn_1_72C(void) {
    s16 var = BoardModelIDGet(lbl_1_data_280);
    Hu3DModelLightInfoSet(var, 1);
}

void fn_1_770(void) {

}

/* Decrement current space's [UNKNOWN] flag */
s32 fn_1_774(void) {
    u32 unkFlag;
    u32 currPlayer;
    u32 currSpace;
    u32 spaceFlags;
    currPlayer = GWSystem.player_curr;
    currSpace = GWPlayer[currPlayer].space_curr;
    spaceFlags = BoardSpaceFlagGet(0, currSpace);
    //temp_r31 = (temp_r)
    unkFlag = (spaceFlags & 0x1C0) >> 6;
    if (unkFlag != 0) {
        unkFlag--;
        fn_1_93C8(unkFlag);
    }
}

/* Check if can iteract with board object? */
s32 fn_1_800(void) {
    BoardSpace* currSpace;
    s32 currPlayer;
    s32 var_r29;

    currPlayer = GWSystem.player_curr;
    currSpace = BoardSpaceGet(0, GWPlayer[currPlayer].space_curr);
    if ((currSpace->flag & 0x30) != 0) {


        // If mega mushroom state return
        if (BoardPlayerSizeGet(currPlayer) == 2) {
            return 0;
        }
        // If using the bowser suit return
        if (GWPlayer[currPlayer].bowser_suit) {
            return 0;
        }

        if ((currSpace->flag & 0x20) != 0 && (currSpace->flag & 0x10) != 0) {
            var_r29 = 2;
        } else if ((currSpace->flag & 0x20) != 0) {
            var_r29 = 1;
        } else {
            var_r29 = 0;
        }
        fn_1_394C(var_r29);
        return 1;
    }
    if ((currSpace->flag & 1) != 0) {
        fn_1_E41C();
        return 1;
    }
    return 0;
}

void fn_1_92C(void) {
    fn_1_39F4();
    fn_1_5CF8();
}

void fn_1_950(void) {

}

void fn_1_954(void) {
    HuPrcSleep(0x3C);
    BoardMusStart(1, 0x12, 0x7F, 0);
    HuPrcEnd();
}

void fn_1_990(void) {
    Vec rotation;
    Vec offset;
    Vec boardSpacePos;

    s32 textChoice;
    s32 currPlayer;
    s32 currSpace;
    s32 spaceLinkFlag;


    currPlayer = GWSystem.player_curr;
    BoardWinCreateChoice(2, MAKE_MESSID(19, 17), 4, 0);
    if (GWPlayer[currPlayer].com) {
        if (frandBool() != 0) {
            BoardComKeySetLeft();
        } else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    textChoice = BoardWinChoiceGet();
    if ((textChoice == 1) || (textChoice == -1)) {
        BoardWinCreate(2, MAKE_MESSID(19, 18), 4);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        return;
    }
    BoardAudSeqPause(0, 1, 1000);
    HuPrcChildCreate(fn_1_954, 0x2003U, 0x1000U, 0, boardMainProc);
    rotation.x = 0.0f;
    rotation.y = rotation.z = 0.0f;
    offset.y = 135.0f;
    offset.x = offset.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_30[8], &rotation, &offset, 1200.0f, 25.0f, 0x15);
    currSpace = GWPlayer[currPlayer].space_curr;
    spaceLinkFlag = BoardSpaceLinkFlagSearch(0, currSpace, 0x02000000U);
    BoardSpacePosGet(0, spaceLinkFlag, &boardSpacePos);
    BoardPlayerMoveBetween(currPlayer, currSpace, spaceLinkFlag);
    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(currPlayer, 1, 0x40000001);
    fn_1_3BF4();

    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(currPlayer, 1, 0x40000001);
}

void fn_1_C50(void) {
    Vec rotation;
    Vec offset;
    s32 currSpace;
    s32 spaceLinkFlags;
    s32 textChoice;
    s32 currPlayer;
    s32 i, j;

    currPlayer = GWSystem.player_curr;
    if (BoardPlayerItemCount((s32) currPlayer) == 3) {
        BoardWinCreate(2, MAKE_MESSID(19, 26), 4);
        BoardWinWait();
        BoardWinKill();
        HuPrcEnd();
    }
    BoardCameraTargetModelSet(lbl_1_bss_30[10]);
    BoardCameraMotionWait();

    /* Generate three random unique items where
       the first item is MINI_MUSHROOM and the
       other two are not BOWSER_SUIT or ITEM_BAG.
    */
    lbl_1_bss_8[0] = BOARD_ITEM_MINI;
    for (i = 1; i < 3;) {
        lbl_1_bss_8[i] = frandmod(BOARD_ITEM_MAX);
        if (lbl_1_bss_8[i] != BOARD_ITEM_SUIT && lbl_1_bss_8[i] != BOARD_ITEM_BAG) {
            for (j = 0; j < i; j++) {
                if (lbl_1_bss_8[i] == lbl_1_bss_8[j]) {
                    lbl_1_bss_8[i] = BOARD_ITEM_NONE;
                }
            }
            if (lbl_1_bss_8[i] != BOARD_ITEM_NONE) {
                i++;
            } 
        }
    }
    fn_1_79BC(lbl_1_bss_8);

    HuAudFXPlay(0x43);
    BoardWinCreateChoice(2, MAKE_MESSID(19, 22), 4, 0);
    if (GWPlayer[currPlayer].com) {
        if (BoardComPreferItemCheck(currPlayer, lbl_1_bss_8[0], lbl_1_bss_8[1], lbl_1_bss_8[2]) != -1) {
            BoardComKeySetLeft();
        } else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    textChoice = BoardWinChoiceGet();
    if ((textChoice == 1) || (textChoice == -1)) {
        HuAudFXPlay(0x44);
        BoardWinCreate(2, MAKE_MESSID(19, 23), 4);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        fn_1_8244(1);
        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        fn_1_5F90();
        HuPrcEnd();
    }
    rotation.x = -30.0f;
    rotation.y = rotation.z = 0.0f;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = -250.0f;
    BoardCameraMotionStartEx(lbl_1_bss_30[10], (Point3d* ) &rotation, (Point3d* ) &offset, 1500.0f, 25.0f, 0x15);
    currSpace = GWPlayer[currPlayer].space_curr;
    spaceLinkFlags = BoardSpaceLinkFlagSearch(0, currSpace, 0x02000000U);
    BoardPlayerMoveBetween(currPlayer, currSpace, spaceLinkFlags);
    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart((s32) currPlayer, 1, 0x40000001);
    BoardPlayerMotBlendSet(currPlayer, 0xB4, 0xF);
    while (BoardPlayerMotBlendCheck(currPlayer) == 0) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    fn_1_5D28();
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_8244(0);
    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    fn_1_5F90();
    BoardPlayerMotionStart((s32) currPlayer, 1, 0x40000001);
    HuPrcEnd();
}

void fn_1_1070(void) {
    BoardWinKill();
    CharModelDataClose(-1);
    lbl_1_bss_4 = 0;
}

void fn_1_10A8(void) {
    lbl_1_bss_4 = HuPrcChildCreate(fn_1_C50, 0x2003U, 0x2000U, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_4, fn_1_1070);
    while (lbl_1_bss_4) {
        HuPrcVSleep();
    }
}

s32 fn_1_1128(void) {
    u32 spaceFlags;
    s16 currSpace;
    currSpace = GWPlayer[GWSystem.player_curr].space_curr;
    spaceFlags = BoardSpaceFlagGet(0, currSpace) & 0x600000;
    BoardRollDispSet(0);

    if (spaceFlags & 0x200000) {
        fn_1_990();
    } else if (spaceFlags & 0x400000) {
        lbl_1_bss_4 = HuPrcChildCreate(fn_1_C50, 0x2003U, 0x2000U, 0, boardMainProc);
        HuPrcDestructorSet2(lbl_1_bss_4, fn_1_1070);
        while (lbl_1_bss_4) {
            HuPrcVSleep();
        }
    }

    BoardRollDispSet(1);
}

void fn_1_121C(u32 mesg) {
    BoardWinCreate(2, mesg, 4);
    BoardWinWait();
    BoardWinKill();
}

f32 const padMain = 0.0f;
