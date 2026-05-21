#include "game/ClusterExec.h"
#include "game/EnvelopeExec.h"
#include "game/ShapeExec.h"
#include "game/hsfload.h"
#include "game/hu3d.h"
#include "game/init.h"

#include "ext_math.h"
#include <string.h>

#define HU3D_MOTATTR_SHIFT_ALL (HU3D_MOTATTR_SHIFT_LOOP|HU3D_MOTATTR_SHIFT_PAUSE|HU3D_MOTATTR_SHIFT_REV)
#define HU3D_MOTATTR_NOSHIFT_ALL (HU3D_MOTATTR_LOOP|HU3D_MOTATTR_PAUSE|HU3D_MOTATTR_REV)
#define HU3D_MOTATTR_ALL (HU3D_MOTATTR_SHIFT_ALL|HU3D_MOTATTR_NOSHIFT_ALL)

static s32 SearchObjectIndex(HSFDATA *arg0, u32 arg1);
static s32 SearchAttributeIndex(HSFDATA *arg0, u32 arg1);

MotionData Hu3DMotion[HU3D_MOTION_MAX];

static HSFBITMAP *bitMapPtr;

void Hu3DMotionInit(void) {
    MotionData *var_r31;
    s16 i;

    var_r31 = (MotionData*) Hu3DData;
    for (i = 0; i < HU3D_MOTION_MAX; i++, var_r31++) {
        var_r31->unk_04 = 0;
    }
}

s16 Hu3DMotionCreate(void *arg0) {
    MotionData *var_r31;
    s16 i;

    var_r31 = Hu3DMotion;
    for (i = 0; i < HU3D_MOTION_MAX; i++, var_r31++) {
        if (var_r31->unk_04 == 0) {
            break;
        }
    }
    if (i == HU3D_MOTION_MAX) {
        OSReport("Error: Create Motion Over!\n");
        return -1;
    }
    var_r31->unk_04 = LoadHSF(arg0);
    var_r31->unk_00 = 0;
    var_r31->unk_02 = -1;
    return i;
}

s16 Hu3DMotionModelCreate(s16 arg0) {
    HU3DMODEL *temp_r29 = &Hu3DData[arg0];
    MotionData *var_r31;
    s16 i;

    var_r31 = Hu3DMotion;
    for (i = 0; i < HU3D_MOTION_MAX; i++, var_r31++) {
        if (var_r31->unk_04 == 0) {
            break;
        }
    }
    if (i == HU3D_MOTION_MAX) {
        OSReport("Error: Create Motion Over!\n");
        return -1;
    }
    var_r31->unk_04 = temp_r29->hsf;
    var_r31->unk_00 = 0;
    var_r31->unk_02 = arg0;
    temp_r29->motIdSrc = i;
    return i;
}

s32 Hu3DMotionKill(s16 arg0) {
    HU3DMODEL *var_r30;
    MotionData *temp_r31;
    s16 i;

    temp_r31 = &Hu3DMotion[arg0];
    if (temp_r31->unk_04 == 0) {
        return 0;
    }
    var_r30 = Hu3DData;
    for (i = 0; i < 512; i++, var_r30++) {
        if (var_r30->hsf && var_r30->motId == arg0 && temp_r31->unk_02 != i) {
            break;
        }
    }
    if (i != 512) {
        return 0;
    }
    if (temp_r31->unk_02 == -1) {
        HuMemDirectFree(temp_r31->unk_04);
    } else {
        Hu3DData[temp_r31->unk_02].motIdSrc = -1;
    }
    temp_r31->unk_04 = NULL;
    return 1;
}

void Hu3DMotionAllKill(void) {
    MotionData *var_r27;
    s16 i;

    var_r27 = Hu3DMotion;
    for (i = 0; i < HU3D_MOTION_MAX; i++, var_r27++) {
        if (var_r27->unk_04) {
            Hu3DMotionKill(i);
        }
    }
}

void Hu3DMotionSet(s16 arg0, s16 arg1) {
    Hu3DData[arg0].motIdShift = -1;
    Hu3DData[arg0].motId = arg1;
    Hu3DData[arg0].motWork.time = 0.0f;
    Hu3DData[arg0].motWork.start = 0.0f;
    Hu3DData[arg0].motWork.end = Hu3DMotionMaxTimeGet(arg0);
}

void Hu3DMotionOverlaySet(s16 arg0, s16 arg1) {
    Hu3DData[arg0].motIdOvl = arg1;
    Hu3DData[arg0].motOvlWork.time = 0.0f;
    Hu3DData[arg0].motOvlWork.speed = 1.0f;
}

void Hu3DMotionOverlayReset(s16 arg0) {
    Hu3DData[arg0].motIdOvl = -1;
}

float Hu3DMotionOverlayTimeGet(s16 arg0) {
    return Hu3DData[arg0].motOvlWork.time;
}

void Hu3DMotionOverlayTimeSet(s16 arg0, float arg1) {
    Hu3DData[arg0].motOvlWork.time = arg1;
}

void Hu3DMotionOverlaySpeedSet(s16 arg0, float arg1) {
    Hu3DData[arg0].motOvlWork.speed = arg1;
}

void Hu3DMotionShiftSet(s16 arg0, s16 arg1, float arg2, float arg3, u32 arg4) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];
    MotionData *sp10 = &Hu3DMotion[arg1];
    s32 var_r30;

    arg4 &= ~HU3D_MOTATTR;
    var_r30 = 0;
    if (temp_r31->motIdShift != -1) {
        temp_r31->motId = temp_r31->motIdShift;
        temp_r31->motWork.time = temp_r31->motShiftWork.time;
        temp_r31->motWork.speed = temp_r31->motShiftWork.speed;
        temp_r31->motWork.start = temp_r31->motShiftWork.start;
        temp_r31->motWork.end = temp_r31->motShiftWork.end;
        if (arg4 & HU3D_MOTATTR_SHIFT_LOOP) {
            var_r30 |= HU3D_MOTATTR_LOOP;
        }
        if (arg4 & HU3D_MOTATTR_SHIFT_PAUSE) {
            var_r30 |= HU3D_MOTATTR_PAUSE;
        }
        if (arg4 & HU3D_MOTATTR_SHIFT_REV) {
            var_r30 |= HU3D_MOTATTR_REV;
        }
        temp_r31->motAttr &= ~HU3D_MOTATTR_ALL;
        temp_r31->motAttr |= var_r30;
        temp_r31->motAttr &= ~HU3D_MOTATTR;
    } else {
        temp_r31->motAttr &= ~HU3D_MOTATTR_SHIFT_ALL;
    }
    temp_r31->motIdShift = arg1;
    temp_r31->motShiftWork.time = arg2;
    temp_r31->motShiftWork.speed = 1.0f;
    temp_r31->motOvlWork.start = 0.0f;
    temp_r31->motOvlWork.end = arg3;
    temp_r31->motShiftWork.start = 0.0f;
    temp_r31->motShiftWork.end = Hu3DMotionShiftMaxTimeGet(arg0);
    if (arg4 & HU3D_MOTATTR_LOOP) {
        var_r30 |= HU3D_MOTATTR_SHIFT_LOOP;
    }
    if (arg4 & HU3D_MOTATTR_PAUSE) {
        var_r30 |= HU3D_MOTATTR_SHIFT_PAUSE;
    }
    if (arg4 & HU3D_MOTATTR_REV) {
        var_r30 |= HU3D_MOTATTR_SHIFT_REV;
    }
    arg4 &= ~HU3D_MOTATTR_NOSHIFT_ALL;
    temp_r31->motAttr |= var_r30 | arg4;
    temp_r31->motAttr &= ~HU3D_MOTATTR;
}

void Hu3DMotionShapeSet(s16 arg0, s16 arg1) {
    Hu3DData[arg0].motIdShape = arg1;
    Hu3DData[arg0].motShapeWork.time = 0.0f;
    Hu3DData[arg0].motShapeWork.speed = 1.0f;
    Hu3DData[arg0].motShapeWork.start = 0.0f;
    Hu3DData[arg0].motShapeWork.end = Hu3DMotionShapeMaxTimeGet(arg0);
}

s16 Hu3DMotionShapeIDGet(s16 arg0) {
    return Hu3DData[arg0].motIdShape;
}

void Hu3DMotionShapeSpeedSet(s16 arg0, float arg1) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    temp_r31->motShapeWork.speed = arg1;
}

void Hu3DMotionShapeTimeSet(s16 arg0, float arg1) {
    Hu3DData[arg0].motShapeWork.time = arg1;
}

float Hu3DMotionShapeMaxTimeGet(s16 arg0) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    return Hu3DMotionMotionMaxTimeGet(temp_r31->motIdShape);
}

void Hu3DMotionShapeStartEndSet(s16 arg0, float arg1, float arg2) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    temp_r31->motShapeWork.start = arg1;
    temp_r31->motShapeWork.end = arg2;
}

s16 Hu3DMotionClusterSet(s16 arg0, s16 arg1) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];
    s16 i;

    for (i = 0; i < 4; i++) {
        if (temp_r31->motIdCluster[i] == -1) {
            temp_r31->motIdCluster[i] = arg1;
            temp_r31->clusterTime[i] = 0.0f;
            temp_r31->clusterSpeed[i] = 1.0f;
            temp_r31->clusterAttr[i] = HU3D_ATTR_NONE;
            temp_r31->attr |= HU3D_ATTR_CLUSTER_ON;
            ClusterAdjustObject(temp_r31->hsf, Hu3DMotion[arg1].unk_04);
            return i;
        }
    }
    OSReport("Error: Cluster Entry Over\n");
    return -1;
}

s16 Hu3DMotionClusterNoSet(s16 arg0, s16 arg1, s16 arg2) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    Hu3DMotionClusterReset(arg0, arg2);
    temp_r31->motIdCluster[arg2] = arg1;
    temp_r31->clusterTime[arg2] = 0.0f;
    temp_r31->clusterSpeed[arg2] = 1.0f;
    temp_r31->attr |= HU3D_ATTR_CLUSTER_ON;
    ClusterAdjustObject(temp_r31->hsf, Hu3DMotion[arg1].unk_04);
    return arg2;
}

void Hu3DMotionShapeReset(s16 arg0) {
    Hu3DData[arg0].motIdShape = -1;
}

void Hu3DMotionClusterReset(s16 arg0, s16 arg1) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];
    s16 i;

    if (arg1 == -1) {
        for (i = 0; i < 4; i++) {
            temp_r31->motIdCluster[i] = -1;
        }
        temp_r31->attr &= ~HU3D_ATTR_CLUSTER_ON;
    } else {
        temp_r31->motIdCluster[arg1] = -1;
        for (i = 0; i < 4; i++) {
            if (temp_r31->motIdCluster[i] != -1) {
                return;
            }
        }
        temp_r31->attr &= ~HU3D_ATTR_CLUSTER_ON;
    }
}

s16 Hu3DMotionIDGet(s16 arg0) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    return temp_r31->motId;
}

s16 Hu3DMotionShiftIDGet(s16 arg0) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    return temp_r31->motIdShift;
}

void Hu3DMotionTimeSet(s16 arg0, float arg1) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    if (Hu3DMotionMaxTimeGet(arg0) <= arg1) {
        arg1 = Hu3DMotionMaxTimeGet(arg0);
    }
    if (arg1 < 0.0f) {
        arg1 = 0.0f;
    }
    temp_r31->motWork.time = arg1;
    if (temp_r31->hsf != (HSFDATA*) -1 && temp_r31->hsf->cenvNum != 0 && (temp_r31->motAttr & HU3D_MOTATTR_PAUSE)) {
        Hu3DMotionExec(arg0, temp_r31->motId, arg1, 0);
        if (temp_r31->motIdShift != -1) {
            Hu3DSubMotionExec(arg0);
        }
        EnvelopeProc(temp_r31->hsf);
    }
}

float Hu3DMotionTimeGet(s16 arg0) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    return temp_r31->motWork.time;
}

float Hu3DMotionShiftTimeGet(s16 arg0) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    return temp_r31->motShiftWork.time;
}

float Hu3DMotionMaxTimeGet(s16 arg0) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];
    MotionData *temp_r30;
    HSFMOTION *temp_r29;
    s16 temp_r28;

    if (temp_r31->motId == -1) {
        return 0.0f;
    }
    temp_r30 = &Hu3DMotion[temp_r31->motId];
    temp_r29 = temp_r30->unk_04->motion;
    temp_r28 = 0.0001 + temp_r29->maxTime;
    return temp_r28;
}

float Hu3DMotionShiftMaxTimeGet(s16 arg0) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];
    MotionData *temp_r30;
    HSFMOTION *temp_r29;
    s16 temp_r28;

    if (temp_r31->motIdShift == -1) {
        return 0.0f;
    }
    temp_r30 = &Hu3DMotion[temp_r31->motIdShift];
    temp_r29 = temp_r30->unk_04->motion;
    temp_r28 = 0.0001 + temp_r29->maxTime;
    return temp_r28;
}

void Hu3DMotionShiftStartEndSet(s16 arg0, float arg1, float arg2) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    temp_r31->motShiftWork.start = arg1;
    temp_r31->motShiftWork.end = arg2;
}

float Hu3DMotionMotionMaxTimeGet(s16 arg0) {
    MotionData *temp_r31 = &Hu3DMotion[arg0];
    HSFMOTION *temp_r30;
    s16 temp_r29;

    if (temp_r31->unk_04 == 0) {
        return 0.0f;
    }
    temp_r30 = temp_r31->unk_04->motion;
    temp_r29 = 0.0001 + temp_r30->maxTime;
    return temp_r29;
}

void Hu3DMotionStartEndSet(s16 arg0, float arg1, float arg2) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    temp_r31->motWork.start = arg1;
    temp_r31->motWork.end = arg2;
}

s32 Hu3DMotionEndCheck(s16 arg0) {
    if (!(Hu3DData[arg0].motAttr & HU3D_MOTATTR_REV)) {
        return (Hu3DMotionMaxTimeGet(arg0) <= Hu3DMotionTimeGet(arg0));
    } else {
        return (Hu3DMotionTimeGet(arg0) <= 0.0f);
    }
}

void Hu3DMotionSpeedSet(s16 arg0, float arg1) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    temp_r31->motWork.speed = arg1;
}

void Hu3DMotionShiftSpeedSet(s16 arg0, float arg1) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    temp_r31->motShiftWork.speed = arg1;
}

void Hu3DMotionNoMotSet(s16 arg0, char *arg1, u32 arg2) {
    HsfConstData *var_r29;
    HSFOBJECT *temp_r3;

    temp_r3 = Hu3DModelObjPtrGet(arg0, arg1);
    if (temp_r3->constData == 0) {
        var_r29 = ObjConstantMake(temp_r3, (u32) Hu3DData[arg0].mallocNo);
    } else {
        var_r29 = temp_r3->constData;
    }
    var_r29->flags |= arg2;
    if (arg2 & 0x10) {
        temp_r3->mesh.curr.pos.x = temp_r3->mesh.base.pos.x;
    }
    if (arg2 & 0x20) {
        temp_r3->mesh.curr.pos.y = temp_r3->mesh.base.pos.y;
    }
    if (arg2 & 0x40) {
        temp_r3->mesh.curr.pos.z = temp_r3->mesh.base.pos.z;
    }
    if (arg2 & 0x80) {
        temp_r3->mesh.curr.rot.x = temp_r3->mesh.base.rot.x;
    }
    if (arg2 & 0x100) {
        temp_r3->mesh.curr.rot.y = temp_r3->mesh.base.rot.y;
    }
    if (arg2 & 0x200) {
        temp_r3->mesh.curr.rot.z = temp_r3->mesh.base.rot.z;
    }
}

void Hu3DMotionNoMotReset(s16 arg0, char *arg1, u32 arg2) {
    HSFOBJECT *temp_r31;
    HsfConstData *temp_r30;

    temp_r31 = Hu3DModelObjPtrGet(arg0, arg1);
    temp_r30 = temp_r31->constData;
    temp_r30->flags &= ~arg2;
}

void Hu3DMotionForceSet(s16 arg0, char *arg1, u32 arg2, float arg3) {
    HsfConstData *var_r29;
    HSFOBJECT *temp_r3;

    temp_r3 = Hu3DModelObjPtrGet(arg0, arg1);
    if (temp_r3->constData == 0) {
        var_r29 = ObjConstantMake(temp_r3, (u32) Hu3DData[arg0].mallocNo);
    } else {
        var_r29 = temp_r3->constData;
    }
    var_r29->flags |= arg2;
    if (arg2 & 0x10) {
        temp_r3->mesh.curr.pos.x = arg3;
    }
    if (arg2 & 0x20) {
        temp_r3->mesh.curr.pos.y = arg3;
    }
    if (arg2 & 0x40) {
        temp_r3->mesh.curr.pos.z = arg3;
    }
    if (arg2 & 0x80) {
        temp_r3->mesh.curr.rot.x = arg3;
    }
    if (arg2 & 0x100) {
        temp_r3->mesh.curr.rot.y = arg3;
    }
    if (arg2 & 0x200) {
        temp_r3->mesh.curr.rot.z = arg3;
    }
}

void Hu3DMotionNext(s16 arg0) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];
    HSFMOTION *temp_r29;
    MotionData *temp_r27;
    u32 temp_r28;
    s16 i;

    temp_r27 = &Hu3DMotion[temp_r31->motId];
    temp_r29 = temp_r27->unk_04->motion;
    temp_r28 = temp_r31->motAttr;
    if (temp_r31->motId != -1) {
        temp_r27 = &Hu3DMotion[temp_r31->motId];
        if (!(temp_r28 & HU3D_MOTATTR_PAUSE)) {
            if (!(temp_r28 & HU3D_MOTATTR_REV)) {
                temp_r31->motWork.time += temp_r31->motWork.speed * minimumVcountf;
            } else {
                temp_r31->motWork.time -= temp_r31->motWork.speed * minimumVcountf;
            }
            if (temp_r28 & HU3D_MOTATTR_LOOP) {
                if (temp_r31->motWork.time < temp_r31->motWork.start) {
                    temp_r31->motWork.time = temp_r31->motWork.end - (temp_r31->motWork.start - temp_r31->motWork.time);
                } else if (temp_r31->motWork.time >= temp_r31->motWork.end) {
                    temp_r31->motWork.time = temp_r31->motWork.start + (temp_r31->motWork.time - temp_r31->motWork.end);
                }
            } else if (temp_r31->motWork.time < 0.0f) {
                temp_r31->motWork.time = 0.0f;
            } else if (temp_r31->motWork.time >= temp_r31->motWork.end) {
                temp_r31->motWork.time = temp_r31->motWork.end;
            }
        }
    }
    if (temp_r31->motIdOvl != -1) {
        temp_r27 = &Hu3DMotion[temp_r31->motIdOvl];
        temp_r29 = temp_r27->unk_04->motion;
        if (!(temp_r28 & HU3D_MOTATTR_OVL_PAUSE)) {
            if (!(temp_r28 & HU3D_MOTATTR_OVL_REV)) {
                temp_r31->motOvlWork.time += temp_r31->motOvlWork.speed * minimumVcountf;
            } else {
                temp_r31->motOvlWork.time -= temp_r31->motOvlWork.speed * minimumVcountf;
            }
            if (temp_r28 & HU3D_MOTATTR_OVL_LOOP) {
                if (temp_r31->motOvlWork.time < 0.0f) {
                    temp_r31->motOvlWork.time = temp_r29->maxTime;
                } else if (temp_r31->motOvlWork.time >= temp_r29->maxTime) {
                    temp_r31->motOvlWork.time = 0.0f;
                }
            } else if (temp_r31->motOvlWork.time < 0.0f) {
                temp_r31->motOvlWork.time = 0.0f;
            } else if (temp_r31->motOvlWork.time >= temp_r29->maxTime) {
                temp_r31->motOvlWork.time = temp_r29->maxTime;
            }
        }
    }
    if (temp_r31->motIdShift != -1) {
        temp_r31->motOvlWork.start += minimumVcountf;
        if (temp_r31->motOvlWork.start >= temp_r31->motOvlWork.end) {
            temp_r31->motId = temp_r31->motIdShift;
            temp_r31->motWork.time = temp_r31->motShiftWork.time;
            temp_r31->motWork.speed = temp_r31->motShiftWork.speed;
            temp_r31->motWork.start = temp_r31->motShiftWork.start;
            temp_r31->motWork.end = temp_r31->motShiftWork.end;
            temp_r31->motIdShift = -1;
            temp_r28 = 0;
            if (temp_r31->motAttr & HU3D_MOTATTR_SHIFT_LOOP) {
                temp_r28 |= HU3D_MOTATTR_LOOP;
            }
            if (temp_r31->motAttr & HU3D_MOTATTR_SHIFT_PAUSE) {
                temp_r28 |= HU3D_MOTATTR_PAUSE;
            }
            if (temp_r31->motAttr & HU3D_MOTATTR_SHIFT_REV) {
                temp_r28 |= HU3D_MOTATTR_REV;
            }
            temp_r31->motAttr &= ~HU3D_MOTATTR_ALL;
            temp_r31->motAttr |= temp_r28;
            temp_r31->motAttr &= ~HU3D_MOTATTR;
            return;
        }
        if (!(temp_r31->motAttr & HU3D_MOTATTR_SHIFT_PAUSE)) {
            temp_r27 = &Hu3DMotion[temp_r31->motIdShift];
            if (!(temp_r31->motAttr & HU3D_MOTATTR_SHIFT_REV)) {
                temp_r31->motShiftWork.time += temp_r31->motShiftWork.speed * minimumVcountf;
            } else {
                temp_r31->motShiftWork.time -= temp_r31->motShiftWork.speed * minimumVcountf;
            }
            if (temp_r31->motAttr & HU3D_MOTATTR_SHIFT_LOOP) {
                if (temp_r31->motShiftWork.time < temp_r31->motShiftWork.start) {
                    temp_r31->motShiftWork.time = temp_r31->motShiftWork.end;
                } else if (temp_r31->motShiftWork.time >= temp_r31->motShiftWork.end) {
                    temp_r31->motShiftWork.time = temp_r31->motShiftWork.start;
                }
            } else if (temp_r31->motShiftWork.time < temp_r31->motShiftWork.start) {
                temp_r31->motShiftWork.time = temp_r31->motShiftWork.start;
            } else if (temp_r31->motShiftWork.time >= temp_r31->motShiftWork.end) {
                temp_r31->motShiftWork.time = temp_r31->motShiftWork.end;
            }
        }
    }
    if (temp_r31->motIdShape != -1 && !(temp_r28 & HU3D_MOTATTR_SHAPE_PAUSE)) {
        temp_r27 = &Hu3DMotion[temp_r31->motIdShape];
        temp_r29 = temp_r27->unk_04->motion;
        if (!(temp_r28 & HU3D_MOTATTR_SHAPE_REV)) {
            temp_r31->motShapeWork.time += temp_r31->motShapeWork.speed * minimumVcountf;
        } else {
            temp_r31->motShapeWork.time -= temp_r31->motShapeWork.speed * minimumVcountf;
        }
        if (temp_r28 & HU3D_MOTATTR_SHAPE_LOOP) {
            if (temp_r31->motShapeWork.time < temp_r31->motShapeWork.start) {
                temp_r31->motShapeWork.time = temp_r31->motShapeWork.end;
            } else if (temp_r31->motShapeWork.time >= temp_r31->motShapeWork.end) {
                temp_r31->motShapeWork.time = temp_r31->motShapeWork.start;
            }
        } else if (temp_r31->motShapeWork.time < temp_r31->motShapeWork.start) {
            temp_r31->motShapeWork.time = temp_r31->motShapeWork.start;
        } else if (temp_r31->motShapeWork.time >= temp_r31->motShapeWork.end) {
            temp_r31->motShapeWork.time = temp_r31->motShapeWork.end;
        }
    }
    if (temp_r31->attr & HU3D_ATTR_CLUSTER_ON) {
        for (i = 0; i < 4; i++) {
            if (temp_r31->motIdCluster[i] != -1 && !(temp_r31->clusterAttr[i] & HU3D_CLUSTER_ATTR_PAUSE)) {
                temp_r27 = &Hu3DMotion[temp_r31->motIdCluster[i]];
                temp_r29 = temp_r27->unk_04->motion;
                if (!(temp_r31->clusterAttr[i] & HU3D_CLUSTER_ATTR_REV)) {
                    temp_r31->clusterTime[i] += temp_r31->clusterSpeed[i] * minimumVcountf;
                } else {
                    temp_r31->clusterTime[i] -= temp_r31->clusterSpeed[i] * minimumVcountf;
                }
                if (temp_r31->clusterAttr[i] & HU3D_CLUSTER_ATTR_LOOP) {
                    if (temp_r31->clusterTime[i] < 0.0f) {
                        temp_r31->clusterTime[i] = temp_r29->maxTime;
                    } else if (temp_r31->clusterTime[i] >= temp_r29->maxTime) {
                        temp_r31->clusterTime[i] = 0.0f;
                    }
                } else if (temp_r31->clusterTime[i] < 0.0f) {
                    temp_r31->clusterTime[i] = 0.0f;
                } else if (temp_r31->clusterTime[i] >= temp_r29->maxTime) {
                    temp_r31->clusterTime[i] = temp_r29->maxTime;
                }
            }
        }
    }
}

void Hu3DMotionExec(s16 arg0, s16 arg1, float arg2, s32 arg3) {
    MotionData *sp18;
    HSFDATA *sp14;
    HSFTRACK *sp10;
    HsfConstData *temp_r28;
    HSFDATA *temp_r29;
    HSFMOTION *temp_r21;
    HSFOBJECT *temp_r31;
    HSFOBJECT *var_r19;
    HSFCLUSTER *var_r23;
    HSFTRACK *var_r30;
    HSFTRACK *temp_r25;
    HSFTRACK *temp_r22;
    HSFTRACK *var_r26;
    HU3DMODEL *temp_r27;
    s16 temp_r24;
    s16 var_r18;
    float *temp_r17;

    temp_r27 = &Hu3DData[arg0];
    sp18 = &Hu3DMotion[arg1];
    temp_r29 = temp_r27->hsf;
    sp14 = sp18->unk_04;
    temp_r21 = sp14->motion;
    var_r30 = temp_r21->track;
    var_r19 = temp_r29->object;
    if (arg3 == 0) {
        for (var_r18 = 0; var_r18 < temp_r29->objectNum; var_r19++, var_r18++) {
            temp_r31 = var_r19;
            if (temp_r31->constData) {
                temp_r28 = temp_r31->constData;
                if (temp_r28->flags & 0x3F0) {
                    temp_r24 = temp_r28->flags;
                    if (!(temp_r24 & 0x10)) {
                        temp_r31->mesh.curr.pos.x = temp_r31->mesh.base.pos.x;
                    }
                    if (!(temp_r24 & 0x20)) {
                        temp_r31->mesh.curr.pos.y = temp_r31->mesh.base.pos.y;
                    }
                    if (!(temp_r24 & 0x40)) {
                        temp_r31->mesh.curr.pos.z = temp_r31->mesh.base.pos.z;
                    }
                    if (!(temp_r24 & 0x80)) {
                        temp_r31->mesh.curr.rot.x = temp_r31->mesh.base.rot.x;
                    }
                    if (!(temp_r24 & 0x100)) {
                        temp_r31->mesh.curr.rot.y = temp_r31->mesh.base.rot.y;
                    }
                    if (!(temp_r24 & 0x200)) {
                        temp_r31->mesh.curr.rot.z = temp_r31->mesh.base.rot.z;
                    }
                } else {
                    temp_r31->mesh.curr = temp_r31->mesh.base;
                }
            } else {
                temp_r31->mesh.curr = temp_r31->mesh.base;
            }
        }
    }
    sp10 = &var_r30[temp_r21->numTracks];
    for (; var_r30 < sp10; var_r30++) {
        switch (var_r30->type) {
            case 2:
                if (var_r30->target < temp_r29->objectNum && var_r30->target != -1) {
                    temp_r31 = &temp_r29->object[var_r30->target];
                    if (var_r30->channel == 0x28) {
                        temp_r31->mesh.mesh.baseMorph = GetCurve(var_r30, arg2);
                    } else if (temp_r31->type == 7) {
                        if (temp_r27->attr & HU3D_ATTR_CAMERA_MOTON) {
                            SetObjCameraMotion(arg0, var_r30, GetCurve(var_r30, arg2));
                        }
                    } else if (temp_r31->type == 8) {
                        SetObjLightMotion(arg0, var_r30, GetCurve(var_r30, arg2));
                    } else if (var_r30->channel == 0x18) {
                        if (temp_r31->constData) {
                            temp_r28 = temp_r31->constData;
                            if (GetCurve(var_r30, arg2) == 1.0f) {
                                temp_r28->flags &= ~0x1000;
                            } else {
                                temp_r28->flags |= 0x1000;
                            }
                        }
                    } else if (var_r30->channel == 0x1A) {
                        if (temp_r31->constData) {
                            temp_r28 = temp_r31->constData;
                            if (GetCurve(var_r30, arg2) == 1.0f) {
                                temp_r28->flags &= ~0x2000;
                            } else {
                                temp_r28->flags |= 0x2000;
                            }
                        }
                    } else {
                        temp_r17 = GetObjTRXPtr(temp_r31, var_r30->channel);
                        if (temp_r17 != (float*) -1) {
                            *temp_r17 = GetCurve(var_r30, arg2);
                        }
                    }
                }
                break;
            case 3:
                temp_r25 = var_r30;
                if (temp_r25->target < temp_r29->objectNum) {
                    temp_r31 = &temp_r29->object[temp_r25->target];
                    temp_r31->mesh.mesh.morphWeight[temp_r25->morphWeight] = GetCurve(temp_r25, arg2);
                }
                break;
            case 9:
                if (!(temp_r27->attr & HU3D_ATTR_CURVE_MOTOFF)) {
                    if (var_r30->attrIdx < temp_r29->materialNum) {
                        SetObjMatMotion(arg0, var_r30, GetCurve(var_r30, arg2));
                    }
                }
                break;
            case 5:
                if (!(temp_r27->attr & HU3D_ATTR_CURVE_MOTOFF)) {
                    var_r23 = &temp_r29->cluster[var_r30->cluster];
                    var_r23->index = GetClusterCurve(var_r30, arg2);
                }
                break;
            case 6:
                if (!(temp_r27->attr & HU3D_ATTR_CURVE_MOTOFF)) {
                    temp_r22 = var_r30;
                    var_r23 = &temp_r29->cluster[temp_r22->cluster];
                    var_r23->weight[temp_r22->clusterWeight] = GetClusterWeightCurve(temp_r22, arg2);
                }
                break;
            case 10:
                var_r26 = var_r30;
                if (var_r26->cluster != -1 || !(temp_r27->attr & HU3D_ATTR_CURVE_MOTOFF)) {
                    if (var_r26->attrIdx != -1 && var_r26->attrIdx < temp_r29->attributeNum) {
                        SetObjAttrMotion(arg0, var_r26, GetCurve(var_r26, arg2));
                    }
                }
                break;
        }
    }
}

void Hu3DCameraMotionExec(s16 arg0) {
    HU3DMODEL *temp_r30;
    MotionData *temp_r28;
    HSFDATA *temp_r27;
    HSFMOTION *temp_r29;
    HSFTRACK *var_r31;
    HSFTRACK *temp_r26;

    temp_r30 = &Hu3DData[arg0];
    temp_r28 = &Hu3DMotion[temp_r30->motId];
    temp_r27 = temp_r28->unk_04;
    temp_r29 = temp_r27->motion;
    var_r31 = temp_r29->track;
    if (temp_r30->attr & HU3D_ATTR_CAMERA_MOTON) {
        temp_r26 = &var_r31[temp_r29->numTracks];
        for (; var_r31 < temp_r26; var_r31++) {
            if (var_r31->type == 2 && var_r31->index == 7) {
                SetObjCameraMotion(arg0, var_r31, GetCurve(var_r31, temp_r30->motWork.time));
            }
        }
    }
}

void Hu3DSubMotionExec(s16 arg0) {
    HU3DMODEL *temp_r30;
    MotionData *temp_r22;
    HSFDATA *temp_r28;
    HSFDATA *temp_r21;
    HSFMOTION *temp_r25;
    HSFTRACK *var_r29;
    HSFOBJECT *var_r23;
    HSFOBJECT *temp_r26;
    float *temp_r31;
    float var_f30;
    float var_f31;
    s16 temp_r24;
    s16 var_r27;

    temp_r30 = &Hu3DData[arg0];
    temp_r22 = &Hu3DMotion[temp_r30->motIdShift];
    temp_r28 = temp_r30->hsf;
    temp_r21 = temp_r22->unk_04;
    temp_r25 = temp_r21->motion;
    var_r29 = temp_r25->track;
    var_r23 = temp_r28->object;
    if (temp_r30->motId == -1) {
        for (var_r27 = 0; var_r27 < temp_r28->objectNum; var_r23++, var_r27++) {
            temp_r26 = var_r23;
            temp_r26->mesh.curr = temp_r26->mesh.base;
        }
    }
    if (temp_r30->motOvlWork.end) {
        var_f30 = temp_r30->motOvlWork.start / temp_r30->motOvlWork.end;
    } else {
        var_f30 = 1.0f;
    }
    for (var_r27 = 0; var_r27 < temp_r25->numTracks; var_r27++, var_r29++) {
        switch (var_r29->type) {
            case 2:
                if (var_r29->target < temp_r28->objectNum && var_r29->target != -1) {
                    temp_r26 = &temp_r28->object[var_r29->target];
                    temp_r24 = var_r29->channel;
                    temp_r31 = GetObjTRXPtr(temp_r26, temp_r24);
                    if (temp_r31 != (float*) -1) {
                        if (temp_r24 == 0x1C || temp_r24 == 0x1D || temp_r24 == 0x1E) {
                            var_f31 = GetCurve(var_r29, temp_r30->motShiftWork.time);
                            if (var_f31 < 0.0f) {
                                var_f31 += 360.0f;
                            }
                            if (*temp_r31 < 0.0f) {
                                *temp_r31 += 360.0f;
                            }
                            if (var_f31 < 180.0f) {
                                if (*temp_r31 > (180.0f + var_f31)) {
                                    *temp_r31 -= 360.0f;
                                }
                            } else if (*temp_r31 < (var_f31 - 180.0f)) {
                                var_f31 -= 360.0f;
                            }
                            *temp_r31 = (1.0f - var_f30) * *temp_r31 + var_f30 * var_f31;
                        } else {
                            *temp_r31 = (1.0f - var_f30) * *temp_r31 + var_f30 * GetCurve(var_r29, temp_r30->motShiftWork.time);
                        }
                    }
                }
                break;
        }
    }
}

__declspec(weak) float *GetObjTRXPtr(HSFOBJECT *arg0, u16 arg1) {
    HsfConstData *temp_r31 = arg0->constData;

    switch (arg1) {
        case 8:
            if (temp_r31 && (temp_r31->flags & 0x10)) {
                return (float*) -1;
            }
            return &arg0->mesh.curr.pos.x;
        case 9:
            if (temp_r31 && (temp_r31->flags & 0x20)) {
                return (float*) -1;
            }
            return &arg0->mesh.curr.pos.y;
        case 10:
            if (temp_r31 && (temp_r31->flags & 0x40)) {
                return (float*) -1;
            }
            return &arg0->mesh.curr.pos.z;
        case 28:
            if (temp_r31 && (temp_r31->flags & 0x80)) {
                return (float*) -1;
            }
            return &arg0->mesh.curr.rot.x;
        case 29:
            if (temp_r31 && (temp_r31->flags & 0x100)) {
                return (float*) -1;
            }
            return &arg0->mesh.curr.rot.y;
        case 30:
            if (temp_r31 && (temp_r31->flags & 0x200)) {
                return (float*) -1;
            }
            return &arg0->mesh.curr.rot.z;
        case 31:
            return &arg0->mesh.curr.scale.x;
        case 32:
            return &arg0->mesh.curr.scale.y;
        case 33:
            return &arg0->mesh.curr.scale.z;
        default:
            return (float*) -1;
    }
}

void SetObjMatMotion(s16 arg0, HSFTRACK *arg1, float arg2) {
    HSFMATERIAL *temp_r31;
    HSFDATA *temp_r29;
    HU3DMODEL *temp_r30;
    float var_f31;

    temp_r30 = &Hu3DData[arg0];
    temp_r29 = temp_r30->hsf;
    temp_r31 = &temp_r29->material[arg1->attrIdx];
    var_f31 = arg2;
    if (arg2 > 1.0f) {
        var_f31 = 1.0f;
    } else if (arg2 < 0.0f) {
        var_f31 = 0.0f;
    }
    switch (arg1->channel) {
        case 0:
            temp_r31->litColor[0] = var_f31 * 255.0f;
            break;
        case 1:
            temp_r31->litColor[1] = var_f31 * 255.0f;
            break;
        case 2:
            temp_r31->litColor[2] = var_f31 * 255.0f;
            break;
        case 0x31:
            temp_r31->color[0] = var_f31 * 255.0f;
            break;
        case 0x32:
            temp_r31->color[1] = var_f31 * 255.0f;
            break;
        case 0x33:
            temp_r31->color[2] = var_f31 * 255.0f;
            break;
        case 0x34:
            temp_r31->shadowColor[0] = var_f31 * 255.0f;
            break;
        case 0x35:
            temp_r31->shadowColor[1] = var_f31 * 255.0f;
            break;
        case 0x36:
            temp_r31->shadowColor[2] = var_f31 * 255.0f;
            break;
        case 0x39:
            if (!(temp_r30->attr & HU3D_ATTR_TPLVL_SET)) {
                temp_r31->invAlpha = var_f31;
            }
            break;
        case 0x3C:
            temp_r31->refAlpha = var_f31;
            break;
    }
}

void SetObjAttrMotion(s16 arg0, HSFTRACK *arg1, float arg2) {
    HU3DMODEL *temp_r28;
    HSFDATA *temp_r27;
    HSFATTRIBUTE *temp_r30;
    HsfdrawStruct01 *var_r31;
    float var_f30;

    temp_r28 = &Hu3DData[arg0];
    temp_r27 = temp_r28->hsf;
    temp_r30 = &temp_r27->attribute[arg1->attrIdx];
    var_f30 = arg2;
    if (arg2 > 1.0f) {
        var_f30 = 1.0f;
    } else if (arg2 < 0.0f) {
        var_f30 = 0.0f;
    }
    switch (arg1->channel) {
        case 8:
        case 9:
        case 0xA:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        case 0x43:
            if (temp_r30->animWorkP == 0) {
                var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(HsfdrawStruct01), (u32) Hu3DData[arg0].mallocNo);
                temp_r30->animWorkP = var_r31;
                var_r31->unk00 = 0;
                var_r31->unk08 = var_r31->unk0C = var_r31->unk10 = 0.0f;
                var_r31->unk14 = var_r31->unk18 = var_r31->unk1C = 0.0f;
                var_r31->unk20 = var_r31->unk24 = var_r31->unk28 = 1.0f;
            } else {
                var_r31 = temp_r30->animWorkP;
            }
            if (arg1->channel != 0x43) {
                var_r31->unk00 |= 4;
            } else {
                var_r31->unk00 |= 8;
            }
            break;
    }
    switch (arg1->channel) {
        case 8:
            var_r31->unk08 = arg2;
            break;
        case 9:
            var_r31->unk0C = arg2;
            break;
        case 10:
            var_r31->unk10 = arg2;
            break;
        case 28:
            var_r31->unk14 = arg2;
            break;
        case 29:
            var_r31->unk18 = arg2;
            break;
        case 30:
            var_r31->unk1C = arg2;
            break;
        case 31:
            var_r31->unk20 = arg2;
            break;
        case 32:
            var_r31->unk24 = arg2;
            break;
        case 33:
            var_r31->unk28 = arg2;
            break;
        case 64:
            temp_r30->unk20 = var_f30;
            break;
        case 62:
            temp_r30->kColor = var_f30;
            break;
        case 63:
            temp_r30->nbtTpLvl = arg2;
            break;
        case 67:
            var_r31->unk3C = bitMapPtr;
            break;
    }
}

void SetObjCameraMotion(s16 arg0, HSFTRACK *arg1, float arg2) {
    HU3DMODEL *temp_r29;
    Vec sp18;
    Vec spC;
    float var_f31;
    float var_f30;
    s16 var_r30;
    s16 temp_r28;
    s16 i;

    temp_r29 = &Hu3DData[arg0];
    temp_r28 = temp_r29->camInfoBit;
    if (temp_r28 != 0) {
        var_f31 = arg2;
        if (arg2 > 1.0f) {
            var_f31 = 1.0f;
        } else if (arg2 < 0.0f) {
            var_f31 = 0.0f;
        }
        switch (arg1->channel) {
            case 8:
                var_f30 = temp_r29->scale.x * (arg2 + temp_r29->pos.x);
                for (i = 0, var_r30 = 1; i < HU3D_CAM_MAX; i++, var_r30 <<= 1) {
                    if (var_r30 & temp_r28) {
                        Hu3DCamera[i].pos.x = var_f30;
                    }
                }
                break;
            case 9:
                var_f30 = temp_r29->scale.y * (arg2 + temp_r29->pos.y);
                for (i = 0, var_r30 = 1; i < HU3D_CAM_MAX; i++, var_r30 <<= 1) {
                    if (var_r30 & temp_r28) {
                        Hu3DCamera[i].pos.y = var_f30;
                    }
                }
                break;
            case 10:
                var_f30 = temp_r29->scale.z * (arg2 + temp_r29->pos.z);
                for (i = 0, var_r30 = 1; i < HU3D_CAM_MAX; i++, var_r30 <<= 1) {
                    if (var_r30 & temp_r28) {
                        Hu3DCamera[i].pos.z = var_f30;
                    }
                }
                break;
            case 11:
                var_f30 = temp_r29->scale.x * (arg2 + temp_r29->pos.x);
                for (i = 0, var_r30 = 1; i < HU3D_CAM_MAX; i++, var_r30 <<= 1) {
                    if (var_r30 & temp_r28) {
                        Hu3DCamera[i].target.x = var_f30;
                    }
                }
                break;
            case 12:
                var_f30 = temp_r29->scale.y * (arg2 + temp_r29->pos.y);
                for (i = 0, var_r30 = 1; i < HU3D_CAM_MAX; i++, var_r30 <<= 1) {
                    if (var_r30 & temp_r28) {
                        Hu3DCamera[i].target.y = var_f30;
                    }
                }
                break;
            case 13:
                var_f30 = temp_r29->scale.z * (arg2 + temp_r29->pos.z);
                for (i = 0, var_r30 = 1; i < HU3D_CAM_MAX; i++, var_r30 <<= 1) {
                    if (var_r30 & temp_r28) {
                        Hu3DCamera[i].target.z = var_f30;
                    }
                }
                break;
            case 14:
                for (i = 0, var_r30 = 1; i < HU3D_CAM_MAX; i++, var_r30 <<= 1) {
                    if (var_r30 & temp_r28) {
                        VECSubtract(&Hu3DCamera[i].pos, &Hu3DCamera[i].target, &spC);
                        VECNormalize(&spC, &spC);
                        sp18.x = spC.x * spC.y * (1.0 - cosd(arg2)) - spC.z * sind(arg2);
                        sp18.y = spC.y * spC.y + (1.0f - spC.y * spC.y) * cosd(arg2);
                        sp18.z = spC.y * spC.z * (1.0 - cosd(arg2)) + spC.x * sind(arg2);
                        VECNormalize(&sp18, &Hu3DCamera[i].up);
                        Hu3DCamera[i].upRot = arg2;
                    }
                }
                break;
            case 15:
                for (i = 0, var_r30 = 1; i < HU3D_CAM_MAX; i++, var_r30 <<= 1) {
                    if (var_r30 & temp_r28) {
                        Hu3DCamera[i].fov = arg2;
                    }
                }
                break;
        }
    }
}

void SetObjLightMotion(s16 arg0, HSFTRACK *arg1, float arg2) {
    s16 var_r29;
    HU3DMODEL *temp_r30;
    HSFDATA *temp_r28;
    HSFOBJECT *var_r26;
    HSFOBJECT *var_r24;
    HU3DLIGHT *temp_r31;
    float var_f30;
    s16 i;

    temp_r30 = &Hu3DData[arg0];
    temp_r28 = temp_r30->hsf;
    var_r26 = temp_r28->object;
    for (i = var_r29 = 0; i < temp_r28->objectNum; i++, var_r26++) {
        var_r24 = var_r26;
        if (var_r24->type == 8) {
            if (i != arg1->target) {
                var_r29++;
            } else {
                break;
            }
        }
    }
    if (i != temp_r28->objectNum) {
        temp_r31 = &Hu3DGlobalLight[temp_r30->lightId[var_r29]];
        var_f30 = arg2;
        if (arg2 > 1.0f) {
            var_f30 = 1.0f;
        } else if (arg2 < 0.0f) {
            var_f30 = 0.0f;
        }
        switch (arg1->channel) {
            case 8:
                temp_r31->pos.x = arg2;
                break;
            case 9:
                temp_r31->pos.y = arg2;
                break;
            case 10:
                temp_r31->pos.z = arg2;
                break;
            case 11:
                temp_r31->unk_34.x = arg2;
                Hu3DGLightPosAimSetV(temp_r30->lightId[var_r29], &temp_r31->pos, &temp_r31->unk_34);
                break;
            case 12:
                temp_r31->unk_34.y = arg2;
                Hu3DGLightPosAimSetV(temp_r30->lightId[var_r29], &temp_r31->pos, &temp_r31->unk_34);
                break;
            case 13:
                temp_r31->unk_34.z = arg2;
                Hu3DGLightPosAimSetV(temp_r30->lightId[var_r29], &temp_r31->pos, &temp_r31->unk_34);
                break;
        }
    }
}

float GetCurve(HSFTRACK *arg0, float arg1) {
    float *var_r30;

    switch (arg0->curveType) {
        case 1:
            return GetLinear(arg0->numKeyframes, arg0->data, arg1);
        case 2:
            return GetBezier(arg0->numKeyframes, arg0, arg1);
        case 3:
            bitMapPtr = GetBitMap(arg0->numKeyframes, arg0->data, arg1);
            break;
        case 4:
            var_r30 = &arg0->value;
            return *var_r30;
        case 0:
            return GetConstant(arg0->numKeyframes, arg0->data, arg1);
    }
    return 0.0f;
}

float GetConstant(s32 arg0, float *arg1, float arg2) {
    float *var_r31;
    s16 i;

    var_r31 = arg1;
    if (arg2 == 0.0f || arg0 == 1) {
        return arg1[1];
    }
    for (i = 0; i < arg0; i++, var_r31 += 2) {
        if (arg2 < var_r31[0]) {
            return var_r31[-1];
        }
    }
    return var_r31[-1];
}

float GetLinear(s32 arg0, float arg1[][2], float arg2) {
    float var_f31;
    float var_f30;
    s16 temp_r30;
    s16 var_r31;

    if (arg2 == 0.0f || arg0 == 1) {
        return arg1[0][1];
    }
    for (var_r31 = 0; var_r31 < arg0; var_r31++) {
        if (arg2 < arg1[var_r31][0]) {
            temp_r30 = var_r31 - 1;
            var_f30 = arg1[var_r31][0] - arg1[temp_r30][0];
            var_f31 = arg1[temp_r30][1] + (arg2 - arg1[temp_r30][0]) * ((arg1[var_r31][1] - arg1[temp_r30][1]) / var_f30);
            return var_f31;
        }
    }
    return arg1[arg0 - 1][1];
}

__declspec(weak) float GetBezier(s32 arg0, HSFTRACK *arg1, float arg2) {
    float temp_f24;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    float temp_f30;
    float temp_f31;
    float (*var_r31)[4];
    float (*var_r29)[4];
    s32 i;

    var_r31 = arg1->data;
    if (arg2 == 0.0f || arg0 == 1) {
        return var_r31[0][1];
    }
    i = -1;
    if (arg1->start == 0 && arg2 < var_r31[0][0]) {
        i = 0;
    }
    if (i == -1) {
        var_r31 = (float(*)[4]) arg1->data + arg1->start;
        var_r29 = var_r31 - 1;
        for (i = arg1->start; i < arg0; i++, var_r31++) {
            if (arg2 >= var_r29[0][0] && arg2 < var_r31[0][0]) {
                break;
            }
            var_r29 = var_r31;
        }
        if (i >= arg0) {
            var_r31 = arg1->data;
            for (i = 0; i < arg0; i++, var_r31++) {
                if (arg2 < var_r31[0][0]) {
                    break;
                }
            }
        }
    }
    arg1->start = i;
    if (i == arg0) {
        return var_r31[-1][1];
    }
    temp_f24 = var_r31[0][0];
    var_r31--;
    temp_f29 = var_r31[0][0];
    temp_f31 = (arg2 - temp_f29) / (temp_f24 - temp_f29);
    temp_f30 = temp_f31 * temp_f31;
    temp_f28 = 2.0f * temp_f30;
    temp_f27 = 3.0f * temp_f30;
    temp_f26 = temp_f31 * temp_f30;
    temp_f25 = temp_f31 * temp_f28;
    return var_r31[0][1] * (temp_f25 - temp_f27 + 1.0f)
        + var_r31[1][1] * (-temp_f25 + temp_f27)
        + var_r31[0][2] * (temp_f26 - temp_f28 + temp_f31)
        + var_r31[1][3] * (temp_f26 - temp_f30);
}

HSFBITMAP *GetBitMap(s32 arg0, UnknownHsfMotionStruct01 *arg1, float arg2) {
    s16 var_r31;

    if (arg2 == 0.0f || arg0 == 1) {
        return arg1->unk04;
    }
    for (var_r31 = 0; var_r31 < arg0; var_r31++, arg1++) {
        if (arg2 < arg1->unk00 * 60.0f) {
            break;
        }
    }
    return arg1[-1].unk04;
}

s16 Hu3DJointMotion(s16 arg0, void *arg1) {
    s16 var_r29;

    var_r29 = Hu3DMotionCreate(arg1);
    JointModel_Motion(arg0, var_r29);
    return var_r29;
}

void JointModel_Motion(s16 arg0, s16 arg1) {
    HU3DMODEL *temp_r24;
    MotionData *temp_r23;
    HSFDATA *temp_r26;
    HSFDATA *temp_r22;
    HSFMOTION *temp_r29;
    HSFTRACK *var_r30;
    HSFTRACK *var_r28;
    HSFTRACK *var_r27;
    HSFTRACK *var_r31;
    s32 temp_r21;
    s32 i;

    temp_r24 = &Hu3DData[arg0];
    temp_r23 = &Hu3DMotion[arg1];
    temp_r26 = temp_r24->hsf;
    temp_r22 = temp_r23->unk_04;
    temp_r29 = temp_r22->motion;
    var_r30 = temp_r29->track;
    for (i = 0; i < temp_r29->numTracks; i++, var_r30++) {
        switch (var_r30->type) {
            case 2:
                var_r28 = var_r30;
                var_r28->target = SearchObjectIndex(temp_r26, var_r28->target);
                break;
            case 3:
                var_r27 = var_r30;
                var_r27->target = SearchObjectIndex(temp_r26, var_r27->target);
                break;
            case 10:
                var_r31 = var_r30;
                if (var_r31->attrIdx == -1) {
                    temp_r21 = SearchAttributeIndex(temp_r26, var_r31->cluster);
                    if (temp_r21 != -1) {
                        var_r31->attrIdx = temp_r21;
                    } else {
                        var_r31->attrIdx = -1;
                    }
                }
                break;
        }
    }
}

void Hu3DMotionCalc(s16 arg0) {
    HU3DMODEL *temp_r31 = &Hu3DData[arg0];

    if ((temp_r31->attr & HU3D_ATTR_DISPOFF) || (temp_r31->attr & HU3D_ATTR_HOOK)) {
        return;
    }
    if (temp_r31->motId != -1) {
        Hu3DMotionExec(arg0, temp_r31->motId, temp_r31->motWork.time, 0);
    }
    if (temp_r31->motIdShift != -1) {
        Hu3DSubMotionExec(arg0);
    }
    if (temp_r31->motIdOvl != -1) {
        Hu3DMotionExec(arg0, temp_r31->motIdOvl, temp_r31->motOvlWork.time, 1);
    }
    if (temp_r31->attr & HU3D_ATTR_CLUSTER_ON) {
        ClusterMotionExec(temp_r31);
    }
    if (temp_r31->motIdShape != -1) {
        if (temp_r31->motId == -1) {
            Hu3DMotionExec(arg0, temp_r31->motIdShape, temp_r31->motShapeWork.time, 0);
        } else {
            Hu3DMotionExec(arg0, temp_r31->motIdShape, temp_r31->motShapeWork.time, 1);
        }
    }
    if (!(temp_r31->attr & (HU3D_ATTR_ENVELOPE_OFF|HU3D_ATTR_HOOKFUNC)) || !(temp_r31->motAttr & HU3D_MOTATTR_PAUSE)) {
        InitVtxParm(temp_r31->hsf);
        if (temp_r31->motIdShape != -1) {
            ShapeProc(temp_r31->hsf);
        }
        if (temp_r31->attr & HU3D_ATTR_CLUSTER_ON) {
            ClusterProc(temp_r31);
        }
        if (temp_r31->hsf->cenvNum != 0) {
            EnvelopeProc(temp_r31->hsf);
        }
        PPCSync();
    }
    temp_r31->attr |= HU3D_ATTR_MOT_EXEC;
}

static s32 SearchObjectIndex(HSFDATA *arg0, u32 arg1) {
    s32 i;
    char *temp_r28;
    HSFOBJECT *var_r30;

    var_r30 = arg0->object;
    temp_r28 = SetName(&arg1);
    for (i = 0; i < arg0->objectNum; i++, var_r30++) {
        if (CmpObjectName(var_r30->name, temp_r28) == 0) {
            return i;
        }
    }
    return -1;
}

static s32 SearchAttributeIndex(HSFDATA *arg0, u32 arg1) {
    HSFATTRIBUTE *var_r31;
    size_t temp_r28;
    char *temp_r27;
    s32 i;

    var_r31 = arg0->attribute;
    temp_r27 = SetName(&arg1);
    for (i = 0; i < arg0->attributeNum; i++, var_r31++) {
        if (var_r31->name) {
            temp_r28 = strlen(var_r31->name);
            if (strncmp(var_r31->name, temp_r27, temp_r28) == 0) {
                return i;
            }
        }
    }
    return -1;
}
