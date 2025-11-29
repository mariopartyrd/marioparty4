#include "game/board/com.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/board/com_path.h"
#include "game/board/main.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/tutorial.h"
#include "game/board/window.h"
#include "game/board/boo.h"
#include "game/chrman.h"

#include "ext_math.h"

typedef BOOL (*UseCheckFunc)(s32 player, s32 item);

static void ExecComKeyLeft(void);
static void ExecComKeyRight(void);
static void ExecComKeyUp(void);
static void ExecComKeyDown(void);
static void ExecComKey(s32 player, s32 move, s32 vertical);
static s32 ChooseUseItem(s32 player);
static BOOL CheckMiniUse(s32 player, s32 item);
static BOOL CheckMegaUse(s32 player, s32 item);
static BOOL CheckSparkUse(s32 player, s32 item);
static BOOL CheckBoardChangeUse(s32 player, s32 item);
static BOOL CheckSwapUse(s32 player, s32 item);
static BOOL CheckBooUse(s32 player, s32 item);
static BOOL CheckLampUse(s32 player, s32 item);

static s8 itemUse = -1;

static s8 comItemPreferTbl[CHARNO_MAX ][SHOP_ITEMS_END] = {
    {   //Mario
        BOARD_ITEM_MAGIC_LAMP,
        BOARD_ITEM_BOOS_CRYSTAL_BALL,
        BOARD_ITEM_WARP_PIPE,
        BOARD_ITEM_SUPER_MEGA_MUSHROOM,
        BOARD_ITEM_MEGA_MUSHROOM,
        BOARD_ITEM_SUPER_MINI_MUSHROOM,
        BOARD_ITEM_SWAP_CARD,
        BOARD_ITEM_MINI_MEGA_HAMMER,
        BOARD_ITEM_MINI_MUSHROOM,
        BOARD_ITEM_SPARKY_STICKER,
        BOARD_ITEM_CHOMP_CALL,
        BOARD_ITEM_BOWSER_SUIT
    },
    {   //Luigi
        BOARD_ITEM_MAGIC_LAMP,
        BOARD_ITEM_BOOS_CRYSTAL_BALL,
        BOARD_ITEM_WARP_PIPE,
        BOARD_ITEM_BOWSER_SUIT,
        BOARD_ITEM_SUPER_MEGA_MUSHROOM,
        BOARD_ITEM_MEGA_MUSHROOM,
        BOARD_ITEM_SUPER_MINI_MUSHROOM,
        BOARD_ITEM_MINI_MUSHROOM,
        BOARD_ITEM_SWAP_CARD,
        BOARD_ITEM_MINI_MEGA_HAMMER,
        BOARD_ITEM_SPARKY_STICKER,
        BOARD_ITEM_CHOMP_CALL
    },   
    {   //Peach
        BOARD_ITEM_MAGIC_LAMP,
        BOARD_ITEM_BOOS_CRYSTAL_BALL,
        BOARD_ITEM_WARP_PIPE,
        BOARD_ITEM_SWAP_CARD,
        BOARD_ITEM_SUPER_MEGA_MUSHROOM,
        BOARD_ITEM_MEGA_MUSHROOM,
        BOARD_ITEM_SUPER_MINI_MUSHROOM,
        BOARD_ITEM_BOWSER_SUIT,
        BOARD_ITEM_SPARKY_STICKER,
        BOARD_ITEM_CHOMP_CALL,
        BOARD_ITEM_MINI_MUSHROOM,
        BOARD_ITEM_MINI_MEGA_HAMMER
    },   
    {   //Yoshi
        BOARD_ITEM_MAGIC_LAMP,
        BOARD_ITEM_WARP_PIPE,
        BOARD_ITEM_BOOS_CRYSTAL_BALL,
        BOARD_ITEM_CHOMP_CALL,
        BOARD_ITEM_SUPER_MEGA_MUSHROOM,
        BOARD_ITEM_MEGA_MUSHROOM,
        BOARD_ITEM_SUPER_MINI_MUSHROOM,
        BOARD_ITEM_SWAP_CARD,
        BOARD_ITEM_MINI_MUSHROOM,
        BOARD_ITEM_MINI_MEGA_HAMMER,
        BOARD_ITEM_BOWSER_SUIT,
        BOARD_ITEM_SPARKY_STICKER
    },    
    {   //Wario
        BOARD_ITEM_MAGIC_LAMP,
        BOARD_ITEM_BOOS_CRYSTAL_BALL,
        BOARD_ITEM_MINI_MEGA_HAMMER,
        BOARD_ITEM_CHOMP_CALL,
        BOARD_ITEM_BOWSER_SUIT,
        BOARD_ITEM_SUPER_MEGA_MUSHROOM,
        BOARD_ITEM_MEGA_MUSHROOM,
        BOARD_ITEM_WARP_PIPE,
        BOARD_ITEM_SUPER_MINI_MUSHROOM,
        BOARD_ITEM_SWAP_CARD,
        BOARD_ITEM_MINI_MUSHROOM,
        BOARD_ITEM_SPARKY_STICKER
    },   
    {   //DK
        BOARD_ITEM_MAGIC_LAMP,
        BOARD_ITEM_BOOS_CRYSTAL_BALL,
        BOARD_ITEM_WARP_PIPE,
        BOARD_ITEM_SUPER_MEGA_MUSHROOM,
        BOARD_ITEM_MEGA_MUSHROOM,
        BOARD_ITEM_BOWSER_SUIT,
        BOARD_ITEM_SWAP_CARD,
        BOARD_ITEM_SUPER_MINI_MUSHROOM,
        BOARD_ITEM_MINI_MUSHROOM,
        BOARD_ITEM_MINI_MEGA_HAMMER,
        BOARD_ITEM_CHOMP_CALL,
        BOARD_ITEM_SPARKY_STICKER
    },   
    {   //Daisy
        BOARD_ITEM_MAGIC_LAMP,
        BOARD_ITEM_WARP_PIPE,
        BOARD_ITEM_BOOS_CRYSTAL_BALL,
        BOARD_ITEM_MINI_MEGA_HAMMER,
        BOARD_ITEM_SPARKY_STICKER,
        BOARD_ITEM_CHOMP_CALL,
        BOARD_ITEM_SUPER_MEGA_MUSHROOM,
        BOARD_ITEM_MEGA_MUSHROOM,
        BOARD_ITEM_BOWSER_SUIT,
        BOARD_ITEM_SWAP_CARD,
        BOARD_ITEM_SUPER_MINI_MUSHROOM,
        BOARD_ITEM_MINI_MUSHROOM
    },   
    {   //Waluigi
        BOARD_ITEM_MAGIC_LAMP,
        BOARD_ITEM_WARP_PIPE,
        BOARD_ITEM_SPARKY_STICKER,
        BOARD_ITEM_BOOS_CRYSTAL_BALL,
        BOARD_ITEM_BOWSER_SUIT,
        BOARD_ITEM_CHOMP_CALL,
        BOARD_ITEM_MINI_MEGA_HAMMER,
        BOARD_ITEM_SWAP_CARD,
        BOARD_ITEM_SUPER_MEGA_MUSHROOM,
        BOARD_ITEM_MEGA_MUSHROOM,
        BOARD_ITEM_SUPER_MINI_MUSHROOM,
        BOARD_ITEM_MINI_MUSHROOM
    }
};

static UseCheckFunc comItemUseCheckFuncTbl[] = {
    CheckMiniUse,
    CheckMegaUse,
    CheckMiniUse,
    CheckMegaUse,
    CheckBoardChangeUse,
    CheckBoardChangeUse,
    CheckSwapUse,
    CheckSparkUse,
    NULL,
    CheckBoardChangeUse,
    NULL,
    CheckBooUse,
    CheckLampUse,
    NULL
};

static Vec comJunctionDirTbl[] = {
    {   0.0f,   0.0f, -72.0f },
    {  90.0f,  72.0f,   0.0f },
    { 180.0f,   0.0f,  72.0f },
    { 270.0f, -72.0f,   0.0f }
};

static void ExecComKeyLeft(void) {
    ExecComKey(GWSystem.player_curr, 0, 1);
}

void BoardComKeySetLeft(void) {
    BoardWinComKeyFuncSet(ExecComKeyLeft);
}

static void ExecComKeyRight(void) {
    ExecComKey(GWSystem.player_curr, 1, 1);
}

void BoardComKeySetRight(void) {
    BoardWinComKeyFuncSet(ExecComKeyRight);
}

static void ExecComKeyUp(void) {
    ExecComKey(GWSystem.player_curr, 0, 0);
}

void BoardComKeySetUp(void) {
    BoardWinComKeyFuncSet(ExecComKeyUp);
}

static void ExecComKeyDown(void) {
    ExecComKey(GWSystem.player_curr, 1, 0);
}

void BoardComKeySetDown(void) {
    BoardWinComKeyFuncSet(ExecComKeyDown);
}

static void ExecComKey(s32 player, s32 move, s32 vertical) {
    s32 comkey[4];
    s32 port;
    s16 delay;
    s32 dpad;

    comkey[0] = comkey[1] = comkey[2] = comkey[3] = 0;
    port = GWPlayer[player].port;
    delay = GWMessDelayGet();
    if (vertical == 0) {
        dpad = PAD_BUTTON_DOWN;
    } else {
        dpad = PAD_BUTTON_RIGHT;
    }
    if (move == 1) {
        comkey[port] = dpad;
        HuWinComKeyWait(comkey[0], comkey[1], comkey[2], comkey[3], delay);
    }
    comkey[port] = 0x100;
    HuWinComKeyWait(comkey[0], comkey[1], comkey[2], comkey[3], delay);
}

s8 BoardComPreferItemGet(s32 player, s8 *items, s8 num_items) {
    s32 character;
    s32 weight;
    s32 item;
    s32 prefer;
    s32 i;
    s32 j;

    character = GWPlayer[player].character;
    prefer = -1;
    weight = 100;
    for (i = 0; i < num_items; i++) {
        item = items[i];
        for (j = 0; j < SHOP_ITEMS_END; j++) {
            if (item == comItemPreferTbl[character][j]) {
                if (j < weight && (BoardPlayerItemFind(player, item) == -1 || item == BOARD_ITEM_MAGIC_LAMP || item == BOARD_ITEM_BOOS_CRYSTAL_BALL)) {
                    weight = j;
                    prefer = i;
                }
                break;
            }
        }
    }
    if (weight == 100) {
        return -1;
    }
    return prefer;
}

s8 BoardComPreferItemCheck(s32 player, s8 item1, s8 item2, s8 item3) {
    s8 items[3];
    s8 prefer;

    items[0] = item1;
    items[1] = item2;
    items[2] = item3;
    prefer = BoardComPreferItemGet(player, items, 3);
    return prefer;
}

s32 BoardComItemWeightGet(s32 player, s32 item) {
    s32 weight;
    s32 i;

    for (i = 0; i < SHOP_ITEMS_END; i++) {
        if (item == comItemPreferTbl[GWPlayer[player].character][i]) {
            break;
        }
    }
    weight = 12-1-i;
    return weight;
}

s32 BoardComUseItemSlotGet(s32 player) {
    s32 slot;
    s32 item;

    if (!GWPlayer[player].com) {
        return -1;
    }
    if (itemUse != -1) {
        item = itemUse;
    }
    if (boardTutorialUseItem >= 0 && boardTutorialUseItem <= 13) {
        item = boardTutorialUseItem;
        boardTutorialUseItem = -1;
    }
    if (item != -1) {
        slot = BoardPlayerItemFind(player, item);
    } else {
        slot = -1;
    }
    return slot;
}

s32 BoardComUseItemSet(s32 player, s32 item) {
    if (item == -1) {
        itemUse = -1;
        return 1;
    }
    if (BoardPlayerItemFind(player, item) != -1) {
        itemUse = item;
        return 1;
    }
    return 0;
}

BOOL BoardComUseItemCheck(s32 player) {
    s32 count;

    count = BoardPlayerItemCount(player);
    if (count <= 0) {
        return FALSE;
    }
    if (ChooseUseItem(player) != -1) {
        return TRUE;
    }
    return FALSE;
}

static s32 ChooseUseItem(s32 player) {
    s32 i;
    s32 j;
    s32 useItem;
    s32 weight;
    s32 item;
    s32 character;
    UseCheckFunc func;
    s8 result;

    useItem = -1;
    character = GWPlayer[player].character;
    weight = 100;
    for (i = 0; i < 3; i++) {
        item = GWPlayer[player].items[i];
        if (item == -1) {
            continue;
        }
        func = comItemUseCheckFuncTbl[item];
        if (!func) {
            continue;
        }
        result = func(player, item);
        if (result) {
            for (j = 0; j < SHOP_ITEMS_END; j++) {
                if (item == comItemPreferTbl[character][j]) {
                    if (j < weight) {
                        weight = j;
                    }
                    break;
                }
            }
        }
    }
    if (weight == 100) {
        return -1;
    }
    useItem = comItemPreferTbl[character][weight];
    if (useItem == -1) {
        itemUse = -1;
    } else if (BoardPlayerItemFind(player, useItem) != -1) {
        itemUse = useItem;
    }
    return useItem;
}

static BOOL CheckMiniUse(s32 player, s32 item) {
    s32 space;
    s32 star_dist_pipe;
    s32 star_dist_no_pipe;
    s32 diff;
    s32 character;
    s32 force_use_mini;
    s32 max_dist;
    s32 chance;

    force_use_mini = 0;
    space = GWPlayer[player].space_curr;
    diff = GWPlayer[player].diff;
    character = GWPlayer[player].character;
    switch (diff) {
        case 0:
            chance = 50;
            break;
        case 1:
            chance = 25;
            break;
        case 2:
            chance = 5;
            break;
        case 3:
            chance = 0;
            break;
    }
    if ((diff == 0 || diff == 1) && character == 1) {
        chance = 7;
    }
    if (GWBoardGet() != BOARD_ID_EXTRA1 && GWBoardGet() != BOARD_ID_EXTRA2) {
        star_dist_pipe = BoardComPathShortcutLenGet(space, 8, 0);
        star_dist_no_pipe = BoardComPathShortcutLenGet(space, 8, 1);
    } else {
        star_dist_pipe = 999;
        star_dist_no_pipe = BoardComPathBestGetFlag(space, 0x10000000, 10);
        if ((GWBoardGet() == BOARD_ID_EXTRA2 || GWBoardGet() == BOARD_ID_EXTRA1) && BoardRandMod(100) < 60) {
            force_use_mini = 1;
        }
    }
    switch (GWPlayer[player].diff) {
        case 0:
            max_dist = 5;
            break;
        case 1:
            max_dist = 7;
            break;
        case 2:
            max_dist = 9;
            break;
        case 3:
            max_dist = 10;
            break;
    }
    if ((star_dist_no_pipe < max_dist || star_dist_pipe < max_dist || force_use_mini != 0) && BoardRandMod(100) >= chance) {
        return TRUE;
    }
    return FALSE;
}

static BOOL CheckMegaUse(s32 player, s32 item) {
    s32 short_len;
    s32 character;
    s32 space;
    s32 diff;
    s16 path_len;
    s16 max_len;
    s16 space_search;
    s16 space_other;
    s16 i;

    diff = GWPlayer[player].diff;
    character = GWPlayer[player].character;
    switch (diff) {
        case 0:
            max_len = 5;
            break;
        case 1:
            max_len = 7;
            break;
        case 2:
            max_len = 9;
            break;
        case 3:
            max_len = 10;
            break;
    }
    if (((diff == 0 || diff == 1) && character == 0) || ((diff == 0 || diff == 1) && character == 5)) {
        max_len = 8;
    }
    if (GWBoardGet() != BOARD_ID_EXTRA1 || BoardRandMod(100) >= 60) {
        space = GWPlayer[player].space_curr;
        short_len = BoardComPathShortcutLenGet(space, 8, 0);
        space_search = GWPlayer[player].space_curr;
        for (i = 0; i < 4; i++) {
            if (i != player) {
                space_other = GWPlayer[i].space_curr;
                path_len = BoardComPathLenGet(space_search, space_other);
                if (path_len < max_len + 20 && path_len > 0 && GWTeamGet() && i == BoardPlayerSameTeamFind(player)) {
                    return FALSE;
                }
            }
        }
        if (GWBoardGet() != BOARD_ID_EXTRA1 && GWBoardGet() != BOARD_ID_EXTRA2 && short_len < 10 && short_len > 0) {
            return FALSE;
        }
    }
    if (BoardPlayerItemFind(player, item) != -1) {
        return TRUE;
    }
    return FALSE;
}

static BOOL CheckSparkUse(s32 player, s32 item) {
    s32 length;
    s32 diff;
    s32 space_other;
    s32 space;
    s32 character;
    s32 i;
    s32 chance;

    space = GWPlayer[player].space_curr;
    diff = GWPlayer[player].diff;
    character = GWPlayer[player].character;
    switch (diff) {
        case 0:
            chance = 50;
            break;
        case 1:
            chance = 25;
            break;
        case 2:
            chance = 5;
            break;
        case 3:
            chance = 0;
            break;
    }
    if ((diff == 0 || diff == 1) && character == 7) {
        chance = 7;
    }
    for (i = 0; i < 4; i++) {
        if (i != player) {
            space_other = GWPlayer[i].space_curr;
            length = BoardComPathLenGet(space_other, space);
            if (length > 0 && length <= 15 && BoardPlayerItemFind(player, item) != -1 && BoardRandMod(0x64) >= chance) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

static BOOL CheckBoardChangeUse(s32 player, s32 item) {
    s32 diff;
    s32 character;
    s32 mini_len;
    s32 non_mini_len;
    s32 search_space;
    s32 space;
    s32 length_min;
    s32 length;
    s32 chance;
    s32 i;

    diff = GWPlayer[player].diff;
    character = GWPlayer[player].character;
    switch (diff) {
        case 0:
            chance = 0x32;
            break;
        case 1:
            chance = 0x19;
            break;
        case 2:
            chance = 5;
            break;
        case 3:
            chance = 0;
            break;
    }
    if (((item == 4 && character == 4) || (item == 5 && (character == 6 || character == 3))) && (diff == 0 || diff == 1)) {
        chance = 7;
    }
    length_min = 999;
    for (i = 0; i < 4; i++) {
        if (player == i) {
            continue;
        }
        search_space = GWPlayer[i].space_curr;
        if (!GWTeamGet() || i != BoardPlayerSameTeamFind(player)) {
            space = GWPlayer[i].space_curr;
            if (GWBoardGet() == BOARD_ID_EXTRA1) {
                if (BoardComPathBestGetFlag(search_space, 0x10000000, 10) != -1) {
                    length = 10;
                } else {
                    length = 0;
                }
            } else if (GWBoardGet() == BOARD_ID_EXTRA2) {
                if (BoardComPathBestGetFlag(search_space, 0x200000, 10) != -1 || BoardComPathBestGetFlag(search_space, 0x400000, 10) != -1) {
                    length = 10;
                } else {
                    length = 0;
                }
            } else {
                length = BoardComPathShortcutLenGet(space, 8, 0);
            }
            if (length != 0 && length < length_min) {
                length_min = length;
            }
        }
    }
    if ((length_min > 0xF && length_min != 999) || (GWTeamGet() && i == BoardPlayerSameTeamFind(player))) {
        return FALSE;
    }
    space = GWPlayer[player].space_curr;
    mini_len = BoardComPathShortcutLenGet(space, 8, 0);
    non_mini_len = BoardComPathShortcutLenGet(space, 8, 1);
    if (BoardPlayerItemFind(player, item) != -1 && BoardRandMod(0x64) >= chance) {
        if ((mini_len == 0 || non_mini_len == 0) && length_min == 999) {
            return TRUE;
        }
        if (mini_len > length_min || non_mini_len > length_min) {
            return TRUE;
        }
        if (mini_len > 10 || non_mini_len > 10) {
            return TRUE;
        }
    }
    return FALSE;
}

static BOOL CheckSwapUse(s32 player, s32 item) {
    s32 diff;
    s32 team_player;
    s32 character;
    s32 item_count;
    s32 chance;
    s32 i;

    diff = GWPlayer[player].diff;
    character = GWPlayer[player].character;
    switch (diff) {
        case 0:
            chance = 0x32;
            break;
        case 1:
            chance = 0x19;
            break;
        case 2:
            chance = 5;
            break;
        case 3:
            chance = 0;
            break;
    }
    if ((diff == 0 || diff == 1) && character == 2) {
        chance = 7;
    }
    for (item_count = i = 0; i < 4; i++) {
        if (i != player) {
            item_count += BoardPlayerItemCount(i);
        }
    }
    if (item_count == 0) {
        return FALSE;
    }
    if (GWTeamGet()) {
        team_player = BoardPlayerSameTeamFind(player);
        for (item_count = i = 0; i < 4; i++) {
            if (team_player != i && i != player) {
                item_count += BoardPlayerItemCount(i);
            }
        }
        if (item_count == 0) {
            return FALSE;
        }
    }
    if (BoardPlayerItemFind(player, item) != -1 && BoardRandMod(0x64) >= chance) {
        return TRUE;
    }
    return FALSE;
}

static BOOL CheckBooUse(s32 player, s32 item) {
    if (BoardPlayerCoinsGet(player) < 5) {
        return FALSE;
    }
    if (BoardBooComUseCheck(player) == 0) {
        return FALSE;
    }
    if (BoardPlayerItemFind(player, item) == -1) {
        return FALSE;
    }
    return TRUE;
}

static BOOL CheckLampUse(s32 player, s32 item) {
    if ((BoardPlayerCoinsGet(player) >= 0x14 || GWSystem.last5_effect == 4) && BoardPlayerItemFind(player, item) != -1) {
        return TRUE;
    }
    return FALSE;
}

s32 BoardComJunctionInputGet(s32 item, Vec *input, s32 num_dirs, float *dirs) {
    Vec pos_next;
    Vec pos_junction;
    Vec dir;
    float dist_min;
    float dist;
    float angle;
    s32 chance_random;
    s32 best_dir;
    s32 board;
    s32 path_unknown;
    s32 choose_path;
    s32 dir_random;
    s32 i;
    s16 space_next;
    s16 space;
    s16 roll;

    board = GWBoardGet();
    path_unknown = 0;
    space = GWPlayer[item].space_curr;
    space_next = -1;
    roll = GWPlayer[item].roll;
    switch (GWPlayer[item].diff) {
        case 3:
            chance_random = 0;
            break;
        case 2:
            chance_random = 0;
            break;
        case 1:
            chance_random = 10;
            break;
        default:
        case 0:
            chance_random = 0x1E;
            break;
    }
    if (BoardRandMod(0x64) >= chance_random) {
        choose_path = 1;
    } else {
        choose_path = 0;
    }
    if (choose_path != 0) {
        if (board >= 0 && board <= 5) {
            space_next = BoardComPathBestGet(space);
        } else if (board == 7) {
            space_next = BoardComPathBestGetFlag(space, 0x10000000, 10);
        }
        if (space_next == -1) {
            path_unknown = 1;
        } else {
            BoardSpacePosGet(0, space, &pos_junction);
            BoardSpacePosGet(0, space_next, &pos_next);
            VECSubtract(&pos_next, &pos_junction, &dir);
            angle = BoardDAngleCalc(90.0 - atan2d(dir.z, dir.x));
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
        }
    }
    if (path_unknown != 0) {
        dir_random = BoardRandMod(num_dirs);
        angle = dirs[dir_random];
    }
    dist_min = 999.0f;
    for (best_dir = i = 0; i < 4; i++) {
        dist = (comJunctionDirTbl[i].x - angle < 0.0f)
            ? -(comJunctionDirTbl[i].x - angle)
            : (comJunctionDirTbl[i].x - angle);
        if (dist < dist_min) {
            best_dir = i;
            dist_min = dist;
        }
    }
    input->x = comJunctionDirTbl[best_dir].y;
    input->z = comJunctionDirTbl[best_dir].z;
    input->y = 0.0f;
    return 0;
}

s32 BoardComFarPlayerFind(void) {
    s32 len;
    s32 max_len;
    s32 far_player;
    s32 space;
    s32 i;

    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        return -1;
    }
    far_player = -1;
    max_len = -1;
    for (i = 0; i < 4; i++) {
        space = GWPlayer[i].space_curr;
        len = BoardComPathShortcutLenGet(space, 8, 0);
        if (len > 0 && len > max_len) {
            max_len = len;
            far_player = i;
        }
    }
    return far_player;
}
