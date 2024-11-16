#include "REL/w04Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/msm.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"
#include "game/board/view.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "ext_math.h"

// Remove this and include frand.h header once we decide what to do with frandmod.
#define frand8() (((s32)frand() & 0xFF))

static void fn_1_62B0(void);
static void fn_1_68D8(void);
static void fn_1_6CF8(void);
static void fn_1_7300(void);
static void fn_1_757C(void);
static void fn_1_75D8(void);
static void fn_1_7888(void);
static void fn_1_8A60(void);
static void fn_1_98A0(void);
static void fn_1_9B34(void);
static void fn_1_9BDC(void);
static void fn_1_9C18(void);
static void fn_1_9EA8(void);
static s16 fn_1_9F50(void);
static void fn_1_A074(s16 arg0);

static s16 lbl_1_bss_282;
static s16 lbl_1_bss_280;
static s16 lbl_1_bss_27E;
static s16 lbl_1_bss_27C;
static Process *lbl_1_bss_278;
static s16 lbl_1_bss_274;
static s16 lbl_1_bss_272;
static s16 lbl_1_bss_270;
static Vec lbl_1_bss_240[4];
static Vec lbl_1_bss_210[4];
static s16 lbl_1_bss_13C[105];
static s16 lbl_1_bss_13A;
static s16 lbl_1_bss_134[3];
static s16 lbl_1_bss_114[4][4];
static Vec lbl_1_bss_108;
static Process *lbl_1_bss_104;
static AnimData *lbl_1_bss_100;

static char *lbl_1_data_3CC[] = {
    "picture", "picture2", "clock", "hari", "papa"
};

static s32 lbl_1_data_3E0[] = {
    DATA_MAKE_NUM(DATADIR_W04, 25),
    DATA_MAKE_NUM(DATADIR_W04, 26),
    DATA_MAKE_NUM(DATADIR_W04, 27),
    DATA_MAKE_NUM(DATADIR_W04, 28),
    -1
};

static s32 lbl_1_data_3F4[8] = {
    DATADIR_MARIOMOT,
    DATADIR_LUIGIMOT,
    DATADIR_PEACHMOT,
    DATADIR_YOSHIMOT,
    DATADIR_WARIOMOT,
    DATADIR_DONKEYMOT,
    DATADIR_DAISYMOT,
    DATADIR_WALUIGIMOT
};

static s32 lbl_1_data_414[] = {
    26, 28, 93, 12
};

static s16 lbl_1_data_424[][2] = {
    {  0, 0 }, {  6, 1 }, {  7, 3 }, { 12, 2 },
    { 15, 3 }, { 18, 4 }, { 20, 6 }, { 23, 5 },
    { 26, 6 }, { 28, 7 }, { 29, 8 }, { -1, 9 }
};

void fn_1_6024(void) {
    lbl_1_bss_27C = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 19), NULL, 0);
    BoardModelHookSet(lbl_1_bss_14[4], lbl_1_data_3CC[0], lbl_1_bss_27C);
    lbl_1_bss_280 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 20), NULL, 0);
    BoardModelHookSet(lbl_1_bss_14[4], lbl_1_data_3CC[2], lbl_1_bss_280);
    lbl_1_bss_27E = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 21), NULL, 0);
    BoardModelHookSet(lbl_1_bss_280, lbl_1_data_3CC[3], lbl_1_bss_27E);
    BoardModelAttrSet(lbl_1_bss_27E, 0x40000002);
    BoardModelAttrSet(lbl_1_bss_27C, 0x40000002);
    BoardModelMotionTimeSet(lbl_1_bss_27C, 20.0f);
    BoardModelAttrSet(lbl_1_bss_280, 0x40000003);
    BoardModelMotionSpeedSet(lbl_1_bss_27C, 0.5f);
    if (lbl_1_bss_0->unk01 != 0) {
        BoardModelMotionTimeSet(lbl_1_bss_280, 0.0f);
        BoardModelMotionSpeedSet(lbl_1_bss_280, 0.5f);
        BoardModelAttrReset(lbl_1_bss_280, 0x40000002);
        BoardModelMotionTimeSet(lbl_1_bss_27E, 120.0f * lbl_1_bss_0->unk01);
        BoardModelMotionTimeSet(lbl_1_bss_27C, 25.0f + 30.0f * lbl_1_bss_0->unk01);
    }
}

static void fn_1_62B0(void) {
    Vec sp14;
    Vec sp8;
    s32 var_r31;

    lbl_1_bss_0->unk01++;
    if (lbl_1_bss_0->unk01 == 3) {
        lbl_1_bss_272 = GWPlayer[lbl_1_bss_282].space_curr;
        var_r31 = BoardSpaceLinkFlagSearch(0, lbl_1_bss_272, 0x02000000);
        BoardPlayerMoveToAsync(lbl_1_bss_282, var_r31);
        while (GWPlayer[lbl_1_bss_282].moving) {
            HuPrcVSleep();
        }
        lbl_1_bss_274 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 24), lbl_1_data_3E0, 0);
        BoardModelMotionStart(lbl_1_bss_274, 4, 0);
        BoardModelAttrSet(lbl_1_bss_274, 0x40000002);
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[4]), lbl_1_data_3CC[4], &sp14);
        BoardModelPosSetV(lbl_1_bss_274, &sp14);
        sp8.x = sp8.y = sp8.z = 3.0f;
        BoardModelScaleSetV(lbl_1_bss_274, &sp8);
        BoardModelVisibilitySet(lbl_1_bss_274, 0);
    }
    BoardPlayerMotBlendSet(lbl_1_bss_282, 180, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_282)) {
        HuPrcVSleep();
    }
    fn_1_9C18();
    switch (lbl_1_bss_0->unk01) {
        case 1:
            HuAudFXPlay(0x4E);
            omVibrate(lbl_1_bss_282, 0x7FFF, 6, 6);
            BoardModelMotionTimeSet(lbl_1_bss_27C, 30.0f);
            BoardModelAttrReset(lbl_1_bss_27C, 0x40000002);
            HuPrcSleep(40);
            BoardModelAttrSet(lbl_1_bss_27C, 0x40000002);
            HuPadRumbleStop(GWPlayer[lbl_1_bss_282].port);
            BoardWinCreate(0, MAKE_MESSID(32, 26), -1);
            BoardWinWait();
            BoardWinKill();
            break;
        case 2:
            HuAudFXPlay(0x4E);
            omVibrate(lbl_1_bss_282, 0x7FFF, 6, 6);
            BoardModelMotionTimeSet(lbl_1_bss_27C, 60.0f);
            BoardModelAttrReset(lbl_1_bss_27C, 0x40000002);
            HuPrcSleep(40);
            BoardModelAttrSet(lbl_1_bss_27C, 0x40000002);
            HuPadRumbleStop(GWPlayer[lbl_1_bss_282].port);
            BoardWinCreate(0, MAKE_MESSID(32, 27), -1);
            BoardWinWait();
            BoardWinKill();
            break;
        case 3:
            BoardWinCreate(0, MAKE_MESSID(32, 28), -1);
            BoardWinWait();
            BoardWinKill();
            HuAudFXPlay(0x4E);
            sp14.x = 5.0f;
            sp14.y = 0.0f;
            sp14.z = 0.0f;
            sp8.x = 0.0f;
            sp8.y = 300.0f;
            sp8.z = -200.0f;
            BoardCameraMotionStartEx(lbl_1_bss_14[4], &sp14, &sp8, 1400.0f, -1.0f, 30);
            BoardCameraMotionWait();
            HuPrcSleep(9);
            HuAudFXPlay(0x464);
            BoardModelMotionTimeSet(lbl_1_bss_27C, 90.0f);
            BoardModelAttrReset(lbl_1_bss_27C, 0x40000002);
            HuPrcSleep(10);
            omVibrate(lbl_1_bss_282, 12, 4, 2);
            BoardModelVisibilitySet(lbl_1_bss_274, 1);
            BoardModelAttrReset(lbl_1_bss_274, 0x40000002);
            HuPrcSleep(39);
            BoardModelPosGet(lbl_1_bss_274, &sp14);
            BoardModelScaleGet(lbl_1_bss_274, &sp8);
            while (!BoardModelMotionEndCheck(lbl_1_bss_274)) {
                sp14.z += 15.0f;
                BoardModelPosSetV(lbl_1_bss_274, &sp14);
                HuPrcVSleep();
            }
            BoardModelMotionStart(lbl_1_bss_274, 1, 0x40000001);
            break;
    }
    if (lbl_1_bss_0->unk01 == 3) {
        fn_1_68D8();
        BoardCameraViewSet(1);
        BoardPlayerMoveToAsync(lbl_1_bss_282, lbl_1_bss_272);
        while (GWPlayer[lbl_1_bss_282].moving) {
            HuPrcVSleep();
        }
        BoardPlayerIdleSet(lbl_1_bss_282);
        BoardCameraMotionWait();
    } else {
        HuPrcSleep(29);
    }
    HuPrcEnd();
}

static void fn_1_68D8(void) {
    float var_f31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 i;

    BoardWinCreate(2, MAKE_MESSID(32, 3), 9);
    BoardWinWait();
    BoardWinKill();
    if (BoardPlayerCoinsGet(lbl_1_bss_282) < 15) {
        BoardWinCreate(2, MAKE_MESSID(32, 4), 9);
        BoardWinWait();
        BoardWinKill();
        BoardAudSeqFadeOut(1, 1000);
        while (msmMusGetStatus(1) != 0) {
            HuPrcVSleep();
        }
        BoardAudSeqPause(0, 0, 1000);
        fn_1_98A0();
        return;
    }
    do {
        var_r30 = 0;
        for (i = 0; i < 4; i++) {
            if (i != lbl_1_bss_282) {
                var_r30 += GWStarsGet(i);
            }
        }
        var_r28 = 0;
        for (i = 0; i < 4; i++) {
            if (i != lbl_1_bss_282) {
                var_r28 += BoardPlayerCoinsGet(i);
            }
        }
        BoardWinCreateChoice(4, MAKE_MESSID(32, 5), 9, 0);
        if (BoardPlayerCoinsGet(lbl_1_bss_282) < 150 || var_r30 == 0) {
            BoardWinChoiceDisable(1);
        }
        if (var_r28 == 0) {
            BoardWinChoiceDisable(0);
        }
        if (GWPlayer[lbl_1_bss_282].com) {
            if (var_r30 != 0 && BoardPlayerCoinsGet(lbl_1_bss_282) >= 150) {
                BoardComKeySetDown();
            } else {
                BoardComKeySetUp();
            }
        }
        BoardWinWait();
        BoardWinKill();
        var_r27 = BoardWinChoiceGet();
        var_r29 = 6;
        switch (var_r27) {
            case 1:
                var_r29 /= 4;
                for (i = 0; i < 135; i++) {
                    BoardPlayerCoinsAdd(lbl_1_bss_282, -1);
                    HuAudFXPlay(0xE);
                    HuPrcSleep(var_r29);
                }
                /* fallthrough */
            case 0:
                for (i = 0; i < 15; i++) {
                    BoardPlayerCoinsAdd(lbl_1_bss_282, -1);
                    HuAudFXPlay(0xE);
                    HuPrcSleep(var_r29);
                }
                HuAudFXPlay(0xF);
                HuAudFXPlay(0x4E);
                BoardWinCreate(2, MAKE_MESSID(32, 7), 9);
                BoardWinWait();
                BoardWinKill();
                var_f31 = 255.0f;
                for (i = 0; i < 60; i++) {
                    var_f31 -= 4.25f;
                    if (var_f31 < 0.0f) {
                        var_f31 = 0.0f;
                    }
                    BoardModelAlphaSet(lbl_1_bss_274, var_f31);
                    HuPrcVSleep();
                }
                BoardModelAlphaSet(lbl_1_bss_274, 0);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                WipeColorSet(0, 0, 0);
                while (WipeStatGet() != 0) {
                    HuPrcVSleep();
                }
                BoardModelAlphaSet(lbl_1_bss_274, 0xFF);
                if (var_r27 == 0) {
                    fn_1_7888();
                } else {
                    fn_1_8A60();
                }
                break;
            case -1:
            case 2:
                BoardWinCreate(2, MAKE_MESSID(32, 6), 9);
                BoardWinWait();
                BoardWinKill();
                BoardAudSeqFadeOut(1, 1000);
                while (msmMusGetStatus(1) != 0) {
                    HuPrcVSleep();
                }
                BoardAudSeqPause(0, 0, 1000);
                break;
            case 3:
                BoardViewMapExec(lbl_1_bss_282);
                break;
        }
    } while (var_r27 == 3);
    fn_1_98A0();
}

static void fn_1_6CF8(void) {
    Vec sp10;
    s16 sp8[4];
    s16 var_r29;
    s16 var_r28;
    s32 temp_r27;
    s32 var_r30;
    s32 i;

    var_r29 = 0;
    for (i = 0; i < 4; i++) {
        if (i != lbl_1_bss_282) {
            BoardPlayerPosGet(i, &lbl_1_bss_240[i]);
            BoardPlayerRotGet(i, &lbl_1_bss_210[i]);
            sp8[var_r29++] = i;
        }
    }
    BoardModelHideSetAll(1);
    BoardSpaceHide(1);
    for (i = 0; i < 4; i++) {
        BoardStatusShowSet(i, 0);
    }
    BoardLightResetExec();
    lbl_1_bss_270 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 22), NULL, 0);
    BoardModelAttrSet(lbl_1_bss_270, 0x40000001);
    sp10.y = 0.0f;
    for (i = -1; i < 2; i++) {
        sp10.z = 220.0f + -20.0f * abs(i);
        sp10.x = 150.0f * i;
        BoardPlayerPosSetV(sp8[i + 1], &sp10);
        BoardPlayerRotYSet(sp8[i + 1], 180.0f);
        BoardModelVisibilitySet(BoardPlayerModelGet(sp8[i + 1]), 1);
        temp_r27 = lbl_1_data_3F4[GWPlayer[sp8[i + 1]].character];
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            lbl_1_bss_114[sp8[i + 1]][var_r30] = BoardPlayerMotionCreate(sp8[i + 1], temp_r27 | lbl_1_data_414[var_r30]);
        }
        BoardPlayerMotionStart(sp8[i + 1], lbl_1_bss_114[sp8[i + 1]][0], 0x40000001);
    }
    BoardModelPosGet(lbl_1_bss_274, &lbl_1_bss_108);
    BoardModelVisibilitySet(lbl_1_bss_274, 1);
    sp10.x = sp10.z = 0.0f;
    sp10.y = 800.0f;
    BoardModelPosSetV(lbl_1_bss_274, &sp10);
    sp10.x = sp10.y = sp10.z = 4.0f;
    BoardModelScaleSetV(lbl_1_bss_274, &sp10);
    BoardModelMotionStart(lbl_1_bss_274, 0, 0);
    BoardCameraMoveSet(0);
    BoardCameraTargetModelSet(lbl_1_bss_270);
    BoardCameraOffsetSet(0.0f, 200.0f, 0.0f);
    BoardCameraXRotZoomSet(1600.0f, -5.0f);
    lbl_1_bss_104 = HuPrcChildCreate(fn_1_75D8, 0x2003, 0x1000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_104, fn_1_757C);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x78);
    for (i = 0; i < 3; i++) {
        BoardPlayerModelAttrReset(sp8[i], 0x40000001);
        BoardPlayerMotionShiftSet(sp8[i], lbl_1_bss_114[sp8[i]][1], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    }
    BoardModelPosGet(lbl_1_bss_274, &sp10);
    var_r28 = 10;
    for (i = 0; i < 60; i++) {
        if (--var_r28 == 0) {
            HuAudFXPlay(0x4E);
            for (var_r30 = 0; var_r30 < 3; var_r30++) {
                HuAudPlayerVoicePlay(sp8[var_r30], 0x12F);
            }
        }
        sp10.y -= 10.0f;
        BoardModelPosSetV(lbl_1_bss_274, &sp10);
        HuPrcVSleep();
    }
    for (i = 0; i < 3; i++) {
        BoardPlayerMotionShiftSet(sp8[i], 1, 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    }
}

static void fn_1_7300(void) {
    Vec sp14;
    Vec sp8;
    s32 i;
    s32 j;

    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardModelKill(lbl_1_bss_270);
    for (i = 0; i < 4; i++) {
        if (i != lbl_1_bss_282) {
            BoardPlayerPosSetV(i, &lbl_1_bss_240[i]);
            BoardPlayerRotSetV(i, &lbl_1_bss_210[i]);
            for (j = 0; j < 4; j++) {
                BoardPlayerMotionKill(i, lbl_1_bss_114[i][j]);
            }
            BoardPlayerMotionStart(i, 1, 0x40000001);
        }
    }
    HuPrcKill(lbl_1_bss_104);
    HuPrcVSleep();
    BoardModelHideSetAll(0);
    BoardSpaceHide(0);
    for (i = 0; i < 4; i++) {
        BoardStatusShowSet(i, 1);
    }
    BoardLightSetExec();
    BoardCameraMoveSet(0);
    sp14.x = 5.0f;
    sp14.y = 0.0f;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 220.0f;
    sp8.z = -200.0f;
    BoardCameraMotionStartEx(lbl_1_bss_14[4], &sp14, &sp8, 1400.0f, -1.0f, 0);
    BoardCameraMoveSet(1);
    BoardModelMotionStart(lbl_1_bss_274, 1, 0x40000001);
    sp8.x = sp8.y = sp8.z = 3.0f;
    BoardModelScaleSetV(lbl_1_bss_274, &sp8);
    BoardModelPosSetV(lbl_1_bss_274, &lbl_1_bss_108);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
}

static void fn_1_757C(void) {
    s16 temp_r31;
    s16 temp_r30;

    temp_r31 = ((s32) HuPrcCurrentGet()->user_data) >> 16;
    temp_r30 = (u16) HuPrcCurrentGet()->user_data;
    Hu3DGLightKill(temp_r31);
    Hu3DGLightKill(temp_r30);
}

static void fn_1_75D8(void) {
    Vec sp1C;
    Vec sp10;
    GXColor spC;
    float sp8;
    float var_f31;
    s16 temp_r3;
    s16 temp_r3_2;

    temp_r3 = Hu3DGLightCreate(0.0f, 1000.0f, 0.0f, 0.0f, 0.9f, -0.1f, 0xFF, 0x64, 0xC8);
    Hu3DGLightInfinitytSet(temp_r3);
    Hu3DGLightStaticSet(temp_r3, 1);
    spC.r = 0xCD;
    spC.g = 0x32;
    spC.b = 0x96;
    sp1C.x = sp1C.y = sp1C.z = 0.0f;
    sp10.x = 0.0f;
    sp10.y = -1.0f;
    sp10.z = 0.0f;
    temp_r3_2 = Hu3DGLightCreateV(&sp1C, &sp10, &spC);
    Hu3DGLightInfinitytSet(temp_r3_2);
    Hu3DGLightStaticSet(temp_r3_2, 1);
    HuPrcCurrentGet()->user_data = (void*) (((temp_r3 << 16) & 0xFFFF0000) | (temp_r3_2 & 0xFFFF));
    var_f31 = 0.0f;
    sp8 = var_f31;
    while (TRUE) {
        sp10.x = cosd(var_f31 - 180.0f);
        sp10.y = sind(var_f31);
        sp10.z = cosd(var_f31) * sind(var_f31);
        var_f31 += 3.0f + 6.0f * frand8() * 0.003921569f;
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        Hu3DGLightPosSetV(temp_r3_2, &sp1C, &sp10);
        HuPrcVSleep();
    }
}

static void fn_1_7888(void) {
    Vec sp8F8[105];
    Vec sp40C[105];
    float sp268[105];
    float spC4[105];
    u8 sp58[105];
    Vec sp4C;
    float sp40[3] = { 270.0f, 0.0f, 90.0f };
    float sp28[2];
    float var_f31;
    char sp30[16];
    s16 sp20[4];
    s16 sp18[4];
    s16 sp10[4];
    s16 sp8[4];
    u16 var_r26;
    u16 var_r24;
    s16 var_r28;
    s16 var_r27;
    s16 var_r22;
    s16 var_r21;
    s16 var_r20;
    s16 var_r23;
    s32 var_r25;
    s32 i;
    s32 j;
    s32 k;

    fn_1_6CF8();
    HuWinMesMaxSizeGet(1, sp28, MAKE_MESSID(32, 8));
    var_r21 = HuWinCreate(-10000.0f, 32.0f, sp28[0], sp28[1], 1);
    HuWinMesSet(var_r21, MAKE_MESSID(32, 8));
    HuWinMesSpeedSet(var_r21, 0);
    BoardModelMotionStart(lbl_1_bss_274, 3, 0x40000001);
    for (i = 0; i < 4; i++) {
        sp20[i] = 0;
        sp18[i] = 0;
    }
    BoardModelPosGet(lbl_1_bss_274, &sp4C);
    var_r20 = 48;
    for (i = 0; i < 120; i++) {
        if (--var_r20 == 0) {
            var_r20 = 48;
            for (j = 0; j < 4; j++) {
                if (j != lbl_1_bss_282) {
                    HuAudPlayerVoicePlay(j, 0x130);
                }
            }
        }
        for (j = 0; j < 4; j++) {
            if (j == lbl_1_bss_282) {
                continue;
            }
            if (GWPlayer[j].com) {
                switch (GWPlayer[j].diff) {
                    case 0:
                        var_r28 = 12;
                        break;
                    case 1:
                        var_r28 = 22;
                        break;
                    case 2:
                        var_r28 = 50;
                        break;
                    case 3:
                        var_r28 = 1000;
                        break;
                }
                if (frandmod(100) < var_r28) {
                    var_r26 = 0x100;
                } else {
                    var_r26 = 0;
                }
            } else {
                var_r24 = GWPlayer[j].port;
                var_r26 = HuPadBtnDown[var_r24];
            }
            if (var_r26 & 0x100) {
                sp20[j]++;
            }
            if (sp18[j] != 0) {
                if (BoardPlayerMotionEndCheck(j)) {
                    sp18[j] = 0;
                    BoardPlayerMotionStart(j, 1, 0x40000001);
                }
            } else if (var_r26 & 0x100) {
                sp18[j] = 1;
                BoardPlayerMotionStart(j, lbl_1_bss_114[j][2], 0);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        if (i == lbl_1_bss_282) {
            continue;
        }
        BoardPlayerMotionStart(i, lbl_1_bss_114[i][3], 0);
        OSReport("%d:%dhit  ", i, sp20[i]);
        omVibrate(i, 12, 4, 2);
    }
    OSReport("\n");
    HuWinKill(var_r21);
    var_r27 = 0;
    var_r23 = GWSystem.turn;
    if (var_r23 <= 5) {
        var_r25 = 15;
    } else if (var_r23 <= 15) {
        var_r25 = 25;
    } else if (var_r23 <= 25) {
        var_r25 = 27;
    } else if (var_r23 <= 35) {
        var_r25 = 30;
    } else if (var_r23 <= 45) {
        var_r25 = 32;
    } else {
        var_r25 = 35;
    }
    for (i = 0; i < 4; i++) {
        if (i == lbl_1_bss_282) {
            continue;
        }
        j = 0;
        while (TRUE) {
            if (lbl_1_data_424[j][0] == -1) {
                sp8[i] = lbl_1_data_424[j][1];
                break;
            } else if (sp20[i] <= lbl_1_data_424[j][0]) {
                sp8[i] = lbl_1_data_424[j][1];
                break;
            }
            j++;
        }
        sp10[i] = var_r25 - sp8[i];
        if (BoardPlayerCoinsGet(i) < sp10[i]) {
            sp10[i] = BoardPlayerCoinsGet(i);
        }
        var_r27 += sp10[i];
        BoardPlayerCoinsAdd(i, -sp10[i]);
        OSReport("%d:%dlost  ", i, sp10[i]);
    }
    OSReport("\n");
    for (i = 0; i < var_r27; i++) {
        lbl_1_bss_13C[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), 0, 1);
        BoardModelVisibilitySet(lbl_1_bss_13C[i], 0);
        sp58[i] = 0;
    }
    for (i = 0; i < 10; i++) {
        sp4C.z += 21.0f - i;
        BoardModelPosSetV(lbl_1_bss_274, &sp4C);
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        if (i == lbl_1_bss_282) {
            continue;
        }
        omVibrate(i, 12, 4, 2);
        HuAudPlayerVoicePlay(i, 0x131);
    }
    HuAudFXPlay(0x4E);
    var_r28 = 0;
    var_r24 = var_r27;
    while (TRUE) {
        if (var_r28 == 0) {
            var_r22 = 0;
            for (i = 0; i < 4; i++) {
                if (i == lbl_1_bss_282) {
                    continue;
                }
                for (j = 0; j < 3; j++) {
                    if (sp10[i] == 0) {
                        continue;
                    }
                    sp10[i]--;
                    var_r24--;
                    for (k = 0; k < var_r27; k++) {
                        if (sp58[k] == 0) {
                            break;
                        }
                    }
                    if (k == var_r27) {
                        OSReport("\x82\xB1\x82\xA2\x82\xF1\x82\xAA\x8F\x6F\x82\xB9\x82\xC8\x82\xA2 total %d\n", var_r27);
                        while (TRUE) {
                            HuPrcVSleep();
                        }
                    }
                    HuAudFXPlay(0x12);
                    sp58[k] = 1;
                    BoardPlayerPosGet(i, &sp8F8[k]);
                    sp8F8[k].y += 180.0f;
                    BoardModelVisibilitySet(lbl_1_bss_13C[k], 1);
                    BoardModelPosSetV(lbl_1_bss_13C[k], &sp8F8[k]);
                    sp40C[k].x = 10.0 * sind(sp40[var_r22] - 20.0f + 40.0f * j);
                    sp40C[k].z = 10.0 * cosd(sp40[var_r22] - 20.0f + 40.0f * j);
                    sp40C[k].y = 6.0f + 6.0f * frand8() * 0.003921569f;
                    sp268[k] = 0.0f;
                    spC4[k] = 360.0f * frand8() * 0.003921569f;
                }
                var_r22++;
            }
            var_r28 = 8;
        } else {
            var_r28--;
        }
        var_r26 = 0;
        for (i = 0; i < var_r27; i++) {
            if (sp58[i] == 0) {
                continue;
            }
            var_r26++;
            sp8F8[i].x += sp40C[i].x;
            sp8F8[i].z += sp40C[i].z;
            sp8F8[i].y += sp40C[i].y - sp268[i] * sp268[i] * 0.25f * 0.075f;
            BoardModelPosSetV(lbl_1_bss_13C[i], &sp8F8[i]);
            BoardModelRotYSet(lbl_1_bss_13C[i], spC4[i]);
            sp268[i] += 1.0f;
            spC4[i] += 12.0f;
            if (spC4[i] >= 360.0f) {
                spC4[i] -= 360.0f;
            }
            if (sp8F8[i].y < -450.0f) {
                sp58[i] = 0;
                BoardModelVisibilitySet(lbl_1_bss_13C[i], 0);
            }
        }
        if (var_r26 == 0 && var_r24 == 0) {
            break;
        }
        HuPrcVSleep();
    }
    fn_1_7300();
    sprintf(sp30, "%d", var_r27);
    BoardWinCreate(2, MAKE_MESSID(32, 9), 9);
    BoardWinInsertMesSet(MAKE_MESSID_PTR(sp30), 0);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerMotBlendSet(lbl_1_bss_282, 0, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_282)) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(lbl_1_bss_282);
    BoardPlayerPosGet(lbl_1_bss_282, &sp4C);
    for (i = 0; i < var_r27; i++) {
        BoardModelVisibilitySet(lbl_1_bss_13C[i], 1);
        sp8F8[i].x = sp4C.x - 25.0f + 50.0f * frand8() * 0.003921569f;
        sp8F8[i].y = sp4C.y + 1200.0f + 130.0f * i + 60.0f * frand8() * 0.003921569f;
        sp8F8[i].z = sp4C.z - 25.0f + 50.0f * frand8() * 0.003921569f;
        BoardModelPosSetV(lbl_1_bss_13C[i], &sp8F8[i]);
    }
    var_f31 = -4.0f;
    var_r28 = 0;
    while (TRUE) {
        for (i = 0; i < var_r27; i++) {
            if (i < var_r28) {
                continue;
            }
            sp8F8[i].y += var_f31;
            spC4[i] += 45.0f;
            BoardModelPosSetV(lbl_1_bss_13C[i], &sp8F8[i]);
            BoardModelRotYSet(lbl_1_bss_13C[i], spC4[i]);
            if (sp8F8[i].y <= sp4C.y + 180.0f) {
                CharModelCoinEffectCreate(1, &sp8F8[i]);
                BoardModelVisibilitySet(lbl_1_bss_13C[i], 0);
                var_r28++;
                BoardPlayerCoinsAdd(lbl_1_bss_282, 1);
                HuAudFXPlay(7);
                omVibrate(lbl_1_bss_282, 12, 6, 6);
            }
        }
        var_f31 *= 1.05f;
        if (var_f31 < -40.0f) {
            var_f31 = -40.0f;
        }
        if (var_r28 == var_r27) {
            BoardPlayerMotionShiftSet(lbl_1_bss_282, 7, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            break;
        }
        HuPrcVSleep();
    }
    while (!BoardPlayerMotionEndCheck(lbl_1_bss_282)) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    for (i = 0; i < var_r27; i++) {
        BoardModelKill(lbl_1_bss_13C[i]);
    }
    BoardPlayerMotBlendSet(lbl_1_bss_282, 0xB4, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_282)) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(lbl_1_bss_282);
    BoardWinCreate(2, MAKE_MESSID(32, 10), 9);
    BoardWinWait();
    BoardWinKill();
    BoardAudSeqFadeOut(1, 1000);
    while (msmMusGetStatus(1) != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 1000);
}

static void fn_1_8A60(void) {
    Vec sp7C[3];
    Vec sp58[3];
    Vec sp4C;
    Vec sp40;
    float sp34[3];
    float sp28[3];
    float sp1C[3] = { 315.0f, 0.0f, 45.0f };
    char sp10[12];
    float var_f31;
    float var_f30;
    s16 sp8[4];
    s16 var_r30;
    s32 temp_r27;
    s32 var_r28;
    s32 var_r29;
    s32 i;

    fn_1_6CF8();
    lbl_1_bss_13A = 0;
    BoardModelMotionStart(lbl_1_bss_274, 3, 0x40000001);
    BoardModelPosGet(lbl_1_bss_274, &sp4C);
    for (i = 0; i < 120; i++) {
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        if (i == lbl_1_bss_282) {
            continue;
        }
        BoardPlayerMotionStart(i, lbl_1_bss_114[i][3], 0);
        omVibrate(i, 12, 4, 2);
    }
    var_r29 = 0;
    for (i = 0; i < 4; i++) {
        if (i == lbl_1_bss_282) {
            continue;
        }
        if (GWStarsGet(i) > 0) {
            sp8[i] = 1;
            var_r29++;
        } else {
            sp8[i] = 0;
        }
        BoardPlayerStarsAdd(i, -sp8[i]);
    }
    OSReport("Total Star %d\n", var_r29);
    for (i = 0; i < var_r29; i++) {
        lbl_1_bss_13C[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 8), NULL, 0);
        BoardModelAttrSet(lbl_1_bss_13C[i], 0x40000002);
        BoardModelVisibilitySet(lbl_1_bss_13C[i], 0);
    }
    for (i = 0; i < 10; i++) {
        sp4C.z += 21.0f - i;
        BoardModelPosSetV(lbl_1_bss_274, &sp4C);
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        if (i == lbl_1_bss_282) {
            continue;
        }
        omVibrate(i, 12, 4, 2);
        HuAudPlayerVoicePlay(i, 0x131);
    }
    HuAudFXPlay(0x4E);
    var_r30 = 0;
    for (i = 0; i < 4; i++) {
        if (i == lbl_1_bss_282 || sp8[i] == 0) {
            continue;
        }
        BoardPlayerPosGet(i, &sp7C[var_r30]);
        sp7C[var_r30].y += 180.0f;
        sp34[var_r30] = 0.0f;
        sp58[var_r30].x = 10.0 * sind(sp1C[var_r30]);
        sp58[var_r30].z = 10.0 * cosd(sp1C[var_r30]);
        sp58[var_r30].y = 6.0f + 6.0f * frand8() * 0.003921569f;
        sp34[var_r30] = 360.0f * frand8() * 0.003921569f;
        sp28[var_r30] = 0.0f;
        BoardModelVisibilitySet(lbl_1_bss_13C[var_r30], 1);
        lbl_1_bss_134[var_r30] = fn_1_9F50();
        var_r30++;
    }
    while (TRUE) {
        var_r30 = 0;
        for (i = 0; i < var_r29; i++) {
            sp7C[i].x += sp58[i].x;
            sp7C[i].z += sp58[i].z;
            sp7C[i].y += sp58[i].y - sp28[i] * sp28[i] * 0.25f * 0.075f;
            BoardModelPosSetV(lbl_1_bss_13C[i], &sp7C[i]);
            BoardModelRotYSet(lbl_1_bss_13C[i], sp34[i]);
            sp28[i] += 1.0f;
            sp34[i] += 12.0f;
            if (sp34[i] >= 360.0f) {
                sp34[i] -= 360.0f;
            }
            if (sp7C[i].y < -500.0f) {
                BoardModelVisibilitySet(lbl_1_bss_13C[i], 0);
                var_r30++;
            }
            Hu3DParManPosSet(lbl_1_bss_134[i], sp7C[i].x, sp7C[i].y + -70.0f, sp7C[i].z);
        }
        if (var_r30 == var_r29) {
            break;
        }
        HuPrcVSleep();
    }
    fn_1_7300();
    #if VERSION_NTSC
    sprintf(sp10, "%d", var_r29);
    BoardWinCreate(2, MAKE_MESSID(32, 11), 9);
    BoardWinInsertMesSet(MAKE_MESSID_PTR(sp10), 0);
    #else
    BoardWinCreate(2, MAKE_MESSID(32, 11), 9);
    #endif
    BoardWinWait();
    BoardWinKill();
    BoardAudSeqFadeOut(1, 1000);
    BoardPlayerMotBlendSet(lbl_1_bss_282, 0, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_282)) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(lbl_1_bss_282);
    BoardPlayerPosGet(lbl_1_bss_282, &sp4C);
    for (i = 0; i < var_r29; i++) {
        BoardModelVisibilitySet(lbl_1_bss_13C[i], 1);
        sp7C[i] = sp4C;
        sp7C[i].y += 600.0f;
        BoardModelPosSetV(lbl_1_bss_13C[i], &sp7C[i]);
        sp34[i] = 0.0f;
        BoardModelRotYSet(lbl_1_bss_13C[i], sp34[i]);
    }
    for (i = 0; i < var_r29; i++) {
        var_f31 = -4.0f;
        HuAudFXPlay(0x338);
        HuAudFXPlay(0x353);
        while (TRUE) {
            sp7C[i].y += var_f31;
            BoardModelPosSetV(lbl_1_bss_13C[i], &sp7C[i]);
            Hu3DParManPosSet(lbl_1_bss_134[i], sp7C[i].x, sp7C[i].y + -70.0f, sp7C[i].z);
            if (sp7C[i].y <= sp4C.y + 270.0f) {
                sp7C[i].y = sp4C.y + 270.0f;
                BoardModelPosSetV(lbl_1_bss_13C[i], &sp7C[i]);
                Hu3DParManPosSet(lbl_1_bss_134[i], sp7C[i].x, sp7C[i].y + -70.0f, sp7C[i].z);
                BoardModelAttrReset(lbl_1_bss_13C[i], 0x40000002);
                while (BoardModelMotionTimeGet(lbl_1_bss_13C[i]) < BoardModelMotionMaxTimeGet(lbl_1_bss_13C[i]) - 10.0f) {
                    HuPrcVSleep();
                }
                var_f31 = -5.0f;
                var_f30 = 1.0f;
                HuAudFXPlay(0x339);
                for (var_r28 = 0; var_r28 < 30; var_r28++) {
                    var_f30 -= 0.033333335f;
                    sp40.x = sp40.y = sp40.z = var_f30;
                    BoardModelScaleSetV(lbl_1_bss_13C[i], &sp40);
                    sp7C[i].y += var_f31;
                    BoardModelPosSetV(lbl_1_bss_13C[i], &sp7C[i]);
                    sp34[i] += 25.0f;
                    BoardModelRotYSet(lbl_1_bss_13C[i], sp34[i]);
                    Hu3DParManPosSet(lbl_1_bss_134[i], sp7C[i].x, sp7C[i].y + -70.0f, sp7C[i].z);
                    HuPrcVSleep();
                }
                omVibrate(lbl_1_bss_282, 12, 0xC, 0);
                BoardPlayerStarsAdd(lbl_1_bss_282, 1);
                BoardModelVisibilitySet(lbl_1_bss_13C[i], 0);
                fn_1_A074(lbl_1_bss_134[i]);
                break;
            }
            var_f31 *= 1.05f;
            if (var_f31 < -20.0f) {
                var_f31 = -20.0f;
            }
            HuPrcVSleep();
        }
    }
    temp_r27 = HuAudSStreamPlay(6);
    BoardPlayerMotionShiftSet(lbl_1_bss_282, 7, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    while (!BoardPlayerMotionEndCheck(lbl_1_bss_282)) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    while (HuAudSStreamStatGet(temp_r27) != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 1000);
    for (i = 0; i < var_r29; i++) {
        BoardModelKill(lbl_1_bss_13C[i]);
    }
    BoardPlayerMotBlendSet(lbl_1_bss_282, 0xB4, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_282)) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(lbl_1_bss_282);
    BoardWinCreate(2, MAKE_MESSID(32, 10), 9);
    BoardWinWait();
    BoardWinKill();
}

static void fn_1_98A0(void) {
    Vec sp14;
    Vec sp8;
    float var_f30;
    float var_f31;
    s32 i;

    BoardModelPosGet(lbl_1_bss_274, &sp14);
    var_f30 = BoardModelRotYGet(lbl_1_bss_274);
    BoardModelMotionShiftSet(lbl_1_bss_274, 2, 0.0f, 25.0f, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 25; i++) {
        var_f30 += 7.2f;
        BoardModelRotYSet(lbl_1_bss_274, var_f30);
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_bss_274, 180.0f);
    BoardModelMotionTimeSet(lbl_1_bss_27C, 0.0f);
    BoardModelAttrReset(lbl_1_bss_27C, 0x40000002);
    HuAudFXPlay(0x464);
    HuAudFXPlay(0x4E);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[4]), lbl_1_data_3CC[4], &sp8);
    var_f31 = 255.0f;
    while (TRUE) {
        sp14.z -= 10.0f;
        if (sp14.z <= sp8.z + 200.0f) {
            var_f31 -= 20.0f;
            if (var_f31 <= 0.0f) {
                break;
            }
            BoardModelAlphaSet(lbl_1_bss_274, var_f31);
        }
        BoardModelPosSetV(lbl_1_bss_274, &sp14);
        if (BoardModelMotionTimeGet(lbl_1_bss_27C) >= 20.0f) {
            BoardModelAttrSet(lbl_1_bss_27C, 0x40000002);
        }
        HuPrcVSleep();
    }
    BoardModelAlphaSet(lbl_1_bss_274, 0);
    BoardModelMotionTimeSet(lbl_1_bss_27C, 20.0f);
    BoardModelAttrSet(lbl_1_bss_27C, 0x40000002);
    fn_1_9B34();
}

static void fn_1_9B34(void) {
    BoardModelKill(lbl_1_bss_274);
    lbl_1_bss_0->unk01 = 0;
    BoardModelMotionTimeSet(lbl_1_bss_280, 0.0f);
    BoardModelAttrSet(lbl_1_bss_280, 0x40000002);
    BoardModelMotionTimeSet(lbl_1_bss_27E, 0.0f);
    BoardModelAttrSet(lbl_1_bss_280, 0x40000002);
}

static void fn_1_9BDC(void) {
    HuPrcSleep(240);
    BoardMusStart(1, 0x1F, 0x7F, 0);
    HuPrcEnd();
}

static void fn_1_9C18(void) {
    Vec sp14;
    Vec sp8;
    s32 temp_r31;

    sp14.x = -150.0f;
    sp14.y = 0.0f;
    sp14.z = 120.0f;
    sp8.x = -45.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_14[4], &sp8, &sp14, 2300.0f, -1.0f, 30);
    BoardCameraMotionWait();
    if (lbl_1_bss_0->unk01 == 1) {
        BoardModelMotionTimeSet(lbl_1_bss_280, 0.0f);
        BoardModelMotionSpeedSet(lbl_1_bss_280, 0.5f);
        BoardModelAttrReset(lbl_1_bss_280, 0x40000002);
    }
    HuAudFXPlay(0x461);
    temp_r31 = HuAudFXPlay(0x462);
    BoardModelAttrReset(lbl_1_bss_27E, 0x40000002);
    HuPrcSleep(110);
    BoardModelAttrSet(lbl_1_bss_27E, 0x40000002);
    HuAudFXStop(temp_r31);
    switch (lbl_1_bss_0->unk01) {
        case 1:
        case 2:
            HuAudFXPlay(0x46A);
            break;
        case 3:
            HuAudFXPlay(0x46B);
            BoardAudSeqPause(0, 1, 1000);
            HuPrcChildCreate(fn_1_9BDC, 0x2003, 0x1000, 0, boardMainProc);
            break;
    }
    HuPrcSleep(9);
    sp14.x = -150.0f;
    sp14.y = 250.0f;
    sp14.z = 120.0f;
    sp8.x = -5.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_14[4], &sp8, &sp14, 1800.0f, -1.0f, 30);
    BoardCameraMotionWait();
    HuPrcSleep(30);
}

static void fn_1_9EA8(void) {
    lbl_1_bss_278 = NULL;
}

void fn_1_9EBC(void) {
    lbl_1_bss_282 = GWSystem.player_curr;
    lbl_1_bss_278 = HuPrcCreate(fn_1_62B0, 0x2004, 0x2000, 0);
    HuPrcDestructorSet2(lbl_1_bss_278, fn_1_9EA8);
    while (lbl_1_bss_278) {
        HuPrcVSleep();
    }
    BoardEventFlagReset();
}

static HsfanimStruct00 lbl_1_data_49C = {
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
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0x40, 0xFF },
        { 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 }
    },
    {
        { 0xFF, 0x80, 0x80, 0x00 },
        { 0xFF, 0x40, 0x20, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 }
    }
};

static s16 fn_1_9F50(void) {
    void *var_r29;
    s16 temp_r3;
    s16 temp_r3_2;

    if (lbl_1_bss_100 == NULL) {
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 1), MEMORY_DEFAULT_NUM, HEAP_DATA);
        lbl_1_bss_100 = HuSprAnimRead(var_r29);
        HuSprAnimLock(lbl_1_bss_100);
    }
    temp_r3 = Hu3DParManCreate(lbl_1_bss_100, 0x64, &lbl_1_data_49C);
    Hu3DParManAttrSet(temp_r3, 0x64);
    Hu3DParManRotSet(temp_r3, 90.0f, 0.0f, 0.0f);
    temp_r3_2 = Hu3DParManModelIDGet(temp_r3);
    Hu3DParticleBlendModeSet(temp_r3_2, 1);
    Hu3DModelLayerSet(temp_r3_2, 2);
    lbl_1_bss_13A++;
    return temp_r3;
}

static void fn_1_A074(s16 arg0) {
    if (arg0 == -1) {
        return;
    }
    Hu3DParManKill(arg0);
    if (--lbl_1_bss_13A == 0) {
        HuSprAnimKill(lbl_1_bss_100);
        lbl_1_bss_100 = NULL;
    }
}
