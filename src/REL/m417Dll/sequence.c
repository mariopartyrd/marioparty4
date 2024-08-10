#include "ext_math.h"
#include "game/audio.h"
#include "game/hsfdraw.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"

#include "REL/m417Dll.h"

typedef struct UnkM417Struct7 {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ char unk14[0x10];
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ u32 unk_28;
    /* 0x2C */ s32 unk_2C[4];
    /* 0x3C */ s32 unk_3C[4];
    /* 0x3C */ s32 unk_4C[4];
    /* 0x5C */ u32 unk_5C;
} UnkM417Struct7; /* size = unknown */

void fn_1_BD9C(omObjData *object);
void fn_1_BFB0(omObjData *object);
void fn_1_C050(omObjData *object);
void fn_1_C434(omObjData *object);
void fn_1_C78C(omObjData *object);

extern omObjData *lbl_1_bss_8AC;
extern s32 lbl_1_bss_8A8;

omObjFunc fn_1_BCAC(Process *arg0)
{
    CRot.x = -80.5f;
    CRot.y = CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    CZoom = 1000.0f;
    lbl_1_bss_8AC = omAddObjEx(arg0, 30, 1, 0, -1, fn_1_BFB0);
    return fn_1_BD9C;
}

void fn_1_BD9C(omObjData *object)
{
    Vec sp8;

    float var_f31;

    UnkM417Struct7 *var_r31;
    s32 var_r29;

    var_r31 = object->data;
    {
        Vec sp2C[2] = { { -400.0f, 0.0f, -200.0f }, { 0.0f, 150.0f, 0.0f } };
        Vec sp14[2] = { { -50.0f, 30.0f, 1500.0f }, { -50.0f, 0.0f, 2700.0f } };

        var_r29 = 60;
        fn_1_5B0(object);
        if (var_r31->unk_10 < var_r29) {
            var_f31 = 0.0f;
        } else {
            var_f31 = 0.0055555557f * (var_r31->unk_10 - var_r29);
        }
        PSVECSubtract(&sp2C[1], &sp2C[0], &sp8);
        PSVECScale(&sp8, &sp8, var_f31);
        PSVECAdd(&sp2C[0], &sp8, &sp8);
        Center.x = sp8.x;
        Center.y = sp8.y;
        Center.z = sp8.z;
        PSVECSubtract(&sp14[1], &sp14[0], &sp8);
        PSVECScale(&sp8, &sp8, var_f31);
        PSVECAdd(&sp14[0], &sp8, &sp8);
        CRot.x = sp8.x;
        CRot.y = sp8.y;
        CRot.z = 0.0f;
        CZoom = sp8.z;
        if (var_f31 >= 1.0f) {
            fn_1_800(object);
        }
    }
}

void fn_1_BFB0(omObjData *object)
{
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M417, 5));
    object->trans.x = -300.0f;
    object->trans.z = -200.0f;
    object->trans.y = 0.0f;
    object->rot.y = 20.0f;
    object->work[0] = object->work[1] = 0;
    object->func = fn_1_C050;
}

void fn_1_C050(omObjData *object)
{
    float var_f31;
    float var_f30;

    object->work[0] += 1;
    switch (object->work[1]) {
        case 0:
            if (object->work[0] > 0.0f) {
                fn_1_7510(-object->trans.x, object->trans.y, -object->trans.z, 1.0f);
                object->work[0] = 0;
                object->work[1] += 1;
            }
            break;
        case 1:
            if (object->work[0] == 60.0f) {
                omVibrate(0, 12, 6, 6);
                omVibrate(1, 12, 6, 6);
                omVibrate(2, 12, 6, 6);
                omVibrate(3, 12, 6, 6);
            }
            if (object->work[0] > 96.0f) {
                object->work[0] = 0;
                object->work[1] += 1;
            }
            break;
        case 2:
            var_f31 = 3.0f * object->work[0];
            object->rot.z = var_f31;
            var_f30 = 0.5 + (0.5 * -cosd(var_f31));
            object->trans.x = -300.0f - (200.0f * var_f30);
            object->trans.z = -200.0f - (50.0f * var_f30);
            var_f31 = 6.0f * object->work[0];
            if (var_f31 >= 180.0f) {
                var_f30 = 0.5 + (0.5 * cosd(var_f31));
                object->trans.y += -5.0f * var_f30;
            }
            if (object->work[0] > 60.0f) {
                object->work[0] = 0;
                object->work[1] += 1;
            }
            break;
        default:
            object->work[2] = 0;
            object->func = fn_1_C434;
            break;
    }
    object->trans.y += 0.05f * (fn_1_78BC(object->trans.x, 0.0f, object->trans.z) - object->trans.y);
}

void fn_1_C434(omObjData *object)
{
    float var_f31;

    object->work[0] = (object->work[0] + 1) % 120;
    var_f31 = 6.0f * object->work[0];
    object->rot.z = 180.0 + (10.0 * sind(var_f31));
    var_f31 = 3.0f * object->work[0];
    object->rot.x = 5.0 * sind(var_f31);
    if (object->work[2] < 120.0f) {
        object->work[2] += 1;
    }
    var_f31 = 100.0f * (-2.0f * (0.008333334f * object->work[2]));
    object->trans.y += 0.1f * ((var_f31 + fn_1_78BC(object->trans.x, 0.0f, object->trans.z)) - object->trans.y);
}

omObjFunc fn_1_C658(Process *arg0, omObjData *object)
{
    UnkM417Struct7 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s16 var_r28;
    s16 var_r27;

    var_r31 = object->data;
    var_r29 = 1;
    if (var_r31->unk_5C == 2) {
        var_r29 = 0;
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r31->unk_4C[var_r30] = -1;
        if (!var_r31->unk_2C[var_r30] == var_r29) {
            var_r31->unk_4C[var_r30] = var_r31->unk_3C[var_r30];
        }
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        if (var_r31->unk_4C[var_r30] >= 0) {
            GWPlayerCoinWinAdd(var_r30, 10);
        }
    }
    HuAudSStreamPlay(1);
    var_r31->unk_24 = 1;
    lbl_1_bss_8A8 = -1;
    return fn_1_C78C;
}

void fn_1_C78C(omObjData *object)
{
    UnkM417Struct7 *var_r31;

    var_r31 = object->data;
    fn_1_5B0(object);
    if (lbl_1_bss_8A8 < 0) {
        lbl_1_bss_8A8 = MGSeqCreate(5, 3, var_r31->unk_4C[0], var_r31->unk_4C[1], var_r31->unk_4C[2], var_r31->unk_4C[3]);
        return;
    }
    if (!MGSeqStatGet(lbl_1_bss_8A8) && var_r31->unk_28 >= 210.0f) {
        var_r31->unk_24 = 2;
        fn_1_800(object);
    }
}
