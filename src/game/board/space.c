#include "game/board/space.h"
#include "game/board/battle.h"
#include "game/board/lottery.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/shop.h"
#include "game/board/star.h"
#include "game/board/tutorial.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/objsub.h"
#include "game/sprite.h"

#include "ext_math.h"
#include "string.h"

static BoardSpace spaceData[2][256];
s16 boardSpaceStarTbl[8];
static GXTexObj spaceHiliteTex;
static GXTexObj spaceTex;

static s8 spaceImgIdx[12] = { 0, 1, 2, 7, 6, 5, 3, 4, 9, 10, 11, 0 };

static s8 spaceHiliteImgIdx[12] = { -1, 0, 1, 1, 2, 2, 2, 2, -1, 3, -1, -1 };

static s16 spaceCnt[2];
static u32 spaceAttr[2];
static void *spaceTexData;
static void *spaceHiliteTexData;
static GXTexFmt spaceTexFmt;
static GXTexFmt spaceHiliteTexFmt;
s16 lbl_801D3FC4[4];
static BoardSpaceEventFunc landEventFunc;
static BoardSpaceEventFunc walkMiniEventFunc;
static BoardSpaceEventFunc walkEventFunc;
static s32 spaceDrawCnt;
static s16 spaceDrawF;

static s16 spaceDrawMdl = -1;
static s16 starPlatMdl = -1;

static s32 ExecPipeSpace(s32 player, s32 space);

void BoardSpaceWalkEventFuncSet(BoardSpaceEventFunc func)
{
    walkEventFunc = func;
}

void BoardSpaceWalkMiniEventFuncSet(BoardSpaceEventFunc func)
{
    walkMiniEventFunc = func;
}

void BoardSpaceLandEventFuncSet(BoardSpaceEventFunc func)
{
    landEventFunc = func;
}

s32 BoardSpaceWalkEventExec(void)
{
    s32 ret = -1;
    if (walkEventFunc) {
        ret = walkEventFunc();
    }
    return ret;
}

s32 BoardSpaceWalkMiniEventExec(void)
{
    s32 ret = -1;
    if (walkMiniEventFunc) {
        _SetFlag(FLAG_ID_MAKE(1, 8));
        ret = walkMiniEventFunc();
        _ClearFlag(FLAG_ID_MAKE(1, 8));
    }
    return ret;
}

s32 BoardSpaceCountGet(s32 layer)
{
    return spaceCnt[layer];
}

BoardSpace *BoardSpaceGet(s32 layer, s32 index)
{
    if (index <= 0 || index > spaceCnt[layer]) {
        return NULL;
    }
    else {
        return &spaceData[layer][index - 1];
    }
}

void BoardSpaceAttrSet(s32 layer, u32 attr)
{
    spaceAttr[layer] |= attr;
}

void BoardSpaceAttrReset(s32 layer, u32 attr)
{
    spaceAttr[layer] &= ~attr;
}

u32 BoardSpaceFlagGet(s32 layer, s32 index)
{
    if (index <= 0 || index > spaceCnt[layer]) {
        return 0;
    }
    else {
        return spaceData[layer][index - 1].flag;
    }
}

s32 BoardSpaceTypeGet(s32 layer, s32 index)
{
    if (index <= 0 || index > spaceCnt[layer]) {
        return 0;
    }
    else {
        return spaceData[layer][index - 1].type;
    }
}

void BoardSpaceTypeSet(s32 layer, s32 index, s32 type)
{
    if (index <= 0 || index > spaceCnt[layer]) {
        return;
    }
    else {
        spaceData[layer][index - 1].type = type;
    }
}

s32 BoardSpacePosGet(s32 layer, s32 index, Vec *pos)
{
    BoardSpace *space = BoardSpaceGet(layer, index);
    if (!space) {
        return -1;
    }
    else {
        *pos = space->pos;
        return 0;
    }
}

void BoardSpaceCornerPosGet(s32 index, s32 corner, Vec *pos)
{
    Vec corner_ofs;
    Vec rot;
    s8 corner_pos[4][2] = { { -1, -1 }, { 1, -1 }, { -1, 1 }, { 1, 1 } };
    BoardSpaceRotGet(0, index, &rot);
    BoardSpacePosGet(0, index, pos);
    corner_ofs.x = corner_pos[corner][0] * 80.0f;
    corner_ofs.y = 0;
    corner_ofs.z = corner_pos[corner][1] * 80.0f;
    corner_ofs.x = (cosd(rot.z) * corner_ofs.x) + (sind(rot.z) * corner_ofs.y);
    corner_ofs.y = (cosd(rot.x) * cosd(rot.z) * corner_ofs.y) + (sind(rot.z) * corner_ofs.x)
        + (sind(-rot.x) * corner_ofs.z);
    corner_ofs.z = (sind(rot.x) * corner_ofs.y) + (cosd(rot.x) * corner_ofs.z);
    pos->x += corner_ofs.x;
    pos->y += corner_ofs.y;
    pos->z += corner_ofs.z;
}

s32 BoardSpaceRotGet(s32 layer, s32 index, Vec *rot)
{
    BoardSpace *space = BoardSpaceGet(layer, index);
    if (!space) {
        return -1;
    }
    else {
        *rot = space->rot;
        return 0;
    }
}

s32 BoardSpaceFlagSearch(s32 layer, u32 flag)
{
    s32 i;
    for (i = 0; i < spaceCnt[layer]; i++) {
        BoardSpace *space = &spaceData[layer][i];
        if ((space->flag & flag) == flag) {
            return space - (&spaceData[layer][0]) + 1;
        }
    }
    return -1;
}

s32 BoardSpaceFlagPosGet(s32 layer, u32 flag, Vec *pos)
{
    s32 space = BoardSpaceFlagSearch(layer, flag);
    if (space == -1) {
        return -1;
    }
    if (pos) {
        BoardSpacePosGet(layer, space, pos);
    }
    return space;
}

s32 BoardSpaceLinkFlagSearch(s32 layer, s32 index, u32 flag)
{
    BoardSpace *link_space;
    BoardSpace *space = BoardSpaceGet(layer, index);
    s32 i;
    if (!space) {
        return -1;
    }
    for (i = 0; i < space->link_cnt; i++) {
        link_space = BoardSpaceGet(layer, space->link[i]);
        if (link_space->flag & flag) {
            return link_space - &spaceData[layer][0] + 1;
        }
    }
    return -1;
}

s32 BoardSpaceLinkTypeListGet(s32 layer, s32 index, s32 type, s16 *list)
{
    s32 count;
    BoardSpace *space = BoardSpaceGet(layer, index);
    s32 i;
    if (!space) {
        return -1;
    }
    for (count = i = 0; i < space->link_cnt; i++) {
        BoardSpace *link_space = BoardSpaceGet(layer, space->link[i]);
        if (link_space->type == type && count < BOARD_SPACE_LINKMAX) {
            list[count] = link_space - &spaceData[layer][0] + 1;
            count++;
        }
    }
    return count;
}

s32 BoardSpaceLinkTargetListGet(s32 layer, s32 target, s16 *list)
{
    s32 i, j;
    s32 count;
    BoardSpace *space;
    memset(list, 0, BOARD_SPACE_LINKMAX * sizeof(s16));
    space = &spaceData[layer][0];
    for (count = i = 0; i < spaceCnt[layer]; i++, space++) {
        for (j = 0; j < space->link_cnt; j++) {
            if (space->link[j] == target && count < BOARD_SPACE_LINKMAX) {
                list[count++] = space - &spaceData[layer][0] + 1;
            }
        }
    }
    return count;
}

s32 BoardSpaceLinkTypeSearch(s32 layer, s32 target, u16 type)
{
    s32 i;
    BoardSpace *space = BoardSpaceGet(layer, target);
    if (!space) {
        return -1;
    }
    for (i = 0; i < space->link_cnt; i++) {
        BoardSpace *link_space = BoardSpaceGet(layer, space->link[i]);
        if (link_space->type == type) {
            return space->link[i];
        }
    }
    return -1;
}

s32 BoardSpaceLinkTransformGet(s32 flag, Vec *pos, Vec *rot, Vec *scale)
{
    s32 i;
    s32 space_flag = BoardSpaceFlagSearch(0, flag);
    BoardSpace *space = BoardSpaceGet(0, space_flag);

    for (i = 0; i < space->link_cnt; i++) {
        BoardSpace *link_space = BoardSpaceGet(0, space->link[i]);
        BoardSpace *src_space;
        if (!(link_space->flag & 0x2000000)) {
            continue;
        }
        src_space = BoardSpaceGet(0, link_space->link[0]);
        if (pos) {
            *pos = src_space->pos;
        }
        if (rot) {
            *rot = src_space->rot;
        }
        if (scale) {
            *scale = src_space->scale;
        }
        return 0;
    }
    return -1;
}

void BoardSpaceHostSet(s32 space)
{
    s16 host_space;
    Vec pos;
    BoardSpace *space_plat;
    BoardSpaceTypeSet(0, space, 8);
    host_space = BoardSpaceLinkFlagSearch(0, space, 0x04000000);
    BoardSpacePosGet(0, host_space, &pos);
    BoardModelPosSetV(BoardStarHostMdlGet(), &pos);
}

static inline s16 StarPlatGetMdl(void)
{
    return starPlatMdl;
}

static inline s32 BoardStarSpaceTypeGet(s16 index)
{
    return BoardSpaceTypeGet(0, BoardSpaceStarGet(index));
}

void BoardSpaceStarSetIndex(s32 index)
{
    Vec pos;
    Vec rot;
    s16 space;
    if (_CheckFlag(FLAG_ID_MAKE(1, 1))) {
        BoardSpaceTypeSet(0, boardSpaceStarTbl[GWSystem.star_pos], 1);
    }
    GWSystem.star_pos = index & 0x7;
    BoardSpaceHostSet(BoardSpaceStarGetCurr());
    space = BoardSpaceLinkFlagSearch(0, BoardSpaceStarGetCurr(), 0x04000000);
    BoardSpacePosGet(0, space, &pos);
    BoardModelPosSetV(StarPlatGetMdl(), &pos);
    BoardSpaceRotGet(0, space, &rot);
    BoardModelRotYSet(StarPlatGetMdl(), rot.y);
    BoardModelVisibilitySet(StarPlatGetMdl(), 1);
}

s32 BoardSpaceStarGetNext(void)
{
    s16 random_pos;
    s16 star_total;
    s16 star_pos;
    star_total = GWSystem.star_total;
    star_pos = GWSystem.star_pos;
    if (GWBoardGet() == BOARD_ID_MAIN6) {
        s16 i;
        s32 count;
        s32 last_free;
        last_free = -1;
        for (count = i = 0; i < 8; i++) {
            if ((1 << i) & GWSystem.star_flag) {
                count++;
            }
            else {
                last_free = i;
            }
        }
        if (count == 7) {
            if (BoardSpaceTypeGet(0, BoardSpaceStarGet(last_free)) == 10) {
                GWSystem.star_flag = 0;
            }
        }
    }
begin:
    random_pos = BoardRandMod(8);
    if (star_pos == random_pos || BoardStarSpaceTypeGet(random_pos) == 10) {
        goto begin;
    }
    switch (GWSystem.board) {
        case BOARD_ID_MAIN1:
            if (star_total >= 2) {
                break;
            }
            if (random_pos != 6 && random_pos != 7) {
                break;
            }
            goto begin;

        case BOARD_ID_MAIN2:
            if (star_total >= 2) {
                break;
            }
            if (random_pos != 6 && random_pos != 7) {
                break;
            }
            goto begin;

        case BOARD_ID_MAIN3:
            if (star_total == 1) {
                if (random_pos < 3 || random_pos > 5) {
                    break;
                }
                goto begin;
            }
            else {
                if (star_total != 2) {
                    break;
                }
                if (random_pos != 3 && random_pos != 4) {
                    break;
                }
                goto begin;
            }

        case BOARD_ID_MAIN4:
            if (star_total == 1) {
                if (random_pos < 5 || random_pos > 7) {
                    break;
                }
                goto begin;
            }
            else {
                if (star_total != 2) {
                    break;
                }
                if (random_pos == 5) {
                    goto begin;
                }
                break;
            }

        case BOARD_ID_MAIN5:
            if (star_total == 1) {
                if (random_pos <= 1 || random_pos >= 4) {
                    goto begin;
                }
            }
            break;

        case BOARD_ID_MAIN6:
            if (star_total == 1) {
                if (random_pos == 1 || random_pos == 4 || random_pos == 5) {
                    goto begin;
                }
            }
            if (star_total != 2) {
                break;
            }
            if (random_pos == 5) {
                goto begin;
            }
    }
    if ((1 << random_pos) & GWSystem.star_flag) {
        goto begin;
    }
    return random_pos;
}

s32 BoardSpaceStarGetRandom(s32 excl_pos)
{
    s8 new_pos;
    int i;
    for (i = 0; i < 1024; i++) {
        new_pos = BoardRandMod(8);
        if (new_pos == GWSystem.star_pos) {
            continue;
        }
        if (GWSystem.turn == 1 && new_pos <= 2) {
            continue;
        }
        if (new_pos != excl_pos) {
            break;
        }
    }
    return new_pos;
}

void BoardSpaceStarMove(void)
{
    u8 star_total;
    s16 star_pos;
    s16 star_next;
    if (_CheckFlag(FLAG_ID_MAKE(1, 1))) {
        star_pos = GWSystem.star_pos;
        GWSystem.star_flag |= (u8)(1 << star_pos);
        if (GWSystem.star_flag == 0xFF) {
            GWSystem.star_flag = 0;
        }
        if (GWSystem.star_total >= 99) {
            star_total = 99;
            GWSystem.star_total = star_total;
        }
        else {
            star_total = GWSystem.star_total++;
        }
    }
    star_next = BoardSpaceStarGetNext();
    BoardSpaceStarSetIndex(star_next);
}

s32 BoardSpaceStarGet(s32 index)
{
    return boardSpaceStarTbl[index & 0x7];
}

s32 BoardSpaceStarGetCurr(void)
{
    return BoardSpaceStarGet(GWSystem.star_pos);
}

s32 BoardSpaceStarCheck(s32 index)
{
    s32 ret;
    BoardSpace *space = BoardSpaceGet(0, index);
    BoardSpace *star_space;
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        ret = 0;
        goto end;
    }
    star_space = BoardSpaceGet(0, boardSpaceStarTbl[GWSystem.star_pos]);
    if (space == star_space) {
        ret = 1;
    }
    else {
        ret = 0;
    }
end:
    return ret;
}

void BoardSpaceLandExec(s32 player, s32 space)
{
#define BLUE_SPACE 1
#define RED_SPACE 2
#define BOWSER_SPACE 3
#define MUSHROOM_SPACE 4
#define BATTLE_SPACE 5
#define HAPPENING_SPACE 6
#define FORTUNE_SPACE 7
#define STAR_SPACE 8
#define WARP_SPACE 9

    BoardSpace *space_ptr = BoardSpaceGet(0, space);
    switch (space_ptr->type) {
        case BLUE_SPACE:
            GWPlayer[player].blue_count++;
            if (GWPlayer[player].blue_count > 99) {
                GWPlayer[player].blue_count = 99;
            }
            BoardLandBlueExec(player, space);
            break;

        case RED_SPACE:
            GWPlayer[player].red_count++;
            if (GWPlayer[player].red_count > 99) {
                GWPlayer[player].red_count = 99;
            }
            BoardLandRedExec(player, space);
            break;

        case BOWSER_SPACE:
            GWPlayer[player].bowser_count++;
            if (GWPlayer[player].bowser_count > 99) {
                GWPlayer[player].bowser_count = 99;
            }
            BoardBowserExec(player, space);
            break;

        case MUSHROOM_SPACE:
            GWPlayer[player].mushroom_count++;
            if (GWPlayer[player].mushroom_count > 99) {
                GWPlayer[player].mushroom_count = 99;
            }
            BoardMushroomExec(player, space);
            break;

        case BATTLE_SPACE:
            GWPlayer[player].battle_count++;
            if (GWPlayer[player].battle_count > 99) {
                GWPlayer[player].battle_count = 99;
            }
            BoardBattleExec(player, space);
            break;

        case HAPPENING_SPACE:
            GWPlayer[player].question_count++;
            if (GWPlayer[player].question_count > 99) {
                GWPlayer[player].question_count = 99;
            }
            if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
                HuAudFXPlay(842);
                BoardCameraViewSet(2);
                BoardPlayerMotBlendSet(player, 0, 15);
                while (!BoardPlayerMotBlendCheck(player)) {
                    HuPrcVSleep();
                }
                BoardCameraMotionWait();
                BoardTutorialHookExec(16, 0);
            }
            else {
                if (landEventFunc) {
                    HuAudFXPlay(842);
                    omVibrate(player, 12, 4, 2);
                    landEventFunc();
                }
            }
            GWPlayer[player].color = 3;
            break;

        case FORTUNE_SPACE:
            GWPlayer[player].fortune_count++;
            if (GWPlayer[player].fortune_count > 99) {
                GWPlayer[player].fortune_count = 99;
            }
            BoardFortuneExec(player, space);
            break;

        case WARP_SPACE:
            GWPlayer[player].warp_count++;
            if (GWPlayer[player].warp_count > 99) {
                GWPlayer[player].warp_count = 99;
            }
            BoardWarpExec(player, space);
            break;

        case STAR_SPACE:
            BoardStarExec(player, space);
            break;
    }
}

s32 BoardSpaceWalkExec(s32 player, s32 space)
{
    s32 is_star;
    BoardSpace *space_ptr;
    BoardSpace *star_space;
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        space_ptr = BoardSpaceGet(0, space);
        if (space_ptr->flag & 0x180000) {
            BoardTutorialHookExec(25, 0);
        }
    }
    if (BoardPlayerSizeGet(player) == 2 || GWPlayer[player].bowser_suit) {
        return 0;
    }
    space_ptr = BoardSpaceGet(0, space);
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        is_star = 0;
    }
    else {
        star_space = BoardSpaceGet(0, boardSpaceStarTbl[GWSystem.star_pos]);
        if (space_ptr == star_space) {
            is_star = 1;
        }
        else {
            is_star = 0;
        }
    }
    if (is_star) {
        BoardStarExec(player, space);
        return 1;
    }
    if (space_ptr->flag & 0x600000) {
        s32 mg_param = GWSystem.unk_38;
        if (BoardPlayerSizeGet(player) == 1) {
            BoardPlayerIdleSet(player);
            BoardMGCreate(mg_param);
        }
        return 1;
    }
    if (space_ptr->flag & 0x180000) {
        BoardShopExec(player, space);
        return 1;
    }
    if (space_ptr->flag & 0x08000000) {
        BoardBooHouseExec(player, space);
        return 1;
    }
    if (space_ptr->flag & 0x10000000) {
        BoardLotteryExec();
        return 1;
    }
    if (space_ptr->flag & 0x20000000) {
        ExecPipeSpace(player, space);
        return 1;
    }
    return 0;
}

s32 BoardSpaceBlockExec(s32 player, s32 space)
{
    s32 event_exec;
    BoardSpace *space_ptr;
    event_exec = 0;
    if (BoardPlayerSizeGet(player) == 2 || GWPlayer[player].bowser_suit) {
        return 0;
    }
    space_ptr = BoardSpaceGet(0, space);
    event_exec = 0;
    if (space == GWSystem.block_pos) {
        event_exec = 1;
    }
    if (!GWBonusStarGet() && GWPartyGet() == 1 && !_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        event_exec = 0;
    }
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        event_exec = 0;
    }
    if (event_exec) {
        BoardBlockExec(player, space);
        if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
            BoardBlockExec(player, space);
        }
        BoardSpaceBlockPosSet();
    }
    return 0;
}

static s32 ExecPipeSpace(s32 player, s32 space)
{
    Vec pos_link;
    Vec pos;
    Vec dir;
    float radius, y_vel;
    s32 mot_disable;
    BoardSpace *space_ptr;
    mot_disable = 0;
    if (BoardPlayerSizeGet(player) != 1) {
        return 0;
    }
    BoardPlayerPosGet(player, &pos);
    pos.y += 200.0f;
    space_ptr = BoardSpaceGet(0, space);
    BoardSpacePosGet(0, space_ptr->link[0], &pos_link);
    VECSubtract(&pos_link, &pos, &dir);
    VECNormalize(&dir, &dir);
    BoardPlayerRotYSet(player, 90 - atan2d(dir.z, dir.x));
    radius = 0.75f * BoardVecDistXZCalc(&pos_link, &pos);
    BoardPlayerMotionStart(player, 4, 0);
    y_vel = 0;
    while (1) {
        if (BoardVecDistXZCalc(&pos_link, &pos) < 2) {
            break;
        }
        pos.x += (dir.x * radius) / 60.0f;
        pos.z += (dir.z * radius) / 60.0f;
        if (pos.y <= pos_link.y) {
            pos.y = pos_link.y;
            if (!mot_disable) {
                BoardPlayerMotionShiftSet(player, 3, 0, 4, HU3D_MOTATTR_LOOP);
                break;
            }
        }
        else {
            pos.y += 10.0f + (-((1 / 2399.99f) + (1 / 50.0f)) * y_vel * y_vel);
            y_vel += 1.0f;
        }
        BoardPlayerPosSetV(player, &pos);
        HuPrcVSleep();
    }
    return 0;
}

void BoardSpaceTypeForce(u16 from, u16 to)
{
    s32 i;
    for (i = 0; i < spaceCnt[0]; i++) {
        BoardSpace *space = &spaceData[0][i];
        if (space->type == from) {
            space->type = to;
        }
    }
}

void BoardSpaceHide(s32 value)
{
    if (value) {
        Hu3DModelAttrSet(spaceDrawMdl, HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrReset(spaceDrawMdl, HU3D_ATTR_DISPOFF);
    }
}

static inline void InitGXSpace()
{
    GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXInvalidateTexAll();
    GXLoadTexObj(&spaceTex, GX_TEXMAP0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1);
    GXSetChanAmbColor(GX_COLOR0A0, color);
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
}

// Some stack allocation issues. code around BoardPlayerGetCurr is incorrect too
static void DrawSpaces(ModelData *model, Mtx matrix)
{
    s32 i;

    Vec player_pos;
    Vec target;
    Vec pos;

    Mtx lookat, final, rot_x, rot_y, rot_z, scale;
    Mtx44 proj;
    BoardCameraData *camera;
    if (!spaceDrawF) {
        return;
    }
    spaceDrawCnt = 0;
    camera = &boardCamera;
    BoardCameraPosGet(&pos);
    BoardCameraTargetGet(&target);
    MTXPerspective(proj, camera->fov, camera->aspect, camera->near, camera->far);
    GXSetProjection(proj, GX_PERSPECTIVE);
    MTXLookAt(lookat, &pos, &camera->up, &target);
    GXSetViewport(camera->viewport_x, camera->viewport_y, camera->viewport_w, camera->viewport_h, camera->viewport_near, camera->viewport_far);
    GXSetScissor(camera->viewport_x, camera->viewport_y, camera->viewport_w, camera->viewport_h);
    {
        BoardSpace *space_curr;
        BoardSpace *space_hilite;
        PlayerState *player;
        s16 player_mdl;
        float y_dist;
        s32 space_img;
        u16 space_type;
        float uv_x, uv_y, uv_size;
        InitGXSpace();

        player = BoardPlayerGet(GWSystem.player_curr);
        BoardPlayerPosGet(GWSystem.player_curr, &player_pos);
        player_mdl = BoardModelIDGet(BoardPlayerModelGet(GWSystem.player_curr));
        space_curr = &spaceData[0][0];
        space_hilite = NULL;
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        for (i = 0; i < spaceCnt[0]; i++, space_curr++) {
            if (space_curr->type == 0) {
                continue;
            }
            if (!BoardCameraCullCheck(&space_curr->pos, 200.0f) || (space_curr->flag & spaceAttr[0])) {
                continue;
            }
            if (!space_hilite) {
                if (player_pos.x > space_curr->pos.x - 100.0f && player_pos.z > space_curr->pos.z - 100.0f
                    && player_pos.x < space_curr->pos.x + 100.0f && player_pos.z < space_curr->pos.z + 100.0f) {
                    if (player_pos.y - space_curr->pos.y < 0.0f) {
                        y_dist = -(player_pos.y - space_curr->pos.y);
                    }
                    else {
                        y_dist = player_pos.y - space_curr->pos.y;
                    }
                    if (y_dist < 10.0f) {
                        space_hilite = space_curr;
                    }
                }
            }
            space_type = space_curr->type;
            space_img = spaceImgIdx[space_type] - 1;
            uv_x = (float)(space_img % 4) / 4.0f;
            uv_y = (float)(space_img / 4) / 4.0f;
            uv_size = 63.0f / 256.0f;
            MTXRotRad(rot_z, 'z', MTXDegToRad(space_curr->rot.y));
            MTXRotRad(rot_y, 'y', MTXDegToRad(space_curr->rot.z));
            MTXRotRad(rot_x, 'x', MTXDegToRad(space_curr->rot.x + 90.0f));
            MTXTrans(final, space_curr->pos.x, 3.0f + space_curr->pos.y, space_curr->pos.z);
            MTXConcat(rot_x, rot_y, rot_y);
            MTXConcat(rot_y, rot_z, rot_z);
            MTXConcat(final, rot_z, final);
            MTXConcat(lookat, final, final);
            GXLoadPosMtxImm(final, GX_PNMTX0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(-100, -100, 0);
            GXTexCoord2f32(uv_x, uv_y);
            GXPosition3f32(100, -100, 0);
            GXTexCoord2f32(uv_x + uv_size, uv_y);
            GXPosition3f32(100, 100, 0);
            GXTexCoord2f32(uv_x + uv_size, uv_y + uv_size + (1.5f / 256.0f));
            GXPosition3f32(-100, 100, 0);
            GXTexCoord2f32(uv_x, uv_y + uv_size + (1.5f / 256.0f));
            GXEnd();
            spaceDrawCnt++;
        }
        if (space_hilite) {
            space_curr = space_hilite;
            space_type = space_curr->type;
            if (player->show_next && space_type != 0 && (space_img = spaceHiliteImgIdx[space_type]) >= 0) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                GXLoadTexObj(&spaceHiliteTex, GX_TEXMAP0);
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
                uv_x = (float)(space_img % 4) / 4.0f;
                uv_y = (float)(space_img / 4) / 4.0f;
                uv_size = 63.0f / 256.0f;
                MTXScale(scale, 1.5f, 1.5f, 1.5f);
                MTXRotRad(rot_z, 'z', MTXDegToRad(space_curr->rot.y));
                MTXRotRad(rot_y, 'y', MTXDegToRad(space_curr->rot.z));
                MTXRotRad(rot_x, 'x', MTXDegToRad(space_curr->rot.x + 90.0f));
                MTXTrans(final, space_curr->pos.x, 3.5f + space_curr->pos.y, space_curr->pos.z);
                MTXConcat(scale, rot_x, rot_x);
                MTXConcat(rot_x, rot_y, rot_y);
                MTXConcat(rot_y, rot_z, rot_z);
                MTXConcat(final, rot_z, final);
                MTXConcat(lookat, final, final);
                GXLoadPosMtxImm(final, GX_PNMTX0);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(-100, -100, 0);
                GXTexCoord2f32(uv_x, uv_y);
                GXPosition3f32(100, -100, 0);
                GXTexCoord2f32(uv_x + uv_size, uv_y);
                GXPosition3f32(100, 100, 0);
                GXTexCoord2f32(uv_x + uv_size, uv_y + uv_size);
                GXPosition3f32(-100, 100, 0);
                GXTexCoord2f32(uv_x, uv_y + uv_size);
                GXEnd();
                spaceDrawCnt++;
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                return;
            }
        }
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
}

s32 BoardSpaceRead(s32 layer, s32 data_num)
{
    int j;
    int i;
    BoardSpace *space;
    u8 *data;
    s32 star_idx;
    u8 *data_base;
    data_base = data = HuDataSelHeapReadNum(data_num, MEMORY_DEFAULT_NUM, HEAP_DATA);
    spaceCnt[layer] = *(u32 *)data;
    data += sizeof(u32);
    space = &spaceData[layer][0];
    for (i = 0; i < spaceCnt[layer]; i++, space++) {
        memcpy(&space->pos, data, sizeof(Vec));
        data += sizeof(Vec);
        memcpy(&space->rot, data, sizeof(Vec));
        data += sizeof(Vec);
        memcpy(&space->scale, data, sizeof(Vec));
        data += sizeof(Vec);
        space->flag = *(u32 *)data;
        data += sizeof(u32);
        space->type = *(u16 *)data;
        data += sizeof(u16);
        space->link_cnt = *(u16 *)data;
        data += sizeof(u16);
        for (j = 0; j < space->link_cnt; j++) {
            space->link[j] = (*(u16 *)data) + 1;
            data += sizeof(u16);
        }
        if (space->type == 8) {

            space->type = 1;
            star_idx = (space->flag & 0x70000) >> 16;
            boardSpaceStarTbl[star_idx] = i + 1;
        }
    }
    HuDataClose(data_base);
    return 0;
}

void BoardSpaceCameraSet(u16 mask)
{
    Hu3DModelCameraSet(spaceDrawMdl, mask);
}

void BoardSpaceBlockPosSet(void)
{
    BoardSpace *space;
    s32 block_pos;
begin:
    if (boardTutorialBlockF) {
        GWSystem.block_pos = boardTutorialBlockPos;
        return;
    }
    block_pos = BoardRandMod(spaceCnt[0]) + 1;
    if (block_pos == GWSystem.block_pos) {
        goto begin;
    }
    space = BoardSpaceGet(0, block_pos);
    if (space->type != 1) {
        goto begin;
    }
    GWSystem.block_pos = block_pos;
}

void BoardSpaceInit(s32 data_num)
{
    s32 board;
    BoardJunctionMaskZero();
    memset(spaceData, 0, sizeof(spaceData));
    memset(spaceAttr, 0, sizeof(spaceAttr));
    lbl_801D3FC4[0] = lbl_801D3FC4[1] = lbl_801D3FC4[2] = lbl_801D3FC4[3] = -1;
    spaceDrawF = 0;
    board = GWBoardGet();
    {
        AnimBmpData *bmp;
        AnimData *data;
        void *data_base;
        s32 size;
        data = data_base = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_BOARD, 29), MEMORY_DEFAULT_NUM, HEAP_DATA);
        data->bmp = (void *)((u32)data_base + (u32)data->bmp);
        data->pat = (void *)((u32)data_base + (u32)data->pat);
        data->bank = (void *)((u32)data_base + (u32)data->bank);
        bmp = data->bmp;
        size = bmp->sizeX;
        spaceHiliteTexFmt = -1;
        switch (bmp->dataFmt) {
            case ANIM_BMP_RGBA8:
                spaceHiliteTexFmt = GX_TF_RGBA8;
                break;

            case ANIM_BMP_RGB5A3_DUPE:
                spaceHiliteTexFmt = GX_TF_RGB5A3;
                break;

            case ANIM_BMP_CMPR:
                spaceHiliteTexFmt = GX_TF_CMPR;
                break;
        }
        spaceHiliteTexData = HuMemDirectMallocNum(HEAP_SYSTEM, bmp->dataSize, MEMORY_DEFAULT_NUM);
        bmp->data = (void *)((u32)bmp->data + (u32)data_base);
        memcpy(spaceHiliteTexData, bmp->data, bmp->dataSize);
        HuDataClose(data_base);
        GXInitTexObj(&spaceHiliteTex, spaceHiliteTexData, size, size, spaceHiliteTexFmt, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&spaceHiliteTex, GX_LINEAR, GX_LINEAR, 0, 0, 0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    {
        AnimBmpData *bmp;
        AnimData *data;
        void *data_base;
        s32 size;
        data = data_base = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_BOARD, 28), MEMORY_DEFAULT_NUM, HEAP_DATA);
        data->bmp = (void *)((u32)data_base + (u32)data->bmp);
        data->pat = (void *)((u32)data_base + (u32)data->pat);
        data->bank = (void *)((u32)data_base + (u32)data->bank);
        bmp = data->bmp;
        size = bmp->sizeX;
        spaceTexFmt = -1;
        switch (bmp->dataFmt) {
            case ANIM_BMP_RGBA8:
                spaceTexFmt = GX_TF_RGBA8;
                break;

            case ANIM_BMP_RGB5A3_DUPE:
                spaceTexFmt = GX_TF_RGB5A3;
                break;

            case ANIM_BMP_CMPR:
                spaceTexFmt = GX_TF_CMPR;
                break;
        }
        spaceTexData = HuMemDirectMallocNum(HEAP_SYSTEM, bmp->dataSize, MEMORY_DEFAULT_NUM);
        bmp->data = (void *)((u32)bmp->data + (u32)data_base);
        memcpy(spaceTexData, bmp->data, bmp->dataSize);
        HuDataClose(data_base);
        GXInitTexObj(&spaceTex, spaceTexData, size, size, spaceTexFmt, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&spaceTex, GX_LINEAR, GX_LINEAR, 0, 0, 0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    BoardSpaceRead(0, data_num);
    spaceDrawMdl = Hu3DHookFuncCreate(DrawSpaces);
    if (!BoardStartCheck() && !_CheckFlag(FLAG_ID_MAKE(1, 1))) {
        BoardSpaceBlockPosSet();
        GWSystem.star_total = 0;
        GWSystem.star_flag = 0;
    }
    if (GWBoardGet() != BOARD_ID_EXTRA1 && GWBoardGet() != BOARD_ID_EXTRA2) {
        starPlatMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 6), NULL, 0);
        BoardModelMotionStart(starPlatMdl, 0, 0x40000001);
        BoardModelVisibilitySet(starPlatMdl, 0);
        if (_CheckFlag(FLAG_ID_MAKE(1, 1))) {
            Vec pos;
            Vec rot;
            s16 space;
            BoardModelVisibilitySet(starPlatMdl, 1);
            GWSystem.star_flag |= (u8)(1 << GWSystem.star_pos);
            BoardSpaceTypeSet(0, boardSpaceStarTbl[GWSystem.star_pos], 8);
            {
                int space;
                BoardSpace *space_plat;
                space = BoardSpaceLinkFlagSearch(0, BoardSpaceStarGetCurr(), 0x04000000);
                BoardSpacePosGet(0, space, &pos);
                BoardModelPosSetV(StarPlatGetMdl(), &pos);
                BoardSpaceRotGet(0, space, &rot);
                BoardModelRotYSet(StarPlatGetMdl(), rot.y);
            }
        }
    }
    spaceDrawF = 1;
#ifdef TARGET_PC
    GXDestroyTexObj(&spaceHiliteTex);
    GXDestroyTexObj(&spaceTex);
#endif
}

void BoardSpaceDestroy(void)
{
    if (spaceDrawMdl >= 0) {
        Hu3DModelKill(spaceDrawMdl);
        spaceDrawMdl = -1;
    }
    if (spaceHiliteTexData) {
        HuMemDirectFree(spaceHiliteTexData);
        spaceHiliteTexData = NULL;
    }
    if (spaceTexData) {
        HuMemDirectFree(spaceTexData);
        spaceTexData = NULL;
    }
}
