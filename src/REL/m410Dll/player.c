#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/sprite.h"

#include <string.h>

#include "REL/m410Dll.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/frand.h"
#endif

omObjData *lbl_1_bss_74;
AnimData *lbl_1_bss_70;
s32 lbl_1_bss_60[4];

char *lbl_1_data_140[] = { "dmy-itemhook-r", "dmy-itemhook-r", "dmy-itemhook-r", "dmy-itemhook-r", "dmy-itemhook-r", "dmy-itemhook-r",
    "dmy-itemhook-r", "dmy-itemhook-r" };

char *lbl_1_data_16C[] = { "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r", "itemhook-r" };

s32 lbl_1_data_18C[] = {
    DATA_MAKE_NUM(DATADIR_M410, 0),
    DATA_MAKE_NUM(DATADIR_M410, 1),
    DATA_MAKE_NUM(DATADIR_M410, 2),
    DATA_MAKE_NUM(DATADIR_M410, 3),
    DATA_MAKE_NUM(DATADIR_M410, 4),
    DATA_MAKE_NUM(DATADIR_M410, 5),
    DATA_MAKE_NUM(DATADIR_M410, 6),
    DATA_MAKE_NUM(DATADIR_M410, 7),
};

u32 lbl_1_data_1AC[] = {
    0,
    DATA_MAKE_NUM(DATADIR_M410, 70),
    DATA_MAKE_NUM(DATADIR_M410, 22),
    DATA_MAKE_NUM(DATADIR_M410, 30),
    DATA_MAKE_NUM(DATADIR_M410, 38),
    DATA_MAKE_NUM(DATADIR_M410, 46),
    DATA_MAKE_NUM(DATADIR_M410, 62),
    DATA_MAKE_NUM(DATADIR_M410, 54),
    DATA_MAKE_NUM(DATADIR_E3SETUP, 23),
    DATA_MAKE_NUM(DATADIR_E3SETUP, 24),
};

UnkM410Struct10 lbl_1_data_1D4[] = {
    { 0.0f, 0.0f, 12.0f, HU3D_MOTATTR_LOOP },
    { 0.0f, 0.0f, 1.1999999f, HU3D_MOTATTR_NONE },
    { 0.0f, 0.0f, 12.0f, HU3D_MOTATTR_LOOP },
    { 0.0f, 0.0f, 6.0f, HU3D_MOTATTR_NONE },
    { 6.0f, 0.0f, 4.7999997f, HU3D_MOTATTR_NONE },
    { 0.0f, 0.0f, 1.1999999f, HU3D_MOTATTR_NONE },
    { 0.0f, 0.0f, 1.1999999f, HU3D_MOTATTR_NONE },
    { 0.0f, 0.0f, 1.1999999f, HU3D_MOTATTR_NONE },
    { 0.0f, 0.0f, 12.0f, HU3D_MOTATTR_NONE },
    { 0.0f, 0.0f, 12.0f, HU3D_MOTATTR_NONE },
};

s32 lbl_1_data_274[] = {
    DATA_MAKE_NUM(DATADIR_MGCONST, 0),
    DATA_MAKE_NUM(DATADIR_MGCONST, 1),
    DATA_MAKE_NUM(DATADIR_MGCONST, 2),
    DATA_MAKE_NUM(DATADIR_MGCONST, 3),
    DATA_MAKE_NUM(DATADIR_MGCONST, 4),
    DATA_MAKE_NUM(DATADIR_MGCONST, 5),
    DATA_MAKE_NUM(DATADIR_MGCONST, 6),
    DATA_MAKE_NUM(DATADIR_MGCONST, 7),
};

GXColor lbl_1_data_294[] = {
    { 102, 0, 0, 255 },
    { 0, 0, 102, 255 },
    { 102, 0, 91, 255 },
    { 0, 102, 0, 255 },
    { 66, 0, 76, 255 },
    { 71, 40, 0, 255 },
    { 102, 102, 0, 255 },
    { 0, 0, 0, 255 },
};

void fn_1_80A0(omObjData *object);
void fn_1_8414(omObjData *object);
void fn_1_8678(omObjData *object);
void fn_1_88D8(omObjData *object);
void fn_1_8A10(omObjData *object);
void fn_1_8ABC(omObjData *object);
void fn_1_9E0C(omObjData *arg0, u32 arg1);
void fn_1_96F4(omObjData *object);
s32 fn_1_9A90(omObjData *object);
s32 fn_1_9C84(omObjData *object);
s32 fn_1_9EFC(omObjData *object);
s32 fn_1_9F70(omObjData *object, u32 arg1);
void fn_1_A0A4(omObjData *object);
void fn_1_A3C0(omObjData *object);
void fn_1_A828(u16 arg0, u16 arg1, u16 arg2);
void fn_1_A9A4(UnkM410Struct13 *arg0);
void fn_1_B140(ModelData *arg0, Mtx arg1);

void fn_1_7E30(Process *objman)
{
    u32 sp18[4];
    u32 sp8[4];

    s16 var_r31;
    s16 var_r30;
    u32 var_r29;
    omObjData *var_r27;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp18[var_r31] = frandmod(1000);
        sp8[var_r31] = var_r31;
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        for (var_r30 = var_r31 + 1; var_r30 < 4; var_r30++) {
            if (sp18[var_r31] > sp18[var_r30]) {
                var_r29 = sp18[var_r31];
                sp18[var_r31] = sp18[var_r30];
                sp18[var_r30] = var_r29;
                var_r29 = sp8[var_r31];
                sp8[var_r31] = sp8[var_r30];
                sp8[var_r30] = var_r29;
            }
        }
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_60[sp8[var_r31]] = var_r31;
    }
    omMakeGroupEx(objman, 0, 4);
    omGetGroupMemberListEx(objman, 0);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r27 = omAddObjEx(objman, 40, 2, 10, 0, fn_1_80A0);
        var_r27->work[0] = var_r31;
    }
    lbl_1_bss_74 = omAddObjEx(objman, 10, 1, 0, -1, fn_1_A0A4);
    lbl_1_bss_70 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M410, 19), MEMORY_DEFAULT_NUM));
}

void fn_1_806C(void)
{
    HuSprAnimKill(lbl_1_bss_70);
    CharModelKill(-1);
}

void fn_1_80A0(omObjData *object)
{
    s32 sp8;

    UnkM410Struct5 *var_r31;
    s16 var_r29;
    s32 var_r28;
    s32 var_r27;

    UnkM410Struct6 spC = { { 0.0f, 0.13f, 0.26f, 0.4f } };
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 148, MEMORY_DEFAULT_NUM);
    var_r31 = object->data;
    memset(var_r31, 0, 148);
    var_r27 = object->work[0];
    var_r28 = GWPlayerCfg[var_r27].character;
    var_r31->unk_00 = var_r28;
    var_r31->unk_04 = lbl_1_bss_60[object->work[0]];
    sp8 = var_r31->unk_08 = 0;
    var_r31->unk_4C = spC.unk_00[GWPlayerCfg[var_r27].diff & 3];
    object->model[0] = CharModelCreate(var_r28, 2);
    Hu3DModelLayerSet(object->model[0], 4);
    Hu3DModelShadowSet(object->model[0]);
    object->model[1] = Hu3DModelCreateFile(lbl_1_data_18C[var_r28]);
    Hu3DModelShadowSet(object->model[1]);
    Hu3DModelLayerSet(object->model[1], 4);

    for (var_r29 = 0; var_r29 < 10; var_r29++) {
        if (lbl_1_data_1AC[var_r29] < 0x10000) {
            object->motion[var_r29] = CharModelMotionCreate(var_r28, lbl_1_data_1AC[var_r29]);
        }
        else {
            object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], var_r28 + lbl_1_data_1AC[var_r29]);
        }
    }
    CharModelMotionDataClose(var_r28);
    object->trans.x = var_r31->unk_58.x = 2.0f * var_r31->unk_04 * 100.0f - 300.0f;
    object->trans.y = var_r31->unk_58.y = 0.0f;
    object->trans.z = var_r31->unk_58.z = 0.0f;

    var_r31->unk_64 = var_r31->unk_68 = var_r31->unk_6C = 0.0f;
    var_r31->unk_3C = var_r31->unk_40 = 0.0f;
    var_r31->unk_44 = 0.0f;
    var_r31->unk_48 = 0.02f;
    var_r31->unk_70.x = var_r31->unk_58.x;
    var_r31->unk_70.y = 100.0f + var_r31->unk_58.y;
    var_r31->unk_70.z = 400.0f + var_r31->unk_58.z;
    var_r31->unk_14 = 1;
    var_r31->unk_0C = -1;
    fn_1_9E0C(object, 0);
    Hu3DModelPosSet(object->model[1], var_r31->unk_70.x, var_r31->unk_70.y, var_r31->unk_70.z);
    var_r31->unk_34 = 0;
    object->func = fn_1_8414;
}

void fn_1_8414(omObjData *object)
{
    UnkM410Struct5 *var_r31;

    var_r31 = object->data;
    {
        UnkM410Struct7 sp8 = { { 42, 78, 108, 125 } };

        switch (var_r31->unk_34) {
            case 0:
                fn_1_9F70(object, 0);
                if (fn_1_2804()) {
                    var_r31->unk_38 = 0;
                    var_r31->unk_34++;
                }
                break;
            case 1:
                if (var_r31->unk_38 >= sp8.unk_00[var_r31->unk_04]) {
                    var_r31->unk_28 = 1;
                    var_r31->unk_34++;
                }
                break;
            case 2:
                fn_1_96F4(object);
                if (var_r31->unk_38 >= (2.8f + 0.00040000002f * frandmod(1000)) * 60.0f) {
                    var_r31->unk_2C = 1;
                    var_r31->unk_38 = 0;
                    var_r31->unk_34++;
                }
                break;
            case 3:
                if (var_r31->unk_24) {
                    if (var_r31->unk_38 >= 27.0f) {
                        var_r31->unk_30 = 1;
                    }
                }
                if (fn_1_9A90(object)) {
                    var_r31->unk_34++;
                }
                break;
            case 4:
                fn_1_9F70(object, 0);
                break;
        }
    }
    fn_1_8A10(object);
    var_r31->unk_38++;
    if (fn_1_2804() == 2) {
        var_r31->unk_28 = 1;
        var_r31->unk_34 = 0;
        object->func = fn_1_8678;
    }
}

void fn_1_8678(omObjData *object)
{
    UnkM410Struct5 *var_r31 = object->data;
    s32 var_r29 = 0;
    var_r31->unk_10 = 0;
    if (fn_1_281C() == 2) {
        var_r31->unk_10 = HuPadBtnDown[GWPlayerCfg[object->work[0]].pad_idx];
        if (GWPlayerCfg[object->work[0]].iscom) {
            fn_1_8ABC(object);
        }
    }
    switch (var_r31->unk_34) {
        case 0:
            if (fn_1_9F70(object, 0)) {
                var_r31->unk_28 = 1;
            }
            fn_1_96F4(object);
            if (var_r31->unk_18) {
                var_r31->unk_34++;
            }
            break;
        case 1:
            if (!var_r31->unk_1C && !var_r31->unk_20) {
                if (var_r31->unk_10 & 0x100) {
                    if (fn_1_281C() == 2) {
                        var_r31->unk_2C = 1;
                    }
                }
                else if (var_r31->unk_10 & 0x200 && fn_1_281C() == 2) {
                    if (fabs(fn_1_30F0(var_r31->unk_3C, var_r31->unk_40)) < 45.0) {
                        var_r31->unk_30 = 1;
                    }
                }
                var_r29 = 1;
            }
            else if (var_r31->unk_24 && var_r31->unk_10 & 0x200) {
                var_r31->unk_30 = 1;
            }
            if (fn_1_9A90(object) || fn_1_9C84(object)) {
                var_r31->unk_36 = 0;
                var_r31->unk_34--;
            }
            break;
    }
    fn_1_8A10(object);
    if (fn_1_281C() == 3 && var_r29) {
        fn_1_287C(object->work[0]);
        var_r31->unk_34 = 0;
        object->func = fn_1_88D8;
    }
}

void fn_1_88D8(omObjData *object)
{
    UnkM410Struct5 *var_r31;

    var_r31 = object->data;
    fn_1_8A10(object);
    switch (var_r31->unk_34) {
        case 0:
            var_r31->unk_34++;
            return;
        case 1:
            if (fn_1_2834() == 1) {
                Hu3DModelHookReset(object->model[0]);
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
                if ((1 << object->work[0]) & fn_1_2864()) {
                    fn_1_9E0C(object, 8);
                }
                else {
                    fn_1_9E0C(object, 9);
                }
                var_r31->unk_40 = 0.0f;
                var_r31->unk_44 = 0.0f;
                var_r31->unk_48 = 0.005f;
                var_r31->unk_34++;
            }
            break;
        case 2:
            if (fn_1_9EFC(object)) {
                fn_1_28AC(object->work[0]);
                var_r31->unk_34++;
            }
            break;
        default:
            break;
    }
}

void fn_1_8A10(omObjData *object)
{
    UnkM410Struct5 *var_r31;

    var_r31 = object->data;
    var_r31->unk_36++;
    object->trans.x = var_r31->unk_58.x;
    object->trans.y = var_r31->unk_58.y;
    object->trans.z = var_r31->unk_58.z;

    var_r31->unk_44 += var_r31->unk_48;
    if (var_r31->unk_44 > 0.45f) {
        var_r31->unk_44 = 0.45f;
    }
    var_r31->unk_3C = fn_1_2FD4(var_r31->unk_3C, var_r31->unk_40, var_r31->unk_44);
    object->rot.y = var_r31->unk_3C;
}

void fn_1_8ABC(omObjData *object)
{
    Vec sp34;
    Vec sp28;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    UnkM410Struct5 *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = object->data;
    var_r31->unk_10 = 0;
    switch (var_r31->unk_50) {
        case 0:
            if (!var_r31->unk_18) {
                return;
            }
            if (frandmod(1000) <= 1000.0f * var_r31->unk_4C) {
                var_f28 = 42.0f;
                if (frandmod(1000) <= 1000.0f * var_r31->unk_4C) {
                    var_f29 = 280.0f;
                    var_r31->unk_54 = 31.8f + frandmod(6);
                }
                else {
                    var_f29 = 419.99997f;
                    var_r31->unk_54 = 9.0f + frandmod(15);
                }
                var_f27 = var_f28 + var_r31->unk_54;
                var_r29 = -1;
                var_f31 = 10000.0f;
                for (var_r30 = 0; var_r30 < 18; var_r30++) {
                    fn_1_7888(var_r30, (s32)var_f27, &sp28);
                    if (fabs(sp28.y - var_f29) > 10.0) {
                        continue;
                    }
                    fn_1_7840(var_r30, &sp34);
                    if (fabs(sp34.x) < 1.9166667461395264) {
                        continue;
                    }
                    var_f30 = sp28.x - var_r31->unk_88.x;
                    if (sp34.x >= 0.0f) {
                        if (var_f30 < 0.0f) {
                            if (fabs(var_f30) < var_f31) {
                                var_r29 = var_r30;
                                var_f31 = fabs(var_f30);
                            }
                        }
                    }
                    else if (var_f30 > 0.0f) {
                        if (fabs(var_f30) < var_f31) {
                            var_r29 = var_r30;
                            var_f31 = fabs(var_f30);
                        }
                    }
                }
                if (var_r29 < 0) {
                    return;
                }
                fn_1_7840(var_r29, &sp34);
                var_f31 /= fabs(sp34.x);
                var_r31->unk_52 = var_f27 + var_f31 - var_f28 - var_r31->unk_54;
            }
            else {
                var_r31->unk_52 = 24.0f + frandmod(36);
                var_r31->unk_54 = 12.0f + frandmod(18);
            }
            var_r31->unk_50++;
            return;
        case 1:
            if (!var_r31->unk_52) {
                var_r31->unk_10 |= 256;
                var_r31->unk_50++;
            }
            var_r31->unk_52--;
            return;
        case 2:
            if (!var_r31->unk_54) {
                var_r31->unk_10 |= 512;
                var_r31->unk_50 = 0;
            }
            var_r31->unk_54--;
            break;
    }
}

void fn_1_9040(omObjData *object)
{
    Mtx sp38;
    Vec sp2C;
    Vec sp20;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;

    UnkM410Struct5 *var_r31;
    s32 var_r29;
    s32 var_r28;
    s16 var_r27;

    var_r31 = object->data;
    fn_1_79F8(object->model[0], lbl_1_data_16C[var_r31->unk_08], sp38);

    var_r31->unk_70.x = sp38[0][3];
    var_r31->unk_70.y = sp38[1][3];
    var_r31->unk_70.z = sp38[2][3];

    if (fn_1_2804() == 1) {
        var_r31->unk_88 = var_r31->unk_70;
        var_r28 = -1;
        var_f30 = 10000.0f;

        for (var_r29 = 0; var_r29 < 18; var_r29++) {
            fn_1_77F8(var_r29, &sp20);
            if (sp20.y < 350.0f) {
                continue;
            }
            VECSubtract(&sp20, &var_r31->unk_58, &sp2C);
            var_f28 = VECMag(&sp2C);
            if (var_f28 < var_f30) {
                var_r28 = var_r29;
                var_f30 = var_f28;
            }
        }
        fn_1_77F8(var_r28, &sp20);
        var_f29 = 5.0f + sp20.y;
        var_f31 = 0.65f + 0.000100000005f * frandmod(1000);
        var_f26 = -3430.0002f;
        var_f27 = (var_f29 - var_r31->unk_70.y - (var_f31 * var_f31 * var_f26 * 0.5f)) / var_f31;
        sp2C.x = (0.016666668f * (sp20.x - var_r31->unk_70.x)) / var_f31;
        sp2C.y = 0.016666668f * var_f27;
        sp2C.z = (0.016666668f * (sp20.z - var_r31->unk_70.z)) / var_f31;
    }
    else {
        if (var_r31->unk_20 != 0) {
            var_f30 = -450.0f + (0.05f * frandmod(1000));
            var_f29 = -100.0f;
            var_f31 = 0.75f + (0.000100000005f * frandmod(1000));
            sp20.x = var_r31->unk_70.x + (0.05f * (frandmod(2000) - 1000));
            sp20.y = var_f29;
            sp20.z = var_f30;
        }
        else {
            var_f30 = -700.0f;
            var_f29 = 420.0f;
            if (var_r31->unk_68 < -600.0f) {
                var_f29 = 280.0f;
            }
            var_f31 = 0.65f + (0.000100000005f * frandmod(1000));
            var_r27 = 60.0f * var_f31;
            var_r28 = -1;
            var_f30 = 10000.0f;

            for (var_r29 = 0; var_r29 < 18; var_r29++) {
                fn_1_7888(var_r29, var_r27, &sp20);
                if (fabs(sp20.y - var_f29) > 20.0) {
                    continue;
                }
                var_f28 = fabs(sp20.x - var_r31->unk_88.x);
                if (var_f28 < var_f30) {
                    var_r28 = var_r29;
                    var_f30 = var_f28;
                }
            }
            var_f25 = 75.0f;
            if (GWPlayerCfg[object->work[0]].iscom) {
                var_f25 *= 0.25f;
            }
            if (var_r28 >= 0 && var_f30 <= var_f25) {
                fn_1_7888(var_r28, var_r27, &sp20);
            }
            else {
                sp20.x = var_r31->unk_88.x;
                sp20.y = var_f29;
                sp20.z = -700.0f;
            }
        }
        var_f26 = -3430.0002f;
        var_f27 = ((sp20.y - var_r31->unk_70.y) - var_f31 * var_f31 * var_f26 * 0.5f) / var_f31;
        sp2C.x = (sp20.x - var_r31->unk_70.x) * 0.016666668f / var_f31;
        sp2C.y = 0.016666668f * var_f27;
        sp2C.z = (sp20.z - var_r31->unk_70.z) * 0.016666668f / var_f31;
    }
    fn_1_76B8(var_r31->unk_70, sp2C, object->work[0]);
    var_r31->unk_18 = 0;
    var_r31->unk_24 = 0;
    if (var_r31->unk_1C) {
        fn_1_9E0C(object, 5);
    }
    Hu3DModelHookReset(object->model[0]);
    Hu3DModelPosSet(object->model[1], var_r31->unk_70.x, var_r31->unk_70.y, var_r31->unk_70.z);
}

void fn_1_96F4(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    UnkM410Struct5 *var_r31;

    var_r31 = object->data;
    if (!var_r31->unk_18 && (!var_r31->unk_14 || var_r31->unk_28)) {
        var_f29 = -3430.0002f;
        var_f30 = 70.0f + object->trans.y;
        var_f31 = 0.3f;
        if (var_r31->unk_14 && var_r31->unk_28) {
            var_r31->unk_14 = 0;
            var_r31->unk_28 = 0;
            Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
            var_r31->unk_36 = 0;
            var_r31->unk_70.x = object->trans.x;
            var_r31->unk_70.y = 100.0f + object->trans.y;
            var_r31->unk_70.z = 500.0f + object->trans.z;
            var_f28 = ((var_f30 - var_r31->unk_70.y) - (var_f31 * var_f31 * var_f29 * 0.5f)) / var_f31;
            var_f27 = 70.0f + object->trans.z;
            var_r31->unk_7C.x = 0.0f;
            var_r31->unk_7C.y = 0.016666668f * var_f28;
            var_r31->unk_7C.z = (0.016666668f * (var_f27 - var_r31->unk_70.z)) / var_f31;
            var_r31->unk_40 = 0.0f;
            var_r31->unk_44 = 0.0f;
            var_r31->unk_48 = 0.04f;
        }
        VECAdd(&var_r31->unk_70, &var_r31->unk_7C, &var_r31->unk_70);
        var_r31->unk_7C.y = var_r31->unk_7C.y + (0.0002777778f * var_f29);
        if ((var_r31->unk_7C.y < 0.0f) && (var_r31->unk_70.y <= var_f30)) {
            var_r31->unk_18 = 1;
            var_r31->unk_14 = 1;
            var_r31->unk_28 = 0;
            Hu3DModelHookSet(object->model[0], lbl_1_data_140[var_r31->unk_08], object->model[1]);
            CharModelMotionSpeedSet(var_r31->unk_00, 2.0f);
            var_r31->unk_40 = 180.0f;
            var_r31->unk_44 = 0.0f;
            var_r31->unk_48 = 0.005f;
            HuAudFXPlay(1376);
        }
        if (var_r31->unk_18 != 0) {
            Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
        }
        else {
            Hu3DModelPosSet(object->model[1], var_r31->unk_70.x, var_r31->unk_70.y, var_r31->unk_70.z);
        }
        if (var_r31->unk_36 >= (60.0f * (var_f31 - 0.17f))) {
            fn_1_9E0C(object, 1);
        }
    }
}

s32 fn_1_9A90(omObjData *object)
{
    UnkM410Struct5 *var_r31;
    s32 var_r29;

    var_r31 = object->data;
    var_r29 = 0;
    if (var_r31->unk_20) {
        return var_r29;
    }
    if (!var_r31->unk_18) {
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
    }
    if (var_r31->unk_18 && !var_r31->unk_1C && var_r31->unk_2C) {
        var_r31->unk_1C = 1;
        var_r31->unk_2C = 0;
        fn_1_9E0C(object, 4);
        var_r31->unk_48 = 0.05f;
        var_r31->unk_68 = 1300.0f;
    }
    if (var_r31->unk_1C) {
        var_r31->unk_58.y = var_r31->unk_58.y + (0.016666668f * var_r31->unk_68);
        var_r31->unk_68 += -66.66667014360428;
        if (var_r31->unk_58.y <= 0.0f) {
            var_r31->unk_1C = 0;
            if (var_r31->unk_18) {
                fn_1_9E0C(object, 7);
            }
            else {
                var_r29 = 1;
                fn_1_9E0C(object, 6);
            }
            var_r31->unk_58.y = 0.0f;
        }
        var_r31->unk_24 = 0;
        if (var_r31->unk_58.y >= 30.000002f && var_r31->unk_18) {
            var_r31->unk_24 = 1;
            if (var_r31->unk_30) {
                fn_1_9040(object);
                var_r31->unk_24 = 0;
                var_r31->unk_30 = 0;
            }
        }
    }
    else if (var_r31->unk_18) {
        fn_1_9F70(object, 2);
    }
    return var_r29;
}

s32 fn_1_9C84(omObjData *object)
{
    UnkM410Struct5 *var_r31;
    s32 var_r29;

    object = object;
    var_r31 = object->data;
    var_r29 = 0;
    if (!var_r31->unk_18) {
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
    }
    if (!var_r31->unk_20 && var_r31->unk_18 && !var_r31->unk_1C && var_r31->unk_30) {
        fn_1_9E0C(object, 3);
        var_r31->unk_30 = 0;
        var_r31->unk_20 = 1;
        var_r31->unk_36 = 0;
    }
    else if (var_r31->unk_20) {
        if (var_r31->unk_18) {
            if (var_r31->unk_36 >= 18.0f) {
                fn_1_9040(object);
            }
        }
        else if (var_r31->unk_36 >= 30.0f && fn_1_9EFC(object)) {
            var_r31->unk_30 = 0;
            var_r31->unk_2C = 0;
            var_r31->unk_20 = 0;
            var_r29 = 1;
        }
    }
    return var_r29;
}

void fn_1_9E0C(omObjData *object, u32 arg1)
{
    float var_f31;

    UnkM410Struct5 *var_r31;

    var_r31 = object->data;
    if ((var_r31->unk_0C != arg1) && (arg1 < 10)) {
        var_f31 = lbl_1_data_1D4[arg1].unk_08;
        if (var_r31->unk_0C < 0) {
            var_f31 = 0.0f;
        }
        var_r31->unk_0C = arg1;
        CharModelMotionShiftSet(var_r31->unk_00, object->motion[arg1], lbl_1_data_1D4[arg1].unk_00, var_f31, lbl_1_data_1D4[arg1].unk_0C);
        CharModelMotionSpeedSet(var_r31->unk_00, 1.0f);
    }
}

s32 fn_1_9EFC(omObjData *object)
{
    UnkM410Struct5 *var_r31;
    s32 var_r30;

    var_r31 = object->data;
    var_r30 = 0;
    if (CharModelMotionEndCheck(var_r31->unk_00) && (CharModelMotionShiftIDGet(var_r31->unk_00) < 0)) {
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_9F70(omObjData *object, u32 arg1)
{
    UnkM410Struct5 *var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r27 = 0;
    var_r28 = object->data;
    var_r26 = 0;
    if (CharModelMotionEndCheck(var_r28->unk_00) && (CharModelMotionShiftIDGet(var_r28->unk_00) < 0)) {
        var_r26 = 1;
    }
    if (var_r26) {
        fn_1_9E0C(object, arg1);
        var_r27 = 1;
    }
    return var_r27;
}

void fn_1_A0A4(omObjData *object)
{

    UnkM410Struct9 *var_r31;
    UnkM410Struct14 *var_r30;
    s32 var_r28;

    float sp8[4][2] = { { 36.0f, 64.0f }, { 476.0f, 64.0f }, { 36.0f, 416.0f }, { 476.0f, 416.0f } };
    object->stat |= 256;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM410Struct14), MEMORY_DEFAULT_NUM);
    var_r30 = object->data;
    memset(var_r30, 0, sizeof(UnkM410Struct14));
    var_r30->unk_F80 = GXGetTexBufferSize(640, 480, GX_TF_RGB5A3, GX_FALSE, 0);
    var_r30->unk_F84 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r30->unk_F80, MEMORY_DEFAULT_NUM);
    DCFlushRange(var_r30->unk_F84, var_r30->unk_F80);
    fn_1_A9A4(&var_r30->unk_120);
    var_r31 = var_r30->unk_00;

    for (var_r28 = 0; var_r28 < 4; var_r28++, var_r31++) {
        var_r31->unk_0C = sp8[lbl_1_bss_60[var_r28]][0];
        var_r31->unk_10 = sp8[lbl_1_bss_60[var_r28]][1];
        var_r31->unk_2C[0] = var_r31->unk_2C[1] = 1.0f;
        var_r31->unk_3C[0] = var_r31->unk_3C[1] = var_r31->unk_40 = var_r31->unk_42 = -1;
        var_r31->unk_3C[0] = espEntry(6357043, 2, 0);
        var_r31->unk_3C[1] = espEntry(6357043, 2, 0);
        var_r31->unk_40 = espEntry(lbl_1_data_274[GWPlayerCfg[var_r28].character], 2, 0);
        var_r31->unk_42 = espEntry(6357014, 3, 0);
        espPosSet(var_r31->unk_42, 36.0f + var_r31->unk_0C, var_r31->unk_10);
        var_r31->unk_44 = espEntry(6357015, 4, 0);
        espPosSet(var_r31->unk_44, 36.0f + var_r31->unk_0C, var_r31->unk_10);
        espColorSet(var_r31->unk_44, 0, 0, 0);
        espTPLvlSet(var_r31->unk_44, 0.5);
        espDispOff(var_r31->unk_3C[0]);
        espDispOff(var_r31->unk_3C[1]);
        espDispOff(var_r31->unk_40);
        espDispOff(var_r31->unk_42);
        espDispOff(var_r31->unk_44);
        var_r31->unk_00 = 0;
    }
    fn_1_77E8(fn_1_A828);
    object->model[0] = Hu3DHookFuncCreate(fn_1_B140);
    Hu3DModelLayerSet(object->model[0], 3);
    HuDataDirClose(DATADIR_MGCONST);
    object->func = fn_1_A3C0;
}

void fn_1_A3C0(omObjData *object)
{
    float var_f31;

    UnkM410Struct9 *var_r31;
    UnkM410Struct8 *var_r30;
    s32 var_r29;
    s32 var_r28;
    UnkM410Struct14 *var_r27;
    u32 var_r26;
    s32 var_r25;

    var_r27 = object->data;
    var_r31 = var_r27->unk_00;

    for (var_r29 = 0; var_r29 < 4; var_r29++, var_r31++) {
        switch (var_r31->unk_14) {
            case 0:
                if (fn_1_281C() == 2) {
                    var_r31->unk_14 = 1;
                }
                break;
            case 1:
                var_r31->unk_18 = 0;
                var_r31->unk_20 = var_r31->unk_08 % 10;
                var_r31->unk_1C = (var_r31->unk_08 / 10) % 10;
                espDispOn(var_r31->unk_3C[0]);
                espDispOn(var_r31->unk_3C[1]);
                espDispOn(var_r31->unk_40);
                espDispOn(var_r31->unk_42);
                espDispOn(var_r31->unk_44);
                espBankSet(var_r31->unk_3C[0], var_r31->unk_1C);
                espBankSet(var_r31->unk_3C[1], var_r31->unk_20);
                espBankSet(var_r31->unk_40, var_r31->unk_24);
                if (var_r31->unk_00) {
                    var_r31->unk_2C[0] = var_r31->unk_2C[1] = 0.5f;
                    var_r31->unk_14++;
                }
                else {
                    var_r31->unk_00 = 1;
                    var_r31->unk_2C[0] = var_r31->unk_2C[1] = 1.0f;
                    var_r31->unk_14 += 3;
                    break;
                }
            case 2:
                var_f31 = var_r31->unk_2C[0];
                var_f31 += 0.10000001f;
                if (var_f31 >= 1.5f) {
                    var_r31->unk_14++;
                }
                var_r31->unk_2C[0] = var_r31->unk_2C[1] = var_f31;
                break;
            case 3:
                var_f31 = var_r31->unk_2C[0];
                var_f31 -= 0.10000001f;
                if (var_f31 <= 1.0f) {
                    var_f31 = 1.0f;
                    var_r31->unk_14 = var_r31->unk_14 + 1;
                }
                var_r31->unk_2C[0] = var_r31->unk_2C[1] = var_f31;
                break;
        }
        var_r31->unk_18++;

        for (var_r28 = 0; var_r28 < 2; var_r28++) {
            espPosSet(var_r31->unk_3C[var_r28], 34.0f + var_r31->unk_0C + (21.0f * var_r28), 2.0f + var_r31->unk_10);
            espScaleSet(var_r31->unk_3C[var_r28], var_r31->unk_2C[var_r28], var_r31->unk_2C[var_r28]);
        }
        espPosSet(var_r31->unk_40, var_r31->unk_0C, var_r31->unk_10 - 2.0f);
    }
    var_r30 = var_r27->unk_120.unk_00;

    for (var_r29 = 0; var_r29 < 16; var_r29++, var_r30++) {
        if (var_r30->unk_00) {
            var_r30->unk_00++;
            if (var_r30->unk_00 < 12.0f) {
                var_r30->unk_04 += 0.058333337f;
            }
            else {
                var_r30->unk_04 += 0.025000002f;
                var_r30->unk_0C -= 0.050000004f;
            }
            if (var_r30->unk_0C < 0.0f) {
                var_r30->unk_00 = 0;
            }
        }
    }
    if (fn_1_281C() == 3) {
        var_r25 = 0;
        var_r31 = var_r27->unk_00;
        var_r26 = 0;

        for (var_r29 = 0; var_r29 < 4; var_r29++, var_r31++) {
            if (var_r31->unk_04 > var_r26) {
                var_r26 = var_r31->unk_04;
            }
        }
        if (var_r26) {
            var_r31 = var_r27->unk_00;

            for (var_r29 = 0; var_r29 < 4; var_r29++, var_r31++) {
                if (var_r31->unk_04 >= var_r26) {
                    var_r25 |= 1 << var_r29;
                }
            }
        }
        fn_1_284C(var_r25);
    }
}

void fn_1_A828(u16 arg0, u16 arg1, u16 arg2)
{
    UnkM410Struct8 *var_r31;
    UnkM410Struct9 *var_r30;
    s32 var_r29;
    UnkM410Struct14 *var_r27;

    var_r27 = lbl_1_bss_74->data;
    if (fn_1_281C() == 2 || fn_1_281C() == 3) {
        var_r30 = var_r27->unk_00;
        var_r30[arg0].unk_04 += arg1;
        var_r30[arg0].unk_08 += arg1;
        var_r30[arg0].unk_14 = 1;

        var_r31 = var_r27->unk_120.unk_00;

        for (var_r29 = 0; var_r29 < 16; var_r29++, var_r31++) {
            if (!var_r31->unk_00) {
                break;
            }
        }
        if (var_r29 < 16) {
            var_r31->unk_00 = 1;
            var_r31->unk_02 = GWPlayerCfg[arg0].character;
            var_r31->unk_0C = 1.0f;
            var_r31->unk_04 = 0.25f;
            var_r31->unk_08 = frandmod(360);
            fn_1_77F8(arg2, &var_r31->unk_10);
            var_r31->unk_10.y -= 30.000002f;
        }
    }
}

void fn_1_A9A4(UnkM410Struct13 *arg0)
{
    float sp88[32][2];
    float sp8[32];

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    s32 var_r31;
    UnkM410Struct12 *var_r29;
    UnkM410Struct11 *var_r28;

    var_f31 = 0.0f;
    for (var_r31 = 0; var_r31 < 32; var_r31++) {
        var_f28 = 1.0f + (0.001f * frandmod(1000));
        sp8[var_r31] = var_f28;
        var_f31 += var_f28;
        sp88[var_r31][1] = 80.0f * var_f28;
        sp88[var_r31][0] = 10.0f + (0.02f * frandmod(1000));
    }
    var_f31 = 360.0f / var_f31;
    for (var_r31 = 0; var_r31 < 32; var_r31++) {
        sp8[var_r31] *= var_f31;
    }
    var_f31 = frandmod(90);
    var_r28 = arg0->unk_1C0;
    var_r29 = arg0->unk_940;
    for (var_r31 = 0; var_r31 < 32; var_r28++, var_r29++, var_r31++) {
        var_f29 = -cosd(var_f31);
        var_f30 = sind(var_f31);
        var_r28->unk_24 = var_f29 * sp88[var_r31][0];
        var_r28->unk_28 = var_f30 * sp88[var_r31][0];
        var_r28->unk_0C = var_f29 * (sp88[var_r31][0] + sp88[var_r31][1]);
        var_r28->unk_10 = var_f30 * (sp88[var_r31][0] + sp88[var_r31][1]);
        var_r28->unk_00 = var_f29 * (sp88[var_r31][0] + (0.85f * sp88[var_r31][1]));
        var_r28->unk_04 = var_f30 * (sp88[var_r31][0] + (0.85f * sp88[var_r31][1]));
        var_r29->unk_00 = -0.3f * -var_f29;
        var_r29->unk_04 = -0.3f * var_f30;
        var_f29 = -cosd(var_f31 - (0.4f * sp8[var_r31]));
        var_f30 = sind(var_f31 - (0.4f * (&sp8[0])[var_r31]));
        var_r28->unk_30 = var_f29 * (sp88[var_r31][0] + (0.7f * sp88[var_r31][1]));
        var_r28->unk_34 = var_f30 * (sp88[var_r31][0] + (0.7f * sp88[var_r31][1]));
        var_f29 = -cosd(var_f31 + (0.4f * sp8[var_r31]));
        var_f30 = sind(var_f31 + (0.4f * sp8[var_r31]));
        var_r28->unk_18 = var_f29 * (sp88[var_r31][0] + (0.7f * sp88[var_r31][1]));
        var_r28->unk_1C = var_f30 * (sp88[var_r31][0] + (0.7f * sp88[var_r31][1]));
        var_r29->unk_08 = var_r29->unk_0C = var_r29->unk_10 = var_r29->unk_14 = 0.0f;
        var_r29->unk_18 = var_r29->unk_1C = var_r29->unk_20 = var_r29->unk_24 = 0.0f;
        var_f31 += sp8[var_r31];
    }

    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        arg0->unk_E40[var_r31].r = arg0->unk_E40[var_r31].g = arg0->unk_E40[var_r31].b = 255;
        arg0->unk_E40[var_r31].a = 255;
    }
    arg0->unk_E54 = 0x6C0;
    arg0->unk_E5C = HuMemDirectMallocNum(HEAP_SYSTEM, arg0->unk_E54, MEMORY_DEFAULT_NUM);
    DCFlushRange(arg0->unk_E5C, arg0->unk_E54);
    GXBeginDisplayList(arg0->unk_E5C, arg0->unk_E54);

    for (var_r31 = 0; var_r31 < 32; var_r31++) {
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 6);

        GXPosition1x16(var_r31 * 5);
        GXColor1x16(0);
        GXTexCoord1x16(var_r31 * 5);

        GXPosition1x16(var_r31 * 5 + 1);
        GXColor1x16(1);
        GXTexCoord1x16(var_r31 * 5 + 1);

        GXPosition1x16(var_r31 * 5 + 2);
        GXColor1x16(2);
        GXTexCoord1x16(var_r31 * 5 + 2);

        GXPosition1x16(var_r31 * 5 + 3);
        GXColor1x16(3);
        GXTexCoord1x16(var_r31 * 5 + 3);

        GXPosition1x16(var_r31 * 5 + 4);
        GXColor1x16(4);
        GXTexCoord1x16(var_r31 * 5 + 4);

        GXPosition1x16(var_r31 * 5 + 1);
        GXColor1x16(1);
        GXTexCoord1x16(var_r31 * 5 + 1);
    }
    arg0->unk_E58 = GXEndDisplayList();
    DCStoreRange(arg0, sizeof(UnkM410Struct13));
}

void fn_1_B140(ModelData *arg0, Mtx arg1)
{
    Mtx sp124;
    Mtx spF4;
    Mtx spC4;
    Mtx sp94;
    Mtx sp64;
    Mtx sp34;
    GXTexObj sp14;

    UnkM410Struct8 *var_r31;
    UnkM410Struct14 *var_r30;
    s32 var_r29;

    var_r30 = lbl_1_bss_74->data;
    {
        GXColor sp10 = { 204, 204, 204, 204 };
        GXSetTexCopySrc(0, 0, 640, 480);
        GXSetTexCopyDst(640, 480, GX_TF_RGB5A3, GX_FALSE);
        GXCopyTex(var_r30->unk_F84, GX_FALSE);
        GXPixModeSync();
        DCStoreRange(&sp10, 4);

        DCStoreRange(&lbl_1_data_294, 32);
        MTXTrans(spF4, -400.0f, 400.0f, -700.0f);
        MTXConcat(Hu3DCameraMtx, spF4, sp64);
        GXLoadPosMtxImm(sp64, 0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
        GXInitTexObj(&sp14, var_r30->unk_F84, 640, 480, 5, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&sp14, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&sp14, GX_TEXMAP0);
        HuSprTexLoad(lbl_1_bss_70, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        GXSetNumTexGens(2);
        C_MTXLightPerspective(sp94, 41.5f, 1.2f, 0.5555555f, -0.5f, 0.5555555f, 0.5f);
        MTXConcat(sp94, Hu3DCameraMtx, sp94);
        MTXInverse(Hu3DCameraMtx, sp34);
        MTXConcat(sp34, sp64, sp124);
        MTXConcat(sp94, sp124, spF4);
        GXLoadTexMtxImm(spF4, 30, GX_MTX3x4);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, 30, GX_FALSE, 125);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEXCOORD0, 33, GX_FALSE, 125);
        GXSetNumIndStages(1);
        GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
        GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
        GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
        MTXScale(spF4, -0.5f, -0.5f, 0.5f);
        GXSetIndTexMtx(GX_ITM_0, (float(*)[3])spF4, -1);
        GXSetNumTevStages(1);
        GXSetTevColor(GX_TEVREG1, sp10);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_C0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_A0, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSETARRAY(GX_VA_POS, var_r30->unk_120.unk_1C0, sizeof(var_r30->unk_120.unk_1C0), sizeof(Vec));
        GXSETARRAY(GX_VA_CLR0, var_r30->unk_120.unk_E40, sizeof(var_r30->unk_120.unk_E40), sizeof(GXColor));
        GXSETARRAY(GX_VA_TEX0, var_r30->unk_120.unk_940, sizeof(var_r30->unk_120.unk_940), sizeof(Vec2f));
        var_r31 = var_r30->unk_120.unk_00;

        for (var_r29 = 0; var_r29 < 16; var_r29++, var_r31++) {
            if (var_r31->unk_00) {
                lbl_1_data_294[var_r31->unk_02].a = 255.0f * var_r31->unk_0C;
                GXSetTevColor(GX_TEVREG0, lbl_1_data_294[var_r31->unk_02]);
                MTXTrans(spF4, var_r31->unk_10.x, var_r31->unk_10.y, var_r31->unk_10.z);
                MTXRotRad(sp124, 90, 0.017453292f * var_r31->unk_08);
                MTXConcat(spF4, sp124, spF4);
                MTXScale(spC4, var_r31->unk_04, var_r31->unk_04, var_r31->unk_04);
                MTXConcat(spF4, spC4, spF4);
                MTXConcat(Hu3DCameraMtx, spF4, sp64);
                GXLoadPosMtxImm(sp64, 0);
                MTXConcat(sp34, sp64, sp124);
                MTXConcat(sp94, sp124, spF4);
                GXLoadTexMtxImm(spF4, 30, GX_MTX3x4);
                MTXRotRad(sp124, 90, 0.017453292f * -var_r31->unk_08);
                GXLoadTexMtxImm(sp124, 33, GX_MTX2x4);
                GXCallDisplayListNative(var_r30->unk_120.unk_E5C, var_r30->unk_120.unk_E58);
            }
        }
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
    }
#ifdef TARGET_PC
    GXDestroyTexObj(&sp14);
#endif
}
