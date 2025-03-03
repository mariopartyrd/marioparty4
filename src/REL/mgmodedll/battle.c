#include "REL/mgmodedll.h"
#include "game/gamework.h"

#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/minigame_seq.h"
#include "game/saveload.h"
#include "game/wipe.h"

#include "ext_math.h"

s16 lbl_1_bss_3A4;
s32 lbl_1_bss_3A0;
s16 lbl_1_bss_396[4];
s16 lbl_1_bss_394;
s16 lbl_1_bss_38C[4];
s16 lbl_1_bss_38A;
s16 lbl_1_bss_388;

s16 lbl_1_data_148 = -1;

void fn_1_FF5C(void);
s32 fn_1_1129C(void);
s32 fn_1_11E68(void);
void fn_1_1222C(void);
void fn_1_2783C(s16 evtno);

s32 fn_1_E72C(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s32 temp_r26;
    ModelData *temp_r25;
    float temp_f31;
    float temp_f30;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    temp_r29 = 0;
    fn_1_279FC(0);
    fn_1_FF5C();
    if (mgModeEvtNo == 3) {
        mgTypeCurr = mgInfoTbl[GWSystem.mg_next].type;
        if (mgTypeCurr >= 4) {
            mgTypeCurr = 3;
        }
        HuSprGrpPosSet(lbl_1_bss_388, 288, 240);
        HuSprGrpDrawNoSet(lbl_1_bss_388, 64);
        Hu3DModelPosSet(lbl_1_bss_2C80[5], -350, 0, 680);
        Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, 20, 0);
        fn_1_27418();
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            Hu3DModelPosSet(lbl_1_bss_2C14[temp_r31], (temp_r31 * 130) - 195, 0, 750);
            Hu3DMotionSet(lbl_1_bss_2C14[temp_r31], lbl_1_bss_2BC4[temp_r31][0]);
            Hu3DModelAttrSet(lbl_1_bss_2C14[temp_r31], HU3D_MOTATTR_LOOP);
        }
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            HuSprAttrSet(lbl_1_bss_388, (temp_r31 * 2) + 2, HUSPR_ATTR_DISPOFF);
            HuSprAttrSet(lbl_1_bss_388, (temp_r31 * 2) + 3, HUSPR_ATTR_DISPOFF);
        }
        HuSprAttrReset(lbl_1_bss_388, mgTypeCurr + 19, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(lbl_1_bss_388, mgTypeCurr + 19, 0, -155);
        HuSprPosSet(lbl_1_bss_388, 1, 0, -180);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
        if (fn_1_1129C() && !fn_1_11E68()) {
            return 1;
        }
    }
    else {
        CharModelDataClose(-1);
        if (HuDataReadChk(DATADIR_INSTPIC) == -1) {
            temp_r26 = HuDataDirReadAsync(DATADIR_INSTPIC);
        }
        else {
            temp_r26 = -1;
        }
        for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
            if (temp_r31 <= 50) {
                temp_f31 = temp_r31 / 50.0;
                HuSprGrpPosSet(lbl_1_bss_388, 288, -400.0 + (656.0 * sind(temp_f31 * 90.0f)));
            }
            else {
                temp_f31 = (temp_r31 - 50) / 10.0;
                HuSprGrpPosSet(lbl_1_bss_388, 288, 240.0 + (16.0 * cosd(temp_f31 * 90.0f)));
            }
            HuPrcVSleep();
        }
        for (temp_r31 = 0; temp_r31 <= 5; temp_r31++) {
            for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                if (temp_r30 != temp_r29) {
                    HuSprTPLvlSet(lbl_1_bss_388, (temp_r30 * 2) + 2, 1 - (temp_r31 / 5.0));
                }
            }
            HuPrcVSleep();
        }
        if (temp_r26 != -1) {
            while (!HuDataGetAsyncStat(temp_r26)) {
                HuPrcVSleep();
            }
        }
    repeat_mode:
        if (lbl_1_bss_20AA == 0) {
            HuPrcChildCreate(fn_1_27080, 100, 12288, 0, objman);
            lbl_1_bss_20AA = 1;
        }
        lbl_1_bss_3A4 = fn_1_25CA8(0x1A0020);
        if (lbl_1_data_148 == -1) {
            lbl_1_data_148 = fn_1_2530C(0, 0, 0);
        }
        HuWinMesSpeedSet(lbl_1_data_148, 1);
        fn_1_25838(lbl_1_data_148, 0x28000F, -1, -1);
        while (1) {
            temp_r28 = 0;
            if ((HuPadDStkRep[0] & PAD_BUTTON_UP) && temp_r29 > 0) {
                temp_r28 = -1;
            }
            else if ((HuPadDStkRep[0] & PAD_BUTTON_DOWN) && temp_r29 < 3) {
                temp_r28 = 1;
            }
            if (temp_r28 != 0) {
                HuSprAttrReset(lbl_1_bss_388, (temp_r29 * 2) + 3, HUSPR_ATTR_DISPOFF);
                for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
                    HuSprTPLvlSet(lbl_1_bss_388, (temp_r29 * 2) + 2, 1 - (temp_r31 / 10.0));
                    if (temp_r31 == 5) {
                        HuAudFXPlay(0);
                        HuSprTPLvlSet(lbl_1_bss_388, ((temp_r29 + temp_r28) * 2) + 2, 1);
                        HuSprAttrReset(lbl_1_bss_388, ((temp_r29 + temp_r28) * 2) + 2, HUSPR_ATTR_DISPOFF);
                    }
                    HuPrcVSleep();
                }
                temp_r29 += temp_r28;
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                fn_1_25E74(lbl_1_bss_3A4);
                fn_1_25584(lbl_1_data_148);
                lbl_1_data_148 = -1;
                for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
                    if (temp_r31 <= 10) {
                        temp_f31 = temp_r31 / 10.0;
                        HuSprGrpPosSet(lbl_1_bss_388, 288, 240.0 + (16.0 * sind(temp_f31 * 90.0f)));
                    }
                    else {
                        temp_f31 = (temp_r31 - 10) / 50.0;
                        HuSprGrpPosSet(lbl_1_bss_388, 288, -400.0 + (656.0 * cosd(temp_f31 * 90.0f)));
                    }
                    HuPrcVSleep();
                }
                HuSprGrpKill(lbl_1_bss_388);
                lbl_1_bss_388 = 0;
                return 0;
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                HuAudFXPlay(1);
                if (lbl_1_bss_20AC[lbl_1_data_A2[temp_r29]]) {
                    break;
                }
                fn_1_25838(lbl_1_data_148, 0x28002E, -1, -1);
                fn_1_25838(lbl_1_data_148, 0x28000F, -1, -1);
                continue;
            }
            HuPrcVSleep();
        }
        fn_1_25E74(lbl_1_bss_3A4);
        fn_1_25584(lbl_1_data_148);
        lbl_1_data_148 = lbl_1_bss_3A4 = -1;
        mgTypeCurr = temp_r29;
        if (temp_r29 == 1 || temp_r29 == 2) {
            if (fn_1_C0C8(1) == 0) {
                goto repeat_mode;
            }
        }
        else {
            for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                GWPlayerCfg[temp_r31].group = temp_r31;
            }
        }
        for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
            for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                HuSprTPLvlSet(lbl_1_bss_388, (temp_r30 * 2) + 3, 1 - (temp_r31 / 10.0));
            }
            HuPrcVSleep();
        }
        Hu3DMotionTimeSet(lbl_1_bss_2C80[5], 0);
        HuPrcVSleep();
        temp_r28 = (temp_r29 * 40) - 110;
        temp_r25 = &Hu3DData[lbl_1_bss_2C80[5]];
        sp20 = temp_r25->pos;
        sp14.x = -350;
        sp14.y = 0;
        sp14.z = 680;
        VECSubtract(&sp14, &sp20, &sp14);
        temp_f30 = (180 + atan2d(sp14.z, sp14.x)) - 360;
        Hu3DMotionShiftSet(lbl_1_bss_2C80[5], lbl_1_bss_2C66[7], 0, 8, HU3D_MOTATTR_LOOP);
        for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
            if (temp_r31 <= 20) {
                temp_f31 = temp_r31 / 20.0;
                HuSprPosSet(lbl_1_bss_388, (temp_r29 * 2) + 2, 0, (sind(temp_f31 * 90.0f) * (-150 - temp_r28)) + temp_r28);
            }
            temp_f31 = temp_r31 / 30.0;
            VECScale(&sp14, &sp8, temp_f31);
            VECAdd(&sp20, &sp8, &sp8);
            Hu3DModelPosSetV(lbl_1_bss_2C80[5], &sp8);
            if (temp_r31 <= 10) {
                temp_f31 = temp_r31 / 10.0;
                Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, temp_f30 * temp_f31, 0);
            }
            HuPrcVSleep();
        }
        HuSprGrpDrawNoSet(lbl_1_bss_388, 64);
        Hu3DMotionShiftSet(lbl_1_bss_2C80[5], lbl_1_bss_2C66[6], 0, 8, HU3D_MOTATTR_LOOP);
        for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
            temp_f31 = temp_r31 / 10.0;
            Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, temp_f30 + ((20 - temp_f30) * temp_f31), 0);
            HuPrcVSleep();
        }
        while (lbl_1_bss_20AA) {
            HuPrcVSleep();
        }
        Hu3DMotionTimeSet(lbl_1_bss_2C80[5], 0);
        HuPrcVSleep();
        fn_1_27418();
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            CharModelMotionSet(lbl_1_bss_2C24[temp_r31], lbl_1_bss_2BC4[temp_r31][2]);
            Hu3DModelAttrSet(lbl_1_bss_2C14[temp_r31], HU3D_MOTATTR_LOOP);
            Hu3DModelRotSet(lbl_1_bss_2C14[temp_r31], 0, -90, 0);
        }
        for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
            temp_f31 = temp_r31 / 30.0f;
            for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                Hu3DModelPosSet(lbl_1_bss_2C14[temp_r30],
                    (sind(temp_f31 * 90.0f) * (((temp_r30 * 130) - 195) - ((temp_r30 * 130) + 400))) + ((temp_r30 * 130) + 400), 0, 750);
                if ((temp_r31 + (temp_r30 * 2)) % 5 == 0) {
                    HuAudFXPlay(GWPlayerCfg[temp_r30].character + 213);
                }
            }
            HuPrcVSleep();
        }
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            Hu3DMotionShiftSet(lbl_1_bss_2C14[temp_r31], lbl_1_bss_2BC4[temp_r31][0], 0, 10, HU3D_MOTATTR_LOOP);
        }
        for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
            temp_f31 = temp_r31 / 10.0f;
            for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                Hu3DModelRotSet(lbl_1_bss_2C14[temp_r30], 0, -90.0 * (1.0 - temp_f31), 0);
            }
            HuPrcVSleep();
        }
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            mgBattleStar[temp_r31] = 0;
        }
    }
    if (lbl_1_data_148 == -1) {
        lbl_1_data_148 = fn_1_2530C(0, 0, 0);
    }
    fn_1_25838(lbl_1_data_148, 0x280010, -1, -1);
    HuSprTPLvlSet(lbl_1_bss_388, 10, 1);
    for (temp_r30 = 0; temp_r30 < 35;) {
        for (temp_r31 = 0; temp_r31 < lbl_1_bss_20AC[lbl_1_data_A2[mgTypeCurr]]; temp_r31++) {
            fn_1_271B4(lbl_1_bss_20C0[lbl_1_data_A2[mgTypeCurr]][temp_r31], 288, 210);
            HuAudFXPlay(855);
            HuPrcSleep(3);
            temp_r30++;
            if (temp_r30 >= 35) {
                break;
            }
        }
    }
    HuAudFXPlay(870);
    lbl_1_bss_2E4 = lbl_1_bss_20C0[lbl_1_data_A2[mgTypeCurr]][frandmod(lbl_1_bss_20AC[lbl_1_data_A2[mgTypeCurr]])];
    fn_1_271B4(lbl_1_bss_2E4, 288, 210);
    HuWinAttrSet(lbl_1_data_148, 0x10);
    HuWinInsertMesSet(lbl_1_data_148, mgInfoTbl[lbl_1_bss_2E4].name_mess, 0);
    fn_1_25838(lbl_1_data_148, 0x280011, -1, -1);
repeat_mess:
    fn_1_25838(lbl_1_data_148, 0x280029, -1, -1);
    temp_r27 = HuWinChoiceGet(lbl_1_data_148, 0);
    if (temp_r27 == 0) {
        _ClearFlag(11);
    }
    else if (temp_r27 == 1) {
        HuWinInsertMesSet(lbl_1_data_148, MAKE_MESSID(0x28, 39), 0);
        fn_1_25838(lbl_1_data_148, 0x280026, -1, -1);
        temp_r27 = HuWinChoiceGet(lbl_1_data_148, 1);
        if (temp_r27 == 1) {
            goto repeat_mess;
        }
        fn_1_271B4(-1, 0, 0);
        for (temp_r31 = 1; temp_r31 <= 10; temp_r31++) {
            HuSprTPLvlSet(lbl_1_bss_388, 10, 1 - (temp_r31 / 10.0));
            HuPrcVSleep();
        }
        fn_1_25584(lbl_1_data_148);
        lbl_1_data_148 = lbl_1_bss_3A4 = -1;
        fn_1_1222C();
        return 1;
    }
    else {
        _SetFlag(11);
    }
    GWSystem.mg_next = lbl_1_bss_2E4;
    HuDataDirClose(DATADIR_INSTPIC);
    fn_1_2783C(3);
    while (1) {
        HuPrcVSleep();
    }
}

s16 lbl_1_data_14A[4] = { 0, 2, 1, 3 };
GXColor lbl_1_data_152[4] = {
    { 255, 64, 64, 255 },
    { 128, 255, 128, 255 },
    { 128, 255, 255, 255 },
    { 255, 255, 128, 255 },
};

void fn_1_FF5C(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    AnimData *temp_r28;
    s16 temp_r27;
    AnimData *temp_r26;
    if (lbl_1_bss_388 == 0) {
        temp_r30 = HuSprGrpCreate(23);
        lbl_1_bss_388 = temp_r30;
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 125), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 200, 0);
        HuSprGrpMemberSet(temp_r30, 0, temp_r29);
        HuSprTPLvlSet(temp_r30, 0, 0.8f);
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 54), MEMORY_DEFAULT_NUM));
        if (mgBattleStarMax == 3) {
            temp_r27 = 0;
        }
        else if (mgBattleStarMax == 5) {
            temp_r27 = 1;
        }
        else {
            temp_r27 = 2;
        }
        temp_r29 = HuSprCreate(temp_r28, 190, temp_r27);
        HuSprGrpMemberSet(temp_r30, 1, temp_r29);
        HuSprPosSet(temp_r30, 1, 0, -180);
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 55) + (lbl_1_data_14A[temp_r31] * 3), MEMORY_DEFAULT_NUM));
            temp_r29 = HuSprCreate(temp_r28, 190, 0);
            HuSprGrpMemberSet(temp_r30, (2 * temp_r31) + 2, temp_r29);
            HuSprPosSet(temp_r30, (2 * temp_r31) + 2, 0, (temp_r31 * 40) - 110);
            temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 56) + (lbl_1_data_14A[temp_r31] * 3), MEMORY_DEFAULT_NUM));
            temp_r29 = HuSprCreate(temp_r28, 195, 0);
            HuSprGrpMemberSet(temp_r30, (2 * temp_r31) + 3, temp_r29);
            HuSprPosSet(temp_r30, (2 * temp_r31) + 3, 0, (temp_r31 * 40) - 110);
            temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 57) + (lbl_1_data_14A[temp_r31] * 3), MEMORY_DEFAULT_NUM));
            temp_r29 = HuSprCreate(temp_r28, 195, 0);
            HuSprGrpMemberSet(temp_r30, temp_r31 + 19, temp_r29);
        }
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 37), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 195, 0);
        HuSprGrpMemberSet(temp_r30, 10, temp_r29);
        HuSprPosSet(temp_r30, 10, 0, -32);
        HuSprScaleSet(temp_r30, 10, 0.9f, 0.9f);
        HuSprTPLvlSet(temp_r30, 10, 0);
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 101), MEMORY_DEFAULT_NUM));
        temp_r26 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 102), MEMORY_DEFAULT_NUM));
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            temp_r29 = HuSprCreate(temp_r28, 180, temp_r31);
            HuSprGrpMemberSet(temp_r30, (temp_r31 * 2) + 11, temp_r29);
            HuSprPosSet(temp_r30, (temp_r31 * 2) + 11, ((temp_r31 % 2) * 350) - 175, ((temp_r31 / 2) * 220) - 180);
            temp_r29 = HuSprCreate(temp_r26, 190, temp_r31);
            HuSprGrpMemberSet(temp_r30, (temp_r31 * 2) + 12, temp_r29);
            HuSprTPLvlSet(temp_r30, (temp_r31 * 2) + 12, 0.5f);
            HuSprPosSet(temp_r30, (temp_r31 * 2) + 12, ((temp_r31 % 2) * 350) - 175, ((temp_r31 / 2) * 220) - 172);
        }
    }
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        HuSprTPLvlSet(lbl_1_bss_388, (temp_r31 * 2) + 2, 1);
        HuSprAttrSet(lbl_1_bss_388, temp_r31 + 19, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpDrawNoSet(lbl_1_bss_388, 0);
}

void fn_1_10564(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    AnimData *temp_r24;
    s16 temp_r23;
    AnimData *temp_r22;
    s16 sp8[4];
    if (mgBattleStarMax == 3) {
        temp_r25 = 0;
    }
    else if (mgBattleStarMax == 5) {
        temp_r25 = 1;
    }
    else {
        temp_r25 = 2;
    }
    temp_r30 = HuSprGrpCreate(35);
    lbl_1_bss_38A = temp_r30;
    temp_r24 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 70) + temp_r25, MEMORY_DEFAULT_NUM));
    temp_r27 = HuSprCreate(temp_r24, 195, 0);
    HuSprGrpMemberSet(temp_r30, 33, temp_r27);
    HuSprAttrSet(temp_r30, 33, HUSPR_ATTR_DISPOFF);
    temp_r27 = HuSprCreate(temp_r24, 195, 0);
    HuSprGrpMemberSet(temp_r30, 34, temp_r27);
    HuSprAttrSet(temp_r30, 34, HUSPR_ATTR_DISPOFF);
    temp_r22 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 73), MEMORY_DEFAULT_NUM));
    temp_r28 = -(((mgBattleStarMax + 1) * 42) / 2) + 20;
    temp_r26 = -64;
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r24 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 74) + lbl_1_bss_2C24[temp_r31], MEMORY_DEFAULT_NUM));
        temp_r27 = HuSprCreate(temp_r24, 190, 0);
        HuSprGrpMemberSet(temp_r30, (temp_r31 * 8) + 0, temp_r27);
        HuSprPosSet(temp_r30, (temp_r31 * 8) + 0, temp_r28, temp_r26 + (temp_r31 * 42));
        for (temp_r29 = 0; temp_r29 < 7; temp_r29++) {
            temp_r27 = HuSprCreate(temp_r22, 190, 0);
            HuSprGrpMemberSet(temp_r30, 1 + (temp_r31 * 8) + temp_r29, temp_r27);
            HuSprPosSet(temp_r30, 1 + (temp_r31 * 8) + temp_r29, 42 + temp_r28 + (temp_r29 * 42), temp_r26 + (temp_r31 * 42));
            if (mgBattleStar[lbl_1_bss_2C1C[temp_r31]] <= temp_r29) {
                HuSprScaleSet(temp_r30, 1 + (temp_r31 * 8) + temp_r29, 0, 0);
            }
            else {
                HuSprScaleSet(temp_r30, 1 + (temp_r31 * 8) + temp_r29, 1, 1);
            }
            if (mgTypeCurr == 1) {
                if (temp_r31 > 2) {
                    HuSprAttrSet(temp_r30, 1 + (temp_r31 * 8) + temp_r29, HUSPR_ATTR_DISPOFF);
                }
                if (temp_r31 == 1) {
                    HuSprPosSet(temp_r30, 1 + (temp_r31 * 8) + temp_r29, 42 + temp_r28 + (temp_r29 * 42), temp_r26 + 84);
                }
            }
            else if (mgTypeCurr == 2) {
                if (temp_r31 % 2 == 1) {
                    HuSprAttrSet(temp_r30, 1 + (temp_r31 * 8) + temp_r29, HUSPR_ATTR_DISPOFF);
                }
                if (temp_r31 == 0) {
                    HuSprPosSet(temp_r30, 1 + (temp_r31 * 8) + temp_r29, 42 + temp_r28 + (temp_r29 * 42), temp_r26 + 21);
                }
                if (temp_r31 == 2) {
                    HuSprPosSet(temp_r30, 1 + (temp_r31 * 8) + temp_r29, 42 + temp_r28 + (temp_r29 * 42), temp_r26 + 105);
                }
            }
        }
    }
    temp_r28 = -(((mgBattleStarMax + 1) * 42) / 2) + 22;
    if (temp_r25 == 0) {
        temp_r28 += 63;
    }
    else if (temp_r25 == 1) {
        temp_r28 += 105;
    }
    else {
        temp_r28 += 146;
    }
    if (mgTypeCurr == 1) {
        HuSprPosSet(temp_r30, 33, temp_r28 + 21, temp_r26 + 63);
        HuSprAttrReset(temp_r30, 33, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(temp_r30, 34, temp_r28 + 21, temp_r26 + 105);
        HuSprAttrReset(temp_r30, 34, HUSPR_ATTR_DISPOFF);
    }
    else if (mgTypeCurr == 2) {
        HuSprPosSet(temp_r30, 33, temp_r28 + 21, temp_r26 + 21);
        HuSprAttrReset(temp_r30, 33, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(temp_r30, 34, temp_r28 + 21, temp_r26 + 105);
        HuSprAttrReset(temp_r30, 34, HUSPR_ATTR_DISPOFF);
    }
    temp_r24 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 67) + temp_r25, MEMORY_DEFAULT_NUM));
    temp_r27 = HuSprCreate(temp_r24, 200, 0);
    HuSprGrpMemberSet(temp_r30, 32, temp_r27);
    HuSprGrpPosSet(temp_r30, 288, 185);
    HuSprGrpDrawNoSet(temp_r30, 64);
    HuSprGrpScaleSet(temp_r30, 1, 0);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        lbl_1_bss_38C[temp_r31] = 0;
    }
    switch (mgTypeCurr) {
        case 0:
            temp_r23 = -1;
            for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                sp8[temp_r31] = GWPlayerCoinWinGet(temp_r31) + GWPlayerCoinCollectGet(temp_r31);
                if (temp_r23 < sp8[temp_r31]) {
                    temp_r23 = sp8[temp_r31];
                }
            }
            lbl_1_bss_394 = 0;
            if (temp_r23 != 0) {
                for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                    if (temp_r23 == sp8[temp_r31]) {
                        lbl_1_bss_396[lbl_1_bss_394] = temp_r31;
                        lbl_1_bss_38C[temp_r31] = 1;
                        lbl_1_bss_394++;
                    }
                }
            }
            break;

        case 1:
        case 2:
            sp8[0] = sp8[1] = 0;
            for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                sp8[GWPlayerCfg[temp_r31].group] += GWPlayerCoinWinGet(temp_r31) + GWPlayerCoinCollectGet(temp_r31);
            }
            if (mgInfoTbl[GWSystem.mg_next].ovl == OVL_M422) {
                sp8[1] /= 3;
            }
            lbl_1_bss_394 = 0;
            if (sp8[0] != 0 || sp8[1] != 0) {
                if (sp8[0] != sp8[1]) {
                    if (sp8[0] > sp8[1]) {
                        temp_r29 = 0;
                    }
                    else {
                        temp_r29 = 1;
                    }
                    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                        if (temp_r29 == GWPlayerCfg[lbl_1_bss_2C1C[temp_r31]].group) {
                            lbl_1_bss_396[lbl_1_bss_394] = temp_r31;
                            lbl_1_bss_38C[temp_r31] = 1;
                            lbl_1_bss_394++;
                        }
                    }
                }
                else {
                    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                        lbl_1_bss_396[lbl_1_bss_394] = temp_r31;
                        lbl_1_bss_38C[temp_r31] = 1;
                        lbl_1_bss_394++;
                    }
                }
            }
            break;

        case 3:
            for (temp_r31 = lbl_1_bss_394 = 0; temp_r31 < 4; temp_r31++) {
                if (!GWPlayerCoinWinGet(lbl_1_bss_2C1C[temp_r31])) {
                    lbl_1_bss_396[lbl_1_bss_394] = temp_r31;
                    lbl_1_bss_38C[temp_r31] = 1;
                    lbl_1_bss_394++;
                }
            }
            break;

        default:
            break;
    }
}

void fn_1_12B64(s16 arg0);

s32 fn_1_1129C(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    float temp_f31;

    s16 sp18[4];
    s16 sp10[4];
    s16 sp8[4];

    HuSprTPLvlSet(lbl_1_bss_388, 10, 0);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    fn_1_10564();
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        if (temp_r31 <= 20) {
            temp_f31 = temp_r31 / 20.0f;
            HuSprGrpScaleSet(lbl_1_bss_38A, 1, 1.1 * sind(temp_f31 * 90.0f));
        }
        else {
            temp_f31 = (temp_r31 - 20) / 10.0f;
            HuSprGrpScaleSet(lbl_1_bss_38A, 1, 1.0 + (0.1 * cosd(temp_f31 * 90.0f)));
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    if (lbl_1_data_148 == -1) {
        lbl_1_data_148 = fn_1_2530C(0, 0, 0);
    }
    if (lbl_1_bss_394) {
        for (temp_r31 = 0; temp_r31 < lbl_1_bss_394; temp_r31++) {
            HuWinInsertMesSet(lbl_1_data_148, lbl_1_bss_2C24[lbl_1_bss_396[temp_r31]], (s32)temp_r31);
        }
        if (lbl_1_bss_394 == 1) {
            fn_1_25838(lbl_1_data_148, 0x280012, -1, -1);
        }
        else if (lbl_1_bss_394 == 2) {
            fn_1_25838(lbl_1_data_148, 0x28001F, -1, -1);
        }
        else if (lbl_1_bss_394 == 3) {
            fn_1_25838(lbl_1_data_148, 0x280020, -1, -1);
        }
        else if (lbl_1_bss_394 == 4) {
            fn_1_25838(lbl_1_data_148, 0x280021, -1, -1);
        }
        HuAudFXPlay(825);
        HuAudFXPlay(826);
        for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
            temp_f31 = (1 - sind((temp_r31 / 30.0f) * 90.0f)) + 1;
            for (temp_r30 = 0; temp_r30 < lbl_1_bss_394; temp_r30++) {
                temp_r28 = lbl_1_bss_396[temp_r30];
                HuSprScaleSet(lbl_1_bss_38A, 1 + (temp_r28 * 8) + mgBattleStar[lbl_1_bss_2C1C[temp_r28]], temp_f31, temp_f31);
            }
            if (temp_r31 == 10) {
                for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                    if (lbl_1_bss_38C[temp_r30]) {
                        Hu3DMotionShiftSet(lbl_1_bss_2C14[temp_r30], lbl_1_bss_2BC4[temp_r30][3], 0, 5, HU3D_MOTATTR_NONE);
                    }
                    else {
                        Hu3DMotionShiftSet(lbl_1_bss_2C14[temp_r30], lbl_1_bss_2BC4[temp_r30][4], 0, 5, HU3D_MOTATTR_NONE);
                    }
                }
            }
            HuPrcVSleep();
        }
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            sp10[temp_r31] = 0;
        }
        for (temp_r30 = temp_r29 = 0; temp_r30 < lbl_1_bss_394; temp_r30++) {
            mgBattleStar[lbl_1_bss_2C1C[lbl_1_bss_396[temp_r30]]]++;
            if (mgBattleStar[lbl_1_bss_2C1C[lbl_1_bss_396[temp_r30]]] >= mgBattleStarMax) {
                sp18[temp_r29] = lbl_1_bss_396[temp_r30];
                sp10[lbl_1_bss_396[temp_r30]] = 1;
                temp_r29++;
            }
        }
        if (temp_r29 != 0) {
            for (temp_r31 = 0; temp_r31 < temp_r29; temp_r31++) {
                HuWinInsertMesSet(lbl_1_data_148, lbl_1_bss_2C24[sp18[temp_r31]], (s32)temp_r31);
            }
            if (temp_r29 == 1) {
                fn_1_25838(lbl_1_data_148, 0x280014, -1, -1);
            }
            else if (temp_r29 == 2) {
                fn_1_25838(lbl_1_data_148, 0x280022, -1, -1);
            }
            else if (temp_r29 == 3) {
                fn_1_25838(lbl_1_data_148, 0x280023, -1, -1);
            }
            else if (temp_r29 == 4) {
                fn_1_25838(lbl_1_data_148, 0x280024, -1, -1);
            }
            for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                if (temp_r31 < temp_r29) {
                    sp8[temp_r31] = lbl_1_bss_2C24[sp18[temp_r31]];
                }
                else {
                    sp8[temp_r31] = -1;
                }
            }
            MGSeqAltWinCreate(sp8[0], sp8[1], sp8[2], sp8[3]);
            HuAudFXPlay(2175);
            for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                if (sp10[temp_r30]) {
                    Hu3DMotionShiftSet(lbl_1_bss_2C14[temp_r30], lbl_1_bss_2BC4[temp_r30][5], 0, 5, HU3D_MOTATTR_NONE);
                    fn_1_12B64(temp_r30);
                }
                else {
                    Hu3DMotionShiftSet(lbl_1_bss_2C14[temp_r30], lbl_1_bss_2BC4[temp_r30][6], 0, 5, HU3D_MOTATTR_NONE);
                }
            }
            HuPrcSleep(120);
            return 1;
        }
        else {
            HuPrcSleep(30);
            for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                Hu3DMotionShiftSet(lbl_1_bss_2C14[temp_r30], lbl_1_bss_2BC4[temp_r30][0], 0, 5, HU3D_MOTATTR_LOOP);
            }
            HuPrcSleep(30);
        }
    }
    else {
        fn_1_25838(lbl_1_data_148, 0x280013, -1, -1);
    }
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        if (temp_r31 <= 10) {
            temp_f31 = temp_r31 / 10.0f;
            HuSprGrpScaleSet(lbl_1_bss_38A, 1, 1.0 + (0.1 * sind(temp_f31 * 90.0f)));
        }
        else {
            temp_f31 = (temp_r31 - 10) / 20.0f;
            HuSprGrpScaleSet(lbl_1_bss_38A, 1, 1.1 * cosd(temp_f31 * 90.0f));
        }
        HuPrcVSleep();
    }
    return 0;
}

s32 fn_1_11E68(void)
{
    s16 choice;
    fn_1_25838(lbl_1_data_148, 0x28000C, -1, -1);
    HuWinAttrSet(lbl_1_data_148, 0x10);
    choice = HuWinChoiceGet(lbl_1_data_148, 1);
    lbl_1_bss_3A0 = 0;
    fn_1_25584(lbl_1_data_148);
    lbl_1_data_148 = -1;
    if (choice == 0) {
        s16 i;
        s16 j;
        float weight;
        for (i = 0; i < 4; i++) {
            Hu3DMotionShiftSet(lbl_1_bss_2C14[i], lbl_1_bss_2BC4[i][0], 0, 10, HU3D_MOTATTR_LOOP);
        }
        for (i = 0; i <= 20; i++) {
            weight = i / 20.0f;
            HuSprGrpScaleSet(lbl_1_bss_38A, 1, cosd(weight * 90.0f));
            HuPrcVSleep();
        }
        for (i = 0; i < 4; i++) {
            mgBattleStar[i] = 0;
            for (j = 0; j < 7; j++) {
                HuSprScaleSet(lbl_1_bss_38A, j + (i * 8) + 1, 0, 0);
            }
        }
        for (i = 0; i <= 20; i++) {
            weight = i / 20.0f;
            HuSprGrpScaleSet(lbl_1_bss_38A, 1, sind(weight * 90.0f));
            HuPrcVSleep();
        }
        for (i = 0; i <= 20; i++) {
            weight = i / 20.0f;
            HuSprGrpScaleSet(lbl_1_bss_38A, 1, cosd(weight * 90.0f));
            HuPrcVSleep();
        }
        return 1;
    }
    else {
        fn_1_1222C();
        return 0;
    }
}

void fn_1_1222C(void)
{
    s16 i;
    s16 j;
    ModelData *model;
    float weight;
    float angle;

    Vec pos;
    Vec posEnd;
    Vec posModel;
    for (i = 0; i < 4; i++) {
        Hu3DMotionShiftSet(lbl_1_bss_2C14[i], lbl_1_bss_2BC4[i][2], 0, 10, HU3D_MOTATTR_LOOP);
    }
    model = &Hu3DData[lbl_1_bss_2C80[5]];
    pos = model->pos;
    posEnd.x = 0;
    posEnd.y = 0;
    posEnd.z = 640;
    VECSubtract(&posEnd, &pos, &posEnd);
    angle = atan2d(posEnd.z, posEnd.x) + 180;
    for (i = 0; i <= 30; i++) {
        for (j = 0; j < 4; j++) {
            if (i <= 10) {
                weight = i / 10.0;
                Hu3DModelRotSet(lbl_1_bss_2C14[j], 0, weight * 90.0f, 0);
            }
            weight = i / 30.0;
            Hu3DModelPosSet(lbl_1_bss_2C14[j], ((j * 130) - 195) + ((1 - cosd(weight * 90.0f)) * 700.0), 0, 750);
            if ((i + (j * 2)) % 5 == 0) {
                HuAudFXPlay(GWPlayerCfg[j].character + 213);
            }
        }
        if (i == 20) {
            Hu3DMotionShiftSet(lbl_1_bss_2C80[5], lbl_1_bss_2C66[7], 0, 8, HU3D_MOTATTR_LOOP);
        }
        if (i >= 20) {
            weight = (i - 20) / 10.0;
            Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, 20.0f + ((angle - 20.0f) * weight), 0);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        Hu3DMotionShiftSet(lbl_1_bss_2C14[i], lbl_1_bss_2BC4[i][0], 0, 10, HU3D_MOTATTR_LOOP);
    }
    for (i = 0; i <= 30; i++) {
        weight = i / 30.0;
        VECScale(&posEnd, &posModel, weight);
        VECAdd(&pos, &posModel, &posModel);
        Hu3DModelPosSetV(lbl_1_bss_2C80[5], &posModel);
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(lbl_1_bss_2C80[5], lbl_1_bss_2C66[6], 0, 10, HU3D_MOTATTR_LOOP);
    for (i = 0; i <= 10; i++) {
        weight = 1.0 - (i / 10.0);
        Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, angle * weight, 0);
        HuPrcVSleep();
    }
    for (i = 0; i <= 60; i++) {
        if (i <= 10) {
            weight = i / 10.0;
            HuSprGrpPosSet(lbl_1_bss_388, 288, 240.0 + (16.0 * sind(weight * 90.0f)));
            if (lbl_1_bss_38A) {
                HuSprGrpPosSet(lbl_1_bss_38A, 288, 185.0 + (16.0 * sind(weight * 90.0f)));
            }
        }
        else {
            weight = (i - 10) / 50.0;
            weight = (1 - cosd(weight * 90.0f)) * 400;
            HuSprGrpPosSet(lbl_1_bss_388, 288, 256 - weight);
            if (lbl_1_bss_38A) {
                HuSprGrpPosSet(lbl_1_bss_38A, 288, 201 - weight);
            }
        }

        HuPrcVSleep();
    }
    HuDataDirClose(DATADIR_INSTPIC);
    if (lbl_1_bss_388) {
        HuSprGrpKill(lbl_1_bss_388);
    }
    if (lbl_1_bss_38A) {
        HuSprGrpKill(lbl_1_bss_38A);
    }
    lbl_1_bss_388 = lbl_1_bss_38A = 0;
    for (i = 0; i < 4; i++) {
        CharModelKill(GWPlayerCfg[i].character);
    }
}

void fn_1_12BEC(void);

void fn_1_12B64(s16 arg0)
{
    Process *process;
    s32 *data;
    process = HuPrcChildCreate(fn_1_12BEC, 100, 12288, 0, objman);
    data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(s32), MEMORY_DEFAULT_NUM);
    process->user_data = data;
    *data = arg0;
    lbl_1_bss_3A0 = 1;
    (void)process;
}

void fn_1_12BEC(void)
{
    s16 temp_r31;
    ModelData *temp_r30;
    HsfMaterial *temp_r29;
    s32 *temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r23;
    s16 temp_r22;
    Process *temp_r21;
    float temp_f31;
    Vec sp44[30];
    s16 sp8[30];

    temp_r21 = HuPrcCurrentGet();
    temp_r28 = temp_r21->user_data;
    temp_r27 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MGMODE, 82));
    Hu3DModelLayerSet(temp_r27, 3);
    Hu3DModelPosSet(temp_r27, (*temp_r28 * 130) - 195, 300, 750);
    Hu3DModelScaleSet(temp_r27, 0.8f, 0.8f, 0.8f);
    for (temp_r31 = 0; temp_r31 < 30; temp_r31++) {
        if (temp_r31 < 4) {
            temp_r26 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MGMODE, 83));
            sp8[temp_r31] = temp_r26;
            temp_r30 = &Hu3DData[temp_r26];
            temp_r29 = temp_r30->hsfData->material;
            for (temp_r24 = 0; temp_r24 < temp_r30->hsfData->materialCnt; temp_r24++, temp_r29++) {
                temp_r29->color[0] = lbl_1_data_152[temp_r31].r;
                temp_r29->color[1] = lbl_1_data_152[temp_r31].g;
                temp_r29->color[2] = lbl_1_data_152[temp_r31].b;
                temp_r29->litColor[0] = lbl_1_data_152[temp_r31].r;
                temp_r29->litColor[1] = lbl_1_data_152[temp_r31].g;
                temp_r29->litColor[2] = lbl_1_data_152[temp_r31].b;
            }
        }
        else {
            temp_r26 = Hu3DModelLink(sp8[temp_r31 % 4]);
            sp8[temp_r31] = temp_r26;
        }
        Hu3DModelPosSet(temp_r26, (frandmod(50) - 220 + (*temp_r28 * 130)), (temp_r31 * 12) + 350, 750);
        Hu3DModelScaleSet(temp_r26, 2.0f, 2.0f, 2.0f);
        Hu3DModelAttrSet(temp_r26, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(temp_r26, 3);
        sp44[temp_r31].x = (float)(frandmod(50) - 25) * 0.05;
        sp44[temp_r31].z = (float)(frandmod(50) - 25) * 0.05;
    }
    HuPrcSleep(45);
    temp_r25 = 0;
    while (1) {
        for (temp_r31 = temp_r22 = 0; temp_r31 < 30; temp_r31++) {
            temp_r30 = &Hu3DData[sp8[temp_r31]];
            if (temp_r30->pos.y > 350.0f) {
                Hu3DModelAttrSet(sp8[temp_r31], HU3D_ATTR_DISPOFF);
            }
            else {
                Hu3DModelAttrReset(sp8[temp_r31], HU3D_ATTR_DISPOFF);
                temp_r30->pos.x += sp44[temp_r31].x;
                temp_r30->pos.z += sp44[temp_r31].z;
            }
            temp_r30->pos.y -= 3.0f;
            temp_r30->rot.x += ((temp_r31 % 3) + 1) * 5;
            temp_r30->rot.y += ((temp_r31 % 5) + 1) * 5;
            if (temp_r30->pos.y < 0.0f) {
                if (lbl_1_bss_3A0 == 0) {
                    Hu3DModelAttrSet(sp8[temp_r31], HU3D_ATTR_DISPOFF);
                    temp_r22++;
                }
                else {
                    temp_r30->pos.y = 350;
                    temp_r23 = frandmod(50) - 25;
                    temp_r30->pos.x = (-195 + (*temp_r28 * 130)) + temp_r23;
                    temp_r30->pos.z = 750;
                    sp44[temp_r31].x = ((float)frandmod(50) * 0.02) * ((temp_r23 < 0) ? -1 : (temp_r23 > 0) ? 1 : 0);
                    sp44[temp_r31].z = (float)(frandmod(50) - 25) * 0.05;
                }
            }
        }
        if (lbl_1_bss_3A0 || temp_r22 != 30) {
            if (lbl_1_bss_3A0 == 0 && temp_r25 <= 10) {
                temp_f31 = 1 - sind((temp_r25 / 10.0) * 90.0);
                if (0.0 == temp_f31) {
                    Hu3DModelAttrSet(temp_r27, HU3D_ATTR_DISPOFF);
                }
                Hu3DModelScaleSet(temp_r27, temp_f31, 1, 1);
                temp_r25++;
            }
            HuPrcVSleep();
        }
        else {
            break;
        }
    }
    (void)temp_r28;
    (void)temp_r28;
    (void)temp_r27;
    (void)temp_r27;
    Hu3DModelKill(temp_r27);
    HuPrcVSleep();
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}
