#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "string.h"

#include "REL/m453Dll.h"

typedef struct M453DllWork {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ Vec unk_04;
    /* 0x10 */ Vec unk_10;
    /* 0x1C */ Vec unk_1C;
    /* 0x28 */ Vec unk_28;
    /* 0x34 */ Vec unk_34;
    /* 0x40 */ Vec unk_40;
    /* 0x4C */ Vec unk_4C;
    /* 0x58 */ Vec unk_58;
    /* 0x64 */ Vec unk_64[3];
    /* 0x88 */ Vec unk_88[3];
    /* 0xAC */ Vec unk_AC[3];
    /* 0xD0 */ Vec unk_D0[3];
    /* 0xF4 */ float unk_F4[3];
    /* 0x100 */ float unk_100[3];
    /* 0x10C */ float unk_10C[3];
    /* 0x118 */ float unk_118[3];
    /* 0x124 */ float unk_124[3];
    /* 0x130 */ float unk_130;
    /* 0x134 */ float unk_134;
    /* 0x138 */ float unk_138;
    /* 0x13C */ float unk_13C;
    /* 0x140 */ float unk_140;
    /* 0x144 */ float unk_144;
    /* 0x148 */ float unk_148;
} M453DllWork; /* size 0x14C */

typedef struct M453DllUnkStruct {
    s16 unk_00;
    s16 unk_02;
    float unk_04;
    float unk_08;
    char unk0C[0x34];
} M453DllUnkStruct; /* 0x40 */

typedef struct M453DllWork2 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    char unk08[2];
    u8 unk_0A;
    char unk0B;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    float unk_1C;
    float unk_20;
    float unk_24;
    float unk_28;
    Vec unk_2C;
    Vec unk_38;
    float unk_44;
    float unk_48;
    float unk_4C;
    Vec unk_50;
    M453DllUnkStruct unk_5C;
    u8 unk_9C;
    s32 unk_A0;
} M453DllWork2; /* size 0xA4 */ // same as Unkm403Struct_01

void fn_1_440(omObjData *object);
void fn_1_460(omObjData *object);
void fn_1_848(omObjData *object);
void fn_1_FFC(omObjData *object);
void fn_1_105C(omObjData *object);
void fn_1_1248(omObjData *object);
void fn_1_14F8(omObjData *object);
void fn_1_15FC(omObjData *object);
void fn_1_1870(float arg8, Vec *arg0, Vec *arg1, float arg9);
void fn_1_1910(float arg8, Vec *arg0, Vec *arg1, float arg9, Vec *arg2, Vec *arg3, float argA);
void fn_1_1BF0(omObjData *object);
void fn_1_1FA0(omObjData *object);
void fn_1_20EC(omObjData *object);
void fn_1_23E0(omObjData *object);
void fn_1_2E24(omObjData *object);
s32 fn_1_36DC(void);
void fn_1_39C8(omObjData *object);
void fn_1_3C94(omObjData *object);
s16 fn_1_3E9C(s32 arg0, s16 arg1, ParticleHook);
void fn_1_3F38(ModelData *model, ParticleData *particle, Mtx matrix);
s32 fn_1_43B8(void);
float fn_1_440C(float arg8, float arg9, float argA);
void fn_1_4E84(float *arg0, float *arg1, float *arg2, s32 arg3);
float fn_1_513C(float arg8, float *arg0, float *arg1, float *arg2, s32 arg3);
void fn_1_5290(float *arg0, float (*arg1)[3], float (*arg2)[3], s32 arg3);
void fn_1_5670(float arg8, float *arg0, float *arg1, float (*arg2)[3], float (*arg3)[3], s32 arg4);
float fn_1_5884(Vec *arg0);
s32 fn_1_63AC(void);
void fn_1_6448(void);

s16 lbl_1_data_0 = -1;

Vec lbl_1_data_4 = { 0.0f, 4000.0f, 4000.0f };

Vec lbl_1_data_10 = { 0.0f, -0.7f, -0.6f };

GXColor lbl_1_data_1C[0xA] = {
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0, 0, 0, 0 },
    { 0x45, 0x7A, 0, 0 },
    { 0xC4, 0xFA, 0, 0 },
    { 0, 0, 0, 0 },
    { 0x3F, 0x80, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
};

omObjData *lbl_1_bss_58;
omObjData *lbl_1_bss_54;
omObjData *lbl_1_bss_50;
omObjData *lbl_1_bss_4C;
omObjData *lbl_1_bss_3C[4];
u16 lbl_1_bss_3A;
s16 lbl_1_bss_38;
s16 lbl_1_bss_36;
s16 lbl_1_bss_34;
s16 lbl_1_bss_32;
s16 lbl_1_bss_1E[0xA];
s16 lbl_1_bss_1C;
s16 lbl_1_bss_18[2];
s32 lbl_1_bss_14;
s32 lbl_1_bss_8[3];
s16 lbl_1_bss_2[3];
s16 lbl_1_bss_0;

void ObjectSetup(void)
{
    Process *var_r31;
    s32 var_r30;
    omObjData *var_r29;
    LightData *var_r28;
    s32 var_r27;
    s32 var_r26;

    OSReport("******* M453ObjectSetup *********\n");
    Hu3DLighInit();
    var_r26 = Hu3DGLightCreateV(&lbl_1_data_4, &lbl_1_data_10, lbl_1_data_1C);
    Hu3DGLightInfinitytSet(var_r26);
    var_r28 = Hu3DGlobalLight;
    var_r28->unk_00 |= 0x8000;
    var_r31 = omInitObjMan(0x32, 0x2000);
    var_r27 = frand() & 0x1F;
    for (var_r30 = 0; var_r30 < var_r27; var_r30++) {
        fn_1_43B8();
    }
    CRot.x = -23.5f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 320.0f;
    Center.z = 147.0f;
    CZoom = 1720.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 400.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lbl_1_bss_54 = omAddObjEx(var_r31, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_58 = omAddObjEx(var_r31, 0x10, 8, 0, -1, fn_1_440);
    lbl_1_bss_4C = omAddObjEx(var_r31, 0x20, 0x10, 0, -1, fn_1_105C);
    lbl_1_bss_50 = omAddObjEx(var_r31, 0x50, 0x10, 0, -1, fn_1_14F8);
    omAddObjEx(var_r31, 0x60, 0, 0, -1, fn_1_39C8);
    fn_1_64E8(var_r31);
    fn_1_7C2C(3);
    omMakeGroupEx(var_r31, 0, 4);
    omGetGroupMemberListEx(var_r31, 0);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r29 = omAddObjEx(var_r31, 0x30, 2, 8, 0, fn_1_1BF0);
        lbl_1_bss_3C[var_r30] = var_r29;
        var_r29->work[0] = var_r30;
        var_r29->work[1] = var_r30;
    }
    omGameSysInit(var_r31);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    HuAudSndGrpSet(0x1C);
    lbl_1_bss_2[0] = 1;
    if (GWMGRecordGet(9) == 0) {
        GWMGRecordSet(9, 0);
    }
    fn_1_8F48(var_r31, GWMGRecordGet(9));
    fn_1_924C(0);
}

void fn_1_440(omObjData *object)
{
    lbl_1_bss_3A = 0;
    object->func = fn_1_460;
}

void fn_1_460(omObjData *object)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;

    switch (lbl_1_bss_3A) {
        case 0:
            sp2C.x = 0.0f;
            sp2C.y = 0.0f;
            sp2C.z = -50.0f;
            sp20.x = -90.0f;
            sp20.y = 90.0f;
            sp20.z = 0.0f;
            var_f31 = 2200.0f;
            fn_1_1870(1.0f, &sp2C, &sp20, var_f31);
            lbl_1_bss_32 = 0x3C;
            lbl_1_bss_3A += 1;
            break;
        case 1:
            if (--lbl_1_bss_32 == 0) {
                lbl_1_bss_3A += 1;
            }
            break;
        case 2:
            if (lbl_1_bss_32 == 0) {
                fn_1_7C3C();
                lbl_1_bss_32 = 0x5A;
                sp2C.x = 200.0f;
                sp2C.y = 100.0f;
                sp2C.z = -50.0f;
                sp20.x = -50.0f;
                sp20.y = 90.0f;
                sp20.z = 0.0f;
                var_f31 = 2000.0f;
                sp14.x = 0.0f;
                sp14.y = 320.0f;
                sp14.z = 147.0f;
                sp8.x = -23.5f;
                sp8.y = 0.0f;
                sp8.z = 0.0f;
                var_f30 = 1720.0f;
                fn_1_1910(180.0f, &sp14, &sp8, var_f30, &sp2C, &sp20, var_f31);
            }
            if (--lbl_1_bss_32 == 0) {
                lbl_1_bss_3A += 1;
            }
            break;
        case 3:
            if (lbl_1_bss_32 == 0) {
                lbl_1_bss_32 = 0x5A;
            }
            if (--lbl_1_bss_32 == 0) {
                lbl_1_bss_3A += 1;
            }
            break;
        case 4:
            lbl_1_bss_3A = 5;
            lbl_1_bss_38 = lbl_1_bss_36 = -1;
            object->func = fn_1_848;
            HuSprAnimRead(HuDataReadNum(0x220013, 0x10000000));
            break;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_FFC;
    }
}

s32 lbl_1_data_68[9] = {
    -1,
    0x610000,
    0x610001,
    0x610002,
    0x610003,
    0x610004,
    0x610005,
    0x610006,
    0x610007,
};

void fn_1_848(omObjData *object)
{
    Vec sp1C;
    Vec sp10;
    s16 sp8[4];
    float var_f31;

    s32 var_r31;
    s32 var_r30;
    s32 var_r28;

    switch (lbl_1_bss_3A) {
        case 5:
            if (lbl_1_bss_36 == -1) {
                lbl_1_bss_34 = 0x708;
                lbl_1_bss_36 = MGSeqCreate(3, 0);
                MGSeqPosSet(lbl_1_bss_36, 320.0f, 240.0f);
            }
            else if (MGSeqStatGet(lbl_1_bss_36) == 0) {
                lbl_1_bss_36 = -1;
                lbl_1_bss_3A += 1;
                lbl_1_bss_32 = 0;
                lbl_1_data_0 = 4;
            }
            if ((lbl_1_data_68[0] == -1) && ((MGSeqStatGet(lbl_1_bss_36) & 0x10) != 0)) {
                lbl_1_data_68[0] = HuAudSeqPlay(0x48);
            }
            break;
        case 6:
            var_r30 = 0;
            if ((lbl_1_data_0 == 0) && (fn_1_8240() == 0)) {
                var_r30++;
            }
            if (var_r30 != 0) {
                lbl_1_bss_3A += 1;
            }
            break;
        case 7:
            if (lbl_1_bss_36 == -1) {
                lbl_1_bss_36 = MGSeqCreate(3, 1);
                MGSeqPosSet(lbl_1_bss_36, 320.0f, 240.0f);
                MGSeqKill(lbl_1_bss_38);
                HuAudSeqFadeOut(lbl_1_data_68[0], 0x64);
            }
            else if (MGSeqStatGet(lbl_1_bss_36) == 0) {
                lbl_1_bss_36 = -1;
                if (lbl_1_bss_2[0] == 0) {
                    if (lbl_1_data_0 != 0) {
                        for (var_r31 = 0; var_r31 < 4; var_r31++) {
                            if (((M453DllWork2 *)lbl_1_bss_3C[var_r31]->data)->unk_07 != 0) {
                                break;
                            }
                        }
                        sp1C.x = lbl_1_bss_3C[var_r31]->trans.x;
                        sp1C.y = 100.0f;
                        sp1C.z = lbl_1_bss_3C[var_r31]->trans.z;
                        sp10.x = -18.0f;
                        sp10.y = 0.0f;
                        sp10.z = 0.0f;
                        var_f31 = 600.0f;
                        fn_1_1870(45.0f, &sp1C, &sp10, var_f31);
                    }
                    lbl_1_bss_3A = 9;
                    lbl_1_bss_32 = 0x5A;
                }
                else {
                    if ((lbl_1_bss_14 != 0) && (lbl_1_bss_0 >= 0xF)) {
                        GWGameStat.present[0x31] = 1;
                    }
                    if ((lbl_1_bss_14 != 0) && ((s32)GWMGRecordGet(9) < lbl_1_bss_0)) {
                        GWMGRecordSet(9, lbl_1_bss_0);
                        lbl_1_bss_3A = 8;
                        fn_1_924C(1);
                    }
                    else {
                        lbl_1_bss_36 = -1;
                        lbl_1_bss_3A = 9;
                        lbl_1_bss_32 = 0x5A;
                    }
                    fn_1_6448();
                }
            }
            break;
        case 8:
            if (lbl_1_bss_36 == -1) {
                lbl_1_bss_36 = MGSeqCreate(0xE, lbl_1_bss_0);
            }
            else if (MGSeqStatGet(lbl_1_bss_36) == 0) {
                lbl_1_bss_36 = -1;
                lbl_1_bss_32 = 0x5A;
                lbl_1_bss_3A = 9;
            }
            break;
        case 9:
            if (--lbl_1_bss_32 == 0) {
                lbl_1_bss_3A += 1;
            }
            break;
        case 10:
            if (lbl_1_bss_2[0] == 0) {
                if (lbl_1_bss_36 == -1) {
                    if (lbl_1_data_0 == 0) {
                        lbl_1_bss_36 = MGSeqCreate(3, 2);
                        HuAudSStreamPlay(4);
                    }
                    else {
                        for (var_r31 = 0; var_r31 < 4; var_r31++) {
                            sp8[var_r31] = -1;
                        }
                        for (var_r31 = 0, var_r28 = 0; var_r31 < 4; var_r31++) {
                            if (((M453DllWork2 *)lbl_1_bss_3C[var_r31]->data)->unk_07 != 0) {
                                sp8[var_r28++] = GWPlayerCfg[var_r31].character;
                            }
                        }
                        lbl_1_bss_36 = MGSeqCreate(5, 3, sp8[0], sp8[1], sp8[2], sp8[3]);
                        HuAudSStreamPlay(1);
                    }
                }
                lbl_1_bss_36 = -1;
                lbl_1_bss_32 = 0xD2;
                lbl_1_bss_3A += 1;
            }
            else {
                if (lbl_1_data_0 != 0) {
                    HuAudSStreamPlay(1);
                }
                else {
                    HuAudSStreamPlay(4);
                }
                lbl_1_bss_36 = -1;
                lbl_1_bss_32 = 0xD2;
                lbl_1_bss_3A += 1;
            }
            break;
        case 11:
            if (--lbl_1_bss_32 == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                object->func = fn_1_FFC;
            }
            break;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_FFC;
    }
}

void fn_1_FFC(omObjData *object)
{
    if (WipeStatGet() == 0) {
        fn_1_6748();
        CharModelKill(-1);
        MGSeqKill(lbl_1_bss_38);
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_105C(omObjData *object)
{
    Hu3DLightAllKill();
    lbl_1_bss_18[0] = Hu3DGLightCreateV(&lbl_1_data_4, &lbl_1_data_10, lbl_1_data_1C);
    Hu3DGLightStaticSet(lbl_1_bss_18[0], 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_18[0]);
    lbl_1_bss_18[1] = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0, 0, 0);
    Hu3DGLightStaticSet(lbl_1_bss_18[1], 1);
    Hu3DGLightPointSet(lbl_1_bss_18[1], 0.0f, 0.0f, 3);
    Hu3DGLightColorSet(lbl_1_bss_18[0], 0, 0, 0, 0xFF);
    Hu3DGLightPosSet(lbl_1_bss_18[1], -1470.0f, 800.0f, -2000.0f, 0.0f, -1.0f, 0.0f);
    Hu3DGLightColorSet(lbl_1_bss_18[1], 0, 0, 0, 0xFF);
    Hu3DGLightPointSet(lbl_1_bss_18[1], 1200.0f, 0.6f, 3);
    object->func = fn_1_1248;
}

void fn_1_1248(omObjData *object)
{
    s32 var_r30;

    s8 sp11[9] = { 0x01, 0x00, 0x02, 0x01, 0x00, 0x03, 0x02, 0x01, 0x00 };
    s8 sp8[9] = { 0x01, 0x01, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03 };

    switch (lbl_1_bss_3A) {
        case 0:
            break;
        case 1:
            Hu3DGLightColorSet(lbl_1_bss_18[0], 0xF0, 0xF0, 0xF0, 0xFF);
            break;
        case 3:
            Hu3DGLightColorSet(lbl_1_bss_18[1], 0xFF, 0xE0, 0xD0, 0xFF);
            break;
        case 5:
            object->work[0] = 0x1E;
            object->work[1] = 0x11;
            lbl_1_bss_8[0] = 1;
            break;
        case 6:
            if (fn_1_8240() == 0) {
                if (lbl_1_bss_8[0] == 0) {
                    lbl_1_bss_8[0] = 0x1E;
                    lbl_1_bss_0++;
                    lbl_1_bss_14 = fn_1_63AC();
                    if (lbl_1_bss_0 == 0x63) {
                        lbl_1_bss_3A = 7;
                        return;
                    }
                }
                lbl_1_bss_8[0]--;
                if (lbl_1_bss_8[0] == 0) {
                    var_r30 = (object->work[1] - 2) >> 1;
                    if (var_r30 < 0) {
                        var_r30 = 0;
                    }
                    fn_1_864C(sp11[var_r30]);
                    fn_1_7C2C(sp8[var_r30]);
                    fn_1_7C0C(0.01f * object->work[0]);
                    object->work[0] += 5;
                    if (object->work[1] > 2) {
                        object->work[1] -= 1;
                    }
                }
            }
            break;
    }
}

void fn_1_14F8(omObjData *object)
{
    M453DllWork *var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M453DllWork), MEMORY_DEFAULT_NUM);
    object->data = var_r31;
    var_r31->unk_148 = var_r31->unk_144 = 0.0f;
    var_r31->unk_140 = 1.0f;
    var_r31->unk_10.x = var_r31->unk_28.x = -23.5f;
    var_r31->unk_10.y = var_r31->unk_28.y = 0.0f;
    var_r31->unk_10.z = var_r31->unk_28.z = 0.0f;
    var_r31->unk_04.x = var_r31->unk_1C.x = 0.0f;
    var_r31->unk_04.y = var_r31->unk_1C.y = 320.0f;
    var_r31->unk_04.z = var_r31->unk_1C.z = 147.0f;
    var_r31->unk_130 = var_r31->unk_134 = 1720.0f;
    object->func = fn_1_15FC;
}

void fn_1_15FC(omObjData *object)
{
    float var_f31;
    M453DllWork *var_r31 = object->data;

    if (var_r31->unk_148 > 0.0f) {
        var_r31->unk_148 = var_r31->unk_148 - var_r31->unk_140;
        var_f31 = (var_r31->unk_144 - var_r31->unk_148) / var_r31->unk_144;
        var_f31 = sind((90.0f * var_f31));
        if (var_r31->unk_00 == 0) {
            var_r31->unk_04.x = var_r31->unk_1C.x + (var_f31 * (var_r31->unk_34.x - var_r31->unk_1C.x));
            var_r31->unk_04.y = var_r31->unk_1C.y + (var_f31 * (var_r31->unk_34.y - var_r31->unk_1C.y));
            var_r31->unk_04.z = var_r31->unk_1C.z + (var_f31 * (var_r31->unk_34.z - var_r31->unk_1C.z));
            var_r31->unk_10.x = var_r31->unk_28.x + (var_f31 * (var_r31->unk_40.x - var_r31->unk_28.x));
            var_r31->unk_10.y = var_r31->unk_28.y + (var_f31 * (var_r31->unk_40.y - var_r31->unk_28.y));
            var_r31->unk_10.z = var_r31->unk_28.z + (var_f31 * (var_r31->unk_40.z - var_r31->unk_28.z));
            var_r31->unk_130 = var_r31->unk_134 + (var_f31 * (var_r31->unk_138 - var_r31->unk_134));
        }
        else {
            fn_1_5670(2.0f * var_f31, (float *)&var_r31->unk_04, var_r31->unk_F4, (float(*)[3])var_r31->unk_64, (float(*)[3])var_r31->unk_88, 3);
            fn_1_5670(2.0f * var_f31, (float *)&var_r31->unk_10, var_r31->unk_100, (float(*)[3])var_r31->unk_AC, (float(*)[3])var_r31->unk_D0, 3);
            var_r31->unk_130 = fn_1_513C(2.0f * var_f31, var_r31->unk_124, var_r31->unk_10C, var_r31->unk_118, 3);
        }
    }
    CRot.x = var_r31->unk_10.x;
    CRot.y = var_r31->unk_10.y;
    CRot.z = var_r31->unk_10.z;
    Center.x = var_r31->unk_04.x;
    Center.y = var_r31->unk_04.y;
    Center.z = var_r31->unk_04.z;
    CZoom = var_r31->unk_130;
}

void fn_1_1870(float arg8, Vec *arg0, Vec *arg1, float arg9)
{
    M453DllWork *var_r31;

    var_r31 = lbl_1_bss_50->data;
    var_r31->unk_00 = 0;
    var_r31->unk_144 = arg8;
    var_r31->unk_148 = arg8;
    var_r31->unk_1C = var_r31->unk_04;
    var_r31->unk_34.x = arg0->x;
    var_r31->unk_34.y = arg0->y;
    var_r31->unk_34.z = arg0->z;
    var_r31->unk_28 = var_r31->unk_10;
    var_r31->unk_40.x = arg1->x;
    var_r31->unk_40.y = arg1->y;
    var_r31->unk_40.z = arg1->z;
    var_r31->unk_134 = var_r31->unk_130;
    var_r31->unk_138 = arg9;
}

void fn_1_1910(float arg8, Vec *arg0, Vec *arg1, float arg9, Vec *arg2, Vec *arg3, float argA)
{
    float var_f31;
    float var_f30;
    M453DllWork *var_r31 = lbl_1_bss_50->data;

    var_r31->unk_00 = 1;
    var_r31->unk_148 = var_r31->unk_144 = arg8;
    var_r31->unk_1C = var_r31->unk_04;
    var_r31->unk_34.x = arg0->x;
    var_r31->unk_34.y = arg0->y;
    var_r31->unk_34.z = arg0->z;
    var_r31->unk_4C.x = arg2->x;
    var_r31->unk_4C.y = arg2->y;
    var_r31->unk_4C.z = arg2->z;
    var_r31->unk_28 = var_r31->unk_10;
    var_r31->unk_40.x = arg1->x;
    var_r31->unk_40.y = arg1->y;
    var_r31->unk_40.z = arg1->z;
    var_r31->unk_58.x = arg3->x;
    var_r31->unk_58.y = arg3->y;
    var_r31->unk_58.z = arg3->z;
    var_r31->unk_134 = var_r31->unk_130;
    var_r31->unk_138 = arg9;
    var_r31->unk_13C = argA;
    var_r31->unk_64[0] = var_r31->unk_1C;
    var_r31->unk_64[1] = var_r31->unk_4C;
    var_r31->unk_64[2] = var_r31->unk_34;
    var_r31->unk_AC[0] = var_r31->unk_28;
    var_r31->unk_AC[1] = var_r31->unk_58;
    var_r31->unk_AC[2] = var_r31->unk_40;
    var_r31->unk_10C[0] = var_r31->unk_134;
    var_r31->unk_10C[1] = var_r31->unk_13C;
    var_r31->unk_10C[2] = var_r31->unk_138;
    var_r31->unk_124[0] = 0.0f;
    if ((var_r31->unk_10C[1] - var_r31->unk_10C[0]) < 0.0f) {
        var_f31 = -(var_r31->unk_10C[1] - var_r31->unk_10C[0]);
    }
    else {
        var_f31 = var_r31->unk_10C[1] - var_r31->unk_10C[0];
    }
    var_r31->unk_124[1] = var_f31;
    if ((var_r31->unk_10C[2] - var_r31->unk_10C[1]) < 0.0f) {
        var_f30 = -(var_r31->unk_10C[2] - var_r31->unk_10C[1]);
    }
    else {
        var_f30 = var_r31->unk_10C[2] - var_r31->unk_10C[1];
    }
    var_r31->unk_124[2] = var_r31->unk_124[1] + var_f30;
    fn_1_5290(var_r31->unk_F4, (float(*)[3])var_r31->unk_64, (float(*)[3])var_r31->unk_88, 3);
    fn_1_5290(var_r31->unk_100, (float(*)[3])var_r31->unk_AC, (float(*)[3])var_r31->unk_D0, 3);
    fn_1_4E84(var_r31->unk_124, var_r31->unk_10C, var_r31->unk_118, 3);
}

void fn_1_1BC8(float arg8)
{
    M453DllWork *var_r31 = lbl_1_bss_50->data;
    var_r31->unk_140 = arg8;
}

s32 lbl_1_data_C4[8] = { 0, 2, 3, 8, 0xA, 9, 0x17, 0x18 };

Vec lbl_1_data_E4[4] = {
    { -300.0f, 2200.0f, 0.0f },
    { -100.0f, 2200.0f, 0.0f },
    { 100.0f, 2200.0f, 0.0f },
    { 300.0f, 2200.0f, 0.0f },
};

void fn_1_1BF0(omObjData *object)
{
    M453DllWork2 *var_r31;
    s32 var_r29;
    s32 var_r28;
    u32 var_r27;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M453DllWork2), MEMORY_DEFAULT_NUM);
    object->data = var_r31;
    var_r31->unk_00 = object->work[0];
    var_r31->unk_01 = GWPlayerCfg[var_r31->unk_00].character;
    var_r31->unk_02 = var_r31->unk_00 >> 1;
    var_r31->unk_03 = var_r31->unk_00 & 1;
    var_r31->unk_04 = GWPlayerCfg[var_r31->unk_00].pad_idx;
    var_r31->unk_05 = GWPlayerCfg[var_r31->unk_00].iscom;
    var_r31->unk_06 = GWPlayerCfg[var_r31->unk_00].diff;
    var_r31->unk_18 = var_r31->unk_1A = 0;
    var_r31->unk_07 = 1;
    var_r31->unk_0C = 1;
    var_r31->unk_0D = 0;
    var_r31->unk_0E = 0;
    var_r31->unk_0A = 0;
    var_r31->unk_9C = 0;
    var_r27 = object->work[1];
    var_r31->unk_2C.x = lbl_1_data_E4[var_r27].x;
    var_r31->unk_2C.y = lbl_1_data_E4[var_r27].y + (100.0f * ((fn_1_43B8() - 0x8000) / 32768.0f));
    var_r31->unk_2C.z = lbl_1_data_E4[var_r27].z;
    var_r31->unk_44 = var_r31->unk_48 = var_r31->unk_4C = 0.0f;
    var_r31->unk_38.x = var_r31->unk_38.y = var_r31->unk_38.z = 0.0f;
    var_r31->unk_20 = var_r31->unk_38.y;
    var_r31->unk_24 = 0.0f;
    var_r31->unk_1C = 0.0f;
    var_r31->unk_28 = 1.0f;
    memset(&var_r31->unk_5C, 0, sizeof(M453DllUnkStruct));
    var_r31->unk_A0 = 1;
    if ((lbl_1_bss_2[0] != 0) && (var_r31->unk_05 == 0)) {
        lbl_1_bss_1E[lbl_1_bss_1C++] = var_r31->unk_00;
    }
    var_r28 = CharModelCreate(var_r31->unk_01, 4);
    object->model[0] = var_r28;
    Hu3DModelAttrSet(var_r28, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(var_r28);
    for (var_r29 = 0; var_r29 < 8; var_r29++) {
        object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_01, lbl_1_data_C4[var_r29]);
    }
    CharModelMotionDataClose(var_r31->unk_01);
    CharModelMotionSet(var_r31->unk_01, object->motion[var_r31->unk_18]);
    omSetTra(object, var_r31->unk_2C.x, var_r31->unk_2C.y, var_r31->unk_2C.z);
    Hu3DModelPosSet(var_r28, var_r31->unk_2C.x, var_r31->unk_2C.y, var_r31->unk_2C.z);
    Hu3DModelRotSet(var_r28, 0.0f, 30.0f, 0.0f);
    CharModelStepTypeSet(var_r31->unk_01, 1);
    CharModelVoiceEnableSet(var_r31->unk_01, object->motion[3], 0);
    object->func = fn_1_1FA0;
}

void fn_1_1FA0(omObjData *object)
{
    s32 sp8 = *object->model;
    M453DllWork2 *var_r31 = object->data;
    var_r31->unk_10 = var_r31->unk_12 = 0;
    var_r31->unk_14 = var_r31->unk_16 = 0;
    switch (lbl_1_bss_3A) {
        case 3:
            break;
        case 2:
            if (!(lbl_1_bss_32 < 60.0f)) {
                case 1:
                    var_r31->unk_18 = 3;
                    var_r31->unk_48 = 0.0f;
                    var_r31->unk_0C = 0;
            }
            break;
        case 5:
            object->func = fn_1_20EC;
            break;
    }
    if (var_r31->unk_2C.y < 10.0f) {
        omVibrate(var_r31->unk_00, 0xC, 6, 6);
        var_r31->unk_2C.y = 10.0f;
        var_r31->unk_0C = 1;
    }
    fn_1_2E24(object);
}

void fn_1_20EC(omObjData *object)
{
    M453DllWork2 *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r29 = object->model[0];
    var_r31 = object->data;
    if (var_r31->unk_07 != 0) {
        if ((lbl_1_bss_3A == 6) && ((var_r31->unk_07 & 2) == 0)) {
            if (var_r31->unk_05 != 0) {
                fn_1_23E0(object);
            }
            else {
                var_r31->unk_10 = HuPadStkX[var_r31->unk_04];
                var_r31->unk_12 = HuPadStkY[var_r31->unk_04];
                var_r31->unk_14 = HuPadBtnDown[var_r31->unk_04];
                var_r31->unk_16 = HuPadBtn[var_r31->unk_04];
            }
        }
        else {
            var_r31->unk_10 = var_r31->unk_12 = 0;
            var_r31->unk_14 = var_r31->unk_16 = 0;
        }
        switch (lbl_1_bss_3A) {
            case 5:
            case 6:
            case 8:
                break;
            case 7:
            case 9:
                object->scale.y += 0.2f * (1.0f - object->scale.y);
                var_r31->unk_38.y = fn_1_440C(var_r31->unk_38.y, 0.0f, 0.9f);
                break;
            case 10:
                if (var_r31->unk_18 != 6) {
                    var_r31->unk_18 = 6;
                }
                break;
        }
        if ((var_r31->unk_07 & 2) != 0) {
            var_r31->unk_10 = var_r31->unk_12 = 0;
            var_r31->unk_14 = var_r31->unk_16 = 0;
            if (object->scale.y < 0.2f) {
                omVibrate(var_r31->unk_00, 0xC, 4, 2);
                HuAudFXPlay(0x523);
                var_r31->unk_07 = 0;
                Hu3DModelShadowReset(var_r29);
                Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);
                lbl_1_data_0--;
                var_r28 = fn_1_3E9C(0x220013, 0x64, fn_1_3F38);
                Hu3DModelPosSet(var_r28, var_r31->unk_2C.x, var_r31->unk_2C.y, var_r31->unk_2C.z);
                Hu3DModelLayerSet(var_r28, 2);
            }
        }
        if (fn_1_8240() != 0) {
            var_r31->unk_A0 = 0;
        }
        else if (((var_r31->unk_07 & 2) == 0) && (var_r31->unk_A0 == 0)) {
            omVibrate(var_r31->unk_00, 0xC, 6, 6);
            var_r31->unk_A0 = 1;
        }
        fn_1_2E24(object);
    }
}

void fn_1_23E0(omObjData *object)
{
    Vec sp38[6];
    float sp20[6];
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    M453DllWork2 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s16 var_r28;
    s16 var_r27;
    s16 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    s16 var_r21;
    s16 var_r20;

    var_r22 = 0;
    var_r30 = 0;
    var_r29 = 0;
    for (; var_r30 < 4; var_r30++) {
        var_r31 = lbl_1_bss_3C[var_r30]->data;
        if ((var_r31->unk_05 == 0) && (var_r31->unk_07 != 0)) {
            break;
        }
    }
    var_r31 = object->data;
    if ((var_r30 >= 4) && (var_r31->unk_9C == 0)) {
        var_r22 = 1;
    }
    var_r28 = var_r31->unk_06;
    var_r27 = var_r26 = var_r21 = var_r20 = 0;
    switch (var_r31->unk_5C.unk_00) {
        case 0:
            if (fn_1_8240() != 0) {
                var_r31->unk_5C.unk_00 = 1;
            }
            break;
        case 1:
            var_r31->unk_5C.unk_00 = 2;
            var_r31->unk_5C.unk_02 = (s32)(60.0f * (1.2f - (0.2f * var_r28)) * (fn_1_43B8() / 65536.0f));
            var_r31->unk_5C.unk_04 = 500.0f * ((fn_1_43B8() - 0x8000) / 32768.0f);
            var_r31->unk_5C.unk_08 = 200.0f * ((fn_1_43B8() - 0x8000) / 32768.0f);
            var_r27 = var_r31->unk_10;
            var_r26 = var_r31->unk_12;
            break;
        case 2:
            sp8.x = var_r31->unk_5C.unk_04 - var_r31->unk_2C.x;
            sp8.y = 0.0f;
            sp8.z = var_r31->unk_5C.unk_08 - var_r31->unk_2C.z;
            var_f31 = fn_1_5884(&sp8);
            if (var_f31 < 20.0f) {
                var_r31->unk_5C.unk_00 = 3;
            }
            else {
                if (var_f31 >= 100.0f) {
                    var_f28 = 0.8f;
                }
                else {
                    var_f28 = 0.4f;
                }
                var_f30 = fn_1_440C(var_r31->unk_38.y, atan2d(sp8.x, sp8.z), var_f28);
                var_f29 = 48.0f + (4.0f * var_r28);
                var_r27 = var_f29 * sind(var_f30);
                var_r26 = var_f29 * -cosd(var_f30);
                if (fn_1_8240() == 0) {
                    var_r31->unk_5C.unk_00 = 0;
                    if (var_r31->unk_5C.unk_02 == 0) {
                        var_r31->unk_5C.unk_02 = -1;
                    }
                }
                else if (var_r31->unk_5C.unk_02 >= 0) {
                    if (var_r31->unk_5C.unk_02 == 0) {
                        if ((var_f31 < 150.0f) && (var_r31->unk_0E != 0)) {
                            var_r31->unk_5C.unk_00 = 3;
                        }
                        else if (((s32)((var_r28 + 2) * (fn_1_43B8() / 65536.0f)) != 0) && (var_r22 == 0)) {
                            var_r31->unk_5C.unk_00 = 4;
                        }
                        else {
                            var_r31->unk_5C.unk_00 = 1;
                        }
                    }
                    else {
                        var_r31->unk_5C.unk_02--;
                    }
                }
            }
            break;
        case 3:
            sp8.x = var_r31->unk_5C.unk_04 - var_r31->unk_2C.x;
            sp8.y = 0.0f;
            sp8.z = var_r31->unk_5C.unk_08 - var_r31->unk_2C.z;
            if ((fn_1_5884(&sp8) >= 30.000002f) && (var_r31->unk_0E == 0)) {
                var_r31->unk_5C.unk_00 = 2;
            }
            else if (fn_1_8240() == 0) {
                var_r31->unk_5C.unk_00 = 0;
            }
            else {
                if (var_r31->unk_5C.unk_02 > 0) {
                    var_r31->unk_5C.unk_02--;
                }
                if (var_r31->unk_5C.unk_02 == 0) {
                    if (((s32)((var_r28 + 2) * (fn_1_43B8() / 65536.0f)) != 0) && (var_r22 == 0)) {
                        var_r31->unk_5C.unk_00 = 4;
                    }
                    else {
                        var_r31->unk_5C.unk_00 = 1;
                    }
                }
            }
            break;
        case 4:
            var_r24 = fn_1_82AC(sp38);
            for (var_r30 = 0; var_r30 < var_r24; var_r30++) {
                VECSubtract(&sp38[var_r30], &var_r31->unk_2C, &sp8);
                sp20[var_r30] = VECMag(&sp8);
            }
            for (var_r30 = 0; var_r30 < (var_r24 - 1); var_r30++) {
                for (var_r29 = var_r30 + 1; var_r29 < var_r24; var_r29++) {
                    if (sp20[var_r30] > sp20[var_r29]) {
                        sp14 = sp38[var_r30];
                        sp38[var_r30] = sp38[var_r29];
                        sp38[var_r29] = sp14;
                        var_f31 = sp20[var_r30];
                        sp20[var_r30] = sp20[var_r29];
                        sp20[var_r29] = var_f31;
                    }
                }
            }
            var_r25 = 0x3E8;
            var_r23 = var_r25 * (fn_1_43B8() / 65536.0f);
            for (var_r30 = 0; var_r30 < (var_r24 - 1); var_r30++) {
                var_r25 = 0.1f * (var_r25 * (5.0f + var_r28));
                var_r23 -= var_r25;
                if (var_r23 < 0) {
                    break;
                }
            }
            var_r31->unk_5C.unk_04 = sp38[var_r30].x + (100.0f * (0.5f - (0.15f * var_r28)) * ((fn_1_43B8() - 0x8000) / 32768.0f));
            var_r31->unk_5C.unk_08 = sp38[var_r30].z + (100.0f * (0.5f - (0.15f * var_r28)) * ((fn_1_43B8() - 0x8000) / 32768.0f));
            var_r31->unk_5C.unk_00 = 2;
            var_r31->unk_5C.unk_02 = -1;
            var_r27 = var_r31->unk_10;
            var_r26 = var_r31->unk_12;
            break;
    }
    var_r31->unk_10 = var_r27;
    var_r31->unk_12 = var_r26;
    var_r31->unk_14 = var_r21;
    var_r31->unk_16 = var_r20;
}

void fn_1_2E24(omObjData *object)
{
    s16 spA;
    s16 sp8;
    float var_f29;

    M453DllWork2 *var_r31;
    s16 var_r30;
    s16 var_r29;
    s16 var_r28;
    s16 var_r27;
    s32 var_r25;

    var_r31 = object->data;
    var_r25 = object->model[0];
    var_r28 = var_r31->unk_18;
    var_r31->unk_50 = var_r31->unk_2C;
    var_r30 = var_r31->unk_10;
    var_r29 = var_r31->unk_12;
    spA = var_r31->unk_14;
    sp8 = var_r31->unk_16;
    switch (var_r31->unk_18) {
        case 0:
        case 1:
        case 2:
            var_r31->unk_1C = 0.14f * sqrtf((var_r30 * var_r30) + (var_r29 * var_r29));
            if (var_r31->unk_1C > 0.1f) {
                if (var_r31->unk_1C >= 6.0f) {
                    var_r28 = 2;
                    var_r27 = 1;
                }
                else {
                    var_r28 = 1;
                    var_r27 = 1;
                }
                var_f29 = atan2d(var_r30, -var_r29);
                var_r31->unk_38.y = fn_1_440C(var_r31->unk_38.y, var_f29, 0.5f);
                var_r31->unk_20 = var_r31->unk_38.y;
                var_r31->unk_24 += 1.0f;
                if (var_r31->unk_24 >= (0.5f * var_r31->unk_28)) {
                    var_r31->unk_24 = var_r31->unk_24 - (0.5f * var_r31->unk_28);
                }
                var_r31->unk_1C = var_r31->unk_1C * (1.0 + (0.25 * cosd((90.0f * (var_r31->unk_24 / (0.5f * var_r31->unk_28))))));
            }
            else {
                var_r31->unk_24 = 0.0f;
                var_r31->unk_1C = 0.0f;
                var_r28 = 0;
                var_r27 = 1;
            }
            var_r31->unk_48 = -2.4333334f;
            break;
        case 3:
            var_r27 = 0;
            if ((Hu3DData[var_r25].unk_0C == -1) && (CharModelMotionEndCheck(var_r31->unk_01) != 0)) {
                var_r31->unk_48 += -2.4333334f;
            }
            else {
                var_r31->unk_48 = 0.0f;
            }
            if (var_r31->unk_0C != 0) {
                if (var_r31->unk_0D != 0) {
                    var_r31->unk_48 = 0.0f;
                    var_r31->unk_0D = 0;
                    var_r28 = 5;
                    var_r27 = 0;
                }
                else {
                    var_r31->unk_48 *= -0.1f;
                    var_r31->unk_0C = 0;
                    var_r28 = 4;
                    var_r27 = 0;
                }
            }
            break;
        case 4:
            var_r31->unk_48 += -2.4333334f;
            if ((var_r31->unk_0C != 0) && (CharModelMotionEndCheck(var_r31->unk_01) != 0)) {
                var_r28 = 5;
                var_r27 = 0;
            }
            break;
        case 5:
            if (CharModelMotionEndCheck(var_r31->unk_01) != 0) {
                var_r28 = 0;
                var_r27 = 1;
            }
            break;
        case 6:
        case 7:
            var_r27 = 0;
            var_r31->unk_48 = -2.4333334f;
            break;
    }
    if (var_r31->unk_07 & 4) {
        if (var_r31->unk_0A & 2) {
            Hu3DModelAttrSet(var_r25, HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(var_r25, HU3D_ATTR_DISPOFF);
        }
        if (--var_r31->unk_0A == 0) {
            var_r31->unk_07 = var_r31->unk_07 & 0xFFFFFFFB;
        }
    }
    var_r31->unk_44 = var_r31->unk_1C * sind(var_r31->unk_20);
    var_r31->unk_4C = var_r31->unk_1C * cosd(var_r31->unk_20);
    var_r31->unk_2C.x += var_r31->unk_44;
    if (var_r31->unk_0C == 0) {
        var_r31->unk_2C.y = var_r31->unk_2C.y + var_r31->unk_48;
    }
    var_r31->unk_2C.z += var_r31->unk_4C;
    if (var_r28 != var_r31->unk_1A) {
        var_r31->unk_1A = var_r28;
        var_r31->unk_18 = var_r28;
        CharModelMotionShiftSet(var_r31->unk_01, object->motion[var_r31->unk_18], 0.0f, 8.0f, var_r27);
        var_r31->unk_28 = CharModelMotionMaxTimeGet(var_r31->unk_01);
    }
    omSetTra(object, var_r31->unk_2C.x, var_r31->unk_2C.y, var_r31->unk_2C.z);
    omSetRot(object, var_r31->unk_38.x, var_r31->unk_38.y, var_r31->unk_38.z);
}

void fn_1_3648(void)
{
    s32 var_r31;
    M453DllWork2 *var_r30;
    s32 var_r29;

    var_r29 = 0;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = lbl_1_bss_3C[var_r31]->data;
        if (var_r30->unk_07 != 0) {
            var_r30->unk_0E = 0;
        }
    }
    while ((fn_1_36DC() != 0) && (var_r29 < 0x32)) {
        var_r29++;
    }
}

s32 fn_1_36DC(void)
{
    Vec sp14[4];
    Vec sp8;
    float var_f30;
    float var_f31;

    M453DllWork2 *var_r31;
    s32 var_r30;
    s32 var_r29;
    M453DllWork2 *var_r28;
    M453DllWork2 *var_r27;
    s32 var_r26;
    omObjData *var_r25;

    var_r26 = 0;
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        sp14[var_r30].x = sp14[var_r30].y = sp14[var_r30].z = 0.0f;
    }
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        var_r28 = lbl_1_bss_3C[var_r30]->data;
        if (var_r28->unk_07 != 0) {
            for (var_r29 = var_r30 + 1; var_r29 < 4; var_r29++) {
                var_r27 = lbl_1_bss_3C[var_r29]->data;
                if (var_r27->unk_07 != 0) {
                    VECSubtract(&var_r28->unk_2C, &var_r27->unk_2C, &sp8);
                    var_f31 = VECMag(&sp8);
                    if (var_f31 < 80.0f) {
                        VECNormalize(&sp8, &sp8);
                        var_f30 = 0.0001f + (0.5f * (80.0f - var_f31));
                        VECScale(&sp8, &sp8, var_f30);
                        VECAdd(&sp14[var_r30], &sp8, &sp14[var_r30]);
                        VECSubtract(&sp14[var_r29], &sp8, &sp14[var_r29]);
                        var_r28->unk_0E++;
                        var_r27->unk_0E++;
                        var_r26++;
                    }
                }
            }
        }
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r25 = lbl_1_bss_3C[var_r30];
        var_r31 = var_r25->data;
        if (var_r31->unk_07 != 0) {
            VECAdd(&var_r31->unk_2C, &sp14[var_r30], &var_r31->unk_2C);
            if (var_r31->unk_2C.x > 660.0f) {
                var_r31->unk_2C.x = 660.0f;
            }
            if (var_r31->unk_2C.x < -660.0f) {
                var_r31->unk_2C.x = -660.0f;
            }
            if (var_r31->unk_2C.z > 360.0f) {
                var_r31->unk_2C.z = 360.0f;
            }
            if (var_r31->unk_2C.z < -360.0f) {
                var_r31->unk_2C.z = -360.0f;
            }
            omSetTra(var_r25, var_r31->unk_2C.x, var_r31->unk_2C.y, var_r31->unk_2C.z);
        }
    }
    return var_r26;
}

void fn_1_39C8(omObjData *object)
{
    s32 sp8[4];

    s32 var_r31;
    s32 var_r30;
    M453DllWork2 *var_r29;
    s32 var_r28;
    s32 var_r27;

    if (lbl_1_bss_3A >= 6) {
        if (fn_1_8240() != 0) {
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                fn_1_3C94(lbl_1_bss_3C[var_r31]);
            }
        }
        else {
            for (var_r31 = 0, var_r30 = 0; var_r31 < 4; var_r31++) {
                ((M453DllWork2 *)lbl_1_bss_3C[var_r31]->data)->unk_9C = 0;
                if (((M453DllWork2 *)lbl_1_bss_3C[var_r31]->data)->unk_07 != 0) {
                    sp8[var_r30++] = var_r31;
                }
            }
            if (var_r30 != 0) {
                var_r31 = sp8[(s32)(var_r30 * (fn_1_43B8() / 65536.0f))];
                ((M453DllWork2 *)lbl_1_bss_3C[var_r31]->data)->unk_9C = 1;
            }
        }
        var_r27 = 0;
        for (var_r28 = 0; var_r28 < 4; var_r28++) {
            var_r29 = lbl_1_bss_3C[var_r28]->data;
            if (var_r29->unk_07 != 0) {
                var_r29->unk_0E = 0;
            }
        }
        while ((fn_1_36DC() != 0) && (var_r27 < 0x32)) {
            var_r27++;
        }
    }
}

void fn_1_3BB4(Vec *arg0, Vec *arg1)
{
    Vec sp18[6];
    Vec spC;
    float var_f31;
    float var_f30;

    s32 var_r31;
    s32 var_r30;

    var_r30 = fn_1_844C(sp18);
    var_f31 = 2000.0f;
    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        VECSubtract(&sp18[var_r31], arg0, &spC);
        var_f30 = VECMag(&spC);
        if (!(var_f30 >= var_f31)) {
            var_f31 = var_f30;
            *arg1 = sp18[var_r31];
        }
    }
}

float lbl_1_data_114[8] = { 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 100.0f, 40.0f, 80.0f };

float lbl_1_data_134[8] = { 160.0f, 160.0f, 180.0f, 160.0f, 160.0f, 180.0f, 180.0f, 200.0f };

void fn_1_3C94(omObjData *object)
{
    Vec sp8;
    float var_f31;
    float var_f30;

    M453DllWork2 *var_r31;
    s32 var_r29;
    s16 var_r28;

    var_r31 = object->data;
    if (var_r31->unk_07 != 0) {
        var_f30 = fn_1_80B0(&var_r31->unk_2C, lbl_1_data_114[var_r31->unk_01]) - 10.0f;
        if (var_f30 < 0.0f) {
            var_f30 = 0.0f;
        }
        if ((var_r31->unk_07 & 2) == 0) {
            var_f31 = 1.0f;
            if (var_f30 < lbl_1_data_134[var_r31->unk_01]) {
                if (fn_1_867C(&var_r31->unk_2C, &sp8) != 0) {
                    var_r31->unk_2C.x = sp8.x;
                    var_r31->unk_2C.z = sp8.z;
                }
                else {
                    if ((fn_1_7F54(var_r31->unk_2C.x, var_r31->unk_2C.z) - 10.0f) < 100.0f) {
                        var_r31->unk_07 = var_r31->unk_07 | 2;
                        var_r28 = lbl_1_bss_0;
                        var_r29 = var_r31->unk_00;
                        GWPlayerCoinWinSet(var_r29, var_r28);
                    }
                    var_f31 = var_f30 / lbl_1_data_134[var_r31->unk_01];
                }
            }
        }
        else {
            var_f31 = var_f30 / lbl_1_data_134[var_r31->unk_01];
        }
        if (object->scale.y < var_f31) {
            var_f31 = object->scale.y + (0.2f * (var_f31 - object->scale.y));
        }
        object->scale.y = var_f31;
    }
}

s16 fn_1_3E9C(s32 arg0, s16 arg1, ParticleHook arg2)
{
    ParticleData *var_r31;
    s32 var_r30;
    AnimData *var_r29;

    var_r29 = HuSprAnimRead(HuDataReadNum(arg0, 0x10000000));
    var_r30 = Hu3DParticleCreate(var_r29, arg1);
    Hu3DParticleHookSet(var_r30, arg2);
    var_r31 = Hu3DData[var_r30].unk_120;
    var_r31->unk_2E = var_r30;
    var_r31->unk_00 = var_r31->unk_02 = 0;
    return var_r30;
}

void fn_1_3F38(ModelData *model, ParticleData *particle, Mtx matrix)
{
    s16 sp8 = 0;
    float var_f31;
    float var_f30;
    float var_f29;

    HsfanimStruct01 *var_r31;
    s32 var_r29;

    switch (particle->unk_00) {
        case 0:
            var_f29 = 360.0f / particle->unk_30;
            for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
                var_r31->unk08.x = sind((var_f29 * var_r29)) * (1.0f + (0.1f * (6.0f * ((fn_1_43B8() - 0x8000) / 32768.0f))));
                var_r31->unk08.y = 0.0f;
                var_r31->unk08.z = cosd((var_f29 * var_r29)) * (1.0f + (0.1f * (6.0f * ((fn_1_43B8() - 0x8000) / 32768.0f))));
                var_r31->unk34.x = 0.0f;
                var_r31->unk34.y = 0.0f;
                var_r31->unk34.z = 0.0f;
            }
            particle->unk_02 = 0x1E;
            particle->unk_00++;
        case 1:
            particle->unk_02--;
            var_f31 = (30.0f - particle->unk_02) / 30.0f;
            var_f30 = particle->unk_02 / 30.0f;
            for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
                var_r31->unk34.x += 5.0f * var_f30 * var_r31->unk08.x;
                var_r31->unk34.y = 20.0f;
                var_r31->unk34.z += 5.0f * var_f30 * var_r31->unk08.z;
                var_r31->unk2C = 20.0f + (60.0f * var_f31);
                var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = 0xFF;
                var_r31->unk40.a = 64.0f * (1.0f - (var_f31 * var_f31));
            }
            if (particle->unk_02 == 0) {
                particle->unk_00++;
            }
            break;
        case 2:
            Hu3DModelKill(particle->unk_2E);
            return;
    }
    DCFlushRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

u32 lbl_1_data_154 = 0x41C64E6D;

s32 fn_1_43B8(void)
{
    lbl_1_data_154 *= 0x41C64E6D;
    lbl_1_data_154 += 0x3039;
    return lbl_1_data_154 >> 0x10;
}

float fn_1_440C(float arg8, float arg9, float argA)
{
    float var_f31;

    if (arg8 > 180.0f) {
        arg8 -= 360.0f;
    }
    else if (arg8 <= -180.0f) {
        arg8 += 360.0f;
    }
    if (arg9 > 180.0f) {
        arg9 -= 360.0f;
    }
    else if (arg9 <= -180.0f) {
        arg9 += 360.0f;
    }
    var_f31 = arg8 - arg9;
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    else if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    }
    arg8 = arg9 + (var_f31 * argA);
    if (arg8 > 180.0f) {
        return arg8 - 360.0f;
    }
    if (arg8 <= -180.0f) {
        arg8 += 360.0f;
    }
    return arg8;
}

void fn_1_4574(Mtx arg0, float arg8, float arg9, float argA)
{
    Mtx sp38;
    Mtx sp8;
    if (argA != 0.0f) {
        MTXRotRad(arg0, 0x5A, 0.017453292f * argA);
    }
    else {
        MTXIdentity(arg0);
    }
    if (arg8 != 0.0f) {
        MTXRotRad(sp38, 0x58, 0.017453292f * arg8);
        MTXConcat(sp38, arg0, arg0);
    }
    if (arg9 != 0.0f) {
        MTXRotRad(sp8, 0x59, 0.017453292f * arg9);
        MTXConcat(sp8, arg0, arg0);
    }
}
// TODO figue out type of arg0
void fn_1_4694(float *arg0, Vec *arg1)
{
    float var_f29;
    float var_f28;

    arg1->x = atan2d(arg0[10], arg0[6]);
    arg1->z = atan2d(arg0[0], arg0[1]);
    var_f29 = -arg0[2];
    var_f28 = sqrtf((1.0 - (var_f29 * var_f29)) < 0.0 ? -(1.0 - (var_f29 * var_f29)) : 1.0 - (var_f29 * var_f29));
    if ((arg1->x > 90.0f) && (arg1->x < 270.0f) && (arg1->z > 90.0f) && (arg1->z < 270.0f)) {
        arg1->x = fmod(180.0f + arg1->x, 360.0);
        arg1->z = fmod(180.0f + arg1->z, 360.0);
        var_f28 = -var_f28;
    }
    arg1->y = atan2d(var_f28, var_f29);
}

float fn_1_49A0(float arg8, float arg9, float argA, float argB)
{
    float var_f31;
    float var_f30;

    var_f31 = 1.0 - arg8;
    var_f30 = (argB * (arg8 * arg8)) + ((arg9 * (var_f31 * var_f31)) + (2.0 * (argA * (var_f31 * arg8))));
    return var_f30;
}

void fn_1_4A18(float *arg0, float *arg1, float *arg2, float *arg3, float arg8)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        *arg3 = fn_1_49A0(arg8, *arg0++, *arg1++, *arg2++);
        arg3++;
    }
}

float fn_1_4B34(float arg8, float arg9, float argA, float argB)
{
    float var_f31 = 2.0 * ((arg8 * argB) + (((arg8 - 1.0) * arg9) + ((1.0 - (2.0 * arg8)) * argA)));
    return var_f31;
}

void fn_1_4BAC(float *arg0, float *arg1, float *arg2, float *arg3, float arg8)
{
    float spC[3];
    float var_f30;
    float var_f29;

    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        spC[var_r31] = fn_1_4B34(arg8, *arg0++, *arg1++, *arg2++);
    }

    var_f30 = (spC[2] * spC[2]) + ((spC[0] * spC[0]) + (spC[1] * spC[1]));
    var_f29 = sqrtf(var_f30);
    if (var_f29) {
        var_f29 = 1.0 / var_f29;
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            *arg3 = var_f29 * spC[var_r31];
            arg3++;
        }
        return;
    }
    *arg3++ = 0.0f;
    *arg3++ = 0.0f;
    *arg3++ = 1.0f;
}

void fn_1_4E84(float *arg0, float *arg1, float *arg2, s32 arg3)
{
    float sp48[16];
    float sp8[16];
    double var_f31;

    s32 var_r31;

    arg2[0] = 0.0f;
    arg2[arg3 - 1] = 0.0f;
    for (var_r31 = 0; var_r31 < (arg3 - 1); var_r31++) {
        sp48[var_r31] = arg0[var_r31 + 1] - arg0[var_r31];
        if (sp48[var_r31] == 0.0f) {
            sp8[var_r31 + 1] = 0.0f;
        }
        else {
            sp8[var_r31 + 1] = (arg1[var_r31 + 1] - arg1[var_r31]) / sp48[var_r31];
        }
    }
    arg2[1] = sp8[2] - sp8[1];
    sp8[1] = 2.0f * (arg0[2] - arg0[0]);
    for (var_r31 = 1; var_r31 < (arg3 - 2); var_r31++) {
        var_f31 = sp48[var_r31] / sp8[var_r31];
        arg2[var_r31 + 1] = (sp8[var_r31 + 2] - sp8[var_r31 + 1]) - (var_f31 * arg2[var_r31]);
        sp8[var_r31 + 1] = (2.0f * (arg0[var_r31 + 2] - arg0[var_r31])) - (var_f31 * sp48[var_r31]);
    }
    arg2[arg3 - 2] -= sp48[arg3 - 2] * arg2[arg3 - 1];
    for (var_r31 = arg3 - 2; var_r31 > 0; var_r31--) {
        if (sp8[var_r31] == 0.0f) {
            arg2[var_r31] = 0.0f;
        }
        else {
            arg2[var_r31] = (arg2[var_r31] - (sp48[var_r31] * arg2[var_r31 + 1])) / sp8[var_r31];
        }
    }
}

float fn_1_513C(float arg8, float *arg0, float *arg1, float *arg2, s32 arg3)
{
    float var_f31;
    float var_f30;
    float var_f29;

    s32 var_r31 = arg8;
    arg8 = arg8 - var_r31;
    var_f31 = arg0[var_r31 + 1] - arg0[var_r31];
    var_f30 = var_f31 * arg8;
    var_f29 = arg1[var_r31]
        + (var_f30
            * ((var_f30 * ((3.0f * arg2[var_r31]) + ((var_f30 * (arg2[var_r31 + 1] - arg2[var_r31])) / var_f31)))
                + (((arg1[var_r31 + 1] - arg1[var_r31]) / var_f31) - (var_f31 * ((2.0f * arg2[var_r31]) + arg2[var_r31 + 1])))));
    if (var_f31 == 0.0f) {
        var_f29 = arg1[var_r31];
    }
    return var_f29;
}

void fn_1_5290(float *arg0, float (*arg1)[3], float (*arg2)[3], s32 arg3)
{
    float spD4[16];
    float sp94[16];
    float sp54[16];
    float sp14[16];
    Vec sp8;
    double var_f31;

    s32 var_r31;
    s32 var_r30;
    s32 var_r27;

    arg0[0] = 0.0f;
    for (var_r30 = 1; var_r30 < arg3; var_r30++) {
        VECSubtract((Vec *)&arg1[var_r30], (Vec *)&arg1[var_r30 - 1], &sp8);
        arg0[var_r30] = arg0[var_r30 - 1] + VECMag(&sp8);
    }
    for (var_r27 = 0; var_r27 < 3; var_r27++) {
        for (var_r30 = 0; var_r30 < arg3; var_r30++) {
            spD4[var_r30] = arg1[var_r30][var_r27];
        }
        sp94[0] = 0.0f;
        sp94[arg3 - 1] = 0.0f;
        for (var_r31 = 0; var_r31 < (arg3 - 1); var_r31++) {
            sp14[var_r31] = arg0[var_r31 + 1] - arg0[var_r31];
            if (sp14[var_r31] == 0.0f) {
                sp54[var_r31 + 1] = 0.0f;
            }
            else {
                sp54[var_r31 + 1] = (spD4[var_r31 + 1] - spD4[var_r31]) / sp14[var_r31];
            }
        }
        sp94[1] = sp54[2] - sp54[1];
        sp54[1] = 2.0f * (arg0[2] - arg0[0]);
        for (var_r31 = 1; var_r31 < (arg3 - 2); var_r31++) {
            var_f31 = sp14[var_r31] / sp54[var_r31];
            sp94[var_r31 + 1] = (sp54[var_r31 + 2] - sp54[var_r31 + 1]) - (var_f31 * sp94[var_r31]);
            sp54[var_r31 + 1] = (2.0f * (arg0[var_r31 + 2] - arg0[var_r31])) - (var_f31 * sp14[var_r31]);
        }
        sp94[arg3 - 2] -= sp14[arg3 - 2] * sp94[arg3 - 1];
        for (var_r31 = arg3 - 2; var_r31 > 0; var_r31--) {
            if (sp54[var_r31] == 0.0f) {
                sp94[var_r31] = 0.0f;
            }
            else {
                sp94[var_r31] = (sp94[var_r31] - (sp14[var_r31] * sp94[var_r31 + 1])) / sp54[var_r31];
            }
        }
        for (var_r30 = 0; var_r30 < arg3; var_r30++) {
            arg2[var_r30][var_r27] = sp94[var_r30];
        }
    }
}

void fn_1_5670(float arg8, float *arg0, float *arg1, float (*arg2)[3], float (*arg3)[3], s32 arg4)
{
    float sp48[16];
    float sp8[16];

    s32 var_r30;
    s32 var_r29;

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        for (var_r30 = 0; var_r30 < arg4; var_r30++) {
            sp48[var_r30] = arg2[var_r30][var_r29];
            sp8[var_r30] = arg3[var_r30][var_r29];
        }
        arg0[var_r29] = fn_1_513C(arg8, arg1, sp48, sp8, 3);
    }
}

float fn_1_5884(Vec *arg0)
{
    float sp8;
    float var_f30;
    float var_f29;

    var_f30 = (arg0->z * arg0->z) + ((arg0->x * arg0->x) + (arg0->y * arg0->y));
    var_f30 = sqrtf(var_f30);
    if (var_f30 != 0.0f) {
        var_f29 = 1.0f / var_f30;
        arg0->x *= var_f29;
        arg0->y *= var_f29;
        arg0->z *= var_f29;
    }
    else {
        arg0->x = arg0->y = arg0->z = 0.0f;
    }
    return var_f30;
}

float fn_1_5A1C(Vec arg0, Vec arg1, Vec *arg2, float arg8)
{
    if (arg8 <= 0.0f) {
        arg2->x = arg0.x;
        arg2->y = arg0.y;
        arg2->z = arg0.z;
        arg8 = 0.0f;
        return arg8;
    }
    if (arg8 >= 1.0f) {
        arg2->x = arg0.x + arg1.x;
        arg2->y = arg0.y + arg1.y;
        arg2->z = arg0.z + arg1.z;
        arg8 = 1.0f;
        return arg8;
    }
    arg2->x = arg0.x + (arg8 * arg1.x);
    arg2->y = arg0.y + (arg8 * arg1.y);
    arg2->z = arg0.z + (arg8 * arg1.z);
    return arg8;
}

float fn_1_5AF4(Vec arg0, Vec arg1, Vec arg2)
{
    float var_f31 = (arg2.z * (arg1.z - arg0.z)) + ((arg2.x * (arg1.x - arg0.x)) + (arg2.y * (arg1.y - arg0.y)));
    float var_f30 = -((arg2.z * arg2.z) + ((arg2.x * arg2.x) + (arg2.y * arg2.y)));
    if (var_f30 != 0.0f) {
        var_f31 /= var_f30;
    }
    return var_f31;
}

float fn_1_5BB0(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Vec sp44;
    float var_f28;

    if (((arg2->z * arg2->z) + ((arg2->x * arg2->x) + (arg2->y * arg2->y))) == 0.0f) {
        return ((arg0->z - arg1->z) * (arg0->z - arg1->z))
            + (((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)));
    }
    var_f28 = fn_1_5AF4(*arg0, *arg1, *arg2);
    fn_1_5A1C(*arg1, *arg2, &sp44, var_f28);
    return ((arg0->z - sp44.z) * (arg0->z - sp44.z)) + (((arg0->x - sp44.x) * (arg0->x - sp44.x)) + ((arg0->y - sp44.y) * (arg0->y - sp44.y)));
}

float fn_1_5EEC(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4)
{
    float var_f30;
    if (((arg2->z * arg2->z) + ((arg2->x * arg2->x) + (arg2->y * arg2->y))) == 0.0f) {
        return ((arg0->z - arg1->z) * (arg0->z - arg1->z))
            + (((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)));
    }
    var_f30 = fn_1_5AF4(*arg0, *arg1, *arg2);
    fn_1_5A1C(*arg1, *arg2, arg3, var_f30);

    arg4->x = arg3->x - arg0->x;
    arg4->y = arg3->y - arg0->y;
    arg4->z = arg3->z - arg0->z;

    return fn_1_5884(arg4);
}

s32 fn_1_639C(void)
{
    return lbl_1_bss_0;
}

s32 fn_1_63AC(void)
{
    s32 var_r31;
    omObjData **var_r30;
    M453DllWork2 *var_r29;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    for (var_r31 = 0; var_r31 < lbl_1_bss_1C; var_r31++) {
        var_r29 = var_r30[lbl_1_bss_1E[var_r31]]->data;
        if (var_r29->unk_07 != 0) {
            return 1;
        }
    }
    return 0;
}

void fn_1_6448(void)
{
    s32 var_r31;
    M453DllWork2 *var_r30;
    omObjData **var_r29;
    s32 var_r28;
    s16 var_r27;

    var_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = var_r29[var_r31]->data;
        if (var_r30->unk_07 != 0) {
            var_r27 = lbl_1_bss_0;
            var_r28 = var_r30->unk_00;
            GWPlayerCoinWinSet(var_r28, var_r27);
        }
    }
}
