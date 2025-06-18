#include "REL/mgmodedll.h"
#include "game/gamework.h"

#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/wipe.h"

#include "ext_math.h"
#include <string.h>

s16 lbl_1_bss_352[2][7];
s16 lbl_1_bss_34A[4];
s16 lbl_1_bss_348;
s16 lbl_1_bss_340[4];
s16 lbl_1_bss_318[10][2];
s16 lbl_1_bss_316;
s16 lbl_1_bss_30E[4];
s16 lbl_1_bss_30C;
Vec lbl_1_bss_2F4[2];
s16 lbl_1_bss_2F0;
s16 lbl_1_bss_2EE;
s16 lbl_1_bss_2EC;
float lbl_1_bss_2E8;
s16 lbl_1_bss_2E6;
s16 lbl_1_bss_2E4;
s16 lbl_1_bss_2E2;
static s16 pad_05_000002E0_bss;

s16 lbl_1_data_A0 = -1;

s16 lbl_1_data_A2[7] = { 0, 1, 2, 4, 3, 6, 9 };

float lbl_1_data_B0[4] = { 370, 412, 488, 530 };

s32 lbl_1_data_C0[4] = {
    DATA_MAKE_NUM(DATADIR_MGMODE, 0x37),
    DATA_MAKE_NUM(DATADIR_MGMODE, 0x3D),
    DATA_MAKE_NUM(DATADIR_MGMODE, 0x3A),
    DATA_MAKE_NUM(DATADIR_MGMODE, 0x40),
};

void fn_1_9E44(void);
void fn_1_9F64(s16 arg0, s16 arg1, s16 arg2);
void fn_1_A364(s16 arg0, float arg1, float arg2, s16 arg3);

void fn_1_A624(void);
void fn_1_A6A8(void);
void fn_1_ACAC(s16 arg0, s16 arg1);
void fn_1_ADA0(s32 arg0);

void fn_1_AE20(s16 arg0, s16 arg1, s16 arg2, s16 arg3);

s16 fn_1_B5A8(s16 *arg0, s16 *arg1);
void fn_1_B770(void);
void fn_1_B9B8(void);
s32 fn_1_BB24(void);
void fn_1_BFA0(s16 arg0);
s32 fn_1_C0C8(s32 arg0);

s32 fn_1_6D28(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    s32 temp_r24;
    s16 temp_r23;
    s16 spC[6];
    s16 spA;
    s16 sp8;
    float temp_f31;
    temp_r25 = 1;
    fn_1_279FC(0);
    fn_1_A6A8();
    fn_1_9E44();
    spA = sp8 = 0;
    mgInstExitEnableF = 1;
    mgTypeCurr = 0;
    _SetFlag(11);
    fn_1_B770();
    if (lbl_1_bss_2A6 != 2) {
        temp_r28 = lbl_1_bss_2C2C[1];
    }
    else {
        temp_r28 = lbl_1_bss_2C2C[2];
    }
    if (mgModeEvtNo == 1 || mgModeEvtNo == 2) {
        mgTypeCurr = fn_1_B5A8(&spA, &sp8);
        espAttrReset(lbl_1_bss_2C2C[3], HUSPR_ATTR_DISPOFF);
        espTPLvlSet(lbl_1_bss_2C2C[3], 1.0f);
        espAttrReset(temp_r28, HUSPR_ATTR_DISPOFF);
        espPosSet(temp_r28, 288, 70);
        espAttrReset(lbl_1_bss_2C2C[13], HUSPR_ATTR_DISPOFF);
        espPosSet(lbl_1_bss_2C2C[13], 450, 216);
        if (lbl_1_bss_2A6 == 0) {
            espAttrReset(lbl_1_bss_2C2C[4], HUSPR_ATTR_DISPOFF);
            espPosSet(lbl_1_bss_2C2C[4], 450, 404);
            if (mgModeEvtNo == 1) {
                fn_1_BFA0(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8]);
                espAttrReset(lbl_1_bss_2C2C[14], HUSPR_ATTR_DISPOFF);
                espPosSet(lbl_1_bss_2C2C[14], 450, 348);
                for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                    HuSprAttrReset(lbl_1_bss_34A[temp_r30], 0, HUSPR_ATTR_DISPOFF);
                    HuSprAttrReset(lbl_1_bss_34A[temp_r30], 1, HUSPR_ATTR_DISPOFF);
                    HuSprGrpPosSet(lbl_1_bss_34A[temp_r30], (temp_r30 * 50) + 375, 348);
                }
            }
            else {
                espAttrReset(lbl_1_bss_2C2C[15], HUSPR_ATTR_DISPOFF);
                espPosSet(lbl_1_bss_2C2C[15], 450, 348);
                espAttrReset(lbl_1_bss_2C2C[16], HUSPR_ATTR_DISPOFF);
                espPosSet(lbl_1_bss_2C2C[16], 450, 348);
                for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                    HuSprAttrReset(lbl_1_bss_34A[temp_r30], 0, HUSPR_ATTR_DISPOFF);
                    HuSprAttrReset(lbl_1_bss_34A[temp_r30], 1, HUSPR_ATTR_DISPOFF);
                    HuSprGrpPosSet(lbl_1_bss_34A[temp_r30], lbl_1_data_B0[temp_r30], 348);
                }
            }
        }
        else if (lbl_1_bss_2A6 == 1) {
            espAttrReset(lbl_1_bss_2C2C[20], HUSPR_ATTR_DISPOFF);
            espPosSet(lbl_1_bss_2C2C[20], 450, 414);
        }
        else if (lbl_1_bss_2A6 == 2) {
            espAttrReset(lbl_1_bss_2C2C[21], HUSPR_ATTR_DISPOFF);
            espPosSet(lbl_1_bss_2C2C[21], 450, 400);
        }
        for (temp_r30 = 0; temp_r30 < lbl_1_bss_316; temp_r30++) {
            espAttrReset(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r30][1]], HUSPR_ATTR_DISPOFF);
            espPosSet(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r30][1]], 180, 270);
            espPriSet(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r30][1]], (temp_r30 * 10) + 20);
        }
        espPriSet(lbl_1_bss_2C2C[lbl_1_bss_318[mgTypeCurr][1]], 19);
        fn_1_9F64(0, lbl_1_bss_318[mgTypeCurr][0], 0);
        fn_1_A364(0, 180, 270, 19);
        fn_1_AE20(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8], 0, 450, 216);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    }
    else {
        espAttrReset(lbl_1_bss_2C2C[3], HUSPR_ATTR_DISPOFF);
        espTPLvlSet(lbl_1_bss_2C2C[3], 0.0f);
        for (temp_r31 = 0; temp_r31 <= 20; temp_r31++) {
            espTPLvlSet(lbl_1_bss_2C2C[3], temp_r31 / 20.0);
            HuPrcVSleep();
        }
        for (temp_r31 = 0; temp_r31 < lbl_1_bss_316; temp_r31++) {
            spC[temp_r31] = -1;
            espPriSet(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r31][1]], (temp_r31 * 10) + 20);
        }
        temp_r26 = 0;
        temp_r23 = (lbl_1_bss_316 * 10) + 10;
        for (temp_r31 = 0; temp_r31 <= temp_r23; temp_r31++) {
            if (temp_r31 <= 20) {
                temp_f31 = temp_r31 / 20.0;
                espAttrReset(temp_r28, HUSPR_ATTR_DISPOFF);
                espPosSet(temp_r28, 288, -100 + (170 * sind(temp_f31 * 90.0f)));
            }
            if (temp_r31 <= 20) {
                temp_f31 = temp_r31 / 20.0;
                espAttrReset(lbl_1_bss_2C2C[13], HUSPR_ATTR_DISPOFF);
                espPosSet(lbl_1_bss_2C2C[13], (-350 * sind(temp_f31 * 90.0f)) + 800, 216);
                if (lbl_1_bss_2A6 == 0) {
                    espAttrReset(lbl_1_bss_2C2C[4], HUSPR_ATTR_DISPOFF);
                    espPosSet(lbl_1_bss_2C2C[4], (-350 * sind(temp_f31 * 90.0f)) + 800, 404);
                    if (lbl_1_bss_2A4 != 1) {
                        espAttrReset(lbl_1_bss_2C2C[14], HUSPR_ATTR_DISPOFF);
                        espPosSet(lbl_1_bss_2C2C[14], (-350 * sind(temp_f31 * 90.0f)) + 800, 348);
                        for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                            HuSprAttrReset(lbl_1_bss_34A[temp_r30], 0, HUSPR_ATTR_DISPOFF);
                            HuSprAttrReset(lbl_1_bss_34A[temp_r30], 1, HUSPR_ATTR_DISPOFF);
                            HuSprGrpPosSet(lbl_1_bss_34A[temp_r30], (temp_r30 * 50) + (((-350 * sind(temp_f31 * 90.0f)) + 800) - 75), 348);
                        }
                    }
                    else {
                        espAttrReset(lbl_1_bss_2C2C[15], HUSPR_ATTR_DISPOFF);
                        espPosSet(lbl_1_bss_2C2C[15], (-350 * sind(temp_f31 * 90.0f)) + 800, 348);
                        espAttrReset(lbl_1_bss_2C2C[16], HUSPR_ATTR_DISPOFF);
                        espPosSet(lbl_1_bss_2C2C[16], (-350 * sind(temp_f31 * 90.0f)) + 800, 348);
                        for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                            HuSprAttrReset(lbl_1_bss_34A[temp_r30], 0, HUSPR_ATTR_DISPOFF);
                            HuSprAttrReset(lbl_1_bss_34A[temp_r30], 1, HUSPR_ATTR_DISPOFF);
                            HuSprGrpPosSet(lbl_1_bss_34A[temp_r30], (800.0 * (1 - sind(temp_f31 * 90.0f))) + lbl_1_data_B0[temp_r30], 348);
                        }
                    }
                }
                else {
                    if (lbl_1_bss_2A6 == 1) {
                        espAttrReset(lbl_1_bss_2C2C[20], HUSPR_ATTR_DISPOFF);
                        espPosSet(lbl_1_bss_2C2C[20], (-350 * sind(temp_f31 * 90.0f)) + 800, 414);
                    }
                    else if (lbl_1_bss_2A6 == 2) {
                        espAttrReset(lbl_1_bss_2C2C[21], HUSPR_ATTR_DISPOFF);
                        espPosSet(lbl_1_bss_2C2C[21], (-350 * sind(temp_f31 * 90.0f)) + 800, 400);
                    }
                }
            }
            for (temp_r30 = 0; temp_r30 < lbl_1_bss_316; temp_r30++) {
                if (temp_r31 >= ((lbl_1_bss_316 - temp_r30) - 1) * 10 && temp_r31 <= (((lbl_1_bss_316 - temp_r30) - 1) * 10) + 10) {
                    temp_f31 = (temp_r31 - (((lbl_1_bss_316 - temp_r30) - 1) * 10)) / 10.0;
                    if (0.0 == temp_f31) {
                        temp_r26++;
                        fn_1_9F64(temp_r26 & 0x1, lbl_1_bss_318[temp_r30][0], 0);
                    }
                    espAttrReset(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r30][1]], HUSPR_ATTR_DISPOFF);
                    espPosSet(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r30][1]], 180, 800 + (-530 * sind(temp_f31 * 90.0f)));
                    espPriSet(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r30][1]], (temp_r30 * 10) + 10);
                    fn_1_A364(temp_r26 & 0x1, 180, 800 + (-530 * sind(temp_f31 * 90.0f)), (temp_r30 * 10) + 8);
                }
            }
            HuPrcVSleep();
        }
        fn_1_AE20(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][0], 10, 450, 216);
    }
    espAttrReset(lbl_1_bss_2C2C[19], HUSPR_ATTR_DISPOFF);
    espPosSet(lbl_1_bss_2C2C[19], 204, (sp8 * 38) + 154);
    espPriSet(lbl_1_bss_2C2C[19], 7);
    espTPLvlSet(lbl_1_bss_2C2C[19], 0.7);
    espAttrSet(lbl_1_bss_2C2C[17], HUSPR_ATTR_DISPOFF);
    espPosSet(lbl_1_bss_2C2C[17], 204, 126);
    espPriSet(lbl_1_bss_2C2C[17], 8);
    espAttrSet(lbl_1_bss_2C2C[18], HUSPR_ATTR_DISPOFF);
    espPosSet(lbl_1_bss_2C2C[18], 204, 410);
    espPriSet(lbl_1_bss_2C2C[18], 8);
    espBankSet(lbl_1_bss_2C2C[18], 1);
    fn_1_A364(0, 180, 270, 7);
    fn_1_9F64(0, lbl_1_bss_318[mgTypeCurr][0], spA);
    fn_1_A364(1, 180, 270, 100);
    fn_1_ACAC(lbl_1_bss_20AC[lbl_1_bss_318[mgTypeCurr][0]], lbl_1_bss_2638[lbl_1_bss_318[mgTypeCurr][0]]);
    fn_1_ADA0(1);
    HuPrcSleep(10);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    while (1) {
        HuPrcVSleep();
        if (spA != 0) {
            espAttrReset(lbl_1_bss_2C2C[17], HUSPR_ATTR_DISPOFF);
        }
        else {
            espAttrSet(lbl_1_bss_2C2C[17], HUSPR_ATTR_DISPOFF);
        }
        if (spA + 7 < lbl_1_bss_2638[lbl_1_bss_318[mgTypeCurr][0]]) {
            espAttrReset(lbl_1_bss_2C2C[18], HUSPR_ATTR_DISPOFF);
        }
        else {
            espAttrSet(lbl_1_bss_2C2C[18], HUSPR_ATTR_DISPOFF);
        }
        temp_r27 = temp_r29 = 0;
        if (HuPadDStkRep[0] & PAD_BUTTON_UP) {
            temp_r29 = -1;
        }
        else if (HuPadDStkRep[0] & PAD_BUTTON_DOWN) {
            temp_r29 = 1;
        }
        else if ((HuPadDStkRep[0] & PAD_BUTTON_LEFT) || (HuPadBtnRep[0] & PAD_BUTTON_TRIGGER_L)) {
            temp_r27 = -1;
        }
        else if ((HuPadDStkRep[0] & PAD_BUTTON_RIGHT) || (HuPadBtnRep[0] & PAD_BUTTON_TRIGGER_R)) {
            temp_r27 = 1;
        }
        if (temp_r29 != 0) {
            if (sp8 + temp_r29 < 0 && spA != 0) {
                spA--;
                fn_1_AE20(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8], 5, 450, 216);
                for (temp_r31 = 0; temp_r31 <= 4; temp_r31++) {
                    espPosSet(lbl_1_bss_2C2C[17], 204, 126 - (8.0 * sind(temp_r31 * 45.0)));
                    if (temp_r31 == 2) {
                        HuAudFXPlay(772);
                        fn_1_9F64(0, lbl_1_bss_318[mgTypeCurr][0], spA);
                    }
                    HuPrcVSleep();
                }
            }
            else if (sp8 + temp_r29 >= 7 && spA + 7 < lbl_1_bss_2638[lbl_1_bss_318[mgTypeCurr][0]]) {
                spA++;
                fn_1_AE20(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8], 5, 450, 216);
                for (temp_r31 = 0; temp_r31 <= 4; temp_r31++) {
                    espPosSet(lbl_1_bss_2C2C[18], 204, 410 + (8.0 * sind(temp_r31 * 45.0)));
                    if (temp_r31 == 2) {
                        HuAudFXPlay(772);
                        fn_1_9F64(0, lbl_1_bss_318[mgTypeCurr][0], spA);
                    }
                    HuPrcVSleep();
                }
            }
            else if (sp8 + temp_r29 >= 0 && (spA + sp8 + temp_r29) < lbl_1_bss_2638[lbl_1_bss_318[mgTypeCurr][0]]) {
                fn_1_AE20(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8 + temp_r29], 5, 450, 216);
                for (temp_r31 = 0; temp_r31 <= 4; temp_r31++) {
                    espPosSet(lbl_1_bss_2C2C[19], 204, ((sp8 * 38) + 154) + (temp_r29 * (38.0 * sind(22.5 * temp_r31))));
                    HuPrcVSleep();
                    if (temp_r31 == 2) {
                        HuAudFXPlay(772);
                    }
                }
                sp8 += temp_r29;
            }
            if (lbl_1_bss_2A4 == 0) {
                fn_1_BFA0(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8]);
            }
        }
        if (temp_r27 && lbl_1_bss_316 > 1) {
            HuAudFXPlay(2172);
            fn_1_9F64(0, lbl_1_bss_318[mgTypeCurr][0], spA);
            temp_r30 = mgTypeCurr;
            if (mgTypeCurr + temp_r27 < 0) {
                mgTypeCurr = lbl_1_bss_316 - 1;
            }
            else {
                if (mgTypeCurr + temp_r27 >= lbl_1_bss_316) {
                    mgTypeCurr = 0;
                }
                else {
                    mgTypeCurr += temp_r27;
                }
            }
            espAttrSet(lbl_1_bss_2C2C[19], HUSPR_ATTR_DISPOFF);
            espAttrSet(lbl_1_bss_2C2C[17], HUSPR_ATTR_DISPOFF);
            espAttrSet(lbl_1_bss_2C2C[18], HUSPR_ATTR_DISPOFF);
            fn_1_ADA0(0);
            for (temp_r31 = 0; temp_r31 < lbl_1_bss_316; temp_r31++) {
                espPriSet(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r31][1]], 30);
            }
            espPriSet(lbl_1_bss_2C2C[lbl_1_bss_318[mgTypeCurr][1]], 25);
            espPriSet(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r30][1]], 15);
            fn_1_9F64(1, lbl_1_bss_318[temp_r30][0], spA);
            fn_1_A364(1, 180, 270, 14);
            fn_1_9F64(0, lbl_1_bss_318[mgTypeCurr][0], 0);
            fn_1_AE20(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][0], 20, 450, 216);
            for (temp_r31 = 0; temp_r31 <= 20; temp_r31++) {
                if (temp_r31 == 10) {
                    espPriSet(lbl_1_bss_2C2C[lbl_1_bss_318[mgTypeCurr][1]], 10);
                }
                espPosSet(lbl_1_bss_2C2C[lbl_1_bss_318[mgTypeCurr][1]], (300.0 * sind(temp_r31 * 9.0)) + 180.0, 270);
                if (temp_r31 >= 10) {
                    temp_r24 = 7;
                }
                else {
                    temp_r24 = 20;
                }
                fn_1_A364(0, (300.0 * sind(temp_r31 * 9.0)) + 180.0, 270, temp_r24);
                HuPrcVSleep();
            }
            fn_1_9F64(0, lbl_1_bss_318[mgTypeCurr][0], 0);
            espPriSet(lbl_1_bss_2C2C[lbl_1_bss_318[mgTypeCurr][1]], 10);
            fn_1_A364(0, 180.0, 270, 7);
            espAttrReset(lbl_1_bss_2C2C[19], HUSPR_ATTR_DISPOFF);
            espPosSet(lbl_1_bss_2C2C[19], 204, 154);
            fn_1_ACAC(lbl_1_bss_20AC[lbl_1_bss_318[mgTypeCurr][0]], lbl_1_bss_2638[lbl_1_bss_318[mgTypeCurr][0]]);
            if (lbl_1_bss_318[mgTypeCurr][0] != 9) {
                fn_1_ADA0(1);
            }
            sp8 = spA = 0;
            if (lbl_1_bss_2A4 == 0) {
                fn_1_BFA0(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8]);
            }
        }
        if ((HuPadBtnDown[0] & PAD_BUTTON_A) && lbl_1_bss_2A6 == 2) {
            temp_r31 = lbl_1_bss_318[mgTypeCurr][0];
            if (!GWMGAvailGet(lbl_1_bss_264C[temp_r31][spA + sp8] + 401)) {
                HuAudFXPlay(4);
                continue;
            }
            else {
                if (lbl_1_bss_318[mgTypeCurr][0] != 9) {
                    HuAudFXPlay(2);
                    temp_r31 = lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8] + 401;
                    if (!GWMGCustomGet(temp_r31)) {
                        GWMGCustomSet(temp_r31);
                    }
                    else {
                        GWMGCustomReset(temp_r31);
                    }
                    fn_1_9F64(0, lbl_1_bss_318[mgTypeCurr][0], spA);
                    fn_1_AE20(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8], 0, 450, 216);
                    fn_1_B9B8();
                }
                else {
                    if (lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8] >= 0) {
                        HuAudFXPlay(2);
                        temp_r31 = lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8] + 401;
                        GWMGCustomReset(temp_r31);
                        fn_1_B9B8();
                        if (lbl_1_bss_2638[lbl_1_bss_318[mgTypeCurr][0]] <= spA + sp8) {
                            if (--sp8 < 0) {
                                sp8 = 0;
                                spA--;
                            }
                            espPosSet(lbl_1_bss_2C2C[19], 204, (sp8 * 38) + 154);
                        }
                        fn_1_9F64(0, lbl_1_bss_318[mgTypeCurr][0], spA);
                        fn_1_AE20(lbl_1_bss_264C[lbl_1_bss_318[mgTypeCurr][0]][spA + sp8], 0, 450, 216);
                    }
                }
            }
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            if (lbl_1_bss_2A6 == 2 && !fn_1_BB24()) {
                continue;
            }
            temp_r25 = 0;
            break;
        }
        if (!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
            continue;
        }
        if (lbl_1_bss_2A6) {
            continue;
        }
        temp_r31 = lbl_1_bss_318[mgTypeCurr][0];
        if (!GWMGAvailGet(lbl_1_bss_264C[temp_r31][spA + sp8] + 401)) {
            HuAudFXPlay(4);
            continue;
        }
        HuAudFXPlay(773);
        GWSystem.mg_next = lbl_1_bss_264C[temp_r31][spA + sp8];
        if (lbl_1_bss_2A4 == 0) {
            GWPlayerCfg[0].group = 0;
            GWPlayerCfg[1].group = 1;
            GWPlayerCfg[2].group = 2;
            GWPlayerCfg[3].group = 3;
            if ((temp_r31 == 1 || temp_r31 == 2) && !fn_1_C0C8(0)) {
                continue;
            }
            fn_1_2783C(1);
        }
        else if (lbl_1_bss_2A4 == 1) {
            fn_1_2783C(2);
        }
        while (1) {
            HuPrcVSleep();
        }
    }
    espAttrSet(lbl_1_bss_2C2C[19], HUSPR_ATTR_DISPOFF);
    espAttrSet(lbl_1_bss_2C2C[17], HUSPR_ATTR_DISPOFF);
    espAttrSet(lbl_1_bss_2C2C[18], HUSPR_ATTR_DISPOFF);
    if (lbl_1_bss_2A6 == 2) {
        for (temp_r31 = 0; temp_r31 < 7; temp_r31++) {
            HuSprAttrSet(lbl_1_bss_2E2, temp_r31, HUSPR_ATTR_DISPOFF);
        }
    }

    fn_1_ADA0(0);
    fn_1_AE20(-1, 5, 450, 216);

    for (temp_r31 = 0; temp_r31 <= 20; temp_r31++) {
        if (temp_r31 <= 20) {
            temp_f31 = temp_r31 / 20.0;
            espAttrReset(temp_r28, HUSPR_ATTR_DISPOFF);
            espPosSet(temp_r28, 288, -100.0 + (170 * cosd(temp_f31 * 90.0f)));
        }
        if (temp_r31 <= 10) {
            temp_f31 = temp_r31 / 10.0;
            espAttrReset(lbl_1_bss_2C2C[13], HUSPR_ATTR_DISPOFF);
            espPosSet(lbl_1_bss_2C2C[13], (-350 * cosd(temp_f31 * 90.0f)) + 800, 216);
            if (lbl_1_bss_2A6 == 0) {
                espPosSet(lbl_1_bss_2C2C[4], (-350 * cosd(temp_f31 * 90.0f)) + 800, 404);
                if (lbl_1_bss_2A4 != 1) {
                    espPosSet(lbl_1_bss_2C2C[14], (-350 * cosd(temp_f31 * 90.0f)) + 800, 348);
                    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {

                        HuSprGrpPosSet(lbl_1_bss_34A[temp_r30], (temp_r30 * 50) + (((-350 * cosd(temp_f31 * 90.0f)) + 800) - 75), 348);
                    }
                }
                else {
                    espPosSet(lbl_1_bss_2C2C[15], (-350 * cosd(temp_f31 * 90.0f)) + 800, 348);
                    espPosSet(lbl_1_bss_2C2C[16], (-350 * cosd(temp_f31 * 90.0f)) + 800, 348);
                    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                        HuSprGrpPosSet(lbl_1_bss_34A[temp_r30], (800 * (1 - cosd(temp_f31 * 90.0f))) + lbl_1_data_B0[temp_r30], 348);
                    }
                }
            }
            else {
                if (lbl_1_bss_2A6 == 1) {
                    espAttrReset(lbl_1_bss_2C2C[20], HUSPR_ATTR_DISPOFF);
                    espPosSet(lbl_1_bss_2C2C[20], (-350 * cosd(temp_f31 * 90.0f)) + 800, 414);
                }
                else if (lbl_1_bss_2A6 == 2) {
                    espAttrReset(lbl_1_bss_2C2C[21], HUSPR_ATTR_DISPOFF);
                    espPosSet(lbl_1_bss_2C2C[21], (-350 * cosd(temp_f31 * 90.0f)) + 800, 400);
                }
            }
        }
        temp_f31 = temp_r31 / 20.0;
        for (temp_r30 = 0; temp_r30 < lbl_1_bss_316; temp_r30++) {
            espPosSet(lbl_1_bss_2C2C[lbl_1_bss_318[temp_r30][1]], 180, 800 + (-530 * cosd(temp_f31 * 90.0f)));
        }
        fn_1_A364(0, 180, (-530.0 * cosd(temp_f31 * 90.0f)) + 800.0, 10);
        fn_1_A364(1, 180, (-530.0 * cosd(temp_f31 * 90.0f)) + 800.0, 100);
        HuPrcVSleep();
    }
    fn_1_A624();
    for (temp_r31 = 0; temp_r31 <= 10; temp_r31++) {
        espTPLvlSet(lbl_1_bss_2C2C[3], 1.0 - (temp_r31 / 10.0));
        HuPrcVSleep();
    }
    mgInstExitEnableF = 0;
    return temp_r25;
}

void fn_1_9E44(void)
{
    s16 j;
    s16 i;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 7; j++) {
            s16 window = HuWinCreate(0, j * 24, 268, 32, 0);
            WindowData *windowP;
            lbl_1_bss_352[i][j] = window;
            windowP = &winData[window];
            windowP->spacing_x = 0;
            HuWinBGTPLvlSet(window, 0);
            HuWinMesSpeedSet(window, 0);
            HuWinDispOff(window);
            (void)i;
        }
    }
}

void fn_1_9F64(s16 arg0, s16 arg1, s16 arg2)
{
    s16 i;
    s16 no;
    s16 window;
    if (lbl_1_bss_2A6 == 2 && lbl_1_bss_30C == arg0) {
        for (i = 0; i < 4; i++) {
            HuSprAttrSet(lbl_1_bss_2E2, i + 14, HUSPR_ATTR_DISPOFF);
        }
    }
    if (arg1 == 9) {
        for (i = 0; i < 7; i++) {
            HuSprAttrSet(lbl_1_bss_2E2, i + (arg0 * 7), HUSPR_ATTR_DISPOFF);
            window = lbl_1_bss_352[arg0][i];
            if (i + arg2 >= lbl_1_bss_2638[9]) {
                HuWinDispOff(window);
            }
            else {
                no = lbl_1_bss_264C[9][i + arg2];
                if (no < 0) {
                    lbl_1_bss_30C = arg0;
                    no = -no - 1;
                    lbl_1_bss_30E[no] = i;
                    HuSprAttrReset(lbl_1_bss_2E2, no + 14, HUSPR_ATTR_DISPOFF);
                    HuSprPosSet(lbl_1_bss_2E2, no + 14, 24 + lbl_1_bss_2F4[arg0].x, (lbl_1_bss_2F4[arg0].y + (i * 38)) - 116);
                    HuWinDispOff(window);
                }
                else {
                    HuWinMesSet(window, mgInfoTbl[no].name_mess);
                    HuWinDispOn(window);
                }
            }
        }
    }
    else {
        for (i = 0; i < 7; i++) {
            window = lbl_1_bss_352[arg0][i];
            if (i + arg2 >= lbl_1_bss_2638[arg1]) {
                HuWinDispOff(window);
                if (lbl_1_bss_2A6 == 2) {
                    HuSprAttrSet(lbl_1_bss_2E2, i + (arg0 * 7), HUSPR_ATTR_DISPOFF);
                }
            }
            else {
                no = lbl_1_bss_264C[arg1][i + arg2];
                if (GWMGAvailGet(no + 401)) {
                    HuWinMesSet(window, mgInfoTbl[no].name_mess);
                }
                else {
                    HuWinMesSet(window, MAKE_MESSID(0x23, 0x00));
                }
                HuWinDispOn(window);
                if (lbl_1_bss_2A6 == 2) {
                    if (GWMGCustomGet(no + 401)) {
                        HuSprAttrReset(lbl_1_bss_2E2, i + (arg0 * 7), HUSPR_ATTR_DISPOFF);
                    }
                    else {
                        HuSprAttrSet(lbl_1_bss_2E2, i + (arg0 * 7), HUSPR_ATTR_DISPOFF);
                    }
                }
            }
        }
    }
}

void fn_1_A364(s16 arg0, float arg1, float arg2, s16 arg3)
{
    s16 i;
    lbl_1_bss_2F4[arg0].x = arg1;
    lbl_1_bss_2F4[arg0].y = arg2;
    for (i = 0; i < 7; i++) {
        s16 window = lbl_1_bss_352[arg0][i];
        HuWinPosSet(window, arg1 - 105, (arg2 - 136) + (i * 38));
        HuWinPriSet(window, arg3);
        if (lbl_1_bss_2A6 == 2) {
            HuSprPosSet(lbl_1_bss_2E2, i + (arg0 * 7), arg1 + 24, arg2 + (i * 38) - 116);
            HuSprPriSet(lbl_1_bss_2E2, i + (arg0 * 7), arg3);
        }
    }
    if (lbl_1_bss_2A6 == 2 && lbl_1_bss_30C == arg0) {
        for (i = 0; i < 4; i++) {
            HuSprPosSet(lbl_1_bss_2E2, i + 14, arg1 + 24, arg2 + (lbl_1_bss_30E[i] * 38) - 116);
            HuSprPriSet(lbl_1_bss_2E2, i + 14, arg3 + 1);
        }
    }
}

void fn_1_A624(void)
{
    s16 j;
    s16 i;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 7; j++) {
            HuWinKill(lbl_1_bss_352[i][j]);
        }
    }
}

void fn_1_A6A8(void)
{
    s16 spA[2];
    s16 i;
    AnimData *anim;
    s16 sprite;
    s16 group;
    s16 player;
    s16 bank;
    s16 iscom;
    if (lbl_1_bss_2A4 == 1) {
        spA[0] = 0;
        spA[1] = 2;
        for (i = 0; i < 4; i++) {
            if (GWPlayerCfg[i].group >= 2) {
                lbl_1_bss_340[i] = 0;
            }
            else {
                lbl_1_bss_340[spA[GWPlayerCfg[i].group]] = i;
                spA[GWPlayerCfg[i].group]++;
            }
        }
    }
    else {
        for (i = 0; i < 4; i++) {
            lbl_1_bss_340[i] = i;
        }
    }
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_34A[i]) {
            HuSprGrpKill(lbl_1_bss_34A[i]);
        }
        player = lbl_1_bss_340[i];
        group = HuSprGrpCreate(2);
        lbl_1_bss_34A[i] = group;
        anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 0x10) + GWPlayerCfg[player].character, MEMORY_DEFAULT_NUM));
        sprite = HuSprCreate(anim, 200, 0);
        HuSprGrpMemberSet(group, 0, sprite);
        if (iscom = GWPlayerCfg[player].iscom) {
            anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 0x27), MEMORY_DEFAULT_NUM));
            bank = GWPlayerCfg[player].diff;
        }
        else {
            anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 0x26), MEMORY_DEFAULT_NUM));
            bank = lbl_1_bss_340[i];
        }
        sprite = HuSprCreate(anim, 200, bank);
        HuSprGrpMemberSet(group, 1, sprite);
        HuSprPosSet(group, 1, 0, 20);
        HuSprAttrSet(lbl_1_bss_34A[i], 0, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(lbl_1_bss_34A[i], 1, HUSPR_ATTR_DISPOFF);
    }
    if (lbl_1_bss_2E6) {
        HuSprGrpKill(lbl_1_bss_2E6);
    }
    group = HuSprGrpCreate(5);
    lbl_1_bss_2E6 = group;
    anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 0x2D), MEMORY_DEFAULT_NUM));
    for (i = 0; i < 5; i++) {
        sprite = HuSprCreate(anim, 5, 0);
        HuSprGrpMemberSet(group, i, sprite);
        HuSprPosSet(group, i, (i * 16) - 32, 0);
    }
    HuSprBankSet(group, 2, 10);
    HuSprGrpPosSet(group, 284, 410);
    fn_1_ADA0(0);
    if (lbl_1_bss_2A6 == 2 && lbl_1_bss_2E2 == 0) {
        anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 0x2B), MEMORY_DEFAULT_NUM));
        lbl_1_bss_2E2 = HuSprGrpCreate(18);
        for (i = 0; i < 14; i++) {
            sprite = HuSprCreate(anim, 8, 0);
            HuSprGrpMemberSet(lbl_1_bss_2E2, i, sprite);
            HuSprColorSet(lbl_1_bss_2E2, i, 255, 0, 0);
            HuSprAttrSet(lbl_1_bss_2E2, i, HUSPR_ATTR_ADDCOL | HUSPR_ATTR_DISPOFF);
            HuSprTPLvlSet(lbl_1_bss_2E2, i, 0.8f);
        }
        for (i = 0; i < 4; i++) {
            anim = HuSprAnimRead(HuDataReadNum(lbl_1_data_C0[i], MEMORY_DEFAULT_NUM));
            sprite = HuSprCreate(anim, 8, 0);
            HuSprGrpMemberSet(lbl_1_bss_2E2, i + 14, sprite);
            HuSprAttrSet(lbl_1_bss_2E2, i + 14, HUSPR_ATTR_DISPOFF);
        }
        HuSprGrpPosSet(lbl_1_bss_2E2, 0, 0);
    }
    lbl_1_data_A0 = -1;
    (void)sprite;
}

void fn_1_ACAC(s16 arg0, s16 arg1)
{
    s16 digit;
    digit = arg0 / 10;
    HuSprBankSet(lbl_1_bss_2E6, 0, digit);
    arg0 -= digit * 10;
    HuSprBankSet(lbl_1_bss_2E6, 1, arg0);
    digit = arg1 / 10;
    HuSprBankSet(lbl_1_bss_2E6, 3, digit);
    arg1 -= digit * 10;
    HuSprBankSet(lbl_1_bss_2E6, 4, arg1);
}

void fn_1_ADA0(s32 arg0)
{
    s16 i;
    for (i = 0; i < 5; i++) {
        if (arg0) {
            HuSprAttrReset(lbl_1_bss_2E6, i, HUSPR_ATTR_DISPOFF);
        }
        else {
            HuSprAttrSet(lbl_1_bss_2E6, i, HUSPR_ATTR_DISPOFF);
        }
    }
}

void fn_1_AED0(void);

void fn_1_AE20(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    lbl_1_bss_2F0 = arg0;
    lbl_1_bss_2E8 = arg1;
    lbl_1_bss_2EE = arg2;
    lbl_1_bss_2EC = arg3;
    HuPrcChildCreate(fn_1_AED0, 100, 12288, 0, HuPrcCurrentGet());
}

void fn_1_AED0(void)
{
    s16 temp_r31;
    s16 temp_r30;
    AnimData *temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s32 temp_r26;
    temp_r27 = lbl_1_data_A0;
    if (lbl_1_bss_2F0 < 0) {
        for (temp_r30 = 1; temp_r30 <= lbl_1_bss_2E8; temp_r30++) {
            HuSprGrpTPLvlSet(temp_r27, 1.0 - (temp_r30 / lbl_1_bss_2E8));
            HuPrcVSleep();
        }
        if (temp_r27 != -1) {
            HuSprGrpKill(temp_r27);
        }
        lbl_1_data_A0 = -1;
        HuPrcEnd();
        while (1) {
            HuPrcVSleep();
        }
    }
    lbl_1_data_A0 = HuSprGrpCreate(4);
    temp_r26 = mgInfoTbl[lbl_1_bss_2F0].mg_pic[0];
    if (GWMGAvailGet(lbl_1_bss_2F0 + 401)) {
        temp_r29 = HuSprAnimRead(HuDataReadNumHeapShortForce(temp_r26, MEMORY_DEFAULT_NUM, HEAP_DATA));
    }
    else {
        temp_r29 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x2C));
    }
    temp_r28 = HuSprCreate(temp_r29, 200, 0);
    HuSprGrpMemberSet(lbl_1_data_A0, 0, temp_r28);
    HuSprGrpPosSet(lbl_1_data_A0, lbl_1_bss_2EE, lbl_1_bss_2EC);
    HuSprGrpScaleSet(lbl_1_data_A0, 0.6f, 0.6f);
    temp_r31 = 0;
    if (mgInfoTbl[lbl_1_bss_2F0].flag & 0x1) {
        temp_r29 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x24));
        temp_r28 = HuSprCreate(temp_r29, 190, 0);
        HuSprGrpMemberSet(lbl_1_data_A0, temp_r31 + 1, temp_r28);
        HuSprPosSet(lbl_1_data_A0, temp_r31 + 1, (355.0 / 3.0) - ((temp_r31 * 50) * (100.0 / 60.0)), (355.0f / 3.0f));
        HuSprScaleSet(lbl_1_data_A0, temp_r31 + 1, 100.0f / 60.0f, 100.0f / 60.0f);
        temp_r31++;
    }
    if (mgInfoTbl[lbl_1_bss_2F0].flag & 0x2) {
        temp_r29 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x23));
        temp_r28 = HuSprCreate(temp_r29, 190, 0);
        HuSprGrpMemberSet(lbl_1_data_A0, temp_r31 + 1, temp_r28);
        HuSprPosSet(lbl_1_data_A0, temp_r31 + 1, (355.0 / 3.0) - ((temp_r31 * 50) * (100.0 / 60.0)), (355.0f / 3.0f));
        HuSprScaleSet(lbl_1_data_A0, temp_r31 + 1, 100.0f / 60.0f, 100.0f / 60.0f);
        temp_r31++;
    }
    if (GWMGCustomGet(lbl_1_bss_2F0 + 401)) {
        temp_r29 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x22));
        temp_r28 = HuSprCreate(temp_r29, 190, 0);
        HuSprGrpMemberSet(lbl_1_data_A0, temp_r31 + 1, temp_r28);
        HuSprPosSet(lbl_1_data_A0, temp_r31 + 1, (355.0 / 3.0) - ((temp_r31 * 50) * (100.0 / 60.0)), (355.0f / 3.0f));
        HuSprScaleSet(lbl_1_data_A0, temp_r31 + 1, 100.0f / 60.0f, 100.0f / 60.0f);
        temp_r31++;
    }
    for (temp_r30 = 1; temp_r30 <= lbl_1_bss_2E8; temp_r30++) {
        if (temp_r27 != -1) {
            HuSprGrpTPLvlSet(temp_r27, 1.0 - (temp_r30 / lbl_1_bss_2E8));
        }
        HuSprGrpTPLvlSet(lbl_1_data_A0, temp_r30 / lbl_1_bss_2E8);
        HuPrcVSleep();
    }
    if (temp_r27 != -1) {
        HuSprGrpKill(temp_r27);
    }
    lbl_1_bss_348 = lbl_1_bss_2F0;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

s16 fn_1_B5A8(s16 *arg0, s16 *arg1)
{
    s16 mgNo = GWSystem.mg_next;
    s16 mgType = mgInfoTbl[mgNo].type;
    s16 ret;
    s16 i;
    for (i = ret = 0; i < lbl_1_bss_316; i++) {
        if (mgType == lbl_1_bss_318[i][0]) {
            ret = i;
            break;
        }
    }
    for (i = 0; i < lbl_1_bss_2638[mgType]; i++) {
        if (mgNo == lbl_1_bss_264C[mgType][i]) {
            break;
        }
    }
    *arg1 = i;
    i = i - 3;
    if (i < 0) {
        i = 0;
    }
    if (lbl_1_bss_2638[mgType] >= 7 && i + 7 >= lbl_1_bss_2638[mgType]) {
        i = lbl_1_bss_2638[mgType] - 7;
    }
    *arg0 = i;
    if (lbl_1_bss_2638[mgType] < 7) {
        *arg0 = 0;
    }
    *arg1 = *arg1 - *arg0;
    return ret;
}

void fn_1_B770(void)
{
    if (lbl_1_bss_2A6 == 2) {
        lbl_1_bss_316 = 5;
        lbl_1_bss_318[0][0] = 0;
        lbl_1_bss_318[0][1] = 5;
        lbl_1_bss_318[1][0] = 1;
        lbl_1_bss_318[1][1] = 6;
        lbl_1_bss_318[2][0] = 2;
        lbl_1_bss_318[2][1] = 7;
        lbl_1_bss_318[3][0] = 4;
        lbl_1_bss_318[3][1] = 8;
        lbl_1_bss_318[4][0] = 9;
        lbl_1_bss_318[4][1] = 11;
        fn_1_B9B8();
    }
    else if (lbl_1_bss_2A4 == 0 || lbl_1_bss_2A6 == 1) {
        lbl_1_bss_316 = 7;
        lbl_1_bss_318[0][0] = 0;
        lbl_1_bss_318[0][1] = 5;
        lbl_1_bss_318[1][0] = 1;
        lbl_1_bss_318[1][1] = 6;
        lbl_1_bss_318[2][0] = 2;
        lbl_1_bss_318[2][1] = 7;
        lbl_1_bss_318[3][0] = 4;
        lbl_1_bss_318[3][1] = 8;
        lbl_1_bss_318[4][0] = 3;
        lbl_1_bss_318[4][1] = 9;
        lbl_1_bss_318[5][0] = 6;
        lbl_1_bss_318[5][1] = 10;
        lbl_1_bss_318[6][0] = 8;
        lbl_1_bss_318[6][1] = 12;
    }
    else if (lbl_1_bss_2A4 == 1) {
        lbl_1_bss_316 = 1;
        lbl_1_bss_318[0][0] = 2;
        lbl_1_bss_318[0][1] = 7;
    }
}

void fn_1_B9B8(void)
{
    s16 customNum;
    s16 i;
    for (i = customNum = 0; i < 4; i++) {
        s16 j;
        lbl_1_bss_264C[9][customNum++] = -i - 1;
        for (j = 0; j < lbl_1_bss_2638[lbl_1_bss_318[i][0]]; j++) {
            if (GWMGCustomGet(lbl_1_bss_264C[lbl_1_bss_318[i][0]][j] + 401)) {
                lbl_1_bss_264C[9][customNum++] = lbl_1_bss_264C[lbl_1_bss_318[i][0]][j];
            }
        }
    }
    lbl_1_bss_2638[9] = customNum;
}

s32 fn_1_BB24(void)
{
    char messInsert[4][6];
    s16 customNum[4];
    float winSize[2];
    static char messInsertBase[6] = { "\x1E\x03"
                                      "0"
                                      "\x1E\x08" };
    static s16 customMinNum[4] = { 4, 3, 3, 2 };
    s16 window;
    s16 j;
    s16 i;
    WindowData *windowP;
    s16 choice;
    for (i = 0; i < 4; i++) {
        customNum[i] = 0;
        for (j = 0; j < lbl_1_bss_20AC[lbl_1_data_A2[i]]; j++) {
            if (GWMGCustomGet(lbl_1_bss_20C0[lbl_1_data_A2[i]][j] + 401)) {
                customNum[i]++;
            }
        }
    }
    if (customNum[0] >= 4 && customNum[1] >= 3 && customNum[2] >= 3 && customNum[3] >= 2) {
        HuWinMesMaxSizeGet(1, winSize, MAKE_MESSID(0x28, 0x30));
        window = HuWinExCreateStyled(-10000, -10000, winSize[0], winSize[1], -1, 1);
        windowP = &winData[window];
        windowP->active_pad = 1;
        HuWinMesPalSet(window, 7, 0, 0, 0);
        HuWinPriSet(window, 3);
        HuWinExAnimIn(window);
        HuWinMesSet(window, MAKE_MESSID(0x28, 0x30));
        HuWinMesWait(window);
        HuWinExAnimOut(window);
        HuWinExCleanup(window);
        return 1;
    }
    else {
        HuWinInsertMesSizeGet(MAKE_MESSID_PTR(messInsertBase), 0);
        HuWinInsertMesSizeGet(MAKE_MESSID_PTR(messInsertBase), 1);
        HuWinInsertMesSizeGet(MAKE_MESSID_PTR(messInsertBase), 2);
        HuWinInsertMesSizeGet(MAKE_MESSID_PTR(messInsertBase), 3);
        HuWinMesMaxSizeGet(3, winSize, MAKE_MESSID(0x28, 0x2B), MAKE_MESSID(0x28, 0x2C), MAKE_MESSID(0x28, 0x2D));
        window = HuWinExCreateStyled(-10000, -10000, winSize[0], winSize[1], -1, 1);
        windowP = &winData[window];
        windowP->active_pad = 1;
        HuWinMesPalSet(window, 7, 0, 0, 0);
        HuWinPriSet(window, 3);
        HuWinExAnimIn(window);
        for (j = 0; j < 4; j++) {
            strcpy(&messInsert[j][0], messInsertBase);
        }
        for (j = 0; j < 4; j++) {
            if (customNum[j] >= customMinNum[j]) {
                messInsert[j][1] = 5;
            }
            else {
                messInsert[j][2] = (customMinNum[j] + '0' - customNum[j]);
            }
            HuWinInsertMesSet(window, MAKE_MESSID_PTR(&messInsert[j][0]), (s16)j);
        }
        HuWinMesSet(window, MAKE_MESSID(0x28, 0x2C));
        HuWinMesWait(window);
        HuWinMesSet(window, MAKE_MESSID(0x28, 0x2B));
        HuWinMesWait(window);
        HuWinMesSet(window, MAKE_MESSID(0x28, 0x2D));
        HuWinMesWait(window);
        choice = HuWinChoiceGet(window, 0);
        HuWinExAnimOut(window);
        HuWinExCleanup(window);
        if (choice == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
}

void fn_1_BFA0(s16 arg0)
{
    s16 i;
    for (i = 0; i < 4; i++) {
        HuSprGrpTPLvlSet(lbl_1_bss_34A[i], 1.0f);
    }
    if (mgInfoTbl[arg0].ovl == OVL_M450) {
        HuSprGrpTPLvlSet(lbl_1_bss_34A[1], 0.0f);
    }
    if (mgInfoTbl[arg0].type == 6 || mgInfoTbl[arg0].type == 8) {
        HuSprGrpTPLvlSet(lbl_1_bss_34A[2], 0.0f);
        HuSprGrpTPLvlSet(lbl_1_bss_34A[3], 0.0f);
        return;
    }
}

float lbl_1_data_E0[2][4] = { -132, -12, 60, 132, -132, -60, 60, 132 };

u8 lbl_1_data_100[16] = { 0, 1, 2, 3, 1, 0, 2, 3, 2, 0, 1, 3, 3, 0, 1, 2 };

u8 lbl_1_data_110[12] = {
    0,
    1,
    2,
    3,
    0,
    2,
    1,
    3,
    0,
    3,
    1,
    2,
};

s32 fn_1_C0C8(s32 arg0)
{
    s16 temp_r31;
    s16 temp_r30;
    float *temp_r29;
    s16 temp_r28;
    AnimData *temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r23;
    WindowData *temp_r22;
    AnimData *temp_r21;

    float temp_f31;
    float temp_f30;
    float temp_f29;
    if (mgTypeCurr == 1) {
        temp_r29 = &lbl_1_data_E0[0][0];
        temp_f29 = 216;
    }
    else {
        temp_r29 = &lbl_1_data_E0[1][0];
        temp_f29 = 288;
    }
    temp_r28 = HuSprGrpCreate(16);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r27 = HuSprAnimReadFile(lbl_1_bss_8.unk24[temp_r31].unk68 + DATA_MAKE_NUM(DATADIR_MGMODE, 0x67));
        temp_r26 = HuSprCreate(temp_r27, 4, 0);
        HuSprGrpMemberSet(temp_r28, 4 * temp_r31, temp_r26);
        HuSprPosSet(temp_r28, 4 * temp_r31, temp_r29[temp_r31], 0);
        if (mgTypeCurr == 1) {
            if (temp_r31 == 0) {
                temp_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x75));
            }
            else {
                temp_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x76));
            }
        }
        else {
            if (temp_r31 < 2) {
                temp_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x75));
            }
            else {
                temp_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x76));
            }
        }
        temp_r26 = HuSprCreate(temp_r27, 3, 0);
        HuSprGrpMemberSet(temp_r28, (4 * temp_r31) + 1, temp_r26);
        HuSprPosSet(temp_r28, (4 * temp_r31) + 1, temp_r29[temp_r31], 0);
        if (GWPlayerCfg[temp_r31].iscom) {
            temp_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x74));
        }
        else {
            temp_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x70) + GWPlayerCfg[temp_r31].pad_idx);
        }
        temp_r26 = HuSprCreate(temp_r27, 2, 1);
        HuSprGrpMemberSet(temp_r28, (4 * temp_r31) + 2, temp_r26);
        HuSprPosSet(temp_r28, (4 * temp_r31) + 2, temp_r29[temp_r31], 0);
        temp_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 0x7B));
        temp_r26 = HuSprCreate(temp_r27, 2, GWPlayerCfg[temp_r31].diff);
        HuSprGrpMemberSet(temp_r28, (4 * temp_r31) + 3, temp_r26);
        HuSprPosSet(temp_r28, (4 * temp_r31) + 3, temp_r29[temp_r31], 38);
        if (!GWPlayerCfg[temp_r31].iscom) {
            HuSprAttrSet(temp_r28, (4 * temp_r31) + 3, HUSPR_ATTR_DISPOFF);
        }
    }
    temp_r25 = HuSprGrpCreate(8);
    temp_r27 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 0x65), MEMORY_DEFAULT_NUM));
    temp_r21 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 0x66), MEMORY_DEFAULT_NUM));
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r26 = HuSprCreate(temp_r27, 3, temp_r31);
        HuSprGrpMemberSet(temp_r25, (temp_r31 * 2), temp_r26);
        HuSprPosSet(temp_r25, (temp_r31 * 2), ((temp_r31 % 2) * 380) - 190, ((temp_r31 / 2) * 156) - 68);
        temp_r26 = HuSprCreate(temp_r21, 4, temp_r31);
        HuSprGrpMemberSet(temp_r25, (temp_r31 * 2) + 1, temp_r26);
        HuSprTPLvlSet(temp_r25, (temp_r31 * 2) + 1, 0.5f);
        HuSprPosSet(temp_r25, (temp_r31 * 2) + 1, ((temp_r31 % 2) * 380) - 190, ((temp_r31 / 2) * 156) - 60);
    }
    espTPLvlSet(lbl_1_bss_2C2C[22], 0.9f);
    espAttrReset(lbl_1_bss_2C2C[22], HUSPR_ATTR_DISPOFF);
    espAttrReset(lbl_1_bss_2C2C[24], HUSPR_ATTR_DISPOFF);
    espAttrReset(lbl_1_bss_2C2C[23], HUSPR_ATTR_DISPOFF);
    espAttrReset(lbl_1_bss_2C2C[25], HUSPR_ATTR_DISPOFF);
    espAttrReset(lbl_1_bss_2C2C[26], HUSPR_ATTR_DISPOFF);
    espBankSet(lbl_1_bss_2C2C[25], 1);
    espPosSet(lbl_1_bss_2C2C[22], 288, 240);
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        if (temp_r31 <= 20) {
            temp_f30 = temp_r31 / 20.0;
            temp_f31 = -300 + (560 * sind(temp_f30 * 90.0f));
            espPosSet(lbl_1_bss_2C2C[22], 288, temp_f31);
            espPosSet(lbl_1_bss_2C2C[24], 288, temp_f31 - 50);
            espPosSet(lbl_1_bss_2C2C[23], temp_f29, temp_f31 + 20);
            espPosSet(lbl_1_bss_2C2C[26], 108, temp_f31 + 20);
            espPosSet(lbl_1_bss_2C2C[25], 468, temp_f31 + 20);
            HuSprGrpPosSet(temp_r28, 288, temp_f31 + 20);
            HuSprGrpPosSet(temp_r25, 288, temp_f31);
        }
        else {
            temp_f30 = (temp_r31 - 20) / 10.0;
            temp_f31 = 240 + (20 * cosd(temp_f30 * 90.0f));
            espPosSet(lbl_1_bss_2C2C[22], 288, temp_f31);
            espPosSet(lbl_1_bss_2C2C[24], 288, temp_f31 - 50);
            espPosSet(lbl_1_bss_2C2C[23], temp_f29, temp_f31 + 20);
            espPosSet(lbl_1_bss_2C2C[26], 108, temp_f31 + 20);
            espPosSet(lbl_1_bss_2C2C[25], 468, temp_f31 + 20);
            HuSprGrpPosSet(temp_r28, 288, temp_f31 + 20);
            HuSprGrpPosSet(temp_r25, 288, temp_f31);
        }
        HuPrcVSleep();
    }
    temp_r24 = fn_1_25CA8(0x1A0020);
    temp_r22 = &winData[temp_r24];
    HuWinPriSet(temp_r24, 5);
    HuWinPosSet(temp_r24, (576.0f - temp_r22->w) / 2.0f, 310.0f);
    temp_r30 = 0;
    temp_r23 = 0;
    while (1) {
        s16 spC;
        HuPrcVSleep();
        if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            goto loop_end;
        }
        spC = 0;
        if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
            HuAudFXPlay(772);
            for (temp_r31 = 0; temp_r31 <= 5; temp_r31++) {
                temp_f30 = temp_r31 / 5.0;
                espPosSet(lbl_1_bss_2C2C[26], 108 - (10 * sind(temp_f30 * 90.0f)), 20 + temp_f31);
                HuPrcVSleep();
            }
            temp_r30--;
            if (mgTypeCurr == 1) {
                if (temp_r30 < 0) {
                    temp_r30 = 3;
                }
                if (temp_r30 >= 4) {
                    temp_r30 = 0;
                }
                for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                    HuSprPosSet(temp_r28, lbl_1_data_100[(temp_r30 * 4) + temp_r31] * 4, temp_r29[temp_r31], 0);
                    HuSprPosSet(temp_r28, (lbl_1_data_100[(temp_r30 * 4) + temp_r31] * 4) + 2, temp_r29[temp_r31], 0);
                    HuSprPosSet(temp_r28, (lbl_1_data_100[(temp_r30 * 4) + temp_r31] * 4) + 3, temp_r29[temp_r31], 38);
                }
            }
            else {
                if (temp_r30 < 0) {
                    temp_r30 = 2;
                }
                if (temp_r30 >= 3) {
                    temp_r30 = 0;
                }
                for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                    HuSprPosSet(temp_r28, lbl_1_data_110[(temp_r30 * 4) + temp_r31] * 4, temp_r29[temp_r31], 0);
                    HuSprPosSet(temp_r28, (lbl_1_data_110[(temp_r30 * 4) + temp_r31] * 4) + 2, temp_r29[temp_r31], 0);
                    HuSprPosSet(temp_r28, (lbl_1_data_110[(temp_r30 * 4) + temp_r31] * 4) + 3, temp_r29[temp_r31], 38);
                }
            }
            for (temp_r31 = 0; temp_r31 <= 5; temp_r31++) {
                temp_f30 = temp_r31 / 5.0;
                espPosSet(lbl_1_bss_2C2C[26], 108 - (10 * cosd(temp_f30 * 90.0f)), 20 + temp_f31);
                HuPrcVSleep();
            }
        }
        else if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
            HuAudFXPlay(772);
            for (temp_r31 = 0; temp_r31 <= 5; temp_r31++) {
                temp_f30 = temp_r31 / 5.0;
                espPosSet(lbl_1_bss_2C2C[25], 468 + (10 * sind(temp_f30 * 90.0f)), 20 + temp_f31);
                HuPrcVSleep();
            }
            temp_r30++;
            if (mgTypeCurr == 1) {
                if (temp_r30 < 0) {
                    temp_r30 = 3;
                }
                if (temp_r30 >= 4) {
                    temp_r30 = 0;
                }
                for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                    HuSprPosSet(temp_r28, lbl_1_data_100[(temp_r30 * 4) + temp_r31] * 4, temp_r29[temp_r31], 0);
                    HuSprPosSet(temp_r28, (lbl_1_data_100[(temp_r30 * 4) + temp_r31] * 4) + 2, temp_r29[temp_r31], 0);
                    HuSprPosSet(temp_r28, (lbl_1_data_100[(temp_r30 * 4) + temp_r31] * 4) + 3, temp_r29[temp_r31], 38);
                }
            }
            else {
                if (temp_r30 < 0) {
                    temp_r30 = 2;
                }
                if (temp_r30 >= 3) {
                    temp_r30 = 0;
                }
                for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                    HuSprPosSet(temp_r28, lbl_1_data_110[(temp_r30 * 4) + temp_r31] * 4, temp_r29[temp_r31], 0);
                    HuSprPosSet(temp_r28, (lbl_1_data_110[(temp_r30 * 4) + temp_r31] * 4) + 2, temp_r29[temp_r31], 0);
                    HuSprPosSet(temp_r28, (lbl_1_data_110[(temp_r30 * 4) + temp_r31] * 4) + 3, temp_r29[temp_r31], 38);
                }
            }
            for (temp_r31 = 0; temp_r31 <= 5; temp_r31++) {
                temp_f30 = temp_r31 / 5.0;
                espPosSet(lbl_1_bss_2C2C[25], 468 + (10 * cosd(temp_f30 * 90.0f)), 20 + temp_f31);
                HuPrcVSleep();
            }
        }
        if (HuPadBtnDown[0] & (PAD_BUTTON_A | PAD_BUTTON_START)) {
            break;
        }
    }
    HuAudFXPlay(773);
    if (mgTypeCurr == 1) {
        GWPlayerCfg[lbl_1_data_100[temp_r30 * 4]].group = 0;
        for (temp_r31 = 1; temp_r31 < 4; temp_r31++) {
            GWPlayerCfg[lbl_1_data_100[(temp_r30 * 4) + temp_r31]].group = 1;
        }
    }
    else {
        for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
            GWPlayerCfg[lbl_1_data_110[(temp_r30 * 4) + temp_r31]].group = 0;
        }
        for (temp_r31 = 2; temp_r31 < 4; temp_r31++) {
            GWPlayerCfg[lbl_1_data_110[(temp_r30 * 4) + temp_r31]].group = 1;
        }
    }
    if (arg0 != 0) {
        temp_r23 = 1;
    }
    else {
        return 1;
    }
loop_end:
    fn_1_25E74(temp_r24);
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        if (temp_r31 <= 10) {
            temp_f30 = temp_r31 / 10.0;
            temp_f31 = 240 + (20 * sind(temp_f30 * 90.0f));
            espPosSet(lbl_1_bss_2C2C[22], 288, temp_f31);
            espPosSet(lbl_1_bss_2C2C[24], 288, temp_f31 - 50);
            espPosSet(lbl_1_bss_2C2C[23], temp_f29, temp_f31 + 20);
            espPosSet(lbl_1_bss_2C2C[26], 108, temp_f31 + 20);
            espPosSet(lbl_1_bss_2C2C[25], 468, temp_f31 + 20);
            HuSprGrpPosSet(temp_r28, 288, temp_f31 + 20);
            HuSprGrpPosSet(temp_r25, 288, temp_f31);
        }
        else {
            temp_f30 = (temp_r31 - 10) / 20.0;
            temp_f31 = -300 + (560 * cosd(temp_f30 * 90.0f));
            espPosSet(lbl_1_bss_2C2C[22], 288, temp_f31);
            espPosSet(lbl_1_bss_2C2C[24], 288, temp_f31 - 50);
            espPosSet(lbl_1_bss_2C2C[23], temp_f29, temp_f31 + 20);
            espPosSet(lbl_1_bss_2C2C[26], 108, temp_f31 + 20);
            espPosSet(lbl_1_bss_2C2C[25], 468, temp_f31 + 20);
            HuSprGrpPosSet(temp_r28, 288, temp_f31 + 20);
            HuSprGrpPosSet(temp_r25, 288, temp_f31);
        }
        HuPrcVSleep();
    }
    HuSprGrpKill(temp_r28);
    HuSprGrpKill(temp_r25);
    return temp_r23;
}
