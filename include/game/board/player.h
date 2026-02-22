#ifndef _BOARD_PLAYER_H
#define _BOARD_PLAYER_H

#include "math.h"
#include "dolphin.h"
#include "game/gamework_data.h"
#include "game/gamework.h"
#include "game/window.h"
#include "game/object.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/board/main.h"
#include "game/board/space.h"
#include "game/board/ui.h"

SHARED_SYM extern s16 boardPlayerMdl[4];

static inline s32 BoardPlayerHandicapGet(s32 player)
{
	return GWPlayer[player].handicap;
}

static inline PlayerState *BoardPlayerGet(s32 player)
{
	return &GWPlayer[player];
}

static inline s16 BoardPlayerModelGet(s32 player)
{
	PlayerState *player_ptr = BoardPlayerGet(player);
	return boardPlayerMdl[player_ptr->player_idx];
}

s32 BoardItemPrevGet(void);
void BoardItemPrevSet(s32 type);
s32 BoardPlayerGetCharMess(s32 player);
char* BoardPlayerGetCharName(s32 player);
s32 BoardPlayerIsAllCom(void);
void BoardPlayerInit(void);
void BoardPlayerModelInit(void);
void BoardPlayerModelKill(void);
void BoardPlayerLayerSet(s32, s32);
void BoardPlayerCameraSet(s32, u16);
void fn_80062A40(s32, f32);
void BoardPlayerExistCheck(s32, s32);
s32 BoardPlayerItemAdd(s32, s32);
s32 BoardPlayerItemRemove(s32, s32);
s32 BoardPlayerItemFind(s32, s32);
s32 BoardPlayerItemCount(s32);
void BoardPlayerCornerPosSet(s32 arg0);
void BoardPlayerCornerPosGet(s32, Vec*);
void BoardPlayerAmbSet(s32, f32, f32, f32);
void BoardPlayerMtxSet(s32, Mtx*);
void BoardPlayerPosSetV(s32, Vec*);
void BoardPlayerPosSet(s32, f32, f32, f32);
void BoardPlayerPosGet(s32, Vec*);
void BoardPlayerRotSetV(s32, Vec*);
void BoardPlayerRotSet(s32, f32, f32, f32);
void BoardPlayerRotGet(s32, Vec*);
void BoardPlayerRotYSet(s32, f32);
f32 BoardPlayerRotYGet(s32);
void BoardPlayerScaleSetV(s32, Vec*);
void BoardPlayerScaleSet(s32, f32, f32, f32);
void BoardPlayerScaleGet(s32, Vec*);
s16 BoardPlayerCurrMotionGet(s32);
s32 BoardPlayerMotionCreate(s32, s32);
s32 BoardPlayerMotionKill(s32, s32);
s32 BoardPlayerMotionEndCheck(s32);
void BoardPlayerMotionEndWait(s32);
void BoardPlayerMotionStart(s32, s32, s32);
void BoardPlayerMotionShiftSet(s32, s32, f32, f32, u32);
void BoardPlayerMotionSpeedSet(s32, f32);
void BoardPlayerMotionTimeSet(s32, f32);
f32 BoardPlayerMotionTimeGet(s32);
f32 BoardPlayerMotionMaxTimeGet(s32);
void BoardPlayerMotionTimeRangeSet(s32, f32, f32);
void BoardPlayerModelAttrSet(s32, s32);
void BoardPlayerModelAttrReset(s32, s32);
void BoardPlayerCoinsSet(s32, s32);
s32 BoardPlayerCoinsGet(s32);
void BoardPlayerCoinsAdd(s32, s32);
void BoardPlayerStarsAdd(s32, s32);
void BoardPlayerSizeSet(s32, s32);
s32 BoardPlayerSizeGet(s32);
s32 BoardPlayerSameTeamFind(s32);
s32 BoardPlayerTeamFind(s32);
s32 BoardPlayerRankCalc(s32);
void BoardPlayerPreTurnHookSet(s32, s32 (*)());
void BoardPlayerPostTurnHookSet(s32, s32 (*)());
void BoardPlayerTurnExec(s32);
void BoardPlayerTurnRollExec(s32);
void BoardPlayerTurnMoveExec(s32);
void BoardPlayerPostTurnHookExec(s32);
void BoardPlayerSizeRestore(s32);
void BoardPlayerZoomRestore(s32);
void BoardJunctionMaskSet(s32);
void BoardJunctionMaskReset(s32);
void BoardJunctionMaskZero(void);
void BoardPlayerVoiceEnableSet(s32, s32, s32);

#ifndef __MWERKS__
void BoardPlayerMoveBetween(s32 arg0, s32 arg1, s32 arg2);
#endif

void BoardPlayerMoveTo(s32, s32);
void BoardPlayerMoveToAsync(s32, s32);
void BoardPlayerPosLerpStart(s32, Vec*, Vec*, s16);
void BoardPlayerDiceJumpStart(s32);
s32 BoardPlayerDiceJumpCheck(s32);
void BoardPlayerIdleSet(s32);
void BoardPlayerMotBlendSet(s32 arg0, s16 arg1, s16 arg2);

void BoardPlayerBtnDownWait(s32, u32);
void BoardPlayerAutoSizeSet(s32, s32);
s32 BoardPlayerAutoSizeGet(s32);
u32 BoardPlayerMoveAwayIsDone(void);
void BoardPlayerMoveAwayStart(s32, s32, s32);
void BoardPlayerMoveAwayStartCurr(s32, s32);
void BoardPlayerCopyMat(s32);
void BoardPlayerCopyEyeMat(s32, s32);
void BoardBowserSuitMotionSetJump(void);
//...
s32 BoardPlayerAutoSizeGet(s32);
void BoardPlayerAutoSizeSet(s32, s32);
void BoardPlayerCopyMat(s32);
void BoardBowserSuitInit(s32);
void BoardBowserSuitKill(s32);
void BoardRollCreate(s32, s32);
void BoardRollUpdateSet(s32);
s32 BoardMegaDoubleDiceCheck(void);
void BoardPlayerResizeAnimExec(s32 player, s32 size);
s32 BoardPlayerAnimBlendCheck(s32);
s16 BoardBowserSuitPlayerModelGet(void);
void BoardBowserSuitMotionSetWait(void);
void BoardBowserSuitPlayerModelKill(void);
void BoardRollDispSet(s32);
s32 BoardPlayerMotBlendCheck(s32);
void BoardBowserSuitMotionSetWalk(void);
s16 BoardBowserSuitModelGet(void);

#endif
