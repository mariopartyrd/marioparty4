#ifndef REL_M401DLL_H
#define REL_M401DLL_H

#include "game/object.h"
#include "dolphin.h"

extern float cameraFieldOfView;
extern float cameraNearPlane;
extern float cameraFarPlane;
extern s16 cameraAspectRatio;
extern Vec cameraPosition;
extern Vec cameraTarget;
extern float cameraMoveDistance;
extern OMOBJ **playerObjects;

typedef struct M401PlayerWork {
	s16 playerState;
	s32 playerIndex;
	s32 controllerIndex;
	Vec worldPosition;
	Vec effectAnchorPosition;
	Vec targetPosition;
	Vec movementOrigin;
	Vec reservedVector3c;
	OMOBJ *trailEffect;
	OMOBJ *landingEffect;
	OMOBJ *scoreEffect;
	OMOBJ *targetObject;
	Vec movementParameters;
	float facingAngle;
	s16 isRoundWinner;
	s16 isWalking;
	s16 stateInitialized;
	s16 stateTimer;
	s16 reservedState70;
	s16 score;
	s16 scorePopupValue;
	s16 reservedState76;
	s16 isStunned;
	s16 stunTimer;
	s16 aiDecisionTimer;
	s16 aiBehavior;
	float animationAngle;
	s16 collisionCooldown;
	s16 characterModelIndex;
	float jumpVelocity;
	s16 runTimer;
	s16 idleTimer;
	s16 aiInputCooldown;
	s16 aiAvoidanceFlags;
	Vec reservedVector94;
	s8 reservedByteA0;
	s8 reservedByteA1;
} M401WorkPlayer;

typedef struct ScoreParticleWork {
	Vec particlePosition;
	OMOBJ *ownerObject;
	s16 activeModelCallbacks;
	s16 poolSlotIndex;
	s16 fadeOutRequested;
	s32 particleVariant;
	float opacity;
} ScoreParticleWork;

void ShowScoreGainPopup(s16 playerIndex);

void SetObjectPosition(OMOBJ *object, float x, float y, float z);

void ProjectWorldPositionToScreen(Vec *worldPosition, Vec *screenPosition);
void LoadScoreParticleResources(void);
void FreeScoreParticleResources(void);

void CreateScoreParticleModelPool(void);
OMOBJ *createScoreParticleEffect(Vec *spawnPosition, s16 particleVariant);

OMOBJ *createParticleEffectController(void);
OMOBJ *createParticleModelManager(HUPROCESS *objectManager);

#endif
