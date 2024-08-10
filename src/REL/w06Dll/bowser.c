#include "REL/w06Dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/board/audio.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    struct {
        u8 unk00_field0 : 1;
    };
    char unk01[3];
    s32 unk04;
    s32 unk08;
    s16 unk0C;
} BssECWork;

static void fn_1_93C8(void);
static void fn_1_94D4(void);
static void fn_1_95AC(s32 arg0);
static void fn_1_9E5C(s32 arg0);
static void fn_1_A408(s32 arg0);
static void fn_1_AB4C(s32 arg0, s32 arg1);
static void fn_1_B27C(s32 arg0);
static void fn_1_B6A0(float arg0, s16 arg1);
static void fn_1_B8E0(omObjData *arg0);
static void fn_1_BB10(s32 arg0);
static void fn_1_BD08(s32 arg0);
static void fn_1_BD44(void);
static void fn_1_BD8C(s32 arg0);
static void fn_1_C40C(void);
static s32 fn_1_C9BC(void);
static s32 fn_1_CA8C(s32 arg0, s32 arg1);
static void fn_1_CACC(void);

static s8 lbl_1_bss_F4;
static s32 lbl_1_bss_F0;
static omObjData *lbl_1_bss_EC;
static Process *lbl_1_bss_E8;

static s16 lbl_1_data_498 = -1;
static s16 lbl_1_data_49A = -1;
static s16 lbl_1_data_49C = -1;
static s16 lbl_1_data_49E = -1;
static s16 lbl_1_data_4A0 = -1;
static s16 lbl_1_data_4A2 = -1;

static s8 lbl_1_data_4A4[] = {
    0, 0, 90,   0,
    0, 0,  0, 166
};

static s32 lbl_1_data_4AC[8] = {
    0x00000128,
    0x00000168,
    0x000001A8,
    0x000001E8,
    0x00000228,
    0x00000268,
    0x000002A8,
    0x000002E8
};

static s32 lbl_1_data_4CC[8] = {
    0x00000123,
    0x00000163,
    0x000001A3,
    0x000001E3,
    0x00000223,
    0x00000263,
    0x000002A3,
    0x000002E3
};

static s32 lbl_1_data_4EC[] = {
    DATA_MAKE_NUM(DATADIR_BKOOPA, 8),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 10),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 11),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 12),
    DATA_MAKE_NUM(DATADIR_W06, 24),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 9),
    DATA_MAKE_NUM(DATADIR_W06, 25),
    DATA_MAKE_NUM(DATADIR_W06, 26),
    -1
};

static s32 lbl_1_data_510[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 19),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 19),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 19),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 19),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 19),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 19),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 19),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 19)
};

void fn_1_8F20(void) {
    omObjData *temp_r3;
    BssECWork *temp_r31;
    s32 var_r28;
    s32 i;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_B8E0);
    lbl_1_bss_EC = temp_r3;
    temp_r31 = OM_GET_WORK_PTR(temp_r3, BssECWork);
    temp_r31->unk00_field0 = 0;
    temp_r31->unk0C = 0;
    temp_r31->unk08 = 0;
    temp_r31->unk04 = 1;
    lbl_1_data_498 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BKOOPA, 7), lbl_1_data_4EC, 0);
    BoardModelMotionStart(lbl_1_data_498, 1, 0x40000001);
    BoardModelScaleSet(lbl_1_data_498, 2.0f, 2.0f, 2.0f);
    lbl_1_data_49A = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 11), NULL, 0);
    BoardModelMotionStart(lbl_1_data_49A, 0, 0x40000001);
    if (_CheckFlag(FLAG_ID_MAKE(1, 1))) {
        fn_1_CACC();
        if (lbl_1_bss_0->unk00_field3 == 0) {
            var_r28 = BoardSpaceStarGet(lbl_1_bss_0->unk04 - 1);
            BoardSpaceTypeSet(0, var_r28, 10);
        }
    } else {
        BoardModelVisibilitySet(lbl_1_data_49A, 0);
        BoardModelVisibilitySet(lbl_1_data_498, 0);
    }
    HuDataDirClose(DATADIR_BKOOPA);
    if (_CheckFlag(FLAG_ID_MAKE(1, 9))) {
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_0->unk05 & (1 << i)) {
                BoardPlayerPreTurnHookSet(i, fn_1_C9BC);
            }
        }
    }
    if (lbl_1_bss_0->unk00_field4 != 0) {
        BoardModelMotionStart(lbl_1_data_498, 2, 0);
        BoardModelMotionTimeSet(lbl_1_data_498, 90.0f);
        BoardModelMotionSpeedSet(lbl_1_data_498, 0.0f);
    }
}

void fn_1_91D8(void) {
    fn_1_BD44();
    if (lbl_1_data_498 != -1) {
        BoardModelKill(lbl_1_data_498);
        lbl_1_data_498 = -1;
    }
    if (lbl_1_data_49A != -1) {
        BoardModelKill(lbl_1_data_49A);
        lbl_1_data_49A = -1;
    }
    if (lbl_1_data_49E != -1) {
        BoardModelKill(lbl_1_data_49E);
        lbl_1_data_49E = -1;
    }
}

void fn_1_9294(s32 arg0, s32 arg1) {
    BoardRollCreate(arg0, 0);
    fn_1_92D8(arg0, arg1);
}

s32 fn_1_92D8(s32 arg0, s32 arg1) {
    lbl_1_bss_F0 = 0;
    if (fn_1_CA8C(arg0, arg1) == 0) {
        return lbl_1_bss_F0;
    }
    lbl_1_bss_F4 = arg0;
    BoardRollDispSet(0);
    lbl_1_bss_E8 = HuPrcChildCreate(fn_1_93C8, 0x2003, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_E8, fn_1_94D4);
    while (lbl_1_bss_E8) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
    return lbl_1_bss_F0;
}

static void fn_1_93C8(void) {
    s32 temp_r31;
    s32 temp_r30;

    temp_r31 = GWSystem.player_curr;
    temp_r30 = GWPlayer[temp_r31].space_curr;
    BoardAudSeqPause(0, 1, 0x1F4);
    fn_1_BD8C(temp_r31);
    if (_CheckFlag(FLAG_ID_MAKE(1, 6))) {
        fn_1_AB4C(temp_r31, temp_r30);
    } else if (GWPlayer[temp_r31].bowser_suit) {
        fn_1_B27C(temp_r31);
    } else {
        switch (BoardPlayerSizeGet(temp_r31)) {
            case 1:
                fn_1_95AC(temp_r31);
                break;
            case 0:
                fn_1_9E5C(temp_r31);
                break;
            case 2:
                fn_1_A408(temp_r31);
                break;
        }
    }
    HuPrcEnd();
}

static void fn_1_94D4(void) {
    if (lbl_1_data_4A2 != -1) {
        BoardModelKill(lbl_1_data_4A2);
        lbl_1_data_4A2 = -1;
    }
    if (lbl_1_data_4A0 != -1) {
        BoardModelKill(lbl_1_data_4A0);
        lbl_1_data_4A0 = -1;
    }
    if (lbl_1_data_49C != -1) {
        BoardPlayerMotionKill(GWSystem.player_curr, lbl_1_data_49C);
        lbl_1_data_49C = -1;
    }
    lbl_1_bss_E8 = NULL;
}

static void fn_1_95AC(s32 arg0) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f30;
    float var_f31;
    s32 temp_r30;
    s32 temp_r29;

    lbl_1_data_49C = BoardPlayerMotionCreate(arg0, lbl_1_data_510[GWPlayer[arg0].character]);
    BoardPlayerPosGet(arg0, &sp38);
    BoardModelPosGet(lbl_1_data_49A, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    VECNormalize(&sp20, &sp20);
    BoardModelMotionShiftSet(lbl_1_data_498, 4, 0.0f, 8.0f, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x3C);
    BoardMusStart(1, 6, 0x7F, 0);
    sp14.x = 0.0f;
    sp14.y = 150.0f;
    sp14.z = 0.0f;
    sp8.x = -14.0f;
    sp8.y = atan2d(-sp20.x, -sp20.z);
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_data_49A, &sp8, &sp14, 1620.0f, -1.0f, 21);
    BoardCameraMotionWait();
    BoardCameraTargetModelSet(-1);
    omVibrate(arg0, 12, 4, 2);
    BoardPlayerMotionStart(arg0, 9, 0);
    HuAudFXPlay(lbl_1_data_4AC[GWPlayer[arg0].character]);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    while (!BoardPlayerMotionEndCheck(arg0)) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(arg0);
    HuPrcSleep(30);
    BoardModelAttrSet(lbl_1_data_498, 0x40000004);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 8.0f, 0x40000001);
    BoardWinCreate(2, MAKE_MESSID(48, 2), 5);
    BoardWinWait();
    BoardWinKill();
    BoardCameraMotionStartEx(-1, NULL, NULL, 2000.0f, -1.0f, 21);
    BoardCameraMotionWait();
    BoardModelMotionShiftSet(lbl_1_data_498, 5, 0.0f, 8.0f, 0);
    HuPrcSleep(8);
    while (BoardModelMotionTimeGet(lbl_1_data_498) < 80.0f) {
        HuPrcVSleep();
    }
    temp_r29 = HuAudFXPlay(0x34E);
    fn_1_BB10(1);
    while (BoardModelMotionTimeGet(lbl_1_data_498) < 60.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(lbl_1_data_4CC[GWPlayer[arg0].character]);
    omVibrate(arg0, 12, 4, 2);
    BoardPlayerMotionStart(arg0, lbl_1_data_49C, 0x40000001);
    temp_r30 = BoardSpaceFlagPosGet(0, 0x8000, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    VECNormalize(&sp20, &sp20);
    sp20.x = 500.0f * sp20.x / 90.0f;
    sp20.z = 500.0f * sp20.z / 90.0f;
    sp38.y += 150.0f;
    for (var_f31 = 0.0f; var_f31 < 90.0f; var_f31 += 1.0f) {
        sp38.x += sp20.x;
        sp38.z += sp20.z;
        if (sp38.y < 0.0f) {
            sp38.y = 0.0f;
            break;
        }
        sp38.y += 30.0f + -0.08166667f * var_f31 * var_f31 * 0.125f;
        BoardPlayerPosSetV(arg0, &sp38);
        HuPrcVSleep();
    }
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSS, 1);
    HuPrcSleep(2);
    BoardCameraMoveSet(0);
    BoardModelVisibilitySet(BoardPlayerModelGet(arg0), 0);
    BoardPlayerRotYSet(arg0, 0.0f);
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    BoardCameraTargetSpaceSet(temp_r30);
    HuAudFXFadeOut(temp_r29, 0xC8);
    fn_1_BB10(0);
    BoardModelMotionStart(lbl_1_data_498, 1, 0x40000001);
    BoardModelRotYSet(lbl_1_data_498, 0.0f);
    sp38.x = sp2C.x;
    sp38.y = sp2C.y + 1000.0f;
    sp38.z = sp2C.z;
    BoardPlayerPosSetV(arg0, &sp38);
    BoardModelVisibilitySet(BoardPlayerModelGet(arg0), 1);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSS, 30);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    var_f31 = 0.0f;
    var_f30 = var_f31;
    while (TRUE) {
        if (sp38.y < sp2C.y) {
            if (var_f30 >= 3.0f) {
                break;
            }
            HuAudFXPlay(0x4A7);
            omVibrate(arg0, 12, 6, 6);
            sp38.y = sp2C.y + 30.0f * (3.0f - var_f30);
            var_f31 = 0.0f;
            var_f30 += 1.0f;
        }
        sp38.y += 5.0f + -0.08166667f * var_f31 * var_f31;
        BoardPlayerPosSetV(arg0, &sp38);
        HuPrcVSleep();
        var_f31 += 1.0f;
    }
    BoardPlayerPosSetV(arg0, &sp2C);
    BoardPlayerMotionStart(arg0, 6, 0x40000001);
    HuPrcSleep(60);
    GWPlayer[arg0].space_curr = temp_r30;
    BoardAudSeqFadeOut(1, 1000);
    HuPrcSleep(24);
    fn_1_B6A0(0.0f, 20);
    BoardCameraMoveSet(1);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    BoardAudSeqPause(0, 0, 1000);
}

static void fn_1_9E5C(s32 arg0) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    u16 var_r30;
    s32 var_r25;
    s32 var_r29;
    s16 i;
    s16 var_r26;
    s16 var_r28;

    BoardPlayerPosGet(arg0, &sp38);
    BoardModelPosGet(lbl_1_data_49A, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    VECNormalize(&sp20, &sp20);
    BoardModelMotionShiftSet(lbl_1_data_498, 4, 0.0f, 8.0f, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x3C);
    BoardMusStart(1, 6, 0x7F, 0);
    sp14.x = 0.0f;
    sp14.y = 150.0f;
    sp14.z = 0.0f;
    sp8.x = -14.0f;
    sp8.y = atan2d(-sp20.x, -sp20.z);
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_data_49A, &sp8, &sp14, 1620.0f, -1.0f, 21);
    BoardCameraMotionWait();
    BoardCameraTargetModelSet(-1);
    omVibrate(arg0, 12, 4, 2);
    BoardPlayerMotionStart(arg0, 9, 0);
    HuAudFXPlay(lbl_1_data_4AC[GWPlayer[arg0].character]);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    while (!BoardPlayerMotionEndCheck(arg0)) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(arg0);
    HuPrcSleep(30);
    BoardModelAttrSet(lbl_1_data_498, 0x40000004);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_data_498, 7, 0.0f, 8.0f, 0);
    HuPrcSleep(9);
    while (BoardModelMotionTimeGet(lbl_1_data_498) < 33.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x51);
    var_r30 = BoardPlayerCoinsGet(arg0);
    if (var_r30 != 0) {
        var_r29 = 0x300003;
        var_r28 = -1;
        var_r30 = BoardPlayerCoinsGet(arg0) - (var_r30 >> 1);
        var_r25 = 8;
    } else {
        var_r29 = 0x300005;
        var_r28 = 1;
        var_r30 = 50;
        var_r25 = 7;
    }
    BoardWinCreate(2, var_r29, 5);
    BoardWinWait();
    if (var_r30 >= 50) {
        var_r26 = 1;
    } else if (var_r30 >= 20) {
        var_r26 = 3;
    } else {
        var_r26 = 6;
    }
    for (i = 0; i < var_r30; i++) {
        BoardPlayerCoinsAdd(arg0, var_r28);
        if (var_r28 == -1) {
            HuAudFXPlay(0xE);
        } else {
            HuAudFXPlay(7);
        }
        HuPrcSleep(var_r26);
    }
    HuAudFXPlay(0xF);
    BoardPlayerMotBlendSet(arg0, BoardPlayerRotYGet(arg0) + 180.0f, 0x14);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    BoardModelAttrSet(lbl_1_data_498, 0x40000004);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 8.0f, 0x40000001);
    BoardPlayerMotionShiftSet(arg0, var_r25, 0.0f, 8.0f, 0);
    HuPrcSleep(10);
    while (!BoardPlayerMotionEndCheck(arg0)) {
        HuPrcVSleep();
    }
    if (var_r28 == -1) {
        var_r29 = 0x300004;
    } else {
        var_r29 = 0x300006;
    }
    BoardModelMotionShiftSet(lbl_1_data_498, 3, 0.0f, 8.0f, 0);
    HuAudFXPlay(0x3A);
    BoardWinCreate(2, var_r29, 5);
    BoardWinWait();
    BoardWinKill();
    BoardAudSeqFadeOut(1, 1000);
    HuPrcSleep(24);
    BoardPlayerIdleSet(arg0);
    BoardCameraMoveSet(1);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 8.0f, 0x40000001);
    fn_1_B6A0(0.0f, 20);
    BoardAudSeqPause(0, 0, 1000);
}

static void fn_1_A408(s32 arg0) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    OverlayID var_r29;
    s32 temp_r28;
    s32 temp_r27;
    s32 i;

    BoardPlayerPosGet(arg0, &sp38);
    BoardModelPosGet(lbl_1_data_49A, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    VECNormalize(&sp20, &sp20);
    BoardModelMotionShiftSet(lbl_1_data_498, 4, 0.0f, 8.0f, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x3C);
    BoardMusStart(1, 6, 0x7F, 0);
    sp14.x = 0.0f;
    sp14.y = 250.0f;
    sp14.z = 0.0f;
    sp8.x = -8.0f;
    sp8.y = atan2d(-sp20.x, -sp20.z) - 45.0;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_data_49A, &sp8, &sp14, 1700.0f, -1.0f, 63);
    BoardCameraMotionWait();
    BoardCameraTargetModelSet(-1);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    BoardModelAttrSet(lbl_1_data_498, 0x40000004);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 8.0f, 0x40000001);
    BoardWinCreate(2, MAKE_MESSID(48, 7), 5);
    BoardWinWait();
    BoardWinKill();
    fn_1_BD08(0);
    BoardPlayerPosGet(arg0, &sp38);
    BoardAudSeqFadeOut(1, 1000);
    BoardModelMotionShiftSet(lbl_1_data_498, 2, 0.0f, 10.0f, 0);
    HuPrcSleep(55);
    BoardPlayerMotionShiftSet(arg0, 4, 0.0f, 5.0f, 0);
    HuPrcSleep(5);
    temp_r28 = HuAudFXPlay(0x3D);
    BoardPlayerPosGet(arg0, &sp20);
    var_f31 = 0.0f;
    while (TRUE) {
        if (BoardModelMotionTimeGet(lbl_1_data_498) >= 90.0f) {
            BoardModelAttrSet(lbl_1_data_498, 0x40000002);
        }
        sp38.y += 50.0f;
        if (sp38.y > sp20.y + 700.0f) {
            break;
        }
        BoardPlayerPosSetV(arg0, &sp38);
        HuPrcVSleep();
        var_f31 += 1.0f;
    }
    BoardModelVisibilitySet(lbl_1_data_498, 0);
    _SetFlag(FLAG_ID_MAKE(1, 28));
    _SetFlag(FLAG_ID_MAKE(1, 14));
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    if (temp_r28 >= 0) {
        while (HuAudFXStatusGet(temp_r28) != 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXAllStop();
    BoardAudSeqFadeOutAll();
    lbl_1_bss_0->unk06 = BoardItemPrevGet() + 1;
    if (BoardRandMod(100) < 50) {
        var_r29 = OVL_M457;
        GWMGAvailSet(0x1C9);
        GWSystem.mg_next = 0x38;
    } else {
        var_r29 = OVL_M458;
        GWMGAvailSet(0x1CA);
        GWSystem.mg_next = 0x39;
    }
    _SetFlag(FLAG_ID_MAKE(1, 6));
    BoardRollUpdateSet(arg0);
    if (!_CheckFlag(FLAG_ID_MAKE(1, 12))) {
        GWPlayer->coin_win = 0;
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 12))) {
        GWPlayer[1].coin_win = 0;
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 12))) {
        GWPlayer[2].coin_win = 0;
    }
    if (!_CheckFlag(FLAG_ID_MAKE(1, 12))) {
        GWPlayer[3].coin_win = 0;
    }
    _ClearFlag(FLAG_ID_MAKE(1, 7));
    for (i = 0; i < 4; i++) {
        if (GWPlayerTeamGet(i)) {
            GWPlayer[i].team_backup = 1;
        } else {
            GWPlayer[i].team_backup = 0;
        }
        if (i == arg0) {
            GWPlayerCfg[i].group = 0;
        } else {
            GWPlayerCfg[i].group = 1;
        }
    }
    if (GWPlayer[arg0].com && !GWMGShowComGet()) {
        if (BoardRandMod(100) > 60) {
            _SetFlag(FLAG_ID_MAKE(1, 7));
        }
        BoardAudSeqFadeOutFast(0);
        BoardAudSeqFadeOutFast(1);
        lbl_1_bss_0->unk00_field4 = 0;
        fn_1_BD08(1);
        HuPrcSleep(60);
        for (i = 0; i < 4; i++) {
            temp_r27 = GWPlayer[i].team_backup;
            GWPlayer[i].team = temp_r27;
            GWPlayerCfg[i].group = temp_r27;
        }
        fn_1_AB4C(arg0, GWPlayer[arg0].space_curr);
        BoardMusStartBoard();
        _ClearFlag(FLAG_ID_MAKE(1, 6));
        BoardCameraViewSet(1);
        BoardCameraMotionWait();
        BoardRollCreate(arg0, 0);
    } else {
        BoardNextOvlSet(var_r29);
    }
}

static void fn_1_AB4C(s32 arg0, s32 arg1) {
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    s16 i;
    s16 var_r27;
    s16 var_r30;
    s16 var_r24;
    s32 var_r26;
    s32 var_r25;
    s32 temp_r23;
    s32 var_r29;

    var_r29 = 0;
    lbl_1_bss_F0 = 1;
    if (GWPlayer[arg0].com && !GWMGShowComGet()) {
        BoardModelVisibilitySet(lbl_1_data_498, 1);
        BoardModelVisibilitySet(lbl_1_data_49A, 1);
        BoardModelMotionStart(lbl_1_data_498, 1, 0x40000001);
        BoardPlayerMotionStart(arg0, 1, 0x40000001);
    }
    BoardStatusItemSet(1);
    BoardMusStart(1, 6, 0x7F, 0);
    BoardItemPrevSet(lbl_1_bss_0->unk06 - 1);
    lbl_1_bss_0->unk06 = 0;
    BoardSpacePosGet(0, arg1, &sp3C);
    BoardPlayerPosSetV(arg0, &sp3C);
    BoardModelPosGet(lbl_1_data_49A, &sp30);
    VECSubtract(&sp30, &sp3C, &sp24);
    VECNormalize(&sp24, &sp24);
    BoardPlayerRotYSet(arg0, atan2d(sp24.x, sp24.z));
    BoardPlayerSizeSet(arg0, 2);
    sp18.x = 0.0f;
    sp18.y = 150.0f;
    sp18.z = 0.0f;
    spC.x = -25.0f;
    spC.y = atan2d(-sp24.x, -sp24.z);
    spC.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_data_49A, &spC, &sp18, 2000.0f, -1.0f, 2);
    BoardCameraMotionWait();
    BoardCameraTargetModelSet(-1);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    _ClearFlag(FLAG_ID_MAKE(1, 28));
    _ClearFlag(FLAG_ID_MAKE(1, 14));
    if (_CheckFlag(FLAG_ID_MAKE(1, 7))) {
        var_r29 = 0;
    } else {
        var_r29 = 1;
    }
    if (var_r29 != 0) {
        var_r26 = MAKE_MESSID(48, 10);
        var_r25 = 8;
        HuAudFXPlay(0x3A);
        BoardModelMotionShiftSet(lbl_1_data_498, 3, 0.0f, 8.0f, 0);
    } else {
        var_r26 = MAKE_MESSID(48, 8);
        var_r25 = 7;
    }
    HuAudFXPlay(0x3C);
    BoardWinCreate(2, var_r26, 5);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerMotBlendSet(arg0, BoardPlayerRotYGet(arg0) + 180.0f, 0x14);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    if (var_r29 != 0) {
        BoardModelMotionShiftSet(lbl_1_data_498, 7, 0.0f, 8.0f, 0);
        temp_r23 = BoardPlayerCoinsGet(arg0);
        var_r30 = temp_r23 - (BoardPlayerCoinsGet(arg0) >> 1);
        if (var_r30 < 0) {
            var_r30 = 0;
        }
        if (var_r30 >= 50) {
            var_r27 = 1;
        } else if (var_r30 >= 20) {
            var_r27 = 3;
        } else {
            var_r27 = 6;
        }
        for (i = 0; i < var_r30; i++) {
            BoardPlayerCoinsAdd(arg0, -1);
            HuAudFXPlay(0xE);
            HuPrcSleep(var_r27);
        }
        HuAudFXPlay(0xF);
    } else {
        BoardModelMotionShiftSet(lbl_1_data_498, 8, 0.0f, 8.0f, 0);
        BoardWinCreate(2, MAKE_MESSID(48, 9), 5);
        BoardWinWait();
        BoardWinKill();
        BoardAudSeqFadeOut(1, 1000);
        lbl_1_data_4A2 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 16), NULL, 0);
        HuAudFXPlay(0x4A8);
        BoardModelPosGet(lbl_1_data_49A, &sp30);
        BoardModelPosSetV(lbl_1_data_4A2, &sp30);
        BoardModelMotionStart(lbl_1_data_4A2, 0, 0);
        BoardModelScaleSet(lbl_1_data_4A2, 2.0f, 2.0f, 2.0f);
        while (BoardModelMotionTimeGet(lbl_1_data_4A2) < 110.0f) {
            HuPrcVSleep();
        }
        BoardModelVisibilitySet(lbl_1_data_498, 0);
        BoardModelVisibilitySet(lbl_1_data_49A, 0);
        while (!BoardModelMotionEndCheck(lbl_1_data_4A2)) {
            HuPrcVSleep();
        }
        BoardModelVisibilitySet(lbl_1_data_4A2, 0);
        lbl_1_bss_0->unk00_field3 = 1;
        var_r24 = BoardSpaceStarGet(lbl_1_bss_0->unk04 - 1);
        BoardSpaceTypeSet(0, var_r24, 1);
        BoardMusStartBoard();
    }
    BoardPlayerMotionShiftSet(arg0, var_r25, 0.0f, 8.0f, 0);
    HuPrcSleep(8);
    BoardModelAttrSet(lbl_1_data_498, 0x40000004);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    while (!BoardPlayerMotionEndCheck(arg0)) {
        HuPrcVSleep();
    }
    if (var_r29 != 0) {
        BoardAudSeqFadeOut(1, 1000);
    }
    HuPrcSleep(48);
    BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 8.0f, 0x40000001);
    BoardPlayerIdleSet(arg0);
    fn_1_B6A0(0.0f, 20);
}

static void fn_1_B27C(s32 arg0) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s16 i;
    s32 var_r29;
    s16 var_r28;
    u16 var_r27;

    BoardPlayerPosGet(arg0, &sp38);
    BoardModelPosGet(lbl_1_data_49A, &sp2C);
    VECSubtract(&sp2C, &sp38, &sp20);
    VECNormalize(&sp20, &sp20);
    BoardModelMotionShiftSet(lbl_1_data_498, 4, 0.0f, 8.0f, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x3C);
    sp14.x = 0.0f;
    sp14.y = 150.0f;
    sp14.z = 0.0f;
    sp8.x = -14.0f;
    sp8.y = atan2d(-sp20.x, -sp20.z);
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_data_49A, &sp8, &sp14, 1620.0f, -1.0f, 21);
    BoardCameraMotionWait();
    BoardCameraTargetModelSet(-1);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(arg0);
    HuPrcSleep(30);
    BoardModelAttrSet(lbl_1_data_498, 0x40000004);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 8.0f, 0x40000001);
    BoardMusStart(1, 6, 0x7F, 0);
    BoardModelMotionShiftSet(lbl_1_data_498, 7, 0.0f, 8.0f, 0);
    HuPrcSleep(8);
    var_r29 = 0x300026;
    var_r27 = 50;
    BoardWinCreate(2, var_r29, 5);
    BoardWinWait();
    var_r28 = 1;
    for (i = 0; i < var_r27; i++) {
        BoardPlayerCoinsAdd(arg0, 1);
        HuAudFXPlay(7);
        HuPrcSleep(var_r28);
    }
    HuAudFXPlay(0xF);
    BoardPlayerMotBlendSet(arg0, BoardPlayerRotYGet(arg0) + 180.0f, 0x14);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    BoardModelAttrSet(lbl_1_data_498, 0x40000004);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    var_r29 = 0x300027;
    BoardModelMotionShiftSet(lbl_1_data_498, 3, 0.0f, 8.0f, 0);
    HuAudFXPlay(0x3A);
    BoardWinCreate(2, var_r29, 5);
    BoardWinWait();
    BoardWinKill();
    BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 8.0f, 0x40000001);
    BoardAudSeqFadeOut(1, 1000);
    HuPrcSleep(24);
    BoardPlayerIdleSet(arg0);
    BoardCameraMoveSet(1);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    fn_1_B6A0(0.0f, 20);
    BoardAudSeqPause(0, 0, 1000);
}

static void fn_1_B6A0(float arg0, s16 arg1) {
    float var_f30;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;

    if (arg1 <= 0) {
        arg1 = 1;
    }
    OSs16tof32(&arg1, &var_f24);
    arg0 = BoardDAngleCalc(arg0);
    var_f26 = BoardDAngleCalc(BoardModelRotYGet(lbl_1_data_498));
    var_f30 = BoardDAngleCalc(arg0 - var_f26);
    var_f25 = var_f30 / var_f24;
    if (var_f30 < 0.0f) {
        var_f28 = -var_f30;
    } else {
        var_f28 = var_f30;
    }
    if (var_f28 < 5.0f) {
        BoardModelRotYSet(lbl_1_data_498, arg0);
        return;
    }
    BoardModelMotionShiftSet(lbl_1_data_498, 6, 0.0f, 8.0f, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_data_498, 2.0f);
    while (arg1 > 0) {
        var_f27 = var_f25 + BoardModelRotYGet(lbl_1_data_498);
        BoardModelRotYSet(lbl_1_data_498, var_f27);
        HuPrcVSleep();
        arg1--;
    }
    BoardModelRotYSet(lbl_1_data_498, arg0);
    BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 8.0f, 0x40000001);
}

static void fn_1_B8E0(omObjData *arg0) {
    Mtx sp14;
    Vec sp8;
    float temp_f30;
    BssECWork *temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0, BssECWork);
    if (temp_r30->unk00_field0 != 0 || lbl_1_data_49A == -1 || BoardIsKill()) {
        fn_1_BB10(0);
        lbl_1_bss_EC = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    // Bug? Likely to be "%=" instead.
    temp_r30->unk0C % 360;
    OSs16tof32(&temp_r30->unk0C, &temp_f30);
    temp_f30 = 0.5 * sind(temp_f30);
    BoardModelPosGet(lbl_1_data_49A, &sp8);
    sp8.y += temp_f30;
    BoardModelPosSetV(lbl_1_data_49A, &sp8);
    if (temp_r30->unk04 != 0 && lbl_1_bss_0->unk00_field4 == 0) {
        Hu3DModelObjMtxGet(BoardModelIDGet(lbl_1_data_49A), "kuppa", sp14);
        Hu3DMtxTransGet(sp14, &sp8);
        BoardModelPosSetV(lbl_1_data_498, &sp8);
    }
    if (temp_r30->unk08 != 0) {
        Hu3DModelObjMtxGet(BoardModelIDGet(lbl_1_data_498), "itemhook_M", sp14);
        Hu3DMtxTransGet(sp14, &sp8);
        BoardModelPosSetV(lbl_1_data_49E, &sp8);
    }
    temp_r30->unk0C += 4;
}

static void fn_1_BB10(s32 arg0) {
    float var_f30;
    BssECWork *var_r30;

    if (lbl_1_bss_EC) {
        var_r30 = OM_GET_WORK_PTR(lbl_1_bss_EC, BssECWork);
        var_r30->unk08 = arg0;
    }
    if (arg0 != 0) {
        if (lbl_1_data_49E == -1) {
            OSs8tof32(&lbl_1_data_4A4[lbl_1_bss_0->unk04 - 1], &var_f30);
            lbl_1_data_49E = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W06, 14), NULL, 0);
            BoardModelRotSet(lbl_1_data_49E, 45.0f, var_f30, 0.0f);
            BoardModelScaleSet(lbl_1_data_49E, 1.8f, 1.8f, 1.8f);
            BoardModelLayerSet(lbl_1_data_49E, 2);
            BoardModelPassSet(lbl_1_data_49E, 1);
            BoardModelMotionStart(lbl_1_data_49E, 0, 0x40000001);
            BoardModelVisibilitySet(lbl_1_data_49E, 1);
        }
    } else if (lbl_1_data_49E != -1) {
        BoardModelKill(lbl_1_data_49E);
        lbl_1_data_49E = -1;
    }
}

static void fn_1_BD08(s32 arg0) {
    BssECWork *var_r31;

    if (lbl_1_bss_EC) {
        var_r31 = OM_GET_WORK_PTR(lbl_1_bss_EC, BssECWork);
        var_r31->unk04 = arg0;
    }
}

static void fn_1_BD44(void) {
    BssECWork *var_r31;

    if (lbl_1_bss_EC) {
        var_r31 = OM_GET_WORK_PTR(lbl_1_bss_EC, BssECWork);
        var_r31->unk00_field0 = 1;
    }
}

static void fn_1_BD8C(s32 arg0) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f26;
    float var_f25;

    OSs8tof32(&lbl_1_data_4A4[lbl_1_bss_0->unk04 - 1], &var_f25);
    BoardPlayerPosGet(arg0, &sp18);
    BoardModelPosGet(lbl_1_data_49A, &sp24);
    VECSubtract(&sp18, &sp24, &spC);
    var_f26 = atan2d(spC.x, spC.z);
    BoardPlayerMotBlendSet(arg0, var_f26 + 180.0f, 0x14);
    fn_1_B6A0(var_f25, 20);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(arg0);
}

void fn_1_C108(s32 arg0) {
    if (arg0 != 0) {
        BoardModelMotionShiftSet(lbl_1_data_498, 2, 0.0f, 10.0f, 0);
        BoardModelMotionSpeedSet(lbl_1_data_498, 2.0f);
        HuPrcSleep(30);
        lbl_1_bss_0->unk00_field4 = 1;
        while (BoardModelMotionTimeGet(lbl_1_data_498) < 90.0f) {
            HuPrcVSleep();
        }
        BoardModelAttrSet(lbl_1_data_498, 0x40000002);
    } else {
        lbl_1_bss_0->unk00_field4 = 0;
        BoardModelMotionStart(lbl_1_data_498, 2, 0);
        BoardModelMotionTimeSet(lbl_1_data_498, 90.0f);
        BoardModelMotionSpeedSet(lbl_1_data_498, 2.0f);
        HuPrcSleep(2);
        while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
            HuPrcVSleep();
        }
        BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 8.0f, 0x40000001);
    }
}

void fn_1_C2B4(void) {
    s32 i;

    if (lbl_1_bss_0->unk00_field3 != 0) {
        return;
    }
    if (lbl_1_bss_0->unk03 != 0) {
        lbl_1_bss_0->unk03--;
        return;
    }
    for (i = 0; i < 4; i++) {
        if (BoardPlayerAutoSizeGet(i) != 0) {
            return;
        }
    }
    if ((BoardPlayerCoinsGet(0) > 5 || BoardPlayerCoinsGet(1) > 5 || BoardPlayerCoinsGet(2) > 5 || BoardPlayerCoinsGet(3) > 5) && GWSystem.turn > 5) {
        lbl_1_bss_E8 = HuPrcChildCreate(fn_1_C40C, 0x2003, 0x3800, 0, boardMainProc);
        HuPrcDestructorSet2(lbl_1_bss_E8, fn_1_94D4);
        while (lbl_1_bss_E8) {
            HuPrcVSleep();
        }
    }
}

static void fn_1_C40C(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f30;
    s16 var_r29;
    s16 i;

    OSs8tof32(&lbl_1_data_4A4[lbl_1_bss_0->unk04 - 1], &var_f30);
    sp14.x = 0.0f;
    sp14.y = 150.0f;
    sp14.z = 0.0f;
    sp8.x = -14.0f;
    sp8.y = var_f30;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_data_49A, &sp8, &sp14, 1620.0f, -1.0f, 1);
    BoardCameraMotionWait();
    BoardCameraTargetModelSet(-1);
    BoardModelRotYSet(lbl_1_data_498, var_f30);
    lbl_1_data_4A0 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 99), NULL, 0);
    BoardModelVisibilitySet(lbl_1_data_4A0, 0);
    BoardModelLayerSet(lbl_1_data_4A0, 2);
    var_r29 = BoardSpaceStarGet(lbl_1_bss_0->unk04 - 1);
    var_r29 = BoardSpaceLinkFlagSearch(0, var_r29, 0x04000000);
    BoardSpacePosGet(0, var_r29, &sp14);
    BoardModelPosGet(lbl_1_data_498, &sp20);
    sp20.x += -100.0 * sind(BoardModelRotYGet(lbl_1_data_498));
    sp20.z += -100.0 * cosd(BoardModelRotYGet(lbl_1_data_498));
    sp20.y += 250.0f;
    BoardModelPosSetV(lbl_1_data_4A0, &sp20);
    BoardModelScaleSet(lbl_1_data_4A0, 10.0f, 10.0f, 10.0f);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardMusStart(1, 6, 0x7F, 0);
    HuAudFXPlay(0x3B);
    BoardWinCreate(2, MAKE_MESSID(48, 11), 5);
    BoardWinWait();
    BoardWinKill();
    HuAudFXPlay(0x359);
    BoardModelMotionShiftSet(lbl_1_data_498, 4, 0.0f, 10.0f, 0);
    HuPrcSleep(11);
    HuAudFXPlay(0x33F);
    HuAudFXPlay(0x3C);
    for (i = 0; i < 4; i++) {
        omVibrate(i, 12, 0xC, 0);
    }
    HuAudFXPlay(0x352);
    BoardModelVisibilitySet(lbl_1_data_4A0, 1);
    BoardModelMotionStart(lbl_1_data_4A0, 0, 0);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    HuPrcSleep(90);
    BoardModelAttrSet(lbl_1_data_498, 0x40000004);
    BoardModelVisibilitySet(lbl_1_data_4A0, 0);
    while (!BoardModelMotionEndCheck(lbl_1_data_498)) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_data_498, 1, 0.0f, 10.0f, 0);
    BoardWinCreate(0, MAKE_MESSID(48, 12), -1);
    BoardWinWait();
    BoardWinKill();
    BoardAudSeqFadeOut(1, 1000);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 21);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_data_498, 0.0f);
    BoardCameraMoveSet(0);
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    BoardCameraMoveSet(1);
    lbl_1_bss_0->unk03 = 3;
    _SetFlag(FLAG_ID_MAKE(1, 9));
    for (i = 0; i < 4; i++) {
        BoardPlayerPreTurnHookSet(i, fn_1_C9BC);
        lbl_1_bss_0->unk05 |= (1 << i);
    }
    HuPrcEnd();
}

static s32 fn_1_C9BC(void) {
    omVibrate(GWSystem.player_curr, 90, 6, 6);
    HuAudFXPlay(0x314);
    HuAudFXPlay(0x313);
    BoardPlayerResizeAnimExec(GWSystem.player_curr, 1);
    BoardPlayerSizeSet(GWSystem.player_curr, 1);
    BoardWinCreate(0, MAKE_MESSID(48, 13), -1);
    BoardWinWait();
    BoardWinKill();
    lbl_1_bss_0->unk05 &= ~(1 << GWSystem.player_curr);
    return 1;
}

static s32 fn_1_CA8C(s32 arg0, s32 arg1) {
    if (BoardSpaceTypeGet(0, arg1) == 10) {
        return 1;
    } else {
        return 0;
    }
}

static void fn_1_CACC(void) {
    Vec sp8;
    float var_f30;
    s16 var_r30;
    s16 var_r29;
    s16 var_r28;

    if (lbl_1_bss_0->unk00_field3 != 0) {
        BoardModelVisibilitySet(lbl_1_data_498, 0);
        BoardModelVisibilitySet(lbl_1_data_49A, 0);
        return;
    }
    BoardModelVisibilitySet(lbl_1_data_49A, 1);
    BoardModelVisibilitySet(lbl_1_data_498, 1);
    var_r30 = lbl_1_bss_0->unk04 - 1;
    OSs8tof32(&lbl_1_data_4A4[var_r30], &var_f30);
    var_r28 = BoardSpaceStarGet(var_r30);
    var_r29 = BoardSpaceLinkFlagSearch(0, var_r28, 0x04000000);
    BoardSpacePosGet(0, var_r29, &sp8);
    BoardModelPosSetV(lbl_1_data_49A, &sp8);
    BoardModelPosSetV(lbl_1_data_498, &sp8);
    BoardModelRotYSet(lbl_1_data_49A, var_f30);
    BoardModelVisibilitySet(lbl_1_data_498, 1);
    BoardModelVisibilitySet(lbl_1_data_49A, 1);
    BoardModelRotYSet(lbl_1_data_498, 0.0f);
}

void fn_1_CC90(void) {
    s32 var_r31;

    var_r31 = BoardSpaceStarGet(lbl_1_bss_0->unk04 - 1);
    BoardSpaceTypeSet(0, var_r31, 1);
    BoardModelVisibilitySet(lbl_1_data_498, 0);
    BoardModelVisibilitySet(lbl_1_data_49A, 0);
}

void fn_1_CD0C(void) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f30;
    float var_f29;
    s32 var_r28;
    s32 var_r27;
    s16 var_r29;
    s16 var_r26;
    s16 var_r25;
    s16 var_r30;
    s8 *var_r24;

    if (lbl_1_bss_0->unk00_field3 != 0) {
        lbl_1_bss_0->unk00_field3 = 0;
    }
    if (lbl_1_bss_0->unk00_field4 != 0) {
        lbl_1_bss_0->unk00_field4 = 0;
    }
    var_r27 = BoardSpaceStarGetRandom(lbl_1_bss_0->unk04 - 1);
    lbl_1_bss_0->unk04 = var_r27 + 1;
    fn_1_7FA4();
    if (lbl_1_bss_0->unk00_field3 != 0) {
        BoardModelVisibilitySet(lbl_1_data_498, 0);
        BoardModelVisibilitySet(lbl_1_data_49A, 0);
    } else {
        BoardModelVisibilitySet(lbl_1_data_49A, 1);
        BoardModelVisibilitySet(lbl_1_data_498, 1);
        var_r29 = lbl_1_bss_0->unk04 - 1;
        var_r24 = &lbl_1_data_4A4[var_r29];
        OSs8tof32(var_r24, &var_f29);
        var_r26 = BoardSpaceStarGet(var_r29);
        var_r25 = BoardSpaceLinkFlagSearch(0, var_r26, 0x04000000);
        BoardSpacePosGet(0, var_r25, &sp8);
        BoardModelPosSetV(lbl_1_data_49A, &sp8);
        BoardModelPosSetV(lbl_1_data_498, &sp8);
        BoardModelRotYSet(lbl_1_data_49A, var_f29);
        BoardModelVisibilitySet(lbl_1_data_498, 1);
        BoardModelVisibilitySet(lbl_1_data_49A, 1);
        BoardModelRotYSet(lbl_1_data_498, 0.0f);
    }
    BoardModelVisibilitySet(lbl_1_data_498, 1);
    BoardModelVisibilitySet(lbl_1_data_49A, 1);
    BoardModelPosGet(lbl_1_data_498, &sp20);
    BoardViewFocusGetPos(&sp2C);
    VECSubtract(&sp2C, &sp20, &sp14);
    sp14.y = 0.0f;
    temp_f30 = VECMag(&sp14);
    if (temp_f30 > 3000.0f) {
        var_r30 = 180;
    } else if (temp_f30 > 1500.0f) {
        var_r30 = 90;
    } else {
        var_r30 = 60;
    }
    BoardViewFocusSet(&sp20, var_r30);
    var_r28 = BoardSpaceStarGet(lbl_1_bss_0->unk04 - 1);
    BoardSpaceTypeSet(0, var_r28, 10);
    BoardViewMoveEnd();
    while (!BoardViewMoveCheck()) {
        HuPrcVSleep();
    }
    BoardWinCreate(3, 0x300001, -1);
    BoardWinWait();
    BoardWinKill();
}
