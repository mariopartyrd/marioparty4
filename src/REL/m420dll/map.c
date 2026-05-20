#include "ext_math.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "REL/m420dll.h"

#ifndef __MWERKS__
#include "game/audio.h"
#endif

typedef struct M420DllUnkMapStruct2 {
    /* 0x00 */ struct {
        s8 unk_00_field0 : 1;
        s8 unk_00_field1 : 1;
        s8 unk_00_field2 : 1;
        s8 unk_00_field3 : 1;
        s8 unk_00_field4 : 1;
        s8 unk_00_field5 : 1;
        s8 unk_00_field6 : 1;
        s8 unk_00_field7 : 1;
    };
    /* 0x04 */ s16 unk_02;
    /* 0x04 */ Vec unk_04;
    /* 0x10 */ Vec unk_10;
    /* 0x1C */ Vec unk_1C;
    /* 0x28 */ Vec unk_28;
    /* 0x34 */ Vec unk_34;
    /* 0x40 */ Vec unk_40;
    /* 0x4C */ Vec unk_4C;
    /* 0x58 */ Vec unk_58;
    /* 0x64 */ Vec unk_64;
    /* 0x70 */ float unk_70;
    /* 0x74 */ float unk_74;
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ float unk_7C;
    /* 0x80 */ float unk_80;
    /* 0x84 */ s32 unk_84;
    /* 0x88 */ float unk_88;
    /* 0x8C */ float unk_8C;
    /* 0x90 */ s32 unk_90;
} M420DllUnkMapStruct2; /* size = 0x94 */

typedef struct M420DllUnkMapStruct {
    /* 0x00 */ M420DllUnkMapStruct2 *unk_00;
    /* 0x04 */ M420DllUnkMapStruct2 *unk_04;
    /* 0x08 */ M420DllUnkMapStruct2 *unk_08;
    /* 0x0C */ M420DllUnkMapStruct2 *unk_0C;
    /* 0x10 */ M420DllUnkMapStruct2 *unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ char pad_18[4];
    /* 0x1C */ float unk_1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
} M420DllUnkMapStruct; /* size = 0x40 */

typedef struct M420DllUnkMapStruct3 {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ GXColor unk_18;
} M420DllUnkMapStruct3; /* size = 0x1C */

s32 fn_1_5A7C(s32 arg0);
void fn_1_6820(void);
void fn_1_6884(void);
void fn_1_6950(void);
void fn_1_6D0C(void);
void fn_1_6D5C(void);
void fn_1_6DF0(M420DllUnkMapStruct2 *arg0);
void fn_1_7230(M420DllUnkMapStruct2 *arg0, Vec *arg1, s32 arg2, s32 arg3);
void fn_1_7704(void);
void fn_1_7E24(void);
void fn_1_8240(void);
void fn_1_8414(void);

M420DllUnkMapStruct3 lbl_1_data_138 = {
    { 1000.0f, 2000.0f, 0.0f },
    { -0.5f, -0.5f, -0.5f },
    { 0xFF, 0xFF, 0xFF, 0xFF },
};
void (*lbl_1_data_154[4])() = { fn_1_7704, fn_1_7E24, fn_1_8240, fn_1_8414 };

static const s32 lbl_1_rodata_360[0x1B] = {
    DATA_MAKE_NUM(DATADIR_M420, 0x00),
    DATA_MAKE_NUM(DATADIR_M420, 0x14),
    DATA_MAKE_NUM(DATADIR_M420, 0x07),
    DATA_MAKE_NUM(DATADIR_M420, 0x08),
    DATA_MAKE_NUM(DATADIR_M420, 0x01),
    DATA_MAKE_NUM(DATADIR_M420, 0x02),
    DATA_MAKE_NUM(DATADIR_M420, 0x03),
    DATA_MAKE_NUM(DATADIR_M420, 0x04),
    DATA_MAKE_NUM(DATADIR_M420, 0x05),
    DATA_MAKE_NUM(DATADIR_M420, 0x06),
    DATA_MAKE_NUM(DATADIR_M420, 0x15),
    DATA_MAKE_NUM(DATADIR_M420, 0x16),
    DATA_MAKE_NUM(DATADIR_M420, 0x17),
    DATA_MAKE_NUM(DATADIR_M420, 0x09),
    DATA_MAKE_NUM(DATADIR_M420, 0x09),
    DATA_MAKE_NUM(DATADIR_M420, 0x0A),
    DATA_MAKE_NUM(DATADIR_M420, 0x0B),
    DATA_MAKE_NUM(DATADIR_M420, 0x0E),
    DATA_MAKE_NUM(DATADIR_M420, 0x0F),
    DATA_MAKE_NUM(DATADIR_M420, 0x0C),
    DATA_MAKE_NUM(DATADIR_M420, 0x0D),
    DATA_MAKE_NUM(DATADIR_M420, 0x12),
    DATA_MAKE_NUM(DATADIR_M420, 0x11),
    DATA_MAKE_NUM(DATADIR_M420, 0x10),
    DATA_MAKE_NUM(DATADIR_M420, 0x10),
    DATA_MAKE_NUM(DATADIR_M420, 0x13),
    DATA_MAKE_NUM(DATADIR_M420, 0x13),
};

Process *lbl_1_bss_A40;
Process *lbl_1_bss_A3C;
Process *lbl_1_bss_A2C[4];
s32 lbl_1_bss_A28;
s16 lbl_1_bss_9F0[0x1C];
s16 lbl_1_bss_9EE;
s16 lbl_1_bss_9EC;
M420DllUnkMapStruct2 lbl_1_bss_140[15];
struct M420DllUnkMapStruct lbl_1_bss_C0[2];
s32 lbl_1_bss_BC;
s32 lbl_1_bss_B8;
s32 lbl_1_bss_B4;
s32 lbl_1_bss_B0;

s32 fn_1_4964(void)
{
    M420DllUnkMapStruct2 *var_r31;
    M420DllUnkMapStruct *var_r30;
    s32 var_r29;

    lbl_1_bss_A40 = HuPrcChildCreate(fn_1_6820, 0x3E9, 0x4000, 0, lbl_1_bss_4);
    lbl_1_bss_A3C = HuPrcChildCreate(fn_1_6884, 0x3EA, 0x4000, 0, lbl_1_bss_4);
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        lbl_1_bss_A2C[var_r29] = NULL;
    }
    lbl_1_bss_A28 = 0;
    fn_1_6D5C();
    fn_1_6950();

    var_r31 = lbl_1_bss_140;
    var_r31->unk_02 = lbl_1_bss_9F0[1];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = 1000.0f;
    var_r31->unk_04.z = 0.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[1];
    var_r31->unk_02 = lbl_1_bss_9F0[0xA];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = 0.0f;
    var_r31->unk_04.z = 0.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[2];
    var_r31->unk_02 = lbl_1_bss_9F0[0xC];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = 0.0f;
    var_r31->unk_04.z = 0.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[3];
    var_r31->unk_02 = lbl_1_bss_9F0[0xB];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = 0.0f;
    var_r31->unk_04.z = 0.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[4];
    var_r31->unk_02 = lbl_1_bss_9F0[0xD];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = -220.0f;
    var_r31->unk_04.y = -60.0f;
    var_r31->unk_04.z = 170.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[9];
    var_r31->unk_02 = lbl_1_bss_9F0[0x17];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = -170.0f;
    var_r31->unk_04.y = 0.0f;
    var_r31->unk_04.z = 170.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[11];
    var_r31->unk_02 = lbl_1_bss_9F0[0x19];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = -160.0f;
    var_r31->unk_04.y = 0.0f;
    var_r31->unk_04.z = 220.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[6];
    var_r31->unk_02 = lbl_1_bss_9F0[0x11];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = -65.0f;
    var_r31->unk_04.z = 0.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[5];
    var_r31->unk_02 = lbl_1_bss_9F0[0xE];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 220.0f;
    var_r31->unk_04.y = -60.0f;
    var_r31->unk_04.z = 170.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[10];
    var_r31->unk_02 = lbl_1_bss_9F0[0x18];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 190.0f;
    var_r31->unk_04.y = 0.0f;
    var_r31->unk_04.z = 170.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[12];
    var_r31->unk_02 = lbl_1_bss_9F0[0x1A];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 185.0f;
    var_r31->unk_04.y = 0.0f;
    var_r31->unk_04.z = 220.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[7];
    var_r31->unk_02 = lbl_1_bss_9F0[0x12];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = -65.0f;
    var_r31->unk_04.z = 0.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[8];
    var_r31->unk_02 = lbl_1_bss_9F0[0x13];
    var_r31->unk_00_field3 = 1;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = 300.0f;
    var_r31->unk_04.z = 0.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[13];
    var_r31->unk_02 = lbl_1_bss_9F0[3];
    var_r31->unk_00_field3 = 0;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = 0.0f;
    var_r31->unk_04.z = 0.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    var_r31 = &lbl_1_bss_140[14];
    var_r31->unk_02 = lbl_1_bss_9F0[2];
    var_r31->unk_00_field3 = 0;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = 0.0f;
    var_r31->unk_04.z = 0.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    var_r31->unk_4C.x = 1.0f;
    var_r31->unk_4C.y = 1.0f;
    var_r31->unk_4C.z = 1.0f;
    fn_1_6DF0(var_r31);

    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        var_r30 = &lbl_1_bss_C0[var_r29];
        var_r30->unk_14 = var_r29;
        var_r30->unk_1C = 20.0f;
        var_r30->unk_20 = 0.0f;
        var_r30->unk_2C = 0.0f;
        var_r30->unk_24 = 0.2f;
        var_r30->unk_28 = 0.1f;
        var_r30->unk_38 = 0;
        var_r30->unk_3C = 0;
        var_r30->unk_30 = 1;
        var_r30->unk_00 = &lbl_1_bss_140[var_r29 + 13];
        var_r30->unk_04 = &lbl_1_bss_140[var_r29 + 4];
        var_r30->unk_08 = &lbl_1_bss_140[var_r29 + 6];
        var_r30->unk_0C = &lbl_1_bss_140[var_r29 + 9];
        var_r30->unk_10 = &lbl_1_bss_140[var_r29 + 11];
    }
    lbl_1_bss_B8 = 0;
    lbl_1_bss_B4 = 0;
    lbl_1_bss_B0 = 0;
    fn_1_6728();

    {
        Vec sp14 = { 0.0f, 0.0f, 0.0f };
        Vec sp8 = { 0.0f, 0.0f, -1.0f };
        HuAudFXListnerSetEX(&sp14, &sp8, 3000.0, 1000.0, 100.0, 300.0, 300.0);
        HuAudFXPlay(0x5F0);
    }
    return 1;
}

void fn_1_596C(void)
{
    Process *var_r30;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = lbl_1_bss_A2C[var_r31];
        if (var_r30) {
            HuPrcKill(var_r30);
        }
    }
    fn_1_6D0C();
    HuPrcKill(lbl_1_bss_A3C);
    HuPrcKill(lbl_1_bss_A40);
}

s32 fn_1_59F4(s32 arg0)
{
    if (fn_1_5A7C(arg0) != 0) {
        return 0;
    }
    lbl_1_bss_A2C[arg0] = HuPrcChildCreate(lbl_1_data_154[arg0], 0x3ED, 0x5000, 0, lbl_1_bss_4);
    return 1;
}

s32 fn_1_5A7C(s32 arg0)
{
    return lbl_1_bss_A2C[arg0] != NULL;
}

s32 fn_1_5AA8(s32 arg0, float arg1)
{
    M420DllUnkMapStruct *var_r31;
    s32 var_r29;
    s32 var_r30;

    var_r31 = &lbl_1_bss_C0[arg0];
    if ((var_r31->unk_1C += arg1) >= 200.0f) {
        var_r31->unk_1C = 200.0f;
    }
    var_r31->unk_38 = 1;
    var_r31->unk_30 = (s32)(200.0f - var_r31->unk_1C) / 10.0f;
    switch (arg0) {
        case 0:
            var_r29 = 3;
            var_r30 = 0x15;
            break;
        case 1:
            var_r29 = 2;
            var_r30 = 0x16;
            break;
    }
    if (var_r31->unk_1C >= 200.0f) {
        if (lbl_1_bss_B0 == 0) {
            var_r31->unk_3C = 1;
            Hu3DMotionTimeSet(lbl_1_bss_9F0[var_r30], 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_9F0[var_r30], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_9F0[var_r30], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrSet(lbl_1_bss_9F0[var_r29], HU3D_ATTR_DISPOFF);
        }
        return 1;
    }
    return 0;
}

void fn_1_5C8C(M420DllUnkMapStruct *arg0)
{
    Vec sp8;

    if (arg0->unk_38 != 0) {
        if (arg0->unk_30 > 0) {
            arg0->unk_30--;
        }
        if (arg0->unk_30 <= 0) {
            sp8 = arg0->unk_04->unk_04;
            sp8.y = -60.0f + arg0->unk_1C;
            fn_1_7230(arg0->unk_04, &sp8, 0x1E, 0);

            sp8 = arg0->unk_08->unk_04;
            sp8.y = -65.0f + arg0->unk_1C;
            fn_1_7230(arg0->unk_08, &sp8, 0x1E, 0);

            sp8 = arg0->unk_0C->unk_04;
            sp8.y = 40.0f + arg0->unk_1C;
            fn_1_7230(arg0->unk_0C, &sp8, 0x1E, 1);

            Hu3DMotionTimeSet(arg0->unk_0C->unk_02, 0.0f);
            Hu3DModelAttrReset(arg0->unk_0C->unk_02, HU3D_ATTR_DISPOFF);

            sp8 = arg0->unk_10->unk_04;
            sp8.y = -50.0f + arg0->unk_1C;
            fn_1_7230(arg0->unk_10, &sp8, 0x1E, 1);

            Hu3DMotionTimeSet(arg0->unk_10->unk_02, 0.0f);
            Hu3DModelAttrReset(arg0->unk_10->unk_02, HU3D_ATTR_DISPOFF);
            Hu3DMotionStartEndSet(arg0->unk_00->unk_02, 0.0f, 30.0f);
            Hu3DMotionTimeSet(arg0->unk_00->unk_02, 0.0f);
            Hu3DModelAttrReset(arg0->unk_00->unk_02, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(arg0->unk_00->unk_02, HU3D_MOTATTR_LOOP);
            arg0->unk_34 = 3;
            arg0->unk_38 = 0;
            arg0->unk_24 = 0.8f;
            arg0->unk_28 = 0.3f;
            arg0->unk_2C = 0.0f;
            if (arg0->unk_14 == 0) {
                HuAudFXPlay(0x5F7);
            }
            else {
                HuAudFXPlay(0x5F8);
            }
        }
    }
    if ((Hu3DMotionEndCheck(arg0->unk_00->unk_02) != 0) && (arg0->unk_34 > 0)) {
        if (--arg0->unk_34 > 0) {
            Hu3DMotionTimeSet(arg0->unk_00->unk_02, 0.0f);
        }
        else {
            Hu3DMotionStartEndSet(arg0->unk_00->unk_02, 0.0f, 1.0f);
            Hu3DMotionTimeSet(arg0->unk_00->unk_02, 0.0f);
            Hu3DModelAttrSet(arg0->unk_00->unk_02, HU3D_MOTATTR_PAUSE);
        }
    }
    if (arg0->unk_24 > 0.2f) {
        if ((arg0->unk_24 -= 0.005f) <= 0.2f) {
            arg0->unk_24 = 0.2f;
        }
    }
    arg0->unk_04->unk_28.y += arg0->unk_24;
    if (arg0->unk_28 > 0.05f) {
        if ((arg0->unk_28 -= 0.003f) <= 0.05f) {
            arg0->unk_28 = 0.05f;
        }
    }
    arg0->unk_04->unk_4C.y = 1.0 + (arg0->unk_28 * sind((90.0f * arg0->unk_2C)));
    arg0->unk_2C += 0.02f;
}

s32 fn_1_60F0(void)
{
    float var_f31;
    float var_f30;
    s32 var_r31;

    if (lbl_1_bss_BC >= 6) {
        return 1;
    }
    var_f31 = 5.0f * (6 - lbl_1_bss_BC);
    var_f30 = var_f31 - 5.0f;
    Hu3DMotionStartEndSet(lbl_1_bss_9F0[0xF], var_f30, var_f31);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[0xF], var_f31);
    Hu3DModelAttrReset(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_REV);
    lbl_1_bss_B8 = 5;
    lbl_1_bss_BC += 1;
    if (lbl_1_bss_BC == 6) {
        var_r31 = 1;
    }
    else {
        var_r31 = 0;
    }
    return var_r31;
}

void fn_1_6268(void)
{
    float var_f31 = 0.0f;
    float var_f30 = 30.0f;

    Hu3DMotionStartEndSet(lbl_1_bss_9F0[0xF], var_f31, var_f30);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[0xF], var_f31);
    Hu3DModelAttrReset(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_REV);
    Hu3DMotionStartEndSet(lbl_1_bss_9F0[0x10], var_f31, var_f30);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[0x10], var_f31);
    lbl_1_bss_BC = 0;
}

void fn_1_636C(void)
{
    float var_f31 = 0.0f;
    float var_f30 = 30.0f;

    Hu3DMotionStartEndSet(lbl_1_bss_9F0[0x14], var_f31, var_f30);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[0x14], var_f31);
}

void fn_1_63EC(void)
{
    float var_f31 = 5.0f * (6 - lbl_1_bss_BC);
    float var_f30 = 30.0f;

    Hu3DMotionStartEndSet(lbl_1_bss_9F0[0xF], var_f31, var_f30);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[0xF], var_f31);
    Hu3DModelAttrReset(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_REV);
    lbl_1_bss_BC = 0;
    lbl_1_bss_B8 = 0;
}

s32 fn_1_650C(void)
{
    s32 var_r31 = 0;

    if ((lbl_1_bss_BC == 6) && (lbl_1_bss_B8 == 0)) {
        var_r31 = 1;
    }
    return var_r31;
}

void fn_1_6554(void)
{
    Vec sp8;
    M420DllUnkMapStruct2 *var_r31;

    var_r31 = &lbl_1_bss_140[8];
    var_r31->unk_04.x = 480.0f;
    var_r31->unk_04.y = 800.0f;
    var_r31->unk_04.z = -314.0f;
    var_r31->unk_28.x = 0.0f;
    var_r31->unk_28.y = 0.0f;
    var_r31->unk_28.z = 0.0f;
    fn_1_6DF0(var_r31);
    sp8.x = 480.0f;
    sp8.y = 370.0f;
    sp8.z = -314.0f;
    Hu3DModelAttrReset(var_r31->unk_02, HU3D_ATTR_DISPOFF);
    fn_1_7230(var_r31, &sp8, 0x14, 0);
    Hu3DMotionTimeSet(fn_1_6660(), 0.0f);
    Hu3DModelAttrSet(fn_1_6660(), HU3D_MOTATTR_PAUSE);
}

s16 fn_1_6660(void)
{
    return lbl_1_bss_140[8].unk_02;
}

s32 fn_1_6670(void)
{
    M420DllUnkMapStruct2 *var_r31 = &lbl_1_bss_140[8];
    return var_r31->unk_00_field0;
}

void fn_1_669C(s32 arg0)
{
    M420DllUnkMapStruct2 *var_r31 = &lbl_1_bss_140[8];
    if (arg0 == 0) {
        var_r31->unk_04.x = 0.0f;
        var_r31->unk_04.y = 0.0f;
        var_r31->unk_04.z = 0.0f;
        fn_1_6DF0(var_r31);
    }
    var_r31->unk_00_field3 = arg0;
}

void fn_1_6728(void)
{
    M420DllUnkMapStruct2 *var_r31 = &lbl_1_bss_140[8];
    var_r31->unk_04.x = 0.0f;
    var_r31->unk_04.y = 1000.0f;
    var_r31->unk_04.z = 0.0f;
    fn_1_6DF0(var_r31);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0x13], HU3D_ATTR_DISPOFF);
}

s32 fn_1_67A4(s32 arg0)
{
    M420DllUnkMapStruct *var_r31 = &lbl_1_bss_C0[arg0];
    return var_r31->unk_1C >= 200.0f;
}

s32 fn_1_67E8(s32 arg0)
{
    M420DllUnkMapStruct *var_r31 = &lbl_1_bss_C0[arg0];
    return var_r31->unk_3C;
}

s32 fn_1_6810(void)
{
    return lbl_1_bss_B4;
}

void fn_1_6820(void)
{
    while (TRUE) {
        if (lbl_1_bss_B8 > 0) {
            if (--lbl_1_bss_B8 <= 0) {
                Hu3DModelAttrSet(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_PAUSE);
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_6884(void)
{
    s32 var_r31;
    M420DllUnkMapStruct *var_r30;
    M420DllUnkMapStruct *var_r29;

    while (TRUE) {
        for (var_r31 = 0; var_r31 < 0xF; var_r31++) {
            fn_1_6DF0(&lbl_1_bss_140[var_r31]);
        }
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            fn_1_5C8C(&lbl_1_bss_C0[var_r31]);
        }
        var_r30 = lbl_1_bss_C0;
        if ((var_r30->unk_1C >= 200.0f) || (var_r29 = &lbl_1_bss_C0[1], var_r29->unk_1C >= 200.0f)) {
            lbl_1_bss_B0 = 1;
        }
        HuPrcVSleep();
    }
}

void fn_1_6950(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x1B; var_r31++) {
        lbl_1_bss_9F0[var_r31] = Hu3DModelCreateFile(lbl_1_rodata_360[var_r31]);
    }
    Hu3DModelAttrSet(lbl_1_bss_9F0[1], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0xA], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_9F0[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_9F0[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(lbl_1_bss_9F0[0xF], -219.0f, 300.0f, -92.0f);
    Hu3DModelRotSet(lbl_1_bss_9F0[0xF], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_9F0[0x10], 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowMapSet(lbl_1_bss_9F0[0]);
    Hu3DModelShadowMapSet(lbl_1_bss_9F0[0xD]);
    Hu3DModelShadowMapSet(lbl_1_bss_9F0[0xE]);
    Hu3DModelShadowSet(lbl_1_bss_9F0[0xF]);
    Hu3DModelShadowSet(lbl_1_bss_9F0[1]);
    Hu3DModelShadowSet(lbl_1_bss_9F0[0xA]);
    Hu3DModelShadowSet(lbl_1_bss_9F0[0xB]);
    Hu3DModelShadowSet(lbl_1_bss_9F0[0x10]);
    Hu3DModelShadowSet(lbl_1_bss_9F0[0x14]);
    Hu3DModelShadowSet(lbl_1_bss_9F0[0x13]);
    Hu3DModelAttrSet(lbl_1_bss_9F0[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[6], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[8], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[9], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0xB], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0xC], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0x15], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0x16], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0x17], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0x18], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0x19], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0x1A], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_PAUSE);
    Hu3DMotionStartEndSet(lbl_1_bss_9F0[0xF], 30.0f, 30.0f);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[0xF], 30.0f);
    Hu3DModelAttrSet(lbl_1_bss_9F0[0xF], HU3D_MOTATTR_PAUSE);
    Hu3DModelHookSet(lbl_1_bss_9F0[1], "itemhook_sao", lbl_1_bss_9F0[0xA]);
}

void fn_1_6D0C(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x1B; var_r31++) {
        Hu3DModelKill(lbl_1_bss_9F0[var_r31]);
    }
}

void fn_1_6D5C(void)
{
    LightData *var_r31;

    Hu3DLighInit();
    lbl_1_bss_9EC = Hu3DGLightCreateV(&lbl_1_data_138.unk_00, &lbl_1_data_138.unk_0C, &lbl_1_data_138.unk_18);
    Hu3DGLightInfinitytSet(lbl_1_bss_9EC);
    var_r31 = &Hu3DGlobalLight[lbl_1_bss_9EC];
    var_r31->unk_00 |= 0x8000;
}

void fn_1_6DF0(M420DllUnkMapStruct2 *arg0)
{
    float var_f31;

    if (arg0->unk_00_field3) {
        if (arg0->unk_00_field0) {
            switch (arg0->unk_78) {
                case 0:
                    var_f31 = arg0->unk_70;
                    break;
                case 1:
                    var_f31 = sind((90.0f * arg0->unk_70));
                    var_f31 *= var_f31;
                    break;
                case 2:
                    var_f31 = sind((90.0f * arg0->unk_70));
                    var_f31 *= var_f31 * var_f31;
                    break;
            }
            arg0->unk_04.x = arg0->unk_10.x + (var_f31 * (arg0->unk_1C.x - arg0->unk_10.x));
            arg0->unk_04.y = arg0->unk_10.y + (var_f31 * (arg0->unk_1C.y - arg0->unk_10.y));
            arg0->unk_04.z = arg0->unk_10.z + (var_f31 * (arg0->unk_1C.z - arg0->unk_10.z));
            if ((arg0->unk_70 += arg0->unk_74) >= 1.0f) {
                arg0->unk_04 = arg0->unk_1C;
                arg0->unk_00_field0 = 0;
            }
        }
        Hu3DModelPosSet(arg0->unk_02, arg0->unk_04.x, arg0->unk_04.y, arg0->unk_04.z);
        if (arg0->unk_00_field1) {
            switch (arg0->unk_84) {
                case 0:
                    var_f31 = arg0->unk_7C;
                    break;
                case 1:
                    var_f31 = sind((90.0f * arg0->unk_7C));
                    var_f31 *= var_f31;
                    break;
            }
            arg0->unk_28.x = arg0->unk_34.x + (var_f31 * (arg0->unk_40.x - arg0->unk_34.x));
            arg0->unk_28.y = arg0->unk_34.y + (var_f31 * (arg0->unk_40.y - arg0->unk_34.y));
            arg0->unk_28.z = arg0->unk_34.z + (var_f31 * (arg0->unk_40.z - arg0->unk_34.z));
            if ((arg0->unk_7C += arg0->unk_80) >= 1.0f) {
                arg0->unk_28 = arg0->unk_40;
                arg0->unk_00_field1 = 0;
            }
        }
        Hu3DModelRotSet(arg0->unk_02, arg0->unk_28.x, arg0->unk_28.y, arg0->unk_28.z);
        if (arg0->unk_00_field2) {
            switch (arg0->unk_90) {
                case 0:
                    var_f31 = arg0->unk_88;
                    break;
                case 1:
                    var_f31 = sind((90.0f * arg0->unk_88));
                    var_f31 *= var_f31;
                    break;
            }
            arg0->unk_4C.x = arg0->unk_58.x + (var_f31 * (arg0->unk_64.x - arg0->unk_58.x));
            arg0->unk_4C.y = arg0->unk_58.y + (var_f31 * (arg0->unk_64.y - arg0->unk_58.y));
            arg0->unk_4C.z = arg0->unk_58.z + (var_f31 * (arg0->unk_64.z - arg0->unk_58.z));
            if ((arg0->unk_88 += arg0->unk_8C) >= 1.0f) {
                arg0->unk_4C = arg0->unk_64;
                arg0->unk_00_field2 = 0;
            }
        }
        Hu3DModelScaleSet(arg0->unk_02, arg0->unk_4C.x, arg0->unk_4C.y, arg0->unk_4C.z);
    }
}

void fn_1_7230(M420DllUnkMapStruct2 *arg0, Vec *arg1, s32 arg2, s32 arg3)
{
    arg0->unk_1C = *arg1;
    arg0->unk_10 = arg0->unk_04;
    arg0->unk_70 = 0.0f;
    arg0->unk_74 = 1.0f / arg2;
    arg0->unk_78 = arg3;
    arg0->unk_00_field0 = 1;
}

void fn_1_72C8(M420DllUnkMapStruct2 *arg0, Vec *arg1, s32 arg2, s32 arg3)
{
    arg0->unk_40 = *arg1;
    arg0->unk_34 = arg0->unk_28;
    arg0->unk_7C = 0.0f;
    arg0->unk_80 = 1.0f / arg2;
    arg0->unk_84 = arg3;
    arg0->unk_00_field1 = 1;
}

void fn_1_7360(M420DllUnkMapStruct2 *arg0, Vec *arg1, s32 arg2, s32 arg3)
{
    arg0->unk_64 = *arg1;
    arg0->unk_58 = arg0->unk_4C;
    arg0->unk_88 = 0.0f;
    arg0->unk_8C = 1.0f / arg2;
    arg0->unk_90 = arg3;
    arg0->unk_00_field2 = 1;
}

float fn_1_73F8(float arg8)
{
    float var_f31;
    float var_f30;

    if (arg8 < 0.0f) {
        arg8 = -arg8;
    }
    if (arg8 < 1.0f) {
        var_f31 = (4.0f + ((arg8 * (3.0f * arg8 * arg8)) - (6.0f * arg8 * arg8))) / 6.0f;
    }
    else if (arg8 < 2.0f) {
        var_f30 = arg8 - 2.0f;
        var_f31 = (var_f30 * (-var_f30 * var_f30)) / 6.0f;
    }
    else {
        var_f31 = 0.0f;
    }
    return var_f31;
}

void fn_1_74F8(float *arg0, float *arg1, float *arg2, float *arg3, float arg8)
{
    float var_f30;
    float var_f29;
    float var_f26;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r29 = 0xB;
    var_f30 = 0.0f;
    var_f29 = 0.0f;
    for (var_r31 = -2; var_r31 <= var_r29 + 2; var_r31++) {
        var_r30 = var_r31;
        if (var_r31 < 0) {
            var_r30 = 0;
        }
        if (var_r31 > var_r29) {
            var_r30 = var_r29;
        }
        var_f26 = fn_1_73F8(arg8 - var_r31);
        var_f30 += var_f26 * arg0[var_r30];
        var_f29 += var_f26 * arg1[var_r30];
    }
    *arg2 = var_f30;
    *arg3 = var_f29;
}

void fn_1_7704(void)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;

    M420DllUnkMapStruct2 *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r28 = 0;
    var_r31 = &lbl_1_bss_140[0];
    sp20.x = 0.0f;
    sp20.y = 1000.0f;
    sp20.z = 0.0f;

    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = 0.0f;

    sp8.x = 1.0f;
    sp8.y = 1.0f;
    sp8.z = 1.0f;

    fn_1_7230(var_r31, &sp20, 1, 0);
    fn_1_72C8(var_r31, &sp14, 1, 0);
    var_r28 = HuAudFXEmiterPlay(0x5EF, &sp20);
    sp20.y = 750.0f;
    fn_1_7230(var_r31, &sp20, 80, 1);
    HuPrcSleep(0x50);
    {
        float var_f30;
        float sp5C[12] = {
            0.0f,
            50.0f,
            300.0f,
            350.0f,
            300.0f,
            0.0f,
            -300.0f,
            -350.0f,
            -350.0f,
            -300.0f,
            -100.0f,
            0.0f,
        };
        float sp2C[12] = {
            750.0f,
            700.0f,
            600.0f,
            500.0f,
            400.0f,
            300.0f,
            350.0f,
            400.0f,
            450.0f,
            500.0f,
            600.0f,
            900.0f,
        };
        float var_f24 = 0.050000004f;
        for (var_f30 = -1.0f; var_f30 < 12.0f; var_f30 += var_f24) {
            fn_1_74F8(sp5C, sp2C, &sp20.x, &sp20.y, var_f30);
            fn_1_7230(var_r31, &sp20, 1, 0);
            HuAudFXEmiterUpDate(var_r28, &sp20);
            HuPrcVSleep();
        }
    }
    for (var_r29 = 0; var_r29 < 0x1E; var_r29++) {
        Hu3DModelTPLvlSet(lbl_1_bss_9F0[1], 1.0f - (0.033333335f * var_r29));
        Hu3DModelTPLvlSet(lbl_1_bss_9F0[0xA], 1.0f - (0.033333335f * var_r29));
        HuAudFXEmiterUpDate(var_r28, &sp20);
        HuPrcSleep(1);
    }
    HuAudFXStop(var_r28);
    sp20.x = 1000.0f;
    sp20.y = 0.0f;
    sp20.z = 0.0f;
    fn_1_7230(var_r31, &sp20, 1, 0);
    HuPrcSleep(1);
    Hu3DModelTPLvlSet(lbl_1_bss_9F0[1], 1.0f);
    Hu3DModelTPLvlSet(lbl_1_bss_9F0[0xA], 1.0f);
    *lbl_1_bss_A2C = NULL;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_7E24(void)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;

    M420DllUnkMapStruct2 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    M420DllUnkMapStruct *var_r27;
    s32 var_r26;
    s32 var_r25;

    var_r31 = &lbl_1_bss_140[0];
    {
        Vec sp8 = { 0.0f, 0.0f, 0.0f };
        var_f29 = 800.0f;
        var_f28 = 10.0f;
        var_r29 = 0;
        var_r28 = 0;
        var_r30 = 0;
        var_r31->unk_28.x = 0.0f;
        var_r31->unk_28.y = 0.0f;
        var_r31->unk_28.z = 0.0f;
        var_f31 = 0.0f;
        var_f26 = 0.005f;
        var_r27 = &lbl_1_bss_C0[1];
        var_r26 = var_r27->unk_3C;
        var_r25 = var_r26;
        if (var_r25 != 0) {
            var_f27 = 220.0f;
        }
        else {
            var_f27 = -220.0f;
        }

        for (var_f30 = var_f27; var_f31 < 1.0f; var_f31 += var_f26) {
            sp8.x = (var_f29 * cosd((-180.0f * var_f31))) - (var_f28 * sind((-180.0f * var_f31)));
            sp8.y = 1200.0 + ((var_f28 * cosd((-180.0f * var_f31))) + (var_f29 * sind((-180.0f * var_f31))));
            sp8.z = 0.0f;
            if (var_f31 <= 0.0f) {
                var_r30 = HuAudFXEmiterPlay(0x5EF, &sp8);
            }
            if ((sp8.x < (200.0f + var_f30)) && (var_r28 == 0)) {
                Hu3DModelHookReset(lbl_1_bss_9F0[1]);
                Hu3DModelAttrSet(lbl_1_bss_9F0[0xA], HU3D_ATTR_DISPOFF);
                Hu3DModelHookSet(lbl_1_bss_9F0[1], "itemhook_sao", lbl_1_bss_9F0[0xC]);
                Hu3DModelAttrReset(lbl_1_bss_9F0[0xC], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(lbl_1_bss_9F0[0xC], 0.0f);
                var_r28 = 1;
            }
            if ((sp8.x < var_f30) && (var_r29 == 0)) {
                sp8.x = var_f30;
                if (lbl_1_bss_A2C[3] == NULL) {
                    lbl_1_bss_A2C[3] = HuPrcChildCreate(lbl_1_data_154[3], 0x3ED, 0x5000, 0, lbl_1_bss_4);
                }
                var_r29 = 1;
            }
            fn_1_7230(var_r31, &sp8, 1, 0);
            HuAudFXEmiterUpDate(var_r30, &sp8);
            HuPrcVSleep();
        }
    }
    HuAudFXStop(var_r30);
    lbl_1_bss_A2C[1] = NULL;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_8240(void)
{
    Hu3DModelAttrReset(lbl_1_bss_9F0[4], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[4], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_9F0[6], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[6], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_9F0[8], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[8], 0.0f);
    HuPrcSleep(0x78);
    Hu3DModelAttrSet(lbl_1_bss_9F0[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[6], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[8], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_9F0[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[5], HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[5], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_9F0[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[7], HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[7], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_9F0[9], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_9F0[9], HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(lbl_1_bss_9F0[9], 0.0f);
    lbl_1_bss_A2C[2] = NULL;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_8414(void)
{
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;

    M420DllUnkMapStruct2 *var_r31;
    M420DllUnkMapStruct *var_r30;
    M420DllUnkMapStruct2 *var_r29;
    M420DllUnkMapStruct2 *var_r28;
    M420DllUnkMapStruct2 *var_r27;
    M420DllUnkMapStruct2 *var_r26;
    s32 var_r25;

    var_r31 = &lbl_1_bss_140[2];
    var_r27 = &lbl_1_bss_140[3];
    var_r26 = &lbl_1_bss_140[0];
    Hu3DModelHookReset(lbl_1_bss_9F0[1]);
    var_r31->unk_04 = var_r26->unk_04;
    var_r31->unk_04.y -= 100.0f;
    var_r31->unk_04.z += 148.0f;
    fn_1_6DF0(var_r31);

    sp14 = var_r31->unk_04;
    sp14.y = 80.0f;
    sp14.z = 170.0f;

    sp8 = var_r31->unk_28;
    sp8.x += 45.0f;

    fn_1_7230(var_r31, &sp14, 30, 0);
    fn_1_72C8(var_r31, &sp8, 30, 0);
    HuPrcSleep(0xA);
    HuAudFXPlay(0x5F5);
    var_r25 = fn_1_67A4(0) != 0 ? 0 : 1;
    var_r30 = &lbl_1_bss_C0[var_r25];
    if (var_r25 == 0) {
        var_f30 = -220.0f;
    }
    else {
        var_f30 = 220.0f;
    }
    var_f31 = var_f30;

    sp14 = var_r30->unk_0C->unk_04;
    sp14.y = 40.0f + var_r30->unk_1C;
    sp14.x = var_f31;

    var_r29 = var_r30->unk_0C;
    fn_1_7230(var_r29, &sp14, 30, 1);

    Hu3DMotionTimeSet(var_r30->unk_0C->unk_02, 0.0f);
    Hu3DModelAttrReset(var_r30->unk_0C->unk_02, HU3D_ATTR_DISPOFF);
    sp14 = var_r30->unk_10->unk_04;
    sp14.y = -50.0f + var_r30->unk_1C;
    sp14.x = var_f31;
    var_r28 = var_r30->unk_10;
    fn_1_7230(var_r28, &sp14, 30, 1);
    Hu3DMotionTimeSet(var_r30->unk_10->unk_02, 0.0f);
    Hu3DModelAttrReset(var_r30->unk_10->unk_02, HU3D_ATTR_DISPOFF);
    HuPrcSleep(5);
    lbl_1_bss_B4 = 1;
    sp8.x = 0.0f;
    fn_1_72C8(var_r31, &sp8, 15, 1);
    HuPrcSleep(0xF);
    var_r27->unk_04 = var_r31->unk_04;
    Hu3DModelAttrSet(var_r31->unk_02, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(var_r27->unk_02, HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(var_r27->unk_02, 0.0f);
    Hu3DModelAttrReset(var_r27->unk_02, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(var_r27->unk_02, HU3D_MOTATTR_LOOP);
    HuPrcSleep(0x78);
    lbl_1_bss_A2C[3] = NULL;
    HuPrcEnd();

    while (TRUE) {
        HuPrcVSleep();
    }
}

const float _pad = 0;
