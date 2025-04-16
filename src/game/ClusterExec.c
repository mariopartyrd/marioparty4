#include "game/ClusterExec.h"
#include "game/EnvelopeExec.h"
#include "game/hsfmotion.h"
#include "game/sprite.h"

float GetClusterCurve(HsfTrack *arg0, float arg1)
{
    float *var_r30;

    switch (arg0->curveType) {
        case 1:
            return GetLinear(arg0->numKeyframes, arg0->data, arg1);
        case 2:
            return GetBezier(arg0->numKeyframes, arg0, arg1);
        case 4:
            var_r30 = &arg0->value;
            return *var_r30;
    }
    return 0.0f;
}

float GetClusterWeightCurve(HsfTrack *arg0, float arg1)
{
    float *var_r30;

    switch (arg0->curveType) {
        case 1:
            return GetLinear(arg0->numKeyframes, arg0->data, arg1);
        case 2:
            return GetBezier(arg0->numKeyframes, arg0, arg1);
        case 4:
            var_r30 = &arg0->value;
            return *var_r30;
    }
    return 0.0f;
}

void SetClusterMain(HsfCluster *arg0)
{
    float var_f30;
    float var_f31;
    s32 temp_r24;
    s32 temp_r29;
    u16 *var_r28;
    s32 var_r23;
    s32 i;
    s32 j;
    HsfBuffer *temp_r25;
    HsfPart *temp_r27;
    HsfBuffer *temp_r30;

    temp_r27 = arg0->part;
    if (arg0->vertexCnt != 0) {
        if (arg0->type == 2) {
            var_r28 = temp_r27->vertex;
            temp_r30 = *arg0->vertex;
            var_f30 = 0.0f;
            for (i = 0; i < arg0->vertexCnt; i++) {
                var_f30 += arg0->weight[i];
            }
            for (i = 0; i < temp_r27->count; i++, var_r28++) {
                temp_r29 = *var_r28;
                Vertextop[temp_r29].x = ((Vec *)temp_r30->data)[i].x;
                Vertextop[temp_r29].y = ((Vec *)temp_r30->data)[i].y;
                Vertextop[temp_r29].z = ((Vec *)temp_r30->data)[i].z;
            }
            for (i = 1; i < arg0->vertexCnt; i++) {
                temp_r30 = arg0->vertex[i];
                var_r28 = temp_r27->vertex;
                var_f31 = arg0->weight[i];
                if (var_f31 < 0.0f) {
                    var_f31 = 0.0f;
                }
                else if (var_f30 > 1.0f) {
                    var_f31 /= var_f30;
                }
                for (j = 0; j < temp_r27->count; j++, var_r28++) {
                    temp_r29 = *var_r28;
                    Vertextop[temp_r29].x += var_f31 * (((Vec *)temp_r30->data)[j].x - Vertextop[temp_r29].x);
                    Vertextop[temp_r29].y += var_f31 * (((Vec *)temp_r30->data)[j].y - Vertextop[temp_r29].y);
                    Vertextop[temp_r29].z += var_f31 * (((Vec *)temp_r30->data)[j].z - Vertextop[temp_r29].z);
                }
            }
            return;
        }
        temp_r24 = arg0->index;
        var_r23 = temp_r24 + 1;
        if (var_r23 >= arg0->vertexCnt) {
            var_r23 = temp_r24;
        }
        var_f31 = arg0->index - temp_r24;
        temp_r30 = arg0->vertex[temp_r24];
        temp_r25 = arg0->vertex[var_r23];
        var_r28 = temp_r27->vertex;
        for (i = 0; i < temp_r27->count; i++, var_r28++) {
            temp_r29 = *var_r28;
            Vertextop[temp_r29].x = ((Vec *)temp_r30->data)[i].x + var_f31 * (((Vec *)temp_r25->data)[i].x - ((Vec *)temp_r30->data)[i].x);
            Vertextop[temp_r29].y = ((Vec *)temp_r30->data)[i].y + var_f31 * (((Vec *)temp_r25->data)[i].y - ((Vec *)temp_r30->data)[i].y);
            Vertextop[temp_r29].z = ((Vec *)temp_r30->data)[i].z + var_f31 * (((Vec *)temp_r25->data)[i].z - ((Vec *)temp_r30->data)[i].z);
        }
    }
}

void ClusterProc(ModelData *arg0)
{
    s32 temp_r24;
    s32 i;
    s32 j;
    s32 k;
    HsfData *temp_r27;
    HsfData *temp_r23;
    MotionData *temp_r22;
    HsfCluster *var_r29;
    HsfObject *temp_r31;

    for (i = 0; i < 4; i++) {
        temp_r24 = arg0->unk_10[i];
        if (temp_r24 != -1) {
            temp_r22 = &Hu3DMotion[temp_r24];
            temp_r27 = temp_r22->hsfData;
            temp_r23 = arg0->hsfData;
            var_r29 = temp_r27->cluster;
            for (j = 0; j < temp_r27->clusterCnt; j++, var_r29++) {
                if (var_r29->target != -1) {
                    temp_r31 = temp_r23->object;
                    temp_r31 += var_r29->target;
                    Vertextop = temp_r31->data.vertex->data;
                    if (temp_r31->data.cenvCnt) {
                        for (k = 0; k < temp_r31->data.vertex->count; k++) {
                            Vertextop[k].x = ((Vec *)temp_r31->data.vtxtop)[k].x;
                            Vertextop[k].y = ((Vec *)temp_r31->data.vtxtop)[k].y;
                            Vertextop[k].z = ((Vec *)temp_r31->data.vtxtop)[k].z;
                        }
                    }
                    SetClusterMain(var_r29);
                    DCStoreRangeNoSync(Vertextop, temp_r31->data.vertex->count * sizeof(Vec));
                    temp_r31->data.unk120[0]++;
                }
            }
        }
    }
}

void ClusterMotionExec(ModelData *arg0)
{
    float temp_f31;
    s32 i;
    s32 j;
    s16 var_r20;
    HsfCluster *temp_r26;
    HsfData *temp_r28;
    HsfMotion *temp_r27; // ! - uninitialized
    HsfTrack *var_r31;
    HsfTrack *var_r30;
    MotionData *var_r23;

#ifdef AVOID_UB
    //var_r31 = temp_r27->track;
#else
    var_r31 = temp_r27->track;
#endif
    for (i = 0; i < 4; i++) {
        if (arg0->unk_10[i] != -1) {
            var_r20 = arg0->unk_10[i];
            var_r23 = &Hu3DMotion[var_r20];
            temp_r28 = var_r23->hsfData;
            temp_r27 = temp_r28->motion;
            var_r31 = temp_r27->track;
            temp_f31 = arg0->unk_A4[i];
            for (j = 0; j < temp_r27->numTracks; j++, var_r31++) {
                switch (var_r31->type) {
                    case 5:
                        temp_r26 = &temp_r28->cluster[var_r31->target_s16];
                        temp_r26->index = GetClusterCurve(var_r31, temp_f31);
                        break;
                    case 6:
                        var_r30 = var_r31;
                        temp_r26 = &temp_r28->cluster[var_r30->target_s16];
                        temp_r26->weight[var_r30->unk04] = GetClusterCurve(var_r30, temp_f31);
                        break;
                }
            }
        }
    }
}
