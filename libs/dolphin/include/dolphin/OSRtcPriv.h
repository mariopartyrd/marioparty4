#ifndef _DOLPHIN_OSRTCPRIV
#define _DOLPHIN_OSRTCPRIV

#include <types.h>

typedef struct OSSram {
    u16 checkSum;
    u16 checkSumInv;
    u32 ead0;
    u32 ead1;
    u32 counterBias;
    s8 displayOffsetH;
    u8 ntd;
    u8 language;
    u8 flags;
} OSSram;

typedef struct OSSramEx {
    u8 flashID[2][12];
    u32 wirelessKeyboardID;
    u16 wirelessPadID[4];
    u8 dvdErrorCode;
    u8 _padding0;
    u8 flashIDCheckSum[2];
    u16 gbs;
    u8 _padding1[2];
} OSSramEx;

void __OSInitSram();
OSSram *__OSLockSram();
BOOL __OSSyncSram();
BOOL __OSUnlockSram(BOOL commit);
OSSramEx *__OSLockSramEx();
void OSSetWirelessID(s32 chan, u16 id);
u16 OSGetWirelessID(s32 chan);

#endif // _DOLPHIN_OSRTCPRIV
