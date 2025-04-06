#include "ext_math.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/mpexDll.h"

#define FONT_CHAR_MAX 100

static s32 FontCharFile[0xC6] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x140025,
    0x140026,
    0x140027,
    0x140028,
    0x140029,
    0x14002A,
    0x14002B,
    0x14002C,
    0x14002D,
    0x14002E,
    0x140025,
    0x140025,
    0x140025,
    0x14002F,
    0x140025,
    0x140025,
    0x140025,
    0x140034,
    0x140035,
    0x140036,
    0x140037,
    0x140038,
    0x140039,
    0x14003A,
    0x14003B,
    0x14003C,
    0x14003D,
    0x14003E,
    0x14003F,
    0x140040,
    0x140041,
    0x140042,
    0x140043,
    0x140044,
    0x140045,
    0x140046,
    0x140047,
    0x140048,
    0x140049,
    0x14004A,
    0x14004B,
    0x14004C,
    0x14004D,
    0x140042,
    0x140032,
    0x140042,
    0x140042,
    0x140042,
    0x140042,
    0x14004E,
    0x14004F,
    0x140050,
    0x140051,
    0x140052,
    0x140053,
    0x140054,
    0x140055,
    0x140056,
    0x140057,
    0x140058,
    0x140059,
    0x14005A,
    0x14005B,
    0x14005C,
    0x14005D,
    0x14005E,
    0x14005F,
    0x140060,
    0x140061,
    0x140062,
    0x140063,
    0x140064,
    0x140065,
    0x140066,
    0x140067,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x14002F,
    0x140033,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140025,
    0x140030,
    0x140031,
    0x140025,
    0x140025,
};

s32 fn_1_1CB80(SeqWork *arg0, char *arg1, s16 arg2)
{
    char *str;
    s16 len;
    s16 *posY;
    s16 charNum;
    s32 *fileTbl;
    s16 i;
    s16 grpNo;
    s32 file;
    s16 *posX;
    AnimData **animP;
    s16 gid;
    s16 sprid;

    fileTbl = FontCharFile;

    for (grpNo = 0; grpNo < 0x10; grpNo++) {
        if (arg0->spr_grp[grpNo] == -1) {
            break;
        }
    }
    if (grpNo == 0x10) {
        return -1;
    }
    animP = HuMemDirectMalloc(HEAP_SYSTEM, (FONT_CHAR_MAX * sizeof(AnimData*)));
    posX = HuMemDirectMalloc(HEAP_SYSTEM, FONT_CHAR_MAX * sizeof(*posX));
    posY = HuMemDirectMalloc(HEAP_SYSTEM, FONT_CHAR_MAX * sizeof(*posY));

    for (str = arg1, len = 0, charNum = 0; str[0] != 0; str++) {
        if (str[0] == 0x20 || str[0] == 0x10) {
            len += 0xE;
        }
        else if (str[0] < 0x30 || str[0] == 0x80 || str[0] == 0x81) {
            continue;
        }
        else {
            if (str[1] == 0x80) {
                if ((str[0] >= 0x96) && (str[0] <= 0xA4)) {
                    file = fileTbl[str[0] + 0x6A];
                }
                else if ((str[0] >= 0xAA) && (str[0] <= 0xAE)) {
                    file = fileTbl[str[0] + 0x65];
                }
                else if ((str[0] >= 0xD6) && (str[0] <= 0xE4)) {
                    file = fileTbl[str[0] + 0x43];
                }
                else if ((str[0] >= 0xEA) && (str[0] <= 0xEE)) {
                    file = fileTbl[str[0] + 0x3E];
                }
            }
            else if (str[1] == 0x81) {
                if ((str[0] >= 0xAA) && (str[0] <= 0xAE)) {
                    file = fileTbl[str[0] + 0x6A];
                }
                else if ((str[0] >= 0xEA) && (str[0] <= 0xEE)) {
                    file = fileTbl[str[0] + 0x43];
                }
            }
            else {
                file = fileTbl[str[0]];
            }
            animP[charNum] = HuSprAnimReadFile(file);
            posX[charNum] = len;
            if ((str[0] >= 0x61) && (str[0] <= 0x7A)) {
                posY[charNum] = 2;
                len += 0x12;
            }
            else if ((str[0] == 0xC2) || (str[0] == 0xC3)) {
                posY[charNum] = 0;
                len += 0x12;
            }
            else if (str[0] == 0x5C) {
                posY[charNum] = 0;
                len += 8;
            }
            else if ((str[0] >= 0x87) && (str[0] <= 0x8F)) {
                posY[charNum] = 4;
                len += 0x18;
            }
            else if ((str[0] >= 0xC7) && (str[0] <= 0xCF)) {
                posY[charNum] = 4;
                len += 0x18;
            }
            else if ((str[0] == 0x3D) || (str[0] == 0x84)) {
                posY[charNum] = 0;
                len += 0x14;
            }
            else {
                posY[charNum] = 0;
                len += 0x1C;
            }
            charNum++;
        }
    }
    gid = HuSprGrpCreate(charNum);
    arg0->spr_grp[grpNo] = gid;
    arg0->alt_word_len = len;
    len = (len / 2) - 0xE;
    for (i = 0; i < charNum; i++) {
        sprid = HuSprCreate(animP[i], 0, 0);
        HuSprGrpMemberSet(gid, i, sprid);
        HuSprPosSet(gid, i, posX[i] - len, posY[i]);
    }

    arg0->word_len = charNum;
    HuMemDirectFree(animP);
    HuMemDirectFree(posX);
    HuMemDirectFree(posY);
    return gid;
}

s32 fn_1_1D02C(s32 arg0)
{
    SeqWork sp10;
    s16 spC[2];
    char *var_r31;
    s32 var_r30;
    s16 var_r29;
    char *var_r28;
    s32 var_r27;
    s32 var_r26;
    s16 var_r25;

    var_r25 = GWGameStat.language;
    lbl_1_bss_6AC = var_r25;
    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        sp10.sprite[var_r30] = sp10.spr_grp[var_r30] = -1;
    }
    var_r28 = MessData_MesPtrGet(messDataPtr, arg0);
    var_r31 = var_r28;
    var_r30 = 0;
    var_r29 = 0;

    while (TRUE) {
        if (var_r31[0] == 0 || var_r31[0] == 0xA) {
            if (var_r31[0] == 0) {
                var_r30 = 1;
            }
            var_r31[0] = 0;
            if (lbl_1_bss_6AC == 0) {
                var_r27 = 1;
            }
            else {
                var_r27 = 0;
            }
            var_r26 = fn_1_1CB80(&sp10, var_r28, var_r27);
            HuSprGrpPosSet(sp10.spr_grp[var_r29], 288.0f, 240.0f);
            spC[var_r29] = sp10.alt_word_len;
            var_r29++;
            if (var_r30 == 0) {
                var_r28 = var_r31 + 1;
            }
            else {
                break;
            }
        }
        var_r31++;
    }
    return var_r26;
}
