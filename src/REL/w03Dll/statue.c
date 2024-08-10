#include "dolphin.h"
#include "REL/executor.h"
#include "game/process.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "REL/w03Dll.h"
#include "game/audio.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"
#include "game/hsfman.h"
#include "game/board/main.h"
#include "game/objsub.h"

void fn_1_1358(void);
void fn_1_152C(void);
s32 fn_1_15E8(void);
s32 fn_1_1650(s32 arg0);
void fn_1_19DC(s32 arg0, s32 arg1);
s32 fn_1_1D1C(void);
void fn_1_1ED4(s32 arg0);
void fn_1_20E0(s32 arg0);
void fn_1_26E0(s32 arg0);
void fn_1_2AC0(void);
void fn_1_2818(void);
void fn_1_2A40(void);
void fn_1_2B44(void);
double atan2(double y, double x);

//data
s16 lbl_1_data_280 = -1;
s16 lbl_1_data_282 = -1;
s16 lbl_1_data_284 = -1;
s16 lbl_1_data_286 = -1;
s32 lbl_1_data_288 = -1;

//BSS Extern


//BSS
s8 lbl_1_bss_6F;
s8 lbl_1_bss_6E;
s16 lbl_1_bss_6C;
s16 lbl_1_bss_6A;
s16 lbl_1_bss_68;
GXTexObj lbl_1_bss_48;
char lbl_1_bss_44[4];
char lbl_1_bss_38[12];
void* lbl_1_bss_34;
f32 lbl_1_bss_30;
s8 lbl_1_bss_2C;
Process* lbl_1_bss_28;

void fn_1_12C8(void) {
    BoardRollDispSet(0);
    lbl_1_bss_28 = HuPrcChildCreate(&fn_1_1358, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_28, &fn_1_152C);

    while (lbl_1_bss_28) {
        HuPrcVSleep();
    }

    BoardRollDispSet(1);
}

void fn_1_1358(void) {
    s32 cur_player_index;
    s32 unkC;

    cur_player_index = GWSystem.player_curr;
    unkC = GWPlayer[cur_player_index].space_curr;
    lbl_1_bss_2C = 0;

    if ((BoardSpaceFlagGet(0, GWPlayer[cur_player_index].space_curr) & 0x2000)) {
        lbl_1_bss_6E = 0;
        lbl_1_bss_6C = lbl_1_bss_C[3];
    } else {
        lbl_1_bss_6E = 1;
        lbl_1_bss_6C = lbl_1_bss_C[4];
    }

    if (fn_1_1650(cur_player_index) != 0) {
        if (fn_1_1D1C() != 0) {
            fn_1_1ED4(cur_player_index);
        } else {
            fn_1_20E0(cur_player_index);
        }
        if (lbl_1_bss_2C) {
            sprintf(lbl_1_bss_44, "%d", lbl_1_bss_2C);
            BoardWinCreate(0, MAKE_MESSID(22, 6), -1);
            BoardWinInsertMesSet((s32)lbl_1_bss_44, 0);
            BoardWinWait();
            BoardWinKill();
            lbl_1_bss_0->unk2 = 1 << cur_player_index;
            lbl_1_bss_0->unk0 = lbl_1_bss_2C;
            fn_1_CF4();
        }
        fn_1_26E0(cur_player_index);
        BoardStatusShowSetAll(1);
    }

    BoardPlayerPostTurnHookSet(cur_player_index, &fn_1_15E8);
    BoardWinKill();
    HuPrcEnd();
}

void fn_1_152C(void) {
    BoardConfettiKill();

    if (lbl_1_data_282 != -1) {
        BoardPlayerMotionKill(GWSystem.player_curr, lbl_1_data_282);
        lbl_1_data_282 = -1;
    }

    if (lbl_1_data_280 != -1) {
        BoardPlayerMotionKill(GWSystem.player_curr, lbl_1_data_280);
        lbl_1_data_280 = -1;
    }

    fn_1_2AC0();
    lbl_1_bss_28 = NULL;
}

s32 fn_1_15E8(void) {
    BoardModelVisibilitySet(lbl_1_bss_6C, 1);

    if (lbl_1_data_284 != -1) {
        BoardModelKill(lbl_1_data_284);
        lbl_1_data_284 = -1;
    }

    return 1;
}

s32 fn_1_1650(s32 arg0) {
    Point3d sp38;
    Point3d sp2C;
    Point3d sp20;
    Point3d sp14;
    Point3d sp8;
    f32 temp;
    s32 temp2;

    BoardPlayerIdleSet(arg0);
    
    if (lbl_1_bss_0->unk2) {
        BoardWinCreate(0, MAKE_MESSID(22, 0), -1);
        BoardWinWait();
        BoardWinKill();
        return 0;
    }
    
    temp2 = BoardSpaceLinkFlagSearch(0, GWPlayer[arg0].space_curr, 0x02000000);
    BoardSpacePosGet(0, temp2, &sp38);
    BoardPlayerPosGet(arg0, &sp2C);
    VECSubtract(&sp38, &sp2C, &sp20);
    temp = (atan2(-sp20.x, -sp20.z) / M_PI) * 180.0f;
    BoardPlayerRotYSet(arg0, temp);
    sp14.x = 0.0f;
    sp14.y = 100.0f;
    sp14.z = 0.0f;
    sp8.x = -20.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_6C, &sp8, &sp14, 1360.0f, -1.0f, 21);
    BoardPlayerPosLerpStart(arg0, &sp2C, &sp38, 0x28);

    while (GWPlayer[arg0].moving) {
        HuPrcVSleep();
    }
    
    BoardStatusShowSetAll(0);
    BoardPlayerMotBlendSet(arg0, 0xB4, 0xF);

    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }
    
    BoardPlayerIdleSet(arg0);
    BoardWinCreate(2, MAKE_MESSID(22, 1), 2);
    BoardWinWait();
    BoardWinCreateChoice(0, MAKE_MESSID(22, 2), -1, 0);
    BoardWinAttrSet(0x10);

    if (GWPlayer[arg0].com) {
        if (BoardRandMod(0x64) > 0x32U) {
            BoardComKeySetLeft();
        } else {
            BoardComKeySetRight();
        }
    }

    BoardWinWait();
    lbl_1_bss_6F = BoardWinChoiceGet();
    BoardWinKill();
    fn_1_19DC(arg0, lbl_1_bss_6F);
    BoardFilterFadeInit(0x1E, 0xA0);
    BoardMusStart(1, 0x19, 0x7F, 0);
    HuAudFXPlay(0x435);
    sp8.y = BoardModelRotYGet(lbl_1_bss_6C);
    
    while (BoardDAngleCalcRange(&sp8.y, 180.0f, 2.0f) == 0) {
        BoardModelRotYSet(lbl_1_bss_6C, sp8.y);
        HuPrcVSleep();
    }
    
    HuAudFXPlay(0x445);
    BoardModelRotYSet(lbl_1_bss_6C, 180.0f);
    
    while (BoardMusStatusGet(1) != 0) {
        HuPrcVSleep();
    }
    return 1;
}

s32 lbl_1_data_290[] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 98),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 98),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 98),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 98),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 98),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 98),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 98),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 98)
};

s32 lbl_1_data_2B0[] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 51),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 51),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 51),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 51),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 51),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 51),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 51),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 51)
};

s32 lbl_1_data_2D0[] = {
    0x00000125, 0x00000165, 0x000001A5,
    0x000001E5, 0x00000225, 0x00000265,
    0x000002A5, 0x000002E5
};

s32 lbl_1_data_2F0[] = {
    0x0000012E, 0x0000016E, 0x000001AE,
    0x000001EE, 0x0000022E, 0x0000026E,
    0x000002AE, 0x000002EE
};

void fn_1_19DC(s32 arg0, s32 arg1) {
    s32 temp_r30;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 var_r29;
    f32 temp;

    temp_r30 = GWPlayer[arg0].character;

    if (arg1 != 0) {
        lbl_1_data_282 = BoardPlayerMotionCreate(arg0, lbl_1_data_2B0[temp_r30]);
        lbl_1_bss_6A = 8;
        lbl_1_bss_68 = lbl_1_data_282;
        var_r29 = lbl_1_data_2F0[GWPlayer[arg0].character];
    } else {
        lbl_1_bss_6A = 7;
        lbl_1_bss_68 = 1;
        var_r29 = lbl_1_data_2D0[GWPlayer[arg0].character];
    }

    lbl_1_data_280 = BoardPlayerMotionCreate(arg0, lbl_1_data_290[temp_r30]);
    temp = (180.0f + BoardPlayerRotYGet(arg0));
    BoardPlayerMotBlendSet(arg0, temp, 15);

    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }

    HuAudFXPlay(var_r29);
    BoardPlayerVoiceEnableSet(arg0, lbl_1_bss_6A, 0);
    BoardPlayerMotionShiftSet(arg0, lbl_1_bss_6A, 0.0f, 8.0f, 0);
    HuPrcSleep(9);

    while (BoardPlayerMotionEndCheck(arg0) == 0) {
        HuPrcVSleep();

    }

    HuPrcSleep(60);
    
    if (arg1 != 0) {
        BoardPlayerMotionShiftSet(arg0, lbl_1_bss_68, 0.0f, 8.0f, 0);
        HuPrcSleep(9);
        while (BoardPlayerMotionEndCheck(arg0) == 0) {
            HuPrcVSleep();
        }
    }

    BoardPlayerIdleSet(arg0);
    HuPrcSleep(0x14);
    temp = (180.0f + BoardPlayerRotYGet(arg0));
    BoardPlayerMotBlendSet(arg0, temp, 15);

    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }

    BoardAudSeqPause(0, 1, 1000);
    BoardPlayerMotionShiftSet(arg0, lbl_1_data_280, 0.0f, 10.0f, 0);
    HuPrcSleep(11);

    while (BoardPlayerMotionEndCheck(arg0) == 0) {
        HuPrcVSleep();
    }
}

s32 fn_1_1D1C(void) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 modRand2;
    s32 var_r31;
    s32 temp2;
    s32 modRand;
    s32 prevTurn;
    s32 maxTurn;

    s32 sp8[3] = { 70, 50, 45 };
    s32 sp14[3][3] = {
        {3, 5, 22},
        {5, 10, 35},
        {5, 15, 35}
    };

    while (BoardMusStatusGet(1) != 0) {
        HuPrcVSleep();
    }
    BoardWinCreate(2, MAKE_MESSID(22, 3), 2);
    BoardWinWait();
    BoardWinKill();

    prevTurn = GWSystem.turn - 1;
    maxTurn = GWSystem.max_turn;
    var_r31 = prevTurn / (maxTurn / 3);

    if (var_r31 >= 3) {
        var_r31 = 2;
    }

    modRand = BoardRandMod(100);
    if (modRand < sp8[var_r31] ) {
        return 1;
    }

    modRand2 = BoardRandMod(100 - sp8[var_r31]);
    if (modRand2 < sp14[var_r31][0]) {
        lbl_1_bss_2C = 3;
    } else if (modRand2 < sp14[var_r31][1]) {
        lbl_1_bss_2C = 2;
    } else {
        lbl_1_bss_2C = 1;
    }

    return 0;
}

void fn_1_1ED4(s32 arg0) {
    Point3d spC;
    f32 sp8;

    lbl_1_data_284 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W03, 0x0C), NULL, 0);
    BoardModelVisibilitySet(lbl_1_data_284, 0);
    BoardModelVisibilitySet(lbl_1_bss_6C, 0);
    BoardModelPosGet(lbl_1_bss_6C, &spC);
    BoardModelVisibilitySet(lbl_1_data_284, 1);
    BoardModelPosSetV(lbl_1_data_284, &spC);
    BoardFilterFadeOut(0x1E);
    BoardPlayerPosGet(arg0, &spC);
    spC.y += 700.0f;
    BoardConfettiCreate(&spC, 0x64, 300.0f);
    sp8 = BoardModelRotYGet(lbl_1_bss_6C);
    
    while (BoardDAngleCalcRange(&sp8, 0.0f, 30.0f) == 0) {
        BoardModelRotYSet(lbl_1_data_284, sp8);
        HuPrcVSleep();
    }
    
    omVibrate(arg0, 0xC, 4, 2);
    BoardMusStart(1, 0x1A, 0x7F, 0);
    BoardModelRotYSet(lbl_1_data_284, 0.0f);
    BoardModelRotYSet(lbl_1_bss_6C, 0.0f);

    while (BoardFilterFadePauseCheck() == 0) {
        HuPrcVSleep();
    }

    BoardPlayerIdleSet(arg0);
    
    while (BoardMusStatusGet(1) != 0) {
        HuPrcVSleep();
    }

    BoardAudSeqPause(0, 0, 1000);
    BoardWinCreate(2, MAKE_MESSID(22, 4), 2);
    BoardWinWait();
    BoardWinKill();
    BoardConfettiStop();
}

void fn_1_20E0(s32 arg0) {
    Point3d sp24;
    Point3d sp18;
    Point3d spC;
    f32 sp8;
    f32 var_f31;
    s32 i;

    lbl_1_data_284 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W03, 0x0D), NULL, 0);
    BoardModelVisibilitySet(lbl_1_data_284, 0);
    BoardModelVisibilitySet(lbl_1_bss_6C, 0);
    BoardModelPosGet(lbl_1_bss_6C, &spC);
    BoardModelVisibilitySet(lbl_1_data_284, 1);
    BoardModelPosSetV(lbl_1_data_284, &spC);
    BoardFilterFadeOut(0x1E);
    sp8 = BoardModelRotYGet(lbl_1_bss_6C);

    while (BoardDAngleCalcRange(&sp8, 0.0f, 30.0f) == 0) {
        BoardModelRotYSet(lbl_1_data_284, sp8);
        HuPrcVSleep();
    }

    omVibrate(arg0, 0xC, 4, 2);
    BoardModelRotYSet(lbl_1_data_284, 0.0f);
    BoardModelRotYSet(lbl_1_bss_6C, 0.0f);
    
    while (BoardFilterFadePauseCheck() == 0) {
        HuPrcVSleep();
    }
    
    BoardMusStart(1, 0x1B, 0x7F, 0);
    HuAudFXPlay(0x44A);
    fn_1_2A40();
    lbl_1_bss_30 = 0.0f;
    
    while (lbl_1_bss_30 < 128.0f) {
        HuPrcVSleep();
        lbl_1_bss_30 += 12.0f;
    }
    
    if (lbl_1_bss_30 > 128.0f) {
        lbl_1_bss_30 = 128.0f;
    }

    HuPrcSleep(40);
    lbl_1_bss_30 = 128.0f;
    
    while (lbl_1_bss_30 > 0.0f) {
        HuPrcVSleep();
        lbl_1_bss_30 -= 12.0f;
    }

    if (lbl_1_bss_30 < 0.0f) {
        lbl_1_bss_30 = 0.0f;
    }

    fn_1_2AC0();

    for (i = 0; i < 3; i++) {
        BoardCameraMotionStartEx(-1, NULL, NULL, 680.0f, -1.0f, 13);
        BoardCameraMotionWait();
        BoardCameraMotionStartEx(-1, NULL, NULL, 1360.0f, -1.0f, 13);
        BoardCameraMotionWait();
    }
    
    BoardPlayerIdleSet(arg0);

    while (BoardMusStatusGet(1) != 0) {
        HuPrcVSleep();
    }
    
    BoardAudSeqPause(0, 0, 1000);
    BoardWinCreate(2, MAKE_MESSID(22, 5), 2);
    BoardWinWait();
    BoardCameraQuakeSet(0x8CA0, 100.0f);
    omVibrate(arg0, 0xE10, 4, 2);
    lbl_1_data_288 = HuAudFXPlay(0x436);
    BoardCameraViewSet(1);
    HuPrcSleep(0x3C);
    BoardCameraMotionWait();
    sp24.x = 0.0f;
    sp24.y = 100.0f;
    sp24.z = 0.0f;
    sp18.x = -20.0f;
    sp18.y = 0.0f;
    sp18.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_C[1], &sp18, &sp24, 3000.0f, -1.0f, 60);
    BoardCameraMotionWait();
    omVibrate(arg0, 0x1E, 6, 6);
    HuPrcSleep(0x1E);

    for (var_f31 = 100.0f; var_f31 > 0.0f; var_f31 -= 2.0f) {
        BoardCameraQuakeSet(0xA, var_f31);
        HuPrcVSleep();        
    }
    
    BoardCameraQuakeReset();

    if (lbl_1_data_288 != 0) {
        HuAudFXStop(lbl_1_data_288);
        lbl_1_data_288 = -1;
    }
    
    fn_1_2818();
    omVibrate(arg0, 0xC, 0xC, 0);
    HuAudFXPlay(0x438);
    fn_1_B5C(1);
    HuPrcSleep(0x3C);
    sp24.x = 0.0f;
    sp24.y = 100.0f;
    sp24.z = 0.0f;
    sp18.x = -20.0f;
    sp18.y = 0.0f;
    sp18.z = 0.0f;
    BoardCameraMotionStartEx(lbl_1_bss_6C, &sp18, &sp24, 1360.0f, -1.0f, 60);
    BoardCameraMotionWait();
    HuPrcSleep(0x3C);
}

void fn_1_26E0(s32 arg0) {
    Point3d sp20;
    Point3d sp14;
    Point3d sp8;
    f32 temp;

    BoardSpacePosGet(0, GWPlayer[arg0].space_curr, &sp20);
    BoardPlayerPosGet(arg0, &sp14);
    VECSubtract(&sp20, &sp14, &sp8);
    VECNormalize(&sp8, &sp8);
    temp = (180.0f * (atan2(-sp8.x, -sp8.z) / M_PI));
    BoardPlayerRotYSet(arg0, temp);
    BoardCameraViewSet(1);
    BoardCameraTargetPlayerSet(arg0);
    BoardPlayerPosLerpStart(arg0, &sp14, &sp20, 0x28);

    while (GWPlayer[arg0].moving != 0) {
        HuPrcVSleep();
    }

    BoardCameraMotionWait();
    BoardModelMotionStart(lbl_1_bss_C[1], 0, 0);
    BoardPlayerIdleSet(arg0);
}

void fn_1_2818(void) {
    s16 temp_r29;
    s16 temp_r30;
    s16 j;
    s16 sp8[3] = {0x0002, 0x003E, 0x007A};

    temp_r29 = (4 - lbl_1_bss_2C) * 60;
    BoardModelMotionStart(lbl_1_bss_C[1], 0, 0);

    while (1) {
        temp_r30 = BoardModelMotionTimeGet(lbl_1_bss_C[1]);
        if (temp_r29 > temp_r30) {
            for (j = 0; j < ARRAY_COUNT(sp8); j++) {
                if (temp_r30 == sp8[j]) {
                    HuAudFXPlay(0x446);
                }            
            }
            HuPrcVSleep();
        } else {
            break;
        }        
    }

    BoardModelAttrSet(lbl_1_bss_C[1], 0x40000002);
    HuPrcSleep(0x3C);
}

s32 fn_1_2930(s32 arg0) {
    lbl_1_bss_0->unk0--;

    if (lbl_1_bss_0->unk0 <= 0) {
        lbl_1_bss_0->unk2 = 0;
        lbl_1_bss_0->unk0 = 0;
        fn_1_B5C(0);
        BoardWinCreate(0, MAKE_MESSID(22, 8), -1);
        BoardWinWait();
        BoardWinKill();
        fn_1_CF4();
        return 1;
    }

    sprintf(lbl_1_bss_38, "%d", lbl_1_bss_0->unk0);
    BoardWinCreate(0, MAKE_MESSID(22, 7), -1);
    BoardWinInsertMesSet((s32)lbl_1_bss_38, 1);
    BoardWinWait();
    BoardWinKill();
    fn_1_CF4();
    return 0;
}

void fn_1_2A40(void) {
    lbl_1_bss_30 = 0.0f;
    lbl_1_bss_34 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x96000, MEMORY_DEFAULT_NUM);
    lbl_1_data_286 = Hu3DHookFuncCreate((void*)&fn_1_2B44);
    Hu3DModelLayerSet(lbl_1_data_286, 3);
}

void fn_1_2AC0(void) {
    if (lbl_1_bss_34) {
        HuMemDirectFree(lbl_1_bss_34);
        lbl_1_bss_34 = NULL;
    }

    if (lbl_1_data_286 != -1) {
        Hu3DModelKill(lbl_1_data_286);
        lbl_1_data_286 = -1;
    }
}

void fn_1_2B44(void) {
    Mtx44 sp50;
    Mtx sp20;
    GXColor sp14;
    GXColor sp10;
    GXColor spC;
    u8 sp8;
    GXColor sp1C = {0xFF, 0xFF, 0xFF, 0xFF};
    GXColor sp18 = {0xFF, 0xFF, 0xFF, 0xFF};

    f32 temp_f28 = 0.0f;
    f32 temp_f30 = 640.0f;
    f32 temp_f27 = 0.0f;
    f32 temp_f29 = 480.0f;

    OSf32tou8(&lbl_1_bss_30, &sp18.a);
    GXInvalidateTexAll();
    GXLoadTexObj(&lbl_1_bss_48, GX_TEXMAP0);
    C_MTXOrtho(sp50, temp_f27, temp_f29, temp_f28, temp_f30, 0.0f, 10.0f);
    GXSetProjection(sp50, GX_ORTHOGRAPHIC);
    PSMTXIdentity(sp20);
    GXLoadPosMtxImm(sp20, 0);
    GXSetCurrentMtx(0);
    GXSetViewport(0.0f, 0.0f, temp_f30, 1.0f + temp_f29, 0.0f, 1.0f);
    GXSetScissor(0, 0, temp_f30, (1.0f + temp_f29));
    GXClearVtxDesc();
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, 1, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, sp18);
    GXSetChanMatColor(GX_COLOR0A0, sp18);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_INVDSTCLR, GX_BL_SRCALPHA, GX_LO_NOOP);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_RGBX8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetAlphaUpdate(1);
    GXSetColorUpdate(1);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2u16(temp_f28, temp_f27);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition2u16(temp_f30, temp_f27);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition2u16(temp_f30, temp_f29);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition2u16(temp_f28, temp_f29);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
    GXSetChanMatColor(GX_COLOR0A0, sp1C);
}
