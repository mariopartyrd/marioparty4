#include "REL/executor.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "dolphin.h"
#include "ext_math.h"

#undef ABS
#define ABS(x) ((0 > (x)) ? -(x) : (x))

typedef struct unk_bss_790_struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ struct unk_bss_790_struct *unk04;
    /* 0x08 */ struct unk_bss_790_struct *unk08;
} UnkBss790Struct; // Size 0xC

typedef struct unk_bss_778_struct {
    /* 0x00 */ HsfanimStruct00 *unk00;
    /* 0x04 */ s32 *unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ struct unk_bss_778_struct *unk10;
    /* 0x14 */ struct unk_bss_778_struct *unk14;
} UnkBss778Struct; // Size 0x18

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2]; // padding?
} UnkBss5E8Struct; // Size 8

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ char unk2E[2];
    /* 0x30 */ float *unk30;
    /* 0x34 */ u16 *unk34;
} UnkFn2480Struct; // Size 0x38

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ float unk0C;
} UnkBssACStruct; // Size 0x10

typedef struct {
    /* 0x00 */ Vec *unk00;
    /* 0x04 */ Vec *unk04;
    /* 0x08 */ u8 (*unk08)[0xC]; // Vec?
    /* 0x0C */ u16 (*unk0C)[4];
    /* 0x10 */ UnkFn2480Struct *unk10;
    /* 0x14 */ Vec *unk14;
    /* 0x18 */ Vec *unk18;
    /* 0x1C */ GXColor *unk1C;
    /* 0x20 */ float (*unk20)[2];
    /* 0x24 */ void *unk24;
    /* 0x28 */ u32 unk28;
} UnkBss5ACStruct; // Size unknown

typedef struct {
    /* 0x00 */ void *unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ GXBool unk0C;
    /* 0x0D */ char unk0D[3]; // padding?
} UnkBss10Struct; // Size 0x10

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ s32 unk04;
} UnkBssA4InnerStruct; // Size 8

typedef struct {
    /* 0x000 */ UnkBssA4InnerStruct *unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C[10];
    /* 0x034 */ float unk34;
    /* 0x038 */ float unk38;
    /* 0x03C */ float unk3C;
    /* 0x040 */ float unk40;
    /* 0x044 */ s32 unk44;
    /* 0x048 */ s32 unk48;
    /* 0x04C */ Vec unk4C;
    /* 0x058 */ float unk58;
    /* 0x05C */ float unk5C;
    /* 0x060 */ float unk60;
    /* 0x064 */ float unk64;
    /* 0x068 */ float unk68;
    /* 0x06C */ float unk6C;
    /* 0x070 */ float unk70;
    /* 0x074 */ float unk74;
    /* 0x078 */ u16 unk78;
    /* 0x07A */ char unk7A[2];
    /* 0x07C */ s32 unk7C;
    /* 0x080 */ s32 unk80;
    /* 0x084 */ s32 unk84;
    /* 0x088 */ s32 unk88;
    /* 0x08C */ s32 unk8C;
    /* 0x090 */ s32 unk90;
    /* 0x094 */ s32 unk94;
    /* 0x098 */ s32 unk98;
    /* 0x09C */ s32 unk9C;
    /* 0x0A0 */ Vec unkA0[5];
    /* 0x0DC */ s32 unkDC[5];
    /* 0x0F0 */ s16 unkF0[5];
    /* 0x0FA */ char unkFA[2];
    /* 0x0FC */ float unkFC;
    /* 0x100 */ s32 unk100;
    /* 0x104 */ s32 unk104;
    /* 0x108 */ s32 unk108;
    /* 0x10C */ s32 unk10C;
    /* 0x110 */ s32 unk110;
} UnkBssA4Data; // Size 0x114

// Functions fn_1_0..fn_1_1FC4 are identical to the ones in m402Dll.
// lbl_1_bss_790..lbl_1_bss_5E8 seems to be the same as well.

void fn_1_0(void);
void fn_1_24(u16 arg0, s16 arg1);
s16 fn_1_AC(s16 arg0);
void fn_1_150(void);
void fn_1_174(s16 arg0, HsfanimStruct00 *arg1, s32 arg2, s32 arg3, s32 arg4, Vec *arg5, u8 arg6);
void fn_1_2D8(void);
void fn_1_414(void);
s16 fn_1_46C(s32 arg0);
void fn_1_580(s32 *arg0, s32 arg1, s32 arg2);
void fn_1_798(s32 arg0);
void fn_1_9EC(void);
void fn_1_A40(void);
void fn_1_B4C(float arg0, s32 arg1);
void fn_1_11F4(float arg0, Vec *arg1, Vec *arg2, Vec *arg3);
void fn_1_1350(Vec *arg0, Vec *arg1, Vec *arg2);
s32 fn_1_13DC(float arg0, Vec *arg1);
void fn_1_1710(float arg0, Vec *arg1);
void fn_1_1A60(Vec *arg0, s16 arg1, Vec *arg2);
void fn_1_1D18(s16 arg0, char *arg1, Vec *arg2);
void fn_1_1D70(s16 arg0, char *arg1, Vec *arg2, Mtx arg3);
float fn_1_1E20(float arg0, float arg1, float arg2);
void fn_1_1F24(s32 arg0);
void fn_1_1F58(s32 arg0);
void fn_1_1FC4(Vec *arg0, float *arg1, s32 arg2, s32 arg3);
s32 fn_1_23B4(Vec *arg0);
void fn_1_2480(UnkFn2480Struct *arg0, float arg1, float arg2);
void fn_1_2508(UnkFn2480Struct *arg0);
void fn_1_2714(u8 arg0, s32 arg1);
void fn_1_280C(omObjData *arg0);
void fn_1_2AAC(omObjData *arg0);
void fn_1_37A4(ModelData *arg0, Mtx arg1);
void fn_1_3F1C(ModelData *arg0, Mtx arg1);
void fn_1_3F40(ModelData *arg0, Mtx arg1);
void fn_1_4024(ModelData *arg0, Mtx arg1);
void fn_1_4700(ModelData *arg0, Mtx arg1);
void fn_1_4F28(omObjData *arg0);
void fn_1_5404(omObjData *arg0);
void fn_1_5530(Vec *arg0, s32 arg1);
void fn_1_557C(Vec *arg0, float arg1, s32 arg2, s32 arg3);
float fn_1_5664(Vec *arg0);
void fn_1_57FC(void);
void fn_1_58A0(omObjData *arg0);
void fn_1_5B28(omObjData *arg0);
void fn_1_5D3C(UnkBssA4Data *arg0, Vec *arg1);
void fn_1_5DCC(UnkBssA4Data *arg0);
void fn_1_6040(UnkBssA4Data *arg0, omObjData *arg1);
void fn_1_65BC(UnkBssA4Data *arg0);
void fn_1_6828(UnkBssA4Data *arg0);
u16 fn_1_68CC(UnkBssA4Data *arg0);
void fn_1_6BFC(omObjData *arg0);
void fn_1_798C(omObjData *arg0);
void fn_1_81B4(omObjData *arg0);
void fn_1_8AF0(void);
void fn_1_9288(omObjData *arg0);
void fn_1_AD10(omObjData *arg0);
void fn_1_B5C8(omObjData *arg0);

UnkBss790Struct lbl_1_bss_790;
UnkBss778Struct lbl_1_bss_778;
Process *lbl_1_bss_774;
Vec lbl_1_bss_768;
Vec lbl_1_bss_75C;
Vec lbl_1_bss_750;
Vec lbl_1_bss_744;
u32 lbl_1_bss_740;
s32 lbl_1_bss_73C;
u32 lbl_1_bss_738;
s16 lbl_1_bss_736;
s16 lbl_1_bss_734;
s32 lbl_1_bss_730;
s32 lbl_1_bss_72C;
float lbl_1_bss_728;
s32 lbl_1_bss_6E8[16];
UnkBss5E8Struct lbl_1_bss_5E8[32];
AnimData *lbl_1_bss_5E4;
AnimData *lbl_1_bss_5E0;
AnimData *lbl_1_bss_5DC;
AnimData *lbl_1_bss_5D8;
UnkBss5ACStruct lbl_1_bss_5AC;
UnkBssACStruct lbl_1_bss_AC[80];
u8 lbl_1_bss_A8;
omObjData **lbl_1_bss_A4;
omObjData *lbl_1_bss_A0;
omObjData *lbl_1_bss_9C;
omObjData *lbl_1_bss_98;
u8 lbl_1_bss_94_unused[4];
AnimData *lbl_1_bss_90;
s16 lbl_1_bss_8C;
AnimData *lbl_1_bss_88;
s16 lbl_1_bss_84;
float lbl_1_bss_80;
s32 lbl_1_bss_7C;
s32 lbl_1_bss_78;
s32 lbl_1_bss_74;
float lbl_1_bss_70;
float lbl_1_bss_6C;
s32 lbl_1_bss_68;
s32 lbl_1_bss_64;
s32 lbl_1_bss_60;
Vec lbl_1_bss_48[2];
Vec lbl_1_bss_30[2];
Vec lbl_1_bss_18[2];
Vec lbl_1_bss_0[2];

s16 lbl_1_data_0[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

UnkBss10Struct lbl_1_data_10[] = { { NULL, 0, 640, 480, GX_FALSE }, { NULL, 0, 640, 480, GX_FALSE }, { NULL, 0, 320, 240, GX_TRUE } };

Vec lbl_1_data_40[] = { { -450.0f, 0.0f, 0.0f }, { -450.0f, 0.0f, 0.0f }, { -150.0f, 0.0f, 0.0f }, { -150.0f, 0.0f, 0.0f }, { 150.0f, 0.0f, 0.0f },
    { 150.0f, 0.0f, 0.0f }, { 450.0f, 0.0f, 0.0f }, { 450.0f, 0.0f, 0.0f } };

float lbl_1_data_A0[]
    = { -600.0f, 300.0f, -600.0f, 300.0f, -300.0f, 300.0f, -300.0f, 300.0f, 0.0f, 300.0f, 0.0f, 300.0f, 300.0f, 300.0f, 300.0f, 300.0f };

u8 lbl_1_data_E0_unused[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0xFF };

GXColor lbl_1_data_E8 = { 0xD8, 0xE2, 0xE5, 0x10 };

void fn_1_0(void)
{
    lbl_1_bss_790.unk04 = NULL;
    lbl_1_bss_790.unk08 = NULL;
}

void fn_1_24(u16 arg0, s16 arg1)
{
    UnkBss790Struct *temp_r31;
    UnkBss790Struct *temp_r30;
    UnkBss790Struct *temp_r29;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r31), MEMORY_DEFAULT_NUM);
    temp_r31->unk00 = arg0;
    temp_r31->unk02 = arg1;
    temp_r30 = &lbl_1_bss_790;
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
    UnkBss790Struct *var_r31;
    UnkBss790Struct *temp_r29;
    UnkBss790Struct *temp_r30;
    s16 temp_r28;

    var_r31 = lbl_1_bss_790.unk08;
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
    lbl_1_bss_778.unk10 = NULL;
    lbl_1_bss_778.unk14 = NULL;
}

void fn_1_174(s16 arg0, HsfanimStruct00 *arg1, s32 arg2, s32 arg3, s32 arg4, Vec *arg5, u8 arg6)
{
    UnkBss778Struct *temp_r27;
    UnkBss778Struct *var_r31;
    UnkBss778Struct *temp_r28;
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
    temp_r28 = &lbl_1_bss_778;
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
    UnkBss778Struct *var_r31;
    UnkBss778Struct *temp_r28;
    UnkBss778Struct *temp_r29;
    s32 i;

    var_r31 = lbl_1_bss_778.unk14;
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
        lbl_1_bss_5E8[i].unk00 = 0;
        lbl_1_bss_5E8[i].unk04 = -1;
    }
}

s16 fn_1_46C(s32 arg0)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        if (arg0 == lbl_1_bss_5E8[i].unk00) {
            return Hu3DModelLink(lbl_1_bss_5E8[i].unk04);
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_1_bss_5E8[i].unk00 == 0) {
            lbl_1_bss_5E8[i].unk00 = arg0;
            lbl_1_bss_5E8[i].unk04 = Hu3DModelCreateFile(arg0);
            return lbl_1_bss_5E8[i].unk04;
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
    lbl_1_bss_728 = 0.0f;
    lbl_1_bss_738 = lbl_1_bss_73C;
    GWMGRecordSet(arg0, lbl_1_bss_738);
    fn_1_580(lbl_1_bss_6E8, 7, lbl_1_bss_73C);
}

void fn_1_9EC(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        espDispOn(lbl_1_bss_6E8[i]);
    }
}

void fn_1_A40(void)
{
    float temp_f31;
    s32 i;

    if (0.0f <= lbl_1_bss_728) {
        lbl_1_bss_728 += 16.0f;
        temp_f31 = 1.0 + 0.2f * sind(lbl_1_bss_728);
        for (i = 7; i <= 14; i++) {
            espScaleSet(lbl_1_bss_6E8[i], temp_f31, temp_f31);
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
    lbl_1_bss_6E8[15] = espEntry(arg1, 0, 0);
    espTPLvlSet(lbl_1_bss_6E8[15], 0.5f);
    espColorSet(lbl_1_bss_6E8[15], 0, 0, 0);
    espPosSet(lbl_1_bss_6E8[15], temp_f31, temp_f30);
    temp_f31 = 248.0f;
    temp_f30 = arg0 - 8.0f;
    lbl_1_bss_6E8[14] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 55), 0, 0);
    espPosSet(lbl_1_bss_6E8[14], temp_f31 - 18.0f, temp_f30);
    for (i = 7; i <= 13; i++) {
        lbl_1_bss_6E8[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 48), 0, 0);
        espPosSet(lbl_1_bss_6E8[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_6E8, 7, lbl_1_bss_738);
    temp_f31 = 248.0f;
    temp_f30 = arg0 + 8.0f;
    for (i = 0; i <= 6; i++) {
        lbl_1_bss_6E8[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 49), 0, 0);
        espPosSet(lbl_1_bss_6E8[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_6E8, 0, 0);
    for (i = 0; i < 16; i++) {
        espDrawNoSet(lbl_1_bss_6E8[i], 0);
        espDispOff(lbl_1_bss_6E8[i]);
        espAttrSet(lbl_1_bss_6E8[i], HUSPR_ATTR_NOANIM);
        espPriSet(lbl_1_bss_6E8[i], 0x80 + i);
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
    lbl_1_bss_768 = *arg0;
    lbl_1_bss_750 = *arg2;
}

s32 fn_1_13DC(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_768, &lbl_1_bss_75C, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_750, &lbl_1_bss_744, &spC);
    Hu3DCameraPosSetV(1, &sp18, arg1, &spC);
    if (1.0f <= arg0) {
        return 1;
    }
    else {
        lbl_1_bss_72C = 1;
        return 0;
    }
}

void fn_1_1710(float arg0, Vec *arg1)
{
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_768, &lbl_1_bss_75C, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_750, &lbl_1_bss_744, &spC);
    fn_1_1350(&sp18, arg1, &spC);
    lbl_1_bss_72C = 1;
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
    C_MTXLookAt(sp1C, &temp_r31->pos, &temp_r31->up, &temp_r31->target);
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
    lbl_1_bss_730 = HuAudSeqPlay(arg0);
}

void fn_1_1F58(s32 arg0)
{
    if (lbl_1_bss_730 >= 0) {
        if (arg0 < 0) {
            arg0 = 1000;
        }
        HuAudSeqFadeOut(lbl_1_bss_730, arg0);
    }
    lbl_1_bss_730 = -1;
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

s32 fn_1_23B4(Vec *arg0)
{
    float var_f31;
    float var_f30;
    s32 var_r31;
    s32 var_r30;

    var_f31 = 41.37931f;
    var_f30 = 86.206894f;
    var_r31 = (arg0->x + var_f31 / 2 + 600.0f) / var_f31;
    var_r30 = (arg0->z + var_f30 / 2 + 1250.0f) / var_f30;
    return var_r31 + var_r30 * 30;
}

void fn_1_2480(UnkFn2480Struct *arg0, float arg1, float arg2)
{
    Vec *var_r31;
    s32 i;

    arg0->unk28 = 0;
    var_r31 = lbl_1_bss_5AC.unk00;
    for (i = 0; i < 900; i++, var_r31++) {
        if (arg1 <= var_r31->x && arg2 >= var_r31->x) {
            arg0->unk34[arg0->unk28] = i;
            arg0->unk28++;
        }
    }
}

void fn_1_2508(UnkFn2480Struct *arg0)
{
    Vec spC;
    Vec *temp_r29;
    float *var_r30;
    u16 *var_r28;
    u32 i;

    if (arg0->unk2D == 3) {
        return;
    }
    if (arg0->unk2D == 2) {
        arg0->unk2D = 3;
    }
    var_r28 = arg0->unk34;
    var_r30 = arg0->unk30;
    for (i = 0; i < arg0->unk28; i++, var_r28++, var_r30++) {
        temp_r29 = &lbl_1_bss_5AC.unk00[*var_r28];
        VECSubtract(temp_r29, &arg0->unk0C, &spC);
        *var_r30 = VECMagXZ(&spC);
        if (arg0->unk2D == 0 && arg0->unk0C.z > temp_r29->z) {
            *var_r30 *= -1.0f;
        }
        if (arg0->unk2D == 1 && arg0->unk0C.z < temp_r29->z) {
            *var_r30 *= -1.0f;
        }
    }
}

void fn_1_2714(u8 arg0, s32 arg1)
{
    GXColor sp14 = { 0x1E, 0x66, 0xA2, 0xFF };
    UnkBss10Struct *temp_r31;

    temp_r31 = &lbl_1_data_10[arg0];
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);
    GXSetTexCopySrc(0, 0, 640, 480);
    GXSetTexCopyDst(temp_r31->unk08, temp_r31->unk0A, GX_TF_RGB565, temp_r31->unk0C);
    GXSetCopyClear(sp14, 0xFFFFFF);
    GXCopyTex(temp_r31->unk00, arg1);
    DCFlushRange(temp_r31->unk00, temp_r31->unk04);
}

void fn_1_280C(omObjData *arg0)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Vec *var_r27;
    Vec *var_r26;
    Vec *var_r25;
    Vec *temp_r28;
    Vec *var_r30;
    u16(*var_r31)[4];
    s32 i;

    var_r27 = lbl_1_bss_5AC.unk00;
    var_r26 = lbl_1_bss_5AC.unk04;
    var_r25 = lbl_1_bss_5AC.unk14;
    for (i = 0; i < 900; i++) {
        VECAdd(var_r27, var_r26, var_r25);
        var_r27++;
        var_r26++;
        var_r25++;
    }
    temp_r28 = lbl_1_bss_5AC.unk14;
    var_r31 = lbl_1_bss_5AC.unk0C;
    var_r30 = lbl_1_bss_5AC.unk18;
    memset(lbl_1_bss_5AC.unk18, 0, 900 * sizeof(*lbl_1_bss_5AC.unk18));
    for (i = 0; i < 841; i++) {
        VECSubtract(&temp_r28[(*var_r31)[1]], &temp_r28[(*var_r31)[0]], &sp2C);
        VECSubtract(&temp_r28[(*var_r31)[3]], &temp_r28[(*var_r31)[0]], &sp20);
        VECSubtract(&temp_r28[(*var_r31)[2]], &temp_r28[(*var_r31)[0]], &sp14);
        VECCrossProduct(&sp2C, &sp20, &sp8);
        VECNormalize(&sp8, &sp8);
        VECAdd(&sp8, &var_r30[(*var_r31)[0]], &var_r30[(*var_r31)[0]]);
        VECAdd(&sp8, &var_r30[(*var_r31)[1]], &var_r30[(*var_r31)[1]]);
        VECAdd(&sp8, &var_r30[(*var_r31)[3]], &var_r30[(*var_r31)[3]]);
        VECCrossProduct(&sp20, &sp14, &sp8);
        VECNormalize(&sp8, &sp8);
        VECAdd(&sp8, &var_r30[(*var_r31)[0]], &var_r30[(*var_r31)[0]]);
        VECAdd(&sp8, &var_r30[(*var_r31)[3]], &var_r30[(*var_r31)[3]]);
        VECAdd(&sp8, &var_r30[(*var_r31)[2]], &var_r30[(*var_r31)[2]]);
        var_r31++;
    }
    for (i = 0; i < 900; i++, var_r30++) {
        VECNormalize(var_r30, var_r30);
    }
    DCStoreRangeNoSync(lbl_1_bss_5AC.unk14, 900 * sizeof(*lbl_1_bss_5AC.unk14));
    DCStoreRangeNoSync(lbl_1_bss_5AC.unk18, 900 * sizeof(*lbl_1_bss_5AC.unk18));
    DCStoreRangeNoSync(lbl_1_bss_5AC.unk1C, 900 * sizeof(*lbl_1_bss_5AC.unk1C));
    DCStoreRangeNoSync(lbl_1_bss_5AC.unk20, 900 * sizeof(*lbl_1_bss_5AC.unk20));
}

void fn_1_2AAC(omObjData *arg0)
{
    Vec sp28;
    Vec *var_r25;
    UnkBss10Struct *temp_r26;
    UnkFn2480Struct *var_r31;
    u16(*var_r28)[4];
    s32 temp_r27;
    s32 i;
    s32 j;

    lbl_1_bss_5E4 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M405, 58));
    lbl_1_bss_5E0 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M405, 59));
    lbl_1_bss_5DC = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M405, 60));
    lbl_1_bss_5D8 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M405, 61));
    lbl_1_bss_5AC.unk00 = HuMemDirectMallocNum(HEAP_SYSTEM, 900 * sizeof(*lbl_1_bss_5AC.unk00), MEMORY_DEFAULT_NUM);
    lbl_1_bss_5AC.unk04 = HuMemDirectMallocNum(HEAP_SYSTEM, 900 * sizeof(*lbl_1_bss_5AC.unk04), MEMORY_DEFAULT_NUM);
    lbl_1_bss_5AC.unk08 = HuMemDirectMallocNum(HEAP_SYSTEM, 900 * sizeof(*lbl_1_bss_5AC.unk08), MEMORY_DEFAULT_NUM);
    lbl_1_bss_5AC.unk14 = HuMemDirectMallocNum(HEAP_SYSTEM, 900 * sizeof(*lbl_1_bss_5AC.unk14), MEMORY_DEFAULT_NUM);
    lbl_1_bss_5AC.unk18 = HuMemDirectMallocNum(HEAP_SYSTEM, 900 * sizeof(*lbl_1_bss_5AC.unk18), MEMORY_DEFAULT_NUM);
    lbl_1_bss_5AC.unk1C = HuMemDirectMallocNum(HEAP_SYSTEM, 900 * sizeof(*lbl_1_bss_5AC.unk1C), MEMORY_DEFAULT_NUM);
    lbl_1_bss_5AC.unk20 = HuMemDirectMallocNum(HEAP_SYSTEM, 900 * sizeof(*lbl_1_bss_5AC.unk20), MEMORY_DEFAULT_NUM);
    lbl_1_bss_5AC.unk0C = HuMemDirectMallocNum(HEAP_SYSTEM, 841 * sizeof(*lbl_1_bss_5AC.unk0C), MEMORY_DEFAULT_NUM);
    lbl_1_bss_5AC.unk10 = HuMemDirectMallocNum(HEAP_SYSTEM, 8 * sizeof(*lbl_1_bss_5AC.unk10), MEMORY_DEFAULT_NUM);
    for (i = 0; i < 8; i++) {
        lbl_1_bss_5AC.unk10[i].unk30 = HuMemDirectMallocNum(HEAP_SYSTEM, 900 * sizeof(*lbl_1_bss_5AC.unk10[i].unk30), MEMORY_DEFAULT_NUM);
        lbl_1_bss_5AC.unk10[i].unk34 = HuMemDirectMallocNum(HEAP_SYSTEM, 900 * sizeof(*lbl_1_bss_5AC.unk10[i].unk34), MEMORY_DEFAULT_NUM);
    }
    lbl_1_bss_5AC.unk28 = 0x10000;
    lbl_1_bss_5AC.unk24 = HuMemDirectMallocNum(HEAP_SYSTEM, lbl_1_bss_5AC.unk28, MEMORY_DEFAULT_NUM);
    DCFlushRange(lbl_1_bss_5AC.unk24, lbl_1_bss_5AC.unk28);
    var_r25 = lbl_1_bss_5AC.unk00;
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 30; var_r25++, j++) {
            var_r25->x = 41.37931f * j - 600.0f;
            var_r25->y = 0.0f;
            var_r25->z = 86.206894f * i - 1250.0f;
        }
    }
    memset(lbl_1_bss_5AC.unk04, 0, 900 * sizeof(*lbl_1_bss_5AC.unk04));
    var_r28 = lbl_1_bss_5AC.unk0C;
    for (i = 0; i < 29; i++) {
        for (j = 0; j < 29; j++) {
            if (!(i & 1)) {
                temp_r27 = j + i * 30;
                (*var_r28)[0] = temp_r27;
                (*var_r28)[1] = temp_r27 + 30;
                (*var_r28)[2] = temp_r27 + 1;
                (*var_r28)[3] = temp_r27 + 31;
            }
            else {
                temp_r27 = j + i * 30;
                (*var_r28)[1] = temp_r27;
                (*var_r28)[3] = temp_r27 + 30;
                (*var_r28)[0] = temp_r27 + 1;
                (*var_r28)[2] = temp_r27 + 31;
            }
            var_r28++;
        }
    }
    var_r31 = lbl_1_bss_5AC.unk10;
    for (i = 0; i < 8; i++, var_r31++) {
        var_r31->unk00 = lbl_1_data_40[i];
        var_r31->unk0C = lbl_1_data_40[i];
        var_r31->unk18 = 1.0f;
        var_r31->unk1C = 1.0f;
        var_r31->unk20 = 0.0f;
        var_r31->unk24 = 3.6f;
        var_r31->unk28 = 0;
        var_r31->unk2C = 0;
        var_r31->unk2D = 2;
        var_r31->unk00.z = 900.0f * ((i & 1) ? -1.0f : 1.0f);
        var_r31->unk0C.z = 900.0f * ((i & 1) ? -1.0f : 1.0f);
        var_r31->unk00 = lbl_1_bss_5AC.unk00[fn_1_23B4(&var_r31->unk00)];
        var_r31->unk0C = lbl_1_bss_5AC.unk00[fn_1_23B4(&var_r31->unk0C)];
        fn_1_2480(var_r31, lbl_1_data_A0[i * 2], lbl_1_data_A0[i * 2] + lbl_1_data_A0[i * 2 + 1]);
        fn_1_2508(var_r31);
    }
    memcpy(lbl_1_bss_5AC.unk14, lbl_1_bss_5AC.unk00, 900 * sizeof(*lbl_1_bss_5AC.unk14));
    for (i = 0; i < 900; i++) {
        lbl_1_bss_5AC.unk1C[i].r = 0xF0;
        lbl_1_bss_5AC.unk1C[i].g = 0xFA;
        lbl_1_bss_5AC.unk1C[i].b = 0xFF;
        lbl_1_bss_5AC.unk1C[i].a = 0xC0;
    }
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 30; j++) {
            temp_r27 = j + i * 30;
            lbl_1_bss_5AC.unk20[temp_r27][0] = 0.00083333335f * lbl_1_bss_5AC.unk00[temp_r27].x;
            lbl_1_bss_5AC.unk20[temp_r27][1] = 0.0004f * lbl_1_bss_5AC.unk00[temp_r27].z;
            lbl_1_bss_5AC.unk20[temp_r27][0] *= 3.0f;
            lbl_1_bss_5AC.unk20[temp_r27][1] *= 3.0f;
        }
    }
    for (i = 0; i < 80; i++) {
        lbl_1_bss_AC[i].unk0C = 0.0f;
    }
    for (i = 0; i < 3; i++) {
        temp_r26 = &lbl_1_data_10[i];
        temp_r26->unk04 = GXGetTexBufferSize(temp_r26->unk08, temp_r26->unk0A, GX_TF_RGB565, GX_FALSE, 0);
        temp_r26->unk00 = HuMemDirectMallocNum(HEAP_DATA, temp_r26->unk04, MEMORY_DEFAULT_NUM);
    }
    fn_1_280C(arg0);
    GXBeginDisplayList(lbl_1_bss_5AC.unk24, lbl_1_bss_5AC.unk28);
    for (i = 0; i < 29; i++) {
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 0x3C);
        for (j = 0; j < 30; j++) {
            GXPosition1x16(j + (i + 1) * 30);
            GXPosition1x16(j + i * 30);
        }
        GXEnd();
    }
    lbl_1_bss_5AC.unk28 = GXEndDisplayList();
    if (lbl_1_bss_5AC.unk28 == 0) {
        OSReport("DL buffer over!!\n");
    }
}

void fn_1_37A4(ModelData *arg0, Mtx arg1)
{
    Mtx spEC;
    Mtx spBC;
    Mtx sp8C;
    Mtx sp5C;
    Mtx sp2C;
    float var_f31;
    GXTexObj spC;
    UnkBss10Struct *temp_r31;

    GXLoadPosMtxImm(arg1, GX_PNMTX0);
    MTXInvXpose(arg1, spEC);
    GXLoadNrmMtxImm(spEC, GX_PNMTX0);
    temp_r31 = &lbl_1_data_10[2];
    GXInitTexObj(&spC, temp_r31->unk00, temp_r31->unk08, temp_r31->unk0A, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&spC, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&spC, GX_TEXMAP0);
    HuSprTexLoad(lbl_1_bss_5D8, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_5E0, 0, 2, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    temp_r31 = &lbl_1_data_10[0];
    GXInitTexObj(&spC, temp_r31->unk00, temp_r31->unk08, temp_r31->unk0A, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&spC, GX_TEXMAP3);
    GXSetNumTexGens(4);
    C_MTXLightPerspective(sp2C, 30.0f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, spEC);
    MTXConcat(spEC, arg1, spEC);
    MTXConcat(sp2C, Hu3DCameraMtx, spBC);
    MTXConcat(spBC, spEC, spBC);
    GXLoadTexMtxImm(spBC, GX_TEXMTX0, GX_MTX3x4);
    C_MTXLightPerspective(sp2C, 30.0f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, spEC);
    MTXConcat(spEC, arg1, spEC);
    MTXConcat(sp2C, Hu3DCameraMtx, spBC);
    MTXConcat(spBC, spEC, spBC);
    GXLoadTexMtxImm(spBC, GX_TEXMTX1, GX_MTX3x4);
    MTXRotRad(spEC, 'X', MTXDegToRad(-90));
    var_f31 = 0.0004f;
    MTXScale(sp8C, 0.00083333335f, var_f31, 0.0004f);
    MTXConcat(sp8C, spEC, sp5C);
    MTXTrans(spBC, 0.5f, 0.5f, 0.5f);
    MTXConcat(spBC, sp5C, sp5C);
    sp5C[0][1] = -0.01f;
    GXLoadTexMtxImm(sp5C, GX_TEXMTX2, GX_MTX2x4);
    MTXRotRad(spEC, 'X', MTXDegToRad(-90));
    var_f31 = 0.0004f;
    MTXScale(sp8C, var_f31, var_f31, var_f31);
    MTXConcat(sp8C, spEC, sp5C);
    MTXTrans(spBC, 0.5f, 0.5f, 0.0f);
    MTXConcat(spBC, sp5C, sp5C);
    GXLoadTexMtxImm(sp5C, GX_TEXMTX3, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_POS, GX_TEXMTX2, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_POS, GX_TEXMTX3, GX_FALSE, GX_PTIDENTITY);
    GXSetNumIndStages(2);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD2, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    MTXScale(spBC, -0.2f, -0.2f, 0.2f);
    GXSetIndTexMtx(GX_ITM_0, (float(*)[3])spBC, -2);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetIndTexOrder(GX_INDTEXSTAGE1, GX_TEXCOORD3, GX_TEXMAP3);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    MTXScale(spBC, 0.5f, 0.5f, 0.5f);
    GXSetIndTexMtx(GX_ITM_1, (float(*)[3])spBC, 0);
    GXSetTevIndWarp(GX_TEVSTAGE1, GX_INDTEXSTAGE1, GX_TRUE, GX_FALSE, GX_ITM_1);
    GXSetNumTevStages(2);
    lbl_1_data_E8.a = lbl_1_bss_A8;
    GXSetTevColor(GX_TEVREG0, lbl_1_data_E8);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
    GXSetArray(GX_VA_POS, lbl_1_bss_5AC.unk14, 0xC);
    GXSetCullMode(GX_CULL_BACK);
    GXCallDisplayList(lbl_1_bss_5AC.unk24, lbl_1_bss_5AC.unk28);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
}

void fn_1_3F1C(ModelData *arg0, Mtx arg1)
{
    fn_1_280C(NULL);
}

void fn_1_3F40(ModelData *arg0, Mtx arg1)
{
    fn_1_2714(2, GX_FALSE);
}

void fn_1_4024(ModelData *arg0, Mtx arg1)
{
    Mtx sp98;
    Mtx sp68;
    Mtx sp38;
    GXTexObj sp18;
    UnkBss10Struct *temp_r31;

    fn_1_2714(1, GX_FALSE);
    GXLoadPosMtxImm(arg1, GX_PNMTX0);
    C_MTXLightPerspective(sp98, 30.0f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXInverse(Hu3DCameraMtx, sp68);
    MTXConcat(sp68, arg1, sp68);
    MTXConcat(sp98, Hu3DCameraMtx, sp38);
    MTXConcat(sp38, sp68, sp68);
    GXLoadTexMtxImm(sp68, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    temp_r31 = &lbl_1_data_10[2];
    GXInitTexObj(&sp18, temp_r31->unk00, temp_r31->unk08, temp_r31->unk0A, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&sp18, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
    GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-600.0f, -2.0f, -1250.0f);
    GXPosition3f32(600.0f, -2.0f, -1250.0f);
    GXPosition3f32(600.0f, -2.0f, 1250.0f);
    GXPosition3f32(-600.0f, -2.0f, 1250.0f);
    GXEnd();
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-600.0f, -100.0f, -1250.0f);
    GXPosition3f32(600.0f, -100.0f, -1250.0f);
    GXPosition3f32(600.0f, -100.0f, 1250.0f);
    GXPosition3f32(-600.0f, -100.0f, 1250.0f);
    GXEnd();
    fn_1_2714(2, GX_FALSE);
    temp_r31 = &lbl_1_data_10[1];
    GXInitTexObj(&sp18, temp_r31->unk00, temp_r31->unk08, temp_r31->unk0A, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&sp18, GX_TEXMAP0);
    GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-600.0f, -2.0f, -1250.0f);
    GXPosition3f32(600.0f, -2.0f, -1250.0f);
    GXPosition3f32(600.0f, -2.0f, 1250.0f);
    GXPosition3f32(-600.0f, -2.0f, 1250.0f);
    GXEnd();
}

void fn_1_4700(ModelData *arg0, Mtx arg1)
{
    Mtx sp60;
    Mtx44 sp20;
    float temp_f31;
    GXColor sp1C = { 0x00, 0x00, 0x00, 0xFF };
    GXColor sp18 = { 0xFF, 0xFF, 0xFF, 0x20 };
    UnkBssACStruct *var_r31;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 var_r24;
    s16 i;

    C_MTXOrtho(sp20, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 100.0f);
    GXSetProjection(sp20, GX_ORTHOGRAPHIC);
    MTXIdentity(sp60);
    GXLoadPosMtxImm(sp60, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, sp1C);
    GXSetNumTexGens(0);
    HuSprTexLoad(lbl_1_bss_5DC, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetScissor(0, 0, lbl_1_data_10->unk08, lbl_1_data_10->unk0A);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_RGBX8, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2u16(0, 0);
    GXPosition2u16(lbl_1_data_10->unk08, 0);
    GXPosition2u16(lbl_1_data_10->unk08, lbl_1_data_10->unk0A);
    GXPosition2u16(0, lbl_1_data_10->unk0A);
    GXEnd();
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_RGBA4, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    var_r31 = lbl_1_bss_AC;
    var_r24 = 0;
    for (i = 0; i < 80; i++, var_r31++) {
        if (0.1f >= var_r31->unk0C) {
            continue;
        }
        var_r24 = 1;
        temp_f31 = 200.0f * (1.0f - var_r31->unk0C);
        sp18.a = 255.0f * var_r31->unk0C;
        GXSetChanMatColor(GX_COLOR0A0, sp18);
        temp_r28 = lbl_1_data_10->unk08 * (1250.0f + var_r31->unk00.x - temp_f31) / 2500.0f;
        temp_r27 = lbl_1_data_10->unk0A * (1250.0f + var_r31->unk00.z - temp_f31) / 2500.0f;
        temp_r26 = lbl_1_data_10->unk08 * (1250.0f + var_r31->unk00.x + temp_f31) / 2500.0f;
        temp_r25 = lbl_1_data_10->unk0A * (1250.0f + var_r31->unk00.z + temp_f31) / 2500.0f;
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2s16(temp_r28, temp_r27);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition2s16(temp_r26, temp_r27);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition2s16(temp_r26, temp_r25);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition2s16(temp_r28, temp_r25);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
    }
    if (var_r24 != 0 && lbl_1_bss_A8 < 24) {
        lbl_1_bss_A8++;
    }
    fn_1_2714(0, GX_TRUE);
}

void fn_1_4F28(omObjData *arg0)
{
    Vec spC;
    float temp_f27;
    float var_f29;
    float *var_r30;
    UnkBssACStruct *var_r27;
    UnkFn2480Struct *var_r31;
    u16 *var_r25;
    s32 i;
    u32 j;

    memset(lbl_1_bss_5AC.unk04, 0, 900 * sizeof(*lbl_1_bss_5AC.unk04));
    var_r27 = lbl_1_bss_AC;
    for (i = 0; i < 80; i++, var_r27++) {
        if (0.1f >= var_r27->unk0C) {
            continue;
        }
        var_r27->unk0C *= 0.95f;
    }
    var_r31 = lbl_1_bss_5AC.unk10;
    for (i = 0; i < 8; i++, var_r31++) {
        var_r31->unk20 += var_r31->unk24 - var_r31->unk24 * frandf() / 2;
        if (360.0f <= var_r31->unk20) {
            var_r31->unk20 -= 360.0f;
        }
        if (0.0f > var_r31->unk20) {
            var_r31->unk20 += 360.0f;
        }
        var_r31->unk18 *= 0.99f;
        var_r31->unk1C += 0.01f * (var_r31->unk18 - var_r31->unk1C);
        var_r31->unk0C.z += 0.02f * (var_r31->unk00.z - var_r31->unk0C.z);
        if (5.0f > var_r31->unk1C) {
            var_r31->unk1C = 5.0f;
        }
        fn_1_2508(var_r31);
        temp_f27 = var_r31->unk20;
        var_r25 = var_r31->unk34;
        var_r30 = var_r31->unk30;
        for (j = 0; j < var_r31->unk28; j++, var_r25++, var_r30++) {
            if (0.0f > *var_r30) {
                continue;
            }
            var_f29 = 1.0f - *var_r30 / 625.0f;
            if (0.2f > var_f29) {
                var_f29 = 0.2f;
            }
            lbl_1_bss_5AC.unk04[*var_r25].y += var_r31->unk1C * var_f29 * var_f29 * sind(temp_f27 + *var_r30 * var_f29 * 3.6f);
        }
    }
}

void fn_1_5404(omObjData *arg0)
{
    lbl_1_bss_A8 = 0;
    omSetTra(arg0, 0.0f, 0.0f, 0.0f);
    fn_1_2AAC(arg0);
    arg0->model[0] = Hu3DHookFuncCreate(fn_1_4700);
    Hu3DModelLayerSet(arg0->model[0], 0);
    arg0->model[1] = Hu3DHookFuncCreate(fn_1_3F40);
    Hu3DModelLayerSet(arg0->model[1], 2);
    arg0->model[2] = Hu3DHookFuncCreate(fn_1_4024);
    Hu3DModelLayerSet(arg0->model[2], 4);
    arg0->model[3] = Hu3DHookFuncCreate(fn_1_37A4);
    Hu3DModelLayerSet(arg0->model[3], 6);
    arg0->model[4] = Hu3DHookFuncCreate(fn_1_3F1C);
    Hu3DModelLayerSet(arg0->model[4], 7);
    arg0->func = fn_1_4F28;
}

void fn_1_5530(Vec *arg0, s32 arg1)
{
    UnkBssACStruct *temp_r31;

    temp_r31 = &lbl_1_bss_AC[arg1];
    temp_r31->unk00 = *arg0;
    temp_r31->unk0C = 1.0f;
}

void fn_1_557C(Vec *arg0, float arg1, s32 arg2, s32 arg3)
{
    UnkFn2480Struct *temp_r31;

    temp_r31 = &lbl_1_bss_5AC.unk10[arg2 + (arg3 ^ 1)];
    temp_r31->unk2C = 0;
    temp_r31->unk2D = 2;
    temp_r31 = &lbl_1_bss_5AC.unk10[arg2 + arg3];
    temp_r31->unk2D = arg3;
    temp_r31->unk18 = arg1;
    temp_r31->unk24 = 10.8f;
    temp_r31->unk00.x = arg0->x;
    temp_r31->unk00.y = 0.0f;
    temp_r31->unk00.z = arg0->z;
    if (1.0f > temp_r31->unk1C) {
        temp_r31->unk20 = 270.0f;
    }
    if (temp_r31->unk2C == 0) {
        temp_r31->unk2C = 1;
        temp_r31->unk0C = temp_r31->unk00;
    }
}

float fn_1_5664(Vec *arg0)
{
    return lbl_1_bss_5AC.unk04[fn_1_23B4(arg0)].y;
}

#include "src/REL/executor.c"

Vec lbl_1_data_100 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_10C = { 450.0f, 300.0f, 500.0f };
Vec lbl_1_data_118 = { 450.0f, 150.0f, 1300.0f };
Vec lbl_1_data_124 = { 0.0f, 800.0f, -3000.0f };
Vec lbl_1_data_130 = { 0.0f, 0.0f, -500.0f };
Vec lbl_1_data_13C = { -2400.0f, 3500.0f, 0.0f };
Vec lbl_1_data_148 = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_154 = { 0.0f, 5000.0f, 1000.0f };
Vec lbl_1_data_160 = { 0.0f, -5.0f, -1.0f };
GXColor lbl_1_data_16C = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_170 = { 0.0f, 8000.0f, 1000.0f };
Vec lbl_1_data_17C = { 0.0f, 0.0f, 0.0f };

s32 lbl_1_data_188[8][8] = { { DATA_MAKE_NUM(DATADIR_MARIOMOT, 42), DATA_MAKE_NUM(DATADIR_M405, 0), DATA_MAKE_NUM(DATADIR_M405, 8),
                                 DATA_MAKE_NUM(DATADIR_M405, 16), DATA_MAKE_NUM(DATADIR_MARIOMOT, 43), DATA_MAKE_NUM(DATADIR_M405, 24),
                                 DATA_MAKE_NUM(DATADIR_M405, 32), DATA_MAKE_NUM(DATADIR_M405, 40) },
    { DATA_MAKE_NUM(DATADIR_LUIGIMOT, 42), DATA_MAKE_NUM(DATADIR_M405, 1), DATA_MAKE_NUM(DATADIR_M405, 9), DATA_MAKE_NUM(DATADIR_M405, 17),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 43), DATA_MAKE_NUM(DATADIR_M405, 25), DATA_MAKE_NUM(DATADIR_M405, 33), DATA_MAKE_NUM(DATADIR_M405, 41) },
    { DATA_MAKE_NUM(DATADIR_PEACHMOT, 42), DATA_MAKE_NUM(DATADIR_M405, 2), DATA_MAKE_NUM(DATADIR_M405, 10), DATA_MAKE_NUM(DATADIR_M405, 18),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 43), DATA_MAKE_NUM(DATADIR_M405, 26), DATA_MAKE_NUM(DATADIR_M405, 34), DATA_MAKE_NUM(DATADIR_M405, 42) },
    { DATA_MAKE_NUM(DATADIR_YOSHIMOT, 42), DATA_MAKE_NUM(DATADIR_M405, 3), DATA_MAKE_NUM(DATADIR_M405, 11), DATA_MAKE_NUM(DATADIR_M405, 19),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 43), DATA_MAKE_NUM(DATADIR_M405, 27), DATA_MAKE_NUM(DATADIR_M405, 35), DATA_MAKE_NUM(DATADIR_M405, 43) },
    { DATA_MAKE_NUM(DATADIR_WARIOMOT, 42), DATA_MAKE_NUM(DATADIR_M405, 4), DATA_MAKE_NUM(DATADIR_M405, 12), DATA_MAKE_NUM(DATADIR_M405, 20),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 43), DATA_MAKE_NUM(DATADIR_M405, 28), DATA_MAKE_NUM(DATADIR_M405, 36), DATA_MAKE_NUM(DATADIR_M405, 44) },
    { DATA_MAKE_NUM(DATADIR_DONKEYMOT, 42), DATA_MAKE_NUM(DATADIR_M405, 5), DATA_MAKE_NUM(DATADIR_M405, 13), DATA_MAKE_NUM(DATADIR_M405, 21),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 43), DATA_MAKE_NUM(DATADIR_M405, 29), DATA_MAKE_NUM(DATADIR_M405, 37), DATA_MAKE_NUM(DATADIR_M405, 45) },
    { DATA_MAKE_NUM(DATADIR_DAISYMOT, 42), DATA_MAKE_NUM(DATADIR_M405, 6), DATA_MAKE_NUM(DATADIR_M405, 14), DATA_MAKE_NUM(DATADIR_M405, 22),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 43), DATA_MAKE_NUM(DATADIR_M405, 30), DATA_MAKE_NUM(DATADIR_M405, 38), DATA_MAKE_NUM(DATADIR_M405, 46) },
    { DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 42), DATA_MAKE_NUM(DATADIR_M405, 7), DATA_MAKE_NUM(DATADIR_M405, 15), DATA_MAKE_NUM(DATADIR_M405, 23),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 43), DATA_MAKE_NUM(DATADIR_M405, 31), DATA_MAKE_NUM(DATADIR_M405, 39), DATA_MAKE_NUM(DATADIR_M405, 47) } };

s32 lbl_1_data_288[] = { DATA_MAKE_NUM(DATADIR_M405, 55), DATA_MAKE_NUM(DATADIR_M405, 56) };

s32 lbl_1_data_290[] = { DATA_MAKE_NUM(DATADIR_MGCONST, 0), DATA_MAKE_NUM(DATADIR_MGCONST, 1), DATA_MAKE_NUM(DATADIR_MGCONST, 2),
    DATA_MAKE_NUM(DATADIR_MGCONST, 3), DATA_MAKE_NUM(DATADIR_MGCONST, 4), DATA_MAKE_NUM(DATADIR_MGCONST, 5), DATA_MAKE_NUM(DATADIR_MGCONST, 6),
    DATA_MAKE_NUM(DATADIR_MGCONST, 7) };

s32 lbl_1_data_2B0[] = { -224, -128, 128, 224 };

s32 lbl_1_data_2C0[] = { 0, 0, 0, 0, -20, -18, 19, -18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s32 lbl_1_data_310[] = { -24, 17, 24, 17, 0, 17 };
s32 lbl_1_data_328[] = { 1, 0, 3, 2, 4 };

u8 lbl_1_data_33C[][3] = { { 1, 0, 1 }, { 2, 3, 0 }, { 1, 0, 0 } };

u16 lbl_1_data_346[] = { 0x0100, 0x0200, 0x0040, 0x0020, 0x0000 };

UnkBssA4InnerStruct lbl_1_data_350 = { 3570.0f, 2 };
UnkBssA4InnerStruct lbl_1_data_358 = { 3330.0f, 2 };
UnkBssA4InnerStruct lbl_1_data_360 = { 3180.0f, 2 };
UnkBssA4InnerStruct lbl_1_data_368 = { 3060.0f, 6 };

HsfanimStruct00 lbl_1_data_370 = { 0x0014, { 0x00, 0x00 }, // padding?
    1.0f, 30.0f, 0.0f, { 0.0f, 0.05f, 0.0f }, 1.0f, 0.999f, 30.0f, 1.03f, 0x0004,
    { { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { 0xFF, 0xFF, 0xFF, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 } } };

HsfanimStruct00 lbl_1_data_3C0 = { 0x0014, { 0x00, 0x00 }, // padding?
    1.0f, 10.0f, 360.0f, { 0.0f, 0.1f, 0.0f }, 1.0f, 1.0f, 50.0f, 1.05f, 0x0001,
    { { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { 0xFF, 0xFF, 0xFF, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 } } };

void fn_1_57FC(void)
{
    UnkBssA4Data *temp_r31;
    s32 i;

    fontcolor = 0;
    for (i = 0; i < 4; i++) {
        temp_r31 = lbl_1_bss_A4[i]->data;
        print8(24, i * 16 + 132, 1.5f, "%d %f %f %f", temp_r31->unk108, temp_r31->unk34, temp_r31->unk38, temp_r31->unk3C);
    }
}

void fn_1_58A0(omObjData *arg0)
{
    Vec sp8;
    s16 var_r30;

    switch (arg0->work[0]) {
        case 0:
            if (lbl_1_bss_98->work[0] >= 1004 && 60.0f < lbl_1_bss_80) {
                arg0->work[0]++;
                lbl_1_bss_6C = 0.0f;
                Hu3DMotionSet(arg0->model[0], arg0->motion[1]);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(arg0->model[1], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            }
            break;
        case 1:
            lbl_1_bss_6C += 1.0f;
            var_r30 = arg0->model[0];
            fn_1_1D18(var_r30, "g001m1_021-itemhook_r", &sp8);
            Hu3DParManAttrSet(lbl_1_bss_84, 1);
            if (50.0f == lbl_1_bss_6C) {
                HuAudFXPlay(0xD);
            }
            if (50.0f <= lbl_1_bss_6C && 60.0f > lbl_1_bss_6C) {
                Hu3DParManPosSet(lbl_1_bss_84, sp8.x - 10.0f, sp8.y + 35.0f, sp8.z - 20.0f);
                Hu3DParManAttrReset(lbl_1_bss_84, 1);
            }
            if (Hu3DMotionEndCheck(arg0->model[0]) != 0) {
                arg0->work[0]++;
                Hu3DMotionSet(arg0->model[0], arg0->motion[0]);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
            }
            break;
        case 2:
            break;
    }
}

void fn_1_5B28(omObjData *arg0)
{
    s32 i;

    arg0->work[0] = 0;
    omSetTra(arg0, 850.0f, 30.0f, 1350.0f);
    omSetRot(arg0, 0.0f, -90.0f, 0.0f);
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M405, 53));
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M405, 54));
    for (i = 0; i < 2; i++) {
        arg0->motion[i] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_288[i]);
    }
    for (i = 0; i < 2; i++) {
        Hu3DModelAttrSet(arg0->model[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->model[i], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(arg0->model[i], 5);
        Hu3DModelShadowSet(arg0->model[i]);
    }
    Hu3DMotionSet(arg0->model[0], *arg0->motion);
    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelHookSet(arg0->model[0], "g001m1_021-itemhook_r", arg0->model[1]);
    Hu3DMotionTimeSet(arg0->model[1], 1.0f);
    for (i = 0; i < 2; i++) {
        Hu3DModelAttrReset(arg0->model[i], HU3D_ATTR_DISPOFF);
    }
    arg0->func = fn_1_58A0;
}

void fn_1_5D3C(UnkBssA4Data *arg0, Vec *arg1)
{
    fn_1_5530(arg1, arg0->unk98 + arg0->unk108 * 20);
    arg0->unk98 = (arg0->unk98 + 1) % 20;
}

void fn_1_5DCC(UnkBssA4Data *arg0)
{
    Vec sp8;
    float var_f31;
    UnkFn2480Struct *temp_r31;

    var_f31 = 30.0f;
    if (arg0->unk104 == 2) {
        var_f31 = 20.0f;
    }
    if (arg0->unk104 == 4) {
        var_f31 = 40.0f;
    }
    sp8 = arg0->unk4C;
    sp8.z -= 70.0f * (arg0->unk94 == 1 ? 1.0f : -1.0f);
    if (1250.0f < ABS(sp8.z)) {
        sp8.z = 1250.0f * (0.0f > sp8.z ? -1 : 1);
    }
    fn_1_557C(&sp8, var_f31, (3 - arg0->unk108) * 2, arg0->unk94 & 1);
}

void fn_1_6040(UnkBssA4Data *arg0, omObjData *arg1)
{
    Vec sp44[5];
    s32 var_r27;
    s32 var_r26;
    s32 i;

    var_r27 = 0;
    var_r26 = 0;
    for (i = 0; i < 5; i++) {
        sp44[i] = arg0->unkA0[i];
        if (lbl_1_bss_740 % 5 == i) {
            fn_1_1D18(arg1->model[0], CharModelHookNameGet(arg0->unk10C, 4, lbl_1_data_328[i]), &arg0->unkA0[i]);
        }
        if ((0.0f <= sp44[i].y && 0.0f > arg0->unkA0[i].y) || (0.0f >= sp44[i].y && 0.0f < arg0->unkA0[i].y)) {
            var_r26++;
            arg0->unkDC[i] = 10;
            if (i < 2) {
                var_r27++;
                fn_1_5D3C(arg0, &arg0->unkA0[i]);
            }
        }
        Hu3DParManPosSet(arg0->unkF0[i], arg0->unkA0[i].x, arg0->unkA0[i].y, arg0->unkA0[i].z);
        if (--arg0->unkDC[i] <= 0) {
            Hu3DParManAttrSet(arg0->unkF0[i], 1);
        }
        else {
            Hu3DParManAttrReset(arg0->unkF0[i], 1);
        }
    }
    if (var_r27 > 0) {
        HuAudFXPlay(0x535);
    }
    if (var_r26 > 0) {
        fn_1_5DCC(arg0);
        if (arg0->unk9C != 0) {
            arg0->unk9C = 0;
            omVibrate(arg0->unk108, 12, 4, 2);
            HuAudFXPlay(0x536);
        }
    }
}

void fn_1_65BC(UnkBssA4Data *arg0)
{
    u8 *temp_r30;
    s32 i;

    temp_r30 = lbl_1_data_33C[arg0->unk94];
    for (i = 4; i < 10; i++) {
        espDispOff(arg0->unk0C[i]);
    }
    espPosSet(arg0->unk0C[temp_r30[0] + 6], arg0->unk04 + lbl_1_data_310[0], arg0->unk08 + lbl_1_data_310[1]);
    espDispOn(arg0->unk0C[temp_r30[0] + 6]);
    espPosSet(arg0->unk0C[temp_r30[1] + 6], arg0->unk04 + lbl_1_data_310[2], arg0->unk08 + lbl_1_data_310[3]);
    espDispOn(arg0->unk0C[temp_r30[1] + 6]);
    espPosSet(arg0->unk0C[temp_r30[2] + 4], arg0->unk04 + lbl_1_data_310[4], arg0->unk08 + lbl_1_data_310[5]);
    espDispOn(arg0->unk0C[temp_r30[2] + 4]);
}

void fn_1_6828(UnkBssA4Data *arg0)
{
    s32 temp_r30;

    temp_r30 = (113.0f - arg0->unk68) / 10.0f - 1.0f;
    if (temp_r30 > 9) {
        espDispOff(arg0->unk0C[3]);
    }
    else {
        espDispOn(arg0->unk0C[3]);
        espBankSet(arg0->unk0C[3], temp_r30);
    }
}

u16 fn_1_68CC(UnkBssA4Data *arg0)
{
    u16 var_r29;
    u8 *temp_r30;

    var_r29 = 0;
    arg0->unk34 -= 1.0f;
    if (6.0f > arg0->unk34) {
        arg0->unk34 = 6.0f;
    }
    if (50.0f > arg0->unk38) {
        arg0->unk38 = 50.0f;
    }
    arg0->unk3C -= 1.0f;
    if (0.0f > arg0->unk3C) {
        arg0->unk3C = arg0->unk34 / (arg0->unk38 / 30.0f);
        if (6.0f > arg0->unk3C) {
            arg0->unk3C = 6.0f;
        }
        if (420.0f < arg0->unk34 && 60.0f > arg0->unk68 && arg0->unk88 < 10) {
            arg0->unk40 = 20.0f;
        }
        if (arg0->unk44 >= 2 && 70.0f < arg0->unk68) {
            arg0->unk3C = 8.0f;
        }
        else if (0.0f != arg0->unk40) {
            arg0->unk3C = arg0->unk40;
        }
        else if (arg0->unk48 > 0) {
            if ((arg0->unk48 & 1) == 1) {
                arg0->unk38 += 40.0f * (arg0->unk44 + 1);
                arg0->unk3C = 8.0f;
                arg0->unk48--;
            }
            else if (frandmod(10) == 0) {
                arg0->unk3C = 8.0f;
                arg0->unk48--;
            }
        }
        temp_r30 = lbl_1_data_33C[arg0->unk94];
        var_r29 = lbl_1_data_346[temp_r30[0]] | lbl_1_data_346[temp_r30[1]];
    }
    if (0.0f != arg0->unk40) {
        if (30.0f < arg0->unk68) {
            arg0->unk40 = 0.0f;
        }
    }
    else if (10.0f > arg0->unk68) {
        arg0->unk40 = 20.0f;
    }
    return var_r29;
}

void fn_1_6BFC(omObjData *arg0)
{
    float var_f31;
    float var_f30;
    UnkBssA4Data *temp_r31;
    u8 *temp_r28;
    u16 var_r24;
    s32 temp_r20;
    s32 var_r27;
    s32 i;

    temp_r31 = arg0->data;
    if (lbl_1_bss_98->work[0] == 1006) {
        temp_r31->unk100 = 2005;
        temp_r31->unk104 = 0;
        Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(arg0->model[0], arg0->motion[temp_r31->unk104], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        Hu3DMotionSpeedSet(arg0->model[0], 1.0f);
        for (i = 0; i < 5; i++) {
            Hu3DParManAttrSet(temp_r31->unkF0[i], 1);
        }
        if (lbl_1_bss_7C == temp_r31->unk108) {
            temp_r20 = temp_r31->unk108;
            if (!_CheckFlag(FLAG_ID_MAKE(1, 12))) {
                GWPlayer[temp_r20].coin_win = 10;
            }
        }
        arg0->func = fn_1_798C;
        return;
    }
    if (GWPlayerCfg[temp_r31->unk108].iscom) {
        temp_r31->unk78 = fn_1_68CC(temp_r31);
    }
    else {
        temp_r31->unk78 |= HuPadBtnDown[temp_r31->unk110];
    }
    var_r27 = temp_r31->unk104;
    switch (temp_r31->unk100) {
        case 2003:
            temp_r28 = lbl_1_data_33C[temp_r31->unk94];
            if (temp_r28[2] == 1) {
                var_r24 = lbl_1_data_346[temp_r28[0]] | lbl_1_data_346[temp_r28[1]];
            }
            else {
                var_r24 = lbl_1_data_346[temp_r28[temp_r31->unk90 & 1]];
            }
            temp_r31->unk6C += 1.0f;
            if (20.0f <= temp_r31->unk6C) {
                temp_r31->unk68 += temp_r31->unk74;
                if (0.0f == temp_r31->unk70) {
                    if (5.0f < temp_r31->unk74) {
                        temp_r31->unk74 -= 1.0f;
                    }
                }
                else {
                    temp_r31->unk74 = 7.0f;
                }
                temp_r31->unk6C = 0.0f;
                temp_r31->unk70 = 0.0f;
                if (100.0f <= temp_r31->unk68) {
                    temp_r31->unk68 = 100.0f;
                }
            }
            temp_r31->unk88++;
            if (1.0f <= temp_r31->unk68 && var_r24 == (temp_r31->unk78 & var_r24)) {
                temp_r31->unk78 = 0;
                temp_r31->unk8C = 0;
                temp_r31->unk84++;
                if (temp_r31->unk80 == 0) {
                    temp_r31->unk80 = 1;
                }
                if (temp_r31->unk84 < 10) {
                    temp_r31->unk90 ^= 1;
                    var_f31 = 30.0f;
                    if (temp_r31->unk88 < 10) {
                        var_f31 = 35.0f;
                    }
                    if (temp_r31->unk94 == 1) {
                        var_f30 = 1.0f;
                    }
                    else {
                        var_f30 = -1.0f;
                    }
                    temp_r31->unk5C += var_f31 * var_f30;
                    temp_r31->unk68 -= 5.0f;
                    temp_r31->unk70 += 5.0f;
                    if (0.0f >= temp_r31->unk68) {
                        temp_r31->unk68 = 0.0f;
                        temp_r31->unk5C = temp_r31->unk4C.z;
                    }
                }
                temp_r31->unk88 = 0;
            }
            if (temp_r31->unk80 > 0) {
                if (++temp_r31->unk80 > 60) {
                    temp_r31->unk80 = 0;
                    temp_r31->unk84 = 0;
                }
            }
            if (temp_r28[2] == 1) {
                if (temp_r31->unk78 != 0) {
                    if (++temp_r31->unk8C >= 2) {
                        temp_r31->unk78 = 0;
                        temp_r31->unk8C = 0;
                    }
                }
            }
            else {
                temp_r31->unk78 = 0;
            }
            if (1.0f > ABS(temp_r31->unk5C - temp_r31->unk4C.z)) {
                temp_r31->unk7C++;
                if (30.0f == temp_r31->unk7C) {
                    var_r27 = 0;
                }
            }
            else {
                temp_r31->unk7C = 0;
                var_r27 = temp_r31->unk94 + 2;
                var_f31 = 0.1f * (temp_r31->unk5C - temp_r31->unk4C.z);
                temp_r31->unk4C.z += var_f31;
                temp_r31->unk38 -= ABS(var_f31);
                temp_r31->unk64 = (temp_r31->unk64 + ABS(var_f31)) / 2;
                if (temp_r31->unk94 >= 2) {
                    if (1150.0f < ABS(temp_r31->unk4C.z)) {
                        temp_r31->unk4C.z = 1150.0f * (0.0f > temp_r31->unk4C.z ? -1 : 1);
                        if (lbl_1_bss_7C < 0) {
                            lbl_1_bss_7C = temp_r31->unk108;
                        }
                        else if (frandmod(100) > 50) {
                            lbl_1_bss_7C = temp_r31->unk108;
                        }
                    }
                }
                else {
                    if (1150.0f < ABS(temp_r31->unk4C.z)) {
                        temp_r31->unk100 = 2004;
                        temp_r31->unkFC = 10.0f;
                        temp_r31->unk4C.z = 1150.0f * (0.0f > temp_r31->unk4C.z ? -1 : 1);
                        temp_r31->unk5C = temp_r31->unk4C.z;
                        var_r27 = temp_r31->unk94 + 5;
                        temp_r31->unk104 = var_r27;
                        Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                        Hu3DMotionShiftSet(arg0->model[0], arg0->motion[temp_r31->unk104], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
                        temp_r31->unk94++;
                        if (temp_r31->unk94 > lbl_1_bss_78) {
                            lbl_1_bss_78 = temp_r31->unk94;
                        }
                        fn_1_65BC(temp_r31);
                        omVibrate(temp_r31->unk108, 12, 6, 6);
                    }
                }
            }
            break;
        case 2004:
            temp_r31->unkFC -= 1.0f;
            if (0.0f > temp_r31->unkFC && Hu3DMotionEndCheck(arg0->model[0])) {
                temp_r31->unk100 = 2003;
                temp_r31->unk8C = 0;
                temp_r31->unk78 = 0;
                temp_r31->unk80 = 0;
                temp_r31->unk84 = 0;
                temp_r31->unk88 = 0;
                temp_r31->unk7C = 0;
                var_r27 = temp_r31->unk94 + 2;
            }
            break;
        default:
            OSReport("*** player mode error(%d)!!\n", temp_r31->unk100);
            break;
    }
    if (var_r27 != temp_r31->unk104) {
        temp_r31->unk104 = var_r27;
        Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(arg0->model[0], arg0->motion[temp_r31->unk104], 0.0f, 30.0f, HU3D_MOTATTR_LOOP);
    }
    if (temp_r31->unk104 >= 2 && temp_r31->unk104 <= 4) {
        temp_r31->unk60 = 0.5f * temp_r31->unk64;
        if (1.0f > temp_r31->unk60) {
            temp_r31->unk60 = 1.0f;
        }
        if (2.0f < temp_r31->unk60) {
            temp_r31->unk60 = 2.0f;
        }
    }
    else {
        temp_r31->unk60 = 1.0f;
        temp_r31->unk64 = 0.0f;
    }
    Hu3DMotionSpeedSet(arg0->model[0], temp_r31->unk60);
    fn_1_6040(temp_r31, arg0);
    fn_1_6828(temp_r31);
    omSetTra(arg0, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
    omSetRot(arg0, 0.0f, temp_r31->unk58, 0.0f);
}

void fn_1_798C(omObjData *arg0)
{
    UnkBssA4Data *temp_r31;
    s32 i;

    temp_r31 = arg0->data;
    switch (temp_r31->unk100) {
        case 2000:
            if (lbl_1_bss_98->work[0] >= 1003) {
                temp_r31->unk100++;
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            }
            break;
        case 2001:
            if (lbl_1_bss_98->work[0] >= 1005) {
                temp_r31->unk100++;
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                for (i = 0; i <= 3; i++) {
                    espDispOn(temp_r31->unk0C[i]);
                }
                fn_1_65BC(temp_r31);
            }
            else if (30.0f == Hu3DMotionTimeGet(arg0->model[0])) {
                Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_PAUSE);
            }
            break;
        case 2002:
            if (Hu3DMotionEndCheck(arg0->model[0])) {
                temp_r31->unk100++;
                temp_r31->unk4C.z = 900.0f;
                temp_r31->unk5C = temp_r31->unk4C.z;
                temp_r31->unk104 = 2;
                Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_PAUSE);
                Hu3DMotionSet(arg0->model[0], arg0->motion[temp_r31->unk104]);
                Hu3DMotionCalc(arg0->model[0]);
                arg0->func = fn_1_6BFC;
            }
            break;
        case 2005:
            if (frandmod(60) == 0) {
                fn_1_5D3C(temp_r31, &temp_r31->unk4C);
            }
            if (lbl_1_bss_7C == temp_r31->unk108) {
                temp_r31->unk58 = fn_1_1E20(temp_r31->unk58, 0.0f, 0.1f);
            }
            if (lbl_1_bss_98->work[0] >= 1008 && temp_r31->unk104 == 0 && lbl_1_bss_7C == temp_r31->unk108
                && 1.0f == Hu3DMotionTimeGet(arg0->model[0])) {
                temp_r31->unk104 = 7;
                Hu3DMotionOverlaySet(arg0->model[0], arg0->motion[temp_r31->unk104]);
                Hu3DMotionOverlayTimeSet(arg0->model[0], 0.0f);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_OVL_PAUSE);
                HuAudCharVoicePlay(temp_r31->unk10C, 0x124);
            }
            if (temp_r31->unk104 == 7 && 73.0f <= Hu3DMotionOverlayTimeGet(arg0->model[0])) {
                Hu3DMotionOverlayTimeSet(arg0->model[0], 35.0f);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_OVL_PAUSE);
            }
            temp_r31->unk4C.y = -62.0f + 4.0f * fn_1_5664(&temp_r31->unk4C);
            break;
        default:
            OSReport("*** player mode error(%d)!!\n", temp_r31->unk100);
            break;
    }
    if (temp_r31->unk100 < 2005) {
        fn_1_6040(temp_r31, arg0);
    }
    omSetTra(arg0, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
    omSetRot(arg0, 0.0f, temp_r31->unk58, 0.0f);
}

void fn_1_81B4(omObjData *arg0)
{
    float var_f31;
    UnkBssA4Data *temp_r31;
    s32 i;

    temp_r31 = arg0->data;
    temp_r31->unk00 = NULL;
    temp_r31->unk108 = arg0->work[0];
    temp_r31->unk10C = GWPlayerCfg[temp_r31->unk108].character;
    temp_r31->unk110 = GWPlayerCfg[temp_r31->unk108].pad_idx;
    temp_r31->unk68 = 100.0f;
    temp_r31->unk6C = 0.0f;
    temp_r31->unk70 = 0.0f;
    temp_r31->unk74 = 7.0f;
    temp_r31->unk7C = 0;
    temp_r31->unk80 = 0;
    temp_r31->unk84 = 0;
    temp_r31->unk88 = 0;
    temp_r31->unk78 = 0;
    temp_r31->unk8C = 0;
    temp_r31->unk90 = 0;
    temp_r31->unk94 = 0;
    temp_r31->unk98 = 0;
    temp_r31->unk9C = 1;
    temp_r31->unk104 = 1;
    temp_r31->unk100 = 2000;
    temp_r31->unkFC = 0.0f;
    temp_r31->unk60 = 1.0f;
    temp_r31->unk64 = 0.0f;
    arg0->model[0] = CharModelCreate(lbl_1_data_0[temp_r31->unk10C], 4);
    CharModelStepTypeSet(lbl_1_data_0[temp_r31->unk10C], 0);
    for (i = 0; i < 8; i++) {
        arg0->motion[i] = CharModelMotionCreate(lbl_1_data_0[temp_r31->unk10C], lbl_1_data_188[temp_r31->unk10C][i]);
        CharModelMotionSet(lbl_1_data_0[temp_r31->unk10C], arg0->motion[i]);
    }
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(arg0->model[0], 3);
    Hu3DMotionSet(arg0->model[0], arg0->motion[1]);
    Hu3DMotionTimeSet(arg0->model[0], 1.0f);
    CharModelVoiceEnableSet(temp_r31->unk10C, arg0->motion[0], 0);
    temp_r31->unk4C.x = 450.0f - 300.0f * arg0->work[0];
    temp_r31->unk4C.y = -32.0f;
    temp_r31->unk4C.z = 1328.7f;
    temp_r31->unk58 = 180.0f;
    omSetTra(arg0, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
    omSetRot(arg0, 0.0f, temp_r31->unk58, 0.0f);
    for (i = 0; i < 1; i++) {
        Hu3DModelAttrReset(arg0->model[i], HU3D_ATTR_DISPOFF);
    }
    temp_r31->unk04 = 288.0f + lbl_1_data_2B0[temp_r31->unk108];
    temp_r31->unk08 = 80;
    temp_r31->unk0C[0] = espEntry(DATA_MAKE_NUM(DATADIR_M405, 64), 0, 0);
    espTPLvlSet(temp_r31->unk0C[0], 0.5f);
    espColorSet(temp_r31->unk0C[0], 0, 0, 0);
    temp_r31->unk0C[1] = espEntry(DATA_MAKE_NUM(DATADIR_M405, 63), 0, 0);
    temp_r31->unk0C[2] = espEntry(lbl_1_data_290[temp_r31->unk10C], 0, 0);
    temp_r31->unk0C[3] = espEntry(DATA_MAKE_NUM(DATADIR_M405, 65), 0, 0);
    temp_r31->unk0C[4] = espEntry(DATA_MAKE_NUM(DATADIR_M405, 66), 0, 0);
    temp_r31->unk0C[5] = espEntry(DATA_MAKE_NUM(DATADIR_M405, 67), 0, 0);
    temp_r31->unk0C[6] = espEntry(DATA_MAKE_NUM(DATADIR_M405, 68), 0, 0);
    temp_r31->unk0C[7] = espEntry(DATA_MAKE_NUM(DATADIR_M405, 69), 0, 0);
    temp_r31->unk0C[8] = espEntry(DATA_MAKE_NUM(DATADIR_M405, 70), 0, 0);
    temp_r31->unk0C[9] = espEntry(DATA_MAKE_NUM(DATADIR_M405, 71), 0, 0);
    for (i = 0; i < 10; i++) {
        espDrawNoSet(temp_r31->unk0C[i], 0);
        espDispOff(temp_r31->unk0C[i]);
        espAttrSet(temp_r31->unk0C[i], HUSPR_ATTR_NOANIM);
        espBankSet(temp_r31->unk0C[i], 0);
        espPriSet(temp_r31->unk0C[i], 128 - i);
        espPosSet(temp_r31->unk0C[i], temp_r31->unk04 + lbl_1_data_2C0[i * 2], temp_r31->unk08 + lbl_1_data_2C0[i * 2 + 1]);
    }
    for (i = 0; i < 5; i++) {
        temp_r31->unkF0[i] = Hu3DParManLink(lbl_1_bss_8C, &lbl_1_data_370);
        Hu3DParManAttrSet(temp_r31->unkF0[i], 1);
        Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(temp_r31->unkF0[i]), 1);
        Hu3DModelLayerSet(Hu3DParManModelIDGet(temp_r31->unkF0[i]), 7);
        temp_r31->unkDC[i] = 0;
        fn_1_1D18(arg0->model[0], CharModelHookNameGet(temp_r31->unk10C, 4, lbl_1_data_328[i]), &temp_r31->unkA0[i]);
    }
    temp_r31->unk34 = 0.0f;
    temp_r31->unk48 = 0;
    temp_r31->unk38 = 0.0f;
    temp_r31->unk3C = 0.0f;
    temp_r31->unk40 = 0.0f;
    if (GWPlayerCfg[temp_r31->unk108].iscom) {
        temp_r31->unk44 = GWPlayerCfg[temp_r31->unk108].diff;
        switch (GWPlayerCfg[temp_r31->unk108].diff) {
            case 0:
                temp_r31->unk00 = &lbl_1_data_350;
                var_f31 = 0.1f;
                break;
            case 1:
                temp_r31->unk00 = &lbl_1_data_358;
                var_f31 = 0.1f;
                break;
            case 2:
                temp_r31->unk00 = &lbl_1_data_360;
                var_f31 = 0.1f;
                break;
            case 3:
            default:
                temp_r31->unk44 = 3;
                temp_r31->unk00 = &lbl_1_data_368;
                var_f31 = 0.05f;
                break;
        }
        temp_r31->unk34 = temp_r31->unk00->unk00 + temp_r31->unk00->unk00 * var_f31 * frandf();
        temp_r31->unk48 = temp_r31->unk00->unk04;
        temp_r31->unk38 = 6700.0f;
        temp_r31->unk3C = 0.0f;
        temp_r31->unk40 = 0.0f;
    }
    CharModelMotionDataClose(lbl_1_data_0[temp_r31->unk10C]);
    arg0->func = fn_1_798C;
}

void fn_1_8AF0(void)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f26;
    float var_f27;
    float var_f28;
    float var_f29;
    float var_f30;
    float var_f31;
    UnkBssA4Data *var_r30;
    s32 i;

    var_f29 = 576.0f;
    var_f30 = 0.0f;
    var_f26 = 480.0f;
    var_f27 = 0.0f;
    for (i = 0; i < 4; i++) {
        var_r30 = lbl_1_bss_A4[i]->data;
        Hu3D3Dto2D(&var_r30->unkA0[4], 1, &sp20);
        if (var_f29 > sp20.x) {
            var_f29 = sp20.x;
        }
        if (var_f30 < sp20.x) {
            var_f30 = sp20.x;
        }
        if (var_f26 > sp20.y) {
            var_f26 = sp20.y;
        }
        if (var_f27 < sp20.y) {
            var_f27 = sp20.y;
        }
    }
    sp14 = lbl_1_bss_768;
    sp8 = lbl_1_bss_750;
    switch (lbl_1_bss_78) {
        case 0:
            if (1.0f < ABS(sp14.z - sp8.z) && sp14.z < sp8.z) {
                var_f31 = 0.05f * (288.0f - (var_f29 + var_f30) / 2);
                if (0.0f < var_f31) {
                    lbl_1_bss_70 -= var_f31;
                }
                sp8.x += 0.02f * -sp8.x;
                sp8.y += 0.02f * -sp8.y;
                sp8.z += 0.02f * (lbl_1_bss_70 - sp8.z);
                sp14.x += 0.02f * (-1500.0f - sp14.x);
                sp14.y += 0.02f * (700.0f - sp14.y);
                sp14.z += 0.04f * (sp8.z - sp14.z);
            }
            else {
                var_f31 = 0.05f * (288.0f - (var_f29 + var_f30) / 2);
                if (0.0f < var_f31) {
                    sp14.z -= var_f31;
                    sp8.z -= var_f31;
                    sp14.z = sp8.z;
                    var_f28 = ABS(var_f30 - var_f29) / 288.0f;
                    if (1.0f < var_f28) {
                        var_f28 = 1.0f;
                    }
                    var_f31 = 0.1f * (100.0f - var_f29) * var_f28;
                    if (var_f31 < var_f30 - 520.0f) {
                        var_f31 = 0.1f * (var_f30 - 520.0f) * var_f28;
                    }
                    if (0.0f < var_f31) {
                        sp14.y += 2.0f * var_f31;
                        sp14.x -= var_f31;
                        sp8.x += 0.01f * var_f31;
                    }
                }
            }
            break;
        case 1:
            var_f31 = 0.05f * (340.0f - var_f27);
            sp14.z += var_f31;
            sp8.z += var_f31;
            break;
        case 2:
            var_f31 = 0.05f * (288.0f - (var_f29 + var_f30) / 2);
            sp14.z -= var_f31;
            sp8.z -= var_f31;
            var_f28 = ABS(var_f30 - var_f29) / 261.81818f;
            if (1.0f < var_f28) {
                var_f28 = 1.0f;
            }
            var_f31 = 0.1f * (100.0f - var_f29) * var_f28;
            if (var_f31 < var_f30 - 480.0f) {
                var_f31 = 0.1f * (var_f30 - 480.0f) * var_f28;
            }
            if (0.0f > var_f31) {
                if (360.0f > var_f27 && 1500.0f <= sp14.y) {
                    sp14.y += var_f31;
                    sp14.x -= 0.2f * var_f31;
                    sp8.x += 0.01f * var_f31;
                }
            }
            else {
                sp14.y += 2.0f * var_f31;
                sp14.x -= 0.5f * var_f31;
                sp8.x += 0.01f * var_f31;
            }
            break;
    }
    fn_1_1350(&sp14, &lbl_1_data_100, &sp8);
}

static inline void fn_1_9288_InlineFunc(Vec *arg0, float arg1, float arg2, float arg3)
{
    arg0->x = arg1;
    arg0->y = arg2;
    arg0->z = arg3;
}

void fn_1_9288(omObjData *arg0)
{
    Vec sp18;
    Vec spC;
    float var_f27;
    UnkBssA4Data *temp_r25;
    s32 var_r30;

    if (omSysExitReq != 0) {
        fn_1_1F58(-1);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        arg0->func = fn_1_B5C8;
    }
    lbl_1_bss_740++;
    switch (arg0->work[0]) {
        case 1000:
            if (WipeStatGet() == 0) {
                arg0->work[0]++;
                lbl_1_bss_80 = 0.0f;
                lbl_1_bss_48[1] = lbl_1_data_10C;
                lbl_1_bss_18[1] = lbl_1_data_118;
                fn_1_9288_InlineFunc(&lbl_1_bss_30[1], -450.0f, lbl_1_bss_48[1].y, lbl_1_bss_48[1].z);
                fn_1_9288_InlineFunc(&lbl_1_bss_0[1], -450.0f, lbl_1_bss_18[1].y, lbl_1_bss_18[1].z);
                lbl_1_bss_48[0] = lbl_1_bss_30[1];
                lbl_1_bss_18[0] = lbl_1_bss_0[1];
                fn_1_9288_InlineFunc(&lbl_1_bss_30[0], -1100.0f, 200.0f + lbl_1_bss_48[0].y, -200.0f);
                lbl_1_bss_0[0].x = 0.0f;
                lbl_1_bss_0[0].y = 0.0f;
                lbl_1_bss_0[0].z = 1300.0f;
            }
            break;
        case 1001:
            lbl_1_bss_80 += 1.0f;
            if (90.0f >= lbl_1_bss_80) {
                var_r30 = 1;
                var_f27 = lbl_1_bss_80;
            }
            else {
                var_r30 = 0;
                var_f27 = lbl_1_bss_80 - 90.0f;
            }
            fn_1_11F4(var_f27 / 90.0f, &lbl_1_bss_48[var_r30], &lbl_1_bss_30[var_r30], &sp18);
            fn_1_11F4(var_f27 / 90.0f, &lbl_1_bss_18[var_r30], &lbl_1_bss_0[var_r30], &spC);
            fn_1_1350(&sp18, &lbl_1_data_100, &spC);
            if (180.0f <= lbl_1_bss_80) {
                arg0->work[0]++;
                lbl_1_bss_80 = 0.0f;
            }
            break;
        case 1002:
            lbl_1_bss_80 += 1.0f;
            if (10.0f < lbl_1_bss_80) {
                arg0->work[0]++;
                lbl_1_bss_80 = 0.0f;
            }
            break;
        case 1003:
            lbl_1_bss_80 += 1.0f;
            if (80.0f < lbl_1_bss_80) {
                arg0->work[0]++;
                lbl_1_bss_80 = 0.0f;
            }
            break;
        case 1004:
            lbl_1_bss_80 += 1.0f;
            if (lbl_1_bss_736 < 0) {
                lbl_1_bss_736 = MGSeqStartCreate();
                break;
            }
            if (lbl_1_bss_730 < 0 && (MGSeqStatGet(lbl_1_bss_736) & 0x10)) {
                lbl_1_bss_730 = HuAudSeqPlay(0x47);
            }
            if (MGSeqStatGet(lbl_1_bss_736) == 0) {
                arg0->work[0]++;
                lbl_1_bss_73C = 0;
                lbl_1_bss_736 = -1;
                lbl_1_bss_80 = 0.0f;
                lbl_1_bss_64 = HuAudFXPlay(0x538);
            }
            break;
        case 1005:
            lbl_1_bss_73C++;
            if (lbl_1_bss_734 >= 0) {
                MGSeqParamSet(lbl_1_bss_734, 1, (18059 - lbl_1_bss_73C) / 60);
            }
            else if (lbl_1_bss_73C > 16200) {
                lbl_1_bss_734 = MGSeqTimerCreate((18059 - lbl_1_bss_73C) / 60);
                MGSeqPosSet(lbl_1_bss_734, 288.0f, 400.0f);
            }
            fn_1_580(lbl_1_bss_6E8, 0, lbl_1_bss_73C);
            if (lbl_1_bss_73C >= 18000 || lbl_1_bss_7C >= 0) {
                arg0->work[0]++;
                lbl_1_bss_80 = 0.0f;
                if (lbl_1_bss_7C >= 0) {
                    temp_r25 = lbl_1_bss_A4[lbl_1_bss_7C]->data;
                    lbl_1_bss_48[0] = lbl_1_bss_768;
                    lbl_1_bss_30[0] = temp_r25->unk4C;
                    lbl_1_bss_30[0].y += 100.0f;
                    lbl_1_bss_30[0].z += 500.0f;
                    lbl_1_bss_18[0] = lbl_1_bss_750;
                    lbl_1_bss_0[0] = temp_r25->unk4C;
                    lbl_1_bss_0[0].y += 75.0f;
                    lbl_1_bss_0[0].z += 50.0f;
                }
            }
            if (lbl_1_bss_74 != lbl_1_bss_78) {
                if (lbl_1_bss_78 == 1) {
                    fn_1_1350(&lbl_1_data_124, &lbl_1_data_100, &lbl_1_data_130);
                }
                if (lbl_1_bss_78 == 2) {
                    fn_1_1350(&lbl_1_data_13C, &lbl_1_data_100, &lbl_1_data_148);
                }
            }
            else {
                fn_1_8AF0();
            }
            lbl_1_bss_74 = lbl_1_bss_78;
            break;
        case 1006:
            if (lbl_1_bss_736 < 0) {
                if (lbl_1_bss_734 >= 0) {
                    MGSeqParamSet(lbl_1_bss_734, 2, -1);
                }
                lbl_1_bss_734 = -1;
                lbl_1_bss_736 = MGSeqFinishCreate();
                fn_1_1F58(100);
                if (lbl_1_bss_7C >= 0) {
                    lbl_1_bss_60 = HuAudFXPlay(0x538);
                }
            }
            else {
                lbl_1_bss_80 += 1.0f;
                if (lbl_1_bss_7C >= 0) {
                    fn_1_11F4(lbl_1_bss_80 / 60.0f, &lbl_1_bss_48[0], &lbl_1_bss_30[0], &sp18);
                    fn_1_11F4(lbl_1_bss_80 / 60.0f, &lbl_1_bss_18[0], &lbl_1_bss_0[0], &spC);
                    fn_1_1350(&sp18, &lbl_1_data_100, &spC);
                }
                if (60.0f < lbl_1_bss_80 && MGSeqStatGet(lbl_1_bss_736) == 0) {
                    arg0->work[0] = 1008;
                    if (lbl_1_bss_7C >= 0 && !GWPlayerCfg[lbl_1_bss_7C].iscom && lbl_1_bss_73C < 3600) {
                        GWGameStat.present[53] = 1;
                    }
                    if (lbl_1_bss_7C >= 0 && !GWPlayerCfg[lbl_1_bss_7C].iscom && lbl_1_bss_738 > lbl_1_bss_73C) {
                        arg0->work[0] = 1007;
                        fn_1_798(0);
                    }
                    lbl_1_bss_736 = -1;
                    lbl_1_bss_80 = 0.0f;
                }
            }
            break;
        case 1007:
            if (lbl_1_bss_736 < 0) {
                lbl_1_bss_736 = MGSeqRecordCreate(lbl_1_bss_738);
                break;
            }
            if (MGSeqStatGet(lbl_1_bss_736) == 0) {
                arg0->work[0]++;
                lbl_1_bss_80 = 0.0f;
                lbl_1_bss_736 = -1;
            }
            break;
        case 1008:
            if (lbl_1_bss_736 < 0) {
                if (lbl_1_bss_7C < 0) {
                    lbl_1_bss_736 = MGSeqDrawCreate();
                    HuAudSStreamPlay(4);
                }
                else {
                    lbl_1_bss_736 = MGSeqWinCreate(GWPlayerCfg[lbl_1_bss_7C].character, -1, -1, -1);
                    HuAudSStreamPlay(1);
                }
            }
            else {
                lbl_1_bss_80 += 1.0f;
                0 <= lbl_1_bss_7C;
                if (210.0f < lbl_1_bss_80 && MGSeqStatGet(lbl_1_bss_736) == 0) {
                    fn_1_1F58(-1);
                    lbl_1_bss_736 = -1;
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                    arg0->func = fn_1_B5C8;
                }
            }
            break;
        default:
            OSReport("*** main mode error(%d)!!\n", arg0->work[0]);
            break;
    }
    fn_1_A40();
}

void fn_1_AD10(omObjData *arg0)
{
    s32 i;

    arg0->work[0] = 1000;
    lbl_1_bss_78 = 0;
    lbl_1_bss_74 = 0;
    lbl_1_bss_70 = 900.0f;
    omSetTra(arg0, 0.0f, 0.0f, 0.0f);
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M405, 48));
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(arg0->model[0], 5);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M405, 49));
    Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(arg0->model[1], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(arg0->model[1], 6);
    Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M405, 50));
    Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(arg0->model[2], 1);
    Hu3DModelPosSet(arg0->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowMapSet(arg0->model[2]);
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M405, 51));
    Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(arg0->model[3], 1);
    Hu3DModelPosSet(arg0->model[3], 0.0f, -4.0f, 0.0f);
    Hu3DModelTPLvlSet(arg0->model[3], 0.4f);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M405, 52));
    Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(arg0->model[4], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(arg0->model[4], 6);
    Hu3DModelPosSet(arg0->model[4], 0.0f, 0.0f, 0.0f);
    fn_1_B4C(80.0f, DATA_MAKE_NUM(DATADIR_M405, 72));
    fn_1_9EC();
    for (i = 0; i < 5; i++) {
        Hu3DModelAttrReset(arg0->model[i], HU3D_ATTR_DISPOFF);
    }
    lbl_1_bss_68 = HuAudFXPlay(0x537);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    arg0->func = fn_1_9288;
}

void ObjectSetup(void)
{
    Vec sp8;
    s32 temp_r29;
    s32 i;
    omObjData *temp_r30;

    OSReport("******* M405 ObjectSetup *********\n");
    lbl_1_bss_774 = omInitObjMan(100, 0x2000);
    omGameSysInit(lbl_1_bss_774);
    lbl_1_bss_740 = 0;
    lbl_1_bss_736 = -1;
    lbl_1_bss_734 = -1;
    lbl_1_bss_7C = -1;
    lbl_1_bss_68 = -1;
    lbl_1_bss_64 = -1;
    lbl_1_bss_60 = -1;
    lbl_1_bss_730 = -1;
    lbl_1_bss_728 = -1.0f;
    lbl_1_bss_738 = GWMGRecordGet(0);
    if (lbl_1_bss_738 == 0) {
        lbl_1_bss_738 = 18000;
    }
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 20000.0f, 1.2f);
    fn_1_1350(&lbl_1_data_10C, &lbl_1_data_100, &lbl_1_data_118);
    temp_r29 = Hu3DGLightCreateV(&lbl_1_data_154, &lbl_1_data_160, &lbl_1_data_16C);
    Hu3DGLightStaticSet(temp_r29, 1);
    Hu3DGLightInfinitytSet(temp_r29);
    Hu3DShadowCreate(30.0f, 20.0f, 20000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    VECNormalize(&lbl_1_data_170, &sp8);
    Hu3DShadowPosSet(&lbl_1_data_170, &sp8, &lbl_1_data_17C);
    lbl_1_bss_90 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M405, 57));
    HuSprAnimLock(lbl_1_bss_90);
    lbl_1_bss_8C = Hu3DParManCreate(lbl_1_bss_90, 500, &lbl_1_data_370);
    Hu3DParManAttrSet(lbl_1_bss_8C, 1);
    lbl_1_bss_88 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M405, 62));
    HuSprAnimLock(lbl_1_bss_88);
    lbl_1_bss_84 = Hu3DParManCreate(lbl_1_bss_88, 2, &lbl_1_data_3C0);
    Hu3DParManAttrSet(lbl_1_bss_84, 1);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(lbl_1_bss_84), 7);
    omMakeGroupEx(lbl_1_bss_774, 0, 4);
    lbl_1_bss_A4 = omGetGroupMemberListEx(lbl_1_bss_774, 0);
    for (i = 0; i < 4; i++) {
        temp_r30 = omAddObjEx(lbl_1_bss_774, 100, 1, 8, 0, fn_1_81B4);
        temp_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkBssA4Data), MEMORY_DEFAULT_NUM);
        temp_r30->work[0] = i;
    }
    lbl_1_bss_A0 = omAddObjEx(lbl_1_bss_774, 101, 2, 2, -1, fn_1_5B28);
    lbl_1_bss_9C = omAddObjEx(lbl_1_bss_774, 103, 5, 0, -1, fn_1_5404);
    lbl_1_bss_98 = omAddObjEx(lbl_1_bss_774, 104, 5, 0, -1, fn_1_AD10);
}

void fn_1_B5C8(omObjData *arg0)
{
    s32 i;

    if (lbl_1_bss_68 >= 0) {
        lbl_1_bss_68 = -1;
        HuAudFXStop(lbl_1_bss_68);
    }
    if (lbl_1_bss_64 >= 0) {
        lbl_1_bss_64 = -1;
        HuAudFXStop(lbl_1_bss_64);
    }
    if (lbl_1_bss_60 >= 0) {
        lbl_1_bss_60 = -1;
        HuAudFXStop(lbl_1_bss_60);
    }
    if (WipeStatGet() == 0) {
        if (lbl_1_bss_736 >= 0) {
            MGSeqKill(lbl_1_bss_736);
        }
        if (lbl_1_bss_734 >= 0) {
            MGSeqKill(lbl_1_bss_734);
        }
        MGSeqKillAll();
        HuAudAllStop();
        for (i = 0; i < 4; i++) {
            CharModelKill(lbl_1_data_0[GWPlayerCfg[i].character]);
        }
        omOvlReturnEx(1, 1);
    }
}
