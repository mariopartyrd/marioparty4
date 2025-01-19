#include "REL/m447dll.h"
#include "game/audio.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/sprite.h"

#include "ext_math.h"

void fn_1_8F7C(void *arg0);
void fn_1_910C(void);
void fn_1_9158(UnkM447Struct_01 *arg0);
void fn_1_9320(UnkM447Struct_01 *arg0);
void fn_1_9374(UnkM447Struct_01 *arg0);
void fn_1_9538(UnkM447Struct_01 *arg0);
void fn_1_953C(UnkM447Struct_01 *arg0);
void fn_1_9758(UnkM447Struct_01 *arg0);
void fn_1_991C(UnkM447Struct_01 *arg0);
void fn_1_9BCC(UnkM447Struct_01 *arg0);
void fn_1_9CEC(UnkM447Struct_01 *arg0);
void fn_1_9EEC(UnkM447Struct_01 *arg0);
void fn_1_9F40(ModelData *model, ParticleData *particle, Mtx matrix);

u32 lbl_1_bss_B8; // Maybe part of another file with fn_1_A230 and fn_1_A240.
UnkM447Struct_01 *lbl_1_bss_A4[5];
s32 lbl_1_bss_A0;

const s32 lbl_1_rodata_5F8[]
    = { DATA_MAKE_NUM(DATADIR_M447, 12), DATA_MAKE_NUM(DATADIR_M447, 13), DATA_MAKE_NUM(DATADIR_M447, 10), DATA_MAKE_NUM(DATADIR_M447, 11),
          DATA_MAKE_NUM(DATADIR_M447, 4), DATA_MAKE_NUM(DATADIR_M447, 5), DATA_MAKE_NUM(DATADIR_M447, 16), DATA_MAKE_NUM(DATADIR_M447, 17),
          DATA_MAKE_NUM(DATADIR_M447, 8), DATA_MAKE_NUM(DATADIR_M447, 9), DATA_MAKE_NUM(DATADIR_M447, 6), DATA_MAKE_NUM(DATADIR_M447, 7),
          DATA_MAKE_NUM(DATADIR_M447, 18), DATA_MAKE_NUM(DATADIR_M447, 19), DATA_MAKE_NUM(DATADIR_M447, 20), DATA_MAKE_NUM(DATADIR_M447, 21),
          DATA_MAKE_NUM(DATADIR_M447, 22), DATA_MAKE_NUM(DATADIR_M447, 23), DATA_MAKE_NUM(DATADIR_M447, 14), DATA_MAKE_NUM(DATADIR_M447, 15) };

const float lbl_1_rodata_648[20]
    = { 30.0f, 30.0f, 80.0f, 30.0f, 80.0f, 80.0f, 60.0f, 60.0f, 80.0f, 80.0f, 30.0f, 30.0f, 45.0f, 45.0f, 50.0f, 50.0f, 30.0f, 30.0f, 75.0f, 50.0f };

UnkM447Struct_01 *fn_1_8DF8(void)
{
    UnkM447Struct_01 *temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r3), MEMORY_DEFAULT_NUM);
    if (!temp_r3) {
        OSReport("M447BlockCreate ERROR...\n");
        return NULL;
    }
    temp_r3->unk04 = 0;
    temp_r3->unk00 = 0;
    temp_r3->unk08 = 0;
    temp_r3->unk0C = 0;
    temp_r3->unk10.x = 0.0f;
    temp_r3->unk10.y = 0.0f;
    temp_r3->unk10.z = 0.0f;
    temp_r3->unk40 = 0.0f;
    temp_r3->unk44 = 0.0f;
    temp_r3->unk48 = 0.0f;
    temp_r3->unk4C = 0.0f;
    temp_r3->unk50 = 0.0f;
    temp_r3->unk54 = 0.0f;
    temp_r3->unk1C.x = 0.0f;
    temp_r3->unk1C.y = 0.0f;
    temp_r3->unk1C.z = 0.0f;
    temp_r3->unk8C = 1.0f;
    fn_1_9158(temp_r3);
    temp_r3->unkA4 = HuPrcChildCreate(fn_1_910C, 105, 0x3000, 0, lbl_1_bss_4);
    temp_r3->unkA4->user_data = temp_r3;
    return temp_r3;
}

void fn_1_8F7C(void *arg0)
{
    fn_1_8F7C(arg0);
    HuMemDirectFree(arg0);
}

void fn_1_8FF4(UnkM447Struct_01 *arg0, s32 arg1)
{
    arg0->unk04 = arg1;
    arg0->unk0C = 0;
}

void fn_1_9004(UnkM447Struct_01 *arg0, s32 arg1, s32 arg2)
{
    if (lbl_1_bss_A0 != 0) {
        arg0->unk00 = arg1 * 2 + (arg2 != 0 ? 0 : 1);
    }
    else {
        arg0->unk00 = arg1 * 2 + (arg2 != 0 ? 1 : 0);
    }
    arg0->unk08 = arg2;
    arg0->unk8C = 1.0f;
    arg0->unk4C = 1.0f;
    arg0->unk50 = 1.0f;
    arg0->unk54 = 1.0f;
    Hu3DModelAttrSet(arg0->unk58[arg0->unk00], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->unk58[21], HU3D_ATTR_DISPOFF);
}

void fn_1_90FC(s32 arg0)
{
    lbl_1_bss_A0 = arg0;
}

void (*lbl_1_data_294[])(UnkM447Struct_01 *) = { fn_1_9538, fn_1_953C, fn_1_9758, fn_1_991C, fn_1_9BCC, fn_1_9CEC };

void fn_1_910C(void)
{
    UnkM447Struct_01 *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        lbl_1_data_294[temp_r31->unk04](temp_r31);
        fn_1_9374(temp_r31);
        HuPrcVSleep();
    }
}

void fn_1_9158(UnkM447Struct_01 *arg0)
{
    s32 i;

    for (i = 0; i <= 19; i++) {
        arg0->unk58[i] = Hu3DModelCreateFile(lbl_1_rodata_5F8[i]);
        Hu3DModelAttrSet(arg0->unk58[i], HU3D_ATTR_ZWRITE_OFF);
        Hu3DModelLayerSet(arg0->unk58[i], 7);
    }
    arg0->unk58[20] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M447, 30));
    Hu3DModelLayerSet(arg0->unk58[20], 7);
    arg0->unk58[21] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M447, 25));
    Hu3DModelLayerSet(arg0->unk58[21], 7);
    arg0->unkA0 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M447, 57));
    arg0->unk58[22] = Hu3DParticleCreate(arg0->unkA0, 64);
    Hu3DParticleHookSet(arg0->unk58[22], fn_1_9F40);
    Hu3DParticleBlendModeSet(arg0->unk58[22], 1);
    Hu3DModelLayerSet(arg0->unk58[22], 6);
    Hu3DModelAttrSet(arg0->unk58[22], HU3D_ATTR_DISPOFF);
    for (i = 0; i <= 19; i++) {
        Hu3DModelAttrSet(arg0->unk58[i], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrReset(arg0->unk58[arg0->unk00], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->unk58[20], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->unk58[21], HU3D_ATTR_DISPOFF);
    for (i = 0; i <= 19; i++) {
        Hu3DModelShadowSet(arg0->unk58[i]);
    }
}

void fn_1_9320(UnkM447Struct_01 *arg0)
{
    s32 i;

    for (i = 0; i < 23; i++) {
        Hu3DModelKill(arg0->unk58[i]);
    }
}

void fn_1_9374(UnkM447Struct_01 *arg0)
{
    ModelData *temp_r30;
    Mtx sp8;

    temp_r30 = &Hu3DData[arg0->unk58[arg0->unk00]];
    MTXIdentity(temp_r30->unk_F0);
    MTXRotRad(sp8, 'x', MTXDegToRad(arg0->unk1C.x));
    MTXConcat(temp_r30->unk_F0, sp8, temp_r30->unk_F0);
    MTXRotRad(sp8, 'y', MTXDegToRad(arg0->unk1C.y));
    MTXConcat(temp_r30->unk_F0, sp8, temp_r30->unk_F0);
    MTXRotRad(sp8, 'z', MTXDegToRad(arg0->unk1C.z));
    MTXConcat(temp_r30->unk_F0, sp8, temp_r30->unk_F0);
    Hu3DModelPosSet(arg0->unk58[arg0->unk00], arg0->unk10.x, arg0->unk10.y, arg0->unk10.z);
    Hu3DModelPosSet(arg0->unk58[20], arg0->unk10.x, arg0->unk10.y - 100.0f, arg0->unk10.z);
    Hu3DModelPosSet(arg0->unk58[21], arg0->unk10.x, arg0->unk10.y, arg0->unk10.z + 120.0f * arg0->unk54);
    Hu3DModelRotSet(arg0->unk58[arg0->unk00], arg0->unk40, arg0->unk44, arg0->unk48);
    Hu3DModelScaleSet(arg0->unk58[arg0->unk00], arg0->unk4C, arg0->unk50, arg0->unk54);
    Hu3DModelScaleSet(arg0->unk58[21], arg0->unk4C, arg0->unk50, arg0->unk54);
    Hu3DModelTPLvlSet(arg0->unk58[arg0->unk00], arg0->unk8C);
}

void fn_1_9538(UnkM447Struct_01 *arg0) { }

void fn_1_953C(UnkM447Struct_01 *arg0)
{
    float temp_f31;

    switch (arg0->unk0C) {
        case 0:
            arg0->unk90 = 0.0f;
            arg0->unk98 = 0.016666668f;
            arg0->unk10.y = -100.0f;
            arg0->unk44 = 0.0f;
            arg0->unk4C = 0.0f;
            arg0->unk50 = 0.0f;
            arg0->unk54 = 0.0f;
            arg0->unk88 = -50.0f;
            Hu3DModelAttrReset(arg0->unk58[arg0->unk00], HU3D_ATTR_DISPOFF);
            arg0->unk0C = 1;
            /* fallthrough */
        case 1:
            arg0->unk44 += arg0->unk88;
            temp_f31 = sind(90.0f * arg0->unk90);
            arg0->unk10.y = -100.0f + 500.0f * temp_f31;
            arg0->unk4C = arg0->unk90;
            arg0->unk50 = arg0->unk90;
            arg0->unk54 = arg0->unk90;
            arg0->unk8C = temp_f31;
            arg0->unk90 += arg0->unk98;
            if (arg0->unk90 < 1.0f) {
                break;
            }
            arg0->unk10.y = 400.0f;
            arg0->unk4C = 1.0f;
            arg0->unk50 = 1.0f;
            arg0->unk54 = 1.0f;
            arg0->unk8C = 1.0f;
            arg0->unk0C = 2;
            /* fallthrough */
        case 2:
            fn_1_8FF4(arg0, 2);
            break;
    }
}

void fn_1_9758(UnkM447Struct_01 *arg0)
{
    float temp_f31;

    switch (arg0->unk0C) {
        case 0:
            arg0->unk90 = 0.1f * (fn_1_A240() % 10);
            arg0->unk98 = 0.011111111f;
            arg0->unk0C = 1;
            /* fallthrough */
        case 1:
            if (arg0->unk88 < -8.0f) {
                arg0->unk88 += 0.05f;
            }
            temp_f31 = sind(180.0f * arg0->unk90);
            temp_f31 *= temp_f31;
            arg0->unk10.y = 400.0f + temp_f31 * 25.0f;
            arg0->unk44 += arg0->unk88;
            arg0->unk90 += arg0->unk98;
            if (arg0->unk90 < 1.0f) {
                break;
            }
            arg0->unk90 = 0.0f;
            break;
        case 2:
            fn_1_8FF4(arg0, 0);
            break;
    }
}

void fn_1_991C(UnkM447Struct_01 *arg0)
{
    float temp_f31;

    switch (arg0->unk0C) {
        case 0:
            arg0->unk90 = 0.0f;
            arg0->unk98 = 0.5f;
            arg0->unk94 = 0.0f;
            arg0->unk9C = 0.05f;
            arg0->unk8C = 1.0f;
            arg0->unk10.y = 400.0f;
            arg0->unk28 = arg0->unk1C;
            arg0->unk34 = 0.0f;
            arg0->unk38 = arg0->unk1C.y;
            arg0->unk3C = 0.0f;
            arg0->unk0C = 1;
            /* fallthrough */
        case 1:
            temp_f31 = arg0->unk94;
            arg0->unk1C.x = arg0->unk28.x + temp_f31 * (arg0->unk34 - arg0->unk28.x);
            arg0->unk1C.y = arg0->unk28.y + temp_f31 * (arg0->unk38 - arg0->unk28.y);
            arg0->unk1C.z = arg0->unk28.z + temp_f31 * (arg0->unk3C - arg0->unk28.z);
            if (arg0->unk94 < 1.0f) {
                arg0->unk94 += arg0->unk9C;
                if (arg0->unk94 > 1.0f) {
                    arg0->unk94 = 1.0f;
                }
            }
            temp_f31 = arg0->unk90;
            arg0->unk10.y = 400.0 + 50.0f * temp_f31 * sind(90) - 4.9f * temp_f31 * temp_f31;
            arg0->unk90 += arg0->unk98;
            if (arg0->unk10.y >= lbl_1_rodata_648[arg0->unk00]) {
                break;
            }
            arg0->unk10.y = lbl_1_rodata_648[arg0->unk00];
            HuAudFXPlay(0x785);
            fn_1_1FEC(lbl_1_bss_10, 30);
            arg0->unk0C = 2;
            /* fallthrough */
        case 2:
            Hu3DModelAttrReset(arg0->unk58[20], HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(arg0->unk58[20], 0.0f);
            fn_1_8FF4(arg0, 4);
            break;
    }
}

void fn_1_9BCC(UnkM447Struct_01 *arg0)
{
    switch (arg0->unk0C) {
        case 0:
            arg0->unk90 = 0.0f;
            arg0->unk98 = 0.016666668f;
            arg0->unk0C = 1;
            /* fallthrough */
        case 1:
            arg0->unk8C = 1.0 - sind(90.0f * arg0->unk90);
            arg0->unk90 += arg0->unk98;
            if (arg0->unk90 < 1.0f) {
                break;
            }
            arg0->unk0C = 2;
            /* fallthrough */
        case 2:
            Hu3DModelAttrSet(arg0->unk58[arg0->unk00], HU3D_ATTR_DISPOFF);
            fn_1_8FF4(arg0, 0);
            break;
    }
}

void fn_1_9CEC(UnkM447Struct_01 *arg0)
{
    float temp_f31;

    switch (arg0->unk0C) {
        case 0:
            arg0->unk90 = 0.0f;
            arg0->unk98 = 0.008333334f;
            Hu3DModelAttrReset(arg0->unk58[21], HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(arg0->unk58[21], 0.0f);
            Hu3DModelAttrSet(arg0->unk58[21], HU3D_MOTATTR_LOOP);
            arg0->unkA8 = arg0->unk10;
            arg0->unkB4 = 0.0f;
            arg0->unkB8 = 200.0f;
            arg0->unkBC = -700.0f - arg0->unk10.z / 2;
            arg0->unkC0 = 0.0f;
            arg0->unkC4 = 400.0f;
            arg0->unkC8 = -700.0f;
            fn_1_9EEC(arg0);
            HuAudFXPlay(0x781);
            arg0->unk0C = 1;
            /* fallthrough */
        case 1:
            temp_f31 = arg0->unk90;
            arg0->unk4C = 1.0f - temp_f31;
            arg0->unk50 = 1.0f - temp_f31;
            arg0->unk54 = 1.0f - temp_f31;
            fn_1_7B54(&arg0->unk10, &arg0->unkA8, 3, temp_f31);
            arg0->unk90 += arg0->unk98;
            if (arg0->unk90 < 1.0f) {
                break;
            }
            arg0->unk0C = 2;
            /* fallthrough */
        case 2:
            fn_1_1EB0(lbl_1_bss_10, 2);
            fn_1_8FF4(arg0, 0);
            break;
    }
}

void fn_1_9EEC(UnkM447Struct_01 *arg0)
{
    ModelData *temp_r30;
    ParticleData *temp_r31;

    temp_r30 = &Hu3DData[arg0->unk58[22]];
    temp_r31 = temp_r30->unk_120;
    temp_r30->attr &= ~1;
    temp_r31->unk_00 = 0;
    temp_r31->unk_02 = 1;
    temp_r31->unk_1C = arg0;
}

void fn_1_9F40(ModelData *model, ParticleData *particle, Mtx matrix)
{
    GXColor sp8 = { 0xFF, 0xFF, 0xFF, 0xFF };
    UnkM447Struct_01 *temp_r29;
    HsfanimStruct01 *var_r31;
    s32 var_r27;
    s32 i;

    if (particle->unk_02 == 0) {
        return;
    }
    temp_r29 = particle->unk_1C;
    if (particle->unk_00 == 0) {
        particle->unk_00 = 1;
        for (i = 0, var_r31 = particle->unk_48; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk00_s16 = i * 5;
            var_r31->unk02 = 0;
            var_r31->unk2C = 0.0f;
            var_r31->unk40.r = sp8.r;
            var_r31->unk40.g = sp8.g;
            var_r31->unk40.b = sp8.b;
            var_r31->unk40.a = sp8.a;
        }
    }
    for (i = 0, var_r27 = 0, var_r31 = particle->unk_48; i < particle->unk_30; i++, var_r31++) {
        if (var_r31->unk00_s16 > 0 && --var_r31->unk00_s16 > 0) {
            continue;
        }
        if (var_r31->unk02 == 0 && temp_r29->unk04 == 5 && temp_r29->unk10.z > -700.0f) {
            var_r31->unk34.x = temp_r29->unk10.x;
            var_r31->unk34.y = temp_r29->unk10.y;
            var_r31->unk34.z = temp_r29->unk10.z;
            var_r31->unk2C = 20.0f;
            var_r31->unk02 = 1;
        }
        else if (var_r31->unk02 == 1) {
            var_r31->unk34.y -= 1.0f;
            var_r31->unk34.z += 3.0f;
            var_r31->unk2C = 20.0f + fn_1_A240() % 60;
            if (var_r31->unk40.a > 10) {
                var_r31->unk40.a -= 4;
            }
            else {
                var_r31->unk40.a = 0;
                var_r31->unk02 = 2;
            }
        }
        else {
            var_r27++;
        }
    }
    if (var_r27 == particle->unk_30) {
        OSReport("*****************************************************\n");
        OSReport("*****************************************************\n");
        OSReport("*****************************************************\n");
        OSReport("*****************************************************\n");
        OSReport("*****************************************************\n");
        OSReport("*****************************************************\n");
        OSReport("*****************************************************\n");
        OSReport("*****************************************************\n");
        particle->unk_02 = 0;
    }
}

void fn_1_A230(s32 arg0)
{
    lbl_1_bss_B8 = arg0;
}

s32 fn_1_A240(void)
{
    return ((lbl_1_bss_B8 = lbl_1_bss_B8 * 0x41C64E6D + 0x3039) >> 16) % (1 << 15);
}
