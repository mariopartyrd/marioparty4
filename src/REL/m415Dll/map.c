#define HUSPR_USE_OLD_DEFS
#include "REL/m415Dll.h"

#include "game/hsfdraw.h"
#include "game/sprite.h"

void fn_1_8780(s16 arg0, s16 arg1)
{
    s32 var_r31;
    unkSubStruct2 *var_r29;
    unkSubStruct3 *var_r30;

    lbl_1_bss_36C.unk34 = Hu3DHookFuncCreate(fn_1_95C0);
    Hu3DModelLayerSet(lbl_1_bss_36C.unk34, 6);
    lbl_1_bss_36C.unk30 = arg0;
    lbl_1_bss_36C.unk40 = var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(unkSubStruct2), MEMORY_DEFAULT_NUM);
    lbl_1_bss_36C.unk32 = arg1;
    lbl_1_bss_36C.unk3C = var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(unkSubStruct3), MEMORY_DEFAULT_NUM);

    for (var_r31 = 0; var_r31 < arg0; var_r31++, var_r29++) {
        var_r29->unk8 = 0;
    }

    for (var_r31 = 0; var_r31 < arg1; var_r31++, var_r30++) {
        var_r30->unk6 = 0;
        var_r30->unk8 = 0;
    }
    lbl_1_bss_36C.unk36 = lbl_1_bss_36C.unk38 = lbl_1_bss_36C.unk3A = 0;
}

void fn_1_88B8(unkSubStruct2 *arg0)
{
    ModelData sp120;
    Mtx spF0;
    Mtx spC0;
    Mtx sp90;
    Mtx sp60;
    Mtx sp30;
    GXColor sp2C;
    s16 sp8;
    s32 var_r25;
    s32 var_r27;
    s16 temp_r23;
    s16 var_r28;
    s16 var_r29;
    s32 var_r24;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;
    unkSubStruct3 *temp_r26;
    unkSubStruct *var_r31;

    mtxRot(sp60, arg0->unk18.x, arg0->unk18.y, arg0->unk18.z);
    MTXScale(sp90, arg0->unk24.x, arg0->unk24.y, arg0->unk24.z);
    MTXConcat(sp60, sp90, sp90);
    mtxTransCat(sp90, arg0->unkC.x, arg0->unkC.y, arg0->unkC.z);
    MTXConcat(Hu3DCameraMtx, sp90, spC0);
    var_r29 = 0;
    var_r28 = 0;
    sp8 = 0;

    for (var_r27 = GX_TEXMAP0; var_r27 < arg0->unk4; var_r27++) {
        if (arg0->unk34[var_r27] != 0) {
            temp_r26 = &lbl_1_bss_36C.unk3C[arg0->unk34[var_r27]];
            MTXCopy(temp_r26->unk18, sp30);
            mtxTransCat(sp30, temp_r26->unkC.x, temp_r26->unkC.y, temp_r26->unkC.z);
            switch (temp_r26->unk4) {
                case 0:
                    GXLoadTexMtxImm(sp30, texMtxTbl[var_r28], GX_MTX2x4);
                    var_r22 = texMtxTbl[var_r28];
                    GXSetTexCoordGen2(var_r28, GX_TG_MTX2x4, var_r27 + 4, var_r22, 0, 0x7D);
                    GXSetTevOrder(var_r29, var_r28, var_r27, GX_COLOR0A0);
                    if (var_r27 == GX_TEXMAP0) {
                        if ((temp_r26->unk0->bmp->dataFmt == 7) || (temp_r26->unk0->bmp->dataFmt == 8)) {
                            GXSetTevColor(GX_TEVREG2, temp_r26->unk48);
                            GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_C2, GX_CC_RASC, GX_CC_ZERO);
                        }
                        else {
                            GXSetTevColorIn(var_r29, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                        }
                        GXSetTevAlphaIn(var_r29, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                    }
                    else {
                        sp2C.a = temp_r26->unk48.a;
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
                    mtxRot(sp60, arg0->unk18.x, arg0->unk18.y, arg0->unk18.z);
                    MTXScale(sp90, arg0->unk24.x, arg0->unk24.y, arg0->unk24.z);
                    MTXConcat(sp60, sp90, sp90);
                    mtxTransCat(sp90, arg0->unkC.x, arg0->unkC.y, arg0->unkC.z);
                    MTXConcat(Hu3DCameraMtx, sp90, sp30);
                    MTXInverse(Hu3DCameraMtx, sp60);
                    MTXConcat(sp60, sp30, sp60);
                    MTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, sp90);
                    MTXConcat(sp90, sp60, sp30);
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
            if (temp_r26->unk4D != 0) {
                HuSprTexLoad(temp_r26->unk0, 0, var_r27, 1, 1, 1);
            }
            else {
                HuSprTexLoad(temp_r26->unk0, 0, var_r27, 0, 0, 1);
            }
        }
    }
    GXSetNumTevStages((s16)var_r29);
    GXSetNumTexGens((s16)var_r28);
    var_r31 = arg0->unk3C;

    for (var_r24 = 0; var_r24 < arg0->unk2; var_r24++, var_r31++) {
        if ((var_r31->unk34 != 0) && ((var_r31->unk34 & 4) == 0)) {
            switch (var_r31->unk30) {
                case 0:
                    mtxRot(sp60, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
                    if (var_r31->unk31 == 2) {
                        MTXConcat(lbl_1_bss_36C.unk0, sp60, sp60);
                    }
                    else if (var_r31->unk31 == 1) {
                        MTXRotDeg(sp90, 0x59, CRot.y);
                        MTXConcat(sp90, sp60, sp60);
                    }
                    MTXScale(sp90, var_r31->unk18.x, var_r31->unk18.y, var_r31->unk18.z);
                    MTXConcat(sp60, sp90, sp90);
                    mtxTransCat(sp90, var_r31->unk0.x, var_r31->unk0.y, var_r31->unk0.z);
                    MTXConcat(Hu3DCameraMtx, sp90, spF0);
                    break;
                case 1:
                    mtxRot(sp60, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
                    if (var_r31->unk31 == 2) {
                        if (HmfInverseMtxF3X3(spC0, sp90) == 0) {
                            MTXIdentity(sp90);
                        }
                        MTXConcat(sp90, sp60, sp60);
                    }
                    else if (var_r31->unk31 == 1) {
                        MTXRotDeg(sp90, 0x59, CRot.y);
                        MTXConcat(sp90, sp60, sp60);
                    }
                    MTXScale(sp90, var_r31->unk18.x, var_r31->unk18.y, var_r31->unk18.z);
                    MTXConcat(sp60, sp90, sp90);
                    mtxTransCat(sp90, var_r31->unk0.x, var_r31->unk0.y, var_r31->unk0.z);
                    MTXConcat(spC0, sp90, spF0);
                    break;
            }
            GXLoadPosMtxImm(spF0, 0);
            MTXInverse(spF0, sp90);
            MTXTranspose(sp90, sp60);
            GXLoadNrmMtxImm(sp60, 0);
            GXSetChanAmbColor(GX_COLOR0A0, var_r31->unk4C);
            GXSetChanMatColor(GX_COLOR0A0, var_r31->unk50);
            GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
            GXSetZCompLoc(0);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            if ((var_r31->unk34 & 0x10) != 0) {
                GXSetZMode(0, GX_LEQUAL, 1);
            }
            else {
                GXSetZMode(1, GX_LEQUAL, 0);
            }
            sp120.attr = 0;
            temp_r23 = Hu3DLightSet(&sp120, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, 0.0f);
            GXSetNumChans(1);
            if ((var_r31->unk34 & 8) != 0) {
                var_r25 = GX_SRC_VTX;
            }
            else {
                var_r25 = GX_SRC_REG;
            }
            switch (var_r31->unk32) {
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
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            GXSetArray(GX_VA_POS, var_r31->unk40, 12);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetArray(GX_VA_CLR0, var_r31->unk44, 4);

            for (var_r27 = 0; var_r27 < var_r31->unk33; var_r27++) {
                GXSetVtxDesc(var_r27 + GX_VA_TEX0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, var_r27 + GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
                GXSetArray(var_r27 + GX_VA_TEX0, var_r31->unk54[var_r27].unk4, 8);
            }
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
            GXSetArray(GX_VA_NRM, var_r31->unk48, 12);
            GXCallDisplayList(var_r31->unk3C, var_r31->unk38);
        }
    }
}

void fn_1_95C0(ModelData *arg0, Mtx arg1)
{
    Mtx sp38;
    Mtx sp8;
    s32 var_r30;
    unkSubStruct2 *var_r31;

    var_r31 = lbl_1_bss_36C.unk40;
    GXLoadPosMtxImm(arg1, 0);
    MTXInverse(arg1, sp38);
    MTXTranspose(sp38, sp8);
    GXLoadNrmMtxImm(sp8, 0);
    HmfInverseMtxF3X3(Hu3DCameraMtx, lbl_1_bss_36C.unk0);

    for (var_r30 = 0; var_r30 < lbl_1_bss_36C.unk30; var_r30++, var_r31++) {
        if ((var_r31->unk8 != 0) && ((var_r31->unk8 & 2) != 0) && ((var_r31->unk8 & 4) == 0)) {
            if ((u8)omPauseChk() == 0) {
                if (var_r31->unk30) {
                    var_r31->unk30(var_r31);
                }
                if (var_r31->unk8 == 0)
                    continue;
                fn_1_9DC8(var_r31);
                if (var_r31->unk8 == 0)
                    continue;
            }
            fn_1_88B8(var_r31);
        }
    }
}

unkSubStruct2 *fn_1_96EC(s16 arg0)
{
    return &lbl_1_bss_36C.unk40[arg0];
}

unkSubStruct *fn_1_9708(s16 arg0, s16 arg1)
{
    return &lbl_1_bss_36C.unk40[arg0].unk3C[arg1];
}

AnimData **fn_1_9734(s16 arg0)
{
    return &lbl_1_bss_36C.unk3C[arg0].unk0;
}

void fn_1_9750(unkStruct6 **arg0, s16 arg1, f32 arg8, f32 arg9)
{
    s32 var_r30;
    unkStruct6 *var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(unkStruct6), MEMORY_DEFAULT_NUM);

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

void fn_1_98D4(Vec **arg0, s16 arg1, Vec *arg2)
{
    s32 var_r29;
    s32 var_r28;
    Vec *var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(Vec[4]), MEMORY_DEFAULT_NUM);

    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
            var_r31->z = arg2->z;
        }
    }
}

void fn_1_9974(GXColor **arg0, s16 arg1, GXColor *arg2)
{
    s32 var_r29;
    s32 var_r28;
    GXColor *var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(GXColor[4]), MEMORY_DEFAULT_NUM);

    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->r = arg2->r;
            var_r31->g = arg2->g;
            var_r31->b = arg2->b;
            var_r31->a = arg2->a;
        }
    }
}

void fn_1_9A1C(Vec **arg0, s16 arg1, Vec *arg2)
{
    s32 var_r29;
    Vec *var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(Vec), MEMORY_DEFAULT_NUM);

    for (var_r29 = 0; var_r29 < arg1; var_r31++, arg2++, var_r29++) {
        var_r31->x = arg2->x;
        var_r31->y = arg2->y;
        var_r31->z = arg2->z;
    }
}

void fn_1_9AA8(HsfVector2f **arg0, s16 arg1, HsfVector2f *arg2)
{
    s32 var_r28;
    s32 var_r29;
    HsfVector2f *var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(HsfVector2f[4]), MEMORY_DEFAULT_NUM);

    for (var_r28 = 0; var_r28 < arg1; var_r28++) {
        for (var_r29 = 0; var_r29 < 4; var_r31++, arg2++, var_r29++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
        }
    }
}

void fn_1_9B40(unkSubStruct *arg0)
{
    void *sp8;
    s32 var_r29;
    s32 var_r31;
    void *temp_r28;

    Vec sp1C[4] = { { -50.0f, 50.0f, 0.0f }, { 50.0f, 50.0f, 0.0f }, { 50.0f, -50.0f, 0.0f }, { -50.0f, -50.0f, 0.0f } };
    GXColor spC[4] = { { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF } };

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        arg0->unk40[var_r31] = sp1C[var_r31];
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        arg0->unk44[var_r31] = spC[var_r31];
    }
    arg0->unk48->x = 0.0f;
    arg0->unk48->y = 0.0f;
    arg0->unk48->z = 1.0;
    temp_r28 = arg0->unk3C;
    sp8 = temp_r28;
    GXBeginDisplayList(temp_r28, 0x100U);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GXPosition1x16(var_r31);
        GXNormal1x16(0);
        GXColor1x16(var_r31);
        for (var_r29 = 0; var_r29 < arg0->unk33; var_r29++) {
            GXTexCoord1x16(var_r31);
        }
    }
    arg0->unk38 = GXEndDisplayList();
}

void fn_1_9DC8(unkSubStruct2 *arg0)
{
    s32 temp_r0;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    unkSubStruct *var_r28;
    unkSubStruct3 *temp_r30;
    unkSubStruct4 *var_r31;

    var_r27 = 0;
    var_r28 = arg0->unk3C;

    for (var_r25 = 0; var_r25 < arg0->unk2; var_r25++, var_r28++) {
        if ((var_r28->unk34 & 4) != 0) {
            var_r27++;
        }
        else {
            var_r31 = var_r28->unk54;

            for (var_r26 = 0; var_r26 < var_r28->unk33; var_r26++, var_r31++) {
                temp_r30 = &lbl_1_bss_36C.unk3C[arg0->unk34[var_r26]];
                var_r31->unk24 &= ~4;
                switch (var_r31->unk24 & 0xF) {
                    case 1:
                        var_r31->unk2C += var_r31->unk28;
                        if (var_r31->unk2C >= 1.0f) {
                            var_r31->unk0++;
                            var_r31->unk2C--;
                        }
                        break;
                    case 2:
                        var_r31->unk2C += var_r31->unk28;
                        if (var_r31->unk2C >= 1.0f) {
                            var_r31->unk0--;
                            var_r31->unk2C--;
                        }
                        break;
                }
                if (var_r31->unk0 >= temp_r30->unk4C) {
                    if ((var_r31->unk24 & 0x10) != 0) {
                        var_r31->unk24 |= 8;
                        var_r31->unk0--;
                    }
                    else if ((var_r31->unk24 & 0x40) != 0) {
                        var_r31->unk24 = (var_r31->unk24 & 0xF0) | 2;
                        var_r31->unk0 -= 2;
                    }
                    else if ((var_r31->unk24 & 0x20) != 0) {
                        var_r31->unk0 = 0;
                    }
                    var_r31->unk24 |= 4;
                }
                else if (var_r31->unk0 < 0) {
                    if ((var_r31->unk24 & 0x10) != 0) {
                        var_r31->unk24 |= 8;
                        var_r31->unk0 = 0;
                    }
                    else if ((var_r31->unk24 & 0x20) != 0) {
                        if ((var_r31->unk24 & 0x40) != 0) {
                            var_r31->unk24 = (var_r31->unk24 & 0xF0) | 1;
                            var_r31->unk0 = 1;
                        }
                        else {
                            var_r31->unk0 = temp_r30->unk4C - 1;
                        }
                    }
                    else if ((var_r31->unk24 & 0x40) != 0) {
                        var_r31->unk24 |= 8;
                        var_r31->unk0 = 0;
                    }
                    var_r31->unk24 |= 4;
                }
                else {
                    var_r31->unk24 &= ~8;
                }
                if (var_r31->unk0 != var_r31->unk1) {
                    var_r31->unk4[0].y = var_r31->unk0 * temp_r30->unk58;
                    var_r31->unk4[1].y = var_r31->unk0 * temp_r30->unk58;
                    var_r31->unk4[2].y = ((var_r31->unk0 + 1) * temp_r30->unk58);
                    var_r31->unk4[3].y = ((var_r31->unk0 + 1) * temp_r30->unk58);
                    if ((var_r31->unk0 + 1) < temp_r30->unk4C) {
                        var_r31->unk4[2].y -= temp_r30->unk60;
                        var_r31->unk4[3].y -= temp_r30->unk60;
                    }
                    var_r31->unk1 = var_r31->unk0;
                }
                if ((var_r31->unk24 & 8) != 0) {
                    if ((var_r28->unk34 & 0x40000000) != 0) {
                        var_r28->unk34 |= 4;
                        if ((var_r31->unk24 & 0x40) == 0) {
                            if (var_r31->unk0 <= 0) {
                                var_r31->unk0 = temp_r30->unk4C;
                            }
                            else {
                                var_r31->unk0 = 0;
                            }
                        }
                    }
                    else if ((var_r28->unk34 & 0x80000000) != 0) {
                        fn_1_A800(arg0->unk0);
                    }
                    var_r27++;
                }
            }
        }
    }
    if (var_r27 >= arg0->unk2) {
        if ((arg0->unk8 & 0x40000000) != 0) {
            arg0->unk8 |= 4;
            return;
        }
        if ((arg0->unk8 & 0x80000000) != 0) {
            fn_1_A800(arg0->unk0);
        }
    }
}

s16 fn_1_A2D0(u8 arg0, u8 arg1)
{
    s32 var_r29;
    s32 var_r28;
    unkSubStruct *var_r30;
    unkSubStruct2 *var_r31;
    void *temp_r25;

    var_r31 = lbl_1_bss_36C.unk40 + 1;

    for (var_r29 = 1; var_r29 < lbl_1_bss_36C.unk30; var_r29++, var_r31++) {
        if (var_r31->unk8 == 0) {
            break;
        }
    }
    if (var_r29 == lbl_1_bss_36C.unk30) {
        return 0;
    }
    var_r31->unk0 = var_r29;
    var_r31->unk8 = 1;
    var_r31->unk30 = NULL;
    var_r31->unk2 = arg0;
    var_r31->unk4 = arg1;
    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(unkSubStruct), MEMORY_DEFAULT_NUM);
    var_r31->unk3C = var_r30;
    var_r31->unk34 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * 2, MEMORY_DEFAULT_NUM);
    var_r31->unk48 = 0;
    var_r31->unk4C = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(unkType), MEMORY_DEFAULT_NUM);
    var_r31->unk50 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(Vec[4]), MEMORY_DEFAULT_NUM);
    var_r31->unk54 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(unkType2), MEMORY_DEFAULT_NUM);
    var_r31->unk58 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    var_r31->unk5C = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * (arg0 * sizeof(unkSubStruct4)), MEMORY_DEFAULT_NUM);
    DCFlushRangeNoSync(var_r31->unk4C, arg0 << 8);
    var_r31->unkC.x = var_r31->unkC.y = var_r31->unkC.z = 0.0f;
    var_r31->unk18.x = var_r31->unk18.y = var_r31->unk18.z = 0.0f;
    var_r31->unk24.x = var_r31->unk24.y = var_r31->unk24.z = 1.0f;
    var_r31->unk70.x = var_r31->unk70.y = var_r31->unk70.z = 0.0f;
    var_r31->unk64.x = var_r31->unk64.y = var_r31->unk64.z = 0.0f;
    var_r31->unk60 = 0;

    for (var_r29 = 0; var_r29 < 0x20; var_r29++) {
        var_r31->unk7C[var_r29] = 0;
    }
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        var_r31->unk34[var_r29] = 0;
    }
    for (var_r29 = 0; var_r29 < arg0; var_r29++, var_r30++) {
        var_r30->unk34 = 1;
        var_r30->unk33 = arg1;
        var_r30->unk30 = 0;
        var_r30->unk31 = 2;
        var_r30->unk32 = 0;

        var_r30->unk4C.r = var_r30->unk4C.g = var_r30->unk4C.b = 0;
        var_r30->unk4C.a = 0xFF;
        var_r30->unk50.r = var_r30->unk50.g = var_r30->unk50.b = 0xFF;
        var_r30->unk50.a = 0xFF;
        var_r30->unk54 = &var_r31->unk5C[var_r29 * arg1];
        for (var_r28 = 0; var_r28 < arg1; var_r28++) {
            var_r30->unk54[var_r28].unk0 = var_r30->unk54[var_r28].unk1 = 0;
            var_r30->unk54[var_r28].unk28 = 1.0f;
            var_r30->unk54[var_r28].unk2C = 0.0f;
        }

        var_r30->unk0.x = var_r30->unk0.y = var_r30->unk0.z = 0.0f;
        var_r30->unkC.x = var_r30->unkC.y = var_r30->unkC.z = 0.0f;
        var_r30->unk18.x = var_r30->unk18.y = var_r30->unk18.z = 1.0f;
        var_r30->unk68.x = var_r30->unk68.y = var_r30->unk68.z = 0.0f;
        var_r30->unk5C.x = var_r30->unk5C.y = var_r30->unk5C.z = 0.0f;
        var_r30->unk58 = 0;

        for (var_r28 = 0; var_r28 < 0x10; var_r28++) {
            var_r30->unk74[var_r28] = 0;
        }
        var_r30->unk40 = &var_r31->unk50[var_r29 * 4];
        var_r30->unk44 = &var_r31->unk54[var_r29 * 4];
        var_r30->unk48 = &var_r31->unk58[var_r29];
        var_r30->unk3C = var_r31->unk4C + var_r31->unk48;
        fn_1_9B40(var_r30);
        var_r31->unk48 += var_r30->unk38;
    }
    temp_r25 = var_r31->unk4C;
    var_r31->unk4C = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk48, MEMORY_DEFAULT_NUM);
    memcpy(var_r31->unk4C, temp_r25, var_r31->unk48);
    HuMemDirectFree(temp_r25);
    DCFlushRangeNoSync(var_r31->unk50, arg0 * 0x30);
    DCFlushRangeNoSync(var_r31->unk54, arg0 * 0x10);
    DCFlushRangeNoSync(var_r31->unk58, arg0 * 0xC);
    DCFlushRangeNoSync(var_r31->unk4C, var_r31->unk48);
    var_r30 = var_r31->unk3C;
    var_r31->unk48 = 0;

    for (var_r29 = 0; var_r29 < arg0; var_r29++, var_r30++) {
        var_r30->unk3C = var_r31->unk4C + var_r31->unk48;
        var_r31->unk48 += var_r30->unk38;
    }
    lbl_1_bss_36C.unk36 = var_r31->unk0;
    lbl_1_bss_36C.unk38 = 0;
    lbl_1_bss_36C.unk3A = 0;
    return var_r31->unk0;
}

void fn_1_A800(s16 arg0)
{
    s32 var_r30;
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk8 != 0) {
            if (temp_r31->unk50 != NULL) {
                HuMemDirectFree(temp_r31->unk50);
            }
            if (temp_r31->unk54 != NULL) {
                HuMemDirectFree(temp_r31->unk54);
            }
            if (temp_r31->unk58 != NULL) {
                HuMemDirectFree(temp_r31->unk58);
            }
            if (temp_r31->unk4C != NULL) {
                HuMemDirectFree(temp_r31->unk4C);
            }
            if (temp_r31->unk5C != NULL) {
                HuMemDirectFree(temp_r31->unk5C);
            }

            for (var_r30 = 0; var_r30 < temp_r31->unk4; var_r30++) {
                fn_1_AF48(temp_r31->unk34[var_r30]);
            }
            HuMemDirectFree(temp_r31->unk3C);
            HuMemDirectFree(temp_r31->unk34);
            temp_r31->unk8 = 0;
        }
    }
}

void fn_1_A920(s16 arg0, s16 arg1, u8 arg2)
{
    lbl_1_bss_36C.unk36 = arg0;
    lbl_1_bss_36C.unk38 = arg1;
    lbl_1_bss_36C.unk3A = arg2;
}

s16 fn_1_A94C(u32 arg0, s16 arg1, s16 arg2)
{
    AnimData *var_r30;
    f32 var_f31;
    f32 var_f30;
    s32 var_r29;
    unkSubStruct3 *var_r31;

    var_r31 = lbl_1_bss_36C.unk3C + 1;
    for (var_r29 = 1; var_r29 < lbl_1_bss_36C.unk32; var_r29++, var_r31++) {
        if ((var_r31->unk6 != 0) && (var_r31->unk8 == arg0)) {
            break;
        }
    }
    if (var_r29 < lbl_1_bss_36C.unk32) {
        var_r31->unk6++;
        return var_r29;
    }
    var_r31 = lbl_1_bss_36C.unk3C + 1;
    for (var_r29 = 1; var_r29 < lbl_1_bss_36C.unk32; var_r29++, var_r31++) {
        if (var_r31->unk6 == 0) {
            break;
        }
    }
    var_r31->unk8 = arg0;
    var_r31->unk6 = 1;
    if (((arg0 & 0xFFFF0000) + 0x10000) == 0U) {
        var_r30 = HuSprAnimMake(arg1, arg2, 2);
        var_r30->bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, arg2 * (arg1 * 2), MEMORY_DEFAULT_NUM);
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
    var_r31->unk0 = var_r30;
    var_r31->unk4E = arg1;
    var_r31->unk50 = arg2;
    var_r31->unk54 = var_f31;
    var_r31->unk58 = var_f30;
    var_r31->unk5C = 1.0f / var_r30->bmp->sizeX;
    var_r31->unk60 = 1.0f / var_r30->bmp->sizeY;
    var_r31->unk4 = 0;
    var_r31->unk4C = (var_r30->bmp->sizeY / arg2);
    if (var_r31->unk4C < 1) {
        var_r31->unk4C = 1;
    }
    var_r31->unk4D = 0;
    if ((arg1 > var_r30->bmp->sizeX) || (arg2 > var_r30->bmp->sizeY)) {
        var_r31->unk4D = 1;
    }
    var_r31->unk48.r = var_r31->unk48.g = var_r31->unk48.b = 0xFF;
    var_r31->unk48.a = 0xFF;
    MTXIdentity(var_r31->unk18);
    var_r31->unkC.x = var_r31->unkC.y = var_r31->unkC.z = 0.0f;
    return var_r29;
}

void fn_1_ACF4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5)
{
    f32 var_f31;
    f32 var_f30;
    AnimData *var_r30;
    unkSubStruct3 *var_r31;

    var_r31 = &lbl_1_bss_36C.unk3C[arg0];
    HuSprAnimKill(var_r31->unk0);
    var_r31->unk8 |= 0xFFFF0000;
    var_r30 = HuSprAnimMake(arg2, arg3, arg1);
    var_r30->bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, arg3 * (var_r30->bmp->pixSize * arg2), 0x10000000U);
    var_f31 = arg4 / (f32)var_r30->bmp->sizeX;
    var_f30 = arg5 / (f32)var_r30->bmp->sizeY;
    var_r31->unk0 = var_r30;
    var_r31->unk4E = arg2;
    var_r31->unk50 = arg3;
    var_r31->unk54 = var_f31;
    var_r31->unk58 = var_f30;
    var_r31->unk5C = 1.0f / var_r30->bmp->sizeX;
    var_r31->unk60 = 1.0f / var_r30->bmp->sizeY;
    var_r31->unk4 = 0;
    var_r31->unk4C = var_r30->bmp->sizeY / arg5;
    var_r31->unk4D = 0;
    var_r31->unk48.r = var_r31->unk48.g = var_r31->unk48.b = 0xFF;
    var_r31->unk48.a = 0xFF;
}

void fn_1_AF48(s16 arg0)
{
    unkSubStruct3 *temp_r31;

    temp_r31 = &lbl_1_bss_36C.unk3C[arg0];
    if (temp_r31->unk8 != 0) {
        if (temp_r31->unk6 != 0) {
            temp_r31->unk6 -= 1;
        }
        if (temp_r31->unk6 == 0) {
            HuSprAnimKill(temp_r31->unk0);
            temp_r31->unk8 = 0;
        }
    }
}

u8 fn_1_AFC8(s16 arg0, u8 arg1, s32 arg2, s16 arg3, s16 arg4)
{
    s32 temp_r3;

    temp_r3 = fn_1_A94C(arg2, arg3, arg4);
    if (temp_r3 == 0) {
        return 0;
    }
    fn_1_B0B8(arg0, arg1, temp_r3);
    return temp_r3;
}

u8 fn_1_B038(s16 arg0, u8 arg1, s32 arg2)
{
    u8 var_r31;
    s32 var_r30;
    u8 var_r29;

    if ((var_r30 = fn_1_A94C(arg2, 0, 0)) == 0) {
        var_r31 = 0;
    }
    else {
        fn_1_B0B8(arg0, arg1, var_r30);
        var_r31 = var_r30;
    }
    var_r29 = var_r31;
    return var_r29;
}

s32 fn_1_B0B8(s16 arg0, u8 arg1, s16 arg2)
{
    s32 var_r27;
    unkSubStruct *var_r29;
    unkSubStruct2 *temp_r28;
    unkSubStruct3 *temp_r30;
    unkSubStruct4 *temp_r31;

    if (arg2 == 0) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }
    temp_r28 = &lbl_1_bss_36C.unk40[arg0];
    temp_r28->unk8 |= 2;
    temp_r28->unk34[arg1] = arg2;
    temp_r30 = &lbl_1_bss_36C.unk3C[arg2];
    var_r29 = temp_r28->unk3C;

    for (var_r27 = 0; var_r27 < temp_r28->unk2; var_r27++, var_r29++) {
        if (arg1 == 0) {
            var_r29->unk40[0].x = -0.5f * temp_r30->unk4E;
            var_r29->unk40[0].y = 0.5f * temp_r30->unk50;
            var_r29->unk40[1].x = (0.5f * temp_r30->unk4E);
            var_r29->unk40[1].y = (0.5f * temp_r30->unk50);
            var_r29->unk40[2].x = (0.5f * temp_r30->unk4E);
            var_r29->unk40[2].y = (-0.5f * temp_r30->unk50);
            var_r29->unk40[3].x = (-0.5f * temp_r30->unk4E);
            var_r29->unk40[3].y = (-0.5f * temp_r30->unk50);
            var_r29->unk40[0].z = var_r29->unk40[1].z = var_r29->unk40[2].z = var_r29->unk40[3].z = 0.0f;
        }
        temp_r31 = &var_r29->unk54[arg1];
        temp_r31->unk24 = 0;
        temp_r31->unk0 = temp_r31->unk1 = 0;
        temp_r31->unk28 = 1.0f;
        temp_r31->unk2C = 0.0f;
        temp_r31->unk4[0].x = temp_r31->unk0 * temp_r30->unk54;
        temp_r31->unk4[0].y = temp_r31->unk0 * temp_r30->unk58;
        temp_r31->unk4[1].x = (temp_r31->unk0 + 1) * temp_r30->unk54;
        temp_r31->unk4[1].y = temp_r31->unk0 * temp_r30->unk58;
        temp_r31->unk4[2].x = (temp_r31->unk0 + 1) * temp_r30->unk54;
        temp_r31->unk4[2].y = (temp_r31->unk0 + 1) * temp_r30->unk58;
        temp_r31->unk4[3].x = temp_r31->unk0 * temp_r30->unk54;
        temp_r31->unk4[3].y = (temp_r31->unk0 + 1) * temp_r30->unk58;
        if ((temp_r31->unk0 + 1) < temp_r30->unk4C) {
            temp_r31->unk4[2].y -= temp_r30->unk60;
            temp_r31->unk4[3].y -= temp_r30->unk60;
        }
        DCFlushRangeNoSync(temp_r31->unk4, 0x20);
    }
    lbl_1_bss_36C.unk36 = arg0;
    lbl_1_bss_36C.unk3A = arg1;
    return 1;
}

void fn_1_B634(s32 arg0)
{
    s32 var_r28;
    s32 var_r27;
    s16 var_r26;
    unkSubStruct2 *temp_r31;
    unkSubStruct3 *temp_r30;
    unkSubStruct3 *temp_r29;

    for (var_r28 = 1; var_r28 < lbl_1_bss_36C.unk30; var_r28++) {
        if ((s16)var_r28 != 0) {
            temp_r31 = &lbl_1_bss_36C.unk40[(s16)var_r28];
            if (temp_r31->unk8 != 0) {
                if (temp_r31->unk50 != NULL) {
                    HuMemDirectFree(temp_r31->unk50);
                }
                if (temp_r31->unk54 != NULL) {
                    HuMemDirectFree(temp_r31->unk54);
                }
                if (temp_r31->unk58 != NULL) {
                    HuMemDirectFree(temp_r31->unk58);
                }
                if (temp_r31->unk4C != NULL) {
                    HuMemDirectFree(temp_r31->unk4C);
                }
                if (temp_r31->unk5C != NULL) {
                    HuMemDirectFree(temp_r31->unk5C);
                }

                for (var_r27 = 0; var_r27 < temp_r31->unk4; var_r27++) {
                    var_r26 = temp_r31->unk34[var_r27];
                    temp_r29 = &lbl_1_bss_36C.unk3C[var_r26];
                    if (temp_r29->unk8 != 0) {
                        if (temp_r29->unk6 != 0) {
                            temp_r29->unk6--;
                        }
                        if (temp_r29->unk6 == 0) {
                            HuSprAnimKill(temp_r29->unk0);
                            temp_r29->unk8 = 0;
                        }
                    }
                }
                HuMemDirectFree(temp_r31->unk3C);
                HuMemDirectFree(temp_r31->unk34);
                temp_r31->unk8 = 0;
            }
        }
    }

    for (var_r28 = 1; var_r28 < lbl_1_bss_36C.unk32; var_r28++) {
        temp_r30 = &lbl_1_bss_36C.unk3C[(s16)var_r28];
        if (temp_r30->unk8 != 0) {
            if (temp_r30->unk6 != 0) {
                temp_r30->unk6 -= 1;
            }
            if (temp_r30->unk6 == 0) {
                HuSprAnimKill(temp_r30->unk0);
                temp_r30->unk8 = 0;
            }
        }
    }
    HuMemDirectFree(lbl_1_bss_36C.unk40);
    HuMemDirectFree(lbl_1_bss_36C.unk3C);
    Hu3DModelKill(lbl_1_bss_36C.unk34);
}

void fn_1_B864(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        temp_r31->unkC.x = arg8;
        temp_r31->unkC.y = arg9;
        temp_r31->unkC.z = argA;
        if (temp_r31->unk2 == 1) {
            temp_r31->unk3C->unk0 = temp_r31->unkC;
        }
    }
}

void fn_1_B8D0(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    unkSubStruct *temp_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unk0.x = arg8;
            temp_r31->unk0.y = arg9;
            temp_r31->unk0.z = argA;
        }
    }
}

void fn_1_B940(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    s32 var_r29;
    unkSubStruct *var_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        var_r31 = temp_r30->unk3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unk0.x = arg8;
            var_r31->unk0.y = arg9;
            var_r31->unk0.z = argA;
        }
    }
}

void fn_1_B9B4(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        temp_r31->unkC.x += arg8;
        temp_r31->unkC.y += arg9;
        temp_r31->unkC.z += argA;
        if (temp_r31->unk2 == 1) {
            temp_r31->unk3C->unk0 = temp_r31->unkC;
        }
    }
}

void fn_1_BA38(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    unkSubStruct *temp_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unk0.x += arg8;
            temp_r31->unk0.y += arg9;
            temp_r31->unk0.z += argA;
        }
    }
}

void fn_1_BAC0(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    s32 var_r29;
    unkSubStruct *var_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        var_r31 = temp_r30->unk3C;

        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unk0.x += arg8;
            var_r31->unk0.y += arg9;
            var_r31->unk0.z += argA;
        }
    }
}

void fn_1_BB4C(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        temp_r31->unk18.x = arg8;
        temp_r31->unk18.y = arg9;
        temp_r31->unk18.z = argA;
        if (temp_r31->unk2 == 1) {
            temp_r31->unk3C->unkC = temp_r31->unk18;
        }
    }
}

void fn_1_BBB8(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    unkSubStruct *temp_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unkC.x = arg8;
            temp_r31->unkC.y = arg9;
            temp_r31->unkC.z = argA;
        }
    }
}

void fn_1_BC28(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    s32 var_r29;
    unkSubStruct *var_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        var_r31 = temp_r30->unk3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unkC.x = arg8;
            var_r31->unkC.y = arg9;
            var_r31->unkC.z = argA;
        }
    }
}

void fn_1_BC9C(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        temp_r31->unk24.x = arg8;
        temp_r31->unk24.y = arg9;
        temp_r31->unk24.z = argA;
        if (temp_r31->unk2 == 1) {
            temp_r31->unk3C->unk18 = temp_r31->unk24;
        }
    }
}

void fn_1_BD08(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA)
{
    unkSubStruct *temp_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unk18.x = arg8;
            temp_r31->unk18.y = arg9;
            temp_r31->unk18.z = argA;
        }
    }
}

void fn_1_BD78(s16 arg0, f32 arg8, f32 arg9, f32 argA)
{
    s32 var_r29;
    unkSubStruct *var_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        var_r31 = temp_r30->unk3C;
        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unk18.x = arg8;
            var_r31->unk18.y = arg9;
            var_r31->unk18.z = argA;
        }
    }
}

void fn_1_BDEC(s16 arg0, s32 arg1)
{
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        temp_r31->unk8 |= arg1;
    }
}

void fn_1_BE30(s16 arg0, s16 arg1, s32 arg2)
{
    unkSubStruct *temp_r30;
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            temp_r30 = &temp_r31->unk3C[arg1];
            temp_r30->unk34 |= arg2;
        }
    }
}

void fn_1_BEA0(s16 arg0, s32 arg1)
{
    s32 var_r30;
    unkSubStruct *temp_r29;
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        temp_r29 = temp_r31->unk3C;

        for (var_r30 = 0; var_r30 < temp_r31->unk2; var_r30++) {
            temp_r29->unk34 |= arg1;
        }
    }
}

void fn_1_BF10(s16 arg0, u32 arg1)
{
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        temp_r31->unk8 &= ~arg1;
    }
}

void fn_1_BF54(s16 arg0, s16 arg1, u32 arg2)
{
    unkSubStruct *temp_r30;
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            temp_r30 = &temp_r31->unk3C[arg1];
            temp_r30->unk34 &= ~arg2;
        }
    }
}

void fn_1_BFC4(s16 arg0, u32 arg1)
{
    s32 var_r30;
    unkSubStruct *temp_r29;
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        temp_r29 = temp_r31->unk3C;

        for (var_r30 = 0; var_r30 < temp_r31->unk2; var_r30++) {
            temp_r29->unk34 &= ~arg1;
        }
    }
}

s32 fn_1_C034(s16 arg0, s32 arg1)
{
    unkSubStruct2 *temp_r31;

    if (arg0 == 0) {
        return 0;
    }

    temp_r31 = &lbl_1_bss_36C.unk40[arg0];
    if ((temp_r31->unk8 & arg1) != 0) {
        return 1;
    }
    return 0;
}

s16 fn_1_C090(s16 arg0, s16 arg1, s32 arg2)
{
    unkSubStruct *temp_r30;
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            temp_r30 = &temp_r31->unk3C[arg1];
            if ((temp_r30->unk34 & arg2) != 0) {
                arg0 = 1;
            }
            else {
                arg0 = 0;
            }
        }
    }
    return arg0;
}

void fn_1_C110(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5)
{
    unkSubStruct *temp_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unk50.r = arg2;
            temp_r31->unk50.g = arg3;
            temp_r31->unk50.b = arg4;
            temp_r31->unk50.a = arg5;
        }
    }
}

void fn_1_C184(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4)
{
    s32 var_r29;
    unkSubStruct *var_r31;
    unkSubStruct2 *temp_r30;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_36C.unk40[arg0];
        var_r31 = temp_r30->unk3C;

        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unk50.r = arg1;
            var_r31->unk50.g = arg2;
            var_r31->unk50.b = arg3;
            var_r31->unk50.a = arg4;
        }
    }
}

void fn_1_C1FC(s16 arg0, s16 arg1, u8 arg2)
{
    unkSubStruct *temp_r30;
    unkSubStruct2 *temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            temp_r30 = &temp_r31->unk3C[arg1];
            temp_r30->unk30 = arg2;
        }
    }
}

void fn_1_C264(s16 arg0, u8 arg1)
{
    s32 var_r29;
    unkSubStruct2 *temp_r31;
    unkSubStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        var_r30 = temp_r31->unk3C;

        for (var_r29 = 0; var_r29 < temp_r31->unk2; var_r29++, var_r30++) {
            var_r30->unk30 = arg1;
        }
    }
}

void fn_1_C2D0(s16 arg0, s16 arg1, u8 arg2)
{
    unkSubStruct2 *temp_r31;
    unkSubStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk31 = arg2;
        }
    }
}

void fn_1_C338(s16 arg0, u8 arg1)
{
    s32 var_r29;
    unkSubStruct2 *temp_r31;
    unkSubStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        var_r30 = temp_r31->unk3C;

        for (var_r29 = 0; var_r29 < temp_r31->unk2; var_r29++, var_r30++) {
            var_r30->unk31 = arg1;
        }
    }
}

void fn_1_C3A4(s16 arg0, s16 arg1, u8 arg2)
{
    unkSubStruct2 *temp_r31;
    unkSubStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54->unk24 = arg2;
        }
    }
}

void fn_1_C410(s16 arg0, s16 arg1, u8 arg2, u8 arg3)
{
    unkSubStruct2 *temp_r31;
    unkSubStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54[arg2].unk24 = arg3;
        }
    }
}

void fn_1_C488(s16 arg0, u8 arg1)
{
    s32 var_r28;
    s32 var_r30;
    unkSubStruct *var_r31;
    unkSubStruct2 *temp_r29;

    if (arg0 != 0) {
        temp_r29 = &lbl_1_bss_36C.unk40[arg0];
        var_r31 = (unkSubStruct *)&temp_r29->unk3C; //! BAD WHY
        (void)temp_r29;

        for (var_r28 = 0; var_r28 < temp_r29->unk2; var_r28++, var_r31++) {
            for (var_r30 = 0; var_r30 < var_r31->unk33; var_r30++) {
                var_r31->unk54[var_r30].unk24 = arg1;
            }
        }
    }
}

void fn_1_C520(s16 arg0, s16 arg1, f32 arg8)
{
    unkSubStruct2 *temp_r31;
    unkSubStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54->unk28 = arg8;
        }
    }
}

void fn_1_C58C(s16 arg0, s16 arg1, u8 arg2, f32 arg8)
{
    unkSubStruct2 *temp_r31;
    unkSubStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54[arg2].unk28 = arg8;
        }
    }
}

void fn_1_C604(s16 arg0, f32 arg8)
{
    unkSubStruct *volatile sp8;
    s32 var_r29;
    unkSubStruct2 *temp_r31;
    s32 var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        sp8 = temp_r31->unk3C;

        for (var_r29 = 0; var_r29 < temp_r31->unk2; var_r29++) {
            for (var_r30 = 0; var_r30 < sp8->unk33; var_r30++) {
                sp8->unk54[var_r30].unk28 = arg8;
            }
        }
    }
}

void fn_1_C69C(s16 arg0, s16 arg1, u8 arg2)
{
    unkSubStruct2 *temp_r31;
    unkSubStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54->unk0 = arg2;
        }
    }
}

void fn_1_C70C(s16 arg0, s16 arg1, u8 arg2, u8 arg3)
{
    unkSubStruct2 *temp_r31;
    unkSubStruct *var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54[arg2].unk0 = arg3;
        }
    }
}

// ...

void fn_1_C784(s16 arg0, u8 arg1)
{
    unkSubStruct *volatile sp8;
    s32 var_r29;
    unkSubStruct2 *temp_r31;
    s32 var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_36C.unk40[arg0];
        sp8 = temp_r31->unk3C;
        for (var_r29 = 0; var_r29 < temp_r31->unk2; var_r29++) {
            for (var_r30 = 0; var_r30 < sp8->unk33; var_r30++) {
                sp8->unk54[var_r30].unk0 = arg1;
            }
        }
    }
}

void fn_1_C81C(s16 arg0, u8 arg1)
{
    unkSubStruct3 *var_r31;
    if (arg0 != 0) {
        var_r31 = &lbl_1_bss_36C.unk3C[arg0];
        var_r31->unk4 = arg1;
    }
}
