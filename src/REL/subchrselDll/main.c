#include "game/audio.h"
#include "game/object.h"
#include "game/gamework_data.h"
#include "game/printfunc.h"
#include "game/pad.h"
#include "game/wipe.h"

#ifndef __MWERKS__
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#endif

#include "math.h"

static void SubchrMain(void);

static u8 dirPlayer[4];

static char *playerNumTbl[4] = {
    "PLAYER1",
    "PLAYER2",
    "PLAYER3",
    "PLAYER4"
};

static char *charNameTbl[8] = {
    "MARIO",
    "LUIGI",
    "PEACH",
    "YOSHI",
    "WARIO",
    "DONKEY",
    "DAISY",
    "WALUIGI"
};

static char *extCharNameTbl[7] = {
    "",
    "KOOPA",
    "KINOPIO",
    "HEIHOH",
    "TERESA",
    "NOKO2",
    "MKOOPA"
};

void ObjectSetup(void)
{
    Process *sp8 = omInitObjMan(0x32, 0x2000);
    Hu3DBGColorSet(0, 0, 0);
    HuPrcChildCreate(SubchrMain, 4096, 12288, 0, HuPrcCurrentGet());
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
}

static u16 GetBtns(void)
{
    u16 btns;

    btns = HuPadBtnDown[0];
    if (dirPlayer[0] != HuPadDStk[0]) {
        btns |= HuPadDStk[0];
    }
    return btns;
}

static void SubchrMain()
{
    int character[4];
    int ext_character[4];
    int i, cursor_pos;
    for(i=0; i<4; i++) {
        character[i] = GWPlayerCfg[i].character;
        ext_character[i] = 0;
        dirPlayer[i] = 0;
    }
    cursor_pos = 0;
    while(1) {
        int y, x;
        u16 btns;
        fontcolor = FONT_COLOR_YELLOW;
        print8(150, 64, 2.0f, "Sub Character Select");
        x = 170;
        y = 120;
        for(i=0; i<4; i++, y += 16) {
            fontcolor = FONT_COLOR_GREEN;
            print8(x, y, 2.0f, playerNumTbl[i]);
            if(i == cursor_pos) {
                fontcolor = FONT_COLOR_CYAN;
            } else {
                fontcolor = FONT_COLOR_GREEN;
            }
            if(ext_character[i] != 0) {
                print8(x+200, y, 2.0f, extCharNameTbl[ext_character[i]]);
            } else {
                print8(x+200, y, 2.0f, charNameTbl[character[i]]);
            }
        }
        if(GetBtns() & PAD_BUTTON_START) {
            for(i=0; i<4; i++) {
                if(ext_character[i] != 0) {
                    GWPlayerCfg[i].character = ext_character[i]+7;
                }
            }
            HuAudFadeOut(30);
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
            HuPrcSleep(wipeData.duration+1.0f);
            MGSeqKillAll();
            omOvlGotoEx(OVL_M433, 1, 0, 0);
            do {
                HuPrcVSleep();
            } while(1);
        } else {
            if(GetBtns() & PAD_BUTTON_LEFT) {
                do {
                    ext_character[cursor_pos]--;
                    if(ext_character[cursor_pos] < 0) {
                        ext_character[cursor_pos] = 6;
                    }
                    for(i=0; i<4; i++) {
                        if(cursor_pos != i) {
                            if(ext_character[cursor_pos] == ext_character[i] && ext_character[cursor_pos] != 0) {
                                break;
                            }
                        }
                    }
                } while(i < 4);
            }
            if(GetBtns() & PAD_BUTTON_RIGHT) {
                do {
                    ext_character[cursor_pos]++;
                    if(ext_character[cursor_pos] > 6) {
                        ext_character[cursor_pos] = 0;
                    }
                    for(i=0; i<4; i++) {
                        if(cursor_pos != i) {
                            if(ext_character[cursor_pos] == ext_character[i] && ext_character[cursor_pos] != 0) {
                                break;
                            }
                        }
                    }
                } while(i < 4);
            }
            if(GetBtns() & PAD_BUTTON_DOWN) {
                cursor_pos++;
            }
            if(GetBtns() & PAD_BUTTON_UP) {
                cursor_pos--;
            }
            if(cursor_pos < 0) {
                cursor_pos = 3;
            }
            if(cursor_pos > 3) {
                cursor_pos = 0;
            }
            if(GetBtns() & PAD_BUTTON_B) {
                HuAudFadeOut(30);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
                HuPrcSleep(wipeData.duration+1.0f);
                MGSeqKillAll();
                omOvlReturnEx(1, 1);
                do {
                    HuPrcVSleep();
                } while(1);
            } else {
                if(dirPlayer[0] != HuPadDStk[0]) {
                    dirPlayer[0] = HuPadDStk[0];
                }
            }
        }
        HuPrcVSleep();
    }
}
