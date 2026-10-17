#include "game/chrman.h"
#include "game/disp.h"
#include "game/esprite.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "REL/m401Dll.h"
#include "ext_math.h"
#include "math.h"

#ifndef __MWERKS__
#include "game/audio.h"
#endif

float gravityAcceleration = -7.1875f;

s16 playerCharacterModelIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

Vec globalLightPosition = { 1500, 2500, 1500 };

Vec globalLightDirection = { 0, -1, 0 };

GXColor globalLightColor = { 255, 255, 255, 255 };

Vec shadowLightPosition = { 0, 2500, 0 };

Vec shadowLightUpVector = { 0, 1, -1 };

Vec shadowLightTarget = { 0, 0, 0 };

s32 soundEffectHandle;
OMOBJ **playerObjects;
OMOBJ *sequenceControllerObject;
OMOBJ *minigameRootObject;
OMOBJ *tunnelSceneObject;
OMOBJ *fallingObjectSceneObject;
OMOBJ *orbitingSceneObjects[2];
OMOBJ *movingObstacleObject;
OMOBJ *orbitingParticleObject;
OMOBJ *flockingParticleObject;
OMOBJ *fallingProjectileObjects[4];
OMOBJ *scoreHudObject;
OMOBJ *cameraControllerObject;
OMOBJ *stageParticleEffectA;
OMOBJ *stageParticleEffectB;
OMOBJ *stageParticleEffectC;
OMOBJ *stageParticleEffectD;
OMOBJ *sceneTransitionObject;
OMOBJ *sharedParticleModelObject;
s16 minigameSequenceId;
s16 minigameExitReady;
s16 reservedMinigameState;
s16 winnerCount;
s16 winnerPlayerIndices[4];
s16 winnerCharacterIndices[4];
s16 globalLightId;
s32 audioSequenceId;
s32 ambientSoundEmitterHandles[5];
s32 movingObstacleSoundEmitter;
float soundEmitterMaxDistance;
float soundEmitterFarDistance;
Vec soundEmitterPosition;
Vec cameraPosition;
Vec cameraTarget;
Vec previousCameraPosition;
float cameraMoveDistance;
Vec activeCameraPosition;
Vec activeCameraTarget;
Vec cameraUpVector;
Vec reservedCameraVector;
HUPROCESS *minigameObjectManager;
s16 winnerSequenceTimer;
s16 cameraTransitionIndex;
s32 stageEventCounter;
float obstacleRotationAngle;
s16 stageSectionIndex;
s16 stageSegmentIndex;
OMOBJ *unusedObjectHandle8;
OMOBJ *unusedObjectHandle4;
OMOBJ *unusedObjectHandle0;

void UpdateMinigameFlow(OMOBJ *object);
void CleanupMinigame(OMOBJ *object);
void CreateScoreHud(OMOBJ *object);
void UpdateScorePopups(OMOBJ *object);

void CreateTunnelScene(OMOBJ *object);
void CreatePlayer(OMOBJ *object);
void UpdatePlayerResults(OMOBJ *object);
void CreateFallingObject(OMOBJ *object);
void CreateOrbitingObject(OMOBJ *object);
void CreateMovingObstacle(OMOBJ *object);
void CreateFallingProjectiles(HUPROCESS *objman);
void UpdateStartCountdown(OMOBJ *object);
void UpdateMinigameResults(OMOBJ *object);
void CreateOrbitingParticleGroup(OMOBJ *object);
void CaptureCameraState(OMOBJ *object);

void CreateSharedParticleModels(s16 modelCount);

void ObjectSetup(void)
{
    s32 i;
    OMOBJ *object;
    HU3DCAMERA *camera;
    HU3DLIGHT *light;
    OSReport("**** M401ObjectSetup ****\n");
    HuMemHeapDump(HuMemHeapPtrGet(HEAP_HEAP), -1);
    HuMemHeapDump(HuMemHeapPtrGet(HEAP_MODEL), -1);
    HuMemHeapDump(HuMemHeapPtrGet(HEAP_DVD), -1);
    minigameObjectManager = omInitObjMan(60, 8192);
    omGameSysInit(minigameObjectManager);
    globalLightId = Hu3DGLightCreateV(&globalLightPosition, &globalLightDirection, &globalLightColor);
    Hu3DGLightInfinitytSet(globalLightId);
    light = &Hu3DGlobalLight[globalLightId];
    light->type |= 0x8000;
    Hu3DCameraCreate(1);
    camera = &Hu3DCamera[0];
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    sequenceControllerObject = omAddObjEx(minigameObjectManager, 1000, 3, 0, -1, UpdateStartCountdown);
    sequenceControllerObject->work[0] = 0;
    minigameRootObject = omAddObjEx(minigameObjectManager, 10, 0, 0, -1, UpdateMinigameFlow);
    omMakeGroupEx(minigameObjectManager, 0, 4);
    playerObjects = omGetGroupMemberListEx(minigameObjectManager, 0);
    omMakeGroupEx(minigameObjectManager, 1, 28);
    for (i = 0; i < 4; i++) {
        object = omAddObjEx(minigameObjectManager, 1200, 4, 10, 0, CreatePlayer);
        object->work[0] = i;
    }
    cameraFieldOfView = 60;
    cameraNearPlane = 50;
    cameraFarPlane = 25000;
    Hu3DShadowCreate(30, 20, 5000);
    Hu3DShadowTPLvlSet(0.35f);
    shadowLightPosition.y = cameraTarget.y + 1500.0f;
    shadowLightPosition.z = cameraTarget.z + 500.0f;
    shadowLightTarget.y = cameraTarget.y;
    shadowLightTarget.z = cameraTarget.z + 500.0f;
    Hu3DShadowPosSet(&shadowLightPosition, &shadowLightUpVector, &shadowLightTarget);
    tunnelSceneObject = omAddObjEx(minigameObjectManager, 500, 12, 3, -1, CreateTunnelScene);
    fallingObjectSceneObject = omAddObjEx(minigameObjectManager, 1100, 1, 1, -1, CreateFallingObject);
    orbitingSceneObjects[0] = omAddObjEx(minigameObjectManager, 1110, 1, 1, -1, CreateOrbitingObject);
    orbitingSceneObjects[1] = omAddObjEx(minigameObjectManager, 1110, 1, 1, -1, CreateOrbitingObject);
    movingObstacleObject = omAddObjEx(minigameObjectManager, 1120, 1, 2, -1, CreateMovingObstacle);
    sceneTransitionObject = omAddObjEx(minigameObjectManager, 100, 0, 0, -1, CaptureCameraState);
    scoreHudObject = omAddObjEx(minigameObjectManager, 1500, 0, 0, -1, CreateScoreHud);
    CreateSharedParticleModels(90);
    orbitingParticleObject = omAddObjEx(minigameObjectManager, 500, 9, 0, -1, CreateOrbitingParticleGroup);
    CreateFallingProjectiles(minigameObjectManager);
    LoadScoreParticleResources();
    CreateScoreParticleModelPool();
    flockingParticleObject = CreateParticleModelManager(minigameObjectManager);
    cameraMoveDistance = 0;
    previousCameraPosition = camera->pos;
    Hu3DReflectNoSet(0);
    cameraAspectRatio = 0;
    minigameExitReady = 0;
    winnerCount = 0;
    Hu3DFogSet(3000, 10000, 10, 60, 160);
    Hu3DBGColorSet(10, 60, 160);
    soundEmitterMaxDistance = 3000;
    soundEmitterFarDistance = 142000;
    soundEffectHandle = HuAudFXPlay(1290);
}

void UpdateMinigameFlow(OMOBJ *object)
{
    s32 playerIndex;
    M401WorkPlayer *playerWork;
    s16 highestScore;
    switch (cameraAspectRatio) {
        case 0:
            break;

        case 1:
            if (minigameExitReady == 1) {
                cameraAspectRatio = 2;
                minigameSequenceId = MGSeqFinishCreate();
                HuAudSeqFadeOut(audioSequenceId, 100);
            }
            break;

        case 2:
            if (sequenceControllerObject == NULL) {
                sequenceControllerObject = omAddObjEx(HuPrcCurrentGet(), 1000, 0, 0, -1, UpdateMinigameResults);
                sequenceControllerObject->work[0] = 0;
                highestScore = 0;
                winnerCount = 0;
                for (playerIndex = 0; playerIndex < 4; playerIndex++) {
                    playerWork = playerObjects[playerIndex]->data;
                    playerObjects[playerIndex]->objFunc = UpdatePlayerResults;
                    playerWork->playerState = 5;
                    playerWork->isRoundWinner = 0;
                    if (playerWork->score > highestScore) {
                        highestScore = playerWork->score;
                    }
                    winnerPlayerIndices[playerIndex] = -1;
                    winnerCharacterIndices[playerIndex] = -1;
                }
                if (highestScore > 0) {
                    for (playerIndex = 0; playerIndex < 4; playerIndex++) {
                        playerWork = playerObjects[playerIndex]->data;
                        if (playerWork->score == highestScore) {
                            winnerCharacterIndices[winnerCount] = GWPlayerCfg[playerIndex].character;
                            winnerPlayerIndices[winnerCount++] = playerIndex;
                            playerWork->isRoundWinner = 1;
                        }
                    }
                }
                OSReport("winnercnt:%d\n", winnerCount);
            }
            break;
    }
    if (omSysExitReq) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        HuAudSeqFadeOut(audioSequenceId, 100);
        HuAudFXStop(soundEffectHandle);
        object->objFunc = CleanupMinigame;
    }
}

void CleanupMinigame(OMOBJ *object)
{
    s32 i;
    if (!WipeStatGet()) {
        FreeScoreParticleResources();
        for (i = 0; i < 4; i++) {
            CharModelKill(playerCharacterModelIndices[GWPlayerCfg[i].character]);
        }
        HuAudFXListnerKill();
        omOvlReturnEx(1, 1);
    }
}

void ResetSceneFog(void)
{
    Hu3DFogSet(3000, 10000, 10, 60, 160);
    Hu3DBGColorSet(10, 60, 160);
}

typedef struct M401ScoreHudWork {
    s16 playerPortraitSprites[4];
    s16 scoreDigitSprites[4][3];
    u8 reservedScoreDisplayData[0x30];
    s16 risingScoreSprites[4][3];
    s16 fallingScoreSprites[4][3];
    s16 playerStatusSprites[4];
    s16 playerStatusShadowSprites[4];
    float risingScoreAlpha[4];
    float fallingScoreAlpha[4];
    float risingScoreBaseX[4];
    float risingScoreBaseY[4];
    float fallingScoreBaseX[4];
    float fallingScoreBaseY[4];
    float risingScoreOffsetX[4];
    float risingScoreOffsetY[4];
    float fallingScoreOffsetX[4];
    float fallingScoreOffsetY[4];
    s16 risingScoreTimer[4];
    s16 fallingScoreTimer[4];
    s16 fallingScoreValue[4];
} M401ScoreHudWork;

void SetScoreHudVisible(s16 isVisible)
{
    M401ScoreHudWork *displayWork;
    s32 i;
    s32 j;
    displayWork = scoreHudObject->data;
    if (isVisible) {
        for (i = 0; i < 4; i++) {
            espDispOn(displayWork->playerPortraitSprites[i]);
            espDispOn(displayWork->playerStatusSprites[i]);
            espDispOn(displayWork->playerStatusShadowSprites[i]);
            for (j = 0; j < 2; j++) {
                espDispOn(displayWork->scoreDigitSprites[i][j]);
            }
        }
    }
    else {
        for (i = 0; i < 4; i++) {
            espDispOff(displayWork->playerPortraitSprites[i]);
            espDispOff(displayWork->playerStatusSprites[i]);
            espDispOff(displayWork->playerStatusShadowSprites[i]);
            for (j = 0; j < 2; j++) {
                espDispOff(displayWork->scoreDigitSprites[i][j]);
            }
        }
    }
}

s32 playerPortraitAssetIds[] = {
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x00),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x01),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x02),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x03),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x04),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x05),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x06),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x07),
};

#define PLAYER_POS_X(index, left, width) ((((index)&1) * width) + left)
#define PLAYER_POS_Y(index, top, height) ((((index) > 1) * height) + top)

void CreateScoreHud(OMOBJ *object)
{
    M401ScoreHudWork *displayWork;
    s32 i;
    s32 j;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M401ScoreHudWork), HU_MEMNUM_OVL);
    displayWork = object->data;
    for (i = 0; i < 4; i++) {
        displayWork->playerPortraitSprites[i] = espEntry(playerPortraitAssetIds[GWPlayerCfg[i].character], 2, 0);
        espDispOff(displayWork->playerPortraitSprites[i]);
        espDrawNoSet(displayWork->playerPortraitSprites[i], 0);
        espPosSet(displayWork->playerPortraitSprites[i], PLAYER_POS_X(i, 37, 438), PLAYER_POS_Y(i, 59, 358));
        displayWork->playerStatusSprites[i] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2F), 3, 0);
        espDispOff(displayWork->playerStatusSprites[i]);
        espDrawNoSet(displayWork->playerStatusSprites[i], 0);
        espPosSet(displayWork->playerStatusSprites[i], PLAYER_POS_X(i, 73, 438), PLAYER_POS_Y(i, 61, 358));
        displayWork->playerStatusShadowSprites[i] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x30), 4, 0);
        espDispOff(displayWork->playerStatusShadowSprites[i]);
        espDrawNoSet(displayWork->playerStatusShadowSprites[i], 0);
        espPosSet(displayWork->playerStatusShadowSprites[i], PLAYER_POS_X(i, 73, 438), PLAYER_POS_Y(i, 61, 358));
        espColorSet(displayWork->playerStatusShadowSprites[i], 0, 0, 0);
        espTPLvlSet(displayWork->playerStatusShadowSprites[i], 0.5f);
        for (j = 0; j < 2; j++) {
            displayWork->scoreDigitSprites[i][j] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2E), 1, 0);
            espDispOff(displayWork->scoreDigitSprites[i][j]);
            espDrawNoSet(displayWork->scoreDigitSprites[i][j], 0);
            espPosSet(displayWork->scoreDigitSprites[i][j], PLAYER_POS_X(i, 69 + (j * 20), 438), PLAYER_POS_Y(i, 63, 358));
            espAttrSet(displayWork->scoreDigitSprites[i][j], HUSPR_ATTR_NOANIM);
        }
        for (j = 0; j < 3; j++) {
            displayWork->risingScoreSprites[i][j] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2D), 0, 0);
            espDispOff(displayWork->risingScoreSprites[i][j]);
            espDrawNoSet(displayWork->risingScoreSprites[i][j], 0);
            espAttrSet(displayWork->risingScoreSprites[i][j], HUSPR_ATTR_NOANIM);
            displayWork->fallingScoreSprites[i][j] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2D), 0, 0);
            espDispOff(displayWork->fallingScoreSprites[i][j]);
            espDrawNoSet(displayWork->fallingScoreSprites[i][j], 0);
            espAttrSet(displayWork->fallingScoreSprites[i][j], HUSPR_ATTR_NOANIM);
        }
        espBankSet(displayWork->risingScoreSprites[i][0], 10);
        espBankSet(displayWork->fallingScoreSprites[i][0], 11);
        displayWork->risingScoreAlpha[i] = 1.0f;
        displayWork->fallingScoreAlpha[i] = 1.0f;
        displayWork->risingScoreTimer[i] = 0;
        displayWork->fallingScoreTimer[i] = 0;
    }
    object->objFunc = UpdateScorePopups;
}

void UpdatePlayerScoreDigits(s16 playerIndex);

void UpdateScorePopups(OMOBJ *object)
{
    M401ScoreHudWork *displayWork;
    s32 i;
    s32 j;
    OMOBJ *playerObject;
    Vec worldPosition;
    Vec screenPosition;
    M401WorkPlayer *playerWork;
    displayWork = object->data;
    for (i = 0; i < 4; i++) {
        playerWork = playerObjects[i]->data;
        if (displayWork->risingScoreTimer[i]) {
            playerObject = playerObjects[i];
            worldPosition.x = playerObject->trans.x;
            worldPosition.y = playerObject->trans.y;
            worldPosition.z = playerObject->trans.z;
            ProjectWorldPositionToScreen(&worldPosition, &screenPosition);
            for (j = 0; j < 3; j++) {
                espPosSet(displayWork->risingScoreSprites[i][j], (-20.0f + screenPosition.x + displayWork->risingScoreOffsetX[i]) + (j * 16), 20.0f + screenPosition.y + displayWork->risingScoreOffsetY[i]);
                espTPLvlSet(displayWork->risingScoreSprites[i][j], displayWork->risingScoreAlpha[i]);
            }
            displayWork->risingScoreBaseY[i] -= 0.5f;
            displayWork->risingScoreOffsetY[i] -= 1.0f;
            if (displayWork->risingScoreTimer[i] < 15) {
                displayWork->risingScoreAlpha[i] -= 1.0f / 15.0f;
            }
            if (--displayWork->risingScoreTimer[i] == 0) {
                espDispOff(displayWork->risingScoreSprites[i][0]);
                espDispOff(displayWork->risingScoreSprites[i][1]);
            }
        }
        if (displayWork->fallingScoreTimer[i]) {
            playerObject = playerObjects[i];
            worldPosition.x = playerObject->trans.x;
            worldPosition.y = playerObject->trans.y;
            worldPosition.z = playerObject->trans.z;
            ProjectWorldPositionToScreen(&worldPosition, &screenPosition);
            for (j = 0; j < 2; j++) {
                espPosSet(displayWork->fallingScoreSprites[i][j], (-20.0f + screenPosition.x + displayWork->fallingScoreOffsetX[i]) + (j * 16), -20.0f + screenPosition.y + displayWork->fallingScoreOffsetY[i]);
                espTPLvlSet(displayWork->fallingScoreSprites[i][j], displayWork->fallingScoreAlpha[i]);
            }
            displayWork->fallingScoreBaseY[i] += 0.5f;
            displayWork->fallingScoreOffsetY[i] += 1.0f;
            if (displayWork->fallingScoreTimer[i] < 15) {
                displayWork->fallingScoreAlpha[i] -= 1.0f / 15.0f;
            }
            if (--displayWork->fallingScoreTimer[i] == 0) {
                espDispOff(displayWork->fallingScoreSprites[i][0]);
                espDispOff(displayWork->fallingScoreSprites[i][1]);
            }
        }
        UpdatePlayerScoreDigits(i);
    }
}

void UpdatePlayerScoreDigits(s16 playerIndex)
{
    M401ScoreHudWork *displayWork;
    s32 scoreValue;
    M401WorkPlayer *playerWork;
    displayWork = scoreHudObject->data;
    playerWork = playerObjects[playerIndex]->data;
    scoreValue = playerWork->score;
    espBankSet(displayWork->scoreDigitSprites[playerIndex][0], scoreValue / 10);
    espBankSet(displayWork->scoreDigitSprites[playerIndex][1], scoreValue % 10);
}

void ShowScoreGainPopup(s16 playerIndex)
{
    M401ScoreHudWork *displayWork;
    s32 i;
    M401WorkPlayer *playerWork;
    displayWork = scoreHudObject->data;
    playerWork = playerObjects[playerIndex]->data;
    for (i = 0; i < 2; i++) {
        espDispOn(displayWork->risingScoreSprites[playerIndex][i]);
    }
    displayWork->risingScoreAlpha[playerIndex] = 1;
    displayWork->risingScoreBaseY[playerIndex] = PLAYER_POS_Y(playerIndex, 52, 398);
    displayWork->risingScoreBaseX[playerIndex] = PLAYER_POS_X(playerIndex, 41, 442);
    displayWork->risingScoreOffsetY[playerIndex] = 0;
    displayWork->risingScoreOffsetX[playerIndex] = 0;
    espBankSet(displayWork->risingScoreSprites[playerIndex][1], playerWork->scorePopupValue);
    displayWork->risingScoreTimer[playerIndex] = 45;
}

void ShowScoreLossPopup(s16 playerIndex, s16 scoreLoss)
{
    M401ScoreHudWork *displayWork;
    M401WorkPlayer *playerWork;
    s32 i;
    displayWork = scoreHudObject->data;
    playerWork = playerObjects[playerIndex]->data;
    for (i = 0; i < 2; i++) {
        espDispOn(displayWork->fallingScoreSprites[playerIndex][i]);
    }
    displayWork->fallingScoreAlpha[playerIndex] = 1;
    displayWork->fallingScoreBaseY[playerIndex] = PLAYER_POS_Y(playerIndex, 20, 398);
    displayWork->fallingScoreBaseX[playerIndex] = PLAYER_POS_X(playerIndex, 41, 442);
    displayWork->fallingScoreOffsetY[playerIndex] = 0;
    displayWork->fallingScoreOffsetX[playerIndex] = 0;
    espBankSet(displayWork->fallingScoreSprites[playerIndex][1], scoreLoss);
    displayWork->fallingScoreTimer[playerIndex] = 45;
    displayWork->fallingScoreValue[playerIndex] = scoreLoss;
    playerWork->score -= scoreLoss;
    if (playerWork->score < 0) {
        playerWork->score = 0;
    }
}

float stageEventStartDistances[] = { -500, -8500, -17500, -26500, -99000 };

float stageEventEndDistances[] = { -9100, -18100, -27100, -36100, -45100, -100000 };

void SetupSceneSectionOne(OMOBJ *object);
void SetupSceneSectionTwo(OMOBJ *object);
void SetupSceneSectionThree(OMOBJ *object);
void SetupSceneSectionFour(OMOBJ *object);
void SetupSceneSectionFive(OMOBJ *object);
void CleanupSceneSectionOne(OMOBJ *object);
void CleanupSceneSectionTwo(OMOBJ *object);
void CleanupSceneSectionThree(OMOBJ *object);
void CleanupSceneSectionFour(OMOBJ *object);
void CleanupSceneSectionFive(OMOBJ *object);

OMOBJFUNC stageEventCallbacks[][2] = { SetupSceneSectionOne, CleanupSceneSectionOne, SetupSceneSectionTwo, CleanupSceneSectionTwo, SetupSceneSectionThree, CleanupSceneSectionThree, SetupSceneSectionFour, CleanupSceneSectionFour, SetupSceneSectionFive, CleanupSceneSectionFive };

char *stageModelResourceNames[] = { "kaitei01", "kaitei02", "kaitei03", "kaitei04", "kaitei05" };

s32 playerMotionResourceIds[] = {
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
};

OMOBJ *CreateFlockingParticleEffect(s16 particleCount, Vec *spawnOrigin, Vec *spawnRadius, Vec *effectOrigin);
void SetFlockingParticleWeights(OMOBJ *object, float separationWeight, float obstacleWeight, float alignmentWeight, float cohesionWeight, float originWeight);

void SetupSceneSectionOne(OMOBJ *object)
{
    Vec modelPosition;
    Vec modelScale;
    Vec particlePosition;
    HSFOBJECT *modelObjectData = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[0]);
    OMOBJ *particleObject;
    modelObjectData->type = 2;
    modelPosition.x = -2500;
    modelPosition.y = 150;
    modelPosition.z = -6800;
    modelScale.x = 50;
    modelScale.y = 50;
    modelScale.z = 50;
    particlePosition.x = 1500;
    particlePosition.y = 150;
    particlePosition.z = -4800;
    particleObject = CreateFlockingParticleEffect(18, &modelPosition, &modelScale, &particlePosition);
    SetFlockingParticleWeights((OMOBJ *)particleObject->work[0], 5, 1.5, 0.2, 0.8, 3);
}

void SetupSceneSectionTwo(OMOBJ *object)
{
    Vec modelPosition;
    Vec modelScale;
    OMOBJ *particleObject;
    HSFOBJECT *modelObjectData = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[1]);
    modelObjectData->type = 2;
    modelPosition.x = -1000;
    modelPosition.y = 0;
    modelPosition.z = -9100;
    modelScale.x = 150;
    modelScale.y = 100;
    modelScale.z = 100;
    particleObject = CreateFlockingParticleEffect(14, &modelPosition, &modelScale, &modelPosition);
    omSetRot(particleObject, 3, 0, 0);
    omSetSca(particleObject, 0, 0, 50);
    SetFlockingParticleWeights((OMOBJ *)particleObject->work[0], 4.5, 2.5, 0.08, 0.9, 1);
}

void SetupSceneSectionThree(OMOBJ *object)
{
    Vec modelPosition;
    Vec modelScale;
    Vec particlePosition;
    HSFOBJECT *modelObjectData = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[2]);
    modelObjectData->type = 2;
    modelPosition.x = 500;
    modelPosition.y = 0;
    modelPosition.z = -24300;
    modelScale.x = 200;
    modelScale.y = 100;
    modelScale.z = 100;
    particlePosition.x = 1000;
    particlePosition.y = 0;
    particlePosition.z = -16300;
    CreateFlockingParticleEffect(40, &modelPosition, &modelScale, &particlePosition);
}

void StartOrbitingObject(OMOBJ *object, Vec *pos);

void SetupSceneSectionFour(OMOBJ *object)
{
    Vec particlePosition;
    Vec modelScale;
    Vec modelPosition;
    Vec audioEmitterPosition;
    OMOBJ *particleObject;
    HSFOBJECT *modelObjectData = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[3]);
    modelObjectData->type = 2;
    particlePosition.x = 0;
    particlePosition.y = -150.0f + ((1.0f / 255.0f) * (300.0f * frandu8()));
    particlePosition.z = -23000;
    StartOrbitingObject(orbitingSceneObjects[0], &particlePosition);
    particlePosition.x = 0;
    particlePosition.y = -150.0f + ((1.0f / 255.0f) * (300.0f * frandu8()));
    particlePosition.z = -25000;
    StartOrbitingObject(orbitingSceneObjects[1], &particlePosition);
    particlePosition.x = 5500;
    particlePosition.y = 0;
    particlePosition.z = -29800;
    modelScale.x = 100;
    modelScale.y = 100;
    modelScale.z = 100;
    modelPosition.x = -1500;
    modelPosition.y = 0;
    modelPosition.z = -24900;
    particleObject = CreateFlockingParticleEffect(20, &particlePosition, &modelScale, &modelPosition);
    SetFlockingParticleWeights((OMOBJ *)particleObject->work[0], 6, 1.5f, 0.2f, 0.8f, 3.5f);
    audioEmitterPosition.x = -650;
    audioEmitterPosition.y = -360;
    audioEmitterPosition.z = -26300;
    stageParticleEffectC = CreateScoreParticleEffect(&audioEmitterPosition, 3);
    ambientSoundEmitterHandles[0] = HuAudFXEmiterPlay(1291, &audioEmitterPosition);
}

void SetupSceneSectionFive(OMOBJ *object)
{
    Vec audioEmitterPosition;
    HSFOBJECT *modelObjectData = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[4]);
    modelObjectData->type = 2;
    Hu3DModelAttrReset(object->mdlId[7], HU3D_ATTR_DISPOFF);
    audioEmitterPosition.x = 0;
    audioEmitterPosition.y = -370;
    audioEmitterPosition.z = -43000;
    unusedObjectHandle8 = CreateScoreParticleEffect(&audioEmitterPosition, 3);
    ambientSoundEmitterHandles[1] = HuAudFXEmiterPlay(1291, &audioEmitterPosition);
    audioEmitterPosition.x = 380;
    audioEmitterPosition.y = -440;
    audioEmitterPosition.z = -32000;
    stageParticleEffectD = CreateScoreParticleEffect(&audioEmitterPosition, 3);
    ambientSoundEmitterHandles[2] = HuAudFXEmiterPlay(1291, &audioEmitterPosition);
    Hu3DModelAttrReset(object->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_CLUSTER_ATTR_LOOP);
}

void ConfigureStageScene(OMOBJ *object)
{
    Vec cameraDirection;
    Vec cameraPosition;
    Vec audioEmitterPosition;
    Vec particlePosition;
    s32 particleIndex;
    HSFOBJECT *modelObjectData = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[0]);
    s32 particleCount;
    modelObjectData->type = 2;
    Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(object->mdlId[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[1], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(object->mdlId[3], HU3D_ATTR_DISPOFF);
    activeCameraPosition.x = 0;
    activeCameraPosition.y = 100;
    activeCameraPosition.z = 0;
    activeCameraTarget.x = 0;
    activeCameraTarget.y = 1000;
    activeCameraTarget.z = -1500;
    cameraUpVector.x = 0;
    cameraUpVector.y = 1;
    cameraUpVector.z = 0;
    Hu3DCameraPosSetV(1, &activeCameraPosition, &cameraUpVector, &activeCameraTarget);
    Hu3DCameraPerspectiveSet(1, cameraFieldOfView, cameraNearPlane, cameraFarPlane, 1.2f);
    previousCameraPosition = activeCameraPosition;
    CaptureCameraState(NULL);
    cameraPosition = activeCameraPosition;
    VECSubtract(&activeCameraTarget, &activeCameraPosition, &cameraDirection);
    VECNormalize(&cameraDirection, &cameraDirection);
    HuAudFXListnerSetEX(&cameraPosition, &cameraDirection, soundEmitterMaxDistance, soundEmitterFarDistance, 300, 300, 300);
    audioEmitterPosition.x = 300;
    audioEmitterPosition.y = -450;
    audioEmitterPosition.z = -3100;
    stageParticleEffectA = CreateScoreParticleEffect(&audioEmitterPosition, 3);
    ambientSoundEmitterHandles[0] = HuAudFXEmiterPlay(1291, &audioEmitterPosition);
    audioEmitterPosition.x = -300;
    audioEmitterPosition.y = -340;
    audioEmitterPosition.z = -4720;
    stageParticleEffectB = CreateScoreParticleEffect(&audioEmitterPosition, 3);
    ambientSoundEmitterHandles[1] = HuAudFXEmiterPlay(1291, &audioEmitterPosition);
    Hu3DModelAttrReset(object->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_CLUSTER_ATTR_LOOP);
    particleCount = 4;
    for (particleIndex = 0; particleIndex < particleCount; particleIndex++) {
        particlePosition.x = -340.0f + ((1.0f / 255.0f) * (680.0f * frandu8()));
        particlePosition.y = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
        particlePosition.z = ((-1550.0f - (particleIndex * 260)) - 40.0f) + ((1.0f / 255.0f) * (80.0f * frandu8()));
        CreateScoreParticleEffect(&particlePosition, 0);
    }
}

typedef struct TunnelSceneWork {
    s32 introTriggered;
    float bridgeVerticalOffset;
    Vec bridgeMotionState;
    Vec sideModelPositions[2];
    s16 particleSpawnTimer;
} TunnelSceneWork;

void ConfigureTunnelScene(OMOBJ *object)
{
    Vec cameraPosition;
    Vec cameraTarget;
    Vec audioEmitterPosition;
    Vec particlePosition;
    TunnelSceneWork *tunnelWork;
    s32 modelIndex;
    Hu3DModelAttrReset(object->mdlId[4], HU3D_ATTR_DISPOFF);
    Hu3DModelClusterAttrSet(object->mdlId[4], 0, 0xC0000001);
    Hu3DModelAttrReset(object->mdlId[8], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[8], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[4], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowMapSet(object->mdlId[4]);
    Hu3DModelAttrReset(object->mdlId[5], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(object->mdlId[4], 0, 0, 0);
    Hu3DModelAmbSet(object->mdlId[4], 1, 1, 1);
    Hu3DModelPosSet(object->mdlId[5], 0, 0, 0);
    Hu3DModelPosSet(object->mdlId[6], 0, 0, 0);
    tunnelWork = tunnelSceneObject->data;
    if (winnerCount) {
        tunnelWork->sideModelPositions[0].x = 210;
        tunnelWork->sideModelPositions[0].y = 1018;
        tunnelWork->sideModelPositions[0].z = 0;
        tunnelWork->sideModelPositions[1].x = -160;
        tunnelWork->sideModelPositions[1].y = 1020;
        tunnelWork->sideModelPositions[1].z = -50;
        for (modelIndex = 0; modelIndex < 2; modelIndex++) {
            Hu3DModelPosSet(object->mdlId[modelIndex + 9], tunnelWork->sideModelPositions[modelIndex].x, tunnelWork->sideModelPositions[modelIndex].y, tunnelWork->sideModelPositions[modelIndex].z);
            Hu3DModelAttrReset(object->mdlId[modelIndex + 9], HU3D_ATTR_DISPOFF);
        }
        Hu3DMotionSet(object->mdlId[10], object->mtnId[0]);
        Hu3DMotionSet(object->mdlId[9], object->mtnId[2]);
    }
    else {
        tunnelWork->sideModelPositions[0].x = 210;
        tunnelWork->sideModelPositions[0].y = 1018;
        tunnelWork->sideModelPositions[0].z = 0;
        tunnelWork->sideModelPositions[1].x = -160;
        tunnelWork->sideModelPositions[1].y = 1020;
        tunnelWork->sideModelPositions[1].z = -50;
        for (modelIndex = 0; modelIndex < 2; modelIndex++) {
            Hu3DModelPosSet(object->mdlId[modelIndex + 9], tunnelWork->sideModelPositions[modelIndex].x, tunnelWork->sideModelPositions[modelIndex].y, tunnelWork->sideModelPositions[modelIndex].z);
            Hu3DModelAttrReset(object->mdlId[modelIndex + 9], HU3D_ATTR_DISPOFF);
        }
        Hu3DMotionSet(object->mdlId[10], object->mtnId[1]);
        Hu3DMotionSet(object->mdlId[9], object->mtnId[2]);
    }
    Hu3DModelAttrSet(object->mdlId[9], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[10], HU3D_MOTATTR_LOOP);
    Hu3DModelRotSet(object->mdlId[9], 0, 90, 0);
    Hu3DModelPosSet(object->mdlId[11], 210, 1018, 0);
    Hu3DModelRotSet(object->mdlId[11], 0, 90, 0);
    Hu3DModelAttrReset(object->mdlId[11], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[11], HU3D_MOTATTR_LOOP);
    cameraPosition.x = 0;
    cameraPosition.y = 1300;
    cameraPosition.z = 1300;
    cameraTarget.x = 0;
    cameraTarget.y = 920;
    cameraTarget.z = -100;
    audioEmitterPosition.x = 0;
    audioEmitterPosition.y = 1;
    audioEmitterPosition.z = 0;
    Hu3DCameraPosSetV(1, &cameraPosition, &audioEmitterPosition, &cameraTarget);
    cameraFieldOfView = 45;
    Hu3DShadowData.fov = cameraFieldOfView;
    MTXLightPerspective(Hu3DShadowData.projMtx, cameraFieldOfView, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    Hu3DCameraPerspectiveSet(1, cameraFieldOfView, cameraNearPlane, cameraFarPlane, 1.2f);
    VECSubtract(&cameraTarget, &cameraPosition, &particlePosition);
    VECNormalize(&particlePosition, &particlePosition);
    HuAudFXListnerUpdate(&cameraPosition, &particlePosition);
}

void CleanupSceneSectionOne(OMOBJ *object)
{
    HSFOBJECT *tempR30 = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[0]);
    tempR30->type = -1;
    Hu3DModelAttrSet(object->mdlId[3], HU3D_ATTR_DISPOFF);
    stageParticleEffectA->work[0] = 1;
    Hu3DModelAttrSet(object->mdlId[2], HU3D_ATTR_DISPOFF);
    HuAudFXStop(ambientSoundEmitterHandles[0]);
    HuAudFXStop(ambientSoundEmitterHandles[1]);
}

void CleanupSceneSectionTwo(OMOBJ *object)
{
    HSFOBJECT *tempR31 = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[1]);
    tempR31->type = -1;
    stageParticleEffectB->work[0] = 1;
}

void CleanupSceneSectionThree(OMOBJ *object)
{
    HSFOBJECT *tempR31 = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[2]);
    tempR31->type = -1;
}

void CleanupSceneSectionFour(OMOBJ *object)
{
    HSFOBJECT *tempR30 = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[3]);
    tempR30->type = -1;
    Hu3DModelAttrSet(orbitingSceneObjects[0]->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(orbitingSceneObjects[1]->mdlId[0], HU3D_ATTR_DISPOFF);
    stageParticleEffectC->work[0] = 1;
    HuAudFXStop(ambientSoundEmitterHandles[0]);
}

void CleanupSceneSectionFive(OMOBJ *object)
{
    HSFOBJECT *tempR30 = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[4]);
    tempR30->type = -1;
    Hu3DModelAttrSet(object->mdlId[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    unusedObjectHandle8->work[0] = 1;
    stageParticleEffectD->work[0] = 1;
    Hu3DModelAttrSet(object->mdlId[2], HU3D_ATTR_DISPOFF);
    HuAudFXStop(ambientSoundEmitterHandles[1]);
    HuAudFXStop(ambientSoundEmitterHandles[2]);
}

void EmptyObjectCallback(OMOBJ *object) { }

void EmptyProcessCallback(OMOBJ *object) { }

void UpdateTunnelProp(OMOBJ *object);

void CreateTunnelScene(OMOBJ *object)
{
    TunnelSceneWork *tunnelWork;
    s32 modelIndex;
    HSFOBJECT *modelObject;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(TunnelSceneWork), HU_MEMNUM_OVL);
    tunnelWork = object->data;
    CaptureCameraState(NULL);
    tunnelWork->introTriggered = 0;
    tunnelWork->bridgeMotionState.x = 0;
    tunnelWork->bridgeMotionState.y = 0;
    tunnelWork->bridgeMotionState.z = 0;
    tunnelWork->particleSpawnTimer = 0;
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x00));
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    object->mdlId[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x01));
    Hu3DModelAttrSet(object->mdlId[1], HU3D_ATTR_DISPOFF);
    object->mdlId[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x07));
    Hu3DModelAttrSet(object->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_MOTATTR_LOOP);
    object->mdlId[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x1F));
    Hu3DModelAttrSet(object->mdlId[3], HU3D_ATTR_DISPOFF);
    object->mdlId[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x20));
    Hu3DModelAttrSet(object->mdlId[4], HU3D_ATTR_DISPOFF);
    object->mdlId[11] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x2C));
    Hu3DModelAttrSet(object->mdlId[11], HU3D_ATTR_DISPOFF);
    object->mdlId[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x03));
    Hu3DModelAttrSet(object->mdlId[7], HU3D_ATTR_DISPOFF);
    object->mdlId[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x23));
    Hu3DModelAttrSet(object->mdlId[8], HU3D_ATTR_DISPOFF);
    object->mdlId[9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x28));
    Hu3DModelAttrSet(object->mdlId[9], HU3D_ATTR_DISPOFF);
    object->mdlId[10] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x28));
    Hu3DModelAttrSet(object->mdlId[10], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(object->mdlId[10]);
    object->mdlId[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x21));
    Hu3DModelAttrSet(object->mdlId[5], HU3D_ATTR_DISPOFF);
    object->mdlId[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x22));
    Hu3DModelAttrSet(object->mdlId[6], HU3D_ATTR_DISPOFF);
    object->mtnId[0] = Hu3DJointMotionFile(object->mdlId[10], DATA_MAKE_NUM(DATADIR_M401, 0x29));
    object->mtnId[1] = Hu3DJointMotionFile(object->mdlId[10], DATA_MAKE_NUM(DATADIR_M401, 0x2A));
    object->mtnId[2] = Hu3DJointMotionFile(object->mdlId[9], DATA_MAKE_NUM(DATADIR_M401, 0x2B));
    Hu3DModelPosSet(object->mdlId[1], 0, 0, -1500);
    Hu3DModelShadowMapSet(object->mdlId[0]);
    for (modelIndex = 0; modelIndex < 5; modelIndex++) {
        modelObject = Hu3DModelObjPtrGet(object->mdlId[0], stageModelResourceNames[modelIndex]);
        modelObject->type = -1;
    }
    ConfigureStageScene(object);
    object->objFunc = UpdateTunnelProp;
}

void UpdateTunnelProp(OMOBJ *object)
{
    Hu3DModelPosSet(object->mdlId[3], 110, 5.0 * sind(obstacleRotationAngle), -1500);
    obstacleRotationAngle += 2.0f;
    if (obstacleRotationAngle >= 360.0f) {
        obstacleRotationAngle -= 360.0f;
    }
}

void InitializeProjectileDistribution(float minimumSpacing, float maximumSpacing);

void UpdateTunnelSceneEvents(OMOBJ *object)
{
    Vec particlePosition;
    TunnelSceneWork *tunnelWork;
    s32 particleIndex;
    s32 particleCount;
    tunnelWork = object->data;
    if (cameraTarget.z < -5000.0f && tunnelWork->introTriggered == 0) {
        tunnelWork->introTriggered = 1;
        InitializeProjectileDistribution(-15500, -20000);
    }
    if (cameraPosition.z <= stageEventStartDistances[stageSegmentIndex]) {
        stageSegmentIndex++;
        stageEventCallbacks[stageSegmentIndex][0](object);
    }
    if (cameraPosition.z <= stageEventEndDistances[stageSectionIndex]) {
        stageEventCallbacks[stageSectionIndex][1](object);
        stageSectionIndex++;
    }
    if (cameraPosition.z <= -40000.0f) {
        minigameExitReady = 1;
    }
    if (tunnelWork->particleSpawnTimer) {
        tunnelWork->particleSpawnTimer--;
    }
    else {
        tunnelWork->particleSpawnTimer = 274;
        if (cameraTarget.z > -31260.0f) {
            particleCount = 4;
            for (particleIndex = 0; particleIndex < particleCount; particleIndex++) {
                particlePosition.x = -340.0f + ((1.0f / 255.0f) * (680.0f * frandu8()));
                particlePosition.y = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
                particlePosition.z = ((-4000.0f - (particleIndex * 240)) - 40.0f) + ((1.0f / 255.0f) * (80.0f * frandu8()));
                CreateScoreParticleEffect(&particlePosition, 0);
            }
        }
    }
}

void UpdateBridgeScene(OMOBJ *object)
{
    TunnelSceneWork *tunnelWork;
    s32 modelIndex;
    float modelHeight;
    tunnelWork = object->data;
    tunnelWork->bridgeVerticalOffset = 5.0 * sind(tunnelWork->bridgeMotionState.x);
    tunnelWork->bridgeMotionState.y += tunnelWork->bridgeMotionState.z;
    Hu3DModelPosSet(object->mdlId[4], tunnelWork->bridgeMotionState.y, tunnelWork->bridgeVerticalOffset, 0);
    Hu3DModelPosSet(object->mdlId[5], tunnelWork->bridgeMotionState.y, 0, 0);
    Hu3DModelScaleSet(object->mdlId[5], 1.0f - (0.09f * (tunnelWork->bridgeVerticalOffset / 5.0f)), 1.0f, 1.0f - (0.09f * (tunnelWork->bridgeVerticalOffset / 5.0f)));
    for (modelIndex = 0; modelIndex < 2; modelIndex++) {
        modelHeight = tunnelWork->sideModelPositions[modelIndex].y + (5.0 * sind(tunnelWork->bridgeMotionState.x));
        tunnelWork->sideModelPositions[modelIndex].x += tunnelWork->bridgeMotionState.z;
        Hu3DModelPosSet(object->mdlId[modelIndex + 9], tunnelWork->sideModelPositions[modelIndex].x, modelHeight, tunnelWork->sideModelPositions[modelIndex].z);
    }
    Hu3DModelPosSet(object->mdlId[11], tunnelWork->sideModelPositions[0].x, modelHeight, tunnelWork->sideModelPositions[0].z);
    tunnelWork->bridgeMotionState.z *= 1.04f;
    if (tunnelWork->bridgeMotionState.z > 12.0f) {
        tunnelWork->bridgeMotionState.z = 12.0f;
    }
    tunnelWork->bridgeMotionState.x += 2.0f;
    if (tunnelWork->bridgeMotionState.x >= 360.0f) {
        tunnelWork->bridgeMotionState.x -= 360.0f;
    }
    shadowLightPosition.x = tunnelWork->bridgeMotionState.y;
    shadowLightTarget.x = tunnelWork->bridgeMotionState.y;
    Hu3DShadowPosSet(&shadowLightPosition, &shadowLightUpVector, &shadowLightTarget);
}

void UpdatePlayerIntro(OMOBJ *object);

s32 playerMotionLookup[][10] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x31),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x39),
    DATA_MAKE_NUM(DATADIR_M401, 0x41),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x49),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x32),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3A),
    DATA_MAKE_NUM(DATADIR_M401, 0x42),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4A),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x33),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3B),
    DATA_MAKE_NUM(DATADIR_M401, 0x43),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4B),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x34),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3C),
    DATA_MAKE_NUM(DATADIR_M401, 0x44),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4C),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x35),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3D),
    DATA_MAKE_NUM(DATADIR_M401, 0x45),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4D),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x36),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3E),
    DATA_MAKE_NUM(DATADIR_M401, 0x46),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4E),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x37),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3F),
    DATA_MAKE_NUM(DATADIR_M401, 0x47),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4F),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x38),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x40),
    DATA_MAKE_NUM(DATADIR_M401, 0x48),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x50),
};

Vec playerSpawnPositions[] = {
    -150,
    1250,
    -1400,
    -50,
    1250,
    -1400,
    50,
    1250,
    -1400,
    150,
    1250,
    -1400,
};

Vec playerTargetPositions[] = {
    -300,
    0,
    -1500,
    -100,
    0,
    -1500,
    100,
    0,
    -1500,
    300,
    0,
    -1500,
};

void UpdatePlayerIntro(OMOBJ *object);

void CreatePlayer(OMOBJ *object)
{
    M401WorkPlayer *playerWork;
    s32 playerIndex;
    s32 motionIndex;
    s32 characterIndex;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M401WorkPlayer), HU_MEMNUM_OVL);
    playerWork = object->data;
    playerIndex = object->work[0];
    playerWork->playerIndex = playerIndex;
    playerWork->controllerIndex = GWPlayerCfg[playerIndex].pad_idx;
    characterIndex = GWPlayerCfg[playerIndex].character;
    playerWork->characterModelIndex = playerCharacterModelIndices[characterIndex];
    object->mdlId[0] = CharModelCreate(playerWork->characterModelIndex, 4);
    if (playerIndex == 0) {
        object->mdlId[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x25));
        object->mdlId[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x27));
    }
    else {
        object->mdlId[2] = Hu3DModelLink(playerObjects[0]->mdlId[2]);
        object->mdlId[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x27));
    }
    Hu3DModelAttrSet(object->mdlId[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelClusterAttrSet(object->mdlId[3], 0, 0xC0000002);
    Hu3DModelLayerSet(object->mdlId[3], 7);
    for (motionIndex = 0; motionIndex < 10; motionIndex++) {
        object->mtnId[motionIndex] = CharMotionCreate(playerCharacterModelIndices[characterIndex], playerMotionLookup[characterIndex][motionIndex]);
    }
    CharMotionSet(playerWork->characterModelIndex, object->mtnId[2]);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->mdlId[2], 2);
    Hu3DModelAmbSet(object->mdlId[0], 1, 1, 1);
    Hu3DModelShadowSet(object->mdlId[0]);
    CharMotionVoiceOnSet(playerCharacterModelIndices[characterIndex], object->mtnId[4], 0);
    playerWork->worldPosition = playerTargetPositions[playerIndex];
    playerWork->movementParameters.z = 0;
    omSetTra(object, playerSpawnPositions[playerIndex].x, playerSpawnPositions[playerIndex].y, playerSpawnPositions[playerIndex].z);
    playerWork->playerState = 0;
    playerWork->stateTimer = 70;
    playerWork->targetPosition.x = playerTargetPositions[playerIndex].x;
    playerWork->targetPosition.y = playerTargetPositions[playerIndex].y;
    playerWork->targetPosition.z = 800 + playerTargetPositions[playerIndex].z;
    playerWork->isWalking = 0;
    playerWork->score = 0;
    playerWork->scorePopupValue = 0;
    playerWork->isStunned = 0;
    playerWork->stunTimer = 0;
    playerWork->aiDecisionTimer = 0;
    playerWork->reservedState76 = 0;
    playerWork->jumpVelocity = 0;
    playerWork->collisionCooldown = 0;
    playerWork->runTimer = 0;
    playerWork->idleTimer = 0;
    playerWork->reservedVector94.x = playerWork->reservedVector94.y = playerWork->reservedVector94.z = 0;
    playerWork->aiInputCooldown = 0;
    playerWork->reservedByteA0 = playerWork->reservedByteA1 = 0;
    CharMotionDataClose(playerWork->characterModelIndex);
    object->objFunc = UpdatePlayerIntro;
}

void UpdatePlayerEffectAnchor(OMOBJ *object);
void UpdateCameraTransition(OMOBJ *object);

void UpdatePlayerIntro(OMOBJ *object)
{
    Vec targetDirection;
    Vec normalizedDirection;
    Vec movementDirection;
    M401WorkPlayer *playerWork;
    HU3DCAMERA *camera;
    OMOBJ *particleObject;
    ScoreParticleWork *particleWork;
    float speed;
    playerWork = object->data;
    switch (playerWork->playerState) {
        case 0:
            if (--playerWork->stateTimer == 0) {
                playerWork->playerState = 1;
                CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[4], 0, 20, HU3D_MOTATTR_NONE);
                playerWork->movementParameters.x = 16;
                playerWork->movementParameters.y = 0;
            }
            break;

        case 1:
            if (object->trans.y < 1100) {
                playerWork->playerState = 2;
                speed = VECMagPoint(object->trans.x - playerWork->targetPosition.x, object->trans.y - playerWork->targetPosition.y, object->trans.z - playerWork->targetPosition.z);
                playerWork->movementParameters.z = speed;
                playerWork->movementParameters.y = 0;
                playerWork->stateTimer = 110;
                particleObject = CreateScoreParticleEffect(&playerSpawnPositions[playerWork->playerIndex], 2);
                playerWork->scoreEffect = particleObject;
                particleWork = particleObject->data;
                particleWork->ownerObject = object;
                UpdatePlayerEffectAnchor(object);
                particleObject = CreateScoreParticleEffect(&playerSpawnPositions[playerWork->playerIndex], 4);
                particleWork = particleObject->data;
                particleWork->ownerObject = object;
                playerWork->landingEffect = particleObject;
                particleObject = CreateScoreParticleEffect(&playerSpawnPositions[playerWork->playerIndex], 5);
                particleWork = particleObject->data;
                particleWork->ownerObject = object;
                playerWork->trailEffect = particleObject;
                CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[1], 0, 80, HU3D_MOTATTR_LOOP);
                playerWork->movementOrigin.x = object->trans.x;
                playerWork->movementOrigin.y = object->trans.y;
                playerWork->movementOrigin.z = object->trans.z;
                Hu3DModelAttrReset(object->mdlId[3], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(object->mdlId[3], HU3D_MOTATTR_PAUSE);
                Hu3DModelClusterAttrReset(object->mdlId[3], 0, 0xC0000002);
                Hu3DModelPosSet(object->mdlId[3], object->trans.x, 100, 100 + object->trans.z);
                Hu3DMotionTimeSet(object->mdlId[3], 0);
                if (playerWork->playerIndex == 0) {
                    HuAudFXPlay(1281);
                }
                omVibrate(playerWork->playerIndex, 12, 4, 2);
            }
            else {
                object->trans.y += playerWork->movementParameters.x - (0.07f * playerWork->movementParameters.y * playerWork->movementParameters.y);
                object->trans.z += 2.0f;
                playerWork->movementParameters.y += 1.0f;
            }
            break;

        case 2:
            camera = &Hu3DCamera[0];
            normalizedDirection = playerWork->targetPosition;
            movementDirection = playerWork->movementOrigin;
            VECSubtract(&normalizedDirection, &movementDirection, &targetDirection);
            VECNormalize(&targetDirection, &targetDirection);
            object->trans.x = playerWork->movementOrigin.x + (playerWork->movementParameters.z * (targetDirection.x * sind(playerWork->movementParameters.y)));
            object->trans.y = playerWork->movementOrigin.y + (playerWork->movementParameters.z * (targetDirection.y * sind(playerWork->movementParameters.y)));
            object->trans.z = playerWork->movementOrigin.z + (playerWork->movementParameters.z * (targetDirection.z * sind(playerWork->movementParameters.y)));
            playerWork->movementParameters.y += 9.0f / 11.0f;
            omSetRot(object, atan2d(targetDirection.y, targetDirection.z) + 90.0, 0, 0);
            speed = VECMagPoint(object->trans.x - normalizedDirection.x, object->trans.y - normalizedDirection.y, object->trans.z - normalizedDirection.z);
            if (--playerWork->stateTimer == 60 && playerWork->playerIndex == 0 && unusedObjectHandle4 == NULL) {
                camera = &Hu3DCamera[0];
                unusedObjectHandle4 = omAddObjEx(HuPrcCurrentGet(), 1400, 0, 0, -1, UpdateCameraTransition);
                unusedObjectHandle4->trans.x = camera->pos.x;
                unusedObjectHandle4->trans.y = camera->pos.y;
                unusedObjectHandle4->trans.z = camera->pos.z;
                unusedObjectHandle4->rot.x = camera->target.x;
                unusedObjectHandle4->rot.y = camera->target.y;
                unusedObjectHandle4->rot.z = camera->target.z;
                unusedObjectHandle4->scale.x = 0;
            }
            if (playerWork->stateTimer == 0) {
                playerWork->playerState = 3;
                playerWork->landingEffect->work[0] = 1;
                playerWork->trailEffect->work[0] = 1;
            }
            UpdatePlayerEffectAnchor(object);
            break;

        case 3:
            normalizedDirection.x = fallingObjectSceneObject->trans.x;
            normalizedDirection.y = playerSpawnPositions[playerWork->playerIndex].y;
            normalizedDirection.z = fallingObjectSceneObject->trans.z;
            movementDirection.x = object->trans.x;
            movementDirection.y = object->trans.y;
            movementDirection.z = object->trans.z;
            VECSubtract(&normalizedDirection, &movementDirection, &targetDirection);
            VECNormalize(&targetDirection, &targetDirection);
            object->rot.x *= 0.95f;
            if (object->rot.x < 1.0f) {
                object->rot.x = 0.0f;
            }
            omSetRot(object, object->rot.x, atan2d(targetDirection.x, targetDirection.z), 0);
            UpdatePlayerEffectAnchor(object);
            break;
    }
}

void UpdatePlayerEffectAnchor(OMOBJ *object);

void UpdatePlayerResults(OMOBJ *object)
{
    M401WorkPlayer *playerWork;
    TunnelSceneWork *tunnelWork;
    float verticalDistance;
    Vec playerDirection;
    Vec playerPosition;
    s32 scoreOffsets[] = { -10, -50, -80, -130 };
    Vec cameraDirection;
    Vec cameraPosition;
    Vec cameraUp;
    playerWork = object->data;
    tunnelWork = tunnelSceneObject->data;
    if (playerWork->playerIndex == 0) {
        winnerSequenceTimer--;
    }
    switch (playerWork->playerState) {
        case 5:
            if (playerWork->isWalking == 1) {
                CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[1], 0, 8, HU3D_MOTATTR_LOOP);
                playerWork->isWalking = 0;
            }
            omSetRot(object, 0, 180, 0);
            object->trans.z -= 5.0f;
            UpdatePlayerEffectAnchor(object);
            break;

        case 6:
            object->trans.y += playerWork->movementParameters.x;
            if (object->trans.y >= 910.0f) {
                if (playerWork->stateInitialized == 0) {
                    playerWork->stateInitialized = 1;
                    Hu3DModelAttrReset(object->mdlId[2], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(object->mdlId[2], HU3D_MOTATTR_LOOP);
                    Hu3DModelPosSet(object->mdlId[2], object->trans.x, 950, 30 + object->trans.z);
                    Hu3DModelScaleSet(object->mdlId[2], 1, 1, 1);
                    Hu3DMotionTimeSet(object->mdlId[2], 0);
                    playerDirection.x = object->trans.x;
                    playerDirection.y = 950;
                    playerDirection.z = 30 + object->trans.z;
                    CreateScoreParticleEffect(&playerDirection, 7);
                    HuAudFXEmiterPlay(1289, &playerDirection);
                }
                playerWork->movementParameters.x *= 0.7f;
                if (playerWork->movementParameters.x <= 0.5f) {
                    playerWork->playerState = 7;
                    playerWork->movementParameters.x = -0.5f;
                    CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[0], 0, 30, HU3D_MOTATTR_LOOP);
                    playerWork->animationAngle = 0;
                    playerWork->stateInitialized = 0;
                }
            }

            break;

        case 7:
            object->trans.y += playerWork->movementParameters.x;
            if (object->trans.y <= 890) {
                object->trans.y = 890;
                if (winnerCount) {
                    if (playerWork->isRoundWinner) {
                        playerWork->playerState = 16;
                    }
                    else {
                        playerWork->playerState = 9;
                    }
                }
                else {
                    playerWork->playerState = 8;
                    tunnelWork->bridgeMotionState.z = 0.5f;
                    playerWork->stateTimer = 0;
                    HuAudSStreamPlay(4);
                    minigameSequenceId = MGSeqDrawCreate();
                    winnerSequenceTimer = 210;
                }
            }
            playerWork->movementParameters.x *= 1.17f;
            object->trans.y -= 0.35f * sind(playerWork->animationAngle);
            playerWork->animationAngle += 3.0f;
            if (playerWork->animationAngle >= 360.0f) {
                playerWork->animationAngle -= 360.0f;
            }
            break;

        case 8:
            object->trans.y -= 0.35f * sind(playerWork->animationAngle);
            playerWork->animationAngle += 3.0f;
            if (playerWork->animationAngle >= 360.0f) {
                playerWork->animationAngle -= 360.0f;
            }
            if (playerWork->stateTimer == 13) {
                Hu3DModelAttrReset(tunnelSceneObject->mdlId[6], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(tunnelSceneObject->mdlId[6], 0);
            }
            else if (playerWork->stateTimer == 50) {
                Hu3DMotionOverlaySet(object->mdlId[0], object->mtnId[8]);
                Hu3DMotionOverlayTimeSet(object->mdlId[0], 31.0f);
                Hu3DData[object->mdlId[0]].motOvlWork.speed = 1;
            }
            if (playerWork->stateTimer >= 70) {
                if (object->rot.y < 90.0f) {
                    object->rot.y += 2.25f;
                }
                else {
                    object->rot.y = 90.0f;
                }
            }
            playerWork->stateTimer++;
            if (tunnelWork->bridgeMotionState.y >= 1500.0f) {
                tunnelWork->bridgeMotionState.z = 0;
                if (playerWork->playerIndex == 0) {
                    playerWork->playerState = 14;
                }
            }
            break;

        case 16:
            if (!playerWork->stateInitialized) {
                playerWork->stateInitialized = 1;
                PlayerFXPlay(playerWork->playerIndex, 292);
                Hu3DMotionOverlaySet(object->mdlId[0], object->mtnId[9]);
                if (playerWork->playerIndex == winnerPlayerIndices[0]) {
                    HuAudSStreamPlay(1);
                    minigameSequenceId = MGSeqWinCreate(winnerCharacterIndices[0], winnerCharacterIndices[1], winnerCharacterIndices[2], winnerCharacterIndices[3]);
                    winnerSequenceTimer = 210;
                    playerWork->stateTimer = 160;
                    playerWork->playerState = 13;
                }
            }
            playerWork->movementParameters.x *= 1.17f;
            object->trans.y -= 0.35f * sind(playerWork->animationAngle);
            playerWork->animationAngle += 3.0f;
            if (playerWork->animationAngle >= 360.0f) {
                playerWork->animationAngle -= 360.0f;
            }
            if (73.0f <= Hu3DMotionOverlayTimeGet(object->mdlId[0])) {
                Hu3DMotionOverlayTimeSet(object->mdlId[0], 35.0f);
            }
            break;

        case 10:
            object->trans.y += playerWork->movementParameters.x;
            if (object->trans.y >= 910.0f) {
                if (playerWork->stateInitialized == 0) {
                    playerWork->stateInitialized = 1;
                    omVibrate(playerWork->playerIndex, 12, 4, 2);
                    Hu3DModelAttrReset(object->mdlId[2], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(object->mdlId[2], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(object->mdlId[2], HU3D_MOTATTR_LOOP);
                    Hu3DModelPosSet(object->mdlId[2], object->trans.x, 950, 30 + object->trans.z);
                    Hu3DModelScaleSet(object->mdlId[2], 1, 1, 1);
                    Hu3DMotionTimeSet(object->mdlId[2], 0);
                    Hu3DModelAttrReset(object->mdlId[3], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(object->mdlId[3], HU3D_ATTR_DISPOFF);
                    Hu3DModelClusterAttrReset(object->mdlId[3], 0, 0xC0000002);
                    Hu3DModelPosSet(object->mdlId[3], object->trans.x, 0, 30 + object->trans.z);
                    Hu3DMotionTimeSet(object->mdlId[3], 0);
                    playerDirection.x = object->trans.x;
                    playerDirection.y = 950;
                    playerDirection.z = 30 + object->trans.z;
                    CreateScoreParticleEffect(&playerDirection, 7);
                    HuAudFXEmiterPlay(1289, &playerDirection);
                }
                playerWork->playerState = 11;
                playerWork->targetPosition.x = scoreOffsets[playerWork->playerIndex];
                playerWork->targetPosition.y = 1030;
                playerWork->targetPosition.z = 40;
                playerDirection.x = object->trans.x;
                playerDirection.y = object->trans.y;
                playerDirection.z = object->trans.z;
                VECSubtract(&playerWork->targetPosition, &playerDirection, &playerPosition);
                VECNormalize(&playerPosition, &playerPosition);
                verticalDistance = VECDistanceXZ(&playerWork->targetPosition, &object->trans);
                playerWork->movementOrigin.x = (playerPosition.x * verticalDistance) / 60.0f;
                playerWork->movementOrigin.z = (playerPosition.z * verticalDistance) / 60.0f;
                playerWork->movementOrigin.y = 18.75f;
                playerWork->movementParameters.y = 0;
            }
            break;

        case 11:
            verticalDistance = playerWork->movementOrigin.y - (0.020833334f * playerWork->movementParameters.y * playerWork->movementParameters.y);
            object->trans.x += playerWork->movementOrigin.x;
            object->trans.z += playerWork->movementOrigin.z;
            object->trans.y += verticalDistance;
            playerWork->movementParameters.y += 1.0f;
            if (object->trans.y <= 1030.0f && verticalDistance < 0) {
                playerWork->playerState = 12;
                object->trans.y = 1030 + tunnelWork->bridgeVerticalOffset;
                CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[2], 0, 15, HU3D_MOTATTR_LOOP);
                playerWork->movementParameters.x = 0;
            }
            break;

        case 12:
            object->trans.y = 1030 + tunnelWork->bridgeVerticalOffset;
            cameraDirection.x = (sind(playerWork->movementParameters.x), 0.0);
            cameraDirection.y = -100 * sind(playerWork->movementParameters.x) + 1300;
            cameraDirection.z = -500 * sind(playerWork->movementParameters.x) + 1300;
            cameraPosition.x = (sind(playerWork->movementParameters.x), 0.0);
            cameraPosition.y = 330 * sind(playerWork->movementParameters.x) + 920;
            cameraPosition.z = (sind(playerWork->movementParameters.x), 0.0) + -100.0;
            cameraUp.x = 0;
            cameraUp.y = 1;
            cameraUp.z = 0;
            Hu3DCameraPosSetV(1, &cameraDirection, &cameraUp, &cameraPosition);
            playerWork->movementParameters.x += 3.0f;
            if (playerWork->movementParameters.x > 90.0f) {
                playerWork->playerState = 13;
                CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[5], 0, 20, HU3D_MOTATTR_NONE);
                HuAudSStreamPlay(1);
                minigameSequenceId = MGSeqWinCreate(winnerCharacterIndices[0], -1, -1, -1);
                winnerSequenceTimer = 210;
            }
            playerWork->stateTimer = 160;
            break;

        case 13:
            if (winnerCount == 1) {
                object->trans.y = 1030 + tunnelWork->bridgeVerticalOffset;
            }
            else {
                playerWork->movementParameters.x *= 1.17f;
                object->trans.y -= 0.35f * sind(playerWork->animationAngle);
                playerWork->animationAngle += 3.0f;
                if (playerWork->animationAngle >= 360.0f) {
                    playerWork->animationAngle -= 360.0f;
                }
                if (73.0f <= Hu3DMotionOverlayTimeGet(object->mdlId[0])) {
                    Hu3DMotionOverlayTimeSet(object->mdlId[0], 35.0f);
                }
            }
            if (--playerWork->stateTimer == 0) {
                playerWork->playerState = 14;
            }

            break;

        case 14:
            if (playerWork->isRoundWinner) {
                if (winnerCount == 1) {
                    object->trans.y = 1030 + tunnelWork->bridgeVerticalOffset;
                }
                else {
                    playerWork->movementParameters.x *= 1.17f;
                    object->trans.y -= 0.35f * sind(playerWork->animationAngle);
                    playerWork->animationAngle += 3.0f;
                    if (playerWork->animationAngle >= 360.0f) {
                        playerWork->animationAngle -= 360.0f;
                    }
                    if (73.0f <= Hu3DMotionOverlayTimeGet(object->mdlId[0])) {
                        Hu3DMotionOverlayTimeSet(object->mdlId[0], 35.0f);
                    }
                }
            }
            if (winnerSequenceTimer <= 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                HuAudSeqFadeOut(audioSequenceId, 100);
                HuAudFXStop(soundEffectHandle);
                playerWork->playerState = 15;
            }
            break;

        case 15:
            if (playerWork->isRoundWinner) {
                if (winnerCount == 1) {
                    object->trans.y = 1030 + tunnelWork->bridgeVerticalOffset;
                }
                else {
                    playerWork->movementParameters.x *= 1.17f;
                    object->trans.y -= 0.35f * sind(playerWork->animationAngle);
                    playerWork->animationAngle += 3.0f;
                    if (playerWork->animationAngle >= 360.0f) {
                        playerWork->animationAngle -= 360.0f;
                    }
                    if (73.0f <= Hu3DMotionOverlayTimeGet(object->mdlId[0])) {
                        Hu3DMotionOverlayTimeSet(object->mdlId[0], 35.0f);
                    }
                }
            }
            if (!WipeStatGet()) {
                minigameRootObject->objFunc = CleanupMinigame;
            }
            break;
    }
}

void ConstrainPlayerMovement(OMOBJ *object);
void UpdatePlayerModelPosition(OMOBJ *object);
void CheckPlayerObstacleCollisions(OMOBJ *object);

void ReadCpuPlayerInput(OMOBJ *object, s8 *x, s8 *y, u16 *btn);

void UpdatePlayerControl(OMOBJ *object)
{
    M401WorkPlayer *playerWork;
    float movementSpeed;
    Vec playerPosition;
    Vec movementDirection;
    s32 buttonInput;
    u16 pressedButtons;
    s8 stickX;
    s8 stickY;
    movementSpeed = 0;
    playerWork = object->data;
    stickX = stickY = pressedButtons = 0;
    if (playerWork->isStunned == 0) {
        if (GWPlayerCfg[playerWork->playerIndex].iscom) {
            ReadCpuPlayerInput(object, &stickX, &stickY, &pressedButtons);
        }
        else {
            stickX = HuPadStkX[playerWork->controllerIndex];
            stickY = HuPadStkY[playerWork->controllerIndex];
            pressedButtons = HuPadBtnDown[playerWork->controllerIndex];
        }
        if (stickX != 0 || stickY != 0) {
            playerWork->movementParameters.z = sqrtf((stickX * stickX) + (stickY * stickY)) / 9.0f;
        }
        playerWork->facingAngle = atan2d(stickX, stickY);
        if (pressedButtons & PAD_BUTTON_A) {
            playerWork->jumpVelocity += 1.51f * gravityAcceleration;
            if (playerWork->jumpVelocity < 1.51f * gravityAcceleration) {
                playerWork->jumpVelocity = 1.51f * gravityAcceleration;
            }
        }
        if (playerWork->jumpVelocity >= 0.0f) {
            movementSpeed = 0;
        }
        else {
            movementSpeed = fabs(playerWork->jumpVelocity / (1.51f * gravityAcceleration));
        }
        if (playerWork->collisionCooldown) {
            if (--playerWork->collisionCooldown == 0) {
                CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[1], 0, 8, HU3D_MOTATTR_LOOP);
                playerWork->isWalking = 0;
            }
        }
    }
    else {
        playerWork->collisionCooldown = 0;
        if (--playerWork->stunTimer == 0) {
            buttonInput = GWPlayerCfg[playerWork->playerIndex].character;
            CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[1], 0, 8, HU3D_MOTATTR_LOOP);
            playerWork->isStunned = 0;
            playerWork->isWalking = 0;
        }
        if (playerWork->stunTimer & 0x1) {
            Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
        }
    }
    if (movementSpeed != 0) {
        if (++playerWork->runTimer > 15) {
            playerWork->runTimer = 15;
        }
        playerWork->idleTimer = 0;
    }
    else {
        if (++playerWork->idleTimer > 5) {
            playerWork->idleTimer = 5;
            playerWork->runTimer = 0;
        }
    }
    if (playerWork->isStunned == 0 && playerWork->collisionCooldown == 0) {
        if (playerWork->movementParameters.z > 0 || playerWork->runTimer >= 5) {
            if (playerWork->isWalking == 0) {
                playerWork->isWalking = 1;
                CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[3], 0, 8, HU3D_MOTATTR_LOOP);
            }
        }
        else {
            if (playerWork->isWalking == 1) {
                CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[1], 0, 8, HU3D_MOTATTR_LOOP);
                playerWork->isWalking = 0;
            }
        }
    }
    CharMotionSpeedSet(playerWork->characterModelIndex, 1.0f + movementSpeed);
    ConstrainPlayerMovement(object);
    if (playerWork->movementParameters.z > 0.1f) {
        playerWork->movementParameters.z *= 0.9f;
    }
    else {
        playerWork->movementParameters.z = 0.0f;
    }
    playerWork->jumpVelocity -= 0.15f * gravityAcceleration;
    if (playerWork->jumpVelocity > -gravityAcceleration) {
        playerWork->jumpVelocity = -gravityAcceleration;
    }
    playerPosition.x = object->trans.x;
    playerPosition.y = object->trans.y;
    playerPosition.z = object->trans.z;
    omSetTra(object, playerWork->worldPosition.x, playerWork->worldPosition.y, cameraTarget.z + playerWork->worldPosition.z);
    movementDirection.x = object->trans.x;
    movementDirection.y = object->trans.y;
    movementDirection.z = object->trans.z;
    if (stickY != 0) {
        object->rot.x -= 0.05f * stickY;
    }
    else {
        object->rot.x *= 0.8f;
        if (object->rot.x < 0.01f) {
            object->rot.x = 0;
        }
    }
    if (stickX != 0) {
        object->rot.z -= 0.05f * stickX;
    }
    else {
        object->rot.z *= 0.8f;
        if (object->rot.z < 0.01f) {
            object->rot.z = 0;
        }
    }
    if (object->rot.x < -30.0f) {
        object->rot.x = -30.0f;
    }
    if (object->rot.x > 30.0f) {
        object->rot.x = 30.0f;
    }
    if (object->rot.z < -30.0f) {
        object->rot.z = -30.0f;
    }
    if (object->rot.z > 30.0f) {
        object->rot.z = 30.0f;
    }
    object->rot.y = 180;
    UpdatePlayerModelPosition(object);
    CheckPlayerObstacleCollisions(object);
    playerWork->reservedState70 = 0;
}

void ConstrainPlayerMovement(OMOBJ *object)
{
    M401WorkPlayer *otherPlayerWork;
    M401WorkPlayer *playerWork;
    s32 playerIndex;
    OMOBJ *playerObject;
    float nextX;
    float nextY;
    float nextZ;
    float movementSpeed;
    float unusedDistance;

    Vec movementVector;
    Vec normalizedVector;
    Vec playerPosition;
    playerWork = object->data;
    movementSpeed = playerWork->movementParameters.z;
    movementVector.x = sind(playerWork->facingAngle);
    movementVector.y = cosd(playerWork->facingAngle);
    movementVector.z = playerWork->jumpVelocity + gravityAcceleration;
    VECNormalize(&movementVector, &normalizedVector);
    movementVector.x *= movementSpeed;
    movementVector.y *= movementSpeed;
    movementVector.z -= gravityAcceleration;
    nextX = playerWork->worldPosition.x + movementVector.x;
    nextY = playerWork->worldPosition.y + movementVector.y;
    nextZ = playerWork->worldPosition.z + movementVector.z;
    if (nextX < -400) {
        nextX = -400;
    }
    if (nextX > 400) {
        nextX = 400;
    }
    if (nextY < -300) {
        nextY = -300;
    }
    if (nextY > 300) {
        nextY = 300;
    }
    if (nextZ < 400) {
        nextZ = 400;
    }
    if (nextZ > 800) {
        nextZ = 800;
    }
    for (playerIndex = 0; playerIndex < 4; playerIndex++) {
        if (playerObjects[playerIndex] != object) {
            playerObject = playerObjects[playerIndex];
            otherPlayerWork = playerObject->data;
            unusedDistance = VECMagPoint(nextX - otherPlayerWork->worldPosition.x, nextY - otherPlayerWork->worldPosition.y, nextZ - otherPlayerWork->worldPosition.z);
            if (unusedDistance < 127.0f) {
                playerPosition.x = nextX - otherPlayerWork->worldPosition.x;
                playerPosition.y = nextY - otherPlayerWork->worldPosition.y;
                playerPosition.z = nextZ - otherPlayerWork->worldPosition.z;
                VECNormalize(&playerPosition, &playerPosition);
                nextX = otherPlayerWork->worldPosition.x + 127.0f * playerPosition.x;
                nextY = otherPlayerWork->worldPosition.y + 127.0f * playerPosition.y;
                nextZ = otherPlayerWork->worldPosition.z + 127.0f * playerPosition.z;
            }
        }
    }
    if (nextX < -400) {
        nextX = -400;
    }
    if (nextX > 400) {
        nextX = 400;
    }
    if (nextY < -300) {
        nextY = -300;
    }
    if (nextY > 300) {
        nextY = 300;
    }
    if (nextZ < 400) {
        nextZ = 400;
    }
    if (nextZ > 800) {
        nextZ = 800;
    }
    playerWork->worldPosition.x = nextX;
    playerWork->worldPosition.y = nextY;
    playerWork->worldPosition.z = nextZ;
}

void UpdatePlayerModelPosition(OMOBJ *object)
{
    M401WorkPlayer *playerWork = object->data;
    playerWork->effectAnchorPosition.x = playerWork->worldPosition.x + cameraTarget.x;
    playerWork->effectAnchorPosition.y = object->trans.y;
    playerWork->effectAnchorPosition.z = 80 + object->trans.z;
}

void UpdatePlayerEffectAnchor(OMOBJ *object)
{
    M401WorkPlayer *playerWork;
    float horizontalOffset;
    float verticalOffset;
    float depthOffset;
    playerWork = object->data;
    horizontalOffset = 80.0 * sind(object->rot.y + 180.0f);
    depthOffset = 80.0 * -cosd(object->rot.y);
    verticalOffset = 80.0 * sind(object->rot.x);
    playerWork->effectAnchorPosition.x = object->trans.x + horizontalOffset;
    playerWork->effectAnchorPosition.y = object->trans.y + verticalOffset;
    playerWork->effectAnchorPosition.z = object->trans.z + depthOffset;
}

OMOBJ *FindClosestPlayer(OMOBJ *object);

void ReadCpuPlayerInput(OMOBJ *object, s8 *x, s8 *y, u16 *btn)
{
    M401WorkPlayer *playerWork;
    s32 playerIndex;
    OMOBJ *targetObject;
    s32 otherPlayerIndex;
    u16 avoidanceFlags = 0;
    float separationDistance;
    float movementSpeed;
    float movementAngle;
    s16 behaviorTable[][8] = {
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };
    Vec steeringVector;
    Vec playerPosition;
    Vec separationVector;
    Vec obstaclePosition;
    s16 horizontalInputChance[] = { 50, 125, 200, 245 };
    s16 verticalInputChance[] = { 75, 150, 200, 250 };
    s16 inputDelayByDifficulty[] = { 9, 6, 4, 2 };
    playerWork = object->data;
    *x = *y = 0;
    *btn = 0;
    if (playerWork->aiDecisionTimer == 0) {
        playerWork->aiBehavior = behaviorTable[GWPlayerCfg[playerWork->playerIndex].diff][frand() & 0x7];
        playerWork->aiDecisionTimer = (frand() % 60) + 30;
        playerWork->aiAvoidanceFlags = 0;
        if (frandu8() < horizontalInputChance[GWPlayerCfg[playerWork->playerIndex].diff]) {
            playerWork->aiAvoidanceFlags |= 1;
        }
        if (frandu8() < verticalInputChance[GWPlayerCfg[playerWork->playerIndex].diff]) {
            playerWork->aiAvoidanceFlags |= 2;
        }
    }
    else {
        playerWork->aiDecisionTimer--;
    }
    avoidanceFlags = playerWork->aiAvoidanceFlags;
    steeringVector.x = steeringVector.y = steeringVector.z = 0;
    switch (playerWork->aiBehavior) {
        case 0:
            targetObject = FindClosestPlayer(object);
            if (targetObject) {
                steeringVector.x = targetObject->trans.x - object->trans.x;
                steeringVector.y = targetObject->trans.y - object->trans.y;
                steeringVector.z = targetObject->trans.z - object->trans.z;
            }
            break;

        case 2:
            break;
    }
    if (avoidanceFlags & 0x1) {
        playerPosition.x = object->trans.x;
        playerPosition.y = object->trans.y;
        playerPosition.z = object->trans.z;
        for (otherPlayerIndex = 0; otherPlayerIndex < 4; otherPlayerIndex++) {
            if (playerObjects[otherPlayerIndex] != object) {
                obstaclePosition.x = playerObjects[otherPlayerIndex]->trans.x;
                obstaclePosition.y = playerObjects[otherPlayerIndex]->trans.y;
                obstaclePosition.z = playerObjects[otherPlayerIndex]->trans.z;
                VECSubtract(&playerPosition, &obstaclePosition, &separationVector);
                separationDistance = VECMag(&separationVector) - 110.0f;
                if (separationDistance < 110.0f) {
                    separationDistance -= 60.0f;
                    if (separationDistance < 0.01f) {
                        separationDistance = 0.01;
                    }
                    VECScale(&separationVector, &separationVector, 1.0f / separationDistance);
                    VECAdd(&steeringVector, &separationVector, &steeringVector);
                }
            }
        }
    }
    if (avoidanceFlags & 0x2) {
        for (playerIndex = 0; playerIndex < 4; playerIndex++) {
            if (fallingProjectileObjects[playerIndex]->objFunc != NULL) {
                obstaclePosition.x = fallingProjectileObjects[playerIndex]->trans.x;
                obstaclePosition.y = fallingProjectileObjects[playerIndex]->trans.y;
                obstaclePosition.z = fallingProjectileObjects[playerIndex]->trans.z;
                VECSubtract(&playerPosition, &obstaclePosition, &separationVector);
                separationDistance = VECMag(&separationVector) - 110.0f;
                if (separationDistance < 110.0f) {
                    separationDistance -= 60.0f;
                    if (separationDistance < 0.01f) {
                        separationDistance = 0.01;
                    }
                    VECScale(&separationVector, &separationVector, 1.0f / separationDistance);
                    VECAdd(&steeringVector, &separationVector, &steeringVector);
                }
            }
        }
        for (playerIndex = 0; playerIndex < 2; playerIndex++) {
            if (orbitingSceneObjects[playerIndex]->objFunc != NULL) {
                obstaclePosition.x = orbitingSceneObjects[playerIndex]->trans.x;
                obstaclePosition.y = orbitingSceneObjects[playerIndex]->trans.y;
                obstaclePosition.z = orbitingSceneObjects[playerIndex]->trans.z;
                VECSubtract(&playerPosition, &obstaclePosition, &separationVector);
                separationDistance = VECMag(&separationVector) - 110.0f;
                if (separationDistance < 110.0f) {
                    separationDistance -= 60.0f;
                    if (separationDistance < 0.01f) {
                        separationDistance = 0.01;
                    }
                    VECScale(&separationVector, &separationVector, 1.0f / separationDistance);
                    VECAdd(&steeringVector, &separationVector, &steeringVector);
                }
            }
        }
        obstaclePosition.x = movingObstacleObject->trans.x;
        obstaclePosition.y = movingObstacleObject->trans.y;
        obstaclePosition.z = movingObstacleObject->trans.z;
        VECSubtract(&playerPosition, &obstaclePosition, &separationVector);
        separationVector.x = 0;
        separationDistance = VECMag(&separationVector) - 220.0f;
        if (separationDistance < 220.0f) {
            separationDistance -= 160.0f;
            if (separationDistance < 0.01f) {
                separationDistance = 0.01;
            }
            VECScale(&separationVector, &separationVector, 1.0f / separationDistance);
            VECAdd(&steeringVector, &separationVector, &steeringVector);
        }
    }

    if (steeringVector.z < 0.0f) {
        if (playerWork->aiInputCooldown == 0) {
            *btn |= 0x100;
            playerWork->aiInputCooldown = (frand() % inputDelayByDifficulty[GWPlayerCfg[playerWork->playerIndex].diff]) + 3;
        }
        else {
            playerWork->aiInputCooldown--;
        }
    }
    steeringVector.z = 0;
    movementSpeed = VECMag(&steeringVector);
    movementSpeed *= 0.2f;
    movementAngle = atan2d(steeringVector.y, steeringVector.x);
    if (movementSpeed > 72.0f) {
        movementSpeed = 72.0f;
    }
    if (movementSpeed < 10.0f) {
        movementSpeed = 0.0f;
    }
    *x = movementSpeed * cosd(movementAngle);
    *y = movementSpeed * sind(movementAngle);
}

s32 FindNearbyObstacle(Vec *pos, float dist, OMOBJ **newobj);

s32 FindNearbyObstacleForPlayer(OMOBJ *object, OMOBJ **newobj)
{
    Vec targetPosition;
    targetPosition.x = object->trans.x;
    targetPosition.y = object->trans.y;
    targetPosition.z = object->trans.z - 100.0f;
    return FindNearbyObstacle(&targetPosition, 270.0f, newobj);
}

void SetCpuAvoidanceResponse(OMOBJ *object, s32 avoidanceDirection)
{
    M401WorkPlayer *playerWork;
    if (avoidanceDirection) {
        playerWork = object->data;
        playerWork->aiBehavior = 1;
        playerWork->aiDecisionTimer = 5;
        switch (avoidanceDirection) {
            case 1:
                playerWork->animationAngle = 180.0 + atan2d(playerWork->targetObject->trans.x - object->trans.x, playerWork->targetObject->trans.y - object->trans.y);
                break;

            case 2:
                if (playerWork->worldPosition.y > playerWork->targetObject->trans.y) {
                    playerWork->animationAngle = 80.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                else {
                    playerWork->animationAngle = 260.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                break;

            case 3:
                if (playerWork->worldPosition.y > playerWork->targetObject->trans.y) {
                    playerWork->animationAngle = 80.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                else {
                    playerWork->animationAngle = 260.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                break;
        }
    }
}

OMOBJ *FindClosestPlayer(OMOBJ *object)
{
    OMOBJ **playerObjects;
    s32 playerIndex;
    OMOBJ *closestPlayer;
    float depthDistance, horizontalDistance, verticalDistance;
    float weightedDistance, closestDistance;
    playerObjects = omGetGroupMemberListEx(HuPrcCurrentGet(), 1);
    closestDistance = 100000;
    closestPlayer = NULL;
    for (playerIndex = 0; playerIndex < 28; playerIndex++) {
        if (playerObjects[playerIndex] == NULL || playerObjects[playerIndex]->trans.z - cameraTarget.z > 850.0f
            || playerObjects[playerIndex]->trans.z - cameraTarget.z < -2500.0f) {
            continue;
        }
        horizontalDistance = playerObjects[playerIndex]->trans.x - object->trans.x;
        verticalDistance = playerObjects[playerIndex]->trans.y - object->trans.y;
        depthDistance = playerObjects[playerIndex]->trans.z - object->trans.z;
        depthDistance *= 0.15f;
        weightedDistance = VECMagPoint(horizontalDistance, verticalDistance, depthDistance);
        if (weightedDistance < closestDistance && weightedDistance < 2000.0f) {
            closestDistance = weightedDistance;
            closestPlayer = playerObjects[playerIndex];
        }
    }
    return closestPlayer;
}

void PlayPlayerEffects(s32 player);

void StunPlayer(OMOBJ *object)
{
    M401WorkPlayer *playerWork = object->data;
    playerWork->isStunned = 1;
    playerWork->stunTimer = 120;
    CharMotionShiftSet(playerWork->characterModelIndex, object->mtnId[7], 0, 10, HU3D_MOTATTR_NONE);
    PlayPlayerEffects(playerWork->playerIndex);
}

typedef struct FallingObjectWork {
    s16 objectState;
    Vec objectPosition;
    Vec objectVelocity;
    s16 activeDuration;
    s16 effectCooldown;
    s16 effectCount;
    s16 stateTimer;
    s16 effectState;
    float effectValue;
    s16 pathIndex;
    s16 pathPointIndex;
    float remainingPathDistance;
} FallingObjectWork;

void UpdateFallingObject(OMOBJ *object);

void CreateFallingObject(OMOBJ *object)
{
    FallingObjectWork *FallingObjectWork;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(FallingObjectWork), HU_MEMNUM_OVL);
    FallingObjectWork = object->data;
    FallingObjectWork->objectVelocity.x = 0;
    FallingObjectWork->objectVelocity.y = 200;
    FallingObjectWork->objectVelocity.z = 0;
    FallingObjectWork->effectCooldown = 0;
    FallingObjectWork->stateTimer = 100;
    FallingObjectWork->objectPosition.x = 0;
    FallingObjectWork->objectPosition.y = 200;
    FallingObjectWork->effectState = 0;
    FallingObjectWork->effectValue = 0;
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x0B));
    Hu3DModelClusterAttrSet(object->mdlId[0], 0, 0xC0000001);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAmbSet(object->mdlId[0], 0.6f, 0.6f, 0.6f);
    Hu3DModelShadowSet(object->mdlId[0]);
    FallingObjectWork->objectState = 0;
    FallingObjectWork->stateTimer = 180;
    omSetTra(object, 0, 200, 200);
    omSetRot(object, 0, 180, 0);
    object->objFunc = UpdateFallingObject;
}

void UpdateFallingObject(OMOBJ *object)
{
    FallingObjectWork *FallingObjectWork;
    FallingObjectWork = object->data;
    switch (FallingObjectWork->objectState) {
        case 0:
            if (--FallingObjectWork->stateTimer == 0) {
                FallingObjectWork->objectState = 1;
            }
            break;

        case 1:
            object->trans.z += -11.333333f;
            break;
    }
}

s32 gap0400000328Data = DATA_MAKE_NUM(DATADIR_M401, 0x0C);
s32 pathLastPointIndices[] = { 4, 6 };
Vec fallingObjectPathPoints[][10] = { {
                                 { 1400, -600, -21500 },
                                 { -100, 100, -22000 },
                                 { -1000, -200, -23000 },
                                 { -2000, -200, -23500 },
                                 { -2200, -200, -23500 },
                                 { -2300, -200, -23500 },
                             },
    {
        { -1000, 500, -29500 },
        { -300, 300, -31500 },
        { 300, -150, -32500 },
        { -200, 250, -34000 },
        { -300, 300, -35000 },
        { -600, 300, -36000 },
        { 1000, -180, -40000 },
        { 1000, -180, -40000 },
    }

};

void InterpolateFallingObjectPath(s32 pathIndex, s32 pointIndex, float interpolationT, Vec *position)
{
    Vec *previousPathPoint;
    Vec *startPathPoint;
    Vec *endPathPoint;
    Vec *nextPathPoint;
    float curveParameterSquared = interpolationT * interpolationT;
    if (pointIndex == 0) {
        previousPathPoint = &fallingObjectPathPoints[pathIndex][pointIndex];
        startPathPoint = &fallingObjectPathPoints[pathIndex][pointIndex + 1];
        endPathPoint = &fallingObjectPathPoints[pathIndex][pointIndex + 2];
        nextPathPoint = &fallingObjectPathPoints[pathIndex][pointIndex + 3];
        position->x = (0.5f
            * ((2.0f * previousPathPoint->x)
                + ((curveParameterSquared * (endPathPoint->x + (previousPathPoint->x - (2.0f * startPathPoint->x))))
                    + (interpolationT * (((-3.0f * previousPathPoint->x) + (4.0f * startPathPoint->x)) - endPathPoint->x)))));
        position->y = (0.5f
            * ((2.0f * previousPathPoint->y)
                + ((curveParameterSquared * (endPathPoint->y + (previousPathPoint->y - (2.0f * startPathPoint->y))))
                    + (interpolationT * (((-3.0f * previousPathPoint->y) + (4.0f * startPathPoint->y)) - endPathPoint->y)))));
        position->z = (0.5f
            * ((2.0f * previousPathPoint->z)
                + ((curveParameterSquared * (endPathPoint->z + (previousPathPoint->z - (2.0f * startPathPoint->z))))
                    + (interpolationT * (((-3.0f * previousPathPoint->z) + (4.0f * startPathPoint->z)) - endPathPoint->z)))));
    }
    else {
        previousPathPoint = &fallingObjectPathPoints[pathIndex][pointIndex - 1];
        startPathPoint = &fallingObjectPathPoints[pathIndex][pointIndex];
        endPathPoint = &fallingObjectPathPoints[pathIndex][pointIndex + 1];
        nextPathPoint = &fallingObjectPathPoints[pathIndex][pointIndex + 2];
        position->x = (0.5f
            * ((2.0f * startPathPoint->x)
                + ((interpolationT * (-previousPathPoint->x + endPathPoint->x))
                    + ((interpolationT * (curveParameterSquared * (nextPathPoint->x + ((-previousPathPoint->x + (3.0f * startPathPoint->x)) - (3.0f * endPathPoint->x)))))
                        + (curveParameterSquared * (((4.0f * endPathPoint->x) + ((2.0f * previousPathPoint->x) - (5.0f * startPathPoint->x))) - nextPathPoint->x))))));
        position->y = (0.5f
            * ((2.0f * startPathPoint->y)
                + ((interpolationT * (-previousPathPoint->y + endPathPoint->y))
                    + ((interpolationT * (curveParameterSquared * (nextPathPoint->y + ((-previousPathPoint->y + (3.0f * startPathPoint->y)) - (3.0f * endPathPoint->y)))))
                        + (curveParameterSquared * (((4.0f * endPathPoint->y) + ((2.0f * previousPathPoint->y) - (5.0f * startPathPoint->y))) - nextPathPoint->y))))));
        position->z = (0.5f
            * ((2.0f * startPathPoint->z)
                + ((interpolationT * (-previousPathPoint->z + endPathPoint->z))
                    + ((interpolationT * (curveParameterSquared * (nextPathPoint->z + ((-previousPathPoint->z + (3.0f * startPathPoint->z)) - (3.0f * endPathPoint->z)))))
                        + (curveParameterSquared * (((4.0f * endPathPoint->z) + ((2.0f * previousPathPoint->z) - (5.0f * startPathPoint->z))) - nextPathPoint->z))))));
    }
}

s32 AdvanceFallingObjectPath(OMOBJ *object)
{
    FallingObjectWork *FallingObjectWork;
    Vec *nextPathPoint;
    Vec *currentPathPoint;
    float segmentLength;
    Vec directionVector;
    Vec curvePosition;
    FallingObjectWork = object->data;
    while (1) {
        if (FallingObjectWork->pathPointIndex == pathLastPointIndices[FallingObjectWork->pathIndex]) {
            return 1;
        }
        currentPathPoint = &fallingObjectPathPoints[FallingObjectWork->pathIndex][FallingObjectWork->pathPointIndex + 1];
        nextPathPoint = &fallingObjectPathPoints[FallingObjectWork->pathIndex][FallingObjectWork->pathPointIndex];
        directionVector.x = currentPathPoint->x - nextPathPoint->x;
        directionVector.y = currentPathPoint->y - nextPathPoint->y;
        directionVector.z = currentPathPoint->z - nextPathPoint->z;
        segmentLength = VECMagPoint(directionVector.x, directionVector.y, directionVector.z);
        if (FallingObjectWork->remainingPathDistance > segmentLength) {
            FallingObjectWork->remainingPathDistance -= segmentLength;
            FallingObjectWork->pathPointIndex++;
            continue;
        }
        break;
    }
    InterpolateFallingObjectPath(FallingObjectWork->pathIndex, FallingObjectWork->pathPointIndex, FallingObjectWork->remainingPathDistance / segmentLength, &curvePosition);
    directionVector.x = curvePosition.x - object->trans.x;
    directionVector.y = curvePosition.y - object->trans.y;
    directionVector.z = curvePosition.z - object->trans.z;
    VECNormalize(&directionVector, &directionVector);
    object->trans.x = curvePosition.x;
    object->trans.y = curvePosition.y;
    object->trans.z = curvePosition.z;
    object->rot.y = atan2d(directionVector.x, directionVector.z);
    object->rot.x = -90.0f * directionVector.y;
    return 0;
}

s32 SpawnFallingObjectEffect(OMOBJ *object)
{
    FallingObjectWork *FallingObjectWork;
    Vec particlePosition;
    FallingObjectWork = object->data;
    if (object->trans.x > -400.0f && object->trans.x < 400.0f && object->trans.z - cameraTarget.z < 300.0f && object->trans.y > -300.0f
        && object->trans.y < 300.0f) {
        if (FallingObjectWork->effectCooldown == 0) {
            if (FallingObjectWork->effectCount != 0) {
                FallingObjectWork->effectCount--;
                particlePosition.x = object->trans.x;
                particlePosition.y = object->trans.y;
                particlePosition.z = object->trans.z - cameraTarget.z;
                CreateScoreParticleEffect(&particlePosition, 1);
                return 1;
            }
        }
        else {
            FallingObjectWork->effectCooldown--;
        }
    }
    return 0;
}

void UpdateFirstFallingObjectPath(OMOBJ *object);

void StartFirstFallingObjectPath(OMOBJ *object)
{
    FallingObjectWork *FallingObjectWork;
    FallingObjectWork = object->data;
    if (cameraTarget.z < -20800.0f) {
        Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
        FallingObjectWork->pathIndex = 0;
        FallingObjectWork->pathPointIndex = 0;
        FallingObjectWork->remainingPathDistance = 0;
        FallingObjectWork->effectCooldown = ((frand() % 10) + 13) * 0.43478262f;
        FallingObjectWork->effectCount = 2;
        AdvanceFallingObjectPath(object);
        object->objFunc = UpdateFirstFallingObjectPath;
    }
}

void StartSecondFallingObjectPath(OMOBJ *object);

void UpdateFirstFallingObjectPath(OMOBJ *object)
{
    FallingObjectWork *FallingObjectWork;
    FallingObjectWork = object->data;
    FallingObjectWork->remainingPathDistance += 25.875;
    if (SpawnFallingObjectEffect(object)) {
        FallingObjectWork->effectCooldown = ((frand() % 15) + 22) * 0.43478262f;
    }
    if (AdvanceFallingObjectPath(object)) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        object->objFunc = StartSecondFallingObjectPath;
    }
}

void UpdateSecondFallingObjectPath(OMOBJ *object);

void StartSecondFallingObjectPath(OMOBJ *object)
{
    FallingObjectWork *FallingObjectWork;
    FallingObjectWork = object->data;
    if (cameraTarget.z < -30500.0f) {
        Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
        FallingObjectWork->pathIndex = 1;
        FallingObjectWork->pathPointIndex = 0;
        FallingObjectWork->remainingPathDistance = 0;
        FallingObjectWork->effectCooldown = ((frand() % 60) + 50) * 0.43478262f;
        FallingObjectWork->effectCount = 3;
        AdvanceFallingObjectPath(object);
        object->objFunc = UpdateSecondFallingObjectPath;
    }
}

s32 fallingObjectEffectCooldowns[] = { 50, 95 };

void UpdateSecondFallingObjectPath(OMOBJ *object)
{
    FallingObjectWork *FallingObjectWork;
    FallingObjectWork = object->data;
    FallingObjectWork->remainingPathDistance += 25.875;
    if (SpawnFallingObjectEffect(object)) {
        FallingObjectWork->effectCooldown = ((frand() % 15) + fallingObjectEffectCooldowns[stageEventCounter++]) * 0.43478262f;
    }
    if (AdvanceFallingObjectPath(object)) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        object->objFunc = NULL;
    }
}

typedef struct OrbitingObjectWork {
    Vec normalizedDirection;
    Vec directionVector;
    Vec originPosition;
    Vec targetPosition;
    float travelDistance;
    Vec orbitParameters;
} OrbitingObjectWork;

void UpdateOrbitingObject(OMOBJ *object);

void CreateOrbitingObject(OMOBJ *object)
{
    OrbitingObjectWork *orbitWork;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(OrbitingObjectWork), HU_MEMNUM_OVL);
    orbitWork = object->data;
    orbitWork->targetPosition.x = 6;
    orbitWork->targetPosition.z = 90;
    orbitWork->targetPosition.y = 100;
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x0D));
    object->mtnId[0] = Hu3DJointMotionFile(object->mdlId[0], DATA_MAKE_NUM(DATADIR_M401, 0x10));
    Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    omSetTra(object, -1000, 0, -23000);
    omSetRot(object, 0, 90, 0);
    orbitWork->directionVector.x = 1000.0f - object->trans.x;
    orbitWork->directionVector.y = orbitWork->targetPosition.y - object->trans.y;
    orbitWork->directionVector.z = 0;
    orbitWork->orbitParameters.x = 1000;
    orbitWork->orbitParameters.y = 30;
    orbitWork->orbitParameters.z = 360.0f + ((1.0f / 255.0f) * frandu8());
    orbitWork->travelDistance = VECMagPoint(orbitWork->directionVector.x, orbitWork->directionVector.y, orbitWork->directionVector.z);
    VECNormalize(&orbitWork->directionVector, &orbitWork->normalizedDirection);
    Hu3DModelShadowSet(object->mdlId[0]);
    object->work[3] = 2;
    object->objFunc = UpdateOrbitingObject;
}

void StartOrbitingObject(OMOBJ *object, Vec *pos)
{
    OrbitingObjectWork *orbitWork;
    orbitWork = object->data;
    orbitWork->originPosition = *pos;
    orbitWork->orbitParameters.z = (1.0f / 255.0f) * (360.0f * frandu8());
    Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
    omSetTra(object, pos->x, pos->y, pos->z);
    object->work[2] = HuAudFXEmiterPlay(1284, &pos);
    object->objFunc = UpdateOrbitingObject;
}

void UpdateOrbitingObject(OMOBJ *object)
{
    OrbitingObjectWork *orbitWork;
    float orbitHeight;
    Vec soundEmitterPosition;
    orbitWork = object->data;
    object->trans.x = orbitWork->originPosition.x + 1000.0f * sind(orbitWork->orbitParameters.z);
    orbitHeight = (orbitWork->orbitParameters.y / orbitWork->orbitParameters.x) * sqrtf((orbitWork->orbitParameters.x * orbitWork->orbitParameters.x) - (object->trans.x * object->trans.x));
    if (orbitWork->orbitParameters.z >= 90.0f && orbitWork->orbitParameters.z <= 270.0f) {
        orbitHeight = -orbitHeight;
    }
    object->trans.z = orbitWork->originPosition.z + orbitHeight;
    orbitWork->orbitParameters.z += 0.6f + (0.6f * fabs(cosd(orbitWork->orbitParameters.z)));
    if (orbitWork->orbitParameters.z >= 360.0f) {
        orbitWork->orbitParameters.z -= 360.0f;
    }
    omSetRot(object, 0, 90.0f + orbitWork->orbitParameters.z, 0);
    soundEmitterPosition.x = object->trans.x;
    soundEmitterPosition.y = object->trans.y;
    soundEmitterPosition.z = object->trans.z;
    HuAudFXEmiterUpDate(object->work[2], &soundEmitterPosition);
    if (object->trans.z > cameraPosition.z - 220.0f) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        HuAudFXStop(object->work[2]);
        object->objFunc = NULL;
    }
}

void WaitForStageThreshold(OMOBJ *object);

void CreateMovingObstacle(OMOBJ *object)
{
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x18));
    object->mtnId[0] = Hu3DJointMotionFile(object->mdlId[0], DATA_MAKE_NUM(DATADIR_M401, 0x19));
    object->mtnId[1] = Hu3DJointMotionFile(object->mdlId[0], DATA_MAKE_NUM(DATADIR_M401, 0x1A));
    omSetTra(object, 3000, 0, -37000);
    omSetRot(object, 0, 270, 0);
    Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
    object->work[3] = 3;
    Hu3DModelShadowSet(object->mdlId[0]);
    object->objFunc = WaitForStageThreshold;
}

void SetMovingObstacleVisible(s32 flag)
{
    if (flag) {
        Hu3DModelAttrReset(movingObstacleObject->mdlId[0], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(movingObstacleObject->mdlId[0], HU3D_ATTR_DISPOFF);
    }
}

void MoveObstacleForward(OMOBJ *object);

void WaitForStageThreshold(OMOBJ *object)
{
    if (cameraTarget.z < -19000.0f) {
        SetMovingObstacleVisible(1);
        omSetTra(object, -2500, -800, -21000);
        omSetRot(object, 0, 125, 0);
        Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
        Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
        object->objFunc = MoveObstacleForward;
    }
}

void RespawnObstacle(OMOBJ *object);

void MoveObstacleForward(OMOBJ *object)
{
    object->trans.x += 2.3f * (26.0 * sind(object->rot.y));
    object->trans.z += 2.3f * (26.0 * cosd(object->rot.y));
    if (object->trans.x > 6000.0f) {
        SetMovingObstacleVisible(0);
        object->objFunc = RespawnObstacle;
    }
}

void MoveObstacleBackward(OMOBJ *object);

void RespawnObstacle(OMOBJ *object)
{
    float spawnHeight;
    if (cameraTarget.z <= -36200.0f + ((1.0f / 255.0f) * (200.0f * frandu8()))) {
        spawnHeight = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
        SetMovingObstacleVisible(1);
        omSetTra(object, 3000, spawnHeight, -37000);
        omSetRot(object, 0, 270, 0);
        Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
        Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
        object->objFunc = MoveObstacleBackward;
        soundEmitterPosition.x = object->trans.x;
        soundEmitterPosition.y = object->trans.y;
        soundEmitterPosition.z = object->trans.z;
        movingObstacleSoundEmitter = HuAudFXEmiterPlay(1286, &soundEmitterPosition);
    }
}

void MoveObstacleBackward(OMOBJ *object)
{
    object->trans.x += 2.3f * (17.0 * sind(object->rot.y));
    object->trans.z += 2.3f * (17.0 * cosd(object->rot.y));
    soundEmitterPosition.x = object->trans.x;
    soundEmitterPosition.y = object->trans.y;
    soundEmitterPosition.z = object->trans.z;
    HuAudFXEmiterUpDate(movingObstacleSoundEmitter, &soundEmitterPosition);
    if (object->trans.x <= -3000.0f) {
        SetMovingObstacleVisible(0);
        object->objFunc = NULL;
        HuAudFXStop(movingObstacleSoundEmitter);
    }
}

typedef struct FallingProjectileWork {
    Vec projectileMotion;
    s16 spawnDelay;
} FallingProjectileWork;

s32 fallingProjectileMotionIds[] = { DATA_MAKE_NUM(DATADIR_M401, 0x1C), DATA_MAKE_NUM(DATADIR_M401, 0x1D) };

void CreateFallingProjectiles(HUPROCESS *objman)
{
    OMOBJ *fallingObject;
    s32 motionIndex;
    s32 objectIndex;
    for (objectIndex = 0; objectIndex < 4; objectIndex++) {
        fallingObject = omAddObjEx(objman, 1130, 1, 2, -1, NULL);
        fallingProjectileObjects[objectIndex] = fallingObject;
        fallingObject->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x1B));
        for (motionIndex = 0; motionIndex < 2; motionIndex++) {
            fallingObject->mtnId[motionIndex] = Hu3DJointMotionFile(fallingObject->mdlId[0], fallingProjectileMotionIds[motionIndex]);
        }
        Hu3DModelAttrSet(fallingObject->mdlId[0], HU3D_ATTR_DISPOFF);
        fallingObject->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(FallingProjectileWork), HU_MEMNUM_OVL);
        Hu3DModelShadowSet(fallingObject->mdlId[0]);
        fallingObject->work[3] = 1;
    }
}

void UpdateFallingProjectile(OMOBJ *object);

void InitializeProjectileDistribution(float minimumSpacing, float maximumSpacing)
{
    s32 objectIndex;
    FallingProjectileWork *FallingObjectWork;
    float objectSpacing;
    float heightStep;
    float spawnHeight;
    heightStep = (maximumSpacing - minimumSpacing) / 4;
    objectSpacing = minimumSpacing;
    for (objectIndex = 0; objectIndex < 4; objectIndex++) {
        FallingObjectWork = fallingProjectileObjects[objectIndex]->data;
        Hu3DModelAttrReset(fallingProjectileObjects[objectIndex]->mdlId[0], HU3D_ATTR_DISPOFF);
        spawnHeight = -400.0f + ((1.0f / 255.0f) * (800.0f * frandu8()));
        FallingObjectWork->projectileMotion.x = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
        omSetTra(fallingProjectileObjects[objectIndex], spawnHeight, FallingObjectWork->projectileMotion.x + cameraTarget.y, objectSpacing);
        Hu3DMotionSet(fallingProjectileObjects[objectIndex]->mdlId[0], fallingProjectileObjects[objectIndex]->mtnId[0]);
        Hu3DModelAttrSet(fallingProjectileObjects[objectIndex]->mdlId[0], HU3D_MOTATTR_LOOP);
        objectSpacing += heightStep;
        FallingObjectWork->spawnDelay = (frand() % 30) + 30;
        FallingObjectWork->projectileMotion.z = 0;
        fallingProjectileObjects[objectIndex]->objFunc = UpdateFallingProjectile;
    }
}

OMOBJ *FindNearestPlayerToObject(OMOBJ *object)
{
    OMOBJ *playerObject;
    s32 playerIndex;
    OMOBJ *closestPlayer;
    M401WorkPlayer *playerWork;

    float candidateDistance;
    float closestDistance;
    closestDistance = 999999;
    for (playerIndex = 0; playerIndex < 4; playerIndex++) {
        float horizontalDistance;
        float verticalDistance;
        float depthDistance;
        playerObject = playerObjects[playerIndex];
        playerWork = playerObject->data;
        horizontalDistance = playerObject->trans.x - object->trans.x;
        verticalDistance = playerObject->trans.y - object->trans.y;
        depthDistance = 0.4f * (playerObject->trans.z - object->trans.z);
        candidateDistance = VECMagPoint(horizontalDistance, verticalDistance, depthDistance);
        if (candidateDistance < closestDistance) {
            closestPlayer = playerObjects[playerIndex];
            closestDistance = candidateDistance;
        }
    }
    return closestPlayer;
}

void UpdateFallingProjectile(OMOBJ *object)
{
    FallingProjectileWork *FallingObjectWork;
    OMOBJ *targetObject;
    M401WorkPlayer *targetPlayerWork;
    FallingObjectWork = object->data;
    if (0.0f == FallingObjectWork->projectileMotion.z) {
        if (FallingObjectWork->spawnDelay == 0) {
            targetObject = FindNearestPlayerToObject(object);
            targetPlayerWork = targetObject->data;
            FallingObjectWork->projectileMotion.y = atan2d(targetObject->trans.y - object->trans.y, targetObject->trans.x - object->trans.x);
            FallingObjectWork->projectileMotion.z = 8.0f + ((1.0f / 255.0f) * ((9.0f * frandu8())));
            Hu3DMotionSet(object->mdlId[0], object->mtnId[1]);
            Hu3DModelAttrReset(object->mdlId[0], HU3D_MOTATTR_LOOP);
            soundEmitterPosition.x = object->trans.x;
            soundEmitterPosition.y = object->trans.y;
            soundEmitterPosition.z = object->trans.z;
            HuAudFXEmiterPlay(1282, &soundEmitterPosition);
        }
        else {
            FallingObjectWork->spawnDelay--;
            FallingObjectWork->projectileMotion.x -= 2.5f;
        }
    }
    else {
        FallingObjectWork->projectileMotion.x = FallingObjectWork->projectileMotion.x + (FallingObjectWork->projectileMotion.z * sind(FallingObjectWork->projectileMotion.y));
        object->trans.x += FallingObjectWork->projectileMotion.z * cosd(FallingObjectWork->projectileMotion.y);
        FallingObjectWork->projectileMotion.z *= 0.94f;
        if (FallingObjectWork->projectileMotion.z < 0.1f) {
            FallingObjectWork->projectileMotion.z = 0;
            FallingObjectWork->spawnDelay = (frand() % 30) + 25;
            Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
            Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
        }
    }
    if (FallingObjectWork->projectileMotion.x < -300.0f) {
        FallingObjectWork->projectileMotion.x = -300.0f;
    }
    if (FallingObjectWork->projectileMotion.x > 300.0f) {
        FallingObjectWork->projectileMotion.x = 300.0f;
    }
    if (object->trans.x < -400.0f) {
        object->trans.x = -400.0f;
    }
    if (object->trans.x > 400.0f) {
        object->trans.x = 400.0f;
    }
    omSetTra(object, object->trans.x, FallingObjectWork->projectileMotion.x + cameraTarget.y, object->trans.z);
    if (object->trans.z > cameraPosition.z - 160.0f) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        object->objFunc = NULL;
    }
}

void SetObjectPosition(OMOBJ *object, float x, float y, float z)
{
    omSetTra(object, cameraTarget.x + x, cameraTarget.y + y, cameraTarget.z + z);
}

s32 playerEffectModelIds[] = { 0x12D, 0x16D, 0x1AD, 0x1ED, 0x22D, 0x26D, 0x2AD, 0x2ED };

void PlayPlayerEffects(s32 player)
{
    PlayerFXPlay(player, 301);
}

void CheckPlayerObstacleCollisions(OMOBJ *object)
{
    Vec playerPosition;
    OMOBJ *targetObject;
    M401WorkPlayer *playerWork;
    s32 playerIndex;
    playerWork = object->data;
    if (playerWork->isStunned != 0) {
        return;
    }
    playerPosition.x = object->trans.x;
    playerPosition.y = object->trans.y;
    playerPosition.z = object->trans.z;
    if ((playerIndex = FindNearbyObstacle(&playerPosition, 90, &targetObject)) != 0) {
        if (playerIndex == 1) {
            omVibrate(playerWork->playerIndex, 12, 4, 2);
        }
        else if (playerIndex == 3) {
            omVibrate(playerWork->playerIndex, 12, 4, 2);
        }
        else {
            omVibrate(playerWork->playerIndex, 12, 12, 0);
        }
        StunPlayer(object);
        ShowScoreLossPopup(playerWork->playerIndex, targetObject->work[3]);
    }
}

s32 FindNearbyObstacle(Vec *pos, float dist, OMOBJ **newobj)
{
    OMOBJ *obstacleObject;
    s32 obstacleIndex;
    float obstacleDistance;
    float obstacleX;
    float obstacleZ;
    FallingProjectileWork *FallingObjectWork;
    float obstacleY;

    *newobj = NULL;
    for (obstacleIndex = 0; obstacleIndex < 4; obstacleIndex++) {
        obstacleObject = fallingProjectileObjects[obstacleIndex];
        if (obstacleObject->objFunc != NULL) {
            FallingObjectWork = obstacleObject->data;
            obstacleDistance = VECMagPoint(pos->x - obstacleObject->trans.x, pos->y - obstacleObject->trans.y, pos->z - obstacleObject->trans.z);
            if (obstacleDistance < sqrtf(1024.0f + (dist * dist))) {
                *newobj = obstacleObject;
                return 1;
            }
        }
    }
    obstacleObject = movingObstacleObject;
    obstacleDistance = VECDistanceZY(pos, &obstacleObject->trans);
    if (obstacleDistance < sqrtf(6400.0f + (dist * dist)) && obstacleObject->trans.x < pos->x - (dist / 2.0f)
        && 1500.0f + obstacleObject->trans.x > pos->x + (dist / 2.0f)) {
        *newobj = obstacleObject;
        return 2;
    }
    for (obstacleIndex = 0; obstacleIndex < 2; obstacleIndex++) {
        if (orbitingSceneObjects[obstacleIndex]->objFunc != NULL) {
            obstacleX = orbitingSceneObjects[obstacleIndex]->trans.x + (70.0 * sind(orbitingSceneObjects[obstacleIndex]->rot.y));
            obstacleZ = orbitingSceneObjects[obstacleIndex]->trans.z + (70.0 * cosd(orbitingSceneObjects[obstacleIndex]->rot.y));
            obstacleY = orbitingSceneObjects[obstacleIndex]->trans.y - 10.0f;
            obstacleDistance = VECMagPoint(pos->x - obstacleX, pos->y - obstacleY, pos->z - obstacleZ);
            if (obstacleDistance < sqrtf(4900.0f + (dist * dist))) {
                *newobj = orbitingSceneObjects[obstacleIndex];
                return 3;
            }
            obstacleX = orbitingSceneObjects[obstacleIndex]->trans.x;
            obstacleZ = orbitingSceneObjects[obstacleIndex]->trans.z;
            obstacleY = orbitingSceneObjects[obstacleIndex]->trans.y - 10.0f;
            obstacleDistance = VECMagPoint(pos->x - obstacleX, pos->y - obstacleY, pos->z - obstacleZ);
            if (obstacleDistance < sqrtf(4900.0f + (dist * dist))) {
                *newobj = orbitingSceneObjects[obstacleIndex];
                return 3;
            }
            obstacleX = orbitingSceneObjects[obstacleIndex]->trans.x + (70.0 * sind(orbitingSceneObjects[obstacleIndex]->rot.y + 180.0f));
            obstacleZ = orbitingSceneObjects[obstacleIndex]->trans.z + (70.0 * cosd(orbitingSceneObjects[obstacleIndex]->rot.y + 180.0f));
            obstacleY = orbitingSceneObjects[obstacleIndex]->trans.y - 10.0f;
            obstacleDistance = VECMagPoint(pos->x - obstacleX, pos->y - obstacleY, pos->z - obstacleZ);
            if (obstacleDistance < sqrtf(4410.0f + (dist * dist))) {
                *newobj = orbitingSceneObjects[obstacleIndex];
                return 3;
            }
        }
    }
    return 0;
}

void UpdateFallingCamera(OMOBJ *object);

void UpdateStartCountdown(OMOBJ *object)
{
    s32 playerIndex;
    M401WorkPlayer *playerWork;
    switch (object->work[0]) {
        case 0:
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            ;
            object->work[0] = 1;
            break;

        case 1:
            if (!WipeStatGet()) {
                object->work[0] = 2;
                object->work[1] = 180;
            }
            break;

        case 2:
            if (object->work[1] == 0) {
                minigameSequenceId = MGSeqStartCreate();
                object->work[0] = 3;
                audioSequenceId = HuAudSeqPlay(68);
            }
            else {
                object->work[1]--;
            }
            break;

        case 3:
            if (!MGSeqStatGet(minigameSequenceId)) {
                SetScoreHudVisible(1);
                cameraAspectRatio = 1;
                SetupSceneSectionOne(tunnelSceneObject);

                tunnelSceneObject->objFunc = UpdateTunnelSceneEvents;
                for (playerIndex = 0; playerIndex < 4; playerIndex++) {
                    playerWork = playerObjects[playerIndex]->data;
                    playerWork->movementParameters.z = 0;
                    playerWork->targetPosition.z = 800;
                    playerObjects[playerIndex]->objFunc = UpdatePlayerControl;
                    object->trans.x = object->trans.y = object->trans.z = 0;
                }
                fallingObjectSceneObject->objFunc = StartFirstFallingObjectPath;
                omDelObjEx(HuPrcCurrentGet(), object);
                sequenceControllerObject = NULL;
                unusedObjectHandle4->objFunc = UpdateFallingCamera;
            }

            break;
    }
}

void UpdateMinigameResults(OMOBJ *object)
{
    M401WorkPlayer *playerWork;
    s32 playerIndex;
    HU3DLIGHT *light;
    Vec cameraPosition;
    Vec cameraDirection;
    switch (object->work[0]) {
        case 0:
            if (!MGSeqStatGet(minigameSequenceId)) {
                object->work[0] = 1;
                #if VERSION_NTSC
                HuAudFXStop(soundEffectHandle);
                #else
                HuAudFXFadeOut(soundEffectHandle, 500);
                #endif
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                WipeColorSet(255, 255, 255);
            }
            break;

        case 1:
            if (WipeStatGet()) {
                return;
            }
            Hu3DFogClear();
            light = &Hu3DGlobalLight[0];
            light->color.r = 255;
            light->color.g = 255;
            light->color.b = 255;
            cameraPosition.x = 0;
            cameraPosition.y = 2500;
            cameraPosition.z = 1000;
            cameraDirection.x = 0;
            cameraDirection.y = 1030;
            cameraDirection.z = 0;
            Hu3DGLightPosAimSetV(globalLightId, &cameraPosition, &cameraDirection);
            shadowLightPosition.x = 0;
            shadowLightPosition.y = 2500;
            shadowLightPosition.z = 1000;
            shadowLightTarget.x = 0;
            shadowLightTarget.y = 1030;
            shadowLightTarget.z = 0;
            Hu3DShadowPosSet(&shadowLightPosition, &shadowLightUpVector, &shadowLightTarget);
            HuAudAUXVolSet(-1, -1);
            CleanupSceneSectionFive(tunnelSceneObject);
            for (playerIndex = 0; playerIndex < 4; playerIndex++) {
                playerWork = playerObjects[playerIndex]->data;
                playerWork->scoreEffect->work[0] = 1;
                playerWork->stateInitialized = 0;
                CharMotionSet(((M401WorkPlayer *)(playerObjects[playerIndex]->data))->characterModelIndex, playerObjects[playerIndex]->mtnId[4]);
                Hu3DModelAttrReset(playerObjects[playerIndex]->mdlId[0], HU3D_MOTATTR_LOOP);
                playerObjects[playerIndex]->objFunc = UpdatePlayerResults;
                Hu3DModelAmbSet(playerObjects[playerIndex]->mdlId[0], 0.7f, 0.7f, 0.7f);
                omSetTra(playerObjects[playerIndex], -225.0f + (playerIndex * 150), 740, 400);
                omSetRot(playerObjects[playerIndex], 0, 0, 0);
                if (playerWork->isRoundWinner) {
                    if (winnerCount == 1) {
                        playerWork->playerState = 10;
                        playerWork->movementParameters.x = 13;
                    }
                    else {
                        playerWork->movementParameters.x = 10;
                        playerWork->playerState = 6;
                    }
                    OSReport("GetCoin:%d\n", playerIndex);
                    GWPlayerCoinWinSet(playerIndex, 10);
                }
                else {
                    playerWork->movementParameters.x = 10;
                    playerWork->playerState = 6;
                }
            }
            ConfigureTunnelScene(tunnelSceneObject);
            object->work[0] = 2;
            flockingParticleObject->work[0] = 1;
            CreateParticleEffectController();
            tunnelSceneObject->objFunc = UpdateBridgeScene;
            soundEffectHandle = HuAudFXPlay(1280);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            omDelObjEx(HuPrcCurrentGet(), sceneTransitionObject);
            break;

        case 2:
            WipeStatGet() == 0;
            break;
    }
}

typedef struct OrbitingParticleGroupWork {
    Vec particlePositions[9];
    float particleOpacity[9];
} OrbitingParticleGroupWork;

void SetOrbitingParticleMotionTime(s16 modelIndex);

void UpdateOrbitingParticleGroup(OMOBJ *object);

void CreateOrbitingParticleGroup(OMOBJ *object)
{
    s32 modelIndex;
    float motionTime;
    OrbitingParticleGroupWork *particleWork;
    particleWork = object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(OrbitingParticleGroupWork), HU_MEMNUM_OVL);
    for (modelIndex = 0; modelIndex < 9; modelIndex++) {
        if (modelIndex == 0) {
            object->mdlId[modelIndex] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x02));
        }
        else {
            object->mdlId[modelIndex] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x02));
        }
        Hu3DModelLayerSet(object->mdlId[modelIndex], 1);
        SetOrbitingParticleMotionTime(modelIndex);
        motionTime = (1.0f / 255.0f) * (Hu3DMotionMaxTimeGet(object->mdlId[modelIndex]) * frandu8());
        Hu3DMotionTimeSet(object->mdlId[modelIndex], motionTime);
    }
    omSetStatBit(object, 0x100);
    object->objFunc = UpdateOrbitingParticleGroup;
}

void SetOrbitingParticleMotionTime(s16 modelIndex)
{
    OrbitingParticleGroupWork *particleWork;
    float particleDistance, particleAngle;
    particleWork = orbitingParticleObject->data;
    particleAngle = (1.0f / 255.0f) * (360.0f * frandu8());
    particleDistance = (1.0f / 255.0f) * (200.0f * frandu8());
    particleWork->particlePositions[modelIndex].x = particleDistance * cosd(particleAngle);
    particleWork->particlePositions[modelIndex].z = particleDistance * sind(particleAngle);
    particleWork->particlePositions[modelIndex].y = 1000;
    particleWork->particleOpacity[modelIndex] = 1.0f;
    particleDistance *= 0.25f;
    Hu3DModelRotSet(orbitingParticleObject->mdlId[modelIndex], particleDistance * sind(particleAngle), 0, particleDistance * cosd(particleAngle));
    Hu3DMotionTimeSet(orbitingParticleObject->mdlId[modelIndex], 0);
}

void UpdateOrbitingParticleGroup(OMOBJ *object)
{
    s32 modelIndex;
    OrbitingParticleGroupWork *particleWork;
    u8 particleIndex;
    float particleLifetime;
    particleWork = object->data;
    for (modelIndex = 0; modelIndex < 9; modelIndex++) {
        Hu3DModelPosSet(
            object->mdlId[modelIndex], particleWork->particlePositions[modelIndex].x, particleWork->particlePositions[modelIndex].y, activeCameraTarget.z + particleWork->particlePositions[modelIndex].z - 500);
        Hu3DModelTPLvlSet(object->mdlId[modelIndex], particleWork->particleOpacity[modelIndex]);
        particleLifetime = Hu3DMotionTimeGet(object->mdlId[modelIndex]) / Hu3DMotionMaxTimeGet(object->mdlId[modelIndex]);
        particleWork->particleOpacity[modelIndex] = 1.0f - particleLifetime;
        if (Hu3DMotionTimeGet(object->mdlId[modelIndex]) >= Hu3DMotionMaxTimeGet(object->mdlId[modelIndex])) {
            SetOrbitingParticleMotionTime(modelIndex);
        }
    }
    if (cameraTarget.z <= -26800.0f && cameraTarget.z >= -27400.0f) {
        particleIndex = 255.0f - (223.0f * (-(cameraTarget.z + 26800.0f) / 600.0f));
        if (particleIndex < 32) {
            particleIndex = 32;
        }
    }
    else if (cameraTarget.z <= -27700.0f && cameraTarget.z >= -28300.0f) {
        particleIndex = 32.0f + (223.0f * (-(cameraTarget.z + 27700.0f) / 600.0f));
    }
    else if (cameraTarget.z < -27400.0f && cameraTarget.z > -28300.0f) {
        particleIndex = 32;
    }
    else {
        particleIndex = 255;
    }
    Hu3DGLightColorSet(globalLightId, particleIndex, particleIndex, particleIndex, 255);
    if (cameraTarget.z < -26600.0f && cameraTarget.z > -27500.0f) {
        for (modelIndex = 0; modelIndex < 9; modelIndex++) {
            Hu3DModelAttrSet(object->mdlId[modelIndex], HU3D_ATTR_DISPOFF);
        }
    }
    else {
        for (modelIndex = 0; modelIndex < 9; modelIndex++) {
            Hu3DModelAttrReset(object->mdlId[modelIndex], HU3D_ATTR_DISPOFF);
        }
    }
}

void CaptureCameraState(OMOBJ *object)
{
    HU3DCAMERA *camera = &Hu3DCamera[0];
    Vec cameraDirection;

    cameraPosition = camera->pos;
    cameraTarget = camera->target;
    VECSubtract(&cameraPosition, &previousCameraPosition, &cameraDirection);
    cameraMoveDistance = VECMag(&cameraDirection);
    previousCameraPosition = cameraPosition;

    ResetSceneFog();
}

void SetCameraVerticalOffset(float verticalOffset)
{
    Vec cameraPosition;
    Vec cameraDirection;
    activeCameraPosition.x = 0;
    activeCameraPosition.y = 0;
    activeCameraPosition.z = verticalOffset;
    activeCameraTarget.x = 0;
    activeCameraTarget.y = 0;
    activeCameraTarget.z = -1500 + verticalOffset;
    cameraUpVector.x = 0;
    cameraUpVector.y = 1;
    cameraUpVector.z = 0;
    Hu3DCameraPosSetV(1, &activeCameraPosition, &cameraUpVector, &activeCameraTarget);
    Hu3DModelPosSet(tunnelSceneObject->mdlId[1], 0, 0, -1500 + verticalOffset);
    shadowLightPosition.y = 3500 + activeCameraTarget.y;
    shadowLightPosition.z = 1500 + activeCameraTarget.z;
    shadowLightTarget.y = activeCameraTarget.y - 200;
    shadowLightTarget.z = 500 + activeCameraTarget.z;
    Hu3DShadowPosSet(&shadowLightPosition, &shadowLightUpVector, &shadowLightTarget);
    cameraPosition = activeCameraPosition;
    VECSubtract(&activeCameraTarget, &cameraPosition, &cameraDirection);
    VECNormalize(&cameraDirection, &cameraDirection);
    HuAudFXListnerUpdate(&cameraPosition, &cameraDirection);
}

void UpdateCameraTransition(OMOBJ *object)
{
    Vec cameraPosition;
    Vec cameraDirection;
    float wipeProgress = 1.5f * object->scale.x;
    activeCameraPosition.x = object->trans.x + (-object->trans.x * sind(wipeProgress));
    activeCameraPosition.y = object->trans.y + (-object->trans.y * sind(wipeProgress));
    activeCameraPosition.z = object->trans.z + (-object->trans.z * sind(wipeProgress));
    activeCameraTarget.x = object->rot.x + (-object->rot.x * sind(wipeProgress));
    activeCameraTarget.y = object->rot.y + (-object->rot.y * sind(wipeProgress));
    activeCameraTarget.z = object->rot.z + ((-1500.0f - object->rot.z) * sind(wipeProgress));
    cameraUpVector.x = 0;
    cameraUpVector.y = 1;
    cameraUpVector.z = 0;
    object->scale.x += 1.0f;
    if (object->scale.x > 60.0f) {
        activeCameraPosition.x = 0;
        activeCameraPosition.y = 0;
        activeCameraPosition.z = 0;
        activeCameraTarget.x = 0;
        activeCameraTarget.y = 0;
        activeCameraTarget.z = -1500;
    }
    Hu3DCameraPosSetV(1, &activeCameraPosition, &cameraUpVector, &activeCameraTarget);
    previousCameraPosition = activeCameraPosition;
    shadowLightPosition.y = 3500 + activeCameraTarget.y;
    shadowLightPosition.z = 1500 + activeCameraTarget.z;
    shadowLightTarget.y = activeCameraTarget.y - 200;
    shadowLightTarget.z = 500 + activeCameraTarget.z;
    Hu3DShadowPosSet(&shadowLightPosition, &shadowLightUpVector, &shadowLightTarget);
    cameraPosition = activeCameraPosition;
    VECSubtract(&activeCameraTarget, &activeCameraPosition, &cameraDirection);
    VECNormalize(&cameraDirection, &cameraDirection);
    HuAudFXListnerUpdate(&cameraPosition, &cameraDirection);
    if (object->scale.x > 60.0f) {
        cameraNearPlane = 100;
        Hu3DCameraPerspectiveSet(1, cameraFieldOfView, cameraNearPlane, cameraFarPlane, 1.2f);
        object->scale.x = 0;
        object->objFunc = NULL;
    }
}

void UpdateFallingCamera(OMOBJ *object)
{
    if (minigameExitReady != 0) {
        return;
    }
    gravityAcceleration *= 1.05f;
    if (gravityAcceleration < -14.375f) {
        gravityAcceleration = -14.375f;
    }
    object->scale.x += gravityAcceleration;
    SetCameraVerticalOffset(object->scale.x);
}

s32 flockingParticleModelIds[] = { DATA_MAKE_NUM(DATADIR_M401, 0x04), DATA_MAKE_NUM(DATADIR_M401, 0x05), DATA_MAKE_NUM(DATADIR_M401, 0x06) };

typedef struct FlockingParticleEffectWork {
    s16 particleCount;
    Vec spawnOrigin;
    float currentLifetime;
    float neighborRadius;
    float baseSpeed;
    float separationWeight;
    float obstacleWeight;
    float alignmentWeight;
    float cohesionWeight;
    float originWeight;
    s8 *particleSlotUsed;
    Vec *particlePositions;
    Vec *particleDirections;
    Vec *separationForces;
    Vec *alignmentForces;
    Vec *neighborCenters;
    Vec *originForces;
    Vec *obstacleForces;
    s16 *neighborCounts;
    s16 *particleGroups;
    float *particleSpeeds;
    float *particleYawAngles;
    float *particlePitchAngles;
    float *particleRollAngles;
    float *particleRollVelocities;
} FlockingParticleEffectWork;

void CreateSharedParticleModels(s16 modelCount)
{
    OMOBJ *effectObject;
    s32 modelIndex;
    s8 *modelVisibility;
    float modelScale;
    effectObject = sharedParticleModelObject = omAddObjEx(minigameObjectManager, 1145, modelCount, 0, -1, NULL);
    omSetStatBit(effectObject, 0x100);
    effectObject->data = HuMemDirectMallocNum(HEAP_HEAP, modelCount * sizeof(s8), HU_MEMNUM_OVL);
    modelVisibility = effectObject->data;
    effectObject->work[0] = modelCount;
    for (modelIndex = 0; modelIndex < modelCount; modelIndex++) {
        if (modelIndex < 3) {
            effectObject->mdlId[modelIndex] = Hu3DModelCreateFile(flockingParticleModelIds[modelIndex]);
        }
        else {
            effectObject->mdlId[modelIndex] = Hu3DModelLink(effectObject->mdlId[modelIndex % 3]);
        }
        modelScale = 0.5f + ((1.0f / 255.0f) * (0.5f * frandu8()));
        Hu3DModelScaleSet(effectObject->mdlId[modelIndex], modelScale, modelScale, modelScale);
        Hu3DModelAttrSet(effectObject->mdlId[modelIndex], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(effectObject->mdlId[modelIndex], HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(effectObject->mdlId[modelIndex], (1.0f / 255.0f) * (Hu3DMotionMaxTimeGet(effectObject->mdlId[modelIndex]) * frandu8()));
        modelVisibility[modelIndex] = 0;
    }
}

void FreeFlockingParticleWork(FlockingParticleEffectWork *effectWork)
{
    HuMemDirectFree(effectWork->particlePositions);
    HuMemDirectFree(effectWork->particleDirections);
    HuMemDirectFree(effectWork->alignmentForces);
    HuMemDirectFree(effectWork->neighborCenters);
    HuMemDirectFree(effectWork->originForces);
    HuMemDirectFree(effectWork->obstacleForces);
    HuMemDirectFree(effectWork->separationForces);
    HuMemDirectFree(effectWork->neighborCounts);
    HuMemDirectFree(effectWork->particleGroups);
    HuMemDirectFree(effectWork->particleSpeeds);
    HuMemDirectFree(effectWork->particleYawAngles);
    HuMemDirectFree(effectWork->particlePitchAngles);
    HuMemDirectFree(effectWork->particleRollAngles);
    HuMemDirectFree(effectWork->particleRollVelocities);
    HuMemDirectFree(effectWork->particleSlotUsed);
}

OMOBJ *CreateFlockingParticleWork(s16 particleCount)
{
    FlockingParticleEffectWork *effectWork;
    s32 slotIndex;
    OMOBJ *effectObject;
    s32 effectIndex;
    s8 *availableSlots;
    if (particleCount <= 0) {
        return NULL;
    }
    effectObject = omAddObjEx(minigameObjectManager, 1145, particleCount, 0, -1, NULL);
    omSetStatBit(effectObject, 0x100);
    effectObject->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(FlockingParticleEffectWork), HU_MEMNUM_OVL);
    effectWork = effectObject->data;
    effectWork->particlePositions = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(Vec), HU_MEMNUM_OVL);
    effectWork->particleDirections = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(Vec), HU_MEMNUM_OVL);
    effectWork->alignmentForces = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(Vec), HU_MEMNUM_OVL);
    effectWork->neighborCenters = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(Vec), HU_MEMNUM_OVL);
    effectWork->originForces = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(Vec), HU_MEMNUM_OVL);
    effectWork->obstacleForces = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(Vec), HU_MEMNUM_OVL);
    effectWork->separationForces = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(Vec), HU_MEMNUM_OVL);
    effectWork->neighborCounts = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(s16), HU_MEMNUM_OVL);
    effectWork->particleGroups = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(s16), HU_MEMNUM_OVL);
    effectWork->particleSpeeds = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(float), HU_MEMNUM_OVL);
    effectWork->particleYawAngles = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(float), HU_MEMNUM_OVL);
    effectWork->particlePitchAngles = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(float), HU_MEMNUM_OVL);
    effectWork->particleRollAngles = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(float), HU_MEMNUM_OVL);
    effectWork->particleRollVelocities = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(float), HU_MEMNUM_OVL);
    effectWork->particleSlotUsed = HuMemDirectMallocNum(HEAP_HEAP, particleCount * sizeof(s8), HU_MEMNUM_OVL);
    for (effectIndex = 0; effectIndex < particleCount; effectIndex++) {
        availableSlots = sharedParticleModelObject->data;
        for (slotIndex = 0; slotIndex < sharedParticleModelObject->work[0]; slotIndex++) {
            if (availableSlots[slotIndex] == 0) {
                availableSlots[slotIndex] = 1;
                effectObject->mdlId[effectIndex] = sharedParticleModelObject->mdlId[slotIndex];
                effectWork->particleGroups[effectIndex] = slotIndex % 3;
                effectWork->particleSlotUsed[effectIndex] = slotIndex;
                break;
            }
        }
        if (slotIndex == sharedParticleModelObject->work[0]) {
            particleCount -= (s32)particleCount - effectIndex;
            break;
        }
    }
    if (particleCount == 0) {
        FreeFlockingParticleWork(effectWork);
        omDelObjEx(HuPrcCurrentGet(), effectObject);
        effectObject = NULL;
    }
    else {
        effectWork->particleCount = particleCount;
        effectWork->currentLifetime = 0;
    }
    return effectObject;
}

void DestroyFlockingParticleEffect(OMOBJ *object)
{
    FlockingParticleEffectWork *effectWork;
    s32 modelIndex;
    s8 *availableSlots;
    effectWork = object->data;
    availableSlots = sharedParticleModelObject->data;
    for (modelIndex = 0; modelIndex < effectWork->particleCount; modelIndex++) {
        availableSlots[effectWork->particleSlotUsed[modelIndex]] = 0;
        Hu3DModelAttrSet(object->mdlId[modelIndex], HU3D_ATTR_DISPOFF);
    }
    FreeFlockingParticleWork(effectWork);
    omDelObjEx(HuPrcCurrentGet(), object);
}

void UpdateFlockingParticles(OMOBJ *object);

void SetFlockingParticlesVisible(OMOBJ *object, s16 isVisible)
{
    s32 modelIndex;
    FlockingParticleEffectWork *effectWork = object->data;
    if (isVisible == 1) {
        for (modelIndex = 0; modelIndex < effectWork->particleCount; modelIndex++) {
            Hu3DModelAttrReset(object->mdlId[modelIndex], HU3D_ATTR_DISPOFF);
        }
        object->objFunc = UpdateFlockingParticles;
    }
    else {
        for (modelIndex = 0; modelIndex < effectWork->particleCount; modelIndex++) {
            Hu3DModelAttrSet(object->mdlId[modelIndex], HU3D_ATTR_DISPOFF);
        }
        object->objFunc = NULL;
    }
}

void InitializeFlockingParticles(OMOBJ *object, Vec *spawnOrigin, Vec *spawnRadius)
{
    FlockingParticleEffectWork *effectWork = object->data;
    s32 effectIndex;
    for (effectIndex = 0; effectIndex < effectWork->particleCount; effectIndex++) {
        effectWork->particlePositions[effectIndex].x = (spawnOrigin->x - spawnRadius->x) + ((1.0f / 255.0f) * (2.0f * spawnRadius->x * frandu8()));
        effectWork->particlePositions[effectIndex].y = (spawnOrigin->y - spawnRadius->y) + ((1.0f / 255.0f) * (2.0f * spawnRadius->y * frandu8()));
        effectWork->particlePositions[effectIndex].z = (spawnOrigin->z - spawnRadius->z) + ((1.0f / 255.0f) * (2.0f * spawnRadius->z * frandu8()));
        VECNormalize(&effectWork->particlePositions[effectIndex], &effectWork->particleDirections[effectIndex]);
        effectWork->particleYawAngles[effectIndex] = effectWork->particleRollAngles[effectIndex] = effectWork->particlePitchAngles[effectIndex] = effectWork->particleRollVelocities[effectIndex] = 0;
        effectWork->particleSpeeds[effectIndex] = 0.1f;
        Hu3DModelPosSet(object->mdlId[effectIndex], effectWork->particlePositions[effectIndex].x, effectWork->particlePositions[effectIndex].y, effectWork->particlePositions[effectIndex].z);
    }
}

void SetFlockingParticleOrigin(OMOBJ *object, Vec *pos)
{
    FlockingParticleEffectWork *effectWork = object->data;
    effectWork->spawnOrigin = *pos;
}

void SetFlockingParticleMotion(OMOBJ *object, float neighborRadius, float baseSpeed)
{
    FlockingParticleEffectWork *effectWork = object->data;
    effectWork->neighborRadius = neighborRadius;
    effectWork->baseSpeed = baseSpeed;
}

void SetFlockingParticleWeights(OMOBJ *object, float separationWeight, float obstacleWeight, float alignmentWeight, float cohesionWeight, float originWeight)
{
    FlockingParticleEffectWork *effectWork = object->data;
    effectWork->separationWeight = separationWeight;
    effectWork->obstacleWeight = obstacleWeight;
    effectWork->alignmentWeight = alignmentWeight;
    effectWork->cohesionWeight = cohesionWeight;
    effectWork->originWeight = originWeight;
}

void UpdateFlockingParticles(OMOBJ *object)
{
    FlockingParticleEffectWork *effectWork = object->data;
    s32 effectIndex;
    s32 neighborIndex;
    float alignmentDotProduct;
    float obstacleDistance;
    float normalizationLength;
    float neighborDistance;
    float combinedForceMagnitude;
    Mtx translationMatrix, pitchMatrix, yawMatrix, rollMatrix, combinedRotationMatrix, particleMatrix;
    Vec particleDifference, forceVector, playerPosition, obstacleDifference, originDifference, combinedForce, horizontalForce, directionVector;
    for (effectIndex = 0; effectIndex < effectWork->particleCount; effectIndex++) {
        effectWork->separationForces[effectIndex].x = 0;
        effectWork->separationForces[effectIndex].y = 0;
        effectWork->separationForces[effectIndex].z = 0;
        effectWork->alignmentForces[effectIndex].x = 0;
        effectWork->alignmentForces[effectIndex].y = 0;
        effectWork->alignmentForces[effectIndex].z = 0;
        effectWork->neighborCenters[effectIndex].x = 0;
        effectWork->neighborCenters[effectIndex].y = 0;
        effectWork->neighborCenters[effectIndex].z = 0;
        effectWork->originForces[effectIndex].x = 0;
        effectWork->originForces[effectIndex].y = 0;
        effectWork->originForces[effectIndex].z = 0;
        effectWork->obstacleForces[effectIndex].x = 0;
        effectWork->obstacleForces[effectIndex].y = 0;
        effectWork->obstacleForces[effectIndex].z = 0;
        effectWork->neighborCounts[effectIndex] = 0;
    }
    for (effectIndex = 0; effectIndex < effectWork->particleCount; effectIndex++) {
        for (neighborIndex = effectIndex + 1; neighborIndex < effectWork->particleCount; neighborIndex++) {
            VECSubtract(&effectWork->particlePositions[effectIndex], &effectWork->particlePositions[neighborIndex], &particleDifference);
            neighborDistance = VECMag(&particleDifference);
            if (neighborDistance < effectWork->neighborRadius) {
                VECScale(&particleDifference, &forceVector, 1.0f / (neighborDistance * neighborDistance));
                VECAdd(&effectWork->separationForces[effectIndex], &forceVector, &effectWork->separationForces[effectIndex]);
                VECSubtract(&effectWork->separationForces[neighborIndex], &forceVector, &effectWork->separationForces[neighborIndex]);
                if (effectWork->particleGroups[effectIndex] == effectWork->particleGroups[neighborIndex]) {
                    VECScale(&effectWork->particleDirections[neighborIndex], &forceVector, 1.0f / neighborDistance);
                    VECAdd(&effectWork->alignmentForces[effectIndex], &forceVector, &effectWork->alignmentForces[effectIndex]);
                    VECScale(&effectWork->particleDirections[effectIndex], &forceVector, 1.0f / neighborDistance);
                    VECAdd(&effectWork->alignmentForces[neighborIndex], &forceVector, &effectWork->alignmentForces[neighborIndex]);
                    VECAdd(&effectWork->neighborCenters[effectIndex], &effectWork->particlePositions[neighborIndex], &effectWork->neighborCenters[effectIndex]);
                    VECAdd(&effectWork->neighborCenters[neighborIndex], &effectWork->particlePositions[effectIndex], &effectWork->neighborCenters[neighborIndex]);
                }
                effectWork->neighborCounts[effectIndex]++;
                effectWork->neighborCounts[neighborIndex]++;
            }
        }
        for (neighborIndex = 0; neighborIndex < 4; neighborIndex++) {
            playerPosition.x = playerObjects[neighborIndex]->trans.x;
            playerPosition.y = playerObjects[neighborIndex]->trans.y;
            playerPosition.z = playerObjects[neighborIndex]->trans.z;
            VECSubtract(&effectWork->particlePositions[effectIndex], &playerPosition, &obstacleDifference);
            if (!(VECDotProduct(&obstacleDifference, &effectWork->particleDirections[effectIndex]) > 0)) {
                obstacleDistance = VECMag(&obstacleDifference) - 200;
                if (obstacleDistance < effectWork->neighborRadius) {
                    obstacleDistance -= 100;
                    if (obstacleDistance < 0.01f) {
                        obstacleDistance = 0.01f;
                    }
                    VECScale(&obstacleDifference, &obstacleDifference, 1.0f / obstacleDistance);
                    VECAdd(&effectWork->obstacleForces[effectIndex], &obstacleDifference, &effectWork->obstacleForces[effectIndex]);
                }
            }
        }
        if (effectWork->neighborCounts[effectIndex] != 0) {
            VECScale(&effectWork->neighborCenters[effectIndex], &effectWork->neighborCenters[effectIndex], 1.0f / effectWork->neighborCounts[effectIndex]);
            VECSubtract(&effectWork->neighborCenters[effectIndex], &effectWork->particlePositions[effectIndex], &originDifference);
            normalizationLength = VECMag(&originDifference);
            if (normalizationLength > 0.0f) {
                VECScale(&originDifference, &effectWork->neighborCenters[effectIndex], 1.0f / normalizationLength);
            }
            else {
                effectWork->neighborCenters[effectIndex].x = 0;
                effectWork->neighborCenters[effectIndex].y = 0;
                effectWork->neighborCenters[effectIndex].z = 0;
            }
            VECScale(&effectWork->alignmentForces[effectIndex], &effectWork->alignmentForces[effectIndex], 1.0f / effectWork->neighborCounts[effectIndex]);
            normalizationLength = VECMag(&effectWork->alignmentForces[effectIndex]);
            if (normalizationLength > 0) {
                VECScale(&effectWork->alignmentForces[effectIndex], &effectWork->alignmentForces[effectIndex], 1.0f / normalizationLength);
                VECSubtract(&effectWork->alignmentForces[effectIndex], &effectWork->particleDirections[effectIndex], &originDifference);
                VECScale(&originDifference, &effectWork->alignmentForces[effectIndex], 1.0f / normalizationLength);
            }
        }
        VECSubtract(&effectWork->spawnOrigin, &effectWork->particlePositions[effectIndex], &effectWork->originForces[effectIndex]);
        VECNormalize(&effectWork->originForces[effectIndex], &effectWork->originForces[effectIndex]);
    }
    for (effectIndex = 0; effectIndex < effectWork->particleCount; effectIndex++) {
        combinedForce.x = 0;
        combinedForce.y = 0;
        combinedForce.z = 0;
        VECScale(&effectWork->separationForces[effectIndex], &directionVector, effectWork->separationWeight);
        VECAdd(&directionVector, &combinedForce, &combinedForce);
        VECScale(&effectWork->obstacleForces[effectIndex], &directionVector, effectWork->obstacleWeight);
        VECAdd(&directionVector, &combinedForce, &combinedForce);
        VECScale(&effectWork->alignmentForces[effectIndex], &directionVector, effectWork->alignmentWeight);
        VECAdd(&directionVector, &combinedForce, &combinedForce);
        VECScale(&effectWork->neighborCenters[effectIndex], &directionVector, effectWork->cohesionWeight);
        VECAdd(&directionVector, &combinedForce, &combinedForce);
        VECScale(&effectWork->originForces[effectIndex], &directionVector, effectWork->originWeight);
        VECAdd(&directionVector, &combinedForce, &combinedForce);
        combinedForceMagnitude = VECMag(&combinedForce);
        if (combinedForceMagnitude > 1.0f) {
            VECScale(&combinedForce, &combinedForce, 1.0f / combinedForceMagnitude);
        }
        if (combinedForce.y > 0.01f) {
            effectWork->particlePitchAngles[effectIndex] += 0.02f;
            if (effectWork->particlePitchAngles[effectIndex] > 0.8f) {
                effectWork->particlePitchAngles[effectIndex] = 0.8f;
            }
        }
        else {
            if (combinedForce.y < -0.01f) {
                effectWork->particlePitchAngles[effectIndex] -= 0.02f;
                if (effectWork->particlePitchAngles[effectIndex] < -0.8f) {
                    effectWork->particlePitchAngles[effectIndex] = -0.8f;
                }
            }
            else {
                effectWork->particlePitchAngles[effectIndex] *= 0.98f;
            }
        }
        effectWork->particleSpeeds[effectIndex] -= 0.002 * effectWork->particlePitchAngles[effectIndex];
        effectWork->particleSpeeds[effectIndex] = effectWork->baseSpeed + (0.99f * (effectWork->particleSpeeds[effectIndex] - effectWork->baseSpeed));
        if (effectWork->particleSpeeds[effectIndex] < 0.4f * effectWork->baseSpeed) {
            effectWork->particleSpeeds[effectIndex] = 0.4f * effectWork->baseSpeed;
        }
        if (effectWork->particleSpeeds[effectIndex] > 5.0f * effectWork->baseSpeed) {
            effectWork->particleSpeeds[effectIndex] = 5.0f * effectWork->baseSpeed;
        }
        horizontalForce = combinedForce;
        horizontalForce.y = 0;
        directionVector = effectWork->particleDirections[effectIndex];
        if (VECMag(&horizontalForce) > 0) {
            VECNormalize(&horizontalForce, &horizontalForce);
        }
        alignmentDotProduct = VECDotProduct(&horizontalForce, &directionVector);
        if (alignmentDotProduct > 0.7f) {
            alignmentDotProduct -= 0.7f;
            effectWork->particleSpeeds[effectIndex] += 0.005f * alignmentDotProduct;
        }
        VECCrossProduct(&horizontalForce, &directionVector, &horizontalForce);
        alignmentDotProduct = 0.07f * ((1.0f - alignmentDotProduct) / 2);
        if (horizontalForce.y > 0.05f) {
            effectWork->particleRollVelocities[effectIndex] = 0.05f * (alignmentDotProduct + (19.0f * effectWork->particleRollVelocities[effectIndex]));
        }
        else if (horizontalForce.y < -0.05f) {
            effectWork->particleRollVelocities[effectIndex] = 0.05f * ((19.0f * effectWork->particleRollVelocities[effectIndex]) - alignmentDotProduct);
        }
        else {
            effectWork->particleRollVelocities[effectIndex] *= 0.98f;
        }
        effectWork->particleYawAngles[effectIndex] += effectWork->particleRollVelocities[effectIndex];
        effectWork->particleRollAngles[effectIndex] = 20.0f * -effectWork->particleRollVelocities[effectIndex];
        MTXTrans(translationMatrix, effectWork->particlePositions[effectIndex].x, effectWork->particlePositions[effectIndex].y, effectWork->particlePositions[effectIndex].z);
        MTXRotDeg(pitchMatrix, 'x', (effectWork->particlePitchAngles[effectIndex] / M_PI) * 180.0);
        MTXRotDeg(yawMatrix, 'y', (effectWork->particleYawAngles[effectIndex] / M_PI) * 180.0);
        MTXRotDeg(rollMatrix, 'z', (effectWork->particleRollAngles[effectIndex] / M_PI) * 180.0);
        MTXConcat(pitchMatrix, yawMatrix, combinedRotationMatrix);
        MTXConcat(rollMatrix, combinedRotationMatrix, particleMatrix);
        MTXConcat(particleMatrix, translationMatrix, combinedRotationMatrix);
        effectWork->particleDirections[effectIndex].x = MTXRowCol(combinedRotationMatrix, 2, 0);
        effectWork->particleDirections[effectIndex].y = MTXRowCol(combinedRotationMatrix, 2, 1);
        effectWork->particleDirections[effectIndex].z = MTXRowCol(combinedRotationMatrix, 2, 2);
        effectWork->particlePositions[effectIndex].x += 100.0f * (effectWork->particleDirections[effectIndex].x * effectWork->particleSpeeds[effectIndex]);
        effectWork->particlePositions[effectIndex].y += 100.0f * (effectWork->particleDirections[effectIndex].y * effectWork->particleSpeeds[effectIndex]);
        effectWork->particlePositions[effectIndex].z += 100.0f * (effectWork->particleDirections[effectIndex].z * effectWork->particleSpeeds[effectIndex]);
        if (effectWork->particlePositions[effectIndex].y < -350.0f) {
            effectWork->particlePositions[effectIndex].y = -350.0f;
        }
        Hu3DModelPosSet(object->mdlId[effectIndex], effectWork->particlePositions[effectIndex].x, effectWork->particlePositions[effectIndex].y, effectWork->particlePositions[effectIndex].z);
        Hu3DModelRotSet(object->mdlId[effectIndex], (-effectWork->particlePitchAngles[effectIndex] / M_PI) * 180.0, (-effectWork->particleYawAngles[effectIndex] / M_PI) * 180.0, 0);
    }
}

void CleanupPlayerEffects()
{
    HU3DCAMERA *camera;
    s32 cameraComponentIndex;
    float cameraValues[7];
    camera = cameraControllerObject->data;
    cameraValues[0] = camera->pos.x;
    cameraValues[1] = camera->pos.y;
    cameraValues[2] = camera->pos.z;
    cameraValues[3] = camera->up.x;
    cameraValues[4] = camera->up.y;
    cameraValues[5] = camera->up.z;
    cameraValues[6] = camera->target.x;
    fontcolor = FONT_COLOR_WHITE;
    for (cameraComponentIndex = 0; cameraComponentIndex < 7; cameraComponentIndex++) {
        if (cameraComponentIndex == cameraTransitionIndex) {
            print8(24.0 + (1.5 * ((cameraComponentIndex * 8) * 7)), 384, 1.5f, "____");
        }
        print8(24.0 + (1.5 * ((cameraComponentIndex * 8) * 7)), 400, 1.5f, "%.2f", cameraValues[cameraComponentIndex]);
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_LEFT) {
        if (--cameraTransitionIndex < 0) {
            cameraTransitionIndex = 6;
        }
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_RIGHT) {
        if (++cameraTransitionIndex > 6) {
            cameraTransitionIndex = 0;
        }
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_UP) {
        if (HuPadBtn[0] & PAD_TRIGGER_R) {
            cameraValues[cameraTransitionIndex] += 1.0f;
        }
        else if (HuPadBtn[0] & PAD_TRIGGER_L) {
            cameraValues[cameraTransitionIndex] += 0.1f;
        }
        else {
            cameraValues[cameraTransitionIndex] += 0.01f;
        }
        if (cameraValues[cameraTransitionIndex] > 999.99f) {
            cameraValues[cameraTransitionIndex] = 999.99f;
        }
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_DOWN) {
        if (HuPadBtn[0] & PAD_TRIGGER_R) {
            cameraValues[cameraTransitionIndex] -= 1.0f;
        }
        else if (HuPadBtn[0] & PAD_TRIGGER_L) {
            cameraValues[cameraTransitionIndex] -= 0.1f;
        }
        else {
            cameraValues[cameraTransitionIndex] -= 0.01f;
        }
        if (cameraValues[cameraTransitionIndex] < 0) {
            cameraValues[cameraTransitionIndex] = 0;
        }
    }
    camera->pos.x = cameraValues[0];
    camera->pos.y = cameraValues[1];
    camera->pos.z = cameraValues[2];
    camera->up.x = cameraValues[3];
    camera->up.y = cameraValues[4];
    camera->up.z = cameraValues[5];
    camera->target.x = cameraValues[6];
}

void UpdateFlockingParticleEffect(OMOBJ *object);

OMOBJ *CreateFlockingParticleEffect(s16 particleCount, Vec *spawnOrigin, Vec *spawnRadius, Vec *effectOrigin)
{
    OMOBJ *effectIndex;
    OMOBJ *priority;
    priority = omAddObjEx(HuPrcCurrentGet(), 1140, 0, 0, -1, UpdateFlockingParticleEffect);
    effectIndex = CreateFlockingParticleWork(particleCount);
    priority->work[0] = (u32)effectIndex;
    InitializeFlockingParticles(effectIndex, spawnOrigin, spawnRadius);
    SetFlockingParticleOrigin(effectIndex, effectOrigin);
    SetFlockingParticleMotion(effectIndex, 90.0f, 0.045999996f);
    SetFlockingParticleWeights(effectIndex, 5.0f, 1.5f, 0.08f, 0.8f, 0.8f);
    SetFlockingParticlesVisible(effectIndex, 1);
    return priority;
}

void UpdateFlockingParticleEffect(OMOBJ *object)
{
    FlockingParticleEffectWork *modelIndex;
    OMOBJ *modelData;
    s32 motionIndex;
    s32 motionCount;
    motionCount = 0;
    modelData = (OMOBJ *)(object->work[0]);
    modelIndex = modelData->data;
    modelIndex->spawnOrigin.x += object->scale.x * sind(object->trans.x);
    modelIndex->spawnOrigin.y += object->scale.y * sind(object->trans.x);
    modelIndex->spawnOrigin.z += object->scale.z * sind(object->trans.x);
    object->trans.x += object->rot.x;
    if (object->trans.x >= 360.0f) {
        object->trans.x -= 360.0f;
    }
    if (object->trans.x < 0.0f) {
        object->trans.x += 360.0f;
    }
    for (motionIndex = 0; motionIndex < modelIndex->particleCount; motionIndex++) {
        if (modelIndex->particlePositions[motionIndex].z >= cameraPosition.z) {
            motionCount++;
        }
    }
    if (motionCount == modelIndex->particleCount) {
        DestroyFlockingParticleEffect(modelData);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}
