#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"

typedef struct UnkM414Struct {
    s32 unk00;
    s32 unk04;
    float unk08;
    char unk0C[0x38];
    s32 unk_44;
    char unk48[0x0C];
    s32 unk_54;
    char unk58[0x24];
    float unk_7C;
    float unk_80;
    float unk_84;
    char unk88[0xB0];
    Vec unk_138[16];
    s32 unk_1F8;
} UnkM414Struct; // size unknown

typedef struct UnkM414BssF0Struct {
    s16 unk_00[9];
    s16 unk_12;
    s16 unk_14[6];
    s16 unk_20;
    s16 unk_22[5];
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30[9];
    s16 unk_42;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    float unk_60;
    float unk_64;
    float unk_68;
    float unk_6C;
    float unk_70;
    float unk_74;
    char unk78[4];
    float unk_7C;
    float unk_80;
    float unk_84;
    float unk_88;
    char unk8C[4];
    float unk_90;
    s16 unk_94[16];
    s16 unk_B4[16];
    s16 unk_D4[16];
    s32 unk_F4[16];
    Vec unk_134[16];
    s32 unk_1F4;
    s32 unk_1F8;
    s8 unk_1FC;
    s8 unk_1FD;
    s8 unk_1FE;
    s8 unk_1FF;
    u16 unk_200;
    char unk202[2];
    s32 unk_204;
} UnkM414BssF0Struct; // size 0x208

typedef struct UnkM414Struct2 {
    UnkM414BssF0Struct *unk_00;
    s32 unk_04;
    union {
        s32 unk_08;
        s32 *unk_08_ptr;
    };
    s32 unk_0C;
} UnkM414Struct2; // size unknown

typedef struct UnkM414Struct3 {
    s32 unk_00;
    s32 unk_04;
    float unk_08;
} UnkM414Struct3; // size unknown

typedef struct UnkM414Struct4 {
    UnkM414BssF0Struct *unk_00;
    s32 unk_04;
    union {
        s32 unk_08;
        s32 *unk_08_ptr;
    };
} UnkM414Struct4; // size unknown

s16 lbl_1_bss_A12;
s16 lbl_1_bss_A10;
s16 lbl_1_bss_990[16][4];
s32 lbl_1_bss_98C;
s32 lbl_1_bss_97C[4];
s32 lbl_1_bss_978;
s32 lbl_1_bss_938[16];
s32 lbl_1_bss_930[2];
float lbl_1_bss_920[4];
float lbl_1_bss_910[4];
UnkM414BssF0Struct lbl_1_bss_F0[4];
Process *lbl_1_bss_E0[4];
Process *lbl_1_bss_DC;
Vec lbl_1_bss_A0[5];
Vec lbl_1_bss_64[5];
Vec lbl_1_bss_28[5];
omObjData *lbl_1_bss_24;
Vec lbl_1_bss_18;
Vec lbl_1_bss_C;
Vec lbl_1_bss_0;

void fn_1_91C(omObjData *object);
void fn_1_1388(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_13C4(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_1400(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_143C(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_168C(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_16C8(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_1704(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_1740(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_1B58(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_1B94(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_1BD0(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_1C0C(ModelData *arg0, ParticleData *arg1, Mtx arg2);
void fn_1_1E04();
void fn_1_3ECC();
void fn_1_5780(UnkM414BssF0Struct *arg0, float arg8);
s32 fn_1_654C(s32 arg0, s32 arg1);
void fn_1_6644();
void fn_1_8A10();
void fn_1_8A70();

ParticleHook lbl_1_data_0[] = { fn_1_1388, fn_1_13C4, fn_1_1400, fn_1_143C };

ParticleHook lbl_1_data_10[] = { fn_1_168C, fn_1_16C8, fn_1_1704, fn_1_1740 };

ParticleHook lbl_1_data_20[] = { fn_1_1B58, fn_1_1B94, fn_1_1BD0, fn_1_1C0C };

s32 lbl_1_data_30[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

s32 lbl_1_data_50[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MARIOMOT, 72),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 23), DATA_MAKE_NUM(DATADIR_MARIOMOT, 24), DATA_MAKE_NUM(DATADIR_MARIOMOT, 54) };

float lbl_1_data_68[] = { 0.0f, 2.0f, 3.0f, 1.0f, 2.0f, 3.0f, 1.0f, 2.0f, 3.0f };

s32 lbl_1_data_8C[] = { 75, 64, 67, 79, 73, 80 };

s32 lbl_1_data_A4[] = { 230, 510, 230, 510 };

s32 lbl_1_data_B4[] = { 205, 205, 420, 420 };

s32 lbl_1_data_C4[][3] = {
    // rgb color
    { 254, 0, 0 },
    { 1, 0, 254 },
    { 255, 123, 222 },
    { 0, 255, 1 },
    { 175, 50, 240 },
    { 225, 127, 80 },
    { 255, 255, 1 },
    { 0, 0, 0 },
};

void ObjectSetup(void)
{
    s32 var_r31;
    s32 var_r30;
    Process *var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r29 = omInitObjMan(50, 8192);
    omGameSysInit(var_r29);
    Hu3DCameraCreate(31);
    Hu3DCameraPerspectiveSet(31, 30.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 10.0f, 20.0f, 309.0f, 219.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(2, 322.0f, 20.0f, 309.0f, 219.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(4, 10.0f, 242.0f, 309.0f, 219.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(8, 322.0f, 242.0f, 309.0f, 219.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(16, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 10, 20, 309, 219);
    Hu3DCameraScissorSet(2, 322, 20, 309, 219);
    Hu3DCameraScissorSet(4, 10, 242, 309, 219);
    Hu3DCameraScissorSet(8, 322, 242, 309, 219);
    Hu3DCameraScissorSet(16, 0, 0, 640, 480);
    lbl_1_bss_24 = omAddObjEx(var_r29, 32730, 0, 0, -1, fn_1_91C);
    lbl_1_bss_24->work[0] = 4;

    for (var_r31 = 0; var_r31 < lbl_1_bss_24->work[0]; var_r31++) {
        lbl_1_bss_920[var_r31] = 0.0f;
        lbl_1_bss_910[var_r31] = 1900.0f;
        lbl_1_bss_A0[var_r31].y = 455.0f;
        lbl_1_bss_64[var_r31].x = var_r31 % 2 * 2000.0f;
        lbl_1_bss_64[var_r31].z = var_r31 / 2 * 2000.0f;
        lbl_1_bss_64[var_r31].y = 610.0f;
        lbl_1_bss_28[var_r31].x = 0.0f;
        lbl_1_bss_28[var_r31].y = 1.0f;
        lbl_1_bss_28[var_r31].z = 0.0f;
    }
    Hu3DCameraPosSet(16, 0.0f, 265.0f, 180.0f, 0.0f, 1.0f, 0.0f, 0.0f, 265.0f, 0.0f);
    Hu3DLighInit();
    lbl_1_bss_A12 = Hu3DGLightCreate(10000.0f, 0.0f, 10000.0f, -1.0f, 0.0f, -1.0f, 255, 255, 255);
    Hu3DGLightPosAimSet(lbl_1_bss_A12, 0.0f, 4330.13f, 2500.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(lbl_1_bss_A12);
    lbl_1_bss_18.x = 1000.0f;
    lbl_1_bss_18.y = 7000.0f;
    lbl_1_bss_18.z = 0.0f;
    lbl_1_bss_C.x = lbl_1_bss_C.z = 0.0f;
    lbl_1_bss_C.y = 1.0f;
    lbl_1_bss_0.x = 1000.0f;
    lbl_1_bss_0.y = 0.0f;
    lbl_1_bss_0.z = 1000.0f;
    Hu3DShadowCreate(30.0f, 20.0f, 50000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&lbl_1_bss_18, &lbl_1_bss_C, &lbl_1_bss_0);
    Hu3DBGColorSet(0, 0, 0);
    lbl_1_bss_978 = frandmod(6);

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        lbl_1_bss_938[var_r31] = lbl_1_bss_978;
    }
    var_r30 = frandmod(6);

    for (; var_r31 < 16; var_r31++, var_r30++) {
        if (var_r30 == lbl_1_bss_978) {
            var_r30++;
        }
        if (var_r30 >= 6) {
            if (lbl_1_bss_978 == 0) {
                var_r30 = 1;
            }
            else {
                var_r30 = 0;
            }
        }
        lbl_1_bss_938[var_r31] = var_r30;
    }
    for (var_r31 = 0; var_r31 < 50; var_r31++) {
        var_r28 = frandmod(16);
        var_r27 = frandmod(16);
        var_r26 = lbl_1_bss_938[var_r28];
        lbl_1_bss_938[var_r28] = lbl_1_bss_938[var_r27];
        lbl_1_bss_938[var_r27] = var_r26;
    }
    fn_1_1E04();
    lbl_1_bss_DC = HuPrcChildCreate(fn_1_8A70, 4096, 8192, 0, HuPrcCurrentGet());
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
}

void fn_1_91C(omObjData *object)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < object->work[0]; var_r31++) {
        lbl_1_bss_A0[var_r31].x = (var_r31 % 2 * 2000.0f) + (lbl_1_bss_910[var_r31] * sind(lbl_1_bss_920[var_r31]));
        lbl_1_bss_A0[var_r31].z = (var_r31 / 2 * 2000.0f) + (lbl_1_bss_910[var_r31] * cosd(lbl_1_bss_920[var_r31]));

        Hu3DCameraPosSet(1 << var_r31, lbl_1_bss_A0[var_r31].x, lbl_1_bss_A0[var_r31].y, lbl_1_bss_A0[var_r31].z, lbl_1_bss_28[var_r31].x,
            lbl_1_bss_28[var_r31].y, lbl_1_bss_28[var_r31].z, lbl_1_bss_64[var_r31].x, lbl_1_bss_64[var_r31].y, lbl_1_bss_64[var_r31].z);
    }
}

void fn_1_B84(void)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    UnkM414Struct3 *var_r31;
    s32 var_r30;

    var_r31 = HuPrcCurrentGet()->user_data;
    if (!var_r31->unk_00) {
        var_f29 = lbl_1_bss_A0[var_r31->unk_04].y;
        var_f28 = lbl_1_bss_64[var_r31->unk_04].y;

        for (var_r30 = 0, var_f31 = 0.0f; var_r30 < 10; var_r30++, var_f31 += 36.0f) {
            var_f30 = var_r31->unk_08 * sind(var_f31);
            lbl_1_bss_A0[var_r31->unk_04].y = var_f29 + var_f30;
            lbl_1_bss_64[var_r31->unk_04].y = var_f28 + var_f30;
            HuPrcVSleep();
        }
        lbl_1_bss_A0[var_r31->unk_04].y = var_f29;
        lbl_1_bss_64[var_r31->unk_04].y = var_f28;
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_CD8(s32 arg0, s32 arg1, float arg8)
{
    UnkM414Struct3 sp14;
    UnkM414Struct3 *var_r31;
    Process *var_r30;

    var_r31 = &sp14;
    var_r30 = HuPrcChildCreate(fn_1_B84, 8192, 8192, 0, HuPrcCurrentGet());
    var_r30->user_data = var_r31;
    var_r31->unk_00 = arg0;
    var_r31->unk_04 = arg1;
    var_r31->unk_08 = arg8;
}

void fn_1_D54(ModelData *arg0, ParticleData *arg1, Mtx arg2, s32 arg3)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    double var_f27;

    HsfanimStruct01 *var_r31;
    UnkM414BssF0Struct *var_r30;
    s16 var_r28;
    s16 var_r27;
    s16 var_r26;
    s32 var_r25;

    if (arg1->unk_34 == 0) {
        var_r31 = arg1->unk_48;

        for (var_r28 = 0; var_r28 < arg1->unk_30; var_r28++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = arg1->unk_48;
    var_r30 = &lbl_1_bss_F0[arg3];
    if (var_r30->unk_54 == 1) {
        for (var_r27 = 0; var_r27 < 2; var_r27++) {
            var_f28 = 2.4f;
            for (var_r26 = 0, var_f29 = 0.0f; var_r26 < 4; var_r26++, var_f29 += 90.0f) {
                for (var_r28 = 0; var_r28 < arg1->unk_30; var_r28++, var_r31++) {
                    if (0.0f == var_r31->unk14.x) {
                        break;
                    }
                }
                if (var_r28 == arg1->unk_30) {
                    break;
                }
                var_f31 = var_f29 + frandmod(70);
                var_f30 = var_f28 + (3.6f * frandf());
                var_r31->unk34.x = var_r30->unk_7C + ((20.0f * var_r27) * (sind(var_f31) * cosd(lbl_1_bss_920[var_r30->unk_44])));
                var_r31->unk34.y = var_r30->unk_80 + ((20.0f * var_r27) * cosd(var_f31));
                var_r31->unk34.z = var_r30->unk_84 + (-(20.0f * var_r27) * (sind(lbl_1_bss_920[var_r30->unk_44]) * sind(var_f31)));
                var_r31->unk08.x = var_f30 * (sind(var_f31) * cosd(lbl_1_bss_920[var_r30->unk_44]));
                var_r31->unk08.y = var_f30 * cosd(var_f31);
                var_r31->unk08.z = -var_f30 * (sind(lbl_1_bss_920[var_r30->unk_44]) * sind(var_f31));
                var_r31->unk14.x = 30.0f;
                var_r31->unk2C = 40.0f + (20.0f * frandf());
                var_r31->unk40.r = frandmod(20) + 235;
                var_r31->unk40.g = frandmod(50) + 205;
                var_r31->unk40.b = frandmod(50);
                var_r31->unk40.a = 255;
            }
        }
        var_r30->unk_54++;
    }
    var_r31 = arg1->unk_48;
    for (var_r28 = 0; var_r28 < arg1->unk_30; var_r28++, var_r31++) {
        if (0.0f != var_r31->unk14.x) {
            VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
            if (var_r31->unk14.x > 10.0f) {
                var_r31->unk14.x = var_r31->unk14.x - 1.0f;
            }
            if (10.0f == var_r31->unk14.x) {
                var_r25 = var_r31->unk40.a - 25;
                if (var_r25 < 0) {
                    var_r25 = 0;
                    var_r31->unk14.x = 0.0f;
                }
                var_r31->unk40.a = var_r25;
            }
            if (0.0f == var_r31->unk14.x) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}

void fn_1_1388(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_D54(arg0, arg1, arg2, 0);
}

void fn_1_13C4(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_D54(arg0, arg1, arg2, 1);
}

void fn_1_1400(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_D54(arg0, arg1, arg2, 2);
}

void fn_1_143C(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_D54(arg0, arg1, arg2, 3);
}

void fn_1_1478(ModelData *arg0, ParticleData *arg1, Mtx arg2, s32 arg3)
{
    HsfanimStruct01 *var_r31;
    s16 var_r30;
    UnkM414BssF0Struct *var_r29;
    s32 var_r28;

    if (arg1->unk_34 == 0) {
        var_r31 = arg1->unk_48;
        for (var_r30 = 0; var_r30 < arg1->unk_30; var_r30++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = arg1->unk_48;
    var_r29 = &lbl_1_bss_F0[arg3];
    if (var_r29->unk_54 == 2) {
        for (var_r30 = 0; var_r30 < arg1->unk_30; var_r30++, var_r31++) {
            if (0.0f == var_r31->unk14.x) {
                break;
            }
        }
        if (var_r30 != arg1->unk_30) {
            var_r31->unk34.x = var_r29->unk_7C;
            var_r31->unk34.y = var_r29->unk_80;
            var_r31->unk34.z = var_r29->unk_84;
            var_r31->unk14.x = 30.0f;
            var_r31->unk2C = 300.0f;
            var_r31->unk40.r = 255;
            var_r31->unk40.g = 255;
            var_r31->unk40.b = 255;
            var_r31->unk40.a = 255;
        }
        var_r29->unk_54++;
    }
    var_r31 = arg1->unk_48;
    for (var_r30 = 0; var_r30 < arg1->unk_30; var_r30++, var_r31++) {
        if (0.0f != var_r31->unk14.x) {
            if (var_r31->unk14.x > 25.0f) {
                var_r31->unk14.x -= 1.0f;
            }
            if (25.0f == var_r31->unk14.x) {
                var_r28 = var_r31->unk40.a - 25;
                if (var_r28 < 0) {
                    var_r28 = 0;
                    var_r31->unk14.x = 0.0f;
                }
                var_r31->unk40.a = var_r28;
            }
            if (0.0f == var_r31->unk14.x) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}

void fn_1_168C(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_1478(arg0, arg1, arg2, 0);
}

void fn_1_16C8(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_1478(arg0, arg1, arg2, 1);
}

void fn_1_1704(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_1478(arg0, arg1, arg2, 2);
}

void fn_1_1740(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_1478(arg0, arg1, arg2, 3);
}

void fn_1_177C(ModelData *arg1, ParticleData *arg2, Mtx arg3, s32 arg4)
{
    float var_f31;
    float var_f30;

    HsfanimStruct01 *var_r31;
    UnkM414BssF0Struct *var_r29;
    s16 var_r28;
    s16 var_r27;
    s32 var_r26;

    if (arg2->unk_34 == 0) {
        var_r31 = arg2->unk_48;
        for (var_r28 = 0; var_r28 < arg2->unk_30; var_r28++, var_r31++) {
            var_r31->unk14.x = var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = arg2->unk_48;
    var_r29 = &lbl_1_bss_F0[arg4];
    if (var_r29->unk_54 == 3) {
        for (var_r27 = 0, var_f30 = 0.0f; var_r27 < 8; var_r27++, var_f30 += 45.0f) {
            for (var_r28 = 0; var_r28 < arg2->unk_30; var_r28++, var_r31++) {
                if (0.0f == var_r31->unk14.x) {
                    break;
                }
            }
            if (var_r28 == arg2->unk_30) {
                break;
            }
            var_f31 = var_f30 + frandmod(30);
            var_r31->unk34.x = var_r29->unk_7C + (120.0 * (sind(var_f31) * cosd(lbl_1_bss_920[var_r29->unk_44])));
            var_r31->unk34.y = var_r29->unk_80 + (120.0 * cosd(var_f31));
            var_r31->unk34.z = var_r29->unk_84 + (-120.0 * (sind(lbl_1_bss_920[var_r29->unk_44]) * sind(var_f31)));
            var_r31->unk30 = (M_PI * (360.0f - var_f31)) / 180.0;
            var_r31->unk14.x = 30.0f;
            var_r31->unk2C = 50.0f;
            var_r31->unk40.r = 255;
            var_r31->unk40.g = 255;
            var_r31->unk40.b = 0;
            var_r31->unk40.a = 255;
        }
        var_r29->unk_54++;
    }
    var_r31 = arg2->unk_48;
    for (var_r28 = 0; var_r28 < arg2->unk_30; var_r28++, var_r31++) {
        if (0.0f != var_r31->unk14.x) {
            var_r26 = var_r31->unk40.a - 8;
            if (var_r26 < 0) {
                var_r26 = 0;
                var_r31->unk14.x = 0.0f;
            }
            var_r31->unk40.a = var_r26;
            if (0.0f == var_r31->unk14.x) {
                var_r31->unk2C = 0.0f;
            }
        }
    }
}

void fn_1_1B58(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_177C(arg0, arg1, arg2, 0);
}

void fn_1_1B94(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_177C(arg0, arg1, arg2, 1);
}

void fn_1_1BD0(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_177C(arg0, arg1, arg2, 2);
}

void fn_1_1C0C(ModelData *arg0, ParticleData *arg1, Mtx arg2)
{
    fn_1_177C(arg0, arg1, arg2, 3);
}

void fn_1_1C48(void)
{
    UnkM414Struct *var_r31;

    var_r31 = HuPrcCurrentGet()->user_data;
    if (var_r31->unk_44 & 1) {
        HuAudFXPlay(1446);
    }
    else {
        HuAudFXPlay(1445);
    }
    var_r31->unk_54 = 1;
    var_r31->unk_7C = -800.0 * sind(lbl_1_bss_920[var_r31->unk_44]);
    var_r31->unk_80 = var_r31->unk_138[var_r31->unk_1F8].x;
    var_r31->unk_84 = -800.0 * cosd(lbl_1_bss_920[var_r31->unk_44]);
    var_r31->unk_7C += 2000.0f * (var_r31->unk_44 % 2);
    var_r31->unk_84 += 2000.0f * (var_r31->unk_44 / 2);
    HuPrcSleep(30);
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_1E04(void)
{
    s32 sp18[6];
    AnimData *sp8[4];

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    UnkM414BssF0Struct *var_r31;
    s16 var_r30;
    s32 var_r29;
    s32 var_r28;
    void *var_r27;
    Process *var_r26;
    AnimData *var_r25;
    s16 var_r24;
    s16 var_r23;
    s16 var_r22;
    AnimData *var_r21;

    HuAudSndGrpSet(39);
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        var_r31 = &lbl_1_bss_F0[var_r28];
        var_r31->unk_44 = var_r28;
        var_r31->unk_48 = var_r28;
        var_r31->unk_4C = GWPlayerCfg[var_r28].pad_idx;
        if (!var_r28) {
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 8), MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r30 = Hu3DModelCreate(var_r27);
            var_r22 = var_r30;
        }
        else {
            var_r30 = Hu3DModelLink(var_r22);
        }
        Hu3DModelCameraSet(var_r30, 15);
        Hu3DModelPosSet(var_r30, 2000.0f * (var_r28 % 2), 0.0f, 2000.0f * (var_r28 / 2));
        for (var_r29 = 0; var_r29 < 9; var_r29++) {
            if (!var_r28 && !var_r29) {
                var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 0), MEMORY_DEFAULT_NUM, HEAP_DATA);
                var_r30 = Hu3DModelCreate(var_r27);
                var_r24 = var_r30;
            }
            else {
                var_r30 = Hu3DModelLink(var_r24);
            }
            var_r31->unk_30[var_r29] = var_r30;
            Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);
            Hu3DModelShadowMapSet(var_r30);
            Hu3DModelAttrSet(var_r30, HU3D_ATTR_NOCULL);
            Hu3DModelRotSet(var_r30, 0.0f, 40.0f * var_r29, 0.0f);
            Hu3DModelPosSet(var_r30, 2000.0f * (var_r28 % 2), 0.0f, 2000.0f * (var_r28 / 2));
        }
        if (!var_r28) {
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 5), MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r30 = Hu3DModelCreate(var_r27);
        }
        else {
            var_r30 = Hu3DModelLink(lbl_1_bss_F0[0].unk_42);
        }
        var_r31->unk_42 = var_r30;
        Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);
        Hu3DModelShadowMapSet(var_r30);
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(var_r30, 2000.0f * (var_r28 % 2), 0.0f, 2000.0f * (var_r28 / 2));
        for (var_r29 = 0; var_r29 < 9; var_r29++) {
            if (!var_r28) {
                var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 1) + lbl_1_data_68[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA);
                var_r30 = Hu3DModelCreate(var_r27);
            }
            else {
                var_r30 = Hu3DModelLink(lbl_1_bss_F0->unk_00[var_r29]);
            }
            var_r31->unk_00[var_r29] = var_r30;
            Hu3DModelRotSet(var_r30, 0.0f, 40.0f * var_r29, 0.0f);
            Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);
            Hu3DModelAttrSet(var_r30, HU3D_ATTR_NOCULL);
            Hu3DModelPosSet(var_r30, 2000.0f * (var_r28 % 2), 0.0f, 2000.0f * (var_r28 / 2));
            Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_PAUSE);
        }
        for (var_r29 = 0; var_r29 < 16; var_r29++) {
            if (!var_r28 && !var_r29) {
                var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 6), MEMORY_DEFAULT_NUM, HEAP_DATA);
                var_r30 = Hu3DModelCreate(var_r27);
                var_r23 = var_r30;
            }
            else {
                var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 6), MEMORY_DEFAULT_NUM, HEAP_DATA);
                var_r30 = Hu3DModelCreate(var_r27);
                var_r23 = var_r30;
            }
            Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);
            var_r31->unk_D4[var_r29] = var_r30;
            Hu3DModelPosSet(var_r30, 2000.0f * (var_r28 % 2), 330.0f - (330.0f * (var_r29 & 1)), 2000.0f * (var_r28 / 2));
            Hu3DModelRotSet(var_r30, 0.0f, 40.0f * ((var_r29 + 2) / 2), 0.0f);
            Hu3DModelAttrSet(var_r30, HU3D_ATTR_NOCULL);
            Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
            Hu3DMotionSpeedSet(var_r30, 3.0f);
            Hu3DMotionShapeSpeedSet(var_r30, 3.0f);
        }
        if (!var_r28) {
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 9), MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r30 = Hu3DModelCreate(var_r27);
        }
        else {
            var_r30 = Hu3DModelLink(lbl_1_bss_F0[0].unk_20);
        }
        var_r31->unk_20 = var_r30;
        Hu3DModelPosSet(var_r30, 2000.0f * (var_r28 % 2), 0.0f, 2000.0f * (var_r28 / 2));
        Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);
        Hu3DModelShadowMapObjSet(var_r30, "m414_11_R-dai_1");
        for (var_r29 = 0; var_r29 < 5; var_r29++) {
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 10) + var_r29, MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r31->unk_22[var_r29] = Hu3DJointMotion(var_r30, var_r27);
        }
        Hu3DMotionSet(var_r30, var_r31->unk_22[0]);
        Hu3DMotionTimeSet(var_r30, 0.0f);
        Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(var_r30, 2.0f);

        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 15), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r21 = HuSprAnimRead(var_r27);
        var_r30 = HuSprCreate(var_r21, 0x4000, 0);
        var_r31->unk_2C = HuSprGrpCreate(1);
        HuSprGrpMemberSet(var_r31->unk_2C, 0, var_r30);
        HuSprAttrSet(var_r31->unk_2C, 0, 4);
        HuSprColorSet(var_r31->unk_2C, 0, lbl_1_data_C4[GWPlayerCfg[var_r28].character][0], lbl_1_data_C4[GWPlayerCfg[var_r28].character][1],
            lbl_1_data_C4[GWPlayerCfg[var_r28].character][2]);
        HuSprTPLvlSet(var_r31->unk_2C, 0, 0.9f);
        HuSprGrpPosSet(var_r31->unk_2C, 320.0f, 240.0f);
        if (!var_r28) {
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 16) + var_r29, MEMORY_DEFAULT_NUM, HEAP_DATA);
                sp8[var_r29] = HuSprAnimRead(var_r27);
            }
        }
        var_r31->unk_2E = HuSprGrpCreate(8);
        var_r30 = HuSprCreate(sp8[2], 0x4000, 0);
        HuSprGrpMemberSet(var_r31->unk_2E, 0, var_r30);
        HuSprPosSet(var_r31->unk_2E, 0, 0.0f, 0.0f);
        var_r30 = HuSprCreate(sp8[3], 0x4000, 0);
        HuSprGrpMemberSet(var_r31->unk_2E, 1, var_r30);
        HuSprPosSet(var_r31->unk_2E, 1, 0.0f, 0.0f);
        HuSprTPLvlSet(var_r31->unk_2E, 1, 0.5f);

        for (var_r29 = 2; var_r29 < 8; var_r29++) {
            var_r30 = HuSprCreate(sp8[var_r29 & 1], 0x4000, 0);
            HuSprGrpMemberSet(var_r31->unk_2E, var_r29, var_r30);
            if (var_r29 & 1) {
                HuSprAttrSet(var_r31->unk_2E, var_r29, 4);
            }
            HuSprPosSet(var_r31->unk_2E, var_r29, -62.0f + (30.0f * (var_r29 / 2)), -2.0f);
        }
        HuSprGrpPosSet(var_r31->unk_2E, lbl_1_data_A4[var_r31->unk_44], lbl_1_data_B4[var_r31->unk_44]);
        HuSprGrpScaleSet(var_r31->unk_2E, 0.0f, 0.0f);
        var_f31 = 0.0f;
        if (!var_r28) {
            for (var_r29 = 0; var_r29 < 6; var_r29++) {
                sp18[var_r29] = -1;
            }
        }
        var_f31 += 40.0f;
        for (var_r29 = 0; var_r29 < 16; var_r29++) {
            if (!var_r28) {
                if (sp18[lbl_1_bss_938[var_r29]] == -1) {
                    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 22) + lbl_1_bss_938[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA);
                    var_r30 = Hu3DModelCreate(var_r27);
                    sp18[lbl_1_bss_938[var_r29]] = var_r30;
                }
                else {
                    var_r30 = Hu3DModelLink(sp18[lbl_1_bss_938[var_r29]]);
                }
            }
            else {
                var_r30 = Hu3DModelLink(sp18[lbl_1_bss_938[var_r29]]);
            }
            var_r31->unk_94[var_r29] = var_r30;
            var_r31->unk_F4[var_r29] = 0;
            Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);
            Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 34) + lbl_1_bss_938[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA);
            var_r31->unk_B4[var_r29] = Hu3DJointMotion(var_r30, var_r27);
            var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 28) + lbl_1_bss_938[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA);
            Hu3DMotionSet(var_r30, Hu3DJointMotion(var_r30, var_r27));
            Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrSet(var_r30, HU3D_ATTR_NOCULL);
            var_f29 = -950.0 * sind(var_f31);
            var_f29 = var_f29;
            var_f28 = -950.0 * cosd(var_f31);
            var_f28 = var_f28;
            if (var_r29 & 1) {
                var_f30 = 220.0f;
                var_f31 += 40.0f;
            }
            else {
                var_f30 = 570.0f;
            }
            if (!lbl_1_bss_938[var_r29]) {
                var_f30 += 70.0f;
            }
            HuSetVecF(&var_r31->unk_134[var_r29], var_f29, var_f30, var_f28);
            if (lbl_1_bss_938[var_r29]) {
                (void)var_r29;
            }
            else {
                (void)var_r29;
            }
            Hu3DModelPosSet(var_r30, var_f29 + (2000.0f * (var_r28 % 2)), var_f30, var_f28 + (2000.0f * (var_r28 / 2)));
            Hu3DModelRotSet(var_r30, 0.0f, atan2d(-var_f29, -var_f28), 0.0f);
            if (lbl_1_bss_938[var_r29] == 4 || lbl_1_bss_938[var_r29] == 5) {
                Hu3DModelScaleSet(var_r30, 0.6f, 0.6f, 0.6f);
            }
            if (lbl_1_bss_938[var_r29] == 2) {
                Hu3DModelScaleSet(var_r30, 1.2f, 1.2f, 1.2f);
            }
        }
        fn_1_5780(var_r31, lbl_1_bss_920[var_r31->unk_44]);
        var_r31->unk_12 = CharModelCreate(lbl_1_data_30[GWPlayerCfg[var_r28].character], 8);
        Hu3DModelCameraSet(var_r31->unk_12, 1 << var_r31->unk_48);
        var_r31->unk_6C = var_r31->unk_74 = var_r31->unk_70 = 0.0f;
        var_r31->unk_90 = 0.0f;
        var_r31->unk_60 = 37.0 * sind(var_r31->unk_70);
        var_r31->unk_64 = 70.0f;
        var_r31->unk_68 = 37.0 * cosd(var_r31->unk_70);
        Hu3DModelPosSet(var_r31->unk_12, var_r31->unk_60 + (2000.0f * (var_r28 % 2)), var_r31->unk_64, var_r31->unk_68 + (2000.0f * (var_r28 / 2)));
        Hu3DModelRotSet(var_r31->unk_12, var_r31->unk_6C, var_r31->unk_70, var_r31->unk_74);
        Hu3DModelShadowSet(var_r31->unk_12);
        for (var_r29 = 0; var_r29 < 6; var_r29++) {
            var_r31->unk_14[var_r29] = CharModelMotionCreate(lbl_1_data_30[GWPlayerCfg[var_r28].character], lbl_1_data_50[var_r29]);
        }
        CharModelMotionSet(lbl_1_data_30[GWPlayerCfg[var_r28].character], var_r31->unk_14[0]);
        Hu3DModelAttrSet(var_r31->unk_12, HU3D_MOTATTR_LOOP);
        CharModelMotionDataClose(lbl_1_data_30[GWPlayerCfg[var_r28].character]);

        var_r25 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 0), MEMORY_DEFAULT_NUM));
        HuDataDirClose(DATA_MAKE_NUM(DATADIR_EFFECT, 0));
        var_r30 = Hu3DParticleCreate(var_r25, 100);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(var_r30, 1.0f, 1.0f, 1.0f);
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DParticleColSet(var_r30, 255, 255, 0);
        Hu3DParticleScaleSet(var_r30, 0.0f);
        Hu3DParticleHookSet(var_r30, lbl_1_data_0[var_r31->unk_44]);
        Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);

        var_r25 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M414, 20), MEMORY_DEFAULT_NUM));
        var_r30 = Hu3DParticleCreate(var_r25, 1);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(var_r30, 1.0f, 1.0f, 1.0f);
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DParticleColSet(var_r30, 255, 255, 255);
        Hu3DParticleScaleSet(var_r30, 0.0f);
        Hu3DParticleHookSet(var_r30, lbl_1_data_10[var_r31->unk_44]);
        Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);

        var_r25 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M414, 21), MEMORY_DEFAULT_NUM));
        var_r30 = Hu3DParticleCreate(var_r25, 8);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(var_r30, 1.0f, 1.0f, 1.0f);
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DParticleColSet(var_r30, 255, 255, 0);
        Hu3DParticleScaleSet(var_r30, 0.0f);
        Hu3DParticleHookSet(var_r30, lbl_1_data_20[var_r31->unk_44]);
        Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);
        var_r26 = HuPrcChildCreate(fn_1_6644, 8192, 12288, 0, HuPrcCurrentGet());
        var_r26->user_data = var_r31;
        lbl_1_bss_E0[var_r28] = var_r26;
    }
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        var_r31 = &lbl_1_bss_F0[var_r28];
        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 40), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r30 = Hu3DModelCreate(var_r27);
        var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 41) + lbl_1_bss_978, MEMORY_DEFAULT_NUM, HEAP_DATA);
        Hu3DAnimCreate(var_r27, var_r30, "gsp000");
        Hu3DModelPosSet(var_r30, 2000.0f * (var_r28 % 2), 520.0f, -820.0f + (2000.0f * (var_r28 / 2)));
        Hu3DModelCameraSet(var_r30, 1 << var_r31->unk_48);
    }
    for (var_r28 = 0; var_r28 < 16; var_r28++) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            lbl_1_bss_990[var_r28][var_r29] = frandmod(120) + 60;
        }
    }
    for (var_r28 = 0; var_r28 < 4; var_r28++) {
        for (var_r29 = 0; var_r29 < 16; var_r29++) {
            var_r26 = HuPrcChildCreate(fn_1_3ECC, 8192, 4096, 0, HuPrcCurrentGet());
            var_r26->user_data = (void *)(var_r29 + (var_r28 << 16));
        }
    }

    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 7), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r27);
    lbl_1_bss_A10 = var_r30;
    Hu3DModelScaleSet(var_r30, 0.5f, 0.5f, 0.5f);
    Hu3DModelCameraSet(var_r30, 16);
    Hu3DModelAttrSet(var_r30, HU3D_MOTATTR_PAUSE);

    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 40), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r30 = Hu3DModelCreate(var_r27);

    var_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M414, 41) + lbl_1_bss_978, MEMORY_DEFAULT_NUM, HEAP_DATA);
    Hu3DAnimCreate(var_r27, var_r30, "gsp000");
    Hu3DModelPosSet(var_r30, 0.0f, 260.0f, -410.0f);
    Hu3DModelScaleSet(var_r30, 0.5f, 0.5f, 0.5f);
    Hu3DModelCameraSet(var_r30, 16);
    HuPrcChildCreate(fn_1_8A10, 4096, 4096, 0, HuPrcCurrentGet());
}

void fn_1_397C(void)
{
    float var_f31;

    s32 var_r31;
    UnkM414BssF0Struct *var_r30;
    s32 var_r29;

    for (var_r29 = 0, var_f31 = 0.0f; var_r29 < 15; var_r29++) {
        var_f31 += 0.06666667f;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            var_r30 = &lbl_1_bss_F0[var_r31];
            HuSprGrpScaleSet(var_r30->unk_2E, var_f31, var_f31);
        }
        HuPrcVSleep();
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = &lbl_1_bss_F0[var_r31];
        HuSprGrpScaleSet(var_r30->unk_2E, 1.0f, 1.0f);
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_3A58(void)
{
    float var_f31;
    s32 var_r29;
    s32 var_r31;
    UnkM414BssF0Struct *var_r30;

    for (var_r29 = 0, var_f31 = 1.0f; var_r29 < 15; var_r29++) {
        var_f31 -= 0.06666667f;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            var_r30 = &lbl_1_bss_F0[var_r31];
            HuSprGrpScaleSet(var_r30->unk_2E, var_f31, var_f31);
        }
        HuPrcVSleep();
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = &lbl_1_bss_F0[var_r31];
        HuSprGrpScaleSet(var_r30->unk_2E, 0.0f, 0.0f);
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_3B34(void)
{
    float var_f31;
    float var_f30;
    double var_f29;

    UnkM414BssF0Struct *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = HuPrcCurrentGet()->user_data;
    HuAudFXPlay(9);
    for (var_r30 = 30; var_r30 != 0; var_r30--) {
        var_f31 = 1.0f - ((var_r30 - 1) / 30.0f);
        var_f31 = (0.5 * var_f31) + (0.5 * (1.0f - ((1.0f - var_f31) * (1.0f - var_f31))));
        if (var_f31 < 0.75) {
            var_f29 = var_f31 / 0.75;
        }
        else {
            var_f29 = 1.0;
        }
        var_f30 = var_f29;
        var_f31 = 1.0f - ((1.0f - var_f31) * (1.0f - var_f31));
        var_f30 = 1.0f - ((1.0f - var_f30) * (1.0f - var_f30));
        var_r29 = (var_r31->unk_5C * 2) + 3;
        HuSprTPLvlSet(var_r31->unk_2E, var_r29, var_f30);
        HuSprScaleSet(var_r31->unk_2E, var_r29, 4.0f - (3.0f * var_f31), 4.0f - (3.0f * var_f31));
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_3D48(s32 arg0, s32 arg1)
{
    UnkM414BssF0Struct *var_r31;
    s32 var_r30;
    Process *var_r29;
    s32 var_r28;

    var_r31 = &lbl_1_bss_F0[arg0];
    var_r28 = lbl_1_bss_97C[var_r31->unk_44];
    if (arg1 == 0) {
        lbl_1_bss_97C[var_r31->unk_44]++;
    }
    else {
        lbl_1_bss_97C[var_r31->unk_44]--;
    }
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        if (var_r30 < lbl_1_bss_97C[var_r31->unk_44]) {
            if (arg1 == 0 && var_r28 == var_r30) {
                var_r29 = HuPrcChildCreate(fn_1_3B34, 8192, 8192, 0, lbl_1_bss_DC);
                var_r29->user_data = var_r31;
                var_r31->unk_5C = var_r30;
            }
            HuSprAttrSet(var_r31->unk_2E, (var_r30 * 2) + 2, HUSPR_ATTR_DISPOFF);
            HuSprAttrReset(var_r31->unk_2E, (var_r30 * 2) + 3, HUSPR_ATTR_DISPOFF);
        }
        else {
            HuSprAttrReset(var_r31->unk_2E, (var_r30 * 2) + 2, HUSPR_ATTR_DISPOFF);
            HuSprAttrSet(var_r31->unk_2E, (var_r30 * 2) + 3, HUSPR_ATTR_DISPOFF);
        }
    }
}

void fn_1_3ECC(void)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    UnkM414BssF0Struct *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r30 = (s32)HuPrcCurrentGet()->user_data;
    var_r27 = (var_r30 >> 16);
    var_r30 = (u16)var_r30;

    while (lbl_1_bss_98C == 0) {
        HuPrcVSleep();
    }
    var_r31 = &lbl_1_bss_F0[var_r27];
    var_r29 = 0;
    while (TRUE) {
        HuPrcSleep(lbl_1_bss_990[var_r30][var_r29++]);
        if (var_r29 >= 4) {
            var_r29 = 0;
        }
        if (var_r31->unk_1F8 == var_r30) {
            continue;
        }
        if (lbl_1_bss_98C == 5) {
            break;
        }

        var_f31 = 40.0f * ((var_r30 + 2) / 2);
        if (var_r31->unk_70 - var_f31 >= 0.0f) {
            var_f29 = var_r31->unk_70 - var_f31;
        }
        else {
            var_f29 = -(var_r31->unk_70 - var_f31);
        }
        if (var_f29 < 45.0f || (0.0f == var_r31->unk_70 && var_r30 >= 14)) {
            if (var_r30 == fn_1_654C(var_r31->unk_44, 0) || var_r30 == fn_1_654C(var_r31->unk_44, 1)) {
                if (var_r31->unk_44 & 1) {
                    HuAudFXPlay(1434);
                }
                else {
                    HuAudFXPlay(1433);
                }
            }
            else {
                HuAudFXPlay(1450);
            }
        }
        Hu3DModelAttrReset(var_r31->unk_D4[var_r30], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV | HU3D_MOTATTR_SHAPE_PAUSE | HU3D_MOTATTR_SHAPE_REV);
        do {
            var_r28 = lbl_1_bss_990[var_r30][var_r29++];
            if (var_r29 >= 4) {
                var_r29 = 0;
            }
            while (var_r28) {
                if (lbl_1_bss_98C == 5) {
                    break;
                }
                HuPrcVSleep();
                var_r28--;
            }
        } while (lbl_1_bss_98C != 5 && var_r31->unk_1F8 != -1 && lbl_1_bss_978 == lbl_1_bss_938[var_r31->unk_1F8]);

        Hu3DModelAttrReset(var_r31->unk_D4[var_r30], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DModelAttrSet(var_r31->unk_D4[var_r30], HU3D_MOTATTR_REV | HU3D_MOTATTR_SHAPE_REV);
        HuPrcSleep(10);
        var_f30 = 40.0f * ((var_r30 + 2) / 2);
        if (var_r31->unk_70 - var_f30 >= 0.0f) {
            var_f28 = var_r31->unk_70 - var_f30;
        }
        else {
            var_f28 = -(var_r31->unk_70 - var_f30);
        }
        if (var_f28 < 45.0f || (0.0f == var_r31->unk_70 && var_r30 >= 14)) {
            if (var_r30 == fn_1_654C(var_r31->unk_44, 0) || var_r30 == fn_1_654C(var_r31->unk_44, 1)) {
                if (var_r31->unk_44 & 1) {
                    HuAudFXPlay(1436);
                }
                else {
                    HuAudFXPlay(1435);
                }
            }
            else {
                HuAudFXPlay(1452);
            }
        }
    }
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_42AC(void)
{
    s32 sp8[1];

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f22;

    UnkM414BssF0Struct *var_r31;
    UnkM414Struct2 *var_r30;
    s32 var_r28;
    s32 var_r27;

    var_r30 = HuPrcCurrentGet()->user_data;
    var_r31 = var_r30->unk_00;
    var_r27 = var_r30->unk_00->unk_44;
    HuPrcSleep(30);
    if (var_r31->unk_44 & 1) {
        HuAudFXPlay(1444);
    }
    else {
        HuAudFXPlay(1443);
    }
    if (var_r31->unk_44 & 1) {
        HuAudFXPlay(1448);
    }
    else {
        HuAudFXPlay(1447);
    }
    if (var_r30->unk_08) {
        var_f24 = -200.0 * (sind(lbl_1_bss_920[var_r27]) * cos(0.0));
        var_f26 = 150.0 + (-200.0 * sin(0.0));
        var_f23 = -200.0 * (cos(0.0) * cosd(lbl_1_bss_920[var_r27]));
    }
    else {
        var_f24 = -200.0 * (sind(lbl_1_bss_920[var_r27]) * cosd(20));
        var_f26 = 150.0 + -200.0 * sind(-20);
        var_f23 = -200.0 * (cosd(-20) * cosd(lbl_1_bss_920[var_r27]));
    }
    if (!lbl_1_bss_938[var_r30->unk_04]) {
        var_f26 += 70.0f;
    }
    var_f31 = var_r31->unk_134[var_r30->unk_04].x;
    var_f30 = var_r31->unk_134[var_r30->unk_04].y;
    var_f29 = var_r31->unk_134[var_r30->unk_04].z;

    var_f28 = (var_f24 - var_f31) / 30.0f;
    var_f22 = (var_f26 - var_f30) / 30.0f;
    var_f27 = (var_f23 - var_f29) / 30.0f;

    for (var_r28 = 0; var_r28 < 30; var_r28++) {
        var_f31 += var_f28;
        var_f30 += var_f22;
        var_f29 += var_f27;
        Hu3DModelPosSet(var_r31->unk_94[var_r30->unk_04], var_f31 + (2000.0f * (var_r27 % 2)), var_f30, var_f29 + (2000.0f * (var_r27 / 2)));
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    HuAudFXPlay(lbl_1_data_8C[lbl_1_bss_978]);
    var_f28 = 500.0 * sind(lbl_1_bss_920[var_r27] - 20.0f);
    var_f28 = var_f28;
    var_f27 = 500.0 * cosd(lbl_1_bss_920[var_r27] - 20.0f);
    var_f27 = var_f27;
    var_f28 /= 30.0f;
    var_f27 /= 30.0f;

    for (var_r28 = 0, var_f25 = -20.0f; var_r28 < 30.0f; var_r28++) {
        var_f31 += var_f28;
        var_f30 -= var_f25;
        var_f29 += var_f27;
        var_f25 += 2.0f;
        Hu3DModelPosSet(var_r31->unk_94[var_r30->unk_04], var_f31 + (2000.0f * (var_r27 % 2)), var_f30, var_f29 + (2000.0f * (var_r27 / 2)));
        HuPrcVSleep();
    }
    var_r31->unk_F4[var_r30->unk_04] = 1;
    Hu3DModelAttrSet(var_r31->unk_94[var_r30->unk_04], HU3D_ATTR_DISPOFF);
    for (var_r28 = 0, sp8[0] = 0; var_r28 < 4; var_r28++) {
        if (lbl_1_bss_97C[var_r28] >= 3) {
            break;
        }
    }
    if (var_r28 >= 4) {
        fn_1_3D48(var_r31->unk_44, 0);
    }
    CharModelMotionSpeedSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], 1.0f);
    if (var_r30->unk_08) {
        CharModelMotionShiftSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], var_r31->unk_14[1], 60.0f, 5.0f, HU3D_MOTATTR_NONE);
    }
    else {
        CharModelMotionShiftSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], var_r31->unk_14[1], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    }
    HuPrcSleep(5);
    Hu3DModelAttrSet(var_r31->unk_12, HU3D_MOTATTR_PAUSE);
    CharModelMotionSpeedSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], 2.0f);
    var_r30->unk_0C = 0;
    HuPrcSleep(5);
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

u32 fn_1_4C04(s32 arg0, s32 arg1, s32 arg2)
{
    switch (GWPlayerCfg[arg0].diff) {
        case 0:
            arg1 *= 12;
            break;
        case 1:
            arg1 *= 10;
            break;
        case 2:
            arg1 *= 10;
            break;
        default:
            arg1 *= 8;
            break;
    }
    if (arg2) {
        arg1 / 2;
    }
    return arg1;
}

s32 fn_1_4C74(UnkM414BssF0Struct *arg0)
{
    s32 sp8[4];

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        sp8[var_r31] = -1;
    }

    for (var_r31 = var_r30 = 0; var_r31 < 16; var_r31++) {
        if (lbl_1_bss_978 == lbl_1_bss_938[var_r31] && !arg0->unk_F4[var_r31]) {
            sp8[var_r30++] = var_r31 / 2;
        }
    }
    var_r29 = fn_1_654C(arg0->unk_44, 0) / 2;
    if (fn_1_654C(arg0->unk_44, 0) == -1) {
        var_r29 = 8;
    }
    for (var_r31 = 0, var_r30 = 100, var_r26 = -1; var_r31 < 3; var_r31++) {
        if (sp8[var_r31] == -1) {
            break;
        }
        if (var_r29 - sp8[var_r31] >= 0) {
            var_r25 = var_r29 - sp8[var_r31];
        }
        else {
            var_r25 = -(var_r29 - sp8[var_r31]);
        }
        var_r27 = var_r25;
        if (var_r30 > var_r27) {
            var_r30 = var_r27;
            var_r26 = var_r31;
        }
    }
    if (!var_r31) {
        return 0;
    }
    return var_r29 - sp8[var_r26];
}

inline s32 fn_1_4C74_inline(UnkM414BssF0Struct *arg0)
{
    s32 sp8[4];

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r27;
    s32 var_r26;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        sp8[var_r31] = -1;
    }

    for (var_r31 = var_r30 = 0; var_r31 < 16; var_r31++) {
        if (lbl_1_bss_978 == lbl_1_bss_938[var_r31] && !arg0->unk_F4[var_r31]) {
            sp8[var_r30++] = var_r31 / 2;
        }
    }
    var_r29 = fn_1_654C(arg0->unk_44, 0) / 2;
    if (fn_1_654C(arg0->unk_44, 0) == -1) {
        var_r29 = 8;
    }
    for (var_r31 = 0, var_r30 = 100, var_r26 = -1; var_r31 < 3; var_r31++) {
        if (sp8[var_r31] == -1) {
            break;
        }
        var_r27 = ABS_INV(var_r29 - sp8[var_r31]);
        if (var_r30 > var_r27) {
            var_r30 = var_r27;
            var_r26 = var_r31;
        }
    }

    if (!var_r31) {
        return 0;
    }

    return var_r29 - sp8[var_r26];
}

void fn_1_4E10(UnkM414BssF0Struct *arg0)
{
    float var_f31;

    u32 var_r21;

    arg0->unk_1FC = arg0->unk_1FD = 0;
    arg0->unk_1FF = arg0->unk_1FE = 0;
    arg0->unk_200 = 0;

    switch (GWPlayerCfg[arg0->unk_44].diff) {
        case 0:
            var_r21 = 45;
            break;
        case 1:
            var_r21 = 55;
            break;
        case 2:
            var_r21 = 70;
            break;
        default:
            var_r21 = 80;
            break;
    }
    if (arg0->unk_204) {
        arg0->unk_204--;
        return;
    }
    var_f31 = fn_1_4C74_inline(arg0);
    if (var_f31 > 0.0f) {
        arg0->unk_1FE = 50;
        arg0->unk_204 = fn_1_4C04(arg0->unk_44, 5, 1) + 20 + fn_1_4C04(arg0->unk_44, frandmod(10), 0);
    }
    if (var_f31 < 0.0f) {
        arg0->unk_1FF = 50;
        arg0->unk_204 = fn_1_4C04(arg0->unk_44, 5, 1) + 20 + fn_1_4C04(arg0->unk_44, frandmod(10), 0);
    }
    if (0.0f == var_f31) {
        arg0->unk_204 = fn_1_4C04(arg0->unk_44, 1, 1) + 10 + fn_1_4C04(arg0->unk_44, frandmod(5), 0);

        if (arg0->unk_1F4 == 1) {
            if (lbl_1_bss_978 == lbl_1_bss_938[fn_1_654C(arg0->unk_44, 0)] && !arg0->unk_F4[fn_1_654C(arg0->unk_44, 0)]) {
                if (!(Hu3DModelMotionAttrGet(arg0->unk_D4[fn_1_654C(arg0->unk_44, 0)]) & 0x40000004)) {
                    arg0->unk_200 = 256;
                }
            }
            else {
                arg0->unk_1FD = -50;
            }
        }
        else if (lbl_1_bss_978 == lbl_1_bss_938[fn_1_654C(arg0->unk_44, 1)] && !arg0->unk_F4[fn_1_654C(arg0->unk_44, 1)]) {
            if (!(Hu3DModelMotionAttrGet(arg0->unk_D4[fn_1_654C(arg0->unk_44, 1)]) & 0x40000004)) {
                arg0->unk_200 = 256;
            }
        }
        else {
            arg0->unk_1FD = 50;
        }
    }
    if (frandmod(100) > var_r21) {
        switch (frandmod(5)) {
            case 0:
                arg0->unk_1FE = 50;
                break;
            case 1:
                arg0->unk_1FF = 50;
                break;
            case 2:
                break;
            case 3:
                arg0->unk_1FD = -50;
                break;
            default:
                arg0->unk_1FD = -50;
                break;
        }
    }
}

s8 fn_1_5554(s32 arg0, s32 arg1) // similar to m411Dll/main.c::fn_1_5D58
{
    UnkM414BssF0Struct *var_r31;
    s8 var_r30;

    var_r31 = &lbl_1_bss_F0[arg0];
    var_r30 = 0;
    if (lbl_1_bss_98C < 4) {
        if (!GWPlayerCfg[arg0].iscom) {
            (arg1) ? (var_r30 = HuPadStkY[var_r31->unk_4C]) : (var_r30 = HuPadStkX[var_r31->unk_4C]);
        }
        else {
            (arg1) ? (var_r30 = var_r31->unk_1FD) : (var_r30 = var_r31->unk_1FC);
        }
    }
    return var_r30;
}

u8 fn_1_5624(s32 arg0, s32 arg1)
{
    UnkM414BssF0Struct *var_r31;
    s8 var_r30;

    var_r31 = &lbl_1_bss_F0[arg0];
    var_r30 = 0;
    if (lbl_1_bss_98C < 4) {
        if (!GWPlayerCfg[arg0].iscom) {
            (arg1) ? (var_r30 = HuPadTrigR[var_r31->unk_4C]) : (var_r30 = HuPadTrigL[var_r31->unk_4C]);
        }
        else {
            (arg1) ? (var_r30 = var_r31->unk_1FE) : (var_r30 = var_r31->unk_1FF);
        }
    }
    return var_r30;
}

u16 fn_1_56FC(s32 arg0)
{
    UnkM414BssF0Struct *var_r31;
    u16 var_r30;

    var_r31 = &lbl_1_bss_F0[arg0];
    var_r30 = 0;
    if (lbl_1_bss_98C < 4) {
        if (!GWPlayerCfg[arg0].iscom) {
            var_r30 = HuPadBtnDown[var_r31->unk_4C];
        }
        else {
            var_r30 = var_r31->unk_200;
        }
    }
    return var_r30;
}

void fn_1_5780(UnkM414BssF0Struct *arg0, float arg8)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;

    s32 var_r31;

    var_f29 = 60.0f;
    var_f31 = 180.0f + arg8;
    if (var_f31 > 360.0f) {
        var_f31 -= 360.0f;
    }
    for (var_r31 = 0, var_f30 = 40.0f; var_r31 < 16; var_r31++) {
        if (var_f30 < var_f29 || var_f31 < var_f29) {
            var_f30 += var_f29;
            var_f31 += var_f29;
        }
        if (var_f30 - var_f31 >= 0.0f) {
            var_f27 = var_f30 - var_f31;
        }
        else {
            var_f27 = -(var_f30 - var_f31);
        }
        var_f28 = var_f27;
        if (var_f28 < var_f29 || arg0->unk_F4[var_r31] == 1) {
            Hu3DModelAttrSet(arg0->unk_94[var_r31], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(arg0->unk_94[var_r31], HU3D_ATTR_DISPOFF);
        }
        if (var_f28 < var_f29) {
            Hu3DModelAttrSet(arg0->unk_D4[var_r31], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(arg0->unk_D4[var_r31], HU3D_ATTR_DISPOFF);
        }
        if (var_r31 & 1) {
            var_f30 += 40.0f;
        }
    }
    var_f31 = 180.0f + arg8;
    if (var_f31 > 360.0f) {
        var_f31 -= 360.0f;
    }
    for (var_r31 = 0, var_f30 = 0.0f; var_r31 < 9; var_f30 += 40.0f, var_r31++) {
        if (var_f30 < var_f29 || var_f31 < var_f29) {
            var_f30 += var_f29;
            var_f31 += var_f29;
        }
        if (var_f30 - var_f31 >= 0.0f) {
            var_f26 = var_f30 - var_f31;
        }
        else {
            var_f26 = -(var_f30 - var_f31);
        }
        var_f28 = var_f26;
        if (var_f28 < var_f29) {
            Hu3DModelAttrSet(arg0->unk_00[var_r31], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(arg0->unk_00[var_r31], HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_1_5A3C(void)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;

    UnkM414Struct4 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r31 = HuPrcCurrentGet()->user_data;
    HuPrcSleep(10);
    var_r28 = var_r31->unk_00->unk_44;
    var_f26 = lbl_1_bss_920[var_r28];
    fn_1_5780(var_r31->unk_00, lbl_1_bss_920[var_r28]);

    if (var_r31->unk_04) {
        var_f30 = 40.0f + lbl_1_bss_920[var_r28];
        var_f29 = 40.0f;
    }
    else {
        var_f30 = lbl_1_bss_920[var_r28] - 40.0f;
        var_f29 = -40.0f;
    }
    if (var_f30 >= 360.0f) {
        var_f30 -= 360.0f;
    }
    if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    for (var_r30 = 0; var_r30 < 9; var_r30++) {
        Hu3DModelAttrSet(var_r31->unk_00->unk_00[var_r30], HU3D_MOTATTR_PAUSE);
    }
    for (var_r30 = 0, var_f28 = 0.0f; var_r30 < 10; var_r30++, var_f28 += 9.0f) {
        var_f27 = (var_f29 / 2) * (1.0 - cosd(var_f28));
        lbl_1_bss_920[var_r28] = var_f26 + var_f27;
        for (var_r29 = 0; var_r29 < 9; var_r29++) {
            if (!var_r31->unk_04) {
                var_f31 = (var_f27 / var_f29) * Hu3DMotionMaxTimeGet(var_r31->unk_00->unk_00[var_r29]);
            }
            else {
                var_f31 = Hu3DMotionMaxTimeGet(var_r31->unk_00->unk_00[var_r29])
                    - (var_f27 / var_f29) * Hu3DMotionMaxTimeGet(var_r31->unk_00->unk_00[var_r29]);
            }
            Hu3DMotionTimeSet(var_r31->unk_00->unk_00[var_r29], ABS_INV(var_f31));
        }
        HuPrcVSleep();
    }
    for (var_r30 = 0, var_f28 = 0.0f; var_r30 < 10; var_r30++, var_f28 += 9.0f) {
        var_f27 = (var_f29 / 2) + ((var_f29 / 2) * sind(var_f28));
        lbl_1_bss_920[var_r28] = var_f26 + var_f27;
        for (var_r29 = 0; var_r29 < 9; var_r29++) {
            if (!var_r31->unk_04) {
                var_f31 = (var_f27 / var_f29) * Hu3DMotionMaxTimeGet(var_r31->unk_00->unk_00[var_r29]);
            }
            else {
                var_f31 = Hu3DMotionMaxTimeGet(var_r31->unk_00->unk_00[var_r29])
                    - (var_f27 / var_f29) * Hu3DMotionMaxTimeGet(var_r31->unk_00->unk_00[var_r29]);
            }
            Hu3DMotionTimeSet(var_r31->unk_00->unk_00[var_r29], ABS_INV(var_f31));
        }
        HuPrcVSleep();
    }
    if (!var_r31->unk_04) {
        for (var_r30 = 0; var_r30 < 9; var_r30++) {
            Hu3DMotionTimeSet(var_r31->unk_00->unk_00[var_r30], Hu3DMotionMaxTimeGet(var_r31->unk_00->unk_00[var_r30]));
        }
    }
    else {
        for (var_r30 = 0; var_r30 < 9; var_r30++) {
            Hu3DMotionTimeSet(var_r31->unk_00->unk_00[var_r30], 0.0f);
        }
    }
    lbl_1_bss_920[var_r28] = var_f30;
    *var_r31->unk_08_ptr = 0;
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_5EE8(void)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    UnkM414Struct4 *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = HuPrcCurrentGet()->user_data;
    var_r29 = var_r31->unk_00->unk_44;
    var_f28 = lbl_1_bss_920[var_r29];
    if (var_r31->unk_04) {
        var_f31 = 40.0f + lbl_1_bss_920[var_r29];
        var_f29 = 40.0f;
    }
    else {
        var_f31 = lbl_1_bss_920[var_r29] - 40.0f;
        var_f29 = -40.0f;
    }
    if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    for (var_r30 = 0, var_f30 = 0.0f; var_r30 < 15; var_r30++, var_f30 += 6.0f) {
        var_r31->unk_00->unk_70 = var_f28 + ((var_f29 / 2) * (1.0 - cosd(var_f30)));
        HuPrcVSleep();
    }
    for (var_r30 = 0, var_f30 = 0.0f; var_r30 < 15; var_r30++, var_f30 += 6.0f) {
        var_r31->unk_00->unk_70 = (var_f29 / 2) + (var_f28 + ((var_f29 / 2) * sind(var_f30)));
        HuPrcVSleep();
    }
    var_r31->unk_00->unk_70 = var_f31;
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_6134(void)
{
    float var_f31;
    float var_f30;
    float var_f29;

    UnkM414BssF0Struct *var_r31;
    s32 var_r30;

    var_r31 = HuPrcCurrentGet()->user_data;
    for (var_r30 = 0, var_f31 = 0.0f; var_r30 < 10; var_r30++, var_f31 += 18.0f) {
        var_f30 = 50.0 * sind(lbl_1_bss_920[var_r31->unk_44]) * sind(var_f31);
        var_f29 = 50.0 * cosd(lbl_1_bss_920[var_r31->unk_44]) * sind(var_f31);
        Hu3DModelPosSet(var_r31->unk_12, (2000.0f * (var_r31->unk_44 % 2)) + (var_r31->unk_60 + var_f30), var_r31->unk_64,
            (2000.0f * (var_r31->unk_44 / 2)) + (var_r31->unk_68 + var_f29));
        Hu3DModelPosSet(var_r31->unk_20, var_f30 + (2000.0f * (var_r31->unk_44 % 2)), 0.0f, var_f29 + (2000.0f * (var_r31->unk_44 / 2)));
        HuPrcVSleep();
    }
    Hu3DModelPosSet(
        var_r31->unk_12, var_r31->unk_60 + (2000.0f * (var_r31->unk_44 % 2)), var_r31->unk_64, var_r31->unk_68 + (2000.0f * (var_r31->unk_44 / 2)));
    Hu3DModelPosSet(var_r31->unk_20, 2000.0f * (var_r31->unk_44 % 2), 0.0f, 2000.0f * (var_r31->unk_44 / 2));
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 fn_1_654C(s32 arg0, s32 arg1)
{
    float var_f31;
    s32 var_r31;

    for (var_r31 = 0, var_f31 = 40.0f; var_r31 < 16; var_f31 += 40.0f, var_r31 += 2) {
        if (var_f31 == lbl_1_bss_920[arg0]) {
            if (arg1) {
                var_r31++;
            }
            break;
        }
    }
    if (var_r31 >= 16) {
        var_r31 = -1;
    }
    return var_r31;
}

s32 fn_1_65DC(UnkM414BssF0Struct *arg0, s32 arg1)
{
    s32 var_r31;

    var_r31 = 1;
    if (Hu3DModelMotionAttrGet(arg0->unk_D4[arg1]) & 0x40000004) {
        var_r31 = 0;
    }
    return var_r31;
}

void fn_1_6644(void)
{
    UnkM414Struct4 sp9C;
    UnkM414Struct2 sp8C;

    UnkM414BssF0Struct *var_r31;
    Process *var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r31 = HuPrcCurrentGet()->user_data;
    var_r31->unk_50 = 0;
    var_r31->unk_1F4 = 1;
    var_r31->unk_1F8 = -1;
    var_r31->unk_204 = 0;

    while (!lbl_1_bss_98C) {
        HuPrcVSleep();
    }
    lbl_1_bss_98C = 2;

    while (lbl_1_bss_98C == 2) {
        HuPrcVSleep();
    }
    var_r31->unk_58 = 0;
    lbl_1_bss_97C[var_r31->unk_44] = 0;

    while (TRUE) {
        lbl_1_bss_930[0] = lbl_1_bss_930[1] = 0;
        if (GWPlayerCfg[var_r31->unk_44].iscom == 1) {
            fn_1_4E10(var_r31);
        }
        if (var_r31->unk_1F4 == 3 && Hu3DMotionEndCheck(var_r31->unk_20)) {
            if (0.0f == Hu3DMotionTimeGet(var_r31->unk_20)) {
                Hu3DMotionSet(var_r31->unk_20, var_r31->unk_22[0]);
                var_r31->unk_1F4 = 1;
            }
            else {
                var_r31->unk_1F4 = 2;
                Hu3DMotionSet(var_r31->unk_20, var_r31->unk_22[0]);
                Hu3DMotionTimeSet(var_r31->unk_20, Hu3DMotionMaxTimeGet(var_r31->unk_20));
            }
        }
        if (var_r31->unk_1F4 == 4 && Hu3DMotionEndCheck(var_r31->unk_20)) {
            var_r31->unk_1F4 = 1;
            var_r31->unk_1F8 = -1;
            Hu3DMotionSet(var_r31->unk_20, var_r31->unk_22[0]);
            Hu3DModelAttrSet(var_r31->unk_20, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(var_r31->unk_20, HU3D_MOTATTR_REV);
            Hu3DMotionSpeedSet(var_r31->unk_20, 2.0f);
        }
        if (var_r31->unk_1F4 == 5 && Hu3DMotionEndCheck(var_r31->unk_20)) {
            var_r31->unk_1F4 = 2;
            var_r31->unk_1F8 = -1;
            Hu3DMotionSet(var_r31->unk_20, var_r31->unk_22[0]);
            Hu3DModelAttrReset(var_r31->unk_20, HU3D_MOTATTR_REV);
            Hu3DMotionTimeSet(var_r31->unk_20, Hu3DMotionMaxTimeGet(var_r31->unk_20));
            Hu3DMotionSpeedSet(var_r31->unk_20, 2.0f);
        }
        if ((fn_1_56FC(var_r31->unk_44) & PAD_BUTTON_A) && !var_r31->unk_58) {
            if (fn_1_654C(var_r31->unk_44, 0) != -1) {
                if (var_r31->unk_1F4 == 1) {
                    var_r29 = fn_1_654C(var_r31->unk_44, 0);
                    if (!var_r31->unk_F4[var_r29]) {
                        if (var_r31->unk_44 & 1) {
                            HuAudFXPlay(1442);
                        }
                        else {
                            HuAudFXPlay(1441);
                        }
                        omVibrate(var_r31->unk_44, 12, 6, 6);
                        var_r31->unk_1F4 = 4;
                        var_r31->unk_1F8 = var_r29;
                        Hu3DMotionSet(var_r31->unk_20, var_r31->unk_22[1]);
                        Hu3DModelAttrReset(var_r31->unk_20, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
                        Hu3DMotionSpeedSet(var_r31->unk_20, 1.0f);
                        var_r30 = HuPrcChildCreate(fn_1_6134, 8192, 8192, 0, HuPrcCurrentGet());
                        var_r30->user_data = var_r31;
                        if (lbl_1_bss_978 == lbl_1_bss_938[var_r29] && fn_1_65DC(var_r31, var_r29)) {
                            Hu3DModelAttrReset(
                                var_r31->unk_D4[var_r29], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV | HU3D_MOTATTR_SHAPE_PAUSE | HU3D_MOTATTR_SHAPE_REV);
                            var_r30 = HuPrcChildCreate(fn_1_42AC, 8192, 8192, 0, HuPrcCurrentGet());
                            var_r30->user_data = &sp8C;
                            sp8C.unk_00 = var_r31;
                            sp8C.unk_08 = 0;
                            sp8C.unk_0C = 1;
                            sp8C.unk_04 = fn_1_654C(var_r31->unk_44, sp8C.unk_08);
                            while (sp8C.unk_0C) {
                                HuPrcVSleep();
                            }
                        }
                        else {
                            HuPrcSleep(10);
                            Hu3DModelAttrReset(var_r31->unk_D4[var_r29], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
                            Hu3DModelAttrSet(var_r31->unk_D4[var_r29], HU3D_MOTATTR_REV | HU3D_MOTATTR_SHAPE_REV);
                            HuPrcSleep(10);
                            omVibrate(var_r31->unk_44, 12, 4, 2);
                            var_r30 = HuPrcChildCreate(fn_1_1C48, 8192, 8192, 0, HuPrcCurrentGet());
                            var_r30->user_data = var_r31;

                            fn_1_CD8(0, var_r31->unk_44, 5.0f);
                            Hu3DModelAttrSet(var_r31->unk_20, HU3D_MOTATTR_REV);
                            HuPrcSleep(10);
                            if (var_r31->unk_44 & 1) {
                                HuAudFXPlay(1444);
                            }
                            else {
                                HuAudFXPlay(1443);
                            }
                            Hu3DModelAttrReset(var_r31->unk_D4[var_r29], HU3D_MOTATTR_REV);
                            HuPrcSleep(10);
                        }
                    }
                }
                else if (var_r31->unk_1F4 == 2) {
                    var_r29 = fn_1_654C(var_r31->unk_44, 1);
                    if (!var_r31->unk_F4[var_r29]) {
                        if (var_r31->unk_44 & 1) {
                            HuAudFXPlay(1442);
                        }
                        else {
                            HuAudFXPlay(1441);
                        }
                        omVibrate(var_r31->unk_44, 12, 6, 6);
                        var_r31->unk_1F4 = 5;
                        var_r31->unk_1F8 = var_r29;
                        Hu3DMotionSet(var_r31->unk_20, var_r31->unk_22[2]);
                        Hu3DMotionSpeedSet(var_r31->unk_20, 1.0f);
                        var_r30 = HuPrcChildCreate(fn_1_6134, 8192, 8192, 0, HuPrcCurrentGet());
                        var_r30->user_data = var_r31;
                        if (lbl_1_bss_978 == lbl_1_bss_938[var_r29] && fn_1_65DC(var_r31, var_r29)) {
                            Hu3DModelAttrReset(
                                var_r31->unk_D4[var_r29], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV | HU3D_MOTATTR_SHAPE_PAUSE | HU3D_MOTATTR_SHAPE_REV);
                            var_r30 = HuPrcChildCreate(fn_1_42AC, 8192, 8192, 0, HuPrcCurrentGet());
                            var_r30->user_data = &sp8C;
                            sp8C.unk_00 = var_r31;
                            sp8C.unk_08 = 1;
                            sp8C.unk_0C = 1;
                            sp8C.unk_04 = fn_1_654C(var_r31->unk_44, sp8C.unk_08);
                            while (sp8C.unk_0C) {
                                HuPrcVSleep();
                            }
                        }
                        else {
                            HuPrcSleep(10);
                            Hu3DModelAttrReset(var_r31->unk_D4[var_r29], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
                            Hu3DModelAttrSet(var_r31->unk_D4[var_r29], HU3D_MOTATTR_REV | HU3D_MOTATTR_SHAPE_REV);
                            HuPrcSleep(10);
                            omVibrate(var_r31->unk_44, 12, 4, 2);
                            var_r30 = HuPrcChildCreate(fn_1_1C48, 8192, 8192, 0, HuPrcCurrentGet());
                            var_r30->user_data = var_r31;
                            fn_1_CD8(0, var_r31->unk_44, 5.0f);
                            Hu3DModelAttrSet(var_r31->unk_20, HU3D_MOTATTR_REV);
                            HuPrcSleep(15);
                            if (var_r31->unk_44 & 1) {
                                HuAudFXPlay(1444);
                            }
                            else {
                                HuAudFXPlay(1443);
                            }
                            Hu3DModelAttrReset(var_r31->unk_D4[var_r29], HU3D_MOTATTR_REV);
                            HuPrcSleep(15);
                        }
                    }
                }
            }
        }
        if (fn_1_5554(var_r31->unk_44, 1) > 20 && (var_r31->unk_1F4 == 2 || var_r31->unk_1F4 == 0)) {
            Hu3DModelAttrReset(var_r31->unk_20, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(var_r31->unk_20, HU3D_MOTATTR_REV);
            var_r31->unk_1F4 = 3;
            Hu3DModelAttrReset(var_r31->unk_12, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(var_r31->unk_12, HU3D_MOTATTR_REV);
            Hu3DMotionSpeedSet(var_r31->unk_12, 2.0f);
        }
        if (fn_1_5554(var_r31->unk_44, 1) < -20 && (var_r31->unk_1F4 == 1 || var_r31->unk_1F4 == 0)) {
            Hu3DModelAttrReset(var_r31->unk_20, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
            var_r31->unk_1F4 = 3;
            Hu3DModelAttrReset(var_r31->unk_12, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
            Hu3DMotionSpeedSet(var_r31->unk_12, 2.0f);
        }
        if (!var_r31->unk_58) {
            var_r28 = -1;
            if (fn_1_5624(var_r31->unk_44, 0) > 20 && var_r28 == -1) {
                var_r28 = 1;
            }
            if (fn_1_5624(var_r31->unk_44, 1) > 20 && var_r28 == -1) {
                var_r28 = 0;
            }
            if (var_r28 != -1) {
                if (var_r28) {
                    if (var_r31->unk_44 & 1) {
                        HuAudFXPlay(1440);
                    }
                    else {
                        HuAudFXPlay(1439);
                    }
                }
                else if (var_r31->unk_44 & 1) {
                    HuAudFXPlay(1438);
                }
                else {
                    HuAudFXPlay(1437);
                }
                var_r31->unk_58 = 1;
                var_r30 = HuPrcChildCreate(fn_1_5A3C, 8192, 8192, 0, HuPrcCurrentGet());
                var_r30->user_data = &sp9C;
                sp9C.unk_00 = var_r31;
                sp9C.unk_04 = var_r28;
                sp9C.unk_08_ptr = &var_r31->unk_58;
                var_r30 = HuPrcChildCreate(fn_1_5EE8, 8192, 8192, 0, HuPrcCurrentGet());
                var_r30->user_data = &sp9C;
                sp9C.unk_00 = var_r31;
                sp9C.unk_04 = var_r28;
            }
        }
        var_r31->unk_60 = 37.0 * sind(var_r31->unk_70);
        var_r31->unk_68 = 37.0 * cosd(var_r31->unk_70);

        Hu3DModelPosSet(var_r31->unk_12, var_r31->unk_60 + (2000.0f * (var_r31->unk_44 % 2)), var_r31->unk_64,
            var_r31->unk_68 + (2000.0f * (var_r31->unk_44 / 2)));
        Hu3DModelRotSet(var_r31->unk_12, var_r31->unk_6C, var_r31->unk_70 + var_r31->unk_90, var_r31->unk_74);
        Hu3DModelRotSet(var_r31->unk_20, var_r31->unk_6C, var_r31->unk_70, var_r31->unk_74);
        HuPrcVSleep();
    }
}

void fn_1_76F4(void)
{
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;

    UnkM414BssF0Struct *var_r31;

    var_r31 = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        if (var_r31->unk_1F4 != 4 && var_r31->unk_1F4 != 5) {
            sp14.x = (2000.0f * (var_r31->unk_44 % 2)) + (-950.0 * sind(var_r31->unk_70));
            sp14.z = (2000.0f * (var_r31->unk_44 / 2)) + (-950.0 * cosd(var_r31->unk_70));
            var_f29 = Hu3DMotionMaxTimeGet(var_r31->unk_20);
            sp14.y = 220.0f + (350.0f * (1.0f - (Hu3DMotionTimeGet(var_r31->unk_20) / var_f29)));
            Hu3D3Dto2D(&sp14, 1 << var_r31->unk_48, &sp8);
            var_f31 = (282.0f * (var_r31->unk_44 % 2)) + (sp8.x / 2);
            var_f30 = (225.0f * (var_r31->unk_44 / 2)) + (sp8.y / 2);
            var_f31 += 3.0f;
            var_f30 -= 15.0f;
            HuSprGrpPosSet(var_r31->unk_2C, var_f31, var_f30);
        }
        HuPrcVSleep();
    }
}
void fn_1_79A8(void)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    UnkM414BssF0Struct *var_r31;
    s32 var_r30;
    s32 var_r29;
    UnkM414BssF0Struct *var_r28;
    Process *var_r27;

    HuAudFXPlay(lbl_1_data_8C[lbl_1_bss_978]);
    HuPrcSleep(60);
    HuAudFXPlay(1449);
    var_f31 = var_f30 = 0.0f;
    var_f29 = 640.0f;
    var_f28 = 480.0f;
    for (var_r29 = 0; var_r29 < 30; var_r29++) {
        Hu3DCameraViewportSet(16, var_f31, var_f30, var_f29, var_f28, 0.0f, 1.0f);
        Hu3DCameraScissorSet(16, var_f31, var_f30, var_f29, var_f28);
        var_f31 += 10.666667f;
        var_f30 += 8.0f;
        var_f29 -= 21.333334f;
        var_f28 -= 16.0f;
        HuPrcVSleep();
    }
    Hu3DCameraViewportSet(16, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(16, 0, 0, 0, 0);
    Hu3DModelAttrSet(lbl_1_bss_A10, HU3D_ATTR_DISPOFF);
    HuPrcSleep(30);
    for (var_r29 = 0; var_r29 < 45; var_r29++) {
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            lbl_1_bss_910[var_r30] -= 23.777779f;
            lbl_1_bss_A0[var_r30].y -= 3.5555556f;
            lbl_1_bss_64[var_r30].y -= 6.2222223f;
        }
        HuPrcVSleep();
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r31 = &lbl_1_bss_F0[var_r30];
        CharModelMotionSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], var_r31->unk_14[5]);
        CharModelMotionTimeSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], 61.0f);
        CharModelMotionSpeedSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], 2.0f);
    }
    for (var_r29 = 0; var_r29 < 30; var_r29++) {
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            var_r31 = &lbl_1_bss_F0[var_r30];
            var_r31->unk_90 += 6.0f;
            Hu3DModelRotSet(var_r31->unk_12, var_r31->unk_6C, var_r31->unk_70 + var_r31->unk_90, var_r31->unk_74);
        }
        HuPrcVSleep();
    }
    var_r31->unk_90 = 180.0f;
    Hu3DModelRotSet(var_r31->unk_12, var_r31->unk_6C, var_r31->unk_70 + var_r31->unk_90, var_r31->unk_74);
    CharModelMotionSpeedSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], 1.0f);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r31 = &lbl_1_bss_F0[var_r30];
        CharModelMotionShiftSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], var_r31->unk_14[1], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    }
    HuPrcSleep(5);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r31 = &lbl_1_bss_F0[var_r30];
        Hu3DModelAttrSet(var_r31->unk_12, HU3D_MOTATTR_PAUSE);
    }
    HuPrcChildCreate(fn_1_397C, 4096, 8192, 0, HuPrcCurrentGet());
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r28 = &lbl_1_bss_F0[var_r30];
        var_r27 = HuPrcChildCreate(fn_1_76F4, 8192, 8192, 0, HuPrcCurrentGet());
        var_r27->user_data = var_r28;
        HuSprAttrReset(var_r28->unk_2C, 0, HUSPR_ATTR_DISPOFF);
    }
    for (var_r29 = 0, var_f27 = 0.0f; var_r29 < 15; var_r29++) {
        var_f27 += 0.06666667f;
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            var_r28 = &lbl_1_bss_F0[var_r30];
            HuSprScaleSet(var_r28->unk_2C, 0, var_f27, var_f27);
        }
        HuPrcVSleep();
    }
}

void fn_1_7FC8(s32 arg0)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    UnkM414BssF0Struct *var_r31;
    UnkM414BssF0Struct *var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    if (arg0 != -1) {
        for (var_r28 = 0, var_r29 = 0; var_r28 < 16; var_r28++) {
            if (lbl_1_bss_978 == lbl_1_bss_938[var_r28]) {
                var_r30 = &lbl_1_bss_F0[arg0];
                switch (var_r29) {
                    case 0:
                        var_f30 = 35.0f + var_r30->unk_70;
                        var_f28 = 240.0f;
                        break;
                    case 1:
                        var_f30 = var_r30->unk_70 - 35.0f;
                        var_f28 = 240.0f;
                        break;
                    default:
                        var_f30 = var_r30->unk_70;
                        var_f28 = 240.0f;
                        break;
                }
                Hu3DMotionSet(var_r30->unk_94[var_r28], var_r30->unk_B4[var_r28]);
                var_f31 = 0.0f;
                if (!lbl_1_bss_938[var_r28]) {
                    var_f31 += 70.0f;
                }
                Hu3DModelPosSet(var_r30->unk_94[var_r28], (2000.0f * (arg0 % 2) + (250.0 * sind(var_f30))), var_f31,
                    (2000.0f * (arg0 / 2)) + (250.0 * cosd(var_f30)));
                Hu3DModelRotSet(var_r30->unk_94[var_r28], var_r30->unk_6C, var_r30->unk_70, var_r30->unk_74);
                if (lbl_1_bss_978 == 2) {
                    Hu3DModelScaleSet(var_r30->unk_94[var_r28], 1.0f, 1.0f, 1.0f);
                }
                Hu3DModelAttrReset(var_r30->unk_94[var_r28], HU3D_ATTR_DISPOFF);
                Hu3DModelShadowSet(var_r30->unk_94[var_r28]);
                if (var_r29++ >= 2) {
                    break;
                }
            }
        }
    }
    for (var_r27 = 0; var_r27 < 4; var_r27++) {
        var_r30 = &lbl_1_bss_F0[var_r27];
        var_f31 = 40.0f + lbl_1_bss_920[var_r30->unk_44];
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        var_r29 = 2.0f + (lbl_1_bss_920[var_r30->unk_44] / 40.0f);
        if (var_r29 >= 9) {
            var_r29 -= 9;
        }
        for (var_r28 = 0; var_r28 < 6; var_r28++) {
            Hu3DModelAttrSet(var_r30->unk_30[var_r29], HU3D_ATTR_DISPOFF);
            var_r29++;
            if (var_r29 >= 9) {
                var_r29 = 0;
            }
        }
        Hu3DModelAttrReset(var_r30->unk_42, HU3D_ATTR_DISPOFF);
        Hu3DModelRotSet(var_r30->unk_42, 0.0f, lbl_1_bss_920[var_r30->unk_44], 0.0f);
    }
    for (var_r28 = 0; var_r28 < 30; var_r28++) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            lbl_1_bss_64[var_r29].y -= 7.6666665f;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(lbl_1_data_8C[lbl_1_bss_978]);
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        var_r31 = &lbl_1_bss_F0[var_r29];
        CharModelMotionShiftSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], var_r31->unk_14[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    }
    HuPrcSleep(5);
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        var_r31 = &lbl_1_bss_F0[var_r29];
        CharModelMotionSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], var_r31->unk_14[5]);
        Hu3DModelAttrReset(var_r31->unk_12, HU3D_MOTATTR_LOOP);
        CharModelMotionTimeSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], 61.0f);
        CharModelMotionSpeedSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], 2.0f);
    }
    for (var_f29 = 37.0f, var_r28 = 0; var_r28 < 30; var_r28++, var_f29 += 1.6666666f) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            var_r31 = &lbl_1_bss_F0[var_r29];
            var_r31->unk_90 += 6.0f;
            Hu3DModelRotSet(var_r31->unk_12, var_r31->unk_6C, var_r31->unk_70 + var_r31->unk_90, var_r31->unk_74);
            var_r31->unk_60 = var_f29 * sind(var_r31->unk_70);
            var_r31->unk_68 = var_f29 * cosd(var_r31->unk_70);
            Hu3DModelPosSet(var_r31->unk_12, var_r31->unk_60 + (2000.0f * (var_r31->unk_44 % 2)), var_r31->unk_64,
                var_r31->unk_68 + (2000.0f * (var_r31->unk_44 / 2)));
        }
        HuPrcVSleep();
    }
    var_r31->unk_90 = 0.0f;
    Hu3DModelRotSet(var_r31->unk_12, var_r31->unk_6C, var_r31->unk_70 + var_r31->unk_90, var_r31->unk_74);
    CharModelMotionSpeedSet(lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], 1.0f);
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        var_r31 = &lbl_1_bss_F0[var_r29];
        CharModelMotionShiftSet(
            lbl_1_data_30[GWPlayerCfg[var_r31->unk_44].character], var_r31->unk_14[var_r31->unk_44 == arg0 ? 3 : 4], 0.0f, 5.0f, 0);
    }
}

void fn_1_88D4(void)
{
    UnkM414BssF0Struct *var_r31;

    var_r31 = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        if (var_r31->unk_1F4 == 4 || var_r31->unk_1F4 == 5 || var_r31->unk_58) {
            HuPrcVSleep();
        }
        else {
            break;
        }
    }
    HuPrcCurrentGet()->user_data = NULL;
    HuPrcKill(lbl_1_bss_E0[var_r31->unk_44]);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_894C(void)
{
    Process *sp8[4];

    s32 var_r31;
    s32 var_r30;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp8[var_r31] = HuPrcChildCreate(fn_1_88D4, 8192, 8192, 0, HuPrcCurrentGet());
        sp8[var_r31]->user_data = &lbl_1_bss_F0[var_r31];
    }
    while (TRUE) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (sp8[var_r31]->user_data) {
                break;
            }
        }
        if (var_r31 < 4) {
            HuPrcVSleep();
        }
        else {
            break;
        }
    }
    HuPrcCurrentGet()->user_data = NULL;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_8A10(void)
{
    while (TRUE) {
        if (omSysExitReq == 1) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            HuPrcSleep(60);
            MGSeqKillAll();
            omOvlReturnEx(1, 1);
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_8A70(void)
{
    float var_f31;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s16 var_r28;
    s16 var_r27;
    s32 var_r26;
    Process *var_r25;
    s16 var_r24;
    UnkM414BssF0Struct *var_r23;
    s32 var_r22;
    UnkM414BssF0Struct *var_r21;

    lbl_1_bss_98C = 0;
    HuPrcSleep(1.0f + wipeData.duration);
    fn_1_79A8();
    HuPrcSleep(30);
    lbl_1_bss_98C = 1;

    while (lbl_1_bss_98C == 1) {
        HuPrcVSleep();
    }

    var_r22 = HuAudSeqPlay(72);
    var_r28 = MGSeqCreate(3, 0);
    while (MGSeqStatGet(var_r28)) {
        HuPrcVSleep();
    }
    var_r27 = 3659;
    var_r24 = MGSeqCreate(1, var_r27 / 60, -1, -1);
    lbl_1_bss_98C = 3;
    while (TRUE) {
        for (var_r31 = 0, var_r30 = 0; var_r31 < 4; var_r31++) {
            var_r21 = &lbl_1_bss_F0[var_r31];
            if (lbl_1_bss_97C[var_r31] >= 3) {
                var_r30++;
                var_r29 = var_r31;
            }
        }
        if (var_r30 > 0) {
            break;
        }
        if (var_r27 < 59) {
            var_r29 = -1;
            break;
        }
        MGSeqParamSet(var_r24, 1, var_r27-- / 60);
        HuPrcVSleep();
    }
    lbl_1_bss_98C = 4;
    HuAudSeqFadeOut(var_r22, 100);
    MGSeqParamSet(var_r24, 2, -1);
    var_r28 = MGSeqCreate(3, 1);
    var_r25 = HuPrcChildCreate(fn_1_894C, 8192, 8192, 0, HuPrcCurrentGet());
    var_r25->user_data = (void *)1;

    while (var_r25->user_data) {
        HuPrcVSleep();
    }
    for (var_r31 = 0, var_r30 = 0; var_r31 < 4; var_r31++) {
        var_r21 = &lbl_1_bss_F0[var_r31];
        if (lbl_1_bss_97C[var_r31] >= 3) {
            var_r30++;
            var_r29 = var_r31;
        }
    }

    while (MGSeqStatGet(var_r28)) {
        HuPrcVSleep();
    }
    lbl_1_bss_98C = 5;
    HuPrcChildCreate(fn_1_3A58, 4096, 8192, 0, HuPrcCurrentGet());
    for (var_r31 = 0, var_f31 = 1.0f; var_r31 < 15; var_r31++) {
        for (var_f31 -= 0.06666667f, var_r26 = 0; var_r26 < 4; var_r26++) {
            var_r23 = &lbl_1_bss_F0[var_r26];
            HuSprScaleSet(var_r23->unk_2C, 0, var_f31, var_f31);
        }
        HuPrcVSleep();
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprAttrSet(lbl_1_bss_F0[var_r31].unk_2C, 0, 4);
    }
    HuPrcSleep(15);
    fn_1_7FC8(var_r29);
    if (var_r29 != -1) {
        HuAudSStreamPlay(1);
        GWPlayerCoinWinSet(var_r29, 10);
        var_r28 = MGSeqCreate(5, 3, GWPlayerCfg[var_r29].character, -1, -1, -1);
    }
    else {
        HuAudSStreamPlay(4);
        var_r28 = MGSeqCreate(3, 2);
    }
    HuPrcSleep(210);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuPrcSleep(60);
    HuAudFadeOut(1);
    MGSeqKillAll();
    omOvlReturnEx(1, 1);
    while (TRUE) {
        HuPrcVSleep();
    }
}
