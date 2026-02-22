#include "datadir_enum.h"
#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXVert.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/sprite.h"
#include "string.h"

#include "REL/m460Dll.h"

#ifndef __MWERKS__
#include "game/frand.h"
#endif

typedef struct UnkM460MapWork {
    s32 unk_00;
    u32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    char unk20[4];
    u32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    u32 unk_30;
    float unk_34;
    float unk_38;
    Vec unk_3C;
    Vec unk_48;
    HsfObject *unk_54;
    u32 unk_58;
    void *unk_5C;
} UnkM460MapWork; /* size = 0x60 */

void fn_1_6818(omObjData *object);
void fn_1_6C00(omObjData *object);
void fn_1_73F8(omObjData *object);
u32 fn_1_76C4(u32 arg0, u32 arg1);
void fn_1_7724(ModelData *model, Mtx mtx);
void fn_1_7790(ModelData *model, Mtx mtx);
void fn_1_7B94(s32 arg0);
void fn_1_7DA8(omObjData *object, Vec *arg1, u32 arg2);

float lbl_1_data_1E8[8][8] = {
    { 0.0f, 325.0f, -387.0f, -8.25f, 15.0f, 0.0f, 1208.0f, 38.65f },
    { 0.0f, 325.0f, -387.0f, -8.25f, -15.0f, 0.0f, 1208.0f, 38.65f },
    { 0.0f, 325.0f, -700.0f, -45.0f, 18.0f, 0.0f, 1500.0f, 41.5f },
    { 0.0f, 325.0f, -700.0f, -45.0f, 0.0f, 0.0f, 1500.0f, 41.5f },
    { 0.0f, 325.0f, -700.0f, -45.0f, -18.0f, 0.0f, 925.0f, 68.0f },
    { 0.0f, 302.0f, -783.0f, 14.25f, 28.5f, 0.0f, 833.0f, 61.0f },
    { 0.0f, 302.0f, -783.0f, 14.25f, 0.0f, 0.0f, 833.0f, 61.0f },
    { 0.0f, 302.0f, -783.0f, 14.25f, -28.5f, 0.0f, 833.0f, 61.0f },
};
float lbl_1_data_2E8[2][8] = {
    { -250.0f, 200.0f, -1000.0f, -10.0f, 0.0f, 0.0f, 1200.0f, 41.5f },
    { 250.0f, 200.0f, -1000.0f, -10.0f, 0.0f, 0.0f, 1200.0f, 41.5f },
};
s32 lbl_1_data_328[3] = { DATA_MAKE_NUM(DATADIR_M460, 0x00), DATA_MAKE_NUM(DATADIR_M460, 0x01), DATA_MAKE_NUM(DATADIR_M460, 0x02) };
s32 lbl_1_data_334[3] = { DATA_MAKE_NUM(DATADIR_M460, 0x03), DATA_MAKE_NUM(DATADIR_M460, 0x04), DATA_MAKE_NUM(DATADIR_M460, 0x05) };
s32 lbl_1_data_340[3] = { DATA_MAKE_NUM(DATADIR_M460, 0x06), DATA_MAKE_NUM(DATADIR_M460, 0x07), DATA_MAKE_NUM(DATADIR_M460, 0x08) };
s32 lbl_1_data_34C[2] = { DATA_MAKE_NUM(DATADIR_M460, 0x09), DATA_MAKE_NUM(DATADIR_M460, 0x0A) };
s32 lbl_1_data_354[2] = { DATA_MAKE_NUM(DATADIR_M460, 0x0B), DATA_MAKE_NUM(DATADIR_M460, 0x0C) };

// UnkM460MapWork
omObjData *lbl_1_bss_48;

void fn_1_67B4(Process *process)
{
    omObjData *var_r31 = omAddObjEx(process, 0x1E, 0x10, 0, -1, fn_1_6818);
    lbl_1_bss_48 = var_r31;
    var_r31->work[0] = 0;
}

void fn_1_6814(void) { }

void fn_1_6818(omObjData *object)
{
    s32 var_r31;
    s32 var_r30;
    UnkM460MapWork *var_r28;
    HsfanimStruct01 *var_r27;

    var_r28 = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM460MapWork), MEMORY_DEFAULT_NUM);
    memset(var_r28, 0, sizeof(UnkM460MapWork));
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r30 = Hu3DModelCreateFile(lbl_1_data_328[var_r31]);
        object->model[var_r31] = var_r30;
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r30 = Hu3DModelCreateFile(lbl_1_data_334[var_r31]);
        object->model[var_r31 + 3] = var_r30;
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r30 = Hu3DModelCreateFile(lbl_1_data_340[var_r31]);
        object->model[var_r31 + 6] = var_r30;
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r30 = Hu3DModelCreateFile(lbl_1_data_34C[var_r31]);
        object->model[var_r31 + 9] = var_r30;
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r30 = Hu3DModelCreateFile(lbl_1_data_354[var_r31]);
        object->model[var_r31 + 0xB] = var_r30;
        Hu3DModelLayerSet(var_r30, 3);
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    }
    var_r28->unk_08 = 8;
    fn_1_73F8(object);
    var_r30 = Hu3DHookFuncCreate(fn_1_7724);
    object->model[13] = var_r30;
    Hu3DModelCameraSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 7);
    var_r30 = Hu3DHookFuncCreate(fn_1_7790);
    object->model[14] = var_r30;
    Hu3DModelCameraSet(var_r30, 2);
    Hu3DModelLayerSet(var_r30, 7);
    var_r28->unk_58 = GXGetTexBufferSize(0x280, 0x1E0, 5, 0, 0);
    var_r28->unk_5C = HuMemDirectMallocNum(HEAP_SYSTEM, var_r28->unk_58, MEMORY_DEFAULT_NUM);
    DCFlushRange(var_r28->unk_5C, var_r28->unk_58);
    var_r30 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M460, 0x23)), 0x100);
    object->model[15] = var_r30;
    Hu3DModelLayerSet(var_r30, 4);
    for (var_r27 = ((ParticleData *)Hu3DData[var_r30].unk_120)->unk_48, var_r31 = 0; var_r31 < 0x100; var_r31++, var_r27++) {
        var_r27->unk2C = 0.0f;
        var_r27->unk40.a = 0;
        var_r27->unk00 = 0;
    }
    DCStoreRange(((ParticleData *)Hu3DData[var_r30].unk_120)->unk_48, 0x4400);
    var_r28->unk_28 = 1;
    var_r28->unk_2C = -1;
    object->func = fn_1_6C00;
}

void fn_1_6C00(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    UnkM460MapWork *var_r31;
    M460DllCameraStruct *var_r30;
    M460DllCameraStruct *var_r28;
    u32 var_r27;
    s32 var_r26;
    s32 var_r25;

    var_r31 = object->data;
    var_r30 = fn_1_3E90(1);
    var_r28 = fn_1_3E90(2);
    switch (fn_1_4164()) {
        case 1:
            var_r31->unk_18 = 0;
            var_r31->unk_1C = 0;
            var_r31->unk_24 = 0;
            if (var_r31->unk_00 != 0) {
                fn_1_73F8(object);
                var_r31->unk_00 = 0;
            }
            break;
        case 3:
            var_r27 = fn_1_42F0();
            Hu3DMotionSpeedSet(object->model[var_r27 + 9], 1.5f);
            if (var_r31->unk_18 == 0) {
                if (fn_1_4324() != 0) {
                    var_r31->unk_18 = 1;
                    if (var_r27 == 0) {
                        var_r31->unk_2C = object->model[var_r31->unk_14 + 3];
                        var_r31->unk_54 = Hu3DModelObjPtrGet(var_r31->unk_2C, "door_l");
                    }
                    else if (var_r27 == 1) {
                        var_r31->unk_2C = object->model[var_r31->unk_10 + 6];
                        var_r31->unk_54 = Hu3DModelObjPtrGet(var_r31->unk_2C, "door_r");
                    }
                    var_r31->unk_28 = 0;
                    var_r31->unk_30 = 0;
                    Hu3DModelAttrReset(object->model[var_r27 + 0xB], HU3D_ATTR_DISPOFF);
                }
            }
            else if (var_r31->unk_28 != 0) {
                fn_1_433C();
                var_r30->unk_10 -= 0.116666675f;
            }
            if (var_r31->unk_1C == 0) {
                var_r31->unk_24++;
                if (var_r31->unk_24 > 102.0f) {
                    var_r31->unk_1C = 1;
                    fn_1_8BA0(0.041666668f);
                    var_r30->unk_1C.x = lbl_1_data_2E8[var_r27][0];
                    var_r30->unk_1C.y = lbl_1_data_2E8[var_r27][1];
                    var_r30->unk_1C.z = lbl_1_data_2E8[var_r27][2];
                    var_r30->unk_28.x = lbl_1_data_2E8[var_r27][3];
                    var_r30->unk_28.y = lbl_1_data_2E8[var_r27][4];
                    var_r30->unk_28.z = lbl_1_data_2E8[var_r27][5];
                    var_r30->unk_34 = lbl_1_data_2E8[var_r27][6];
                    var_r30->unk_10 = lbl_1_data_2E8[var_r27][7];
                }
            }
            break;
        case 4:
            var_r30->unk_10 -= 0.116666675f;
            var_r31->unk_00 = 1;
            break;
    }
    if ((var_r31->unk_28 == 0) && (var_r31->unk_2C >= 0)) {
        if (var_r31->unk_30 == 0) {
            var_r31->unk_34 = 0.0f;
            var_r31->unk_38 = 0.0f;
            var_r31->unk_3C.x = var_r31->unk_3C.y = var_r31->unk_3C.z = 0.0f;
            var_r31->unk_48 = var_r31->unk_3C;
            var_r31->unk_38 = 2.9166667f;
            if (var_r31->unk_54) {
                sp14.x = var_r31->unk_54->data.base.pos.x;
                sp14.y = 10.0f + var_r31->unk_54->data.base.pos.y;
                sp14.z = 20.0f + var_r31->unk_54->data.base.pos.z;
                fn_1_7DA8(object, &sp14, 0);
            }
            HuAudFXPlay(0x818);
        }
        if (var_r31->unk_30 < 24.0f) {
            var_r31->unk_38 *= 0.93f;
        }
        else {
            var_f31 = 3.888889f;
            var_r31->unk_38 = var_r31->unk_38 + (0.033333335f * var_f31);
            if (var_r31->unk_38 > var_f31) {
                var_r31->unk_38 = var_f31;
            }
        }
        var_r26 = 0.5f + (0.2f * var_r31->unk_34);
        var_r31->unk_34 = var_r31->unk_34 + var_r31->unk_38;
        if (var_r31->unk_34 >= 350.0f) {
            var_r31->unk_34 = 350.0f;
            var_r31->unk_28 = 1;
            HuAudFXPlay(0x819);
            if (var_r31->unk_54) {
                sp14.x = var_r31->unk_54->data.base.pos.x;
                sp14.y = (var_r31->unk_54->data.base.pos.y + var_r31->unk_34) - 15.000001f;
                sp14.z = 10.0f + var_r31->unk_54->data.base.pos.z;
                fn_1_7DA8(object, &sp14, 2);
            }
        }
        var_r25 = 0.5f + (0.2f * var_r31->unk_34);
        if (var_r26 != var_r25) {
            var_r31->unk_48.x = 100.0f * ((0.00003f * frandmod(0x3E8)) - 0.015f);
            var_r31->unk_48.y = 100.0f * ((0.00006f * frandmod(0x3E8)) - 0.03f);
            var_r31->unk_48.z = 100.0f * ((0.00006f * frandmod(0x3E8)) - 0.03f);
            if (var_r31->unk_54) {
                sp14.x = var_r31->unk_54->data.base.pos.x;
                sp14.y = (var_r31->unk_54->data.base.pos.y + var_r31->unk_34) - 15.000001f;
                sp14.z = 15.000001f + var_r31->unk_54->data.base.pos.z;
                fn_1_7DA8(object, &sp14, 1);
            }
        }
        VECSubtract(&var_r31->unk_48, &var_r31->unk_3C, &sp8);
        VECScale(&sp8, &sp8, 0.4f);
        VECAdd(&var_r31->unk_3C, &sp8, &sp14);
        sp14.y += var_r31->unk_34;
        Hu3DModelPosSetV(var_r31->unk_2C, &sp14);
        var_r31->unk_30++;
    }
    fn_1_7B94(object->model[15]);
    if (var_r28->unk_00 != 0) {
        var_r28->unk_90 = var_r28->unk_90 + var_r28->unk_8C;
        if (var_r28->unk_90 > 1.0f) {
            var_r28->unk_00 = 0;
            var_r28->unk_90 = 1.0f;
            fn_1_3E68(1);
        }
    }
}

Vec lbl_1_data_36C = { 0.0f, 0.0f, 0.0f };
GXColor lbl_1_data_378 = { 0, 0, 0, 0x80 };

void fn_1_73F8(omObjData *object)
{
    UnkM460MapWork *var_r31;
    M460DllCameraStruct *var_r29;
    u32 var_r28;

    var_r31 = object->data;
    Hu3DModelAttrSet(object->model[var_r31->unk_0C], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[var_r31->unk_10 + 6], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[var_r31->unk_14 + 3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[11], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[12], HU3D_ATTR_DISPOFF);
    if (var_r31->unk_04 != 0) {
        var_r31->unk_0C = fn_1_76C4(3, var_r31->unk_0C);
        var_r31->unk_14 = fn_1_76C4(3, var_r31->unk_14);
        var_r31->unk_10 = fn_1_76C4(3, var_r31->unk_10);
        var_r29 = fn_1_3E90(1);
        var_r28 = var_r31->unk_08 = fn_1_76C4(8, var_r31->unk_08);
        var_r29->unk_1C.x = lbl_1_data_1E8[var_r28][0];
        var_r29->unk_1C.y = lbl_1_data_1E8[var_r28][1];
        var_r29->unk_1C.z = lbl_1_data_1E8[var_r28][2];
        var_r29->unk_28.x = lbl_1_data_1E8[var_r28][3];
        var_r29->unk_28.y = lbl_1_data_1E8[var_r28][4];
        var_r29->unk_28.z = lbl_1_data_1E8[var_r28][5];
        var_r29->unk_34 = lbl_1_data_1E8[var_r28][6];
        var_r29->unk_10 = lbl_1_data_1E8[var_r28][7];
    }
    Hu3DMotionTimeSet(object->model[9], 0.0f);
    Hu3DMotionSpeedSet(object->model[9], 0.0f);
    Hu3DMotionTimeSet(object->model[10], 0.0f);
    Hu3DMotionSpeedSet(object->model[10], 0.0f);
    Hu3DModelAttrReset(object->model[var_r31->unk_0C], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(object->model[var_r31->unk_14 + 3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(object->model[var_r31->unk_10 + 6], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSetV(object->model[var_r31->unk_14 + 3], &lbl_1_data_36C);
    Hu3DModelPosSetV(object->model[var_r31->unk_10 + 6], &lbl_1_data_36C);
    var_r31->unk_04++;
}

u32 fn_1_76C4(u32 arg0, u32 arg8)
{
    u32 var_r31 = frandmod(arg0);
    if (var_r31 == arg8) {
        var_r31++;
    }
    var_r31 %= arg0;
    return var_r31;
}

void fn_1_7724(ModelData *model, Mtx mtx)
{
    UnkM460MapWork *var_r31 = lbl_1_bss_48->data;
    GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
    GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB5A3, 0);
    GXCopyTex(var_r31->unk_5C, 0);
    GXPixModeSync();
}

void fn_1_7790(ModelData *model, Mtx mtx)
{
    Mtx sp5C;
    Mtx sp2C;
    GXTexObj spC;
    float var_f31;
    float var_f30;
    float var_f29;
    UnkM460MapWork *var_r31;
    M460DllCameraStruct *var_r30;

    var_r31 = lbl_1_bss_48->data;
    var_r30 = fn_1_3F2C(2);
    lbl_1_data_378.a = 255.0f * var_r30->unk_90;
    DCStoreRange(&lbl_1_data_378, 4);
    C_MTXPerspective(sp2C, 41.5f, 1.2f, 100.0f, 5500.0f);
    GXSetProjection(sp2C, GX_PERSPECTIVE);
    MTXIdentity(sp5C);
    GXLoadPosMtxImm(sp5C, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXInitTexObj(&spC, var_r31->unk_5C, 0x280, 0x1E0, 5, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&spC, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&spC, GX_TEXMAP0);
    C_MTXLightPerspective(sp2C, 41.5f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    GXLoadTexMtxImm(sp2C, 0x1E, GX_MTX3x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, 0x1E, 0, 0x7D);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, lbl_1_data_378);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetZMode(0, GX_LEQUAL, 0);
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
#ifdef TARGET_PC
    GXDestroyTexObj(&spC);
#endif
}

void fn_1_7B94(s32 arg0)
{
    HsfanimStruct01 *var_r31;
    ParticleData *var_r30;
    s32 var_r29;

    var_r30 = Hu3DData[arg0].unk_120;
    for (var_r31 = var_r30->unk_48, var_r29 = 0; var_r29 < var_r30->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00 != 0) {
            VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            switch (var_r31->unk02) {
                case 0:
                    var_r31->unk2C += 1.0f;
                    var_r31->unk20 *= 0.99f;
                    var_r31->unk08.y += 0.019444447f;
                    break;
                case 1:
                    var_r31->unk2C += 2.0f;
                    var_r31->unk20 *= 0.98f;
                    break;
                case 2:
                    var_r31->unk2C += 1.0f;
                    var_r31->unk20 *= 0.995f;
                    break;
            }
            if (var_r31->unk00 < 12.0f) {
                var_r31->unk20 = 0.9f * var_r31->unk20;
            }
            var_r31->unk40.a = var_r31->unk20;
            if (--var_r31->unk00 == 0) {
                var_r31->unk00 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(var_r30->unk_48, var_r30->unk_30 * 0x44);
}

void fn_1_7DA8(omObjData *object, Vec *arg1, u32 arg2)
{
    Vec sp1C;
    float var_f31;

    HsfanimStruct01 *var_r31;
    ParticleData *var_r30;
    s32 var_r28;
    u32 var_r27;

    GXColor spC = { 0xA2, 0x97, 0x7B, 0x80 };
    GXColor sp8 = { 0xE7, 0xDD, 0xC0, 0xFF };
    s32 sp10[3] = { 0x00000032, 4, 0x00000046 };

    var_r30 = Hu3DData[object->model[15]].unk_120;
    if (arg2 > 2) {
        arg2 = 1;
    }
    var_r27 = sp10[arg2];
    for (var_r31 = var_r30->unk_48, var_r28 = 0; var_r28 < var_r30->unk_30; var_r28++, var_r31++) {
        if (var_r31->unk00 == 0) {
            var_r31->unk02 = arg2;
            sp1C.x = 100.0f * ((0.0026f * frandmod(0x3E8)) - 1.3f);
            sp1C.y = 0.0f;
            sp1C.z = 100.0f * ((0.000100000005f * frandmod(0x3E8)) - 0.05f);
            VECAdd(&sp1C, arg1, &var_r31->unk34);
            var_r31->unk30 = 0.0031415902f * frandmod(0x3E8);
            switch (arg2) {
                case 0:
                    var_r31->unk00 = 60.0f * (0.8f + (0.0007f * frandmod(0x3E8)));
                    var_r31->unk08.x = 1.6666667f * (0.000100000005f * frandmod(0x3E8) - 0.05f);
                    var_r31->unk08.y = 1.6666667f * (0.05f + (0.00020000001f * frandmod(0x3E8)));
                    var_r31->unk08.z = 1.6666667f * (0.1f + (0.0006f * frandmod(0x3E8)));
                    var_f31 = 0.001f * frandmod(0x3E8);
                    var_r31->unk2C = 30.0f + (30.0f * var_f31);
                    var_r31->unk40.a = 40.0f + (40.0f * (1.0f - var_f31));
                    var_r31->unk40.r = spC.r + (var_f31 * (sp8.r - spC.r));
                    var_r31->unk40.g = spC.g + (var_f31 * (sp8.g - spC.g));
                    var_r31->unk40.b = spC.b + (var_f31 * (sp8.b - spC.b));
                    break;
                case 1:
                    sp1C.x = 100.0f * (1.1f + (0.00020000001f * frandmod(0x3E8)));
                    sp1C.y = 100.0f * (0.2f + (0.0005f * frandmod(0x3E8)));
                    if (frandmod(0x3E8) < 0x1F4) {
                        sp1C.x *= -1.0f;
                    }
                    VECAdd(&sp1C, arg1, &var_r31->unk34);
                    var_r31->unk00 = 60.0f * (0.2f + (0.0005f * frandmod(0x3E8)));
                    var_r31->unk08.x = 1.6666667f * ((0.000100000005f * frandmod(0x3E8)) - 0.05f);
                    var_r31->unk08.y = -1.6666667f * (0.2f + (0.0003f * frandmod(0x3E8)));
                    var_r31->unk08.z = 1.6666667f * (0.05f + (0.000100000005f * frandmod(0x3E8)));
                    var_f31 = 0.001f * frandmod(0x3E8);
                    var_r31->unk2C = 20.0f + (30.0f * var_f31);
                    var_r31->unk40.a = 8.0f + (13.0f * (1.0f - var_f31));
                    var_r31->unk40.r = spC.r + (var_f31 * (sp8.r - spC.r));
                    var_r31->unk40.g = spC.g + (var_f31 * (sp8.g - spC.g));
                    var_r31->unk40.b = spC.b + (var_f31 * (sp8.b - spC.b));
                    break;
                case 2:
                    var_r31->unk00 = 60.0f * (0.9f + (0.00080000004f * frandmod(0x3E8)));
                    var_r31->unk08.x = 1.6666667f * ((0.00020000001f * frandmod(0x3E8)) - 0.1f);
                    var_r31->unk08.y = -1.6666667f * (0.1f + (0.0007f * frandmod(0x3E8)));
                    var_r31->unk08.z = 1.6666667f * ((0.00020000001f * frandmod(0x3E8)) - 0.1f);
                    var_f31 = 0.001f * frandmod(0x3E8);
                    var_r31->unk2C = 40.0f + (60.0f * var_f31);
                    var_r31->unk40.a = 8.0f + (10.0f * (1.0f - var_f31));
                    var_r31->unk40.r = spC.r + (var_f31 * (sp8.r - spC.r));
                    var_r31->unk40.g = spC.g + (var_f31 * (sp8.g - spC.g));
                    var_r31->unk40.b = spC.b + (var_f31 * (sp8.b - spC.b));
                    break;
            }
            var_r31->unk20 = var_r31->unk40.a;
            var_r27--;
            if (var_r27 < 1) {
                break;
            }
        }
    }

    DCStoreRange(var_r30->unk_48, var_r30->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_8BA0(float arg8)
{
    M460DllCameraStruct *var_r31;
    M460DllCameraStruct *var_r30;

    var_r30 = fn_1_3E90(1);
    var_r31 = fn_1_3E90(2);
    var_r31->unk_00 = 1;
    var_r31->unk_1C = var_r30->unk_1C;
    var_r31->unk_28 = var_r30->unk_28;
    var_r31->unk_34 = var_r30->unk_34;
    var_r31->unk_10 = var_r30->unk_10;
    var_r31->unk_44 = var_r30->unk_44;
    var_r31->unk_40 = var_r30->unk_40;
    var_r31->unk_8C = arg8;
    var_r31->unk_90 = 0.0f;
    fn_1_3E68(2);
}

s32 fn_1_8C78(void)
{
    M460DllCameraStruct *var_r31 = fn_1_3E90(2);
    return var_r31->unk_00;
}
