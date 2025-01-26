#include "REL/mstory3Dll.h"
#include "game/data.h"
#include "game/hsfanim.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/sprite.h"

#include "ext_math.h"

#define frand5() (((s32)frand() & 0x1F))
#define frand8() (((s32)frand() & 0xFF))

typedef struct {
    /* 0x00 */ Vec* unk00;
    /* 0x04 */ Vec unk04;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ u16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ float unk24;
    /* 0x28 */ AnimData* unk28;
} StructBss1CF8; // Size 0x2C

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x1A];
    /* 0x1C */ StructBss1CF8* unk1C;
} StructFn1E13C; // Size unknown

void fn_1_1E13C(s32 arg0, s32 arg1, StructBss1CF8* arg2, Vec* arg3);
void fn_1_1E558(void);
void fn_1_1E820(ModelData* model, ParticleData* particle, Mtx matrix);

StructBss1CF8 lbl_1_bss_1CF8[2];
s32 lbl_1_bss_1CF4;
s32 lbl_1_bss_1CF0;
s32 lbl_1_bss_1CEC;
s16 lbl_1_bss_1CE8;

void fn_1_1DED8(s32 arg0, Vec* arg1, Vec* arg2, s16 arg3) {
    AnimData* temp_r28;
    s16 var_r27;

    fn_1_1E13C(arg0 + 1, arg0 + 3, &lbl_1_bss_1CF8[0], arg2);
    lbl_1_bss_1CF8[0].unk04 = *arg1;
    lbl_1_bss_1CF8[0].unk24 = arg3 - 20;
    fn_1_1E13C(arg0 + 2, arg0 + 3, &lbl_1_bss_1CF8[1], arg2);
    lbl_1_bss_1CF8[1].unk04 = *arg1;
    lbl_1_bss_1CF8[1].unk24 = arg3 - 20;
    temp_r28 = HuSprAnimReadFile(arg0);
    lbl_1_bss_1CE8 = HuSprGrpCreate(1);
    var_r27 = HuSprCreate(temp_r28, 0, 0);
    HuSprGrpMemberSet(lbl_1_bss_1CE8, 0, var_r27);
    HuSprPosSet(lbl_1_bss_1CE8, 0, arg2->x, arg2->y);
    HuSprTPLvlSet(lbl_1_bss_1CE8, 0, 0.0f);
    HuSprAttrSet(lbl_1_bss_1CE8, 0, 8);
    HuPrcChildCreate(fn_1_1E558, 100, 0x2000, 0, HuPrcCurrentGet());
    lbl_1_bss_1CF4 = 0;
    lbl_1_bss_1CF0 = 0;
    lbl_1_bss_1CEC = 0;
}

void fn_1_1E0F4(void) {
    lbl_1_bss_1CF4 = 1;
}

s32 fn_1_1E108(void) {
    return lbl_1_bss_1CF0;
}

void fn_1_1E118(void) {
    lbl_1_bss_1CEC = 1;
}

s32 fn_1_1E12C(void) {
    return lbl_1_bss_1CE8;
}

void fn_1_1E13C(s32 arg0, s32 arg1, StructBss1CF8* arg2, Vec* arg3) {
    Vec sp14;
    AnimBmpData* temp_r31;
    s32 sp10;
    s32 var_r27;
    s32 var_r26;
    u16* var_r25;
    AnimData* var_r24;
    Vec* var_r22;
    StructFn1E13C* temp_r23;
    s16 var_r29;
    s16 var_r28;

    var_r24 = HuSprAnimReadFile(arg0);
    arg2->unk28 = var_r24;
    temp_r31 = var_r24->bmp;
    sp10 = temp_r31->sizeX * temp_r31->sizeY;
    var_r25 = temp_r31->data;
    for (var_r28 = var_r26 = 0; var_r28 < temp_r31->sizeY; var_r28 += 2) {
        for (var_r29 = 0; var_r29 < temp_r31->sizeX; var_r29 += 2) {
            var_r25 = (u16*) temp_r31->data + ((var_r28 % 4) * 4 + (var_r28 / 4) * temp_r31->sizeX * 4 + (var_r29 / 4) * 16 + var_r29 % 4);
            if (*var_r25 != 0x8000) {
                var_r26++;
            }
        }
    }
    arg2->unk20 = var_r26;
    var_r22 = arg2->unk00 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r26 * sizeof(*var_r22), MEMORY_DEFAULT_NUM);
    arg2->unk1C = temp_r31->sizeX;
    arg2->unk1E = temp_r31->sizeY;
    Hu3D2Dto3D(arg3, 1, &arg2->unk10);
    for (var_r28 = 0; var_r28 < temp_r31->sizeY; var_r28 += 2) {
        for (var_r29 = 0; var_r29 < temp_r31->sizeX; var_r29 += 2) {
            var_r25 = (u16*) temp_r31->data + ((var_r28 % 4) * 4 + (var_r28 / 4) * temp_r31->sizeX * 4 + (var_r29 / 4) * 16 + var_r29 % 4);
            if (*var_r25 != 0x8000) {
                sp14 = *arg3;
                sp14.x = sp14.x + var_r29 - temp_r31->sizeX / 2;
                sp14.y = sp14.y + var_r28 - temp_r31->sizeY / 2;
                Hu3D2Dto3D(&sp14, 1, var_r22);
                var_r22++;
            }
        }
    }
    HuSprAnimKill(var_r24);
    var_r24 = HuSprAnimRead(HuDataRead(arg1));
    var_r27 = Hu3DParticleCreate(var_r24, var_r26);
    arg2->unk22 = var_r27;
    Hu3DModelPosSet(var_r27, 0.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet(var_r27, 1);
    Hu3DParticleColSet(var_r27, 0xFF, 0xFF, 0xA);
    Hu3DParticleScaleSet(var_r27, 20.0f);
    Hu3DParticleHookSet(var_r27, fn_1_1E820);
    Hu3DParticleBlendModeSet(var_r27, 1);
    Hu3DParticleAttrSet(var_r27, 2);
    temp_r23 = Hu3DData[var_r27].unk_120;
    temp_r23->unk1C = arg2;
    temp_r23->unk00 = 0;
    OSReport("Particle Count %d\n", var_r26);
}

void fn_1_1E558(void) {
    float var_f31;
    float var_f30;
    float temp_f29;
    s16* temp_r30;
    s16* temp_r29;
    s16 i;

    var_f31 = 0.0f;
    var_f30 = 0.0f;
    while (lbl_1_bss_1CF4 == 0) {
        HuPrcVSleep();
    }
    Hu3DParticleAttrReset(lbl_1_bss_1CF8->unk22, 2);
    HuPrcSleep(20);
    Hu3DParticleAttrReset(lbl_1_bss_1CF8[1].unk22, 2);
    temp_r30 = Hu3DData[lbl_1_bss_1CF8[0].unk22].unk_120;
    temp_r29 = Hu3DData[lbl_1_bss_1CF8[1].unk22].unk_120;
    while (*temp_r30 == 0 || *temp_r29 == 0) {
        HuPrcVSleep();
    }
    for (i = 0; i <= 20; i++) {
        temp_f29 = i / 20.0f;
        HuSprTPLvlSet(lbl_1_bss_1CE8, 0, temp_f29);
        HuPrcVSleep();
    }
    OSReport("Finish\n");
    for (i = 0; i < 2; i++) {
        Hu3DModelKill(lbl_1_bss_1CF8[i].unk22);
        HuSprAnimKill(lbl_1_bss_1CF8[i].unk28);
    }
    lbl_1_bss_1CF0 = 1;
    while (TRUE) {
        if (lbl_1_bss_1CEC != 0) {
            break;
        }
        var_f31 += var_f30;
        if (var_f31 > 360.0f) {
            var_f31 -= 360.0f;
        }
        var_f30 += 0.5;
        if (var_f30 > 10.0f) {
            var_f30 = 10.0f;
        }
        temp_f29 = 1.0 + 0.25 * sind(var_f31);
        HuSprScaleSet(lbl_1_bss_1CE8, 0, temp_f29, temp_f29);
        HuPrcVSleep();
    }
    HuSprGrpKill(lbl_1_bss_1CE8);
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_1E820(ModelData* model, ParticleData* particle, Mtx matrix) {
    Vec sp8;
    float temp_f30;
    float temp_f31;
    s16 var_r22;
    s16 var_r29;
    StructBss1CF8* temp_r28;
    HsfanimStruct01* var_r31;
    s16 var_r27;
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r21;
    s16 temp_r26;
    s16 temp_r20;
    s16 var_r23;

    temp_r28 = particle->unk_1C;
    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            var_r31->unk2C = 0.0f;
        }
    }
    if (particle->unk_2D & 2) {
        return;
    }
    temp_r21 = temp_r28->unk24 - (temp_r28->unk24 / 5.0f);
    temp_r26 = temp_r21 / 2;
    temp_r20 = temp_r21 - temp_r26;
    PSVECSubtract(&temp_r28->unk04, &temp_r28->unk10, &sp8);
    temp_f31 = PSVECMag(&sp8) / temp_r20;
    for (var_r22 = 0; var_r22 < particle->unk_30 / (temp_r28->unk24 / 5.0f); var_r22++) {
        var_r31 = particle->unk_48;
        for (var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
            if (!var_r31->unk2C) {
                break;
            }
        }
        if (var_r29 == particle->unk_30) {
            break;
        }
        var_r31->unk34 = temp_r28->unk04;
        var_r27 = (frand8() * 360) >> 8;
        temp_f30 = 0.2 * frand5();
        var_r31->unk08.x = temp_f30 * sind(var_r27);
        var_r31->unk08.y = 0.1 * (frand5() + 100);
        var_r31->unk08.z = temp_f30 * cosd(var_r27);
        var_r31->unk40.r = 0xF0;
        var_r31->unk40.g = 0x80;
        var_r31->unk40.b = 0x60;
        var_r31->unk2C = 10.0f;
        var_r31->unk00 = 0;
        var_r31->unk02 = 0;
        var_r31->unk14.x = frandmod(360);
    }
    var_r31 = particle->unk_48;
    for (var_r29 = var_r23 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (!var_r31->unk2C) {
            continue;
        }
        if (var_r31->unk00 == 0) {
            PSVECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
            var_r31->unk08.x *= 0.999f;
            var_r31->unk08.y -= 0.5f;
            var_r31->unk08.z *= 0.999f;
            if (var_r31->unk02 > temp_r26 - (temp_r26 / 5.0)) {
                PSVECScale(&var_r31->unk08, &var_r31->unk08, 1.0 - ((var_r31->unk02 - (temp_r26 - temp_r26 / 5.0)) / (temp_r26 / 5.0)));
            }
            if (var_r31->unk02 == temp_r26) {
                var_r31->unk00++;
            }
            if (var_r31->unk34.y <= 0.0f) {
                var_r31->unk08.y = 0.5f * -var_r31->unk08.y;
                var_r31->unk34.y = 0.0f;
            }
        } else if (var_r31->unk00 == 1) {
            sp8 = temp_r28->unk00[var_r29];
            PSVECSubtract(&sp8, &var_r31->unk34, &sp8);
            if (PSVECMag(&sp8) <= 1.0 + temp_f31) {
                var_r23++;
                var_r31->unk34 = temp_r28->unk00[var_r29];
                var_r31->unk00++;
                continue;
            }
            PSVECNormalize(&sp8, &sp8);
            var_r31->unk08.x = sp8.x * temp_f31 + sind(var_r31->unk14.x);
            var_r31->unk08.y = sp8.y * temp_f31;
            var_r31->unk08.z = sp8.z * temp_f31;
            PSVECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
            var_r31->unk14.x += 20.0f;
        } else {
            var_r23++;
        }
        if (var_r31->unk00 >= 1) {
            var_r27 = var_r31->unk40.r;
            var_r27 += (var_r27 - 0xFF) / 20;
            if (var_r27 > 0xFF) {
                var_r31->unk40.r = 0xFF;
            } else {
                var_r31->unk40.r = var_r27;
            }
            temp_r25 = var_r31->unk40.g;
            temp_r25 += (temp_r25 - 0xFF) / 20;
            if (temp_r25 > 0xFF) {
                var_r31->unk40.g = 0xFF;
            } else {
                var_r31->unk40.g = temp_r25;
            }
            temp_r24 = var_r31->unk40.b;
            temp_r24 += (temp_r24 - 0x80) / 20;
            if (temp_r24 > 0x80) {
                var_r31->unk40.b = 0x80;
            } else {
                var_r31->unk40.b = temp_r24;
            }
        }
        var_r31->unk2C -= 0.2f;
        if (var_r31->unk2C < 5.0f) {
            var_r31->unk2C = 5.0f;
        }
        var_r31->unk02++;
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
    if (var_r23 >= particle->unk_30) {
        particle->unk_00++;
    }
}
