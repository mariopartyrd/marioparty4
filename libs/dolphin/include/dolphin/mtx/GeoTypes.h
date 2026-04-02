#ifndef _DOLPHIN_GEOTYPES
#define _DOLPHIN_GEOTYPES

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  f32 x, y, z;
} Vec, *VecPtr, Point3d, *Point3dPtr;

typedef struct {
  s16 x;
  s16 y;
  s16 z;
} S16Vec, *S16VecPtr;

typedef struct {
  f32 x, y, z, w;
} Quaternion, *QuaternionPtr, Qtrn, *QtrnPtr;

typedef f32 Mtx[3][4];

typedef f32 (*MtxPtr)[4];

typedef f32 ROMtx[4][3];

typedef f32 (*ROMtxPtr)[3];

typedef f32 Mtx44[4][4];

typedef f32 (*Mtx44Ptr)[4];
#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GEOTYPES
