#include "REL/executor.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/wipe.h"

#include "game/gamework_data.h"

#include "game/mapspace.h"
#include "game/pad.h"
#include "game/printfunc.h"

#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "game/esprite.h"
#include "game/sprite.h"

#include "ext_math.h"
#include "version.h"

#undef ABS
#define ABS(x) ((0 > (x)) ? -(x) : (x))

typedef struct unk_bss_358_struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ struct unk_bss_358_struct *unk04;
    /* 0x08 */ struct unk_bss_358_struct *unk08;
} UnkBss358Struct; // Size 0xC

typedef struct unk_bss_340_struct {
    /* 0x00 */ HsfanimStruct00 *unk00;
    /* 0x04 */ s32 *unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ struct unk_bss_340_struct *unk10;
    /* 0x14 */ struct unk_bss_340_struct *unk14;
} UnkBss340Struct; // Size 0x18

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ s16 unk04;
} UnkBss1B0Struct; // Size 8

UnkBss358Struct lbl_1_bss_358;
UnkBss340Struct lbl_1_bss_340;
Process *lbl_1_bss_33C;
Vec lbl_1_bss_330;
Vec lbl_1_bss_324;
Vec lbl_1_bss_318;
Vec lbl_1_bss_30C;
u32 lbl_1_bss_308;
s32 lbl_1_bss_304;
u32 lbl_1_bss_300;
s16 lbl_1_bss_2FE;
s16 lbl_1_bss_2FC;
s32 lbl_1_bss_2F8;
s32 lbl_1_bss_2F4;
float lbl_1_bss_2F0;
s32 lbl_1_bss_2B0[16];
UnkBss1B0Struct lbl_1_bss_1B0[32];

void fn_1_0(void)
{
    lbl_1_bss_358.unk04 = NULL;
    lbl_1_bss_358.unk08 = NULL;
}

void fn_1_24(u16 arg0, s16 arg1)
{
    UnkBss358Struct *temp_r31;
    UnkBss358Struct *temp_r30;
    UnkBss358Struct *temp_r29;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r31), MEMORY_DEFAULT_NUM);
    temp_r31->unk00 = arg0;
    temp_r31->unk02 = arg1;
    temp_r30 = &lbl_1_bss_358;
    temp_r29 = temp_r30->unk08;
    temp_r30->unk08 = temp_r31;
    if (NULL != temp_r29) {
        temp_r29->unk04 = temp_r31;
    }
    temp_r31->unk04 = temp_r30;
    temp_r31->unk08 = temp_r29;
}

s16 fn_1_AC(s16 arg0)
{
    UnkBss358Struct *var_r31;
    UnkBss358Struct *temp_r29;
    UnkBss358Struct *temp_r30;
    s16 temp_r28;

    var_r31 = lbl_1_bss_358.unk08;
    while (NULL != var_r31) {
        if (arg0 == var_r31->unk00) {
            temp_r28 = var_r31->unk02;
            temp_r29 = var_r31->unk04;
            temp_r30 = var_r31->unk08;
            temp_r29->unk08 = temp_r30;
            if (NULL != temp_r30) {
                temp_r30->unk04 = temp_r29;
            }
            HuMemDirectFree(var_r31);
            return temp_r28;
        }
        var_r31 = var_r31->unk08;
    }
    return -1;
}

void fn_1_150(void)
{
    lbl_1_bss_340.unk10 = NULL;
    lbl_1_bss_340.unk14 = NULL;
}

void fn_1_174(s16 arg0, HsfanimStruct00 *arg1, s32 arg2, s32 arg3, s32 arg4, Vec *arg5, u8 arg6)
{
    UnkBss340Struct *temp_r27;
    UnkBss340Struct *var_r31;
    UnkBss340Struct *temp_r28;
    s32 i;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*var_r31), MEMORY_DEFAULT_NUM);
    var_r31->unk00 = arg1;
    var_r31->unk08 = arg3;
    var_r31->unk0C = arg4;
    var_r31->unk04 = HuMemDirectMallocNum(HEAP_SYSTEM, arg4 * sizeof(*var_r31->unk04), MEMORY_DEFAULT_NUM);
    for (i = 0; i < arg4; i++, arg5++) {
        var_r31->unk04[i] = Hu3DParManLink(arg0, arg1);
        if (var_r31->unk04[i] >= 0) {
            Hu3DParManAttrReset(var_r31->unk04[i], 1);
            Hu3DParManPosSet(var_r31->unk04[i], arg5->x, arg5->y, arg5->z);
            Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(var_r31->unk04[i]), arg6);
            Hu3DModelLayerSet(Hu3DParManModelIDGet(var_r31->unk04[i]), arg2);
        }
    }
    temp_r28 = &lbl_1_bss_340;
    temp_r27 = temp_r28->unk14;
    temp_r28->unk14 = var_r31;
    if (NULL != temp_r27) {
        temp_r27->unk10 = var_r31;
    }
    var_r31->unk10 = temp_r28;
    var_r31->unk14 = temp_r27;
}

void fn_1_2D8(void)
{
    UnkBss340Struct *var_r31;
    UnkBss340Struct *temp_r28;
    UnkBss340Struct *temp_r29;
    s32 i;

    var_r31 = lbl_1_bss_340.unk14;
    while (NULL != var_r31) {
        var_r31->unk08--;
        if (var_r31->unk08 == 0) {
            for (i = 0; i < var_r31->unk0C; i++) {
                if (var_r31->unk04[i] >= 0) {
                    Hu3DParManAttrSet(var_r31->unk04[i], 1);
                }
            }
        }
        temp_r28 = var_r31->unk10;
        temp_r29 = var_r31->unk14;
        if (-var_r31->unk00->unk00 > var_r31->unk08) {
            for (i = 0; i < var_r31->unk0C; i++) {
                if (var_r31->unk04[i] >= 0) {
                    Hu3DParManKill(var_r31->unk04[i]);
                }
            }
            temp_r28->unk14 = temp_r29;
            if (NULL != temp_r29) {
                temp_r29->unk10 = temp_r28;
            }
            HuMemDirectFree(var_r31->unk04);
            HuMemDirectFree(var_r31);
        }
        var_r31 = temp_r29;
    }
}

void fn_1_414(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        lbl_1_bss_1B0[i].unk00 = 0;
        lbl_1_bss_1B0[i].unk04 = -1;
    }
}

s16 fn_1_46C(s32 arg0)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        if (arg0 == lbl_1_bss_1B0[i].unk00) {
            return Hu3DModelLink(lbl_1_bss_1B0[i].unk04);
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_1_bss_1B0[i].unk00 == 0) {
            lbl_1_bss_1B0[i].unk00 = arg0;
            lbl_1_bss_1B0[i].unk04 = Hu3DModelCreateFile(arg0);
            return lbl_1_bss_1B0[i].unk04;
        }
    }
    return Hu3DModelCreateFile(arg0);
}

void fn_1_580(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 var_r30;

    espBankSet(arg0[arg1 + 1], 10);
    espBankSet(arg0[arg1 + 4], 11);
    if (600 * REFRESH_RATE <= arg2) {
        arg2 = 600 * REFRESH_RATE - 1;
    }
    var_r30 = arg2 / (60 * REFRESH_RATE);
    arg2 -= var_r30 * (60 * REFRESH_RATE);
    if (var_r30 > 9) {
        var_r30 = 9;
    }
    espBankSet(arg0[arg1], var_r30);
    var_r30 = arg2 / REFRESH_RATE;
    arg2 -= var_r30 * REFRESH_RATE;
    espBankSet(arg0[arg1 + 2], var_r30 / 10);
    espBankSet(arg0[arg1 + 3], var_r30 % 10);
    var_r30 = 101.5f * arg2 / REFRESH_RATE;
    espBankSet(arg0[arg1 + 5], var_r30 / 10);
    espBankSet(arg0[arg1 + 6], var_r30 % 10);
}

void fn_1_798(s32 arg0)
{
    lbl_1_bss_2F0 = 0.0f;
    lbl_1_bss_300 = lbl_1_bss_304;
    GWMGRecordSet(arg0, lbl_1_bss_300);
    fn_1_580(lbl_1_bss_2B0, 7, lbl_1_bss_304);
}

void fn_1_9EC(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        espDispOn(lbl_1_bss_2B0[i]);
    }
}

void fn_1_A40(void)
{
    float temp_f31;
    s32 i;

    if (0.0f <= lbl_1_bss_2F0) {
        lbl_1_bss_2F0 += 16.0f;
        temp_f31 = 1.0 + 0.2f * sind(lbl_1_bss_2F0);
        for (i = 7; i <= 14; i++) {
            espScaleSet(lbl_1_bss_2B0[i], temp_f31, temp_f31);
        }
    }
}

void fn_1_B4C(float arg0, s32 arg1)
{
    float temp_f30;
    float temp_f31;
    s32 i;

    temp_f31 = 288.0f;
    temp_f30 = arg0;
    lbl_1_bss_2B0[15] = espEntry(arg1, 0, 0);
    espTPLvlSet(lbl_1_bss_2B0[15], 0.5f);
    espColorSet(lbl_1_bss_2B0[15], 0, 0, 0);
    espPosSet(lbl_1_bss_2B0[15], temp_f31, temp_f30);
    temp_f31 = 248.0f;
    temp_f30 = arg0 - 8.0f;
    lbl_1_bss_2B0[14] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 55), 0, 0);
    espPosSet(lbl_1_bss_2B0[14], temp_f31 - 18.0f, temp_f30);
    for (i = 7; i <= 13; i++) {
        lbl_1_bss_2B0[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 48), 0, 0);
        espPosSet(lbl_1_bss_2B0[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_2B0, 7, lbl_1_bss_300);
    temp_f31 = 248.0f;
    temp_f30 = arg0 + 8.0f;
    for (i = 0; i <= 6; i++) {
        lbl_1_bss_2B0[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 49), 0, 0);
        espPosSet(lbl_1_bss_2B0[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_2B0, 0, 0);
    for (i = 0; i < 16; i++) {
        espDrawNoSet(lbl_1_bss_2B0[i], 0);
        espDispOff(lbl_1_bss_2B0[i]);
        espAttrSet(lbl_1_bss_2B0[i], HUSPR_ATTR_NOANIM);
        espPriSet(lbl_1_bss_2B0[i], 0x80 + i);
    }
}

void fn_1_11F4(float arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    float temp_f31;

    if (1.0f < arg0) {
        arg0 = 1.0f;
    }
    temp_f31 = sind(90.0f * arg0) * sind(90.0f * arg0);
    arg3->x = arg1->x + temp_f31 * (arg2->x - arg1->x);
    arg3->y = arg1->y + temp_f31 * (arg2->y - arg1->y);
    arg3->z = arg1->z + temp_f31 * (arg2->z - arg1->z);
}

void fn_1_1350(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Hu3DCameraPosSetV(1, arg0, arg1, arg2);
    lbl_1_bss_330 = *arg0;
    lbl_1_bss_318 = *arg2;
}

s32 fn_1_13DC(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_330, &lbl_1_bss_324, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_318, &lbl_1_bss_30C, &spC);
    Hu3DCameraPosSetV(1, &sp18, arg1, &spC);
    if (1.0f <= arg0) {
        return 1;
    }
    else {
        lbl_1_bss_2F4 = 1;
        return 0;
    }
}

void fn_1_1710(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_330, &lbl_1_bss_324, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_318, &lbl_1_bss_30C, &spC);
    fn_1_1350(&sp18, arg1, &spC);
    lbl_1_bss_2F4 = 1;
}

void fn_1_1A60(Vec *arg0, s16 arg1, Vec *arg2)
{
    Mtx sp1C;
    Vec sp10;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f31;
    CameraData *temp_r31;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            break;
        }
    }
    temp_r31 = &Hu3DCamera[i];
    MTXLookAt(sp1C, &temp_r31->pos, &temp_r31->up, &temp_r31->target);
    MTXMultVec(sp1C, arg0, &sp10);
    temp_f30 = sp10.z * (sind(temp_r31->fov / 2) / cosd(temp_r31->fov / 2)) * temp_r31->aspect;
    temp_f29 = sp10.z * (sind(temp_r31->fov / 2) / cosd(temp_r31->fov / 2));
    temp_f28 = 0.9f * temp_r31->viewport_x;
    temp_f31 = 0.9f * temp_r31->viewport_w;
    arg2->x = temp_f31 / 2 + sp10.x * ((temp_f31 / 2) / -temp_f30) + temp_f28;
    arg2->y = temp_r31->viewport_h / 2 + sp10.y * ((temp_r31->viewport_h / 2) / temp_f29) + temp_r31->viewport_y;
    arg2->z = 0.0f;
}

void fn_1_1D18(s16 arg0, char *arg1, Vec *arg2)
{
    Mtx sp10;

    Hu3DModelObjMtxGet(arg0, arg1, sp10);
    arg2->x = sp10[0][3];
    arg2->y = sp10[1][3];
    arg2->z = sp10[2][3];
}

void fn_1_1D70(s16 arg0, char *arg1, Vec *arg2, Mtx arg3)
{
    Mtx spC;
    ModelData *var_r30;

    var_r30 = &Hu3DData[arg0];
    Hu3DModelObjMtxGet(arg0, arg1, spC);
    MTXConcat(var_r30->unk_F0, spC, spC);
    if (NULL != arg3) {
        MTXCopy(spC, arg3);
    }
    arg2->x = spC[0][3];
    arg2->y = spC[1][3];
    arg2->z = spC[2][3];
}

float fn_1_1E20(float arg0, float arg1, float arg2)
{
    float var_f31;
    float var_f30;

    var_f31 = fmod(arg1 - arg0, 360.0);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg0 + var_f31 * arg2, 360.0);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

void fn_1_1F24(s32 arg0)
{
    lbl_1_bss_2F8 = HuAudSeqPlay((s32)arg0);
}

void fn_1_1F58(s32 arg0)
{
    if (lbl_1_bss_2F8 >= 0) {
        if (arg0 < 0) {
            arg0 = 1000;
        }
        HuAudSeqFadeOut(lbl_1_bss_2F8, arg0);
    }
    lbl_1_bss_2F8 = -1;
}

void fn_1_1FC4(Vec *arg0, float *arg1, s32 arg2, s32 arg3)
{
    Vec sp18;
    float var_f28;
    s32 var_r30;

    sp18.x = 0.0f;
    sp18.y = 0.0f;
    sp18.z = 0.0f;
    sp18.x = arg2 / 4.0f;
    sp18.z = -(float)arg3 / 4.0f;
    var_r30 = 0;
    var_f28 = VECMagXZ(&sp18);
    if (0.5f <= var_f28) {
        if (10.0f <= var_f28) {
            sp18.x /= var_f28;
            sp18.z /= var_f28;
            var_f28 = 10.0f;
            sp18.x = 10.0f * sp18.x;
            sp18.z = 10.0f * sp18.z;
        }
        *arg1 = fn_1_1E20(*arg1, atan2d(sp18.x, sp18.z), 0.4f);
        if (8.0f <= var_f28) {
            var_r30 = 2;
        }
        else {
            var_r30 = 1;
        }
    }
    VECAdd((Vec *)&arg0, &sp18, (Vec *)&arg0);
}

typedef struct data_1340_sub_struct {
    char *unk0;
    s32 unk4;
    s32 unk8[4];
    Vec unk18;
} Data1340SubStruct;

typedef struct data_1340_struct {
    s32 unk0;
    s32 *unk4;
    s32 unk8[4];
    float unk18;
    s32 unk1C;
    Data1340SubStruct *unk20;
} Data1340Struct;

typedef struct data_13A8_struct {
    float unk0;
    float unk4;
    float unk8;
    s32 unkC;
} Data13A8Struct;

typedef struct bss_130_struct {
    s32 unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
    float unk14;
} Bss130Struct;

s16 lbl_1_data_0[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

Data1340SubStruct lbl_1_data_22C[] = {
    { "baseA2-null2", 1, { 13, 1, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null11", 0, { 10, 0, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null12", 0, { 6, 3, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null13", 8, { 20, 2, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null5", 16, { 14, 5, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null6", 0, { 9, 4, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null20", 128, { 2, -1, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null21", 128, { 8, -1, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null22", 0, { 19, 7, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null7", 0, { 5, 15, 10, -1 }, { 0, 0, 0 } },
    { "baseA2-null10", 16, { 1, 9, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null18", 0, { 17, 12, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null17", 0, { 18, 11, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null3", 0, { 0, 14, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null4", 0, { 4, 13, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null8", 0, { 9, 16, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null9", 0, { 22, 15, 17, -1 }, { 0, 0, 0 } },
    { "baseA2-null19", 0, { 11, 23, 16, -1 }, { 0, 0, 0 } },
    { "baseA2-null16", 0, { 12, 19, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null15", 0, { 8, 18, 20, -1 }, { 0, 0, 0 } },
    { "baseA2-null14", 0, { 3, 19, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null39", 0, { 30, 22, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null40", 0, { 16, 21, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null27", 0, { 17, 37, 24, -1 }, { 0, 0, 0 } },
    { "baseA2-null28", 64, { 32, 23, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null23", 64, { 33, 26, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null24", 0, { 38, 25, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null35", 0, { 31, 28, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null34", 32, { 35, 27, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null31", 32, { 36, -1, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null37", 0, { 21, 34, 31, -1 }, { 0, 0, 0 } },
    { "baseA2-null36", 0, { 27, 30, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null29", 0, { 24, 33, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null30", 0, { 25, 32, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null38", 2, { 30, 35, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null33", 0, { 28, 34, 36, -1 }, { 0, 0, 0 } },
    { "baseA2-null32", 0, { 29, 35, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null26", 0, { 23, 38, -1, -1 }, { 0, 0, 0 } },
    { "baseA2-null25", 4, { 26, 37, -1, -1 }, { 0, 0, 0 } },
};

Data1340SubStruct lbl_1_data_9EC[] = {
    { "baseB2-null1", 1, { 12, 1, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null2", 0, { 8, 0, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null6", 0, { 9, 3, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null10", 0, { 15, 2, 4, -1 }, { 0, 0, 0 } },
    { "baseB2-null11", 0, { 10, 3, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null12", 0, { 11, 6, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null13", 8, { 18, 5, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null7", 16, { 14, -1, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null4", 16, { 1, 9, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null5", 0, { 2, 8, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null14", 128, { 4, 11, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null15", 0, { 5, 10, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null3", 0, { 0, 13, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null9", 0, { 21, 12, 14, -1 }, { 0, 0, 0 } },
    { "baseB2-null8", 0, { 7, 13, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null16", 0, { 3, 16, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null17", 0, { 24, 15, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null18", 128, { 18, -1, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null19", 0, { 6, 17, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null20", 0, { 35, 20, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null21", 0, { 27, 19, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null30", 0, { 13, 22, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null29", 0, { 38, 21, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null31", 0, { 32, 24, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null33", 0, { 16, 23, 25, -1 }, { 0, 0, 0 } },
    { "baseB2-null34", 0, { 30, 24, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null42", 64, { 34, -1, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null25", 0, { 20, 28, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null26", 32, { 37, 27, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null36", 0, { 39, 30, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null35", 0, { 25, 33, 29, -1 }, { 0, 0, 0 } },
    { "baseB2-null24", 32, { 36, -1, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null32", 64, { 23, -1, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null38", 0, { 30, 40, 34, -1 }, { 0, 0, 0 } },
    { "baseB2-null40", 0, { 26, 33, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null22", 2, { 19, 36, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null23", 0, { 31, 35, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null27", 0, { 28, 38, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null28", 0, { 22, 37, 39, -1 }, { 0, 0, 0 } },
    { "baseB2-null37", 0, { 29, 38, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null39", 0, { 33, 41, -1, -1 }, { 0, 0, 0 } },
    { "baseB2-null41", 4, { 40, -1, -1, -1 }, { 0, 0, 0 } },
};

Vec lbl_1_data_FD4 = { 0, 1, -1 };
Vec lbl_1_data_FE0 = { 0, 1, 0 };
s32 lbl_1_data_FEC[4] = { 1, 2, 4, 8 };
float lbl_1_data_FFC[4][4] = { 0, 0, 320, 240, 0, 240, 320, 240, 320, 0, 320, 240, 320, 240, 320, 240 };
float lbl_1_data_103C[4][4] = { 2, 2, 316, 236, 2, 242, 316, 236, 322, 2, 316, 236, 322, 242, 316, 236 };

float lbl_1_data_107C[4][4] = { 0, 0, 640, 480, 0, 480, 640, 0, 640, 0, 0, 480, 640, 480, 0, 0 };

float lbl_1_data_10BC[4][4] = { 0, 0, 0, 480, 0, 480, 0, 0, 0, 0, 640, 480, 0, 480, 640, 0 };

float lbl_1_data_10FC[4][2] = { -1, -1, -1, 1, 1, -1, 1, 1 };

Vec lbl_1_data_111C = { 0, 10000, 0 };
Vec lbl_1_data_1128 = { 0, -1, 0 };
GXColor lbl_1_data_1134 = { 255, 255, 255, 255 };
Vec lbl_1_data_1138 = { 0, 8000, 1000 };
Vec lbl_1_data_1144 = { 0, 0, 0 };
s32 lbl_1_data_1150[8][10] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x72),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x5A),
    DATA_MAKE_NUM(DATADIR_M429, 0x08),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x58),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x59),
    DATA_MAKE_NUM(DATADIR_M429, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x72),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x5A),
    DATA_MAKE_NUM(DATADIR_M429, 0x09),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x58),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x59),
    DATA_MAKE_NUM(DATADIR_M429, 0x01),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x72),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x5A),
    DATA_MAKE_NUM(DATADIR_M429, 0x0A),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x58),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x59),
    DATA_MAKE_NUM(DATADIR_M429, 0x02),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x72),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x5A),
    DATA_MAKE_NUM(DATADIR_M429, 0x0B),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x58),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x59),
    DATA_MAKE_NUM(DATADIR_M429, 0x03),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x72),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x5A),
    DATA_MAKE_NUM(DATADIR_M429, 0x0C),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x58),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x59),
    DATA_MAKE_NUM(DATADIR_M429, 0x04),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x72),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x5A),
    DATA_MAKE_NUM(DATADIR_M429, 0x0D),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x58),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x59),
    DATA_MAKE_NUM(DATADIR_M429, 0x05),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x72),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x5A),
    DATA_MAKE_NUM(DATADIR_M429, 0x0E),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x58),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x59),
    DATA_MAKE_NUM(DATADIR_M429, 0x06),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x72),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x5A),
    DATA_MAKE_NUM(DATADIR_M429, 0x0F),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x58),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x59),
    DATA_MAKE_NUM(DATADIR_M429, 0x07),
};

s32 lbl_1_data_1290[8] = {
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x00),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x01),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x02),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x03),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x04),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x05),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x06),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x07),
};

s32 lbl_1_data_12B0[8] = {
    DATA_MAKE_NUM(DATADIR_M429, 0x2C),
    DATA_MAKE_NUM(DATADIR_M429, 0x2E),
    DATA_MAKE_NUM(DATADIR_M429, 0x2C),
    DATA_MAKE_NUM(DATADIR_M429, 0x2E),
    DATA_MAKE_NUM(DATADIR_M429, 0x2D),
    DATA_MAKE_NUM(DATADIR_M429, 0x2E),
    DATA_MAKE_NUM(DATADIR_M429, 0x2D),
    DATA_MAKE_NUM(DATADIR_M429, 0x2E),
};

s32 lbl_1_data_12D0[4] = {
    DATA_MAKE_NUM(DATADIR_M429, 0x3D),
    DATA_MAKE_NUM(DATADIR_M429, 0x3D),
    DATA_MAKE_NUM(DATADIR_M429, 0x3E),
    DATA_MAKE_NUM(DATADIR_M429, 0x3E),
};

s32 lbl_1_data_12E0[4][3] = {
    DATA_MAKE_NUM(DATADIR_M429, 0x24),
    DATA_MAKE_NUM(DATADIR_M429, 0x30),
    DATA_MAKE_NUM(DATADIR_M429, 0x25),
    DATA_MAKE_NUM(DATADIR_M429, 0x26),
    DATA_MAKE_NUM(DATADIR_M429, 0x30),
    DATA_MAKE_NUM(DATADIR_M429, 0x27),
    DATA_MAKE_NUM(DATADIR_M429, 0x28),
    DATA_MAKE_NUM(DATADIR_M429, 0x30),
    DATA_MAKE_NUM(DATADIR_M429, 0x29),
    DATA_MAKE_NUM(DATADIR_M429, 0x2A),
    DATA_MAKE_NUM(DATADIR_M429, 0x30),
    DATA_MAKE_NUM(DATADIR_M429, 0x2B),
};

s32 lbl_1_data_1310[4] = {
    DATA_MAKE_NUM(DATADIR_M429, 0x3A),
    DATA_MAKE_NUM(DATADIR_M429, 0x3A),
    DATA_MAKE_NUM(DATADIR_M429, 0x3B),
    DATA_MAKE_NUM(DATADIR_M429, 0x3B),
};

s32 lbl_1_data_1320[4] = {
    DATA_MAKE_NUM(DATADIR_M429, 0x13),
    DATA_MAKE_NUM(DATADIR_M429, 0x16),
    DATA_MAKE_NUM(DATADIR_M429, 0x15),
    DATA_MAKE_NUM(DATADIR_M429, 0x14),
};

s32 lbl_1_data_1330[4] = {
    DATA_MAKE_NUM(DATADIR_M429, 0x1C),
    DATA_MAKE_NUM(DATADIR_M429, 0x1F),
    DATA_MAKE_NUM(DATADIR_M429, 0x1E),
    DATA_MAKE_NUM(DATADIR_M429, 0x1D),
};

Data1340Struct lbl_1_data_1340[2] = {
    {
        0,
        lbl_1_data_1320,
        {
            DATA_MAKE_NUM(DATADIR_M429, 0x10),
            DATA_MAKE_NUM(DATADIR_M429, 0x11),
            DATA_MAKE_NUM(DATADIR_M429, 0x17),
            DATA_MAKE_NUM(DATADIR_M429, 0x18),
        },
        13000,
        39,
        lbl_1_data_22C,
    },
    {
        4,
        lbl_1_data_1330,
        {
            DATA_MAKE_NUM(DATADIR_M429, 0x19),
            DATA_MAKE_NUM(DATADIR_M429, 0x1A),
            DATA_MAKE_NUM(DATADIR_M429, 0x20),
            DATA_MAKE_NUM(DATADIR_M429, 0x21),
        },
        13000,
        42,
        lbl_1_data_9EC,
    },
};

s32 lbl_1_data_1388[8] = {
    DATA_MAKE_NUM(DATADIR_M429, 0x32),
    DATA_MAKE_NUM(DATADIR_M429, 0x33),
    DATA_MAKE_NUM(DATADIR_M429, 0x34),
    DATA_MAKE_NUM(DATADIR_M429, 0x35),
    DATA_MAKE_NUM(DATADIR_M429, 0x36),
    DATA_MAKE_NUM(DATADIR_M429, 0x37),
    DATA_MAKE_NUM(DATADIR_M429, 0x38),
    DATA_MAKE_NUM(DATADIR_M429, 0x39),
};

Data13A8Struct lbl_1_data_13A8 = { 0.5f, 100.0f, 130.0f, 15 };

Data13A8Struct lbl_1_data_13B8 = { 0.6f, 110.0f, 120.0f, 12 };

Data13A8Struct lbl_1_data_13C8 = { 0.7f, 120.0f, 110.0f, 9 };

Data13A8Struct lbl_1_data_13D8 = { 0.8f, 130.0f, 100.0f, 6 };

HsfanimStruct00 lbl_1_data_13E8 = {
    30,
    { 0, 0 },
    1.0f,
    10.0f,
    360.0f,
    { 0.0f, 0.1f, 0.0f },
    1.0f,
    1.0f,
    30.0f,
    1.05f,
    1,
    {
        { 255, 255, 255, 255 },
        { 255, 255, 255, 255 },
        { 255, 255, 255, 255 },
        { 255, 255, 255, 255 },
    },
    {
        { 255, 255, 255, 0 },
        { 255, 255, 255, 0 },
        { 255, 255, 255, 0 },
        { 255, 255, 255, 0 },
    },
};

omObjData *lbl_1_bss_1AC;
omObjData *lbl_1_bss_1A8;
omObjData **lbl_1_bss_1A4;
omObjData **lbl_1_bss_1A0;
omObjData **lbl_1_bss_19C;
omObjData **lbl_1_bss_198;
s32 lbl_1_bss_194;
Data1340Struct *lbl_1_bss_190;
Bss130Struct lbl_1_bss_130[4];
float lbl_1_bss_12C;
float lbl_1_bss_128;
float lbl_1_bss_124;
float lbl_1_bss_120;
float lbl_1_bss_11C;
float lbl_1_bss_118;
float lbl_1_bss_114;
float lbl_1_bss_110;
Vec lbl_1_bss_F8[2];
Vec lbl_1_bss_C8[4];
Vec lbl_1_bss_98[4];
Vec lbl_1_bss_68[4];
Vec lbl_1_bss_38[4];
s32 lbl_1_bss_34;
s32 lbl_1_bss_2C[2];
s32 lbl_1_bss_28;
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s16 lbl_1_bss_1A;
s16 lbl_1_bss_10[5];
AnimData *lbl_1_bss_C;
s16 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

typedef struct work_8F68 {
    Data13A8Struct *unk0;
    Vec unk4;
    Vec unk10;
    Vec unk1C;
    Vec unk28;
    Vec unk34;
    Vec unk40;
    float unk4C;
    float unk50;
    float unk54;
    float unk58;
    float unk5C;
    float unk60;
    float unk64;
    float unk68;
    float unk6C;
    s32 unk70;
    u8 *unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    float unk90;
    u32 unk94[2];
    s32 unk9C;
    s32 unkA0;
    s32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s32 unkB4;
    s32 unkB8[4];
    s32 unkC8[4][2];
    s32 unkE8;
    s32 unkEC;
    s32 unkF0;
    s32 unkF4;
    s32 unkF8;
    s32 unkFC;
    s32 unk100;
    s32 unk104;
    s32 unk108;
    s32 unk10C;
    s32 unk110;
    s32 unk114;
    s32 unk118;
    s32 unk11C;
    s32 unk120;
} Work8F68;

void fn_1_23B4(void)
{
    Work8F68 *temp_r31;
    s32 temp_r30;
    HuSysVWaitSet(1);
    lbl_1_bss_11C -= HuPadSubStkX[0] / 59.0f;
    lbl_1_bss_120 -= 4 * (HuPadSubStkY[0] / 59.0f);
    lbl_1_bss_118 -= 4 * (HuPadTrigL[0] / 150.0f);
    lbl_1_bss_118 += 4 * (HuPadTrigR[0] / 150.0f);
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        temp_r31 = lbl_1_bss_1A4[temp_r30]->data;
        print8(24, 96 + (16 * temp_r30), 1.5f, "%d %d %d M%2d %04x %2d %2d %d %d", temp_r31->unk100, temp_r31->unk10C, temp_r31->unk104,
            temp_r31->unk8C, temp_r31->unkE8, temp_r31->unkEC, temp_r31->unkF0, temp_r31->unk80, temp_r31->unk8C);
    }
}

Data1340SubStruct *fn_1_2614(s32 arg0)
{
    Data1340SubStruct *temp_r31;
    s32 temp_r30;
    temp_r31 = lbl_1_bss_190->unk20;
    for (temp_r30 = 0; temp_r30 < lbl_1_bss_190->unk1C; temp_r30++, temp_r31++) {
        if (arg0 & temp_r31->unk4) {
            return temp_r31;
        }
    }
    return NULL;
}

void fn_1_2684(void)
{
    Data1340SubStruct *temp_r31;
    s32 temp_r30;

    s32 temp_r28;
    temp_r30 = frandmod(2);
    lbl_1_bss_190 = &lbl_1_data_1340[temp_r30];
    temp_r30 = Hu3DModelCreateFile(lbl_1_bss_190->unk8[0]);
    Hu3DModelAttrSet(temp_r30, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(temp_r30, 0, 0, 0);
    Hu3DModelRotSet(temp_r30, 0, -90.f * lbl_1_bss_34, 0);
    for (temp_r28 = 0; temp_r28 < lbl_1_bss_190->unk1C; temp_r28++) {
        fn_1_1D18(temp_r30, lbl_1_bss_190->unk20[temp_r28].unk0, &lbl_1_bss_190->unk20[temp_r28].unk18);
    }
    lbl_1_bss_128 = 2000;
    lbl_1_bss_124 = 2000;
    temp_r31 = fn_1_2614(1);
    if (NULL != temp_r31) {
        lbl_1_bss_128 = 2.0f * ABS(temp_r31->unk18.x);
        lbl_1_bss_124 = 2.2f * ABS(temp_r31->unk18.z);
    }
}

void fn_1_2950(Work8F68 *arg0)
{
    float temp_f31;
    float temp_f30;
    float temp_f28;
    float temp_f27;
    s32 temp_r31;
    Data1340SubStruct *temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    s32 temp_r26;
    temp_r28 = arg0->unkEC;
    temp_r31 = -1;
    temp_f27 = lbl_1_bss_190->unk18;
    temp_r30 = lbl_1_bss_190->unk20;
    for (temp_r29 = 0; temp_r29 < lbl_1_bss_190->unk1C; temp_r29++, temp_r30++) {
        temp_f31 = arg0->unk4.x - temp_r30->unk18.x;
        temp_f30 = arg0->unk4.z - temp_r30->unk18.z;
        temp_f28 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
        if (arg0->unk54 + 200.0f > temp_f28 && temp_f27 > temp_f28) {
            temp_r31 = temp_r29;
            temp_f27 = temp_f28;
        }
    }
    if (temp_r31 >= 0) {
        arg0->unkEC = temp_r31;
        if (temp_r28 != temp_r31) {
            if (--arg0->unk8C < 0) {
                arg0->unk8C = -1;
            }
        }
        temp_r27 = temp_r31 / 32;
        temp_r26 = temp_r31 % 32;
        arg0->unk94[temp_r27] |= 1 << temp_r26;
    }
}

void fn_1_2BE0(Work8F68 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4, s32 *arg5)
{
    s32 sp8[2];
    s32 temp_r31;
    Data1340SubStruct *temp_r30;
    s32 temp_r29;
    u8 *temp_r27;

    s32 temp_r24;
    s32 temp_r23;
    temp_r24 = arg1 / 32;
    temp_r23 = arg1 % 32;
    arg5[temp_r24] |= 1 << temp_r23;
    temp_r27 = HuMemDirectMallocNum(HEAP_SYSTEM, arg3 + 1, MEMORY_DEFAULT_NUM);
    for (temp_r31 = 0; temp_r31 < arg3; temp_r31++) {
        temp_r27[temp_r31] = arg4[temp_r31];
    }
    temp_r30 = &lbl_1_bss_190->unk20[arg1];
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        if (temp_r30->unk8[temp_r31] < 0) {
            break;
        }
        temp_r27[arg3] = temp_r30->unk8[temp_r31];
        if (arg2 == temp_r30->unk8[temp_r31]) {
            if (arg0->unk78 > arg3 + 1) {
                if (NULL != arg0->unk74) {
                    HuMemDirectFree(arg0->unk74);
                }
                arg0->unk74 = HuMemDirectMallocNum(HEAP_SYSTEM, arg3 + 1, MEMORY_DEFAULT_NUM);
                for (temp_r29 = 0; temp_r29 < arg3 + 1; temp_r29++) {
                    arg0->unk74[temp_r29] = temp_r27[temp_r29];
                }
                arg0->unk78 = arg3 + 1;
            }
        }
        else {
            if (temp_r30->unk8[temp_r31] >= 0) {
                temp_r24 = temp_r30->unk8[temp_r31] / 32;
                temp_r23 = temp_r30->unk8[temp_r31] % 32;
                if ((arg5[temp_r24] & (1 << temp_r23)) == 0u) {
                    for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
                        sp8[temp_r29] = arg5[temp_r29];
                    }
                    fn_1_2BE0(arg0, temp_r30->unk8[temp_r31], arg2, arg3 + 1, temp_r27, sp8);
                }
            }
        }
    }
    HuMemDirectFree(temp_r27);
}

void fn_1_2E14(Work8F68 *arg0)
{
    s32 spC[2];
    u8 sp8;
    s32 temp_r30;
    if (NULL != arg0->unk74) {
        HuMemDirectFree(arg0->unk74);
    }
    arg0->unk74 = NULL;
    arg0->unk78 = 65535;
    arg0->unk7C = 0;
    if (arg0->unkEC == arg0->unkF0) {
        arg0->unkE8 |= 0x8;
        arg0->unkF0 = -1;
        return;
    }
    sp8 = arg0->unkEC;
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        spC[temp_r30] = 0;
    }
    fn_1_2BE0(arg0, arg0->unkEC, arg0->unkF0, 1, &sp8, spC);
}

void fn_1_2EEC(Work8F68 *arg0)
{
    Vec sp18;
    Vec spC;
    float temp_f31;
    float temp_f30;
    float temp_f28;
    Data1340SubStruct *temp_r30;
    Data1340SubStruct *temp_r29;

    if (NULL != arg0->unk74 && arg0->unk78 >= 2) {
        temp_r30 = &lbl_1_bss_190->unk20[arg0->unk74[0]];
        temp_r29 = &lbl_1_bss_190->unk20[arg0->unk74[1]];
        temp_f31 = temp_r30->unk18.x - arg0->unk4.x;
        temp_f30 = temp_r30->unk18.z - arg0->unk4.z;
        temp_f28 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
        if (150.0f > temp_f28) {
            arg0->unk7C = 1;
            return;
        }
        VECSubtract(&temp_r29->unk18, &temp_r30->unk18, &sp18);
        VECSubtract(&arg0->unk4, &temp_r30->unk18, &spC);
        if (0.0f != VECMag(&sp18) && 0.0f != VECMag(&spC)) {
            VECNormalize(&sp18, &sp18);
            VECNormalize(&spC, &spC);
            if (0.8f < VECDotProduct(&sp18, &spC)) {
                arg0->unk7C = 1;
            }
        }
    }
}

void fn_1_31A8(omObjData *object) { }

void fn_1_31AC(omObjData *object)
{
    object->model[0] = Hu3DModelCreateFile(lbl_1_bss_190->unk4[lbl_1_bss_34]);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    omSetTra(object, 0, 0, 0);
    omSetRot(object, 0, 0, 0);
    object->func = fn_1_31A8;
}

typedef struct work_3284 {
    Vec unk0;
    float unkC;
    float unk10;
    s32 unk14;
    s32 unk18;
} Work3284;

void fn_1_3284(omObjData *object)
{
    Work3284 *temp_r31 = object->data;
    if (lbl_1_bss_1AC->work[0] >= 1007) {
        temp_r31->unk10 *= 0.9f;
        if (0.0f > temp_r31->unk10) {
            temp_r31->unk10 = 0.0f;
        }
    }
    else {
        if (temp_r31->unk18 & 0x1) {
            temp_r31->unkC += 6.0f;
            if (180.0f < temp_r31->unkC) {
                temp_r31->unkC = 180.0f;
            }
            temp_r31->unk10 = 1.0 - (0.5 * sind(temp_r31->unkC));
        }
    }
    omSetSca(object, temp_r31->unk10, temp_r31->unk10, temp_r31->unk10);
    Hu3DModelScaleSet(object->model[1], temp_r31->unk10, temp_r31->unk10, temp_r31->unk10);
    Hu3DModelScaleSet(object->model[0], temp_r31->unk10, temp_r31->unk10, temp_r31->unk10);
}

void fn_1_33F8(omObjData *object)
{
    Work3284 *temp_r31 = object->data;
    s32 temp_r29;
    s32 temp_r28;
    s32 *temp_r27;
    Data1340SubStruct *temp_r26;
    s32 temp_r25;
    s32 temp_r24;

    temp_r31->unk0.x = 0;
    temp_r31->unk0.y = 0;
    temp_r31->unk0.z = 0;
    temp_r31->unkC = 0;
    temp_r31->unk10 = 1;
    temp_r31->unk14 = -1;
    temp_r31->unk18 = 0;
    temp_r24 = 16 << ((object->work[0] + lbl_1_bss_34 + 2) & 0x3);
    temp_r25 = frandmod(lbl_1_bss_190->unk1C) + 1;
    temp_r28 = frandmod(lbl_1_bss_190->unk1C);
    while (1) {
        temp_r26 = &lbl_1_bss_190->unk20[temp_r28];
        if ((temp_r24 & temp_r26->unk4) && --temp_r25 < 0) {
            temp_r31->unk14 = temp_r28;
            temp_r31->unk0 = temp_r26->unk18;
            break;
        }
        else {
            temp_r28 = (temp_r28 + 1) % lbl_1_bss_190->unk1C;
        }
    }
    temp_r31->unk0.y = 100;
    temp_r27 = &lbl_1_data_12B0[object->work[0] * 2];
    object->model[0] = Hu3DModelCreateFile(*temp_r27++);
    object->model[1] = Hu3DModelCreateFile(*temp_r27++);
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
        Hu3DModelCameraSet(object->model[temp_r29], 15);
        Hu3DModelAttrSet(object->model[temp_r29], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[temp_r29], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(object->model[temp_r29], HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(object->model[temp_r29], 3);
        Hu3DModelPosSet(object->model[temp_r29], temp_r31->unk0.x, temp_r31->unk0.y, temp_r31->unk0.z);
        Hu3DModelRotSet(object->model[temp_r29], 0, 0, 0);
        Hu3DModelShadowSet(object->model[temp_r29]);
    }
    omSetTra(object, temp_r31->unk0.x, temp_r31->unk0.y, temp_r31->unk0.z);
    omSetRot(object, 0, 0, 0);
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    object->func = fn_1_3284;
}

s32 fn_1_36FC(Work8F68 *arg0)
{
    AddX = 0;
    AddZ = 0;
    MapWall(arg0->unk54, arg0->unk4.x, arg0->unk4.y + arg0->unk54, arg0->unk4.z);

    arg0->unk4.x += AddX;
    arg0->unk4.z += AddZ;
    if (0.0f != ABS(AddX) + ABS(AddZ)) {
        arg0->unk108 = 1;
        return 1;
    }
    else {
        return 0;
    }
}

static inline void VECSet(Vec *dst, float x, float y, float z)
{
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

void fn_1_386C(Work8F68 *arg0)
{
    Vec sp18;
    Vec spC;
    float temp_f31;
    float temp_f30;
    float temp_f28;

    Work8F68 *temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    temp_r28 = 0;
    temp_r27 = 0;
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        temp_r30 = lbl_1_bss_1A4[temp_r29]->data;
        if (arg0->unk114 == temp_r30->unk114) {
            continue;
        }
        temp_f31 = arg0->unk4.x - temp_r30->unk4.x;
        temp_f30 = arg0->unk4.z - temp_r30->unk4.z;
        temp_f28 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
        if (temp_f28 < arg0->unk54 + temp_r30->unk54) {
            if (0.0f == temp_f28) {
                temp_f31 = 0;
                temp_f30 = -1;
            }
            else {
                temp_f31 /= temp_f28;
                temp_f30 /= temp_f28;
            }
            temp_r27++;
            arg0->unk4.x = temp_r30->unk4.x + (temp_f31 * (arg0->unk54 + temp_r30->unk54));
            arg0->unk4.z = temp_r30->unk4.z + (temp_f30 * (arg0->unk54 + temp_r30->unk54));
            fn_1_36FC(arg0);
            VECSet(&sp18, arg0->unkF4, 0, arg0->unkF8);
            VECSet(&spC, temp_r30->unkF4, 0, temp_r30->unkF8);
            if (0.0f != VECMag(&sp18) && 0.0f != VECMag(&spC)) {
                VECNormalize(&sp18, &sp18);
                VECNormalize(&spC, &spC);
                if (-0.8f > VECDotProduct(&sp18, &spC)) {
                    temp_r28++;
                }
            }
        }
    }
    if (temp_r28 != 0 || temp_r27 >= 2) {
        arg0->unk100++;
        arg0->unk10C++;
    }
    else {
        arg0->unk10C = 0;
    }
}

void fn_1_3DCC(Work8F68 *arg0)
{
    float temp_f31;
    float temp_f30;
    float temp_f28;
    Work3284 *temp_r31;
    s32 temp_r30;
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        temp_r31 = lbl_1_bss_19C[temp_r30]->data;
        temp_f31 = arg0->unk4.x - temp_r31->unk0.x;
        temp_f30 = arg0->unk4.z - temp_r31->unk0.z;
        temp_f28 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
        if (temp_f28 < arg0->unk54 + 50) {
            if (0.0f == temp_f28) {
                temp_f31 = 0;
                temp_f30 = -1;
            }
            else {
                temp_f31 /= temp_f28;
                temp_f30 /= temp_f28;
            }
            arg0->unk4.x = temp_r31->unk0.x + (temp_f31 * (arg0->unk54 + 50));
            arg0->unk4.z = temp_r31->unk0.z + (temp_f30 * (arg0->unk54 + 50));
        }
    }
}

#ifdef __MWERKS__
#include "src/REL/executor.c"
#endif

void fn_1_40C0(Work8F68 *arg0, omObjData *arg1, s32 arg2)
{
    float temp_f31;

    s32 temp_r29;
    if (arg2 >= 0 && arg0->unkA8 != arg2) {
        arg0->unkA8 = arg2;
        Hu3DMotionShiftSet(arg1->model[0], arg1->motion[arg0->unkA8], 0, 8, HU3D_MOTATTR_LOOP);
        temp_r29 = -1;
        temp_f31 = 1;
        if (arg0->unkA4 == 1) {
            temp_r29 = 9;
        }
        if (arg0->unkA4 == 0) {
            switch (arg0->unkA8) {
                case 0:
                    temp_r29 = 7;
                    break;

                case 1:
                    temp_r29 = 7;
                    temp_f31 = 30.0f / 11.0f;
                    break;

                case 2:
                    temp_r29 = 8;
                    break;
            }
        }

        if (temp_r29 > 0 && arg0->unkAC != temp_r29) {
            arg0->unkAC = temp_r29;
            Hu3DMotionOverlaySet(arg1->model[0], arg1->motion[arg0->unkAC]);
            Hu3DMotionOverlaySpeedSet(arg1->model[0], temp_f31);
        }
    }
}

void fn_1_4224(Work8F68 *arg0, omObjData *arg1)
{
    s32 temp_r25;
    arg0->unk10 = arg0->unk4;
    arg0->unk1C.x = 0;
    arg0->unk1C.y = 0;
    arg0->unk1C.z = 0;
    arg0->unk1C.x = arg0->unkF4 / 4.0f;
    arg0->unk1C.z = (-(float)arg0->unkF8) / 4.0f;
    temp_r25 = 0;
    if ((arg0->unkE8 & 0x1) == 0) {
        arg0->unk58 = VECMagXZ(&arg0->unk1C);
        if (0.5f <= arg0->unk58) {
            if (10.0f <= arg0->unk58) {
                arg0->unk1C.x /= arg0->unk58;
                arg0->unk1C.z /= arg0->unk58;
                arg0->unk58 = 10;
                arg0->unk1C.x = 10.0f * arg0->unk1C.x;
                arg0->unk1C.z = 10.0f * arg0->unk1C.z;
            }
            arg0->unk50 = fn_1_1E20(arg0->unk50, atan2d(arg0->unk1C.x, arg0->unk1C.z), 0.4f);
            if (8.0f <= arg0->unk58) {
                temp_r25 = 2;
            }
            else {
                temp_r25 = 1;
            }
        }
        VECAdd(&arg0->unk4, &arg0->unk1C, &arg0->unk4);
    }
    arg0->unk108 = 0;
    fn_1_36FC(arg0);
    fn_1_386C(arg0);
    fn_1_3DCC(arg0);
    fn_1_36FC(arg0);
    if (arg0->unk108) {
        arg0->unk100++;
        arg0->unk104++;
    }
    else {
        arg0->unk104 = 0;
    }
    fn_1_2950(arg0);
    fn_1_40C0(arg0, arg1, temp_r25);
}

Work8F68 *fn_1_4DF0(s32 arg0)
{
    s32 temp_r31;
    Work8F68 *temp_r30;
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r30 = lbl_1_bss_1A4[temp_r31]->data;
        if (arg0 == temp_r30->unk110) {
            return temp_r30;
        }
    }
    return NULL;
}

void fn_1_4E50(Work8F68 *arg0)
{
    float temp_f31;
    float temp_f30;
    float temp_f27;
    Work8F68 *temp_r31;

    if ((arg0->unkE8 & 0x4) && lbl_1_bss_28 < 0) {
        temp_r31 = fn_1_4DF0(arg0->unk110 ^ 1);
        if (temp_r31->unkE8 & 0x4) {
            temp_f31 = arg0->unk4.x - temp_r31->unk4.x;
            temp_f30 = arg0->unk4.z - temp_r31->unk4.z;
            temp_f27 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
            if ((1.5f * (arg0->unk54 + temp_r31->unk54)) >= temp_f27) {
                lbl_1_bss_28 = arg0->unk110 & 0x2;
            }
        }
    }
}

void fn_1_50AC(Work8F68 *arg0, omObjData *arg1)
{
    float temp_f31;
    float temp_f30;
    float temp_f27;
    Work3284 *temp_r30;
    s32 temp_r28;
    omObjData *temp_r27;
    if (arg0->unkE8 & 0x2) {
        return;
    }
    for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
        if ((arg0->unk110 & 0x2) != (lbl_1_bss_19C[temp_r28]->work[0] & 0x2)) {
            continue;
        }
        temp_r30 = lbl_1_bss_19C[temp_r28]->data;
        if (temp_r30->unk18 & 0x1) {
            continue;
        }
        temp_f31 = temp_r30->unk0.x - arg0->unk4.x;
        temp_f30 = temp_r30->unk0.z - arg0->unk4.z;
        temp_f27 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
        if (50 + arg0->unk54 >= temp_f27) {
            omVibrate(arg0->unk114, 12, 6, 6);
            arg0->unk9C = 2002;
            arg0->unk5C = 0;
            arg0->unkE8 |= 0x2;
            arg0->unkE8 &= ~0x10;
            arg0->unk28 = temp_r30->unk0;
            arg0->unkA4 = lbl_1_bss_2C[arg0->unk110 >> 1]++;
            arg0->unkA0 = (arg0->unk110 & 0x2) + arg0->unkA4;
            Hu3DModelAttrReset(arg1->model[0], HU3D_MOTATTR_LOOP);
            if (!arg0->unkA4) {
                arg0->unkA8 = 5;
                Hu3DMotionShiftSet(arg1->model[0], arg1->motion[5], 0, 10, HU3D_MOTATTR_NONE);
                HuAudFXPlay(1642);
            }
            else {
                arg0->unkA8 = 6;
                Hu3DMotionShiftSet(arg1->model[0], arg1->motion[6], 0, 10, HU3D_MOTATTR_NONE);
                HuAudFXPlay(1643);
            }
            temp_r27 = lbl_1_bss_1A0[arg0->unkA0];
            omSetTra(temp_r27, arg0->unk28.x, arg0->unk28.y, arg0->unk28.z);
            Hu3DModelAttrReset(temp_r27->model[0], HU3D_ATTR_DISPOFF);

            temp_r30->unk18 |= 0x1;
            Hu3DModelAttrSet(lbl_1_bss_19C[temp_r28]->model[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_19C[temp_r28]->model[1], HU3D_ATTR_DISPOFF);
            break;
        }
    }
}

void fn_1_54BC(Work8F68 *arg0, omObjData *arg1)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    Vec sp14;
    Vec sp8;
    omObjData *temp_r29;

    arg0->unk5C++;
    temp_f31 = arg0->unk5C / 50;
    if (1.0f <= temp_f31) {
        temp_f31 = 1.0f;
    }
    fn_1_1D18(arg1->model[0], CharModelHookNameGet(arg0->unk118, 8, 0), &sp14);
    fn_1_11F4(temp_f31, &arg0->unk28, &sp14, &sp8);
    sp8.y += sind(180.0f * temp_f31) * 100;
    temp_r29 = lbl_1_bss_1A0[arg0->unkA0];
    omSetTra(temp_r29, sp8.x, sp8.y, sp8.z);
    (void)temp_f31;
    if (80.0f <= arg0->unk5C++) {
        arg0->unk9C = 2001;
        arg0->unkE8 |= 0x4;
        arg0->unkA8 = 0;
        omSetTra(temp_r29, 0, 0, 0);
        Hu3DModelHookSet(arg1->model[0], CharModelHookNameGet(arg0->unk118, 8, 0), temp_r29->model[0]);
        if (arg0->unkA4 == 0) {
            arg0->unkAC = 7;
        }
        else {
            arg0->unkAC = 9;
        }
        Hu3DModelAttrSet(arg1->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_OVL_LOOP);
        Hu3DMotionSet(arg1->model[0], arg1->motion[0]);
        Hu3DMotionOverlaySet(arg1->model[0], arg1->motion[arg0->unkAC]);
    }
}

s32 fn_1_583C(Work8F68 *arg0, s32 arg1)
{
    s32 temp_r31;
    s32 temp_r29;
    s32 temp_r27;
    s32 temp_r26;
    if (arg0->unkE8 & 0x10) {
        return arg1;
    }
    temp_r29 = 0;
    temp_r31 = arg1;
    if (arg0->unk8C >= 0) {
        arg0->unk88 = -1;
        temp_r31 = frandmod(lbl_1_bss_190->unk1C);
        do {
            temp_r29++;
            if (lbl_1_bss_190->unk1C <= temp_r29) {
                temp_r31 = frandmod(lbl_1_bss_190->unk1C);
            }
            else {
                temp_r27 = temp_r31 / 32;
                temp_r26 = temp_r31 % 32;
                if ((1 << temp_r26) & arg0->unk94[temp_r27]) {
                    temp_r31 = (temp_r31 + 1) % lbl_1_bss_190->unk1C;
                }
            }
        } while (temp_r31 == arg1);
    }

    return temp_r31;
}

void fn_1_595C(Work8F68 *arg0, Work8F68 *arg1)
{
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    Work3284 *temp_r26;
    s32 temp_r24;
    Data1340SubStruct *temp_r23;

    if (!(arg0->unkE8 & 0x10)) {
        fn_1_2950(arg0);
        if (arg0->unkEC >= 0) {
            temp_r27 = 0;
            temp_r23 = &lbl_1_bss_190->unk20[arg0->unkEC];
            for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
                temp_r24 = temp_r23->unk8[temp_r28];
                if (temp_r24 < 0) {
                    break;
                }
                if (arg0->unkE8 & 0x2) {
                    if (temp_r24 == arg1->unkEC) {
                        temp_r27 = 1;
                    }
                }
                else {
                    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                        if ((arg0->unk110 & 0x2) == (lbl_1_bss_19C[temp_r29]->work[0] & 0x2)) {
                            temp_r26 = lbl_1_bss_19C[temp_r29]->data;
                            if (!(temp_r26->unk18 & 0x1)) {
                                if (temp_r24 == temp_r26->unk14) {
                                    temp_r27 = 1;
                                }
                            }
                        }
                    }
                }
                if (temp_r27 != 0) {
                    break;
                }
            }
            if (temp_r27 != 0) {
                arg0->unkF0 = -1;
                arg0->unkE8 |= 0x10;
            }
        }
    }
}

s32 fn_1_5CDC(Work8F68 *arg0)
{
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    Work3284 *temp_r27;
    s32 temp_r24;
    temp_r28 = -1;
    temp_r24 = 65535;
    arg0->unk88 = -1;
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        if ((arg0->unk110 & 0x2) == (lbl_1_bss_19C[temp_r29]->work[0] & 0x2)) {
            temp_r27 = lbl_1_bss_19C[temp_r29]->data;
            if (temp_r27->unk18 & 0x1) {
                continue;
            }
            arg0->unkF0 = temp_r27->unk14;
            fn_1_2E14(arg0);
            if (temp_r24 > arg0->unk78) {
                temp_r28 = temp_r27->unk14;
                temp_r24 = arg0->unk78;
                arg0->unk88 = temp_r29;
            }
        }
    }
    temp_r28 = fn_1_583C(arg0, temp_r28);
    return temp_r28;
}

void fn_1_5F44(Work8F68 *arg0)
{
    float temp_f31;
    float temp_f30;
    float temp_f24;
    float temp_f23;

    Vec spC4;
    Work3284 *sp78;

    Work8F68 *temp_r28;
    s32 temp_r18;
    if (NULL == arg0->unk0) {
        return;
    }
    temp_r28 = fn_1_4DF0(arg0->unk110 ^ 1);
    arg0->unk90--;
    if (0.0f < arg0->unk90) {
        return;
    }
    if (arg0->unk100 > 30 || arg0->unk10C > 30) {
        arg0->unk90 = 30;
        if (arg0->unkE8 & 0x2) {
            arg0->unk90 *= 2.5f;
        }
    }
    arg0->unk84 -= 1.0f;
    if (0.0f > arg0->unk84) {
        arg0->unk80 -= 1.0f;
        if (0.0f > arg0->unk80) {
            arg0->unk80 = ((arg0->unk0->unk4 / 2) * frandf()) + arg0->unk0->unk4;
            arg0->unk84 = ((arg0->unk0->unk8 / 2) * frandf()) + arg0->unk0->unk8;
        }
    }
    if (arg0->unkF0 >= 0) {
        if (arg0->unkE8 & 0x2) {
            if (arg0->unk8C >= 0) {
                if (arg0->unkE8 & 0x8) {
                    arg0->unkF0 = -1;
                }
            }
            else {
                if (arg0->unkF0 != temp_r28->unkEC) {
                    arg0->unkF0 = -1;
                }
            }
        }
        else {
            if (arg0->unk88 >= 0) {
                sp78 = lbl_1_bss_19C[arg0->unk88]->data;
                if (sp78->unk18 & 0x1) {
                    arg0->unkF0 = -1;
                }
            }
            else {
                if (arg0->unkE8 & 0x8) {
                    arg0->unkF0 = -1;
                }
            }
        }
        if (arg0->unk100 > 30) {
            arg0->unkF0 = -1;
        }
        if (arg0->unk104 > 30) {
            arg0->unkF0 = -1;
        }
        if (arg0->unk10C > 30) {
            arg0->unkF0 = -1;
        }
    }
    temp_r18 = -1;
    if (arg0->unkF0 < 0) {
        if (arg0->unkE8 & 0x2) {
            arg0->unkF0 = fn_1_583C(arg0, temp_r28->unkEC);
        }
        else {
            arg0->unkF0 = fn_1_5CDC(arg0);
        }
        temp_r18 = arg0->unkF0;
        arg0->unkE8 &= ~0x8;
        fn_1_2E14(arg0);
        fn_1_2EEC(arg0);
    }

    if ((arg0->unkE8 & 0x8) && (arg0->unkE8 & 0x2)) {
        spC4 = temp_r28->unk4;
    }
    else {
        if (NULL == arg0->unk74) {
            if (temp_r18 < 0) {
                arg0->unkE8 &= ~0x8;
                arg0->unkF0 = frandmod(lbl_1_bss_190->unk1C);
                fn_1_2E14(arg0);
                fn_1_2EEC(arg0);
                return;
            }
            else {
                spC4 = lbl_1_bss_190->unk20[temp_r18].unk18;
            }
        }
        else {
            spC4 = lbl_1_bss_190->unk20[arg0->unk74[arg0->unk7C]].unk18;
        }
    }
    temp_f31 = spC4.x - arg0->unk4.x;
    temp_f30 = spC4.z - arg0->unk4.z;
    temp_f24 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
    if (10.0f <= temp_f24) {
        temp_f31 /= temp_f24;
        temp_f30 /= temp_f24;
    }
    else {
        temp_f31 = 0;
        temp_f30 = 0;
    }
    if (150.0f > temp_f24) {
        fn_1_595C(arg0, temp_r28);
        arg0->unk7C++;
        if (arg0->unk78 <= arg0->unk7C) {
            arg0->unk7C = arg0->unk78 - 1;
            arg0->unkE8 |= 8;
        }
    }
    temp_f23 = arg0->unk0->unk0;
    arg0->unkF4 = (72.0f * temp_f31) * temp_f23;
    arg0->unkF8 = (72.0f * -temp_f30) * temp_f23;
    if (ABS(arg0->unkF4) > 72) {
        arg0->unkF4 = ((arg0->unkF4 < 0) ? -1 : 1) * 72;
    }
    if (ABS(arg0->unkF8) > 72) {
        arg0->unkF8 = ((arg0->unkF8 < 0) ? -1 : 1) * 72;
    }
}

void fn_1_7098(s32 arg0, float *arg1)
{
    Bss130Struct *temp_r30;
    Hu3DCameraViewportSet(lbl_1_data_FEC[arg0], arg1[0], arg1[1], arg1[2], arg1[3], 0, 1);
    Hu3DCameraScissorSet(lbl_1_data_FEC[arg0], arg1[0], arg1[1], arg1[2], arg1[3]);
    temp_r30 = &lbl_1_bss_130[arg0];
    temp_r30->unk8 = 0.9f * (arg1[0] + (arg1[2] / 2));
    temp_r30->unkC = arg1[1] + (arg1[3] / 2);
    temp_r30->unk10 = arg1[2] / 316;
    temp_r30->unk14 = arg1[3] / 236;
}

void fn_1_7D38(omObjData *object);

void fn_1_71F0(omObjData *object)
{
    Work8F68 *temp_r31;
    s32 temp_r29;
    temp_r31 = object->data;

    if (lbl_1_bss_1AC->work[0] == 1007) {
        temp_r31->unkE8 &= ~0x1;
        espDispOff(temp_r31->unkB4);
        for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
            espDispOff(temp_r31->unkB8[temp_r29]);
            espDispOff(temp_r31->unkC8[temp_r29][0]);
            espDispOff(temp_r31->unkC8[temp_r29][1]);
        }
        if (temp_r31->unk9C == 2001) {
            temp_r31->unk9C = 2003;
            fn_1_40C0(temp_r31, object, 0);
            if (lbl_1_bss_28 == (temp_r31->unk110 & 0x2)) {
                GWPlayerCoinWinSet(temp_r31->unk114, 10);
            }
            object->func = fn_1_7D38;
            return;
        }
    }
    if (GWPlayerCfg[temp_r31->unk114].iscom) {
        temp_r31->unkF4 = 0;
        temp_r31->unkF8 = 0;
        temp_r31->unkFC = 0;
        fn_1_5F44(temp_r31);
    }
    else {
        temp_r31->unkF4 = HuPadStkX[temp_r31->unk11C];
        temp_r31->unkF8 = HuPadStkY[temp_r31->unk11C];
        temp_r31->unkFC = HuPadBtnDown[temp_r31->unk11C];
    }
    if (lbl_1_bss_1AC->work[0] < 1007 && (temp_r31->unkFC & (PAD_BUTTON_X | PAD_BUTTON_Y))) {
        if (temp_r31->unkE8 & 0x1) {
            temp_r31->unkE8 &= ~0x1;
            espDispOff(temp_r31->unkB4);
            for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                espDispOff(temp_r31->unkB8[temp_r29]);
                espDispOff(temp_r31->unkC8[temp_r29][0]);
                espDispOff(temp_r31->unkC8[temp_r29][1]);
            }
        }
        else {
            temp_r31->unkE8 |= 0x1;
            espDispOn(temp_r31->unkB4);
            for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                espDispOn(temp_r31->unkB8[temp_r29]);
            }
        }
    }
    switch (temp_r31->unk9C) {
        case 2001:
            fn_1_4224(temp_r31, object);
            fn_1_50AC(temp_r31, object);
            fn_1_4E50(temp_r31);
            break;

        case 2002:
            fn_1_54BC(temp_r31, object);
            break;

        default:
            OSReport("*** player mode error(%d)!!\n", temp_r31->unk9C);
            break;
    }
    if (temp_r31->unk104 == 0 && temp_r31->unk10C == 0) {
        temp_r31->unk100 = 0;
    }
    lbl_1_bss_C8[temp_r31->unk110].x = temp_r31->unk4.x + (lbl_1_bss_120 * sind(lbl_1_bss_11C));
    lbl_1_bss_C8[temp_r31->unk110].y = temp_r31->unk4.y + lbl_1_bss_118;
    lbl_1_bss_C8[temp_r31->unk110].z = temp_r31->unk4.z + (lbl_1_bss_120 * cosd(lbl_1_bss_11C));
    lbl_1_bss_68[temp_r31->unk110].x = temp_r31->unk4.x;
    lbl_1_bss_68[temp_r31->unk110].y = temp_r31->unk4.y;
    lbl_1_bss_68[temp_r31->unk110].z = temp_r31->unk4.z;
    Hu3DCameraPosSetV(lbl_1_data_FEC[temp_r31->unk110], &lbl_1_bss_C8[temp_r31->unk110], &lbl_1_data_FE0, &lbl_1_bss_68[temp_r31->unk110]);
    temp_r31->unk60 = temp_r31->unk50;
    omSetTra(object, temp_r31->unk4.x, temp_r31->unk4.y, temp_r31->unk4.z);
    omSetRot(object, 0, temp_r31->unk50, 0);
}

void fn_1_7D38(omObjData *object)
{
    float temp_f27;

    Mtx sp74;
    Vec sp8;

    Work8F68 *temp_r31 = object->data;

    switch (temp_r31->unk9C) {
        case 2000:
            if (lbl_1_bss_1AC->work[0] >= 1006) {
                temp_r31->unk9C++;
                object->func = fn_1_71F0;
            }
            break;

        case 2003:
            if (lbl_1_bss_1AC->work[0] == 1010) {
                Hu3DMotionOverlayReset(object->model[0]);
                if (lbl_1_bss_28 >= 0 && (temp_r31->unk110 == lbl_1_bss_28 || temp_r31->unk110 == (lbl_1_bss_28 ^ 1))) {
                    temp_r31->unk9C = 2004;
                    temp_r31->unk5C = 0;
                    temp_r31->unkE8 |= 0x20;
                    fn_1_1D18(object->model[0], CharModelHookNameGet(temp_r31->unk118, 8, 0), &temp_r31->unk28);
                    Hu3DModelObjMtxGet(object->model[0], CharModelHookNameGet(temp_r31->unk118, 8, 0), sp74);
                    Hu3DMtxRotGet(sp74, &temp_r31->unk40);
                    Hu3DModelHookObjReset(object->model[0], CharModelHookNameGet(temp_r31->unk118, 8, 0));
                    omSetTra(lbl_1_bss_1A0[temp_r31->unkA0], temp_r31->unk28.x, temp_r31->unk28.y, temp_r31->unk28.z);
                    if (temp_r31->unkA4 == 0) {
                        temp_r31->unk4C = lbl_1_bss_110;
                        Hu3DMotionSet(object->model[0], object->motion[5]);
                    }
                    else {
                        temp_r31->unk4C = lbl_1_bss_110 + 180;
                        temp_r31->unk40.y = lbl_1_bss_110 + 180;
                        Hu3DMotionSet(object->model[0], object->motion[6]);
                    }
                    Hu3DMotionTimeSet(object->model[0], Hu3DMotionMaxTimeGet(object->model[0]) - 1);
                    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_REV);
                    temp_r31->unk40.x = 0;
                    temp_r31->unk40.z = 0;
                    omSetRot(lbl_1_bss_1A0[temp_r31->unkA0], temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z);
                    temp_r31->unk4C = fmod(temp_r31->unk4C - temp_r31->unk40.y, 360);
                    if (0.0f > temp_r31->unk4C) {
                        temp_r31->unk4C += 360.0f;
                    }
                    if (180.0f < temp_r31->unk4C) {
                        temp_r31->unk4C -= 360.0f;
                    }
                    temp_r31->unk4C /= 60.0f;
                }
                else {
                    temp_r31->unk9C = 2008;
                    Hu3DMotionShiftSet(object->model[0], object->motion[4], 0, 8, HU3D_MOTATTR_NONE);
                }
            }
            if (lbl_1_bss_1AC->work[0] == 1012) {
                temp_r31->unk9C = 2008;
                Hu3DMotionOverlayReset(object->model[0]);
                Hu3DMotionShiftSet(object->model[0], object->motion[4], 0, 8, HU3D_MOTATTR_NONE);
            }
            if (temp_r31->unk9C == 2008 && temp_r31->unkA0 >= 0) {
                Hu3DModelAttrSet(lbl_1_bss_1A0[temp_r31->unkA0]->model[0], HU3D_ATTR_DISPOFF);
                fn_1_1D18(object->model[0], CharModelHookNameGet(temp_r31->unk118, 8, 0), &sp8);
                temp_r31->unk70 = Hu3DParManLink(lbl_1_bss_8, &lbl_1_data_13E8);
                temp_r31->unk6C = 0;
                Hu3DParManPosSet(temp_r31->unk70, sp8.x, sp8.y, sp8.z);
                Hu3DParManAttrReset(temp_r31->unk70, 1);
                Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(temp_r31->unk70), 1);
                Hu3DModelLayerSet(Hu3DParManModelIDGet(temp_r31->unk70), 6);
            }
            break;

        case 2004:
            temp_r31->unk5C++;
            fn_1_11F4(temp_r31->unk5C / 60, &temp_r31->unk28, &lbl_1_bss_F8[temp_r31->unkA4], &temp_r31->unk34);
            temp_r31->unk34.y += sind(temp_r31->unk5C * 3.0f) * 100;
            omSetTra(lbl_1_bss_1A0[temp_r31->unkA0], temp_r31->unk34.x, temp_r31->unk34.y, temp_r31->unk34.z);
            temp_r31->unk40.y += temp_r31->unk4C;
            omSetRot(lbl_1_bss_1A0[temp_r31->unkA0], temp_r31->unk40.x, temp_r31->unk40.y, temp_r31->unk40.z);
            if (60.0f <= temp_r31->unk5C) {
                temp_r31->unk9C++;
                temp_r31->unk5C = 0;
                temp_r31->unk28 = temp_r31->unk34;
                if (temp_r31->unkA4 == 1) {
                    lbl_1_bss_F8[1].x -= 10 * sind(lbl_1_bss_110);
                    lbl_1_bss_F8[1].z -= 10 * cosd(lbl_1_bss_110);
                }
                else {
                    sp8.x = (30 * sind(lbl_1_bss_110)) + temp_r31->unk34.x;
                    sp8.y = 30 + temp_r31->unk34.y;
                    sp8.z = (30 * cosd(lbl_1_bss_110)) + temp_r31->unk34.z;
                    Hu3DModelTPLvlSet(lbl_1_bss_1A0[temp_r31->unkA0]->model[1], 0);
                    Hu3DModelPosSet(lbl_1_bss_1A0[temp_r31->unkA0]->model[1], sp8.x, sp8.y, sp8.z);
                    Hu3DModelRotSet(lbl_1_bss_1A0[temp_r31->unkA0]->model[1], 0, lbl_1_bss_110, 0);
                    Hu3DModelAttrReset(lbl_1_bss_1A0[temp_r31->unkA0]->model[1], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_1A0[temp_r31->unkA0]->model[1], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(lbl_1_bss_1A0[temp_r31->unkA0]->model[1], HU3D_MOTATTR_LOOP);
                }
            }
            break;

        case 2005:
            temp_r31->unk5C++;
            fn_1_11F4(temp_r31->unk5C / 60, &temp_r31->unk28, &lbl_1_bss_F8[temp_r31->unkA4], &temp_r31->unk34);
            omSetTra(lbl_1_bss_1A0[temp_r31->unkA0], temp_r31->unk34.x, temp_r31->unk34.y, temp_r31->unk34.z);
            if (temp_r31->unkA4 == 0) {
                temp_f27 = temp_r31->unk5C / 20;
                if (1.0f <= temp_f27) {
                    temp_f27 = 1.0f;
                }
                Hu3DModelTPLvlSet(lbl_1_bss_1A0[temp_r31->unkA0]->model[1], temp_f27);
            }
            if (60.0f <= temp_r31->unk5C) {
                temp_r31->unk9C++;
                temp_r31->unk5C = 0;
                if (temp_r31->unkA4 == 1) {
                    Hu3DModelAttrReset(lbl_1_bss_1A0[temp_r31->unkA0]->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                    Hu3DMotionSet(lbl_1_bss_1A0[temp_r31->unkA0]->model[0], lbl_1_bss_1A0[temp_r31->unkA0]->motion[0]);
                    HuAudFXPlay(1649);
                }
            }

            break;

        case 2006:
            temp_r31->unk5C++;
            if (20.0f == temp_r31->unk5C) {
                temp_r31->unk60 = temp_r31->unk64;
                if (temp_r31->unkA4 == 0) {
                    Hu3DModelAttrReset(lbl_1_bss_1A0[temp_r31->unkA0]->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                    Hu3DMotionSet(lbl_1_bss_1A0[temp_r31->unkA0]->model[0], lbl_1_bss_1A0[temp_r31->unkA0]->motion[0]);
                    HuAudFXPlay(1648);
                }
            }
            if (30.0f < temp_r31->unk5C && Hu3DMotionEndCheck(lbl_1_bss_1A0[temp_r31->unkA0 & 0x2]->model[0])) {
                temp_r31->unk9C++;
                lbl_1_bss_1C++;
            }
            break;

        case 2007:
            if ((temp_r31->unk110 & 0x1) < lbl_1_bss_20) {
                temp_r31->unk9C = 2008;
                Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_REV);
                Hu3DMotionShiftSet(object->model[0], object->motion[3], 0, 8, HU3D_MOTATTR_NONE);
            }
            break;

        case 2008:
            if (temp_r31->unk70 >= 0) {
                temp_r31->unk6C++;
                if (10.0f == temp_r31->unk6C) {
                    Hu3DParManAttrSet(temp_r31->unk70, 1);
                }
            }
            break;

        default:
            OSReport("*** player mode error(%d)!!\n", temp_r31->unk9C);
            break;
    }
    if (temp_r31->unk9C >= 2005 && (temp_r31->unkE8 & 0x20)) {
        temp_r31->unk68 += 4.0f;
        sp8 = temp_r31->unk34;
        sp8.y += sind(temp_r31->unk68) * 5.0;
        omSetTra(lbl_1_bss_1A0[temp_r31->unkA0], sp8.x, sp8.y, sp8.z);
        sp8.x = temp_r31->unk34.x + (30.0 * sind(lbl_1_bss_110));
        sp8.y = (temp_r31->unk34.y + 30) + (5.0 * sind(temp_r31->unk68));
        sp8.z = temp_r31->unk34.z + (30.0 * cosd(lbl_1_bss_110));
        Hu3DModelPosSet(lbl_1_bss_1A0[temp_r31->unkA0]->model[1], sp8.x, sp8.y, sp8.z);
    }
    if (temp_r31->unk9C >= 2003) {
        temp_r31->unk50 = fn_1_1E20(temp_r31->unk50, temp_r31->unk60, 0.1f);
    }
    omSetTra(object, temp_r31->unk4.x, temp_r31->unk4.y, temp_r31->unk4.z);
    omSetRot(object, 0, temp_r31->unk50, 0);
}

void fn_1_8F68(omObjData *object)
{
    Work8F68 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    Data1340SubStruct *temp_r23;

    temp_r31 = object->data;
    temp_r31->unk118 = GWPlayerCfg[temp_r31->unk114].character;
    temp_r31->unk11C = GWPlayerCfg[temp_r31->unk114].pad_idx;
    temp_r31->unk9C = 2000;
    temp_r31->unkA0 = -1;
    temp_r31->unkA4 = -1;
    temp_r31->unkE8 = 0;
    temp_r31->unk70 = -1;
    temp_r31->unk50 = 0;
    temp_r31->unk68 = 0;
    temp_r31->unkA8 = 0;
    temp_r31->unkAC = -1;
    temp_r31->unk54 = 65;
    temp_r31->unk0 = 0;
    temp_r31->unk80 = 0;
    temp_r31->unk84 = 0;
    temp_r31->unk74 = 0;
    temp_r31->unk78 = 65535;
    temp_r31->unk7C = 0;
    temp_r31->unk88 = -1;
    temp_r31->unk8C = -1;
    temp_r31->unk90 = 0;
    temp_r31->unkEC = -1;
    temp_r31->unkF0 = -1;
    temp_r31->unk100 = 0;
    temp_r31->unk104 = 0;
    temp_r31->unk10C = 0;
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
        temp_r31->unk94[temp_r29] = 0;
    }
    object->model[0] = CharModelCreate(lbl_1_data_0[temp_r31->unk118], 8);
    CharModelStepTypeSet(lbl_1_data_0[temp_r31->unk118], 0);
    for (temp_r29 = 0; temp_r29 < 10; temp_r29++) {
        object->motion[temp_r29] = CharModelMotionCreate(lbl_1_data_0[temp_r31->unk118], lbl_1_data_1150[temp_r31->unk118][temp_r29]);
        CharModelMotionSet(lbl_1_data_0[temp_r31->unk118], object->motion[temp_r29]);
    }
    Hu3DModelCameraSet(object->model[0], 15);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->model[0], 2);
    Hu3DMotionSet(object->model[0], object->motion[0]);
    Hu3DModelShadowSet(object->model[0]);
    temp_r31->unk4.x = 0;
    temp_r31->unk4.y = 0;
    temp_r31->unk4.z = 0;
    temp_r28 = temp_r31->unk110;
    if (temp_r28 >= 2) {
        temp_r28 ^= 1;
    }
    temp_r28 = (temp_r28 + lbl_1_bss_34) % 4;
    temp_r23 = fn_1_2614(1 << temp_r28);
    if (NULL != temp_r23) {
        temp_r31->unk4 = temp_r23->unk18;
    }
    omSetTra(object, temp_r31->unk4.x, temp_r31->unk4.y, temp_r31->unk4.z);
    omSetRot(object, 0, temp_r31->unk50, 0);
    lbl_1_bss_98[temp_r31->unk110].x = temp_r31->unk4.x;
    lbl_1_bss_98[temp_r31->unk110].y = temp_r31->unk4.y + 450;
    lbl_1_bss_98[temp_r31->unk110].z = temp_r31->unk4.z + 850;
    lbl_1_bss_38[temp_r31->unk110].x = temp_r31->unk4.x;
    lbl_1_bss_38[temp_r31->unk110].y = temp_r31->unk4.y;
    lbl_1_bss_38[temp_r31->unk110].z = temp_r31->unk4.z;
    temp_r31->unkB0 = espEntry(lbl_1_data_12D0[temp_r31->unk110], 134, 0);
    espDrawNoSet(temp_r31->unkB0, 0);
    lbl_1_bss_130[temp_r31->unk110].unk0 = temp_r31->unkB0;
    espDispOff(temp_r31->unkB0);
    espZRotSet(temp_r31->unkB0, (temp_r31->unk110 & 0x1) ? 0.0f : 180.0f);
    temp_r31->unkB4 = espEntry(DATA_MAKE_NUM(DATADIR_M429, 0x31), 133, 0);
    espDrawNoSet(temp_r31->unkB4, 0);
    espDispOff(temp_r31->unkB4);
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        temp_r31->unkB8[temp_r29] = espEntry(lbl_1_data_1290[GWPlayerCfg[temp_r29].character], (temp_r31->unk114 == temp_r29) ? 129 : 130, 0);
        espDrawNoSet(temp_r31->unkB8[temp_r29], 0);
        espDispOff(temp_r31->unkB8[temp_r29]);
        temp_r31->unkC8[temp_r29][0] = espEntry(lbl_1_data_1310[temp_r29], 128, 0);
        espDrawNoSet(temp_r31->unkC8[temp_r29][0], 0);
        espDispOff(temp_r31->unkC8[temp_r29][0]);
        temp_r31->unkC8[temp_r29][1] = espEntry(DATA_MAKE_NUM(DATADIR_M429, 0x3C), 128, 0);
        espDrawNoSet(temp_r31->unkC8[temp_r29][1], 0);
        espDispOff(temp_r31->unkC8[temp_r29][1]);
    }
    if (GWPlayerCfg[temp_r31->unk114].iscom) {
        switch (GWPlayerCfg[temp_r31->unk114].diff) {
            case 0:
                temp_r31->unk0 = &lbl_1_data_13A8;
                break;

            case 1:
                temp_r31->unk0 = &lbl_1_data_13B8;
                break;

            case 2:
                temp_r31->unk0 = &lbl_1_data_13C8;
                break;

            case 3:
            default:
                temp_r31->unk0 = &lbl_1_data_13D8;
                break;
        }
        temp_r31->unk80 = frandf() * temp_r31->unk0->unk4;
        temp_r31->unk8C = temp_r31->unk0->unkC + ((temp_r31->unk0->unkC / 2.0f) * frandf());
    }
    CharModelVoiceEnableSet(temp_r31->unk118, object->motion[4], 0);
    fn_1_2950(temp_r31);
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    CharModelLayerSetAll2(5);
    CharModelMotionDataClose(lbl_1_data_0[temp_r31->unk118]);
    object->func = fn_1_7D38;
}

void fn_1_99EC(omObjData *object) { }

void fn_1_99F0(omObjData *object)
{
    s32 temp_r30;
    s32 *temp_r29;
    temp_r29 = &lbl_1_data_12E0[object->work[0]][0];
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        object->model[temp_r30] = Hu3DModelCreateFile(*temp_r29++);
        Hu3DModelCameraSet(object->model[temp_r30], 15);
        Hu3DModelAttrSet(object->model[temp_r30], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[temp_r30], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(object->model[temp_r30], HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(object->model[temp_r30], 3);
        Hu3DModelShadowSet(object->model[temp_r30]);
    }
    for (temp_r30 = 0; temp_r30 < 1; temp_r29++, temp_r30++) {
        object->motion[temp_r30] = Hu3DJointMotionFile(object->model[0], temp_r29[0]);
    }
    Hu3DMotionSet(object->model[0], object->motion[0]);
    omSetTra(object, 0, 0, 0);
    omSetRot(object, 0, 0, 0);
    object->func = fn_1_99EC;
}

void fn_1_9BAC(omObjData *object)
{
    float temp_f31;
    float temp_f30;

    Vec *temp_r31;
    Work8F68 *temp_r29;
    s32 temp_r27;
    temp_r31 = object->data;
    temp_r31[1].x += (frandf() * 12.0f) + 12.0f;
    temp_r27 = lbl_1_bss_28;
    if (object->work[0] & 0x1) {
        temp_r27 ^= 0x1;
    }
    temp_r29 = fn_1_4DF0(temp_r27);
    temp_r31[1].y++;
    if (90.0f < temp_r31[1].y) {
        temp_r31[1].y = 90.0f;
    }
    temp_f31 = temp_r31[1].y / 90.0f;
    temp_f30 = sind(90.0f * temp_f31) * sind(90.0f * temp_f31);
    temp_r31[0].x = lbl_1_bss_F8->x + temp_f30 * (temp_r29->unk4.x - lbl_1_bss_F8->x) * 1.5f;
    temp_r31[0].z = lbl_1_bss_F8->z + temp_f30 * (temp_r29->unk4.z - lbl_1_bss_F8->z) * 1.5f;
    temp_r31[0].y += temp_r31[1].z;
    temp_r31[1].z -= 0.4f;
    omSetTra(object, temp_r31[0].x, temp_r31[0].y, temp_r31[0].z);
    omSetRot(object, 0, temp_r31[1].x, 0);
    if (0.0f > temp_r31[1].z && 180.0f > temp_r31[0].y) {
        lbl_1_bss_20++;
        HuAudFXPlay(7);
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        CharModelCoinEffectCreate(lbl_1_data_FEC[lbl_1_bss_28], temp_r31);
        omDelObjEx(lbl_1_bss_33C, object);
    }
}

void fn_1_9EEC(omObjData *object)
{
    Vec *temp_r30;
    temp_r30 = object->data;
    object->model[0] = Hu3DModelLink(lbl_1_bss_1A);
    Hu3DModelCameraSet(object->model[0], lbl_1_data_FEC[lbl_1_bss_28]);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(object->model[0], 4);
    Hu3DModelShadowSet(object->model[0]);
    temp_r30[0] = lbl_1_bss_F8[0];
    temp_r30[0].y += 20;
    temp_r30[1].x = 0;
    temp_r30[1].y = 0;
    temp_r30[1].z = (4 * frandf()) + 10;
    omSetTra(object, temp_r30[0].x, temp_r30[0].y, temp_r30[0].z);
    omSetRot(object, 0, temp_r30[1].x, 0);
    omSetSca(object, 0.4f, 0.4f, 0.4f);
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    object->func = fn_1_9BAC;
}

void fn_1_A0A8(s32 arg0)
{
    omObjData *object;
    object = omAddObjEx(lbl_1_bss_33C, 103, 1, 0, 3, fn_1_9EEC);
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Vec) * 2, MEMORY_DEFAULT_NUM);
    object->work[0] = arg0;
}

void fn_1_A118(void)
{
    s32 temp_r31;
    float temp_f31;
    float temp_f30;
    Vec sp8;
    temp_f30 = sind(15.0f) / cosd(15.0f);
    temp_f31 = 0.5f;
    sp8.z = (1.0f - temp_f31) * (lbl_1_bss_190->unk18 * temp_f30);
    sp8.x = 1.2f * sp8.z;
    sp8.y = lbl_1_bss_190->unk18 * temp_f31;
    Hu3DCameraCreate(15);
    Hu3DCameraPerspectiveSet(15, 30, 10, 20000, 1.2f);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        fn_1_7098(temp_r31, &lbl_1_data_FFC[temp_r31][0]);
        lbl_1_bss_C8[temp_r31].x = sp8.x * lbl_1_data_10FC[temp_r31][0];
        lbl_1_bss_C8[temp_r31].y = sp8.y;
        lbl_1_bss_C8[temp_r31].z = sp8.z * lbl_1_data_10FC[temp_r31][1];
        lbl_1_bss_68[temp_r31].x = lbl_1_bss_C8[temp_r31].x;
        lbl_1_bss_68[temp_r31].y = 0;
        lbl_1_bss_68[temp_r31].z = lbl_1_bss_C8[temp_r31].z;
        Hu3DCameraPosSetV(lbl_1_data_FEC[temp_r31], &lbl_1_bss_C8[temp_r31], &lbl_1_data_FD4, &lbl_1_bss_68[temp_r31]);
    }
}

void fn_1_A588(s32 arg0, Vec *arg1, float arg2)
{
    Vec sp18;
    Vec spC;
    sp18.x = lbl_1_bss_C8[arg0].x + (arg2 * (lbl_1_bss_98[arg0].x - lbl_1_bss_C8[arg0].x));
    sp18.y = lbl_1_bss_C8[arg0].y + (arg2 * (lbl_1_bss_98[arg0].y - lbl_1_bss_C8[arg0].y));
    sp18.z = lbl_1_bss_C8[arg0].z + (arg2 * (lbl_1_bss_98[arg0].z - lbl_1_bss_C8[arg0].z));
    spC.x = lbl_1_bss_68[arg0].x + (arg2 * (lbl_1_bss_38[arg0].x - lbl_1_bss_68[arg0].x));
    spC.y = lbl_1_bss_68[arg0].y + (arg2 * (lbl_1_bss_38[arg0].y - lbl_1_bss_68[arg0].y));
    spC.z = lbl_1_bss_68[arg0].z + (arg2 * (lbl_1_bss_38[arg0].z - lbl_1_bss_68[arg0].z));
    Hu3DCameraPosSetV(lbl_1_data_FEC[arg0], &sp18, arg1, &spC);
}

void fn_1_A7B4(void)
{
    s32 temp_r31;
    float *temp_r30;
    float *temp_r29;
    float temp_f31;
    float temp_f30;

    float sp20[4];
    lbl_1_bss_12C++;
    temp_f30 = lbl_1_bss_12C / 120;
    temp_f31 = sind(90 * temp_f30) * sind(90 * temp_f30);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        fn_1_A588(temp_r31, &lbl_1_data_FD4, temp_f31);
    }
    if (30.0f < lbl_1_bss_12C) {
        temp_f30 = (lbl_1_bss_12C - 30.0f) / 60.0f;
        if (1.0f < temp_f30) {
            temp_f30 = 1;
        }
        temp_f31 = sind(90 * temp_f30) * sind(90 * temp_f30);
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            temp_r30 = &lbl_1_data_FFC[temp_r31][0];
            temp_r29 = &lbl_1_data_103C[temp_r31][0];
            sp20[0] = temp_r30[0] + (temp_f31 * (temp_r29[0] - temp_r30[0]));
            sp20[1] = temp_r30[1] + (temp_f31 * (temp_r29[1] - temp_r30[1]));
            sp20[2] = temp_r30[2] + (temp_f31 * (temp_r29[2] - temp_r30[2]));
            sp20[3] = temp_r30[3] + (temp_f31 * (temp_r29[3] - temp_r30[3]));
            fn_1_7098(temp_r31, sp20);
        }
    }
}

void fn_1_AD74(float *arg0)
{
    float sp8[4];
    float *temp_r31;
    s32 temp_r28;
    float temp_f31;
    float temp_f30;

    temp_r31 = &lbl_1_data_103C[0][0];
    temp_f30 = lbl_1_bss_12C / REFRESH_RATE;
    temp_f31 = sind(90 * temp_f30) * sind(90 * temp_f30);
    for (temp_r28 = 0; temp_r28 < 4; temp_r28++, temp_r31 += 4, arg0 += 4) {
        sp8[0] = temp_r31[0] + (temp_f31 * (arg0[0] - temp_r31[0]));
        sp8[1] = temp_r31[1] + (temp_f31 * (arg0[1] - temp_r31[1]));
        sp8[2] = temp_r31[2] + (temp_f31 * (arg0[2] - temp_r31[2]));
        sp8[3] = temp_r31[3] + (temp_f31 * (arg0[3] - temp_r31[3]));
        fn_1_7098(temp_r28, sp8);
    }
}

void fn_1_B01C(void)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;

    Work8F68 *temp_r31;
    Work8F68 *temp_r30;
    temp_r31 = fn_1_4DF0(lbl_1_bss_28);
    temp_r30 = fn_1_4DF0(lbl_1_bss_28 ^ 1);
    temp_f31 = temp_r31->unk4.x - temp_r30->unk4.x;
    temp_f30 = temp_r31->unk4.z - temp_r30->unk4.z;
    lbl_1_bss_110 = atan2d(temp_f31, temp_f30) + 90;
    if (90.0f < lbl_1_bss_110) {
        lbl_1_bss_110 -= 180.0f;
    }

    lbl_1_bss_38[lbl_1_bss_28].x = lbl_1_bss_68[lbl_1_bss_28].x - (temp_f31 / 2);
    lbl_1_bss_38[lbl_1_bss_28].y = lbl_1_bss_68[lbl_1_bss_28].y + 200;
    lbl_1_bss_38[lbl_1_bss_28].z = lbl_1_bss_68[lbl_1_bss_28].z - (temp_f30 / 2);
    temp_f29 = 1350;
    lbl_1_bss_98[lbl_1_bss_28].x = lbl_1_bss_38[lbl_1_bss_28].x + (temp_f29 * sind(lbl_1_bss_110));
    lbl_1_bss_98[lbl_1_bss_28].y = 250 + lbl_1_bss_38[lbl_1_bss_28].y;
    lbl_1_bss_98[lbl_1_bss_28].z = lbl_1_bss_38[lbl_1_bss_28].z + (temp_f29 * cosd(lbl_1_bss_110));
    lbl_1_bss_F8[0] = lbl_1_bss_38[lbl_1_bss_28];
    lbl_1_bss_F8[1] = lbl_1_bss_38[lbl_1_bss_28];
    lbl_1_bss_F8[1].x += 50 * sind(lbl_1_bss_110);
    lbl_1_bss_F8[1].y += 15;
    lbl_1_bss_F8[1].z += 50 * cosd(lbl_1_bss_110);
    temp_f31 = lbl_1_bss_F8[0].x - temp_r31->unk4.x;
    temp_f30 = lbl_1_bss_F8[0].z - temp_r31->unk4.z;
    temp_r31->unk60 = atan2d(temp_f31, temp_f30);
    temp_f31 = lbl_1_bss_F8[0].x - temp_r30->unk4.x;
    temp_f30 = lbl_1_bss_F8[0].z - temp_r30->unk4.z;
    temp_r30->unk60 = atan2d(temp_f31, temp_f30);
    temp_f31 = lbl_1_bss_98[lbl_1_bss_28].x - temp_r31->unk4.x;
    temp_f30 = lbl_1_bss_98[lbl_1_bss_28].z - temp_r31->unk4.z;
    temp_r31->unk64 = atan2d(temp_f31, temp_f30);
    temp_f31 = lbl_1_bss_98[lbl_1_bss_28].x - temp_r30->unk4.x;
    temp_f30 = lbl_1_bss_98[lbl_1_bss_28].z - temp_r30->unk4.z;
    temp_r30->unk64 = atan2d(temp_f31, temp_f30);
    omVibrate(temp_r31->unk114, (VERSION_JP ? 3 : 2) * REFRESH_RATE, 6, 6);
    omVibrate(temp_r30->unk114, (VERSION_JP ? 3 : 2) * REFRESH_RATE, 6, 6);
}

void fn_1_B754(float *arg0, float arg1, float arg2, s32 arg3)
{
    float temp_f31;
    float temp_f30;
    temp_f30 = (arg0[2] / 2) * (arg1 / lbl_1_bss_128);
    temp_f31 = (arg0[3] / 2) * (arg2 / lbl_1_bss_124);
    temp_f30 += arg0[0] + (arg0[2] / 2);
    temp_f31 += arg0[1] + (arg0[3] / 2);
    temp_f30 = 576.0f * (temp_f30 / 640.0f);
    temp_f31 = 480.0f * (temp_f31 / 480.0f);
    temp_f31 += (240.0f <= arg0[1]) ? -16.0f : 16.0f;
    espPosSet(arg3, temp_f30, temp_f31);
}

void fn_1_E96C(omObjData *object);

void fn_1_B8E0(omObjData *object)
{
    float temp_f31;
    float temp_f30;
    float temp_f20;
    float temp_f19;

    float *temp_r31;
    s32 temp_r29;
    Work8F68 *temp_r28;
    Bss130Struct *temp_r27;
    s32 temp_r24;
    Work3284 *temp_r23;
    Work8F68 *temp_r20;

    s32 sp74;
    Work8F68 *sp68;
    Work8F68 *sp5C;
    if (omSysExitReq) {
        fn_1_1F58(-1);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_E96C;
    }
    lbl_1_bss_114 += 1.0f / REFRESH_RATE;
    if (360.0f <= lbl_1_bss_114) {
        lbl_1_bss_114 -= 360.0f;
    }
    Hu3DModelRotSet(object->model[2], 0, lbl_1_bss_114, 0);
    lbl_1_bss_308++;
    switch (object->work[0]) {

        case 1000:
            if (!WipeStatGet()) {
                object->work[0]++;
                lbl_1_bss_12C = 0;
                HuAudFXPlay(1644);
            }
            break;

        case 1001:
            lbl_1_bss_12C++;
            if (60.0f <= lbl_1_bss_12C) {
                object->work[0]++;
                lbl_1_bss_12C = 0;
            }
            break;

        case 1002:
            lbl_1_bss_12C++;
            temp_f30 = lbl_1_bss_12C / REFRESH_RATE;
            temp_f31 = 1 - (sind(temp_f30 * 90.0f) * sind(temp_f30 * 90.0f));
            for (temp_r29 = 0; temp_r29 < 5; temp_r29++) {
                espTPLvlSet(lbl_1_bss_10[temp_r29], temp_f31);
            }
            if (REFRESH_RATE <= lbl_1_bss_12C) {
                object->work[0]++;
                lbl_1_bss_12C = 0;
                for (temp_r29 = 0; temp_r29 < 5; temp_r29++) {
                    espKill(lbl_1_bss_10[temp_r29]);
                }
            }
            break;

        case 1003:
            lbl_1_bss_12C++;
            temp_f30 = lbl_1_bss_12C / REFRESH_RATE;
            temp_f31 = sind(temp_f30 * 90.0f) * sind(temp_f30 * 90.0f);
            for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                lbl_1_bss_130[temp_r29].unk4 = temp_f31;
            }
            if (REFRESH_RATE <= lbl_1_bss_12C) {
                object->work[0]++;
                lbl_1_bss_12C = 0;
                lbl_1_bss_4 = HuAudFXPlay(1645);
                lbl_1_bss_0 = HuAudFXPlay(1646);
            }
            break;

        case 1004:
            fn_1_A7B4();
            if (120.0f <= lbl_1_bss_12C) {
                object->work[0]++;
                HuAudFXStop(lbl_1_bss_4);
            }
            break;

        case 1005:
            if (lbl_1_bss_2FE < 0) {
                lbl_1_bss_2FE = MGSeqStartCreate();
            }
            else {
                if (lbl_1_bss_2F8 < 0 && (MGSeqStatGet(lbl_1_bss_2FE) & 0x10)) {
                    fn_1_1F24(71);
                }
                if (!MGSeqStatGet(lbl_1_bss_2FE)) {
                    object->work[0]++;
                    lbl_1_bss_304 = 60 * REFRESH_RATE;
                    lbl_1_bss_2FC = MGSeqTimerCreate(lbl_1_bss_304 / REFRESH_RATE);
                    lbl_1_bss_2FE = -1;
                }
            }
            break;

        case 1006:
            MGSeqParamSet(lbl_1_bss_2FC, 1, (lbl_1_bss_304 + REFRESH_RATE - 1) / REFRESH_RATE);
            lbl_1_bss_304--;
            if (lbl_1_bss_304 < 0 || lbl_1_bss_28 >= 0) {
                object->work[0] = 1007;
                lbl_1_bss_304 = 60 * REFRESH_RATE;
                lbl_1_bss_12C = 0;
            }
            break;

        case 1007:
            if (lbl_1_bss_2FE < 0) {
                MGSeqParamSet(lbl_1_bss_2FC, 2, -1);
                lbl_1_bss_2FC = -1;
                lbl_1_bss_2FE = MGSeqFinishCreate();
                fn_1_1F58(100);
                lbl_1_bss_12C = 0;
                if (lbl_1_bss_28 >= 0) {
                    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(object->model[3], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(object->model[3], HU3D_ATTR_DISPOFF);
                }
            }
            else {
                sp74 = 0;
                for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                    if (((Work8F68 *)lbl_1_bss_1A4[temp_r29]->data)->unk9C >= 2003) {
                        sp74++;
                    }
                }
                if (sp74 == 4) {
                    lbl_1_bss_12C++;
                }
                if (lbl_1_bss_28 >= 0 && 60.0f == lbl_1_bss_12C) {
                    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(object->model[4], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(object->model[4], HU3D_MOTATTR_PAUSE);
                }
                if (60.0f < lbl_1_bss_12C && !MGSeqStatGet(lbl_1_bss_2FE)) {
                    lbl_1_bss_2FE = -1;
                    lbl_1_bss_12C = 0;
                    if (lbl_1_bss_28 < 0) {
                        object->work[0] = 1012;
                        lbl_1_bss_12C = 0;
                        lbl_1_bss_2FE = MGSeqDrawCreate();
                        HuAudSStreamPlay(4);
                    }
                    else {
                        object->work[0] = 1008;
                        fn_1_B01C();
                    }
                }
            }
            break;

        case 1008:
            lbl_1_bss_12C++;
            if (REFRESH_RATE < lbl_1_bss_12C) {
                object->work[0]++;
                lbl_1_bss_12C = 0;
                HuAudFXPlay(1650);
                for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                    if (lbl_1_bss_28 != temp_r29) {
                        Hu3DCameraKill(lbl_1_data_FEC[temp_r29]);
                    }
                }
            }
            else {
                fn_1_AD74(((lbl_1_bss_28 & 0x2) == 0) ? &lbl_1_data_107C[0][0] : &lbl_1_data_10BC[0][0]);
                temp_f30 = lbl_1_bss_12C / REFRESH_RATE;
                temp_f31 = sind(temp_f30 * 90.0f) * sind(temp_f30 * 90.0f);
                fn_1_A588(lbl_1_bss_28, &lbl_1_data_FE0, temp_f31);
            }
            break;

        case 1009:
            lbl_1_bss_12C++;
            if (2 * REFRESH_RATE < lbl_1_bss_12C) {
                object->work[0]++;
                lbl_1_bss_12C = 0;
                HuAudFXPlay(1651);
            }
            else {
                temp_f30 = lbl_1_bss_12C / (2 * REFRESH_RATE);
                temp_f31 = sind(temp_f30 * 90.0f) * sind(temp_f30 * 90.0f);
                temp_f20 = (6.0f * frandf()) - 3.0f;
                temp_f19 = (6.0f * frandf()) - 3.0f;
                omSetTra(object, temp_f20, -90 * temp_f31, temp_f19);
                Hu3DModelPosSet(object->model[3], temp_f20, -90 * temp_f31, temp_f19);
                Hu3DModelPosSet(object->model[4], temp_f20, -90 * temp_f31, temp_f19);
            }
            break;

        case 1010:
            if (lbl_1_bss_1C >= 2) {
                object->work[0]++;
                lbl_1_bss_12C = 0;
            }
            break;

        case 1011:
            if (lbl_1_bss_20 > 0 && lbl_1_bss_2FE < 0) {
                lbl_1_bss_2FE = MGSeqWinCreate(fn_1_4DF0(lbl_1_bss_28)->unk118, fn_1_4DF0(lbl_1_bss_28 + 1)->unk118, -1, -1);
                HuAudSStreamPlay(1);
            }
            if (lbl_1_bss_24 < 20) {
                if ((lbl_1_bss_308 % 6) == 0) {
                    lbl_1_bss_24++;
                    fn_1_A0A8(lbl_1_bss_24);
                }
            }
            else {
                if (lbl_1_bss_24 == lbl_1_bss_20) {
                    lbl_1_bss_12C++;
                    if (60.0f < lbl_1_bss_12C) {
                        object->work[0] = 1012;
                        lbl_1_bss_12C = 0;
                    }
                }
            }
            break;

        case 1012:
            lbl_1_bss_12C++;
            if (210.0f < lbl_1_bss_12C) {
                if (lbl_1_bss_2FE < 0 || !MGSeqStatGet(lbl_1_bss_2FE)) {
                    fn_1_1F58(-1);
                    lbl_1_bss_2FE = -1;
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                    object->func = fn_1_E96C;
                }
            }
            break;

        default:
            OSReport("*** main mode error(%d)!!\n", object->work[0]);
            break;
    }
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        temp_r27 = &lbl_1_bss_130[temp_r29];
        if (temp_r27->unk0 >= 0) {
            espPosSet(temp_r27->unk0, temp_r27->unk8, temp_r27->unkC);
            espScaleSet(temp_r27->unk0, temp_r27->unk10, temp_r27->unk14);
            espTPLvlSet(temp_r27->unk0, temp_r27->unk4);
            espDispOn(temp_r27->unk0);
        }
    }
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        temp_r28 = lbl_1_bss_1A4[temp_r29]->data;
        temp_r31 = &lbl_1_data_103C[temp_r28->unk110][0];
        if ((temp_r28->unkE8 & 0x1) == 0) {
            continue;
        }
        fn_1_B754(temp_r31, 0, 0, temp_r28->unkB4);
        for (temp_r24 = 0; temp_r24 < 4; temp_r24++) {
            temp_r20 = lbl_1_bss_1A4[temp_r24]->data;
            fn_1_B754(temp_r31, temp_r20->unk4.x, temp_r20->unk4.z, temp_r28->unkB8[temp_r24]);
            temp_r23 = lbl_1_bss_19C[temp_r24]->data;
            fn_1_B754(temp_r31, temp_r23->unk0.x, temp_r23->unk0.z, temp_r28->unkC8[temp_r24][0]);
            fn_1_B754(temp_r31, temp_r23->unk0.x, temp_r23->unk0.z, temp_r28->unkC8[temp_r24][1]);
            if (temp_r23->unk18 & 0x1) {
                espDispOn(temp_r28->unkC8[temp_r24][1]);
                espDispOff(temp_r28->unkC8[temp_r24][0]);
            }
            else {
                espDispOn(temp_r28->unkC8[temp_r24][0]);
                espDispOff(temp_r28->unkC8[temp_r24][1]);
            }
        }
    }
}

void fn_1_D5E8(omObjData *object)
{
    float temp_f31;
    float temp_f30;
    s32 temp_r30;
    Work3284 *temp_r29;
    temp_f31 = 288;
    temp_f30 = 240;
    lbl_1_bss_10[0] = espEntry(lbl_1_data_1388[lbl_1_bss_190->unk0 + lbl_1_bss_34], 132, 0);
    espPosSet(lbl_1_bss_10[0], temp_f31, temp_f30);
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        temp_r29 = lbl_1_bss_19C[temp_r30]->data;
        lbl_1_bss_10[temp_r30 + 1] = espEntry(lbl_1_data_1310[temp_r30], 131, 0);
        espPosSet(lbl_1_bss_10[temp_r30 + 1], temp_f31 + (0.07f * temp_r29->unk0.x), temp_f30 + (0.07f * temp_r29->unk0.z));
    }
    for (temp_r30 = 0; temp_r30 < 5; temp_r30++) {
        espDrawNoSet(lbl_1_bss_10[temp_r30], 0);
        espTPLvlSet(lbl_1_bss_10[temp_r30], 1.0f);
        espDispOn(lbl_1_bss_10[temp_r30]);
    }
    object->model[0] = Hu3DModelCreateFile(lbl_1_bss_190->unk8[1]);
    Hu3DModelCameraSet(object->model[0], 15);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->model[0], 0);
    Hu3DModelShadowMapSet(object->model[0]);
    omSetTra(object, 0, 0, 0);
    omSetRot(object, 0, -90.0f * lbl_1_bss_34, 0);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M429, 0x22));
    Hu3DModelCameraSet(object->model[1], 15);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(object->model[1], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(object->model[1], 0);
    Hu3DModelShadowMapSet(object->model[1]);
    Hu3DModelPosSet(object->model[1], 0, 0, 0);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M429, 0x23));
    Hu3DModelCameraSet(object->model[2], 15);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(object->model[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(object->model[2], 0);
    Hu3DModelPosSet(object->model[2], 0, 0, 0);
    object->model[3] = Hu3DModelCreateFile(lbl_1_bss_190->unk8[2]);
    Hu3DModelCameraSet(object->model[3], 15);
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(object->model[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(object->model[3], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->model[3], 1);
    Hu3DModelPosSet(object->model[3], 0, 0, 0);
    Hu3DModelRotSet(object->model[3], 0, -90.0f * lbl_1_bss_34, 0);
    object->model[4] = Hu3DModelCreateFile(lbl_1_bss_190->unk8[3]);
    Hu3DModelCameraSet(object->model[4], 15);
    Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(object->model[4], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(object->model[4], 1);
    Hu3DModelPosSet(object->model[4], 0, 0, 0);
    Hu3DModelRotSet(object->model[4], 0, -90.0f * lbl_1_bss_34, 0);
    lbl_1_bss_114 = 45;
    for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
        Hu3DModelAttrReset(object->model[temp_r30], HU3D_ATTR_DISPOFF);
    }
    object->work[0] = 1000;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    object->func = fn_1_B8E0;
}

void ObjectSetup(void)
{
    s32 temp_r31;
    omObjData *temp_r28;
    Work8F68 *temp_r27;
    s32 temp_r22;
    s32 temp_r17;
    Vec sp2C;
    s32 sp1C;
    s32 sp18;
    s32 sp14;

    OSReport("******* M429 ObjectSetup *********\n");
    nMap = 0;
    nChar = 0;
    lbl_1_bss_33C = omInitObjMan(100, 8192);
    omGameSysInit(lbl_1_bss_33C);
    lbl_1_bss_308 = 0;
    lbl_1_bss_2FE = -1;
    lbl_1_bss_2FC = -1;
    lbl_1_bss_28 = -1;
    lbl_1_bss_24 = 0;
    lbl_1_bss_20 = 0;
    lbl_1_bss_1C = 0;
    lbl_1_bss_2F8 = -1;
    lbl_1_bss_4 = -1;
    lbl_1_bss_0 = -1;
    lbl_1_bss_11C = 0;
    lbl_1_bss_120 = 850;
    lbl_1_bss_118 = 450;
    for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
        lbl_1_bss_2C[temp_r31] = 0;
    }
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        lbl_1_bss_130[temp_r31].unk0 = -1;
        lbl_1_bss_130[temp_r31].unk4 = 0;
    }
    lbl_1_bss_34 = frandmod(4);
    fn_1_2684();
    fn_1_A118();
    temp_r17 = Hu3DGLightCreateV(&lbl_1_data_111C, &lbl_1_data_1128, &lbl_1_data_1134);
    Hu3DGLightStaticSet(temp_r17, 1);
    Hu3DGLightInfinitytSet(temp_r17);
    Hu3DShadowCreate(30, 10, 20000);
    Hu3DShadowTPLvlSet(0.5f);
    VECNormalize(&lbl_1_data_1138, &sp2C);
    Hu3DShadowPosSet(&lbl_1_data_1138, &sp2C, &lbl_1_data_1144);
    omMakeGroupEx(lbl_1_bss_33C, 0, 4);
    lbl_1_bss_1A4 = omGetGroupMemberListEx(lbl_1_bss_33C, 0);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r28 = omAddObjEx(lbl_1_bss_33C, 100, 1, 10, 0, fn_1_8F68);
        temp_r28->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work8F68), MEMORY_DEFAULT_NUM);
        temp_r28->work[0] = temp_r31;
        temp_r27 = temp_r28->data;
        temp_r27->unk110 = -1;
        temp_r27->unk114 = temp_r28->work[0];
        temp_r27->unk120 = GWPlayerCfg[temp_r27->unk114].group;
    }
    (void)&sp14;

    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        sp14 = -1;
        sp18 = 40;
        for (temp_r22 = 0; temp_r22 < 4; temp_r22++) {
            temp_r27 = lbl_1_bss_1A4[temp_r22]->data;
            if (temp_r27->unk110 < 0) {
                sp1C = temp_r27->unk114 + (temp_r27->unk120 * 4);
                if (sp18 > sp1C) {
                    sp18 = sp1C;
                    sp14 = temp_r22;
                }
            }
        }
        ((Work8F68 *)lbl_1_bss_1A4[sp14]->data)->unk110 = temp_r31;
    }
    omMakeGroupEx(lbl_1_bss_33C, 1, 4);
    lbl_1_bss_1A0 = omGetGroupMemberListEx(lbl_1_bss_33C, 1);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r28 = omAddObjEx(lbl_1_bss_33C, 101, 2, 1, 1, fn_1_99F0);
        temp_r28->work[0] = temp_r31;
    }
    omMakeGroupEx(lbl_1_bss_33C, 2, 4);
    lbl_1_bss_19C = omGetGroupMemberListEx(lbl_1_bss_33C, 2);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r28 = omAddObjEx(lbl_1_bss_33C, 102, 2, 0, 2, fn_1_33F8);
        temp_r28->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work3284), MEMORY_DEFAULT_NUM);
        temp_r28->work[0] = temp_r31;
    }
    lbl_1_bss_1A = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M429, 0x2F));
    Hu3DModelAttrSet(lbl_1_bss_1A, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_1A, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    omMakeGroupEx(lbl_1_bss_33C, 3, 20);
    lbl_1_bss_198 = omGetGroupMemberListEx(lbl_1_bss_33C, 3);
    lbl_1_bss_1A8 = omAddObjEx(lbl_1_bss_33C, 104, 5, 0, -1, fn_1_31AC);
    MapObject[nMap++] = lbl_1_bss_1A8;
    lbl_1_bss_1AC = omAddObjEx(lbl_1_bss_33C, 105, 5, 0, -1, fn_1_D5E8);
    lbl_1_bss_C = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M429, 0x3F));
    HuSprAnimLock(lbl_1_bss_C);
    lbl_1_bss_8 = Hu3DParManCreate(lbl_1_bss_C, 20, &lbl_1_data_13E8);
    Hu3DParManAttrSet(lbl_1_bss_8, 1);
}

void fn_1_E96C(omObjData *object)
{
    s32 temp_r31;
    if (lbl_1_bss_0 >= 0) {
        HuAudFXStop(lbl_1_bss_0);
        lbl_1_bss_0 = -1;
    }
    if (WipeStatGet()) {
        return;
    }
    if (lbl_1_bss_2FE >= 0) {
        MGSeqKill(lbl_1_bss_2FE);
    }
    if (lbl_1_bss_2FC >= 0) {
        MGSeqKill(lbl_1_bss_2FC);
    }
    MGSeqKillAll();
    HuAudAllStop();
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        CharModelKill(lbl_1_data_0[GWPlayerCfg[temp_r31].character]);
    }
    omOvlReturnEx(1, 1);
}
