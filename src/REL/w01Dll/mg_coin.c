#include "REL/w01Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"

#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/window.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/window.h"

#include "dolphin.h"
#include "ext_math.h"

extern s32 rand8(void);

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ float len;
} SpaceAmidaPathPoint; // Size 0x10

typedef SpaceAmidaPathPoint SpaceAmidaMap[15];

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ Vec rocketPos;
    /* 0x10 */ Vec jumpDir;
    /* 0x1C */ u16 waitTime;
    /* 0x20 */ float jumpTime;
    /* 0x24 */ u16 comDelay;
    /* 0x26 */ s16 comChoice;
    /* 0x28 */ s16 comInputTimer;
} SpaceAmidaGameWork; // Size 0x2C

typedef struct {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ SpaceAmidaMap *map;
    /* 0x08 */ u16 mapCursor;
    /* 0x0C */ float len;
    /* 0x10 */ float speed;
    /* 0x14 */ float maxSpeed;
    /* 0x18 */ float rocketXOfs;
    /* 0x1C */ float kemuriSize;
    /* 0x20 */ Vec kemuriScale;
    /* 0x2C */ Vec kemuriScaleVel;
    /* 0x38 */ float kemuriTPLvl;
    /* 0x3C */ float unk3C;
    /* 0x40 */ s16 targetNo;
} RocketWork; // Size 0x44

static void SpaceAmidaMainUpdate(omObjData *obj);
static void SpaceAmidaStop(void);
static void SpaceAmidaKill(void);
static void SpaceAmidaRocketObjUpdate(omObjData *obj);
static float SpaceAmidaMapLenGet(SpaceAmidaMap *obj);
static void SpaceAmidaComChoiceSet(omObjData *obj);
static void SpaceAmidaComInputGet(omObjData *obj, u16 *stkBtn, u16 *btn);
static void SpaceAmidaGameOpen(omObjData *obj);
static void SpaceAmidaGameUpdate(omObjData *obj);
static void SpaceAmidaRocketJump(omObjData *obj);
static void SpaceAmidaRocketKemuriExec(omObjData *obj);
static void SpaceAmidaRocketWait(omObjData *obj);
static void SpaceAmidaRocketUp(omObjData *obj);
static void SpaceAmidaCoinWin(void);
static void SpaceAmidaJumpDown(omObjData *obj);
static void SpaceAmidaCoinRainMain(void);
static void SpaceAmidaReturnWinMain(void);
static void SpaceAmidaGameStop(omObjData *obj);
static void SpaceAmidaDirGet(Vec *a, Vec *b, Vec *result);
static float SpaceAmidaAngleGet(Vec *dir);
static u32 SpaceAmidaPlayerRotAdd(Vec *rocketPos, float delta);
static void SpaceAmidaEffCreate(void);
static void SpaceAmidaEffKill(void);
static void SpaceAmidaEffUpdate(omObjData *arg0);
static void SpaceAmidaEffParticleHook(ModelData *model, ParticleData *particle, Mtx matrix);

static s32 spaceAmidaPadNo;
static s32 spaceAmidaPlayerNo;
static s16 spaceAmidaMdlId;
static s16 mapMdlId[3];
static s16 rocketMdlId[3];
static s16 spaceAmidaEffMdlId;
static s16 coinMdlId[20];
static Process *coinWinProc;
static omObjData *spaceAmidaMainObj;
static float spaceAmidaTime;
static s16 kemuriMdlId;
static s32 timerSec;
static s32 timerFrame;
static s16 timerSeqId;
static Vec spaceAmidaPos;
static s32 spaceAmidaMapNo;
static s32 spaceAmidaPath;
static s32 rocketWarpF;
static u16 spaceAmidaStopF;
static u16 spaceAmidaCoinNum;
static s32 spaceAmidaSeNo;
static omObjData *spaceAmidaGameObj;
static omObjData *rocketObj[3];
static omObjData *spaceAmidaEffObj;
static AnimData *spaceAmidaEffAnim;
static s16 spaceAmidaSeqStopF;

static Vec effPosTbl[3] = { { -50.0f, 238.0f, 0.0f }, { 0.0f, 275.5f, 0.0f }, { 50.0f, 238.0f, 0.0f } };

static u16 spaceAmidaCoinNumTbl[3][3] = { { 10, 5, 20 }, { 10, 5, 20 }, { 5, 20, 10 } };

static SpaceAmidaMap spaceAmidaMap1[3]
    = { { { { -50.0f, -12.0f, 0.0f }, 75.0f }, { { -50.0f, 63.0f, 0.0f }, 50.0f }, { { 0.0f, 63.0f, 0.0f }, 25.0f }, { { 0.0f, 88.0f, 0.0f }, 50.0f },
            { { 50.0f, 88.0f, 0.0f }, 87.5f }, { { 50.0f, 175.5f, 0.0f }, 0.0f } },
          { { { 0.0f, -12.0f, 0.0f }, 75.0f }, { { 0.0f, 63.0f, 0.0f }, 50.0f }, { { -50.0f, 63.0f, 0.0f }, 50.0f },
              { { -50.0f, 113.0f, 0.0f }, 50.0f }, { { 0.0f, 113.0f, 0.0f }, 50.0f }, { { 0.0f, 163.0f, 0.0f }, 50.0f },
              { { -50.0f, 163.0f, 0.0f }, 12.5f }, { { -50.0f, 175.5f, 0.0f }, 0.0f } },
          { { { 50.0f, -12.0f, 0.0f }, 100.0f }, { { 50.0f, 88.0f, 0.0f }, 50.0f }, { { 0.0f, 88.0f, 0.0f }, 25.0f },
              { { 0.0f, 113.0f, 0.0f }, 50.0f }, { { -50.0f, 113.0f, 0.0f }, 50.0f }, { { -50.0f, 163.0f, 0.0f }, 50.0f },
              { { 0.0f, 163.0f, 0.0f }, 50.0f }, { { 0.0f, 213.0f, 0.0f }, 0.0f } } };

static SpaceAmidaMap spaceAmidaMap2[3]
    = { { { { -50.0f, -12.0f, 0.0f }, 125.0f }, { { -50.0f, 113.0f, 0.0f }, 50.0f }, { { 0.0f, 113.0f, 0.0f }, 25.0f },
            { { 0.0f, 138.0f, 0.0f }, 50.0f }, { { 50.0f, 138.0f, 0.0f }, 37.5f }, { { 50.0f, 175.5f, 0.0f }, 0.0f } },
          { { { 0.0f, -12.0f, 0.0f }, 75.0f }, { { 0.0f, 63.0f, 0.0f }, 50.0f }, { { 50.0f, 63.0f, 0.0f }, 75.0f },
              { { 50.0f, 138.0f, 0.0f }, 50.0f }, { { 0.0f, 138.0f, 0.0f }, 25.0f }, { { 0.0f, 163.0f, 0.0f }, 50.0f },
              { { -50.0f, 163.0f, 0.0f }, 12.5f }, { { -50.0f, 175.5f, 0.0f }, 0.0f } },
          { { { 50.0f, -12.0f, 0.0f }, 75.0f }, { { 50.0f, 63.0f, 0.0f }, 50.0f }, { { 0.0f, 63.0f, 0.0f }, 50.0f },
              { { 0.0f, 113.0f, 0.0f }, 50.0f }, { { -50.0f, 113.0f, 0.0f }, 50.0f }, { { -50.0f, 163.0f, 0.0f }, 50.0f },
              { { 0.0f, 163.0f, 0.0f }, 50.0f }, { { 0.0f, 213.0f, 0.0f }, 0.0f } } };

static SpaceAmidaMap spaceAmidaMap3[3]
    = { { { { -50.0f, -12.0f, 0.0f }, 100.0f }, { { -50.0f, 88.0f, 0.0f }, 50.0f }, { { 0.0f, 88.0f, 0.0f }, 50.0f },
            { { 0.0f, 138.0f, 0.0f }, 50.0f }, { { -50.0f, 138.0f, 0.0f }, 37.5f }, { { -50.0f, 175.5f, 0.0f }, 0.0f } },
          { { { 0.0f, -12.0f, 0.0f }, 75.0f }, { { 0.0f, 63.0f, 0.0f }, 50.0f }, { { 50.0f, 63.0f, 0.0f }, 100.0f },
              { { 50.0f, 163.0f, 0.0f }, 50.0f }, { { 0.0f, 163.0f, 0.0f }, 50.0f }, { { 0.0f, 213.0f, 0.0f }, 0.0f } },
          { { { 50.0f, -12.0f, 0.0f }, 75.0f }, { { 50.0f, 63.0f, 0.0f }, 50.0f }, { { 0.0f, 63.0f, 0.0f }, 25.0f }, { { 0.0f, 88.0f, 0.0f }, 50.0f },
              { { -50.0f, 88.0f, 0.0f }, 50.0f }, { { -50.0f, 138.0f, 0.0f }, 50.0f }, { { 0.0f, 138.0f, 0.0f }, 25.0f },
              { { 0.0f, 163.0f, 0.0f }, 50.0f }, { { 50.0f, 163.0f, 0.0f }, 12.5f }, { { 50.0f, 175.5f, 0.0f }, 0.0f } } };

void SpaceAmidaExec(void)
{
    Vec rocketMdlOfs[3];
    Vec pos;
    Vec rocketPos;
    Vec scale;
    SpaceAmidaGameWork *gameObjWork;
    RocketWork *rocketWork;
    s32 i;

    spaceAmidaPadNo = GWPlayer[GWSystem.player_curr].port;
    spaceAmidaMdlId = mapObjMdlId[MAPOBJ_SPACEAMIDA];
    mapMdlId[0] = mapObjMdlId[MAPOBJ_SPACEAMIDA_MAP1];
    mapMdlId[1] = mapObjMdlId[MAPOBJ_SPACEAMIDA_MAP2];
    mapMdlId[2] = mapObjMdlId[MAPOBJ_SPACEAMIDA_MAP3];
    rocketMdlId[0] = mapObjMdlId[MAPOBJ_SPACEAMIDA_ROCKET1];
    rocketMdlId[1] = mapObjMdlId[MAPOBJ_SPACEAMIDA_ROCKET2];
    rocketMdlId[2] = mapObjMdlId[MAPOBJ_SPACEAMIDA_ROCKET3];
    BoardModelVisibilitySet(mapMdlId[0], 0);
    BoardModelVisibilitySet(mapMdlId[1], 0);
    BoardModelVisibilitySet(mapMdlId[2], 0);
    spaceAmidaMapNo = rand8() % 3;
    BoardModelVisibilitySet(mapMdlId[spaceAmidaMapNo], 1);
    BoardModelMotionStart(mapMdlId[spaceAmidaMapNo], 0, HU3D_MOTATTR_LOOP);
    BoardModelPosGet(spaceAmidaMdlId, &pos);
    scale.x = scale.y = scale.z = 1.0f;
    for (i = 0; i < 3; i++) {
        rocketMdlOfs[i] = spaceAmidaMap1[i][0].pos;
        rocketMdlOfs[i].y -= -12.0f;
        BoardModelPosSet(rocketMdlId[i], pos.x + rocketMdlOfs[i].x, pos.y + rocketMdlOfs[i].y, pos.z + 30.0f);
        BoardModelVisibilitySet(rocketMdlId[i], 1);
        BoardModelScaleSetV(rocketMdlId[i], &scale);
    }
    spaceAmidaPlayerNo = GWSystem.player_curr;
    BoardModelPosGet(spaceAmidaMdlId, &spaceAmidaPos);
    spaceAmidaPath = 1;
    BoardModelPosGet(rocketMdlId[spaceAmidaPath], &rocketPos);
    BoardPlayerPosGet(spaceAmidaPlayerNo, &pos);
    spaceAmidaMainObj = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, SpaceAmidaMainUpdate);
    spaceAmidaGameObj = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, SpaceAmidaGameOpen);
    spaceAmidaGameObj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(SpaceAmidaGameWork), MEMORY_DEFAULT_NUM);
    gameObjWork = spaceAmidaGameObj->data;
    gameObjWork->unk02 = 0;
    gameObjWork->rocketPos = rocketPos;
    gameObjWork->comInputTimer = 0;
    SpaceAmidaPlayerRotAdd(&rocketPos, 0.0f);
    SpaceAmidaComChoiceSet(spaceAmidaGameObj);
    kemuriMdlId = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_W01, 19));
    Hu3DModelAttrSet(kemuriMdlId, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 3; i++) {
        rocketObj[i] = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, SpaceAmidaRocketObjUpdate);
        rocketObj[i]->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(RocketWork), MEMORY_DEFAULT_NUM);
        rocketObj[i]->work[0] = rocketMdlId[i];
        rocketObj[i]->work[1] = 0;
        rocketObj[i]->work[3] = 0;
        rocketWork = rocketObj[i]->data;
        if (i == spaceAmidaPath) {
            rocketObj[i]->work[2] = 1;
        }
        else {
            rocketObj[i]->work[2] = 0;
        }
        rocketWork->rocketXOfs = 1.0f;
        rocketWork->kemuriSize = 0.0f;
    }
    rocketWarpF = 0;
    timerSec = 5;
    timerFrame = REFRESH_RATE;
    spaceAmidaStopF = 0;
    SpaceAmidaEffCreate();
    spaceAmidaEffMdlId = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 17), NULL, 0);
    BoardModelMotionUpdateSet(spaceAmidaEffMdlId, 1);
    BoardModelVisibilitySet(spaceAmidaEffMdlId, 0);
    for (i = 0; i < 20; i++) {
        coinMdlId[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 1);
        BoardModelVisibilitySet(coinMdlId[i], 0);
    }
}

static void SpaceAmidaMainUpdate(omObjData *obj)
{
    if (spaceAmidaStopF == 0) {
        return;
    }
    if (BoardMGDoneFlagGet() == 1) {
        if (spaceAmidaTime <= 0.0f) {
            SpaceAmidaKill();
            omDelObjEx(HuPrcCurrentGet(), obj);
        }
    }
    spaceAmidaTime -= 1.0f;
}

static void SpaceAmidaStop(void)
{
    float time;

    spaceAmidaStopF = 1;
    BoardMGExit();
    time = BoardModelMotionTimeGet(spaceAmidaMdlId);
    spaceAmidaTime = time;
    BoardModelMotionStart(spaceAmidaMdlId, 0, 0);
    BoardModelMotionTimeSet(spaceAmidaMdlId, time);
    BoardModelMotionSpeedSet(spaceAmidaMdlId, -1.0f);
}

static void SpaceAmidaKill(void)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        BoardModelVisibilitySet(mapMdlId[i], 0);
        BoardModelVisibilitySet(rocketMdlId[i], 0);
        omDelObjEx(HuPrcCurrentGet(), rocketObj[i]);
    }
    for (i = 0; i < 20; i++) {
        BoardModelKill(coinMdlId[i]);
    }
    SpaceAmidaEffKill();
    BoardModelKill(spaceAmidaEffMdlId);
    BoardMGDoneFlagSet(0);
    Hu3DModelKill(kemuriMdlId);
}

static void SpaceAmidaRocketObjUpdate(omObjData *obj)
{
    RocketWork *work;
    Vec scale;
    Vec pos;
    Vec rocketPos;
    Vec dir;
    float len;

    work = obj->data;
    BoardModelScaleGet(obj->work[0], &scale);
    switch (obj->work[2]) {
        case 1:
            if ((scale.x += 0.08f) >= 1.5f) {
                scale.x = 1.5f;
                scale.y = 1.5f;
                if (obj->work[3] == 1) {
                    obj->work[2] = 0;
                }
                else {
                    obj->work[2] = 2;
                }
            }
            else {
                scale.y += 0.08f;
            }
            BoardModelScaleSetV(obj->work[0], &scale);
            break;
        case 2:
            if ((scale.x -= 0.08f) <= 1.0f) {
                scale.x = 1.0f;
                scale.y = 1.0f;
                if (obj->work[1] == 1) {
                    obj->work[2] = 0;
                    obj->work[1] = 0;
                }
                else {
                    obj->work[2] = 1;
                }
            }
            else {
                scale.y -= 0.08f;
            }
            BoardModelScaleSetV(obj->work[0], &scale);
            break;
        case 3:
            switch (spaceAmidaMapNo) {
                case 0:
                    work->map = &spaceAmidaMap1[spaceAmidaPath];
                    break;
                case 1:
                    work->map = &spaceAmidaMap2[spaceAmidaPath];
                    break;
                case 2:
                    work->map = &spaceAmidaMap3[spaceAmidaPath];
                    break;
            }
            BoardModelPosGet(obj->work[0], &rocketPos);
            rocketPos.x = spaceAmidaPos.x + ((*work->map)[0].pos.x + work->rocketXOfs);
            work->rocketXOfs = -work->rocketXOfs;
            BoardModelPosSetV(obj->work[0], &rocketPos);
            rocketPos.y += 5.0f;
            BoardPlayerPosSetV(spaceAmidaPlayerNo, &rocketPos);
            work->kemuriSize += 0.022222223f;
            work->kemuriTPLvl -= 0.011111111f;
            if (work->kemuriTPLvl < 0.0f) {
                work->kemuriTPLvl = 0.0f;
            }
            Hu3DModelTPLvlSet(kemuriMdlId, work->kemuriTPLvl);
            if (work->kemuriSize > 1.0f) {
                work->kemuriSize = 1.0f;
            }
            VECAdd(&work->kemuriScale, &work->kemuriScaleVel, &work->kemuriScale);
            if (work->kemuriScale.y >= 4.0f) {
                work->kemuriScale.y = 4.0f;
                work->kemuriScaleVel.y = -0.1f;
            }
            if (work->kemuriScale.y < 1.0f) {
                work->kemuriScale.y = 1.0f;
            }
            Hu3DModelScaleSet(kemuriMdlId, work->kemuriScale.x, work->kemuriScale.y, work->kemuriScale.z);
            break;
        case 4:
            Hu3DModelAttrSet(kemuriMdlId, HU3D_ATTR_DISPOFF);
            obj->work[2] = 5;
            work->mapCursor = 0;
            work->len = 12.0f;
            work->maxSpeed = (SpaceAmidaMapLenGet(work->map) - work->len) / 90.0f;
            work->speed = work->maxSpeed / 20.0f;
            HuAudFXPlay(0x406);
            HuAudFXPlay(0x407);
            HuAudFXStop(spaceAmidaSeNo);
            break;
        case 5:
            len = work->len + work->speed;
            work->len = len;
            work->speed *= 1.04f;
            if (work->speed > work->maxSpeed) {
                work->speed = work->maxSpeed;
            }
            BoardModelPosGet(obj->work[0], &pos);
            while (len >= (*work->map)[work->mapCursor].len) {
                len -= (*work->map)[work->mapCursor].len;
                work->mapCursor++;
                if ((*work->map)[work->mapCursor].len == 0.0f) {
                    omVibrate(spaceAmidaPlayerNo, 12, 6, 6);
                    len = 0.0f;
                    rocketWarpF = 1;
                    spaceAmidaSeNo = HuAudFXPlay(0x332);
                    spaceAmidaSeqStopF = 0;
                    obj->work[2] = 6;
                    if (pos.x - spaceAmidaPos.x < -25.0f) {
                        work->targetNo = 0;
                        spaceAmidaCoinNum = 5;
                    }
                    else if (pos.x - spaceAmidaPos.x > 25.0f) {
                        work->targetNo = 2;
                        spaceAmidaCoinNum = 10;
                    }
                    else {
                        work->targetNo = 1;
                        spaceAmidaCoinNum = 20;
                    }
                    break;
                }
            }
            work->len = len;
            rocketPos.x = rocketPos.y = rocketPos.z = 0.0f;
            if (rocketWarpF == 0) {
                SpaceAmidaDirGet(&(*work->map)[work->mapCursor].pos, &(*work->map)[work->mapCursor + 1].pos, &dir);
                pos.x = spaceAmidaPos.x + (dir.x * len + (*work->map)[work->mapCursor].pos.x);
                pos.y = spaceAmidaPos.y + (dir.y * len + (*work->map)[work->mapCursor].pos.y);
            }
            else {
                pos.x = spaceAmidaPos.x + (*work->map)[work->mapCursor].pos.x;
                pos.y = spaceAmidaPos.y + (*work->map)[work->mapCursor].pos.y;
            }
            BoardModelPosSetV(obj->work[0], &pos);
            pos.y += 5.0f;
            BoardPlayerPosSetV(spaceAmidaPlayerNo, &pos);
            BoardModelRotSetV(obj->work[0], &rocketPos);
            BoardPlayerRotSetV(spaceAmidaPlayerNo, &rocketPos);
            break;
        case 6:
            if (spaceAmidaSeqStopF == 0 && (HuAudFXStatusGet(spaceAmidaSeNo) == 1 || HuAudFXStatusGet(spaceAmidaSeNo) == 0)) {
                BoardAudSeqPause(0, 0, 1000);
                spaceAmidaSeqStopF = 1;
            }
            BoardModelVisibilitySet(spaceAmidaEffMdlId, 1);
            pos.x = spaceAmidaPos.x + effPosTbl[work->targetNo].x;
            pos.y = spaceAmidaPos.y + effPosTbl[work->targetNo].y;
            pos.z = spaceAmidaPos.z + effPosTbl[work->targetNo].z;
            BoardModelPosSetV(spaceAmidaEffMdlId, &pos);
            work->kemuriSize -= 0.05f;
            if (work->kemuriSize <= 0.0f) {
                work->kemuriSize = 0.0f;
            }
            break;
    }
}

static float SpaceAmidaMapLenGet(SpaceAmidaMap *arg0)
{
    float len;
    s32 i;

    len = 0.0f;
    i = 0;
    while (TRUE) {
        if ((*arg0)[i].len == 0.0f) {
            break;
        }
        len += (*arg0)[i].len;
        i++;
    }
    return len;
}

static void SpaceAmidaComChoiceSet(omObjData *obj)
{
    SpaceAmidaGameWork *work;
    u16 chance[] = { 20, 60, 120, 190 };
    s32 i;

    work = obj->data;
    if (rand8() < chance[GWPlayerCfg[spaceAmidaPlayerNo].diff]) {
        for (i = 0; i < 3; i++) {
            if (spaceAmidaCoinNumTbl[spaceAmidaMapNo][i] == 20) {
                work->comChoice = i;
            }
        }
    }
    else {
        work->comChoice = rand8() % 3;
    }
    work->comDelay = rand8() % 20 + 20;
}

static void SpaceAmidaComInputGet(omObjData *obj, u16 *stkBtn, u16 *btn)
{
    SpaceAmidaGameWork *work;

    work = obj->data;
    *stkBtn = *btn = 0;
    if (work->comDelay != 0) {
        work->comDelay--;
        return;
    }
    if (work->comInputTimer >= 4 || (rand8() & 1)) {
        if (work->comChoice == spaceAmidaPath) {
            *btn |= PAD_BUTTON_A;
        }
        else if (work->comChoice < spaceAmidaPath) {
            *stkBtn |= PAD_BUTTON_LEFT;
        }
        else {
            *stkBtn |= PAD_BUTTON_RIGHT;
        }
        work->comDelay = rand8() % 10 + 10;
    }
    else {
        work->comInputTimer++;
        work->comDelay = rand8() % 10 + 20;
        if (spaceAmidaPath == 0) {
            *stkBtn |= PAD_BUTTON_RIGHT;
        }
        else if (spaceAmidaPath == 2) {
            *stkBtn |= PAD_BUTTON_LEFT;
        }
        else if (rand8() & 1) {
            *stkBtn |= PAD_BUTTON_LEFT;
        }
        else {
            *stkBtn |= PAD_BUTTON_RIGHT;
        }
    }
}

static void SpaceAmidaGameOpen(omObjData *obj)
{
    if (BoardModelMotionTimeGet(spaceAmidaMdlId) >= BoardModelMotionMaxTimeGet(spaceAmidaMdlId)) {
        timerSeqId = MGSeqCreate(1, timerSec, 0x120, 0x40);
        spaceAmidaGameObj->func = SpaceAmidaGameUpdate;
        BoardMusStart(1, 0xF, 0x7F, 0);
        spaceAmidaSeNo = HuAudFXPlay(0x408);
    }
}

static void SpaceAmidaGameUpdate(omObjData *obj)
{
    SpaceAmidaGameWork *work;
    Vec rocketPos;
    Vec playerPos;
    float jumpDist;
    u16 btn;
    u16 stkBtn;

    work = obj->data;
    if ((--timerFrame) == 0) {
        if ((--timerSec) >= 0) {
            MGSeqParamSet(timerSeqId, 1, timerSec);
        }
        timerFrame = REFRESH_RATE;
    }
    if (GWPlayerCfg[spaceAmidaPlayerNo].iscom == 1) {
        SpaceAmidaComInputGet(obj, &stkBtn, &btn);
    }
    else {
        stkBtn = HuPadDStkRep[spaceAmidaPadNo];
        btn = HuPadBtnDown[spaceAmidaPadNo];
    }
    if ((stkBtn & PAD_BUTTON_LEFT) && spaceAmidaPath != 0) {
        rocketObj[spaceAmidaPath]->work[1] = 1;
        rocketObj[spaceAmidaPath]->work[2] = 2;
        spaceAmidaPath--;
        rocketObj[spaceAmidaPath]->work[2] = 1;
    }
    if ((stkBtn & PAD_BUTTON_RIGHT) && spaceAmidaPath != 2) {
        rocketObj[spaceAmidaPath]->work[1] = 1;
        rocketObj[spaceAmidaPath]->work[2] = 2;
        spaceAmidaPath++;
        rocketObj[spaceAmidaPath]->work[2] = 1;
    }
    BoardModelPosGet(rocketMdlId[spaceAmidaPath], &rocketPos);
    BoardPlayerPosGet(spaceAmidaPlayerNo, &playerPos);
    SpaceAmidaPlayerRotAdd(&rocketPos, 0.0f);
    work->rocketPos = rocketPos;
    if (timerSec < 0 || (btn & PAD_BUTTON_A)) {
        MGSeqParamSet(timerSeqId, 2, -1);
        rocketObj[spaceAmidaPath]->work[1] = 1;
        BoardPlayerPosGet(spaceAmidaPlayerNo, &playerPos);
        jumpDist = VECDistanceXZ(&work->rocketPos, &playerPos);
        SpaceAmidaDirGet(&playerPos, &work->rocketPos, &work->jumpDir);
        work->jumpDir.y = 0.0f;
        work->jumpDir.x *= jumpDist / 30.0f;
        work->jumpDir.z *= jumpDist / 30.0f;
        work->unk00 = 0;
        work->jumpTime = 0.0f;
        obj->func = SpaceAmidaRocketJump;
    }
}

static void SpaceAmidaRocketJump(omObjData *obj)
{
    SpaceAmidaGameWork *work;
    Vec playerPos;
    Vec rocketPos;

    work = obj->data;
    if (rocketObj[spaceAmidaPath]->work[2] != 0) {
        return;
    }
    BoardPlayerMotionStart(spaceAmidaPlayerNo, 4, 0);
    BoardPlayerPosGet(spaceAmidaPlayerNo, &playerPos);
    playerPos.x += work->jumpDir.x;
    playerPos.z += work->jumpDir.z;
    playerPos.y = spaceAmidaPos.y + 80.0 * sind(6.0f * work->jumpTime);
    BoardModelPosGet(rocketObj[spaceAmidaPath]->work[0], &rocketPos);
    if ((++work->jumpTime) == 30.0f) {
        playerPos.y = rocketPos.y + 5.0f;
        BoardPlayerPosSetV(spaceAmidaPlayerNo, &playerPos);
        BoardPlayerMotionShiftSet(spaceAmidaPlayerNo, 2, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        obj->func = SpaceAmidaRocketKemuriExec;
    }
    BoardPlayerPosSetV(spaceAmidaPlayerNo, &playerPos);
}

static void SpaceAmidaRocketKemuriExec(omObjData *obj)
{
    SpaceAmidaGameWork *work;
    RocketWork *rocketWork;
    Vec playerPos;
    Vec kemuriPos;

    work = obj->data;
    BoardPlayerPosGet(spaceAmidaPlayerNo, &playerPos);
    kemuriPos = playerPos;
    kemuriPos.z += 100.0f;
    if (SpaceAmidaPlayerRotAdd(&kemuriPos, 10.0f) == 1) {
        BoardPlayerMotionShiftSet(spaceAmidaPlayerNo, 1, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        work->waitTime = 90;
        spaceAmidaEffObj->work[0] = 1;
        rocketObj[spaceAmidaPath]->work[2] = 3;
        rocketWork = rocketObj[spaceAmidaPath]->data;
        Hu3DModelAttrReset(kemuriMdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(kemuriMdlId, playerPos.x, playerPos.y, playerPos.z);
        rocketWork->kemuriScale.x = 1.4f;
        rocketWork->kemuriScale.y = 1.4f;
        rocketWork->kemuriScale.z = 1.4f;
        rocketWork->kemuriScaleVel.x = 0.055999998f;
        rocketWork->kemuriScaleVel.y = 0.08088889f;
        rocketWork->kemuriScaleVel.z = 0.055999998f;
        rocketWork->kemuriTPLvl = 1.0f;
        rocketWork->unk3C = 0.0f;
        Hu3DModelScaleSet(kemuriMdlId, 1.4f, 1.4f, 1.4f);
        obj->func = SpaceAmidaRocketWait;
    }
}

static void SpaceAmidaRocketWait(omObjData *obj)
{
    SpaceAmidaGameWork *work;

    work = obj->data;
    if (work->waitTime == 0) {
        rocketObj[spaceAmidaPath]->work[2] = 4;
        obj->func = SpaceAmidaRocketUp;
    }
    else {
        work->waitTime--;
    }
}

static void SpaceAmidaRocketUp(omObjData *obj)
{
    SpaceAmidaGameWork *work;

    work = obj->data;
    if (rocketObj[spaceAmidaPath]->work[2] == 6) {
        coinWinProc = HuPrcCreate(SpaceAmidaCoinWin, 0x2004, 0x1000, 0);
        coinWinProc->user_data = obj;
        obj->func = NULL;
    }
}

static void SpaceAmidaCoinWin(void)
{
    char mess[16]; // array size may range between 1 and 16 (inclusive)
    omObjData *obj;
    SpaceAmidaGameWork *work;

    BoardAudSeqFadeOut(1, 100);
    sprintf(mess, "%d", spaceAmidaCoinNum);
    BoardWinCreate(2, MAKE_MESSID(11, 6), 0);
    BOARD_WIN_MES_SET_PTR(MAKE_MESSID_PTR(mess), 0);
    BoardWinWait();
    BoardWinKill();
    obj = HuPrcCurrentGet()->user_data;
    work = obj->data;
    work->jumpDir.x = 0.0f;
    work->jumpDir.y = 10.0f;
    work->jumpDir.z = 3.0f;
    work->jumpTime = 0.0f;
    BoardPlayerMotionShiftSet(spaceAmidaPlayerNo, 4, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    obj->func = SpaceAmidaJumpDown;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void SpaceAmidaJumpDown(omObjData *obj)
{
    SpaceAmidaGameWork *work;
    Vec pos;

    work = obj->data;
    BoardPlayerPosGet(spaceAmidaPlayerNo, &pos);
    pos.x += work->jumpDir.x;
    pos.y += work->jumpDir.y - 0.029166667f * work->jumpTime * work->jumpTime;
    pos.z += work->jumpDir.z;
    work->jumpTime += 1.0f;
    if (pos.y <= spaceAmidaPos.y) {
        BoardPlayerMotionShiftSet(spaceAmidaPlayerNo, 1, 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
        pos.y = spaceAmidaPos.y;
        coinWinProc = HuPrcCreate(SpaceAmidaCoinRainMain, 0x2004, 0x1000, 0);
        coinWinProc->user_data = obj;
        obj->func = NULL;
    }
    BoardPlayerPosSetV(spaceAmidaPlayerNo, &pos);
}

static void SpaceAmidaCoinRainMain(void)
{
    Vec coinPos[20];
    Vec coinRot[20];
    Vec playerPos;
    Vec scale;
    Vec coinEffPos;
    float velY;
    s16 coinNum;
    s16 i;

    coinNum = 0;
    BoardPlayerPosGet(spaceAmidaPlayerNo, &playerPos);
    scale.x = scale.y = scale.z = 1.0f;
    for (i = 0; i < spaceAmidaCoinNum; i++) {
        BoardModelVisibilitySet(coinMdlId[i], 1);
        coinPos[i] = playerPos;
        coinPos[i].y += 600.0f + i * 120;
        coinPos[i].x += -25.0f + 50.0f * frand8() * 0.003921569f;
        coinPos[i].z += -25.0f + 50.0f * frand8() * 0.003921569f;
        coinRot[i].x = coinRot[i].z = 0.0f;
        coinRot[i].y = 360.0f * frand8() * 0.003921569f;
        BoardModelPosSetV(coinMdlId[i], &coinPos[i]);
        BoardModelScaleSetV(coinMdlId[i], &scale);
        BoardModelRotSetV(coinMdlId[i], &coinRot[i]);
    }
    velY = -1.0f;
    while (TRUE) {
        for (i = 0; i < spaceAmidaCoinNum; i++) {
            if (i >= coinNum) {
                coinPos[i].y += velY;
                BoardModelPosSetV(coinMdlId[i], &coinPos[i]);
                coinRot[i].y += 45.0f;
                if (coinRot[i].y >= 360.0f) {
                    coinRot[i].y -= 360.0f;
                }
                BoardModelRotSetV(coinMdlId[i], &coinRot[i]);
                if (coinPos[i].y <= playerPos.y + 80.0f) {
                    Vec pos = coinPos[i];
                    CharModelCoinEffectCreate(1, &pos);
                    BoardModelVisibilitySet(coinMdlId[i], 0);
                    coinNum++;
                    BoardPlayerCoinsAdd(spaceAmidaPlayerNo, 1);
                    HuAudFXPlay(7);
                    omVibrate(spaceAmidaPlayerNo, 0xC, 6, 6);
                }
            }
        }
        velY *= 1.05f;
        if (velY < -20.0f) {
            velY = -20.0f;
        }
        if (coinNum == spaceAmidaCoinNum) {
            BoardPlayerMotionShiftSet(spaceAmidaPlayerNo, 7, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            break;
        }
        HuPrcVSleep();
    }
    while (!BoardPlayerMotionEndCheck(spaceAmidaPlayerNo)) {
        HuPrcVSleep();
    }
    coinWinProc = HuPrcCreate(SpaceAmidaReturnWinMain, 0x2004, 0x1000, 0);
    coinWinProc->user_data = HuPrcCurrentGet()->user_data;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void SpaceAmidaReturnWinMain(void)
{
    omObjData *obj;

    BoardWinCreate(2, MAKE_MESSID(11, 7), 0);
    BoardWinWait();
    BoardWinKill();
    obj = HuPrcCurrentGet()->user_data;
    obj->func = SpaceAmidaGameStop;
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void SpaceAmidaGameStop(omObjData *obj)
{
    SpaceAmidaStop();
    omDelObjEx(HuPrcCurrentGet(), obj);
}

static void SpaceAmidaDirGet(Vec *b, Vec *a, Vec *result)
{
    VECSubtract(a, b, result);
    VECNormalize(result, result);
}

static float SpaceAmidaAngleGet(Vec *dir)
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

static u32 SpaceAmidaPlayerRotAdd(Vec *rocketPos, float delta)
{
    Vec dir;
    Vec playerPos;
    Vec playerRot;
    float rocketAngle;
    float angleDelta;
    float rotY;

    BoardPlayerPosGet(spaceAmidaPlayerNo, &playerPos);
    SpaceAmidaDirGet(&playerPos, rocketPos, &dir);
    rocketAngle = SpaceAmidaAngleGet(&dir);
    BoardPlayerRotGet(spaceAmidaPlayerNo, &playerRot);
    rotY = playerRot.y;
    angleDelta = rocketAngle - rotY;
    if (delta == 0.0f) {
        rotY = rocketAngle;
    }
    else if (fabs(angleDelta) > delta) {
        if (angleDelta < 0.0f) {
            angleDelta += 360.0f;
        }
        if (angleDelta < 180.0f) {
            if (angleDelta > delta) {
                rotY += delta;
            }
            else {
                rotY += angleDelta;
            }
        }
        else if (360.0f - angleDelta > delta) {
            rotY -= delta;
        }
        else {
            rotY -= 360.0f - angleDelta;
        }
    }
    else {
        rotY = rocketAngle;
    }
    if (rotY >= 360.0f) {
        rotY -= 360.0f;
    }
    if (rotY < 0.0f) {
        rotY += 360.0f;
    }
    BoardPlayerRotYSet(spaceAmidaPlayerNo, rotY);
    if (rotY == rocketAngle) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

static void SpaceAmidaEffCreate(void)
{
    spaceAmidaEffAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_W01, 20));
    spaceAmidaEffObj = omAddObjEx(boardObjMan, 0x101, 1, 0, -1, SpaceAmidaEffUpdate);
    spaceAmidaEffObj->data = HuMemDirectMallocNum(HEAP_SYSTEM, 12, MEMORY_DEFAULT_NUM);
    spaceAmidaEffObj->model[0] = Hu3DParticleCreate(spaceAmidaEffAnim, 0x320);
    Hu3DParticleColSet(spaceAmidaEffObj->model[0], 255, 0, 0);
    Hu3DParticleScaleSet(spaceAmidaEffObj->model[0], 5.0f);
    Hu3DParticleHookSet(spaceAmidaEffObj->model[0], SpaceAmidaEffParticleHook);
    Hu3DParticleBlendModeSet(spaceAmidaEffObj->model[0], 1);
    Hu3DModelAttrSet(spaceAmidaEffObj->model[0], HU3D_ATTR_DISPOFF);
    spaceAmidaEffObj->work[0] = 0;
}

static void SpaceAmidaEffKill(void)
{
    Hu3DModelKill(spaceAmidaEffObj->model[0]);
    omDelObjEx(HuPrcCurrentGet(), spaceAmidaEffObj);
}

static void SpaceAmidaEffUpdate(omObjData *obj)
{
    void *work;

    work = obj->data;
    switch (obj->work[0]) {
        case 0:
            break;
        case 1:
            obj->work[0] = 2;
            Hu3DModelAttrReset(obj->model[0], HU3D_ATTR_DISPOFF);
            Hu3DModelScaleSet(obj->model[0], 10.0f, 10.0f, 10.0f);
            break;
        case 2:
            break;
    }
}

static void SpaceAmidaEffParticleHook(ModelData *model, ParticleData *particle, Mtx matrix)
{
    RocketWork *work;
    HsfanimStruct01 *particleDataP;
    Vec pos;
    float size;
    s32 i;
    s32 j;
    s32 relSize;

    BoardModelPosGet(rocketObj[spaceAmidaPath]->work[0], &pos);
    work = rocketObj[spaceAmidaPath]->data;
    if (particle->unk_34 == 0) {
        particleDataP = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, particleDataP++) {
            particleDataP->unk2C = 0.0f;
        }
        particle->unk_1C = (void *)1;
    }
    if (work->kemuriSize > 0.0f) {
        for (i = 0; i < 80.0f * work->kemuriSize; i++) {
            particleDataP = particle->unk_48;
            for (j = 0; j < particle->unk_30; j++, particleDataP++) {
                if (particleDataP->unk2C == 0.0f) {
                    break;
                }
            }
            if (j != particle->unk_30) {
                relSize = frand16();
                size = (-15.0f + 30.0f * (relSize / 65536.0f)) * work->kemuriSize;
                particleDataP->unk08.x = pos.x + size;
                particleDataP->unk08.y = pos.y;
                particleDataP->unk08.z = pos.z;
                particleDataP->unk14.x = 255.0f;
                particleDataP->unk14.y = 155.0f;
                particleDataP->unk14.z = 55.0f;
                particleDataP->unk40.a = 0xFF;
                particleDataP->unk20 = 0.0f;
                particleDataP->unk24 = work->kemuriSize * (-3.0 + (2.0 * (fabs(size) / 15.0)));
                particleDataP->unk28 = 0.0f;
                particleDataP->unk2C = 7.3f;
            }
        }
    }
    particleDataP = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, particleDataP++) {
        if (particleDataP->unk2C == 0.0f) {
            continue;
        }
        particleDataP->unk34.x = particleDataP->unk08.x;
        particleDataP->unk34.y = particleDataP->unk08.y;
        particleDataP->unk34.z = particleDataP->unk08.z;
        particleDataP->unk08.x += particleDataP->unk20;
        particleDataP->unk08.y += particleDataP->unk24;
        particleDataP->unk08.z += particleDataP->unk28;
        if (particleDataP->unk08.y <= spaceAmidaPos.y) {
            particleDataP->unk08.y = spaceAmidaPos.y;
            particleDataP->unk24 = -particleDataP->unk24 - 0.3f;
            if (particleDataP->unk24 < 0.0f) {
                particleDataP->unk24 = 0.0f;
            }
            relSize = 80.0f * (2.0f * ((pos.x - particleDataP->unk08.x) / 15.0f) - rand8() / 255.0f);
            particleDataP->unk20 = 8.0 * sind(relSize);
            particleDataP->unk28 = 8.0 * cosd(relSize);
        }
        particleDataP->unk24 -= 0.35f;
        if ((particleDataP->unk14.x -= 25.5f) < 0.0f) {
            particleDataP->unk14.x = 0.0f;
        }
        if ((particleDataP->unk14.y -= 36.42857f) < 0.0f) {
            particleDataP->unk14.y = 0.0f;
        }
        if ((particleDataP->unk14.z -= 63.75f) < 0.0f) {
            particleDataP->unk14.z = 0.0f;
        }
        particleDataP->unk40.r = particleDataP->unk14.x;
        particleDataP->unk40.g = particleDataP->unk14.y;
        particleDataP->unk40.b = particleDataP->unk14.z;
        if (particleDataP->unk40.r == 0 && particleDataP->unk40.g == 0 && particleDataP->unk40.b == 0) {
            particleDataP->unk2C = 0.0f;
        }
    }
}
