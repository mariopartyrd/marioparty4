#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXVert.h"
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

#include "REL/m460Dll.h"

#ifndef __MWERKS__
#include "game/frand.h"
#endif

typedef struct M460DllWork {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u32 unk_0C;
    s32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    s32 unk_28;
    u32 unk_2C;
    s32 unk_30;
    char unk34[0x4];
    u32 unk_38;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    u32 unk_50;
    s32 unk_54[4];
    s32 unk_64[4];
    s32 unk_74;
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
    char unk84[4];
    s32 unk_88;
    u32 unk_8C;
    u32 unk_90;
    s32 unk_94;
} M460DllWork; /* size = 0x98 */

void fn_1_11EC(omObjData *object);
void fn_1_1548(omObjData *object);
void fn_1_197C(omObjData *object);
void fn_1_201C(omObjData *object);
omObjFunc fn_1_24F4(Process *arg1, omObjData *object);
void fn_1_2564(omObjData *object);
omObjFunc fn_1_2D64(Process *process, omObjData *object);
void fn_1_2D70(omObjData *object);
void fn_1_32CC(Process *process);
void fn_1_337C(omObjData *object);
void fn_1_35F0(omObjData *object);
void fn_1_3618(omObjData *object);
void fn_1_3BC0(ModelData *model, Mtx mtx);
M460DllCameraStruct *fn_1_3E90(s32 arg0);
M460DllCameraStruct *fn_1_3F2C(s32 arg0);
void fn_1_42BC(u32 arg0);
s32 fn_1_4358(void);
void fn_1_4C8(omObjData *object);
void fn_1_7FC(omObjData *object);
void fn_1_948(omObjData *object);
void fn_1_D7C(omObjData *object);

Vec lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };
Vec lbl_1_data_C = { 0.3f, -0.8f, 0.3f };
Vec lbl_1_data_18 = { 10.0f, 45.0f, 3500.0f };
GXColor lbl_1_data_24 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_28 = { 50.0f, 150000.0f, 50.0f };
Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_40 = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_4C[3] = {
    { 0.0f, 442.0f, -927.00006f },
    { 0.0f, 442.0f, -927.00006f },
    { 0.0f, 325.0f, -600.0f },
};
Vec lbl_1_data_70[3] = {
    { 4.5f, 0.0f, 450.0f },
    { 4.5f, 0.0f, 450.0f },
    { 9.75f, 0.0f, 1275.0f },
};
float lbl_1_data_94[3] = { 70.0f, 70.0f, 41.5f };
float lbl_1_data_A0[3] = { 0.0f, 0.016666668f, 0.0f };
s32 lbl_1_data_AC[3] = { -0x3C, 0x3C, 0 };
GXColor lbl_1_data_B8 = { 0, 0, 0, 0 };

Process *lbl_1_bss_30;
// M460DllWork2
omObjData *lbl_1_bss_2C;
omObjData *lbl_1_bss_28;
// M460DllWork2
omObjData *lbl_1_bss_24;
s16 lbl_1_bss_20;
s16 lbl_1_bss_1A[3];
s16 lbl_1_bss_18;
s16 lbl_1_bss_16;
s16 lbl_1_bss_14;
s16 lbl_1_bss_12;
s16 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    Mtx sp2C;
    Process *var_r31;
    LightData *var_r30;

    Vec sp20 = { 0.0f, 0.0f, 0.0f };
    Vec sp14 = { 0.0f, 0.0f, -1.0f };
    Vec sp8;

    lbl_1_bss_C = 0;
    HuAudSndGrpSet(0x53);
    HuAudFXListnerSetEX(&sp20, &sp14, 10000.0f, 566.6667f, 0.0f, 300.0f, 300.0f);
    lbl_1_bss_8 = lbl_1_bss_4 = -1;
    lbl_1_bss_20 = -1;
    lbl_1_bss_0 = 1;
    lbl_1_data_28.x = 200.0f;
    lbl_1_data_28.y = 1200.0f;
    lbl_1_data_28.z = 160.0f;
    lbl_1_data_34.x = 0.0f;
    lbl_1_data_34.y = 1.0f;
    lbl_1_data_34.z = 0.0f;
    lbl_1_data_40.x = 0.0f;
    lbl_1_data_40.y = 0.0f;
    lbl_1_data_40.z = 0.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.625f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    lbl_1_bss_1A[0] = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_1A[0]);
    var_r30 = &Hu3DGlobalLight[lbl_1_bss_1A[0]];
    var_r30->unk_00 |= 0x8000;
    lbl_1_data_18.x = 160.0f;
    lbl_1_data_18.y = 0.0f;
    lbl_1_data_18.z = 4200.0f;
    sp8.x = sp8.z = 0.0f;
    sp8.y = lbl_1_data_18.z;
    mtxRot(sp2C, lbl_1_data_18.x, lbl_1_data_18.y, 0.0f);
    MTXMultVec(sp2C, &sp8, &lbl_1_data_28);
    Hu3DGLightPosAimSetV(lbl_1_bss_1A[0], &lbl_1_data_28, &lbl_1_data_40);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    lbl_1_bss_18 = lbl_1_bss_16 = lbl_1_bss_14 = lbl_1_bss_12 = lbl_1_bss_10 = -1;
    var_r31 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_30 = var_r31;
    omGameSysInit(var_r31);
    fn_1_32CC(var_r31);
    lbl_1_bss_2C = omAddObjEx(var_r31, 0xA, 0, 0, -1, fn_1_4C8);
    fn_1_67B4(var_r31);
    fn_1_49A0(var_r31);
}

void fn_1_4C8(omObjData *var_r30)
{
    M460DllWork *work;

    var_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M460DllWork), MEMORY_DEFAULT_NUM);
    work = var_r30->data;
    memset(work, 0, sizeof(M460DllWork));
    work->unk_00 = 0;
    work->unk_04 = 0;
    work->unk_0C = 0;
    work->unk_10 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->unk_4C = 0;
    work->unk_50 = 0;
    work->unk_08 = 0;
    work->unk_88 = 0;
    work->unk_74 = work->unk_78 = work->unk_7C = work->unk_80 = -1;
    work->unk_8C = 0;
    work->unk_94 = 0;
    work->unk_30 = 0;
    work->unk_30 = GWMGRecordGet(0xC);
    work->unk_28 = (work->unk_30 >> 0x10) & 0xFF;
    work->unk_24 = (work->unk_30 >> 0x18) & 0xFF;
    work->unk_30 = (u16)work->unk_30;
    fn_1_8CAC(lbl_1_bss_30, work->unk_30);
    var_r30->func = fn_1_948;
}

void fn_1_5F0(omObjData *var_r29)
{
    Vec sp14;
    Vec sp8;
    M460DllCameraStruct *var_r31;
    M460DllWork *work;

    work = var_r29->data;
    work->unk_04++;
    work->unk_10++;
    work->unk_18++;
    work->unk_50++;
    if ((omSysExitReq != 0) && (work->unk_00 != 5)) {
        work->unk_00 = 4;
        fn_1_7FC(var_r29);
    }
    var_r31 = fn_1_3F2C(1);
    sp8.x = -(sind(var_r31->unk_28.y) * cosd(var_r31->unk_28.x));
    sp8.y = -(-sind(var_r31->unk_28.x));
    sp8.z = -(cosd(var_r31->unk_28.y) * cosd(var_r31->unk_28.x));
    sp14.x = var_r31->unk_1C.x - (sp8.x * var_r31->unk_34);
    sp14.y = var_r31->unk_1C.y - (sp8.y * var_r31->unk_34);
    sp14.z = var_r31->unk_1C.z - (sp8.z * var_r31->unk_34);
    HuAudFXListnerUpdate(&sp14, &sp8);
}

void fn_1_7FC(omObjData *object)
{
    M460DllWork *work = object->data;

    if (work->unk_08 == 0) {
        switch (work->unk_00) {
            case 0:
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 0x3C);
                lbl_1_bss_0 = 1;
                fn_1_8FAC(0);
                work->unk_00 = 1;
                work->unk_10 = 0;
                object->func = fn_1_24F4(lbl_1_bss_30, object);
                break;
            case 1:
                work->unk_00 = 2;
                work->unk_18 = 0;
                object->func = fn_1_1548;
                break;
            case 2:
                work->unk_00 = 3;
                work->unk_50 = 0;
                object->func = fn_1_2D64(lbl_1_bss_30, object);
                break;
            case 3:
            case 4:
                work->unk_08 = 1;
                work->unk_00 = 5;
                object->func = fn_1_D7C;
                break;
            case 5:
            default:
                work->unk_00 = 5;
                object->func = fn_1_11EC;
        }
        work->unk_04 = 0;
    }
}

void fn_1_948(omObjData *object)
{
    fn_1_5F0(object);
    fn_1_7FC(object);
}

void fn_1_D7C(omObjData *object)
{
    M460DllWork *work = object->data;
    fn_1_5F0(object);
    if (WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
        WipeColorSet(0xFF, 0xFF, 0xFF);
        work->unk_08 = 0;
        fn_1_7FC(object);
    }
}

void fn_1_11EC(omObjData *object)
{
    fn_1_5F0(object);
    if (WipeStatGet() == 0) {
        fn_1_4BE4();
        fn_1_6814();
        fn_1_8F38();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_1548(omObjData *object)
{
    M460DllWork *work = object->data;
    fn_1_5F0(object);
    switch (work->unk_14) {
        case 0:
            work->unk_1C = 0x3C;
            work->unk_20 = 0x3C;
            lbl_1_bss_18 = MGSeqCreate(3, 0);
            MGSeqPosSet(lbl_1_bss_18, 320.0f, 240.0f);
            work->unk_14 = 1;
            work->unk_18 = 0;
            break;
        case 1:
            if ((lbl_1_bss_8 < 0) && ((MGSeqStatGet(lbl_1_bss_18) & 0x10) != 0)) {
                lbl_1_bss_8 = HuAudSeqPlay(0x49);
            }
            if (MGSeqStatGet(lbl_1_bss_18) == 0) {
                work->unk_2C = 0;
                work->unk_44 = 0;
                if (work->unk_08 == 0) {
                    work->unk_18 = 0;
                    object->func = fn_1_197C;
                }
            }
            break;
    }
}

void fn_1_197C(omObjData *object)
{
    M460DllWork *work = object->data;
    s32 var_r26 = 0;
    s32 sp8 = 0;
    fn_1_5F0(object);
    switch (work->unk_14) {
        case 1:
            if (WipeStatGet() == 0) {
                work->unk_38 = 3;
                work->unk_3C = 0;
                work->unk_40 = 0;
                work->unk_1C = 0x3C;
                work->unk_20 = 0x3C;
                work->unk_14 = 2;
                work->unk_18 = 0;
            }
            break;
        case 2:
            if (work->unk_38 == 3) {
                if ((--work->unk_20) == 0) {
                    work->unk_20 = 0x3C;
                    work->unk_1C--;
                    if (work->unk_1C == 0) {
                        work->unk_44 = 1;
                        fn_1_42BC(frandmod(2));
                    }
                }
                if ((lbl_1_bss_16 < 0) && (work->unk_1C < 0xA)) {
                    lbl_1_bss_16 = MGSeqCreate(1, work->unk_1C, -1, -1);
                }
                MGSeqParamSet(lbl_1_bss_16, 1, work->unk_1C);
            }
            else {
                if (lbl_1_bss_16 >= 0) {
                    MGSeqParamSet(lbl_1_bss_16, 2, -1);
                    lbl_1_bss_16 = -1;
                }
                if (frandmod(0x3E8) < 0x1F4) {
                    work->unk_44 = 1;
                }
                if (work->unk_2C >= 0x1E) {
                    work->unk_44 = 1;
                }
                if (work->unk_44 != 0) {
                    work->unk_44 = 1;
                    work->unk_88 = 1;
                }
                work->unk_14 = 3;
                work->unk_18 = 0;
            }
            break;
        case 3:
            if (fn_1_4358() != 0) {
                if (work->unk_44 != 0) {
                    var_r26 = 1;
                }
                else if (work->unk_18 > 60.0f) {
                    if (work->unk_08 == 0) {
                        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x1E);
                        WipeColorSet(0, 0, 0);
                    }
                    work->unk_14 = 4;
                    work->unk_18 = 0;
                }
            }
            else {
                work->unk_18 = 0;
            }
            break;
        case 4:
            if (WipeStatGet() == 0) {
                work->unk_2C++;
                if (work->unk_08 == 0) {
                    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 0x1E);
                }
                work->unk_14 = 1;
                work->unk_18 = 0;
            }
            break;
    }
    if (var_r26 != 0) {
        lbl_1_bss_14 = MGSeqCreate(3, 1);
        HuAudSeqFadeOut(lbl_1_bss_8, 0x64);
        work->unk_24++;
        if (work->unk_24 > 0xFF) {
            work->unk_24 = 0xFF;
        }
        if (work->unk_2C > work->unk_30) {
            work->unk_28 = work->unk_24;
            work->unk_30 = work->unk_2C;
            work->unk_48 = 1;
            GWMGRecordSet(0xC, work->unk_30);
        }
        mgRecordExtra = work->unk_2C;
        work->unk_14 = 5;
        work->unk_18 = 0;
        if (work->unk_08 == 0) {
            object->func = fn_1_201C;
        }
    }
}

void fn_1_201C(omObjData *object)
{
    M460DllWork *work = object->data;

    if (lbl_1_bss_16 >= 0) {
        MGSeqParamSet(lbl_1_bss_16, 2, -1);
        lbl_1_bss_16 = -1;
    }
    fn_1_5F0(object);
    if (MGSeqStatGet(lbl_1_bss_14) == 0) {
        if (work->unk_48 != 0) {
            fn_1_8FAC(1);
            lbl_1_bss_12 = MGSeqCreate(0xE, work->unk_30);
            work->unk_48 = 0;
        }
        work->unk_14 = 6;
        work->unk_18 = 0;
        fn_1_7FC(object);
    }
}

omObjFunc fn_1_24F4(Process *process, omObjData *object)
{
    M460DllCameraStruct *var_r31;

    object->work[0] = object->work[1] = 0;
    fn_1_3E68(1);
    var_r31 = fn_1_3E90(1);
    var_r31->unk_84 = 1.0f;
    var_r31->unk_94 = 0;
    return fn_1_2564;
}

void fn_1_2564(omObjData *object)
{
    Vec sp20;
    M460DllCameraStruct *var_r26;
    M460DllWork *work;
    s32 var_r24;
    float var_f31;

    work = object->data;
    fn_1_5F0(object);
    object->work[0]++;
    var_f31 = lbl_1_data_AC[object->work[1]];
    var_r24 = 1;
    if (var_f31 < 0.0f) {
        var_r24 = 0;
        var_f31 *= -1.0f;
    }
    var_f31 = object->work[0] / var_f31;
    VECSubtract(&lbl_1_data_4C[object->work[1] + var_r24], &lbl_1_data_4C[object->work[1]], &sp20);
    VECScale(&sp20, &sp20, var_f31);
    VECAdd(&lbl_1_data_4C[object->work[1]], &sp20, &sp20);
    Center.x = sp20.x;
    Center.y = sp20.y;
    Center.z = sp20.z;
    VECSubtract(&lbl_1_data_70[object->work[1] + var_r24], &lbl_1_data_70[object->work[1]], &sp20);
    VECScale(&sp20, &sp20, var_f31);
    VECAdd(&lbl_1_data_70[object->work[1]], &sp20, &sp20);
    CRot.x = sp20.x;
    CRot.y = sp20.y;
    CRot.z = 0.0f;
    CZoom = sp20.z;
    var_r26 = fn_1_3E90(1);
    var_r26->unk_1C = Center;
    var_r26->unk_28 = CRot;
    var_r26->unk_34 = CZoom;
    var_r26->unk_10 = lbl_1_data_94[object->work[1]] + (var_f31 * (lbl_1_data_94[object->work[1] + var_r24] - lbl_1_data_94[object->work[1]]));
    if (var_f31 >= 1.0f) {
        object->work[0] = 0;
        object->work[1]++;
        if (lbl_1_data_A0[object->work[1]] > 0.0f) {
            fn_1_8BA0(lbl_1_data_A0[object->work[1]]);
        }
        if (lbl_1_data_AC[object->work[1]] == 0) {
            work->unk_0C = 2;
            fn_1_7FC(object);
        }
        else if (lbl_1_data_AC[object->work[1] + 1] == 0) {
            work->unk_0C = 1;
        }
    }
}

omObjFunc fn_1_2D64(Process *process, omObjData *object)
{
    return fn_1_2D70;
}

void fn_1_2D70(omObjData *object)
{
    M460DllWork *work = object->data;
    s32 var_r23 = 1;
    fn_1_5F0(object);
    if (lbl_1_bss_12 >= 0) {
        if (MGSeqStatGet(lbl_1_bss_12) != 0) {
            var_r23 = 0;
        }
        else {
            lbl_1_bss_12 = -1;
        }
    }
    if (work->unk_8C != 1) {
        var_r23 = 0;
    }
    if (var_r23 != 0) {
        work->unk_4C = 1;
        if (lbl_1_bss_4 < 0) {
            lbl_1_bss_4 = HuAudSStreamPlay(4);
        }
        if (work->unk_50 >= 210.0f) {
            work->unk_4C = 2;
            fn_1_7FC(object);
        }
    }
    else {
        work->unk_50 = 0;
    }
}

void fn_1_32CC(Process *process)
{
    Hu3DCameraCreate(0x1F);
    lbl_1_bss_28 = omAddObjEx(process, 0x7FDA, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_28->work[0] = 5;
    lbl_1_bss_24 = omAddObjEx(process, 0xC, 1, 0, -1, fn_1_337C);
    lbl_1_bss_24->work[0] = 0;
}

void fn_1_337C(omObjData *object)
{
    UnkM460DllStruct sp1C[5] = {
        { 320.0f, 240.0f, 640.0f, 480.0f },
        { 160.0f, 120.0f, 320.0f, 240.0f },
        { 160.0f, 360.0f, 320.0f, 240.0f },
        { 480.0f, 120.0f, 320.0f, 240.0f },
        { 480.0f, 360.0f, 320.0f, 240.0f },
    };
    s32 sp8[5] = { 1, 2, 4, 8, 16 };
    M460DllCameraStruct *var_r31;
    s32 var_r29;
    M460DllCameraStruct *var_r28;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 10 * sizeof(M460DllCameraStruct), MEMORY_DEFAULT_NUM);
    var_r28 = object->data;
    memset(var_r28, 0, 10 * sizeof(M460DllCameraStruct));
    object->model[0] = Hu3DHookFuncCreate(fn_1_3BC0);
    Hu3DModelLayerSet(object->model[0], 0);
    Hu3DModelCameraSet(object->model[0], 0x1E);
    for (var_r31 = var_r28, var_r29 = 0; var_r29 < 5; var_r29++, var_r31++) {
        var_r31->unk_00 = 0;
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
    var_r31 = var_r28;
    var_r31->unk_00 = 1;
    object->work[1] = object->work[2] = 0;
    object->work[0]++;
    fn_1_3618(object);
    object->func = fn_1_35F0;
}

void fn_1_35F0(omObjData *object)
{
    fn_1_3618(object);
}

void fn_1_3618(omObjData *var_r28)
{
    float var_f31;
    M460DllCameraStruct *var_r31;
    s32 var_r30;
    s32 var_r29;
    M460DllCameraStruct *var_r27;
    u32 var_r26;
    u32 var_r25;
    s32 var_r24;
    u32 var_r23;
    u32 var_r22;
    u32 var_r21;

    var_r27 = var_r28->data;
    {
        s32 sp40[4] = { 2, 4, 8, 16 };
        u32 sp30[4];
        s32 sp20[4];
        float sp10[4];
        float sp8[2];
        var_r24 = 0;
        var_r26 = 0;
        memcpy(&var_r27[5], var_r27, 5 * sizeof(M460DllCameraStruct));
        var_r28->work[1] = var_r28->work[2];
        switch (var_r28->work[1]) {
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
            Hu3DModelAttrReset(var_r28->model[0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrSet(var_r28->model[0], HU3D_ATTR_DISPOFF);
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

void fn_1_3BC0(ModelData *model, Mtx mtx)
{
    Mtx sp3C;
    Mtx spC;
    float var_f31;
    float var_f30;
    float var_f29;

    DCStoreRange(&lbl_1_data_B8, 4);
    C_MTXPerspective(spC, 41.5f, 1.2f, 100.0f, 5500.0f);
    GXSetProjection(spC, GX_PERSPECTIVE);
    MTXIdentity(sp3C);
    GXLoadPosMtxImm(sp3C, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, lbl_1_data_B8);
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
    var_f29 = 2530.0f;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-var_f31, var_f30, -var_f29);
    GXPosition3f32(var_f31, var_f30, -var_f29);
    GXPosition3f32(var_f31, -var_f30, -var_f29);
    GXPosition3f32(-var_f31, -var_f30, -var_f29);
    GXEnd();
}

void fn_1_3E68(u32 arg0)
{
    lbl_1_bss_24->work[2] = arg0;
}

u32 fn_1_3E7C(void)
{
    return lbl_1_bss_24->work[1];
}

M460DllCameraStruct *fn_1_3E90(s32 arg0)
{
    M460DllCameraStruct *var_r31;
    s32 var_r30;
    M460DllCameraStruct *var_r29;

    var_r29 = lbl_1_bss_24->data;
    for (var_r31 = var_r29, var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
        if ((var_r31->unk_0C & arg0) != 0) {
            break;
        }
    }
    if (var_r30 >= 5) {
        OSReport("M460:Camera Flag Error!!\n");
        return NULL;
    }
    return var_r31;
}

M460DllCameraStruct *fn_1_3F2C(s32 arg0)
{
    M460DllCameraStruct *var_r31;
    s32 var_r30;
    M460DllCameraStruct *var_r29;

    var_r29 = lbl_1_bss_24->data;
    for (var_r31 = &var_r29[5], var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
        if ((var_r31->unk_0C & arg0) != 0) {
            break;
        }
    }
    if (var_r30 >= 5) {
        OSReport("M460:Camera Flag Error!!\n");
        return NULL;
    }
    return var_r31;
}

M460DllCameraStruct *fn_1_3FC8(u32 arg0)
{
    M460DllCameraStruct *var_r31 = lbl_1_bss_24->data;
    if (arg0 >= 5) {
        OSReport("M460:Camera No. Error!!\n");
        return NULL;
    }
    return &var_r31[arg0];
}

M460DllCameraStruct *fn_1_4030(u32 arg0)
{
    M460DllCameraStruct *var_r31 = lbl_1_bss_24->data;
    if (arg0 >= 5) {
        OSReport("M460:Camera No. Error!!\n");
        return NULL;
    }
    return &var_r31[arg0 + 5];
}

void fn_1_409C(s32 arg0, s32 arg1)
{
    M460DllCameraStruct *var_r31;
    s32 var_r30;
    s32 var_r29;
    M460DllCameraStruct *var_r28;
    M460DllCameraStruct *var_r27;

    var_r29 = 0;
    if (arg0 >= 0) {
        var_r27 = lbl_1_bss_24->data;
        var_r28 = &var_r27[5];
        for (var_r31 = var_r28, var_r30 = 0; var_r30 < 5; var_r30++, var_r31++) {
            if ((var_r31->unk_0C & arg1) != 0) {
                var_r29 |= var_r31->unk_3C;
            }
        }
        Hu3DModelCameraSet(arg0, var_r29);
    }
}

s32 fn_1_4134(void)
{
    return ((M460DllWork *)lbl_1_bss_2C->data)->unk_00;
}

u32 fn_1_414C(void)
{
    return ((M460DllWork *)lbl_1_bss_2C->data)->unk_0C;
}

u32 fn_1_4164(void)
{
    return ((M460DllWork *)lbl_1_bss_2C->data)->unk_14;
}

s32 fn_1_417C(void)
{
    return ((M460DllWork *)lbl_1_bss_2C->data)->unk_4C;
}

s32 fn_1_4194(void)
{
    return 1;
}

s32 fn_1_419C(void)
{
    return ((M460DllWork *)lbl_1_bss_2C->data)->unk_88;
}

void fn_1_41B4(s32 arg0, s32 arg1, s32 arg2)
{
    M460DllWork *work = lbl_1_bss_2C->data;
    work->unk_64[arg0 &= 3] = arg1;
    work->unk_54[arg0] = arg2;
}

void fn_1_41F4(s32 arg0)
{
    ((M460DllWork *)lbl_1_bss_2C->data)->unk_8C |= (1 << ((arg0 & 7) * 4));
}

void fn_1_4224(s32 arg0)
{
    ((M460DllWork *)lbl_1_bss_2C->data)->unk_90 |= (1 << ((arg0 & 3) * 4));
}

void fn_1_4254(s32 arg0)
{
    ((M460DllWork *)lbl_1_bss_2C->data)->unk_94 |= (1 << ((arg0 & 3) * 4));
}

s32 fn_1_4284(void)
{
    return MGSeqStatGet(lbl_1_bss_14) == 0;
}

void fn_1_42BC(u32 arg0)
{
    M460DllWork *work = lbl_1_bss_2C->data;
    if (work->unk_38 == 3) {
        work->unk_38 = arg0;
    }
}

s32 fn_1_42F0(void)
{
    return ((M460DllWork *)lbl_1_bss_2C->data)->unk_38;
}

void fn_1_4308(void)
{
    ((M460DllWork *)lbl_1_bss_2C->data)->unk_3C = 1;
}

s32 fn_1_4324(void)
{
    return ((M460DllWork *)lbl_1_bss_2C->data)->unk_3C;
}

void fn_1_433C(void)
{
    ((M460DllWork *)lbl_1_bss_2C->data)->unk_40 = 1;
}

s32 fn_1_4358(void)
{
    return ((M460DllWork *)lbl_1_bss_2C->data)->unk_40;
}

u32 fn_1_4370(void)
{
    return ((M460DllWork *)lbl_1_bss_2C->data)->unk_2C;
}

void fn_1_4388(Vec *sp8, Vec *var_r31)
{
    Vec sp10;

    VECSubtract(var_r31, sp8, &sp10);
    Center = *var_r31;
    CRot.x = atan2d(sp10.y, sqrtf((sp10.x * sp10.x) + (sp10.z * sp10.z)));
    CRot.y = atan2d(-sp10.x, -sp10.z);
    CRot.z = 0.0f;
    CZoom = VECMag(&sp10);
}

void fn_1_4590(float arg8, float arg9, float argA, float argB, float argC, float argD)
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

float fn_1_47D0(float arg8, float arg9, float argA)
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

float fn_1_48EC(float arg8, float arg9)
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
