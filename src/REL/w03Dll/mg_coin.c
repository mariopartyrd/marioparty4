#include "REL/w03Dll.h"
#include "dolphin.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/chrman.h"
#include "game/hsfdraw.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/pad.h"

#include "game/board/window.h"

#ifndef __MWERKS__
#include "game/audio.h"
#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/objsub.h"
#endif

#include "ext_math.h"
#include <string.h>

// structs
typedef struct someBits3 { // make sure this is defined correctly
    /* 0x00 */ struct {
        u8 unk00_bit0 : 1;
        u8 unk00_bit1 : 4;
        u8 unk00_bit5 : 2;
        u8 unk00_bit7 : 1;
    };
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 unk_04;
    s16 unk_06[3];
    s32 unk_0C;
} someBits3;

typedef struct unkTemp {
    s8 unk0;
    u8 unk1;
    s16 unk_02;
    f32 unk4;
    Vec unk8;
} unkTemp;

typedef struct unkTemp2 {
    /* 0x00 */ struct {
        u8 unk00_bit0 : 1;
    };
    char unk_01[3];
    s8 unk4;
    char unk_05[3];
    f32 unk8;
    unkTemp *unk_0C;
} unkTemp2;

// function signatures
void fn_1_7C98(void);
void fn_1_7C38(void);
s32 fn_1_7D18(s32 arg0);
void fn_1_8140(s32 arg0);
void fn_1_81E0(s32 arg0);
void fn_1_8530(omObjData *arg0);
void fn_1_84A8(s32 arg0);
void fn_1_8698(omObjData *arg0, someBits3 *arg1);
void fn_1_8C08(omObjData *arg0, someBits3 *arg1);
void fn_1_8E44(omObjData *arg0, someBits3 *arg1);
void fn_1_9044(omObjData *arg0, someBits3 *arg1);
void fn_1_91B8(void);
void fn_1_9230(s32 arg0);
void fn_1_9384(void);
void fn_1_9474(s32 arg0);
void fn_1_97F8(s32 arg0);
void fn_1_9A1C(unkTemp2 *arg0);

// data
s32 lbl_1_data_450 = -1;
s16 lbl_1_data_454 = -1;
s16 lbl_1_data_456 = -1;
s16 lbl_1_data_458 = -1;
s32 lbl_1_data_45C[] = { DATA_MAKE_NUM(DATADIR_W03, 0x21), DATA_MAKE_NUM(DATADIR_W03, 0x22), DATA_NUM_LISTEND };

// BSS
char lbl_1_bss_150[0x30];
s16 lbl_1_bss_14E;
s8 lbl_1_bss_14C;
omObjData *lbl_1_bss_148;
omObjData *lbl_1_bss_144;
Process *lbl_1_bss_140;

void fn_1_7ABC(void)
{
    lbl_1_data_456 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W03, 0x20), lbl_1_data_45C, 0);
    BoardModelHookSet(lbl_1_bss_C[7], "phei", lbl_1_data_456);
    BoardModelMotionStart(lbl_1_data_456, 2, 0x40000002);
    BoardModelRotYSet(lbl_1_data_456, -45.0f);
}

void fn_1_7B58(void)
{
    if (lbl_1_data_456 != -1) {
        BoardModelKill(lbl_1_data_456);
        lbl_1_data_456 = -1;
    }
}

void fn_1_7BA8(void)
{
    BoardRollDispSet(0);
    lbl_1_bss_140 = HuPrcChildCreate(&fn_1_7C98, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_140, &fn_1_7C38);
    while (lbl_1_bss_140) {
        HuPrcVSleep();
    }
    BoardRollDispSet(1);
}

void fn_1_7C38(void)
{
    if (lbl_1_data_454 != -1) {
        HuWinKill(lbl_1_data_454);
        lbl_1_data_454 = -1;
    }
    lbl_1_bss_140 = 0;
}

void fn_1_7C98(void)
{
    s32 temp_r31;

    temp_r31 = GWSystem.player_curr;
    lbl_1_bss_14C = 0;
    lbl_1_bss_14E = 0;
    if (fn_1_7D18(temp_r31) != 0) {
        fn_1_8140(temp_r31);
        fn_1_9474(temp_r31);
        fn_1_9230(temp_r31);
    }
    HuPrcEnd();
}

s32 fn_1_7D18(s32 arg0)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 var_f31;
    s16 model;
    s16 space;
    s16 temp_r28;
    f32 arctan;

    BoardWinCreateChoice(2, MAKE_MESSID(22, 21), 2, 0);

    if (GWPlayer[arg0].com != 0) {
        BoardComKeySetLeft();
    }

    BoardWinWait();
    BoardWinKill();

    if (BoardWinChoiceGet() != 0) {
        BoardWinCreate(2, MAKE_MESSID(22, 24), 2);
        BoardWinWait();
        BoardWinKill();
        return 0;
    }

    BoardAudSeqPause(0, 1, 1000);

    sp14.x = 0.0f;
    sp14.y = 200.0f;
    sp14.z = 0.0f;
    sp8.x = -10.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;

    BoardCameraMotionStartEx(lbl_1_bss_C[7], &sp8, &sp14, 1500.0f, -1.0f, 21);
    space = GWPlayer[arg0].space_curr;
    temp_r28 = BoardSpaceLinkFlagSearch(0, space, 0x02000000);
    BoardPlayerPosGet(arg0, &sp2C);
    BoardSpacePosGet(0, temp_r28, &sp38);
    VECSubtract(&sp38, &sp2C, &sp20);
    VECNormalize(&sp20, &sp20);
    BoardPlayerRotYSet(arg0, atan2d(-sp20.x, -sp20.z));
    HuPrcSleep(0x1E);
    model = BoardModelIDGet(lbl_1_bss_C[7]);
    Hu3DModelObjPosGet(model, "phei", &sp38);

    if (GWPlayer[arg0].character == 5) {
        var_f31 = 54.000004f;
    }
    else {
        var_f31 = 39.0f;
    }

    sp38.x += var_f31 * sind(180.0f + BoardModelRotYGet(lbl_1_data_456));
    sp38.z += var_f31 * cosd(180.0f + BoardModelRotYGet(lbl_1_data_456));

    BoardPlayerPosGet(arg0, &sp2C);
    BoardPlayerPosLerpStart(arg0, &sp2C, &sp38, 0x14);

    while (GWPlayer[arg0].moving != 0) {
        BoardModelPosGet(lbl_1_bss_C[10], &sp2C);
        BoardPlayerPosGet(arg0, &sp38);
        VECSubtract(&sp38, &sp2C, &sp20);
        arctan = atan2d(sp20.x, sp20.z);
        BoardModelRotYSet(lbl_1_bss_C[10], arctan);
        HuPrcVSleep();
    }

    BoardPlayerMotBlendSet(arg0, -0x2D, 7);

    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }

    return 1;
}

void fn_1_8140(s32 arg0)
{
    s16 temp_r31;

    fn_1_81E0(arg0);
    BoardMusStart(1, 0x16, 0x7F, 0);
    temp_r31 = MGSeqStartCreate();

    while (MGSeqStatGet(temp_r31)) {
        HuPrcVSleep();
    }

    fn_1_9384();
    fn_1_84A8(0);

    while (lbl_1_bss_144) {
        HuPrcVSleep();
    }

    fn_1_91B8();
}

s32 lbl_1_data_470[] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x66),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x66),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x66),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x66),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x66),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x66),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x66),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x66),
};

s32 lbl_1_data_490[] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x67),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x67),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x67),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x67),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x67),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x67),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x67),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x67),
};

void fn_1_81E0(s32 arg0)
{
    Vec sp8;
    omObjData *temp_r3;
    f32 temp_f31;
    s32 temp_r28;
    s32 temp_r5;
    s32 temp_r5_2;
    someBits3 *temp_r31;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, fn_1_8530);
    lbl_1_bss_144 = temp_r3;
    temp_r31 = OM_GET_WORK_PTR(temp_r3, someBits3);
    temp_r31->unk00_bit0 = 0;
    temp_r31->unk00_bit5 = arg0;
    temp_r31->unk00_bit1 = 4; //?
    temp_r31->unk1 = 0;
    temp_r31->unk2 = 5;
    temp_r31->unk3 = 0x3C;
    temp_r31->unk_0C = -1;
    lbl_1_data_450 = -1;
    temp_r3->trans.x = 0.0f;
    temp_r3->trans.y = 0.0f;
    temp_r28 = GWPlayer[arg0].character;
    temp_r31->unk_06[1] = BoardPlayerMotionCreate(arg0, lbl_1_data_470[temp_r28]);
    temp_r31->unk_06[2] = BoardPlayerMotionCreate(arg0, lbl_1_data_490[temp_r28]);
    temp_f31 = 0.3f;
    temp_r31->unk_06[0] = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W03, 0x09), NULL, 0);
    BoardModelVisibilitySet(temp_r31->unk_06[0], 0);
    BoardPlayerPosGet(arg0, &sp8);
    BoardModelPosSetV(temp_r31->unk_06[0], &sp8);
    BoardModelScaleSet(temp_r31->unk_06[0], temp_f31, temp_f31, temp_f31);
    BoardModelMotionStart(temp_r31->unk_06[0], 0, 0x40000001);
    BoardModelMotionStart(lbl_1_data_456, 0, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_data_456, temp_r3->trans.x);
    BoardPlayerMotionStart(arg0, temp_r31->unk_06[1], 0x40000001);
    BoardPlayerMotionSpeedSet(arg0, temp_r3->trans.x);
    lbl_1_data_458 = BoardModelMotionCreate(lbl_1_bss_C[10], DATA_MAKE_NUM(DATADIR_W03, 0x25));
}

void fn_1_8434(someBits3 *arg0)
{
    if (arg0->unk_06[1] != -1) {
        BoardPlayerMotionKill(arg0->unk00_bit5, arg0->unk_06[1]);
    }
    if (arg0->unk_06[2] != -1) {
        BoardPlayerMotionKill(arg0->unk00_bit5, arg0->unk_06[2]);
    }
    if (arg0->unk_06[0] != -1) {
        BoardModelKill(arg0->unk_06[0]);
    }
}

void fn_1_84A8(s32 arg0)
{
    someBits3 *temp_r31;

    if (lbl_1_bss_144) {
        temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_144, someBits3);
        temp_r31->unk00_bit1 = arg0;
        if (arg0 == 0) {
            temp_r31->unk_04 = MGSeqTimerCreateXY(temp_r31->unk2, 288, 64);
        }
    }
}

void fn_1_8530(omObjData *arg0)
{
    s32 temp_r0;
    someBits3 *temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, someBits3);

    if ((temp_r31->unk00_bit0 != 0) || (BoardIsKill() != 0)) {
        if (temp_r31->unk_04 != -1) {
            MGSeqParamSet(temp_r31->unk_04, 2, -1);
        }
        if (temp_r31->unk_06[1] != -1) {
            BoardPlayerMotionKill(temp_r31->unk00_bit5, temp_r31->unk_06[1]);
        }
        if (temp_r31->unk_06[2] != -1) {
            BoardPlayerMotionKill(temp_r31->unk00_bit5, temp_r31->unk_06[2]);
        }
        if (temp_r31->unk_06[0] != -1) {
            BoardModelKill(temp_r31->unk_06[0]);
        }
        lbl_1_bss_144 = NULL;

        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }

    if (temp_r31->unk1 != 0) {
        temp_r31->unk1--;
        return;
    }

    switch (temp_r31->unk00_bit1) {
        case 0:
            fn_1_8698(arg0, temp_r31);
            return;
        case 1:
            fn_1_8C08(arg0, temp_r31);
            return;
        case 2:
            fn_1_8E44(arg0, temp_r31);
            return;
        case 3:
            fn_1_9044(arg0, temp_r31);
            /* fallthrough */
        case 4:
            break;
    }
}

void fn_1_8698(omObjData *arg0, someBits3 *arg1)
{
    s32 temp_r27;
    u32 var_r28;
    u32 var_r26;
    f32 temp;
    Vec sp8;

    if (arg1->unk3 != 0) {
        arg1->unk3--;
    }
    else {
        if (arg1->unk2 != 0) {
            arg1->unk2--;
        }
        else {
            MGSeqParamSet(arg1->unk_04, 2, -1);
            arg1->unk_04 = -1;
            arg1->unk00_bit1 = 1;
            temp = BoardModelMotionTimeGet(lbl_1_bss_C[7]);

            if (temp == 0.0f) {
                temp = 1.0f;
            }

            if (lbl_1_bss_14E > 30) {
                lbl_1_bss_14E = 30;
            }

            OSu16tof32((u16 *)&lbl_1_bss_14E, &arg0->rot.x); //??
            BoardModelAttrReset(lbl_1_data_456, 0x40000002);
            BoardModelAttrReset(lbl_1_bss_C[7], 0x40000002);
            BoardModelAttrReset(lbl_1_bss_C[10], 0x40000002);
            BoardPlayerModelAttrReset(arg1->unk00_bit5, 0x40000002);
            BoardModelMotionStart(lbl_1_data_456, 1, 0x40000001);
            BoardModelMotionStart(lbl_1_bss_C[7], 0, 0);
            BoardModelMotionStart(lbl_1_bss_C[10], lbl_1_data_458, 0);
            BoardPlayerMotionStart(arg1->unk00_bit5, arg1->unk_06[2], 0);
            BoardModelVisibilitySet(arg1->unk_06[0], 0);
            arg1->unk_0C = HuAudFXPlay(0x43F);
            BoardModelPosGet(lbl_1_data_456, &sp8);
            arg0->trans.z = sp8.y;
            arg0->rot.y = 16.666666f * arg0->rot.x;
            arg0->scale.x = BoardModelMotionMaxTimeGet(lbl_1_bss_C[7]);
            HuWinDispOff(lbl_1_data_454);
            BoardCameraMotionStartEx(-1, NULL, NULL, 1900.0f, -1.0f, 21);
            return;
        }

        MGSeqParamSet(arg1->unk_04, 1, arg1->unk2);
        arg1->unk3 = 60;
    }

    var_r26 = GWPlayer[arg1->unk00_bit5].port;
    var_r28 = 0;

    if ((GWPlayer[arg1->unk00_bit5].com) != 0) {
        temp_r27 = BoardRandMod(100);

        switch (GWPlayer[arg1->unk00_bit5].diff) {
            case 0:
                if (temp_r27 < 12) {
                    var_r28 = 0x100;
                }
                break;
            case 1:
                if (temp_r27 < 22) {
                    var_r28 = 0x100;
                }
                break;
            case 2:
                if (temp_r27 < 50) {
                    var_r28 = 0x100;
                }
                break;
            case 3:
                var_r28 = 0x100;
                break;
        }
    }
    else {
        var_r28 = HuPadBtnDown[var_r26] & 0x100;
    }

    if ((var_r28 & 0x100)) {
        arg0->trans.y += 0.5f;
        if (arg0->trans.y > 2.0f) {
            arg0->trans.y = 2.0f;
        }
        if (lbl_1_data_450 == -1) {
            lbl_1_data_450 = HuAudFXPlay(0x43E);
        }
        lbl_1_bss_14E += 1;
        BoardModelVisibilitySet(arg1->unk_06[0], 1);
        BoardModelRotYSet(arg1->unk_06[0], BoardPlayerRotYGet(arg1->unk00_bit5));
    }
    else {
        arg0->trans.x *= 0.98f;
        arg0->trans.y = 0.0f;
        if (arg0->trans.x <= 1.0f) {
            BoardModelVisibilitySet(arg1->unk_06[0], 0);
            if (lbl_1_data_450 != -1) {
                HuAudFXStop(lbl_1_data_450);
                lbl_1_data_450 = -1;
            }
        }
    }

    if ((lbl_1_data_450 != -1) && (HuAudFXStatusGet(lbl_1_data_450) == 0)) {
        lbl_1_data_450 = -1;
    }

    arg0->trans.x += arg0->trans.y;

    if (arg0->trans.x > 3.0f) {
        arg0->trans.x = 3.0f;
    }

    BoardPlayerMotionSpeedSet(arg1->unk00_bit5, arg0->trans.x);
    BoardModelMotionSpeedSet(lbl_1_data_456, arg0->trans.x);
}

s8 lbl_1_data_4B0 = -1;
s32 lbl_1_data_4B4[] = { 0x00000440, 0x00000441, 0x00000442, 0x00000443, 0x00000444 };

void fn_1_8C08(omObjData *arg0, someBits3 *arg1)
{
    Vec spC;
    f32 temp_f31;
    f32 temp_f30;
    s8 temp_r27;

    BoardModelPosGet(lbl_1_data_456, &spC);
    spC.y += 1.6666666f;

    if (spC.y >= (arg0->trans.z + arg0->rot.y)) {
        spC.y = arg0->trans.z + arg0->rot.y;
        BoardModelMotionSpeedSet(lbl_1_bss_C[10], 0.0f);
        BoardPlayerMotionSpeedSet(arg1->unk00_bit5, 0.0f);
        BoardModelAttrSet(lbl_1_bss_C[7], 0x40000002);
        BoardModelAttrSet(lbl_1_data_456, 0x40000002);
        arg1->unk00_bit1 = 2;
        arg1->unk1 = 0x3C;
        arg1->unk2 = 0;
    }

    BoardModelPosSetV(lbl_1_data_456, &spC);
    temp_f30 = arg0->scale.x * ((spC.y - arg0->trans.z) / 500.0f);
    OSf32tos8(&temp_f30, &temp_r27);
    temp_r27 = temp_r27 / 30;

    if (lbl_1_data_4B0 != temp_r27) {
        lbl_1_data_4B0 = temp_r27;
        HuAudFXPlay(lbl_1_data_4B4[temp_r27]);
    }

    BoardModelMotionTimeSet(lbl_1_bss_C[7], temp_f30);
    BoardModelMotionTimeSet(lbl_1_bss_C[10], 0.2f * temp_f30);
    BoardPlayerMotionTimeSet(arg1->unk00_bit5, 2.0f * temp_f30);
}

void fn_1_8E44(omObjData *arg0, someBits3 *arg1)
{
    Vec sp8;
    f32 temp_f1;
    f32 temp_f31;

    if (arg1->unk00_bit7 == 0) {
        HuAudFXPlay(0x448);
        arg1->unk00_bit7 = 1;
        if (arg1->unk_0C != -1) {
            HuAudFXStop(arg1->unk_0C);
            arg1->unk_0C = -1;
        }
        BoardAudSeqFadeOut(1, 0x3E8);
    }

    OSu8tof32(&arg1->unk2, &temp_f31);
    BoardModelPosGet(lbl_1_data_456, &sp8);

    sp8.y = (sp8.y + (-0.08166666666666668 * temp_f31 * temp_f31));

    if (sp8.y < arg0->trans.z) {
        sp8.y = arg0->trans.z;
        arg1->unk00_bit1 = 3;
        arg0->trans.x = arg0->rot.y / 20.0f;
        arg0->trans.y = 0.0f;
        arg0->trans.z = 24.0f;
        BoardModelAttrReset(lbl_1_bss_C[10], 0x40000003);
        BoardModelMotionSpeedSet(lbl_1_bss_C[10], -2.0f);
        BoardPlayerModelAttrReset(arg1->unk00_bit5, 0x40000003);
        BoardPlayerMotionSpeedSet(arg1->unk00_bit5, -2.0f);
        HuAudFXPlay(0x449);
        BoardAudSeqPause(0, 0, 0x3E8);
    }

    arg1->unk2 += 1;
    BoardModelPosSetV(lbl_1_data_456, &sp8);
}

void fn_1_9044(omObjData *arg0, someBits3 *arg1)
{
    Vec sp8;

    BoardModelRotGet(lbl_1_data_456, &sp8);
    arg0->trans.y = BoardDAngleCalc(arg0->trans.y + arg0->trans.z);

    if (arg0->trans.y <= 2.0f) {
        if (arg0->trans.y >= -2.0) {
            arg0->trans.x *= 0.5f;
            if (arg0->trans.x <= 1.0f) {
                arg0->trans.y = 0.0f;
                BoardPlayerIdleSet(arg1->unk00_bit5);
                BoardModelMotionShiftSet(lbl_1_bss_C[10], 1, 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                arg1->unk00_bit0 = 1;
            }
        }
    }

    sp8.z = arg0->trans.x * sind(arg0->trans.y);
    BoardModelRotSetV(lbl_1_data_456, &sp8);
}

s8 lbl_1_data_4C8[] = { 1, 5, 10, 15, 20, 20 };

void fn_1_91B8(void)
{
    s8 temp_r3;

    if (lbl_1_bss_14E == 0) {
        lbl_1_bss_14E = 1;
    }

    temp_r3 = lbl_1_bss_14E / 6;
    lbl_1_bss_14C = lbl_1_data_4C8[temp_r3];
}

void fn_1_9230(s32 arg0)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s16 temp_r30;
    f32 rotY;

    temp_r30 = GWPlayer[arg0].space_curr;
    BoardPlayerPosGet(arg0, &sp20);
    BoardSpacePosGet(0, temp_r30, &sp14);
    BoardCameraTargetPlayerSet(arg0);
    BoardCameraViewSet(1);
    BoardPlayerPosLerpStart(arg0, &sp20, &sp14, 0x14);

    while (GWPlayer[arg0].moving != 0) {
        BoardModelPosGet(lbl_1_bss_C[10], &sp20);
        BoardPlayerPosGet(arg0, &sp14);
        VECSubtract(&sp14, &sp20, &sp8);
        rotY = atan2d(sp8.x, sp8.z);
        BoardModelRotYSet(lbl_1_bss_C[10], rotY);
        HuPrcVSleep();
    }

    BoardModelRotYSet(lbl_1_bss_C[10], 0.0f);
    BoardCameraMotionWait();
}

void fn_1_9384(void)
{
    f32 widthHeight[2];
    f32 x, y;

    HuWinMesMaxSizeGet(1, widthHeight, MAKE_MESSID(0x16, 0x19));
    x = -10000.0f;
    y = 288.0f;
    lbl_1_data_454 = HuWinCreate(x, y, widthHeight[0], widthHeight[1], 0);
    HuWinBGTPLvlSet(lbl_1_data_454, 0.0f);
    HuWinMesSpeedSet(lbl_1_data_454, 0);
    HuWinMesSet(lbl_1_data_454, MAKE_MESSID(0x16, 0x19));
}

void fn_1_9474(s32 arg0)
{
    sprintf(lbl_1_bss_150, "%d", lbl_1_bss_14C);
    BoardWinCreate(2, MAKE_MESSID(22, 23), 2);
    BOARD_WIN_MES_SET_PTR((uintptr_t)lbl_1_bss_150, 4);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerMotBlendSet(arg0, 0, 0xF);

    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }

    fn_1_97F8(arg0);

    while (lbl_1_bss_148) {
        HuPrcVSleep();
    }

    BoardPlayerMotionShiftSet(arg0, 7, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    HuPrcSleep(8);

    while (BoardPlayerMotionEndCheck(arg0) == 0) {
        HuPrcVSleep();
    }

    BoardWinCreate(2, MAKE_MESSID(22, 24), 2);
    BoardWinWait();
    BoardWinKill();
    BoardModelMotionStart(lbl_1_bss_C[7], 0, 0x40000002);
}

void fn_1_95B8(omObjData *arg0)
{
    f32 temp_f31;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    unkTemp *var_r30;
    unkTemp2 *temp_r29;
    s32 i;
    s32 temp;

    temp_r29 = OM_GET_WORK_PTR(arg0, unkTemp2);

    if ((temp_r29->unk00_bit0 != 0) || (BoardIsKill() != 0)) {
        fn_1_9A1C(temp_r29);
        HuMemDirectFree((void *)temp_r29->unk_0C);
        lbl_1_bss_148 = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }

    var_r30 = temp_r29->unk_0C;

    for (var_r27 = i = 0; i < 20; i++, var_r30++) {
        if (var_r30->unk0 == 0) {
            var_r27++;
        }
    }

    if (var_r27 == 20) {
        temp_r29->unk00_bit0 = 1;
        return;
    }

    var_r25 = 0;
    for (i = 0; i < 20; i++) {
        var_r30 = &temp_r29->unk_0C[i];
        if ((var_r30->unk0 == 1) && (var_r25 == 0)) {
            var_r30->unk0 = 2U;
            var_r25 = 1;
        }
        if (var_r30->unk0 == 2) {
            var_r30->unk1++;
            OSu8tof32(&var_r30->unk1, &temp_f31);
            var_r30->unk4 += 45.0f;
            var_r30->unk8.y += -0.08166667f * temp_f31 * temp_f31 * 0.75f;
            if (var_r30->unk8.y < temp_r29->unk8) {
                var_r30->unk8.y = temp_r29->unk8;
                CharModelCoinEffectCreate(1, &var_r30->unk8);
                BoardModelVisibilitySet(var_r30->unk_02, 0);
                HuAudFXPlay(7);
                BoardPlayerCoinsAdd(temp_r29->unk4, 1);
                omVibrate(temp_r29->unk4, 0xC, 6, 6);
                var_r30->unk0 = 0;
            }
            BoardModelPosSetV(var_r30->unk_02, &var_r30->unk8);
            BoardModelRotYSet(var_r30->unk_02, var_r30->unk4);
        }
    }
}

void fn_1_97F8(s32 arg0)
{
    Vec sp8;
    f32 temp_f2;
    f32 var_f31;
    f64 temp_f1;
    omObjData *temp_r3;
    s32 i;
    unkTemp2 *temp_r30;
    unkTemp *temp_r31;

    temp_r3 = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, fn_1_95B8);
    lbl_1_bss_148 = temp_r3;
    temp_r30 = OM_GET_WORK_PTR(temp_r3, unkTemp2);
    temp_r30->unk00_bit0 = 0;
    temp_r30->unk4 = arg0;
    temp_r30->unk_0C = HuMemDirectMallocNum(0, 20 * sizeof(unkTemp), MEMORY_DEFAULT_NUM);
    BoardPlayerPosGet(arg0, &sp8);
    temp_r30->unk8 = (80.0f + sp8.y);
    memset(temp_r30->unk_0C, 0, 0x190);

    for (i = 0; i < lbl_1_bss_14C; i++) {
        if (i == 0) {
            var_f31 = 0.0f;
        }
        else {
            var_f31 = BoardRandFloat();
        }
        temp_r31 = &temp_r30->unk_0C[i];
        temp_r31->unk0 = 1;
        temp_r31->unk8.x = sp8.x + (50.0f * sind(var_f31));
        temp_r31->unk8.z = sp8.z + (50.0f * cosd(var_f31));
        temp_r31->unk8.y = 600.0f + sp8.y + (500.0f * BoardRandFloat());
        temp_r31->unk1 = 0;
        temp_r31->unk4 = BoardRandFloat() * 360.0f;
        temp_r31->unk_02 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 0x0A), NULL, 1);
    }
}

void fn_1_9A1C(unkTemp2 *arg0)
{
    s32 i;
    unkTemp *temp;

    for (i = 0; i < 20; i++) {
        temp = &arg0->unk_0C[i];
        BoardModelKill(temp->unk_02);
    }
}
