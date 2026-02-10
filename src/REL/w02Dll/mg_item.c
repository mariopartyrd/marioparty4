#include "REL/w02Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/hsfdraw.h"
#include "game/objsub.h"
#include "game/pad.h"

#include "ext_math.h"

#include "game/minigame_seq.h"

#if VERSION_JP
#define MDL_ID_SHIFT 0
#else
#define MDL_ID_SHIFT 1
#endif

s32 lbl_1_data_428[14] = {
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

char *lbl_1_data_474[3] = { "item", "item1", "item2" };

s32 lbl_1_data_480[] = { DATA_MAKE_NUM(DATADIR_W02, 0x18), DATA_MAKE_NUM(DATADIR_W02, 0x19), DATA_MAKE_NUM(DATADIR_W02, 0x1A), -1 };

u16 lbl_1_bss_198;
s16 lbl_1_bss_196;
s16 lbl_1_bss_190[3];
s16 lbl_1_bss_18A[3];
s16 lbl_1_bss_184[3];
Vec lbl_1_bss_160[3];
Vec lbl_1_bss_13C[3];
Vec lbl_1_bss_118[3];
float lbl_1_bss_114;
float lbl_1_bss_110;
omObjData *lbl_1_bss_10C;
omObjData *lbl_1_bss_108;
omObjData *lbl_1_bss_104;
Process *lbl_1_bss_100;
Vec lbl_1_bss_DC[3];
s32 lbl_1_bss_D8;
s32 lbl_1_bss_CC[3];
AnimData *lbl_1_bss_C8;

void fn_1_5CF8(void)
{
    BoardModelVisibilitySet(lbl_1_bss_30[10], 1);
}

typedef struct work_mgitem {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
} WorkMGItem;

typedef struct work_mgitem_player {
    Vec unk0[3];
    s16 unk24[3];
    s16 unk2A[3];
    float unk30[2];
    float unk38[2];
    s16 unk40[2];
    Vec unk44[3];
    s16 unk68;
} WorkMGItemPlayer;

void fn_1_8570(void);

void fn_1_5F08(omObjData *object);
void fn_1_606C(omObjData *object);

void fn_1_5D28(void)
{
    Vec spC;
    WorkMGItem *sp8;
    lbl_1_bss_196 = GWSystem.player_curr;
    BoardPlayerPosGet(lbl_1_bss_196, &spC);
    BoardPlayerPosLerpStart(lbl_1_bss_196, &spC, &lbl_1_bss_DC[1], 20);
    while (GWPlayer[lbl_1_bss_196].moving) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(lbl_1_bss_196);
    HuPrcSleep(REFRESH_RATE*2);
    BoardAudSeqPause(0, 1, 1000);
    HuAudFXPlay(781);
    fn_1_8570();
    HuPrcSleep(REFRESH_RATE);
    lbl_1_bss_104 = omAddObjEx(boardObjMan, 257, 0, 0, -1, fn_1_5F08);
    lbl_1_bss_108 = omAddObjEx(boardObjMan, 257, 0, 0, -1, fn_1_606C);
    lbl_1_bss_10C = omAddObjEx(boardObjMan, 257, 0, 0, -1, NULL);
    lbl_1_bss_108->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkMGItemPlayer), MEMORY_DEFAULT_NUM);
    lbl_1_bss_10C->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkMGItem), MEMORY_DEFAULT_NUM);
    sp8 = lbl_1_bss_10C->data;
    lbl_1_bss_198 = 0;
}

void fn_1_602C(void);

void fn_1_5F08(omObjData *object)
{
    if (lbl_1_bss_198 && BoardMGDoneFlagGet() == 1) {
        fn_1_602C();
        omDelObjEx(boardObjMan, object);
    }
}

void fn_1_5F60(void)
{
    lbl_1_bss_198 = 1;
    BoardMGExit();
}

void fn_1_5F90(void)
{
    s32 i;
    for (i = 0; i < 3; i++) {
        BoardModelKill(lbl_1_bss_184[i]);
        BoardModelKill(lbl_1_bss_18A[i]);
    }
    if (lbl_1_bss_C8) {
        HuSprAnimKill(lbl_1_bss_C8);
        lbl_1_bss_C8 = NULL;
    }
}

void fn_1_602C(void)
{
    omDelObjEx(boardObjMan, lbl_1_bss_10C);
    BoardMGDoneFlagSet(0);
}

void fn_1_6248(omObjData *object);

void fn_1_606C(omObjData *object)
{
    WorkMGItemPlayer *temp_r31 = object->data;
    temp_r31->unk24[0] = lbl_1_bss_18A[0];
    temp_r31->unk24[1] = lbl_1_bss_18A[1];
    temp_r31->unk24[2] = lbl_1_bss_18A[2];
    BoardModelPosGet(lbl_1_bss_18A[1], &temp_r31->unk44[0]);
    temp_r31->unk44[0].x -= lbl_1_bss_110;
    BoardModelPosGet(lbl_1_bss_18A[1], &temp_r31->unk44[1]);
    temp_r31->unk44[1].x += lbl_1_bss_110;
    BoardModelPosGet(lbl_1_bss_18A[1], &temp_r31->unk44[2]);
    BoardMusStart(1, 19, 127, 0);
    object->work[0] = REFRESH_RATE*5;
    object->work[1] = 0;
    object->func = fn_1_6248;
}

void fn_1_616C(s16 arg0, s16 arg1)
{
    s32 temp;
    temp = lbl_1_bss_190[arg0];
    lbl_1_bss_190[arg0] = lbl_1_bss_190[arg1];
    lbl_1_bss_190[arg1] = temp;
    temp = lbl_1_bss_184[arg0];
    lbl_1_bss_184[arg0] = lbl_1_bss_184[arg1];
    lbl_1_bss_184[arg1] = temp;
}

void fn_1_6AB0(omObjData *object);

void fn_1_6248(omObjData *object)
{
    float temp_f31;
    float temp_f30;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    u8 sp8[8] = { 0, 1, 1, 2, 0, 1, 0, 2 };
    WorkMGItemPlayer *temp_r31 = object->data;
    s32 temp_r30;
    s32 temp_r28;
    if (object->work[0]) {
        object->work[0]--;
    }
    if (object->work[1] == 0) {
        if (object->work[0] == 0) {
            object->func = fn_1_6AB0;
        }
        temp_r28 = sp8[frand() & 0x7];
        switch (temp_r28) {
            case 0:
                temp_r31->unk2A[0] = temp_r31->unk24[0];
                temp_r31->unk2A[1] = temp_r31->unk24[1];
                sp28 = lbl_1_bss_160[0];
                sp34 = lbl_1_bss_160[1];
                temp_f31 = ((REFRESH_RATE+3)/4);
                break;

            case 1:
                temp_r31->unk2A[0] = temp_r31->unk24[1];
                temp_r31->unk2A[1] = temp_r31->unk24[2];
                sp28 = lbl_1_bss_160[1];
                sp34 = lbl_1_bss_160[2];
                temp_f31 = ((REFRESH_RATE+3)/4);
                break;

            case 2:
                temp_r31->unk2A[0] = temp_r31->unk24[0];
                temp_r31->unk2A[1] = temp_r31->unk24[2];
                temp_f31 = ((REFRESH_RATE+3)/4)*1.5f;
                break;
        }
        temp_r31->unk68 = temp_r28;
        temp_r31->unk30[0] = 180;
        temp_r31->unk30[1] = 0;
        if (temp_r28 != 2) {
            temp_r31->unk40[0] = frandmod(3);
            temp_r31->unk40[1] = frandmod(3);
            while (temp_r31->unk40[1] == temp_r31->unk40[0]) {
                temp_r31->unk40[1] = frandmod(3);
            }
            VECSubtract(&sp34, &sp28, &temp_r31->unk0[0]);
            VECScale(&temp_r31->unk0[0], &temp_r31->unk0[0], 1.0f / temp_f31);
            VECSubtract(&sp28, &sp34, &temp_r31->unk0[1]);
            VECScale(&temp_r31->unk0[1], &temp_r31->unk0[1], 1.0f / temp_f31);
        }
        else {
            temp_r31->unk40[0] = frandmod(2);
            temp_r31->unk40[1] = temp_r31->unk40[0] ^ 1;
        }
        for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
            if (temp_r31->unk40[temp_r30] == 0) {
                temp_r31->unk38[temp_r30] = 180.0f / temp_f31;
            }
            else {
                temp_r31->unk38[temp_r30] = -180.0f / temp_f31;
            }
            if (temp_r30 == 1) {
                temp_r31->unk38[temp_r30] = -temp_r31->unk38[temp_r30];
            }
        }
        object->work[2] = temp_f31;
        object->work[1] = 1;
        BoardModelMotionStart(temp_r31->unk2A[temp_r30], 2, 0x40000001);
        BoardModelMotionSpeedSet(temp_r31->unk2A[temp_r30], 3.0f);
    }
    else {
        for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
            BoardModelPosGet(temp_r31->unk2A[temp_r30], &sp1C);
            sp10 = sp1C;
            if (temp_r31->unk68 != 2) {
                temp_f30 = lbl_1_bss_110;
            }
            else {
                temp_f30 = 2.0f * lbl_1_bss_110;
            }
            if (temp_r31->unk40[temp_r30] != 2) {
                sp1C.x = temp_r31->unk44[temp_r31->unk68].x + (temp_f30 * cosd(temp_r31->unk30[temp_r30]));
                sp1C.z = temp_r31->unk44[temp_r31->unk68].z + (temp_f30 * sind(temp_r31->unk30[temp_r30]));
                temp_r31->unk30[temp_r30] += temp_r31->unk38[temp_r30];
            }
            else {
                VECAdd(&sp1C, &temp_r31->unk0[temp_r30], &sp1C);
            }
            BoardModelPosSetV(temp_r31->unk2A[temp_r30], &sp1C);
            VECSubtract(&sp1C, &sp10, &sp10);
            BoardModelRotGet(temp_r31->unk2A[temp_r30], &sp1C);
            sp1C.y = atan2d(sp10.x, sp10.z);
            BoardModelRotSetV(temp_r31->unk2A[temp_r30], &sp1C);
        }
        if (--object->work[2] == 0) {
            object->work[1] = 0;
            BoardModelMotionStart(temp_r31->unk2A[temp_r30], 1, 0x40000001);
            BoardModelMotionSpeedSet(temp_r31->unk2A[temp_r30], 1.0f);
            for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
                if (temp_r31->unk40[temp_r30] == 0) {
                    BoardModelRotGet(temp_r31->unk2A[temp_r30], &sp1C);
                    sp1C.y = 0;
                    BoardModelRotSetV(temp_r31->unk2A[temp_r30], &sp1C);
                }
                else if (temp_r31->unk40[temp_r30] == 1) {
                    BoardModelRotGet(temp_r31->unk2A[temp_r30], &sp1C);
                    sp1C.y = 180;
                    BoardModelRotSetV(temp_r31->unk2A[temp_r30], &sp1C);
                }
            }
            switch (temp_r31->unk68) {
                case 0:
                    temp_r31->unk24[0] = temp_r31->unk2A[1];
                    temp_r31->unk24[1] = temp_r31->unk2A[0];
                    fn_1_616C(0, 1);
                    break;

                case 1:
                    temp_r31->unk24[1] = temp_r31->unk2A[1];
                    temp_r31->unk24[2] = temp_r31->unk2A[0];
                    fn_1_616C(1, 2);
                    break;

                case 2:
                    temp_r31->unk24[0] = temp_r31->unk2A[1];
                    temp_r31->unk24[2] = temp_r31->unk2A[0];
                    fn_1_616C(0, 2);
                    break;
            }
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                BoardModelPosSetV(temp_r31->unk24[temp_r30], &lbl_1_bss_160[temp_r30]);
            }
        }
    }
}

void fn_1_6CA4(omObjData *object);

void fn_1_6AB0(omObjData *object)
{
    Vec sp8;
    s32 temp_r31;
    s32 temp_r30;
    temp_r30 = 0;
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        BoardModelRotGet(lbl_1_bss_18A[temp_r31], &sp8);
        if (sp8.y < 0.0f) {
            sp8.y += 360.0f;
        }
        if (0.0f == sp8.y) {
            temp_r30++;
            continue;
        }
        if (sp8.y < 180.0f) {
            if (sp8.y < -10.0f) {
                sp8.y = 0;
            }
            else {
                sp8.y -= 10.0f;
            }
        }
        else {
            if (360.0f - sp8.y < 10.0f) {
                sp8.y = 0;
            }
            else {
                sp8.y += 10.0f;
            }
        }
        BoardModelRotSetV(lbl_1_bss_18A[temp_r31], &sp8);
    }
    if (temp_r30 == 3) {
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            BoardModelPosSetV(lbl_1_bss_18A[temp_r31], &lbl_1_bss_160[temp_r31]);
        }
        object->work[0] = MGSeqStartCreate();
        object->func = fn_1_6CA4;
    }
}

void fn_1_73C8(omObjData *object);

void fn_1_6CA4(omObjData *object)
{
    if (!MGSeqStatGet(object->work[0])) {
        lbl_1_bss_10C->func = fn_1_73C8;
        object->func = NULL;
    }
}

void fn_1_6E34(omObjData *object);
void fn_1_85FC(void);
void fn_1_8DAC(void);

void fn_1_6D04(omObjData *object)
{
    Vec sp8;
    BoardModelRotGet(lbl_1_bss_18A[object->work[0]], &sp8);
    sp8.y += 8.0f;
    if (sp8.y >= 360.0f) {
        sp8.y = 0.0f;
        HuAudFXPlay(784);
        lbl_1_bss_100 = HuPrcCreate(fn_1_85FC, 8196, 8192, 0);
        HuPrcDestructorSet2(lbl_1_bss_100, fn_1_8DAC);
        *((u32 *)&lbl_1_bss_100->user_data) = (1 << object->work[0]) | 0x10000000;
        lbl_1_bss_D8 = HuAudFXPlay(863);
        object->func = fn_1_6E34;
    }
    BoardModelRotSetV(lbl_1_bss_18A[object->work[0]], &sp8);
}

void fn_1_6EA8(void);

void fn_1_6E34(omObjData *object)
{
    Process *temp_r31;
    if ((u32)lbl_1_bss_100->user_data & 0x40000000) {
        temp_r31 = HuPrcCreate(fn_1_6EA8, 8196, 6144, 0);
        temp_r31->user_data = object;
        object->func = NULL;
    }
}

void fn_1_72E4(omObjData *object);

void fn_1_6EA8(void)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;

    temp_r31 = lbl_1_bss_108->work[0];
    BoardWinCreate(2, MAKE_MESSID(19, 24), 4);
    BoardWinInsertMesSet(MAKE_MESSID(8, lbl_1_bss_190[temp_r31]), 1);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerPosGet(lbl_1_bss_196, &sp20);
    BoardModelPosGet(lbl_1_bss_184[temp_r31], &sp2C);
    sp20.y = sp2C.y = 0;
    VECSubtract(&sp20, &sp2C, &sp14);
    temp_f30 = VECMag(&sp14);
    VECScale(&sp14, &sp14, 1.0f / REFRESH_RATE);
    for (temp_r30 = 0; temp_r30 < REFRESH_RATE; temp_r30++) {
        BoardModelPosGet(lbl_1_bss_184[temp_r31], &sp2C);
        VECAdd(&sp2C, &sp14, &sp2C);
        BoardModelPosSetV(lbl_1_bss_184[temp_r31], &sp2C);
        HuPrcVSleep();
    }
    BoardModelPosGet(lbl_1_bss_184[temp_r31], &sp2C);
    sp2C.x = sp20.x;
    sp2C.z = sp20.z;
    BoardModelPosSetV(lbl_1_bss_184[temp_r31], &sp2C);
    BoardPlayerMotBlendSet(lbl_1_bss_196, 0, 15);
    while (!BoardPlayerMotBlendCheck(lbl_1_bss_196)) {
        HuPrcVSleep();
    }
    HuPrcKill(lbl_1_bss_100);
    lbl_1_bss_100 = NULL;
    HuPrcVSleep();
    HuAudFXPlay(781);
    BoardModelPosGet(lbl_1_bss_184[temp_r31], &sp2C);
    BoardModelScaleGet(lbl_1_bss_184[temp_r31], &sp8);
    temp_f31 = sp8.x;
    temp_f29 = -0.04f;
    temp_f30 = (sp20.y - sp2C.y) / (REFRESH_RATE/2);
    temp_r29 = 0;
    HuAudFXFadeOut(lbl_1_bss_D8, (((REFRESH_RATE*500)+30)/60)-1);
    while (!temp_r29) {
        sp2C.y += temp_f30;
        temp_f31 += temp_f29;
        if (temp_f31 < 0.0f) {
            temp_f31 = 0.0f;
            temp_r29 = 1;
        }
        sp8.x = sp8.y = sp8.z = temp_f31;
        BoardModelPosSetV(lbl_1_bss_184[temp_r31], &sp2C);
        BoardModelScaleSetV(lbl_1_bss_184[temp_r31], &sp8);
        HuPrcVSleep();
    }
    HuAudFXStop(lbl_1_bss_D8);
    BoardModelVisibilitySet(lbl_1_bss_184[temp_r31], 0);
    BoardPlayerItemAdd(lbl_1_bss_196, lbl_1_bss_190[temp_r31]);
    omVibrate(lbl_1_bss_196, 12, 6, 6);
    temp_r28 = HuAudSStreamPlay(2);
    BoardPlayerMotionShiftSet(lbl_1_bss_196, 7, 0, 5, HU3D_MOTATTR_NONE);
    while (!BoardPlayerMotionEndCheck(lbl_1_bss_196)) {
        HuPrcVSleep();
    }
    HuPrcSleep(REFRESH_RATE/2);
    while (HuAudSStreamStatGet(temp_r28)) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(0, 0, 1000);
    HuAudFXPlay(68);
    W02MesExec(MAKE_MESSID(0x13, 0x19));
    lbl_1_bss_108->func = fn_1_72E4;
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_72E4(omObjData *object)
{
    fn_1_5F60();
    omDelObjEx(boardObjMan, object);
}

void fn_1_732C(s32 arg0)
{
    lbl_1_bss_108->work[0] = arg0;
    lbl_1_bss_108->func = fn_1_6D04;
}

void fn_1_7358(WorkMGItem *arg0)
{
    if (--arg0->unk2 == 0) {
        arg0->unk2 = REFRESH_RATE;
        if (--arg0->unk0 >= 0) {
            MGSeqParamSet(arg0->unk4, 1, arg0->unk0);
        }
    }
}

void fn_1_74E4(omObjData *object);

void fn_1_73C8(omObjData *object)
{
    float sp8[2];
    WorkMGItem *temp_r31;
    temp_r31 = object->data;
    temp_r31->unk0 = 5;
    temp_r31->unk2 = REFRESH_RATE;
    temp_r31->unk4 = MGSeqTimerCreateXY(temp_r31->unk0, 288, 64);
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x13, 0x1B));
    temp_r31->unk6 = HuWinCreate(-10000, 368, sp8[0], sp8[1], 0);
    HuWinMesSet(temp_r31->unk6, MAKE_MESSID(0x13, 0x1B));
    HuWinBGTPLvlSet(temp_r31->unk6, 0);
    HuWinMesSpeedSet(temp_r31->unk6, 0);
    temp_r31->unk8 = 1;
    temp_r31->unkA = frandmod(30) + 15;
    temp_r31->unkC = 0;
    object->func = fn_1_74E4;
}

void fn_1_7898(omObjData *arg0, s32 *arg1, s32 *arg2);

void fn_1_7750(omObjData *object);
void fn_1_7818(omObjData *object);

void fn_1_74E4(omObjData *object)
{
    s32 spC;
    s32 sp8;
    WorkMGItem *temp_r31;
    s32 temp_r29;
    temp_r31 = object->data;
    fn_1_7358(temp_r31);
    temp_r29 = GWPlayer[lbl_1_bss_196].port;
    if (GWPlayer[lbl_1_bss_196].com) {
        fn_1_7898(object, &spC, &sp8);
    }
    else {
        spC = HuPadDStkRep[temp_r29];
        sp8 = HuPadBtnDown[temp_r29];
    }
    if ((sp8 & PAD_BUTTON_A) || temp_r31->unk0 < 0) {
        MGSeqParamSet(temp_r31->unk4, 2, -1);
        HuWinKill(temp_r31->unk6);
        BoardPlayerMotBlendSet(lbl_1_bss_196, 180, 10);
        BoardAudSeqFadeOut(1, 1000);
        object->func = fn_1_7818;
    }
    else if (spC & PAD_BUTTON_LEFT) {
        if (temp_r31->unk8 != 0) {
            temp_r31->unk8--;
            BoardPlayerPosLerpStart(lbl_1_bss_196, &lbl_1_bss_DC[temp_r31->unk8 + 1], &lbl_1_bss_DC[temp_r31->unk8], REFRESH_RATE/5);
            object->func = fn_1_7750;
        }
    }
    else if (spC & PAD_BUTTON_RIGHT) {
        if (temp_r31->unk8 != 2) {
            temp_r31->unk8++;
            BoardPlayerPosLerpStart(lbl_1_bss_196, &lbl_1_bss_DC[temp_r31->unk8 - 1], &lbl_1_bss_DC[temp_r31->unk8], REFRESH_RATE/5);
            object->func = fn_1_7750;
        }
    }
}

void fn_1_7750(omObjData *object)
{
    WorkMGItem *temp_r31 = object->data;
    fn_1_7358(temp_r31);
    if (!GWPlayer[lbl_1_bss_196].moving) {
        BoardPlayerIdleSet(lbl_1_bss_196);
        object->func = fn_1_74E4;
    }
}

void fn_1_7818(omObjData *object)
{
    if (BoardPlayerMotBlendCheck(lbl_1_bss_196)) {
        fn_1_732C(((WorkMGItem *)object->data)->unk8);
        object->func = NULL;
    }
}

void fn_1_7898(omObjData *arg0, s32 *arg1, s32 *arg2)
{
    WorkMGItem *temp_r31;
    s32 temp_r28;
    temp_r31 = arg0->data;
    *arg1 = *arg2 = 0;
    if (temp_r31->unkA) {
        temp_r31->unkA--;
    }
    else {
        temp_r31->unkA = frandmod(30) + 15;
        if (temp_r31->unkC == 4) {
            *arg2 |= PAD_BUTTON_A;
        }
        else if ((s32)frandmod(10) < 4) {
            *arg2 |= PAD_BUTTON_A;
        }
        else {
            temp_r28 = frandBool();
            if ((temp_r28 == 0 && temp_r31->unk8 != 2) || temp_r31->unk8 == 0) {
                *arg1 |= PAD_BUTTON_RIGHT;
            }
            else if ((temp_r28 == 1 && temp_r31->unk8 != 0) || temp_r31->unk8 == 2) {
                *arg1 |= PAD_BUTTON_LEFT;
            }
            temp_r31->unkC++;
        }
    }
}

static inline void WriteTrans(s32 index, float value)
{
    Hu3DData[BoardModelIDGet(lbl_1_bss_184[index])].unk_F0[1][3] = value;
}

void fn_1_79BC(s16 *arg0)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f25;
    Vec sp8;
    s32 temp_r31;
    s32 temp_r29;
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        lbl_1_bss_190[temp_r31] = arg0[temp_r31];
        lbl_1_bss_184[temp_r31] = BoardModelCreate(lbl_1_data_428[lbl_1_bss_190[temp_r31]], NULL, 0);
        if (lbl_1_bss_190[temp_r31] == 5) {
            WriteTrans(temp_r31, -50.0f);
        }
        if (arg0[temp_r31] == 4) {
            BoardModelMotionSpeedSet(lbl_1_bss_184[temp_r31], 0);
        }
        BoardModelVisibilitySet(lbl_1_bss_184[temp_r31], 0);
        if (arg0[temp_r31] == 11) {
            BoardModelAttrSet(lbl_1_bss_184[temp_r31], 0x40000001);
        }
    }
    if (lbl_1_bss_C8 == NULL) {
        lbl_1_bss_C8 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 0x00));
        HuSprAnimLock(lbl_1_bss_C8);
    }
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        lbl_1_bss_18A[temp_r31] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W02, 0x17), lbl_1_data_480, 0);
        lbl_1_bss_118[temp_r31].x = lbl_1_bss_118[temp_r31].z = 0.1f;
        lbl_1_bss_118[temp_r31].y = 0.1f;
        lbl_1_bss_13C[temp_r31].x = 0;
        lbl_1_bss_13C[temp_r31].y = lbl_1_bss_13C[temp_r31].z = 0;
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_30[10]), lbl_1_data_474[temp_r31], &lbl_1_bss_160[temp_r31]);
        BoardModelPosSetV(lbl_1_bss_18A[temp_r31], &lbl_1_bss_160[temp_r31]);
        BoardModelRotSetV(lbl_1_bss_18A[temp_r31], &lbl_1_bss_13C[temp_r31]);
        BoardModelScaleSetV(lbl_1_bss_18A[temp_r31], &lbl_1_bss_118[temp_r31]);
    }
    lbl_1_bss_114 = lbl_1_bss_160[0].y;
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        BoardModelPosGet(lbl_1_bss_30[10], &lbl_1_bss_DC[temp_r31]);
        lbl_1_bss_DC[temp_r31].x = lbl_1_bss_160[temp_r31].x;
        lbl_1_bss_DC[temp_r31].z = lbl_1_bss_160[temp_r31].z + 200.0f;
        BoardModelMotionStart(lbl_1_bss_18A[temp_r31], 3, 0);
    }
    lbl_1_bss_110 = fabs(lbl_1_bss_160[0].x - lbl_1_bss_160[1].x) / 2;
    temp_f31 = 0;
    temp_f29 = 20;
    sp8.x = 0.04f;
    sp8.y = 0.04f;
    sp8.z = 0.04f;
    for (temp_r29 = 0; temp_r29 < 3;) {
        temp_f30 = temp_f29 - ((7.0f / 60.0f) * (0.25f * (temp_f31 * temp_f31)));
        temp_f31++;
        temp_r29 = 0;
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            lbl_1_bss_160[temp_r31].y += temp_f30;
            if (lbl_1_bss_160[temp_r31].y < lbl_1_bss_114) {
                lbl_1_bss_160[temp_r31].y = lbl_1_bss_114;
                temp_r29++;
            }
            BoardModelPosSetV(lbl_1_bss_18A[temp_r31], &lbl_1_bss_160[temp_r31]);
            VECAdd(&lbl_1_bss_118[temp_r31], &sp8, &lbl_1_bss_118[temp_r31]);
            if (lbl_1_bss_118[temp_r31].x > 0.7f) {
                lbl_1_bss_118[temp_r31].x = 0.7f;
            }
            if (lbl_1_bss_118[temp_r31].y > 0.7f) {
                lbl_1_bss_118[temp_r31].y = 0.7f;
            }
            if (lbl_1_bss_118[temp_r31].z > 0.7f) {
                lbl_1_bss_118[temp_r31].z = 0.7f;
            }
            BoardModelScaleSetV(lbl_1_bss_18A[temp_r31], &lbl_1_bss_118[temp_r31]);
        }
        HuPrcVSleep();
    }
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        lbl_1_bss_118[temp_r31].x = lbl_1_bss_118[temp_r31].y = lbl_1_bss_118[temp_r31].z = 0.7f;
        BoardModelScaleSetV(lbl_1_bss_18A[temp_r31], &lbl_1_bss_118[temp_r31]);
        BoardModelMotionStart(lbl_1_bss_18A[temp_r31], 1, 0x40000001);
    }
    lbl_1_bss_100 = HuPrcCreate(fn_1_85FC, 8196, 8192, 0);
    HuPrcDestructorSet2(lbl_1_bss_100, fn_1_8DAC);
    *((u32 *)&lbl_1_bss_100->user_data) = 7;
    HuAudFXPlay(866);
    while (((u32)lbl_1_bss_100->user_data & 0x40000000) == 0) {
        HuPrcVSleep();
    }
}

void fn_1_8244(u16 arg0)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    Vec spC;

    s32 temp_r31;
    s32 temp_r30;
    if (arg0) {
        fn_1_8570();
    }
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        BoardModelMotionStart(lbl_1_bss_18A[temp_r31], 3, 0);
    }
    temp_f31 = 0;
    temp_f29 = 20;
    spC.x = -0.02f;
    spC.y = -0.02f;
    spC.z = -0.02f;
    for (temp_r30 = 0; temp_r30 < 3;) {
        temp_f30 = temp_f29 - ((7.0f / 60.0f) * (0.25f * (temp_f31 * temp_f31)));
        temp_f31++;
        temp_r30 = 0;
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            lbl_1_bss_160[temp_r31].y += temp_f30;
            BoardModelPosSetV(lbl_1_bss_18A[temp_r31], &lbl_1_bss_160[temp_r31]);
            if (temp_f30 < 0.0f) {
                VECAdd(&lbl_1_bss_118[temp_r31], &spC, &lbl_1_bss_118[temp_r31]);
                if (lbl_1_bss_118[temp_r31].x < 0.0f) {
                    lbl_1_bss_118[temp_r31].x = 0.0f;
                }
                if (lbl_1_bss_118[temp_r31].y < 0.0f) {
                    lbl_1_bss_118[temp_r31].y = 0.0f;
                }
                if (lbl_1_bss_118[temp_r31].z < 0.0f) {
                    lbl_1_bss_118[temp_r31].z = 0.0f;
                }
                BoardModelScaleSetV(lbl_1_bss_18A[temp_r31], &lbl_1_bss_118[temp_r31]);
                if (lbl_1_bss_118[temp_r31].x == 0.0f) {
                    temp_r30++;
                }
            }
        }
        HuPrcVSleep();
    }
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        BoardModelVisibilitySet(lbl_1_bss_18A[temp_r31], 0);
    }
}

void fn_1_8570(void)
{
    u32 temp_r31;
    temp_r31 = (u32)lbl_1_bss_100->user_data;
    temp_r31 |= 0x20000000;
    *(u32 *)&lbl_1_bss_100->user_data = temp_r31;
    while (((u32)lbl_1_bss_100->user_data & 0x80000000) == 0) {
        HuPrcVSleep();
    }
    HuPrcKill(lbl_1_bss_100);
    lbl_1_bss_100 = NULL;
}

void fn_1_8E38(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_1_85FC(void)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;

    Vec sp20[3];
    Vec sp14;
    float sp8[3];
    s32 temp_r31;
    u32 temp_r30;
    u32 temp_r29;
    s32 temp_r28;
    ParticleData *temp_r27;
    temp_r30 = (u32)HuPrcCurrentGet()->user_data;
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        temp_r29 = 1 << temp_r31;
        if (temp_r30 & temp_r29) {
            BoardModelPosGet(lbl_1_bss_18A[temp_r31], &sp20[temp_r31]);
            sp20[temp_r31].y += 50.0f;
            sp8[temp_r31] = 0.0f;
            BoardModelPosSetV(lbl_1_bss_184[temp_r31], &sp20[temp_r31]);
            sp14.x = sp14.y = sp14.z = sp8[temp_r31];
            BoardModelScaleSetV(lbl_1_bss_184[temp_r31], &sp14);
            BoardModelVisibilitySet(lbl_1_bss_184[temp_r31], 1);
            temp_f28 = 130.0f + sp20[temp_r31].y;
            if (temp_r30 & 0x10000000) {
                lbl_1_bss_CC[temp_r31] = Hu3DParticleCreate(lbl_1_bss_C8, 100);
                temp_r27 = Hu3DData[lbl_1_bss_CC[temp_r31]].unk_120;
                temp_r27->unk_02 = lbl_1_bss_184[temp_r31];
                Hu3DParticleHookSet(lbl_1_bss_CC[temp_r31], fn_1_8E38);
                Hu3DParticleColSet(lbl_1_bss_CC[temp_r31], 255, 255, 0);
                Hu3DModelPosSet(lbl_1_bss_CC[temp_r31], 0, 0, 0);
                Hu3DParticleBlendModeSet(lbl_1_bss_CC[temp_r31], 1);
                Hu3DModelLayerSet(lbl_1_bss_CC[temp_r31], 2);
            }
        }
    }
    temp_f31 = 12;
    temp_f29 = 0.05f;
    while (1) {
        temp_r28 = 0;
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            temp_r29 = 1 << temp_r31;
            if (temp_r30 & temp_r29) {
                temp_r28++;
                BoardModelPosGet(lbl_1_bss_184[temp_r31], &sp20[temp_r31]);
                sp20[temp_r31].y += temp_f31;
                if (sp20[temp_r31].y >= temp_f28) {
                    sp20[temp_r31].y = temp_f28;
                    temp_r28--;
                }
                BoardModelPosSetV(lbl_1_bss_184[temp_r31], &sp20[temp_r31]);
                sp8[temp_r31] += temp_f29;
                if (sp8[temp_r31] > 1.0f) {
                    sp8[temp_r31] = 1.0f;
                }
                sp14.x = sp14.y = sp14.z = sp8[temp_r31];
                BoardModelScaleSetV(lbl_1_bss_184[temp_r31], &sp14);
            }
        }
        temp_f31 *= 0.92f;
        if (temp_r28 == 0) {
            break;
        }
        HuPrcVSleep();
    }
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        temp_r29 = 1 << temp_r31;
        if (temp_r30 & temp_r29) {
            sp8[temp_r31] = 1.0f;
            sp14.x = sp14.y = sp14.z = sp8[temp_r31];
            BoardModelScaleSetV(lbl_1_bss_184[temp_r31], &sp14);
        }
    }
    temp_r30 |= 0x40000000;
    *((u32 *)&HuPrcCurrentGet()->user_data) = temp_r30;
    temp_f30 = 0;
    while (1) {

        temp_r30 = (u32)HuPrcCurrentGet()->user_data;
        if (temp_r30 & 0x20000000) {
            break;
        }
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            temp_r29 = 1 << temp_r31;
            if (temp_r30 & temp_r29) {
                BoardModelPosGet(lbl_1_bss_184[temp_r31], &sp20[temp_r31]);
                sp20[temp_r31].y += sind(temp_f30) * 0.25f;
                BoardModelPosSetV(lbl_1_bss_184[temp_r31], &sp20[temp_r31]);
            }
        }
        temp_f30 += 5.0f;
        if (temp_f30 >= 360.0f) {
            temp_f30 -= 360.0f;
        }

        HuPrcVSleep();
    }
    temp_f31 = -12;
    temp_f29 = -0.05f;
    while (1) {
        temp_r28 = 0;
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            temp_r29 = 1 << temp_r31;
            if (temp_r30 & temp_r29) {
                temp_r28++;
                BoardModelPosGet(lbl_1_bss_184[temp_r31], &sp20[temp_r31]);
                sp20[temp_r31].y += temp_f31;
                BoardModelPosSetV(lbl_1_bss_184[temp_r31], &sp20[temp_r31]);
                sp8[temp_r31] += temp_f29;
                if (sp8[temp_r31] < 0.0f) {
                    sp8[temp_r31] = 0.0f;
                }
                if (sp8[temp_r31] == 0.0f) {
                    temp_r28--;
                }
                sp14.x = sp14.y = sp14.z = sp8[temp_r31];
                BoardModelScaleSetV(lbl_1_bss_184[temp_r31], &sp14);
            }
        }
        temp_f31 *= 0.92f;
        if (temp_r28 == 0) {
            break;
        }
        HuPrcVSleep();
    }
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        temp_r29 = 1 << temp_r31;
        if (temp_r30 & temp_r29) {
            sp14.x = sp14.y = sp14.z = 1.0f;
            BoardModelScaleSetV(lbl_1_bss_184[temp_r31], &sp14);
            BoardModelVisibilitySet(lbl_1_bss_184[temp_r31], 0);
        }
    }
    temp_r30 |= 0x80000000;
    *((u32 *)&HuPrcCurrentGet()->user_data) = temp_r30;
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_8DAC(void)
{
    s32 temp_r31;
    u32 temp_r30 = (u32)HuPrcCurrentGet()->user_data;
    u32 temp_r29;
    if (temp_r30 & 0x10000000) {
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            temp_r29 = 1 << temp_r31;
            if (temp_r30 & temp_r29) {
                Hu3DModelKill(lbl_1_bss_CC[temp_r31]);
            }
        }
    }
}

void fn_1_8E38(ModelData *model, ParticleData *particle, Mtx matrix)
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
