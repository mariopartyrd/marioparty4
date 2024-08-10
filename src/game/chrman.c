#include "game/chrman.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/process.h"
#include "game/sprite.h"

#include "ext_math.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C[32];
    /* 0x4C */ s16 unk4C[32];
    /* 0x8C */ u8 unk8C[32];
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ s8 unkB0;
    /* 0xB1 */ char unkB1[3];
    /* 0xB4 */ Vec unkB4;
    /* 0xC0 */ void *unkC0;
    /* 0xC4 */ Process *unkC4;
} UnkCharInstanceStruct; // Size 0xC8

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 unk08;
} EffectData; // Size 0xC

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ u8 unk08;
    /* 0x09 */ u8 unk09;
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ char unk0B[1];
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ s32 unk28; // unknown type
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
} EffectParamData; // Size 0x38

typedef struct {
    u16 unk00;
    s16 unk02;
} UnkProcessData; // Size 4

static void UpdateChar(void);
static void UpdateCharAnim(s16 character, s16 arg1, s16 arg2, u8 arg3, s16 arg4, Vec *arg5);
static s32 PlayCharVoice(s16 character, s16 arg1, u8 arg2);
static void InitEffect(void);
static s16 CreateEffectDust(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5);
static s16 CreateEffectSmoke(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5);
static s16 CreateEffectDot(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5);
static s16 CreateEffectStar(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5);
static s16 CreateEffectWarn(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5);
static s16 CreateEffectBird(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5);
static s16 CreateEffect(s16 arg0, s16 arg1, float arg2, float arg3, float arg4, float arg5, EffectParamData *arg6);
static void UpdateEffect(ModelData *model, ParticleData *particle, Mtx matrix);
static void RotateEffect(HsfanimStruct01 *arg0);
static void PlayEffectSound(HsfanimStruct01 *arg0);
static void UpdateItemHook(void);
static void OrbitEffect(HsfanimStruct01 *arg0);
static void UpdateNpcEffect(void);
static s32 PlayStepFX(s16 arg0, s16 arg1, u8 arg2);

static UnkCharInstanceStruct charInstance[8];
static s16 effectMdl[8];
static EffectParamData *particleData[8];
static Process *itemHookProcess[32];
static u16 lbl_801975B0[8];
static u8 lbl_801975C0[0x90]; // Unused?

static s32 skipAnimUpdate;
static void *effectAMemP;

static u8 lbl_801D35F0[8] = { 0x0C, 0x00, 0x17, 0x75, 0x1E, 0x1E, 0x1D, 0x18 };
static u8 lbl_801D35F8[8] = { 0x0D, 0x00, 0x17, 0x54, 0x1E, 0x00, 0x00, 0x23 };
static u8 lbl_801D3600[8] = { 0x0A, 0x00, 0x19, 0x63, 0x26, 0x00, 0x10, 0x0F };
static u8 lbl_801D3608[8] = { 0x0D, 0x00, 0x17, 0x69, 0x0D, 0x1E, 0x1D, 0x14 };
static u8 lbl_801D3610[8] = { 0x15, 0x1E, 0x16, 0x54, 0x0F, 0x62, 0x39, 0x0A };

static EffectData effectDataTbl[8] = {
    { 0x00120006, 0x000A, 0x0000, 0x00000002 },
    { 0x00120005, 0x000A, 0x0000, 0x00000002 },
    { 0x00120002, 0x0096, 0x0001, 0x00000000 },
    { 0x00120003, 0x0046, 0x0000, 0x00000000 },
    { 0x00120000, 0x012C, 0x0001, 0x00000000 },
    { 0x00120001, 0x012C, 0x0001, 0x00000000 },
    { 0x00120004, 0x00C8, 0x0001, 0x00000000 },
    { 0x00120007, 0x000C, 0x0000, 0x00000002 }
};

static s32 charDirTbl[8][3] = {
    { 0x005D0000, 0x005E0000, 0x005F0000 },
    { 0x00180000, 0x00190000, 0x001A0000 },
    { 0x006B0000, 0x006C0000, 0x006D0000 },
    { 0x00880000, 0x00890000, 0x008A0000 },
    { 0x00830000, 0x00840000, 0x00850000 },
    { 0x000F0000, 0x00100000, 0x00110000 },
    { 0x000B0000, 0x000C0000, 0x000D0000 },
    { 0x007F0000, 0x00800000, 0x00810000 }
};

static EffectParamData effectDustParam = {
    0,
    0x80, 0x80, 0x80, 0xFF,
    0x40, 0x20, 0x00, 0xFF,
    { 0.0f, 2.0f, 1.0f },
    0.95f, 0.95f, 0.95f,
    0.0f,
    0x00000000,
    1.0f,
    -5.0f,
    0.02f
};

static EffectParamData effectDotParam = {
    0,
    0xFF, 0x40, 0x40, 0x80,
    0xFF, 0x40, 0x40, 0x80,
    { 0.0f, 0.0f, 0.0f },
    0.0f, 0.0f, 0.0f,
    0.0f,
    0x00000000,
    -5.0f,
    0.0f,
    0.0f
};

static EffectParamData effectStarParam = {
    0,
    0xFF, 0xFF, 0x00, 0xFF,
    0xFF, 0xFF, 0x00, 0xFF,
    { 0.0f, 0.0f, 0.0f },
    0.95f, 0.95f, 0.95f,
    0.0f,
    0x00000000,
    -0.5f,
    -10.0f,
    0.0f
};

static EffectParamData effectWarnParam = {
    0,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    { 0.0f, 20.0f, 0.0f },
    0.95f, 0.85f, 0.95f,
    0.0f,
    0x00000000,
    1.0f,
    -5.0f,
    0.0f
};

static EffectParamData effectSmokeParam = {
    0,
    0x80, 0x20, 0x20, 0xFF,
    0x00, 0x00, 0x00, 0xFF,
    { 0.0f, 10.0f, 0.0f },
    1.0f, 0.95f, 1.0f,
    0.0f,
    0x00000000,
    5.0f,
    -13.0f,
    0.1f
};

static s8 lbl_801309A0[32] = {
    10, 32, -1, -1,
    20, 40, -1, -1,
    12, 37, -1, -1,
     4, 25, -1, -1,
     5, 30, -1, -1,
    16,  1, 24, 39,
    23, 50, -1, -1,
    19, 39, -1, -1
};

static s8 lbl_801309C0[32] = {
    15, 29, -1, -1,
     5, 19, -1, -1,
     5, 22, -1, -1,
    12, 28, -1, -1,
    18, 35, -1, -1,
     1,  8, 12, -1,
     0, 16, -1, -1,
    12, 28, -1, -1
};

static s8 lbl_801309E0[16] = {
     5,  7,  6,  9,
    10, 11,  9, -1,
     9, 11,  9, -1,
     8, -1, 10, -1
};

void CharManInit(void) {
    UnkCharInstanceStruct *temp_r29;
    s16 i;
    s16 j;

    for (i = 0; i < 8; i++) {
        temp_r29 = &charInstance[i];
        temp_r29->unkC0 = NULL;
        for (j = 0; j < 32; j++) {
            temp_r29->unk0C[j] = -1;
        }
        temp_r29->unk00 = -1;
        temp_r29->unkC4 = NULL;
    }
    if (!effectAMemP) {
        effectAMemP = (void*) HuAR_DVDtoARAM(0x120000);
    }
    for (i = 0; i < 8; i++) {
        effectMdl[i] = -1;
        particleData[i] = NULL;
    }
    for (i = 0; i < 32; i++) {
        itemHookProcess[i] = NULL;
    }
}

void *CharAMemPtrGet(s16 character) {
    return charInstance[character].unkC0;
}

void CharARAMOpen(s16 character) {
    UnkCharInstanceStruct *temp_r31;

    if (character >= 8 || character < 0 || character == 0xFF) {
        return;
    }
    temp_r31 = &charInstance[character];
    if (!temp_r31->unkC0) {
        temp_r31->unkC0 = (void*) HuAR_DVDtoARAM(charDirTbl[character][2]);
    }
}

void CharARAMClose(s16 character) {
    UnkCharInstanceStruct *temp_r31;

    temp_r31 = &charInstance[character];
    if (temp_r31->unkC0) {
        HuARFree((u32) temp_r31->unkC0);
        temp_r31->unkC0 = NULL;
    }
}

void CharKill(s16 character) {
    s16 i;

    if (character == -1) {
        for (i = 0; i < 8; i++) {
            CharKill(i);
        }
    } else {
        HuDataDirClose(charDirTbl[character][0]);
        HuDataDirClose(charDirTbl[character][1]);
        HuDataDirClose(charDirTbl[character][2]);
        CharARAMClose(character);
    }
}

void CharKillAll(void) {
    CharModelKill(-1);
    CharKill(-1);
    HuARFree((u32) effectAMemP);
    effectAMemP = NULL;
}

s16 CharModelCreate(s16 character, s16 lod) {
    s16 sp8 = 0;
    UnkCharInstanceStruct *temp_r31;
    void *var_r26;
    s16 *var_r27;
    s16 var_r25;
    s32 var_r29;

    temp_r31 = &charInstance[character];
    if (temp_r31->unk00 != -1) {
        Hu3DModelKill(temp_r31->unk00);
    }
    if (lod & 1) {
        var_r29 = charDirTbl[character][0];
    } else if (lod & 2) {
        var_r29 = charDirTbl[character][1];
    } else if (lod & 4) {
        var_r29 = charDirTbl[character][1] | 1;
    } else {
        var_r29 = charDirTbl[character][1] | 2;
    }
    var_r26 = HuDataSelHeapReadNum(var_r29, MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r31->unk00 = var_r25 = Hu3DModelCreate(var_r26);
    temp_r31->unkC4 = HuPrcCreate(UpdateChar, 0x64, 0x4000, 0);
    temp_r31->unkC4->user_data = var_r27 = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s16));
    temp_r31->unk02 = lod;
    temp_r31->unkAC = 0;
    *var_r27 = character;
    temp_r31->unkB0 = 0;
    InitEffect();
    return var_r25;
}

static void UpdateChar(void) {
    Vec sp8;
    s16 *temp_r28;
    UnkCharInstanceStruct *temp_r31;
    ModelData *temp_r29;
    s16 var_r27;
    s16 i;

    temp_r28 = HuPrcCurrentGet()->user_data;
    temp_r31 = &charInstance[*temp_r28];
    temp_r29 = &Hu3DData[temp_r31->unk00];
    var_r27 = 0;
    while (1) {
        for (i = 0; i < 32; i++) {
            if (temp_r31->unk0C[i] == temp_r29->unk_08) {
                break;
            }
        }
        skipAnimUpdate = 0;
        if (i != 32) {
            temp_r31->unk04 = temp_r31->unk4C[i];
            UpdateCharAnim(*temp_r28, temp_r31->unk00, temp_r31->unk4C[i], temp_r31->unk8C[i], temp_r29->unk_64, &sp8);
            temp_r31->unk08 = temp_r31->unk4C[i];
        } else {
            temp_r31->unk04 = -1;
        }
        if (temp_r29->unk_0C != -1) {
            for (i = 0; i < 32; i++) {
                if (temp_r31->unk0C[i] == temp_r29->unk_0C) {
                    break;
                }
            }
            skipAnimUpdate = 1;
            var_r27 = 1;
            if (i != 32) {
                temp_r31->unk06 = temp_r31->unk4C[i];
                UpdateCharAnim(*temp_r28, temp_r31->unk00, temp_r31->unk4C[i], temp_r31->unk8C[i], temp_r29->unk_84, &sp8);
                temp_r31->unk0A = temp_r31->unk4C[i];
            } else {
                temp_r31->unk06 = -1;
            }
        } else if (var_r27 != 0) {
            CharModelTexAnimSet(*temp_r28);
            var_r27 = 0;
        }
        temp_r31->unkB4 = temp_r29->pos;
        HuPrcVSleep();
    }
}

static void UpdateCharAnim(s16 character, s16 arg1, s16 arg2, u8 arg3, s16 arg4, Vec *arg5) {
    Vec sp1C;
    Vec sp10;
    ModelData *temp_r30;
    s16 var_r19;
    ParticleData *var_r18;
    ModelData *var_r17;
    HsfanimStruct01 *var_r27;
    UnkCharInstanceStruct *temp_r29;
    Mtx sp28;
    u32 var_r22;
    s16 var_r20;
    s16 i;

    temp_r30 = &Hu3DData[arg1];
    temp_r29 = &charInstance[character];
    var_r22 = 0;
    if (skipAnimUpdate == 0 && (temp_r30->motion_attr & 0x40000002)) {
        return;
    }
    switch (arg2) {
        case 2:
            if (skipAnimUpdate == 0 && temp_r30->unk_68 <= 0.5) {
                break;
            }
            if (skipAnimUpdate != 0 && temp_r30->unk_88 <= 0.5) {
                break;
            }
            if (!(arg4 & 0xF) && !(temp_r29->unkAC & 0x10)) {
                effectDustParam.unk0C.x = 2.0 * -sind(temp_r30->rot.y);
                effectDustParam.unk0C.y = 1.0 + 0.1 * frandmod(10);
                effectDustParam.unk0C.z = 2.0 * -cosd(temp_r30->rot.y);
                sp1C.x = temp_r30->pos.x + temp_r30->scale.x * (frandmod(50) - 25);
                sp1C.y = temp_r30->pos.y;
                sp1C.z = temp_r30->pos.z + temp_r30->scale.x * (frandmod(50) - 25);
                CreateEffectDust(arg1, sp1C.x, sp1C.y, sp1C.z, frandmod(10) + 30, &effectDustParam);
            }
            for (i = 0; i < 4; i++) {
                if (lbl_801309A0[character * 4 + i] == arg4) {
                    PlayStepFX(character, 0x101, arg3);
                    break;
                }
            }
            break;
        case 3:
            if (skipAnimUpdate == 0 && temp_r30->unk_68 <= 0.5) {
                break;
            }
            if (skipAnimUpdate != 0 && temp_r30->unk_88 <= 0.5) {
                break;
            }
            if (!(arg4 & 3) && !(temp_r29->unkAC & 0x10)) {
                effectDustParam.unk0C.x = 4.0 * -sind(temp_r30->rot.y);
                effectDustParam.unk0C.y = 2.0 + 0.1 * frandmod(10);
                effectDustParam.unk0C.z = 4.0 * -cosd(temp_r30->rot.y);
                sp1C.x = temp_r30->pos.x + temp_r30->scale.x * (frandmod(50) - 25);
                sp1C.y = temp_r30->pos.y;
                sp1C.z = temp_r30->pos.z + temp_r30->scale.x * (frandmod(50) - 25);
                CreateEffectDust(arg1, sp1C.x, sp1C.y, sp1C.z, frandmod(10) + 30, &effectDustParam);
            }
            for (i = 0; i < 4; i++) {
                if (lbl_801309C0[character * 4 + i] == arg4) {
                    PlayStepFX(character, 0x105, arg3);
                    break;
                }
            }
            break;
        case 4:
            if (arg4 < 5 && !(temp_r29->unkAC & 0x10)) {
                effectDustParam.unk0C.x = 6.0 * sind(temp_r30->rot.y);
                effectDustParam.unk0C.z = 6.0 * cosd(temp_r30->rot.y);
                for (i = 0; i < 5; i++) {
                    effectDustParam.unk0C.y = 2.0 + 0.1 * frandmod(10);
                    sp1C.x = temp_r30->pos.x + temp_r30->scale.x * (frandmod(50) - 25);
                    sp1C.y = temp_r30->pos.y;
                    sp1C.z = temp_r30->pos.z + temp_r30->scale.x * (frandmod(50) - 25);
                    CreateEffectDust(arg1, sp1C.x, sp1C.y, sp1C.z, 20.0f, &effectDustParam);
                }
            }
            if (arg4 == 0) {
                PlayStepFX(character, 0x10D, arg3);
            }
            break;
        case 6:
            if (arg4 == 5 && !(temp_r29->unkAC & 0x10)) {
                for (i = 0; i < 8; i++) {
                    effectDustParam.unk0C.x = 4.0 * sind(45.0f * i) * temp_r30->scale.x;
                    effectDustParam.unk0C.y = 0.0f;
                    effectDustParam.unk0C.z = 4.0 * cosd(45.0f * i) * temp_r30->scale.x;
                    CreateEffectDust(arg1, temp_r30->pos.x, temp_r30->pos.y + 10.0f * temp_r30->scale.x, temp_r30->pos.z, 20.0f, &effectDustParam);
                }
                for (i = 0; i < 8; i++) {
                    effectDustParam.unk0C.x = 2.0 * sind(45.0f * i + 22.5) * temp_r30->scale.x;
                    effectDustParam.unk0C.y = 0.0f;
                    effectDustParam.unk0C.z = 2.0 * cosd(45.0f * i + 22.5) * temp_r30->scale.x;
                    CreateEffectDust(arg1, temp_r30->pos.x, temp_r30->pos.y + 10.0f * temp_r30->scale.x, temp_r30->pos.z, 20.0f, &effectDustParam);
                }
            }
            for (i = 0; i < 2; i++) {
                if (lbl_801309E0[character * 2 + i] == arg4) {
                    PlayStepFX(character, 0x10D, arg3);
                    break;
                }
            }
            break;
        case 7:
            if (arg2 == 7) {
                Hu3DModelObjMtxGet(arg1, CharModelHookNameGet(character, temp_r29->unk02, 0), sp28);
                var_r20 = 10;
            } else {
                Hu3DModelObjMtxGet(arg1, CharModelHookNameGet(character, temp_r29->unk02, 1), sp28);
                var_r20 = 13;
            }
            if (arg4 <= var_r20 && !(temp_r29->unkAC & 0x10)) {
                effectDotParam.unk0C.x = 0.0f;
                effectDotParam.unk0C.y = 0.0f;
                effectDotParam.unk0C.z = 0.0f;
                effectDotParam.unk2C = -5.0f;
                sp1C.x = sp28[0][3];
                sp1C.y = sp28[1][3];
                sp1C.z = sp28[2][3];
                if (arg4 != 0) {
                    PSVECSubtract(&sp1C, arg5, &sp10);
                    var_r20 = 0.2 * sqrtf(sp10.x * sp10.x + sp10.y * sp10.y + sp10.z * sp10.z);
                    if (var_r20 > 5) {
                        var_r20 = 5;
                    }
                    if (var_r20 < 1) {
                        var_r20 = 1;
                    }
                    for (i = 1; i <= var_r20; i++) {
                        sp10.x = arg5->x + (sp1C.x - arg5->x) * ((float) i / var_r20);
                        sp10.y = arg5->y + (sp1C.y - arg5->y) * ((float) i / var_r20);
                        sp10.z = arg5->z + (sp1C.z - arg5->z) * ((float) i / var_r20);
                        CreateEffectDot(arg1, sp10.x, sp10.y, sp10.z, 50.0f, &effectDotParam);
                    }
                } else {
                    CreateEffectDot(arg1, sp1C.x, sp1C.y, sp1C.z, 40.0f, &effectDotParam);
                }
                *arg5 = sp1C;
            }
            break;
        case 0xA:
            if (arg4 == 0) {
                if (!(temp_r29->unkAC & 0x10)) {
                    for (i = 0; i < 8; i++) {
                        effectStarParam.unk0C.x = 10.0 * sind(45.0f * i) * temp_r30->scale.x;
                        effectStarParam.unk0C.y = 0.0f;
                        effectStarParam.unk0C.z = 10.0 * cosd(45.0f * i) * temp_r30->scale.x;
                        CreateEffectStar(arg1, temp_r30->pos.x, temp_r30->pos.y + 10.0f * temp_r30->scale.x, temp_r30->pos.z, 40.0f, &effectStarParam);
                    }
                    for (i = 0; i < 8; i++) {
                        effectDustParam.unk0C.x = 4.0 * sind(45.0f * i + 22.5) * temp_r30->scale.x;
                        effectDustParam.unk0C.y = 0.0f;
                        effectDustParam.unk0C.z = 4.0 * cosd(45.0f * i + 22.5) * temp_r30->scale.x;
                        CreateEffectDust(arg1, temp_r30->pos.x, temp_r30->pos.y + 10.0f * temp_r30->scale.x, temp_r30->pos.z, 20.0f, &effectDustParam);
                    }
                }
                PlayCharVoice(character, 0x119, arg3);
            }
            break;
        case 0x1B:
            if (temp_r30->unk_0C != -1 && skipAnimUpdate == 0) {
                break;
            }
            if (!(temp_r29->unkAC & 0x10)) {
                if (arg4 == 10) {
                    var_r19 = CreateEffectWarn(arg1, temp_r30->pos.x, temp_r30->pos.y + 100.0f, temp_r30->pos.z, 20.0f, &effectWarnParam);
                    if (var_r19 == -1) {
                        break;
                    }
                    var_r17 = &Hu3DData[effectMdl[0]];
                    var_r18 = var_r17->unk_120;
                    var_r27 = &var_r18->unk_48[var_r19];
                    var_r27->unk02 = 0;
                    var_r27->unk08.x = arg1;
                    if (character == 7) {
                        var_r27->unk08.y = 190.0f;
                    } else if (character == 2 || character == 5 || character == 6) {
                        var_r27->unk08.y = 140.0f;
                    } else {
                        var_r27->unk08.y = 120.0f;
                    }
                    var_r27->unk14.x = var_r27->unk14.z = 0.0f;
                    var_r27->unk14.y = 100.0f;
                }
                if (arg4 == 30) {
                    for (i = 0; i < 8; i++) {
                        effectDustParam.unk0C.x = 4.0 * sind(45.0f * i + 22.5) * temp_r30->scale.x;
                        effectDustParam.unk0C.y = 0.0f;
                        effectDustParam.unk0C.z = 4.0 * cosd(45.0f * i + 22.5) * temp_r30->scale.x;
                        CreateEffectDust(arg1, temp_r30->pos.x, temp_r30->pos.y + 10.0f * temp_r30->scale.x, temp_r30->pos.z, 20.0f, &effectDustParam);
                    }
                }
            }
            break;
        case 0x1C:
            if (temp_r30->unk_0C != -1 && skipAnimUpdate == 0) {
                break;
            }
            if (!(temp_r29->unkAC & 0x10) && arg4 == 0) {
                var_r19 = CreateEffectWarn(arg1, temp_r30->pos.x, temp_r30->pos.y + 100.0f, temp_r30->pos.z, 20.0f, &effectWarnParam);
                if (var_r19 == -1) {
                    break;
                }
                var_r17 = &Hu3DData[effectMdl[0]];
                var_r18 = var_r17->unk_120;
                var_r27 = &var_r18->unk_48[var_r19];
                var_r27->unk02 = 0;
                var_r27->unk08.x = arg1;
                if (character == 7) {
                    var_r27->unk08.y = 150.0f;
                } else if (character == 2 || character == 5 || character == 6) {
                    var_r27->unk08.y = 120.0f;
                } else {
                    var_r27->unk08.y = 100.0f;
                }
                var_r27->unk14.x = var_r27->unk14.z = 0.0f;
                var_r27->unk14.y = 100.0f;
            }
            break;
        case 0x15:
        case 0x16:
        case 0x79:
            if (!(temp_r29->unkAC & 1) && !(temp_r29->unkAC & 0x10)) {
                PlayCharVoice(character, 0x11A, arg3);
                for (i = 0; i < 3; i++) {
                    var_r19 = CreateEffectBird(arg1, temp_r30->pos.x, temp_r30->pos.y + 100.0f * temp_r30->scale.x, temp_r30->pos.z, 1.0f, &effectWarnParam);
                    if (var_r19 == -1) {
                        break;
                    }
                    var_r17 = &Hu3DData[effectMdl[7]];
                    var_r18 = var_r17->unk_120;
                    var_r27 = &var_r18->unk_48[var_r19];
                    var_r27->unk02 = 1;
                    var_r27->unk00 = 0;
                    var_r27->unk08.x = character;
                    var_r27->unk08.y = i * 0x78;
                    temp_r29->unkAC |= 1;
                }
            }
            break;
        case 0x13:
            if ((arg4 & 1) && !(temp_r29->unkAC & 0x10)) {
                Hu3DModelObjMtxGet(arg1, CharModelHookNameGet(character, temp_r29->unk02, 4), sp28);
                sp1C.x = sp28[0][3];
                sp1C.y = sp28[1][3];
                sp1C.z = sp28[2][3];
                CreateEffectSmoke(arg1, sp1C.x, sp1C.y, sp1C.z, 20.0f, &effectSmokeParam);
            }
            break;
        case 5:
            if (arg4 == 0) {
                if (temp_r29->unkB0 == 4) {
                    PlayCharVoice(character, 0x10A, arg3);
                } else if (temp_r29->unkB0 == 5) {
                    PlayCharVoice(character, 0x10C, arg3);
                } else {
                    PlayCharVoice(character, 0x115, arg3);
                }
            }
            break;
        case 8:
            if (arg4 == 0) {
                PlayCharVoice(character, 0x118, arg3);
            }
            break;
        case 0x14:
        case 0x50:
            if (arg4 == 0 && !(temp_r29->unkAC & 0x14)) {
                PlayCharVoice(character, 0x123, arg3);
            }
            break;
        case 0x3B:
        case 0x48:
            if (arg4 == 0 && !(temp_r29->unkAC & 0x12)) {
                PlayCharVoice(character, 0x122, arg3);
            }
            break;
        case 0x3F:
        case 0x53:
        case 0x57:
            if (arg4 == 0 && !(temp_r29->unkAC & 0x12)) {
                PlayCharVoice(character, 0x124, arg3);
            }
            temp_r29->unkAC |= 2;
            var_r22 |= 2;
            break;
        case 0x4B:
            if (arg4 == lbl_801D3600[character] && !(temp_r29->unkAC & 0x12)) {
                PlayCharVoice(character, 0x124, arg3);
                temp_r29->unkAC |= 2;
                var_r22 |= 2;
            }
            break;
        case 0x4C:
            if (arg4 == lbl_801D3608[character] && !(temp_r29->unkAC & 0x12)) {
                PlayCharVoice(character, 0x124, arg3);
                temp_r29->unkAC |= 2;
                var_r22 |= 2;
            }
            break;
        case 0x17:
            if (!(temp_r29->unkAC & 0x12)) {
                if (omcurovl < OVL_W01 && arg4 == lbl_801D35F0[character]) {
                    PlayCharVoice(character, 0x124, arg3);
                    temp_r29->unkAC |= 2;
                    var_r22 |= 2;
                } else if (omcurovl >= OVL_W01 && arg4 == lbl_801D35F8[character]) {
                    PlayCharVoice(character, 0x122, arg3);
                    temp_r29->unkAC |= 2;
                    var_r22 |= 2;
                }
            }
            break;
        case 0x18:
            if (arg4 == lbl_801D3610[character] && !(temp_r29->unkAC & 0x14)) {
                PlayCharVoice(character, 0x121, arg3);
                temp_r29->unkAC |= 4;
                var_r22 |= 4;
            }
            break;
        case 0x2A:
        case 0x72:
            if (arg4 == 0 && !(temp_r29->unkAC & 0x14)) {
                PlayCharVoice(character, 0x121, arg3);
            }
            temp_r29->unkAC |= 4;
            var_r22 |= 4;
            break;
        case 0x49:
        case 0x4E:
            if (arg4 == 0 && !(temp_r29->unkAC & 0x14)) {
                PlayCharVoice(character, 0x12E, arg3);
            }
            temp_r29->unkAC |= 4;
            var_r22 |= 4;
            break;
    }
    if (skipAnimUpdate == 0) {
        if (!(var_r22 & 4)) {
            temp_r29->unkAC &= ~4;
        }
        if (!(var_r22 & 2)) {
            temp_r29->unkAC &= ~2;
        }
    }
}

static s32 PlayCharVoice(s16 character, s16 arg1, u8 arg2) {
    UnkCharInstanceStruct *temp_r31;
    ModelData *temp_r29;

    temp_r31 = &charInstance[character];
    temp_r29 = &Hu3DData[temp_r31->unk00];
    if (arg2 & 1) {
        return;
    }
    if (temp_r31->unkAC & 8) {
        return HuAudCharVoicePlayPos(character, arg1, &temp_r29->pos);
    } else {
        return HuAudCharVoicePlay(character, arg1);
    }
}

static void InitEffect(void) {
    HsfanimStruct01 *var_r29;
    ParticleData *temp_r30;
    void *temp_r26;
    AnimData *temp_r25;
    s16 var_r27;
    s16 i;
    s16 j;

    var_r27 = 0;
    for (i = 0; i < 8; i++) {
        if (effectMdl[i] == -1) {
            temp_r26 = HuDataSelHeapReadNum(effectDataTbl[i].unk00, MEMORY_DEFAULT_NUM, HEAP_DATA);
            temp_r25 = HuSprAnimRead(temp_r26);
            effectMdl[i] = Hu3DParticleCreate(temp_r25, effectDataTbl[i].unk04);
            if (i == 7) {
                Hu3DParticleAnimModeSet(effectMdl[i], 0);
            }
            Hu3DParticleHookSet(effectMdl[i], UpdateEffect);
            if (!particleData[i]) {
                particleData[i] = HuMemDirectMalloc(HEAP_SYSTEM, effectDataTbl[i].unk04 * sizeof(EffectParamData));
            }
            Hu3DParticleBlendModeSet(effectMdl[i], effectDataTbl[i].unk06);
            temp_r30 = Hu3DData[effectMdl[i]].unk_120;
            temp_r30->unk_02 = 0;
            temp_r30->unk_1C = particleData[i];
            temp_r30->unk_34 = 1;
            var_r29 = temp_r30->unk_48;
            for (j = 0; j < temp_r30->unk_30; j++, var_r29++) {
                var_r29->unk2C = 0.0f;
            }
            var_r27 = 1;
        }
    }
    if (var_r27 != 0) {
        HuDataDirClose(0x120000);
    }
}

static s16 CreateEffectDust(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5) {
    ModelData *temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if (effectMdl[2] == -1) {
        return -1;
    }
    arg4 *= temp_r31->scale.x;
    return CreateEffect(effectMdl[2], temp_r31->camera, arg1, arg2, arg3, arg4, arg5);
}

static s16 CreateEffectSmoke(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5) {
    ModelData *temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if (effectMdl[3] == -1) {
        return -1;
    }
    arg4 *= temp_r31->scale.x;
    return CreateEffect(effectMdl[3], temp_r31->camera, arg1, arg2, arg3, arg4, arg5);
}

static s16 CreateEffectDot(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5) {
    ModelData *temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if (effectMdl[6] == -1) {
        return -1;
    }
    arg4 *= temp_r31->scale.x;
    return CreateEffect(effectMdl[6], temp_r31->camera, arg1, arg2, arg3, arg4, arg5);
}

static s16 CreateEffectStar(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5) {
    ModelData *temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if (effectMdl[4] == -1) {
        return -1;
    }
    arg4 *= temp_r31->scale.x;
    return CreateEffect(effectMdl[4], temp_r31->camera, arg1, arg2, arg3, arg4, arg5);
}

static s16 CreateEffectWarn(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5) {
    ModelData *temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if (effectMdl[0] == -1) {
        return -1;
    }
    arg4 *= temp_r31->scale.x;
    return CreateEffect(effectMdl[0], temp_r31->camera, arg1, arg2, arg3, arg4, arg5);
}

static s16 CreateEffectBird(s16 arg0, float arg1, float arg2, float arg3, float arg4, EffectParamData *arg5) {
    ModelData *temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if (effectMdl[7] == -1) {
        return -1;
    }
    arg4 *= temp_r31->scale.x;
    return CreateEffect(effectMdl[7], temp_r31->camera, arg1, arg2, arg3, arg4, arg5);
}

static s16 CreateEffect(s16 arg0, s16 arg1, float arg2, float arg3, float arg4, float arg5, EffectParamData *arg6) {
    ModelData *var_r28;
    ParticleData *temp_r30;
    EffectParamData *var_r27;
    HsfanimStruct01 *var_r31;
    s16 i;

    var_r28 = &Hu3DData[arg0];
    temp_r30 = var_r28->unk_120;
    var_r27 = temp_r30->unk_1C;
    var_r31 = &temp_r30->unk_48[temp_r30->unk_02];
    for (i = temp_r30->unk_02; i < temp_r30->unk_30; i++, var_r31++) {
        if (!var_r31->unk2C) {
            break;
        }
    }
    if (i >= temp_r30->unk_30) {
        var_r31 = temp_r30->unk_48;
        for (i = 0; i < temp_r30->unk_30; i++, var_r31++) {
            if (!var_r31->unk2C) {
                break;
            }
        }
    }
    if (i != temp_r30->unk_30) {
        var_r27[i] = *arg6;
        var_r31->unk06 = arg1;
        var_r31->unk34.x = arg2;
        var_r31->unk34.y = arg3;
        var_r31->unk34.z = arg4;
        var_r31->unk08 = arg6->unk0C;
        var_r31->unk40.r = arg6->unk04;
        var_r31->unk40.g = arg6->unk05;
        var_r31->unk40.b = arg6->unk06;
        var_r31->unk40.a = arg6->unk07;
        var_r31->unk28 = arg5;
        var_r31->unk2C = arg5;
        var_r31->unk00 = 0;
        var_r31->unk02 = -1;
        temp_r30->unk_02 = i;
    } else {
        return -1;
    }
    return i;
}

static void UpdateEffect(ModelData *model, ParticleData *particle, Mtx matrix) {
    EffectParamData *temp_r30;
    HsfanimStruct01 *var_r31;
    s16 var_r28;
    s16 i;

    temp_r30 = particle->unk_1C;
    if (particle->unk_34 == 0) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (var_r31->unk2C) {
            if (var_r31->unk02 == -1) {
                var_r31->unk08.x *= temp_r30[i].unk18;
                var_r31->unk08.y *= temp_r30[i].unk1C;
                var_r31->unk08.z *= temp_r30[i].unk20;
                PSVECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
                var_r31->unk08.y += temp_r30[i].unk24;
                var_r28 = var_r31->unk40.r + temp_r30[i].unk34 * (temp_r30[i].unk08 - temp_r30[i].unk04);
                if (var_r28 < 0) {
                    var_r28 = 0;
                } else if (var_r28 > 0xFF) {
                    var_r28 = 0xFF;
                }
                var_r31->unk40.r = var_r28;
                var_r28 = var_r31->unk40.g + temp_r30[i].unk34 * (temp_r30[i].unk09 - temp_r30[i].unk05);
                if (var_r28 < 0) {
                    var_r28 = 0;
                } else if (var_r28 > 0xFF) {
                    var_r28 = 0xFF;
                }
                var_r31->unk40.g = var_r28;
                var_r28 = var_r31->unk40.b + temp_r30[i].unk34 * (temp_r30[i].unk0A - temp_r30[i].unk06);
                if (var_r28 < 0) {
                    var_r28 = 0;
                } else if (var_r28 > 0xFF) {
                    var_r28 = 0xFF;
                }
                var_r31->unk40.b = var_r28;
                var_r28 = var_r31->unk40.a + temp_r30[i].unk30;
                if (var_r28 < 1) {
                    var_r31->unk2C = 0.0f;
                }
                var_r31->unk40.a = var_r28;
                if (var_r31->unk2C) {
                    if (temp_r30[i].unk00 & 1) {
                        var_r31->unk2C = var_r31->unk28 * (((var_r31->unk00_s16 + i) & 1) ? 1.0 : 0.5);
                    } else {
                        var_r31->unk2C = var_r31->unk28;
                    }
                    var_r31->unk28 += temp_r30[i].unk2C;
                    if (var_r31->unk28 <= 0.01f) {
                        var_r31->unk2C = 0.0f;
                    }
                }
                var_r31->unk00_s16++;
            } else {
                switch (var_r31->unk02) {
                    case 0:
                        RotateEffect(var_r31);
                        break;
                    case 1:
                        PlayEffectSound(var_r31);
                        break;
                    case 2:
                        OrbitEffect(var_r31);
                        break;
                }
            }
        }
    }
    DCStoreRangeNoSync(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

static void RotateEffect(HsfanimStruct01 *arg0) {
    ModelData *temp_r30;
    float var_f31;

    temp_r30 = &Hu3DData[(s32) arg0->unk08.x];
    if (arg0->unk00_s16 < 8) {
        var_f31 = 0.3 + sind(40.0f + 10.0f * (arg0->unk00_s16 + 1));
        arg0->unk2C = 50.0f * var_f31 * temp_r30->scale.x;
        arg0->unk40.a = 0xFF;
        var_f31 = 0.3 + sind(15.0f * (arg0->unk00_s16 + 1));
    } else {
        var_f31 = 0.3 + sind(135);
    }
    var_f31 *= temp_r30->scale.x;
    arg0->unk34.x = temp_r30->pos.x + arg0->unk14.x * var_f31;
    arg0->unk34.y = temp_r30->pos.y + arg0->unk08.y * temp_r30->scale.x + arg0->unk14.y * var_f31;
    arg0->unk34.z = temp_r30->pos.z + arg0->unk14.z * var_f31;
    if (arg0->unk00_s16 > 0x14) {
        arg0->unk40.a -= 0x20;
        arg0->unk2C -= 8.0f * temp_r30->scale.x;
        if (arg0->unk2C < 0.0f) {
            arg0->unk2C = 0.0f;
        }
    }
    arg0->unk00_s16++;
}

static float voiceParam[16] = {
    110.0f, 160.0f, 110.0f, 160.0f,
    150.0f, 180.0f, 130.0f, 160.0f,
    130.0f, 160.0f, 150.0f, 160.0f,
    150.0f, 180.0f, 120.0f, 210.0f
};

static void PlayEffectSound(HsfanimStruct01 *arg0) {
    ModelData *temp_r30;
    UnkCharInstanceStruct *temp_r29;
    s16 temp_r26;
    s16 temp_r28;
    s16 var_r25;

    temp_r28 = arg0->unk08.x;
    temp_r29 = &charInstance[temp_r28];
    temp_r30 = &Hu3DData[temp_r29->unk00];
    if (arg0->unk00_s16 < 0x14 && arg0->unk2C < 40.0f * temp_r30->scale.x) {
        arg0->unk2C += 4.0f * temp_r30->scale.x;
    }
    arg0->unk40.a = 0xFF;
    if (temp_r29->unk04 == 0x16 || temp_r29->unk06 == 0x16) {
        var_r25 = voiceParam[temp_r28 * 2];
    } else {
        var_r25 = voiceParam[temp_r28 * 2 + 1];
    }
    temp_r26 = (arg0->unk00_s16 * 5) % 360;
    arg0->unk34.x = temp_r30->pos.x + 40.0 * sind(arg0->unk08.y + temp_r26) * temp_r30->scale.x;
    arg0->unk34.y = temp_r30->pos.y + var_r25 * temp_r30->scale.x;
    arg0->unk34.z = temp_r30->pos.z + 40.0 * cosd(arg0->unk08.y + temp_r26) * temp_r30->scale.x;
    arg0->unk00_s16++;
    if (arg0->unk00_s16 >= 0x8F) {
        arg0->unk00_s16 = 0x48;
    }
    if (temp_r29->unk04 != 0x15 && temp_r29->unk04 != 0x16 && temp_r29->unk04 != 0x79 && arg0->unk00_s16 > 0x1E) {
        arg0->unk2C -= 4.0f * temp_r30->scale.x;
        if (arg0->unk2C < 0.0f) {
            arg0->unk2C = 0.0f;
            temp_r29->unkAC &= ~1;
            if (arg0->unk08.y == 0.0) {
                PlayCharVoice(temp_r28, 0x100, temp_r29->unkAC);
            }
        }
    }
}

s16 CharModelMotionCreate(s16 character, s32 data_num) {
    UnkCharInstanceStruct *temp_r31;
    s16 var_r28;
    s16 var_r30;
    u32 temp_r26;
    void *var_r27;

    temp_r31 = &charInstance[character];
    if (temp_r31->unk00 == -1) {
        return -1;
    }
    for (var_r30 = 0; var_r30 < 32; var_r30++) {
        if (temp_r31->unk0C[var_r30] == -1) {
            break;
        }
    }
    if (var_r30 == 32) {
        return -1;
    }
    temp_r26 = data_num & 0xFFFF0000;
    for (var_r28 = 0; var_r28 < 8; var_r28++) {
        if (temp_r26 == charDirTbl[var_r28][2]) {
            break;
        }
    }
    if (var_r28 != 8 || temp_r26 == 0) {
        data_num &= 0xFFFF;
        var_r27 = HuAR_ARAMtoMRAMFileRead(data_num | charDirTbl[character][2], MEMORY_DEFAULT_NUM, 2);
        if (!var_r27) {
            var_r27 = HuDataSelHeapReadNum(data_num | charDirTbl[character][2], MEMORY_DEFAULT_NUM, HEAP_DATA);
        }
        temp_r31->unk4C[var_r30] = data_num;
    } else {
        var_r27 = HuDataSelHeapReadNum(data_num, MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk4C[var_r30] = -1;
    }
    temp_r31->unk0C[var_r30] = Hu3DJointMotion(temp_r31->unk00, var_r27);
    temp_r31->unk8C[var_r30] = 0;
    return temp_r31->unk0C[var_r30];
}

void CharModelMotionIndexSet(s16 character, s16 arg1, s32 arg2) {
    UnkCharInstanceStruct *temp_r30;
    s16 i;

    temp_r30 = &charInstance[character];
    for (i = 0; i < 32; i++) {
        if (temp_r30->unk0C[i] == arg1) {
            break;
        }
    }
    if (i != 32) {
        temp_r30->unk4C[i] = arg2;
    }
}

void CharModelMotionKill(s16 character, u32 motion) {
    UnkCharInstanceStruct *temp_r30;
    s16 i;

    temp_r30 = &charInstance[character];
    for (i = 0; i < 32; i++) {
        if (temp_r30->unk0C[i] == motion) {
            break;
        }
    }
    temp_r30->unk0C[i] = -1;
    Hu3DMotionKill(motion);
}

void CharModelMotionDataClose(s16 character) {
    s16 i;

    if (character == -1) {
        for (i = 0; i < 8; i++) {
            CharModelMotionDataClose(i);
        }
    } else {
        HuDataDirClose(charDirTbl[character][2]);
    }
}

void CharModelDataClose(s16 arg0) {
    s16 i;

    if (arg0 == -1) {
        for (i = 0; i < 8; i++) {
            CharModelDataClose(i);
            // Required to match.
            (void) i;
            (void) arg0;
        }
    } else {
        HuDataDirClose(charDirTbl[arg0][0]);
        HuDataDirClose(charDirTbl[arg0][1]);
        HuDataDirClose(charDirTbl[arg0][2]);
    }
}

void CharModelKill(s16 character) {
    UnkCharInstanceStruct *temp_r29;
    s16 i;

    if (character == -1) {
        for (i = 0; i < 8; i++) {
            CharModelKill(i);
        }
        for (i = 0; i < 15; i++) {
            lbl_801975B0[i] = 0;
        }
        return;
    }
    CharModelMotionDataClose(character);
    temp_r29 = &charInstance[character];
    for (i = 0; i < 32; i++) {
        if (temp_r29->unk0C[i] != -1) {
            Hu3DMotionKill(temp_r29->unk0C[i]);
        }
        temp_r29->unk0C[i] = -1;
    }
    if (temp_r29->unk00 != -1) {
        Hu3DModelKill(temp_r29->unk00);
    }
    temp_r29->unk00 = -1;
    for (i = 0; i < 8; i++) {
        if (charInstance[i].unk00 != -1) {
            break;
        }
    }
    if (i == 8) {
        for (i = 0; i < 8; i++) {
            if (effectMdl[i] != -1) {
                Hu3DModelKill(effectMdl[i]);
            }
            effectMdl[i] = -1;
        }
    }
    if (temp_r29->unkC4) {
        HuMemDirectFree(temp_r29->unkC4->user_data);
        HuPrcKill(temp_r29->unkC4);
        for (i = 0; i < 32; i++) {
            if (itemHookProcess[i]) {
                HuPrcKill(itemHookProcess[i]);
            }
            itemHookProcess[i] = NULL;
        }
        temp_r29->unkC4 = NULL;
    }
}

void CharModelMotionSet(s16 character, s16 motion) {
    UnkCharInstanceStruct *temp_r31;
    MotionData *sp8;

    temp_r31 = &charInstance[character];
    sp8 = &Hu3DMotion[motion];
    CharModelTexAnimSet(character);
    Hu3DMotionSet(temp_r31->unk00, motion);
}

void CharModelTexAnimSet(s16 character) {
    HsfAttribute *var_r31;
    HsfdrawStruct01 *temp_r30;
    ModelData *temp_r26;
    UnkCharInstanceStruct *temp_r27;
    s16 var_r25;
    s16 i;
    char **temp_r28;

    temp_r27 = &charInstance[character];
    temp_r26 = &Hu3DData[temp_r27->unk00];
    var_r31 = temp_r26->hsfData->attribute;
    for (i = 0, var_r25 = 1; i < 4; i++, var_r25 <<= 1) {
        if (var_r25 & temp_r27->unk02) {
            break;
        }
    }
    if (i < 4) {
        temp_r28 = CharModelTexNameGet(character, temp_r27->unk02);
        for (i = 0; i < temp_r26->hsfData->attributeCnt; i++, var_r31++) {
            if ((var_r31->bitmap->name[0] == temp_r28[0][0] && strcmp(var_r31->bitmap->name, temp_r28[0]) == 0)
                || (var_r31->bitmap->name[0] == temp_r28[1][0] && strcmp(var_r31->bitmap->name, temp_r28[1]) == 0)) {
                if (var_r31->unk04) {
                    temp_r30 = var_r31->unk04;
                    temp_r30->unk08 = temp_r30->unk0C = temp_r30->unk10 = 0.0f;
                    temp_r30->unk14 = temp_r30->unk18 = temp_r30->unk1C = 0.0f;
                }
            }
        }
    }
}

char *charTexNameTbl[64] = {
              "s3c000m1_eyes",            "s3c000m1_eyes",  "s3c000m1_eyes",  "s3c000m1_eyes",
              "s3c000m2_eyes",            "s3c000m2_eyes",  "s3c000m3_eyes",  "s3c000m3_eyes",
               "S3c001m0_eye",             "S3c001m0_eye",   "S3c001m1_eye",   "S3c001m1_eye",
                 "c001m3_eye",               "c001m3_eye",     "c001m3_eye",     "c001m3_eye",
             "s3c002m0_r_eye",           "s3c002m0_l_eye", "s3c002m1_r_eye", "s3c002m1_l_eye",
             "s3c002m2_r_eye",           "s3c002m2_l_eye",               "",               "",
                       "eye1",                     "eye2",       "S3c003m1",       "S3c003m1",
                       "eye1",                     "eye2",           "eye1",           "eye2",
                    "GC-eyes",                  "GC-eyes",   "s3c004m1_eye",   "s3c004m1_eye",
     "Clswario_eye_l1_AUTO12",   "Clswario_eye_l1_AUTO13",               "",               "",
              "m_donkey_eye4",            "m_donkey_eye5",   "S3donkey_eye",   "S3donkey_eye",
              "m_donkey_eye1",            "m_donkey_eye2",               "",               "",
                    "GC-eyes",                  "GC-eyes", "s3c007m1_Eye_L", "s3c007m1_Eye_R",
                      "mat87",                    "mat89",               "",               "",
    "clswaluigi_eye_l1_AUTO1",  "clswaluigi_eye_l1_AUTO2",  "s3c007_m1_eye",  "s3c007_m1_eye",
    "clswaluigi_eye_l1_AUTO9", "clswaluigi_eye_l1_AUTO10",               "",               ""
};

char **CharModelTexNameGet(s16 arg0, s16 arg1) {
    s16 var_r30;
    s16 i;

    for (i = 0, var_r30 = 1; i < 3; i++, var_r30 <<= 1) {
        if (var_r30 & arg1) {
            break;
        }
    }
    return &charTexNameTbl[arg0 * 8 + i * 2];
}

static char *hookNameTbl[40] = {
    "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body",
    "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body",
    "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body",
    "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body",
    "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body",
    "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body",
    "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body",
    "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body"
};

char *CharModelHookNameGet(s16 arg0, s16 arg1, s16 arg2) {
    s16 i;
    s16 var_r30;

    for (i = 0, var_r30 = 1; i < 3; i++, var_r30 <<= 1) {
        if (var_r30 & arg1) {
            break;
        }
    }
    return hookNameTbl[arg0 * 5 + arg2];
}

void CharModelMotionTimeSet(s16 character, float time) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    Hu3DMotionTimeSet(temp_r31->unk00, time);
}

float CharModelMotionTimeGet(s16 character) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    return Hu3DMotionTimeGet(temp_r31->unk00);
}

float CharModelMotionMaxTimeGet(s16 character) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    return Hu3DMotionMaxTimeGet(temp_r31->unk00);
}

s32 CharModelMotionEndCheck(s16 character) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    return Hu3DMotionEndCheck(temp_r31->unk00);
}

s16 CharModelMotionShiftIDGet(s16 character) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    return Hu3DMotionShiftIDGet(temp_r31->unk00);
}

void CharModelMotionShiftSet(s16 character, s16 motion, float time, float shift_time, u32 attr) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];
    MotionData *sp18 = &Hu3DMotion[motion];

    Hu3DMotionShiftSet(temp_r31->unk00, motion, time, shift_time, attr);
}

float CharModelMotionShiftTimeGet(s16 character) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    return Hu3DMotionShiftTimeGet(temp_r31->unk00);
}

void CharModelMotionSpeedSet(s16 character, float speed) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    Hu3DMotionSpeedSet(temp_r31->unk00, speed);
}

void CharModelLayerSetAll(s16 arg0) {
    s16 i;

    for (i = 0; i < 8; i++) {
        if (effectMdl[i] != -1) {
            Hu3DModelLayerSet(effectMdl[i], arg0);
        }
    }
}

static inline Process *CharModelItemHookCreateInlineFunc(void) {
    s16 i;

    for (i = 0; i < 32; i++) {
        if (!itemHookProcess[i]) {
            break;
        }
    }
    if (i == 32) {
        return NULL;
    } else {
        itemHookProcess[i] = HuPrcCreate(UpdateItemHook, 0x64, 0x2000, 0);
        return itemHookProcess[i];
    }
}

void CharModelItemHookCreate(s16 character, char *arg1) {
    Mtx sp18;
    Vec spC;
    UnkCharInstanceStruct *temp_r31;
    ModelData *temp_r28;
    HsfObject *temp_r25;
    HsfConstData *temp_r24;
    Process *var_r26;
    UnkProcessData *temp_r27;
    s16 temp_r29;

    temp_r31 = &charInstance[character];
    temp_r28 = &Hu3DData[temp_r31->unk00];
    temp_r25 = Hu3DModelObjPtrGet(temp_r31->unk00, arg1);
    Hu3DModelObjMtxGet(temp_r31->unk00, arg1, sp18);
    temp_r24 = temp_r25->constData;
    temp_r29 = temp_r24->hook;
    if (temp_r29 != -1) {
        Hu3DModelHookObjReset(temp_r31->unk00, arg1);
        var_r26 = CharModelItemHookCreateInlineFunc();
        if (!var_r26) {
            Hu3DModelAttrSet(temp_r29, 1);
            return;
        }
        var_r26->user_data = temp_r27 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkProcessData), MEMORY_DEFAULT_NUM);
        temp_r28 = &Hu3DData[temp_r29];
        Hu3DMtxTransGet(sp18, &spC);
        Hu3DModelPosSetV(temp_r29, &spC);
        Hu3DMtxRotGet(sp18, &spC);
        mtxRot(temp_r28->unk_F0, spC.x, spC.y, spC.z);
        Hu3DMtxScaleGet(sp18, &spC);
        Hu3DModelScaleSetV(temp_r29, &spC);
        temp_r27->unk02 = temp_r29;
        temp_r27->unk00 = temp_r28->camera;
    }
}

static void UpdateItemHook(void) {
    Mtx sp14;
    Vec sp8;
    ModelData *temp_r30;
    Process *temp_r25;
    s16 var_r28;
    s16 var_r29;
    UnkProcessData *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r30 = &Hu3DData[temp_r31->unk02];
    Hu3DModelObjMtxGet(temp_r31->unk02, "", sp14);
    sp8.x = PGMinPos.x + (PGMaxPos.x - PGMinPos.x) / 2;
    sp8.y = PGMinPos.y + (PGMaxPos.y - PGMinPos.y) / 2;
    sp8.z = PGMinPos.z + (PGMaxPos.z - PGMinPos.z) / 2;
    for (var_r29 = 0; var_r29 < 0x28; var_r29++) {
        temp_r30->pos.y += 4.0f;
        mtxRotCat(temp_r30->unk_F0, 24.0f, 0.0f, 0.0f);
        temp_r30->scale.x *= 0.95f;
        temp_r30->scale.y *= 0.95f;
        temp_r30->scale.z *= 0.95f;
        HuPrcVSleep();
    }
    Hu3DModelObjMtxGet(temp_r31->unk02, "", sp14);
    sp8.x = PGMinPos.x + (PGMaxPos.x - PGMinPos.x) / 2;
    sp8.y = PGMinPos.y + (PGMaxPos.y - PGMinPos.y) / 2;
    sp8.z = PGMinPos.z + (PGMaxPos.z - PGMinPos.z) / 2;
    Hu3DModelAttrSet(temp_r31->unk02, 1);
    effectDustParam.unk0C.x = 0.0f;
    effectDustParam.unk0C.y = 0.0f;
    effectDustParam.unk0C.z = 0.0f;
    CreateEffectDust(temp_r31->unk02, sp8.x, sp8.y, sp8.z, 40.0f, &effectDustParam);
    for (var_r29 = 0; var_r29 < 8; var_r29++) {
        effectDustParam.unk0C.x = frandmod(10) - 5;
        effectDustParam.unk0C.y = frandmod(10) - 5;
        effectDustParam.unk0C.z = frandmod(10) - 5;
        CreateEffectDust(temp_r31->unk02, sp8.x, sp8.y, sp8.z, 20.0f, &effectDustParam);
    }
    PSMTXIdentity(temp_r30->unk_F0);
    temp_r25 = HuPrcCurrentGet();
    for (var_r28 = 0; var_r28 < 32; var_r28++) {
        if (itemHookProcess[var_r28] == temp_r25) {
            HuPrcKill(temp_r25);
            itemHookProcess[var_r28] = NULL;
        }
    }
    while (1) {
        HuPrcVSleep();
    }
}

static EffectParamData modelParticleParam = {
    0,
    0xFF, 0xFF, 0xFF, 0xFF,
    0x40, 0x20, 0x00, 0xFF,
    { 0.0f, 2.0f, 1.0f },
    0.95f, 0.95f, 0.95f,
    0.0f,
    0x00000000,
    1.0f,
    -5.0f,
    0.02f
};

void CharModelEffectCreate(s16 arg0, Vec *arg1) {
    s16 temp_r28;
    s16 i;
    HsfanimStruct01 *var_r31;
    ParticleData *var_r27;
    ModelData *var_r26;

    for (i = 0; i < 8; i++) {
        temp_r28 = CreateEffect(effectMdl[3], arg0, arg1->x, arg1->y, arg1->z, 20.0f, &modelParticleParam);
        if (temp_r28 == -1) {
            break;
        }
        var_r26 = &Hu3DData[effectMdl[3]];
        var_r27 = var_r26->unk_120;
        var_r31 = &var_r27->unk_48[temp_r28];
        var_r31->unk02 = 2;
        var_r31->unk08.x = 30.0 * sind(i * 45);
        var_r31->unk08.y = 30.0 * cosd(i * 45);
        var_r31->unk08.z = 0.0f;
        var_r31->unk14 = *arg1;
        var_r31->unk20 = 1.15f;
        var_r31->unk24 = 0.1f * (frandmod(20) - 10);
        var_r31->unk40.a = 0xFF - frandmod(3) * 16;
    }
    for (i = 0; i < 8; i++) {
        temp_r28 = CreateEffect(effectMdl[3], arg0, arg1->x, arg1->y, arg1->z, 10.0f, &modelParticleParam);
        if (temp_r28 == -1) {
            break;
        }
        var_r26 = &Hu3DData[effectMdl[3]];
        var_r27 = var_r26->unk_120;
        var_r31 = &var_r27->unk_48[temp_r28];
        var_r31->unk02 = 2;
        var_r31->unk08.x = frandmod(100) - 50;
        var_r31->unk08.y = frandmod(100) - 50;
        var_r31->unk08.z = frandmod(100) - 50;
        var_r31->unk14 = *arg1;
        var_r31->unk20 = 1.15f;
        var_r31->unk24 = 0.1f * (frandmod(20) - 10);
        var_r31->unk40.a = 0xFF - frandmod(3) * 16;
    }
    temp_r28 = CreateEffect(effectMdl[3], arg0, arg1->x, arg1->y, arg1->z, 10.0f, &modelParticleParam);
    if (temp_r28 != -1) {
        var_r26 = &Hu3DData[effectMdl[3]];
        var_r27 = var_r26->unk_120;
        var_r31 = &var_r27->unk_48[temp_r28];
        var_r31->unk02 = 2;
        var_r31->unk08.x = 0.0f;
        var_r31->unk08.y = 0.0f;
        var_r31->unk08.z = 0.0f;
        var_r31->unk14 = *arg1;
        var_r31->unk24 = 0.0f;
        var_r31->unk20 = 1.15f;
        var_r31->unk40.a = 0xFF;
    }
}

static void OrbitEffect(HsfanimStruct01 *arg0) {
    float temp_f31;
    float var_f30;
    s16 temp_r30;

    var_f30 = 20.0f + 3.75f * arg0->unk00_s16;
    if (var_f30 > 90.0f) {
        var_f30 = 90.0f;
    }
    temp_f31 = sind(var_f30);
    arg0->unk34.x = arg0->unk14.x + arg0->unk08.x * temp_f31;
    arg0->unk34.y = arg0->unk14.y + arg0->unk08.y * temp_f31;
    arg0->unk34.z = arg0->unk14.z + arg0->unk08.z * temp_f31;
    arg0->unk2C *= arg0->unk20;
    arg0->unk20 -= 0.01;
    if (arg0->unk20 < 1.0f) {
        arg0->unk20 = 1.0f;
    }
    if (arg0->unk00_s16 > 8) {
        temp_r30 = arg0->unk40.a;
        temp_r30 -= 8;
        if (temp_r30 < 0) {
            arg0->unk40.a = 0;
            arg0->unk2C = 0.0f;
        } else {
            arg0->unk40.a = temp_r30;
        }
    }
    arg0->unk00_s16++;
}

static EffectParamData coinParticleParam = {
    1,
    0xFF, 0xFF, 0x00, 0xFF,
    0xFF, 0xFF, 0x00, 0xFF,
    { 0.0f, 2.0f, 1.0f },
    0.95f, 1.0f, 0.95f,
    -0.1f,
    0x00000000,
    -0.2f,
    -8.0f,
    0.0f
};

void CharModelCoinEffectCreate(s16 arg0, Vec *arg1) {
    s16 temp_r29;
    s16 var_r28;
    s16 i;

    for (i = 0; i < 16; i++) {
        temp_r29 = i * 22.5f;
        coinParticleParam.unk0C.x = 5.0 * sind(temp_r29);
        coinParticleParam.unk0C.y = 0.1f * (frandmod(100) - 50);
        coinParticleParam.unk0C.z = 5.0 * cosd(temp_r29);
        var_r28 = CreateEffect(effectMdl[5], arg0, arg1->x, arg1->y, arg1->z, 30.0f, &coinParticleParam);
        if (var_r28 == -1) {
            break;
        }
    }
}

static EffectParamData lbl_80131030 = {
    0,
    0xFF, 0xFF, 0x00, 0xFF,
    0xFF, 0x80, 0x00, 0xFF,
    { 0.0f, 2.0f, 1.0f },
    0.95f, 0.95f, 0.95f,
    0.0f,
    0x00000000,
    -0.2f,
    -16.0f,
    0.05f
};

static EffectParamData lbl_80131068 = {
    0,
    0xE0, 0x20, 0x20, 0xFF,
    0xE0, 0x20, 0x20, 0xFF,
    { 0.0f, 2.0f, 1.0f },
    1.0f, 1.0f, 1.0f,
    0.0f,
    0x00000000,
    -0.2f,
    -12.0f,
    0.05f
};

void fn_8004EC74(s16 character) {
    Mtx sp24;
    Vec sp18;
    Vec spC;
    UnkCharInstanceStruct *temp_r30;
    ModelData *temp_r31;
    s16 i;

    temp_r30 = &charInstance[character];
    temp_r31 = &Hu3DData[temp_r30->unk00];
    for (i = 0; i < 32; i++) {
        if (temp_r30->unk0C[i] == temp_r31->unk_08) {
            break;
        }
    }
    if (i != 32) {
        Hu3DModelObjMtxGet(temp_r30->unk00, "test11_tex_we-itemhook-r", sp24);
        sp18.x = sp24[0][3];
        sp18.y = sp24[1][3];
        sp18.z = sp24[2][3];
        mtxRot(sp24, temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
        spC.x = sp24[0][2];
        spC.y = sp24[1][2];
        spC.z = sp24[2][2];
        PSVECScale(&spC, &spC, 20.0f);
        PSVECAdd(&sp18, &spC, &sp18);
        fn_8004EDA4(temp_r31->camera, &sp18, &temp_r31->rot);
    }
}

void fn_8004EDA4(s16 arg0, Vec *arg1, Vec *arg2) {
    Mtx sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    s16 var_r28;
    s16 i;

    mtxRot(sp2C, arg2->x, arg2->y, arg2->z);
    sp20.x = sp2C[0][2];
    sp20.y = sp2C[1][2];
    sp20.z = sp2C[2][2];
    for (i = 0; i < 8; i++) {
        temp_f31 = i * 45;
        sp14.x = sp20.x * sp20.y * (1.0 - cosd(temp_f31)) - sp20.z * sind(temp_f31);
        sp14.y = sp20.y * sp20.y + (1.0f - sp20.y * sp20.y) * cosd(temp_f31);
        sp14.z = sp20.y * sp20.z * (1.0 - cosd(temp_f31)) + sp20.x * sind(temp_f31);
        PSVECNormalize(&sp14, &sp14);
        PSVECScale(&sp14, &lbl_80131030.unk0C, 10.0f);
        var_r28 = CreateEffect(effectMdl[4], arg0, arg1->x, arg1->y, arg1->z, 20.0f, &lbl_80131030);
        if (var_r28 == -1) {
            break;
        }
        PSVECScale(&sp20, &sp8, -2.0 - 0.1 * frandmod(20));
        PSVECScale(&sp14, &sp14, 2.0f);
        PSVECAdd(&sp14, &sp8, &lbl_80131068.unk0C);
        var_r28 = CreateEffect(effectMdl[6], arg0, arg1->x, arg1->y, arg1->z, 20.0f, &lbl_80131068);
        if (var_r28 == -1) {
            break;
        }
    }
}

static EffectParamData lbl_801310BC = {
    0,
    0x20, 0x20, 0xFF, 0xFF,
    0x80, 0xFF, 0x20, 0xFF,
    0.0f, 2.0f, 1.0f,
    0.95f, 0.95f, 0.95f,
    0.0f,
    0x00000000,
    -0.2f,
    -16.0f,
    0.06f
};

static EffectParamData lbl_801310F4 = {
    0,
    0x20, 0xE0, 0x20, 0xFF,
    0x20, 0xE0, 0x20, 0xFF,
    0.0f, 2.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    0.0f,
    0x00000000,
    -0.2f,
    -12.0f,
    0.05f
};

void fn_8004F058(s16 character) {
    Mtx sp24;
    Vec sp18;
    Vec spC;
    ModelData* temp_r31;
    UnkCharInstanceStruct* temp_r30;

    temp_r30 = &charInstance[character];
    temp_r31 = &Hu3DData[temp_r30->unk00];
    Hu3DModelObjMtxGet(temp_r30->unk00, "test11_tex_we-ske_R_shoe1", sp24);
    sp18.x = sp24[0][3];
    sp18.y = sp24[1][3];
    sp18.z = sp24[2][3];
    mtxRot(sp24, temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
    spC.x = sp24[0][2];
    spC.y = sp24[1][2];
    spC.z = sp24[2][2];
    PSVECScale(&spC, &spC, 30.0f);
    PSVECAdd(&sp18, &spC, &sp18);
    fn_8004F13C(temp_r31->camera, &sp18, &temp_r31->rot);
}

void fn_8004F13C(s16 arg0, Vec *arg1, Vec *arg2) {
    Mtx sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    s16 var_r28;
    s16 i;

    mtxRot(sp2C, arg2->x, arg2->y, arg2->z);
    sp20.x = sp2C[0][2];
    sp20.y = sp2C[1][2];
    sp20.z = sp2C[2][2];
    for (i = 0; i < 8; i++) {
        temp_f31 = i * 45;
        sp14.x = sp20.x * sp20.y * (1.0 - cosd(temp_f31)) - sp20.z * sind(temp_f31);
        sp14.y = sp20.y * sp20.y + (1.0f - sp20.y * sp20.y) * cosd(temp_f31);
        sp14.z = sp20.y * sp20.z * (1.0 - cosd(temp_f31)) + sp20.x * sind(temp_f31);
        PSVECNormalize(&sp14, &sp14);
        PSVECScale(&sp14, &lbl_801310BC.unk0C, 10.0f);
        var_r28 = CreateEffect(effectMdl[4], arg0, arg1->x, arg1->y, arg1->z, 20.0f, &lbl_801310BC);
        if (var_r28 == -1) {
            break;
        }
        PSVECScale(&sp20, &sp8, -2.0 - 0.1 * frandmod(20));
        PSVECScale(&sp14, &sp14, 2.0f);
        PSVECAdd(&sp14, &sp8, &lbl_801310F4.unk0C);
        var_r28 = CreateEffect(effectMdl[6], arg0, arg1->x, arg1->y, arg1->z, 20.0f, &lbl_801310F4);
        if (var_r28 == -1) {
            break;
        }
    }
}

void CharModelLayerSetAll2(s16 arg0) {
    CharModelLayerSetAll(arg0);
}

void CharModelVoiceEnableSet(s16 character, s16 motion, s32 flag) {
    UnkCharInstanceStruct* temp_r31 = &charInstance[character];
    s16 i;

    if (temp_r31->unk00 == -1) {
        return;
    }
    for (i = 0; i < 32; i++) {
        if (temp_r31->unk0C[i] == motion) {
            break;
        }
    }
    if (i != 32) {
        if (flag == 0) {
            temp_r31->unk8C[i] |= 1;
        } else {
            temp_r31->unk8C[i] &= ~1;
        }
    }
}

void fn_8004F52C(s16 character, s32 arg1) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    if (arg1 != 0) {
        temp_r31->unkAC |= 8;
        return;
    } else {
        temp_r31->unkAC &= ~8;
    }
}

void CharModelEffectEnableSet(s16 character, s32 arg1) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    if (character >= 8) {
        if (arg1 == 0) {
            lbl_801975B0[character] |= 0x10;
        } else {
            lbl_801975B0[character] &= ~0x10;
        }
        return;
    }
    if (arg1 == 0) {
        temp_r31->unkAC |= 0x10;
    } else {
        temp_r31->unkAC &= ~0x10;
    }
}

s32 CharModelEffectNpcInit(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Process *var_r24;
    Process *var_r27;
    s16 *var_r29;

    var_r24 = HuPrcCurrentGet();
    var_r27 = HuPrcChildCreate(UpdateNpcEffect, 0x64, 0x2000, 0, var_r24);
    if (var_r27) {
        var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, 4 * sizeof(s16), MEMORY_DEFAULT_NUM);
        var_r27->user_data = var_r29;
        var_r29[0] = arg0;
        var_r29[1] = arg1;
        var_r29[2] = arg2;
        var_r29[3] = arg3;
        InitEffect();
    }
}

s32 CharModelEffectNpcInitSilent(s16 arg0, s16 arg1, s16 arg2) {
    s32 sp10; // ! - uninitialized

    CharModelEffectNpcInit(arg0, arg1, arg2, -1);
    return sp10;
}

static s8 lbl_80131146[] = {
    0x07, 0x20, 0x10, 0x28,
    0x01, 0x1E, 0xE7, 0xE7,
    0x01, 0x1E, 0x01, 0x1A,
    0x01, 0x14, 0x13, 0x20,
    0x02, 0x13
};

static u16 lbl_80131158[] = {
    0x0051, 0x0053,
    0x0057, 0x0101,
    0x0059, 0x005B,
    0x0055, 0x0069,
    0x006A,
};

// Unused?
static s8 lbl_8013116A[] = {
    0x01, 0x20, 0x01, 0x15,
    0x0A, 0x1E, 0xE7, 0xE7,
    0x01, 0x1E, 0x01, 0x10,
    0x01, 0x11, 0xE7, 0xE7,
    0xE7, 0xE7
};

static u16 lbl_8013117C[] = {
    0x0052, 0x0054,
    0x0058, 0x0101,
    0x005A, 0x005C,
    0x0056, 0x0069,
    0x006A
};

static s8 lbl_8013118E[] = {
    0x03, 0x37, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0x01, 0x1A,
    0xE7, 0xE7
};

static u16 lbl_8013119C[] = {
    0x0051, 0x0053,
    0x0057, 0x0101,
    0x0059, 0x0068,
    0x0055
};

static s8 lbl_801311AA[] = {
    0x04, 0x11, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0x01, 0x10,
    0xE7, 0xE7
};

static u16 lbl_801311B8[] = {
    0x0052, 0x0054,
    0x0058, 0x0101,
    0x005A, 0x0067,
    0x0056
};

static s8 lbl_801311C6[] = {
    0x01, 0x17, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7
};

static u16 lbl_801311D4[] = {
    0x0051, 0x0053,
    0x0057, 0x0101,
    0x0059, 0x005B,
    0x0055
};

static void UpdateNpcEffect(void) {
    Vec sp2C;
    ModelData *temp_r30;
    s16 *temp_r27;
    s16 temp_r25;
    s16 temp_r26;
    s16 temp_r28;
    s16 i;

    temp_r27 = HuPrcCurrentGet()->user_data;
    temp_r25 = temp_r27[0];
    temp_r26 = 0;
    temp_r30 = &Hu3DData[temp_r27[0]];
    temp_r28 = temp_r27[3] - 8;
    while (1) {
        HuPrcVSleep();
        if (temp_r27[1] != Hu3DMotionIDGet(temp_r25)) {
            continue;
        }
        if (temp_r30->attr & 1) {
            continue;
        }
        temp_r26 = Hu3DMotionTimeGet(temp_r25);
        switch (temp_r27[2]) {
            case 0:
                if (!(temp_r26 & 0xF) && !(lbl_801975B0[temp_r28] & 0x10)) {
                    effectDustParam.unk0C.x = 2.0 * -sind(temp_r30->rot.y);
                    effectDustParam.unk0C.y = 1.0 + 0.1 * frandmod(10);
                    effectDustParam.unk0C.z = 2.0 * -cosd(temp_r30->rot.y);
                    sp2C.x = temp_r30->pos.x + (frandmod(50) - 25);
                    sp2C.y = temp_r30->pos.y;
                    sp2C.z = temp_r30->pos.z + (frandmod(50) - 25);
                    CreateEffectDust(temp_r25, sp2C.x, sp2C.y, sp2C.z, frandmod(10) + 30, &effectDustParam);
                }
                if (temp_r27[3] != -1) {
                    for (i = 0; i < 2; i++) {
                        if (lbl_80131146[temp_r28 * 2 + i] == temp_r26 * 2) {
                            HuAudFXPlay(lbl_80131158[temp_r28]);
                            break;
                        }
                    }
                }
                break;
            case 1:
                if (!(temp_r26 & 3) && !(lbl_801975B0[temp_r28] & 0x10)) {
                    effectDustParam.unk0C.x = 4.0 * -sind(temp_r30->rot.y);
                    effectDustParam.unk0C.y = 2.0 + 0.1 * frandmod(10);
                    effectDustParam.unk0C.z = 4.0 * -cosd(temp_r30->rot.y);
                    sp2C.x = temp_r30->pos.x + (frandmod(50) - 25);
                    sp2C.y = temp_r30->pos.y;
                    sp2C.z = temp_r30->pos.z + (frandmod(50) - 25);
                    CreateEffectDust(temp_r25, sp2C.x, sp2C.y, sp2C.z, frandmod(10) + 30, &effectDustParam);
                }
                if (temp_r27[3] != -1) {
                    for (i = 0; i < 2; i++) {
                        if (lbl_80131146[temp_r28 * 2 + i] == temp_r26 * 2) {
                            HuAudFXPlay(lbl_8013117C[temp_r28]);
                            break;
                        }
                    }
                }
                break;
            case 2:
                if (temp_r28 != -1) {
                    if (!(temp_r26 & 0x1F) && !(lbl_801975B0[temp_r28] & 0x10)) {
                        effectDustParam.unk0C.x = 2.0 * -sind(temp_r30->rot.y);
                        effectDustParam.unk0C.y = 1.0 + 0.1 * frandmod(10);
                        effectDustParam.unk0C.z = 2.0 * -cosd(temp_r30->rot.y);
                        sp2C.x = temp_r30->pos.x + (frandmod(50) - 25);
                        sp2C.y = temp_r30->pos.y;
                        sp2C.z = temp_r30->pos.z + (frandmod(50) - 25);
                        CreateEffectDust(temp_r25, sp2C.x, sp2C.y, sp2C.z, frandmod(10) + 30, &effectDustParam);
                    }
                    for (i = 0; i < 2; i++) {
                        if (lbl_8013118E[temp_r28 * 2 + i] == temp_r26 * 2) {
                            HuAudFXPlay(lbl_8013119C[temp_r28]);
                            break;
                        }
                    }
                }
                break;
            case 3:
                if (temp_r28 != -1) {
                    if (!(temp_r26 & 3) && !(lbl_801975B0[temp_r28] & 0x10)) {
                        effectDustParam.unk0C.x = 2.0 * -sind(temp_r30->rot.y);
                        effectDustParam.unk0C.y = 1.0 + 0.1 * frandmod(10);
                        effectDustParam.unk0C.z = 2.0 * -cosd(temp_r30->rot.y);
                        sp2C.x = temp_r30->pos.x + (frandmod(50) - 25);
                        sp2C.y = temp_r30->pos.y;
                        sp2C.z = temp_r30->pos.z + (frandmod(50) - 25);
                        CreateEffectDust(temp_r25, sp2C.x, sp2C.y, sp2C.z, frandmod(10) + 30, &effectDustParam);
                    }
                    for (i = 0; i < 2; i++) {
                        if (lbl_801311AA[temp_r28 * 2 + i] == temp_r26 * 2) {
                            HuAudFXPlay(lbl_801311B8[temp_r28]);
                            break;
                        }
                    }
                }
                break;
            case 4:
                if (temp_r28 != -1) {
                    if (!(temp_r26 & 7) && !(lbl_801975B0[temp_r28] & 0x10)) {
                        effectDustParam.unk0C.x = 2.0 * -sind(temp_r30->rot.y);
                        effectDustParam.unk0C.y = 1.0 + 0.1 * frandmod(10);
                        effectDustParam.unk0C.z = 2.0 * -cosd(temp_r30->rot.y);
                        sp2C.x = temp_r30->pos.x + (frandmod(50) - 25);
                        sp2C.y = temp_r30->pos.y;
                        sp2C.z = temp_r30->pos.z + (frandmod(50) - 25);
                        CreateEffectDust(temp_r25, sp2C.x, sp2C.y, sp2C.z, frandmod(10) + 30, &effectDustParam);
                    }
                    for (i = 0; i < 2; i++) {
                        if (lbl_801311C6[temp_r28 * 2 + i] == temp_r26 * 2) {
                            HuAudFXPlay(lbl_801311D4[temp_r28]);
                            break;
                        }
                    }
                }
                break;
            case 5:
                if (temp_r26 != 0) {
                    break;
                }
                if (lbl_801975B0[temp_r28] & 0x10) {
                    break;
                }
                for (i = 0; i < 8; i++) {
                    effectStarParam.unk0C.x = 10.0 * sind(45.0f * i) * temp_r30->scale.x;
                    effectStarParam.unk0C.y = 0.0f;
                    effectStarParam.unk0C.z = 10.0 * cosd(45.0f * i) * temp_r30->scale.x;
                    CreateEffectStar(temp_r25, temp_r30->pos.x, temp_r30->pos.y + 10.0f * temp_r30->scale.x, temp_r30->pos.z, 40.0f, &effectStarParam);
                }
                for (i = 0; i < 8; i++) {
                    effectDustParam.unk0C.x = 4.0 * sind(45.0f * i + 22.5) * temp_r30->scale.x;
                    effectDustParam.unk0C.y = 0.0f;
                    effectDustParam.unk0C.z = 4.0 * cosd(45.0f * i + 22.5) * temp_r30->scale.x;
                    CreateEffectDust(temp_r25, temp_r30->pos.x, temp_r30->pos.y + 10.0f * temp_r30->scale.x, temp_r30->pos.z, 20.0f, &effectDustParam);
                }
                if (temp_r28 != -1) {
                    HuAudFXPlay(0x61);
                }
                break;
        }
    }
}

void CharModelStepTypeSet(s16 character, s32 arg1) {
    UnkCharInstanceStruct *temp_r31 = &charInstance[character];

    temp_r31->unkB0 = arg1;
}

static s32 PlayStepFX(s16 character, s16 arg1, u8 arg2) {
    UnkCharInstanceStruct *temp_r31;
    ModelData *var_r28;

    temp_r31 = &charInstance[character];
    var_r28 = &Hu3DData[temp_r31->unk00];
    if (arg2 & 1) {
        return;
    }
    if (temp_r31->unkB0 == 4) {
        arg1 = 0x109;
    } else if (temp_r31->unkB0 == 5) {
        arg1 = 0x10B;
    } else {
        arg1 += temp_r31->unkB0;
    }
    if (temp_r31->unkAC & 8) {
        return HuAudCharVoicePlayPos(character, arg1, &var_r28->pos);
    } else {
        return HuAudCharVoicePlay(character, arg1);
    }
}
