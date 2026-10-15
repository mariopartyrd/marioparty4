#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/modeseldll.h"
#include "ext_math.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/thpmain.h"
#endif

s16 modeCardMdlTbl[] = { 16, 17, 18, 19, 20, 21 };

s32 modeCardFrontAnimTbl[] = { DATA_MAKE_NUM(DATADIR_MODESEL, 0x30), DATA_MAKE_NUM(DATADIR_MODESEL, 0x32), DATA_MAKE_NUM(DATADIR_MODESEL, 0x34),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x36), DATA_MAKE_NUM(DATADIR_MODESEL, 0x38), DATA_MAKE_NUM(DATADIR_MODESEL, 0x3A) };

s32 modeCardBackAnimTbl[] = { DATA_MAKE_NUM(DATADIR_MODESEL, 0x31), DATA_MAKE_NUM(DATADIR_MODESEL, 0x33), DATA_MAKE_NUM(DATADIR_MODESEL, 0x35),
    DATA_MAKE_NUM(DATADIR_MODESEL, 0x37), DATA_MAKE_NUM(DATADIR_MODESEL, 0x39), DATA_MAKE_NUM(DATADIR_MODESEL, 0x3B) };

u32 modeHelpMessTbl[] = { MAKE_MESSID(17, 1), MAKE_MESSID(17, 2), MAKE_MESSID(17, 3), MAKE_MESSID(17, 4), MAKE_MESSID(17, 5), MAKE_MESSID(17, 6) };

s16 modeHelpWinId;
s16 modeNo;

void ModeSelCardInit(void);

// Scratch is at https://decomp.me/scratch/iirXp
// Register allocation issues at line 180 with load of 1.0 double constant
s32 ModeSelExec(void)
{
    float helpWinSize[2];
    float returnWinSize[2];
    float time;
    float speed;
    s16 frame;
    s16 move;
    s16 returnWinId;
    s16 cardNo;
    s16 movieGrpId;
    s16 prevModeNo;
    s32 fxId;
    WindowData *helpWin;
    ANIMDATA *frontAnim;
    ANIMDATA *backAnim;
    s16 movieSprId;
    ModeSelCardInit();
    ModeSelCameraViewSet(1);
    fxId = HuAudFXPlay(2094);
    if (omovlevtno) {
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    }
    for (frame = 0; frame <= 20; frame++) {
        time = 1.0 - sind(90.0 * (frame / 20.0));
        Hu3DModelPosSet(modeSelMdlId[14], 0, -50.0f + (200.0f * time), 0);
        Hu3DModelPosSet(modeSelMdlId[15], 0, -50.0f + (200.0f * time), 0);
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    Hu3DModelAttrReset(modeSelMdlId[14], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(modeSelMdlId[15], HU3D_MOTATTR_PAUSE);
    HuAudFXPlay(2093);
    HuPrcSleep(120);
    HuAudFXPlay(2095);
    for (frame = 0; frame <= 30; frame++) {
        time = frame / 30.0;
        Hu3DModelPosSet(modeSelMdlId[14], 0, -50.0f - (20.0f * time), 0);
        HuPrcVSleep();
    }
    HuWinMesMaxSizeBetGet(helpWinSize, MAKE_MESSID(0x11, 0x00), MAKE_MESSID(0x11, 0x06));
    modeHelpWinId = HuWinExCreateStyled(-10000, 432 - helpWinSize[1], helpWinSize[0], helpWinSize[1], -1, 0);
    HuWinMesSpeedSet(modeHelpWinId, 0);
    helpWin = &winData[modeHelpWinId];
    helpWin->active_pad = 1;
    HuWinExAnimIn(modeHelpWinId);
    HuWinMesSet(modeHelpWinId, MAKE_MESSID(0x11, 0x00));
    HuWinMesMaxSizeGet(1, returnWinSize, MAKE_MESSID(0x1A, 0x20));
    returnWinId = HuWinCreate(-10000, 8 + (432 - helpWinSize[1] - returnWinSize[1]), returnWinSize[0], returnWinSize[1], 0);
    HuWinMesSpeedSet(returnWinId, 0);
    HuWinBGTPLvlSet(returnWinId, 0);
    HuWinMesSet(returnWinId, MAKE_MESSID(0x1A, 0x20));
    HuWinDispOff(returnWinId);
    while (!Hu3DMotionEndCheck(modeSelMdlId[15])) {
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(modeSelMdlId[15], HU3D_ATTR_DISPOFF);
    for (frame = 0; frame < 6; frame++) {
        Hu3DModelAttrReset(modeSelMdlId[modeCardMdlTbl[frame]], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(modeSelMdlId[modeCardMdlTbl[frame]], HU3D_MOTATTR_PAUSE);
        Hu3DMotionTimeSet(modeSelMdlId[modeCardMdlTbl[frame]], 0);
        Hu3DModelPosSet(modeSelMdlId[modeCardMdlTbl[frame]], 0, -50, 0);
    }
    HuWinMesWait(modeHelpWinId);

    prevModeNo = modeNo = 0;
    espAttrReset(modeSelSprId[10], HUSPR_ATTR_DISPOFF);
    espBankSet(modeSelSprId[10], 0);
    for (frame = 0; frame <= 10; frame++) {
        time = frame / 10.0f;
        Hu3DModelPosSet(modeSelMdlId[modeCardMdlTbl[modeNo]], 0, -50, 50.0 * sind(90.0f * time));
        espPosSet(modeSelSprId[10], 288.0, -50.0 + (106.0 * sind(90.0f * time)));
        HuPrcVSleep();
    }
    HuWinMesSet(modeHelpWinId, modeHelpMessTbl[modeNo]);
    HuWinDispOn(returnWinId);
    while (1) {
        move = 0;
        if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
            move = -1;
        }
        else if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
            move = 1;
        }
        if (move) {
            if (modeNo + move < 0) {
                modeNo = 0;
            }
            else if (modeNo + move >= 6) {
                modeNo = 5;
            }
            else {
                modeNo += move;
            }
            if (prevModeNo != modeNo) {
                HuAudFXPlay(0);
                for (frame = 0; frame <= 10; frame++) {
                    time = frame / 10.0f;
                    Hu3DModelPosSet(modeSelMdlId[modeCardMdlTbl[prevModeNo]], 0, -50, 50.0 * cosd(90.0f * time));
                    Hu3DModelPosSet(modeSelMdlId[modeCardMdlTbl[modeNo]], 0, -50, 50.0 * sind(90.0f * time));
                    espPosSet(modeSelSprId[10], 288.0, -50.0 + (106.0 * (1.0 - sind(180.0f * time))));
                    if (frame == 5) {
                        espBankSet(modeSelSprId[10], modeNo);
                    }
                    HuPrcVSleep();
                }
                prevModeNo = modeNo;
                HuWinMesSet(modeHelpWinId, modeHelpMessTbl[modeNo]);
            }
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            HuAudFXPlay(2);
            break;
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            HuAudFXStop(fxId);
            return -1;
        }
        else {
            HuPrcVSleep();
            continue;
        }
    }
    Hu3DModelAttrReset(modeSelMdlId[modeCardMdlTbl[modeNo]], HU3D_MOTATTR_PAUSE);
    HuAudSeqAllFadeOut(1000);
    for (frame = 0; frame <= 20; frame++) {
        time = frame / 20.0f;
        for (cardNo = 0; cardNo < 6; cardNo++) {
            if (cardNo != modeNo) {
                Hu3DModelPosSet(modeSelMdlId[modeCardMdlTbl[cardNo]], 0, -50 - (300.0 * (1.0 - cosd(90.0f * time))), 0);
                espPosSet(modeSelSprId[10], 288.0, -50.0 + (106.0 * (cosd(90.0f * time))));
            }
        }
        HuPrcVSleep();
    }
    HuWinKill(returnWinId);
    HuWinExAnimOut(modeHelpWinId);
    HuAudFXStop(fxId);
    movieGrpId = HuSprGrpCreate(1);
    movieSprId = HuTHPSprCreateVol("movie/opmov_c00.thp", 0, 3000, 90.0);
    HuSprGrpMemberSet(movieGrpId, 0, movieSprId);
    HuSprPosSet(movieGrpId, 0, 288.0f, 240.0f);
    HuSprDrawNoSet(movieGrpId, 0, 127);
    HuPrcSleep(2);
    espAttrSet(modeSelSprId[9], HUSPR_ATTR_DISPOFF);
    for (frame = 0; frame <= 10; frame++) {
        time = frame / 10.0;
        Hu3DModelPosSet(modeSelMdlId[14], 0, -70.0f - (100.0f * time), 0);
        HuPrcVSleep();
    }
    frontAnim = HuSprAnimRead(HuDataReadNum(modeCardFrontAnimTbl[modeNo], HU_MEMNUM_OVL));
    backAnim = HuSprAnimRead(HuDataReadNum(modeCardBackAnimTbl[modeNo], HU_MEMNUM_OVL));
    Hu3DAnimCreate(frontAnim, modeSelMdlId[22], "ys002_a1");
    Hu3DAnimCreate(backAnim, modeSelMdlId[22], "ys002_a2");
    Hu3DModelAttrSet(modeSelMdlId[modeCardMdlTbl[modeNo]], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(modeSelMdlId[22], 0);
    Hu3DModelAttrReset(modeSelMdlId[22], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(modeSelMdlId[22], HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(modeSelMdlId[22], 0, 27, 50);
    Hu3DModelScaleSet(modeSelMdlId[22], 1.0f, 1.063f, 1.0f);
    for (frame = 1; frame <= 20; frame++) {
        time = frame / 20.0;
        Hu3DModelPosSet(modeSelMdlId[22], 0, 27.0 - (60.0 * sind(90.0f * time)), 50);
        HuPrcVSleep();
    }
    HuPrcSleep(90);
    Hu3DFogSet(3000, 8000, 255, 255, 255);
    Hu3DModelAttrReset(modeSelMdlId[22], HU3D_MOTATTR_PAUSE);
    HuPrcSleep(60);
    time = 0;
    speed = 5;
    while (!HuTHPEndCheck()) {
        Hu3DModelPosSet(modeSelMdlId[22], 0, -33.0f + (time / 30.0f), 50.0f - time);
        time += speed;
        speed += 5.0f;
        HuPrcVSleep();
    }
    _ClearFlag(FLAG_ID_MAKE(1, 11));
    WipeColorSet(255, 255, 255);
    #if VERSION_PAL
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
    #else
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 10);
    #endif
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuTHPClose();
    HuSprGrpKill(movieGrpId);
    return modeNo;
}

void ModeSelCardInit(void)
{
    Vec pos;
    Vec target;
    Vec up;
    Hu3DShadowCreate(20, 100, 5000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowSizeSet(192);
    target.x = target.y = target.z = 0;
    pos.x = 0;
    pos.z = 300;
    pos.y = 400;
    up.x = 0;
    up.y = 1;
    up.z = 0;
    Hu3DShadowPosSet(&pos, &up, &target);
    Hu3DModelAttrReset(modeSelMdlId[15], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(modeSelMdlId[15], HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(modeSelMdlId[15], 0);
    Hu3DModelAttrReset(modeSelMdlId[14], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(modeSelMdlId[14], HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(modeSelMdlId[14], 0);
}
