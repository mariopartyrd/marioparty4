#include "REL/executor.h"
#include "datadir_enum.h"
#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/mtx/GeoTypes.h"
#include "dolphin/pad.h"
#include "dolphin/types.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/wipe.h"

#include "game/gamework.h"
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

#include "game/window.h"
#include "string.h"
#include "version.h"

#ifndef __MWERKS__
#include "game/audio.h"
#include "game/hsfex.h"

void HuSysVWaitSet(s16 vcount);
#endif

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

typedef struct UnkData1380Struct {
    /* 0x00 */ char **unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 *unk_24;
    /* 0x28 */ s32 *unk_28;
    /* 0x2C */ s32 *unk_2C;
    /* 0x30 */ Vec *unk_30;
    /* 0x34 */ Vec *unk_34;
} UnkData1380Struct; /* size = 0x38 */

typedef struct UnkData1450Struct {
    /* 0x00 */ char *unk_00;
    /* 0x04 */ Vec unk_04;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} UnkData1450Struct; /* size = 0x24 */

typedef struct UnkData5CCStruct {
    /* 0x00 */ char *unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ float unk_0C;
} UnkData5CCStruct; /* size = 0x10 */

typedef struct UnkDataA0CStruct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 *unk_18;
} UnkDataA0CStruct; /* size = 0x1C */

typedef struct UnkData94CStruct {
    /* 0x00 */ s32 unk_00;
    /* 0x00 */ float unk_04;
    /* 0x00 */ float unk_08;
    /* 0x00 */ float unk_0C;
    /* 0x00 */ u32 unk_10;
} UnkData94CStruct; /* size = 0x14 */

typedef struct UnkDataA80Struct {
    char *unk_00;
    Vec unk_04;
    s32 unk_10;
    float unk_14;
    Vec unk_18;
    s32 unk_24;
    s32 unk_28;
} UnkDataA80Struct; /* size = 0x2C */

typedef struct UnkData204Struct {
    float unk_00;
    s32 unk_04;
} UnkData204Struct; /* size = 0x08 */

// these are copied from m461Dll/main.c
typedef void (*PlayerOldHook)(omObjData *obj);
typedef Vec *(*PlayerOldPosHook)(omObjData *obj);

typedef struct work_playerold {
    omObjData *unk_00;
    PlayerOldHook unk_04;
    PlayerOldPosHook unk_08;
    PlayerOldHook unk_0C;
    PlayerOldHook unk_10;
    s32 *unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    Vec *unk_50;
    Vec unk_54;
    float unk_60;
    s32 unk_64;
    Vec *unk_68;
    Vec unk_6C;
    Vec unk_78;
    Vec unk_84;
    Vec unk_90;
    float unk_9C;
    float unk_A0;
    float unk_A4;
    float unk_A8;
    Vec unk_AC;
    float unk_B8;
    float unk_BC;
    float unk_C0;
} WorkPlayerOld;

typedef WorkPlayerOld *(*PlayerOldFind)(int no);

typedef struct UnkM450Struct5 {
    WorkPlayerOld unk_00;
    UnkData94CStruct *unk_C4;
    float unk_C8;
    float unk_CC;
    Vec unk_D0;
    Vec unk_DC;
    float unk_E8;
    float unk_EC;
    s32 unk_F0;
    s32 unk_F4;
    float unk_F8;
    u32 unk_FC;
    s32 unk_100;
    s32 unk_104;
    s32 unk_108;
    s32 unk_10C;
    s32 unk_110;
    s32 unk_114;
    s32 unk_118;
    s32 unk_11C;
    s32 unk_120;
} UnkM450Struct5; /* size = 0x124 */

typedef struct UnkM450Struct4 {
    Vec unk_00;
    Vec unk_0C;
    Vec unk_18;
    Vec unk_24;
    Vec unk_30;
    float unk_3C;
    float unk_40;
    float unk_44;
    float unk_48;
    float unk_4C;
    float unk_50;
    s32 unk_54;
    s32 unk_58;
    float unk_5C;
    float unk_60;
    Vec unk_64;
    s32 unk_70;
    s32 unk_74;
    s32 unk_78;
    s32 unk_7C;
} UnkM450Struct4; /* size = 0x80 */

typedef struct UnkM450Struct3 {
    WorkPlayerOld unk_00;
    UnkData204Struct *unk_C4;
    Vec2f *unk_C8;
    char *unk_CC;
    float *unk_D0;
    Vec unk_D4;
    float unk_E0;
    float unk_E4;
    float unk_E8;
    float unk_EC;
    float unk_F0;
    float unk_F4;
    s32 unk_F8;
    s32 unk_FC;
    float unk_100;
    float unk_104;
    float unk_108;
    s32 unk_10C;
    s32 unk_110;
    Vec unk_114;
    Vec unk_120;
    s32 unk_12C;
    s32 unk_130;
    s32 unk_134;
    s32 unk_138;
    s32 unk_13C;
    s32 unk_140;
    float unk_144;
    s32 unk_148;
    s32 unk_14C;
    s32 unk_150;
    u32 unk_154;
} UnkM450Struct3; /* size = 0x158 */

typedef struct UnkM450Struct2 {
    s32 unk_00;
    Vec unk_04;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    float unk_20;
    float unk_24;
    float unk_28;
    float unk_2C;
    Vec unk_30;
    s16 unk_3C;
    s16 unk_3E;
} UnkM450Struct2; /* size = 0x40 */

struct UnkM450Struct;
typedef void (*UnkM450ModelFunc)(ModelData *, struct UnkM450Struct *, Mtx);

typedef struct UnkM450Struct {
    UnkM450ModelFunc unk_00;
    AnimData *unk_04;
    Vec *unk_08;
    float *unk_0C;
    UnkM450Struct2 *unk_10;
    Vec *unk_14;
    Vec2f *unk_18;
    Vec2f *unk_1C;
    GXColor *unk_20;
    void *unk_24;
    Vec unk_28;
    float unk_34;
    float unk_38;
    float unk_3C;
    float unk_40;
    float unk_44;
    float unk_48;
    float unk_4C;
    float unk_50;
    float unk_54;
    u32 unk_58;
    float unk_5C;
    float unk_60;
    s16 unk_64;
    s16 unk_66;
    s16 unk_68;
    u8 unk_6A;
    u8 unk_6B;
} UnkM450Struct; /* size = 0x6C */

s32 fn_1_125C0(s32 arg0, s32 arg1);
s32 fn_1_13B90(s32 arg0);
Vec *fn_1_16314(s32 arg0);
void fn_1_16BC4(Vec *arg0, Vec *arg1, s32 arg2);
void fn_1_17360(Vec *arg0, float arg8);
void fn_1_17970(s32 arg0, s32 arg1, float arg8);
void fn_1_18424(s32 arg0, Vec *arg1);
void fn_1_186A8();
s32 fn_1_1964C(Vec *arg0, Vec *arg1);
s32 fn_1_19798();
s32 fn_1_19A10(WorkPlayerOld *arg0, Vec *arg1);
s32 fn_1_1B4C8(UnkM450Struct5 *arg0);
void fn_1_1B510(s32 arg0);
s32 fn_1_1C39C(UnkM450Struct5 *arg0);
void fn_1_20170(omObjData *object);
void fn_1_2902C();
void fn_1_298EC(omObjData *object);
void fn_1_A968(s32 arg0, float arg8, u32 arg1, s32 arg2, float arg9);
s32 fn_1_E0E8(s32 arg0, s32 arg1);
s32 fn_1_E178(s32 arg0, s32 arg1);
void fn_1_E1A8(s32 arg0, s32 arg1, float arg8, u32 arg2, s32 arg3, float arg9);

s16 lbl_1_data_0[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

s32 lbl_1_data_10[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

float lbl_1_data_30[0xA] = { 70.0f, 70.0f, 70.0f, 70.0f, 70.0f, 70.0f, 70.0f, 70.0f, 70.0f, 100.0f };

float lbl_1_data_58[0xA] = {
    150.0f,
    170.0f,
    190.0f,
    170.0f,
    160.0f,
    150.0f,
    180.0f,
    200.0f,
    150.0f,
    200.0f,
};

PlayerOldFind lbl_1_bss_1AC;
float lbl_1_bss_1A8;
omObjData *lbl_1_bss_1A4;
omObjData *lbl_1_bss_1A0;
omObjData *lbl_1_bss_144[0x17];
omObjData **lbl_1_bss_140;
omObjData **lbl_1_bss_13C;
// data: UnkM450Struct5
omObjData *lbl_1_bss_138;
// data: UnkM450Struct3
omObjData *lbl_1_bss_134;
// data: UnkM450Struct3
omObjData **lbl_1_bss_130;
float lbl_1_bss_12C;
float lbl_1_bss_128;
float lbl_1_bss_124;
s32 lbl_1_bss_120;
s32 lbl_1_bss_11C;
s32 lbl_1_bss_118;
s32 lbl_1_bss_114;
s32 lbl_1_bss_110;
s32 lbl_1_bss_10C;
s32 lbl_1_bss_108;
UnkDataA80Struct *lbl_1_bss_104;
s32 lbl_1_bss_100;
UnkData1380Struct *lbl_1_bss_FC;
s32 lbl_1_bss_F8;
Vec lbl_1_bss_EC;
void *lbl_1_bss_E8[1];
UnkM450Struct4 *lbl_1_bss_E4[1];
UnkM450Struct4 *lbl_1_bss_DC[2];
s32 lbl_1_bss_D8;
Vec lbl_1_bss_CC;
float lbl_1_bss_C8;
s32 lbl_1_bss_C4;
s32 lbl_1_bss_B8[3];
Mtx lbl_1_bss_88;
Vec lbl_1_bss_4C[5];
Vec lbl_1_bss_34[2];
s16 lbl_1_bss_2C[4];
AnimData *lbl_1_bss_28;
s16 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
AnimData *lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

#if VERSION_NTSC
#define _1606_BY_REFRESH_RATE 26.766666f
#else
#define _1606_BY_REFRESH_RATE 32.120003f
#endif

void fn_1_23B4(WorkPlayerOld *player)
{
    s32 i;
    for (i = 0; i < 8; i++) {
        if (player->unk_44 == player->unk_14[i]) {
            player->unk_40 = lbl_1_data_10[i];
            return;
        }
    }
    player->unk_40 = -1;
}

void fn_1_2418(float *minDist, s32 *state, s32 stateNew, Vec *posA, float aYOfs, Vec *posB, float bYOfs)
{
    Vec pointA = *posA;
    Vec pointB = *posB;
    float dist;
    pointA.y += aYOfs;
    pointB.y += bYOfs;
    dist = VECDistance(&pointA, &pointB);
    if (*minDist > dist) {
        *minDist = dist;
        *state = stateNew;
    }
}

void fn_1_24F8(WorkPlayerOld *player1, WorkPlayerOld *player2, float *minDist, s32 *state)
{
    *minDist = 10 * (player1->unk_BC + player2->unk_BC);
    fn_1_2418(minDist, state, 0, &player1->unk_6C, player1->unk_BC, &player2->unk_6C, player2->unk_BC);
    fn_1_2418(minDist, state, 1, &player1->unk_6C, player1->unk_C0 - player1->unk_BC, &player2->unk_6C, player2->unk_C0 - player2->unk_BC);
    fn_1_2418(minDist, state, 2, &player1->unk_6C, player1->unk_BC, &player2->unk_6C, player2->unk_C0 - player2->unk_BC);
    fn_1_2418(minDist, state, 3, &player1->unk_6C, player1->unk_C0 - player1->unk_BC, &player2->unk_6C, player2->unk_BC);
}

s32 fn_1_2824(WorkPlayerOld *player, WorkPlayerOld *player2)
{
    Vec dir;
    Vec dir2;
    float dist;

    player->unk_3C |= 0x1;
    player->unk_90.x = player->unk_20 / 4.0f;
    player->unk_90.z = -(float)player->unk_24 / 4.0f;
    if (player->unk_90.x != 0.0f || player->unk_90.z != 0.0f) {
#ifdef NON_MATCHING
        return (s32)(uintptr_t)player;
#else
        return;
#endif
    }
    VECSubtract(&player->unk_6C, &player2->unk_6C, &dir);
    dist = VECMagXZ(&dir);
    if (0.0f == dist) {
        dir.x = 0;
        dir.z = -1;
    }
    else {
        dir.x /= dist;
        dir.z /= dist;
    }
    VECSubtract(&player->unk_6C, &player->unk_78, &dir2);
    dist = VECMagXZ(&dir2);
    if (5 > dist) {
        dist = 5;
    }
    player->unk_90.x = dir.x * dist;
    player->unk_90.z = dir.z * dist;
}

void fn_1_2BD0(WorkPlayerOld *player, float arg1, float arg2)
{
    player->unk_38 = 1;
    player->unk_84.y = arg1;
    player->unk_A4 = arg2;
    if (player->unk_3C & 0x2) {
        player->unk_3C &= ~0x2;
    }
}

void fn_1_2C00(PlayerOldFind find, float yDist)
{
    lbl_1_bss_1AC = find;
    lbl_1_bss_1A8 = yDist;
}

void fn_1_2C1C(WorkPlayerOld *player, omObjData *obj, s32 arg2, s32 arg3, s32 *arg4, s32 arg5, Vec *pos, float arg7)
{
    player->unk_00 = obj;
    player->unk_18 = arg2;
    player->unk_1C = arg3;
    player->unk_14 = arg4;
    player->unk_04 = NULL;
    player->unk_08 = NULL;
    player->unk_0C = NULL;
    player->unk_10 = NULL;
    player->unk_50 = NULL;
    player->unk_64 = 0;
    player->unk_68 = NULL;
    player->unk_38 = 0;
    player->unk_3C = 0;
    player->unk_44 = arg5;
    player->unk_48 = 0;
    player->unk_4C = 0;
    fn_1_23B4(player);
    player->unk_9C = arg7;
    player->unk_6C = *pos;
    player->unk_78 = *pos;
    player->unk_84.x = 0;
    player->unk_84.y = 0;
    player->unk_84.z = 0;
    player->unk_B8 = 1;
    player->unk_A8 = 0;
    player->unk_BC = lbl_1_data_30[player->unk_1C];
    player->unk_C0 = lbl_1_data_58[player->unk_1C];
}

void fn_1_2DA8(WorkPlayerOld *player, PlayerOldHook func)
{
    player->unk_04 = func;
}

void fn_1_2DB0(WorkPlayerOld *player, PlayerOldPosHook func)
{
    player->unk_08 = func;
}

void fn_1_2DB8(WorkPlayerOld *player, PlayerOldHook func)
{
    player->unk_0C = func;
}

void fn_1_2DC0(WorkPlayerOld *player, PlayerOldHook func)
{
    player->unk_10 = func;
}

void fn_1_2DC8(WorkPlayerOld *player, s32 count, Vec *data)
{
    player->unk_64 = count;
    player->unk_68 = data;
}

void fn_1_2DD4(WorkPlayerOld *player)
{
    omSetTra(player->unk_00, player->unk_6C.x, player->unk_6C.y, player->unk_6C.z);
    omSetRot(player->unk_00, 0.0f, player->unk_9C, 0.0f);
}

void fn_1_2E34(WorkPlayerOld *player)
{
    BOOL addTime;
    s32 i;
    player->unk_3C &= ~0x100;
    if (player->unk_3C & 0x8) {
        return;
    }
    if (NULL == lbl_1_bss_1AC) {
        return;
    }
    addTime = FALSE;
    for (i = 0; i < 4; i++) {
        WorkPlayerOld *player2 = lbl_1_bss_1AC(i);
        BOOL fixPos;
        float minDist;
        s32 state;
        if (player == player2) {
            continue;
        }
        if (player2->unk_3C & 0x8) {
            continue;
        }
        fixPos = FALSE;
        fn_1_24F8(player, player2, &minDist, &state);
        if (minDist < player->unk_BC + player2->unk_BC) {
            if (state < 2) {
                fixPos = TRUE;
                if (player->unk_38 == 1) {
                    fn_1_2824(player, player2);
                }
            }
            else {
                if (state == 2 && player->unk_38 == 1) {
                    fn_1_2824(player, player2);
                    player->unk_3C |= 0x100;
                    player->unk_A4 = 0;
                    if (!(player2->unk_3C & 0x100)) {
                        player->unk_84.y = _1606_BY_REFRESH_RATE;
                    }
                }
                if (state == 3) {
                    fixPos = TRUE;
                    if (player->unk_38 == 1) {
                        if (0.0f < player->unk_84.y) {
                            player->unk_84.y = 0.0f;
                        }
                        player->unk_A4 = 0;
                    }
                }
            }
        }
        if (fixPos) {
            Vec dir;
            addTime = TRUE;
            VECSubtract(&player->unk_6C, &player2->unk_6C, &dir);
            if (0.0f == minDist) {
                dir.x = 0;
                dir.z = -1;
            }
            else {
                dir.x /= minDist;
                dir.z /= minDist;
            }
            player->unk_6C.x = player2->unk_6C.x + (dir.x * (player->unk_BC + player2->unk_BC));
            player->unk_6C.z = player2->unk_6C.z + (dir.z * (player->unk_BC + player2->unk_BC));
        }
    }
    if (addTime) {
        player->unk_4C++;
    }
    else {
        player->unk_4C = 0;
    }
}

float fn_1_39C4(WorkPlayerOld *player, float arg2)
{
    Vec *pos;
    s32 i;
    AddX = 0.0f;
    AddZ = 0.0f;
    MapWall(player->unk_BC, player->unk_6C.x, arg2 + player->unk_BC, player->unk_6C.z);
    player->unk_6C.x += AddX;
    player->unk_6C.z += AddZ;
    if (NULL != player->unk_68) {
        for (pos = player->unk_68, i = 0; i < player->unk_64; i++, pos += 2) {
            int num = 0;
            if (pos[0].x == pos[1].x || pos[0].x > player->unk_6C.x || pos[1].x < player->unk_6C.x) {
                num++;
            }
            if (pos[0].y == pos[1].y || pos[0].y > player->unk_6C.y || pos[1].y < player->unk_6C.y) {
                num++;
            }
            if (pos[0].z == pos[1].z || pos[0].z > player->unk_6C.z || pos[1].z < player->unk_6C.z) {
                num++;
            }
            if (num == 3) {
                if (pos[0].x != pos[1].x) {
                    if (pos[0].x > player->unk_6C.x) {
                        player->unk_6C.x = pos[0].x + player->unk_BC;
                    }
                    if (pos[1].x < player->unk_6C.x) {
                        player->unk_6C.x = pos[1].x - player->unk_BC;
                    }
                }
                if (pos[0].y != pos[1].y) {
                    if (pos[0].y > player->unk_6C.y) {
                        player->unk_6C.y = pos[0].y;
                    }
                    if (pos[1].y < player->unk_6C.y) {
                        player->unk_6C.y = pos[1].y;
                    }
                }
                if (pos[0].z != pos[1].z) {
                    if (pos[0].z > player->unk_6C.z) {
                        player->unk_6C.z = pos[0].z + player->unk_BC;
                    }
                    if (pos[1].z < player->unk_6C.z) {
                        player->unk_6C.z = pos[1].z - player->unk_BC;
                    }
                }
            }
        }
    }
    return ABS(AddX) + ABS(AddZ);
}

void fn_1_3CE0(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    *motAttr = HU3D_MOTATTR_LOOP;
    *state = 0;
    if (0.5f <= player->unk_A0) {
        if (7.0f <= player->unk_A0) {
            *state = 2;
        }
        else {
            *state = 1;
        }
    }

    if (player->unk_14[3] >= 0 && (player->unk_28 & 0x100)) {
        fn_1_2BD0(player, _1606_BY_REFRESH_RATE, 1.0f);
        *motAttr = HU3D_MOTATTR_NONE;
        *state = 3;
    }
}

void fn_1_3DB8(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    if (0.0f < player->unk_A4) {
        if (player->unk_2C & 0x100) {
            player->unk_A4++;
            if (4.0f < player->unk_A4) {
                player->unk_A4 = 0;
            }
            else {
                player->unk_84.y += 219.0f / REFRESH_RATE;
            }
        }
        else {
            player->unk_A4 = 0;
        }
    }
    player->unk_84.y += -146.0f / REFRESH_RATE;
    if (player->unk_14[5] >= 0 && (player->unk_28 & 0x140)) {
        player->unk_38 = 3;
        player->unk_84.y = 0;
        player->unk_3C &= ~0x3;
        player->unk_3C |= 0x4;
        *motAttr = HU3D_MOTATTR_NONE;
        *state = 5;
    }
}

void fn_1_3ECC(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    if ((player->unk_3C & 0x1000) || Hu3DMotionEndCheck(player->unk_00->model[0])) {
        player->unk_3C &= ~0x3;
        if (player->unk_40 == 6) {
            player->unk_38 = 4;
            *motAttr = HU3D_MOTATTR_NONE;
            *state = 7;
        }
        else {
            player->unk_38 = 0;
            *motAttr = HU3D_MOTATTR_LOOP;
            *state = 0;
        }
    }
}

void fn_1_3F84(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    if (Hu3DMotionShiftIDGet(player->unk_00->model[0]) < 0 && Hu3DMotionEndCheck(player->unk_00->model[0])) {
        fn_1_2BD0(player, 0.0f, 0.0f);
    }
}

void fn_1_4024(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    if (Hu3DMotionShiftIDGet(player->unk_00->model[0]) < 0 && Hu3DMotionEndCheck(player->unk_00->model[0])) {
        player->unk_3C &= ~0x4;
        player->unk_38 = 0;
        *motAttr = HU3D_MOTATTR_LOOP;
        *state = 0;
    }
}

void fn_1_40C0(WorkPlayerOld *player)
{
    u32 motAttr = HU3D_MOTATTR_NONE;
    s32 state = -1;
    float temp_f28;
    float temp_f23;
    float temp_f22;
    Vec *pos;
    BOOL temp_r27;
    if (player->unk_3C & 0x1) {
        player->unk_84.x = player->unk_90.x;
        player->unk_84.z = player->unk_90.z;
    }
    else {
        player->unk_84.x = player->unk_20 / 4.0f;
        player->unk_84.z = -(float)player->unk_24 / 4.0f;
        if (player->unk_38 == 1 && 0.0f == player->unk_84.x && 0.0f == player->unk_84.z) {
            player->unk_84.x = 0.98f * (player->unk_6C.x - player->unk_78.x);
            player->unk_84.z = 0.98f * (player->unk_6C.z - player->unk_78.z);
        }
        if (player->unk_3C & 0x14) {
            player->unk_84.x = 0;
            player->unk_84.z = 0;
            player->unk_28 = 0;
        }
    }
    player->unk_78 = player->unk_6C;
    player->unk_A0 = VECMagXZ(&player->unk_84);
    if (0.5f <= player->unk_A0) {
        if (10.0f <= player->unk_A0) {
            player->unk_84.x /= player->unk_A0;
            player->unk_84.z /= player->unk_A0;
            player->unk_A0 = 10;
            player->unk_84.x = 10 * player->unk_84.x;
            player->unk_84.z = 10 * player->unk_84.z;
        }
    }
    else {
        player->unk_84.x = 0;
        player->unk_84.z = 0;
        player->unk_A0 = 0;
    }
    player->unk_84.x *= player->unk_B8;
    player->unk_84.z *= player->unk_B8;
    player->unk_A0 *= player->unk_B8;
    if (player->unk_3C & 0x800) {
        player->unk_28 |= 0x100;
        player->unk_2C |= 0x100;
        if (player->unk_38 == 1) {
            if (0.0f == player->unk_A4) {
                player->unk_3C &= ~0x800;
            }
        }
    }
    switch (player->unk_38) {
        case 0:
            fn_1_3CE0(player, &state, &motAttr);
            break;

        case 1:
            fn_1_3DB8(player, &state, &motAttr);
            break;

        case 2:
            fn_1_3ECC(player, &state, &motAttr);
            break;

        case 3:
            fn_1_3F84(player, &state, &motAttr);
            break;

        case 4:
            fn_1_4024(player, &state, &motAttr);
            break;

        default:
            OSReport("*** player action error(%d)!!\n", player->unk_38);
            break;
    }
    if (player->unk_3C & 0x2000) {
        player->unk_84.y = 0;
    }
    temp_f28 = 0.0f;
    if (50.0f < ABS(player->unk_84.y)) {
        player->unk_84.y = 50.0f * ((0.0f > player->unk_84.y) ? -1 : 1);
    }
    if (player->unk_3C & 0x2) {
        Mtx rotMtx;
        MTXRotDeg(rotMtx, 'y', player->unk_50[2].x - player->unk_60);
        MTXMultVec(rotMtx, &player->unk_54, &player->unk_54);
        VECAdd(&player->unk_54, &player->unk_50[0], &player->unk_6C);
        player->unk_9C += player->unk_50[2].x - player->unk_60;
    }
    temp_f22 = player->unk_6C.y;
    VECAdd(&player->unk_6C, &player->unk_84, &player->unk_6C);
    if ((player->unk_3C & 0x1) == 0 && (0.0f != player->unk_84.x || 0.0f != player->unk_84.z)) {
        player->unk_9C = fn_1_1E20(player->unk_9C, atan2d(player->unk_84.x, player->unk_84.z), 0.4f * player->unk_B8);
    }
    temp_f28 += fn_1_39C4(player, temp_f22);
    if (nMap == 0) {
        player->unk_A8 = lbl_1_bss_1A8;
    }
    else {
        player->unk_A8 = MapPos(player->unk_6C.x, player->unk_6C.y, player->unk_6C.z, player->unk_C0, &player->unk_AC);
    }
    temp_r27 = FALSE;
    if (NULL != player->unk_08) {
        pos = player->unk_08(player->unk_00);
        if (NULL != pos) {
            if (player->unk_A8 < pos[1].y) {
                temp_r27 = TRUE;
                player->unk_50 = pos;
                player->unk_A8 = pos[1].y;
            }
        }
    }
    if (!temp_r27 && (player->unk_3C & 0x2)) {
        player->unk_3C &= ~0x2;
    }
    if (player->unk_38 == 1 && player->unk_A8 >= player->unk_6C.y) {
        player->unk_38 = 2;
        player->unk_3C &= ~0x3;
        player->unk_6C.y = player->unk_A8;
        player->unk_84.y = 0;
        motAttr = HU3D_MOTATTR_NONE;
        state = 4;
        if (player->unk_40 == 5) {
            state = 6;
            if (NULL != player->unk_10) {
                player->unk_10(player->unk_00);
            }
            if (player->unk_18 < 4) {
                omVibrate(player->unk_18, 12, 4, 2);
            }
        }
        if (player->unk_3C & 0x200) {
            state = -1;
            if (NULL != player->unk_0C) {
                player->unk_0C(player->unk_00);
            }
        }
        if (temp_r27) {
            player->unk_3C |= 0x2;
        }
    }
    temp_f23 = player->unk_6C.y - player->unk_A8;
    if (player->unk_38 == 0 && 10.0f < temp_f23) {
        if ((player->unk_3C & 0x2000) == 0) {
            if ((player->unk_3C & 0x400) != 0) {
                player->unk_3C |= 0x800;
            }
            else {
                fn_1_2BD0(player, 0.0f, 0.0f);

                motAttr = HU3D_MOTATTR_NONE;
                state = 3;
            }
        }
    }
    else if (temp_r27) {
        if (!(player->unk_3C & 0x2)) {
            player->unk_6C.y = player->unk_A8;
            player->unk_3C |= 0x2;
        }
    }
    fn_1_2E34(player);
    if (NULL != player->unk_04) {
        player->unk_04(player->unk_00);
    }
    temp_f28 += fn_1_39C4(player, player->unk_6C.y);
    if (player->unk_3C & 0x2) {
        player->unk_60 = player->unk_50[2].x;
        VECSubtract(&player->unk_6C, &player->unk_50[0], &player->unk_54);
    }
    if (0.0f != temp_f28) {
        player->unk_48++;
    }
    else {
        player->unk_48 = 0;
    }
    if (state >= 0 && player->unk_40 != state) {
        player->unk_40 = state;
        player->unk_44 = player->unk_14[player->unk_40];
        if (player->unk_44 >= 0 && !(player->unk_3C & 0x20)) {
            Hu3DMotionShiftSet(player->unk_00->model[0], player->unk_00->motion[player->unk_44], 0, 8, motAttr);
        }
    }
}

void fn_1_4ED8(WorkPlayerOld *player, s32 motNo)
{
    s32 i;
    player->unk_44 = motNo;
    player->unk_38 = 0;
    player->unk_3C &= 0x1400;
    player->unk_78 = player->unk_6C;
    player->unk_84.x = 0;
    player->unk_84.y = 0;
    player->unk_84.z = 0;
    fn_1_23B4(player);
    if (player->unk_40 == 3) {
        Hu3DModelAttrReset(player->unk_00->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DMotionSet(player->unk_00->model[0], player->unk_00->motion[player->unk_44]);
        Hu3DMotionTimeSet(player->unk_00->model[0], Hu3DMotionMaxTimeGet(player->unk_00->model[0]) - 1);
    }
    else if (player->unk_40 == 5) {
        player->unk_38 = 3;
        player->unk_3C |= 0x4;
        Hu3DModelAttrReset(player->unk_00->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DMotionSet(player->unk_00->model[0], player->unk_00->motion[player->unk_44]);
        Hu3DMotionTimeSet(player->unk_00->model[0], Hu3DMotionMaxTimeGet(player->unk_00->model[0]) - 1);
    }
    else {
        Hu3DModelAttrReset(player->unk_00->model[0], HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(player->unk_00->model[0], player->unk_00->motion[player->unk_44], 0, 8, HU3D_MOTATTR_LOOP);
    }
}

void fn_1_5128(WorkPlayerOld *player, s32 attr)
{
    player->unk_3C |= attr;
}

void fn_1_5138(WorkPlayerOld *player, s32 attr)
{
    player->unk_3C &= ~attr;
}

void fn_1_5148(ModelData *model, UnkM450Struct *arg1, Mtx matrix)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;

    UnkM450Struct2 *var_r31;
    WorkPlayerOld *var_r29;
    GXColor *var_r28;
    s16 var_r27;
    UnkM450Struct5 *var_r26;

    var_r26 = lbl_1_bss_138->data;
    var_r29 = &var_r26->unk_00;
    var_r31 = arg1->unk_10;
    var_r28 = arg1->unk_20;
    arg1->unk_66 = 0;
    for (var_r27 = 0; var_r27 < arg1->unk_64; var_r27++, var_r31++, var_r28++) {
        if (var_r31->unk_3E >= 0) {
            var_r31->unk_10 += var_r31->unk_1C;
            if (var_r31->unk_20 < var_r31->unk_10) {
                var_r31->unk_3E = -1;
            }
            else {
                arg1->unk_66++;
                if (NULL != arg1->unk_08) {
                    var_r31->unk_04 = *arg1->unk_08;
                }
                if (NULL != arg1->unk_0C) {
                    var_r31->unk_14 = *arg1->unk_0C;
                }
                var_r31->unk_30.x = var_r31->unk_04.x + (var_r31->unk_10 * sind((var_r31->unk_14 + var_r31->unk_18)));
                var_r31->unk_30.y = var_r31->unk_30.y + (0.03f * (var_r31->unk_24 - var_r31->unk_30.y));
                var_r31->unk_30.z = var_r31->unk_04.z + (var_r31->unk_10 * cosd((var_r31->unk_14 + var_r31->unk_18)));
                var_f31 = var_r31->unk_10 / var_r31->unk_20;
                var_f29 = 512.0 * cosd((90.0f * var_f31));
                var_r28->a = 255.0f < var_f29 ? 255.0f : var_f29;
                var_r31->unk_3C = arg1->unk_68 * var_f31;
                if (arg1->unk_68 <= var_r31->unk_3C) {
                    var_r31->unk_3C = arg1->unk_68 - 1;
                }
                var_f31 *= 2.0f;
                if (1.0f < var_f31) {
                    var_f31 = 1.0f;
                }
                var_r31->unk_2C = sind((100.0f * var_f31));
                var_f30 = (26.666666f * var_r31->unk_2C) + var_r29->unk_BC;
                sp14 = var_r29->unk_6C;
                sp14.y += var_f30;
                sp8 = var_r29->unk_6C;
                sp8.y += var_r29->unk_C0 - var_f30;
                if ((var_r31->unk_3C < 0xC)
                    && ((var_f30 > VECDistance(&sp14, &var_r31->unk_30)) || (var_f30 > VECDistance(&sp8, &var_r31->unk_30)))) {
                    var_r26->unk_FC |= 0x20;
                }
            }
        }
    }
}
void fn_1_5548(Vec *arg0, float *arg1)
{
    arg1[0] = arg0[0].x;
    arg1[4] = arg0[0].y;
    arg1[8] = arg0[0].z;
    arg1[1] = arg0[1].y;
    arg1[5] = arg0[1].z;
    arg1[9] = arg0[2].x;
    arg1[2] = arg0[2].z;
    arg1[6] = arg0[3].x;
    arg1[10] = arg0[3].y;
    arg1[3] = 0.0f;
    arg1[7] = 0.0f;
    arg1[11] = 0.0f;
}

void fn_1_55C4(Vec *arg0, Vec *arg1, s16 arg2, float arg8)
{
    s16 var_r31;
    for (var_r31 = 0; var_r31 < arg2; var_r31++, arg0++, arg1++) {
        arg1->x = arg0->x * arg8;
        arg1->y = arg0->y * arg8;
        arg1->z = arg0->z * arg8;
    }
}

void fn_1_5620(Vec2f *arg0, Vec2f *arg1, s16 arg2, float arg8, float arg9)
{
    arg0[0].x = arg1[arg2].x;
    arg0[0].y = arg1[arg2].y;
    arg0[1].x = arg8 + arg1[arg2].x;
    arg0[1].y = arg1[arg2].y;
    arg0[2].x = arg8 + arg1[arg2].x;
    arg0[2].y = arg9 + arg1[arg2].y;
    arg0[3].x = arg1[arg2].x;
    arg0[3].y = arg9 + arg1[arg2].y;
}

void fn_1_56C4(ModelData *arg0, Mtx arg1)
{
    Mtx sp130;
    ROMtx sp100;
    Mtx spD0;
    Mtx spA0;
    Vec sp70[4];
    Vec sp64;
    Vec sp58;
    Vec sp4C;
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    UnkM450ModelFunc spC;
    s16 sp8;

    UnkM450Struct *var_r31;
    Vec *var_r30;
    UnkM450Struct2 *var_r29;
    Vec2f *var_r27;
    s16 var_r19;

    var_r31 = arg0->unk_120;
    if ((var_r31->unk_6B == 0) || (var_r31->unk_66 != 0)) {
        GXLoadPosMtxImm(arg1, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        sp8 = var_r31->unk_04->bmp->dataFmt & 0xF;
        if ((sp8 == 8) || (sp8 == 7)) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXA, GX_CC_RASC, GX_CC_ZERO);
        }
        else {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
        }
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
        if ((arg0->attr & 2) != 0) {
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        }
        else {
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        }
        HuSprTexLoad(var_r31->unk_04, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(GX_FALSE);
        switch (var_r31->unk_6A) {
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
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSETARRAY(GX_VA_POS, var_r31->unk_14, var_r31->unk_64 * sizeof(Vec) * 4, sizeof(Vec));
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSETARRAY(GX_VA_CLR0, var_r31->unk_20, var_r31->unk_64 * sizeof(GXColor), sizeof(GXColor));
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSETARRAY(GX_VA_TEX0, var_r31->unk_18, var_r31->unk_64 * sizeof(Vec2f) * 4, sizeof(Vec2f));
        sp130[0][0] = arg1[0][0];
        sp130[1][0] = arg1[0][1];
        sp130[2][0] = arg1[0][2];
        sp130[0][1] = arg1[1][0];
        sp130[1][1] = arg1[1][1];
        sp130[2][1] = arg1[1][2];
        sp130[0][2] = arg1[2][0];
        sp130[1][2] = arg1[2][1];
        sp130[2][2] = arg1[2][2];
        sp130[0][3] = 0.0f;
        sp130[1][3] = 0.0f;
        sp130[2][3] = 0.0f;
        MTXReorder(sp130, sp100);
        if ((omPauseChk() == 0) && (var_r31->unk_00)) {
            spC = var_r31->unk_00;
            spC(arg0, var_r31, arg1);
        }
        var_r29 = var_r31->unk_10;
        var_r30 = var_r31->unk_14;
        var_r27 = var_r31->unk_18;
        MTXROMultVecArray(sp100, &var_r31->unk_28, sp70, 4);
        for (var_r19 = 0; var_r19 < var_r31->unk_64; var_r19++, var_r29++, var_r27 += 4) {
            if (var_r29->unk_3E < 0) {
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
            }
            else {
                if (var_r29->unk_28 == 0.0f) {
                    fn_1_55C4(sp70, &sp40, 4, var_r29->unk_2C);
                    VECAdd(&sp40, &var_r29->unk_30, var_r30++);
                    VECAdd(&sp4C, &var_r29->unk_30, var_r30++);
                    VECAdd(&sp58, &var_r29->unk_30, var_r30++);
                    VECAdd(&sp64, &var_r29->unk_30, var_r30++);
                }
                else {
                    fn_1_55C4(&var_r31->unk_28, &sp40, 4, var_r29->unk_2C);
                    MTXRotRad(spD0, 0x5A, 0.017453292f * var_r29->unk_28);
                    MTXConcat(sp130, spD0, spA0);
                    MTXMultVecArray(spA0, &sp40, &sp10, 4);
                    VECAdd(&sp10, &var_r29->unk_30, var_r30++);
                    VECAdd(&sp1C, &var_r29->unk_30, var_r30++);
                    VECAdd(&sp28, &var_r29->unk_30, var_r30++);
                    VECAdd(&sp34, &var_r29->unk_30, var_r30++);
                }
                if (var_r29->unk_3C != -1) {
                    fn_1_5620(var_r27, var_r31->unk_1C, var_r29->unk_3C, var_r31->unk_5C, var_r31->unk_60);
                }
            }
        }
        DCFlushRangeNoSync(var_r31->unk_14, var_r31->unk_64 * sizeof(Vec) * 4);
        DCFlushRangeNoSync(var_r31->unk_18, var_r31->unk_64 * sizeof(Vec2f) * 4);
        GXCallDisplayListNative(var_r31->unk_24, var_r31->unk_58);
    }
}

void fn_1_5E0C(Vec2f *arg0, s16 arg1, s16 arg2, float arg8, float arg9)
{
    s16 var_r31;
    s16 var_r30;
    s16 var_r29;

    (void)arg9;
    (void)arg9;
    (void)arg9;
    (void)arg8;
    (void)arg8;
    (void)arg8;

    for (var_r31 = 0; var_r31 < arg1; var_r31++, arg0++) {
        var_r30 = var_r31 % arg2;
        var_r29 = var_r31 / arg2;
        arg0->x = var_r30 * arg8;
        arg0->y = var_r29 * arg9;
    }
}

s16 fn_1_5ED8(AnimData *arg0, Vec *arg1, float *arg2, s16 arg3, float arg8, s16 arg4, s16 arg5)
{
    void *sp1C;

    UnkM450Struct *var_r31;
    s16 var_r30;
    Vec2f *var_r29;
    ModelData *var_r28;
    GXColor *var_r26;
    Vec *var_r25;
    UnkM450Struct2 *var_r24;
    s16 var_r21;
    void *var_r19;
    s16 var_r18;
    s16 var_r17;

    var_r18 = Hu3DHookFuncCreate(fn_1_56C4);
    var_r28 = &Hu3DData[var_r18];
    var_r28->unk_120 = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkM450Struct), var_r28->unk_48);
    var_r31 = var_r28->unk_120;
    arg0->useNum++;
    var_r31->unk_04 = arg0;
    var_r31->unk_08 = arg1;
    var_r31->unk_0C = arg2;
    var_r31->unk_64 = arg3;
    var_r31->unk_6A = 0;
    var_r31->unk_00 = 0;
    var_r31->unk_66 = arg3;
    var_r31->unk_6B = 0;
    var_r31->unk_10 = HuMemDirectMallocNum(HEAP_DATA, arg3 * sizeof(UnkM450Struct2), var_r28->unk_48);
    for (var_r24 = var_r31->unk_10, var_r30 = 0; var_r30 < arg3; var_r30++, var_r24++) {
        var_r24->unk_3E = -1;
        var_r24->unk_3C = -1;
    }
    var_r31->unk_14 = HuMemDirectMallocNum(HEAP_DATA, arg3 * sizeof(Vec) * 4, var_r28->unk_48);
    for (var_r25 = var_r31->unk_14, var_r30 = 0; var_r30 < (arg3 * 4); var_r30++, var_r25++) {
        var_r25->x = 0.0f;
        var_r25->y = 0.0f;
        var_r25->z = 0.0f;
    }
    var_r31->unk_20 = HuMemDirectMallocNum(HEAP_DATA, arg3 * sizeof(GXColor), var_r28->unk_48);
    for (var_r26 = var_r31->unk_20, var_r30 = 0; var_r30 < arg3; var_r30++, var_r26++) {
        var_r26->r = 0xFF;
        var_r26->g = 0xFF;
        var_r26->b = 0xFF;
        var_r26->a = 0xFF;
    }
    var_r31->unk_18 = HuMemDirectMallocNum(HEAP_DATA, arg3 * sizeof(Vec2f) * 4, var_r28->unk_48);
    var_r29 = var_r31->unk_18;
    for (var_r30 = 0; var_r30 < arg3; var_r30++) {
        var_r29->x = 0.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 1.0f;
        var_r29++;
        var_r29->x = 0.0f;
        var_r29->y = 1.0f;
        var_r29++;
    }
    if ((arg4 != 0) || (arg5 != 0)) {
        var_r21 = arg0->bmp->sizeX / arg4;
        var_r17 = arg0->bmp->sizeY / arg5;
        var_r31->unk_68 = var_r21 * var_r17;
        var_r31->unk_5C = 1.0f / var_r21;
        var_r31->unk_60 = 1.0f / var_r17;
    }
    else {
        var_r21 = 1;
        var_r31->unk_68 = 1;
        var_r31->unk_5C = 1.0f;
        var_r31->unk_60 = 1.0f;
    }
    var_r31->unk_1C = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_68 * sizeof(Vec2f), var_r28->unk_48);
    fn_1_5E0C(var_r31->unk_1C, var_r31->unk_68, var_r21, var_r31->unk_5C, var_r31->unk_60);
    var_r31->unk_28.x = var_r31->unk_4C = var_r31->unk_44 = var_r31->unk_50 = -arg8;
    var_r31->unk_38 = arg8;
    var_r31->unk_28.y = arg8;
    var_r31->unk_40 = arg8;
    var_r31->unk_34 = arg8;
    var_r31->unk_28.z = var_r31->unk_3C = var_r31->unk_48 = var_r31->unk_54 = 0.0f;
    var_r19 = HuMemDirectMallocNum(HEAP_DATA, 0x20000, var_r28->unk_48);
    sp1C = var_r19;
    GXBeginDisplayList(sp1C, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, arg3 * 4);
    for (var_r30 = 0; var_r30 < arg3; var_r30++) {
        // TODO is this right?
        GXPosition1x16(var_r30 * 4);
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30 * 4);

        GXPosition1x16(var_r30 * 4 + 1);
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30 * 4 + 1);

        GXPosition1x16(var_r30 * 4 + 2);
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30 * 4 + 2);

        GXPosition1x16(var_r30 * 4 + 3);
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30 * 4 + 3);
    }
    var_r31->unk_58 = GXEndDisplayList();
    DCFlushRangeNoSync(var_r19, var_r31->unk_58);
    var_r31->unk_24 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_58, var_r28->unk_48);
    memcpy(var_r31->unk_24, var_r19, var_r31->unk_58);
    DCFlushRangeNoSync(var_r31->unk_24, var_r31->unk_58);
    HuMemDirectFree(var_r19);
    return var_r18;
}

UnkM450Struct2 *fn_1_6530(s16 arg0, Vec *arg1, GXColor *arg2, float arg8, float arg9)
{
    UnkM450Struct2 *var_r31;
    UnkM450Struct *var_r30;
    s16 var_r29;
    ModelData *var_r28;

    var_r28 = &Hu3DData[arg0];
    var_r30 = var_r28->unk_120;
    if (var_r30->unk_6B != 0) {
        return NULL;
    }

    for (var_r29 = 0, var_r31 = var_r30->unk_10; var_r29 < var_r30->unk_64; var_r29++, var_r31++) {
        if (var_r31->unk_3E < 0) {
            break;
        }
    }
    if (var_r29 == var_r30->unk_64) {
        return NULL;
    }
    var_r30->unk_20[var_r29] = *arg2;
    var_r31->unk_30 = *arg1;
    var_r31->unk_2C = arg8;
    var_r31->unk_28 = arg9;
    var_r31->unk_3C = 0;
    var_r31->unk_00 = 0;
    var_r31->unk_3E = var_r29;
    return var_r31;
}

void fn_1_6638(s16 arg0, UnkM450ModelFunc arg1)
{
    ModelData *var_r31 = &Hu3DData[arg0];
    UnkM450Struct *var_r30 = var_r31->unk_120;
    var_r30->unk_00 = arg1;
}

void fn_1_6670(s16 arg0, u8 arg1)
{
    ModelData *var_r31 = &Hu3DData[arg0];
    ((UnkM450Struct *)var_r31->unk_120)->unk_6A = arg1;
}

void fn_1_66A0(s16 arg0)
{
    ModelData *var_r31 = &Hu3DData[arg0];
    UnkM450Struct *var_r30 = var_r31->unk_120;
    var_r30->unk_6B = 1;
}

s32 fn_1_66DC(s16 arg0)
{
    ModelData *var_r30 = &Hu3DData[arg0];
    UnkM450Struct *var_r31 = var_r30->unk_120;

    if ((var_r31->unk_6B != 0) && (var_r31->unk_66 == 0)) {
        HuMemDirectFree(var_r31->unk_10);
        HuMemDirectFree(var_r31->unk_14);
        HuMemDirectFree(var_r31->unk_20);
        HuMemDirectFree(var_r31->unk_18);
        HuMemDirectFree(var_r31->unk_1C);
        HuMemDirectFree(var_r31->unk_24);
        HuSprAnimKill(var_r31->unk_04);
        HuMemDirectFree(var_r30->unk_120);
        Hu3DModelKill(arg0);
        return 1;
    }
    return 0;
}

void fn_1_6798(s16 arg0, s16 arg1, Vec *arg2, float arg8, float arg9, float argA)
{
    UnkM450Struct2 *var_r31;
    s16 var_r27;

    GXColor sp18 = { 0xFF, 0xFF, 0xFF, 0xFF };
    for (var_r27 = 0; var_r27 < arg1; var_r27++) {
        var_r31 = fn_1_6530(arg0, arg2, &sp18, 0.0f, 0.0f);
        if (!var_r31) {
            break;
        }
        var_r31->unk_04 = *arg2;
        var_r31->unk_10 = 0.0f;
        var_r31->unk_14 = arg8;
        var_r31->unk_1C = 5.0f;
        var_r31->unk_20 = arg9;
        var_r31->unk_24 = argA;
        var_r31->unk_18 = (20.0f * frandf()) - 10.0f;
        var_r31->unk_1C = var_r31->unk_1C * (0.8f + (0.4f * frandf()));
        var_r31->unk_20 = var_r31->unk_20 * (0.9f + (0.3f * frandf()));
    }
}

s16 fn_1_69F8(Vec *arg0, float *arg1, s16 arg2)
{
    s16 var_r31 = fn_1_5ED8(lbl_1_bss_14, arg0, arg1, arg2, 80.0f, 0x40, 0x40);
    fn_1_6638(var_r31, fn_1_5148);
    fn_1_6670(var_r31, 1);
    Hu3DModelLayerSet(var_r31, 5);
    return var_r31;
}

float fn_1_6AC8(float arg8, float arg9, float argA, float argB)
{
    if (argA >= argB) {
        return arg9;
    }
    return arg8 + ((arg9 - arg8) * sind(((90.0f / argB) * argA)));
}

float fn_1_6B90(float arg8, float arg9, float argA, float argB)
{
    if (argA >= argB) {
        return arg9;
    }
    return arg8 + ((arg9 - arg8) * (1.0 - cosd(((90.0f / argB) * argA))));
}

void fn_1_6C68(s32 arg0)
{
    lbl_1_bss_10 = 0;
    lbl_1_bss_C = arg0;
    HuWinInit(1);
}

void fn_1_6CB0(void (*arg0)(), s32 arg1)
{
    if ((arg1 < 0) || (fn_1_13B90(arg1) == 0)) {
        lbl_1_bss_10++;
        HuPrcChildCreate(arg0, 0x64, 0x2000, 0, HuPrcCurrentGet());
    }
}

void fn_1_6D2C(void)
{
    lbl_1_bss_10--;
    HuPrcEnd();
}

void fn_1_6D68(float *arg0, s32 arg1)
{
    float spC[2];

    HuWinMesMaxSizeGet(1, spC, arg1);
    if (spC[0] > arg0[0]) {
        arg0[0] = spC[0];
    }
    if (spC[1] > arg0[1]) {
        arg0[1] = spC[1];
    }
}

GXColor lbl_1_data_9F[3] = {
    { 0xFF, 0xFF, 0xCC, 0xE6 },
    { 0xCC, 0xFF, 0xFF, 0xE6 },
    { 0xFF, 0xCC, 0xFF, 0xE6 },
};

s32 lbl_1_data_AC[2] = { DATA_MAKE_NUM(DATADIR_M450, 0x2C), DATA_MAKE_NUM(DATADIR_M450, 0x2D) };

s32 lbl_1_data_B4[0x13] = {
    DATA_MAKE_NUM(DATADIR_M450, 0x2E),
    DATA_MAKE_NUM(DATADIR_M450, 0x2F),
    DATA_MAKE_NUM(DATADIR_M450, 0x30),
    DATA_MAKE_NUM(DATADIR_M450, 0x31),
    DATA_MAKE_NUM(DATADIR_M450, 0x32),
    DATA_MAKE_NUM(DATADIR_M450, 0x33),
    DATA_MAKE_NUM(DATADIR_M450, 0x34),
    DATA_MAKE_NUM(DATADIR_M450, 0x35),
    DATA_MAKE_NUM(DATADIR_M450, 0x36),
    DATA_MAKE_NUM(DATADIR_M450, 0x37),
    DATA_MAKE_NUM(DATADIR_M450, 0x38),
    DATA_MAKE_NUM(DATADIR_M450, 0x39),
    DATA_MAKE_NUM(DATADIR_M450, 0x3A),
    DATA_MAKE_NUM(DATADIR_M450, 0x3B),
    DATA_MAKE_NUM(DATADIR_M450, 0x3C),
    DATA_MAKE_NUM(DATADIR_M450, 0x3D),
    DATA_MAKE_NUM(DATADIR_M450, 0x3E),
    DATA_MAKE_NUM(DATADIR_M450, 0x3F),
    DATA_MAKE_NUM(DATADIR_M450, 0x40),
};

s32 lbl_1_data_100[5] = {
    DATA_MAKE_NUM(DATADIR_M450, 0x41),
    DATA_MAKE_NUM(DATADIR_M450, 0x42),
    DATA_MAKE_NUM(DATADIR_M450, 0x43),
    DATA_MAKE_NUM(DATADIR_M450, 0x44),
    DATA_MAKE_NUM(DATADIR_M450, 0x45),
};
s32 lbl_1_data_114[0xF] = {
    DATA_MAKE_NUM(DATADIR_M450, 0x46),
    DATA_MAKE_NUM(DATADIR_M450, 0x47),
    DATA_MAKE_NUM(DATADIR_M450, 0x47),
    DATA_MAKE_NUM(DATADIR_M450, 0x49),
    DATA_MAKE_NUM(DATADIR_M450, 0x4A),
    DATA_MAKE_NUM(DATADIR_M450, 0x4B),
    DATA_MAKE_NUM(DATADIR_M450, 0x4C),
    DATA_MAKE_NUM(DATADIR_M450, 0x4D),
    DATA_MAKE_NUM(DATADIR_M450, 0x4E),
    DATA_MAKE_NUM(DATADIR_M450, 0x4F),
    DATA_MAKE_NUM(DATADIR_M450, 0x50),
    DATA_MAKE_NUM(DATADIR_M450, 0x51),
    DATA_MAKE_NUM(DATADIR_M450, 0x52),
    DATA_MAKE_NUM(DATADIR_M450, 0x53),
    DATA_MAKE_NUM(DATADIR_M450, 0x54),
};
s32 lbl_1_data_150[0xF] = {
    DATA_MAKE_NUM(DATADIR_M450, 0x55),
    DATA_MAKE_NUM(DATADIR_M450, 0x56),
    DATA_MAKE_NUM(DATADIR_M450, 0x56),
    DATA_MAKE_NUM(DATADIR_M450, 0x58),
    DATA_MAKE_NUM(DATADIR_M450, 0x59),
    DATA_MAKE_NUM(DATADIR_M450, 0x5A),
    DATA_MAKE_NUM(DATADIR_M450, 0x5B),
    DATA_MAKE_NUM(DATADIR_M450, 0x55),
    DATA_MAKE_NUM(DATADIR_M450, 0x5C),
    DATA_MAKE_NUM(DATADIR_M450, 0x5D),
    DATA_MAKE_NUM(DATADIR_M450, 0x5E),
    DATA_MAKE_NUM(DATADIR_M450, 0x5F),
    DATA_MAKE_NUM(DATADIR_M450, 0x60),
    DATA_MAKE_NUM(DATADIR_M450, 0x61),
    DATA_MAKE_NUM(DATADIR_M450, 0x62),
};
s32 lbl_1_data_18C[8] = { 0, 1, 2, 1, 1, -1, -1, -1 };
s32 lbl_1_data_1AC[8] = { 0, 1, 2, 1, 1, -1, -1, -1 };
s32 lbl_1_data_1CC[4] = { 0x3E, 0x65, 0x3F, 0x66 };
UnkData204Struct lbl_1_data_1DC[5] = {
    { 8.5f * REFRESH_RATE, 0 },
    { 5.0f * REFRESH_RATE, 1 },
    { 5.0f * REFRESH_RATE, 0 },
    { 5.0f * REFRESH_RATE, 1 },
    { 0.0f, 0 },
};
UnkData204Struct lbl_1_data_204[6] = {
    { 3.5f * REFRESH_RATE, 0 },
    { 5.0f * REFRESH_RATE, 1 },
    { 5.0f * REFRESH_RATE, 0 },
    { 5.0f * REFRESH_RATE, 1 },
    { 5.0f * REFRESH_RATE, 0 },
    { 0.0f, 0 },
};
Vec2f lbl_1_data_234[4] = {
    { 5.0f * REFRESH_RATE, 5.0f * REFRESH_RATE },
    { 5.0f * REFRESH_RATE, 4.0f * REFRESH_RATE },
    { 5.0f * REFRESH_RATE, 3.5f * REFRESH_RATE },
    { 5.0f * REFRESH_RATE, 3.0f * REFRESH_RATE },
};
float lbl_1_data_254[5] = { 0.4f, 0.35f, 0.3f, 0.25f, 0.2f };
float lbl_1_data_268[5] = { 0.45f, 0.4f, 0.35f, 0.3f, 0.25f };
float lbl_1_data_27C[5] = { 0.5f, 0.45f, 0.4f, 0.35f, 0.3f };
float lbl_1_data_290[5] = { 0.55f, 0.5f, 0.45f, 0.4f, 0.35f };

s32 fn_1_6DD8(float arg8, float arg9, float argA, float argB, s32 arg0)
{
    float spC[2];

    float var_f30;
    float var_f29;
    float var_f25;
    float var_f24;
    float var_f19;
    float var_f18;

    s32 var_r31;
    WindowData *var_r30;
    GXColor *var_r29;
    s32 var_r28;

    if (555.0f < (arg8 + argA)) {
        arg8 = 555.0f - argA;
    }
    if (21.0f > arg8) {
        arg8 = 21.0f;
    }
    lbl_1_bss_10++;
    var_r28 = HuWinCreate(arg8, arg9, argA, argB, 1);
    var_r30 = &winData[var_r28];
    var_r29 = &lbl_1_data_9F[arg0];
    HuWinBGTPLvlSet(var_r28, var_r29->a / 255.0f);
    HuSprColorSet(var_r30->group, 0, var_r29->r, var_r29->g, var_r29->b);
    var_r30->mess_color = 0;
    var_r30->mess_shadow_color = 9;
    var_r30->attr |= 0x80;
    var_r30->active_pad = 0;
    var_f30 = arg8 + (0.5f * argA);
    var_f25 = 4.0f / argA;
    if (((4.0f + var_f30) - (arg8 + argA)) >= 0.0f) {
        var_f30 = (arg8 + argA) - 4.0f;
    }
    else if ((arg8 - (var_f30 - 2.0f)) >= 0.0f) {
        var_f30 = arg8;
    }
    else {
        var_f30 -= 2.0f;
    }
    var_f29 = arg9 + (0.5f * argB);
    var_f24 = 4.0f / argB;
    if (((4.0f + var_f29) - (arg9 + argB)) >= 0.0f) {
        var_f29 = (arg9 + argB) - 4.0f;
    }
    else if ((arg9 - (var_f29 - 2.0f)) >= 0.0f) {
        var_f29 = arg9;
    }
    else {
        var_f29 -= 2.0f;
    }
    for (var_r31 = 0; var_r31 < 0xA; var_r31++) {
        var_f19 = fn_1_6AC8(var_f30, arg8, var_r31, 10.0f);
        spC[1] = fn_1_6AC8(var_f25, 1.0f, var_r31, 10.0f);
        var_f18 = fn_1_6AC8(var_f29, arg9, var_r31, 10.0f);
        spC[0] = fn_1_6AC8(var_f24, 1.0f, var_r31, 10.0f);
        HuWinPosSet(var_r28, var_f19, var_f18);
        HuWinScaleSet(var_r28, spC[1], spC[0]);
        HuPrcVSleep();
    }
    HuWinPosSet(var_r28, arg8, arg9);
    HuWinScaleSet(var_r28, 1.0f, 1.0f);
    HuPrcVSleep();
    return var_r28;
}

void fn_1_74EC(s32 arg0)
{
    float sp8[2];
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f25;
    float var_f26;
    float var_f24;
    float var_f19;
    float var_f18;

    s32 var_r31;
    WindowData *var_r30;

    HuWinMesSet(arg0, 0x1D0016);
    HuPrcVSleep();
    var_r30 = &winData[arg0];
    var_f29 = var_r30->pos_x;
    var_f28 = var_r30->pos_y;
    var_f27 = var_r30->w;
    var_f26 = var_r30->h;
    var_f31 = var_f29 + (0.5f * var_f27);
    var_f25 = 4.0f / var_f27;
    if (((4.0f + var_f31) - (var_f29 + var_f27)) >= 0.0f) {
        var_f31 = (var_f29 + var_f27) - 4.0f;
    }
    else if ((var_f29 - (var_f31 - 2.0f)) >= 0.0f) {
        var_f31 = var_f29;
    }
    else {
        var_f31 -= 2.0f;
    }
    var_f30 = var_f28 + (0.5f * var_f26);
    var_f24 = 4.0f / var_f26;
    if (((4.0f + var_f30) - (var_f28 + var_f26)) >= 0.0f) {
        var_f30 = (var_f28 + var_f26) - 4.0f;
    }
    else if ((var_f28 - (var_f30 - 2.0f)) >= 0.0f) {
        var_f30 = var_f28;
    }
    else {
        var_f30 -= 2.0f;
    }
    for (var_r31 = 0; var_r31 < 0xA; var_r31++) {
        var_f19 = fn_1_6B90(var_f29, var_f31, var_r31, 10.0f);
        sp8[1] = fn_1_6B90(1.0f, var_f25, var_r31, 10.0f);
        var_f18 = fn_1_6B90(var_f28, var_f30, var_r31, 10.0f);
        sp8[0] = fn_1_6B90(1.0f, var_f24, var_r31, 10.0f);
        HuWinPosSet(arg0, var_f19, var_f18);
        HuWinScaleSet(arg0, sp8[1], sp8[0]);
        HuPrcVSleep();
    }
    HuWinPosSet(arg0, var_f31, var_f30);
    HuWinScaleSet(arg0, var_f25, var_f24);
    HuPrcVSleep();
    HuWinKill(arg0);
    lbl_1_bss_10--;
}

void fn_1_7B90(s32 arg0, u32 arg1)
{
    winData[arg0].mess_color = 0;
    winData[arg0].mess_shadow_color = 9;
    winData[arg0].attr |= 0x80;
    HuWinMesSet(arg0, arg1);
}

void fn_1_7C14(s32 arg0, s32 arg1)
{
    HuWinComKeyReset();
    if (arg1 > 0) {
        HuPrcSleep(arg1);
    }
    else {
        winData[arg0].active_pad = 1 << lbl_1_bss_C;
        HuWinMesWait(arg0);
    }
    HuWinComKeyReset();
}

void fn_1_7C98(s32 arg0)
{
    s32 var_r31;

    HuWinComKeyReset();
    winData[arg0].active_pad = 1 << lbl_1_bss_C;
    var_r31 = HuWinChoiceGet(arg0, 1);
    if ((var_r31 == -1) || (var_r31 == 1)) {
        lbl_1_bss_8 = 0;
    }
    else {
        lbl_1_bss_8 = 1;
    }
    HuWinComKeyReset();
}

void fn_1_7D40(void)
{
    Vec sp18;
    float var_f31;
    float var_f30;
    float var_f29;

    s32 var_r31;

    float sp10[2] = { 0.0f, 0.0f };
    s32 sp24[22] = {
        0x002D0003,
        0x0000003E,
        0x002D0009,
        0x0000003E,
        0x002D000B,
        0x0000003E,
        0x002D000D,
        0x0000003E,
        0x002D000F,
        0x0000003E,
        0x002D0011,
        0x0000003E,
        0x002D0013,
        0x0000003E,
        0x002D0015,
        0x0000003E,
        0x002D0017,
        0x0000003E,
        0x002D0019,
        0x0000003E,
        0x002D001B,
        0x0000003F,
    };
    fn_1_E178(0, 1);
    fn_1_6D68(sp10, sp24[lbl_1_bss_4 * 2]);
    sp18 = lbl_1_bss_34[0];
    sp18.y += 200.0f;
    Hu3D3Dto2D(&sp18, 1, &sp18);
    if (sp24[(lbl_1_bss_4 * 2) + 1] >= 0) {
        var_f30 = 32.0f + (64.0f * (sp18.x / 576.0f));
        if (32.0f > var_f30) {
            var_f30 = 32.0f;
        }
        if (96.0f < var_f30) {
            var_f30 = 96.0f;
        }
        HuAudFXPanning(fn_1_E0E8(0, sp24[(lbl_1_bss_4 * 2) + 1]), (s32)var_f30);
    }
    var_f31 = sp18.x - (sp10[0] / 2);
    var_f29 = 72.0f;
    if (lbl_1_bss_4 >= 5) {
        if (var_f29 > var_f31) {
            var_f31 = var_f29;
        }
        if ((576.0f - var_f29) < (var_f31 + sp10[0])) {
            var_f31 = (576.0f - var_f29) - sp10[0];
        }
    }
    var_r31 = fn_1_6DD8(var_f31, sp18.y - sp10[1], sp10[0], sp10[1], 0);
    fn_1_7B90(var_r31, sp24[lbl_1_bss_4 * 2]);
    fn_1_7C14(var_r31, lbl_1_bss_0);
    fn_1_74EC(var_r31);
    fn_1_E178(0, 0);
    fn_1_6D2C();
}

void fn_1_8120(void)
{
    Vec sp18;

    float var_f31;
    float var_f30;
    float var_f29;

    s32 var_r31;

    float sp10[2] = { 0.0f, 0.0f };
    s32 sp24[22] = {
        0x002D0002,
        0x0000003E,
        0x002D0008,
        0x0000003E,
        0x002D000A,
        0x0000003E,
        0x002D000C,
        0x0000003E,
        0x002D000E,
        0x0000003E,
        0x002D0010,
        0x0000003E,
        0x002D0012,
        0x0000003E,
        0x002D0014,
        0x0000003E,
        0x002D0016,
        0x0000003E,
        0x002D0018,
        0x0000003F,
        0x002D001A,
        0x0000003F,
    };
    fn_1_E178(1, 1);
    fn_1_6D68(sp10, sp24[lbl_1_bss_4 * 2]);
    sp18 = lbl_1_bss_34[1];
    sp18.y += 200.0f;
    Hu3D3Dto2D(&sp18, 1, &sp18);
    if (sp24[(lbl_1_bss_4 * 2) + 1] >= 0) {
        var_f30 = 32.0f + (64.0f * (sp18.x / 576.0f));
        if (32.0f > var_f30) {
            var_f30 = 32.0f;
        }
        if (96.0f < var_f30) {
            var_f30 = 96.0f;
        }
        HuAudFXPanning(fn_1_E0E8(1, sp24[(lbl_1_bss_4 * 2) + 1]), (s32)var_f30);
    }
    var_f31 = sp18.x - (sp10[0] / 2);
    var_f29 = 72.0f;
    if (lbl_1_bss_4 >= 5) {
        if (var_f29 > var_f31) {
            var_f31 = var_f29;
        }
        if ((576.0f - var_f29) < (var_f31 + sp10[0])) {
            var_f31 = (576.0f - var_f29) - sp10[0];
        }
    }
    var_r31 = fn_1_6DD8(var_f31, sp18.y - sp10[1], sp10[0], sp10[1], 1);
    fn_1_7B90(var_r31, sp24[lbl_1_bss_4 * 2]);
    fn_1_7C14(var_r31, lbl_1_bss_0);
    fn_1_74EC(var_r31);
    fn_1_E178(1, 0);
    fn_1_6D2C();
}

void fn_1_8500(void)
{
    s32 var_r31;

    float sp30[2] = { 0.0f, 0.0f };
    fn_1_6D68(sp30, 0x2D0001);
    fn_1_6D68(sp30, 0x2D0004);
    fn_1_6D68(sp30, 0x2D0005);
    fn_1_6D68(sp30, 0x2D0006);
    fn_1_6D68(sp30, 0x2D0007);
    var_r31 = fn_1_6DD8((576.0f - sp30[0]) / 2, 48.0f, sp30[0], sp30[1], 2);
    HuAudFXPlay(0x3A);
    fn_1_A968(3, 8.0f, 0, 0, 0.0f);
    fn_1_7B90(var_r31, 0x2D0001);
    fn_1_7C14(var_r31, -1);
    lbl_1_bss_4 = 0;
    lbl_1_bss_0 = 0x78;
    fn_1_E1A8(0, 8, 8.0f, 0, 7, 0.0f);
    fn_1_E1A8(1, 8, 8.0f, 0, 7, 0.0f);
    fn_1_6CB0(fn_1_7D40, -1);
    fn_1_6CB0(fn_1_8120, -1);

    while (lbl_1_bss_10 > 2) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x3B);
    fn_1_A968(4, 8.0f, 0, 0, REFRESH_RATE);
    fn_1_E1A8(0, 9, 8.0f, 0, 7, REFRESH_RATE);
    fn_1_E1A8(1, 9, 8.0f, 0, 7, REFRESH_RATE);
    fn_1_7B90(var_r31, 0x2D0004);
    fn_1_7C14(var_r31, -1);
    HuAudFXPlay(0x3C);
    fn_1_7B90(var_r31, 0x2D0005);
    fn_1_7C14(var_r31, -1);
    fn_1_7B90(var_r31, 0x2D0006);
    fn_1_7C14(var_r31, -1);
    HuAudFXPlay(0x3A);
    fn_1_7B90(var_r31, 0x2D0007);
    fn_1_7C14(var_r31, -1);
    fn_1_74EC(var_r31);
    fn_1_6D2C();
}

void fn_1_8BDC(void)
{
    lbl_1_bss_4 = 2;
    lbl_1_bss_0 = -1;
    fn_1_E1A8(1, 0xD, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_6CB0(fn_1_8120, -1);

    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(1, 0, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_E1A8(0, 0xD, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_6CB0(fn_1_7D40, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(0, 0, 8.0f, 0x40000001, -1, 0.0f);
    lbl_1_bss_4 = 3;
    lbl_1_bss_0 = -1;
    fn_1_E1A8(1, 0xD, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_6CB0(fn_1_8120, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(1, 0, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_E1A8(0, 0xD, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_6CB0(fn_1_7D40, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);
    fn_1_1F58(0x3E8);
    lbl_1_bss_4 = 4;
    lbl_1_bss_0 = 0x1E;
    fn_1_E1A8(0, 0xC, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_E1A8(1, 0xC, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_6CB0(fn_1_7D40, -1);
    fn_1_6CB0(fn_1_8120, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_6D2C();
}

void fn_1_9074(void)
{
    lbl_1_bss_4 = 5;
    lbl_1_bss_0 = 0x1E;
    fn_1_6CB0(fn_1_7D40, -1);
    fn_1_6CB0(fn_1_8120, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    lbl_1_bss_4 = 6;
    lbl_1_bss_0 = -1;
    fn_1_E1A8(1, 0xD, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_6CB0(fn_1_8120, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(1, 0, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_E1A8(0, 0xD, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_6CB0(fn_1_7D40, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(0, 0, 8.0f, 0x40000001, -1, 0.0f);
    lbl_1_bss_4 = 7;
    lbl_1_bss_0 = -1;
    fn_1_E1A8(1, 0xD, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_6CB0(fn_1_8120, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(1, 0, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_E1A8(0, 0xD, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_6CB0(fn_1_7D40, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(0, 0, 8.0f, 0x40000001, -1, 0.0f);
    lbl_1_bss_4 = 8;
    lbl_1_bss_0 = -1;
    fn_1_E1A8(1, 0xE, 8.0f, 0, -1, 0.0f);
    fn_1_6CB0(fn_1_8120, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(1, 0, 8.0f, 0x40000001, -1, 0.0f);
    fn_1_E1A8(0, 0xE, 8.0f, 0, -1, 0.0f);
    fn_1_6CB0(fn_1_7D40, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(0, 0, 8.0f, 0x40000001, -1, 0.0f);
    lbl_1_bss_4 = 9;
    lbl_1_bss_0 = 0x1E;
    fn_1_6CB0(fn_1_7D40, -1);
    fn_1_6CB0(fn_1_8120, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_6D2C();
}

void fn_1_96C0(void)
{
    lbl_1_bss_4 = 0xA;
    lbl_1_bss_0 = -1;
    fn_1_E1A8(1, 4, 8.0f, 0, -1, 0.0f);
    fn_1_6CB0(fn_1_8120, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_E1A8(0, 4, 8.0f, 0, -1, 0.0f);
    fn_1_6CB0(fn_1_7D40, -1);
    while (lbl_1_bss_10 > 1) {
        HuPrcVSleep();
    }
    fn_1_6D2C();
}

void fn_1_9824(void)
{
    s32 var_r31;

    float sp20[2] = { 0.0f, 0.0f };
    fn_1_6D68(sp20, 0x2D001C);
    fn_1_6D68(sp20, 0x2D001D);
    fn_1_6D68(sp20, 0x2D001E);
    var_r31 = fn_1_6DD8((576.0f - sp20[0]) / 2, 132.0f, sp20[0], sp20[1], 2);
    fn_1_A968(8, 8.0f, 0, 7, 0.0f);
    HuAudFXPlay(0x3C);
    fn_1_7B90(var_r31, 0x2D001C);
    fn_1_7C14(var_r31, -1);
    fn_1_7B90(var_r31, 0x2D001D);
    fn_1_7C14(var_r31, -1);
    HuAudFXPlay(0x3C);
    fn_1_7B90(var_r31, 0x2D001E);
    fn_1_7C14(var_r31, -1);
    fn_1_74EC(var_r31);
    fn_1_6D2C();
}

void fn_1_9BA4(void)
{
    s32 var_r31;
    float sp20[2] = { 0.0f, 0.0f };

    fn_1_6D68(sp20, 0x2D001F);
    fn_1_6D68(sp20, 0x2D0020);
    fn_1_6D68(sp20, 0x2D0021);
    var_r31 = fn_1_6DD8((576.0f - sp20[0]) / 2, 48.0f, sp20[0], sp20[1], 2);
    HuAudFXPlay(0x3C);
    fn_1_7B90(var_r31, 0x2D001F);
    fn_1_7C14(var_r31, -1);
    fn_1_A968(5, 8.0f, 0, 6, 0.0f);
    fn_1_7B90(var_r31, 0x2D0020);
    fn_1_7C14(var_r31, -1);
    HuAudFXPlay(0x3C);
    fn_1_7B90(var_r31, 0x2D0021);
    fn_1_7C14(var_r31, -1);
    fn_1_A968(0, 8.0f, 0, -1, 0.0f);
    fn_1_74EC(var_r31);
    fn_1_6D2C();
}

void fn_1_9F4C(UnkM450Struct3 *arg0, s32 arg1, Vec *arg2, s8 arg3)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;

    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    if (90.0f <= arg0->unk_E4) {
        arg0->unk_00.unk_6C.y -= 10.0f;
        return;
    }
    var_r29 = 1;
    if (arg3 == 0x78) {
        if (arg2->x > arg0->unk_00.unk_6C.x) {
            var_r29 = 0;
        }
    }
    else if (arg2->z < arg0->unk_00.unk_6C.z) {
        var_r29 = 0;
    }
    if (var_r29 != 0) {
        arg0->unk_E4 += 5.0f;
        if (0.0f > arg2->x) {
            var_f30 = -arg2->x;
        }
        else {
            var_f30 = arg2->x;
        }
        var_f31 = var_f30;
        if (0.0f > arg2->y) {
            var_f29 = -arg2->y;
        }
        else {
            var_f29 = arg2->y;
        }
        if (var_f31 < var_f29) {
            if (0.0f > arg2->y) {
                var_f28 = -arg2->y;
            }
            else {
                var_f28 = arg2->y;
            }
            var_f31 = var_f28;
        }
        if (0.0f > arg2->z) {
            var_f27 = -arg2->z;
        }
        else {
            var_f27 = arg2->z;
        }
        if (var_f31 < var_f27) {
            if (0.0f > arg2->z) {
                var_f26 = -arg2->z;
            }
            else {
                var_f26 = arg2->z;
            }
            var_f31 = var_f26;
        }
        var_f31 = 1500.0f - var_f31;
        if (arg3 == 0x78) {
            if (0.0f > arg2->x) {
                var_r28 = -1;
            }
            else {
                var_r28 = 1;
            }
            arg0->unk_00.unk_6C.x = arg2->x + ((var_f31 * var_r28) * sind(arg0->unk_E4));
        }
        else {
            if (0.0f > arg2->z) {
                var_r27 = -1;
            }
            else {
                var_r27 = 1;
            }
            arg0->unk_00.unk_6C.z = arg2->z + ((var_f31 * var_r27) * sind(arg0->unk_E4));
        }
        MTXRotRad(Hu3DData[arg1].unk_F0, 0x58, 0.017453292f * arg0->unk_E4);
        arg0->unk_00.unk_6C.y = arg2->y + (var_f31 * cosd(arg0->unk_E4));
        return;
    }
    if (arg3 == 0x78) {
        arg0->unk_00.unk_20 = 0x48;
    }
    else {
        arg0->unk_00.unk_24 = 0x48;
    }
    if (arg0->unk_154 & 0x200) {
        var_f31 = arg0->unk_F0 - arg0->unk_00.unk_6C.x;
        if (0.0f > var_f31) {
            var_f25 = -var_f31;
        }
        else {
            var_f25 = var_f31;
        }
        if (10.0f > var_f25) {
            arg0->unk_154 &= ~0x200;
        }
        if (0.0f <= var_f31) {
            arg0->unk_00.unk_20 = 0x48;
        }
        else {
            arg0->unk_00.unk_20 = -0x48;
        }
    }
    fn_1_40C0(&arg0->unk_00);
}

void fn_1_A3C4(omObjData *object, Vec *arg1, s32 arg2)
{
    s32 var_r31;

    if (1495.0f > arg1->y) {
        for (var_r31 = 0; var_r31 < arg2; var_r31++) {
            Hu3DModelShadowDispOff(object->model[var_r31]);
        }
        return;
    }
    for (var_r31 = 0; var_r31 < arg2; var_r31++) {
        Hu3DModelShadowDispOn(object->model[var_r31]);
    }
}

void fn_1_A470(UnkM450Struct3 *arg0, omObjData *arg1, char *arg2, s32 arg3)
{
    s32 var_r30;

    arg0->unk_CC = arg2;
    arg0->unk_154 |= 1;
    omSetTra(arg1, 0.0f, 0.0f, 0.0f);
    omSetRot(arg1, 0.0f, 0.0f, 0.0f);
    omSetSca(arg1, 1.0f, 1.0f, 1.0f);
    for (var_r30 = 0; var_r30 < arg3; var_r30++) {
        Hu3DModelPosSet(arg1->model[var_r30], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(arg1->model[var_r30], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(arg1->model[var_r30], 1.0f, 1.0f, 1.0f);
    }
}

void fn_1_A600(UnkM450Struct3 *arg0, omObjData *arg1, char *arg2, s32 arg3)
{
    s32 var_r29;

    arg0->unk_CC = arg2;
    arg0->unk_154 &= ~1;
    fn_1_1D70(lbl_1_bss_1A0->model[0], arg0->unk_CC, &arg0->unk_00.unk_6C, NULL);
    omSetTra(arg1, 0.0f, 0.0f, 0.0f);
    omSetRot(arg1, 0.0f, 0.0f, 0.0f);
    for (var_r29 = 0; var_r29 < arg3; var_r29++) {
        MTXIdentity(Hu3DData[arg1->model[var_r29]].unk_F0);
        Hu3DModelPosSet(arg1->model[var_r29], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(arg1->model[var_r29], 0.0f, 0.0f, 0.0f);
    }
}

s32 fn_1_A7CC(UnkM450Struct3 *arg0)
{
    if (fn_1_19A10(&arg0->unk_00, &arg0->unk_D4) != 0) {
        arg0->unk_150 += 1;
        return 1;
    }
    fn_1_40C0(&arg0->unk_00);
    return 0;
}

void fn_1_A828(UnkM450Struct3 *arg0, float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;

    arg0->unk_E0 += 1.0f;
    var_f31 = arg0->unk_E0 / arg8;
    if (1.0f < var_f31) {
        var_f31 = 1.0f;
    }
    var_f30 = sind((90.0f * var_f31)) * sind((90.0f * var_f31));
    arg0->unk_00.unk_6C.y = arg9 + ((var_f30) * (argA - arg9));
}

void fn_1_A968(s32 arg0, float arg8, u32 arg1, s32 arg2, float arg9)
{
    UnkM450Struct3 *var_r31;

    if (arg8 == 0.0f) {
        Hu3DMotionSet(lbl_1_bss_134->model[0], lbl_1_bss_134->motion[arg0]);
    }
    else {
        Hu3DMotionShiftSet(lbl_1_bss_134->model[0], lbl_1_bss_134->motion[arg0], 0.0f, arg8, arg1);
    }
    var_r31 = lbl_1_bss_134->data;
    var_r31->unk_140 = -1;
    var_r31->unk_154 &= ~0x2100;
    if (arg2 >= 0) {
        var_r31->unk_140 = arg2;
        var_r31->unk_144 = arg9;
        var_r31->unk_154 |= 0x100;
        if (arg0 == 4 || arg0 == 5) {
            var_r31->unk_154 |= 0x2000;
        }
    }
}

s32 lbl_1_data_F6C[6];
UnkDataA0CStruct lbl_1_data_A0C[2];

void fn_1_AAB0(UnkM450Struct3 *arg0, Vec2f *arg1, s32 arg2)
{
    float var_f30;
    float var_f31 = 1.0f;
    if (arg2 != 0) {
        var_f31 = arg0->unk_F4;
        if ((lbl_1_data_F6C[lbl_1_bss_118] - lbl_1_bss_304) > 60 * REFRESH_RATE) {
            arg0->unk_F4 = arg0->unk_F4 - 0.1f;
            if (0.0f > arg0->unk_F4) {
                arg0->unk_F4 = 0.0f;
            }
        }
    }
    var_f30 = arg1->x - arg1->y;
    arg0->unk_100 = arg1->y + (var_f30 * var_f31);
}

float fn_1_AB88(UnkM450Struct3 *arg0)
{
    s32 var_r31 = lbl_1_data_A0C[1].unk_14 - 1;
    if (var_r31 > 4) {
        var_r31 = 4;
    }
    if (var_r31 < 0) {
        var_r31 = 0;
    }
    return arg0->unk_D0[var_r31];
}

void fn_1_ABD0(omObjData *object)
{
    float var_f29;
    UnkM450Struct3 *var_r31 = object->data;

    var_r31->unk_138 = 0;
    var_f29 = sqrtf((var_r31->unk_00.unk_6C.x * var_r31->unk_00.unk_6C.x) + (var_r31->unk_00.unk_6C.z * var_r31->unk_00.unk_6C.z));
    if (680.0f < var_f29) {
        var_r31->unk_138 = 1;
        var_r31->unk_00.unk_6C.x = 680.0f * (var_r31->unk_00.unk_6C.x / var_f29);
        var_r31->unk_00.unk_6C.z = 680.0f * (var_r31->unk_00.unk_6C.z / var_f29);
    }
}

void fn_1_AD58(omObjData *object)
{
    Mtx sp1F8;
    Vec spFC;
    Vec spF0;
    Vec spE4;
    Vec spD8;
    float spCC;
    float spC8;

    UnkM450Struct3 *var_r31;
    s32 var_r20;

    var_r20 = 0;
    spE4 = ((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_00.unk_6C;
    var_r31 = object->data;
    var_r31->unk_00.unk_20 = 0;
    var_r31->unk_00.unk_24 = 0;
    var_r31->unk_00.unk_28 = 0;
    var_r31->unk_00.unk_2C = 0;
    var_r31->unk_00.unk_30 = 0;
    var_r31->unk_00.unk_34 = 0;
    switch (var_r31->unk_150) {
        case 0xBB8:
            if (lbl_1_bss_1A4->work[0] >= 0x3EF) {
                var_r31->unk_150++;
                var_r31->unk_E4 = 0.0f;
                var_r31->unk_154 = var_r31->unk_154 & 0xFFFFFEFF;
            }
            break;
        case 0xBB9:
            fn_1_9F4C(var_r31, object->model[0], lbl_1_bss_4C, 0x7A);
            if (1000.0f > var_r31->unk_00.unk_6C.y) {
                var_r31->unk_150++;
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
            }
            break;
        case 0xBBA:
            if (lbl_1_bss_1A4->work[0] >= 0x402) {
                var_r31->unk_150++;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_00.unk_9C = 270.0f;
                fn_1_A470(var_r31, object, "m450mex06-s4kuppa", 2);
                fn_1_4ED8(&var_r31->unk_00, 0);
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
            }
            break;
        case 0xBBB:
            if (lbl_1_bss_1A4->work[0] >= 0x403) {
                var_r31->unk_E0 += 1.0f;
                if (30.0f < var_r31->unk_E0) {
                    var_r31->unk_150++;
                    var_r31->unk_E4 = 0.0f;
                    fn_1_A600(var_r31, object, "m450mex06-s4kuppa", 2);
                    omSetSca(object, 1.5f, 1.5f, 1.5f);
                    var_r31->unk_00.unk_9C = 270.0f;
                    var_r31->unk_00.unk_6C.y = 1505.0f;
                }
            }
            break;
        case 0xBBC:
            fn_1_9F4C(var_r31, object->model[0], &lbl_1_bss_4C[3], 0x78);
            if (1000.0f > var_r31->unk_00.unk_6C.y) {
                var_r31->unk_150++;
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
                lbl_1_bss_1A4->work[0] = 0x404;
                lbl_1_bss_128 = 0.0f;
            }
            break;
        case 0xBBD:
            if (lbl_1_bss_1A4->work[0] >= 0x409) {
                var_r31->unk_150++;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_E8 = 360.0f * frandf();
                var_r31->unk_154 |= 2;
                MTXIdentity(Hu3DData[object->model[0]].unk_F0);
                omSetSca(object, 1.0f, 1.0f, 1.0f);
                Hu3DModelScaleSet(object->model[1], 1.5f, 1.5f, 1.5f);
                Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(object->model[1], HU3D_MOTATTR_PAUSE);
                Hu3DModelHookSet(object->model[1], "g000i00-itemhook_A", object->model[0]);
                var_r31->unk_00.unk_6C.x = 0.0f;
                var_r31->unk_00.unk_6C.y = 3000.0f;
                var_r31->unk_00.unk_6C.z = 0.0f;
                var_r31->unk_00.unk_9C = 270.0f;
                fn_1_4ED8(&var_r31->unk_00, 0);
                var_r31->unk_00.unk_3C |= 0x2020;
                Hu3DMotionSet(object->model[0], object->motion[7]);
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
            }
            break;
        case 0xBBE:
            fn_1_A828(var_r31, 2 * REFRESH_RATE, 3000.0f, 1605.0f);
            if (lbl_1_bss_1A4->work[0] >= 0x40B) {
                var_r31->unk_150++;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_D4.x = 1200.0f;
                var_r31->unk_D4.y = var_r31->unk_00.unk_6C.y;
                var_r31->unk_D4.z = 0.0f;
            }
            break;
        case 0xBBF:
            fn_1_A828(var_r31, 60.0f, var_r31->unk_D4.y, 1605.0f);
            if ((fn_1_A7CC(var_r31) != 0) && (lbl_1_bss_1A4->work[0] < 0x40C)) {
                lbl_1_bss_1A4->work[0] = 0x40C;
                lbl_1_bss_128 = 0.0f;
            }
            break;
        case 0xBC0:
            var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 270.0f, 0.05f);
            if (lbl_1_bss_1A4->work[0] >= 0x40D) {
                var_r31->unk_150++;
                var_r31->unk_EC = 0.0f;
                var_r31->unk_104 = 0.0f;
                fn_1_AAB0(var_r31, var_r31->unk_C8, 0);
                var_r31->unk_D4 = var_r31->unk_00.unk_6C;
                Hu3DMotionShiftSet(object->model[0], object->motion[9], 0.0f, 8.0f, 0x40000001);
            }
            break;
        case 0xBC1:
            if ((var_r31->unk_154 & 0x80) != 0) {
                var_r31->unk_100 += 1.0f;
                if ((Hu3DMotionShiftIDGet(object->model[0]) < 0) && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
                    var_r31->unk_154 = var_r31->unk_154 & 0xFFFFFF7F;
                    Hu3DMotionShiftSet(object->model[0], object->motion[9], 0.0f, 8.0f, 0x40000001);
                }
            }
            else if ((var_r31->unk_134 > lbl_1_data_A0C[0].unk_14) || (lbl_1_data_A0C[0].unk_14 <= 0)) {
                var_r31->unk_100 += 1.0f;
                var_r31->unk_154 |= 0x80;
                Hu3DMotionShiftSet(object->model[0], object->motion[8], 0.0f, 8.0f, 0);
            }
            VECSubtract(&((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_00.unk_6C, &var_r31->unk_00.unk_6C, &spF0);
            var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, atan2d(spF0.x, spF0.z), 0.4f);
            var_r31->unk_100 -= 1.0f;
            if (0.0f > var_r31->unk_100) {
                var_r31->unk_150 = 0xBC2;
                var_r31->unk_154 |= 0x10;
                fn_1_AAB0(var_r31, var_r31->unk_C8, 0);
                fn_1_17970(object->model[0], object->model[1], var_r31->unk_00.unk_9C - 45.0f);
                Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
                Hu3DMotionShiftSet(object->model[0], object->motion[10], 0.0f, 8.0f, 0);
            }
            var_r31->unk_EC += 0.5f;
            if (360.0f <= var_r31->unk_EC) {
                var_r31->unk_EC -= 360.0f;
            }
            var_r31->unk_00.unk_6C.x
                = var_r31->unk_D4.x - (400.0 * (1.0 - (0.0 > cosd(var_r31->unk_EC) ? -cosd(var_r31->unk_EC) : cosd(var_r31->unk_EC))));
            var_r31->unk_00.unk_6C.z = var_r31->unk_D4.z + (800.0 * sind(var_r31->unk_EC));
            if ((var_r31->unk_150 == 0xBC1) && (lbl_1_bss_1A4->work[0] >= 0x40E)) {
                var_r31->unk_150 = 0xBC3;
                var_r31->unk_D4 = var_r31->unk_00.unk_6C;
                var_r31->unk_D4.z = -1800.0f;
                Hu3DMotionShiftSet(object->model[0], object->motion[7], 0.0f, 8.0f, 0x40000001);
            }
            break;
        case 0xBC2:
            var_r31->unk_154 &= ~0x80;
            if (((var_r31->unk_154 & 0x20) == 0) && (Hu3DMotionShiftIDGet(object->model[0]) < 0) && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
                var_r31->unk_154 |= 0x20;
                Hu3DMotionShiftSet(object->model[0], object->motion[7], 0.0f, 8.0f, 0x40000001);
            }
            var_r31->unk_100 -= 1.0f;
            if (0.0f > var_r31->unk_100) {
                var_r31->unk_150 = 0xBC1;
                var_r31->unk_154 &= ~0x30;
                Hu3DMotionShiftSet(object->model[0], object->motion[9], 0.0f, 8.0f, 0x40000001);
                fn_1_AAB0(var_r31, var_r31->unk_C8, 1);
            }
            break;
        case 0xBC3:
            if (lbl_1_bss_1A4->work[0] >= 0x40F) {
                if ((var_r31->unk_154 & 0x1000) == 0) {
                    var_r31->unk_154 |= 0x1000;
                    HuAudFXPlay(0x3B);
                }
                if (fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D4) != 0) {
                    var_r31->unk_150++;
                    var_r31->unk_154 &= ~2;
                    Hu3DModelHookObjReset(object->model[1], "g000i00-itemhook_A");
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
                    lbl_1_bss_1A4->work[0] = 0x410;
                    lbl_1_bss_128 = 0.0f;
                }
                fn_1_40C0(&var_r31->unk_00);
            }
            break;
        case 0xBC4:
            if (lbl_1_bss_1A4->work[0] >= 0x411) {
                var_r31->unk_150++;
                var_r31->unk_00.unk_9C = 0.0f;
                fn_1_A470(var_r31, object, "m450mex06-s6kuppa01", 2);
                fn_1_4ED8(&var_r31->unk_00, 0);
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
            }
            break;
        case 0xBC5:
            if (lbl_1_bss_1A4->work[0] >= 0x415) {
                var_r31->unk_150 = 0xBC7;
                var_r31->unk_E0 = 0.0f;
                fn_1_A600(var_r31, object, "m450mex06-s6kuppa01", 2);
                omSetSca(object, 1.5f, 1.5f, 1.5f);
                var_r31->unk_00.unk_9C = 0.0f;
                var_r31->unk_00.unk_6C.y = 1505.0f;
                fn_1_4ED8(&var_r31->unk_00, 0);
                var_r31->unk_00.unk_04 = fn_1_ABD0;
            }
            break;
        case 0xBC6:
            var_r31->unk_E0 += 1.0f;
            if (120.0f < var_r31->unk_E0) {
                var_r31->unk_150++;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_00.unk_3C &= ~0x20;
                fn_1_4ED8(&var_r31->unk_00, 0);
            }
            break;
        case 0xBC7:
            var_r31->unk_00.unk_B8 = fn_1_AB88(var_r31);
            fn_1_19A10(&var_r31->unk_00, &spE4);
            fn_1_40C0(&var_r31->unk_00);
            var_r31->unk_E0 += 1.0f;
            spC8 = (REFRESH_RATE * (3.0f + lbl_1_data_A0C[1].unk_14));
            if (spC8 < var_r31->unk_E0) {
                var_r31->unk_150++;
                var_r31->unk_154 &= ~0x70;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_114 = spE4;
                if (frandmod(0x64) < 0x1E) {
                    var_r31->unk_110 = 0xBC9;
                }
                else if (500.0f > VECDistance(&var_r31->unk_00.unk_6C, &spE4)) {
                    var_r31->unk_110 = 0xBCA;
                    if (lbl_1_data_A0C[1].unk_14 <= 2) {
                        var_r31->unk_110 = 0xBCB;
                    }
                }
                else {
                    var_r31->unk_110 = 0xBCC;
                }
                fn_1_4ED8(&var_r31->unk_00, 0);
            }
            break;
        case 0xBC8:
            VECSubtract(&var_r31->unk_114, &var_r31->unk_00.unk_6C, &spF0);
            var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, atan2d(spF0.x, spF0.z), 0.4f);
            var_r31->unk_E0 += 1.0f;
            var_r31->unk_114 = spE4;
            if (60.0f < var_r31->unk_E0) {
                var_r31->unk_150 = var_r31->unk_110;
                var_r31->unk_154 &= ~0x30;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_00.unk_3C |= 0x20;
            }
            break;
        case 0xBC9:
            if ((var_r31->unk_154 & 0x10) == 0) {
                var_r31->unk_154 |= 0x10;
                Hu3DMotionShiftSet(object->model[0], object->motion[15], 0.0f, 8.0f, 0x40000001);
            }
            else {
                var_r31->unk_00.unk_B8 = 1.5f;
                if ((fn_1_19A10(&var_r31->unk_00, &var_r31->unk_114) != 0) || (var_r31->unk_00.unk_48 > 0)) {
                    var_r31->unk_150 = 0xBC6;
                    var_r31->unk_E0 = 0.0f;
                    var_r31->unk_154 |= 0x20;
                    Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, 0x40000001);
                }
                else {
                    fn_1_40C0(&var_r31->unk_00);
                }
            }
            break;
        case 0xBCA:
            if ((var_r31->unk_154 & 0x10) == 0) {
                var_r31->unk_154 |= 0x10;
                var_r31->unk_12C = fn_1_69F8(NULL, NULL, 0x200);
                var_r31->unk_130 = HuAudFXPlay(0x7BC);
                Hu3DMotionShiftSet(object->model[0], object->motion[12], 0.0f, 8.0f, 0);
            }
            else if (Hu3DMotionShiftIDGet(object->model[0]) < 0) {
                if (45.0f < Hu3DMotionTimeGet(object->model[0])) {
                    var_r20 = 1;
                }
                if (var_r20 != 0) {
                    if ((Hu3DMotionShiftIDGet(object->model[0]) < 0) && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
                        Hu3DMotionTimeSet(object->model[0], 50.0f);
                    }
                    var_r31->unk_E0 += 1.0f;
                    if (3 * REFRESH_RATE < var_r31->unk_E0) {
                        var_r31->unk_150 = 0xBC6;
                        var_r31->unk_E0 = 0.0f;
                        var_r31->unk_154 |= 0x20;
                        Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 30.0f, 0x40000001);
                        fn_1_66A0(var_r31->unk_12C);
                        if (var_r31->unk_130 >= 0) {
                            HuAudFXStop(var_r31->unk_130);
                            var_r31->unk_130 = -1;
                        }
                    }
                }
            }
            break;
        case 0xBCB:
            if ((var_r31->unk_154 & 0x10) == 0) {
                var_r31->unk_154 |= 0x10;
                var_r31->unk_12C = fn_1_69F8(NULL, NULL, 0x200);
                var_r31->unk_130 = HuAudFXPlay(0x7BC);
                Hu3DMotionShiftSet(object->model[0], object->motion[13], 0.0f, 8.0f, 0);
            }
            else if ((var_r31->unk_154 & 0x40) == 0) {
                if (Hu3DMotionShiftIDGet(object->model[0]) < 0) {
                    if (52.0f < Hu3DMotionTimeGet(object->model[0])) {
                        var_r20 = 1;
                    }
                    if (Hu3DMotionEndCheck(object->model[0]) != 0) {
                        var_r31->unk_154 |= 0x40;
                        Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
                        Hu3DMotionSet(object->model[0], object->motion[14]);
                    }
                }
            }
            else {
                var_r20 = 1;
                var_r31->unk_00.unk_B8 = 0.25f;
                fn_1_19A10(&var_r31->unk_00, &spE4);
                fn_1_40C0(&var_r31->unk_00);
                var_r31->unk_E0 += 1.0f;
                if (3 * REFRESH_RATE < var_r31->unk_E0) {
                    var_r31->unk_150 = 0xBC6;
                    var_r31->unk_E0 = 0.0f;
                    var_r31->unk_154 |= 0x20;
                    Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, 0x40000001);
                    fn_1_66A0(var_r31->unk_12C);
                    if (var_r31->unk_130 >= 0) {
                        HuAudFXStop(var_r31->unk_130);
                        var_r31->unk_130 = -1;
                    }
                }
            }
            break;
        case 0xBCC:
            if ((var_r31->unk_154 & 0x10) == 0) {
                var_r31->unk_154 |= 0x10;
                fn_1_18424(object->model[0], &var_r31->unk_114);
                Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
                Hu3DMotionSet(object->model[0], object->motion[11]);
            }
            else if (((var_r31->unk_154 & 0x20) == 0) && (Hu3DMotionShiftIDGet(object->model[0]) < 0)
                && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
                var_r31->unk_150 = 0xBC6;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_154 |= 0x20;
                Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, 0x40000001);
                if (((var_r31->unk_154 & 0x40) == 0) && (lbl_1_data_A0C[1].unk_14 <= 2)) {
                    var_r31->unk_150 = 0xBCD;
                    var_r31->unk_154 |= 0x40;
                }
            }
            break;
        case 0xBCD:
            var_r31->unk_E0 += 1.0f;
            if (10.0f < var_r31->unk_E0) {
                var_r31->unk_150 = 0xBC8;
                var_r31->unk_110 = 0xBCC;
                var_r31->unk_114 = spE4;
                var_r31->unk_154 &= ~0x30;
                var_r31->unk_E0 = 0.0f;
            }
            break;
        case 0xBCE:
            if ((Hu3DMotionShiftIDGet(object->model[0]) < 0) && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
                var_r31->unk_150 = 0xBC6;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_154 &= ~0x8000;
                Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, 0x40000001);
                Hu3DModelAttrSet(lbl_1_bss_1A0->model[var_r31->unk_10C + 2], HU3D_ATTR_DISPOFF);
            }
            break;
        case 0xBCF:
            if ((var_r31->unk_154 & 0x2000) && (Hu3DMotionShiftIDGet(object->model[0]) < 0) && (128.0f < Hu3DMotionTimeGet(object->model[0]))) {
                var_r31->unk_154 &= ~0x2000;
                HuAudFXPlay(0x7BD);
            }
            break;
        default:
            OSReport("*** kuppa mode error(%d)!!\n", var_r31->unk_150);
            break;
    }

    if ((var_r31->unk_150 >= 0xBC6) && (var_r31->unk_150 <= 0xBCD)) {
        if (var_r31->unk_154 & 0x8000) {
            var_r31->unk_E0 = 0.0f;
            if (var_r31->unk_12C >= 0) {
                fn_1_66A0(var_r31->unk_12C);
            }
            if (var_r31->unk_130 >= 0) {
                HuAudFXStop(var_r31->unk_130);
                var_r31->unk_130 = -1;
            }
            if (fn_1_125C0(1, 1) <= 0) {
                var_r31->unk_150 = 0xBCF;
                var_r31->unk_154 |= 0x2000;
                Hu3DMotionShiftSet(object->model[0], object->motion[17], 0.0f, 8.0f, 0);
                HuAudFXPlay(0x3B);
            }
            else {
                var_r31->unk_150 = 0xBCE;
                Hu3DMotionShiftSet(object->model[0], object->motion[16], 0.0f, 8.0f, 0);
                HuAudFXPlay(0x3B);
                Hu3DModelPosSet(lbl_1_bss_1A0->model[var_r31->unk_10C + 2], var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y,
                    150.0f + var_r31->unk_00.unk_6C.z);
                Hu3DModelScaleSet(lbl_1_bss_1A0->model[var_r31->unk_10C + 2], 2.0f, 2.0f, 2.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1A0->model[var_r31->unk_10C + 2], 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_1A0->model[var_r31->unk_10C + 2], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(lbl_1_bss_1A0->model[var_r31->unk_10C + 2], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(lbl_1_bss_1A0->model[var_r31->unk_10C + 2], HU3D_ATTR_DISPOFF);
            }
        }
        if (var_r31->unk_150 != 0xBCF) {
            if ((var_r31->unk_150 < 0xBCE) && ((lbl_1_data_A0C[0].unk_14 <= 0) || (((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_118 >= 0x7EB))) {
                var_r31->unk_150 = 0xBCF;
                Hu3DMotionShiftSet(object->model[0], object->motion[3], 0.0f, 8.0f, 0x40000001);
                HuAudFXPlay(0x3A);
                if (var_r31->unk_12C >= 0) {
                    fn_1_66A0(var_r31->unk_12C);
                }
                if (var_r31->unk_130 >= 0) {
                    HuAudFXStop(var_r31->unk_130);
                    var_r31->unk_130 = -1;
                }
            }
            else if (((var_r31->unk_138 != 0) || (fn_1_19798() != 0)) && (var_r31->unk_150 == 0xBC9)) {
                var_r31->unk_150 = 0xBC6;
                var_r31->unk_E0 = 0.0f;
                Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, 0x40000001);
            }
        }
    }
    if ((var_r31->unk_154 & 0x100) && (Hu3DMotionShiftIDGet(object->model[0]) < 0) && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
        if (var_r31->unk_154 & 0x2000) {
            var_r31->unk_154 &= ~0x2000;
            HuAudFXPlay(0x7BE);
        }
        var_r31->unk_144 -= 1.0f;
        if (0.0f > var_r31->unk_144) {
            var_r31->unk_154 &= ~0x100;
            Hu3DMotionShiftSet(object->model[0], object->motion[var_r31->unk_140], 0.0f, 8.0f, 0x40000001);
        }
    }
    if (var_r31->unk_12C >= 0) {
        if (var_r20 != 0) {
            fn_1_1D18(object->model[0], "g000m0-itemhook_M", &spFC);
            fn_1_1D18(object->model[0], "g000m0-ns_hed", &spD8);
            VECSubtract(&spFC, &spD8, &spF0);
            fn_1_6798(var_r31->unk_12C, 1, &spFC, atan2d(spF0.x, spF0.z), 700.0f, 1550.0f);
        }
        if (fn_1_66DC(var_r31->unk_12C) != 0) {
            var_r31->unk_12C = -1;
        }
    }
    var_r31->unk_134 = lbl_1_data_A0C[0].unk_14;
    spFC = var_r31->unk_00.unk_6C;
    if (var_r31->unk_154 & 2) {
        var_r31->unk_E8 += 4.0f;
        if (360.0f <= var_r31->unk_E8) {
            var_r31->unk_E8 -= 360.0f;
        }
        spCC = var_r31->unk_00.unk_6C.y + (8.0 * sind(var_r31->unk_E8));
        omSetTra(object, 0.0f, 0.0f, 0.0f);
        omSetRot(object, 0.0f, 0.0f, 0.0f);
        Hu3DModelPosSet(object->model[1], var_r31->unk_00.unk_6C.x, spCC, var_r31->unk_00.unk_6C.z);
        Hu3DModelRotSet(object->model[1], 0.0f, var_r31->unk_00.unk_9C, 0.0f);
    }
    else if (var_r31->unk_154 & 1) {
        fn_1_1D70(lbl_1_bss_1A0->model[0], var_r31->unk_CC, &spFC, Hu3DData[object->model[0]].unk_F0);
        MTXScale(sp1F8, 1.5f, 1.5f, 1.5f);
        MTXConcat(Hu3DData[object->model[0]].unk_F0, sp1F8, Hu3DData[object->model[0]].unk_F0);
    }
    else {
        omSetTra(var_r31->unk_00.unk_00, var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, var_r31->unk_00.unk_6C.z);
        omSetRot(var_r31->unk_00.unk_00, 0.0f, var_r31->unk_00.unk_9C, 0.0f);
    }
    fn_1_A3C4(object, &spFC, 2);
}

void fn_1_DBF0(omObjData *object)
{
    Vec sp8;

    UnkM450Struct3 *var_r31;
    s32 var_r29;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM450Struct3), MEMORY_DEFAULT_NUM);
    var_r31 = object->data;
    var_r31->unk_150 = 0xBB8;
    var_r31->unk_154 = 0;
    var_r31->unk_14C = 0;
    var_r31->unk_12C = -1;
    var_r31->unk_130 = -1;
    sp8.x = 0.0f;
    sp8.y = 1500.0f;
    sp8.z = -800.0f;
    fn_1_2C1C(&var_r31->unk_00, object, 4, 9, lbl_1_data_18C, 0, &sp8, 0.0f);
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        object->model[var_r29] = Hu3DModelCreateFile(lbl_1_data_AC[var_r29]);
        Hu3DModelAttrSet(object->model[var_r29], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
        Hu3DModelAttrSet(object->model[var_r29], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(object->model[var_r29], HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(object->model[var_r29], 3);
        Hu3DModelShadowSet(object->model[var_r29]);
    }
    for (var_r29 = 0; var_r29 < 0x13; var_r29++) {
        object->motion[var_r29] = Hu3DJointMotion(object->model[0], HuDataSelHeapReadNum(lbl_1_data_B4[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA));
    }
    Hu3DMotionSet(object->model[0], object->motion[0]);
    CharModelEffectNpcInit(object->model[0], object->motion[1], 2, 8);
    CharModelEffectNpcInit(object->model[0], object->motion[2], 1, 8);
    CharModelEffectNpcInit(object->model[0], object->motion[15], 3, 8);
    var_r31->unk_F4 = 1.0f;
    switch (GWPlayerCfg[lbl_1_bss_120].diff) {
        case 0:
            var_r31->unk_C8 = &lbl_1_data_234[0];
            var_r31->unk_D0 = lbl_1_data_254;
            break;
        case 1:
            var_r31->unk_C8 = &lbl_1_data_234[1];
            var_r31->unk_D0 = lbl_1_data_268;
            break;
        case 2:
            var_r31->unk_C8 = &lbl_1_data_234[2];
            var_r31->unk_D0 = lbl_1_data_27C;
            break;
        case 3:
        default:
            var_r31->unk_C8 = &lbl_1_data_234[3];
            var_r31->unk_D0 = lbl_1_data_290;
            break;
    }
    omSetTra(var_r31->unk_00.unk_00, var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, var_r31->unk_00.unk_6C.z);
    omSetRot(var_r31->unk_00.unk_00, 0.0f, var_r31->unk_00.unk_9C, 0.0f);
    omSetSca(object, 1.5f, 1.5f, 1.5f);
    Hu3DModelAttrReset(*object->model, HU3D_ATTR_DISPOFF);
    object->func = (omObjFunc)fn_1_AD58;
}

s32 fn_1_E0E8(s32 arg0, s32 arg1)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        if (arg1 == lbl_1_data_1CC[var_r31 * 2]) {
            return HuAudFXPlay(lbl_1_data_1CC[arg0 + (var_r31 * 2)]);
        }
    }

    return -1;
}

s32 fn_1_E178(s32 arg0, s32 arg1)
{
    UnkM450Struct3 *var_r31 = lbl_1_bss_130[arg0]->data;
    var_r31->unk_14C = arg1;
    return arg0;
}

void fn_1_E1A8(s32 arg0, s32 arg1, float arg8, u32 arg2, s32 arg3, float arg9)
{
    UnkM450Struct3 *var_r31;
    omObjData *var_r30;

    var_r30 = lbl_1_bss_130[arg0];
    if (arg8 == 0.0f) {
        Hu3DMotionSet(var_r30->model[0], var_r30->motion[arg1]);
    }
    else {
        Hu3DMotionShiftSet(var_r30->model[0], var_r30->motion[arg1], 0.0f, arg8, arg2);
    }
    var_r31 = var_r30->data;
    var_r31->unk_140 = -1;
    var_r31->unk_154 &= ~0x100;
    if (arg3 >= 0) {
        var_r31->unk_140 = arg3;
        var_r31->unk_144 = arg9;
        var_r31->unk_154 |= 0x100;
    }
    var_r31->unk_148 = arg1;
}

void fn_1_E2BC(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    lbl_1_bss_4 = arg0;
    lbl_1_bss_0 = arg1;
    if (arg2 == 0) {
        fn_1_6CB0(fn_1_7D40, arg3);
    }
    else {
        fn_1_6CB0(fn_1_8120, arg3);
    }
}

void fn_1_E3C8(UnkM450Struct3 *arg0, omObjData *arg1, s32 arg2)
{
    s32 var_r30;
    if (arg2 != 0) {
        if (arg1->work[0] == 0) {
            Hu3DModelAttrReset(arg1->model[1], HU3D_ATTR_DISPOFF);
        }
        Hu3DModelAttrReset(arg1->model[0], HU3D_ATTR_DISPOFF);
    }
    else {
        for (var_r30 = 0; var_r30 < 5; var_r30++) {
            Hu3DModelAttrSet(arg1->model[var_r30], HU3D_ATTR_DISPOFF);
        }
    }
    arg0->unk_00.unk_3C &= ~0xC00;
}

UnkData1380Struct lbl_1_data_1380;
UnkData1380Struct lbl_1_data_13B8;

void fn_1_E478(UnkM450Struct3 *arg0, omObjData *arg1)
{
    s32 var_r29;
    float var_f31;
    UnkData1380Struct *var_r30 = &lbl_1_data_1380;
    float var_f30;

    arg0->unk_F8 = -1;
    arg0->unk_154 &= ~0x30;
    arg0->unk_120.x = 0.0f;
    arg0->unk_120.y = 0.0f;
    arg0->unk_120.z = 0.0f;
    if (arg1->work[0] != 0) {
        var_r29 = frandmod(var_r30->unk_08);
        while (var_r30->unk_24[var_r29] < 0) {
            var_r29 = (var_r29 + 1) % var_r30->unk_08;
        }
        arg0->unk_F8 = var_r30->unk_24[var_r29];
        var_f31 = 200.0f * frandf();
        var_f30 = 360.0f * frandf();
        arg0->unk_120.x = var_f31 * sind(var_f30);
        arg0->unk_120.z = var_f31 * cosd(var_f30);
    }
}

void fn_1_E604(UnkM450Struct3 *arg0, omObjData *arg1)
{
    Vec spC;

    arg0->unk_D4 = ((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_00.unk_6C;
    if (((arg0->unk_154 & 0x10) != 0) && ((arg0->unk_154 & 0x20) == 0)) {
        if ((Hu3DMotionShiftIDGet(arg1->model[0]) < 0) && (20.0f < Hu3DMotionTimeGet(arg1->model[0]))) {
            arg0->unk_154 |= 0x20;
            spC = arg0->unk_00.unk_6C;
            spC.x += (200.0 * sind(arg0->unk_00.unk_9C));
            spC.y += 100.0f;
            spC.z += (200.0 * cosd(arg0->unk_00.unk_9C));
            fn_1_17360(&spC, arg0->unk_00.unk_9C);
        }
    }
    else {
        fn_1_19A10(&arg0->unk_00, &arg0->unk_D4);
        fn_1_40C0(&arg0->unk_00);
        VECSubtract(&arg0->unk_00.unk_6C, &arg0->unk_D4, &spC);
        if ((300.0f > sqrtf((spC.x * spC.x) + (spC.z * spC.z))) && ((arg0->unk_154 & 0x10) == 0)) {
            arg0->unk_154 |= 0x10;
            Hu3DMotionShiftSet(arg1->model[0], arg1->motion[5], 0.0f, 8.0f, 0);
        }
    }
}

void fn_1_E918(UnkM450Struct3 *arg0, omObjData *arg1)
{
    arg0->unk_D4 = *fn_1_16314(arg0->unk_F8);
    VECAdd(&arg0->unk_120, &arg0->unk_D4, &arg0->unk_D4);
    if ((arg0->unk_154 & 0x10) && ((arg0->unk_154 & 0x20) == 0) && (Hu3DMotionShiftIDGet(arg1->model[0]) < 0)
        && (Hu3DMotionEndCheck(*arg1->model) != 0)) {
        arg0->unk_154 |= 0x20;
        fn_1_16BC4(&arg0->unk_00.unk_6C, &arg0->unk_120, arg0->unk_F8);
    }
    if (fn_1_19A10(&arg0->unk_00, &arg0->unk_D4) != 0) {
        if ((arg0->unk_154 & 0x10) == 0) {
            arg0->unk_154 |= 0x10;
            Hu3DMotionShiftSet(*arg1->model, arg1->motion[5], 0.0f, 8.0f, 0);
        }
    }
    else {
        fn_1_40C0(&arg0->unk_00);
    }
}

void fn_1_EA50(UnkM450Struct3 *arg0, omObjData *arg1)
{
    arg0->unk_150 = 0xFAD;
    arg0->unk_E0 = 0.0f;
    Hu3DMotionShiftSet(*arg1->model, *arg1->motion, 0.0f, 8.0f, 0);
    fn_1_1D70(lbl_1_bss_1A0->model[0], arg1->work[0] == 0 ? "m450mex06-s3mini2" : "m450mex06-s3mini1", &arg0->unk_D4, NULL);
}

HsfanimStruct00 lbl_1_data_1504;

void fn_1_EB6C(UnkM450Struct3 *arg0, omObjData *arg1)
{
    fn_1_1D18(arg1->model[4], "g007i03-itemhook_M", &arg0->unk_00.unk_6C);
    Hu3DModelHookObjReset(arg1->model[4], "g007i03-itemhook_M");
    Hu3DModelAttrSet(arg1->model[4], HU3D_ATTR_DISPOFF);
    arg0->unk_150 = 0xFAE;
    arg0->unk_154 &= 0xFFFFFFFD;
    arg0->unk_108 = 19.6f;
    arg0->unk_E0 = 0.0f;
    Hu3DMotionSet(arg1->model[0], arg1->motion[6]);
    Hu3DModelAttrReset(arg1->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(arg1->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(arg1->model[0], 1.0f);
    arg0->unk_13C = Hu3DParManLink(lbl_1_bss_24, &lbl_1_data_1504);
    Hu3DParManPosSet(arg0->unk_13C, arg0->unk_00.unk_6C.x, arg0->unk_00.unk_6C.y, arg0->unk_00.unk_6C.z);
    Hu3DParManAttrReset(arg0->unk_13C, 1);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(arg0->unk_13C), 1);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(arg0->unk_13C), 5);
    fn_1_E0E8(arg1->work[0], 0x3F);
}

void fn_1_ED4C(omObjData *object)
{
    Vec spEC;
    float spDC;

    UnkM450Struct3 *var_r31;
    Vec *var_r29;
    UnkM450Struct3 *var_r18;

    var_r18 = lbl_1_bss_130[object->work[0] ^ 1]->data;
    var_r31 = object->data;
    var_r31->unk_00.unk_20 = 0;
    var_r31->unk_00.unk_24 = 0;
    var_r31->unk_00.unk_28 = 0;
    var_r31->unk_00.unk_2C = 0;
    var_r31->unk_00.unk_30 = 0;
    var_r31->unk_00.unk_34 = 0;

    switch (var_r31->unk_150) {
        case 0xFA0:
            if ((lbl_1_bss_1A4->work[0] >= 0x3EF) && (30.0f < lbl_1_bss_128)) {
                var_r31->unk_150++;
                var_r31->unk_E4 = 0.0f;
                var_r31->unk_154 &= ~0x100;
                var_r31->unk_154 |= 0x200;
                var_r31->unk_F0 = var_r31->unk_00.unk_6C.x - (100.0f * (0.0f > var_r31->unk_00.unk_6C.x ? -1 : 1));
            }
            if ((object->work[0] == 0) && (var_r31->unk_148 == 7)) {
                var_r31->unk_00.unk_9C = 0.0f;
            }
            else {
                VECSubtract(&((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_00.unk_6C, &var_r31->unk_00.unk_6C, &spEC);
                var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, atan2d(spEC.x, spEC.z), 0.4f);
            }
            break;
        case 0xFA1:
            fn_1_9F4C(var_r31, object->model[0], lbl_1_bss_4C, 0x7A);
            if (-1100.0f > var_r31->unk_00.unk_6C.z) {
                var_r31->unk_150++;
                fn_1_E2BC(1, 0x1E, object->work[0], 0);
                fn_1_E1A8(object->work[0], 12, 8.0f, 0, 1, 0.0f);
            }
            break;
        case 0xFA2:
            if (lbl_1_bss_10 == 0) {
                fn_1_9F4C(var_r31, object->model[0], lbl_1_bss_4C, 0x7A);
                if (1000.0f > var_r31->unk_00.unk_6C.y) {
                    var_r31->unk_150++;
                    var_r31->unk_154 &= ~0x200;
                    fn_1_E3C8(var_r31, object, 0);
                }
            }
            else {
                var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 0.0f, 0.4f);
            }
            break;
        case 0xFA3:
            if (((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_118 >= 0x7D5) {
                var_r31->unk_150++;
                fn_1_A470(var_r31, object, object->work[0] == 0 ? "m450mex06-s2kuppa01" : "m450mex06-s2kuppa02", 5);
                fn_1_4ED8(&var_r31->unk_00, 0);
                fn_1_E3C8(var_r31, object, 1);
            }
            break;
        case 0xFA4:
            if (lbl_1_bss_1A4->work[0] >= 0x3F2) {
                var_r31->unk_150 = var_r31->unk_150 + 1;
                var_r31->unk_00.unk_9C = 0.0f;
                fn_1_A600(var_r31, object, object->work[0] == 0 ? "m450mex06-s2kuppa01" : "m450mex06-s2kuppa02", 5);
                var_r31->unk_00.unk_6C.y = 1505.0f;
                var_r31->unk_00.unk_3C |= 0x400;
                fn_1_1D70(lbl_1_bss_1A0->model[0], "m450mex06-s2hook04", &var_r31->unk_D4, NULL);
                var_r31->unk_D4.x += (-100.0f + (300.0f * (object->work[0] ^ 1)));
                var_r31->unk_D4.z += (100.0f - (200.0f * (object->work[0] ^ 1)));
            }
            break;
        case 0xFA5:
            if (fn_1_A7CC(var_r31) != 0) {
                var_r31->unk_D4.x = 1200.0f;
                var_r31->unk_D4.z = 150.0f - (300.0f * (object->work[0] ^ 1));
            }
            break;
        case 0xFA6:
            if (fn_1_A7CC(var_r31)) {
                fn_1_E3C8(var_r31, object, 0);
            }
            break;
        case 0xFA7:
            if (lbl_1_bss_1A4->work[0] >= 0x3F7) {
                var_r31->unk_150++;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_E8 = 360.0f * frandf();
                var_r31->unk_154 |= 2;
                Hu3DModelAttrReset(object->model[4], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(object->model[4], HU3D_MOTATTR_PAUSE);
                Hu3DModelHookSet(object->model[4], "g007i03-itemhook_M", object->model[0]);
                var_r31->unk_00.unk_6C.x = 0.0f;
                var_r31->unk_00.unk_6C.y = 3000.0f;
                var_r31->unk_00.unk_6C.z = -300.0f + (600.0f * object->work[0]);
                var_r31->unk_00.unk_9C = 270.0f;
                fn_1_4ED8(&var_r31->unk_00, 0);
                var_r31->unk_00.unk_3C |= 0x2020;
                fn_1_E3C8(var_r31, object, 1);
            }
            break;
        case 0xFA8:
            fn_1_A828(var_r31, 2 * REFRESH_RATE, 3000.0f, 1605.0f);
            if (lbl_1_bss_1A4->work[0] >= 0x3F9) {
                var_r31->unk_150 = var_r31->unk_150 + 1;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_D4.x = 800.0f;
                var_r31->unk_D4.y = var_r31->unk_00.unk_6C.y;
                var_r31->unk_D4.z = -400.0f + (800.0f * object->work[0]);
            }
            break;
        case 0xFA9:
            fn_1_A828(var_r31, 60.0f, var_r31->unk_D4.y, 2055.0f);
            if ((fn_1_A7CC(var_r31) != 0) && (lbl_1_bss_1A4->work[0] < 0x3FA)) {
                lbl_1_bss_1A4->work[0] = 0x3FA;
                lbl_1_bss_128 = 0.0f;
            }
            break;
        case 0xFAA:
            var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 270.0f, 0.05f);
            if (lbl_1_bss_1A4->work[0] >= 0x3FB) {
                var_r31->unk_150++;
                var_r31->unk_FC = 0;
                var_r31->unk_100 = var_r31->unk_C4[var_r31->unk_FC].unk_00;
                var_r31->unk_D4 = var_r31->unk_00.unk_6C;
                Hu3DMotionShiftSet(object->model[0], object->motion[10], 0.0f, 8.0f, 0x40000001);
            }
            break;
        case 0xFAB:
            if (var_r31->unk_154 & 0x80) {
                var_r31->unk_100 += 1.0f;
                if ((Hu3DMotionShiftIDGet(object->model[0]) < 0) && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
                    var_r31->unk_154 = var_r31->unk_154 & 0xFFFFFF7F;
                    Hu3DMotionShiftSet(object->model[0], object->motion[10], 0.0f, 8.0f, 0x40000001);
                }
            }
            else if ((var_r31->unk_134 > lbl_1_data_A0C[0].unk_14) || (lbl_1_data_A0C[0].unk_14 <= 0)) {
                var_r31->unk_100 += 1.0f;
                if (lbl_1_data_A0C[0].unk_14 > 0) {
                    var_r31->unk_154 |= 0x80;
                    Hu3DMotionShiftSet(object->model[0], object->motion[11], 0.0f, 8.0f, 0);
                }
                else {
                    var_r31->unk_150 = 0xFB0;
                    Hu3DMotionShiftSet(object->model[0], object->motion[3], 0.0f, 8.0f, 0);
                }
            }
            var_r31->unk_154 &= ~4;
            var_r31->unk_100 -= 1.0f;
            if ((var_r18->unk_154 & 4) && (0.0f > var_r31->unk_100)) {
                var_r31->unk_FC++;
                if (var_r31->unk_C4[var_r31->unk_FC].unk_00 == 0.0f) {
                    var_r31->unk_FC -= 2;
                }
                var_r31->unk_100 = var_r31->unk_C4[var_r31->unk_FC].unk_00;
                if (var_r31->unk_C4[var_r31->unk_FC].unk_04) {
                    var_r31->unk_150 = 0xFAC;
                    fn_1_E478(var_r31, object);
                    Hu3DMotionShiftSet(object->model[0], object->motion[10], 0.0f, 8.0f, 0);
                }
            }
            else if (fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D4) != 0) {
                var_r31->unk_154 |= 4;
                VECSubtract(&((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_00.unk_6C, &var_r31->unk_00.unk_6C, &spEC);
                var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, atan2d(spEC.x, spEC.z), 0.4f);
            }
            else {
                fn_1_40C0(&var_r31->unk_00);
            }
            if (lbl_1_bss_1A4->work[0] >= 0x3FC) {
                fn_1_EA50(var_r31, object);
            }
            break;
        case 0xFAC:
            var_r31->unk_154 &= ~0x84;
            var_r31->unk_100 -= 1.0f;
            if (0.0f > var_r31->unk_100) {
                var_r31->unk_FC++;
                if (var_r31->unk_C4[var_r31->unk_FC].unk_00 == 0.0f) {
                    var_r31->unk_FC -= 2;
                }
                var_r31->unk_100 = var_r31->unk_C4[var_r31->unk_FC].unk_00;
                if (var_r31->unk_C4[var_r31->unk_FC].unk_04 == 0) {
                    var_r31->unk_150 = 0xFAB;
                    Hu3DMotionShiftSet(object->model[0], object->motion[10], 0.0f, 8.0f, 0x40000001);
                    var_r31->unk_D4.x = 800.0f;
                    if (0.0f > var_r18->unk_00.unk_6C.z) {
                        var_r31->unk_D4.z = 200.0f;
                    }
                    else {
                        var_r31->unk_D4.z = -200.0f;
                    }
                    var_r31->unk_D4.z += var_r31->unk_D4.z * frandf();
                }
            }
            else {
                if (object->work[0] == 0) {
                    fn_1_E604(var_r31, object);
                }
                else {
                    fn_1_E918(var_r31, object);
                }
                if ((((var_r31->unk_154 & 0x10) == 0) || (var_r31->unk_154 & 0x20)) && (lbl_1_bss_1A4->work[0] == 0x3E8)) {
                    var_r31->unk_100 = 0.0f;
                }
            }
            if (lbl_1_bss_1A4->work[0] >= 0x3FC) {
                fn_1_EA50(var_r31, object);
            }
            break;
        case 0xFAD:
            if (lbl_1_bss_1A4->work[0] >= 0x3FD) {
                if (fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D4) != 0) {
                    var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 270.0f, 0.4f);
                    if ((object->work[0] + 0x3FE) == lbl_1_bss_1A4->work[0]) {
                        lbl_1_bss_1A4->work[0] += 1;
                        lbl_1_bss_128 = 0;
                    }
                    if (lbl_1_bss_1A4->work[0] > 0x3FF) {
                        fn_1_EB6C(var_r31, object);
                    }
                }
                fn_1_40C0(&var_r31->unk_00);
            }
            break;
        case 0xFAE:
            var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 270.0f, 0.4f);
            var_r31->unk_00.unk_6C.x += 0.1f * (var_r31->unk_D4.x - var_r31->unk_00.unk_6C.x);
            var_r31->unk_00.unk_6C.z += 0.1f * (var_r31->unk_D4.z - var_r31->unk_00.unk_6C.z);
            if (1505.0f < var_r31->unk_00.unk_6C.y) {
                var_r31->unk_00.unk_6C.y += var_r31->unk_108;
                var_r31->unk_108 = var_r31->unk_108 - 0.98f;
                if (1505.0f >= var_r31->unk_00.unk_6C.y) {
                    var_r31->unk_00.unk_6C.y = 1505.0f;
                    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
                }
            }
            else if (((var_r31->unk_154 & 0x400) == 0) && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
                var_r31->unk_154 |= 0x400;
                Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, 0x40000001);
            }
            if (lbl_1_bss_1A4->work[0] >= 0x402) {
                var_r31->unk_150 = var_r31->unk_150 + 1;
                var_r31->unk_E0 = 0.0f;
                var_r31->unk_00.unk_3C &= ~0x2020;
                fn_1_A470(var_r31, object, object->work[0] == 0 ? "m450mex06-s3mini2" : "m450mex06-s3mini1", 5);
            }
            var_r31->unk_E0 += 1.0f;
            if (var_r31->unk_E0 == 10.0f) {
                Hu3DParManAttrSet(var_r31->unk_13C, 1);
            }
            break;
        case 0xFAF:
            if (lbl_1_bss_1A4->work[0] >= 0x403) {
                var_r31->unk_150 = var_r31->unk_150 + 1;
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
            }
            break;
        case 0xFB0:
            break;
        default:
            OSReport("*** minik mode error(%d)!!\n", var_r31->unk_150);
            break;
    }

    if ((var_r31->unk_154 & 0x100) && (Hu3DMotionShiftIDGet(object->model[0]) < 0) && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
        var_r31->unk_144 -= 1.0f;
        if (0.0f > var_r31->unk_144) {
            var_r31->unk_154 &= ~0x100;
            var_r31->unk_148 = var_r31->unk_140;
            Hu3DMotionShiftSet(object->model[0], object->motion[var_r31->unk_140], 0.0f, 8.0f, 0x40000001);
        }
    }
    var_r31->unk_134 = lbl_1_data_A0C[0].unk_14;
    var_r29 = &lbl_1_bss_34[object->work[0]];
    if (var_r31->unk_154 & 2) {
        *var_r29 = var_r31->unk_00.unk_6C;
        var_r29->y += 100.0f;
        var_r31->unk_E8 += 4.0f;
        if (360.0f <= var_r31->unk_E8) {
            var_r31->unk_E8 -= 360.0f;
        }
        spDC = var_r31->unk_00.unk_6C.y + (8.0 * sind(var_r31->unk_E8));
        omSetTra(object, 0.0f, 0.0f, 0.0f);
        omSetRot(object, 0.0f, 0.0f, 0.0f);
        Hu3DModelPosSet(object->model[4], var_r31->unk_00.unk_6C.x, spDC, var_r31->unk_00.unk_6C.z);
        Hu3DModelRotSet(object->model[4], 0.0f, var_r31->unk_00.unk_9C, 0.0f);
    }
    else if ((var_r31->unk_154 & 1) != 0) {
        fn_1_1D70(lbl_1_bss_1A0->model[0], var_r31->unk_CC, var_r29, Hu3DData[object->model[0]].unk_F0);
    }
    else {
        *var_r29 = var_r31->unk_00.unk_6C;
        omSetTra(var_r31->unk_00.unk_00, var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, var_r31->unk_00.unk_6C.z);
        omSetRot(var_r31->unk_00.unk_00, 0.0f, var_r31->unk_00.unk_9C, 0.0f);
    }
    fn_1_A3C4(object, var_r29, 5);
    if (var_r31->unk_14C != 0) {
        lbl_1_bss_D8++;
        VECAdd(&lbl_1_bss_CC, &var_r31->unk_00.unk_6C, &lbl_1_bss_CC);
    }
}

void fn_1_11D5C(omObjData *object)
{
    Vec sp8;

    UnkM450Struct3 *var_r31;
    s32 var_r29;
    s32 var_r27; // ! - uninitialized
    s32 *var_r26;

    (void)var_r27;
    (void)var_r27;
    (void)var_r27;
    (void)var_r27;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM450Struct3), MEMORY_DEFAULT_NUM);
    var_r31 = object->data;
    var_r31->unk_150 = 0xFA0;
    var_r31->unk_154 = 0;
    var_r31->unk_14C = 0;
    var_r31->unk_13C = -1;
    var_r31->unk_148 = 7;
    sp8.x = -300.0f + (600.0f * object->work[0]);
    sp8.y = 1500.0f;
    sp8.z = -600.0f;
    fn_1_2C1C(&var_r31->unk_00, object, 4, 8, lbl_1_data_1AC, 0, &sp8, 0.0f);
    var_r31->unk_00.unk_3C |= 0x1000;
    for (var_r29 = 0; var_r29 < 5; var_r29++) {
        object->model[var_r29] = Hu3DModelCreateFile(lbl_1_data_100[var_r29]);
        Hu3DModelAttrSet(object->model[var_r29], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
        Hu3DModelAttrSet(object->model[var_r29], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(object->model[var_r29], 3);
        Hu3DModelShadowSet(object->model[var_r29]);
    }
    var_r31->unk_F4 = 1.0f;
    var_r31->unk_C4 = lbl_1_data_204;
    var_r26 = lbl_1_data_150;
    if (object->work[0] == 0) {
        var_r31->unk_C4 = lbl_1_data_1DC;
        var_r26 = lbl_1_data_114;
        Hu3DModelHookSet(object->model[0], "g007m0-itemhook_r", object->model[1]);
    }
    for (var_r29 = 0; var_r29 < 0xF; var_r29++) {
        object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], var_r26[var_r29]);
    }
    Hu3DMotionSet(object->model[0], object->motion[7]);
    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
    if (object->work[0] == 0) {
        CharModelEffectNpcInit(object->model[0], object->motion[1], 0, 0xD);
        CharModelEffectNpcInit(object->model[0], object->motion[2], 1, 0xD);
    }
    else {
        CharModelEffectNpcInit(object->model[0], object->motion[1], 2, 0xD);
        CharModelEffectNpcInit(object->model[0], object->motion[2], 3, 0xD);
    }
    omSetTra(var_r31->unk_00.unk_00, var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, var_r31->unk_00.unk_6C.z);
    omSetRot(var_r31->unk_00.unk_00, 0.0f, var_r31->unk_00.unk_9C, 0.0f);
    if (object->work[0] == 0) {
        Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    var_r31->unk_00.unk_3C &= ~0xC00;
    object->func = (omObjFunc)fn_1_ED4C;
}

Vec lbl_1_data_464 = { 7000.0f, 7000.0f, 7000.0f };
Vec lbl_1_data_470 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_47C = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_488 = { 0.0f, 2200.0f, 1500.0f };
Vec lbl_1_data_494 = { 0.0f, 1800.0f, 0.0f };
Vec lbl_1_data_4A0 = { 0.0f, 1800.f, 650.0f };
Vec lbl_1_data_4AC = { 0.0f, 1700.0f, -650.0f };
Vec lbl_1_data_4B8 = { 0.0f, 1850.0f, 450.0f };
Vec lbl_1_data_4C4 = { 0.0f, 1775.0f, -50.0f };
Vec lbl_1_data_4D0 = { 0.0f, 1850.0f, 550.0f };
Vec lbl_1_data_4DC = { 0.0f, 1775.0f, -50.0f };
Vec lbl_1_data_4E8 = { 0.0f, 3000.0f, 1000.0f };
Vec lbl_1_data_4F4 = { 0.0f, -3.0f, -1.0f };
GXColor lbl_1_data_500 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_504 = { 0.0f, 8000.0f, 1000.0f };
Vec lbl_1_data_510 = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_51C[4] = {
    { 1500.0f, 700.0f, 300.0f },
    { 1500.0f, 1200.0f, 200.0f },
    { 2400.0f, 1400.0f, 400.0f },
    { 2500.0f, 800.0f, -200.0f },
};

s32 lbl_1_data_9EC[8];

void fn_1_12234(void)
{
    UnkDataA0CStruct *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    lbl_1_data_A0C[0].unk_0C = lbl_1_data_9EC[GWPlayerCfg[lbl_1_bss_120].character];
    for (var_r31 = lbl_1_data_A0C, var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        var_r27 = var_r31->unk_10 + 3;
        var_r31->unk_18 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r27 * 4, MEMORY_DEFAULT_NUM);
        var_r31->unk_18[0] = espEntry(var_r31->unk_00, 0, 0);
        var_r31->unk_18[1] = espEntry(var_r31->unk_04, 0, 0);
        var_r31->unk_18[2] = espEntry(var_r31->unk_0C, 0, 0);
        for (var_r30 = 3; var_r30 < var_r27; var_r30++) {
            var_r31->unk_18[var_r30] = espEntry(var_r31->unk_08, 0, 0);
        }
        var_r28 = 0x30;
        if (var_r29 != 0) {
            var_r28 = 0x210;
        }
        for (var_r30 = 0; var_r30 < var_r27; var_r30++) {
            espDrawNoSet(var_r31->unk_18[var_r30], 0);
            espDispOff(var_r31->unk_18[var_r30]);
            espAttrSet(var_r31->unk_18[var_r30], HUSPR_ATTR_NOANIM);
            espBankSet(var_r31->unk_18[var_r30], 0);
            espPriSet(var_r31->unk_18[var_r30], 0x80 - var_r29);
            espPosSet(var_r31->unk_18[var_r30], var_r28, 225.0f);
        }
        espTPLvlSet(var_r31->unk_18[0], 0.5f);
        espColorSet(var_r31->unk_18[0], 0, 0, 0);
        espPosSet(var_r31->unk_18[2], var_r28 - 2, 83.0f);
        for (var_r30 = 3; var_r30 < var_r27; var_r30++) {
            espPosSet(var_r31->unk_18[var_r30], var_r28 - 1, ((var_r30 - 3) * 0x1A) + 0x7B);
        }
    }
}

void fn_1_12540(s32 arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < (lbl_1_data_A0C[arg0].unk_10 + 3); var_r31++) {
        espDispOn(lbl_1_data_A0C[arg0].unk_18[var_r31]);
    }
}

s32 fn_1_125C0(s32 arg0, s32 arg1)
{
    UnkDataA0CStruct *var_r31;
    s32 var_r30;

    var_r31 = &lbl_1_data_A0C[arg0];
    if (arg1 == 0) {
        arg1 = var_r31->unk_10 + 1;
    }
    var_r31->unk_14 -= arg1;
    arg1 = var_r31->unk_14;
    if (var_r31->unk_14 < 0) {
        var_r31->unk_14 = 0;
    }
    for (var_r30 = 0; var_r30 < var_r31->unk_10; var_r30++) {
        if (var_r31->unk_14 <= var_r30) {
            espBankSet(var_r31->unk_18[var_r30 + 3], 1);
        }
    }
    return arg1;
}

void fn_1_12688(omObjData *object)
{
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;

    CameraData *var_r30;

    var_f30 = 1.0f;
    var_f31 = 1.0f;
    if (lbl_1_bss_1A4->work[0] > 0x3EC) {
        var_f30 = 0.8f;
        var_f31 = 0.4f;
    }
    if (object->work[0] != 0) {
        if (lbl_1_bss_1A4->work[0] <= 0x3EB) {
            object->work[0] = object->work[0] - (3.0f - (lbl_1_bss_128 / 120.0f));
            if (object->work[0] > 10 * REFRESH_RATE) {
                object->work[0] = 1;
            }
        }
        if (--object->work[0] == 0) {
            var_r30 = Hu3DCamera;
            VECSubtract(&var_r30->pos, &var_r30->target, &sp8);
            var_f29 = (atan2d(sp8.x, sp8.z)) + ((90.0f * frandf()) - 45.0f);
            omSetRot(object, 0.0f, var_f29, 0.0f);
            omSetSca(object, var_f31, var_f30, var_f31);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
            HuAudFXPlay(0x7C0);
        }
    }
    else if (Hu3DMotionEndCheck(object->model[0]) != 0) {
        object->work[0] = frandmod(10 * REFRESH_RATE);
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
    }
}

void fn_1_1291C(omObjData *object)
{
    object->work[0] = frandmod(10 * REFRESH_RATE);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M450, 0x22));
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->model[0], 1);
    object->func = fn_1_12688;
}

UnkData5CCStruct lbl_1_data_5CC[8] = {
    { "c000m1-ske_head", 0x100, 1, 183.0f },
    { "c001m1-ske_head", 0x100, 1, 183.0f },
    { "c002m1-ske_head", 0x80, 0, 100.0f },
    { "c003m1-ske_head", 0x80, 0, 90.0f },
    { "c004m1-ske_head", 0x80, 0, 83.0f },
    { "c005m1-ske_head", 0x80, 0, 112.0f },
    { "c006m1-ske_head", 0x80, 0, 100.0f },
    { "c007m1-ske_head", 0x80, 0, 70.0f },
};
s32 lbl_1_data_64C[8][0x17] = {
    {
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x08),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x0A),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x09),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x13),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x16),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x19),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1A),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x36),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x6D),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1F),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1C),
        DATA_MAKE_NUM(DATADIR_M450, 0x00),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x0D),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x0E),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x10),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x11),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x7F),
    },
    {
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x02),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x03),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x08),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x0A),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x09),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x13),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x16),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x19),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x1A),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x36),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x6D),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x1F),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x1C),
        DATA_MAKE_NUM(DATADIR_M450, 0x01),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x0D),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x0E),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x10),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x11),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x7F),
    },
    {
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x02),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x03),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x08),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x0A),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x09),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x13),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x16),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x19),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x1A),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x36),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x6D),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x1F),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x1C),
        DATA_MAKE_NUM(DATADIR_M450, 0x02),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x0D),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x0E),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x10),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x11),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x7F),
    },
    {
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x02),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x03),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x08),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x0A),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x09),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x13),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x16),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x19),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x1A),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x36),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x6D),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x1F),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x1C),
        DATA_MAKE_NUM(DATADIR_M450, 0x03),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x0D),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x0E),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x10),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x11),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x7F),
    },
    {
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x02),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x03),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x08),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x0A),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x09),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x13),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x16),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x19),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x1A),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x36),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x6D),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x1F),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x1C),
        DATA_MAKE_NUM(DATADIR_M450, 0x04),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x0D),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x0E),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x10),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x11),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x7F),
    },
    {
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x02),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x03),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x08),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x0A),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x09),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x13),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x16),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x19),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x1A),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x36),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x6D),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x1F),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x1C),
        DATA_MAKE_NUM(DATADIR_M450, 0x05),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x0D),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x0E),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x10),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x11),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x7F),
    },
    {
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x02),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x03),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x08),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x0A),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x09),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x13),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x16),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x19),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x1A),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x36),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x6D),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x1F),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x1C),
        DATA_MAKE_NUM(DATADIR_M450, 0x06),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x0D),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x0E),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x10),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x11),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x7F),
    },
    {
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x02),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x03),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x08),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x0A),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x09),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x13),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x16),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x19),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x1A),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x36),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x6D),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x1F),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x1C),
        DATA_MAKE_NUM(DATADIR_M450, 0x07),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x0D),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x0E),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x10),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x11),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x7F),
    },
};
s32 lbl_1_data_92C[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
UnkData94CStruct lbl_1_data_94C[8] = {
    { 9, 1.0f, 8.0f, 0.0f, 0 },
    { 0xA, 1.0f, 0.0f, 0.0f, 0 },
    { 0xB, 2.5f, 8.0f, 0.0f, 0 },
    { 0xC, 1.0f, 8.0f, 61.0f, 0x40000002 },
    { -1, 1.0f, 0.0f, 0.0f, 0 },
    { 0xD, 1.0f, 8.0f, 0.0f, 0 },
    { 0, 1.0f, 16.0f, 0.0f, 0x40000001 },
    { -1, 1.0f, 0.0f, 0.0f, 0 },
};
s32 lbl_1_data_9EC[8] = {
    0x610000,
    0x610001,
    0x610002,
    0x610003,
    0x610004,
    0x610005,
    0x610006,
    0x610007,
};
UnkDataA0CStruct lbl_1_data_A0C[2] = {
    { 0x00510065, DATA_MAKE_NUM(DATADIR_M450, 0x64), DATA_MAKE_NUM(DATADIR_M450, 0x68), DATA_MAKE_NUM(DATADIR_M450, 0x6B), 0xA, 0xA, NULL },
    { 0x00510067, DATA_MAKE_NUM(DATADIR_M450, 0x66), DATA_MAKE_NUM(DATADIR_M450, 0x69), DATA_MAKE_NUM(DATADIR_M450, 0x6A), 5, 5, NULL },
};
UnkDataA80Struct lbl_1_data_A80[9] = {
    { "m450mex06-s2hook01", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 135.0f, 36.0f / REFRESH_RATE, 350.0f }, -1, 0 },
    { "m450mex06-s2hook01", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 315.0f, 36.0f / REFRESH_RATE, 350.0f }, -2, 0 },
    { "m450mex06-s2hook02", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 45.0f, -36.0f / REFRESH_RATE, 350.0f }, -1, 0 },
    { "m450mex06-s2hook02", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 225.0f, -36.0f / REFRESH_RATE, 350.0f }, -2, 0 },
    { "m450mex06-s2hook03", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 0.0f, 36.0f / REFRESH_RATE, 350.0f }, -1, 0 },
    { "m450mex06-s2hook03", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 120.0f, 36.0f / REFRESH_RATE, 350.0f }, -2, 0 },
    { "m450mex06-s2hook03", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 240.0f, 36.0f / REFRESH_RATE, 350.0f }, -2, 0 },
    { "m450mex06-s2hook04", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 0.0f, 36.0f / REFRESH_RATE, 300.0f }, -1, 0 },
    { "m450mex06-s2hook04", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 180.0f, 36.0f / REFRESH_RATE, 300.0f }, -2, 0 },
};
UnkDataA80Struct lbl_1_data_C58[0xA] = {
    { "m450mex06-s4hook01", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 60.0f, -36.0f / REFRESH_RATE, 300.0f }, -1, 0 },
    { "m450mex06-s4hook01", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 180.0f, -36.0f / REFRESH_RATE, 300.0f }, -2, 0 },
    { "m450mex06-s4hook01", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 300.0f, -36.0f / REFRESH_RATE, 300.0f }, -2, 0 },
    { "m450mex06-s4hook03", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 135.0f, -72.0f / REFRESH_RATE, 300.0f }, -1, 0 },
    { "m450mex06-s4hook03", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 315.0f, -72.0f / REFRESH_RATE, 300.0f }, -2, 0 },
    { "m450mex06-s4hook02", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 225.0f, -36.0f / REFRESH_RATE, 300.0f }, -1, 0 },
    { "m450mex06-s4hook02", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 45.0f, -36.0f / REFRESH_RATE, 300.0f }, -2, 0 },
    { "m450mex06-s4hook04", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 0.0f, 72.0f / REFRESH_RATE, 300.0f }, -1, 0 },
    { "m450mex06-s4hook04", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 120.0f, 72.0f / REFRESH_RATE, 300.0f }, -2, 0 },
    { "m450mex06-s4hook04", { 0.0f, 0.0f, 0.0f }, -1, 0.0f, { 240.0f, 72.0f / REFRESH_RATE, 300.0f }, -2, 0 },
};
char *lbl_1_data_E68[5] = {
    "m450m01-from1to2",
    "m450m01-from2to3",
    "m450m01-from3to4",
    "m450m01-from4to5",
    "m450m01-from5to6",
};
s32 lbl_1_data_E7C[0x21] = {
    DATA_MAKE_NUM(DATADIR_M450, 0x10),
    DATA_MAKE_NUM(DATADIR_M450, 0x11),
    DATA_MAKE_NUM(DATADIR_M450, 0x12),
    DATA_MAKE_NUM(DATADIR_M450, 0x13),
    DATA_MAKE_NUM(DATADIR_M450, 0x14),
    DATA_MAKE_NUM(DATADIR_M450, 0x15),
    DATA_MAKE_NUM(DATADIR_M450, 0x16),
    DATA_MAKE_NUM(DATADIR_M450, 0x16),
    DATA_MAKE_NUM(DATADIR_M450, 0x17),
    DATA_MAKE_NUM(DATADIR_M450, 0x18),
    DATA_MAKE_NUM(DATADIR_M450, 0x19),
    DATA_MAKE_NUM(DATADIR_M450, 0x1A),
    DATA_MAKE_NUM(DATADIR_M450, 0x1B),
    DATA_MAKE_NUM(DATADIR_M450, 0x1C),
    DATA_MAKE_NUM(DATADIR_M450, 0x1D),
    DATA_MAKE_NUM(DATADIR_M450, 0x1E),
    DATA_MAKE_NUM(DATADIR_M450, 0x1F),
    DATA_MAKE_NUM(DATADIR_M450, 0x16),
    DATA_MAKE_NUM(DATADIR_M450, 0x16),
    DATA_MAKE_NUM(DATADIR_M450, 0x20),
    DATA_MAKE_NUM(DATADIR_M450, 0x21),
    DATA_MAKE_NUM(DATADIR_M450, 0x21),
    DATA_MAKE_NUM(DATADIR_M450, 0x21),
    DATA_MAKE_NUM(DATADIR_M450, 0x21),
    DATA_MAKE_NUM(DATADIR_M450, 0x21),
    DATA_MAKE_NUM(DATADIR_M450, 0x28),
    DATA_MAKE_NUM(DATADIR_M450, 0x28),
    DATA_MAKE_NUM(DATADIR_M450, 0x28),
    DATA_MAKE_NUM(DATADIR_M450, 0x29),
    DATA_MAKE_NUM(DATADIR_M450, 0x2A),
    DATA_MAKE_NUM(DATADIR_M450, 0x2A),
    DATA_MAKE_NUM(DATADIR_M450, 0x2B),
    DATA_MAKE_NUM(DATADIR_M450, 0x2B),
};
s32 lbl_1_data_F00[0x17] = {
    DATA_MAKE_NUM(DATADIR_M450, 0x08),
    DATA_MAKE_NUM(DATADIR_M450, 0x09),
    DATA_MAKE_NUM(DATADIR_M450, 0x0B),
    DATA_MAKE_NUM(DATADIR_M450, 0x0C),
    DATA_MAKE_NUM(DATADIR_M450, 0x0E),
    DATA_MAKE_NUM(DATADIR_M450, 0x0A),
    DATA_MAKE_NUM(DATADIR_M450, 0x0A),
    DATA_MAKE_NUM(DATADIR_M450, 0x0A),
    DATA_MAKE_NUM(DATADIR_M450, 0x0A),
    DATA_MAKE_NUM(DATADIR_M450, 0x0D),
    DATA_MAKE_NUM(DATADIR_M450, 0x0D),
    DATA_MAKE_NUM(DATADIR_M450, 0x0D),
    DATA_MAKE_NUM(DATADIR_M450, 0x0D),
    DATA_MAKE_NUM(DATADIR_M450, 0x0D),
    DATA_MAKE_NUM(DATADIR_M450, 0x0D),
    DATA_MAKE_NUM(DATADIR_M450, 0x0D),
    DATA_MAKE_NUM(DATADIR_M450, 0x0D),
    DATA_MAKE_NUM(DATADIR_M450, 0x0D),
    DATA_MAKE_NUM(DATADIR_M450, 0x0F),
    DATA_MAKE_NUM(DATADIR_M450, 0x0F),
    DATA_MAKE_NUM(DATADIR_M450, 0x0F),
    DATA_MAKE_NUM(DATADIR_M450, 0x0F),
    DATA_MAKE_NUM(DATADIR_M450, 0x0F),
};
s32 lbl_1_data_F5C[4]
    = { DATA_MAKE_NUM(DATADIR_M450, 0x24), DATA_MAKE_NUM(DATADIR_M450, 0x25), DATA_MAKE_NUM(DATADIR_M450, 0x26), DATA_MAKE_NUM(DATADIR_M450, 0x27) };
s32 lbl_1_data_F6C[6] = { 0, 60 * REFRESH_RATE, 300 * REFRESH_RATE, 60 * REFRESH_RATE, 300 * REFRESH_RATE, 300 * REFRESH_RATE };
float lbl_1_data_F84[5] = { 1200.0f, 1500.0f, 0.0f, 200.0f, 300.0f };
float lbl_1_data_F98[5] = { 1200.0f, 1500.0f, 0.0f, 200.0f, 300.0f };
float *lbl_1_data_FAC[6] = { NULL, lbl_1_data_F84, NULL, lbl_1_data_F98, NULL, NULL };
s32 lbl_1_data_FC4[5] = { 5, 4, 3, 2, 0 };
s32 lbl_1_data_FD8[5] = { 3, 4, 5, 2, 2 };
s32 lbl_1_data_FEC[5] = { 3, 4, 2, 5, 3 };
s32 lbl_1_data_1000[5] = { 4, 2, 3, 5, 3 };
s32 lbl_1_data_1014[0xA] = { 9, 0x10, 0xA, 8, 0xC, 0xD, 0xB, 0xE, 0xF, 1 };
s32 lbl_1_data_103C[0xA] = { 9, 0x10, 0xA, 8, 0xB, 0xC, 0xE, 0xF, 0xD, 1 };
s32 lbl_1_data_1064[0xA] = { 8, 0xC, 9, 0xB, 0xA, 0x10, 0xE, 0xF, 0xD, 5 };
s32 lbl_1_data_108C[0xA] = { 8, 0xC, 9, 0xB, 0xF, 0xA, 0x10, 0xE, 0xD, 6 };
s32 lbl_1_data_10B4[0xA] = { 8, 0xA, 0x10, 0xC, 9, 0xD, 0xB, 0xE, 0xF, 2 };
s32 lbl_1_data_10DC[0xA] = { 8, 0xA, 0xC, 0xB, 9, 0xD, 0xE, 0xF, 0x10, 8 };
s32 lbl_1_data_1104[0xA] = { 8, 0xC, 9, 0x10, 0xF, 0xA, 0xB, 0xE, 0xD, 3 };
s32 lbl_1_data_112C[0xA] = { 0xB, 8, 0xA, 9, 0xD, 0x10, 0xE, 0xC, 0xF, 5 };
s32 lbl_1_data_1154[0xA] = { 9, 0xC, 0xA, 8, 0xD, 0x10, 0xB, 0xE, 0xF, 5 };
s32 lbl_1_data_117C[0xA] = { 9, 0xB, 0xA, 8, 0xF, 0xC, 0x10, 0xE, 0xD, 6 };
s32 lbl_1_data_11A4[0xA] = { 8, 9, 0x10, 0xE, 0xD, 0xA, 0xC, 0xB, 0xF, 2 };
s32 lbl_1_data_11CC[0xA] = { 0xB, 8, 0xA, 0xE, 9, 0xD, 0xC, 0xF, 0x10, 8 };
s32 *lbl_1_data_11F4[4] = { lbl_1_data_FC4, lbl_1_data_FD8, lbl_1_data_FEC, lbl_1_data_1000 };
s32 *lbl_1_data_1204[3] = { lbl_1_data_1014, lbl_1_data_103C, lbl_1_data_1064 };
s32 *lbl_1_data_1210[3] = { lbl_1_data_108C, lbl_1_data_10B4, lbl_1_data_10DC };
s32 *lbl_1_data_121C[3] = { lbl_1_data_1104, lbl_1_data_112C, lbl_1_data_1154 };
s32 *lbl_1_data_1228[3] = { lbl_1_data_117C, lbl_1_data_11A4, lbl_1_data_11CC };
s32 lbl_1_data_1234[8] = { 0xFFFFFFFF, 0, 1, 0, 0, 0xFFFFFFFF, 0, 1 };

char *lbl_1_data_12A0[4] = {
    "m450mex06-s3hook01",
    "m450mex06-s3hook02",
    "m450mex06-s3hook03",
    "m450mex06-s3hook04",
};

char *lbl_1_data_135C[9] = {
    "m450mex06-s5hook03",
    "m450mex06-s5hook02",
    "m450mex06-s5hook01",
    "m450mex06-s5hook06",
    "m450mex06-s5hook05",
    "m450mex06-s5hook04",
    "m450mex06-s5hook09",
    "m450mex06-s5hook08",
    "m450mex06-s5hook07",
};
UnkData1380Struct lbl_1_data_1380 = { lbl_1_data_12A0, 300.0f, 4, 2, -1, 0, 1, 0, 2, NULL, NULL, NULL, NULL, NULL };
UnkData1380Struct lbl_1_data_13B8 = { lbl_1_data_135C, 200.0f, 9, 3, -1, 0, 1, 0, 8, NULL, NULL, NULL, NULL, NULL };
UnkData1450Struct lbl_1_data_1450[5] = {
    { "m450mex06-s6hook01", { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0, 0, 0 },
    { "m450mex06-s6hook02", { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0, 0, 0 },
    { "m450mex06-s6hook03", { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0, 0, 0 },
    { "m450mex06-s6hook04", { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0, 0, 0 },
    { "m450mex06-s6hook05", { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0, 0, 0 },
};

HsfanimStruct00 lbl_1_data_1504 = {
    0x1E,
    { 0, 0 },
    1.0f,
    30.0f,
    360.0f,
    { 0.0f, 0.1f, 0.0f },
    1.0f,
    1.0f,
    50.0f,
    1.08f,
    1,
    {
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
    },
    {
        { 0xFF, 0xFF, 0xFF, 0 },
        { 0xFF, 0xFF, 0xFF, 0 },
        { 0xFF, 0xFF, 0xFF, 0 },
        { 0xFF, 0xFF, 0xFF, 0 },
    },
};

void fn_1_12A1C(omObjData *object)
{
    float var_f31;
    float var_f30;

    if (object->work[0] != 0) {
        if (lbl_1_bss_108 != 0) {
            if (--object->work[0] == 0) {
                var_f31 = (1500.0f * frandf()) - 750.0f;
                var_f30 = (1500.0f * frandf()) - 750.0f;
                omSetTra(object, var_f31, 1380.0f, var_f30);
                Hu3DMotionTimeSet(object->model[0], 0.0f);
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
            }
        }
    }
    else if (Hu3DMotionEndCheck(object->model[0]) != 0) {
        object->work[0] = frandmod(3 * REFRESH_RATE);
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
    }
}

void fn_1_12B80(omObjData *object)
{
    object->work[0] = frandmod(3 * REFRESH_RATE);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);

    object->model[0] = fn_1_46C(DATA_MAKE_NUM(DATADIR_M450, 0x23));
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->model[0], 1);
    object->func = fn_1_12A1C;
}

void fn_1_12D78(omObjData *object) { }

void fn_1_12D7C(omObjData *object)
{
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    object->model[0] = Hu3DModelCreateFile(lbl_1_data_F00[object->work[0]]);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
    object->func = fn_1_12D78;
}

void fn_1_12E5C(s32 var_r30, s32 var_r29, s32 var_r31)
{
    Vec sp8 = lbl_1_data_1450[var_r30].unk_04;

    VECAdd(&lbl_1_data_1450[var_r29].unk_04, &sp8, &sp8);
    VECScale(&sp8, &sp8, 0.5f);
    sp8.y = 1501.0f;
    Hu3DModelPosSet(lbl_1_bss_1A0->model[var_r31], sp8.x, sp8.y, sp8.z);
    Hu3DModelRotSet(
        lbl_1_bss_1A0->model[var_r31], 0.0f, atan2d(lbl_1_data_1450[var_r30].unk_04.x - sp8.x, lbl_1_data_1450[var_r30].unk_04.z - sp8.z), 0.0f);
    Hu3DModelScaleSet(
        lbl_1_bss_1A0->model[var_r31], 1.0f, 1.0f, VECDistance(&lbl_1_data_1450[var_r30].unk_04, &lbl_1_data_1450[var_r29].unk_04) / 1000.0f);
    Hu3DMotionTimeSet(lbl_1_bss_1A0->model[var_r31], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1A0->model[var_r31], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_1A0->model[var_r31], HU3D_ATTR_DISPOFF);
}

void fn_1_130A4(Vec *arg0, s32 var_r30)
{
    Hu3DModelPosSet(lbl_1_bss_1A0->model[var_r30], arg0->x, arg0->y, arg0->z);
    Hu3DMotionTimeSet(lbl_1_bss_1A0->model[var_r30], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1A0->model[var_r30], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_1A0->model[var_r30], HU3D_ATTR_DISPOFF);
    HuAudFXPlay(0x7B7);
}

void fn_1_13174(UnkData1380Struct *arg0)
{
    s32 var_r30;
    s32 var_r27;

    if (arg0->unk_14 != 0) {
        arg0->unk_14 = 0;
        arg0->unk_18 = 0;
        for (var_r30 = 0; var_r30 < arg0->unk_08; var_r30++) {
            if (arg0->unk_24[var_r30] >= 0) {
                var_r27 = lbl_1_bss_1A0->model[arg0->unk_24[var_r30]];
                MTXIdentity(Hu3DData[var_r27].unk_F0);
                if (arg0->unk_08 == 4) {
                    Hu3DModelRotSet(lbl_1_bss_1A0->model[arg0->unk_24[var_r30]], 0.0f, 90.0f, 0.0f);
                }
                else {
                    Hu3DModelRotSet(lbl_1_bss_1A0->model[arg0->unk_24[var_r30]], 0.0f, -90.0f, 0.0f);
                }
            }
        }
    }
    for (var_r30 = 0; var_r30 < arg0->unk_08; var_r30++) {
        if (arg0->unk_18 != 0) {
            if (arg0->unk_24[var_r30] < 0) {
                fn_1_1D70(lbl_1_bss_1A0->model[0], arg0->unk_00[var_r30], &arg0->unk_30[var_r30], NULL);
            }
            else {
                var_r27 = lbl_1_bss_1A0->model[arg0->unk_24[var_r30]];
                fn_1_1D70(lbl_1_bss_1A0->model[0], arg0->unk_00[var_r30], &arg0->unk_30[var_r30], Hu3DData[var_r27].unk_F0);
            }
        }
        else if (arg0->unk_24[var_r30] >= 0) {
            Hu3DModelPosSet(lbl_1_bss_1A0->model[arg0->unk_24[var_r30]], arg0->unk_30[var_r30].x, arg0->unk_30[var_r30].y, arg0->unk_30[var_r30].z);
        }
    }
    for (var_r30 = 0; var_r30 < arg0->unk_08; var_r30++) {
        if (arg0->unk_28[var_r30] >= 0) {
            omSetTra(lbl_1_bss_144[arg0->unk_28[var_r30]], arg0->unk_30[var_r30].x, arg0->unk_30[var_r30].y, arg0->unk_30[var_r30].z);
        }
    }
}

void fn_1_13560(UnkData1380Struct *arg0, s32 *arg1, s32 arg2)
{
    s32 var_r30;
    Vec *var_r28;

    arg0->unk_30 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0->unk_08 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    arg0->unk_34 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0->unk_08 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    arg0->unk_24 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0->unk_08 * sizeof(s32), MEMORY_DEFAULT_NUM);
    arg0->unk_28 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0->unk_08 * sizeof(s32), MEMORY_DEFAULT_NUM);
    arg0->unk_2C = arg1;
    for (var_r30 = 0; var_r30 < arg0->unk_08; var_r30++) {
        arg0->unk_24[var_r30] = *arg1++;
        arg0->unk_28[var_r30] = arg2++;
        var_r28 = &arg0->unk_34[var_r30];
        var_r28->x = 0.0f;
        var_r28->y = 0.0f;
        var_r28->z = 0.0f;
    }
    arg0->unk_10 = arg0->unk_24[*arg1];
    arg0->unk_24[*arg1] = -1;
    arg0->unk_28[*arg1] = -1;
    fn_1_13174(arg0);
    for (var_r30 = 0; var_r30 < arg0->unk_08; var_r30++) {
        if (arg0->unk_24[var_r30] >= 0) {
            Hu3DModelAttrReset(lbl_1_bss_1A0->model[arg0->unk_24[var_r30]], HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_1_13714(void)
{
    Vec sp8;
    s32 var_r31;
    s32 var_r30;

    if ((0 > lbl_1_bss_F8) || (NULL == lbl_1_bss_FC)) {
        return;
    }
    VECSubtract(&lbl_1_bss_EC, &lbl_1_bss_FC->unk_30[lbl_1_bss_F8], &sp8);
    if (10.0f < VECMag(&sp8)) {
        VECNormalize(&sp8, &sp8);
        VECScale(&sp8, &sp8, 10.0f);
    }
    lbl_1_bss_FC->unk_34[lbl_1_bss_F8] = sp8;
    VECAdd(&sp8, &lbl_1_bss_FC->unk_30[lbl_1_bss_F8], &lbl_1_bss_FC->unk_30[lbl_1_bss_F8]);
    if ((sp8.x == 0.0f) && (sp8.z == 0.0f)) {
        for (var_r30 = lbl_1_bss_FC->unk_20, var_r31 = 0; var_r31 < lbl_1_bss_FC->unk_08; var_r31++, var_r30++) {
            if ((lbl_1_bss_FC->unk_24[var_r31] >= 0) && (var_r30 != lbl_1_bss_FC->unk_24[var_r31])) {
                break;
            }
        }
        if (lbl_1_bss_FC->unk_08 == var_r31) {
            lbl_1_bss_FC->unk_1C = 1;
        }
        lbl_1_bss_FC->unk_30[lbl_1_bss_F8] = lbl_1_bss_EC;
        lbl_1_bss_F8 = -1;
        lbl_1_bss_FC = NULL;
        HuAudFXPlay(0x7B9);
    }
}

void fn_1_139B0(UnkData1380Struct *arg0, s32 arg1)
{
    s32 var_r30;
    s32 var_r28;

    arg0->unk_18 = 1;
    arg0->unk_24[arg0->unk_08 - 1] = arg1;
    for (var_r30 = 0; var_r30 < arg0->unk_08; var_r30++) {
        var_r28 = lbl_1_bss_1A0->model[arg0->unk_24[var_r30]];
        fn_1_1D70(lbl_1_bss_1A0->model[0], arg0->unk_00[var_r30], &arg0->unk_30[var_r30], Hu3DData[var_r28].unk_F0);
        Hu3DModelPosSet(var_r28, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r28, 0.0f, 0.0f, 0.0f);
    }
}

void fn_1_13B4C(UnkData1380Struct *arg0)
{
    arg0->unk_14 = 1;
}

void fn_1_13B58(s32 arg0)
{
    if (arg0 > GWMGTypeGet()) {
        GWMGTypeSet(arg0);
    }
}

s32 fn_1_13B90(s32 arg0)
{
    if (arg0 > GWMGTypeGet()) {
        return 0;
    }
    return 1;
}

void fn_1_13BC4(s32 arg0)
{
    s32 var_r31;
    UnkData1380Struct *var_r30;

    nMap = 0;
    lbl_1_bss_118 = arg0;
    lbl_1_bss_F8 = -1;
    lbl_1_bss_FC = NULL;
    lbl_1_bss_110 = 1;
    lbl_1_bss_304 = lbl_1_data_F6C[arg0];
    var_r30 = NULL;
    switch (arg0) {
        case 1:
            MapObject[nMap++] = lbl_1_bss_144[0];
            break;
        case 2:
            lbl_1_bss_110 = 2;
            var_r30 = &lbl_1_data_1380;
            lbl_1_data_1380.unk_14 = 1;
            MapObject[nMap++] = lbl_1_bss_144[1];
            break;
        case 3:
            MapObject[nMap++] = lbl_1_bss_144[2];
            break;
        case 4:
            lbl_1_bss_110 = 2;
            var_r30 = &lbl_1_data_13B8;
            lbl_1_data_13B8.unk_14 = 1;
            MapObject[nMap++] = lbl_1_bss_144[3];
            break;
        case 5:
            lbl_1_bss_110 = 3;
            MapObject[nMap++] = lbl_1_bss_144[4];
            for (var_r31 = 0; var_r31 < 5; var_r31++) {
                MapObject[nMap++] = lbl_1_bss_144[var_r31 + 0x12];
            }
            break;
    }
    fn_1_13B58(arg0);
    if (NULL != var_r30) {
        for (var_r31 = 0; var_r31 < var_r30->unk_08; var_r31++) {
            if (var_r30->unk_28[var_r31] >= 0) {
                MapObject[nMap++] = lbl_1_bss_144[var_r30->unk_28[var_r31]];
            }
        }
    }
}

void fn_1_13F28(omObjData *object)
{
    Vec sp30;
    float var_f31;

    UnkData1450Struct *var_r31;
    s32 var_r29;
    s32 var_r28;
    Vec *var_r27;
    Vec *var_r26;

    for (var_r29 = 0; var_r29 < lbl_1_data_1380.unk_08; var_r29++) {
        var_r27 = &lbl_1_data_1380.unk_34[var_r29];
        var_r27->x = 0.0f;
        var_r27->y = 0.0f;
        var_r27->z = 0.0f;
    }
    for (var_r29 = 0; var_r29 < lbl_1_data_13B8.unk_08; var_r29++) {
        var_r26 = &lbl_1_data_13B8.unk_34[var_r29];
        var_r26->x = 0.0f;
        var_r26->y = 0.0f;
        var_r26->z = 0.0f;
    }
    fn_1_13714();
    fn_1_13174(&lbl_1_data_1380);
    fn_1_13174(&lbl_1_data_13B8);
    var_r28 = object->model[6];
    fn_1_1D70(object->model[0], "m450mex06-s3hook06", &sp30, Hu3DData[var_r28].unk_F0);
    var_r28 = object->model[7];
    fn_1_1D70(object->model[0], "m450mex06-s3hook05", &sp30, Hu3DData[var_r28].unk_F0);
    var_r28 = object->model[17];
    fn_1_1D70(object->model[0], "m450mex06-s5hook11", &sp30, Hu3DData[var_r28].unk_F0);
    var_r28 = object->model[18];
    fn_1_1D70(object->model[0], "m450mex06-s5hook10", &sp30, Hu3DData[var_r28].unk_F0);
    var_r28 = object->model[19];
    fn_1_1D70(object->model[0], "m450m01-from5to6", &sp30, Hu3DData[var_r28].unk_F0);
    for (var_r29 = 0; var_r29 < 5; var_r29++) {
        var_r31 = &lbl_1_data_1450[var_r29];
        var_r31->unk_10 = var_r31->unk_04.y;
        var_r28 = object->model[var_r29 + 0x14];
        fn_1_1D70(object->model[0], var_r31->unk_00, &var_r31->unk_04, Hu3DData[var_r28].unk_F0);
        fn_1_1D18(object->model[var_r29 + 0x14], "m450_s6a1-s6a1hook", &sp30);
        VECAdd(&sp30, &var_r31->unk_04, &var_r31->unk_04);
        if (1560.0f > var_r31->unk_04.y) {
            var_r31->unk_04.y = 1560.0f;
        }
        omSetTra(lbl_1_bss_144[var_r29 + 0x12], var_r31->unk_04.x, var_r31->unk_04.y, var_r31->unk_04.z);
        var_r31->unk_10 = var_r31->unk_04.y - var_r31->unk_10;
        if (var_r31->unk_18 != 0) {
            if (var_r31->unk_1C != 0) {
                var_f31 = Hu3DMotionTimeGet(object->model[var_r29 + 0x14]);
                if ((10.0f <= var_f31) && (40.0f >= var_f31)) {
                    var_r31->unk_10 = 0.0f;
                }
                if (40.0f <= var_f31) {
                    Hu3DMotionTimeSet(object->model[var_r29 + 0x14], 10.0f);
                    if (var_r31->unk_20 != 0) {
                        var_r31->unk_20 = 0;
                    }
                }
                if (((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_10C < 3) {
                    var_r31->unk_14 += 1.0f;
                    if (20 * REFRESH_RATE < var_r31->unk_14) {
                        var_r31->unk_1C = 0;
                        fn_1_1B510(var_r29);
                    }
                }
            }
            else if (Hu3DMotionEndCheck(object->model[var_r29 + 0x14]) != 0) {
                var_r31->unk_18 = 0;
            }
        }
    }
}

void fn_1_148B0(float arg8, s8 arg0)
{
    Mtx spC;
    ModelData *var_r30;
    s32 var_r31;

    if (lbl_1_bss_114 == 0) {
        if (arg0 == 0x78) {
            MTXRotRad(spC, 0x5A, 0.017453292f * arg8);
        }
        else {
            MTXRotRad(spC, 0x58, 0.017453292f * arg8);
        }
        MTXConcat(spC, lbl_1_bss_88, spC);
        for (var_r31 = 0; var_r31 <= 1; var_r31++) {
            var_r30 = &Hu3DData[lbl_1_bss_1A0->model[var_r31]];
            MTXCopy(spC, var_r30->unk_F0);
        }
        fn_1_13F28(lbl_1_bss_1A0);
    }
}

void fn_1_149C0(s8 arg0)
{
    Mtx spC;
    s32 var_r31;
    ModelData *var_r30;

    lbl_1_bss_114 = 1;
    if (arg0 == 0x78) {
        MTXRotRad(spC, 0x5A, 1.5707964f);
    }
    else {
        MTXRotRad(spC, 0x58, 1.5707964f);
    }
    MTXConcat(spC, lbl_1_bss_88, lbl_1_bss_88);
    for (var_r31 = 0; var_r31 <= 1; var_r31++) {
        var_r30 = &Hu3DData[lbl_1_bss_1A0->model[var_r31]];
        MTXCopy(lbl_1_bss_88, var_r30->unk_F0);
    }
    fn_1_13F28(lbl_1_bss_1A0);
}

void fn_1_14AB8(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        fn_1_1D70(lbl_1_bss_1A0->model[0], lbl_1_data_E68[var_r31], &lbl_1_bss_4C[var_r31], NULL);
    }
}

void fn_1_14BC8(UnkDataA80Struct *arg0, s32 arg1)
{
    s32 var_r31;

    lbl_1_bss_104 = arg0;
    lbl_1_bss_100 = arg1;
    for (var_r31 = 0; var_r31 < lbl_1_bss_100; var_r31++, arg0++) {
        arg0->unk_10 = -1;
        arg0->unk_28 = 1;
    }
}

void fn_1_14C28(void)
{
    UnkDataA80Struct *var_r31;
    s32 var_r30;

    if (NULL != lbl_1_bss_104) {
        for (var_r31 = lbl_1_bss_104, var_r30 = 0; var_r30 < lbl_1_bss_100; var_r30++, var_r31++) {
            if (var_r31->unk_10 >= 0) {
                fn_1_66A0(var_r31->unk_10);
            }
            if (var_r31->unk_24 >= 0) {
                HuAudFXStop(var_r31->unk_24);
                var_r31->unk_24 = -2;
            }
        }
    }
}

void fn_1_14CE8(omObjData *object)
{
    UnkDataA80Struct *var_r31;
    s32 var_r25;
    s32 var_r22;
    s32 var_r19;
    s32 var_r18;

    if (NULL != lbl_1_bss_104) {
        var_r19 = 1;
        var_r18 = 1;
        var_r25 = 0;
        for (var_r31 = lbl_1_bss_104, var_r22 = 0; var_r22 < lbl_1_bss_100; var_r22++, var_r31++) {
            if ((var_r18 != 0) && (var_r31->unk_28 != 0)) {
                var_r25++;
                var_r18 = 0;
                var_r31->unk_28 = 0;
                var_r31->unk_14 = var_r31->unk_18.x;
                fn_1_1D70(lbl_1_bss_1A0->model[0], var_r31->unk_00, &var_r31->unk_04, NULL);
                var_r31->unk_10 = fn_1_69F8(NULL, &var_r31->unk_14, 0x40);
            }
            else if (var_r31->unk_10 >= 0) {
                var_r25++;
                var_r31->unk_14 += var_r31->unk_18.y;
                if (0.0f > var_r31->unk_14) {
                    var_r31->unk_14 += 360.0f;
                }
                if (360.0f <= var_r31->unk_14) {
                    var_r31->unk_14 -= 360.0f;
                }
                if ((lbl_1_bss_308 & 1) == 0) {
                    fn_1_6798(var_r31->unk_10, 1, &var_r31->unk_04, 0.0f, var_r31->unk_18.z, var_r31->unk_04.y);
                    if ((var_r19 != 0) && (var_r31->unk_24 < 0) && (var_r31->unk_24 > -2)) {
                        var_r19 = 0;
                        var_r31->unk_24 = HuAudFXEmiterPlay(var_r31->unk_18.z == 350.0f ? 0x7BF : 0x7AD, &var_r31->unk_04);
                    }
                }
                if (fn_1_66DC(var_r31->unk_10) != 0) {
                    var_r31->unk_10 = -1;
                }
            }
        }
        if (var_r25 == 0) {
            lbl_1_bss_104 = NULL;
        }
    }
    fn_1_13F28(object);
    fn_1_186A8();
}

void fn_1_15308(omObjData *object)
{
    s32 var_r30;
    s32 **var_r22;

    lbl_1_bss_104 = NULL;
    MTXIdentity(lbl_1_bss_88);
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    for (var_r30 = 0; var_r30 < 0x21; var_r30++) {
        object->model[var_r30] = Hu3DModelCreateFile(lbl_1_data_E7C[var_r30]);
        Hu3DModelAttrSet(object->model[var_r30], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
        Hu3DModelAttrSet(object->model[var_r30], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(object->model[var_r30], HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(object->model[var_r30], 0);
        Hu3DModelPosSet(object->model[var_r30], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(object->model[var_r30], 0.0f, 0.0f, 0.0f);
        if (var_r30 != 1) {
            Hu3DModelShadowMapSet(object->model[var_r30]);
        }
    }
    Hu3DMotionSpeedSet(object->model[1], 0.1f);
    switch (GWPlayerCfg[lbl_1_bss_120].diff) {
        case 0:
            var_r22 = lbl_1_data_1204;
            break;
        case 1:
            var_r22 = lbl_1_data_1210;
            break;
        case 2:
            var_r22 = lbl_1_data_121C;
            break;
        case 3:
        default:
            var_r22 = lbl_1_data_1228;
            break;
    }
    fn_1_13560(&lbl_1_data_1380, lbl_1_data_11F4[frandmod(4)], 5);
    fn_1_13560(&lbl_1_data_13B8, var_r22[frandmod(3)], 9);
    fn_1_14AB8();

    for (var_r30 = 0; var_r30 <= 1; var_r30++) {
        Hu3DModelAttrReset(object->model[var_r30], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrReset(object->model[6], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(object->model[17], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(object->model[19], HU3D_ATTR_DISPOFF);
    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        Hu3DModelAttrSet(object->model[var_r30 + 0x14], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(object->model[var_r30 + 0x14], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(object->model[var_r30 + 0x14], HU3D_ATTR_DISPOFF);
    }
    object->func = fn_1_14CE8;
}

float fn_1_15B48(s32 arg0, float arg8, float arg9)
{
    return (arg9 + (arg8 * (arg0 - 1))) / arg0;
}

void fn_1_15BAC(Vec *arg0, Vec *arg1, float arg8, s32 arg2, float *arg3, float *arg4)
{
    Vec sp14;

    VECSubtract(arg1, arg0, &sp14);
    if (360.0f <= arg8) {
        arg8 -= 360.0f;
    }
    else if (0.0f > arg8) {
        arg8 += 360.0f;
    }
    if (360.0f <= arg8) {
        arg8 -= 360.0f;
    }
    else if (0.0f > arg8) {
        arg8 += 360.0f;
    }
    if (360.0f <= arg8) {
        arg8 -= 360.0f;
    }
    else if (0.0f > arg8) {
        arg8 += 360.0f;
    }
    *arg3 = (atan2d(sp14.z, sp14.x))-90.0;
    *arg4 = atan2d(sp14.y, sqrtf((sp14.x * sp14.x) + (sp14.z * sp14.z)));
    if (arg2 == 0) {
        *arg3 *= -1.0f;
    }
    if (arg2 != 0) {
        *arg3 += arg8;
    }
    else {
        *arg3 -= arg8;
    }
    if (180.0f <= *arg3) {
        *arg3 -= 360.0f;
    }
    else if (-180.0f > *arg3) {
        *arg3 += 360.0f;
    }
    if (180.0f <= *arg3) {
        *arg3 -= 360.0f;
    }
    else if (-180.0f > *arg3) {
        *arg3 += 360.0f;
    }
    if (180.0f <= *arg3) {
        *arg3 -= 360.0f;
    }
    else if (-180.0f > *arg3) {
        *arg3 += 360.0f;
    }
    if (60.0f <= *arg3) {
        *arg3 = 60.0f;
    }
    if (-60.0f >= *arg3) {
        *arg3 = -60.0f;
    }
    if (45.0f <= *arg4) {
        *arg4 = 45.0f;
    }
    if (-45.0f >= *arg4) {
        *arg4 = -45.0f;
    }
}

void fn_1_160AC(UnkM450Struct5 *arg0, omObjData *object, Vec *arg2)
{
    float spC;
    float sp8;
    UnkData5CCStruct *var_r30;

    arg0->unk_FC |= 0x8000;
    var_r30 = &lbl_1_data_5CC[arg0->unk_11C];
    if (NULL == arg2) {
        spC = 0.0f;
        sp8 = 0.0f;
    }
    else {
        fn_1_15BAC(&arg0->unk_00.unk_6C, arg2, arg0->unk_00.unk_9C, var_r30->unk_08, &spC, &sp8);
    }
    arg0->unk_C8 = fn_1_15B48(10, arg0->unk_C8, spC);
    arg0->unk_CC = fn_1_15B48(10, arg0->unk_CC, sp8);
    Hu3DMotionForceSet(object->model[0], var_r30->unk_00, var_r30->unk_04, arg0->unk_C8);
    Hu3DMotionForceSet(object->model[0], var_r30->unk_00, 0x200, var_r30->unk_0C - arg0->unk_CC);
}

void fn_1_16280(UnkM450Struct5 *arg0, omObjData *object)
{
    UnkData5CCStruct *var_r31;

    if (arg0->unk_FC & 0x8000) {
        arg0->unk_FC &= ~0x8000;
        var_r31 = &lbl_1_data_5CC[arg0->unk_11C];
        Hu3DMotionNoMotReset(object->model[0], var_r31->unk_00, var_r31->unk_04);
        Hu3DMotionNoMotReset(object->model[0], var_r31->unk_00, 0x200);
    }
}

Vec *fn_1_16314(s32 arg0)
{
    UnkData1380Struct *var_r31;
    s32 var_r30;

    var_r31 = &lbl_1_data_1380;
    for (var_r30 = 0; var_r30 < var_r31->unk_08; var_r30++) {
        if (arg0 == var_r31->unk_24[var_r30]) {
            return &var_r31->unk_30[var_r30];
        }
    }
    return var_r31->unk_30;
}

void fn_1_16378(omObjData *object)
{
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;

    UnkM450Struct4 *var_r31;
    s32 var_r30;

    var_r31 = object->data;
    var_r31->unk_48 += 0.98f;
    if (1555.0f < var_r31->unk_00.y) {
        var_r31->unk_00.y -= var_r31->unk_48;
    }
    if (1555.0f >= var_r31->unk_00.y) {
        if (10.0f < var_r31->unk_48) {
            var_r31->unk_48 = 10.0f;
        }
        var_r31->unk_00.y = 1555.0f;
        if (0.0f > (var_r31->unk_48 / 1.5f)) {
            var_f30 = -(var_r31->unk_48 / 1.5f);
        }
        else {
            var_f30 = var_r31->unk_48 / 1.5f;
        }
        var_r31->unk_48 = -var_f30;
        if (0.0f > var_r31->unk_48) {
            var_f29 = -var_r31->unk_48;
        }
        else {
            var_f29 = var_r31->unk_48;
        }
        if (1.0f < var_f29) {
            var_r31->unk_00.y += 1.0f;
        }
        if (var_r31->unk_74 != 0) {
            var_r31->unk_74 = 0;
            omVibrate(lbl_1_bss_120, 0xC, 4, 2);
            HuAudFXPlay(0x7AE);
        }
    }
    if (Hu3DMotionEndCheck(object->model[0]) != 0) {
        var_r31->unk_78 = 1;
    }
    if ((var_r31->unk_74 == 0) && (lbl_1_bss_1A4->work[0] > 0x3FB)) {
        var_r31->unk_78 = 1;
    }
    if ((var_r31->unk_74 == 0) && (lbl_1_bss_1A4->work[0] == 0x3E8)) {
        var_r31->unk_78 = 1;
    }
    if (var_r31->unk_78 != 0) {
        var_r31->unk_50 = var_r31->unk_50 - 1.0f;
        if ((lbl_1_bss_308 & 1) != 0) {
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                Hu3DModelAttrSet(object->model[var_r30], HU3D_ATTR_DISPOFF);
            }
        }
        else {
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                Hu3DModelAttrReset(object->model[var_r30], HU3D_ATTR_DISPOFF);
            }
        }
        if (0.0f > var_r31->unk_50) {
            Hu3DModelShadowReset(object->model[0]);
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                Hu3DModelAttrSet(object->model[var_r30], HU3D_ATTR_DISPOFF);
            }
            fn_1_24(0x1000, object->model[0]);
            fn_1_24(0x2000, object->model[1]);
            omDelObjEx(lbl_1_bss_33C, object);
            return;
        }
    }
    if (var_r31->unk_78 == 0) {
        for (var_r30 = 0; var_r30 < 1; var_r30++) {
            if (NULL == lbl_1_bss_E8[var_r30]) {
                lbl_1_bss_E8[var_r30] = var_r31;
                break;
            }
        }
    }
    var_f31 = (var_r31->unk_00.y - 1555.0f) / 300.0f;
    if (1.0f < var_f31) {
        var_f31 = 1.0f;
    }
    var_f31 = 1.0f - var_f31;
    var_f31 = 1.0f;
    sp8 = *fn_1_16314(var_r31->unk_70);
    VECAdd(&var_r31->unk_64, &sp8, &sp8);
    var_r31->unk_00.x += var_f31 * (sp8.x - var_r31->unk_00.x);
    var_r31->unk_00.z += var_f31 * (sp8.z - var_r31->unk_00.z);
    omSetTra(object, var_r31->unk_00.x, var_r31->unk_00.y, var_r31->unk_00.z);
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        Hu3DModelPosSet(object->model[var_r30], var_r31->unk_00.x, var_r31->unk_00.y, var_r31->unk_00.z);
    }
}

void fn_1_16910(omObjData *object)
{
    UnkM450Struct4 *var_r30;
    s32 var_r27;
    s32 var_r26;

    var_r30 = object->data;
    var_r30->unk_48 = 0.0f;
    var_r30->unk_50 = 30.0f;
    var_r26 = fn_1_AC(0x1000);
    if (var_r26 < 0) {
        object->model[0] = Hu3DModelLink(lbl_1_bss_2C[0]);
    }
    else {
        object->model[0] = var_r26;
    }
    var_r26 = fn_1_AC(0x2000);
    if (var_r26 < 0) {
        object->model[1] = Hu3DModelLink(lbl_1_bss_2C[1]);
    }
    else {
        object->model[1] = var_r26;
    }
    for (var_r27 = 0; var_r27 < 2; var_r27++) {
        Hu3DModelAttrSet(object->model[var_r27], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(object->model[var_r27], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(object->model[var_r27], 4);
        Hu3DMotionTimeSet(object->model[var_r27], 0.0f);
        Hu3DModelPosSet(object->model[var_r27], var_r30->unk_00.x, var_r30->unk_00.y, var_r30->unk_00.z);
        Hu3DModelRotSet(object->model[var_r27], 0.0f, 0.0f, 0.0f);
    }
    omSetTra(object, var_r30->unk_00.x, var_r30->unk_00.y, var_r30->unk_00.z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowSet(object->model[0]);
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
    object->func = fn_1_16378;
}

void fn_1_16BC4(Vec *arg0, Vec *arg1, s32 arg2)
{
    UnkData1380Struct *spC;

    UnkM450Struct4 *var_r31;
    s32 var_r30;
    omObjData *var_r29;

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        if (lbl_1_data_1CC[var_r30 * 2] == 0x3E) {
            HuAudFXPlay(lbl_1_data_1CC[(var_r30 * 2) + 1]);
            break;
        }
    }
    var_r29 = omAddObjEx(lbl_1_bss_33C, 0x6A, 2, 0, -1, fn_1_16910);
    var_r29->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM450Struct4), MEMORY_DEFAULT_NUM);
    spC = &lbl_1_data_1380;
    var_r31 = var_r29->data;
    var_r31->unk_74 = 1;
    var_r31->unk_78 = 0;
    var_r31->unk_7C = 0;
    var_r31->unk_70 = arg2;
    var_r31->unk_00 = *arg0;
    var_r31->unk_64 = *arg1;
}

void fn_1_16CF4(omObjData *object)
{
    float spC;
    float sp8;

    UnkM450Struct4 *var_r31 = object->data;
    UnkM450Struct5 *var_r30 = lbl_1_bss_138->data;
    spC = var_r30->unk_00.unk_6C.x - var_r31->unk_00.x;
    sp8 = var_r30->unk_00.unk_6C.z - var_r31->unk_00.z;
    var_r31->unk_00.y += (0.1f * (1505.0f - var_r31->unk_00.y));
    if ((lbl_1_bss_1A4->work[0] > 0x3FB) || (lbl_1_bss_1A4->work[0] == 0x3E8)) {
        var_r31->unk_78 = 1;
    }
    if (var_r31->unk_78 != 0) {
        var_r31->unk_40 = var_r31->unk_40 - 0.1f;
        if (0.0f > var_r31->unk_40) {
            Hu3DModelAttrSet(*object->model, HU3D_ATTR_DISPOFF);
            fn_1_24(0x3000, object->model[0]);
            omDelObjEx(lbl_1_bss_33C, object);
            return;
        }
    }
    else {
        var_r31->unk_50 += 1.0f;
        if (var_r31->unk_7C != 0) {
            if (60.0f < var_r31->unk_50) {
                var_r31->unk_78 = 1;
            }
            var_r31->unk_00.x += (0.1f * (var_r30->unk_00.unk_6C.x - var_r31->unk_00.x));
            var_r31->unk_00.z += (0.1f * (var_r30->unk_00.unk_6C.z - var_r31->unk_00.z));
            var_r31->unk_44 *= 1.01f;
        }
        else {
            if (240.0f < var_r31->unk_50) {
                var_r31->unk_78 = 1;
            }
            var_r31->unk_00.x += (11.0 * sind(var_r31->unk_3C));
            var_r31->unk_00.z += (11.0 * cosd(var_r31->unk_3C));
            var_r31->unk_3C = fn_1_1E20(
                var_r31->unk_3C, atan2d(var_r30->unk_00.unk_6C.x - var_r31->unk_00.x, var_r30->unk_00.unk_6C.z - var_r31->unk_00.z), 0.05f);
        }
    }
    if ((var_r31->unk_78 == 0) && (1605.0f > var_r31->unk_00.y)) {
        s32 var_r27;
        for (var_r27 = 0; var_r27 < 1; var_r27++) {
            if (NULL == lbl_1_bss_E4[var_r27]) {
                lbl_1_bss_E4[var_r27] = var_r31;
                break;
            }
        }
    }
    Hu3DModelTPLvlSet(object->model[0], var_r31->unk_40);
    omSetTra(object, var_r31->unk_00.x, var_r31->unk_00.y, var_r31->unk_00.z);
    omSetSca(object, var_r31->unk_44, var_r31->unk_44, var_r31->unk_44);
}

void fn_1_171C4(omObjData *object)
{
    UnkM450Struct4 *var_r29;
    s16 var_r26;

    var_r29 = object->data;
    var_r29->unk_40 = 1.0f;
    var_r29->unk_44 = 1.0f;
    var_r29->unk_50 = 0.0f;
    var_r26 = fn_1_AC(0x3000);
    if (var_r26 < 0) {
        object->model[0] = Hu3DModelLink(lbl_1_bss_2C[2]);
    }
    else {
        object->model[0] = var_r26;
    }
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(object->model[0], 4);
    omSetTra(object, var_r29->unk_00.x, var_r29->unk_00.y, var_r29->unk_00.z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    object->func = fn_1_16CF4;
}

void fn_1_17360(Vec *arg0, float arg8)
{
    omObjData *var_r29;
    s32 var_r30;
    UnkM450Struct4 *var_r31;

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        if (lbl_1_data_1CC[var_r30 * 2] == 0x3E) {
            HuAudFXPlay(lbl_1_data_1CC[var_r30 * 2]);
            break;
        }
    }
    var_r29 = omAddObjEx(lbl_1_bss_33C, 0x6B, 1, 0, -1, fn_1_171C4);
    var_r29->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM450Struct4), MEMORY_DEFAULT_NUM);
    var_r31 = var_r29->data;
    var_r31->unk_78 = 0;
    var_r31->unk_7C = 0;
    var_r31->unk_00 = *arg0;
    var_r31->unk_3C = arg8;
    HuAudFXPlay(0x7AF);
}

void fn_1_17474(omObjData *object)
{
    Mtx spB0;
    Mtx sp80;
    Mtx sp50;
    Vec sp14;
    Vec sp8;
    float var_f31;

    UnkM450Struct4 *var_r31 = object->data;
    if (var_r31->unk_74 != 0) {
        fn_1_1D18(var_r31->unk_54, "g000m0-itemhook_R", &sp8);
        if (Hu3DMotionShiftIDGet(var_r31->unk_54) < 0) {
            Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
            if (165.0f <= Hu3DMotionTimeGet(var_r31->unk_54)) {
                HuAudFXPlay(0x7B0);
                var_r31->unk_74 = 0;
                var_r31->unk_3C = 0.0f;
                var_r31->unk_4C = VECDistance(&sp8, &var_r31->unk_0C);
                Hu3DModelObjMtxGet(var_r31->unk_58, "g000i00-itemhook_A", sp80);
                Hu3DModelObjMtxGet(var_r31->unk_54, "g000m0-itemhook_R", sp50);
                MTXConcat(sp80, sp50, sp80);
                var_r31->unk_00.x = sp80[0][3];
                var_r31->unk_00.y = sp80[1][3];
                var_r31->unk_00.z = sp80[2][3];
                Hu3DModelHookObjReset(var_r31->unk_54, "g000m0-itemhook_R");
                MTXIdentity(Hu3DData[object->model[0]].unk_F0);
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_HOOK);
            }
        }
        var_r31->unk_0C = sp8;
    }
    if (var_r31->unk_74 == 0) {
        if (lbl_1_bss_1A4->work[0] > 0x40D) {
            var_r31->unk_40 = var_r31->unk_40 - 0.05f;
        }
        var_f31 = var_r31->unk_4C;
        sp14.x = 0.0f;
        sp14.y = 0.0f;
        sp14.z = var_f31;
        MTXRotRad(spB0, 0x59, 0.017453292f * (var_r31->unk_5C + var_r31->unk_60));
        MTXMultVec(spB0, &sp14, &sp14);
        VECAdd(&var_r31->unk_00, &sp14, &var_r31->unk_00);
        var_r31->unk_00.y += 0.1f * (1575.0f - var_r31->unk_00.y);
        var_r31->unk_4C += 0.05f * (30.0f - var_r31->unk_4C);
        var_r31->unk_3C += var_r31->unk_4C;
        var_r31->unk_60 += 0.08f * var_r31->unk_4C;
        if (360.0f <= var_r31->unk_60) {
            var_r31->unk_60 = 360.0f;
        }
        sp14.x = 0.0f;
        sp14.y = 1575.0f;
        sp14.z = 0.0f;
        if ((360.0f <= var_r31->unk_60) && (1500.0f < VECDistance(&sp14, &var_r31->unk_00))) {
            var_r31->unk_40 = var_r31->unk_40 - 0.05f;
            if (0.0f > var_r31->unk_40) {
                Hu3DModelShadowReset(object->model[0]);
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
                fn_1_24(0x4000, object->model[0]);
                omDelObjEx(lbl_1_bss_33C, object);
                return;
            }
        }
        if (1.0f <= var_r31->unk_40) {
            s32 var_r28;
            for (var_r28 = 0; var_r28 < 2; var_r28++) {
                if (NULL == lbl_1_bss_DC[var_r28]) {
                    lbl_1_bss_DC[var_r28] = var_r31;
                    break;
                }
            }
        }
        omSetTra(object, var_r31->unk_00.x, var_r31->unk_00.y, var_r31->unk_00.z);
        omSetRot(object, 0.0f, var_r31->unk_3C, 0.0f);
    }
    Hu3DModelShadowDispOn(object->model[0]);
    Hu3DModelTPLvlSet(object->model[0], var_r31->unk_40);
}

void fn_1_17970(s32 arg0, s32 arg1, float arg8)
{
    omObjData *var_r31;
    UnkM450Struct4 *var_r30;
    s16 var_r26;

    HuAudFXPlay(0x3A);
    var_r31 = omAddObjEx(lbl_1_bss_33C, 0x6C, 1, 0, -1, fn_1_17474);
    var_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM450Struct4), MEMORY_DEFAULT_NUM);
    var_r30 = var_r31->data;
    var_r30->unk_40 = 1.0f;
    var_r30->unk_50 = 0.0f;
    var_r30->unk_74 = 1;
    var_r30->unk_78 = 0;
    var_r30->unk_7C = 0;
    var_r30->unk_54 = arg0;
    var_r30->unk_58 = arg1;
    var_r30->unk_5C = arg8;
    var_r30->unk_60 = 0.0f;

    var_r26 = fn_1_AC(0x4000);
    if (var_r26 < 0) {
        var_r31->model[0] = Hu3DModelLink(lbl_1_bss_2C[3]);
    }
    else {
        var_r31->model[0] = var_r26;
    }
    Hu3DModelAttrSet(var_r31->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(var_r31->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(var_r31->model[0], 4);
    omSetTra(var_r31, 0.0f, 0.0f, 0.0f);
    omSetRot(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DModelHookSet(var_r30->unk_54, "g000m0-itemhook_R", var_r31->model[0]);
    Hu3DModelShadowSet(var_r31->model[0]);
    Hu3DModelShadowDispOff(var_r31->model[0]);
}

void fn_1_17BBC(omObjData *object)
{
    Mtx sp84;
    Vec sp18;
    Vec spC;
    float sp8;
    float var_f31;
    float var_f30;
    float var_f28;

    UnkM450Struct4 *var_r31;
    s32 var_r27;
    UnkM450Struct3 *var_r22;

    var_r31 = object->data;
    var_r22 = lbl_1_bss_134->data;
    if (var_r31->unk_74 != 0) {
        fn_1_1D18(var_r31->unk_54, "g000m0-itemhook_R", &spC);
        if ((Hu3DMotionShiftIDGet(var_r31->unk_54) < 0) && (165.0f <= Hu3DMotionTimeGet(var_r31->unk_54))) {
            HuAudFXPlay(0x7B0);
            var_r31->unk_74 = 0;
            var_r31->unk_3C = 0.0f;
            var_r31->unk_4C = VECDistance(&spC, &var_r31->unk_0C);
            fn_1_1D18(var_r31->unk_54, "g000m0-itemhook_R", &var_r31->unk_00);
            Hu3DModelHookObjReset(var_r31->unk_54, "g000m0-itemhook_R");
            MTXIdentity(Hu3DData[*object->model].unk_F0);
            Hu3DModelAttrReset(*object->model, HU3D_ATTR_HOOK);
            var_f31 = var_r31->unk_00.x - var_r31->unk_24.x;
            var_f30 = var_r31->unk_00.z - var_r31->unk_24.z;
            var_r31->unk_30.x = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) / 2;
            var_r31->unk_30.z = 150.0f + var_r31->unk_00.y;
            VECAdd(&var_r31->unk_00, &var_r31->unk_24, &var_r31->unk_24);
            VECScale(&var_r31->unk_24, &var_r31->unk_24, 0.5f);
            var_r31->unk_24.y = var_r31->unk_00.y;
            var_r31->unk_30.y = atan2d(var_r31->unk_00.x - var_r31->unk_24.x, var_r31->unk_00.z - var_r31->unk_24.z);
        }
        var_r31->unk_0C = spC;
        if ((var_r31->unk_74 != 0) && (var_r22->unk_150 >= 0xBCE)) {
            Hu3DModelShadowReset(object->model[0]);
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
            Hu3DModelHookObjReset(var_r31->unk_54, "g000m0-itemhook_R");
            fn_1_24(0x4000, object->model[0]);
            omDelObjEx(lbl_1_bss_33C, object);
            return;
        }
    }
    if (var_r31->unk_74 == 0) {
        if (lbl_1_bss_1A4->work[0] > 0x415) {
            var_r31->unk_40 = var_r31->unk_40 - 0.05f;
        }
        var_f28 = 1575.0f;
        if (180.0f < var_r31->unk_60) {
            var_f28 = var_r31->unk_30.z;
        }
        var_r31->unk_00.y += (0.05f * (var_f28 - var_r31->unk_00.y));
        var_r31->unk_4C += 0.05f * (30.0f - var_r31->unk_4C);
        var_r31->unk_3C += var_r31->unk_4C;
        var_r31->unk_60 += 0.08f * var_r31->unk_4C;
        if (360.0f <= var_r31->unk_60) {
            var_r31->unk_60 = 360.0f;
            VECAdd(&var_r31->unk_18, &var_r31->unk_00, &var_r31->unk_00);
        }
        else {
            spC = var_r31->unk_00;
            sp18.x = (0.6666667f * var_r31->unk_30.x) * sind(var_r31->unk_60);
            sp18.z = var_r31->unk_30.x * cosd(var_r31->unk_60);
            MTXRotRad(sp84, 0x59, 0.017453292f * var_r31->unk_30.y);
            MTXMultVec(sp84, &sp18, &sp18);
            var_r31->unk_00.x = var_r31->unk_24.x + sp18.x;
            var_r31->unk_00.z = var_r31->unk_24.z + sp18.z;
            VECSubtract(&var_r31->unk_00, &spC, &var_r31->unk_18);
        }
        sp18.x = 0.0f;
        sp18.y = 1575.0f;
        sp18.z = 0.0f;
        if ((360.0f <= var_r31->unk_60) && (1500.0f < VECDistance(&sp18, &var_r31->unk_00))) {
            var_r31->unk_40 = var_r31->unk_40 - 0.05f;
            if (0.0f > var_r31->unk_40) {
                Hu3DModelShadowReset(*object->model);
                Hu3DModelAttrSet(*object->model, HU3D_ATTR_DISPOFF);
                fn_1_24(0x4000, object->model[0]);
                omDelObjEx(lbl_1_bss_33C, object);
                return;
            }
        }
        if (1.0f <= var_r31->unk_40) {
            for (var_r27 = 0; var_r27 < 2; var_r27++) {
                if (NULL == lbl_1_bss_DC[var_r27]) {
                    lbl_1_bss_DC[var_r27] = var_r31;
                    break;
                }
            }
        }
        omSetTra(object, var_r31->unk_00.x, var_r31->unk_00.y, var_r31->unk_00.z);
        omSetRot(object, 0.0f, var_r31->unk_3C, 0.0f);
        omSetSca(object, 1.0f, 1.0f, 1.0f);
    }
    Hu3DModelShadowDispOn(object->model[0]);
    Hu3DModelTPLvlSet(object->model[0], var_r31->unk_40);
}

void fn_1_18424(s32 arg0, Vec *arg1)
{
    omObjData *var_r31;
    s16 var_r26;
    UnkM450Struct4 *var_r30;

    var_r31 = omAddObjEx(lbl_1_bss_33C, 0x6C, 1, 0, -1, fn_1_17BBC);
    var_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM450Struct4), MEMORY_DEFAULT_NUM);
    var_r30 = var_r31->data;
    var_r30->unk_54 = arg0;
    var_r30->unk_40 = 1.0f;
    var_r30->unk_50 = 0.0f;
    var_r30->unk_74 = 1;
    var_r30->unk_78 = 0;
    var_r30->unk_7C = 0;
    var_r30->unk_60 = 0.0f;
    var_r30->unk_24 = *arg1;

    var_r26 = fn_1_AC(0x4000);
    if (var_r26 < 0) {
        var_r31->model[0] = Hu3DModelLink(lbl_1_bss_2C[3]);
    }
    else {
        var_r31->model[0] = var_r26;
    }
    Hu3DModelAttrSet(var_r31->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(var_r31->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(var_r31->model[0], 4);
    omSetTra(var_r31, 0.0f, 0.0f, 0.0f);
    omSetRot(var_r31, 0.0f, 0.0f, 0.0f);
    omSetSca(var_r31, 1.0f, 1.0f, 1.0f);
    Hu3DModelHookSet(var_r30->unk_54, "g000m0-itemhook_R", var_r31->model[0]);
    Hu3DModelAttrReset(var_r31->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(var_r31->model[0]);
    Hu3DModelShadowDispOff(var_r31->model[0]);
}

void fn_1_186A8(void)
{
    Vec sp14[3];
    Vec sp8;
    float var_f31;

    s32 var_r31;
    UnkM450Struct5 *var_r30;
    UnkM450Struct3 *var_r29;
    HsfBuffer *var_r28;
    s32 var_r27;
    ModelData *var_r26;
    HsfObject *var_r25;

    if (lbl_1_bss_C4 >= 0) {
        var_r30 = lbl_1_bss_138->data;
        var_r29 = lbl_1_bss_134->data;
        switch (lbl_1_bss_C4) {
            case 0x1388:
                for (var_r31 = 0x19; var_r31 <= 0x1B; var_r31++) {
                    if (Hu3DMotionEndCheck(lbl_1_bss_1A0->model[var_r31]) == 0) {
                        return;
                    }
                }
                lbl_1_bss_C4++;
                lbl_1_bss_C8 = 0.0f;
                Hu3DModelPosSet(lbl_1_bss_1A0->model[28], 0.0f, 1501.0f, 0.0f);
                Hu3DModelAttrReset(lbl_1_bss_1A0->model[28], HU3D_ATTR_DISPOFF);
                Hu3DModelTPLvlSet(lbl_1_bss_1A0->model[28], 0.0f);
                var_r26 = &Hu3DData[lbl_1_bss_1A0->model[28]];
                var_r25 = var_r26->hsfData->object;
                var_r28 = var_r25->data.vertex;
                for (var_r31 = 0; var_r31 < 3; var_r31++) {
                    ((Vec *)var_r28->data)[var_r31].x = lbl_1_data_1450[lbl_1_bss_B8[var_r31]].unk_04.x;
                    ((Vec *)var_r28->data)[var_r31].z = lbl_1_data_1450[lbl_1_bss_B8[var_r31]].unk_04.z;
                    DCFlushRange(&((Vec *)var_r28->data)[var_r31], sizeof(Vec));
                }

                break;
            case 0x1389:
                var_f31 = lbl_1_bss_C8 / 30.0f;
                if (1.0f < var_f31) {
                    var_f31 = 1.0f;
                }
                Hu3DModelTPLvlSet(lbl_1_bss_1A0->model[28], var_f31);
                lbl_1_bss_C8 += 1.0f;
                if ((120.0f < lbl_1_bss_C8) && (var_r30->unk_00.unk_38 == 0)) {
                    lbl_1_bss_C4++;
                    lbl_1_bss_C8 = 0.0f;
                    var_r27 = 0;
                    for (var_r31 = 0; var_r31 < 3; var_r31++) {
                        sp14[var_r31] = lbl_1_data_1450[lbl_1_bss_B8[var_r31]].unk_04;
                    }
                    if ((fn_1_1C39C(var_r30) != 0) && (fn_1_1964C(&var_r30->unk_00.unk_6C, sp14) != 0)) {
                        var_r27++;
                        var_r30->unk_110 = 0x1D;
                        var_r30->unk_FC |= 0x20000;
                        fn_1_130A4(&var_r30->unk_00.unk_6C, 29);
                    }
                    if (fn_1_1964C(&var_r29->unk_00.unk_6C, sp14) != 0) {
                        var_r27++;
                        var_r29->unk_10C = 0x1E;
                        var_r29->unk_154 |= 0x8000;
                        fn_1_130A4(&var_r29->unk_00.unk_6C, 30);
                    }
                    if (var_r27 == 0) {
                        sp8.x = 0.0f;
                        sp8.y = 0.0f;
                        sp8.z = 0.0f;
                        for (var_r31 = 0; var_r31 < 3; var_r31++) {
                            VECAdd(&sp14[var_r31], &sp8, &sp8);
                        }
                        VECScale(&sp8, &sp8, 0.33333334f);
                        fn_1_130A4(&sp8, 29);
                        return;
                    }
                }
                break;
            case 0x138A:
                if (45.0f < lbl_1_bss_C8) {
                    var_f31 = (lbl_1_bss_C8 - 45.0f) / 15.0f;
                    if (1.0f < var_f31) {
                        var_f31 = 1.0f;
                    }
                    Hu3DModelTPLvlSet(lbl_1_bss_1A0->model[28], 1.0f - var_f31);
                    for (var_r31 = 0; var_r31 < 3; var_r31++) {
                        Hu3DModelTPLvlSet(lbl_1_bss_1A0->model[var_r31 + 0x19], 1.0f - var_f31);
                    }
                }
                lbl_1_bss_C8 += 1.0f;
                if (60.0f <= lbl_1_bss_C8) {
                    lbl_1_bss_C4 = -1;
                    Hu3DModelAttrSet(lbl_1_bss_1A0->model[28], HU3D_ATTR_DISPOFF);
                    Hu3DModelTPLvlSet(lbl_1_bss_1A0->model[28], 1.0f);
                    Hu3DModelAttrSet(lbl_1_bss_1A0->model[29], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_1A0->model[30], HU3D_ATTR_DISPOFF);
                    for (var_r31 = 0; var_r31 < 3; var_r31++) {
                        lbl_1_data_1450[lbl_1_bss_B8[0]].unk_1C = 0;
                        fn_1_1B510(lbl_1_bss_B8[0]);
                        Hu3DModelAttrSet(lbl_1_bss_1A0->model[var_r31 + 0x19], HU3D_ATTR_DISPOFF);
                        Hu3DModelTPLvlSet(lbl_1_bss_1A0->model[var_r31 + 0x19], 1.0f);
                    }
                    fn_1_1B4C8(var_r30);
                    return;
                }
                break;
            default:
                OSReport("*** thunder attack mode error(%d)!!\n", lbl_1_bss_C4);
                break;
        }
    }
}

void fn_1_18F30(UnkM450Struct5 *arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;
    float var_f31;
    float var_f30;
    float var_f28;
    float var_f27;

    if (NULL != arg1) {
        sp18 = *arg1;
        var_f27 = arg0->unk_00.unk_C0;
        if ((arg0->unk_00.unk_38 == 3) || (arg0->unk_00.unk_38 == 4)) {
            var_f27 *= 0.5f;
        }
        var_f31 = arg0->unk_00.unk_6C.x - sp18.x;
        var_f30 = arg0->unk_00.unk_6C.z - sp18.z;
        var_f28 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
        if (((sp18.y - 50.0f) < (arg0->unk_00.unk_6C.y + var_f27)) && (arg0->unk_00.unk_BC > var_f28)) {
            if (var_f28 == 0.0f) {
                var_f31 = 0.0f;
                var_f30 = -1.0f;
            }
            else {
                var_f31 /= var_f28;
                var_f30 /= var_f28;
            }
            arg0->unk_00.unk_6C.x = sp18.x + (var_f31 * arg0->unk_00.unk_BC);
            arg0->unk_00.unk_6C.z = sp18.z + (var_f30 * arg0->unk_00.unk_BC);
        }
        if ((arg0->unk_FC & 0x220) == 0) {
            spC = arg0->unk_00.unk_6C;
            spC.y += var_f27 - arg0->unk_00.unk_BC;
            var_f28 = VECDistance(&spC, &sp18);
            if ((spC.y < sp18.y) && ((50.0f + arg0->unk_00.unk_BC) > var_f28)) {
                arg0->unk_FC |= 0x200;
                return;
            }
            spC = arg0->unk_00.unk_6C;
            spC.y += arg0->unk_00.unk_BC;
            var_f28 = VECDistance(&spC, &sp18);
            if ((50.0f + arg0->unk_00.unk_BC) > var_f28) {
                arg0->unk_FC |= 0x20;
            }
        }
    }
}

void fn_1_192AC(UnkM450Struct5 *arg0, UnkM450Struct4 *arg1)
{
    Vec sp8;
    float var_f31;

    if ((NULL != arg1) && (arg0->unk_00.unk_38 == 0) && ((arg0->unk_FC & 0x2000) == 0)) {
        sp8 = arg0->unk_00.unk_6C;
        sp8.y += arg0->unk_00.unk_BC;
        var_f31 = VECDistance(&sp8, &arg1->unk_00);
        if ((50.0f + arg0->unk_00.unk_BC) > var_f31) {
            arg0->unk_FC |= 0x2000;
            arg1->unk_7C = 1;
            arg1->unk_50 = 0.0f;
        }
    }
}

void fn_1_19390(UnkM450Struct5 *var_r31, UnkM450Struct4 *var_r30)
{
    Vec sp8;
    float var_f31;

    if ((NULL != var_r30) && ((var_r31->unk_FC & 0x20) == 0)) {
        sp8 = var_r31->unk_00.unk_6C;
        sp8.y += var_r31->unk_00.unk_BC;
        var_f31 = VECDistance(&sp8, &var_r30->unk_00);
        if ((70.0f + var_r31->unk_00.unk_BC) > var_f31) {
            var_r31->unk_FC |= 0x20;
        }
    }
}

void fn_1_19450(UnkM450Struct5 *var_r31)
{
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 1; var_r30++) {
        fn_1_18F30(var_r31, lbl_1_bss_E8[var_r30]);
    }
    for (var_r30 = 0; var_r30 < 1; var_r30++) {
        fn_1_192AC(var_r31, lbl_1_bss_E4[var_r30]);
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        fn_1_19390(var_r31, lbl_1_bss_DC[var_r30]);
    }
}

s32 fn_1_1964C(Vec *arg0, Vec *arg1)
{
    Vec sp74;
    Vec sp68;
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    VECSubtract(&arg1[1], &arg1[0], &sp74);
    VECSubtract(&arg1[2], &arg1[1], &sp68);
    VECSubtract(&arg1[0], &arg1[2], &sp5C);
    VECCrossProduct(&sp74, &sp68, &sp50);
    VECSubtract(arg0, &arg1[0], &sp44);
    VECSubtract(arg0, &arg1[1], &sp38);
    VECSubtract(arg0, &arg1[2], &sp2C);
    VECCrossProduct(&sp74, &sp50, &sp20);
    VECCrossProduct(&sp68, &sp50, &sp14);
    VECCrossProduct(&sp5C, &sp50, &sp8);
    if ((0.0f >= VECDotProduct(&sp20, &sp44)) && (0.0f >= VECDotProduct(&sp14, &sp38)) && (0.0f >= VECDotProduct(&sp8, &sp2C))) {
        return 1;
    }
    return 0;
}

s32 fn_1_19798(void)
{
    float var_f31;
    float var_f30;
    float var_f28;

    UnkM450Struct5 *var_r31 = lbl_1_bss_138->data;
    UnkM450Struct3 *var_r30 = lbl_1_bss_134->data;

    var_f31 = var_r31->unk_00.unk_6C.x - var_r30->unk_00.unk_6C.x;
    var_f30 = var_r31->unk_00.unk_6C.z - var_r30->unk_00.unk_6C.z;
    var_f28 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    if ((150.0f + var_r31->unk_00.unk_BC) > var_f28) {
        if (var_f28 == 0.0f) {
            var_f31 = 0.0f;
            var_f30 = -1.0f;
        }
        else {
            var_f31 /= var_f28;
            var_f30 /= var_f28;
        }
        var_r31->unk_FC |= 0x200000;
        if (var_r30->unk_150 != 0xBC9) {
            var_r31->unk_FC |= 4;
        }
        var_r31->unk_00.unk_6C.x = var_r30->unk_00.unk_6C.x + (var_f31 * (150.0f + var_r31->unk_00.unk_BC));
        var_r31->unk_00.unk_6C.z = var_r30->unk_00.unk_6C.z + (var_f30 * (150.0f + var_r31->unk_00.unk_BC));
        return 1;
    }
    return 0;
}

s32 fn_1_19A10(WorkPlayerOld *arg0, Vec *arg1)
{
    float var_f31;
    float var_f30;
    float var_f28;

    var_f31 = arg1->x - arg0->unk_6C.x;
    var_f30 = arg1->z - arg0->unk_6C.z;
    var_f28 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    if (10.0f <= var_f28) {
        var_f31 /= var_f28;
        var_f30 /= var_f28;
    }
    else {
        var_f31 = 0.0f;
        var_f30 = 0.0f;
        return 1;
    }
    arg0->unk_20 = 72.0f * var_f31;
    arg0->unk_24 = 72.0f * -var_f30;
    return 0;
}

void fn_1_19C18(omObjData *object)
{
    UnkM450Struct5 *var_r31 = object->data;

    if ((var_r31->unk_FC & 1) != 0) {
        if (1250.0f < var_r31->unk_00.unk_6C.x) {
            var_r31->unk_00.unk_6C.x = 1250.0f;
        }
        if (-1250.0f > var_r31->unk_00.unk_6C.x) {
            var_r31->unk_00.unk_6C.x = -1250.0f;
        }
        if (1250.0f < var_r31->unk_00.unk_6C.z) {
            var_r31->unk_00.unk_6C.z = 1250.0f;
        }
        if (-1250.0f > var_r31->unk_00.unk_6C.z) {
            var_r31->unk_00.unk_6C.z = -1250.0f;
        }
    }
}

void fn_1_19CE0(omObjData *object)
{
    UnkM450Struct5 *var_r31 = object->data;

    if (var_r31->unk_FC & 0x10) {
        var_r31->unk_FC |= 0x42;
        Hu3DMotionShiftSet(object->model[0], object->motion[10], 0.0f, 8.0f, 0x40000002);
    }
    if (var_r31->unk_FC & 0x100) {
        var_r31->unk_FC |= 0x402;
        Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSet(object->model[0], object->motion[14]);
        Hu3DMotionTimeSet(object->model[0], 48.0f);
    }
    if (var_r31->unk_FC & 0x1000) {
        var_r31->unk_FC |= 0x4002;
        Hu3DMotionShiftSet(object->model[0], object->motion[9], 0.0f, 8.0f, 0);
    }
    if (var_r31->unk_FC & 0x10000) {
        var_r31->unk_FC |= 0x40002;
        Hu3DMotionShiftSet(object->model[0], object->motion[16], 0.0f, 8.0f, 0);
        Hu3DModelPosSet(
            lbl_1_bss_1A0->model[var_r31->unk_110 + 2], var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, 50.0f + var_r31->unk_00.unk_6C.z);
        Hu3DMotionTimeSet(lbl_1_bss_1A0->model[var_r31->unk_110 + 2], 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_1A0->model[var_r31->unk_110 + 2], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(lbl_1_bss_1A0->model[var_r31->unk_110 + 2], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(lbl_1_bss_1A0->model[var_r31->unk_110 + 2], HU3D_ATTR_DISPOFF);
    }
    if (var_r31->unk_FC & 0x100000) {
        var_r31->unk_FC |= 0x400002;
        Hu3DMotionShiftSet(object->model[0], object->motion[9], 0.0f, 8.0f, 0);
    }
    var_r31->unk_FC &= ~0x30;
    var_r31->unk_FC &= ~0x300;
    var_r31->unk_FC &= ~0x3000;
    var_r31->unk_FC &= ~0x30000;
    var_r31->unk_FC &= ~0x300000;
    var_r31->unk_100 = 2 * REFRESH_RATE;
    var_r31->unk_F8 = 0.0f;
    var_r31->unk_00.unk_3C &= ~0x210;
}

void fn_1_1A014(omObjData *arg0)
{
    UnkM450Struct5 *var_r31 = arg0->data;

    if (var_r31->unk_FC & 0x555550) {
        var_r31->unk_FC &= ~0x800;
        return;
    }
    var_r31->unk_FC |= 0x800;
}

void fn_1_1A060(void)
{
    Vec sp8;

    Vec *var_r31;
    UnkM450Struct5 *var_r30 = lbl_1_bss_138->data;

    sp8 = var_r30->unk_00.unk_6C;
    if (lbl_1_bss_10C == 0) {
        sp8.y = 1500.0f;
    }
    lbl_1_bss_324 = sp8;
    lbl_1_bss_30C = sp8;
    var_r31 = &lbl_1_data_51C[lbl_1_bss_110];
    lbl_1_bss_324.x += (var_r31->x * sind((180.0f + var_r30->unk_00.unk_9C)));
    lbl_1_bss_324.z += (var_r31->x * cosd((180.0f + var_r30->unk_00.unk_9C)));
    lbl_1_bss_324.y += var_r31->y;
    lbl_1_bss_30C.y += var_r31->z;
}

void fn_1_1A21C(float var_f30, float var_f31)
{
    Vec sp8;
    Vec *var_r31;
    UnkM450Struct5 *var_r30 = lbl_1_bss_138->data;

    sp8 = var_r30->unk_00.unk_6C;
    if (lbl_1_bss_10C == 0) {
        sp8.y = 1500.0f;
    }
    if (var_f31 != 0.0f) {
        sp8.y = var_f31;
    }
    lbl_1_bss_324 = sp8;
    lbl_1_bss_30C = sp8;
    var_r31 = &lbl_1_data_51C[lbl_1_bss_110];
    lbl_1_bss_324.x += var_r31->x * sind(var_f30);
    lbl_1_bss_324.z += var_r31->x * cosd(var_f30);
    lbl_1_bss_324.y += var_r31->y;
    lbl_1_bss_30C.y += var_r31->z;
}

void fn_1_1A3F0(void)
{
    float var_f31;
    float var_f30;
    float var_f28;
    UnkM450Struct5 *var_r31 = lbl_1_bss_138->data;
    UnkM450Struct3 *var_r30 = lbl_1_bss_134->data;

    var_f31 = var_r31->unk_00.unk_6C.x - var_r30->unk_00.unk_6C.x;
    var_f30 = var_r31->unk_00.unk_6C.z - var_r30->unk_00.unk_6C.z;
    var_f28 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    var_f31 = 800.0f * (var_f31 / var_f28);
    var_f30 = 800.0f * (var_f30 / var_f28);
    lbl_1_bss_324 = var_r31->unk_00.unk_6C;
    lbl_1_bss_30C = var_r31->unk_00.unk_6C;
    lbl_1_bss_324.x += var_f31;
    lbl_1_bss_324.y += 350.0f;
    lbl_1_bss_324.z += var_f30;
    lbl_1_bss_30C.y += 150.0f;
}

#ifdef __MWERKS__
#include "src/REL/executor.c"
#endif

void fn_1_1A714(void)
{
    UnkM450Struct5 *var_r31;

    HuSysVWaitSet(1);
    if (HuPadBtn[0] & PAD_BUTTON_X) {
        lbl_1_bss_304 = -1;
    }
    print8(0x18, 0x20, 1.5f, "%d COUNT:%d MODE:%d MES:%d CAM:%d", GWMGTypeGet(), lbl_1_bss_308, lbl_1_bss_1A4->work[0], lbl_1_bss_2FE, lbl_1_bss_110);
    print8(0x18, 0x30, 1.5f, "%f %f %f", lbl_1_bss_330.x, lbl_1_bss_330.y, lbl_1_bss_330.z);
    print8(0x18, 0x40, 1.5f, "%f %f %f", lbl_1_bss_318.x, lbl_1_bss_318.y, lbl_1_bss_318.z);
    print8(0x18, 0x50, 1.5f, "H:%x M:%x", HuMemHeapSizeGet(HEAP_SYSTEM) - HuMemUsedMallocSizeGet(HEAP_SYSTEM),
        HuMemHeapSizeGet(HEAP_DATA) - HuMemUsedMallocSizeGet(HEAP_DATA));
    var_r31 = lbl_1_bss_138->data;
    print8(0x18, 0x60, 1.5f, "%f (%f %f %f)", var_r31->unk_00.unk_A8, var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, var_r31->unk_00.unk_6C.z);
    print8(0x18, 0x70, 1.5f, "%d %d", var_r31->unk_104, var_r31->unk_108);
}

void fn_1_1A940(UnkM450Struct5 *var_r30, Vec *var_r31, s8 var_r27)
{
    Mtx spD0;
    float var_f31;

    s32 var_r23;

    nMap = 0;
    var_r23 = 1;
    lbl_1_bss_10C = 1;
    if (var_r30->unk_E8 == 0.0f) {
        lbl_1_bss_114 = 0;
        if (var_r27 == 0x78) {
            if (var_r31->x > var_r30->unk_00.unk_6C.x) {
                var_r23 = 0;
            }
        }
        else if (var_r31->z < var_r30->unk_00.unk_6C.z) {
            var_r23 = 0;
        }
    }
    if (var_r23 != 0) {
        CharModelEffectEnableSet(var_r30->unk_11C, 0);
        var_r30->unk_E8 += 1.0f;
        var_f31 = 0.0f > var_r31->x ? -var_r31->x : var_r31->x;
        if (var_f31 < (0.0f > var_r31->y ? -var_r31->y : var_r31->y)) {
            var_f31 = 0.0f > var_r31->y ? -var_r31->y : var_r31->y;
        }
        if (var_f31 < (0.0f > var_r31->z ? -var_r31->z : var_r31->z)) {
            var_f31 = 0.0f > var_r31->z ? -var_r31->z : var_r31->z;
        }
        var_f31 = 1505.0f - var_f31;
        if (var_r27 == 0x78) {
            fn_1_148B0(var_r30->unk_E8, var_r27);
            MTXRotRad(spD0, 0x5A, 0.017453292f * var_r30->unk_E8);
            var_r30->unk_00.unk_6C.x = var_r31->x + ((var_f31 * (0.0f > var_r31->x ? -1 : 1)) * sind(var_r30->unk_E8));
        }
        else {
            fn_1_148B0(var_r30->unk_E8, var_r27);
            MTXRotRad(spD0, 0x58, 0.017453292f * var_r30->unk_E8);
            var_r30->unk_00.unk_6C.z = var_r31->z + ((var_f31 * (0.0f > var_r31->z ? -1 : 1)) * sind(var_r30->unk_E8));
        }
        var_r30->unk_00.unk_6C.y = var_r31->y + (var_f31 * cosd(var_r30->unk_E8));
        MTXMultVec(&spD0[0], &var_r30->unk_00.unk_6C, &var_r30->unk_00.unk_6C);
    }
    else {
        if (var_r27 == 0x78) {
            var_r30->unk_00.unk_20 = 0x48;
        }
        else {
            var_r30->unk_00.unk_24 = 0x48;
        }
        fn_1_40C0(&var_r30->unk_00);
    }
    if (90.0f <= var_r30->unk_E8) {
        if (lbl_1_bss_114 == 0) {
            fn_1_149C0(var_r27);
        }
        fn_1_14AB8();
    }
}

s32 fn_1_1B0C4(float *arg0, UnkM450Struct5 *arg1)
{
    if (arg1->unk_00.unk_38 != 0) {
        return 0;
    }
    if (((arg0[0] - arg0[3]) <= arg1->unk_00.unk_6C.x) && ((arg0[0] + arg0[3]) >= arg1->unk_00.unk_6C.x)
        && ((arg0[2] - arg0[4]) <= arg1->unk_00.unk_6C.z) && ((arg0[2] + arg0[4]) >= arg1->unk_00.unk_6C.z)) {
        return 1;
    }
    return 0;
}

void fn_1_1B158(UnkM450Struct5 *arg0, UnkData1380Struct *arg1)
{
    s32 var_r31;

    arg0->unk_104 = -1;
    if (NULL != arg1) {
        if ((arg0->unk_00.unk_38 == 1) || (arg0->unk_00.unk_38 == 3)) {
            return;
        }
        if ((!(1505.0f < arg0->unk_00.unk_6C.y) && !(1495.0f > arg0->unk_00.unk_6C.y)) || (arg0->unk_00.unk_38 == 1) || (arg0->unk_00.unk_38 == 3)) {
            for (var_r31 = 0; var_r31 < arg1->unk_08; var_r31++) {
                if ((0 <= arg1->unk_24[var_r31]) && ((arg1->unk_30[var_r31].x - arg1->unk_04) <= arg0->unk_00.unk_6C.x)
                    && ((arg1->unk_04 + arg1->unk_30[var_r31].x) >= arg0->unk_00.unk_6C.x)
                    && ((arg1->unk_30[var_r31].z - arg1->unk_04) <= arg0->unk_00.unk_6C.z)
                    && ((arg1->unk_04 + arg1->unk_30[var_r31].z) >= arg0->unk_00.unk_6C.z)) {
                    arg0->unk_104 = var_r31;
                }
            }
        }
    }
}

void fn_1_1B2AC(UnkM450Struct5 *var_r30, UnkData1380Struct *var_r31)
{
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    if ((var_r30->unk_FC & 0x800) != 0) {
        if ((NULL == var_r31) || (var_r30->unk_104 < 0) || (lbl_1_bss_F8 >= 0) || (var_r31->unk_1C != 0)) {
            return;
        }
        var_r25 = var_r30->unk_104 % var_r31->unk_0C;
        var_r24 = var_r30->unk_104 / var_r31->unk_0C;
        for (var_r28 = 0; var_r28 < 4; var_r28++) {
            var_r27 = var_r25 + lbl_1_data_1234[var_r28 * 2];
            var_r26 = var_r24 + lbl_1_data_1234[(var_r28 * 2) + 1];
            if ((var_r27 >= 0) && (var_r31->unk_0C > var_r27) && (var_r26 >= 0) && (var_r31->unk_0C > var_r26)) {
                var_r29 = var_r27 + (var_r26 * var_r31->unk_0C);
                if (var_r31->unk_24[var_r29] < 0) {
                    lbl_1_bss_FC = var_r31;
                    lbl_1_bss_F8 = var_r29;
                    var_r31->unk_24[var_r29] = var_r31->unk_24[var_r30->unk_104];
                    var_r31->unk_24[var_r30->unk_104] = -1;
                    var_r31->unk_28[var_r29] = var_r31->unk_28[var_r30->unk_104];
                    var_r31->unk_28[var_r30->unk_104] = -1;
                    lbl_1_bss_EC = var_r31->unk_30[var_r29];
                    var_r31->unk_30[var_r29] = var_r31->unk_30[var_r30->unk_104];
                    HuAudFXPlay(0x7B8);
                    return;
                }
            }
        }
    }
}

s32 fn_1_1B4C8(UnkM450Struct5 *arg0)
{
    s32 var_r31;

    arg0->unk_10C = 0;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_B8[var_r31] = -1;
    }
}

void fn_1_1B510(s32 sp8)
{
    s32 var_r31;
    s32 var_r30;
    UnkM450Struct5 *var_r29 = lbl_1_bss_138->data;

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        if (sp8 == lbl_1_bss_B8[var_r30]) {
            var_r29->unk_10C--;
            lbl_1_bss_B8[var_r30] = -1;
            for (var_r31 = 0; var_r31 < 3; var_r31++) {
                Hu3DModelAttrSet(lbl_1_bss_1A0->model[var_r31 + 0x19], HU3D_ATTR_DISPOFF);
            }
            for (var_r31 = var_r30; var_r31 < 2; var_r31++) {
                lbl_1_bss_B8[var_r31] = lbl_1_bss_B8[var_r31 + 1];
                lbl_1_bss_B8[var_r31 + 1] = -1;
            }
        }
    }
}

void fn_1_1B644(UnkM450Struct5 *arg0)
{
    s32 var_r31;

    arg0->unk_108 = -1;
    if (lbl_1_bss_118 == 5) {
        if ((arg0->unk_00.unk_38 == 1) || (arg0->unk_00.unk_38 == 3)) {
            return;
        }
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            float var_f31;
            float var_f30;
            UnkData1450Struct *var_r30 = &lbl_1_data_1450[var_r31];
            var_f31 = arg0->unk_00.unk_6C.x - var_r30->unk_04.x;
            var_f30 = arg0->unk_00.unk_6C.z - var_r30->unk_04.z;
            if (100.0f > sqrtf((var_f31 * var_f31) + (var_f30 * var_f30))) {
                arg0->unk_108 = var_r31;
            }
        }
    }
}

void fn_1_1B830(UnkM450Struct5 *arg0)
{
    s32 var_r30;

    if (arg0->unk_FC & 0x800) {
        if ((lbl_1_bss_118 != 5) || (arg0->unk_108 < 0)) {
            return;
        }
        if ((arg0->unk_10C < 3) && (lbl_1_data_1450[arg0->unk_108].unk_18 == 0)) {
            for (var_r30 = 0; var_r30 < arg0->unk_10C; var_r30++) {
                if (arg0->unk_108 == lbl_1_bss_B8[var_r30]) {
                    return;
                }
            }
            lbl_1_data_1450[arg0->unk_108].unk_14 = 0.0f;
            lbl_1_data_1450[arg0->unk_108].unk_18 = 1;
            lbl_1_data_1450[arg0->unk_108].unk_1C = 1;
            lbl_1_data_1450[arg0->unk_108].unk_20 = 1;
            lbl_1_bss_B8[arg0->unk_10C++] = arg0->unk_108;
            Hu3DMotionTimeSet(lbl_1_bss_1A0->model[arg0->unk_108 + 0x14], 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_1A0->model[arg0->unk_108 + 0x14], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            if (arg0->unk_10C == 2) {
                fn_1_12E5C(lbl_1_bss_B8[0], lbl_1_bss_B8[1], 25);
                HuAudFXPlay(0x7B4);
            }
            if (arg0->unk_10C == 3) {
                lbl_1_bss_C8 = 0.0f;
                lbl_1_bss_C4 = 0x1388;
                fn_1_12E5C(lbl_1_bss_B8[0], lbl_1_bss_B8[2], 26);
                fn_1_12E5C(lbl_1_bss_B8[1], lbl_1_bss_B8[2], 27);
                HuAudFXPlay(0x7B5);
                HuAudFXPlay(0x7B6);
            }
        }
    }
}

void fn_1_1C060(UnkM450Struct5 *arg0)
{
    UnkData1450Struct *var_r31;

    fn_1_1B644(arg0);
    if (arg0->unk_108 >= 0) {
        var_r31 = &lbl_1_data_1450[arg0->unk_108];
        if ((arg0->unk_00.unk_38 != 1) && (arg0->unk_00.unk_38 != 3) && (1560.0f > arg0->unk_00.unk_6C.y)) {
            arg0->unk_00.unk_6C.y = 1565.0f;
            arg0->unk_00.unk_78.y = 1565.0f;
        }
        if (0.0f != var_r31->unk_10) {
            arg0->unk_00.unk_6C.y = 5.0f + var_r31->unk_04.y;
            arg0->unk_00.unk_78.y = 5.0f + var_r31->unk_04.y;
        }
    }
}

s32 fn_1_1C2D4(UnkM450Struct5 *arg0)
{
    if ((arg0->unk_FC & 0x50) != 0) {
        return 0;
    }
    if ((arg0->unk_FC & 0x500) != 0) {
        return 0;
    }
    if ((arg0->unk_FC & 0x5000) != 0) {
        return 0;
    }
    if ((arg0->unk_FC & 0x50000) != 0) {
        return 0;
    }
    if ((arg0->unk_FC & 0x500000) != 0) {
        return 0;
    }
    if (lbl_1_data_A0C[0].unk_14 <= 0) {
        return 0;
    }
    if ((arg0->unk_FC & 0x80000) != 0) {
        return 0;
    }
    if (arg0->unk_00.unk_38 != 0) {
        return 0;
    }
    return 1;
}

s32 fn_1_1C39C(UnkM450Struct5 *arg0)
{
    if ((arg0->unk_FC & 0x50) != 0) {
        return 0;
    }
    if ((arg0->unk_FC & 0x500) != 0) {
        return 0;
    }
    if ((arg0->unk_FC & 0x5000) != 0) {
        return 0;
    }
    if ((arg0->unk_FC & 0x50000) != 0) {
        return 0;
    }
    if ((arg0->unk_FC & 0x500000) != 0) {
        return 0;
    }
    if ((arg0->unk_FC & 2) != 0) {
        return 0;
    }
    return 1;
}

void fn_1_1C434(UnkM450Struct5 *arg0, omObjData *arg1)
{
    arg0->unk_118++;
    lbl_1_bss_1A4->work[0] += 1;
    lbl_1_bss_128 = 0.0f;
    fn_1_4ED8(&arg0->unk_00, 0);
    Hu3DModelAttrReset(arg1->model[0], HU3D_ATTR_DISPOFF);
    arg1->func = fn_1_20170;
}

void fn_1_1C6E4(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        lbl_1_bss_E8[var_r31] = NULL;
    }
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        lbl_1_bss_E4[var_r31] = NULL;
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_DC[var_r31] = NULL;
    }
}

void fn_1_1C77C(UnkM450Struct5 *arg0)
{
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    UnkM450Struct3 *var_r30 = lbl_1_bss_134->data;

    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = 1.0f;
    MTXRotRad(sp20, 0x59, 0.017453292f * arg0->unk_00.unk_9C);
    MTXMultVec(sp20, &sp14, &sp14);
    VECNormalize(&sp14, &sp14);
    VECSubtract(&arg0->unk_00.unk_6C, &var_r30->unk_00.unk_6C, &arg0->unk_DC);
    VECNormalize(&arg0->unk_DC, &arg0->unk_DC);
    VECSubtract(&var_r30->unk_00.unk_6C, &arg0->unk_00.unk_6C, &sp8);
    VECNormalize(&sp8, &sp8);
    if (0.0f <= VECDotProduct(&sp14, &sp8)) {
        arg0->unk_114 = 0x11;
        return;
    }
    arg0->unk_114 = 0x13;
}

s32 fn_1_1C898(UnkM450Struct5 *var_r31, omObjData *var_r30)
{
    s32 sp3C;
    float var_f31;

    if (var_r31->unk_FC & 2) {
        if (var_r31->unk_FC & 0x40) {
            var_r31->unk_F8 += 1.0f;
            if (var_r31->unk_F8 == 15.0f) {
                Hu3DModelAttrReset(var_r30->model[0], HU3D_MOTATTR_PAUSE);
            }
            if ((15.0f < var_r31->unk_F8) && (Hu3DMotionEndCheck(var_r30->model[0]) != 0)) {
                var_r31->unk_FC &= ~0x40;
                fn_1_4ED8(&var_r31->unk_00, 0);
            }
            return 0;
        }
        if (var_r31->unk_FC & 0x400) {
            var_r31->unk_F8 += 1.0f;
            if (var_r31->unk_F8 == 15.0f) {
                Hu3DModelAttrReset(var_r30->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            }
            if ((15.0f < var_r31->unk_F8) && (Hu3DMotionEndCheck(var_r30->model[0]) != 0)) {
                var_r31->unk_FC &= ~0x400;
                fn_1_4ED8(&var_r31->unk_00, 0);
            }
            return 0;
        }
        if (var_r31->unk_FC & 0x4000) {
            var_r31->unk_F8 += 1.0f;
            if (120.0f < var_r31->unk_F8) {
                var_r31->unk_FC &= ~0x4000;
                fn_1_4ED8(&var_r31->unk_00, 0);
            }
            return 0;
        }
        if (var_r31->unk_FC & 0x40000) {
            var_r31->unk_F8 += 1.0f;
            if (120.0f < var_r31->unk_F8) {
                var_r31->unk_FC &= ~0x40000;
                fn_1_4ED8(&var_r31->unk_00, 0);
                Hu3DModelAttrSet(lbl_1_bss_1A0->model[var_r31->unk_110 + 2], HU3D_ATTR_DISPOFF);
            }
            return 0;
        }
        if (var_r31->unk_FC & 0x400000) {
            if ((Hu3DMotionShiftIDGet(var_r30->model[0]) < 0) && (Hu3DMotionEndCheck(var_r30->model[0]) != 0)) {
                if (var_r31->unk_F8 == 0.0f) {
                    var_r31->unk_F8 = 1.0f;
                    Hu3DMotionShiftSet(var_r30->model[0], var_r30->motion[var_r31->unk_114 + 1], 0.0f, 8.0f, 0);
                }
                else {
                    var_r31->unk_FC &= ~0x400000;
                    fn_1_4ED8(&var_r31->unk_00, 0);
                }
            }
            return 0;
        }
        if ((var_r31->unk_100 & 1) == 0) {
            Hu3DModelAttrSet(var_r30->model[0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(var_r30->model[0], HU3D_ATTR_DISPOFF);
        }
        if (--var_r31->unk_100 < 0) {
            var_r31->unk_FC &= ~0x70;
            var_r31->unk_FC &= ~0x700;
            var_r31->unk_FC &= ~0x7000;
            var_r31->unk_FC &= ~0x70000;
            var_r31->unk_FC &= ~0x700004;
            var_r31->unk_FC &= ~0x2;
            Hu3DModelAttrReset(var_r30->model[0], HU3D_ATTR_DISPOFF);
        }
        return 1;
    }
    if (var_r31->unk_FC & 0x110) {
        fn_1_40C0(&var_r31->unk_00);
        return 0;
    }
    if ((var_r31->unk_FC & 0x1000) != 0) {
        if ((Hu3DMotionShiftIDGet(var_r30->model[0]) < 0) && (Hu3DMotionEndCheck(var_r30->model[0]) != 0)) {
            var_r31->unk_00.unk_9C += (10.0 + (8.0 * sind((180.0f * (var_r31->unk_F8 / 60.0f)))));
            if (360.0f <= var_r31->unk_00.unk_9C) {
                var_r31->unk_00.unk_9C -= 360.0f;
            }
            var_r31->unk_F8 += 1.0f;
            if (60.0f < var_r31->unk_F8) {
                fn_1_19CE0(var_r30);
            }
        }
        return 0;
    }
    if (var_r31->unk_FC & 0x10000) {
        fn_1_19CE0(var_r30);
        return 0;
    }
    if (var_r31->unk_FC & 0x100000) {
        var_r31->unk_00.unk_20 = 72.0f * var_r31->unk_DC.x;
        var_r31->unk_00.unk_24 = -(72.0f * var_r31->unk_DC.z);
        fn_1_40C0(&var_r31->unk_00);
        return 0;
    }
    if ((var_r31->unk_FC & 0x20) != 0) {
        if (lbl_1_bss_118 < 4) {
            omVibrate(lbl_1_bss_120, 0xC, 4, 2);
        }
        else {
            omVibrate(lbl_1_bss_120, 0xC, 0xC, 0);
        }
        HuAudCharVoicePlay(var_r31->unk_11C, 0x123);
        var_r31->unk_FC |= 0x10;
        var_r31->unk_00.unk_3C |= 0x210;
        fn_1_2BD0(&var_r31->unk_00, VERSION_NTSC ? 48.179995f : 57.816f, 0.0f);
        Hu3DMotionShiftSet(var_r30->model[0], var_r30->motion[8], 0.0f, 8.0f, 0);
        if (fn_1_125C0(0, 1) <= 0) {
            var_r31->unk_FC |= 0x80000;
        }
        return 0;
    }
    if (var_r31->unk_FC & 0x200) {
        omVibrate(lbl_1_bss_120, 0xC, 4, 2);
        HuAudCharVoicePlay(var_r31->unk_11C, 0x123);
        var_r31->unk_FC |= 0x100;
        var_r31->unk_00.unk_3C |= 0x210;
        fn_1_2BD0(&var_r31->unk_00, 0.0f, 0.0f);
        if (fn_1_125C0(0, 1) <= 0) {
            var_r31->unk_FC |= 0x80000;
        }
        return 0;
    }
    if (var_r31->unk_FC & 0x2000) {
        omVibrate(lbl_1_bss_120, 0xC, 4, 2);
        HuAudCharVoicePlay(var_r31->unk_11C, 0x123);
        var_r31->unk_F8 = 0.0f;
        var_r31->unk_FC |= 0x1000;
        var_r31->unk_00.unk_3C |= 0x10;
        Hu3DMotionShiftSet(var_r30->model[0], var_r30->motion[15], 0.0f, 8.0f, 0);
        if (fn_1_125C0(0, 1) <= 0) {
            var_r31->unk_FC |= 0x80000;
        }
        return 0;
    }
    if (var_r31->unk_FC & 0x20000) {
        omVibrate(lbl_1_bss_120, 0xC, 4, 2);
        HuAudCharVoicePlay(var_r31->unk_11C, 0x123);
        var_r31->unk_F8 = 0.0f;
        var_r31->unk_FC |= 0x10000;
        var_r31->unk_00.unk_3C |= 0x10;
        if (fn_1_125C0(0, 1) <= 0) {
            var_r31->unk_FC |= 0x80000;
        }
        return 0;
    }
    if ((var_r31->unk_FC & 0x200000) != 0) {
        omVibrate(lbl_1_bss_120, 0xC, 0xC, 0);
        HuAudCharVoicePlay(var_r31->unk_11C, 0x123);
        var_r31->unk_F8 = 0.0f;
        var_r31->unk_FC |= 0x100000;
        var_r31->unk_00.unk_3C |= 0x200;
        var_r31->unk_00.unk_3C &= ~0x10;
        var_f31 = VERSION_NTSC ? 40.15f : 48.180005f;
        if (var_r31->unk_FC & 4) {
            var_f31 = var_f31 / 2;
        }
        fn_1_1C77C(var_r31);
        fn_1_2BD0(&var_r31->unk_00, var_f31, 0.0f);
        Hu3DMotionShiftSet(var_r30->model[0], var_r30->motion[var_r31->unk_114], 0.0f, 8.0f, 0);
        sp3C = 1;
        if ((var_r31->unk_FC & 4) != 0) {
            sp3C = 1;
        }
        if (fn_1_125C0(0, sp3C) <= 0) {
            var_r31->unk_FC |= 0x80000;
        }
        return 0;
    }
    return 1;
}

void fn_1_1E150(omObjData *var_r29)
{
    s32 sp70;
    float var_f20;

    UnkM450Struct5 *var_r31 = var_r29->data;
    UnkData1380Struct *var_r30;

    var_r31->unk_FC |= 1;
    var_r31->unk_FC &= 0xFFFFF7FF;
    fn_1_1C060(var_r31);
    sp70 = 1;
    var_r31->unk_00.unk_20 = 0;
    var_r31->unk_00.unk_24 = 0;
    var_r31->unk_00.unk_28 = 0;
    var_r31->unk_00.unk_2C = 0;
    var_r31->unk_00.unk_30 = 0;
    var_r31->unk_00.unk_34 = 0;
    if (lbl_1_bss_118 == 5) {
        fn_1_19798();
    }
    sp70 = fn_1_1C898(var_r31, var_r29);
    if (sp70 != 0) {
        if (((var_r31->unk_FC & 0x80000) || (lbl_1_bss_304 < 0)) && (var_r31->unk_00.unk_38 == 0)) {
            var_r31->unk_118 = 0x7EB;
            Hu3DModelAttrReset(*var_r29->model, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            Hu3DMotionShiftSet(*var_r29->model, var_r29->motion[22], 0.0f, 8.0f, 0);
            Hu3DModelAttrReset(*var_r29->model, HU3D_ATTR_DISPOFF);
            var_r29->func = fn_1_20170;
            return;
        }
        if (NULL != lbl_1_data_FAC[lbl_1_bss_118]) {
            if (fn_1_1B0C4(lbl_1_data_FAC[lbl_1_bss_118], var_r31) != 0) {
                if (fn_1_1C2D4(var_r31) != 0) {
                    fn_1_1C434(var_r31, var_r29);
                    return;
                }
            }
        }
        var_r31->unk_00.unk_20 = HuPadStkX[var_r31->unk_120];
        var_r31->unk_00.unk_24 = HuPadStkY[var_r31->unk_120];
        var_r31->unk_00.unk_28 = HuPadBtnDown[var_r31->unk_120];
        var_r31->unk_00.unk_2C = HuPadBtn[var_r31->unk_120];
        var_r31->unk_00.unk_30 = HuPadTrigL[var_r31->unk_120];
        var_r31->unk_00.unk_34 = HuPadTrigR[var_r31->unk_120];
        if ((lbl_1_bss_118 >= 2) && (lbl_1_bss_118 <= 4)) {
            var_r31->unk_00.unk_20 = HuPadStkY[var_r31->unk_120];
            var_r31->unk_00.unk_24 = -HuPadStkX[var_r31->unk_120];
        }
        fn_1_40C0(&var_r31->unk_00);
    }
    if ((1490.0f > var_r31->unk_00.unk_6C.y) && (var_r31->unk_00.unk_38 != 1) && (var_r31->unk_00.unk_38 != 3)) {
        omVibrate(lbl_1_bss_120, 0xC, 4, 2);
        HuAudCharVoicePlay(var_r31->unk_11C, 0x123);
        var_r31->unk_FC |= 0x800000;
        var_r31->unk_118 = 0x7EB;
        fn_1_2BD0(&var_r31->unk_00, VERSION_NTSC ? 53.533333f : 64.240005f, 0.0f);
        Hu3DMotionSet(var_r29->model[0], var_r29->motion[8]);
        Hu3DModelAttrReset(var_r29->model[0], HU3D_ATTR_DISPOFF);
        fn_1_125C0(0, 0);
        var_r29->func = fn_1_20170;
        return;
    }
    fn_1_19450(var_r31);

    var_r30 = NULL;
    if (lbl_1_bss_118 == 2) {
        var_r30 = &lbl_1_data_1380;
    }
    if (lbl_1_bss_118 == 4) {
        var_r30 = &lbl_1_data_13B8;
    }
    fn_1_1B158(var_r31, var_r30);
    fn_1_1B2AC(var_r31, var_r30);
    if (NULL != var_r30) {
        if ((var_r31->unk_104 >= 0) && (((var_r30->unk_34[var_r31->unk_104].x) != 0.0f) || (var_r30->unk_34[var_r31->unk_104].z != 0.0f))) {
            VECAdd(&var_r30->unk_34[var_r31->unk_104], &var_r31->unk_00.unk_6C, &var_r31->unk_00.unk_6C);
            var_r31->unk_00.unk_78 = var_r31->unk_00.unk_6C;
        }
        if (var_r30->unk_1C != 0) {
            if (fn_1_1C2D4(var_r31) != 0) {
                fn_1_1C434(var_r31, var_r29);
                return;
            }
        }
    }
    if ((lbl_1_bss_118 == 5) && (lbl_1_data_A0C[1].unk_14 <= 0)) {
        if (fn_1_1C2D4(var_r31) != 0) {
            lbl_1_bss_11C = lbl_1_bss_120;
            fn_1_1C434(var_r31, var_r29);
            fn_1_1F58(0x3E8);
            return;
        }
    }
    fn_1_1B644(var_r31);
    fn_1_1B830(var_r31);
    if (lbl_1_bss_118 < 5) {
        var_f20 = 0.0;
        if ((lbl_1_bss_118 >= 2) && (lbl_1_bss_118 <= 4)) {
            var_f20 = 270.0f;
        }
        fn_1_1A21C(var_f20, 1500.0f);
        fn_1_1710(0.5f, &lbl_1_data_470);
    }
    omSetTra(var_r31->unk_00.unk_00, var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, var_r31->unk_00.unk_6C.z);
    omSetRot(var_r31->unk_00.unk_00, 0.0f, var_r31->unk_00.unk_9C, 0.0f);
    fn_1_1C6E4();
}

void fn_1_200BC(UnkM450Struct5 *arg0, omObjData *object)
{
    arg0->unk_118++;
    arg0->unk_FC &= ~0x802;
    arg0->unk_FC &= ~0x70;
    arg0->unk_FC &= ~0x700;
    arg0->unk_FC &= ~0x7000;
    arg0->unk_FC &= ~0x70000;
    arg0->unk_FC &= ~0x700004;
    fn_1_1B4C8(arg0);
    object->func = fn_1_1E150;
}

void fn_1_20170(omObjData *var_r30)
{
    Vec sp1CC;
    float sp1C8;
    float sp1C4;
    float var_f31;
    float var_f30;

    UnkM450Struct5 *var_r31;
    UnkM450Struct5 *var_r29;
    UnkData94CStruct *var_r28;
    s32 var_r25;

    var_r31 = var_r30->data;
    var_r31->unk_FC &= 0xFFFFFFFE;
    var_r31->unk_00.unk_20 = 0;
    var_r31->unk_00.unk_24 = 0;
    var_r31->unk_00.unk_28 = 0;
    var_r31->unk_00.unk_2C = 0;
    var_r31->unk_00.unk_30 = 0;
    var_r31->unk_00.unk_34 = 0;
    CharModelEffectEnableSet(var_r31->unk_11C, 1);
    lbl_1_bss_10C = 0;
    switch (var_r31->unk_118) {
        case 0x7D0:
            if (lbl_1_bss_1A4->work[0] > 0x3EC) {
                var_r31->unk_118++;
                Hu3DModelShadowSet(var_r30->model[0]);
                if (fn_1_13B90(0) != 0) {
                    var_r31->unk_00.unk_9C = 180.0f;
                    fn_1_4ED8(&var_r31->unk_00, 0);
                }
                else {
                    var_r31->unk_00.unk_9C = 0.0f;
                    fn_1_4ED8(&var_r31->unk_00, 5);
                }
                var_r31->unk_00.unk_3C |= 0x20;
            }
            break;
        case 0x7D1:
            fn_1_40C0(&var_r31->unk_00);
            if (var_r31->unk_00.unk_38 == 2) {
                var_r31->unk_118++;
                var_r31->unk_F0 = 0;
                var_r31->unk_F4 = -1;
                var_r31->unk_C4 = lbl_1_data_94C;
                var_r31->unk_EC = 360.0f;
                omVibrate(lbl_1_bss_120, 0xC, 0xC, 0);
                if (fn_1_13B90(0) != 0) {
                    var_r31->unk_118 = 0x7D4;
                    var_r31->unk_E8 = 0.0f;
                    fn_1_4ED8(&var_r31->unk_00, 0);
                }
                var_r31->unk_00.unk_3C &= ~0x20;
            }
            break;
        case 0x7D2:
        case 0x7DA:
            if (var_r31->unk_EC != 360.0f) {
                var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, var_r31->unk_EC, 0.05f);
            }
            if (var_r31->unk_F4 < 0) {
                var_r31->unk_F4 = var_r31->unk_F0;
                var_r31->unk_F0++;
                var_r28 = &var_r31->unk_C4[var_r31->unk_F4];
                if (var_r28->unk_08 == 0.0f) {
                    Hu3DMotionSet(var_r30->model[0], var_r30->motion[var_r28->unk_00]);
                    Hu3DMotionTimeSet(var_r30->model[0], var_r28->unk_0C);
                }
                else {
                    Hu3DMotionShiftSet(
                        var_r30->model[0], var_r30->motion[var_r28->unk_00], var_r28->unk_0C, var_r28->unk_08, var_r28->unk_10 & 0xBFFFFFFD);
                }
                Hu3DMotionSpeedSet(var_r30->model[0], var_r28->unk_04);
                Hu3DMotionShiftSpeedSet(var_r30->model[0], var_r28->unk_04);
                if (var_r28->unk_10 & 0x40000003) {
                    var_r31->unk_118++;
                    Hu3DMotionSpeedSet(var_r30->model[0], 1.0f);
                    Hu3DMotionShiftSpeedSet(var_r30->model[0], 1.0f);
                }
            }
            else if ((Hu3DMotionShiftIDGet(var_r30->model[0]) < 0) && (Hu3DMotionEndCheck(var_r30->model[0]) != 0)) {
                var_r31->unk_F4 = -1;
                if (var_r31->unk_C4[var_r31->unk_F0].unk_00 < 0) {
                    var_r31->unk_118++;
                    Hu3DMotionSpeedSet(var_r30->model[0], 1.0f);
                    Hu3DMotionShiftSpeedSet(var_r30->model[0], 1.0f);
                }
            }
            break;
        case 0x7D3:
            if (Hu3DMotionShiftIDGet(var_r30->model[0]) < 0) {
                sp1C4 = Hu3DMotionTimeGet(var_r30->model[0]) / Hu3DMotionMaxTimeGet(var_r30->model[0]);
                if (0.5f > sp1C4) {
                    sp1C4 = 0.5f;
                }
                var_r31->unk_00.unk_9C = 180.0f * (2.0f * (sp1C4 - 0.5f));
                if (Hu3DMotionEndCheck(var_r30->model[0]) != 0) {
                    var_r31->unk_118++;
                    var_r31->unk_E8 = 0.0f;
                    fn_1_4ED8(&var_r31->unk_00, 0);
                    Hu3DMotionShiftSet(var_r30->model[0], var_r30->motion[0], 0.0f, 8.0f, 0x40000001);
                }
            }
            break;
        case 0x7D4:
            if ((lbl_1_bss_1A4->work[0] >= 0x3EF) && (120.0f < lbl_1_bss_128)) {
                var_r31->unk_118++;
            }
            break;
        case 0x7D5:
            if (90.0f > var_r31->unk_E8) {
                fn_1_1A940(var_r31, lbl_1_bss_4C, 0x7A);
            }
            else {
                if (lbl_1_bss_1A4->work[0] < 0x3F0) {
                    lbl_1_bss_1A4->work[0] = 0x3F0;
                    lbl_1_bss_128 = 0.0f;
                    lbl_1_bss_324 = lbl_1_data_4B8;
                    lbl_1_bss_30C = lbl_1_data_4C4;
                }
                if ((lbl_1_bss_4C->z - 100.0f) < var_r31->unk_00.unk_6C.z) {
                    var_r31->unk_00.unk_24 = 0x48;
                    fn_1_40C0(&var_r31->unk_00);
                }
                else {
                    var_r31->unk_118++;
                    fn_1_4ED8(&var_r31->unk_00, 0);
                }
            }
            break;
        case 0x7D6:
            if (lbl_1_bss_1A4->work[0] >= 0x3F3) {
                fn_1_200BC(var_r31, var_r30);
            }
            break;
        case 0x7D8:
            var_r31->unk_D0.x = 1200.0f;
            var_r31->unk_D0.z = 0.0f;
            if (fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D0) != 0) {
                if (lbl_1_bss_1A4->work[0] >= 0x3F5) {
                    var_r31->unk_118++;
                    var_r31->unk_E8 = 0.0f;
                    var_r31->unk_00.unk_6C.z = 0.0f;
                }
                else {
                    var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 90.0f, 0.4f);
                    var_r31->unk_00.unk_6C.z = 0.0f;
                }
            }
            fn_1_40C0(&var_r31->unk_00);
            break;
        case 0x7D9:
            if (90.0f > var_r31->unk_E8) {
                fn_1_1A940(var_r31, &lbl_1_bss_4C[1], 0x78);
            }
            else {
                if ((-1000.0f < var_r31->unk_00.unk_6C.x) && (lbl_1_bss_1A4->work[0] < 0x3F6)) {
                    lbl_1_bss_1A4->work[0] = 0x3F6;
                    lbl_1_bss_128 = 0.0f;
                }
                if (lbl_1_bss_1A4->work[0] >= 0x3F7) {
                    var_r31->unk_118 = 0x7DB;
                    fn_1_4ED8(&var_r31->unk_00, 0);
                }
                if (lbl_1_data_1380.unk_24[2] >= 0) {
                    var_r31->unk_D0 = lbl_1_data_1380.unk_30[2];
                }
                else {
                    var_r31->unk_D0 = lbl_1_data_1380.unk_30[3];
                }
                var_r31->unk_D0.z *= 0.5f;
                fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D0);
                fn_1_40C0(&var_r31->unk_00);
            }
            break;
        case 0x7DB:
            if ((lbl_1_bss_1A4->work[0] <= 0x3F9) && (Hu3DMotionShiftIDGet(var_r30->model[0]) < 0) && (lbl_1_bss_D8 > 0)) {
                VECScale(&lbl_1_bss_CC, &lbl_1_bss_CC, 1.0f / lbl_1_bss_D8);
                fn_1_160AC(var_r31, var_r30, &lbl_1_bss_CC);
            }
            if (lbl_1_bss_1A4->work[0] >= 0x3FA) {
                fn_1_160AC(var_r31, var_r30, NULL);
            }
            if (lbl_1_bss_1A4->work[0] >= 0x3FB) {
                fn_1_16280(var_r31, var_r30);
                fn_1_200BC(var_r31, var_r30);
            }
            break;
        case 0x7DD:
            var_r31->unk_D0.x = 300.0f;
            var_r31->unk_D0.z = 0.0f;
            if (lbl_1_bss_1A4->work[0] >= 0x3FD) {
                if (fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D0) != 0) {
                    var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 90.0f, 0.4f);
                    if (lbl_1_bss_1A4->work[0] <= 0x3FD) {
                        lbl_1_bss_1A4->work[0] += 1;
                        lbl_1_bss_128 = 0.0f;
                    }
                    if (lbl_1_bss_1A4->work[0] >= 0x402) {
                        var_r31->unk_118++;
                        var_r31->unk_E8 = 0.0f;
                    }
                }
                fn_1_40C0(&var_r31->unk_00);
            }
            break;
        case 0x7DE:
            if (90.0f > var_r31->unk_E8) {
                fn_1_1A940(var_r31, &lbl_1_bss_4C[2], 0x78);
            }
            else if ((100.0f + lbl_1_bss_4C[2].x) > var_r31->unk_00.unk_6C.x) {
                var_r31->unk_00.unk_20 = 0x48;
                fn_1_40C0(&var_r31->unk_00);
            }
            else {
                var_r31->unk_118++;
                fn_1_4ED8(&var_r31->unk_00, 0);
                lbl_1_bss_1A4->work[0] = 0x403;
                lbl_1_bss_128 = 0.0f;
            }
            break;
        case 0x7DF:
            if (lbl_1_bss_1A4->work[0] >= 0x405) {
                fn_1_200BC(var_r31, var_r30);
            }
            break;
        case 0x7E1:
            var_r31->unk_D0.x = 1200.0f;
            var_r31->unk_D0.z = 0.0f;
            if (fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D0) != 0) {
                if (lbl_1_bss_1A4->work[0] >= 0x407) {
                    var_r31->unk_118++;
                    var_r31->unk_E8 = 0.0f;
                    var_r31->unk_00.unk_6C.z = 0.0f;
                }
                else {
                    var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 90.0f, 0.4f);
                    var_r31->unk_00.unk_6C.z = 0.0f;
                }
            }
            fn_1_40C0(&var_r31->unk_00);
            break;
        case 0x7E2:
            if (90.0f > var_r31->unk_E8) {
                fn_1_1A940(var_r31, &lbl_1_bss_4C[3], 0x78);
            }
            else {
                if ((-1000.0f < var_r31->unk_00.unk_6C.x) && (lbl_1_bss_1A4->work[0] < 0x408)) {
                    lbl_1_bss_1A4->work[0] = 0x408;
                    lbl_1_bss_128 = 0.0f;
                }
                if (lbl_1_bss_1A4->work[0] >= 0x409) {
                    var_r31->unk_118++;
                }
                var_r31->unk_D0 = lbl_1_data_13B8.unk_30[7];

                fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D0);
                fn_1_40C0(&var_r31->unk_00);
            }
            break;
        case 0x7E3:
            if (lbl_1_bss_1A4->work[0] >= 0x40D) {
                fn_1_200BC(var_r31, var_r30);
            }
            break;
        case 0x7E5:
            var_r31->unk_D0.x = 0.0f;
            var_r31->unk_D0.z = -400.0f;
            if (lbl_1_bss_1A4->work[0] >= 0x410) {
                if (fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D0) != 0) {
                    var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 180.0f, 0.4f);
                    if ((lbl_1_bss_1A4->work[0] <= 0x410) && (120.0f <= lbl_1_bss_128)) {
                        lbl_1_bss_1A4->work[0] += 1;
                        lbl_1_bss_128 = 0.0f;
                        var_r31->unk_118++;
                        var_r31->unk_E8 = 0.0f;

                        fn_1_139B0(&lbl_1_data_13B8, 0x10);
                        fn_1_1F58(0x3E8);
                    }
                }
                fn_1_40C0(&var_r31->unk_00);
            }
            break;
        case 0x7E6:
            if (90.0f > var_r31->unk_E8) {
                fn_1_1A940(var_r31, &lbl_1_bss_4C[4], 0x7A);
            }
            else {
                if (lbl_1_bss_1A4->work[0] <= 0x411) {
                    lbl_1_bss_1A4->work[0] = 0x412;
                    lbl_1_bss_128 = 0.0f;
                    fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
                    lbl_1_bss_324 = lbl_1_data_4D0;
                    lbl_1_bss_30C = lbl_1_data_4DC;
                }
                var_r31->unk_D0.x = 0.0f;
                var_r31->unk_D0.z = 600.0f;
                if (fn_1_19A10(&var_r31->unk_00, &var_r31->unk_D0) != 0) {
                    ++var_r31->unk_118;
                    fn_1_4ED8(&var_r31->unk_00, 0);
                }
                else {
                    fn_1_40C0(&var_r31->unk_00);
                }
            }
            break;
        case 0x7E7:
            var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 180.0f, 0.4f);
            if (lbl_1_bss_1A4->work[0] >= 0x415) {
                fn_1_200BC(var_r31, var_r30);
            }
            break;
        case 0x7E9:
            if (lbl_1_bss_1A4->work[0] >= 0x417) {
                if ((VERSION_NTSC ? 100.0f : 80.0f) < lbl_1_bss_128) {
                    var_r31->unk_118++;
                    GWPlayerCoinWinSet(lbl_1_bss_120, 10);
                    Hu3DMotionShiftSet(var_r30->model[0], var_r30->motion[21], 0.0f, 8.0f, 0);
                    lbl_1_bss_18 = HuAudSStreamPlay(0xD);
                }
            }
            if ((lbl_1_bss_1A4->work[0] == 0x416) && (240.0f < lbl_1_bss_128)) {
                lbl_1_bss_1A4->work[0] += 1;
                lbl_1_bss_128 = 0.0f;
            }
            break;
        case 0x7EA:
            VECSubtract(&((UnkM450Struct3 *)lbl_1_bss_134->data)->unk_00.unk_6C, &var_r31->unk_00.unk_6C, &sp1CC);
            var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 180.0 + (atan2d(sp1CC.x, sp1CC.z)), 0.4f);
            break;
        case 0x7EB:
            if (var_r31->unk_FC & 0x800000) {
                var_r29 = var_r31;
                var_r29->unk_00.unk_84.y += -146.0f / REFRESH_RATE;
                var_r29->unk_00.unk_6C.y += var_r29->unk_00.unk_84.y;
                var_r29->unk_00.unk_A8 = MapPos(
                    var_r29->unk_00.unk_6C.x, var_r29->unk_00.unk_6C.y, var_r29->unk_00.unk_6C.z, var_r29->unk_00.unk_C0, &var_r29->unk_00.unk_AC);
                if (var_r29->unk_00.unk_A8 > var_r29->unk_00.unk_6C.y) {
                    fn_1_2BD0(&var_r31->unk_00, VERSION_NTSC ? 53.533333f : 64.240005f, 0.0f);
                }
                var_f31 = var_r29->unk_00.unk_6C.x;
                var_f30 = var_r29->unk_00.unk_6C.z;
                sp1C8 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
                if (sp1C8 == 0.0f) {
                    var_f31 = 0.0f;
                    var_f30 = -1.0f;
                }
                else {
                    var_f31 /= sp1C8;
                    var_f30 /= sp1C8;
                }
                var_r29->unk_00.unk_84.x = 72.0f * var_f31 / 4;
                var_r29->unk_00.unk_84.z = 72.0f * var_f30 / 4;
                var_r29->unk_00.unk_6C.x += var_r29->unk_00.unk_84.x;
                var_r29->unk_00.unk_6C.z += var_r29->unk_00.unk_84.z;
                var_r29->unk_00.unk_9C = fn_1_1E20(var_r29->unk_00.unk_9C, atan2d(var_r29->unk_00.unk_84.x, var_r29->unk_00.unk_84.z), 0.4f);
            }
            break;
        default:
            OSReport("*** player mode error(%d)!!\n", var_r31->unk_118);
            break;
    }
    if ((var_r31->unk_118 >= 0x7E9) && (var_r31->unk_118 <= 0x7EA)) {
        fn_1_1C060(var_r31);
    }
    if (1495.0f > var_r31->unk_00.unk_6C.y) {
        for (var_r25 = 0; var_r25 < 1; var_r25++) {
            Hu3DModelShadowDispOff(var_r30->model[var_r25]);
        }
    }
    else {
        for (var_r25 = 0; var_r25 < 1; var_r25++) {
            Hu3DModelShadowDispOn(var_r30->model[var_r25]);
        }
    }
    omSetTra(var_r31->unk_00.unk_00, var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, var_r31->unk_00.unk_6C.z);
    omSetRot(var_r31->unk_00.unk_00, 0.0f, var_r31->unk_00.unk_9C, 0.0f);
}

void fn_1_23330(omObjData *object)
{
    Vec sp8;
    UnkM450Struct5 *var_r31;
    s32 var_r29;
    s32 var_r27;
    s32 var_r26;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM450Struct5), MEMORY_DEFAULT_NUM);
    var_r31 = object->data;
    var_r31->unk_FC = 0;
    var_r31->unk_11C = GWPlayerCfg[lbl_1_bss_120].character;
    var_r31->unk_120 = GWPlayerCfg[lbl_1_bss_120].pad_idx;
    var_r31->unk_118 = 0x7D0;
    var_r31->unk_C8 = 0.0f;
    var_r31->unk_CC = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 4000.0f;
    sp8.z = 0.0f;
    var_r26 = var_r31->unk_11C;
    var_r27 = lbl_1_bss_120;
    fn_1_2C1C(&var_r31->unk_00, object, var_r27, var_r26, lbl_1_data_92C, 0, &sp8, 0.0f);
    var_r31->unk_00.unk_04 = fn_1_19C18;
    var_r31->unk_00.unk_0C = fn_1_19CE0;
    var_r31->unk_00.unk_10 = fn_1_1A014;
    object->model[0] = CharModelCreate(lbl_1_data_0[var_r31->unk_11C], 2);
    CharModelStepTypeSet(lbl_1_data_0[var_r31->unk_11C], 0);
    for (var_r29 = 0; var_r29 < 0x17; var_r29++) {
        object->motion[var_r29] = CharModelMotionCreate(lbl_1_data_0[var_r31->unk_11C], lbl_1_data_64C[var_r31->unk_11C][var_r29]);
        CharModelMotionSet(lbl_1_data_0[var_r31->unk_11C], object->motion[var_r29]);
    }
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->model[0], 2);
    Hu3DMotionSet(object->model[0], *object->motion);
    omSetTra(var_r31->unk_00.unk_00, var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, var_r31->unk_00.unk_6C.z);
    omSetRot(var_r31->unk_00.unk_00, 0.0f, var_r31->unk_00.unk_9C, 0.0f);
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    CharModelLayerSetAll2(6);
    CharModelMotionDataClose(lbl_1_data_0[var_r31->unk_11C]);
    object->func = fn_1_20170;
}

void fn_1_23770(omObjData *object, s32 arg1)
{
    lbl_1_bss_108 = 1;
    lbl_1_bss_128 += 1.0f;
    if ((fn_1_13DC(lbl_1_bss_128 / 120.0f, &lbl_1_data_470) != 0) && (MGSeqStatGet(lbl_1_bss_2FE) == 0)) {
        lbl_1_bss_2FE = -1;
        object->work[0] += 1;
        fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
        fn_1_12540(0);
        if (lbl_1_bss_118 == 5) {
            fn_1_12540(1);
        }
    }
    if ((arg1 >= 0) && (lbl_1_bss_2F8 < 0) && ((MGSeqStatGet(lbl_1_bss_2FE) & 0x10) != 0)) {
        fn_1_1F24(arg1);
    }
}

void fn_1_23CA0(omObjData *arg0, float arg8, float arg9)
{
    lbl_1_bss_108 = 0;
    lbl_1_bss_110 = 0;
    if (lbl_1_bss_2FE < 0) {
        nMap = 0;
        fn_1_14C28();
        MGSeqParamSet(lbl_1_bss_2FC, 2, -1);
        lbl_1_bss_128 = 0.0f;
        lbl_1_bss_2FC = -1;
        lbl_1_bss_2FE = MGSeqCreate(3, 1);
        return;
    }
    lbl_1_bss_128 += 1.0f;
    if (lbl_1_bss_118 < 5) {
        fn_1_1A21C(arg8, 1500.0f);
    }
    else {
        fn_1_1A3F0();
    }
    fn_1_13DC(lbl_1_bss_128 / arg9, &lbl_1_data_470);

    if ((arg9 < lbl_1_bss_128) && (MGSeqStatGet(lbl_1_bss_2FE) == 0)) {
        arg0->work[0] += 1;
        lbl_1_bss_128 = 0.0f;
        lbl_1_bss_124 = 0.0f;
        lbl_1_bss_2FE = -1;
        fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
    }
}

void fn_1_24620(omObjData *var_r31)
{
    Vec sp280;
    s32 sp120;
    s32 sp11C;
    CameraData *sp118;
    float var_f31;
    UnkData1380Struct *var_r30;

    if (omSysExitReq != 0) {
        fn_1_1F58(0x64);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        var_r31->func = fn_1_298EC;
    }
    lbl_1_bss_308++;
    switch (var_r31->work[0]) {
        case 0x3E8:
            if (lbl_1_bss_2FE < 0) {
                fn_1_1F58(0x64);
                MGSeqParamSet(lbl_1_bss_2FC, 2, -1);
                lbl_1_bss_2FC = -1;
                lbl_1_bss_2FE = MGSeqCreate(3, 1);
                lbl_1_bss_1C = -1;
            }
            else {
                lbl_1_bss_128 += 1.0f;
                sp11C = 0;
                if (lbl_1_bss_1C < 0) {
                    if (120.0f < lbl_1_bss_128) {
                        lbl_1_bss_1C = HuAudSStreamPlay(3);
                    }
                }
                else if (HuAudSStreamStatGet(lbl_1_bss_1C) == 0) {
                    sp11C = 1;
                }
                if ((sp11C != 0) || (1200.0f < lbl_1_bss_128)) {
                    fn_1_1F58(0x64);
                    lbl_1_bss_2FE = -1;
                    WipeColorSet(0, 0, 0);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                    var_r31->func = fn_1_298EC;
                }
            }
            break;
        case 0x3E9:
            lbl_1_bss_128 += 1.0f;
            if (60.0f < lbl_1_bss_128) {
                var_r31->work[0] += 1;
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                HuAudFXPlay(0x7B2);
            }
            break;
        case 0x3EA:
            if (WipeStatGet() == 0) {
                var_r31->work[0] += 1;
                lbl_1_bss_128 = 0.0f;
            }
            break;
        case 0x3EB:
            lbl_1_bss_128 += 1.0f;
            if (120.0f < lbl_1_bss_128) {
                var_r31->work[0] += 1;
                lbl_1_bss_128 = 0.0f;
                lbl_1_bss_324 = lbl_1_data_488;
                lbl_1_bss_30C = lbl_1_data_494;
                fn_1_1F24(0x41);
            }
            break;
        case 0x3EC:
            lbl_1_bss_128 += 1.0f;
            if (fn_1_13DC(lbl_1_bss_128 / 120.0f, &lbl_1_data_470) != 0) {
                var_r31->work[0] += 1;
                lbl_1_bss_128 = 0;
                fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
                lbl_1_bss_324 = lbl_1_data_4A0;
                lbl_1_bss_30C = lbl_1_data_4AC;
            }
            break;
        case 0x3ED:
            if (((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_118 >= 0x7D3) {
                lbl_1_bss_128 += 1.0f;
                if (fn_1_13DC(lbl_1_bss_128 / 120.0f, &lbl_1_data_470) != 0) {
                    var_r31->work[0] += 1;
                    fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
                    fn_1_6CB0(fn_1_8500, 0);
                }
            }
            break;
        case 0x3EE:
        case 0x3F1:
        case 0x3F8:
        case 0x401:
        case 0x40A:
        case 0x413:
            if (lbl_1_bss_10 == 0) {
                var_r31->work[0] += 1;
                lbl_1_bss_128 = 0.0f;
            }
            break;
        case 0x3EF:
            lbl_1_bss_128 += 1.0f;
            if (120.0f < lbl_1_bss_128) {
                fn_1_1A060();
                fn_1_1710((lbl_1_bss_128 - 120.0f) / 240.0f, &lbl_1_data_470);
            }
            break;
        case 0x3F0:
            lbl_1_bss_128 += 1.0f;
            if (fn_1_13DC(lbl_1_bss_128 / 120.0f, &lbl_1_data_470) != 0) {
                var_r31->work[0] += 1;
                fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
                fn_1_6CB0(fn_1_8BDC, 1);
            }
            if (fn_1_13B90(1) != 0) {
                fn_1_1F58(0x3E8);
            }
            break;
        case 0x3F2:
            if (lbl_1_bss_2FE < 0) {
                lbl_1_bss_128 = 0.0f;
                lbl_1_bss_2FE = MGSeqCreate(3, 0);
                fn_1_14BC8(&lbl_1_data_A80[0], 9);
                fn_1_13BC4(1);
                fn_1_1A060();
            }
            else {
                fn_1_23770(var_r31, 0x40);
            }
            break;
        case 0x3F3:
        case 0x3FB:
        case 0x405:
        case 0x40D:
        case 0x415:
            if (lbl_1_bss_2FC >= 0) {
                MGSeqParamSet(lbl_1_bss_2FC, 1, (lbl_1_bss_304 + REFRESH_RATE - 1) / REFRESH_RATE);
            }
            else {
                sp120 = 0;
                if ((lbl_1_bss_118 == 2) || (lbl_1_bss_118 == 4) || (lbl_1_bss_118 == 5)) {
                    if (lbl_1_bss_304 < 30 * REFRESH_RATE) {
                        sp120 = 1;
                    }
                }
                else {
                    sp120 = 1;
                }
                if (sp120 != 0) {
                    lbl_1_bss_2FC = MGSeqCreate(1, lbl_1_bss_304 / REFRESH_RATE, -1, -1);
                }
            }
            lbl_1_bss_304--;
            if (((UnkM450Struct5 *)lbl_1_bss_138->data)->unk_118 >= 0x7EB) {
                var_r31->work[0] = 0x3E8;
                lbl_1_bss_128 = 0.0f;
            }
            break;
        case 0x3F4:
            fn_1_23CA0(var_r31, 270.0f, 2 * REFRESH_RATE);
            break;
        case 0x3F5:
            lbl_1_bss_128 += 1.0f;
            fn_1_1A21C(270.0f, 0.0f);
            fn_1_13DC(1.0f, &lbl_1_data_470);
            break;
        case 0x3F6:
            lbl_1_bss_128 += 1.0f;
            if (90.0f < lbl_1_bss_128) {
                var_r31->work[0] += 1;
                lbl_1_bss_128 = 0.0f;
            }
            fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
            lbl_1_bss_20 = -1;
            break;
        case 0x3F7:
            if (lbl_1_bss_20 < 0) {
                lbl_1_bss_20 = HuAudFXPlay(0x7B1);
            }
            omVibrate(lbl_1_bss_120, 0xC, 6, 6);
            lbl_1_bss_128 += 1.0f;
            Hu3DModelPosSet(lbl_1_bss_1A0->model[6], 0.0f, -(2.0f * lbl_1_bss_128), 0.0f);
            if (2 * REFRESH_RATE < lbl_1_bss_128) {
                var_r31->work[0] += 1;
                fn_1_6CB0(fn_1_9074, 2);
                HuAudFXPlay(0x7BB);
            }
            break;
        case 0x3F9:
            break;
        case 0x3FA:
            if (lbl_1_bss_2FE < 0) {
                lbl_1_bss_128 = 0.0f;
                lbl_1_bss_2FE = MGSeqCreate(3, 0);
                fn_1_13BC4(2);
                fn_1_1A21C(270.0f, 0.0f);
            }
            else {
                fn_1_23770(var_r31, -1);
            }
            break;
        case 0x3FC:
            var_f31 = lbl_1_bss_128 / (2 * REFRESH_RATE);
            if (1.0f < var_f31) {
                var_f31 = 1.0f;
            }
            var_r30 = &lbl_1_data_1380;
            Hu3DModelAttrReset(lbl_1_bss_1A0->model[5], HU3D_ATTR_DISPOFF);
            Hu3DModelRotSet(lbl_1_bss_1A0->model[5], 0.0f, 90.0f, 0.0f);
            Hu3DModelPosSet(lbl_1_bss_1A0->model[5], var_r30->unk_30[3].x, var_r30->unk_30[3].y, var_r30->unk_30[3].z);
            Hu3DModelTPLvlSet(lbl_1_bss_1A0->model[5], var_f31);
            fn_1_23CA0(var_r31, 270.0f, 2 * REFRESH_RATE);
            break;
        case 0x3FD:
        case 0x3FE:
        case 0x3FF:
            lbl_1_bss_124 += 1.0f;
            fn_1_1A21C(270.0f, 0.0f);
            fn_1_1710(lbl_1_bss_124 / 120.0f, &lbl_1_data_470);
            lbl_1_bss_20 = -1;
            break;
        case 0x400:
            lbl_1_bss_124 += 1.0f;
            fn_1_1A21C(270.0f, 0.0f);
            fn_1_1710(lbl_1_bss_124 / 120.0f, &lbl_1_data_470);
            if (lbl_1_bss_20 < 0) {
                lbl_1_bss_20 = HuAudFXPlay(0x7B1);
            }
            omVibrate(lbl_1_bss_120, 0xC, 6, 6);
            lbl_1_bss_128 += 1.0f;
            Hu3DModelAttrReset(lbl_1_bss_1A0->model[7], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(lbl_1_bss_1A0->model[7], 0.0f, -(60.0f - (lbl_1_bss_128 / 2)), 0.0f);
            if (120.0f < lbl_1_bss_128) {
                var_r31->work[0] += 1;
                lbl_1_bss_128 = 0;
                fn_1_6CB0(fn_1_96C0, -1);
                fn_1_139B0(&lbl_1_data_1380, 5);
                fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
                HuAudFXPlay(0x7BB);
            }
            break;
        case 0x402:
            lbl_1_bss_128 += 1.0f;
            fn_1_1A21C(270.0f, 0.0f);
            fn_1_13DC(1.0f, &lbl_1_data_470);
            break;
        case 0x403:
            fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
            break;
        case 0x404:
            if (lbl_1_bss_2FE < 0) {
                lbl_1_bss_128 = 0.0f;
                lbl_1_bss_2FE = MGSeqCreate(3, 0);
                fn_1_14BC8(&lbl_1_data_C58[0], 10);
                fn_1_13BC4(3);
                fn_1_1A21C(270.0f, 0.0f);
            }
            else {
                fn_1_23770(var_r31, -1);
            }
            break;
        case 0x406:
            fn_1_23CA0(var_r31, 270.0f, 2 * REFRESH_RATE);
            break;
        case 0x407:
            lbl_1_bss_128 += 1.0f;
            fn_1_1A21C(270.0f, 0.0f);
            fn_1_13DC(1.0f, &lbl_1_data_470);
            break;
        case 0x408:
            lbl_1_bss_128 += 1.0f;
            if (90.0f < lbl_1_bss_128) {
                var_r31->work[0] += 1;
                lbl_1_bss_128 = 0.0f;
            }
            fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
            lbl_1_bss_20 = -1;
            break;
        case 0x409:
            if (lbl_1_bss_20 < 0) {
                lbl_1_bss_20 = HuAudFXPlay(0x7B1);
            }
            omVibrate(lbl_1_bss_120, 0xC, 6, 6);
            lbl_1_bss_128 += 1.0f;
            Hu3DModelPosSet(lbl_1_bss_1A0->model[17], 0.0f, -(2.0f * lbl_1_bss_128), 0.0f);
            if (2 * REFRESH_RATE < lbl_1_bss_128) {
                var_r31->work[0] += 1;
                fn_1_6CB0(fn_1_9824, 4);
                HuAudFXPlay(0x7BB);
            }
            break;
        case 0x40B:
            break;
        case 0x40C:
            if (lbl_1_bss_2FE < 0) {
                lbl_1_bss_128 = 0.0f;
                lbl_1_bss_2FE = MGSeqCreate(3, 0);
                fn_1_13BC4(4);
                fn_1_1A21C(270.0f, 0.0f);
            }
            else {
                fn_1_23770(var_r31, -1);
            }
            break;
        case 0x40E:
            var_f31 = lbl_1_bss_128 / (2 * REFRESH_RATE);
            if (1.0f < var_f31) {
                var_f31 = 1.0f;
            }
            var_r30 = &lbl_1_data_13B8;
            Hu3DModelAttrReset(lbl_1_bss_1A0->model[16], HU3D_ATTR_DISPOFF);
            Hu3DModelRotSet(lbl_1_bss_1A0->model[16], 0.0f, -90.0f, 0.0f);
            Hu3DModelPosSet(lbl_1_bss_1A0->model[16], var_r30->unk_30[8].x, var_r30->unk_30[8].y, var_r30->unk_30[8].z);
            Hu3DModelTPLvlSet(lbl_1_bss_1A0->model[16], var_f31);
            fn_1_23CA0(var_r31, 270.0f, 2 * REFRESH_RATE);
            break;
        case 0x40F:
            lbl_1_bss_20 = -1;
            break;
        case 0x410:
            if (lbl_1_bss_20 < 0) {
                lbl_1_bss_20 = HuAudFXPlay(0x7B1);
            }
            omVibrate(lbl_1_bss_120, 0xC, 6, 6);
            lbl_1_bss_128 += 1.0f;
            if (120.0f <= lbl_1_bss_128) {
                lbl_1_bss_128 = 120.0f;
            }
            Hu3DModelAttrReset(lbl_1_bss_1A0->model[18], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(lbl_1_bss_1A0->model[18], 0.0f, -(60.0f - (lbl_1_bss_128 / 2)), 0.0f);
            fn_1_1A21C(0.0f, 0.0f);
            fn_1_1710(lbl_1_bss_128 / 120.0f, &lbl_1_data_470);
            break;
        case 0x411:
            if (lbl_1_bss_20 >= 0) {
                lbl_1_bss_20 = -1;
                HuAudFXPlay(0x7BB);
            }
            lbl_1_bss_128 += 1.0f;
            fn_1_1A060();
            fn_1_13DC(1.0f, &lbl_1_data_470);
            break;
        case 0x412:
            lbl_1_bss_128 += 1.0f;
            if (fn_1_13DC(lbl_1_bss_128 / 120.0f, &lbl_1_data_470) != 0) {
                var_r31->work[0] += 1;
                fn_1_1350(&lbl_1_bss_324, &lbl_1_data_470, &lbl_1_bss_30C);
                fn_1_6CB0(fn_1_9BA4, 5);
                Hu3DModelAttrSet(lbl_1_bss_1A0->model[19], HU3D_ATTR_DISPOFF);
            }
            break;
        case 0x414:
            if (lbl_1_bss_2FE < 0) {
                lbl_1_bss_128 = 0.0f;
                lbl_1_bss_2FE = MGSeqCreate(3, 0);
                fn_1_13BC4(5);
                fn_1_1A21C(0.0f, 2000.0f);
                fn_1_1F24(0x42);
            }
            else {
                fn_1_23770(var_r31, -1);
            }
            break;
        case 0x416:
            lbl_1_bss_128 += 1.0f;
            break;
        case 0x417:
            fn_1_23CA0(var_r31, 0.0f, 2 * REFRESH_RATE);
            break;
        case 0x418:
            lbl_1_bss_128 += 1.0f;
            sp11C = 0;
            if (HuAudSStreamStatGet(lbl_1_bss_18) == 0) {
                sp11C = 1;
            }
            if ((sp11C != 0) || (1200.0f < lbl_1_bss_128)) {
                fn_1_1F58(0x64);
                lbl_1_bss_2FE = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                var_r31->func = fn_1_298EC;
            }
            break;
        default:
            OSReport("*** main mode error(%d)!!\n", var_r31->work[0]);
            break;
    }

    sp118 = Hu3DCamera;
    VECSubtract(&sp118->target, &sp118->pos, &sp280);
    VECNormalize(&sp280, &sp280);
    HuAudFXListnerUpdate(&sp118->pos, &sp280);
    lbl_1_bss_D8 = 0;
    lbl_1_bss_CC.x = 0.0f;
    lbl_1_bss_CC.y = 0.0f;
    lbl_1_bss_CC.z = 0.0f;
}

void ObjectSetup(void)
{
    Vec sp14;
    Vec sp8;
    s32 var_r31;
    s32 var_r29;
    omObjData *var_r28;
    s32 var_r27;

    OSReport("******* M450 ObjectSetup *********\n");
    lbl_1_bss_33C = omInitObjMan(0x3E8, 0x2000);
    omGameSysInit(lbl_1_bss_33C);
    nMap = 0;
    nChar = 0;
    lbl_1_bss_120 = 0;
    lbl_1_bss_11C = -1;
    lbl_1_bss_118 = 0;
    lbl_1_bss_110 = 0;
    lbl_1_bss_10C = 0;
    lbl_1_bss_108 = 0;
    lbl_1_bss_308 = 0;
    lbl_1_bss_2FE = -1;
    lbl_1_bss_2FC = -1;
    lbl_1_bss_2F8 = -1;
    lbl_1_bss_1C = -1;
    lbl_1_bss_18 = -1;
    lbl_1_bss_D8 = 0;
    lbl_1_bss_F8 = -1;
    lbl_1_bss_FC = NULL;
    lbl_1_bss_C4 = -1;
    fn_1_1C6E4();
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 30000.0f, 1.2f);
    fn_1_1350(&lbl_1_data_464, &lbl_1_data_470, &lbl_1_data_47C);
    VECSubtract(&lbl_1_data_47C, &lbl_1_data_464, &sp8);
    VECNormalize(&sp8, &sp8);
    HuAudFXListnerSetEX(&lbl_1_data_464, &sp8, 5800.0, 1000.0, 100.0, 300.0, 300.0);
    var_r27 = Hu3DGLightCreateV(&lbl_1_data_4E8, &lbl_1_data_4F4, &lbl_1_data_500);
    Hu3DGLightStaticSet(var_r27, 1);
    Hu3DGLightInfinitytSet(var_r27);
    Hu3DShadowCreate(30.0f, 20.0f, 30000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    VECNormalize(&lbl_1_data_504, &sp14);
    Hu3DShadowPosSet(&lbl_1_data_504, &sp14, &lbl_1_data_510);
    fn_1_6C68(lbl_1_bss_120);
    lbl_1_bss_14 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M450, 0x63), 0x10000000));
    HuSprAnimLock(lbl_1_bss_14);
    fn_1_12234();
    for (var_r29 = 0; var_r29 < 0x20; var_r29++) {
        lbl_1_bss_1B0[var_r29].unk00 = 0;
        lbl_1_bss_1B0[var_r29].unk04 = -1;
    }
    lbl_1_bss_1A0 = omAddObjEx(lbl_1_bss_33C, 0x64, 0x21, 0, -1, fn_1_15308);
    for (var_r31 = 0; var_r31 < 0x17; var_r31++) {
        lbl_1_bss_144[var_r31] = omAddObjEx(lbl_1_bss_33C, 0x65, 1, 0, -1, fn_1_12D7C);
        lbl_1_bss_144[var_r31]->work[0] = var_r31;
    }
    omMakeGroupEx(lbl_1_bss_33C, 0, 1);
    lbl_1_bss_140 = omGetGroupMemberListEx(lbl_1_bss_33C, 0);
    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        var_r28 = omAddObjEx(lbl_1_bss_33C, 0x66, 1, 0, 0, fn_1_1291C);
    }
    omMakeGroupEx(lbl_1_bss_33C, 1, 0xA);
    lbl_1_bss_13C = omGetGroupMemberListEx(lbl_1_bss_33C, 1);
    for (var_r31 = 0; var_r31 < 0xA; var_r31++) {
        var_r28 = omAddObjEx(lbl_1_bss_33C, 0x67, 1, 0, 1, fn_1_12B80);
    }
    fn_1_2C00(NULL, 1505.0f);
    lbl_1_bss_138 = omAddObjEx(lbl_1_bss_33C, 0x6D, 1, 0x17, -1, fn_1_23330);
    lbl_1_bss_134 = omAddObjEx(lbl_1_bss_33C, 0x68, 2, 0x13, -1, fn_1_DBF0);
    omMakeGroupEx(lbl_1_bss_33C, 2, 2);
    lbl_1_bss_130 = omGetGroupMemberListEx(lbl_1_bss_33C, 2);
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        var_r28 = omAddObjEx(lbl_1_bss_33C, 0x69, 5, 0xF, 2, fn_1_11D5C);
        var_r28->work[0] = var_r31;
    }
    lbl_1_bss_358.unk04 = NULL;
    lbl_1_bss_358.unk08 = NULL;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_2C[var_r31] = Hu3DModelCreateFile(lbl_1_data_F5C[var_r31]);
        Hu3DModelAttrSet(lbl_1_bss_2C[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_2C[var_r31], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    }
    lbl_1_bss_28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M450, 0x6C));
    HuSprAnimLock(lbl_1_bss_28);
    lbl_1_bss_24 = Hu3DParManCreate(lbl_1_bss_28, 0x14, &lbl_1_data_1504);
    Hu3DParManAttrSet(lbl_1_bss_24, 1);
    lbl_1_bss_1A4 = omAddObjEx(lbl_1_bss_33C, 0x6E, 0, 0, -1, fn_1_24620);
    lbl_1_bss_1A4->work[0] = 0x3E9;
    lbl_1_bss_128 = 0.0f;
}

void fn_1_298EC(omObjData *object)
{
    s32 var_r31;

    if (WipeStatGet() == 0) {
        if (lbl_1_bss_2FE >= 0) {
            MGSeqKill(lbl_1_bss_2FE);
        }
        if (lbl_1_bss_2FC >= 0) {
            MGSeqKill(lbl_1_bss_2FC);
        }
        MGSeqKillAll();
        HuAudAllStop();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            CharModelKill(lbl_1_data_0[GWPlayerCfg[var_r31].character]);
        }
        omOvlReturnEx(1, 1);
    }
}
