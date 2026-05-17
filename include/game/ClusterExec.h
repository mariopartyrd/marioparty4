#ifndef _GAME_CLUSTER_EXEC_H
#define _GAME_CLUSTER_EXEC_H

#include "game/hsfformat.h"
#include "game/hsfman.h"

float GetClusterCurve(HSFTRACK *arg0, float arg1);
float GetClusterWeightCurve(HSFTRACK *arg0, float arg1);
void SetClusterMain(HsfCluster *arg0);
void ClusterProc(ModelData *arg0);
void ClusterMotionExec(ModelData *arg0);

#endif
