#include "REL/w01Dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"

#include "game/board/audio.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/ui.h"
#include "game/board/window.h"
#include "game/window.h"

#include "dolphin.h"
#include "ext_math.h"

static void RoundItemEnd(void);
static void RoundItemClose(void);
static void RoundItemMainUpdate(omObjData *obj);
static void RoundItemUmaStop(omObjData *obj);
static void RoundItemPlayerJump(omObjData *obj);
static void RoundItemStartWait(omObjData *obj);
static void RoundItemComInputGet(omObjData *obj, u16 *btn);
static void RoundItemInputWait(omObjData *obj);
static void RoundItemStop(omObjData *obj);
static void RoundItemLightFlicker(omObjData *obj);
static void RoundItemUmaJumpWait(omObjData *obj);
static void RoundItemUmaJump(omObjData *obj);
static void RoundItemRotatePlayer(omObjData *obj);
static void RoundItemStreamWait(omObjData *obj);
static void RoundItemWinWait(omObjData *obj);
static void ItemGetWinExec(void);
static void ItemGetShrinkWait(omObjData *obj);
static void ItemGetReturnWinExec(void);
static void RoundItemGameClose(omObjData *obj);
static void RoundItemGameEnd(omObjData *obj);
static void RoundItemItemUpdate(omObjData *obj);
static s16 RoundItemItemGet(u32 umaNo);
static void ItemGetCreate(s16 itemNo);
static void ItemGetObjUpdate(omObjData *obj);
static void ItemGetPlayerMove(omObjData *obj);
static void ItemGetShrink(omObjData *obj);
static float RoundItemUmaRotYGet(u32 umaNo);
static void RoundItemUmaPlayerSet(u32 umaNo);
static float RoundItemAngleGet(Vec *arg0);
static void ItemGetEff1Hook(ModelData *model, ParticleData *particle, Mtx matrix);
static void ItemGetEff2Hook(ModelData *model, ParticleData *particle, Mtx matrix);

static void *itemAnim;
static Vec roundItemPos;
static omObjData *itemObj[4];
static omObjData *roundItemUmaObj;
static omObjData *roundItemMainObj;
static omObjData *itemGetObj;
static float umaSpeed;
static float borderSpeed;
static s32 roundItemPlayer;
static Vec umaPos;
static s16 seqStartId;
static s16 timerSeqId;
static s16 timerSec;
static s16 timerFrame;
static Vec roundItemPlayerPos;
static s32 lbl_1_bss_7C0_pad;
static s32 itemGetMotId;
static s32 jumpMotId;
static s16 umaStopF;
static s32 lbl_1_bss_7B0_pad;
static s32 itemGetSeNo;
static s16 roundItemStopF;
static s16 umaStopTimer;
static s32 roundItemStreamId;
static AnimData *roundItemEffAnim;

#if VERSION_JP
#define MDL_ID_SHIFT 0
#else
#define MDL_ID_SHIFT 1
#endif

static s32 itemMdlTbl[] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 108 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 109 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 110 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 111 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 112 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 113 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 114 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 115 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 117 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 118 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 119 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 120 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 121 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 122 + MDL_ID_SHIFT),
};

static s32 itemGetMotTbl[8] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 23), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 23), DATA_MAKE_NUM(DATADIR_PEACHMOT, 23),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 23), DATA_MAKE_NUM(DATADIR_WARIOMOT, 23), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 23),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 23), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 23) };

static s32 jumpMotTbl[8] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 64), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 64), DATA_MAKE_NUM(DATADIR_PEACHMOT, 64),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 64), DATA_MAKE_NUM(DATADIR_WARIOMOT, 64), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 64),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 64), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 64) };

void RoundItemInit(s16 *itemTbl)
{
    s16 itemOrderTbl[14];
    s16 itemMdlId[4];
    float borderTime;
    float borderMaxTime;
    float itemAngle;
    s32 itemOrderNum;
    s32 itemNum;
    s32 i;
    s32 j;

    itemAnim = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_W01, 28), MEMORY_DEFAULT_NUM, HEAP_DATA);
    BoardModelPosGet(mapObjMdlId[MAPOBJ_ROUNDITEM], &roundItemPos);
    itemMdlId[0] = BoardModelIDGet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM]);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM], 1);
    for (i = 1; i < 4; i++) {
        itemMdlId[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_W01, 24));
    }
    itemNum = 0;
    for (i = 0; i < 4; i++) {
        itemObj[i] = omAddObjEx(boardObjMan, 0x165, 2, 0, -1, NULL);
        if (itemTbl[i] != -1) {
            itemObj[itemNum++]->work[1] = itemTbl[i];
        }
    }
    while (itemNum != 4) {
        itemOrderNum = 0;
        for (i = 0; i < 14; i++) {
            for (j = 0; j < itemNum; j++) {
                if (i == itemObj[j]->work[1]) {
                    break;
                }
            }
            if (j == itemNum) {
                itemOrderTbl[itemOrderNum++] = i;
            }
        }
        itemObj[itemNum++]->work[1] = itemOrderTbl[rand8() % itemOrderNum];
    }
    borderTime = BoardModelMotionTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]);
    borderMaxTime = BoardModelMotionMaxTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]);
    for (i = 0; i < 4; i++) {
        itemObj[i]->model[0] = itemMdlId[i];
        itemObj[i]->model[1] = Hu3DModelCreateFile(itemMdlTbl[itemObj[i]->work[1]]);
        if (itemObj[i]->work[1] == 5) {
            Hu3DData[itemObj[i]->model[1]].unk_F0[1][3] = -50.0f;
        }
        if (itemObj[i]->work[1] == 11) {
            Hu3DModelAttrSet(itemObj[i]->model[1], HU3D_MOTATTR_LOOP);
        }
        if (itemObj[i]->work[1] == 4) {
            Hu3DMotionSpeedSet(itemObj[i]->model[1], 0.0f);
        }
        Hu3DModelAttrReset(itemMdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(itemObj[i]->model[1], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(itemObj[i]->model[1], HU3D_MOTATTR_PAUSE);
        omSetTra(itemObj[i], roundItemPos.x, roundItemPos.y + 66.0f, roundItemPos.z);
        itemAngle = 90.0f - 90.0f * i + 360.0f * (borderTime / borderMaxTime);
        if (itemAngle >= 360.0f) {
            itemAngle -= 360.0f;
        }
        if (itemAngle < 0.0f) {
            itemAngle += 360.0f;
        }
        omSetRot(itemObj[i], 0.0f, itemAngle, 0.0f);
        itemObj[i]->work[0] = Hu3DAnimCreate(itemAnim, itemObj[i]->model[0], "item01");
        Hu3DAnimAttrSet(itemObj[i]->work[0], 1);
        itemObj[i]->work[2] = i;
    }
    for (i = 0; i < 4; i++) {
        Hu3DAnmNoSet(itemObj[i]->work[0], itemObj[i]->work[1]);
    }
}

void RoundItemKill(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i != 0) {
            Hu3DModelKill(itemObj[i]->model[0]);
        }
        else {
            BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM], 0);
            Hu3DAnimKill(itemObj[i]->work[0]);
        }
        Hu3DModelKill(itemObj[i]->model[1]);
        omDelObjEx(boardObjMan, itemObj[i]);
    }
    if (roundItemEffAnim) {
        HuSprAnimKill(roundItemEffAnim);
        roundItemEffAnim = NULL;
    }
}

void RoundItemEventStart(void)
{
    s32 i;

    BoardModelPosGet(mapObjMdlId[MAPOBJ_ROUNDITEM], &roundItemPos);
    for (i = 0; i < 4; i++) {
        itemObj[i]->func = RoundItemItemUpdate;
    }
    roundItemMainObj = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, RoundItemMainUpdate);
    roundItemUmaObj = omAddObjEx(boardObjMan, 0x133, 0, 0, -1, RoundItemUmaStop);
    roundItemUmaObj->work[3] = rand8() % 200 + 10;
    roundItemPlayer = GWSystem.player_curr;
    BoardPlayerPosGet(roundItemPlayer, &roundItemPlayerPos);
    umaSpeed = 1.0f;
    borderSpeed = 1.0f;
    roundItemStopF = 0;
    itemGetMotId = BoardPlayerMotionCreate(roundItemPlayer, itemGetMotTbl[GWPlayer[roundItemPlayer].character]);
    jumpMotId = BoardPlayerMotionCreate(roundItemPlayer, jumpMotTbl[GWPlayer[roundItemPlayer].character]);
    roundItemEffAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 0));
    HuSprAnimLock(roundItemEffAnim);
    umaStopF = 0;
}

static void RoundItemEnd(void)
{
    roundItemStopF = 1;
    BoardMGExit();
    HuAudFXPlay(0x40F);
    BoardModelMotionStart(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP], 0, HU3D_MOTATTR_REV);
}

static void RoundItemClose(void)
{
    RoundItemKill();
    BoardPlayerMotionKill(roundItemPlayer, itemGetMotId);
    BoardPlayerMotionKill(roundItemPlayer, jumpMotId);
    BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_LIGHT], 0);
    BoardMGDoneFlagSet(0);
}

static void RoundItemMainUpdate(omObjData *obj)
{
    if (roundItemStopF == 1 && BoardMGDoneFlagGet() == 1) {
        RoundItemClose();
        omDelObjEx(HuPrcCurrentGet(), obj);
    }
}

static char *umaHookTbl[] = { "uma1", "uma2", "uma3", "uma4" };

static void RoundItemUmaStop(omObjData *obj)
{
    Vec playerPos;
    Vec objPos;
    float umaDist;
    float motTime;
    float motMaxTime;
    float umaMinDist;
    s32 i;

    motMaxTime = BoardModelMotionMaxTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]);
    motTime = BoardModelMotionTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]);
    if (motTime >= motMaxTime) {
        motTime -= motMaxTime;
    }
    if (fmodf(motTime, motMaxTime / 4) >= motMaxTime / 4 - 30.0f && umaStopF == 0) {
        umaStopF = 1;
        umaStopTimer = 90;
    }
    if (umaStopF != 0) {
        umaSpeed *= 0.97f;
        umaStopTimer--;
    }
    if (umaSpeed != 1.0f && umaStopTimer == 0) {
        umaSpeed = 0.0f;
        BoardAudSeqPause(0, 1, 1000);
        BoardPlayerPosGet(roundItemPlayer, &playerPos);
        Hu3DModelObjPosGet(BoardModelIDGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]), umaHookTbl[0], &objPos);
        umaMinDist = VECSquareDistance(&playerPos, &objPos);
        obj->work[2] = 0;
        for (i = 1; i < 4; i++) {
            Hu3DModelObjPosGet(BoardModelIDGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]), umaHookTbl[i], &objPos);
            umaDist = VECSquareDistance(&playerPos, &objPos);
            if (umaDist < umaMinDist) {
                umaMinDist = umaDist;
                obj->work[2] = i;
            }
        }
        Hu3DModelObjPosGet(BoardModelIDGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]), umaHookTbl[obj->work[2]], &umaPos);
        VECSubtract(&umaPos, &playerPos, &objPos);
        VECNormalize(&objPos, &objPos);
        obj->trans.x = objPos.x;
        obj->trans.y = objPos.y;
        obj->trans.z = objPos.z;
        obj->rot.x = VECDistanceXZ(&umaPos, &playerPos);
        obj->rot.y = 10.0f;
        obj->rot.z = playerPos.y;
        obj->scale.x = 0.0f;
        BoardPlayerMotionShiftSet(roundItemPlayer, 4, 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        obj->func = RoundItemPlayerJump;
    }
    BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA], umaSpeed);
}

static void RoundItemPlayerJump(omObjData *obj)
{
    Vec pos;
    s32 i;

    BoardPlayerPosGet(roundItemPlayer, &pos);
    pos.x += obj->trans.x * obj->rot.x / 32.760002f;
    pos.z += obj->trans.z * obj->rot.x / 32.760002f;
    pos.y += obj->rot.y - 0.016666668f * obj->scale.x * obj->scale.x;
    obj->scale.x += 1.0f;
    if (VECDistanceXZ(&umaPos, &pos) < 2.0f) {
        pos = umaPos;
        BoardPlayerRotSet(roundItemPlayer, 0.0f, RoundItemUmaRotYGet(obj->work[2]), 0.0f);
        umaSpeed = 0.05f;
        borderSpeed = 0.05f;
        BoardModelAttrReset(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], HU3D_MOTATTR_PAUSE);
        BoardModelAttrSet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], HU3D_MOTATTR_LOOP);
        BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], 0.0f);
        for (i = 0; i < 4; i++) {
            itemObj[i]->func = RoundItemItemUpdate;
        }
        BoardPlayerMotionShiftSet(roundItemPlayer, jumpMotId, 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        seqStartId = MGSeqStartCreate();
        BoardMusStart(1, 0xE, 0x7F, 0);
        obj->func = RoundItemStartWait;
    }
    BoardPlayerPosSetV(roundItemPlayer, &pos);
}

static void RoundItemStartWait(omObjData *obj)
{
    umaSpeed *= 1.05f;
    borderSpeed *= 1.05f;
    if (umaSpeed > 2.0f) {
        umaSpeed = 2.0f;
    }
    if (borderSpeed > 4.0f) {
        borderSpeed = 4.0f;
    }
    if (MGSeqStatGet(seqStartId) == 0) {
        umaSpeed = 2.0f;
        borderSpeed = 4.0f;
        obj->func = RoundItemInputWait;
        timerSec = 5;
        timerFrame = REFRESH_RATE;
        timerSeqId = MGSeqTimerCreateXY(timerSec, 288, 64);
    }
    BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA], umaSpeed);
    BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], borderSpeed);
    RoundItemUmaPlayerSet(obj->work[2]);
}

static void RoundItemComInputGet(omObjData *obj, u16 *btn)
{
    *btn = 0;
    if (obj->work[3] != 0) {
        obj->work[3]--;
    }
    else {
        *btn |= PAD_BUTTON_A;
    }
}

static void RoundItemInputWait(omObjData *obj)
{
    s16 padNo;
    u16 btn;

    RoundItemUmaPlayerSet(obj->work[2]);
    padNo = GWPlayer[roundItemPlayer].port;
    if ((--timerFrame) == 0) {
        if ((--timerSec) >= 0) {
            MGSeqParamSet(timerSeqId, 1, timerSec);
        }
        timerFrame = REFRESH_RATE;
    }
    if (GWPlayerCfg[roundItemPlayer].iscom == 1) {
        RoundItemComInputGet(obj, &btn);
    }
    else {
        btn = HuPadBtnDown[padNo];
    }
    if (timerSec < 0 || (btn & PAD_BUTTON_A)) {
        BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA], 0.0f);
        MGSeqParamSet(timerSeqId, 2, -1);
        obj->scale.y = 0.0f;
        obj->func = RoundItemStop;
    }
}

static void RoundItemStop(omObjData *obj)
{
    float maxTime;
    float time;

    maxTime = BoardModelMotionMaxTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]);
    obj->scale.y += borderSpeed;
    if (obj->scale.y >= maxTime - 150.0f) {
        borderSpeed *= 0.9745f;
        if (borderSpeed < 0.08f) {
            borderSpeed = 0.08f;
        }
    }
    BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], borderSpeed);
    if (obj->scale.y >= maxTime) {
        BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], 0.0f);
        time = obj->scale.y - maxTime + BoardModelMotionTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]);
        if (time > maxTime) {
            time -= maxTime;
        }
        BoardModelMotionTimeSet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER], time);
        obj->work[0] = RoundItemItemGet(obj->work[2]);
        BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_LIGHT], 1);
        BoardModelPosSet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_LIGHT], itemObj[obj->work[0]]->trans.x, itemObj[obj->work[0]]->trans.y + 1.0f,
            itemObj[obj->work[0]]->trans.z);
        BoardModelRotSet(
            mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_LIGHT], itemObj[obj->work[0]]->rot.x, itemObj[obj->work[0]]->rot.y + 1.0f, itemObj[obj->work[0]]->rot.z);
        obj->work[1] = 60;
        BoardAudSeqFadeOut(1, 100);
        obj->func = RoundItemLightFlicker;
        HuAudFXPlay(0x40A);
    }
}

static void RoundItemLightFlicker(omObjData *obj)
{
    if ((obj->work[1] / 4) & 1) {
        BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_LIGHT], 0);
    }
    else {
        BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_LIGHT], 1);
    }
    if ((--obj->work[1]) == 0) {
        BoardModelVisibilitySet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_LIGHT], 0);
        ItemGetCreate(obj->work[0]);
        HuAudFXPlay(0x310);
        obj->func = RoundItemUmaJumpWait;
    }
}

static void RoundItemUmaJumpWait(omObjData *obj)
{
    Vec playerPos;
    Vec dir;

    if (itemGetObj->work[0] != 1) {
        return;
    }
    BoardPlayerPosGet(roundItemPlayer, &playerPos);
    VECSubtract(&roundItemPlayerPos, &playerPos, &dir);
    VECNormalize(&dir, &dir);
    obj->trans.x = dir.x;
    obj->trans.y = dir.y;
    obj->trans.z = dir.z;
    obj->rot.x = VECDistanceXZ(&roundItemPlayerPos, &playerPos);
    obj->scale.y = 20.0f + 40.0f * (obj->rot.x / 445.0f);
    obj->rot.y = 0.016666668f * (obj->scale.y / 2) * (obj->scale.y / 2);
    obj->rot.z = playerPos.y;
    obj->scale.x = 0.0f;
    BoardPlayerMotionShiftSet(roundItemPlayer, 4, 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    VECSubtract(&roundItemPlayerPos, &playerPos, &dir);
    VECNormalize(&dir, &dir);
    BoardPlayerRotSet(roundItemPlayer, 0.0f, RoundItemAngleGet(&dir), 0.0f);
    obj->func = RoundItemUmaJump;
}

static void RoundItemUmaJump(omObjData *obj)
{
    Vec pos;

    BoardPlayerPosGet(roundItemPlayer, &pos);
    pos.x += obj->trans.x * obj->rot.x / obj->scale.y;
    pos.z += obj->trans.z * obj->rot.x / obj->scale.y;
    pos.y += obj->rot.y - 0.016666668f * obj->scale.x * obj->scale.x;
    obj->scale.x += 1.0f;
    if (pos.y < roundItemPos.y || obj->scale.x >= obj->scale.y) {
        pos.y = roundItemPos.y;
        BoardCameraMotionStart(BoardPlayerModelGet(roundItemPlayer), NULL, 700.0f, -1.0f);
        BoardPlayerMotionStart(roundItemPlayer, 2, HU3D_MOTATTR_LOOP);
        obj->func = RoundItemRotatePlayer;
    }
    BoardPlayerPosSetV(roundItemPlayer, &pos);
}

static void RoundItemRotatePlayer(omObjData *obj)
{
    Vec rot;

    BoardPlayerRotGet(roundItemPlayer, &rot);
    if (rot.y == 0.0f) {
        BoardPlayerMotionShiftSet(roundItemPlayer, 1, 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
        itemGetObj->work[0] = 0;
        itemGetObj->func = ItemGetPlayerMove;
        obj->func = RoundItemStreamWait;
    }
    else if (rot.y > 180.0f) {
        if (360.0f - rot.y < 3.0f) {
            rot.y = 0.0f;
        }
        else {
            rot.y += 3.0f;
        }
    }
    else {
        if (rot.y < 3.0f) {
            rot.y = 0.0f;
        }
        else {
            rot.y -= 3.0f;
        }
    }
    BoardPlayerRotSetV(roundItemPlayer, &rot);
}

static void RoundItemStreamWait(omObjData *obj)
{
    if (itemGetObj->work[0] == 1) {
        BoardPlayerMotionShiftSet(roundItemPlayer, itemGetMotId, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        obj->work[0] = 30;
        roundItemStreamId = HuAudSStreamPlay(2);
        obj->func = RoundItemWinWait;
    }
}

static void RoundItemWinWait(omObjData *obj)
{
    Process *proc;

    if (obj->work[0] == 0) {
        if (HuAudSStreamStatGet(roundItemStreamId) == 0) {
            proc = HuPrcCreate(ItemGetWinExec, 0x2004, 0x1000, 0);
            proc->user_data = obj;
            BoardAudSeqPause(0, 0, 1000);
            obj->func = NULL;
        }
    }
    else {
        obj->work[0]--;
    }
}

static void ItemGetWinExec(void)
{
    omObjData *obj;

    BoardWinCreate(2, MAKE_MESSID(10, 6), 0);
    BoardWinInsertMesSet(MAKE_MESSID(8, itemGetObj->work[1]), 0);
    BoardWinWait();
    BoardWinKill();
    obj = HuPrcCurrentGet()->user_data;
    BoardPlayerMotionShiftSet(roundItemPlayer, 1, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    itemGetObj->work[0] = 0;
    HuAudFXPlay(0x30D);
    HuAudFXFadeOut(itemGetSeNo, 1000);
    itemGetObj->func = ItemGetShrink;
    obj->func = ItemGetShrinkWait;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void ItemGetShrinkWait(omObjData *obj)
{
    Process *proc;

    if (itemGetObj->work[0] == 1) {
        BoardPlayerItemAdd(roundItemPlayer, itemGetObj->work[1]);
        omVibrate(roundItemPlayer, 12, 6, 6);
        proc = HuPrcCreate(ItemGetReturnWinExec, 0x2004, 0x1000, 0);
        proc->user_data = obj;
        obj->func = NULL;
    }
}

static void ItemGetReturnWinExec(void)
{
    omObjData *obj;

    BoardWinCreate(2, MAKE_MESSID(10, 7), 0);
    BoardWinWait();
    BoardWinKill();
    obj = HuPrcCurrentGet()->user_data;
    obj->func = RoundItemGameClose;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void RoundItemGameClose(omObjData *obj)
{
    BoardStatusShowSetAll(1);
    BoardCameraTargetModelSet(mapObjMdlId[MAPOBJ_ROUNDITEM_ITEM_UP]);
    BoardCameraOffsetSet(0.0f, 0.0f, 0.0f);
    BoardCameraXRotZoomSet(1200.0f, -45.0f);
    BoardModelMotionSpeedSet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA], 1.0f);
    Hu3DModelKill(itemGetObj->model[0]);
    Hu3DModelKill(itemGetObj->model[1]);
    Hu3DModelKill(itemGetObj->model[2]);
    omDelObjEx(HuPrcCurrentGet(), itemGetObj);
    obj->func = RoundItemGameEnd;
}

static void RoundItemGameEnd(omObjData *obj)
{
    if (BoardStatusStopCheck(roundItemPlayer) && BoardCameraMotionIsDone()) {
        RoundItemEnd();
        obj->func = NULL;
    }
}

static void RoundItemItemUpdate(omObjData *obj)
{
    float time;
    float rotY;
    float maxTime;

    time = BoardModelMotionTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]);
    maxTime = BoardModelMotionMaxTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]);
    rotY = 90.0f - 90.0f * obj->work[2] + 360.0f * (time / maxTime);
    if (rotY >= 360.0f) {
        rotY -= 360.0f;
    }
    if (rotY < 0.0f) {
        rotY += 360.0f;
    }
    omSetRot(obj, 0.0f, rotY, 0.0f);
}

static s16 RoundItemItemGet(u32 umaNo)
{
    float umaMaxTime;
    float umaAngle;
    float borderAngle;
    float angle;
    float umaTime;

    borderAngle = 360.0f - 360.0f * (BoardModelMotionTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]) / BoardModelMotionMaxTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]));
    umaTime = BoardModelMotionTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]);
    umaMaxTime = BoardModelMotionMaxTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]);
    umaTime = umaTime - (umaMaxTime / 4) * umaNo;
    if (umaTime < 0.0f) {
        umaTime += umaMaxTime;
    }
    umaAngle = 360.0f * (umaTime / umaMaxTime);
    angle = umaAngle - borderAngle;
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    angle /= 90.0f;
    return angle;
}

static void ItemGetCreate(s16 itemNo)
{
    omObjData *obj;
    float *data;
    float borderAngle;
    float posX;
    float posY;
    float posZ;
    float angle;

    obj = itemGetObj = omAddObjEx(boardObjMan, 0x165, 3, 0, -1, ItemGetObjUpdate);
    obj->model[0] = itemObj[itemNo]->model[1];
    Hu3DModelAttrReset(obj->model[0], HU3D_ATTR_DISPOFF);
    itemGetObj->work[1] = itemObj[itemNo]->work[1];
    itemGetObj->data = HuMemDirectMallocNum(HEAP_SYSTEM, 3 * sizeof(float), MEMORY_DEFAULT_NUM);
    data = itemGetObj->data;
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 0.0f, 0.0f, 0.0f);
    borderAngle = 360.0f - 360.0f * (BoardModelMotionTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]) / BoardModelMotionMaxTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_BORDER]));
    angle = 45.0f + borderAngle + 90.0f * itemNo;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    posX = roundItemPos.x - 100.0 * cosd(angle);
    posZ = roundItemPos.z - 100.0 * sind(angle);
    posY = roundItemPos.y + 66.0f + 1.0f;
    omSetTra(obj, posX, posY, posZ);
    obj->work[0] = 0;
    data[0] = 0.1f;
    data[2] = 20.0f;
    data[1] = 0.0f;
    obj->model[1] = Hu3DParticleCreate(roundItemEffAnim, 200);
    obj->model[2] = Hu3DParticleCreate(roundItemEffAnim, 100);
    Hu3DParticleHookSet(obj->model[1], ItemGetEff1Hook);
    Hu3DParticleHookSet(obj->model[2], ItemGetEff2Hook);
    Hu3DParticleColSet(obj->model[1], 0xFF, 0xFF, 0);
    Hu3DParticleColSet(obj->model[2], 0xFF, 0xFF, 0);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[2], posX, posY, posZ);
    Hu3DParticleBlendModeSet(obj->model[1], 1);
    Hu3DParticleBlendModeSet(obj->model[2], 1);
    Hu3DModelLayerSet(obj->model[1], 3);
    Hu3DModelLayerSet(obj->model[2], 3);
    itemGetSeNo = HuAudFXPlay(0x35F);
}

static void ItemGetObjUpdate(omObjData *obj)
{
    float *data;
    float scale;

    data = obj->data;
    scale = data[0];
    if (obj->work[0] == 0) {
        if (scale > 1.0f) {
            scale = 1.0f;
        }
        else {
            data[0] += 0.025f;
        }
        obj->trans.y += data[2];
        data[2] -= 1.0f;
        if (data[2] < 0.0f && obj->trans.y < roundItemPos.y + 66.0f + 1.0f + 90.0f) {
            obj->work[0] = 1;
        }
        omSetSca(obj, scale, scale, scale);
    }
    else {
        obj->trans.y += sind(data[1]);
        data[1] += 4.0f;
        if (data[1] >= 360.0f) {
            data[1] -= 360.0f;
        }
    }
}

static void ItemGetPlayerMove(omObjData *obj)
{
    Vec playerPos;
    Vec objPos;
    Vec dir;
    float var_f28;
    float *data;

    data = obj->data;
    if (obj->work[0] == 0) {
        BoardPlayerPosGet(roundItemPlayer, &playerPos);
        objPos.x = obj->trans.x;
        objPos.y = 0.0f;
        objPos.z = obj->trans.z;
        playerPos.y = 0.0f;
        VECSubtract(&playerPos, &objPos, &dir);
        VECNormalize(&dir, &dir);
        var_f28 = VECDistanceXZ(&playerPos, &objPos);
        if (var_f28 < 8.0f) {
            obj->trans.x = playerPos.x;
            obj->trans.z = playerPos.z;
            obj->work[0] = 1;
        }
        else {
            obj->trans.x += 8.0f * dir.x;
            obj->trans.z += 8.0f * dir.z;
        }
    }
    obj->trans.y += sind(data[1]);
    data[1] += 4.0f;
    if (data[1] >= 360.0f) {
        data[1] -= 360.0f;
    }
}

static void ItemGetShrink(omObjData *obj)
{
    float *data;

    data = obj->data;
    if (obj->work[0] == 0) {
        data[0] -= 0.016666668f;
        if (data[0] <= 0.0f) {
            data[0] = 0.0f;
            obj->work[0] = 1;
            HuAudFXStop(itemGetSeNo);
        }
        obj->trans.y -= 2.1666667f;
    }
    omSetSca(obj, data[0], data[0], data[0]);
}

static float RoundItemUmaRotYGet(u32 umaNo)
{
    float time;
    float maxTime;
    float rotY;

    time = BoardModelMotionTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]);
    maxTime = BoardModelMotionMaxTimeGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]);
    time = time - (maxTime / 4) * umaNo;
    if (time < 0.0f) {
        time += maxTime;
    }
    rotY = 180.0f + -360.0f * (time / maxTime);
    if (rotY >= 360.0f) {
        rotY -= 360.0f;
    }
    if (rotY < 0.0f) {
        rotY += 360.0f;
    }
    return rotY;
}

static void RoundItemUmaPlayerSet(u32 umaNo)
{
    Hu3DModelObjPosGet(BoardModelIDGet(mapObjMdlId[MAPOBJ_ROUNDITEM_UMA]), umaHookTbl[umaNo], &umaPos);
    BoardPlayerPosSetV(roundItemPlayer, &umaPos);
    BoardPlayerRotSet(roundItemPlayer, 0.0f, RoundItemUmaRotYGet(umaNo), 0.0f);
}

static float RoundItemAngleGet(Vec *dir)
{
    float angle;

    if (dir->x || dir->z) {
        if (dir->x == 0.0f) {
            if (dir->z > 0.0f) {
                return 0.0f;
            }
            else {
                return 180.0f;
            }
        }
        if (dir->z == 0.0f) {
            if (dir->x > 0.0f) {
                return 90.0f;
            }
            else {
                return 270.0f;
            }
        }
        angle = atan2d(dir->z, dir->x);
        if (dir->z < 0.0f) {
            angle = 90.0f - angle;
        }
        else {
            angle = 90.0f - angle;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
        }
        return angle;
    }
    return -1.0f;
}

static void ItemGetEff1Hook(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *particleDataP;
    float angle;
    float radius;
    float radiusBase;
    s32 j;
    s32 i;

    if (particle->unk_34 == 0) {
        particleDataP = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, particleDataP++) {
            particleDataP->unk40.a = 0;
            particleDataP->unk2C = 0.0f;
        }
        particle->unk_00 = 0;
    }
    radiusBase = itemGetObj->scale.x;
    for (i = 0; i < 30; i++) {
        particleDataP = particle->unk_48;
        for (j = 0; j < particle->unk_30; j++, particleDataP++) {
            if (particleDataP->unk2C == 0.0f) {
                break;
            }
        }
        if (j != particle->unk_30) {
            angle = 0.003921569f * frand8() * 360.0f;
            radius = 0.003921569f * frand8() * 70.0f * radiusBase;
            particleDataP->unk34.x = itemGetObj->trans.x + radius * sind(angle);
            particleDataP->unk34.z = itemGetObj->trans.z + radius * cosd(angle);
            particleDataP->unk34.y = itemGetObj->trans.y + radiusBase * (-30.0f + 0.003921569f * frand8() * 60.0f);
            particleDataP->unk08.x = 0.5f + 0.003921569f * frand8() * 3.0f;
            particleDataP->unk08.y = 0.3f + 0.003921569f * frand8() * 2.0f;
            particleDataP->unk40.a = 0xB4;
            particleDataP->unk2C = 15.0f * radiusBase;
        }
    }
    particleDataP = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, particleDataP++) {
        if (particleDataP->unk2C != 0.0f) {
            particleDataP->unk34.y -= particleDataP->unk08.x;
            particleDataP->unk2C -= particleDataP->unk08.y;
            if (particleDataP->unk2C <= 0.0f) {
                particleDataP->unk2C = 0.0f;
            }
        }
    }
}

static void ItemGetEff2Hook(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *particleDataP;
    float angle2;
    float angle;
    float radius;
    s32 j;
    s32 i;

    if (particle->unk_34 == 0) {
        particleDataP = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, particleDataP++) {
            particleDataP->unk40.a = 0;
            particleDataP->unk2C = 0.0f;
        }
        particle->unk_00 = 0;
    }
    if (particle->unk_00 == 0) {
        particleDataP = particle->unk_48;
        for (j = 0; j < particle->unk_30; j++, particleDataP++) {
            angle = 0.003921569f * frand8() * 360.0f;
            radius = 0.003921569f * frand8() * 50.0f;
            particleDataP->unk08.x = radius * cosd(angle);
            particleDataP->unk08.y = 2.0f + 0.003921569f * frand8() * 4.0f;
            particleDataP->unk08.z = radius * sind(angle);
            angle2 = 60.0f + 20.0f * frand8() * 0.003921569f;
            radius = 4.0f + 5.0f * frand8() * 0.003921569f;
            particleDataP->unk14.x = radius * sind(angle) * cosd(angle2);
            particleDataP->unk14.y = radius * sind(angle2);
            particleDataP->unk14.z = radius * cosd(angle) * cosd(angle2);
            particleDataP->unk20 = 1.0f;
            particleDataP->unk40.a = 0xB4;
            particleDataP->unk2C = 9.0f + 0.003921569f * frand8() * 4.0f;
        }
        particle->unk_00 = 1;
    }
    particleDataP = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, particleDataP++) {
        if (particleDataP->unk2C != 0.0f) {
            particleDataP->unk34.x = particleDataP->unk08.x + particleDataP->unk14.x * particleDataP->unk20;
            particleDataP->unk34.z = particleDataP->unk08.z + particleDataP->unk14.z * particleDataP->unk20;
            particleDataP->unk34.y = particleDataP->unk08.y + particleDataP->unk14.y * particleDataP->unk20 - 0.2f * particleDataP->unk20 * particleDataP->unk20;
            particleDataP->unk2C -= 0.25f;
            particleDataP->unk20 += 1.0f;
            if (particleDataP->unk2C <= 0.0f) {
                particleDataP->unk2C = 0.0f;
            }
        }
    }
}
