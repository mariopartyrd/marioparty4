#include "dolphin.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/board/player.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/saveload.h"
#include "game/window.h"
#include "game/wipe.h"

#include "ext_math.h"

#include "REL/resultdll.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#endif

static StageModel resultModel[] = { { DATA_MAKE_NUM(DATADIR_RESULT, 0x00), 1, 0, -1, -1, { 148, 132, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x01), 1, 0, -1, -1, { 148, 217, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x02), 1, 0, -1, -1, { 148, 302, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x03), 1, 0, -1, -1, { 148, 387, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 0, -1, -1, { 230, 132, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 4, -1, { 230, 217, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 4, -1, { 230, 302, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 4, -1, { 230, 387, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x05), 0, 0, -1, -1, { 410, 132, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 8, -1, { 410, 217, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 8, -1, { 410, 302, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x06), 0, 2, 8, -1, { 410, 387, 500 }, { 0, 0, 0 }, { 1, 1, 1 } },
    { -1, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } } };

static StageSprite resultSprite[] = {
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x43), 0, 10, 288, 240, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1D), 0, 10, 288, 60, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 270, 132, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 450, 132, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 270, 217, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 450, 217, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 270, 302, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 450, 302, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 270, 387, { 255, 255, 255, 255 } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x1A), 0, 10, 450, 387, { 255, 255, 255, 255 } },
    { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } },
};

static s16 rankNewGrpId = -1;

omObjData *lbl_1_bss_188;
static omObjData *outViewObj;
Process *objman;
s16 resultMgNo;
s32 resultReadEndF;
s32 resultFastF;
s16 resultBonusPlayer;
static s16 teamResultGrpId;
static s16 charShadowMdlId[4];
static s16 statShadowMdlId[8];
static AnimData *resultRankAnim[5];
static AnimData *resultCharAnim[8][3];
static AnimData *resultCrownAnim;
static s16 resultNumGrpId[8];
static s16 resultNumSprId[8][3];
static s16 resultCrownGrpId;
static s16 resultCubeMdlId[8][4];
static s16 resultPlayerCubeMdlId[4];
static s16 resultRankGrpId;
static s16 resultOrder[4];
static s16 resultRank[4];
static s16 resultCoinAddGrpId[4];
static s16 resultCoinAddSprId[4][5];
static s16 resultCharCubeMdlId[4];
static s16 resultTeamOrder;
static s32 resultSkipF;
static s32 resultReorderF;

static void ResultMain(void);
static void ResultIdle(void);

static void ResultCreate(void);
static void ResultStatAdd(void);
static void ResultOrderApply(void);
static void SaveExec(void);
static void ResultTeamExec(void);

void ObjectSetup(void)
{
    s32 i;
    s32 lightId;
    OSReport("******* RESULT ObjectSetup *********\n");
    objman = omInitObjMan(50, 8192);
    resultMgNo = GWSystem.mg_next;

    if (mgInfoTbl[resultMgNo].ovl == OVL_M430) {
        for (i = 0; i < 4; i++) {
            GWPlayerCfg[i].group = GWPlayerCfg[i].group / 2;
        }
    }
    HuDataDirClose(mgInfoTbl[resultMgNo].data_dir);
    if (mgInfoTbl[resultMgNo].type == 3 || mgInfoTbl[resultMgNo].type == 5 || mgInfoTbl[resultMgNo].type == 6
        || !_CheckFlag(FLAG_ID_MAKE(1, 0))) {
        if (_CheckFlag(0x10000)) {
            HuAR_DVDtoARAM(DATADIR_BOARD);
            while (HuARDMACheck())
                ;
        }
        omOvlReturnEx(1, 1);
        return;
    }
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    CZoom = 500.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    lightId = Hu3DGLightCreate(0, 100, 1000, 0, -0.5, -1, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
    resultFastF = 0;
    if (mgInfoTbl[GWSystem.mg_next].type != 4) {
        HuPrcChildCreate(ResultMain, 100, 12288, 0, objman);
    }
    else {
        HuPrcChildCreate(ResultBattleMain, 100, 12288, 0, objman);
    }
    outViewObj = omAddObjEx(objman, 32730, 0, 0, -1, omOutView);
    HuWinInit(1);
    resultBonusPlayer = frandmod(4);
}

static void ResultMain(void)
{
    s16 player;
    s16 i;
    s16 winId;
    s16 btnDown;
    Process *proc = HuPrcCurrentGet();
    HuAudSeqPlay(57);
    for (i = player = 0; i < 4; i++) {
        if (GWPlayerCfg[i].iscom) {
            player++;
        }
    }
    if (player == 4) {
        resultSkipF = 1;
    }
    else {
        resultSkipF = 0;
    }
    ResultCreate();
    HuPrcChildCreate(ResultIdle, 100, 8192, 0, objman);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATADIR_RESULT);
    resultReadEndF = 0;
    HuPrcChildCreate(ResultBoardDataRead, 100, 12288, 0, objman);
    HuPrcSleep(10);
    if (!resultFastF) {
        HuPrcSleep(20);
    }
    ResultStatAdd();
    ResultCoinAdd();
    ResultOrderApply();
    winId = HuWinCreate(-10000.0f, 400.0f, 320, 40, 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinBGTPLvlSet(winId, 0);
    HuWinPriSet(winId, 5);
    HuWinAttrSet(winId, 0x800);
    HuWinMesSet(winId, MAKE_MESSID(0x24, 0x07));
    HuPrcSleep(4);
    i = 0;
    while (1) {
        if (!resultSkipF || i <= 120) {
            for (player = btnDown = 0; player < 4; player++) {
                if (!GWPlayerCfg[player].iscom) {
                    btnDown |= HuPadBtnDown[GWPlayerCfg[player].pad_idx];
                }
            }
            if (btnDown & PAD_BUTTON_A) {
                HuAudFXPlay(28);
                break;
            }
            HuPrcVSleep();
            i++;
        }
        else {
            break;
        }
    }
    HuWinKill(winId);
    if (GWTeamGet()) {
        ResultTeamExec();
    }
    while (!resultReadEndF) {
        HuPrcVSleep();
    }
    HuAudSeqAllFadeOut(1000);
    WipeColorSet(255, 255, 255);
    if (GWSaveModeGet() != 1 && SLSaveFlagGet()) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        SaveExec();
    }
    else {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
    }
    omSysPauseEnable(1);
    omOvlReturnEx(1, 1);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

static void ResultIdle(void)
{
    float rotRightSpeed;
    float rotLeft;
    float rotRight;

    rotLeft = 0.0f;
    rotRight = 0.0f;
    rotRightSpeed = 0.0f;
    resultReorderF = 0;

    while (1) {
        if (((HuPadBtn[0] | HuPadBtn[1] | HuPadBtn[2] | HuPadBtn[3]) & PAD_BUTTON_A) != 0 || resultSkipF != 0) {
            resultFastF = 1;
        }
        else {
            resultFastF = 0;
        }
        Hu3DModelRotSet(stageMdlId[4], 0.0f, rotLeft, 0.0f);
        Hu3DModelRotSet(stageMdlId[5], 0.0f, -rotLeft, 0.0f);
        Hu3DModelRotSet(stageMdlId[6], 0.0f, rotLeft, 0.0f);
        Hu3DModelRotSet(stageMdlId[7], 0.0f, -rotLeft, 0.0f);
        rotLeft += 0.2;
        if (rotLeft >= 360.0f) {
            rotLeft -= 360.0f;
        }
        if (resultReorderF != 0) {
            Hu3DModelRotSet(stageMdlId[8], 0.0f, rotRight, 0.0f);
            Hu3DModelRotSet(stageMdlId[9], 0.0f, -rotRight, 0.0f);
            Hu3DModelRotSet(stageMdlId[10], 0.0f, rotRight, 0.0f);
            Hu3DModelRotSet(stageMdlId[11], 0.0f, -rotRight, 0.0f);
            rotRightSpeed += 0.001;
            if (rotRightSpeed > 0.1) {
                rotRightSpeed = 0.1f;
            }
            rotRight += rotRightSpeed;
            if (rotRight >= 360.0f) {
                rotRight -= 360.0f;
            }
        }
        HuPrcVSleep();
    }
}

static s32 resultBackFile[] = {
    DATA_MAKE_NUM(DATADIR_RESULT, 0x10),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x11),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x12),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x13),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x14),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x15),
};

static s32 resultLetterFile[] = {
    DATA_MAKE_NUM(DATADIR_RESULT, 0x1F),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x1E),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x1D),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x21),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x20),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x1F),
};

static s16 resultStatPosTbl[] = {
    320,
    132,
    500,
    132,
    320,
    217,
    500,
    217,
    320,
    302,
    500,
    302,
    320,
    387,
    500,
    387,
};

static s16 resultRankPosTbl[] = { 74, 132, 74, 217, 74, 302, 74, 387 };

static Vec resultCharPosTbl[4] = { { 148, 132, 500 }, { 148, 217, 500 }, { 148, 302, 500 }, { 148, 387, 500 } };

static s16 resultCoinAddPosTbl[] = { 164, 148, 164, 233, 164, 318, 164, 403 };

static void ResultSprNumSet(s16 grpId, s16 value);
static void ResultCoinAddNumSet(s16 grpId, s16 value);

static void ResultOrderSet(void);

static void ResultCreate(void)
{
    Vec pos;
    s16 coinNum[5];
    s16 i;
    s16 j;
    s16 charNo;
    AnimData *anim;
    s16 sprId;
    s16 grpId;
    s16 mdlId;
    AnimData *anim2;
    AnimData *anim3;
    AnimData *anim4;

    StageModelCreate(resultModel);
    resultSprite[0].datanum = resultBackFile[mgInfoTbl[resultMgNo].type];
    resultSprite[1].datanum = resultLetterFile[mgInfoTbl[resultMgNo].type];
    StageSpriteCreate(resultSprite);
    espDrawNoSet(stageSprId[0], 127);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x1B));
    for (i = 0; i < 8; i++) {
        resultNumGrpId[i] = HuSprGrpCreate(3);
        resultNumSprId[i][0] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(resultNumGrpId[i], 0, resultNumSprId[i][0]);
        HuSprPosSet(resultNumGrpId[i], 0, -28.0f, 0.0f);
        resultNumSprId[i][1] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(resultNumGrpId[i], 1, resultNumSprId[i][1]);
        HuSprPosSet(resultNumGrpId[i], 1, 0.0f, 0.0f);
        resultNumSprId[i][2] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(resultNumGrpId[i], 2, resultNumSprId[i][2]);
        HuSprPosSet(resultNumGrpId[i], 2, 28.0f, 0.0f);
        HuSprGrpPosSet(resultNumGrpId[i], resultStatPosTbl[(i * 2)], resultStatPosTbl[(i * 2) + 1]);
        ResultSprNumSet(resultNumGrpId[i], 999);
    }
    ResultOrderSet();
    ResultCoinNumGet(coinNum);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3A));
    anim3 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3B));
    anim2 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3C));
    anim4 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3E));
    for (i = 0; i < 4; i++) {
        resultCoinAddGrpId[i] = HuSprGrpCreate(5);
        if (coinNum[resultOrder[i]] < 100) {
            resultCoinAddSprId[i][0] = HuSprCreate(anim, 10, 0);
            HuSprGrpMemberSet(resultCoinAddGrpId[i], 0, resultCoinAddSprId[i][0]);
            HuSprPosSet(resultCoinAddGrpId[i], 0, 30.0f, -25.0f);
        }
        else {
            resultCoinAddSprId[i][0] = HuSprCreate(anim4, 10, 0);
            HuSprGrpMemberSet(resultCoinAddGrpId[i], 0, resultCoinAddSprId[i][0]);
            HuSprPosSet(resultCoinAddGrpId[i], 0, 40.0f, -21.0f);
        }
        resultCoinAddSprId[i][1] = HuSprCreate(anim3, 0, 0);
        HuSprGrpMemberSet(resultCoinAddGrpId[i], 1, resultCoinAddSprId[i][1]);
        HuSprPosSet(resultCoinAddGrpId[i], 1, 12.0f, -25.0f);
        resultCoinAddSprId[i][2] = HuSprCreate(anim2, 0, 0);
        HuSprGrpMemberSet(resultCoinAddGrpId[i], 2, resultCoinAddSprId[i][2]);
        HuSprPosSet(resultCoinAddGrpId[i], 2, 28.0f, -25.0f);
        resultCoinAddSprId[i][3] = HuSprCreate(anim2, 0, 0);
        HuSprGrpMemberSet(resultCoinAddGrpId[i], 3, resultCoinAddSprId[i][3]);
        HuSprPosSet(resultCoinAddGrpId[i], 3, 44.0f, -25.0f);
        resultCoinAddSprId[i][4] = HuSprCreate(anim2, 0, 0);
        HuSprGrpMemberSet(resultCoinAddGrpId[i], 4, resultCoinAddSprId[i][4]);
        HuSprPosSet(resultCoinAddGrpId[i], 4, 60.0f, -25.0f);
        HuSprGrpPosSet(resultCoinAddGrpId[i], resultCoinAddPosTbl[(i * 2)], resultCoinAddPosTbl[(i * 2) + 1]);
        ResultCoinAddNumSet(resultCoinAddGrpId[i], 9);
        HuSprGrpScaleSet(resultCoinAddGrpId[i], 0.0f, 0.0f);
    }
    for (i = 0; i < 4; i++) {
        charNo = GWPlayerCfg[i].character;
        resultCharAnim[charNo][0] = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x22) + (charNo * 3));
        resultCharAnim[charNo][1] = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x23) + (charNo * 3));
        resultCharAnim[charNo][2] = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x24) + (charNo * 3));
        for (j = 0; j < 4; j++) {
            resultCubeMdlId[charNo][j] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x00) + j);
            Hu3DModelScaleSet(resultCubeMdlId[charNo][j], 1.1f, 1.1f, 1.1f);
            Hu3DAnimCreate(resultCharAnim[charNo][0], resultCubeMdlId[charNo][j], "ys22");
            Hu3DModelAttrSet(resultCubeMdlId[charNo][j], HU3D_ATTR_DISPOFF);
        }
    }
    for (i = 0; i < 4; i++) {
        resultRankAnim[i] = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x16) + i);
    }
    resultRankGrpId = HuSprGrpCreate(4);
    for (i = 0; i < 4; i++) {
        sprId = HuSprCreate(resultRankAnim[resultRank[i]], i, 0);
        HuSprGrpMemberSet(resultRankGrpId, i, sprId);
        HuSprPosSet(resultRankGrpId, i, resultRankPosTbl[(i * 2)], resultRankPosTbl[(i * 2) + 1]);
        ResultSprNumSet(resultNumGrpId[(i * 2)], GWStarsGet(resultOrder[i]));
        ResultSprNumSet(resultNumGrpId[(i * 2) + 1], BoardPlayerCoinsGet(resultOrder[i]));
        charNo = GWPlayerCfg[resultOrder[i]].character;
        Hu3D2Dto3D(&resultCharPosTbl[i], 1, &pos);
        Hu3DModelPosSetV(resultCubeMdlId[charNo][resultRank[i]], &pos);
        Hu3DModelAttrReset(resultCubeMdlId[charNo][resultRank[i]], HU3D_ATTR_DISPOFF);
    }
    for (i = 4; i <= 11; i++) {
        Hu3D2Dto3D(&resultModel[i].pos, 1, &pos);
        Hu3DModelPosSetV(stageMdlId[i], &pos);
        Hu3D3Dto2D(&pos, 1, &pos);
    }
    mdlId = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x04));
    for (i = 0; i < 4; i++) {
        j = Hu3DModelLink(mdlId);
        charShadowMdlId[i] = j;
        pos = resultCharPosTbl[i];
        pos.x += 5.0f;
        pos.y += 3.0f;
        pos.z += 200.0f;
        Hu3D2Dto3D(&pos, 1, &pos);
        Hu3DModelPosSetV(j, &pos);
        Hu3DModelScaleSet(j, 1.5f, 1.5f, 1.5f);
    }
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    mdlId = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x07));
    for (i = 0; i < 8; i++) {
        j = Hu3DModelLink(mdlId);
        statShadowMdlId[i] = j;
        pos = resultModel[i + 4].pos;
        pos.x += 5.0f;
        pos.y += 3.0f;
        pos.z += 200.0f;
        Hu3D2Dto3D(&pos, 1, &pos);
        Hu3DModelPosSetV(j, &pos);
        Hu3DModelScaleSet(j, 1.5f, 1.5f, 1.5f);
    }
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    resultCrownAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x1C));
    resultCrownGrpId = HuSprGrpCreate(4);
    for (i = 0; i < 4; i++) {
        sprId = HuSprCreate(resultCrownAnim, i, 0);
        HuSprGrpMemberSet(resultCrownGrpId, i, sprId);
        HuSprScaleSet(resultCrownGrpId, i, 0.0f, 0.0f);
        HuSprPosSet(resultCrownGrpId, i, resultCharPosTbl[i].x - 4.0f, resultCharPosTbl[i].y - 35.0f);
        HuSprAttrSet(resultCrownGrpId, i, 4);
    }
    grpId = HuSprGrpCreate(4);
    teamResultGrpId = grpId;
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x3F));
    sprId = HuSprCreate(anim, 100, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprAttrSet(grpId, 0, 4);
    HuSprDrawNoSet(grpId, 0, 127);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x40));
    sprId = HuSprCreate(anim, 90, 0);
    HuSprGrpMemberSet(grpId, 1, sprId);
    HuSprAttrSet(grpId, 1, 4);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x41));
    sprId = HuSprCreate(anim, 80, 0);
    HuSprGrpMemberSet(grpId, 2, sprId);
    HuSprAttrSet(grpId, 2, 4);
    HuSprDrawNoSet(grpId, 2, 127);
    anim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x42));
    sprId = HuSprCreate(anim, 80, 0);
    HuSprGrpMemberSet(grpId, 3, sprId);
    HuSprAttrSet(grpId, 3, 4);
    HuSprDrawNoSet(grpId, 3, 127);
    (void)sprId;
}

static void ResultStatAdd(void)
{
    float scale;
    float addTime;

    s16 i;
    s16 time;
    s16 maxTime;
    s16 crownTime;
    s32 seNo;
    s32 sePlayF;
    s32 doneF[4];
    float coinRot[4];
    s16 coinNum[5];

    ResultCoinNumGet(coinNum);
    for (i = 0; i < 4; i++) {
        ResultCoinAddNumSet(resultCoinAddGrpId[i], coinNum[resultOrder[i]]);
        doneF[i] = 0;
    }
    maxTime = (resultFastF) ? 3 : 10;
    for (time = 0; time <= maxTime; time++) {
        scale = sind((90.0 / maxTime) * time);
        for (i = 0; i < 4; i++) {
            HuSprGrpScaleSet(resultCoinAddGrpId[i], scale, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuSprGrpScaleSet(resultCoinAddGrpId[i], 1.0f, 1.0f);
    }
    for (crownTime = 0; crownTime <= 14;) {
        for (i = 0; i < 4; i++) {
            if (GWPlayerCoinWinGet(resultOrder[i]) >= 10) {
                HuSprAttrReset(resultCrownGrpId, i, 4);
            }
            HuSprScaleSet(resultCrownGrpId, i, sind((120.0f / 14.0f) * crownTime) * (0.8 * (1.0 / sin((M_PI * 2) / 3))),
                0.8 * (sind((120.0f / 14.0f) * crownTime) * (1.0 / sin((M_PI * 2) / 3))));
        }
        crownTime += (resultFastF) ? 2 : 1;
        HuPrcVSleep();
    }
    if (!resultFastF) {
        HuPrcSleep(15);
    }
    for (i = 0; i < 4; i++) {
        coinRot[i] = 0.0f;
    }
    for (i = time = 0; i < 4; i++) {
        time += coinNum[i];
    }
    seNo = -1;
    if (time) {
        seNo = HuAudFXPlay(23);
    }
    time = 0;
    addTime = time;
    time = 0;
    while (1) {
        sePlayF = FALSE;
        addTime += (resultFastF) ? 1.0f : 0.2f;
        time = addTime;
        for (i = maxTime = 0; i < 4; i++) {
            if (coinNum[resultOrder[i]] - time <= 0) {
                if (!doneF[resultOrder[i]] && coinNum[resultOrder[i]] != 0) {
                    doneF[resultOrder[i]] = 1;
                    if (!sePlayF) {
                        HuAudFXPlay(9);
                        sePlayF = TRUE;
                    }
                }

                maxTime++;
                ResultCoinAddNumSet(resultCoinAddGrpId[i], 0);
                ResultSprNumSet(resultNumGrpId[(i * 2) + 1], coinNum[resultOrder[i]] + BoardPlayerCoinsGet(resultOrder[i]));
                if (!coinRot[i]) {
                    continue;
                }
                coinRot[i] += 20.0f;
                if (coinRot[i] >= 360.0f) {
                    coinRot[i] -= 360.0f;
                }
                Hu3DModelRotSet(stageMdlId[i + 8], 0.0f, coinRot[i], 0.0f);
            }
            else {
                ResultCoinAddNumSet(resultCoinAddGrpId[i], coinNum[resultOrder[i]] - time);
                ResultSprNumSet(resultNumGrpId[(i * 2) + 1], (s32)time + BoardPlayerCoinsGet(resultOrder[i]));
                coinRot[i] += 20.0f;
                if (coinRot[i] >= 360.0f) {
                    coinRot[i] -= 360.0f;
                }
                Hu3DModelRotSet(stageMdlId[i + 8], 0.0f, coinRot[i], 0.0f);
            }
        }
        if (maxTime == 4) {
            break;
        }
        HuPrcVSleep();
    }
    if (seNo != -1) {
        HuAudFXStop(seNo);
    }
    maxTime = 0;
    while (1) {
        for (i = time = 0; i < 4; i++) {
            if (coinRot[i]) {
                coinRot[i] += 20.0f;
                if (coinRot[i] >= 360.0f) {
                    coinRot[i] -= 360.0f;
                }
                Hu3DModelRotSet(stageMdlId[i + 8], 0.0f, coinRot[i], 0.0f);
            }
            else {
                time++;
            }
        }
        if (time >= 4) {
            break;
        }
        HuPrcVSleep();
        maxTime++;
    }
    if (maxTime < 30) {
        HuPrcSleep(30 - maxTime);
    }
    maxTime = (resultFastF) ? 3 : 10;
    for (time = 0; time <= maxTime; time++) {
        scale = cosd((90.0 / maxTime) * time);
        for (i = 0; i < 4; i++) {
            HuSprGrpScaleSet(resultCoinAddGrpId[i], scale, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuSprGrpScaleSet(resultCoinAddGrpId[i], 0.0f, 0.0f);
    }
}
static void ResultOrderApply(void)
{
    float weight;
    s16 i;
    s16 charNo;
    s16 num;
    s16 scaleTime;
    s16 rankTime;
    s16 doneNum;
    s16 sePlayF;
    s16 sprId;
    float cubeRot[4];
    Vec cubePos;
    s32 voiceSeNo[4] = { -1, -1, -1, -1 };
    s16 order[4];
    s16 statOrder[4];
    s16 statRank[4];
    s16 rank[4];
    s16 coin[4];
    s16 star[4];
    for (i = 0; i < 4; i++) {
        order[i] = statOrder[i] = resultOrder[i];
        rank[i] = statRank[i] = resultRank[i];
        coin[i] = BoardPlayerCoinsGet(resultOrder[i]);
        star[i] = GWStarsGet(resultOrder[i]);
    }
    ResultOrderSet();
    for (i = 0; i < 4; i++) {
        if (order[i] != resultOrder[i] || rank[i] != resultRank[i]) {
            break;
        }
    }
    if (i == 4) {
        resultReorderF = 1;
        return;
    }
    rankNewGrpId = HuSprGrpCreate(4);
    for (i = 0; i < 4; i++) {
        sprId = HuSprCreate(resultRankAnim[resultRank[i]], i, 0);
        HuSprGrpMemberSet(rankNewGrpId, i, sprId);
        HuSprPosSet(rankNewGrpId, i, resultRankPosTbl[(i * 2)], resultRankPosTbl[(i * 2) + 1]);
        HuSprAttrSet(rankNewGrpId, i, 4);
        charNo = GWPlayerCfg[resultOrder[i]].character;
        resultPlayerCubeMdlId[i] = resultCharCubeMdlId[i] = Hu3DModelLink(resultCubeMdlId[charNo][resultRank[i]]);
        Hu3D2Dto3D(&resultCharPosTbl[i], 1, &cubePos);
        Hu3DModelPosSetV(resultCharCubeMdlId[i], &cubePos);
        if (order[i] == resultOrder[i] && rank[i] == resultRank[i]) {
            Hu3DModelAttrSet(resultCubeMdlId[charNo][rank[i]], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(resultCharCubeMdlId[i], HU3D_ATTR_DISPOFF);
            Hu3DModelScaleSet(resultCharCubeMdlId[i], 1.1f, 1.1f, 1.1f);
        }
        else {
            Hu3DModelAttrSet(resultCharCubeMdlId[i], HU3D_ATTR_DISPOFF);
        }
    }
    for (i = 0; i < 4; i++) {
        cubeRot[i] = 0;
    }
    sePlayF = 0;
    scaleTime = 0;
    while (1) {
        for (doneNum = i = 0; i < 4; i++) {
            if (order[i] == resultOrder[i] && rank[i] == resultRank[i]) {
                doneNum++;
                ResultSprNumSet(resultNumGrpId[(i * 2)], GWStarsGet(resultOrder[i]));
                ResultSprNumSet(resultNumGrpId[(i * 2) + 1], BoardPlayerCoinsGet(resultOrder[i]));
            }
            else {
                if (scaleTime > (i * 20)) {
                    rankTime = scaleTime - (i * 20);
                    if (rankTime <= 20) {
                        if (rankTime <= 10) {
                            HuSprScaleSet(resultRankGrpId, i, 1.0f, cosd(9.0f * rankTime));
                        }
                        else {
                            HuSprAttrSet(resultRankGrpId, i, 4);
                            HuSprAttrReset(rankNewGrpId, i, 4);
                            HuSprScaleSet(rankNewGrpId, i, 1.0f, sind(9.0f * (rankTime - 10)));
                        }
                        weight = rankTime / 20.0f;
                        num = GWStarsGet(statOrder[i]) + (weight * (GWStarsGet(resultOrder[i]) - GWStarsGet(statOrder[i])));
                        ResultSprNumSet(resultNumGrpId[(i * 2)], num);
                        num = BoardPlayerCoinsGet(statOrder[i]) + (weight * (BoardPlayerCoinsGet(resultOrder[i]) - BoardPlayerCoinsGet(statOrder[i])));
                        ResultSprNumSet(resultNumGrpId[(i * 2) + 1], num);
                    }
                    else {
                        charNo = GWPlayerCfg[statOrder[i]].character;
                        Hu3DModelAttrSet(resultCubeMdlId[charNo][rank[i]], HU3D_ATTR_DISPOFF);
                        charNo = GWPlayerCfg[resultOrder[i]].character;
                        Hu3DModelAttrReset(resultCharCubeMdlId[i], HU3D_ATTR_DISPOFF);
                        Hu3DModelScaleSet(resultCharCubeMdlId[i], 1.1f, 1.1f, 1.1f);
                        ResultSprNumSet(resultNumGrpId[(i * 2)], GWStarsGet(resultOrder[i]));
                        ResultSprNumSet(resultNumGrpId[(i * 2) + 1], BoardPlayerCoinsGet(resultOrder[i]));
                        for (num = 0; num < 4; num++) {
                            if (statOrder[num] == resultOrder[i]) {
                                break;
                            }
                        }
                        if (resultRank[i] != statRank[num]) {
                            if (resultRank[i] < statRank[num]) {
                                Hu3DAnimCreate(resultCharAnim[charNo][1], resultCubeMdlId[charNo][resultRank[i]], "ys22");
                            }
                            else {
                                Hu3DAnimCreate(resultCharAnim[charNo][2], resultCubeMdlId[charNo][resultRank[i]], "ys22");
                            }
                            if (resultRank[i] == 0) {
                                voiceSeNo[resultOrder[i]] = HuAudPlayerVoicePlay(resultOrder[i], 293);
                            }
                            if (!sePlayF) {
                                sePlayF = 1;
                                HuAudFXPlay(27);
                            }
                        }
                        order[i] = resultOrder[i];
                        rank[i] = resultRank[i];
                    }
                }
                cubeRot[i] += 20.0f;
                if (cubeRot[i] >= 360.0f) {
                    cubeRot[i] -= 360.0f;
                }
                charNo = GWPlayerCfg[statOrder[i]].character;
                Hu3DModelRotSet(resultCubeMdlId[charNo][rank[i]], cubeRot[i] / (4 - i), cubeRot[i], 0.0f);
            }
        }
        if (scaleTime <= 10) {
            for (i = 0; i < 4; i++) {
                HuSprScaleSet(resultCrownGrpId, i, cosd(9.0f * scaleTime), cosd(9.0f * scaleTime));
            }
        }
        else {
            for (i = 0; i < 4; i++) {
                HuSprScaleSet(resultCrownGrpId, i, 0.0f, 0.0f);
            }
        }
        if (doneNum >= 4) {
            break;
        }
        if (resultFastF) {
            scaleTime += 2;
        }
        HuPrcVSleep();
        scaleTime++;
    }
    for (i = 0; i < 4; i++) {
        HuSprScaleSet(resultCrownGrpId, i, 0.0f, 0.0f);
    }
    resultReorderF = 1;
}

static void ResultSprNumSet(s16 grpId, s16 value)
{
    s16 no;
    s16 bank;
    if (value > 999) {
        value = 999;
    }
    no = 0;
    bank = value / 100;
    if (bank != 0) {
        HuSprBankSet(grpId, no, bank);
        HuSprAttrReset(grpId, no, 4);
        no++;
    }
    value -= bank * 100;
    bank = value / 10;
    if (bank != 0 || no == 1) {
        HuSprBankSet(grpId, no, bank);
        HuSprAttrReset(grpId, no, 4);
        no++;
    }
    value -= bank * 10;
    HuSprBankSet(grpId, no, value);
    HuSprAttrReset(grpId, no, 4);
    no++;
    for (bank = no; bank < 3; bank++) {
        HuSprAttrSet(grpId, bank, 4);
    }
}

static void ResultCoinAddNumSet(s16 grpId, s16 value)
{
    s16 no;
    s16 bank;
    if (value > 999) {
        value = 999;
    }
    no = 2;
    bank = value / 100;
    if (bank != 0) {
        HuSprBankSet(grpId, no, bank);
        HuSprAttrReset(grpId, no, 4);
        no++;
    }
    value -= bank * 100;
    bank = value / 10;
    if (bank != 0 || no == 3) {
        HuSprBankSet(grpId, no, bank);
        HuSprAttrReset(grpId, no, 4);
        no++;
    }
    value -= bank * 10;
    HuSprBankSet(grpId, no, value);
    HuSprAttrReset(grpId, no, 4);
    no++;
    for (bank = no; bank < 5; bank++) {
        HuSprAttrSet(grpId, bank, 4);
    }
}

static void ResultOrderSet(void)
{
    s16 i;
    s16 j;
    for (i = 0; i < 4; i++) {
        resultRank[i] = BoardPlayerRankCalc(i);
        resultOrder[i] = i;
    }
    for (j = 1; j < 4; j++) {
        for (i = 0; i < 4 - j; i++) {
            if (resultRank[i] > resultRank[i + 1]) {
                s16 temp = resultRank[i];
                resultRank[i] = resultRank[i + 1];
                resultRank[i + 1] = temp;
                temp = resultOrder[i];
                resultOrder[i] = resultOrder[i + 1];
                resultOrder[i + 1] = temp;
            }
        }
    }
}

static s32 resultBoardDirTbl[] = { DATADIR_W01, DATADIR_W02, DATADIR_W03, DATADIR_W04, DATADIR_W05, DATADIR_W06 };

void ResultBoardDataRead(void)
{
    s32 statId;
    u32 aMemP;
    if (!_CheckFlag(0x10000)) {
        resultReadEndF = 1;
        HuPrcEnd();
        while (1) {
            HuPrcVSleep();
        }
    }
    statId = HuDataDirReadAsync(DATADIR_BOARD);
    if (statId != -1) {
        while (!HuDataGetAsyncStat(statId)) {
            HuPrcVSleep();
        }
    }
    aMemP = HuAR_MRAMtoARAM(DATADIR_BOARD);
    if (aMemP) {
        while (HuARDMACheck()) {
            HuPrcVSleep();
        }
    }
    HuDataDirClose(DATADIR_BOARD);
    statId = HuDataDirReadAsync(resultBoardDirTbl[GWSystem.board]);
    if (statId != -1) {
        while (!HuDataGetAsyncStat(statId)) {
            HuPrcVSleep();
        }
    }
    resultReadEndF = 1;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void ResultCoinAdd(void)
{
    s16 i;
    s16 coinNum[5];
    ResultCoinNumGet(coinNum);
    coinNum[resultBonusPlayer] += coinNum[4];
    for (i = 0; i < 4; i++) {
        GWCoinsAdd(i, coinNum[i]);
        GWPlayerCoinWinSet(i, 0);
        GWPlayerCoinCollectSet(i, 0);
        if (mgInfoTbl[GWSystem.mg_next].type != 4) {
            GWPlayer[i].coins_mg += coinNum[i];
            if (GWPlayer[i].coins_mg > 9999) {
                GWPlayer[i].coins_mg = 9999;
            }
        }
    }
}

void ResultCoinNumGet(s16 *coinNum)
{
    s16 i;
    s32 coin;
    u32 coinMul;
    u32 coin_battle;
    s16 unkRankF;
    s16 mgType;
    float scale[4];
    s16 rank[4];
    mgType = mgInfoTbl[GWSystem.mg_next].type;
    switch (mgType) {
        case 4:
            unkRankF = 0;
            for (i = coin_battle = 0; i < 4; i++) {
                coin_battle += GWPlayerCoinBattleGet(i);
            }
            rank[0] = rank[1] = rank[2] = rank[3] = 0;
            for (i = 0; i < 4; i++) {
                rank[GWPlayerCoinWinGet(i)]++;
            }
            scale[0] = scale[1] = scale[2] = scale[3] = 0;
            if (rank[0] == 1 && rank[1] == 1 && rank[2] == 1) {
                scale[0] = 0.7f;
                scale[1] = 0.3f;
            }
            else if (rank[0] == 2) {
                scale[0] = 0.5f;
            }
            else if (rank[0] == 3) {
                scale[0] = 0.3333333f;
            }
            else if (rank[0] == 1 && rank[1] == 2) {
                scale[0] = 0.6f;
                scale[1] = 0.2f;
            }
            else if (rank[0] == 1 && rank[1] == 3) {
                scale[0] = 0.7f;
                scale[1] = 0.1f;
            }
            else if (rank[0] == 1 && rank[1] == 1 && rank[2] == 2) {
                scale[0] = 0.7f;
                scale[1] = 0.3f;
            }
            else if (rank[0] == 4) {
                scale[0] = 0.25f;
            }
            else {
                unkRankF = 1;
            }
            for (i = coin = 0; i < 4; i++) {
                if (!unkRankF) {
                    coinMul = coin_battle * scale[GWPlayerCoinWinGet(i)];
                }
                else {
                    coinMul = GWPlayerCoinBattleGet(i);
                }
                coinNum[i] = coinMul;
                coin += coinMul;
            }
            if (coin < coin_battle) {
                coinNum[4] = coin_battle - coin;
            }
            else {
                coinNum[4] = 0;
            }
            break;

        default:
            for (i = 0; i < 4; i++) {
                coin = GWPlayerCoinWinGet(i) + GWPlayerCoinCollectGet(i);
                coinMul = GWLuckyValueGet();
                if (coinMul == 0) {
                    coinMul = 1;
                }
                coin *= coinMul;
                coinNum[i] = coin;
            }
            break;
    }
}

static void SaveExec(void)
{
    s16 sprId;
    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    espInit();
    HuPrcVSleep();
    sprId = espEntry(0x860020, 5000, 0);
    espPosSet(sprId, 288.0, 240.0);
    espAttrReset(sprId, HUSPR_ATTR_DISPOFF);
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    if (GWSaveModeGet() == 2) {
        GWSaveModeSet(1);
    }
    if (GWPartyGet() == 1) {
        GWGameStat.party_continue = 1;
        SLSaveBoard();
    }
    else {
        GWGameStat.story_continue = 1;
        SLSaveBoardStory();
    }
    SLCommonSet();
    if (SLSave()) {
        saveExecF = 1;
    }
    else {
        GWSaveModeSet(1);
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
}

static s32 resultCharMdlTbl[] = { DATADIR_MARIOMDL1, DATADIR_LUIGIMDL1, DATADIR_PEACHMDL1, DATADIR_YOSHIMDL1, DATADIR_WARIOMDL1, DATADIR_DONKEYMDL1,
    DATADIR_DAISYMDL1, DATADIR_WALUIGIMDL1 };

static Vec resultTeamCharPosTbl[] = {
    { 160, 185, 500 },
    { 240, 185, 500 },
    { 160, 355, 500 },
    { 240, 355, 500 },
};

static void ResultTeamExec(void)
{
    s16 i;
    s16 temp;
    s16 winId;
    s16 player;
    s16 j;
    s16 cubeMdlId;
    s16 teamNo;
    Vec pos3D;
    Vec pos2D;
    s16 charNo[4];
    s16 coinNum[2];
    s16 starNum[2];
    s16 teamYPos[2];
    s16 teamPlayerNo[2];
    s16 rank[2];
    AnimData *rankAnim;
    s32 cubeNo;
    s16 rankGrpId;
    s16 rankSprId;
    s16 btnDown;
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    espAttrSet(stageSprId[0], HUSPR_ATTR_DISPOFF);
    espAttrSet(stageSprId[1], HUSPR_ATTR_DISPOFF);
    for (i = 0; i < 2; i++) {
        Hu3DModelAttrSet(stageMdlId[i + 6], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stageMdlId[i + 10], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 4; i++) {
        espAttrSet(stageSprId[i + 6], HUSPR_ATTR_DISPOFF);
    }
    for (i = 4; i < 8; i++) {
        Hu3DModelAttrSet(statShadowMdlId[i], HU3D_ATTR_DISPOFF);
    }
    for (i = 4; i < 8; i++) {
        HuSprGrpTPLvlSet(resultNumGrpId[i], 0.0f);
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            Hu3DModelAttrSet(resultCubeMdlId[GWPlayerCfg[i].character][j], HU3D_ATTR_DISPOFF);
        }
        Hu3DModelAttrSet(resultPlayerCubeMdlId[i], HU3D_ATTR_DISPOFF);
    }
    HuSprGrpKill(resultCrownGrpId);
    HuSprGrpKill(resultRankGrpId);
    if (rankNewGrpId != -1) {
        HuSprGrpKill(rankNewGrpId);
    }
    coinNum[0] = coinNum[1] = 0;
    starNum[0] = starNum[1] = 0;
    teamPlayerNo[0] = 0;
    teamPlayerNo[1] = 2;
    for (i = 0; i < 4; i++) {
        teamNo = GWPlayer[i].team;
        coinNum[teamNo] += BoardPlayerCoinsGet(i);
        starNum[teamNo] += GWStarsGet(i);
        charNo[teamPlayerNo[teamNo]++] = GWPlayerCfg[i].character;
    }
    rank[0] = 0;
    rank[1] = 1;
    if (starNum[0] > starNum[1]) {
        resultTeamOrder = 0;
    }
    else {
        if (starNum[0] == starNum[1]) {
            if (coinNum[0] > coinNum[1]) {
                resultTeamOrder = 0;
            }
            else if (coinNum[0] == coinNum[1]) {
                rank[0] = rank[1] = 0;
                resultTeamOrder = 0;
            }
            else {
                resultTeamOrder = 1;
            }
        }
        else {
            resultTeamOrder = 1;
        }
    }
    HuSprAttrReset(teamResultGrpId, 0, 4);
    HuSprAttrReset(teamResultGrpId, 1, 4);
    HuSprPosSet(teamResultGrpId, 1, 0, -180);
    HuSprAttrReset(teamResultGrpId, 2, 4);
    HuSprAttrReset(teamResultGrpId, 3, 4);
    if (resultTeamOrder == 0) {
        teamYPos[0] = -55;
        teamYPos[1] = 115;
    }
    else {
        teamYPos[0] = 115;
        teamYPos[1] = -55;
        temp = charNo[0];
        charNo[0] = charNo[2];
        charNo[2] = temp;
        temp = charNo[1];
        charNo[1] = charNo[3];
        charNo[3] = temp;
        temp = coinNum[0];
        coinNum[0] = coinNum[1];
        coinNum[1] = temp;
        temp = starNum[0];
        starNum[0] = starNum[1];
        starNum[1] = temp;
    }
    HuSprPosSet(teamResultGrpId, 2, 0, teamYPos[0]);
    HuSprPosSet(teamResultGrpId, 3, 0, teamYPos[1]);
    HuSprGrpPosSet(teamResultGrpId, 288, 240);
    for (i = 0; i < 4; i++) {
        if (i < 2) {
            cubeNo = 0;
        }
        else {
            cubeNo = 1;
        }
        cubeMdlId = resultCubeMdlId[charNo[i]][cubeNo];
        Hu3DAnimCreate(resultCharAnim[charNo[i]][0], cubeMdlId, "ys22");
        Hu3DModelAttrReset(cubeMdlId, HU3D_ATTR_DISPOFF);
        Hu3D2Dto3D(&resultTeamCharPosTbl[i], 1, &pos3D);
        Hu3DModelPosSetV(cubeMdlId, &pos3D);
        Hu3DModelRotSet(cubeMdlId, 0, 0, 0);
        pos2D = resultTeamCharPosTbl[i];
        pos2D.y += 5.0f;
        pos2D.x += 3.0f;
        pos2D.z += 200.0f;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        Hu3DModelPosSetV(charShadowMdlId[i], &pos3D);
    }
    rankGrpId = HuSprGrpCreate(2);
    for (i = 0; i < 2; i++) {
        rankAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x16) + rank[i]);
        rankSprId = HuSprCreate(rankAnim, i, 0);
        HuSprGrpMemberSet(rankGrpId, i, rankSprId);
        HuSprPosSet(rankGrpId, i, (resultTeamCharPosTbl[i * 2].x) - 80.0f, resultTeamCharPosTbl[i * 2].y);
        pos2D = resultTeamCharPosTbl[i * 2];
        pos2D.x += 180.0f;
        pos2D.y -= 35.0f;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        Hu3DModelPosSetV(stageMdlId[i + 4], &pos3D);
        pos2D.y += 5.0f;
        pos2D.x += 3.0f;
        pos2D.z += 200.0f;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        Hu3DModelPosSetV(statShadowMdlId[i * 2], &pos3D);
        espPosSet(stageSprId[(i * 2) + 2], 230.0f + resultTeamCharPosTbl[i * 2].x, resultTeamCharPosTbl[i * 2].y - 35.0f);
        ResultSprNumSet(resultNumGrpId[i * 2], starNum[i]);
        HuSprGrpPosSet(resultNumGrpId[i * 2], 320.0f + resultTeamCharPosTbl[i * 2].x, resultTeamCharPosTbl[i * 2].y - 35.0f);
        pos2D = resultTeamCharPosTbl[i * 2];
        pos2D.x += 180.0f;
        pos2D.y += 35.0f;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        Hu3DModelPosSetV(stageMdlId[i + 8], &pos3D);
        pos2D.y += 5.0f;
        pos2D.x += 3.0f;
        pos2D.z += 200.0f;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        Hu3DModelPosSetV(statShadowMdlId[(i * 2) + 1], &pos3D);
        espPosSet(stageSprId[(i * 2) + 3], 230.0f + resultTeamCharPosTbl[i * 2].x, 35.0f + resultTeamCharPosTbl[i * 2].y);
        ResultSprNumSet(resultNumGrpId[(i * 2) + 1], coinNum[i]);
        HuSprGrpPosSet(resultNumGrpId[(i * 2) + 1], 320.0f + resultTeamCharPosTbl[i * 2].x, 35.0f + resultTeamCharPosTbl[i * 2].y);
    }
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    winId = HuWinCreate(-10000.0f, 400.0f, 320, 40, 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinBGTPLvlSet(winId, 0);
    HuWinPriSet(winId, 5);
    HuWinAttrSet(winId, 0x800);
    HuWinMesSet(winId, MAKE_MESSID(0x24, 0x07));
    HuPrcSleep(4);
    i = 0;
    while (1) {
        if (resultSkipF && i > 120) {
            break;
        }
        for (player = btnDown = 0; player < 4; player++) {
            if (!GWPlayerCfg[player].iscom) {
                btnDown |= HuPadBtnDown[GWPlayerCfg[player].pad_idx];
            }
        }
        if (btnDown & PAD_BUTTON_A) {
            HuAudFXPlay(28);
            break;
        }
        HuPrcVSleep();
        i++;
    }
    HuWinKill(winId);
}

void CameraDebug(omObjData *object)
{
    Vec pos;
    Vec offset;
    Vec dir;
    Vec yOfs;

    float z_rot;
    s8 stickPos;

    if (HuPadBtn[0] & PAD_BUTTON_UP) {
        CRot.x += 2.0f;
    }
    if (HuPadBtn[0] & PAD_BUTTON_DOWN) {
        CRot.x -= 2.0f;
    }
    if (HuPadBtn[0] & PAD_BUTTON_LEFT) {
        CRot.y += 2.0f;
    }
    if (HuPadBtn[0] & PAD_BUTTON_RIGHT) {
        CRot.y -= 2.0f;
    }
    if (HuPadBtnDown[0] & PAD_BUTTON_B) {
        OSReport("CRot   %f,%f,%f\n", CRot.x, CRot.y, CRot.z);
        OSReport("Center %f,%f,%f\n", Center.x, Center.y, Center.z);
        OSReport("CZoom  %f\n", CZoom);
    }

    CZoom += HuPadTrigL[0] / 2;
    CZoom -= HuPadTrigR[0] / 2;

    pos.x = Center.x + CZoom * (sind(CRot.y) * cosd(CRot.x));
    pos.y = Center.y + CZoom * -sind(CRot.x);
    pos.z = Center.z + CZoom * (cosd(CRot.y) * cosd(CRot.x));
    offset.x = Center.x - pos.x;
    offset.y = Center.y - pos.y;
    offset.z = Center.z - pos.z;
    dir.x = (sind(CRot.y) * sind(CRot.x));
    dir.y = cosd(CRot.x);
    dir.z = (cosd(CRot.y) * sind(CRot.x));
    z_rot = CRot.z;
    yOfs.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * cosd(z_rot))
        + dir.y * (offset.x * offset.y * (1.0f - cosd(z_rot)) - offset.z * sind(z_rot))
        + dir.z * (offset.x * offset.z * (1.0f - cosd(z_rot)) + offset.y * sind(z_rot));

    yOfs.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * cosd(z_rot))
        + dir.x * (offset.x * offset.y * (1.0f - cosd(z_rot)) + offset.z * sind(z_rot))
        + dir.z * (offset.y * offset.z * (1.0f - cosd(z_rot)) - offset.x * sind(z_rot));

    yOfs.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * cosd(z_rot))
        + (dir.x * (offset.x * offset.z * (1.0 - cosd(z_rot)) - offset.y * sind(z_rot))
            + dir.y * (offset.y * offset.z * (1.0 - cosd(z_rot)) + offset.x * sind(z_rot)));

    VECCrossProduct(&dir, &offset, &offset);
    VECNormalize(&offset, &offset);
    stickPos = (HuPadSubStkX[0] & 0xF8);
    if (stickPos != 0) {
        Center.x += 0.05f * (offset.x * stickPos);
        Center.y += 0.05f * (offset.y * stickPos);
        Center.z += 0.05f * (offset.z * stickPos);
    }
    VECNormalize(&yOfs, &offset);
    stickPos = -(HuPadSubStkY[0] & 0xF8);
    if (stickPos != 0) {
        Center.x += 0.05f * (offset.x * stickPos);
        Center.y += 0.05f * (offset.y * stickPos);
        Center.z += 0.05f * (offset.z * stickPos);
    }
}
