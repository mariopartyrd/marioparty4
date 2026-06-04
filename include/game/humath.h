#ifndef _HU_MATH_H
#define _HU_MATH_H

#include "math.h"
#include "dolphin/mtx.h"

typedef Vec HuVecF;

typedef struct HuVec2f_s {
    float x;
    float y;
} HuVec2f;

#define HuAbs(x) (((x) < 0) ? -(x) : (x))

#define HuSquare(x) ((x)*(x))

// #define HuSetVecF(vec, x, y, z) \
// (vec)->x = (x); \
// (vec)->y = (y); \
// (vec)->z = (z)

#define HuAddVecF(dst, src1, src2) VECAdd(src1, src2, dst)
// #define HuSubVecF(dst, src1, src2) VECSubtract(src1, src2, dst)

#define HuCopyVecF(dst, src) \
(dst)->x = (src)->x; \
(dst)->y = (src)->y; \
(dst)->z = (src)->z

#define HuCopyVec2F(dst, src) \
(dst)->x = (src)->x; \
(dst)->y = (src)->y

#define HuMag2Point2D(x, y) (HuSquare(x)+HuSquare(y))
#define HuMag2Point3D(x, y, z) (HuSquare(x)+HuSquare(y)+HuSquare(z))

#define HuMagPoint2D(x, y) sqrtf(HuMag2Point2D(x, y))
#define HuMagPoint3D(x, y, z) sqrtf(HuMag2Point3D(x, y, z))

#define HuMagVecF(vec) HuMagPoint3D((vec)->x, (vec)->y, (vec)->z)
#define HuDistVecF(a, b) HuMagPoint3D((a)->x-(b)->x, (a)->y-(b)->y, (a)->z-(b)->z)

#define HuMagXZVecF(vec) HuMagPoint2D((vec)->x, (vec)->z)
#define HuDistXZVecF(a, b) HuMagPoint2D((a)->x-(b)->x, (a)->z-(b)->z)

#define HuMagXYVecF(vec) HuMagPoint2D((vec)->x, (vec)->y)
#define HuDistXYVecF(a, b) HuMagPoint2D((a)->x-(b)->x, (a)->y-(b)->y)

#define HuMagVec2F(vec) HuMagPoint2D((vec)->x, (vec)->y)
#define HuDistVec2F(a, b) HuMagPoint2D((a)->x-(b)->x, (a)->y-(b)->y)

#define HuScaleVecF(src, dst, scale) VECScale(src, dst, scale)
#define HuNormVecF(src, dst) VECNormalize(src, dst)

#define HuSin(x) sin(M_PI*(x)/180.0)
#define HuCos(x) cos(M_PI*(x)/180.0)
#define HuTan(x) tan(M_PI*(x)/180.0)

#define HuAtan(y, x) (180.0*(atan2((y), (x)) / M_PI))

#endif
