#include "dolphin/card.h"
#include "game/audio.h"
#include "game/card.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hu3d.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/saveload.h"
#include "game/window.h"
#include "game/wipe.h"

#include "ext_math.h"

#include "REL/modeseldll.h"

s32 msmSysGetOutputMode(void);

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/hsfex.h"
#endif

s16 fileSelectFxId = -1;
float fileSelectCameraViewTbl[] = { -55, 0, 0, 0, 60, -57, 806, -71, 0, 0, 0, 100, -131, 900, -87, 0, 0, 0, 46, -117, 566, -87, 0, 0, 0, 46, -117, 566, -90, 0,
    0, -22, 39, -153, 432, -40, 0, 0, 0, 130, -186, 6530, -23, 0, 0, -9, 1, -70, 1318, -25, 0, 0, 0, 242, 90, 343, -30, 0, 0, 0, 223, -60, 505, -23,
    0, 0, 0, 65, -97, 1318 };

s32 fileSelectCharAnimTbl[] = {
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x0D),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x0E),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x0F),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x10),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x11),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x12),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x13),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x14),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x15),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x16),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x17),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x18),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x19),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1A),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1B),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1C),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1D),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x1E),
};

char *fileSelectSlotIconTbl[] = { "\x0E\x16", "\x0E\x17" };

char *fileSelectSlotNameTbl[] = { "A", "B" };

char *fileSelectBoxNameTbl[] = { "1", "2", "3" };

s32 fileSelectCardBit;
s16 fileSelectWinId;
s16 fileSelectHelpWinId;
s16 fileSelectBoxPresentF[3];
s16 fileSelectBoxCharAnimId[3];
s16 fileSelectBoxCharBackAnimId[3];
s32 fileSelectSlotLabelF[2];
s32 fileSelectBoxLabelF[3];
s16 fileSelectSlotNo;
s16 fileSelectStarSprGrpId[3];
s16 fileSelectDateSprGrpId[3];
float fileSelectCardRotScale[2];
float fileSelectCardTiltScale[2];
ANIMDATA *fileSelectStarAnim;
ANIMDATA *fileSelectDigitAnim;
ANIMDATA *fileSelectStarMaxAnim;
s16 fileSelectBoxStars[3];
s16 fileSelectBoxCharNo[3];
OSTime fileSelectBoxCreateTime[3];
s32 fileSelectStoryContinueF[3];
s32 fileSelectPartyContinueF[3];
s32 fileSelectStoryClearF[3];
s16 fileSelectStoryBoardNo[3];
s16 fileSelectPartyBoardNo[3];
s16 fileSelectPartyTurn[3];
s16 fileSelectPartyMaxTurn[3];
s16 fileSelectCopySourceBox;
float fileSelectCardRot;
s16 fileSelectBoxNum;

s32 FileSelectCardExec(void);
void FileSelectCardInit(void);
s32 FileSelectBoxExec(void);
void FileSelectDisplayMain(void);

s32 FileSelectExec(void)
{
    s16 i;
    s16 result;
    WindowData *window;
    s16 fxstat;
    HUPROCESS *process = HuPrcCurrentGet();
    HUPROCESS *child;
    float winSize[2];
    for (i = 0; i < 3; i++) {
        fileSelectBoxCharAnimId[i] = fileSelectBoxCharBackAnimId[i] = -1;
        fileSelectStarSprGrpId[i] = -1;
        fileSelectDateSprGrpId[i] = -1;
    }
    fileSelectStarAnim = fileSelectDigitAnim = fileSelectStarMaxAnim = NULL;
    curSlotNo = 0;
    ModeSelCameraViewSet(0);
    FileSelectCardInit();
    child = HuPrcChildCreate(FileSelectDisplayMain, 10, 8192, 0, process);
    winSize[0] = 457;
    winSize[1] = 94;
    fileSelectWinId = HuWinExCreateStyled(-10000, 448 - winSize[1], winSize[0], winSize[1], -1, 0);
    window = &winData[fileSelectWinId];
    window->active_pad = 1;
    HuWinPushKeySet(fileSelectWinId, 0x300);
    HuWinMesSpeedSet(fileSelectWinId, 0);
    HuWinDispOn(fileSelectWinId);
    fxstat = HuAudFXPlay(2098);
    fileSelectFxId = fxstat;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuAudSeqPlay(43);
    while (1) {
        result = FileSelectCardExec();
        if (!result) {
            break;
        }
        if (!SLSaveFlagGet()) {
            GWGameStatReset();
            #if VERSION_PAL
            _ClearFlag(0x1000B);
            #endif
            GWGameStat.sound_mode = msmSysGetOutputMode();
            result = 1;
            break;
        }
        else {
            if (FileSelectBoxExec()) {
                break;
            }
        }
    }
    if (result == 0) {
        HuAudFXStop(fxstat);
    }
    HuWinExAnimOut(fileSelectWinId);
    HuWinExCleanup(fileSelectWinId);
    HuPrcKill(child);
    HuCardUnMount(0);
    HuCardUnMount(1);
    return result;
}

#define GET_ZEROSIGN(x) (((x) == 0) ? (-1) : (1))

s32 FileSelectCardErrorCheck(void);
void FileSelectModelMaterialReset(s16 mdlId);
void FileSelectCardAnimStart(s16 slotNo, s32 selectF);
s32 FileSelectCardCheck(void);
void FileSelectProgressWinOpen(u32 messId);
void FileSelectProgressWinClose(void);

s32 FileSelectCardExec(void)
{
    s16 slotNo;
    s16 frame;
    s32 errorF;
    s32 cardResult;
    s16 choice;
    s16 otherSlotNo;
    s16 formatChoice;
    s16 prevSlotNo;
    WindowData *window;
    float time;
    CARDFileInfo fileInfo;
    Vec screenPos;
    Vec pos;
    Vec targetPos;
    float helpWinSize[2];

    ModeSelCameraViewSet(0);
    window = &winData[fileSelectWinId];
    HuWinMesMaxSizeGet(1, helpWinSize, MAKE_MESSID(0x10, 0x0C));
    fileSelectHelpWinId = HuWinExCreateStyled(-10000.0f, 316.0f, helpWinSize[0], helpWinSize[1], -1, 0);
    HuWinBGTPLvlSet(fileSelectHelpWinId, 0);
    HuWinMesSpeedSet(fileSelectHelpWinId, 0);
repeat:
    screenPos.x = 188;
    screenPos.y = 250;
    screenPos.z = 600;
    Hu3D2Dto3D(&screenPos, 1, &pos);
    Hu3DModelPosSetV(modeSelMdlId[2], &pos);
    Hu3DModelPosSetV(modeSelMdlId[4], &pos);
    Hu3DModelPosSetV(modeSelMdlId[0], &pos);
    screenPos.x = 388;
    Hu3D2Dto3D(&screenPos, 1, &pos);
    Hu3DModelPosSetV(modeSelMdlId[3], &pos);
    Hu3DModelPosSetV(modeSelMdlId[5], &pos);
    Hu3DModelPosSetV(modeSelMdlId[1], &pos);
    Hu3DModelAttrReset(modeSelMdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(modeSelMdlId[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(modeSelMdlId[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(modeSelMdlId[5], HU3D_ATTR_DISPOFF);
    Hu3DModelRotSet(modeSelMdlId[2], 0, 0, 0);
    Hu3DModelRotSet(modeSelMdlId[3], 0, 0, 0);
    FileSelectModelMaterialReset(modeSelMdlId[4]);
    FileSelectModelMaterialReset(modeSelMdlId[5]);
    fileSelectSlotLabelF[0] = fileSelectSlotLabelF[1] = 1;
    fileSelectCardRotScale[0] = fileSelectCardRotScale[1] = fileSelectCardTiltScale[0] = fileSelectCardTiltScale[1] = 1.0f;
    fileSelectSlotNo = -1;
    FileSelectCardCheck();
    for (frame = 0; frame <= 20; frame++) {
        time = frame / 20.0;
        time = sind(90.0f * time);
        Hu3DModelScaleSet(modeSelMdlId[0], time, time, time);
        Hu3DModelScaleSet(modeSelMdlId[1], time, time, time);
        Hu3DModelScaleSet(modeSelMdlId[2], time, time, time);
        Hu3DModelScaleSet(modeSelMdlId[3], time, time, time);
        Hu3DModelScaleSet(modeSelMdlId[4], time, time, time);
        Hu3DModelScaleSet(modeSelMdlId[5], time, time, time);
        HuPrcVSleep();
    }
    while (1) {
    repeat_loop:
        HuWinDispOff(fileSelectHelpWinId);
        cardResult = FileSelectCardErrorCheck();
        if (cardResult == 0 && FileSelectCardCheck() == 0) {
            if (FileSelectCardCheck() == 0) {
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
                HuWinMesWait(fileSelectWinId);
            }
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4F));
            HuWinAttrSet(fileSelectWinId, 0x10);
            HuWinMesWait(fileSelectWinId);
            choice = HuWinChoiceGet(fileSelectWinId, 1);
            if (choice == 0) {
                SLSaveFlagSet(0);
                errorF = 1;
                goto cleanup;
            }
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x52), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4C));
            HuWinMesWait(fileSelectWinId);
            while (!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
                HuPrcVSleep();
            }
        }
        while (!FileSelectCardCheck()) {
            cardResult = FileSelectCardErrorCheck();
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
            HuWinMesWait(fileSelectWinId);
            if (window->key_down & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                return 0;
            }
            if (FileSelectCardCheck()) {
                break;
            }
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4B));
            HuWinAttrSet(fileSelectWinId, 0x10);
            HuWinMesWait(fileSelectWinId);
            choice = HuWinChoiceGet(fileSelectWinId, 1);
            if (choice == 0) {
                SLSaveFlagSet(0);
                errorF = 1;
                goto cleanup;
            }
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x52), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4C));
            HuWinMesWait(fileSelectWinId);
            while (!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
                HuPrcVSleep();
            }
        }
        SLSaveFlagSet(1);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x01));
        HuWinMesWait(fileSelectWinId);
        HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x0C));
        HuWinDispOn(fileSelectHelpWinId);
        if (curSlotNo == 0) {
            if (fileSelectCardBit & 0x1) {
                slotNo = 0;
            }
            else {
                slotNo = 1;
            }
        }
        else {
            if (fileSelectCardBit & 0x2) {
                slotNo = 1;
            }
            else {
                slotNo = 0;
            }
        }
        FileSelectCardAnimStart(slotNo, 1);
        HuPrcSleep(10);
        prevSlotNo = slotNo;
        while (1) {
            if (!FileSelectCardCheck()) {
                FileSelectCardAnimStart(slotNo, 0);
                HuPrcSleep(10);
                goto repeat_loop;
            }
            else {
                if ((HuPadDStkRep[0] & 0x1) && (fileSelectCardBit & 0x1)) {
                    slotNo = 0;
                }
                else if ((HuPadDStkRep[0] & 0x2) && (fileSelectCardBit & 0x2)) {
                    slotNo = 1;
                }
                else if (!(fileSelectCardBit & (1 << slotNo))) {
                    if (!(fileSelectCardBit & (1 << ((slotNo + 1) & 0x1)))) {
                        FileSelectCardAnimStart(slotNo, 0);
                        HuPrcSleep(10);
                        goto repeat_loop;
                    }
                    else {
                        slotNo = (slotNo + 1) & 0x1;
                    }
                }
                if (prevSlotNo != slotNo) {
                    HuAudFXPlay(0);
                    FileSelectCardAnimStart(slotNo, 1);
                    FileSelectCardAnimStart((slotNo + 1) & 0x1, 0);
                    HuPrcSleep(10);
                    prevSlotNo = slotNo;
                }
                if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                    HuAudFXPlay(2096);
                    goto loop_exit;
                }
                else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                    HuAudFXPlay(3);
                    return 0;
                }
            }
            HuPrcVSleep();
        }
    }
loop_exit:
    HuWinHomeClear(fileSelectWinId);
    otherSlotNo = (slotNo + 1) & 0x1;
    Hu3DMotionSet(modeSelMdlId[slotNo + 4], modeSelMotId[7]);
    Hu3DMotionSpeedSet(modeSelMdlId[slotNo + 4], 2.0f);
    fileSelectSlotLabelF[0] = fileSelectSlotLabelF[1] = 0;
    fileSelectSlotNo = slotNo;
    SLCurSlotNoSet(slotNo);
    cardResult = HuCardMount(slotNo);
    if (cardResult == CARD_RESULT_READY) {
        SLSerialNoGet();
        cardResult = HuCardOpen(slotNo, SaveFileNameTbl[0], &fileInfo);
        if (cardResult != 0 && cardResult != -4) {
            errorF = 1;
        }
        else {
            errorF = 0;
        }
        HuCardClose(&fileInfo);
    }
    else {
        if (cardResult == CARD_RESULT_NOCARD) {
            goto repeat;
        }
        errorF = 1;
    }
    choice = HuCardSectorSizeGet(curSlotNo);
    if (choice > 0 && choice != 8192) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x39));
        HuWinMesWait(fileSelectWinId);
        errorF = 1;
        goto skip_check;
    }
    else {
        if (choice == -128) {
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
            HuWinMesWait(fileSelectWinId);
            errorF = 1;
            goto skip_check;
        }
        else {
            fileSelectCardRot += 720.0f;
            for (frame = 0; frame <= 40; frame++) {
                if (frame <= 30) {
                    time = frame / 30.0f;
                    screenPos.x = 288.0 + (GET_ZEROSIGN(otherSlotNo) * (100.0 + (250.0 * sind(90.0f * time))));
                    screenPos.y = 250.0 - (100.0 * sind(180.0f * time));
                    screenPos.z = (frame * 100) + 600;
                    Hu3D2Dto3D(&screenPos, 1, &pos);
                    Hu3DModelPosSetV(modeSelMdlId[otherSlotNo + 2], &pos);
                    Hu3DModelPosSetV(modeSelMdlId[otherSlotNo], &pos);
                    Hu3DModelRotSet(modeSelMdlId[otherSlotNo + 2], frame * 20, frame * 10, 0);
                }

                if (frame > 20) {
                    time = (frame - 20) / 20.0f;
                    if (errorF) {
                        screenPos.x = 288.0f + ((1.0 - time) * (100 * GET_ZEROSIGN(slotNo)));
                        screenPos.y = 250.0 - (100.0 * sind(180.0f * time));
                        screenPos.z = 600.0f;
                        Hu3D2Dto3D(&screenPos, 1, &pos);
                        Hu3DModelPosSetV(modeSelMdlId[slotNo], &pos);
                        time = (0.5 * sind(90.0f * time)) + 1.0;
                        Hu3DModelScaleSet(modeSelMdlId[slotNo], time, time, time);
                    }
                    else {
                        screenPos.x = 288.0f + (100 * GET_ZEROSIGN(slotNo));
                        screenPos.y = 250;
                        screenPos.z = 600;
                        Hu3D2Dto3D(&screenPos, 1, &pos);
                        screenPos.x = 60;
                        screenPos.y = 90;
                        screenPos.z = 600;
                        Hu3D2Dto3D(&screenPos, 1, &targetPos);
                        VECSubtract(&targetPos, &pos, &screenPos);
                        screenPos.x *= sind(90.0f * time);
                        screenPos.y *= 1.0 - cosd(90.0f * time);
                        screenPos.z = 0;
                        VECAdd(&screenPos, &pos, &pos);
                        Hu3DModelPosSetV(modeSelMdlId[slotNo], &pos);
                        fileSelectCardRotScale[slotNo] *= cosd(90.0f * time);
                        fileSelectCardTiltScale[slotNo] = 1.0 - time;
                        time = 1.0 + (0.3 * cosd(90.0f * time));
                        Hu3DModelScaleSet(modeSelMdlId[slotNo], time, time, time);
                    }
                }
                HuPrcVSleep();
            }
            if (errorF == 0) {
                HuWinKill(fileSelectHelpWinId);
                return 1;
            }
            HuWinDispOff(fileSelectHelpWinId);
            errorF = 0;
            if (cardResult == CARD_RESULT_WRONGDEVICE) {
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[slotNo]), 0);
                #if VERSION_PAL
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x39));
                #else
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x37));
                #endif
                HuWinMesWait(fileSelectWinId);
                errorF = 1;
            }
            else if (cardResult == CARD_RESULT_FATAL_ERROR) {
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[slotNo]), 0);
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
                HuWinMesWait(fileSelectWinId);
                errorF = 1;
            }
            else if (cardResult == CARD_RESULT_NOCARD) {
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
                HuWinMesWait(fileSelectWinId);
                errorF = 1;
            }
            else if (cardResult == CARD_RESULT_BROKEN) {
                UnMountCnt = 0;
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[slotNo]), 0);
                HuWinAttrSet(fileSelectWinId, 0x10);
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x04));
                HuWinMesWait(fileSelectWinId);
                formatChoice = HuWinChoiceGet(fileSelectWinId, 1);
                if (formatChoice == 0) {
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4E));
                    HuWinMesWait(fileSelectWinId);
                    formatChoice = HuWinChoiceGet(fileSelectWinId, 1);
                    if (formatChoice == 0) {
                        FileSelectProgressWinOpen(MAKE_MESSID(16, 0x38));
                        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x0B));
                        HuWinMesWait(fileSelectWinId);
                        HuPrcSleep(60);
                        if (UnMountCnt & (1 << slotNo)) {
                            FileSelectProgressWinClose();
                            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x50));
                            HuWinMesWait(fileSelectWinId);
                            errorF = 1;
                            goto cleanup;
                        }
                        else {
                            _SetFlag(0x30000);
                            cardResult = HuCardFormat(slotNo);
                            _ClearFlag(FLAG_ID_MAKE(3, 0));
                            if (cardResult == CARD_RESULT_READY) {
                                SLSerialNoGet();
                            }
                            FileSelectProgressWinClose();
                            if (cardResult == CARD_RESULT_FATAL_ERROR) {
                                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x36));
                                HuWinMesWait(fileSelectWinId);
                                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
                                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
                                HuWinMesWait(fileSelectWinId);
                                errorF = 1;
                            }
                            else if (cardResult == CARD_RESULT_NOCARD) {
                                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
                                HuWinMesWait(fileSelectWinId);
                                errorF = 1;
                            }
                        }
                    }
                    else {
                        errorF = 1;
                    }
                }
                else {
                    errorF = 1;
                }
            }
        }
    }
    if (errorF == 0) {
        goto cleanup;
    }
skip_check:
    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4F));
    HuWinAttrSet(fileSelectWinId, 0x10);
    HuWinMesWait(fileSelectWinId);
    choice = HuWinChoiceGet(fileSelectWinId, 1);
    if (choice == 0) {
        SLSaveFlagSet(0);
        goto cleanup;
    }
    else {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x52), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4C));
        HuWinMesWait(fileSelectWinId);
        while (!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
            HuPrcVSleep();
        }
    }
cleanup:
    HuWinDispOff(fileSelectHelpWinId);
    fileSelectCardRot += 720.0f;
    for (frame = 0; frame <= 20; frame++) {
        time = frame / 20.0f;
        if (errorF) {
            time = 1.5 * cosd(90.0f * time);
            Hu3DModelScaleSet(modeSelMdlId[0], time, time, time);
            Hu3DModelScaleSet(modeSelMdlId[1], time, time, time);
            Hu3DModelScaleSet(modeSelMdlId[2], 0.7 * time, 0.7 * time, 0.7 * time);
            Hu3DModelScaleSet(modeSelMdlId[3], 0.7 * time, 0.7 * time, 0.7 * time);
            if (!SLSaveFlagGet()) {
                espScaleSet(modeSelSprId[1], time, time);
            }
        }
        else {
            screenPos.x = 288;
            screenPos.y = 250;
            screenPos.z = 600;
            Hu3D2Dto3D(&screenPos, 1, &pos);
            screenPos.x = 60;
            screenPos.y = 90;
            screenPos.z = 600;
            Hu3D2Dto3D(&screenPos, 1, &targetPos);
            VECSubtract(&targetPos, &pos, &screenPos);
            screenPos.x *= sind(90.0f * time);
            screenPos.y *= 1.0 - cosd(90.0f * time);
            screenPos.z = 0.0f;
            VECAdd(&screenPos, &pos, &pos);
            Hu3DModelPosSetV(modeSelMdlId[slotNo], &pos);
            fileSelectCardRotScale[slotNo] *= cosd(90.0f * time);
            fileSelectCardTiltScale[slotNo] = 1.0 - time;
            time = 1.0 + (0.5 * cosd(90.0f * time));
            Hu3DModelScaleSet(modeSelMdlId[slotNo], time, time, time);
        }
        HuPrcVSleep();
    }
    if (errorF && SLSaveFlagGet()) {
        goto repeat;
    }
    HuWinKill(fileSelectHelpWinId);
    return 1;
}

s32 FileSelectCardErrorCheck(void)
{
    s16 i;
    s16 result;
    s16 ret;
    ret = 1;
    for (i = 0; i < 2; i++) {
        result = HuCardSlotCheck((s32)i);
        if (result == -2) {
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[i]), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x37));
            HuWinMesWait(fileSelectWinId);
            ret = 0;
        }
        else if (result > 0 && result != 8192) {
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[i]), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x39));
            HuWinMesWait(fileSelectWinId);
            ret = 0;
        }
        else if (result == -128) {
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[i]), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
            HuWinMesWait(fileSelectWinId);
            ret = 0;
        }
    }
    return ret;
}

void FileSelectModelMaterialReset(s16 mdlId)
{
    HU3DMODEL *model = &Hu3DData[mdlId];
    HSFDATA *hsf = model->hsf;
    HSFMATERIAL *mat = hsf->material;
    s16 i;
    for (i = 0; i < hsf->materialNum; i++, mat++) {
        mat->invAlpha = 0.0f;
        mat->pass &= 0xF0;
    }
}

typedef struct file_select_anim_work {
    s16 index;
    s32 selectF;
} FileSelectAnimWork;

void FileSelectCardAnimMain(void)
{
    s16 index;
    FileSelectAnimWork *work;
    s16 i;
    s32 selectF;
    HUPROCESS *curr;
    curr = HuPrcCurrentGet();
    work = curr->user_data;
    index = work->index;
    selectF = work->selectF;
    Hu3DModelAttrSet(modeSelMdlId[index + 2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(modeSelMdlId[index + 4], HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(modeSelMdlId[index + 4], modeSelMotId[6]);
    Hu3DMotionSpeedSet(modeSelMdlId[index + 4], 2.0f);
    if (selectF) {
        Hu3DModelAttrReset(modeSelMdlId[index + 4], HU3D_MOTATTR_REV);
    }
    else {
        Hu3DModelAttrSet(modeSelMdlId[index + 4], HU3D_MOTATTR_REV);
        Hu3DMotionTimeSet(modeSelMdlId[index + 4], Hu3DMotionMaxTimeGet(modeSelMdlId[6]));
    }
    for (i = 0; i < 10; i++) {
        float scale;
        float time = i / 10.0;
        if (selectF) {
            scale = 1.0 + (0.3 * sind(90.0f * time));
        }
        else {
            scale = 1.0 + (0.3 * cosd(90.0f * time));
        }
        Hu3DModelScaleSet(modeSelMdlId[index + 2], scale, scale, scale);
        Hu3DModelScaleSet(modeSelMdlId[index + 4], scale, scale, scale);
        Hu3DModelScaleSet(modeSelMdlId[index], scale, scale, scale);
        HuPrcVSleep();
    }
    if (!selectF) {
        Hu3DModelAttrReset(modeSelMdlId[index + 2], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(modeSelMdlId[index + 4], HU3D_ATTR_DISPOFF);
    }
    HuMemDirectFree(work);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void FileSelectCardAnimStart(s16 slotNo, s32 selectF)
{
    FileSelectAnimWork *work;
    HUPROCESS *child;
    HUPROCESS *parent;
    parent = HuPrcCurrentGet();
    child = HuPrcChildCreate(FileSelectCardAnimMain, 50, 8192, 0, parent);
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(FileSelectAnimWork), HU_MEMNUM_OVL);
    child->user_data = work;
    work->index = slotNo;
    work->selectF = selectF;
}

s32 FileSelectCardCheck(void)
{
    s32 result;
    fileSelectCardBit = 0;
    result = HuCardSlotCheck(0);
    if (result == 8192) {
        Hu3DModelAttrReset(modeSelMdlId[0], HU3D_ATTR_DISPOFF);
        fileSelectCardBit |= 1;
    }
    else {
        Hu3DModelAttrSet(modeSelMdlId[0], HU3D_ATTR_DISPOFF);
    }
    result = HuCardSlotCheck(1);
    if (result == 8192) {
        Hu3DModelAttrReset(modeSelMdlId[1], HU3D_ATTR_DISPOFF);
        fileSelectCardBit |= 2;
    }
    else {
        Hu3DModelAttrSet(modeSelMdlId[1], HU3D_ATTR_DISPOFF);
    }
    return fileSelectCardBit;
}

void FileSelectCardInit(void)
{
    HU3DMODEL *model;
    Vec pos_2d;
    Vec pos_3d;
    Mtx scale;
    espAttrReset(modeSelSprId[0], HUSPR_ATTR_DISPOFF);
    espDrawNoSet(modeSelSprId[0], 127);
    espAttrReset(modeSelSprId[1], HUSPR_ATTR_DISPOFF);
    Hu3DModelAttrReset(modeSelMdlId[2], HU3D_ATTR_DISPOFF);
    pos_2d.x = 188;
    pos_2d.y = 250;
    pos_2d.z = 600;
    Hu3D2Dto3D(&pos_2d, 1, &pos_3d);
    Hu3DModelPosSetV(modeSelMdlId[2], &pos_3d);
    Hu3DModelPosSetV(modeSelMdlId[4], &pos_3d);
    Hu3DModelPosSetV(modeSelMdlId[0], &pos_3d);
    MTXScale(scale, 0.5f, 0.5f, 0.5f);
    model = &Hu3DData[modeSelMdlId[2]];
    MTXCopy(scale, model->mtx);
    model = &Hu3DData[modeSelMdlId[4]];
    MTXCopy(scale, model->mtx);
    model = &Hu3DData[modeSelMdlId[0]];
    MTXCopy(scale, model->mtx);
    Hu3DModelAttrReset(modeSelMdlId[3], HU3D_ATTR_DISPOFF);
    pos_2d.x = 388;
    Hu3D2Dto3D(&pos_2d, 1, &pos_3d);
    Hu3DModelPosSetV(modeSelMdlId[3], &pos_3d);
    Hu3DModelPosSetV(modeSelMdlId[5], &pos_3d);
    Hu3DModelPosSetV(modeSelMdlId[1], &pos_3d);
    model = &Hu3DData[modeSelMdlId[3]];
    MTXCopy(scale, model->mtx);
    model = &Hu3DData[modeSelMdlId[5]];
    MTXCopy(scale, model->mtx);
    model = &Hu3DData[modeSelMdlId[1]];
    MTXCopy(scale, model->mtx);
    Hu3DModelScaleSet(modeSelMdlId[0], 0, 0, 0);
    Hu3DModelScaleSet(modeSelMdlId[1], 0, 0, 0);
    Hu3DModelScaleSet(modeSelMdlId[2], 0, 0, 0);
    Hu3DModelScaleSet(modeSelMdlId[3], 0, 0, 0);
    Hu3DModelScaleSet(modeSelMdlId[4], 0, 0, 0);
    Hu3DModelScaleSet(modeSelMdlId[5], 0, 0, 0);
    FileSelectCardCheck();
}

void FileSelectBoxAnimStart(s16 boxno, s32 flag);

s32 FileSelectFileOpen(char *name, s16 slotno);
s32 FileSelectFileCreate(s16 boxno);
s32 FileSelectFileWrite(void);
s32 FileSelectFileRead(void);
s32 FileSelectFileDelete(s16 boxno);
s32 FileSelectFileCopy(s16 boxno);
s32 FileSelectFileClose(void);
s32 FileSelectBoxInit(void);

void FileSelectBoxInfoLoad(s16 boxno);
void FileSelectBoxInfoSet(s16 boxno);

s32 FileSelectBoxExec(void)
{
    float scale;
    s16 result;
    s16 boxNo;
    s16 i;
    s16 modelNo;
    s32 cardResult;
    s16 move;
    float helpWinSize[2];
    OSTime createTime;
    HuWinMesMaxSizeGet(1, helpWinSize, MAKE_MESSID(0x10, 0x3D));
    fileSelectHelpWinId = HuWinExCreateStyled(-10000, 316, helpWinSize[0], helpWinSize[1], -1, 0);
    HuWinAttrSet(fileSelectHelpWinId, 0x800);
    HuWinBGTPLvlSet(fileSelectHelpWinId, 0);
    HuWinMesSpeedSet(fileSelectHelpWinId, 0);
    boxNo = -1;
    for (i = fileSelectBoxNum = 0; i < 3; i++) {
        fileSelectBoxStars[i] = -1;
        fileSelectBoxCharNo[i] = -1;
        fileSelectBoxPresentF[i] = 0;
        cardResult = FileSelectFileOpen(SaveFileNameTbl[i], curSlotNo);
        if (cardResult == 0) {
            cardResult = FileSelectFileRead();
            if (cardResult == 0) {
                fileSelectBoxPresentF[i] = 1;
                if (fileSelectBoxNum == 0) {
                    boxNo = i;
                }
                fileSelectBoxNum++;
                if (SLCheckSumCheck()) {
                    FileSelectBoxInfoLoad(i);
                }
            }
            FileSelectFileClose();
        }
        if (cardResult != 0 && cardResult != -4) {
            HuWinKill(fileSelectHelpWinId);
            return 0;
        }
    }
    FileSelectBoxInit();
    if (boxNo == -1) {
        boxNo = 0;
    }
    fileSelectBoxLabelF[0] = fileSelectBoxLabelF[1] = fileSelectBoxLabelF[2] = 1;
    UnMountCnt = 0;
    for (i = 0; i <= 20; i++) {
        scale = sind(90.0f * (i / 20.0f));
        for (modelNo = 0; modelNo < 3; modelNo++) {
            Hu3DModelScaleSet(modeSelMdlId[modelNo + 8], scale, scale, scale);
            Hu3DModelScaleSet(modeSelMdlId[modelNo + 11], scale, scale, scale);
        }
        HuPrcVSleep();
    }
    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x07));
    HuWinMesWait(fileSelectWinId);
    FileSelectBoxAnimStart(boxNo, 1);
    if (fileSelectBoxNum == 0) {
        HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x40));
    }
    else {
        if (fileSelectBoxNum == 3) {
            HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x3F));
        }
        else {
            HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x3D));
        }
    }
    HuWinDispOn(fileSelectHelpWinId);
    FileSelectBoxInfoSet(boxNo);
    if (UnMountCnt & (1 << curSlotNo)) {
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x50));
        HuWinMesWait(fileSelectWinId);
        result = 0;
    }
    else {
        UnMountCnt = 0;
        while (1) {
            HuPrcVSleep();
            if (UnMountCnt & (1 << curSlotNo)) {
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x50));
                HuWinMesWait(fileSelectWinId);
                result = 0;
                break;
            }
            move = 0;
            if (HuPadDStkRep[0] & 0x1) {
                move = -1;
            }
            else if (HuPadDStkRep[0] & 0x2) {
                move = 1;
            }
            if (move) {
                FileSelectBoxAnimStart(boxNo, 0);
                boxNo += move;
                if (boxNo < 0) {
                    boxNo = 2;
                }
                else if (boxNo >= 3) {
                    boxNo = 0;
                }
                HuAudFXPlay(0);
                FileSelectBoxAnimStart(boxNo, 1);
                FileSelectBoxInfoSet(boxNo);
                HuPrcSleep(10);
            }
            if ((HuPadBtnDown[0] & PAD_BUTTON_X) && fileSelectBoxPresentF[boxNo]) {
                UnMountCnt = 0;
                result = FileSelectFileOpen(SaveFileNameTbl[boxNo], curSlotNo);
                if (result < 0) {
                    result = 0;
                    break;
                }
                if (!fileSelectBoxPresentF[boxNo]) {
                    continue;
                }
                HuWinDispOff(fileSelectHelpWinId);
                HuAudFXPlay(2);
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectBoxNameTbl[boxNo]), 1);
                HuWinAttrSet(fileSelectWinId, 0x10);
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x08));
                HuWinMesWait(fileSelectWinId);
                result = HuWinChoiceGet(fileSelectWinId, 1);
                if (result == 0) {
                    result = FileSelectFileDelete(boxNo);
                    if (result == 0) {
                        break;
                    }
                }
                if (UnMountCnt & (1 << curSlotNo)) {
                    continue;
                }
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x07));
                HuWinMesWait(fileSelectWinId);
                if (fileSelectBoxNum == 0) {
                    HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x40));
                }
                else if (fileSelectBoxNum == 3) {
                    HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x3F));
                }
                else {
                    HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x3D));
                }
                HuWinDispOn(fileSelectHelpWinId);
                FileSelectBoxInfoSet(boxNo);
                continue;
            }
            else if (HuPadBtnDown[0] & PAD_BUTTON_Y) {
                UnMountCnt = 0;
                if (HuCardSlotCheck(curSlotNo) < 0) {
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
                    HuWinMesWait(fileSelectWinId);
                    result = 0;
                    break;
                }
                if (!fileSelectBoxPresentF[boxNo]) {
                    continue;
                }
                for (i = 0; i < 3; i++) {
                    if (!fileSelectBoxPresentF[i]) {
                        break;
                    }
                }
                if (i == 3) {
                    continue;
                }
                HuWinDispOff(fileSelectHelpWinId);
                HuAudFXPlay(2);
                if (FileSelectFileCopy(boxNo) == 0) {
                    result = 0;
                    break;
                }
                if (UnMountCnt & (1 << curSlotNo)) {
                    continue;
                }
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x07));
                HuWinMesWait(fileSelectWinId);
                if (fileSelectBoxNum == 0) {
                    HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x40));
                }
                else if (fileSelectBoxNum == 3) {
                    HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x3F));
                }
                else {
                    HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x3D));
                }
                HuWinDispOn(fileSelectHelpWinId);
                FileSelectBoxInfoSet(boxNo);
                continue;
            }
            else if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                UnMountCnt = 0;
                HuWinDispOff(fileSelectHelpWinId);
                HuCardMount(curSlotNo);
                if (HuCardSlotCheck(curSlotNo) < 0) {
                    HuAudFXPlay(4);
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
                    HuWinMesWait(fileSelectWinId);
                    result = 0;
                    break;
                }
                if (SLSerialNoCheck() == 0) {
                    HuAudFXPlay(4);
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x45));
                    HuWinMesWait(fileSelectWinId);
                    result = 0;
                    break;
                }
                HuAudFXPlay(2097);
                SLCurBoxNoSet(boxNo);
                if (!fileSelectBoxPresentF[boxNo]) {
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x0B));
                    HuWinMesWait(fileSelectWinId);
                    createTime = OSGetTime();
                    SLSaveDataMake(1, &createTime);
                    GWGameStatReset();
                    #if VERSION_PAL
                    _ClearFlag(0x1000B);
                    #endif
                    GWGameStat.sound_mode = msmSysGetOutputMode();
                    SLCommonSet();
                    FileSelectProgressWinOpen(MAKE_MESSID(16, 0x3C));
                    HuPrcSleep(20);
                    if (UnMountCnt & (1 << curSlotNo)) {
                        FileSelectProgressWinClose();
                        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x50));
                        HuWinMesWait(fileSelectWinId);
                        result = 0;
                        break;
                    }
                    cardResult = FileSelectFileCreate(boxNo);
                    FileSelectProgressWinClose();
                    if (cardResult != 0) {
                        result = 1;
                        break;
                    }
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4F));
                    HuWinAttrSet(fileSelectWinId, 0x10);
                    HuWinMesWait(fileSelectWinId);
                    result = HuWinChoiceGet(fileSelectWinId, 1);
                    if (result == 0) {
                        SLSaveFlagSet(0);
                        result = 1;
                        break;
                    }
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x52), 0);
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4C));
                    HuWinMesWait(fileSelectWinId);
                    while (!(HuPadBtnDown[0] & PAD_BUTTON_A)) {
                        HuPrcVSleep();
                    }
                    result = 0;
                    break;
                }
                else {
                    if (!FileSelectFileOpen(SaveFileNameTbl[boxNo], curSlotNo)) {
                        if (!FileSelectFileRead()) {
                            if (SLCheckSumCheck()) {
                                FileSelectFileClose();
                                SLLoadGameStat();
                                #if VERSION_PAL
                                if(GwLanguageSave != -1) {
                                    GWGameStat.language = GwLanguageSave;
                                }
                                GwLanguage = GWGameStat.language;
                                _ClearFlag(0x1000B);
                                #endif
                                result = 1;
                                break;
                            }
                            HuWinHomeClear(fileSelectWinId);
                            HuPrcSleep(60);
                            if (UnMountCnt & (1 << curSlotNo)) {
                                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x50));
                                HuWinMesWait(fileSelectWinId);
                                result = 0;
                                break;
                            }
                            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectBoxNameTbl[boxNo]), 0);
                            HuWinAttrSet(fileSelectWinId, 0x10);
                            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x3A));
                            HuWinMesWait(fileSelectWinId);
                            result = HuWinChoiceGet(fileSelectWinId, 1);
                            if (!result) {
                                result = FileSelectFileDelete(boxNo);
                                if (result == 0) {
                                    break;
                                }
                                if (HuCardMount(curSlotNo) < 0) {
                                    result = 0;
                                    break;
                                }
                            }
                        }
                        else {
                            result = 0;
                        }
                    }
                    else {
                        result = 0;
                    }
                    if (result == 0) {
                        break;
                    }
                    if (UnMountCnt & (1 << curSlotNo)) {
                        continue;
                    }
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x07));
                    HuWinMesWait(fileSelectWinId);
                    if (fileSelectBoxNum == 0) {
                        HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x40));
                    }
                    else if (fileSelectBoxNum == 3) {
                        HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x3F));
                    }
                    else {
                        HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x3D));
                    }
                    HuWinDispOn(fileSelectHelpWinId);
                    FileSelectBoxInfoSet(boxNo);
                    continue;
                }
            }
            else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                result = 0;
                break;
            }
        }
    }
    HuWinDispOff(fileSelectHelpWinId);
    for (i = 0; i <= 20; i++) {
        scale = cosd(90.0 * (i / 20.0));
        Hu3DModelScaleSet(modeSelMdlId[curSlotNo], scale, scale, scale);
        for (modelNo = 0; modelNo < 3; modelNo++) {
            Hu3DModelScaleSet(modeSelMdlId[modelNo + 8], scale, scale, scale);
            Hu3DModelScaleSet(modeSelMdlId[modelNo + 11], scale, scale, scale);
        }
        if (result) {
            espScaleSet(modeSelSprId[1], scale, scale);
        }
        HuPrcVSleep();
    }
    HuWinKill(fileSelectHelpWinId);
    return result;
}

void FileSelectBoxAnimMain(void)
{
    s16 index;
    FileSelectAnimWork *work;
    s16 i;
    s32 selectF;
    HUPROCESS *curr;
    curr = HuPrcCurrentGet();
    work = curr->user_data;
    index = work->index;
    selectF = work->selectF;
    if (selectF) {
        Hu3DModelAttrReset(modeSelMdlId[index + 8], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(modeSelMdlId[index + 11], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(modeSelMdlId[index + 8], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(modeSelMdlId[index + 11], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i <= 10; i++) {
        float scale;
        Vec pos_2d;
        Vec pos_3d;
        if (selectF) {
            scale = sind(90.0f * (i / 10.0f));
        }
        else {
            scale = cosd(90.0f * (i / 10.0f));
        }
        pos_2d.x = 158.0f + (index * 130);
        pos_2d.y = 230;
        pos_2d.z = 800;
        Hu3D2Dto3D(&pos_2d, 1, &pos_3d);
        pos_3d.z = 800 + (100.0f * scale);
        Hu3DModelPosSetV(modeSelMdlId[index + 8], &pos_3d);
        Hu3DModelPosSetV(modeSelMdlId[index + 11], &pos_3d);
        Hu3DModelScaleSet(modeSelMdlId[index + 8], 1, 1, 1);
        Hu3DModelScaleSet(modeSelMdlId[index + 11], 1, 1, 1);
        HuPrcVSleep();
    }
    (void)curr;
    HuMemDirectFree(work);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void FileSelectBoxAnimStart(s16 boxno, s32 flag)
{
    FileSelectAnimWork *work;
    HUPROCESS *parent;
    HUPROCESS *child;

    parent = HuPrcCurrentGet();
    child = HuPrcChildCreate(FileSelectBoxAnimMain, 50, 8192, 0, parent);
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(FileSelectAnimWork), HU_MEMNUM_OVL);
    child->user_data = work;
    work->index = boxno;
    work->selectF = flag;
}

s32 FileSelectFileOpen(char *name, s16 slotno)
{
    s32 result;
    s16 choice;
    s16 filecnt;
    filecnt = 0;
    while (1) {
        filecnt++;
        result = HuCardMount(slotno);
        if (result == CARD_RESULT_READY) {
            result = HuCardOpen(slotno, name, &curFileInfo);
            if (result == CARD_RESULT_READY || result == CARD_RESULT_NOFILE) {
                if (SLSerialNoCheck()) {
                    return result;
                }
            }
        }
        if (result == CARD_RESULT_WRONGDEVICE) {
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[slotno]), 0);
            #if VERSION_PAL
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x39));
            #else
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x37));
            #endif
            HuWinMesWait(fileSelectWinId);
            return result;
        }
        if (result == CARD_RESULT_FATAL_ERROR || filecnt > 3) {
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[slotno]), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
            HuWinMesWait(fileSelectWinId);
            return result;
        }
        else if (result == CARD_RESULT_NOCARD) {
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
            HuWinMesWait(fileSelectWinId);
            return result;
        }
        else if (result == CARD_RESULT_NOFILE || !SLSerialNoCheck()) {
            OSReport("Card Open Error:No File\n");
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x45));
            HuWinMesWait(fileSelectWinId);
            break;
        }
        else if (result == CARD_RESULT_BROKEN) {
            UnMountCnt = 0;
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[slotno]), 0);
            HuWinAttrSet(fileSelectWinId, 0x10);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x04));
            HuWinMesWait(fileSelectWinId);
            choice = HuWinChoiceGet(fileSelectWinId, 1);
            if (choice == 0) {
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4E));
                HuWinMesWait(fileSelectWinId);
                choice = HuWinChoiceGet(fileSelectWinId, 1);
                if (choice == 0) {
                    FileSelectProgressWinOpen(MAKE_MESSID(16, 0x38));
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x0B));
                    HuWinMesWait(fileSelectWinId);
                    HuPrcSleep(60);
                    if (UnMountCnt & (1 << curSlotNo)) {
                        FileSelectProgressWinClose();
                        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x50));
                        HuWinMesWait(fileSelectWinId);
                    }
                    else {
                        _SetFlag(0x30000);
                        result = HuCardFormat(slotno);
                        _ClearFlag(0x30000);
                        if (result == CARD_RESULT_READY) {
                            SLSerialNoGet();
                        }
                        FileSelectProgressWinClose();
                        if (result == CARD_RESULT_FATAL_ERROR) {
                            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x36));
                            HuWinMesWait(fileSelectWinId);
                            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
                            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
                            HuWinMesWait(fileSelectWinId);
                            return result;
                        }
                        else if (result == CARD_RESULT_NOCARD) {
                            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
                            HuWinMesWait(fileSelectWinId);
                            return result;
                        }
                    }
                }
                else {
                    return result;
                }
                continue;
            }
            return result;
        }
        break;
    }
    return result;
}

s32 FileSelectFileCreate(s16 boxno)
{
    s32 result;
    s32 i;
    result = HuCardMount(curSlotNo);
    if (result == 0 && !SLSerialNoCheck()) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x45));
        HuWinMesWait(fileSelectWinId);
    }
    else {
        result = HuCardSectorSizeGet(curSlotNo);
        if (result == -3) {
            FileSelectProgressWinClose();
            OSReport("SectorSize Check Error:No Card %d\n", curSlotNo);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
            HuWinMesWait(fileSelectWinId);
        }
        else {
            if (result != 8192) {
                FileSelectProgressWinClose();
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x39));
                HuWinMesWait(fileSelectWinId);
            }
            else {
                u32 byteNotUsed;
                u32 filesNotUsed;
                result = HuCardFreeSpaceGet(curSlotNo, &byteNotUsed, &filesNotUsed);
                if (filesNotUsed == 0 && byteNotUsed < SAVE_BUF_SIZE) {
                    FileSelectProgressWinClose();
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4A));
                    HuWinMesWait(fileSelectWinId);
                }
                else if (filesNotUsed == 0) {
                    FileSelectProgressWinClose();
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4A));
                    HuWinMesWait(fileSelectWinId);
                }
                else if (byteNotUsed < SAVE_BUF_SIZE) {
                    FileSelectProgressWinClose();
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4A));
                    HuWinMesWait(fileSelectWinId);
                }
                else {
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x0B));
                    HuWinMesWait(fileSelectWinId);
                    for (i = 0; i <= 40; i++) {
                        float time = i / 40.0;
                        Hu3DModelTPLvlSet(modeSelMdlId[boxno + 8], 0.6 + (0.4 * time));
                        Hu3DModelTPLvlSet(modeSelMdlId[boxno + 11], 0.3 + (0.7 * time));
                        HuPrcVSleep();
                    }
                    _SetFlag(0x30000);
                    result = HuCardCreate(curSlotNo, SaveFileNameTbl[boxno], SAVE_BUF_SIZE, &curFileInfo);
                    if (result == CARD_RESULT_NOCARD) {
                        _ClearFlag(0x30000);
                        FileSelectProgressWinClose();
                        OSReport("File Create Error:No Card\n");
                        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
                        HuWinMesWait(fileSelectWinId);
                    }
                    else if (result == CARD_RESULT_WRONGDEVICE) {
                        _ClearFlag(0x30000);
                        FileSelectProgressWinClose();
                        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
                        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x37));
                        HuWinMesWait(fileSelectWinId);
                    }
                    else if (result < 0) {
                        _ClearFlag(0x30000);
                        FileSelectProgressWinClose();
                        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
                        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
                        HuWinMesWait(fileSelectWinId);
                    }
                    else {
                        result = FileSelectFileWrite();
                        _ClearFlag(0x30000);
                        if (result != 0) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

s32 FileSelectFileWrite(void)
{
    s32 result;
    SLCheckSumSet();
    _SetFlag(0x30000);
    result = HuCardWrite(&curFileInfo, &saveBuf.buf[0], SAVE_BUF_SIZE, 0);
    _ClearFlag(0x30000);
    if (result == CARD_RESULT_NOCARD) {
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    if (result == CARD_RESULT_WRONGDEVICE) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x37));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    if (result < 0) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    result = SLStatSet(0);
    if (result == CARD_RESULT_NOCARD) {
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    if (result == CARD_RESULT_WRONGDEVICE) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x37));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    if (result < 0) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    return 1;
}

s32 FileSelectFileRead(void)
{
    s32 result;
    result = HuCardRead(&curFileInfo, &saveBuf.buf[0], SAVE_BUF_SIZE, 0);
    if (result == -3) {
        OSReport("Card Read Error:No Card\n");
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
        HuWinMesWait(fileSelectWinId);
    }
    else if (result == -4 || !SLSerialNoCheck()) {
        OSReport("Card Read Error:No File\n", result);
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x45));
        HuWinMesWait(fileSelectWinId);
    }
    else if (result < 0) {
        OSReport("Card Read Error:Fatal Error %d\n", result);
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
        HuWinMesWait(fileSelectWinId);
    }
    return result;
}

s32 FileSelectFileDelete(s16 boxno)
{
    float scale;
    s32 result;
    s32 time;
    ANIMDATA *sprite;
    result = HuCardMount(curSlotNo);
    if (result == -3) {
        OSReport("Card Delete Error:No Card\n");
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    if (result == -4 || !SLSerialNoCheck()) {
        OSReport("Card Delete Error:No File\n", result);
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x45));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    if (result < 0) {
        OSReport("Card Delete Error:Fatal Error %d\n", result);
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }

    FileSelectProgressWinOpen(MAKE_MESSID(16, 0x3B));
    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x0B));
    HuWinMesWait(fileSelectWinId);
    HuPrcSleep(60);
    if (UnMountCnt & (1 << curSlotNo)) {
        FileSelectProgressWinClose();
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x50));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    else {
        _SetFlag(0x30000);
        result = HuCardDelete(curSlotNo, SaveFileNameTbl[boxno]);
        _ClearFlag(0x30000);
        FileSelectProgressWinClose();
        if (result == -3) {
            OSReport("Card Delete Error:No Card\n");
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x02));
            HuWinMesWait(fileSelectWinId);
            return 0;
        }
        if (result == -4 || !SLSerialNoCheck()) {
            OSReport("Card Delete Error:No File\n", result);
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x45));
            HuWinMesWait(fileSelectWinId);
            return 0;
        }
        if (result < 0) {
            OSReport("Card Delete Error:Fatal Error %d\n", result);
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x53));
            HuWinMesWait(fileSelectWinId);
            return 0;
        }
        for (time = 0; time <= 10; time++) {
            scale = cosd(90.0 * (time / 10.0));
            Hu3DModelScaleSet(modeSelMdlId[boxno + 8], scale, scale, scale);
            HuPrcVSleep();
        }
        Hu3DAnimKill(fileSelectBoxCharAnimId[boxno]);
        Hu3DAnimKill(fileSelectBoxCharBackAnimId[boxno]);
        sprite = HuSprAnimRead(HuDataReadNum(fileSelectCharAnimTbl[8], HU_MEMNUM_OVL));
        fileSelectBoxCharAnimId[boxno] = Hu3DAnimCreate(sprite, modeSelMdlId[boxno + 8], "star");
        sprite = HuSprAnimRead(HuDataReadNum(fileSelectCharAnimTbl[17], HU_MEMNUM_OVL));
        fileSelectBoxCharBackAnimId[boxno] = Hu3DAnimCreate(sprite, modeSelMdlId[boxno + 11], "star");
        fileSelectBoxStars[boxno] = -1;
        Hu3DModelTPLvlSet(modeSelMdlId[boxno + 8], 0.6f);
        Hu3DModelTPLvlSet(modeSelMdlId[boxno + 11], 0.3f);
        for (time = 0; time <= 20; time++) {
            scale = sind(90.0 * (time / 20.0));
            Hu3DModelScaleSet(modeSelMdlId[boxno + 8], scale, scale, scale);
            HuPrcVSleep();
        }
        fileSelectBoxPresentF[boxno] = 0;
        fileSelectBoxNum--;
        return 1;
    }
}

s32 FileSelectFileCopy(s16 boxno)
{
    float time;
    s16 destBoxNo;
    s16 i;
    s32 result;
    s16 move;
    s16 charNo;
    ANIMDATA *charAnim;
    Vec screenPos;
    Vec srcPos;
    Vec destPos;
    Vec delta;
    s32 freeFiles;
    s32 freeBytes;
    HUPROCESS *process;
    HU3DMODEL *model;
    process = HuPrcCurrentGet();
    OSReport("Card Copy Seq.:Open\n");
    result = FileSelectFileOpen(SaveFileNameTbl[boxno], curSlotNo);
    if (result < 0 || !SLSerialNoCheck()) {
        return 0;
    }
    OSReport("Card Copy Seq.:Read\n");
    result = FileSelectFileRead();
    if (result != 0) {
        return 0;
    }
    OSReport("Card Copy Seq.:CheckSum Check\n");
    if (!SLCheckSumCheck()) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectBoxNameTbl[boxno]), 0);
        HuWinAttrSet(fileSelectWinId, 0x10);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x3A));
        HuWinMesWait(fileSelectWinId);
        result = HuWinChoiceGet(fileSelectWinId, 1);
        if (result != 0) {
            return 1;
        }
        else {
            result = FileSelectFileDelete(boxno);
            return result;
        }
    }
    if (!SLSerialNoCheck()) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x45));
        HuWinMesWait(fileSelectWinId);
        return 0;
    }
    result = HuCardFreeSpaceGet(curSlotNo, (u32 *)&freeBytes, (u32 *)&freeFiles);
    if (freeFiles == 0 && freeBytes < SAVE_BUF_SIZE) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4A));
        HuWinMesWait(fileSelectWinId);
        return 1;
    }
    else if (freeFiles == 0) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4A));
        HuWinMesWait(fileSelectWinId);
        return 1;
    }
    else if (freeBytes < SAVE_BUF_SIZE) {
        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x4A));
        HuWinMesWait(fileSelectWinId);
        return 1;
    }
    for (i = 0; i < 3; i++) {
        if (!fileSelectBoxPresentF[i]) {
            break;
        }
    }
    if (i == 3) {
        return 1;
    }
    destBoxNo = i;
    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x09));
    HuWinMesWait(fileSelectWinId);
    HuWinMesSet(fileSelectHelpWinId, MAKE_MESSID(16, 0x35));
    HuWinDispOn(fileSelectHelpWinId);
    fileSelectCopySourceBox = boxno;
    Hu3DModelAttrReset(modeSelMdlId[23], HU3D_ATTR_DISPOFF);
    model = &Hu3DData[modeSelMdlId[boxno + 8]];
    Hu3DModelPosSetV(modeSelMdlId[23], &model->pos);
    for (i = 1; i <= 10; i++) {
        time = 0.7 + (0.3 * (i / 10.0));
        Hu3DModelScaleSet(modeSelMdlId[23], time, time, time);
        HuPrcVSleep();
    }
    FileSelectBoxAnimStart(destBoxNo, 1);
    while (1) {
        HuPrcVSleep();
        if (UnMountCnt & (1 << curSlotNo)) {
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x50));
            HuWinMesWait(fileSelectWinId);
            break;
        }
        else {
            move = 0;
            if (HuPadDStkRep[0] & 0x1) {
                move = -1;
            }
            else if (HuPadDStkRep[0] & 0x2) {
                move = 1;
            }
            (void)move;
            if (move) {
                HuAudFXPlay(0);
                FileSelectBoxAnimStart(destBoxNo, 0);
                while (1) {
                    destBoxNo += move;
                    if (destBoxNo < 0) {
                        destBoxNo = 2;
                    }
                    else if (destBoxNo >= 3) {
                        destBoxNo = 0;
                    }
                    if (fileSelectBoxPresentF[destBoxNo] == 0) {
                        break;
                    }
                }
                FileSelectBoxAnimStart(destBoxNo, 1);
                HuPrcSleep(10);
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                HuAudFXPlay(2096);
            }
            else if (!(HuPadBtnDown[0] & PAD_BUTTON_B)) {
                continue;
            }
            else {
                HuAudFXPlay(3);
                Hu3DModelAttrSet(modeSelMdlId[23], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(modeSelMdlId[boxno + 8], HU3D_ATTR_DISPOFF);
                FileSelectBoxAnimStart(destBoxNo, 0);
                HuWinDispOff(fileSelectHelpWinId);
                return 1;
            }
            HuWinDispOff(fileSelectHelpWinId);
            result = FileSelectFileOpen(SaveFileNameTbl[boxno], curSlotNo);
            if (result >= 0 && SLSerialNoCheck()) {
                FileSelectProgressWinOpen(MAKE_MESSID(16, 0x0A));
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x0B));
                HuWinMesWait(fileSelectWinId);
                Hu3DModelAttrReset(modeSelMdlId[boxno + 8], HU3D_ATTR_DISPOFF);
                OSReport("CheckSum Check\n");
                if (!SLCheckSumCheck()) {
                    HuPrcSleep(60);
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(fileSelectBoxNameTbl[boxno]), 0);
                    HuWinAttrSet(fileSelectWinId, 0x10);
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x3A));
                    HuWinMesWait(fileSelectWinId);
                    result = HuWinChoiceGet(fileSelectWinId, 1);
                    if (result == 0) {
                        result = FileSelectFileDelete(boxno);
                    }
                }
                else {
                    FileSelectFileClose();
                    for (i = 0; i <= 10; i++) {
                        time = cosd(90.0 * (i / 10.0));
                        Hu3DModelScaleSet(modeSelMdlId[destBoxNo + 8], time, time, time);
                        HuPrcVSleep();
                    }
                    Hu3DModelAttrSet(modeSelMdlId[23], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(modeSelMdlId[boxno + 8], HU3D_ATTR_DISPOFF);
                    if (UnMountCnt & (1 << curSlotNo)) {
                        FileSelectProgressWinClose();
                        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x50));
                        HuWinMesWait(fileSelectWinId);
                    }
                    else {
                        OSReport("File Create\n");
                        SLCurBoxNoSet(destBoxNo);
                        SLLoadGameStat();
                        SLSaveDataMake(0, &GWGameStat.create_time);
                        if (FileSelectFileCreate(destBoxNo)) {
                            FileSelectFileClose();
                            FileSelectBoxInfoLoad(destBoxNo);
                            Hu3DAnimKill(fileSelectBoxCharAnimId[destBoxNo]);
                            Hu3DAnimKill(fileSelectBoxCharBackAnimId[destBoxNo]);
                            charNo = fileSelectBoxCharNo[destBoxNo];
                            if (charNo < 0) {
                                charNo = 8;
                            }
                            (void)charNo;
                            charAnim = HuSprAnimRead(HuDataReadNum(fileSelectCharAnimTbl[charNo], HU_MEMNUM_OVL));
                            fileSelectBoxCharAnimId[destBoxNo] = Hu3DAnimCreate(charAnim, modeSelMdlId[destBoxNo + 8], "star");
                            charAnim = HuSprAnimRead(HuDataReadNum(fileSelectCharAnimTbl[charNo], HU_MEMNUM_OVL));
                            fileSelectBoxCharBackAnimId[destBoxNo] = Hu3DAnimCreate(charAnim, modeSelMdlId[destBoxNo + 11], "star");
                            Hu3DModelAttrReset(modeSelMdlId[destBoxNo + 11], HU3D_ATTR_DISPOFF);
                            Hu3DModelAttrSet(modeSelMdlId[destBoxNo + 8], HU3D_ATTR_DISPOFF);
                            screenPos.x = 158.0f + (boxno * 130);
                            screenPos.y = 230;
                            screenPos.z = 800;
                            Hu3D2Dto3D(&screenPos, 1, &srcPos);
                            srcPos.z = 900;
                            screenPos.x = 158.0f + (destBoxNo * 130);
                            Hu3D2Dto3D(&screenPos, 1, &destPos);
                            destPos.z = 800;
                            VECSubtract(&destPos, &srcPos, &delta);
                            Hu3DModelTPLvlSet(modeSelMdlId[destBoxNo + 8], 1.0f);
                            Hu3DModelTPLvlSet(modeSelMdlId[destBoxNo + 11], 1.0f);
                            fileSelectBoxLabelF[destBoxNo] = 0;
                            for (i = 1; i <= 30; i++) {
                                time = i / 30.0;
                                screenPos.x = delta.x * time;
                                screenPos.y = delta.y * time;
                                screenPos.z = (delta.z * time) + (-300 * sind(180.0f * time));
                                VECAdd(&screenPos, &srcPos, &screenPos);
                                Hu3DModelPosSetV(modeSelMdlId[destBoxNo + 11], &screenPos);
                                HuPrcVSleep();
                            }
                            fileSelectBoxLabelF[destBoxNo] = 1;
                            FileSelectProgressWinClose();
                            fileSelectBoxPresentF[destBoxNo] = 1;
                            fileSelectBoxNum++;
                            return 1;
                        }
                    }
                }
            }
            break;
        }
    }
    FileSelectProgressWinClose();
    Hu3DModelAttrSet(modeSelMdlId[23], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(modeSelMdlId[boxno + 8], HU3D_ATTR_DISPOFF);
    for (i = 0; i <= 10; i++) {
        time = sind(90.0 * (i / 10.0));
        Hu3DModelScaleSet(modeSelMdlId[destBoxNo + 8], time, time, time);
        HuPrcVSleep();
    }
    FileSelectBoxAnimStart(destBoxNo, 0);
    return 0;
}

s32 FileSelectFileClose(void)
{
    s32 result = HuCardClose(&curFileInfo);
    return result;
}

s16 fileSelectDateCharWidthTbl[] = { 15, 15, 13, 15, 15, 8, 15, 15, 8, 15, 15 };

s32 FileSelectBoxInit(void)
{
    s16 boxNo;
    s16 i;
    s16 sprId;
    HU3DMODEL *model;
    s16 charNo;
    s16 x;
    s16 width;
    ANIMDATA *charAnim;
    s16 result;
    ANIMDATA *dateAnim;
    Mtx scale;
    Vec pos;
    Vec screenPos;
    WindowData *window;
    result = -1;
    window = &winData[fileSelectWinId];
    OSReport("Init\n");
    MTXScale(scale, 0.5f, 0.5f, 0.5f);
    for (boxNo = 0; boxNo < 3; boxNo++) {
        if (fileSelectStarSprGrpId[boxNo] != -1) {
            HuSprGrpKill(fileSelectStarSprGrpId[boxNo]);
        }
    }
    for (boxNo = 0; boxNo < 3; boxNo++) {
        if (fileSelectDateSprGrpId[boxNo] != -1) {
            HuSprGrpKill(fileSelectDateSprGrpId[boxNo]);
        }
    }
    fileSelectStarAnim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x22), HU_MEMNUM_OVL));
    fileSelectDigitAnim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x23), HU_MEMNUM_OVL));
    fileSelectStarMaxAnim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x25), HU_MEMNUM_OVL));
    dateAnim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATA_MAKE_NUM(DATADIR_MODESEL, 0x00), 0x24), HU_MEMNUM_OVL));
    for (boxNo = 0; boxNo < 3; boxNo++) {
        Hu3DModelAttrSet(modeSelMdlId[boxNo + 8], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(modeSelMdlId[boxNo + 11], HU3D_ATTR_DISPOFF);
        charNo = fileSelectBoxCharNo[boxNo];
        if (charNo < 0 || charNo >= 8) {
            charNo = 8;
        }
        if (fileSelectBoxCharAnimId[boxNo] != -1) {
            Hu3DAnimKill(fileSelectBoxCharAnimId[boxNo]);
        }
        if (fileSelectBoxCharBackAnimId[boxNo] != -1) {
            Hu3DAnimKill(fileSelectBoxCharBackAnimId[boxNo]);
        }
        charAnim = HuSprAnimRead(HuDataReadNum(fileSelectCharAnimTbl[charNo], HU_MEMNUM_OVL));
        fileSelectBoxCharAnimId[boxNo] = Hu3DAnimCreate(charAnim, modeSelMdlId[boxNo + 8], "star");
        charAnim = HuSprAnimRead(HuDataReadNum(fileSelectCharAnimTbl[charNo + 9], HU_MEMNUM_OVL));
        fileSelectBoxCharBackAnimId[boxNo] = Hu3DAnimCreate(charAnim, modeSelMdlId[boxNo + 11], "star");
        if (!fileSelectBoxPresentF[boxNo]) {
            Hu3DModelTPLvlSet(modeSelMdlId[boxNo + 8], 0.6f);
            Hu3DModelTPLvlSet(modeSelMdlId[boxNo + 11], 0.3f);
        }
        else {
            Hu3DModelTPLvlSet(modeSelMdlId[boxNo + 8], 1.0f);
            Hu3DModelTPLvlSet(modeSelMdlId[boxNo + 11], 1.0f);
        }
        pos.x = 158.0f + (boxNo * 130);
        pos.y = 230;
        pos.z = 800;
        Hu3D2Dto3D(&pos, 1, &screenPos);
        screenPos.z = 800;
        Hu3DModelPosSetV(modeSelMdlId[boxNo + 8], &screenPos);
        Hu3DModelPosSetV(modeSelMdlId[boxNo + 11], &screenPos);
        Hu3DModelScaleSet(modeSelMdlId[boxNo + 8], 0, 0, 0);
        Hu3DModelScaleSet(modeSelMdlId[boxNo + 11], 0, 0, 0);
        model = &Hu3DData[modeSelMdlId[boxNo + 8]];
        MTXCopy(scale, model->mtx);
        model = &Hu3DData[modeSelMdlId[boxNo + 11]];
        MTXCopy(scale, model->mtx);
        fileSelectStarSprGrpId[boxNo] = HuSprGrpCreate(9);
        sprId = HuSprCreate(fileSelectStarAnim, 3000, 0);
        HuSprGrpMemberSet(fileSelectStarSprGrpId[boxNo], 0, sprId);
        HuSprPosSet(fileSelectStarSprGrpId[boxNo], 0, -48, 0);
        for (i = 0; i < 4; i++) {
            sprId = HuSprCreate(fileSelectDigitAnim, 3000, 0);
            HuSprGrpMemberSet(fileSelectStarSprGrpId[boxNo], i + 1, sprId);
            HuSprPosSet(fileSelectStarSprGrpId[boxNo], i + 1, (i * 24) - 24, 0);
        }
        sprId = HuSprCreate(fileSelectStarMaxAnim, 3000, 0);
        HuSprGrpMemberSet(fileSelectStarSprGrpId[boxNo], 5, sprId);
        HuSprPosSet(fileSelectStarSprGrpId[boxNo], 5, 16, 0);
        HuSprGrpScissorSet(fileSelectStarSprGrpId[boxNo], 0, 16, 640, 448);
        fileSelectDateSprGrpId[boxNo] = HuSprGrpCreate(11);
        for (i = width = 0; i < 11; i++) {
            width += fileSelectDateCharWidthTbl[i];
        }
        for (i = x = 0; i < 11; i++) {
            sprId = HuSprCreate(dateAnim, 3000, 0);
            HuSprGrpMemberSet(fileSelectDateSprGrpId[boxNo], i, sprId);
            HuSprPosSet(fileSelectDateSprGrpId[boxNo], i, -(width / 2) + 8 + x, 0);
            x += fileSelectDateCharWidthTbl[i];
        }
        HuSprAttrSet(fileSelectDateSprGrpId[boxNo], 5, 4);
        HuSprBankSet(fileSelectDateSprGrpId[boxNo], 2, 10);
        HuSprBankSet(fileSelectDateSprGrpId[boxNo], 8, 11);
        HuSprGrpScissorSet(fileSelectDateSprGrpId[boxNo], 0, 16, 640, 448);
    }
    MTXScale(scale, 0.45f, 0.45f, 0.45f);
    model = &Hu3DData[modeSelMdlId[23]];
    Hu3DModelAttrSet(modeSelMdlId[23], HU3D_MOTATTR_LOOP);
    MTXCopy(scale, model->mtx);
    return result;
}

void FileSelectBoxInfoLoad(s16 boxno)
{
    SLLoadGameStat();
    SLLoadBoardStory();
    fileSelectBoxStars[boxno] = GWGameStat.total_stars;
    fileSelectBoxCreateTime[boxno] = GWGameStat.create_time;
    fileSelectBoxCharNo[boxno] = GWSystem.storyChar;
    fileSelectStoryContinueF[boxno] = GWGameStat.story_continue;
    fileSelectPartyContinueF[boxno] = GWGameStat.party_continue;
    if (GWGameStat.story_continue) {
        SLLoadBoardStory();
        fileSelectStoryBoardNo[boxno] = GWSystem.board;
        fileSelectStoryClearF[boxno] = 0;
    }
    if (GWGameStat.party_continue) {
        SLLoadBoard();
        fileSelectPartyBoardNo[boxno] = GWSystem.board;
        fileSelectPartyTurn[boxno] = GWSystem.turn;
        fileSelectPartyMaxTurn[boxno] = GWSystem.max_turn;
    }
}

void FileSelectDisplayMain(void)
{
    float scale;
    float baseHeight;
    float height;
    HU3DMODEL *model;
    s16 i;
    s16 digit;
    s16 j;
    Mtx matrix;
    OSCalendarTime calendar;
    Vec screenPos;
    Vec pos;
    for (i = 0; i < 2; i++) {
        fileSelectSlotLabelF[i] = 1;
    }
    while (1) {
        for (i = 0; i < 2; i++) {
            MTXScale(matrix, 0.5f, 0.5f, 0.5f);
            mtxRotCat(matrix, 0.0f, 0.0f, 15.0f * fileSelectCardTiltScale[i]);
            model = &Hu3DData[modeSelMdlId[i]];
            MTXCopy(matrix, model->mtx);
            Hu3DModelRotSet(modeSelMdlId[i], 0, fileSelectCardRot * fileSelectCardRotScale[i] * GET_ZEROSIGN(i == 0), 0);
            if (!fileSelectSlotLabelF[i]) {
                espAttrSet(modeSelSprId[i + 2], HUSPR_ATTR_DISPOFF);
            }
            else {
                model = &Hu3DData[modeSelMdlId[i + 2]];
                if (model->attr & 0x1) {
                    model = &Hu3DData[modeSelMdlId[i + 4]];
                }
                if (model->attr & 0x1) {
                    espAttrSet(modeSelSprId[i + 2], HUSPR_ATTR_DISPOFF);
                }
                else {
                    espAttrReset(modeSelSprId[i + 2], HUSPR_ATTR_DISPOFF);
                }
                pos = model->pos;
                pos.y -= 30.0f * model->scale.x;
                Hu3D3Dto2D(&pos, 1, &screenPos);
                espPosSet(modeSelSprId[i + 2], screenPos.x, screenPos.y);
                espScaleSet(modeSelSprId[i + 2], model->scale.x, model->scale.x);
            }
        }
        fileSelectCardRot += 3.0f;
        if (fileSelectCardRot > 1080.0f) {
            fileSelectCardRot -= 360;
        }
        if (fileSelectSlotNo == -1) {
            espAttrSet(modeSelSprId[4], HUSPR_ATTR_DISPOFF);
        }
        else {
            model = &Hu3DData[modeSelMdlId[fileSelectSlotNo]];
            if (model->attr & 0x1) {
                espAttrSet(modeSelSprId[4], HUSPR_ATTR_DISPOFF);
            }
            else {
                espBankSet(modeSelSprId[4], fileSelectSlotNo);
                espAttrReset(modeSelSprId[4], HUSPR_ATTR_DISPOFF);
                pos = model->pos;
                pos.y += 5.0f * model->scale.x;
                Hu3D3Dto2D(&pos, 1, &screenPos);
                espPosSet(modeSelSprId[4], screenPos.x, screenPos.y);
                espScaleSet(modeSelSprId[4], model->scale.x, model->scale.x);
            }
        }
        for (i = 0; i < 3; i++) {
            if (!fileSelectBoxLabelF[i]) {
                espAttrSet(modeSelSprId[i + 5], HUSPR_ATTR_DISPOFF);
                continue;
            }
            model = &Hu3DData[modeSelMdlId[i + 8]];
            if (model->attr & 0x1) {
                model = &Hu3DData[modeSelMdlId[i + 11]];
            }
            baseHeight = (900.0 + (50.0 * model->scale.x)) * sin(M_PI / 12);
            height = (model->pos.z + (50.0 * model->scale.x)) * sin(M_PI / 12);
            scale = model->scale.x * (height / baseHeight);
            if (model->attr & 0x1) {
                espAttrSet(modeSelSprId[i + 5], HUSPR_ATTR_DISPOFF);
            }
            else {
                espAttrReset(modeSelSprId[i + 5], HUSPR_ATTR_DISPOFF);
            }
            pos = model->pos;
            pos.y += 40.0 * model->scale.x;
            pos.z += 50.0 * model->scale.x;
            Hu3D3Dto2D(&pos, 1, &screenPos);
            espPosSet(modeSelSprId[i + 5], screenPos.x, screenPos.y);
            espScaleSet(modeSelSprId[i + 5], scale, scale);
            if (fileSelectBoxStars[i] == -1) {
                HuSprGrpPosSet(fileSelectStarSprGrpId[i], 0, -500);
            }
            else {
                pos = model->pos;
                pos.y -= 30.0 * model->scale.x;
                pos.z += 50.0 * model->scale.x;
                Hu3D3Dto2D(&pos, 1, &screenPos);
                HuSprGrpPosSet(fileSelectStarSprGrpId[i], screenPos.x, screenPos.y);
                HuSprGrpScaleSet(fileSelectStarSprGrpId[i], scale, scale);
                if (fileSelectBoxStars[i] > 9999) {
                    for (j = 0; j < 4; j++) {
                        HuSprAttrSet(fileSelectStarSprGrpId[i], j + 1, HUSPR_ATTR_DISPOFF);
                    }
                    HuSprAttrReset(fileSelectStarSprGrpId[i], 5, HUSPR_ATTR_DISPOFF);
                }
                else {
                    for (j = 0; j < 4; j++) {
                        HuSprAttrReset(fileSelectStarSprGrpId[i], j + 1, HUSPR_ATTR_DISPOFF);
                    }
                    HuSprAttrSet(fileSelectStarSprGrpId[i], 5, HUSPR_ATTR_DISPOFF);
                    digit = fileSelectBoxStars[i];
                    HuSprBankSet(fileSelectStarSprGrpId[i], 1, digit / 1000);
                    digit -= (digit / 1000) * 1000;
                    HuSprBankSet(fileSelectStarSprGrpId[i], 2, digit / 100);
                    digit -= (digit / 100) * 100;
                    HuSprBankSet(fileSelectStarSprGrpId[i], 3, digit / 10);
                    digit -= (digit / 10) * 10;
                    HuSprBankSet(fileSelectStarSprGrpId[i], 4, digit);
                }
                pos = model->pos;
                pos.y -= 40.0 * model->scale.x;
                pos.z += 50.0 * model->scale.x;
                Hu3D3Dto2D(&pos, 1, &screenPos);
                HuSprGrpPosSet(fileSelectDateSprGrpId[i], screenPos.x, screenPos.y);
                HuSprGrpScaleSet(fileSelectDateSprGrpId[i], scale, scale);
                OSTicksToCalendarTime(fileSelectBoxCreateTime[i], &calendar);
                #if VERSION_PAL
                digit = calendar.mday;
                HuSprBankSet(fileSelectDateSprGrpId[i], 0, digit / 10);
                digit -= (digit / 10) * 10;
                HuSprBankSet(fileSelectDateSprGrpId[i], 1, digit);
                digit = calendar.mon+1;
                HuSprBankSet(fileSelectDateSprGrpId[i], 3, digit / 10);
                digit -= (digit / 10) * 10;
                HuSprBankSet(fileSelectDateSprGrpId[i], 4, digit);
                #else
                digit = calendar.mon + 1;
                HuSprBankSet(fileSelectDateSprGrpId[i], 0, digit / 10);
                digit -= (digit / 10) * 10;
                HuSprBankSet(fileSelectDateSprGrpId[i], 1, digit);
                digit = calendar.mday;
                HuSprBankSet(fileSelectDateSprGrpId[i], 3, digit / 10);
                digit -= (digit / 10) * 10;
                HuSprBankSet(fileSelectDateSprGrpId[i], 4, digit);
                #endif
                digit = calendar.hour;
                HuSprBankSet(fileSelectDateSprGrpId[i], 6, digit / 10);
                digit -= (digit / 10) * 10;
                HuSprBankSet(fileSelectDateSprGrpId[i], 7, digit);
                digit = calendar.min;
                HuSprBankSet(fileSelectDateSprGrpId[i], 9, digit / 10);
                digit -= (digit / 10) * 10;
                HuSprBankSet(fileSelectDateSprGrpId[i], 10, digit);
            }
        }
        HuPrcVSleep();
    }
}

s16 fileSelectProgressWinId = -1;

void FileSelectProgressWinOpen(u32 messId)
{
    float size[2];
    if (fileSelectProgressWinId != -1) {
        HuWinExCleanup(fileSelectProgressWinId);
    }
    HuWinInsertMesSizeGet(MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
    HuWinMesMaxSizeGet(1, size, messId);
    fileSelectProgressWinId = HuWinExCreateStyled(-10000, 308, size[0], size[1], -1, 2);
    HuWinMesSpeedSet(fileSelectProgressWinId, 0);
    HuWinExAnimIn(fileSelectProgressWinId);
    HuWinInsertMesSet(fileSelectProgressWinId, MAKE_MESSID_PTR(fileSelectSlotNameTbl[curSlotNo]), 0);
    HuWinMesSet(fileSelectProgressWinId, messId);
    HuWinMesWait(fileSelectProgressWinId);
}

void FileSelectProgressWinClose(void)
{
    if (fileSelectProgressWinId != -1) {
        HuWinExAnimOut(fileSelectProgressWinId);
        HuWinExCleanup(fileSelectProgressWinId);
        fileSelectProgressWinId = -1;
    }
}

void FileSelectBoxInfoSet(s16 boxno)
{
    char mesMaxTurn[4];
    char mesTurn[4];
    char mesDummy[1] = { 0 };
    if (fileSelectBoxStars[boxno] < 0) {
        HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x11));
    }
    else {
        if (!fileSelectStoryContinueF[boxno] && !fileSelectPartyContinueF[boxno]) {
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x11), 0);
            HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(mesDummy), 1);
            HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x43));
        }
        else {
            if (!fileSelectStoryContinueF[boxno]) {
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x11), 0);
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(mesDummy), 1);
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x12) + fileSelectPartyBoardNo[boxno], 2);
                sprintf(mesMaxTurn, "%2d", fileSelectPartyTurn[boxno]);
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(mesMaxTurn), 3);
                sprintf(mesTurn, "%2d", fileSelectPartyMaxTurn[boxno]);
                HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(mesTurn), 4);
                HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x42));
            }
            else {
                if (!fileSelectPartyContinueF[boxno]) {
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x12) + fileSelectStoryBoardNo[boxno], 0);
                    if (fileSelectStoryClearF[boxno]) {
                        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x18), 1);
                    }
                    else {
                        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(mesDummy), 1);
                    }
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x43));
                }
                else {
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x12) + fileSelectStoryBoardNo[boxno], 0);
                    if (fileSelectStoryClearF[boxno]) {
                        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x18), 1);
                    }
                    else {
                        HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(mesDummy), 1);
                    }
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID(16, 0x12) + fileSelectPartyBoardNo[boxno], 2);
                    sprintf(mesMaxTurn, "%2d", fileSelectPartyTurn[boxno]);
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(mesMaxTurn), 3);
                    sprintf(mesTurn, "%2d", fileSelectPartyMaxTurn[boxno]);
                    HuWinInsertMesSet(fileSelectWinId, MAKE_MESSID_PTR(mesTurn), 4);
                    HuWinMesSet(fileSelectWinId, MAKE_MESSID(16, 0x42));
                }
            }
        }
    }
    HuWinMesWait(fileSelectWinId);
}
