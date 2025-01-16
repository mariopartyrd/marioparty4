#ifndef REL_MODELTEST_H
#define REL_MODELTEST_H

#include "game/hsfdraw.h"
#include "game/objsub.h"
#include "game/object.h"

#include "ext_math.h"

// -------------------------------------------------------------------------- //

#define US_PER_60TH_SEC (1000000.0f / 60.0f)
#define US_TO_60TH_SEC(us) ((us) / US_PER_60TH_SEC)
#define FB_SIZE(width, height) width * height * 2

// -------------------------------------------------------------------------- //

typedef struct
{
    s16 unk0[7];
} HuUnkF9C2;

typedef struct
{
    Point3d pos;      // 0000
    Point3d rot;      // 000C
    Point3d scale;    // 0018
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    HsfObject * obj;  // 0030
} HuObjUnk;

extern Point3d CRot;
extern Point3d Center;
extern f32 CZoom;
void fn_1_29C();
void fn_1_28F8(Point3d * arg0, Point3d * arg1);
void fn_1_37DC(omObjData*);
void fn_1_439C(omObjData*);
void fn_1_46F0();

typedef void (omObjFunc2)(struct om_obj_data *);
omObjFunc2 fn_1_F9C;

#endif

// -------------------------------------------------------------------------- //
