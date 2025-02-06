#include "dolphin.h"
#include "ext_math.h"

#include "game/armem.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "game/gamework_data.h"

#include "REL/resultdll.h"

#define COIN_EFFECT_MAX 180

static StageModel resultBattleModel[] = { { DATA_MAKE_NUM(DATADIR_RESULT, 0x08), 0, 0, -1, -1, { -300, 0, 0 }, { 0, 0, 0 }, { 0.9f, 0.9f, 0.9f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x09), 0, 0, -1, -1, { -100, 0, 0 }, { 0, 0, 0 }, { 0.9f, 0.9f, 0.9f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0A), 0, 0, -1, -1, { 100, 0, 0 }, { 0, 0, 0 }, { 0.9f, 0.9f, 0.9f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0A), 0, 0, -1, -1, { 300, 0, 0 }, { 0, 0, 0 }, { 0.9f, 0.9f, 0.9f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0B), 0, 0, -1, -1, { -300, 1000, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0B), 0, 0, -1, -1, { -100, 1000, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0B), 0, 0, -1, -1, { 100, 1000, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0B), 0, 0, -1, -1, { 300, 1000, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0D), 0, 0, -1, -1, { 5000, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0E), 0, 1, -1, 8, { 0, 0, 0 }, { 0, 0, 0 }, { 1.0f, 1.0f, 1.0f } },
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x0F), 0x40000002, 0, -1, -1, { 5000, 0, 0 }, { 0, 0, 0 }, { 2.0f, 2.0f, 2.0f } },
    { -1, 0, 0, -1, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 } } };

static StageSprite resultBattleSprite[] = {
    { DATA_MAKE_NUM(DATADIR_RESULT, 0x43), 0, 10, 288, 240, { 255, 255, 255, 255 } },
    { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } },
};

static HsfanimStruct00 resultBattleEffParMan = { 80, { 0, 0 }, 3, 30, 90, { 0, -0.2, 0 }, 5.0f, 0.95f, 10.0f, 0.995f, 2,
    {
        { 255, 192, 112, 255 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    {
        { 128, 128, 128, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    }
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

static Vec playerPosTbl[] = { { -300, 270, 0 }, { -100, 180, 500 }, { 100, 90, 500 }, { 300, 0, 500 } };

s16 lbl_1_data_820[] = { -284, 148, -84, 233, 116, 318, 316, 403 };

static s32 bomheiCubeMdlTbl[] = { DATA_MAKE_NUM(DATADIR_RESULT, 0x08), DATA_MAKE_NUM(DATADIR_RESULT, 0x09), DATA_MAKE_NUM(DATADIR_RESULT, 0x0A),
    DATA_MAKE_NUM(DATADIR_RESULT, 0x0A) };

static float coinEffectYOfs[] = { 130, 150, 170, 150, 150, 130, 170, 190 };

static float coinAddYOfs[] = { 130, 150, 180, 150, 150, 170, 180, 210 };

static float coinBlankYOfs[] = { 140, 160, 180, 150, 150, 120, 180, 210 };

static s16 coinNumXOfs[] = { 8, 0, -8 };

typedef struct CoinEffect_s {
    s16 playerNo;
    s16 rank;
    Vec pos;
    Vec rotVel;
    float velY;
} CoinEffect;

u8 lbl_1_bss_19F8[32];
static s16 resultBattleOrder[4];
static s16 resultBattleRank[4];
static s16 coinNumGrpId[4];
static s16 coinNumSprId[4][5];
static s16 resultBattleCharMdl[4];
static s16 resultBattleCharMot[4][4];
static s16 coinEffectMdlId[COIN_EFFECT_MAX];
s16 lbl_1_bss_181C[6];
static s16 resultBattleEffParManId[4];
static CoinEffect coinEffectData[COIN_EFFECT_MAX];
static s32 resultBattleSkipF;

static void ResultBattleIdle(void);
static void ResultBattleCreate(void);
static void ResultBattleStatAdd(void);

void ResultBattleMain(void)
{
    s16 playerNo;
    s16 i;
    s16 winId;
    s16 btnDown;
    Process *proc = HuPrcCurrentGet();
    HuAudSeqPlay(10);
    for (i = playerNo = 0; i < 4; i++) {
        if (GWPlayerCfg[i].iscom) {
            playerNo++;
        }
    }
    if (playerNo == 4) {
        resultBattleSkipF = 1;
    }
    else {
        resultBattleSkipF = 0;
    }
    ResultBattleCreate();
    HuPrcChildCreate(ResultBattleIdle, 100, 8192, 0, proc);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    resultReadEndF = 0;
    HuPrcChildCreate(ResultBoardDataRead, 100, 12288, 0, proc);
    HuPrcSleep(10);
    if (!resultFastF) {
        HuPrcSleep(20);
    }
    ResultBattleStatAdd();
    ResultCoinAdd();
    winId = HuWinCreate(-10000.0f, 400.0f, 320, 40, 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinBGTPLvlSet(winId, 0);
    HuWinAttrSet(winId, 0x800);
    HuWinMesSet(winId, MAKE_MESSID(0x24, 0x07));
    i = 0;
    while (1) {
        if (resultBattleSkipF && i > 120) {
            break;
        }
        for (playerNo = btnDown = 0; playerNo < 4; playerNo++) {
            if (!GWPlayerCfg[playerNo].iscom) {
                btnDown |= HuPadBtnDown[GWPlayerCfg[playerNo].pad_idx];
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
    while (!resultReadEndF) {
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
    HuAudSeqAllFadeOut(500);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    omSysPauseEnable(1);
    Hu3DParManAllKill();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

static void ResultBattleIdle(void)
{
    Vec temp;
    temp.z = 0.0f;
    temp.y = 0.0f;
    temp.x = 0.0f;
    while (1) {
        if (((HuPadBtn[0] | HuPadBtn[1] | HuPadBtn[2] | HuPadBtn[3]) & 0x100) != 0 || resultBattleSkipF != 0) {
            resultFastF = 1;
        }
        else {
            resultFastF = 0;
        }
        HuPrcVSleep();
    }
}

static void ResultBattleCoinAddShow(void);
static void ResultBattleCoinAddNumSet(s16 grpId, s16 value);
static void ResultBattleOrderSet(void);
static void CoinEffectInit(void);
static void CoinEffectAdd(s16 playerNo);
static void ResultShadowDraw(struct model_data *model, Mtx matrix);

static void ResultBattleCreate(void)
{
    s16 i;
    s16 charNo;
    s16 playerNo;
    s16 xOfs;
    AnimData *anim;
    AnimData *anim2;
    AnimData *anim3;
    s16 charMdlId;
    Vec pos;
    Vec target;
    Vec up;
    s16 coinNum[5];
    Process *proc = HuPrcCurrentGet();
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    Center.x = 0;
    Center.y = 330;
    Center.z = 0;
    CZoom = 2210;
    Hu3DShadowCreate(20, 100, 5000);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowSizeSet(192);
    target.x = target.y = target.z = 0;
    pos.x = 500;
    pos.z = 1000;
    pos.y = 2000;
    up.x = 0;
    up.y = 1;
    up.z = 0;
    Hu3DShadowPosSet(&pos, &up, &target);
    i = Hu3DHookFuncCreate(ResultShadowDraw);
    Hu3DModelPosSet(i, 0, 0, 0);
    ResultBattleOrderSet();
    ResultCoinNumGet(coinNum);
    coinNum[resultBonusPlayer] += coinNum[4];
    for (i = 0; i < 4; i++) {
        resultBattleModel[i].datanum = bomheiCubeMdlTbl[resultBattleRank[i]];
        if (resultBattleRank[i] == 3) {
            resultBattleModel[i].attr = 1;
        }
    }
    StageModelCreate(resultBattleModel);
    StageSpriteCreate(resultBattleSprite);
    espDrawNoSet(stageSprId[0], 127);
    for (i = 0; i < 4; i++) {
        Hu3DModelShadowSet(stageMdlId[i]);
    }
    for (i = 0; i < 4; i++) {
        anim = HuSprAnimRead(HuDataReadNum(resultBattleRank[i] + DATA_MAKE_NUM(DATADIR_RESULT, 0x44), MEMORY_DEFAULT_NUM));
        if (resultBattleRank[i] <= 2) {
            anim2 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x48), MEMORY_DEFAULT_NUM));
        }
        else {
            anim2 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x48), MEMORY_DEFAULT_NUM));
        }
        Hu3DAnimCreate(anim, stageMdlId[i + 4], "ys22_a0");
        Hu3DAnimCreate(anim2, stageMdlId[i + 4], "ys22_a1");
        Hu3DModelAttrSet(stageMdlId[i + 4], HU3D_MOTATTR_PAUSE);
    }
    anim = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x3D), MEMORY_DEFAULT_NUM));
    anim2 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x3B), MEMORY_DEFAULT_NUM));
    anim3 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_RESULT, 0x3C), MEMORY_DEFAULT_NUM));
    for (i = 0; i < 4; i++) {
        if (coinNum[resultBattleOrder[i]] >= 100) {
            xOfs = coinNumXOfs[2];
        }
        else if (coinNum[resultBattleOrder[i]] >= 10) {
            xOfs = coinNumXOfs[1];
        }
        else {
            xOfs = coinNumXOfs[0];
        }
        coinNumGrpId[i] = HuSprGrpCreate(5);
        coinNumSprId[i][0] = HuSprCreate(anim, 10, 0);
        HuSprGrpMemberSet(coinNumGrpId[i], 0, coinNumSprId[i][0]);
        HuSprPosSet(coinNumGrpId[i], 0, 17, -32);
        coinNumSprId[i][1] = HuSprCreate(anim2, 0, 0);
        HuSprGrpMemberSet(coinNumGrpId[i], 1, coinNumSprId[i][1]);
        HuSprPosSet(coinNumGrpId[i], 1, xOfs, -36);
        coinNumSprId[i][2] = HuSprCreate(anim3, 0, 0);
        HuSprGrpMemberSet(coinNumGrpId[i], 2, coinNumSprId[i][2]);
        HuSprPosSet(coinNumGrpId[i], 2, xOfs + 16, -36);
        coinNumSprId[i][3] = HuSprCreate(anim3, 0, 0);
        HuSprGrpMemberSet(coinNumGrpId[i], 3, coinNumSprId[i][3]);
        HuSprPosSet(coinNumGrpId[i], 3, xOfs + 32, -36);
        coinNumSprId[i][4] = HuSprCreate(anim3, 0, 0);
        HuSprGrpMemberSet(coinNumGrpId[i], 4, coinNumSprId[i][4]);
        HuSprPosSet(coinNumGrpId[i], 4, xOfs + 48, -36);
        HuSprGrpPosSet(coinNumGrpId[i], 0, 0);
        ResultBattleCoinAddNumSet(coinNumGrpId[i], 9);
        HuSprGrpScaleSet(coinNumGrpId[i], 0, 0);
    }
    (void)anim3;
    Hu3DMotionSet(stageMdlId[8], stageMotId[9]);
    Hu3DModelAttrSet(stageMdlId[8], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(stageMdlId[8]);
    for (i = 0; i < COIN_EFFECT_MAX; i++) {
        if (i == 0) {
            coinEffectMdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_RESULT, 0x0C));
        }
        else {
            coinEffectMdlId[i] = Hu3DModelLink(coinEffectMdlId[0]);
        }
        Hu3DModelScaleSet(coinEffectMdlId[i], 0.5f, 0.5f, 0.5f);
        Hu3DModelAttrSet(coinEffectMdlId[i], HU3D_ATTR_DISPOFF);
    }
    CoinEffectInit();
    anim = HuSprAnimRead(HuAR_ARAMtoMRAMFileRead(DATA_MAKE_NUM(DATADIR_EFFECT, 4), MEMORY_DEFAULT_NUM, HEAP_DATA));
    for (i = 0; i < 4; i++) {
        resultBattleEffParManId[i] = Hu3DParManCreate(anim, 300, &resultBattleEffParMan);
        Hu3DParManAttrSet(resultBattleEffParManId[i], 0x65);
        Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(resultBattleEffParManId[i]), 1);
        Hu3DParManRotSet(resultBattleEffParManId[i], 90, 0, 0);
    }
    HuDataDirClose(DATADIR_RESULT);
    for (i = 0; i < 4; i++) {
        playerNo = resultBattleOrder[i];
        charNo = GWPlayerCfg[resultBattleOrder[i]].character;
        charMdlId = CharModelCreate(charNo, 2);
        resultBattleCharMdl[playerNo] = charMdlId;
        resultBattleCharMot[playerNo][0] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
        resultBattleCharMot[playerNo][1] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17));
        resultBattleCharMot[playerNo][2] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x49));
        CharModelVoiceEnableSet(charNo, resultBattleCharMot[playerNo][1], 0);
        CharModelMotionSet(charNo, resultBattleCharMot[playerNo][0]);
        Hu3DModelPosSet(charMdlId, playerPosTbl[i].x, playerPosTbl[resultBattleRank[i]].y, 0);
        Hu3DModelAttrSet(charMdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelShadowSet(charMdlId);
    }
    CharModelDataClose(-1);
}

static Vec cameraShakeOfs[] = { { 8, 0, 0 }, { 0, 8, 0 }, { 10, 5, 0 }, { -5, 10, 0 }, { 0, -8, 0 }, { 8, 10, 0 }, { -10, 8, 0 }, { 15, 0, 0 } };

static void ResultBattleStatAdd(void)
{
    s16 i;
    s16 time;
    s16 done_cnt;
    float pos_y;
    s16 coinNum[5];
    s16 delay[4];
    ResultCoinNumGet(coinNum);
    for (time = 0; time <= 5; time++) {
        pos_y = ((5 - time) * 50) + 580;
        for (i = 0; i < 4; i++) {
            Hu3DModelPosSet(stageMdlId[i + 4], playerPosTbl[i].x, pos_y, 0);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        Hu3DModelAttrReset(stageMdlId[i + 4], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(stageMdlId[i + 4], 1.5f);
    }
    HuPrcSleep(35);
    for (i = 0; i < 4; i++) {
        if (coinNum[resultBattleOrder[i]] > 0) {
            Hu3DParManAttrReset(resultBattleEffParManId[i], 1);
            delay[i] = frandmod(10);
        }
        else {
            delay[i] = 0;
        }
        Hu3DParManPosSet(resultBattleEffParManId[i], playerPosTbl[i].x, 610.0f, 0.0f);
    }
    while (1) {
        for (i = done_cnt = 0; i < 4; i++) {
            if (delay[i]) {
                delay[i]--;
                continue;
            }
            if (coinNum[resultBattleOrder[i]] <= 0) {
                Hu3DParManAttrSet(resultBattleEffParManId[i], 1);
                done_cnt++;
            }
            else {
                CoinEffectAdd(i);
                coinNum[resultBattleOrder[i]]--;
                if (coinNum[resultBattleOrder[i]] <= 10) {
                    delay[i] = 4;
                }
                else {
                    if (coinNum[resultBattleOrder[i]] <= 20) {
                        delay[i] = 3;
                    }
                    else {
                        if (coinNum[resultBattleOrder[i]] <= 40) {
                            delay[i] = 2;
                        }
                        else {
                            delay[i] = 1;
                        }
                    }
                }
            }
        }
        if (done_cnt == 4) {
            break;
        }
        HuPrcVSleep();
    }
    if (coinNum[4]) {
        HuPrcSleep(20);
        Hu3DModelRotSet(stageMdlId[8], 0, -90, 0);
        Hu3DModelScaleSet(stageMdlId[8], 0.8f, 0.8f, 0.8f);
        Hu3DMotionSpeedSet(stageMdlId[8], 2.0f);
        for (i = 0; i <= 40; i++) {
            Hu3DModelPosSet(stageMdlId[8], 500.0f * (1.0f - (i / 40.0f)), 0, 100.0f);
            HuPrcVSleep();
        }
        HuAudFXPlay(828);
        Hu3DModelAttrReset(stageMdlId[10], HU3D_MOTATTR_PAUSE);
        Hu3DModelPosSet(stageMdlId[10], 0, 0, 200);
        for (i = 0; i < Hu3DMotionMaxTimeGet(stageMdlId[10]); i++) {
            if (i > 10) {
                Hu3DModelAttrSet(stageMdlId[8], HU3D_ATTR_DISPOFF);
            }
            Center.x = cameraShakeOfs[(i / 2) & 0x7].x;
            Center.y = 330.0f + cameraShakeOfs[(i / 2) & 0x7].y;
            Center.z = cameraShakeOfs[(i / 2) & 0x7].z;
            espPosSet(stageSprId[0], 288.0f + cameraShakeOfs[(i / 2) & 0x7].x, 240.0f - cameraShakeOfs[(i / 2) & 0x7].y);
            HuPrcVSleep();
        }
        espPosSet(stageSprId[0], 288.0, 240.0);
        Center.x = 0;
        Center.y = 330;
        Center.z = 0;
        delay[0] = 10;
        for (i = 0; i < 4; i++) {
            if (resultBonusPlayer == resultBattleOrder[i]) {
                break;
            }
        }
        Hu3DParManAttrReset(resultBattleEffParManId[i], 1);
        while (1) {
            if (delay[0] != 0) {
                delay[0]--;
                HuPrcVSleep();
                continue;
            }
            if (coinNum[4] <= 0) {
                Hu3DParManAttrSet(resultBattleEffParManId[i], 1);
                break;
            }
            CoinEffectAdd(i);
            coinNum[4]--;
            delay[0] = 5;
            HuPrcVSleep();
        }
        Hu3DParManAttrSet(resultBattleEffParManId[i], 1);
    }
    ResultCoinNumGet(coinNum);
    coinNum[resultBonusPlayer] += coinNum[4];
    for (i = 0; i < 4; i++) {
        if (coinNum[resultBattleOrder[i]]) {
            CharModelMotionShiftSet(GWPlayerCfg[resultBattleOrder[i]].character, resultBattleCharMot[resultBattleOrder[i]][1], 0, 4, HU3D_MOTATTR_NONE);
            HuAudPlayerVoicePlay(resultBattleOrder[i], 293);
        }
        else {
            CharModelMotionShiftSet(GWPlayerCfg[resultBattleOrder[i]].character, resultBattleCharMot[resultBattleOrder[i]][2], 0, 4, HU3D_MOTATTR_NONE);
        }
    }
    HuPrcSleep(20);
    ResultBattleCoinAddShow();
    HuPrcSleep(120);
}

static void ResultBattleCoinAddShow(void)
{
    s16 i;
    s16 time;
    s16 speed;
    s16 coinNum[5];
    Vec pos3D;
    Vec pos2D;
    ResultCoinNumGet(coinNum);
    coinNum[resultBonusPlayer] += coinNum[4];
    for (i = 0; i < 4; i++) {
        ResultBattleCoinAddNumSet(coinNumGrpId[i], coinNum[resultBattleOrder[i]]);
        pos3D.x = playerPosTbl[i].x;
        if (coinNum[resultBattleOrder[i]]) {
            pos3D.y = playerPosTbl[resultBattleRank[i]].y + coinAddYOfs[GWPlayerCfg[resultBattleOrder[i]].character];
        }
        else {
            pos3D.y = playerPosTbl[resultBattleRank[i]].y + coinBlankYOfs[GWPlayerCfg[resultBattleOrder[i]].character];
        }
        pos3D.z = 0;
        Hu3D3Dto2D(&pos3D, 1, &pos2D);
        HuSprGrpPosSet(coinNumGrpId[i], pos2D.x, pos2D.y);
    }
    speed = (resultFastF) ? 3 : 10;
    for (time = 0; time <= speed; time++) {
        float scale = sind((90.0 / speed) * time);
        for (i = 0; i < 4; i++) {
            HuSprGrpScaleSet(coinNumGrpId[i], scale, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuSprGrpScaleSet(coinNumGrpId[i], 1.0f, 1.0f);
    }
}

static void ResultBattleCoinAddNumSet(s16 grpId, s16 value)
{
    s16 no;
    s16 bank;
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

static void ResultBattleOrderSet(void)
{
    s16 i;
    s16 j;
    for (i = 0; i < 4; i++) {
        resultBattleRank[i] = GWPlayerCoinWinGet(i);
        resultBattleOrder[i] = i;
    }
    for (j = 1; j < 4; j++) {
        for (i = 0; i < 4 - j; i++) {
            if (resultBattleRank[i] > resultBattleRank[i + 1]) {
                s16 temp;
                temp = resultBattleRank[i];
                resultBattleRank[i] = resultBattleRank[i + 1];
                resultBattleRank[i + 1] = temp;
                temp = resultBattleOrder[i];
                resultBattleOrder[i] = resultBattleOrder[i + 1];
                resultBattleOrder[i + 1] = temp;
            }
        }
    }
}

static void CoinEffectMain(void);

static void CoinEffectInit(void)
{
    s16 i;
    Process *process = HuPrcCurrentGet();
    for (i = 0; i < COIN_EFFECT_MAX; i++) {
        coinEffectData[i].playerNo = -1;
    }
    HuPrcChildCreate(CoinEffectMain, 100, 8192, 0, process);
}

static void CoinEffectAdd(s16 playerNo)
{
    s16 i;
    for (i = 0; i < COIN_EFFECT_MAX; i++) {
        if (coinEffectData[i].playerNo == -1) {
            break;
        }
    }
    if (i == COIN_EFFECT_MAX) {
        return;
    }
    coinEffectData[i].playerNo = playerNo;
    coinEffectData[i].pos.x = playerPosTbl[playerNo].x;
    coinEffectData[i].pos.y = 610.0f;
    coinEffectData[i].pos.z = 0.0f;
    coinEffectData[i].rank = resultBattleRank[playerNo];
    coinEffectData[i].rotVel.x = frandmod(20) - 10.0f;
    coinEffectData[i].rotVel.y = frandmod(20) - 10.0f;
    coinEffectData[i].rotVel.z = 0;
    coinEffectData[i].velY = 10.0f;
    Hu3DModelAttrReset(coinEffectMdlId[i], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(coinEffectMdlId[i], 0, 100, 0);
    Hu3DModelRotSet(coinEffectMdlId[i], 0, 0, 0);
}

static void CoinEffectMain(void)
{
    s16 i;
    ModelData *modelP;
    s16 player;
    while (1) {
        for (i = 0; i < COIN_EFFECT_MAX; i++) {
            if (coinEffectData[i].playerNo == -1) {
                continue;
            }
            player = coinEffectData[i].playerNo;
            modelP = &Hu3DData[coinEffectMdlId[i]];
            modelP->pos = coinEffectData[i].pos;
            modelP->rot.x += coinEffectData[i].rotVel.x;
            modelP->rot.y += coinEffectData[i].rotVel.y;
            coinEffectData[i].pos.y -= coinEffectData[i].velY;
            coinEffectData[i].velY += 0.2f;
            if (coinEffectData[i].pos.y < ((3 - coinEffectData[i].rank) * 100) + coinEffectYOfs[GWPlayerCfg[resultBattleOrder[player]].character]) {
                Vec pos;
                pos.x = playerPosTbl[player].x;
                pos.y = ((3 - coinEffectData[i].rank) * 100) + coinEffectYOfs[GWPlayerCfg[resultBattleOrder[player]].character];
                pos.z = 0.0f;
                CharModelCoinEffectCreate(1, &pos);
                coinEffectData[i].playerNo = -1;
                HuAudFXPlay(7);
                Hu3DModelAttrSet(coinEffectMdlId[i], HU3D_ATTR_DISPOFF);
            }
        }
        HuPrcVSleep();
    }
}

static void ResultShadowDraw(struct model_data *model, Mtx matrix)
{
    s32 sp8 = 0;
    GXTexObj tex;
    Mtx final;
    Mtx invCamera;
    Mtx shadow;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXInitTexObj(&tex, Hu3DShadowData.unk_04, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex, 0);
    MTXInverse(Hu3DCameraMtx, invCamera);
    MTXConcat(invCamera, matrix, final);
    MTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, shadow);
    MTXConcat(shadow, final, final);
    GXLoadTexMtxImm(final, GX_TEXMTX9, GX_MTX3x4);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX9);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXLoadPosMtxImm(matrix, GX_PNMTX0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-500.0f, 0, -500.0f);
    GXPosition3f32(500.0f, 0, -500.0f);
    GXPosition3f32(500.0f, 0, 500.0f);
    GXPosition3f32(-500.0f, 0, 500.0f);
    GXEnd();
}
