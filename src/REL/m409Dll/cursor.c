#define HUSPR_USE_OLD_DEFS
#include "REL/m409Dll.h"

#include "game/hsfdraw.h"
#include "game/sprite.h"

void fn_1_BF88(s16 arg0, s16 arg1) {
    s32 var_r31;
    s32 var_r31_2;
    unkStruct8* var_r29;
    unkStruct9Sub* var_r30;

    lbl_1_bss_F0.unk4 = Hu3DHookFuncCreate(fn_1_CB98);
    Hu3DModelLayerSet(lbl_1_bss_F0.unk4, 6);
    lbl_1_bss_F0.unk0 = arg0;
    var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(unkStruct8), 0x10000000);
    lbl_1_bss_F0.unk10 = var_r29;
    lbl_1_bss_F0.unk2 = arg1;
    var_r30 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(unkStruct9Sub), 0x10000000);
    lbl_1_bss_F0.unkC = var_r30;
    
    for (var_r31 = 0; var_r31 < arg0; var_r31++, var_r29++) {
        var_r29->unk8 = 0;
    }
    
    for (var_r31 = 0; var_r31 < arg1; var_r31++, var_r30++) {
        var_r30->unk6 = 0;
        var_r30->unk8 = 0;
    }
    
    lbl_1_bss_F0.unk6 = lbl_1_bss_F0.unk8 = lbl_1_bss_F0.unkA = 0;
}

void fn_1_C0C0(void) {
    s32 var_r31;

    for (var_r31 = 1; var_r31 < lbl_1_bss_F0.unk0; var_r31++) {
        fn_1_DDB8(var_r31);
    }
    
    for (var_r31 = 1; var_r31 < lbl_1_bss_F0.unk2; var_r31++) {
        fn_1_E228(var_r31);
    }
    HuMemDirectFree(lbl_1_bss_F0.unk10);
    HuMemDirectFree(lbl_1_bss_F0.unkC);
    Hu3DModelKill(lbl_1_bss_F0.unk4);
}

extern u8 texMtxTbl[];

void fn_1_C164(unkStruct8* arg0) {
    ModelData spEC;
    Mtx spBC;
    Mtx sp8C;
    Mtx sp5C;
    Mtx sp2C;
    GXColor sp28;
    s16 sp8;
    GXColorSrc var_r25;
    s32 var_r26;
    s16 temp_r23;
    unkStruct9Sub* temp_r28;
    s16 var_r27;
    s16 var_r30;
    s32 var_r24;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    unkStruct8Sub* var_r31;

    mtxRot(sp2C, arg0->unk18.x, arg0->unk18.y, arg0->unk18.z);
    PSMTXScale(sp5C, arg0->unk24.x, arg0->unk24.y, arg0->unk24.z);
    PSMTXConcat(sp2C, sp5C, sp5C);
    mtxTransCat(sp5C, arg0->unkC.x, arg0->unkC.y, arg0->unkC.z);
    PSMTXConcat(Hu3DCameraMtx, sp5C, sp8C);
    var_r30 = 0;
    var_r27 = 0;
    sp8 = 0;
    
    for (var_r26 = GX_TEXMAP0; var_r26 < arg0->unk4; var_r26++) {
        temp_r28 = &lbl_1_bss_F0.unkC[arg0->unk34[var_r26]];
        PSMTXRotRad(temp_r28->unk18, 0x5A, 0.0f);
        mtxTransCat(temp_r28->unk18, temp_r28->unkC.x, temp_r28->unkC.y, temp_r28->unkC.z);
        switch (temp_r28->unk4) {
            case 0:
                GXLoadTexMtxImm(temp_r28->unk18, texMtxTbl[var_r27], GX_MTX2x4);
                var_r22 = texMtxTbl[var_r27];
                GXSetTexCoordGen2(var_r27, GX_TG_MTX2x4, var_r26 + GX_TG_TEX0, var_r22, GX_FALSE, 0x7D);
                GXSetTevOrder(var_r30, var_r27, var_r26, GX_COLOR0A0);
                if (var_r26 == GX_TEXMAP0) {
                    if ((temp_r28->unk0->bmp->dataFmt == 7) || (temp_r28->unk0->bmp->dataFmt == 8)) {
                        GXSetTevColor(GX_TEVREG2, temp_r28->unk48);
                        GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_C2, GX_CC_RASC, GX_CC_ZERO);
                    } else {
                        GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                    }
                    GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                } else {
                    sp28.a = temp_r28->unk48.a;
                    GXSetTevColor(GX_TEVREG2, sp28);
                    GXSetTevColorIn(var_r30, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A2, GX_CC_ZERO);
                    GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                }
                GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                break;
            case 1:
                GXLoadTexMtxImm(temp_r28->unk18, texMtxTbl[var_r27], GX_MTX2x4);
                var_r21 = texMtxTbl[var_r27];
                GXSetTexCoordGen2(var_r27, GX_TG_MTX2x4, var_r26 + GX_TG_TEX0, var_r21, GX_FALSE, 0x7D);
                GXSetTevOrder(var_r30, var_r27, var_r26, GX_COLOR0A0);
                GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
                GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
                GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                break;
            case 2:
                sp28.a = 0xE0;
                GXSetTevColor(GX_TEVREG1, sp28);
                GXSetTexCoordGen2(var_r27 + GX_TEXCOORD1, GX_TG_BUMP0, var_r27, 0x3C, GX_FALSE, 0x7D);
                GXSetTevOrder(var_r30, var_r27, var_r26, GX_COLOR0A0);
                GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_RASC);
                GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                var_r30++;
                GXSetTevOrder(var_r30, var_r27 + GX_TEXCOORD1, GX_TEXMAP0, GX_COLOR0A0);
                GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A1, GX_CC_CPREV);
                GXSetTevColorOp(var_r30, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
                break;
            case 3:
                var_r27--;
                GXLoadTexMtxImm(temp_r28->unk18, texMtxTbl[var_r27], GX_MTX2x4);
                var_r20 = texMtxTbl[var_r27];
                GXSetTexCoordGen2(var_r27, GX_TG_MTX2x4, var_r26 + GX_TG_TEX0, var_r20, GX_FALSE, 0x7D);
                GXSetTevOrder(var_r30, var_r27, var_r26, GX_COLOR0A0);
                GXSetTevColorIn(var_r30, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
                GXSetTevColorOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(var_r30, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
                GXSetTevAlphaOp(var_r30, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                var_r27++;
                break;
        }
        var_r30++;
        var_r27++;
        HuSprTexLoad(temp_r28->unk0, 0, var_r26, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    }
    GXSetNumTevStages((s32)var_r30);
    GXSetNumTexGens((s32)var_r27);
    var_r31 = arg0->unk3C;
    
    for (var_r24 = 0; var_r24 < arg0->unk2; var_r24++, var_r31++) {
        if ((var_r31->unk34 != 0) && ((var_r31->unk34 & 4) == 0)) {
            switch (var_r31->unk30) {
                case 0:
                    mtxRot(sp2C, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
                    PSMTXIdentity(sp5C);
                    HmfInverseMtxF3X3(Hu3DCameraMtx, sp5C);
                    PSMTXConcat(sp5C, sp2C, sp2C);
                    PSMTXScale(sp5C, var_r31->unk18.x, var_r31->unk18.y, var_r31->unk18.z);
                    PSMTXConcat(sp2C, sp5C, sp5C);
                    mtxTransCat(sp5C, var_r31->unk0.x, var_r31->unk0.y, var_r31->unk0.z);
                    PSMTXConcat(Hu3DCameraMtx, sp5C, spBC);
                    break;
                case 1:
                    PSMTXCopy(sp8C, sp2C);
                    mtxRotCat(sp2C, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
                    PSMTXScale(sp5C, var_r31->unk18.x, var_r31->unk18.y, var_r31->unk18.z);
                    PSMTXConcat(sp2C, sp5C, sp5C);
                    mtxTransCat(sp5C, var_r31->unk0.x, var_r31->unk0.y, var_r31->unk0.z);
                    PSMTXCopy(sp5C, spBC);
                    break;
            }
            GXLoadPosMtxImm(spBC, 0);
            PSMTXInverse(spBC, sp5C);
            PSMTXTranspose(sp5C, sp2C);
            GXLoadNrmMtxImm(sp2C, 0);
            GXSetChanAmbColor(GX_COLOR0A0, var_r31->unk4C);
            GXSetChanMatColor(GX_COLOR0A0, var_r31->unk50);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            if ((var_r31->unk34 & 0x10) != 0) {
                GXSetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);
            } else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            }
            spEC.attr = 0;
            temp_r23 = Hu3DLightSet(&spEC, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, 0.0f);
            GXSetNumChans(1);
            if ((var_r31->unk34 & 8) != 0) {
                var_r25 = GX_SRC_VTX;
            } else {
                var_r25 = GX_SRC_REG;
            }
            switch (var_r31->unk31) {
                case 0:
                    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, var_r25, 0, GX_DF_CLAMP, GX_AF_NONE);
                    break;
                case 1:
                    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, var_r25, temp_r23, GX_DF_CLAMP, GX_AF_SPOT);
                    break;
                case 2:
                    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, var_r25, temp_r23, GX_DF_CLAMP, GX_AF_SPEC);
                    break;
            }
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
            GXSetArray(GX_VA_POS, var_r31->unk40, 0xC);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
            GXSetArray(GX_VA_CLR0, var_r31->unk44, 4);
            for (var_r26 = 0; var_r26 < var_r31->unk32; var_r26++) {
                GXSetVtxDesc(var_r26 + GX_VA_TEX0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, var_r26 + GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
                GXSetArray(var_r26 + GX_VA_TEX0, var_r31->unk54[var_r26].unk4, 8);
            }
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA6, 0);
            GXSetArray(GX_VA_NRM, var_r31->unk48, 0xC);
            GXCallDisplayList(var_r31->unk3C, var_r31->unk38);
        }
    }
}

void fn_1_CB98(ModelData* model, Mtx matrix) {
    Mtx sp38;
    Mtx sp8;
    s32 var_r30;
    unkStruct8* var_r31;

    var_r31 = lbl_1_bss_F0.unk10;
    GXLoadPosMtxImm(matrix, 0);
    PSMTXInverse(matrix, sp38);
    PSMTXTranspose(sp38, sp8);
    GXLoadNrmMtxImm(sp8, 0);
    
    for (var_r30 = 0; var_r30 < lbl_1_bss_F0.unk0; var_r30++, var_r31++) {
        if ((var_r31->unk8 == 0) || ((var_r31->unk8 & 2) == 0) || ((var_r31->unk8 & 4) != 0)) {
            continue;
        }
        if (omPauseChk() == 0) {
            if (var_r31->unk30) {
                var_r31->unk30(var_r31);
            }
            if (var_r31->unk8 == 0) continue;
            fn_1_D430(var_r31);
            if (var_r31->unk8 == 0) continue;
        }
        fn_1_C164(var_r31);
    }
}

unkStruct8* fn_1_CCB0(s16 idx) {
    return &lbl_1_bss_F0.unk10[idx];
}

unkStruct8Sub* fn_1_CCCC(s16 arg0, s16 arg1) {
    return &lbl_1_bss_F0.unk10[arg0].unk3C[arg1];
}

void fn_1_CCF8(unkStruct11** arg0, s16 arg1, f32 arg8, f32 arg9) {
    s32 var_r30;
    unkStruct11* var_r31;
    
    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(unkStruct11), 0x10000000);
    
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

void fn_1_CE7C(Vec** arg0, s16 arg1, Vec* arg2) {
    s32 var_r29;
    s32 var_r28;
    Vec* var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(Vec[4]), 0x10000000);
    
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
            var_r31->z = arg2->z;
        }
    }
}

void fn_1_CF1C(GXColor** arg0, s16 arg1, GXColor* arg2) {
    s32 var_r29;
    s32 var_r28;
    GXColor* var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(GXColor[4]), 0x10000000U);
    
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->r = arg2->r;
            var_r31->g = arg2->g;
            var_r31->b = arg2->b;
            var_r31->a = arg2->a;
        }
    }
}

void fn_1_CFC4(Vec** arg0, s16 arg1, Vec* arg2) {
    s32 var_r29;
    Vec* var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(Vec), 0x10000000U);
    
    for (var_r29 = 0; var_r29 < arg1; var_r31++, arg2++, var_r29++) {
        var_r31->x = arg2->x;
        var_r31->y = arg2->y;
        var_r31->z = arg2->z;
    }
}

void fn_1_D050(HsfVector2f** arg0, s16 arg1, HsfVector2f* arg2) {
    s32 var_r28;
    s32 var_r29;
    HsfVector2f* var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(HsfVector2f[4]), 0x10000000U);

    for (var_r28 = 0; var_r28 < arg1; var_r28++) {
        for (var_r29 = 0; var_r29 < 4; var_r31++, arg2++, var_r29++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
        }
    }
}

void fn_1_D0E8(unkStruct8Sub* arg0) {
    Vec sp18[4] = {
        { -50.0f,  50.0f, 0.0f },
        {  50.0f,  50.0f, 0.0f },
        {  50.0f, -50.0f, 0.0f },
        { -50.0f, -50.0f, 0.0f }
    };
    GXColor sp8[4] = {
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF }
    };
    s32 var_r26;
    s32 var_r25;
    void* temp_r3_3;
    
    if (arg0->unk40 != NULL) {
        HuMemDirectFree(arg0->unk40);
    }
    fn_1_CE7C((Vec**)&arg0->unk40, 1, &sp18[0]);
    if (arg0->unk44 != NULL) {
        HuMemDirectFree(arg0->unk44);
    }
    fn_1_CF1C((GXColor**)&arg0->unk44, 1, &sp8[0]);
    if (arg0->unk48 != NULL) {
        HuMemDirectFree(arg0->unk48);
    }
    arg0->unk48 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Vec), 0x10000000);
    arg0->unk48->x = 0.0f;
    arg0->unk48->y = 0.0f;
    arg0->unk48->z = 1.0f;
    if (arg0->unk3C != NULL) {
        HuMemDirectFree(arg0->unk3C);
    }
    temp_r3_3 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x1000, 0x10000000);
    arg0->unk3C = temp_r3_3;
    DCFlushRange(arg0->unk3C, 0x1000);
    GXBeginDisplayList(temp_r3_3, 0x1000);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    
    for (var_r26 = 0; var_r26 < 4; var_r26++) {
        GXPosition1x16(var_r26);
        GXColor1x16(0);
        GXNormal1x16(var_r26);
        
        for (var_r25 = 0; var_r25 < arg0->unk32; var_r25++) {
            GXTexCoord1x16(var_r26);
        }
    }
    arg0->unk38 = GXEndDisplayList();
}

void fn_1_D430(unkStruct8* arg0) {
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    unkStruct8Sub* var_r28;
    unkStruct12* var_r31;
    unkStruct9Sub* temp_r30;

    var_r27 = 0;
    var_r28 = arg0->unk3C;
    
    for (var_r25 = 0; var_r25 < arg0->unk2; var_r25++, var_r28++) {
        if ((var_r28->unk34 & 4) != 0) {
            var_r27++;
        } else {
            var_r31 = var_r28->unk54;
            
            for (var_r26 = 0; var_r26 < var_r28->unk32; var_r26++, var_r31++) {
                temp_r30 = &lbl_1_bss_F0.unkC[arg0->unk34[var_r26]];
                var_r31->unk8 &= ~4;
                switch (var_r31->unk8 & 0xF) {
                    case 1:
                        var_r31->unk10 += var_r31->unkC;
                        if (var_r31->unk10 >= 1.0f) {
                            var_r31->unk0++;
                            var_r31->unk10--;
                        }
                        break;
                    case 2:
                        var_r31->unk10 += var_r31->unkC;
                        if (var_r31->unk10 >= 1.0f) {
                            var_r31->unk0--;
                            var_r31->unk10--;
                        }
                        break;
                }
                if (var_r31->unk0 >= temp_r30->unk4C) {
                    if ((var_r31->unk8 & 0x10) != 0) {
                        var_r31->unk8 |= 8;
                        var_r31->unk0--;
                    } else if ((var_r31->unk8 & 0x40) != 0) {
                        var_r31->unk8 = (var_r31->unk8 & 0xF0) | 2;
                        var_r31->unk0 -= 2;
                    } else if ((var_r31->unk8 & 0x20) != 0) {
                        var_r31->unk0 = 0;
                    }
                    var_r31->unk8 |= 4;
                } else if (var_r31->unk0 < 0) {
                    if ((var_r31->unk8 & 0x10) != 0) {
                        var_r31->unk8 |= 8;
                        var_r31->unk0 = 0;
                    } else if ((var_r31->unk8 & 0x20) != 0) {
                        if ((var_r31->unk8 & 0x40) != 0) {
                            var_r31->unk8 = ((var_r31->unk8 & 0xF0) | 1);
                            var_r31->unk0 = 1U;
                        } else {
                            var_r31->unk0 = (temp_r30->unk4C - 1);
                        }
                    } else if ((var_r31->unk8 & 0x40) != 0) {
                        var_r31->unk8 |= 8;
                        var_r31->unk0 = 0;
                    }
                    var_r31->unk8 |= 4;
                } else {
                    var_r31->unk8 &= ~8;
                }
                if (var_r31->unk0 != var_r31->unk1) {
                    var_r31->unk4[0].x = (var_r31->unk0 * temp_r30->unk54);
                    var_r31->unk4[0].y = (var_r31->unk0 * temp_r30->unk58);
                    var_r31->unk4[1].x = ((var_r31->unk0 + 1) * temp_r30->unk54);
                    var_r31->unk4[1].y = (var_r31->unk0 * temp_r30->unk58);
                    var_r31->unk4[2].x = ((var_r31->unk0 + 1) * temp_r30->unk54);
                    var_r31->unk4[2].y = ((var_r31->unk0 + 1) * temp_r30->unk58);
                    var_r31->unk4[3].x = (var_r31->unk0 * temp_r30->unk54);
                    var_r31->unk4[3].y = ((var_r31->unk0 + 1) * temp_r30->unk58);
                    if ((var_r31->unk0 + 1) < temp_r30->unk4C) {
                        var_r31->unk4[2].y -= temp_r30->unk60;
                        var_r31->unk4[3].y -= temp_r30->unk60;
                    }
                    var_r31->unk1 = var_r31->unk0;
                }
                if ((var_r31->unk8 & 8) != 0) {
                    if ((var_r28->unk34 & 0x40000000) != 0) {
                        var_r28->unk34 |= 4;
                        if ((var_r31->unk8 & 0x40) == 0) {
                            if (var_r31->unk0 <= 0) {
                                var_r31->unk0 = temp_r30->unk4C;
                            } else {
                                var_r31->unk0 = 0U;
                            }
                        }
                    } else if ((var_r28->unk34 & 0x80000000) != 0) {
                        fn_1_DDB8(arg0->unk0);
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
            fn_1_DDB8(arg0->unk0);
        }
    }
}

s16 fn_1_DA48(u8 arg0, u8 arg1) {
    s32 var_r29;
    s32 var_r28;
    unkStruct8* var_r30;
    unkStruct8Sub* var_r31;

    var_r30 = &lbl_1_bss_F0.unk10[1];
    
    for (var_r29 = 1; var_r29 < lbl_1_bss_F0.unk0; var_r29++, var_r30++) {
        if (var_r30->unk8 == 0) break;
    
    }
    
    if (var_r29 == lbl_1_bss_F0.unk0) return 0;
    
    var_r30->unk0 = var_r29;
    var_r30->unk8 = 1;
    var_r30->unk30 = NULL;
    var_r30->unk2 = arg0;
    var_r30->unk4 = arg1;
    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(unkStruct8Sub), 0x10000000);
    var_r30->unk3C = var_r31;
    var_r30->unk34 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(s16), 0x10000000);
    var_r30->unkC.x = var_r30->unkC.y = var_r30->unkC.z = 0.0f;
    var_r30->unk18.x = var_r30->unk18.y = var_r30->unk18.z = 0.0f;
    var_r30->unk24.x = var_r30->unk24.y = var_r30->unk24.z = 1.0f;
    var_r30->unk54.x = var_r30->unk54.y = var_r30->unk54.z = 0.0f;
    var_r30->unk48.x = var_r30->unk48.y = var_r30->unk48.z = 0.0f;
    
    for (var_r29 = 0; var_r29 < 0x20; var_r29++) {
        var_r30->unk60[var_r29] = 0;
    }
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        var_r30->unk34[var_r29] = 0;
    }
    
    for (var_r29 = 0; var_r29 < arg0; var_r29++, var_r31++) {
        var_r31->unk34 = 1;
        var_r31->unk32 = arg1;
        var_r31->unk30 = 0;
        var_r31->unk31 = 0;
        var_r31->unk4C.r = var_r31->unk4C.g = var_r31->unk4C.b = 0;
        var_r31->unk4C.a = 0xFF;
        var_r31->unk50.r = var_r31->unk50.g = var_r31->unk50.b = 0xFF;
        var_r31->unk50.a = 0xFF;
        var_r31->unk54 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(unkStruct12), 0x10000000);
        
        for (var_r28 = 0; var_r28 < arg1; var_r28++) {
            var_r31->unk54[var_r28].unk0 = var_r31->unk54[var_r28].unk1 = 0;
            var_r31->unk54[var_r28].unk4 = NULL;
            var_r31->unk54[var_r28].unkC = 1.0f;
            var_r31->unk54[var_r28].unk10 = 0.0f;
        }
        var_r31->unk0.x = var_r31->unk0.y = var_r31->unk0.z = 0.0f;
        var_r31->unkC.x = var_r31->unkC.y = var_r31->unkC.z = 0.0f;
        var_r31->unk18.x = var_r31->unk18.y = var_r31->unk18.z = 1.0f;
        var_r31->unk64.x = var_r31->unk64.y = var_r31->unk64.z = 0.0f;
        var_r31->unk58.x = var_r31->unk58.y = var_r31->unk58.z = 0.0f;
        
        for (var_r28 = 0; var_r28 < 0x10; var_r28++) {
            var_r31->unk70[var_r28] = 0;
        }
        var_r31->unk40 = var_r31->unk44 = var_r31->unk48 = NULL;
        var_r31->unk3C = NULL;
        fn_1_D0E8(var_r31);
    }
    return var_r30->unk0;
}

void fn_1_DDB8(s16 arg0) {
    unkStruct12* var_r28;
    s32 var_r29;
    unkStruct8* temp_r30;
    unkStruct8Sub* var_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r30->unk8 != 0) {
            var_r31 = temp_r30->unk3C;
            
            for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
                if (var_r31->unk40 != NULL) {
                    HuMemDirectFree(var_r31->unk40);
                }
                if (var_r31->unk44 != NULL) {
                    HuMemDirectFree(var_r31->unk44);
                }
                if (var_r31->unk48 != NULL) {
                    HuMemDirectFree(var_r31->unk48);
                }
                if (var_r31->unk3C != NULL) {
                    HuMemDirectFree(var_r31->unk3C);
                }
                var_r28 = var_r31->unk54;
                HuMemDirectFree(var_r28->unk4);
                HuMemDirectFree(var_r31->unk54);
            }
            
            for (var_r29 = 0; var_r29 < temp_r30->unk4; var_r29++) {
                fn_1_E228(temp_r30->unk34[var_r29]);
            }
            HuMemDirectFree(temp_r30->unk3C);
            HuMemDirectFree(temp_r30->unk34);
            temp_r30->unk8 = 0;
            temp_r30->unk0 = 0;
        }
    }
}

void fn_1_DEF4(s16 arg0, s16 arg1, u8 arg2) {
    lbl_1_bss_F0.unk6 = arg0;
    lbl_1_bss_F0.unk8 = arg1;
    lbl_1_bss_F0.unkA = arg2;
}

s16 fn_1_DF20(u32 arg0, s16 arg1, s16 arg2) {
    AnimData* temp_r30;
    f32 var_f31;
    f32 var_f30;
    s32 var_r29;
    unkStruct9Sub* var_r31;

    var_r31 = &lbl_1_bss_F0.unkC[1];
    
    for (var_r29 = 1; var_r29 < lbl_1_bss_F0.unk2; var_r29++, var_r31++) {
        if ((var_r31->unk6 != 0) && (var_r31->unk8 == arg0)) break;
    }
    if (var_r29 < lbl_1_bss_F0.unk2) {
        var_r31->unk6++;
        return var_r29;
    }
    var_r31 = &lbl_1_bss_F0.unkC[1];
    
    for (var_r29 = 1; var_r29 < lbl_1_bss_F0.unk2; var_r29++, var_r31++) {
        if (var_r31->unk6 == 0) break;
    }
    var_r31->unk8 = arg0;
    var_r31->unk6 = 1;
    temp_r30 = HuSprAnimRead(HuDataReadNum(arg0, 0x10000000));
    if ((arg1 == 0) || (arg2 == 0)) {
        arg1 = temp_r30->bmp->sizeX;
        arg2 = temp_r30->bmp->sizeY;
        var_f31 = var_f30 = 1.0f;
    } else {
        var_f31 = arg1 / (f32)temp_r30->bmp->sizeX;
        var_f30 = arg2 / (f32)temp_r30->bmp->sizeY;
    }
    var_r31->unk0 = temp_r30;
    var_r31->unk4E = arg1;
    var_r31->unk50 = arg2;
    var_r31->unk54 = var_f31;
    var_r31->unk58 = var_f30;
    var_r31->unk5C = (1.0f / temp_r30->bmp->sizeX);
    var_r31->unk60 = 1.0f / temp_r30->bmp->sizeY;
    var_r31->unk4 = 0;
    var_r31->unk4C = (temp_r30->bmp->sizeY / arg2);
    var_r31->unk48.r = var_r31->unk48.g = var_r31->unk48.b = 0xFF;
    var_r31->unk48.a = 0xFF;
    PSMTXIdentity(var_r31->unk18);
    var_r31->unkC.x = var_r31->unkC.y = var_r31->unkC.z = 0.0f;
    return var_r29;
}

void fn_1_E228(s16 arg0) {
    unkStruct9Sub* temp_r31;
    
    temp_r31 = &lbl_1_bss_F0.unkC[arg0];
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

s32 fn_1_E2A8(s16 arg0, u8 arg1, u32 arg2, s16 arg3, s16 arg4) {
    f32 temp_f31;
    f32 temp_f30;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    unkStruct12* temp_r31;
    unkStruct8* temp_r27;
    unkStruct8Sub* var_r28;
    unkStruct9Sub* temp_r30;
    unkStruct11* var_r29;

    if (arg0 == 0) {
        return 0;
    }
    temp_r27 = &lbl_1_bss_F0.unk10[arg0];
    var_r24 = fn_1_DF20(arg2, arg3, arg4);
    if (var_r24 == 0) {
        return 0;
    }
    temp_r27->unk8 |= 2;
    temp_r27->unk34[arg1] = var_r24;
    temp_r30 = &lbl_1_bss_F0.unkC[var_r24];
    var_r28 = temp_r27->unk3C;
    
    for (var_r26 = 0; var_r26 < temp_r27->unk2; var_r26++, var_r28++) {
        if (arg1 == 0) {
            if (var_r28->unk40) {
                HuMemDirectFree(var_r28->unk40);
            }
            temp_f30 = temp_r30->unk50;
            temp_f31 = temp_r30->unk4E;
            var_r29 = var_r28->unk40 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x30, 0x10000000);
            
            for (var_r25 = 0; var_r25 < 1; var_r29++, var_r25++) {
                var_r29->unk0.x = (-0.5f * temp_f31);
                var_r29->unk0.y = (0.5f * temp_f30);
                var_r29->unk0.z = 0.0f;
                var_r29->unkC.x = (0.5f * temp_f31);
                var_r29->unkC.y = (0.5f * temp_f30);
                var_r29->unkC.z = 0.0f;
                var_r29->unk18.x = (0.5f * temp_f31);
                var_r29->unk18.y = (-0.5f * temp_f30);
                var_r29->unk18.z = 0.0f;
                var_r29->unk24.x = (-0.5f * temp_f31);
                var_r29->unk24.y = (-0.5f * temp_f30);
                var_r29->unk24.z = 0.0f;
            }
        }
        temp_r31 = &var_r28->unk54[arg1];
        temp_r31->unk8 = 0;
        temp_r31->unk0 = temp_r31->unk1 = 0;
        temp_r31->unkC = 1.0f;
        temp_r31->unk10 = 0.0f;
        if (temp_r31->unk4 == NULL) {
            temp_r31->unk4 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x20, 0x10000000U);
        }
        temp_r31->unk4[0].x = temp_r31->unk0 * temp_r30->unk54;
        temp_r31->unk4[0].y = temp_r31->unk0 * temp_r30->unk58;
        temp_r31->unk4[1].x = ((temp_r31->unk0 + 1) * temp_r30->unk54);
        temp_r31->unk4[1].y = (temp_r31->unk0 * temp_r30->unk58);
        temp_r31->unk4[2].x = ((temp_r31->unk0 + 1) * temp_r30->unk54);
        temp_r31->unk4[2].y = ((temp_r31->unk0 + 1) * temp_r30->unk58);
        temp_r31->unk4[3].x = (temp_r31->unk0 * temp_r30->unk54);
        temp_r31->unk4[3].y = ((temp_r31->unk0 + 1) * temp_r30->unk58);
        if ((temp_r31->unk0 + 1) < temp_r30->unk4C) {
            temp_r31->unk4[2].y -= temp_r30->unk60;
            temp_r31->unk4[3].y -= temp_r30->unk60;
        }
    }
    return 1;
}

s32 fn_1_E7C8(s16 arg0, u8 arg1, u32 arg2) {
    s32 var_r31;
    
    var_r31 = fn_1_E2A8(arg0, arg1, arg2, 0, 0);
    return var_r31;
}

void fn_1_E818(s16 arg0, f32 arg8, f32 arg9, f32 argA) {
    unkStruct8* temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        temp_r31->unkC.x = arg8;
        temp_r31->unkC.y = arg9;
        temp_r31->unkC.z = argA;
    }
}

void fn_1_E85C(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA) {
    unkStruct8* temp_r30;
    unkStruct8Sub* temp_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unk0.x = arg8;
            temp_r31->unk0.y = arg9;
            temp_r31->unk0.z = argA;
        }
    }
}

void fn_1_E8CC(s16 arg0, f32 arg8, f32 arg9, f32 argA) {
    s32 var_r29;
    unkStruct8* temp_r30;
    unkStruct8Sub* var_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        var_r31 = temp_r30->unk3C;
        
        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unk0.x = arg8;
            var_r31->unk0.y = arg9;
            var_r31->unk0.z = argA;
        }
    }
}

void fn_1_E940(s16 arg0, f32 arg8, f32 arg9, f32 argA) {
    unkStruct8* temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        temp_r31->unkC.x += arg8;
        temp_r31->unkC.y += arg9;
        temp_r31->unkC.z += argA;
    }
}

void fn_1_E99C(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA) {
    unkStruct8* temp_r30;
    unkStruct8Sub* temp_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unk0.x += arg8;
            temp_r31->unk0.y += arg9;
            temp_r31->unk0.z += argA;
        }
    }
}

void fn_1_EA24(s16 arg0, f32 arg8, f32 arg9, f32 argA) {
    s32 var_r29;
    unkStruct8* temp_r30;
    unkStruct8Sub* var_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        var_r31 = temp_r30->unk3C;
        
        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unk0.x += arg8;
            var_r31->unk0.y += arg9;
            var_r31->unk0.z += argA;
        }
    }
}

void fn_1_EAB0(s16 arg0, f32 arg8, f32 arg9, f32 argA) {
    unkStruct8* temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        temp_r31->unk18.x = arg8;
        temp_r31->unk18.y = arg9;
        temp_r31->unk18.z = argA;
    }
}

void fn_1_EAF4(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA) {
    unkStruct8* temp_r30;
    unkStruct8Sub* temp_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unkC.x = arg8;
            temp_r31->unkC.y = arg9;
            temp_r31->unkC.z = argA;
        }
    }
}

void fn_1_EB64(s16 arg0, f32 arg8, f32 arg9, f32 argA) {
    s32 var_r29;
    unkStruct8* temp_r30;
    unkStruct8Sub* var_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        var_r31 = temp_r30->unk3C;
        
        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unkC.x = arg8;
            var_r31->unkC.y = arg9;
            var_r31->unkC.z = argA;
        }
    }
}

void fn_1_EBD8(s16 arg0, f32 arg8, f32 arg9, f32 argA) {
    unkStruct8* temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        temp_r31->unk24.x = arg8;
        temp_r31->unk24.y = arg9;
        temp_r31->unk24.z = argA;
    }
}

void fn_1_EC1C(s16 arg0, s16 arg1, f32 arg8, f32 arg9, f32 argA) {
    unkStruct8* temp_r30;
    unkStruct8Sub* temp_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unk18.x = arg8;
            temp_r31->unk18.y = arg9;
            temp_r31->unk18.z = argA;
        }
    }
}

void fn_1_EC8C(s16 arg0, f32 arg8, f32 arg9, f32 argA) {
    s32 var_r29;
    unkStruct8* temp_r30;
    unkStruct8Sub* var_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        var_r31 = temp_r30->unk3C;
        
        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unk18.x = arg8;
            var_r31->unk18.y = arg9;
            var_r31->unk18.z = argA;
        }
    }
}

void fn_1_ED00(s16 arg0, s32 arg1) {
    unkStruct8* temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        temp_r31->unk8 |= arg1;
    }
}

void fn_1_ED44(s16 arg0, s16 arg1, s32 arg2) {
    unkStruct8* temp_r31;
    unkStruct8Sub* temp_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r31->unk2 > arg1) {
            temp_r30 = &temp_r31->unk3C[arg1];
            temp_r30->unk34 |= arg2;
        }
    }
}

void fn_1_EDB4(s16 arg0, s32 arg1) {
    s32 var_r30;
    unkStruct8* temp_r31;
    unkStruct8Sub* temp_r29;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        temp_r29 = temp_r31->unk3C;
        
        for (var_r30 = 0; var_r30 < temp_r31->unk2; var_r30++) {
            temp_r29->unk34 |= arg1;
        }
    }
}

void fn_1_EE24(s16 arg0, u32 arg1) {
    unkStruct8* temp_r31;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        temp_r31->unk8 &= ~arg1;
    }
}

void fn_1_EE68(s16 arg0, s16 arg1, u32 arg2) {
    unkStruct8* temp_r31;
    unkStruct8Sub* temp_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r31->unk2 > arg1) {
            temp_r30 = &temp_r31->unk3C[arg1];
            temp_r30->unk34 &= ~arg2;
        }
    }
}

void fn_1_EED8(s16 arg0, u32 arg1) {
    s32 var_r30;
    unkStruct8* temp_r31;
    unkStruct8Sub* temp_r29;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        temp_r29 = temp_r31->unk3C;
        
        for (var_r30 = 0; var_r30 < temp_r31->unk2; var_r30++) {
            temp_r29->unk34 &= ~arg1;
        }
    }
}

s32 fn_1_EF48(s16 arg0, s32 arg1) {
    unkStruct8* var_r31;

    if (arg0 == 0) {
        return 0;
    }

    var_r31 = &lbl_1_bss_F0.unk10[arg0];
    if ((var_r31->unk8 & arg1) != 0) {
        return 1;
    }
    return 0;
}

s32 fn_1_EFA4(s16 arg0, s16 arg1, s32 arg2) {
    unkStruct8Sub* var_r30;
    unkStruct8* temp_r31;

    if (arg0 == 0) return;
    
    temp_r31 = &lbl_1_bss_F0.unk10[arg0];
    if (temp_r31->unk2 <= arg1) return;
    
    var_r30 = &temp_r31->unk3C[arg1];
    if ((var_r30->unk34 & arg2) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void fn_1_F024(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    unkStruct8* temp_r30;
    unkStruct8Sub* temp_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r30->unk2 > arg1) {
            temp_r31 = &temp_r30->unk3C[arg1];
            temp_r31->unk50.r = arg2;
            temp_r31->unk50.g = arg3;
            temp_r31->unk50.b = arg4;
            temp_r31->unk50.a = arg5;
        }
    }
}

void fn_1_F098(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    s32 var_r29;
    unkStruct8* temp_r30;
    unkStruct8Sub* var_r31;

    if (arg0 != 0) {
        temp_r30 = &lbl_1_bss_F0.unk10[arg0];
        var_r31 = temp_r30->unk3C;
        
        for (var_r29 = 0; var_r29 < temp_r30->unk2; var_r29++, var_r31++) {
            var_r31->unk50.r = arg1;
            var_r31->unk50.g = arg2;
            var_r31->unk50.b = arg3;
            var_r31->unk50.a = arg4;
        }
    }
}

void fn_1_F110(s16 arg0, s16 arg1, u8 arg2) {
    unkStruct8* temp_r31;
    unkStruct8Sub* var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54->unk8 = arg2;
        }
    }
}

void fn_1_F17C(s16 arg0, s16 arg1, u8 arg2, u8 arg3) {
    unkStruct8* temp_r31;
    unkStruct8Sub* var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54[arg2].unk8 = arg3;
        }
    }
}

void fn_1_F1F4(s16 arg0, u8 arg1) {
    s32 var_r28;
    s32 var_r30;
    unkStruct8* temp_r29;
    unkStruct8Sub* var_r31;

    if (arg0 != 0) {
        temp_r29 = &lbl_1_bss_F0.unk10[arg0];
        var_r31 = (unkStruct8Sub *)(&temp_r29->unk3C);
        (void)temp_r29;
        
        for (var_r28 = 0; var_r28 < temp_r29->unk2; var_r28++, var_r31++) {
            for (var_r30 = 0; var_r30 < var_r31->unk32; var_r30++) {
                var_r31->unk54[var_r30].unk8 = arg1;
            }
        }
    }
}

void fn_1_F28C(s16 arg0, s16 arg1, f32 arg8) {
    unkStruct8* temp_r31;
    unkStruct8Sub* var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54->unkC = arg8;
        }
    }
}

void fn_1_F2F8(s16 arg0, s16 arg1, u8 arg2, f32 arg8) {
    unkStruct8* temp_r31;
    unkStruct8Sub* var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54[arg2].unkC = arg8;
        }
    }
}

void fn_1_F370(s16 arg0, f32 arg8) {
    unkStruct8* temp_r31;
    s32 var_r29;
    s32 var_r30;
    unkStruct8Sub* volatile sp8;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        sp8 = &temp_r31->unk3C[0];
        
        for (var_r29 = 0; var_r29 < temp_r31->unk2; var_r29++) {
            for (var_r30 = 0; var_r30 < sp8->unk32; var_r30++) {
                sp8->unk54[var_r30].unkC = arg8;
            }
        }
    }
}

void fn_1_F408(s16 arg0, s16 arg1, u8 arg2) {
    unkStruct8* temp_r31;
    unkStruct8Sub* var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54->unk0 = arg2;
        }
    }
}

void fn_1_F478(s16 arg0, s16 arg1, u8 arg2, u8 arg3) {
    unkStruct8* temp_r31;
    unkStruct8Sub* var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        if (temp_r31->unk2 > arg1) {
            var_r30 = &temp_r31->unk3C[arg1];
            var_r30->unk54[arg2].unk0 = arg3;
        }
    }
}

void fn_1_F4F0(s16 arg0, u8 arg1) {
    unkStruct8Sub* volatile sp8;
    s32 var_r29;
    unkStruct8* temp_r31;
    s32 var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_F0.unk10[arg0];
        sp8 = temp_r31->unk3C;
        for (var_r29 = 0; var_r29 < temp_r31->unk2; var_r29++) {
            for (var_r30 = 0; var_r30 < sp8->unk32; var_r30++) {
                sp8->unk54[var_r30].unk0 = arg1;
            }
        }
    }
}