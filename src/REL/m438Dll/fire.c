#include "REL/m438Dll.h"

#include "game/hsfdraw.h"
#define HUSPR_USE_OLD_DEFS
#include "game/sprite.h"

extern u8 texMtxTbl[];

// PROTO
void fn_1_E790(M438UnkStruct2 *);
void fn_1_F538(ModelData *, Mtx);
void fn_1_FAB8(M438UnkStruct *);
void fn_1_FD40(M438UnkStruct2 *);
void fn_1_10F0C(s16);
s32 fn_1_110B4(s16, u8, s16);

void fn_1_E658(s16 arg0, s16 arg1)
{
    M438UnkStruct2 *var_r29;
    s32 var_r31;
    M438UnkStruct3 *var_r30;

    lbl_1_bss_DE4.unk_34 = Hu3DHookFuncCreate(fn_1_F538);
    Hu3DModelLayerSet(lbl_1_bss_DE4.unk_34, 6);
    lbl_1_bss_DE4.unk_30 = arg0;
    var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(M438UnkStruct2), 0x10000000);
    lbl_1_bss_DE4.unk_40 = var_r29;
    lbl_1_bss_DE4.unk_32 = arg1;
    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(M438UnkStruct3), 0x10000000);
    lbl_1_bss_DE4.unk_3C = var_r30;

    for (var_r31 = 0; var_r31 < arg0; var_r31++, var_r29++) {
        var_r29->unk_08 = 0;
    }

    for (var_r31 = 0; var_r31 < arg1; var_r31++, var_r30++) {
        var_r30->unk_06 = 0;
        var_r30->unk_08 = 0;
    }
    lbl_1_bss_DE4.unk_36 = lbl_1_bss_DE4.unk_38 = lbl_1_bss_DE4.unk_3A = 0;
}

void fn_1_E790(M438UnkStruct2 *arg0)
{
    ModelData sp120;
    Mtx spF0;
    Mtx spC0;
    Mtx sp90;
    Mtx sp60;
    Mtx sp30;
    GXColor sp2C;
    s16 sp8;
    M438UnkStruct *var_r31;
    s16 var_r29;
    s16 var_r28;
    s32 var_r27;
    M438UnkStruct3 *temp_r26;
    s32 var_r25;
    s32 var_r24;
    s16 temp_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;

    mtxRot(sp60, arg0->unk_18.x, arg0->unk_18.y, arg0->unk_18.z);
    Scale(sp90, arg0->unk_24.x, arg0->unk_24.y, arg0->unk_24.z);
    Concat(sp60, sp90, sp90);
    mtxTransCat(sp90, arg0->unk_0C.x, arg0->unk_0C.y, arg0->unk_0C.z);
    Concat(Hu3DCameraMtx, sp90, spC0);
    var_r29 = 0;
    var_r28 = 0;
    sp8 = 0;
    for (var_r27 = GX_TEXMAP0; var_r27 < arg0->unk_04; var_r27++) {
        if (arg0->unk_34[var_r27] != 0) {
            temp_r26 = &lbl_1_bss_DE4.unk_3C[arg0->unk_34[var_r27]];
            Copy(temp_r26->unk_18, sp30);
            mtxTransCat(sp30, temp_r26->unk_0C.x, temp_r26->unk_0C.y, temp_r26->unk_0C.z);
            switch (temp_r26->unk_04) {
                case 0:
                    GXLoadTexMtxImm(sp30, texMtxTbl[var_r28], GX_MTX2x4);
                    var_r22 = texMtxTbl[var_r28];
                    GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r27 + 4, var_r22, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    if (var_r27 == GX_TEXMAP0) {
                        if ((temp_r26->unk_00->bmp->dataFmt == 7) || (temp_r26->unk_00->bmp->dataFmt == 8)) {
                            GXSetTevColor(GX_TEVREG2, temp_r26->unk_48);
                            GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_C2, GX_CC_RASC, GX_CC_ZERO);
                        }
                        else {
                            GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        }
                        GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                    }
                    else {
                        sp2C.a = temp_r26->unk_48.a;
                        GXSetTevColor(GX_TEVREG2, sp2C);
                        GXSetTevColorIn(var_r29, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A2, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                    }
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    break;
                case 1:
                    GXLoadTexMtxImm(sp30, texMtxTbl[var_r28], GX_MTX2x4);
                    var_r21 = texMtxTbl[var_r28];
                    GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r27 + 4, var_r21, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
                    GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    break;
                case 2:
                    sp2C.a = 0xE0;
                    GXSetTevColor(GX_TEVREG1, sp2C);
                    GXSetTexCoordGen2(var_r28 + 1, GX_TG_BUMP0, var_r28, 0x3C, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_RASC);
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
                    var_r29++;
                    GXSetTevOrder(var_r29, var_r28 + 1, GX_TEXMAP0, GX_COLOR0A0);
                    GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_CPREV);
                    GXSetTevColorOp(var_r29, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
                    break;
                case 3:
                    var_r28--;
                    GXLoadTexMtxImm(sp30, texMtxTbl[var_r28], GX_MTX2x4);
                    var_r20 = texMtxTbl[var_r28];
                    GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r27 + 4, var_r20, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    var_r28++;
                    break;
                case 4:
                    mtxRot(sp60, arg0->unk_18.x, arg0->unk_18.y, arg0->unk_18.z);
                    Scale(sp90, arg0->unk_24.x, arg0->unk_24.y, arg0->unk_24.z);
                    Concat(sp60, sp90, sp90);
                    mtxTransCat(sp90, arg0->unk_0C.x, arg0->unk_0C.y, arg0->unk_0C.z);
                    Concat(Hu3DCameraMtx, sp90, sp30);
                    Inverse(Hu3DCameraMtx, sp60);
                    Concat(sp60, sp30, sp60);
                    Concat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, sp90);
                    Concat(sp90, sp60, sp30);
                    GXLoadTexMtxImm(sp30, texMtxTbl[var_r28], GX_MTX3x4);
                    var_r19 = texMtxTbl[var_r28];
                    GXSetTexCoordGen2(var_r28, GX_TG_MTX3x4, GX_TG_POS, var_r19, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    if (var_r27 == GX_TEXMAP0) {
                        GXSetTevColorIn(var_r29, GX_CC_ONE, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                    }
                    else {
                        GXSetTevColorIn(var_r29, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
                        GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    }
                    GXSetTevColorOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    GXSetTevAlphaOp(var_r29, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVPREV);
                    break;
            }
            var_r29++;
            var_r28++;
            if (temp_r26->unk_4D != 0) {
                HuSprTexLoad(temp_r26->unk_00, 0, var_r27, 1, 1, 1);
            }
            else {
                HuSprTexLoad(temp_r26->unk_00, 0, var_r27, 0, 0, 1);
            }
        }
    }
    GXSetNumTevStages((s16)var_r29);
    GXSetNumTexGens((s16)var_r28);
    var_r31 = arg0->unk_3C;
    for (var_r24 = 0; var_r24 < arg0->unk_02; var_r24++, var_r31++) {
        if ((var_r31->unk_38 != 0) && ((var_r31->unk_38 & 4) == 0)) {
            switch (var_r31->unk_30) {
                case 0:
                    mtxRot(sp60, var_r31->unk_0C.x, var_r31->unk_0C.y, var_r31->unk_0C.z);
                    if (var_r31->unk_31 == 2) {
                        Concat(lbl_1_bss_DE4.unk_00, sp60, sp60);
                    }
                    else if (var_r31->unk_31 == 1) {
                        RotRad(sp90, 0x59, MTXDegToRad(CRot.y));
                        Concat(sp90, sp60, sp60);
                    }
                    Scale(sp90, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
                    Trans(sp30, var_r31->unk_24.x, var_r31->unk_24.y, var_r31->unk_24.z);
                    Concat(sp90, sp30, sp90);
                    Concat(sp60, sp90, sp90);
                    mtxTransCat(sp90, var_r31->unk_00.x, var_r31->unk_00.y, var_r31->unk_00.z);
                    Concat(Hu3DCameraMtx, sp90, spF0);
                    break;
                case 1:
                    mtxRot(sp60, var_r31->unk_0C.x, var_r31->unk_0C.y, var_r31->unk_0C.z);
                    if (var_r31->unk_31 == 2) {
                        if (HmfInverseMtxF3X3(spC0, sp90) == 0) {
                            Identity(sp90);
                        }
                        Concat(sp90, sp60, sp60);
                    }
                    else if (var_r31->unk_31 == 1) {
                        RotRad(sp90, 0x59, MTXDegToRad(CRot.y));
                        Concat(sp90, sp60, sp60);
                    }
                    Scale(sp90, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
                    Trans(sp30, var_r31->unk_24.x, var_r31->unk_24.y, var_r31->unk_24.z);
                    Concat(sp90, sp30, sp90);
                    Concat(sp60, sp90, sp90);
                    mtxTransCat(sp90, var_r31->unk_00.x, var_r31->unk_00.y, var_r31->unk_00.z);
                    Concat(spC0, sp90, spF0);
                    break;
            }
            GXLoadPosMtxImm(spF0, 0);
            Inverse(spF0, sp90);
            Transpose(sp90, sp60);
            GXLoadNrmMtxImm(sp60, 0);
            GXSetChanAmbColor(GX_COLOR0A0, var_r31->unk_50);
            GXSetChanMatColor(GX_COLOR0A0, var_r31->unk_54);
            GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
            GXSetZCompLoc(0);
            switch (var_r31->unk_33) {
                case 0:
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
                    break;
                case 1:
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
                    break;
                case 2:
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
                    break;
            }
            if ((var_r31->unk_38 & 0x10) != 0) {
                GXSetZMode(0, GX_LEQUAL, 1);
            }
            else {
                GXSetZMode(1, GX_LEQUAL, 0);
            }
            sp120.attr = 0;
            temp_r23 = Hu3DLightSet(&sp120, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, 0.0f);
            GXSetNumChans(1);
            if ((var_r31->unk_38 & 8) != 0) {
                var_r25 = GX_SRC_VTX;
            }
            else {
                var_r25 = GX_SRC_REG;
            }
            switch (var_r31->unk_32) {
                case 0:
                    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, var_r25, 0, GX_DF_CLAMP, GX_AF_NONE);
                    break;
                case 1:
                    GXSetChanCtrl(GX_COLOR0A0, 1, GX_SRC_REG, var_r25, temp_r23, GX_DF_CLAMP, GX_AF_SPOT);
                    break;
                case 2:
                    GXSetChanCtrl(GX_COLOR0A0, 1, GX_SRC_REG, var_r25, temp_r23, GX_DF_CLAMP, GX_AF_SPEC);
                    break;
            }
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
            GXSetArray(GX_VA_POS, var_r31->unk_44, 12);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetArray(GX_VA_CLR0, var_r31->unk_48, 4);
            for (var_r27 = 0; var_r27 < var_r31->unk_34; var_r27++) {
                GXSetVtxDesc(var_r27 + GX_VA_TEX0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, var_r27 + GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
                GXSetArray(var_r27 + GX_VA_TEX0, &var_r31->unk_58[var_r27].unk_04, 8);
            }
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_RGBA6, 0U);
            GXSetArray(GX_VA_NRM, var_r31->unk_4C, 12);
            GXCallDisplayList(var_r31->unk_40, var_r31->unk_3C);
        }
    }
}

void fn_1_F538(ModelData *arg0, Mtx arg1)
{
    Mtx sp38;
    Mtx sp8;
    M438UnkStruct2 *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_DE4.unk_40;
    GXLoadPosMtxImm(arg1, 0);
    Inverse(arg1, sp38);
    Transpose(sp38, sp8);
    GXLoadNrmMtxImm(sp8, 0);
    HmfInverseMtxF3X3(Hu3DCameraMtx, lbl_1_bss_DE4.unk_00);

    for (var_r30 = 0; var_r30 < lbl_1_bss_DE4.unk_30; var_r30++, var_r31++) {
        if ((var_r31->unk_08 != 0) && ((var_r31->unk_08 & 2) != 0) && ((var_r31->unk_08 & 4) == 0)) {
            if ((u8)omPauseChk() == 0) {
                if (var_r31->unk_30) {
                    var_r31->unk_30(var_r31);
                }
                if (var_r31->unk_08 == 0)
                    continue;
                fn_1_FD40(var_r31);
                if (var_r31->unk_08 == 0)
                    continue;
            }
            fn_1_E790(var_r31);
        }
    }
}

M438UnkStruct2 *fn_1_F664(s16 arg0)
{
    return &lbl_1_bss_DE4.unk_40[arg0];
}

M438UnkStruct *fn_1_F680(s16 arg0, s16 arg1)
{
    return &lbl_1_bss_DE4.unk_40[arg0].unk_3C[arg1];
}

M438UnkStruct3 *fn_1_F6AC(s16 arg0)
{
    return &lbl_1_bss_DE4.unk_3C[arg0];
}

void fn_1_F6C8(M438FireStruct **arg0, s16 arg1, f32 arg8, f32 arg9)
{
    s32 var_r30;
    M438FireStruct *var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(M438FireStruct), 0x10000000);

    for (var_r30 = 0; var_r30 < arg1; var_r31++, var_r30++) {
        var_r31->unk0.x = (-0.5f * arg8);
        var_r31->unk0.y = (0.5f * arg9);
        var_r31->unk0.z = 0.0f;
        var_r31->unkC.x = (0.5f * arg8);
        var_r31->unkC.y = (0.5f * arg9);
        var_r31->unkC.z = 0.0f;
        var_r31->unk18.x = (0.5f * arg8);
        var_r31->unk18.y = (-0.5f * arg9);
        var_r31->unk18.z = 0.0f;
        var_r31->unk24.x = (-0.5f * arg8);
        var_r31->unk24.y = (-0.5f * arg9);
        var_r31->unk24.z = 0.0f;
    }
}

void fn_1_F84C(M438FireStruct **arg0, s16 arg1, Vec *arg2)
{
    Vec *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r31 = (Vec *)*arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(M438FireStruct), 0x10000000);

    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
            var_r31->z = arg2->z;
        }
    }
}

void fn_1_F8EC(M438FireStruct2 **arg0, s16 arg1, GXColor *arg2)
{
    GXColor *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r31 = (GXColor *)*arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(M438FireStruct2), 0x10000000U);

    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->r = arg2->r;
            var_r31->g = arg2->g;
            var_r31->b = arg2->b;
            var_r31->a = arg2->a;
        }
    }
}

void fn_1_F994(Vec **arg0, s16 arg1, Vec *arg2)
{
    s32 var_r29;
    Vec *var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(Vec), 0x10000000);

    for (var_r29 = 0; var_r29 < arg1; var_r31++, arg2++, var_r29++) {
        var_r31->x = arg2->x;
        var_r31->y = arg2->y;
        var_r31->z = arg2->z;
    }
}

void fn_1_FA20(M438FireStruct3 **arg0, s16 arg1, HsfVector2f *arg2)
{
    HsfVector2f *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r31 = (HsfVector2f *)*arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(M438FireStruct3), 0x10000000);

    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
        }
    }
}

void fn_1_FAB8(M438UnkStruct *arg0)
{
    Vec sp1C[4] = { { -50.0f, 50.0f, 0.0f }, { 50.0f, 50.0f, 0.0f }, { 50.0f, -50.0f, 0.0f }, { -50.0f, -50.0f, 0.0f } };
    GXColor spC[4] = { { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF } };

    void *sp8;
    s32 var_r31;
    s32 var_r29;
    void *temp_r28;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        arg0->unk_44[var_r31] = sp1C[var_r31];
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        arg0->unk_48[var_r31] = spC[var_r31];
    }
    arg0->unk_4C->x = 0.0f;
    arg0->unk_4C->y = 0.0f;
    arg0->unk_4C->z = 1.0f;
    temp_r28 = arg0->unk_40;
    sp8 = temp_r28;
    GXBeginDisplayList(temp_r28, 0x100);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GXPosition1x16(var_r31);
        GXColor1x16(0);
        GXNormal1x16(var_r31);
        for (var_r29 = 0; var_r29 < arg0->unk_34; var_r29++) {
            GXTexCoord1x16(var_r31);
        }
    }
    arg0->unk_3C = GXEndDisplayList();
}

void fn_1_FD40(M438UnkStruct2 *arg0)
{
    M438UnkStruct *var_r28;
    M438UnkStruct3 *temp_r30;
    M438UnkSubStruct *var_r31;
    s32 temp_r0;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;

    var_r27 = 0;

    var_r28 = arg0->unk_3C;
    for (var_r25 = 0; var_r25 < arg0->unk_02; var_r25++, var_r28++) {
        if ((var_r28->unk_38 & 4) != 0) {
            var_r27++;
        }
        else {
            var_r31 = var_r28->unk_58;
            for (var_r26 = 0; var_r26 < var_r28->unk_34; var_r26++, var_r31++) {
                temp_r30 = &lbl_1_bss_DE4.unk_3C[arg0->unk_34[var_r26]];
                var_r31->unk_24 &= ~4;
                switch (var_r31->unk_24 & 0xF) {
                    case 1:
                        var_r31->unk_2C += var_r31->unk_28;
                        if (var_r31->unk_2C >= 1.0f) {
                            var_r31->unk_00++;
                            var_r31->unk_2C -= 1.0f;
                        }
                        break;
                    case 2:
                        var_r31->unk_2C += var_r31->unk_28;
                        if (var_r31->unk_2C >= 1.0f) {
                            var_r31->unk_00 -= 1;
                            var_r31->unk_2C -= 1.0f;
                        }
                        break;
                }
                if (var_r31->unk_00 >= temp_r30->unk_4C) {
                    if ((var_r31->unk_24 & 0x10) != 0) {
                        var_r31->unk_24 |= 8;
                        var_r31->unk_00 -= 1;
                    }
                    else if ((var_r31->unk_24 & 0x40) != 0) {
                        var_r31->unk_24 = (var_r31->unk_24 & 0xF0) | 2;
                        var_r31->unk_00 -= 2;
                    }
                    else if ((var_r31->unk_24 & 0x20) != 0) {
                        var_r31->unk_00 = 0;
                    }
                    var_r31->unk_24 |= 4;
                }
                else if (var_r31->unk_00 < 0) {
                    if ((var_r31->unk_24 & 0x10) != 0) {
                        var_r31->unk_24 |= 8;
                        var_r31->unk_00 = 0;
                    }
                    else if ((var_r31->unk_24 & 0x20) != 0) {
                        if ((var_r31->unk_24 & 0x40) != 0) {
                            var_r31->unk_24 = (var_r31->unk_24 & 0xF0) | 1;
                            var_r31->unk_00 = 1;
                        }
                        else {
                            var_r31->unk_00 = temp_r30->unk_4C - 1;
                        }
                    }
                    else if ((var_r31->unk_24 & 0x40) != 0) {
                        var_r31->unk_24 |= 8;
                        var_r31->unk_00 = 0;
                    }
                    var_r31->unk_24 |= 4;
                }
                else {
                    var_r31->unk_24 &= ~8;
                }
                if (var_r31->unk_00 != var_r31->unk_01) {
                    var_r31->unk_08 = (var_r31->unk_00 * temp_r30->unk_58);
                    var_r31->unk_10 = (var_r31->unk_00 * temp_r30->unk_58);
                    var_r31->unk_18 = ((var_r31->unk_00 + 1) * temp_r30->unk_58);
                    var_r31->unk_20 = ((var_r31->unk_00 + 1) * temp_r30->unk_58);
                    if ((var_r31->unk_00 + 1) < temp_r30->unk_4C) {
                        var_r31->unk_18 -= temp_r30->unk_60;
                        var_r31->unk_20 -= temp_r30->unk_60;
                    }
                    var_r31->unk_01 = var_r31->unk_00;
                    DCFlushRangeNoSync(&var_r31->unk_04, 0x20);
                }
                if ((var_r31->unk_24 & 8) != 0) {
                    if ((var_r28->unk_38 & 0x40000000) != 0) {
                        var_r28->unk_38 |= 4;
                        if ((var_r31->unk_24 & 0x40) == 0) {
                            if (var_r31->unk_00 <= 0) {
                                var_r31->unk_00 = temp_r30->unk_4C;
                            }
                            else {
                                var_r31->unk_00 = 0;
                            }
                        }
                    }
                    else if ((var_r28->unk_38 & 0x80000000) != 0) {
                        fn_1_107BC(arg0->unk_00);
                    }
                    var_r27++;
                }
            }
        }
    }
    if (var_r27 >= arg0->unk_02) {
        if ((arg0->unk_08 & 0x40000000) != 0) {
            arg0->unk_08 |= 4;
        }
        else if ((arg0->unk_08 & 0x80000000) != 0) {
            fn_1_107BC(arg0->unk_00);
        }
    }
    PPCSync();
}

s16 fn_1_10258(u8 arg0, u8 arg1)
{
    M438UnkStruct *var_r30;
    M438UnkStruct2 *var_r31;
    s32 var_r29;
    s32 var_r28;
    void *temp_r25;

    var_r31 = &lbl_1_bss_DE4.unk_40[1];

    for (var_r29 = 1; var_r29 < lbl_1_bss_DE4.unk_30; var_r29++, var_r31++) {
        if (var_r31->unk_08 == 0)
            break;
    }
    if (var_r29 == lbl_1_bss_DE4.unk_30) {
        OSReport("OVER BILL\n");
        return 0;
    }
    var_r31->unk_00 = var_r29;
    var_r31->unk_08 = 1;
    var_r31->unk_30 = NULL;
    var_r31->unk_02 = arg0;
    var_r31->unk_04 = arg1;
    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * 0x98, 0x10000000);
    var_r31->unk_3C = var_r30;
    var_r31->unk_34 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * 2, 0x10000000);
    var_r31->unk_48 = 0;
    var_r31->unk_4C = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 << 8, 0x10000000);
    var_r31->unk_50 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * 0x30, 0x10000000);
    var_r31->unk_54 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * 0x10, 0x10000000);
    var_r31->unk_58 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * 0xC, 0x10000000);
    var_r31->unk_5C = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * (arg0 * 0x30), 0x10000000);
    DCFlushRangeNoSync(var_r31->unk_4C, arg0 << 8);
    var_r31->unk_0C.x = var_r31->unk_0C.y = var_r31->unk_0C.z = 0.0f;
    var_r31->unk_18.x = var_r31->unk_18.y = var_r31->unk_18.z = 0.0f;
    var_r31->unk_24.x = var_r31->unk_24.y = var_r31->unk_24.z = 1.0f;
    var_r31->unk_70.x = var_r31->unk_70.y = var_r31->unk_70.z = 0.0f;
    var_r31->unk_64.x = var_r31->unk_64.y = var_r31->unk_64.z = 0.0f;
    var_r31->unk_60 = 0;

    for (var_r29 = 0; var_r29 < 0x20; var_r29++) {
        var_r31->unk_7Ca[var_r29] = 0;
    }

    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        var_r31->unk_34[var_r29] = 0;
    }

    for (var_r29 = 0; var_r29 < arg0; var_r29++, var_r30++) {
        var_r30->unk_38 = 1;
        var_r30->unk_34 = arg1;
        var_r30->unk_30 = 0;
        var_r30->unk_31 = 2;
        var_r30->unk_32 = 0;
        var_r30->unk_33 = 0;
        var_r30->unk_50.r = var_r30->unk_50.g = var_r30->unk_50.b = 0;
        var_r30->unk_50.a = 0xFF;
        var_r30->unk_54.r = var_r30->unk_54.g = var_r30->unk_54.b = 0xFF;
        var_r30->unk_54.a = 0xFF;
        var_r30->unk_58 = &var_r31->unk_5C[var_r29 * arg1];

        for (var_r28 = 0; var_r28 < arg1; var_r28++) {
            var_r30->unk_58[var_r28].unk_00 = var_r30->unk_58[var_r28].unk_01 = 0;
            var_r30->unk_58[var_r28].unk_28 = 1.0f;
            var_r30->unk_58[var_r28].unk_2C = 0.0f;
        }
        var_r30->unk_00.x = var_r30->unk_00.y = var_r30->unk_00.z = 0.0f;
        var_r30->unk_0C.x = var_r30->unk_0C.y = var_r30->unk_0C.z = 0.0f;
        var_r30->unk_18.x = var_r30->unk_18.y = var_r30->unk_18.z = 1.0f;
        var_r30->unk_6C.x = var_r30->unk_6C.y = var_r30->unk_6C.z = 0.0f;
        var_r30->unk_24.x = var_r30->unk_24.y = var_r30->unk_24.z = 0.0f;
        var_r30->unk_60.x = var_r30->unk_60.y = var_r30->unk_60.z = 0.0f;
        var_r30->unk_5C = 0;

        for (var_r28 = 0; var_r28 < 0x10; var_r28++) {
            var_r30->unk_78[var_r28] = 0;
        }
        var_r30->unk_44 = &var_r31->unk_50[var_r29 * 4];
        var_r30->unk_48 = &var_r31->unk_54[var_r29 * 4];
        var_r30->unk_4C = &var_r31->unk_58[var_r29];
        var_r30->unk_40 = ((char *)var_r31->unk_4C) + var_r31->unk_48;
        fn_1_FAB8(var_r30);
        var_r31->unk_48 += var_r30->unk_3C;
    }
    temp_r25 = var_r31->unk_4C;
    var_r31->unk_4C = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk_48, 0x10000000);
    memcpy(var_r31->unk_4C, temp_r25, var_r31->unk_48);
    HuMemDirectFree(temp_r25);
    DCFlushRangeNoSync(var_r31->unk_50, arg0 * 0x30);
    DCFlushRangeNoSync(var_r31->unk_54, arg0 * 0x10);
    DCFlushRangeNoSync(var_r31->unk_58, arg0 * 0xC);
    DCFlushRangeNoSync(var_r31->unk_4C, var_r31->unk_48);
    var_r30 = var_r31->unk_3C;
    var_r31->unk_48 = 0;

    for (var_r29 = 0; var_r29 < arg0; var_r29++, var_r30++) {
        var_r30->unk_40 = ((char *)var_r31->unk_4C) + var_r31->unk_48;
        var_r31->unk_48 += var_r30->unk_3C;
    }
    lbl_1_bss_DE4.unk_36 = var_r31->unk_00;
    lbl_1_bss_DE4.unk_38 = 0;
    lbl_1_bss_DE4.unk_3A = 0;
    PPCSync();
    return var_r31->unk_00;
}

void fn_1_107BC(s16 arg0)
{
    M438UnkStruct2 *temp_r31;
    s32 var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if ((u32)temp_r31->unk_08 != 0) {
            if (temp_r31->unk_50 != NULL) {
                HuMemDirectFree(temp_r31->unk_50);
            }
            if (temp_r31->unk_54 != NULL) {
                HuMemDirectFree(temp_r31->unk_54);
            }
            if (temp_r31->unk_58 != NULL) {
                HuMemDirectFree(temp_r31->unk_58);
            }
            if (temp_r31->unk_4C != NULL) {
                HuMemDirectFree(temp_r31->unk_4C);
            }
            if (temp_r31->unk_5C != NULL) {
                HuMemDirectFree(temp_r31->unk_5C);
            }

            for (var_r30 = 0; var_r30 < temp_r31->unk_04; var_r30++) {
                fn_1_10F0C(temp_r31->unk_34[var_r30]);
            }
            HuMemDirectFree(temp_r31->unk_3C);
            HuMemDirectFree(temp_r31->unk_34);
            temp_r31->unk_08 = 0;
            temp_r31->unk_00 = 0;
        }
    }
}

void fn_1_108E4(s16 arg0, s16 arg1, u8 arg2)
{
    lbl_1_bss_DE4.unk_36 = arg0;
    lbl_1_bss_DE4.unk_38 = arg1;
    lbl_1_bss_DE4.unk_3A = arg2;
}

#include "game/sprite.h"

s16 fn_1_10910(u32 arg0, s16 arg1, s16 arg2)
{
    f32 var_f31;
    f32 var_f30;
    AnimData *var_r30;
    M438UnkStruct3 *var_r31;
    s32 var_r29;

    var_r31 = &lbl_1_bss_DE4.unk_3C[1];
    for (var_r29 = 1; var_r29 < lbl_1_bss_DE4.unk_32; var_r29++, var_r31++) {
        if ((var_r31->unk_06 != 0) && (var_r31->unk_08 == arg0))
            break;
    }
    if (var_r29 < lbl_1_bss_DE4.unk_32) {
        var_r31->unk_06++;
        return var_r29;
    }

    var_r31 = &lbl_1_bss_DE4.unk_3C[1];
    for (var_r29 = 1; var_r29 < lbl_1_bss_DE4.unk_32; var_r29++, var_r31++) {
        if (var_r31->unk_06 == 0)
            break;
    }
    var_r31->unk_08 = arg0;
    var_r31->unk_06 = 1;
    if (((arg0 & 0xFFFF0000) + 0x10000) == 0) {
        var_r30 = HuSprAnimMake(arg1, arg2, 2);
        var_r30->bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, arg2 * (arg1 * 2), 0x10000000);
        arg1 = arg2 = 0;
    }
    else {
        var_r30 = HuSprAnimRead(HuDataReadNum(arg0, 0x10000000));
    }
    if ((arg1 == 0) || (arg2 == 0)) {
        arg1 = var_r30->bmp->sizeX;
        arg2 = var_r30->bmp->sizeY;
        var_f31 = var_f30 = 1.0f;
    }
    else {
        var_f31 = arg1 / (f32)var_r30->bmp->sizeX;
        var_f30 = arg2 / (f32)var_r30->bmp->sizeY;
    }
    var_r31->unk_00 = var_r30;
    var_r31->unk_4E = arg1;
    var_r31->unk_50 = arg2;
    var_r31->unk_54 = var_f31;
    var_r31->unk_58 = var_f30;
    var_r31->unk_5C = 1.0f / var_r30->bmp->sizeX;
    var_r31->unk_60 = 1.0f / var_r30->bmp->sizeY;
    var_r31->unk_04 = 0;
    var_r31->unk_4C = var_r30->bmp->sizeY / arg2;
    if (var_r31->unk_4C < 1) {
        var_r31->unk_4C = 1;
    }
    var_r31->unk_4D = 0;
    if ((arg1 > var_r30->bmp->sizeX) || (arg2 > var_r30->bmp->sizeY)) {
        var_r31->unk_4D = 1;
    }
    var_r31->unk_48.r = var_r31->unk_48.g = var_r31->unk_48.b = 0xFF;
    var_r31->unk_48.a = 0xFF;
    Identity(var_r31->unk_18);
    var_r31->unk_0C.x = var_r31->unk_0C.y = var_r31->unk_0C.z = 0.0f;
    return var_r29;
}

void fn_1_10CB8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5)
{
    f32 var_f31;
    f32 var_f30;
    M438UnkStruct3 *temp_r31;
    AnimData *temp_r30;

    temp_r31 = &lbl_1_bss_DE4.unk_3C[arg0];
    HuSprAnimKill(temp_r31->unk_00);
    temp_r31->unk_08 |= 0xFFFF0000;
    temp_r30 = HuSprAnimMake(arg2, arg3, arg1);
    temp_r30->bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, arg3 * (temp_r30->bmp->pixSize * arg2), 0x10000000U);
    var_f31 = arg4 / (f32)temp_r30->bmp->sizeX;
    var_f30 = arg5 / (f32)temp_r30->bmp->sizeY;
    temp_r31->unk_00 = temp_r30;
    temp_r31->unk_4E = arg2;
    temp_r31->unk_50 = arg3;
    temp_r31->unk_54 = var_f31;
    temp_r31->unk_58 = var_f30;
    temp_r31->unk_5C = 1.0f / (f32)temp_r30->bmp->sizeX;
    temp_r31->unk_60 = 1.0f / (f32)temp_r30->bmp->sizeY;
    temp_r31->unk_04 = 0;
    temp_r31->unk_4C = temp_r30->bmp->sizeY / arg5;
    temp_r31->unk_4D = 0;
    temp_r31->unk_48.r = temp_r31->unk_48.g = temp_r31->unk_48.b = 0xFF;
    temp_r31->unk_48.a = 0xFF;
}

void fn_1_10F0C(s16 arg0)
{
    M438UnkStruct3 *temp_r31;

    temp_r31 = &lbl_1_bss_DE4.unk_3C[arg0];
    if (temp_r31->unk_08 != 0) {
        if (temp_r31->unk_06 != 0) {
            temp_r31->unk_06 -= 1;
        }
        if (temp_r31->unk_06 == 0) {
            HuSprAnimKill(temp_r31->unk_00);
            temp_r31->unk_08 = 0;
        }
    }
}

u8 fn_1_10F8C(s16 arg0, u8 arg1, u32 arg2, s16 arg3, s16 arg4)
{
    s32 var_r31;

    if (arg0 == 0)
        return 0;

    var_r31 = fn_1_10910(arg2, arg3, arg4);
    if (var_r31 == 0)
        return 0;

    fn_1_110B4(arg0, arg1, var_r31);
    return var_r31;
}

u8 fn_1_11018(s16 arg0, u8 arg1, u32 arg2)
{
    u8 var_r31;

    var_r31 = fn_1_10F8C(arg0, arg1, arg2, 0, 0);

    return var_r31;
}

s32 fn_1_110B4(s16 arg0, u8 arg1, s16 arg2)
{
    M438UnkStruct *var_r29;
    M438UnkStruct2 *temp_r28;
    M438UnkStruct3 *temp_r30;
    M438UnkSubStruct *temp_r31;
    s32 var_r26;

    if (arg2 == 0) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }
    temp_r28 = &lbl_1_bss_DE4.unk_40[arg0];
    temp_r28->unk_08 |= 2;
    if (arg2 == temp_r28->unk_34[arg1]) {
        return 1;
    }
    temp_r28->unk_34[arg1] = arg2;
    temp_r30 = &lbl_1_bss_DE4.unk_3C[arg2];

    var_r29 = temp_r28->unk_3C;
    for (var_r26 = 0; var_r26 < temp_r28->unk_02; var_r26++, var_r29++) {
        if (arg1 == 0) {
            var_r29->unk_44[0].x = -0.5f * temp_r30->unk_4E;
            var_r29->unk_44[0].y = 0.5f * temp_r30->unk_50;
            var_r29->unk_44[1].x = (0.5f * temp_r30->unk_4E);
            var_r29->unk_44[1].y = (0.5f * temp_r30->unk_50);
            var_r29->unk_44[2].x = (0.5f * temp_r30->unk_4E);
            var_r29->unk_44[2].y = (-0.5f * temp_r30->unk_50);
            var_r29->unk_44[3].x = (-0.5f * temp_r30->unk_4E);
            var_r29->unk_44[3].y = (-0.5f * temp_r30->unk_50);
            var_r29->unk_44[0].z = var_r29->unk_44[1].z = var_r29->unk_44[2].z = var_r29->unk_44[3].z = 0.0f;
        }
        temp_r31 = &var_r29->unk_58[arg1];
        temp_r31->unk_24 = 0;
        temp_r31->unk_00 = temp_r31->unk_01 = 0;
        temp_r31->unk_28 = 1.0f;
        temp_r31->unk_2C = 0.0f;
        temp_r31->unk_04 = temp_r31->unk_00 * temp_r30->unk_54;
        temp_r31->unk_08 = temp_r31->unk_00 * temp_r30->unk_58;
        temp_r31->unk_0C = (temp_r31->unk_00 + 1) * temp_r30->unk_54;
        temp_r31->unk_10 = temp_r31->unk_00 * temp_r30->unk_58;
        temp_r31->unk_14 = (temp_r31->unk_00 + 1) * temp_r30->unk_54;
        temp_r31->unk_18 = (temp_r31->unk_00 + 1) * temp_r30->unk_58;
        temp_r31->unk_1C = (temp_r31->unk_00 * temp_r30->unk_54);
        temp_r31->unk_20 = (temp_r31->unk_00 + 1) * temp_r30->unk_58;
        if ((temp_r31->unk_00 + 1) < temp_r30->unk_4C) {
            temp_r31->unk_18 -= temp_r30->unk_60;
            temp_r31->unk_20 -= temp_r30->unk_60;
        }
        DCFlushRangeNoSync(&temp_r31->unk_04, 0x20);
    }
    lbl_1_bss_DE4.unk_36 = arg0;
    lbl_1_bss_DE4.unk_3A = arg1;
    PPCSync();
    return 1;
}

void fn_1_11658(void)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct3 *temp_r30;
    M438UnkStruct3 *temp_r29;
    s32 var_r28;
    s32 var_r27;
    s16 var_r26;

    for (var_r28 = 1; var_r28 < lbl_1_bss_DE4.unk_30; var_r28++) {
        if ((s16)var_r28 != 0) {
            temp_r31 = &lbl_1_bss_DE4.unk_40[(s16)var_r28];
            if (temp_r31->unk_08 != 0) {
                if (temp_r31->unk_50 != NULL) {
                    HuMemDirectFree(temp_r31->unk_50);
                }
                if (temp_r31->unk_54 != NULL) {
                    HuMemDirectFree(temp_r31->unk_54);
                }
                if (temp_r31->unk_58 != NULL) {
                    HuMemDirectFree(temp_r31->unk_58);
                }
                if (temp_r31->unk_4C != NULL) {
                    HuMemDirectFree(temp_r31->unk_4C);
                }
                if (temp_r31->unk_5C != NULL) {
                    HuMemDirectFree(temp_r31->unk_5C);
                }

                for (var_r27 = 0; var_r27 < temp_r31->unk_04; var_r27++) {
                    var_r26 = temp_r31->unk_34[var_r27];
                    temp_r29 = &lbl_1_bss_DE4.unk_3C[var_r26];
                    if (temp_r29->unk_08 != 0) {
                        if (temp_r29->unk_06 != 0) {
                            temp_r29->unk_06 -= 1;
                        }
                        if (temp_r29->unk_06 == 0) {
                            HuSprAnimKill(temp_r29->unk_00);
                            temp_r29->unk_08 = 0;
                        }
                    }
                }
                HuMemDirectFree(temp_r31->unk_3C);
                HuMemDirectFree(temp_r31->unk_34);
                temp_r31->unk_08 = 0;
                temp_r31->unk_00 = 0;
            }
        }
    }

    for (var_r28 = 1; var_r28 < lbl_1_bss_DE4.unk_32; var_r28++) {
        temp_r30 = &lbl_1_bss_DE4.unk_3C[(s16)var_r28];
        if (temp_r30->unk_08 != 0U) {
            if (temp_r30->unk_06 != 0) {
                temp_r30->unk_06 -= 1;
            }
            if (temp_r30->unk_06 == 0) {
                HuSprAnimKill(temp_r30->unk_00);
                temp_r30->unk_08 = 0;
            }
        }
    }
    HuMemDirectFree(lbl_1_bss_DE4.unk_40);
    HuMemDirectFree(lbl_1_bss_DE4.unk_3C);
    Hu3DModelKill(lbl_1_bss_DE4.unk_34);
}

void fn_1_11890(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        temp_r31->unk_0C.x = arg8;
        temp_r31->unk_0C.y = arg9;
        temp_r31->unk_0C.z = argA;
        if (temp_r31->unk_02 == 1) {
            temp_r31->unk_3C->unk_00 = temp_r31->unk_0C;
        }
    }
}

void fn_1_118FC(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *temp_r31;
    M438UnkStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r30->unk_02 > arg1) {
            temp_r31 = &temp_r30->unk_3C[arg1];
            temp_r31->unk_00.x = arg8;
            temp_r31->unk_00.y = arg9;
            temp_r31->unk_00.z = argA;
        }
    }
}

void fn_1_1196C(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = temp_r30->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk_02; var_r29++, var_r31++) {
            var_r31->unk_00.x = arg8;
            var_r31->unk_00.y = arg9;
            var_r31->unk_00.z = argA;
        }
    }
}

void fn_1_119E0(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        temp_r31->unk_0C.x += arg8;
        temp_r31->unk_0C.y += arg9;
        temp_r31->unk_0C.z += argA;
        if (temp_r31->unk_02 == 1) {
            temp_r31->unk_3C->unk_00 = temp_r31->unk_0C;
        }
    }
}

void fn_1_11A64(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *temp_r31;
    M438UnkStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r30->unk_02 > arg1) {
            temp_r31 = &temp_r30->unk_3C[arg1];
            temp_r31->unk_00.x += arg8;
            temp_r31->unk_00.y += arg9;
            temp_r31->unk_00.z += argA;
        }
    }
}

void fn_1_11AEC(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = temp_r30->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk_02; var_r29++, var_r31++) {
            var_r31->unk_00.x += arg8;
            var_r31->unk_00.y += arg9;
            var_r31->unk_00.z += argA;
        }
    }
}

void fn_1_11B78(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *temp_r31;
    M438UnkStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r30->unk_02 > arg1) {
            temp_r31 = &temp_r30->unk_3C[arg1];
            temp_r31->unk_24.x = arg8;
            temp_r31->unk_24.y = arg9;
            temp_r31->unk_24.z = argA;
        }
    }
}

void fn_1_11BE8(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = temp_r30->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk_02; var_r29++, var_r31++) {
            var_r31->unk_24.x = arg8;
            var_r31->unk_24.y = arg9;
            var_r31->unk_24.z = argA;
        }
    }
}

void fn_1_11C5C(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        temp_r31->unk_70.x = arg8;
        temp_r31->unk_70.y = arg9;
        temp_r31->unk_70.z = argA;
        if (temp_r31->unk_02 == 1) {
            temp_r31->unk_3C->unk_6C = temp_r31->unk_70;
        }
    }
}

void fn_1_11CC8(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *temp_r31;
    M438UnkStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r30->unk_02 > arg1) {
            temp_r31 = &temp_r30->unk_3C[arg1];
            temp_r31->unk_6C.x = arg8;
            temp_r31->unk_6C.y = arg9;
            temp_r31->unk_6C.z = argA;
        }
    }
}

void fn_1_11D38(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = temp_r30->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk_02; var_r29++, var_r31++) {
            var_r31->unk_6C.x = arg8;
            var_r31->unk_6C.y = arg9;
            var_r31->unk_6C.z = argA;
        }
    }
}

void fn_1_11DAC(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        temp_r31->unk_18.x = arg8;
        temp_r31->unk_18.y = arg9;
        temp_r31->unk_18.z = argA;
        if (temp_r31->unk_02 == 1) {
            temp_r31->unk_3C->unk_0C = temp_r31->unk_18;
        }
    }
}

void fn_1_11E18(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *temp_r31;
    M438UnkStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r30->unk_02 > arg1) {
            temp_r31 = &temp_r30->unk_3C[arg1];
            temp_r31->unk_0C.x = arg8;
            temp_r31->unk_0C.y = arg9;
            temp_r31->unk_0C.z = argA;
        }
    }
}

void fn_1_11E88(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = temp_r30->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk_02; var_r29++, var_r31++) {
            var_r31->unk_0C.x = arg8;
            var_r31->unk_0C.y = arg9;
            var_r31->unk_0C.z = argA;
        }
    }
}

void fn_1_11EFC(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        temp_r31->unk_24.x = arg8;
        temp_r31->unk_24.y = arg9;
        temp_r31->unk_24.z = argA;
        if (temp_r31->unk_02 == 1) {
            temp_r31->unk_3C->unk_18 = temp_r31->unk_24;
        }
    }
}

void fn_1_11F68(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *temp_r31;
    M438UnkStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r30->unk_02 > arg1) {
            temp_r31 = &temp_r30->unk_3C[arg1];
            temp_r31->unk_18.x = arg8;
            temp_r31->unk_18.y = arg9;
            temp_r31->unk_18.z = argA;
        }
    }
}

void fn_1_11FD8(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = temp_r30->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk_02; var_r29++, var_r31++) {
            var_r31->unk_18.x = arg8;
            var_r31->unk_18.y = arg9;
            var_r31->unk_18.z = argA;
        }
    }
}

void fn_1_1204C(s16 arg0, s32 arg1)
{
    M438UnkStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        temp_r31->unk_08 |= arg1;
    }
}

void fn_1_12090(s16 arg0, s16 arg1, s32 arg2)
{
    M438UnkStruct *temp_r30;
    M438UnkStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            temp_r30 = &temp_r31->unk_3C[arg1];
            temp_r30->unk_38 |= arg2;
        }
    }
}

void fn_1_12100(s16 arg0, s32 arg1)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r30 = temp_r31->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r31->unk_02; var_r29++, var_r30++) {
            var_r30->unk_38 |= arg1;
        }
    }
}

void fn_1_12174(s16 arg0, u32 arg1)
{
    M438UnkStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        temp_r31->unk_08 &= ~arg1;
    }
}

void fn_1_121B8(s16 arg0, s16 arg1, u32 arg2)
{
    M438UnkStruct *temp_r30;
    M438UnkStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if ((s16)temp_r31->unk_02 > arg1) {
            temp_r30 = &temp_r31->unk_3C[arg1];
            temp_r30->unk_38 &= ~arg2;
        }
    }
}

void fn_1_12228(s16 arg0, u32 arg1)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r30 = temp_r31->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r31->unk_02; var_r29++, var_r30++) {
            var_r30->unk_38 &= ~arg1;
        }
    }
}

s32 fn_1_1229C(s16 arg0, s32 arg1)
{
    M438UnkStruct2 *var_r31;

    if (arg0 == 0) {
        return 0;
    }

    var_r31 = &lbl_1_bss_DE4.unk_40[arg0];
    if ((var_r31->unk_08 & arg1) != 0) {
        return 1;
    }
    return 0;
}

s16 fn_1_122F8(s16 arg0, s16 arg1, s32 arg2)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            if ((var_r30->unk_38 & arg2) != 0) {
                return 1;
            }
            arg0 = 0;
        }
    }
    return arg0;
}

void fn_1_12378(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5)
{
    M438UnkStruct *temp_r31;
    M438UnkStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r30->unk_02 > arg1) {
            temp_r31 = &temp_r30->unk_3C[arg1];
            temp_r31->unk_54.r = arg2;
            temp_r31->unk_54.g = arg3;
            temp_r31->unk_54.b = arg4;
            temp_r31->unk_54.a = arg5;
        }
    }
}

void fn_1_123EC(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = temp_r30->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk_02; var_r29++, var_r31++) {
            var_r31->unk_54.r = arg1;
            var_r31->unk_54.g = arg2;
            var_r31->unk_54.b = arg3;
            var_r31->unk_54.a = arg4;
        }
    }
}

void fn_1_12464(s16 arg0, s16 arg1, u8 arg2)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            var_r30->unk_30 = arg2;
        }
    }
}

void fn_1_124CC(s16 arg0, u8 arg1)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r30 = temp_r31->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r31->unk_02; var_r29++, var_r30++) {
            var_r30->unk_30 = arg1;
        }
    }
}

void fn_1_12538(s16 arg0, s16 arg1, u8 arg2)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            var_r30->unk_31 = arg2;
        }
    }
}

void fn_1_125A0(s16 arg0, u8 arg1)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r30 = temp_r31->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r31->unk_02; var_r29++, var_r30++) {
            var_r30->unk_31 = arg1;
        }
    }
}

void fn_1_1260C(s16 arg0, s16 arg1, u8 arg2)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            var_r30->unk_33 = arg2;
        }
    }
}

void fn_1_12674(s16 arg0, u8 arg1)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r30 = temp_r31->unk_3C;
        for (var_r29 = 0; var_r29 < temp_r31->unk_02; var_r29++, var_r30++) {
            var_r30->unk_33 = arg1;
        }
    }
}

void fn_1_126E0(s16 arg0, s16 arg1, u8 arg2)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            var_r30->unk_58[0].unk_24 = arg2;
        }
    }
}

void fn_1_1274C(s16 arg0, s16 arg1, u8 arg2, u8 arg3)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            var_r30->unk_58[arg2].unk_24 = arg3;
        }
    }
}

void fn_1_127C4(s16 arg0, u8 arg1)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r29;
    s32 var_r28;
    s32 var_r30;

    if (arg0 != 0) {
        temp_r29 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = (M438UnkStruct *)&temp_r29->unk_3C; //! bug
        for (var_r28 = 0; var_r28 < temp_r29->unk_02; var_r28++, var_r31++) {
            for (var_r30 = 0; var_r30 < var_r31->unk_34; var_r30++) {
                var_r31->unk_58[var_r30].unk_24 = arg1;
            }
        }
    }
}

void fn_1_1285C(s16 arg0, s16 arg1, f32 arg8)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            var_r30->unk_58[0].unk_28 = arg8;
        }
    }
}

void fn_1_128C8(s16 arg0, s16 arg1, u8 arg2, f32 arg8)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            var_r30->unk_58[arg2].unk_28 = arg8;
        }
    }
}

void fn_1_12940(s16 arg0, f32 arg8)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r30;
    s32 var_r28;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = temp_r30->unk_3C;

        for (var_r28 = 0; var_r28 < temp_r30->unk_02; var_r28++, var_r31++) {
            for (var_r29 = 0; var_r29 < var_r31->unk_34; var_r29++) {
                var_r31->unk_58[var_r29].unk_28 = arg8;
            }
        }
    }
}

void fn_1_129D8(s16 arg0, s16 arg1, u8 arg2)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            var_r30->unk_58[0].unk_00 = arg2;
        }
    }
}

void fn_1_12A48(s16 arg0, s16 arg1, u8 arg2, u8 arg3)
{
    M438UnkStruct2 *temp_r31;
    M438UnkStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if (temp_r31->unk_02 > arg1) {
            var_r30 = &temp_r31->unk_3C[arg1];
            var_r30->unk_58[arg2].unk_00 = arg3;
        }
    }
}

void fn_1_12AC0(s16 arg0, u8 arg1)
{
    M438UnkStruct *var_r31;
    M438UnkStruct2 *temp_r30;
    s32 var_r28;
    s32 var_r29;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_DE4.unk_40[arg0];
        var_r31 = temp_r30->unk_3C;

        for (var_r28 = 0; var_r28 < temp_r30->unk_02; var_r28++, var_r31++) {
            for (var_r29 = 0; var_r29 < var_r31->unk_34; var_r29++) {
                var_r31->unk_58[var_r29].unk_00 = arg1;
            }
        }
    }
}

void fn_1_12B58(s16 arg0, u8 arg1)
{
    M438UnkStruct3 *var_r31;

    if (arg0 != 0) {
        var_r31 = &lbl_1_bss_DE4.unk_3C[arg0];
        var_r31->unk_04 = arg1;
    }
}
