#include "REL/executor.h"
#include "REL/w03Dll.h"
#include "dolphin.h"
#include "dolphin/os/OSFastCast.h"
#include "ext_math.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "math.h"

typedef struct someBits {
    /* 0x00 */ struct {
        u8 unk00_bit0 : 1;
        u8 unk00_bit1 : 3;
        u8 unk00_bit4 : 2;
        u8 unk00_bit6 : 1;
        u8 unk00_bit7 : 1;
    };
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 unk4;
    s16 unk_06[3];
} someBits;

typedef struct someBits2 {
    /* 0x00 */ struct {
        u8 unk00_bit0 : 1;
        u8 unk00_bit1 : 3;
        u8 unk00_bit4 : 2;
        u8 unk00_bit6 : 1;
        u8 unk00_bit7 : 1;
    };
    s8 unk1;
    s8 unk2;
    u8 unk3[3];
    s16 unk_06[4];
} someBits2;

typedef struct w03UnkMG {
    /* 0x00 */ char unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
} w03UnkMG;

// external symbols

// function signatures
s32 BoardVecDAngleCalcRange(float *value, float min, float range);

void fn_1_BE30(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_BDAC(void);
void fn_1_BC7C(s16 arg0);
void fn_1_BBF8(void);
s32 fn_1_BBC4(void);
void fn_1_BB74(s8 *arg0);
s32 fn_1_BB48(void);
void fn_1_B8E8(s32 arg0);
void fn_1_B748(omObjData *arg0, someBits2 *arg1);
void fn_1_B688(omObjData *arg0, someBits2 *arg1);
void fn_1_B4AC(omObjData *arg0, someBits2 *arg1);
void fn_1_B350(omObjData *arg0);
void fn_1_B0A4(s32 arg0);
u32 fn_1_AF24(s32 arg0);
s32 fn_1_AE4C(s32 arg0, s8 *arg1);
s32 fn_1_AE20(void);
void fn_1_ACD8(s32 arg0);
void fn_1_ABD0(omObjData *arg0, someBits *arg1);
void fn_1_AB18(omObjData *arg0, someBits *arg1);
void fn_1_A8AC(s32 arg0);
void fn_1_A7A0(s32 arg0);
void fn_1_A994(omObjData *arg0);
void fn_1_A5E0(s32 arg0);
void fn_1_A6B0(void);
void fn_1_A44C(s32 arg0);
void fn_1_9C8C(void);
void fn_1_9B30(void);
s32 fn_1_9CF4(s32 arg0);
void fn_1_9F78(void);
void fn_1_9FE4(void);

// data
s16 lbl_1_data_4D8 = -1;
s16 lbl_1_data_4DA = -1;
s16 lbl_1_data_4DC = -1;
s32 lbl_1_data_4E0 = -1;
s16 lbl_1_data_4E4 = -1;
s8 lbl_1_data_4E6[] = { 1, 1, 3, 3, 2, 2, 2, 1, 2, 3, 0, 4, 5, 0 };

char *lbl_1_data_508[] = { "item", "item1", "item2" };

#if VERSION_JP
#define MDL_ID_SHIFT 0
#else
#define MDL_ID_SHIFT 1
#endif

s32 lbl_1_data_514[] = {
    DATA_MAKE_NUM(DATADIR_BOARD, 0x6C + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x6D + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x6E + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x6F + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x70 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x71 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x72 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x73 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x75 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x76 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x77 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x78 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x79 + MDL_ID_SHIFT),
    DATA_MAKE_NUM(DATADIR_BOARD, 0x7A + MDL_ID_SHIFT),
};

// BSS
s8 lbl_1_bss_194[3];
AnimData *lbl_1_bss_190;
s8 lbl_1_bss_18C;
omObjData *lbl_1_bss_188;
omObjData *lbl_1_bss_184;
Process *lbl_1_bss_180;

void fn_1_9A7C(void)
{
    fn_1_BBF8();
}

void fn_1_9A9C(void) { }

void fn_1_9AA0(void)
{
    BoardRollDispSet(0);
    lbl_1_bss_180 = HuPrcChildCreate(fn_1_9C8C, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_180, fn_1_9B30);

    while (lbl_1_bss_180 != 0) {
        HuPrcVSleep();
    }

    BoardRollDispSet(1);
}

void fn_1_9B30(void)
{
    fn_1_BDAC();

    if (lbl_1_bss_188) {
        lbl_1_bss_188;
    }

    if (lbl_1_bss_184) {
        OM_GET_WORK_PTR(lbl_1_bss_184, someBits2)->unk00_bit0 = 1;
    }

    if (lbl_1_data_4E0 != -1) {
        HuAudFXStop(lbl_1_data_4E0);
        lbl_1_data_4E0 = -1;
    }

    if (lbl_1_data_4DC != -1) {
        BoardModelMotionKill(lbl_1_bss_C[11], lbl_1_data_4DC);
        lbl_1_data_4DC = -1;
    }

    if (lbl_1_data_4DA != -1) {
        BoardModelMotionKill(lbl_1_bss_C[11], lbl_1_data_4DA);
        lbl_1_data_4DA = -1;
    }

    if (lbl_1_data_4D8 != -1) {
        HuWinKill(lbl_1_data_4D8);
        lbl_1_data_4D8 = -1;
    }

    lbl_1_bss_180 = 0;
}

void fn_1_9C8C(void)
{
    s32 temp_r31;

    temp_r31 = GWSystem.player_curr;
    lbl_1_data_4E0 = -1;

    if (fn_1_9CF4(temp_r31) != 0) {
        fn_1_A44C(temp_r31);
        fn_1_A5E0(temp_r31);
    }

    HuPrcEnd();
}

s32 fn_1_9CF4(s32 arg0)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s16 spaceCur;
    s16 temp_r29;

    if (BoardPlayerItemCount(arg0) == 3) {
        BoardWinCreate(2, MAKE_MESSID(22, 30), 2);
        BoardWinWait();
        BoardWinKill();
        return 0;
    }

    BoardWinCreateChoice(2, MAKE_MESSID(22, 26), 2, 0);

    if (GWPlayer[arg0].com != 0) {
        BoardComKeySetLeft();
    }

    BoardWinWait();

    if (BoardWinChoiceGet() != 0) {
        BoardWinCreate(2, MAKE_MESSID(22, 27), 2);
        BoardWinWait();
        BoardWinKill();
        return 0;
    }

    BoardWinKill();

    sp14.x = 0.0f;
    sp14.y = 200.0f;
    sp14.z = 0.0f;
    sp8.x = -10.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;

    BoardCameraMotionStartEx(lbl_1_bss_C[8], &sp8, &sp14, 1500.0f, -1.0f, 21);
    spaceCur = GWPlayer[arg0].space_curr;
    temp_r29 = BoardSpaceLinkFlagSearch(0, spaceCur, 0x02000000);
    BoardPlayerPosGet(arg0, &sp2C);
    BoardSpacePosGet(0, temp_r29, &sp38);
    VECSubtract(&sp38, &sp2C, &sp20);
    VECNormalize(&sp20, &sp20);
    BoardPlayerRotYSet(arg0, atan2d(-sp20.x, -sp20.z));
    BoardPlayerPosLerpStart(arg0, &sp2C, &sp38, 0x14);

    while (GWPlayer[arg0].moving != 0) {
        HuPrcVSleep();
    }

    BoardPlayerIdleSet(arg0);
    HuPrcSleep(0x3C);
    fn_1_B0A4(arg0);
    fn_1_9F78();
    fn_1_9FE4();
    fn_1_A8AC(arg0);
    return 1;
}

void fn_1_9F78(void)
{
    lbl_1_data_4DA = BoardModelMotionCreate(lbl_1_bss_C[11], DATA_MAKE_NUM(DATADIR_W03, 0x23));
    lbl_1_data_4DC = BoardModelMotionCreate(lbl_1_bss_C[11], DATA_MAKE_NUM(DATADIR_W03, 0x24));
}

void fn_1_9FE4(void)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    f32 sp8;
    f32 temp_f30;
    f32 var_f31;

    BoardModelPosGet(lbl_1_bss_C[11], &sp24);
    sp18.x = -3179.8f + 200.0 * sin(0.0);
    sp18.z = -907.7f + 200.0 * cos(0.0);
    sp18.y = sp24.y;
    VECSubtract(&sp18, &sp24, &spC);
    temp_f30 = atan2d(spC.z, spC.x);
    sp8 = BoardModelRotYGet(lbl_1_bss_C[11]);
    BoardModelMotionShiftSet(lbl_1_bss_C[11], lbl_1_data_4DA, 0.0f, 10.0, HU3D_MOTATTR_LOOP);

    while (BoardDAngleCalcRange(&sp8, temp_f30, 10.0) == 0) {
        BoardModelRotYSet(lbl_1_bss_C[11], sp8);
        HuPrcVSleep();
    }

    BoardModelRotYSet(lbl_1_bss_C[11], temp_f30);
    BoardModelMotionSpeedSet(lbl_1_bss_C[11], 2.0f);

    spC.x /= 20.0f;
    spC.z /= 20.0f;
    spC.y = 0.0f;
    sp30 = sp24;
    var_f31 = 0.0f;

    while (var_f31 < 20.0f) {
        VECAdd(&sp30, &spC, &sp30);
        BoardModelPosSetV(lbl_1_bss_C[11], &sp30);
        HuPrcVSleep();
        var_f31 += 1.0f;
    }

    BoardAudSeqPause(0, 1, 0x3E8);
    HuAudFXPlay(0x450);
    HuAudFXPlay(0x362);
    BoardCameraQuakeSet(3, 100.0f);
    fn_1_B8E8(1);
    BoardModelMotionShiftSet(lbl_1_bss_C[11], lbl_1_data_4DC, 0.0f, 10.0, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV);
    VECSubtract(&sp24, &sp30, &spC);

    spC.x /= 60.0f;
    spC.z /= 60.0f;
    spC.y = 0.0f;
    var_f31 = 0.0f;

    while (var_f31 < 60.0f) {
        VECAdd(&sp30, &spC, &sp30);
        BoardModelPosSetV(lbl_1_bss_C[11], &sp30);
        HuPrcVSleep();
        var_f31 += 1.0f;
    }

    temp_f30 = 0.0f;
    sp8 = BoardModelRotYGet(lbl_1_bss_C[11]);
    BoardModelMotionShiftSet(lbl_1_bss_C[11], lbl_1_data_4DA, 0.0f, 10.0, HU3D_MOTATTR_LOOP);

    while (BoardDAngleCalcRange(&sp8, temp_f30, 10.0) == 0) {
        BoardModelRotYSet(lbl_1_bss_C[11], sp8);
        HuPrcVSleep();
    }

    BoardModelMotionShiftSet(lbl_1_bss_C[11], 1, 0.0f, 10.0, HU3D_MOTATTR_LOOP);
}

void fn_1_A44C(s32 arg0)
{
    s16 temp_r30;
    s32 temp_r29;
    s32 temp_r28;

    BoardMusStart(1, 0x17, 0x7F, 0);
    temp_r30 = MGSeqStartCreate();

    while (MGSeqStatGet(temp_r30) != 0) {
        HuPrcVSleep();
    }

    fn_1_A7A0(arg0);
    fn_1_A6B0();
    fn_1_ACD8(1);

    while (fn_1_AE20() != 0) {
        HuPrcVSleep();
    }

    temp_r29 = fn_1_BBC4() + 0x80000;
    BoardWinCreate(2, MAKE_MESSID(22, 28), 2);
    BoardWinInsertMesSet(temp_r29, 0);
    BoardWinWait();
    fn_1_B8E8(4);

    while (fn_1_BB48() != 0) {
        HuPrcVSleep();
    }

    omVibrate(arg0, 0xC, 6, 6);
    BoardPlayerItemAdd(arg0, fn_1_BBC4());
    fn_1_ACD8(3);
    temp_r28 = HuAudSStreamPlay(2);

    while (HuAudSStreamStatGet(temp_r28) != 0) {
        HuPrcVSleep();
    }

    BoardAudSeqPause(0, 0, 1000);

    while (lbl_1_bss_188) {
        HuPrcVSleep();
    }

    HuPrcSleep(0x1E);
    BoardWinCreate(2, MAKE_MESSID(22, 29), 2);
    BoardWinWait();
    BoardWinKill();
}

void fn_1_A5E0(s32 arg0)
{
    Vec sp14;
    Vec sp8;
    s16 spaceCur;

    spaceCur = GWPlayer[arg0].space_curr;
    BoardPlayerPosGet(arg0, &sp14);
    BoardSpacePosGet(0, spaceCur, &sp8);
    BoardCameraTargetPlayerSet(arg0);
    BoardCameraViewSet(1);
    BoardPlayerPosLerpStart(arg0, &sp14, &sp8, 20);
    while (GWPlayer[arg0].moving != 0) {
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_bss_C[11], 0.0f);
    BoardCameraMotionWait();
}

void fn_1_A6B0(void)
{
    f32 sp8[2];
    f32 val1, val2;

    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x16, 0x1F));
    val1 = -10000.0f;
    val2 = 392.0f;
    lbl_1_data_4D8 = HuWinCreate(val1, val2, sp8[0], sp8[1], 0);
    HuWinBGTPLvlSet(lbl_1_data_4D8, 0.0f);
    HuWinMesSpeedSet(lbl_1_data_4D8, 0);
    HuWinMesSet(lbl_1_data_4D8, MAKE_MESSID(0x16, 0x1F));
}

void fn_1_A7A0(s32 arg0)
{
    someBits *temp_r31;
    omObjData *temp_r3;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, (void *)fn_1_A994);
    lbl_1_bss_188 = temp_r3;
    temp_r31 = (someBits *)&temp_r3->work[0];
    temp_r31->unk00_bit0 = 0;
    temp_r31->unk00_bit6 = 0;
    temp_r31->unk00_bit4 = arg0;
    temp_r31->unk00_bit1 = 0;
    temp_r31->unk1 = 5U;
    temp_r31->unk2 = 0x3C;
    temp_r31->unk4 = MGSeqTimerCreateXY(temp_r31->unk1, 288, 64);
    fn_1_BB74(lbl_1_bss_194);
    lbl_1_bss_18C = fn_1_AE4C(arg0, lbl_1_bss_194);
}

void fn_1_A8AC(s32 arg0)
{
    Vec sp14;
    Vec sp8;
    f32 playerYRot;

    BoardModelPosGet(lbl_1_bss_C[9], &sp8);
    BoardPlayerPosGet(arg0, &sp14);
    sp8.y = sp14.y;
    BoardPlayerPosLerpStart(arg0, &sp14, &sp8, 20);

    while (GWPlayer[arg0].moving != 0) {
        HuPrcVSleep();
    }

    playerYRot = BoardPlayerRotYGet(arg0) + 180.0f;
    BoardPlayerMotBlendSet(arg0, playerYRot, 15);

    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }
}

void fn_1_A994(omObjData *arg0)
{
    s32 temp_r0;
    someBits *temp_r31;

    temp_r31 = (someBits *)&lbl_1_bss_188->work[0];
    if ((temp_r31->unk00_bit0 != 0) || (BoardIsKill() != 0)) {
        if (temp_r31->unk4 != -1) {
            MGSeqParamSet(temp_r31->unk4, 2, -1U);
            temp_r31->unk4 = -1;
        }
        lbl_1_bss_188 = NULL;

        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }

    if (temp_r31->unk00_bit6 == 0) {
        if (temp_r31->unk2 != 0) {
            temp_r31->unk2--;
        }
        else {
            if (temp_r31->unk1 != 0) {
                temp_r31->unk1--;
            }
            else {
                fn_1_ACD8(2);
            }
            MGSeqParamSet(temp_r31->unk4, 1, temp_r31->unk1);
            temp_r31->unk2 = 0x3CU;
        }
    }

    switch (temp_r31->unk00_bit1) {
        case 1:
            fn_1_AB18(arg0, temp_r31);
            return;
        case 2:
            fn_1_ABD0(arg0, temp_r31);
            return;
        case 3:
            if (BoardPlayerMotionEndCheck(temp_r31->unk00_bit4) != 0) {
                temp_r31->unk00_bit0 = 1;
            }
        case 0:
            break;
    }
}

void fn_1_AB18(omObjData *arg0, someBits *arg1)
{
    u32 var_r31 = 0;

    if (GWPlayer[arg1->unk00_bit4].com != 0) {
        var_r31 = fn_1_AF24(arg1->unk00_bit4);
    }
    else {
        var_r31 = HuPadBtnDown[GWPlayer[arg1->unk00_bit4].port];
    }
    if (var_r31 == 0x100) {
        fn_1_ACD8(2);
    }
}

// TODO properly use inlines
void fn_1_ABD0(omObjData *arg0, someBits *arg1)
{
    s16 boardModelID;
    PlayerState *playerStateCopy;
    s32 bit;
    PlayerState *playerState;
    s16 temp, temp2;

    bit = arg1->unk00_bit4;
    playerState = &GWPlayer[bit];
    playerStateCopy = playerState;
    temp = boardPlayerMdl[playerStateCopy->player_idx];
    temp2 = temp;
    boardModelID = BoardModelIDGet(temp2);

    if (Hu3DMotionShiftIDGet(boardModelID) == -1) {
        if (!(arg1->unk00_bit7)) {
            if (BoardPlayerMotionTimeGet(arg1->unk00_bit4) >= 27.0f) {
                arg1->unk00_bit7 = 1;
                BoardAudSeqFadeOut(1, 0x64);
                fn_1_B8E8(2);
                return;
            }
        }
        if (BoardPlayerMotionEndCheck(arg1->unk00_bit4)) {
            fn_1_ACD8(0);
        }
    }
}

void fn_1_ACD8(s32 arg0)
{
    someBits *temp_r31;

    temp_r31 = (someBits *)&lbl_1_bss_188->work[0];
    temp_r31->unk00_bit1 = arg0;

    switch (arg0) {
        case 0:
            BoardPlayerIdleSet(temp_r31->unk00_bit4);
            return;
        case 2:
            temp_r31->unk00_bit6 = 1;
            if (lbl_1_data_4D8 != -1) {
                HuWinKill(lbl_1_data_4D8);
                lbl_1_data_4D8 = -1;
            }
            if (temp_r31->unk4 != -1) {
                MGSeqParamSet(temp_r31->unk4, 2, -1U);
                temp_r31->unk4 = -1;
            }
            BoardPlayerMotionShiftSet(temp_r31->unk00_bit4, 0xB, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            return;
        case 3:
            BoardPlayerMotionShiftSet(temp_r31->unk00_bit4, 7, 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            break;
    }
}

s32 fn_1_AE20(void)
{
    someBits *temp_r31 = (someBits *)&lbl_1_bss_188->work[0];
    return temp_r31->unk00_bit1;
}

s32 fn_1_AE4C(s32 arg0, s8 *arg1)
{
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 var_r31;

    temp_r29 = lbl_1_data_4E6[arg1[0]];
    temp_r28 = lbl_1_data_4E6[arg1[1]];
    temp_r30 = lbl_1_data_4E6[arg1[2]];

    if (temp_r29 > temp_r28) {
        if (temp_r29 > temp_r30) {
            var_r31 = 0;
        }
        else if (temp_r30 > temp_r28) {
            var_r31 = 2;
        }
        else {
            var_r31 = 1;
        }
    }
    else if (temp_r28 > temp_r30) {
        var_r31 = 1;
    }
    else if (temp_r30 > temp_r29) {
        var_r31 = 2;
    }
    else {
        var_r31 = 0;
    }

    return var_r31;
}

u32 fn_1_AF24(s32 arg0)
{
    s32 spC;
    s32 sp8;
    s16 temp_r31;
    s16 var_r30;
    s8 temp_r0_2;

    spC = 0;

    switch (GWPlayer[arg0].diff) {
        case 3:
            var_r30 = 0;
            break;
        case 2:
            var_r30 = 5;
            break;
        case 1:
            var_r30 = 15;
            break;
        case 0:
            var_r30 = 40;
            break;
    }
    if ((var_r30 != 0) && (BoardRandMod(100) < var_r30)) {
        return 0x100U;
    }

    temp_r31 = BoardModelMotionTimeGet(lbl_1_bss_C[9]);

    switch (lbl_1_bss_18C) {
        case 0:
            if ((temp_r31 < 33) || (temp_r31 > 35)) {
                break;
            }
            return 0x100U;
        case 1:
            if (((temp_r31 >= 40) && (temp_r31 <= 42)) || ((temp_r31 >= 20) && (temp_r31 <= 22))) {
                return 0x100U;
            }
            break;
        case 2:
            if (temp_r31 >= 50) {
                return 0x100U;
            }
            break;
    }
    return 0;
}

void fn_1_B0A4(s32 arg0)
{
    Mtx sp18;
    s32 spC[3];
    s32 j;
    s32 i;
    s32 var_r31_2;
    s32 temp_r29;
    someBits2 *temp_r30;
    omObjData *temp_r3;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, (void *)fn_1_B350);
    lbl_1_bss_184 = (void *)temp_r3;
    temp_r30 = (someBits2 *)&temp_r3->work[0];

    temp_r30->unk00_bit0 = 0;
    temp_r30->unk00_bit1 = 0;
    temp_r30->unk00_bit4 = arg0;

    for (i = 0; i < ARRAY_COUNT(spC);) {
        spC[i] = BoardRandMod(14);
        if ((spC[i] != 10) && (spC[i] != 13)) {
            for (j = 0; j < i; j++) {
                if (spC[i] == spC[j]) {
                    spC[i] = -1;
                }
            }
            if (spC[i] == -1) {
                continue;
            }
        }
        else {
            continue;
        }
        i++;
    }

    fn_1_BBF8();

    for (i = 0; i < ARRAY_COUNT(spC); i++) {
        temp_r29 = spC[i];
        temp_r30->unk3[i] = temp_r29;
        temp_r30->unk_06[i] = BoardModelCreate(lbl_1_data_514[temp_r29], NULL, 0);
        BoardModelHookSet(lbl_1_bss_C[9], lbl_1_data_508[i], temp_r30->unk_06[i]);
        BoardModelMotionSpeedSet(temp_r30->unk_06[i], 0.0f);

        if (temp_r29 == 11) {
            BoardModelMotionStart(temp_r30->unk_06[i], 0, 0x40000001);
        }

        if (temp_r29 == 5) {
            MTXTrans(sp18, 0.0f, -50.0f, 0.0f);
            BoardModelMtxSet(temp_r30->unk_06[i], &sp18);
        }

        if ((temp_r29 == 6) || (temp_r29 == 7)) {
            MTXTrans(sp18, 0.0f, 0.0f, 8.0f);
            BoardModelMtxSet(temp_r30->unk_06[i], &sp18);
        }
    }
}

void fn_1_B350(omObjData *arg0)
{
    s32 i;
    someBits2 *temp_r31;

    temp_r31 = (someBits2 *)&arg0->work[0];

    if ((temp_r31->unk00_bit0 != 0) || (BoardIsKill() != 0)) {
        BoardModelHookReset(lbl_1_bss_C[9]);
        for (i = 0; i < 3; i++) {
            BoardModelKill(temp_r31->unk_06[i]);
        }
        fn_1_BBF8();
        omDelObjEx(HuPrcCurrentGet(), arg0);
        lbl_1_bss_184 = NULL;
        return;
    }

    switch (temp_r31->unk00_bit1) {
        case 1:
            if (!(BoardModelMotionTimeGet(lbl_1_bss_C[9]) < 20.0f)) {
                BoardModelMotionStartEndSet(lbl_1_bss_C[9], 0x14, 0x3A);
                fn_1_B8E8(0);
                return;
            }
        case 0:
            break;
        case 2:
            fn_1_B4AC(arg0, temp_r31);
            return;
        case 3:
            fn_1_B688(arg0, temp_r31);
            return;
        case 4:
            fn_1_B748(arg0, temp_r31);
            break;
    }
}

void fn_1_B4AC(omObjData *arg0, someBits2 *arg1)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 temp_f31;
    s8 temp_r0;
    s32 i;

    arg1->unk2 = -1;

    for (i = 0; i < 3; i++) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_C[9]), lbl_1_data_508[i], &sp20);
        BoardPlayerPosGet(arg1->unk00_bit4, &sp14);
        sp14.y += 66.0f;
        if (BoardVecMinDistCheck(&sp20, &sp14, 100.0f) != 0) {
            sp8 = sp20;
            arg1->unk2 = i;
            break;
        }
    }

    HuAudFXPlay(0x30C);
    BoardModelHookObjReset(lbl_1_bss_C[9], lbl_1_data_508[arg1->unk2]);
    temp_f31 = BoardModelMotionTimeGet(lbl_1_bss_C[9]);
    BoardModelMotionShiftSet(lbl_1_bss_C[9], 0, 15.0f, 10.0f, HU3D_MOTATTR_REV);
    BoardModelMotionSpeedSet(lbl_1_bss_C[9], 0.5f);
    BoardModelMotionTimeSet(lbl_1_bss_C[9], temp_f31);
    BoardModelPosSetV(arg1->unk_06[arg1->unk2], &sp8);
    fn_1_B8E8(3);
    fn_1_BC7C(arg1->unk_06[arg1->unk2]);
}

void fn_1_B688(omObjData *arg0, someBits2 *arg1)
{
    Vec sp8;

    if (arg1->unk1-- != 0) {
        BoardModelPosGet(arg1->unk_06[arg1->unk2], &sp8);
        sp8.x = sp8.x + arg0->trans.x;
        sp8.y += arg0->trans.y;
        sp8.z = sp8.z + arg0->trans.z;
        BoardModelPosSetV(arg1->unk_06[arg1->unk2], &sp8);
        return;
    }

    fn_1_B8E8(0);
}

void fn_1_B748(omObjData *arg0, someBits2 *arg1)
{
    Vec sp14;
    Vec sp8;
    f32 temp_f0;
    s16 temp_r29;

    temp_r29 = arg1->unk_06[arg1->unk2];

    if (arg1->unk1 == 0) {
        HuAudFXPlay(781);
    }

    if (arg1->unk1 < 90) {
        OSu8tof32((u8 *)&arg1->unk1, &temp_f0);
        BoardModelPosGet(temp_r29, &sp8);
        sp8.y += arg0->trans.y;
        BoardModelPosSetV(temp_r29, &sp8);
        BoardModelRotYSet(temp_r29, 8.0f + BoardModelRotYGet(temp_r29));
        BoardModelScaleGet(temp_r29, &sp14);
        sp14.x = sp14.y = sp14.z = cosd(temp_f0);
        BoardModelScaleSetV(temp_r29, &sp14);
        arg1->unk1 += 4;
        return;
    }

    if (lbl_1_data_4E0 != -1) {
        HuAudFXStop(lbl_1_data_4E0);
        lbl_1_data_4E0 = -1;
    }

    fn_1_B8E8(0);
}

void fn_1_B8E8(s32 arg0)
{
    Vec sp14;
    Vec sp8;
    f32 temp_f31;
    someBits2 *temp_r31;
    f32 temp;

    temp_r31 = (someBits2 *)&lbl_1_bss_184->work[0];
    temp_r31->unk00_bit1 = arg0;

    switch (arg0) {
        case 1:
            temp_f31 = 0.31666666f;
            BoardModelMotionStart(lbl_1_bss_C[9], 0, 0x40000001);
            BoardModelMotionSpeedSet(lbl_1_bss_C[9], temp_f31);
            BoardModelMotionTimeSet(lbl_1_bss_C[9], 8.0f);
            return;
        case 2:
            temp_r31->unk00_bit6 = 1;
            return;
        case 3:
            lbl_1_data_4E0 = HuAudFXPlay(0x35F);
            BoardModelPosGet(temp_r31->unk_06[temp_r31->unk2], &sp8);
            BoardPlayerPosGet(temp_r31->unk00_bit4, &sp14);
            temp = 50.0f + sp8.y;
            lbl_1_bss_184->trans.x = (sp14.x - sp8.x) / 10.0f;
            lbl_1_bss_184->trans.z = (sp14.z - sp8.z) / 10.0f;
            lbl_1_bss_184->trans.y = (temp - sp8.y) / 10.0f;
            temp_r31->unk1 = 10;
            return;
        case 4:
            BoardPlayerPosGet(temp_r31->unk00_bit4, &sp14);
            sp14.y += 30.000002f;
            BoardModelPosGet(temp_r31->unk_06[temp_r31->unk2], &sp8);
            lbl_1_bss_184->trans.y = (sp14.y - sp8.y) / 22.0f;
            temp_r31->unk1 = 0;
    }
}

s32 fn_1_BB48(void)
{
    someBits2 *temp = (someBits2 *)&lbl_1_bss_184->work[0];
    return temp->unk00_bit1;
}

void fn_1_BB74(s8 *arg0)
{
    someBits2 *bits = OM_GET_WORK_PTR(lbl_1_bss_184, someBits2);
    s32 i;

    for (i = 0; i < ARRAY_COUNT(bits->unk3); i++) {
        arg0[i] = bits->unk3[i];
    }
}

s32 fn_1_BBC4(void)
{
    someBits2 *bits = OM_GET_WORK_PTR(lbl_1_bss_184, someBits2);
    return bits->unk3[bits->unk2];
}

void fn_1_BBF8(void)
{
    BoardModelMotionStart(lbl_1_bss_C[9], 0, 0);
    BoardModelMotionSpeedSet(lbl_1_bss_C[9], 0.0f);
    BoardModelMotionTimeSet(lbl_1_bss_C[9], 0.0f);
    BoardModelAttrReset(lbl_1_bss_C[9], 0x40000004);
}

void fn_1_BC7C(s16 arg0)
{
    ParticleData *particle;

    lbl_1_bss_190 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 0x00));
    HuSprAnimLock(lbl_1_bss_190);
    lbl_1_data_4E4 = Hu3DParticleCreate(lbl_1_bss_190, 100);
    Hu3DParticleHookSet(lbl_1_data_4E4, fn_1_BE30);
    Hu3DParticleColSet(lbl_1_data_4E4, 0xFF, 0xFF, 0);
    Hu3DModelPosSet(lbl_1_data_4E4, 0.0f, 0.0f, 0.0f);
    Hu3DParticleBlendModeSet(lbl_1_data_4E4, 1);
    Hu3DModelLayerSet(lbl_1_data_4E4, 2);
    particle = Hu3DData[lbl_1_data_4E4].unk_120;
    particle->unk_02 = arg0;
}

void fn_1_BDAC(void)
{
    if (lbl_1_data_4E4 != -1) {
        Hu3DModelKill(lbl_1_data_4E4);
        lbl_1_data_4E4 = -1;
    }
    if (lbl_1_bss_190) {
        HuSprAnimKill(lbl_1_bss_190);
        lbl_1_bss_190 = NULL;
    }
}

void fn_1_BE30(ModelData *model, ParticleData *particle, Mtx matrix)
{
    Vec sp8;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f31;
    HsfanimStruct01 *var_r31;
    s32 i, j;

    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
        particle->unk_00 = 0;
    }

    BoardModelScaleGet(particle->unk_02, &sp8);
    temp_f31 = sp8.x;
    BoardModelPosGet(particle->unk_02, &sp8);

    for (i = 0; i < 22; i++) {
        var_r31 = particle->unk_48;
        for (j = 0; j < particle->unk_30; j++, var_r31++) {
            if (0.0f == var_r31->unk2C) {
                break;
            }
        }
        if (j != particle->unk_30) {
            temp_f30 = 360.0f * ((1.0f / 255.0f) * frand8());
            temp_f29 = temp_f31 * (20.0f + (60.0f * ((1.0f / 255.0f) * frand8())));
            var_r31->unk34.x = (sp8.x + (temp_f29 * sind(temp_f30)));
            var_r31->unk34.z = (sp8.z + (temp_f29 * cosd(temp_f30)));
            var_r31->unk34.y = (sp8.y + (temp_f31 * (-30.0f + (40.0f * ((1.0f / 255.0f) * frand8())))));
            var_r31->unk08.x = (0.5f + (3.0f * ((1.0f / 255.0f) * frand8())));
            var_r31->unk08.y = (0.3f + (2.0f * ((1.0f / 255.0f) * frand8())));
            var_r31->unk40.a = 180;
            var_r31->unk2C = (15.0f * temp_f31);
        }
    }

    var_r31 = particle->unk_48;

    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (0.0f != var_r31->unk2C) {
            var_r31->unk34.y = (var_r31->unk34.y - var_r31->unk08.x);
            var_r31->unk2C = (var_r31->unk2C - var_r31->unk08.y);
            if (var_r31->unk2C <= 0.0f) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}
