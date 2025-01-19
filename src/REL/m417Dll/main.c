#include "ext_math.h"
#include "game/audio.h"
#include "game/hsfdraw.h"
#include "game/minigame_seq.h"
#include "game/wipe.h"

#include "REL/m417Dll.h"

typedef struct UnkM417Struct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u32 unk_1C;
    /* 0x20 */ u32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C[4];
    /* 0x3C */ s32 unk_3C[4];
    /* 0x4C */ s32 unk_4C[4];
    /* 0x5C */ u32 unk_5C;
    /* 0x60 */ u32 unk_60;
    /* 0x64 */ s32 unk_64;
} UnkM417Struct; /* size = 0x68 */

void fn_1_4D8(omObjData *object);
void fn_1_990(omObjData *object);
void fn_1_EA8(omObjData *object);
void fn_1_13DC(omObjData *object);
void fn_1_17C0(omObjData *object);
void fn_1_1CA8(omObjData *object);
void fn_1_2158(omObjData *object);
s32 fn_1_27D0(void);

Vec lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };
Vec lbl_1_data_C = { 0.3f, -0.8f, 0.3f };
Vec lbl_1_data_18 = { 10.0f, 45.0f, 1000.0f };
GXColor lbl_1_data_24 = { 255, 255, 255, 255 };
Vec lbl_1_data_28 = { 50.0f, 150000.0f, 50.0f };
Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_40 = { 0.0f, 0.0f, 0.0f };

Process *lbl_1_bss_20;
omObjData *lbl_1_bss_1C;
omObjData *lbl_1_bss_18;
s16 lbl_1_bss_14;
s16 lbl_1_bss_12;
s16 lbl_1_bss_10;
s16 lbl_1_bss_8[4];
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    Mtx sp38;
    Vec sp2C = { 0.0f, 0.0f, 0.0f };
    Vec sp20 = { 0.0f, 0.0f, -1.0f };
    Vec sp14;
    Vec sp8;

    Process *var_r31;
    LightData *var_r30;

    HuAudSndGrpSet(42);
    HuAudFXListnerSetEX(&sp2C, &sp20, 10000.0f, 1000.0f, 0.0f, 300.0f, 300.0f);
    lbl_1_bss_4 = lbl_1_bss_0 = -1;
    lbl_1_bss_14 = -1;
    lbl_1_bss_8[0] = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_8[0]);
    var_r30 = &Hu3DGlobalLight[lbl_1_bss_8[0]];
    var_r30->unk_00 |= 32768;
    lbl_1_data_18.x = 20.0f;
    lbl_1_data_18.y = 45.0f;
    lbl_1_data_18.z = 1000.0f;
    sp14.x = sp14.y = sp14.z = 0.0f;
    sp8.x = sp8.z = 0.0f;
    sp8.y = lbl_1_data_18.z;
    mtxRot(sp38, lbl_1_data_18.x, lbl_1_data_18.y, 0.0f);
    MTXMultVec(sp38, &sp8, &sp8);
    Hu3DGLightPosAimSetV(lbl_1_bss_8[0], &sp8, &sp14);
    lbl_1_data_28.x = 200.0f;
    lbl_1_data_28.y = 3000.0f;
    lbl_1_data_28.z = 100.0f;
    lbl_1_data_34.x = 0.0f;
    lbl_1_data_34.y = 1.0f;
    lbl_1_data_34.z = 0.0f;
    lbl_1_data_40.x = 0.0f;
    lbl_1_data_40.y = 0.0f;
    lbl_1_data_40.z = 0.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.625f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    var_r31 = omInitObjMan(50, 8192);
    lbl_1_bss_20 = var_r31;
    omGameSysInit(var_r31);
    lbl_1_bss_12 = lbl_1_bss_10 = -1;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, -1.0f, 5.0f, 5000.0f, 1.2f);
    lbl_1_bss_18 = omAddObjEx(var_r31, 32730, 0, 0, -1, omOutView);
    lbl_1_bss_1C = omAddObjEx(var_r31, 10, 0, 0, -1, fn_1_4D8);
    fn_1_3274(var_r31);
    fn_1_7A34(var_r31);
}

void fn_1_4D8(omObjData *object)
{
    UnkM417Struct *var_r31;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x68, 268435456);
    var_r31 = object->data;
    memset(var_r31, 0, 0x68);
    var_r31->unk_00 = 0;
    var_r31->unk_04 = 0;
    var_r31->unk_0C = 0;
    var_r31->unk_10 = 0;
    var_r31->unk_14 = 0;
    var_r31->unk_18 = 0;
    var_r31->unk_24 = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_08 = 0;
    var_r31->unk_5C = 3;
    var_r31->unk_4C[0] = var_r31->unk_4C[1] = var_r31->unk_4C[2] = var_r31->unk_4C[3] = -1;
    var_r31->unk_60 = 0;
    var_r31->unk_64 = 0;
    object->func = fn_1_990;
}

void fn_1_5B0(omObjData *object)
{
    Vec sp14;
    Vec sp8;

    UnkM417Struct *var_r31;

    var_r31 = object->data;
    var_r31->unk_04++;
    var_r31->unk_10++;
    var_r31->unk_18++;
    var_r31->unk_28++;
    sp8.x = -(sind(CRot.y) * cosd(CRot.x));
    sp8.y = -(-sind(CRot.x));
    sp8.z = -(cosd(CRot.y) * cosd(CRot.x));
    sp14.x = Center.x - (sp8.x * CZoom);
    sp14.y = Center.y - (sp8.y * CZoom);
    sp14.z = Center.z - (sp8.z * CZoom);
    HuAudFXListnerUpdate(&sp14, &sp8);
    if (omSysExitReq && (var_r31->unk_00 != 5)) {
        var_r31->unk_00 = 4;
        fn_1_800(object);
    }
}

void fn_1_800(omObjData *object)
{
    UnkM417Struct *var_r31;

    var_r31 = object->data;
    if (var_r31->unk_08) {
        return;
    }
    switch (var_r31->unk_00) {
        case 0:
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            Hu3DCameraPerspectiveSet(1, 35.0f, 5.0f, 5000.0f, 1.2f);
            var_r31->unk_00 = 1;
            var_r31->unk_10 = 0;
            object->func = fn_1_BCAC(lbl_1_bss_20);
            break;
        case 1:
            var_r31->unk_00 = 2;
            var_r31->unk_18 = 0;
            object->func = fn_1_17C0;
            break;
        case 2:
            if (lbl_1_bss_0 < 0) {
                lbl_1_bss_0 = HuAudSStreamPlay(1);
            }
            var_r31->unk_00 = 3;
            var_r31->unk_28 = 0;
            object->func = fn_1_C658(lbl_1_bss_20, object);
            break;
        case 3:
        case 4:
            var_r31->unk_08 = 1;
            var_r31->unk_00 = 5;
            object->func = fn_1_EA8;
            break;
        case 5:
        default:
            var_r31->unk_00 = 5;
            object->func = fn_1_13DC;
            break;
    }
    var_r31->unk_04 = 0;
}

void fn_1_990(omObjData *object)
{
    fn_1_5B0(object);
    fn_1_800(object);
}

void fn_1_EA8(omObjData *object)
{
    UnkM417Struct *var_r27;

    var_r27 = object->data;

    fn_1_5B0(object);
    if (!WipeStatGet()) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        var_r27->unk_08 = 0;
        fn_1_800(object);
    }
}

void fn_1_13DC(omObjData *object)
{
    fn_1_5B0(object);
    if (!WipeStatGet()) {
        fn_1_33B4();
        CharModelKill(-1);
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_17C0(omObjData *object)
{
    s16 sp8; // ! - uninitialized

    UnkM417Struct *var_r30;

    var_r30 = object->data;
    fn_1_5B0(object);

    switch (var_r30->unk_14) {
        case 0:
            var_r30->unk_1C = 30;
            var_r30->unk_20 = 60;
            lbl_1_bss_12 = MGSeqCreate(3, 0);
            MGSeqPosSet(sp8, 320.0f, 240.0f);
            var_r30->unk_14 = 1;
            var_r30->unk_18 = 0;
            break;
        case 1:
            if (lbl_1_bss_4 < 0 && MGSeqStatGet(lbl_1_bss_12) & 16) {
                lbl_1_bss_4 = HuAudSeqPlay(72);
            }
            if (!MGSeqStatGet(lbl_1_bss_12) && !var_r30->unk_08) {
                lbl_1_bss_14 = MGSeqCreate(1, var_r30->unk_1C, -1, -1);
                var_r30->unk_14 = 2;
                var_r30->unk_18 = 0;
                object->func = fn_1_1CA8;
            }
            break;
        default:
            break;
    }
}

void fn_1_1CA8(omObjData *object)
{
    UnkM417Struct *var_r30;
    s32 var_r27;

    var_r30 = object->data;
    var_r27 = 0;
    fn_1_5B0(object);

    if (--var_r30->unk_20 == 0) {
        var_r30->unk_20 = 60;
        var_r30->unk_1C--;
        if (var_r30->unk_1C == 0) {
            var_r27 = 1;
        }
    }
    if (var_r30->unk_5C != 3) {
        var_r27 = 1;
    }
    if (var_r27) {
        if (var_r30->unk_5C == 3) {
            var_r30->unk_5C = 1;
        }
        lbl_1_bss_10 = MGSeqCreate(3, 1);
        MGSeqPosSet(lbl_1_bss_10, 320.0f, 240.0f);
        HuAudSeqFadeOut(lbl_1_bss_4, 100);
        var_r30->unk_14 = 3;
        var_r30->unk_18 = 0;
        if (var_r30->unk_08 == 0) {
            object->func = fn_1_2158;
        }
    }
    MGSeqParamSet(lbl_1_bss_14, 1, var_r30->unk_1C);
}

void fn_1_2158(omObjData *object)
{
    UnkM417Struct *var_r27;

    var_r27 = object->data;
    if (lbl_1_bss_14 >= 0) {
        MGSeqParamSet(lbl_1_bss_14, 2, -1);
        lbl_1_bss_14 = -1;
    }
    fn_1_5B0(object);
    if (fn_1_27D0() && var_r27->unk_60 == 4369) {
        var_r27->unk_14 = 4;
        var_r27->unk_18 = 0;
        fn_1_800(object);
    }
}

u32 fn_1_26C8(void)
{
    return ((UnkM417Struct *)lbl_1_bss_1C->data)->unk_00;
}

s32 fn_1_26E0(void)
{
    return ((UnkM417Struct *)lbl_1_bss_1C->data)->unk_0C;
}

u32 fn_1_26F8(void)
{
    return ((UnkM417Struct *)lbl_1_bss_1C->data)->unk_14;
}

u32 fn_1_2710(void)
{
    return ((UnkM417Struct *)lbl_1_bss_1C->data)->unk_24;
}

void fn_1_2728(u32 arg0)
{
    ((UnkM417Struct *)lbl_1_bss_1C->data)->unk_5C = arg0;
}

s32 fn_1_2740(s32 arg0)
{
    UnkM417Struct *var_r31;

    var_r31 = lbl_1_bss_1C->data;
    return var_r31->unk_4C[arg0];
}

void fn_1_2770(s32 arg0)
{
    ((UnkM417Struct *)lbl_1_bss_1C->data)->unk_60 |= (1 << ((arg0 & 3) * 4));
}

void fn_1_27A0(s32 arg0)
{
    ((UnkM417Struct *)lbl_1_bss_1C->data)->unk_64 |= (1 << ((arg0 & 3) * 4));
}

s32 fn_1_27D0(void)
{
    return !MGSeqStatGet(lbl_1_bss_10);
}

void fn_1_2808(s32 arg0, s32 arg1, s32 arg2)
{
    UnkM417Struct *var_r31;

    var_r31 = lbl_1_bss_1C->data;
    arg0 &= 3;
    var_r31->unk_2C[arg0] = arg1;
    var_r31->unk_3C[arg0] = arg2;
}

void fn_1_2848(Vec *arg0, Vec *arg1)
{
    Vec sp10;

    float var_f29;
    float var_f28;

    sp10.x = arg1->x - arg0->x;
    sp10.y = arg1->y - arg0->y;
    sp10.z = arg1->z - arg0->z;

    Center.x = arg1->x;
    Center.y = arg1->y;
    Center.z = arg1->z;

    var_f29 = (sp10.x * sp10.x) + (sp10.z * sp10.z);
    CRot.x = atan2d(sp10.y, sqrtf(var_f29));
    CRot.y = atan2d(-sp10.x, -sp10.z);
    CRot.z = 0.0f;

    var_f28 = (sp10.z * sp10.z) + ((sp10.x * sp10.x) + (sp10.y * sp10.y));
    CZoom = sqrtf(var_f28);
}

void fn_1_2B90(float arg8, float arg9, float argA, float argB, float argC, float argD)
{
    Vec sp40;
    Vec sp34;
    Vec sp28;

    float var_f29;
    float var_f28;

    sp40.x = arg8;
    sp40.y = arg9;
    sp40.z = argA;

    sp34.x = argB;
    sp34.y = argC;
    sp34.z = argD;

    sp28.x = sp34.x - sp40.x;
    sp28.y = sp34.y - sp40.y;
    sp28.z = sp34.z - sp40.z;

    Center.x = sp34.x;
    Center.y = sp34.y;
    Center.z = sp34.z;

    var_f29 = (sp28.x * sp28.x) + (sp28.z * sp28.z);
    CRot.x = atan2d(sp28.y, sqrtf(var_f29));
    CRot.y = atan2d(-sp28.x, -sp28.z);
    CRot.z = 0.0f;

    var_f28 = (sp28.z * sp28.z) + ((sp28.x * sp28.x) + (sp28.y * sp28.y));
    CZoom = sqrtf(var_f28);
}

float fn_1_2F08(float arg8, float arg9, float argA)
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

float fn_1_3024(float arg8, float arg9)
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

void fn_1_30D8(float *arg1, float *arg2, float *arg3, float *arg4)
{
    *arg2 = *arg3 = *arg4 = 0.0f;
    *arg2 = *arg3 = *arg4 = 0.0f;
}

void fn_1_310C(float arg8, float arg9, float argA, float *arg0, float *arg1, float *arg2)
{
    Mtx sp38;
    Mtx sp8;

    if (arg8 != 0.0f) {
        MTXRotRad(sp38, 88, 0.017453292f * arg8);
    }
    else {
        MTXIdentity(sp38);
    }
    if (arg9 != 0.0f) {
        MTXRotRad(sp8, 89, 0.017453292f * arg9);
        MTXConcat(sp38, sp8, sp38);
    }
    if (argA != 0.0f) {
        MTXRotRad(sp8, 90, 0.017453292f * argA);
        MTXConcat(sp38, sp8, sp38);
    }
    fn_1_30D8(NULL, arg0, arg1, arg2);
}
