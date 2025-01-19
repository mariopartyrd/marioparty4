#include "REL/m438Dll.h"

#include "game/hsfdraw.h"

extern u8 texMtxTbl;

// PROTO
void fn_1_E790(M438UnkStruct2*);
void fn_1_F538(ModelData*, Mtx);
void fn_1_FAB8(M438UnkStruct*);
void fn_1_FD40(M438UnkStruct2*);
void fn_1_10F0C(s16);

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

void fn_1_FD40(M438UnkStruct2* arg0) {
    M438UnkStruct* var_r28;
    M438UnkStruct3* temp_r30;
    M438UnkSubStruct* var_r31;
    s32 temp_r0;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;

    var_r27 = 0;
    
    var_r28 = arg0->unk_3C;
    for (var_r25 = 0; var_r25 < arg0->unk_02; var_r25++, var_r28++) {
        if ((var_r28->unk_38 & 4) != 0) {
            var_r27++;
        } else {
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
                    } else if ((var_r31->unk_24 & 0x40) != 0) {
                        var_r31->unk_24 = (var_r31->unk_24 & 0xF0) | 2;
                        var_r31->unk_00 -= 2;
                    } else if ((var_r31->unk_24 & 0x20) != 0) {
                        var_r31->unk_00 = 0;
                    }
                    var_r31->unk_24 |= 4;
                } else if (var_r31->unk_00 < 0) {
                    if ((var_r31->unk_24 & 0x10) != 0) {
                        var_r31->unk_24 |= 8;
                        var_r31->unk_00 = 0;
                    } else if ((var_r31->unk_24 & 0x20) != 0) {
                        if ((var_r31->unk_24 & 0x40) != 0) {
                            var_r31->unk_24 = (var_r31->unk_24 & 0xF0) | 1;
                            var_r31->unk_00 = 1;
                        } else {
                            var_r31->unk_00 = temp_r30->unk_4C - 1;
                        }
                    } else if ((var_r31->unk_24 & 0x40) != 0) {
                        var_r31->unk_24 |= 8;
                        var_r31->unk_00 = 0;
                    }
                    var_r31->unk_24 |= 4;
                } else {
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
                            } else {
                                var_r31->unk_00 = 0;
                            }
                        }
                    } else if ((var_r28->unk_38 & 0x80000000) != 0) {
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
        } else if ((arg0->unk_08 & 0x80000000) != 0) {
            fn_1_107BC(arg0->unk_00);
        }
    }
    PPCSync();
}

s16 fn_1_10258(u8 arg0, u8 arg1) {
    M438UnkStruct* var_r30;
    M438UnkStruct2* var_r31;
    s32 var_r29;
    s32 var_r28;
    void* temp_r25;

    var_r31 = &lbl_1_bss_DE4.unk_40[1];
    
    for (var_r29 = 1; var_r29 < lbl_1_bss_DE4.unk_30; var_r29++, var_r31++) {
        if (var_r31->unk_08 == 0) break;
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
        var_r30->unk_40 = ((char*)var_r31->unk_4C) + var_r31->unk_48;
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
        var_r30->unk_40 = ((char*)var_r31->unk_4C) + var_r31->unk_48;
        var_r31->unk_48 += var_r30->unk_3C;
    }
    lbl_1_bss_DE4.unk_36 = var_r31->unk_00;
    lbl_1_bss_DE4.unk_38 = 0;
    lbl_1_bss_DE4.unk_3A = 0;
    PPCSync();
    return var_r31->unk_00;
}

void fn_1_107BC(s16 arg0) {
    M438UnkStruct2* temp_r31;
    s32 var_r30;

    if (arg0 != 0) {
        temp_r31 = &lbl_1_bss_DE4.unk_40[arg0];
        if ((u32) temp_r31->unk_08 != 0) {
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

void fn_1_108E4(s16 arg0, s16 arg1, u8 arg2) {
    lbl_1_bss_DE4.unk_36 = arg0;
    lbl_1_bss_DE4.unk_38 = arg1;
    lbl_1_bss_DE4.unk_3A = arg2;
}

#include "game/sprite.h"

s16 fn_1_10910(u32 arg0, s16 arg1, s16 arg2) {
    f32 var_f31;
    f32 var_f30;
    AnimData* var_r30;
    M438UnkStruct3* var_r31;
    s32 var_r29;

    var_r31 = &lbl_1_bss_DE4.unk_3C[1];
    for (var_r29 = 1; var_r29 < lbl_1_bss_DE4.unk_32; var_r29++, var_r31++) {
        if ((var_r31->unk_06 != 0) && (var_r31->unk_08 == arg0)) break;
    }
    if (var_r29 < lbl_1_bss_DE4.unk_32) {
        var_r31->unk_06++;
        return var_r29;
    }
    
    var_r31 = &lbl_1_bss_DE4.unk_3C[1];
    for (var_r29 = 1; var_r29 < lbl_1_bss_DE4.unk_32; var_r29++, var_r31++) {
        if (var_r31->unk_06 == 0) break;
    }
    var_r31->unk_08 = arg0;
    var_r31->unk_06 = 1;
    if (((arg0 & 0xFFFF0000) + 0x10000) == 0) {
        var_r30 = HuSprAnimMake(arg1, arg2, 2);
        var_r30->bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, arg2 * (arg1 * 2), 0x10000000);
        arg1 = arg2 = 0;
    } else {
        var_r30 = HuSprAnimRead(HuDataReadNum(arg0, 0x10000000));
    }
    if ((arg1 == 0) || (arg2 == 0)) {
        arg1 = var_r30->bmp->sizeX;
        arg2 = var_r30->bmp->sizeY;
        var_f31 = var_f30 = 1.0f;
    } else {
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
    PSMTXIdentity(var_r31->unk_18);
    var_r31->unk_0C.x = var_r31->unk_0C.y = var_r31->unk_0C.z = 0.0f;
    return var_r29;
}

void fn_1_10CB8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    f32 var_f31;
    f32 var_f30;
    M438UnkStruct3* temp_r31;
    AnimData* temp_r30;

    temp_r31 = &lbl_1_bss_DE4.unk_3C[arg0];
    HuSprAnimKill(temp_r31->unk_00);
    temp_r31->unk_08 |= 0xFFFF0000;
    temp_r30 = HuSprAnimMake(arg2, arg3, arg1);
    temp_r30->bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, arg3 * (temp_r30->bmp->pixSize * arg2), 0x10000000U);
    var_f31 = arg4 / (f32) temp_r30->bmp->sizeX;
    var_f30 = arg5 / (f32) temp_r30->bmp->sizeY;
    temp_r31->unk_00 = temp_r30;
    temp_r31->unk_4E = arg2;
    temp_r31->unk_50 = arg3;
    temp_r31->unk_54 = var_f31;
    temp_r31->unk_58 = var_f30;
    temp_r31->unk_5C = 1.0f / (f32) temp_r30->bmp->sizeX;
    temp_r31->unk_60 = 1.0f / (f32) temp_r30->bmp->sizeY;
    temp_r31->unk_04 = 0;
    temp_r31->unk_4C = temp_r30->bmp->sizeY / arg5;
    temp_r31->unk_4D = 0;
    temp_r31->unk_48.r = temp_r31->unk_48.g = temp_r31->unk_48.b = 0xFF;
    temp_r31->unk_48.a = 0xFF;
}
