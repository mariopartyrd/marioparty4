#include "game/sprite.h"
#include "game/minigame_seq.h"

#include "REL/ztardll.h"

s32 lbl_1_data_B0[0xC6] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x01), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x02),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x03), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x04), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x05),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x06), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x07), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x08),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x09), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x0A), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x0F),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x10), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x11), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x12),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x13), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x14), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x15),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x16), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x17), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x18),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x19), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1A), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1B),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1C), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1D), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1E),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1F), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x20), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x21),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x22), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x23), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x24),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x25), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x26), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x27),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x28), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1D), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x0D),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1D), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1D), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1D),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x1D), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x29), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x2A),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x2B), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x2C), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x2D),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x2E), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x2F), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x30),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x31), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x32), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x33),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x34), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x35), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x36),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x37), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x38), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x39),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x3A), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x3B), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x3C),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x3D), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x3E), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x3F),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x40), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x41), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x42),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x0A), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x0E), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x0B),
    DATA_MAKE_NUM(DATADIR_INSTFONT, 0x0C), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00), DATA_MAKE_NUM(DATADIR_INSTFONT, 0x00) };

s32 fn_1_7754(SeqWork *work, char *mess)
{
    char *var_r31;
    s16 var_r30;
    s16 *var_r29;
    s16 var_r28;
    s32 *var_r27;
    s16 var_r26;
    s16 var_r25;
    s32 var_r24;
    s16 *var_r22;
    AnimData **var_r21;
    s16 var_r20;
    s16 var_r19;

    var_r27 = lbl_1_data_B0;
    for (var_r25 = 0; var_r25 < 0x10; var_r25++) {
        if (work->spr_grp[var_r25] == -1) {
            break;
        }
    }
    if (var_r25 == 0x10) {
        return -1;
    }
    var_r21 = HuMemDirectMalloc(HEAP_SYSTEM, 0x190);
    var_r22 = HuMemDirectMalloc(HEAP_SYSTEM, 0xC8);
    var_r29 = HuMemDirectMalloc(HEAP_SYSTEM, 0xC8);
    for (var_r31 = mess, var_r30 = 0, var_r28 = 0; var_r31[0] != 0; var_r31++) {
        if (var_r31[0] == 0x20 || var_r31[0] == 0x10) {
            var_r30 += 0xE;
        }
        else if (var_r31[0] < 0x30) {
        }
        else if (var_r31[0] == 0x80) {
        }
        else if (var_r31[0] == 0x81) {
        }
        else {
            if (var_r31[1] == 0x80) {
                if ((var_r31[0] >= 0x96) && (var_r31[0] <= 0xA4)) {
                    var_r24 = var_r27[var_r31[0] + 0x6A];
                }
                else if ((var_r31[0] >= 0xAA) && (var_r31[0] <= 0xAE)) {
                    var_r24 = var_r27[var_r31[0] + 0x65];
                }
                else if ((var_r31[0] >= 0xD6) && (var_r31[0] <= 0xE4)) {
                    var_r24 = var_r27[var_r31[0] + 0x43];
                }
                else if ((var_r31[0] >= 0xEA) && (var_r31[0] <= 0xEE)) {
                    var_r24 = var_r27[var_r31[0] + 0x3E];
                }
            }
            else if (var_r31[1] == 0x81) {
                if ((var_r31[0] >= 0xAA) && (var_r31[0] <= 0xAE)) {
                    var_r24 = var_r27[var_r31[0] + 0x6A];
                }
                else if ((var_r31[0] >= 0xEA) && (var_r31[0] <= 0xEE)) {
                    var_r24 = var_r27[var_r31[0] + 0x43];
                }
            }
            else {
                var_r24 = var_r27[var_r31[0]];
            }
            var_r21[var_r28] = HuSprAnimReadFile(var_r24);
            var_r22[var_r28] = var_r30;
            if ((var_r31[0] >= 0x61) && (var_r31[0] <= 0x7A)) {
                var_r29[var_r28] = 2;
                var_r30 += 0x12;
            }
            else if ((var_r31[0] == 0xC2) || (var_r31[0] == 0xC3)) {
                var_r29[var_r28] = 0;
                var_r30 += 0x12;
            }
            else if (var_r31[0] == 0x5C) {
                var_r29[var_r28] = 0;
                var_r30 += 8;
            }
            else if ((var_r31[0] >= 0x87) && (var_r31[0] <= 0x8F)) {
                var_r29[var_r28] = 4;
                var_r30 += 0x18;
            }
            else if ((var_r31[0] >= 0xC7) && (var_r31[0] <= 0xCF)) {
                var_r29[var_r28] = 4;
                var_r30 += 0x18;
            }
            else if ((var_r31[0] == 0x3D) || (var_r31[0] == 0x84)) {
                var_r29[var_r28] = 0;
                var_r30 += 0x14;
            }
            else {
                var_r29[var_r28] = 0;
                var_r30 += 0x1C;
            }
            var_r28++;
        }
    }
    var_r20 = HuSprGrpCreate(var_r28);
    work->spr_grp[var_r25] = var_r20;
    work->alt_word_len = var_r30;
    var_r30 = (var_r30 / 2) - 0xE;
    for (var_r26 = 0; var_r26 < var_r28; var_r26++) {
        var_r19 = HuSprCreate(var_r21[var_r26], 0, 0);
        HuSprGrpMemberSet(var_r20, var_r26, var_r19);
        HuSprPosSet(var_r20, var_r26, var_r22[var_r26] - var_r30, var_r29[var_r26]);
    }
    work->word_len = var_r28;
    HuMemDirectFree(var_r21);
    HuMemDirectFree(var_r22);
    HuMemDirectFree(var_r29);
    return var_r25;
}
