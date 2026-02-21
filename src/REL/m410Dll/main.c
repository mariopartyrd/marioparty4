#include "ext_math.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/wipe.h"

#include "REL/m410Dll.h"
#include "version.h"

Process *lbl_1_bss_28;
omObjData *lbl_1_bss_24;
omObjData *lbl_1_bss_20;
s16 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s16 lbl_1_bss_16;
s16 lbl_1_bss_14;
s16 lbl_1_bss_12;
s16 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

Vec lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };
Vec lbl_1_data_C = { 0.3f, -0.8f, 0.3f };
Vec lbl_1_data_18 = { 10.0f, 45.0f, 3500.0f };
GXColor lbl_1_data_24 = { 255, 255, 255, 255 };
Vec lbl_1_data_28 = { 50.0f, 150000.0f, 50.0f };
Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_40 = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_4C[] = {
    { -350.0f, 120.00001f, 0.0f },
    { -350.0f, 120.00001f, 0.0f },
    { 0.0f, 350.0f, -300.0f },
    { 0.0f, 350.0f, -300.0f },
    { 0.0f, 367.0f, 252.0f },
};
Vec lbl_1_data_88[] = {
    { 20.0f, -25.0f, 300.0f },
    { 20.0f, -25.0f, 300.0f },
    { 15.0f, 15.0f, 1100.0f },
    { 15.0f, 15.0f, 1100.0f },
    { -11.2f, 0.0f, 592.0f },
};

s32 lbl_1_data_C4[] = {
    REFRESH_RATE,
    REFRESH_RATE * 3 / 2,
    REFRESH_RATE * 9 / 5,
    REFRESH_RATE / 2,
    0
};

void fn_1_4E4(omObjData *object);
void fn_1_63C(omObjData *object);
void fn_1_7A8(omObjData *object);
void fn_1_ABC(omObjData *object);
void fn_1_DEC(omObjData *object);
void fn_1_FF0(omObjData *object);
void fn_1_139C(omObjData *object);
void fn_1_1648(omObjData *object);
omObjFunc fn_1_19C8(Process *objman, omObjData *object);
void fn_1_1A7C(omObjData *object);
omObjFunc fn_1_216C(Process *objman, omObjData *object);
void fn_1_2188(omObjData *object);

void ObjectSetup(void)
{
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    Process *var_r31;
    LightData *var_r30;

    HuAudSndGrpSet(35);
    lbl_1_bss_4 = lbl_1_bss_0 = -1;
    lbl_1_bss_C = lbl_1_bss_8 = -1;
    lbl_1_bss_1C = -1;
    lbl_1_data_28.x = 200.0f;
    lbl_1_data_28.y = 1200.0f;
    lbl_1_data_28.z = 160.0f;
    lbl_1_data_34.x = 0.0f;
    lbl_1_data_34.y = 1.0f;
    lbl_1_data_34.z = 0.0f;
    lbl_1_data_40.x = 0.0f;
    lbl_1_data_40.y = 0.0f;
    lbl_1_data_40.z = 0.0f;
    Hu3DShadowCreate(45.0f, 20.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.625f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    lbl_1_bss_16 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_16);
    var_r30 = &Hu3DGlobalLight[lbl_1_bss_16];
    var_r30->unk_00 = var_r30->unk_00 | 0x8000;
    lbl_1_data_18.x = 34.75f;
    lbl_1_data_18.y = -24.75f;
    lbl_1_data_18.z = 3500.0f;
    sp14.x = sp14.y = sp14.z = 0.0f;
    sp8.x = sp8.z = 0.0f;
    sp8.y = lbl_1_data_18.z;
    mtxRot(sp20, lbl_1_data_18.x, lbl_1_data_18.y, 0.0f);
    MTXMultVec(sp20, &sp8, &sp8);
    Hu3DGLightPosAimSetV(lbl_1_bss_16, &sp8, &sp14);
    Hu3DShadowPosSet(&sp8, &lbl_1_data_34, &sp14);
    lbl_1_bss_14 = lbl_1_bss_12 = lbl_1_bss_10 = -1;
    var_r31 = omInitObjMan(50, 8192);
    lbl_1_bss_28 = var_r31;
    omGameSysInit(var_r31);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, -1.0f, 5.0f, 5000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lbl_1_bss_20 = omAddObjEx(var_r31, 32730, 0, 0, -1, omOutView);
    lbl_1_bss_24 = omAddObjEx(var_r31, 10, 0, 0, -1, fn_1_4E4);
    fn_1_31A4(var_r31);
    fn_1_33A8(var_r31);
    fn_1_7E30(var_r31);
}

void fn_1_4E4(omObjData *object)
{
    UnkM410Struct *var_r31;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM410Struct), MEMORY_DEFAULT_NUM);
    var_r31 = object->data;
    memset(var_r31, 0, sizeof(UnkM410Struct));
    var_r31->unk_00 = 0;
    var_r31->unk_04 = 0;
    var_r31->unk_0C = 0;
    var_r31->unk_10 = 0;
    var_r31->unk_14 = 0;
    var_r31->unk_18 = 0;
    var_r31->unk_24 = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_08 = 0;
    var_r31->unk_2C = 0;
    var_r31->unk_30 = 0;
    var_r31->unk_34 = 0;
    object->func = fn_1_7A8;
}

void fn_1_5A8(omObjData *object)
{
    UnkM410Struct *var_r31;

    var_r31 = object->data;
    var_r31->unk_04++;
    var_r31->unk_10++;
    var_r31->unk_18++;
    var_r31->unk_28++;
    if (omSysExitReq && var_r31->unk_00 != 5) {
        var_r31->unk_00 = 4;
        fn_1_63C(object);
    }
}

void fn_1_63C(omObjData *object)
{
    UnkM410Struct *var_r31;

    var_r31 = object->data;

    if (var_r31->unk_08) {
        return;
    }
    switch (var_r31->unk_00) {
        case 0:
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            Hu3DCameraPerspectiveSet(1, 41.5f, 5.0f, 5000.0f, 1.2f);
            var_r31->unk_00 = 1;
            var_r31->unk_10 = 0;
            object->func = fn_1_19C8(lbl_1_bss_28, object);
            break;
        case 1:
            var_r31->unk_00 = 2;
            var_r31->unk_18 = 0;
            object->func = fn_1_FF0;
            break;
        case 2:
            var_r31->unk_00 = 3;
            var_r31->unk_28 = 0;
            object->func = fn_1_216C(lbl_1_bss_28, object);
            break;
        case 3:
        case 4:
            var_r31->unk_08 = 1;
            var_r31->unk_00 = 5;
            object->func = fn_1_ABC;
            break;
        case 5:
        default:
            var_r31->unk_00 = 5;
            object->func = fn_1_DEC;
            break;
    }
    var_r31->unk_04 = 0;
}

void fn_1_7A8(omObjData *object)
{
    fn_1_5A8(object);
    fn_1_63C(object);
}

void fn_1_ABC(omObjData *object)
{
    UnkM410Struct *var_r27;

    var_r27 = object->data;
    fn_1_5A8(object);
    if (!WipeStatGet()) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        var_r27->unk_08 = 0;
        fn_1_63C(object);
    }
}

void fn_1_DEC(omObjData *object)
{
    fn_1_5A8(object);
    if (!WipeStatGet()) {
        fn_1_806C();
        fn_1_3484();
        fn_1_31F8();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_FF0(omObjData *object)
{
    void *var_r31;
    UnkM410Struct *var_r29;
    void *var_r28;

    var_r29 = object->data;

    fn_1_5A8(object);
    switch (var_r29->unk_14) {
        case 0:
            var_r29->unk_1C = 30;
            var_r29->unk_20 = REFRESH_RATE;
            lbl_1_bss_14 = MGSeqCreate(3, 0);
            MGSeqPosSet(lbl_1_bss_14, 320.0f, 240.0f);
            CRot.x = -11.2f;
            CRot.y = CRot.z = 0.0f;
            Center.x = 0.0f;
            Center.y = 367.0f;
            Center.z = 252.0f;
            CZoom = 592.0f;
            var_r29->unk_14 = 1;
            var_r29->unk_18 = 0;
            break;

        case 1:
            if (lbl_1_bss_4 < 0 && MGSeqStatGet(lbl_1_bss_14) & 16) {
                lbl_1_bss_4 = HuAudSeqPlay(71);
            }
            if (!MGSeqStatGet(lbl_1_bss_14) && !var_r29->unk_08) {
                lbl_1_bss_1C = MGSeqCreate(1, var_r29->unk_1C, -1, -1);
                var_r29->unk_14 = 2;
                var_r29->unk_18 = 0;
                object->func = fn_1_139C;
            }
            break;

        default:
            break;
    }
}

void fn_1_139C(omObjData *object)
{
    UnkM410Struct *var_r29;
    s32 var_r27;

    var_r29 = object->data;
    var_r27 = 0;
    fn_1_5A8(object);

    if (!--var_r29->unk_20) {
        var_r29->unk_20 = REFRESH_RATE;
        var_r29->unk_1C--;
        if (!var_r29->unk_1C) {
            var_r27 = 1;
        }
    }
    if (var_r27) {
        lbl_1_bss_12 = MGSeqCreate(3, 1);
        MGSeqPosSet(lbl_1_bss_12, 320.0f, 240.0f);
        HuAudSeqFadeOut(lbl_1_bss_4, 100);
        var_r29->unk_14 = 3;
        var_r29->unk_18 = 0;
        if (var_r29->unk_08 == 0) {
            object->func = fn_1_1648;
        }
    }
    MGSeqParamSet(lbl_1_bss_1C, 1, var_r29->unk_1C);
}

void fn_1_1648(omObjData *object)
{
    UnkM410Struct *var_r27;

    var_r27 = object->data;
    if (lbl_1_bss_1C >= 0) {
        MGSeqParamSet(lbl_1_bss_1C, 2, -1);
        lbl_1_bss_1C = -1;
    }
    fn_1_5A8(object);

    if (!MGSeqStatGet(lbl_1_bss_12) && (var_r27->unk_30 + 0xFFFF0000 == 0x1111)) { // -4294897391
        var_r27->unk_14 = 4;
        var_r27->unk_18 = 0;
        fn_1_63C(object);
    }
}

omObjFunc fn_1_19C8(Process *objman, omObjData *object)
{
    CRot.x = -80.5f;
    CRot.y = CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    CZoom = 1000.0f;
    object->work[0] = object->work[1] = 0;
    return fn_1_1A7C;
}

void fn_1_1A7C(omObjData *object)
{
    Vec sp8;
    float var_f31;
    UnkM410Struct *var_r27;

    var_r27 = object->data;
    fn_1_5A8(object);
    var_r27->unk_0C = 1;
    object->work[0]++;

    if (!object->work[1] && object->work[0] > REFRESH_RATE_F / 5.0f) {
        if (lbl_1_bss_C < 0) {
            lbl_1_bss_C = HuAudFXPlay(1382);
        }
        if (lbl_1_bss_8 < 0) {
            lbl_1_bss_8 = HuAudFXPlay(1383);
        }
    }
    var_f31 = (float)object->work[0] / lbl_1_data_C4[object->work[1]];

    VECSubtract(&lbl_1_data_4C[object->work[1] + 1], &lbl_1_data_4C[object->work[1]], &sp8);
    VECScale(&sp8, &sp8, var_f31);
    VECAdd(&lbl_1_data_4C[object->work[1]], &sp8, &sp8);

    Center.x = sp8.x;
    Center.y = sp8.y;
    Center.z = sp8.z;

    VECSubtract(&lbl_1_data_88[object->work[1] + 1], &lbl_1_data_88[object->work[1]], &sp8);
    VECScale(&sp8, &sp8, var_f31);
    VECAdd(&lbl_1_data_88[object->work[1]], &sp8, &sp8);

    CRot.x = sp8.x;
    CRot.y = sp8.y;
    CRot.z = 0.0f;
    CZoom = sp8.z;

    if (var_f31 >= 1.0f) {
        object->work[0] = 0;
        object->work[1] += 1;
        if (!lbl_1_data_C4[object->work[1]]) {
            var_r27->unk_0C = 2;
            fn_1_63C(object);
        }
    }
}

omObjFunc fn_1_216C(Process *objman, omObjData *object)
{
    u32 sp8 = object->work[4];
    return fn_1_2188;
}

void fn_1_2188(omObjData *object)
{
    s32 sp10[5];
    UnkM410Struct *var_r27;
    s32 var_r26;
    u32 var_r25;
    s32 var_r24;

    var_r27 = object->data;
    fn_1_5A8(object);

    var_r27->unk_24 = 1;
    if (var_r27->unk_28 < REFRESH_RATE_F) {
#if VERSION_PAL
        Center.y -= 100.0f / REFRESH_RATE_F;
#else
        Center.y -= 100.0f / REFRESH_RATE_OFF_BY_1;
#endif
    }
    if (lbl_1_bss_10 < 0) {
        for (var_r24 = 0, var_r25 = 1, var_r26 = 0; var_r26 < 4; var_r25 *= 2, var_r26++) {
            sp10[var_r26] = -1;
            if (var_r27->unk_2C & var_r25) {
                sp10[var_r24++] = GWPlayerCfg[var_r26].character;
                GWPlayerCoinWinAdd(var_r26, 10);
            }
        }
        if (sp10[0] == -1) {
            lbl_1_bss_10 = MGSeqCreate(3, 2);
            if (lbl_1_bss_0 >= 0) {
                return;
            }
            lbl_1_bss_0 = HuAudSStreamPlay(4);
            return;
        }
        lbl_1_bss_10 = MGSeqCreate(5, 3, sp10[0], sp10[1], sp10[2], sp10[3]);
        if (lbl_1_bss_0 >= 0) {
            return;
        }
        lbl_1_bss_0 = HuAudSStreamPlay(1);
        return;
    }
    if (!MGSeqStatGet(lbl_1_bss_10)) {
        if (var_r27->unk_28 >= 3.5f * REFRESH_RATE_F) {
            var_r27->unk_24 = 2;
            fn_1_63C(object);
        }
    }
}

s32 fn_1_27EC(void)
{
    return ((UnkM410Struct *)lbl_1_bss_24->data)->unk_00;
}

u32 fn_1_2804(void)
{
    return ((UnkM410Struct *)lbl_1_bss_24->data)->unk_0C;
}

u32 fn_1_281C(void)
{
    return ((UnkM410Struct *)lbl_1_bss_24->data)->unk_14;
}

u32 fn_1_2834(void)
{
    return ((UnkM410Struct *)lbl_1_bss_24->data)->unk_24;
}

void fn_1_284C(s32 arg0)
{
    ((UnkM410Struct *)lbl_1_bss_24->data)->unk_2C = arg0;
}

u32 fn_1_2864(void)
{
    return ((UnkM410Struct *)lbl_1_bss_24->data)->unk_2C;
}

void fn_1_287C(s32 arg0)
{
    ((UnkM410Struct *)lbl_1_bss_24->data)->unk_30 |= (1 << ((arg0 & 7) * 4));
}

void fn_1_28AC(s32 arg0)
{
    ((UnkM410Struct *)lbl_1_bss_24->data)->unk_34 |= (1 << ((arg0 & 3) * 4));
}

s32 fn_1_28DC(void)
{
    return MGSeqStatGet(lbl_1_bss_12) == 0;
}

void fn_1_2914(Vec *arg0, Vec *arg1)
{
    Vec sp10;
    float var_f29;
    float var_f28;
    float var_f27;

    sp10.x = arg1->x - arg0->x;
    sp10.y = arg1->y - arg0->y;
    sp10.z = arg1->z - arg0->z;

    Center.x = arg1->x;
    Center.y = arg1->y;
    Center.z = arg1->z;

    CRot.x = atan2d(sp10.y, VECMagXZ(&sp10));
    CRot.y = atan2d(-sp10.x, -sp10.z);
    CRot.z = 0.0f;

    CZoom = VECMagPoint(sp10.x, sp10.y, sp10.z);
}

void fn_1_2C5C(float arg8, float arg9, float argA, float argB, float argC, float argD)
{
    Vec sp28;
    Vec sp14;
    Vec sp8;

    sp28.x = arg8;
    sp28.y = arg9;
    sp28.z = argA;

    sp14.x = argB;
    sp14.y = argC;
    sp14.z = argD;

    sp8.x = sp14.x - sp28.x;
    sp8.y = sp14.y - sp28.y;
    sp8.z = sp14.z - sp28.z;

    Center.x = sp14.x;
    Center.y = sp14.y;
    Center.z = sp14.z;

    CRot.x = atan2d(sp8.y, VECMagXZ(&sp8));
    CRot.y = atan2d(-sp8.x, -sp8.z);
    CRot.z = 0.0f;

    CZoom = VECMagPoint(sp8.x, sp8.y, sp8.z);
}

float fn_1_2FD4(float arg8, float arg9, float argA)
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

float fn_1_30F0(float arg8, float arg9)
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
