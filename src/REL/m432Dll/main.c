#include "REL/executor.h"
#include "dolphin/types.h"
#include "game/chrman.h"
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

#include "string.h"
#include "version.h"

#ifndef __MWERKS__
#include "game/audio.h"
#include "game/hsfex.h"

void HuSysVWaitSet(s16 vcount);
#endif

#undef ABS
#define ABS(x) ((0 > (x)) ? -(x) : (x))

typedef struct unk_bss_5D0_struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ struct unk_bss_5D0_struct *unk04;
    /* 0x08 */ struct unk_bss_5D0_struct *unk08;
} UnkBss5D0Struct; // Size 0xC

typedef struct unk_bss_5B8_struct {
    /* 0x00 */ HsfanimStruct00 *unk00;
    /* 0x04 */ s32 *unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ struct unk_bss_5B8_struct *unk10;
    /* 0x14 */ struct unk_bss_5B8_struct *unk14;
} UnkBss5B8Struct; // Size 0x18

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ s16 unk04;
} UnkBss428Struct; // Size 8

UnkBss5D0Struct lbl_1_bss_5D0;
UnkBss5B8Struct lbl_1_bss_5B8;
Process *lbl_1_bss_5B4;
Vec lbl_1_bss_5A8;
Vec lbl_1_bss_59C;
Vec lbl_1_bss_590;
Vec lbl_1_bss_584;
u32 lbl_1_bss_580;
s32 lbl_1_bss_57C;
u32 lbl_1_bss_578; // TODO maybe array?
s16 lbl_1_bss_576;
s16 lbl_1_bss_574;
s32 lbl_1_bss_570;
s32 lbl_1_bss_56C;
float lbl_1_bss_568;
s32 lbl_1_bss_528[16];
UnkBss428Struct lbl_1_bss_428[32];

#if VERSION_NTSC
#define _1606_BY_REFRESH_RATE 26.766666f
#else
#define _1606_BY_REFRESH_RATE 32.120003f
#endif

void fn_1_0(void)
{
    lbl_1_bss_5D0.unk04 = NULL;
    lbl_1_bss_5D0.unk08 = NULL;
}

void fn_1_24(u16 arg0, s16 arg1)
{
    UnkBss5D0Struct *temp_r31;
    UnkBss5D0Struct *temp_r30;
    UnkBss5D0Struct *temp_r29;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r31), MEMORY_DEFAULT_NUM);
    temp_r31->unk00 = arg0;
    temp_r31->unk02 = arg1;
    temp_r30 = &lbl_1_bss_5D0;
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
    UnkBss5D0Struct *var_r31;
    UnkBss5D0Struct *temp_r29;
    UnkBss5D0Struct *temp_r30;
    s16 temp_r28;

    var_r31 = lbl_1_bss_5D0.unk08;
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
    lbl_1_bss_5B8.unk10 = NULL;
    lbl_1_bss_5B8.unk14 = NULL;
}

void fn_1_174(s16 arg0, HsfanimStruct00 *arg1, s32 arg2, s32 arg3, s32 arg4, Vec *arg5, u8 arg6)
{
    UnkBss5B8Struct *temp_r27;
    UnkBss5B8Struct *var_r31;
    UnkBss5B8Struct *temp_r28;
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
    temp_r28 = &lbl_1_bss_5B8;
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
    UnkBss5B8Struct *var_r31;
    UnkBss5B8Struct *temp_r28;
    UnkBss5B8Struct *temp_r29;
    s32 i;

    var_r31 = lbl_1_bss_5B8.unk14;
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
        lbl_1_bss_428[i].unk00 = 0;
        lbl_1_bss_428[i].unk04 = -1;
    }
}

s16 fn_1_46C(s32 arg0)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        if (arg0 == lbl_1_bss_428[i].unk00) {
            return Hu3DModelLink(lbl_1_bss_428[i].unk04);
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_1_bss_428[i].unk00 == 0) {
            lbl_1_bss_428[i].unk00 = arg0;
            lbl_1_bss_428[i].unk04 = Hu3DModelCreateFile(arg0);
            return lbl_1_bss_428[i].unk04;
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
    lbl_1_bss_568 = 0.0f;
    lbl_1_bss_578 = lbl_1_bss_57C;
    GWMGRecordSet(arg0, lbl_1_bss_578);
    fn_1_580(lbl_1_bss_528, 7, lbl_1_bss_57C);
}

void fn_1_9EC(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        espDispOn(lbl_1_bss_528[i]);
    }
}

void fn_1_A40(void)
{
    float temp_f31;
    s32 i;

    if (0.0f <= lbl_1_bss_568) {
        lbl_1_bss_568 += 16.0f;
        temp_f31 = 1.0 + 0.2f * sind(lbl_1_bss_568);
        for (i = 7; i <= 14; i++) {
            espScaleSet(lbl_1_bss_528[i], temp_f31, temp_f31);
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
    lbl_1_bss_528[15] = espEntry(arg1, 0, 0);
    espTPLvlSet(lbl_1_bss_528[15], 0.5f);
    espColorSet(lbl_1_bss_528[15], 0, 0, 0);
    espPosSet(lbl_1_bss_528[15], temp_f31, temp_f30);
    temp_f31 = 248.0f;
    temp_f30 = arg0 - 8.0f;
    lbl_1_bss_528[14] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 55), 0, 0);
    espPosSet(lbl_1_bss_528[14], temp_f31 - 18.0f, temp_f30);
    for (i = 7; i <= 13; i++) {
        lbl_1_bss_528[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 48), 0, 0);
        espPosSet(lbl_1_bss_528[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_528, 7, lbl_1_bss_578);
    temp_f31 = 248.0f;
    temp_f30 = arg0 + 8.0f;
    for (i = 0; i <= 6; i++) {
        lbl_1_bss_528[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 49), 0, 0);
        espPosSet(lbl_1_bss_528[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_528, 0, 0);
    for (i = 0; i < 16; i++) {
        espDrawNoSet(lbl_1_bss_528[i], 0);
        espDispOff(lbl_1_bss_528[i]);
        espAttrSet(lbl_1_bss_528[i], HUSPR_ATTR_NOANIM);
        espPriSet(lbl_1_bss_528[i], 0x80 + i);
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
    lbl_1_bss_5A8 = *arg0;
    lbl_1_bss_590 = *arg2;
}

s32 fn_1_13DC(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_5A8, &lbl_1_bss_59C, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_590, &lbl_1_bss_584, &spC);
    Hu3DCameraPosSetV(1, &sp18, arg1, &spC);
    if (1.0f <= arg0) {
        return 1;
    }
    else {
        lbl_1_bss_56C = 1;
        return 0;
    }
}

void fn_1_1710(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_5A8, &lbl_1_bss_59C, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_590, &lbl_1_bss_584, &spC);
    fn_1_1350(&sp18, arg1, &spC);
    lbl_1_bss_56C = 1;
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
    lbl_1_bss_570 = HuAudSeqPlay(arg0);
}

void fn_1_1F58(s32 arg0)
{
    if (lbl_1_bss_570 >= 0) {
        if (arg0 < 0) {
            arg0 = 1000;
        }
        HuAudSeqFadeOut(lbl_1_bss_570, arg0);
    }
    lbl_1_bss_570 = -1;
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

PlayerOldFind lbl_1_bss_424;
float lbl_1_bss_420;

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
        return;
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
    lbl_1_bss_424 = find;
    lbl_1_bss_420 = yDist;
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
    player->unk_68 = 0;
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
    if (NULL == lbl_1_bss_424) {
        return;
    }
    addTime = FALSE;
    for (i = 0; i < 4; i++) {
        WorkPlayerOld *player2 = lbl_1_bss_424(i);
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
        fn_1_2BD0(player, _1606_BY_REFRESH_RATE, 1);
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
    temp_f28 = 0;
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
        player->unk_A8 = lbl_1_bss_420;
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

#include "REL/m432data.h"

typedef struct UnkBss0Struct {
    /* 0x000 */ omObjData *unk_00;
    /* 0x004 */ omObjData *unk_04;
    /* 0x008 */ omObjData *unk_08;
    /* 0x00C */ omObjData *unk_0C;
    /* 0x010 */ UnkM432DllBss0SubStruct *unk_10[2];
    /* 0x018 */ s32 unk_18;
    /* 0x01C */ Vec unk_1C;
    /* 0x028 */ Vec unk_28;
    /* 0x034 */ Vec unk_34;
    /* 0x040 */ Vec unk_40;
    /* 0x04C */ Vec unk_4C;
    /* 0x058 */ Vec unk_58;
    /* 0x064 */ float unk_64;
    /* 0x068 */ float unk_68;
    /* 0x06C */ float unk_6C;
    /* 0x070 */ float unk_70;
    /* 0x074 */ float unk_74;
    /* 0x078 */ float unk_78;
    /* 0x07C */ float unk_7C;
    /* 0x080 */ float unk_80;
    /* 0x084 */ float unk_84;
    /* 0x088 */ Vec unk_88[4][3];
    /* 0x118 */ Vec unk_118;
    /* 0x124 */ float unk_124;
    /* 0x128 */ float unk_128;
    /* 0x12C */ float unk_12C;
    /* 0x130 */ Vec unk_130[8];
    /* 0x190 */ Vec unk_190;
    /* 0x19C */ Vec unk_19C;
    /* 0x1A8 */ Vec unk_1A8;
    /* 0x1B4 */ s32 unk_1B4;
    /* 0x1B8 */ s32 unk_1B8;
    /* 0x1BC */ s32 unk_1BC;
    /* 0x1C0 */ Vec unk_1C0;
    /* 0x1CC */ s32 unk_1CC;
    /* 0x1D0 */ s32 unk_1D0;
    /* 0x1D4 */ float unk_1D4;
    /* 0x1D8 */ s32 unk_1D8;
    /* 0x1DC */ float unk_1DC;
    /* 0x1E0 */ float unk_1E0;
    /* 0x1E4 */ float unk_1E4;
    /* 0x1E8 */ float unk_1E8;
    /* 0x1EC */ float unk_1EC;
    /* 0x1F0 */ float unk_1F0[2];
} UnkBss0Struct; /* size = 0x1F8 */

typedef struct UnkM432DllStruct {
    WorkPlayerOld unk_00;
    s32 *unk_C4;
    UnkM432DllBss0SubStruct *unk_C8;
    UnkM432DllData1794Struct *unk_CC;
    UnkM432DllBss0SubStruct *unk_D0;
    s32 unk_D4[10];
    s32 unk_FC;
    s32 unk_100;
    float unk_104;
    float unk_108;
    float unk_10C;
    float unk_110;
    float unk_114;
    s32 unk_118[9];
    Vec unk_13C;
    float unk_148;
    float unk_14C;
    float unk_150;
    float unk_154;
    float unk_158;
    float unk_15C;
    float unk_160;
    float unk_164;
    s32 unk_168;
    s32 unk_16C;
    s32 unk_170;
    s32 unk_174;
    s32 unk_178;
    s32 unk_17C;
    s32 unk_180;
    s32 unk_184;
    s32 unk_188;
    s32 unk_18C;
    s32 unk_190;
    s32 unk_194;
} UnkM432DllStruct;

typedef struct UnkM432DllStruct2 {
    Vec unk_00;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
} UnkM432DllStruct2; /* size = 0x1C */

void fn_1_10250(omObjData *object);
void fn_1_153BC(void);
void fn_1_1615C(omObjData *object);
void fn_1_6F28(UnkBss0Struct *arg0);
void fn_1_93BC(UnkM432DllStruct *arg0);

omObjData *lbl_1_bss_41C;
omObjData **lbl_1_bss_418;
omObjData *lbl_1_bss_414;
// data UnkM432DllStruct
omObjData **lbl_1_bss_410;
s32 lbl_1_bss_40C;
AnimData *lbl_1_bss_408;
s16 lbl_1_bss_404;
s16 lbl_1_bss_402;
s16 lbl_1_bss_400;
s32 lbl_1_bss_3FC;
s32 lbl_1_bss_3F8;
s32 lbl_1_bss_3F4;
float lbl_1_bss_3F0;
UnkBss0Struct lbl_1_bss_0[2];

void fn_1_5148(UnkM432DllStruct *arg0)
{
    s32 var_r31;

    arg0->unk_D0 = 0;
    arg0->unk_FC = 0;
    arg0->unk_100 = 0;
    arg0->unk_10C = 0.0f;
    for (var_r31 = 0; var_r31 < 0xA; var_r31++) {
        arg0->unk_D4[var_r31] = -1;
    }
}

UnkM432DllStruct *fn_1_51A8(s32 arg0)
{
    s32 var_r31;
    UnkM432DllStruct *var_r30;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = lbl_1_bss_410[var_r31]->data;
        if (arg0 == var_r30->unk_184) {
            return var_r30;
        }
    }
    return NULL;
}

UnkM432DllBss0SubStruct *fn_1_5208(s32 arg0, UnkM432DllBss0SubStruct *arg1)
{
    UnkM432DllBss0SubStruct *var_r31;
    s32 var_r30;
    s32 var_r29;

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31 = lbl_1_bss_0[arg0].unk_10[var_r30];
        for (var_r29 = 0; var_r29 < 0x1F; var_r29++, var_r31++) {
            if (strcmp(arg1->unk_04, var_r31->unk_00) == 0) {
                return var_r31;
            }
        }
    }
    return NULL;
}

inline void fn_1_52B8_inline(Vec *arg0, float arg8, float arg9, float argA)
{
    arg0->x = arg8;
    arg0->y = arg9;
    arg0->z = argA;
}

void fn_1_52B8(UnkM432DllBss0SubStruct *arg0, Vec *arg1)
{
    Mtx sp8;

    fn_1_52B8_inline(arg1, 0.0f, 0.0f, arg0->unk_1C);
    MTXRotRad(sp8, 0x79, 0.017453292f * arg0->unk_18);
    MTXMultVec(sp8, arg1, arg1);
    VECAdd(&arg0->unk_2C, arg1, arg1);
}

void fn_1_5364(s32 arg0, omObjData *object)
{
    if (lbl_1_bss_0[arg0].unk_1D8 >= 0) {
        lbl_1_bss_0[arg0].unk_1DC -= 1.0f / REFRESH_RATE;
        if (0.0f >= lbl_1_bss_0[arg0].unk_1DC) {
            HuAudFXStop(lbl_1_bss_0[arg0].unk_1D8);
            lbl_1_bss_0[arg0].unk_1D8 = -1;
        }
        else {
            HuAudFXPitchSet(lbl_1_bss_0[arg0].unk_1D8, (s32)(8191.0f * lbl_1_bss_0[arg0].unk_1DC));
            HuAudFXVolSet(lbl_1_bss_0[arg0].unk_1D8, (s32)(127.0f * lbl_1_bss_0[arg0].unk_1DC));
        }
    }
    lbl_1_bss_0[arg0].unk_88[0][2].x = lbl_1_bss_0[arg0].unk_80;
    lbl_1_bss_0[arg0].unk_88[1][2].x = lbl_1_bss_0[arg0].unk_80;
    Hu3DModelRotSet(object->model[20], 0.0f, lbl_1_bss_0[arg0].unk_80, 0.0f);
    fn_1_1D18(object->model[20], "m432_13-player2A", &lbl_1_bss_0[arg0].unk_88[0][1]);
    fn_1_1D18(object->model[20], "m432_13-player2B", &lbl_1_bss_0[arg0].unk_88[1][1]);
    lbl_1_bss_0[arg0].unk_88[2][2].x = lbl_1_bss_0[arg0].unk_84;
    lbl_1_bss_0[arg0].unk_88[3][2].x = lbl_1_bss_0[arg0].unk_84;
    Hu3DModelRotSet(object->model[21], 0.0f, lbl_1_bss_0[arg0].unk_84, 0.0f);
    fn_1_1D18(object->model[21], "m432_13-player2C", &lbl_1_bss_0[arg0].unk_88[2][1]);
    fn_1_1D18(object->model[21], "m432_13-player2C", &lbl_1_bss_0[arg0].unk_88[3][1]);
}

void fn_1_576C(s32 arg0, omObjData *arg1)
{
    float var_f31 = lbl_1_bss_0[arg0].unk_124 * (Hu3DMotionMaxTimeGet(arg1->model[22]) / 1000.0f);
    lbl_1_bss_0[arg0].unk_128 += 0.02f * (var_f31 - lbl_1_bss_0[arg0].unk_128);
    Hu3DMotionTimeSet(arg1->model[22], lbl_1_bss_0[arg0].unk_128);
}

void fn_1_5848(UnkM432DllStruct *var_r28, UnkM432DllBss0SubStruct *var_r31)
{
    s32 sp20;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    s32 var_r30;
    s32 var_r27;
    UnkM432DllStruct *var_r26;
    UnkM432DllBss0SubStruct *var_r25;
    UnkBss0Struct *var_r24;
    s32 var_r21;
    s32 var_r20;
    char **var_r19;
    u8 *var_r18;

    var_r20 = var_r31->unk_1C;
    var_r26 = fn_1_51A8(var_r28->unk_184 ^ 1);
    var_r24 = &lbl_1_bss_0[var_r28->unk_184 >> 1];
    sp20 = var_r24->unk_1B8;
    var_r27 = 6;
    var_r18 = lbl_1_data_4F0;
    var_r19 = lbl_1_data_440;
    if ((var_r31->unk_14 & 4) != 0) {
        sp20 = var_r24->unk_1BC;
        var_r27 = 0xA;
        var_r18 = lbl_1_data_504;
        var_r19 = lbl_1_data_4C8;
    }
    var_r30 = frandmod(var_r27 - 1);
    for (var_r21 = 0; var_r21 < (var_r27 - 1); var_r21++) {
        var_r30 = (var_r30 + 1) % (var_r27 - 1);
        if ((var_r20 != var_r30) && (sp20 != var_r30) && (var_r30 != var_r18[var_r20])) {
            var_r31->unk_04 = var_r19[var_r30];
            var_r25 = fn_1_5208(var_r28->unk_184 >> 1, var_r31);
            var_f31 = var_r26->unk_00.unk_6C.x - var_r25->unk_2C.x;
            var_f30 = var_r26->unk_00.unk_6C.z - var_r25->unk_2C.z;
            if (200.0f < sqrtf((var_f31 * var_f31) + (var_f30 * var_f30))) {
                break;
            }
        }
    }
    (void)var_r31;
    (void)var_r31;
    (void)var_r31;
}

void fn_1_5BAC(UnkM432DllStruct *arg0, omObjData *object, UnkM432DllBss0SubStruct *arg2, UnkM432DllBss0SubStruct *arg3)
{
    Vec sp14;
    Vec sp8;
    float var_f31;

    var_f31 = arg2->unk_20.y;
    if (25.0f <= arg3->unk_38) {
        var_f31 -= 400.0f;
    }
    else {
        var_f31 -= 8.0f * arg3->unk_38;
    }
    if ((arg2->unk_20.y == var_f31) && (0.0f > arg2->unk_2C.y) && (-1.0f < arg2->unk_2C.y)) {
        arg2->unk_2C.y = 0.0f;
        HuAudFXPlay(0x699);
    }
    arg2->unk_2C.y += 0.25f * (var_f31 - arg2->unk_2C.y);
    if ((arg2->unk_40 < 0) && ((arg2->unk_20.y - 200.0f) > arg2->unk_2C.y)) {
        fn_1_52B8_inline(&sp8, arg2->unk_2C.x - 80.0f, arg2->unk_20.y, arg2->unk_2C.z);
        fn_1_52B8_inline(&sp14, 80.0f + arg2->unk_2C.x, arg2->unk_20.y, arg2->unk_2C.z);
        fn_1_174(lbl_1_bss_404, &lbl_1_data_1814, 4, 4, 2, &sp8, 0);
        HuAudFXPlay(0x69A);
    }
    Hu3DModelPosSet(object->model[arg2->unk_08], arg2->unk_2C.x, arg2->unk_2C.y, arg2->unk_2C.z);
    if ((arg2->unk_20.y - 399.0f) > arg2->unk_2C.y) {
        arg0->unk_17C++;
        arg2->unk_14 = 0;
    }
}

void fn_1_5F2C(UnkM432DllStruct *arg0, UnkM432DllBss0SubStruct *arg1)
{
    float var_f31;
    float var_f30;
    UnkBss0Struct *var_r28;
    s32 var_r25;
    s32 var_r22;
    char *var_r24;

    if ((arg0->unk_180 == 0x7D3) && !(arg1->unk_2C.y <= arg0->unk_00.unk_6C.y)) {
        var_r28 = &lbl_1_bss_0[arg0->unk_184 >> 1];
        var_f31 = arg0->unk_00.unk_6C.x - arg1->unk_2C.x;
        var_f30 = arg0->unk_00.unk_6C.z - arg1->unk_2C.z;
        if (sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) < 100.0f) {
            arg0->unk_00.unk_3C |= 0x18;
            arg0->unk_180 = 0x7D7;
            arg0->unk_C4 = NULL;
            var_r22 = arg1->unk_1C;
            var_r25 = var_r28->unk_1B8;
            var_r24 = lbl_1_data_440[5];
            if (arg1->unk_14 & 4) {
                var_r25 = var_r28->unk_1BC;
                var_r24 = lbl_1_data_4C8[9];
            }
            if (var_r22 == var_r25) {
                arg1->unk_04 = var_r24;
            }
            else {
                fn_1_5848(arg0, arg1);
            }
            arg0->unk_C8 = fn_1_5208(arg0->unk_184 >> 1, arg1);
            arg0->unk_D4[arg0->unk_FC] = arg1->unk_44 - arg0->unk_17C;
            arg0->unk_FC = (arg0->unk_FC + 1) % 10;
        }
    }
}

void fn_1_623C(UnkBss0Struct *arg0, s32 arg1, UnkM432DllStruct *arg2, UnkM432DllStruct *arg3)
{
    UnkM432DllBss0SubStruct *sp3C;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f23;
    UnkM432DllBss0SubStruct *var_r31;
    UnkM432DllStruct *var_r29;
    omObjData *var_r28;
    s32 var_r26;
    s32 var_r19;

    var_f29 = 0.0f;
    var_f28 = 0.0f;
    var_f27 = 0.0f;
    var_r28 = arg0->unk_04;
    for (var_r26 = 0; var_r26 < 2; var_r26++) {
        var_r29 = fn_1_51A8((var_r26 + (arg1 * 2)));
        for (var_r31 = arg0->unk_10[var_r26], var_r19 = 0; var_r19 < 0x1F; var_r19++, var_r31++) {
            if (var_r31->unk_14 & 0x600) {
                if (1.0f < var_r31->unk_3C) {
                    var_r31->unk_3C = 1.0f;
                }
                var_r31->unk_38 = var_r31->unk_38 + var_r31->unk_3C;
                var_r31->unk_3C = var_r31->unk_3C - 0.05f;
                if (0.0f > var_r31->unk_3C) {
                    var_r31->unk_3C = 0.0f;
                }
                if (var_r31->unk_14 & 0x400) {
                    var_f29 += var_r31->unk_38;
                }
                if (var_r31->unk_14 & 0x200) {
                    var_f28 += var_r31->unk_38;
                }
            }
            if (var_r31->unk_14 & 0x800) {
                var_f27 += var_r31->unk_38;
            }
            if (NULL != var_r31->unk_04) {
                sp3C = fn_1_5208(arg1, var_r31);
                switch (var_r31->unk_14) {
                    case 3:
                        break;
                    case 1:
                        fn_1_5BAC(var_r29, var_r28, var_r31, sp3C);
                        break;
                    case 2:
                    case 4:
                        fn_1_5F2C(var_r29, var_r31);
                        break;
                }
            }
        }
    }
    arg0->unk_80 = 80.0f + -var_f29;
    arg0->unk_84 = 160.0f + -var_f28;
    fn_1_5364(arg1, var_r28);
    arg0->unk_124 = var_f27;
    if (1000.0f <= arg0->unk_124) {
        arg0->unk_124 = 1000.0f;
    }
    var_f23 = lbl_1_bss_0[arg1].unk_124 * (Hu3DMotionMaxTimeGet(var_r28->model[22]) / 1000.0f);
    lbl_1_bss_0[arg1].unk_128 += 0.02f * (var_f23 - lbl_1_bss_0[arg1].unk_128);
    Hu3DMotionTimeSet(var_r28->model[22], lbl_1_bss_0[arg1].unk_128);
    if ((lbl_1_bss_3FC < 0) && (1000.0f <= arg0->unk_124)) {
        lbl_1_bss_3FC = arg2->unk_184 & 2;
        arg2->unk_17C += 4;
        arg3->unk_17C += 4;
    }
}

void fn_1_6D34(UnkBss0Struct *arg0, UnkM432DllStruct *arg1, Vec *arg2)
{
    float var_f31;
    float var_f30;
    float var_f28;
    float var_f27;
    s32 var_r31;

    var_f27 = 100000.0f;
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        var_f31 = arg1->unk_00.unk_6C.x - arg0->unk_130[var_r31].x;
        var_f30 = arg1->unk_00.unk_6C.z - arg0->unk_130[var_r31].z;
        var_f28 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
        if (var_f27 > var_f28) {
            var_f27 = var_f28;
            *arg2 = arg0->unk_130[var_r31];
        }
    }
}

void fn_1_6F28(UnkBss0Struct *arg0)
{
    float var_f31;
    float var_f30;
    float var_f26;
    float var_f23;

    UnkM432DllStruct *var_r30 = arg0->unk_08->data;

    if (arg0->unk_1B4 < 0) {
        fn_1_6D34(arg0, var_r30, &arg0->unk_190);
        var_r30->unk_00.unk_3C |= 8;
        var_r30->unk_180 = 0x7D9;
        arg0->unk_190.y = 3000.0f;
        arg0->unk_19C = arg0->unk_190;
        arg0->unk_1B4 = 0;
        Hu3DModelRotSet(arg0->unk_04->model[25], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(arg0->unk_04->model[25], HU3D_ATTR_DISPOFF);
    }
    switch (arg0->unk_1B4) {
        case 0:
            fn_1_40C0(&var_r30->unk_00);
            var_f23 = var_r30->unk_00.unk_6C.y - arg0->unk_19C.y;
            arg0->unk_190.y += 0.03f * var_f23;
            if (50.0f > ABS(var_f23)) {
                arg0->unk_1B4++;
                arg0->unk_1A8 = arg0->unk_1C0;
                arg0->unk_1A8.y += 900.0f;
                arg0->unk_1A8.z -= 150.0f;
                var_r30->unk_00.unk_6C = arg0->unk_19C;
                var_r30->unk_00.unk_9C = 0.0f;
                Hu3DMotionShiftSet(arg0->unk_08->model[0], arg0->unk_08->motion[6], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
            break;
        case 1:
            if (50.0f > (0.0f > (arg0->unk_1A8.y - arg0->unk_190.y) ? -(arg0->unk_1A8.y - arg0->unk_190.y) : arg0->unk_1A8.y - arg0->unk_190.y)) {
                arg0->unk_1B4++;
            }
            break;
        case 2:
            arg0->unk_1A8.y += 0.1f * (((900.0f + arg0->unk_1C0.y) - 200.0f) - arg0->unk_1A8.y);
            if (((900.0f + arg0->unk_1C0.y) - 190.0f) > arg0->unk_1A8.y) {
                arg0->unk_1B4++;
                var_r30->unk_16C = 1;
                var_r30->unk_180 = 0x7D3;
                fn_1_4ED8(&var_r30->unk_00, 0);
                var_r30->unk_00.unk_3C |= 0x210;
                if (NULL != arg0->unk_0C) {
                    arg0->unk_1B4 = 4;
                    arg0->unk_08 = arg0->unk_0C;
                    var_r30 = arg0->unk_08->data;
                    fn_1_6D34(arg0, var_r30, &arg0->unk_1A8);
                    var_r30->unk_00.unk_3C |= 8;
                    var_r30->unk_180 = 0x7D9;
                }
            }
            break;
        case 3:
            arg0->unk_1A8.y += 10.0f;
            if ((2000.0f + arg0->unk_1C0.y) < arg0->unk_1A8.y) {
                arg0->unk_08 = NULL;
                Hu3DModelAttrSet(arg0->unk_04->model[25], HU3D_ATTR_DISPOFF);
                return;
            }
            break;
        case 4:
            fn_1_40C0(&var_r30->unk_00);
            var_f31 = arg0->unk_1A8.x - arg0->unk_190.x;
            var_f30 = arg0->unk_1A8.z - arg0->unk_190.z;
            arg0->unk_190.x += 0.05f * var_f31;
            arg0->unk_190.y += 0.01f * (arg0->unk_1A8.y - arg0->unk_190.y);
            arg0->unk_190.z += 0.05f * var_f30;
            if (20.0f > sqrtf((var_f31 * var_f31) + (var_f30 * var_f30))) {
                arg0->unk_19C = arg0->unk_190;
                arg0->unk_1B4 = 0;
            }
            break;
    }
    if ((arg0->unk_1B4 > 0) && (arg0->unk_1B4 < 4)) {
        if (arg0->unk_1B4 < 3) {
            var_r30->unk_00.unk_6C = arg0->unk_19C;
            fn_1_2DD4(&var_r30->unk_00);
        }
        var_f23 = 0.03f * (arg0->unk_1A8.y - arg0->unk_190.y);
        arg0->unk_190.y += var_f23;
        if (arg0->unk_1C0.y < arg0->unk_190.y) {
            var_f26 = (arg0->unk_1A8.y - arg0->unk_190.y) / 900.0f;
            if (0.1f > var_f26) {
                var_f26 = 0.1f;
            }
            if (1.0f < var_f26) {
                var_f26 = 1.0f;
            }
            var_f26 = 1.0f - var_f26;
            arg0->unk_190.x += 0.03f * var_f26 * (arg0->unk_1A8.x - arg0->unk_190.x);
            arg0->unk_190.z += 0.03f * var_f26 * (arg0->unk_1A8.z - arg0->unk_190.z);
        }
    }
    Hu3DModelPosSet(arg0->unk_04->model[25], arg0->unk_190.x, arg0->unk_190.y, arg0->unk_190.z);
    fn_1_1D18(arg0->unk_04->model[25], "g008m2_000-itemhook_sao", &arg0->unk_19C);
}

void fn_1_7C1C(UnkBss0Struct *var_r31, UnkM432DllStruct *var_r30, UnkM432DllStruct *var_r29)
{
    float var_f31;
    float var_f30;

    if ((var_r31->unk_7C == 0.0f) && ((0.0f < var_r31->unk_70) || (0.0f > var_r31->unk_74))) {
        if (0.0f < var_r31->unk_70) {
            var_r31->unk_28.y += 0.05f * (var_r31->unk_70 - var_r31->unk_28.y);
            if (2.0f
                > (0.0f > (var_r31->unk_70 - var_r31->unk_28.y) ? -(var_r31->unk_70 - var_r31->unk_28.y) : var_r31->unk_70 - var_r31->unk_28.y)) {
                var_r31->unk_28.y = var_r31->unk_70;
                var_r31->unk_70 = 0.0f;
            }
        }
        if (0.0f > var_r31->unk_74) {
            var_r31->unk_28.z += 0.05f * (var_r31->unk_74 - var_r31->unk_28.z);
            if (2.0f
                > (0.0f > (var_r31->unk_74 - var_r31->unk_28.z) ? -(var_r31->unk_74 - var_r31->unk_28.z) : var_r31->unk_74 - var_r31->unk_28.z)) {
                var_r31->unk_28.z = var_r31->unk_74;
                var_r31->unk_74 = 0.0f;
            }
        }
    }
    else {
        var_f30 = var_r31->unk_1EC / var_r31->unk_1E8;
        if (265.0f > var_f30) {
            var_f31 = 0.2f * (265.0f - var_f30);
            if (1.0f <= ABS(var_f31)) {
                var_r31->unk_28.z -= var_f31;
            }
        }
        switch (var_r31->unk_18) {
            case 0:
                if ((-7100.0f > var_r31->unk_28.z) && ((-7750.0f < var_r31->unk_1F0[0]) || (-7750.0f < var_r31->unk_1F0[1]))) {
                    var_r31->unk_28.z = -7100.0f;
                }
                if ((-7750.0f >= var_r31->unk_1F0[0]) && (-7750.0f >= var_r31->unk_1F0[1])) {
                    var_r31->unk_18++;
                    var_r31->unk_74 = -8700.0f;
                    var_r30->unk_17C += 3;
                    var_r30->unk_15C = -7750.0f;
                    var_r29->unk_17C += 3;
                    var_r29->unk_15C = -7750.0f;
                    fn_1_1D18(var_r31->unk_04->model[3], "m432_00-n1", &var_r31->unk_1C0);
                    return;
                }
                break;
            case 1:
                if ((-9500.0f > var_r31->unk_28.z) && ((-10200.0f < var_r31->unk_1F0[0]) || (-10200.0f < var_r31->unk_1F0[1]))) {
                    var_r31->unk_28.z = -9500.0f;
                }
                if ((-10200.0f >= var_r31->unk_1F0[0]) && (-10200.0f >= var_r31->unk_1F0[1])) {
                    var_r31->unk_18++;
                    var_r31->unk_74 = -11100.0f;
                    var_r30->unk_17C += 3;
                    var_r30->unk_15C = -10200.0f;
                    var_r29->unk_17C += 3;
                    var_r29->unk_15C = -10200.0f;
                    return;
                }
                break;
            case 2:
                if ((-11500.0f > var_r31->unk_28.z) && ((-12300.0f < var_r31->unk_1F0[0]) || (-12300.0f < var_r31->unk_1F0[1]))) {
                    var_r31->unk_28.z = -11500.0f;
                }
                if ((NULL != var_r30->unk_C8) && (var_r30->unk_C8->unk_14 & 8) && (NULL != var_r29->unk_C8) && ((var_r29->unk_C8->unk_14 & 8) != 0)
                    && (var_r30->unk_00.unk_38 == 0) && (var_r29->unk_00.unk_38 == 0)) {
                    var_r31->unk_18++;
                    var_r31->unk_1E4 = var_r30->unk_C8->unk_2C.y;
                    var_r31->unk_74 = -13500.0f;
                    var_r31->unk_70 = var_r30->unk_C8->unk_2C.y;
                    var_r30->unk_17C += 6;
                    var_r29->unk_17C += 6;
                    return;
                }
                break;
            case 3:
                if ((-13700.0f > var_r31->unk_28.z) && ((-14400.0f < var_r31->unk_1F0[0]) || (-14400.0f < var_r31->unk_1F0[1]))) {
                    var_r31->unk_28.z = -13700.0f;
                }
                if ((NULL != var_r30->unk_C8) && (var_r30->unk_C8->unk_14 & 0x10) && (NULL != var_r29->unk_C8) && (var_r29->unk_C8->unk_14 & 0x10)
                    && (var_r30->unk_00.unk_38 == 0) && (var_r29->unk_00.unk_38 == 0)) {
                    var_r31->unk_18++;
                    var_r31->unk_1E4 = var_r30->unk_C8->unk_2C.y;
                    var_r31->unk_74 = -15700.0f;
                    var_r31->unk_78 = 0.0f;
                    var_r31->unk_7C = 120.0f;
                    var_r31->unk_4C = var_r31->unk_28;
                    var_r31->unk_34 = var_r31->unk_1C;
                    var_r31->unk_58.x = var_r31->unk_28.x;
                    var_r31->unk_58.y = 400.0f + var_r30->unk_C8->unk_2C.y;
                    var_r31->unk_58.z = -15700.0f;
                    var_r31->unk_40 = var_r31->unk_58;
                    var_r31->unk_40.y = 800.0f + var_r30->unk_C8->unk_2C.y;
                    var_r31->unk_40.z += 3800.0f;
                    var_r30->unk_17C += 0xA;
                    var_r30->unk_148 = 0.0f;
                    fn_1_52B8(&lbl_1_bss_0[var_r30->unk_184 >> 1].unk_10[var_r30->unk_184 & 1][0x1B], &var_r30->unk_13C);
                    var_r29->unk_17C += 0xA;
                    var_r29->unk_148 = 0.0f;
                    fn_1_52B8(&lbl_1_bss_0[var_r29->unk_184 >> 1].unk_10[var_r29->unk_184 & 1][0x1B], &var_r29->unk_13C);
                }
                break;
        }
    }
}

s32 fn_1_8540(UnkM432DllStruct *arg0)
{
    if (arg0->unk_17C >= 0x1F) {
        return -1;
    }
    if (arg0->unk_17C >= 0x1B) {
        return 3;
    }
    if (arg0->unk_17C >= 0xB) {
        return 2;
    }
    if (arg0->unk_17C >= 5) {
        return 1;
    }
    if (arg0->unk_17C >= 1) {
        return 0;
    }
    return -1;
}

UnkM432DllBss0SubStruct *fn_1_85AC(UnkM432DllStruct *arg0, UnkBss0Struct *arg1)
{
    UnkM432DllBss0SubStruct *var_r31 = arg1->unk_10[arg0->unk_184 & 1];
    s32 var_r30;
    for (var_r30 = 0; var_r30 < 0x1F; var_r30++, var_r31++) {
        if ((arg0->unk_17C <= var_r30) && (var_r31->unk_14 & 0xF00)) {
            return var_r31;
        }
    }
    return NULL;
}

float fn_1_861C(UnkM432DllStruct *arg0, UnkBss0Struct *arg1, Vec *arg2)
{
    float var_f31;
    float var_f30;
    float var_f27;
    float var_f28;
    s32 var_r31;

    var_f28 = 100000.0f;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_f31 = arg0->unk_00.unk_6C.x - arg1->unk_88[var_r31][1].x;
        var_f30 = arg0->unk_00.unk_6C.z - arg1->unk_88[var_r31][1].z;
        var_f27 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
        if (var_f28 > var_f27) {
            var_f28 = var_f27;
            *arg2 = arg1->unk_88[var_r31][1];
        }
    }
    return var_f28;
}

void fn_1_8814(UnkM432DllStruct *arg0, s32 arg1, Vec *arg2)
{
    float var_f31;
    float var_f30;
    float var_f28;
    float var_f27;

    var_f27 = 72.0f * arg0->unk_CC->unk_04;
    var_f31 = arg2->x - arg0->unk_00.unk_6C.x;
    var_f30 = arg2->z - arg0->unk_00.unk_6C.z;
    var_f31 *= 4.0f;
    var_f30 *= 4.0f;
    var_f28 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    if (var_f27 < var_f28) {
        var_f31 = var_f27 * (var_f31 / var_f28);
        var_f30 = var_f27 * (var_f30 / var_f28);
    }
    arg0->unk_00.unk_20 = var_f31;
    arg0->unk_00.unk_24 = -var_f30;
}

void fn_1_8A14(UnkM432DllStruct *arg0, s32 arg1, UnkM432DllBss0SubStruct *arg2)
{
    Vec spC;

    if (NULL != arg2) {
        spC = arg2->unk_2C;
        if (arg2->unk_14 & 0xF00) {
            fn_1_52B8(arg2, &spC);
        }
        fn_1_8814(arg0, 0, &spC);
    }
}

UnkM432DllBss0SubStruct *fn_1_8CB4(UnkM432DllStruct *arg0, UnkM432DllStruct *arg1, UnkBss0Struct *arg2)
{
    s32 var_r30;
    UnkM432DllBss0SubStruct *var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;

    var_r29 = NULL;
    if (arg0->unk_17C < 0x1F) {
        var_r29 = &arg2->unk_10[arg0->unk_184 & 1][arg0->unk_17C];
    }
    if (NULL == var_r29) {
        return NULL;
    }
    if (var_r29->unk_14 & 2) {
        var_r28 = 5;
        var_r27 = arg2->unk_1B8;
        var_r26 = 0;
        var_r25 = 5;
    }
    else {
        var_r28 = 9;
        var_r27 = arg2->unk_1BC;
        var_r26 = 0;
        var_r25 = 9;
        if (-14100.0f < arg0->unk_00.unk_6C.z) {
            var_r26 = 3;
            var_r25 = 9;
        }
        if (-13700.0f < arg0->unk_00.unk_6C.z) {
            var_r26 = 0;
            var_r25 = 6;
        }
        if (-13300.0f < arg0->unk_00.unk_6C.z) {
            var_r26 = 0;
            var_r25 = 3;
        }
    }
    var_r30 = frandmod(var_r28);
    for (var_r21 = 0; var_r21 < var_r28; var_r21++) {
        var_r30 = (var_r30 + 1) % var_r28;
        if ((var_r26 <= var_r30) && (var_r25 > var_r30)
            && ((arg0->unk_100 != 0) || ((var_r27 != var_r30) && (((var_r29->unk_14 & 4) == 0) || (var_r30 <= 3))))) {
            var_r24 = arg0->unk_FC;
            var_r19 = 0;
            for (var_r20 = 0; var_r20 < arg0->unk_CC->unk_18; var_r20++) {
                var_r24--;
                if (var_r24 < 0) {
                    var_r24 += 0xA;
                }
                if (var_r30 == arg0->unk_D4[var_r24]) {
                    var_r19 = 1;
                }
            }
            if (var_r19 == 0) {
                break;
            }
        }
    }
    if ((var_r21 == var_r28) || (var_r27 == var_r30)) {
        var_r30 = frandmod(var_r28);
        while (var_r30 == var_r27) {
            var_r30 = (var_r30 + 1) % var_r28;
        }
    }
    if (arg0->unk_CC->unk_1C < arg0->unk_100) {
        var_r30 = var_r27;
    }
    if (NULL != arg1->unk_C8) {
        if (var_r29->unk_14 & 2) {
            if (arg1->unk_C8->unk_14 & 8) {
                var_r30 = var_r27;
            }
        }
        else if (arg1->unk_C8->unk_14 & 0x10) {
            var_r30 = var_r27;
        }
    }
    arg0->unk_100++;
    (void)var_r26;
    (void)var_r25;
    return &var_r29[var_r30];
}

void fn_1_8F3C(UnkM432DllStruct *arg0, UnkBss0Struct *arg1, UnkM432DllBss0SubStruct *arg2, Vec *arg3)
{
    *arg3 = arg2->unk_2C;
    if (arg0->unk_00.unk_48 >= 0x14) {
        if (-12200.0f < arg0->unk_00.unk_6C.z) {
            arg3->x = arg1->unk_28.x;
        }
        else if ((-13300.0f < arg0->unk_00.unk_6C.z) && (-13400.0f > arg2->unk_2C.z)) {
            arg3->x = arg1->unk_28.x - 500.0f;
        }
        else if ((-13700.0f < arg0->unk_00.unk_6C.z) && (-13800.0f > arg2->unk_2C.z)) {
            arg3->x = 500.0f + arg1->unk_28.x;
        }
        else if ((-13500.0f > arg0->unk_00.unk_6C.z) && (-13400.0f < arg2->unk_2C.z)) {
            arg3->x = 500.0f + arg1->unk_28.x;
            return;
        }
    }
}

void fn_1_906C(UnkM432DllStruct *var_r31, UnkM432DllBss0SubStruct *var_r27)
{
    float var_f31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r30 = 0;
    var_r29 = 0;
    var_r28 = 0;
    switch (var_r27->unk_14 & 0xF00) {
        case 0x100:
            var_r30 = 0x200;
            var_r29 = 0x200;
            break;
        case 0x400:
            var_r30 = 0x800;
            var_r29 = 0x800;
            var_r28 = 1;
            break;
        case 0x200:
            var_r30 = 0x400;
            var_r29 = 0x400;
            var_r28 = 1;
            break;
        case 0x800:
            if ((var_r31->unk_CC->unk_14 >= var_r31->unk_154) && (var_r31->unk_CC->unk_10 > var_r31->unk_158)) {
                var_r31->unk_00.unk_34 = 0x96;
            }
            else if ((var_r31->unk_CC->unk_10 <= var_r31->unk_154) && (var_r31->unk_CC->unk_14 >= var_r31->unk_158)) {
                var_r31->unk_00.unk_34 = 0x96;
            }
            else {
                var_r31->unk_00.unk_30 = 0x96;
            }
            if (var_r31->unk_CC->unk_0C < frandf()) {
                var_r31->unk_104 *= 0.99f;
            }
            if (var_r31->unk_CC->unk_00 > lbl_1_bss_57C) {
                var_r31->unk_104 *= 0.99f;
            }
            else {
                var_r31->unk_104 *= 1.01f;
            }
            if (0.5f > var_r31->unk_104) {
                var_r31->unk_104 = 0.5f;
            }
            if (1.0f < var_r31->unk_104) {
                var_r31->unk_104 = 1.0f;
            }
            var_r31->unk_00.unk_30 = var_r31->unk_00.unk_30 * var_r31->unk_104;
            var_r31->unk_00.unk_34 = var_r31->unk_00.unk_34 * var_r31->unk_104;
            break;
    }
    var_r31->unk_108 -= 1.0f;
    if (0.0f > var_r31->unk_108) {
        var_f31 = var_r31->unk_CC->unk_08;
        if ((var_r28 != 0) && (GWPlayerCfg[var_r31->unk_188].diff == 3)) {
            var_f31 = lbl_1_data_17D4.unk_08;
        }
        var_r31->unk_108 = var_f31 * (0.9f + (frandf() / 2));
        var_r31->unk_00.unk_28 |= var_r30;
        var_r31->unk_00.unk_2C |= var_r29;
    }
}

void fn_1_93BC(UnkM432DllStruct *arg0)
{
    Vec spF8;
    float spD0;

    float var_f31;
    float var_f30;

    UnkM432DllBss0SubStruct *var_r30;
    UnkBss0Struct *var_r29;
    UnkM432DllBss0SubStruct *var_r28;
    UnkM432DllStruct *var_r27;
    s32 var_r20;

    if (NULL != arg0->unk_CC) {
        var_r27 = fn_1_51A8(arg0->unk_184 ^ 1);
        var_r29 = &lbl_1_bss_0[arg0->unk_184 >> 1];
        var_r20 = 1;
        switch (fn_1_8540(arg0)) {
            case 0:
                var_r30 = fn_1_85AC(arg0, var_r29);
                fn_1_8A14(arg0, 0, var_r30);
                break;
            case 1:
                var_r28 = fn_1_85AC(arg0, var_r29);
                if (NULL != var_r28) {
                    var_r30 = var_r28;
                    if (((NULL == arg0->unk_C8) && (NULL != var_r27->unk_C8)) || ((var_r28->unk_2C.z - 400.0f) > arg0->unk_00.unk_6C.z)) {
                        var_r30++;
                    }
                    else if ((var_r28->unk_2C.z - 1350.0f) > var_r27->unk_00.unk_6C.z) {
                        var_r30++;
                        var_r20 = 0;
                    }
                    if ((1400.0f < (var_r28->unk_2C.z - arg0->unk_00.unk_6C.z)) && (1400.0f < (var_r28->unk_2C.z - var_r27->unk_00.unk_6C.z))) {
                        var_r20 = 0;
                        arg0->unk_00.unk_24 = 0x48;
                    }
                    else {
                        if (((var_r28->unk_2C.z - 175.0f) > arg0->unk_00.unk_6C.z) && ((var_r28->unk_2C.z - 1350.0f) < arg0->unk_00.unk_6C.z)) {
                            if (((var_r29->unk_28.x - 20.0f) < arg0->unk_00.unk_6C.x) && ((20.0f + var_r29->unk_28.x) > arg0->unk_00.unk_6C.x)
                                && ((var_r28->unk_2C.z - 1000.0f) > arg0->unk_00.unk_6C.z)) {
                                arg0->unk_00.unk_24 = 0x48;
                            }
                            if ((var_r28->unk_2C.z - 1100.0f) > arg0->unk_00.unk_6C.z) {
                                arg0->unk_00.unk_28 |= 0x100;
                                arg0->unk_00.unk_2C |= 0x100;
                                fn_1_8A14(arg0, 0, var_r30);
                            }
                            else {
                                spD0 = fn_1_861C(arg0, var_r29, &spF8);
                                if ((arg0->unk_00.unk_BC < spD0) && (400.0f > spD0)) {
                                    arg0->unk_00.unk_28 |= 0x100;
                                    arg0->unk_00.unk_2C |= 0x100;
                                    fn_1_8814(arg0, 0, &spF8);
                                }
                            }
                        }
                        else {
                            fn_1_8A14(arg0, 0, var_r30);
                        }
                        if (((var_r28->unk_2C.z - 175.0f) < arg0->unk_00.unk_6C.z) && (arg0->unk_00.unk_A8 < arg0->unk_00.unk_6C.y)) {
                            arg0->unk_00.unk_20 = 0;
                            arg0->unk_00.unk_24 = 0;
                        }
                    }
                }
                break;
            case 2:
                var_r20 = 0;
                arg0->unk_10C -= 1.0f;
                if (NULL == arg0->unk_D0) {
                    arg0->unk_D0 = fn_1_8CB4(arg0, var_r27, var_r29);
                }
                if (arg0->unk_10C == 1.0f) {
                    arg0->unk_D0 = fn_1_8CB4(arg0, var_r27, var_r29);
                }
                if (NULL != arg0->unk_D0) {
                    fn_1_8F3C(arg0, var_r29, arg0->unk_D0, &spF8);
                    fn_1_8814(arg0, 0, &spF8);
                    if (arg0->unk_00.unk_3C & 1) {
                        arg0->unk_10C = 20.0f + (20.0f * (arg0->unk_184 & 1));
                    }
                    var_f31 = arg0->unk_00.unk_6C.x - arg0->unk_D0->unk_2C.x;
                    var_f30 = arg0->unk_00.unk_6C.z - arg0->unk_D0->unk_2C.z;
                    spD0 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
                    if ((200.0f > spD0) || (arg0->unk_00.unk_4C > 0x14) || (arg0->unk_00.unk_48 > 0xC8)) {
                        arg0->unk_00.unk_28 |= 0x100;
                        arg0->unk_00.unk_2C |= 0x100;
                    }
                    if (50.0f > spD0) {
                        arg0->unk_00.unk_20 = 0;
                        arg0->unk_00.unk_24 = 0;
                    }
                    if (0.0f < arg0->unk_10C) {
                        arg0->unk_00.unk_20 = 0;
                        arg0->unk_00.unk_24 = 0;
                        arg0->unk_00.unk_28 &= 0xFFFFFEFF;
                        arg0->unk_00.unk_2C &= 0xFFFFFEFF;
                    }
                }
                break;
            case 3:
                var_r30 = fn_1_85AC(arg0, var_r29);
                break;
        }
        if ((var_r20 != 0) && (NULL != var_r30)) {
            fn_1_906C(arg0, var_r30);
        }
    }
}

float fn_1_A974(UnkM432DllStruct *var_r31)
{
    Vec sp14;
    Vec sp8;

    sp14 = var_r31->unk_00.unk_6C;
    sp14.y = lbl_1_bss_0[var_r31->unk_184 >> 1].unk_28.y;
    Hu3D3Dto2D(&sp14, lbl_1_data_A0[var_r31->unk_184 >> 1], &sp8);
    return sp8.y;
}

WorkPlayerOld *fn_1_AA00(int no)
{
    return &((UnkM432DllStruct *)lbl_1_bss_410[no]->data)->unk_00;
}

void fn_1_AA1C(omObjData *object)
{
    float var_f31;
    UnkM432DllStruct *var_r31;
    UnkM432DllBss0SubStruct *var_r30;
    s32 var_r29;

    var_r31 = object->data;
    var_f31 = lbl_1_bss_0[var_r31->unk_184 >> 1].unk_28.z - 750.0f;
    if (var_f31 > var_r31->unk_00.unk_6C.z) {
        var_r31->unk_00.unk_6C.z = var_f31;
    }
    var_f31 = 900.0f + lbl_1_bss_0[var_r31->unk_184 >> 1].unk_28.z;
    if (var_f31 < var_r31->unk_00.unk_6C.z) {
        var_r31->unk_00.unk_6C.z = var_f31;
    }
    if (var_r31->unk_15C < var_r31->unk_00.unk_6C.z) {
        var_r31->unk_00.unk_6C.z = var_r31->unk_15C;
    }
    var_r30 = lbl_1_bss_0[var_r31->unk_184 >> 1].unk_10[var_r31->unk_184 & 1];
    if ((var_r31->unk_184 & 1) != 0) {
        lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1E0 = 0.0f;
    }
    for (var_r29 = 0; var_r29 < 0x1F; var_r29++, var_r30++) {
        if ((var_r31->unk_17C <= var_r29) && ((var_r30->unk_14 & 1) != 0)) {
            var_f31 = 170.0f + var_r30->unk_2C.z;
            if (var_f31 > var_r31->unk_00.unk_6C.z) {
                var_r31->unk_00.unk_6C.z = var_f31;
            }
            if ((var_r31->unk_184 & 1) && (lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1E0 > (var_r30->unk_2C.z - 170.0f))) {
                lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1E0 = var_r30->unk_2C.z - 170.0f;
            }
        }
    }
    if (((var_r31->unk_184 & 1) == 0) && (lbl_1_bss_0[var_r31->unk_184 >> 1].unk_28.x < var_r31->unk_00.unk_6C.x)
        && (0.0f > lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1E0) && (lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1E0 < var_r31->unk_00.unk_6C.z)) {
        var_r31->unk_00.unk_6C.z = lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1E0;
    }
}

Vec *fn_1_ACC8(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f27;

    UnkM432DllStruct *var_r31;
    UnkBss0Struct *var_r30;
    s32 var_r29;
    UnkM432DllStruct *var_r28;

    var_r28 = object->data;
    var_r31 = var_r28;
    var_r30 = &lbl_1_bss_0[var_r28->unk_184 >> 1];
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if ((var_r31->unk_00.unk_6C.y <= var_r30->unk_88[var_r29][1].y)
            && ((var_r31->unk_00.unk_6C.y + (var_r31->unk_00.unk_BC / 2)) >= var_r30->unk_88[var_r29][1].y)) {
            var_f31 = var_r31->unk_00.unk_6C.x - var_r30->unk_88[var_r29][1].x;
            var_f30 = var_r31->unk_00.unk_6C.z - var_r30->unk_88[var_r29][1].z;
            var_f27 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
            if (var_f27 < (var_r31->unk_00.unk_BC + var_r30->unk_88[var_r29][2].y)) {
                return &var_r30->unk_88[var_r29][0];
            }
        }
    }
    return NULL;
}

void fn_1_AF28(omObjData *object)
{
    UnkM432DllStruct *var_r31 = object->data;
    var_r31->unk_16C = 0;
    var_r31->unk_00.unk_3C &= 0xFFFFFFEF;
    fn_1_4ED8(&var_r31->unk_00, 0);
}

#ifdef __MWERKS__
#include "src/REL/executor.c"
#endif

void fn_1_B234(void)
{
    UnkM432DllStruct *var_r31;
    s32 var_r30;
    u32 var_r29;
    u32 var_r28;

    if (HuPadBtn[0] & 2) {
        lbl_1_bss_57C = 300 * REFRESH_RATE;
    }
    print8(0x18, 0x20, 1.5f, "COUNT:%d MODE:%d MES:%d", lbl_1_bss_580, lbl_1_bss_41C->work[0], lbl_1_bss_576);
    print8(0x18, 0x30, 1.5f, "%f %f %f %f", lbl_1_bss_0[0].unk_64, lbl_1_bss_0[0].unk_68, lbl_1_bss_0[0].unk_6C, lbl_1_bss_0[0].unk_28.z);
    print8(0x18, 0x40, 1.5f, "%f %f %f %f", lbl_1_bss_0[1].unk_64, lbl_1_bss_0[1].unk_68, lbl_1_bss_0[1].unk_6C, lbl_1_bss_0[0].unk_28.z);
    print8(0x18, 0x50, 1.5f, "%x %x", HuMemHeapSizeGet(HEAP_SYSTEM) - HuMemUsedMallocSizeGet(HEAP_SYSTEM),
        HuMemHeapSizeGet(HEAP_DATA) - HuMemUsedMallocSizeGet(HEAP_DATA));
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r31 = lbl_1_bss_410[var_r30]->data;
        print8(0x18, (var_r30 * 0x10) + 0x70, 1.5f, "%d %d %04x %.3f (%.3f %.3f %.3f)", var_r31->unk_180, var_r31->unk_00.unk_38,
            var_r31->unk_00.unk_3C, var_r31->unk_00.unk_A8, var_r31->unk_00.unk_6C.x, var_r31->unk_00.unk_6C.y, var_r31->unk_00.unk_6C.z);
    }
}

void fn_1_B458(omObjData *object)
{
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    fn_1_24(0x1000, object->model[0]);
    omDelObjEx(lbl_1_bss_5B4, object);
    lbl_1_bss_402--;
}

void fn_1_B518(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    UnkM432DllStruct2 *var_r31;

    var_r31 = object->data;
    var_r31->unk_10 += 1.0f;
    if (30.0f <= var_r31->unk_10) {
        fn_1_B458(object);
        return;
    }
    if (10.0f > var_r31->unk_10) {
        var_f31 = var_r31->unk_10 / 10.0f;
        var_f30 = 0.0f;
    }
    else {
        var_f31 = 1.0f;
        var_f30 = (var_r31->unk_10 - 10.0f) / 20.0f;
    }
    var_f29 = sind((90.0f * var_f31)) * sind((90.0f * var_f31));
    var_f28 = sind((90.0f * var_f30)) * sind((90.0f * var_f30));
    omSetTra(object, var_r31->unk_00.x + (var_r31->unk_14 * var_f29), var_r31->unk_00.y, var_r31->unk_00.z + (var_r31->unk_18 * var_f28));
}

void fn_1_B7E4(omObjData *object)
{
    UnkM432DllStruct2 *var_r30;
    UnkBss5D0Struct *var_r29;
    UnkBss5D0Struct *var_r28;
    UnkBss5D0Struct *var_r27;
    s16 var_r26;
    s16 var_r25;
    s16 var_r24;

    var_r26 = fn_1_AC(0x1000);
    if (var_r26 < 0) {
        object->model[0] = Hu3DModelLink(lbl_1_bss_400);
    }
    else {
        object->model[0] = var_r26;
    }
    var_r30 = object->data;
    var_r30->unk_10 = 0.0f;
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(object->model[0], 3);
    omSetTra(object, var_r30->unk_00.x, var_r30->unk_00.y, var_r30->unk_00.z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, var_r30->unk_0C, var_r30->unk_0C, var_r30->unk_0C);
    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    object->func = fn_1_B518;
}

void fn_1_B974(Vec *arg0, float arg8, float arg9)
{
    UnkM432DllStruct2 *var_r31;
    omObjData *var_r30;

    if (lbl_1_bss_402 < 0xF0) {
        lbl_1_bss_402++;
        var_r30 = omAddObjEx(lbl_1_bss_5B4, 0x67, 1, 0, 3, fn_1_B7E4);
        var_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM432DllStruct2), 0x10000000);
        var_r31 = var_r30->data;
        var_r31->unk_00 = *arg0;
        var_r31->unk_00.x += 30.0f * arg9;
        var_r31->unk_0C = 1.0f + arg8;
        var_r31->unk_14 = 70.0f * arg9;
        var_r31->unk_18 = -675.0f;
    }
}

void fn_1_BAA8(UnkM432DllStruct *arg0)
{
    Vec sp20;
    Vec sp14;
    float var_f31;
    float var_f30;

    s32 *var_r29;
    s32 var_r27;

    sp20 = arg0->unk_00.unk_6C;
    sp20.y += 220.0f;
    fn_1_1A60(&sp20, lbl_1_data_A0[arg0->unk_184 >> 1], &sp14);

    arg0->unk_110 = sp14.x;
    arg0->unk_114 = sp14.y;
    if (NULL != arg0->unk_C4) {
        var_f31 = 0.0f;
        var_f30 = 0.0f;
        for (var_r29 = arg0->unk_C4, var_r27 = 1; var_r29[0] >= 0; var_r29 += 3) {
            espPosSet(arg0->unk_118[var_r29[0]], var_r29[1] + (arg0->unk_110 + var_f31), var_r29[2] + (arg0->unk_114 + var_f30));
            espDispOn(arg0->unk_118[var_r29[0]]);
            if (var_r27 != 0) {
                var_r27 = 0;
                var_f31 = var_r29[1];
                var_f30 = var_r29[2];
            }
        }
    }
}

s32 fn_1_BF08(UnkM432DllStruct *arg0)
{
    switch (arg0->unk_C8->unk_14 & 0xF00) {
        case 0x100:
            if (arg0->unk_00.unk_28 & 0x200) {
                return 0x7D4;
            }
            break;
        case 0x400:
            if (arg0->unk_00.unk_28 & 0x800) {
                return 0x7D5;
            }
            break;
        case 0x200:
            if (arg0->unk_00.unk_28 & 0x400) {
                return 0x7D5;
            }
            break;
        case 0x800:
            return 0x7D6;
    }
    return 0x7D3;
}

void fn_1_BF9C(UnkM432DllStruct *arg0)
{
    Vec spC;
    float var_f31;
    float var_f30;
    float var_f26;

    UnkM432DllStruct *var_r31;

    var_r31 = arg0;
    var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 180.0f + arg0->unk_C8->unk_18, 0.4f);
    fn_1_52B8(arg0->unk_C8, &spC);
    var_f31 = spC.x - var_r31->unk_00.unk_6C.x;
    var_f30 = spC.z - var_r31->unk_00.unk_6C.z;
    var_f26 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    if (10.0f <= var_f26) {
        var_f31 = 10.0f * (var_f31 / var_f26);
        var_f30 = 10.0f * (var_f30 / var_f26);
    }
    var_r31->unk_00.unk_6C.x += var_f31;
    var_r31->unk_00.unk_6C.z += var_f30;
}

void fn_1_C33C(UnkM432DllStruct *arg0)
{
    Vec spC;
    float sp8;
    float var_f31;
    float var_f30;
    float var_f27;
    UnkM432DllBss0SubStruct *var_r30;
    s32 var_r29;
    s32 *var_r28;
    UnkM432DllStruct *var_r27;

    var_r28 = NULL;
    if (arg0->unk_00.unk_38 == 0) {
        for (var_r30 = lbl_1_bss_0[arg0->unk_184 >> 1].unk_10[arg0->unk_184 & 1], var_r29 = 0; var_r29 < 0x1F; var_r29++, var_r30++)
            if ((arg0->unk_17C <= var_r29) && (var_r30->unk_14 & 0xF00) && (((var_r30->unk_14 & 0x700) == 0) || !(20.0f < arg0->unk_00.unk_6C.y))) {
                fn_1_52B8(var_r30, &spC);
                var_f31 = spC.x - arg0->unk_00.unk_6C.x;
                var_f30 = spC.z - arg0->unk_00.unk_6C.z;
                var_f27 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
                if (arg0->unk_00.unk_BC > var_f27) {
                    var_r27 = fn_1_51A8(arg0->unk_184 ^ 1);
                    if ((NULL == var_r27->unk_C8) || (var_r30->unk_08 != var_r27->unk_C8->unk_08)) {
                        arg0->unk_C8 = var_r30;
                        switch (var_r30->unk_14 & 0xF00) {
                            case 0x100:
                                var_r28 = lbl_1_data_2AC;
                                break;
                            case 0x200:
                                var_r28 = lbl_1_data_2D0;
                                break;
                            case 0x400:
                                var_r28 = lbl_1_data_2F4;
                                break;
                            case 0x800:
                                var_r28 = lbl_1_data_318;
                                break;
                        }
                        break;
                    }
                }
            }
    }

    if (arg0->unk_C4 != var_r28) {
        arg0->unk_C4 = var_r28;
        if (NULL == var_r28) {
            arg0->unk_C8 = NULL;
        }
        for (var_r29 = 0; var_r29 < 9; var_r29++) {
            espDispOff(arg0->unk_118[var_r29]);
        }
    }
}

void fn_1_C724(UnkM432DllStruct *var_r31, omObjData *var_r25, omObjData *var_r24)
{
    Vec spC;
    float var_f25;

    UnkBss0Struct *var_r30;
    UnkM432DllStruct *var_r29;
    s32 var_r28;
    void *var_r27;
    s32 var_r26;
    float var_f19;

    var_r30 = &lbl_1_bss_0[var_r31->unk_184 >> 1];
    fn_1_BF9C(var_r31);
    if (fn_1_BF08(var_r31) == 0x7D4) {
        var_r30->unk_1D4 += 1.0f - (2.0f * (var_r31->unk_14C / REFRESH_RATE));
        if (0.0f > var_r30->unk_1D4) {
            var_r30->unk_1D4 = 0.0f;
        }
        if (1.0f < var_r30->unk_1D4) {
            var_r30->unk_1D4 = 1.0f;
        }
        var_r31->unk_14C = 0.0f;
        if (25.0f <= (var_r31->unk_C8->unk_38 += 1.0f)) {
            var_r31->unk_C8->unk_38 = 25.0f;
        }
        omVibrate(var_r31->unk_188, 0xC, 6, 6);
    }
    else {
        var_r31->unk_14C += 1.0f;
        var_r30->unk_1D4 -= 1.0f / REFRESH_RATE;
        if (0.0f > var_r30->unk_1D4) {
            var_r30->unk_1D4 = 0.0f;
        }
        if (20.0f <= var_r31->unk_14C) {
            var_r31->unk_14C = 0.0f;
            if (0.0f >= (var_r31->unk_C8->unk_38 -= 1.0f)) {
                var_r31->unk_C8->unk_38 = 0.0f;
            }
        }
    }
    HuAudFXPitchSet(var_r30->unk_1CC, (s32)(8191.0f * var_r30->unk_1D4));
    HuAudFXPitchSet(var_r30->unk_1D0, (s32)(8191.0f * (1.0f - (var_r31->unk_C8->unk_38 / 25.0f))));
    if (Hu3DMotionShiftIDGet(var_r25->model[0]) < 0) {
        var_f25 = var_r31->unk_C8->unk_38 * (Hu3DMotionMaxTimeGet(var_r25->model[0]) / 25.0f);
        Hu3DMotionTimeSet(var_r25->model[0], var_f25);
        var_f25 = var_r31->unk_C8->unk_38 * (Hu3DMotionMaxTimeGet((var_r24->model[var_r31->unk_C8->unk_08])) / 25.0f);
        Hu3DMotionTimeSet(var_r24->model[var_r31->unk_C8->unk_08], var_f25);
    }
    if ((25.0f <= var_r31->unk_C8->unk_38) || (var_r31->unk_C8->unk_38 == 0.0f)) {
        if (25.0f <= var_r31->unk_C8->unk_38) {
            var_r31->unk_17C++;
        }
        var_r31->unk_180 = 0x7D3;
        fn_1_4ED8(&var_r31->unk_00, 0);
        HuAudFXStop(var_r30->unk_1CC);
        HuAudFXStop(var_r30->unk_1D0);
        var_r30->unk_1CC = -1;
        var_r30->unk_1D0 = -1;
    }
}

void fn_1_D0E0(UnkM432DllStruct *arg0, omObjData *arg1, omObjData *arg2)
{
    fn_1_BF9C(arg0);
    if (fn_1_BF08(arg0) == 0x7D5) {
        lbl_1_bss_0[arg0->unk_184 >> 1].unk_1DC += 1.0f - (2.0f * (arg0->unk_14C / REFRESH_RATE));
        if (0.0f > lbl_1_bss_0[arg0->unk_184 >> 1].unk_1DC) {
            lbl_1_bss_0[arg0->unk_184 >> 1].unk_1DC = 0.0f;
        }
        if (1.0f < lbl_1_bss_0[arg0->unk_184 >> 1].unk_1DC) {
            lbl_1_bss_0[arg0->unk_184 >> 1].unk_1DC = 1.0f;
        }
        arg0->unk_14C = 0.0f;
        arg0->unk_C8->unk_3C += 3.0f;
        omVibrate(arg0->unk_188, 0xC, 6, 6);
    }
    else {
        arg0->unk_14C += 1.0f;
    }
    if (Hu3DMotionShiftIDGet(arg1->model[0]) < 0) {
        Hu3DMotionTimeSet(arg1->model[0], 120.0 * (fmod(arg0->unk_C8->unk_38, 360.0) / 360.0));
        Hu3DMotionTimeSet(
            arg2->model[arg0->unk_C8->unk_08], Hu3DMotionMaxTimeGet(arg2->model[arg0->unk_C8->unk_08]) * (fmod(arg0->unk_C8->unk_38, 360.0) / 360.0));
    }
    if (20.0f <= arg0->unk_14C) {
        arg0->unk_180 = 0x7D3;
        fn_1_4ED8(&arg0->unk_00, 0);
    }
    else if (lbl_1_bss_0[arg0->unk_184 >> 1].unk_1D8 < 0) {
        lbl_1_bss_0[arg0->unk_184 >> 1].unk_1DC = 0.5f;
        lbl_1_bss_0[arg0->unk_184 >> 1].unk_1D8 = HuAudFXPlay((arg0->unk_184 & 2) == 0 ? 0x68E : 0x68F);
    }
}

void fn_1_D9EC(UnkM432DllStruct *arg0, omObjData *arg1, omObjData *arg2)
{
    float var_f28;
    float var_f27;
    float var_f23;

    fn_1_BF9C(arg0);
    if ((arg0->unk_00.unk_30 <= 0) || (arg0->unk_00.unk_34 <= 0)) {
        var_f27 = 0.0f;
        if (arg0->unk_00.unk_30 > 0) {
            var_f27 = -(arg0->unk_00.unk_30 / 150.0f);
        }
        if (arg0->unk_00.unk_34 > 0) {
            var_f27 = arg0->unk_00.unk_34 / 150.0f;
        }
        if (var_f27 != 0.0f) {
            if ((0.0f > var_f27 ? -1 : 1) != (0.0f > arg0->unk_150 ? -1 : 1)) {
                var_f28 = arg0->unk_158 - arg0->unk_154;
                if (0.0f < var_f28) {
                    if (0.98f < var_f28) {
                        var_f28 += 0.6f;
                        if ((arg0->unk_184 & 2) == 0) {
                            HuAudFXPlay(0x692);
                        }
                        else {
                            HuAudFXPlay(0x693);
                        }
                    }
                    arg0->unk_C8->unk_38 += 10.0f * var_f28;
                    var_f23 = var_f28;
                    if (0.5f > var_f23) {
                        var_f23 = 0.0f;
                    }
                    fn_1_B974(&arg0->unk_C8->unk_2C, var_f23 / 2, (arg0->unk_184 & 1) ? -1.0f : 1.0f);
                }
                arg0->unk_154 = arg0->unk_158;
            }
            arg0->unk_150 = var_f27;
            arg0->unk_158 = arg0->unk_158 + (0.1f * arg0->unk_150);
            if (0.0f > arg0->unk_158) {
                arg0->unk_158 = 0.0f;
            }
            if (1.0f < arg0->unk_158) {
                arg0->unk_158 = 1.0f;
            }
        }
    }
    if (Hu3DMotionShiftIDGet(arg1->model[0]) < 0) {
        Hu3DMotionTimeSet(arg1->model[0], arg0->unk_158 * Hu3DMotionMaxTimeGet(arg1->model[0]));
        Hu3DMotionTimeSet(arg2->model[arg0->unk_C8->unk_08], arg0->unk_158 * Hu3DMotionMaxTimeGet(arg2->model[arg0->unk_C8->unk_08]));
    }
    if (1000.0f <= lbl_1_bss_0[arg0->unk_184 >> 1].unk_124) {
        arg0->unk_180 = 0x7D3;
        fn_1_4ED8(&arg0->unk_00, 0);
    }
}

void fn_1_E3B4(UnkM432DllStruct *arg0, omObjData *arg1)
{
    float var_f31;
    float var_f30;
    s32 var_r28;

    if (arg0->unk_00.unk_38 != 0) {
        fn_1_40C0(&arg0->unk_00);
        return;
    }
    if (arg0->unk_C8->unk_14 & 0x18) {
        if (((arg0->unk_C8->unk_14 & 8) && (arg0->unk_178 <= 0)) || ((arg0->unk_C8->unk_14 & 0x10) && (arg0->unk_178 <= 1))) {
            arg0->unk_178++;
            omVibrate(arg0->unk_188, 0xC, 4, 2);
            if ((arg0->unk_184 & 2) == 0) {
                HuAudFXPlay(0x690);
            }
            else {
                HuAudFXPlay(0x691);
            }
        }
        if ((arg0->unk_184 & 1) != 0) {
            var_r28 = 1;
        }
        else {
            var_r28 = -1;
        }
        arg0->unk_170 = var_r28 * 0x18;
        arg0->unk_174 = 0x48;
        arg0->unk_00.unk_9C = 180.0f;
        if ((((arg0->unk_C8->unk_14 & 8) == 0) || !(-11100.0f < lbl_1_bss_0[arg0->unk_184 >> 1].unk_28.z))
            && (((arg0->unk_C8->unk_14 & 0x10) == 0) || !(-13500.0f < lbl_1_bss_0[arg0->unk_184 >> 1].unk_28.z))) {
            var_f30 = 800.0f - (400.0f * (arg0->unk_184 & 1));
            if (0.0f > (lbl_1_bss_0[arg0->unk_184 >> 1].unk_74 - lbl_1_bss_0[arg0->unk_184 >> 1].unk_28.z)) {
                var_f31 = -(lbl_1_bss_0[arg0->unk_184 >> 1].unk_74 - lbl_1_bss_0[arg0->unk_184 >> 1].unk_28.z);
            }
            else {
                var_f31 = lbl_1_bss_0[arg0->unk_184 >> 1].unk_74 - lbl_1_bss_0[arg0->unk_184 >> 1].unk_28.z;
            }
            if (!(var_f30 < var_f31)) {
                fn_1_5148(arg0);
                HuAudCharVoicePlay(arg0->unk_18C, 0x122);
                goto block_26;
            }
        }
    }
    else {
        arg0->unk_170 = 0;
        arg0->unk_174 = -0x48;
        arg0->unk_00.unk_9C = 0.0f;
    block_26:
        arg0->unk_D0 = 0;
        arg0->unk_D4[arg0->unk_FC] = arg0->unk_C8->unk_44 - arg0->unk_17C;
        arg0->unk_FC = (arg0->unk_FC + 1) % 10;
        arg0->unk_180 = 0x7D8;
        arg0->unk_00.unk_6C = arg0->unk_C8->unk_2C;
        arg0->unk_00.unk_6C.y -= 200.0f;
        fn_1_4ED8(&arg0->unk_00, 3);
        arg0->unk_00.unk_3C |= 8;
    }
}

void fn_1_E9E4(UnkM432DllStruct *arg0)
{
    float var_f31;
    float var_f30;
    float var_f28;

    arg0->unk_00.unk_20 = arg0->unk_170;
    arg0->unk_00.unk_24 = arg0->unk_174;
    arg0->unk_00.unk_28 = 0x100;
    arg0->unk_00.unk_2C = 0x100;
    fn_1_40C0(&arg0->unk_00);
    var_f31 = arg0->unk_C8->unk_2C.x - arg0->unk_00.unk_6C.x;
    var_f30 = arg0->unk_C8->unk_2C.z - arg0->unk_00.unk_6C.z;
    if (sqrtf((var_f31 * var_f31) + (var_f30 * var_f30)) < 100.0f) {
        var_f28 = 0.0f;
        if (arg0->unk_174 > 0) {
            var_f28 = 100.0f;
        }
        if ((arg0->unk_C8->unk_2C.y + var_f28) > arg0->unk_00.unk_6C.y) {
            arg0->unk_00.unk_84.y = _1606_BY_REFRESH_RATE;
            arg0->unk_00.unk_A4 = 1.0f;
            return;
        }
        arg0->unk_00.unk_3C &= 0xFFFFFFF7;
        return;
    }
    if ((0.0f > arg0->unk_00.unk_84.y) && ((100.0f + arg0->unk_C8->unk_2C.y) > arg0->unk_00.unk_6C.y)) {
        arg0->unk_180 = 0x7D3;
        HuAudCharVoicePlay(arg0->unk_18C, 0x10D);
    }
}

void fn_1_EC7C(UnkM432DllStruct *arg0, omObjData *arg1)
{
    if ((lbl_1_bss_0[arg0->unk_184 >> 1].unk_1E4 - (arg0->unk_00.unk_BC / 2)) > arg0->unk_00.unk_6C.y) {
        Hu3DModelShadowDispOff(arg1->model[0]);
        return;
    }
    Hu3DModelShadowDispOn(arg1->model[0]);
}

void fn_1_ED0C(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f26;
    UnkBss0Struct *var_r28;
    UnkM432DllStruct *var_r31;
    s32 var_r26;
    s32 var_r22;

    var_r31 = object->data;
    var_r28 = &lbl_1_bss_0[var_r31->unk_184 >> 1];
    if (lbl_1_bss_41C->work[0] >= 0x3EC) {
        if (lbl_1_bss_3FC != (var_r31->unk_184 & 2)) {
            var_r26 = 1;
            if (var_r31->unk_00.unk_A8 < var_r31->unk_00.unk_6C.y) {
                var_r26 = 0;
            }
            if (var_r31->unk_180 == 0x7D7) {
                var_r26 = 0;
            }
            if (var_r31->unk_180 == 0x7D8) {
                var_r26 = 0;
            }
            if (var_r31->unk_180 == 0x7D9) {
                var_r26 = 0;
            }
            if ((var_r31->unk_180 == 0x7D3) && (var_r31->unk_00.unk_38 == 1)) {
                var_r26 = 0;
            }
            if (var_r26 != 0) {
                var_r31->unk_180 = 0x7DA;
                if (lbl_1_bss_3FC >= 0) {
                    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
                    Hu3DMotionShiftSet(object->model[0], object->motion[10], 0.0f, 8.0f, HU3D_ATTR_NONE);
                }
                else {
                    var_r31->unk_168 = 1;
                    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
                    Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
            }
        }
        else {
            var_r31->unk_180 = 0x7DB;
            var_r31->unk_13C.x += 100.0f * (var_r31->unk_184 & 1 ? -1.0f : 1.0f);
            var_r31->unk_13C.z += -475.0f;
            Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
            Hu3DMotionShiftSet(object->model[0], object->motion[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        }
        if (var_r31->unk_180 >= 0x7DA) {
            for (var_r22 = 0; var_r22 < 9; var_r22++) {
                espDispOff(var_r31->unk_118[var_r22]);
            }
            if (lbl_1_bss_3FC == (var_r31->unk_184 & 2)) {
                GWPlayerCoinWinSet(var_r31->unk_188, 10);
            }
            object->func = fn_1_10250;
            return;
        }
    }
    if (GWPlayerCfg[var_r31->unk_188].iscom != 0) {
        var_r31->unk_00.unk_20 = 0;
        var_r31->unk_00.unk_24 = 0;
        var_r31->unk_00.unk_28 = 0;
        var_r31->unk_00.unk_2C = 0;
        var_r31->unk_00.unk_30 = 0;
        var_r31->unk_00.unk_34 = 0;
        fn_1_93BC(var_r31);
    }
    else {
        var_r31->unk_00.unk_20 = HuPadStkX[var_r31->unk_190];
        var_r31->unk_00.unk_24 = HuPadStkY[var_r31->unk_190];
        var_r31->unk_00.unk_28 = HuPadBtnDown[var_r31->unk_190];
        var_r31->unk_00.unk_2C = HuPadBtn[var_r31->unk_190];
        var_r31->unk_00.unk_30 = HuPadTrigL[var_r31->unk_190];
        var_r31->unk_00.unk_34 = HuPadTrigR[var_r31->unk_190];
    }
    if ((var_r31->unk_180 == 0x7D3) && ((var_r31->unk_13C.x != 0.0f) || (var_r31->unk_13C.z != 0.0f))) {
        var_f30 = var_r31->unk_13C.x - var_r31->unk_00.unk_6C.x;
        var_f31 = var_r31->unk_13C.z - var_r31->unk_00.unk_6C.z;
        if (var_r31->unk_00.unk_BC < ABS(var_f31)) {
            var_f30 = 0.0f;
        }
        var_f26 = sqrtf((var_f30 * var_f30) + (var_f31 * var_f31));
        if (10.0f <= var_f26) {
            var_f30 /= var_f26;
            var_f31 /= var_f26;
        }
        else {
            var_f30 = 0.0f;
            var_f31 = 0.0f;
            var_r31->unk_00.unk_9C = var_r31->unk_148;
        }
        var_r31->unk_00.unk_20 = 72.0f * var_f30;
        var_r31->unk_00.unk_24 = 72.0f * -var_f31;
        var_r31->unk_00.unk_28 = 0;
        var_r31->unk_00.unk_2C = 0;
        var_r31->unk_00.unk_30 = 0;
        var_r31->unk_00.unk_34 = 0;
    }
    switch (var_r31->unk_180) {
        case 0x7D3:
            if ((var_r31->unk_16C != 0) && ((var_r31->unk_00.unk_3C & 0x101) != 0)) {
                var_r31->unk_16C = 0;
                var_r31->unk_00.unk_3C &= 0xFFFFFFEF;
                fn_1_4ED8(&var_r31->unk_00, 0);
            }
            fn_1_40C0(&var_r31->unk_00);
            fn_1_C33C(var_r31);
            if ((NULL != var_r31->unk_C4) && (NULL != var_r31->unk_C8)) {
                var_r31->unk_180 = fn_1_BF08(var_r31);
                switch (var_r31->unk_180) {
                    case 0x7D4:
                        var_r31->unk_14C = 0.0f;
                        var_r31->unk_C8->unk_38 = 1.0f;
                        var_r28->unk_1D4 = 0.5f;
                        if (var_r28->unk_1CC < 0) {
                            var_r28->unk_1CC = HuAudFXPlay((var_r31->unk_184 & 2) == 0 ? 0x68C : 0x68D);
                        }
                        if (var_r28->unk_1D0 < 0) {
                            var_r28->unk_1D0 = HuAudFXPlay((var_r31->unk_184 & 2) == 0 ? 0x695 : 0x696);
                        }
                        Hu3DMotionShiftSet(object->model[0], object->motion[5], 0.0f, 8.0f, HU3D_MOTATTR_PAUSE);
                        break;
                    case 0x7D5:
                        var_r31->unk_14C = 0.0f;
                        var_r31->unk_C8->unk_3C += 3.0f;
                        if (var_r28->unk_1D8 < 0) {
                            var_r28->unk_1DC = 0.5f;
                            var_r28->unk_1D8 = HuAudFXPlay((var_r31->unk_184 & 2) == 0 ? 0x68E : 0x68F);
                        }
                        Hu3DMotionShiftSet(
                            object->model[0], object->motion[7], 120.0 * (fmod(var_r31->unk_C8->unk_38, 360.0) / 360.0), 8.0f, HU3D_MOTATTR_PAUSE);
                        break;
                    case 0x7D6:
                        var_r31->unk_14C = 0.0f;
                        var_r31->unk_150 = -1.0f;
                        var_r31->unk_158 = 0.0f;
                        var_r31->unk_154 = 0.0f;
                        Hu3DMotionShiftSet(object->model[0], object->motion[8], 0.0f, 8.0f, HU3D_MOTATTR_PAUSE);
                        break;
                }
            }
            else if (-800.0f > var_r31->unk_00.unk_6C.y) {
                var_r31->unk_00.unk_3C |= 0x10;
                if (NULL == lbl_1_bss_0[var_r31->unk_184 >> 1].unk_08) {
                    lbl_1_bss_0[var_r31->unk_184 >> 1].unk_08 = object;
                    lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1B4 = -1;
                }
                else {
                    lbl_1_bss_0[var_r31->unk_184 >> 1].unk_0C = object;
                }
            }
            break;
        case 0x7D4:
            fn_1_C724(var_r31, object, lbl_1_bss_0[var_r31->unk_184 >> 1].unk_04);
            break;
        case 0x7D5:
            fn_1_D0E0(var_r31, object, lbl_1_bss_0[var_r31->unk_184 >> 1].unk_04);
            break;
        case 0x7D6:
            fn_1_D9EC(var_r31, object, lbl_1_bss_0[var_r31->unk_184 >> 1].unk_04);
            break;
        case 0x7D7:
            fn_1_E3B4(var_r31, object);
            break;
        case 0x7D8:
            fn_1_E9E4(var_r31);
            break;
        case 0x7D9:
            break;
        default:
            OSReport("*** player mode error(%d)!!\n", var_r31->unk_180);
            break;
    }
    fn_1_EC7C(var_r31, object);
    fn_1_BAA8(var_r31);

    lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1E8 += 1.0f;

    lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1EC += fn_1_A974(var_r31);
    lbl_1_bss_0[var_r31->unk_184 >> 1].unk_1F0[var_r31->unk_184 & 1] = var_r31->unk_00.unk_6C.z;
    fn_1_2DD4(&var_r31->unk_00);
}

void fn_1_10250(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f24;
    UnkM432DllStruct *var_r31;
    omObjData *var_r29;

    var_r31 = object->data;
    var_r29 = lbl_1_bss_0[var_r31->unk_184 >> 1].unk_04;
    switch (var_r31->unk_180) {
        case 0x7D0:
            if (lbl_1_bss_41C->work[0] >= 0x3E9) {
                var_r31->unk_180++;
                Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
                HuAudCharVoicePlay(var_r31->unk_18C, 0x125);
            }
            break;
        case 0x7D1:
            var_r31->unk_00.unk_20 = 0;
            var_r31->unk_00.unk_24 = 0x48;
            var_r31->unk_00.unk_28 = 0x100;
            var_r31->unk_00.unk_2C = 0x100;
            fn_1_40C0(&var_r31->unk_00);
            if (200.0f > var_r31->unk_00.unk_6C.y) {
                var_r31->unk_00.unk_84.y = _1606_BY_REFRESH_RATE;
                var_r31->unk_00.unk_A4 = 1.0f;
            }
            else {
                var_r31->unk_180++;
            }
            break;
        case 0x7D2:
            var_r31->unk_00.unk_20 = 0;
            var_r31->unk_00.unk_24 = 0;
            var_r31->unk_00.unk_28 = 0;
            var_r31->unk_00.unk_2C = 0;
            if (var_r31->unk_00.unk_38 == 1) {
                var_r31->unk_00.unk_24 = 0x48;
            }
            fn_1_40C0(&var_r31->unk_00);
            if ((var_r31->unk_00.unk_38 == 0) && (lbl_1_bss_41C->work[0] >= 0x3EB)) {
                var_r31->unk_180++;
                object->func = fn_1_ED0C;
            }
            break;
        case 0x7DA:
            if ((var_r31->unk_168 != 0) && (lbl_1_bss_3FC < 0) && (lbl_1_bss_41C->work[0] >= 0x3F1)) {
                var_r31->unk_168 = 0;
                Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
                Hu3DMotionShiftSet(object->model[0], object->motion[10], 0.0f, 8.0f, HU3D_ATTR_NONE);
            }
            break;
        case 0x7DB:
            var_f31 = var_r31->unk_13C.x - var_r31->unk_00.unk_6C.x;
            var_f30 = var_r31->unk_13C.z - var_r31->unk_00.unk_6C.z;
            if (1.0f > ABS(var_f31)) {
                if (1.0f > ABS(var_f30)) {
                    var_r31->unk_180++;
                    var_r31->unk_160 = 0.0f;
                    var_r31->unk_164 = var_r31->unk_00.unk_6C.y;
                    Hu3DMotionShiftSet(object->model[0], object->motion[3], 0.0f, 8.0f, HU3D_ATTR_NONE);
                    break;
                }
            }
            if (1.0f < ABS(var_f31)) {
                var_f30 = 0.0f;
            }
            var_f24 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
            if (10.0f < var_f24) {
                var_f31 = 10.0f * (var_f31 / var_f24);
                var_f30 = 10.0f * (var_f30 / var_f24);
            }
            var_r31->unk_00.unk_6C.x += var_f31;
            var_r31->unk_00.unk_6C.z += var_f30;

            var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, atan2d(var_f31, var_f30), 0.4f);
            break;
        case 0x7DC:
            var_r31->unk_160 += 5.0f;
            var_r31->unk_00.unk_6C.z -= 10.0f;
            var_r31->unk_00.unk_6C.y = lbl_1_bss_0[var_r31->unk_184 >> 1].unk_118.y + (120.0 * sind(var_r31->unk_160));
            if (180.0f <= var_r31->unk_160) {
                var_r31->unk_180++;
                Hu3DMotionShiftSet(object->model[0], object->motion[4], 0.0f, 8.0f, HU3D_ATTR_NONE);
            }
            break;
        case 0x7DD:
            if ((Hu3DMotionShiftIDGet(object->model[0]) < 0) && (Hu3DMotionEndCheck(object->model[0]) != 0)) {
                var_r31->unk_180++;
                Hu3DMotionShiftSet(object->model[0], object->motion[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(var_r29->model[9], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(var_r29->model[15], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(var_r29->model[23], HU3D_MOTATTR_PAUSE);
                HuAudFXPlay(0x694);
            }
            break;
        case 0x7DE:
            var_r31->unk_00.unk_9C = fn_1_1E20(var_r31->unk_00.unk_9C, 0.0f, 0.4f);
            if ((Hu3DMotionEndCheck(var_r29->model[9]) != 0) && (Hu3DMotionEndCheck(var_r29->model[15]) != 0)) {
                var_r31->unk_180++;
            }
            break;
        case 0x7DF:
            var_r31->unk_00.unk_6C.y = lbl_1_bss_0[var_r31->unk_184 >> 1].unk_118.y;
            if (lbl_1_bss_41C->work[0] >= 0x3F1) {
                var_r31->unk_180++;
                Hu3DMotionShiftSet(object->model[0], object->motion[9], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                HuAudCharVoicePlay(var_r31->unk_18C, 0x125);
            }
            break;
        case 0x7E0:
            var_r31->unk_00.unk_6C.y = lbl_1_bss_0[var_r31->unk_184 >> 1].unk_118.y;
            break;
        case 0x7D3:
        case 0x7D4:
        case 0x7D5:
        case 0x7D6:
        case 0x7D7:
        case 0x7D8:
        case 0x7D9:
        default:
            OSReport("*** player mode error(%d)!!\n", var_r31->unk_180);
            break;
    }
    fn_1_EC7C(var_r31, object);
    fn_1_2DD4(&var_r31->unk_00);
}

void fn_1_10CCC(omObjData *object)
{
    Vec sp8;

    UnkM432DllStruct *var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    UnkM432DllBss0SubStruct *var_r26;
    s32 var_r24;
    s32 var_r23;

    var_r31 = object->data;
    var_r26 = lbl_1_bss_0[var_r31->unk_184 >> 1].unk_10[var_r31->unk_184 & 1];
    var_r31->unk_18C = GWPlayerCfg[var_r31->unk_188].character;
    var_r31->unk_190 = GWPlayerCfg[var_r31->unk_188].pad_idx;
    var_r31->unk_180 = 0x7D0;
    var_r31->unk_168 = 0;
    var_r31->unk_CC = NULL;
    var_r31->unk_C4 = NULL;
    var_r31->unk_C8 = NULL;
    var_r31->unk_150 = 0.0f;
    var_r31->unk_158 = 0.0f;
    var_r31->unk_154 = 0.0f;
    var_r31->unk_17C = 0;
    var_r31->unk_15C = 10000.0f;
    var_r31->unk_178 = 0;
    var_r31->unk_16C = 0;
    var_r31->unk_104 = 0.5f;
    var_r31->unk_108 = 0.0f;
    fn_1_5148(var_r31);
    sp8 = var_r26[var_r31->unk_17C++].unk_2C;
    sp8.y -= 200.0f;
    fn_1_2C1C(&var_r31->unk_00, object, var_r31->unk_188, var_r31->unk_18C, lbl_1_data_268, 0, &sp8, 180.0f);
    var_r31->unk_00.unk_04 = fn_1_AA1C;
    var_r31->unk_00.unk_08 = fn_1_ACC8;
    fn_1_2DC8(&var_r31->unk_00, 1, (var_r31->unk_184 & 2) == 0 ? lbl_1_data_354 : lbl_1_data_36C);
    var_r31->unk_00.unk_0C = fn_1_AF28;
    var_r31->unk_13C.x = 0.0f;
    var_r31->unk_13C.y = 0.0f;
    var_r31->unk_13C.z = 0.0f;
    object->model[0] = CharModelCreate(lbl_1_data_0[var_r31->unk_18C], 4);
    CharModelStepTypeSet(lbl_1_data_0[var_r31->unk_18C], 0);
    for (var_r29 = 0; var_r29 < 0xB; var_r29++) {
        object->motion[var_r29] = CharModelMotionCreate(lbl_1_data_0[var_r31->unk_18C], lbl_1_data_108[var_r31->unk_18C][var_r29]);
        CharModelMotionSet(lbl_1_data_0[var_r31->unk_18C], object->motion[var_r29]);
    }
    Hu3DModelCameraSet(object->model[0], lbl_1_data_A0[var_r31->unk_184 >> 1]);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->model[0], 2);
    Hu3DMotionSet(object->model[0], object->motion[0]);
    Hu3DModelShadowSet(object->model[0]);
    fn_1_2DD4(&var_r31->unk_00);
    for (var_r29 = 0; var_r29 < 9; var_r29++) {
        var_r31->unk_118[var_r29] = espEntry(lbl_1_data_288[var_r29], 0, 0);
        espDrawNoSet(var_r31->unk_118[var_r29], 0);
        espDispOff(var_r31->unk_118[var_r29]);
        espAttrSet(var_r31->unk_118[var_r29], HUSPR_ATTR_NOANIM);
        espBankSet(var_r31->unk_118[var_r29], 0);
        espPriSet(var_r31->unk_118[var_r29], 0x80 - var_r29);
    }
    espTPLvlSet(var_r31->unk_118[0], 0.9f);
    espTPLvlSet(var_r31->unk_118[1], 0.9f);
    if (GWPlayerCfg[var_r31->unk_188].iscom != 0) {
        switch (GWPlayerCfg[var_r31->unk_188].diff) {
            case 0:
                var_r31->unk_CC = &lbl_1_data_1794;
                break;
            case 1:
                var_r31->unk_CC = &lbl_1_data_17B4;
                break;
            case 2:
                var_r31->unk_CC = &lbl_1_data_17D4;
                break;
            case 3:
            default:
                var_r31->unk_CC = &lbl_1_data_17F4;
                break;
        }
    }
    CharModelLayerSetAll2(5);
    CharModelMotionDataClose(lbl_1_data_0[var_r31->unk_18C]);
    object->func = fn_1_10250;
}

void fn_1_113F0(omObjData *object) { }

void fn_1_113F4(omObjData *var_r31)
{
    s32 sp48;

    UnkM432DllBss0SubStruct *var_r30;
    s32 var_r28;
    UnkBss0Struct *var_r22;

    var_r22 = &lbl_1_bss_0[var_r31->work[0]];
    var_r31->model[0] = fn_1_46C(DATA_MAKE_NUM(DATADIR_M432, 0x02));
    Hu3DModelCameraSet(var_r31->model[0], lbl_1_data_A0[var_r31->work[0]]);
    Hu3DModelAttrSet(var_r31->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(var_r31->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(var_r31->model[0], 0);

    var_r31->model[1] = fn_1_46C(DATA_MAKE_NUM(DATADIR_M432, 0x04));
    Hu3DModelCameraSet(var_r31->model[1], lbl_1_data_A0[var_r31->work[0]]);
    Hu3DModelAttrSet(var_r31->model[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->model[1], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(var_r31->model[1], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(var_r31->model[1], 0);

    var_r31->model[2] = fn_1_46C(lbl_1_data_528[var_r31->work[0]]);
    Hu3DModelCameraSet(var_r31->model[2], lbl_1_data_A0[var_r31->work[0]]);
    Hu3DModelAttrSet(var_r31->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->model[2], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(var_r31->model[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(var_r31->model[2], 1);

    var_r31->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M432, 0x01));
    Hu3DModelCameraSet(var_r31->model[3], lbl_1_data_A0[var_r31->work[0]]);
    Hu3DModelAttrSet(var_r31->model[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->model[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(var_r31->model[3], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(var_r31->model[3], 0);

    var_r31->model[24] = fn_1_46C(DATA_MAKE_NUM(DATADIR_M432, 0x03));
    Hu3DModelCameraSet(var_r31->model[24], lbl_1_data_A0[var_r31->work[0]]);
    Hu3DModelLayerSet(var_r31->model[24], 0);
    Hu3DModelPosSet(var_r31->model[24], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31->model[24], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(var_r31->model[24], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->model[24], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(var_r31->model[24], HU3D_MOTATTR_LOOP);

    var_r31->model[25] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M432, 0x07));
    Hu3DMotionSet(var_r31->model[25], Hu3DJointMotionFile(var_r31->model[25], DATA_MAKE_NUM(DATADIR_M432, 0x08)));
    Hu3DModelCameraSet(var_r31->model[25], lbl_1_data_A0[var_r31->work[0]]);
    Hu3DModelAttrSet(var_r31->model[25], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->model[25], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(var_r31->model[25], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(var_r31->model[25], 2);
    Hu3DModelShadowSet(var_r31->model[25]);
    omSetTra(var_r31, var_r22->unk_28.x, 0.0f, 0.0f);
    omSetRot(var_r31, 0.0f, 0.0f, 0.0f);
    for (var_r28 = 0; var_r28 < 0x1A; var_r28++) {
        Hu3DModelPosSet(var_r31->model[var_r28], var_r22->unk_28.x, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r31->model[var_r28], 0.0f, 0.0f, 0.0f);
    }
    for (var_r28 = 0; var_r28 < 2; var_r28++) {
        var_r22->unk_10[var_r28] = HuMemDirectMallocNum(HEAP_SYSTEM, 31 * sizeof(UnkM432DllBss0SubStruct), MEMORY_DEFAULT_NUM);
        memcpy(var_r22->unk_10[var_r28], var_r28 == 0 ? &lbl_1_data_5EC : &lbl_1_data_EDC, 31 * sizeof(UnkM432DllBss0SubStruct));
        for (var_r30 = var_r22->unk_10[var_r28], sp48 = 0; sp48 < 0x1F; sp48++, var_r30++) {
            fn_1_1D18(var_r31->model[3], var_r30->unk_00, &var_r30->unk_20);
            var_r30->unk_2C = var_r30->unk_20;
            var_r30->unk_38 = 0.0f;
            var_r30->unk_3C = 0.0f;
            var_r30->unk_40 = -1;
            var_r30->unk_44 = sp48;
            if ((var_r30->unk_08 > 0) && (var_r30->unk_0C[var_r31->work[0]] != 0)) {
                var_r31->model[var_r30->unk_08] = fn_1_46C(var_r30->unk_0C[var_r31->work[0]]);
                Hu3DModelCameraSet(var_r31->model[var_r30->unk_08], lbl_1_data_A0[var_r31->work[0]]);
                Hu3DModelLayerSet(var_r31->model[var_r30->unk_08], 0);
                Hu3DModelPosSet(var_r31->model[var_r30->unk_08], var_r30->unk_2C.x, var_r30->unk_2C.y, var_r30->unk_2C.z);
                Hu3DModelRotSet(var_r31->model[var_r30->unk_08], 0.0f, var_r30->unk_18, 0.0f);
                Hu3DModelAttrSet(var_r31->model[var_r30->unk_08], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
                Hu3DModelAttrSet(var_r31->model[var_r30->unk_08], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(var_r31->model[var_r30->unk_08], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(var_r31->model[var_r30->unk_08], HU3D_ATTR_DISPOFF);
            }
        }
    }
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        lbl_1_bss_0[var_r31->work[0]].unk_88[var_r28][2].y = 35.0f;
    }
    fn_1_1D18(var_r31->model[3], "m432_00-d0", &lbl_1_bss_0[var_r31->work[0]].unk_88[0][0]);
    fn_1_1D18(var_r31->model[3], "m432_00-d0", &lbl_1_bss_0[var_r31->work[0]].unk_88[1][0]);
    fn_1_1D18(var_r31->model[3], "m432_00-d1", &lbl_1_bss_0[var_r31->work[0]].unk_88[2][0]);
    fn_1_1D18(var_r31->model[3], "m432_00-d1", &lbl_1_bss_0[var_r31->work[0]].unk_88[3][0]);

    fn_1_5364(var_r31->work[0], var_r31);

    fn_1_1D18(var_r31->model[3], "m432_00-h0", &lbl_1_bss_0[var_r31->work[0]].unk_118);
    for (var_r28 = 0; var_r28 < 8; var_r28++) {
        fn_1_1D18(var_r31->model[3], lbl_1_data_3DC[var_r28], &lbl_1_bss_0[var_r31->work[0]].unk_130[var_r28]);
        if ((var_r28 % 4) < 2) {
            lbl_1_bss_0[var_r31->work[0]].unk_130[var_r28].z -= 150.0f;
        }
    }
    fn_1_1D18(var_r31->model[3], "m432_00-n0", &lbl_1_bss_0[var_r31->work[0]].unk_1C0);
    Hu3DModelShadowMapSet(var_r31->model[0]);
    Hu3DModelShadowMapSet(var_r31->model[20]);
    Hu3DModelShadowMapSet(var_r31->model[21]);
    Hu3DModelAttrReset(var_r31->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(var_r31->model[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(var_r31->model[2], HU3D_ATTR_DISPOFF);
    var_r31->func = fn_1_113F0;
}

void fn_1_12800(omObjData *object) { }

void fn_1_12804(omObjData *object)
{
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M432, 0x00));
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    omSetTra(object, lbl_1_bss_0[object->work[0]].unk_28.x, 0.0f, 0.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    object->func = fn_1_12800;
}

void fn_1_128C8(omObjData *object)
{
    s32 var_r31;
    UnkM432DllStruct *var_r30;
    UnkM432DllStruct *var_r29;
    s32 var_r28;
    s32 var_r27;
    void *var_r26;
    void *var_r25;
    omObjData *var_r24;
    void *var_r23;
    void *var_r22;

    if (lbl_1_bss_41C->work[0] >= 0x3EB) {
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            var_r24 = lbl_1_bss_0[var_r31].unk_04;
            var_r30 = fn_1_51A8(var_r31 * 2);
            var_r29 = fn_1_51A8(var_r31 * 2 + 1);
            if ((var_r30->unk_180 == 0x7DF) && (var_r29->unk_180 == 0x7DF)) {
                lbl_1_bss_0[var_r31].unk_12C += 0.05f;
                if (12.0f < lbl_1_bss_0[var_r31].unk_12C) {
                    lbl_1_bss_0[var_r31].unk_12C = 12.0f;
                }
                lbl_1_bss_0[var_r31].unk_118.y += lbl_1_bss_0[var_r31].unk_12C;
                Hu3DModelPosSet(var_r24->model[22], lbl_1_bss_0[var_r31].unk_118.x, lbl_1_bss_0[var_r31].unk_118.y, lbl_1_bss_0[var_r31].unk_118.z);
                lbl_1_bss_0[var_r31].unk_28.y += 0.1f * ((500.0f + lbl_1_bss_0[var_r31].unk_118.y) - lbl_1_bss_0[var_r31].unk_28.y);
                lbl_1_bss_0[var_r31].unk_1C.y += 0.01f * (1000.0f - lbl_1_bss_0[var_r31].unk_1C.y);
                lbl_1_bss_0[var_r31].unk_1C.z += 0.002f * ((4000.0f + lbl_1_bss_0[var_r31].unk_118.z) - lbl_1_bss_0[var_r31].unk_1C.z);
                Hu3DCameraPosSetV(lbl_1_data_A0[var_r31], &lbl_1_bss_0[var_r31].unk_1C, &lbl_1_data_C8, &lbl_1_bss_0[var_r31].unk_28);
            }
            else {
                fn_1_623C(&lbl_1_bss_0[var_r31], var_r31, var_r30, var_r29);
                if (NULL != lbl_1_bss_0[var_r31].unk_08) {
                    fn_1_6F28(&lbl_1_bss_0[var_r31]);
                }
                if ((2.0f <= lbl_1_bss_0[var_r31].unk_1E8) && (lbl_1_bss_0[var_r31].unk_1EC != 0.0f)) {
                    fn_1_7C1C(&lbl_1_bss_0[var_r31], var_r30, var_r29);
                }
                lbl_1_bss_0[var_r31].unk_0C = NULL;
                lbl_1_bss_0[var_r31].unk_1E8 = 0.0f;
                lbl_1_bss_0[var_r31].unk_1EC = 0.0f;
                lbl_1_bss_0[var_r31].unk_1F0[0] = 0.0f;
                lbl_1_bss_0[var_r31].unk_1F0[1] = 0.0f;
            }
        }
#if VERSION_NTSC
        if (lbl_1_bss_41C->work[0] >= 0x3EC) {
            for (var_r31 = 0; var_r31 < 2; var_r31++) {
                if (lbl_1_bss_0[var_r31].unk_1CC >= 0) {
                    HuAudFXStop(lbl_1_bss_0[var_r31].unk_1CC);
                }
                if (lbl_1_bss_0[var_r31].unk_1D0 >= 0) {
                    HuAudFXStop(lbl_1_bss_0[var_r31].unk_1D0);
                }
                if (lbl_1_bss_0[var_r31].unk_1D8 >= 0) {
                    HuAudFXStop(lbl_1_bss_0[var_r31].unk_1D8);
                }
                lbl_1_bss_0[var_r31].unk_1CC = -1;
                lbl_1_bss_0[var_r31].unk_1D0 = -1;
                lbl_1_bss_0[var_r31].unk_1D8 = -1;
            }
        }
#endif
    }
}

void fn_1_12EA8(void)
{
    float var_f31;
    float var_f30;

    UnkBss0Struct *var_r31;
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31 = &lbl_1_bss_0[var_r30];
        if (var_r31->unk_7C == 0.0f) {
            var_r31->unk_1C = var_r31->unk_28;
            var_r31->unk_1C.x = var_r31->unk_1C.x + (var_r31->unk_68 * sind(var_r31->unk_64));
            var_r31->unk_1C.y += var_r31->unk_6C;
            var_r31->unk_1C.z = var_r31->unk_1C.z + (var_r31->unk_68 * cosd(var_r31->unk_64));
        }
        else {
            var_r31->unk_78 += 1.0f;
            var_f30 = var_r31->unk_78 / var_r31->unk_7C;
            var_f31 = sind((90.0f * var_f30)) * sind((90.0f * var_f30));

            var_r31->unk_1C.x = var_r31->unk_34.x + (var_f31 * (var_r31->unk_40.x - var_r31->unk_34.x));
            var_r31->unk_1C.y = var_r31->unk_34.y + (var_f31 * (var_r31->unk_40.y - var_r31->unk_34.y));
            var_r31->unk_1C.z = var_r31->unk_34.z + (var_f31 * (var_r31->unk_40.z - var_r31->unk_34.z));
            var_r31->unk_28.x = var_r31->unk_4C.x + (var_f31 * (var_r31->unk_58.x - var_r31->unk_4C.x));
            var_r31->unk_28.y = var_r31->unk_4C.y + (var_f31 * (var_r31->unk_58.y - var_r31->unk_4C.y));
            var_r31->unk_28.z = var_r31->unk_4C.z + (var_f31 * (var_r31->unk_58.z - var_r31->unk_4C.z));
            if (var_r31->unk_7C <= var_r31->unk_78) {
                var_r31->unk_68 = var_r31->unk_1C.z - var_r31->unk_28.z;
                var_r31->unk_6C = var_r31->unk_1C.y - var_r31->unk_28.y;
                var_r31->unk_78 = 0.0f;
                var_r31->unk_7C = 0.0f;
            }
        }
        Hu3DCameraPosSetV(lbl_1_data_A0[var_r30], &var_r31->unk_1C, &lbl_1_data_C8, &var_r31->unk_28);
    }
}

void fn_1_131A8(omObjData *var_r28)
{
    Vec sp98;
    Vec sp8C;
    Vec sp80;
    UnkM432DllStruct *sp7C[1];

    float var_f31;
    float var_f30;
    float var_f27;
    float var_f26;
    float var_f22;
    float var_f21;

    UnkBss0Struct *var_r29;
    s32 var_r26;
    s32 var_r17;

    if (omSysExitReq != 0) {
        fn_1_1F58(-1);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
        var_r28->func = fn_1_1615C;
    }
    lbl_1_bss_580++;
    switch (var_r28->work[0]) {
        case 0x3E8:
            if (WipeStatGet() == 0) {
                var_r28->work[0]++;
                lbl_1_bss_3F0 = 0.0f;
            }
            break;
        case 0x3E9:
            lbl_1_bss_3F0 += 1.0f;
            var_f31 = lbl_1_bss_3F0 / 60.0f;
            var_f30 = sind((90.0f * var_f31)) * sind((90.0f * var_f31));
            for (var_r26 = 0; var_r26 < 2; var_r26++) {
                lbl_1_bss_0[var_r26].unk_28.z = -300.0f + (-400.0f * var_f30);
            }
            fn_1_12EA8();
            if (60.0f <= lbl_1_bss_3F0) {
                var_r28->work[0]++;
                lbl_1_bss_3F0 = 0.0f;
            }
            break;
        case 0x3EA:
            if (lbl_1_bss_576 < 0) {
                lbl_1_bss_576 = MGSeqCreate(3, 0);
            }
            else {
                if ((lbl_1_bss_570 < 0) && ((MGSeqStatGet(lbl_1_bss_576) & 0x10) != 0)) {
                    fn_1_1F24(0x46);
                }
                if (MGSeqStatGet(lbl_1_bss_576) == 0) {
                    var_r28->work[0]++;
                    lbl_1_bss_57C = 0;
                    lbl_1_bss_576 = -1;
                    lbl_1_bss_3F0 = 0.0f;
                }
            }
            break;
        case 0x3EB:
            lbl_1_bss_57C++;
            if (lbl_1_bss_574 >= 0) {
                MGSeqParamSet(lbl_1_bss_574, 1, (300 * REFRESH_RATE + REFRESH_RATE - 1 - lbl_1_bss_57C) / REFRESH_RATE);
            }
            else if (lbl_1_bss_57C > 270 * REFRESH_RATE) {
                lbl_1_bss_574 = MGSeqCreate(1, (300 * REFRESH_RATE + REFRESH_RATE - 1 - lbl_1_bss_57C) / REFRESH_RATE, -1, -1);
                MGSeqPosSet(lbl_1_bss_574, 288.0f, 400.0f);
            }
            fn_1_580(lbl_1_bss_528, 0, lbl_1_bss_57C);

            fn_1_12EA8();
            if ((lbl_1_bss_57C >= 300 * REFRESH_RATE) || (lbl_1_bss_3FC >= 0)) {
                var_r28->work[0] = 0x3EC;
                lbl_1_bss_3F0 = 0.0f;
            }
            break;
        case 0x3EC:
            if (lbl_1_bss_576 < 0) {
                if (lbl_1_bss_574 >= 0) {
                    MGSeqParamSet(lbl_1_bss_574, 2, -1);
                }
                lbl_1_bss_574 = -1;
                lbl_1_bss_3F8 = 0;
                lbl_1_bss_576 = MGSeqCreate(3, 1);
                fn_1_1F58(0x64);
            }
            else {
                var_r17 = 0;
                for (var_r26 = 0; var_r26 < 4; var_r26++) {
                    if (((UnkM432DllStruct *)lbl_1_bss_410[var_r26]->data)->unk_180 >= 0x7DA) {
                        var_r17++;
                    }
                }
                if (++lbl_1_bss_3F8 > 0x78) {
                    var_r17 = 4;
                }
                lbl_1_bss_3F0 += 1.0f;
                if ((var_r17 >= 4) && (60.0f <= lbl_1_bss_3F0) && (MGSeqStatGet(lbl_1_bss_576) == 0)) {
                    var_r28->work[0] = 0x3EE;
                    if ((lbl_1_bss_3FC >= 0) && (lbl_1_bss_57C < (VERSION_NTSC ? 5400 : 5250))) {
                        if (GWPlayerCfg[fn_1_51A8(lbl_1_bss_3FC)->unk_188].iscom != 0) {
                            if (GWPlayerCfg[fn_1_51A8(lbl_1_bss_3FC + 1)->unk_188].iscom == 0) {
                                goto block_81;
                            }
                        }
                        else {
                        block_81:
                            GWGameStat.present[0x32] = 1;
                        }
                    }
                    if ((lbl_1_bss_3FC >= 0) && (lbl_1_bss_578 > lbl_1_bss_57C)) {
                        if (GWPlayerCfg[fn_1_51A8(lbl_1_bss_3FC)->unk_188].iscom != 0) {
                            if (GWPlayerCfg[fn_1_51A8(lbl_1_bss_3FC + 1)->unk_188].iscom == 0) {
                                goto block_98;
                            }
                        }
                        else {
                        block_98:
                            var_r28->work[0] = 0x3ED;
                            fn_1_798(3);
                        }
                    }
                    lbl_1_bss_576 = -1;
                    lbl_1_bss_3F0 = 0.0f;
                }
            }
            break;
        case 0x3ED:
            if (lbl_1_bss_576 < 0) {
                lbl_1_bss_576 = MGSeqCreate(0xE, lbl_1_bss_578);
            }
            else if (MGSeqStatGet(lbl_1_bss_576) == 0) {
                var_r28->work[0]++;
                lbl_1_bss_3F0 = 0.0f;
                lbl_1_bss_576 = -1;
            }
            break;
        case 0x3EE:
            if (lbl_1_bss_3FC < 0) {
                var_r28->work[0] = 0x3F1;
                lbl_1_bss_3F0 = 0.0f;
            }
            else if (2000.0f < lbl_1_bss_0[lbl_1_bss_3FC >> 1].unk_118.y) {
                var_r28->work[0]++;
                WipeColorSet(0xFF, 0xFF, 0xFF);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            }
            break;
        case 0x3EF:
            if (WipeStatGet() == 0) {
                var_r28->work[0]++;
                lbl_1_bss_3F0 = 0.0f;
                omDelObjEx(lbl_1_bss_5B4, lbl_1_bss_414);
                Hu3DCameraKill(lbl_1_data_A0[(lbl_1_bss_3FC >> 1) ^ 1]);
                Hu3DCameraPerspectiveSet(lbl_1_data_A0[lbl_1_bss_3FC >> 1], 20.0f, 20.0f, 20000.0f, 1.2f);
                Hu3DCameraViewportSet(lbl_1_data_A0[lbl_1_bss_3FC >> 1], 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
                Hu3DCameraScissorSet(lbl_1_data_A0[lbl_1_bss_3FC >> 1], 0, 0, 0x280, 0x1E0);
                var_r29 = &lbl_1_bss_0[lbl_1_bss_3FC >> 1];
                var_r29->unk_118.y = 5000.0f;
                Hu3DModelPosSet(var_r29->unk_04->model[22], var_r29->unk_118.x, var_r29->unk_118.y, var_r29->unk_118.z);
                Hu3DModelPosSet(var_r29->unk_04->model[24], var_r29->unk_118.x, var_r29->unk_118.y, var_r29->unk_118.z);
                Hu3DModelAttrReset(var_r29->unk_04->model[24], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(var_r29->unk_04->model[24], HU3D_MOTATTR_PAUSE);
                var_r29->unk_28.y = 8000.0f;
                var_r29->unk_1C.y = 8000.0f;
                var_r29->unk_1C.z = 5000.0f + var_r29->unk_118.z;
                Hu3DCameraPosSetV(lbl_1_data_A0[lbl_1_bss_3FC >> 1], &var_r29->unk_1C, &lbl_1_data_C8, &var_r29->unk_28);
                var_r29->unk_4C = var_r29->unk_28;
                var_r29->unk_58 = var_r29->unk_28;
                var_r29->unk_34 = var_r29->unk_1C;
                var_r29->unk_40 = var_r29->unk_1C;
                var_r29->unk_58.y = 5200.0f;
                var_r29->unk_40.y = 5200.0f;
                var_r29->unk_40.z = 2000.0f + var_r29->unk_118.z;
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 0x3C);
                lbl_1_bss_3F4 = HuAudFXPlay(0x69B);
            }
            break;
        case 0x3F0:
            var_r29 = &lbl_1_bss_0[lbl_1_bss_3FC >> 1];
            lbl_1_bss_3F0 += 1.0f;
            var_f31 = lbl_1_bss_3F0 / (3.0f * REFRESH_RATE);
            var_f30 = sind((90.0f * var_f31)) * sind((90.0f * var_f31));
            var_r29->unk_28.y = var_r29->unk_4C.y + (var_f30 * (var_r29->unk_58.y - var_r29->unk_4C.y));
            var_r29->unk_1C.y = var_r29->unk_34.y + (var_f30 * (var_r29->unk_40.y - var_r29->unk_34.y));
            if ((1.5f * REFRESH_RATE) < lbl_1_bss_3F0) {
                var_f31 = (lbl_1_bss_3F0 - 1.5f * REFRESH_RATE) / (1.5f * REFRESH_RATE);
                var_f30 = sind((90.0f * var_f31)) * sind((90.0f * var_f31));
                var_r29->unk_1C.z = var_r29->unk_34.z + (var_f30 * (var_r29->unk_40.z - var_r29->unk_34.z));
            }
            Hu3DCameraPosSetV(lbl_1_data_A0[lbl_1_bss_3FC >> 1], &var_r29->unk_1C, &lbl_1_data_C8, &var_r29->unk_28);
            if ((3 * REFRESH_RATE) <= lbl_1_bss_3F0) {
                var_r28->work[0]++;
                lbl_1_bss_3F0 = 0.0f;
            }
            break;
        case 0x3F1:
            if (lbl_1_bss_576 < 0) {
                if (lbl_1_bss_3FC < 0) {
                    lbl_1_bss_576 = MGSeqCreate(3, 2);
                    HuAudSStreamPlay(4);
                }
                else {
                    lbl_1_bss_576 = MGSeqCreate(5, 3, fn_1_51A8(lbl_1_bss_3FC)->unk_18C, fn_1_51A8(lbl_1_bss_3FC + 1)->unk_18C, -1, -1);
                    HuAudSStreamPlay(1);
                }
            }
            else {
                lbl_1_bss_3F0 += 1.0f;
                if (0 <= lbl_1_bss_3FC) { }
                if ((210.0f < lbl_1_bss_3F0) && (MGSeqStatGet(lbl_1_bss_576) == 0)) {
                    fn_1_1F58(-1);
                    lbl_1_bss_576 = -1;
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
                    var_r28->func = fn_1_1615C;
                }
            }
            break;
        default:
            OSReport("*** main mode error(%d)!!\n", var_r28->work[0]);
            break;
    }
    fn_1_A40();
    if ((lbl_1_bss_3FC >= 0) && (var_r28->work[0] >= 0x3F0)) {
        var_r29 = &lbl_1_bss_0[lbl_1_bss_3FC >> 1];
        var_r29->unk_118.y = 5000.0 + (10.0 * sind((lbl_1_bss_580 * 4)));
        Hu3DModelPosSet(var_r29->unk_04->model[22], var_r29->unk_118.x, var_r29->unk_118.y, var_r29->unk_118.z);
    }
    sp98.x = 0.0f;
    sp98.y = 0.0f;
    sp98.z = 0.0f;
    for (var_r26 = 0; var_r26 < 4; var_r26++) {
        sp7C[0] = lbl_1_bss_410[var_r26]->data;
        sp98.x += sp7C[0]->unk_00.unk_6C.x;
        sp98.z += sp7C[0]->unk_00.unk_6C.z;
    }
    sp98.x *= 0.25f;
    sp98.z *= 0.25f;
    var_f27 = 0.0f;
    for (var_r26 = 0; var_r26 < 4; var_r26++) {
        var_f26 = VECDistance(&sp98, &((UnkM432DllStruct *)lbl_1_bss_410[var_r26]->data)->unk_00.unk_6C);
        if (var_f27 < var_f26) {
            var_f27 = var_f26;
        }
    }

    fn_1_52B8_inline(&sp80, sp98.x, 0.0f, sp98.z);

    sp98.y = 6.0f * var_f27;
    sp98.z += 1000.0f;
    VECNormalize(&sp98, &sp8C);
    Hu3DShadowPosSet(&sp98, &sp8C, &sp80);
    fn_1_2D8();
}

void fn_1_15320(omObjData *object)
{
    s32 var_r31;
    object->work[0] = 0x3E8;
    fn_1_B4C(80.0f, DATA_MAKE_NUM(DATADIR_M432, 0x1E));
    fn_1_9EC();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    object->func = fn_1_131A8;
}

void ObjectSetup(void)
{
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;

    UnkBss0Struct *var_r31;
    s32 var_r30;
    float *var_r29;
    UnkM432DllStruct *var_r28;
    omObjData *var_r27;
    s32 var_r26;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;

    OSReport("******* M432 ObjectSetup *********\n");
    lbl_1_bss_5B4 = omInitObjMan(0x258, 0x2000);
    omGameSysInit(lbl_1_bss_5B4);
    nMap = 0;
    nChar = 0;
    lbl_1_bss_580 = 0;
    lbl_1_bss_576 = -1;
    lbl_1_bss_574 = -1;
    lbl_1_bss_3FC = -1;
    lbl_1_bss_3F8 = 0;
    lbl_1_bss_570 = -1;
    lbl_1_bss_3F4 = -1;
    lbl_1_bss_57C = 0;
    lbl_1_bss_578 = GWMGRecordGet(3);
    lbl_1_bss_568 = -1.0f;
    if (lbl_1_bss_578 == 0) {
        lbl_1_bss_578 = 120 * REFRESH_RATE;
    }
    fn_1_414();
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        lbl_1_bss_0[var_r30].unk_08 = NULL;
        lbl_1_bss_0[var_r30].unk_18 = 0;
        lbl_1_bss_0[var_r30].unk_28.x = -800.0f + (1600.0f * var_r30);
        lbl_1_bss_0[var_r30].unk_28.y = 0.0f;
        lbl_1_bss_0[var_r30].unk_28.z = -300.0f;
        lbl_1_bss_0[var_r30].unk_1E4 = 0.0f;
        lbl_1_bss_0[var_r30].unk_64 = 0.0f;
        lbl_1_bss_0[var_r30].unk_68 = 3900.0f;
        lbl_1_bss_0[var_r30].unk_6C = 3250.0f;
        lbl_1_bss_0[var_r30].unk_1E8 = 0.0f;
        lbl_1_bss_0[var_r30].unk_70 = 0.0f;
        lbl_1_bss_0[var_r30].unk_74 = 0.0f;
        lbl_1_bss_0[var_r30].unk_78 = 0.0f;
        lbl_1_bss_0[var_r30].unk_7C = 0.0f;
        lbl_1_bss_0[var_r30].unk_80 = 0.0f;
        lbl_1_bss_0[var_r30].unk_84 = 0.0f;
        lbl_1_bss_0[var_r30].unk_124 = 0.0f;
        lbl_1_bss_0[var_r30].unk_128 = 0.0f;
        lbl_1_bss_0[var_r30].unk_12C = 0.0f;
        lbl_1_bss_0[var_r30].unk_1B8 = frandmod(5);
        lbl_1_bss_0[var_r30].unk_1BC = frandmod(9);
        lbl_1_bss_0[var_r30].unk_1CC = -1;
        lbl_1_bss_0[var_r30].unk_1D0 = -1;
        lbl_1_bss_0[var_r30].unk_1D4 = 0.0f;
        lbl_1_bss_0[var_r30].unk_1D8 = -1;
        lbl_1_bss_0[var_r30].unk_1DC = 0.0f;
    }
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(3, 20.0f, 20.0f, 20000.0f, 0.6f);
    fn_1_12EA8();
    for (var_r29 = lbl_1_data_A8, var_r30 = 0; var_r30 < 2; var_r30++, var_r29 += 4) {
        Hu3DCameraViewportSet(lbl_1_data_A0[var_r30], var_r29[0], var_r29[1], var_r29[2], var_r29[3], 0.0f, 1.0f);
        Hu3DCameraScissorSet(lbl_1_data_A0[var_r30], var_r29[0], var_r29[1], var_r29[2], var_r29[3]);
    }
    var_r20 = Hu3DGLightCreateV(&lbl_1_data_D4, &lbl_1_data_E0, &lbl_1_data_EC);
    Hu3DGLightStaticSet(var_r20, 0);
    Hu3DGLightInfinitytSet(var_r20);
    Hu3DShadowCreate(30.0f, 20.0f, 20000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    VECNormalize(&lbl_1_data_F0, &sp8);
    Hu3DShadowPosSet(&lbl_1_data_F0, &sp8, &lbl_1_data_FC);
    fn_1_2C00(fn_1_AA00, 0.0f);
    omMakeGroupEx(lbl_1_bss_5B4, 2, 4);
    lbl_1_bss_410 = omGetGroupMemberListEx(lbl_1_bss_5B4, 2);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r27 = omAddObjEx(lbl_1_bss_5B4, 0x68, 1, 0xB, 2, fn_1_10CCC);
        var_r27->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM432DllStruct), MEMORY_DEFAULT_NUM);
        var_r27->work[0] = var_r30;
        var_r28 = var_r27->data;
        var_r28->unk_184 = -1;
        var_r28->unk_188 = var_r27->work[0];
        var_r28->unk_194 = GWPlayerCfg[var_r28->unk_188].group;
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r22 = -1;
        var_r21 = 0x28;
        for (var_r26 = 0; var_r26 < 4; var_r26++) {
            var_r28 = lbl_1_bss_410[var_r26]->data;
            if (var_r28->unk_184 < 0) {
                var_r23 = var_r28->unk_188 + (var_r28->unk_194 * 4);
                if (var_r21 > var_r23) {
                    var_r21 = var_r23;
                    var_r22 = var_r26;
                }
            }
        }
        ((UnkM432DllStruct *)lbl_1_bss_410[var_r22]->data)->unk_184 = var_r30;
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        lbl_1_bss_0[var_r30].unk_04 = omAddObjEx(lbl_1_bss_5B4, 0x64, 0x1A, 0, 0, fn_1_113F4);
        lbl_1_bss_0[var_r30].unk_04->work[0] = var_r30;
        lbl_1_bss_0[var_r30].unk_00 = omAddObjEx(lbl_1_bss_5B4, 0x65, 1, 0, 1, fn_1_12804);
        lbl_1_bss_0[var_r30].unk_00->work[0] = var_r30;
        MapObject[nMap++] = lbl_1_bss_0[var_r30].unk_00;
    }
    fn_1_150();
    lbl_1_bss_408 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M432, 0x28));
    HuSprAnimLock(lbl_1_bss_408);
    lbl_1_bss_404 = Hu3DParManCreate(lbl_1_bss_408, 0x1F4, &lbl_1_data_1814);
    Hu3DParManAttrSet(lbl_1_bss_404, 1);
    lbl_1_bss_402 = 0;
    fn_1_0();
    omMakeGroupEx(lbl_1_bss_5B4, 3, 0xF0);
    lbl_1_bss_418 = omGetGroupMemberListEx(lbl_1_bss_5B4, 3);
    lbl_1_bss_400 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M432, 0x09));
    Hu3DModelAttrSet(lbl_1_bss_400, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_400, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    lbl_1_bss_414 = omAddObjEx(lbl_1_bss_5B4, 0x66, 0, 0, -1, fn_1_128C8);
    lbl_1_bss_41C = omAddObjEx(lbl_1_bss_5B4, 0x69, 0x1A, 0, -1, fn_1_15320);
    lbl_1_bss_41C->work[0] = 0x3E8;
}

void fn_1_1615C(omObjData *arg0)
{
    s32 var_r31;

    if (lbl_1_bss_3F4 >= 0) {
        lbl_1_bss_3F4 = -1;
        HuAudFXStop(lbl_1_bss_3F4);
    }
    if (WipeStatGet() == 0) {
        if (lbl_1_bss_576 >= 0) {
            MGSeqKill(lbl_1_bss_576);
        }
        if (lbl_1_bss_574 >= 0) {
            MGSeqKill(lbl_1_bss_574);
        }
        MGSeqKillAll();
        HuAudAllStop();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            CharModelKill(lbl_1_data_0[GWPlayerCfg[var_r31].character]);
        }
        omOvlReturnEx(1, 1);
    }
}
