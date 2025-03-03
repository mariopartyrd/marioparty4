#include "REL/mgmodedll.h"
#include "game/gamework.h"

#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/saveload.h"
#include "game/wipe.h"

#include "ext_math.h"

void fn_1_DE3C(void);
void fn_1_DFB8(void);
void fn_1_E02C(float x, float y, s16 recordNo);

static s16 lbl_1_bss_37C[6];
static s16 lbl_1_bss_370[6];

s16 mgRecordIdxTbl[6][3] = { 0, 2, 13, 1, 0, 15, 2, 1, 35, 3, 2, 40, 5, 1, 51, 10, 1, 62 };

void fn_1_D8D0(void)
{
    s16 i;
    float weight;
    fn_1_DE3C();
    espAttrReset(lbl_1_bss_2C2C[3], HUSPR_ATTR_DISPOFF);
    espTPLvlSet(lbl_1_bss_2C2C[3], 0);
    for (i = 0; i <= 20; i++) {
        espTPLvlSet(lbl_1_bss_2C2C[3], i / 20.0);
        HuPrcVSleep();
    }
    for (i = 0; i <= 20; i++) {
        weight = i / 20.0;
        espAttrReset(lbl_1_bss_2C2C[27], HUSPR_ATTR_DISPOFF);
        espPosSet(lbl_1_bss_2C2C[27], 288, -100.0 + (164.0 * sind(weight * 90.0f)));
        espAttrReset(lbl_1_bss_2C2C[28], HUSPR_ATTR_DISPOFF);
        espTPLvlSet(lbl_1_bss_2C2C[28], weight);
        espAttrReset(lbl_1_bss_2C2C[20], HUSPR_ATTR_DISPOFF);
        espPosSet(lbl_1_bss_2C2C[20], ((1 - sind(weight * 90.0f)) * 400) + 288, 424);
        HuPrcVSleep();
    }
    for (i = 0; i < 6; i++) {
        fn_1_E02C(288, (i * 42) + 150.0f, i);
        HuPrcVSleep();
    }
    while (1) {
        if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            break;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(3);
    for (i = 0; i < 6; i++) {
        fn_1_E02C(1288, 0, i);
        HuPrcVSleep();
    }
    fn_1_DFB8();
    for (i = 0; i <= 20; i++) {
        weight = i / 20.0;
        espAttrReset(lbl_1_bss_2C2C[27], HUSPR_ATTR_DISPOFF);
        espPosSet(lbl_1_bss_2C2C[27], 288, -100.0 + (164.0 * cosd(weight * 90.0f)));
        espAttrReset(lbl_1_bss_2C2C[28], HUSPR_ATTR_DISPOFF);
        espTPLvlSet(lbl_1_bss_2C2C[28], 1.0 - weight);
        espAttrReset(lbl_1_bss_2C2C[20], HUSPR_ATTR_DISPOFF);
        espPosSet(lbl_1_bss_2C2C[20], ((1 - cosd(weight * 90.0f)) * 400) + 288, 424);
        HuPrcVSleep();
    }
    for (i = 0; i <= 10; i++) {
        espTPLvlSet(lbl_1_bss_2C2C[3], 1 - (i / 10.0));
        HuPrcVSleep();
    }
}

void fn_1_DE3C(void)
{
    AnimData *numAnim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGMODE, 53), MEMORY_DEFAULT_NUM));
    s16 i;
    for (i = 0; i < 6; i++) {
        s16 window = HuWinCreate(0, (i * 24), 268, 32, 0);
        s16 j;
        lbl_1_bss_37C[i] = window;
        HuWinBGTPLvlSet(window, 0);
        HuWinMesSpeedSet(window, 0);
        HuWinDispOff(window);
        lbl_1_bss_370[i] = HuSprGrpCreate(8);
        for (j = 0; j < 8; j++) {
            s16 sprite = HuSprCreate(numAnim, 10, 0);
            HuSprGrpMemberSet(lbl_1_bss_370[i], j, sprite);
            (void)sprite;
            HuSprAttrSet(lbl_1_bss_370[i], j, HUSPR_ATTR_DISPOFF);
        }
    }
}

void fn_1_DFB8(void)
{
    s16 i;
    for (i = 0; i < 6; i++) {
        HuWinKill(lbl_1_bss_37C[i]);
        HuSprGrpKill(lbl_1_bss_370[i]);
    }
}

void fn_1_E02C(float x, float y, s16 recordNo)
{
    s32 sprGrpId = lbl_1_bss_370[recordNo];
    s32 value = GWMGRecordGet(mgRecordIdxTbl[recordNo][0]);
    s32 i;
    s16 mgNo;
    float xOfs;

    if (mgRecordIdxTbl[recordNo][2] != -1) {
        mgNo = omMgIndexGet(mgRecordIdxTbl[recordNo][2]);
        if (!GWMGAvailGet(mgNo + 401)) {
            mgNo = -1;
        }
        else {
            HuWinMesSet(lbl_1_bss_37C[recordNo], mgInfoTbl[mgNo].name_mess);
        }
    }
    else {
        mgNo = -1;
    }
    HuWinDispOn(lbl_1_bss_37C[recordNo]);
    HuWinPosSet(lbl_1_bss_37C[recordNo], x - 220, y - 24);
    if (mgNo == -1) {
        HuWinMesSet(lbl_1_bss_37C[recordNo], MAKE_MESSID(35, 0));
        for (i = 0; i < 8; i++) {
            HuSprBankSet(sprGrpId, i, 0);
            HuSprPosSet(sprGrpId, i, i * 16, 0);
            HuSprAttrReset(sprGrpId, i, HUSPR_ATTR_DISPOFF);
        }
        xOfs = 128;
    }
    else {
        s32 memberNum;
        s32 digitValue;
        if (mgRecordIdxTbl[recordNo][1] == 0) {
            memberNum = 0;
            if (value > 9999) {
                value = 9999;
            }
            digitValue = value / 1000;
            if (digitValue != 0) {
                HuSprBankSet(sprGrpId, memberNum, digitValue);
                value -= digitValue * 1000;
                memberNum++;
            }
            digitValue = value / 100;
            if (digitValue != 0 || memberNum != 0) {
                HuSprBankSet(sprGrpId, memberNum, digitValue);
                value -= digitValue * 100;
                memberNum++;
            }
            digitValue = value / 10;
            if (digitValue != 0 || memberNum != 0) {
                HuSprBankSet(sprGrpId, memberNum, digitValue);
                value -= digitValue * 10;
                memberNum++;
            }
            HuSprBankSet(sprGrpId, memberNum, value);
            memberNum++;
            for (i = 0; i < 8; i++) {
                HuSprAttrSet(sprGrpId, i, HUSPR_ATTR_DISPOFF);
            }
            for (i = 0; i < memberNum; i++) {
                HuSprPosSet(sprGrpId, i, i * 16, 0);
                HuSprAttrReset(sprGrpId, i, HUSPR_ATTR_DISPOFF);
            }
            xOfs = memberNum * 16;
        }
        else {
            s16 yOfs[8];
            for (i = 0; i < 8; i++) {
                yOfs[i] = 0;
            }
            memberNum = 0;
            HuSprAttrSet(sprGrpId, memberNum, HUSPR_ATTR_DISPOFF);
            memberNum++;
            digitValue = value / 3600;
            HuSprBankSet(sprGrpId, memberNum, digitValue);
            value -= digitValue * 3600;
            memberNum++;
            HuSprBankSet(sprGrpId, memberNum, 11);
            yOfs[memberNum] = -2;
            memberNum++;
            digitValue = value / 600;
            HuSprBankSet(sprGrpId, memberNum, digitValue);
            value -= digitValue * 600;
            memberNum++;
            digitValue = value / 60;
            HuSprBankSet(sprGrpId, memberNum, digitValue);
            value -= digitValue * 60;
            memberNum++;
            HuSprBankSet(sprGrpId, memberNum, 12);
            yOfs[memberNum] = -2;
            memberNum++;
            if (mgRecordIdxTbl[recordNo][1] == 2) {
                value = (float)value * (203.0 / 120.0);
            }
            else {
                value = (float)value * (200.0 / 120.0);
            }
            digitValue = value / 10;
            HuSprBankSet(sprGrpId, memberNum, digitValue);
            value -= digitValue * 10;
            memberNum++;
            HuSprBankSet(sprGrpId, memberNum, value);
            memberNum++;
            for (i = 1; i < 8; i++) {
                HuSprAttrReset(sprGrpId, i, HUSPR_ATTR_DISPOFF);
            }
            for (i = 0; i < memberNum; i++) {
                HuSprPosSet(sprGrpId, i, i * 16, yOfs[i]);
            }
            xOfs = memberNum * 16;
        }
    }
    HuSprGrpPosSet(sprGrpId, 8 + ((210 + x) - xOfs), y);
}
