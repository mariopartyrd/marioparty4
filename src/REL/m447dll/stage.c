#include "REL/m447dll.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/sprite.h"

#include "ext_math.h"

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ GXColor unk18;
} UnkM447Struct_07; // Size 0x1C

void fn_1_1FF4(void);
void fn_1_2164(UnkM447Struct_06 *arg0);
void fn_1_231C(UnkM447Struct_06 *arg0);
void fn_1_236C(UnkM447Struct_06 *arg0);
void fn_1_2490(UnkM447Struct_06 *arg0);
void fn_1_2494(UnkM447Struct_06 *arg0);
void fn_1_25E4(UnkM447Struct_06 *arg0);
void fn_1_2700(UnkM447Struct_06 *arg0);
void fn_1_2A3C(UnkM447Struct_06 *arg0);
void fn_1_2D08(UnkM447Struct_06 *arg0);
void fn_1_2DAC(ModelData *model, ParticleData *particle, Mtx matrix);

const s32 lbl_1_rodata_138[] = { DATA_MAKE_NUM(DATADIR_M447, 0), DATA_MAKE_NUM(DATADIR_M447, 2), DATA_MAKE_NUM(DATADIR_M447, 3),
    DATA_MAKE_NUM(DATADIR_M447, 1), DATA_MAKE_NUM(DATADIR_M447, 1), DATA_MAKE_NUM(DATADIR_M447, 1), DATA_MAKE_NUM(DATADIR_M447, 1),
    DATA_MAKE_NUM(DATADIR_M447, 1), DATA_MAKE_NUM(DATADIR_M447, 24), DATA_MAKE_NUM(DATADIR_M447, 24), DATA_MAKE_NUM(DATADIR_M447, 24),
    DATA_MAKE_NUM(DATADIR_M447, 24), DATA_MAKE_NUM(DATADIR_M447, 24), DATA_MAKE_NUM(DATADIR_M447, 25), DATA_MAKE_NUM(DATADIR_M447, 26),
    DATA_MAKE_NUM(DATADIR_M447, 28), DATA_MAKE_NUM(DATADIR_M447, 29), DATA_MAKE_NUM(DATADIR_M447, 29), DATA_MAKE_NUM(DATADIR_M447, 29),
    DATA_MAKE_NUM(DATADIR_M447, 29), DATA_MAKE_NUM(DATADIR_M447, 29), 0 };

const Vec lbl_1_rodata_190[]
    = { { 0.0f, 0.1f, 0.0f }, { 400.0f, 0.1f, 0.0f }, { -400.0f, 0.1f, 0.0f }, { 200.0f, 0.1f, -400.0f }, { -200.0f, 0.1f, -400.0f } };

UnkM447Struct_07 lbl_1_data_A0[] = { { { 0.0f, 2500.0f, 0.0f }, { 0.0f, -0.5f, 0.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { 0.0f, -100.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { 400.0f, -100.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { -400.0f, -100.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { 200.0f, -100.0f, -400.0f }, { 0.0f, 1.0f, 0.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { -200.0f, -100.0f, -400.0f }, { 0.0f, 1.0f, 0.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } } };

UnkM447Struct_06 *fn_1_1D90(void)
{
    UnkM447Struct_06 *temp_r3;
    s32 i;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r3), MEMORY_DEFAULT_NUM);
    if (!temp_r3) {
        return NULL;
    }
    temp_r3->unk38 = 0;
    temp_r3->unk50 = NULL;
    temp_r3->unk44 = 0;
    for (i = 0; i < 5; i++) {
        temp_r3->unk54[i] = 0;
        temp_r3->unk68[i] = 0;
    }
    fn_1_2164(temp_r3);
    fn_1_236C(temp_r3);
    temp_r3->unk7C = HuPrcChildCreate(fn_1_1FF4, 0x65, 0x3000, 0, lbl_1_bss_4);
    temp_r3->unk7C->user_data = temp_r3;
    return temp_r3;
}

void fn_1_1E70(UnkM447Struct_06 *arg0)
{
    fn_1_231C(arg0);
    HuPrcKill(arg0->unk7C);
    HuMemDirectFree(arg0);
}

void fn_1_1EB0(UnkM447Struct_06 *arg0, s32 arg1)
{
    arg0->unk38 = arg1;
    arg0->unk3C = 0;
}

BOOL fn_1_1EC0(UnkM447Struct_06 *arg0)
{
    return arg0->unk38 != 0;
}

void fn_1_1ED4(s32 arg0, Vec *arg1)
{
    *arg1 = lbl_1_rodata_190[arg0];
}

void fn_1_1F00(UnkM447Struct_06 *arg0, s32 arg1)
{
    s16 temp_r31;

    temp_r31 = arg0->unk00[arg1 + 3];
    Hu3DModelAttrReset(temp_r31, HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(temp_r31, 0.0f);
    Hu3DMotionStartEndSet(temp_r31, 0.0f, 40.0f);
    arg0->unk54[arg1] = 1;
}

s32 fn_1_1F9C(UnkM447Struct_06 *arg0)
{
    s32 var_r30;
    s32 i;

    var_r30 = 0;
    for (i = 0; i < 5; i++) {
        if (arg0->unk54[i] == 0) {
            var_r30++;
        }
    }
    return var_r30;
}

void fn_1_1FEC(UnkM447Struct_06 *arg0, s32 arg1)
{
    arg0->unk44 = arg1;
}

void (*lbl_1_data_148[])(UnkM447Struct_06 *) = {
    fn_1_2490, fn_1_2494, fn_1_25E4, fn_1_2700, fn_1_2A3C,
    NULL // padding?
};

void fn_1_1FF4(void)
{
    Vec sp8;
    UnkM447Struct_06 *temp_r31;
    s16 temp_r29;
    s32 i;

    temp_r31 = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        if (lbl_1_data_148[temp_r31->unk38]) {
            lbl_1_data_148[temp_r31->unk38](temp_r31);
        }
        for (i = 0; i < 5; i++) {
            temp_r29 = temp_r31->unk00[i + 3];
            if (Hu3DMotionEndCheck(temp_r29)) {
                Hu3DMotionStartEndSet(temp_r29, 20.0f, 40.0f);
                Hu3DModelAttrSet(temp_r29, HU3D_MOTATTR_LOOP);
            }
        }
        if (temp_r31->unk44 > 0) {
            fn_1_351C(&sp8);
            if (--temp_r31->unk44 == 0) {
                sp8.y = 300.0f;
            }
            else {
                sp8.y = fn_1_A240() % 20 - 10 + 300.0f;
            }
            fn_1_3540(&sp8);
        }
        HuPrcVSleep();
    }
}

void fn_1_2164(UnkM447Struct_06 *arg0)
{
    s32 i;

    for (i = 0; i <= 20; i++) {
        arg0->unk00[i] = Hu3DModelCreateFile(lbl_1_rodata_138[i]);
        Hu3DModelLayerSet(arg0->unk00[i], 0);
    }
    arg0->unk50 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M447, 57));
    arg0->unk00[21] = Hu3DParticleCreate(arg0->unk50, 64);
    Hu3DParticleHookSet(arg0->unk00[21], fn_1_2DAC);
    Hu3DParticleBlendModeSet(arg0->unk00[21], 1);
    Hu3DModelLayerSet(arg0->unk00[21], 0);
    Hu3DModelAttrSet(arg0->unk00[21], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowMapSet(arg0->unk00[2]);
    for (i = 0; i < 5; i++) {
        Hu3DModelPosSet(arg0->unk00[i + 3], lbl_1_rodata_190[i].x, lbl_1_rodata_190[i].y, lbl_1_rodata_190[i].z);
        Hu3DModelAttrSet(arg0->unk00[i + 3], HU3D_MOTATTR_PAUSE);
        Hu3DModelShadowMapSet(arg0->unk00[i + 3]);
    }
    for (i = 8; i <= 15; i++) {
        Hu3DModelAttrSet(arg0->unk00[i], HU3D_ATTR_DISPOFF);
    }
    for (i = 16; i <= 20; i++) {
        Hu3DModelAttrSet(arg0->unk00[i], HU3D_ATTR_DISPOFF);
    }
}

void fn_1_231C(UnkM447Struct_06 *arg0)
{
    s32 i;

    for (i = 0; i < 22; i++) {
        Hu3DModelKill(arg0->unk00[i]);
    }
}

void fn_1_236C(UnkM447Struct_06 *arg0)
{
    s32 i;

    Hu3DLighInit();
    for (i = 0; i < 6; i++) {
        arg0->unk2C[i] = Hu3DGLightCreateV(&lbl_1_data_A0[i].unk00, &lbl_1_data_A0[i].unk0C, &lbl_1_data_A0[i].unk18);
        switch (i) {
            case 0:
                Hu3DGLightInfinitytSet(arg0->unk2C[i]);
                Hu3DGLightStaticSet(arg0->unk2C[i], 1);
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                Hu3DGLightStaticSet(arg0->unk2C[i], 1);
                Hu3DGLightSpotSet(arg0->unk2C[i], 20.0f, 2);
                Hu3DGLightColorSet(arg0->unk2C[i], 0, 0, 0, 0);
                break;
        }
    }
}

void fn_1_2490(UnkM447Struct_06 *arg0) { }

void fn_1_2494(UnkM447Struct_06 *arg0)
{
    s32 i;

    switch (arg0->unk3C) {
        case 0:
            arg0->unk3C = 1;
            break;
        case 1:
            Hu3DModelPosSet(arg0->unk00[14], 0.0f, 0.0f, 0.0f);
            Hu3DMotionTimeSet(arg0->unk00[14], 0.0f);
            Hu3DModelAttrReset(arg0->unk00[14], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->unk00[14], HU3D_MOTATTR_LOOP);
            arg0->unk40 = 0;
            arg0->unk3C = 2;
            HuAudFXPlay(0x77E);
            for (i = 0; i < 2; i++) {
                fn_1_7AA4(lbl_1_bss_98[i], 0, 0x3C);
            }
            break;
        case 2:
            if (arg0->unk40++ >= 60) {
                arg0->unk3C = 3;
            }
            break;
        case 3:
            Hu3DModelAttrSet(arg0->unk00[14], HU3D_ATTR_DISPOFF);
            arg0->unk38 = 0;
            arg0->unk3C = 0;
            break;
    }
}

void fn_1_25E4(UnkM447Struct_06 *arg0)
{
    switch (arg0->unk3C) {
        case 0:
            arg0->unk3C = 1;
            break;
        case 1:
            fn_1_2D08(arg0);
            Hu3DModelPosSet(arg0->unk00[15], 0.0f, 0.0f, 0.0f);
            Hu3DMotionTimeSet(arg0->unk00[15], 0.0f);
            Hu3DModelAttrReset(arg0->unk00[15], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->unk00[15], HU3D_MOTATTR_LOOP);
            arg0->unk40 = 0;
            arg0->unk3C = 2;
            HuAudFXPlay(0x782);
            break;
        case 2:
            if (arg0->unk40++ >= 60) {
                arg0->unk3C = 3;
            }
            break;
        case 3:
            Hu3DModelAttrSet(arg0->unk00[15], HU3D_ATTR_DISPOFF);
            arg0->unk38 = 0;
            arg0->unk3C = 0;
            break;
    }
}

void fn_1_2700(UnkM447Struct_06 *arg0)
{
    float temp_f31;
    s16 temp_r29;
    s32 i;

    switch (arg0->unk3C) {
        case 0:
            arg0->unk48 = 0.0f;
            arg0->unk4C = 0.011111111f;
            arg0->unk3C = 1;
            HuAudFXPlay(0x77F);
            break;
        case 1:
            temp_f31 = -90.0f * arg0->unk48;
            for (i = 0; i < 5; i++) {
                Hu3DModelPosSet(arg0->unk00[i + 3], lbl_1_rodata_190[i].x, temp_f31, lbl_1_rodata_190[i].z);
            }
            arg0->unk48 += arg0->unk4C;
            if (arg0->unk48 < 1.0f) {
                break;
            }
            for (i = 0; i < 5; i++) {
                Hu3DMotionTimeSet(arg0->unk00[i + 3], 0.0f);
                Hu3DModelAttrSet(arg0->unk00[i + 3], HU3D_MOTATTR_PAUSE);
                arg0->unk54[i] = 0;
                arg0->unk68[i] = 0;
            }
            arg0->unk3C = 2;
            break;
        case 2:
            for (i = 0; i < 5; i++) {
                temp_r29 = arg0->unk00[i + 8];
                Hu3DModelPosSet(temp_r29, lbl_1_rodata_190[i].x, lbl_1_rodata_190[i].y, lbl_1_rodata_190[i].z);
                Hu3DMotionTimeSet(temp_r29, 0.0f);
                Hu3DModelAttrReset(temp_r29, HU3D_ATTR_DISPOFF);
                Hu3DGLightColorSet(arg0->unk2C[i + 1], lbl_1_data_A0[i + 1].unk18.r, lbl_1_data_A0[i + 1].unk18.g, lbl_1_data_A0[i + 1].unk18.b,
                    lbl_1_data_A0[i + 1].unk18.a);
            }
            arg0->unk40 = 0;
            arg0->unk3C = 3;
            HuAudFXPlay(0x780);
            break;
        case 3:
            if (arg0->unk40++ >= 60) {
                for (i = 0; i < 5; i++) {
                    Hu3DModelAttrSet(arg0->unk00[i + 8], HU3D_ATTR_DISPOFF);
                    Hu3DGLightColorSet(arg0->unk2C[i + 1], 0, 0, 0, 0);
                }
                arg0->unk3C = 4;
            }
            break;
        case 4:
            arg0->unk38 = 0;
            arg0->unk3C = 0;
            break;
    }
}

void fn_1_2A3C(UnkM447Struct_06 *arg0)
{
    float temp_f31;
    s16 temp_r29;
    s32 i;

    switch (arg0->unk3C) {
        case 0:
            arg0->unk48 = 0.0f;
            arg0->unk4C = 0.033333335f;
            arg0->unk3C = 1;
            HuAudFXPlay(0x77F);
            break;
        case 1:
            temp_f31 = 90.0f * arg0->unk48 + -90.0f + 0.1f;
            for (i = 0; i < 5; i++) {
                Hu3DModelPosSet(arg0->unk00[i + 3], lbl_1_rodata_190[i].x, temp_f31, lbl_1_rodata_190[i].z);
            }
            arg0->unk48 += arg0->unk4C;
            if (arg0->unk48 < 1.0f) {
                break;
            }
            for (i = 0; i < 5; i++) {
                Hu3DModelPosSet(arg0->unk00[i + 3], lbl_1_rodata_190[i].x, lbl_1_rodata_190[i].y, lbl_1_rodata_190[i].z);
            }
            HuAudFXPlay(0x783);
            arg0->unk3C = 2;
            break;
        case 2:
            for (i = 0; i < 5; i++) {
                temp_r29 = arg0->unk00[i + 16];
                Hu3DModelPosSet(temp_r29, lbl_1_rodata_190[i].x, lbl_1_rodata_190[i].y, lbl_1_rodata_190[i].z);
                Hu3DMotionTimeSet(temp_r29, 0.0f);
                Hu3DModelAttrReset(temp_r29, HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(temp_r29, HU3D_ATTR_DISPOFF);
            }
            arg0->unk40 = 0;
            arg0->unk3C = 3;
            break;
        case 3:
            if (arg0->unk40++ >= 20) {
                for (i = 0; i < 5; i++) {
                    Hu3DModelAttrSet(arg0->unk00[i + 16], HU3D_ATTR_DISPOFF);
                }
                arg0->unk3C = 4;
                break;
            }
            break;
        case 4:
            arg0->unk38 = 0;
            arg0->unk3C = 0;
            break;
    }
}

void fn_1_2D08(UnkM447Struct_06 *arg0)
{
    ModelData *temp_r30;
    ParticleData *temp_r31;

    temp_r30 = &Hu3DData[arg0->unk00[21]];
    temp_r31 = temp_r30->unk_120;
    temp_r30->attr &= ~1;
    temp_r31->unk_00 = 0;
    temp_r31->unk_02 = 1;
    temp_r31->unk_04.x = 0.0f;
    temp_r31->unk_04.y = 350.0f;
    temp_r31->unk_04.z = -700.0f;
    HuAudFXPlay(0x780);
}

void fn_1_2DAC(ModelData *model, ParticleData *particle, Mtx matrix)
{
    GXColor sp8 = { 0xFF, 0xFF, 0xFF, 0xFF };
    HsfanimStruct01 *var_r31;
    s32 i;

    if (particle->unk_02 == 0) {
        return;
    }
    if (particle->unk_00 == 0) {
        particle->unk_00 = 1;
        particle->unk_04.z = 0.0f;
        particle->unk_10.z = 0.016666668f;
        for (i = 0, var_r31 = particle->unk_48; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk00 = 0;
            var_r31->unk2C = 20.0f;
            var_r31->unk40.r = sp8.r;
            var_r31->unk40.g = sp8.g;
            var_r31->unk40.b = sp8.b;
            var_r31->unk40.a = sp8.a;
            var_r31->unk34.x = particle->unk_04.x;
            var_r31->unk34.y = particle->unk_04.y;
            var_r31->unk34.z = particle->unk_04.z;
            var_r31->unk08.x = -8.0f + 0.1f * (fn_1_A240() % 160);
            var_r31->unk08.y = -8.0f + 0.1f * (fn_1_A240() % 160);
            var_r31->unk08.z = 0.0f;
        }
    }
    for (i = 0, var_r31 = particle->unk_48; i < particle->unk_30; i++, var_r31++) {
        if (var_r31->unk00 < 0) {
            continue;
        }
        var_r31->unk34.x += var_r31->unk08.x;
        var_r31->unk34.y += var_r31->unk08.y;
        var_r31->unk34.z = -700.0 + 500.0 * sind(90.0f * particle->unk_04.z);
        var_r31->unk40.a = 255.0f * (1.0f - particle->unk_04.z);
        var_r31->unk2C = 20.0f + fn_1_A240() % 30;
    }
    particle->unk_04.z += particle->unk_10.z;
    if (particle->unk_04.z >= 1.0f) {
        model->attr |= 1;
        particle->unk_02 = 0;
    }
}
