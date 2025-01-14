#include "REL/m438Dll.h"

#include "ext_math.h"
#include "game/hsfanim.h"
#include "game/wipe.h"

// STRUCT

typedef struct M438MapStruct {
    s32 unk0;
    s32 unk4;
    char unk8[0x4];
    Vec unkC;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} M438MapStruct;

typedef struct M438MapStruct2 {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    Vec unk24;
    Vec unk30;
    Vec unk3C;
    M438MainWork4* unk48;
} M438MapStruct2;

typedef struct M438MapStruct3 {
    u32 unk0;
    M438MapStruct2 unk4;
    char unk4C[0x934];
    M438MapStruct unk984;
} M438MapStruct3;

// BSS
omObjData* lbl_1_bss_108C;
HsfanimStruct01* lbl_1_bss_E34[0x96];
s32 lbl_1_bss_E30;

// DATA
const char* lbl_1_data_848[] = {
    "iwa_s1", "iwa_s2", "iwa_s3", "iwa_s4", "iwa_s5",
    "iwa_s6", "iwa_s7", "iwa_s8", "iwa_s9",
    "iwa_s10", "iwa_s11", "iwa_s12", "iwa_s13",
    "iwa_s14", "iwa_s15", "iwa_s16", "iwa_s17",
    "iwa_s18", "iwa_s19", "iwa_s20", "iwa_s21",
    "iwa_s22", "iwa_s23", "iwa_s24", "iwa_s25",
    "iwa_s26", "iwa_s27", "iwa_s28", "iwa_s29",
    "iwa_s30", "iwa_s31", "iwa_s32"
};

// PROTO
void fn_1_B54C(omObjData*);
void fn_1_D57C(Vec*, f32);
void fn_1_E034(Mtx, Vec*);

void fn_1_B4D8(Process* arg0) {
    omObjData* var_r31;

    lbl_1_bss_E30 = 0;
    var_r31 = lbl_1_bss_108C = omAddObjEx(arg0, 0x20, 8, 0, -1, fn_1_B54C);
    var_r31->work[0] = 0;
}

void fn_1_B548(void) {}

//

Vec lbl_1_data_8D8[4][2] = {
    {
        { -967.0f, -80.0f, -312.0f },
        { -867.0f, -80.0f, -485.0f },
    },
    {
        { -917.0f, -80.0f, -857.0f  },
        { -817.0f, -80.0f, -1030.0f },
    },
    {
        { 967.0f, -80.0f, -312.0f },
        { 867.0f, -80.0f, -485.0f },
    },
    {
        { 917.0f, -80.0f, -857.0f  },
        { 817.0f, -80.0f, -1030.0f },
    },
};

void fn_1_BF20(omObjData* arg0) {
    Mtx sp5C;
    Mtx sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    s32 var_r29;
    M438MapStruct2* var_r31;
    M438MapStruct* var_r30;
    M438MapStruct3* temp_r28;

    temp_r28 = arg0->data;
    temp_r28->unk0++;
    var_r31 = &temp_r28->unk4;
    
    for (var_r29 = 0; var_r29 < 0x20; var_r29++, var_r31++) {
        if ((var_r31->unk0 == 0) && (var_r31->unk4 != 0)) {
            temp_f29 = var_r31->unk30.y;
            PSVECAdd(&var_r31->unk30, &var_r31->unk3C, &var_r31->unk30);
            var_r31->unk3C.x *= 0.92f;
            var_r31->unk3C.z *= 0.92f;
            var_r31->unk3C.y += -0.27222225f;
            if (temp_f29 > 0.0) {
                if (var_r31->unk30.y <= 0.0) {
                    HuAudFXEmiterPlay(0x6FF, &var_r31->unk30);
                }
            }
            var_r31->unkC += var_r31->unk10;
            var_r31->unk14 += var_r31->unk18;
            var_r31->unk1C += var_r31->unk20;
            sp14.x = sind(90.0f + var_r31->unk8);
            sp14.z = cosd(90.0f + var_r31->unk8);
            sp14.y = 0.0f;
            PSMTXRotAxisRad(sp5C, &sp14, MTXDegToRad(var_r31->unkC));
            sp14.x = sp14.z = 0.0f;
            sp14.y = 1.0f;
            PSMTXRotAxisRad(sp2C, &sp14, MTXDegToRad(var_r31->unk14));
            PSMTXConcat(sp2C, sp5C, sp5C);
            sp14.x = sind(var_r31->unk8);
            sp14.z = cosd(var_r31->unk8);
            sp14.y = 0.0f;
            PSMTXRotAxisRad(sp2C, &sp14, MTXDegToRad(var_r31->unk1C));
            PSMTXConcat(sp2C, sp5C, sp5C);
            fn_1_E034(sp5C, &sp20);
            var_r31->unk48->unk_28.x = sp20.x;
            var_r31->unk48->unk_28.y = sp20.y;
            var_r31->unk48->unk_28.z = sp20.z;
            PSMTXInverse(sp5C, sp5C);
            PSMTXMultVec(sp5C, &var_r31->unk24, &sp8);
            var_r31->unk48->unk_1C.x = (var_r31->unk30.x - sp8.x);
            var_r31->unk48->unk_1C.y = (var_r31->unk30.y - sp8.y);
            var_r31->unk48->unk_1C.z = (var_r31->unk30.z - sp8.z);
            if (var_r31->unk30.y < -500.0f) {
                var_r31->unk4 = 0;
            }
        }
    }
    if ((temp_r28->unk0 & 1) == 0) {
        var_r30 = &temp_r28->unk984;
        
        for (var_r29 = 0; var_r29 < 0x32; var_r29++, var_r30++) {
            if (var_r30->unk0 != 0) continue;
            var_r30->unk0 = 1;
            var_r30->unk18 = frandmod(0x168);
            if (frandmod(0x64) < 0x14) {
                var_r30->unkC.x = (0.8f * (frandmod(0x7D0) - 0x3E8));
                var_r30->unkC.y = -80.0f;
                var_r30->unkC.z = ((-1.2f * frandmod(0x3E8)) - 1000.0f);
            } else {
                temp_f31 = frandmod(0x168);
                temp_f30 = 800.0f + (0.25f * frandmod(0x3E8));
                var_r30->unkC.x = (temp_f30 * sind(temp_f31));
                var_r30->unkC.y = -80.0f;
                var_r30->unkC.z = (temp_f30 * cosd(temp_f31));
            }
            var_r30->unk20 = (0.1f + (0.0005f * frandmod(0x3E8)));
            var_r30->unk1C = 0.0f;
            Hu3DModelAttrReset(var_r30->unk4, 1);
            Hu3DModelPosSetV(var_r30->unk4, &var_r30->unkC);
            Hu3DModelRotSet(var_r30->unk4, 0.0f, var_r30->unk18, 0.0f);
            Hu3DModelScaleSet(var_r30->unk4, var_r30->unk1C, var_r30->unk1C, var_r30->unk1C);
            break;
        }
    }
    var_r30 = &temp_r28->unk984;
    for (var_r29 = 0; var_r29 < 0x32; var_r29++, var_r30++) {
        if (var_r30->unk0 != 0) {
            var_r30->unk1C += 0.005f;
            if (var_r30->unk1C > var_r30->unk20) {
                var_r30->unk0 = 0;
                Hu3DModelAttrSet(var_r30->unk4, 1);
                fn_1_D57C(&Hu3DData[var_r30->unk4].pos, var_r30->unk20);
            }
            Hu3DModelScaleSet(var_r30->unk4, var_r30->unk1C, var_r30->unk1C, var_r30->unk1C);
        }
    }
    
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        PSVECSubtract(&lbl_1_data_8D8[var_r29][1], &lbl_1_data_8D8[var_r29][0], &sp14);
        temp_f31 = 0.001f * frandmod(0x3E8);
        PSVECScale(&sp14, &sp14, temp_f31);
        PSVECAdd(&lbl_1_data_8D8[var_r29][0], &sp14, &sp8);
        PSVECScale(&sp8, &sp8, 0.98f);
        fn_1_D57C(&sp8, 0.03f);
    }
    if ((lbl_1_bss_E30 == 0) && (WipeStatGet() == 0)) {
        HuAudFXPlay(0x6F9);
        HuAudFXPlay(0x6FD);
        lbl_1_bss_E30 = 1;
    }
}

void fn_1_C764(ModelData* model, ParticleData* particle, Mtx matrix) {
    HsfanimStruct01* var_r31;
    s32 var_r29;
    u16 temp_r0;

    var_r31 = particle->unk_48;
    
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00_s16 != 0) {
            PSVECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            var_r31->unk08.x *= 0.95f;
            var_r31->unk08.z *= 0.95f;
            var_r31->unk08.y += -0.27222225f;
            if (var_r31->unk00_s16 < 24.0f) {
                var_r31->unk40.a = 0.9f * var_r31->unk40.a;
            }
            if (--var_r31->unk00_s16 == 0) {
                var_r31->unk00 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * 0x44);
}

void fn_1_C8E8(ModelData* model, ParticleData* particle, Mtx matrix) {
    HsfanimStruct01* var_r31;
    s32 var_r29;
    u16 temp_r0;

    var_r31 = particle->unk_48;
    
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00_s16 != 0) {
            PSVECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            var_r31->unk08.x *= 0.95f;
            var_r31->unk08.z *= 0.95f;
            var_r31->unk2C += -0.27222225f;
                var_r31->unk40.a *= 0.99f;
            if (var_r31->unk00_s16 < 24.0f) {
                var_r31->unk40.a = 0.9f * var_r31->unk40.a;
            }
            if (--var_r31->unk00_s16 == 0) {
                var_r31->unk00 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * 0x44);
}
