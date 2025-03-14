#include "ext_math.h"
#include "game/hsfman.h"
#include "game/pad.h"
#include "game/printfunc.h"

#include "REL/present.h"

typedef struct CameraWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec target;
    /* 0x18 */ Vec up;
    /* 0x24 */ float zoom;
    /* 0x28 */ float rot;
    /* 0x2C */ Vec posPrev;
    /* 0x38 */ Vec targetPrev;
    /* 0x44 */ char unk44[0xC];
    /* 0x50 */ float zoomPrev;
    /* 0x54 */ float rotPrev;
    /* 0x58 */ Vec posTarget;
    /* 0x64 */ Vec posFocus;
    /* 0x70 */ char unk70[0xC];
    /* 0x7C */ float zoomTarget;
    /* 0x80 */ float rotTarget;
    /* 0x84 */ float timeEye;
    /* 0x88 */ float eyeSpeed;
    /* 0x8C */ float timeTarget;
    /* 0x90 */ float targetSpeed;
    /* 0x94 */ float timeRot;
    /* 0x98 */ float rotSpeed;
} CameraWork; /* size = 0x9C */ // same as in option/camera.c

static void ExecCameraObj(omObjData *object);
static void ExecCamera(omObjData *object);

omObjData *PresentCameraCreate(void)
{
    omObjData *object = omAddObjEx(presentObjMan, 1001, 0, 0, 3, ExecCameraObj);
    CameraWork *work = HuMemDirectMallocNum(HEAP_SYSTEM, 156, MEMORY_DEFAULT_NUM);
    object->data = work;

    work->pos.x = 0.0f;
    work->pos.y = 0.0f;
    work->pos.z = 0.0f;

    work->target.x = 0.0f;
    work->target.y = 0.0f;
    work->target.z = 0.0f;

    work->up.x = 0.0f;
    work->up.y = 1.0f;
    work->up.z = 0.0f;

    work->zoom = 0.0f;
    work->rot = 0.0f;
    work->timeTarget = 1.0f;
    work->timeEye = 1.0f;
    work->timeRot = 1.0f;
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 42.0f, 10.0f, 8000.0f, 1.2f);
    PresentCameraFocusSet(object, 0.0f, 0.0f, -600.0f, 1);
    PresentCameraTargetSet(object, 0.0f, 220.0f, 250.0f, 1);

    return object;
}

void PresentCameraKill(omObjData *object)
{
    HuMemDirectFree(object->data);
}

void PresentCameraTargetSet(omObjData *object, float x, float y, float z, s32 duration)
{
    CameraWork *work = object->data;

    work->posTarget.x = x;
    work->posTarget.y = y;
    work->posTarget.z = z;

    work->posPrev = work->pos;
    work->timeEye = 0.0f;
    work->eyeSpeed = 1.0f / duration;
}

void PresentCameraFocusSet(omObjData *object, float x, float y, float z, s32 duration)
{
    CameraWork *work = object->data;

    work->posFocus.x = x;
    work->posFocus.y = y;
    work->posFocus.z = z;

    work->targetPrev = work->target;
    work->timeTarget = 0.0f;
    work->targetSpeed = 1.0f / duration;
}

void PresentCameraViewSet(omObjData *object, float zoom, float rot, float y, s32 duration)
{
    CameraWork *work = object->data;

    work->posFocus.y = y;
    work->zoomTarget = zoom;
    work->rotTarget = rot;

    work->targetPrev.y = work->target.y;
    work->zoomPrev = work->zoom;
    work->rotPrev = work->rot;
    work->timeRot = 0.0f;
    work->rotSpeed = 1.0f / duration;
}

float PresentCameraZoomGet(omObjData *object)
{
    CameraWork *work = object->data;

    float zoom = work->zoom;
    return zoom;
}

float PresentCameraRotGet(omObjData *object)
{
    CameraWork *work = object->data;

    float rot = work->rot;
    return rot;
}

void PresentCameraPosGet(omObjData *object, float *x, float *y, float *z)
{
    CameraWork *work = object->data;

    *x = work->pos.x;
    *y = work->pos.y;
    *z = work->pos.z;
}

void PresentCameraTargetGet(omObjData *object, float *x, float *y, float *z)
{
    CameraWork *work = object->data;

    *x = work->target.x;
    *y = work->target.y;
    *z = work->target.z;
}

s32 PresentCameraDoneCheck(omObjData *object)
{
    CameraWork *work = object->data;

    s32 var_r30 = 1;
    s32 var_r29 = 1;

    if (!(work->timeTarget < 1.0f) && !(work->timeRot < 1.0f)) {
        var_r29 = 0;
    }
    if (!var_r29 && !(work->timeEye < 1.0f)) {
        var_r30 = 0;
    }
    return var_r30;
}

static void ExecCameraObj(omObjData *object)
{
    ExecCamera(object);
}

static void ExecCamera(omObjData *object)
{
    CameraWork *work = object->data;
    float weight;
    float dx;
    float dz;

    if (work->timeEye < 1.0f) {
        weight = sind(90.0f * work->timeEye);
        work->pos.x = work->posPrev.x + weight * (work->posTarget.x - work->posPrev.x);
        work->pos.y = work->posPrev.y + weight * (work->posTarget.y - work->posPrev.y);
        work->pos.z = work->posPrev.z + weight * (work->posTarget.z - work->posPrev.z);

        if ((work->timeEye += work->eyeSpeed) >= 1.0f) {
            work->pos = work->posTarget;
        }
    }
    if (work->timeTarget < 1.0f) {
        weight = sind(90.0f * work->timeTarget);
        work->target.x = work->targetPrev.x + weight * (work->posFocus.x - work->targetPrev.x);
        work->target.y = work->targetPrev.y + weight * (work->posFocus.y - work->targetPrev.y);
        work->target.z = work->targetPrev.z + weight * (work->posFocus.z - work->targetPrev.z);

        if ((work->timeTarget += work->targetSpeed) >= 1.0f) {
            work->target = work->posFocus;
        }
    }
    if (work->timeRot < 1.0f) {
        weight = sind(90.0f * work->timeRot);
        work->target.y = work->targetPrev.y + (weight * (work->posFocus.y - work->targetPrev.y));
        work->zoom = work->zoomPrev + (weight * (work->zoomTarget - work->zoomPrev));
        work->rot = work->rotPrev + (weight * (work->rotTarget - work->rotPrev));

        if ((work->timeRot += work->rotSpeed) >= 1.0f) {
            work->target.y = work->posFocus.y;
            work->zoom = work->zoomTarget;
            work->rot = work->rotTarget;
        }
        work->target.x = work->zoom * -sind(work->rot);
        work->target.z = work->zoom * cosd(work->rot);
    }
    dx = work->target.x - work->pos.x;
    dz = work->target.z - work->pos.z;

    work->zoom = sqrtf(dx * dx + dz * dz);
    work->rot = fmod(-atan2d(dx, dz), 360.0);
    if (work->rot < 0.0f) {
        work->rot += 360.0f;
    }
    Hu3DCameraPosSet(1, work->pos.x, work->pos.y, work->pos.z, work->up.x, work->up.y, work->up.z, work->target.x, work->target.y, work->target.z);
}

static void CameraExecDebug(omObjData *object)
{
    if (HuPadBtn[0] & PAD_BUTTON_B) {
        CameraWork *work = object->data;

        work->target.x += (0.5f * HuPadStkX[0]);
        work->target.y += (0.5f * HuPadStkY[0]);
        work->pos.z += (0.5f * HuPadTrigL[0]);
        work->pos.z -= (0.5f * HuPadTrigR[0]);
        work->pos.x += (0.5f * HuPadSubStkY[0]);
        work->pos.y += (0.5f * HuPadSubStkX[0]);
    }
}

static void CameraPrintDebug(omObjData *object)
{
    CameraWork *work = object->data;
    print8(32, 64, 1.5f, "AT  : x=%.2f y=%.2f z=%.2f", work->target.x, work->target.y, work->target.z);
    print8(32, 80, 1.5f, "EYE : x=%.2f y=%.2f z=%.2f", work->pos.x, work->pos.y, work->pos.z);
    print8(32, 96, 1.5f, "R : %.2f    DEG: %.2f", work->zoom, work->rot);
}
