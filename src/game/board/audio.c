#include "game/board/audio.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/msm.h"
#include "game/board/main.h"

static s16 boardSeq[2][2];

static s32 boardFX = -1;

static s16 boardMusTbl[] = {
    0x000D, 0x0011, 0x0015,
    0x001C, 0x0021, 0x0025,
    0x0028, 0x0029, 0x002A
};

void BoardMusStartBoard(void) {
    s16 musIdx = boardMusTbl[GWBoardGet()];

    BoardMusStart(0, musIdx, 0x7F, 0);
    BoardAudFXPlay();
}

void BoardMusStart(s32 boardNo, s32 musId, s8 vol, u16 speed) {
    s16 *board = boardSeq[boardNo];
    MSM_MUSPARAM param;

    if (musId == board[1]) {
        return;
    }
    if (board[0] != -1) {
        BoardAudSeqFadeOutFast(board[0]);
    }
    param.flag = MSM_MUSPARAM_CHAN;
    if (speed != 0) {
        param.flag |= MSM_MUSPARAM_FADESPEED;
    }
    if (vol < 0) {
        param.flag |= MSM_MUSPARAM_VOL;
        vol = 0x7F;
    }
    param.fadeSpeed = speed;
    param.vol = vol;
    param.chan = boardNo;
    board[0] = msmMusPlay(musId, &param);
    board[1] = musId;
}

void BoardAudSeqFadeOutFast(s32 boardNo) {
    BoardAudSeqFadeOut(boardNo, 0x64);
}

void BoardAudSeqFadeOut(s32 boardNo, u16 speed) {
    s16 *board = boardSeq[boardNo];

    if (board[0] == -1) {
        return;
    }
    HuAudSeqFadeOut(board[0], speed);
    board[1] = board[0] = -1;
}

void BoardMusLoudSet(s32 boardNo, s32 isQuieter) {
    if (isQuieter != 0) {
        BoardMusVolPanSet(boardNo, 0x60, 0x1F4);
    } else {
        BoardMusVolPanSet(boardNo, 0x7F, 0x1F4);
    }
}

void BoardMusVolPanSet(s32 boardNo, s8 vol, u16 fadeSpeed) {
    s16 *board = boardSeq[boardNo];
    MSM_MUSPARAM param;

    if (board[0] == -1) {
        return;
    }
    param.flag = MSM_MUSPARAM_CHAN;
    param.flag |= MSM_MUSPARAM_VOL;
    if (vol < 0) {
        vol = 0x7F;
    }
    param.fadeSpeed = fadeSpeed;
    param.vol = vol;
    msmMusSetParam(board[0], &param);
}

void BoardAudSeqPause(s32 boardNo, s32 pause, u16 speed) {
    s16 *board = boardSeq[boardNo];

    if (board[0] == -1) {
        return;
    }
    if (pause != 0) {
        if (BoardMusStatusGet(boardNo) == 3) {
            return;
        }
    } else if (BoardMusStatusGet(boardNo) != 3) {
        return;
    }
    HuAudSeqPause(board[0], pause, speed);
}

s32 BoardMusStatusGet(s32 boardNo) {
    s16 *board = boardSeq[boardNo];

    if (board[0] == -1) {
        return 0;
    }
    return msmMusGetStatus(board[0]);
}

void BoardAudSeqClear(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        boardSeq[i][0] = boardSeq[i][1] = -1;
    }
    boardFX = -1;
}

void BoardAudSeqFadeOutAll(void) {
    s16 *temp_r31;
    s32 i;

    for (i = 0; i < 2; i++) {
        temp_r31 = boardSeq[i];
        if (temp_r31[0] != -1) {
            HuAudSeqFadeOut(temp_r31[0], 0x64);
            temp_r31[1] = temp_r31[0] = -1;
        }
    }
    BoardAudFXStop();
}

void BoardAudFXPlay(void) {
    s32 seId;

    switch (GWBoardGet()) {
        case BOARD_ID_MAIN5:
            seId = 0x48D;
            break;
        case BOARD_ID_MAIN6:
            seId = 0x4A2;
            break;
        default:
            return;
    }
    if (boardFX == -1) {
        boardFX = HuAudFXPlay(seId);
    }
}

void BoardAudFXStop(void) {
    if (boardFX != -1) {
        HuAudFXStop(boardFX);
        boardFX = -1;
    }
}
