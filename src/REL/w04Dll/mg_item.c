#include "REL/w04Dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/board/audio.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/window.h"

#include "dolphin.h"
#include "ext_math.h"

static void fn_1_A71C(void);
static void fn_1_A7E8(void);
static void fn_1_C388(ModelData *model, ParticleData *particle, Mtx matrix);

static s16 lbl_1_bss_2AC;
static s16 lbl_1_bss_2A6[3];
static s16 lbl_1_bss_29E[4];
static s16 lbl_1_bss_298[3];
static float lbl_1_bss_294;
static s32 lbl_1_bss_290_pad;
static s32 lbl_1_bss_28C;
static AnimData *lbl_1_bss_288;

static char *lbl_1_data_51C[] = {
    "item1", "item2", "item3",
    "switch1", "switch2", "switch3"
};

static s32 lbl_1_data_534[] = {
    0x00000466,
    0x00000467,
    0x00000468
};

static s32 lbl_1_data_540[] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 109),
    DATA_MAKE_NUM(DATADIR_BOARD, 110),
    DATA_MAKE_NUM(DATADIR_BOARD, 111),
    DATA_MAKE_NUM(DATADIR_BOARD, 112),
    DATA_MAKE_NUM(DATADIR_BOARD, 113),
    DATA_MAKE_NUM(DATADIR_BOARD, 114),
    DATA_MAKE_NUM(DATADIR_BOARD, 115),
    DATA_MAKE_NUM(DATADIR_BOARD, 116),
    DATA_MAKE_NUM(DATADIR_BOARD, 118),
    DATA_MAKE_NUM(DATADIR_BOARD, 119),
    DATA_MAKE_NUM(DATADIR_BOARD, 120),
    DATA_MAKE_NUM(DATADIR_BOARD, 121),
    DATA_MAKE_NUM(DATADIR_BOARD, 122),
    DATA_MAKE_NUM(DATADIR_BOARD, 123),
    DATA_MAKE_NUM(DATADIR_W02, 24),
    DATA_MAKE_NUM(DATADIR_W02, 25),
    DATA_MAKE_NUM(DATADIR_W02, 26),
    -1
};

void fn_1_A0F8(void) {
    Vec sp8;
    s32 i;

    BoardModelAttrSet(lbl_1_bss_14[6], 0x40000002);
    for (i = 0; i < 3; i++) {
        lbl_1_bss_29E[i] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 13), NULL, 1);
        BoardModelHookSet(lbl_1_bss_14[6], lbl_1_data_51C[i + 3], lbl_1_bss_29E[i]);
        BoardModelAttrSet(lbl_1_bss_29E[i], 0x40000002);
    }
    BoardModelPosGet(lbl_1_bss_14[6], &sp8);
    lbl_1_bss_294 = sp8.y;
}

void fn_1_A1F0(void) {
    Vec sp38[3];
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    s16 temp_r29;
    s32 var_r30;
    s32 i;

    lbl_1_bss_2AC = GWSystem.player_curr;
    temp_r29 = BoardModelMotionCreate(lbl_1_bss_14[10], DATA_MAKE_NUM(DATADIR_BGUEST, 25));
    HuPrcSleep(60);
    var_f31 = 0.0f;
    for (i = 0; i < 30; i++) {
        var_f31 += 3.0f;
        BoardModelRotYSet(lbl_1_bss_14[10], var_f31);
        HuPrcVSleep();
    }
    BoardModelMotionStart(lbl_1_bss_14[10], temp_r29, 0);
    for (i = 0; i < 3; i++) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[6]), lbl_1_data_51C[i], &sp38[i]);
    }
    while (TRUE) {
        var_r30 = 0;
        for (i = 0; i < 3; i++) {
            BoardModelPosGet(lbl_1_bss_298[i], &sp2C);
            sp2C.y += 2.0f;
            if (sp2C.y >= sp38[i].y) {
                sp2C.y = sp38[i].y;
                var_r30++;
            }
            BoardModelPosSetV(lbl_1_bss_298[i], &sp2C);
        }
        if (var_r30 == 3) {
            break;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 3; i++) {
        BoardModelHookSet(lbl_1_bss_14[6], lbl_1_data_51C[i], lbl_1_bss_298[i]);
    }
    while (BoardModelMotionTimeGet(lbl_1_bss_14[10]) < BoardModelMotionMaxTimeGet(lbl_1_bss_14[10])) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_bss_14[10], 1, 0.0f, 5.0f, 0x40000001);
    BoardAudSeqPause(0, 1, 1000);
    BoardModelMotionTimeSet(lbl_1_bss_14[6], 0.0f);
    BoardModelAttrReset(lbl_1_bss_14[6], 0x40000002);
    HuPrcSleep(20);
    HuAudFXPlay(0x469);
    HuPrcSleep(50);
    BoardMusStart(1, 0x1E, 0x7F, 0);
    HuAudFXPlay(0x46C);
    while (BoardModelMotionTimeGet(lbl_1_bss_14[6]) < 202.0f) {
        HuPrcVSleep();
    }
    BoardModelMotionTimeSet(lbl_1_bss_14[6], 202.0f);
    BoardModelAttrSet(lbl_1_bss_14[6], 0x40000002);
    BoardModelMotionKill(lbl_1_bss_14[10], temp_r29);
    sp14.x = -35.0f;
    sp14.y = sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 0.0f;
    sp8.z = -150.0f;
    BoardCameraMotionStartEx(lbl_1_bss_14[6], &sp14, &sp8, 1500.0f, 25.0f, 21);
    BoardPlayerPosGet(lbl_1_bss_2AC, &sp2C);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[6]), lbl_1_data_51C[4], &sp20);
    sp20.z = sp2C.z - 50.0f;
    sp20.y = sp2C.y;
    BoardPlayerPosLerpStart(lbl_1_bss_2AC, &sp2C, &sp20, 0x3C);
    while (GWPlayer[lbl_1_bss_2AC].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotBlendSet(lbl_1_bss_2AC, 0xB4, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_2AC)) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    fn_1_A7E8();
    BoardMGExit();
    while (TRUE) {
        if (BoardMGDoneFlagGet() == 1) {
            BoardMGDoneFlagSet(0);
            fn_1_BA7C();
            break;
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

static void fn_1_A71C(void) {
    Vec sp8;
    float var_f31;
    s16 temp_r31;

    var_f31 = 0.0f;
    temp_r31 = (s16) HuPrcCurrentGet()->user_data;
    while (TRUE) {
        BoardModelPosGet(temp_r31, &sp8);
        sp8.y += 0.25 * sind(var_f31);
        var_f31 += 5.0f;
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        BoardModelPosSetV(temp_r31, &sp8);
        HuPrcVSleep();
    }
}

static void fn_1_A7E8(void) {
    Vec sp54[3];
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    float sp10[2];
    float var_f29;
    float var_f30;
    float var_f31;
    Process *var_r20;
    s16 var_r30;
    s16 var_r28;
    s16 var_r27;
    s16 var_r26;
    s16 var_r25;
    s16 var_r24;
    u16 temp_r29;
    u16 var_r23;
    s16 var_r22;
    s16 var_r21;
    s16 var_r19;
    u16 temp_r18;
    u16 var_r17;
    ParticleData *spC;
    s32 sp8;
    s32 i;

    var_r28 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W04, 14), NULL, 0);
    BoardModelAttrSet(var_r28, 0x40000001);
    BoardModelVisibilitySet(var_r28, 0);
    var_r30 = 1;
    for (i = 0; i < 3; i++) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[6]), lbl_1_data_51C[i + 3], &sp54[i]);
        sp54[i].y += 50.0f;
    }
    var_r25 = MGSeqCreate(3, 0);
    while (MGSeqStatGet(var_r25) != 0) {
        HuPrcVSleep();
    }
    var_r24 = 5;
    var_r21 = 60;
    var_r25 = MGSeqCreate(1, var_r24, 0x120, 0x40);
    HuWinMesMaxSizeGet(1, sp10, MAKE_MESSID(32, 22));
    var_r27 = HuWinCreate(-10000.0f, 368.0f, sp10[0], sp10[1], 0);
    HuWinMesSet(var_r27, MAKE_MESSID(32, 22));
    HuWinBGTPLvlSet(var_r27, 0.0f);
    HuWinMesSpeedSet(var_r27, 0);
    BoardModelVisibilitySet(var_r28, 1);
    BoardModelPosSetV(var_r28, &sp54[var_r30]);
    var_r22 = 30;
    var_r19 = 0;
    temp_r18 = GWPlayer[lbl_1_bss_2AC].port;
    while (TRUE) {
        var_r21--;
        if (var_r21 == 0) {
            var_r21 = 60;
            if (--var_r24 < 0) {
                break;
            }
            MGSeqParamSet(var_r25, 1, var_r24);
        }
        if (GWPlayer[lbl_1_bss_2AC].com) {
            if (var_r22 != 0) {
                var_r22--;
            } else {
                var_r22 = frandmod(30) + 15;
                if (frandBool() || var_r19 == 3) {
                    var_r17 = 0x100;
                } else {
                    if (frandBool()) {
                        var_r23 = 1;
                    } else {
                        var_r23 = 2;
                    }
                    var_r19++;
                }
            }
        } else {
            var_r17 = HuPadBtnDown[temp_r18];
            var_r23 = HuPadDStkRep[temp_r18];
        }
        if (var_r17 & 0x100) {
            break;
        }
        if ((var_r23 & 1) && var_r30 != 0) {
            HuAudFXPlay(0);
            var_r30--;
        }
        if ((var_r23 & 2) && var_r30 != 2) {
            HuAudFXPlay(0);
            var_r30++;
        }
        BoardModelPosSetV(var_r28, &sp54[var_r30]);
        HuPrcVSleep();
    }
    HuAudFXPlay(2);
    MGSeqParamSet(var_r25, 2, -1);
    HuWinKill(var_r27);
    for (i = 0; i < 360; i += 12) {
        sp48.x = sp48.y = sp48.z = 1.0 + 0.8f * sind(i % 180);
        BoardModelScaleSetV(var_r28, &sp48);
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(var_r28, 0);
    BoardPlayerPosGet(lbl_1_bss_2AC, &sp18);
    BoardPlayerMotionShiftSet(lbl_1_bss_2AC, 4, 0.0f, 5.0f, 0);
    var_f30 = 0.0f;
    var_f29 = 12.0f;
    sp3C = sp54[var_r30];
    BoardPlayerPosGet(lbl_1_bss_2AC, &sp30);
    VECSubtract(&sp3C, &sp30, &sp3C);
    VECScale(&sp3C, &sp3C, 0.05f);
    while (TRUE) {
        BoardPlayerPosGet(lbl_1_bss_2AC, &sp30);
        sp3C.y = var_f29 - var_f30 * var_f30 * 0.25f * 0.075f;
        var_f30 += 1.0f;
        VECAdd(&sp3C, &sp30, &sp30);
        if (sp30.y <= sp54[var_r30].y - 40.0f && sp3C.y < 0.0f) {
            sp30.y = sp54[var_r30].y - 40.0f;
            break;
        }
        BoardPlayerPosSetV(lbl_1_bss_2AC, &sp30);
        sp48 = sp54[var_r30];
        sp48.y = sp30.y = 0.0f;
        VECSubtract(&sp48, &sp30, &sp30);
        var_f31 = VECMag(&sp30);
        if (var_f31 <= 1.0f) {
            sp3C.x = sp3C.z = 0.0f;
        }
        HuPrcVSleep();
    }
    BoardAudSeqFadeOut(1, 100);
    HuAudFXPlay(lbl_1_data_534[var_r30]);
    BoardModelMotionTimeSet(lbl_1_bss_29E[var_r30], 0.0f);
    BoardModelAttrReset(lbl_1_bss_29E[var_r30], 0x40000002);
    BoardPlayerPosSetV(lbl_1_bss_2AC, &sp30);
    BoardPlayerMotionShiftSet(lbl_1_bss_2AC, 1, 0.0f, 5.0f, 0x40000001);
    while (BoardModelMotionTimeGet(lbl_1_bss_29E[var_r30]) < BoardModelMotionMaxTimeGet(lbl_1_bss_29E[var_r30])) {
        if (BoardModelMotionTimeGet(lbl_1_bss_29E[var_r30]) >= 13.0f) {
            BoardPlayerPosGet(lbl_1_bss_2AC, &sp30);
            sp30.y += 1.0f;
            BoardPlayerPosSetV(lbl_1_bss_2AC, &sp30);
        }
        HuPrcVSleep();
    }
    temp_r29 = frandmod(3);
    BoardModelHookReset(lbl_1_bss_14[6]);
    for (i = 0; i < 3; i++) {
        BoardModelHookSet(lbl_1_bss_14[6], lbl_1_data_51C[i + 3], lbl_1_bss_29E[i]);
        if (i != temp_r29) {
            BoardModelVisibilitySet(lbl_1_bss_298[i], 0);
        }
    }
    BoardModelHookSet(lbl_1_bss_14[6], lbl_1_data_51C[1], lbl_1_bss_298[temp_r29]);
    BoardModelAttrReset(lbl_1_bss_14[6], 0x40000002);
    HuPrcSleep(30);
    HuAudFXPlay(0x310);
    while (BoardModelMotionTimeGet(lbl_1_bss_14[6]) < BoardModelMotionMaxTimeGet(lbl_1_bss_14[6])) {
        HuPrcVSleep();
    }
    BoardModelHookReset(lbl_1_bss_14[6]);
    for (i = 0; i < 3; i++) {
        BoardModelHookSet(lbl_1_bss_14[6], lbl_1_data_51C[i + 3], lbl_1_bss_29E[i]);
    }
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[6]), lbl_1_data_51C[1], &sp24);
    BoardModelPosSetV(lbl_1_bss_298[temp_r29], &sp24);
    var_r20 = HuPrcChildCreate(fn_1_A71C, 0x2002, 0x800, 0, boardMainProc);
    var_r20->user_data = (void*) lbl_1_bss_298[temp_r29];
    var_r26 = Hu3DParticleCreate(lbl_1_bss_288, 100);
    spC = Hu3DData[var_r26].unk_120;
    spC->unk_02 = lbl_1_bss_298[temp_r29];
    Hu3DParticleHookSet(var_r26, fn_1_C388);
    Hu3DParticleColSet(var_r26, 0xFF, 0xFF, 0);
    Hu3DModelPosSet(var_r26, 0.0f, 0.0f, 0.0f);
    Hu3DParticleBlendModeSet(var_r26, 1);
    Hu3DModelLayerSet(var_r26, 2);
    lbl_1_bss_28C = HuAudFXPlay(0x35F);
    BoardPlayerMotBlendSet(lbl_1_bss_2AC, 0, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_2AC)) {
        HuPrcVSleep();
    }
    BoardPlayerMotionShiftSet(lbl_1_bss_2AC, 4, 0.0f, 5.0f, 0);
    var_f30 = 0.0f;
    var_f29 = 12.0f;
    BoardPlayerPosGet(lbl_1_bss_2AC, &sp30);
    VECSubtract(&sp18, &sp30, &sp3C);
    VECScale(&sp3C, &sp3C, 0.05f);
    while (TRUE) {
        BoardPlayerPosGet(lbl_1_bss_2AC, &sp30);
        sp3C.y = var_f29 - var_f30 * var_f30 * 0.25f * 0.075f;
        var_f30 += 1.0f;
        VECAdd(&sp3C, &sp30, &sp30);
        if (sp30.y < sp18.y) {
            sp30.y = sp18.y;
            break;
        }
        BoardPlayerPosSetV(lbl_1_bss_2AC, &sp30);
        sp48 = sp18;
        sp48.y = sp30.y = 0.0f;
        VECSubtract(&sp48, &sp30, &sp30);
        var_f31 = VECMag(&sp30);
        if (var_f31 <= 1.0f) {
            sp3C.x = sp3C.z = 0.0f;
        }
        HuPrcVSleep();
    }
    omVibrate(lbl_1_bss_2AC, 12, 6, 6);
    BoardPlayerPosSetV(lbl_1_bss_2AC, &sp30);
    BoardPlayerMotionShiftSet(lbl_1_bss_2AC, 1, 0.0f, 5.0f, 0x40000001);
    BoardModelPosGet(lbl_1_bss_298[temp_r29], &sp24);
    sp3C = sp24;
    sp3C.z += 100.0f;
    VECSubtract(&sp3C, &sp24, &sp3C);
    VECScale(&sp3C, &sp3C, 0.033333335f);
    for (i = 0; i < 30; i++) {
        BoardModelPosGet(lbl_1_bss_298[temp_r29], &sp24);
        VECAdd(&sp24, &sp3C, &sp24);
        BoardModelPosSetV(lbl_1_bss_298[temp_r29], &sp24);
        HuPrcVSleep();
    }
    BoardPlayerPosGet(lbl_1_bss_2AC, &sp30);
    sp24.y = sp30.y;
    BoardPlayerPosLerpStart(lbl_1_bss_2AC, &sp30, &sp24, 0x3C);
    while (GWPlayer[lbl_1_bss_2AC].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotBlendSet(lbl_1_bss_2AC, 0, 0xF);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_2AC)) {
        HuPrcVSleep();
    }
    var_f31 = 90.0f;
    for (i = 0; i < 15; i++) {
        var_f31 -= 3.0f;
        BoardModelRotYSet(lbl_1_bss_14[10], var_f31);
        HuPrcVSleep();
    }
    BoardWinCreate(2, MAKE_MESSID(32, 15), 3);
    BoardWinInsertMesSet(MAKE_MESSID(8, lbl_1_bss_2A6[temp_r29]), 0);
    BoardWinWait();
    BoardWinKill();
    HuAudFXPlay(0x30D);
    HuPrcKill(var_r20);
    BoardPlayerPosGet(lbl_1_bss_2AC, &sp30);
    BoardModelPosGet(lbl_1_bss_298[temp_r29], &sp24);
    var_f29 = 1.0f;
    var_f31 = (sp30.y - sp24.y) / 30.0f;
    var_f30 = -0.04f;
    var_r27 = 0;
    HuAudFXFadeOut(lbl_1_bss_28C, 0x1F3);
    while (var_r27 == 0) {
        sp24.y += var_f31;
        var_f29 += var_f30;
        if (var_f29 < 0.0f) {
            var_f29 = 0.0f;
            var_r27 = 1;
        }
        sp48.x = sp48.y = sp48.z = var_f29;
        BoardModelPosSetV(lbl_1_bss_298[temp_r29], &sp24);
        BoardModelScaleSetV(lbl_1_bss_298[temp_r29], &sp48);
        HuPrcVSleep();
    }
    HuAudFXStop(lbl_1_bss_28C);
    BoardModelVisibilitySet(lbl_1_bss_298[temp_r29], 0);
    BoardPlayerItemAdd(lbl_1_bss_2AC, lbl_1_bss_2A6[temp_r29]);
    omVibrate(lbl_1_bss_2AC, 12, 6, 6);
    sp8 = HuAudSStreamPlay(2);
    BoardPlayerMotionShiftSet(lbl_1_bss_2AC, 7, 0.0f, 5.0f, 0);
    while (!BoardPlayerMotionEndCheck(lbl_1_bss_2AC)) {
        HuPrcVSleep();
    }
    var_f31 = 45.0f;
    for (i = 0; i < 15; i++) {
        var_f31 -= 3.0f;
        BoardModelRotYSet(lbl_1_bss_14[10], var_f31);
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_bss_14[10], 0.0f);
    HuPrcSleep(30);
    while (HuAudSStreamStatGet(sp8) != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 1000);
    BoardWinCreate(2, MAKE_MESSID(32, 16), 3);
    BoardWinWait();
    BoardWinKill();
    BoardModelMotionTimeSet(lbl_1_bss_14[6], 0.0f);
    BoardModelAttrSet(lbl_1_bss_14[6], 0x40000002);
    Hu3DModelKill(var_r26);
    BoardModelKill(var_r28);
}

void fn_1_BA7C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        BoardModelKill(lbl_1_bss_298[i]);
    }
    if (lbl_1_bss_288) {
        HuSprAnimKill(lbl_1_bss_288);
        lbl_1_bss_288 = NULL;
    }
}

void fn_1_BB00(s16 *arg0) {
    Vec sp54[3];
    Vec sp30[3];
    Vec sp24;
    Vec sp18;
    float spC[3];
    float temp_f28;
    float var_f27;
    float var_f29;
    s32 var_r30;
    s32 i;

    for (i = 0; i < 3; i++) {
        lbl_1_bss_2A6[i] = arg0[i];
        lbl_1_bss_298[i] = BoardModelCreate(lbl_1_data_540[lbl_1_bss_2A6[i]], NULL, 0);
        BoardModelVisibilitySet(lbl_1_bss_298[i], 0);
        if (lbl_1_bss_2A6[i] == 11) {
            BoardModelAttrSet(lbl_1_bss_298[i], 0x40000001);
        }
        if (lbl_1_bss_2A6[i] == 5) {
            Hu3DData[BoardModelIDGet(lbl_1_bss_298[i])].unk_F0[1][3] = -50.0f;
        }
        if (lbl_1_bss_2A6[i] == 4) {
            BoardModelMotionSpeedSet(lbl_1_bss_298[i], 0.0f);
        }
    }
    if (lbl_1_bss_288 == NULL) {
        lbl_1_bss_288 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 0));
        HuSprAnimLock(lbl_1_bss_288);
    }
    BoardModelMotionTimeSet(lbl_1_bss_14[6], 0.0f);
    BoardModelAttrSet(lbl_1_bss_14[6], 0x40000002);
    sp18.x = sp18.y = sp18.z = 0.0f;
    for (i = 0; i < 3; i++) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[6]), lbl_1_data_51C[i], &sp54[i]);
        sp54[i].y += -50.0f;
        BoardModelVisibilitySet(lbl_1_bss_298[i], 1);
        BoardModelPosSetV(lbl_1_bss_298[i], &sp54[i]);
        BoardModelPosGet(lbl_1_bss_14[10], &sp24);
        BoardModelPosSetV(lbl_1_bss_298[i], &sp24);
        BoardModelScaleSetV(lbl_1_bss_298[i], &sp18);
        VECSubtract(&sp54[i], &sp24, &sp30[i]);
        VECNormalize(&sp30[i], &sp30[i]);
        spC[i] = 0.0f;
    }
    sp30[0].y = 16.0f;
    sp30[1].y = 13.0f;
    sp30[2].y = 10.0f;
    HuAudFXPlay(0x362);
    var_f29 = 0.0f;
    while (TRUE) {
        var_r30 = 0;
        var_f29 += 0.05f;
        if (var_f29 > 1.0f) {
            var_f29 = 1.0f;
        }
        sp18.x = sp18.y = sp18.z = var_f29;
        for (i = 0; i < 3; i++) {
            BoardModelPosGet(lbl_1_bss_298[i], &sp24);
            temp_f28 = sp30[i].y - spC[i] * spC[i] * 0.25f * 0.075f;
            sp24.x += 6.55f * sp30[i].x;
            sp24.z += 6.55f * sp30[i].z;
            sp24.y += temp_f28;
            var_f27 = VECDistanceXZ(&sp54[i], &sp24);
            if (var_f27 < 3.0f) {
                sp30[i].x = sp30[i].z = 0.0f;
                sp24.x = sp54[i].x;
                sp24.z = sp54[i].z;
            }
            if (sp24.y <= sp54[i].y && temp_f28 < 0.0f) {
                sp24.y = sp54[i].y;
                var_r30++;
            }
            BoardModelPosSetV(lbl_1_bss_298[i], &sp24);
            BoardModelScaleSetV(lbl_1_bss_298[i], &sp18);
            spC[i] += 1.0f;
        }
        if (var_r30 == 3) {
            break;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 3; i++) {
        BoardModelPosSetV(lbl_1_bss_298[i], &sp54[i]);
    }
}

void fn_1_C2BC(void) {
    Vec sp8;
    float var_f31;
    s32 i;
    s32 j;

    var_f31 = 1.0f;
    for (i = 0; i < 20; i++) {
        var_f31 -= 0.05f;
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        }
        sp8.x = sp8.y = sp8.z = var_f31;
        for (j = 0; j < 3; j++) {
            BoardModelScaleSetV(lbl_1_bss_298[j], &sp8);
        }
        HuPrcVSleep();
    }
}

static void fn_1_C388(ModelData *model, ParticleData *particle, Mtx matrix) {
    Vec sp8;
    HsfanimStruct01 *var_r31;
    float var_f31;
    float temp_f30;
    float temp_f29;
    s32 var_r28;
    s32 i;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
        particle->unk_00 = 0;
    }
    BoardModelScaleGet(particle->unk_02, &sp8);
    var_f31 = sp8.x;
    BoardModelPosGet(particle->unk_02, &sp8);
    for (i = 0; i < 22; i++) {
        var_r31 = particle->unk_48;
        for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
            if (var_r31->unk2C == 0.0f) {
                break;
            }
        }
        if (var_r28 != particle->unk_30) {
            temp_f30 = 0.003921569f * frand8() * 360.0f;
            temp_f29 = var_f31 * (20.0f + 0.003921569f * frand8() * 60.0f);
            var_r31->unk34.x = sp8.x + temp_f29 * sind(temp_f30);
            var_r31->unk34.z = sp8.z + temp_f29 * cosd(temp_f30);
            var_r31->unk34.y = sp8.y + var_f31 * (-30.0f + 0.003921569f * frand8() * 40.0f);
            var_r31->unk08.x = 0.5f + 0.003921569f * frand8() * 3.0f;
            var_r31->unk08.y = 0.3f + 0.003921569f * frand8() * 2.0f;
            var_r31->unk40.a = 0xB4;
            var_r31->unk2C = var_f31 * 15.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (var_r31->unk2C != 0.0f) {
            var_r31->unk34.y -= var_r31->unk08.x;
            var_r31->unk2C -= var_r31->unk08.y;
            if (var_r31->unk2C <= 0.0f) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}
