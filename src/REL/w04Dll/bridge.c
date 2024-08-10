#include "REL/w04Dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/memory.h"
#include "game/objsub.h"
#include "game/process.h"
#include "game/window.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "ext_math.h"

static void fn_1_17B4(s16 arg0, s16 arg1);
static void fn_1_191C(void);
static void fn_1_1B98(s16 arg0);
static void fn_1_1C2C(void);
static void fn_1_1E60(void);
static void fn_1_2008(void);
static void fn_1_2044(void);

static Process *lbl_1_bss_3C[3];
static Process *lbl_1_bss_38;

static s32 lbl_1_data_298[] = {
    DATA_MAKE_NUM(DATADIR_W04, 32),
    -1
};

void fn_1_12FC(void) {
    Vec sp14;
    Vec sp8;
    s16 *temp_r3;
    s32 var_r29;
    s32 i;

    sp8.x = sp8.y = sp8.z = 1.5f;
    for (i = 0; i < 3; i++) {
        lbl_1_bss_3C[i] = HuPrcChildCreate(fn_1_1E60, 0x2003, 0x1000, 0, boardMainProc);
        HuPrcDestructorSet2(lbl_1_bss_3C[i], fn_1_2008);
        temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, 5 * sizeof(s16), MEMORY_DEFAULT_NUM);
        lbl_1_bss_3C[i]->user_data = temp_r3;
        temp_r3[0] = i;
        temp_r3[1] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 31), lbl_1_data_298, 1);
        BoardModelScaleSetV(temp_r3[1], &sp8);
        temp_r3[2] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 33), NULL, 1);
        BoardModelAttrSet(temp_r3[2], 0x40000001);
        BoardModelHookSet(temp_r3[1], "itemhook_R", temp_r3[2]);
        BoardModelMotionStart(temp_r3[1], 1, 0x40000001);
        var_r29 = (0x8000 >> i);
        var_r29 |= 0x1000;
        temp_r3[3] = BoardSpaceFlagSearch(0, var_r29);
        var_r29 = (0x8000 >> i);
        var_r29 |= 0x800;
        temp_r3[4] = BoardSpaceFlagSearch(0, var_r29);
        BoardSpacePosGet(0, temp_r3[3], &sp14);
        BoardModelPosSetV(temp_r3[1], &sp14);
    }
    sp8.x = sp8.y = sp8.z = 2.0f;
    BoardModelScaleSetV(lbl_1_bss_14[11], &sp8);
    fn_1_1C2C();
    if (lbl_1_bss_0->unk00 & 1) {
        BoardModelMotionStartEndSet(lbl_1_bss_14[5], 0, 180);
        BoardModelMotionTimeSet(lbl_1_bss_14[5], 108.0f);
        fn_1_17B4(0, 1);
        BoardModelAttrSet(lbl_1_bss_14[5], 0x40000002);
        return;
    }
    BoardModelAttrReset(lbl_1_bss_14[5], 0x40000002);
    BoardModelMotionStartEndSet(lbl_1_bss_14[5], 0, 60);
    BoardModelMotionTimeSet(lbl_1_bss_14[5], 0.0f);
    fn_1_17B4(1, 1);
}

void fn_1_15C8(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        HuPrcKill(lbl_1_bss_3C[i]);
    }
}

static s32 lbl_1_data_2AC[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 28),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 28),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 28),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 28),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 28),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 28),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 28),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 28)
};

void fn_1_1618(void) {
    s32 temp_r31;
    s16 temp_r30;

    temp_r31 = GWSystem.player_curr;
    temp_r30 = BoardPlayerMotionCreate(temp_r31, lbl_1_data_2AC[GWPlayer[temp_r31].character]);
    BoardRollDispSet(0);
    BoardPlayerMotBlendSet(temp_r31, 180, 15);
    BoardCameraViewSet(2);
    while (!BoardPlayerMotBlendCheck(temp_r31)) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    lbl_1_bss_0->unk00 ^= 1;
    fn_1_191C();
    fn_1_1C2C();
    HuAudPlayerVoicePlay(temp_r31, 0x128);
    BoardPlayerMotionStart(temp_r31, temp_r30, 0);
    while (!BoardPlayerMotionEndCheck(temp_r31)) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    if (!(lbl_1_bss_0->unk00 & 1)) {
        BoardWinCreate(2, MAKE_MESSID(32, 24), 11);
        BoardWinWait();
        BoardWinKill();
    }
    BoardPlayerMotionShiftSet(temp_r31, 1, 0.0f, 10.0f, 0x40000001);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    BoardRollDispSet(1);
    BoardPlayerMotionKill(temp_r31, temp_r30);
    HuPrcKill(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void fn_1_17B4(s16 arg0, s16 arg1) {
    float var_f30;
    float var_f31;
    s32 i;

    if (arg0 != 0) {
        var_f31 = 0.0f;
        var_f30 = 255.0f / arg1;
    } else {
        var_f31 = 255.0f;
        var_f30 = -255.0f / arg1;
    }
    for (i = 0; i < arg1; i++) {
        BoardModelAlphaSet(lbl_1_bss_14[11], var_f31);
        var_f31 += var_f30;
        HuPrcVSleep();
    }
    if (arg0 != 0) {
        BoardModelAlphaSet(lbl_1_bss_14[11], 0xFF);
    } else {
        BoardModelAlphaSet(lbl_1_bss_14[11], 0);
    }
}

static void fn_1_191C(void) {
    float var_f31;
    float temp_f29;
    float var_f30;
    float temp_f28;
    s32 var_r31;
    s32 var_r30;

    HuAudFXPlay(0x4B);
    if (lbl_1_bss_0->unk00 & 1) {
        BoardWinCreate(2, MAKE_MESSID(32, 23), 11);
        BoardWinWait();
        BoardWinKill();
        omVibrate(GWSystem.player_curr, 12, 6, 6);
        HuAudFXPlay(0x45E);
        BoardModelMotionStartEndSet(lbl_1_bss_14[5], 0, 180);
        BoardModelMotionTimeSet(lbl_1_bss_14[5], 59.0f);
        var_f31 = 255.0f;
        temp_f29 = -5.1f;
        for (var_r31 = 0; var_r31 < 50; var_r31++) {
            BoardModelAlphaSet(lbl_1_bss_14[11], var_f31);
            var_f31 += temp_f29;
            HuPrcVSleep();
        }
        BoardModelAlphaSet(lbl_1_bss_14[11], 0);
        BoardModelAttrSet(lbl_1_bss_14[5], 0x40000002);
    } else {
        omVibrate(GWSystem.player_curr, 12, 6, 6);
        HuAudFXPlay(0x45D);
        BoardModelAttrReset(lbl_1_bss_14[5], 0x40000002);
        BoardModelMotionStartEndSet(lbl_1_bss_14[5], 0, 180);
        BoardModelMotionTimeSet(lbl_1_bss_14[5], 110.0f);
        var_f30 = 0.0f;
        temp_f28 = 3.642857f;
        for (var_r30 = 0; var_r30 < 70; var_r30++) {
            BoardModelAlphaSet(lbl_1_bss_14[11], var_f30);
            var_f30 += temp_f28;
            HuPrcVSleep();
        }
        BoardModelAlphaSet(lbl_1_bss_14[11], 0xFF);
        BoardModelMotionStartEndSet(lbl_1_bss_14[5], 0, 60);
    }
}

static void fn_1_1B98(s16 arg0) {
    BoardSpace *temp_r3;
    s32 i;

    for (i = 0; i < BoardSpaceCountGet(0); i++) {
        temp_r3 = BoardSpaceGet(0, i + 1);
        if (temp_r3->flag & 0x20) {
            if (arg0 != 0) {
                temp_r3->flag |= 0x04000000;
            } else {
                temp_r3->flag &= ~0x04000000;
            }
        }
    }
}

static void fn_1_1C2C(void) {
    s16 *var_r28;
    s32 i;

    if (lbl_1_bss_0->unk00 == 0) {
        BoardModelMotionStartEndSet(lbl_1_bss_14[3], 0, 80);
        BoardModelMotionTimeSet(lbl_1_bss_14[3], 0.0f);
        BoardModelVisibilitySet(lbl_1_bss_14[0], 1);
        BoardModelVisibilitySet(lbl_1_bss_14[1], 1);
        BoardModelVisibilitySet(lbl_1_bss_14[2], 1);
        fn_1_1B98(0);
        for (i = 0; i < 3; i++) {
            var_r28 = lbl_1_bss_3C[i]->user_data;
            BoardModelMotionStartEndSet(var_r28[2], 0, 20);
        }
    } else {
        BoardModelMotionStartEndSet(lbl_1_bss_14[3], 100, 100);
        BoardModelMotionTimeSet(lbl_1_bss_14[3], 100.0f);
        BoardModelVisibilitySet(lbl_1_bss_14[0], 0);
        BoardModelVisibilitySet(lbl_1_bss_14[1], 0);
        BoardModelVisibilitySet(lbl_1_bss_14[2], 0);
        fn_1_1B98(1);
        for (i = 0; i < 3; i++) {
            var_r28 = lbl_1_bss_3C[i]->user_data;
            BoardModelMotionStartEndSet(var_r28[2], 25, 25);
        }
    }
}

static void fn_1_1E60(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    s16 *temp_r31;
    s16 var_r29;
    s16 var_r28;
    s16 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    var_r29 = temp_r31[3];
    var_r28 = temp_r31[4];
    while (TRUE) {
        BoardSpacePosGet(0, var_r29, &sp14);
        BoardSpacePosGet(0, var_r28, &sp8);
        VECSubtract(&sp8, &sp14, &sp20);
        VECScale(&sp20, &sp20, 0.008333334f);
        temp_f31 = atan2d(sp8.x - sp14.x, sp8.z - sp14.z);
        BoardModelPosGet(temp_r31[1], &sp14);
        while (fn_1_1130(temp_r31[1], temp_f31, 2.5f) == 0) {
            if (lbl_1_bss_0->unk00 == 0) {
                BoardModelAlphaSet(temp_r31[1], 0xFF);
            } else {
                BoardModelAlphaSet(temp_r31[1], 0);
            }
            HuPrcVSleep();
        }
        for (i = 0; i < 120; i++) {
            if (lbl_1_bss_0->unk00 == 0) {
                BoardModelAlphaSet(temp_r31[1], 0xFF);
            } else {
                BoardModelAlphaSet(temp_r31[1], 0);
            }
            VECAdd(&sp14, &sp20, &sp14);
            BoardModelPosSetV(temp_r31[1], &sp14);
            HuPrcVSleep();
        }
        i = var_r29;
        var_r29 = var_r28;
        var_r28 = i;
    }
}

static void fn_1_2008(void) {
    s16 *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    BoardModelKill(temp_r31[1]);
    HuMemDirectFree(temp_r31);
}

static void fn_1_2044(void) {
    lbl_1_bss_38 = NULL;
}

void fn_1_2058(void) {
    s32 sp8;

    sp8 = GWSystem.player_curr;
    lbl_1_bss_38 = HuPrcChildCreate(fn_1_1618, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_38, fn_1_2044);
    while (lbl_1_bss_38) {
        HuPrcVSleep();
    }
}
