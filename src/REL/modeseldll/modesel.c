#define HUWIN_USE_OLD_DEFS
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"


#include "REL/modeseldll.h"
#include "ext_math.h"


s16 lbl_1_data_80[] = { 16, 17, 18, 19, 20, 21 };

s32 lbl_1_data_8C[] = { DATA_MAKE_NUM(DATADIR_MODESEL, 0x30), DATA_MAKE_NUM(DATADIR_MODESEL, 0x32), DATA_MAKE_NUM(DATADIR_MODESEL, 0x34),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x36), DATA_MAKE_NUM(DATADIR_MODESEL, 0x38), DATA_MAKE_NUM(DATADIR_MODESEL, 0x3A) };

s32 lbl_1_data_A4[] = { DATA_MAKE_NUM(DATADIR_MODESEL, 0x31), DATA_MAKE_NUM(DATADIR_MODESEL, 0x33), DATA_MAKE_NUM(DATADIR_MODESEL, 0x35),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x37), DATA_MAKE_NUM(DATADIR_MODESEL, 0x39), DATA_MAKE_NUM(DATADIR_MODESEL, 0x3B) };

u32 lbl_1_data_BC[] = { MAKE_MESSID(17, 1), MAKE_MESSID(17, 2), MAKE_MESSID(17, 3), MAKE_MESSID(17, 4), MAKE_MESSID(17, 5), MAKE_MESSID(17, 6) };

s16 lbl_1_bss_82;
s16 lbl_1_bss_80;

void fn_1_3668(void);

// Scratch is at https://decomp.me/scratch/iirXp
// Register allocation issues at line 180 with load of 1.0 double constant
s32 fn_1_2490(void)
{
    float sp10[2];
    float sp8[2];
    float temp_f31;
    float temp_f30;
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s32 temp_r25;
    WindowData *temp_r24;
    AnimData *temp_r23;
    AnimData *temp_r22;
    s16 temp_r21;
    fn_1_3668();
    fn_1_1EC0(1);
    temp_r25 = HuAudFXPlay(2094);
    if (omovlevtno) {
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    }
    for (temp_r31 = 0; temp_r31 <= 20; temp_r31++) {
        temp_f31 = 1.0 - sind(90.0 * (temp_r31 / 20.0));
        Hu3DModelPosSet(lbl_1_bss_19A[14], 0, -50.0f + (200.0f * temp_f31), 0);
        Hu3DModelPosSet(lbl_1_bss_19A[15], 0, -50.0f + (200.0f * temp_f31), 0);
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    Hu3DModelAttrReset(lbl_1_bss_19A[14], 0x40000002);
    Hu3DModelAttrReset(lbl_1_bss_19A[15], 0x40000002);
    HuAudFXPlay(2093);
    HuPrcSleep(120);
    HuAudFXPlay(2095);
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        temp_f31 = temp_r31 / 30.0;
        Hu3DModelPosSet(lbl_1_bss_19A[14], 0, -50.0f - (20.0f * temp_f31), 0);
        HuPrcVSleep();
    }
    HuWinMesMaxSizeBetGet(sp10, MAKE_MESSID(0x11, 0x00), MAKE_MESSID(0x11, 0x06));
    lbl_1_bss_82 = HuWinExCreateStyled(-10000, 432 - sp10[1], sp10[0], sp10[1], -1, 0);
    HuWinMesSpeedSet(lbl_1_bss_82, 0);
    temp_r24 = &winData[lbl_1_bss_82];
    temp_r24->active_pad = 1;
    HuWinExAnimIn(lbl_1_bss_82);
    HuWinMesSet(lbl_1_bss_82, MAKE_MESSID(0x11, 0x00));
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x1A, 0x20));
    temp_r29 = HuWinCreate(-10000, 8 + (432 - sp10[1] - sp8[1]), sp8[0], sp8[1], 0);
    HuWinMesSpeedSet(temp_r29, 0);
    HuWinBGTPLvlSet(temp_r29, 0);
    HuWinMesSet(temp_r29, MAKE_MESSID(0x1A, 0x20));
    HuWinDispOff(temp_r29);
    while (!Hu3DMotionEndCheck(lbl_1_bss_19A[15])) {
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(lbl_1_bss_19A[15], 1);
    for (temp_r31 = 0; temp_r31 < 6; temp_r31++) {
        Hu3DModelAttrReset(lbl_1_bss_19A[lbl_1_data_80[temp_r31]], 1);
        Hu3DModelAttrSet(lbl_1_bss_19A[lbl_1_data_80[temp_r31]], 0x40000002);
        Hu3DMotionTimeSet(lbl_1_bss_19A[lbl_1_data_80[temp_r31]], 0);
        Hu3DModelPosSet(lbl_1_bss_19A[lbl_1_data_80[temp_r31]], 0, -50, 0);
    }
    HuWinMesWait(lbl_1_bss_82);

    lbl_1_bss_80 = temp_r26 = 0;
    espAttrReset(lbl_1_bss_152[10], HUSPR_ATTR_DISPOFF);
    espBankSet(lbl_1_bss_152[10], 0);
    for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
        temp_f31 = temp_r31 / 10.0f;
        Hu3DModelPosSet(lbl_1_bss_19A[lbl_1_data_80[lbl_1_bss_80]], 0, -50, 50.0 * sind(90.0f * temp_f31));
        espPosSet(lbl_1_bss_152[10], 288.0, -50.0 + (106.0 * sind(90.0f * temp_f31)));
        HuPrcVSleep();
    }
    HuWinMesSet(lbl_1_bss_82, lbl_1_data_BC[lbl_1_bss_80]);
    HuWinDispOn(temp_r29);
    while (1) {
        temp_r30 = 0;
        if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
            temp_r30 = -1;
        }
        else if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
            temp_r30 = 1;
        }
        if (temp_r30) {
            if (lbl_1_bss_80 + temp_r30 < 0) {
                lbl_1_bss_80 = 0;
            }
            else if (lbl_1_bss_80 + temp_r30 >= 6) {
                lbl_1_bss_80 = 5;
            }
            else {
                lbl_1_bss_80 += temp_r30;
            }
            if (temp_r26 != lbl_1_bss_80) {
                HuAudFXPlay(0);
                for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
                    temp_f31 = temp_r31 / 10.0f;
                    Hu3DModelPosSet(lbl_1_bss_19A[lbl_1_data_80[temp_r26]], 0, -50, 50.0 * cosd(90.0f * temp_f31));
                    Hu3DModelPosSet(lbl_1_bss_19A[lbl_1_data_80[lbl_1_bss_80]], 0, -50, 50.0 * sind(90.0f * temp_f31));
                    espPosSet(lbl_1_bss_152[10], 288.0, -50.0 + (106.0 * (1.0 - sind(180.0f * temp_f31))));
                    if (temp_r31 == 5) {
                        espBankSet(lbl_1_bss_152[10], lbl_1_bss_80);
                    }
                    HuPrcVSleep();
                }
                temp_r26 = lbl_1_bss_80;
                HuWinMesSet(lbl_1_bss_82, lbl_1_data_BC[lbl_1_bss_80]);
            }
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            HuAudFXPlay(2);
            break;
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            HuAudFXStop(temp_r25);
            return -1;
        }
        else {
            HuPrcVSleep();
            continue;
        }
    }
    Hu3DModelAttrReset(lbl_1_bss_19A[lbl_1_data_80[lbl_1_bss_80]], 0x40000002);
    HuAudSeqAllFadeOut(1000);
    for (temp_r31 = 0; temp_r31 <= 20; temp_r31++) {
        temp_f31 = temp_r31 / 20.0f;
        for (temp_r28 = 0; temp_r28 < 6; temp_r28++) {
            if (temp_r28 != lbl_1_bss_80) {
                Hu3DModelPosSet(lbl_1_bss_19A[lbl_1_data_80[temp_r28]], 0, -50 - (300.0 * (1.0 - cosd(90.0f * temp_f31))), 0);
                espPosSet(lbl_1_bss_152[10], 288.0, -50.0 + (106.0 * (cosd(90.0f * temp_f31))));
            }
        }
        HuPrcVSleep();
    }
    HuWinKill(temp_r29);
    HuWinExAnimOut(lbl_1_bss_82);
    HuAudFXStop(temp_r25);
    temp_r27 = HuSprGrpCreate(1);
    temp_r21 = HuTHPSprCreateVol("movie/opmov_c00.thp", 0, 3000, 90.0);
    HuSprGrpMemberSet(temp_r27, 0, temp_r21);
    HuSprPosSet(temp_r27, 0, 288.0f, 240.0f);
    HuSprDrawNoSet(temp_r27, 0, 127);
    HuPrcSleep(2);
    espAttrSet(lbl_1_bss_152[9], HUSPR_ATTR_DISPOFF);
    for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
        temp_f31 = temp_r31 / 10.0;
        Hu3DModelPosSet(lbl_1_bss_19A[14], 0, -70.0f - (100.0f * temp_f31), 0);
        HuPrcVSleep();
    }
    temp_r23 = HuSprAnimRead(HuDataReadNum(lbl_1_data_8C[lbl_1_bss_80], MEMORY_DEFAULT_NUM));
    temp_r22 = HuSprAnimRead(HuDataReadNum(lbl_1_data_A4[lbl_1_bss_80], MEMORY_DEFAULT_NUM));
    Hu3DAnimCreate(temp_r23, lbl_1_bss_19A[22], "ys002_a1");
    Hu3DAnimCreate(temp_r22, lbl_1_bss_19A[22], "ys002_a2");
    Hu3DModelAttrSet(lbl_1_bss_19A[lbl_1_data_80[lbl_1_bss_80]], 1);
    Hu3DMotionTimeSet(lbl_1_bss_19A[22], 0);
    Hu3DModelAttrReset(lbl_1_bss_19A[22], 1);
    Hu3DModelAttrSet(lbl_1_bss_19A[22], 0x40000002);
    Hu3DModelPosSet(lbl_1_bss_19A[22], 0, 27, 50);
    Hu3DModelScaleSet(lbl_1_bss_19A[22], 1.0f, 1.063f, 1.0f);
    for (temp_r31 = 1; temp_r31 <= 20; temp_r31++) {
        temp_f31 = temp_r31 / 20.0;
        Hu3DModelPosSet(lbl_1_bss_19A[22], 0, 27.0 - (60.0 * sind(90.0f * temp_f31)), 50);
        HuPrcVSleep();
    }
    HuPrcSleep(90);
    Hu3DFogSet(3000, 8000, 255, 255, 255);
    Hu3DModelAttrReset(lbl_1_bss_19A[22], 0x40000002);
    HuPrcSleep(60);
    temp_f31 = 0;
    temp_f30 = 5;
    while (!HuTHPEndCheck()) {
        Hu3DModelPosSet(lbl_1_bss_19A[22], 0, -33.0f + (temp_f31 / 30.0f), 50.0f - temp_f31);
        temp_f31 += temp_f30;
        temp_f30 += 5.0f;
        HuPrcVSleep();
    }
    _ClearFlag(FLAG_ID_MAKE(1, 11));
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuTHPClose();
    HuSprGrpKill(temp_r27);
    return lbl_1_bss_80;
}

void fn_1_3668(void)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Hu3DShadowCreate(20, 100, 5000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowSizeSet(192);
    sp14.x = sp14.y = sp14.z = 0;
    sp20.x = 0;
    sp20.z = 300;
    sp20.y = 400;
    sp8.x = 0;
    sp8.y = 1;
    sp8.z = 0;
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);
    Hu3DModelAttrReset(lbl_1_bss_19A[15], 1);
    Hu3DModelAttrSet(lbl_1_bss_19A[15], 0x40000002);
    Hu3DMotionTimeSet(lbl_1_bss_19A[15], 0);
    Hu3DModelAttrReset(lbl_1_bss_19A[14], 1);
    Hu3DModelAttrSet(lbl_1_bss_19A[14], 0x40000002);
    Hu3DMotionTimeSet(lbl_1_bss_19A[14], 0);
}
