#include "REL/executor.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/gamework.h"
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

#ifndef __MWERKS__
#include "game/audio.h"
#endif

#undef ABS
#define ABS(x) ((0 > (x)) ? -(x) : (x))

typedef struct unk_bss_358_struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ struct unk_bss_358_struct *unk04;
    /* 0x08 */ struct unk_bss_358_struct *unk08;
} UnkBss254Struct; // Size 0xC

typedef struct unk_bss_340_struct {
    /* 0x00 */ HsfanimStruct00 *unk00;
    /* 0x04 */ s32 *unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ struct unk_bss_340_struct *unk10;
    /* 0x14 */ struct unk_bss_340_struct *unk14;
} UnkBss23CStruct; // Size 0x18

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ s16 unk04;
} UnkBssACStruct; // Size 8

UnkBss254Struct lbl_1_bss_254;
UnkBss23CStruct lbl_1_bss_23C;
Process *lbl_1_bss_238;
Vec lbl_1_bss_22C;
Vec lbl_1_bss_220;
Vec lbl_1_bss_214;
Vec lbl_1_bss_208;
u32 lbl_1_bss_204;
s32 lbl_1_bss_200;
u32 lbl_1_bss_1FC;
s16 lbl_1_bss_1FA;
s16 lbl_1_bss_1F8;
s32 lbl_1_bss_1F4;
s32 lbl_1_bss_1F0;
float lbl_1_bss_1EC;
s32 lbl_1_bss_1AC[16];
UnkBssACStruct lbl_1_bss_AC[32];

void fn_1_0(void)
{
    lbl_1_bss_254.unk04 = NULL;
    lbl_1_bss_254.unk08 = NULL;
}

void fn_1_24(u16 arg0, s16 arg1)
{
    UnkBss254Struct *temp_r31;
    UnkBss254Struct *temp_r30;
    UnkBss254Struct *temp_r29;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r31), MEMORY_DEFAULT_NUM);
    temp_r31->unk00 = arg0;
    temp_r31->unk02 = arg1;
    temp_r30 = &lbl_1_bss_254;
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
    UnkBss254Struct *var_r31;
    UnkBss254Struct *temp_r29;
    UnkBss254Struct *temp_r30;
    s16 temp_r28;

    var_r31 = lbl_1_bss_254.unk08;
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
    lbl_1_bss_23C.unk10 = NULL;
    lbl_1_bss_23C.unk14 = NULL;
}

void fn_1_174(s16 arg0, HsfanimStruct00 *arg1, s32 arg2, s32 arg3, s32 arg4, Vec *arg5, u8 arg6)
{
    UnkBss23CStruct *temp_r27;
    UnkBss23CStruct *var_r31;
    UnkBss23CStruct *temp_r28;
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
    temp_r28 = &lbl_1_bss_23C;
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
    UnkBss23CStruct *var_r31;
    UnkBss23CStruct *temp_r28;
    UnkBss23CStruct *temp_r29;
    s32 i;

    var_r31 = lbl_1_bss_23C.unk14;
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
        lbl_1_bss_AC[i].unk00 = 0;
        lbl_1_bss_AC[i].unk04 = -1;
    }
}

s16 fn_1_46C(s32 arg0)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        if (arg0 == lbl_1_bss_AC[i].unk00) {
            return Hu3DModelLink(lbl_1_bss_AC[i].unk04);
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_1_bss_AC[i].unk00 == 0) {
            lbl_1_bss_AC[i].unk00 = arg0;
            lbl_1_bss_AC[i].unk04 = Hu3DModelCreateFile(arg0);
            return lbl_1_bss_AC[i].unk04;
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
    lbl_1_bss_1EC = 0.0f;
    lbl_1_bss_1FC = lbl_1_bss_200;
    GWMGRecordSet(arg0, lbl_1_bss_1FC);
    fn_1_580(lbl_1_bss_1AC, 7, lbl_1_bss_200);
}

void fn_1_9EC(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        espDispOn(lbl_1_bss_1AC[i]);
    }
}

void fn_1_A40(void)
{
    float temp_f31;
    s32 i;

    if (0.0f <= lbl_1_bss_1EC) {
        lbl_1_bss_1EC += 16.0f;
        temp_f31 = 1.0 + 0.2f * sind(lbl_1_bss_1EC);
        for (i = 7; i <= 14; i++) {
            espScaleSet(lbl_1_bss_1AC[i], temp_f31, temp_f31);
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
    lbl_1_bss_1AC[15] = espEntry(arg1, 0, 0);
    espTPLvlSet(lbl_1_bss_1AC[15], 0.5f);
    espColorSet(lbl_1_bss_1AC[15], 0, 0, 0);
    espPosSet(lbl_1_bss_1AC[15], temp_f31, temp_f30);
    temp_f31 = 248.0f;
    temp_f30 = arg0 - 8.0f;
    lbl_1_bss_1AC[14] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 55), 0, 0);
    espPosSet(lbl_1_bss_1AC[14], temp_f31 - 18.0f, temp_f30);
    for (i = 7; i <= 13; i++) {
        lbl_1_bss_1AC[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 48), 0, 0);
        espPosSet(lbl_1_bss_1AC[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_1AC, 7, lbl_1_bss_1FC);
    temp_f31 = 248.0f;
    temp_f30 = arg0 + 8.0f;
    for (i = 0; i <= 6; i++) {
        lbl_1_bss_1AC[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 49), 0, 0);
        espPosSet(lbl_1_bss_1AC[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_1AC, 0, 0);
    for (i = 0; i < 16; i++) {
        espDrawNoSet(lbl_1_bss_1AC[i], 0);
        espDispOff(lbl_1_bss_1AC[i]);
        espAttrSet(lbl_1_bss_1AC[i], HUSPR_ATTR_NOANIM);
        espPriSet(lbl_1_bss_1AC[i], 0x80 + i);
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
    lbl_1_bss_22C = *arg0;
    lbl_1_bss_214 = *arg2;
}

s32 fn_1_13DC(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_22C, &lbl_1_bss_220, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_214, &lbl_1_bss_208, &spC);
    Hu3DCameraPosSetV(1, &sp18, arg1, &spC);
    if (1.0f <= arg0) {
        return 1;
    }
    else {
        lbl_1_bss_1F0 = 1;
        return 0;
    }
}

void fn_1_1710(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_22C, &lbl_1_bss_220, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_214, &lbl_1_bss_208, &spC);
    fn_1_1350(&sp18, arg1, &spC);
    lbl_1_bss_1F0 = 1;
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
    lbl_1_bss_1F4 = HuAudSeqPlay((s32)arg0);
}

void fn_1_1F58(s32 arg0)
{
    if (lbl_1_bss_1F4 >= 0) {
        if (arg0 < 0) {
            arg0 = 1000;
        }
        HuAudSeqFadeOut(lbl_1_bss_1F4, arg0);
    }
    lbl_1_bss_1F4 = -1;
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

typedef void (*PlayerOldHook)(omObjData *obj);
typedef Vec *(*PlayerOldPosHook)(omObjData *obj);

typedef struct work_playerold {
    omObjData *unk0;
    PlayerOldHook unk4;
    PlayerOldPosHook unk8;
    PlayerOldHook unkC;
    PlayerOldHook unk10;
    s32 *unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    Vec *unk50;
    Vec unk54;
    float unk60;
    s32 unk64;
    Vec *unk68;
    Vec unk6C;
    Vec unk78;
    Vec unk84;
    Vec unk90;
    float unk9C;
    float unkA0;
    float unkA4;
    float unkA8;
    Vec unkAC;
    float unkB8;
    float unkBC;
    float unkC0;
} WorkPlayerOld;

typedef WorkPlayerOld *(*PlayerOldFind)(int no);

PlayerOldFind lbl_1_bss_A8;
float lbl_1_bss_A4;
omObjData *lbl_1_bss_A0;
omObjData *lbl_1_bss_9C;
omObjData *lbl_1_bss_4C[20];
int lbl_1_bss_48;
int lbl_1_bss_3C[3];
int lbl_1_bss_2C[4];
s32 lbl_1_bss_28;
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
float lbl_1_bss_1C;
BOOL lbl_1_bss_18;
BOOL lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
float lbl_1_bss_8;
float lbl_1_bss_4;
float lbl_1_bss_0;

s16 lbl_1_data_0[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

s32 lbl_1_data_10[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

float lbl_1_data_30[10] = { 70, 70, 70, 70, 70, 70, 70, 70, 70, 100 };

float lbl_1_data_58[10] = { 150, 170, 190, 170, 160, 150, 180, 200, 150, 200 };

void fn_1_23B4(WorkPlayerOld *player)
{
    s32 i;
    for (i = 0; i < 8; i++) {
        if (player->unk44 == player->unk14[i]) {
            player->unk40 = lbl_1_data_10[i];
            return;
        }
    }
    player->unk40 = -1;
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
    *minDist = 10 * (player1->unkBC + player2->unkBC);
    fn_1_2418(minDist, state, 0, &player1->unk6C, player1->unkBC, &player2->unk6C, player2->unkBC);
    fn_1_2418(minDist, state, 1, &player1->unk6C, player1->unkC0 - player1->unkBC, &player2->unk6C, player2->unkC0 - player2->unkBC);
    fn_1_2418(minDist, state, 2, &player1->unk6C, player1->unkBC, &player2->unk6C, player2->unkC0 - player2->unkBC);
    fn_1_2418(minDist, state, 3, &player1->unk6C, player1->unkC0 - player1->unkBC, &player2->unk6C, player2->unkBC);
}

s32 fn_1_2824(WorkPlayerOld *player, WorkPlayerOld *player2)
{
    Vec dir;
    Vec dir2;
    float dist;

    player->unk3C |= 0x1;
    player->unk90.x = player->unk20 / 4.0f;
    player->unk90.z = -(float)player->unk24 / 4.0f;
    if (player->unk90.x != 0.0f || player->unk90.z != 0.0f) {
        return;
    }
    VECSubtract(&player->unk6C, &player2->unk6C, &dir);
    dist = VECMagXZ(&dir);
    if (0.0f == dist) {
        dir.x = 0;
        dir.z = -1;
    }
    else {
        dir.x /= dist;
        dir.z /= dist;
    }
    VECSubtract(&player->unk6C, &player->unk78, &dir2);
    dist = VECMagXZ(&dir2);
    if (5 > dist) {
        dist = 5;
    }
    player->unk90.x = dir.x * dist;
    player->unk90.z = dir.z * dist;
}

void fn_1_2BD0(WorkPlayerOld *player, float arg1, float arg2)
{
    player->unk38 = 1;
    player->unk84.y = arg1;
    player->unkA4 = arg2;
    if (player->unk3C & 0x2) {
        player->unk3C &= ~0x2;
    }
}

void fn_1_2C00(PlayerOldFind find, float yDist)
{
    lbl_1_bss_A8 = find;
    lbl_1_bss_A4 = yDist;
}

void fn_1_2C1C(WorkPlayerOld *player, omObjData *obj, s32 arg2, s32 arg3, s32 *arg4, s32 arg5, Vec *pos, float arg7)
{
    player->unk0 = obj;
    player->unk18 = arg2;
    player->unk1C = arg3;
    player->unk14 = arg4;
    player->unk4 = NULL;
    player->unk8 = NULL;
    player->unkC = NULL;
    player->unk10 = NULL;
    player->unk50 = NULL;
    player->unk64 = 0;
    player->unk68 = 0;
    player->unk38 = 0;
    player->unk3C = 0;
    player->unk44 = arg5;
    player->unk48 = 0;
    player->unk4C = 0;
    fn_1_23B4(player);
    player->unk9C = arg7;
    player->unk6C = *pos;
    player->unk78 = *pos;
    player->unk84.x = 0;
    player->unk84.y = 0;
    player->unk84.z = 0;
    player->unkB8 = 1;
    player->unkA8 = 0;
    player->unkBC = lbl_1_data_30[player->unk1C];
    player->unkC0 = lbl_1_data_58[player->unk1C];
}

void fn_1_2DA8(WorkPlayerOld *player, PlayerOldHook func)
{
    player->unk4 = func;
}

void fn_1_2DB0(WorkPlayerOld *player, PlayerOldPosHook func)
{
    player->unk8 = func;
}

void fn_1_2DB8(WorkPlayerOld *player, PlayerOldHook func)
{
    player->unkC = func;
}

void fn_1_2DC0(WorkPlayerOld *player, PlayerOldHook func)
{
    player->unk10 = func;
}

void fn_1_2DC8(WorkPlayerOld *player, s32 count, Vec *data)
{
    player->unk64 = count;
    player->unk68 = data;
}

void fn_1_2DD4(WorkPlayerOld *player)
{
    omSetTra(player->unk0, player->unk6C.x, player->unk6C.y, player->unk6C.z);
    omSetRot(player->unk0, 0.0f, player->unk9C, 0.0f);
}

void fn_1_2E34(WorkPlayerOld *player)
{
    BOOL addTime;
    s32 i;
    player->unk3C &= ~0x100;
    if (player->unk3C & 0x8) {
        return;
    }
    if (NULL == lbl_1_bss_A8) {
        return;
    }
    addTime = FALSE;
    for (i = 0; i < 4; i++) {
        WorkPlayerOld *player2 = lbl_1_bss_A8(i);
        BOOL fixPos;
        float minDist;
        s32 state;
        if (player == player2) {
            continue;
        }
        if (player2->unk3C & 0x8) {
            continue;
        }
        fixPos = FALSE;
        fn_1_24F8(player, player2, &minDist, &state);
        if (minDist < player->unkBC + player2->unkBC) {
            if (state < 2) {
                fixPos = TRUE;
                if (player->unk38 == 1) {
                    fn_1_2824(player, player2);
                }
            }
            else {
                if (state == 2 && player->unk38 == 1) {
                    fn_1_2824(player, player2);
                    player->unk3C |= 0x100;
                    player->unkA4 = 0;
                    if (!(player2->unk3C & 0x100)) {
                        player->unk84.y = 26.766666f;
                    }
                }
                if (state == 3) {
                    fixPos = TRUE;
                    if (player->unk38 == 1) {
                        if (0.0f < player->unk84.y) {
                            player->unk84.y = 0.0f;
                        }
                        player->unkA4 = 0;
                    }
                }
            }
        }
        if (fixPos) {
            Vec dir;
            addTime = TRUE;
            VECSubtract(&player->unk6C, &player2->unk6C, &dir);
            if (0.0f == minDist) {
                dir.x = 0;
                dir.z = -1;
            }
            else {
                dir.x /= minDist;
                dir.z /= minDist;
            }
            player->unk6C.x = player2->unk6C.x + (dir.x * (player->unkBC + player2->unkBC));
            player->unk6C.z = player2->unk6C.z + (dir.z * (player->unkBC + player2->unkBC));
        }
    }
    if (addTime) {
        player->unk4C++;
    }
    else {
        player->unk4C = 0;
    }
}

float fn_1_39C4(WorkPlayerOld *player, float arg2)
{
    Vec *pos;
    s32 i;
    AddX = 0;
    AddZ = 0;
    if (NULL != player->unk68) {
        for (pos = player->unk68, i = 0; i < player->unk64; i++, pos += 2) {
            int num = 0;
            if (pos[0].x == pos[1].x || pos[0].x > player->unk6C.x || pos[1].x < player->unk6C.x) {
                num++;
            }
            if (pos[0].y == pos[1].y || pos[0].y > player->unk6C.y || pos[1].y < player->unk6C.y) {
                num++;
            }
            if (pos[0].z == pos[1].z || pos[0].z > player->unk6C.z || pos[1].z < player->unk6C.z) {
                num++;
            }
            if (num == 3) {
                if (pos[0].x != pos[1].x) {
                    if (pos[0].x > player->unk6C.x) {
                        player->unk6C.x = pos[0].x + player->unkBC;
                    }
                    if (pos[1].x < player->unk6C.x) {
                        player->unk6C.x = pos[1].x - player->unkBC;
                    }
                }
                if (pos[0].y != pos[1].y) {
                    if (pos[0].y > player->unk6C.y) {
                        player->unk6C.y = pos[0].y;
                    }
                    if (pos[1].y < player->unk6C.y) {
                        player->unk6C.y = pos[1].y;
                    }
                }
                if (pos[0].z != pos[1].z) {
                    if (pos[0].z > player->unk6C.z) {
                        player->unk6C.z = pos[0].z + player->unkBC;
                    }
                    if (pos[1].z < player->unk6C.z) {
                        player->unk6C.z = pos[1].z - player->unkBC;
                    }
                }
            }
        }
    }
    return ABS(AddX) + ABS(AddZ);
}

void fn_1_3C74(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    *motAttr = HU3D_MOTATTR_LOOP;
    *state = 0;
    if (0.5f <= player->unkA0) {
        if (7.0f <= player->unkA0) {
            *state = 2;
        }
        else {
            *state = 1;
        }
    }

    if (player->unk14[3] >= 0 && (player->unk28 & 0x100)) {
        fn_1_2BD0(player, 26.766666f, 1.0f);
        *motAttr = HU3D_MOTATTR_NONE;
        *state = 3;
    }
}

void fn_1_3D4C(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    if (0.0f < player->unkA4) {
        if (player->unk2C & 0x100) {
            player->unkA4++;
            if (4.0f < player->unkA4) {
                player->unkA4 = 0;
            }
            else {
                player->unk84.y += 3.65f;
            }
        }
        else {
            player->unkA4 = 0;
        }
    }
    player->unk84.y += -2.4333334f;
    if (player->unk14[5] >= 0 && (player->unk28 & 0x140)) {
        player->unk38 = 3;
        player->unk84.y = 0.0f;
        player->unk3C &= ~0x3;
        player->unk3C |= 0x4;
        *motAttr = HU3D_MOTATTR_NONE;
        *state = 5;
    }
}

void fn_1_3E60(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    if ((player->unk3C & 0x1000) || Hu3DMotionEndCheck(player->unk0->model[0])) {
        player->unk3C &= ~0x3;
        if (player->unk40 == 6) {
            player->unk38 = 4;
            *motAttr = HU3D_MOTATTR_NONE;
            *state = 7;
        }
        else {
            player->unk38 = 0;
            *motAttr = HU3D_MOTATTR_LOOP;
            *state = 0;
        }
    }
}

void fn_1_3F18(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    if (Hu3DMotionShiftIDGet(player->unk0->model[0]) < 0 && Hu3DMotionEndCheck(player->unk0->model[0])) {
        fn_1_2BD0(player, 0.0f, 0.0f);
    }
}

void fn_1_3FB8(WorkPlayerOld *player, s32 *state, u32 *motAttr)
{
    if (Hu3DMotionShiftIDGet(player->unk0->model[0]) < 0 && Hu3DMotionEndCheck(player->unk0->model[0])) {
        player->unk3C &= ~0x4;
        player->unk38 = 0;
        *motAttr = HU3D_MOTATTR_LOOP;
        *state = 0;
    }
}

void fn_1_4054(WorkPlayerOld *player)
{
    u32 motAttr = HU3D_MOTATTR_NONE;
    s32 state = -1;
    float temp_f28;
    float temp_f23;
    float temp_f22;
    Vec *pos;
    BOOL temp_r27;
    if (player->unk3C & 0x1) {
        player->unk84.x = player->unk90.x;
        player->unk84.z = player->unk90.z;
    }
    else {
        player->unk84.x = player->unk20 / 4.0f;
        player->unk84.z = -(float)player->unk24 / 4.0f;
        if (player->unk38 == 1 && 0.0f == player->unk84.x && 0.0f == player->unk84.z) {
            player->unk84.x = 0.98f * (player->unk6C.x - player->unk78.x);
            player->unk84.z = 0.98f * (player->unk6C.z - player->unk78.z);
        }
        if (player->unk3C & 0x14) {
            player->unk84.x = 0;
            player->unk84.z = 0;
            player->unk28 = 0;
        }
    }
    player->unk78 = player->unk6C;
    player->unkA0 = VECMagXZ(&player->unk84);
    if (0.5f <= player->unkA0) {
        if (10.0f <= player->unkA0) {
            player->unk84.x /= player->unkA0;
            player->unk84.z /= player->unkA0;
            player->unkA0 = 10;
            player->unk84.x = 10 * player->unk84.x;
            player->unk84.z = 10 * player->unk84.z;
        }
    }
    else {
        player->unk84.x = 0;
        player->unk84.z = 0;
        player->unkA0 = 0;
    }
    player->unk84.x *= player->unkB8;
    player->unk84.z *= player->unkB8;
    player->unkA0 *= player->unkB8;
    if (player->unk3C & 0x800) {
        player->unk28 |= 0x100;
        player->unk2C |= 0x100;
        if (player->unk38 == 1) {
            if (0.0f == player->unkA4) {
                player->unk3C &= ~0x800;
            }
        }
    }
    switch (player->unk38) {
        case 0:
            fn_1_3C74(player, &state, &motAttr);
            break;

        case 1:
            fn_1_3D4C(player, &state, &motAttr);
            break;

        case 2:
            fn_1_3E60(player, &state, &motAttr);
            break;

        case 3:
            fn_1_3F18(player, &state, &motAttr);
            break;

        case 4:
            fn_1_3FB8(player, &state, &motAttr);
            break;

        default:
            OSReport("*** player action error(%d)!!\n", player->unk38);
            break;
    }
    if (player->unk3C & 0x2000) {
        player->unk84.y = 0;
    }
    temp_f28 = 0;
    if (50.0f < ABS(player->unk84.y)) {
        player->unk84.y = 50.0f * ((0.0f > player->unk84.y) ? -1 : 1);
    }
    if (player->unk3C & 0x2) {
        Mtx rotMtx;
        MTXRotDeg(rotMtx, 'y', player->unk50[2].x - player->unk60);
        MTXMultVec(rotMtx, &player->unk54, &player->unk54);
        VECAdd(&player->unk54, &player->unk50[0], &player->unk6C);
        player->unk9C += player->unk50[2].x - player->unk60;
    }
    temp_f22 = player->unk6C.y;
    VECAdd(&player->unk6C, &player->unk84, &player->unk6C);
    if ((player->unk3C & 0x1) == 0 && (0.0f != player->unk84.x || 0.0f != player->unk84.z)) {
        player->unk9C = fn_1_1E20(player->unk9C, atan2d(player->unk84.x, player->unk84.z), 0.4f * player->unkB8);
    }
    temp_f28 += fn_1_39C4(player, temp_f22);
    if (nMap == 0) {
        player->unkA8 = lbl_1_bss_A4;
    }
    else {
        player->unkA8 = MapPos(player->unk6C.x, player->unk6C.y, player->unk6C.z, player->unkC0, &player->unkAC);
    }
    temp_r27 = FALSE;
    if (NULL != player->unk8) {
        pos = player->unk8(player->unk0);
        if (NULL != pos) {
            if (player->unkA8 < pos[1].y) {
                temp_r27 = TRUE;
                player->unk50 = pos;
                player->unkA8 = pos[1].y;
            }
        }
    }
    if (!temp_r27 && (player->unk3C & 0x2)) {
        player->unk3C &= ~0x2;
    }
    if (player->unk38 == 1 && player->unkA8 >= player->unk6C.y) {
        player->unk38 = 2;
        player->unk3C &= ~0x3;
        player->unk6C.y = player->unkA8;
        player->unk84.y = 0;
        motAttr = HU3D_MOTATTR_NONE;
        state = 4;
        if (player->unk40 == 5) {
            state = 6;
            if (NULL != player->unk10) {
                player->unk10(player->unk0);
            }
            if (player->unk18 < 4) {
                omVibrate(player->unk18, 12, 4, 2);
            }
        }
        if (player->unk3C & 0x200) {
            state = -1;
            if (NULL != player->unkC) {
                player->unkC(player->unk0);
            }
        }
        if (temp_r27) {
            player->unk3C |= 0x2;
        }
    }
    temp_f23 = player->unk6C.y - player->unkA8;
    if (player->unk38 == 0 && 10.0f < temp_f23) {
        if (!(player->unk3C & 0x2000) && (player->unk3C & 0x400)) {
            player->unk3C |= 0x800;
        }
    }
    else if (temp_r27) {
        if (!(player->unk3C & 0x2)) {
            player->unk6C.y = player->unkA8;
            player->unk3C |= 0x2;
        }
    }
    fn_1_2E34(player);
    if (NULL != player->unk4) {
        player->unk4(player->unk0);
    }
    temp_f28 += fn_1_39C4(player, player->unk6C.y);
    if (player->unk3C & 0x2) {
        player->unk60 = player->unk50[2].x;
        VECSubtract(&player->unk6C, &player->unk50[0], &player->unk54);
    }
    if (0.0f != temp_f28) {
        player->unk48++;
    }
    else {
        player->unk48 = 0;
    }
    if (state >= 0 && player->unk40 != state) {
        player->unk40 = state;
        player->unk44 = player->unk14[player->unk40];
        if (player->unk44 >= 0 && !(player->unk3C & 0x20)) {
            Hu3DMotionShiftSet(player->unk0->model[0], player->unk0->motion[player->unk44], 0, 8, motAttr);
        }
    }
}

void fn_1_4E1C(WorkPlayerOld *player, s32 motNo)
{
    s32 i;
    player->unk44 = motNo;
    player->unk38 = 0;
    player->unk3C &= 0x1400;
    player->unk78 = player->unk6C;
    player->unk84.x = 0;
    player->unk84.y = 0;
    player->unk84.z = 0;
    fn_1_23B4(player);
    if (player->unk40 == 3) {
        Hu3DModelAttrReset(player->unk0->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DMotionSet(player->unk0->model[0], player->unk0->motion[player->unk44]);
        Hu3DMotionTimeSet(player->unk0->model[0], Hu3DMotionMaxTimeGet(player->unk0->model[0]) - 1);
    }
    else if (player->unk40 == 5) {
        player->unk38 = 3;
        player->unk3C |= 0x4;
        Hu3DModelAttrReset(player->unk0->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DMotionSet(player->unk0->model[0], player->unk0->motion[player->unk44]);
        Hu3DMotionTimeSet(player->unk0->model[0], Hu3DMotionMaxTimeGet(player->unk0->model[0]) - 1);
    }
    else {
        Hu3DModelAttrReset(player->unk0->model[0], HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(player->unk0->model[0], player->unk0->motion[player->unk44], 0, 8, HU3D_MOTATTR_LOOP);
    }
}

void fn_1_506C(WorkPlayerOld *player, s32 attr)
{
    player->unk3C |= attr;
}

void fn_1_507C(WorkPlayerOld *player, s32 attr)
{
    player->unk3C &= ~attr;
}

#ifdef __MWERKS__
#include "src/REL/executor.c"
#endif

Vec lbl_1_data_A0 = { 0, 600, 600 };
Vec lbl_1_data_AC = { 0, 1, 0 };
Vec lbl_1_data_B8 = { 0, 100, 0 };

Vec lbl_1_data_C4 = { 0, 2300, 2200 };
Vec lbl_1_data_D0 = { 0, 1, 0 };
Vec lbl_1_data_DC = { 0, 0, 0 };

Vec lbl_1_data_E8 = { -1500, 4000, 1500 };
Vec lbl_1_data_F4 = { 1.5, -4, -1.5 };
GXColor lbl_1_data_100 = { 255, 255, 255, 255 };

Vec lbl_1_data_104 = { -1500, 4000, 1500 };
Vec lbl_1_data_110 = { 0, 0, 0 };
Vec lbl_1_data_11C = { 0, 1, 0 };

s32 lbl_1_data_128[8][5] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x14),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x14),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x14),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x14),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x14),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x14),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x14),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x14),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x17),
};

s32 lbl_1_data_1C8[3] = { DATA_MAKE_NUM(DATADIR_M461, 0x02), DATA_MAKE_NUM(DATADIR_M461, 0x03), DATA_MAKE_NUM(DATADIR_M461, 0x08) };

s32 lbl_1_data_1D4[4]
    = { DATA_MAKE_NUM(DATADIR_M461, 0x04), DATA_MAKE_NUM(DATADIR_M461, 0x05), DATA_MAKE_NUM(DATADIR_M461, 0x06), DATA_MAKE_NUM(DATADIR_M461, 0x07) };

float lbl_1_data_1E4[3] = { 0.3f, 0.5f, 0.9f };

float lbl_1_data_1F0[10][2] = { 0, 60, 1860, 60, 3660, 50, 5460, 50, 7260, 40, 9060, 40, 10860, 30, 12660, 20, 14460, 10, -1, 10 };

Vec lbl_1_data_240[3] = { { 0, 0, 2800 }, { 2800, 0, 0 }, { -2800, 0, 0 } };

s32 lbl_1_data_264[3] = { 70, 30, 0 };

typedef struct data270_struct {
    Vec unk0;
    float unkC;
} Data270Struct;

Data270Struct lbl_1_data_270[8] = { { { 200, 0, 1400 }, 180 }, { { -200, 0, 1400 }, 180 }, { { 200, 0, -1400 }, 0 }, { { -200, 0, -1400 }, 0 },
    { { 1400, 0, 200 }, 270 }, { { 1400, 0, -200 }, 270 }, { { -1400, 0, 200 }, 90 }, { { -1400, 0, -200 }, 90 } };

Vec lbl_1_data_2F0[4] = { { 600, 0, 600 }, { 600, 0, -600 }, { -600, 0, 600 }, { -600, 0, -600 } };

void fn_1_512C(void)
{
    if (HuPadBtn[0] & PAD_BUTTON_X) {
        lbl_1_bss_200 = 35999;
    }
    print8(24, 32, 1.5f, "COUNT:%d MODE:%d MES:%d %d/%d %02x", lbl_1_bss_204, lbl_1_bss_A0->work[0], lbl_1_bss_1FA, lbl_1_bss_20, lbl_1_bss_24,
        lbl_1_bss_28);
    print8(24, 48, 1.5f, "%f %f %f", lbl_1_bss_0, lbl_1_bss_8, lbl_1_bss_4);
    print8(24, 64, 1.5f, "%x %x", HuMemHeapSizeGet(HEAP_SYSTEM) - HuMemUsedMallocSizeGet(HEAP_SYSTEM),
        HuMemHeapSizeGet(HEAP_DATA) - HuMemUsedMallocSizeGet(HEAP_DATA));
    lbl_1_bss_4 -= HuPadSubStkX[0] / 59.0f;
    lbl_1_bss_8 -= 4.0f * (HuPadSubStkY[0] / 59.0f);
    lbl_1_bss_0 -= (HuPadTrigL[0] / 150.0f) * 4.0f;
    lbl_1_bss_0 += (HuPadTrigR[0] / 150.0f) * 4.0f;
}

typedef struct work_player {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    Vec unk24;
    Vec unk30;
    Vec unk3C;
    float unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
} WorkPlayer;

typedef struct work_bomhei {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    float unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
} WorkBomhei;

void fn_1_5438(Vec *pos)
{
    float dist = VECDistance(pos, &((WorkPlayer *)lbl_1_bss_9C->data)->unk0);
    if (2000 < dist) {
        return;
    }
    if (1000 < dist) {
        omVibrate(lbl_1_bss_18, 12, 6, 6);
    }
    else if (300 < dist) {
        omVibrate(lbl_1_bss_18, 12, 4, 2);
    }
    else {
        omVibrate(lbl_1_bss_18, 12, 12, 0);
    }
}

BOOL fn_1_5528(Vec *pos, float offset)
{
    BOOL result = FALSE;
    float ofs = 700 - offset;
    Mtx rotMtx;

    if (ofs < pos->x) {
        pos->x = ofs;
    }
    if (ofs < pos->z) {
        pos->z = ofs;
    }
    if (-ofs > pos->x) {
        pos->x = -ofs;
    }
    if (-ofs > pos->z) {
        pos->z = -ofs;
    }
    if (ofs == ABS(pos->x) || ofs == ABS(pos->z)) {
        result = TRUE;
    }
    MTXRotDeg(rotMtx, 'Y', 45);
    MTXMultVec(rotMtx, pos, pos);
    ofs = (550 * sqrtf(2)) - offset;
    if (ofs < pos->x) {
        pos->x = ofs;
    }
    if (ofs < pos->z) {
        pos->z = ofs;
    }
    if (-ofs > pos->x) {
        pos->x = -ofs;
    }
    if (-ofs > pos->z) {
        pos->z = -ofs;
    }
    if (ofs == ABS(pos->x) || ofs == ABS(pos->z)) {
        result = TRUE;
    }
    MTXRotDeg(rotMtx, 'Y', -45);
    MTXMultVec(rotMtx, pos, pos);
    return result;
}

void fn_1_5894(Vec *pos1, Vec *pos2, float radius1, float radius2)
{
    float dx = pos1->x - pos2->x;
    float dz = pos1->z - pos2->z;
    float dist = sqrtf((dx * dx) + (dz * dz));
    if (radius1 + radius2 > dist) {
        if (0.0f == dist) {
            dx = 0;
            dz = -1;
        }
        else {
            dx /= dist;
            dz /= dist;
        }
        pos1->x = pos2->x + (dx * (radius1 + radius2));
        pos1->z = pos2->z + (dz * (radius1 + radius2));
    }
}

void fn_1_5A7C(WorkPlayer *player, omObjData *obj)
{
    float distMin;
    s32 i;
    player->unk58 = 2002;
    Hu3DMotionShiftSet(obj->model[0], obj->motion[3], 0, 8, HU3D_MOTATTR_NONE);
    distMin = 100000;
    for (i = 0; i < 3; i++) {
        float dist = VECDistance(&lbl_1_data_240[i], &player->unk0);
        if (distMin > dist) {
            distMin = dist;
            player->unk3C = lbl_1_data_240[i];
        }
    }
    player->unk24 = player->unk0;
    player->unk30 = player->unk0;
    player->unk48 = 15;
    lbl_1_bss_10 = HuAudFXEmiterPlay(2084, &player->unk0);
    lbl_1_bss_C = HuAudCharVoicePlayPos(player->unk5C, 291, &player->unk0);
}

void fn_1_5BF4(WorkPlayer *player, omObjData *obj)
{
    s32 i;
    s32 action;
    player->unkC.x = 0;
    player->unkC.y = 0;
    player->unkC.z = 0;
    player->unkC.x = player->unk4C / 4.0f;
    player->unkC.z = -(float)player->unk50 / 4.0f;
    action = 0;
    player->unk18.z = VECMagXZ(&player->unkC);
    if (0.5f <= player->unk18.z) {
        if (10.0f <= player->unk18.z) {
            player->unkC.x /= player->unk18.z;
            player->unkC.z /= player->unk18.z;
            player->unk18.z = 10;
            player->unkC.x = 10 * player->unkC.x;
            player->unkC.z = 10 * player->unkC.z;
        }
        player->unk18.y = fn_1_1E20(player->unk18.y, atan2d(player->unkC.x, player->unkC.z), 0.4f);
        if (7.0f <= player->unk18.z) {
            action = 2;
        }
        else {
            action = 1;
        }
    }
    VECAdd(&player->unk0, &player->unkC, &player->unk0);
    fn_1_5528(&player->unk0, 70);
    for (i = 0; i < 20; i++) {
        WorkBomhei *bomhei;
        if (NULL == lbl_1_bss_4C[i]) {
            continue;
        }
        bomhei = lbl_1_bss_4C[i]->data;
        if (bomhei->unk34 == 3004 && 30 > Hu3DMotionTimeGet(lbl_1_bss_4C[i]->model[2])) {
            float dx = player->unk0.x - bomhei->unk0.x;
            float dz = player->unk0.z - bomhei->unk0.z;
            if (200 > sqrtf((dx * dx) + (dz * dz))) {
                lbl_1_bss_14 = 1;
            }
        }
        else {
            fn_1_5894(&player->unk0, &bomhei->unk0, 70, 70);
        }
    }
    fn_1_5528(&player->unk0, 70);
    if (player->unk54 != action) {
        player->unk54 = action;
        Hu3DMotionShiftSet(obj->model[0], obj->motion[player->unk54], 0, 8, HU3D_MOTATTR_LOOP);
    }
}

void fn_1_6A00(omObjData *obj)
{
    WorkPlayer *player = obj->data;
    float dx;
    float dz;
    float dist;
    switch (player->unk58) {
        case 2000:
            if (lbl_1_bss_A0->work[0] >= 1004) {
                player->unk58++;
            }
            break;

        case 2001:
            player->unk4C = HuPadStkX[player->unk60];
            player->unk50 = HuPadStkY[player->unk60];
            fn_1_5BF4(player, obj);
            if (lbl_1_bss_A0->work[0] >= 1005) {
                if (lbl_1_bss_14) {
                    fn_1_5A7C(player, obj);
                }
                else {
                    player->unk58 = 2003;
                    Hu3DMotionShiftSet(obj->model[0], obj->motion[0], 0, 8, HU3D_MOTATTR_LOOP);
                }
            }
            break;

        case 2002:
            dx = player->unk3C.x - player->unk0.x;
            dz = player->unk3C.z - player->unk0.z;
            dist = sqrtf((dx * dx) + (dz * dz));
            if (player->unk48 < dist) {
                dx = player->unk48 * (dx / dist);
                dz = player->unk48 * (dz / dist);
            }
            player->unk18.x -= player->unk48;
            if (0.0f > player->unk18.x) {
                player->unk18.x += 360;
            }
            player->unk18.y = fn_1_1E20(player->unk18.y, atan2d(dx, dz) + 180.0, 0.4f);
            player->unk0.x += dx;
            player->unk0.z += dz;
            dist = VECDistance(&player->unk3C, &player->unk0) / VECDistance(&player->unk3C, &player->unk30);
            player->unk0.y = 500 * sind(dist * 180);
            player->unk48 *= 1.05f;
            if (lbl_1_bss_10 >= 0) {
                HuAudFXEmiterUpDate(lbl_1_bss_10, &player->unk0);
            }
            if (lbl_1_bss_C >= 0) {
                HuAudFXEmiterUpDate(lbl_1_bss_C, &player->unk0);
            }
            fn_1_5438(&player->unk24);
            if (lbl_1_bss_A0->work[0] >= 1007) {
                player->unk58 = 2005;
                HuAudSStreamPlay(4);
            }
            break;

        case 2003:
            if (lbl_1_bss_A0->work[0] >= 1007) {
                player->unk58 = 2004;
                HuAudSStreamPlay(1);
                Hu3DMotionShiftSet(obj->model[0], obj->motion[4], 0, 8, HU3D_MOTATTR_NONE);
            }
            break;

        case 2004:
            player->unk18.y = fn_1_1E20(player->unk18.y, 0, 0.4f);
            break;

        case 2005:
            break;

        default:
            OSReport("*** player mode error(%d)!!\n", player->unk58);
            break;
    }
    omSetTra(obj, player->unk0.x, player->unk0.y, player->unk0.z);
    omSetRot(obj, player->unk18.x, player->unk18.y, 0);
}

void fn_1_7328(omObjData *obj)
{
    WorkPlayer *player;
    s32 i;
    obj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkPlayer), MEMORY_DEFAULT_NUM);
    player = obj->data;
    player->unk5C = GWPlayerCfg[lbl_1_bss_18].character;
    player->unk60 = GWPlayerCfg[lbl_1_bss_18].pad_idx;
    player->unk58 = 2000;
    player->unk54 = 0;
    obj->model[0] = CharModelCreate(lbl_1_data_0[player->unk5C], 2);
    CharModelStepTypeSet(lbl_1_data_0[player->unk5C], 0);
    for (i = 0; i < 5; i++) {
        obj->motion[i] = CharModelMotionCreate(lbl_1_data_0[player->unk5C], lbl_1_data_128[player->unk5C][i]);
        CharModelMotionSet(lbl_1_data_0[player->unk5C], obj->motion[i]);
    }
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(obj->model[0], 2);
    Hu3DMotionSet(obj->model[0], obj->motion[0]);
    Hu3DModelShadowSet(obj->model[0]);
    player->unk18.x = 0;
    player->unk18.y = 0;
    player->unk0.x = 0;
    player->unk0.y = 0;
    player->unk0.z = 0;
    omSetTra(obj, player->unk0.x, player->unk0.y, player->unk0.z);
    omSetRot(obj, player->unk18.x, player->unk18.y, 0);
    Hu3DModelAttrReset(obj->model[0], HU3D_ATTR_DISPOFF);
    CharModelLayerSetAll2(6);
    CharModelMotionDataClose(lbl_1_data_0[player->unk5C]);
    obj->func = fn_1_6A00;
}

void fn_1_75B0(WorkBomhei *bomhei, omObjData *obj)
{
    float *data1F0;
    bomhei->unk34 = 3003;
    bomhei->unk24 = 10;
    for (data1F0 = &lbl_1_data_1F0[0][0]; 0.0f <= data1F0[0]; data1F0 += 2) {
        if (data1F0[0] <= lbl_1_bss_200) {
            bomhei->unk24 = data1F0[1];
        }
    }
    Hu3DModelAttrSet(obj->model[1], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(obj->model[1], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(obj->model[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF);
    HuAudFXEmiterPlay(2087, &bomhei->unk0);
}

BOOL fn_1_76CC(WorkBomhei *bomhei)
{
    if (bomhei->unk34 == 3002) {
        if (fn_1_5528(&bomhei->unk0, 70)) {
            return TRUE;
        }
    }
    else {
        float ofs = 700 - 70;

        if (ofs > bomhei->unk0.x && -ofs < bomhei->unk0.x) {
            if (ofs > bomhei->unk0.z && -ofs < bomhei->unk0.z) {
                if (bomhei->unk28 >= 0) {
                    lbl_1_bss_28 = lbl_1_bss_28 & ~(u32)(1 << bomhei->unk28);
                    bomhei->unk28 = -1;
                }
            }
        }
    }
    return FALSE;
}

void fn_1_7AD8(WorkBomhei *bomhei, omObjData *obj)
{
    float radius = 10 * lbl_1_data_1E4[bomhei->unk30];
    Vec playerOfs;
    Vec angle;

    s32 i;
    s32 state;
    BOOL temp_r25;

    angle.x = bomhei->unkC.y;
    if (bomhei->unk34 == 3002) {
        switch (bomhei->unk30) {
            case 0:
                bomhei->unk18.x--;
                if (0.0f > bomhei->unk18.x) {
                    radius = 0;
                    if (-bomhei->unk18.y > bomhei->unk18.x) {
                        bomhei->unk18.y = frandmod(120) + 120;
                        bomhei->unk18.x = frandmod(120) + 120;
                    }
                }
                else {
                    bomhei->unk18.z--;
                    if (0.0f > bomhei->unk18.z) {
                        bomhei->unk18.z = frandmod(120) + 120;
                        bomhei->unkC.z = frandf() * 360;
                    }
                }
                angle.x = bomhei->unkC.z;
                break;

            case 1:
            case 2:
                VECSubtract(&((WorkPlayer *)lbl_1_bss_9C->data)->unk0, &bomhei->unk0, &playerOfs);
                angle.x = atan2d(playerOfs.x, playerOfs.z);
                break;
        }
    }
    bomhei->unkC.y = fn_1_1E20(bomhei->unkC.y, angle.x, 0.05f);
    angle.z = radius * sind(bomhei->unkC.y);
    angle.y = radius * cosd(bomhei->unkC.y);
    bomhei->unk0.x += angle.z;
    bomhei->unk0.z += angle.y;
    if (0.0f < radius) {
        bomhei->unkC.x = fn_1_1E20(bomhei->unkC.x, atan2d(angle.z, angle.y), 0.2f);
    }
    state = 0;
    if (0.5f <= radius) {
        if (7.0f <= radius) {
            state = 2;
        }
        else {
            state = 1;
        }
    }
    temp_r25 = FALSE;
    if (fn_1_76CC(bomhei)) {
        temp_r25 = TRUE;
    }
    fn_1_5894(&bomhei->unk0, &((WorkPlayer *)lbl_1_bss_9C->data)->unk0, 70, 70);
    for (i = 0; i < 20; i++) {
        WorkBomhei *bomhei2;
        if (NULL == lbl_1_bss_4C[i]) {
            continue;
        }
        if (obj == lbl_1_bss_4C[i]) {
            continue;
        }
        bomhei2 = lbl_1_bss_4C[i]->data;
        if (bomhei2->unk34 != 3004) {
            fn_1_5894(&bomhei->unk0, &bomhei2->unk0, 70, 70);
        }
    }
    if (fn_1_76CC(bomhei)) {
        temp_r25 = TRUE;
    }
    if (temp_r25 && bomhei->unk30 == 0) {
        float radius = frandf() * 350;
        float angle2 = frandf() * 360;
        bomhei->unkC.z = atan2d((radius * sind(angle2)) - bomhei->unk0.x, (radius * cosd(angle2)) - bomhei->unk0.z);
        bomhei->unk18.z = frandmod(120) + 120;
    }
    if (bomhei->unk2C != state) {
        bomhei->unk2C = state;
        Hu3DMotionShiftSet(obj->model[0], obj->motion[bomhei->unk2C], 0, 8, HU3D_MOTATTR_LOOP);
    }
}

void fn_1_9724(omObjData *obj);

void fn_1_8D08(omObjData *obj)
{
    WorkBomhei *bomhei = obj->data;
    s32 i;
    switch (bomhei->unk34) {
        case 3000:
            if (lbl_1_bss_A0->work[0] >= 1004) {
                bomhei->unk34 = 3002;
            }
            break;

        case 3001:
            fn_1_7AD8(bomhei, obj);
            if (bomhei->unk28 < 0) {
                bomhei->unk34 = 3002;
            }
            break;

        case 3002:
            fn_1_7AD8(bomhei, obj);
            bomhei->unk24--;
            if (0.0f > bomhei->unk24) {
                fn_1_75B0(bomhei, obj);
            }
            break;

        case 3003:
            bomhei->unk24--;
            if (0.0f > bomhei->unk24) {
                bomhei->unk34++;
                Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(obj->model[2], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(obj->model[2], HU3D_ATTR_DISPOFF);
                HuAudFXEmiterPlay(2082, &bomhei->unk0);
                fn_1_5438(&bomhei->unk0);
            }
            break;

        case 3004:
            if (Hu3DMotionEndCheck(obj->model[2])) {
                fn_1_9724(obj);
                return;
            }
            break;

        case 3005:
            break;

        default:
            OSReport("*** bomhei mode error(%d)!!\n", bomhei->unk34);
            break;
    }
    if (bomhei->unk34 != 3004 && lbl_1_bss_A0->work[0] >= 1005) {
        bomhei->unk34 = 3005;
        Hu3DMotionShiftSet(obj->model[0], obj->motion[0], 0, 8, HU3D_MOTATTR_LOOP);
    }
    omSetTra(obj, bomhei->unk0.x, bomhei->unk0.y, bomhei->unk0.z);
    omSetRot(obj, 0, bomhei->unkC.x, 0);
    for (i = 0; i < 3; i++) {
        Hu3DModelPosSet(obj->model[i], bomhei->unk0.x, bomhei->unk0.y, bomhei->unk0.z);
        Hu3DModelRotSet(obj->model[i], 0, bomhei->unkC.x, 0);
    }
}

void fn_1_9164(omObjData *obj)
{
    WorkBomhei *bomhei = obj->data;
    s32 modelId;
    s32 i;
    omSetTra(obj, bomhei->unk0.x, bomhei->unk0.y, bomhei->unk0.z);
    omSetRot(obj, 0, bomhei->unkC.x, 0);
    modelId = fn_1_AC(0x1000);
    if (modelId < 0) {
        obj->model[0] = Hu3DModelLink(lbl_1_bss_3C[0]);
    }
    else {
        obj->model[0] = modelId;
    }
    modelId = fn_1_AC(0x2000);
    if (modelId < 0) {
        obj->model[1] = Hu3DModelLink(lbl_1_bss_3C[1]);
    }
    else {
        obj->model[1] = modelId;
    }
    modelId = fn_1_AC(0x3000);
    if (modelId < 0) {
        obj->model[2] = Hu3DModelLink(lbl_1_bss_3C[2]);
    }
    else {
        obj->model[2] = modelId;
    }
    for (i = 0; i < 4; i++) {
        obj->motion[i] = lbl_1_bss_2C[i];
    }
    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(obj->model[i], HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(obj->model[i], 3);
        Hu3DMotionTimeSet(obj->model[i], 0);
        Hu3DModelPosSet(obj->model[i], bomhei->unk0.x, bomhei->unk0.y, bomhei->unk0.z);
        Hu3DModelRotSet(obj->model[i], 0, bomhei->unkC.x, 0);
    }
    Hu3DModelLayerSet(obj->model[2], 4);
    Hu3DModelShadowSet(obj->model[0]);
    Hu3DModelShadowSet(obj->model[1]);
    for (i = 0; i < 20; i++) {
        if (NULL == lbl_1_bss_4C[i]) {
            lbl_1_bss_4C[i] = obj;
            break;
        }
    }
    Hu3DMotionSet(obj->model[0], obj->motion[0]);
    Hu3DModelAttrSet(obj->model[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(obj->model[0], HU3D_ATTR_DISPOFF);
    obj->func = fn_1_8D08;
}

void fn_1_956C(Vec *pos, float rotY, s32 type, s32 mode, s32 time)
{
    WorkBomhei *bomhei;
    omObjData *obj;
    lbl_1_bss_20++;
    obj = omAddObjEx(lbl_1_bss_238, 101, 3, 4, -1, fn_1_9164);
    obj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkBomhei), MEMORY_DEFAULT_NUM);
    bomhei = obj->data;
    bomhei->unk0 = *pos;
    bomhei->unkC.x = rotY;
    bomhei->unk30 = type;
    bomhei->unk34 = mode;
    bomhei->unk28 = time;
    bomhei->unkC.y = bomhei->unkC.x;
    bomhei->unkC.z = bomhei->unkC.x;
    bomhei->unk18.x = frandmod(120) + 120;
    bomhei->unk18.y = frandmod(120) + 120;
    bomhei->unk18.z = frandmod(120) + 120;
    bomhei->unk24 = frandmod(300) + 180;
    bomhei->unk2C = 0;
}

void fn_1_9724(omObjData *obj)
{
    s32 i;
    lbl_1_bss_20--;
    for (i = 0; i < 20; i++) {
        if (obj == lbl_1_bss_4C[i]) {
            lbl_1_bss_4C[i] = NULL;
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF);
        fn_1_24((i * 4096) + 4096, obj->model[i]);
    }
    omDelObjEx(lbl_1_bss_238, obj);
}

typedef struct work_bomhei2 {
    omObjData *unk0;
    omObjData *unk4;
    Vec unk8;
    Vec unk14;
    Vec unk20;
    float unk2C;
    float unk30;
    float unk34;
    BOOL unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    float unk48;
} WorkBomhei2;

void fn_1_9854(void)
{
    if (lbl_1_bss_200 % 900 == 0) {
        if (++lbl_1_bss_24 >= 20) {
            lbl_1_bss_24 = 20;
        }
    }
    if (lbl_1_bss_200 % 1800 == 0) {
        if (lbl_1_data_264[2] < 40) {
            lbl_1_data_264[2] += 10;
            if (lbl_1_data_264[2] > 100) {
                lbl_1_data_264[2] = 100;
            }
            lbl_1_data_264[1] -= 5;
            if (lbl_1_data_264[1] < 0) {
                lbl_1_data_264[1] = 0;
                lbl_1_data_264[0] -= 5;
            }
            lbl_1_data_264[0] -= 5;
            if (lbl_1_data_264[0] < 0) {
                lbl_1_data_264[0] = 0;
            }
        }
    }
    if (lbl_1_bss_24 > lbl_1_bss_20) {
        Data270Struct *data270 = NULL;
        s32 bitNum = frandmod(8);
        s32 i;
        for (i = 0; i < 8; i++) {
            if (((1 << bitNum) & lbl_1_bss_28) == 0) {
                data270 = &lbl_1_data_270[bitNum];
                lbl_1_bss_28 |= (1 << bitNum);
                (void)i;
                break;
            }
            bitNum++;
            if (bitNum >= 8) {
                bitNum -= 8;
            }
        }
        if (NULL != data270) {
            s32 type = 2;
            s32 chance = frandmod(100);
            Vec pos;
            for (i = 0; i < 3; i++) {
                if (lbl_1_data_264[i] > chance) {
                    type = i;
                    break;
                }
                chance -= lbl_1_data_264[i];
            }
            pos.x = data270->unk0.x;
            pos.y = data270->unk0.y;
            pos.z = data270->unk0.z;
            fn_1_956C(&pos, data270->unkC, type, 3001, bitNum);
        }
    }
}

WorkBomhei2 *fn_1_9CAC(omObjFunc func, s32 prio)
{
    omObjData *obj = omAddObjEx(lbl_1_bss_238, prio, 1, 4, -1, func);
    WorkBomhei2 *bomhei;
    s32 i;
    s32 modelId;
    obj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkBomhei2), MEMORY_DEFAULT_NUM);
    bomhei = obj->data;
    bomhei->unk38 = 1;
    bomhei->unk3C = 0;
    bomhei->unk0 = obj;
    bomhei->unk4 = NULL;
    bomhei->unk2C = 0;
    bomhei->unk8.x = 0;
    bomhei->unk8.y = 10;
    bomhei->unk8.z = 0;
    modelId = fn_1_AC(0x1000);
    if (modelId < 0) {
        obj->model[0] = Hu3DModelLink(lbl_1_bss_3C[0]);
    }
    else {
        obj->model[0] = modelId;
    }
    for (i = 0; i < 4; i++) {
        obj->motion[i] = lbl_1_bss_2C[i];
    }
    omSetTra(obj, bomhei->unk8.x, bomhei->unk8.y, bomhei->unk8.z);
    omSetRot(obj, 0, bomhei->unk2C, 0);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(obj->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(obj->model[0], 3);
    Hu3DMotionSet(obj->model[0], obj->motion[0]);
    Hu3DModelShadowSet(obj->model[0]);
    return bomhei;
}

void fn_1_9EF4(omObjData *obj)
{
    float dist;
    WorkBomhei2 *bomhei = obj->data;
    WorkBomhei2 *parent = bomhei->unk4->data;
    float vel = 3;
    float dx;
    float dz;

    s32 state;
    switch (bomhei->unk44) {
        case 0:
            if (bomhei->unk3C != 1) {
                bomhei->unk3C = 1;
                Hu3DMotionShiftSet(obj->model[0], obj->motion[bomhei->unk3C], 0, 8, HU3D_MOTATTR_LOOP);
            }
            dx = bomhei->unk14.x - bomhei->unk8.x;
            dz = bomhei->unk14.z - bomhei->unk8.z;
            dist = sqrtf((dx * dx) + (dz * dz));
            if (vel < dist) {
                dx = vel * (dx / dist);
                dz = vel * (dz / dist);
            }
            bomhei->unk8.x += dx;
            bomhei->unk8.z += dz;
            bomhei->unk2C = fn_1_1E20(bomhei->unk2C, atan2d(dx, dz), 0.4f);
            bomhei->unk30 = bomhei->unk2C;
            if (vel > dist) {
                switch (bomhei->unk40) {
                    case 1:
                    case 2:
                        bomhei->unk44 = 1;
                        bomhei->unk34 = 0;
                        bomhei->unk3C = 0;
                        Hu3DMotionShiftSet(obj->model[0], obj->motion[bomhei->unk3C], 0, 8, HU3D_MOTATTR_LOOP);
                        break;

                    default:
                        bomhei->unk44 = 3;
                        break;
                }
            }
            break;

        case 1:
            bomhei->unk2C = fn_1_1E20(bomhei->unk2C, atan2d(parent->unk8.x - bomhei->unk8.x, parent->unk8.z - bomhei->unk8.z), 0.05f);
            bomhei->unk30 = bomhei->unk2C;
            parent->unk2C = fn_1_1E20(parent->unk2C, atan2d(bomhei->unk8.x - parent->unk8.x, bomhei->unk8.z - parent->unk8.z), 0.05f);
            parent->unk30 = parent->unk2C;
            bomhei->unk34++;
            if (180.0f < bomhei->unk34) {
                bomhei->unk44 = 3;
                if (bomhei->unk40 == 2) {
                    bomhei->unk44 = 2;
                }
            }
            break;

        case 2: {
            Vec temp = parent->unk8;
            float tempAngle = parent->unk2C;
            parent->unk20 = parent->unk8;
            parent->unk8 = bomhei->unk8;
            parent->unk2C = bomhei->unk2C;
            bomhei->unk8 = temp;
            bomhei->unk2C = tempAngle;
            bomhei->unk30 = tempAngle;
            bomhei->unk34 = 0;
            bomhei->unk44 = 3;
        } break;

        case 3:
            bomhei->unk30 = fn_1_1E20(bomhei->unk30, atan2d(bomhei->unk20.x - bomhei->unk14.x, bomhei->unk20.z - bomhei->unk14.z), 0.2f);
            bomhei->unk2C = bomhei->unk30;
            bomhei->unk8.x += vel * sind(bomhei->unk30);
            bomhei->unk8.z += vel * cosd(bomhei->unk30);
            if (bomhei->unk3C != 1) {
                bomhei->unk3C = 1;
                Hu3DMotionShiftSet(obj->model[0], obj->motion[bomhei->unk3C], 0, 8, HU3D_MOTATTR_LOOP);
            }
            parent->unk2C = fn_1_1E20(parent->unk2C, atan2d(-parent->unk8.x, -parent->unk8.z), 0.05f);
            bomhei->unk34++;
            if (bomhei->unk40 == 2 && 60.0f < bomhei->unk34) {
                dx = parent->unk20.x - parent->unk8.x;
                dz = parent->unk20.z - parent->unk8.z;
                dist = sqrtf((dx * dx) + (dz * dz));
                if (vel < dist) {
                    dx = vel * (dx / dist);
                    dz = vel * (dz / dist);
                }
                parent->unk8.x += dx;
                parent->unk8.z += dz;
                state = 0;
                if (0.0f < dist) {
                    state = 1;
                }
                if (state != parent->unk3C) {
                    parent->unk3C = state;
                    Hu3DMotionShiftSet(parent->unk0->model[0], parent->unk0->motion[parent->unk3C], 0, 8, HU3D_MOTATTR_LOOP);
                }
            }
            if (1750 < VECMagXZ(&bomhei->unk8)) {
                parent->unk4 = NULL;
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF);
                fn_1_24(0x1000, obj->model[0]);
                omDelObjEx(lbl_1_bss_238, obj);
                return;
            }
            break;
    }
    omSetTra(obj, bomhei->unk8.x, bomhei->unk8.y, bomhei->unk8.z);
    omSetRot(obj, 0, bomhei->unk2C, 0);
    if (bomhei->unk38) {
        bomhei->unk38 = 0;
        Hu3DMotionTimeSet(obj->model[0], Hu3DMotionMaxTimeGet(obj->model[0]) * frandf());
        Hu3DModelAttrReset(obj->model[0], HU3D_ATTR_DISPOFF);
    }
}

s32 fn_1_ADDC(WorkBomhei2 *parent, WorkBomhei2 *bomhei)
{
    parent->unk4 = bomhei->unk0;
    bomhei->unk4 = parent->unk0;
    bomhei->unk40 = frandmod(3);
    bomhei->unk44 = 0;
    bomhei->unk14.x = 750.0f * ((0 > parent->unk8.x) ? -1 : 1);
    bomhei->unk14.z = 750.0f * ((0 > parent->unk8.z) ? -1 : 1);
    if (lbl_1_bss_204 & 0x1) {
        bomhei->unk8.x = 1400.0f * ((0 > parent->unk8.x) ? -1 : 1);
        bomhei->unk8.z = 750.0f * ((0 > parent->unk8.z) ? -1 : 1);
        bomhei->unk20.x = 750.0f * ((0 > parent->unk8.x) ? -1 : 1);
        bomhei->unk20.z = 1400.0f * ((0 > parent->unk8.z) ? -1 : 1);
    }
    else {
        bomhei->unk8.x = 750.0f * ((0 > parent->unk8.x) ? -1 : 1);
        bomhei->unk8.z = 1400.0f * ((0 > parent->unk8.z) ? -1 : 1);
        bomhei->unk20.x = 1400.0f * ((0 > parent->unk8.x) ? -1 : 1);
        bomhei->unk20.z = 750.0f * ((0 > parent->unk8.z) ? -1 : 1);
    }
    bomhei->unk2C = atan2d(bomhei->unk14.x - bomhei->unk8.x, bomhei->unk14.z - bomhei->unk8.z);
    bomhei->unk30 = bomhei->unk2C;
}

void fn_1_B234(omObjData *obj)
{
    WorkBomhei2 *bomhei = obj->data;
    if (NULL == bomhei->unk4) {
        bomhei->unk2C = atan2d(-bomhei->unk8.x, -bomhei->unk8.z);
        bomhei->unk48--;
        if (0.0f > bomhei->unk48) {
            WorkBomhei2 *bomheiNew;
            bomhei->unk48 = frandmod(1200) + 300;
            bomheiNew = fn_1_9CAC(fn_1_9EF4, 102);
            fn_1_ADDC(bomhei, bomheiNew);
        }
    }
    omSetTra(obj, bomhei->unk8.x, bomhei->unk8.y, bomhei->unk8.z);
    omSetRot(obj, 0, bomhei->unk2C, 0);
    if (bomhei->unk38) {
        bomhei->unk38 = 0;
        Hu3DMotionTimeSet(obj->model[0], Hu3DMotionMaxTimeGet(obj->model[0]) * frandf());
        Hu3DModelAttrReset(obj->model[0], HU3D_ATTR_DISPOFF);
    }
}

void fn_1_D70C(omObjData *obj);

void fn_1_BA2C(omObjData *obj)
{
    if (omSysExitReq) {
        fn_1_1F58(-1);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        obj->func = fn_1_D70C;
    }
    lbl_1_bss_204++;
    switch (obj->work[0]) {
        case 1000:
            if (!WipeStatGet()) {
                Vec dir;
                obj->work[0]++;
                lbl_1_bss_1C = 0;
                lbl_1_bss_220 = lbl_1_data_C4;
                lbl_1_bss_208 = lbl_1_data_DC;
                VECSubtract(&lbl_1_bss_208, &lbl_1_bss_220, &dir);
                VECNormalize(&dir, &dir);
                HuAudFXListnerSetEX(&lbl_1_bss_220, &dir, 14000.0, 36000.0, 1000.0, 300.0, 300.0);
            }

            break;

        case 1001:
            lbl_1_bss_1C++;
            if (30.0f < lbl_1_bss_1C) {
                obj->work[0]++;
                lbl_1_bss_1C = 0;
            }
            break;

        case 1002:
            lbl_1_bss_1C++;
            fn_1_13DC(lbl_1_bss_1C / 120, &lbl_1_data_D0);
            if (120.0f <= lbl_1_bss_1C) {
                obj->work[0]++;
                lbl_1_bss_1C = 0;
                fn_1_1350(&lbl_1_data_C4, &lbl_1_data_D0, &lbl_1_data_DC);
            }
            break;

        case 1003:
            if (lbl_1_bss_1FA < 0) {
                lbl_1_bss_1FA = MGSeqStartCreate();
            }
            else {
                if (lbl_1_bss_1F4 < 0 && (MGSeqStatGet(lbl_1_bss_1FA) & 0x10)) {
                    fn_1_1F24(70);
                }
                if (MGSeqStatGet(lbl_1_bss_1FA) == 0) {
                    obj->work[0]++;
                    lbl_1_bss_1FA = -1;
                }
            }
            break;

        case 1004:
            lbl_1_bss_200++;
            fn_1_580(lbl_1_bss_1AC, 0, lbl_1_bss_200);
            if (lbl_1_bss_14 || 35999 <= lbl_1_bss_200) {
                obj->work[0] = 1005;
                lbl_1_bss_1C = 0;
            }
            fn_1_9854();
            break;

        case 1005:
            if (lbl_1_bss_1FA < 0) {
                lbl_1_bss_1FA = MGSeqFinishCreate();
                fn_1_1F58(100);
                mgRecordExtra = lbl_1_bss_200;
            }
            else {
                lbl_1_bss_1C++;
                if (60.0f < lbl_1_bss_1C && !MGSeqStatGet(lbl_1_bss_1FA)) {
                    obj->work[0] = 1007;
                    if (lbl_1_bss_1FC < lbl_1_bss_200) {
                        obj->work[0] = 1006;
                        fn_1_798(13);
                    }
                    lbl_1_bss_1FA = -1;
                    lbl_1_bss_1C = 0;
                }
            }
            break;

        case 1006:
            if (lbl_1_bss_1FA < 0) {
                lbl_1_bss_1FA = MGSeqRecordCreate(lbl_1_bss_1FC);
            }
            else {
                if (!MGSeqStatGet(lbl_1_bss_1FA)) {
                    obj->work[0]++;
                    lbl_1_bss_1C = 0;
                    lbl_1_bss_1FA = -1;
                }
            }
            break;

        case 1007:
            lbl_1_bss_1C++;
            if (210.0f < lbl_1_bss_1C) {
                fn_1_1F58(-1);
                lbl_1_bss_1FA = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                obj->func = fn_1_D70C;
            }
            break;

        default:
            OSReport("*** main mode error(%d)!!\n", obj->work[0]);
            break;
    }
    fn_1_A40();
}

void fn_1_C970(omObjData *obj)
{
    s32 i;
    obj->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M461, 0x00));
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_NOCULL | HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(obj->model[0], 0);
    Hu3DModelShadowMapSet(obj->model[0]);
    omSetTra(obj, 0, 0, 0);
    omSetRot(obj, 0, 0, 0);
    obj->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M461, 0x01));
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_NOCULL | HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[1], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(obj->model[1], 1);
    Hu3DModelShadowSet(obj->model[1]);
    Hu3DModelPosSet(obj->model[1], 0, 0, 0);
    Hu3DModelRotSet(obj->model[1], 0, 0, 0);
    fn_1_B4C(64, DATA_MAKE_NUM(DATADIR_M461, 0x09));
    fn_1_9EC();
    for (i = 0; i < 2; i++) {
        Hu3DModelAttrReset(obj->model[i], HU3D_ATTR_DISPOFF);
    }
    HuAudFXPlay(2085);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    obj->func = fn_1_BA2C;
}

void ObjectSetup(void)
{
    s32 i;
    s32 light;
    float angle;
    float radius;
    float radiusPrev;
    OSReport("******* M461 ObjectSetup *********\n");
    lbl_1_bss_238 = omInitObjMan(200, 8192);
    omGameSysInit(lbl_1_bss_238);
    lbl_1_bss_14 = FALSE;
    lbl_1_bss_18 = FALSE;
    lbl_1_bss_204 = 0;
    lbl_1_bss_1FA = -1;
    lbl_1_bss_1F8 = -1;
    lbl_1_bss_1F4 = -1;
    lbl_1_bss_10 = -1;
    lbl_1_bss_C = -1;
    lbl_1_bss_4 = 0;
    lbl_1_bss_8 = 2200;
    lbl_1_bss_0 = 2300;
    lbl_1_bss_200 = 0;
    lbl_1_bss_1FC = GWMGRecordGet(13);
    lbl_1_bss_1EC = -1;
    Hu3DCameraViewportSet(HU3D_CAM0, 0, 0, 640, 480, 0, 1);
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 30, 20, 30000, 1.2f);
    fn_1_1350(&lbl_1_data_A0, &lbl_1_data_AC, &lbl_1_data_B8);
    light = Hu3DGLightCreateV(&lbl_1_data_E8, &lbl_1_data_F4, &lbl_1_data_100);
    Hu3DGLightStaticSet(light, 1);
    Hu3DGLightInfinitytSet(light);
    Hu3DShadowCreate(30, 20, 30000);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_data_104, &lbl_1_data_11C, &lbl_1_data_110);
    fn_1_0();
    for (i = 0; i < 20; i++) {
        s32 modelId;
        lbl_1_bss_4C[i] = NULL;
        modelId = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M461, 0x08));
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        fn_1_24(12288, modelId);
    }
    for (i = 0; i < 3; i++) {
        lbl_1_bss_3C[i] = Hu3DModelCreateFile(lbl_1_data_1C8[i]);
        Hu3DModelAttrSet(lbl_1_bss_3C[i], HU3D_ATTR_NOCULL | HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_2C[i] = Hu3DJointMotionFile(lbl_1_bss_3C[0], lbl_1_data_1D4[i]);
    }
    lbl_1_bss_28 = 0;
    lbl_1_bss_20 = 0;
    lbl_1_bss_24 = 10;
    angle = 360.0f * frandf();
    radiusPrev = -1;
    for (i = 0; i < lbl_1_bss_24; i++) {
        Vec pos;
        do {
            radius = frandmod(5);
        } while (radiusPrev == radius);
        radiusPrev = radius;
        pos.x = (200 + (100 * radius)) * sind(angle);
        pos.y = 0;
        pos.z = (200 + (100 * radius)) * cosd(angle);
        fn_1_956C(&pos, 360.0f * frandf(), (i == 0) ? 1 : 0, 3000, -1);
        angle += 36;
        if (360.0f <= angle) {
            angle -= 360.0f;
        }
    }
    for (i = 0; i < 4; i++) {
        WorkBomhei2 *bomhei2 = fn_1_9CAC(fn_1_B234, 103);
        bomhei2->unk8 = lbl_1_data_2F0[i];
        bomhei2->unk2C = atan2d(-bomhei2->unk8.x, -bomhei2->unk8.z);
        bomhei2->unk48 = frandmod(1200) + 300;
    }
    lbl_1_bss_9C = omAddObjEx(lbl_1_bss_238, 100, 1, 5, -1, fn_1_7328);
    lbl_1_bss_A0 = omAddObjEx(lbl_1_bss_238, 104, 2, 0, -1, fn_1_C970);
    lbl_1_bss_A0->work[0] = 1000;
    lbl_1_bss_1C = 0;
}

void fn_1_D70C(omObjData *obj)
{
    s32 i;
    if (WipeStatGet()) {
        return;
    }
    if (lbl_1_bss_1FA >= 0) {
        MGSeqKill(lbl_1_bss_1FA);
    }
    if (lbl_1_bss_1F8 >= 0) {
        MGSeqKill(lbl_1_bss_1F8);
    }
    MGSeqKillAll();
    HuAudAllStop();
    for (i = 0; i < 4; i++) {
        CharModelKill(lbl_1_data_0[GWPlayerCfg[i].character]);
    }
    omOvlReturnEx(1, 1);
}
