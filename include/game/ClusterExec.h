#ifndef _GAME_CLUSTER_EXEC_H
#define _GAME_CLUSTER_EXEC_H

#include "game/hsfformat.h"
#include "game/hu3d.h"

float GetClusterCurve(HSFTRACK *arg0, float arg1);
float GetClusterWeightCurve(HSFTRACK *arg0, float arg1);
void SetClusterMain(HSFCLUSTER *arg0);
void ClusterProc(HU3DMODEL *arg0);
void ClusterMotionExec(HU3DMODEL *arg0);

#endif
