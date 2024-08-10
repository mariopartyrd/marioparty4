#include "REL/w05Dll.h"

#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/hsfdraw.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"

#include "game/board/audio.h"
#include "game/board/model.h"
#include "game/board/window.h"

// data
s32 lbl_1_data_310[2] = { 0x79, 0x7A };
char *lbl_1_data_330[3] = { "suika1", "suika2", "suika3" };

// bss
s16 lbl_1_bss_B6;
s16 lbl_1_bss_B0[3];
s16 lbl_1_bss_AA[3];
s16 lbl_1_bss_A4[3];
s16 lbl_1_bss_A2;
s16 lbl_1_bss_9E[2];
s16 lbl_1_bss_9C;
Process *lbl_1_bss_98;
omObjData *lbl_1_bss_94;
omObjData *lbl_1_bss_90;
omObjData *lbl_1_bss_8C;
s32 lbl_1_bss_88;
s32 lbl_1_bss_7C[3];
AnimData *lbl_1_bss_78;

void fn_1_6B28(void)
{
    BoardModelAttrSet(*lbl_1_bss_14, 0x40000002U);
    lbl_1_bss_98 = NULL;
    lbl_1_bss_78 = NULL;
}

void fn_1_6B7C(void)
{
    Vec sp1C;
    Vec sp10;
    s32 spC;
    s32 var_r31;

    lbl_1_bss_B6 = GWSystem.player_curr;
    spC = GWPlayer[lbl_1_bss_B6].character;

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_9E[var_r31] = BoardPlayerMotionCreate(lbl_1_bss_B6, lbl_1_data_310[var_r31] | lbl_1_data_124[GWPlayer[lbl_1_bss_B6].character]);
    }
    lbl_1_bss_A2 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x13), NULL, 0);
    BoardModelVisibilitySet(lbl_1_bss_A2, 0);
    sp1C.x = sp1C.y = sp1C.z = 3.33333f;
    BoardModelScaleSetV(lbl_1_bss_A2, &sp1C);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[0]), "chara1", &sp1C);
    BoardPlayerPosGet(lbl_1_bss_B6, &sp10);
    BoardPlayerPosLerpStart(lbl_1_bss_B6, &sp10, &sp1C, 0x1E);

    while (GWPlayer[lbl_1_bss_B6].moving != 0) {
        HuPrcVSleep();
    }
    BoardPlayerMotBlendSet(lbl_1_bss_B6, 0, 0xF);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_B6) == 0) {
        HuPrcVSleep();
    }

    HuPrcSleep(0x3C);
    BoardAudSeqPause(0, 1, 0x3E8);
    HuAudFXPlay(0x30D);
    fn_1_88B8();
    HuAudFXPlay(0x491);
    omVibrate(lbl_1_bss_B6, 0x7FFF, 6, 6);
    BoardModelHookSet(lbl_1_bss_14[0], "chara1", BoardPlayerModelGet(lbl_1_bss_B6));
    BoardModelMotionStartEndSet(lbl_1_bss_14[0], 0x1E, 0x5A);
    BoardModelAttrReset(lbl_1_bss_14[0], 0x40000002);
    BoardMusStart(1, 0x22, 0x7F, 0);
    BoardPlayerMotionShiftSet(lbl_1_bss_B6, lbl_1_bss_9E[0], 0.0f, 30.0f, 0x40000001);
    HuPrcSleep(0x1E);
    BoardModelVisibilitySet(lbl_1_bss_A2, 1);
    BoardModelHookSet(BoardPlayerModelGet(lbl_1_bss_B6), "a-itemhook-r", lbl_1_bss_A2);
    Hu3DModelObjPosGet(BoardModelIDGet(*lbl_1_bss_14), "chara1", &sp10);
    Hu3DModelObjPosGet(BoardModelIDGet(BoardPlayerModelGet(lbl_1_bss_B6)), "a-itemhook-r", &sp1C);
    VECAdd(&sp1C, &sp10, &sp1C);
    sp1C.y += 25.0f;
    CharModelLayerSetAll(7);
    CharModelEffectCreate(-1, &sp1C);
    HuPadRumbleStop(GWPlayer[lbl_1_bss_B6].port);
    BoardModelAttrSet(lbl_1_bss_14[0], 0x40000002);
    HuPrcSleep(0x1E);
    BoardModelAttrReset(lbl_1_bss_14[0], 0x40000002);
    omVibrate(lbl_1_bss_B6, 0x7FFF, 6, 6);
    HuAudFXPlay(0x492);

    while (BoardModelMotionTimeGet(lbl_1_bss_14[0]) < 90.0f) {
        HuPrcVSleep();
    }
    BoardModelMotionTimeSet(lbl_1_bss_14[0], 90.0f);
    HuPadRumbleStop(GWPlayer[lbl_1_bss_B6].port);
    BoardModelHookReset(lbl_1_bss_14[0]);

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        BoardModelHookSet(lbl_1_bss_14[0], lbl_1_data_330[var_r31], lbl_1_bss_AA[var_r31]);
    }
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[0]), "chara1", &sp10);
    BoardPlayerPosSetV(lbl_1_bss_B6, &sp10);
    HuPrcSleep(0x3C);
    lbl_1_bss_94 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_7284);
    lbl_1_bss_8C = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, fn_1_78A0);
    lbl_1_bss_90 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, NULL);
    lbl_1_bss_90->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x14, MEMORY_DEFAULT_NUM);
    if (lbl_1_bss_78 == NULL) {
        lbl_1_bss_78 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 0x00));
        HuSprAnimLock(lbl_1_bss_78);
    }
    lbl_1_bss_9C = 0;
}

void fn_1_7284(omObjData *arg0)
{
    if ((lbl_1_bss_9C != 0) && (BoardMGDoneFlagGet() == 1)) {
        fn_1_77B0();
        fn_1_7314();
        fn_1_73C0();
        omDelObjEx(boardObjMan, arg0);
    }
}

void fn_1_72E4(void)
{
    lbl_1_bss_9C = 1;
    BoardMGExit();
}

void fn_1_7314(void)
{
    s32 var_r31;

    BoardModelHookReset(lbl_1_bss_14[0]);

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        BoardModelKill(lbl_1_bss_A4[var_r31]);
        BoardModelKill(lbl_1_bss_AA[var_r31]);
    }
    if (lbl_1_bss_78 != 0) {
        HuSprAnimKill(lbl_1_bss_78);
        lbl_1_bss_78 = NULL;
    }
}

void fn_1_73C0(void)
{
    omDelObjEx(boardObjMan, lbl_1_bss_90);
    BoardMGDoneFlagSet(0);
}

void fn_1_7400(void)
{

    while (BoardModelMotionTimeGet(lbl_1_bss_14[0]) < 30.0f) {
        HuPrcVSleep();
    }
    BoardModelAttrSet(lbl_1_bss_14[0], 0x40000002U);
    BoardModelMotionTimeSet(lbl_1_bss_14[0], 30.0f);
    lbl_1_bss_98 = HuPrcCreate(fn_1_896C, 0x2004, 0x1000, 0);
    HuPrcDestructorSet2(lbl_1_bss_98, fn_1_91DC);
    lbl_1_bss_98->user_data = (void *)7;
    HuPrcEnd();
}

s32 lbl_1_data_350[14] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x6D),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x6E),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x6F),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x70),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x71),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x72),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x73),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x74),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x76),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x77),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x78),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x79),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x7A),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x7B),
};

s16 lbl_1_data_388[92] = { 0, 1, -1, 2, 0, -1, 1, 2, 0, -1, 2, 1, 0, 2, -1, 1, 0, 2, 1, -1, 1, 2, -1, 0, 1, 2, 0, -1, 1, -1, 0, 2, 1, -1, 2, 0, 1, 0,
    2, -1, 1, 0, -1, 2, 2, -1, 0, 1, 2, -1, 1, 0, 2, 0, 1, -1, 2, 0, -1, 1, 2, 1, -1, 0, 2, 1, 0, -1, -1, 0, 1, 2, -1, 0, 2, 1, -1, 1, 2, 0, -1, 1, 0,
    2, -1, 2, 0, 1, -1, 2, 1, 0 };

f32 lbl_1_data_440[3] = { -90.0f, 0.0f, 90.0f };

void fn_1_74D0(s16 arg0[3])
{
    f32 temp_f31;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_B0[var_r31] = arg0[var_r31];
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_A4[var_r31] = BoardModelCreate(lbl_1_data_350[lbl_1_bss_B0[var_r31]], NULL, 0);
        if (lbl_1_bss_B0[var_r31] == 0xB) {
            BoardModelAttrSet(lbl_1_bss_A4[var_r31], 0x40000001U);
        }
        if (lbl_1_bss_B0[var_r31] == 5) {
            temp_f31 = -50.0f;
            Hu3DData[BoardModelIDGet(lbl_1_bss_A4[var_r31])].unk_F0[1][3] = temp_f31;
        }
        if (lbl_1_bss_B0[var_r31] == 4) {
            BoardModelMotionSpeedSet(lbl_1_bss_A4[var_r31], 0.0f);
        }
        BoardModelVisibilitySet(lbl_1_bss_A4[var_r31], 0);
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_AA[var_r31] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W05, 0x12), NULL, 1);
        BoardModelHookSet(lbl_1_bss_14[0], lbl_1_data_330[var_r31], lbl_1_bss_AA[var_r31]);
        BoardModelAttrSet(lbl_1_bss_AA[var_r31], 0x40000002);
        BoardModelMotionTimeSet(lbl_1_bss_AA[var_r31], 10.0f);
    }

    HuAudFXPlay(0x488);
    BoardModelMotionTimeSet(lbl_1_bss_14[0], 0.0f);
    BoardModelMotionStartEndSet(lbl_1_bss_14[0], 0, 0x1E);
    BoardModelAttrReset(lbl_1_bss_14[0], 0x40000002);
    HuPrcCreate(fn_1_7400, 0x2004, 0x1000, 0);
}

void fn_1_77B0(void)
{
    HuAudFXPlay(0x489);
    BoardModelMotionStartEndSet(lbl_1_bss_14[0], 0x5A, 0x78);
    BoardModelMotionTimeSet(lbl_1_bss_14[0], 90.0f);
    BoardModelAttrReset(lbl_1_bss_14[0], 0x40000002);

    while (BoardModelMotionEndCheck(lbl_1_bss_14[0]) == 0) {
        fn_1_1208(lbl_1_bss_14[6], 0.0f, 6.0f);
        HuPrcVSleep();
    }

    while (fn_1_1208(lbl_1_bss_14[6], 0.0f, 6.0f) == 0) {
        HuPrcVSleep();
    }
}

void fn_1_78A0(omObjData *arg0)
{
    if (arg0->work[0] == 0) {
        arg0->work[0] = MGSeqCreate(3, 0);
        return;
    }
    if (MGSeqStatGet(arg0->work[0]) == 0) {
        arg0->func = NULL;
        lbl_1_bss_90->func = fn_1_7F04;
    }
}

void fn_1_7928(omObjData *arg0)
{
    Process *temp;
    if (((u32)lbl_1_bss_98->user_data & 0x10) != 0) {
        temp = HuPrcCreate(fn_1_799C, 0x2004, 0x1800, 0);
        temp->user_data = arg0;
        arg0->func = NULL;
    }
}

void fn_1_799C(void)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f31;
    s32 temp_r27;
    s32 temp_r31;
    s32 var_r28;
    s32 var_r29;
    omObjData *temp_r30;

    temp_r30 = HuPrcCurrentGet()->user_data;
    BoardPlayerPosGet(lbl_1_bss_B6, &sp2C);
    temp_r31 = temp_r30->work[0];
    BoardModelPosGet(lbl_1_bss_A4[temp_r31], &sp20);
    sp2C.y = sp20.y = 0.0f;
    VECSubtract(&sp2C, &sp20, &sp14);
    temp_f30 = VECMag(&sp14);
    VECScale(&sp14, &sp14, 0.016666668);
    for (var_r29 = 0; var_r29 < 0x3C; var_r29++) {
        BoardModelPosGet(lbl_1_bss_A4[temp_r31], &sp20);
        VECAdd(&sp20, &sp14, &sp20);
        BoardModelPosSetV(lbl_1_bss_A4[temp_r31], &sp20);
        HuPrcVSleep();
    }
    BoardModelPosGet(lbl_1_bss_A4[temp_r31], &sp20);
    sp20.x = sp2C.x;
    sp20.z = sp2C.z;
    BoardModelPosSetV(lbl_1_bss_A4[temp_r31], &sp20);
    BoardPlayerMotBlendSet(lbl_1_bss_B6, 0, 0xF);

    while (BoardPlayerMotBlendCheck(lbl_1_bss_B6) == 0) {
        fn_1_1208(lbl_1_bss_14[6], 90.0f, 6.0f);
        HuPrcVSleep();
    }

    while (fn_1_1208(lbl_1_bss_14[6], 90.0f, 6.0f) == 0) {
        HuPrcVSleep();
    }
    BoardWinCreate(2, MAKE_MESSID(39, 12), 7);
    BoardWinInsertMesSet(lbl_1_bss_B0[temp_r31] + 0x80000, 0);
    BoardWinWait();
    BoardWinKill();
    HuPrcKill(lbl_1_bss_98);
    lbl_1_bss_98 = NULL;
    HuPrcVSleep();
    HuAudFXPlay(0x30D);
    BoardModelPosGet(lbl_1_bss_A4[temp_r31], &sp20);
    BoardModelScaleGet(lbl_1_bss_A4[temp_r31], &sp8);
    var_f31 = sp8.x;
    temp_f29 = -0.075f;
    temp_f30 = (sp2C.y - sp20.y) / 30.0f;
    var_r28 = 0;
    HuAudFXFadeOut(lbl_1_bss_88, 0x1F3);
    while (var_r28 == 0) {
        sp20.y += temp_f30;
        var_f31 += temp_f29;
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
            var_r28 = 1;
        }
        sp8.x = sp8.y = sp8.z = var_f31;
        BoardModelPosSetV(lbl_1_bss_A4[temp_r31], &sp20);
        BoardModelScaleSetV(lbl_1_bss_A4[temp_r31], &sp8);
        HuPrcVSleep();
    }
    HuAudFXStop(lbl_1_bss_88);
    BoardModelVisibilitySet(lbl_1_bss_A4[temp_r31], 0);
    BoardPlayerItemAdd(lbl_1_bss_B6, lbl_1_bss_B0[temp_r31]);
    omVibrate(lbl_1_bss_B6, 0xC, 6, 6);
    temp_r27 = HuAudSStreamPlay(2);
    BoardPlayerMotionShiftSet(lbl_1_bss_B6, 7, 0.0f, 5.0f, 0);

    while (BoardPlayerMotionEndCheck(lbl_1_bss_B6) == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);

    while (HuAudSStreamStatGet(temp_r27) != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 0x3E8);
    BoardWinCreate(2, MAKE_MESSID(39, 13), 7);
    BoardWinWait();
    BoardWinKill();
    temp_r30->func = &fn_1_7E4C;
    HuPrcEnd();
}

void fn_1_7E4C(omObjData *arg0)
{
    lbl_1_bss_9C = 1;
    BoardMGExit();
    omDelObjEx(boardObjMan, arg0);
}

void fn_1_7E94(dataCopy *arg0)
{
    if (--arg0->unk_02 == 0) {
        arg0->unk_02 = 0x3C;
        if (--arg0->unk_00 >= 0) {
            MGSeqParamSet(arg0->unk_04, 1, arg0->unk_00);
        }
    }
}

void fn_1_7F04(omObjData *arg0)
{
    f32 sp8[2];
    s32 var_r30;
    s32 var_r28;
    dataCopy *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk_00 = 5;
    temp_r31->unk_02 = 0x3C;
    temp_r31->unk_04 = MGSeqCreate(1, temp_r31->unk_00, 0x120, 0x40);
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x27, 0x0E));
    temp_r31->unk_06 = HuWinCreate(-10000.0f, 344.0f, sp8[0], sp8[1], 0);
    HuWinMesSet(temp_r31->unk_06, MAKE_MESSID(0x27, 0x0E));
    HuWinBGTPLvlSet(temp_r31->unk_06, 0.0f);
    HuWinMesSpeedSet(temp_r31->unk_06, 0);
    temp_r31->unk_08 = 1;

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r31->unk_0A[var_r30] = -1;
    }

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        do {
            var_r28 = frandmod(3);
        } while (temp_r31->unk_0A[var_r28] != -1);
        temp_r31->unk_0A[var_r28] = var_r30;
    }

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        if (temp_r31->unk_0A[var_r30] == -1) {
            temp_r31->unk_0A[var_r30] = 2;
        }
    }
    temp_r31->unk_12 = frandmod(5);
    temp_r31->unk_10 = (frandmod(0x1E) + 0xF);
    arg0->func = fn_1_80D8;
}

void fn_1_80D8(omObjData *arg0)
{
    s32 sp10;
    s32 spC;
    s32 sp8;
    f32 var_f31;
    s32 temp_r30;
    s32 var_r29;
    dataCopy *temp_r31;

    temp_r31 = arg0->data;
    fn_1_7E94(temp_r31);
    temp_r30 = GWPlayer[lbl_1_bss_B6].port;
    if (GWPlayer[lbl_1_bss_B6].com != 0) {
        fn_1_8798(temp_r31, &sp10, &spC, &sp8);
    }
    else {
        sp10 = HuPadStkX[temp_r30];
        spC = HuPadStkY[temp_r30];
        sp8 = HuPadBtnDown[temp_r30];
    }

    if (((sp8 & 0x100) != 0) || (temp_r31->unk_00 < 0)) {
        MGSeqParamSet(temp_r31->unk_04, 2, -1);
        HuWinKill(temp_r31->unk_06);
        BoardPlayerMotionStart(lbl_1_bss_B6, lbl_1_bss_9E[1], 0);
        arg0->func = fn_1_8410;
        return;
    }
    if ((spC != 0) || (sp10 != 0)) {
        var_r29 = -1;
        var_f31 = (180.0 * (atan2(spC, sp10) / M_PI));
        if (var_f31 < 0.0f) {
            var_f31 += 360.0f;
        }

        if ((var_f31 > 170.0f) && (var_f31 < 190.0f)) {
            var_r29 = 0;
        }
        else if ((var_f31 > 260.0f) && (var_f31 < 280.0f)) {
            var_r29 = 1;
        }
        else if ((var_f31 < 10.0f) || (var_f31 > 350.0f)) {
            var_r29 = 2;
        }
        if (var_r29 != -1) {
            temp_r31->unk_08 = temp_r31->unk_0A[var_r29];
            BoardPlayerRotYSet(lbl_1_bss_B6, lbl_1_data_440[temp_r31->unk_08]);
        }
    }
}

void fn_1_8410(omObjData *arg0)
{
    s32 temp_r30;
    dataCopy *temp_r31;

    temp_r31 = arg0->data;
    if (BoardPlayerMotionTimeGet(lbl_1_bss_B6) >= 30.0f) {
        BoardAudSeqFadeOut(1, 0x64);
        HuAudFXPlay(0x486);
        HuAudFXPlay(0x487);
        temp_r30 = (1 << temp_r31->unk_08);
        temp_r30 |= 0x1C0;
        lbl_1_bss_98 = HuPrcCreate(fn_1_896C, 0x2004, 0x4000, 0);
        HuPrcDestructorSet2(lbl_1_bss_98, fn_1_91DC);
        lbl_1_bss_98->user_data = (void *)temp_r30;
        lbl_1_bss_8C->work[0] = temp_r31->unk_08;
        arg0->func = fn_1_850C;
    }
}

void fn_1_850C(omObjData *arg0)
{
    Vec sp14;
    Vec sp8;
    f32 temp_f31;

    temp_f31 = BoardPlayerMotionMaxTimeGet(lbl_1_bss_B6);
    if (BoardPlayerMotionTimeGet(lbl_1_bss_B6) >= temp_f31) {
        BoardPlayerMotionStart(lbl_1_bss_B6, lbl_1_bss_9E[0], 0x40000001);
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[0]), "chara1", &sp8);
        Hu3DModelObjPosGet(BoardModelIDGet(BoardPlayerModelGet(lbl_1_bss_B6)), "a-itemhook-r", &sp14);
        VECAdd(&sp14, &sp8, &sp14);
        sp14.y += 25.0f;
        CharModelLayerSetAll(7);
        CharModelEffectCreate(-1, &sp14);
        arg0->work[0] = 0xA;
        arg0->func = fn_1_8668;
    }
}

void fn_1_8668(omObjData *arg0)
{
    s32 var_r30;

    if (arg0->work[0] == 0) {
        BoardModelHookReset(BoardPlayerModelGet(lbl_1_bss_B6));
        BoardPlayerMotionShiftSet(lbl_1_bss_B6, 1, 0.0f, 5.0f, 0x40000001);
        arg0->func = NULL;
        lbl_1_bss_8C->func = fn_1_7928;
        BoardModelKill(lbl_1_bss_A2);

        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            BoardPlayerMotionKill(lbl_1_bss_B6, lbl_1_bss_9E[var_r30]);
        }
        return;
    }
    arg0->work[0] -= 1;
}

void fn_1_8798(dataCopy *arg0, s32 *arg1, s32 *arg2, s32 *arg3)
{
    *arg1 = *arg2 = *arg3 = 0;
    if (arg0->unk_10 != 0) {
        arg0->unk_10 -= 1;
        return;
    }
    arg0->unk_10 = frandmod(0xF) + 10;
    if (arg0->unk_12 == 0) {
        *arg3 = 0x100;
        return;
    }
    arg0->unk_12 -= 1;
    if (frandBool() != 0) {
        *arg1 = (frandBool() * 0x8C) - 0x46;
        return;
    }
    *arg2 = (frandBool() * 0x8C) - 0x46;
}

void *fn_1_8884(void)
{
    if (lbl_1_bss_98 == NULL) {
        return NULL;
    }
    return lbl_1_bss_98->user_data;
}

void fn_1_88B8(void)
{
    s32 userData = (s32)lbl_1_bss_98->user_data;
    userData |= 8;
    lbl_1_bss_98->user_data = (void *)(userData);

    while (((u32)fn_1_8884() & 0x20) == 0) {
        HuPrcVSleep();
    }
    HuPrcKill(lbl_1_bss_98);
    lbl_1_bss_98 = NULL;
}

void fn_1_896C(void)
{
    Vec sp18;
    Vec spC;
    f32 sp8;
    f32 temp_f29;
    f32 var_f30;
    f32 var_f31;
    u32 temp_r30;
    s32 var_r28;
    s32 var_r31;
    s32 var_r29;
    ParticleData *var_r27;

    temp_r30 = (u32)HuPrcCurrentGet()->user_data;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r29 = (1 << var_r31);
        if ((temp_r30 & var_r29) != 0) {
            BoardModelAttrReset(lbl_1_bss_AA[var_r31], 0x40000002);
            if ((temp_r30 & 0x80) != 0) {
                BoardModelMotionStartEndSet(lbl_1_bss_AA[var_r31], 0, 0x28);
                BoardModelMotionTimeSet(lbl_1_bss_AA[var_r31], 0.0f);
            }
            else {
                BoardModelMotionStartEndSet(lbl_1_bss_AA[var_r31], 0xA, 0x28);
                BoardModelMotionTimeSet(lbl_1_bss_AA[var_r31], 10.0f);
            }
        }
    }
    if ((temp_r30 & 0x80) != 0) {
        HuPrcSleep(0x19);
    }
    else {
        HuPrcSleep(0xF);
    }
    spC.x = spC.y = spC.z = 0.0f;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r29 = (1 << var_r31);
        if ((temp_r30 & var_r29) != 0) {
            BoardModelVisibilitySet(lbl_1_bss_A4[var_r31], 1);
            BoardModelScaleSetV(lbl_1_bss_A4[var_r31], &spC);
            Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_14[0]), lbl_1_data_330[var_r31], &sp18);
            BoardModelPosSetV(lbl_1_bss_A4[var_r31], &sp18);
            if ((temp_r30 & 0x40) != 0) {
                lbl_1_bss_7C[var_r31] = Hu3DParticleCreate(lbl_1_bss_78, 0x64);
                var_r27 = Hu3DData[lbl_1_bss_7C[var_r31]].unk_120;
                var_r27->unk_02 = lbl_1_bss_A4[var_r31];
                Hu3DParticleHookSet(lbl_1_bss_7C[var_r31], fn_1_9268);
                Hu3DParticleColSet(lbl_1_bss_7C[var_r31], 0xFF, 0xFF, 0);
                Hu3DModelPosSet(lbl_1_bss_7C[var_r31], 0.0f, 0.0f, 0.0f);
                Hu3DParticleBlendModeSet(lbl_1_bss_7C[var_r31], 1);
                Hu3DModelLayerSet(lbl_1_bss_7C[var_r31], 2);
            }
            if ((temp_r30 & 0x100) != 0) {
                lbl_1_bss_88 = HuAudFXPlay(0x35F);
                HuAudFXPlay(0x310);
            }
            else {
                HuAudFXPlay(0x362);
            }
        }
    }
    temp_f29 = 150.0f + sp18.y;
    sp8 = 0.0f;
    var_f31 = 12.0f;

    while (1) {
        for (var_r28 = 0, var_r31 = 0; var_r31 < 3; var_r31++) {
            var_r29 = (1 << var_r31);
            if ((temp_r30 & var_r29) != 0) {
                var_r28++;
                sp8 += 0.1f;
                if (sp8 > 1.0f) {
                    sp8 = 1.0f;
                }

                spC.x = spC.y = spC.z = sp8;
                BoardModelScaleSetV(lbl_1_bss_A4[var_r31], (Vec *)&sp8); //!
                BoardModelPosGet(lbl_1_bss_A4[var_r31], &sp18);
                sp18.y += var_f31;
                if (sp18.y >= temp_f29) {
                    sp18.y = temp_f29;
                    var_r28 -= 1;
                }
                BoardModelPosSetV(lbl_1_bss_A4[var_r31], &sp18);
            }
        }
        var_f31 *= 0.95f;
        if (var_r28 > 0) {
            HuPrcVSleep();
        }
        else {
            break;
        }
    }
    spC.x = spC.y = spC.z = 1.0f;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r29 = (1 << var_r31);
        if ((temp_r30 & var_r29) != 0) {
            BoardModelScaleSetV(lbl_1_bss_A4[var_r31], &spC);
        }
    }
    temp_r30 = (u32)HuPrcCurrentGet()->user_data | 0x10;
    HuPrcCurrentGet()->user_data = (void *)temp_r30;
    var_f30 = 0.0f;

    while (1) {
        temp_r30 = (u32)HuPrcCurrentGet()->user_data;
        if ((temp_r30 & 8) == 0) {
            for (var_r31 = 0; var_r31 < 3; var_r31++) {
                var_r29 = (1 << var_r31);
                if ((temp_r30 & var_r29) != 0) {
                    BoardModelPosGet(lbl_1_bss_A4[var_r31], &sp18);
                    sp18.y = (sp18.y + (0.25 * sin((M_PI * var_f30) / 180.0)));
                    BoardModelPosSetV(lbl_1_bss_A4[var_r31], &sp18);
                }
            }
            var_f30 += 5.0f;
            if (var_f30 >= 360.0f) {
                var_f30 -= 360.0f;
            }
            HuPrcVSleep();
        }
        else {
            break;
        }
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        BoardModelMotionStartEndSet(lbl_1_bss_AA[var_r31], 0x28, 0x46);
    }
    HuPrcSleep(13);
    var_f31 = -8.0f;
    while (1) {
        for (var_r28 = 0, var_r31 = 0; var_r31 < 3; var_r31++) {
            var_r29 = (1 << var_r31);
            if ((temp_r30 & var_r29) != 0) {
                var_r28++;
                sp8 -= 0.02f;
                if (sp8 < 0.0f) {
                    sp8 = 0.0f;
                }
                spC.x = spC.y = spC.z = sp8;
                BoardModelScaleSetV(lbl_1_bss_A4[var_r31], (Vec *)&sp8); //!
                BoardModelPosGet(lbl_1_bss_A4[var_r31], &sp18);
                sp18.y += var_f31;
                if (sp18.y <= (temp_f29 - 150.0f)) {
                    sp18.y = temp_f29 - 150.0f;
                }
                if (BoardModelMotionTimeGet(lbl_1_bss_AA[var_r31]) >= 70.0f) {
                    var_r28--;
                }
                BoardModelPosSetV(lbl_1_bss_A4[var_r31], &sp18);
            }
        }
        var_f31 *= 0.98f;
        if (var_r28 > 0) {
            HuPrcVSleep();
        }
        else {
            break;
        }
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r29 = (1 << var_r31);
        if ((temp_r30 & var_r29) != 0) {
            spC.x = spC.y = spC.z = 1.0f;
            BoardModelScaleSetV(lbl_1_bss_A4[var_r31], &spC);
            BoardModelVisibilitySet(lbl_1_bss_A4[var_r31], 0);
        }
    }
    temp_r30 = (u32)HuPrcCurrentGet()->user_data;
    temp_r30 |= 0x20;
    HuPrcCurrentGet()->user_data = (void *)temp_r30;
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_91DC(void)
{
    u32 temp_r30;
    s32 var_r29;
    s32 var_r31;

    temp_r30 = (u32)HuPrcCurrentGet()->user_data;
    if ((temp_r30 & 0x40) != 0) {
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            var_r29 = (1 << var_r31);
            if ((temp_r30 & var_r29) != 0) {
                Hu3DModelKill(lbl_1_bss_7C[var_r31]);
            }
        }
    }
}

void fn_1_9268(ModelData *model, ParticleData *particle, f32 (*matrix)[4])
{
    Vec sp8;
    HsfanimStruct01 *var_r31;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f31;
    s32 var_r28;
    s32 var_r29;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
        particle->unk_00 = 0;
    }
    BoardModelScaleGet(particle->unk_02, &sp8);
    temp_f31 = sp8.x;
    BoardModelPosGet(particle->unk_02, &sp8);

    for (var_r29 = 0; var_r29 < 0x16; var_r29++) {
        var_r31 = particle->unk_48;

        for (var_r28 = 0; var_r28 < particle->unk_30; var_r28++, var_r31++) {
            if (var_r31->unk2C == 0.0f)
                break;
        }
        if (var_r28 != particle->unk_30) {
            temp_f30 = 360.0f * (0.003921569f * (s32)(frand() & 0xFF));
            temp_f29 = temp_f31 * (20.0f + (60.0f * (0.003921569f * (s32)(frand() & 0xFF))));
            var_r31->unk34.x = sp8.x + (temp_f29 * sin((M_PI * temp_f30) / 180.0));
            var_r31->unk34.z = sp8.z + (temp_f29 * cos((M_PI * temp_f30) / 180.0));
            var_r31->unk34.y = sp8.y + (temp_f31 * (-30.0f + (40.0f * (0.003921569f * (s32)(frand() & 0xFF)))));
            var_r31->unk08.x = 0.5f + (3.0f * (0.003921569f * (s32)(frand() & 0xFF)));
            var_r31->unk08.y = 0.3f + (2.0f * (0.003921569f * (s32)(frand() & 0xFF)));
            var_r31->unk40.a = 0xB4;
            var_r31->unk2C = 15.0f * temp_f31;
        }
    }
    var_r31 = particle->unk_48;
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (0.0f != var_r31->unk2C) {
            var_r31->unk34.y -= var_r31->unk08.x;
            var_r31->unk2C -= var_r31->unk08.y;
            if (var_r31->unk2C <= 0.0f) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}
