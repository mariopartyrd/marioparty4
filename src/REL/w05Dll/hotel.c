#include "REL/w05Dll.h"

#include "game/hsfdraw.h"
#include "game/audio.h"
#include "game/pad.h"
#include "game/objsub.h"
#include "game/wipe.h"

#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/window.h"

#include "ext_math.h"

// data
s32 lbl_1_data_150[5] = {
    DATA_MAKE_NUM(DATADIR_W05, 0x21), DATA_MAKE_NUM(DATADIR_W05, 0x22), DATA_MAKE_NUM(DATADIR_W05, 0x23),
    DATA_MAKE_NUM(DATADIR_W05, 0x24), DATA_MAKE_NUM(DATADIR_W05, 0x25),
};
s16 lbl_1_data_164 = 0xFFFF;

// bss
s16 lbl_1_bss_28;

void fn_1_13D4(void) {
    Vec sp8;
    ModelData* temp_r31;

    lbl_1_data_164 = BoardModelCreate(lbl_1_data_150[lbl_1_bss_0->unk_04], NULL, 0);
    BoardModelAttrSet(lbl_1_data_164, 0x40000001);
    temp_r31 = &Hu3DData[BoardModelIDGet(lbl_1_data_118)];
    Hu3DMotionExec(BoardModelIDGet(lbl_1_data_118), temp_r31->unk_08, 0.0f, 0);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_118), "hotel1", &sp8);
    BoardModelPosSetV(lbl_1_data_164, &sp8);
}

void fn_1_14D0(void) {
    BoardModelKill(lbl_1_data_164);
}

u32 lbl_1_data_170[4] = { 0, 10, 25, 40 };
s32 lbl_1_data_180 = DATA_MAKE_NUM(DATADIR_W05, 0x0C);

s16 fn_1_14FC(void) {
    s16 var_r31;
    
    for (var_r31 = 0; var_r31 < 4;var_r31++) {
        if (lbl_1_bss_0->unk_00 <= lbl_1_data_170[var_r31]) {
            break;
        }
    }
    return var_r31;
}

void fn_1_155C(void) {
    Vec sp64;
    Vec sp58;
    Vec sp4C;
    Vec sp40;
    Vec sp34;
    Vec sp28;
    char sp18[16];
    Vec spC;
    char sp8[4];
    s32 var_r27;
    ModelData* temp_r25;
    f32 temp_f30;
    f32 temp_f31;
    s16 var_r26;
    s16 temp_r28;
    s16 var_r30;
    u32 var_r31;

    lbl_1_bss_28 = GWSystem.player_curr;
    BoardRollDispSet(0);
    temp_r28 = BoardModelMotionCreate(lbl_1_bss_14[4], lbl_1_data_180);
    temp_f30 = BoardPlayerRotYGet(lbl_1_bss_28);
    BoardPlayerPosGet(lbl_1_bss_28, &sp58);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_118), "hotel1", &sp64);
    temp_f31 = atan2d(sp64.x - sp58.x, sp64.z - sp58.z);
    BoardPlayerMotBlendSet(lbl_1_bss_28, temp_f31, 0xF);
    BoardCameraViewSet(2);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_28) == 0) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    BoardModelPosGet(lbl_1_bss_14[4], &sp4C);

    sp40 = sp28 = sp4C;
    if (sp58.x > sp28.x) {
        sp28.x += 650.0f;
        BoardModelRotYSet(lbl_1_bss_14[4], 90.0f);
    } else {
        sp28.x -= 650.0f;
        BoardModelRotYSet(lbl_1_bss_14[4], -90.0f);
    }
    BoardModelMotionStart(lbl_1_bss_14[4], temp_r28, 0x40000001);
    VECSubtract(&sp28, &sp40, &sp34);
    VECScale(&sp34, &sp34, 0.018518519f);
    
    for (var_r31 = 0; var_r31 < 0x36; var_r31++) {
        VECAdd(&sp40, &sp34, &sp40);
        BoardModelPosSetV(lbl_1_bss_14[4], &sp40);
        HuPrcVSleep();
    }
    BoardModelPosSetV(lbl_1_bss_14[4], &sp28);
    temp_f31 = atan2d(sp58.x - sp28.x, sp58.z - sp28.z);

    while (fn_1_1208(lbl_1_bss_14[4], temp_f31, 10.0f) == 0) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_bss_14[4], 0, 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    var_r30 = BoardPlayerCoinsGet(lbl_1_bss_28);
    sprintf(sp18, "%d", lbl_1_bss_0->unk_00);
    if (var_r30 > 0) {
        if (var_r30 >= 5) {
            var_r27 = MAKE_MESSID(0x27, 0x01);
            var_r30 = 5;
        } else {
            var_r27 = MAKE_MESSID(0x27, 0x02);
        }
        sprintf(sp8, "%d", var_r30);
        BoardWinCreate(2, var_r27, 7);
        BOARD_WIN_MES_SET_PTR(MAKE_MESSID_PTR(sp8), 1);
    } else {
        BoardWinCreate(2, MAKE_MESSID(39, 3), 7);
        BOARD_WIN_MES_SET_PTR(MAKE_MESSID_PTR(sp18), 0);
    }
    BoardWinWait();
    BoardWinKill();
    if (var_r30 > 0) {
        for (var_r31 = 0; (s32) var_r31 < var_r30; var_r31++) {
            BoardPlayerCoinsAdd(lbl_1_bss_28, -1);
            HuAudFXPlay(0xE);
            HuPrcSleep(6);
        }
        HuAudFXPlay(0xF);
        lbl_1_bss_0->unk_00 += var_r30;
        sprintf(sp18, "%d", lbl_1_bss_0->unk_00);
        BoardWinCreate(2, MAKE_MESSID(39, 22), 7);
        BOARD_WIN_MES_SET_PTR(MAKE_MESSID_PTR(sp18), 0);
        BoardWinWait();
        BoardWinKill();
    }

    var_r26 = fn_1_14FC();
    if (var_r26 != lbl_1_bss_0->unk_04) {
        lbl_1_bss_0->unk_04 = var_r26;
        BoardCameraTargetModelSet(lbl_1_data_164);
        BoardCameraOffsetSet(0.0f, 200.0f, 0.0f);
        BoardCameraMotionWait();
        HuPrcSleep(60);
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 48);

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        fn_1_14D0();
        fn_1_13D4();
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 48);

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        HuPrcSleep(60);
        BoardCameraTargetPlayerSet(lbl_1_bss_28);
        BoardCameraMotionWait();
    }
    BoardPlayerMotBlendSet(lbl_1_bss_28, temp_f30, 0xF);
    BoardModelPosGet(lbl_1_bss_14[4], &sp40);
    sp28 = sp4C;
    if (sp58.x > sp28.x) {
        BoardModelRotYSet(lbl_1_bss_14[4], -90.0f);
    } else {
        BoardModelRotYSet(lbl_1_bss_14[4], 90.0f);
    }
    BoardModelMotionStart(lbl_1_bss_14[4], temp_r28, 0x40000001);
    VECSubtract(&sp28, &sp40, &sp34);
    VECScale(&sp34, &sp34, 0.033333335f);
    
    for (var_r31 = 0; var_r31 < 0x1E; var_r31++) {
        VECAdd(&sp40, &sp34, &sp40);
        BoardModelPosSetV(lbl_1_bss_14[4], &sp40);
        HuPrcVSleep();
    }
    BoardModelPosSetV(lbl_1_bss_14[4], &sp28);

    while (fn_1_1208(lbl_1_bss_14[4], 0.0f, 15.0f) == 0) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_bss_14[4], 0, 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    BoardCameraViewSet(1);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_28) == 0) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    BoardModelMotionKill(lbl_1_bss_14[4], temp_r28);
    BoardRollDispSet(1);
}

s32 lbl_1_data_188[4] = {
    DATA_MAKE_NUM(DATADIR_W05, 0x0C), DATA_MAKE_NUM(DATADIR_W05, 0x0E),
    DATA_MAKE_NUM(DATADIR_W05, 0x0F),DATA_MAKE_NUM(DATADIR_W05, 0x10)
};
s32 lbl_1_data_198[2] = { 28, 25 };

void fn_1_1E44(void) {
    char sp84[0x10];
    char sp74[0x10];
    Vec sp68;
    f32 sp64;
    f32 sp60;
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    Vec sp38;
    f32 sp34;
    f32 sp30;
    Vec sp2C;
    s16 sp1C[4][2];
    Vec sp10;
    s16 sp8[4];
    ModelData* temp_r25;
    f32 temp_f31;
    f32 temp;
    s16 temp_r3;
    s16 var_r26;
    s16 var_r27;
    s32 var_r28;
    s32 var_r31;
    s32 temp_r24;
    s32 var_r30;

    lbl_1_bss_28 = GWSystem.player_curr;
    BoardRollDispSet(0);
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp8[var_r31] = BoardModelMotionCreate(lbl_1_bss_14[4], lbl_1_data_188[var_r31]);
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            sp1C[var_r31][var_r30] = BoardPlayerMotionCreate(var_r31, lbl_1_data_198[var_r30] | lbl_1_data_124[GWPlayer[var_r31].character]);
        }
    }
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    BoardPlayerPosGet(lbl_1_bss_28, &sp50);
    BoardModelPosGet(lbl_1_bss_14[4], &sp38);
    sp5C = sp2C = sp38;
    if (sp50.x > sp2C.x) {
        sp2C.x += 520.0f;
        BoardModelRotYSet(lbl_1_bss_14[4], 90.0f);
    } else {
        sp2C.x -= 520.0f;
        BoardModelRotYSet(lbl_1_bss_14[4], -90.0f);
    }
    BoardModelMotionStart(lbl_1_bss_14[4], sp8[0], 0x40000001);
    VECSubtract(&sp2C, &sp5C, &sp44);
    VECScale(&sp44, &sp44, 0.018518519f);

    for (var_r31 = 0; var_r31 < 0x36U; var_r31++) {
        VECAdd(&sp5C, &sp44, &sp5C);
        BoardModelPosSetV(lbl_1_bss_14[4], &sp5C);
        HuPrcVSleep();
    }
    BoardModelPosSetV(lbl_1_bss_14[4], &sp2C);
    temp_f31 = atan2d(sp50.x - sp2C.x, sp50.z - sp2C.z);

    while (fn_1_1208(lbl_1_bss_14[4], temp_f31, 10.0f) == 0) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_bss_14[4], 0, 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    temp_f31 = atan2d(sp2C.x - sp50.x, sp2C.z - sp50.z);
    BoardPlayerMotBlendSet(lbl_1_bss_28, temp_f31, 0xF);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_28) == 0) {
        HuPrcVSleep();
    }
    if (lbl_1_bss_0->unk_00 == 0) {
        BoardWinCreate(2, MAKE_MESSID(39, 5), 7);
        BoardWinWait();
        BoardWinKill();
    } else {
        temp_r3 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x04), NULL, 0);
        BoardModelVisibilitySet(temp_r3, 0);
        BoardModelLayerSet(temp_r3, 2U);
        if (lbl_1_bss_0->unk_00 > BoardPlayerCoinsGet(lbl_1_bss_28)) {
            var_r28 = BoardPlayerCoinsGet(lbl_1_bss_28);
        } else {
            var_r28 = lbl_1_bss_0->unk_00;
        }
        if (var_r28 < 0x14) {
            var_r26 = 6;
        } else if (var_r28 < 0x32) {
            var_r26 = 3;
        } else if (var_r28 < 0x64) {
            var_r26 = 2;
        } else {
            var_r26 = 0;
        }
        sprintf(&sp84, "%d", lbl_1_bss_0->unk_00);
        sprintf(&sp74, "%d", var_r28);
        if (var_r28 == lbl_1_bss_0->unk_00) {
            BoardWinCreate(2, MAKE_MESSID(39, 4), 7);
        } else {
            BoardWinCreate(2, MAKE_MESSID(39, 23), 7);
        }
        BOARD_WIN_MES_SET_PTR(MAKE_MESSID_PTR(sp84), 0);
        BOARD_WIN_MES_SET_PTR(MAKE_MESSID_PTR(sp74), 1);
        BoardWinWait();
        BoardWinKill();
        
        for (var_r31 = 0; var_r31 < var_r28; var_r31++) {
            BoardPlayerCoinsAdd(lbl_1_bss_28, -1);
            HuAudFXPlay(0xE);
            HuPrcSleep(var_r26);
        }
        HuAudFXPlay(0xF);
        HuPrcSleep(0x1E);
        BoardCameraViewSet(1);
        BoardCameraTargetModelSet(lbl_1_data_164);
        BoardCameraMotionWait();
        HuPrcSleep(0x1E);
        omVibrate(lbl_1_bss_28, 0x7FFF, 0xC, 0);
        BoardCameraQuakeSet(0x8C, 250.0f);
        temp_r24 = HuAudFXPlay(0x482);

        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            BoardPlayerMotBlendSet(var_r31, 0, 0xF);
        }

        while (fn_1_1208(lbl_1_bss_14[4], 0.0f, 15.0f) == 0) {
            HuPrcVSleep();
        }
        BoardModelMotionStart(lbl_1_bss_14[4], sp8[1], 0U);

        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            BoardPlayerVoiceEnableSet(var_r31, sp1C[var_r31][0], 0);
            BoardPlayerMotionStart(var_r31, sp1C[var_r31][0], 0);
        }
        HuAudPlayerVoicePlay(lbl_1_bss_28, 0x12E);
        HuPrcSleep(0x5A);
        HuAudFXStop(temp_r24);
        HuAudFXPlay(0x483);
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_118), "tunami1", &sp68);
        BoardModelPosSetV(temp_r3, &sp68);
        BoardModelVisibilitySet(temp_r3, 1);
        BoardModelMotionTimeSet(temp_r3, 0.0f);
        HuPrcSleep(0x1E);
        lbl_1_bss_0->unk_00 = 0;
        
        lbl_1_bss_0->unk_04 = fn_1_14FC();
        BoardModelKill(lbl_1_data_164);
        lbl_1_data_164 = BoardModelCreate(lbl_1_data_150[lbl_1_bss_0->unk_04], NULL, 0);
        BoardModelAttrSet(lbl_1_data_164, 0x40000001);
        temp_r25 = &Hu3DData[BoardModelIDGet(lbl_1_data_118)];
        Hu3DMotionExec(BoardModelIDGet(lbl_1_data_118), temp_r25->unk_08, 0.0f, 0);
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_118), "hotel1", &sp10);
        BoardModelPosSetV(lbl_1_data_164, &sp10);
        BoardModelMotionStart(lbl_1_bss_14[4], sp8[2], 0x40000001U);
        
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            BoardPlayerVoiceEnableSet(var_r31, sp1C[var_r31][0], 1);
            if (var_r31 != lbl_1_bss_28) {
                BoardPlayerVoiceEnableSet(var_r31, 6, 0);
            }
            BoardPlayerMotionStart(var_r31, 6, 0x40000001);
        }
        while (BoardModelMotionTimeGet(temp_r3) < BoardModelMotionMaxTimeGet(temp_r3)) {
            HuPrcVSleep();
        }
        BoardModelKill(temp_r3);
        HuPadRumbleStop(GWPlayer[lbl_1_bss_28].port);
        BoardWinCreate(0, MAKE_MESSID(39, 6), -1);
        BoardWinWait();
        BoardWinKill();
        HuPrcSleep(0x1E);
        BoardModelMotionShiftSet(lbl_1_bss_14[4], sp8[3], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            BoardPlayerMotionShiftSet(var_r31, sp1C[var_r31][1], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
            BoardPlayerVoiceEnableSet(var_r31, 6, 1);
        }
        HuPrcSleep(0x23);
        BoardModelMotionShiftSet(lbl_1_bss_14[4], 0, 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            BoardPlayerMotionShiftSet(var_r31, 1, 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        }
    }
    BoardCameraViewSet(1);
    BoardPlayerPosGet(lbl_1_bss_28, &sp50);
    BoardModelPosGet(lbl_1_bss_14[4], &sp5C);
    sp2C = sp38;
    if (sp50.x > sp2C.x) {
        BoardModelRotYSet(lbl_1_bss_14[4], -90.0f);
    } else {
        BoardModelRotYSet(lbl_1_bss_14[4], 90.0f);
    }
    BoardModelMotionStart(lbl_1_bss_14[4], sp8[0], 0x40000001U);
    VECSubtract(&sp38, &sp5C, &sp44);
    VECScale(&sp44, &sp44, 0.055555556);

    for (var_r31 = 0; var_r31 < 0x12U; var_r31++) {
        VECAdd(&sp5C, &sp44, &sp5C);
        BoardModelPosSetV(lbl_1_bss_14[4], &sp5C);
        HuPrcVSleep();
    }
    BoardModelPosSetV(lbl_1_bss_14[4], &sp38);
    
    while (fn_1_1208(lbl_1_bss_14[4], 0.0f, 15.0f) == 0) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(lbl_1_bss_14[4], 0, 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        BoardModelMotionKill(lbl_1_bss_14[4], sp8[var_r31]);
    }
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            BoardPlayerMotionKill(var_r31, sp1C[var_r31][var_r30]);
        }
    }
    BoardCameraMotionWait();
    BoardPlayerMotBlendSet(lbl_1_bss_28, 0, 0xF);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_28) == 0) {
        HuPrcVSleep();
    }
}
