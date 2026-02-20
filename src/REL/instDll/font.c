#include <version.h>
#include "game/sprite.h"

#include "REL/instDll.h"

#define FONT_CHAR_MAX 100

#if VERSION_PAL
static s32 FontCharFile[0x130] = {
#else
static s32 FontCharFile[0xC6] = {
#endif
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
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x26),
    DATA_MAKE_NUM(DATADIR_INST, 0x27),
    DATA_MAKE_NUM(DATADIR_INST, 0x28),
    DATA_MAKE_NUM(DATADIR_INST, 0x29),
    DATA_MAKE_NUM(DATADIR_INST, 0x2A),
    DATA_MAKE_NUM(DATADIR_INST, 0x2B),
    DATA_MAKE_NUM(DATADIR_INST, 0x2C),
    DATA_MAKE_NUM(DATADIR_INST, 0x2D),
    DATA_MAKE_NUM(DATADIR_INST, 0x2E),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x2F),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
#if VERSION_NTSC
    DATA_MAKE_NUM(DATADIR_INST, 0x34),
#endif
    DATA_MAKE_NUM(DATADIR_INST, 0x35),
    DATA_MAKE_NUM(DATADIR_INST, 0x36),
    DATA_MAKE_NUM(DATADIR_INST, 0x37),
    DATA_MAKE_NUM(DATADIR_INST, 0x38),
    DATA_MAKE_NUM(DATADIR_INST, 0x39),
    DATA_MAKE_NUM(DATADIR_INST, 0x3A),
    DATA_MAKE_NUM(DATADIR_INST, 0x3B),
    DATA_MAKE_NUM(DATADIR_INST, 0x3C),
    DATA_MAKE_NUM(DATADIR_INST, 0x3D),
    DATA_MAKE_NUM(DATADIR_INST, 0x3E),
    DATA_MAKE_NUM(DATADIR_INST, 0x3F),
    DATA_MAKE_NUM(DATADIR_INST, 0x40),
    DATA_MAKE_NUM(DATADIR_INST, 0x41),
    DATA_MAKE_NUM(DATADIR_INST, 0x42),
    DATA_MAKE_NUM(DATADIR_INST, 0x43),
    DATA_MAKE_NUM(DATADIR_INST, 0x44),
    DATA_MAKE_NUM(DATADIR_INST, 0x45),
    DATA_MAKE_NUM(DATADIR_INST, 0x46),
    DATA_MAKE_NUM(DATADIR_INST, 0x47),
    DATA_MAKE_NUM(DATADIR_INST, 0x48),
    DATA_MAKE_NUM(DATADIR_INST, 0x49),
    DATA_MAKE_NUM(DATADIR_INST, 0x4A),
    DATA_MAKE_NUM(DATADIR_INST, 0x4B),
    DATA_MAKE_NUM(DATADIR_INST, 0x4C),
    DATA_MAKE_NUM(DATADIR_INST, 0x4D),
#if VERSION_PAL
    DATA_MAKE_NUM(DATADIR_INST, 0x4E),
    DATA_MAKE_NUM(DATADIR_INST, 0x43),
    DATA_MAKE_NUM(DATADIR_INST, 0x32),
    DATA_MAKE_NUM(DATADIR_INST, 0x43),
    DATA_MAKE_NUM(DATADIR_INST, 0x43),
    DATA_MAKE_NUM(DATADIR_INST, 0x43),
    DATA_MAKE_NUM(DATADIR_INST, 0x43),
#else
    DATA_MAKE_NUM(DATADIR_INST, 0x42),
    DATA_MAKE_NUM(DATADIR_INST, 0x32),
    DATA_MAKE_NUM(DATADIR_INST, 0x42),
    DATA_MAKE_NUM(DATADIR_INST, 0x42),
    DATA_MAKE_NUM(DATADIR_INST, 0x42),
    DATA_MAKE_NUM(DATADIR_INST, 0x42),
    DATA_MAKE_NUM(DATADIR_INST, 0x4E),
#endif
    DATA_MAKE_NUM(DATADIR_INST, 0x4F),
    DATA_MAKE_NUM(DATADIR_INST, 0x50),
    DATA_MAKE_NUM(DATADIR_INST, 0x51),
    DATA_MAKE_NUM(DATADIR_INST, 0x52),
    DATA_MAKE_NUM(DATADIR_INST, 0x53),
    DATA_MAKE_NUM(DATADIR_INST, 0x54),
    DATA_MAKE_NUM(DATADIR_INST, 0x55),
    DATA_MAKE_NUM(DATADIR_INST, 0x56),
    DATA_MAKE_NUM(DATADIR_INST, 0x57),
    DATA_MAKE_NUM(DATADIR_INST, 0x58),
    DATA_MAKE_NUM(DATADIR_INST, 0x59),
    DATA_MAKE_NUM(DATADIR_INST, 0x5A),
    DATA_MAKE_NUM(DATADIR_INST, 0x5B),
    DATA_MAKE_NUM(DATADIR_INST, 0x5C),
    DATA_MAKE_NUM(DATADIR_INST, 0x5D),
    DATA_MAKE_NUM(DATADIR_INST, 0x5E),
    DATA_MAKE_NUM(DATADIR_INST, 0x5F),
    DATA_MAKE_NUM(DATADIR_INST, 0x60),
    DATA_MAKE_NUM(DATADIR_INST, 0x61),
    DATA_MAKE_NUM(DATADIR_INST, 0x62),
    DATA_MAKE_NUM(DATADIR_INST, 0x63),
    DATA_MAKE_NUM(DATADIR_INST, 0x64),
    DATA_MAKE_NUM(DATADIR_INST, 0x65),
    DATA_MAKE_NUM(DATADIR_INST, 0x66),
    DATA_MAKE_NUM(DATADIR_INST, 0x67),
#if VERSION_PAL
    DATA_MAKE_NUM(DATADIR_INST, 0x68),
#endif
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
#if VERSION_PAL
    DATA_MAKE_NUM(DATADIR_INST, 0x34),
#else
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
#endif
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x2F),
    DATA_MAKE_NUM(DATADIR_INST, 0x33),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
#if VERSION_PAL
    DATA_MAKE_NUM(DATADIR_INST, 0x69),
    DATA_MAKE_NUM(DATADIR_INST, 0x6A),
    DATA_MAKE_NUM(DATADIR_INST, 0x6B),
    DATA_MAKE_NUM(DATADIR_INST, 0x6C),
    DATA_MAKE_NUM(DATADIR_INST, 0x6D),
    DATA_MAKE_NUM(DATADIR_INST, 0x6E),
    DATA_MAKE_NUM(DATADIR_INST, 0x6F),
    DATA_MAKE_NUM(DATADIR_INST, 0x70),
    DATA_MAKE_NUM(DATADIR_INST, 0x71),
    DATA_MAKE_NUM(DATADIR_INST, 0x72),
    DATA_MAKE_NUM(DATADIR_INST, 0x73),
    DATA_MAKE_NUM(DATADIR_INST, 0x74),
    DATA_MAKE_NUM(DATADIR_INST, 0x75),
    DATA_MAKE_NUM(DATADIR_INST, 0x76),
    DATA_MAKE_NUM(DATADIR_INST, 0x77),
#else
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
#endif
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x30),
    DATA_MAKE_NUM(DATADIR_INST, 0x31),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
#if VERSION_PAL
    DATA_MAKE_NUM(DATADIR_INST, 0x8F),
    DATA_MAKE_NUM(DATADIR_INST, 0x8E),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x78),
    DATA_MAKE_NUM(DATADIR_INST, 0x79),
    DATA_MAKE_NUM(DATADIR_INST, 0x7A),
    DATA_MAKE_NUM(DATADIR_INST, 0x7B),
    DATA_MAKE_NUM(DATADIR_INST, 0x7C),
    DATA_MAKE_NUM(DATADIR_INST, 0x7D),
    DATA_MAKE_NUM(DATADIR_INST, 0x7E),
    DATA_MAKE_NUM(DATADIR_INST, 0x7F),
    DATA_MAKE_NUM(DATADIR_INST, 0x80),
    DATA_MAKE_NUM(DATADIR_INST, 0x81),
    DATA_MAKE_NUM(DATADIR_INST, 0x82),
    DATA_MAKE_NUM(DATADIR_INST, 0x83),
    DATA_MAKE_NUM(DATADIR_INST, 0x84),
    DATA_MAKE_NUM(DATADIR_INST, 0x85),
    DATA_MAKE_NUM(DATADIR_INST, 0x86),
    DATA_MAKE_NUM(DATADIR_INST, 0x87),
    DATA_MAKE_NUM(DATADIR_INST, 0x88),
    DATA_MAKE_NUM(DATADIR_INST, 0x89),
    DATA_MAKE_NUM(DATADIR_INST, 0x8A),
    DATA_MAKE_NUM(DATADIR_INST, 0x8B),
    DATA_MAKE_NUM(DATADIR_INST, 0x8C),
    DATA_MAKE_NUM(DATADIR_INST, 0x8D),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
    DATA_MAKE_NUM(DATADIR_INST, 0x25),
#endif
};

s32 FontCreate(SeqWork *work, char *mess, s16 jp_flag)
{
    char *str;
    s16 len;
    s16 *posY;
    s16 charNum;
    s32 *fileTbl;
    s16 i;
    s16 grpNo;
    s16 *posX;
    AnimData **animP;
    s16 gid;
    s16 sprid;
    s32 file;

    fileTbl = FontCharFile;
    for (grpNo = 0; grpNo < 0x10; grpNo++) {
        if (work->spr_grp[grpNo] == -1) {
            break;
        }
    }
    if (grpNo == 0x10) {
        return -1;
    }
    animP = HuMemDirectMalloc(HEAP_SYSTEM, (FONT_CHAR_MAX * sizeof(AnimData*)));
    posX = HuMemDirectMalloc(HEAP_SYSTEM, FONT_CHAR_MAX * sizeof(*posX));
    posY = HuMemDirectMalloc(HEAP_SYSTEM, FONT_CHAR_MAX * sizeof(*posY));

    for (str = mess, len = 0, charNum = 0; str[0] != 0; str++) {
        if (str[0] == 0x20 || str[0] == 0x10) {
            len += 0xE;
        }
        else if (str[0] < 0x30) {
        }
#if VERSION_NTSC
        else if (str[0] == 0x80) {
        }
        else if (str[0] == 0x81) {
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
#else
        else {
            file = fileTbl[str[0]];
#endif
            animP[charNum] = HuSprAnimReadFile(file);
            posX[charNum] = len;
            if ((str[0] >= 0x61) && (str[0] <= 0x7A)) {
                posY[charNum] = 2;
                len += 0x12;
            }
#if VERSION_PAL
            else if ((str[0] == 0xC2) || (str[0] == 0xC3) || (str[0] == 0xC7)) {
#else
            else if ((str[0] == 0xC2) || (str[0] == 0xC3)) {
#endif
                posY[charNum] = 0;
                len += 0x12;
            }
#if VERSION_PAL
            else if (str[0] == 0xC6) {
                posY[charNum] = 0;
                len += 0x18;
            }
            else if (str[0] == 0x5C) {
                posY[charNum] = 0;
                len += 8;
            }
            else if ((str[0] == 0x85) || (str[0] == 0x82)) {
                posY[charNum] = 0;
                len += 0xC;
            }
            else if (str[0] == 0x94) {
                posY[charNum] = -2;
                len += 0x18;
            }
            else if ((str[0] >= 0x90) && (str[0] <= 0x9F)) {
                posY[charNum] = -2;
                len += 0x18;
            }
            else if ((str[0] >= 0xD0) && (str[0] <= 0xEF)) {
                posY[charNum] = -2;
                len += 0x12;
            }
#else
            else if (str[0] == 0x5C || str[0] == 0x85) {
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
#endif
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
    work->spr_grp[grpNo] = gid;
    work->alt_word_len = len;
    len = (len / 2) - 0xE;
    for (i = 0; i < charNum; i++) {
        sprid = HuSprCreate(animP[i], 0, 0);
        HuSprGrpMemberSet(gid, i, sprid);
        HuSprPosSet(gid, i, posX[i] - len, posY[i]);
    }
    work->word_len = charNum;
    HuMemDirectFree(animP);
    HuMemDirectFree(posX);
    HuMemDirectFree(posY);
    return grpNo;
}
