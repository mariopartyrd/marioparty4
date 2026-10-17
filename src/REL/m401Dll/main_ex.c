#include "game/audio.h"
#include "game/frand.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"

#include "ext_math.h"

#include "REL/m401Dll.h"

#ifndef __MWERKS__
extern s32 rand8(void);
#endif

struct ScoreParticlePoolEntry {
    s16 isAllocated;
    s16 particleModelIds[3];
};

ANIMDATA *scoreParticleAnimationA;
ANIMDATA *scoreParticleAnimationB;
ANIMDATA *scoreParticleAnimationC;
ANIMDATA *scoreParticleBonusAnimation;
ANIMDATA *scoreParticleAnimationD;
ANIMDATA *scoreParticleAnimationE;
ANIMDATA *scoreParticleAnimationF;
ANIMDATA *scoreParticleAnimationTable[2][3];
struct ScoreParticlePoolEntry scoreParticlePool[28];
s16 scoreParticleModelIds[4];
s16 nextScoreParticlePoolSlot;
float unusedParticleParameter;
float cameraFieldOfView;
float cameraNearPlane;
float cameraFarPlane;
s16 cameraAspectRatio;

void ProjectWorldPositionToScreen(Vec *worldPosition, Vec *screenPosition)
{
    HU3DCAMERA *camera;
    Mtx lookat;
    Mtx44 proj;
    float coord[4];
    worldPosition->y = -worldPosition->y;
    camera = &Hu3DCamera[0];
    MTXLookAt(lookat, &camera->pos, &camera->up, &camera->target);
    MTXMultVec(lookat, worldPosition, worldPosition);
    MTXPerspective(proj, camera->fov, camera->aspect, camera->near, camera->far);
    coord[0] = (worldPosition->x * proj[0][0]) + (worldPosition->y * proj[0][1]) + (worldPosition->z * proj[0][2]) + proj[0][3];
    coord[1] = (worldPosition->x * proj[1][0]) + (worldPosition->y * proj[1][1]) + (worldPosition->z * proj[1][2]) + proj[1][3];
    coord[2] = (worldPosition->x * proj[2][0]) + (worldPosition->y * proj[2][1]) + (worldPosition->z * proj[2][2]) + proj[2][3];
    coord[3] = (worldPosition->x * proj[3][0]) + (worldPosition->y * proj[3][1]) + (worldPosition->z * proj[3][2]) + proj[3][3];
    screenPosition->x = ((coord[0] / coord[3]) * 320.0f) + 320.0f;
    screenPosition->y = ((coord[1] / coord[3]) * 240.0f) + 240.0f;
    screenPosition->z = coord[2] / coord[3];
}

void LoadScoreParticleResources(void)
{
    s32 i;
    scoreParticleAnimationA = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x11));
    scoreParticleAnimationB = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x12));
    scoreParticleAnimationC = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x13));
    scoreParticleAnimationD = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x14));
    scoreParticleAnimationE = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x15));
    scoreParticleAnimationF = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x16));
    HuSprAnimLock(scoreParticleAnimationA);
    HuSprAnimLock(scoreParticleAnimationB);
    HuSprAnimLock(scoreParticleAnimationC);
    HuSprAnimLock(scoreParticleAnimationD);
    HuSprAnimLock(scoreParticleAnimationE);
    HuSprAnimLock(scoreParticleAnimationF);
    scoreParticleBonusAnimation = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M401, 0x26));
    HuSprAnimLock(scoreParticleBonusAnimation);
    scoreParticleAnimationTable[0][0] = scoreParticleAnimationA;
    scoreParticleAnimationTable[0][1] = scoreParticleAnimationB;
    scoreParticleAnimationTable[0][2] = scoreParticleAnimationC;
    scoreParticleAnimationTable[1][0] = scoreParticleAnimationD;
    scoreParticleAnimationTable[1][1] = scoreParticleAnimationE;
    scoreParticleAnimationTable[1][2] = scoreParticleAnimationF;
    for (i = 0; i < 4; i++) {
        scoreParticleModelIds[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x17));
        Hu3DModelAttrSet(scoreParticleModelIds[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(scoreParticleModelIds[i], HU3D_MOTATTR_LOOP);
        Hu3DModelScaleSet(scoreParticleModelIds[i], 1.5f, 1.5f, 1.0f);
        Hu3DModelLayerSet(scoreParticleModelIds[i], 2);
    }
}

void FreeScoreParticleResources(void)
{
    HuSprAnimKill(scoreParticleAnimationA);
    HuSprAnimKill(scoreParticleAnimationB);
    HuSprAnimKill(scoreParticleAnimationC);
    HuSprAnimKill(scoreParticleAnimationD);
    HuSprAnimKill(scoreParticleAnimationE);
    HuSprAnimKill(scoreParticleAnimationF);
    HuSprAnimKill(scoreParticleBonusAnimation);
}

void CreateScoreParticleModelPool(void)
{
    s32 i;
    for (i = 0; i < 28; i++) {
        scoreParticlePool[i].isAllocated = 0;
        scoreParticlePool[i].particleModelIds[0] = Hu3DParticleCreate(scoreParticleAnimationA, 80);
        scoreParticlePool[i].particleModelIds[1] = Hu3DParticleCreate(scoreParticleAnimationB, 80);
        scoreParticlePool[i].particleModelIds[2] = Hu3DParticleCreate(scoreParticleAnimationC, 80);
        Hu3DModelAttrSet(scoreParticlePool[i].particleModelIds[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(scoreParticlePool[i].particleModelIds[1], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(scoreParticlePool[i].particleModelIds[2], HU3D_ATTR_DISPOFF);
    }
    nextScoreParticlePoolSlot = 0;
}

s16 AcquireScoreParticlePoolSlot(void)
{
    s32 i;
    s32 j;
    for (i = 0; i < 28; i++) {
        if (!scoreParticlePool[i].isAllocated) {
            for (j = 0; j < 3; j++) {
                Hu3DModelAttrReset(scoreParticlePool[i].particleModelIds[j], HU3D_ATTR_DISPOFF);
            }
            scoreParticlePool[i].isAllocated = 1;
            return i;
        }
    }
    return -1;
}

void ReleaseScoreParticlePoolSlot(s16 poolSlotIndex)
{
    s32 i;
    scoreParticlePool[poolSlotIndex].isAllocated = 0;
    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(scoreParticlePool[poolSlotIndex].particleModelIds[i], HU3D_ATTR_DISPOFF);
    }
}

s16 AcquireScoreParticleModel(void)
{
    s16 particleModelId = scoreParticleModelIds[nextScoreParticlePoolSlot];
    nextScoreParticlePoolSlot = (nextScoreParticlePoolSlot + 1) & 0x3;
    Hu3DModelTPLvlSet(particleModelId, 1.0f);
    return particleModelId;
}

void UpdateScoreParticleEffect(OMOBJ *object);
void UpdateScoreParticleLayerOne(OMOBJ *object);
void UpdateScoreParticleLayerTwo(OMOBJ *object);
void UpdateScoreParticleLayerThree(OMOBJ *object);
void UpdateScoreParticleLayerFour(OMOBJ *object);
void UpdateScoreParticleLayerFive(OMOBJ *object);
void UpdateScoreParticleLayerSix(OMOBJ *object);

void UpdateScoreParticleModel(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void UpdateScoreParticleModelVisibility(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void UpdateScoreParticleModelMotion(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void UpdateScoreParticleSparkle(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void UpdateScoreParticleTrail(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void UpdateScoreParticleBurst(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);
void UpdateScoreParticleFade(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);

OMOBJ *CreateScoreParticleEffect(Vec *spawnPosition, s16 particleVariant)
{
    OMOBJ *particleObject;
    s32 particleIndex;
    HU3DPARTICLE *particleData;
    ScoreParticleWork *particleWork;
    s16 particlePoolIndex = AcquireScoreParticlePoolSlot();
    if (particlePoolIndex < 0) {
        return NULL;
    }
    {
        s16 priority = -1;
        if (particleVariant == 0) {
            priority = 1;
        }
        particleObject = omAddObjEx(HuPrcCurrentGet(), 0x514, 3, 0, priority, NULL);
    }

    particleObject->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(ScoreParticleWork), HU_MEMNUM_OVL);
    particleWork = particleObject->data;
    particleWork->particlePosition = *spawnPosition;
    for (particleIndex = 0; particleIndex < 3; particleIndex++) {
        particleObject->mdlId[particleIndex] = scoreParticlePool[particlePoolIndex].particleModelIds[particleIndex];
        particleData = Hu3DData[particleObject->mdlId[particleIndex]].hookData;
        Hu3DParticleCntSet(particleObject->mdlId[particleIndex], 0);
        Hu3DParticleAnimModeSet(particleObject->mdlId[particleIndex], 0);
        Hu3DModelLayerSet(particleObject->mdlId[particleIndex], 1);
        if (particleVariant == 1) {
            particleObject->mode = AcquireScoreParticleModel();
            Hu3DModelAttrReset(particleObject->mode, HU3D_ATTR_DISPOFF);
            particleData->anim = scoreParticleAnimationTable[1][particleIndex];
            particleWork->opacity = 1.0f;
            particleObject->work[3] = 45;
            Hu3DModelTPLvlSet(particleObject->mode, particleWork->opacity);
        }
        else {
            particleData->anim = scoreParticleAnimationTable[0][particleIndex];
        }
    }
    particleWork->activeModelCallbacks = 3;
    particleWork->poolSlotIndex = particlePoolIndex;
    particleWork->particleVariant = particleVariant;
    switch (particleVariant) {
        case 1:
            Hu3DModelPosSet(particleObject->mode, spawnPosition->x, spawnPosition->y, cameraTarget.z + spawnPosition->z);

        case 0:
            particleObject->trans.x = spawnPosition->x;
            particleObject->trans.y = spawnPosition->y;
            particleObject->trans.z = cameraTarget.z + spawnPosition->z;
            for (particleIndex = 0; particleIndex < 3; particleIndex++) {
                Hu3DParticleHookSet(particleObject->mdlId[particleIndex], UpdateScoreParticleModel);
                Hu3DParticleColSet(particleObject->mdlId[particleIndex], 255, 255, 255);
                Hu3DModelPosSet(particleObject->mdlId[particleIndex], particleObject->trans.x, particleObject->trans.y, particleObject->trans.z);
                particleData = Hu3DData[particleObject->mdlId[particleIndex]].hookData;
                Hu3DParticleBlendModeSet(particleObject->mdlId[particleIndex], 0);
                particleData->dataCnt = (particleIndex * 4.5f) / 3.0f;
                particleData->emitCnt = 0;
                particleData->work = particleObject;
            }
            particleWork->fadeOutRequested = 0;
            particleObject->objFunc = UpdateScoreParticleEffect;
            break;

        case 2:
            SetObjectPosition(particleObject, spawnPosition->x, spawnPosition->y, spawnPosition->z);
            for (particleIndex = 0; particleIndex < 3; particleIndex++) {
                Hu3DParticleHookSet(particleObject->mdlId[particleIndex], UpdateScoreParticleModelVisibility);
                Hu3DParticleColSet(particleObject->mdlId[particleIndex], 255, 255, 255);
                Hu3DModelPosSet(particleObject->mdlId[particleIndex], particleObject->trans.x, particleObject->trans.y, particleObject->trans.z);
                Hu3DParticleBlendModeSet(particleObject->mdlId[particleIndex], 0);
                particleData = Hu3DData[particleObject->mdlId[particleIndex]].hookData;
                particleData->dataCnt = (particleIndex * 2) + (frand() & 0x7);
                particleData->work = particleObject;
            }
            particleObject->objFunc = UpdateScoreParticleLayerOne;
            break;

        case 3:
            for (particleIndex = 0; particleIndex < 3; particleIndex++) {
                Hu3DParticleHookSet(particleObject->mdlId[particleIndex], UpdateScoreParticleModelMotion);
                Hu3DParticleColSet(particleObject->mdlId[particleIndex], 255, 255, 255);
                Hu3DModelPosSet(particleObject->mdlId[particleIndex], spawnPosition->x, spawnPosition->y, spawnPosition->z);
                Hu3DParticleBlendModeSet(particleObject->mdlId[particleIndex], 0);
                particleData = Hu3DData[particleObject->mdlId[particleIndex]].hookData;
                particleData->dataCnt = (particleIndex * 2) + (frand() & 0x7);
                particleData->work = particleObject;
            }
            particleObject->objFunc = UpdateScoreParticleLayerTwo;
            break;

        case 4:
            SetObjectPosition(particleObject, spawnPosition->x, spawnPosition->y, spawnPosition->z);
            for (particleIndex = 0; particleIndex < 3; particleIndex++) {
                Hu3DParticleHookSet(particleObject->mdlId[particleIndex], UpdateScoreParticleSparkle);
                Hu3DParticleColSet(particleObject->mdlId[particleIndex], 255, 255, 255);
                Hu3DModelPosSet(particleObject->mdlId[particleIndex], particleObject->trans.x, particleObject->trans.y, particleObject->trans.z);
                Hu3DParticleBlendModeSet(particleObject->mdlId[particleIndex], 0);
                particleData = Hu3DData[particleObject->mdlId[particleIndex]].hookData;
                particleData->dataCnt = (particleIndex * 2) + (frand() & 0x7);
                particleData->work = particleObject;
            }
            particleObject->objFunc = UpdateScoreParticleLayerThree;
            break;

        case 5:
            SetObjectPosition(particleObject, spawnPosition->x, spawnPosition->y, spawnPosition->z);
            for (particleIndex = 0; particleIndex < 3; particleIndex++) {
                Hu3DParticleHookSet(particleObject->mdlId[particleIndex], UpdateScoreParticleTrail);
                Hu3DParticleColSet(particleObject->mdlId[particleIndex], 255, 255, 255);
                Hu3DModelPosSet(particleObject->mdlId[particleIndex], particleObject->trans.x, particleObject->trans.y, particleObject->trans.z);
                Hu3DParticleBlendModeSet(particleObject->mdlId[particleIndex], 1);
                particleData = Hu3DData[particleObject->mdlId[particleIndex]].hookData;
                particleData->dataCnt = (particleIndex * 2) + (frand() & 0x7);
                particleData->work = particleObject;
            }
            particleObject->objFunc = UpdateScoreParticleLayerFour;
            break;

        case 6:
            omSetTra(particleObject, spawnPosition->x, spawnPosition->y, spawnPosition->z);
            for (particleIndex = 0; particleIndex < 3; particleIndex++) {
                Hu3DParticleHookSet(particleObject->mdlId[particleIndex], UpdateScoreParticleBurst);
                Hu3DParticleColSet(particleObject->mdlId[particleIndex], 255, 255, 255);
                Hu3DModelPosSet(particleObject->mdlId[particleIndex], particleObject->trans.x, particleObject->trans.y, particleObject->trans.z);
                particleData = Hu3DData[particleObject->mdlId[particleIndex]].hookData;
                Hu3DParticleBlendModeSet(particleObject->mdlId[particleIndex], 1);
            }
            particleObject->objFunc = UpdateScoreParticleLayerFive;
            break;

        case 7:
            omSetTra(particleObject, spawnPosition->x, spawnPosition->y, spawnPosition->z);
            for (particleIndex = 0; particleIndex < 3; particleIndex++) {
                Hu3DParticleHookSet(particleObject->mdlId[particleIndex], UpdateScoreParticleFade);
                Hu3DParticleColSet(particleObject->mdlId[particleIndex], 255, 255, 255);
                Hu3DModelPosSet(particleObject->mdlId[particleIndex], particleObject->trans.x, particleObject->trans.y, particleObject->trans.z);
                particleData = Hu3DData[particleObject->mdlId[particleIndex]].hookData;
                Hu3DParticleBlendModeSet(particleObject->mdlId[particleIndex], 1);
            }
            particleObject->objFunc = UpdateScoreParticleLayerSix;
            break;

        default:
            break;
    }
    return particleObject;
}

void FadeScoreParticleEffect(OMOBJ *object);
void UpdateScoreParticleBonusModel(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);

void UpdateScoreParticleEffect(OMOBJ *object)
{
    ScoreParticleWork *particleWork;
    s32 particleIndex;
    M401WorkPlayer *playerWork;
    OMOBJ *playerObject;
    HU3DPARTICLE *particleData;
    s16 playerId;
    particleWork = object->data;
    particleWork->particlePosition.z += (cameraMoveDistance * 0.5f);
    object->trans.x = particleWork->particlePosition.x;
    object->trans.y = particleWork->particlePosition.y;
    object->trans.z = cameraTarget.z + particleWork->particlePosition.z;
    if (object->mode != 0) {
        Hu3DModelPosSet(object->mode, object->trans.x, object->trans.y, object->trans.z);
    }
    for (particleIndex = 1; particleIndex < 3; particleIndex++) {
        Hu3DModelRotSet(object->mdlId[particleIndex], object->rot.x, object->rot.y, object->rot.z);
        Hu3DModelPosSet(object->mdlId[particleIndex], object->trans.x, object->trans.y, object->trans.z);
    }
    for (particleIndex = 0; particleIndex < 4; particleIndex++) {
        float dist;
        playerObject = playerObjects[particleIndex];
        playerWork = playerObject->data;
        if (playerWork->isStunned != 0) {
            continue;
        }
        dist = VECDistanceXYZ(&object->trans, &playerObject->trans);
        if (dist < 108.00001f) {
            Hu3DMotionShiftSet(playerObjects[particleIndex]->mdlId[0], playerObjects[particleIndex]->mtnId[6], 0, 10, HU3D_MOTATTR_NONE);
            HuAudFXPlay(1288);
            if (particleWork->particleVariant == 0) {
                HuAudFXPlay(9);
                playerWork->score++;
                omVibrate(playerWork->playerIndex, 12, 6, 6);
            }
            else {
                HuAudFXPlay(1292);
                playerWork->scorePopupValue = 3;
                playerWork->score += 3;
                ShowScoreGainPopup(playerWork->playerIndex);
                omVibrate(playerWork->playerIndex, 12, 4, 2);
            }
            playerWork->collisionCooldown = 50;
            for (particleIndex = 0; particleIndex < 3; particleIndex++) {
                particleData = Hu3DData[object->mdlId[particleIndex]].hookData;
                particleData->emitCnt = 0;
                Hu3DParticleHookSet(object->mdlId[particleIndex], UpdateScoreParticleBonusModel);
            }
            object->objFunc = FadeScoreParticleEffect;
            break;
        }
    }
    if (particleWork->particlePosition.z > 850.0f) {
        particleWork->fadeOutRequested = 1;
    }
    if (object->mode) {
        if (object->work[3] != 0) {
            object->work[3]--;
        }
        else {
            particleWork->opacity -= 0.033333335f;
            if (particleWork->opacity < 0) {
                particleWork->opacity = 0;
            }
            Hu3DModelTPLvlSet(object->mode, particleWork->opacity);
        }
    }
    if (particleWork->activeModelCallbacks == 0) {
        if (object->mode) {
            Hu3DModelAttrSet(object->mode, HU3D_ATTR_DISPOFF);
        }
        ReleaseScoreParticlePoolSlot(particleWork->poolSlotIndex);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void FadeScoreParticleEffect(OMOBJ *object)
{
    ScoreParticleWork *particleWork;
    s32 particleIndex;

    particleWork = object->data;
    particleWork->particlePosition.z += (cameraMoveDistance * 0.5f);
    object->trans.x = particleWork->particlePosition.x;
    object->trans.y = particleWork->particlePosition.y;
    object->trans.z = cameraTarget.z + particleWork->particlePosition.z;
    for (particleIndex = 1; particleIndex < 3; particleIndex++) {
        Hu3DModelPosSet(object->mdlId[particleIndex], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->mode != 0) {
        Hu3DModelPosSet(object->mode, object->trans.x, object->trans.y, object->trans.z);
        particleWork->opacity -= 0.033333335f;
        if (particleWork->opacity < 0) {
            particleWork->opacity = 0;
        }
        Hu3DModelTPLvlSet(object->mode, particleWork->opacity);
    }

    if (particleWork->activeModelCallbacks == 0) {
        if (object->mode) {
            Hu3DModelAttrSet(object->mode, HU3D_ATTR_DISPOFF);
        }
        ReleaseScoreParticlePoolSlot(particleWork->poolSlotIndex);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void UpdateScoreParticleLayerOne(OMOBJ *object)
{
    s32 modelIndex;
    ScoreParticleWork *particleWork;
    ScoreParticleWork *parentParticleWork;
    particleWork = object->data;
    parentParticleWork = particleWork->ownerObject->data;
    omSetTra(object, 0, 0, 0);
    for (modelIndex = 1; modelIndex < 3; modelIndex++) {
        Hu3DModelPosSet(object->mdlId[modelIndex], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->work[0] == 1) {
        ReleaseScoreParticlePoolSlot(particleWork->poolSlotIndex);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void UpdateScoreParticleLayerTwo(OMOBJ *object)
{
    ScoreParticleWork *particleIndex;
    particleIndex = object->data;
    if (object->work[0] == 1) {
        ReleaseScoreParticlePoolSlot(particleIndex->poolSlotIndex);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void UpdateScoreParticleLayerThree(OMOBJ *object)
{
    s32 modelIndex;
    ScoreParticleWork *particleWork;
    ScoreParticleWork *parentParticleWork;
    particleWork = object->data;
    parentParticleWork = particleWork->ownerObject->data;
    omSetTra(object, 0, 0, 0);
    for (modelIndex = 1; modelIndex < 3; modelIndex++) {
        Hu3DModelPosSet(object->mdlId[modelIndex], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->work[1] == 1) {
        ReleaseScoreParticlePoolSlot(particleWork->poolSlotIndex);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void UpdateScoreParticleLayerFour(OMOBJ *object)
{
    s32 modelIndex;
    ScoreParticleWork *particleWork;
    ScoreParticleWork *parentParticleWork;
    particleWork = object->data;
    parentParticleWork = particleWork->ownerObject->data;
    omSetTra(object, particleWork->ownerObject->trans.x, particleWork->ownerObject->trans.y, particleWork->ownerObject->trans.z);
    for (modelIndex = 1; modelIndex < 3; modelIndex++) {
        Hu3DModelPosSet(object->mdlId[modelIndex], object->trans.x, object->trans.y, object->trans.z);
    }
    if (object->work[1] == 1) {
        ReleaseScoreParticlePoolSlot(particleWork->poolSlotIndex);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void UpdateScoreParticleLayerFive(OMOBJ *object)
{
    ScoreParticleWork *particleIndex;
    particleIndex = object->data;
    if (object->work[0] == 1) {
        ReleaseScoreParticlePoolSlot(particleIndex->poolSlotIndex);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void UpdateScoreParticleLayerSix(OMOBJ *object)
{
    ScoreParticleWork *particleIndex;
    particleIndex = object->data;
    if (object->work[0] == 1) {
        ReleaseScoreParticlePoolSlot(particleIndex->poolSlotIndex);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void UpdateScoreParticleModel(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float particleAlpha;
    float particleHeight;
    float particleAngleStep;
    HU3DPARTICLEDATA *particleData;
    s32 particleIndex;
    ScoreParticleWork *activeParticleCount;
    s32 particleWork;
    activeParticleCount = ((OMOBJ *)(particle->work))->data;
    if (particle->count == 0) {
        particleData = particle->data;
        particleAngleStep = 360.0f / (particle->maxCnt / 2);
        particleAlpha = particle->dataCnt;
        for (particleIndex = 0; particleIndex < particle->maxCnt / 2; particleIndex++, particleData++) {
            particleHeight = (0.1f * (rand8() % 50)) + 50;
            particleData->scale = (0.1f * (rand8() % 41)) + 8.0f;
            particleData->vel.x = particleAlpha;
            particleData->vel.y = particleHeight;
            particleData->vel.z = 0;
            particleData->accel.x = (10.0f / 255.0f) * ((u8)frand());
            particleData->color.a = 180;
            particleAlpha += particleAngleStep;
            particleData->pos.z = 0;
        }
        for (particleIndex = 0; particleIndex < particle->maxCnt / 2; particleIndex++, particleData++) {
            particleData->scale = 0;
            particleData->color.a = 0;
        }
    }
    particleData = particle->data;
    particleWork = 0;
    for (particleIndex = 0; particleIndex < particle->maxCnt / 2; particleIndex++, particleData++) {
        if (particleData->color.a != 0) {
            particleWork++;
            particleHeight = (6.0 * sind(particleData->vel.z)) + particleData->vel.y;
            particleData->pos.x = particleHeight * cosd(particleData->vel.x);
            particleData->pos.y = particleHeight * sind(particleData->vel.x);
            particleData->vel.z += particleData->accel.x;
            if (particleData->vel.z >= 360.0f) {
                particleData->vel.z -= 360.0f;
            }
            particleAlpha = particleData->color.a;
            if (activeParticleCount->fadeOutRequested) {
                particleAlpha -= 3.0f;
                if (particleAlpha < 0.0f) {
                    particleAlpha = 0.0f;
                }
            }
            particleData->color.a = particleAlpha;
        }
    }
    if (!particleWork) {
        activeParticleCount->activeModelCallbacks--;
    }
}

void UpdateScoreParticleBonusModel(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float particleAlpha;
    HU3DPARTICLEDATA *particleData;
    s32 particleIndex;
    s32 activeParticleCount;
    ScoreParticleWork *particleWork;
    if (!particle->emitCnt) {
        particle->emitCnt = 1;
        particleData = particle->data;
        for (particleIndex = 0; particleIndex < particle->maxCnt / 2; particleIndex++, particleData++) {
            particleData->vel.x = particleData->pos.x;
            particleData->accel.x = 0;
            particleData->accel.y = 5.0f + ((35.0f / 255.0f) * ((u8)frand()));
            particleData->accel.z = 8.0f + ((8.0f / 255.0f) * ((u8)frand()));
            particleData->colorIdx = 3.0f + ((5.0f / 255.0f) * ((u8)frand()));
        }
    }
    particleData = particle->data;
    activeParticleCount = 0;
    for (particleIndex = 0; particleIndex < particle->maxCnt / 2; particleIndex++, particleData++) {
        if (particleData->color.a != 0) {
            activeParticleCount++;
            particleData->pos.x = particleData->vel.x + (particleData->accel.z * sind(particleData->accel.x));
            particleData->accel.x += particleData->accel.y;
            if (particleData->accel.x >= 360.0f) {
                particleData->accel.x -= 360.0f;
            }
            particleData->pos.y += particleData->colorIdx;
            particleAlpha = particleData->color.a;
            particleAlpha -= 3.0f;
            if (particleAlpha < 0.0f) {
                particleAlpha = 0.0f;
            }
            particleData->color.a = particleAlpha;
        }
    }
    if (activeParticleCount == 0) {
        ScoreParticleWork *particleWork = ((OMOBJ *)(particle->work))->data;
        particleWork->activeModelCallbacks--;
    }
}

// Here exclusively to match update_score_particle_model_visibility
static inline void PreserveParticleCallbackMatch(s32 value)
{
    s32 temp1, temp2, temp3, temp4, temp5;
    if (value != 0) {
        temp1 = 1;
        temp2 = temp1 * 2;
        temp3 = temp2 * 3;
        temp4 = temp3 * 4;
        temp5 = temp4 * 5;
        temp5 = temp5 / 2;
    }
}

void UpdateScoreParticleModelVisibility(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    PreserveParticleCallbackMatch(0);
}

void UpdateScoreParticleModelMotion(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    HU3DPARTICLEDATA *particleData;
    s32 particleIndex;
    s32 freeParticleIndex;
    if (particle->count == 0) {
        particleData = particle->data;
        for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
            particleData->color.a = 0;
            particleData->scale = 0;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0) {
        for (particleIndex = 0; particleIndex < 2; particleIndex++) {
            particleData = particle->data;
            for (freeParticleIndex = 0; freeParticleIndex < particle->maxCnt; freeParticleIndex++, particleData++) {
                if (particleData->color.a == 0) {
                    break;
                }
            }
            if (freeParticleIndex == particle->maxCnt) {
                continue;
            }
            particleData->vel.x = -50.0f + (0.3921569f * ((u8)frand()));
            particleData->vel.y = 0.058823533f * ((u8)frand());
            particleData->accel.x = (90.0f / 255.0f) * ((u8)frand());
            particleData->accel.y = 5.0f + (0.098039225f * ((u8)frand()));
            particleData->accel.z = (float)(frand() % 10) + 8.0f;
            particleData->pos.z = -5.0f + ((11.0f / 255.0f) * ((u8)frand()));
            particleData->pos.y = (float)(frand() % 31) + -5.0f;
            particleData->scale = particleData->vel.y + 35.0f;
            particleData->color.a = 210;
            particleData->vel.y = (0.2 * particleData->vel.y) + 5.0;
            particle->dataCnt = (frand() % 10) + 10;
        }
    }
    else {
        particle->dataCnt--;
    }
    particleData = particle->data;
    for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
        if (particleData->color.a == 0) {
            continue;
        }
        particleData->pos.x = (particleData->accel.z * sind(particleData->accel.x)) + particleData->vel.x;
        particleData->accel.x += particleData->accel.y;
        if (particleData->accel.x >= 360.0f) {
            particleData->accel.x -= 360.0f;
        }
        particleData->pos.y += particleData->vel.y;
        particleData->color.a--;
    }
}

void UpdateScoreParticleSparkle(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    HU3DPARTICLEDATA *particleData;
    s32 particleIndex;
    M401WorkPlayer *playerWork;
    OMOBJ *particleObject;
    s32 freeParticleIndex;
    s32 activeParticleCount;
    ScoreParticleWork *particleWork;
    particleObject = particle->work;
    particleWork = ((OMOBJ *)(particle->work))->data;
    playerWork = particleWork->ownerObject->data;
    if (particle->count == 0) {
        particleData = particle->data;
        for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
            particleData->color.a = 0;
            particleData->scale = 0;
            particleData->speedDecay = 0;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0 && particleObject->work[0] == 0) {
        for (particleIndex = 0; particleIndex < 10; particleIndex++) {
            particleData = particle->data;
            for (freeParticleIndex = 0; freeParticleIndex < particle->maxCnt; freeParticleIndex++, particleData++) {
                if (particleData->speedDecay == 0) {
                    break;
                }
            }
            if (freeParticleIndex == particle->maxCnt) {
                continue;
            }
            particleData->vel.x = (((40.0f / 255.0f) * ((u8)frand())) + (playerWork->effectAnchorPosition.x - 20.0f));
            particleData->vel.y = (frand() % 5) + 3;
            particleData->accel.x = ((90.0f / 255.0f) * ((u8)frand()));
            particleData->accel.y = 5.0f + ((45.0f / 255.0f) * ((u8)frand()));
            particleData->accel.z = 2.0f + (0.011764707f * ((u8)frand()));
            particleData->color.a = 180;
            particleData->pos.z = ((0.121568635f * ((u8)frand())) + (playerWork->effectAnchorPosition.z + 70.0f));
            particleData->pos.y = ((0.20000002f * ((u8)frand())) + (playerWork->effectAnchorPosition.y - 25.0f));
            particle->dataCnt = (frand() % 6) + 5;
            particleData->speedDecay = 1;
            particleData->scale = 11;
        }
    }
    else {
        particle->dataCnt--;
    }
    particleData = particle->data;
    activeParticleCount = 0;
    for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
        if (particleData->color.a != 0) {
            float remainingAlpha;
            particleData->pos.x = (particleData->accel.z * sind(particleData->accel.x)) + particleData->vel.x;
            particleData->accel.x += particleData->accel.y;
            if (particleData->accel.x >= 360.0f) {
                particleData->accel.x -= 360.0f;
            }
            particleData->pos.y += 3.0f;
            remainingAlpha = particleData->color.a;
            remainingAlpha -= particleData->vel.y;
            if (remainingAlpha < 0.0f) {
                remainingAlpha = 0.0f;
                particleData->speedDecay = 0;
            }

            particleData->color.a = remainingAlpha;
            activeParticleCount++;
        }
    }
    if (activeParticleCount == 0 && particleObject->work[0] == 1) {
        particleObject->work[1] = 1;
    }
}

void UpdateScoreParticleTrail(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    HU3DPARTICLEDATA *particleData;
    s32 particleIndex;
    M401WorkPlayer *playerWork;
    OMOBJ *particleObject;
    s32 freeParticleIndex;
    s32 activeParticleCount;
    ScoreParticleWork *particleWork;
    particleObject = particle->work;
    particleWork = (particleObject)->data;
    playerWork = particleWork->ownerObject->data;
    if (particle->count == 0) {
        particleData = particle->data;
        for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
            particleData->color.a = 0;
            particleData->scale = 0;
            particleData->speedDecay = 0;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0 && particleObject->work[0] == 0) {
        for (particleIndex = 0; particleIndex < 10; particleIndex++) {
            particleData = particle->data;
            for (freeParticleIndex = 0; freeParticleIndex < particle->maxCnt; freeParticleIndex++, particleData++) {
                if (particleData->speedDecay == 0) {
                    break;
                }
            }
            if (freeParticleIndex == particle->maxCnt) {
                continue;
            }
            particleData->vel.x = (((80.0f / 255.0f) * ((u8)frand())) + (-40.0f));
            particleData->vel.y = (frand() % 10) + 7;
            particleData->accel.x = ((90.0f / 255.0f) * ((u8)frand()));
            particleData->accel.y = 5.0f + ((45.0f / 255.0f) * ((u8)frand()));
            particleData->accel.z = 2.0f + (frand() % 3);
            particleData->color.a = 180;
            particleData->pos.z = ((0.121568635f * ((u8)frand())) + (85.0f));
            particleData->pos.y = ((0.2392157f * ((u8)frand())) + (-30.0f));
            particle->dataCnt = (frand() % 3) + 3;
            particleData->speedDecay = 1;
            particleData->scale = 11;
        }
    }
    else {
        particle->dataCnt--;
    }
    particleData = particle->data;
    activeParticleCount = 0;
    for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
        if (particleData->color.a != 0) {
            float remainingAlpha;
            particleData->pos.x = (particleData->accel.z * sind(particleData->accel.x)) + particleData->vel.x;
            particleData->accel.x += particleData->accel.y;
            if (particleData->accel.x >= 360.0f) {
                particleData->accel.x -= 360.0f;
            }
            particleData->pos.y += 3.0f;
            particleData->pos.z -= 1.0f;
            remainingAlpha = particleData->color.a;
            remainingAlpha -= particleData->vel.y;
            if (remainingAlpha < 0.0f) {
                remainingAlpha = 0.0f;
                particleData->speedDecay = 0;
            }

            particleData->color.a = remainingAlpha;
            activeParticleCount++;
        }
    }
    if (activeParticleCount == 0 && particleObject->work[0] == 1) {
        particleObject->work[1] = 1;
    }
}

void UpdateScoreParticleBurst(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float particleLifetime;
    float horizontalAngle;
    float launchSpeed;
    float verticalAngle;
    HU3DPARTICLEDATA *particleData;
    s32 particleIndex;
    s32 freeParticleIndex;
    if (particle->count == 0) {
        particleData = particle->data;
        for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
            particleData->scale = 0;
        }
        particle->work = (void *)1;
        particle->emitCnt = 0;
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0) {
        for (particleIndex = 0; particleIndex < 16; particleIndex++) {
            particleData = particle->data;
            for (freeParticleIndex = 0; freeParticleIndex < particle->maxCnt; freeParticleIndex++, particleData++) {
                if (particleData->scale == 0) {
                    break;
                }
            }
            if (freeParticleIndex == particle->maxCnt) {
                continue;
            }
            horizontalAngle = (360.0f / 255.0f) * ((u8)frand());
            particleData->speedDecay = 45 * sind(horizontalAngle);
            particleData->scaleBase = 45 * cosd(horizontalAngle);
            particleData->colorIdx = 0;
            verticalAngle = 0.098039225f * ((u8)frand()) + 50.0f;
            launchSpeed = (2.0f / 255.0f) * ((u8)frand()) + 2.5f;
            particleData->vel.x = launchSpeed * sind(horizontalAngle) * cosd(verticalAngle);
            particleData->vel.y = 0.8f * (launchSpeed * sind(verticalAngle));
            particleData->vel.z = launchSpeed * cosd(horizontalAngle) * cosd(verticalAngle);
            particleData->accel.x = 1;
            particleData->accel.y = 255;
            particleData->scale = (4.0f / 255.0f) * ((u8)frand()) + 3.0f;
            particleData->color.r = (155.0f / 255.0f) * ((u8)frand()) + 100.0f;
            particleData->color.g = 0.21568629f * ((u8)frand()) + 200.0f;
            particleData->color.b = 255;
            particleData->color.a = particleData->accel.y;
        }
        particle->dataCnt = 0.058823533f * ((u8)frand()) + 30.0f;
    }
    else {
        particle->dataCnt--;
    }
    particleData = particle->data;
    for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
        if (particleData->scale != 0) {
            particleLifetime = particleData->accel.x;
            particleData->pos.x = (particleData->vel.x * particleLifetime) + particleData->speedDecay;
            particleData->pos.z = (particleData->vel.z * particleLifetime) + particleData->scaleBase;
            particleData->pos.y = ((particleData->vel.y * particleLifetime) + particleData->colorIdx) - (0.2 * particleLifetime * particleLifetime);
            particleData->accel.y -= 3.5f;
            particleData->color.a = particleData->accel.y;
            if (particleData->scale < 0 || particleData->accel.y < 10.0f || particleData->pos.y <= 0.0f) {
                particleData->scale = 0;
                particle->emitCnt++;
            }

            particleData->accel.x += 0.7f;
        }
    }
}

void UpdateScoreParticleFade(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float particleLifetime;
    float horizontalAngle;
    float launchSpeed;
    float verticalAngle;
    HU3DPARTICLEDATA *particleData;
    s32 particleIndex;
    s32 freeParticleIndex;
    if (particle->count == 0) {
        particleData = particle->data;
        for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
            particleData->scale = 0;
        }
        particle->work = (void *)1;
        particle->emitCnt = 0;
        particle->dataCnt = 0;
    }
    if (particle->work) {
        for (particleIndex = 0; particleIndex < 20; particleIndex++) {
            particleData = particle->data;
            for (freeParticleIndex = 0; freeParticleIndex < particle->maxCnt; freeParticleIndex++, particleData++) {
                if (particleData->scale == 0) {
                    break;
                }
            }
            if (freeParticleIndex != particle->maxCnt) {
                horizontalAngle = (360.0f / 255.0f) * ((u8)frand());
                particleData->speedDecay = 40 * sind(horizontalAngle);
                particleData->scaleBase = 40 * cosd(horizontalAngle);
                particleData->colorIdx = 0;
                verticalAngle = (20.0f / 255.0f) * ((u8)frand()) + 70.0f;
                launchSpeed = (4.0f / 255.0f) * ((u8)frand()) + 5.0f;
                particleData->vel.x = launchSpeed * sind(horizontalAngle) * cosd(verticalAngle);
                particleData->vel.y = launchSpeed * sind(verticalAngle);
                particleData->vel.z = launchSpeed * cosd(horizontalAngle) * cosd(verticalAngle);
                particleData->accel.x = 1;
                particleData->accel.y = 255;
                particleData->scale = (4.0f / 255.0f) * ((u8)frand()) + 5.0f;
                particleData->color.r = (155.0f / 255.0f) * ((u8)frand()) + 100.0f;
                particleData->color.g = 0.21568629f * ((u8)frand()) + 200.0f;
                particleData->color.b = 255;
                particleData->color.a = particleData->accel.y;
            }
            else {
                particle->work = NULL;
                break;
            }
        }
    }
    particleData = particle->data;
    for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
        if (particleData->scale != 0) {
            particleLifetime = particleData->accel.x;
            particleData->pos.x = (particleData->vel.x * particleLifetime) + particleData->speedDecay;
            particleData->pos.z = (particleData->vel.z * particleLifetime) + particleData->scaleBase;
            particleData->pos.y = ((particleData->vel.y * particleLifetime) + particleData->colorIdx) - (0.2 * particleLifetime * particleLifetime);
            particleData->accel.y -= 3.5f;
            particleData->color.a = particleData->accel.y;
            if (particleData->scale < 0 || particleData->accel.y < 10.0f || particleData->pos.y <= 0.0f) {
                particleData->scale = 0;
                particle->emitCnt++;
            }
            particleData->accel.x += 1.0f;
        }
    }
    if (particle->emitCnt >= particle->maxCnt && particle->work == NULL) {
        particle->dataCnt = 1;
    }
}

void EmptyScoreParticleCallback(OMOBJ *object);
void UpdateScoreParticleDisplayModel(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);

OMOBJ *CreateParticleEffectController(void)
{
    OMOBJ *object = omAddObjEx(HuPrcCurrentGet(), 1300, 5, 0, -1, EmptyScoreParticleCallback);
    HU3DPARTICLE *particle;
    omSetStatBit(object, 0x100);
    object->mdlId[0] = Hu3DParticleCreate(scoreParticleBonusAnimation, 200);
    Hu3DParticleHookSet(object->mdlId[0], UpdateScoreParticleDisplayModel);
    Hu3DParticleColSet(object->mdlId[0], 255, 255, 255);
    Hu3DModelPosSet(object->mdlId[0], 0, 0, 0);
    Hu3DParticleAnimModeSet(object->mdlId[0], 0);
    Hu3DModelLayerSet(object->mdlId[0], 1);
    Hu3DParticleBlendModeSet(object->mdlId[0], 1);
    particle = Hu3DData[object->mdlId[0]].hookData;
    return object;
}

void EmptyScoreParticleCallback(OMOBJ *object) { }

void UpdateScoreParticleDisplayModel(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    HU3DPARTICLEDATA *particleData;
    s32 particleIndex;
    s32 freeParticleIndex;
    if (particle->count == 0) {
        particleData = particle->data;
        for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
            particleData->scale = 0;
            particleData->pos.y = 950;
        }
    }
    if (particle->dataCnt == 0) {
        for (particleIndex = 0; particleIndex < 30; particleIndex++) {
            particleData = particle->data;
            for (freeParticleIndex = 0; freeParticleIndex < particle->maxCnt; freeParticleIndex++, particleData++) {
                if (particleData->scale == 0) {
                    break;
                }
            }
            if (freeParticleIndex == particle->maxCnt) {
                continue;
            }
            particleData->scale = 1;
            particleData->color.a = 150;
            particleData->pos.x = ((11.764707f * ((u8)frand())) + (-1500.0f));
            particleData->pos.z = ((6.666667f * ((u8)frand())) + (-2000.0f));
            particleData->vel.x = 0;
            particleData->vel.y = (((5.0f / 255.0f) * ((u8)frand())) + (5.0f));
            particleData->vel.z = ((0.011764707f * ((u8)frand())) + (18.0f));
        }
        particle->dataCnt = (frand() % 5) + 4;
    }
    else {
        particle->dataCnt--;
    }
    particleData = particle->data;
    for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
        if (particleData->scale != 0) {
            particleData->pos.x += 1.1f;
            particleData->pos.z += 1.1f;
            particleData->scale = (particleData->vel.z * sind(particleData->vel.x)) + 1.0;
            particleData->vel.x += particleData->vel.y;
            if (particleData->vel.x >= 180.0f) {
                particleData->scale = 0.0f;
            }
        }
    }
}

void UpdateScoreParticleDisplay(OMOBJ *object);
void UpdateScoreParticleDisplayModelMotion(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix);

OMOBJ *CreateParticleModelManager(HUPROCESS *objman)
{
    OMOBJ *object;
    object = omAddObjEx(objman, 1300, 1, 0, -1, UpdateScoreParticleDisplay);
    object->mdlId[0] = Hu3DParticleCreate(scoreParticleAnimationA, 450);
    Hu3DParticleHookSet(object->mdlId[0], UpdateScoreParticleDisplayModelMotion);
    Hu3DParticleColSet(object->mdlId[0], 255, 255, 255);
    Hu3DModelPosSet(object->mdlId[0], 0, -6000, -21000);
    Hu3DParticleAnimModeSet(object->mdlId[0], 0);
    Hu3DModelLayerSet(object->mdlId[0], 1);
    Hu3DParticleBlendModeSet(object->mdlId[0], 1);
    return object;
}

void UpdateScoreParticleDisplay(OMOBJ *object)
{
    omSetTra(object, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    if (object->work[0] == 1) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}

void UpdateScoreParticleDisplayModelMotion(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix)
{
    float remainingAlpha;
    float particleAngle;
    HU3DPARTICLEDATA *particleData;
    s32 particleIndex;
    s32 freeParticleIndex;
    if (particle->count == 0) {
        particleData = particle->data;
        for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
            particleData->color.a = 180;
            particleData->vel.x = ((3.9215689f * ((u8)frand())) + (-500.0f));
            particleData->vel.y = ((3.529412f * ((u8)frand())) + (-500.0f));
            particleData->vel.z = (-300.0f) - ((3.9215689f * ((u8)frand())));
            particleData->accel.x = (360.0f / 255.0f) * ((u8)frand());
            particleData->accel.y = (4.0f / 255.0f) * ((u8)frand());
            particleData->scale = 2;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0) {
        for (particleIndex = 0; particleIndex < 2; particleIndex++) {
            particleData = particle->data;
            for (freeParticleIndex = 0; freeParticleIndex < particle->maxCnt; freeParticleIndex++, particleData++) {
                if (particleData->color.a == 0) {
                    break;
                }
            }
            if (freeParticleIndex == particle->maxCnt) {
                continue;
            }
            particleData->color.a = 180;
            particleData->vel.x = -50.0f + (0.3921569f * ((u8)frand()));
            particleData->vel.y = 0.058823533f * ((u8)frand());
            particleData->accel.x = (90.0f / 255.0f) * ((u8)frand());
            particleData->accel.y = 5.0f + (0.098039225f * ((u8)frand()));
            particleData->accel.z = (float)(frand() % 10) + 8.0f;
            particleData->pos.z = -5.0f + ((11.0f / 255.0f) * ((u8)frand()));
            particleData->pos.y = (float)(frand() % 31) + -5.0f;
            particleData->scale = particleData->vel.y + 35.0f;
            particleData->color.a = 210;
            particleData->vel.y = (0.2 * particleData->vel.y) + 5.0;
            particle->dataCnt = (frand() % 10) + 10;
        }
    }
    else {
        particle->dataCnt--;
    }
    particleData = particle->data;
    particleAngle = cameraMoveDistance * 0.3f;
    for (particleIndex = 0; particleIndex < particle->maxCnt; particleIndex++, particleData++) {
        if (particleData->color.a == 0) {
            continue;
        }
        particleData->pos.x = particleData->vel.x;
        particleData->pos.y = particleData->vel.y;
        particleData->pos.z = particleData->vel.z;
        particleData->vel.x -= 0.5 * sind(particleData->accel.x);
        particleData->vel.z -= -particleAngle;
        particleData->accel.x += particleData->accel.y;
        if (particleData->accel.x >= 360.0f) {
            particleData->accel.x -= 360.0f;
        }
        if (particleData->vel.z >= 0.0f) {
            remainingAlpha = 800.0f + ((300.0f / 255.0f) * ((u8)frand()));
            particleData->vel.z -= remainingAlpha;
        }
    }
}
