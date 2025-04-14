#ifndef _GAME_OBJSUB_H
#define _GAME_OBJSUB_H

#include "dolphin.h"
#include "game/process.h"
#include "game/gamework_data.h"
#include "version.h"

typedef struct mg_info {
    u16 ovl;
    u8 type;
    u8 flag;
    u8 record_idx;
    u32 name_mess;
    u32 data_dir;
    u32 inst_pic[3];
    u32 mg_pic[3];
    u32 inst_mess[4];
} MgInfo;

s32 omMgIndexGet(s16 overlay);
void omGameSysInit(Process *objman);
void omVibrate(s16 player_cfg_index, s16 duration, s16 off, s16 on);


SHARED_SYM extern s16 mgTypeCurr;
SHARED_SYM extern s16 mgBattleStar[4];
SHARED_SYM extern s16 mgBattleStarMax;
SHARED_SYM extern u8 lbl_801D3E94;
SHARED_SYM extern u32 mgRecordExtra;
SHARED_SYM extern s32 mgQuitExtraF;
SHARED_SYM extern s32 mgPracticeEnableF;
SHARED_SYM extern s32 mgInstExitEnableF;
SHARED_SYM extern u8 mgBoardHostEnableF;

SHARED_SYM extern s16 mgTicTacToeGrid[3][3];
SHARED_SYM extern u8 mgIndexList[256];
SHARED_SYM extern GameStat mgGameStatBackup;

SHARED_SYM extern MgInfo mgInfoTbl[];

#endif
