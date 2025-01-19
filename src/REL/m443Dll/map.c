#include "datadir_enum.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "REL/m443Dll.h"

void fn_1_4AB4(omObjData *object);
void fn_1_4D14(omObjData *object);

s32 lbl_1_data_240[5] = { 1, 2, 4, 8, 0x10 };

void fn_1_4A5C(Process *process)
{
    omObjData *var_r31 = omAddObjEx(process, 0x1E, 0xD, 0, -1, fn_1_4AB4);
    var_r31->work[0] = 0;
}

void fn_1_4AB0(void) { }

void fn_1_4AB4(omObjData *object)
{
    s32 var_r30;

    omSetTra(object, 0.0f, 0.0f, 0.0f);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M443, 0));
    Hu3DModelLayerSet(object->model[0], 2);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M443, 2));
    Hu3DModelLayerSet(object->model[2], 2);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M443, 4));
    Hu3DModelLayerSet(object->model[3], 2);
    Hu3DMotionSpeedSet(object->model[3], 0.0f);
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M443, 3));
    Hu3DModelLayerSet(object->model[4], 2);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        object->model[var_r30 + 5] = Hu3DModelLink(object->model[4]);
        Hu3DModelLayerSet(object->model[var_r30 + 5], 2);
        Hu3DModelScaleSet(object->model[var_r30 + 5], 0.93f, 0.93f, 0.93f);
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        object->model[var_r30 + 9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M443, 1));
        Hu3DModelLayerSet(object->model[var_r30 + 9], 2);
        Hu3DMotionSpeedSet(object->model[var_r30 + 9], 0.0f);
    }
    object->work[0] = 0;
    object->work[1] = 0;
    object->work[2] = 0;
    object->work[3] = 0;
    object->func = fn_1_4D14;
}

typedef struct M443DllMapUnkStruct {
    Vec unk_00[4];
    float unk_30;
} M443DllMapUnkStruct; /* size = 0x34 */

void fn_1_4D14(omObjData *object)
{
    float var_f31;
    float var_f30;

    M443DllCameraStruct *var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r28 = 1;
    {
        Mtx sp5C;
        Vec sp20;
        Vec sp14;
        Vec sp8 = { 0.0f, 0.0f, 0.0f };
        Vec sp2C[4] = {
            { -50.0f, 0.0f, -150.0f },
            { 50.0f, 0.0f, -150.0f },
            { -50.0f, 0.0f, -150.0f },
            { 50.0f, 0.0f, -150.0f },
        };

        for (var_r29 = 0; var_r29 < 5; var_r29++) {
            var_r30 = fn_1_40AC(lbl_1_data_240[var_r29]);
            sp20.x = var_r30->unk_1C.x + (var_r30->unk_34 * (sind(var_r30->unk_28.y) * cosd(var_r30->unk_28.x)));
            sp20.y = var_r30->unk_1C.y + (var_r30->unk_34 * -sind(var_r30->unk_28.x));
            sp20.z = var_r30->unk_1C.z + (var_r30->unk_34 * (cosd(var_r30->unk_28.y) * cosd(var_r30->unk_28.x)));
            Hu3DModelPosSetV(object->model[var_r29 + 4], &sp20);
            fn_1_421C(object->model[var_r29 + 4], lbl_1_data_240[var_r29]);
        }
        object->work[1] += 1;
        var_f31 = 150.0f;
        switch (object->work[0]) {
            case 0:
                if (fn_1_3FFC() == 4) {
                    object->work[0] += 1;
                    object->work[1] = 0;
                }
                break;
            case 1:
                var_f30 = 1.0f - (0.016666668f * object->work[1]);
                if (var_f30 <= 0.0f) {
                    object->work[0] += 1;
                    object->work[1] = 0;
                    var_f30 = 0.0f;
                }
                var_f31 = var_f31 * var_f30;
                break;
            case 2:
                var_f31 = 0.0f;
                if (fn_1_42E4() < 2) {
                    object->work[1] = 0;
                }
                if (object->work[1] >= 60.0f) {
                    object->work[0] += 1;
                    object->work[1] = 0;
                }
                break;
            case 3:
                var_f30 = 0.016666668f * object->work[1];
                if (var_f30 > 1.0f) {
                    object->work[0] += 1;
                    object->work[1] = 0;
                    var_r28 = 0;
                }
                var_f31 = var_f31 * var_f30;
                break;
            default:
                var_r28 = 0;
                break;
        }
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            var_r30 = fn_1_40AC(lbl_1_data_240[var_r29 + 1]);
            mtxRot(sp5C, var_r30->unk_28.x, var_r30->unk_28.y, 0.0f);
            sp8.z = var_r30->unk_34;
            MTXMultVec(sp5C, &sp8, &sp14);
            VECAdd(&var_r30->unk_1C, &sp14, &sp20);
            sp2C[var_r29].y += var_f31;
            MTXMultVec(sp5C, &sp2C[var_r29], &sp14);
            VECAdd(&sp20, &sp14, &sp20);
            Hu3DModelPosSetV(object->model[var_r29 + 9], &sp20);
            Hu3DModelRotSet(object->model[var_r29 + 9], var_r30->unk_28.x, var_r30->unk_28.y, 0.0f);
            Hu3DModelScaleSet(object->model[var_r29 + 9], 0.15f, 0.15f, 0.15f);
            fn_1_421C(object->model[var_r29 + 9], lbl_1_data_240[var_r29 + 1]);
            if (fn_1_42E4() >= 1) {
                if (object->work[2] == 0) {
                    object->work[2] = 1;
                    object->work[3] = 0;
                }
                Hu3DMotionSpeedSet(object->model[var_r29 + 9], 0.95f);
                if (var_r28 == 0) {
                    Hu3DModelAttrSet(object->model[var_r29 + 9], HU3D_ATTR_DISPOFF);
                }
            }
        }
        if (object->work[2] != 0) {
            object->work[3] += 1;
            if (object->work[3] >= 60.0f) {
                switch (object->work[2]) {
                    case 1:
                    case 2:
                        HuAudFXPlay(0x725);
                        break;
                    case 3:
                        HuAudFXPlay(0x726);
                        break;
                }
                object->work[2] += 1;
                object->work[3] = 0;
            }
        }
        if (fn_1_42E4() == 2) {
            Hu3DMotionSpeedSet(object->model[3], 1.0f);
        }
        else if (fn_1_42E4() == 5) {
            Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
        }
        if (fn_1_42E4() == 5) {
            Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
            Hu3DModelShadowMapSet(object->model[0]);
            Hu3DModelShadowMapSet(object->model[2]);
        }
    }
}
