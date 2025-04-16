#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/gamework.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/wipe.h"

#include "game/frand.h"

typedef struct M459DllBss18Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04[8];
    /* 0x14 */ s16 unk_14[8];
    /* 0x24 */ u8 unk_24[2];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
} M459DllBss18Struct; /* size = 0x30 */

typedef struct M459DllBss4CStruct {
    /* 0x00 */ s16 unk_00[6];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} M459DllBss4CStruct; /* size = 0x18 */

typedef struct M459DllBss64Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
} M459DllBss64Struct; /* size = 0xC */

typedef struct M459DllBss70Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ s32 unk_08;
} M459DllBss70Struct; /* size = 0xC */

typedef struct M459DllBss7CStruct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ s16 unk_0C[2];
} M459DllBss7CStruct; /* size = 0x10 */

typedef struct M459DllBssCCStruct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ s32 unk_04;
    /* 0x008 */ s32 unk_08;
    /* 0x00C */ Vec unk_0C;
    /* 0x018 */ float unk_18;
    /* 0x01C */ float unk_1C;
    /* 0x020 */ float unk_20;
    /* 0x024 */ char pad_24[0x4];
    /* 0x028 */ s32 unk_28[5];
    /* 0x03C */ s32 unk_3C[5];
    /* 0x050 */ float unk_50;
    /* 0x054 */ float unk_54;
    /* 0x058 */ float unk_58;
    /* 0x05C */ float unk_5C;
    /* 0x060 */ s16 unk_60;
    /* 0x062 */ s16 unk_62[0xC];
    /* 0x07A */ s16 unk_7A[0xC][6];
    /* 0x10A */ s16 unk_10A[2];
    /* 0x10E */ char pad_10E[2];
} M459DllBssCCStruct; /* size = 0x110 */

typedef struct M459DllBss61CStruct {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ float unk_18;
    /* 0x1C */ float unk_1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x24 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ float unk_30;
    /* 0x34 */ float unk_34;
    /* 0x38 */ float unk_38;
    /* 0x3C */ char unk3C[0xC];
    /* 0x48 */ Vec unk_48;
    /* 0x54 */ Vec unk_54;
    /* 0x60 */ char unk60[0xC];
    /* 0x6C */ float unk_6C;
    /* 0x70 */ float unk_70;
    /* 0x74 */ float unk_74;
    /* 0x78 */ float unk_78;
} M459DllBss61CStruct; /* size = 0x7C */

typedef struct M459DllData70Struct {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ GXColor unk_18;
} M459DllData70Struct; /* size = 0x1C */

void fn_1_11DC(float arg8, float arg9, float argA);
void fn_1_1204(float arg8, float arg9, float argA);
void fn_1_122C(void);
void fn_1_14B8(void);
void fn_1_19B4(M459DllBssCCStruct *arg0);
void fn_1_1A00(M459DllBssCCStruct *arg0);
void fn_1_1D8(void);
void fn_1_1FDC(M459DllBssCCStruct *arg0);
void fn_1_2044(M459DllBssCCStruct *arg0);
void fn_1_21AC(M459DllBssCCStruct *arg0);
void fn_1_23AC(M459DllBssCCStruct *arg0);
void fn_1_25C8(M459DllBssCCStruct *arg0);
void fn_1_27C8(M459DllBssCCStruct *arg0);
void fn_1_2930(M459DllBssCCStruct *arg0);
void fn_1_2B24(M459DllBssCCStruct *arg0);
void fn_1_2F18(M459DllBssCCStruct *arg0);
void fn_1_3004(M459DllBssCCStruct *arg0);
void fn_1_338C(M459DllBssCCStruct *arg0, float arg8);
void fn_1_3700(M459DllBssCCStruct *arg0);
void fn_1_4160(M459DllBssCCStruct *arg0);
float fn_1_4210(float arg8, float arg9, float argA);
void fn_1_4314(s32 arg0, u32 arg1);
void fn_1_4530(void);
void fn_1_45EC(void);
void fn_1_4764(void);
void fn_1_47E4(void);
void fn_1_4850(void);
void fn_1_48E4(void);
void fn_1_4A74(void);
void fn_1_4B68(void);
void fn_1_4C1C(void);
void fn_1_4CD0(void);
s32 fn_1_4E54(void);
void fn_1_4E64(s32 arg0);
void fn_1_4E98(void);
void fn_1_4EAC(void);
void fn_1_4F8C(s32 arg0);
s32 fn_1_4FAC(void);
void fn_1_4FC8(void);
void fn_1_52D8(s32 arg0);
s32 fn_1_52F0(void);
s32 fn_1_5300(void);
s32 fn_1_5310(void);
void fn_1_535C(void);
void fn_1_5490(void);
void fn_1_556C(M459DllBss18Struct *arg0);
void fn_1_55B0(M459DllBss18Struct *arg0);
void fn_1_5A78(M459DllBss18Struct *arg0);
void fn_1_5E3C(M459DllBss18Struct *arg0);
void fn_1_5EAC(void);
void fn_1_5F40(M459DllBss7CStruct *arg0);
void fn_1_5F84(M459DllBss7CStruct *arg0);
void fn_1_6198(M459DllBss7CStruct *arg0);
void fn_1_640(void);
void fn_1_6458(M459DllBss7CStruct *arg0);
void fn_1_73C(void);
void fn_1_E78(void);

Process *lbl_1_bss_6E4;
Process *lbl_1_bss_698[0x13];
M459DllBss61CStruct lbl_1_bss_61C;
M459DllBssCCStruct lbl_1_bss_CC[5];
M459DllBss7CStruct lbl_1_bss_7C[5];
M459DllBss70Struct lbl_1_bss_70;
M459DllBss64Struct lbl_1_bss_64;
M459DllBss4CStruct lbl_1_bss_4C;
s16 lbl_1_bss_48[1];
M459DllBss18Struct lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
u8 lbl_1_bss_2;
s16 lbl_1_bss_0;

static const s32 lbl_1_rodata_10[0xC] = {
    DATA_MAKE_NUM(DATADIR_M459, 0x05),
    DATA_MAKE_NUM(DATADIR_M459, 0x03),
    DATA_MAKE_NUM(DATADIR_M459, 0x04),
    DATA_MAKE_NUM(DATADIR_M459, 0x01),
    DATA_MAKE_NUM(DATADIR_M459, 0x02),
    DATA_MAKE_NUM(DATADIR_M459, 0x05),
    DATA_MAKE_NUM(DATADIR_M459, 0x03),
    DATA_MAKE_NUM(DATADIR_M459, 0x04),
    DATA_MAKE_NUM(DATADIR_M459, 0x01),
    DATA_MAKE_NUM(DATADIR_M459, 0x02),
    DATA_MAKE_NUM(DATADIR_M459, 0x0E),
    DATA_MAKE_NUM(DATADIR_M459, 0x0F),
};
static const s32 lbl_1_rodata_40[5][6] = {
    {
        DATA_MAKE_NUM(DATADIR_M459, 0x28),
        DATA_MAKE_NUM(DATADIR_M459, 0x29),
        DATA_MAKE_NUM(DATADIR_M459, 0x2A),
        DATA_MAKE_NUM(DATADIR_M459, 0x2C),
        DATA_MAKE_NUM(DATADIR_M459, 0x2B),
        DATA_MAKE_NUM(DATADIR_M459, 0x2D),
    },
    {
        DATA_MAKE_NUM(DATADIR_M459, 0x1C),
        DATA_MAKE_NUM(DATADIR_M459, 0x1D),
        DATA_MAKE_NUM(DATADIR_M459, 0x1E),
        DATA_MAKE_NUM(DATADIR_M459, 0x20),
        DATA_MAKE_NUM(DATADIR_M459, 0x1F),
        DATA_MAKE_NUM(DATADIR_M459, 0x21),
    },
    {
        DATA_MAKE_NUM(DATADIR_M459, 0x22),
        DATA_MAKE_NUM(DATADIR_M459, 0x23),
        DATA_MAKE_NUM(DATADIR_M459, 0x24),
        DATA_MAKE_NUM(DATADIR_M459, 0x26),
        DATA_MAKE_NUM(DATADIR_M459, 0x25),
        DATA_MAKE_NUM(DATADIR_M459, 0x27),
    },
    {
        DATA_MAKE_NUM(DATADIR_M459, 0x10),
        DATA_MAKE_NUM(DATADIR_M459, 0x11),
        DATA_MAKE_NUM(DATADIR_M459, 0x12),
        DATA_MAKE_NUM(DATADIR_M459, 0x14),
        DATA_MAKE_NUM(DATADIR_M459, 0x13),
        DATA_MAKE_NUM(DATADIR_M459, 0x15),
    },
    {
        DATA_MAKE_NUM(DATADIR_M459, 0x16),
        DATA_MAKE_NUM(DATADIR_M459, 0x17),
        DATA_MAKE_NUM(DATADIR_M459, 0x18),
        DATA_MAKE_NUM(DATADIR_M459, 0x1A),
        DATA_MAKE_NUM(DATADIR_M459, 0x19),
        DATA_MAKE_NUM(DATADIR_M459, 0x1B),
    },
};
static const s32 lbl_1_rodata_B8[2] = { DATA_MAKE_NUM(DATADIR_M459, 0x3C), DATA_MAKE_NUM(DATADIR_M459, 0x3D) };
static const s32 lbl_1_rodata_C0[2] = { DATA_MAKE_NUM(DATADIR_M459, 0x3A), DATA_MAKE_NUM(DATADIR_M459, 0x3B) };
static const s32 lbl_1_rodata_C8[6] = {
    DATA_MAKE_NUM(DATADIR_M459, 0x30),
    DATA_MAKE_NUM(DATADIR_M459, 0x30),
    DATA_MAKE_NUM(DATADIR_M459, 0x2F),
    DATA_MAKE_NUM(DATADIR_M459, 0x2F),
    DATA_MAKE_NUM(DATADIR_M459, 0x31),
    DATA_MAKE_NUM(DATADIR_M459, 0x2E),
};
static const s32 lbl_1_rodata_E0[1] = { DATA_MAKE_NUM(DATADIR_M459, 0x00) };
static const s32 lbl_1_rodata_E4[8] = {
    DATA_MAKE_NUM(DATADIR_M459, 0x06),
    DATA_MAKE_NUM(DATADIR_M459, 0x07),
    DATA_MAKE_NUM(DATADIR_M459, 0x08),
    DATA_MAKE_NUM(DATADIR_M459, 0x09),
    DATA_MAKE_NUM(DATADIR_M459, 0x0A),
    DATA_MAKE_NUM(DATADIR_M459, 0x0B),
    DATA_MAKE_NUM(DATADIR_M459, 0x0C),
    DATA_MAKE_NUM(DATADIR_M459, 0x0D),
};
static const s32 lbl_1_rodata_104[8] = {
    DATA_MAKE_NUM(DATADIR_M459, 0x32),
    DATA_MAKE_NUM(DATADIR_M459, 0x33),
    DATA_MAKE_NUM(DATADIR_M459, 0x34),
    DATA_MAKE_NUM(DATADIR_M459, 0x35),
    DATA_MAKE_NUM(DATADIR_M459, 0x36),
    DATA_MAKE_NUM(DATADIR_M459, 0x37),
    DATA_MAKE_NUM(DATADIR_M459, 0x38),
    DATA_MAKE_NUM(DATADIR_M459, 0x39),
};
static const s32 lbl_1_rodata_124[0x63] = { 0x14, 0x13, 0x12, 0x11, 0x10, 0xF, 0xE, 0xD, 0xC, 0xB, 0xA, 9, 8, 7, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };

static const s32 lbl_1_rodata_2B0[4] = {0x80000000, 0x40000000, 0x20000000, 0x10000000};

void ObjectSetup(void)
{
    s32 var_r31;
    u32 var_r30;

    lbl_1_bss_6E4 = omInitObjMan(1, 0x2000);
    omGameSysInit(lbl_1_bss_6E4);
    fn_1_1D8();
    var_r30 = HuPadRumbleGet();
    if ((var_r30 & 0x80000000) != 0) {
        lbl_1_bss_8 = GWGameStat.rumble;
    }
    else {
        lbl_1_bss_8 = 0;
    }
    lbl_1_bss_4 = 0;
    for (var_r31 = 0; var_r31 < 0x13; var_r31++) {
        lbl_1_bss_698[var_r31] = NULL;
    }
    lbl_1_bss_698[0] = HuPrcChildCreate(fn_1_640, 0x100, 0x1000, 0, lbl_1_bss_6E4);
    lbl_1_bss_698[1] = HuPrcChildCreate(fn_1_73C, 0x101, 0x3000, 0, lbl_1_bss_6E4);
}

void fn_1_1D8(void)
{
    M459DllBssCCStruct *var_r29;
    s32 var_r31;
    s32 var_r30;
    M459DllBss18Struct *var_r28;
    s16 *var_r27;
    s32 var_r26;
    s16 *var_r25;
    M459DllBss7CStruct *var_r24;

    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        var_r29 = &lbl_1_bss_CC[var_r30];
        for (var_r31 = 0; var_r31 < 0xC; var_r31++) {
            if ((var_r31 >= 5) && (var_r31 <= 9)) {
                var_r29->unk_62[var_r31] = Hu3DModelLink(var_r29->unk_62[var_r31 - 5]);
            }
            else {
                var_r29->unk_62[var_r31] = Hu3DModelCreateFile(lbl_1_rodata_10[var_r31]);
            }
            if ((var_r31 >= 0) && (var_r31 <= 4)) {
                Hu3DModelLayerSet(var_r29->unk_62[var_r31], 2);
            }
            else if ((var_r31 >= 5) && (var_r31 <= 9)) {
                Hu3DModelLayerSet(var_r29->unk_62[var_r31], 0);
                Hu3DModelAttrSet(var_r29->unk_62[var_r31], HU3D_ATTR_CULL_FRONT);
            }
            else {
                Hu3DModelLayerSet(var_r29->unk_62[var_r31], 3);
            }
            if (var_r31 == 0xA) {
                Hu3DModelAttrSet(var_r29->unk_62[var_r31], HU3D_ATTR_ZWRITE_OFF);
            }
            if ((var_r31 >= 0) && (var_r31 <= 4)) {
                Hu3DModelShadowSet(var_r29->unk_62[var_r31]);
            }
            Hu3DModelAttrSet(var_r29->unk_62[var_r31], HU3D_ATTR_DISPOFF);
        }
        for (var_r26 = 0; var_r26 < 5; var_r26++) {
            for (var_r31 = 0; var_r31 < 6; var_r31++) {
                var_r29->unk_7A[var_r26][var_r31] = Hu3DJointMotionFile(var_r29->unk_62[var_r26], lbl_1_rodata_40[var_r26][var_r31]);
            }
        }
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            var_r29->unk_10A[var_r31] = espEntry(lbl_1_rodata_B8[var_r31], 0, 0);
            espDispOff(var_r29->unk_10A[var_r31]);
        }
    }
    CharModelLayerSetAll(3);
    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        var_r24 = &lbl_1_bss_7C[var_r30];
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            var_r24->unk_0C[var_r31] = espEntry(lbl_1_rodata_C0[var_r31], 0, 0);
            espDispOff(var_r24->unk_0C[var_r31]);
        }
    }
    var_r25 = lbl_1_bss_4C.unk_00;
    for (var_r30 = 0; var_r30 < 6; var_r30++) {
        var_r25[var_r30] = espEntry(lbl_1_rodata_C8[var_r30], 0, 0);
    }
    espColorSet(var_r25[5], 0, 0, 0);
    var_r27 = lbl_1_bss_48;
    for (var_r30 = 0; var_r30 < 1; var_r30++) {
        var_r27[var_r30] = Hu3DModelCreateFile(lbl_1_rodata_E0[var_r30]);
        Hu3DModelLayerSet(var_r27[var_r30], 1);
        Hu3DModelShadowMapSet(var_r27[var_r30]);
    }
    var_r28 = &lbl_1_bss_18;
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        var_r28->unk_14[var_r30] = Hu3DModelCreateFile(lbl_1_rodata_E4[var_r30]);
        Hu3DModelLayerSet(var_r28->unk_14[var_r30], 2);
        Hu3DModelAttrSet(var_r28->unk_14[var_r30], HU3D_ATTR_ZWRITE_OFF);
        Hu3DModelAttrSet(var_r28->unk_14[var_r30], HU3D_ATTR_DISPOFF);
    }
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        var_r28->unk_04[var_r30] = espEntry(lbl_1_rodata_104[var_r30], 0, 0);
        espDispOff(var_r28->unk_04[var_r30]);
    }
}

void fn_1_640(void)
{
    s32 var_r31;

    while (omSysExitReq == 0) {
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFadeOut(0x3E8);
    for (var_r31 = 0; var_r31 < 0x13; var_r31++) {
        if ((var_r31 != 0) && lbl_1_bss_698[var_r31]) {
            HuPrcKill(lbl_1_bss_698[var_r31]);
            lbl_1_bss_698[var_r31] = NULL;
        }
    }
    HuPrcVSleep();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
    lbl_1_bss_698[0] = NULL;
}

void fn_1_73C(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    lbl_1_bss_698[2] = HuPrcChildCreate(fn_1_E78, 0xFF, 0x1000, 0, HuPrcCurrentGet());
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_698[var_r31 + 3] = HuPrcChildCreate(fn_1_14B8, 0x102, 0x3000, 0, HuPrcCurrentGet());
        *((s32 *)&lbl_1_bss_698[var_r31 + 3]->user_data) = var_r31;
    }
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_698[var_r31 + 8] = HuPrcChildCreate(fn_1_5EAC, 0x105, 0x1000, 0, HuPrcCurrentGet());
        *((s32 *)&lbl_1_bss_698[var_r31 + 8]->user_data) = var_r31;
    }
    lbl_1_bss_698[0x11] = HuPrcChildCreate(fn_1_5490, 0x103, 0x2000, 0, HuPrcCurrentGet());
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        fn_1_4314(var_r31, frandmod(5));
    }
    lbl_1_bss_698[0xD] = HuPrcChildCreate(fn_1_4CD0, 0x200, 0x2000, 0, HuPrcCurrentGet());
    lbl_1_bss_698[0xE] = HuPrcChildCreate(fn_1_4EAC, 0x103, 0x2000, 0, HuPrcCurrentGet());
    lbl_1_bss_698[0xF] = HuPrcChildCreate(fn_1_4FC8, 0x104, 0x2000, 0, HuPrcCurrentGet());
    lbl_1_bss_698[0x10] = HuPrcChildCreate(fn_1_535C, 0x110, 0x2000, 0, HuPrcCurrentGet());
    HuPrcVSleep();
    fn_1_1204(0.0f, 90.0f, -400.0f);
    fn_1_11DC(0.0f, 300.0f, 1100.0f);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_698[0x12] = HuPrcChildCreate(fn_1_4530, 0x100, 0x4000, 0, HuPrcCurrentGet());

    while (lbl_1_bss_698[0x12]) {
        HuPrcVSleep();
    }
    while (TRUE) {
        lbl_1_bss_10 = frandmod(5);
        var_r29 = frandmod(5);
        var_r30 = frandmod(5);
        if (var_r29 == var_r30) {
            var_r30 = (var_r30 + 1) % 5;
        }
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            if (var_r31 != lbl_1_bss_10) {
                lbl_1_bss_7C[var_r31].unk_08 = var_r29;
            }
        }
        lbl_1_bss_7C[lbl_1_bss_10].unk_08 = var_r30;
        if (fn_1_52F0() > 0) {
            for (var_r31 = 0; var_r31 < 5; var_r31++) {
                fn_1_4314(var_r31, frandmod(5));
            }
            lbl_1_bss_698[0x12] = HuPrcChildCreate(fn_1_4C1C, 0x100, 0x4000, 0, HuPrcCurrentGet());
            while (lbl_1_bss_698[0x12]) {
                HuPrcVSleep();
            }
            HuPrcSleep(0x3C);
            lbl_1_bss_698[0x12] = HuPrcChildCreate(fn_1_4764, 0x100, 0x4000, 0, HuPrcCurrentGet());
            while (lbl_1_bss_698[0x12]) {
                HuPrcVSleep();
            }
        }
        var_r28 = lbl_1_rodata_124[fn_1_52F0()] * 0x3C;
        fn_1_4E64(var_r28);
        lbl_1_bss_18.unk_00 = 1;
        while (TRUE) {
            if ((lbl_1_bss_18.unk_00 == 0) || (fn_1_4E54() <= 0)) {
                break;
            }
            HuPrcVSleep();
        }
        fn_1_4E98();
        if (lbl_1_bss_18.unk_00 != 0) {
            lbl_1_bss_18.unk_00 = 2;
            lbl_1_bss_698[0x12] = HuPrcChildCreate(fn_1_4A74, 0x100, 0x4000, 0, HuPrcCurrentGet());
            while (lbl_1_bss_698[0x12]) {
                HuPrcVSleep();
            }
        }
        else {
            lbl_1_bss_698[0x12] = HuPrcChildCreate(fn_1_47E4, 0x100, 0x4000, 0, HuPrcCurrentGet());
            while (lbl_1_bss_698[0x12]) {
                HuPrcVSleep();
            }
            if (lbl_1_bss_14 == lbl_1_bss_10) {
                lbl_1_bss_698[0x12] = HuPrcChildCreate(fn_1_4850, 0x100, 0x4000, 0, HuPrcCurrentGet());
                while (lbl_1_bss_698[0x12]) {
                    HuPrcVSleep();
                }
                goto label;
            }
            else {
                
                lbl_1_bss_698[0x12] = HuPrcChildCreate(fn_1_48E4, 0x100, 0x4000, 0, HuPrcCurrentGet());
                while (lbl_1_bss_698[0x12]) {
                    HuPrcVSleep();
                }
                if(0) {
                    label:
                    fn_1_52D8(1);
                    if (fn_1_52F0() != 0x63) {
                        lbl_1_bss_698[0x12] = HuPrcChildCreate(fn_1_4B68, 0x100, 0x4000, 0, HuPrcCurrentGet());
                        while (lbl_1_bss_698[0x12]) {
                            HuPrcVSleep();
                        }
                        continue;
                    } 
                }
            }
        }
        break;
    }
    lbl_1_bss_698[0x12] = HuPrcChildCreate(fn_1_45EC, 0x100, 0x4000, 0, HuPrcCurrentGet());

    while (lbl_1_bss_698[0x12]) {
        HuPrcVSleep();
    }
    mgRecordExtra = fn_1_52F0();
    omSysExitReq = 1;
    HuPrcEnd();
    lbl_1_bss_698[1] = NULL;
    lbl_1_bss_698[1] = NULL;
}

void fn_1_E78(void)
{
    float var_f31;
    M459DllBss61CStruct *var_r31;

    var_r31 = &lbl_1_bss_61C;
    var_r31->unk_00.x = 0.0f;
    var_r31->unk_00.y = 300.0f;
    var_r31->unk_00.z = 1100.0f;
    var_r31->unk_0C.x = 90.0f;
    var_r31->unk_0C.y = -400.0f;
    var_r31->unk_0C.z = 0.0f;
    var_r31->unk_18 = 0.0f;
    var_r31->unk_1C = 1.0f;
    var_r31->unk_20 = 0.0f;
    var_r31->unk_74 = 1.0f;
    var_r31->unk_6C = 1.0f;
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 30.0f, 10.0f, 8000.0f, 1.2f);
    while (TRUE) {
        fn_1_122C();
        if (var_r31->unk_6C < 1.0f) {
            var_f31 = sind((90.0f * var_r31->unk_6C));
            var_r31->unk_00.x = var_r31->unk_24 + (var_f31 * (var_r31->unk_48.x - var_r31->unk_24));
            var_r31->unk_00.y = var_r31->unk_28 + (var_f31 * (var_r31->unk_48.y - var_r31->unk_28));
            var_r31->unk_00.z = var_r31->unk_2C + (var_f31 * (var_r31->unk_48.z - var_r31->unk_2C));
            if ((var_r31->unk_6C += var_r31->unk_70) >= 1.0f) {
                var_r31->unk_00 = var_r31->unk_48;
            }
        }
        if (var_r31->unk_74 < 1.0f) {
            var_f31 = sind((90.0f * var_r31->unk_74));
            var_r31->unk_0C.x = var_r31->unk_30 + (var_f31 * (var_r31->unk_54.x - var_r31->unk_30));
            var_r31->unk_0C.y = var_r31->unk_34 + (var_f31 * (var_r31->unk_54.y - var_r31->unk_34));
            var_r31->unk_0C.z = var_r31->unk_38 + (var_f31 * (var_r31->unk_54.z - var_r31->unk_38));
            if ((var_r31->unk_74 += var_r31->unk_78) >= 1.0f) {
                var_r31->unk_0C = var_r31->unk_54;
            }
        }
        Hu3DCameraPosSet(1, var_r31->unk_00.x, var_r31->unk_00.y, var_r31->unk_00.z, var_r31->unk_18, var_r31->unk_1C, var_r31->unk_20,
            var_r31->unk_0C.x, var_r31->unk_0C.y, var_r31->unk_0C.z);
        HuPrcVSleep();
    }
}

void fn_1_11DC(float arg8, float arg9, float argA)
{
    M459DllBss61CStruct *var_r31 = &lbl_1_bss_61C;
    var_r31->unk_00.x = arg8;
    var_r31->unk_00.y = arg9;
    var_r31->unk_00.z = argA;
}

void fn_1_1204(float arg8, float arg9, float argA)
{
    M459DllBss61CStruct *var_r31 = &lbl_1_bss_61C;
    var_r31->unk_0C.x = arg8;
    var_r31->unk_0C.y = arg9;
    var_r31->unk_0C.z = argA;
}

void fn_1_122C(void)
{
    M459DllBss61CStruct *var_r31;

    if (lbl_1_bss_4 != 0) {
        var_r31 = &lbl_1_bss_61C;
        var_r31->unk_0C.x += (0.25f * HuPadStkX[0]);
        var_r31->unk_0C.y += (0.25f * HuPadStkY[0]);
        var_r31->unk_00.z += (0.25f * HuPadTrigL[0]);
        var_r31->unk_00.z -= (0.25f * HuPadTrigR[0]);
        var_r31->unk_00.x += (0.25f * HuPadSubStkX[0]);
        var_r31->unk_00.y += (0.25f * HuPadSubStkY[0]);
    }
}

void fn_1_142C(void)
{
    M459DllBss61CStruct *var_r31 = &lbl_1_bss_61C;
    print8(0x20, 0x40, 1.5f, "AT  : x=%.2f y=%.2f z=%.2f", var_r31->unk_0C.x, var_r31->unk_0C.y, var_r31->unk_0C.z);
    print8(0x20, 0x50, 1.5f, "EYE : x=%.2f y=%.2f z=%.2f", var_r31->unk_00.x, var_r31->unk_00.y, var_r31->unk_00.z);
}

static const u8 lbl_1_rodata_31C[8] = { 9, 0xE, 0xC, 0xA, 0xB };

void fn_1_14B8(void)
{
    M459DllBssCCStruct *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r29 = (s32)HuPrcCurrentGet()->user_data;
    var_r31 = &lbl_1_bss_CC[var_r29];
    var_r31->unk_00 = var_r29;
    var_r31->unk_04 = 0;
    var_r31->unk_0C.x = -260.0f + (130.0f * var_r29);
    var_r31->unk_0C.y = 0.0f;
    var_r31->unk_0C.z = 0.0f;
    var_r31->unk_18 = 0.0f;
    var_r31->unk_1C = 0.0f;
    var_r31->unk_20 = 0.0f;
    var_r31->unk_50 = 0.0f;
    var_r31->unk_54 = 0.0f;
    var_r31->unk_58 = 0.0f;
    Hu3DMotionSet(var_r31->unk_62[var_r31->unk_08], var_r31->unk_7A[var_r31->unk_08][var_r31->unk_60 = 0]);
    Hu3DModelAttrSet(var_r31->unk_62[var_r31->unk_08], HU3D_MOTATTR_LOOP);
    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        var_r31->unk_28[var_r30] = CharModelEffectNpcInit(var_r31->unk_62[var_r30], var_r31->unk_7A[var_r30][2], 1, lbl_1_rodata_31C[var_r30]);
        var_r31->unk_3C[var_r30] = CharModelEffectNpcInit(var_r31->unk_62[var_r30], var_r31->unk_7A[var_r30][1], 0, lbl_1_rodata_31C[var_r30]);
    }
    while (TRUE) {
        switch (var_r31->unk_04) {
            case 0:
                fn_1_19B4(var_r31);
                break;
            case 1:
                fn_1_1A00(var_r31);
                break;
            case 3:
                fn_1_1FDC(var_r31);
                lbl_1_bss_7C[var_r31->unk_00].unk_04 = 3;
                break;
            case 4:
                fn_1_2044(var_r31);
                break;
            case 5:
                fn_1_21AC(var_r31);
                break;
            case 6:
                fn_1_23AC(var_r31);
                break;
            case 7:
                fn_1_27C8(var_r31);
                break;
            case 8:
                fn_1_2930(var_r31);
                break;
            case 9:
                fn_1_2B24(var_r31);
                break;
            case 10:
                fn_1_3004(var_r31);
                break;
            case 11:
                fn_1_2F18(var_r31);
                break;
            case 12:
                fn_1_25C8(var_r31);
                break;
            case 13:
                fn_1_3700(var_r31);
                break;
        }
    }
}

void fn_1_1778(M459DllBssCCStruct *arg0, s16 arg1, float arg8, float arg9, u32 arg2)
{
    Hu3DMotionShiftSet(arg0->unk_62[arg0->unk_08], arg0->unk_7A[arg0->unk_08][arg0->unk_60 = arg1], arg8, arg9, arg2);
    Hu3DMotionShiftSet(arg0->unk_62[arg0->unk_08 + 5], arg0->unk_7A[arg0->unk_08][arg1], arg8, arg9, arg2);
    Hu3DModelScaleSet(arg0->unk_62[arg0->unk_08 + 5], 1.0f, -1.0f, 1.0f);
}

void fn_1_189C(M459DllBssCCStruct *arg0, s16 arg1, u32 arg2)
{
    Hu3DMotionSet(arg0->unk_62[arg0->unk_08], arg0->unk_7A[arg0->unk_08][arg0->unk_60 = arg1]);
    Hu3DMotionSet(arg0->unk_62[arg0->unk_08 + 5], arg0->unk_7A[arg0->unk_08][arg1]);
    Hu3DModelScaleSet(arg0->unk_62[arg0->unk_08 + 5], 1.0f, -1.0f, 1.0f);
    Hu3DModelAttrSet(arg0->unk_62[arg0->unk_08], arg2);
    Hu3DModelAttrSet(arg0->unk_62[arg0->unk_08 + 5], arg2);
}

void fn_1_19B4(M459DllBssCCStruct *arg0)
{
    s32 var_r30;
    do {
        var_r30 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
    } while (arg0->unk_04 == var_r30);
}

static const s32 lbl_1_rodata_330[5] = { 0x36, 0x44, 0x47, 0x41, 0x4C };

void fn_1_1A00(M459DllBssCCStruct *var_r31)
{
    Vec sp8;
    float var_f31;

    s32 var_r30;
    s16 var_r29;
    s16 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    if (var_r31->unk_00 == 0) {
        HuAudFXPlay(0x30D);
    }
    var_r29 = var_r31->unk_62[10];
    Hu3DModelAttrReset(var_r29, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(var_r29, 1.0f, 1.0f, 1.0f);
    Hu3DModelTPLvlSet(var_r29, 1.0f);
    sp8 = var_r31->unk_0C;
    for (var_r30 = 0; var_r30 < 0x28; var_r30++) {
        var_f31 = sind((2.25f * var_r30));
        sp8.y = 170.0f + (350.0f - (350.0f * var_f31));
        Hu3DModelPosSet(var_r29, sp8.x, sp8.y, sp8.z);
        var_r27 = var_r31->unk_04;
        fn_1_4160(var_r31);
        HuPrcVSleep();
        if (var_r31->unk_04 != var_r27) {
            return;
        }
    }
    if (var_r31->unk_00 == 0) {
        HuAudFXPlay(0x312);
        HuAudFXPlay(0x314);
    }
    for (var_r30 = 0; var_r30 < 0x14; var_r30++) {
        var_f31 = sind((4.5f * var_r30));
        var_f31 = 1.0f - var_f31;
        Hu3DModelScaleSet(var_r29, var_f31, var_f31, var_f31);
        Hu3DModelTPLvlSet(var_r29, var_f31);
        sp8.y = 170.0f - (2.0f * var_r30);
        Hu3DModelPosSet(var_r29, sp8.x, sp8.y, sp8.z);
        var_r26 = var_r31->unk_04;
        fn_1_4160(var_r31);
        HuPrcVSleep();
        if (var_r31->unk_04 != var_r26) {
            return;
        }
    }
    Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);
    HuAudFXPlay(lbl_1_rodata_330[var_r31->unk_08]);
    var_r28 = var_r31->unk_10A[0];
    sp8 = var_r31->unk_0C;
    sp8.y = 200.0f;
    Hu3D3Dto2D(&sp8, 1, &sp8);
    espPosSet(var_r28, sp8.x, sp8.y);
    espTPLvlSet(var_r28, 1.0f);
    espDispOn(var_r28);
    fn_1_1778(var_r31, 3, 0.0f, 8.0f, HU3D_ATTR_NONE);
    for (var_r30 = 0; var_r30 < 0x3C; var_r30++) {
        var_r25 = var_r31->unk_04;
        fn_1_4160(var_r31);
        HuPrcVSleep();
        if (var_r31->unk_04 != var_r25) {
            return;
        }
    }
    fn_1_1778(var_r31, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    for (var_r30 = 0; var_r30 <= 0xA; var_r30++) {
        espTPLvlSet(var_r28, 1.0f - (0.1f * var_r30));
        var_r24 = var_r31->unk_04;
        fn_1_4160(var_r31);
        HuPrcVSleep();
        if (var_r31->unk_04 != var_r24) {
            return;
        }
    }
    espDispOff(var_r28);
    lbl_1_bss_CC[var_r31->unk_00].unk_04 = 0;
}

void fn_1_1FDC(M459DllBssCCStruct *arg0)
{
    s32 var_r30;

    lbl_1_bss_7C[arg0->unk_00].unk_04 = 1;
    do {
        var_r30 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
    } while (arg0->unk_04 == var_r30);
}

void fn_1_2044(M459DllBssCCStruct *var_r31)
{
    Vec sp8;

    s32 var_r30;
    s16 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r29 = var_r31->unk_10A[0];
    sp8 = var_r31->unk_0C;
    sp8.y = 200.0f;
    Hu3D3Dto2D(&sp8, 1, &sp8);
    espPosSet(var_r29, sp8.x, sp8.y);
    espTPLvlSet(var_r29, 1.0f);
    espDispOn(var_r29);
    for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
        var_r28 = var_r31->unk_04;
        fn_1_4160(var_r31);
        HuPrcVSleep();
        if (var_r31->unk_04 != var_r28) {
            return;
        }
    }
    for (var_r30 = 0; var_r30 <= 0xA; var_r30++) {
        espTPLvlSet(var_r29, 1.0f - (0.1f * var_r30));
        var_r27 = var_r31->unk_04;
        fn_1_4160(var_r31);
        HuPrcVSleep();
        if (var_r31->unk_04 != var_r27) {
            return;
        }
    }
    espDispOff(var_r29);
    lbl_1_bss_CC[var_r31->unk_00].unk_04 = 0;
}

void fn_1_21AC(M459DllBssCCStruct *arg0)
{
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    if (lbl_1_bss_C > arg0->unk_00) {
        for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
            arg0->unk_50 = 0.0001f;
            fn_1_338C(arg0, 0.1f);
            var_r29 = arg0->unk_04;
            fn_1_4160(arg0);
            HuPrcVSleep();
            if (arg0->unk_04 != var_r29) {
                return;
            }
        }
    }
    else {
        for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
            arg0->unk_50 = -0.0001f;
            fn_1_338C(arg0, 0.1f);
            var_r28 = arg0->unk_04;
            fn_1_4160(arg0);
            HuPrcVSleep();
            if (arg0->unk_04 != var_r28) {
                return;
            }
        }
    }
    fn_1_1778(arg0, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    lbl_1_bss_CC[arg0->unk_00].unk_04 = 0;
}

static const s32 lbl_1_rodata_36C[5] = { 0x38, 0x44, 0x47, 0x41, 0x4C };

void fn_1_23AC(M459DllBssCCStruct *arg0)
{
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    if (lbl_1_bss_C > arg0->unk_00) {
        for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
            arg0->unk_50 = 0.0001f;
            fn_1_338C(arg0, 0.1f);
            var_r29 = arg0->unk_04;
            fn_1_4160(arg0);
            HuPrcVSleep();
            if (arg0->unk_04 != var_r29) {
                return;
            }
        }
    }
    else {
        for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
            arg0->unk_50 = -0.0001f;
            fn_1_338C(arg0, 0.1f);
            var_r28 = arg0->unk_04;
            fn_1_4160(arg0);
            HuPrcVSleep();
            if (arg0->unk_04 != var_r28) {
                return;
            }
        }
    }
    HuAudFXPlay(lbl_1_rodata_36C[arg0->unk_08]);
    fn_1_1778(arg0, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    lbl_1_bss_CC[arg0->unk_00].unk_04 = 0;
}

void fn_1_25C8(M459DllBssCCStruct *arg0)
{
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    if (lbl_1_bss_C > arg0->unk_00) {
        for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
            arg0->unk_58 = 0.0001f;
            fn_1_338C(arg0, 0.1f);
            var_r29 = arg0->unk_04;
            fn_1_4160(arg0);
            HuPrcVSleep();
            if (arg0->unk_04 != var_r29) {
                return;
            }
        }
    }
    else {
        for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
            arg0->unk_58 = 0.0001f;
            fn_1_338C(arg0, 0.1f);
            var_r28 = arg0->unk_04;
            fn_1_4160(arg0);
            HuPrcVSleep();
            if (arg0->unk_04 != var_r28) {
                return;
            }
        }
    }
    fn_1_1778(arg0, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    lbl_1_bss_CC[arg0->unk_00].unk_04 = 0;
}

void fn_1_27C8(M459DllBssCCStruct *arg0)
{
    Vec sp8;

    s32 var_r30;
    s16 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r29 = arg0->unk_10A[1];
    sp8 = arg0->unk_0C;
    sp8.y = 200.0f;
    Hu3D3Dto2D(&sp8, 1, &sp8);
    espPosSet(var_r29, sp8.x, sp8.y);
    espTPLvlSet(var_r29, 1.0f);
    espDispOn(var_r29);
    for (var_r30 = 0; var_r30 < 0x3C; var_r30++) {
        var_r28 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r28) {
            return;
        }
    }
    for (var_r30 = 0; var_r30 <= 0xA; var_r30++) {
        espTPLvlSet(var_r29, 1.0f - (0.1f * var_r30));
        var_r27 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r27) {
            return;
        }
    }
    espDispOff(var_r29);
    lbl_1_bss_CC[arg0->unk_00].unk_04 = 0;
}

static const s32 lbl_1_rodata_380[5] = { 0x38, 0x44, 0x47, 0x41, 0x4C };

void fn_1_2930(M459DllBssCCStruct *arg0)
{
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
        var_r29 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r29) {
            return;
        }
    }
    for (var_r30 = 0; var_r30 < 0xF; var_r30++) {
        arg0->unk_58 = 0.0001f;
        fn_1_338C(arg0, 0.2f);
        var_r28 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r28) {
            return;
        }
    }
    HuAudFXPlay(lbl_1_rodata_380[arg0->unk_08]);
    fn_1_1778(arg0, 5, 0.0f, 8.0f, HU3D_ATTR_NONE);
    for (var_r30 = 0; var_r30 < 0x8C; var_r30++) {
        var_r27 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r27) {
            return;
        }
    }
    lbl_1_bss_CC[arg0->unk_00].unk_04 = 0;
}

static const s32 lbl_1_rodata_398[5] = { 0x39, 0x43, 0x46, 0x40, 0x4B };

void fn_1_2B24(M459DllBssCCStruct *arg0)
{
    Vec sp8;

    s16 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r30 = arg0->unk_62[11];
    sp8 = arg0->unk_0C;
    sp8.y = 80.0f;
    sp8.z = -50.0f;
    Hu3DModelPosSet(var_r30, sp8.x, sp8.y, sp8.z);
    Hu3DMotionTimeSet(var_r30, 0.0f);
    Hu3DModelAttrReset(var_r30, HU3D_ATTR_DISPOFF);
    for (var_r29 = 0; var_r29 < 0x1E; var_r29++) {
        var_r28 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r28) {
            return;
        }
    }
    Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    HuAudFXPlay(lbl_1_rodata_398[arg0->unk_08]);
    fn_1_1778(arg0, 4, 0.0f, 8.0f, HU3D_ATTR_NONE);
    while (Hu3DMotionEndCheck(arg0->unk_62[arg0->unk_08]) == 0) {
        var_r27 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r27) {
            return;
        }
    }

    if (arg0->unk_08 == 4) {
        fn_1_189C(arg0, 0, HU3D_MOTATTR_LOOP);
    }
    else {
        fn_1_1778(arg0, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    }
    lbl_1_bss_CC[arg0->unk_00].unk_04 = 0;
}

void fn_1_2F18(M459DllBssCCStruct *arg0)
{
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    for (var_r30 = 0; var_r30 < (arg0->unk_00 * 8); var_r30++) {
        var_r29 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r29) {
            return;
        }
    }
    while (TRUE) {
        arg0->unk_50 = -8.0f;
        fn_1_338C(arg0, 0.2f);
        var_r28 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 == var_r28) {
            if (arg0->unk_0C.x < -600.0f) {
                lbl_1_bss_CC[arg0->unk_00].unk_04 = 0;
                break;
            }
        }
        else {
            break;
        }
    }
}

void fn_1_3004(M459DllBssCCStruct *arg0)
{
    float var_f31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    arg0->unk_0C.x = 600.0f;
    arg0->unk_0C.z = 0.0f;
    arg0->unk_0C.y = 0.0f;
    var_f31 = -260.0f + (130.0f * arg0->unk_00);
    for (var_r30 = 0; var_r30 < (arg0->unk_00 * 0x1E); var_r30++) {
        var_r29 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r29) {
            return;
        }
    }
loop_1:
    arg0->unk_50 = -8.0f;
    fn_1_338C(arg0, 0.2f);
    if (arg0->unk_0C.x < var_f31) {
        arg0->unk_0C.x = var_f31;
    }
    else {
        var_r28 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r28) {
            return;
        }
        goto loop_1;
    }
    fn_1_1778(arg0, 1, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    for (var_r30 = 0; var_r30 < 0xF; var_r30++) {
        arg0->unk_58 = 0.0001f;
        fn_1_338C(arg0, 0.2f);
        var_r27 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r27) {
            return;
        }
    }
    arg0->unk_1C = 0.0f;
    fn_1_1778(arg0, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    lbl_1_bss_CC[arg0->unk_00].unk_04 = 0;
}

void fn_1_338C(M459DllBssCCStruct *arg0, float arg8)
{
    s16 var_r30;

    var_r30 = 0;
    arg0->unk_5C = sqrtf((arg0->unk_50 * arg0->unk_50) + (arg0->unk_58 * arg0->unk_58));
    if (0.0001f <= arg0->unk_5C) {
        if (10.0f <= arg0->unk_5C) {
            arg0->unk_50 /= arg0->unk_5C;
            arg0->unk_58 /= arg0->unk_5C;
            arg0->unk_5C = 10.0f;
            arg0->unk_50 = 10.0f * arg0->unk_50;
            arg0->unk_58 = 10.0f * arg0->unk_58;
        }
        arg0->unk_1C = fn_1_4210(arg0->unk_1C, atan2d(arg0->unk_50, arg0->unk_58), arg8);
        if (8.0f <= arg0->unk_5C) {
            var_r30 = 2;
        }
        else {
            var_r30 = 1;
        }
    }
    arg0->unk_0C.x += arg0->unk_50;
    arg0->unk_0C.z += arg0->unk_58;
    if (arg0->unk_60 != var_r30) {
        fn_1_1778(arg0, var_r30, 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
    }
    arg0->unk_50 = 0.0f;
    arg0->unk_58 = 0.0f;
}

void fn_1_3700(M459DllBssCCStruct *arg0)
{
    s32 var_r30;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;

    if (lbl_1_bss_C > arg0->unk_00) {
        for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
            arg0->unk_58 = 0.0001f;
            fn_1_338C(arg0, 0.4f);
            var_r25 = arg0->unk_04;
            fn_1_4160(arg0);
            HuPrcVSleep();
            if (arg0->unk_04 != var_r25) {
                return;
            }
        }
    }
    else {
        for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
            arg0->unk_58 = 0.0001f;
            fn_1_338C(arg0, 0.4f);
            var_r24 = arg0->unk_04;
            fn_1_4160(arg0);
            HuPrcVSleep();
            if (arg0->unk_04 != var_r24) {
                return;
            }
        }
    }
    fn_1_1778(arg0, 4, 0.0f, 8.0f, HU3D_ATTR_NONE);
    while (Hu3DMotionEndCheck(arg0->unk_62[arg0->unk_08]) == 0) {
        var_r23 = arg0->unk_04;
        fn_1_4160(arg0);
        HuPrcVSleep();
        if (arg0->unk_04 != var_r23) {
            return;
        }
    }
    if (arg0->unk_08 == 4) {
        fn_1_189C(arg0, 0, HU3D_MOTATTR_LOOP);
    }
    else {
        fn_1_1778(arg0, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    }
    lbl_1_bss_CC[arg0->unk_00].unk_04 = 0;
}

void fn_1_4160(M459DllBssCCStruct *arg0)
{
    Hu3DModelPosSet(arg0->unk_62[arg0->unk_08], arg0->unk_0C.x, arg0->unk_0C.y, arg0->unk_0C.z);
    Hu3DModelPosSet(arg0->unk_62[arg0->unk_08 + 5], arg0->unk_0C.x, arg0->unk_0C.y, arg0->unk_0C.z);
    Hu3DModelRotSet(arg0->unk_62[arg0->unk_08], arg0->unk_18, arg0->unk_1C, arg0->unk_20);
    Hu3DModelRotSet(arg0->unk_62[arg0->unk_08 + 5], arg0->unk_18, arg0->unk_1C, arg0->unk_20);
}

float fn_1_4210(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;

    var_f31 = fmod(arg9 - arg8, 360.0);
    if (0.0f > var_f31) {
        var_f31 += 360.0f;
    }
    if (180.0f < var_f31) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg8 + (var_f31 * argA), 360.0);
    if (0.0f > var_f30) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

void fn_1_4314(s32 arg0, u32 arg1)
{
    M459DllBssCCStruct *var_r31;
    s32 var_r30;

    var_r31 = &lbl_1_bss_CC[arg0];
    var_r31->unk_08 = arg1;
    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        if (var_r30 != var_r31->unk_08) {
            Hu3DModelAttrSet(var_r31->unk_62[var_r30], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(var_r31->unk_62[var_r30 + 5], HU3D_ATTR_DISPOFF);
        }
        Hu3DModelPosSet(var_r31->unk_62[var_r30], 0.0f, 0.0f, -1000.0f);
        Hu3DModelPosSet(var_r31->unk_62[var_r30 + 5], 0.0f, 0.0f, -1000.0f);
    }
    Hu3DModelAttrReset(var_r31->unk_62[var_r31->unk_08], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(var_r31->unk_62[var_r31->unk_08 + 5], HU3D_ATTR_DISPOFF);
    fn_1_1778(var_r31, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
}

void fn_1_4530(void)
{
    s32 var_r31;

    HuPrcSleep(0x3C);
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_CC[var_r31].unk_04 = 1;
    }
    while (lbl_1_bss_CC->unk_04 != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_0 = HuAudSeqPlay(0x43);
    fn_1_4F8C(0);
    while (fn_1_4FAC() != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_698[0x12] = NULL;
    HuPrcEnd();
}

void fn_1_45EC(void)
{
    s32 var_r31;
    s32 var_r30;
    s16 var_r29;
    s32 var_r28;

    HuAudSeqFadeOut(lbl_1_bss_0, 0x64);
    HuAudFXPlay(0x814);
    var_r28 = fn_1_5300();
    if (fn_1_52F0() > var_r28) {
        fn_1_4F8C(1);
        while (fn_1_4FAC() != 0) {
            HuPrcVSleep();
        }
        var_r30 = fn_1_52F0();
        GWMGRecordSet(0xB, var_r30);
        var_r29 = MGSeqCreate(0xE, var_r30);
        HuAudFXPlay(0x26);
        fn_1_5310();
        while (MGSeqStatGet(var_r29) != 0) {
            HuPrcVSleep();
        }
    }
    else {
        fn_1_4F8C(1);
        while (fn_1_4FAC() != 0) {
            HuPrcVSleep();
        }
    }
    HuAudSStreamPlay(3);
    if (fn_1_52F0() >= 0x63) {
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            lbl_1_bss_CC[var_r31].unk_04 = 0xD;
        }
        while (lbl_1_bss_CC[var_r31].unk_04 == 0xD) {
            HuPrcVSleep();
        }
    }
    HuPrcSleep(0xD2);
    lbl_1_bss_698[0x12] = NULL;
    HuPrcEnd();
}

void fn_1_4764(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_CC[var_r31].unk_04 = 1;
    }
    while (lbl_1_bss_CC->unk_04 != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_698[0x12] = NULL;
    HuPrcEnd();
}

void fn_1_47E4(void)
{
    HuPrcSleep(0x1E);
    HuAudFXPlay(0x30D);
    lbl_1_bss_18.unk_00 = 3;
    while (lbl_1_bss_18.unk_00 != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_698[0x12] = NULL;
    HuPrcEnd();
}

void fn_1_4850(void)
{
    HuAudFXPlay(9);
    lbl_1_bss_CC[lbl_1_bss_14].unk_04 = 9;
    while (lbl_1_bss_CC[lbl_1_bss_14].unk_04 == 9) {
        HuPrcVSleep();
    }
    HuPrcSleep(8);
    lbl_1_bss_698[0x12] = NULL;
    HuPrcEnd();
}

void fn_1_48E4(void)
{
    s32 var_r31;

    lbl_1_bss_CC[lbl_1_bss_14].unk_04 = 7;
    HuPrcSleep(0x1E);
    lbl_1_bss_CC[lbl_1_bss_10].unk_04 = 8;
    HuPrcSleep(0x50);
    lbl_1_bss_C = lbl_1_bss_10;
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        if ((var_r31 != lbl_1_bss_10) && (var_r31 != lbl_1_bss_14)) {
            lbl_1_bss_CC[var_r31].unk_04 = 6;
        }
    }
    while (lbl_1_bss_CC[lbl_1_bss_14].unk_04 == 7) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);
    lbl_1_bss_CC[lbl_1_bss_14].unk_04 = 5;
    while (lbl_1_bss_CC[lbl_1_bss_14].unk_04 == 5) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x3C);
    lbl_1_bss_698[0x12] = NULL;
    HuPrcEnd();
}

void fn_1_4A74(void)
{
    s32 var_r31;

    lbl_1_bss_CC[lbl_1_bss_10].unk_04 = 8;
    HuPrcSleep(0x6E);
    lbl_1_bss_C = lbl_1_bss_10;
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        if (var_r31 != lbl_1_bss_10) {
            lbl_1_bss_CC[var_r31].unk_04 = 5;
        }
    }
    while (lbl_1_bss_CC[lbl_1_bss_10].unk_04 != 8) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x3C);
    lbl_1_bss_698[0x12] = NULL;
    HuPrcEnd();
}

void fn_1_4B68(void)
{
    s32 var_r31;
    s32 var_r30;

    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_CC[var_r31].unk_04 = 0xB;
    }
    while (TRUE) {
        var_r30 = 0;
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            if (lbl_1_bss_CC[var_r31].unk_04 != 0) {
                var_r30++;
            }
        }
        if (var_r30 != 0) {
            HuPrcVSleep();
        }
        else {
            break;
        }
    }
    lbl_1_bss_698[0x12] = NULL;
    HuPrcEnd();
}

void fn_1_4C1C(void)
{
    s32 var_r31;
    s32 var_r30;

    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        lbl_1_bss_CC[var_r31].unk_04 = 0xA;
    }
    while (TRUE) {
        var_r30 = 0;
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            if (lbl_1_bss_CC[var_r31].unk_04 != 0) {
                var_r30++;
            }
        }
        if (var_r30 != 0) {
            HuPrcVSleep();
        }
        else {
            break;
        }
    }
    lbl_1_bss_698[0x12] = NULL;
    HuPrcEnd();
}

void fn_1_4CD0(void)
{
    M459DllBss70Struct *var_r31;

    var_r31 = &lbl_1_bss_70;
    var_r31->unk_00 = 0;
    var_r31->unk_08 = 0;
    var_r31->unk_04 = -1;
    while (TRUE) {
        switch (var_r31->unk_00) {
            case 4:
            case 0:
                break;
            case 1:
                if (var_r31->unk_04 == -1) {
                    var_r31->unk_04 = MGSeqCreate(1, var_r31->unk_08 / 60, -1, -1);
                }
                var_r31->unk_00 = 2;
                break;
            case 3:
                if (var_r31->unk_04 != -1) {
                    MGSeqParamSet(var_r31->unk_04, 2, -1);
                    var_r31->unk_04 = -1;
                }
                var_r31->unk_00 = 0;
                break;
            case 2:
                if ((var_r31->unk_04 != -1) && (var_r31->unk_08 > 0)) {
                    if (--var_r31->unk_08 <= 0) {
                        var_r31->unk_08 = 0;
                        var_r31->unk_00 = 3;
                    }
                    if ((var_r31->unk_08 % 60) == 0) {
                        MGSeqParamSet(var_r31->unk_04, 1, var_r31->unk_08 / 60);
                    }
                }
                break;
        }
        HuPrcVSleep();
    }
}

s32 fn_1_4E54(void)
{
    return lbl_1_bss_70.unk_08;
}

void fn_1_4E64(s32 arg0)
{
    lbl_1_bss_70.unk_08 = arg0;
    lbl_1_bss_70.unk_00 = 1;
}

void fn_1_4E84(void)
{
    lbl_1_bss_70.unk_00 = 4;
}

void fn_1_4E98(void)
{
    lbl_1_bss_70.unk_00 = 3;
}

void fn_1_4EAC(void)
{
    M459DllBss64Struct *var_r31;

    var_r31 = &lbl_1_bss_64;
    var_r31->unk_00 = 0;
    var_r31->unk_08 = -1;
    while (TRUE) {
        switch (var_r31->unk_00) {
            case 0:
                break;
            case 2:
                if (var_r31->unk_08 == -1) {
                    switch (var_r31->unk_04) {
                        case 0:
                            var_r31->unk_08 = MGSeqCreate(3, 0);
                            break;
                        case 1:
                            var_r31->unk_08 = MGSeqCreate(3, 1);
                            break;
                    }
                }
                var_r31->unk_00 = 1;
                break;
            case 1:
                if (MGSeqStatGet(var_r31->unk_08) == 0) {
                    MGSeqKill(var_r31->unk_08);
                    var_r31->unk_08 = -1;
                    var_r31->unk_00 = 0;
                }
                break;
        }
        HuPrcVSleep();
    }
}

void fn_1_4F8C(s32 arg0)
{
    lbl_1_bss_64.unk_00 = 2;
    lbl_1_bss_64.unk_04 = arg0;
}

s32 fn_1_4FAC(void)
{
    return lbl_1_bss_64.unk_00 != 0;
}

void fn_1_4FC8(void)
{
    float var_f31;
    M459DllBss4CStruct *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r31 = &lbl_1_bss_4C;
    var_r31->unk_0C = 0;
    var_r31->unk_10 = (s16)GWMGRecordGet(0xB);
    var_r31->unk_14 = 0;
    espPosSet(var_r31->unk_00[5], 508.0f, 64.0f);
    espPosSet(var_r31->unk_00[4], 488.0f, 56.0f);
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        espPosSet(var_r31->unk_00[var_r30 + 2], (var_r30 * 0x10) + 0x1FC, 57.0f);
        espPosSet(var_r31->unk_00[var_r30], (var_r30 * 0x10) + 0x1FC, 75.0f);
    }
    espTPLvlSet(var_r31->unk_00[5], 0.5f);
    espPriSet(var_r31->unk_00[5], 0x65);
    espPriSet(var_r31->unk_00[4], 0x64);
    espPriSet(var_r31->unk_00[2], 0x64);
    espPriSet(var_r31->unk_00[3], 0x64);
    espPriSet(var_r31->unk_00[0], 0x64);
    espPriSet(var_r31->unk_00[1], 0x64);
    var_f31 = 1.0f;
    while (TRUE) {
        if (var_r31->unk_14 != 0) {
            if (var_r28 != 0) {
                var_f31 += 0.02;
                var_f31 = var_f31;
                if (var_f31 >= 1.2f) {
                    var_f31 = 1.2f;
                    var_r28 = 0;
                }
            }
            else {
                var_f31 -= 0.02;
                var_f31 = var_f31;
                if (var_f31 <= 1.0f) {
                    var_f31 = 1.0f;
                    var_r28 = 1;
                }
            }
            espScaleSet(var_r31->unk_00[4], var_f31, var_f31);
            for (var_r30 = 0; var_r30 < 2; var_r30++) {
                espScaleSet(var_r31->unk_00[var_r30 + 2], var_f31, var_f31);
            }
        }
        var_r29 = var_r31->unk_0C;
        espBankSet(var_r31->unk_00[0], var_r29 / 10);
        var_r29 = var_r29 % 10;
        espBankSet(var_r31->unk_00[1], var_r29);
        var_r29 = var_r31->unk_10;
        espBankSet(var_r31->unk_00[2], var_r29 / 10);
        var_r29 = var_r29 % 10;
        espBankSet(var_r31->unk_00[3], var_r29);
        HuPrcVSleep();
    }
}

void fn_1_52D8(s32 arg0)
{
    lbl_1_bss_4C.unk_0C += arg0;
}

s32 fn_1_52F0(void)
{
    return lbl_1_bss_4C.unk_0C;
}

s32 fn_1_5300(void)
{
    return lbl_1_bss_4C.unk_10;
}

s32 fn_1_5310(void)
{
    if (lbl_1_bss_4C.unk_10 < lbl_1_bss_4C.unk_0C) {
        lbl_1_bss_4C.unk_10 = lbl_1_bss_4C.unk_0C;
        lbl_1_bss_4C.unk_14 = 1;
    }
}

M459DllData70Struct lbl_1_data_70 = { { 0.0f, 300.0f, 0.0f }, { 0.0f, -300.0f, -600.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } };

void fn_1_535C(void)
{
    LightData *sp8;
    s16 *var_r31;

    var_r31 = lbl_1_bss_48;
    Hu3DLighInit();
    var_r31[1] = Hu3DGLightCreateV(&lbl_1_data_70.unk_00, &lbl_1_data_70.unk_0C, &lbl_1_data_70.unk_18);
    Hu3DGLightInfinitytSet(var_r31[1]);
    sp8 = &Hu3DGlobalLight[var_r31[1]];
    {
        Vec sp24 = { 0.0f, 3000.0f, 1.0f };
        Vec sp18 = { 0.0f, 1.0f, 0.0f };
        Vec spC = { 0.0f, 0.0f, 0.0f };
        Hu3DShadowCreate(30.0f, 20.0f, 5000.0f);
        Hu3DShadowTPLvlSet(0.45f);
        Hu3DShadowPosSet(&sp24, &sp18, &spC);
    }
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DModelAttrSet(var_r31[0], HU3D_MOTATTR_LOOP);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static const s32 lbl_1_rodata_458[6][3];

void fn_1_5490(void)
{
    M459DllBss18Struct *var_r31;

    var_r31 = &lbl_1_bss_18;
    var_r31->unk_00 = 0;
    var_r31->unk_24[0] = GWPlayerCfg->pad_idx;
    var_r31->unk_24[1] = GWPlayerCfg->character;
    var_r31->unk_28 = GWPlayerCfg->iscom;
    var_r31->unk_2C = 0x14;
    lbl_1_bss_14 = 0;
    lbl_1_bss_2 = var_r31->unk_24[0];
    while (TRUE) {
        switch (var_r31->unk_00) {
            case 0:
                fn_1_556C(var_r31);
                continue;
            case 1:
                fn_1_55B0(var_r31);
                continue;
            case 2:
                break;
            case 3:
                fn_1_5A78(var_r31);
                continue;
            default:
                continue;
        }
        fn_1_5E3C(var_r31);
    }
}

void fn_1_556C(M459DllBss18Struct *arg0)
{
    s32 var_r30;

    do {
        var_r30 = arg0->unk_00;
        HuPrcVSleep();
    } while (arg0->unk_00 == var_r30);
}

void fn_1_55B0(M459DllBss18Struct *var_r31)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;

    u8 var_r30;
    s16 var_r29;
    s32 var_r28;
    u16 var_r27;
    s32 var_r26;
    M459DllBssCCStruct *var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;

    lbl_1_bss_14 = 0;
    var_r28 = -1;
    var_r29 = var_r31->unk_04[var_r31->unk_24[1]];
    espDispOn(var_r29);
    var_r23 = 0;
    while(1) {
        var_r30 = 0;
        var_r27 = 0;
        if (var_r31->unk_28 != 0) {
            if (var_r31->unk_2C <= 0) {
                var_r20 = lbl_1_bss_70.unk_08;
                if ((var_r20 > 0xB4) && (var_r23 == 0)) {
                    var_r24 = frandmod(0xA);
                    if (var_r24 >= 5) {
                        var_r30 |= 1;
                    }
                    else if (var_r24 > 1) {
                        var_r30 |= 2;
                    }
                    else {
                        var_r23 = 1;
                    }
                }
                else {
                    if (lbl_1_bss_14 > lbl_1_bss_10) {
                        var_r30 |= 1;
                    }
                    else if (lbl_1_bss_14 < lbl_1_bss_10) {
                        var_r30 |= 2;
                    }
                    if (lbl_1_bss_14 == lbl_1_bss_10) {
                        var_r27 |= 0x100;
                    }
                }
                var_r31->unk_2C = 0x1E;
            }
            else {
                var_r31->unk_2C--;
            }
        }
        else {
            var_r30 = HuPadDStkRep[var_r31->unk_24[0]];
            var_r27 = HuPadBtnDown[var_r31->unk_24[0]];
        }
        if (var_r28 != -1) {
            if ((var_r27 & 0x100) != 0) {
                HuAudFXPlay(2);
                break;
            }
            else {
                if ((var_r30 & 1) != 0) {
                    if (--lbl_1_bss_14 < 0) {
                        lbl_1_bss_14 = 4;
                    }
                    HuAudFXPlay(0);
                }
                else if ((var_r30 & 2) != 0) {
                    if (++lbl_1_bss_14 >= 5) {
                        lbl_1_bss_14 = 0;
                    }
                    HuAudFXPlay(0);
                }
                goto block_30;
            }
        }
        else {
        block_30:
            if (var_r28 != lbl_1_bss_14) {
                var_r25 = &lbl_1_bss_CC[lbl_1_bss_14];
                sp14 = sp20;
                sp20 = var_r25->unk_0C;
                sp20.y = 40.0f;
                espPriSet(var_r29, 0x32);
                if (var_r28 == -1) {
                    sp14 = sp20;
                }
                else {
                    lbl_1_bss_7C[var_r28].unk_04 = 3;
                }
                for (var_r26 = 0; var_r26 <= 4; var_r26++) {
                    var_f31 = sind((90.0f * (0.25f * var_r26)));
                    var_f31 *= var_f31 * var_f31;
                    sp8.x = sp14.x + (var_f31 * (sp20.x - sp14.x));
                    sp8.y = sp14.y + (var_f31 * (sp20.y - sp14.y));
                    sp8.z = sp14.z + (var_f31 * (sp20.z - sp14.z));
                    Hu3D3Dto2D(&sp8, 1, &sp8);
                    espPosSet(var_r29, sp8.x, sp8.y);
                    var_r22 = var_r31->unk_00;
                    HuPrcVSleep();
                    if (var_r31->unk_00 != var_r22) {
                        return;
                    }
                }
                espPosSet(var_r29, sp8.x, sp8.y);
                lbl_1_bss_7C[lbl_1_bss_14].unk_04 = 1;
            }
            var_r28 = lbl_1_bss_14;
            var_r21 = var_r31->unk_00;
            HuPrcVSleep();
            if (var_r31->unk_00 != var_r21) {
                return;
            }
        }
    }
    lbl_1_bss_7C[lbl_1_bss_14].unk_04 = 3;
    espDispOff(var_r29);
    lbl_1_bss_18.unk_00 = 0;
}

void fn_1_5A78(M459DllBss18Struct *arg0)
{
    Vec sp8;
    float var_f31;

    s32 var_r31;
    s16 var_r29;
    M459DllBssCCStruct *var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    var_r28 = &lbl_1_bss_CC[lbl_1_bss_14];
    lbl_1_bss_CC[lbl_1_bss_14].unk_04 = 4;
    for (var_r31 = 0; var_r31 < 0x3C; var_r31++) {
        var_r27 = arg0->unk_00;
        HuPrcVSleep();
        if (arg0->unk_00 != var_r27) {
            return;
        }
    }
    var_r29 = arg0->unk_14[arg0->unk_24[1]];
    Hu3DModelAttrReset(var_r29, HU3D_ATTR_DISPOFF);
    Hu3DModelTPLvlSet(var_r29, 1.0f);
    Hu3DModelScaleSet(var_r29, 1.0f, 1.0f, 1.0f);
    sp8 = var_r28->unk_0C;
    for (var_r31 = 0; var_r31 < 0x3C; var_r31++) {
        var_f31 = sind((1.5000001f * var_r31));
        sp8.y = 170.0f + (350.0f - (350.0f * var_f31));
        Hu3DModelPosSet(var_r29, sp8.x, sp8.y, sp8.z);
        var_r26 = arg0->unk_00;
        HuPrcVSleep();
        if (arg0->unk_00 != var_r26) {
            return;
        }
    }
    for (var_r31 = 0; var_r31 < 0x14; var_r31++) {
        var_f31 = sind((4.5f * var_r31));
        var_f31 = 1.0f - var_f31;
        Hu3DModelScaleSet(var_r29, var_f31, var_f31, var_f31);
        Hu3DModelTPLvlSet(var_r29, var_f31);
        Hu3DModelRotSet(var_r29, 0.0f, 540.0f * var_f31, 0.0f);
        sp8.y = 170.0f - (2.0f * var_r31);
        Hu3DModelPosSet(var_r29, sp8.x, sp8.y, sp8.z);
        var_r25 = arg0->unk_00;
        HuPrcVSleep();
        if (arg0->unk_00 != var_r25) {
            return;
        }
    }
    Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);
    lbl_1_bss_C = lbl_1_bss_14;
    for (var_r31 = 0; var_r31 < 5; var_r31++) {
        if (var_r31 != lbl_1_bss_14) {
            lbl_1_bss_CC[var_r31].unk_04 = 5;
        }
    }
    for (var_r31 = 0; var_r31 < 0x78; var_r31++) {
        var_r24 = arg0->unk_00;
        HuPrcVSleep();
        if (arg0->unk_00 != var_r24) {
            return;
        }
    }
    lbl_1_bss_18.unk_00 = 0;
}

void fn_1_5E3C(M459DllBss18Struct *arg0)
{
    lbl_1_bss_7C[lbl_1_bss_14].unk_04 = 3;
    espDispOff(arg0->unk_04[arg0->unk_24[1]]);
    lbl_1_bss_18.unk_00 = 0;
}

void fn_1_5EAC(void)
{
    M459DllBss7CStruct *var_r31;
    s32 var_r30;

    var_r30 = (s32)HuPrcCurrentGet()->user_data;
    var_r31 = &lbl_1_bss_7C[var_r30];
    var_r31->unk_00 = var_r30;
    var_r31->unk_04 = 0;
    while (TRUE) {
        switch (var_r31->unk_04) {
            case 0:
                fn_1_5F40(var_r31);
                break;
            case 1:
                fn_1_5F84(var_r31);
                break;
            case 2:
                fn_1_6198(var_r31);
                break;
            case 3:
                fn_1_6458(var_r31);
                break;
        }
        
    }
}

void fn_1_5F40(M459DllBss7CStruct *arg0)
{
    s32 var_r30;

    do {
        var_r30 = arg0->unk_04;
        HuPrcVSleep();
    } while (arg0->unk_04 == var_r30);
}

void fn_1_5F84(M459DllBss7CStruct *arg0)
{
    Vec sp8;
    float var_f31;

    M459DllBssCCStruct *var_r27;
    s16 var_r30;
    s16 var_r29;
    s32 var_r28;
    s32 var_r26;

    var_r29 = arg0->unk_0C[1];
    var_r30 = arg0->unk_0C[0];
    var_r27 = &lbl_1_bss_CC[arg0->unk_00];
    sp8 = var_r27->unk_0C;
    sp8.y = 200.0f;
    Hu3D3Dto2D(&sp8, 1, &sp8);
    espPosSet(var_r29, sp8.x, sp8.y);
    espPosSet(var_r30, sp8.x, sp8.y);
    espScaleSet(var_r30, 0.0f, 0.0f);
    espPriSet(var_r29, 0x32);
    espPriSet(var_r30, 0x31);
    if (lbl_1_bss_8 == 0) {
        espScaleSet(var_r29, 1.0f, 1.0f);
        espScaleSet(var_r30, 0.5f, 0.5f);
        espDispOn(var_r29);
        espDispOn(var_r30);
    }
    var_f31 = 0.0f;
    for (var_r28 = 0; var_r28 < 0xA; var_r28++) {
        espTPLvlSet(var_r29, var_f31);
        espTPLvlSet(var_r30, var_f31);
        var_f31 = 0.08f * var_r28;
        var_r26 = arg0->unk_04;
        HuPrcVSleep();
        if (arg0->unk_04 != var_r26) {
            return;
        }
    }
    espTPLvlSet(var_r29, 0.8f);
    espTPLvlSet(var_r30, 0.8f);
    lbl_1_bss_7C[arg0->unk_00].unk_04 = 2;
}

static const s32 lbl_1_rodata_458[6][3] = {
    { 0, 0xF, 0xF },
    { 1, 0xA, 0xA },
    { 1, 0x14, 5 },
    { 2, 0x14, 0xA },
    { 2, 5, 0xA },
    { 0x3F000000, 0x3F000000, 0x3F000000 },
};

void fn_1_6198(M459DllBss7CStruct *var_r31)
{
    float var_f31;
    float var_f30;
    s32 var_r30;
    s32 var_r29;
    s16 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    var_r28 = var_r31->unk_0C[0];
    var_r27 = lbl_1_rodata_458[var_r31->unk_08][0];
    var_r29 = lbl_1_rodata_458[var_r31->unk_08][1];
    var_r26 = lbl_1_rodata_458[var_r31->unk_08][2];
    while (TRUE) {
        if (lbl_1_bss_8 != 0) {
            switch (var_r27) {
                case 0:
                    omVibrate(0, var_r29, 6, 6);
                    break;
                case 1:
                    omVibrate(0, var_r29, 4, 2);
                    break;
                case 2:
                    omVibrate(0, var_r29, 0xC, 0);
                    break;
            }
        }
        switch (var_r27) {
            case 0:
                var_f30 = 0.4f;
                break;
            case 1:
                var_f30 = 0.55f;
                break;
            case 2:
                var_f30 = 0.7f;
                break;
        }
        for (var_r30 = 0; var_r30 < var_r29; var_r30++) {
            var_f31 = var_r30 * (var_f30 * (1.0f / var_r29));
            var_f31 += 0.5f;
            espScaleSet(var_r28, var_f31, var_f31);
            var_r25 = var_r31->unk_04;
            HuPrcVSleep();
            if (var_r31->unk_04 != var_r25) {
                return;
            }
        }

        for (var_r30 = 0; var_r30 < var_r26; var_r30++) {
            var_f31 = var_f30 - (var_r30 * (var_f30 * (1.0f / var_r26)));
            var_f31 += 0.5f;
            espScaleSet(var_r28, var_f31, var_f31);
            var_r24 = var_r31->unk_04;
            HuPrcVSleep();
            if (var_r31->unk_04 != var_r24) {
                return;
            }
        }
    }
}

void fn_1_6458(M459DllBss7CStruct *arg0)
{
    float var_f31;
    s32 var_r30;
    s16 var_r29;
    s16 var_r28;
    s32 var_r27;

    var_r29 = arg0->unk_0C[1];
    var_r28 = arg0->unk_0C[0];
    if (lbl_1_bss_8 != 0) {
        HuPadRumbleStop(lbl_1_bss_2);
    }
    var_f31 = 0.8f;
    for (var_r30 = 0; var_r30 < 0xA; var_r30++) {
        espTPLvlSet(var_r29, var_f31);
        espTPLvlSet(var_r28, var_f31);
        var_f31 = 0.8f - (0.08f * var_r30);
        var_r27 = arg0->unk_04;
        HuPrcVSleep();
        if (arg0->unk_04 != var_r27) {
            return;
        }
    }
    espDispOff(var_r29);
    espDispOff(var_r28);
    lbl_1_bss_7C[arg0->unk_00].unk_04 = 0;
}
