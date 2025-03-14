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

s16 lbl_1_bss_3B8;
s16 lbl_1_bss_3B4[2];
s16 lbl_1_bss_3B0[2];
s16 lbl_1_bss_3AC[2];
s16 lbl_1_bss_3AA;
s16 lbl_1_bss_3A8;

s16 lbl_1_data_168 = -1;
s16 lbl_1_data_16A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 3, 6, 1, 4, 7, 2, 5, 8, 0, 4, 8, 2, 4, 6 };

float lbl_1_data_19C[4] = { -80, -38, 38, 80 };

s16 lbl_1_data_1AC[8] = { 4, 4, 4, 4, 0, 2, 6, 8 };

void fn_1_2783C(s16 evtno);

void fn_1_14CFC(void);
s32 fn_1_15E98(s16 arg0, s32 arg1);

void fn_1_16438(void);
s32 fn_1_16B30(void);
void fn_1_17A5C(void);
void fn_1_17BE0(void);

s32 fn_1_13418(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    ModelData *temp_r27;
    Vec sp24;
    Vec sp18;
    Vec spC;
    s16 sp8[2];
    float temp_f31;
    float temp_f30;
    float temp_f29;

    fn_1_279FC(0);
    if (mgModeEvtNo != 4) {
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                mgTicTacToeGrid[temp_r31][temp_r30] = 0;
            }
        }
    }
    fn_1_14CFC();
    if (mgModeEvtNo == 4) {
        HuSprGrpPosSet(lbl_1_bss_3A8, 288, 240);
        HuSprGrpPosSet(lbl_1_bss_3AA, 450, 65);
        Hu3DModelPosSet(lbl_1_bss_2C80[5], -300, 0, 680);
        Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, 20, 0);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        if (fn_1_16B30()) {
            if (lbl_1_data_168 == -1) {
                lbl_1_data_168 = fn_1_2530C(0, 0, 0);
            }
            HuWinAttrSet(lbl_1_data_168, 16);
            fn_1_25838(lbl_1_data_168, 0x28000C, -1, -1);
            temp_r29 = HuWinChoiceGet(lbl_1_data_168, 1);
            if (temp_r29 == 0) {
                fn_1_17A5C();
            }
            else {
                fn_1_16438();
                return 0;
            }
        }
    }
    else {
        temp_r27 = &Hu3DData[lbl_1_bss_2C80[5]];
        sp24 = temp_r27->pos;
        sp18.x = -300;
        sp18.y = 0;
        sp18.z = 680;
        VECSubtract(&sp18, &sp24, &sp18);
        temp_f29 = (180 + atan2d(sp18.z, sp18.x)) - 360;
        for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
            if (temp_r31 <= 50) {
                temp_f31 = 1.0 - sind((temp_r31 / 50.0) * 90.0);
                HuSprGrpPosSet(lbl_1_bss_3A8, 288, 256 + (-400 * temp_f31));
            }
            else {
                temp_f31 = cosd(((temp_r31 - 50.0) / 10.0) * 90.0);
                HuSprGrpPosSet(lbl_1_bss_3A8, 288, 240 + (16 * temp_f31));
            }
            if (temp_r31 > 20 && temp_r31 <= 50) {
                temp_f31 = 1.0 - sind(((temp_r31 - 20) / 30.0) * 90.0);
                HuSprGrpPosSet(lbl_1_bss_3AA, 434 + (400 * temp_f31), 65);
            }
            else if (temp_r31 > 50) {
                temp_f31 = cosd(((temp_r31 - 50.0) / 10.0) * 90.0);
                HuSprGrpPosSet(lbl_1_bss_3AA, 450 + (-16 * temp_f31), 65);
            }
            if (temp_r31 == 30) {
                Hu3DMotionShiftSet(lbl_1_bss_2C80[5], lbl_1_bss_2C66[7], 0, 8, HU3D_MOTATTR_LOOP);
            }
            if (temp_r31 > 30) {
                temp_f31 = (temp_r31 - 30.0) / 30.0;
                VECScale(&sp18, &spC, temp_f31);
                VECAdd(&sp24, &spC, &spC);
                Hu3DModelPosSetV(lbl_1_bss_2C80[5], &spC);
                if (temp_r31 <= 40) {
                    temp_f31 = (temp_r31 - 20) / 10.0;
                    Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, temp_f29 * temp_f31, 0);
                }
            }
            HuPrcVSleep();
        }
        Hu3DMotionShiftSet(lbl_1_bss_2C80[5], lbl_1_bss_2C66[6], 0, 8, HU3D_MOTATTR_LOOP);
        for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
            temp_f31 = temp_r31 / 10.0;
            Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, temp_f29 + ((20.0f - temp_f29) * temp_f31), 0);
            HuPrcVSleep();
        }
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                mgTicTacToeGrid[temp_r31][temp_r30] = 0;
            }
        }
    }
    lbl_1_bss_3B8 = fn_1_25CA8(0x280019);
    if (lbl_1_data_168 == -1) {
        lbl_1_data_168 = fn_1_2530C(0, 0, 0);
    }
    fn_1_25838(lbl_1_data_168, 0x280015, -1, -1);
    lbl_1_bss_3B4[0] = 0;
    lbl_1_bss_3B4[1] = 2;
    fn_1_17BE0();
    lbl_1_bss_3AC[0] = lbl_1_bss_3AC[1] = 30;
    HuSprAttrReset(lbl_1_bss_3A8, 12, HUSPR_ATTR_DISPOFF);
    HuSprTPLvlSet(lbl_1_bss_3A8, 12, 0.5f);
    HuSprAttrReset(lbl_1_bss_3A8, 13, HUSPR_ATTR_DISPOFF);
    HuSprTPLvlSet(lbl_1_bss_3A8, 13, 0.5f);
    temp_f30 = 0;
    sp8[0] = sp8[1] = 0;
    for (temp_r31 = 0; temp_r31 < 9; temp_r31++) {
        mgTicTacToeGrid[temp_r31 % 3][temp_r31 / 3] &= 0x3;
    }
    while (1) {
        for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
            if (sp8[temp_r31] == 0) {
                sp8[temp_r31] = fn_1_15E98(temp_r31, 1);
                if (sp8[temp_r31] == -1) {
                    sp8[temp_r31] = 0;
                    goto else_case;
                }
                else if (sp8[temp_r31] == 1) {
                    HuSprAttrSet(lbl_1_bss_3A8, temp_r31 + 12, HUSPR_ATTR_DISPOFF);
                    HuSprAttrReset(lbl_1_bss_3A8, temp_r31 + 14, HUSPR_ATTR_DISPOFF);
                    if (lbl_1_bss_3B4[0] != lbl_1_bss_3B4[1]) {
                        HuSprPosSet(
                            lbl_1_bss_3A8, temp_r31 + 14, ((lbl_1_bss_3B4[temp_r31] % 3) * 56) - 56, ((lbl_1_bss_3B4[temp_r31] / 3) * 56) - 56);
                    }
                    else {
                        HuSprPosSet(lbl_1_bss_3A8, temp_r31 + 14, ((lbl_1_bss_3B4[temp_r31] % 3) * 56) - 60 + (temp_r31 * 8),
                            ((lbl_1_bss_3B4[temp_r31] / 3) * 56) - 56);
                    }
                }
                else {
                else_case:
                    if (lbl_1_bss_3B4[0] != lbl_1_bss_3B4[1]) {
                        HuSprPosSet(
                            lbl_1_bss_3A8, temp_r31 + 12, ((lbl_1_bss_3B4[temp_r31] % 3) * 56) - 56, ((lbl_1_bss_3B4[temp_r31] / 3) * 56) - 56);
                    }
                    else {
                        HuSprPosSet(lbl_1_bss_3A8, temp_r31 + 12, ((lbl_1_bss_3B4[temp_r31] % 3) * 56) - 60 + (temp_r31 * 8),
                            ((lbl_1_bss_3B4[temp_r31] / 3) * 56) - 56);
                    }
                    HuSprTPLvlSet(lbl_1_bss_3A8, temp_r31 + 12, 0.7 + (0.2 * sind(temp_f30 + (temp_r31 * 180))));
                    HuSprPriSet(lbl_1_bss_3A8, temp_r31 + 12, 150);
                }
            }
            else {
                sp8[temp_r31] = fn_1_15E98(temp_r31, 0);
                if (sp8[temp_r31] == -1) {
                    sp8[temp_r31] = 0;
                    HuSprAttrReset(lbl_1_bss_3A8, temp_r31 + 12, HUSPR_ATTR_DISPOFF);
                    HuSprAttrSet(lbl_1_bss_3A8, temp_r31 + 14, HUSPR_ATTR_DISPOFF);
                    if (lbl_1_bss_3B4[0] != lbl_1_bss_3B4[1]) {
                        HuSprPosSet(
                            lbl_1_bss_3A8, temp_r31 + 12, ((lbl_1_bss_3B4[temp_r31] % 3) * 56) - 56, ((lbl_1_bss_3B4[temp_r31] / 3) * 56) - 56);
                    }
                    else {
                        HuSprPosSet(lbl_1_bss_3A8, temp_r31 + 12, ((lbl_1_bss_3B4[temp_r31] % 3) * 56) - 60 + (temp_r31 * 8),
                            ((lbl_1_bss_3B4[temp_r31] / 3) * 56) - 56);
                    }
                }
                else {
                    HuSprTPLvlSet(lbl_1_bss_3A8, temp_r31 + 12, 1.0f);
                    HuSprPriSet(lbl_1_bss_3A8, temp_r31 + 12, temp_r31 + 180);
                    if (lbl_1_bss_3B4[0] != lbl_1_bss_3B4[1]) {
                        HuSprPosSet(
                            lbl_1_bss_3A8, temp_r31 + 14, ((lbl_1_bss_3B4[temp_r31] % 3) * 56) - 56, ((lbl_1_bss_3B4[temp_r31] / 3) * 56) - 56);
                    }
                    else {
                        HuSprPosSet(lbl_1_bss_3A8, temp_r31 + 14, ((lbl_1_bss_3B4[temp_r31] % 3) * 56) - 60 + (temp_r31 * 8),
                            ((lbl_1_bss_3B4[temp_r31] / 3) * 56) - 56);
                    }
                }
            }
        }
        if (sp8[0] == 1 && sp8[1] == 1) {
            HuSprTPLvlSet(lbl_1_bss_3A8, 12, 1.0f);
            HuSprTPLvlSet(lbl_1_bss_3A8, 13, 1.0f);
            break;
        }
        else {
            temp_f30 += 10.0f;
            if (temp_f30 > 360.0f) {
                temp_f30 -= 360.0f;
            }
            HuPrcVSleep();
        }
    }
    fn_1_25E74(lbl_1_bss_3B8);
    lbl_1_bss_3B8 = -1;
    fn_1_25838(lbl_1_data_168, 0x280010, -1, -1);
    HuSprTPLvlSet(lbl_1_bss_3A8, 24, 1.0f);
    mgTypeCurr = 2;
    for (temp_r30 = 0; temp_r30 < 35;) {
        for (temp_r31 = 0; temp_r31 < lbl_1_bss_20AC[lbl_1_data_A2[mgTypeCurr]]; temp_r31++) {
            temp_r28 = fn_1_271B4(lbl_1_bss_20C0[lbl_1_data_A2[mgTypeCurr]][temp_r31], 288, 240);
            HuSprGrpDrawNoSet(temp_r28, 0);
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
    temp_r28 = fn_1_271B4(lbl_1_bss_2E4, 288, 240);
    HuSprGrpDrawNoSet(temp_r28, 0);
    HuWinInsertMesSet(lbl_1_data_168, mgInfoTbl[lbl_1_bss_2E4].name_mess, 0);
    HuWinAttrSet(lbl_1_data_168, 16);
    fn_1_25838(lbl_1_data_168, 0x280011, -1, -1);
repeat_mess:
    fn_1_25838(lbl_1_data_168, 0x280029, -1, -1);
    temp_r29 = HuWinChoiceGet(lbl_1_data_168, 0);
    if (temp_r29 == 0) {
        _ClearFlag(11);
    }
    else if (temp_r29 == 1) {
        HuWinInsertMesSet(lbl_1_data_168, MAKE_MESSID(0x28, 40), 0);
        fn_1_25838(lbl_1_data_168, 0x280026, -1, -1);
        temp_r29 = HuWinChoiceGet(lbl_1_data_168, 1);
        if (temp_r29 == 1) {
            goto repeat_mess;
        }
        fn_1_271B4(-1, 0, 0);
        for (temp_r31 = 1; temp_r31 <= 10; temp_r31++) {
            HuSprTPLvlSet(lbl_1_bss_3A8, 24, 1 - (temp_r31 / 10.0));
            HuPrcVSleep();
        }

        fn_1_16438();
        return 1;
    }
    else {
        _SetFlag(11);
    }
    GWSystem.mg_next = lbl_1_bss_2E4;
    HuDataDirClose(DATADIR_INSTPIC);
    fn_1_2783C(4);
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_14CFC(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    AnimData *temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    AnimData *temp_r23;
    AnimData *temp_r22;
    s16 temp_r21;
    s16 temp_r20;
    s16 sp8;
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        lbl_1_bss_2C1C[temp_r31] = temp_r31;
    }
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        for (temp_r27 = 0; temp_r27 < 3 - temp_r31; temp_r27++) {
            if (GWPlayerCfg[lbl_1_bss_2C1C[temp_r27]].group > GWPlayerCfg[lbl_1_bss_2C1C[temp_r27 + 1]].group) {
                temp_r24 = lbl_1_bss_2C1C[temp_r27];
                lbl_1_bss_2C1C[temp_r27] = lbl_1_bss_2C1C[temp_r27 + 1];
                lbl_1_bss_2C1C[temp_r27 + 1] = temp_r24;
            }
        }
    }
    if (lbl_1_bss_3A8 == 0) {

        lbl_1_bss_3A8 = temp_r30 = HuSprGrpCreate(25);
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 84), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 200, 0);
        HuSprGrpMemberSet(temp_r30, 0, temp_r29);
        HuSprTPLvlSet(temp_r30, 0, 0.8f);
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 85), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 190, 0);
        HuSprGrpMemberSet(temp_r30, 1, temp_r29);
        HuSprPosSet(temp_r30, 1, 0, -110);
        temp_r26 = 0;
        temp_r25 = 0;
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 86), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 190, 0);
        HuSprGrpMemberSet(temp_r30, 2, temp_r29);
        HuSprPosSet(temp_r30, 2, temp_r26, temp_r25);
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 87), MEMORY_DEFAULT_NUM));
        temp_r22 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 88), MEMORY_DEFAULT_NUM));
        for (temp_r31 = temp_r27 = 0; temp_r31 < 9; temp_r31++) {
            if (mgTicTacToeGrid[temp_r31 % 3][temp_r31 / 3] & 0xF) {
                temp_r24 = mgTicTacToeGrid[temp_r31 % 3][temp_r31 / 3];
                if (temp_r24 & 0x4) {
                    temp_r23 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 91), MEMORY_DEFAULT_NUM));
                    temp_r29 = HuSprCreate(temp_r23, 180, 0);
                    HuSprGrpMemberSet(temp_r30, 14, temp_r29);
                    if (temp_r24 & 0x8) {
                        HuSprPosSet(temp_r30, 14, temp_r26 + ((temp_r31 % 3) * 56) - 60, temp_r25 + ((temp_r31 / 3) * 56) - 56);
                    }
                    else {
                        HuSprPosSet(temp_r30, 14, temp_r26 + ((temp_r31 % 3) * 56) - 56, temp_r25 + ((temp_r31 / 3) * 56) - 56);
                    }
                    temp_r27++;
                }
                if (temp_r24 & 0x8) {
                    temp_r23 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 92), MEMORY_DEFAULT_NUM));
                    temp_r29 = HuSprCreate(temp_r23, 180, 0);
                    HuSprGrpMemberSet(temp_r30, 15, temp_r29);
                    if (temp_r24 & 0x4) {
                        HuSprPosSet(temp_r30, 15, temp_r26 + ((temp_r31 % 3) * 56) - 48, temp_r25 + ((temp_r31 / 3) * 56) - 56);
                    }
                    else {
                        HuSprPosSet(temp_r30, 15, temp_r26 + ((temp_r31 % 3) * 56) - 56, temp_r25 + ((temp_r31 / 3) * 56) - 56);
                    }
                    temp_r27++;
                }
                if (temp_r24 & 0x3) {
                    if (mgTicTacToeGrid[temp_r31 % 3][temp_r31 / 3] & 0x1) {
                        temp_r29 = HuSprCreate(temp_r28, 180, 0);
                    }
                    else {
                        temp_r29 = HuSprCreate(temp_r22, 180, 0);
                    }
                    HuSprGrpMemberSet(temp_r30, temp_r31 + 3, temp_r29);
                    HuSprPosSet(temp_r30, temp_r31 + 3, temp_r26 + ((temp_r31 % 3) * 56) - 56, temp_r25 + ((temp_r31 / 3) * 56) - 56);
                }
            }
        }
        if (temp_r27 == 0) {
            temp_r23 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 91), MEMORY_DEFAULT_NUM));
            temp_r29 = HuSprCreate(temp_r23, 150, 0);
            HuSprGrpMemberSet(temp_r30, 14, temp_r29);
            HuSprPosSet(temp_r30, 14, temp_r26 + ((temp_r31 % 3) * 56) - 56, temp_r25 + ((temp_r31 / 3) * 56) - 56);
            HuSprAttrSet(temp_r30, 14, HUSPR_ATTR_DISPOFF);
            temp_r23 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 92), MEMORY_DEFAULT_NUM));
            temp_r29 = HuSprCreate(temp_r23, 150, 0);
            HuSprGrpMemberSet(temp_r30, 15, temp_r29);
            HuSprPosSet(temp_r30, 15, temp_r26 + ((temp_r31 % 3) * 56) - 56, temp_r25 + ((temp_r31 / 3) * 56) - 56);
            HuSprAttrSet(temp_r30, 15, HUSPR_ATTR_DISPOFF);
        }
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 89), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 150, 0);
        HuSprGrpMemberSet(temp_r30, 12, temp_r29);
        HuSprAttrSet(temp_r30, 12, HUSPR_ATTR_DISPOFF);
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 90), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 150, 0);
        HuSprGrpMemberSet(temp_r30, 13, temp_r29);
        HuSprAttrSet(temp_r30, 13, HUSPR_ATTR_DISPOFF);
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 101), MEMORY_DEFAULT_NUM));
        temp_r22 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 102), MEMORY_DEFAULT_NUM));
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            temp_r29 = HuSprCreate(temp_r28, 130, temp_r31);
            HuSprGrpMemberSet(temp_r30, (temp_r31 * 2) + 16, temp_r29);
            HuSprPosSet(temp_r30, (temp_r31 * 2) + 16, ((temp_r31 % 2) * 314) - 155, ((temp_r31 / 2) * 185) - 110);
            temp_r29 = HuSprCreate(temp_r22, 135, temp_r31);
            HuSprGrpMemberSet(temp_r30, (temp_r31 * 2) + 17, temp_r29);
            HuSprTPLvlSet(temp_r30, (temp_r31 * 2) + 17, 0.5f);
            HuSprPosSet(temp_r30, (temp_r31 * 2) + 17, ((temp_r31 % 2) * 314) - 155, ((temp_r31 / 2) * 185) - 102);
        }
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 37), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 150, 0);
        HuSprGrpMemberSet(temp_r30, 24, temp_r29);
        HuSprPosSet(temp_r30, 24, 0, 0);
        HuSprScaleSet(temp_r30, 24, 0.9f, 0.9f);
        HuSprTPLvlSet(temp_r30, 24, 0);
    }
    if (lbl_1_bss_3AA == 0) {

        lbl_1_bss_3AA = temp_r30 = HuSprGrpCreate(10);
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 15), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 200, 0);
        HuSprGrpMemberSet(temp_r30, 0, temp_r29);
        HuSprTPLvlSet(temp_r30, 0, 0.8f);
        temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 25), MEMORY_DEFAULT_NUM));
        temp_r29 = HuSprCreate(temp_r28, 190, 0);
        HuSprGrpMemberSet(temp_r30, 1, temp_r29);
        HuSprPosSet(temp_r30, 1, 0, 0);
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            temp_r20 = lbl_1_bss_2C24[temp_r31] = GWPlayerCfg[lbl_1_bss_2C1C[temp_r31]].character;
            temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 16) + temp_r20, MEMORY_DEFAULT_NUM));
            temp_r29 = HuSprCreate(temp_r28, 190, 0);
            HuSprGrpMemberSet(temp_r30, (temp_r31 * 2) + 2, temp_r29);
            HuSprPosSet(temp_r30, (temp_r31 * 2) + 2, lbl_1_data_19C[temp_r31], 0);
            if (sp8 = GWPlayerCfg[lbl_1_bss_2C1C[temp_r31]].iscom) {
                temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 39), MEMORY_DEFAULT_NUM));
                temp_r21 = GWPlayerCfg[lbl_1_bss_2C1C[temp_r31]].diff;
            }
            else {
                temp_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 38), MEMORY_DEFAULT_NUM));
                temp_r21 = GWPlayerCfg[lbl_1_bss_2C1C[temp_r31]].pad_idx;
            }
            temp_r29 = HuSprCreate(temp_r28, 180, temp_r21);
            HuSprGrpMemberSet(temp_r30, (temp_r31 * 2) + 3, temp_r29);
            HuSprPosSet(temp_r30, (temp_r31 * 2) + 3, lbl_1_data_19C[temp_r31], 24);
        }
        HuSprGrpPosSet(temp_r30, 800, 240);
    }
}

s32 fn_1_15E98(s16 arg0, s32 arg1)
{
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r23;
    temp_r28 = 4;
    for (temp_r27 = 0; temp_r27 < 4; temp_r27++) {
        if (arg0 == GWPlayerCfg[temp_r27].group && GWPlayerCfg[temp_r27].iscom == 0 && temp_r28 > GWPlayerCfg[temp_r27].pad_idx) {
            temp_r28 = GWPlayerCfg[temp_r27].pad_idx;
        }
    }
    if (temp_r28 == 4) {
        if (arg1 == 0) {
            return 1;
        }
        temp_r30 = lbl_1_bss_3B4[arg0] % 3;
        temp_r29 = lbl_1_bss_3B4[arg0] / 3;
        temp_r24 = lbl_1_bss_3B0[arg0] % 3;
        temp_r23 = lbl_1_bss_3B0[arg0] / 3;
        if (--lbl_1_bss_3AC[arg0] != 0) {
            return 0;
        }
        if (temp_r30 == temp_r24 && temp_r29 == temp_r23) {
            HuAudFXPlay(1);
            mgTicTacToeGrid[temp_r24][temp_r23] |= 4 << arg0;
            return 1;
        }
        else {
            lbl_1_bss_3AC[arg0] = 30;
            temp_r26 = (temp_r24 - temp_r30 < 0) ? -1 : (temp_r24 - temp_r30 > 0) ? 1 : 0;
            temp_r25 = (temp_r23 - temp_r29 < 0) ? -1 : (temp_r23 - temp_r29 > 0) ? 1 : 0;
            lbl_1_bss_3B4[arg0] = temp_r30 + temp_r26 + ((temp_r29 + temp_r25) * 3);
            HuAudFXPlay(0);
            return 0;
        }
    }
    else {
        temp_r30 = lbl_1_bss_3B4[arg0] % 3;
        temp_r29 = lbl_1_bss_3B4[arg0] / 3;
        if (arg1 == 0) {
            return 1;
        }
        if (HuPadBtnDown[temp_r28] & PAD_BUTTON_A) {
            if ((mgTicTacToeGrid[temp_r30][temp_r29] & 0x3) == 0) {
                mgTicTacToeGrid[temp_r30][temp_r29] |= 4 << arg0;
                HuAudFXPlay(1);
                return 1;
            }
            else {
                HuAudFXPlay(4);
            }
        }
        if (HuPadDStkRep[temp_r28] == 0) {
            return 0;
        }
        temp_r26 = temp_r25 = 0;
        if ((HuPadDStkRep[temp_r28] & PAD_BUTTON_LEFT) && temp_r30 > 0) {
            temp_r26 = -1;
        }
        else if ((HuPadDStkRep[temp_r28] & PAD_BUTTON_RIGHT) && temp_r30 < 2) {
            temp_r26 = 1;
        }
        if ((HuPadDStkRep[temp_r28] & PAD_BUTTON_UP) && temp_r29 > 0) {
            temp_r25 = -1;
        }
        else if ((HuPadDStkRep[temp_r28] & PAD_BUTTON_DOWN) && temp_r29 < 2) {
            temp_r25 = 1;
        }
        if (temp_r26 || temp_r25) {
            HuAudFXPlay(0);
        }
        lbl_1_bss_3B4[arg0] = temp_r30 + temp_r26 + ((temp_r29 + temp_r25) * 3);
        return 0;
    }
}

void fn_1_16438(void)
{
    s16 temp_r31;
    ModelData *temp_r30;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    float temp_f30;

    fn_1_25E74(lbl_1_bss_3B8);
    fn_1_25584(lbl_1_data_168);
    lbl_1_data_168 = lbl_1_bss_3B8 = -1;
    temp_r30 = &Hu3DData[lbl_1_bss_2C80[5]];
    sp20 = temp_r30->pos;
    sp14.x = 0;
    sp14.y = 0;
    sp14.z = 640;
    VECSubtract(&sp14, &sp20, &sp14);
    temp_f30 = 180 + atan2d(sp14.z, sp14.x);
    for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
        if (temp_r31 <= 10) {
            temp_f31 = sind((temp_r31 / 10.0) * 90.0);
            HuSprGrpPosSet(lbl_1_bss_3A8, 288, 240 + (16 * temp_f31));
        }
        else {
            temp_f31 = 1.0 - cosd(((temp_r31 - 10.0) / 50.0) * 90.0);
            HuSprGrpPosSet(lbl_1_bss_3A8, 288, 256 + (-400 * temp_f31));
        }
        if (temp_r31 <= 10) {
            temp_f31 = sind((temp_r31 / 10.0) * 90.0);
            HuSprGrpPosSet(lbl_1_bss_3AA, 450 + (-16 * temp_f31), 65);
        }
        else if (temp_r31 < 30) {
            temp_f31 = 1 - cosd(((temp_r31 - 10.0) / 20.0) * 90.0);
            HuSprGrpPosSet(lbl_1_bss_3AA, 434 + (400 * temp_f31), 65);
        }
        if (temp_r31 == 29) {
            Hu3DMotionTimeSet(lbl_1_bss_2C80[5], 0);
        }
        if (temp_r31 == 30) {
            Hu3DMotionShiftSet(lbl_1_bss_2C80[5], lbl_1_bss_2C66[7], 0, 8, HU3D_MOTATTR_LOOP);
        }
        if (temp_r31 > 30) {
            temp_f31 = (temp_r31 - 30.0) / 30.0;
            VECScale(&sp14, &sp8, temp_f31);
            VECAdd(&sp20, &sp8, &sp8);
            Hu3DModelPosSetV(lbl_1_bss_2C80[5], &sp8);
            if (temp_r31 <= 40) {
                temp_f31 = (temp_r31 - 30) / 10.0;
                Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, temp_f30 * temp_f31, 0);
            }
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(lbl_1_bss_2C80[5], lbl_1_bss_2C66[6], 0, 8, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
        temp_f31 = 1.0 - (temp_r31 / 10.0);
        Hu3DModelRotSet(lbl_1_bss_2C80[5], 0, temp_f31 * temp_f30, 0);
        HuPrcVSleep();
    }
    HuSprGrpKill(lbl_1_bss_3A8);
    lbl_1_bss_3A8 = 0;
    HuSprGrpKill(lbl_1_bss_3AA);
    lbl_1_bss_3AA = 0;
}

s32 fn_1_16B30(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    AnimData *temp_r23;
    s16 temp_r22;
    s16 temp_r21;
    s16 temp_r20;
    float temp_f31;

    s16 sp22[9];
    s16 sp1E[2];
    s16 sp1A[2];
    s16 sp16[2];
    s16 sp12[2];
    char spE[2][2];

    for (temp_r31 = 0; temp_r31 < 9; temp_r31++) {
        if (mgTicTacToeGrid[temp_r31 % 3][temp_r31 / 3] & 0x4) {
            sp1E[0] = temp_r31;
        }
        if (mgTicTacToeGrid[temp_r31 % 3][temp_r31 / 3] & 0x8) {
            sp1E[1] = temp_r31;
        }
    }
    HuPrcSleep(60);
    sp16[0] = sp16[1] = 0;
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        sp16[temp_r31 / 2] += GWPlayerCoinWinGet(lbl_1_bss_2C1C[temp_r31]) + GWPlayerCoinCollectGet(lbl_1_bss_2C1C[temp_r31]);
    }
    sp12[0] = sp12[1] = 0;
    if (sp16[0] != sp16[1]) {
        if (sp16[0] > sp16[1]) {
            sp12[0] = 1;
        }
        else {
            sp12[1] = 1;
        }
    }
    for (temp_r30 = 0, temp_r28 = -1; temp_r30 < 2; temp_r30++) {
        temp_r22 = sp1E[temp_r30] % 3;
        temp_r21 = sp1E[temp_r30] / 3;
        if (sp12[temp_r30] != 0) {
            mgTicTacToeGrid[temp_r22][temp_r21] = (1 << temp_r30);
            temp_r28 = temp_r30;
        }
        else {
            mgTicTacToeGrid[temp_r22][temp_r21] &= ~(4 << temp_r30);
        }
    }
    if (lbl_1_data_168 == -1) {
        lbl_1_data_168 = fn_1_2530C(0, 0, 0);
    }
    if (temp_r28 != -1) {
        HuWinInsertMesSet(lbl_1_data_168, lbl_1_bss_2C24[temp_r28 * 2], 0);
        HuWinInsertMesSet(lbl_1_data_168, lbl_1_bss_2C24[(temp_r28 * 2) + 1], 1);
        fn_1_25838(lbl_1_data_168, 0x280016, -1, -1);
    }
    else {
        fn_1_25838(lbl_1_data_168, 0x280013, -1, -1);
    }
    temp_r26 = espEntry(0x62005D, 100, 0);
    espColorSet(temp_r26, 255, 255, 192);
    espAttrSet(temp_r26, HUSPR_ATTR_ADDCOL | HUSPR_ATTR_DISPOFF | HUSPR_ATTR_LOOP);
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
            if (sp12[temp_r30]) {
                if (temp_r31 == 0) {
                    temp_r23 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 87) + temp_r30, MEMORY_DEFAULT_NUM));
                    temp_r24 = HuSprCreate(temp_r23, 170, 0);
                    HuSprGrpMemberSet(lbl_1_bss_3A8, sp1E[temp_r30] + 3, temp_r24);
                    HuSprPosSet(lbl_1_bss_3A8, sp1E[temp_r30] + 3, ((sp1E[temp_r30] % 3) * 56) - 56, ((sp1E[temp_r30] / 3) * 56) - 56);
                    HuSprAttrSet(lbl_1_bss_3A8, sp1E[temp_r30] + 3, HUSPR_ATTR_DISPOFF);
                    espAttrReset(temp_r26, HUSPR_ATTR_DISPOFF);
                    espPosSet(temp_r26, (((sp1E[temp_r30] % 3) * 56) + 288.0f) - 56, ((sp1E[temp_r30] / 3) * 56) + 184);
                    HuAudFXPlay(825);
                    HuAudFXPlay(826);
                }
                if (temp_r31 == 8) {
                    HuSprAttrReset(lbl_1_bss_3A8, sp1E[temp_r30] + 3, HUSPR_ATTR_DISPOFF);
                }
                if (temp_r31 == 14) {
                    espKill(temp_r26);
                }
            }
            else {
                temp_f31 = 1 - (temp_r31 / 30.0);
                HuSprTPLvlSet(lbl_1_bss_3A8, temp_r30 + 14, temp_f31);
            }
        }
        HuPrcVSleep();
    }
    HuSprAttrSet(lbl_1_bss_3A8, 14, HUSPR_ATTR_DISPOFF);
    HuSprTPLvlSet(lbl_1_bss_3A8, 14, 1.0f);
    HuSprAttrSet(lbl_1_bss_3A8, 15, HUSPR_ATTR_DISPOFF);
    HuSprTPLvlSet(lbl_1_bss_3A8, 15, 1.0f);
    for (temp_r31 = 0; temp_r31 < 9; temp_r31++) {
        sp22[temp_r31] = 0;
    }
    temp_r27 = 0;
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        for (temp_r31 = 0; temp_r31 < 8; temp_r31++) {
            temp_r29 = lbl_1_data_16A[temp_r31 * 3];
            if ((1 << temp_r30) & mgTicTacToeGrid[temp_r29 % 3][temp_r29 / 3]) {
                temp_r29 = lbl_1_data_16A[(temp_r31 * 3) + 1];
                if ((1 << temp_r30) & mgTicTacToeGrid[temp_r29 % 3][temp_r29 / 3]) {
                    temp_r29 = lbl_1_data_16A[(temp_r31 * 3) + 2];
                    if ((1 << temp_r30) & mgTicTacToeGrid[temp_r29 % 3][temp_r29 / 3]) {
                        temp_r29 = lbl_1_data_16A[temp_r31 * 3];
                        if (sp22[temp_r29] == 0) {
                            sp22[temp_r29]++;
                            temp_r27++;
                        }
                        temp_r29 = lbl_1_data_16A[(temp_r31 * 3) + 1];
                        if (sp22[temp_r29] == 0) {
                            sp22[temp_r29]++;
                            temp_r27++;
                        }
                        temp_r29 = lbl_1_data_16A[(temp_r31 * 3) + 2];
                        if (sp22[temp_r29] == 0) {
                            sp22[temp_r29]++;
                            temp_r27++;
                        }
                    }
                }
            }
        }
    }
    if (temp_r27 == 0) {
        sp1A[0] = sp1A[1] = 0;
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
                temp_r20 = mgTicTacToeGrid[temp_r31][temp_r30];
                if (temp_r20 & 0x1) {
                    sp1A[0]++;
                }
                if (temp_r20 & 0x2) {
                    sp1A[1]++;
                }
            }
        }
        if (sp1A[0] + sp1A[1] >= 9) {
            for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
                spE[temp_r31][0] = sp1A[temp_r31] + '0';
                spE[temp_r31][1] = 0;
                HuWinInsertMesSet(lbl_1_data_168, MAKE_MESSID_PTR(&spE[temp_r31][0]), (s32)temp_r31);
            }
            if (sp1A[0] > sp1A[1]) {
                temp_r28 = 0;
            }
            else {
                temp_r28 = 1;
            }
            HuPrcSleep(30);
            HuAudFXPlay(2175);
            HuWinInsertMesSet(lbl_1_data_168, lbl_1_bss_2C24[(temp_r28 * 2) + 0], 2);
            HuWinInsertMesSet(lbl_1_data_168, lbl_1_bss_2C24[(temp_r28 * 2) + 1], 3);
            fn_1_25838(lbl_1_data_168, 0x280025, -1, -1);
            fn_1_25584(lbl_1_data_168);
            lbl_1_data_168 = -1;
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        temp_r23 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 93), MEMORY_DEFAULT_NUM));
        temp_r25 = HuSprGrpCreate(temp_r27);
        for (temp_r30 = temp_r31 = 0; temp_r30 < 9; temp_r30++) {
            if (sp22[temp_r30] == 0) {
                continue;
            }
            temp_r24 = HuSprCreate(temp_r23, 100, 0);
            HuSprGrpMemberSet(temp_r25, temp_r31, temp_r24);
            HuSprPosSet(temp_r25, temp_r31, (((temp_r30 % 3) * 56) + 288.0f) - 56, ((temp_r30 / 3) * 56) + 184);
            HuSprAttrSet(temp_r25, temp_r31, HUSPR_ATTR_LOOP);
            temp_r31++;
        }
        HuPrcSleep(14);
        HuSprGrpKill(temp_r25);
        HuAudFXPlay(2175);
        HuWinInsertMesSet(lbl_1_data_168, lbl_1_bss_2C24[(temp_r28 * 2) + 0], 0);
        HuWinInsertMesSet(lbl_1_data_168, lbl_1_bss_2C24[(temp_r28 * 2) + 1], 1);
        fn_1_25838(lbl_1_data_168, 0x280017, -1, -1);
        fn_1_25584(lbl_1_data_168);
        lbl_1_data_168 = -1;
        return 1;
    }
}

void fn_1_17A5C(void)
{
    HuSprGrp *gp = &HuSprGrpData[lbl_1_bss_3A8];
    s16 j;
    s16 i;
    for (j = 0; j <= 30; j++) {
        float tplvl = 1.0 - (j / 30.0);
        for (i = 3; i < 12; i++) {
            if (gp->members[i] != -1) {
                HuSprData[gp->members[i]].a = 255.0f * tplvl;
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mgTicTacToeGrid[i][j] = 0;
        }
    }
}

void fn_1_17BE0(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r23;
    s16 temp_r22;
    s16 temp_r21;

    s16 sp2A[9];
    s16 sp18[9];
    s16 sp8[8];
    for (temp_r26 = 0; temp_r26 < 2; temp_r26++) {
        for (temp_r31 = 0; temp_r31 < 8; temp_r31++) {
            temp_r28 = 0;
            temp_r25 = -1;
            temp_r30 = lbl_1_data_16A[(temp_r31 * 3) + 0];
            if ((1 << temp_r26) & mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3]) {
                temp_r28++;
            }
            else if ((mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3] & 0x3) == 0) {
                temp_r25 = temp_r30;
            }
            temp_r30 = lbl_1_data_16A[(temp_r31 * 3) + 1];
            if ((1 << temp_r26) & mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3]) {
                temp_r28++;
            }
            else if ((mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3] & 0x3) == 0) {
                temp_r25 = temp_r30;
            }
            temp_r30 = lbl_1_data_16A[(temp_r31 * 3) + 2];
            if ((1 << temp_r26) & mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3]) {
                temp_r28++;
            }
            else if ((mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3] & 0x3) == 0) {
                temp_r25 = temp_r30;
            }
            if (temp_r28 == 2 && temp_r25 != -1) {
                OSReport("%d:LEACH\n", temp_r26);
                lbl_1_bss_3B0[temp_r26] = temp_r25;
                break;
            }
        }
        if (temp_r31 != 8) {
            continue;
        }
        if (frandmod(5) != 0) {
            temp_r29 = temp_r26 ^ 1;
            for (temp_r31 = 0; temp_r31 < 8; temp_r31++) {
                temp_r28 = 0;
                temp_r25 = -1;
                temp_r30 = lbl_1_data_16A[(temp_r31 * 3) + 0];
                if ((1 << temp_r29) & mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3]) {
                    temp_r28++;
                }
                else if ((mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3] & 0x3) == 0) {
                    temp_r25 = temp_r30;
                }
                temp_r30 = lbl_1_data_16A[(temp_r31 * 3) + 1];
                if ((1 << temp_r29) & mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3]) {
                    temp_r28++;
                }
                else if ((mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3] & 0x3) == 0) {
                    temp_r25 = temp_r30;
                }
                temp_r30 = lbl_1_data_16A[(temp_r31 * 3) + 2];
                if ((1 << temp_r29) & mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3]) {
                    temp_r28++;
                }
                else if ((mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3] & 0x3) == 0) {
                    temp_r25 = temp_r30;
                }
                if (temp_r28 == 2 && temp_r25 != -1) {
                    lbl_1_bss_3B0[temp_r26] = temp_r25;
                    break;
                }
            }
            if (temp_r31 != 8) {
                continue;
            }
        }
        for (temp_r31 = temp_r24 = temp_r21 = 0; temp_r31 < 9; temp_r31++) {
            if ((1 << temp_r26) & mgTicTacToeGrid[temp_r31 % 3][temp_r31 / 3]) {
                sp2A[temp_r24] = temp_r31;
                temp_r24++;
            }
            else if ((mgTicTacToeGrid[temp_r31 % 3][temp_r31 / 3] & 0x3) == 0) {
                sp18[temp_r21++] = temp_r31;
            }
        }
        if (temp_r24 == 0) {
            OSReport("%d:KOMA None\n", temp_r26);
            for (temp_r31 = 0; temp_r31 < 50; temp_r31++) {
                temp_r30 = lbl_1_data_1AC[frandmod(8)];
                if ((mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3] & 0x3) == 0) {
                    lbl_1_bss_3B0[temp_r26] = temp_r30;
                    break;
                }
            }
            if (temp_r31 == 50) {
                lbl_1_bss_3B0[temp_r26] = sp18[frandmod(temp_r21)];
            }
        }
        else {
            for (temp_r22 = 0; temp_r22 < 50; temp_r22++) {
                temp_r29 = sp2A[frandmod(temp_r24)];
                temp_r27 = 0;
                if ((temp_r29 % 3) != 0 && (mgTicTacToeGrid[(temp_r29 - 1) % 3][temp_r29 / 3] & 0x3) == 0) {
                    sp8[temp_r27++] = temp_r29 - 1;
                }
                if ((temp_r29 % 3) != 2 && (mgTicTacToeGrid[(temp_r29 + 1) % 3][temp_r29 / 3] & 0x3) == 0) {
                    sp8[temp_r27++] = temp_r29 + 1;
                }
                if ((temp_r29 / 3) != 0 && (mgTicTacToeGrid[temp_r29 % 3][(temp_r29 - 3) / 3] & 0x3) == 0) {
                    sp8[temp_r27++] = temp_r29 - 3;
                }
                if ((temp_r29 / 3) != 2 && (mgTicTacToeGrid[temp_r29 % 3][(temp_r29 + 3) / 3] & 0x3) == 0) {
                    sp8[temp_r27++] = temp_r29 + 3;
                }
                if ((temp_r29 % 3) != 0 && (temp_r29 / 3) != 0 && (mgTicTacToeGrid[(temp_r29 - 4) % 3][(temp_r29 - 4) / 3] & 0x3) == 0) {
                    sp8[temp_r27++] = temp_r29 - 4;
                }
                if ((temp_r29 % 3) != 2 && (temp_r29 / 3) != 0 && (mgTicTacToeGrid[(temp_r29 - 2) % 3][(temp_r29 - 2) / 3] & 0x3) == 0) {
                    sp8[temp_r27++] = temp_r29 - 2;
                }
                if ((temp_r29 % 3) != 0 && (temp_r29 / 3) != 2 && (mgTicTacToeGrid[(temp_r29 + 2) % 3][(temp_r29 + 2) / 3] & 0x3) == 0) {
                    sp8[temp_r27++] = temp_r29 + 2;
                }
                if ((temp_r29 % 3) != 2 && (temp_r29 / 3) != 2 && (mgTicTacToeGrid[(temp_r29 + 4) % 3][(temp_r29 + 4) / 3] & 0x3) == 0) {
                    sp8[temp_r27++] = temp_r29 + 4;
                }
                if (temp_r27 != 0) {
                    temp_r23 = sp8[frandmod(temp_r27)];
                    for (temp_r31 = 0; temp_r31 < 8; temp_r31++) {
                        temp_r28 = 0;
                        if (temp_r29 == lbl_1_data_16A[(temp_r31 * 3) + 0] || temp_r29 == lbl_1_data_16A[(temp_r31 * 3) + 1]
                            || temp_r29 == lbl_1_data_16A[(temp_r31 * 3) + 2]) {
                            temp_r28++;
                        }
                        if (temp_r23 == lbl_1_data_16A[(temp_r31 * 3) + 0] || temp_r23 == lbl_1_data_16A[(temp_r31 * 3) + 1]
                            || temp_r23 == lbl_1_data_16A[(temp_r31 * 3) + 2]) {
                            temp_r28++;
                        }
                        if (temp_r28 == 2) {
                            for (temp_r28 = 0; temp_r28 < 3; temp_r28++) {
                                if (temp_r29 != lbl_1_data_16A[(temp_r31 * 3) + temp_r28] && temp_r23 != lbl_1_data_16A[(temp_r31 * 3) + temp_r28]) {
                                    break;
                                }
                            }
                            temp_r30 = lbl_1_data_16A[(temp_r31 * 3) + temp_r28];
                            if (mgTicTacToeGrid[temp_r30 % 3][temp_r30 / 3] & 0x3) {
                                temp_r30 = -1;
                            }
                            break;
                        }
                    }
                    if (temp_r31 == 8 || temp_r30 < 0) {
                        continue;
                    }
                    lbl_1_bss_3B0[temp_r26] = temp_r23;
                    break;
                }
            }
            if (temp_r22 == 50) {
                lbl_1_bss_3B0[temp_r26] = sp18[frandmod(temp_r21)];
            }
        }
    }
    OSReport("com %d,%d\n", lbl_1_bss_3B0[0], lbl_1_bss_3B0[1]);
}
