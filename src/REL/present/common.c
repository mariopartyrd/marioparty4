#include "ext_math.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "REL/present.h"

typedef struct GuideWork {
    /* 0x00 */ s32 execMode;
    /* 0x04 */ s16 motion;
    /* 0x08 */ Vec pos;
    /* 0x14 */ Vec newPos;
    /* 0x20 */ Vec rot;
    /* 0x2C */ Vec posDelta;
    /* 0x38 */ float distRemain;
    /* 0x3C */ char unk3C[0xC];
    /* 0x48 */ float time;
    /* 0x4C */ float speed;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
} GuideWork; /* size = 0x58 */

static void ExecGuideEnter(omObjData *object);
static void ExecGuideLeave(omObjData *object);
static void UpdateGuide(omObjData *object);
static float LerpAngle(float start, float end, float time);

static omObjFunc execModeTbl[] = { NULL, ExecGuideEnter, ExecGuideLeave };

static const s32 guideMotTbl[] = {
    DATA_MAKE_NUM(DATADIR_PRESENT, 137),
    DATA_MAKE_NUM(DATADIR_PRESENT, 138),
    DATA_MAKE_NUM(DATADIR_PRESENT, 139),
};

omObjData *PresentGuideCreate(void)
{
    s32 var_r29;

    omObjData *object = omAddObjEx(presentObjMan, 1002, 1, 3, 2, NULL);
    GuideWork *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(GuideWork), MEMORY_DEFAULT_NUM);
    object->data = work;

    work->pos.x = 0.0f;
    work->pos.z = 0.0f;
    work->pos.y = 0.0f;
    work->rot.x = 0.0f;
    work->rot.y = 0.0f;
    work->rot.z = 0.0f;

    work->posDelta.x = 0.0f;
    work->posDelta.z = 0.0f;
    work->posDelta.y = 0.0f;
    object->model[0] = Hu3DModelCreate(HuDataReadNum(DATA_MAKE_NUM(DATADIR_PRESENT, 136), MEMORY_DEFAULT_NUM));
    Hu3DModelLayerSet(object->model[0], 1);

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], guideMotTbl[var_r29]);
    }
    Hu3DMotionShiftSet(object->model[0], object->motion[work->motion = 0], 0.0f, 8.0f, 0x40000001);
    work->unk_50 = CharModelEffectNpcInit(object->model[0], object->motion[2], 1, 10);
    work->unk_54 = CharModelEffectNpcInit(object->model[0], object->motion[1], 0, 10);
    CharModelLayerSetAll(1);
    Hu3DModelShadowSet(object->model[0]);
    PresentGuideExecModeSet(object, PRESENT_GUIDE_MODE_NONE);
    UpdateGuide(object);
    Hu3DModelAttrSet(object->model[0], 1);

    return object;
}

void PresentGuideKill(omObjData *object)
{
    void *work = object->data;

    s32 i;
    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }

    for (i = 0; i < 3; i++) {
        Hu3DMotionKill(object->motion[i]);
    }
    HuMemDirectFree(work);
}

void PresentGuideExecModeSet(omObjData *object, s32 execMode)
{
    GuideWork *work = object->data;

    work->execMode = execMode;
    object->func = execModeTbl[execMode];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 PresentGuideExecModeGet(omObjData *object)
{
    GuideWork *work = object->data;

    return work->execMode;
}

static void ExecGuideEnter(omObjData *object)
{
    float var_f31;
    GuideWork *work = object->data;

    switch (object->unk10) {
        case 0:
            Hu3DModelAttrReset(object->model[0], 1);
            work->pos.x = -300.0f;
            work->pos.z = -180.0f;
            work->time = 0.0f;
            work->speed = 0.025f;
            object->unk10 = 1;
        case 1:
            var_f31 = sind(90.0f * work->time);
            var_f31 *= var_f31;
            work->newPos.x = -300.0f + (300.0f * var_f31);
            work->posDelta.x = work->newPos.x - work->pos.x;
            if ((work->time += work->speed) < 1.0f) {
                break;
            }
            work->pos.x = 0.0f;
            work->time = 0.0f;
            work->speed = 0.05f;
            object->unk10 = 2;
        case 2:
            work->posDelta.x = 0.0f;
            work->posDelta.z = 0.01f;
            if ((work->time += work->speed) < 1.0f) {
                break;
            }
            work->rot.y = 0.0f;
            work->posDelta.x = 0.0f;
            work->posDelta.y = 0.0f;
            work->posDelta.z = 0.0f;
            object->unk10 = 3;
        case 3:
            PresentGuideExecModeSet(object, PRESENT_GUIDE_MODE_NONE);
            break;
        default:
            break;
    }
    UpdateGuide(object);
}

static void ExecGuideLeave(omObjData *object)
{
    float weight;

    GuideWork *work = object->data;
    switch (object->unk10) {
        case 0:
            work->time = 0.0f;
            work->speed = 0.025f;
            Hu3DModelAttrReset(object->model[0], 1);
            object->unk10 = 1;
        case 1:
            weight = sind(90.0f * work->time);
            weight *= weight;
            work->newPos.x = -(300.0f * weight);
            work->posDelta.x = work->newPos.x - work->pos.x;
            if ((work->time += work->speed) < 1.0f) {
                break;
            }
            object->unk10 = 2;
        case 2:
            Hu3DModelAttrSet(object->model[0], 1);
            PresentGuideExecModeSet(object, PRESENT_GUIDE_MODE_NONE);
            break;
        default:
            break;
    }
    UpdateGuide(object);
    (void)object;
}

static void UpdateGuide(omObjData *object)
{
    GuideWork *work = object->data;
    s16 motion = 0;

    work->distRemain = sqrtf(work->posDelta.x * work->posDelta.x + work->posDelta.z * work->posDelta.z);
    if (0.001f <= work->distRemain) {
        if (12.0f <= work->distRemain) {
            work->posDelta.x /= work->distRemain;
            work->posDelta.z /= work->distRemain;
            work->distRemain = 12.0f;
            work->posDelta.x = 12.0f * work->posDelta.x;
            work->posDelta.z = 12.0f * work->posDelta.z;
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
        Hu3DMotionShiftSet(object->model[0], object->motion[work->motion = motion], 0.0f, 8.0f, 0x40000001);
    }
    omSetTra(object, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(object, work->rot.x, work->rot.y, work->rot.z);
}

static float LerpAngle(float start, float end, float time)
{
    float angle;

    float delta = fmod(end - start, 360.0f);
    if (0.0f > delta) {
        delta += 360.0f;
    }
    if (180.0f < delta) {
        delta -= 360.0f;
    }
    angle = fmod(start + (delta * time), 360.0f);
    if (0.0f > angle) {
        angle += 360.0f;
    }
    return angle;
}
