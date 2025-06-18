#include "game/board/lottery.h"
#include "game/audio.h"
#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/tutorial.h"
#include "game/board/ui.h"
#include "game/board/window.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"

#include "ext_math.h"
#include "stdlib.h"
#include <string.h>

#ifndef __MWERKS__
#include <game/board/shop.h>
#endif

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        s8 unk00_field1 : 1;
        u8 unk00_field2 : 4;
    };
    u8 unk01;
    s16 unk02;
    s16 unk04;
    char unk06[2];
    AnimData *unk08;
} TicketWork;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    s8 unk01;
    s8 unk02;
    s8 unk03;
    u8 unk04;
    char unk05[1];
    s16 unk06;
    s16 unk08;
} LotteryTicketPickWork;

static void CreateModel(void);
static void KillModel(void);
static void DestroyLottery(void);
static void ExecLottery(void);
static void DoMiniJumpUp(s32 arg0);
static void DoMiniJumpDown(s32 arg0);
static void PayEnterFee(s32 arg0);
static void ShowTicket(void);
static void SetupTicket(s32 arg0);
static void ExecBallGame(void);
static void SetBallPrize(void);
static void ExecBallPrize(void);
static void ExecScratchTicket(s32 arg0);
static void ExecScratch(void);
static void KillScratch(void);
static void ExecScratchSpr(omObjData *arg0);
static void HideScratchSpr(void);
static void InitScratchSpr(void);
static void ExecScratchPick(omObjData *arg0);
static void InitScratchPick(void);
static void InitTicketPrizes(void);
static void ExecTicketFocus(s32 arg0);
static BOOL ScratchTicketCheckDone(AnimBmpData *arg0);
static u16 TicketGetPixel(u16 arg0, u16 arg1, u16 arg2);
static s32 TicketUpdate(AnimBmpData *arg0, Vec *arg1, s32 arg2);
static void ExecCoinPrize(void);
static void ExecItemPrize(void);
static void KillCoin(void);
static void ExecPrize(void);
static void ExecLose(s32 arg0);
static void CreateLotteryWin(s32 arg0);
static void KillLotteryWin(void);

static s16 lotteryMdl[6];
static s8 coinF[12];
static s16 coinMdl[10];

static s32 lotteryMessBase;
static s16 lotterySpace;
static s8 currPrize;
s8 lbl_801D401B;
static s8 comLotteryType;
static s8 comLotteryWinType;
static u8 comInputPos;
static s32 handUpdateF;
static omObjData *lotteryTicketPickObj;
static s8 (*comInputDrawP)[2];
static Process *lotteryProc;

static s16 hostMdl = -1;
static s16 lotteryMot[4] = { -1, -1, -1, -1 };
static s16 lotterySpr = -1;
static s16 lotteryInstWin = -1;
static s16 gripMdl[2] = { 0, 0 };
static s16 turnMot = -1;
static s16 ballMdl[4] = { -1, -1, -1, -1 };
static s16 loseMot = -1;
static s16 ticketSprGrp = -1;

static s8 comInputDraw1[][2] = { { 0x0B, 0xF8 }, { 0x2B, 0xDD }, { 0x2A, 0xDC }, { 0x2B, 0xDC }, { 0x2B, 0xDC }, { 0x29, 0xDB }, { 0x24, 0xD6 },
    { 0x02, 0xE8 }, { 0x00, 0x00 }, { 0xFC, 0x02 }, { 0xD8, 0x27 }, { 0xD8, 0x28 }, { 0xD8, 0x28 }, { 0xD8, 0x27 }, { 0xDA, 0x29 }, { 0xDE, 0x2C },
    { 0xE4, 0x31 }, { 0xF0, 0x3A }, { 0x00, 0x3C }, { 0x06, 0x3A }, { 0x1B, 0x32 }, { 0x23, 0x2B }, { 0x24, 0x2A }, { 0x25, 0x29 }, { 0x26, 0x29 },
    { 0x28, 0x27 }, { 0x28, 0x27 }, { 0x28, 0x26 }, { 0x28, 0x26 }, { 0x2E, 0x20 }, { 0x39, 0x11 }, { 0x48, 0x00 }, { 0x48, 0x00 }, { 0x35, 0xEA },
    { 0x29, 0xDB }, { 0x24, 0xD5 }, { 0x17, 0xCB }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0xEB, 0xCA },
    { 0xD6, 0xDB }, { 0xD6, 0xDB }, { 0xD4, 0xDE }, { 0xD1, 0xE2 }, { 0xC4, 0xF2 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 },
    { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xC1, 0x0B }, { 0xC6, 0x10 }, { 0xC9, 0x14 }, { 0xCB, 0x16 }, { 0xCB, 0x17 }, { 0xCE, 0x1A },
    { 0xD1, 0x1E }, { 0xD5, 0x23 }, { 0xD4, 0x22 }, { 0xDB, 0x29 }, { 0xF5, 0x3E }, { 0x00, 0x48 }, { 0x00, 0x42 }, { 0x0D, 0x3D }, { 0x24, 0x2A },
    { 0x29, 0x26 }, { 0x29, 0x26 }, { 0x29, 0x25 }, { 0x2D, 0x21 }, { 0x34, 0x18 }, { 0x40, 0x09 }, { 0x48, 0x00 }, { 0x48, 0x00 }, { 0x43, 0xFA },
    { 0x33, 0xE6 }, { 0x29, 0xDB }, { 0x1B, 0xCF }, { 0x05, 0xBD }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0xFB, 0xBD }, { 0xDD, 0xD5 },
    { 0xD6, 0xDC }, { 0xD6, 0xDC }, { 0xD4, 0xDE }, { 0xCB, 0xE9 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xC5, 0x0F }, { 0xD0, 0x1D },
    { 0xD5, 0x23 }, { 0xDC, 0x2A }, { 0xF0, 0x3B }, { 0x00, 0x3D }, { 0x08, 0x3F }, { 0x15, 0x36 }, { 0x24, 0x2A }, { 0x29, 0x26 }, { 0x2A, 0x24 },
    { 0x30, 0x1C }, { 0x3B, 0x0F }, { 0x48, 0x00 }, { 0x48, 0x00 }, { 0x3E, 0xF4 }, { 0x2D, 0xE0 }, { 0x22, 0xD4 }, { 0x02, 0xBB }, { 0x00, 0xB8 },
    { 0xFB, 0xBD }, { 0xD9, 0xD8 }, { 0xD4, 0xDE }, { 0x7F, 0x7F } };

static s8 comInputDraw2[][2] = { { 0x07, 0x00 }, { 0x1F, 0x00 }, { 0x3A, 0x00 }, { 0x48, 0x00 }, { 0x48, 0x00 }, { 0x48, 0x00 }, { 0x48, 0x00 },
    { 0x48, 0x00 }, { 0x43, 0xFA }, { 0x35, 0xEA }, { 0x2A, 0xDB }, { 0x1A, 0xCE }, { 0x00, 0xB9 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xB8 },
    { 0x00, 0xBA }, { 0xE9, 0xCC }, { 0xD5, 0xDD }, { 0xD4, 0xDE }, { 0xD4, 0xDE }, { 0xD0, 0xE3 }, { 0xBD, 0xFB }, { 0xB8, 0x00 }, { 0xB8, 0x00 },
    { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xBC, 0x03 }, { 0xC2, 0x0C }, { 0xCB, 0x17 }, { 0xD5, 0x23 },
    { 0xD8, 0x27 }, { 0xF0, 0x3A }, { 0x00, 0x43 }, { 0x18, 0x34 }, { 0x29, 0x26 }, { 0x29, 0x26 }, { 0x29, 0x26 }, { 0x29, 0x25 }, { 0x29, 0x26 },
    { 0x29, 0x25 }, { 0x29, 0x25 }, { 0x2C, 0x22 }, { 0x31, 0x1B }, { 0x39, 0x12 }, { 0x47, 0x00 }, { 0x48, 0x00 }, { 0x48, 0x00 }, { 0x37, 0xEC },
    { 0x26, 0xD7 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0xFB, 0xBD }, { 0xE5, 0xCE },
    { 0xD6, 0xDC }, { 0xD6, 0xDC }, { 0xD6, 0xDC }, { 0xD5, 0xDD }, { 0xD2, 0xE0 }, { 0xCC, 0xE8 }, { 0xC4, 0xF2 }, { 0xBE, 0xFA }, { 0xB8, 0x00 },
    { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xB8, 0x00 },
    { 0xB8, 0x00 }, { 0xC7, 0x12 }, { 0xD8, 0x27 }, { 0xF6, 0x3E }, { 0x00, 0x47 }, { 0x00, 0x44 }, { 0x05, 0x42 }, { 0x16, 0x35 }, { 0x28, 0x27 },
    { 0x29, 0x26 }, { 0x29, 0x26 }, { 0x29, 0x26 }, { 0x29, 0x26 }, { 0x7F, 0x7F } };

static s8 comInputBall[][2] = { { 0xE5, 0x00 }, { 0xC0, 0x03 }, { 0xBC, 0x04 }, { 0xBC, 0x03 }, { 0xBF, 0x07 }, { 0xC3, 0x0C }, { 0xCB, 0x17 },
    { 0xD5, 0x24 }, { 0xDE, 0x2C }, { 0xF9, 0x3E }, { 0x00, 0x48 }, { 0x00, 0x45 }, { 0x06, 0x40 }, { 0x21, 0x2C }, { 0x28, 0x27 }, { 0x28, 0x26 },
    { 0x29, 0x25 }, { 0x30, 0x1D }, { 0x43, 0x05 }, { 0x48, 0x00 }, { 0x33, 0xE7 }, { 0x24, 0xD6 }, { 0x07, 0xBF }, { 0x00, 0xB8 }, { 0x00, 0xB8 },
    { 0xE4, 0xCF }, { 0xD4, 0xDE }, { 0xC6, 0xF0 }, { 0xB8, 0x00 }, { 0xC7, 0x11 }, { 0xD2, 0x20 }, { 0xD5, 0x24 }, { 0xD6, 0x25 }, { 0xD8, 0x27 },
    { 0xE1, 0x2E }, { 0x00, 0x43 }, { 0x00, 0x48 }, { 0x00, 0x44 }, { 0x1D, 0x30 }, { 0x28, 0x27 }, { 0x28, 0x27 }, { 0x2C, 0x22 }, { 0x39, 0x12 },
    { 0x48, 0x00 }, { 0x34, 0xE8 }, { 0x23, 0xD5 }, { 0x0A, 0xC1 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0xF4, 0xC3 }, { 0xD4, 0xDE }, { 0xC3, 0xF4 },
    { 0xB8, 0x00 }, { 0xC6, 0x10 }, { 0xD3, 0x21 }, { 0xD6, 0x25 }, { 0xD8, 0x27 }, { 0xDF, 0x2D }, { 0xEA, 0x36 }, { 0x00, 0x48 }, { 0x00, 0x48 },
    { 0x00, 0x48 }, { 0x17, 0x35 }, { 0x28, 0x27 }, { 0x29, 0x25 }, { 0x33, 0x19 }, { 0x48, 0x00 }, { 0x48, 0x00 }, { 0x34, 0xE8 }, { 0x23, 0xD5 },
    { 0x00, 0xB9 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0xFA, 0xBE }, { 0xD4, 0xDE }, { 0xC8, 0xED }, { 0xB8, 0x00 }, { 0xB8, 0x00 }, { 0xC0, 0x09 },
    { 0xD0, 0x1C }, { 0xD6, 0x24 }, { 0xDC, 0x2A }, { 0xED, 0x38 }, { 0x00, 0x48 }, { 0x00, 0x48 }, { 0x00, 0x48 }, { 0x1B, 0x31 }, { 0x28, 0x27 },
    { 0x29, 0x26 }, { 0x2D, 0x21 }, { 0x3D, 0x0C }, { 0x48, 0x00 }, { 0x33, 0xE7 }, { 0x20, 0xD3 }, { 0x00, 0xB8 }, { 0x00, 0xB8 }, { 0x00, 0xBB },
    { 0xDB, 0xD7 }, { 0xD4, 0xDE }, { 0xD3, 0xDF }, { 0xBB, 0xFD }, { 0xB8, 0x00 }, { 0x7F, 0x7F } };

void BoardLotteryHostSet(s16 arg0)
{
    hostMdl = arg0;
}

s16 BoardLotteryHostGet(void)
{
    return hostMdl;
}

void BoardLotteryExec(void)
{
    if (BoardPlayerSizeGet(GWSystem.player_curr) == 2) {
        return;
    }
    BoardRollDispSet(0);
    lotteryProc = HuPrcChildCreate(ExecLottery, 0x2003, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(lotteryProc, DestroyLottery);
    while (lotteryProc) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

void BoardLotteryInit(void)
{
    Vec sp14;
    Vec sp8;
    s32 i;

    for (i = 0; i < 5; i++) {
        lotteryMdl[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        lotteryMot[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        ballMdl[i] = -1;
    }
    turnMot = -1;
    loseMot = -1;
    if (GWBoardGet() != BOARD_ID_EXTRA2) {
        BoardModelVisibilitySet(BoardLotteryHostGet(), 0);
        BoardSpaceLinkTransformGet(0x10000000, &sp14, &sp8, NULL);
        lotteryMdl[0] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BKUJIYA, 0), NULL, 0);
        BoardModelMotionStart(lotteryMdl[0], 0, 0);
        BoardModelMotionSpeedSet(lotteryMdl[0], 0.0f);
        BoardModelPosSetV(lotteryMdl[0], &sp14);
        BoardModelRotSetV(lotteryMdl[0], &sp8);
        HuDataDirClose(DATA_MAKE_NUM(DATADIR_BKUJIYA, 0));
    }
}

static void CreateModel(void)
{
    s32 i;
    s32 sp10[4] = { DATA_MAKE_NUM(DATADIR_BKUJIYA, 5), DATA_MAKE_NUM(DATADIR_BKUJIYA, 6), DATA_MAKE_NUM(DATADIR_BKUJIYA, 7),
        DATA_MAKE_NUM(DATADIR_BKUJIYA, 8) };
    s32 sp8[2] = { DATA_MAKE_NUM(DATADIR_BKUJIYA, 3), DATA_MAKE_NUM(DATADIR_BKUJIYA, 4) };
    s32 sp20[9][4] = {
        { DATA_MAKE_NUM(DATADIR_BGUEST, 1), DATA_MAKE_NUM(DATADIR_BGUEST, 2), DATA_MAKE_NUM(DATADIR_BGUEST, 3), DATA_MAKE_NUM(DATADIR_BGUEST, 4) },
        { DATA_MAKE_NUM(DATADIR_BGUEST, 9), DATA_MAKE_NUM(DATADIR_BGUEST, 10), DATA_MAKE_NUM(DATADIR_BGUEST, 11), DATA_MAKE_NUM(DATADIR_BGUEST, 12) },
        { DATA_MAKE_NUM(DATADIR_BGUEST, 14), DATA_MAKE_NUM(DATADIR_BGUEST, 15), DATA_MAKE_NUM(DATADIR_BGUEST, 16),
            DATA_MAKE_NUM(DATADIR_BGUEST, 17) },
        { DATA_MAKE_NUM(DATADIR_BGUEST, 24), DATA_MAKE_NUM(DATADIR_BGUEST, 25), DATA_MAKE_NUM(DATADIR_BGUEST, 26),
            DATA_MAKE_NUM(DATADIR_BGUEST, 27) },
        { DATA_MAKE_NUM(DATADIR_BGUEST, 29), DATA_MAKE_NUM(DATADIR_BGUEST, 30), DATA_MAKE_NUM(DATADIR_BGUEST, 31),
            DATA_MAKE_NUM(DATADIR_BGUEST, 32) },
        { DATA_MAKE_NUM(DATADIR_BGUEST, 34), DATA_MAKE_NUM(DATADIR_BGUEST, 35), DATA_MAKE_NUM(DATADIR_BGUEST, 36),
            DATA_MAKE_NUM(DATADIR_BGUEST, 37) },
        { DATA_MAKE_NUM(DATADIR_BGUEST, 14), DATA_MAKE_NUM(DATADIR_BGUEST, 15), DATA_MAKE_NUM(DATADIR_BGUEST, 16),
            DATA_MAKE_NUM(DATADIR_BGUEST, 17) },
        { DATA_MAKE_NUM(DATADIR_BGUEST, 42), DATA_MAKE_NUM(DATADIR_BGUEST, 43), DATA_MAKE_NUM(DATADIR_BGUEST, 44),
            DATA_MAKE_NUM(DATADIR_BGUEST, 45) },
        { DATA_MAKE_NUM(DATADIR_BGUEST, 42), DATA_MAKE_NUM(DATADIR_BGUEST, 43), DATA_MAKE_NUM(DATADIR_BGUEST, 44), DATA_MAKE_NUM(DATADIR_BGUEST, 45) }
    };

    lotteryMdl[1] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BKUJIYA, 1), NULL, 0);
    fn_8006DDE8(lotteryMdl[1], -1.0f);
    BoardModelMotionSpeedSet(lotteryMdl[1], 0.0f);
    lotteryMdl[2] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BKUJIYA, 2), NULL, 0);
    BoardModelVisibilitySet(lotteryMdl[2], 0);
    fn_8006DDE8(lotteryMdl[2], -1.0f);
    BoardModelMotionStart(lotteryMdl[2], 0, 0);
    BoardModelMotionSpeedSet(lotteryMdl[2], 0.0f);
    for (i = 0; i < 4; i++) {
        ballMdl[i] = BoardModelCreate(sp10[i], NULL, 0);
        BoardModelVisibilitySet(ballMdl[i], 0);
        fn_8006DDE8(ballMdl[i], -1.0f);
    }
    for (i = 0; i < 2; i++) {
        gripMdl[i] = BoardModelCreate(sp8[i], NULL, 0);
        BoardModelVisibilitySet(gripMdl[i], 0);
        fn_8006DDE8(gripMdl[i], -1.0f);
        BoardModelMotionSpeedSet(gripMdl[i], 0.0f);
    }
    lotteryMdl[3] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BKUJIYA, 17), NULL, 0);
    BoardModelVisibilitySet(lotteryMdl[3], 0);
    fn_8006DDE8(lotteryMdl[3], -1.0f);
    BoardModelPosSet(BoardLotteryHostGet(), 0.0f, 0.0f, 0.0f);
    BoardModelVisibilitySet(BoardLotteryHostGet(), 1);
    for (i = 0; i < 4; i++) {
        lotteryMot[i] = BoardModelMotionCreate(BoardLotteryHostGet(), sp20[GWBoardGet()][i]);
    }
    BoardModelMotionStart(BoardLotteryHostGet(), lotteryMot[0], 0x40000001);
    BoardModelHookSet(lotteryMdl[0], "toto_heyhoo", BoardLotteryHostGet());
    BoardModelHookSet(lotteryMdl[0], "toto_gara", lotteryMdl[1]);
    BoardModelHookSet(lotteryMdl[0], "toto_efe", lotteryMdl[2]);
    BoardModelHookSet(lotteryMdl[0], "toto_chibidai", lotteryMdl[3]);
    BoardModelHookSet(lotteryMdl[1], "toto_grip", gripMdl[0]);
    BoardModelHookSet(lotteryMdl[1], "toto_grip1", gripMdl[1]);
}

static void KillModel(void)
{
    s32 i;

    if (lotteryMdl[1] != -1) {
        BoardModelHookReset(lotteryMdl[0]);
    }
    BoardModelMotionStart(BoardLotteryHostGet(), 1, 0x40000001);
    if (turnMot != -1) {
        BoardPlayerMotionKill(GWSystem.player_curr, turnMot);
        turnMot = -1;
    }
    for (i = 0; i < 4; i++) {
        if (lotteryMot[i] != -1) {
            BoardModelMotionKill(BoardLotteryHostGet(), lotteryMot[i]);
            lotteryMot[i] = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (ballMdl[i] != -1) {
            BoardModelKill(ballMdl[i]);
            ballMdl[i] = -1;
        }
    }
    for (i = 0; i < 2; i++) {
        if (gripMdl[i] != -1) {
            BoardModelKill(gripMdl[i]);
            gripMdl[i] = -1;
        }
    }
    for (i = 0; i < 5; i++) {
        if (i != 0 && lotteryMdl[i] != -1) {
            BoardModelKill(lotteryMdl[i]);
            lotteryMdl[i] = -1;
        }
    }
    BoardModelVisibilitySet(BoardLotteryHostGet(), 0);
}

void BoardLotteryKill(void)
{
    if (lotteryProc) {
        HuPrcKill(lotteryProc);
    }
    if (lotteryMdl[0] != -1) {
        BoardModelKill(lotteryMdl[0]);
        lotteryMdl[0] = -1;
    }
}

static void DestroyLottery(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i != GWSystem.player_curr) {
            BoardPlayerMotBlendSet(i, 0, 7);
        }
    }
    if (loseMot != -1) {
        BoardPlayerMotionKill(GWSystem.player_curr, loseMot);
        loseMot = -1;
    }
    KillLotteryWin();
    BoardConfettiKill();
    BoardWinKill();
    KillScratch();
    KillCoin();
    HuDataDirClose(DATA_MAKE_NUM(DATADIR_BKUJIYA, 0));
    lotteryProc = NULL;
}

static void ExecLottery(void)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s16 temp_r26;
    s16 temp_r28;
    u32 var_r25;
    s32 var_r27;
    s32 temp_r31;
    s32 i;
    s32 temp_r29;

    switch (GWBoardGet()) {
        case BOARD_ID_MAIN1:
            lotteryMessBase = MAKE_MESSID(6, 2);
            break;
        case BOARD_ID_MAIN2:
            lotteryMessBase = MAKE_MESSID(6, 15);
            break;
        case BOARD_ID_MAIN3:
            lotteryMessBase = MAKE_MESSID(6, 28);
            break;
        case BOARD_ID_MAIN4:
            lotteryMessBase = MAKE_MESSID(6, 41);
            break;
        case BOARD_ID_MAIN5:
            lotteryMessBase = MAKE_MESSID(6, 54);
            break;
        case BOARD_ID_MAIN6:
            lotteryMessBase = MAKE_MESSID(6, 67);
            break;
        case BOARD_ID_TUTORIAL:
            lotteryMessBase = MAKE_MESSID(6, 2);
            break;
        case BOARD_ID_EXTRA1:
            lotteryMessBase = MAKE_MESSID(6, 82);
            break;
        case BOARD_ID_EXTRA2:
            lotteryMessBase = MAKE_MESSID(6, 82);
            break;
    }
    temp_r29 = BoardDataDirReadAsync(DATADIR_BKUJIYA);
    temp_r31 = GWSystem.player_curr;
    temp_r28 = GWPlayer[temp_r31].space_curr;
    BoardPlayerIdleSet(temp_r31);
    BoardWinCreateChoice(0, MAKE_MESSID(6, 0), -1, 0);
    if (GWPlayer[temp_r31].com) {
        if (BoardPlayerCoinsGet(temp_r31) >= 5) {
            BoardComKeySetLeft();
        }
        else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    if (BoardWinChoiceGet() != 0) {
        if (temp_r29 != -1) {
            BoardDataAsyncWait(temp_r29);
        }
        HuPrcEnd();
    }
    if (BoardPlayerCoinsGet(temp_r31) < 5) {
        BoardWinCreate(0, MAKE_MESSID(6, 1), -1);
        BoardWinWait();
        BoardWinKill();
        if (temp_r29 != -1) {
            BoardDataAsyncWait(temp_r29);
        }
        HuPrcEnd();
    }
    BoardWinKill();
    if (temp_r29 != -1) {
        BoardDataAsyncWait(temp_r29);
    }
    BoardModelMotionStart(BoardLotteryHostGet(), 1, 0x40000001);
    BoardAudSeqPause(0, 1, 1000);
    CreateModel();
    BoardStatusShowSetAll(0);
    lotterySpace = BoardSpaceLinkFlagSearch(0, temp_r28, 0x02000000);
    BoardSpacePosGet(0, temp_r28, &sp38);
    BoardSpacePosGet(0, lotterySpace, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    if (GWBoardGet() == BOARD_ID_MAIN3 || GWBoardGet() == BOARD_ID_MAIN4) {
        VECScale(&sp20, &sp20, 0.95f);
        VECAdd(&sp20, &sp38, &sp2C);
    }
    temp_r26 = atan2d(-sp20.x, -sp20.z);
    if (BoardPlayerSizeGet(temp_r31) == 1) {
        BoardModelVisibilitySet(gripMdl[0], 0);
        BoardModelVisibilitySet(gripMdl[1], 1);
    }
    else {
        BoardModelVisibilitySet(gripMdl[0], 1);
        BoardModelVisibilitySet(gripMdl[1], 0);
    }
    sp14.x = -3.0f;
    sp14.y = temp_r26;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 200.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lotteryMdl[0], &sp14, &sp8, 1300.0f, -1.0f, 27);
    if (BoardPlayerSizeGet(temp_r31) == 1) {
        BoardModelVisibilitySet(lotteryMdl[3], 1);
    }
    omVibrate(temp_r31, 12, 6, 6);
    HuAudFXPlay(0x331);
    HuAudFXPlay(0x344);
    BoardModelMotionStart(lotteryMdl[0], 0, 0);
    while (!BoardModelMotionEndCheck(lotteryMdl[0])) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(BoardLotteryHostGet(), lotteryMot[3], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    BoardPlayerRotSet(temp_r31, 0.0f, temp_r26, 0.0f);
    BoardPlayerPosLerpStart(temp_r31, &sp38, &sp2C, 0x14);
    while (GWPlayer[temp_r31].moving) {
        HuPrcVSleep();
    }
    if (BoardPlayerSizeGet(temp_r31) == 1) {
        DoMiniJumpUp(temp_r31);
    }
    BoardPlayerPosGet(temp_r31, &sp2C);
    for (i = 0; i < 4; i++) {
        if (i != temp_r31) {
            BoardPlayerPosGet(i, &sp38);
            VECSubtract(&sp2C, &sp38, &sp20);
            VECNormalize(&sp20, &sp20);
            BoardPlayerMotBlendSet(i, atan2d(sp20.x, sp20.z), 7);
        }
    }
    BoardMusStart(1, 2, 0x7F, 0);
    BoardPlayerIdleSet(temp_r31);
    while (!BoardStatusStopCheck(temp_r31)) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(BoardLotteryHostGet(), lotteryMot[0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    if (GWPlayer[temp_r31].draw_ticket == 0 && GWSystem.max_turn - GWSystem.turn >= 5) {
        SetupTicket(temp_r31);
        ShowTicket();
        var_r27 = 1;
    }
    else {
        var_r27 = 0;
    }
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        var_r27 = 0;
    }
    PayEnterFee(var_r27);
    var_r25 = BoardRandMod(100) & 0xFF;
    if (var_r25 < 50) {
        ExecBallGame();
    }
    else {
        ExecScratch();
    }
    ExecPrize();
    if (BoardPlayerSizeGet(temp_r31) == 1) {
        DoMiniJumpDown(temp_r31);
    }
    BoardPlayerMoveBetween(temp_r31, lotterySpace, temp_r28);
    while (GWPlayer[temp_r31].moving) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(temp_r31);
    BoardModelVisibilitySet(ballMdl[currPrize & 3], 0);
    BoardAudSeqFadeOut(1, 1000);
    BoardCameraTargetPlayerSet(temp_r31);
    BoardCameraViewSet(1);
    BoardStatusShowSet(temp_r31, 0);
    BoardModelMotionStart(lotteryMdl[0], 0, 0x40000004);
    while (!BoardModelMotionEndCheck(lotteryMdl[0])) {
        HuPrcVSleep();
    }
    BoardModelMotionSpeedSet(lotteryMdl[0], 0.0f);
    BoardModelAttrReset(lotteryMdl[0], 0x40000004);
    HuAudFXPlay(0x32F);
    KillModel();
    BoardStatusShowSetAll(1);
    BoardAudSeqPause(0, 0, 1000);
    HuPrcEnd();
}

static void DoMiniJumpUp(s32 arg0)
{
    Mtx sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float temp_f29;
    float temp_f30;
    float var_f27;
    s16 var_r27;
    s16 temp_r26;
    s16 i;

    var_r27 = BoardModelIDGet(lotteryMdl[0]);
    Hu3DModelObjMtxGet(var_r27, "toto_chibidai", sp34);
    Hu3DMtxTransGet(sp34, &sp28);
    BoardPlayerMotionStart(arg0, 4, 0);
    temp_f29 = BoardPlayerMotionMaxTimeGet(arg0);
    BoardPlayerPosGet(arg0, &sp1C);
    sp28.y += 52.5308f;
    VECSubtract(&sp28, &sp1C, &sp10);
    sp10.x /= temp_f29;
    sp10.z /= temp_f29;
    sp10.y /= temp_f29;
    OSf32tos16(&temp_f29, &temp_r26);
    for (i = 0; i < temp_r26; i++) {
        OSs16tof32(&i, &temp_f30);
        if (i < 4) {
            var_f27 = 5.0f;
        }
        else {
            var_f27 = 0.0f;
        }
        sp1C.x += sp10.x;
        sp1C.y += sp10.y + var_f27 - 0.016666668f * temp_f30 * temp_f30;
        sp1C.z += sp10.z;
        BoardPlayerPosSetV(arg0, &sp1C);
        HuPrcVSleep();
    }
    sp1C.y = sp28.y;
    BoardPlayerPosSetV(arg0, &sp1C);
    BoardPlayerIdleSet(arg0);
}

static void DoMiniJumpDown(s32 arg0)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f31;
    float var_f29;
    s16 i;

    BoardPlayerPosGet(arg0, &sp18);
    BoardSpacePosGet(0, lotterySpace, &sp24);
    VECSubtract(&sp24, &sp18, &spC);
    BoardPlayerMotionStart(arg0, 4, 0);
    spC.x /= 30.0f;
    spC.z /= 30.0f;
    for (i = 0; i < 30; i++) {
        OSs16tof32(&i, &temp_f31);
        if (i < 3) {
            var_f29 = 10.0f;
        }
        else {
            var_f29 = 0.0f;
        }
        sp18.x += spC.x;
        sp18.y += var_f29 + -0.016666668f * temp_f31 * temp_f31 * 0.75f;
        sp18.z += spC.z;
        if (sp24.y > sp18.y) {
            sp18.y = sp24.y;
            break;
        }
        BoardPlayerPosSetV(arg0, &sp18);
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(arg0, 5, 0);
    BoardPlayerPosSetV(arg0, &sp24);
    while (!BoardPlayerMotionEndCheck(arg0)) {
        HuPrcVSleep();
    }
}

static void PayEnterFee(s32 arg0)
{
    s32 var_r29;
    s32 temp_r31;
    s32 i;

    temp_r31 = GWSystem.player_curr;
    BoardStatusShowSetForce(temp_r31);
    BoardStatusShowSet(temp_r31, 1);
    if (arg0 != 0) {
        var_r29 = lotteryMessBase + 12;
    }
    else {
        var_r29 = lotteryMessBase;
    }
    BoardWinCreate(2, var_r29, BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
    while (!BoardStatusStopCheck(temp_r31)) {
        HuPrcVSleep();
    }
    for (i = 0; i < 5; i++) {
        BoardPlayerCoinsAdd(temp_r31, -1);
        HuAudFXPlay(0xE);
        HuPrcSleep(6);
    }
    HuAudFXPlay(0xF);
    BoardStatusShowSet(temp_r31, 0);
}

static void ShowTicket(void)
{
    s16 sp10;
    s16 spE;
    s16 spC;
    s16 spA;
    s8 sp8;
    float var_f31;
    s16 temp_r31;
    s32 var_r29;
    s32 i;
    u8 *var_r28;
    s32 sp14[] = { DATA_MAKE_NUM(DATADIR_BKUJIYA, 21), DATA_MAKE_NUM(DATADIR_BKUJIYA, 22), DATA_MAKE_NUM(DATADIR_BKUJIYA, 23),
        DATA_MAKE_NUM(DATADIR_BKUJIYA, 24), DATA_MAKE_NUM(DATADIR_BKUJIYA, 25), DATA_MAKE_NUM(DATADIR_BKUJIYA, 26),
        DATA_MAKE_NUM(DATADIR_BKUJIYA, 27), DATA_MAKE_NUM(DATADIR_BKUJIYA, 28) };

    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        return;
    }
    sp8 = GWPlayer[GWSystem.player_curr].ticket_player;
    var_r28 = (u8 *)&sp8;
    temp_r31 = HuSprGrpCreate(4);
    BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BKUJIYA, 20), 30001, 0, &spA);
    HuSprGrpMemberSet(temp_r31, 0, spA);
    HuSprAttrSet(temp_r31, 0, 9);
    HuSprPosSet(temp_r31, 0, 288.0f, 240.0f);
    HuSprTPLvlSet(temp_r31, 0, 0.0f);
    var_r29 = GWPlayer[(*var_r28 >> 4) & 3].character;
    BoardSpriteCreate(sp14[var_r29], 30000, 0, &spC);
    HuSprGrpMemberSet(temp_r31, 1, spC);
    HuSprAttrSet(temp_r31, 1, 9);
    HuSprPosSet(temp_r31, 1, 200.0f, 237.0f);
    HuSprTPLvlSet(temp_r31, 1, 0.0f);
    var_r29 = GWPlayer[(*var_r28 >> 2) & 3].character;
    BoardSpriteCreate(sp14[var_r29], 30000, 0, &spE);
    HuSprGrpMemberSet(temp_r31, 2, spE);
    HuSprAttrSet(temp_r31, 2, 9);
    HuSprPosSet(temp_r31, 2, 294.0f, 237.0f);
    HuSprTPLvlSet(temp_r31, 2, 0.0f);
    var_r29 = GWPlayer[*var_r28 & 3].character;
    BoardSpriteCreate(sp14[var_r29], 30000, 0, &sp10);
    HuSprGrpMemberSet(temp_r31, 3, sp10);
    HuSprAttrSet(temp_r31, 3, 9);
    HuSprPosSet(temp_r31, 3, 388.0f, 237.0f);
    HuSprTPLvlSet(temp_r31, 3, 0.0f);
    BoardWinCreate(2, lotteryMessBase + 10, BoardWinPortraitGet());
    BoardWinWait();
    for (var_f31 = 0.0f; var_f31 <= 1.0f; var_f31 += 0.15f) {
        if (var_f31 >= 1.0f) {
            var_f31 = 1.0f;
        }
        for (i = 0; i < 4; i++) {
            HuSprTPLvlSet(temp_r31, i, var_f31);
        }
        HuPrcVSleep();
    }
    BoardWinCreate(2, lotteryMessBase + 11, BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
    for (var_f31 = 1.0f; var_f31 > 0.0f; var_f31 -= 0.15f) {
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        }
        for (i = 0; i < 4; i++) {
            HuSprTPLvlSet(temp_r31, i, var_f31);
        }
        HuPrcVSleep();
    }
    HuSprGrpKill(temp_r31);
    (void)var_r29; // Required to match
}

static void SetupTicket(s32 arg0)
{
    u8 sp8[4];
    u8 var_r29;
    s32 var_r28;
    s32 var_r30;
    s32 var_r31;

    for (var_r30 = var_r31 = 0; var_r31 < 4; var_r31++) {
        if (arg0 != var_r31 && GWPlayer[var_r31].draw_ticket != 0) {
            sp8[var_r30] = GWPlayer[var_r31].ticket_player;
            var_r30++;
        }
    }
    for (var_r28 = 0; var_r28 < 1000; var_r28++) {
        var_r29 = BoardRandMod(64) & 0x3F;
        for (var_r31 = 0; var_r30 != 0 && var_r31 < var_r30; var_r31++) {
            if (sp8[var_r31] == var_r29) {
                var_r29 = 0x80;
                break;
            }
        }
        if (var_r29 != 0x80) {
            break;
        }
    }
    GWPlayer[arg0].ticket_player = var_r29;
    GWPlayer[arg0].draw_ticket = 1;
}

static void LotteryInlineFunc00(s32 arg0, s32 arg1)
{
    s32 sp20[2] = { DATA_MAKE_NUM(DATADIR_BKUJIYA, 18), DATA_MAKE_NUM(DATADIR_BKUJIYA, 19) };
    s16 sp10[2] = { 152, 120 };
    s16 sp14[2] = { 120, 120 };
    Vec sp34;
    float temp_f30;
    s16 var_r30;

    sp34.x = (sp14[arg0] / 2) + 32;
    if (arg1 == 0) {
        sp34.y = -sp10[arg0] / 2;
        temp_f30 = 4.0f;
        if (lotterySpr == -1) {
            lotterySpr = espEntry(sp20[arg0], 30001, 0);
            espAttrSet(lotterySpr, HUSPR_ATTR_NOANIM);
        }
    }
    else {
        sp34.y = (sp10[arg0] / 2) + 40;
        temp_f30 = -4.0f;
    }
    for (var_r30 = sp10[arg0] + 40; var_r30 > 0; var_r30 -= 4) {
        sp34.y += temp_f30;
        espPosSet(lotterySpr, sp34.x, sp34.y);
        HuPrcVSleep();
    }
    if (arg1 != 0 && lotterySpr >= 0) {
        espKill(lotterySpr);
        lotterySpr = -1;
    }
}

static void ExecBallGame(void)
{
    Vec sp4C;
    float temp_f24;
    float var_f23;
    float var_f25;
    float var_f26;
    float var_f27;
    float var_f19;
    float var_f28;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20 = 0;
    s32 temp_r25;
    s32 var_r24;
    s32 temp_r27;
    u8 var_r26;
    s8 var_r17;
    s8 spB;
    s8 spA;
    s8 sp9;
    s8 *temp_r23;
    s32 sp58[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 29), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 29), DATA_MAKE_NUM(DATADIR_PEACHMOT, 29),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 29), DATA_MAKE_NUM(DATADIR_WARIOMOT, 29), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 29),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 29), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 29) };

    temp_r27 = GWSystem.player_curr;
    currPrize = -1;
    sp4C.x = 0.0f;
    sp4C.y = 210.0f;
    sp4C.z = 0.0f;
    BoardCameraMotionStartEx(lotteryMdl[0], NULL, &sp4C, 980.0f, -1.0f, 21);
    LotteryInlineFunc00(0, 0);
    BoardCameraMotionWait();
    BoardWinCreate(2, lotteryMessBase + 1, BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
    HuPrcSleep(0x12);
    CreateLotteryWin(0);
    turnMot = BoardPlayerMotionCreate(temp_r27, sp58[GWPlayer[temp_r27].character]);
    BoardPlayerMotionSpeedSet(temp_r27, 0.0f);
    BoardModelAttrSet(lotteryMdl[1], 0x40000001);
    BoardModelMotionSpeedSet(lotteryMdl[1], 0.0f);
    BoardModelMotionTimeSet(lotteryMdl[1], 0.0f);
    BoardModelAttrSet(gripMdl[0], 0x40000001);
    BoardModelAttrSet(gripMdl[1], 0x40000001);
    BoardPlayerMotionShiftSet(temp_r27, turnMot, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    BoardPlayerMotionSpeedSet(temp_r27, 0.0f);
    temp_f24 = BoardModelMotionMaxTimeGet(lotteryMdl[1]);
    temp_f24 -= 4.0f;
    comInputPos = 0;
    var_r20 = 0;
    spB = spA = sp9 = var_r17 = 0;
    var_r26 = var_f28 = var_f27 = var_f25 = var_f23 = var_r21 = 0;
    HuPrcSleep(24);
    var_r24 = var_r22 = 0;
    while (1) {
        HuPrcVSleep();
        BoardModelMotionSpeedSet(lotteryMdl[1], var_f28);
        BoardModelMotionSpeedSet(gripMdl[0], var_f28);
        BoardModelMotionSpeedSet(gripMdl[1], var_f28);
        BoardPlayerMotionSpeedSet(temp_r27, var_f28);
        if (var_r22 != 0 && var_f28 <= 0.1f) {
            BoardModelMotionSpeedSet(lotteryMdl[1], 0.0f);
            BoardModelMotionSpeedSet(gripMdl[0], 0.0f);
            BoardModelMotionSpeedSet(gripMdl[1], 0.0f);
            BoardPlayerMotionSpeedSet(temp_r27, 0.0f);
            break;
        }
        if (var_r24 == 0) {
            if (BoardModelMotionTimeGet(lotteryMdl[1]) >= temp_f24) {
                var_r21++;
                if ((var_r26++) != 0 || var_r21 >= 1 || var_r20 != 0) {
                    var_r22 = 1;
                    if (currPrize == -1) {
                        var_f27 *= 128.0f;
                        OSf32tos8(&var_f27, &lbl_801D401B);
                        SetBallPrize();
                    }
                }
                var_r24 = 1;
            }
        }
        if (var_r24 != 0 && BoardModelMotionTimeGet(lotteryMdl[1]) < 2.0f) {
            var_r24 = 0;
        }
        if (var_r22 == 0) {
            var_r17 = spB;
            sp9 = spA;
            if (!GWPlayer[temp_r27].com) {
                temp_r25 = GWPlayer[temp_r27].port;
                spB = HuPadStkX[temp_r25];
                spA = HuPadStkY[temp_r25];
            }
            else {
                temp_r23 = comInputBall[comInputPos++];
                spB = temp_r23[0];
                spA = temp_r23[1];
            }
        }
        else {
            spB = spA = 0;
        }
        if (spB == 0x7F || spA == 0x7F) {
            var_r20 = 1;
        }
        else {
            if ((abs(spB) < 57.600002f && abs(spA) < 57.600002f) || (var_r17 == spB && sp9 == spA) || (spB == 0 && spA == 0)) {
                var_f28 *= 0.93f;
                var_f27 *= 0.8f;
                if (var_f27 < 0.01f && var_r26 != 0) {
                    var_r26--;
                }
            }
            else {
                OSs8tof32(&spB, &var_f26);
                OSs8tof32(&spA, &var_f19);
                var_f25 = atan2d(var_f26, var_f19);
                if (var_f25 < 0.0f) {
                    var_f25 += 360.0f;
                }
                if (var_f25 < 20.0f) {
                    HuAudFXPlay(0x333);
                }
                var_f26 = var_f25 - var_f23;
                if (!(var_f26 < 0.0f)) {
                    if (ABS(var_f26) > 30.0f) {
                        var_f26 = 10.0f;
                    }
                    var_f27 += 0.01f * var_f26;
                    if (var_f28 + var_f27 < 2.0f) {
                        var_f28 += var_f27;
                    }
                    else {
                        var_f28 = 2.0f;
                    }
                }
            }
        }
        var_f23 = var_f25;
    }
    KillLotteryWin();
    LotteryInlineFunc00(0, 1);
}

static void SetBallPrize(void)
{
    Process *sp8;
    s32 temp_r31;

    while (1) {
        temp_r31 = BoardRandMod(100);
        if (temp_r31 > 97) {
            currPrize = 0;
        }
        else if (temp_r31 > 87) {
            currPrize = 1;
        }
        else if (temp_r31 > 67) {
            currPrize = 2;
        }
        else {
            currPrize = 3;
        }
        if (GWSystem.max_turn - GWSystem.turn != 0 || currPrize != 2) {
            break;
        }
    }
    sp8 = HuPrcChildCreate(ExecBallPrize, 0x2004, 0x3800, 0, lotteryProc);
}

static void ExecBallPrize(void)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f25;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    float var_f29;
    float var_f30;
    s32 var_r28;
    s16 temp_r29;
    s16 var_r27;
    s16 sp8;
    HsfObject *temp_r3;
    Mtx sp6C;
    Mtx sp3C;

    var_r28 = 0;
    HuAudFXPlay(0x34C);
    temp_r29 = ballMdl[currPrize & 3];
    BoardModelPosGet(lotteryMdl[0], &sp30);
    BoardModelRotGet(lotteryMdl[0], &sp18);
    MTXRotRad(sp6C, 'Y', MTXDegToRad(sp18.y));
    var_r27 = BoardModelIDGet(lotteryMdl[0]);
    temp_r3 = Hu3DModelObjPtrGet(var_r27, "toto_gara");
    temp_f28 = sp30.y + temp_r3->data.curr.pos.y + 100.0f;
    MTXTrans(sp3C, temp_r3->data.curr.pos.x, temp_r3->data.curr.pos.y + 210.0f, temp_r3->data.curr.pos.z + -40.0f);
    MTXConcat(sp6C, sp3C, sp3C);
    Hu3DMtxTransGet(sp3C, &spC);
    VECAdd(&spC, &sp30, &sp30);
    BoardModelVisibilitySet(temp_r29, 1);
    sp24.x = 10.5f;
    sp24.y = -3.0f;
    sp24.z = 0.0f;
    MTXMultVec(sp6C, &sp24, &sp24);
    var_f29 = 0.0f;
    var_f30 = 1.8f;
    temp_f27 = 0.016666668f;
    sp8 = 0;
    while (1) {
        OSs16tof32(&sp8, &var_f25);
        temp_f26 = 4.9f * (2.0f * var_f25 - temp_f27) * temp_f27;
        sp24.y -= temp_f26;
        sp24.x *= 0.92f;
        sp24.z *= 0.92f;
        VECAdd(&sp24, &sp30, &sp30);
        var_f29 += sp24.z;
        if (sp30.y - 25.0f < temp_f28) {
            if (var_r28 == 0) {
                HuAudFXPlay(0x334);
                var_r28 = 1;
            }
            sp30.y = 25.0f + temp_f28 + temp_f26 * var_f30;
            if (var_f30 > 0.0f) {
                var_f30 -= 0.1f;
            }
        }
        BoardModelPosSetV(temp_r29, &sp30);
        BoardModelRotSet(temp_r29, 0.0f, var_f29, 0.0f);
        HuPrcVSleep();
        sp8++;
    }
}

static const s32 pickSpr[]
    = { DATA_MAKE_NUM(DATADIR_BOARD, 30), DATA_MAKE_NUM(DATADIR_BOARD, 31), DATA_MAKE_NUM(DATADIR_BOARD, 32), DATA_MAKE_NUM(DATADIR_BOARD, 33),
          DATA_MAKE_NUM(DATADIR_BOARD, 34), DATA_MAKE_NUM(DATADIR_BOARD, 35), DATA_MAKE_NUM(DATADIR_BOARD, 36), DATA_MAKE_NUM(DATADIR_BOARD, 37) };

static const s32 handMdl[] = { DATA_MAKE_NUM(DATADIR_BKUJIYA, 9), DATA_MAKE_NUM(DATADIR_BKUJIYA, 10), DATA_MAKE_NUM(DATADIR_BKUJIYA, 11),
    DATA_MAKE_NUM(DATADIR_BKUJIYA, 12), DATA_MAKE_NUM(DATADIR_BKUJIYA, 13), DATA_MAKE_NUM(DATADIR_BKUJIYA, 14), DATA_MAKE_NUM(DATADIR_BKUJIYA, 15),
    DATA_MAKE_NUM(DATADIR_BKUJIYA, 16) };

static const s32 ticketSpr[] = { DATA_MAKE_NUM(DATADIR_BKUJIYA, 29), DATA_MAKE_NUM(DATADIR_BKUJIYA, 30), DATA_MAKE_NUM(DATADIR_BKUJIYA, 31),
    DATA_MAKE_NUM(DATADIR_BKUJIYA, 32) };

static omObjData *ticketObj[12] = { NULL };
static s8 ticketPrize[12] = { 0 };
static Vec handLastPos = { 0.0f, 0.0f, 0.0f };

static s32 loseSoundTbl[] = { 0x0000012E, 0x0000016E, 0x000001AE, 0x000001EE, 0x0000022E, 0x0000026E, 0x000002AE, 0x000002EE };

static s32 loseMotTbl[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 51), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 51), DATA_MAKE_NUM(DATADIR_PEACHMOT, 51),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 51), DATA_MAKE_NUM(DATADIR_WARIOMOT, 51), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 51),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 51), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 51) };

static void ExecScratchTicket(s32 arg0)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    u16 var_r29;
    u16 var_r28;
    s16 *temp_r25;
    s32 var_r24;
    s32 temp_r27;
    u16 var_r23;
    omObjData *var_r22;
    TicketWork *temp_r30;
    AnimBmpData *temp_r31;

    var_r24 = GWPlayer[GWSystem.player_curr].character;
    var_r22 = ticketObj[arg0];
    temp_r30 = OM_GET_WORK_PTR(var_r22, TicketWork);
    lotteryMdl[4] = BoardModelCreate(handMdl[var_r24], NULL, 0);
    BoardModelLayerSet(lotteryMdl[4], 6);
    BoardModelPassSet(lotteryMdl[4], 0);
    BoardCameraDirGet(&spC);
    BoardModelRotYSet(lotteryMdl[4], atan2d(-spC.x, -spC.z));
    BoardModelScaleSet(lotteryMdl[4], 3.0f, 3.0f, 3.0f);
    sp24.x = 320.0f;
    sp24.y = 480.0f;
    sp24.z = 500.0f;
    CreateLotteryWin(1);
    while (1) {
        HuPrcVSleep();
        if (sp24.y <= 240.0f) {
            break;
        }
        sp24.y -= 4.0f;
        Hu3D2Dto3D(&sp24, 1, &sp18);
        BoardModelPosSetV(lotteryMdl[4], &sp18);
    }
    comInputPos = 0;
    if (BoardRandMod(100) < 50) {
        comInputDrawP = comInputDraw1;
    }
    else {
        comInputDrawP = comInputDraw2;
    }
    temp_r27 = HuAudFXPlay(0x335);
    HuAudFXVolSet(temp_r27, 0);
    while (1) {
        HuPrcVSleep();
        if (TicketUpdate(temp_r30->unk08->bmp, &sp24, temp_r27) != 0) {
            break;
        }
        if (ScratchTicketCheckDone(temp_r30->unk08->bmp)) {
            break;
        }
    }
    HuAudFXStop(temp_r27);
    while (1) {
        HuPrcVSleep();
        if (sp24.y >= 480.0f) {
            break;
        }
        sp24.y += 4.0f;
        Hu3D2Dto3D(&sp24, 1, &sp18);
        BoardModelPosSetV(lotteryMdl[4], &sp18);
    }
    BoardModelVisibilitySet(lotteryMdl[4], 0);
    temp_r31 = temp_r30->unk08->bmp;
    temp_r25 = temp_r31->data;
    for (var_r28 = 0; var_r28 < temp_r31->sizeY; var_r28++) {
        for (var_r29 = 0; var_r29 < temp_r31->sizeX; var_r29++) {
            var_r23 = TicketGetPixel(temp_r31->sizeX, var_r29, var_r28);
            temp_r25[var_r23] = 0;
        }
        HuPrcVSleep();
    }
    KillLotteryWin();
    BoardModelKill(lotteryMdl[4]);
    lotteryMdl[4] = -1;
}

static void ExecScratch(void)
{
    TicketWork *temp_r28;
    float var_f31;
    s32 temp_curr;
    s32 temp_r31;

    currPrize = -1;
    BoardFilterFadeInit(30, 0xA0);
    InitTicketPrizes();
    InitScratchSpr();
    temp_curr = GWSystem.player_curr;
    if (GWPlayer[temp_curr].com) {
        comLotteryType = BoardRandMod(4);
        comLotteryWinType = BoardRandMod(3);
    }
    BoardWinCreate(2, lotteryMessBase + 9, BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
    CreateLotteryWin(2);
    InitScratchPick();
    while (currPrize == -1) {
        HuPrcVSleep();
    }
    temp_r31 = currPrize;
    currPrize = ticketPrize[temp_r31];
    ExecTicketFocus(temp_r31);
    KillLotteryWin();
    LotteryInlineFunc00(1, 0);
    ExecScratchTicket(temp_r31);
    LotteryInlineFunc00(1, 1);
    temp_r28 = OM_GET_WORK_PTR(ticketObj[temp_r31], TicketWork);
    for (var_f31 = 1.0f; var_f31 > 0.0f; var_f31 -= 0.078125f) {
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        }
        HuSprTPLvlSet(ticketSprGrp, temp_r28->unk00_field2, var_f31);
        HuPrcVSleep();
    }
    HideScratchSpr();
    BoardFilterFadeOut(30);
}

static void KillScratch(void)
{
    if (ticketSprGrp != -1) {
        HuSprGrpKill(ticketSprGrp);
        ticketSprGrp = -1;
    }
    if (lotteryTicketPickObj) {
        OM_GET_WORK_PTR(lotteryTicketPickObj, LotteryTicketPickWork)->unk00_field0 = 1;
    }
    memset(ticketObj, 0, sizeof(ticketObj));
}

static void ExecScratchSpr(omObjData *arg0)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 temp_r29;
    TicketWork *temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0, TicketWork);
    if (temp_r30->unk00_field0 != 0 || BoardIsKill()) {
        temp_r29 = temp_r30->unk00_field2;
        HuSprAttrSet(ticketSprGrp, temp_r29, 4);
        HuSprAttrSet(ticketSprGrp, temp_r29 + 12, 4);
        ticketObj[temp_r29] = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r30->unk01 != 0) {
        temp_r30->unk01--;
        return;
    }
    sp14.x = arg0->trans.x;
    sp14.y = arg0->trans.y;
    sp20.x = arg0->rot.x;
    sp20.y = arg0->rot.y;
    VECSubtract(&sp14, &sp20, &sp8);
    if (ABS(sp8.x) < 1.0f && ABS(sp8.y) < 1.0f) {
        sp8 = sp14;
        temp_r30->unk00_field1 = 1;
    }
    else {
        VECScale(&sp8, &sp8, 0.2f);
        VECAdd(&sp20, &sp8, &sp8);
        temp_r30->unk00_field1 = 0;
    }
    HuSprPosSet(ticketSprGrp, temp_r30->unk00_field2, sp8.x, sp8.y);
    HuSprPosSet(ticketSprGrp, temp_r30->unk00_field2 + 12, sp8.x, sp8.y);
    arg0->rot.x = sp8.x;
    arg0->rot.y = sp8.y;
}

static void HideScratchSpr(void)
{
    s32 i;

    for (i = 0; i < 12; i++) {
        if (ticketObj[i]) {
            OM_GET_WORK_PTR(ticketObj[i], TicketWork)->unk00_field0 = 1;
        }
    }
}

static void InitScratchSpr(void)
{
    Vec sp18;
    Vec spC;
    omObjData *temp_r31;
    TicketWork *temp_r29;
    s32 temp_curr;
    s16 temp_r28;
    s16 sp8;
    s16 i;

    temp_curr = GWSystem.player_curr;
    BoardPlayerRotGet(temp_curr, &sp18);
    memset(ticketObj, 0, sizeof(ticketObj));
    BoardCameraRotGet(&spC);
    temp_r28 = HuSprGrpCreate(24);
    ticketSprGrp = temp_r28;
    for (i = 0; i < 12; i++) {
        temp_r31 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, ExecScratchSpr);
        ticketObj[i] = temp_r31;
        temp_r29 = OM_GET_WORK_PTR(temp_r31, TicketWork);
        temp_r29->unk00_field0 = 0;
        temp_r29->unk00_field2 = i;
        temp_r29->unk01 = (i / 4) * 2;
        temp_r29->unk02 = temp_r29->unk04 = -1;
        temp_r31->trans.x = 107.0f + 110.0f * (i % 4);
        temp_r31->trans.y = 98.0f + 110.0f * (i / 4);
        temp_r31->rot.x = -56.0f;
        temp_r31->rot.y = temp_r31->trans.y;
        BoardSpriteCreate(ticketSpr[ticketPrize[i]], 5500, NULL, &sp8);
        HuSprGrpMemberSet(temp_r28, i, sp8);
        HuSprPosSet(temp_r28, i, temp_r31->rot.x, temp_r31->rot.y);
        HuSprAttrSet(temp_r28, i, 8);
        temp_r29->unk02 = sp8;
        BoardSpriteCreate(DATA_MAKE_NUM(DATADIR_BKUJIYA, 33), 5000, &temp_r29->unk08, &sp8);
        HuSprGrpMemberSet(temp_r28, i + 12, sp8);
        HuSprPosSet(temp_r28, i + 12, temp_r31->rot.x, temp_r31->rot.y);
        HuSprAttrSet(temp_r28, i + 12, 8);
        temp_r29->unk04 = sp8;
    }
    HuSprGrpDrawNoSet(temp_r28, 0x40);
}

static inline u32 ExecStratchPickInlineFunc(LotteryTicketPickWork *temp_r29)
{
    s32 var_r21;
    s32 temp_r23;
    u32 var_r26;

    var_r21 = GWSystem.player_curr;
    var_r26 = 0;
    if (!GWPlayer[var_r21].com) {
        temp_r23 = GWPlayer[GWSystem.player_curr].port;
        var_r26 = HuPadDStkRep[temp_r23] | HuPadBtnDown[temp_r23];
    }
    else if (comLotteryType != temp_r29->unk02) {
        var_r26 = 2;
    }
    else if (comLotteryWinType != temp_r29->unk03) {
        var_r26 = 4;
    }
    else if (comLotteryType == temp_r29->unk02 && comLotteryWinType == temp_r29->unk03) {
        var_r26 = 0x100;
    }
    return var_r26;
}

static void ExecScratchPick(omObjData *arg0)
{
    float var_f29;
    float var_f28;
    s8 var_r28;
    s8 var_r25;
    s8 var_r24;
    u32 var_r26;
    LotteryTicketPickWork *temp_r29;

    temp_r29 = OM_GET_WORK_PTR(arg0, LotteryTicketPickWork);
    if (temp_r29->unk00_field0 || BoardIsKill()) {
        HuSprGrpKill(temp_r29->unk08);
        lotteryTicketPickObj = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r29->unk04 != 0) {
        temp_r29->unk04--;
        return;
    }
    var_r25 = var_r24 = 0;
    var_r26 = ExecStratchPickInlineFunc(temp_r29);
    if (var_r26 == 0x100) {
        currPrize = (temp_r29->unk02 + (temp_r29->unk03 * 4));
        temp_r29->unk00_field0 = 1;
        HuAudFXPlay(2);
        return;
    }
    var_r28 = 0;
    if (var_r26 == 8) {
        var_r24 = -1;
        var_r28 = 1;
    }
    if (var_r26 == 4) {
        var_r24 = 1;
        var_r28 = 1;
    }
    if (var_r26 == 1) {
        var_r25 = -1;
        var_r28 = 1;
    }
    if (var_r26 == 2) {
        var_r25 = 1;
        var_r28 = 1;
    }
    if ((var_r25 != 0 || var_r24 != 0) && GWPlayer[GWSystem.player_curr].com) {
        temp_r29->unk04 = 0x14;
    }
    temp_r29->unk02 += var_r25;
    temp_r29->unk03 += var_r24;
    if (temp_r29->unk02 < 0) {
        temp_r29->unk02 = 0;
        var_r28 = 0;
    }
    else if (temp_r29->unk03 < 0) {
        temp_r29->unk03 = 0;
        var_r28 = 0;
    }
    if (temp_r29->unk02 >= 4) {
        temp_r29->unk02 = 3;
        var_r28 = 0;
    }
    else if (temp_r29->unk03 >= 3) {
        temp_r29->unk03 = 2;
        var_r28 = 0;
    }
    if (var_r28 != 0) {
        HuAudFXPlay(0);
    }
    OSs8tof32(&temp_r29->unk02, &var_f29);
    OSs8tof32(&temp_r29->unk03, &var_f28);
    var_f29 = 107.0f + 110.0f * var_f29 - 32.0f + 16.0f;
    var_f28 = 98.0f + 110.0f * var_f28 + 32.0f - 24.0f;
    HuSprPosSet(temp_r29->unk08, 0, var_f29, var_f28);
}

static void InitScratchPick(void)
{
    float temp_f31 = 91.0f;
    float temp_f30 = 106.0f;
    omObjData *temp_r30;
    LotteryTicketPickWork *var_r31;

    temp_r30 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, ExecScratchPick);
    lotteryTicketPickObj = temp_r30;
    var_r31 = OM_GET_WORK_PTR(temp_r30, LotteryTicketPickWork);
    var_r31->unk02 = var_r31->unk03 = 0;
    var_r31->unk04 = 6;
    var_r31->unk00_field0 = 0;
    var_r31->unk01 = GWPlayer[GWSystem.player_curr].character;
    var_r31->unk08 = HuSprGrpCreate(1);
    BoardSpriteCreate(pickSpr[var_r31->unk01], 5000, 0, &var_r31->unk06);
    HuSprGrpMemberSet(var_r31->unk08, 0, var_r31->unk06);
    HuSprAttrSet(var_r31->unk08, 0, 8);
    HuSprPosSet(var_r31->unk08, 0, temp_f31, temp_f30);
    HuSprGrpDrawNoSet(var_r31->unk08, 0x40);
}

static void InitTicketPrizes(void)
{
    s32 temp_r31;
    s32 i;

    memset(ticketPrize, 3, sizeof(ticketPrize));
    for (i = 0; i < 3; i++) {
        do {
            temp_r31 = BoardRandMod(12);
        } while (ticketPrize[temp_r31] != 3);
        ticketPrize[temp_r31] = i;
        if (GWSystem.max_turn - GWSystem.turn == 0 && i == 2) {
            ticketPrize[temp_r31] = 3;
        }
    }
}

static void ExecTicketFocus(s32 arg0)
{
    float var_f31;
    float temp_f30;
    omObjData *var_r30;
    TicketWork *temp_r29;
    s32 i;

    var_r30 = ticketObj[arg0];
    var_r30->trans.x = 288.0f;
    var_r30->trans.y = 240.0f;
    for (i = 0; i < 12; i++) {
        if (i != arg0) {
            OM_GET_WORK_PTR(ticketObj[i], TicketWork)->unk00_field0 = 1;
        }
    }
    temp_r29 = OM_GET_WORK_PTR(ticketObj[arg0], TicketWork);
    for (var_f31 = 0.0f; var_f31 < 90.0f; var_f31 += 2.0f) {
        temp_f30 = 1.0 + 1.3f * sind(var_f31);
        HuSprScaleSet(ticketSprGrp, temp_r29->unk00_field2, temp_f30, temp_f30);
        HuSprScaleSet(ticketSprGrp, temp_r29->unk00_field2 + 12, temp_f30, temp_f30);
        HuPrcVSleep();
    }
}

static BOOL ScratchTicketCheckDone(AnimBmpData *arg0)
{
    s32 var_r29;
    s32 var_r31;
    s32 var_r30;
    u16 *var_r28;

    var_r28 = arg0->data;
    for (var_r29 = var_r30 = 0; var_r30 < arg0->sizeY; var_r30++) {
        for (var_r31 = 0; var_r31 < arg0->sizeX; var_r31++) {
            if (var_r28[var_r31 + var_r30 * arg0->sizeX] == 0) {
                var_r29++;
            }
        }
    }
    if (var_r29 >= arg0->sizeX * arg0->sizeY - 300) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

static u16 TicketGetPixel(u16 arg0, u16 arg1, u16 arg2)
{
    u16 var_r31;
    u16 var_r30;
    u16 var_r29;
    u16 var_r28;

    var_r29 = (arg1 & 3);
    var_r28 = (arg2 & 3);
    var_r31 = (arg1 >> 2);
    var_r30 = (arg2 >> 2);
    return var_r29 + (var_r28 << 2) + ((var_r31 + var_r30 * (arg0 >> 2)) << 4);
}

static s32 TicketUpdate(AnimBmpData *arg0, Vec *arg1, s32 arg2)
{
    Vec sp48;
    Vec sp3C;
    float temp_f25;
    float temp_f20;
    s32 var_r18;
    s16 var_r17;
    s32 var_r21;
    s32 var_r20;
    s8 *temp_r19;
    s16 *sp38;
    s32 sp34;
    s16 sp26;
    s16 sp24;
    s16 sp22;
    s8 spD;

    if (GWPlayer[GWSystem.player_curr].com) {
        temp_r19 = comInputDrawP[comInputPos++];
        if (temp_r19[0] == 0x7F && temp_r19[1] == 0x7F) {
            return -1;
        }
        OSs8tof32(&temp_r19[0], &sp48.x);
        OSs8tof32(&temp_r19[1], &sp48.y);
    }
    else {
        sp34 = GWPlayer[GWSystem.player_curr].port;
        sp48.x = HuPadStkX[sp34];
        sp48.y = HuPadStkY[sp34];
    }
    sp48.z = 0.0f;
    if (sp48.x == 0.0f && sp48.y == 0.0f) {
        handLastPos = *arg1;
        handUpdateF = 0;
        HuAudFXVolSet(arg2, 0);
        return 0;
    }
    if (handUpdateF == 0) {
        handUpdateF = 1;
    }
    VECNormalize(&sp48, &sp48);
    temp_f20 = atan2f(sp48.x, -sp48.y);
    sp48.x = sin(temp_f20);
    sp48.y = cos(temp_f20);
    temp_f25 = 127.0f * VECMag(&sp48);
    OSf32tos8(&temp_f25, &spD);
    HuAudFXVolSet(arg2, spD);
    sp48.x *= 8.0f;
    sp48.y *= 8.0f;
    VECAdd(&sp48, arg1, &sp3C);
    var_r18 = 0;
    if (sp3C.x < 192.0f) {
        sp3C.x = 192.0f;
        var_r18 = 1;
    }
    if (sp3C.y < 192.0f) {
        sp3C.y = 192.0f;
        var_r18 = 1;
    }
    if (sp3C.x >= 384.0f) {
        sp3C.x = 384.0f;
        var_r18 = 1;
    }
    if (sp3C.y >= 288.0f) {
        sp3C.y = 288.0f;
        var_r18 = 1;
    }
    if (var_r18 != 0) {
        HuAudFXVolSet(arg2, 0);
    }
    *arg1 = sp3C;
    Hu3D2Dto3D(&sp3C, 1, &sp3C);
    BoardModelPosSetV(lotteryMdl[4], &sp3C);
    sp3C = *arg1;
    sp3C.x -= 192.0f;
    sp3C.y -= 192.0f;
    sp3C.x *= arg0->sizeX / 192.0f;
    sp3C.y *= arg0->sizeY / 96.0f;
    sp24 = arg0->sizeX;
    sp38 = arg0->data;
    for (var_r20 = -8; var_r20 < 9; var_r20++) {
        for (var_r21 = -8; var_r21 < 9; var_r21++) {
            OSf32tos16(&sp3C.x, &var_r17);
            OSf32tos16(&sp3C.y, &sp26);
            if (var_r17 + var_r21 < arg0->sizeX && sp26 + var_r20 < arg0->sizeY && var_r17 + var_r21 >= 0 && sp26 + var_r20 >= 0) {
                var_r17 += var_r21;
                sp26 += var_r20;
                sp22 = TicketGetPixel(sp24, var_r17, sp26);
                if (sp22 < arg0->sizeX * arg0->sizeY) {
                    sp38[sp22] = 0;
                }
            }
        }
    }
    DCFlushRange(arg0->data, (u32)(arg0->sizeX * arg0->sizeY * 2) >> 3);
    handLastPos = *arg1;
    return 0;
}

static s32 ExecCoinPrizeInlineFunc(void)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        if (coinF[i] == 0) {
            return i;
        }
    }
    return -1;
}

static void ExecCoinPrize(void)
{
    Vec sp64[10];
    Vec sp8;
    float sp3C[10];
    float sp14[10];
    float var_f31;
    s32 var_r26;
    s32 var_r28;
    s32 temp_r27;
    s32 var_r30;
    s32 i;

    temp_r27 = GWSystem.player_curr;
    if (currPrize == 0) {
        var_r28 = 100;
    }
    else {
        var_r28 = 30;
    }
    memset(coinMdl, 0, sizeof(coinMdl));
    memset(coinF, 0, 10);
    BoardPlayerPosGet(temp_r27, &sp8);
    var_f31 = 150.0f + sp8.y;
    if (BoardPlayerSizeGet(temp_r27) == 1) {
        var_f31 = 52.5308f + 0.3f * var_f31 + 110.0f;
    }
    for (i = 0; i < 10; i++) {
        coinMdl[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 0);
        BoardModelVisibilitySet(coinMdl[i], 0);
    }
    while (1) {
        HuPrcVSleep();
        if (var_r28 > 0) {
            var_r30 = ExecCoinPrizeInlineFunc();
            if (var_r30 != -1) {
                coinF[var_r30] = 1;
                sp64[var_r30].x = sp8.x + 100.0f * (BoardRandFloat() - 0.5f);
                sp64[var_r30].y = sp8.y + 700.0f;
                sp64[var_r30].z = sp8.z + 100.0f * (BoardRandFloat() - 0.5f);
                sp14[var_r30] = -20.0f + -10.0f * BoardRandFloat();
                sp3C[var_r30] = BoardRandMod(360);
                BoardModelVisibilitySet(coinMdl[var_r30], 1);
                BoardModelScaleSet(coinMdl[var_r30], 0.5f, 0.5f, 0.5f);
                var_r28--;
            }
        }
        else {
            var_r26 = 0;
            for (i = 0; i < 10; i++) {
                if (coinF[i] != 0) {
                    var_r26 = 1;
                }
            }
            if (var_r26 == 0) {
                return;
            }
        }
        for (i = 0; i < 10; i++) {
            if (coinF[i] != 0) {
                if (sp64[i].y < var_f31) {
                    sp64[i].y = var_f31;
                    CharModelLayerSetAll(2);
                    CharModelCoinEffectCreate(1, &sp64[i]);
                    BoardModelVisibilitySet(coinMdl[i], 0);
                    coinF[i] = 0;
                    BoardPlayerCoinsAdd(temp_r27, 1);
                    HuAudFXPlay(7);
                    omVibrate(temp_r27, 12, 6, 6);
                }
                else {
                    BoardModelPosSetV(coinMdl[i], &sp64[i]);
                    BoardModelRotSet(coinMdl[i], 0.0f, sp3C[i], 0.0f);
                    sp3C[i] = BoardDAngleCalc(45.0f + sp3C[i]);
                    sp64[i].y += sp14[i];
                }
            }
        }
    }
}

static void ExecItemPrize(void)
{
    Vec sp20;
    Vec sp14;
    float temp_f29;
    float var_f28;
    float var_f30;
    float var_f31;
    s32 temp_r26;
    s32 var_r28;
    s32 temp_r29;
    s16 *var_r31;
    s16 i;
    s32 spC[2] = { DATA_MAKE_NUM(DATADIR_BOARD, 111), DATA_MAKE_NUM(DATADIR_BOARD, 112) };
    s8 sp8[2] = { 2, 3 };

    temp_r29 = GWSystem.player_curr;
    var_r28 = (BoardRandFloat() < 0.5f) ? 1 : 0;
    memset(coinMdl, 0, sizeof(coinMdl));
    var_r31 = &coinMdl[0];
    *var_r31 = BoardModelCreate(spC[var_r28], NULL, 0);
    var_f30 = BoardPlayerRotYGet(temp_r29);
    BoardModelRotYSet(*var_r31, var_f30);
    BoardModelScaleSet(*var_r31, 1.0f, 1.0f, 1.0f);
    BoardSpacePosGet(0, GWPlayer[temp_r29].space_curr, &sp20);
    BoardPlayerPosGet(temp_r29, &sp14);
    sp14.y = sp20.y;
    sp20 = sp14;
    sp14.y += 700.0f;
    sp20.y += 280.0f;
    temp_f29 = (sp20.y - sp14.y) / 60.0f;
    temp_r26 = HuAudFXPlay(0x35F);
    for (i = 0; i < 60; i++) {
        sp14.y += temp_f29;
        BoardModelPosSetV(*var_r31, &sp14);
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    BoardPlayerPosGet(temp_r29, &sp20);
    if (BoardPlayerSizeGet(temp_r29) == 0) {
        sp20.y += 100.0f;
    }
    else {
        sp20.y += 30.000002f;
    }
    temp_f29 = (sp20.y - sp14.y) / 30.0f;
    var_f28 = 0.0f;
    HuAudFXPlay(0x30D);
    for (i = 0; i < 30; i++) {
        sp14.y += temp_f29;
        var_f30 = BoardDAngleCalc(15.0f + var_f30);
        var_f31 = cosd(var_f28);
        if (var_f31 <= 0.0f) {
            var_f31 = 0.01f;
        }
        var_f28 += 3.3333333f;
        BoardModelPosSetV(*var_r31, &sp14);
        BoardModelRotYSet(*var_r31, var_f30);
        BoardModelScaleSet(*var_r31, var_f31, var_f31, var_f31);
        HuPrcVSleep();
    }
    HuAudFXStop(temp_r26);
    BoardModelKill(*var_r31);
    *var_r31 = -1;
    BoardPlayerItemAdd(GWSystem.player_curr, sp8[var_r28]);
    omVibrate(GWSystem.player_curr, 12, 6, 6);
}

static void KillCoin(void)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        BoardModelKill(coinMdl[i]);
        coinMdl[i] = -1;
    }
}

static void ExecPrize(void)
{
    Vec sp14;
    Vec sp8;
    s16 var_r29;
    s16 var_r23;
    s32 var_r26;
    s32 var_r28;
    s32 var_r27;
    s32 temp_r30;
    s32 var_r31;
    s32 i;
    s32 var_r24;

    var_r28 = -1;
    var_r29 = 0;
    var_r27 = -1;
    sp14.x = 0.0f;
    sp14.y = 200.0f;
    sp14.z = 0.0f;
    BoardCameraMotionStartEx(lotteryMdl[0], NULL, &sp14, 1300.0f, -1.0f, 21);
    temp_r30 = GWSystem.player_curr;
    BoardStatusShowSetForce(temp_r30);
    BoardStatusShowSet(temp_r30, 1);
    for (var_r24 = i = 0; i < 3; i++) {
        if (GWPlayer[GWSystem.player_curr].items[i] != -1) {
            var_r24++;
        }
    }
    var_r31 = currPrize;
    if (var_r31 == 0) {
        BoardModelVisibilitySet(lotteryMdl[2], 1);
        BoardModelMotionStart(lotteryMdl[2], 0, 0x40000001);
        BoardModelMotionSpeedSet(lotteryMdl[2], 2.0f);
    }
    var_r26 = 0;
    switch (var_r31) {
        case 0:
            var_r28 = lotteryMessBase + 2;
            var_r29 = 7;
            var_r26 = 100;
            break;
        case 1:
            var_r28 = lotteryMessBase + 4;
            var_r29 = 7;
            var_r26 = 80;
            break;
        case 2:
            var_r28 = lotteryMessBase + 5;
            if (var_r24 < 3) {
                var_r29 = 7;
                var_r26 = 80;
            }
            else {
                var_r29 = 8;
            }
            break;
        case 3:
            var_r28 = lotteryMessBase + 7;
            var_r29 = 8;
            break;
    }
    if (var_r31 != 3) {
        HuAudFXPlay(0x332);
    }
    if (var_r29 == 7) {
        BoardModelMotionShiftSet(BoardLotteryHostGet(), lotteryMot[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    }
    if (var_r26 != 0) {
        BoardPlayerPosGet(temp_r30, &sp8);
        sp8.y = 700.0f;
        BoardConfettiCreate(&sp8, var_r26, 150.0f);
    }
    if (var_r31 == 0 || var_r31 == 1) {
        BoardAudSeqPause(1, 1, 0x1F4);
        HuPrcSleep(0x14);
        if (var_r31 == 0) {
            var_r27 = HuAudSStreamPlay(0xA);
        }
        else {
            var_r27 = HuAudSStreamPlay(9);
        }
    }
    var_r23 = (s32)BoardPlayerRotYGet(temp_r30) + 180;
    BoardPlayerMotBlendSet(temp_r30, var_r23, 0xF);
    while (!BoardPlayerMotBlendCheck(temp_r30)) {
        HuPrcVSleep();
    }
    if (var_r31 == 0 || var_r31 == 1) {
        while (HuAudSStreamStatGet(var_r27) != 0) {
            HuPrcVSleep();
        }
        var_r27 = -1;
        BoardAudSeqPause(1, 0, 1000);
    }
    BoardWinCreate(2, var_r28, BoardWinPortraitGet());
    BoardWinWait();
    if (var_r31 == 2) {
        if (var_r24 == 3) {
            BoardWinCreate(2, lotteryMessBase + 6, BoardWinPortraitGet());
            BoardWinWait();
        }
        else {
            BoardAudSeqPause(1, 1, 1000);
            HuPrcSleep(0x30);
            var_r27 = HuAudSStreamPlay(2);
        }
    }
    if (var_r29 == 8) {
        HuAudFXPlay(loseSoundTbl[GWPlayer[temp_r30].character]);
        BoardPlayerVoiceEnableSet(temp_r30, var_r29, 0);
    }
    BoardPlayerMotionShiftSet(temp_r30, var_r29, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    switch (var_r31) {
        case 0:
        case 1:
            ExecCoinPrize();
            break;
        case 2:
            if (var_r24 < 3) {
                ExecItemPrize();
            }
            else {
                var_r31 = 3;
            }
            break;
    }
    if (var_r27 != -1) {
        while (HuAudSStreamStatGet(var_r27) != 0) {
            HuPrcVSleep();
        }
        var_r27 = -1;
        BoardAudSeqPause(1, 0, 1000);
    }
    while (!BoardPlayerMotionEndCheck(temp_r30)) {
        HuPrcVSleep();
    }
    if (var_r31 != 3) {
        var_r28 = lotteryMessBase + 3;
    }
    else {
        var_r28 = lotteryMessBase + 8;
    }
    BoardModelMotionShiftSet(BoardLotteryHostGet(), lotteryMot[2], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    BoardWinCreate(2, var_r28, BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
    if (var_r26 != 0) {
        BoardConfettiStop();
    }
    if (var_r31 == 3) {
        ExecLose(temp_r30);
    }
}

static void ExecLose(s32 arg0)
{
    s32 temp_r30;

    temp_r30 = GWPlayer[arg0].character;
    loseMot = BoardPlayerMotionCreate(arg0, loseMotTbl[temp_r30]);
    BoardPlayerMotionShiftSet(arg0, loseMot, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(10);
    while (!BoardPlayerMotionEndCheck(arg0)) {
        HuPrcVSleep();
    }
}

static void CreateLotteryWin(s32 arg0)
{
    float sp8[2];
    float temp_f30;
    float var_f31;
    s32 var_r31;

    temp_f30 = -10000.0f;
    if (arg0 == 0) {
        var_r31 = MAKE_MESSID(6, 80);
        var_f31 = 352.0f;
    }
    else if (arg0 == 1) {
        var_f31 = 352.0f;
        var_r31 = MAKE_MESSID(6, 81);
    }
    else {
        var_f31 = 364.0f;
        var_r31 = MAKE_MESSID(32, 22);
    }
    HuWinMesMaxSizeGet(1, sp8, var_r31);
    lotteryInstWin = HuWinCreate(temp_f30, var_f31, sp8[0], sp8[1], 0);
    HuWinBGTPLvlSet(lotteryInstWin, 0.0f);
    HuWinMesSpeedSet(lotteryInstWin, 0);
    HuWinMesSet(lotteryInstWin, var_r31);
}

static void KillLotteryWin(void)
{
    if (lotteryInstWin != -1) {
        HuWinKill(lotteryInstWin);
        lotteryInstWin = -1;
    }
}

void BoardLotteryTutorialExec(void)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r31;
    s32 temp_r30;

    temp_r30 = BoardDataDirReadAsync(DATADIR_BKUJIYA);
    temp_r31 = BoardSpaceFlagSearch(0, 0x10000000);
    if (temp_r30 != -1) {
        BoardDataAsyncWait(temp_r30);
    }
    BoardModelMotionStart(BoardLotteryHostGet(), 1, 0x40000001);
    CreateModel();
    temp_r29 = BoardSpaceLinkFlagSearch(0, temp_r31, 0x02000000);
    BoardSpacePosGet(0, temp_r31, &sp38);
    BoardSpacePosGet(0, temp_r29, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    VECNormalize(&sp20, &sp20);
    temp_r28 = atan2d(-sp20.x, -sp20.z);
    sp14.x = -3.0f;
    sp14.y = temp_r28;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 200.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lotteryMdl[0], &sp14, &sp8, 1300.0f, -1.0f, 21);
    HuAudFXPlay(0x331);
    HuAudFXPlay(0x344);
    BoardModelMotionStart(lotteryMdl[0], 0, 0);
    while (!BoardModelMotionEndCheck(lotteryMdl[0])) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(BoardLotteryHostGet(), lotteryMot[3], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(10);
    while (!BoardModelMotionEndCheck(BoardShopHostGet())) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(BoardLotteryHostGet(), lotteryMot[0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    BoardTutorialHookExec(0x1C, 0);
    BoardModelMotionShiftSet(BoardLotteryHostGet(), lotteryMot[2], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    HuPrcSleep(30);
    BoardModelMotionStart(lotteryMdl[0], 0, 0x40000004);
    while (!BoardModelMotionEndCheck(lotteryMdl[0])) {
        HuPrcVSleep();
    }
    BoardModelMotionSpeedSet(lotteryMdl[0], 0.0f);
    BoardModelAttrReset(lotteryMdl[0], 0x40000004);
    HuAudFXPlay(0x32F);
    KillModel();
}
