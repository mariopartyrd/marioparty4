#include "ext_math.h"
#include "game/audio.h"
#include "game/gamework.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/wipe.h"
#include "string.h"

#include "REL/m421Dll.h"

#ifndef __MWERKS__
#include "game/frand.h"
#endif

typedef struct M421DllWork {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u32 unk_0C;
    s32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk24;
    u32 unk_28;
    u32 unk_2C;
    s32 unk_30[4];
    s32 unk_40[4];
    s32 unk_50[4];
    u32 unk_60;
    u32 unk_64;
    u32 unk_68;
    u32 unk_6C;
    s32 unk_70;
} M421DllWork; /* size = 0x74 */

void fn_1_10EC(omObjData *object);
void fn_1_142C(omObjData *object);
void fn_1_1850(omObjData *object);
void fn_1_1C90(omObjData *object);
omObjFunc fn_1_213C(Process *process, omObjData *object);
void fn_1_21AC(omObjData *object);
omObjFunc fn_1_2A28(Process *process, omObjData *object);
void fn_1_2BB8(omObjData *object);
void fn_1_3020(Process *process);
void fn_1_30D0(omObjData *object);
void fn_1_3334(omObjData *object);
void fn_1_335C(omObjData *object);
void fn_1_38FC(ModelData *model, Mtx mtx);
void fn_1_3B50(u32 arg0);
M421DllCameraStruct *fn_1_3B78(s32 arg0);
M421DllCameraStruct *fn_1_3CB0(u32 arg0);
float fn_1_4478(float arg8, float arg9, float argA);
void fn_1_4A0(omObjData *object);
void fn_1_784(omObjData *object);
void fn_1_8B8(omObjData *object);
void fn_1_CBC(omObjData *object);

Vec lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };
Vec lbl_1_data_C = { 0.3f, -0.8f, 0.3f };
Vec lbl_1_data_18 = { 10.0f, 45.0f, 3500.0f };
GXColor lbl_1_data_24 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_28 = { 50.0f, 150000.0f, 50.0f };
Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_40 = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_4C[3] = {
    { 0.0f, 200.0f, -50.0f },
    { 0.0f, 200.0f, -50.0f },
    { 0.0f, 200.0f, -50.0f },
};
Vec lbl_1_data_70[3] = {
    { -37.5f, 0.0f, 1500.0f },
    { -37.5f, 0.0f, 1500.0f },
    { -37.5f, 0.0f, 2300.0f },
};
s32 lbl_1_data_94[3] = { 0xF0, 0x1E, 0 };
GXColor lbl_1_data_A0 = { 0, 0, 0, 0 };

Process *lbl_1_bss_28;
omObjData *lbl_1_bss_24;
omObjData *lbl_1_bss_20;
// M421DllCameraStruct
omObjData *lbl_1_bss_1C;
s16 lbl_1_bss_18;
s16 lbl_1_bss_12[3];
s16 lbl_1_bss_10;
s16 lbl_1_bss_E;
s16 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    Mtx sp2C;
    Vec sp20 = { 0.0f, 0.0f, 0.0f };
    Vec sp14 = { 0.0f, 0.0f, -1.0f };
    Vec sp8;
    Process *process;
    LightData *lightData;

    lbl_1_bss_8 = 0;
    HuAudSndGrpSet(0x2E);
    HuAudFXListnerSetEX(&sp20, &sp14, 11200.0f, 4166.6665f, 0.0f, 300.0f, 0.0f);
    lbl_1_bss_4 = lbl_1_bss_0 = -1;
    lbl_1_bss_18 = -1;
    lbl_1_data_28.x = 200.0f;
    lbl_1_data_28.y = 1200.0f;
    lbl_1_data_28.z = 160.0f;
    lbl_1_data_34.x = 0.0f;
    lbl_1_data_34.y = 1.0f;
    lbl_1_data_34.z = 0.0f;
    lbl_1_data_40.x = 0.0f;
    lbl_1_data_40.y = 0.0f;
    lbl_1_data_40.z = 0.0f;
    Hu3DShadowCreate(22.0f, 20.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.625f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    lbl_1_bss_12[0] = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_12[0]);
    lightData = &Hu3DGlobalLight[lbl_1_bss_12[0]];
    lightData->unk_00 |= 0x8000;
    lbl_1_data_18.x = 1.0f;
    lbl_1_data_18.y = 0.0f;
    lbl_1_data_18.z = 4200.0f;
    sp8.x = sp8.z = 0.0f;
    sp8.y = lbl_1_data_18.z;
    mtxRot(sp2C, lbl_1_data_18.x, lbl_1_data_18.y, 0.0f);
    MTXMultVec(sp2C, &sp8, &lbl_1_data_28);
    Hu3DGLightPosAimSetV(lbl_1_bss_12[0], &lbl_1_data_28, &lbl_1_data_40);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    lbl_1_bss_10 = lbl_1_bss_E = lbl_1_bss_C = -1;
    process = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_28 = process;
    omGameSysInit(process);
    fn_1_3020(process);
    lbl_1_bss_24 = omAddObjEx(process, 0xA, 0, 0, -1, fn_1_4A0);
    fn_1_B15C(process);
    fn_1_4648(process);
}

void fn_1_4A0(omObjData *object)
{
    M421DllWork *work;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M421DllWork), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, sizeof(M421DllWork));
    work->unk_00 = 0;
    work->unk_04 = 0;
    work->unk_0C = 0;
    work->unk_10 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->unk_28 = 0;
    work->unk_2C = 0;
    work->unk_08 = 0;
    work->unk_64 = 2;
    work->unk_50[0] = work->unk_50[1] = work->unk_50[2] = work->unk_50[3] = -1;
    work->unk_68 = 0;
    work->unk_70 = 0;
    object->func = fn_1_8B8;
}

void fn_1_578(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    M421DllCameraStruct *var_r31;

    M421DllWork *work = object->data;
    work->unk_04++;
    work->unk_10++;
    work->unk_18++;
    work->unk_2C++;
    if ((omSysExitReq != 0) && (work->unk_00 != 5)) {
        work->unk_00 = 4;
        fn_1_784(object);
    }
    var_r31 = fn_1_3B78(1);
    sp8.x = -(sind(var_r31->unk_28.y) * cosd(var_r31->unk_28.x));
    sp8.y = -(-sind(var_r31->unk_28.x));
    sp8.z = -(cosd(var_r31->unk_28.y) * cosd(var_r31->unk_28.x));
    sp14.x = var_r31->unk_1C.x - (sp8.x * var_r31->unk_34);
    sp14.y = var_r31->unk_1C.y - (sp8.y * var_r31->unk_34);
    sp14.z = var_r31->unk_1C.z - (sp8.z * var_r31->unk_34);
    HuAudFXListnerUpdate(&sp14, &sp8);
}

void fn_1_784(omObjData *object)
{
    M421DllWork *work = object->data;

    if (work->unk_08 == 0) {
        switch (work->unk_00) {
            case 0:
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 0x3C);
                work->unk_00 = 1;
                work->unk_10 = 0;
                object->func = fn_1_213C(lbl_1_bss_28, object);
                break;
            case 1:
                work->unk_00 = 2;
                work->unk_18 = 0;
                object->func = fn_1_142C;
                break;
            case 2:
                work->unk_00 = 3;
                work->unk_2C = 0;
                object->func = fn_1_2A28(lbl_1_bss_28, object);
                break;
            case 3:
            case 4:
                work->unk_08 = 1;
                work->unk_00 = 5;
                object->func = fn_1_CBC;
                break;
            case 5:
            default:
                work->unk_00 = 5;
                object->func = fn_1_10EC;
        }
        work->unk_04 = 0;
    }
}

void fn_1_8B8(omObjData *object)
{
    fn_1_578(object);
    fn_1_784(object);
}

void fn_1_CBC(omObjData *object)
{
    M421DllWork *work = object->data;
    fn_1_578(object);
    if (WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
        work->unk_08 = 0;
        fn_1_784(object);
    }
}

void fn_1_10EC(omObjData *object)
{
    fn_1_578(object);
    if (WipeStatGet() == 0) {
        fn_1_48B0();
        fn_1_B1BC();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_142C(omObjData *object)
{
    M421DllWork *work = object->data;
    fn_1_578(object);
    switch (work->unk_14) {
        case 0:
            work->unk_1C = 0x2D;
            work->unk_20 = 0x3C;
            lbl_1_bss_10 = MGSeqCreate(3, 0);
            MGSeqPosSet(lbl_1_bss_10, 320.0f, 240.0f);
            lbl_1_bss_18 = -1;
            work->unk_14 = 1;
            work->unk_18 = 0;
            break;
        case 1:
            if ((lbl_1_bss_4 < 0) && ((MGSeqStatGet(lbl_1_bss_10) & 0x10) != 0)) {
                lbl_1_bss_4 = HuAudSeqPlay(0x48);
            }
            if (MGSeqStatGet(lbl_1_bss_10) == 0 && (work->unk_08 == 0)) {
                work->unk_14 = 2;
                work->unk_18 = 0;
                object->func = fn_1_1850;
            }
            break;
    }
}

void fn_1_1850(omObjData *object)
{
    M421DllWork *work = object->data;
    s32 var_r26 = 0;
    fn_1_578(object);
    if (--work->unk_20 == 0) {
        work->unk_20 = 0x3C;
        work->unk_1C--;
        if ((work->unk_1C == 0) && (work->unk_64 == 2)) {
            work->unk_64 = 1;
            var_r26 = 1;
        }
    }
    if (lbl_1_bss_18 < 0) {
        lbl_1_bss_18 = MGSeqCreate(1, work->unk_1C, -1, -1);
    }
    MGSeqParamSet(lbl_1_bss_18, 1, work->unk_1C);
    if (work->unk_64 != 2) {
        var_r26 = 1;
    }
    if (var_r26 != 0) {
        lbl_1_bss_E = MGSeqCreate(3, 1);
        MGSeqPosSet(lbl_1_bss_E, 320.0f, 240.0f);
        HuAudSeqFadeOut(lbl_1_bss_4, 0x64);
        work->unk_14 = 3;
        work->unk_18 = 0;
        if (work->unk_08 == 0) {
            object->func = fn_1_1C90;
        }
    }
}

void fn_1_1C90(omObjData *object)
{
    M421DllWork *work = object->data;
    s32 var_r25 = 0;
    if (lbl_1_bss_18 >= 0) {
        MGSeqParamSet(lbl_1_bss_18, 2, -1);
        lbl_1_bss_18 = -1;
    }
    fn_1_578(object);
    if (work->unk_14 == 3) {
        var_r25 = 1;
        if ((MGSeqStatGet(lbl_1_bss_E) == 0) && (work->unk_68 == 0x1111) && (var_r25 != 0)) {
            work->unk_14 = 4;
            work->unk_18 = 0;
        }
    }
    else {
        work->unk_14 = 5;
        work->unk_18 = 0;
        fn_1_784(object);
    }
}

omObjFunc fn_1_213C(Process *process, omObjData *object)
{
    M421DllCameraStruct *var_r31;

    object->work[0] = object->work[1] = 0;
    fn_1_3B50(1);
    var_r31 = fn_1_3CB0(0);
    var_r31->unk_84 = 1.0f;
    var_r31->unk_94 = 0;
    return fn_1_21AC;
}

void fn_1_21AC(omObjData *object)
{
    Vec sp20;
    float var_f31;
    M421DllCameraStruct *var_r30;
    M421DllWork *work;

    work = object->data;
    fn_1_578(object);
    work->unk_0C = 1;
    object->work[0]++;
    var_f31 = (float)object->work[0] / lbl_1_data_94[object->work[1]];
    VECSubtract(&lbl_1_data_4C[object->work[1] + 1], &lbl_1_data_4C[object->work[1]], &sp20);
    VECScale(&sp20, &sp20, var_f31);
    VECAdd(&lbl_1_data_4C[object->work[1]], &sp20, &sp20);
    Center.x = sp20.x;
    Center.y = sp20.y;
    Center.z = sp20.z;
    VECSubtract(&lbl_1_data_70[object->work[1] + 1], &lbl_1_data_70[object->work[1]], &sp20);
    VECScale(&sp20, &sp20, var_f31);
    VECAdd(&lbl_1_data_70[object->work[1]], &sp20, &sp20);
    CRot.x = sp20.x;
    CRot.y = sp20.y;
    CRot.z = 0.0f;
    CZoom = sp20.z;
    var_r30 = fn_1_3CB0(0);
    var_r30->unk_1C = Center;
    var_r30->unk_28 = CRot;
    var_r30->unk_34 = CZoom;
    var_r30->unk_94++;
    if (var_r30->unk_94 > 180.0f) {
        var_r30->unk_84 -= 0.025000002f;
        if (var_r30->unk_84 < 0.0f) {
            var_r30->unk_84 = 0.0f;
        }
        var_r30->unk_1C.x += var_r30->unk_84 * ((0.02f * frandmod(0x3E8)) - 10.0f);
        var_r30->unk_1C.y += var_r30->unk_84 * ((0.02f * frandmod(0x3E8)) - 10.0f);
        var_r30->unk_1C.z += var_r30->unk_84 * ((0.02f * frandmod(0x3E8)) - 10.0f);
    }
    if (var_f31 >= 1.0f) {
        object->work[0] = 0;
        object->work[1]++;
        if (lbl_1_data_94[object->work[1]] == 0) {
            work->unk_0C = 2;
            fn_1_784(object);
        }
    }
}

omObjFunc fn_1_2A28(Process *process, omObjData *object)
{
    M421DllCameraStruct *var_r31;
    s32 var_r30;
    M421DllWork *var_r29;
    s32 var_r28;

    var_r29 = object->data;
    var_r28 = 1;
    var_r31 = fn_1_3CB0(0);
    if (var_r29->unk_64 == 1) {
        var_r28 = 0;
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r29->unk_50[var_r30] = -1;
        if ((var_r29->unk_40[var_r30] == 0) == var_r28) {
            var_r29->unk_50[var_r30] = var_r29->unk_30[var_r30];
        }
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        if (var_r29->unk_50[var_r30] >= 0) {
            GWPlayerCoinWinAdd(var_r30, 10);
        }
    }
    var_r31->unk_54 = 0.0f;
    var_r31->unk_58 = 150.0f;
    var_r31->unk_5C = 0.0f;
    var_r31->unk_60 = -30.0f;
    var_r31->unk_64 = 0.0f;
    var_r31->unk_68 = 1000.0f;
    var_r31->unk_84 = 0.0f;
    return fn_1_2BB8;
}

void fn_1_2BB8(omObjData *var_r29)
{
    M421DllCameraStruct *var_r31;
    M421DllWork *var_r28;

    var_r28 = var_r29->data;
    var_r31 = fn_1_3CB0(0);
    fn_1_578(var_r29);
    var_r31->unk_84 += 0.0016666668f;
    if (var_r31->unk_84 > 0.1f) {
        var_r31->unk_84 = 0.1f;
    }
    var_r31->unk_1C.y += var_r31->unk_84 * (var_r31->unk_58 - var_r31->unk_1C.y);
    var_r31->unk_1C.z += var_r31->unk_84 * (var_r31->unk_5C - var_r31->unk_1C.z);
    var_r31->unk_28.x = fn_1_4478(var_r31->unk_28.x, var_r31->unk_60, var_r31->unk_84);
    var_r31->unk_34 += var_r31->unk_84 * (var_r31->unk_68 - var_r31->unk_34);
    if (var_r28->unk_6C == 0x1111) {
        var_r28->unk_28 = 1;
        if (lbl_1_bss_0 < 0) {
            lbl_1_bss_0 = HuAudSStreamPlay(1);
        }
        if (lbl_1_bss_C < 0) {
            lbl_1_bss_C = MGSeqCreate(5, 3, var_r28->unk_50[0], var_r28->unk_50[1], var_r28->unk_50[2], var_r28->unk_50[3]);
            return;
        }
        if ((MGSeqStatGet(lbl_1_bss_C) == 0) && (var_r28->unk_2C >= 210.0f)) {
            var_r28->unk_28 = 2;
            fn_1_784(var_r29);
        }
    }
}

void fn_1_3020(Process *process)
{
    Hu3DCameraCreate(0x1F);
    lbl_1_bss_20 = omAddObjEx(process, 0x7FDA, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_20->work[0] = 5;
    lbl_1_bss_1C = omAddObjEx(process, 0xC, 1, 0, -1, fn_1_30D0);
    lbl_1_bss_1C->work[0] = 0;
}

void fn_1_30D0(omObjData *object)
{
    UnkM421DllStruct sp1C[5] = {
        { 320.0f, 240.0f, 640.0f, 480.0f },
        { 160.0f, 120.0f, 320.0f, 240.0f },
        { 160.0f, 360.0f, 320.0f, 240.0f },
        { 480.0f, 120.0f, 320.0f, 240.0f },
        { 480.0f, 360.0f, 320.0f, 240.0f },
    };
    s32 sp8[5] = { 1, 2, 4, 8, 16 };
    M421DllCameraStruct *var_r31;
    s32 var_r29;
    M421DllCameraStruct *var_r28;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 10 * sizeof(M421DllCameraStruct), MEMORY_DEFAULT_NUM);
    var_r28 = object->data;
    memset(var_r28, 0, 10 * sizeof(M421DllCameraStruct));
    object->model[0] = Hu3DHookFuncCreate(fn_1_38FC);
    Hu3DModelLayerSet(object->model[0], 0);
    Hu3DModelCameraSet(object->model[0], 0x1E);
    for (var_r31 = var_r28, var_r29 = 0; var_r29 < 5; var_r29++, var_r31++) {
        var_r31->unk_00 = 1;
        var_r31->unk_04 = var_r29 * 0x64;
        var_r31->unk_10 = 41.5f;
        var_r31->unk_14 = 100.0f;
        var_r31->unk_18 = 5500.0f;
        var_r31->unk_1C.x = 0.0f;
        var_r31->unk_1C.y = 0.0f;
        var_r31->unk_1C.z = 0.0f;
        var_r31->unk_28.x = -15.0f;
        var_r31->unk_28.y = 0.0f;
        var_r31->unk_28.z = 0.0f;
        var_r31->unk_34 = 1000.0f;
        var_r31->unk_40 = 1.0f;
        var_r31->unk_44.unk_00 = sp1C[var_r29].unk_00;
        var_r31->unk_44.unk_04 = sp1C[var_r29].unk_04;
        var_r31->unk_44.unk_08 = sp1C[var_r29].unk_08;
        var_r31->unk_44.unk_0C = sp1C[var_r29].unk_0C;
        var_r31->unk_3C = var_r31->unk_0C = sp8[var_r29];
        var_r31->unk_08 = var_r29;
        var_r31->unk_38 = var_r29;
    }
    object->work[1] = 0;
    object->work[0]++;
    fn_1_335C(object);
    object->func = fn_1_3334;
}

void fn_1_3334(omObjData *object)
{
    fn_1_335C(object);
}

void fn_1_335C(omObjData *object)
{
    float var_f31;
    M421DllCameraStruct *var_r31;
    s32 var_r30;
    s32 var_r29;
    M421DllCameraStruct *var_r27;
    u32 var_r26;
    u32 var_r25;
    s32 var_r24;
    u32 var_r23;
    u32 var_r22;
    u32 var_r21;

    var_r27 = object->data;
    {
        s32 sp40[4] = { 2, 4, 8, 16 };
        u32 sp30[4];
        s32 sp20[4];
        float sp10[4];
        float sp8[2];
        var_r24 = 0;
        var_r26 = 0;
        memcpy(&var_r27[5], var_r27, 5 * sizeof(M421DllCameraStruct));
        switch (object->work[1]) {
            case 0:
                break;
            case 1:
                var_r26 |= 1;
                break;
            case 2:
                var_r26 |= 1;
            case 3:
                var_r24 = 1;
            case 4:
                var_r26 |= 0x1E;
                break;
        }
        if (var_r24 != 0) {
            Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            sp30[var_r30] = var_r27[var_r30 + 6].unk_04;
            sp20[var_r30] = var_r30;
        }
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            for (var_r29 = var_r30 + 1; var_r29 < 4; var_r29++) {
                if ((var_r30 != var_r29) && (sp30[var_r30] > sp30[var_r29])) {
                    var_r25 = sp30[var_r30];
                    sp30[var_r30] = sp30[var_r29];
                    sp30[var_r29] = var_r25;
                    var_r25 = sp20[var_r30];
                    sp20[var_r30] = sp20[var_r29];
                    sp20[var_r29] = var_r25;
                }
            }
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            var_r27[sp20[var_r30] + 6].unk_3C = sp40[var_r30];
            var_r27[sp20[var_r30] + 6].unk_38 = var_r30 + 1;
        }

        for (var_r31 = &var_r27[5], var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
            if ((var_r31->unk_00 == 0) || ((var_r26 & var_r31->unk_0C) == 0)) {
                Hu3DCamera[var_r31->unk_38].fov = -1.0f;
            }
            else {
                var_f31 = 1.2f * ((var_r31->unk_44.unk_08 / 640.0f) / (var_r31->unk_44.unk_0C / 480.0f));
                sp10[2] = var_r31->unk_44.unk_08 * var_r31->unk_40;
                sp10[3] = var_r31->unk_44.unk_0C * var_r31->unk_40;
                Hu3DCameraPerspectiveSet(var_r31->unk_3C, var_r31->unk_10, var_r31->unk_14, var_r31->unk_18, var_f31);
                Hu3DCameraViewportSet(var_r31->unk_3C, var_r31->unk_44.unk_00 - (0.5f * sp10[2]), var_r31->unk_44.unk_04 - (0.5f * sp10[3]), sp10[2],
                    sp10[3], 0.0f, 1.0f);
                sp10[0] = var_r31->unk_44.unk_00 - (0.5f * sp10[2]);
                sp10[1] = var_r31->unk_44.unk_04 - (0.5f * sp10[3]);
                sp8[0] = var_r31->unk_44.unk_00 + (0.5f * sp10[2]);
                sp8[1] = var_r31->unk_44.unk_04 + (0.5f * sp10[3]);
                if (sp10[0] < 0.0f) {
                    sp10[0] = 0.0f;
                }
                if (sp10[1] < 0.0f) {
                    sp10[1] = 0.0f;
                }
                if (sp8[0] > 640.0f) {
                    sp8[0] = 640.0f;
                }
                if (sp8[1] > 480.0f) {
                    sp8[1] = 480.0f;
                }
                sp8[0] -= sp10[0];
                sp8[1] -= sp10[1];
                var_r21 = sp8[1];
                var_r22 = sp8[0];
                var_r23 = sp10[1];
                Hu3DCameraScissorSet(var_r31->unk_3C, sp10[0], var_r23, var_r22, var_r21);
                var_r29 = var_r31->unk_38;
                CenterM[var_r29].x = var_r31->unk_1C.x;
                CenterM[var_r29].y = var_r31->unk_1C.y;
                CenterM[var_r29].z = var_r31->unk_1C.z;
                CRotM[var_r29].x = var_r31->unk_28.x;
                CRotM[var_r29].y = var_r31->unk_28.y;
                CRotM[var_r29].z = var_r31->unk_28.z;
                CZoomM[var_r29] = var_r31->unk_34;
            }
        }
    }
}

void fn_1_38FC(ModelData *model, Mtx mtx)
{
    Mtx spC;
    float var_f31;
    float var_f30;
    float var_f29;

    MTXIdentity(spC);
    GXLoadPosMtxImm(spC, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, lbl_1_data_A0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    var_f31 = 4125.0f;
    var_f30 = 2750.0f;
    var_f29 = 5494.5f;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-var_f31, var_f30, -var_f29);
    GXPosition3f32(var_f31, var_f30, -var_f29);
    GXPosition3f32(var_f31, -var_f30, -var_f29);
    GXPosition3f32(-var_f31, -var_f30, -var_f29);
    GXEnd();
}

void fn_1_3B50(u32 arg0)
{
    lbl_1_bss_1C->work[1] = arg0;
}

u32 fn_1_3B64(void)
{
    return lbl_1_bss_1C->work[1];
}

M421DllCameraStruct *fn_1_3B78(s32 arg0)
{
    M421DllCameraStruct *var_r31;
    s32 var_r30;
    M421DllCameraStruct *var_r29;

    var_r29 = lbl_1_bss_1C->data;
    for (var_r31 = var_r29, var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
        if ((var_r31->unk_0C & arg0) != 0) {
            break;
        }
    }
    if (var_r30 >= 5) {
        OSReport("M421:Camera Flag Error!!\n");
        return NULL;
    }
    return var_r31;
}

M421DllCameraStruct *fn_1_3C14(s32 arg0)
{
    M421DllCameraStruct *var_r31;
    s32 var_r30;
    M421DllCameraStruct *var_r29;

    var_r29 = lbl_1_bss_1C->data;
    for (var_r31 = &var_r29[5], var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
        if ((var_r31->unk_0C & arg0) != 0) {
            break;
        }
    }
    if (var_r30 >= 5) {
        OSReport("M421:Camera Flag Error!!\n");
        return NULL;
    }
    return var_r31;
}

M421DllCameraStruct *fn_1_3CB0(u32 arg0)
{
    M421DllCameraStruct *var_r31 = lbl_1_bss_1C->data;
    if (arg0 >= 5) {
        OSReport("M421:Camera No. Error!!\n");
        return NULL;
    }
    return &var_r31[arg0];
}

M421DllCameraStruct *fn_1_3D18(u32 arg0)
{
    M421DllCameraStruct *var_r31 = lbl_1_bss_1C->data;
    if (arg0 >= 5) {
        OSReport("M421:Camera No. Error!!\n");
        return NULL;
    }
    return &var_r31[arg0 + 5];
}

void fn_1_3D84(s32 arg0, s32 arg1)
{
    M421DllCameraStruct *var_r31;
    s32 var_r30;
    s32 var_r29;
    M421DllCameraStruct *var_r28;
    M421DllCameraStruct *var_r27;

    var_r29 = 0;
    if (arg0 >= 0) {
        var_r27 = lbl_1_bss_1C->data;
        var_r28 = &var_r27[5];
        for (var_r31 = var_r28, var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
            if ((var_r31->unk_0C & arg1) != 0) {
                var_r29 |= var_r31->unk_3C;
            }
        }
        Hu3DModelCameraSet(arg0, var_r29);
    }
}

s32 fn_1_3E1C(void)
{
    return ((M421DllWork *)lbl_1_bss_24->data)->unk_00;
}

u32 fn_1_3E34(void)
{
    return ((M421DllWork *)lbl_1_bss_24->data)->unk_0C;
}

u32 fn_1_3E4C(void)
{
    return ((M421DllWork *)lbl_1_bss_24->data)->unk_14;
}

u32 fn_1_3E64(void)
{
    return ((M421DllWork *)lbl_1_bss_24->data)->unk_28;
}

s32 fn_1_3E7C(s32 arg0)
{
    M421DllWork *work = lbl_1_bss_24->data;

    if (work->unk_64 != 2) {
        return 0;
    }
    work->unk_60 |= (1 << ((arg0 & 3) * 4));
    if (((work->unk_60 & 0x1110) == 0x1110) && (work->unk_64 == 2)) {
        work->unk_64 = 0;
    }
    return 1;
}

s32 fn_1_3EF8(s32 arg0)
{
    M421DllWork *work = lbl_1_bss_24->data;
    return work->unk_50[arg0];
}

void fn_1_3F28(s32 arg0, s32 arg1, s32 arg2)
{
    M421DllWork *work = lbl_1_bss_24->data;
    arg0 &= 3;
    work->unk_40[arg0] = arg1;
    work->unk_30[arg0] = arg2;
}

void fn_1_3F68(s32 arg0)
{
    ((M421DllWork *)lbl_1_bss_24->data)->unk_68 |= (1 << ((arg0 & 7) * 4));
}

void fn_1_3F98(s32 arg0)
{
    ((M421DllWork *)lbl_1_bss_24->data)->unk_6C |= (1 << ((arg0 & 3) * 4));
}

void fn_1_3FC8(s32 arg0)
{
    ((M421DllWork *)lbl_1_bss_24->data)->unk_70 |= (1 << ((arg0 & 3) * 4));
}

s32 fn_1_3FF8(void)
{
    return MGSeqStatGet(lbl_1_bss_E) == 0;
}

void fn_1_4030(Vec *sp8, Vec *var_r31)
{
    Vec sp10;

    VECSubtract(var_r31, sp8, &sp10);
    Center = *var_r31;
    CRot.x = atan2d(sp10.y, sqrtf((sp10.x * sp10.x) + (sp10.z * sp10.z)));
    CRot.y = atan2d(-sp10.x, -sp10.z);
    CRot.z = 0.0f;
    CZoom = VECMag(&sp10);
}

void fn_1_4238(float arg8, float arg9, float argA, float argB, float argC, float argD)
{
    Vec sp3C;
    Vec sp30;
    Vec sp24;

    sp3C.x = arg8;
    sp3C.y = arg9;
    sp3C.z = argA;
    sp30.x = argB;
    sp30.y = argC;
    sp30.z = argD;
    VECSubtract(&sp30, &sp3C, &sp24);
    Center = sp30;
    CRot.x = atan2d(sp24.y, sqrtf((sp24.x * sp24.x) + (sp24.z * sp24.z)));
    CRot.y = atan2d(-sp24.x, -sp24.z);
    CRot.z = 0.0f;
    CZoom = VECMag(&sp24);
}

float fn_1_4478(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;
    float var_f29;

    var_f30 = fmod(arg9 - arg8, 360.0);
    var_f31 = var_f30;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f29 = fmod(arg8 + (argA * var_f31), 360.0);
    var_f31 = var_f29;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    return var_f31;
}

float fn_1_4594(float arg8, float arg9)
{
    float var_f31;
    float var_f30;

    var_f30 = fmod(arg9 - arg8, 360.0);
    var_f31 = var_f30;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}
