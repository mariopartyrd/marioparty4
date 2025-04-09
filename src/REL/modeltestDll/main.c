#define HUSPR_USE_OLD_DEFS
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfex.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/modeltestDll.h"

// -------------------------------------------------------------------------- //

s32 lbl_1_data_0[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1B),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x15),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x16),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x06),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x04),
};

omObjData *lbl_1_bss_9A4;
omObjData *lbl_1_bss_9A0;

// -------------------------------------------------------------------------- //

void ObjectSetup(void)
{
    Process *prc;
    OSReport("******* MODELTESTObjectSetup *********\n");

    prc = omInitObjMan(0x32, 0x2000);
    omGameSysInit(prc);

    CRot.x = -30.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    CZoom = 800.0f;

    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 20000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);

    lbl_1_bss_9A4 = omAddObjEx(prc, 0, 0x20, 0x20, -1, fn_1_29C);
    lbl_1_bss_9A0 = omAddObjEx(prc, 0x7FDA, 0, 0, -1, omOutView);

    Hu3DBGColorSet(0x20U, 0x80U, 0x80U);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
}

// -------------------------------------------------------------------------- //

char *lbl_1_data_D8[16] = { "target1A", "target1B", "target2A", "target2B", "target3A", "target3B", "target4A", "target4B", "target5A", "target5B",
    "target6A", "target6B", "target7A", "target7B", "target8A", "target8B" };

HsfanimStruct00 lbl_1_data_118 = {
    /* unk00 */ 40,
    /* unk02 */ { 0, 0 },
    /* unk04 */ 50.0f,
    /* unk08 */ 0.0f,
    /* unk0C */ 90.0f,
    /* unk10 */ { /* x */ 0.0f, /* y */ -0.05000000074505806f, /* z */ 0.0f },
    /* unk1C */ 50.0f,
    /* unk20 */ 0.800000011920929f,
    /* unk24 */ 20.0f,
    /* unk28 */ 0.9900000095367432f,
    /* unk2C */ 4,
    /* unk2E */
    { { /* r */ 255, /* g */ 255, /* b */ 32, /* a */ 255 }, { /* r */ 255, /* g */ 255, /* b */ 0, /* a */ 255 },
        { /* r */ 255, /* g */ 255, /* b */ 128, /* a */ 255 }, { /* r */ 255, /* g */ 255, /* b */ 255, /* a */ 255 } },
    /* unk3E */
    { { /* r */ 255, /* g */ 255, /* b */ 255, /* a */ 0 }, { /* r */ 255, /* g */ 255, /* b */ 255, /* a */ 0 },
        { /* r */ 255, /* g */ 255, /* b */ 255, /* a */ 0 }, { /* r */ 255, /* g */ 255, /* b */ 255, /* a */ 0 } },
};

HsfanimStruct00 lbl_1_data_168[2] = { {
                                          /* unk00 */ 50,
                                          /* unk02 */ { 0, 0 },
                                          /* unk04 */ 5.0f,
                                          /* unk08 */ 10.0f,
                                          /* unk0C */ 10.0f,
                                          /* unk10 */ { /* x */ 0.0f, /* y */ 0.0f, /* z */ 0.0f },
                                          /* unk1C */ 2.0f,
                                          /* unk20 */ 1.0099999904632568f,
                                          /* unk24 */ 30.0f,
                                          /* unk28 */ 0.9900000095367432f,
                                          /* unk2C */ 2,
                                          /* unk2E */
                                          { { /* r */ 48, /* g */ 48, /* b */ 8, /* a */ 255 }, { /* r */ 64, /* g */ 48, /* b */ 8, /* a */ 255 },
                                              { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 }, { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 } },
                                          /* unk3E */
                                          { { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 }, { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 },
                                              { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 }, { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 } },
                                      },
    {
        /* unk00 */ 30,
        /* unk02 */ { 0, 0 },
        /* unk04 */ 3.299999952316284f,
        /* unk08 */ 10.0f,
        /* unk0C */ 0.0f,
        /* unk10 */ { /* x */ 0.0f, /* y */ -0.05000000074505806f, /* z */ 0.0f },
        /* unk1C */ 2.0f,
        /* unk20 */ 1.0f,
        /* unk24 */ 20.0f,
        /* unk28 */ 0.9800000190734863f,
        /* unk2C */ 2,
        /* unk2E */
        { { /* r */ 255, /* g */ 255, /* b */ 255, /* a */ 255 }, { /* r */ 255, /* g */ 255, /* b */ 64, /* a */ 255 },
            { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 }, { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 } },
        /* unk3E */
        { { /* r */ 255, /* g */ 128, /* b */ 128, /* a */ 0 }, { /* r */ 255, /* g */ 64, /* b */ 32, /* a */ 0 },
            { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 }, { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 } },
    } };

HsfanimStruct00 lbl_1_data_208 = {
    /* unk00 */ 40,
    /* unk02 */ { 0, 0 },
    /* unk04 */ 50.0f,
    /* unk08 */ 0.0f,
    /* unk0C */ 180.0f,
    /* unk10 */ { /* x */ 0.0f, /* y */ 0.0f, /* z */ 0.0f },
    /* unk1C */ 30.0f,
    /* unk20 */ 0.8999999761581421f,
    /* unk24 */ 20.0f,
    /* unk28 */ 0.9900000095367432f,
    /* unk2C */ 4,
    /* unk2E */
    { { /* r */ 255, /* g */ 255, /* b */ 32, /* a */ 255 }, { /* r */ 255, /* g */ 255, /* b */ 0, /* a */ 255 },
        { /* r */ 255, /* g */ 255, /* b */ 128, /* a */ 255 }, { /* r */ 255, /* g */ 255, /* b */ 255, /* a */ 255 } },
    /* unk3E */
    { { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 }, { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 }, { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 },
        { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 } },
};

HsfanimStruct00 lbl_1_data_258 = {
    /* unk00 */ 30,
    /* unk02 */ { 0, 0 },
    /* unk04 */ 50.0f,
    /* unk08 */ 0.0f,
    /* unk0C */ 90.0f,
    /* unk10 */ { /* x */ 0.0f, /* y */ 0.0f, /* z */ 0.0f },
    /* unk1C */ 30.0f,
    /* unk20 */ 0.949999988079071f,
    /* unk24 */ 20.0f,
    /* unk28 */ 0.9900000095367432f,
    /* unk2C */ 2,
    /* unk2E */
    { { /* r */ 255, /* g */ 16, /* b */ 16, /* a */ 255 }, { /* r */ 255, /* g */ 255, /* b */ 16, /* a */ 255 },
        { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 }, { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 } },
    /* unk3E */
    { { /* r */ 255, /* g */ 16, /* b */ 16, /* a */ 255 }, { /* r */ 255, /* g */ 255, /* b */ 16, /* a */ 255 },
        { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 }, { /* r */ 0, /* g */ 0, /* b */ 0, /* a */ 0 } },
};

const Vec lbl_1_rodata_38 = { 0.0f, 0.0f, 0.0f };
const Vec lbl_1_rodata_44 = { 0.0f, 1.0f, 0.0f };
s16 lbl_1_bss_99C;
s16 lbl_1_bss_99A;
s16 lbl_1_bss_98A[8];
s16 lbl_1_bss_88A[8][16];
s16 lbl_1_bss_888;
s16 unk_bss_886;
s16 lbl_1_bss_884;
s16 lbl_1_bss_864[16];
s16 lbl_1_bss_664[256];
s16 lbl_1_bss_460[258];
s16 lbl_1_bss_45A[3];
s16 lbl_1_bss_458;
AnimData *lbl_1_bss_454;
s32 unk_bss_450;
HuObjUnk lbl_1_bss_40[20];
void *lbl_1_bss_30[4];
u8 lbl_1_bss_2C;
f32 lbl_1_bss_28;
s16 lbl_1_bss_24;
f32 lbl_1_bss_20;
Process *lbl_1_bss_18[2];
Process *lbl_1_bss_14;
Process *lbl_1_bss_10;
s32 lbl_1_bss_C;
f32 lbl_1_bss_8;
static u8 unk_bss[8];

// -------------------------------------------------------------------------- //

void fn_1_29C(omObjData *arg0)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Mtx sp2C;
    s16 var_r31;
    s16 temp_r27;
    u32 temp_r26;
    s16 temp_r3;
    void *temp_r29;
    AnimData *temp_r28;
    f32 temp_r5;
    f32 temp_f30;
    s16 chrIdx;
    s32 temp_r0;

    sp14 = lbl_1_rodata_38;
    sp8 = lbl_1_rodata_44;

    var_r31 = Hu3DGLightCreate(0.0f, 500.0f, 1000.0f, 0.0f, -0.5f, -1.0f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DGLightInfinitytSet(var_r31);
    Hu3DShadowCreate(45.0f, 500.0f, 8000.0f);
    Hu3DShadowTPLvlSet(0.5f);

    Hu3DShadowSizeSet(0xC0U);
    sp20.x = -500.0f;
    sp20.y = 1000.0f;
    sp20.z = 1000.0f;
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);

    for (var_r31 = 0; var_r31 < 1; ++var_r31) {
        chrIdx = 0;
        lbl_1_bss_98A[var_r31] = CharModelCreate(chrIdx, 2);
        if (var_r31 == 1) {
            Hu3DModelLayerSet(lbl_1_bss_98A[var_r31], 1);
        }

        lbl_1_bss_88A[var_r31][0] = CharModelMotionCreate(chrIdx, lbl_1_data_0[0]);
        lbl_1_bss_88A[var_r31][1] = CharModelMotionCreate(chrIdx, lbl_1_data_0[1]);
        lbl_1_bss_88A[var_r31][2] = CharModelMotionCreate(chrIdx, lbl_1_data_0[2]);
        lbl_1_bss_88A[var_r31][3] = CharModelMotionCreate(chrIdx, lbl_1_data_0[3]);
        lbl_1_bss_88A[var_r31][4] = CharModelMotionCreate(chrIdx, lbl_1_data_0[4]);
        lbl_1_bss_88A[var_r31][5] = CharModelMotionCreate(chrIdx, lbl_1_data_0[5]);
        lbl_1_bss_88A[var_r31][6] = CharModelMotionCreate(chrIdx, lbl_1_data_0[6]);
        lbl_1_bss_88A[var_r31][7] = CharModelMotionCreate(chrIdx, lbl_1_data_0[7]);
        lbl_1_bss_88A[var_r31][0] = CharModelMotionCreate(chrIdx, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x4D));
        CharModelMotionSet(chrIdx, lbl_1_bss_88A[var_r31][0]);
        Hu3DModelAttrSet(lbl_1_bss_98A[var_r31], HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(lbl_1_bss_98A[var_r31], (var_r31 / 4 * 0xC8) - 100, 0.0f, -(var_r31 % 4) * 0x96);
        CharModelMotionDataClose(chrIdx);
    }
    temp_r26 = OSGetTick();

    for (var_r31 = 0; var_r31 < 8; ++var_r31) {
        Hu3DModelObjMtxGet(lbl_1_bss_98A[0], "test11_tex_we-ske_R_shoe1", sp2C);
    }

    temp_r5 = OSTicksToMicroseconds(OSGetTick() - temp_r26);
    OSReport("time %f\n", US_TO_60TH_SEC(temp_r5));
    var_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_SAF, 0x24));
    Hu3DModelScaleSet(var_r31, 5.0f, 5.0f, 5.0f);
    Hu3DModelShadowMapSet(var_r31);
    var_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M407, 0x1E));
    temp_r27 = Hu3DJointMotion(var_r31, HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M407, 0x2F), MEMORY_DEFAULT_NUM, 2));
    Hu3DMotionSet(var_r31, temp_r27);
    Hu3DModelAttrSet(var_r31, HU3D_MOTATTR_LOOP);

    for (var_r31 = 0; var_r31 < 10; ++var_r31) {
        if (var_r31 == 0) {
            lbl_1_bss_664[var_r31] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_SAF, 0x19));
        }
        else {
            lbl_1_bss_664[var_r31] = Hu3DModelLink(lbl_1_bss_664[0]);
        }
        Hu3DModelShadowSet(lbl_1_bss_664[var_r31]);
        Hu3DModelPosSet(lbl_1_bss_664[var_r31], (((var_r31 / 5) * 0x1F4) + 0xC8), 0.0f, (-(var_r31 % 5) * 0x12C));
        Hu3DModelAttrSet(lbl_1_bss_664[var_r31], HU3D_ATTR_NOCULL);
        Hu3DModelAttrSet(lbl_1_bss_664[var_r31], HU3D_MOTATTR_LOOP);
    }
    temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_SAF, 0x13), MEMORY_DEFAULT_NUM, 2);
    temp_r28 = HuSprAnimRead(temp_r29);
    lbl_1_bss_99C = HuSprGrpCreate(0x14);

    for (var_r31 = 0; var_r31 < 0x14; ++var_r31) {
        lbl_1_bss_99A = HuSprCreate(temp_r28, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_99C, var_r31, lbl_1_bss_99A);
        HuSprPosSet(lbl_1_bss_99C, var_r31, 640.0f, 240.0f);
    }

    HuSprExecLayerSet(0x40, 1);
    HuSprGrpDrawNoSet(lbl_1_bss_99C, 0x40);
    lbl_1_bss_458 = 0x293;
    lbl_1_bss_45A[0] = MGSeqTimerCreate(lbl_1_bss_458 / 60);
    temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 0x01), MEMORY_DEFAULT_NUM, 2);
    temp_r28 = HuSprAnimRead(temp_r29);
    lbl_1_bss_888 = Hu3DParManCreate(temp_r28, 0x3E8, &lbl_1_data_208);
    Hu3DParManAttrSet(lbl_1_bss_888, 0x45);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(lbl_1_bss_888), 1U);
    Hu3DParManRotSet(lbl_1_bss_888, 0.0f, 0.0f, 0.0f);
    Hu3DParManVacumeSet(lbl_1_bss_888, 500.0f, 0.0f, 0.0f, 1.0f);
    lbl_1_bss_884 = Hu3DParManLink(lbl_1_bss_888, &lbl_1_data_258);
    Hu3DParManAttrSet(lbl_1_bss_884, 0x143);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(lbl_1_bss_884), 1U);
    Hu3DParManVecSet(lbl_1_bss_884, 0.0f, 1.0f, 0.0f);
    Hu3DParManVacumeSet(lbl_1_bss_884, 500.0f, 0.0f, 0.0f, 1.0f);
    Hu3DParManColorSet(lbl_1_bss_884, 0);
    temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 0x02), MEMORY_DEFAULT_NUM, 2);
    temp_r28 = HuSprAnimRead(temp_r29);

    for (var_r31 = 0; var_r31 < 10; ++var_r31) {
        lbl_1_bss_864[var_r31] = Hu3DParManCreate(temp_r28, 0x1F4, &lbl_1_data_168[0]);
        Hu3DParManAttrSet(lbl_1_bss_864[var_r31], 0x864);
        Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(lbl_1_bss_864[var_r31]), 1U);
        Hu3DParManPosSet(lbl_1_bss_864[var_r31], (100.0 * sind(36.0f * var_r31)), 0.0f, 100.0 * cosd(36.0f * var_r31));
        Hu3DParManRotSet(lbl_1_bss_864[var_r31], -90.0f, 0.0f, 0.0f);
    }

    lbl_1_bss_C = 0;
    Hu3DFogSet(5000.0f, 10000.0f, 0x20U, 0x10U, 0x30U);
    arg0->func = fn_1_F9C;
}

// -------------------------------------------------------------------------- //

s32 unrefData[] = { 0, 0, 0 };

// -------------------------------------------------------------------------- //

void fn_1_F38(void)
{
    f32 var_f31;
    var_f31 = 0.0f;

    while (TRUE) {
        Hu3DModelRotSet(lbl_1_bss_460[0], 0.0f, var_f31, 0.0f);
        var_f31 += 1.0f;
        HuPrcVSleep();
    }
}

// -------------------------------------------------------------------------- //

static inline void HuControlCamCenter(Vec *sp18, Vec *sp30)
{
    s8 temp_r28;

    temp_r28 = HuPadSubStkX[0] & 0xF8;
    if (temp_r28 != 0) {
        Center.x += 0.05f * (sp30->x * temp_r28);
        Center.y += 0.05f * (sp30->y * temp_r28);
        Center.z += 0.05f * (sp30->z * temp_r28);
    }
    VECNormalize(sp18, sp30);
    temp_r28 = -(HuPadSubStkY[0] & 0xF8);
    if (temp_r28 != 0) {
        Center.x += 0.05f * (sp30->x * temp_r28);
        Center.y += 0.05f * (sp30->y * temp_r28);
        Center.z += 0.05f * (sp30->z * temp_r28);
    }
}

// -------------------------------------------------------------------------- //

const HuUnkF9C2 lbl_1_rodata_B8 = { { 8, 6, 4, 7, 9, 10, 11 } };

// -------------------------------------------------------------------------- //

void fn_1_F9C(struct om_obj_data *omData)
{
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    f32 temp_f31;
    s32 var_r31;
    s16 var_r30;
    HuUnkF9C2 teropPatterns;

    if (omSysExitReq != 0) {
        if (lbl_1_bss_10 != 0) {
            HuPrcKill(lbl_1_bss_10);
        }
        if (lbl_1_bss_14 != 0) {
            HuPrcKill(lbl_1_bss_14);
        }
        if (lbl_1_bss_18[0] != 0) {
            HuPrcKill(lbl_1_bss_18[0]);
        }
        CharModelKill(-1);
        omOvlReturnEx(1, 1);
        return;
    }

    CRot.y += 0.1f * HuPadStkX[0];
    CRot.x += 0.1f * HuPadStkY[0];
    CZoom += HuPadTrigL[0] / 2;
    CZoom -= HuPadTrigR[0] / 2;

    if (((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0) && (lbl_1_data_118.unk0C < 360.0f)) {
        lbl_1_data_118.unk0C += 1.0f;
    }

    if (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) && (lbl_1_data_118.unk0C > 0.0f)) {
        lbl_1_data_118.unk0C -= 1.0f;
    }

    if ((HuPadBtnDown[0] & PAD_BUTTON_X) != 0) {
        Hu3DParManAttrSet(lbl_1_bss_888, 0x81);
        Hu3DParManAttrSet(lbl_1_bss_884, 0x81);
    }

    lbl_1_bss_20 += 2.0f;
    if (lbl_1_bss_20 > 360.0f) {
        lbl_1_bss_20 -= 360.0f;
    }

    for (var_r30 = 0; var_r30 < 10; ++var_r30) {
        f32 temp_f30;
        s32 var_r29;
        s32 var_fake;

        while (0) {
            (void)temp_f30;
            (void)temp_f30;
            (void)var_r31;
            (void)var_r31;
            (void)var_r31;
            (void)var_r31;
            (void)var_r31;
            (void)var_r31;
            (void)var_r31;
            (void)var_r31;
            (void)var_r31;
            (void)var_r31;
            (void)var_r30;
            (void)var_r30;
            (void)var_r30;
            (void)var_r29;
            (void)var_r29;
            (void)var_r29;
            (void)var_r29;
            (void)var_r29;
            (void)var_r29;
            (void)var_r29;
            (void)var_r29;
            (void)var_r29;
            (void)var_r29;
            (void)var_fake;
            (void)var_fake;
            (void)var_fake;
            (void)var_fake;
            (void)var_fake;
            (void)var_fake;
            (void)var_fake;
            (void)var_fake;
            (void)var_fake;
        }
    }

    if (lbl_1_bss_458 > 0) {
        MGSeqParamSet(lbl_1_bss_45A[0], 1, lbl_1_bss_458 / 60);
        --lbl_1_bss_458;
        if (lbl_1_bss_458 <= 0) {
            MGSeqParamSet(lbl_1_bss_45A[0], 2, -1);
        }
    }

    sp3C.x = Center.x + CZoom * (sind(CRot.y) * cosd(CRot.x));
    sp3C.y = Center.y + CZoom * -sind(CRot.x);
    sp3C.z = Center.z + CZoom * (cosd(CRot.y) * cosd(CRot.x));
    sp30.x = Center.x - sp3C.x;
    sp30.y = Center.y - sp3C.y;
    sp30.z = Center.z - sp3C.z;
    sp24.x = sind(CRot.y) * sind(CRot.x);
    sp24.y = cosd(CRot.x);
    sp24.z = cosd(CRot.y) * sind(CRot.x);
    temp_f31 = CRot.z;

    sp18.x = sp24.x * (sp30.x * sp30.x + (1.0f - sp30.x * sp30.x) * cosd(temp_f31))
        + sp24.y * (sp30.x * sp30.y * (1.0f - cosd(temp_f31)) - sp30.z * sind(temp_f31))
        + sp24.z * (sp30.x * sp30.z * (1.0f - cosd(temp_f31)) + sp30.y * sind(temp_f31));

    sp18.y = sp24.y * (sp30.y * sp30.y + (1.0f - sp30.y * sp30.y) * cosd(temp_f31))
        + sp24.x * (sp30.x * sp30.y * (1.0f - cosd(temp_f31)) + sp30.z * sind(temp_f31))
        + sp24.z * (sp30.y * sp30.z * (1.0f - cosd(temp_f31)) - sp30.x * sind(temp_f31));

    sp18.z = sp24.z * (sp30.z * sp30.z + (1.0f - sp30.z * sp30.z) * cosd(temp_f31))
        + (sp24.x * (sp30.x * sp30.z * (1.0 - cosd(temp_f31)) - sp30.y * sind(temp_f31))
            + sp24.y * (sp30.y * sp30.z * (1.0 - cosd(temp_f31)) + sp30.x * sind(temp_f31)));

    VECCrossProduct(&sp24, &sp30, &sp30);
    VECNormalize(&sp30, &sp30);

    if (lbl_1_bss_C == 0) {
        HuControlCamCenter(&sp18, &sp30);
    }

    teropPatterns = lbl_1_rodata_B8;

    if ((HuPadBtnDown[0] & PAD_BUTTON_X) != 0) {
        ++lbl_1_bss_24;
        if (lbl_1_bss_24 >= 7) {
            lbl_1_bss_24 = 0;
        }
    }

    if ((HuPadBtnDown[0] & PAD_BUTTON_B) != 0) {
        var_r30 = MGSeqStartCreateType(teropPatterns.unk0[lbl_1_bss_24]);
    }
    if ((HuPadBtnDown[0] & PAD_BUTTON_A) != 0) {
        var_r30 = MGSeqDrawCreateType(teropPatterns.unk0[lbl_1_bss_24]);
    }
    if ((HuPadBtnDown[0] & PAD_BUTTON_Y) != 0) {
        var_r30 = MGSeqRecordCreate(59);
    }

    if ((HuPadBtnDown[0] & (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT | PAD_BUTTON_UP | PAD_BUTTON_DOWN)) != 0) {
        if ((HuPadBtnDown[0] & PAD_BUTTON_UP) != 0) {
            MGSeqChampionCreate(GWPlayerCfg[0].character, -1, -1, -1);
        }
        if ((HuPadBtnDown[0] & PAD_BUTTON_LEFT) != 0) {
            MGSeqChampionCreate(GWPlayerCfg[0].character, GWPlayerCfg[1].character, -1, -1);
        }
        if ((HuPadBtnDown[0] & PAD_BUTTON_DOWN) != 0) {
            MGSeqChampionCreate(GWPlayerCfg[0].character, GWPlayerCfg[1].character, GWPlayerCfg[2].character, -1);
        }
        if ((HuPadBtnDown[0] & PAD_BUTTON_RIGHT) != 0) {
            MGSeqChampionCreate(GWPlayerCfg[0].character, GWPlayerCfg[1].character, GWPlayerCfg[2].character, GWPlayerCfg[3].character);
        }
    }
    fontcolor = 5;
    print8(0x10, 0x190, 1.5f, "Terop Pattern%d", lbl_1_bss_24 + 1);
    lbl_1_bss_8 += 5.0f;
    if (lbl_1_bss_8 > 360.0f) {
        lbl_1_bss_8 -= 360.0f;
    }
}

// -------------------------------------------------------------------------- //

void fn_1_20F4(void)
{
    s16 temp_r3;
    s16 var_r29;
    HsfObject *temp_r3_2;
    HuObjUnk *temp_r31;
    Mtx spC0;
    Vec sp24;
    Mtx sp90;
    Mtx sp60;
    Mtx sp30;
    Vec sp18;
    Vec spC;
    f32 temp_f27;
    f32 var_f29; // ! - uninitialized
    s16 var_r27; // ! - uninitialized
    s32 var_r26;
    f32 temp_f30;

    temp_r3 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_PEACHMDL1, 0x00));
    Hu3DModelPosSet(temp_r3, 0.0f, 0.0f, 100.0f);

    for (var_r29 = 0; var_r29 < 16; ++var_r29) {
        OSReport("%s\n", lbl_1_data_D8[var_r29]);
        temp_r3_2 = Hu3DModelObjPtrGet(temp_r3, lbl_1_data_D8[var_r29]);
        lbl_1_bss_40[var_r29].obj = temp_r3_2;

        Hu3DMotionNoMotSet(temp_r3, lbl_1_data_D8[var_r29], 0x380);

        lbl_1_bss_40[var_r29].pos.x = temp_r3_2->data.base.pos.x;
        lbl_1_bss_40[var_r29].pos.y = temp_r3_2->data.base.pos.y;
        lbl_1_bss_40[var_r29].pos.z = temp_r3_2->data.base.pos.z;
        lbl_1_bss_40[var_r29].rot.x = temp_r3_2->data.base.rot.x;
        lbl_1_bss_40[var_r29].rot.y = temp_r3_2->data.base.rot.y;
        lbl_1_bss_40[var_r29].rot.z = temp_r3_2->data.base.rot.z;
        lbl_1_bss_40[var_r29].scale.x = temp_r3_2->data.base.scale.x;
        lbl_1_bss_40[var_r29].scale.y = temp_r3_2->data.base.scale.y;
        lbl_1_bss_40[var_r29].scale.z = temp_r3_2->data.base.scale.z;

        OSReport("%d:(%3.2f,%3.2f,%3.2f),(%3.2f,%3.2f,%3.2f)\n", var_r29, temp_r3_2->data.base.pos.x, temp_r3_2->data.base.pos.y,
            temp_r3_2->data.base.pos.z, temp_r3_2->data.base.rot.x, temp_r3_2->data.base.rot.y, temp_r3_2->data.base.rot.z);
    }
    while (TRUE) {
        Hu3DModelObjMtxGet(temp_r3, "ske_skirt", sp30);

        for (var_r29 = 0; var_r29 < 8; ++var_r29) {
            temp_r31 = &lbl_1_bss_40[var_r29 * 2];
            temp_r31->obj->data.curr.rot.x = temp_r31->rot.x;
            temp_r31->obj->data.curr.rot.y = temp_r31->rot.y;
            temp_r31->obj->data.curr.rot.z = temp_r31->rot.z;

            Hu3DModelObjMtxGet(temp_r3, lbl_1_data_D8[var_r29 * 2], sp90);

            temp_r31 = &lbl_1_bss_40[(var_r29 * 2) + 1];
            temp_r31->obj->data.curr.rot.x = temp_r31->rot.x;
            temp_r31->obj->data.curr.rot.y = temp_r31->rot.y;
            temp_r31->obj->data.curr.rot.z = temp_r31->rot.z;

            Hu3DModelObjMtxGet(temp_r3, lbl_1_data_D8[(var_r29 * 2) + 1], spC0);
            Hu3DMtxTransGet(spC0, &sp18);
            MTXInverse(sp30, sp60);
            Hu3DModelObjMtxGet(temp_r3, lbl_1_data_D8[(var_r29 * 2) + 1], spC0);
            Hu3DMtxTransGet(spC0, &sp18);
            MTXMultVec(sp60, &sp18, &sp18);

            temp_f27 = atan2d(sp18.z, sp18.x);
            temp_r31 = &lbl_1_bss_40[var_r29 * 2];
            temp_r31->obj->data.curr.rot.x = temp_r31->rot.x + (var_f29 * (2.0 * (sind(temp_f27) * sind(var_r27))));
            temp_r31->obj->data.curr.rot.y = temp_r31->rot.y;
            temp_r31->obj->data.curr.rot.z = temp_r31->rot.z + (var_f29 * cosd(var_r27));

            Hu3DModelObjMtxGet(temp_r3, lbl_1_data_D8[(var_r29 * 2) + 1], spC0);
            Hu3DMtxTransGet(spC0, &sp24);
            fn_1_28F8(&sp24, &spC);
            HuSprPosSet(lbl_1_bss_99C, var_r29, spC.x, spC.y);
        }

        var_r27 += 5;
        if (var_r27 > 0x168) {
            var_r27 -= 0x168;
        }

        if (HuPadSubStkX[1] < 0) {
            var_r26 = -HuPadSubStkX[1];
        }
        else {
            var_r26 = HuPadSubStkX[1];
        }

        if (var_r26 < 0xA && ABS(HuPadSubStkY[1]) < 0xA) {
            var_r27 = 0x168;
            var_f29 = 0.0f;
        }
        else {
            var_r27 = atan2d(HuPadSubStkX[1], HuPadSubStkY[1]);
            temp_f30 = (HuPadSubStkX[1] * HuPadSubStkX[1]) + (HuPadSubStkY[1] * HuPadSubStkY[1]);
            var_f29 = sqrtf(temp_f30);
            if (var_f29 > 80.0f) {
                var_f29 = 80.0f;
            }
        }

        HuPrcVSleep();
    }
}

// -------------------------------------------------------------------------- //

void fn_1_28F8(Vec *arg0, Vec *arg1)
{
    Vec spC;
    Mtx sp18;
    CameraData *cam;
    f32 temp_f31;
    f32 temp_f30;

    cam = &Hu3DCamera[0];
    C_MTXLookAt(sp18, &cam->pos, &cam->up, &cam->target);
    MTXMultVec(sp18, arg0, &spC);

    temp_f31 = (1.2f * (spC.z * (sind(cam->fov / 2) / (cosd(cam->fov / 2)))));
    temp_f30 = (spC.z * (sind(cam->fov / 2) / (cosd(cam->fov / 2))));
    arg1->x = 288.0f + (spC.x * (288.0f / -temp_f31));
    arg1->y = 240.0f + (spC.y * (240.0f / temp_f30));
}

void fn_1_2AFC(void)
{
    s16 temp_r3;

    HuWinInit(1);
    temp_r3 = HuWinCreate(-10000.0f, -10000.0f, 480, 0x80, 0);
    HuWinMesSpeedSet(temp_r3, 3);

    while (TRUE) {
        HuWinMesSet(temp_r3, MAKE_MESSID(0x20, 0x11));
        HuWinMesWait(temp_r3);
    }
}

// -------------------------------------------------------------------------- //

// unreferenced data
u8 lbl_1_data_322[54] = {
    255,
    255,
    255,
    255,
    0,
    0,
    60,
    68,
    155,
    166,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    60,
    68,
    155,
    166,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    63,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    63,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

// -------------------------------------------------------------------------- //

void fn_1_2B68(ModelData *mdl, Mtx arg1)
{
    GXColor sp17;
    Mtx sp150;
    Mtx sp120;
    Mtx spF0;
    Mtx spC0;
    Mtx sp90;
    GXTexObj sp30;
    f32 sp18[2][3];
    Mtx44 sp50;
    AnimBmpData *sp10;
    f32 temp_f31;
    f32 var_f30; // ! - uninitialized
    f32 var_f29; // ! - uninitialized
    f32 var_f28; // ! - uninitialized
    f32 var_f27; // ! - uninitialized

    if (!lbl_1_bss_30[0]) {
        lbl_1_bss_30[0] = HuMemDirectMallocNum(HEAP_SYSTEM, FB_SIZE(640, 480), MEMORY_DEFAULT_NUM);
    }

    GXSetTexCopySrc(0, 0, 640, 480);
    GXSetTexCopyDst(640, 480, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(lbl_1_bss_30[0], GX_FALSE);
    DCFlushRangeNoSync(lbl_1_bss_30[0], FB_SIZE(640, 480));
    C_MTXOrtho(sp50, 0.0f, 480.0f, 0.0f, 576.0f, 0.0f, 10.0f);
    GXSetProjection(sp50, GX_ORTHOGRAPHIC);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 640, 480);
    GXInvalidateTexAll();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);

    sp17.r = sp17.g = sp17.b = sp17.a = 255;
    GXSetChanMatColor(GX_COLOR0A0, sp17);

    sp17.r = sp17.g = sp17.b = 128;
    sp17.a = 255;
    GXSetChanAmbColor(GX_COLOR0A0, sp17);

    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1U);
    GXSetChanCtrl(GX_COLOR0, 1U, GX_SRC_REG, GX_SRC_VTX, 1U, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_GEQUAL, 1U, GX_AOP_AND, GX_GEQUAL, 1U);
    GXSetZCompLoc(0U);
    MTXIdentity(arg1);
    GXLoadPosMtxImm(arg1, 0U);

    MTXInvXpose(arg1, sp90);
    GXLoadNrmMtxImm(sp90, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);

    sp10 = lbl_1_bss_454->bmp;
    lbl_1_bss_2C += 1;
    HuSprTexLoad(lbl_1_bss_454, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);

    PPCSync();
    GXInitTexObj(&sp30, lbl_1_bss_30[0], 0x280U, 0x1E0U, 4U, GX_CLAMP, GX_CLAMP, 0U);
    GXInitTexObjLOD(&sp30, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0U, 0U, GX_ANISO_1);
    GXLoadTexObj(&sp30, GX_TEXMAP0);
    GXSetNumIndStages(1U);

    MTXScale(sp150, 0.1f, 0.1f, 0.0f);
    sp18[0][0] = sp150[0][0];
    sp18[0][1] = sp150[0][1];
    sp18[0][2] = 0.0f;
    sp18[1][0] = sp150[1][0];
    sp18[1][1] = sp150[1][1];
    sp18[1][2] = 0.0f;

    MTXRotRad(spF0, 0x58, -1.5707964f);
    mtxRot(spF0, 0.0f, 0.0f, 0.0f);
    temp_f31 = 0.0015625f;
    MTXScale(sp120, temp_f31, temp_f31, temp_f31);
    MTXConcat(sp120, spF0, sp150);
    MTXTrans(spC0, 0.5f, 0.0f, 0.5f);
    GXLoadTexMtxImm(sp150, 0x1EU, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_POS, 0x1EU, 0U, 0x7DU);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_4, GX_ITS_4);
    GXSetIndTexMtx(GX_ITM_0, sp18, 0);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, 1, 0, GX_ITM_0);

    lbl_1_bss_28 += 5.0f;
    if (lbl_1_bss_28 > 360.0f) {
        lbl_1_bss_28 -= 360.0f;
    }

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXNormal3f32(0.0f, var_f30 / 640.0f, var_f29 / 480.0f);

    GXPosition3f32(640.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXNormal3f32(0.0f, var_f28 / 640.0f, var_f29 / 480.0f);

    GXPosition3f32(640.0f, 480.0f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXNormal3f32(0.0f, var_f28 / 640.0f, var_f27 / 480.0f);

    GXPosition3f32(0.0f, 480.0f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXNormal3f32(0.0f, var_f30 / 640.0f, var_f27 / 480.0f);

    GXEnd();
    GXSetNumIndStages(0U);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
#ifdef TARGET_PC
    GXDestroyTexObj(&sp30);
#endif
}

// -------------------------------------------------------------------------- //
