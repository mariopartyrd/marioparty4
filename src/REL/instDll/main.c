#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"

#include "game/hsfmotion.h"

#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/minigame_seq.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "ext_math.h"
#include "math.h"

#include "REL/instDll.h"

static s16 instMode = 1;

static omObjData *lbl_1_bss_60;
static omObjData *outViewObj;
Process *objman;
Vec cameraRot[2];
Vec cameraPos[2];
float cameraZoom[2];
static s32 instBoxMdlId;
static AnimData *instPicAnim;
static u16 instMgNo;
static u16 instHostNo;
static u16 instMesOfs;
static float instFov;
static u8 LanguageNo;
static u16 instPage;
static u16 instBusyF;
static s32 debugCamOnF;

static void InstMain(void);
static void InstPlayerMain(void);
static void InstHostMain(void);
static void InstWinMain(void);
static void InstNameMain(void);
static void CameraOutView(omObjData *object);
static void CameraDebug(omObjData *object);

void ObjectSetup(void)
{
    s32 i;
    omOvlHisData *his;
    s32 lightId;
    OSReport("******* INST ObjectSetup *********\n");
    objman = omInitObjMan(50, 8192);
    omGameSysInit(objman);
    LanguageNo = GWLanguageGet();
    instMgNo = GWSystem.mg_next;
    instMesOfs = 0;
    instBusyF = 0;
    _ClearFlag(0x1000C);
    for (i = 0; sndGrpTable[i].ovl != OVL_INVALID; i++) {
        if (sndGrpTable[i].ovl == mgInfoTbl[instMgNo].ovl) {
            break;
        }
    }
    if (sndGrpTable[i].ovl != OVL_INVALID) {
        HuAudSndGrpSetSet(sndGrpTable[i].grpSet);
    }
    if (mgInfoTbl[instMgNo].ovl == OVL_M411) {
        if (GWMGTypeGet() == -1) {
            GWMGTypeSet(frandmod(3));
        }
    }
    else {
        GWMGTypeSet(-1);
    }
    HuDataDirClose(mgInfoTbl[instMgNo].data_dir);
    his = omOvlHisGet(0);
    omOvlHisChg(0, OVL_RESULT, his->event, his->stat);
    if (omovlevtno == 0 && mgInfoTbl[instMgNo].ovl == OVL_M430) {
        s32 team_cnt[2];
        s32 team_players[2][2];
        team_cnt[0] = team_cnt[1] = 0;
        for (i = 0; i < 4; i++) {
            team_players[GWPlayerCfg[i].group][team_cnt[GWPlayerCfg[i].group]++] = i;
        }
        if (frandBool()) {
            GWPlayerCfg[team_players[0][0]].group = 0;
            GWPlayerCfg[team_players[0][1]].group = 1;
        }
        else {
            GWPlayerCfg[team_players[0][0]].group = 1;
            GWPlayerCfg[team_players[0][1]].group = 0;
        }
        if (frandBool()) {
            GWPlayerCfg[team_players[1][0]].group = 2;
            GWPlayerCfg[team_players[1][1]].group = 3;
        }
        else {
            GWPlayerCfg[team_players[1][0]].group = 3;
            GWPlayerCfg[team_players[1][1]].group = 2;
        }
    }
    if (mgInfoTbl[instMgNo].type == 3 || mgInfoTbl[instMgNo].type == 5 || mgInfoTbl[instMgNo].type == 6
        || mgInfoTbl[instMgNo].type == 8 || !_CheckFlag(FLAG_ID_MAKE(0, 11))) {
        HuDataDirClose(DATADIR_INST);
        omSysPauseEnable(1);
        omOvlCallEx(mgInfoTbl[instMgNo].ovl, 1, 0, 0);
        return;
    }
    cameraRot[0].x = -67.0f;
    cameraRot[0].y = 40.0f;
    cameraRot[0].z = 0.0f;
    cameraPos[0].x = 260.0f;
    cameraPos[0].y = -103.0f;
    cameraPos[0].z = -18.0f;
    cameraZoom[0] = 2885.0f;
    instFov = 20.0f;
    instHostNo = GWSystem.board;
    if (mgBoardHostEnableF) {
        instHostNo = 1;
    }
    cameraRot[1].x = cameraRot[1].y = cameraRot[1].z = 0.0f;
    cameraPos[1].x = cameraPos[1].y = cameraPos[1].z = 0.0f;
    cameraZoom[1] = 1000.0f;
    omSysPauseEnable(0);
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    Hu3DCameraPerspectiveSet(2, 30.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(2, 0, 0, 640, 480, 0, 1);
    lightId = Hu3DGLightCreate(0, 100, 1000, 0, -0.5, -1, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
    HuPrcChildCreate(InstMain, 100, 12288, 0, objman);
    HuPrcChildCreate(InstPlayerMain, 100, 12288, 0, objman);
    HuPrcChildCreate(InstHostMain, 100, 12288, 0, objman);
    HuPrcChildCreate(InstWinMain, 100, 12288, 0, objman);
    HuPrcChildCreate(InstNameMain, 100, 12288, 0, objman);
    outViewObj = omAddObjEx(objman, 32730, 0, 0, -1, CameraOutView);
    omAddObjEx(objman, 0, 32, 32, -1, CameraDebug);
    HuAudSeqPlay(59);
    Hu3DBGColorSet(0, 0, 0);
    HuWinInit(1);
}

static s8 instGrpTbl[] = { 3, 2, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, -1, -1, -1, 0, -1, -1, -1, 3, 2, 1, 0 };

static s8 instPlayerNumTbl[] = { 4, 4, 4, 4, 4, 1, 1, 4 };

static s32 instBoxFile[] = {
    DATA_MAKE_NUM(DATADIR_INST, 0),
    DATA_MAKE_NUM(DATADIR_INST, 1),
    DATA_MAKE_NUM(DATADIR_INST, 2),
    DATA_MAKE_NUM(DATADIR_INST, 3),
    DATA_MAKE_NUM(DATADIR_INST, 4),
    DATA_MAKE_NUM(DATADIR_INST, 0),
    DATA_MAKE_NUM(DATADIR_INST, 5),
    DATA_MAKE_NUM(DATADIR_INST, 0),
};

static s32 instBackFile[] = {
    DATA_MAKE_NUM(DATADIR_INST, 9),
    DATA_MAKE_NUM(DATADIR_INST, 10),
    DATA_MAKE_NUM(DATADIR_INST, 11),
    DATA_MAKE_NUM(DATADIR_INST, 12),
    DATA_MAKE_NUM(DATADIR_INST, 13),
    DATA_MAKE_NUM(DATADIR_INST, 14),
    DATA_MAKE_NUM(DATADIR_INST, 14),
    DATA_MAKE_NUM(DATADIR_INST, 9),
};

static void InstPicDraw(ModelData *model, Mtx mtx);
static void ShadowDraw(ModelData *model, Mtx mtx);

static void InstMain(void)
{
    Vec pos;
    Vec target;
    Vec up;

    Vec rot;
    Process *proc;

    s16 i;
    s16 model;
    s16 comNum;
    s16 j;
    s16 btnDown;
    s32 statId;
    s32 endF;
    s16 grpId;
    s32 picFile;
    omOvlHisData *his;
    s16 sprId;
    AnimData *anim;
    float z;
    float time;
    float fovSpeed;
    float rotX;

    proc = HuPrcCurrentGet();
    statId = -1;
    grpId = HuSprGrpCreate(1);
    anim = HuSprAnimRead(HuDataReadNum(instBackFile[mgInfoTbl[instMgNo].type], MEMORY_DEFAULT_NUM));
    sprId = HuSprCreate(anim, 0, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprGrpDrawNoSet(grpId, 127);
    HuSprPosSet(grpId, 0, 288, 240);
    if (GWMGTypeGet() == -1) {
        picFile = mgInfoTbl[instMgNo].inst_pic[0];
    }
    else {
        picFile = mgInfoTbl[instMgNo].inst_pic[GWMGTypeGet()];
    }
    instPicAnim = HuSprAnimRead(HuDataReadNumHeapShortForce(picFile, MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DShadowCreate(20, 500, 8000);
    Hu3DShadowTPLvlSet(0);
    Hu3DShadowSizeSet(192);
    target.x = target.y = target.z = 0;
    pos.x = pos.z = 100.0f;
    pos.y = 7000.0f;
    up.x = up.y = 0.0f;
    up.z = 1.0f;
    Hu3DShadowPosSet(&pos, &up, &target);
    model = Hu3DModelCreateFile(instBoxFile[mgInfoTbl[instMgNo].type]);
    instBoxMdlId = model;
    Hu3DModelPosSet(model, 0, 2000, 0);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelCameraSet(model, 1);
    Hu3DModelShadowSet(model);
    i = Hu3DHookFuncCreate(ShadowDraw);
    Hu3DModelPosSet(i, 0, -200, 0);
    Hu3DModelCameraSet(i, 1);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    z = -500.0f;
    for (i = 0; i <= 50; i++) {
        Hu3DModelPosSet(model, 0.0f, 2500.0 * cosd(i * 1.8f) - 200.0, z);
        Hu3DModelRotSet(model, 0, 0, 45.0f * (1.0f - (i / 50.0f)));
        z += 50.0 / 7.0;
        Hu3DShadowTPLvlSet(0.5 * (i / 50.0f));
        HuPrcVSleep();
    }
    HuAudFXPlay(1211);
    Hu3DModelAttrReset(model, HU3D_MOTATTR_PAUSE);
    for (i = 1; i <= 20; i++) {
        Hu3DModelPosSet(model, 0.0f, (200.0 * (sind(i * 2.25f) * (1.0 / sind(45)))) - 200.0, z);
        rotX = (20 - i) * cosd(i * 13.5f);
        Hu3DModelRotSet(model, rotX, 0.0f, 0.0f);
        z += 50.0 / 7.0;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    HuPrcSleep(10);
    HuAudFXPlay(1212);
    Hu3DModelAttrReset(model, HU3D_MOTATTR_PAUSE);
    i = Hu3DHookFuncCreate(InstPicDraw);

    Hu3DModelCameraSet(i, 1);
    Hu3DModelPosSet(i, 0, 415, 0);
    instMode = 0;
    while (Hu3DMotionTimeGet(model) < 80.0f) {
        if (Hu3DMotionTimeGet(model) > 30.0f) {
            instMode = 2;
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    HuDataDirClose(DATADIR_INST);
    statId = HuDataDirReadAsync(mgInfoTbl[instMgNo].data_dir);
    while (instMode != 1) {
        HuPrcVSleep();
    }
    endF = 0;
    for (i = comNum = 0; i < 4; i++) {
        if (GWPlayerCfg[i].iscom) {
            comNum++;
        }
    }
    i = 0;
    while (1) {
        if (!endF) {
            for (btnDown = j = 0; j < 4; j++) {
                if (!GWPlayerCfg[j].iscom) {
                    btnDown |= HuPadBtnDown[GWPlayerCfg[j].pad_idx];
                }
            }
            if ((btnDown == PAD_BUTTON_START) || omSysExitReq || (comNum == 4 && i > 60)) {
                HuAudFXPlay(2);
                endF = 1;
            }
            if (btnDown == PAD_TRIGGER_Z) {
                HuAudFXPlay(1);
                endF = 1;
                his = omOvlHisGet(0);
                omOvlHisChg(0, OVL_INST, 1, his->stat);
                _SetFlag(0x1000C);
            }
            if (mgInstExitEnableF && (btnDown & PAD_BUTTON_B)) {
                HuAudFXPlay(3);
                if (statId != -1) {
                    while (!HuDataGetAsyncStat(statId)) {
                        HuPrcVSleep();
                    }
                }
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                HuAudSeqAllFadeOut(500);
                while (WipeStatGet()) {
                    HuPrcVSleep();
                }
                HuDataDirClose(mgInfoTbl[instMgNo].data_dir);
                if (mgInfoTbl[instMgNo].ovl == OVL_M430) {
                    for (comNum = 0; comNum < 4; comNum++) {
                        GWPlayerCfg[comNum].group = GWPlayerCfg[comNum].group / 2;
                    }
                }
                omOvlReturnEx(1, 1);
                HuPrcEnd();
                while (1) {
                    HuPrcVSleep();
                }
            }
        }
        if (!instBusyF || !endF) {
            HuPrcVSleep();
            i++;
            continue;
        }
        else {
            break;
        }
    }
    if (statId != -1) {
        while (!HuDataGetAsyncStat(statId)) {
            HuPrcVSleep();
        }
    }
    rot = cameraRot[0];
    pos = cameraPos[0];
    z = cameraZoom[0];
    WipeColorSet(255, 255, 255);
    instMode = 3;
    HuPrcSleep(20);
    instMode = 4;
    HuPrcSleep(10);

    Hu3DModelAttrReset(model, HU3D_MOTATTR_PAUSE);
    HuPrcSleep(10);
    fovSpeed = 0;
    for (i = 0; i <= 60; i++) {
        time = i / 60.0f;
        cameraRot[0].x = rot.x + ((-65.0f - rot.x) * time);
        cameraRot[0].y = rot.y + ((8.0f - rot.y) * time);
        cameraRot[0].z = rot.z + (-rot.z) * time;
        cameraPos[0].x = pos.x + ((17.0f - pos.x) * time);
        cameraPos[0].y = pos.y + ((5.0f - pos.y) * time);
        cameraPos[0].z = pos.z + ((-188.0f - pos.z) * time);
        cameraZoom[0] = z + ((1173.0f - z) * time);
        if (i == 30) {
            HuAudFXPlay(1210);
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
            HuAudSeqAllFadeOut(1000);
        }
        if (i == 40) {
            Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        }
        if (i > 20) {
            instFov += fovSpeed;
            fovSpeed += 0.04;
        }
        HuPrcVSleep();
    }
    while (WipeStatGet()) {
        instFov += fovSpeed;
        fovSpeed += 0.04;
        HuPrcVSleep();
    }
    instMode = 6;
    HuPrcVSleep();
    omSysPauseEnable(1);
    if (omSysExitReq) {
        HuDataDirClose(mgInfoTbl[instMgNo].data_dir);
        omOvlReturnEx(1, 1);
    }
    else {
        omOvlCallEx(mgInfoTbl[instMgNo].ovl, 1, 0, 0);
    }
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

static char *playerPosNameTbl[] = { "p_pos_a", "p_pos_b", "p_pos_c", "p_pos_d" };

static u8 playerDelayTbl[] = { 8, 0, 12, 4 };

static void InstPlayerMain(void)
{
    float tpLvl;
    s16 i;
    s16 j;
    s16 time;
    s16 playerNum;
    s16 order;
    s16 type;
    s16 grpType;
    s16 group;
    ModelData *modelP;
    s16 playerMdlId[4];
    s16 charNo[4];
    s16 shadowMdl[4];
    s16 playerOrder[4];
    s16 motId[4][3];
    Vec playerPos[4];

    type = mgInfoTbl[instMgNo].type;
    playerNum = instPlayerNumTbl[type];
    for (i = 0; i < playerNum; i++) {
        playerOrder[i] = -1;
    }
    if (mgInfoTbl[instMgNo].ovl != OVL_M430) {
        grpType = type;
    }
    else {
        grpType = 0;
    }
    for (i = 0; i < playerNum; i++) {
        group = instGrpTbl[(grpType * 4) + i];
        for (j = 0; j < 4; j++) {
            if (group == GWPlayerCfg[j].group) {
                for (order = 0; order < i; order++) {
                    if (j == playerOrder[order]) {
                        break;
                    }
                }
                if (order == i) {
                    playerOrder[i] = j;
                    break;
                }
            }
        }
    }
    for (i = 0; i < playerNum; i++) {
        if (playerOrder[i] == -1) {
            for (j = 0; j < playerNum; j++) {
                playerOrder[j] = j;
            }
            break;
        }
    }
    for (i = 0; i < playerNum; i++) {
        charNo[i] = GWPlayerCfg[playerOrder[i]].character;
        playerMdlId[i] = CharModelCreate(charNo[i], 2);
        Hu3DModelPosSet(playerMdlId[i], 5000.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(playerMdlId[i], 0.0f, 180.0f, 0.0f);
        Hu3DModelCameraSet(playerMdlId[i], 1);
        motId[i][0] = CharModelMotionCreate(charNo[i], DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
        motId[i][1] = CharModelMotionCreate(charNo[i], DATA_MAKE_NUM(DATADIR_MARIOMOT, 5));
        motId[i][2] = CharModelMotionCreate(charNo[i], DATA_MAKE_NUM(DATADIR_MARIOMOT, 6));
        CharModelVoiceEnableSet(charNo[i], motId[i][1], 0);
        CharModelMotionSet(charNo[i], motId[i][1]);
        CharModelDataClose(-1);
        shadowMdl[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_INST, 7));
        Hu3DModelTPLvlSet(shadowMdl[i], 0.0f);
        Hu3DModelScaleSet(shadowMdl[i], 0.0f, 0.0f, 0.0f);
    }
    while (instMode != 2) {
        HuPrcVSleep();
    }
    for (i = 0; i < playerNum; i++) {
        Hu3DModelObjPosGet(instBoxMdlId, playerPosNameTbl[i], &playerPos[i]);
        Hu3DModelPosSet(shadowMdl[i], playerPos[i].x, 10 + playerPos[i].y, playerPos[i].z);
    }
    HuPrcSleep(10);
    for (i = 0; i <= 50; i++) {
        for (j = 0; j < playerNum; j++) {
            time = i - playerDelayTbl[j];
            if (time < 0) {
                continue;
            }
            if (time == 15) {
                CharModelMotionSet(charNo[j], motId[j][2]);
            }
            if (time == 30) {
                CharModelMotionShiftSet(charNo[j], motId[j][0], 0, 10, HU3D_MOTATTR_LOOP);
            }
            if (time <= 20) {
                Hu3DModelPosSet(playerMdlId[j], playerPos[j].x, playerPos[j].y + 1000.0 * cosd(time * 4.5f), playerPos[j].z);
                time -= 10;
                if (time >= 0) {
                    tpLvl = 0.1 * time;
                    Hu3DModelTPLvlSet(shadowMdl[j], 0.5 * tpLvl);
                    Hu3DModelScaleSet(shadowMdl[j], tpLvl, tpLvl, tpLvl);
                }
            }
        }
        HuPrcVSleep();
    }
    modelP = &Hu3DData[playerMdlId[0]];
    while (instMode != 4) {
        HuPrcVSleep();
    }
    for (i = 0; i <= 45; i++) {
        for (j = 0; j < playerNum; j++) {
            time = i - playerDelayTbl[j];
            if (time < 0) {
                continue;
            }
            if (time == 0) {
                Hu3DModelAttrReset(playerMdlId[j], HU3D_MOTATTR_LOOP);
                CharModelVoiceEnableSet(charNo[i], motId[i][1], 1);
                CharModelMotionSet(charNo[j], motId[j][1]);
            }
            if (time <= 30) {
                Hu3DModelPosSet(playerMdlId[j], playerPos[j].x, playerPos[j].y + (300.0 * sind(time * 9.0f)), playerPos[j].z - (time * 20));
                if (time <= 10) {
                    tpLvl = 1 - (0.1 * time);
                    Hu3DModelTPLvlSet(shadowMdl[j], 0.5 * tpLvl);
                    Hu3DModelScaleSet(shadowMdl[j], tpLvl, tpLvl, tpLvl);
                }
            }
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

static s32 hostFileTbl[] = {
    DATA_MAKE_NUM(DATADIR_INST, 19),
    DATA_MAKE_NUM(DATADIR_INST, 20),
    DATA_MAKE_NUM(DATADIR_INST, 21),
    DATA_MAKE_NUM(DATADIR_INST, 22),
    DATA_MAKE_NUM(DATADIR_INST, 23),
    DATA_MAKE_NUM(DATADIR_INST, 24),
    DATA_MAKE_NUM(DATADIR_INST, 25),
    DATA_MAKE_NUM(DATADIR_INST, 26),
    DATA_MAKE_NUM(DATADIR_INST, 27),
    DATA_MAKE_NUM(DATADIR_INST, 28),
    DATA_MAKE_NUM(DATADIR_INST, 29),
    DATA_MAKE_NUM(DATADIR_INST, 30),
    DATA_MAKE_NUM(DATADIR_INST, 31),
    DATA_MAKE_NUM(DATADIR_INST, 32),
    DATA_MAKE_NUM(DATADIR_INST, 33),
    DATA_MAKE_NUM(DATADIR_INST, 34),
    DATA_MAKE_NUM(DATADIR_INST, 35),
    DATA_MAKE_NUM(DATADIR_INST, 36),
};

static u16 hostSeTbl[] = { 55, 57, 68, 67, 64, 65, 75, 76, 70, 71, 62, 62 };

static void InstHostMain(void)
{
    float ofsX;
    s16 i;
    s16 modelId;
    s16 motId[2];
    ModelData *modelP;
    modelId = Hu3DModelCreateFile(hostFileTbl[instHostNo * 3]);
    motId[0] = Hu3DJointMotionFile(modelId, hostFileTbl[(instHostNo * 3) + 1]);
    motId[1] = Hu3DJointMotionFile(modelId, hostFileTbl[(instHostNo * 3) + 2]);
    Hu3DMotionSet(modelId, motId[1]);
    if (instHostNo == 3) {
        ofsX = 50;
    }
    else {
        ofsX = 0;
    }
    Hu3DModelPosSet(modelId, -353.0f + ofsX, -150, 356);
    Hu3DModelRotSet(modelId, 0, 90, 0);
    Hu3DModelCameraSet(modelId, 2);
    while (instMode != 2) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    Hu3DMotionTimeSet(modelId, 40);
    HuAudFXPlay(hostSeTbl[instHostNo * 2]);
    for (i = 0; i <= 20; i++) {
        Hu3DModelPosSet(modelId, -153.0f - (100.0f - (100.0f * (i / 20.0f))), (100.0 * sind(i * 9.0f)) + -150.0 + ofsX, 356.0f);
        HuPrcVSleep();
    }
    for (i = 0; i <= 10; i++) {
        Hu3DModelPosSet(modelId, -153.0f, (15.0 * sind(i * 18.0f)) + -150.f + ofsX, 356.0f);
        Hu3DModelRotSet(modelId, 0.0f, 90 - ((i / 10.0f) * 70), 0);
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(modelId, motId[0], 0, 10, HU3D_MOTATTR_LOOP);
    modelP = &Hu3DData[modelId];
    while (1) {
        fontcolor = FONT_COLOR_RED;
        if (instMode == 3) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DMotionSet(modelId, motId[1]);
    HuPrcSleep(20);
    HuAudFXPlay(hostSeTbl[(instHostNo * 2) + 1]);
    for (i = 0; i <= 30; i++) {
        Hu3DModelPosSet(modelId, (i * 5) - 153, (50.0 * sind(i * 9.0f)) + -150.0 + ofsX, (i * 20) + 356);
        HuPrcVSleep();
    }
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

static void InstWinMain(void)
{
    float posX;
    s16 i;
    s16 winId;
    s16 win2Id;
    s16 j;
    s16 insert_idx;
    s16 trigR;
    s16 groupCnt[4];
    s16 charTbl[4][4];

    winId = HuWinExCreateStyled(640, 320, 412, 120, -1, 1);
    while (instMode != 0) {
        HuPrcVSleep();
    }
    HuWinDispOn(winId);
    HuWinMesSet(winId, mgInfoTbl[instMgNo].inst_mess[0]);
    HuWinMesPalSet(winId, 7, 0, 0, 192);
    HuWinMesSpeedSet(winId, 0);
    win2Id = HuWinExCreateStyled(640, 320, 412, 120, -1, 1);
    HuWinDispOn(win2Id);
    HuWinMesSpeedSet(win2Id, 0);
    HuWinPosSet(win2Id, 142.0f, 640.0f);
    instPage = 0;
    for (i = 0; i < 4; i++) {
        groupCnt[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        charTbl[GWPlayerCfg[i].group][groupCnt[GWPlayerCfg[i].group]] = GWPlayerCfg[i].character;
        groupCnt[GWPlayerCfg[i].group]++;
    }
    for (i = insert_idx = 0; i < 4; i++) {
        for (j = 0; j < groupCnt[i]; j++) {
            HuWinInsertMesSet(winId, charTbl[i][j], (s16)insert_idx);
            insert_idx++;
        }
    }
    while (instMode != 2) {
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    for (i = 0; i <= 20; i++) {
        posX = 500.0 * cosd(i * 4.5f) + 142.0;
        HuWinPosSet(winId, posX, 320);
        HuPrcVSleep();
    }
    instMode = 1;
    while (instMode != 3) {
        for (i = trigR = 0; i < 4; i++) {
            if (!GWPlayerCfg[i].iscom) {
                trigR |= HuPadTrigR[GWPlayerCfg[i].pad_idx] & 0xC0;
            }
        }
        if (trigR) {
            HuAudFXPlay(1213);
            instBusyF = 0;
            HuWinMesSet(win2Id, mgInfoTbl[instMgNo].inst_mess[instPage]);
            HuWinMesPalSet(win2Id, 7, 0, 0, 192);
            instPage++;
            if (mgInfoTbl[instMgNo].inst_mess[instPage] == 0) {
                instPage++;
            }
            if (instPage >= 4) {
                instPage = 0;
            }
            HuWinMesSet(winId, mgInfoTbl[instMgNo].inst_mess[instPage]);
            HuWinMesPalSet(winId, 7, 0, 0, 192);
            HuWinPosSet(win2Id, 142.0f, 320.0f);
            for (i = 0; i <= 10; i++) {
                #if VERSION_NTSC
                HuWinPosSet(win2Id, 30.0 * sind(i * 9.0f) + 142.0, 160.0 * (1.0 - cosd(i * 9.0f)) + 320.0);
                #else
                HuWinPosSet(win2Id, 30.0 * sind(i * 9.0f) + 142.0, 180.0 * (1.0 - cosd(i * 9.0f)) + 320.0);
                #endif
                HuPrcVSleep();
            }
            HuPrcSleep(5);
        }
        instBusyF = 1;
        HuPrcVSleep();
    }
    for (i = 0; i <= 20; i++) {
        posX = 500.0 * (1.0 - cosd(i * 4.5f)) + 142.0;
        HuWinPosSet(winId, posX, 320);
        HuPrcVSleep();
    }
    HuWinAllKill();
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

static float instNamePosTbl[] = { 420, 70, 488, 186, 476, 242, 400, 292 };

#if VERSION_NTSC
#define WIN_ANIM_OFS 201
#else
#define WIN_ANIM_OFS 219
#endif

static void InstNameMain(void)
{
    float posX;
    float t;
    float nameX;
    float nameY;
    float nameScaleY;
    s16 i;
    s16 j;
    char *mes;
    AnimData *nameAnim;
    s16 rulesWinId;
    s16 mesSpaceNum;
    s16 nameGrpId;
    s16 startGrpId;
    s16 practiceGrpId;
    s16 nameW;
    u16 prevPage;
    char *mesWord;
    s16 nameSprId;
    s16 startSprId;
    s16 practiceSprId;

    s16 spC[2];
    s16 sp10[4];
    SeqWork work;
    prevPage = 0;
    for (i = 0; i < 16; i++) {
        work.sprite[i] = work.spr_grp[i] = -1;
    }
    mesWord = MessData_MesPtrGet(messDataPtr, mgInfoTbl[instMgNo].name_mess);
    mes = mesWord;
    i = 0;
    mesSpaceNum = 0;
    while (1) {
        if (*mes == 0 || *mes == 10) {
            if (*mes == 0) {
                i = 1;
            }
            *mes = 0;
            FontCreate(&work, mesWord, (LanguageNo == 0) ? 1 : 0);
            HuSprGrpPosSet(work.spr_grp[mesSpaceNum], 288.0f, 240.0f);
            spC[mesSpaceNum] = work.alt_word_len;
            mesSpaceNum++;
            if (i) {
                break;
            }
            mesWord = mes + 1;
        }

        mes++;
    }
    #if VERSION_NTSC
    if (mesSpaceNum == 1) {
        nameW = spC[0];
        nameAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 18));
        nameX = ((576.0f - nameW) - 24.0f) - 16.0f + 227;
        nameY = 78;
        nameScaleY = 0.5f;
    }
    else {
        nameW = (spC[0] > spC[1]) ? spC[0] : spC[1];
        nameAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 15));
        
        nameX = ((576.0f - nameW) - 24.0f) - 16.0f + 172.0f;
        nameY = 84;
        nameScaleY = 1.0f;
    }
    #else
    if (mesSpaceNum == 1) {
        nameW = spC[0];
        nameAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 18));
        nameX = ((576.0f - nameW) - 24.0f) - 16.0f + 235;
        nameY = 78;
        nameScaleY = 0.5f;
    }
    else {
        nameW = (spC[0] > spC[1]) ? spC[0] : spC[1];
        nameAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 15));
        
        nameX = ((576.0f - nameW) - 24.0f) - 16.0f + 235;
        nameY = 84;
        nameScaleY = 1.0f;
    }
    #endif
    nameGrpId = HuSprGrpCreate(1);
    nameSprId = HuSprCreate(nameAnim, 0, 0);
    HuSprGrpMemberSet(nameGrpId, 0, nameSprId);
    HuSprPriSet(nameGrpId, 0, 100);
    HuSprGrpPosSet(nameGrpId, 10000, 70);
    HuSprScaleSet(nameGrpId, 0, 1.0f, nameScaleY);
    for (i = 0; i < mesSpaceNum; i++) {
        HuSprGrpPosSet(work.spr_grp[i], 1000, 70);
    }
    nameAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 16));
    startGrpId = HuSprGrpCreate(1);
    startSprId = HuSprCreate(nameAnim, 0, 0);
    HuSprGrpMemberSet(startGrpId, 0, startSprId);
    HuSprGrpPosSet(startGrpId, 1000, 186);
    HuSprPriSet(startGrpId, 0, 1000);
    sp10[0] = HuWinCreate(1000, 186, 456, 42, 0);
    HuWinMesSet(sp10[0], MAKE_MESSID(0x24, instMesOfs));
    HuWinBGTPLvlSet(sp10[0], 0.0f);
    nameAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 17));
    practiceGrpId = HuSprGrpCreate(1);
    practiceSprId = HuSprCreate(nameAnim, 0, 0);
    HuSprGrpMemberSet(practiceGrpId, 0, practiceSprId);
    HuSprGrpPosSet(practiceGrpId, 1000, 242);
    HuSprPriSet(practiceGrpId, 0, 1000);
    sp10[1] = HuWinCreate(1000, 242, 456, 42, 0);
    HuWinMesSet(sp10[1], instMesOfs + MAKE_MESSID(0x24, 0x01));
    HuWinBGTPLvlSet(sp10[1], 0.0f);
    nameAnim = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_INST, 18));
    sp10[2] = HuWinCreate(1000, 292, 456, 42, 0);
    HuWinMesSet(sp10[2], instMesOfs + MAKE_MESSID(0x24, 0x02));
    HuWinBGTPLvlSet(sp10[2], 0.0f);
    HuWinMesSpeedSet(sp10[2], 0);
    i = HuWinAnimSet(sp10[2], nameAnim, 0, WIN_ANIM_OFS, 18);
    HuWinSprPriSet(sp10[2], i, 1000);
    rulesWinId = HuWinCreate(1000, 292, 456, 42, 0);
    HuWinBGTPLvlSet(rulesWinId, 0.0f);
    HuWinMesSpeedSet(rulesWinId, 0);
    HuWinMesSet(rulesWinId, instMesOfs + MAKE_MESSID(0x24, 0x02));
    i = HuWinAnimSet(rulesWinId, nameAnim, 0, WIN_ANIM_OFS, 18);
    HuWinPriSet(rulesWinId, 10);
    HuWinSprPriSet(rulesWinId, i, 11);
    while (instMode != 0) {
        HuPrcVSleep();
    }
    for (i = 0; i < 36; i++) {
        t = i;
        if (t <= 20.0f) {
            #if VERSION_NTSC
            posX = 300.0 * cosd(4.5f * t) + nameX;
            HuSprGrpPosSet(nameGrpId, posX, nameY);
            posX = 300.0 * cosd(4.5f * t) + (576.0f - (nameW / 2) - 24.0f);
            for (j = 0; j < mesSpaceNum; j++) {
                HuSprGrpPosSet(work.spr_grp[j], posX, (j * 28) + 70);
            }
            #else
            posX = 500.0 * cosd(4.5f * t) + nameX;
            HuSprGrpPosSet(nameGrpId, posX, nameY);
            posX = 500.0 * cosd(4.5f * t) + (576.0f - (nameW / 2) - 24.0f);
            for (j = 0; j < mesSpaceNum; j++) {
                HuSprGrpPosSet(work.spr_grp[j], posX, (j * 28) + 70);
            }
            #endif
        }
        t = i - 3;
        if (t > 0.0f) {
            if (t <= 20.0f) {
                posX = 300.0 * cosd(4.5f * t) + instNamePosTbl[2];
                HuSprGrpPosSet(startGrpId, posX, 186.0f);
                posX = 300.0 * cosd(4.5f * t) + (instNamePosTbl[2] - 88.0f);
                #if VERSION_NTSC
                HuWinPosSet(sp10[0], 16.0f + posX, 168.0f);
                #else
                HuWinPosSet(sp10[0], 8.0f + posX, 168.0f);
                #endif
            }
        }
        t = i - 6;
        if (t > 0.0f) {
            if (t <= 20.0f) {
                posX = 300.0 * cosd(4.5f * t) + instNamePosTbl[4];
                HuSprGrpPosSet(practiceGrpId, posX, 242.0f);
                posX = 300.0 * cosd(4.5f * t) + (instNamePosTbl[4] - 100.0f);
                #if VERSION_NTSC
                HuWinPosSet(sp10[1], 16.0f + posX, 224.0f);
                #else
                HuWinPosSet(sp10[1], 8.0f + posX, 224.0f);
                #endif
            }
        }
        t = i - 9;
        if (t > 0.0f) {
            if (t <= 20.0f) {
                posX = 300.0 * cosd(4.5f * t) + (instNamePosTbl[6] - (WIN_ANIM_OFS+16));
                HuWinPosSet(sp10[2], 16.0f + posX, 274.0f);
            }
        }
        HuPrcVSleep();
    }
    while (instMode != 3) {
        if (prevPage != instPage) {
            posX = 16.0f + (instNamePosTbl[6] - (WIN_ANIM_OFS+16));
            HuWinMesSet(rulesWinId, MAKE_MESSID(0x24, 0x02) + instMesOfs + prevPage);
            prevPage = instPage;
            if (instPage == 1) {
                if (mgInfoTbl[instMgNo].inst_mess[2]) {
                    HuWinMesSet(sp10[2], MAKE_MESSID(0x24, 0x02) + instMesOfs + instPage);
                }
                else {
                    HuWinMesSet(sp10[2], MAKE_MESSID(0x24, 0x06) + instMesOfs);
                }
            }
            else {
                HuWinMesSet(sp10[2], MAKE_MESSID(0x24, 0x02) + instMesOfs + instPage);
            }
            for (i = 0; i <= 10; i++) {
                #if VERSION_NTSC
                HuWinPosSet(rulesWinId, 30.0 * sind(i * 9.0f) + posX, 200.0 * (1.0 - cosd(i * 9.0f)) + 274.0);
                #else
                HuWinPosSet(rulesWinId, 30.0 * sind(i * 9.0f) + posX, 220.0 * (1.0 - cosd(i * 9.0f)) + 274.0);
                #endif
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 20; i++) {
        t = 1.0 - cosd(i * 4.5f);
        posX = nameX + (500.0f * t);
        HuSprGrpPosSet(nameGrpId, posX, nameY);
        posX = ((576.0f - (work.alt_word_len / 2)) - 24.0f) + (500.0f * t);
        for (j = 0; j < mesSpaceNum; j++) {
            HuSprGrpPosSet(work.spr_grp[j], posX, (j * 28) + 70);
        }
        posX = instNamePosTbl[2] + (300.0f * t);
        HuSprGrpPosSet(startGrpId, posX, 186.0f);
        posX = (instNamePosTbl[2] - 88.0f) + (300.0f * t);
        HuWinPosSet(sp10[0], 16.0f + posX, 168);
        posX = instNamePosTbl[4] + (300.0f * t);
        HuSprGrpPosSet(practiceGrpId, posX, 242.0f);
        posX = (instNamePosTbl[4] - 100.0f) + (300.0f * t);
        HuWinPosSet(sp10[1], 16.0f + posX, 224);
        #if VERSION_NTSC
        posX = (instNamePosTbl[6] - 184.0f) + (400.0f * t);
        #else
        posX = (instNamePosTbl[6] - 235.0f) + (400.0f * t);
        #endif
        HuWinPosSet(sp10[2], 16.0f + posX, 274);
        HuPrcVSleep();
    }
    MGSeqSprKill(&work);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}


static void CameraOutView(omObjData *object)
{
    s16 i;
    static u16 cameraMask[] = { HU3D_CAM0, HU3D_CAM1 };
    for (i = 0; i < 2; i++) {
        Vec pos, target, up;
        float x, y, z;

        x = cameraRot[i].x;
        y = cameraRot[i].y;
        z = cameraRot[i].z;

        pos.x = (((sind(y) * cosd(x)) * cameraZoom[i]) + cameraPos[i].x);
        pos.y = (-sind(x) * cameraZoom[i]) + cameraPos[i].y;
        pos.z = ((cosd(y) * cosd(x)) * cameraZoom[i]) + cameraPos[i].z;
        target.x = cameraPos[i].x;
        target.y = cameraPos[i].y;
        target.z = cameraPos[i].z;
        up.x = sind(y) * sind(x);
        up.y = cosd(x);
        up.z = cosd(y) * sind(x);
        Hu3DCameraPosSet(cameraMask[i], pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
    }
}

static void CameraDebug(omObjData *object)
{
    Vec pos;
    Vec offset;
    Vec dir;
    Vec yOffset;

    float rotZ;
    s8 stickPos;

    if (debugCamOnF != 0) {
        cameraRot[0].y += 0.1f * HuPadStkX[0];
        cameraRot[0].x += 0.1f * HuPadStkY[0];
        cameraZoom[0] += HuPadTrigL[0] / 2;
        cameraZoom[0] -= HuPadTrigR[0] / 2;
        if (cameraZoom[0] < 100.0f) {
            cameraZoom[0] = 100.0f;
        }
        pos.x = cameraPos[0].x + (cameraZoom[0] * (sind(cameraRot[0].y) * cosd(cameraRot[0].x)));
        pos.y = (cameraPos[0].y + (cameraZoom[0] * -sind(cameraRot[0].x)));
        pos.z = (cameraPos[0].z + (cameraZoom[0] * (cosd(cameraRot[0].y) * cosd(cameraRot[0].x))));
        offset.x = cameraPos[0].x - pos.x;
        offset.y = cameraPos[0].y - pos.y;
        offset.z = cameraPos[0].z - pos.z;
        dir.x = (sind(cameraRot[0].y) * sind(cameraRot[0].x));
        dir.y = cosd(cameraRot[0].x);
        dir.z = (cosd(cameraRot[0].y) * sind(cameraRot[0].x));
        rotZ = cameraRot[0].z;
        yOffset.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * cosd(rotZ))
            + dir.y * (offset.x * offset.y * (1.0f - cosd(rotZ)) - offset.z * sind(rotZ))
            + dir.z * (offset.x * offset.z * (1.0f - cosd(rotZ)) + offset.y * sind(rotZ));

        yOffset.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * cosd(rotZ))
            + dir.x * (offset.x * offset.y * (1.0f - cosd(rotZ)) + offset.z * sind(rotZ))
            + dir.z * (offset.y * offset.z * (1.0f - cosd(rotZ)) - offset.x * sind(rotZ));

        yOffset.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * cosd(rotZ))
            + (dir.x * (offset.x * offset.z * (1.0 - cosd(rotZ)) - offset.y * sind(rotZ))
                + dir.y * (offset.y * offset.z * (1.0 - cosd(rotZ)) + offset.x * sind(rotZ)));

        VECCrossProduct(&dir, &offset, &offset);
        VECNormalize(&offset, &offset);
        stickPos = (HuPadSubStkX[0] & 0xF8);
        if (stickPos != 0) {
            cameraPos[0].x += 0.05f * (offset.x * stickPos);
            cameraPos[0].y += 0.05f * (offset.y * stickPos);
            cameraPos[0].z += 0.05f * (offset.z * stickPos);
        }
        VECNormalize(&yOffset, &offset);
        stickPos = -(HuPadSubStkY[0] & 0xF8);
        if (stickPos != 0) {
            cameraPos[0].x += 0.05f * (offset.x * stickPos);
            cameraPos[0].y += 0.05f * (offset.y * stickPos);
            cameraPos[0].z += 0.05f * (offset.z * stickPos);
        }
    }
}

static float lbl_1_data_148 = 842;
static float instPicRadius = 34;

static void InstPicDraw(ModelData *model, Mtx mtx)
{
    Mtx final;
    Mtx invCamera;
    Mtx lookAtLight;
    Mtx light;
    Mtx lookat;
    Vec pos;
    Vec up;
    Vec target;

    s32 x;
    s32 y;
    u8 r;
    u8 g;
    u8 b;
    s16 row;

    s32 practiceSprId = 0;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_RGB8, 0);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    target.x = target.z = 0.0f;
    target.x = instPicRadius * sind(cameraRot[0].y);
    target.z = instPicRadius * cosd(cameraRot[0].y);
    target.y = 415.0f;
    pos.x = (sind(cameraRot[0].y) * cosd(cameraRot[0].x) * cameraZoom[0]) + cameraPos[0].x;
    pos.y = (-sind(cameraRot[0].x) * cameraZoom[0]) + cameraPos[0].y;
    pos.z = (cosd(cameraRot[0].y) * cosd(cameraRot[0].x) * cameraZoom[0]) + cameraPos[0].z;
    up.x = -sind(cameraRot[0].y);
    up.z = -cosd(cameraRot[0].y);
    up.y = 0;
    MTXLookAt(lookat, &pos, &up, &target);
    MTXLightPerspective(light, instFov, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    HuSprTexLoad(instPicAnim, 0, 0, GX_CLAMP, GX_CLAMP, GX_NEAR);
    MTXInverse(Hu3DCameraMtx, invCamera);
    MTXConcat(invCamera, mtx, final);
    MTXConcat(light, lookat, lookAtLight);
    MTXConcat(lookAtLight, final, final);
    GXLoadTexMtxImm(final, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    MTXInvXpose(mtx, final);
    GXLoadNrmMtxImm(final, GX_PNMTX0);
    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 2400);
    row = 0;
    for (y = -310; y < 310; y += 31) {
        for (x = -310; x < 310; x += 31) {
            if (row++ & 0x1) {
                r = g = 0;
                b = 255;
            }
            else {
                r = 255;
                g = b = 0;
            }
            GXPosition3f32(x, 0.0f, y);
            GXPosition3f32(0.0f, 1.0f, 0.0f);
            GXColor3u8(r, g, b);
            GXPosition3f32(x + 31, 0.0f, y);
            GXPosition3f32(0.0f, 1.0f, 0.0f);
            GXColor3u8(r, g, b);
            GXPosition3f32(x + 31, 0.0f, y + 31);
            GXPosition3f32(0.0f, 1.0f, 0.0f);
            GXColor3u8(r, g, b);
            GXPosition3f32(x, 0.0f, y);
            GXPosition3f32(0.0f, 1.0f, 0.0f);
            GXColor3u8(r, g, b);
            GXPosition3f32(x + 31, 0.0f, y + 31);
            GXPosition3f32(0.0f, 1.0f, 0.0f);
            GXColor3u8(r, g, b);
            GXPosition3f32(x, 0.0f, y + 31);
            GXPosition3f32(0.0f, 1.0f, 0.0f);
            GXColor3u8(r, g, b);
        }
        row++;
    }
    GXEnd();
}

static void ShadowDraw(ModelData *model, Mtx mtx)
{
    s32 temp = 0;
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
    MTXConcat(invCamera, mtx, final);
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
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-2000.0f, 0, -2000.0f);
    GXPosition3f32(2000.0f, 0, -2000.0f);
    GXPosition3f32(2000.0f, 0, 2000.0f);
    GXPosition3f32(-2000.0f, 0, 2000.0f);
    GXEnd();
}
