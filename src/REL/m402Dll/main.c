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
#include "rel_sqrt_consts.h"

#undef ABS
#define ABS(x) ((0 > (x)) ? -(x) : (x))

typedef struct unk_bss_204_struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ struct unk_bss_204_struct *unk04;
    /* 0x08 */ struct unk_bss_204_struct *unk08;
} UnkBss204Struct; // Size 0xC

typedef struct unk_bss_1ec_struct {
    /* 0x00 */ HsfanimStruct00 *unk00;
    /* 0x04 */ s32 *unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ struct unk_bss_1ec_struct *unk10;
    /* 0x14 */ struct unk_bss_1ec_struct *unk14;
} UnkBss1ECStruct; // Size 0x18

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2]; // padding?
} UnkBss5CStruct; // Size 8

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
} UnkFn27A8Struct; // Size 0x64

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ s32 unk10;
} UnkData234Struct; // Size 0x14

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ s32 unk18;
} UnkFn6AB4Struct; // Size 0x1C

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ Vec unk24;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ s32 unk38;
} UnkFn70E4Struct; // Size 0x3C

static void fn_1_0(void);
static void fn_1_24(u16 arg0, s16 arg1);
static s16 fn_1_AC(s16 arg0);
static void fn_1_150(void);
static void fn_1_174(s16 arg0, HsfanimStruct00 *arg1, s32 arg2, s32 arg3, s32 arg4, Vec *arg5, u8 arg6);
static void fn_1_2D8(void);
static void fn_1_414(void);
static s16 fn_1_46C(s32 arg0);
static void fn_1_580(s32 *arg0, s32 arg1, s32 arg2);
static void fn_1_798(s32 arg0);
static void fn_1_9EC(void);
static void fn_1_A40(void);
static void fn_1_B4C(float arg0, s32 arg1);
static void fn_1_11F4(float arg0, Vec *arg1, Vec *arg2, Vec *arg3);
static void fn_1_1350(Vec *arg0, Vec *arg1, Vec *arg2);
static s32 fn_1_13DC(float arg0, Vec *arg1);
static void fn_1_1710(float arg0, Vec *arg1);
static void fn_1_1A60(Vec *arg0, s16 arg1, Vec *arg2);
static void fn_1_1D18(s16 arg0, char *arg1, Vec *arg2);
static void fn_1_1D70(s16 arg0, char *arg1, Vec *arg2, Mtx arg3);
static float fn_1_1E20(float arg0, float arg1, float arg2);
static void fn_1_1F24(s32 arg0);
static void fn_1_1F58(s32 arg0);
static void fn_1_1FC4(Vec *arg0, float *arg1, s32 arg2, s32 arg3);
static void fn_1_2454(void);
static void fn_1_2744(s16 arg0, GXColor *arg1);
static u16 fn_1_27A8(UnkFn27A8Struct *arg0);
static void fn_1_2880(UnkFn27A8Struct *arg0, omObjData *arg1);
static void fn_1_2970(UnkFn27A8Struct *arg0, omObjData *arg1, u8 arg2);
static void fn_1_2B30(UnkFn27A8Struct *arg0, omObjData *arg1, omObjData *arg2);
static u8 fn_1_2DBC(UnkFn27A8Struct *arg0, omObjData *arg1);
static void fn_1_313C(UnkFn27A8Struct *arg0, omObjData *arg1);
static void fn_1_3204(omObjData *arg0);
static void fn_1_4190(float arg0);
static void fn_1_4284(float arg0);
static void fn_1_43D8(omObjData *arg0);
static void fn_1_63C8(omObjData *arg0);
static void fn_1_6858(omObjData *arg0);
static void fn_1_685C(omObjData *arg0);
static void fn_1_6AB4(omObjData *arg0);
static void fn_1_6E64(omObjData *arg0);
static void fn_1_7020(omObjData *arg0);
static void fn_1_70E4(omObjData *arg0);
static void fn_1_7950(omObjData *arg0);
static void fn_1_7AEC(s32 arg0, Vec *arg1, Vec *arg2);
static void fn_1_7D48(omObjData *arg0);
static void fn_1_7D4C(omObjData *arg0);
static void fn_1_7E80(omObjData *arg0);
static void fn_1_7E84(omObjData *arg0);
static void fn_1_8048(void);
static void fn_1_8218(omObjData *arg0);
static void fn_1_9058(omObjData *arg0);
static void fn_1_9AF4(omObjData *arg0);

static UnkBss204Struct lbl_1_bss_204;
static UnkBss1ECStruct lbl_1_bss_1EC;
static Process *lbl_1_bss_1E8;
static Vec lbl_1_bss_1DC;
static Vec lbl_1_bss_1D0;
static Vec lbl_1_bss_1C4;
static Vec lbl_1_bss_1B8;
static u32 lbl_1_bss_1B4;
static s32 lbl_1_bss_1B0;
static s32 lbl_1_bss_1AC;
static s16 lbl_1_bss_1AA;
static s16 lbl_1_bss_1A8;
static s32 lbl_1_bss_1A4;
static s32 lbl_1_bss_1A0;
static float lbl_1_bss_19C;
static s32 lbl_1_bss_15C[16];
static UnkBss5CStruct lbl_1_bss_5C[32];
static omObjData *lbl_1_bss_58;
static omObjData **lbl_1_bss_54;
static omObjData **lbl_1_bss_50;
static omObjData **lbl_1_bss_4C;
static omObjData **lbl_1_bss_48;
static omObjData **lbl_1_bss_44;
static omObjData **lbl_1_bss_40;
static u8 lbl_1_bss_3C_unused[4];
static float lbl_1_bss_38;
static float lbl_1_bss_34;
static float lbl_1_bss_30;
static float lbl_1_bss_2C;
static float lbl_1_bss_28;
static s16 lbl_1_bss_26;
static s16 lbl_1_bss_24;
static s16 lbl_1_bss_16[7];
static s16 lbl_1_bss_14;
static s32 lbl_1_bss_10;
static float lbl_1_bss_C;
static float lbl_1_bss_8;
static float lbl_1_bss_4;
static u8 lbl_1_bss_0[4];

static s16 lbl_1_data_0[] = {
    0, 1, 2, 3, 4, 5, 6, 7
};

static Vec lbl_1_data_10 = { 0.0f, 2500.0f, 2200.0f };
static Vec lbl_1_data_1C = { 0.0f, 1.0f, 0.0f };
static Vec lbl_1_data_28 = { 0.0f, 388.0f, 0.0f };
static Vec lbl_1_data_34 = { 0.0f, 2000.0f, 1000.0f };
static Vec lbl_1_data_40 = { 0.0f, -2.0f, -1.0f };
static GXColor lbl_1_data_4C = { 0xFF, 0xFF, 0xFF, 0xFF };

static Vec lbl_1_data_50_unused = { 0.0f, -1.0f, 0.0f };
static u8 lbl_1_data_5C_unused[] = { 0xFF, 0xFF, 0xFF, 0xFF };

static Vec lbl_1_data_60 = { 0.0f, 4000.0f, 1000.0f };
static Vec lbl_1_data_6C = { 0.0f, 0.0f, 0.0f };

static s32 lbl_1_data_78[8][11] = {
    {
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 2),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 28),
        DATA_MAKE_NUM(DATADIR_M402, 16),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 62),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 3),
        DATA_MAKE_NUM(DATADIR_M402, 8),
        DATA_MAKE_NUM(DATADIR_M402, 0),
        DATA_MAKE_NUM(DATADIR_M402, 24),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 117),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 76)
    },
    {
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 2),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 28),
        DATA_MAKE_NUM(DATADIR_M402, 17),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 62),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 3),
        DATA_MAKE_NUM(DATADIR_M402, 9),
        DATA_MAKE_NUM(DATADIR_M402, 1),
        DATA_MAKE_NUM(DATADIR_M402, 25),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 117),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 76)
    },
    {
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 2),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 28),
        DATA_MAKE_NUM(DATADIR_M402, 18),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 62),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 3),
        DATA_MAKE_NUM(DATADIR_M402, 10),
        DATA_MAKE_NUM(DATADIR_M402, 2),
        DATA_MAKE_NUM(DATADIR_M402, 26),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 117),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 76)
    },
    {
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 2),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 28),
        DATA_MAKE_NUM(DATADIR_M402, 19),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 62),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 3),
        DATA_MAKE_NUM(DATADIR_M402, 11),
        DATA_MAKE_NUM(DATADIR_M402, 3),
        DATA_MAKE_NUM(DATADIR_M402, 27),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 117),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 76)
    },
    {
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 2),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 28),
        DATA_MAKE_NUM(DATADIR_M402, 20),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 62),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 3),
        DATA_MAKE_NUM(DATADIR_M402, 12),
        DATA_MAKE_NUM(DATADIR_M402, 4),
        DATA_MAKE_NUM(DATADIR_M402, 28),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 117),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 76)
    },
    {
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 2),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 28),
        DATA_MAKE_NUM(DATADIR_M402, 21),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 62),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 3),
        DATA_MAKE_NUM(DATADIR_M402, 13),
        DATA_MAKE_NUM(DATADIR_M402, 5),
        DATA_MAKE_NUM(DATADIR_M402, 29),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 117),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 76)
    },
    {
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 2),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 28),
        DATA_MAKE_NUM(DATADIR_M402, 22),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 62),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 3),
        DATA_MAKE_NUM(DATADIR_M402, 14),
        DATA_MAKE_NUM(DATADIR_M402, 6),
        DATA_MAKE_NUM(DATADIR_M402, 30),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 117),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 76)
    },
    {
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 2),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 28),
        DATA_MAKE_NUM(DATADIR_M402, 23),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 62),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 3),
        DATA_MAKE_NUM(DATADIR_M402, 15),
        DATA_MAKE_NUM(DATADIR_M402, 7),
        DATA_MAKE_NUM(DATADIR_M402, 31),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 117),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 76)
    }
};

static s32 lbl_1_data_1D8[] = {
    DATA_MAKE_NUM(DATADIR_M402, 38),
    DATA_MAKE_NUM(DATADIR_M402, 40),
    DATA_MAKE_NUM(DATADIR_M402, 37),
    DATA_MAKE_NUM(DATADIR_M402, 39)
};

static s32 lbl_1_data_1E8[] = {
    DATA_MAKE_NUM(DATADIR_M402, 41),
    DATA_MAKE_NUM(DATADIR_M402, 42),
    DATA_MAKE_NUM(DATADIR_M402, 43)
};

static s32 lbl_1_data_1F4 = DATA_MAKE_NUM(DATADIR_M402, 44);

static s32 lbl_1_data_1F8[] = {
    DATA_MAKE_NUM(DATADIR_M402, 45),
    DATA_MAKE_NUM(DATADIR_M402, 46)
};

static Vec lbl_1_data_200[] = {
    {  450.0f, 290.0f, 0.0f },
    { -450.0f, 290.0f, 0.0f }
};

static s32 lbl_1_data_218[] = {
    DATA_MAKE_NUM(DATADIR_M402, 48),
    DATA_MAKE_NUM(DATADIR_M402, 50),
    DATA_MAKE_NUM(DATADIR_M402, 47),
    DATA_MAKE_NUM(DATADIR_M402, 49),
    DATA_MAKE_NUM(DATADIR_M402, 51),
    DATA_MAKE_NUM(DATADIR_M402, 52),
    DATA_MAKE_NUM(DATADIR_M402, 53)
};

static UnkData234Struct lbl_1_data_234[] = {
    { 0.0f,  0.0f,  0.0f,    0.0f,    -1 },
    { 2.0f,  2.0f,  0.1f,  0.125f, 0x514 },
    { 2.0f,  2.0f,  0.2f,   0.25f,    -1 },
    { 3.0f,  4.0f,  0.3f,   0.35f, 0x515 },
    { 3.0f,  4.0f,  0.4f,   0.45f,    -1 },
    { 3.0f,  6.0f, 0.45f, 0.5125f, 0x516 },
    { 3.0f,  6.0f,  0.5f,  0.575f,    -1 },
    { 3.0f,  6.0f, 0.55f, 0.6375f,    -1 },
    { 3.0f,  6.0f,  0.6f,    0.7f,    -1 },
    { 4.0f,  8.0f, 0.65f,   0.75f, 0x517 },
    { 4.0f,  8.0f,  0.7f,    0.8f,    -1 },
    { 4.0f,  8.0f, 0.75f,   0.85f,    -1 },
    { 4.0f,  8.0f,  0.8f,    0.9f,    -1 },
    { 4.0f, 10.0f, 0.83f, 0.9166f, 0x518 },
    { 4.0f, 10.0f, 0.86f, 0.9333f,    -1 },
    { 4.0f, 10.0f,  0.9f,   0.95f,    -1 },
    { 4.0f, 10.0f, 0.93f, 0.9666f,    -1 },
    { 4.0f, 10.0f, 0.96f, 0.9833f,    -1 },
    { 4.0f, 10.0f,  1.0f,    1.0f,    -1 },
    { 1.0f, 10.0f,  1.0f,    1.0f,    -1 }
};

static s32 lbl_1_data_3C4[] = {
    0x00000514,
    0x00000515,
    0x00000516,
    0x00000517,
    0x00000518
};

static void fn_1_0(void) {
    lbl_1_bss_204.unk04 = NULL;
    lbl_1_bss_204.unk08 = NULL;
}

static void fn_1_24(u16 arg0, s16 arg1) {
    UnkBss204Struct *temp_r31;
    UnkBss204Struct *temp_r30;
    UnkBss204Struct *temp_r29;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r31), MEMORY_DEFAULT_NUM);
    temp_r31->unk00 = arg0;
    temp_r31->unk02 = arg1;
    temp_r30 = &lbl_1_bss_204;
    temp_r29 = temp_r30->unk08;
    temp_r30->unk08 = temp_r31;
    if (NULL != temp_r29) {
        temp_r29->unk04 = temp_r31;
    }
    temp_r31->unk04 = temp_r30;
    temp_r31->unk08 = temp_r29;
}

static s16 fn_1_AC(s16 arg0) {
    UnkBss204Struct *var_r31;
    UnkBss204Struct *temp_r29;
    UnkBss204Struct *temp_r30;
    s16 temp_r28;

    var_r31 = lbl_1_bss_204.unk08;
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

static void fn_1_150(void) {
    lbl_1_bss_1EC.unk10 = NULL;
    lbl_1_bss_1EC.unk14 = NULL;
}

static void fn_1_174(s16 arg0, HsfanimStruct00 *arg1, s32 arg2, s32 arg3, s32 arg4, Vec *arg5, u8 arg6) {
    UnkBss1ECStruct *temp_r27;
    UnkBss1ECStruct *var_r31;
    UnkBss1ECStruct *temp_r28;
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
    temp_r28 = &lbl_1_bss_1EC;
    temp_r27 = temp_r28->unk14;
    temp_r28->unk14 = var_r31;
    if (NULL != temp_r27) {
        temp_r27->unk10 = var_r31;
    }
    var_r31->unk10 = temp_r28;
    var_r31->unk14 = temp_r27;
}

static void fn_1_2D8(void) {
    UnkBss1ECStruct *var_r31;
    UnkBss1ECStruct *temp_r28;
    UnkBss1ECStruct *temp_r29;
    s32 i;

    var_r31 = lbl_1_bss_1EC.unk14;
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

static void fn_1_414(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        lbl_1_bss_5C[i].unk00 = 0;
        lbl_1_bss_5C[i].unk04 = -1;
    }
}

static s16 fn_1_46C(s32 arg0) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (arg0 == lbl_1_bss_5C[i].unk00) {
            return Hu3DModelLink(lbl_1_bss_5C[i].unk04);
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_1_bss_5C[i].unk00 == 0) {
            lbl_1_bss_5C[i].unk00 = arg0;
            lbl_1_bss_5C[i].unk04 = Hu3DModelCreateFile(arg0);
            return lbl_1_bss_5C[i].unk04;
        }
    }
    return Hu3DModelCreateFile(arg0);
}

static void fn_1_580(s32 *arg0, s32 arg1, s32 arg2) {
    s32 var_r30;

    espBankSet(arg0[arg1 + 1], 10);
    espBankSet(arg0[arg1 + 4], 11);
    if (36000 <= arg2) {
        arg2 = 35999;
    }
    var_r30 = arg2 / 3600;
    arg2 -= var_r30 * 3600;
    if (var_r30 > 9) {
        var_r30 = 9;
    }
    espBankSet(arg0[arg1], var_r30);
    var_r30 = arg2 / 60;
    arg2 -= var_r30 * 60;
    espBankSet(arg0[arg1 + 2], var_r30 / 10);
    espBankSet(arg0[arg1 + 3], var_r30 % 10);
    var_r30 = 101.5f * arg2 / 60.0f;
    espBankSet(arg0[arg1 + 5], var_r30 / 10);
    espBankSet(arg0[arg1 + 6], var_r30 % 10);
}

static void fn_1_798(s32 arg0) {
    lbl_1_bss_19C = 0.0f;
    lbl_1_bss_1AC = lbl_1_bss_1B0;
    GWMGRecordSet(arg0, lbl_1_bss_1AC);
    fn_1_580(lbl_1_bss_15C, 7, lbl_1_bss_1B0);
}

static void fn_1_9EC(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        espDispOn(lbl_1_bss_15C[i]);
    }
}

static void fn_1_A40(void) {
    float temp_f31;
    s32 i;

    if (0.0f <= lbl_1_bss_19C) {
        lbl_1_bss_19C += 16.0f;
        temp_f31 = 1.0 + 0.2f * sind(lbl_1_bss_19C);
        for (i = 7; i <= 14; i++) {
            espScaleSet(lbl_1_bss_15C[i], temp_f31, temp_f31);
        }
    }
}

static void fn_1_B4C(float arg0, s32 arg1) {
    float temp_f30;
    float temp_f31;
    s32 i;

    temp_f31 = 288.0f;
    temp_f30 = arg0;
    lbl_1_bss_15C[15] = espEntry(arg1, 0, 0);
    espTPLvlSet(lbl_1_bss_15C[15], 0.5f);
    espColorSet(lbl_1_bss_15C[15], 0, 0, 0);
    espPosSet(lbl_1_bss_15C[15], temp_f31, temp_f30);
    temp_f31 = 248.0f;
    temp_f30 = arg0 - 8.0f;
    lbl_1_bss_15C[14] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 55), 0, 0);
    espPosSet(lbl_1_bss_15C[14], temp_f31 - 18.0f, temp_f30);
    for (i = 7; i <= 13; i++) {
        lbl_1_bss_15C[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 48), 0, 0);
        espPosSet(lbl_1_bss_15C[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_15C, 7, lbl_1_bss_1AC);
    temp_f31 = 248.0f;
    temp_f30 = arg0 + 8.0f;
    for (i = 0; i <= 6; i++) {
        lbl_1_bss_15C[i] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 49), 0, 0);
        espPosSet(lbl_1_bss_15C[i], temp_f31, temp_f30);
        temp_f31 += 16.0f;
    }
    fn_1_580(lbl_1_bss_15C, 0, 0);
    for (i = 0; i < 16; i++) {
        espDrawNoSet(lbl_1_bss_15C[i], 0);
        espDispOff(lbl_1_bss_15C[i]);
        espAttrSet(lbl_1_bss_15C[i], HUSPR_ATTR_NOANIM);
        espPriSet(lbl_1_bss_15C[i], 0x80 + i);
    }
}

static void fn_1_11F4(float arg0, Vec *arg1, Vec *arg2, Vec *arg3) {
    float temp_f31;

    if (1.0f < arg0) {
        arg0 = 1.0f;
    }
    temp_f31 = sind(90.0f * arg0) * sind(90.0f * arg0);
    arg3->x = arg1->x + temp_f31 * (arg2->x - arg1->x);
    arg3->y = arg1->y + temp_f31 * (arg2->y - arg1->y);
    arg3->z = arg1->z + temp_f31 * (arg2->z - arg1->z);
}

static void fn_1_1350(Vec *arg0, Vec *arg1, Vec *arg2) {
    Hu3DCameraPosSetV(1, arg0, arg1, arg2);
    lbl_1_bss_1DC = *arg0;
    lbl_1_bss_1C4 = *arg2;
}

static s32 fn_1_13DC(float arg0, Vec *arg1) {
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_1DC, &lbl_1_bss_1D0, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_1C4, &lbl_1_bss_1B8, &spC);
    Hu3DCameraPosSetV(1, &sp18, arg1, &spC);
    if (1.0f <= arg0) {
        return 1;
    } else {
        lbl_1_bss_1A0 = 1;
        return 0;
    }
}

static void fn_1_1710(float arg0, Vec *arg1) {
    Vec sp18;
    Vec spC;

    fn_1_11F4(arg0, &lbl_1_bss_1DC, &lbl_1_bss_1D0, &sp18);
    fn_1_11F4(arg0, &lbl_1_bss_1C4, &lbl_1_bss_1B8, &spC);
    fn_1_1350(&sp18, arg1, &spC);
    lbl_1_bss_1A0 = 1;
}

static void fn_1_1A60(Vec *arg0, s16 arg1, Vec *arg2) {
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
    PSMTXMultVec(sp1C, arg0, &sp10);
    temp_f30 = sp10.z * (sind(temp_r31->fov / 2) / cosd(temp_r31->fov / 2)) * temp_r31->aspect;
    temp_f29 = sp10.z * (sind(temp_r31->fov / 2) / cosd(temp_r31->fov / 2));
    temp_f28 = 0.9f * temp_r31->viewport_x;
    temp_f31 = 0.9f * temp_r31->viewport_w;
    arg2->x = temp_f31 / 2 + sp10.x * ((temp_f31 / 2) / -temp_f30) + temp_f28;
    arg2->y = temp_r31->viewport_h / 2 + sp10.y * ((temp_r31->viewport_h / 2) / temp_f29) + temp_r31->viewport_y;
    arg2->z = 0.0f;
}

static void fn_1_1D18(s16 arg0, char *arg1, Vec *arg2) {
    Mtx sp10;

    Hu3DModelObjMtxGet(arg0, arg1, sp10);
    arg2->x = sp10[0][3];
    arg2->y = sp10[1][3];
    arg2->z = sp10[2][3];
}

static void fn_1_1D70(s16 arg0, char *arg1, Vec *arg2, Mtx arg3) {
    Mtx spC;
    ModelData *var_r30;

    var_r30 = &Hu3DData[arg0];
    Hu3DModelObjMtxGet(arg0, arg1, spC);
    PSMTXConcat(var_r30->unk_F0, spC, spC);
    if (NULL != arg3) {
        PSMTXCopy(spC, arg3);
    }
    arg2->x = spC[0][3];
    arg2->y = spC[1][3];
    arg2->z = spC[2][3];
}

static float fn_1_1E20(float arg0, float arg1, float arg2) {
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

static void fn_1_1F24(s32 arg0) {
    lbl_1_bss_1A4 = HuAudSeqPlay(arg0);
}

static void fn_1_1F58(s32 arg0) {
    if (lbl_1_bss_1A4 >= 0) {
        if (arg0 < 0) {
            arg0 = 1000;
        }
        HuAudSeqFadeOut(lbl_1_bss_1A4, arg0);
    }
    lbl_1_bss_1A4 = -1;
}

static void fn_1_1FC4(Vec *arg0, float *arg1, s32 arg2, s32 arg3) {
    Vec sp18;
    float var_f28;
    s32 var_r30;

    sp18.x = 0.0f;
    sp18.y = 0.0f;
    sp18.z = 0.0f;
    sp18.x = arg2 / 4.0f;
    sp18.z = -(float) arg3 / 4.0f;
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
        } else {
            var_r30 = 1;
        }
    }
    PSVECAdd((Vec*) &arg0, &sp18, (Vec*) &arg0);
}

#include "src/REL/executor.c"

static void fn_1_2454(void) {
    HuSysVWaitSet(1);
    if (HuPadBtnDown[0] & 0x400) {
        lbl_1_bss_1B0 = -1;
    }
    print8(24, 32, 1.5f, "%f COUNT:%d MES:%d WIN:%d", lbl_1_bss_38, lbl_1_bss_1B4, lbl_1_bss_1AA, lbl_1_bss_26);
    print8(24, 48, 1.5f, "%f %f %f", lbl_1_bss_4, lbl_1_bss_C, lbl_1_bss_8);
    print8(24, 64, 1.5f, "%x %x", HuMemHeapSizeGet(HEAP_SYSTEM) - HuMemUsedMallocSizeGet(HEAP_SYSTEM), HuMemHeapSizeGet(HEAP_DATA) - HuMemUsedMallocSizeGet(HEAP_DATA));
    lbl_1_bss_8 -= HuPadSubStkX[0] / 59.0f;
    lbl_1_bss_C -= (HuPadSubStkY[0] / 59.0f) * 4.0f;
    lbl_1_bss_4 -= (HuPadTrigL[0] / 150.0f) * 4.0f;
    lbl_1_bss_4 += (HuPadTrigR[0] / 150.0f) * 4.0f;
}

static void fn_1_2744(s16 arg0, GXColor *arg1) {
    s16 var_r30;

    var_r30 = Hu3DLLightCreateV(arg0, &lbl_1_data_34, &lbl_1_data_40, arg1);
    Hu3DLLightStaticSet(arg0, var_r30, 1);
}

static u16 fn_1_27A8(UnkFn27A8Struct *arg0) {
    u16 var_r30;

    var_r30 = 0;
    if (frandmod(arg0->unk34) == 0) {
        var_r30 = 0x100;
    }
    if (--arg0->unk38 < 0) {
        arg0->unk34 -= frandmod(3);
        if (arg0->unk34 < 2) {
            arg0->unk34 = 2;
        }
        arg0->unk38 = (arg0->unk3C >> 1) + frandmod(arg0->unk3C);
    }
    if (var_r30 == 0) {
        if (++arg0->unk40 > 60) {
            arg0->unk40 = 0;
            var_r30 = 0x100;
        }
    } else {
        arg0->unk40 = 0;
    }
    return var_r30;
}

static void fn_1_2880(UnkFn27A8Struct *arg0, omObjData *arg1) {
    arg0->unk4C = 2016;
    arg0->unk60 = 0;
    arg0->unk2C = 0.0f;
    arg0->unk30 = 0.0f;
    arg0->unk1C = 670.0f;
    arg0->unk20 = 0.0f;
    arg0->unk24 = arg0->unk1C;
    arg0->unk08 = 0.0f;
    arg0->unk0C = 0.0f;
    arg0->unk10 = arg0->unk0C;
    Hu3DModelAttrReset(arg1->model[0], 0x40000002);
    Hu3DModelAttrSet(arg1->model[0], 0x40000001);
    Hu3DMotionSet(arg1->model[0], arg1->motion[0]);
}

static void fn_1_2970(UnkFn27A8Struct *arg0, omObjData *arg1, u8 arg2) {
    Vec sp18;
    Vec spC;
    float temp_f31;
    s32 i;

    fn_1_1D18(arg1->model[0], "motionC-stretch", &sp18);
    for (i = 0; i < 8; i++) {
        temp_f31 = arg0->unk1C + 50.0f;
        spC.x = 20.0f * frandf() - 10.0f;
        spC.y = arg0->unk18;
        spC.z = 20.0f;
        if (arg2 != 0) {
            spC.y += 180.0f;
            spC.z = 10.0f;
        }
        temp_f31 = 3.0f * (30.0f * frandf() - 15.0f);
        spC.y += temp_f31 + 10.0f * (0.0f > temp_f31 ? -1 : 1);
        fn_1_7AEC(arg0->unk54, &sp18, &spC);
    }
}

static void fn_1_2B30(UnkFn27A8Struct *arg0, omObjData *arg1, omObjData *arg2) {
    arg0->unk50 = 0;
    arg0->unk20 = (770.0f - arg0->unk1C) / 18.0f;
    arg0->unk0C = Hu3DMotionTimeGet(arg2->model[0]);
    Hu3DMotionTimeSet(lbl_1_bss_54[arg0->unk54]->model[0], 0.0f);
    Hu3DMotionSpeedSet(arg1->model[0], 1.0f);
    Hu3DModelAttrReset(arg1->model[0], 0x40000003);
    Hu3DMotionShiftSet(arg1->model[0], arg1->motion[7], 0.0f, 8.0f, 0);
    fn_1_2970(arg0, arg2, 1);
    HuAudCharVoicePlay(arg0->unk58, 0x123);
}

static u8 fn_1_2DBC(UnkFn27A8Struct *arg0, omObjData *arg1) {
    Vec sp20;
    float var_f30;
    float var_f29;

    arg0->unk50++;
    var_f30 = 90.0f * (arg0->unk50 / 18.0f);
    var_f29 = arg0->unk0C * (1.0 - sind(var_f30));
    Hu3DMotionTimeSet(arg1->model[0], var_f29);
    fn_1_1D18(arg1->model[0], "motionC-stretch", &sp20);
    arg0->unk28 = sp20.y - arg0->unk14 + 388.0f;
    arg0->unk1C += arg0->unk20;
    if (18.0f < arg0->unk50) {
        arg0->unk20 = (670.0f - arg0->unk1C) / 20.0f;
        Hu3DModelAttrReset(arg1->model[0], 0x40000003);
        Hu3DMotionSet(arg1->model[0], arg1->motion[2]);
        Hu3DMotionTimeSet(arg1->model[0], 20.0f);
        omVibrate(arg0->unk54, 12, 4, 2);
        HuAudFXPlay(0x50F);
        fn_1_2970(arg0, arg1, 0);
        return 1;
    }
    return 0;
}

static void fn_1_313C(UnkFn27A8Struct *arg0, omObjData *arg1) {
    Vec sp8;

    arg0->unk1C += arg0->unk20;
    if (670.0f > arg0->unk1C) {
        arg0->unk1C = 670.0f;
    }
    fn_1_1D18(arg1->model[0], "motionC-stretch", &sp8);
    arg0->unk28 = sp8.y - arg0->unk14 + 388.0f;
}

static void fn_1_3204(omObjData *arg0) {
    Vec sp48;
    Vec sp3C;
    Vec sp24;
    Vec spC;
    float temp_f31;
    UnkFn27A8Struct *temp_r31;
    omObjData *temp_r29;
    UnkData234Struct *temp_r28;
    u16 var_r26;

    temp_r31 = arg0->data;
    if (lbl_1_bss_58->work[0] == 1007) {
        switch (temp_r31->unk4C) {
            case 2017:
                temp_r31->unk4C = 2014;
                break;
            case 2018:
                temp_r31->unk4C = 2015;
                break;
            default:
                temp_r31->unk4C = 2010;
                break;
        }
        Hu3DMotionSpeedSet(arg0->model[0], 1.0f);
        if (lbl_1_bss_26 == temp_r31->unk54) {
            GWPlayerCoinWinSet(temp_r31->unk54, 10);
        }
        arg0->func = fn_1_43D8;
        return;
    }
    if (lbl_1_bss_58->work[0] == 1006) {
        temp_r29 = lbl_1_bss_48[temp_r31->unk54];
        if (temp_r31->unk60 < 19) {
            if (GWPlayerCfg[temp_r31->unk54].iscom) {
                var_r26 = fn_1_27A8(temp_r31);
            } else {
                var_r26 = HuPadBtnDown[temp_r31->unk5C];
            }
            if (temp_r31->unk60 == 0) {
                if (var_r26 & 0x100) {
                    temp_r31->unk60 = 1;
                    temp_r31->unk2C = 0.0f;
                    temp_r31->unk30 = 0.0f;
                    temp_r31->unk08 = 0.0f;
                    temp_r31->unk0C = 0.0f;
                    temp_r31->unk10 = temp_r31->unk0C;
                    temp_r31->unk20 = 0.0f;
                    temp_r31->unk24 = temp_r31->unk1C;
                    HuAudFXPlay(0x50E);
                    Hu3DMotionShiftSet(arg0->model[0], arg0->motion[5], 0.0f, 2.0f, 0x40000001);
                }
            } else {
                temp_r31->unk30 += 1.0f;
            }
            switch (temp_r31->unk4C) {
                case 2016:
                    if (var_r26 & 0x100) {
                        temp_r28 = &lbl_1_data_234[temp_r31->unk60];
                        if (temp_r28->unk10 >= 0 && 0.0f == temp_r31->unk2C) {
                            HuAudFXPlay(temp_r28->unk10);
                        }
                        temp_r31->unk2C += 1.0f;
                        Hu3DMotionTimeSet(lbl_1_bss_54[temp_r31->unk54]->model[0], temp_r28->unk04);
                        temp_f31 = temp_r28->unk08 - temp_r28[-1].unk08;
                        temp_f31 *= 1.0f - temp_r31->unk2C / temp_r28->unk00;
                        temp_r31->unk24 = 670.0f - 450.0f * (temp_r28->unk08 - temp_f31);
                        temp_f31 = temp_r28->unk0C - temp_r28[-1].unk0C;
                        temp_f31 *= 1.0f - temp_r31->unk2C / temp_r28->unk00;
                        temp_r31->unk10 = (temp_r28->unk0C - temp_f31) * Hu3DMotionMaxTimeGet(temp_r29->model[0]);
                        temp_f31 = temp_r31->unk60 / 20.0f;
                        temp_r31->unk20 = temp_f31 * (temp_r31->unk24 - temp_r31->unk1C);
                        temp_r31->unk08 = temp_f31 * (temp_r31->unk10 - temp_r31->unk0C);
                        if (temp_r28->unk00 <= temp_r31->unk2C) {
                            temp_r31->unk60++;
                            if (temp_r31->unk60 == 3) {
                                Hu3DMotionSpeedSet(arg0->model[0], 0.83f);
                                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[6], 0.0f, 4.0f, 0x40000001);
                            }
                            if (temp_r31->unk60 == 9) {
                                Hu3DMotionSpeedSet(arg0->model[0], 1.0f);
                            }
                            temp_r31->unk2C = 0.0f;
                            temp_r31->unk30 = 0.0f;
                            if (temp_r31->unk60 >= 19) {
                                temp_r31->unk1C = temp_r31->unk24;
                                temp_r31->unk20 = 0.0f;
                                temp_r31->unk0C = temp_r31->unk10;
                                temp_r31->unk08 = 0.0f;
                                if (lbl_1_bss_26 < 0) {
                                    lbl_1_bss_26 = temp_r31->unk54;
                                } else if (frandmod(100) > 50) {
                                    lbl_1_bss_26 = temp_r31->unk54;
                                }
                            }
                        }
                    }
                    if (60.0f <= temp_r31->unk30) {
                        temp_r31->unk4C = 2017;
                        fn_1_2B30(temp_r31, arg0, temp_r29);
                    } else {
                        if (temp_r31->unk1C > temp_r31->unk24) {
                            temp_r31->unk1C += temp_r31->unk20;
                            if (temp_r31->unk1C <= temp_r31->unk24) {
                                temp_r31->unk1C = temp_r31->unk24;
                            }
                        }
                        if (temp_r31->unk0C < temp_r31->unk10) {
                            temp_r31->unk0C += temp_r31->unk08;
                            if (temp_r31->unk0C >= temp_r31->unk10) {
                                temp_r31->unk0C = temp_r31->unk10;
                            }
                        }
                        Hu3DMotionTimeSet(temp_r29->model[0], temp_r31->unk0C);
                    }
                    break;
                case 2017:
                    if (fn_1_2DBC(temp_r31, temp_r29) != 0) {
                        temp_r31->unk4C = 2018;
                        temp_r31->unk50 = 120;
                    }
                    break;
                case 2018:
                    fn_1_313C(temp_r31, temp_r29);
                    temp_r31->unk50 -= 1.0f;
                    if (temp_r31->unk50 == 32) {
                        Hu3DMotionSet(arg0->model[0], arg0->motion[9]);
                        Hu3DMotionShiftSet(temp_r29->model[0], temp_r29->motion[1], 0.0f, 20.0f, 0x40000002);
                    }
                    if (0.0f > temp_r31->unk50) {
                        fn_1_2880(temp_r31, arg0);
                    }
                    break;
                default:
                    OSReport("*** player mode error(%d)!!\n", temp_r31->unk4C);
                    break;
            }
            if (lbl_1_bss_28 < temp_r31->unk1C) {
                lbl_1_bss_28 = temp_r31->unk1C;
            }
            omSetTra(arg0, temp_r31->unk1C * sind(180.0f + temp_r31->unk18), temp_r31->unk28, temp_r31->unk1C * cosd(180.0f + temp_r31->unk18));
        }
    }
}

static void fn_1_4190(float arg0) {
    Vec sp8;
    s32 i;

    for (i = 0; i < 4; i++) {
        sp8.x = 155.5 * sind(arg0);
        sp8.y = 588.0f;
        sp8.z = 155.5 * cosd(arg0);
        fn_1_7AEC(5, &sp8, NULL);
        arg0 += 90.0f;
    }
}

static void fn_1_4284(float arg0) {
    Vec sp8;
    s32 i;

    for (i = 0; i < 4; i++) {
        sp8.x = 155.5 * sind(arg0);
        sp8.y = 388.0f;
        sp8.z = 155.5 * cosd(arg0);
        sp8.x += 40.0f * frandf() - 20.0f;
        sp8.z += 40.0f * frandf() - 20.0f;
        fn_1_7AEC(4, &sp8, NULL);
        arg0 += 90.0f;
    }
}

static void fn_1_43D8(omObjData *arg0) {
    Vec spE8;
    float temp_f31;
    float temp_f23;
    UnkFn27A8Struct *temp_r31;
    omObjData *temp_r30;
    s32 temp_r28;

    temp_r31 = arg0->data;
    temp_r30 = lbl_1_bss_48[temp_r31->unk54];
    switch (temp_r31->unk4C) {
        case 2000:
            if (lbl_1_bss_58->work[0] == 1001) {
                temp_r31->unk4C++;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[1], 0.0f, 10.0f, 0);
            }
            break;
        case 2001:
            temp_r31->unk1C -= 1.0f;
            if (Hu3DMotionEndCheck(arg0->model[0])) {
                temp_r31->unk4C++;
                temp_r31->unk08 = 0.0f;
                temp_r31->unk04 = 2000.0f;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[2], 0.0f, 10.0f, 0);
                Hu3DMotionSet(temp_r30->model[0], temp_r30->motion[0]);
                Hu3DModelAttrSet(temp_r30->model[0], 0x40000002);
                Hu3DModelAttrReset(temp_r30->model[0], 0x40000001);
                Hu3DModelAttrReset(temp_r30->model[0], 1);
            }
            break;
        case 2002:
            temp_r31->unk08 += 0.4f;
            temp_r31->unk04 -= temp_r31->unk08;
            if (temp_r31->unk48 != 0 && Hu3DMotionEndCheck(arg0->model[0])) {
                temp_r31->unk48 = 0;
                HuAudCharVoicePlay(temp_r31->unk58, 0x128);
            }
            if (786.0f > temp_r31->unk04) {
                temp_r31->unk4C++;
                if (temp_r31->unk54 == 0) {
                    HuAudFXPlay(0x50D);
                }
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[3], 0.0f, 10.0f, 0);
            }
            break;
        case 2003:
            temp_r31->unk08 += 0.4f;
            temp_r31->unk04 -= temp_r31->unk08;
            if (536.0f > temp_r31->unk04) {
                temp_r31->unk4C++;
                temp_r31->unk50 = 0;
                temp_r31->unk04 = 536.0f;
                Hu3DModelAttrReset(temp_r30->model[0], 0x40000002);
                spE8.x = temp_r31->unk00 * sind(180.0f + temp_r31->unk18);
                spE8.y = temp_r31->unk04;
                spE8.z = temp_r31->unk00 * cosd(180.0f + temp_r31->unk18);
                fn_1_7AEC(6, &spE8, NULL);
                omVibrate(temp_r31->unk54, 12, 0xC, 0);
            }
            break;
        case 2004:
            temp_r31->unk50++;
            if (70.0f < temp_r31->unk50) {
                temp_r31->unk4C++;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[4], 0.0f, 10.0f, 0);
            }
            break;
        case 2005:
            temp_r31->unk50++;
            if (130.0f == temp_r31->unk50) {
                if (lbl_1_bss_10 != 0) {
                    lbl_1_bss_10 = 0;
                    HuAudFXPlay(0x510);
                }
                fn_1_2970(temp_r31, temp_r30, 0);
            }
            if (!Hu3DMotionEndCheck(arg0->model[0])) {
                temp_r31->unk1C -= 2.3f;
            }
            if (Hu3DMotionEndCheck(temp_r30->model[0])) {
                temp_r31->unk4C++;
                temp_r31->unk50 = 0;
                temp_r31->unk0C = 0.0f;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[5], 0.0f, 10.0f, 0x40000001);
                Hu3DMotionShiftSet(temp_r30->model[0], temp_r30->motion[1], 0.0f, 10.0f, 0x40000002);
            }
            break;
        case 2006:
            if (temp_r31->unk50++ > 10) {
                temp_r31->unk4C++;
            }
            fn_1_1D18(temp_r30->model[0], "motionC-stretch", &spE8);
            temp_r31->unk14 = spE8.y;
            break;
        case 2007:
            temp_r31->unk1C -= 5.0f;
            if (670.0f > temp_r31->unk1C) {
                temp_f31 = (670.0f - temp_r31->unk1C) / 450.0f;
                Hu3DMotionTimeSet(lbl_1_bss_54[temp_r31->unk54]->model[0], 10.0f * temp_f31);
                temp_r28 = (s32) (10.0f * temp_f31) >> 1;
                if (temp_r28 < 5 && temp_r31->unk44 != lbl_1_data_3C4[temp_r28]) {
                    temp_r31->unk44 = lbl_1_data_3C4[temp_r28];
                    HuAudFXPlay(temp_r31->unk44);
                }
            }
            if (470.0f > temp_r31->unk1C) {
                temp_r31->unk4C++;
                temp_r31->unk1C = 470.0f;
                fn_1_2B30(temp_r31, arg0, temp_r30);
            } else {
                temp_r31->unk0C += 0.7f;
                Hu3DMotionTimeSet(temp_r30->model[0], temp_r31->unk0C);
            }
            break;
        case 2008:
            if (fn_1_2DBC(temp_r31, temp_r30) != 0) {
                temp_r31->unk4C++;
                temp_r31->unk50 = 120;
            }
            break;
        case 2009:
            fn_1_313C(temp_r31, temp_r30);
            temp_r31->unk50 -= 1.0f;
            if (temp_r31->unk50 == 32) {
                Hu3DMotionSet(arg0->model[0], arg0->motion[9]);
                Hu3DMotionShiftSet(temp_r30->model[0], temp_r30->motion[1], 0.0f, 20.0f, 0x40000002);
            }
            if (0.0f > temp_r31->unk50) {
                lbl_1_bss_58->work[0]++;
                fn_1_2880(temp_r31, arg0);
                arg0->func = fn_1_3204;
            }
            break;

        case 2010:
            if (temp_r31->unk54 == lbl_1_bss_26) {
                temp_r31->unk4C = 2012;
                temp_r31->unk20 = 10.5f;
                Hu3DModelAttrReset(arg0->model[0], 0x40000003);
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[8], 0.0f, 20.0f, 0);
                Hu3DModelAttrReset(temp_r30->model[0], 0x40000003);
                Hu3DMotionShiftSet(temp_r30->model[0], temp_r30->motion[2], 20.0f, 20.0f, 0);
                HuAudFXPlay(0x513);
                fn_1_4190(temp_r31->unk18);
            } else {
                temp_r31->unk4C = 2014;
                fn_1_2B30(temp_r31, arg0, temp_r30);
            }
            break;

        case 2011:
            break;

        case 2012:
            temp_r31->unk1C -= temp_r31->unk20;
            if (0.0f > temp_r31->unk1C) {
                temp_r31->unk1C = 0.0f;
            }
            temp_r31->unk20 -= 0.25f;
            if (0.0f > temp_r31->unk20) {
                temp_r31->unk4C++;
                temp_r31->unk50 = 0;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[9], 0.0f, 20.0f, 0);
            }
            if (4.5f <= temp_r31->unk20) {
                fn_1_4284(temp_r31->unk18);
            }
            break;
        case 2013:
            temp_r31->unk50++;
            temp_f23 = 90.0f * (temp_r31->unk50 / 20.0f);
            temp_f31 = sind(temp_f23) * sind(temp_f23);
            if (180.0f > temp_r31->unk18) {
                temp_r31->unk24 = temp_r31->unk18 + -temp_r31->unk18 * temp_f31;
            } else {
                temp_r31->unk24 = temp_r31->unk18 + (360.0f - temp_r31->unk18) * temp_f31;
            }
            omSetRot(arg0, 0.0f, temp_r31->unk24, 0.0f);
            if (20.0f <= temp_r31->unk50) {
                temp_r31->unk4C = 2011;
            }
            break;
        case 2014:
            if (fn_1_2DBC(temp_r31, temp_r30) != 0) {
                temp_r31->unk4C++;
                temp_r31->unk50 = 120;
            }
            break;
        case 2015:
            fn_1_313C(temp_r31, temp_r30);
            temp_r31->unk50 -= 1.0f;
            if (temp_r31->unk50 == 32) {
                Hu3DMotionSet(arg0->model[0], arg0->motion[9]);
                Hu3DMotionShiftSet(temp_r30->model[0], temp_r30->motion[1], 0.0f, 20.0f, 0x40000002);
            }
            if (0.0f > temp_r31->unk50) {
                temp_r31->unk4C = 2011;
            }
            break;
        default:
            OSReport("*** player mode error(%d)!!\n", temp_r31->unk4C);
            break;
    }
    omSetTra(arg0, temp_r31->unk1C * sind(180.0f + temp_r31->unk18), temp_r31->unk28, temp_r31->unk1C * cosd(180.0f + temp_r31->unk18));
    omSetTra(temp_r30, temp_r31->unk00 * sind(180.0f + temp_r31->unk18), temp_r31->unk04, temp_r31->unk00 * cosd(180.0f + temp_r31->unk18));
    if (lbl_1_bss_58->work[0] < 1008 && temp_r31->unk54 == lbl_1_bss_26) {
        lbl_1_bss_1B8.x = temp_r31->unk1C * sind(180.0f + temp_r31->unk18);
        lbl_1_bss_1B8.y = 508.0f;
        lbl_1_bss_1B8.z = temp_r31->unk1C * cosd(180.0f + temp_r31->unk18);
        lbl_1_bss_1D0.x = lbl_1_bss_1B8.x;
        lbl_1_bss_1D0.y = lbl_1_bss_1B8.y + 270.0f;
        lbl_1_bss_1D0.z = lbl_1_bss_1B8.z + 850.0f;
    }
}

static void fn_1_63C8(omObjData *arg0) {
    UnkFn27A8Struct *temp_r31;
    s16 temp_r28;
    s16 var_r27;
    s32 i;

    temp_r31 = arg0->data;
    temp_r31->unk54 = arg0->work[0];
    temp_r31->unk58 = GWPlayerCfg[temp_r31->unk54].character;
    temp_r31->unk5C = GWPlayerCfg[temp_r31->unk54].pad_idx;
    temp_r31->unk4C = 2000;
    temp_r31->unk60 = 0;
    temp_r31->unk28 = 388.0f;
    temp_r31->unk2C = 0.0f;
    temp_r31->unk30 = 0.0f;
    temp_r31->unk0C = 0.0f;
    temp_r31->unk00 = 895.0f;
    temp_r31->unk04 = 536.0f;
    temp_r31->unk44 = -1;
    temp_r31->unk48 = 1;
    temp_r31->unk34 = 10;
    temp_r31->unk38 = 10;
    temp_r31->unk3C = 10;
    temp_r31->unk40 = 60;
    arg0->model[0] = CharModelCreate(lbl_1_data_0[temp_r31->unk58], 4);
    CharModelStepTypeSet(lbl_1_data_0[temp_r31->unk58], 0);
    for (i = 0; i < 11; i++) {
        arg0->motion[i] = CharModelMotionCreate(lbl_1_data_0[temp_r31->unk58], lbl_1_data_78[temp_r31->unk58][i]);
        CharModelMotionSet(lbl_1_data_0[temp_r31->unk58], arg0->motion[i]);
    }
    temp_r28 = arg0->model[0];
    var_r27 = Hu3DLLightCreateV(temp_r28, &lbl_1_data_34, &lbl_1_data_40, &lbl_1_data_4C);
    Hu3DLLightStaticSet(temp_r28, var_r27, 1);
    Hu3DModelAttrSet(arg0->model[0], 1);
    Hu3DModelAttrSet(arg0->model[0], 0x40000001);
    Hu3DModelLayerSet(arg0->model[0], 3);
    Hu3DMotionSet(arg0->model[0], arg0->motion[0]);
    temp_r31->unk18 = 135.0f + 90.0f * temp_r31->unk54;
    temp_r31->unk1C = 895.0f;
    omSetTra(arg0, temp_r31->unk1C * sind(180.0f + temp_r31->unk18), temp_r31->unk28, temp_r31->unk1C * cosd(180.0f + temp_r31->unk18));
    omSetRot(arg0, 0.0f, temp_r31->unk18, 0.0f);
    Hu3DModelShadowSet(arg0->model[0]);
    Hu3DModelAttrReset(arg0->model[0], 1);
    if (GWPlayerCfg[temp_r31->unk54].iscom) {
        switch (GWPlayerCfg[temp_r31->unk54].diff) {
            case 0:
                temp_r31->unk34 = 26;
                temp_r31->unk3C = 90;
                break;
            case 1:
                temp_r31->unk34 = 24;
                temp_r31->unk3C = 80;
                break;
            case 2:
                temp_r31->unk34 = 22;
                temp_r31->unk3C = 70;
                break;
            case 3:
            default:
                temp_r31->unk34 = 18;
                temp_r31->unk3C = 40;
                break;
        }
        temp_r31->unk38 = (temp_r31->unk3C >> 1) + frandmod(temp_r31->unk3C);
    }
    CharModelMotionDataClose(lbl_1_data_0[temp_r31->unk58]);
    arg0->func = fn_1_43D8;
}

static void fn_1_6858(omObjData *arg0) {
}

static void fn_1_685C(omObjData *arg0) {
    float temp_f31;
    float temp_f29;
    float temp_f30;
    s32 temp_r29;
    s32 i;

    temp_r29 = arg0->work[0];
    arg0->model[0] = Hu3DModelCreateFile(lbl_1_data_1D8[temp_r29]);
    for (i = 0; i < 3; i++) {
        arg0->motion[i] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_1E8[i]);
    }
    Hu3DModelAttrSet(arg0->model[0], 1);
    Hu3DModelAttrSet(arg0->model[0], 0x40000002);
    Hu3DModelLayerSet(arg0->model[0], 4);
    Hu3DMotionSet(arg0->model[0], arg0->motion[0]);
    temp_f31 = ((UnkFn27A8Struct*) lbl_1_bss_4C[temp_r29]->data)->unk18;
    temp_f29 = ((UnkFn27A8Struct*) lbl_1_bss_4C[temp_r29]->data)->unk04;
    temp_f30 = ((UnkFn27A8Struct*) lbl_1_bss_4C[temp_r29]->data)->unk00;
    omSetTra(arg0, temp_f30 * sind(180.0f + temp_f31), temp_f29, temp_f30 * cosd(180.0f + temp_f31));
    omSetRot(arg0, 0.0f, temp_f31, 0.0f);
    Hu3DModelShadowSet(arg0->model[0]);
    arg0->func = fn_1_6858;
}

static void fn_1_6AB4(omObjData *arg0) {
    Vec *temp_r29;
    UnkFn6AB4Struct *temp_r31;
    float temp_f31;

    temp_r29 = &lbl_1_data_200[arg0->work[0]];
    temp_r31 = arg0->data;
    switch (temp_r31->unk18) {
        case 3000:
            temp_r31->unk14 -= 1.0f;
            if (0.0f > temp_r31->unk14 && frandmod(20) == 0) {
                temp_r31->unk18 = 3001;
                temp_r31->unk0C = 360.0f * frandf();
                temp_r31->unk10 = 10.0f;
                HuAudFXPlay(0x512);
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[0], 0.0f, 20.0f, 0);
            }
            break;
        case 3001:
            temp_r31->unk00 += sind(temp_r31->unk0C);
            temp_r31->unk08 += cosd(temp_r31->unk0C);
            temp_f31 = temp_r31->unk00 - temp_r29->x;
            if (50.0f < ABS(temp_f31)) {
                temp_r31->unk00 = temp_r29->x + 50.0f * (0.0f > temp_f31 ? -1 : 1);
            }
            temp_f31 = temp_r31->unk08 - temp_r29->z;
            if (50.0f < ABS(temp_f31)) {
                temp_r31->unk08 = temp_r29->z + 50.0f * (0.0f > temp_f31 ? -1 : 1);
            }
            temp_r31->unk04 += temp_r31->unk10;
            temp_r31->unk10 -= 0.5f;
            if (temp_r29->y > temp_r31->unk04) {
                temp_r31->unk18 = 3000;
                temp_r31->unk14 = 20.0f;
                temp_r31->unk04 = temp_r29->y;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[1], 0.0f, 20.0f, 0);
            }
            break;
    }
    omSetTra(arg0, temp_r31->unk00, temp_r31->unk04, temp_r31->unk08);
    omSetRot(arg0, 0.0f, temp_r31->unk0C, 0.0f);
}

static void fn_1_6E64(omObjData *arg0) {
    Vec *temp_r29;
    UnkFn6AB4Struct *temp_r30;
    s32 i;

    temp_r29 = &lbl_1_data_200[arg0->work[0]];
    temp_r30 = arg0->data;
    arg0->model[0] = Hu3DModelCreateFile(lbl_1_data_1F4);
    for (i = 0; i < 2; i++) {
        arg0->motion[i] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_1F8[i]);
    }
    Hu3DModelAttrSet(arg0->model[0], 1);
    Hu3DModelLayerSet(arg0->model[0], 5);
    Hu3DMotionSet(arg0->model[0], arg0->motion[1]);
    temp_r30->unk18 = 3000;
    temp_r30->unk14 = 0.0f;
    temp_r30->unk00 = temp_r29->x;
    temp_r30->unk04 = temp_r29->y;
    temp_r30->unk08 = temp_r29->z;
    temp_r30->unk0C = 360.0f * frandf();
    omSetTra(arg0, temp_r30->unk00, temp_r30->unk04, temp_r30->unk08);
    omSetRot(arg0, 0.0f, temp_r30->unk0C, 0.0f);
    Hu3DModelShadowSet(arg0->model[0]);
    Hu3DModelAttrReset(arg0->model[0], 0x40000002);
    Hu3DModelAttrReset(arg0->model[0], 1);
    arg0->func = fn_1_6AB4;
}

static void fn_1_7020(omObjData *arg0) {
    Hu3DModelAttrSet(arg0->model[0], 1);
    fn_1_24(arg0->work[0], arg0->model[0]);
    omDelObjEx(lbl_1_bss_1E8, arg0);
    lbl_1_bss_24--;
}

static void fn_1_70E4(omObjData *arg0) {
    Mtx sp18;
    Vec spC;
    float var_f27;
    float temp_f26;
    float temp_f30;
    float temp_f31;
    UnkFn70E4Struct *temp_r31;

    temp_r31 = arg0->data;
    switch (arg0->work[0]) {
        case 0:
        case 1:
        case 2:
        case 3:
            var_f27 = temp_r31->unk24.z;
            spC.x = 0.0f;
            spC.y = 0.0f;
            spC.z = var_f27;
            temp_r31->unk24.z *= 0.92f;
            PSMTXIdentity(sp18);
            mtxRot(sp18, temp_r31->unk24.x, temp_r31->unk24.y, 0.0f);
            PSMTXMultVec(sp18, &spC, &spC);
            PSVECAdd(&spC, &temp_r31->unk00, &temp_r31->unk00);
            omSetTra(arg0, temp_r31->unk00.x, temp_r31->unk00.y, temp_r31->unk00.z);
            Hu3DModelTPLvlSet(arg0->model[0], temp_r31->unk30);
            temp_r31->unk30 -= 0.02f;
            if (0.1f > temp_r31->unk30) {
                fn_1_7020(arg0);
            }
            break;
        case 4:
            temp_r31->unk00.y += temp_r31->unk30;
            if (390.0f >= temp_r31->unk00.y) {
                temp_r31->unk00.y = 390.0f;
            }
            omSetTra(arg0, temp_r31->unk00.x, temp_r31->unk00.y, temp_r31->unk00.z);
            if (390.0f >= temp_r31->unk00.y) {
                break;
            }
            temp_r31->unk0C += 8.0f + frandmod(8);
            temp_r31->unk10 += 8.0f + frandmod(8);
            temp_r31->unk14 += 8.0f + frandmod(8);
            omSetRot(arg0, temp_r31->unk0C, temp_r31->unk10, temp_r31->unk14);
            if (0.0f < temp_r31->unk30) {
                temp_r31->unk30 -= 0.3f;
                break;
            }
            if (0.0f == temp_r31->unk34) {
                temp_r31->unk34 = 0.003f + 0.006f * frandf();
            }
            temp_r31->unk30 -= temp_r31->unk34;
            temp_r31->unk00.x += temp_r31->unk24.x;
            temp_r31->unk00.z += temp_r31->unk24.z;
            if (!(lbl_1_bss_1B4 & 3)) {
                temp_r31->unk24.x = 6.0f * frandf() - 3.0f;
                temp_r31->unk24.z = 6.0f * frandf() - 3.0f;
            }
            break;
        case 5:
            if (Hu3DMotionEndCheck(arg0->model[0])) {
                fn_1_7020(arg0);
            }
            break;
        case 6:
            spC = lbl_1_data_10;
            temp_f26 = Hu3DMotionMaxTimeGet(arg0->model[0]);
            temp_f31 = 1.0f - Hu3DMotionTimeGet(arg0->model[0]) / temp_f26;
            spC.x += 100.0f * temp_f31 * frandf() * (frandmod(100) > 50 ? 1.0f : -1.0f);
            spC.z += 100.0f * temp_f31 * frandf() * (frandmod(100) > 50 ? 1.0f : -1.0f);
            Hu3DCameraPosSetV(1, &spC, &lbl_1_data_1C, &lbl_1_data_28);
            lbl_1_bss_1DC = spC;
            lbl_1_bss_1C4 = lbl_1_data_28;
            temp_f30 = 0.5f * Hu3DMotionMaxTimeGet(arg0->model[0]);
            if (temp_f30 < Hu3DMotionTimeGet(arg0->model[0])) {
                temp_f31 = 1.0f - (Hu3DMotionTimeGet(arg0->model[0]) - temp_f30) / temp_f30;
                Hu3DModelTPLvlSet(arg0->model[0], temp_f31);
                temp_f31 = 1.0f - temp_f31;
                omSetSca(arg0, temp_r31->unk18 + temp_f31, temp_r31->unk1C + temp_f31, temp_r31->unk20 + temp_f31);
            }
            if (Hu3DMotionEndCheck(arg0->model[0])) {
                Hu3DCameraPosSetV(1, &lbl_1_data_10, &lbl_1_data_1C, &lbl_1_data_28);
                lbl_1_bss_1DC = lbl_1_data_10;
                lbl_1_bss_1C4 = lbl_1_data_28;
                fn_1_7020(arg0);
            }
            break;
        default:
            OSReport("effect id error!!(%d)\n", arg0->work[0]);
            break;
    }
}

static void fn_1_7950(omObjData *arg0) {
    UnkFn70E4Struct *temp_r30;
    s16 var_r25;

    temp_r30 = arg0->data;
    temp_r30->unk38--;
    if (temp_r30->unk38 <= 0) {
        var_r25 = fn_1_AC(arg0->work[0]);
        if (var_r25 < 0) {
            arg0->model[0] = Hu3DModelLink(lbl_1_bss_16[arg0->work[0]]);
        } else {
            arg0->model[0] = var_r25;
        }
        Hu3DMotionTimeSet(arg0->model[0], 0.0f);
        Hu3DModelAttrSet(arg0->model[0], 1);
        Hu3DModelLayerSet(arg0->model[0], 2);
        omSetTra(arg0, temp_r30->unk00.x, temp_r30->unk00.y, temp_r30->unk00.z);
        omSetRot(arg0, temp_r30->unk0C, temp_r30->unk10, temp_r30->unk14);
        omSetSca(arg0, temp_r30->unk18, temp_r30->unk1C, temp_r30->unk20);
        Hu3DModelAttrReset(arg0->model[0], 0x40000003);
        Hu3DModelAttrReset(arg0->model[0], 1);
        arg0->func = fn_1_70E4;
    }
}

static void fn_1_7AEC(s32 arg0, Vec *arg1, Vec *arg2) {
    omObjData *temp_r3;
    UnkFn70E4Struct *temp_r31;

    if (lbl_1_bss_24 < 300) {
        lbl_1_bss_24++;
        temp_r3 = omAddObjEx(lbl_1_bss_1E8, 105, 1, 1, 5, fn_1_7950);
        temp_r3->work[0] = arg0;
        temp_r3->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r31), MEMORY_DEFAULT_NUM);
        temp_r31 = temp_r3->data;
        temp_r31->unk0C = 0.0f;
        temp_r31->unk10 = 0.0f;
        temp_r31->unk14 = 0.0f;
        temp_r31->unk18 = 1.0f;
        temp_r31->unk1C = 1.0f;
        temp_r31->unk20 = 1.0f;
        temp_r31->unk24.x = 0.0f;
        temp_r31->unk24.y = 0.0f;
        temp_r31->unk24.z = 0.0f;
        temp_r31->unk00 = *arg1;
        if (NULL != arg2) {
            temp_r31->unk24 = *arg2;
        }
        temp_r31->unk38 = frandmod(10);
        switch (arg0) {
            case 0:
            case 1:
            case 2:
            case 3:
                temp_r31->unk30 = 1.0f;
                break;
            case 4:
                temp_r31->unk30 = 12.0f + 2.0f * frandf();
                temp_r31->unk34 = 0.0f;
                temp_r31->unk18 = 8.0f;
                temp_r31->unk1C = 8.0f;
                temp_r31->unk20 = 8.0f;
                break;
            case 5:
                temp_r31->unk18 = 4.0f;
                temp_r31->unk1C = 4.0f;
                temp_r31->unk20 = 4.0f;
                break;
        }
    }
}

static void fn_1_7D48(omObjData *arg0) {
}

static void fn_1_7D4C(omObjData *arg0) {
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M402, 35));
    Hu3DModelAttrSet(arg0->model[0], 1);
    Hu3DModelAttrSet(arg0->model[0], 0x40000002);
    Hu3DModelLayerSet(arg0->model[0], 0);
    omSetTra(arg0, 0.0f, 0.0f, 0.0f);
    omSetRot(arg0, 0.0f, 270.0f + 90.0f * arg0->work[0], 0.0f);
    Hu3DModelShadowMapSet(arg0->model[0]);
    Hu3DModelAttrReset(arg0->model[0], 1);
    arg0->func = fn_1_7D48;
}

static void fn_1_7E80(omObjData *arg0) {
}

static void fn_1_7E84(omObjData *arg0) {
    float temp_f31;

    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M402, 36));
    Hu3DModelAttrSet(arg0->model[0], 1);
    Hu3DModelAttrSet(arg0->model[0], 0x40000001);
    Hu3DModelAttrReset(arg0->model[0], 0x40000002);
    Hu3DModelLayerSet(arg0->model[0], 1);
    temp_f31 = 135.0f + 90.0f * arg0->work[0];
    omSetTra(arg0, 155.5 * sind(temp_f31), 0.0f, 155.5 * cosd(temp_f31));
    omSetRot(arg0, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(arg0->model[0], 1);
    arg0->func = fn_1_7E80;
}

static inline void fn_1_8048InlineFunc(Vec *arg0, float arg1, float arg2, float arg3) {
    arg0->x = arg1;
    arg0->y = arg2;
    arg0->z = arg3;
}

static void fn_1_8048(void) {
    Vec sp14;
    Vec sp8;

    lbl_1_bss_38 += lbl_1_bss_34;
    if (360.0f < lbl_1_bss_38) {
        lbl_1_bss_34 -= 0.2f;
        if (0.0f > lbl_1_bss_34) {
            lbl_1_bss_34 = 0.0f;
        }
    }
    sp14.x = 2000.0 * cosd(lbl_1_bss_38);
    sp14.y = 2000.0 * sind(lbl_1_bss_38);
    sp14.z = 0.0f;
    fn_1_8048InlineFunc(&sp8, -sp14.x, -sp14.y, -sp14.z);
    Hu3DGLightPosSetV(lbl_1_bss_14, &sp14, &sp8);
}

static void fn_1_8218(omObjData *arg0) {
    Vec sp38;
    float temp_f26;
    omObjData *temp_r30;

    if (omSysExitReq != 0) {
        fn_1_1F58(-1);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        arg0->func = fn_1_9AF4;
    }
    lbl_1_bss_1B4++;
    switch (arg0->work[0]) {
        case 1000:
            if (WipeStatGet() == 0) {
                arg0->work[0]++;
            }
            break;
        case 1001:
        case 1002:
        case 1003:
        case 1004:
            break;
        case 1005:
            if (lbl_1_bss_1AA < 0) {
                lbl_1_bss_1AA = MGSeqCreate(3, 0);
            } else {
                if (lbl_1_bss_1A4 < 0 && (MGSeqStatGet(lbl_1_bss_1AA) & 0x10)) {
                    lbl_1_bss_1A4 = HuAudSeqPlay(0x46);
                }
                if (MGSeqStatGet(lbl_1_bss_1AA) == 0) {
                    arg0->work[0]++;
                    lbl_1_bss_1B0 = 1800;
                    lbl_1_bss_1A8 = MGSeqCreate(1, lbl_1_bss_1B0 / 60, -1, -1);
                    lbl_1_bss_1AA = -1;
                }
            }
            break;
        case 1006:
            MGSeqParamSet(lbl_1_bss_1A8, 1, (lbl_1_bss_1B0 + 59) / 60);
            lbl_1_bss_1B0--;
            if (lbl_1_bss_1B0 < 0 || lbl_1_bss_26 >= 0) {
                lbl_1_bss_1B0 = 1800;
                lbl_1_bss_2C = 0.0f;
                arg0->work[0] = 1007;
            }
            if (670.0f <= lbl_1_bss_28) {
                lbl_1_bss_28 = 670.0f;
            }
            temp_f26 = 2.5f * (670.0f - lbl_1_bss_28);
            sp38 = lbl_1_data_10;
            sp38.y = lbl_1_bss_1DC.y + (lbl_1_data_10.y - temp_f26 - lbl_1_bss_1DC.y) / 3.0f;
            sp38.z = lbl_1_bss_1DC.z + (lbl_1_data_10.z - temp_f26 - lbl_1_bss_1DC.z) / 3.0f;
            fn_1_1350(&sp38, &lbl_1_data_1C, &lbl_1_data_28);
            lbl_1_bss_28 = 0.0f;
            break;
        case 1007:
            if (lbl_1_bss_1AA < 0) {
                MGSeqParamSet(lbl_1_bss_1A8, 2, -1);
                lbl_1_bss_1A8 = -1;
                lbl_1_bss_1AA = MGSeqCreate(3, 1);
                fn_1_1F58(100);
            } else {
                lbl_1_bss_2C += 1.0f;
                if (90.0f >= lbl_1_bss_2C) {
                    fn_1_13DC(lbl_1_bss_2C / 90.0f, &lbl_1_data_1C);
                }
                if (MGSeqStatGet(lbl_1_bss_1AA) == 0) {
                    arg0->work[0]++;
                    lbl_1_bss_1AA = -1;
                    lbl_1_bss_2C = 0.0f;
                }
            }
            break;
        case 1008:
            if (lbl_1_bss_1AA < 0) {
                if (lbl_1_bss_26 < 0) {
                    lbl_1_bss_1AA = MGSeqCreate(3, 2);
                    HuAudSStreamPlay(4);
                } else {
                    lbl_1_bss_1AA = MGSeqCreate(5, 3, GWPlayerCfg[lbl_1_bss_26].character, -1, -1, -1);
                    temp_r30 = lbl_1_bss_4C[lbl_1_bss_26];
                    Hu3DMotionShiftSet(temp_r30->model[0], temp_r30->motion[10], 0.0f, 20.0f, 0);
                    HuAudSStreamPlay(1);
                }
            } else {
                lbl_1_bss_2C += 1.0f;
                if (lbl_1_bss_26 >= 0 && 110.0f == lbl_1_bss_2C) {
                    Hu3DModelAttrSet(arg0->model[1], 1);
                    Hu3DModelAttrReset(arg0->model[2], 0x40000002);
                    Hu3DModelAttrReset(arg0->model[2], 1);
                    Hu3DMotionTimeSet(arg0->model[2], 0.0f);
                    Hu3DMotionSpeedSet(arg0->model[2], 3.0f);
                }
                if (210.0f < lbl_1_bss_2C && MGSeqStatGet(lbl_1_bss_1AA) == 0) {
                    fn_1_1F58(-1);
                    lbl_1_bss_1AA = -1;
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                    arg0->func = fn_1_9AF4;
                }
            }
            break;
        default:
            OSReport("*** main mode error(%d)!!\n", arg0->work[0]);
            break;
    }
    lbl_1_bss_30 -= 1.0f;
    if (0.0f == lbl_1_bss_30) {
        Hu3DModelAttrSet(arg0->model[1], 1);
        Hu3DModelAttrReset(arg0->model[2], 0x40000002);
        Hu3DModelAttrReset(arg0->model[2], 1);
        Hu3DMotionTimeSet(arg0->model[2], 0.0f);
        Hu3DMotionSpeedSet(arg0->model[2], 3.0f);
    }
    if (0.0f > lbl_1_bss_30) {
        lbl_1_bss_30 = -1.0f;
        fn_1_8048();
        if (Hu3DMotionEndCheck(arg0->model[2])) {
            Hu3DModelAttrReset(arg0->model[1], 1);
            Hu3DModelAttrSet(arg0->model[2], 1);
        }
    }
}

static void fn_1_9058(omObjData *arg0) {
    s16 temp_r29;
    s16 temp_r28;
    s32 i;

    arg0->work[0] = 1000;
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M402, 32));
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M402, 33));
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M402, 34));
    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(arg0->model[i], 1);
        Hu3DModelAttrSet(arg0->model[i], 0x40000002);
        Hu3DModelLayerSet(arg0->model[i], 0);
        Hu3DModelPosSet(arg0->model[i], 0.0f, 0.0f, 0.0f);
    }
    Hu3DModelReflectTypeSet(arg0->model[0], 3);
    Hu3DModelReflectTypeSet(arg0->model[1], 3);
    Hu3DModelReflectTypeSet(arg0->model[2], 3);
    temp_r29 = arg0->model[0];
    temp_r28 = Hu3DLLightCreateV(temp_r29, &lbl_1_data_34, &lbl_1_data_40, &lbl_1_data_4C);
    Hu3DLLightStaticSet(temp_r29, temp_r28, 1);
    Hu3DModelAttrReset(arg0->model[0], 1);
    Hu3DModelAttrReset(arg0->model[1], 1);
    Hu3DModelShadowMapSet(arg0->model[0]);
    HuAudFXPlay(0x519);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    arg0->func = fn_1_8218;
}

void ObjectSetup(void) {
    Vec sp20;
    omObjData *temp_r30;
    s32 i;

    OSReport("******* M402 ObjectSetup *********\n");
    lbl_1_bss_1E8 = omInitObjMan(400, 0x2000);
    omGameSysInit(lbl_1_bss_1E8);
    lbl_1_bss_1B4 = 0;
    lbl_1_bss_1AA = -1;
    lbl_1_bss_1A8 = -1;
    lbl_1_bss_26 = -1;
    lbl_1_bss_1A4 = -1;
    lbl_1_bss_10 = 1;
    lbl_1_bss_8 = 0.0f;
    lbl_1_bss_C = 2200.0f;
    lbl_1_bss_4 = 2500.0f;
    lbl_1_bss_1D0 = lbl_1_data_10;
    lbl_1_bss_1B8 = lbl_1_data_28;
    Hu3DReflectNoSet(0);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 20000.0f, 1.2f);
    fn_1_1350(&lbl_1_data_10, &lbl_1_data_1C, &lbl_1_data_28);
    lbl_1_bss_38 = 180.0f;
    lbl_1_bss_34 = 4.0f;
    lbl_1_bss_30 = 60.0f;
    lbl_1_bss_14 = Hu3DGLightCreateV(&lbl_1_data_34, &lbl_1_data_40, &lbl_1_data_4C);
    Hu3DGLightStaticSet(lbl_1_bss_14, 1);
    fn_1_8048();
    Hu3DShadowCreate(30.0f, 20.0f, 20000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    PSVECNormalize(&lbl_1_data_60, &sp20);
    Hu3DShadowPosSet(&lbl_1_data_60, &sp20, &lbl_1_data_6C);
    omMakeGroupEx(lbl_1_bss_1E8, 0, 4);
    lbl_1_bss_54 = omGetGroupMemberListEx(lbl_1_bss_1E8, 0);
    for (i = 0; i < 4; i++) {
        temp_r30 = omAddObjEx(lbl_1_bss_1E8, 100, 1, 0, 0, fn_1_7D4C);
        temp_r30->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_1E8, 1, 4);
    lbl_1_bss_50 = omGetGroupMemberListEx(lbl_1_bss_1E8, 1);
    for (i = 0; i < 4; i++) {
        temp_r30 = omAddObjEx(lbl_1_bss_1E8, 101, 1, 0, 1, fn_1_7E84);
        temp_r30->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_1E8, 2, 4);
    lbl_1_bss_4C = omGetGroupMemberListEx(lbl_1_bss_1E8, 2);
    for (i = 0; i < 4; i++) {
        temp_r30 = omAddObjEx(lbl_1_bss_1E8, 102, 1, 11, 2, fn_1_63C8);
        temp_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkFn27A8Struct), MEMORY_DEFAULT_NUM);
        temp_r30->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_1E8, 3, 4);
    lbl_1_bss_48 = omGetGroupMemberListEx(lbl_1_bss_1E8, 3);
    for (i = 0; i < 4; i++) {
        temp_r30 = omAddObjEx(lbl_1_bss_1E8, 103, 1, 3, 3, fn_1_685C);
        temp_r30->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_1E8, 4, 2);
    lbl_1_bss_44 = omGetGroupMemberListEx(lbl_1_bss_1E8, 4);
    for (i = 0; i < 2; i++) {
        temp_r30 = omAddObjEx(lbl_1_bss_1E8, 104, 1, 2, 4, fn_1_6E64);
        temp_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkFn6AB4Struct), MEMORY_DEFAULT_NUM);
        temp_r30->work[0] = i;
    }
    fn_1_0();
    lbl_1_bss_24 = 0;
    omMakeGroupEx(lbl_1_bss_1E8, 5, 300);
    lbl_1_bss_40 = omGetGroupMemberListEx(lbl_1_bss_1E8, 5);
    for (i = 0; i < 7; i++) {
        lbl_1_bss_16[i] = Hu3DModelCreateFile(lbl_1_data_218[i]);
        Hu3DModelAttrSet(lbl_1_bss_16[i], 1);
        Hu3DModelAttrSet(lbl_1_bss_16[i], 0x40000002);
    }
    lbl_1_bss_58 = omAddObjEx(lbl_1_bss_1E8, 106, 3, 1, -1, fn_1_9058);
}

static void fn_1_9AF4(omObjData *arg0) {
    s32 i;

    if (WipeStatGet() == 0) {
        if (lbl_1_bss_1AA >= 0) {
            MGSeqKill(lbl_1_bss_1AA);
        }
        if (lbl_1_bss_1A8 >= 0) {
            MGSeqKill(lbl_1_bss_1A8);
        }
        MGSeqKillAll();
        HuAudAllStop();
        for (i = 0; i < 4; i++) {
            CharModelKill(lbl_1_data_0[GWPlayerCfg[i].character]);
        }
        omOvlReturnEx(1, 1);
    }
}
