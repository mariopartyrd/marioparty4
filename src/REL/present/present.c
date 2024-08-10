#include "ext_math.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/wipe.h"

#include "REL/present.h"

void fn_1_180C(omObjData *object, s32 arg1);
void fn_1_1928(omObjData *arg0);
void fn_1_1FA8(omObjData *object, s32 arg1);
void fn_1_20E8(omObjData *arg0);
void fn_1_268C(omObjData *object, float *arg1, float *arg2, float *arg3);
void fn_1_2708(omObjData *arg0, float arg8, s32 arg1);
void fn_1_2774(omObjData *arg0);
s32 fn_1_28F0(omObjData *object);
void fn_1_2924(omObjData *object);
s32 fn_1_2B84(omObjData *arg0, s32 arg1, s32 arg2);
s32 fn_1_2BCC(omObjData *object, s32 arg1);
s32 fn_1_2C5C(omObjData *object, s32 arg1);
s32 fn_1_3394(s32 arg0);
void fn_1_33AC(omObjData *arg0);
s32 fn_1_393C(s32 arg0, s32 arg1);

UnkPresentStruct3 lbl_1_data_50 = { { 0.0f, 400.0f, 0.0f }, { 0.0f, -400.0f, -500.0f }, { 255, 255, 255, 255 } };
omObjFunc lbl_1_data_6C[] = { NULL, fn_1_1928, fn_1_20E8, fn_1_33AC };

static const s32 lbl_1_rodata_A0[] = { 0x006E006C, 0x006E006B, 0x006E0000, 0x006E0001, 0x006E0002, 0x006E0003, 0x006E0004, 0x006E0005, 0x006E0006,
    0x006E0007, 0x006E0008, 0x006E0009, 0x006E000A, 0x006E000B, 0x006E000C, 0x006E000D, 0x006E000E, 0x006E000F, 0x006E0010, 0x006E0011, 0x006E0012,
    0x006E0013, 0x006E0014, 0x006E0015, 0x006E0016, 0x006E0017, 0x006E0018, 0x006E0019, 0x006E001A, 0x006E001B, 0x006E001C, 0x006E001D, 0x006E001E,
    0x006E001F, 0x006E0020, 0x006E0021, 0x006E0022, 0x006E0023, 0x006E0024, 0x006E0025, 0x006E0026, 0x006E0027, 0x006E0028, 0x006E0029, 0x006E002A,
    0x006E002B, 0x006E002C, 0x006E002D, 0x006E002E, 0x006E002F, 0x006E0030, 0x006E0031, 0x006E0032, 0x006E0033, 0x006E0034, 0x006E0035, 0x006E0036,
    0x006E0037, 0x006E0038, 0x006E0039, 0x006E003A, 0x006E003B, 0x006E003C, 0x006E003D, 0x006E003E, 0x006E003F, 0x006E0040, 0x006E0041, 0x006E0042,
    0x006E0043, 0x006E0044, 0x006E0045, 0x006E0046, 0x006E0047, 0x006E0048, 0x006E0049, 0x006E004A, 0x006E004B, 0x006E004C, 0x006E004D, 0x006E004E,
    0x006E004F, 0x006E0050, 0x006E0051, 0x006E0052, 0x006E0053, 0x006E0054, 0x006E0055, 0x006E0056, 0x006E0057, 0x006E0058, 0x006E0059, 0x006E005A,
    0x006E005B, 0x006E005C, 0x006E005D, 0x006E005E, 0x006E005F, 0x006E0060, 0x006E0061, 0x006E0062, 0x006E0063, 0x006E0064, 0x006E0065, 0x006E0066,
    0x006E0067, 0x006E0068, 0x006E0069, 0x006E006A, 0x006E006D, 0x006E006F, 0x006E0071, 0x006E0073, 0x006E0075, 0x006E0077, 0x006E0079, 0x006E007B,
    0x006E007D, 0x006E006E, 0x006E0070, 0x006E0072, 0x006E0074, 0x006E0076, 0x006E0078, 0x006E007A, 0x006E007C, 0x006E007F, 0x006E0080, 0x006E0081,
    0x006E0082, 0x006E0083, 0x006E0084, 0x006E0085, 0x006E0086 };

static const UnkPresentNestedOuterStruct lbl_1_rodata_2B8[] = {
    { 0x00000006, { { 0x00000002, 0x00000008, 0x00320006, 0x00320042 }, { 0x00000003, 0x00000009, 0x00320007, 0x00320043 },
          { 0x00000004, 0x0000000A, 0x00320008, 0x00320044 }, { 0x00000005, 0x0000000B, 0x00320009, 0x00320045 },
          { 0x00000006, 0x0000000C, 0x0032000A, 0x00320046 }, { 0x00000007, 0x0000000D, 0x0032000B, 0x00320047 },
         },
	},
	{ 0x00000006, { { 0x0000000E, 0x00000014, 0x0032000C, 0x00320048 }, { 0x0000000F, 0x00000015, 0x0032000D, 0x00320049 },
          { 0x00000010, 0x00000016, 0x0032000E, 0x0032004A }, { 0x00000011, 0x00000017, 0x0032000F, 0x0032004B },
          { 0x00000012, 0x00000018, 0x00320010, 0x0032004C }, { 0x00000013, 0x00000019, 0x00320011, 0x0032004D },
         },
	},
	{ 0x00000006, { { 0x0000001A, 0x00000020, 0x00320012, 0x0032004E }, { 0x0000001B, 0x00000021, 0x00320013, 0x0032004F },
          { 0x0000001C, 0x00000022, 0x00320014, 0x00320050 }, { 0x0000001D, 0x00000023, 0x00320015, 0x00320051 },
          { 0x0000001E, 0x00000024, 0x00320016, 0x00320052 }, { 0x0000001F, 0x00000025, 0x00320017, 0x00320053 },
         },
	},
	{ 0x00000006, { { 0x00000026, 0x0000002C, 0x00320018, 0x00320054 }, { 0x00000027, 0x0000002D, 0x00320019, 0x00320055 },
          { 0x00000028, 0x0000002E, 0x0032001A, 0x00320056 }, { 0x00000029, 0x0000002F, 0x0032001B, 0x00320057 },
          { 0x0000002A, 0x00000030, 0x0032001C, 0x00320058 }, { 0x0000002B, 0x00000031, 0x0032001D, 0x00320059 },
         },
	},
	{ 0x00000006, { { 0x00000032, 0x00000038, 0x0032001E, 0x0032005A }, { 0x00000033, 0x00000039, 0x0032001F, 0x0032005B },
          { 0x00000034, 0x0000003A, 0x00320020, 0x0032005C }, { 0x00000035, 0x0000003B, 0x00320021, 0x0032005D },
          { 0x00000036, 0x0000003C, 0x00320022, 0x0032005E }, { 0x00000037, 0x0000003D, 0x00320023, 0x0032005F },
         },
	},
	{ 0x00000001, { { 0x00000001, 0xFFFFFFFF, 0x00320041, 0x00320041 } } },
	{ 0x00000006, { { 0x0000003E, 0x00000044, 0x00320024, 0x00320060 }, { 0x0000003F, 0x00000045, 0x00320025, 0x00320061 },
          { 0x00000040, 0x00000046, 0x00320026, 0x00320062 }, { 0x00000041, 0x00000047, 0x00320027, 0x00320063 },
          { 0x00000042, 0x00000048, 0x00320028, 0x00320064 }, { 0x00000043, 0x00000049, 0x00320029, 0x00320065 },
         },
	},
	{ 0x00000006, { { 0x0000004A, 0x00000050, 0x0032002A, 0x00320066 }, { 0x0000004B, 0x00000051, 0x0032002B, 0x00320067 },
          { 0x0000004C, 0x00000052, 0x0032002C, 0x00320068 }, { 0x0000004D, 0x00000053, 0x0032002D, 0x00320069 },
          { 0x0000004E, 0x00000054, 0x0032002E, 0x0032006A }, { 0x0000004F, 0x00000055, 0x0032002F, 0x0032006B },
         },
	},
	{ 0x00000006, { { 0x00000056, 0x0000005C, 0x00320030, 0x0032006C }, { 0x00000057, 0x0000005D, 0x00320031, 0x0032006D },
          { 0x00000058, 0x0000005E, 0x00320032, 0x0032006E }, { 0x00000059, 0x0000005F, 0x00320033, 0x0032006F },
          { 0x0000005A, 0x00000060, 0x00320034, 0x00320070 }, { 0x0000005B, 0x00000061, 0x00320035, 0x00320071 },
         },
	},
	{ 0x0000000B, { { 0x00000062, 0xFFFFFFFF, 0x00320036, 0x00320072 }, { 0x00000063, 0xFFFFFFFF, 0x00320037, 0x00320073 },
          { 0x00000064, 0xFFFFFFFF, 0x00320038, 0x00320074 }, { 0x00000065, 0xFFFFFFFF, 0x00320039, 0x00320075 },
          { 0x00000066, 0xFFFFFFFF, 0x0032003A, 0x00320076 }, { 0x00000067, 0xFFFFFFFF, 0x0032003B, 0x00320077 },
          { 0x00000068, 0xFFFFFFFF, 0x0032003C, 0x00320078 }, { 0x00000069, 0xFFFFFFFF, 0x0032003D, 0x00320079 },
          { 0x0000006A, 0xFFFFFFFF, 0x0032003E, 0x0032007A }, { 0x0000006B, 0xFFFFFFFF, 0x0032003F, 0x0032007B },
          { 0x0000006C, 0xFFFFFFFF, 0x00320040, 0x0032007C }
         },
	},
};

omObjData *fn_1_1458(void)
{
    UnkPresentStruct2 *var_r31;
    s32 var_r30;
    omObjData *var_r29;
    s32 var_r28;
    s16 var_r27;
    LightData *var_r26;

    var_r29 = omAddObjEx(lbl_1_bss_4, 1003, 0, 0, 1, NULL);
    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, 868, MEMORY_DEFAULT_NUM);
    var_r29->data = var_r31;
    var_r31->unk_234 = 0;
    var_r31->unk_238 = 0;
    var_r31->unk_23C = 0.0f;
    var_r31->unk_248 = 1.0f;
    var_r31->unk_250 = 0.0f;

    for (var_r30 = 0; var_r30 < 60; var_r30++) {
        var_r31->unk_270[var_r30] = GWGameStat.present[var_r30];
    }

    for (var_r30 = 0; var_r30 < 59; var_r30++) {
        if (!var_r31->unk_270[var_r30]) {
            break;
        }
    }
    if (var_r30 == 59) {
        var_r31->unk_270[59] = 1;
    }
    Hu3DLighInit();
    var_r27 = Hu3DGLightCreateV(&lbl_1_data_50.unk_00, &lbl_1_data_50.unk_0C, &lbl_1_data_50.unk_18);
    Hu3DGLightInfinitytSet(var_r27);
    Hu3DGLightStaticSet(var_r27, 1);
    var_r26 = &Hu3DGlobalLight[var_r27];
    var_r26->unk_00 = var_r26->unk_00 | 0x8000;

    for (var_r30 = 0; var_r30 < 134; var_r30++) {
        var_r31->unk_10[var_r30] = omAddObjEx(lbl_1_bss_4, 1003, 1, 0, 1, NULL);
        var_r31->unk_10[var_r30]->model[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_A0[var_r30], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelLayerSet(var_r31->unk_10[var_r30]->model[0], 0);
        Hu3DModelAttrSet(var_r31->unk_10[var_r30]->model[0], 1);
    }

    for (var_r28 = 0; var_r28 < 8; var_r28++) {
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            Hu3DModelLayerSet(var_r31->unk_10[var_r30 + 2 + var_r28 * 6 * 2]->model[0], 1);
        }
    }
    Hu3DModelShadowMapSet(var_r31->unk_10[0]->model[0]);
    fn_1_2924(var_r29);
    var_r31->sprite = espEntry(7209095, 0, 0);
    espDispOff(var_r31->sprite);
    var_r31->unk_228 = fn_1_3EA4(0);
    var_r31->unk_22C = fn_1_3EA4(1);
    fn_1_2708(var_r29, var_r31->unk_234 * 36.0f, 1);
    fn_1_2774(var_r29);
    fn_1_180C(var_r29, 0);

    (void)var_r27;
    return var_r29;
}

void fn_1_1784(omObjData *object)
{
    UnkPresentStruct2 *var_r31;
    s32 var_r30;
    void *var_r29;

    var_r31 = object->data;
    fn_1_4040(var_r31->unk_228);
    fn_1_4040(var_r31->unk_22C);

    for (var_r30 = 0; var_r30 < 134; var_r30++) {
        Hu3DModelKill(var_r31->unk_10[var_r30]->model[0]);
    }
    espKill(var_r31->sprite);
    HuMemDirectFree(var_r31);
}

void fn_1_180C(omObjData *object, s32 arg1)
{
    UnkPresentStruct2 *var_r31;

    var_r31 = object->data;
    var_r31->unk_0C = arg1;
    object->func = lbl_1_data_6C[arg1];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 fn_1_1850(omObjData *object)
{
    UnkPresentStruct2 *var_r31;

    var_r31 = object->data;
    return var_r31->unk_0C;
}

static const s32 lbl_1_rodata_9D8[] = { 0, 1, 2, 3, 4, 6, 7, 8 };
static const s32 lbl_1_rodata_9F8[] = { 0, 1, 2, 3, 4, 0, 5, 6, 7, 0 };

void fn_1_186C(omObjData *object, s32 arg1)
{
    UnkPresentStruct2 *var_r31;

    var_r31 = object->data;
    if (arg1 < 48) {
        var_r31->unk_234 = lbl_1_rodata_9D8[arg1 / 6];
        var_r31->unk_238 = arg1 % 6;
        return;
    }
    if (arg1 < 59) {
        var_r31->unk_234 = 9;
        var_r31->unk_238 = (arg1 - 48) % 11;
        return;
    }
    var_r31->unk_234 = 5;
    var_r31->unk_238 = 0;
}

void fn_1_1928(omObjData *object)
{
    Vec sp8;
    UnkPresentStruct2 *var_r31;
    s32 var_r29;
    UnkPresentStruct2 *var_r28;

    var_r31 = object->data;
    switch (object->unk10) {
    case 0:
        var_r31->unk_00 = 0;
        var_r31->unk_08 = 0;
        object->unk10 = 1;
    case 1:
        if (var_r31->unk_08) {
            fn_1_920(lbl_1_bss_8, 0.0f, 220.0f, 250.0f, 30);
            fn_1_9A4(lbl_1_bss_8, 0.0f, 420.0f, -600.0f, 30);
        } else {
            fn_1_920(lbl_1_bss_8, 0.0f, 220.0f, 250.0f, 30);
            fn_1_9A4(lbl_1_bss_8, 0.0f, 0.0f, -600.0f, 30);
        }
        object->unk10 = 2;
    case 2:
        if (!fn_1_B6C(lbl_1_bss_8) && !var_r31->unk_228->unk_20 && !fn_1_28F0(object)) {
            fn_1_4080(var_r31->unk_228);
            fn_1_4080(var_r31->unk_22C);
            if (var_r31->unk_08) {
                var_r29 = 0x320080;
            } else if (var_r31->unk_234 == 5) {
                var_r29 = 0x320085;
            } else {
                var_r29 = 0x32007e;
            }
            fn_1_40B0(var_r31->unk_22C, var_r29);
            switch (var_r31->unk_234) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
            case 7:
            case 8:
                if (var_r31->unk_08) {
                    if (fn_1_2B84(object, var_r31->unk_234, 5)) {
                        var_r29 = 0x320005;
                    } else {
                        var_r29 = 0x320082;
                    }
                } else if (fn_1_2BCC(object, var_r31->unk_234) > 0) {
                    var_r29 = 0x320001;
                } else {
                    var_r29 = 0x320081;
                }
                fn_1_40B0(var_r31->unk_228, var_r29);
                fn_1_4104(var_r31->unk_228, lbl_1_rodata_9F8[var_r31->unk_234], 0);
                break;
            case 5:
                if (fn_1_2B84(object, 5, 0)) {
                    var_r29 = 0x320041;
                } else {
                    var_r29 = 0x320084;
                }
                fn_1_40B0(var_r31->unk_228, var_r29);
                break;
            case 9:
                if (fn_1_2BCC(object, 9) > 0) {
                    var_r29 = 0x320083;
                } else {
                    var_r29 = 0x320081;
                }
                fn_1_40B0(var_r31->unk_228, var_r29);
                break;
            default:
                break;
            }
            if (var_r31->unk_08) {
                sp8.x = 0.0f;
                sp8.y = 600.0f;
                sp8.z = -500.0f;
            } else {
                sp8.x = 0.0f;
                sp8.y = 210.0f;
                sp8.z = -500.0f;
            }
            Hu3D3Dto2D(&sp8, 1, &sp8);
            sp8.y -= 15.0f;
            sp8.x -= 20.0f;
            espPosSet(var_r31->sprite, sp8.x, sp8.y);
            if (!var_r31->unk_00) {
                fn_1_144(var_r31->sprite, 1, 5);
                var_r31->unk_00 = 1;
            }
            object->unk10 = 3;
        }
        break;
    case 3:
        if (!var_r31->unk_228->unk_20) {
            if (fn_1_550(512) && !var_r31->unk_08) {
                fn_1_144(var_r31->sprite, 0, 5);
                var_r31->unk_00 = 0;
                fn_1_4098(var_r31->unk_228);
                fn_1_4098(var_r31->unk_22C);
                HuAudFXPlay(3);
                object->unk10 = 4;
            } else if (fn_1_550(256) && !var_r31->unk_08) {
                if (var_r31->unk_234 != 5) {
                    fn_1_144(var_r31->sprite, 0, 5);
                    var_r31->unk_00 = 0;
                    fn_1_4098(var_r31->unk_228);
                    fn_1_4098(var_r31->unk_22C);
                    HuAudFXPlay(2);
                    fn_1_180C(object, 2);
                }
            } else if (fn_1_584(8) && !var_r31->unk_08) {
                if ((var_r31->unk_234 != 5) && (var_r31->unk_234 != 9)) {
                    var_r31->unk_08 = 1;
                    fn_1_144(var_r31->sprite, 0, 5);
                    var_r31->unk_00 = 0;
                    fn_1_4098(var_r31->unk_228);
                    fn_1_4098(var_r31->unk_22C);
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
            } else if (fn_1_584(4) && var_r31->unk_08) {
                var_r31->unk_08 = 0;
                fn_1_144(var_r31->sprite, 0, 5);
                var_r31->unk_00 = 0;
                fn_1_4098(var_r31->unk_228);
                fn_1_4098(var_r31->unk_22C);
                HuAudFXPlay(0);
                object->unk10 = 1;
            } else if (fn_1_584(1)) {
                fn_1_1FA8(object, 1);
                HuAudFXPlay(0);
                object->unk10 = 2;
            } else if (fn_1_584(2)) {
                fn_1_1FA8(object, 2);
                HuAudFXPlay(0);
                object->unk10 = 2;
            }
        }
        break;
    case 4:
        fn_1_180C(object, 0);
        break;
    }
    fn_1_2774(object);
}

void fn_1_1FA8(omObjData *object, s32 arg1)
{
    UnkPresentStruct2 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    float var_f30;
    float var_f31;
    float var_f29;

    var_r31 = object->data;

    for (var_r30 = 0, var_f31 = 0.0f;; var_r30++) {
        var_f31 += 36.0f;
        if (arg1 == 1) {
            var_r29 = -1;
        } else {
            var_r29 = 1;
        }
        var_r31->unk_234 = var_r31->unk_234 + var_r29;
        if (var_r31->unk_234 < 0) {
            var_r31->unk_234 = 9;
        } else if (var_r31->unk_234 >= 10) {
            var_r31->unk_234 = 0;
        }
        if (!((var_r31->unk_08) && ((var_r31->unk_234 == 5) || (var_r31->unk_234 == 9)))) {
            break;
        }
    }
    if (arg1 == 1) {
        var_f30 = -var_f31;
    } else {
        var_f30 = var_f31;
    }
    var_f29 = var_r31->unk_23C + var_f30;
    if (!var_r30) {
        var_r28 = 30;
    } else {
        var_r28 = 45;
    }
    fn_1_2708(object, var_f29, var_r28);
}

void fn_1_20E8(omObjData *object)
{
    Vec sp8;
    UnkPresentStruct2 *var_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r25;
    float var_f31;
    float var_f30;

    var_r31 = object->data;
    var_r29 = var_r31->unk_238;
    var_r27 = var_r31->unk_234;
    switch (object->unk10) {
    case 0:
        fn_1_920(lbl_1_bss_8, 0.0f, 220.0f, -120.0f, 30);
        fn_1_9A4(lbl_1_bss_8, 0.0f, 0.0f, -600.0f, 30);
        var_r31->unk_04 = fn_1_2BCC(object, var_r27) > 0;
        var_r31->unk_00 = 0;
        var_r31->unk_238 = 0;
        if (var_r31->unk_04) {
            var_r25 = fn_1_3394(var_r31->unk_234);
            for (var_r28 = 0; var_r28 < var_r25; var_r28++) {
                if (fn_1_2B84(object, var_r27, var_r28)) {
                    var_r31->unk_238 = var_r28;
                    break;
                }
            }
        }
        object->unk10 = 1;
    case 1:
        if (fn_1_B6C(lbl_1_bss_8)) {
            break;
        }
        fn_1_4080(var_r31->unk_228);
        fn_1_4080(var_r31->unk_22C);
        fn_1_40B0(var_r31->unk_22C, 0x32007F);

        if (var_r31->unk_04) {
            fn_1_40B0(var_r31->unk_228, lbl_1_rodata_2B8[var_r27].unk_04[var_r29].unk_0C);
        } else {
            fn_1_40B0(var_r31->unk_228, 0x320003);
        }
        var_r31->unk_258 = 0.0f;
        var_r31->unk_25C = 5.0f / 30.0f;
        if (var_r31->unk_04) {
            fn_1_268C(var_r31->unk_10[lbl_1_rodata_2B8[var_r27].unk_04[var_r29].unk_00], &sp8.x, &sp8.y, &sp8.z);
            Hu3D3Dto2D(&sp8, 1, &sp8);
            sp8.y -= 15.0f;
            sp8.x -= 20.0f;
            if (!var_r31->unk_00) {
                fn_1_144(var_r31->sprite, 1, 5);
                var_r31->unk_00 = 1;
                var_r31->unk_260 = sp8.x;
                var_r31->unk_264 = sp8.y;
            } else {
                var_r31->unk_260 = var_r31->unk_268;
                var_r31->unk_264 = var_r31->unk_26C;
            }
            var_r31->unk_268 = sp8.x;
            var_r31->unk_26C = sp8.y;
            object->unk10 = 2;
        } else {
            object->unk10 = 3;
            break;
        }
    case 2:
        var_f31 = var_r31->unk_260 + (var_r31->unk_258 * (var_r31->unk_268 - var_r31->unk_260));
        var_f30 = var_r31->unk_264 + (var_r31->unk_258 * (var_r31->unk_26C - var_r31->unk_264));
        espPosSet(var_r31->sprite, var_f31, var_f30);
        if ((var_r31->unk_258 = var_r31->unk_258 + var_r31->unk_25C) < 1.0f) {
            break;
        }
        espPosSet(var_r31->sprite, var_r31->unk_268, var_r31->unk_26C);
        object->unk10 = 3;
    case 3:
        if (fn_1_550(512)) {
            fn_1_4098(var_r31->unk_228);
            fn_1_4098(var_r31->unk_22C);
            HuAudFXPlay(3);
            object->unk10 = 4;
        } else if (var_r31->unk_04) {
            if (fn_1_584(1) && fn_1_5B8(8)) {
                var_r29 = fn_1_2C5C(object, 5);
            } else if (fn_1_584(1) && fn_1_5B8(4)) {
                var_r29 = fn_1_2C5C(object, 9);
            } else if (fn_1_584(2) && fn_1_5B8(8)) {
                var_r29 = fn_1_2C5C(object, 6);
            } else if (fn_1_584(2) && fn_1_5B8(4)) {
                var_r29 = fn_1_2C5C(object, 10);
            } else if (fn_1_584(1)) {
                var_r29 = fn_1_2C5C(object, 1);
            } else if (fn_1_584(2)) {
                var_r29 = fn_1_2C5C(object, 2);
            } else if (fn_1_584(8)) {
                var_r29 = fn_1_2C5C(object, 4);
            } else if (fn_1_584(4)) {
                var_r29 = fn_1_2C5C(object, 8);
            }
        } else {
            break;
        }
        if (var_r29 == -1) {
            var_r29 = var_r31->unk_238;
        }
        if (var_r29 != var_r31->unk_238) {
            var_r31->unk_238 = var_r29;
            object->unk10 = 1;
            HuAudFXPlay(0);
        }
        break;
    case 4:
        if (var_r31->unk_00) {
            fn_1_144(var_r31->sprite, 0, 5);
        }
        fn_1_180C(object, 1);
        break;
    default:
        break;
    }
}

void fn_1_268C(omObjData *object, float *arg1, float *arg2, float *arg3)
{
    Mtx sp8;

    Hu3DModelObjMtxGet(object->model[0], "cursor", sp8);
    *arg1 = sp8[0][3];
    *arg2 = sp8[1][3];
    *arg3 = sp8[2][3];
}

void fn_1_2708(omObjData *arg0, float arg8, s32 arg1)
{
    UnkPresentStruct2 *var_r31;

    var_r31 = arg0->data;
    var_r31->unk_244 = arg8;
    var_r31->unk_240 = var_r31->unk_23C;
    var_r31->unk_248 = 0.0f;
    var_r31->unk_250 = 1.0f / arg1;
}

void fn_1_2774(omObjData *object)
{
    UnkPresentStruct2 *var_r31;
    float var_f31;
    s32 var_r30;

    var_r31 = object->data;

    if (var_r31->unk_248 < 1.0f) {
        var_f31 = sin(90.0f * var_r31->unk_248 * M_PI / 180.0f);
        var_f31 *= var_f31;
        var_r31->unk_23C = var_r31->unk_240 + (var_f31 * (var_r31->unk_244 - var_r31->unk_240));

        if ((var_r31->unk_248 = var_r31->unk_248 + var_r31->unk_250) >= 1.0f) {
            var_r31->unk_23C = var_r31->unk_244;
        }
    }
    var_r31->unk_23C = fmod(var_r31->unk_23C, 360.0);

    if (var_r31->unk_23C < 0.0f) {
        var_r31->unk_23C += 360.0f;
    }

    for (var_r30 = 0; var_r30 < 134; var_r30++) {
        omSetRot(var_r31->unk_10[var_r30], 0.0f, var_r31->unk_23C, 0.0f);
    }
}

s32 fn_1_28F0(omObjData *object)
{
    UnkPresentStruct2 *var_r31;

    var_r31 = object->data;
    return var_r31->unk_248 < 1.0f;
}

s32 lbl_1_data_84[] = { 0, 1, 2, 3, 4, 6, 7, 8 };

void fn_1_2924(omObjData *object)
{
    UnkPresentStruct2 *var_r31;
    s32 var_r30;
    s32 var_r27;
    s32 var_r29;

    var_r31 = object->data;
    Hu3DModelAttrReset(var_r31->unk_10[0]->model[0], 1);

    for (var_r29 = 0; var_r29 < 8; var_r29++) {
        if (fn_1_2BCC(object, lbl_1_data_84[var_r29]) > 0) {
            Hu3DModelAttrReset(var_r31->unk_10[var_r29 + 109]->model[0], 1);
        }

        for (var_r27 = 0, var_r30 = 0; var_r30 < 6; var_r30++) {
            if (fn_1_2B84(object, lbl_1_data_84[var_r29], var_r30)) {
                Hu3DModelAttrReset(var_r31->unk_10[var_r29 * 6 * 2 + 2 + var_r30]->model[0], 1);
                Hu3DModelAttrReset(var_r31->unk_10[var_r29 * 6 * 2 + 8 + var_r30]->model[0], 1);
                var_r27++;
            }
        }
        if (var_r27 >= 6) {
            Hu3DModelAttrReset(var_r31->unk_10[var_r29 + 118]->model[0], 1);
        }
    }
    if (fn_1_2BCC(object, 9) > 0) {
        Hu3DModelAttrReset(var_r31->unk_10[117]->model[0], 1);
    }
    for (var_r30 = 0; var_r30 < 11; var_r30++) {
        if (fn_1_2B84(object, 9, var_r30)) {
            Hu3DModelAttrReset(var_r31->unk_10[var_r30 + 98]->model[0], 1);
        }
    }
    if (fn_1_2B84(object, 5, 0)) {
        Hu3DModelAttrReset(var_r31->unk_10[1]->model[0], 1);
    }
    for (var_r30 = 0; var_r30 < 8; var_r30++) {
        if (fn_1_2B84(object, lbl_1_data_84[var_r30], 5)) {
            Hu3DModelAttrReset(var_r31->unk_10[var_r30 + 126]->model[0], 1);
        }
    }
}

static const s32 lbl_1_rodata_A74[] = { 0, 6, 12, 18, 24, 59, 30, 36, 42, 48 };

s32 fn_1_2B84(omObjData *arg0, s32 arg1, s32 arg2)
{
    UnkPresentStruct2 *var_r31;

    var_r31 = arg0->data;
    return var_r31->unk_270[arg2 + lbl_1_rodata_A74[arg1]] != 0;
}

s32 fn_1_2BCC(omObjData *object, s32 arg1)
{
    s32 var_r31;
    s32 var_r30;
    UnkPresentStruct2 *var_r29;
    s32 var_r28;

    var_r28 = fn_1_3394(arg1);

    for (var_r30 = 0, var_r31 = 0; var_r31 < var_r28; var_r31++) {
        if (fn_1_2B84(object, arg1, var_r31)) {
            var_r30++;
        }
    }

    return var_r30;
}

s32 fn_1_2C5C(omObjData *object, s32 arg1)
{
    UnkPresentStruct7 spA4[10];
    Vec sp38;
    Vec sp2C;
    UnkPresentStruct7 sp24;
    float var_f31;
    float var_f30;
    float var_f29;
    UnkPresentStruct2 *var_r31;
    s32 var_r30;
    s32 var_r28;
    s32 var_r26;
    s32 var_r23;
    s32 var_r22;
    omObjData *var_r21;
    omObjData *var_r19;
    s32 var_r18;
    s32 var_r17;

    var_r31 = object->data;

    var_r22 = fn_1_3394(var_r31->unk_234);

    var_r18 = fn_1_2BCC(object, var_r31->unk_234);
    if (var_r18 == 1) {
        return var_r31->unk_238;
    }

    fn_1_268C(var_r31->unk_10[lbl_1_rodata_2B8[var_r31->unk_234].unk_04[var_r31->unk_238].unk_00], &sp38.x, &sp38.y, &sp38.z);
    Hu3D3Dto2D(&sp38, 1, &sp38);
    for (var_r28 = 0, var_r26 = 0; !var_r28 && (var_r26 < 1); var_r26++) {
        for (var_r28 = 0, var_r30 = 0; var_r30 < var_r22; var_r30++) {
            if (var_r30 == var_r31->unk_238) {
                continue;
            }
            if (!fn_1_2B84(object, var_r31->unk_234, var_r30)) {
                continue;
            }
            fn_1_268C(var_r31->unk_10[lbl_1_rodata_2B8[var_r31->unk_234].unk_04[var_r30].unk_00], &sp2C.x, &sp2C.y, &sp2C.z);
            Hu3D3Dto2D(&sp2C, 1, &sp2C);
            var_f30 = sp38.x - sp2C.x;
            var_f29 = sp38.y - sp2C.y;
            var_f31 = fmod(atan2d(var_f30, var_f29), 360.0);
            if (var_f31 < 0.0f) {
                var_f31 += 360.0f;
            }
            if ((arg1 == 1 && var_f31 >= 45.0f && var_f31 < 135.0f) || (arg1 == 2 && var_f31 >= 225.0f && var_f31 < 315.0f)
                || (arg1 == 8 && var_f31 >= 135.0f && var_f31 < 225.0f)
                || (arg1 == 4 && (var_f31 >= 0.0f && var_f31 < 45.0f || var_f31 >= 315.0f && var_f31 < 360.0f))
                || (arg1 == 5 && var_f31 >= 0.0f && var_f31 < 90.0f) || (arg1 == 9 && var_f31 >= 90.0f && var_f31 < 180.0f)
                || (arg1 == 6 && var_f31 >= 270.0f && var_f31 < 360.0f) || (arg1 == 10 && var_f31 >= 180.0f && var_f31 < 270.0f)) {
                spA4[var_r28].unk_00 = var_r30;
                spA4[var_r28].unk_04 = sqrtf(var_f30 * var_f30 + var_f29 * var_f29);
                var_r28++;
            }
        }

        if (var_r28) {
            continue;
        }
        switch (arg1) {
        case 0:
            break;
        case 1:
        L_00003218:
            arg1 = 2;
            break;
        case 2:
        L_00003220:
            arg1 = 1;
            break;
        case 3:
            break;
        case 4:
        L_00003228:
            arg1 = 8;
            break;
        case 7:
            break;
        case 8:
        L_00003230:
            arg1 = 4;
            break;
        case 5:
        L_00003238:
            arg1 = 10;
            break;
        case 9:
        L_00003240:
            arg1 = 6;
            break;
        case 6:
        L_00003248:
            arg1 = 9;
            break;
        case 10:
        L_00003250:
            arg1 = 5;
            break;
        default:
            break;
        }
        // L_00003254:
    }
    if (!var_r28) {
        return var_r31->unk_238;
    }
    do {
        for (var_r23 = 0, var_r30 = 0; var_r30 < (var_r28 - 1); var_r30++) {
            if (spA4[var_r30].unk_04 > spA4[var_r30 + 1].unk_04) {
                sp24 = spA4[var_r30 + 1];
                spA4[var_r30 + 1] = spA4[var_r30];
                spA4[var_r30] = sp24;
                var_r23 = 1;
            }
        }
    } while (var_r23);
    return spA4[(var_r26 <= 1) ? 0 : var_r28 - 1].unk_00;
}

static const s32 lbl_1_rodata_AC8[] = { 6, 6, 6, 6, 6, 1, 6, 6, 6, 11 };

s32 fn_1_3394(s32 arg0)
{
    return lbl_1_rodata_AC8[arg0];
}

static const s32 lbl_1_rodata_AF0[] = { 2, 14, 26, 38, 50, 0, 62, 74, 86, 0 };
static const s32 lbl_1_rodata_B18[] = { 8, 20, 32, 44, 56, 0, 68, 80, 92, 0 };
static const s32 lbl_1_rodata_B40[] = { 126, 127, 128, 129, 130, 0, 131, 132, 133, 0 };
static const s32 lbl_1_rodata_B68[] = { 118, 119, 120, 121, 122, 0, 123, 124, 125, 0 };

void fn_1_33AC(omObjData *object)
{
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    UnkPresentStruct2 *var_r31;
    UnkPresentStruct2 *var_r30;
    UnkPresentStruct2 *var_r28;
    s32 var_r27;

    var_r31 = object->data;
    switch (object->unk10) {
    case 0:
        var_f29 = 36.0f * var_r31->unk_234;
        fn_1_2708(object, var_f29, 1);
        fn_1_2774(object);
        Hu3DModelAttrSet(var_r31->unk_10[var_r31->unk_238 + lbl_1_rodata_B18[var_r31->unk_234]]->model[0], 1);
        Hu3DModelAttrSet(var_r31->unk_10[lbl_1_rodata_B68[var_r31->unk_234]]->model[0], 1);
        Hu3DModelAttrSet(var_r31->unk_10[lbl_1_rodata_B40[var_r31->unk_234]]->model[0], 1);
        var_r31->unk_24C = 0.0f;
        var_r31->unk_254 = 1.0f / 360.0f;
        object->unk10 = 1;
    case 1:
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 120);
        object->unk10 = 2;
    case 2:
        var_f31 = sind(90.0f * var_r31->unk_24C);
        var_f31 *= var_f31;
        fn_1_920(lbl_1_bss_8, 0.0f, 820.0f - (600.0f * var_f31), -120.0f, 1);
        fn_1_9A4(lbl_1_bss_8, 0.0f, 680.0f - (680.0f * var_f31), -600.0f, 1);
        omSetTra(var_r31->unk_10[var_r31->unk_238 + lbl_1_rodata_AF0[var_r31->unk_234]], 0.0f, 840.0f - (840.0f * var_f31), 0.0f);
        if ((var_r31->unk_24C = var_r31->unk_24C + var_r31->unk_254) < 1.0f) {
            return;
        }
        if (fn_1_393C(var_r31->unk_234, var_r31->unk_238)) {
            fn_1_334(var_r31->unk_10[var_r31->unk_238 + lbl_1_rodata_B18[var_r31->unk_234]]->model[0], 1, 0.4f, 30);
        }
        object->unk10 = 3;
    case 3:
        fn_1_4080(var_r31->unk_228);
        fn_1_4104(var_r31->unk_228, lbl_1_rodata_2B8[var_r31->unk_234].unk_04[var_r31->unk_238].unk08, 0);
        fn_1_40B0(var_r31->unk_228, 0x320004);
        fn_1_419C(var_r31->unk_228);
        object->unk10 = 4;
    case 4:
        if (var_r31->unk_228->unk_20) {
            break;
        }
        object->unk10 = 5;
    case 5:
        fn_1_4098(var_r31->unk_228);
        object->unk10 = 6;
    case 6:
        if (!var_r31->unk_228->unk_20) {
            fn_1_180C(object, 0);
        }
        break;
    }
}

static const s32 lbl_1_rodata_BA4[][2] = { { 7, 1 } };

s32 fn_1_393C(s32 arg0, s32 arg1)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        if (arg0 == lbl_1_rodata_BA4[var_r31][0] && arg1 == lbl_1_rodata_BA4[var_r31][1]) {
            return 0;
        }
    }
    return 1;
}
