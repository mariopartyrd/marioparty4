#include "REL/m438Dll.h"

#include "ext_math.h"
#include "game/hsfanim.h"
#include "game/hsfmotion.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "string.h"


// STRUCT
typedef struct M438MapStruct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
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
    union {
        M438MainWork4 *unk48;
        HsfObject *unk48o;
    };
} M438MapStruct2;

typedef struct M438MapStruct3 {
    u32 unk0;
    M438MapStruct2 unk4;
    char unk4C[0x934];
    M438MapStruct unk984;
} M438MapStruct3;

// BSS
omObjData *lbl_1_bss_108C[6];
HsfanimStruct01 *lbl_1_bss_E34[0x96];
s32 lbl_1_bss_E30;
s32 lbl_1_bss_E2C;
s32 lbl_1_bss_E28;

// DATA
char *lbl_1_data_848[] = { "iwa_s1", "iwa_s2", "iwa_s3", "iwa_s4", "iwa_s5", "iwa_s6", "iwa_s7", "iwa_s8", "iwa_s9", "iwa_s10", "iwa_s11", "iwa_s12",
    "iwa_s13", "iwa_s14", "iwa_s15", "iwa_s16", "iwa_s17", "iwa_s18", "iwa_s19", "iwa_s20", "iwa_s21", "iwa_s22", "iwa_s23", "iwa_s24", "iwa_s25",
    "iwa_s26", "iwa_s27", "iwa_s28", "iwa_s29", "iwa_s30", "iwa_s31", "iwa_s32" };

// PROTO
void fn_1_B54C(omObjData *);
void fn_1_BF20(omObjData *);
void fn_1_CAB0(f32);
void fn_1_C764(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_C8E8(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_D3FC(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_D57C(Vec *, f32);
void fn_1_E034(Mtx, Vec *);

void fn_1_B4D8(Process *arg0)
{
    omObjData *var_r31;

    lbl_1_bss_E30 = 0;
    var_r31 = lbl_1_bss_108C[0] = omAddObjEx(arg0, 0x20, 8, 0, -1, fn_1_B54C);
    var_r31->work[0] = 0;
}

void fn_1_B548(void) { }

void fn_1_B54C(omObjData *arg0)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 var_r30;
    s32 var_r29;
    HsfObject *var_r26;
    s32 var_r27;
    M438MapStruct2 *var_r28;
    HsfanimStruct01 *var_r25;
    M438MapStruct *var_r24;
    M438MapStruct3 *temp_r23;

    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x108C, 0x10000000);
    temp_r23 = arg0->data;
    memset(temp_r23, 0, 0x108C);
    arg0->model[0] = Hu3DModelCreateFile(0x450000);
    Hu3DModelLayerSet(arg0->model[0], 0);
    Hu3DModelAttrSet(arg0->model[0], 0x40000001);
    Hu3DModelShadowMapSet(arg0->model[0]);
    arg0->model[1] = Hu3DModelCreateFile(0x450001);
    Hu3DModelLayerSet(arg0->model[1], 1);
    Hu3DModelPosSet(arg0->model[1], 0.0f, -80.0f, 0.0f);
    arg0->model[2] = Hu3DModelCreateFile(0x450002);
    Hu3DModelLayerSet(arg0->model[2], 0);
    Hu3DModelPosSet(arg0->model[2], 0.0f, -50.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[2], 0x40000001);
    Hu3DMotionSpeedSet(arg0->model[2], 0.1f);
    var_r29 = Hu3DTexScrollCreate(arg0->model[1], "lavafall");
    Hu3DTexScrollPosMoveSet(var_r29, 0.0f, -0.025000002f, 0.0f);
    var_r29 = Hu3DTexScrollCreate(arg0->model[1], "lafall");
    Hu3DTexScrollPosMoveSet(var_r29, 0.0f, -(1.0f / 60.0f), 0.0f);
    var_r29 = 0;
  
    var_r27 = Hu3DParticleCreate(HuSprAnimReadFile(0x45000C), 0x32);
    arg0->model[3] = var_r27;
    Hu3DModelLayerSet(var_r27, 3);
    Hu3DParticleHookSet(var_r27, fn_1_C764);
    for (var_r30 = 0; var_r30 < 0x32; var_r30++, var_r29++) {
        lbl_1_bss_E34[var_r29] = &((ParticleData *)(Hu3DData[var_r27].unk_120))->unk_48[var_r30];
    }

    var_r27 = Hu3DParticleCreate(HuSprAnimReadFile(0x45000D), 0x32);
    arg0->model[4] = var_r27;
    Hu3DModelLayerSet(var_r27, 3);
    Hu3DParticleHookSet(var_r27, fn_1_C764);
    for (var_r30 = 0; var_r30 < 0x32; var_r30++, var_r29++) {
        lbl_1_bss_E34[var_r29] = &((ParticleData *)(Hu3DData[var_r27].unk_120))->unk_48[var_r30];
    }

    var_r27 = Hu3DParticleCreate(HuSprAnimReadFile(0x45000E), 0x32);
    arg0->model[5] = var_r27;
    Hu3DModelLayerSet(var_r27, 3);
    Hu3DParticleHookSet(var_r27, fn_1_C764);
    for (var_r30 = 0; var_r30 < 0x32; var_r30++, var_r29++) {
        lbl_1_bss_E34[var_r29] = &((ParticleData *)(Hu3DData[var_r27].unk_120))->unk_48[var_r30];
    }
    for (var_r30 = 0; var_r30 < 0x95; var_r30++) {
        for (var_r29 = 1; var_r29 < 0x96; var_r29++) {
            if (frandmod(0x3E8) < 0x1C2) {
                var_r25 = lbl_1_bss_E34[var_r30];
                lbl_1_bss_E34[var_r30] = lbl_1_bss_E34[var_r29];
                lbl_1_bss_E34[var_r29] = var_r25;
            }
        }
    }

    for (var_r30 = 0; var_r30 < 0x96; var_r30++) {
        lbl_1_bss_E34[var_r30]->unk2C = 0.0f;
        lbl_1_bss_E34[var_r30]->unk40.a = 0;
        lbl_1_bss_E34[var_r30]->unk00 = 0;
    }
  
    var_r27 = Hu3DParticleCreate(HuSprAnimReadFile(0x45000F), 0x32);
    arg0->model[6] = var_r27;
    Hu3DModelLayerSet(var_r27, 3);
    Hu3DParticleHookSet(var_r27, fn_1_C8E8);
    var_r25 = &((ParticleData *)(Hu3DData[var_r27].unk_120))->unk_48[0];
    for (var_r30 = 0; var_r30 < 0x32; var_r30++, var_r25++) {
        var_r25->unk2C = 0.0f;
        var_r25->unk40.a = 0;
        var_r25->unk00 = 0;
    }
  
    var_r27 = Hu3DParticleCreate(HuSprAnimReadFile(0x450010), 0x1F4);
    arg0->model[7] = var_r27;
    Hu3DModelLayerSet(var_r27, 2);
    Hu3DParticleBlendModeSet(var_r27, 1);
    Hu3DParticleHookSet(var_r27, fn_1_D3FC);
    var_r25 = &((ParticleData *)(Hu3DData[var_r27].unk_120))->unk_48[0];
    for (var_r30 = 0; var_r30 < 0x1F4; var_r30++, var_r25++) {
        var_r25->unk2C = 0.0f;
        var_r25->unk40.a = 0;
        var_r25->unk00 = 0;
    }
    var_r28 = &temp_r23->unk4;
    for (var_r30 = 0; var_r30 < 0x20; var_r30++, var_r28++) {
        var_r28->unk0 = 1;
        var_r28->unk4 = 0;
        var_r28->unkC = var_r28->unk10 = 0.0f;
        var_r28->unk14 = var_r28->unk18 = 0.0f;
        var_r28->unk1C = var_r28->unk20 = 0.0f;
        var_r26 = Hu3DModelObjPtrGet(arg0->model[0], lbl_1_data_848[var_r30]);
        var_r28->unk48o = var_r26;
        sp14.x = sp14.y = sp14.z = -100000.0f;
        sp8.x = sp8.y = sp8.z = 100000.0f;

        for (var_r29 = 0; var_r29 < var_r26->data.vertex->count; var_r29++) {
            if (((Vec *)var_r26->data.vertex->data)[var_r29].x > sp14.x) {
                sp14.x = ((Vec *)var_r26->data.vertex->data)[var_r29].x;
            }
            if (((Vec *)var_r26->data.vertex->data)[var_r29].y > sp14.y) {
                sp14.y = ((Vec *)var_r26->data.vertex->data)[var_r29].y;
            }
            if (((Vec *)var_r26->data.vertex->data)[var_r29].z > sp14.z) {
                sp14.z = ((Vec *)var_r26->data.vertex->data)[var_r29].z;
            }
            if (((Vec *)var_r26->data.vertex->data)[var_r29].x < sp8.x) {
                sp8.x = ((Vec *)var_r26->data.vertex->data)[var_r29].x;
            }
            if (((Vec *)var_r26->data.vertex->data)[var_r29].y < sp8.y) {
                sp8.y = ((Vec *)var_r26->data.vertex->data)[var_r29].y;
            }
            if (((Vec *)var_r26->data.vertex->data)[var_r29].z < sp8.z) {
                sp8.z = ((Vec *)var_r26->data.vertex->data)[var_r29].z;
            }
        }
        VECAdd(&sp14, &sp8, &sp20);
        VECScale(&sp20, &sp20, 0.5f);
        var_r28->unk24 = sp20;
        var_r28->unk30 = var_r28->unk24;
        var_r28->unk8 = (360.0 + atan2d(sp20.x, sp20.z));
        if (var_r28->unk8 >= 360.0f) {
            var_r28->unk8 -= 360.0f;
        }
    }
    var_r27 = Hu3DModelCreateFile(0x45000B);
    Hu3DModelLayerSet(var_r27, 2);
    var_r24 = &temp_r23->unk984;
    for (var_r30 = 0; var_r30 < 0x32; var_r30++, var_r24++) {
        var_r24->unk0 = 0;
        var_r24->unk8 = 0;
        var_r24->unk18 = 0.0f;
        var_r24->unk1C = var_r24->unk20 = 0.0f;
        var_r24->unk4 = Hu3DModelLink(var_r27);
        Hu3DModelLayerSet(var_r24->unk4, 2);
        Hu3DModelAttrSet(var_r24->unk4, 1);
    }
    Hu3DModelKill(var_r27);
    arg0->func = fn_1_BF20;
}

Vec lbl_1_data_8D8[4][2] = {
    {
        { -967.0f, -80.0f, -312.0f },
        { -867.0f, -80.0f, -485.0f },
    },
    {
        { -917.0f, -80.0f, -857.0f },
        { -817.0f, -80.0f, -1030.0f },
    },
    {
        { 967.0f, -80.0f, -312.0f },
        { 867.0f, -80.0f, -485.0f },
    },
    {
        { 917.0f, -80.0f, -857.0f },
        { 817.0f, -80.0f, -1030.0f },
    },
};

void fn_1_BF20(omObjData *arg0)
{
    Mtx sp5C;
    Mtx sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    s32 var_r29;
    M438MapStruct2 *var_r31;
    M438MapStruct *var_r30;
    M438MapStruct3 *temp_r28;

    temp_r28 = arg0->data;
    temp_r28->unk0++;
    var_r31 = &temp_r28->unk4;

    for (var_r29 = 0; var_r29 < 0x20; var_r29++, var_r31++) {
        if ((var_r31->unk0 == 0) && (var_r31->unk4 != 0)) {
            temp_f29 = var_r31->unk30.y;
            VECAdd(&var_r31->unk30, &var_r31->unk3C, &var_r31->unk30);
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
            MTXRotAxisRad(sp5C, &sp14, MTXDegToRad(var_r31->unkC));
            sp14.x = sp14.z = 0.0f;
            sp14.y = 1.0f;
            MTXRotAxisRad(sp2C, &sp14, MTXDegToRad(var_r31->unk14));
            MTXConcat(sp2C, sp5C, sp5C);
            sp14.x = sind(var_r31->unk8);
            sp14.z = cosd(var_r31->unk8);
            sp14.y = 0.0f;
            MTXRotAxisRad(sp2C, &sp14, MTXDegToRad(var_r31->unk1C));
            MTXConcat(sp2C, sp5C, sp5C);
            fn_1_E034(sp5C, &sp20);
            var_r31->unk48->unk_28.x = sp20.x;
            var_r31->unk48->unk_28.y = sp20.y;
            var_r31->unk48->unk_28.z = sp20.z;
            MTXInverse(sp5C, sp5C);
            MTXMultVec(sp5C, &var_r31->unk24, &sp8);
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
            if (var_r30->unk0 != 0)
                continue;
            var_r30->unk0 = 1;
            var_r30->unk18 = frandmod(0x168);
            if (frandmod(0x64) < 0x14) {
                var_r30->unkC.x = (0.8f * (frandmod(0x7D0) - 0x3E8));
                var_r30->unkC.y = -80.0f;
                var_r30->unkC.z = ((-1.2f * frandmod(0x3E8)) - 1000.0f);
            }
            else {
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
        VECSubtract(&lbl_1_data_8D8[var_r29][1], &lbl_1_data_8D8[var_r29][0], &sp14);
        temp_f31 = 0.001f * frandmod(0x3E8);
        VECScale(&sp14, &sp14, temp_f31);
        VECAdd(&lbl_1_data_8D8[var_r29][0], &sp14, &sp8);
        VECScale(&sp8, &sp8, 0.98f);
        fn_1_D57C(&sp8, 0.03f);
    }
    if ((lbl_1_bss_E30 == 0) && (WipeStatGet() == 0)) {
        HuAudFXPlay(0x6F9);
        HuAudFXPlay(0x6FD);
        lbl_1_bss_E30 = 1;
    }
}

void fn_1_C764(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    s32 var_r29;
    u16 temp_r0;

    var_r31 = particle->unk_48;

    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00 != 0) {
            VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            var_r31->unk08.x *= 0.95f;
            var_r31->unk08.z *= 0.95f;
            var_r31->unk08.y += -0.27222225f;
            if (var_r31->unk00 < 24.0f) {
                var_r31->unk40.a = 0.9f * var_r31->unk40.a;
            }
            if (--var_r31->unk00 == 0) {
                var_r31->unk00 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * 0x44);
}

void fn_1_C8E8(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    s32 var_r29;
    u16 temp_r0;

    var_r31 = particle->unk_48;

    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00 != 0) {
            VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            var_r31->unk08.x *= 0.92f;
            var_r31->unk08.z *= 0.92f;
            var_r31->unk2C += 5.0f;
            var_r31->unk40.a *= 0.99f;
            if (var_r31->unk00 < 24.0f) {
                var_r31->unk40.a = 0.9f * var_r31->unk40.a;
            }
            if (--var_r31->unk00 == 0) {
                var_r31->unk00 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * 0x44);
}

void fn_1_CAB0(f32 arg8)
{
    Vec sp8;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f28;
    f32 temp_f27;
    HsfanimStruct01 *var_r31;
    s32 var_r30;
    u32 var_r29;

    temp_f28 = 20.0f;
    temp_f27 = 7.0f;
    var_r29 = 0x19;
  
    for (var_r30 = 0; var_r30 < 0x96; var_r30++) {
        var_r31 = lbl_1_bss_E34[var_r30];
        if (var_r31->unk00 == 0) {
            var_r31->unk00 = 60.0f * (0.6f + (0.0006f * frandmod(0x3E8)));
            temp_f31 = ((0.002f * frandmod(0x3E8)) - 1.0f);
            temp_f31 = arg8 + (temp_f31 * temp_f28);
            sp8.x = sind(temp_f31);
            sp8.y = 0.0f;
            sp8.z = cosd(temp_f31);
          
            temp_f31 = arg8 + (((0.002f * frandmod(0x3E8)) - 1.0f)) * temp_f27;
            var_r31->unk34.x = 7.5 * sind(temp_f31) * 100.0;
            var_r31->unk34.y = 0.2f * frandmod(0x3E8);
            var_r31->unk34.z = 7.5 * cosd(temp_f31) * 100.0;
          
            temp_f30 = 1.6666667f * (4.0f + (0.014f * frandmod(0x3E8)));
            var_r31->unk08.x = sp8.x * temp_f30;
            var_r31->unk08.z = sp8.z * temp_f30;
            var_r31->unk08.y = temp_f30 * ((0.0006f * frandmod(0x3E8)) - 0.2f);

            var_r31->unk30 = frandmod(0x168);
            var_r31->unk2C = 10.0f + frandmod(0x32);
            var_r31->unk40.a = 0xFA;
            var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = 0xFF;

            var_r29--;
            if (var_r29 < 1)
                break;
        }
    }
    var_r31 = ((ParticleData *)(Hu3DData[lbl_1_bss_108C[0]->model[6]].unk_120))->unk_48;
    var_r29 = 0xF;
    for (var_r30 = 0; var_r30 < 0x32; var_r30++, var_r31++) {
        if (var_r31->unk00 == 0) {
            var_r31->unk00 = 60.0f * (0.6f + (0.0006f * frandmod(0x3E8)));
            temp_f31 = ((0.002f * frandmod(0x3E8)) - 1.0f);
            temp_f31 = arg8 + (temp_f31 * temp_f28);
            sp8.x = sind(temp_f31);
            sp8.y = 0.0f;
            sp8.z = cosd(temp_f31);
          
            temp_f31 = arg8 + (((0.002f * frandmod(0x3E8)) - 1.0f)) * temp_f27;
            var_r31->unk34.x = 7.5 * sind(temp_f31) * 100.0;
            var_r31->unk34.y = 0.2f * frandmod(0x3E8);
            var_r31->unk34.z = 7.5 * cosd(temp_f31) * 100.0;
          
            temp_f30 = 1.6666667f * -(0.01f * frandmod(0x3E8));
            var_r31->unk08.x = sp8.x * temp_f30;
            var_r31->unk08.z = sp8.z * temp_f30;
            var_r31->unk08.y = temp_f30 * -((0.00020000001f * frandmod(0x3E8)) + 0.05f);

            var_r31->unk30 = frandmod(0x168);
            var_r31->unk2C = 100.0f + frandmod(0x64);
            var_r31->unk40.a = 0x50 + frandmod(0x50);
            temp_f31 = frandmod(0x3E8) * 0.001f;
            var_r31->unk40.r = (60.0f * temp_f31) + 80.0f;
            var_r31->unk40.g = (60.0f * temp_f31) + 61.0f;
            var_r31->unk40.b = (60.0f * temp_f31) + 54.0f;

            var_r29--;
            if (var_r29 < 1)
                break;
        }
    }
}

void fn_1_D3FC(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    s32 var_r29;
    u16 temp_r0;

    lbl_1_bss_E2C = 0;
    var_r31 = particle->unk_48;
    for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00 != 0) {
            VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            var_r31->unk08.y += -0.27222225f;
            if (var_r31->unk00 < 12.0f) {
                var_r31->unk40.a = (0.8f * var_r31->unk40.a);
            }
            if (--var_r31->unk00 == 0) {
                var_r31->unk00 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
            lbl_1_bss_E2C++;
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * 0x44);
}

void fn_1_D57C(Vec *arg0, f32 arg1)
{
    Vec sp8;
    f32 temp_f31;
    f32 temp_f29;
    HsfanimStruct01 *var_r31;
    s32 var_r30;
    u32 var_r29;

    var_r31 = ((ParticleData *)(Hu3DData[lbl_1_bss_108C[0]->model[7]].unk_120))->unk_48;
    var_r29 = (u32)(3.0f + (15.0f * arg1));

    for (var_r30 = 0; var_r30 < 0x1F4; var_r30++, var_r31++) {
        if (var_r31->unk00 == 0) {
            var_r31->unk00 = 60.0f * (0.3f + (0.0003f * frandmod(0x3E8)));
            var_r31->unk34 = *arg0;
            var_r31->unk34.x += arg1 * (0.07f * (frandmod(0x3E8) - 0x1F4));
            var_r31->unk34.z += arg1 * (0.07f * (frandmod(0x3E8) - 0x1F4));

            temp_f31 = frandmod(0x168);
            sp8.x = sind(temp_f31);
            sp8.y = 0.0f;
            sp8.z = cosd(temp_f31);

            temp_f29 = 1.6666667f * (0.5f + (0.001f * frandmod(0x3E8)));
            var_r31->unk08.x = sp8.x * temp_f29;
            var_r31->unk08.z = sp8.z * temp_f29;
            var_r31->unk08.y = 1.6666667f * ((2.0f * arg1) + (1.0f + (0.002f * frandmod(0x3E8))));
            var_r31->unk30 = frandmod(0x168);
            var_r31->unk2C = (20.0f + frandmod(0x14));
            var_r31->unk40.a = (frandmod(0x46) + 0x64);

            temp_f31 = 0.001f * frandmod(0x3E8);
            var_r31->unk40.r = 177.0f + (78.0f * temp_f31);
            var_r31->unk40.g = 60.0f + (129.0f * temp_f31);
            var_r31->unk40.b = 30.0f + (122.0f * temp_f31);

            var_r29--;
            if (var_r29 < 1)
                break;
        }
    }
}

s32 fn_1_DA64(f32 arg8)
{
    M438MapStruct3 *var_r28;
    s32 var_r29;
    s32 var_r30;
    M438MapStruct2 *var_r31;
    float var_f31;
    float var_f29;

    var_r28 = lbl_1_bss_108C[0]->data;
    var_r29 = 0;
    var_r31 = &var_r28->unk4;
  
    for (var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        var_f31 = fn_1_E5A4(var_r31->unk8, arg8);
        if ((fabs(var_f31) < 12.0) && (var_r31->unk0 != 0)) {
            var_r31->unk0 = 0;
            var_r31->unk4 = 1;
            var_r31->unk30 = var_r31->unk24;
            var_r31->unk3C.y = (1.6666667f * (2.0f + (0.002f * frandmod(0x3E8))));
            var_r31->unk3C.x = (1.6666667461395264f * (sind(var_r31->unk8) * (10.0f + (0.006f * frandmod(0x3E8)))));
            var_r31->unk3C.z = (1.6666667461395264f * (cosd(var_r31->unk8) * (10.0f + (0.006f * frandmod(0x3E8)))));
            var_r31->unkC = var_r31->unk14 = var_r31->unk1C = 0.0f;
            var_r31->unk10 = (0.016666668f * (10.0f + (0.05f * frandmod(0x3E8))));
            var_r31->unk18 = (0.016666668f * (30.0f + (0.05f * frandmod(0x3E8))));
            var_r31->unk20 = (0.016666668f * (10.0f + (0.02f * frandmod(0x3E8))));
            if (frandmod(0x64) < 0x50) {
                var_r31->unk10 *= -1.0f;
            }
            if (frandmod(0x64) < 0x32) {
                var_r31->unk18 *= -1.0f;
            }
            if (frandmod(0x64) < 0x32) {
                var_r31->unk20 *= -1.0f;
            }
            fn_1_CAB0(var_r31->unk8);
            var_r29 = 1;
        }
    }
    return var_r29;
}

s32 fn_1_DEA0(f32 arg8)
{
    M438MapStruct3 *var_r28;
    s32 var_r29;
    s32 var_r30;
    M438MapStruct2 *var_r31;
    f32 var_f31;

    var_r28 = lbl_1_bss_108C[0]->data;
    var_r29 = 0;
    var_r31 = &var_r28->unk4;
  
    for (var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        var_f31 = fn_1_E5A4(var_r31->unk8, arg8);
        if ((fabs(var_f31) < 8.0) && (var_r31->unk0 != 0)) {
            var_r29 = 1;
            break;
        }
    }
    return var_r29;
}

f32 fn_1_DF70(f32 arg8, f32 arg9)
{
    f32 temp_f30;
    f32 var_f31;

    temp_f30 = 360.0f;
    var_f31 = 180.0 * (atan2f(arg9, arg8) / M_PI);
    if (var_f31 < 0.0f) {
        var_f31 += temp_f30;
      
    }
    else if (var_f31 >= temp_f30) {
        var_f31 -= temp_f30;
    }
    return var_f31;
}

void fn_1_E034(Mtx arg0, Vec *arg1)
{
    f32 var_f26;
    f32 temp_f25;

    arg1->x = fn_1_DF70(arg0[2][2], arg0[1][2]);
    arg1->z = fn_1_DF70(arg0[0][0], arg0[0][1]);
    temp_f25 = -arg0[0][2];
    var_f26 = sqrtf(fabs(1.0 - (temp_f25 * temp_f25)));
    if ((arg1->x > 90.0f) && (arg1->x < 270.0f) && (arg1->z > 90.0f) && (arg1->z < 270.0f)) {
        arg1->x = fmod((180.0f + arg1->x), 360.0);
        arg1->z = fmod((180.0f + arg1->z), 360.0);
        var_f26 = -var_f26;
    }
    arg1->y = fn_1_DF70(var_f26, temp_f25);
}

f32 fn_1_E488(f32 arg8, f32 arg9, f32 argA)
{
    f32 var_f31;

    var_f31 = fmodf((arg9 - arg8), 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f31 = fmodf((arg8 + (argA * var_f31)), 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    return var_f31;
}

f32 fn_1_E5A4(f32 arg8, f32 arg9)
{
    f32 var_f31;

    var_f31 = fmodf((arg9 - arg8), 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}
