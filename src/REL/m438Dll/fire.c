#include "REL/m438Dll.h"

#include "game/hsfdraw.h"

extern u8 texMtxTbl;

typedef struct M438FireStruct {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    Vec unk24;
} M438FireStruct;

typedef struct M438FireStruct2 {
    GXColor unk0;
    GXColor unk4;
    GXColor unk8;
    GXColor unkC;
} M438FireStruct2;

typedef struct M438FireStruct3 {
    HsfVector2f unk0;
    HsfVector2f unk8;
    HsfVector2f unk10;
    HsfVector2f unk18;
} M438FireStruct3;

// PROTO
void fn_1_E790(M438UnkStruct2*);
void fn_1_F538(ModelData*, Mtx);
void fn_1_FD40(M438UnkStruct2*);

void fn_1_E658(s16 arg0, s16 arg1) {
    M438UnkStruct2* var_r29;
    s32 var_r31;
    M438UnkStruct3* var_r30;

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

void fn_1_F538(ModelData* arg0, Mtx arg1) {
    Mtx sp38;
    Mtx sp8;
    M438UnkStruct2* var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_DE4.unk_40;
    GXLoadPosMtxImm(arg1, 0);
    PSMTXInverse(arg1, sp38);
    PSMTXTranspose(sp38, sp8);
    GXLoadNrmMtxImm(sp8, 0);
    HmfInverseMtxF3X3(Hu3DCameraMtx, lbl_1_bss_DE4.unk_00);
    
    for (var_r30 = 0; var_r30 < lbl_1_bss_DE4.unk_30; var_r30++, var_r31++) {
        if ((var_r31->unk_08 != 0) && ((var_r31->unk_08 & 2) != 0) && ((var_r31->unk_08 & 4) == 0)) {
            if ((u8)omPauseChk() == 0) {
                if (var_r31->unk_30) {
                    var_r31->unk_30(var_r31);
                }
                if (var_r31->unk_08 == 0) continue;
                fn_1_FD40(var_r31);
                if (var_r31->unk_08 == 0) continue;
            }
            fn_1_E790(var_r31);
        }
    }
}

M438UnkStruct2* fn_1_F664(s16 arg0) {
    return &lbl_1_bss_DE4.unk_40[arg0];
}

M438UnkStruct* fn_1_F680(s16 arg0, s16 arg1) {
    return &lbl_1_bss_DE4.unk_40[arg0].unk_3C[arg1];
}

M438UnkStruct3* fn_1_F6AC(s16 arg0) {
    return &lbl_1_bss_DE4.unk_3C[arg0];
}

void fn_1_F6C8(M438FireStruct** arg0, s16 arg1, f32 arg8, f32 arg9) {
    s32 var_r30;
    M438FireStruct* var_r31;

    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(M438FireStruct), 0x10000000);
    
    for (var_r30 = 0; var_r30 < arg1; var_r31++, var_r30++) {
        var_r31->unk0.x  = (-0.5f * arg8);
        var_r31->unk0.y  = (0.5f * arg9);
        var_r31->unk0.z  = 0.0f;
        var_r31->unkC.x  = (0.5f * arg8);
        var_r31->unkC.y  = (0.5f * arg9);
        var_r31->unkC.z  = 0.0f;
        var_r31->unk18.x = (0.5f * arg8);
        var_r31->unk18.y = (-0.5f * arg9);
        var_r31->unk18.z = 0.0f;
        var_r31->unk24.x = (-0.5f * arg8);
        var_r31->unk24.y = (-0.5f * arg9);
        var_r31->unk24.z = 0.0f;
    }
}

void fn_1_F84C(M438FireStruct** arg0, s16 arg1, Vec* arg2) {
    Vec* var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r31 = (Vec*)*arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(M438FireStruct), 0x10000000);
    
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
            var_r31->z = arg2->z;
        }
    }
}

void fn_1_F8EC(M438FireStruct2** arg0, s16 arg1, GXColor* arg2) {
    GXColor* var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r31 = (GXColor*)*arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(M438FireStruct2), 0x10000000U);
    
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->r = arg2->r;
            var_r31->g = arg2->g;
            var_r31->b = arg2->b;
            var_r31->a = arg2->a;
        }
    }
}

void fn_1_F994(Vec** arg0, s16 arg1, Vec* arg2) {
    s32 var_r29;
    Vec* var_r31;
    
    var_r31 = *arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(Vec), 0x10000000);
    
    for (var_r29 = 0; var_r29 < arg1; var_r31++, arg2++, var_r29++) {
        var_r31->x = arg2->x;
        var_r31->y = arg2->y;
        var_r31->z = arg2->z;
    }
}

void fn_1_FA20(M438FireStruct3** arg0, s16 arg1, HsfVector2f* arg2) {
    HsfVector2f* var_r31;
    s32 var_r29;
    s32 var_r28;
    
    var_r31 = (HsfVector2f*)*arg0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg1 * sizeof(M438FireStruct3), 0x10000000);
    
    for (var_r29 = 0; var_r29 < arg1; var_r29++) {
        for (var_r28 = 0; var_r28 < 4; var_r31++, arg2++, var_r28++) {
            var_r31->x = arg2->x;
            var_r31->y = arg2->y;
        }
    }
}

void fn_1_FAB8(M438UnkStruct* arg0) {
    Vec sp1C[4] = {
        { -50.0f,  50.0f, 0.0f },
        {  50.0f,  50.0f, 0.0f },
        {  50.0f, -50.0f, 0.0f },
        { -50.0f, -50.0f, 0.0f }
    };
    GXColor spC[4] = {
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF }
    };
    
    void* sp8;
    s32 var_r31;
    s32 var_r29;
    void* temp_r28;
    
    
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
