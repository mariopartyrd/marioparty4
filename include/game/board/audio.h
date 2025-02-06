#ifndef _BOARD_AUDIO_H
#define _BOARD_AUDIO_H

#include "dolphin/types.h"

void BoardMusStartBoard(void);
void BoardMusStart(s32 boardNo, s32 musId, s8 vol, u16 speed);
void BoardAudSeqFadeOutFast(s32 boardNo);
void BoardAudSeqFadeOut(s32 boardNo, u16 speed);
void BoardMusLoudSet(s32 boardNo, s32 isQuieter);
void BoardMusVolPanSet(s32 boardNo, s8 vol, u16 fadeSpeed);
void BoardAudSeqPause(s32 boardNo, s32 pause, u16 speed);
s32 BoardMusStatusGet(s32 boardNo);
void BoardAudSeqClear(void);
void BoardAudSeqFadeOutAll(void);
void BoardAudFXPlay(void);
void BoardAudFXStop(void);

#endif
