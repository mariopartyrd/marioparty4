#include "REL/w05Dll.h"

#include "game/hsfdraw.h"
#include "game/frand.h"

#include "game/board/model.h"
#include "game/board/player.h"

// data
s32 lbl_1_data_1A8[3] = { DATA_MAKE_NUM(DATADIR_W05, 0x1F), DATA_MAKE_NUM(DATADIR_W05, 0x20), DATA_NUM_LISTEND };
char *lbl_1_data_1C4[2] = { "monkyA", "monkyB"};
s32 lbl_1_data_1CC[3] = { 0x78, 0x6F, 0x70 };

// bss
s16 lbl_1_bss_4E[2];
s16 lbl_1_bss_4C;
s16 lbl_1_bss_4A;
s16 lbl_1_bss_48;
s16 lbl_1_bss_44[2];
Vec lbl_1_bss_38;
s16 lbl_1_bss_30[4];

void fn_1_2B40(void) {
        s32 var_r31;

    BoardModelAttrSet(lbl_1_bss_14[2], 0x40000002);
    BoardModelAttrSet(lbl_1_bss_14[3], 0x40000002);
    BoardModelMotionTimeSet(lbl_1_bss_14[2], 0.0f);
    BoardModelMotionTimeSet(lbl_1_bss_14[3], 0.0f);
    
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_4E[var_r31] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x1E), lbl_1_data_1A8, 0);
        BoardModelAttrSet(lbl_1_bss_4E[var_r31], 0x40000001);
    }
    BoardModelHookSet(lbl_1_bss_14[2], lbl_1_data_1C4[0], lbl_1_bss_4E[0]);
    BoardModelHookSet(lbl_1_bss_14[3], lbl_1_data_1C4[1], lbl_1_bss_4E[1]);
}

void fn_1_2C7C(s32 arg0) {
    Vec spC;
    s32 var_r31;

    lbl_1_bss_4C = GWSystem.player_curr;
    lbl_1_bss_48 = arg0;
    if (lbl_1_bss_48 == 0) {
        lbl_1_bss_4A = lbl_1_bss_14[2];
        spC.x = 150.0f;
        BoardModelPosGet(lbl_1_bss_4A, &lbl_1_bss_38);
        lbl_1_bss_38.x += 140.0f;
    } else {
        lbl_1_bss_4A = lbl_1_bss_14[3];
        spC.x = -150.0f;
        BoardModelPosGet(lbl_1_bss_4A, &lbl_1_bss_38);
        lbl_1_bss_38.x -= 140.0f;
    }
    lbl_1_bss_44[0] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x1C), NULL, 0);
    lbl_1_bss_44[1] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x1D), NULL, 0);
    BoardModelVisibilitySet(lbl_1_bss_44[0], 0);
    BoardModelVisibilitySet(lbl_1_bss_44[1], 0);
    BoardModelAttrSet(lbl_1_bss_44[0], 0x40000001);
    
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_30[var_r31] = BoardPlayerMotionCreate(lbl_1_bss_4C, lbl_1_data_1CC[var_r31] | lbl_1_data_124[GWPlayer[lbl_1_bss_4C].character]);
    }
    BoardRollDispSet(0);
    BoardPlayerIdleSet(lbl_1_bss_4C);
    spC.y = 100.0f;
    spC.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_4A, NULL, &spC, 2300.0f, -1.0f, 0x1E);
    BoardCameraRotSet(-33.0f, 0.0f);
    BoardCameraMotionWait();
    HuAudFXPlay(0x48A);
    BoardWinCreate(0, MAKE_MESSID(39, 24), -1);
    BoardWinWait();
    BoardWinKill();
    fn_1_3044();
    fn_1_3430();
    if (GWPlayer[lbl_1_bss_4C].bowser_suit != 0) {
        fn_1_3D88();
    } else {
        fn_1_3514();
    }
    BoardPlayerIdleSet(lbl_1_bss_4C);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    BoardRollDispSet(1);
    
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        BoardModelKill(lbl_1_bss_44[var_r31]);
    }
    
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        BoardPlayerMotionKill(lbl_1_bss_4C, lbl_1_bss_30[var_r31]);
    }
}

void fn_1_3044(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 temp_f30;
    f32 var_f29;
    f32 temp_f28;
    f32 var_f31;

    HuPrcSleep(0x1E);
    BoardModelMotionStart(lbl_1_bss_4E[lbl_1_bss_48], 1, 0);
    BoardModelAttrReset(lbl_1_bss_4A, 0x40000002);
    BoardModelMotionTimeSet(lbl_1_bss_4A, 0.0f);
    HuPrcSleep(0x88);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_4A), lbl_1_data_1C4[lbl_1_bss_48], &sp20);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_4E[lbl_1_bss_48]), "bakawa1", &sp14);
    VECAdd(&sp20, &sp14, &sp14);
    BoardModelPosSetV(lbl_1_bss_44[0], &sp14);
    BoardModelVisibilitySet(lbl_1_bss_44[0], 1);
    BoardModelMotionTimeSet(lbl_1_bss_44[0], 0.0f);
    HuAudFXPlay(0x48C);
    VECSubtract(&lbl_1_bss_38, &sp14, &sp8);
    sp8.y = 0.0f;
    VECNormalize(&sp8, &sp8);
    VECScale(&sp8, &sp8, 8.0f);
    temp_f30 = 11.0f;
    var_f31 = 0.0f;
    
    while (1) {
        sp8.y = (temp_f30 - (0.075 * (0.25f * (var_f31 * var_f31))));
        var_f31 += 1.0f;
        VECAdd(&sp14, &sp8, &sp14);
        VECSubtract(&lbl_1_bss_38, &sp14, &sp20);
        sp20.y = 0.0f;
        var_f29 = VECMag(&sp20);
        if (var_f29 <= 8.0f) {
            sp14.x = lbl_1_bss_38.x;
            sp14.z = lbl_1_bss_38.z;
            sp8.x = sp8.z = 0.0f;
        }
        if (sp14.y <= lbl_1_bss_38.y) {
            sp14.y = lbl_1_bss_38.y;
            BoardModelVisibilitySet(lbl_1_bss_44[0], 0);
            BoardModelVisibilitySet(lbl_1_bss_44[1], 1);
            BoardModelPosSetV(lbl_1_bss_44[1], &sp14);
            BoardModelMotionTimeSet(lbl_1_bss_44[1], 0.0f);
            break;
        } else {
            BoardModelPosSetV(lbl_1_bss_44[0], &sp14);
            if (BoardModelMotionTimeGet(lbl_1_bss_4E[lbl_1_bss_48]) >= BoardModelMotionMaxTimeGet(lbl_1_bss_4E[lbl_1_bss_48])) {
                BoardModelMotionStart(lbl_1_bss_4E[lbl_1_bss_48], 0, 0x40000001);
            }
            HuPrcVSleep();
        }
    }
}

void fn_1_3430(void) {
    if (GWPlayer[lbl_1_bss_4C].bowser_suit == 0) {
        BoardPlayerMotionShiftSet(lbl_1_bss_4C, lbl_1_bss_30[2], 0.0f, 8.0f, 0);
        HuPrcSleep(8);

        while (BoardPlayerMotionEndCheck(lbl_1_bss_4C) == 0) {
            HuPrcVSleep();
        }
        BoardPlayerMotionStart(lbl_1_bss_4C, lbl_1_bss_30[1], 0x40000001);
        HuPrcSleep(0x5A);
        return;
    }
    HuPrcSleep(0x2D);
}

void fn_1_3514(void) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s32 var_r30;
    s32 var_r31;

    BoardPlayerPosGet(lbl_1_bss_4C, &sp2C);
    BoardPlayerMotionShiftSet(lbl_1_bss_4C, 4, 0.0f, 5.0f, 0);
    VECSubtract(&lbl_1_bss_38, &sp2C, &sp20);
    sp20.y = 0.0f;
    VECNormalize(&sp20, &sp20);
    VECScale(&sp20, &sp20, 7.2f);
    var_f30 = 10.0f;
    var_f31 = 0.0f;
    while (1) {
        sp20.y = (var_f30 - (0.075f * (0.25f * (var_f31 * var_f31))));
        var_f31 += 1.0f;
        VECAdd(&sp2C, &sp20, &sp2C);
        VECSubtract(&lbl_1_bss_38, &sp2C, &sp14);
        sp14.y = 0.0f;
        var_f29 = VECMag(&sp14);
        if (var_f29 <= 7.2f) {
            sp2C.x = lbl_1_bss_38.x;
            sp2C.z = lbl_1_bss_38.z;
            sp20.x = sp20.z = 0.0f;
        }
        if (sp2C.y <= lbl_1_bss_38.y) {
            sp2C.y = lbl_1_bss_38.y;
            BoardPlayerMotionStart(lbl_1_bss_4C, lbl_1_bss_30[0], 0);
            break;
        } else {
            BoardPlayerPosSetV(lbl_1_bss_4C, &sp2C);
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x48B);
    HuAudPlayerVoicePlay(lbl_1_bss_4C, 0x123);
    HuPrcChildCreate(fn_1_3E8C, 0x2001, 0x1000, 0, boardMainProc);
    HuAudFXPlay(0x48A);
    BoardModelMotionStart(lbl_1_bss_4E[lbl_1_bss_48], 2, 0);
    var_r31 = BoardSpaceLinkFlagSearch(0, GWPlayer[lbl_1_bss_4C].space_curr, 0x100);
    if (frandBool() != 0) {
        var_r31 = BoardSpaceLinkFlagSearch(0, var_r31, 0x200);
    } else {
        var_r31 = BoardSpaceLinkFlagSearch(0, var_r31, 0x400);
    }
    BoardSpacePosGet(0, var_r31, &sp8);
    VECSubtract(&sp8, &sp2C, &sp20);
    sp20.y = 0.0f;
    VECNormalize(&sp20, &sp20);
    VECScale(&sp20, &sp20, 10.0f);
    var_f30 = 9.0f;
    var_f31 = 0.0f;
    while (1) {
        sp20.y = var_f30 - (0.075f * (0.25f * (var_f31 * var_f31)));
        var_f31 += 1.0f;
        VECAdd(&sp2C, &sp20, &sp2C);
        VECSubtract(&sp8, &sp2C, &sp14);
        sp14.y = 0.0f;
        var_f29 = VECMag(&sp14);
        if (var_f29 <= 10.0f) {
            sp2C.x = sp8.x;
            sp2C.z = sp8.z;
            sp20.x = sp20.z = 0.0f;
        }
        if (sp2C.y <= sp8.y) {
            sp2C.y = sp8.y;
            omVibrate(lbl_1_bss_4C, 0xC, 4, 2);
            break;
        }
        BoardPlayerPosSetV(lbl_1_bss_4C, &sp2C);
        if (BoardModelMotionTimeGet(lbl_1_bss_4E[lbl_1_bss_48]) >= BoardModelMotionMaxTimeGet(lbl_1_bss_4E[lbl_1_bss_48])) {
            BoardModelMotionStart(lbl_1_bss_4E[lbl_1_bss_48], 0, 0x40000001);
        }
        HuPrcVSleep();
    }
    var_f30 = 10.0f;
    var_f31 = 0.0f;
    if (BoardPlayerSizeGet(lbl_1_bss_4C) == 2) {
        HuAudFXPlay(0x490);
    } else if (BoardPlayerSizeGet(lbl_1_bss_4C) == 1) {
        HuAudFXPlay(0x48F);
    } else {
        HuAudPlayerVoicePlay(lbl_1_bss_4C, 0x119);
    }
    while (1) {
        sp20.y = var_f30 - (0.18333334f * (0.25f * (var_f31 * var_f31)));
        var_f31 += 1.0f;
        sp2C.y += sp20.y;
        if (sp2C.y <= sp8.y) {
            var_f30 = 0.25f * -sp20.y;
            var_f31 = 0.0f;
            sp2C.y = sp8.y;
            if (BoardPlayerSizeGet(lbl_1_bss_4C) == 2) {
                OSReport("big se\n");
                HuAudFXPlay(0x490);
            } else {
                if (BoardPlayerSizeGet(lbl_1_bss_4C) == 1) {
                    OSReport("small se\n");
                    HuAudFXPlay(0x48F);
                } else {
                    OSReport("normal se\n");
                    HuAudPlayerVoicePlay(lbl_1_bss_4C, 0x119);
                }
            }
        }
        BoardPlayerPosSetV(lbl_1_bss_4C, &sp2C);
        if (!(fabs(var_f30) < 5.0)) {
            if (BoardModelMotionTimeGet(lbl_1_bss_4E[lbl_1_bss_48]) >= BoardModelMotionMaxTimeGet(lbl_1_bss_4E[lbl_1_bss_48])) {
                BoardModelMotionStart(lbl_1_bss_4E[lbl_1_bss_48], 0, 0x40000001U);
            }
            HuPrcVSleep();
        } else {
            BoardPlayerMotionShiftSet(lbl_1_bss_4C, 6, 0.0f, 8.0f, 0x40000001U);
            break;
        }
    }

    var_r30 = 0x44;
    while (var_r30--, var_r30 != 0) {
        if (BoardModelMotionTimeGet(lbl_1_bss_4E[lbl_1_bss_48]) >= BoardModelMotionMaxTimeGet(lbl_1_bss_4E[lbl_1_bss_48])) {
            BoardModelMotionStart(lbl_1_bss_4E[lbl_1_bss_48], 0, 0x40000001U);
        }
        HuPrcVSleep();
    }
    GWPlayer[lbl_1_bss_4C].space_curr = var_r31;
}

void fn_1_3D88(void) {
    s32 temp_r3;

    temp_r3 = BoardSpaceLinkFlagSearch(0, GWPlayer[lbl_1_bss_4C].space_curr, 0x100U);
    BoardPlayerMoveBetween(lbl_1_bss_4C, GWPlayer[lbl_1_bss_4C].space_curr, temp_r3);
    GWPlayer[lbl_1_bss_4C].space_curr = temp_r3;
    HuAudFXPlay(0x48B);
    HuPrcChildCreate(fn_1_3E8C, 0x2001U, 0x1000U, 0, boardMainProc);
    BoardPlayerIdleSet(lbl_1_bss_4C);
    BoardWinCreate(0, MAKE_MESSID(39, 25), -1);
    BoardWinWait();
    BoardWinKill();
}

void fn_1_3E8C(void) {
    Vec sp14;
    Vec sp8;
    s32 i;

    BoardModelPosGet(lbl_1_bss_44[1], &sp14);
    sp8.z = 0.0f;
    sp8.y = 10.0f;
    if (lbl_1_bss_48 == 0) {
        sp8.x = -25.0f;
    } else {
        sp8.x = 25.0f;
    }
    for (i = 0; i < 60; i++) {
        VECAdd(&sp14, &sp8, &sp14);
        sp8.y -= 0.625f;
        BoardModelPosSetV(lbl_1_bss_44[1], &sp14);
        HuPrcVSleep();        
    }
    HuPrcEnd();
}
