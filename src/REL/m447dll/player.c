#include "REL/m447dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"

#include "ext_math.h"

void fn_1_4300(UnkM447Struct_04 *arg0);
float fn_1_43DC(UnkM447Struct_04 *arg0);
void fn_1_43F8(void);
void fn_1_4444(UnkM447Struct_04 *arg0);
void fn_1_44B0(UnkM447Struct_04 *arg0);
void fn_1_4590(UnkM447Struct_04 *arg0);
void fn_1_4638(UnkM447Struct_04 *arg0);
void fn_1_4680(UnkM447Struct_04 *arg0);
void fn_1_470C(UnkM447Struct_04 *arg0);
void fn_1_4760(UnkM447Struct_04 *arg0);
void fn_1_4764(UnkM447Struct_04 *arg0);
void fn_1_4C84(UnkM447Struct_04 *arg0);
float fn_1_4F7C(float arg0, float arg1, float arg2);
void fn_1_5080(UnkM447Struct_04 *arg0);
void fn_1_5298(UnkM447Struct_04 *arg0);
void fn_1_5520(UnkM447Struct_04 *arg0);
void fn_1_5760(UnkM447Struct_04 *arg0);
void fn_1_59D8(UnkM447Struct_04 *arg0);
void fn_1_5AF0(UnkM447Struct_04 *arg0);
void fn_1_5BD0(UnkM447Struct_04 *arg0);
void fn_1_5C78(UnkM447Struct_04 *arg0);
void fn_1_671C(UnkM447Struct_04 *arg0);
void fn_1_70BC(UnkM447Struct_04 *arg0);
void fn_1_717C(UnkM447Struct_04 *arg0, s32 arg1, s32 arg2);
void fn_1_71FC(UnkM447Struct_04 *arg0, s32 arg1, float arg2, float arg3, s32 arg4);
void fn_1_72A8(UnkM447Struct_04 *arg0);
void fn_1_7688(UnkM447Struct_04 *arg0);
void fn_1_78A8(UnkM447Struct_04 *arg0);
s32 fn_1_7984(UnkM447Struct_04 *arg0);
void fn_1_7A34(UnkM447Struct_04 *arg0);

UnkM447Struct_04 *lbl_1_bss_98[2];

const s32 lbl_1_rodata_2A0[][9]
    = { { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MARIOMOT, 2), DATA_MAKE_NUM(DATADIR_MARIOMOT, 3),
            DATA_MAKE_NUM(DATADIR_MARIOMOT, 113), DATA_MAKE_NUM(DATADIR_MARIOMOT, 31), DATA_MAKE_NUM(DATADIR_MARIOMOT, 28),
            DATA_MAKE_NUM(DATADIR_MARIOMOT, 72), DATA_MAKE_NUM(DATADIR_MARIOMOT, 23), DATA_MAKE_NUM(DATADIR_MARIOMOT, 24) },
          { DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 2), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 3),
              DATA_MAKE_NUM(DATADIR_LUIGIMOT, 113), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 31), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 28),
              DATA_MAKE_NUM(DATADIR_LUIGIMOT, 72), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 23), DATA_MAKE_NUM(DATADIR_LUIGIMOT, 24) },
          { DATA_MAKE_NUM(DATADIR_PEACHMOT, 0), DATA_MAKE_NUM(DATADIR_PEACHMOT, 2), DATA_MAKE_NUM(DATADIR_PEACHMOT, 3),
              DATA_MAKE_NUM(DATADIR_PEACHMOT, 113), DATA_MAKE_NUM(DATADIR_PEACHMOT, 31), DATA_MAKE_NUM(DATADIR_PEACHMOT, 28),
              DATA_MAKE_NUM(DATADIR_PEACHMOT, 72), DATA_MAKE_NUM(DATADIR_PEACHMOT, 23), DATA_MAKE_NUM(DATADIR_PEACHMOT, 24) },
          { DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0), DATA_MAKE_NUM(DATADIR_YOSHIMOT, 2), DATA_MAKE_NUM(DATADIR_YOSHIMOT, 3),
              DATA_MAKE_NUM(DATADIR_YOSHIMOT, 113), DATA_MAKE_NUM(DATADIR_YOSHIMOT, 31), DATA_MAKE_NUM(DATADIR_YOSHIMOT, 28),
              DATA_MAKE_NUM(DATADIR_YOSHIMOT, 72), DATA_MAKE_NUM(DATADIR_YOSHIMOT, 23), DATA_MAKE_NUM(DATADIR_YOSHIMOT, 24) },
          { DATA_MAKE_NUM(DATADIR_WARIOMOT, 0), DATA_MAKE_NUM(DATADIR_WARIOMOT, 2), DATA_MAKE_NUM(DATADIR_WARIOMOT, 3),
              DATA_MAKE_NUM(DATADIR_WARIOMOT, 113), DATA_MAKE_NUM(DATADIR_WARIOMOT, 31), DATA_MAKE_NUM(DATADIR_WARIOMOT, 28),
              DATA_MAKE_NUM(DATADIR_WARIOMOT, 72), DATA_MAKE_NUM(DATADIR_WARIOMOT, 23), DATA_MAKE_NUM(DATADIR_WARIOMOT, 24) },
          { DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 2), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 3),
              DATA_MAKE_NUM(DATADIR_DONKEYMOT, 113), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 31), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 28),
              DATA_MAKE_NUM(DATADIR_DONKEYMOT, 72), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 23), DATA_MAKE_NUM(DATADIR_DONKEYMOT, 24) },
          { DATA_MAKE_NUM(DATADIR_DAISYMOT, 0), DATA_MAKE_NUM(DATADIR_DAISYMOT, 2), DATA_MAKE_NUM(DATADIR_DAISYMOT, 3),
              DATA_MAKE_NUM(DATADIR_DAISYMOT, 113), DATA_MAKE_NUM(DATADIR_DAISYMOT, 31), DATA_MAKE_NUM(DATADIR_DAISYMOT, 28),
              DATA_MAKE_NUM(DATADIR_DAISYMOT, 72), DATA_MAKE_NUM(DATADIR_DAISYMOT, 23), DATA_MAKE_NUM(DATADIR_DAISYMOT, 24) },
          { DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 2), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 3),
              DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 113), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 31), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 28),
              DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 72), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 23), DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 24) },
          { DATA_MAKE_NUM(DATADIR_M447, 32), DATA_MAKE_NUM(DATADIR_M447, 33), DATA_MAKE_NUM(DATADIR_M447, 34), DATA_MAKE_NUM(DATADIR_M447, 41),
              DATA_MAKE_NUM(DATADIR_M447, 39), DATA_MAKE_NUM(DATADIR_M447, 38), DATA_MAKE_NUM(DATADIR_M447, 37), DATA_MAKE_NUM(DATADIR_M447, 36),
              DATA_MAKE_NUM(DATADIR_M447, 40) } };

const float lbl_1_rodata_3E4[] = { 150.0f, 170.0f, 188.0f, 169.0f, 164.0f, 140.0f, 180.0f, 145.0f, 150.0f };

const float lbl_1_rodata_408[][6] = { { -150.0f, 0.0f, 350.0f, 0.0f, 90.0f, 0.0f }, { 150.0f, 0.0f, 350.0f, 0.0f, -90.0f, 0.0f },
    { -150.0f, 0.0f, -200.0f, 0.0f, 90.0f, 0.0f }, { 150.0f, 0.0f, -200.0f, 0.0f, -90.0f, 0.0f } };

const u8 lbl_1_rodata_468[][5] = { { 5, 6, 7, 8, 9 }, { 4, 5, 6, 7, 8 }, { 3, 4, 5, 6, 7 }, { 2, 3, 4, 5, 6 } };

void fn_1_3F84(void)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        lbl_1_bss_98[i] = NULL;
    }
}

UnkM447Struct_04 *fn_1_3FC4(s32 arg0)
{
    UnkM447Struct_04 *temp_r3;
    s16 var_r28;
    s16 var_r27;
    s32 i;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r3), MEMORY_DEFAULT_NUM);
    if (!temp_r3) {
        OSReport("M447PlayerCreate ERROR...\n");
        return NULL;
    }
    temp_r3->unk00 = arg0;
    temp_r3->unk19 = GWPlayerCfg[arg0].diff;
    temp_r3->unk08 = GWPlayerCfg[arg0].iscom;
    if (temp_r3->unk08 != 0) {
        var_r28 = 4;
    }
    else {
        var_r28 = GWPlayerCfg[arg0].pad_idx;
    }
    temp_r3->unk1A = var_r28;
    temp_r3->unk1C = (GWPlayerCfg[arg0].character == 10);
    if (temp_r3->unk1C != 0) {
        var_r27 = 8;
    }
    else {
        var_r27 = GWPlayerCfg[arg0].character;
    }
    temp_r3->unk18 = var_r27;
    temp_r3->unk24 = 0;
    temp_r3->unk20 = 0;
    temp_r3->unk1B = 0;
    temp_r3->unk28.x = lbl_1_rodata_408[arg0][0];
    temp_r3->unk28.y = lbl_1_rodata_408[arg0][1];
    temp_r3->unk28.z = lbl_1_rodata_408[arg0][2];
    temp_r3->unk34 = lbl_1_rodata_408[arg0][3];
    temp_r3->unk38 = lbl_1_rodata_408[arg0][4];
    temp_r3->unk3C = lbl_1_rodata_408[arg0][5];
    temp_r3->unk44 = 0.0f;
    temp_r3->unk48 = 0.0f;
    temp_r3->unk4C = 0.0f;
    temp_r3->unk50 = 50.0f;
    temp_r3->unk04 = 0;
    temp_r3->unkB0 = NULL;
    temp_r3->unkB4 = NULL;
    fn_1_4444(temp_r3);
    Hu3DModelLayerSet(temp_r3->unk68, 6);
    fn_1_44B0(temp_r3);
    fn_1_4590(temp_r3);
    fn_1_717C(temp_r3, 0, 0x40000001);
    if (temp_r3->unk1C == 0) {
        CharModelMotionDataClose(temp_r3->unk18);
    }
    if (temp_r3->unk1C != 0) {
        temp_r3->unkB0 = (Process *)CharModelEffectNpcInit(temp_r3->unk68, temp_r3->unk6A[2], 1, 10);
        temp_r3->unkB4 = (Process *)CharModelEffectNpcInit(temp_r3->unk68, temp_r3->unk6A[1], 0, 10);
    }
    CharModelLayerSetAll(2);
    temp_r3->unkAC = HuPrcChildCreate(fn_1_43F8, 102, 0x3000, 0, lbl_1_bss_4);
    temp_r3->unkAC->user_data = temp_r3;
    for (i = 0; i < 2; i++) {
        if (!lbl_1_bss_98[i]) {
            lbl_1_bss_98[i] = temp_r3;
            break;
        }
    }
    return temp_r3;
}

void fn_1_4300(UnkM447Struct_04 *arg0)
{
    s32 i;

    if (arg0->unkB0) {
        HuPrcKill(arg0->unkB0);
    }
    if (arg0->unkB4) {
        HuPrcKill(arg0->unkB4);
    }
    fn_1_470C(arg0);
    fn_1_4680(arg0);
    fn_1_4638(arg0);
    HuPrcKill(arg0->unkAC);
    for (i = 0; i < 2; i++) {
        if (lbl_1_bss_98[i] == arg0) {
            lbl_1_bss_98[i] = NULL;
            break;
        }
    }
    HuMemDirectFree(arg0);
}

void fn_1_43CC(UnkM447Struct_04 *arg0, s32 arg1)
{
    arg0->unk24 = arg1;
    arg0->unk20 = 0;
}

float fn_1_43DC(UnkM447Struct_04 *arg0)
{
    return lbl_1_rodata_3E4[arg0->unk18];
}

void (*lbl_1_data_1CC[])(UnkM447Struct_04 *)
    = { fn_1_4760, fn_1_4764, fn_1_5080, fn_1_5298, fn_1_5520, fn_1_5760, fn_1_5C78, fn_1_671C, fn_1_59D8, fn_1_5AF0, fn_1_5BD0 };

void fn_1_43F8(void)
{
    UnkM447Struct_04 *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        lbl_1_data_1CC[temp_r31->unk24](temp_r31);
        fn_1_70BC(temp_r31);
        HuPrcVSleep();
    }
}

void fn_1_4444(UnkM447Struct_04 *arg0)
{
    if (arg0->unk1C != 0) {
        arg0->unk68 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M447, 31));
    }
    else {
        arg0->unk68 = CharModelCreate(arg0->unk18, 2);
    }
    Hu3DModelShadowSet(arg0->unk68);
}

void fn_1_44B0(UnkM447Struct_04 *arg0)
{
    s32 i;

    if (arg0->unk1C != 0) {
        for (i = 0; i < 9; i++) {
            arg0->unk6A[i] = Hu3DJointMotionFile(arg0->unk68, lbl_1_rodata_2A0[arg0->unk18][i]);
        }
    }
    else {
        for (i = 0; i < 9; i++) {
            arg0->unk6A[i] = CharModelMotionCreate(arg0->unk18, lbl_1_rodata_2A0[arg0->unk18][i]);
        }
    }
}

void fn_1_4590(UnkM447Struct_04 *arg0)
{
    arg0->unk7C[0] = espEntry(DATA_MAKE_NUM(DATADIR_M447, 42), 0, 0);
    espPriSet(arg0->unk7C[0], arg0->unk00 * 10);
    arg0->unk7C[1] = espEntry(DATA_MAKE_NUM(DATADIR_M447, 43), 0, 0);
    espPriSet(arg0->unk7C[1], arg0->unk00 * 10 + 1);
    espDispOff(arg0->unk7C[0]);
    espDispOff(arg0->unk7C[1]);
    espTPLvlSet(arg0->unk7C[1], 0.8f);
}

void fn_1_4638(UnkM447Struct_04 *arg0)
{
    if (arg0->unk1C != 0) {
        Hu3DModelKill(arg0->unk68);
    }
    else {
        CharModelKill(arg0->unk18);
    }
}

void fn_1_4680(UnkM447Struct_04 *arg0)
{
    s32 i;

    if (arg0->unk1C != 0) {
        for (i = 0; i < 9; i++) {
            Hu3DMotionKill(arg0->unk6A[i]);
        }
    }
    else {
        for (i = 0; i < 9; i++) {
            CharModelMotionKill(arg0->unk18, arg0->unk6A[i]);
        }
    }
}

void fn_1_470C(UnkM447Struct_04 *arg0)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        espKill(arg0->unk7C[i]);
    }
}

void fn_1_4760(UnkM447Struct_04 *arg0) { }

void fn_1_4764(UnkM447Struct_04 *arg0)
{
    Vec sp8;
    float temp_f31;
    s32 var_r29;
    s32 var_r28;
    s32 i;

    switch (arg0->unk20) {
        case 0:
            arg0->unk0C = 0;
            arg0->unk10 = 0;
            arg0->unk28.y = 0.0f;
            arg0->unk20 = 1;
            arg0->unk14 = 0;
            /* fallthrough */
        case 1:
            if (arg0->unk04 != 0) {
                if (arg0->unk08 != 0) {
                    if (arg0->unk0C == 0 && arg0->unk10 == 0) {
                        arg0->unk44 = 0.0f;
                        arg0->unk48 = 0.0f;
                        arg0->unk4C = 0.0f;
                        if (fn_1_A240() % lbl_1_rodata_468[arg0->unk19][lbl_1_bss_8->unk2C] == 0) {
                            var_r29 = 5;
                            for (i = 0; i < 5; i++) {
                                if (lbl_1_bss_10->unk54[i] == 0 && lbl_1_bss_A4[i]->unk08 != 0) {
                                    var_r29 = i;
                                    break;
                                }
                            }
                        }
                        else {
                            for (i = 0; i < 10; i++) {
                                var_r29 = fn_1_A240() % 5;
                                if (lbl_1_bss_10->unk54[var_r29] == 0) {
                                    break;
                                }
                            }
                            if (i == 10) {
                                var_r29 = 5;
                            }
                        }
                        if (var_r29 < 5) {
                            fn_1_1ED4(var_r29, &sp8);
                            temp_f31 = 10.0f - 0.1f * (fn_1_A240() % 10);
                            arg0->unk44 = (sp8.x - arg0->unk28.x) / temp_f31;
                            arg0->unk4C = (sp8.z - arg0->unk28.z) / temp_f31;
                            arg0->unk48 = 0.0f;
                            arg0->unk64 = fn_1_A240() % 20 + 10;
                            arg0->unk0C = 1;
                        }
                    }
                }
                else {
                    arg0->unk44 = (float)HuPadStkX[arg0->unk1A] / 4;
                    arg0->unk4C = -(float)HuPadStkY[arg0->unk1A] / 4;
                }
                var_r28 = 0;
                var_r29 = fn_1_7984(arg0);
                if (var_r29 != 5) {
                    if (lbl_1_bss_10->unk68[var_r29] == 0) {
                        fn_1_7A34(arg0);
                        if (arg0->unk08 != 0) {
                            arg0->unk10 = 1;
                            arg0->unk44 = 0.0f;
                            arg0->unk48 = 0.0f;
                            arg0->unk4C = 0.0f;
                            if (arg0->unk64-- <= 0) {
                                var_r28 = 1;
                            }
                        }
                        else if (HuPadBtnDown[arg0->unk1A] & 0x100) {
                            var_r28 = 1;
                        }
                        if (var_r28 != 0) {
                            arg0->unk44 = 0.0f;
                            arg0->unk4C = 0.0f;
                            lbl_1_bss_10->unk68[var_r29] = 1;
                            fn_1_43CC(arg0, 2);
                            arg0->unk10 = 0;
                        }
                    }
                }
                else {
                    if (arg0->unk10 != 0) {
                        arg0->unk10 = 0;
                        arg0->unk0C = 0;
                    }
                    fn_1_7A6C(arg0);
                }
            }
            else {
                arg0->unk44 = 0.0f;
                arg0->unk48 = 0.0f;
                arg0->unk4C = 0.0f;
            }
            fn_1_4C84(arg0);
            break;
    }
}

void fn_1_4C84(UnkM447Struct_04 *arg0)
{
    s16 var_r30;

    var_r30 = 0;
    arg0->unk40 = sqrtf(arg0->unk44 * arg0->unk44 + arg0->unk4C * arg0->unk4C);
    if (0.5f <= arg0->unk40) {
        if (10.0f <= arg0->unk40) {
            arg0->unk44 /= arg0->unk40;
            arg0->unk4C /= arg0->unk40;
            arg0->unk40 = 10.0f;
            arg0->unk44 = arg0->unk44 * 10.0f;
            arg0->unk4C = arg0->unk4C * 10.0f;
        }
        arg0->unk38 = fn_1_4F7C(arg0->unk38, atan2d(arg0->unk44, arg0->unk4C), 0.4f);
        if (8.0f <= arg0->unk40) {
            var_r30 = 2;
        }
        else {
            var_r30 = 1;
        }
    }
    arg0->unk28.x += arg0->unk44;
    arg0->unk28.z += arg0->unk4C;
    switch (arg0->unk24) {
        case 1:
            fn_1_72A8(arg0);
            fn_1_78A8(arg0);
            fn_1_7688(arg0);
            break;
        case 6:
        case 7:
            fn_1_78A8(arg0);
            fn_1_7688(arg0);
            break;
    }
    if (var_r30 >= 0 && arg0->unkA4 != var_r30) {
        fn_1_71FC(arg0, var_r30, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    }
}

float fn_1_4F7C(float arg0, float arg1, float arg2)
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

void fn_1_5080(UnkM447Struct_04 *arg0)
{
    Vec sp14;
    Vec sp8;
    s32 var_r30;

    switch (arg0->unk20) {
        case 0:
            fn_1_7A6C(arg0);
            var_r30 = fn_1_7984(arg0);
            fn_1_1ED4(var_r30, &sp14);
            VECSubtract(&sp14, &arg0->unk28, &sp8);
            arg0->unk38 = fn_1_4F7C(arg0->unk38, atan2d(sp8.x, sp8.z), 1.0f);
            fn_1_71FC(arg0, 3, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            arg0->unk20 = 1;
            /* fallthrough */
        case 1:
            if (!Hu3DMotionEndCheck(arg0->unk68)) {
                break;
            }
            arg0->unk20 = 2;
            /* fallthrough */
        case 2:
            fn_1_43CC(arg0, 3);
            break;
    }
}

void fn_1_5298(UnkM447Struct_04 *arg0)
{
    Vec sp8;
    s32 temp_r29;
    UnkM447Struct_01 *temp_r28;
    s32 i;

    switch (arg0->unk20) {
        case 0:
            temp_r29 = fn_1_7984(arg0);
            fn_1_717C(arg0, 0, 0x40000001);
            fn_1_1ED4(temp_r29, &sp8);
            arg0->unk28.x = sp8.x;
            arg0->unk28.z = sp8.z;
            arg0->unk28.y = 30.0f;
            fn_1_1F00(lbl_1_bss_10, temp_r29);
            HuAudFXPlay(0x784);
            arg0->unk60 = 0;
            arg0->unk20 = 1;
            /* fallthrough */
        case 1:
            arg0->unk28.y -= 1.0f;
            if (arg0->unk60++ >= 30) {
                arg0->unk28.y = 2.0f;
                arg0->unk20 = 2;
                temp_r29 = fn_1_7984(arg0);
                arg0->unkA8 = lbl_1_bss_A4[temp_r29];
                if (arg0->unkA8->unk08 != 0) {
                    fn_1_8FF4(arg0->unkA8, 5);
                    for (i = 0; i < 5; i++) {
                        temp_r28 = lbl_1_bss_A4[i];
                        if (temp_r28 != arg0->unkA8 && lbl_1_bss_10->unk68[i] == 0) {
                            fn_1_1F00(lbl_1_bss_10, i);
                            if (temp_r28->unk04 == 2) {
                                fn_1_8FF4(temp_r28, 4);
                            }
                        }
                    }
                    for (i = 0; i < 2; i++) {
                        if (lbl_1_bss_98[i] != arg0) {
                            lbl_1_bss_98[i]->unk04 = 0;
                        }
                    }
                    arg0->unk1B++;
                    arg0->unk14 = 1;
                    fn_1_43CC(arg0, 5);
                }
                else {
                    fn_1_8FF4(arg0->unkA8, 3);
                    fn_1_43CC(arg0, 4);
                }
            }
            break;
        case 2:
            fn_1_43CC(arg0, 1);
            break;
    }
}

const s32 lbl_1_rodata_4EC[] = { 0x0000012A, 0x0000016A, 0x000001AA, 0x000001EA, 0x0000022A, 0x0000026A, 0x000002AA, 0x000002EA };

void fn_1_5520(UnkM447Struct_04 *arg0)
{
    Vec sp8;
    float var_f31;
    float var_f30;

    switch (arg0->unk20) {
        case 0:
            fn_1_71FC(arg0, 5, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            arg0->unk60 = 0;
            arg0->unk20 = 1;
            /* fallthrough */
        case 1:
            var_f30 = lbl_1_rodata_3E4[arg0->unk18];
            var_f31 = var_f30; // inline?
            sp8 = arg0->unkA8->unk10;
            if (var_f31 + lbl_1_rodata_648[arg0->unkA8->unk00] + 120.0f < sp8.y) {
                break;
            }
            arg0->unk20 = 2;
            /* fallthrough */
        case 2:
            fn_1_717C(arg0, 4, 0);
            arg0->unk60 = 0;
            arg0->unk20 = 3;
            fn_1_7AA4(arg0, 1, 60);
            if (arg0->unk18 == 8) {
                HuAudFXPlay(0x42);
            }
            else {
                HuAudFXPlay(lbl_1_rodata_4EC[arg0->unk18]);
            }
            /* fallthrough */
        case 3:
            if (arg0->unk60++ < 40) {
                break;
            }
            arg0->unk60 = 0;
            arg0->unk20 = 4;
            /* fallthrough */
        case 4:
            Hu3DModelAttrSet(arg0->unk68, HU3D_MOTATTR_PAUSE);
            arg0->unk60 = 0;
            arg0->unk20 = 5;
            /* fallthrough */
        case 5:
            if (arg0->unk60++ < 20) {
                break;
            }
            arg0->unk20 = 6;
            /* fallthrough */
        case 6:
            Hu3DModelAttrReset(arg0->unk68, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(arg0->unk68, HU3D_MOTATTR_LOOP);
            arg0->unk60 = 0;
            arg0->unk20 = 7;
            /* fallthrough */
        case 7:
            if (arg0->unk60++ < 40) {
                break;
            }
            arg0->unk20 = 8;
        case 8:
            /* fallthrough */
            fn_1_43CC(arg0, 1);
            break;
    }
}

void fn_1_5760(UnkM447Struct_04 *arg0)
{
    Vec sp14;
    Vec sp8;
    s32 var_r30;

    switch (arg0->unk20) {
        case 0:
            Hu3DModelAttrReset(arg0->unk68, HU3D_MOTATTR_LOOP);
            fn_1_71FC(arg0, 5, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            arg0->unk60 = 0;
            arg0->unk20 = 1;
            /* fallthrough */
        case 1:
            var_r30 = fn_1_7984(arg0);
            sp14 = lbl_1_bss_A4[var_r30]->unk10;
            VECSubtract(&sp14, &arg0->unk28, &sp8);
            arg0->unk38 = fn_1_4F7C(arg0->unk38, atan2d(sp8.x, sp8.z), 0.1f);
            if (arg0->unk60++ < 30) {
                break;
            }
            arg0->unk20 = 2;
        case 2:
            fn_1_71FC(arg0, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            fn_1_43CC(arg0, 8);
            break;
    }
}

const s32 lbl_1_rodata_510[] = { 0x00000122, 0x00000162, 0x000001A2, 0x000001E2, 0x00000222, 0x00000262, 0x000002A2, 0x000002E2, 0x00000124,
    0x00000164, 0x000001A4, 0x000001E4, 0x00000224, 0x00000264, 0x000002A4, 0x000002E4, 0x00000121, 0x00000161, 0x000001A1, 0x000001E1, 0x00000221,
    0x00000261, 0x000002A1, 0x000002E1 };

void fn_1_59D8(UnkM447Struct_04 *arg0)
{
    switch (arg0->unk20) {
        case 0:
            if (arg0->unk18 == 8) {
                HuAudFXPlay(0x40);
            }
            else {
                HuAudFXPlay(lbl_1_rodata_510[arg0->unk18]);
            }
            fn_1_71FC(arg0, 6, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            arg0->unk20 = 1;
            /* fallthrough */
        case 1:
            if (!Hu3DMotionEndCheck(arg0->unk68)) {
                break;
            }
            arg0->unk20 = 2;
            /* fallthrough */
        case 2:
            fn_1_71FC(arg0, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            fn_1_43CC(arg0, 0);
            fn_1_7AA4(arg0, 0, 60);
            break;
    }
}

void fn_1_5AF0(UnkM447Struct_04 *arg0)
{
    switch (arg0->unk20) {
        case 0:
            if (arg0->unk1C != 0) {
                HuAudFXPlay(0x40);
            }
            fn_1_71FC(arg0, 7, 0.0f, 8.0f, (arg0->unk1C != 0) ? HU3D_MOTATTR_LOOP : HU3D_MOTATTR_NONE);
            arg0->unk20 = 1;
            /* fallthrough */
        case 1:
            if (!Hu3DMotionEndCheck(arg0->unk68)) {
                break;
            }
            arg0->unk20 = 2;
            /* fallthrough */
        case 2:
            fn_1_43CC(arg0, 0);
            break;
    }
}

void fn_1_5BD0(UnkM447Struct_04 *arg0)
{
    switch (arg0->unk20) {
        case 0:
            fn_1_71FC(arg0, 8, 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            arg0->unk20 = 1;
            /* fallthrough */
        case 1:
            if (!Hu3DMotionEndCheck(arg0->unk68)) {
                break;
            }
            arg0->unk20 = 2;
            /* fallthrough */
        case 2:
            fn_1_43CC(arg0, 0);
            break;
    }
}

void fn_1_5C78(UnkM447Struct_04 *arg0)
{
    float temp_f22;
    float temp_f21;
    float temp_f25;

    switch (arg0->unk20) {
        case 0:
            fn_1_7A6C(arg0);
            temp_f22 = arg0->unk28.x - lbl_1_rodata_408[arg0->unk00][0];
            temp_f21 = arg0->unk28.z - lbl_1_rodata_408[arg0->unk00][2] - 25.0f;
            if (ABS(temp_f22) < 5.0f && ABS(temp_f21) < 5.0f && 180.0f == arg0->unk38) {
                arg0->unk20 = 3;
            }
            else {
                arg0->unk20 = 1;
            }
            /* fallthrough */
        case 1:
            temp_f25 = 8.0f;
            arg0->unk44 = (lbl_1_rodata_408[arg0->unk00][0] - arg0->unk28.x) / temp_f25;
            arg0->unk4C = (lbl_1_rodata_408[arg0->unk00][2] - arg0->unk28.z) / temp_f25;
            arg0->unk48 = 0.0f;
            if (!(arg0->unk44 > -0.1f && arg0->unk44 < 0.1f && arg0->unk4C > -0.1f && arg0->unk4C < 0.1f)) {
                fn_1_4C84(arg0);
                break;
            }
            arg0->unk20 = 2;
            /* fallthrough */
        case 2:
            temp_f25 = 8.0f;
            arg0->unk44 = (lbl_1_rodata_408[arg0->unk00][0] - arg0->unk28.x) / temp_f25;
            arg0->unk4C = (lbl_1_rodata_408[arg0->unk00][2] - 25.0f - arg0->unk28.z) / temp_f25;
            arg0->unk48 = 0.0f;
            if (!(arg0->unk44 > -0.1f && arg0->unk44 < 0.1f && arg0->unk4C > -0.1f && arg0->unk4C < 0.1f)) {
                fn_1_4C84(arg0);
                break;
            }
            arg0->unk20 = 3;
            /* fallthrough */
        case 3:
            fn_1_43CC(arg0, 1);
            break;
    }
}

void fn_1_671C(UnkM447Struct_04 *arg0)
{
    float var_f25;

    switch (arg0->unk20) {
        case 0:
            fn_1_7A6C(arg0);
            arg0->unk20 = 1;
            /* fallthrough */
        case 1:
            var_f25 = 8.0f;
            arg0->unk44 = (lbl_1_rodata_408[arg0->unk00][12] - arg0->unk28.x) / var_f25;
            arg0->unk4C = (lbl_1_rodata_408[arg0->unk00][14] - 25.0f - arg0->unk28.z) / var_f25;
            arg0->unk48 = 0.0f;
            fn_1_4C84(arg0);
            if (!(arg0->unk44 > -0.1f && arg0->unk44 < 0.1f && arg0->unk4C > -0.1f && arg0->unk4C < 0.1f)) {
                break;
            }
            arg0->unk20 = 2;
            /* fallthrough */
        case 2:
            var_f25 = 8.0f;
            arg0->unk44 = (lbl_1_rodata_408[arg0->unk00][12] - arg0->unk28.x) / var_f25;
            arg0->unk4C = (lbl_1_rodata_408[arg0->unk00][14] - arg0->unk28.z) / var_f25;
            arg0->unk48 = 0.0f;
            fn_1_4C84(arg0);
            if (!(arg0->unk44 > -0.1f && arg0->unk44 < 0.1f && arg0->unk4C > -0.1f && arg0->unk4C < 0.1f)) {
                break;
            }
            arg0->unk20 = 3;
            /* fallthrough */
        case 3:
            fn_1_43CC(arg0, 1);
            break;
    }
}

void fn_1_70BC(UnkM447Struct_04 *arg0)
{
    Vec sp14;
    Vec sp8;

    Hu3DModelPosSet(arg0->unk68, arg0->unk28.x, arg0->unk28.y, arg0->unk28.z);
    Hu3DModelRotSet(arg0->unk68, arg0->unk34, arg0->unk38, arg0->unk3C);
    sp14 = arg0->unk28;
    sp14.y += 300.0f;
    Hu3D3Dto2D(&sp14, 1, &sp8);
    espPosSet(arg0->unk7C[1], sp8.x, sp8.y + 3.0f);
    espPosSet(arg0->unk7C[0], sp8.x, sp8.y);
}

void fn_1_717C(UnkM447Struct_04 *arg0, s32 arg1, s32 arg2)
{
    if (arg0->unk1C != 0) {
        Hu3DMotionSet(arg0->unk68, arg0->unk6A[arg1]);
    }
    else {
        CharModelMotionSet(arg0->unk18, arg0->unk6A[arg1]);
    }
    Hu3DModelAttrSet(arg0->unk68, arg2);
    arg0->unkA4 = arg1;
}

void fn_1_71FC(UnkM447Struct_04 *arg0, s32 arg1, float arg2, float arg3, s32 arg4)
{
    if (arg0->unk1C != 0) {
        Hu3DMotionShiftSet(arg0->unk68, arg0->unk6A[arg1], arg2, arg3, arg4);
    }
    else {
        CharModelMotionShiftSet(arg0->unk18, arg0->unk6A[arg1], arg2, arg3, arg4);
    }
    arg0->unkA4 = arg1;
}

float lbl_1_data_21C[][4] = { { -700.0f, -700.0f, -700.0f, 700.0f }, { 700.0f, -700.0f, 700.0f, 700.0f }, { -800.0f, 450.0f, 800.0f, 450.0f },
    { -700.0f, -700.0f, 700.0f, -700.0f } };

// Vec[]?
float lbl_1_data_25C[][3] = { { -700.0f, -700.0f, 200.0f }, { 700.0f, -700.0f, 200.0f } };

void fn_1_72A8(UnkM447Struct_04 *arg0)
{
    float sp28[3]; // Vec?
    float sp18[4];
    float spC[3]; // Vec?
    float temp_f31;
    float temp_f30;
    float var_f28;
    s32 i;

    sp28[0] = arg0->unk28.x;
    sp28[1] = arg0->unk28.z;
    sp28[2] = 95.0f;
    for (i = 0; i < 4; i++) {
        if (fn_1_80BC(sp28, lbl_1_data_21C[i], sp18) == 0) {
            continue;
        }
        if (i / 2 == 0) {
            if (lbl_1_data_21C[i][0] < 0.0f) {
                arg0->unk28.x = sp28[2] + lbl_1_data_21C[i][0];
            }
            else {
                arg0->unk28.x = lbl_1_data_21C[i][0] - sp28[2];
            }
        }
        else {
            if (lbl_1_data_21C[i][1] < 0.0f) {
                arg0->unk28.z = sp28[2] + lbl_1_data_21C[i][1];
            }
            else {
                arg0->unk28.z = lbl_1_data_21C[i][1] - sp28[2];
            }
        }
        arg0->unk0C = 0;
    }
    spC[0] = arg0->unk28.x;
    spC[1] = arg0->unk28.z;
    spC[2] = arg0->unk50;
    for (i = 0; i < 2; i++) {
        if (fn_1_879C(spC, lbl_1_data_25C[i], 1, 0) != 0) {
            arg0->unk28.x = spC[0];
            arg0->unk28.z = spC[1];
            arg0->unk0C = 0;
        }
    }
    if (arg0->unk28.z > 0.0f) {
        temp_f31 = arg0->unk28.x;
        temp_f30 = arg0->unk28.z - -120.0f;
        var_f28 = sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30);
        if (700.0f - arg0->unk50 < var_f28) {
            temp_f31 /= var_f28;
            temp_f30 /= var_f28;
            arg0->unk28.x = temp_f31 * (700.0f - arg0->unk50);
            arg0->unk28.z = -120.0f + temp_f30 * (700.0f - arg0->unk50);
        }
    }
}

void fn_1_7688(UnkM447Struct_04 *arg0)
{
    float sp14[3]; // Vec?
    float sp8[3]; // Vec?
    UnkM447Struct_04 *temp_r30;
    s32 var_r26;
    s32 i;

    for (i = 0; i < 2; i++) {
        temp_r30 = lbl_1_bss_98[i];
        if (!temp_r30 || temp_r30 == arg0) {
            continue;
        }
        sp14[0] = arg0->unk28.x;
        sp14[1] = arg0->unk28.z;
        sp14[2] = arg0->unk50;
        sp8[0] = temp_r30->unk28.x;
        sp8[1] = temp_r30->unk28.z;
        sp8[2] = temp_r30->unk50;
        var_r26 = (temp_r30->unk24 == 1) ? 1 : 0;
        if (fn_1_879C(sp14, sp8, 1, var_r26) == 0) {
            continue;
        }
        switch (arg0->unk24) {
            case 1:
                arg0->unk28.x = sp14[0];
                arg0->unk28.z = sp14[1];
                temp_r30->unk28.x = sp8[0];
                temp_r30->unk28.z = sp8[1];
                arg0->unk0C = 0;
                break;
            case 6:
            case 7:
                arg0->unk28.x = sp14[0];
                arg0->unk28.z = sp14[1];
                if (ABS(arg0->unk28.z - temp_r30->unk28.z) < 2.0f) {
                    arg0->unk28.z += 55.0f * (0.0f > arg0->unk28.z ? -1 : 1);
                }
                arg0->unk0C = 0;
                break;
        }
        switch (arg0->unk24) {
            case 1:
                fn_1_72A8(arg0);
                fn_1_72A8(temp_r30);
                break;
        }
    }
}

void fn_1_78A8(UnkM447Struct_04 *arg0)
{
    float sp20[3]; // Vec?
    float sp14[3]; // Vec?
    Vec sp8;
    s32 i;

    sp20[0] = arg0->unk28.x;
    sp20[1] = arg0->unk28.z;
    sp20[2] = arg0->unk50;
    for (i = 0; i < 5; i++) {
        if (lbl_1_bss_10->unk54[i] != 0) {
            continue;
        }
        fn_1_1ED4(i, &sp8);
        sp14[0] = sp8.x;
        sp14[1] = sp8.z;
        sp14[2] = 35.0f;
        if (fn_1_879C(sp20, sp14, 1, 0) != 0) {
            arg0->unk28.x = sp20[0];
            arg0->unk28.z = sp20[1];
            arg0->unk0C = 0;
        }
    }
}

s32 fn_1_7984(UnkM447Struct_04 *arg0)
{
    float sp20[3]; // Vec?
    float sp14[3]; // Vec?
    Vec sp8;
    s32 i;

    sp20[0] = arg0->unk28.x;
    sp20[1] = arg0->unk28.z;
    sp20[2] = arg0->unk50;
    for (i = 0; i < 5; i++) {
        fn_1_1ED4(i, &sp8);
        sp14[0] = sp8.x;
        sp14[1] = sp8.z;
        sp14[2] = 40.0f;
        if (fn_1_879C(sp20, sp14, 0, 0) != 0) {
            return i;
        }
    }
    return 5;
}

void fn_1_7A34(UnkM447Struct_04 *arg0)
{
    espDispOn(arg0->unk7C[1]);
    espDispOn(arg0->unk7C[0]);
}

void fn_1_7A6C(UnkM447Struct_04 *arg0)
{
    espDispOff(arg0->unk7C[1]);
    espDispOff(arg0->unk7C[0]);
}

void fn_1_7AA4(UnkM447Struct_04 *arg0, s32 arg1, s32 arg2)
{
    if (arg0->unk1C == 0) {
        switch (arg1) {
            case 0:
                omVibrate(arg0->unk00, arg2, 6, 6);
                return;
            case 1:
                omVibrate(arg0->unk00, arg2, 4, 2);
                return;
            case 2:
                omVibrate(arg0->unk00, arg2, 12, 0);
                break;
        }
    }
}
