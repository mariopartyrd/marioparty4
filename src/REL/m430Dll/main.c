#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

#include "REL/m430Dll.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#endif

typedef struct M430DllMainWork {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u32 unk_0C;
    s32 unk_10;
    u32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u32 unk_24;
    u32 unk_28;
    s32 unk_2C;
    u32 unk_30;
    s32 unk_34;
} M430DllMainWork; /* size = 0x38 */

void fn_1_10FC(omObjData *object);
void fn_1_168C(omObjData *object);
void fn_1_1B04(omObjData *object);
void fn_1_21E4(omObjData *object);
void fn_1_2710(omObjData *object);
omObjFunc fn_1_2D48(Process *process, omObjData *object);
void fn_1_2E80(omObjData *object);
omObjFunc fn_1_369C(Process *arg1, omObjData *object);
void fn_1_3768(omObjData *object);
s32 fn_1_4030(void);
void fn_1_65C(omObjData *object);
void fn_1_A54(omObjData *arg0);
void fn_1_B98(omObjData *object);

Vec lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };
Vec lbl_1_data_C = { 0.3f, -0.8f, 0.3f };
Vec lbl_1_data_18 = { 10.0f, 45.0f, 3500.0f };
GXColor lbl_1_data_24 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_28 = { 50.0f, 150000.0f, 50.0f };
Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_40 = { 0.0f, 0.0f, 0.0f };

Process *lbl_1_bss_38;
omObjData *lbl_1_bss_34;
omObjData *lbl_1_bss_30;
s16 lbl_1_bss_2C;
char lbl_1_bss_28[4];
s16 lbl_1_bss_26;
s16 lbl_1_bss_24;
s16 lbl_1_bss_22;
s16 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s32 lbl_1_bss_14;
s16 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    Process *var_r31;
    LightData *var_r30;

    HuAudSndGrpSet(0x37);
    lbl_1_bss_C = lbl_1_bss_8 = -1;
    lbl_1_bss_4 = lbl_1_bss_0 = -1;
    lbl_1_bss_2C = -1;
    lbl_1_bss_14 = 1;
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
    lbl_1_bss_26 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_26);
    var_r30 = &Hu3DGlobalLight[lbl_1_bss_26];
    var_r30->unk_00 |= 0x8000;
    lbl_1_data_18.x = 34.75f;
    lbl_1_data_18.y = -24.75f;
    lbl_1_data_18.z = 3500.0f;
    sp14.x = sp14.y = sp14.z = 0.0f;
    sp8.x = sp8.z = 0.0f;
    sp8.y = lbl_1_data_18.z;
    mtxRot(sp20, lbl_1_data_18.x, lbl_1_data_18.y, 0.0f);
    MTXMultVec(sp20, &sp8, &sp8);
    Hu3DGLightPosAimSetV(lbl_1_bss_26, &sp8, &sp14);
    Hu3DShadowPosSet(&sp8, &lbl_1_data_34, &sp14);
    lbl_1_bss_24 = lbl_1_bss_22 = lbl_1_bss_20 = -1;
    lbl_1_bss_1C = 1;
    lbl_1_bss_18 = 1;
    var_r31 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_38 = var_r31;
    omGameSysInit(var_r31);
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(1, -1.0f, 5.0f, 25000.0f, 0.6f);
    Hu3DCameraPerspectiveSet(2, -1.0f, 5.0f, 25000.0f, 0.6f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(2, 320.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 0x140, 0x1E0);
    Hu3DCameraScissorSet(2, 0x140, 0, 0x140, 0x1E0);
    lbl_1_bss_30 = omAddObjEx(var_r31, 0x7FDA, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_30->work[0] = 2;
    lbl_1_bss_34 = omAddObjEx(var_r31, 0xA, 0, 0, -1, fn_1_65C);
    fn_1_4A80(var_r31);
    fn_1_BBC4(var_r31);
    lbl_1_bss_10 = espEntry(DATA_MAKE_NUM(DATADIR_M430, 0x1B), 0x64, 0);
    espPosSet(lbl_1_bss_10, 288.0, 240.0);
    espScaleSet(lbl_1_bss_10, 0.22499999403953552, 60.0);
    espDispOff(lbl_1_bss_10);
}

void fn_1_65C(omObjData *object)
{
    M430DllMainWork *work;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M430DllMainWork), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, sizeof(M430DllMainWork));
    work->unk_00 = 0;
    work->unk_04 = 0;
    work->unk_0C = 0;
    work->unk_10 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->unk_24 = 0;
    work->unk_28 = 0;
    work->unk_08 = 0;
    work->unk_2C = 0;
    work->unk_30 = 0;
    work->unk_34 = 0;
    object->func = fn_1_B98;
}

void fn_1_720(omObjData *object)
{
    M430DllMainWork *work = object->data;
    work->unk_04++;
    work->unk_10++;
    work->unk_18++;
    work->unk_28++;
    if ((omSysExitReq != 0) && (work->unk_00 != 5)) {
        work->unk_00 = 4;
        fn_1_A54(object);
    }
    if (lbl_1_bss_18 == 0) {
        if (fn_1_4030() != 0) {
            if ((Hu3DCamera->fov < 0.0f) || (Hu3DCamera[1].fov < 0.0f)) {
                Hu3DCameraPerspectiveSet(1, 41.5f, 5.0f, 25000.0f, 0.6f);
                Hu3DCameraPerspectiveSet(2, 41.5f, 5.0f, 25000.0f, 0.6f);
                Hu3DCameraViewportSet(1, 0.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
                Hu3DCameraViewportSet(2, 320.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
                Hu3DCameraScissorSet(1, 0, 0, 0x140, 0x1E0);
                Hu3DCameraScissorSet(2, 0x140, 0, 0x140, 0x1E0);
            }
        }
        else if ((Hu3DCamera->fov < 0.0f) || (Hu3DCamera[1].fov >= 0.0f)) {
            Hu3DCamera[1].fov = -1.0f;
            Hu3DCameraPerspectiveSet(1, 41.5f, 5.0f, 25000.0f, 1.2f);
            Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
            Hu3DCameraScissorSet(1, 0, 0, 0x280, 0x1E0);
        }
    }
}

void fn_1_A54(omObjData *object)
{
    M430DllMainWork *work = object->data;
    if (work->unk_08 == 0) {
        switch (work->unk_00) {
            case 0:
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                lbl_1_bss_18 = 0;
                work->unk_00 = 1;
                work->unk_10 = 0;
                object->func = fn_1_2D48(lbl_1_bss_38, object);
                break;
            case 1:
                work->unk_00 = 2;
                work->unk_18 = 0;
                object->func = fn_1_1B04;
                break;
            case 2:
                work->unk_00 = 3;
                work->unk_28 = 0;
                object->func = fn_1_369C(lbl_1_bss_38, object);
                break;
            case 3:
            case 4:
                work->unk_08 = 1;
                work->unk_00 = 5;
                object->func = fn_1_10FC;
                break;
            case 5:
            default:
                work->unk_00 = 5;
                object->func = fn_1_168C;
                break;
        }
        work->unk_04 = 0;
    }
}

void fn_1_B98(omObjData *object)
{
    fn_1_720(object);
    fn_1_A54(object);
}

void fn_1_10FC(omObjData *object)
{
    M430DllMainWork *work = object->data;
    fn_1_720(object);

    if (WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        lbl_1_bss_14 = 1;
        work->unk_08 = 0;
        fn_1_A54(object);
    }
}

void fn_1_168C(omObjData *object)
{
    fn_1_720(object);
    if (WipeStatGet() == 0) {
        fn_1_C00C();
        fn_1_4C48();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_1B04(omObjData *object)
{
    M430DllMainWork *work = object->data;
    fn_1_720(object);
    switch (work->unk_14) {
        case 0:
            lbl_1_bss_1C = 1;
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
            lbl_1_bss_14 = 0;
            espDispOn(lbl_1_bss_10);
            work->unk_1C = 0x2D;
            work->unk_20 = 0x3C;
            CenterM->x = -450.0f;
            CenterM[1].x = 450.0f;
            CenterM->y = CenterM[1].y = 300.0f;
            CenterM->z = CenterM[1].z = 950.0f;
            CRotM->x = CRotM[1].x = -5.0f;
            CRotM->y = CRotM[1].y = 0.0f;
            CZoomM[0] = CZoomM[1] = 700.0f;
            work->unk_14 = 1;
            work->unk_18 = 0;
            object->work[0] = 0;
            return;
        case 1:
            if (object->work[0] == 0) {
                if (WipeStatGet() == 0) {
                    lbl_1_bss_24 = MGSeqCreate(3, 0);
                    MGSeqPosSet(lbl_1_bss_24, 320.0f, 240.0f);
                    object->work[0]++;
                }
            }
            else {
                if ((lbl_1_bss_4 < 0) && ((MGSeqStatGet(lbl_1_bss_24) & 0x10) != 0)) {
                    lbl_1_bss_4 = HuAudSeqPlay(0x4A);
                }
                if ((MGSeqStatGet(lbl_1_bss_24) == 0) && (work->unk_08 == 0)) {
                    lbl_1_bss_2C = MGSeqCreate(1, work->unk_1C, -1, -1);
                    work->unk_14 = 2;
                    work->unk_18 = 0;
                    object->func = fn_1_21E4;
                }
            }
            break;
    }
}

void fn_1_21E4(omObjData *object)
{
    M430DllMainWork *work = object->data;
    s32 var_r27 = 0;
    fn_1_720(object);
    if (--work->unk_20 == 0) {
        work->unk_20 = 0x3C;
        work->unk_1C--;
        if (work->unk_1C <= 0) {
            var_r27 = 1;
        }
    }
    if (var_r27 != 0) {
        lbl_1_bss_22 = MGSeqCreate(3, 1);
        MGSeqPosSet(lbl_1_bss_22, 320.0f, 240.0f);
        HuAudSeqFadeOut(lbl_1_bss_4, 0x64);
        object->work[1] = 0;
        work->unk_14 = 3;
        work->unk_18 = 0;
        if (work->unk_08 == 0) {
            object->func = fn_1_2710;
        }
    }
    MGSeqParamSet(lbl_1_bss_2C, 1, work->unk_1C);
}

void fn_1_2710(omObjData *object)
{
    M430DllMainWork *work = object->data;
    if (lbl_1_bss_2C >= 0) {
        MGSeqParamSet(lbl_1_bss_2C, 2, -1);
        lbl_1_bss_2C = -1;
    }
    fn_1_720(object);
    if (object->work[1] == 0) {
        if (MGSeqStatGet(lbl_1_bss_22) == 0) {
            if (work->unk_08 == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
                lbl_1_bss_14 = 1;
            }
            object->work[1]++;
            HuAudFXFadeOut(lbl_1_bss_C, 0x1E);
        }
    }
    else if ((WipeStatGet() == 0) && (work->unk_30 == 0x1111)) {
        work->unk_14 = 4;
        work->unk_18 = 0;
        fn_1_A54(object);
    }
}

omObjFunc fn_1_2D48(Process *process, omObjData *object)
{
    CenterM->x = CenterM[1].x = 0.0f;
    CenterM->y = CenterM[1].y = 300.0f;
    CenterM->z = CenterM[1].z = 950.0f;
    CRotM->x = CRotM[1].x = -5.0f;
    CRotM->y = CRotM[1].y = 0.0f;
    CZoomM[0] = CZoomM[1] = 700.0f;
    object->work[0] = object->work[1] = 0;
    lbl_1_bss_1C = 0;
    lbl_1_bss_C = HuAudFXPlay(0x674);
    return fn_1_2E80;
}

void fn_1_2E80(omObjData *object)
{
    M430DllMainWork *work = object->data;
    fn_1_720(object);
    work->unk_0C = 1;
    object->work[0]++;
    switch (object->work[1]) {
        case 0:
            if (object->work[0] > 180.0f) {
                if (work->unk_08 == 0) {
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
                    lbl_1_bss_14 = 1;
                }
                object->work[1]++;
                object->work[0] = 0;
            }
            break;
        case 1:
            if (WipeStatGet() == 0) {
                object->work[0] = 0;
                work->unk_0C = 2;
                fn_1_A54(object);
            }
            break;
    }
}

omObjFunc fn_1_369C(Process *arg0, omObjData *object)
{
    M430DllMainWork *work = object->data;
    s32 spC = 0;
    s32 sp8 = 1;
    lbl_1_bss_1C = 0;
    espDispOff(lbl_1_bss_10);
    fn_1_BB98(1);
    if (work->unk_08 == 0) {
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
        lbl_1_bss_14 = 0;
    }
    CenterM->x = 0.0f;
    lbl_1_bss_8 = HuAudFXPlay(0x679);
    return fn_1_3768;
}

void fn_1_3768(omObjData *object)
{
    M430DllMainWork *work = object->data;

    fn_1_720(object);
    if (WipeStatGet() == 0) {
        work->unk_24 = 1;
        if (work->unk_28 >= 210.0f) {
            work->unk_24 = 2;
            fn_1_A54(object);
        }
    }
    else {
        work->unk_28 = 0;
    }
}

s32 fn_1_4030(void)
{
    return lbl_1_bss_1C;
}

u32 fn_1_4040(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_34, M430DllMainWork)->unk_00;
}

u32 fn_1_4058(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_34, M430DllMainWork)->unk_0C;
}

u32 fn_1_4070(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_34, M430DllMainWork)->unk_14;
}

u32 fn_1_4088(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_34, M430DllMainWork)->unk_24;
}

void fn_1_40A0(s32 arg0)
{
    OM_GET_DATA_PTR(lbl_1_bss_34, M430DllMainWork)->unk_2C = arg0;
}

s32 fn_1_40B8(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_34, M430DllMainWork)->unk_2C;
}

void fn_1_40D0(s32 arg0)
{

    OM_GET_DATA_PTR(lbl_1_bss_34, M430DllMainWork)->unk_30 |= (1 << ((arg0 & 3) * 4));
}

void fn_1_4100(s32 arg0)
{
    OM_GET_DATA_PTR(lbl_1_bss_34, M430DllMainWork)->unk_34 |= (1 << ((arg0 & 3) * 4));
}

float fn_1_4130(void)
{
    M430DllMainWork *work = lbl_1_bss_34->data;
    float var_f31 = work->unk_1C - 1;
    if (var_f31 < 0.0f) {
        var_f31 = 0.0f;
    }
    var_f31 += 0.016666668f * work->unk_20;
    return var_f31;
}

void fn_1_41F0(Vec *arg0, Vec *arg1)
{
    Vec sp10;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;

    sp10.x = arg1->x - arg0->x;
    sp10.y = arg1->y - arg0->y;
    sp10.z = arg1->z - arg0->z;
    Center.x = arg1->x;
    Center.y = arg1->y;
    Center.z = arg1->z;
    CRot.x = atan2d(sp10.y, sqrtf((sp10.x * sp10.x) + (sp10.z * sp10.z)));
    CRot.y = atan2d(-sp10.x, -sp10.z);
    CRot.z = 0.0f;
    CZoom = sqrtf((sp10.z * sp10.z) + ((sp10.x * sp10.x) + (sp10.y * sp10.y)));
}

void fn_1_4538(float sp8, float spC, float sp10, float sp14, float sp18, float sp1C)
{
    Vec sp40;
    Vec sp34;
    sp40.x = sp8;
    sp40.y = spC;
    sp40.z = sp10;

    sp34.x = sp14;
    sp34.y = sp18;
    sp34.z = sp1C;
    fn_1_41F0(&sp40, &sp34);
}

float fn_1_48B0(float arg8, float arg9, float argA)
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

float fn_1_49CC(float arg0, float arg1)
{
    float var_f31;
    float var_f30;

    var_f30 = fmod(arg1 - arg0, 360.0);
    var_f31 = var_f30;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}
