#ifndef M407DLL_H
#define M407DLL_H

#include "game/object.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

typedef void (*VoidFuncs)(void);
typedef void (*ObjFuncs)(omObjData *);

void fn_1_F4(Process *arg0);
void fn_1_194(void);
void fn_1_1E4(void);
void fn_1_238(void);
void fn_1_28C(void);
void fn_1_2E0(void);
void fn_1_334(void);
void fn_1_388(u8, s32);
void fn_1_3C4(u8);
void fn_1_404(void);
s32 fn_1_508(u8);
s32 fn_1_53C(u8);
void fn_1_568(s16, s16, s16);

void fn_1_14F0(Process *arg0, s32 arg1);
void fn_1_15D8(void);

void fn_1_1B1C(Process *arg0);
void fn_1_1CA8(void);
void fn_1_1CAC(f32, f32, f32);
void fn_1_1CD4(f32* arg0, f32* arg1, f32* arg2);
s32 fn_1_1D88(void);
void fn_1_1DB0(Point3d *arg0, Point3d *arg1, f32 *arg2, s32 arg3, s32 arg4);

void fn_1_2354(Process *arg0);
void fn_1_2564(void);
void fn_1_25C0(void);
s32 fn_1_2880(void);
#ifndef __MWERKS__
s16 fn_1_28B8(u8 arg0);
s16 fn_1_28D4(void);
#endif

void fn_1_3AC8(Process *arg0);
void fn_1_3B68(void);

void fn_1_41CC(Process *arg0);
void fn_1_44F4(void);

void fn_1_4980(Process* arg0);
void fn_1_4C6C(omObjData *obj);

void fn_1_5C5C(Process *arg0, s16 arg1);
void fn_1_5ECC(void);
void fn_1_5F40(s32 arg0);

#endif
