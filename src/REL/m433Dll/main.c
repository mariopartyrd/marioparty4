#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "string.h"

#include "REL/m433Dll.h"

void fn_1_4C0(omObjData *object);
void fn_1_618(omObjData *object);
void fn_1_798(omObjData *object);
void fn_1_AD4(omObjData *object);
void fn_1_E2C(omObjData *object);
void fn_1_1040(omObjData *object);
void fn_1_13FC(omObjData *object);
void fn_1_16D0(omObjData *object);
omObjFunc fn_1_1A3C(Process *process, omObjData *object);
void fn_1_1A48(omObjData *object);
float fn_1_26C4(float arg8, float arg9, float argA);

Vec lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };
Vec lbl_1_data_C = { 0.3f, -0.8f, 0.3f };
Vec lbl_1_data_18 = { 10.0f, 45.0f, 3500.0f };
GXColor lbl_1_data_24 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_28 = { 50.0f, 150000.0f, 50.0f };
Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_40 = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_4C = { 0.0f, 170.0f, 0.0f };
Vec lbl_1_data_58 = { 0.0f, -22.0f, 850.0f };

char lbl_1_bss_34[0x4];
char lbl_1_bss_30[0x4];
char lbl_1_bss_2C[0x4];
Process *lbl_1_bss_28;
omObjData *lbl_1_bss_24;
omObjData *lbl_1_bss_20;
char lbl_1_bss_18[8];
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
    Vec sp14;
    Vec sp8;
    Process *var_r31;
    LightData *var_r30;

    HuAudSndGrpSet(0x3A);
    lbl_1_bss_C = lbl_1_bss_8 = -1;
    lbl_1_bss_4 = lbl_1_bss_0 = -1;
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
    lbl_1_bss_16 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_16);
    var_r30 = &Hu3DGlobalLight[lbl_1_bss_16];
    var_r30->unk_00 |= 0x8000;
    lbl_1_data_18.x = 55.74f;
    lbl_1_data_18.y = 0.0f;
    lbl_1_data_18.z = 3500.0f;
    sp14.x = sp14.y = sp14.z = 0.0f;
    sp8.x = sp8.z = 0.0f;
    sp8.y = lbl_1_data_18.z;
    sp8.x = 0.0f;
    sp8.y = 3480.0002f;
    sp8.z = 900.00006f;
    Hu3DGLightPosAimSetV(lbl_1_bss_16, &sp8, &sp14);
    Hu3DShadowPosSet(&sp8, &lbl_1_data_34, &sp14);
    lbl_1_bss_14 = lbl_1_bss_12 = lbl_1_bss_10 = -1;
    var_r31 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_28 = var_r31;
    omGameSysInit(var_r31);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, -1.0f, 10.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lbl_1_bss_20 = omAddObjEx(var_r31, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_24 = omAddObjEx(var_r31, 0xA, 0, 0, -1, fn_1_4C0);
    fn_1_2894(var_r31);
    fn_1_5904(var_r31);
}

void fn_1_4C0(omObjData *object)
{
    M433DllWork *work;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M433DllWork), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, sizeof(M433DllWork));
    work->unk_00 = 0;
    work->unk_04 = 0;
    work->unk_0C = 0;
    work->unk_10 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->unk_24 = 0;
    work->unk_28 = 0;
    work->unk_08 = 0;
    work->unk_34 = 2;
    work->unk_38 = 0;
    work->unk_3C = 0;
    object->func = fn_1_798;
}

void fn_1_584(omObjData *object)
{
    M433DllWork *work = object->data;
    work->unk_04++;
    work->unk_10++;
    work->unk_18++;
    work->unk_28++;
    if ((omSysExitReq != 0) && (work->unk_00 != 5)) {
        work->unk_00 = 4;
        fn_1_618(object);
    }
}

void fn_1_618(omObjData *object)
{
    M433DllWork *work = object->data;
    if (work->unk_08 == 0) {
        switch (work->unk_00) {
            case 0:
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                Hu3DCameraPerspectiveSet(1, 41.5f, 10.0f, 10000.0f, 1.2f);
                lbl_1_bss_C = HuAudFXPlay(0x6AC);
                work->unk_00 = 1;
                work->unk_10 = 0;
                object->func = fn_1_29A4(lbl_1_bss_28, object);
                break;
            case 1:
                work->unk_00 = 2;
                work->unk_18 = 0;
                object->func = fn_1_1040;
                break;
            case 2:
                work->unk_00 = 3;
                work->unk_28 = 0;
                object->func = fn_1_1A3C(lbl_1_bss_28, object);
                break;
            case 3:
            case 4:
                work->unk_08 = 1;
                work->unk_00 = 5;
                object->func = fn_1_AD4;
                break;
            case 5:
            default:
                work->unk_00 = 5;
                object->func = fn_1_E2C;
                break;
        }
        work->unk_04 = 0;
    }
}

void fn_1_798(omObjData *object)
{
    fn_1_584(object);
    fn_1_618(object);
}

void fn_1_AD4(omObjData *object)
{
    M433DllWork *work = object->data;

    fn_1_584(object);
    if (WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        work->unk_08 = 0;
        fn_1_618(object);
    }
}

void fn_1_E2C(omObjData *object)
{
    fn_1_584(object);
    if (WipeStatGet() == 0) {
        fn_1_5B74();
        fn_1_2984();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_1040(omObjData *object)
{
    M433DllWork *work = object->data;
    fn_1_584(object);
    switch (work->unk_14) {
        case 0:
            HuAudFXFadeOut(lbl_1_bss_C, 0x1E);
            work->unk_1C = 0x1E;
            work->unk_20 = 0x3C;
            lbl_1_bss_14 = MGSeqCreate(3, 0);
            MGSeqPosSet(lbl_1_bss_14, 320.0f, 240.0f);
            Center.x = 0.0f;
            Center.y = 200.0f;
            Center.z = 0.0f;
            CRot.x = -30.0f;
            CRot.y = 0.0f;
            CRot.z = 0.0f;
            CZoom = 1900.0f;
            work->unk_14 = 1;
            work->unk_18 = 0;
            break;
        case 1:
            if ((lbl_1_bss_4 < 0) && ((MGSeqStatGet(lbl_1_bss_14) & 0x10) != 0)) {
                lbl_1_bss_4 = HuAudSeqPlay(0x47);
            }
            if ((MGSeqStatGet(lbl_1_bss_14) == 0) && (work->unk_08 == 0)) {
                work->unk_14 = 2;
                work->unk_18 = 0;
                object->func = fn_1_13FC;
            }
            break;
    }
}

void fn_1_13FC(omObjData *object)
{

    M433DllWork *work = object->data;
    s32 var_r27 = 0;
    fn_1_584(object);
    work->unk_20++;
    if (--work->unk_20 == 0) {
        work->unk_20 = 0x3C;
        work->unk_1C--;
        if (work->unk_1C == 0) {
            var_r27 = 1;
        }
    }
    if (work->unk_34 != 2) {
        var_r27 = 1;
    }
    if (var_r27 != 0) {
        lbl_1_bss_12 = MGSeqCreate(3, 1);
        MGSeqPosSet(lbl_1_bss_12, 320.0f, 240.0f);
        HuAudSeqFadeOut(lbl_1_bss_4, 0x64);
        work->unk_14 = 3;
        work->unk_18 = 0;
        if (work->unk_08 == 0) {
            object->func = fn_1_16D0;
        }
        lbl_1_bss_8 = HuAudFXPlay(0x6AC);
    }
}

void fn_1_16D0(omObjData *object)
{
    M433DllWork *work = object->data;
    fn_1_584(object);
    if ((MGSeqStatGet(lbl_1_bss_12) == 0) && ((work->unk_38 + 0xFFFF0000) == 0x1111)) {
        work->unk_14 = 4;
        work->unk_18 = 0;
        fn_1_618(object);
    }
}

omObjFunc fn_1_1A3C(Process *process, omObjData *object)
{
    return fn_1_1A48;
}

static inline s32 fn_1_1A48_inline(void)
{
    return GWSystem.mg_type;
}

void fn_1_1A48(omObjData *object)
{
    M433DllWork *work = object->data;
    float var_f31 = lbl_1_data_58.y;
    if (fn_1_10FA4(1) != 0) {
        var_f31 *= -1.0f;
    }
    Center.x += 0.15f * (lbl_1_data_4C.x - Center.x);
    Center.y += 0.15f * (lbl_1_data_4C.y - Center.y);
    Center.z += 0.15f * (lbl_1_data_4C.z - Center.z);
    CRot.x = fn_1_26C4(CRot.x, lbl_1_data_58.x, 0.15f);
    CRot.y = fn_1_26C4(CRot.y, var_f31, 0.15f);
    CZoom += 0.15f * (lbl_1_data_58.z - CZoom);
    fn_1_584(object);
    work->unk_24 = 1;
    if (lbl_1_bss_0 < 0) {
        lbl_1_bss_0 = HuAudSStreamPlay(1);
    }
    if (lbl_1_bss_10 < 0) {
        s32 spC[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
        s32 var_r26;
        s32 var_r25 = 0;
        s32 var_r24;
        for (var_r26 = 0; var_r26 < 2; var_r26++) {
            if (work->unk_2C[var_r26] >= 0) {
                spC[var_r25++] = GWPlayerCfg[work->unk_2C[var_r26]].character;
                GWPlayerCoinWinAdd(work->unk_2C[var_r26], 10);
            }
        }
        if (spC[0] == -1) {
            lbl_1_bss_10 = MGSeqCreate(5, 2);
            return;
        }
        var_r24 = 3;
        if (fn_1_1A48_inline() == 0) {
            if (fn_1_10FA4(0) != 0) {
                var_r24 = 5;
            }
        }
        lbl_1_bss_10 = MGSeqCreate(5, var_r24, spC[0], spC[1], spC[2], spC[3]);
        return;
    }
    if ((MGSeqStatGet(lbl_1_bss_10) == 0) && (work->unk_28 >= 210.0f)) {
        HuAudFXFadeOut(lbl_1_bss_8, 0x1E);
        work->unk_24 = 2;
        fn_1_618(object);
    }
}

s32 fn_1_213C(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_24, M433DllWork)->unk_00;
}

s32 fn_1_2154(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_24, M433DllWork)->unk_0C;
}

u32 fn_1_216C(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_24, M433DllWork)->unk_14;
}

u32 fn_1_2184(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_24, M433DllWork)->unk_24;
}

void fn_1_219C(s32 arg0, s32 arg1, s32 arg2)
{
    M433DllWork *work = lbl_1_bss_24->data;
    work->unk_34 = arg0;
    work->unk_2C[0] = arg1;
    work->unk_2C[1] = arg2;
}

s32 fn_1_21CC(void)
{
    return OM_GET_DATA_PTR(lbl_1_bss_24, M433DllWork)->unk_34;
}

void fn_1_21E4(s32 arg0)
{
    OM_GET_DATA_PTR(lbl_1_bss_24, M433DllWork)->unk_38 |= (1 << ((arg0 & 7) * 4));
}

void fn_1_2214(s32 arg0)
{
    OM_GET_DATA_PTR(lbl_1_bss_24, M433DllWork)->unk_3C |= (1 << ((arg0 & 3) * 4));
}

s32 fn_1_2244(void)
{
    return MGSeqStatGet(lbl_1_bss_12) == 0;
}

void fn_1_227C(Vec *arg0, Vec *arg1)
{
    Vec sp10;

    VECSubtract(arg1, arg0, &sp10);
    Center = *arg1;
    CRot.x = atan2d(sp10.y, sqrtf((sp10.x * sp10.x) + (sp10.z * sp10.z)));
    CRot.y = atan2d(-sp10.x, -sp10.z);
    CRot.z = 0.0f;
    CZoom = VECMag(&sp10);
}

void fn_1_2484(float arg8, float arg9, float argA, float argB, float argC, float argD)
{
    Vec sp3C;
    Vec sp30;

    sp3C.x = arg8;
    sp3C.y = arg9;
    sp3C.z = argA;
    sp30.x = argB;
    sp30.y = argC;
    sp30.z = argD;
    fn_1_227C(&sp3C, &sp30);
}

float fn_1_26C4(float arg8, float arg9, float argA)
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

float fn_1_27E0(float arg8, float arg9)
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

s32 lbl_1_data_64[] = {
    0x00000000,
    0x00000000,
    0x45ABE000,
    0xC576E000,
    0x00000000,
    0xBF333333,
    0x3F19999A,
    0xFFFFFFFF,
    0x00000000,
    0x45ABE000,
    0xC576E000,
    0x00000000,
    0x3F800000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
};
