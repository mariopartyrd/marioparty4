#ifndef _EXT_MATH_H
#define _EXT_MATH_H

#include "math.h"
#include "dolphin/mtx.h"

typedef struct vec2f {
    float x;
    float y;
} Vec2f;

#define ABS(x) (((x) < 0) ? -(x) : (x))
#define ABS_INV(x) (((x) >= 0) ? (x) : -(x))


#define VECDistanceXYZ(a, b) sqrtf((((a)->x-(b)->x)*((a)->x-(b)->x))+(((a)->y-(b)->y)*((a)->y-(b)->y))+(((a)->z-(b)->z)*((a)->z-(b)->z)))

#define VECDistanceXZ(a, b) sqrtf((((a)->x-(b)->x)*((a)->x-(b)->x))+(((a)->z-(b)->z)*((a)->z-(b)->z)))
#define VECDistanceZY(a, b) sqrtf((((a)->z-(b)->z)*((a)->z-(b)->z))+(((a)->y-(b)->y)*((a)->y-(b)->y)))
#define VECSumXZ(a, b) sqrtf((((a)->x+(b)->x)*((a)->x+(b)->x))+(((a)->z+(b)->z)*((a)->z+(b)->z)))

#define VECMagXYZ(a) sqrtf(((a)->x*(a)->x)+((a)->y*(a)->y)+((a)->z*(a)->z))
#define VECMagXZ(a) sqrtf(((a)->x*(a)->x)+((a)->z*(a)->z))
#define VECMagXY(a) sqrtf(((a)->x*(a)->x)+((a)->y*(a)->y))

#define VECMag2Point(a) (((a)->x*(a)->x)+((a)->y*(a)->y)+((a)->z*(a)->z))
#define VECMagPoint(x, y, z) sqrtf(((x)*(x))+((y)*(y))+((z)*(z)))
// #define sqrtDist3D(x, y, z) sqrtf(x * x + y * y + z * z)

#define sind(x) sin(M_PI*(x)/180.0)
#define cosd(x) cos(M_PI*(x)/180.0)
#define asind(x) (180.0*(asinf((x)) / M_PI))
#define atan2d(y, x) (180.0*(atan2((y), (x)) / M_PI))

#ifndef __MWERKS__
void HuSetVecF(Vec* arg0, f32 arg8, f32 arg9, f32 argA)
#endif

#endif
