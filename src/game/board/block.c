#include "game/flag.h"
#include "game/objsub.h"
#include "game/process.h"
#include "game/board/main.h"
#include "game/board/player.h"
#include "game/board/model.h"
#include "game/board/star.h"
#include "game/board/window.h"
#include "math.h"

#define BLOCK_SPAWN 0
#define BLOCK_HIT 2
#define BLOCK_OPEN 3

typedef struct {
    struct {
        u8 kill : 1;
        u8 state : 3;
        u8 unk00_field2 : 1;
        u8 contains_star : 1;
        u8 opened : 1;
        u8 unk00_field5 : 1;
    };
    
    s16 hit_y_velocity;
    s16 target_y_pos;
} BlockWork;

typedef struct {
    struct {
        u8 kill : 1;
    };
    
    u8 lifetime;
    s8 model_index;
    s16 model;
} CoinWork;

static void BlockProc(void);
static void DestroyBlock(void);
static void ExecBlockObj(omObjData* arg0);
static void CreateBlockObj(s32 arg0);
static void DestroyBlockObj(BlockWork* unused0, omObjData* unused1);
static void SpawnBlock(BlockWork* arg0, omObjData* arg1);
static void HitBlock(BlockWork* arg0, omObjData* arg1);
static void OpenBlock(BlockWork* arg0, omObjData* arg1);
static void SetBlockOpen(void);
static void SetBlockStop(void);
static void WaitBlockHit(void);
static void CreateCoinMdl(void);
static void KillCoinMdl(void);
static void PopupCoin(void);
static void PopupCoinExec(omObjData* arg0);

extern s8 boardTutorialBlockF;
extern s8 boardTutorialBlockItem;

static s16 jumpMot = -1;
static s16 starMdl = -1;

static f32 rotMax;
static f32 scaleAngle;
static f32 rotY;

static omObjData* blockObj;
static Process* blockProc;

static s16 coinMdl[10] = { -1, -1, -1, -1 };
static s32 coinF[10];

s32 BoardBlockExec(s32 arg0) {
    if (BoardPlayerSizeGet(arg0) == 2) {
        return 0;
    }
    
    blockProc = HuPrcChildCreate(BlockProc, 0x2003, 0x3800U, 0, boardMainProc);
    HuPrcDestructorSet2(blockProc, DestroyBlock);
    
    while (blockProc != NULL) {
        HuPrcVSleep();
    }
    
    return 0;
}

static void BlockProc(void) {
    s32 sp14[8] = {0x005F0060, 0x001A0060, 0x006D0060, 0x008A0060, 0x00850060, 0x00110060, 0x000D0060, 0x00810060};
    Point3d sp8;
    s32 var_r28;
    s32 i;
    s32 player;
    BlockWork* work;
    s32* temp_r4;
    s32 player_character;
    
    player = GWSystem.player_curr;

    player_character = GWPlayer[player].character;
    jumpMot = BoardPlayerMotionCreate(player, sp14[player_character]);
    BoardPlayerIdleSet(player);
    BoardPlayerMotBlendSet(player, 0, 0xF);
    omVibrate(player, 12, 12, 0);
    CreateBlockObj(player);
    
    work = OM_GET_WORK_PTR(blockObj, BlockWork);
    while (work->state != BLOCK_HIT) {
        HuPrcVSleep();
    }
    
    BoardCameraViewSet(3);
    BoardCameraMotionWait();
    BoardWinCreate(0, 0x10000, -1);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerMotionShiftSet(player, 0xB, 0, 8.0, 0.0);
    HuPrcSleep(9);
    while (BoardPlayerMotionTimeGet(player) < 30.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x30C);
    SetBlockOpen();
    while (BoardPlayerMotionEndCheck(player) == 0) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(player);
    
    if (work->contains_star != 0) {
        SetBlockStop();
        BoardModelPosGet(starMdl, &sp8);
        if (_CheckFlag(FLAG_ID_MAKE(1, 11)) == 0) {
            BoardAudSeqPause(0, 1, 1000);
        }
        BoardStarGive(player, &sp8);
        if (_CheckFlag(FLAG_ID_MAKE(1, 11)) == 0) {
            BoardAudSeqPause(0, 0, 1000);
        }
    } else {
        for (i = 0; i < 0x14; i++) {
            WaitBlockHit();
            BoardPlayerMotionStart(player, (s32) jumpMot, 0);
            BoardPlayerMotionSpeedSet(player, 2);
            while (BoardPlayerMotionTimeGet(player) < 4) {
                HuPrcVSleep();
            }
            SetBlockOpen();
            PopupCoin();
            while (BoardPlayerMotionEndCheck(player) == 0) {
                HuPrcVSleep();
            }
            BoardPlayerMotionStart(player, 1, 0);
            BoardPlayerCoinsAdd(player, 1);
            HuAudFXPlay(7);
            HuPrcVSleep();
        }
        
        SetBlockStop();
    }
    
    BoardWinCreate(0, work->contains_star != 0 ? MAKE_MESSID(1, 1) : MAKE_MESSID(1, 2), -1);
    BoardWinWait();
    BoardWinKill();
    KillCoinMdl();
    work->kill = 1;
    
    BoardPlayerIdleSet((s32) player);
    HuPrcVSleep();
    
    if ((_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) && work->contains_star == 0) {
        BoardTutorialHookExec(0x16, 0);
    }
    
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    HuPrcEnd();
}

static void DestroyBlock(void) {
    if (jumpMot != -1) {
        BoardPlayerMotionKill(GWSystem.player_curr, jumpMot);
        jumpMot = -1;
    }
    KillCoinMdl();
    blockProc = 0;
}

static void CreateBlockObj(s32 arg0) {
    Point3d player_pos;
    BlockWork* work;
    s8 contains_star;
    
    BoardPlayerPosGet(arg0, &player_pos);
    starMdl = BoardModelCreate(0x70004, NULL, 0);
    BoardModelVisibilitySet(starMdl, 0);
    BoardModelMotionSpeedSet(starMdl, 0);
    BoardModelLayerSet(starMdl, 2U);
    
    blockObj = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, ExecBlockObj);
    
    work = OM_GET_WORK_PTR(blockObj, BlockWork);
    work->kill = 0;
    work->unk00_field2 = 0;
    work->opened = 0;
    work->unk00_field5 = 0;
    work->state = BLOCK_SPAWN;
    
    blockObj->trans.x = player_pos.x;
    blockObj->trans.y = 270 + player_pos.y;
    blockObj->trans.z = player_pos.z;
    
    blockObj->scale.x = blockObj->scale.y = blockObj->scale.z = 0.01;
    blockObj->rot.x = blockObj->rot.y = blockObj->rot.z = 0.0;
    
    scaleAngle = 0;
    rotY = 0;
    rotMax = 30;
    
    BoardModelVisibilitySet(starMdl, 1);
    
    if (BoardRandFloat() > 0.5f) {
        contains_star = 0;
    } else {
        contains_star = 1;
    }
    
    work->contains_star = contains_star;
    
    if (boardTutorialBlockF != 0) {
        work->contains_star = boardTutorialBlockItem;
        boardTutorialBlockF = 0;
    }
    
    HuAudFXPlay(0x302);
    
    if (work->contains_star == 0) {
        CreateCoinMdl();
    }
}

static void ExecBlockObj(omObjData* arg0) {
    BlockWork* work;

    work = OM_GET_WORK_PTR(arg0, BlockWork);
    
    if (work->kill != 0 || BoardIsKill() != 0) {
        DestroyBlockObj(work, arg0);
        blockObj = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    
    switch (work->state) {
        case BLOCK_SPAWN:
            SpawnBlock(work, arg0);
            break;
        case BLOCK_HIT:
            HitBlock(work, arg0);
            break;
        case BLOCK_OPEN:
            OpenBlock(work, arg0);
            break;
    }
    
    if (work->unk00_field5 != 0) {
        BoardModelVisibilitySet(starMdl, 0);
    }
    
    BoardModelPosSet(starMdl, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotSet(starMdl, arg0->rot.x, arg0->rot.y, arg0->rot.z);
    BoardModelScaleSet(starMdl, arg0->scale.x, arg0->scale.y, arg0->scale.z);
}

static void DestroyBlockObj(BlockWork* unused0, omObjData* unused1) {
    if (starMdl != -1) {
        BoardModelKill(starMdl);
        starMdl = -1;
    }
}

static void SpawnBlock(BlockWork* arg0, omObjData* arg1) {
    if (scaleAngle < 90.0f) {
        scaleAngle += 3.75f;
        if (scaleAngle > 90.0f) {
            scaleAngle = 90.0f;
        }
    } else {
        rotMax *= 0.5f;
        if (rotMax < 0.8f) {
            rotY = 0.0f;
            rotMax = 0.0f;
            arg0->hit_y_velocity = 0;
            arg0->state = BLOCK_HIT;
        }
    }
    
    if (rotY < 360.0f) {
        rotY += rotMax;
        if (rotY > 360.0f) {
            rotY = 360.0f;
        }
    }
    
    arg1->rot.y = rotY;
    arg1->scale.x = arg1->scale.y = arg1->scale.z = sin(M_PI * scaleAngle / 180.0);
}

static void HitBlock(BlockWork* arg0, omObjData* arg1) {
    float var_f30;

    arg0->hit_y_velocity += 3;
    if (arg0->hit_y_velocity > 0x168) {
        arg0->hit_y_velocity -= 0x168;
    }
    
    OSs16tof32(&arg0->hit_y_velocity, &var_f30);
    arg1->trans.y += 0.2f * sin((M_PI * var_f30) / 180.0);
}

static void OpenBlock(BlockWork* arg0, omObjData* arg1) {
    f32 target_y_pos;

    if (arg0->opened == 0) {
        arg0->opened = 1;
        HuAudFXPlay(0x33B);
        BoardModelMotionStart(starMdl, 0, 0);
    }
    
    if (arg0->unk00_field2 == 0) {
        OSf32tos16(&arg1->trans.y, &arg0->target_y_pos);
        
        arg1->trans.y += 80.0f;
        arg0->unk00_field2 = 1;
    } else {
        OSs16tof32(&arg0->target_y_pos, &target_y_pos);
        arg1->trans.y += -8.0f;
        
        if (arg1->trans.y < target_y_pos) {
            arg1->trans.y = target_y_pos;
            arg0->state = BLOCK_HIT;
        }
    }
}

static void SetBlockOpen(void) {
    BlockWork* work;

    work = OM_GET_WORK_PTR(blockObj, BlockWork);
    work->state = BLOCK_OPEN;
}

static void SetBlockStop(void) {
    BlockWork* work;

    work = OM_GET_WORK_PTR(blockObj, BlockWork);
    work->unk00_field5 = 1;
}

static void WaitBlockHit(void) {
    BlockWork* work;

    work = OM_GET_WORK_PTR(blockObj, BlockWork);
    
    while (work->state != BLOCK_HIT) {
        HuPrcVSleep();
    }
}

static void CreateCoinMdl(void) {
    s32 i;
    
    for (i = 0; i < 10; i += 1) {
        coinMdl[i] = BoardModelCreate(0x7000A, NULL, 1);
        BoardModelVisibilitySet(coinMdl[i], 0);
        coinF[i] = 0;
    }
}

static void KillCoinMdl(void) {
    s32 i;
    
    for (i = 0; i < 0xA; i += 1) {
        if (coinMdl[i] != -1) {
            BoardModelKill(coinMdl[i]);
            coinMdl[i] = -1;
        }
        coinF[i] = 0;
    }
}

static inline s32 FindCoinModel(s16 *out_model) {
    s32 i;
    
    for (i = 0; i < 10; i++) {
        if (coinF[i] == 0) {
            *out_model = coinMdl[i];
            return i;
        }
    }
    
    return -1;
}

static void PopupCoin(void) {
    Point3d star_pos;
    omObjData* coinObj;
    s32 model_index;
    s16 model;
    CoinWork* work;
    
    do {
        HuPrcVSleep();
        model_index = FindCoinModel(&model);
    } while (model_index == -1);
    
    coinObj = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, PopupCoinExec);
    work = OM_GET_WORK_PTR(coinObj, CoinWork);
    
    work->kill = 0;
    work->lifetime = 10;
    work->model = model;
    work->model_index = model_index;
    
    coinObj->trans.x = 15.0f;
    coinObj->trans.y = 40.0f;
    
    BoardModelPosGet(starMdl, &star_pos);
    BoardModelPosSetV(work->model, &star_pos);
    BoardModelVisibilitySet(work->model, 1);
}

static void PopupCoinExec(omObjData* obj) {
    Point3d coin_pos;
    Point3d coin_rot;
    CoinWork* work;

    work = OM_GET_WORK_PTR(obj, CoinWork);
    
    if (work->kill != 0 || BoardIsKill() != 0) {
        BoardModelVisibilitySet(work->model, 0);
        coinF[work->model_index] = 0;
        omDelObjEx(HuPrcCurrentGet(), obj);
        return;
    }
    
    if (work->lifetime != 0) {
        work->lifetime -= 1;
    } else {
        work->kill = 1;
        return;
    }
    
    BoardModelPosGet(work->model, &coin_pos);
    coin_pos.y += obj->trans.y;
    BoardModelPosSetV(work->model, &coin_pos);
    BoardModelRotGet(work->model, &coin_rot);
    coin_rot.y += obj->trans.x;
    
    if (coin_rot.y > 360.0f) {
        coin_rot.y -= 360.0f;
    }
    
    BoardModelRotSetV(work->model, &coin_rot);
}
