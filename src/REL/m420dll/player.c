#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/objsub.h"
#include "game/pad.h"

#include "REL/m420dll.h"

typedef void (*M420DllUnkFunc)(M420DllPlayerStruct *);

typedef struct M420DllUnkStruct2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} M420DllUnkStruct2; /* size = 0x20 */

void fn_1_1F14(void);
void fn_1_1F54(M420DllPlayerStruct *arg0);
void fn_1_1F94(M420DllPlayerStruct *arg0);
void fn_1_200C(M420DllPlayerStruct *arg0);
void fn_1_20EC(M420DllPlayerStruct *arg0);
void fn_1_211C(M420DllPlayerStruct *arg0);
void fn_1_2174(M420DllPlayerStruct *arg0);
void fn_1_2260(M420DllPlayerStruct *arg0);
void fn_1_22CC(M420DllPlayerStruct *arg0);
void fn_1_276C(M420DllPlayerStruct *arg0);
void fn_1_2CE0(M420DllPlayerStruct *arg0);
void fn_1_2D7C(M420DllPlayerStruct *arg0);
void fn_1_2EA8(M420DllPlayerStruct *arg0);
void fn_1_3098(M420DllPlayerStruct *arg0);
void fn_1_326C(M420DllPlayerStruct *arg0);
void fn_1_3450(M420DllPlayerStruct *arg0);
s32 fn_1_34AC(M420DllPlayerStruct *arg0);
void fn_1_355C(M420DllPlayerStruct *arg0);
void fn_1_36E4(M420DllPlayerStruct *arg0);
void fn_1_374C(M420DllPlayerStruct *arg0);
void fn_1_378C(M420DllPlayerStruct *arg0);
void fn_1_3854(void);
void fn_1_3970(M420DllPlayerStruct *arg0);
void fn_1_3F94(M420DllPlayerStruct *arg0);
void fn_1_4294(M420DllPlayerStruct *arg0);
void fn_1_4574(M420DllPlayerStruct *arg0);
void fn_1_476C(M420DllPlayerStruct *arg0);

M420DllUnkStruct2 lbl_1_data_50[4] = {
    { 0x19, 0x01, 0x2A, 0x08, 0x2D, 0x10, 0x01, 0x01 },
    { 0x19, 0x01, 0x22, 0x06, 0x22, 0x0C, 0x01, 0x01 },
    { 0x19, 0x01, 0x1B, 0x05, 0x14, 0x0A, 0x01, 0x01 },
    { 0x19, 0x01, 0x14, 0x04, 0x0A, 0x08, 0x01, 0x01 },
};

static const s32 lbl_1_rodata_F8[8][0xB] = {
    {
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x68),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x69),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x6A),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x35),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x6B),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x6E),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x49),
        0x33001B,
    },
    {
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x18),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x68),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x69),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x6A),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x35),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x6B),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x6E),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x49),
        0x33001C,
    },
    {
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x18),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x68),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x69),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x6A),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x35),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x6B),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x6E),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x49),
        0x33001D,
    },
    {
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x18),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x68),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x69),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x6A),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x35),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x6B),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x6E),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x49),
        0x33001E,
    },
    {
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x18),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x68),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x69),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x6A),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x35),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x6B),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x6E),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x49),
        0x33001F,
    },
    {
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x18),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x68),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x69),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x6A),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x35),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x6B),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x6E),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x49),
        0x330020,
    },
    {
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x18),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x68),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x69),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x6A),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x35),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x6B),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x6E),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x49),
        0x330021,
    },
    {
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x17),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x18),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x68),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x69),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x6A),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x35),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x6B),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x6E),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x49),
        0x330022,
    },
};
static const Vec lbl_1_rodata_258[4][2] = {
    { { -372.0f, 300.0f, -220.0f }, { 0.0f, 50.0f, 0.0f } },
    { { 435.0f, 300.0f, -260.0f }, { 0.0f, 140.0f, 0.0f } },
    { { 315.0f, 300.0f, -153.0f }, { 0.0f, 140.0f, 0.0f } },
    { { 195.0f, 300.0f, -46.0f }, { 0.0f, 140.0f, 0.0f } },
};

M420DllPlayerStruct *fn_1_1B8C(s32 arg0, s32 arg1)
{
    M420DllPlayerStruct *var_r31;
    s32 var_r30;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M420DllPlayerStruct), MEMORY_DEFAULT_NUM);
    if (!var_r31) {
        OSReport("M420PlayerCreate ERROR...\n");
        return NULL;
    }
    var_r31->unk_04 = arg0;
    var_r31->unk_4C = arg1;
    var_r31->unk_08 = GWPlayerCfg[arg0].diff;
    var_r31->unk_00_field0 = GWPlayerCfg[arg0].iscom;
    var_r31->unk_0A = GWPlayerCfg[arg0].character;
    var_r31->unk_0C = GWPlayerCfg[arg0].pad_idx;
    var_r31->unk_10 = lbl_1_rodata_258[arg1][0];
    var_r31->unk_1C = lbl_1_rodata_258[arg1][1];
    var_r31->unk_48 = 0;
    var_r31->unk_50 = 0;
    var_r31->unk_00_field2 = 0;
    var_r31->unk_00_field1 = 0;
    var_r31->unk_E8 = NULL;
    for (var_r30 = 0; var_r30 < 0xA; var_r30++) {
        var_r31->unk_84[var_r30] = 7;
    }
    fn_1_1F54(var_r31);
    fn_1_1F94(var_r31);

    switch (arg1) {
        case 0:
            if (var_r31->unk_0A == 5) {
                CharModelMotionSet(var_r31->unk_0A, var_r31->unk_AE[0xA]);
                Hu3DMotionStartEndSet(var_r31->unk_AC, 0.0f, 1.0f);
                Hu3DMotionTimeSet(var_r31->unk_AC, 0.0f);
            }
            else {
                CharModelMotionSet(var_r31->unk_0A, var_r31->unk_AE[0]);
            }
            break;
        case 1:
        case 2:
        case 3:
            var_r31->unk_1C.y = 0.0f;
            CharModelMotionSet(var_r31->unk_0A, var_r31->unk_AE[0]);
            break;
        default:
            break;
    }

    CharModelMotionDataClose(var_r31->unk_0A);
    fn_1_200C(var_r31);
    var_r31->unk_40 = HuPrcChildCreate(fn_1_1F14, 0x64, 0x5000, 0, lbl_1_bss_4);
    var_r31->unk_40->user_data = var_r31;
    return var_r31;
}

void fn_1_1E14(M420DllPlayerStruct *arg0)
{
    fn_1_2174(arg0);
    fn_1_211C(arg0);
    fn_1_20EC(arg0);
    HuPrcKill(arg0->unk_40);
    HuMemDirectFree(arg0);
}

void fn_1_1E64(M420DllPlayerStruct *arg0, s32 arg1, s32 arg2)
{
    switch (arg1) {
        case 0:
            omVibrate(arg0->unk_04, arg2, 6, 6);
            break;
        case 1:
            omVibrate(arg0->unk_04, arg2, 4, 2);
            break;
        case 2:
            omVibrate(arg0->unk_04, arg2, 0xC, 0);
            break;
    }
}

M420DllUnkFunc lbl_1_data_EC[0xC] = {
    fn_1_2260,
    fn_1_22CC,
    fn_1_2D7C,
    fn_1_276C,
    fn_1_2CE0,
    fn_1_2EA8,
    fn_1_2260,
    fn_1_4574,
    fn_1_476C,
    fn_1_3F94,
    fn_1_4294,
    fn_1_3970,
};

void fn_1_1F14(void)
{
    M420DllPlayerStruct *var_r31 = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        lbl_1_data_EC[var_r31->unk_48](var_r31);
    }
}

void fn_1_1F54(M420DllPlayerStruct *arg0)
{
    arg0->unk_AC = CharModelCreate(arg0->unk_0A, 2);
    Hu3DModelShadowSet(arg0->unk_AC);
}

void fn_1_1F94(M420DllPlayerStruct *arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        arg0->unk_AE[var_r31] = CharModelMotionCreate(arg0->unk_0A, lbl_1_rodata_F8[arg0->unk_0A][var_r31]);
    }
}

void fn_1_200C(M420DllPlayerStruct *arg0)
{
    s32 var_r30;

    for (var_r30 = 0; var_r30 <= 9; var_r30++) {
        arg0->unk_C4[var_r30] = espEntry(0x330018, 0, 0);
        espDispOff(arg0->unk_C4[var_r30]);
    }
    switch (arg0->unk_4C) {
        case 0:
            arg0->unk_D8 = espEntry(0x330019, 1, 0);
            break;
        case 1:
        case 2:
        case 3:
            arg0->unk_D8 = espEntry(0x33001A, 1, 0);
            break;
        default:
            break;
    }
    espDispOff(arg0->unk_D8);
    espTPLvlSet(arg0->unk_D8, 0.8f);
}

void fn_1_20EC(M420DllPlayerStruct *arg0)
{
    CharModelKill(arg0->unk_0A);
}

void fn_1_211C(M420DllPlayerStruct *arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        CharModelMotionKill(arg0->unk_0A, arg0->unk_AE[var_r31]);
    }
}

void fn_1_2174(M420DllPlayerStruct *arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0xB; var_r31++) {
        espKill(arg0->unk_C4[var_r31]);
    }
}

void fn_1_21C8(M420DllPlayerStruct *arg0, Vec *arg1, s32 arg2, s32 arg3)
{
    arg0->unk_34 = *arg1;
    arg0->unk_28 = arg0->unk_1C;
    arg0->unk_DC = 0.0f;
    arg0->unk_E0 = 1.0f / arg2;
    arg0->unk_E4 = arg3;
    arg0->unk_00_field2 = 1;
}

void fn_1_2260(M420DllPlayerStruct *arg0)
{
    s32 var_r30;
    s32 var_r29;

    while (TRUE) {
        for (var_r30 = 0; var_r30 < 1; var_r30++) {
            fn_1_355C(arg0);
            var_r29 = arg0->unk_48;
            HuPrcVSleep();
            if (arg0->unk_48 != var_r29) {
                return;
            }
        }
    }
}

#define WAITMODECHG(player, maxTime)                                                                                                                 \
    do {                                                                                                                                             \
        s32 time;                                                                                                                                    \
        s32 mode;                                                                                                                                    \
        for (time = 0; time < maxTime; time++) {                                                                                                     \
            fn_1_355C(arg0);                                                                                                                         \
            mode = arg0->unk_48;                                                                                                                     \
            HuPrcVSleep();                                                                                                                           \
            if (arg0->unk_48 != mode) {                                                                                                              \
                return;                                                                                                                              \
            }                                                                                                                                        \
        }                                                                                                                                            \
    } while (0)

void fn_1_22CC(M420DllPlayerStruct *arg0)
{
    float var_f31;
    float var_f30;
    M420DllUnkStruct2 *var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r30 = &lbl_1_data_50[arg0->unk_08];
    fn_1_3098(arg0);
    CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[8], 0.0f, 10.0f, 0x40000001);
    arg0->unk_50 = 0;
    arg0->unk_58 = var_r30->unk_00 + (fn_1_8944() % var_r30->unk_04);

    while (arg0->unk_50 < 6) {
        fn_1_326C(arg0);
        do {
            if (arg0->unk_00_field0 == 0) {
                var_r29 = fn_1_34AC(arg0);
            }
            else if (arg0->unk_58 > 0) {
                arg0->unk_58--;
                var_r29 = 0;
            }
            else if ((fn_1_8944() % 30) != 0) {
                var_r29 = 1;
                arg0->unk_58 = (var_r30->unk_08 - (var_r30->unk_0C / 2)) + (fn_1_8944() % var_r30->unk_0C);
            }
            else {
                var_r29 = 2;
                arg0->unk_58 = (var_r30->unk_08 - (var_r30->unk_0C / 2)) + (fn_1_8944() % var_r30->unk_0C);
            }
            switch (var_r29) {
                case 0:
                    WAITMODECHG(arg0, 1);
                    break;
                case 1:
                    var_f31 = 5.0f * arg0->unk_50;
                    var_f30 = 5.0f + var_f31;
                    CharModelMotionSet(arg0->unk_0A, arg0->unk_AE[5]);
                    Hu3DMotionStartEndSet(arg0->unk_AC, var_f31, var_f30);
                    Hu3DMotionTimeSet(arg0->unk_AC, var_f31);
                    Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_REV);
                    arg0->unk_5C[arg0->unk_50++] = 1;
                    HuAudFXPlay(0x5F4);
                    fn_1_60F0();
                    WAITMODECHG(arg0, 5);
                    break;
                case 2:
                    if (arg0->unk_50 <= 0) {
                        WAITMODECHG(arg0, 1);
                    }
                    else {
                        Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_PAUSE);
                        Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_LOOP);
                        Hu3DModelAttrSet(arg0->unk_AC, HU3D_MOTATTR_REV);
                        fn_1_63EC();
                        while (!Hu3DMotionEndCheck(arg0->unk_AC))
                            WAITMODECHG(arg0, 1);
                        for (var_r28 = 0; var_r28 < 0xA; var_r28++) {
                            arg0->unk_5C[var_r28] = 0;
                        }
                        arg0->unk_50 = 0;
                        var_f31 = 0.0f;
                        var_f30 = 0.0f;
                        CharModelMotionSet(arg0->unk_0A, arg0->unk_AE[5]);
                        Hu3DMotionStartEndSet(arg0->unk_AC, var_f31, var_f30);
                        Hu3DMotionTimeSet(arg0->unk_AC, var_f31);
                        Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_LOOP);
                    }
                    break;
                default:
                    break;
            }
        } while (var_r29 == 0);
    }
    fn_1_326C(arg0);
    WAITMODECHG(arg0, 5);
    fn_1_3450(arg0);
    arg0->unk_48 = 2;
}

void fn_1_276C(M420DllPlayerStruct *arg0)
{
    float var_f31;
    float var_f30;

    s32 var_r30;
    M420DllUnkStruct2 *var_r29 = &lbl_1_data_50[arg0->unk_08];
    if (arg0->unk_4C == 1) {
        HuAudFXPlay(0x5F1);
        fn_1_669C(1);
        fn_1_6554();
        WAITMODECHG(arg0, 15);
        CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[7], 0.0f, 6.0f, 0);
        WAITMODECHG(arg0, 6);
        fn_1_669C(0);
        fn_1_36E4(arg0);
        HuAudFXPlay(0x5F2);
    }
    fn_1_3098(arg0);
    arg0->unk_50 = 0;
    arg0->unk_58 = var_r29->unk_10 + (fn_1_8944() % var_r29->unk_14);
    while (arg0->unk_50 < 1) {
        fn_1_326C(arg0);
        do {
            if (arg0->unk_00_field0 == 0) {
                var_r30 = fn_1_34AC(arg0);
            }
            else if (arg0->unk_58 > 0) {
                arg0->unk_58--;
                var_r30 = 0;
            }
            else if (fn_1_8944() % 30) {
                var_r30 = 1;
            }
            else {
                var_r30 = 2;
            }
            switch (var_r30) {
                case 0:
                    WAITMODECHG(arg0, 1);
                    break;

                case 1:
                    if (arg0->unk_4C != 1) {
                        CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[7], 0.0f, 6.0f, 0);
                        WAITMODECHG(arg0, 6);
                        fn_1_374C(arg0->unk_E8);
                        fn_1_36E4(arg0);
                        HuAudFXPlay(0x5F2);
                    }
                    arg0->unk_5C[arg0->unk_50++] = 1;
                    switch (arg0->unk_4C) {
                        case 1:
                        case 2:
                            var_f31 = 0.0f;
                            var_f30 = 34.0f;
                            CharModelMotionSet(arg0->unk_0A, arg0->unk_AE[4]);
                            Hu3DMotionStartEndSet(arg0->unk_AC, var_f31, var_f30);
                            Hu3DMotionTimeSet(arg0->unk_AC, var_f31);
                            Hu3DMotionSpeedSet(arg0->unk_AC, 2.0f);
                            break;

                        case 3:
                            arg0->unk_48 = 5;
                            return;
                    }
                    break;

                case 2:
                    switch (arg0->unk_4C) {
                        case 1:
                            var_f31 = 0.0f;
                            var_f30 = 10.0f;
                            CharModelMotionSet(arg0->unk_0A, arg0->unk_AE[4]);
                            Hu3DMotionStartEndSet(arg0->unk_AC, var_f31, var_f30);
                            Hu3DMotionTimeSet(arg0->unk_AC, var_f31);
                            Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_PAUSE);
                            WAITMODECHG(arg0, 30);
                            var_f31 = 60.0f;
                            var_f30 = 70.0f;
                            CharModelMotionSet(arg0->unk_0A, arg0->unk_AE[4]);
                            Hu3DMotionStartEndSet(arg0->unk_AC, var_f31, var_f30);
                            Hu3DMotionTimeSet(arg0->unk_AC, var_f31);
                            Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_PAUSE);
                            WAITMODECHG(arg0, 30);
                            break;

                        case 2:
                        case 3:
                            CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[9], 0.0f, 2.0f, 0);
                            WAITMODECHG(arg0, 60);
                            CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[0], 0.0f, 8.0f, 0);
                            break;
                    }
                    break;
            }
        } while (var_r30 == 0);
    }
    fn_1_326C(arg0);
    WAITMODECHG(arg0, 18);
    fn_1_3450(arg0);
    arg0->unk_48 = 6;
}

void fn_1_2CE0(M420DllPlayerStruct *arg0)
{
    CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[0], 0.0f, 30.0f, 0x40000001);

    WAITMODECHG(arg0, 35);
    arg0->unk_48 = 0;
}

void fn_1_2D7C(M420DllPlayerStruct *arg0)
{
    float var_f31;
    float var_f30;
    s32 var_r30;
    s32 var_r29;

    var_f30 = 0.0f;
    var_f31 = 30.0f;
    Hu3DMotionStartEndSet(arg0->unk_AC, var_f30, var_f31);
    Hu3DMotionTimeSet(arg0->unk_AC, var_f31);
    Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(arg0->unk_AC, HU3D_MOTATTR_REV);
    HuAudFXPlay(0x5F6);
    fn_1_6268();
    fn_1_5AA8(0, 22.5f);
    fn_1_1E64(arg0, 1, 0x1E);
    // fn_1_2260?
    for (var_r30 = 0; var_r30 < 0x1E; var_r30++) {
        fn_1_355C(arg0);
        var_r29 = arg0->unk_48;
        HuPrcVSleep();
        if (arg0->unk_48 != var_r29) {
            return;
        }
    }
    arg0->unk_48 = 0;
}

void fn_1_2EA8(M420DllPlayerStruct *arg0)
{
    s16 var_r30;

    fn_1_326C(arg0);
    CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[3], 0.0f, 1.0f, 0);
    var_r30 = fn_1_6660();

    Hu3DModelAttrReset(var_r30, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(var_r30, 0.0f);
    {
        s32 var_r30;
        s32 var_r29;
        for (var_r30 = 0; var_r30 < 24; var_r30++) {
            fn_1_355C(arg0);
            var_r29 = arg0->unk_48;
            HuPrcVSleep();
            if (arg0->unk_48 != var_r29) {
                return;
            }
        }
    }
    HuAudFXPlay(0x5F7);
    fn_1_636C();
    fn_1_1E64(arg0, 1, 0x1E);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_PAUSE);
    fn_1_5AA8(1, 22.5f);
    {
        s32 var_r30;
        s32 var_r29;
        for (var_r30 = 0; var_r30 < 20; var_r30++) {
            fn_1_355C(arg0);
            var_r29 = arg0->unk_48;
            HuPrcVSleep();
            if (arg0->unk_48 != var_r29) {
                return;
            }
        }
    }
    HuAudFXPlay(0x5F8);
    fn_1_3450(arg0);
    fn_1_378C(arg0);
    {
        s32 var_r30;
        s32 var_r29;
        for (var_r30 = 0; var_r30 < 20; var_r30++) {
            fn_1_355C(arg0);
            var_r29 = arg0->unk_48;
            HuPrcVSleep();
            if (arg0->unk_48 != var_r29) {
                return;
            }
        }
    }
    CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[0], 0.0f, 30.0f, 0x40000001);
    {
        s32 var_r30;
        s32 var_r29;
        for (var_r30 = 0; var_r30 < 25; var_r30++) {
            fn_1_355C(arg0);
            var_r29 = arg0->unk_48;
            HuPrcVSleep();
            if (arg0->unk_48 != var_r29) {
                return;
            }
        }
    }
    arg0->unk_48 = 6;
}

void fn_1_3098(M420DllPlayerStruct *arg0)
{
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    for (var_r30 = 0; var_r30 < 0xA; var_r30++) {
        arg0->unk_5C[var_r30] = 0;
    }
    arg0->unk_50 = 0;
    switch (arg0->unk_4C) {
        case 0:
            for (var_r29 = 0; var_r29 < 6;) {
                arg0->unk_84[var_r29] = fn_1_8944() % 7;
                if (arg0->unk_84[var_r29] == 6) {
                    arg0->unk_84[var_r29] = 0;
                }
                if ((var_r29 <= 0) || (arg0->unk_84[var_r29] != arg0->unk_84[var_r29 - 1])) {
                    for (var_r30 = 0, var_r28 = 0; var_r30 < var_r29; var_r30++) {
                        if (arg0->unk_84[var_r29] == arg0->unk_84[var_r30]) {
                            var_r28++;
                        }
                    }
                    if (var_r28 < 2) {
                        var_r29++;
                    }
                }
            }
            break;
        case 1:
        case 2:
        case 3:
            for (var_r30 = 0; var_r30 < 0xA; var_r30++) {
                arg0->unk_84[1] = arg0->unk_84[0];
                arg0->unk_84[0] = fn_1_8944() % 7;
                if (arg0->unk_84[0] == 6) {
                    arg0->unk_84[0] = 0;
                }
                if (arg0->unk_84[0] != arg0->unk_84[1]) {
                    break;
                }
            }
            break;
        default:
            break;
    }
}

static const s32 lbl_1_rodata_2F8[4] = { 6, 1, 1, 1 };

void fn_1_326C(M420DllPlayerStruct *arg0)
{
    Vec sp14;
    Vec sp8;

    s32 var_r30;
    s16 var_r29;
    s32 var_r28;
    s32 var_r26;

    sp14 = arg0->unk_10;
    sp14.y += 300.0f;
    Hu3D3Dto2D(&sp14, 1, &sp8);

    var_r26 = arg0->unk_4C == 0 ? -6 : 0;
    espPosSet(arg0->unk_D8, sp8.x + var_r26, 6.0f + sp8.y);
    espDispOn(arg0->unk_D8);
    var_r28 = lbl_1_rodata_2F8[arg0->unk_4C];
    sp8.x -= (var_r28 / 2) * 0x1E;
    for (var_r30 = 0; var_r30 < var_r28; var_r30++) {
        var_r29 = arg0->unk_C4[var_r30];
        if (arg0->unk_5C[var_r30] != 0) {
            espBankSet(var_r29, arg0->unk_84[var_r30] + 7);
        }
        else {
            espBankSet(var_r29, arg0->unk_84[var_r30]);
        }
        espPosSet(var_r29, sp8.x + var_r30 * 0x20, sp8.y);
        espDispOn(var_r29);
    }
}

void fn_1_3450(M420DllPlayerStruct *arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0xA; var_r31++) {
        espDispOff(arg0->unk_C4[var_r31]);
    }
    espDispOff(arg0->unk_D8);
}

static const s32 lbl_1_rodata_30C[7] = { 0x100, 0x200, 0x40, 0x20, 0x800, 0x400, 0x10 };

s32 fn_1_34AC(M420DllPlayerStruct *arg0)
{
    s32 var_r31;
    u16 var_r30;
    u16 var_r29;

    var_r31 = 0;
    var_r30 = HuPadBtnDown[arg0->unk_0C] & 0xF60;
    var_r29 = lbl_1_rodata_30C[arg0->unk_84[arg0->unk_50]];
    if (var_r30 != 0) {
        var_r31 = 2;
    }
    if (((var_r30 & var_r29) != 0) && ((var_r30 & ~var_r29) == 0)) {
        var_r31 = 1;
    }
    return var_r31;
}

void fn_1_355C(M420DllPlayerStruct *arg0)
{
    float var_f31;

    arg0 = HuPrcCurrentGet()->user_data;
    Hu3DModelPosSet(arg0->unk_AC, arg0->unk_10.x, arg0->unk_10.y, arg0->unk_10.z);
    if (arg0->unk_00_field2) {
        switch (arg0->unk_E4) {
            case 0:
                var_f31 = arg0->unk_DC;
                break;
            case 1:
                var_f31 = sind((90.0f * arg0->unk_DC));
                var_f31 *= var_f31;
                break;
        }
        arg0->unk_1C.x = arg0->unk_28.x + (var_f31 * (arg0->unk_34.x - arg0->unk_28.x));
        arg0->unk_1C.y = arg0->unk_28.y + (var_f31 * (arg0->unk_34.y - arg0->unk_28.y));
        arg0->unk_1C.z = arg0->unk_28.z + (var_f31 * (arg0->unk_34.z - arg0->unk_28.z));
        if ((arg0->unk_DC += arg0->unk_E0) >= 1.0f) {
            arg0->unk_1C = arg0->unk_34;
            arg0->unk_00_field2 = 0;
        }
    }
    Hu3DModelRotSet(arg0->unk_AC, arg0->unk_1C.x, arg0->unk_1C.y, arg0->unk_1C.z);
}

void fn_1_36E4(M420DllPlayerStruct *arg0)
{
    Hu3DModelHookSet(arg0->unk_AC, "test11_tex_we-itemhook-r", fn_1_6660());
    arg0->unk_00_field1 = 1;
    fn_1_1E64(arg0, 1, 0x14);
}

void fn_1_374C(M420DllPlayerStruct *arg0)
{
    Hu3DModelHookReset(arg0->unk_AC);
    arg0->unk_00_field1 = 0;
}

void fn_1_378C(M420DllPlayerStruct *arg0)
{
    Mtx sp20;
    Vec sp14;
    Vec sp8;

    if (arg0->unk_00_field1) {
        Hu3DModelObjMtxGet(arg0->unk_AC, "test11_tex_we-itemhook-r", sp20);
        Hu3DModelHookObjReset(arg0->unk_AC, "test11_tex_we-itemhook-r");
        Hu3DMtxTransGet(sp20, &sp14);
        Hu3DMtxRotGet(sp20, &sp8);
        Hu3DModelPosSetV(fn_1_6660(), &sp14);
        Hu3DModelRotSetV(fn_1_6660(), &sp8);
    }
    HuPrcChildCreate(fn_1_3854, 0x64, 0x2000, 0, lbl_1_bss_4);
    arg0->unk_00_field1 = 0;
}

char lbl_1_data_135[1] = { 0 };

void fn_1_3854(void)
{
    Mtx sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;
    s16 var_r31;

    var_r31 = fn_1_6660();
    Hu3DModelObjMtxGet(var_r31, lbl_1_data_135, sp2C);
    Hu3DMtxRotGet(sp2C, &sp8);
    Hu3DMtxTransGet(sp2C, &sp20);
    var_f31 = 0.0f;

    while (var_f31 < 1.0f) {
        sp14.x = cosd((90.0f * var_f31));
        sp14.y = sp14.z = sp14.x;
        Hu3DModelScaleSet(var_r31, sp14.x, sp14.y, sp14.z);
        var_f31 += 0.05f;
        HuPrcVSleep();
    }
    fn_1_6728();
    sp14.x = sp14.y = sp14.z = 1.0f;
    Hu3DModelScaleSet(var_r31, sp14.x, sp14.y, sp14.z);
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_3970(M420DllPlayerStruct *arg0)
{
    Vec sp38;

    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    if (arg0->unk_00_field1) {
        fn_1_378C(arg0);
    }
    else if (arg0->unk_4C == 1) {
        fn_1_378C(arg0);
    }
    fn_1_3450(arg0);
    if (arg0->unk_4C == 0) {
        Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(arg0->unk_AC, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(arg0->unk_AC, HU3D_MOTATTR_REV);
        fn_1_63EC();
        CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[6], 0.0f, 32.0f, 0);
        Hu3DMotionShiftStartEndSet(arg0->unk_AC, 0.0f, 59.0f);
        sp38 = arg0->unk_1C;
        sp38.y = 0.0f;
        fn_1_21C8(arg0, &sp38, 60, 1);
    }
    for (var_r27 = 0; var_r27 < 0x3C; var_r27++) {
        fn_1_355C(arg0);
        var_r25 = arg0->unk_48;
        HuPrcVSleep();
        if (arg0->unk_48 != var_r25) {
            return;
        }
    }
    CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[0], 0.0f, 16.0f, 0);
    for (var_r26 = 0; var_r26 < 0x3C; var_r26++) {
        fn_1_355C(arg0);
        var_r24 = arg0->unk_48;
        HuPrcVSleep();
        if (arg0->unk_48 != var_r24) {
            return;
        }
    }
    arg0->unk_48 = 0;
}

void fn_1_3F94(M420DllPlayerStruct *arg0)
{
    Vec sp8;
    s32 var_r29;
    s32 var_r28;

    if (arg0->unk_4C != 0) {
        CharModelMotionSet(arg0->unk_0A, arg0->unk_AE[6]);
        Hu3DMotionStartEndSet(arg0->unk_AC, 60.0f, 119.0f);
        Hu3DMotionTimeSet(arg0->unk_AC, 60.0f);
        sp8 = arg0->unk_1C;
        sp8.y = lbl_1_rodata_258[arg0->unk_4C][1].y;
        fn_1_21C8(arg0, &sp8, 60, 1);
        while (arg0->unk_00_field2 != 0) {
            for (var_r28 = 0; var_r28 < 1; var_r28++) {
                fn_1_355C(arg0);
                var_r29 = arg0->unk_48;
                HuPrcVSleep();
                if (arg0->unk_48 != var_r29) {
                    return;
                }
            }
        }
        CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[0], 0.0f, 4.0f, 0);
    }
    arg0->unk_48 = 0;
}

void fn_1_4294(M420DllPlayerStruct *arg0)
{
    Vec sp8;
    s32 var_r29;
    s32 var_r28;

    if (arg0->unk_4C != 0) {
        CharModelMotionSet(arg0->unk_0A, arg0->unk_AE[6]);
        Hu3DMotionStartEndSet(arg0->unk_AC, 0.0f, 59.0f);
        sp8 = arg0->unk_1C;
        sp8.y = 0.0f;
        fn_1_21C8(arg0, &sp8, 60, 1);
        while (arg0->unk_00_field2 != 0) {
            for (var_r28 = 0; var_r28 < 1; var_r28++) {
                fn_1_355C(arg0);
                var_r29 = arg0->unk_48;
                HuPrcVSleep();
                if (arg0->unk_48 != var_r29) {
                    return;
                }
            }
        }
        CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[0], 0.0f, 8.0f, 0);
    }
    arg0->unk_48 = 0;
}

void fn_1_4574(M420DllPlayerStruct *arg0)
{
    CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[1], 0.0f, 4.0f, 0);
    fn_1_2260(arg0);
}

void fn_1_476C(M420DllPlayerStruct *arg0)
{
    CharModelMotionShiftSet(arg0->unk_0A, arg0->unk_AE[2], 0.0f, 4.0f, 0);
    fn_1_2260(arg0);
}
