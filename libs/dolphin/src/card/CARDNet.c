#include <dolphin/card.h>
#include <dolphin/dsp.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>

#include <dolphin/CARDPriv.h>

u16 __CARDVendorID = 0xffff;

s32 CARDGetSerialNo(s32 chan, u64 *serialNo)
{
    CARDControl *card;
    CARDID *id;
    int i;
    u64 code;
    s32 result;

    if (!(0 <= chan && chan < 2)) {
        return CARD_RESULT_FATAL_ERROR;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    id = (CARDID *)card->workArea;
    for (code = 0, i = 0; i < sizeof(id->serial) / sizeof(u64); ++i) {
        code ^= *(u64 *)&id->serial[sizeof(u64) * i];
    }
    *serialNo = code;

    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}
