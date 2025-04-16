#include "REL/m427Dll.h"

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXVert.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfformat.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/frand.h"
#endif

typedef struct M427DllPlayerWork2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ float unk_68;
    /* 0x6C */ float unk_6C;
    /* 0x70 */ float unk_70;
} M427DllPlayerWork2; /* size = 0x74 */

typedef struct M427DllPlayerWork {
    /* 0x00 */ omObjData *unk_00[2];
    /* 0x08 */ M427DllPlayerWork2 *unk_08[2];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ s32 unk_30[5];
    /* 0x34 */ char unk44[8];
    /* 0x4C */ float unk_4C;
    /* 0x50 */ float unk_50;
    /* 0x54 */ float unk_54;
    /* 0x58 */ float unk_58;
    /* 0x5C */ float unk_5C;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ float unk_64;
    /* 0x68 */ s32 unk_68;
    /* 0x6C */ char unk6C[4];
} M427DllPlayerWork; /* size = 0x70 */

typedef struct M427DllBss57CStruct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ Vec unk_1C;
    /* 0x28 */ Vec unk_28;
    /* 0x34 */ float unk_34;
    /* 0x38 */ char unk38[4];
} M427DllBss57CStruct; /* size = 0x3C */

typedef struct M427DllBss590Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ Vec unk_14[2];
    /* 0x2C */ Vec unk_2C[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ float unk_50;
    /* 0x54 */ float unk_54;
    /* 0x58 */ float unk_58;
    /* 0x5C */ float unk_5C;
    /* 0x60 */ float unk_60;
    /* 0x64 */ float unk_64;
    /* 0x68 */ float unk_68;
    /* 0x6C */ float unk_6C;
    /* 0x70 */ float unk_70;
    /* 0x74 */ float unk_74;
    /* 0x78 */ Vec *unk_78;
    /* 0x7C */ Vec *unk_7C;
    /* 0x80 */ Vec *unk_80;
} M427DllBss590Struct; /* size = 0x84 */

void fn_1_10830(omObjData *object);
void fn_1_1143C(omObjData *object);
void fn_1_115B4(omObjData *object);
void fn_1_119C0(omObjData *object);
void fn_1_11A74(omObjData *object);
void fn_1_11ED8(omObjData *object);
void fn_1_12514(omObjData *object);
void fn_1_12518(omObjData *object);
void fn_1_12580(omObjData *object);
void fn_1_12B08(void);
void fn_1_13F24(void);
void fn_1_13FB8(void);
s32 fn_1_155E0(float arg8, float arg9, float argA, float *arg0);
float fn_1_15714(float arg8, float arg9);
void fn_1_158D8(float arg8, float arg9, Vec *arg0);
s32 fn_1_15AF0(s32 arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4);
void fn_1_1607C(s32 arg0);
s32 fn_1_160D4(s32 arg0, Vec *arg1, float arg8);
s32 fn_1_16260(s32 arg0, Vec *arg2, Vec *arg3, Vec *arg4, float arg8);
float fn_1_16594(float arg8, float arg9);
void fn_1_16E3C(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
void fn_1_17048(Vec *arg0, float *arg1, Vec *arg2, Vec *arg3);
void fn_1_1723C(Mtx arg0, Vec *arg1);
void fn_1_172F0(s32 arg0, float arg8);
s32 fn_1_17430(s32 arg0, s32 arg1, s32 arg2);
void fn_1_EC74(omObjData *object);
void fn_1_EC94(omObjData *object);
void fn_1_F0E0(omObjData *object);

Vec lbl_1_data_260[0x1D] = {
    { -900.0f, 0.0f, 2000.0f },
    { -900.0f, 0.0f, 0.0f },
    { -900.0f, 0.0f, -2000.0f },
    { -900.0f, 0.0f, -4000.0f },
    { -1300.0f, 0.0f, -4500.0f },
    { -1600.0f, 0.0f, -5000.0f },
    { -1800.0f, 0.0f, -5500.0f },
    { -1900.0f, 0.0f, -6000.0f },
    { -1800.0f, 0.0f, -6500.0f },
    { -1600.0f, -100.0f, -7000.0f },
    { -1300.0f, -200.0f, -7500.0f },
    { -900.0f, -300.0f, -8000.0f },
    { -900.0f, -300.0f, -8500.0f },
    { -500.0f, -300.0f, -9000.0f },
    { -500.0f, -300.0f, -10000.0f },
    { -500.0f, -300.0f, -11000.0f },
    { -900.0f, -300.0f, -11500.0f },
    { -900.0f, -300.0f, -12000.0f },
    { -500.0f, -300.0f, -12500.0f },
    { -200.0f, -300.0f, -13000.0f },
    { -0.0f, -300.0f, -13500.0f },
    { 100.0f, -300.0f, -14000.0f },
    { 0.0f, -300.0f, -14500.0f },
    { -200.0f, -400.0f, -15000.0f },
    { -500.0f, -500.0f, -15500.0f },
    { -900.0f, -600.0f, -16000.0f },
    { -900.0f, -600.0f, -18000.0f },
    { -900.0f, -600.0f, -20000.0f },
    { -900.0f, -600.0f, -22000.0f },
};
Vec lbl_1_data_3BC[29] = {
    { 900.0f, 0.0f, 2000.0f },
    { 900.0f, 0.0f, -0.0f },
    { 900.0f, 0.0f, -2000.0f },
    { 900.0f, 0.0f, -4000.0f },
    { 500.0f, 0.0f, -4500.0f },
    { 200.0f, 0.0f, -5000.0f },
    { 0.0f, 0.0f, -5500.0f },
    { -100.0f, 0.0f, -6000.0f },
    { 0.0f, 0.0f, -6500.0f },
    { 200.0f, -100.0f, -7000.0f },
    { 500.0f, -200.0f, -7500.0f },
    { 900.0f, -300.0f, -8000.0f },
    { 900.0f, -300.0f, -8500.0f },
    { 500.0f, -300.0f, -9000.0f },
    { 500.0f, -300.0f, -10000.0f },
    { 500.0f, -300.0f, -11000.0f },
    { 900.0f, -300.0f, -11500.0f },
    { 900.0f, -300.0f, -12000.0f },
    { 1300.0f, -300.0f, -12500.0f },
    { 1600.0f, -300.0f, -13000.0f },
    { 1800.0f, -300.0f, -13500.0f },
    { 1900.0f, -300.0f, -14000.0f },
    { 1800.0f, -300.0f, -14500.0f },
    { 1600.0f, -400.0f, -15000.0f },
    { 1300.0f, -500.0f, -15500.0f },
    { 900.0f, -600.0f, -16000.0f },
    { 900.0f, -600.0f, -18000.0f },
    { 900.0f, -600.0f, -20000.0f },
    { 900.0f, -600.0f, -22000.0f },
};
s32 lbl_1_data_518[7] = { 0, 1, 2, 3, 4, 5, 6 };
Vec lbl_1_data_534[2] = { { 0.0f, -25.0f, 50.0f }, { 0.0f, -25.0f, -50.0f } };
Vec lbl_1_data_54C[2] = { { 0.0f, 0.0f, 1900.0f }, { 0.0f, 20.0f, 20.0f } };
Vec lbl_1_data_564 = { 0.0f, 240.00002f, 360.0f };
Vec lbl_1_data_570 = { 0.0f, 1.0f, 1.5f };
GXColor lbl_1_data_57C = { 0xFF, 0xFF, 0xFF, 0xFF };

Process *lbl_1_bss_594;
M427DllBss590Struct *lbl_1_bss_590;
Vec *lbl_1_bss_58C;
Vec *lbl_1_bss_588;
Vec *lbl_1_bss_584;
s32 lbl_1_bss_580;
M427DllBss57CStruct *lbl_1_bss_57C;
M427DllPlayerWork *lbl_1_bss_578;
M427DllPlayerWork2 *lbl_1_bss_574;
omObjData *lbl_1_bss_56C[2];
char lbl_1_bss_55C[0x10];
Vec *lbl_1_bss_558;
Vec *lbl_1_bss_554;
Vec *lbl_1_bss_550;

void fn_1_E98C(Process *sp8)
{
    s32 sp10;
    omObjData *object;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    s8 spE[2] = { 0xFF, 0xFF };
    s8 spC[2] = { 0xFF, 0xFF };
    sp10 = 0;
    OSReport("Init Player \n");
    lbl_1_bss_594 = sp8;
    object = omAddObjEx(lbl_1_bss_594, 0x42, 0, 0, -1, fn_1_EC74);
    omMakeGroupEx(lbl_1_bss_594, 0, 4);
    omGetGroupMemberListEx(lbl_1_bss_594, 0);
    for (var_r30 = 0, var_r28 = 0, var_r27 = 0, var_r29 = 0; var_r30 < 4; var_r30++) {
        var_r26 = GWPlayerCfg[var_r30].group;
        switch (var_r26) {
            case 0:
                if (var_r28 >= 2) {
                    var_r29 = 1;
                }
                else {
                    spE[var_r28] = var_r30;
                    var_r28++;
                }
                break;
            case 1:
                if (var_r27 >= 2) {
                    var_r29 = 1;
                }
                else {
                    spC[var_r27] = var_r30;
                    var_r27++;
                }
                break;
            default:
                var_r29 = 1;
                break;
        }
        if (var_r29 != 0) {
            break;
        }
    }
    lbl_1_bss_578 = HuMemDirectMallocNum(HEAP_SYSTEM, 2 * sizeof(M427DllPlayerWork), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_578, 0, 0xE0);
    lbl_1_bss_574 = HuMemDirectMallocNum(HEAP_SYSTEM, 4 * sizeof(M427DllPlayerWork2), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_574, 0, 0x1D0);
    memset(lbl_1_bss_56C, 0, 8);
    memset(lbl_1_bss_55C, 0, 0x10);
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        object = lbl_1_bss_56C[var_r30] = omAddObjEx(lbl_1_bss_594, 0x41, 0xE, 0, -1, fn_1_EC94);
        object->work[0] = var_r30;
        if (var_r29 != 0) {
            object->work[1] = var_r30 * 2;
            object->work[2] = (var_r30 * 2) + 1;
        }
        else if (var_r30 == 0) {
            object->work[1] = spE[0];
            object->work[2] = spE[1];
        }
        else {
            object->work[1] = spC[0];
            object->work[2] = spC[1];
        }
    }
    fn_1_12B08();
}

s32 lbl_1_data_590[7] = { 0x3A001C, 0x3A001D, 0x3A001E, 0x3A001F, 0x3A0020, 0x3A0026, 0x3A0027 };
s32 lbl_1_data_5AC[7] = { 0x3A0021, 0x3A0022, 0x3A0023, 0x3A0024, 0x3A0025, 0x3A0026, 0x3A0027 };
s32 lbl_1_data_5C8[2] = { 1, 3 };
s32 lbl_1_data_5D0[2] = { 2, 4 };

void fn_1_EC54(void)
{
    fn_1_13FB8();
}

void fn_1_EC74(omObjData *object)
{
    fn_1_13F24();
}

void fn_1_EC94(omObjData *object)
{
    M427DllPlayerWork *work;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    work = &lbl_1_bss_578[object->work[0]];
    object->data = work;
    work->unk_10 = object->work[0];
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->unk_1C = 0;
    work->unk_20 = 0;
    work->unk_24 = 0;
    work->unk_28 = 0.0f;
    work->unk_2C = 0.0f;
    work->unk_4C = 0.0f;
    work->unk_50 = 0.0f;
    work->unk_54 = 0.0f;
    work->unk_58 = 0.0f;
    work->unk_5C = 0.0f;
    work->unk_60 = 0;
    work->unk_64 = 180.0f;
    work->unk_68 = 0;
    object->trans.x = lbl_1_data_54C->x;
    object->trans.y = lbl_1_data_54C->y;
    object->trans.z = lbl_1_data_54C->z;
    for (var_r29 = 0; var_r29 < 7; var_r29++) {
        if (work->unk_10 == 0) {
            object->model[var_r29] = Hu3DModelCreateFile(lbl_1_data_590[var_r29]);
        }
        else {
            object->model[var_r29] = Hu3DModelCreateFile(lbl_1_data_5AC[var_r29]);
        }
        Hu3DModelLayerSet(object->model[var_r29], 2);
        if (work->unk_10 == 0) {
            Hu3DModelCameraSet(object->model[var_r29], 1);
        }
        else {
            Hu3DModelCameraSet(object->model[var_r29], 2);
        }
        if (var_r29 < 5) {
            Hu3DMotionSpeedSet(object->model[var_r29], 2.0f);
        }
    }
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(object->model[0], 2.0f);
    Hu3DModelLayerSet(object->model[5], 5);
    Hu3DModelAttrSet(object->model[5], HU3D_MOTATTR_LOOP);
    for (var_r29 = 0; var_r29 < 5; var_r29++) {
        if (var_r29 == 0) {
            var_r28 = object->model[var_r29];
            var_r27 = Hu3DLLightCreateV(var_r28, &lbl_1_data_564, &lbl_1_data_570, &lbl_1_data_57C);
            work->unk_30[var_r29] = var_r27;
            Hu3DLLightStaticSet(var_r28, var_r27, 1);
            Hu3DLLightPointSet(var_r28, var_r27, 80.0f, 0.95f, 3);
            Hu3DLLightColorSet(var_r28, var_r27, 0xFF, 0xF0, 0xDC, 0xFF);
            Hu3DLLightPosSet(
                var_r28, var_r27, lbl_1_data_564.x, lbl_1_data_564.y, lbl_1_data_564.z, lbl_1_data_570.x, lbl_1_data_570.y, lbl_1_data_570.z);
        }
        else {
            var_r28 = object->model[var_r29];
            work->unk_30[var_r29] = fn_1_17430(object->model[0], work->unk_30[0], var_r28);
        }
        fn_1_172F0(var_r28, 0.1f);
    }
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        work->unk_00[var_r29] = omAddObjEx(lbl_1_bss_594, 0x40, 2, 4, -1, fn_1_11A74);
        work->unk_00[var_r29]->work[0] = object->work[var_r29 + 1];
        work->unk_00[var_r29]->work[1] = work->unk_10;
        work->unk_00[var_r29]->work[2] = var_r29;
    }
    object->func = fn_1_F0E0;
}

void fn_1_F0E0(omObjData *object)
{
    Mtx sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    M427DllPlayerWork *work;
    s32 var_r29;
    s32 var_r28;

    work = object->data;
    if ((work->unk_00[0] == NULL) || (work->unk_08[0] == NULL)) {
        return;
    }
    sp2C.x = object->trans.x;
    sp2C.y = object->trans.y;
    sp2C.z = object->trans.z;
    switch (work->unk_1C) {
        case 0:
            object->rot.y = work->unk_64 = 180.0f;
            for (var_r29 = 0; var_r29 < 2; var_r29++) {
                if ((work->unk_08[var_r29]->unk_30 != 0) && (Hu3DMotionEndCheck(object->model[lbl_1_data_5C8[var_r29]]) != 0)) {
                    fn_1_3B20(var_r29 * 2, work->unk_10);
                    Hu3DMotionTimeSet(object->model[lbl_1_data_5C8[var_r29]], 0.0f);
                    if (work->unk_10 == 0) {
                        HuAudFXPlay(0x655);
                    }
                    else {
                        HuAudFXPlay(0x656);
                    }
                }
                if ((work->unk_08[var_r29]->unk_34 != 0) && (Hu3DMotionEndCheck(object->model[lbl_1_data_5D0[var_r29]]) != 0)) {
                    fn_1_3B20((var_r29 * 2) + 1, work->unk_10);
                    Hu3DMotionTimeSet(object->model[lbl_1_data_5D0[var_r29]], 0.0f);
                    if (work->unk_10 == 0) {
                        HuAudFXPlay(0x655);
                    }
                    else {
                        HuAudFXPlay(0x656);
                    }
                }
            }
            if (sp2C.z != object->trans.z) {
                work->unk_60 = 2;
            }
            else {
                work->unk_60 = 0;
            }
            if (fn_1_1788() == 3) {
                work->unk_1C = 1;
            }
            break;
        case 1:
            if (sp2C.z != object->trans.z) {
                work->unk_60 = 2;
            }
            else {
                work->unk_60 = 0;
            }
            if (fn_1_1788() == 4) {
                work->unk_1C = 2;
            }
            break;
        case 2:
            for (var_r29 = 0; var_r29 < 2; var_r29++) {
                if (work->unk_08[var_r29]->unk_30 != 0) {
                    work->unk_58 += 0.1f;
                    if (Hu3DMotionEndCheck(object->model[lbl_1_data_5C8[var_r29]]) != 0) {
                        fn_1_3B20(var_r29 * 2, work->unk_10);
                        Hu3DMotionTimeSet(object->model[lbl_1_data_5C8[var_r29]], 0.0f);
                        if (work->unk_10 == 0) {
                            HuAudFXPlay(0x655);
                        }
                        else {
                            HuAudFXPlay(0x656);
                        }
                    }
                }
                if (work->unk_08[var_r29]->unk_34 != 0) {
                    work->unk_5C += 0.1f;
                    if (Hu3DMotionEndCheck(object->model[lbl_1_data_5D0[var_r29]]) != 0) {
                        fn_1_3B20((var_r29 * 2) + 1, work->unk_10);
                        Hu3DMotionTimeSet(object->model[lbl_1_data_5D0[var_r29]], 0.0f);
                        if (work->unk_10 == 0) {
                            HuAudFXPlay(0x655);
                        }
                        else {
                            HuAudFXPlay(0x656);
                        }
                    }
                }
            }
            fn_1_158D8(object->trans.x, object->trans.z, &sp8);
            work->unk_4C += 0.15f * sp8.x;
            work->unk_54 += 0.15f * sp8.z;
            work->unk_58 *= 0.995f;
            work->unk_5C *= 0.995f;
            work->unk_4C *= 0.99f;
            work->unk_54 *= 0.99f;
            work->unk_60 = work->unk_58 + work->unk_5C;
            if (work->unk_60 < -5.0f) {
                work->unk_60 = -5;
            }
            else if (work->unk_60 > 5.0f) {
                work->unk_60 = 5;
            }
            var_f30 = 0.25f * (work->unk_58 - work->unk_5C);
            if (var_f30 > 20.0f) {
                var_f30 = 20.0f;
            }
            else if (var_f30 < -20.0f) {
                var_f30 = -20.0f;
            }
            work->unk_64 += var_f30;
            if (work->unk_64 > 360.0f) {
                work->unk_64 -= 360.0f;
            }
            else if (work->unk_64 < 0.0f) {
                work->unk_64 += 360.0f;
            }
            if (work->unk_64 > 270.0f) {
                work->unk_64 = 270.0f;
            }
            else if (work->unk_64 < 90.0f) {
                work->unk_64 = 90.0f;
            }
            object->rot.y = work->unk_64;
            var_f31 = work->unk_60;
            object->trans.x = object->trans.x + (2.0 * (var_f31 * sind(work->unk_64)));
            object->trans.z = object->trans.z + (2.0 * (var_f31 * cosd(work->unk_64)));
            object->trans.x += work->unk_4C;
            object->trans.z += work->unk_54;
            if (work->unk_68 > 0) {
                work->unk_68--;
            }
            for (var_r29 = 0, var_r28 = 1; (var_r28 == 1) && (var_r29 < 6); var_r29++) {
                var_r28 = 0;
                sp20.x = object->trans.x;
                sp20.y = object->trans.y;
                sp20.z = object->trans.z;
                if (fn_1_15AF0(-1, &sp2C, &sp20, &sp14, &sp8) != 0) {
                    var_r28 = 1;
                    sp2C = sp20;
                    object->trans.x = sp14.x;
                    object->trans.y = sp14.y;
                    object->trans.z = sp14.z;
                    if ((work->unk_68 == 0) && (fn_1_1788() <= 4)) {
                        if (work->unk_10 == 0) {
                            HuAudFXPlay(0x65C);
                        }
                        else {
                            HuAudFXPlay(0x65D);
                        }
                    }
                    work->unk_68 = 5;
                }
                sp20.x = object->trans.x;
                sp20.y = object->trans.y;
                sp20.z = object->trans.z;
                if (fn_1_16260(work->unk_10, &sp2C, &sp20, &sp14, 200.0f) != 0) {
                    var_r28 = 1;
                    sp2C = sp20;
                    object->trans.x = sp14.x;
                    object->trans.y = sp14.y;
                    object->trans.z = sp14.z;
                }
            }
            if (work->unk_20 <= 0) {
                sp20.x = object->trans.x;
                sp20.y = object->trans.y;
                sp20.z = object->trans.z;
                if (fn_1_160D4(work->unk_10, &sp20, 200.0f) != 0) {
                    omVibrate(work->unk_08[0]->unk_00, 0xC, 6, 6);
                    omVibrate(work->unk_08[1]->unk_00, 0xC, 6, 6);
                    HuAudCharVoicePlay(work->unk_08[0]->unk_0C, 0x123);
                    HuAudCharVoicePlay(work->unk_08[1]->unk_0C, 0x123);
                    work->unk_24 = 0x78;
                    work->unk_1C = 3;
                    work->unk_28 = 5.0f;
                    work->unk_2C = 360.0f * ((frand() & 0x7F) / 127.0f);
                    work->unk_18 = 0;
                }
            }
            else {
                work->unk_20--;
            }
            fn_1_119C0(object);
            if (fn_1_1788() >= 5) {
                work->unk_1C = 4;
            }
            break;
        case 3:
            work->unk_58 = 0.0f;
            work->unk_5C = 0.0f;
            work->unk_4C = 0.0f;
            work->unk_54 = 0.0f;
            work->unk_60 = work->unk_58 + work->unk_5C;
            if (work->unk_60 < -5.0f) {
                work->unk_60 = -5;
            }
            else if (work->unk_60 > 5.0f) {
                work->unk_60 = 5;
            }
            var_f31 = work->unk_60 / 5.0f;
            var_f31 = 5.0f * (var_f31 * var_f31);
            object->trans.x = object->trans.x + (2.0 * (var_f31 * sind(work->unk_64)));
            object->trans.z = object->trans.z + (2.0 * (var_f31 * cosd(work->unk_64)));
            object->trans.x += work->unk_4C;
            object->trans.z += work->unk_54;
            for (var_r29 = 0, var_r28 = 1; (var_r28 == 1) && (var_r29 < 6); var_r29++) {
                var_r28 = 0;
                sp20.x = object->trans.x;
                sp20.y = object->trans.y;
                sp20.z = object->trans.z;
                if (fn_1_15AF0(-1, &sp2C, &sp20, &sp14, &sp8) != 0) {
                    var_r28 = 1;
                    sp2C = sp20;
                    object->trans.x = sp14.x;
                    object->trans.y = sp14.y;
                    object->trans.z = sp14.z;
                }
                sp20.x = object->trans.x;
                sp20.y = object->trans.y;
                sp20.z = object->trans.z;
                if (fn_1_16260(work->unk_10, &sp2C, &sp20, &sp14, 200.0f) != 0) {
                    var_r28 = 1;
                    sp2C = sp20;
                    object->trans.x = sp14.x;
                    object->trans.y = sp14.y;
                    object->trans.z = sp14.z;
                }
            }
            if ((--work->unk_24 > 0) && ((work->unk_18 & 3) == 0)) {
                omVibrate(work->unk_08[0]->unk_00, 0xC, 6, 6);
                omVibrate(work->unk_08[1]->unk_00, 0xC, 6, 6);
            }
            if (work->unk_18 >= 120.0f) {
                work->unk_1C = 2;
                work->unk_20 = 0xB4;
                work->unk_18 = 0;
            }
            fn_1_119C0(object);
            if (fn_1_1788() >= 7) {
                work->unk_20 = 0;
                work->unk_18 = 0;
                work->unk_1C = 4;
                object->func = fn_1_10830;
            }
            break;
        case 4:
            work->unk_58 *= 0.993f;
            work->unk_5C *= 0.993f;
            work->unk_4C *= 0.993f;
            work->unk_54 *= 0.993f;
            work->unk_60 = work->unk_58 + work->unk_5C;
            if (work->unk_60 < -5.0f) {
                work->unk_60 = -5;
            }
            else if (work->unk_60 > 5.0f) {
                work->unk_60 = 5;
            }
            var_f31 = work->unk_60 / 5.0f;
            var_f31 = 5.0f * (var_f31 * var_f31);
            object->trans.x = object->trans.x + (2.0 * (var_f31 * sind(work->unk_64)));
            object->trans.z = object->trans.z + (2.0 * (var_f31 * cosd(work->unk_64)));
            object->trans.x += work->unk_4C;
            object->trans.z += work->unk_54;
            for (var_r29 = 0, var_r28 = 1; (var_r28 == 1) && (var_r29 < 6); var_r29++) {
                var_r28 = 0;
                sp20.x = object->trans.x;
                sp20.y = object->trans.y;
                sp20.z = object->trans.z;
                if (fn_1_15AF0(-1, &sp2C, &sp20, &sp14, &sp8) != 0) {
                    var_r28 = 1;
                    sp2C = sp20;
                    object->trans.x = sp14.x;
                    object->trans.y = sp14.y;
                    object->trans.z = sp14.z;
                }
                sp20.x = object->trans.x;
                sp20.y = object->trans.y;
                sp20.z = object->trans.z;
                if (fn_1_16260(work->unk_10, &sp2C, &sp20, &sp14, 200.0f) != 0) {
                    var_r28 = 1;
                    sp2C = sp20;
                    object->trans.x = sp14.x;
                    object->trans.y = sp14.y;
                    object->trans.z = sp14.z;
                }
            }
            work->unk_20 = 0;
            if (fn_1_1788() >= 7) {
                work->unk_18 = 0;
                work->unk_1C = 4;
                object->func = fn_1_10830;
            }
            break;
        case 5:
            if (sp2C.z != object->trans.z) {
                work->unk_60 = 2;
            }
            else {
                work->unk_60 = 0;
            }
            break;
        case 6:
            break;
        case 7:
            break;
    }
    var_f31 = work->unk_60 / 5.0f;
    Hu3DMotionSpeedSet(object->model[0], 2.0f * var_f31);
    if (work->unk_1C == 3) {
        work->unk_2C += (frand() & 3) + 2;
        object->rot.x = 0.0f;
        object->rot.z = 0.0f;
        work->unk_28 = 5.0f - (5.0f * (0.008333334f * work->unk_18));
        var_f29 = 7.0 * (work->unk_28 * sind((10.0f * work->unk_18)));
        object->rot.x = object->rot.x + (var_f29 * sind(work->unk_2C));
        object->rot.z = object->rot.z + (var_f29 * cosd(work->unk_2C));
    }
    if (((work->unk_1C == 3) || (work->unk_20 != 0)) && ((work->unk_18 & 1) != 0)) {
        for (var_r29 = 0; var_r29 < 7; var_r29++) {
            Hu3DModelAttrSet(object->model[var_r29], HU3D_ATTR_DISPOFF);
        }
        for (var_r29 = 0; var_r29 < 2; var_r29++) {
            if (work->unk_00[var_r29]->model[0] != -1) {
                Hu3DModelAttrSet(*work->unk_00[var_r29]->model, HU3D_ATTR_DISPOFF);
            }
        }
    }
    else {
        for (var_r29 = 0; var_r29 < 7; var_r29++) {
            Hu3DModelAttrReset(object->model[var_r29], HU3D_ATTR_DISPOFF);
        }
        for (var_r29 = 0; var_r29 < 2; var_r29++) {
            if (work->unk_00[var_r29]->model[0] != -1) {
                Hu3DModelAttrReset(*work->unk_00[var_r29]->model, HU3D_ATTR_DISPOFF);
            }
        }
    }
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        work->unk_08[var_r29]->unk_24 = work->unk_1C;
    }
    object->trans.y = fn_1_AE78(work->unk_10, object->trans.x, object->trans.z);
    mtxRot(sp38, object->rot.x, object->rot.y, object->rot.z);
    sp38[1][0] *= object->scale.y;
    sp38[1][1] *= object->scale.y;
    sp38[1][2] *= object->scale.z;
    sp20.x = 0.0f;
    sp20.y = 0.0f;
    sp20.z = 100.0f;
    fn_1_1723C(sp38, &sp20);
    sp20.x += object->trans.x;
    sp20.y += object->trans.y;
    sp20.z += object->trans.z;
    fn_1_91E0(work->unk_10, sp20.x, sp20.y, sp20.z, 180.0f + object->rot.y);
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        sp20 = lbl_1_data_534[var_r29];
        fn_1_1723C(sp38, &sp20);
        work->unk_00[var_r29]->trans.x = object->trans.x + sp20.x;
        work->unk_00[var_r29]->trans.y = object->trans.y + sp20.y;
        work->unk_00[var_r29]->trans.z = object->trans.z + sp20.z;
        work->unk_00[var_r29]->rot.x = object->rot.x;
        work->unk_00[var_r29]->rot.y = object->rot.y;
        work->unk_00[var_r29]->rot.z = object->rot.z;
    }
    for (var_r29 = 0; var_r29 < 7; var_r29++) {
        Hu3DModelPosSet(object->model[var_r29], object->trans.x, object->trans.y, object->trans.z);
        Hu3DModelRotSet(object->model[var_r29], object->rot.x, object->rot.y, object->rot.z);
    }
    fn_1_1143C(object);
    if ((fn_1_32EC() == 0) && (object->func != fn_1_10830) && ((work->unk_1C == 2) || (work->unk_1C == 3))) {
        fn_1_115B4(object);
    }
    work->unk_18++;
}

s32 lbl_1_data_5F8[2] = { 1, 3 };
s32 lbl_1_data_600[2] = { 2, 4 };
s32 lbl_1_data_608[4] = { 0x3A002F, 0x3A0037, 0x3A003F, 0x3A0047 };
s32 lbl_1_data_618[4] = { 15, 10, 6, 5 };

void fn_1_10830(omObjData *object)
{
    Mtx sp14;
    Vec sp8;
    s32 var_r30;
    M427DllPlayerWork *work;
    s32 var_r28;
    s32 var_r27;

    work = object->data;
    switch (work->unk_1C) {
        case 4:
            var_r27 = fn_1_1884();
            if (var_r27 == 3) {
                break;
            }
            if (var_r27 == work->unk_10) {
                for (var_r30 = 0; var_r30 < 2; var_r30++) {
                    Hu3DModelCameraSet(*work->unk_00[var_r30]->model, 1);
                    Hu3DModelLayerSet(*work->unk_00[var_r30]->model, 3);
                    fn_1_172F0(work->unk_00[var_r30]->model[0], 5.0f);
                }
                for (var_r30 = 0; var_r30 < 7; var_r30++) {
                    Hu3DModelCameraSet(object->model[var_r30], 1);
                    Hu3DModelLayerSet(object->model[var_r30], 3);
                    if (var_r30 < 5) {
                        fn_1_172F0(object->model[var_r30], 5.0f);
                    }
                }
                Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF);
                for (var_r30 = 0; var_r30 < 2; var_r30++) {
                    work->unk_00[var_r30]->model[1] = Hu3DModelLink(*work->unk_00[var_r30]->model);
                    Hu3DModelCameraSet(work->unk_00[var_r30]->model[1], 1);
                    Hu3DModelLayerSet(work->unk_00[var_r30]->model[1], 1);
                }
                for (var_r30 = 0; var_r30 < 7; var_r30++) {
                    object->model[var_r30 + 7] = Hu3DModelLink(object->model[var_r30]);
                    Hu3DModelCameraSet(object->model[var_r30 + 7], 1);
                    Hu3DModelLayerSet(object->model[var_r30 + 7], 1);
                }
                object->trans.x = object->trans.y = object->trans.z = 0.0f;
                object->rot.x = object->rot.z = 0.0f;
                object->rot.y = 180.0f;
                work->unk_1C = 5;
                break;
            }
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                Hu3DModelAttrSet(work->unk_00[var_r30]->model[0], HU3D_ATTR_DISPOFF);
                work->unk_00[var_r30]->func = NULL;
            }
            for (var_r30 = 0; var_r30 < 7; var_r30++) {
                Hu3DModelAttrSet(object->model[var_r30], HU3D_ATTR_DISPOFF);
            }
            object->func = NULL;
            return;
        case 5:
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                var_r28 = lbl_1_data_5F8[var_r30];
                if ((work->unk_08[var_r30]->unk_30 != 0) && (Hu3DMotionEndCheck(object->model[var_r28]) != 0)) {
                    fn_1_3B20(var_r30 * 2, work->unk_10);
                    Hu3DMotionTimeSet(object->model[var_r28], 0.0f);
                    if (work->unk_10 == 0) {
                        HuAudFXPlay(0x655);
                    }
                    else {
                        HuAudFXPlay(0x656);
                    }
                }
                var_r28 = lbl_1_data_600[var_r30];
                if ((work->unk_08[var_r30]->unk_34 != 0) && (Hu3DMotionEndCheck(object->model[var_r28]) != 0)) {
                    fn_1_3B20((var_r30 * 2) + 1, work->unk_10);
                    Hu3DMotionTimeSet(object->model[var_r28], 0.0f);
                    if (work->unk_10 == 0) {
                        HuAudFXPlay(0x655);
                    }
                    else {
                        HuAudFXPlay(0x656);
                    }
                }
            }
            if (fn_1_1788() >= 0xC) {
                work->unk_1C = 6;
            }
            break;
        case 6:
        case 7:
            break;
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        work->unk_08[var_r30]->unk_24 = work->unk_1C;
    }
    mtxRot(sp14, object->rot.x, object->rot.y, object->rot.z);
    sp14[1][0] *= object->scale.y;
    sp14[1][1] *= object->scale.y;
    sp14[1][2] *= object->scale.z;
    sp8.x = 0.0f;
    sp8.y = 0.0f;
    sp8.z = 100.0f;
    fn_1_1723C(sp14, &sp8);
    sp8.x += object->trans.x;
    sp8.y += object->trans.y;
    sp8.z += object->trans.z;
    fn_1_91E0(work->unk_10, sp8.x, sp8.y, sp8.z, 180.0f + object->rot.y);
    object->trans.y = fn_1_AE78(work->unk_10, object->trans.x, object->trans.z);
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        sp8 = lbl_1_data_534[var_r30];
        fn_1_1723C(sp14, &sp8);
        work->unk_00[var_r30]->trans.x = object->trans.x + sp8.x;
        work->unk_00[var_r30]->trans.y = object->trans.y + sp8.y;
        work->unk_00[var_r30]->trans.z = object->trans.z + sp8.z;
        work->unk_00[var_r30]->rot.x = object->rot.x;
        work->unk_00[var_r30]->rot.y = object->rot.y;
        work->unk_00[var_r30]->rot.z = object->rot.z;
        if (work->unk_00[var_r30]->model[1] != -1) {
            Hu3DModelPosSet(
                work->unk_00[var_r30]->model[1], -work->unk_00[var_r30]->trans.x, work->unk_00[var_r30]->trans.y, work->unk_00[var_r30]->trans.z);
            Hu3DModelRotSet(
                work->unk_00[var_r30]->model[1], work->unk_00[var_r30]->rot.x, -work->unk_00[var_r30]->rot.y, work->unk_00[var_r30]->rot.z);
        }
    }
    for (var_r30 = 0; var_r30 < 0xE; var_r30++) {
        if (object->model[var_r30] != -1) {
            if (var_r30 < 7) {
                Hu3DModelPosSet(object->model[var_r30], object->trans.x, object->trans.y, object->trans.z);
                Hu3DModelRotSet(object->model[var_r30], object->rot.x, object->rot.y, object->rot.z);
            }
            else {
                Hu3DModelPosSet(object->model[var_r30], -object->trans.x, object->trans.y, object->trans.z);
                Hu3DModelRotSet(object->model[var_r30], object->rot.x, -object->rot.y, object->rot.z);
            }
        }
    }
    work->unk_64 = 200.0f;
    fn_1_1143C(object);
    work->unk_18++;
}

void fn_1_10F8C(omObjData *object)
{
    s32 var_r31;
    M427DllPlayerWork *work = object->data;
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        fn_1_12514(work->unk_00[var_r31]);
    }
}

s32 fn_1_10FE8(s32 arg0, s32 *arg1)
{
    s32 var_r31;
    M427DllPlayerWork *var_r30;
    omObjData *var_r29;

    var_r29 = lbl_1_bss_56C[arg0];
    var_r30 = &lbl_1_bss_578[arg0];
    if ((var_r29 == NULL) || (var_r30 == NULL)) {
        return -1;
    }
    if ((var_r30->unk_00[0] == NULL) || (var_r30->unk_08[0] == NULL)) {
        return -1;
    }
    for (var_r31 = 0; var_r31 < 7; var_r31++) {
        if (var_r31 < 5) {
            arg1[var_r31] = var_r29->model[var_r31];
        }
        else if (var_r31 < 6) {
            arg1[var_r31] = var_r30->unk_00[0]->model[0];
        }
        else {
            arg1[var_r31] = var_r30->unk_00[1]->model[0];
        }
    }
    return var_r31;
}

void fn_1_110E8(s32 arg0, s32 *arg1)
{
    s32 var_r31;
    M427DllPlayerWork *var_r30;
    omObjData *var_r29;

    var_r29 = lbl_1_bss_56C[arg0];
    var_r30 = &lbl_1_bss_578[arg0];
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        arg1[var_r31] = 0;
    }
    if ((var_r29 == NULL) || (var_r30 == NULL)) {
        return;
    }
    if ((var_r30->unk_00[0] == NULL) || (var_r30->unk_08[0] == NULL)) {
        return;
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        arg1[var_r31] = var_r30->unk_08[var_r31]->unk_0C;
    }
}

void fn_1_111C0(s32 arg0, s32 *arg1)
{
    s32 var_r31;
    M427DllPlayerWork *var_r30;
    omObjData *var_r29;

    var_r29 = lbl_1_bss_56C[arg0];
    var_r30 = &lbl_1_bss_578[arg0];
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        arg1[var_r31] = 0;
    }
    if ((var_r29 == NULL) || (var_r30 == NULL)) {
        return;
    }
    if ((var_r30->unk_00[0] == NULL) || (var_r30->unk_08[0] == NULL)) {
        return;
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        arg1[var_r31] = var_r30->unk_08[var_r31]->unk_00;
    }
}

void fn_1_11298(float var_f30)
{
    float var_f31;
    omObjData *object;
    s32 var_r30;

    if (fn_1_1788() < 4) {
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            object = lbl_1_bss_56C[var_r30];
            if (object) {
                object->trans.z = 1900.0f + (-1800.0f * var_f30);
            }
        }
        return;
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        object = lbl_1_bss_56C[var_r30];
        if (object) {
            object->trans.z = -1800.0f * var_f30;
            if (object->trans.z < -1500.0f) {
                var_f31 = (object->trans.z - -1500.0f) / 300.0f;
                object->rot.y = 180.0f - (30.0f * var_f31);
            }
        }
    }
}

s32 fn_1_113F0(s32 arg0)
{
    M427DllPlayerWork *work;
    omObjData *object;

    object = lbl_1_bss_56C[arg0];
    work = object->data;
    if (work->unk_14 == 3) {
        return 1;
    }
    return 0;
}

void fn_1_1143C(omObjData *object)
{
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    M427DllPlayerWork *work;
    s32 var_r29;

    work = object->data;
    mtxRot(sp20, 0.0f, work->unk_64, 0.0f);
    sp14 = lbl_1_data_564;
    fn_1_1723C(sp20, &sp14);
    sp14.x += object->trans.x;
    sp14.y += object->trans.y;
    sp14.z += object->trans.z;
    sp8.x = sp8.z = 0.0f;
    sp8.y = 1.0f;
    Hu3DLLightPosSet(object->model[0], work->unk_30[0], sp14.x, sp14.y, sp14.z, sp8.x, sp8.y, sp8.z);
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        if (*work->unk_00[var_r29]->model != -1) {
            Hu3DLLightPosSet(work->unk_00[var_r29]->model[0], work->unk_08[var_r29]->unk_14, sp14.x, sp14.y, sp14.z, sp8.x, sp8.y, sp8.z);
        }
    }
}

void fn_1_115B4(omObjData *object)
{
    Vec spC;
    float sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    M427DllBss590Struct *var_r31;
    M427DllPlayerWork *work;
    s32 var_r28;

    work = object->data;
    var_r28 = fn_1_155E0(object->trans.x, object->trans.y, object->trans.z, &sp8);
    if ((var_r28 < 0) || (var_r28 >= (lbl_1_bss_580 - 1))) {
        return;
    }
    var_r31 = &lbl_1_bss_590[var_r28];
    spC.x = var_r31->unk_44.x + (sp8 * var_r31->unk_50);
    spC.y = 275.0f + (var_r31->unk_44.y + (sp8 * var_r31->unk_54));
    spC.z = var_r31->unk_44.z + (sp8 * var_r31->unk_58);
    var_f29 = object->trans.x - spC.x;
    spC.x += 0.4f * var_f29;
    if (var_f29 < 0.0f) {
        var_f30 = fabs(var_r31->unk_5C + (sp8 * (var_r31->unk_64 - var_r31->unk_5C)));
    }
    else {
        var_f30 = fabs(var_r31->unk_60 + (sp8 * (var_r31->unk_68 - var_r31->unk_60)));
    }
    CenterM[work->unk_10].x = CenterM[work->unk_10].x + (0.06666667f * (spC.x - CenterM[work->unk_10].x));
    CenterM[work->unk_10].y = CenterM[work->unk_10].y + (0.06666667f * (spC.y - CenterM[work->unk_10].y));
    CenterM[work->unk_10].z = CenterM[work->unk_10].z + (0.06666667f * (spC.z - CenterM[work->unk_10].z));
    var_f31 = var_r31->unk_0C;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    var_f31 = 180.0f + (0.25f * (var_f31 - 180.0f));
    if (var_f30 != 0.0f) {
        var_f30 = var_f29 / var_f30;
    }
    var_f31 -= 30.0f * var_f30;
    CRotM[work->unk_10].y = fn_1_168FC(0.020000001f, CRotM[work->unk_10].y, 180.0f + var_f31);
}

void fn_1_119C0(omObjData *object)
{
    float var_f31;
    float var_f30;
    M427DllBss590Struct *var_r31;
    M427DllPlayerWork *work;
    M427DllBss590Struct *var_r28;

    work = object->data;
    var_r31 = &lbl_1_bss_590[1];
    var_r28 = &lbl_1_bss_590[27];
    var_f31 = var_r28->unk_80->z - var_r31->unk_80->z;
    var_f30 = object->trans.z - var_r31->unk_80->z;
    fn_1_1798(work->unk_10, var_f30 / var_f31);
}

void fn_1_11A74(omObjData *object)
{
    M427DllPlayerWork2 *var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    M427DllPlayerWork *var_r26;

    var_r31 = &lbl_1_bss_574[object->work[0]];
    object->data = var_r31;
    var_r26 = &lbl_1_bss_578[object->work[1]];
    lbl_1_bss_578[object->work[1]].unk_08[object->work[2]] = var_r31;
    var_r31->unk_00 = object->work[0];
    var_r31->unk_04 = object->work[1];
    var_r31->unk_08 = GWPlayerCfg[var_r31->unk_00].pad_idx;
    var_r31->unk_0C = GWPlayerCfg[var_r31->unk_00].character;
    var_r31->unk_10 = object->work[2];
    var_r31->unk_18 = GWPlayerCfg[var_r31->unk_00].iscom;
    var_r31->unk_1C = GWPlayerCfg[var_r31->unk_00].diff;
    var_r31->unk_20 = 0;
    var_r31->unk_24 = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_30 = 0;
    var_r31->unk_34 = 0;
    var_r31->unk_38 = 0;
    var_r31->unk_3C = 0;
    var_r31->unk_40 = var_r31->unk_44 = 0;
    var_r31->unk_48 = var_r31->unk_4C = 0;
    var_r31->unk_50 = 0;
    var_r31->unk_54 = 0;
    var_r31->unk_60 = lbl_1_data_618[var_r31->unk_1C];
    var_r31->unk_58 = frand() % var_r31->unk_60;
    var_r31->unk_5C = frand() % 7;
    var_r31->unk_64 = -1;
    var_r31->unk_68 = var_r31->unk_6C = var_r31->unk_70 = 0.0f;
    if (var_r31->unk_18 != 0) {
        var_r26->unk_14 |= 1 << var_r31->unk_10;
    }
    var_r27 = var_r31->unk_0C;
    object->model[0] = CharModelCreate(var_r27, 4);
    Hu3DModelLayerSet(object->model[0], 2);
    if (var_r31->unk_04 == 0) {
        Hu3DModelCameraSet(object->model[0], 1);
    }
    else {
        Hu3DModelCameraSet(object->model[0], 2);
    }
    if (var_r31->unk_10 != 0) {
        fn_1_172F0(object->model[0], 0.3f);
    }
    else {
        fn_1_172F0(object->model[0], 0.3f);
    }
    CharModelStepTypeSet(var_r27, 3);
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], var_r31->unk_0C + lbl_1_data_608[var_r29]);
    }
    var_r31->unk_2C = 0;
    CharModelMotionSet(var_r31->unk_0C, object->motion[0]);
    CharModelMotionDataClose(var_r27);
    var_r28 = Hu3DLLightCreateV(object->model[0], &lbl_1_data_564, &lbl_1_data_570, &lbl_1_data_57C);
    var_r31->unk_14 = var_r28;
    Hu3DLLightStaticSet(object->model[0], var_r28, 1);
    if (var_r31->unk_10 == 0) {
        Hu3DLLightPointSet(object->model[0], var_r28, 80.0f, 0.95f, 3);
    }
    else {
        Hu3DLLightPointSet(object->model[0], var_r28, 80.0f, 0.95f, 3);
    }
    Hu3DLLightColorSet(object->model[0], var_r28, 0xFF, 0xFF, 0xFF, 0xFF);
    Hu3DLLightPosSet(
        object->model[0], var_r28, lbl_1_data_564.x, lbl_1_data_564.y, lbl_1_data_564.z, lbl_1_data_570.x, lbl_1_data_570.y, lbl_1_data_570.z);
    object->func = fn_1_11ED8;
    (void)var_r29;
}

void fn_1_11ED8(omObjData *object)
{
    M427DllPlayerWork2 *var_r31;
    s32 var_r29;
    M427DllPlayerWork *var_r28;
    omObjData *var_r27;

    var_r31 = object->data;
    var_r28 = &lbl_1_bss_578[var_r31->unk_04];
    var_r27 = lbl_1_bss_56C[var_r31->unk_04];
    var_r31->unk_40 = HuPadBtn[var_r31->unk_08];
    var_r31->unk_44 = HuPadBtnDown[var_r31->unk_08];
    if ((var_r31->unk_18 != 0) && (var_r31->unk_24 == 2)) {
        if (var_r28->unk_14 == 3) {
            fn_1_12580(object);
        }
        else {
            fn_1_12518(object);
        }
    }
    var_r31->unk_38 = var_r31->unk_3C = 0;
    if (var_r31->unk_30 != 0) {
        var_r31->unk_38 = 1;
    }
    if (var_r31->unk_34 != 0) {
        var_r31->unk_3C = 1;
    }
    var_r31->unk_30 = var_r31->unk_34 = 0;
    switch (var_r31->unk_24) {
        case 0:
            if (((var_r31->unk_20 & 0xF) == 0) && (var_r27->trans.z > 100.0f)) {
                var_r31->unk_30 = 1;
                var_r31->unk_34 = 1;
            }
            var_r29 = 1;
            if (var_r29 != var_r31->unk_2C) {
                var_r31->unk_2C = var_r29;
                CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_2C], 0.0f, 8.0f, 0x40000001);
            }
            break;
        case 1:
            var_r29 = 0;
            if ((var_r29 != var_r31->unk_2C) && (CharModelMotionShiftIDGet(var_r31->unk_0C) == -1)) {
                var_r31->unk_2C = var_r29;
                CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_2C], 0.0f, 8.0f, 0x40000001);
                var_r31->unk_28 = 0;
            }
            break;
        case 2:
            if (fn_1_32EC() == 0) {
                if ((var_r31->unk_44 & 0x100) != 0) {
                    var_r31->unk_30 = 1;
                }
                if ((var_r31->unk_44 & 0x200) != 0) {
                    var_r31->unk_34 = 1;
                }
            }
            var_r31->unk_48 = var_r31->unk_40;
            var_r31->unk_4C = var_r31->unk_44;
            if ((var_r31->unk_30 != 0) || (var_r31->unk_34 != 0)) {
                var_r29 = 1;
            }
            else {
                var_r29 = 0;
            }
            if ((CharModelMotionShiftIDGet(var_r31->unk_0C) == -1)
                && ((var_r29 != var_r31->unk_2C) || (CharModelMotionEndCheck(var_r31->unk_0C) == 1))) {
                if (var_r31->unk_2C == var_r29) {
                    CharModelMotionTimeSet(var_r31->unk_0C, 0.0f);
                }
                else {
                    var_r31->unk_2C = var_r29;
                    CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_2C], 0.0f, 8.0f, 0);
                }
            }
            break;
        case 3:
            var_r29 = 2;
            if ((var_r29 != var_r31->unk_2C) && (CharModelMotionShiftIDGet(var_r31->unk_0C) == -1)) {
                var_r31->unk_2C = var_r29;
                CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_2C], 0.0f, 8.0f, 0x40000001);
                var_r31->unk_28 = 0;
            }
            if (var_r31->unk_2C == 2) {
                if (++var_r31->unk_28 >= 240.0f) {
                    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
                }
            }
            break;
        case 4:
            var_r29 = 0;
            if ((var_r29 != var_r31->unk_2C) && (CharModelMotionShiftIDGet(var_r31->unk_0C) == -1)) {
                var_r31->unk_2C = var_r29;
                if (object->model[1] != -1) {
                    Hu3DMotionShiftSet(object->model[1], object->motion[var_r31->unk_2C], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
                else {
                    CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_2C], 0.0f, 8.0f, 0x40000001);
                }
                var_r31->unk_28 = 0;
            }
            break;
        case 5:
            if (object->trans.z > -1300.0f) {
                if ((var_r31->unk_20 & 0xF) == 0) {
                    var_r31->unk_30 = 1;
                    var_r31->unk_34 = 1;
                }
                var_r29 = 1;
            }
            else {
                var_r29 = 0;
            }
            if (var_r31->unk_2C == 1) {
                Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
            }
            if ((CharModelMotionShiftIDGet(var_r31->unk_0C) == -1) && (var_r29 != var_r31->unk_2C)) {
                var_r31->unk_2C = var_r29;
                CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_2C], 0.0f, 8.0f, 0x40000001);
            }
            break;
        case 6:
            var_r29 = 3;
            if ((var_r29 != var_r31->unk_2C) && (CharModelMotionShiftIDGet(var_r31->unk_0C) == -1)) {
                var_r31->unk_2C = var_r29;
                CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_2C], 0.0f, 8.0f, 0);
                HuAudCharVoicePlay(var_r31->unk_0C, 0x124);
                var_r31->unk_28 = 0;
            }
            break;
        case 7:
            break;
    }
    var_r31->unk_20++;
}

void fn_1_12514(omObjData *object) { }

void fn_1_12518(omObjData *object)
{
    M427DllPlayerWork *var_r31;
    M427DllPlayerWork2 *var_r30;
    M427DllPlayerWork2 *var_r29;

    var_r30 = object->data;
    var_r31 = &lbl_1_bss_578[var_r30->unk_04];
    if (var_r31->unk_14 == 1) {
        var_r29 = var_r31->unk_08[1];
    }
    else {
        var_r29 = var_r31->unk_08[0];
    }
    var_r30->unk_40 = var_r29->unk_48;
    var_r30->unk_44 = var_r29->unk_4C;
}

void fn_1_12580(omObjData *var_r24)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    M427DllPlayerWork2 *var_r31;
    M427DllBss590Struct *var_r30;
    omObjData *var_r29;
    M427DllPlayerWork *var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    var_r31 = var_r24->data;
    var_r28 = &lbl_1_bss_578[var_r31->unk_04];
    var_r29 = lbl_1_bss_56C[var_r31->unk_04];
    var_r31->unk_40 = 0;
    var_r31->unk_44 = 0;
    var_r26 = fn_1_155E0(var_r29->trans.x, var_r29->trans.y, var_r29->trans.z, NULL);
    if ((var_r31->unk_64 != var_r26) || (var_r31->unk_54 > 180.0f)) {
        var_r31->unk_64 = var_r26;
        switch (var_r31->unk_1C) {
            case 0:
                var_r27 = 2;
                break;
            case 1:
                var_r27 = 2;
                break;
            case 2:
                var_r27 = 3;
                break;
            case 3:
                var_r27 = 4;
                break;
        }
        if ((var_r31->unk_64 >= 0) && (var_r31->unk_64 < (lbl_1_bss_580 - var_r27)) && (var_r31->unk_64 <= (lbl_1_bss_580 - 2))) {
            var_r26 = var_r31->unk_64 + var_r27;
            var_r30 = &lbl_1_bss_590[var_r26];
            var_f31 = 0.5f * (var_r30->unk_64 + var_r30->unk_68);
            var_f30 = (0.6f - (0.1f * var_r31->unk_1C)) - (0.1f * var_r31->unk_1C * ((frand() & 0x7F) / 127.0f));
            if (var_f30 > 1.0f) {
                var_f30 = 1.0f;
            }
            else if (var_f30 < 0.0f) {
                var_f30 = 0.0f;
            }
            var_f31 *= var_f30;
            if ((frand() & 1) != 0) {
                var_f31 *= -1.0f;
            }
            var_r31->unk_68 = var_r30->unk_80->x + var_f31;
            var_r31->unk_6C = var_r30->unk_80->y;
            var_r31->unk_70 = var_r30->unk_80->z;
        }
        else {
            var_r30 = &lbl_1_bss_590[lbl_1_bss_580 - 1];
            var_r31->unk_68 = var_r30->unk_80->x;
            var_r31->unk_6C = var_r30->unk_80->y;
            var_r31->unk_70 = var_r30->unk_80->z;
        }
        var_r31->unk_54 = 0;
    }
    var_r25 = var_r31->unk_60 + var_r31->unk_5C;
    if (var_r28->unk_20 != 0) {
        var_r25 = 5;
    }
    if (++var_r31->unk_58 > var_r25) {
        var_r31->unk_58 = 0;
        var_r31->unk_5C = frand() % 7;
        var_f28 = var_r31->unk_68 - var_r29->trans.x;
        var_f27 = var_r31->unk_70 - var_r29->trans.z;
        var_f31 = fn_1_16594(atan2d(var_f28, var_f27), var_r28->unk_64);
        if (fabs(var_f31) < (30.0f - (5.0f * var_r31->unk_1C))) {
            if (var_r31->unk_1C > 2) {
                var_f29 = 0.25f * (var_r28->unk_58 - var_r28->unk_5C);
                if (var_f29 > 10.0f) {
                    var_r31->unk_44 |= 0x100;
                }
                else if (var_f29 < -10.0f) {
                    var_r31->unk_44 |= 0x200;
                }
                else {
                    var_r31->unk_44 |= 0x300;
                }
            }
            else {
                var_r31->unk_44 |= 0x300;
            }
        }
        else if (var_f31 < 0.0f) {
            var_r31->unk_44 |= 0x200;
        }
        else {
            var_r31->unk_44 |= 0x100;
        }
    }
    var_r31->unk_50++;
    var_r31->unk_54++;
}

void fn_1_12B08(void)
{
    Vec sp20;
    M427DllBss590Struct *var_r31;
    s32 var_r30;
    M427DllBss57CStruct *var_r29;

    lbl_1_bss_580 = 0x1D;
    lbl_1_bss_584 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_580 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_584, 0, lbl_1_bss_580 * sizeof(Vec));
    for (var_r30 = 0; var_r30 < lbl_1_bss_580; var_r30++) {
        lbl_1_bss_584[var_r30].x = 0.5f * (lbl_1_data_260[var_r30].x + lbl_1_data_3BC[var_r30].x);
        lbl_1_bss_584[var_r30].y = 0.5f * (lbl_1_data_260[var_r30].y + lbl_1_data_3BC[var_r30].y);
        lbl_1_bss_584[var_r30].z = 0.5f * (lbl_1_data_260[var_r30].z + lbl_1_data_3BC[var_r30].z);
    }
    lbl_1_bss_58C = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_580 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_58C, 0, lbl_1_bss_580 * sizeof(Vec));
    for (var_r30 = 0; var_r30 < lbl_1_bss_580; var_r30++) {
        VECSubtract(&lbl_1_bss_584[var_r30], &lbl_1_data_260[var_r30], &lbl_1_bss_58C[var_r30]);
        VECNormalize(&lbl_1_bss_58C[var_r30], &lbl_1_bss_58C[var_r30]);
        VECScale(&lbl_1_bss_58C[var_r30], &lbl_1_bss_58C[var_r30], 200.0f);
        VECAdd(&lbl_1_bss_58C[var_r30], &lbl_1_data_260[var_r30], &lbl_1_bss_58C[var_r30]);
    }
    lbl_1_bss_588 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_580 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_588, 0, lbl_1_bss_580 * sizeof(Vec));
    for (var_r30 = 0; var_r30 < lbl_1_bss_580; var_r30++) {
        VECSubtract(&lbl_1_bss_584[var_r30], &lbl_1_data_3BC[var_r30], &lbl_1_bss_588[var_r30]);
        VECNormalize(&lbl_1_bss_588[var_r30], &lbl_1_bss_588[var_r30]);
        VECScale(&lbl_1_bss_588[var_r30], &lbl_1_bss_588[var_r30], 200.0f);
        VECAdd(&lbl_1_bss_588[var_r30], &lbl_1_data_3BC[var_r30], &lbl_1_bss_588[var_r30]);
    }
    var_r31 = lbl_1_bss_590 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_580 * sizeof(M427DllBss590Struct), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_590, 0, lbl_1_bss_580 * sizeof(M427DllBss590Struct));
    for (var_r30 = 0; var_r30 < lbl_1_bss_580; var_r30++, var_r31++) {
        var_r31->unk_00 = var_r30;
        var_r31->unk_04 = var_r30 + 1;
        var_r31->unk_08 = var_r30 - 1;
        if (var_r31->unk_04 >= lbl_1_bss_580) {
            var_r31->unk_04 = -1;
        }
        if (var_r31->unk_08 >= lbl_1_bss_580) {
            var_r31->unk_08 = -1;
        }
        var_r31->unk_78 = &lbl_1_bss_58C[var_r30];
        var_r31->unk_7C = &lbl_1_bss_588[var_r30];
        var_r31->unk_80 = &lbl_1_bss_584[var_r30];
        if (var_r31->unk_04 < 0) {
            var_r31->unk_0C = 180.0f;
            var_r31->unk_70 = 180.0f;
            var_r31->unk_74 = 180.0f;
        }
        else {
            var_r31->unk_0C
                = atan2d(lbl_1_bss_584[var_r31->unk_04].x - lbl_1_bss_584[var_r30].x, lbl_1_bss_584[var_r31->unk_04].z - lbl_1_bss_584[var_r30].z);
            var_r31->unk_70
                = atan2d(lbl_1_bss_58C[var_r31->unk_04].x - lbl_1_bss_58C[var_r30].x, lbl_1_bss_58C[var_r31->unk_04].z - lbl_1_bss_58C[var_r30].z);
            var_r31->unk_74
                = atan2d(lbl_1_bss_588[var_r31->unk_04].x - lbl_1_bss_588[var_r30].x, lbl_1_bss_588[var_r31->unk_04].z - lbl_1_bss_588[var_r30].z);
        }
        if (var_r31->unk_08 < 0) {
            var_r31->unk_10 = 0.0f;
        }
        else {
            var_r31->unk_10
                = atan2d(lbl_1_bss_584[var_r31->unk_08].x - lbl_1_bss_584[var_r30].x, lbl_1_bss_584[var_r31->unk_08].z - lbl_1_bss_584[var_r30].z);
        }
        if (var_r31->unk_04 < 0) {
            var_r31->unk_6C = 0.0f;
            sp20.x = lbl_1_bss_58C[var_r30].x + lbl_1_bss_590[var_r30 - 1].unk_14[1].x;
            sp20.y = lbl_1_bss_58C[var_r30].y + lbl_1_bss_590[var_r30 - 1].unk_14[1].y;
            sp20.z = lbl_1_bss_58C[var_r30].z + lbl_1_bss_590[var_r30 - 1].unk_14[1].z;
            fn_1_16E3C(&lbl_1_data_260[var_r30], &sp20, &var_r31->unk_14[0], 0);
            sp20.x = lbl_1_bss_588[var_r30].x + lbl_1_bss_590[var_r30 - 1].unk_2C[1].x;
            sp20.y = lbl_1_bss_588[var_r30].y + lbl_1_bss_590[var_r30 - 1].unk_2C[1].y;
            sp20.z = lbl_1_bss_588[var_r30].z + lbl_1_bss_590[var_r30 - 1].unk_2C[1].z;
            fn_1_16E3C(&lbl_1_data_3BC[var_r30], &sp20, &var_r31->unk_2C[0], 0);
            sp20.x = lbl_1_bss_584[var_r30].x + lbl_1_bss_590[var_r30 - 1].unk_50;
            sp20.y = lbl_1_bss_584[var_r30].y + lbl_1_bss_590[var_r30 - 1].unk_54;
            sp20.z = lbl_1_bss_584[var_r30].z + lbl_1_bss_590[var_r30 - 1].unk_58;
            fn_1_16E3C(&lbl_1_bss_584[var_r30], &sp20, &var_r31->unk_44, 0);
        }
        else {
            sp20.x = lbl_1_bss_584[var_r30 + 1].x - lbl_1_bss_584[var_r30].x;
            sp20.y = lbl_1_bss_584[var_r30 + 1].y - lbl_1_bss_584[var_r30].y;
            sp20.z = lbl_1_bss_584[var_r30 + 1].z - lbl_1_bss_584[var_r30].z;
            var_r31->unk_6C = sqrtf((sp20.z * sp20.z) + ((sp20.x * sp20.x) + (sp20.y * sp20.y)));
            fn_1_16E3C(&lbl_1_bss_58C[var_r30], &lbl_1_bss_58C[var_r31->unk_04], &var_r31->unk_14[0], 0);
            fn_1_16E3C(&lbl_1_bss_588[var_r30], &lbl_1_bss_588[var_r31->unk_04], &var_r31->unk_2C[0], 0);
            fn_1_16E3C(&lbl_1_bss_584[var_r30], &lbl_1_bss_584[var_r31->unk_04], &var_r31->unk_44, 0);
        }
        sp20.x = lbl_1_bss_58C[var_r30].x - lbl_1_bss_584[var_r30].x;
        sp20.z = lbl_1_bss_58C[var_r30].z - lbl_1_bss_584[var_r30].z;
        sp20.y = 0.0f;
        var_r31->unk_5C = sqrtf((sp20.z * sp20.z) + ((sp20.x * sp20.x) + (sp20.y * sp20.y)));
        sp20.x = lbl_1_bss_588[var_r30].x - lbl_1_bss_584[var_r30].x;
        sp20.z = lbl_1_bss_588[var_r30].z - lbl_1_bss_584[var_r30].z;
        sp20.y = 0.0f;
        var_r31->unk_60 = sqrtf((sp20.z * sp20.z) + ((sp20.x * sp20.x) + (sp20.y * sp20.y)));
        if (var_r31->unk_04 < 0) {
            var_r31->unk_64 = var_r31->unk_5C;
            var_r31->unk_68 = var_r31->unk_60;
        }
        else {
            sp20.x = lbl_1_bss_58C[var_r31->unk_04].x - lbl_1_bss_584[var_r31->unk_04].x;
            sp20.z = lbl_1_bss_58C[var_r31->unk_04].z - lbl_1_bss_584[var_r31->unk_04].z;
            sp20.y = 0.0f;
            var_r31->unk_64 = sqrtf((sp20.z * sp20.z) + ((sp20.x * sp20.x) + (sp20.y * sp20.y)));
            sp20.x = lbl_1_bss_588[var_r31->unk_04].x - lbl_1_bss_584[var_r31->unk_04].x;
            sp20.z = lbl_1_bss_588[var_r31->unk_04].z - lbl_1_bss_584[var_r31->unk_04].z;
            sp20.y = 0.0f;
            var_r31->unk_68 = sqrtf((sp20.z * sp20.z) + ((sp20.x * sp20.x) + (sp20.y * sp20.y)));
        }
    }
    lbl_1_bss_558 = lbl_1_data_260;
    lbl_1_bss_554 = lbl_1_data_3BC;
    lbl_1_bss_550 = lbl_1_bss_584;
    var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, 64 * sizeof(M427DllBss57CStruct), MEMORY_DEFAULT_NUM);
    lbl_1_bss_57C = var_r29;
    memset(lbl_1_bss_57C, 0, 64 * sizeof(M427DllBss57CStruct));
    for (var_r30 = 0; var_r30 < 64; var_r30++, var_r29++) {
        var_r29->unk_00 = var_r30;
        var_r29->unk_04 = -1;
        var_r29->unk_08 = -1;
        var_r29->unk_0C = 0;
        var_r29->unk_10 = 0;
        var_r29->unk_14 = var_r29->unk_18 = 0;
    }
}

void fn_1_13F24(void)
{
    M427DllBss57CStruct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_57C, var_r30 = 0; var_r30 < 0x40; var_r30 += 1, var_r31++) {
        if ((var_r31->unk_04 >= 0) && (var_r31->unk_08 >= 0) && (var_r31->unk_18 >= 0)) {
            if (++var_r31->unk_14 > var_r31->unk_18) {
                fn_1_1607C(var_r30);
            }
        }
    }
}

void fn_1_13FB8(void) { }

GXColor lbl_1_data_648 = { 0xFF, 0xFF, 0xFF, 0xFF };
GXColor lbl_1_data_64C = { 0xFF, 0, 0, 0xFF };
GXColor lbl_1_data_650 = { 0xFF, 0xFF, 0, 0xFF };

void fn_1_13FBC(ModelData *model, Mtx matrix)
{
    Mtx sp70;
    float var_f31;
    float var_f30;
    float var_f29;
    M427DllBss57CStruct *var_r31;
    M427DllBss590Struct *var_r30;
    s16 var_r29;
    s16 var_r28;
    M427DllPlayerWork *var_r27;
    M427DllPlayerWork2 *var_r26;
    s32 *var_r25;
    omObjData *var_r24;

    var_r25 = model->unk_120;
    var_r27 = &lbl_1_bss_578[*var_r25];
    var_r24 = lbl_1_bss_56C[*var_r25];
    GXLoadPosMtxImm(matrix, 0);
    MTXInvXpose(matrix, sp70);
    GXLoadNrmMtxImm(sp70, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetChanCtrl(GX_COLOR0A0, 1, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_SPEC);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetZCompLoc(GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetLineWidth(0x10, GX_TO_ZERO);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXSETARRAY(GX_VA_POS, lbl_1_data_260, sizeof(lbl_1_data_260), sizeof(Vec));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
    GXSETARRAY(GX_VA_CLR0, &lbl_1_data_648, sizeof(lbl_1_data_648), sizeof(GXColor));
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 0x1D);
    for (var_r29 = 0; var_r29 < 0x1DU; var_r29++) {
        GXPosition1x16(var_r29);
        GXColor1x16(0);
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSETARRAY(GX_VA_POS, &lbl_1_data_3BC, sizeof(lbl_1_data_3BC), sizeof(Vec));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSETARRAY(GX_VA_CLR0, &lbl_1_data_648, sizeof(lbl_1_data_648), sizeof(GXColor));
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 0x1D);
    for (var_r29 = 0; var_r29 < 0x1DU; var_r29++) {
        GXPosition1x16(var_r29);
        GXColor1x16(0);
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSETARRAY(GX_VA_POS, lbl_1_bss_584, lbl_1_bss_580 * sizeof(Vec), sizeof(Vec));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSETARRAY(GX_VA_CLR0, &lbl_1_data_650, sizeof(lbl_1_data_650), sizeof(GXColor));
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 0x1D);
    for (var_r29 = 0; var_r29 < lbl_1_bss_580; var_r29++) {
        GXPosition1x16(var_r29);
        GXColor1x16(0);
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXBegin(GX_LINES, GX_VTXFMT0, lbl_1_bss_580 * 4);
    for (var_r30 = lbl_1_bss_590, var_r29 = 0; var_r29 < lbl_1_bss_580; var_r29++, var_r30++) {
        GXPosition3f32(var_r30->unk_78->x, var_r30->unk_78->y, var_r30->unk_78->z);
        GXColor4u8(lbl_1_data_64C.r, lbl_1_data_64C.g, lbl_1_data_64C.b, lbl_1_data_64C.a);
        GXPosition3f32(var_r30->unk_80->x, var_r30->unk_80->y, var_r30->unk_80->z);
        GXColor4u8(lbl_1_data_64C.r, lbl_1_data_64C.g, lbl_1_data_64C.b, lbl_1_data_64C.a);
        GXPosition3f32(var_r30->unk_7C->x, var_r30->unk_7C->y, var_r30->unk_7C->z);
        GXColor4u8(lbl_1_data_64C.r, lbl_1_data_64C.g, lbl_1_data_64C.b, lbl_1_data_64C.a);
        GXPosition3f32(var_r30->unk_80->x, var_r30->unk_80->y, var_r30->unk_80->z);
        GXColor4u8(lbl_1_data_64C.r, lbl_1_data_64C.g, lbl_1_data_64C.b, lbl_1_data_64C.a);
    }
    for (var_r29 = 0, var_r31 = lbl_1_bss_57C; var_r29 < 0x40; var_r29++, var_r31++) {
        if ((var_r31->unk_04 >= 0) && (var_r31->unk_08 >= 0) && (var_r31->unk_10 == *var_r25) && (var_r31->unk_04 == 1)) {
            switch (var_r31->unk_08) {
                case 0:
                    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
                    var_f31 = 200.0f + fn_1_15714(var_r31->unk_1C.x, var_r31->unk_1C.z);
                    GXPosition3f32(var_r31->unk_1C.x, var_f31, var_r31->unk_1C.z);
                    GXColor4u8(0, 0xFF, 0, 0xFF);
                    GXPosition3f32(var_r31->unk_28.x, var_f31, var_r31->unk_1C.z);
                    GXColor4u8(0, 0xFF, 0, 0xFF);
                    GXPosition3f32(var_r31->unk_28.x, var_f31, var_r31->unk_28.z);
                    GXColor4u8(0, 0xFF, 0, 0xFF);
                    GXPosition3f32(var_r31->unk_1C.x, var_f31, var_r31->unk_28.z);
                    GXColor4u8(0, 0xFF, 0, 0xFF);
                    GXPosition3f32(var_r31->unk_1C.x, var_f31, var_r31->unk_1C.z);
                    GXColor4u8(0, 0xFF, 0, 0xFF);
                    break;
                case 1:
                    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 0xA);
                    var_f31 = 200.0f + fn_1_15714(var_r31->unk_1C.x, var_r31->unk_1C.z);
                    for (var_r28 = 0; var_r28 < 0xA; var_r28++) {
                        var_f30 = var_r31->unk_1C.x + (var_r31->unk_34 * sind((40.0f * var_r28)));
                        var_f29 = var_r31->unk_1C.z + (var_r31->unk_34 * cosd((40.0f * var_r28)));
                        GXPosition3f32(var_f30, var_f31, var_f29);
                        GXColor4u8(0, 0xFF, 0, 0xFF);
                    }
                    break;
            }
        }
    }
    for (var_r29 = 0, var_r31 = lbl_1_bss_57C; var_r29 < 0x40; var_r29++, var_r31++) {
        if ((var_r31->unk_04 >= 0) && (var_r31->unk_08 >= 0) && (var_r31->unk_10 == *var_r25) && (var_r31->unk_04 == 0)) {
            switch (var_r31->unk_08) {
                case 0:
                    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
                    var_f31 = 200.0f + fn_1_15714(var_r31->unk_1C.x, var_r31->unk_1C.z);
                    GXPosition3f32(var_r31->unk_1C.x, var_f31, var_r31->unk_1C.z);
                    GXColor4u8(0, 0, 0xFF, 0xFF);
                    GXPosition3f32(var_r31->unk_28.x, var_f31, var_r31->unk_1C.z);
                    GXColor4u8(0, 0, 0xFF, 0xFF);
                    GXPosition3f32(var_r31->unk_28.x, var_f31, var_r31->unk_28.z);
                    GXColor4u8(0, 0, 0xFF, 0xFF);
                    GXPosition3f32(var_r31->unk_1C.x, var_f31, var_r31->unk_28.z);
                    GXColor4u8(0, 0, 0xFF, 0xFF);
                    GXPosition3f32(var_r31->unk_1C.x, var_f31, var_r31->unk_1C.z);
                    GXColor4u8(0, 0, 0xFF, 0xFF);
                    break;
                case 1:
                    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 0xA);
                    var_f31 = 200.0f + fn_1_15714(var_r31->unk_1C.x, var_r31->unk_1C.z);
                    for (var_r28 = 0; var_r28 < 0xA; var_r28++) {
                        var_f30 = var_r31->unk_1C.x + (var_r31->unk_34 * sind((40.0f * var_r28)));
                        var_f29 = var_r31->unk_1C.z + (var_r31->unk_34 * cosd((40.0f * var_r28)));
                        GXPosition3f32(var_f30, var_f31, var_f29);
                        GXColor4u8(0, 0, 0xFF, 0xFF);
                    }
                    break;
            }
        }
    }
    if ((var_r24 == NULL) || (var_r27 == NULL)) {
        return;
    }
    if ((var_r27->unk_00[0] == NULL) || (var_r27->unk_08[0] == NULL)) {
        return;
    }
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 0xA);
    var_f31 = 100.0f + var_r24->trans.y;
    for (var_r28 = 0; var_r28 < 0xA; var_r28++) {
        var_f30 = var_r24->trans.x + (200.0 * sind((40.0f * var_r28)));
        var_f30 = var_f30;
        var_f29 = var_r24->trans.z + (200.0 * cosd((40.0f * var_r28)));
        var_f29 = var_f29;
        GXPosition3f32(var_f30, var_f31, var_f29);
        GXColor4u8(0xFF, 0, 0xFF, 0xFF);
    }
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 4);
    var_r26 = var_r27->unk_08[0];
    var_f30 = var_r26->unk_68;
    var_f29 = var_r26->unk_70;
    var_f31 = 100.0f + fn_1_15714(var_f30, var_f29);
    GXPosition3f32(var_f30, var_f31, var_f29);
    GXColor4u8(0xFF, 0x80, 0, 0xFF);
    GXPosition3f32(100.0f + var_f30, 200.0f + var_f31, var_f29);
    GXColor4u8(0xFF, 0x80, 0, 0xFF);
    GXPosition3f32(var_f30 - 100.0f, 200.0f + var_f31, var_f29);
    GXColor4u8(0xFF, 0x80, 0, 0xFF);
    GXPosition3f32(var_f30, var_f31, var_f29);
    GXColor4u8(0xFF, 0x80, 0, 0xFF);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 4);
    var_r26 = var_r27->unk_08[1];
    var_f30 = var_r26->unk_68;
    var_f29 = var_r26->unk_70;
    var_f31 = 100.0f + fn_1_15714(var_f30, var_f29);
    GXPosition3f32(var_f30, var_f31, var_f29);
    GXColor4u8(0, 0x80, 0xFF, 0xFF);
    GXPosition3f32(100.0f + var_f30, 200.0f + var_f31, var_f29);
    GXColor4u8(0, 0x80, 0xFF, 0xFF);
    GXPosition3f32(var_f30 - 100.0f, 200.0f + var_f31, var_f29);
    GXColor4u8(0, 0x80, 0xFF, 0xFF);
    GXPosition3f32(var_f30, var_f31, var_f29);
    GXColor4u8(0, 0x80, 0xFF, 0xFF);
}

void fn_1_154B8(void) { }

s32 fn_1_154BC(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    s32 var_r31;
    s32 var_r30;

    var_r30 = -1;
    var_f27 = 1e7f;
    for (var_r31 = 0; var_r31 < lbl_1_bss_580; var_r31++) {
        var_f31 = lbl_1_bss_590[var_r31].unk_80->x - arg8;
        var_f30 = lbl_1_bss_590[var_r31].unk_80->y - arg9;
        var_f29 = lbl_1_bss_590[var_r31].unk_80->z - argA;
        var_f28 = (var_f29 * var_f29) + ((var_f31 * var_f31) + (var_f30 * var_f30));
        if (var_f28 < var_f27) {
            var_r30 = var_r31;
            var_f27 = var_f28;
        }
    }
    return var_r30;
}

s32 fn_1_155E0(float arg8, float arg9, float argA, float *arg0)
{
    float var_f31;
    M427DllBss590Struct *var_r31;
    s32 var_r30;
    M427DllBss590Struct *var_r29;

    for (var_r30 = 0; var_r30 < (lbl_1_bss_580 - 1); var_r30++) {
        var_r31 = &lbl_1_bss_590[var_r30];
        var_r29 = &lbl_1_bss_590[var_r30 + 1];
        if ((argA < var_r31->unk_80->z) && (argA >= var_r29->unk_80->z)) {
            var_f31 = var_r29->unk_80->z - var_r31->unk_80->z;
            if ((arg0 != NULL) && (var_f31 != 0.0f)) {
                *arg0 = fabs((argA - var_r31->unk_80->z) / var_f31);
            }
            break;
        }
    }
    return var_r30;
}

float fn_1_15714(float arg8, float arg9)
{
    float sp8;
    M427DllBss590Struct *var_r31;
    s32 var_r28;
    M427DllBss590Struct *var_r26;

    var_r28 = fn_1_155E0(0.0f, 0.0f, arg9, &sp8);
    var_r31 = &lbl_1_bss_590[var_r28];
    if ((var_r28 < 0) || (var_r28 >= (lbl_1_bss_580 - 1))) {
        return var_r31->unk_80->y;
    }
    var_r26 = &lbl_1_bss_590[var_r28 + 1];
    return var_r31->unk_80->y + (sp8 * (var_r26->unk_80->y - var_r31->unk_80->y));
}

void fn_1_158D8(float arg8, float var_f30, Vec *var_r31)
{
    float sp8;
    M427DllBss590Struct *var_r30;
    M427DllBss590Struct *var_r29;
    s32 var_r26;

    var_r31->x = var_r31->y = var_r31->z = 0.0f;
    var_r26 = fn_1_155E0(0.0f, 0.0f, var_f30, &sp8);
    var_r30 = &lbl_1_bss_590[var_r26];
    if ((var_r26 < 0) || (var_r26 >= (lbl_1_bss_580 - 1))) {
        return;
    }
    var_r29 = &lbl_1_bss_590[var_r26 + 1];
    if (var_r30->unk_80->y > var_r29->unk_80->y) {
        var_r31->x = var_r29->unk_80->x - var_r30->unk_80->x;
        var_r31->z = var_r29->unk_80->z - var_r30->unk_80->z;
        VECNormalize(var_r31, var_r31);
    }
}

s32 fn_1_15AF0(s32 arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4)
{
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float sp8;
    float var_f31;
    float var_f29;
    M427DllBss590Struct *var_r30;

    *arg3 = *arg2;
    arg4->x = arg4->y = arg4->z = 0.0f;
    if (arg0 < 0) {
        arg0 = fn_1_155E0(0.0f, 0.0f, arg2->z, &sp8);
    }
    if ((arg0 < 0) || (arg0 >= (lbl_1_bss_580 - 1))) {
        return 0;
    }
    var_r30 = &lbl_1_bss_590[arg0];
    sp3C.x = arg2->x - arg1->x;
    sp3C.y = arg2->y - arg1->y;
    sp3C.z = arg2->z - arg1->z;
    VECNormalize(&sp3C, &sp3C);
    spC.x = var_r30->unk_44.x + (sp8 * var_r30->unk_50);
    spC.y = var_r30->unk_44.y + (sp8 * var_r30->unk_54);
    spC.z = var_r30->unk_44.z + (sp8 * var_r30->unk_58);
    var_f29 = fabs(arg2->x - spC.x);
    if (arg2->x < spC.x) {
        var_f31 = var_r30->unk_5C + (sp8 * (var_r30->unk_64 - var_r30->unk_5C));
        if (var_f29 > var_f31) {
            sp30 = *arg2;
            fn_1_17048(var_r30->unk_14, NULL, &sp30, &sp24);
            arg3->x = sp24.x;
            arg3->y = sp24.y;
            arg3->z = sp24.z;
            arg4->x = arg3->x - arg2->x;
            arg4->y = arg3->y - arg2->y;
            arg4->z = arg3->z - arg2->z;
            return 1;
        }
        goto block_18;
    }
    var_f31 = var_r30->unk_60 + (sp8 * (var_r30->unk_68 - var_r30->unk_60));
    if (var_f29 > var_f31) {
        sp30 = *arg2;
        fn_1_17048(var_r30->unk_2C, NULL, &sp30, &sp18);
        arg3->x = sp18.x;
        arg3->y = sp18.y;
        arg3->z = sp18.z;
        arg4->x = arg3->x - arg2->x;
        arg4->y = arg3->y - arg2->y;
        arg4->z = arg3->z - arg2->z;
        return 1;
    }
block_18:
    return 0;
}

s32 fn_1_15F10(Vec arg0, Vec arg1, s32 arg2, s32 arg3, s32 arg4)
{
    M427DllBss57CStruct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_57C, var_r30 = 0; var_r30 < 0x40; var_r30++, var_r31++) {
        if ((var_r31->unk_04 < 0) || (var_r31->unk_08 < 0)) {
            break;
        }
    }
    if (var_r30 >= 0x40) {
        return -1;
    }
    var_r31->unk_04 = arg2;
    var_r31->unk_08 = 0;
    var_r31->unk_0C = 0;
    var_r31->unk_10 = arg4;
    var_r31->unk_18 = arg3;
    var_r31->unk_14 = 0;
    var_r31->unk_1C = arg0;
    var_r31->unk_28 = arg1;
    return var_r30;
}

s32 fn_1_15FD0(Vec arg0, float arg8, s32 arg1, s32 arg2, s32 arg3)
{
    M427DllBss57CStruct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_57C, var_r30 = 0; var_r30 < 0x40; var_r30++, var_r31++) {
        if ((var_r31->unk_04 < 0) || (var_r31->unk_08 < 0)) {
            break;
        }
    }
    if (var_r30 >= 0x40) {
        return -1;
    }
    var_r31->unk_04 = arg1;
    var_r31->unk_08 = 1;
    var_r31->unk_0C = 0;
    var_r31->unk_10 = arg3;
    var_r31->unk_18 = arg2;
    var_r31->unk_14 = 0;
    var_r31->unk_1C = arg0;
    var_r31->unk_34 = arg8;
    return var_r30;
}

void fn_1_1607C(s32 arg0)
{
    M427DllBss57CStruct *var_r31;

    if ((arg0 < 0) || (arg0 >= 0x40)) {
        return;
    }
    var_r31 = &lbl_1_bss_57C[arg0];
    var_r31->unk_04 = -1;
    var_r31->unk_08 = -1;
    var_r31->unk_14 = var_r31->unk_18 = 0;
}

s32 fn_1_160D4(s32 arg0, Vec *arg1, float arg8)
{
    float var_f31;
    float var_f30;
    float var_f29;
    M427DllBss57CStruct *var_r31;
    s32 var_r30;

    for (var_r31 = lbl_1_bss_57C, var_r30 = 0; var_r30 < 0x40; var_r30++, var_r31++) {
        if ((var_r31->unk_04 >= 0) && (var_r31->unk_08 >= 0) && (var_r31->unk_10 == arg0) && ((var_r31->unk_04 == 1) || (var_r31->unk_04 == 2))) {
            switch (var_r31->unk_08) {
                case 0:
                    var_f31 = arg1->x - var_r31->unk_1C.x;
                    var_f30 = arg1->z - var_r31->unk_1C.z;
                    if ((arg1->x >= (var_r31->unk_1C.x - arg8)) && (arg1->x <= (var_r31->unk_28.x + arg8)) && (arg1->z >= (var_r31->unk_1C.z - arg8))
                        && (arg1->z <= (var_r31->unk_28.z + arg8))) {
                        return 1;
                    }
                    break;
                case 1:
                    var_f31 = arg1->x - var_r31->unk_1C.x;
                    var_f30 = arg1->z - var_r31->unk_1C.z;
                    var_f29 = var_r31->unk_34 + arg8;
                    if (((var_f31 * var_f31) + (var_f30 * var_f30)) < (var_f29 * var_f29)) {
                        return 1;
                    }
                    break;
            }
        }
    }
    return 0;
}

s32 fn_1_16260(s32 arg0, Vec *arg2, Vec *arg3, Vec *arg4, float arg8)
{
    float var_f31;
    float var_f30;
    float var_f28;
    M427DllBss57CStruct *var_r31;
    s32 var_r30;

    *arg4 = *arg3;
    for (var_r31 = lbl_1_bss_57C, var_r30 = 0; var_r30 < 0x40; var_r30++, var_r31++) {
        if ((var_r31->unk_04 >= 0) && (var_r31->unk_08 >= 0) && (var_r31->unk_10 == arg0) && ((var_r31->unk_04 == 0) || (var_r31->unk_04 == 2))) {
            switch (var_r31->unk_08) {
                case 0:
                    var_f31 = arg3->x - var_r31->unk_1C.x;
                    var_f30 = arg3->z - var_r31->unk_1C.z;
                    if ((arg3->x >= (var_r31->unk_1C.x - arg8)) && (arg3->x <= (var_r31->unk_28.x + arg8)) && (arg3->z >= (var_r31->unk_1C.z - arg8))
                        && (arg3->z <= (var_r31->unk_28.z + arg8))) {
                        return 1;
                    }
                    break;
                case 1:
                    var_f31 = arg3->x - var_r31->unk_1C.x;
                    var_f30 = arg3->z - var_r31->unk_1C.z;
                    var_f28 = var_r31->unk_34 + arg8;
                    if (((var_f31 * var_f31) + (var_f30 * var_f30)) < (var_f28 * var_f28)) {
                        var_f28 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
                        if (var_f28 == 0.0f) {
                            var_f31 = 0.0f;
                            var_f30 = 1.0f;
                        }
                        else {
                            var_f31 /= var_f28;
                            var_f30 /= var_f28;
                        }
                        var_f28 = var_r31->unk_34 + arg8;
                        arg4->x = var_r31->unk_1C.x + (var_f31 * var_f28);
                        arg4->z = var_r31->unk_1C.z + (var_f30 * var_f28);
                        arg4->y = arg3->y;
                        return 1;
                    }
                    break;
            }
        }
    }
    return 0;
}

float fn_1_16594(float arg8, float arg9)
{
    float var_f31;

    if (arg8 >= 360.0f) {
        arg8 -= 360.0f;
    }
    else if (arg8 < 0.0f) {
        arg8 += 360.0f;
    }
    if (arg9 >= 360.0f) {
        arg9 -= 360.0f;
    }
    else if (arg9 < 0.0f) {
        arg9 += 360.0f;
    }
    var_f31 = arg8 - arg9;
    if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    }
    else if (var_f31 >= 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}

float fn_1_166AC(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;

    if (arg8 >= 360.0) {
        arg8 -= 360.0;
    }
    else if (arg8 < 0.0) {
        arg8 += 360.0;
    }
    if (arg9 >= 360.0) {
        arg9 -= 360.0;
    }
    else if (arg9 < 0.0) {
        arg9 += 360.0;
    }
    var_f30 = 360.0 + (arg8 - arg9);
    if (fabs(var_f30) >= 360.0) {
        var_f30 = fmod(var_f30, 360.0);
    }
    if (var_f30 < 180.0) {
        if (var_f30 <= argA) {
            var_f31 = var_f30;
        }
        else {
            var_f31 = argA;
        }
    }
    else if ((360.0 - var_f30) <= argA) {
        var_f31 = -(360.0 - var_f30);
    }
    else {
        var_f31 = -argA;
    }
    var_f31 += arg9;
    if (var_f31 >= 360.0) {
        var_f31 -= 360.0;
    }
    else if (var_f31 < 0.0) {
        var_f31 += 360.0;
    }
    return var_f31;
}

float fn_1_168FC(float arg8, float arg9, float argA)
{
    float var_f24;
    float var_f23;

    var_f23 = fn_1_16594(argA, arg9);
    var_f24 = fabs(var_f23 * arg8);
    return fn_1_166AC(argA, arg9, var_f24);
}

void fn_1_16CF4(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    Vec sp14;
    Vec sp8;

    sp14.x = arg1->x - arg0->x;
    sp14.y = arg1->y - arg0->y;
    sp14.z = arg1->z - arg0->z;
    sp8.x = arg2->x - arg0->x;
    sp8.y = arg2->y - arg0->y;
    sp8.z = arg2->z - arg0->z;
    arg3->x = (sp14.y * sp8.z) - (sp14.z * sp8.y);
    arg3->y = (sp14.z * sp8.x) - (sp14.x * sp8.z);
    arg3->z = (sp14.x * sp8.y) - (sp14.y * sp8.x);
    VECNormalize(arg3, arg3);
    arg3[1].x = (arg3->z * arg0->z) + ((arg3->x * arg0->x) + (arg3->y * arg0->y));
}

void fn_1_16E3C(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3)
{
    Vec spC;

    spC.x = arg1->x - arg0->x;
    spC.y = arg1->y - arg0->y;
    spC.z = arg1->z - arg0->z;
    if (arg3 != 0) {
        VECNormalize(&spC, &spC);
    }
    arg2->x = arg0->x;
    arg2->y = arg0->y;
    arg2->z = arg0->z;
    arg2[1].x = spC.x;
    arg2[1].y = spC.y;
    arg2[1].z = spC.z;
}

void fn_1_16EF8(Vec *arg0, float *arg1, Vec *arg2, Vec *arg3)
{
    float var_f31;
    float var_f30;
    float var_f29;

    var_f30 = (arg0[1].z * arg0[1].z) + ((arg0[1].x * arg0[1].x) + (arg0[1].y * arg0[1].y));
    var_f29 = (-arg0[0].z * arg0[1].z) + (arg2->z * arg0[1].z)
        + ((-arg0[0].x * arg0[1].x) + (arg2->x * arg0[1].x) + ((-arg0[0].y * arg0[1].y) + (arg2->y * arg0[1].y)));
    if (var_f30 != 0.0f) {
        var_f31 = var_f29 / var_f30;
    }
    else {
        var_f31 = 0.0f;
    }
    if (arg3 != NULL) {
        arg3->x = arg0[0].x + (var_f31 * arg0[1].x);
        arg3->y = arg0[0].y + (var_f31 * arg0[1].y);
        arg3->z = arg0[0].z + (var_f31 * arg0[1].z);
    }
    if (arg1 != NULL) {
        *arg1 = var_f31;
    }
}

typedef struct Vec3d {
    double x;
    double y;
    double z;
} Vec3d;

void fn_1_17048(Vec *arg0, float *arg1, Vec *arg2, Vec *arg3)
{
    Vec3d sp38;
    Vec3d sp20;
    Vec3d sp8;
    double var_f31;
    double var_f30;
    double var_f29;

    sp20.x = 0.0;
    sp20.y = 0.0;
    sp20.z = 0.0;
    sp38.x = arg0[1].x;
    sp38.y = arg0[1].y;
    sp38.z = arg0[1].z;
    sp8.x = arg2->x - arg0->x;
    sp8.y = arg2->y - arg0->y;
    sp8.z = arg2->z - arg0->z;

    var_f30 = (sp38.z * arg0[1].z) + ((sp38.x * arg0[1].x) + (sp38.y * arg0[1].y));
    var_f29 = (-sp20.z * sp38.z) + (sp8.z * sp38.z) + ((-sp20.x * sp38.x) + (sp8.x * sp38.x) + ((-sp20.y * sp38.y) + (sp8.y * sp38.y)));
    if (0.0 != var_f30) {
        var_f31 = var_f29 / var_f30;
    }
    else {
        var_f31 = 0.0;
    }
    if (arg3 != NULL) {
        arg3->x = arg0->x + (float)(sp20.x + (var_f31 * sp38.x));
        arg3->y = arg0->y + (float)(sp20.y + (var_f31 * sp38.y));
        arg3->z = arg0->z + (float)(sp20.z + (var_f31 * sp38.z));
    }
    if (arg1 != NULL) {
        *arg1 = var_f31;
    }
}

void fn_1_17238(void) { }

void fn_1_1723C(Mtx arg0, Vec *arg1)
{
    Vec sp8;

    sp8.x = (arg0[0][2] * arg1->z) + ((arg0[0][0] * arg1->x) + (arg0[0][1] * arg1->y));
    sp8.y = (arg0[1][2] * arg1->z) + ((arg0[1][0] * arg1->x) + (arg0[1][1] * arg1->y));
    sp8.z = (arg0[2][2] * arg1->z) + ((arg0[2][0] * arg1->x) + (arg0[2][1] * arg1->y));
    *arg1 = sp8;
}

void fn_1_172F0(s32 arg0, float arg8)
{
    HsfMaterial *var_r31;
    s32 var_r30;
    HsfData *var_r29;
    s32 var_r28;
    ModelData *var_r27;
    s32 var_r26;

    var_r27 = &Hu3DData[arg0];
    var_r29 = var_r27->hsfData;
    var_r31 = var_r29->material;
    var_r26 = var_r29->materialCnt;
    for (var_r28 = 0; var_r28 < var_r26; var_r28++, var_r31++) {
        var_r31->vtxMode = 1;
        var_r30 = var_r31->litColor[0] * arg8;
        if (var_r30 > 0xFF) {
            var_r30 = 0xFF;
        }
        var_r31->litColor[0] = var_r30;
        var_r30 = var_r31->litColor[1] * arg8;
        if (var_r30 > 0xFF) {
            var_r30 = 0xFF;
        }
        var_r31->litColor[1] = var_r30;
        var_r30 = var_r31->litColor[2] * arg8;
        if (var_r30 > 0xFF) {
            var_r30 = 0xFF;
        }
        var_r31->litColor[2] = var_r30;
    }
}

s32 fn_1_17430(s32 arg0, s32 arg1, s32 arg2)
{
    s32 var_r31;
    ModelData *var_r30;
    ModelData *var_r29;

    var_r29 = &Hu3DData[arg0];
    var_r30 = &Hu3DData[arg2];
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        if (var_r30->unk_38[var_r31] == -1) {
            break;
        }
    }
    if (var_r31 == 8) {
        return -1;
    }
    var_r30->unk_38[var_r31] = var_r29->unk_38[arg1];
    var_r30->attr |= 0x1000;
    return var_r31;
}
