#include "REL/w05Dll.h"

#include "game/hsfdraw.h"
#include "game/audio.h"
#include "game/objsub.h"
#include "game/frand.h"
#include "game/chrman.h"
#include "game/pad.h"
#include "game/minigame_seq.h"

#include "game/board/model.h"
#include "game/board/window.h"
#include "game/board/audio.h"

s16 lbl_1_bss_102[3];
s16 lbl_1_bss_100;
s16 lbl_1_bss_FE;
s16 lbl_1_bss_D6[20];
s16 lbl_1_bss_D4;
omObjData* lbl_1_bss_D0;
omObjData* lbl_1_bss_CC;
omObjData* lbl_1_bss_C8;
s16 lbl_1_bss_C6;
s16 lbl_1_bss_C4;
s16 lbl_1_bss_C2;
s16 lbl_1_bss_C0;
u32 lbl_1_bss_BC;
s32 lbl_1_bss_B8;

char *lbl_1_data_464[3] = { "gyoei", "gyoei1", "gyoei2" };
s32 lbl_1_data_470[3] = { 0x7B, 0x7C, 0x7D };
s32 lbl_1_data_47C[3] = { 0x00790016, 0x00790017, 0x00790018 };
char *lbl_1_data_494[3] = { "uo", "uo1", "uo2" };

void fn_1_9680(void) {
    BoardModelAttrSet(lbl_1_bss_14[1], 0x40000002U);
}

void fn_1_96B4(void) {
    BoardModelAttrReset(lbl_1_bss_14[1], 0x40000002);
    BoardModelMotionTimeSet(lbl_1_bss_14[1], 0.0f);

    while (BoardModelMotionTimeGet(lbl_1_bss_14[1]) < 60.0f) {
        HuPrcVSleep();
    }
    BoardModelAttrSet(lbl_1_bss_14[1], 0x40000001);
    BoardModelMotionStartEndSet(lbl_1_bss_14[1], 0x3C, 0x64);
}

void fn_1_9760(void) {
    BoardModelAttrReset(lbl_1_bss_14[1], 0x40000001);
    BoardModelMotionStartEndSet(lbl_1_bss_14[1], 0, 0xA0);
}

void fn_1_97AC(void) {
    Vec sp8;
    s32 var_r31;

    lbl_1_bss_C0 = GWSystem.player_curr;
    
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_102[var_r31] = BoardPlayerMotionCreate(lbl_1_bss_C0, lbl_1_data_470[var_r31] | lbl_1_data_124[GWPlayer[lbl_1_bss_C0].character]);
    }
    sp8.x = sp8.y = sp8.z = 1.0f;
    lbl_1_bss_100 = BoardModelCreate(0x790015, NULL, 0);
    BoardModelScaleSetV(lbl_1_bss_100, &sp8);
    BoardModelVisibilitySet(lbl_1_bss_100, 0);
    lbl_1_bss_D4 = BoardModelCreate(0x79002C, NULL, 0);
    BoardModelVisibilitySet(lbl_1_bss_D4, 0);
    lbl_1_bss_C2 = frandmod(3U);
    lbl_1_bss_FE = BoardModelCreate(lbl_1_data_47C[lbl_1_bss_C2], NULL, 0);
    BoardModelVisibilitySet(lbl_1_bss_FE, 0);
    
    for (var_r31 = 0; var_r31 < 0x14; var_r31++) {
        lbl_1_bss_D6[var_r31] = BoardModelCreate(0x7000A, NULL, 1);
        BoardModelVisibilitySet(lbl_1_bss_D6[var_r31], 0);
    }
    BoardPlayerPostTurnHookSet(lbl_1_bss_C0, (s32 (*)())fn_1_9B74);
    lbl_1_bss_CC = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, fn_1_9A68);
    lbl_1_bss_D0 = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, fn_1_9C24);
    lbl_1_bss_C6 = 0;
    lbl_1_bss_C4 = 0;
}

void fn_1_9A68(omObjData* arg0) {
    if ((lbl_1_bss_C4 != 0) && (BoardMGDoneFlagGet() == 1)) {
        fn_1_9AF0();
        omDelObjEx(boardObjMan, arg0);
    }
}

void fn_1_9AC0(void) {
    lbl_1_bss_C4 = 1;
    BoardMGExit();
}

void fn_1_9AF0(void) {
    s32 var_r31;

    omDelObjEx(boardObjMan, lbl_1_bss_D0);
    
    for (var_r31 = 0; var_r31 < 0x14; var_r31++) {
        BoardModelKill(lbl_1_bss_D6[var_r31]);
    }
    BoardModelKill(lbl_1_bss_D4);
    BoardMGDoneFlagSet(0);
}

void fn_1_9B74(void) {
    HsfObject *var_r31;
    omDelObjEx(boardObjMan, lbl_1_bss_C8);
    BoardModelKill(lbl_1_bss_FE);
    var_r31 = Hu3DModelObjPtrGet(BoardModelIDGet(lbl_1_bss_14[1]), lbl_1_data_464[lbl_1_bss_B8]);
    var_r31->type = lbl_1_bss_BC;
    BoardModelAttrReset(lbl_1_bss_14[1], 0x40000004);
}

void fn_1_9C24(omObjData* arg0) {
    if (arg0->work[0] == 0) {
        arg0->work[0] = MGSeqCreate(3, 0);
        return;
    }
    if (MGSeqStatGet(arg0->work[0]) == 0) {
        arg0->func = fn_1_9D0C;
    }
}

void fn_1_9C98(dataCopy2* arg0) {
    Vec sp8;
    Vec temp_r4;

    sp8 = arg0->unk_0C[arg0->unk_08];
    sp8.y += 50.0f;
    BoardModelPosSetV(arg0->unk_0A, &sp8);
}

void fn_1_9D0C(omObjData* arg0) {
    Vec sp1C;
    Vec sp10;
    f32 sp8[2];
    s32 var_r30;
    dataCopy2* temp_r31;

    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x34, 0x10000000);
    temp_r31 = arg0->data;
    temp_r31->unk_02 = 5;
    temp_r31->unk_04 = 0x3C;
    temp_r31->unk_00 = MGSeqCreate(1, temp_r31->unk_02, 0x120, 0x40);
    HuWinMesMaxSizeGet(1, sp8, 0x27000E);
    temp_r31->unk_06 = HuWinCreate(-10000.0f, 368.0f, sp8[0], sp8[1], 0);
    HuWinMesSet(temp_r31->unk_06, 0x27000E);
    HuWinBGTPLvlSet(temp_r31->unk_06, 0.0f);
    HuWinMesSpeedSet(temp_r31->unk_06, 0);
    temp_r31->unk_08 = 1;
    temp_r31->unk_30 = frandmod(0x1EU) + 15;
    temp_r31->unk_32 = 0;

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[1]), lbl_1_data_494[var_r30], &temp_r31->unk_0C[var_r30]);
    }
    temp_r31->unk_0A = BoardModelCreate(0x790019, NULL, 0);
    BoardModelAttrSet(temp_r31->unk_0A, 0x40000001);
    sp1C.x = sp1C.y = sp1C.z = 1.5f;
    BoardModelScaleSetV(temp_r31->unk_0A, &sp1C);
    sp10 = temp_r31->unk_0C[temp_r31->unk_08];
    sp10.y += 50.0f;
    BoardModelPosSetV(temp_r31->unk_0A, &sp10);
    arg0->func = fn_1_9F24;
}

void fn_1_9F24(omObjData* arg0) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    u16 spA;
    s16 sp8;
    f32 var_f31;
    u16 temp_r29;
    dataCopy2* temp_r31;

    temp_r31 = arg0->data;
    if (--temp_r31->unk_04 == 0) {
        temp_r31->unk_04 = 0x3C;
        if (--temp_r31->unk_02 >= 0) {
            MGSeqParamSet(temp_r31->unk_00, 1, temp_r31->unk_02);
        }
    }
    BoardPlayerPosGet(lbl_1_bss_C0, &sp24);
    temp_r29 = GWPlayer[lbl_1_bss_C0].port;
    if (GWPlayer[lbl_1_bss_C0].com != 0) {
        fn_1_B2B0(arg0, &spA, &sp8);
    } else {
        sp8 = HuPadDStkRep[temp_r29];
        spA = HuPadBtnDown[temp_r29];
    }
    if (((spA & 0x100) != 0) || (temp_r31->unk_02 < 0)) {
        HuAudFXPlay(2);
        MGSeqParamSet(temp_r31->unk_00, 2, -1);
        HuWinKill(temp_r31->unk_06);
        BoardModelKill(temp_r31->unk_0A);
        BoardPlayerMotionStart(lbl_1_bss_C0, lbl_1_bss_102[0], 0);
        BoardPlayerMotionSpeedSet(lbl_1_bss_C0, 0.5f);
        arg0->func = fn_1_A224;
    } else if ((temp_r31->unk_08 != 0) && ((sp8 & 1) != 0)) {
        HuAudFXPlay(0);
        temp_r31->unk_08--;
    } else if ((temp_r31->unk_08 != 2) && ((sp8 & 2) != 0)) {
        HuAudFXPlay(0);
        temp_r31->unk_08++;
    }
    sp18 = temp_r31->unk_0C[temp_r31->unk_08];
    var_f31 = (180.0 * (atan2((sp18.x - sp24.x), (sp18.z - sp24.z)) / M_PI));
    BoardPlayerRotYSet(lbl_1_bss_C0, var_f31);
    spC = temp_r31->unk_0C[temp_r31->unk_08];
    spC.y += 50.0f;
    BoardModelPosSetV(temp_r31->unk_0A, &spC);
}

void fn_1_A224(omObjData* arg0) {
    Vec sp14;
    Vec sp8;
    f32 temp_f31;

    temp_f31 = BoardPlayerMotionMaxTimeGet(lbl_1_bss_C0);
    if (BoardPlayerMotionTimeGet(lbl_1_bss_C0) >= temp_f31) {
        HuAudFXPlay(0x350);
        BoardPlayerPosGet(lbl_1_bss_C0, &sp14);
        Hu3DModelObjPosGet(BoardModelIDGet(BoardPlayerModelGet(lbl_1_bss_C0)), "a-itemhook-r", &sp8);
        sp8.x -= 20.0f;
        sp8.y += 25.0f;
        sp8.z += 80.0f;
        CharModelLayerSetAll(7);
        CharModelEffectCreate(-1, &sp8);
        BoardModelVisibilitySet(lbl_1_bss_100, 1);
        BoardModelMotionTimeSet(lbl_1_bss_100, 0.0f);
        BoardModelAttrSet(lbl_1_bss_100, 0x40000002);
        BoardModelHookSet(BoardPlayerModelGet(lbl_1_bss_C0), "a-itemhook-r", lbl_1_bss_100);
        BoardModelMotionSpeedSet(lbl_1_bss_100, 1.5f);
        BoardPlayerMotionStart(lbl_1_bss_C0, lbl_1_bss_102[1], 0);
        BoardPlayerMotionSpeedSet(lbl_1_bss_C0, 0.5f);
        switch (lbl_1_bss_C2) {
        case 0:
            omVibrate(lbl_1_bss_C0, 0x7FFF, 0xC, 0);
            break;
        case 1:
            omVibrate(lbl_1_bss_C0, 0x7FFF, 4, 2);
            break;
        case 2:
            omVibrate(lbl_1_bss_C0, 0x7FFF, 6, 6);
            break;
        }
        arg0->func = fn_1_A4F8;
    }
}

void fn_1_A4F8(omObjData* arg0) {
    f32 temp_f31;

    temp_f31 = BoardPlayerMotionMaxTimeGet(lbl_1_bss_C0);
    if ((6.0f + BoardPlayerMotionTimeGet(lbl_1_bss_C0)) >= temp_f31) {
        BoardModelMotionTimeSet(lbl_1_bss_100, 0.0f);
        BoardModelAttrReset(lbl_1_bss_100, 0x40000002);
        arg0->func = fn_1_A5B0;
    }
}

void fn_1_A5B0(omObjData* arg0) {
    Vec sp14;
    Vec sp8;
    HsfObject* temp_r28;
    dataCopy2* temp_r30;
    omObjData* temp_r29;
    Vec* temp_r31;
    f32 temp_f30;
    f32 var_f31;

    temp_r30 = arg0->data;
    temp_f30 = BoardModelMotionMaxTimeGet(lbl_1_bss_100);
    if (BoardModelMotionTimeGet(lbl_1_bss_100) >= temp_f30) {
        BoardAudSeqFadeOut(1, 0x64);
        HuAudFXPlay(0x485);
        temp_r28 = Hu3DModelObjPtrGet(BoardModelIDGet(lbl_1_bss_14[1]), lbl_1_data_464[temp_r30->unk_08]);
        lbl_1_bss_BC = temp_r28->type;
        lbl_1_bss_B8 = temp_r30->unk_08;
        temp_r28->type = -1;
        BoardModelAttrSet(lbl_1_bss_100, 0x40000004);
        HuPadRumbleStop(GWPlayer[lbl_1_bss_C0].port);
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[1]), lbl_1_data_494[temp_r30->unk_08], &sp14);
        BoardModelPosSetV(lbl_1_bss_FE, &sp14);
        BoardModelAttrSet(lbl_1_bss_FE, 0x40000001);
        BoardModelVisibilitySet(lbl_1_bss_FE, 1);
        sp8.x = sp8.y = sp8.z = 0.8f;
        BoardModelScaleSetV(lbl_1_bss_D4, &sp8);
        BoardModelPosSetV(lbl_1_bss_D4, &sp14);
        BoardModelVisibilitySet(lbl_1_bss_D4, 1);
        BoardModelMotionTimeSet(lbl_1_bss_D4, 110.0f);
        lbl_1_bss_C8 = temp_r29 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_B3C4);
        temp_r29->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0xC, 0x10000000);
        temp_r31 = temp_r29->data;
        lbl_1_bss_C8->work[1] = 1;
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[1]), "fish", &sp14);
        BoardModelPosGet(lbl_1_bss_FE, &sp8);
        sp14.y = sp8.y;
        VECSubtract(&sp14, &sp8, temp_r31);
        var_f31 = VECMag(temp_r31);
        VECNormalize(temp_r31, temp_r31);
        var_f31 /= 38.0f;
        VECScale(temp_r31, temp_r31, var_f31);
        temp_r31->y = 25.0f;
        temp_r29->trans.x = var_f31;
        BoardPlayerMotionStart(lbl_1_bss_C0, lbl_1_bss_102[2], 0);
        BoardPlayerMotionSpeedSet(lbl_1_bss_C0, 0.5f);
        BoardModelAttrReset(lbl_1_bss_14[1], 0x40000001);
        BoardModelMotionStartEndSet(lbl_1_bss_14[1], 0, 0xA0);
        arg0->func = fn_1_A990;
        return;
    }
    var_f31 = BoardModelMotionSpeedGet(lbl_1_bss_100);
    var_f31 -= 0.1f;
    if (var_f31 < 1.0f) {
        var_f31 = 1.0f;
    }
    BoardModelMotionSpeedSet(lbl_1_bss_100, var_f31);
}

void fn_1_A990(omObjData* arg0) {
    Vec sp8;
    Process *var_r31;

    if (BoardModelMotionTimeGet(lbl_1_bss_100) <= 0.0f) {
        Hu3DModelObjPosGet(BoardModelIDGet(BoardPlayerModelGet(lbl_1_bss_C0)), "a-itemhook-r", &sp8);
        sp8.x += 20.0f;
        sp8.y += 25.0f;
        sp8.z += 80.0f;
        CharModelLayerSetAll(7);
        HuAudFXPlay(0x351);
        CharModelEffectCreate(-1, &sp8);
        BoardModelHookReset(BoardPlayerModelGet(lbl_1_bss_C0));
        BoardModelKill(lbl_1_bss_100);
        var_r31 = HuPrcCreate(fn_1_AB24, 0x2004, 0x1800, 0);
        var_r31->user_data = arg0;
        arg0->func = NULL;
    }
}

s16 lbl_1_data_4B2[3] = { 20, 10, 5 };
s32 lbl_1_data_4B8[3] = { 0x00270013, 0x00270014, 0x00270015 };

void fn_1_AB24(void) {
    Vec sp124[20];
    Vec sp34[20];
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    void *spC;
    char sp8;
    f32 var_f31;
    omObjData *temp_r30;
    s32 var_r29;
    s32 var_r31;
    f32 var_f30;
    Vec* temp_r4;

    temp_r30 = HuPrcCurrentGet()->user_data;
    spC = temp_r30->data;
    BoardPlayerPosGet(lbl_1_bss_C0, &sp28);
    BoardModelPosGet(lbl_1_bss_14[5], &sp1C);
    var_f30 = (180.0 * (atan2((sp1C.z - sp28.z), (sp1C.x - sp28.x)) / M_PI));
    BoardPlayerMotBlendSet(lbl_1_bss_C0, var_f30, 0xF);
    
    while (BoardPlayerMotBlendCheck(lbl_1_bss_C0) == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);
    lbl_1_bss_C6 = lbl_1_data_4B2[lbl_1_bss_C2];
    BoardAudSeqPause(0, 0, 1000);
    sprintf(&sp8, "%d", lbl_1_bss_C6);
    BoardWinCreate(2, MAKE_MESSID(39, 17), 7);
    BoardWinInsertMesSet((u32)&sp8, 0);
    BoardWinInsertMesSet(lbl_1_data_4B8[lbl_1_bss_C2], 1);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerMotBlendSet(lbl_1_bss_C0, 0, 0xF);
    
    while (BoardPlayerMotBlendCheck(lbl_1_bss_C0) == 0) {
        HuPrcVSleep();
    }
    BoardPlayerPosGet(lbl_1_bss_C0, &sp28);
    
    for (var_r31 = 0; var_r31 < lbl_1_bss_C6; var_r31++) {
        BoardModelVisibilitySet(lbl_1_bss_D6[var_r31], 1);
        sp124[var_r31] = sp28;
        sp124[var_r31].y += (800.0f + (var_r31 * 0x78));
        sp124[var_r31].x += (-25.0f + (0.003921569f * (50.0f * (s32)(u8)frand())));
        sp124[var_r31].z += (-25.0f + (0.003921569f * (50.0f * (s32)(u8)frand())));
        sp34[var_r31].x = sp34[var_r31].z = 0.0f;
        sp34[var_r31].y = 0.003921569f * (360.0f * (s32)(u8)frand());
        BoardModelPosSetV(lbl_1_bss_D6[var_r31], &sp124[var_r31]);
        BoardModelRotSetV(lbl_1_bss_D6[var_r31], &sp34[var_r31]);
    }
    var_f31 = -1.0f;
    var_r29 = 0;
    
    while (1) {
        for (var_r31 = 0; var_r31 < lbl_1_bss_C6; var_r31++) {
            if (var_r31 >= var_r29) {
                sp124[var_r31].y += var_f31;
                BoardModelPosSetV(lbl_1_bss_D6[var_r31], &sp124[var_r31]);
                sp34[var_r31].y += 45.0f;
                if (sp34[var_r31].y >= 360.0f) {
                    sp34[var_r31].y -= 360.0f;
                }
                BoardModelRotSetV(lbl_1_bss_D6[var_r31], &sp34[var_r31]);
                if (sp124[var_r31].y <= (80.0f + sp28.y)) {
                    sp10 = sp124[var_r31];
                    CharModelCoinEffectCreate(1, &sp10);
                    BoardModelVisibilitySet(lbl_1_bss_D6[var_r31], 0);
                    var_r29++;
                    BoardPlayerCoinsAdd(lbl_1_bss_C0, 1);
                    HuAudFXPlay(7);
                    omVibrate(lbl_1_bss_C0, 0xC, 6, 6);
                }
            }
        }
        var_f31 *= 1.05f;
        if (var_f31 < -20.0f) {
            var_f31 = -20.0f;
        }
        if (var_r29 == lbl_1_bss_C6) {
            BoardPlayerMotionShiftSet(lbl_1_bss_C0, 7, 0.0f, 10.0f, 0);
            break;
        } else {
            HuPrcVSleep();
        }
    }
    
    while (BoardPlayerMotionEndCheck(lbl_1_bss_C0) == 0) {
        HuPrcVSleep();
    }
    BoardWinCreate(2, MAKE_MESSID(39, 18), 7);
    BoardWinWait();
    BoardWinKill();
    temp_r30->func = fn_1_B214;
    HuPrcEnd();
}

void fn_1_B214(omObjData* arg0) {
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        BoardPlayerMotionKill(lbl_1_bss_C0, lbl_1_bss_102[var_r31]);
    }
    lbl_1_bss_C4 = 1;
    BoardMGExit();
    lbl_1_bss_C8->work[1] = 0;
    omDelObjEx(boardObjMan, arg0);
}

void fn_1_B2B0(omObjData* arg0, u16* arg1, s16* arg2) {
    dataCopy2* temp_r31;

    temp_r31 = arg0->data;
    *arg1 = 0;
    *arg2 = 0;
    if (temp_r31->unk_30 != 0) {
        temp_r31->unk_30 -= 1;
        return;
    }
    temp_r31->unk_30 = (frandmod(0x32U) + 15);
    if (temp_r31->unk_32 == 4) {
        *arg1 = 0x100;
        return;
    }
    if ((s32)frandmod(0xAU) < 2) {
        *arg1 = 0x100;
        return;
    }
    if (temp_r31->unk_08 == 0) {
        *arg2 = 2;
        return;
    }
    if (temp_r31->unk_08 == 2) {
        *arg2 = 1;
        return;
    }
    if (frandBool() != 0) {
        *arg2 = 1;
        return;
    }
    *arg2 = 2;
}

void fn_1_B3C4(omObjData* arg0) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f31;

    if (BoardIsKill() == 0) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[1]), "fish", &sp14);
        sp2C = *(Vec *)arg0->data;
        temp_f31 = arg0->work[0];
        temp_f30 = sp2C.y;
        sp2C.y = temp_f30 - (0.11666667f * (0.25f * (temp_f31 * temp_f31)));
        BoardModelPosGet(lbl_1_bss_FE, &sp20);
        sp8.x = 0.0f;
        sp8.y = 180.0f;
        sp8.z = 0.0f;
        BoardModelRotSetV(lbl_1_bss_FE, &sp8);
        VECAdd(&sp20, &sp2C, &sp20);
        sp14.y = sp20.y;
        VECSubtract(&sp14, &sp20, &sp14);
        temp_f29 = VECMag(&sp14);
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[1]), "fish", &sp14);
        if (temp_f29 <= arg0->trans.x) {
            sp20.x = sp14.x;
            sp20.z = sp14.z;
            sp2C.x = sp2C.z = 0.0f;
            *(Vec *)arg0->data = sp2C;
        }
        if ((sp20.y <= sp14.y) && (sp2C.y < 0.0f)) {
            sp20.y = sp14.y;
            if ((0.0f == BoardModelMotionTimeGet(lbl_1_bss_FE)) && (arg0->work[1] != 0)) {
                HuAudFXPlay(0x484);
            }
        } else {
            arg0->work[0] += 1;
        }
        BoardModelPosSetV(lbl_1_bss_FE, &sp20);
    }
}