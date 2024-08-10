#include "REL/option.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"

#include "dolphin.h"
#include "ext_math.h"

typedef struct {
    /* 0x00 */ s32 execMode;
    /* 0x04 */ s16 motion;
    /* 0x08 */ Vec pos;
    /* 0x14 */ Vec newPos;
    /* 0x20 */ Vec rot;
    /* 0x2C */ Vec posDelta;
    /* 0x38 */ float distRemain;
    /* 0x3C */ float angle;
    /* 0x40 */ float angleEnd;
    /* 0x44 */ float camDist;
    /* 0x48 */ char unk48[0xC];
    /* 0x54 */ float time;
    /* 0x58 */ float speed;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ s32 unk_60;
} GuideWork; // Size 0x64

#define MODE_DISABLED 0
#define MODE_HANDLE_GUIDE 1

static void SetExecMode(omObjData *object, s32 mode);
static s32 GetExecMode(omObjData *object);
static void ExecGuide(omObjData *object);
static void UpdateGuide(omObjData *object);
static float LerpAngle(float arg0, float arg1, float arg2);

omObjData *optionGuide;

static const s32 guideMotTbl[] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 16),
    DATA_MAKE_NUM(DATADIR_OPTION, 17),
    DATA_MAKE_NUM(DATADIR_OPTION, 18),
};

static omObjFunc execModeTbl[] = { NULL, ExecGuide };

omObjData *OptionGuideCreate(void)
{
    omObjData *object;
    GuideWork *work;
    s32 i;

    object = omAddObjEx(optionObjMan, 1002, 1, 3, 2, NULL);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(GuideWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    work->pos.x = -298.59f;
    work->pos.z = 298.21f;
    work->pos.y = 0.0f;

    work->rot.x = 0.0f;
    work->rot.y = 134.42f;
    work->rot.z = 0.0f;

    work->posDelta.x = 0.0f;
    work->posDelta.z = 0.0f;
    work->posDelta.y = 0.0f;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 12));
    Hu3DModelLayerSet(object->model[0], 1);
    for (i = 0; i < 3; i++) {
        object->motion[i] = Hu3DJointMotionFile(object->model[0], guideMotTbl[i]);
    }
    work->unk_5C = CharModelEffectNpcInit(object->model[0], object->motion[2], 1, 0xC);
    work->unk_60 = CharModelEffectNpcInit(object->model[0], object->motion[1], 0, 0xC);
    CharModelLayerSetAll(1);
    Hu3DModelShadowSet(object->model[0]);
    Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, 0x40000001);
    SetExecMode(object, MODE_DISABLED);
    UpdateGuide(object);
    return object;
}

void OptionGuideKill(omObjData *object)
{
    GuideWork *work = object->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
    for (i = 0; i < 3; i++) {
        Hu3DMotionKill(object->motion[i]);
    }
    HuMemDirectFree(work);
}

static void SetExecMode(omObjData *object, s32 execMode)
{
    GuideWork *work = object->data;

    work->execMode = execMode;
    object->func = execModeTbl[execMode];
    object->unk10 = 0;
    object->unk10 = 0;
}

static s32 GetExecMode(omObjData *object)
{
    GuideWork *work = object->data;

    return work->execMode;
}

void OptionGuideWalkExec(omObjData *object, float angleEnd, float camDist, s32 duration)
{
    GuideWork *work = object->data;

    work->angleEnd = angleEnd;
    work->camDist = camDist;
    work->time = 0.0f;
    work->speed = 1.0f / duration;
    work->motion = 0;
    SetExecMode(object, MODE_HANDLE_GUIDE);
}

static void ExecGuide(omObjData *object)
{
    GuideWork *work = object->data;
    float angle;
    float weight;

    switch (object->unk10) {
        case 0:
            work->angle = fmod(-atan2d(work->pos.x, work->pos.z), 360.0);
            if (work->angle < 0.0f) {
                work->angle += 360.0f;
            }
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            weight = sind(90.0f * work->time);
            angle = work->angle + weight * (work->angleEnd - work->angle);
            work->newPos.x = work->camDist * -sind(angle);
            work->newPos.z = work->camDist * cosd(angle);
            work->newPos.y = 0.0f;
            work->posDelta.x = work->newPos.x - work->pos.x;
            work->posDelta.z = work->newPos.z - work->pos.z;
            if (work->time <= 0.0f) {
                work->posDelta.x = 0.0f;
                work->posDelta.z = 0.0f;
                work->pos = work->newPos;
            }
            if ((work->time += work->speed) < 1.0f) {
                break;
            }
            angle = fmod(-atan2d(work->pos.x, work->pos.z), 360.0);
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            work->newPos.x = 422.0 * -sind(angle);
            work->newPos.z = 422.0 * cosd(angle);
            work->posDelta.x = (work->newPos.x - work->pos.x) / 10.0f;
            work->posDelta.z = (work->newPos.z - work->pos.z) / 10.0f;
            work->speed = 0.1f;
            work->time = 0.0f;
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if ((work->time += work->speed) < 1.0f) {
                break;
            }
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            work->pos = work->newPos;
            work->posDelta.x = 0.0f;
            work->posDelta.y = 0.0f;
            work->posDelta.z = 0.0f;
            UpdateGuide(object);
            SetExecMode(object, MODE_DISABLED);
            break;
    }
    UpdateGuide(object);
}

static void UpdateGuide(omObjData *object)
{
    GuideWork *work = object->data;
    s16 motion = 0;
    work->distRemain = sqrtf(work->posDelta.x * work->posDelta.x + work->posDelta.z * work->posDelta.z);
    if (0.001f <= work->distRemain) {
        if (14.0f <= work->distRemain) {
            work->posDelta.x /= work->distRemain;
            work->posDelta.z /= work->distRemain;
            work->distRemain = 14.0f;
            work->posDelta.x = 14.0f * work->posDelta.x;
            work->posDelta.z = 14.0f * work->posDelta.z;
        }
        work->rot.y = LerpAngle(work->rot.y, atan2d(work->posDelta.x, work->posDelta.z), 0.4f);
        if (8.0f <= work->distRemain) {
            motion = 2;
        }
        else {
            motion = 1;
        }
    }
    work->pos.x += work->posDelta.x;
    work->pos.z += work->posDelta.z;
    if (work->motion != motion) {
        Hu3DMotionShiftSet(*object->model, object->motion[motion], 0.0f, 8.0f, 0x40000001);
        work->motion = motion;
    }
    omSetTra(object, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(object, work->rot.x, work->rot.y, work->rot.z);
}

static float LerpAngle(float start, float end, float time)
{
    float angle;

    float delta = fmod(end - start, 360.0);
    if (0.0f > delta) {
        delta += 360.0f;
    }
    if (180.0f < delta) {
        delta -= 360.0f;
    }
    angle = fmod(start + delta * time, 360.0);
    if (0.0f > angle) {
        angle += 360.0f;
    }
    return angle;
}
