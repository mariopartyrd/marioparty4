#include "game/board/star.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/msm.h"
#include "game/objsub.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/tutorial.h"
#include "game/board/ui.h"
#include "game/board/window.h"

#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        u8 unk00_field2 : 1;
        u8 unk00_field3 : 2;
        u8 unk00_field4 : 1;
    };
    s8 unk01;
    s8 unk02;
    char unk03[1];
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s16 unk0C;
} GiveStarWork;

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    s8 unk01;
} ShowNextWork;

static void ExecStar(void);
static void DestroyStar(void);
static void GiveStarMain(omObjData *arg0);
static void UpdateStarAngle(GiveStarWork *arg0, omObjData *arg1);
static void InitGiveStar(GiveStarWork *arg0, omObjData *arg1);
static void MoveGiveStar(GiveStarWork *arg0, omObjData *arg1);
static void ShrinkGiveStar(GiveStarWork *arg0, omObjData *arg1);
static void StopGiveStar(void);
static void InitGiveStarEffect(void);
static void KillGiveStarEffect(void);
static void ShowNextUpdate(omObjData *arg0);
static void HideNextHost(s32 arg0);

static Vec starCharPos;

static s16 hostMot[2];
static omObjData *showNextObj;
static s16 starDoneF;
static AnimData *starEffAnim;
static omObjData *giveStarObj;
static Process *starProc;

static s16 starParman = -1;
static s16 hostMdl = -1;

//mod: extend for custom board
const s32 lbl_8011E040[10] = {
    MAKE_MESSID(12, 0),
    MAKE_MESSID(12, 9),
    MAKE_MESSID(12, 18),
    MAKE_MESSID(12, 27),
    MAKE_MESSID(12, 36),
    MAKE_MESSID(12, 45),
    MAKE_MESSID(12, 0),
    MAKE_MESSID(12, 0),
    MAKE_MESSID(12, 0),
    //Mod TODO: fix for custom board data
    MAKE_MESSID(12, 0)
};

//mod: extend for custom board
const s32 lbl_8011E064[10][2] = {
    { MAKE_MESSID(21, 34), MAKE_MESSID(21, 40) },
    { MAKE_MESSID(21, 35), MAKE_MESSID(21, 41) },
    { MAKE_MESSID(21, 36), MAKE_MESSID(21, 42) },
    { MAKE_MESSID(21, 37), MAKE_MESSID(21, 43) },
    { MAKE_MESSID(21, 38), MAKE_MESSID(21, 44) },
    { MAKE_MESSID(21, 39), MAKE_MESSID(21, 45) },
    { MAKE_MESSID(21, 34), MAKE_MESSID(21, 40) },
    { MAKE_MESSID(21, 34), MAKE_MESSID(21, 40) },
    { MAKE_MESSID(21, 34), MAKE_MESSID(21, 40) },

    //Mod TODO: fix for custom board data
    { MAKE_MESSID(21, 34), MAKE_MESSID(21, 40) }
};

s32 boardStarSndTbl[] = {
    0x00000120,
    0x00000160,
    0x000001A0,
    0x000001E0,
    0x00000220,
    0x00000260,
    0x000002A0,
    0x000002E0
};

//mod: extend for custom board
static s32 hostMotTbl[10][2] = {
    { DATA_MAKE_NUM(DATADIR_W01, 33), DATA_MAKE_NUM(DATADIR_BOARD, 157) },
    { DATA_MAKE_NUM(DATADIR_W02, 7), DATA_MAKE_NUM(DATADIR_BOARD, 158) },
    { DATA_MAKE_NUM(DATADIR_W03, 31), DATA_MAKE_NUM(DATADIR_BOARD, 159) },
    { DATA_MAKE_NUM(DATADIR_W04, 11), DATA_MAKE_NUM(DATADIR_BOARD, 160) },
    { DATA_MAKE_NUM(DATADIR_W05, 9), DATA_MAKE_NUM(DATADIR_BOARD, 161) },
    { DATA_MAKE_NUM(DATADIR_W06, 21), DATA_MAKE_NUM(DATADIR_BOARD, 162) },

    //dummy data for tutorial and extra board
    { DATA_MAKE_NUM(DATADIR_W06, 21), DATA_MAKE_NUM(DATADIR_BOARD, 162) },
    { DATA_MAKE_NUM(DATADIR_W06, 21), DATA_MAKE_NUM(DATADIR_BOARD, 162) },
    { DATA_MAKE_NUM(DATADIR_W06, 21), DATA_MAKE_NUM(DATADIR_BOARD, 162) },

    //Mod TODO: fix for custom board data
    { DATA_MAKE_NUM(DATADIR_W06, 21), DATA_MAKE_NUM(DATADIR_BOARD, 162) }
};

static HsfanimStruct00 starEffParam = {
    0x001E,
    { 0x00, 0x00 }, // padding?
    3.3f,
    70.0f,
    7.0f,
    { 0.0f, -0.05f, 0.0f },
    2.0f,
    1.0f,
    20.0f,
    0.98f,
    0x0002,
    {
        0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0x40, 0xFF,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    },
    {
        0xFF, 0x80, 0x80, 0x00,
        0xFF, 0x40, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    }
};

void BoardStarHostSet(s16 arg0) {
    hostMdl = arg0;
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        return;
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 1))) {
        BoardSpaceHostSet(boardSpaceStarTbl[GWSystem.star_pos]);
    }
}

s16 BoardStarHostMdlGet(void) {
    return hostMdl;
}

void BoardStarExec(s32 arg0, s32 arg1) {
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        return;
    }
    if (BoardPlayerSizeGet(arg0) != 2) {
        BoardRollDispSet(0);
        starProc = HuPrcChildCreate(ExecStar, 0x2003, 0x3800, 0, boardMainProc);
        HuPrcDestructorSet2(starProc, DestroyStar);
        while (starProc != NULL) {
            HuPrcVSleep();
        }
        BoardRollDispSet(1);
    }
}

static void ExecStar(void) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f27;
    float temp_f29;
    float temp_f30;
    float var_f28;
    float var_f31;
    s16 temp_r30;
    u32 sp8;
    s32 temp_r24;
    s32 temp_r29;
    s32 var_r26;
    s32 var_r25;
    s32 i;
    s32 temp_r27;
    s32 temp_r31;
    s32 var_r22;
    BoardSpace *var_r23;

    temp_r31 = GWSystem.player_curr;
    temp_r27 = GWBoardGet();
    temp_r30 = BoardStarHostMdlGet();
    HuAudFXPlay(0x33A);
    for (i = 0; i < 2; i++) {
        hostMot[i] = BoardModelMotionCreate(temp_r30, hostMotTbl[temp_r27][i]);
    }
    BoardPlayerPosGet(temp_r31, &sp24);
    temp_r24 = GWPlayer[temp_r31].space_curr;
    var_r23 = BoardSpaceGet(0, temp_r24);
    sp8 = (var_r23->flag & 0x70000) >> 16;
    starDoneF = 0;
    var_r22 = BoardSpaceLinkFlagSearch(0, temp_r24, 0x04000000);
    BoardSpacePosGet(0, var_r22, &sp18);
    PSVECSubtract(&sp18, &sp24, &spC);
    temp_f30 = 90.0 - atan2d(spC.z, spC.x);
    temp_f30 = 90.0f * ((temp_f30 + 3.0f) / 90.0f);
    temp_f29 = BoardPlayerRotYGet(temp_r31);
    BoardPlayerIdleSet(temp_r31);
    if (BoardDAngleCalc(temp_f30 - temp_f29) < 0.0f) {
        var_f28 = -BoardDAngleCalc(temp_f30 - temp_f29);
    } else {
        var_f28 = BoardDAngleCalc(temp_f30 - temp_f29);
    }
    if (var_f28 > 90.0f) {
        var_r25 = 30;
    } else {
        var_r25 = 15;
    }
    BoardPlayerMotBlendSet(temp_r31, temp_f30, var_r25);
    temp_f27 = BoardModelRotYGet(temp_r30);
    var_f31 = BoardDAngleCalc(temp_f30 + 180.0f) - temp_f27;
    if ((var_f31 <= 4.0f && var_f31 >= 0.0f)
        || (var_f31 <= 360.0f && var_f31 >= 355.0f)
        || (var_f31 <= 0.0f && var_f31 >= -4.0f)) {
        var_r26 = 0;
    } else {
        var_r26 = 1;
    }
    if (var_r26 != 0) {
        var_f31 /= var_r25;
        BoardModelMotionShiftSet(temp_r30, hostMot[1], 0.0f, 10.0f, 0x40000001);
        BoardModelMotionSpeedSet(temp_r30, 2.0f);
    }
    while (!BoardPlayerMotBlendCheck(temp_r31)) {
        if (var_r26 != 0) {
            temp_f30 = var_f31 + BoardModelRotYGet(temp_r30);
            BoardModelRotYSet(temp_r30, temp_f30);
        }
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(temp_r30, 1, 0.0f, 10.0f, 0x40000001);
    BoardCameraViewSet(3);
    BoardCameraMotionWait();
    if (GWStarsGet(temp_r31) >= 999) {
        temp_r29 = lbl_8011E040[temp_r27] + 5;
        BoardWinCreate(0, temp_r29, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
    } else if (BoardPlayerCoinsGet(temp_r31) < 20 && GWSystem.last5_effect != 4) {
        temp_r29 = lbl_8011E040[temp_r27] + 2;
        BoardWinCreate(2, temp_r29, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
    } else {
        BoardStatusShowSetAll(0);
        while (!BoardStatusStopCheck(0) || !BoardStatusStopCheck(1) || !BoardStatusStopCheck(2) || !BoardStatusStopCheck(3)) {
            HuPrcVSleep();
        }
        temp_r29 = lbl_8011E040[temp_r27];
        BoardWinCreate(2, temp_r29, BoardWinPortraitGetStar());
        BoardWinInsertMesSet(BoardPlayerGetCharMess(temp_r31), 0);
        BoardWinWait();
        BoardWinKill();
        while (1) {
            BoardStatusShowSetForce(temp_r31);
            BoardStatusShowSet(temp_r31, 1);
            while (!BoardStatusStopCheck(temp_r31)) {
                HuPrcVSleep();
            }
            if (GWSystem.last5_effect == 4) {
                temp_r29 = lbl_8011E040[temp_r27] + 8;
                BoardWinCreate(2, temp_r29, BoardWinPortraitGetStar());
                BoardWinWait();
                break;
            }
            temp_r29 = lbl_8011E040[temp_r27] + 1;
            BoardWinCreateChoice(1, temp_r29, BoardWinPortraitGetStar(), 0);
            BoardWinAttrSet(0x10);
            if (GWPlayer[temp_r31].com) {
                if (BoardPlayerCoinsGet(temp_r31) >= 20) {
                    BoardComKeySetUp();
                } else {
                    BoardComKeySetDown();
                }
            }
            BoardWinWait();
            switch (BoardWinChoiceGet()) {
                case 0:
                    if (BoardPlayerCoinsGet(temp_r31) < 20) {
                        temp_r29 = lbl_8011E040[temp_r27] + 2;
                        BoardWinCreate(2, temp_r29, BoardWinPortraitGetStar());
                        BoardWinWait();
                        BoardStatusShowSet(temp_r31, 0);
                        while (!BoardStatusStopCheck(temp_r31)) {
                            HuPrcVSleep();
                        }
                        BoardStatusShowSetAll(1);
                        goto block_B;
                    }
                    goto block_A;
                case 1:
                    temp_r29 = lbl_8011E040[temp_r27] + 4;
                    BoardWinCreate(2, temp_r29, BoardWinPortraitGetStar());
                    BoardWinWait();
                    BoardStatusShowSet(temp_r31, 0);
                    while (!BoardStatusStopCheck(temp_r31)) {
                        HuPrcVSleep();
                    }
                    BoardStatusShowSetAll(1);
                    goto block_B;
                default:
                    BoardStatusShowSet(temp_r31, 0);
                    while (!BoardStatusStopCheck(temp_r31)) {
                        HuPrcVSleep();
                    }
                    BoardWinKill();
                    BoardViewMapExec(temp_r31);
                    break;
            }
        }
block_A:
        temp_r29 = lbl_8011E040[temp_r27] + 3;
        BoardWinCreate(2, temp_r29, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
        if (GWSystem.last5_effect != 4) {
            for (i = 0; i < 20; i++) {
                BoardPlayerCoinsAdd(temp_r31, -1);
                HuAudFXPlay(0xE);
                HuPrcSleep(3);
            }
            HuAudFXPlay(0xF);
        }
        _SetFlag(0x10017);
        BoardModelMotionShiftSet(temp_r30, hostMot[0], 0.0f, 10.0f, 0);
        HuPrcSleep(30);
        starDoneF = 1;
        BoardAudSeqFadeOut(0, 1000);
        BoardModelPosGet(temp_r30, &sp24);
        sp24.y += 130.0f;
        BoardStarGive(temp_r31, &sp24);
        BoardStatusShowSet(temp_r31, 0);
        while (!BoardStatusStopCheck(temp_r31)) {
            HuPrcVSleep();
        }
        BoardModelMotionShiftSet(temp_r30, 1, 0.0f, 10.0f, 0x40000001);
        BoardStarShowNext(temp_r31);
        BoardMusStartBoard();
        BoardModelRotYSet(temp_r30, 0.0f);
    }
block_B:
    BoardWinKill();
    var_f31 = -BoardModelRotYGet(temp_r30);
    if (var_r26 != 0) {
        var_f31 /= var_r25;
        BoardModelMotionShiftSet(temp_r30, hostMot[1], 0.0f, 10.0f, 0x40000001);
        BoardModelMotionSpeedSet(temp_r30, 3.0f);
    }
    BoardPlayerMotBlendSet(temp_r31, 0, var_r25);
    while (!BoardPlayerMotBlendCheck(temp_r31)) {
        if (var_r26 != 0) {
            temp_f30 = var_f31 + BoardModelRotYGet(temp_r30);
            BoardModelRotYSet(temp_r30, temp_f30);
        }
        HuPrcVSleep();
    }
    BoardModelRotYSet(temp_r30, 0.0f);
    BoardModelMotionShiftSet(temp_r30, 1, 0.0f, 10.0f, 0x40000001);
    if (!_CheckFlag(FLAG_ID_MAKE(1, 22))) {
        BoardCameraViewSet(1);
        BoardCameraTargetPlayerSet(temp_r31);
        BoardCameraMotionWait();
    }
    HuPrcEnd();
}

static void DestroyStar(void) {
    s32 i;

    _ClearFlag(0x10017);
    for (i = 0; i < 2; i++) {
        BoardModelMotionKill(BoardStarHostMdlGet(), hostMot[i]);
        hostMot[i] = -1;
    }
    StopGiveStar();
    KillGiveStarEffect();
    starProc = NULL;
}

static void GiveStarMain(omObjData *arg0) {
    GiveStarWork *temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0, GiveStarWork);
    if (temp_r30->unk00_field0 != 0 || BoardIsKill()) {
        KillGiveStarEffect();
        BoardModelKill(temp_r30->unk0C);
        giveStarObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r30->unk04 != 0) {
        temp_r30->unk04--;
    } else {
        switch (temp_r30->unk01) {
            case 4:
                break;
            case 0:
                InitGiveStar(temp_r30, arg0);
                break;
            case 1:
                MoveGiveStar(temp_r30, arg0);
                break;
            case 2:
                ShrinkGiveStar(temp_r30, arg0);
                break;
        }
        UpdateStarAngle(temp_r30, arg0);
    }
    BoardModelPosSet(temp_r30->unk0C, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotSet(temp_r30->unk0C, 0.0f, arg0->rot.y, 0.0f);
    BoardModelScaleSet(temp_r30->unk0C, arg0->scale.x, arg0->scale.y, arg0->scale.z);
    if (starParman != -1) {
        Hu3DParManPosSet(starParman, arg0->trans.x, -70.0f + arg0->trans.y, arg0->trans.z);
    }
}

static void UpdateStarAngle(GiveStarWork *arg0, omObjData *arg1) {
    float var_f31;

    if (arg0->unk00_field1 != 0) {
        if (arg0->unk02 < 16.0f) {
            arg0->unk02 += 2.0f;
            if (arg0->unk02 > 16.0f) {
                arg0->unk02 = 16;
            }
        }
        OSs8tof32(&arg0->unk02, &var_f31);
        arg1->rot.y = BoardDAngleCalc(arg1->rot.y + var_f31);
    }
}

static void InitGiveStar(GiveStarWork *arg0, omObjData *arg1) {
    Vec sp8;

    BoardPlayerPosGet(arg0->unk00_field3, &sp8);
    BoardModelVisibilitySet(arg0->unk0C, 1);
    BoardModelMotionStart(arg0->unk0C, 0, 0x40000001);
    BoardModelMotionTimeSet(arg0->unk0C, 2.0f);
    arg0->unk01 = 1;
    arg0->unk0A = 0;
    arg1->trans.x = starCharPos.x;
    arg1->trans.y = starCharPos.y;
    arg1->trans.z = starCharPos.z;
    arg1->rot.x = (sp8.x - starCharPos.x) / 10.0f;
    arg1->rot.z = (sp8.z - starCharPos.z) / 10.0f;
    arg1->rot.y = 0.0f;
    arg1->scale.x = arg1->scale.y = arg1->scale.z = 1.0f;
    InitGiveStarEffect();
}

static void MoveGiveStar(GiveStarWork *arg0, omObjData *arg1) {
    Vec sp8;
    float temp_f31;

    BoardPlayerPosGet(arg0->unk00_field3, &sp8);
    if (arg0->unk00_field2 == 0) {
        if (BoardModelMotionTimeGet(arg0->unk0C) >= 50.0f) {
            BoardModelMotionStartEndSet(arg0->unk0C, 50, 150);
            arg0->unk00_field2 = 1;
        }
    }
    if (arg0->unk0A < 10) {
        OSs16tof32(&arg0->unk0A, &temp_f31);
        arg1->trans.x += arg1->rot.x;
        arg1->trans.z += arg1->rot.z;
        arg1->trans.y += -0.08166667f * temp_f31 * temp_f31 * 0.97f + 50.0f;
        arg0->unk0A++;
    } else {
        arg1->trans.y += -4.0f;
        if (arg1->trans.y <= sp8.y + 300.0f) {
            arg1->trans.y = sp8.y + 300.0f;
            arg0->unk01 = 4;
        }
    }
}

static void ShrinkGiveStar(GiveStarWork *arg0, omObjData *arg1) {
    Vec sp8;
    float var_f30;

    if (arg0->unk00_field4 == 0) {
        HuAudFXPlay(0x339);
        arg0->unk00_field4 = 1;
    }
    BoardPlayerPosGet(arg0->unk00_field3, &sp8);
    arg1->trans.y += -4.0f;
    if (arg1->trans.y > sp8.y + 80.0f) {
        if (arg0->unk08 < 90) {
            if (BoardPlayerSizeGet(arg0->unk00_field3) != 1) {
                arg0->unk08 += 2;
            } else {
                arg0->unk08 += 1.4f;
            }
            if (arg0->unk08 > 90) {
                arg0->unk08 = 90;
            }
        }
        OSs16tof32(&arg0->unk08, &var_f30);
        arg1->scale.x = sind(var_f30 + 90.0f);
        if (arg1->scale.x <= 0.0f) {
            arg1->scale.x = 0.001f;
        }
        arg1->scale.y = arg1->scale.x;
        arg1->scale.z = arg1->scale.x;
    } else {
        omVibrate(arg0->unk00_field3, 12, 0xC, 0);
        arg0->unk00_field0 = 1;
        arg0->unk01 = 4;
        arg1->scale.x = arg1->scale.y = arg1->scale.z = 0.001f;
        KillGiveStarEffect();
        BoardModelVisibilitySet(arg0->unk0C, 0);
    }
}

static void StopGiveStar(void) {
    GiveStarWork *temp_r31;

    if (giveStarObj) {
        temp_r31 = OM_GET_WORK_PTR(giveStarObj, GiveStarWork);
        temp_r31->unk00_field0 = 1;
    }
}

static void InitGiveStarEffect(void) {
    s16 temp_r3;
    void *var_r30;

    var_r30 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 1), MEMORY_DEFAULT_NUM, HEAP_DATA);
    starEffAnim = HuSprAnimRead(var_r30);
    starParman = Hu3DParManCreate(starEffAnim, 0x64, &starEffParam);
    Hu3DParManAttrSet(starParman, 0x64);
    Hu3DParManRotSet(starParman, 90.0f, 0.0f, 0.0f);
    temp_r3 = Hu3DParManModelIDGet(starParman);
    Hu3DParticleBlendModeSet(temp_r3, 1);
    Hu3DModelLayerSet(temp_r3, 2);
    HuDataDirClose(DATADIR_EFFECT);
}

static void KillGiveStarEffect(void) {
    if (starParman != -1) {
        Hu3DParManKill(starParman);
        starParman = -1;
        starEffAnim = NULL;
    }
}

static inline void StarInlineFunc00(void) {
    GiveStarWork *temp_r28 = OM_GET_WORK_PTR(giveStarObj, GiveStarWork);

    temp_r28->unk01 = 0;
}

static inline void StarInlineFunc01(void) {
    GiveStarWork *temp_r27 = OM_GET_WORK_PTR(giveStarObj, GiveStarWork);

    while (temp_r27->unk01 != 4) {
        HuPrcVSleep();
    }
}

static inline void StarInlineFunc02(void) {
    GiveStarWork *temp_r29 = OM_GET_WORK_PTR(giveStarObj, GiveStarWork);

    temp_r29->unk00_field1 = 1;
    temp_r29->unk04 = 45;
    temp_r29->unk08 = 0;
    temp_r29->unk01 = 2;
}

void BoardStarGive(s32 arg0, Vec *arg1) {
    Vec sp8;
    s32 temp_r25;
    GiveStarWork *temp_r31;

    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        return;
    }
    starCharPos = *arg1;
    giveStarObj = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, GiveStarMain);
    BoardCameraRotGet(&sp8);
    temp_r31 = OM_GET_WORK_PTR(giveStarObj, GiveStarWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field1 = 0;
    temp_r31->unk00_field2 = 0;
    temp_r31->unk00_field4 = 0;
    temp_r31->unk01 = 4;
    temp_r31->unk00_field3 = arg0;
    temp_r31->unk06 = 0;
    temp_r31->unk02 = 0;
    temp_r31->unk08 = 0;
    temp_r31->unk0C = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 11), NULL, 0);
    BoardModelVisibilitySet(temp_r31->unk0C, 0);
    BoardModelPassSet(temp_r31->unk0C, 0);
    BoardModelMotionSpeedSet(temp_r31->unk0C, 0.0f);
    BoardModelLayerSet(temp_r31->unk0C, 2);
    StarInlineFunc00();
    HuAudFXPlay(0x338);
    HuAudFXPlay(0x353);
    StarInlineFunc01();
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardTutorialHookExec(0x15, 0);
    }
    BoardPlayerMotBlendSet(arg0, 0, 0xF);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    StarInlineFunc02();
    StarInlineFunc01();
    BoardPlayerVoiceEnableSet(arg0, 7, 0);
    BoardPlayerMotionShiftSet(arg0, 7, 0.0f, 8.0f, 0);
    HuAudFXPlay(boardStarSndTbl[GWPlayer[arg0].character]);
    BoardPlayerStarsAdd(arg0, 1);
    HuAudFXPlay(8);
    HuPrcSleep(10);
    if (_CheckFlag(FLAG_ID_MAKE(1, 11))) {
        BoardPlayerMotionEndWait(arg0);
    } else {
        temp_r25 = HuAudSStreamPlay(6);
        BoardPlayerMotionEndWait(arg0);
        while (msmStreamGetStatus(temp_r25) != 0) {
            HuPrcVSleep();
        }
    }
    BoardPlayerVoiceEnableSet(arg0, 7, 1);
}

void BoardStarShowNext(s32 arg0) {
    Mtx spBC;
    Mtx sp8C;
    Mtx sp5C;
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    float temp_f31;
    WipeState *var_r26;
    s32 var_r28;
    s32 var_r30;
    s16 var_r27;
    s16 var_r29;

    var_r28 = 0;
    if (GWBoardGet() == BOARD_ID_EXTRA1 || GWBoardGet() == BOARD_ID_EXTRA2) {
        return;
    }
    _SetFlag(0x1001C);
    var_r26 = &wipeData;
    if (var_r26->mode == 0) {
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
    } else {
        HuPrcSleep(18);
    }
    BoardStatusItemSet(0);
    if (GWBoardGet() == BOARD_ID_MAIN6 && BoardItemPrevGet() != 9 && boardStarGiveHook) {
        boardStarGiveHook();
    }
    BoardSpaceStarMove();
    if (arg0 == -1) {
        var_r28 = 1;
        arg0 = 0;
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            BoardPlayerCornerPosSet(var_r29);
        }
        BoardSpacePosGet(0, GWPlayer[arg0].space_curr, &sp38);
        BoardPlayerPosSetV(arg0, &sp38);
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 23))) {
        BoardAudSeqFadeOut(0, 1000);
    }
    showNextObj = omAddObjEx(boardObjMan, 0x7E03, 0, 0, -1, ShowNextUpdate);
    BoardPlayerIdleSet(arg0);
    BoardModelMotionStart(BoardStarHostMdlGet(), 1, 0x40000001);
    BoardModelPosGet(BoardStarHostMdlGet(), &sp50);
    showNextObj->scale.x = sp50.x;
    showNextObj->scale.y = sp50.y;
    showNextObj->scale.z = sp50.z;
    BoardPlayerPosGet(arg0, &sp38);
    sp50.y = sp38.y;
    PSVECSubtract(&sp50, &sp38, &sp20);
    sp20.y = 0.0f;
    temp_f31 = PSVECMag(&sp20);
    if (temp_f31 > 3000.0f) {
        var_r27 = 0xF0;
    } else if (temp_f31 > 1500.0f) {
        var_r27 = 0x78;
    } else {
        var_r27 = 0x78;
    }
    BoardViewMoveStart(&sp38, &sp50, var_r27);
    showNextObj->trans.x = 68.0f;
    showNextObj->trans.y = 430.0f;
    showNextObj->trans.z = 100.0f;
    sp44.x = showNextObj->trans.x;
    sp44.y = showNextObj->trans.y;
    sp44.z = showNextObj->trans.z;
    Hu3D2Dto3D(&sp44, 1, &sp44);
    BoardModelPosSetV(BoardStarHostMdlGet(), &sp44);
    BoardCameraRotGet(&sp2C);
    PSMTXRotRad(sp5C, 'y', MTXDegToRad(10.0f));
    PSMTXRotRad(sp8C, 'x', MTXDegToRad(sp2C.x));
    PSMTXConcat(sp8C, sp5C, spBC);
    BoardModelMtxSet(BoardStarHostMdlGet(), &spBC);
    BoardModelRotSet(BoardStarHostMdlGet(), 0.0f, 0.0f, 0.0f);
    BoardModelScaleSet(BoardStarHostMdlGet(), 0.09f, 0.09f, 0.09f);
    BoardMusStart(1, 7, 0x7F, 0);
    BoardCameraMoveSet(0);
    BoardCameraMotionWait();
    BoardCameraMoveSet(1);
    HuPrcSleep(1);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    if (var_r28 == 0) {
        var_r30 = lbl_8011E040[GWBoardGet()] + 6;
    } else {
        var_r30 = lbl_8011E064[GWBoardGet()][0];
    }
    BoardWinCreate(3, var_r30, -1);
    BoardWinPause();
    BoardViewMoveEnd();
    while (!BoardViewMoveCheck()) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    BoardWinKill();
    HuPrcSleep(3);
    if (var_r28 == 0) {
        var_r30 = lbl_8011E040[GWBoardGet()] + 7;
    } else {
        var_r30 = lbl_8011E064[GWBoardGet()][1];
    }
    BoardWinCreate(3, var_r30, -1);
    BoardWinWait();
    BoardWinKill();
    if (GWBoardGet() == BOARD_ID_MAIN6 && BoardItemPrevGet() != 9 && boardStarShowNextHook) {
        boardStarShowNextHook();
    }
    BoardAudSeqFadeOut(1, 1000);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardViewWait();
    PSMTXIdentity(spBC);
    BoardModelMtxSet(BoardStarHostMdlGet(), &spBC);
    HideNextHost(1);
    while (showNextObj) {
        HuPrcVSleep();
    }
    BoardCameraMoveSet(0);
    BoardCameraTargetPlayerSet(arg0);
    BoardCameraMotionWait();
    BoardCameraMoveSet(1);
    BoardStatusItemSet(1);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 23))) {
        BoardMusStartBoard();
    }
    _ClearFlag(FLAG_ID_MAKE(1, 28));
}

static void ShowNextUpdate(omObjData *arg0) {
    ShowNextWork *temp_r30 = OM_GET_WORK_PTR(arg0, ShowNextWork);
    Vec sp8;

    if (temp_r30->unk00_field0 != 0 || BoardIsKill()) {
        showNextObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    switch (temp_r30->unk01) {
        case 0:
            sp8.x = arg0->trans.x;
            sp8.y = arg0->trans.y;
            sp8.z = arg0->trans.z;
            Hu3D2Dto3D(&sp8, 1, &sp8);
            break;
        case 1:
            sp8.x = arg0->scale.x;
            sp8.y = arg0->scale.y;
            sp8.z = arg0->scale.z;
            BoardModelLayerSet(BoardStarHostMdlGet(), 0);
            BoardModelRotSet(BoardStarHostMdlGet(), 0.0f, 0.0f, 0.0f);
            BoardModelScaleSet(BoardStarHostMdlGet(), 1.0f, 1.0f, 1.0f);
            temp_r30->unk00_field0 = 1;
            break;
    }
    BoardModelPosSetV(BoardStarHostMdlGet(), &sp8);
}

static void HideNextHost(s32 arg0) {
    ShowNextWork *temp_r31 = OM_GET_WORK_PTR(showNextObj, ShowNextWork);

    temp_r31->unk01 = arg0;
}
