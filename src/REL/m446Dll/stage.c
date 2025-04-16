#include "REL/m446Dll.h"

#include "game/hsfman.h"
#include "game/hsfmotion.h"

// bss
unkStruct3 *lbl_1_bss_A0;

// data
s32 lbl_1_data_410[5] = { 0x4D0008, 0x4D0007, 0x4D0006, 0x4D001F, 0x4D001F };
Vec lbl_1_data_424[5] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.1f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 160.0f, 160.0f, 0.0f },
    { -160.0f, 160.0f, 0.0f },
};
unkStruct10 lbl_1_data_460[3] = { { { 160.0f, 160.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { -160.0f, 160.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { 0.0f, 160.0f, 500.0f }, { 0.0f, 0.0f, 0.0f }, { 0xB0, 0xB0, 0xB0, 0xFF } } };
Vec lbl_1_data_4B4[3] = {
    { 1.0f, 3000.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};

s32 fn_1_7BF0(void)
{
    lbl_1_bss_A0 = 0;
    return 1;
}

void fn_1_7C08(void)
{
    unkStruct3 *var_r31;
    unkStruct9 *var_r30;

    var_r31 = lbl_1_bss_A0;
    if (var_r31) {
        do {
            var_r30 = var_r31->unk0;
            fn_1_2688((unkStruct4 *)var_r30); // ???
            var_r31 = var_r31->unk8;
        } while (var_r31);
    }
}

void fn_1_7C60(void)
{
    s32 var_r30;
    unkStruct3 *var_r29;
    unkStruct9 *temp_r31;

    var_r29 = lbl_1_bss_A0;
    if (var_r29) {
        do {
            temp_r31 = var_r29->unk0;
            if ((temp_r31->unk28 != 0) && (temp_r31->unk14 < 1.0f)) {
                if ((temp_r31->unk14 += 0.002f) > 1.0f) {
                    temp_r31->unk14 = 1.0f;
                }
                Hu3DGLightColorSet(temp_r31->unkA[2], lbl_1_data_460[2].unk18.r * temp_r31->unk14, lbl_1_data_460[2].unk18.g * temp_r31->unk14,
                    lbl_1_data_460[2].unk18.b * temp_r31->unk14, lbl_1_data_460[2].unk18.a * temp_r31->unk14);
            }
            if (temp_r31->unk24 != 0) {
                for (var_r30 = 0; var_r30 <= 1; var_r30++) {
                    if (temp_r31->unk10 < 1.0f) {
                        if ((temp_r31->unk10 += 0.002f) > 1.0f) {
                            temp_r31->unk10 = 1.0f;
                        }
                        Hu3DGLightColorSet(temp_r31->unkA[var_r30], temp_r31->unk10 * lbl_1_data_460[var_r30].unk18.r,
                            temp_r31->unk10 * lbl_1_data_460[var_r30].unk18.g, temp_r31->unk10 * lbl_1_data_460[var_r30].unk18.b,
                            temp_r31->unk10 * lbl_1_data_460[var_r30].unk18.a);
                    }
                }
                if ((temp_r31->unk18 == 0) && (Hu3DMotionEndCheck(temp_r31->unk0[2]) != 0)) {
                    Hu3DMotionStartEndSet(temp_r31->unk0[2], 180.0f, 359.0f);
                    Hu3DModelAttrSet(temp_r31->unk0[2], HU3D_MOTATTR_LOOP);
                    temp_r31->unk18 = 1;
                }
                if ((temp_r31->unk1C == 0) && (Hu3DMotionEndCheck(temp_r31->unk0[3]) != 0)) {
                    Hu3DMotionStartEndSet(temp_r31->unk0[3], 120.0f, 159.0f);
                    Hu3DModelAttrSet(temp_r31->unk0[3], HU3D_MOTATTR_LOOP);
                    temp_r31->unk1C = 1;
                }
                if ((temp_r31->unk20 == 0) && (Hu3DMotionEndCheck(temp_r31->unk0[4]) != 0)) {
                    Hu3DMotionStartEndSet(temp_r31->unk0[4], 120.0f, 159.0f);
                    Hu3DModelAttrSet(temp_r31->unk0[4], HU3D_MOTATTR_LOOP);
                    temp_r31->unk20 = 1;
                }
            }
            var_r29 = var_r29->unk8;
        } while (var_r29);
    }
}

unkStruct9 *m446StageCreate(void)
{
    s32 var_r30;
    unkStruct3 *var_r29;
    unkStruct3 *temp_ret;
    unkStruct9 *var_r31;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkStruct9), MEMORY_DEFAULT_NUM);
    if (!var_r31) {
        return NULL;
    }
    var_r31->unk10 = 0.0f;
    var_r31->unk14 = 0.0f;
    var_r31->unk18 = 0;
    var_r31->unk1C = 0;
    var_r31->unk20 = 0;
    var_r31->unk24 = 0;
    var_r31->unk28 = 0;
    var_r31->unk2C = 0;

    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        var_r31->unk0[var_r30] = Hu3DModelCreateFile(lbl_1_data_410[var_r30]);
        Hu3DModelPosSet(var_r31->unk0[var_r30], lbl_1_data_424[var_r30].x, lbl_1_data_424[var_r30].y, lbl_1_data_424[var_r30].z);
    }
    Hu3DModelAttrSet(var_r31->unk0[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->unk0[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(var_r31->unk0[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(var_r31->unk0[4], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(var_r31->unk0[3], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(var_r31->unk0[4], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(var_r31->unk0[2], HU3D_MOTATTR_LOOP);

    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        var_r31->unkA[var_r30] = Hu3DGLightCreateV(&lbl_1_data_460[var_r30].unk0, &lbl_1_data_460[var_r30].unkC, &lbl_1_data_460[var_r30].unk18);
        Hu3DGLightStaticSet(var_r31->unkA[var_r30], 1);
        Hu3DGLightPointSet(var_r31->unkA[var_r30], 100.0f, 1.0f, 3);
        Hu3DGLightColorSet(var_r31->unkA[var_r30], 0, 0, 0, 0);
    }
    Hu3DShadowCreate(30.0f, 20.0f, 20000.0f);
    Hu3DShadowTPLvlSet(1.0f);
    Hu3DShadowPosSet(&lbl_1_data_4B4[0], &lbl_1_data_4B4[1], &lbl_1_data_4B4[2]);
    Hu3DModelShadowMapSet(var_r31->unk0[0]);
    Hu3DModelShadowSet(var_r31->unk0[1]);
    var_r29 = fn_1_1DF4(var_r31);
    if (!var_r29) {
        OSReport("[!] m446StageCreate ERROR...\n");
        HuMemDirectFree(var_r31);
        return NULL;
    }
    if (lbl_1_bss_A0) {
        fn_1_1EC8(lbl_1_bss_A0, var_r29);
    }
    else {
        lbl_1_bss_A0 = var_r29;
    }
    return var_r31;
}

void fn_1_83F0(unkStruct9 *arg0)
{
    s32 var_r30;
    unkStruct3 *var_r31;

    var_r31 = lbl_1_bss_A0;
    do {
        if (arg0 == var_r31->unk0) {
            if (var_r31 == lbl_1_bss_A0) {
                lbl_1_bss_A0 = var_r31->unk8;
            }
            fn_1_1F04(var_r31);
            fn_1_1E5C(var_r31);

            for (var_r30 = 0; var_r30 < 5; var_r30++) {
                Hu3DModelKill(arg0->unk0[var_r30]);
            }
            HuMemDirectFree(arg0);
            return;
        }
        var_r31 = var_r31->unk8;
    } while (var_r31);
}

void fn_1_84AC(unkStruct9 *arg0)
{
    Hu3DModelAttrReset(arg0->unk0[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(arg0->unk0[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(arg0->unk0[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(arg0->unk0[4], HU3D_MOTATTR_PAUSE);
    arg0->unk24 = 1;
    arg0->unk1C = 0;
    arg0->unk20 = 0;
    arg0->unk18 = 0;
}

void fn_1_852C(unkStruct9 *arg0)
{
    Hu3DModelAttrSet(arg0->unk0[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->unk0[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->unk0[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(arg0->unk0[4], HU3D_MOTATTR_PAUSE);
    Hu3DMotionStartEndSet(arg0->unk0[2], 0.0f, 359.0f);
    Hu3DMotionStartEndSet(arg0->unk0[3], 0.0f, 119.0f);
    Hu3DMotionStartEndSet(arg0->unk0[4], 0.0f, 119.0f);
    arg0->unk24 = 0;
    arg0->unk1C = 0;
    arg0->unk20 = 0;
    arg0->unk18 = 0;
}

void fn_1_860C(unkStruct9 *arg0)
{
    arg0->unk28 = 1;
}
