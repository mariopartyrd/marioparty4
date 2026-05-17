#ifndef _GAME_MAPSPACE_H
#define _GAME_MAPSPACE_H

#include "game/hsfformat.h"
#include "game/object.h"

#include "dolphin.h"

void MapWall(float arg0, float arg1, float arg2, float arg3);
void MapWallCheck(float *arg0, float *arg1, HSFMAPATTR *arg2);
float MapPos(float arg0, float arg1, float arg2, float arg3, Vec *arg4);
BOOL Hitcheck_Triangle_with_Sphere(Vec *arg0, Vec *arg1, float arg2, Vec *arg3);
BOOL Hitcheck_Quadrangle_with_Sphere(Vec *arg0, Vec *arg1, float arg2, Vec *arg3);
void AppendAddXZ(float arg0, float arg1, float arg2);
void CharRotInv(Mtx arg0, Mtx arg1, Vec *arg2, omObjData *arg3);

extern Mtx MapMT;
extern Mtx MapMTR;
extern float AddX;
extern float AddZ;
extern s32 nMap;
extern s32 nChar;
extern s32 HitFaceCount;
extern omObjData *MapObject[16];

#endif
