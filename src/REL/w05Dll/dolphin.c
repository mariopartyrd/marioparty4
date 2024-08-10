#include "REL/w05Dll.h"

#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/hsfdraw.h"
#include "game/objsub.h"

#include "game/board/audio.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/window.h"

// bss
s16 lbl_1_bss_72[2];
s16 lbl_1_bss_6C[3];
s32 lbl_1_bss_68;
s16 lbl_1_bss_64;
s16 lbl_1_bss_58[6];

// data
char *lbl_1_data_22C[6] = { "orange1", "orange2", "pine2", "pine1", "suika1", "suika2" };
s32 lbl_1_data_244[6] = {
    DATA_MAKE_NUM(DATADIR_W05, 0x27),
    DATA_MAKE_NUM(DATADIR_W05, 0x28),
    DATA_MAKE_NUM(DATADIR_W05, 0x29),
    DATA_MAKE_NUM(DATADIR_W05, 0x2A),
    DATA_MAKE_NUM(DATADIR_W05, 0x2B),
    DATA_NUM_LISTEND,
};
Vec lbl_1_data_25C[6] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 90.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 180.0f, 0.0f },
    { 0.0f, 270.0f, 0.0f },
    { 0.0f, 90.0f, 0.0f },
};
Vec lbl_1_data_2A4[6] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 300.0f, 0.0f },
    { 0.0f, 450.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};
s32 lbl_1_data_2EC[2] = { 0x76, 0x77 };
s32 lbl_1_data_2F4[6] = {
    DATA_MAKE_NUM(DATADIR_W05, 0x2C),
    DATA_MAKE_NUM(DATADIR_W05, 0x2D),
    DATA_MAKE_NUM(DATADIR_W05, 0x2E),
    DATA_MAKE_NUM(DATADIR_W05, 0x2C),
    DATA_MAKE_NUM(DATADIR_W05, 0x2F),
    DATA_MAKE_NUM(DATADIR_W05, 0x30),
};

void fn_1_3F74(void)
{
    s32 var_r31;

    BoardAudSeqPause(0, 1, 0x3E8);

    for (var_r31 = 0x3C; var_r31 != 0; var_r31--) {
        HuPrcVSleep();
    }

    BoardMusStart(1, 0x24, 0x7F, 0);
    HuPrcEnd();
}

void fn_1_3FD8(void)
{
    s32 var_r31;

    BoardAudSeqFadeOut(1, 0x3E8);

    for (var_r31 = 0x3C; var_r31 != 0; var_r31--) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 0x3E8);
    HuPrcEnd();
}

void fn_1_4034(s32 arg0)
{
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    s16 sp14[4];
    s32 sp10;
    f32 temp_f22;
    f32 temp_f25;
    f32 var_f26;
    f32 var_f27;
    s16 var_r30;
    s32 var_r27;
    BoardSpace *var_r25;
    omObjData *temp_r24;
    BoardSpace *var_r28;
    s32 var_r31;
    s32 temp_r26;

    lbl_1_bss_68 = GWSystem.player_curr;
    sp10 = GWPlayer[lbl_1_bss_68].character;

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_72[var_r31] = BoardPlayerMotionCreate(lbl_1_bss_68, lbl_1_data_2EC[var_r31] | lbl_1_data_124[GWPlayer[lbl_1_bss_68].character]);
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_6C[var_r31] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x0A), NULL, 1);
        BoardModelAttrSet(lbl_1_bss_6C[var_r31], 0x40000001);
        BoardModelVisibilitySet(lbl_1_bss_6C[var_r31], 0);
    }
    fn_1_65E8();
    var_r27 = BoardSpaceLinkFlagSearch(0, GWPlayer[lbl_1_bss_68].space_curr, 0x02000000);
    BoardPlayerMoveBetween(lbl_1_bss_68, GWPlayer[lbl_1_bss_68].space_curr, var_r27);
    var_r28 = BoardSpaceGet(0, var_r27);

    var_r31 = 0;
    while (var_r31 < var_r28->link_cnt) {
        var_r25 = BoardSpaceGet(0, var_r28->link[var_r31]);
        if ((var_r25->flag & 0x02000000) == 0) {
            var_r31++;
            continue;
        }
        break;
    }
    temp_r26 = var_r28->link[var_r31];
    BoardPlayerMotBlendSet(lbl_1_bss_68, lbl_1_data_25C[arg0].y - 180.0f, 5);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_68) == 0) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(lbl_1_bss_68);
    HuPrcSleep(8);
    lbl_1_bss_64 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x26), lbl_1_data_244, 0);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_118), lbl_1_data_22C[arg0], &sp40);
    VECAdd(&sp40, &lbl_1_data_2A4[arg0], &sp40);
    BoardModelMotionStart(lbl_1_bss_64, 4, 0);
    sp40.y = -50.0f;
    BoardModelPosSetV(lbl_1_bss_64, &sp40);
    BoardModelRotSetV(lbl_1_bss_64, &lbl_1_data_25C[arg0]);
    fn_1_66C0(0, &sp40);

    var_r30 = 0;
    while (BoardModelMotionTimeGet(lbl_1_bss_64) < BoardModelMotionMaxTimeGet(lbl_1_bss_64)) {
        if (BoardModelMotionTimeGet(lbl_1_bss_64) > 50.0f && var_r30 == 0) {
            var_r30++;
            HuAudFXPlay(0x47D);
            HuAudFXPlay(0x48E);
        }
        if (BoardModelMotionTimeGet(lbl_1_bss_64) > 70.0f && var_r30 == 1) {
            var_r30++;
            HuAudFXPlay(0x47E);
        }
        if (BoardModelMotionTimeGet(lbl_1_bss_64) > 105.0f && var_r30 == 2) {
            var_r30++;
            HuAudFXPlay(0x481);
        }
        HuPrcVSleep();
    }
    BoardModelMotionStart(lbl_1_bss_64, 1, 0x40000001);
    temp_r24 = fn_1_66C0(2, &sp40);
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    HuAudFXPlay(0x480);
    BoardWinCreate(2, MAKE_MESSID(39, 7), 0xA);
    BoardWinWait();
    BoardWinKill();
    if (arg0 >= 4) {
        HuPrcChildCreate(fn_1_3F74, 0x2001, 0x800, 0, boardMainProc);
    }
    if ((arg0 & 1) != 0) {
        var_r27 = arg0 - 1;
    }
    else {
        var_r27 = arg0 + 1;
    }
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_118), lbl_1_data_22C[var_r27], &sp34);
    temp_f25 = (180.0 * (atan2((sp34.x - sp40.x), (sp34.z - sp40.z)) / M_PI));
    BoardModelMotionShiftSet(lbl_1_bss_64, 2, 0.0f, 10.0f, 0x40000001);

    while (fn_1_1208(lbl_1_bss_64, temp_f25, 10.0f) == 0) {
        HuPrcVSleep();
    }

    BoardPlayerPosGet(lbl_1_bss_68, &sp28);
    var_f27 = sqrtf(((sp40.x - sp28.x) * (sp40.x - sp28.x)) + ((sp40.z - sp28.z) * (sp40.z - sp28.z)));
    VECSubtract(&sp40, &sp28, &sp1C);
    VECNormalize(&sp1C, &sp1C);
    VECScale(&sp1C, &sp1C, var_f27 / 50.0f);
    BoardPlayerMotionStart(lbl_1_bss_68, 4, 0);
    var_f26 = 0.0f;
    temp_f22 = 15.0f;

loop_37:
    sp1C.y = temp_f22 - (0.075f * (0.25f * (var_f26 * var_f26)));
    var_f26++;
    VECAdd(&sp28, &sp1C, &sp28);
    var_f27 = sqrtf(((sp40.x - sp28.x) * (sp40.x - sp28.x)) + ((sp40.z - sp28.z) * (sp40.z - sp28.z)));
    if (var_f27 < 5.0f) {
        sp1C.x = sp1C.z = 0.0f;
        sp28.x = sp40.x;
        sp28.z = sp40.z;
    }

    if (sp28.y <= 20.0f + sp40.y) {
        sp28.y = 20.0f + sp40.y;
    }
    else {
        BoardPlayerPosSetV(lbl_1_bss_68, &sp28);
        HuPrcVSleep();
        goto loop_37;
    }
    BoardPlayerPosSetV(lbl_1_bss_68, &sp28);
    BoardPlayerMotionStart(lbl_1_bss_68, lbl_1_bss_72[0], 0);

    while (fn_1_1208(BoardPlayerModelGet(lbl_1_bss_68), temp_f25, 10.0f) == 0) {
        HuPrcVSleep();
    }

    while (BoardPlayerMotionEndCheck(lbl_1_bss_68) == 0) {
        HuPrcVSleep();
    }

    BoardPlayerMotionStart(lbl_1_bss_68, lbl_1_bss_72[1], 0x40000001);
    HuPrcSleep(0x12);
    temp_r24->work[1] = 1;
    if (arg0 < 4) {
        fn_1_4EB4(arg0, temp_r26, &sp34);
    }
    else {
        fn_1_5794(arg0, temp_r26, &sp34);
    }
    BoardModelPosGet(lbl_1_bss_64, &sp40);
    BoardPlayerPosGet(lbl_1_bss_68, &sp28);
    var_f27 = 180.0 * (atan2((sp40.x - sp28.x), (sp40.z - sp28.z)) / M_PI);
    BoardPlayerMotBlendSet(lbl_1_bss_68, var_f27, 0xF);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_68) == 0) {
        HuPrcVSleep();
    }

    fn_1_66C0(1, &sp40);
    BoardModelMotionShiftSet(lbl_1_bss_64, 5, 0.0f, 5.0f, 0);
    var_r30 = 0;
    var_r31 = 0;

    while (var_r31 < 0x5AU) {
        if ((BoardModelMotionTimeGet(lbl_1_bss_64) > 15.0f) && (var_r30 == 0)) {
            var_r30++;
            HuAudFXPlay(0x47D);
            if (arg0 >= 4) {
                BoardAudSeqFadeOut(1, 0x3E8);
                HuPrcChildCreate(fn_1_3FD8, 0x2001, 0x800, 0, boardMainProc);
            }
        }
        if ((BoardModelMotionTimeGet(lbl_1_bss_64) > 30.0f) && (var_r30 == 1)) {
            var_r30++;
            HuAudFXPlay(0x47E);
        }
        if ((BoardModelMotionTimeGet(lbl_1_bss_64) > 65.0f) && (var_r30 == 2)) {
            var_r30++;
            HuAudFXPlay(0x481);
        }
        HuPrcVSleep();
        var_r31++;
    }
    BoardCameraMoveSet(0);
    GWPlayer[lbl_1_bss_68].space_curr = temp_r26;
    var_r27 = BoardSpaceLinkTargetListGet(0, temp_r26, sp14);

    for (var_r31 = 0; (s32)var_r31 < var_r27;) {
        var_r28 = BoardSpaceGet(0, sp14[var_r31]);
        if ((var_r28->flag & 0x80) == 0) {
            var_r31++;
            continue;
        }
        break;
    }
    BoardPlayerMoveBetween(lbl_1_bss_68, temp_r26, sp14[var_r31]);
    GWPlayer[lbl_1_bss_68].space_curr = sp14[var_r31];
    BoardPlayerIdleSet(lbl_1_bss_68);
    HuPrcSleep(8);
    if (arg0 >= 4) {
        BoardStatusShowSetAll(1);
    }
    BoardModelKill(lbl_1_bss_64);

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        BoardPlayerMotionKill(lbl_1_bss_68, lbl_1_bss_72[var_r31]);
    }

    fn_1_6670();

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        BoardModelKill(lbl_1_bss_6C[var_r31]);
    }
}

void fn_1_4EB4(s32 arg1, s32 arg2, Vec *arg3)
{
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    f32 temp_f19;
    f32 temp_f23;
    f32 var_f20;
    f32 var_f22;
    f32 var_f24;
    f32 var_f28;
    omObjData *temp_r30;
    omObjData *temp_r29;
    s32 temp_r28;

    temp_f23 = 10.0f;
    BoardModelPosGet(lbl_1_bss_64, &sp3C);
    arg3->y = sp3C.y;
    VECSubtract(arg3, &sp3C, &sp24);
    VECNormalize(&sp24, &sp24);
    VECScale(&sp24, &sp24, temp_f23);
    temp_r28 = HuAudFXPlay(0x47F);
    BoardModelPosGet(lbl_1_bss_64, &sp18);
    temp_r30 = fn_1_66C0(4, &sp18);
    temp_r29 = fn_1_66C0(5, &sp18);
    while (1) {
        var_f28 = sqrtf((arg3->x - sp3C.x) * (arg3->x - sp3C.x) + (arg3->z - sp3C.z) * (arg3->z - sp3C.z));
        if (var_f28 <= temp_f23) {
            sp3C.x = arg3->x;
            sp3C.z = arg3->z;
            BoardModelPosSetV(lbl_1_bss_64, &sp3C);
            sp30 = sp3C;
            sp30.y += 20.0f;
            BoardPlayerPosSetV(lbl_1_bss_68, &sp30);
            break;
        } else {
            VECAdd(&sp3C, &sp24, &sp3C);
            BoardModelPosSetV(lbl_1_bss_64, &sp3C);
            sp30 = sp3C;
            sp30.y += 20.0f;
            BoardPlayerPosSetV(lbl_1_bss_68, &sp30);
            HuPrcVSleep();
        }
    }
    HuAudFXStop(temp_r28);
    temp_r30->work[1] = 1;
    temp_r29->work[1] = 1;
    BoardPlayerIdleSet(lbl_1_bss_68);
    HuPrcSleep(8);
    BoardSpacePosGet(0, arg2, &sp3C);
    var_f28 = 180.0 * (atan2((sp3C.x - sp30.x), (sp3C.z - sp30.z)) / M_PI);
    BoardPlayerMotBlendSet(lbl_1_bss_68, var_f28, 0xF);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_68) == 0) {
        HuPrcVSleep();
    }

    BoardPlayerPosGet(lbl_1_bss_68, &sp30);
    var_f28 = sqrtf(((sp3C.x - sp30.x) * (sp3C.x - sp30.x)) + ((sp3C.z - sp30.z) * (sp3C.z - sp30.z)));
    VECSubtract(&sp3C, &sp30, &sp24);
    VECNormalize(&sp24, &sp24);
    VECScale(&sp24, &sp24, var_f28 / 45.0f);
    BoardPlayerMotionStart(lbl_1_bss_68, 4, 0);

    var_f24 = 0.0f;
    temp_f19 = 15.0f;

    while (1) {
        sp24.y = temp_f19 - (0.075f * (0.25f * (var_f24 * var_f24)));
        var_f24++;
        VECAdd(&sp30, &sp24, &sp30);
        var_f28 = sqrtf(((sp3C.x - sp30.x) * (sp3C.x - sp30.x)) + ((sp3C.z - sp30.z) * (sp3C.z - sp30.z)));
        if (var_f28 < 5.0f) {
            sp24.x = sp24.z = 0.0f;
            sp30.x = sp3C.x;
            sp30.z = sp3C.z;
        }
        if (sp30.y <= sp3C.y && sp24.y < 0.0f) {
            sp30.y = sp3C.y;
        }
        else {
            BoardPlayerPosSetV(lbl_1_bss_68, &sp30);
            HuPrcVSleep();
            continue;
        }
        BoardPlayerPosSetV(lbl_1_bss_68, &sp30);
        break;
    }
}

void fn_1_5648(void)
{
    Vec sp8;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        BoardModelRotGet(lbl_1_bss_6C[var_r31], &sp8);
        sp8.y = 0.003921569f * (360.0f * frand8());
        BoardModelRotSetV(lbl_1_bss_6C[var_r31], &sp8);
    }
    while (1) {
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            BoardModelRotGet(lbl_1_bss_6C[var_r31], &sp8);
            sp8.y += 10.0f;
            if (sp8.y >= 360.0f) {
                sp8.y -= 360.0f;
            }
            BoardModelRotSetV(lbl_1_bss_6C[var_r31], &sp8);
        }
        HuPrcVSleep();
    }
}

void fn_1_5794(s32 arg0, s32 arg1, Vec *arg2)
{
    Vec sp64;
    Vec sp58;
    Vec sp4C;
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    f32 sp18;
    Process *temp_r23;
    f32 temp_f18;
    f32 temp_f22;
    f32 var_f27;
    f32 var_f23;
    f32 var_f28;
    omObjData *temp_r27;
    omObjData *var_r26;
    omObjData *temp_r25;
    omObjData *var_r24;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;

    BoardModelPosGet(lbl_1_bss_64, &sp58);
    temp_r23 = HuPrcChildCreate(fn_1_5648, 0x2001, 0x800, 0, boardMainProc);
    BoardCameraMoveSet(0);
    BoardCameraTargetPlayerSet(lbl_1_bss_68);
    BoardCameraRotSet(-15.0f, 180.0f + BoardModelRotYGet(lbl_1_bss_64));
    BoardCameraZoomSet(1400.0f);
    BoardStatusShowSetAll(0);
    fn_1_62AC(arg0, arg2);
    temp_f22 = 10.0f;
    arg2->y = sp58.y;
    VECSubtract(arg2, &sp58, &sp40);
    VECNormalize(&sp40, &sp40);
    VECScale(&sp40, &sp40, temp_f22);
    if (arg0 == 5) {
        var_r29 = 0x96;
    }
    else {
        var_r29 = 0x5A;
    }
    var_f28 = 0.0f;
    sp64 = sp58;
    BoardModelRotGet(lbl_1_bss_64, &sp34);
    BoardPlayerRotGet(lbl_1_bss_68, &sp28);
    BoardCameraTargetModelSet(-1);
    var_r30 = 0;
    var_r28 = HuAudFXPlay(0x47F);
    BoardModelPosGet(lbl_1_bss_64, &sp1C);
    temp_r27 = fn_1_66C0(4, &sp1C);
    temp_r25 = fn_1_66C0(5, &sp1C);

    while (1) {
        sp18 = BoardModelRotYGet(lbl_1_bss_64);
        sp58 = sp64;
        var_f27 = sqrtf(((arg2->x - sp58.x) * (arg2->x - sp58.x)) + ((arg2->z - sp58.z) * (arg2->z - sp58.z)));
        if (var_f27 <= temp_f22) {
            sp58.x = arg2->x;
            sp58.z = arg2->z;
            BoardModelPosSetV(lbl_1_bss_64, &sp58);
            sp4C = sp58;
            sp4C.y += 20.0f;
            BoardPlayerPosSetV(lbl_1_bss_68, &sp4C);
            break;
        } else {
            VECAdd(&sp58, &sp40, &sp58);
            sp64 = sp58;
            if (var_r29 == 0) {
                sp58.y += 250.0 * sin((M_PI * var_f28) / 180.0);
                var_f28 -= 2.5f;
                if (var_f28 < -540.0f) {
                    var_f28 = -540.0f;
                }

                if (var_r30 == 0) {
                    temp_r27->work[1] = 1;
                    temp_r25->work[1] = 1;
                    var_r30++;
                }
                else if (var_r30 == 1 && var_f28 < -180.0f) {
                    HuAudFXStop(var_r28);
                    HuAudFXPlay(0x47D);
                    HuAudPlayerVoicePlay(lbl_1_bss_68, 0x125);
                    fn_1_66C0(3, &sp58);
                    var_r30++;
                }
                else if ((var_r30 == 2) && (var_f28 < -360.0f)) {
                    var_r28 = HuAudFXPlay(0x47F);
                    HuAudFXPlay(0x481);
                    fn_1_66C0(3, &sp58);
                    var_r30++;
                }
                else if ((var_r30 == 3) && (-540.0f == var_f28)) {
                    var_r30++;
                    BoardModelPosGet(lbl_1_bss_64, &sp1C);
                    var_r26 = fn_1_66C0(4, &sp1C);
                    var_r24 = fn_1_66C0(5, &sp1C);
                }
            }
            else {
                var_r29--;
            }
            BoardModelPosSetV(lbl_1_bss_64, &sp58);
            sp28.x = sp34.x = (45.0 * -sin((M_PI * var_f28) / 180.0));
            BoardModelRotSetV(lbl_1_bss_64, &sp34);
            BoardPlayerRotSetV(lbl_1_bss_68, &sp28);
            sp4C = sp58;
            sp4C.y += 20.0f;
            BoardPlayerPosSetV(lbl_1_bss_68, &sp4C);
            fn_1_64BC();
            BoardCameraTargetSet(sp58.x, -50.0f, sp58.z);
            HuPrcVSleep();
        }
    }
    HuAudFXStop(var_r28);
    var_r26->work[1] = 1;
    var_r24->work[1] = 1;
    BoardCameraMoveSet(1);
    BoardCameraTargetPlayerSet(lbl_1_bss_68);
    BoardPlayerIdleSet(lbl_1_bss_68);
    HuPrcSleep(8);
    BoardSpacePosGet(0, arg1, &sp58);
    var_f27 = (180.0 * (atan2((sp58.x - sp4C.x), (sp58.z - sp4C.z)) / M_PI));
    BoardPlayerMotBlendSet(lbl_1_bss_68, var_f27, 0xF);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_68) == 0) {
        HuPrcVSleep();
    }
    BoardPlayerPosGet(lbl_1_bss_68, &sp4C);
    var_f27 = sqrtf(((sp58.x - sp4C.x) * (sp58.x - sp4C.x)) + ((sp58.z - sp4C.z) * (sp58.z - sp4C.z)));
    VECSubtract(&sp58, &sp4C, &sp40);
    VECNormalize(&sp40, &sp40);
    VECScale(&sp40, &sp40, var_f27 / 45.0f);
    BoardPlayerMotionStart(lbl_1_bss_68, 4, 0);
    var_f23 = 0.0f;
    temp_f18 = 15.0f;
    while (1) {
        sp40.y = temp_f18 - (0.075f * (0.25f * (var_f23 * var_f23)));
        var_f23++;
        VECAdd(&sp4C, &sp40, &sp4C);
        var_f27 = sqrtf(((sp58.x - sp4C.x) * (sp58.x - sp4C.x)) + ((sp58.z - sp4C.z) * (sp58.z - sp4C.z)));
        if (var_f27 < 5.0f) {
            sp40.x = sp40.z = 0.0f;
            sp4C.x = sp58.x;
            sp4C.z = sp58.z;
        }
        if (sp4C.y <= sp58.y && sp40.y < 0.0f) {
            sp4C.y = sp58.y;
            break;
        }
        else {
            BoardPlayerPosSetV(lbl_1_bss_68, &sp4C);
            HuPrcVSleep();
        }
    }
    BoardPlayerPosSetV(lbl_1_bss_68, &sp4C);
    HuPrcKill(temp_r23);
}

void fn_1_62AC(s32 arg0, Vec *arg1)
{
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    f32 sp8[2] = { 1950.0f, 2550.0f };
    f32 var_f30;
    f32 var_f31;
    s32 var_r31;

    BoardModelPosGet(lbl_1_bss_64, &sp34);
    arg0 -= 4;
    arg1->y = sp34.y;
    VECSubtract(arg1, &sp34, &sp28);
    VECNormalize(&sp28, &sp28);
    var_f31 = 45.0f;
    var_r31 = 0;
    while (var_r31 < 3) {
        sp1C = sp28;
        sp10 = sp28;
        VECScale(&sp1C, &sp1C, sp8[arg0]);
        sp1C.y += (250.0 * sin((M_PI * var_f31) / 180.0));
        var_f30 = (250.0 * -cos((M_PI * var_f31) / 180.0));
        VECScale(&sp10, &sp10, var_f30);
        VECAdd(&sp10, &sp1C, &sp1C);
        VECAdd(&sp1C, &sp34, &sp1C);
        BoardModelPosSetV(lbl_1_bss_6C[var_r31], &sp1C);
        BoardModelVisibilitySet(lbl_1_bss_6C[var_r31], 1);
        var_f31 += 45.0f;
        var_r31++;
    }
}

void fn_1_64BC(void)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 var_r31;
    f32 var_f31;

    BoardPlayerPosGet(lbl_1_bss_68, &sp20);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        if (BoardModelVisibilityGet(lbl_1_bss_6C[var_r31]) != 0) {
            BoardModelPosGet(lbl_1_bss_6C[var_r31], &sp14);
            VECSubtract(&sp14, &sp20, &sp8);
            var_f31 = VECMag(&sp8);
            if (var_f31 < 60.0f) {
                CharModelCoinEffectCreate(1, &sp14);
                BoardModelVisibilitySet(lbl_1_bss_6C[var_r31], 0);
                BoardPlayerCoinsAdd(lbl_1_bss_68, 1);
                HuAudFXPlay(7);
                omVibrate(lbl_1_bss_68, 0xC, 6, 6);
            }
        }
    }
}

void fn_1_65E8(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        lbl_1_bss_58[var_r31] = BoardModelCreate(lbl_1_data_2F4[var_r31], NULL, 0);
        BoardModelVisibilitySet(lbl_1_bss_58[var_r31], 0);
    }
}

void fn_1_6670(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        BoardModelKill(lbl_1_bss_58[var_r31]);
    }
}

omObjData *fn_1_66C0(u32 arg0, Vec *arg1)
{
    Vec sp8;
    omObjData *temp_r31;
    f32 temp_f31;

    temp_r31 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_6914);
    temp_r31->trans.x = arg1->x;
    temp_r31->trans.y = arg1->y;
    temp_r31->trans.z = arg1->z;
    temp_r31->work[0] = BoardModelCreate(lbl_1_data_2F4[arg0], NULL, 1);
    temp_r31->work[2] = arg0;
    BoardModelPosSetV(temp_r31->work[0], arg1);
    BoardModelMotionTimeSet(temp_r31->work[0], 0.0f);
    switch (arg0) {
        case 0:
        case 1:
            break;
        case 2:
            BoardModelAttrSet(temp_r31->work[0], 0x40000001);
            break;
        case 3:
            BoardModelMotionTimeSet(temp_r31->work[0], 110.0f);
            break;
        case 4:
            temp_f31 = BoardModelRotYGet(lbl_1_bss_64);
            BoardModelRotYSet(temp_r31->work[0], temp_f31);
            BoardModelAttrSet(temp_r31->work[0], 0x40000001);
            BoardModelPosGet(lbl_1_bss_64, &sp8);
            temp_r31->rot.x = arg1->x - sp8.x;
            temp_r31->rot.y = arg1->y - sp8.y;
            temp_r31->rot.z = arg1->z - sp8.z;
            BoardModelLayerSet(temp_r31->work[0], 2);
            break;
        case 5:
            temp_f31 = BoardModelRotYGet(lbl_1_bss_64);
            BoardModelRotYSet(temp_r31->work[0], temp_f31);
            BoardModelAttrSet(temp_r31->work[0], 0x40000001);
            BoardModelPosGet(lbl_1_bss_64, &sp8);
            temp_r31->rot.x = arg1->x - sp8.x;
            temp_r31->rot.y = arg1->y - sp8.y;
            temp_r31->rot.z = arg1->z - sp8.z;
            break;
    }
    return temp_r31;
}

void fn_1_6914(omObjData *arg0)
{
    Vec sp8;

    if (arg0->work[1] != 0) {
        if (arg0->work[2] != 4) {
            BoardModelKill(arg0->work[0]);
            omDelObjEx(boardObjMan, arg0);
            return;
        }
        BoardModelAttrReset(arg0->work[0], 0x40000001);
        BoardModelMotionStartEndSet(arg0->work[0], 0x14, 0x50);
        if (BoardModelMotionEndCheck(arg0->work[0]) != 0) {
            BoardModelKill(arg0->work[0]);
            omDelObjEx(boardObjMan, arg0);
        }
    }
    else {
        switch (arg0->work[2]) {
            case 0:
            case 1:
            case 3:
                if (BoardModelMotionEndCheck(arg0->work[0]) != 0) {
                    BoardModelKill(arg0->work[0]);
                    omDelObjEx(boardObjMan, arg0);
                    return;
                }
                break;
            case 4:
                if (BoardModelMotionTimeGet(arg0->work[0]) >= 20.0f) {
                    BoardModelMotionStartEndSet(arg0->work[0], 0x14, 0x3C);
                }
                BoardModelPosGet(lbl_1_bss_64, &sp8);
                sp8.x += arg0->rot.x;
                sp8.y += arg0->rot.y;
                sp8.z += arg0->rot.z;
                BoardModelPosSetV(arg0->work[0], &sp8);
                break;
            case 5:
                BoardModelPosGet(lbl_1_bss_64, &sp8);
                sp8.x += arg0->rot.x;
                sp8.y += arg0->rot.y;
                sp8.z += arg0->rot.z;
                BoardModelPosSetV(arg0->work[0], &sp8);
                break;
        }
    }
}
