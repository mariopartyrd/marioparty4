#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "string.h"

#include "REL/m456Dll.h"
#include "version.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/frand.h"
#endif

typedef struct M456DllMainWork {
    struct {
        u8 unk_00_field0 : 1;
        u8 unk_00_field1 : 1;
        u8 unk_00_field2 : 1;
        u8 unk_00_field3 : 1;
    };
    s16 unk_02;
    s16 unk_04;
    s8 unk_06;
    s8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    char unk1C[4];
    s32 unk_20;
    s32 unk_24;
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
} M456DllMainWork; /* size = 0x34 */

typedef struct M456DllData0Struct {
    /* 0x00 */ float unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
} M456DllData0Struct; /* size = 0x1C */

typedef struct M456DllData1B0Struct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ s32 unk_04;
} M456DllData1B0Struct; /* size = 0x08 */

typedef struct M456DllDataE4Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u32 unk_04;
} M456DllDataE4Struct; /* size = 0x08 */

typedef struct M456DllBss18Struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    float unk_0C;
    float unk_10;
    s32 unk_14;
    s32 unk_18;
    float unk_1C;
    s16 unk_20[0x10];
} M456DllBss18Struct; /* size 0x40 */

void fn_1_1304(omObjData *object);
void fn_1_2040(omObjData *object);
float fn_1_2090(float arg8, float arg9, float argA);
void fn_1_2194(Process *process);
void fn_1_21F8(s32 arg0, s32 arg1, float arg8);
void fn_1_2448(omObjData *object);
void fn_1_2918(Process *process);
void fn_1_2AC4(omObjData *object);
void fn_1_3C0(omObjData *object);
void fn_1_498(omObjData *);
void fn_1_BE4(omObjData *);
void fn_1_C40(Process *process);
void fn_1_CC4(void);
s32 fn_1_D2C(void);
s32 fn_1_F4C(void);
void fn_1_FD0(omObjData *object);

M456DllData0Struct lbl_1_data_0[2] = {
    { 500.0f, 0.0f, 1000.0f, 0.0f, 40.0f, 0.0f, 0.0f },
    { 1985.0f, 0.0f, 100.0f, 100.0f, -13.0f, 0.0f, 0.0f },
};
Vec lbl_1_data_38 = { 700.0f, 2500.0f, -700.0f };
Vec lbl_1_data_44 = { 0.0f, 0.0f, 0.0f };
GXColor lbl_1_data_50 = { 0xFF, 0xFF, 0xFF, 0xFF };
Vec lbl_1_data_54 = { 200.0f, 15000.0f, -200.0f };
Vec lbl_1_data_60 = { 0.0f, 1.0f, 0.0f };

omObjData *lbl_1_bss_8C;
omObjData *lbl_1_bss_88;
omObjData *lbl_1_bss_84;
s32 lbl_1_bss_80;
s32 lbl_1_bss_70[4];
s32 lbl_1_bss_6C;
s32 lbl_1_bss_68;
s32 lbl_1_bss_64;
s16 lbl_1_bss_62;
s16 lbl_1_bss_60;
u32 lbl_1_bss_5C;
u32 lbl_1_bss_58;
M456DllBss18Struct lbl_1_bss_18;
u32 lbl_1_bss_14;
Vec lbl_1_bss_8;
s16 lbl_1_bss_6;
s16 lbl_1_bss_4;
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    Process *var_r31;
    CameraData *var_r30;
    s16 var_r29;

    var_r30 = Hu3DCamera;
    OSReport("******* M456ObjectSetup *********\n");
    var_r31 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(var_r31);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, -1.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lbl_1_bss_88 = omAddObjEx(var_r31, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_8.x = lbl_1_data_44.x - lbl_1_data_38.x;
    lbl_1_bss_8.y = lbl_1_data_44.y - lbl_1_data_38.y;
    lbl_1_bss_8.z = lbl_1_data_44.z - lbl_1_data_38.z;
    VECNormalize(&lbl_1_bss_8, &lbl_1_bss_8);
    var_r29 = Hu3DGLightCreateV(&lbl_1_data_38, &lbl_1_bss_8, &lbl_1_data_50);
    Hu3DGLightInfinitytSet(var_r29);
    Hu3DGLightStaticSet(var_r29, 1);
    Hu3DShadowCreate(10.0f, var_r30->nnear, var_r30->ffar);
    Hu3DShadowTPLvlSet(0.7f);
    Hu3DShadowPosSet(&lbl_1_data_54, &lbl_1_data_60, &lbl_1_data_44);
    HuAudSndGrpSet(0x4E);
    lbl_1_bss_84 = omAddObjEx(var_r31, 0, 0, 0, -1, fn_1_3C0);
    fn_1_2194(var_r31);
    fn_1_C40(var_r31);
    fn_1_2DF4(var_r31);
    lbl_1_bss_5C = GWMGRecordGet(0xA);
    if (lbl_1_bss_5C == 0) {
        lbl_1_bss_5C = 5 * REFRESH_RATE;
    }
    lbl_1_bss_58 = 0;
    fn_1_2918(var_r31);
    lbl_1_bss_18.unk_14 = lbl_1_bss_5C;
    lbl_1_bss_18.unk_00 = 1;
    lbl_1_bss_18.unk_0C = 536.0f;
}

s32 lbl_1_data_90 = -1;
s32 lbl_1_data_94 = -1;

void fn_1_3A0(u32 arg0)
{
    lbl_1_bss_80 = arg0;
}

s32 fn_1_3B0(void)
{
    return lbl_1_bss_80;
}

void fn_1_3C0(omObjData *object)
{
    CameraData *var_r31 = Hu3DCamera;
    fn_1_3A0(0);
    lbl_1_bss_6C = REFRESH_RATE;
    lbl_1_bss_70[0] = lbl_1_bss_70[1] = lbl_1_bss_70[2] = lbl_1_bss_70[3] = -1;
    lbl_1_bss_62 = 5;
    lbl_1_bss_60 = REFRESH_RATE;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 0x3C);
    var_r31->fov = 30.0f;
    object->func = fn_1_498;
}

void fn_1_498(omObjData *object)
{
    s16 sp8[4];

    s32 var_r31;
    omObjData **var_r29;
    M456DllMainWork *var_r28;

    switch (fn_1_3B0()) {
        case 0:
            if (lbl_1_data_94 < 0) {
                lbl_1_data_94 = HuAudFXPlay(0x7D1);
            }
            if (--lbl_1_bss_6C == 0) {
                fn_1_3A0(1);
                lbl_1_bss_6C = 2 * REFRESH_RATE;
            }
            break;
        case 1:
            if (--lbl_1_bss_6C == 0) {
                fn_1_3A0(2);
                lbl_1_bss_6 = MGSeqCreate(3, 0);
            }
            break;
        case 2:
            if (MGSeqStatGet(lbl_1_bss_6) == 0) {
                fn_1_3A0(3);
                lbl_1_bss_4 = MGSeqCreate(1, 5, -1, -1);
            }
            if ((lbl_1_data_90 < 0) && ((MGSeqStatGet(lbl_1_bss_6) & 0x10) != 0)) {
                lbl_1_data_90 = HuAudSeqPlay(0x43);
            }
            break;
        case 3:
            if (--lbl_1_bss_60 == 0) {
                lbl_1_bss_62--;
                MGSeqParamSet(lbl_1_bss_4, 1, lbl_1_bss_62);
                lbl_1_bss_60 = REFRESH_RATE;
            }
            if (lbl_1_bss_62 == 0) {
                lbl_1_bss_64 = fn_1_D2C();
                if (lbl_1_bss_64 == 0) {
                    fn_1_3A0(5);
                    lbl_1_bss_6 = MGSeqCreate(3, 1);
                    HuAudSeqFadeOut(lbl_1_data_90, 0x64);
                }
                else {
                    fn_1_3A0(4);
                    HuAudFXPlay(0x11);
                    lbl_1_bss_6C = 2 * REFRESH_RATE;
                }
            }
            break;
        case 4:
            if (lbl_1_bss_4 >= 0) {
                MGSeqParamSet(lbl_1_bss_4, 2, -1);
                lbl_1_bss_4 = -1;
            }
            if (lbl_1_bss_6C != 0) {
                lbl_1_bss_6C--;
            }
            else if (lbl_1_bss_18.unk_18 < lbl_1_bss_14) {
                lbl_1_bss_18.unk_18++;
            }
            if (fn_1_F4C() != 0) {
                fn_1_3A0(5);
                lbl_1_bss_6 = MGSeqCreate(3, 1);
                HuAudSeqFadeOut(lbl_1_data_90, 0x64);
            }
            break;
        case 5:
            if (lbl_1_bss_4 >= 0) {
                MGSeqParamSet(lbl_1_bss_4, 2, -1);
                lbl_1_bss_4 = -1;
            }
            if (MGSeqStatGet(lbl_1_bss_6) == 0) {
                if (lbl_1_bss_58 == 0) {
                    fn_1_3A0(9);
                    lbl_1_bss_6C = 2 * REFRESH_RATE;
                }
                else {
                    fn_1_3A0(6);
                    lbl_1_bss_6 = MGSeqCreate(0xE, lbl_1_bss_58);
                    GWMGRecordSet(0xA, lbl_1_bss_58);
                    lbl_1_bss_18.unk_04 = 1;
                    lbl_1_bss_18.unk_14 = lbl_1_bss_18.unk_18;
                }
            }
            break;
        case 6:
            if (MGSeqStatGet(lbl_1_bss_6) == 0) {
                fn_1_3A0(9);
                lbl_1_bss_6C = 2 * REFRESH_RATE;
            }
            break;
        case 9:
            if (lbl_1_bss_6C != 0) {
                lbl_1_bss_6C--;
            }
            if (lbl_1_bss_6C == 0) {
                if (fn_1_F4C() != 0) {
                    fn_1_3A0(0xB);
                    if (lbl_1_bss_64 != 0) {
                        var_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
                        for (var_r31 = 0; var_r31 < lbl_1_bss_64; var_r31++) {
                            var_r28 = var_r29[lbl_1_bss_70[var_r31]]->data;
                            sp8[var_r31] = var_r28->unk_14;
                            GWPlayerCoinWinSet(lbl_1_bss_70[var_r31], 10);
                        }
                        for (; var_r31 < 4; var_r31++) {
                            sp8[var_r31] = -1;
                        }
                        lbl_1_bss_6 = MGSeqCreate(5, 3, sp8[0], sp8[1], sp8[2], sp8[3]);
                        HuAudSStreamPlay(1);
                    }
                    else {
                        lbl_1_bss_6 = MGSeqCreate(3, 2);
                        HuAudSStreamPlay(4);
                    }
                    lbl_1_bss_6C = 3.5 * REFRESH_RATE;
                }
            }
            break;
        case 11:
            if (--lbl_1_bss_6C == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
                HuAudFXStop(lbl_1_data_94);
                object->func = fn_1_BE4;
            }
            break;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
        object->func = fn_1_BE4;
    }
}

void fn_1_BE4(omObjData *object)
{
    if (WipeStatGet() == 0) {
        fn_1_CC4();
        fn_1_2F3C();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
        OSReport("******* M456Exit *********\n");
    }
}

void fn_1_C40(Process *process)
{
    s32 var_r31;

    lbl_1_bss_68 = 0;
    omMakeGroupEx(process, 0, 4);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        omAddObjEx(process, 5, 0xA, 0x32, 0, fn_1_FD0);
    }
}

void fn_1_CC4(void)
{
    s32 var_r31;
    omObjData **var_r30;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    if (var_r30 != NULL) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            fn_1_2040(var_r30[var_r31]);
        }
    }
}

s32 fn_1_D2C(void)
{
    s32 sp8[4];

    s32 var_r31;
    M456DllMainWork *var_r30;
    s32 var_r29;
    u32 var_r28;
    omObjData **var_r27;

    var_r29 = 0;
    var_r28 = 0;
    var_r27 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = var_r27[var_r31]->data;
        if ((var_r30->unk_30 != 0) && (var_r30->unk_30 < 5)) {
            var_r30->unk_30 = 5;
        }
        if (var_r30->unk_30 > var_r28) {
            var_r28 = var_r30->unk_30;
            var_r29 = 0;
            sp8[var_r29++] = var_r31;
        }
        else if (var_r30->unk_30 == var_r28) {
            sp8[var_r29++] = var_r31;
        }
    }
    if (var_r28 == 0) {
        lbl_1_bss_70[var_r31] = -1;
        return 0;
    }
    lbl_1_bss_14 = (var_r28 * REFRESH_RATE) / 5;
    for (var_r31 = 0; var_r31 < var_r29; var_r31++) {
        if (GWPlayerCfg[sp8[var_r31]].iscom == 0) {
            break;
        }
    }
    if (var_r31 < var_r29) {
        if (lbl_1_bss_14 > lbl_1_bss_5C) {
            lbl_1_bss_58 = lbl_1_bss_14;
        }
        if (lbl_1_bss_14 >= 7.5f * REFRESH_RATE) {
            GWGameStat.present[0x33] = 1;
        }
    }
    for (var_r31 = 0; var_r31 < var_r29; var_r31++) {
        lbl_1_bss_70[var_r31] = sp8[var_r31];
    }
    return var_r29;
}

s32 fn_1_F4C(void)
{
    s32 var_r31;
    omObjData **var_r30;
    M456DllMainWork *var_r29;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = var_r30[var_r31]->data;
        if (var_r29->unk_00_field2 == 0) {
            return 0;
        }
    }
    return 1;
}

M456DllDataE4Struct lbl_1_data_E4[0xA] = {
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00), 0 },
    { DATA_MAKE_NUM(DATADIR_M456, 0x1C), 1 },
    { DATA_MAKE_NUM(DATADIR_M456, 0x24), 1 },
    { DATA_MAKE_NUM(DATADIR_M456, 0x2C), 1 },
    { DATA_MAKE_NUM(DATADIR_M456, 0x34), 1 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2A), 0 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05), 0 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17), 0 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18), 0 },
    { DATA_MAKE_NUM(DATADIR_M456, 0x3C), 1 },
};
Vec lbl_1_data_134[4] = {
    { -300.0f, 0.0f, 0.0f },
    { -100.0f, 0.0f, 0.0f },
    { 100.0f, 0.0f, 0.0f },
    { 300.0f, 0.0f, 0.0f },
};
float lbl_1_data_164[8] = { -50.0f, -50.0f, -50.0f, -50.0f, -50.0f, -50.0f, -50.0f, -50.0f };
u16 lbl_1_data_184[2] = { 0x40, 0x20 };

void fn_1_FD0(omObjData *object)
{
    M456DllMainWork *var_r31;
    u32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M456DllMainWork), MEMORY_DEFAULT_NUM);
    object->data = var_r31;
    memset(var_r31, 0, sizeof(M456DllMainWork));
    var_r31->unk_02 = lbl_1_bss_68++;
    var_r31->unk_04 = GWPlayerCfg[var_r31->unk_02].pad_idx;
    var_r27 = GWGameStat.rumble;
    var_r31->unk_10 = var_r27;
    var_r28 = GWPlayerCfg[var_r31->unk_02].character;
    var_r31->unk_14 = var_r28;
    var_r31->unk_16 = GWPlayerCfg[var_r31->unk_02].diff;
    var_r31->unk_18 = GWPlayerCfg[var_r31->unk_02].group;
    var_r31->unk_0C = -1;
    object->model[0] = CharModelCreate(var_r28, 8);
    Hu3DModelShadowSet(object->model[0]);
    Hu3DModelLayerSet(object->model[0], 3);
    Hu3DModelCameraSet(object->model[0], 1);
    var_r31->unk_20 = 0;
    for (var_r29 = 0; var_r29 < 0xA; var_r29++) {
        if (lbl_1_data_E4[var_r29].unk_04 == 0) {
            object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_14, lbl_1_data_E4[var_r29].unk_00);
        }
        else {
            object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_14, var_r31->unk_14 + lbl_1_data_E4[var_r29].unk_00);
        }
    }
    Hu3DMotionSet(object->model[0], object->motion[var_r31->unk_20]);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    CharModelVoiceEnableSet(var_r31->unk_14, object->motion[5], 0);
    CharModelVoiceEnableSet(var_r31->unk_14, object->motion[6], 0);
    var_r31->unk_2E = REFRESH_RATE;
    object->trans.x = lbl_1_data_134[var_r31->unk_02].x;
    object->trans.y = lbl_1_data_134[var_r31->unk_02].y;
    object->trans.z = lbl_1_data_134[var_r31->unk_02].z;
    object->rot.y = 0.0f;
    CharModelDataClose(var_r31->unk_14);
    object->func = fn_1_1304;
}

#if VERSION_PAL
#define fn_1_1288_COND (((var_r31->unk_16 + 4) * 60) / 50.0f)
#else
#define fn_1_1288_COND (var_r31->unk_16 + 4)
#endif

void fn_1_1288(omObjData *object)
{
    M456DllMainWork *var_r31 = object->data;

    if ((frand() & 0x3F) < fn_1_1288_COND) {
        if (var_r31->unk_0C <= 0) {
            var_r31->unk_0A |= 0x40;
            return;
        }
        var_r31->unk_0A |= 0x20;
    }
}

void fn_1_1304(omObjData *var_r30)
{
    Vec sp14;
    Vec sp8;
    float var_f31;

    M456DllMainWork *var_r31;
    s32 var_r29;
    u32 var_r28;
    void *var_r27;
    s32 var_r26;
    omObjData **var_r25;
    s32 var_r24;

    var_r31 = var_r30->data;
    var_r29 = var_r31->unk_20;
    var_r28 = var_r31->unk_24;
    if (var_r31->unk_00_field0 == 0) {
        var_r30->trans.y = fn_1_63AC();
    }
    if (fn_1_3B0() < 3) {
        return;
    }
    switch (var_r31->unk_1A) {
        case 0:
            if (fn_1_3B0() == 5) {
                var_r31->unk_00_field2 = 1;
                var_r31->unk_1A = 6;
                return;
            }
            if (fn_1_3B0() == 4) {
                if (var_r31->unk_30 != 0) {
                    var_r31->unk_1A = 1;
                    var_r31->unk_28 = REFRESH_RATE;
                }
                else {
                    var_r31->unk_1A = 6;
                    var_r31->unk_00_field2 = 1;
                }
                return;
            }
            if (GWPlayerCfg[var_r31->unk_02].iscom == 0) {
                var_r31->unk_06 = HuPadStkX[var_r31->unk_04];
                var_r31->unk_07 = HuPadStkY[var_r31->unk_04];
                var_r31->unk_08 = HuPadBtn[var_r31->unk_04];
                var_r31->unk_0A = HuPadBtnDown[var_r31->unk_04] & 0xFFFF9FFF;
            }
            else {
                var_r31->unk_08 = var_r31->unk_0A = 0;
                var_r31->unk_06 = var_r31->unk_07 = 0;
                fn_1_1288(var_r30);
            }
            if (var_r31->unk_2C != 0) {
                if (--var_r31->unk_2C == 0) {
                    var_r29 = 0;
                    var_r28 = 0x40000001;
                }
            }
            if ((var_r31->unk_0A & 0x60) != 0) {
                if (var_r31->unk_0C < 0) {
                    var_r31->unk_0C = (var_r31->unk_0A & 0x40) ? 0 : 1;
                }
                if (((var_r31->unk_0A & lbl_1_data_184[var_r31->unk_0C]) != 0) && ((var_r31->unk_0A & ~lbl_1_data_184[var_r31->unk_0C]) == 0)) {
                    var_r31->unk_30++;
                    var_r31->unk_2C = var_r31->unk_2E;
                    var_r29 = 1;
                    var_r28 = 0x40000001;
                    var_r31->unk_0C ^= 1;
                }
            }
            break;
        case 1:
            if (--var_r31->unk_28 == 0) {
                var_r31->unk_00_field0 = 1;
                var_r31->unk_1A = 2;
                var_r31->unk_28 = var_r31->unk_2A = REFRESH_RATE;
            }
            var_r29 = 2;
            var_r28 = 0;
            break;
        case 2:
            var_r29 = 3;
            var_r28 = 0;
            if (var_r31->unk_28 < (var_r31->unk_2A - 0xF)) {
                var_f31 = (float)var_r31->unk_28 / (var_r31->unk_2A - 0xF);
                var_r30->trans.y = -300.0 * cosd((270.0f * var_f31));
                var_r30->trans.z = 400.0f + (-400.0f * var_f31);
                if ((var_r31->unk_00_field1 == 0) && (var_f31 < 0.35f)) {
                    var_r31->unk_00_field1 = 1;
                    fn_1_67E0(&var_r30->trans, -1.0f);
                    fn_1_61C8(&var_r30->trans, -1.0f, -1.0f, -1);
                    fn_1_7F78();
                    HuAudFXPlay(0x7D2);
                }
            }
            if (--var_r31->unk_28 == 0) {
                var_r30->trans.y = -300.0f;
                var_r30->trans.z = 400.0f;
                var_r31->unk_1A = 3;
                var_r31->unk_28 = (var_r31->unk_30 * REFRESH_RATE) / 5;
                for (var_r26 = 0; var_r26 < lbl_1_bss_64; var_r26++) {
                    if (var_r31->unk_02 == lbl_1_bss_70[var_r26]) {
                        break;
                    }
                }
                if (var_r26 < lbl_1_bss_64) {
                    var_r31->unk_00_field3 = 1;
                    var_r31->unk_28 -= VERSION_PAL ? 16.5f : 19.800001f;
                }
                else {
                    var_r31->unk_28 -= 0.8f * REFRESH_RATE;
                }
                var_r31->unk_2A = var_r31->unk_28;
            }
            break;
        case 3:
            var_r29 = 5;
            var_r28 = 0x40000001;
            if (var_r31->unk_28 < 1.0f * REFRESH_RATE) {
                if ((frand() & 3) == 0) {
                    sp14.x = var_r30->trans.x;
                    sp14.y = 100.0f + var_r30->trans.y;
                    sp14.z = var_r30->trans.z;
                    fn_1_74F8(&sp14, -1.0f);
                }
            }
            else if ((frand() & 0xF) == 0) {
                sp14.x = var_r30->trans.x;
                sp14.y = 100.0f + var_r30->trans.y;
                sp14.z = var_r30->trans.z;
                fn_1_74F8(&sp14, -1.0f);
            }
            if (--var_r31->unk_28 == 0) {
                var_r31->unk_00_field1 = 0;
                if (var_r31->unk_00_field3 == 0) {
                    var_r31->unk_1A = 4;
                    var_r31->unk_28 = var_r31->unk_2A = REFRESH_RATE / 1.25;
                }
                else {
                    var_r31->unk_1A = 5;
                    var_r31->unk_28 = var_r31->unk_2A = REFRESH_RATE;
                }
            }
            break;
        case 4:
            var_r29 = 4;
            var_r28 = 0x40000001;
            var_f31 = (float)var_r31->unk_28 / var_r31->unk_2A;
            var_r30->trans.y = -300.0 * sind((90.0f * var_f31));
            if ((frand() & 3) == 0) {
                fn_1_74F8(&var_r30->trans, -1.0f);
            }
            if ((var_r31->unk_00_field1 == 0) && (var_f31 < 0.2f)) {
                var_r31->unk_00_field1 = 1;
                fn_1_67E0(&var_r30->trans, -1.0f);
                fn_1_61C8(&var_r30->trans, -1.0f, -1.0f, -1);
                HuAudFXPlay(0x7D3);
            }
            if (--var_r31->unk_28 == 0) {
                var_r31->unk_00_field2 = 1;
                var_r31->unk_1A = 6;
                var_r30->trans.y = lbl_1_data_164[var_r31->unk_14];
            }
            break;
        case 5:
            var_r29 = 6;
            var_r28 = 0;
            var_f31 = (float)var_r31->unk_28 / var_r31->unk_2A;
            var_r30->trans.y = -300.0 * -sind((270.0f * var_f31));
            if ((var_r31->unk_00_field1 == 0) && (var_f31 < 0.7f)) {
                var_r31->unk_00_field1 = 1;
                fn_1_67E0(&var_r30->trans, 5.0f);
                fn_1_61C8(&var_r30->trans, -1.0f, -1.0f, -1);
                HuAudFXPlay(0x7D3);
                HuAudCharVoicePlay(var_r31->unk_14, 0x125);
            }
            if (--var_r31->unk_28 == 0) {
                var_r31->unk_00_field2 = 1;
                var_r31->unk_1A = 6;
                var_r30->trans.y = lbl_1_data_164[var_r31->unk_14];
                fn_1_67E0(&var_r30->trans, -1.0f);
                fn_1_61C8(&var_r30->trans, -1.0f, -1.0f, -1);
            }
            break;
        case 6:
            if (var_r31->unk_00_field0 == 0) {
                var_r29 = 0;
            }
            else {
                var_r29 = 5;
            }
            var_r28 = 0x40000001;
            if ((fn_1_3B0() == 5) && (var_r31->unk_00_field3 == 0) && (lbl_1_bss_64 == 1)) {
                var_r25 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
                VECSubtract(&var_r25[*lbl_1_bss_70]->trans, &var_r30->trans, &sp8);
                var_r30->rot.y = fn_1_2090(var_r30->rot.y, atan2d(sp8.x, sp8.z), 0.1f);
            }
            if (fn_1_3B0() == 0xB) {
                var_r31->unk_1A = 7;
                if (var_r31->unk_00_field3 != 0) {
                    Hu3DMotionOverlaySet(var_r30->model[0], var_r30->motion[9]);
                    HuAudCharVoicePlay(var_r31->unk_14, 0x124);
                }
            }
            break;
        case 7:
            if (var_r31->unk_00_field3 != 0) {
                var_r29 = 5;
                var_r28 = 0x40000001;
                if (73.0f <= Hu3DMotionOverlayTimeGet(var_r30->model[0])) {
                    Hu3DMotionOverlayTimeSet(var_r30->model[0], 35.0f);
                    Hu3DModelAttrReset(var_r30->model[0], HU3D_MOTATTR_OVL_PAUSE);
                }
            }
            else if (var_r31->unk_00_field0 == 0) {
                var_r29 = 8;
                var_r28 = 0;
            }
            break;
    }
    if ((var_r31->unk_00_field0 != 0) && (var_r31->unk_1A >= 6) && (var_r31->unk_1A <= 7) && ((frand() & 0x3F) == 0)) {
        fn_1_61C8(&var_r30->trans, 0.3f, -1.0f, -1);
    }
    if ((var_r29 != var_r31->unk_20) || (var_r28 != var_r31->unk_24)) {
        var_r31->unk_20 = var_r29;
        var_r31->unk_24 = var_r28;
        CharModelMotionShiftSet(var_r31->unk_14, var_r30->motion[var_r31->unk_20], 0.0f, 8.0f, var_r28);
    }
}

void fn_1_2040(omObjData *object)
{
    M456DllMainWork *sp8 = object->data;
    if (object->data != NULL) {
        HuMemDirectFree(object->data);
        object->data = NULL;
    }
}

float fn_1_2090(float var_f29, float sp8, float spC)
{
    float var_f31;
    float var_f30;

    var_f31 = fmod(sp8 - var_f29, 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(var_f29 + (spC * var_f31), 360.0);
    if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

void fn_1_2194(Process *process)
{
    fn_1_21F8(0, 0, 0.0f);
    lbl_1_bss_8C = omAddObjEx(process, 0xA, 0, 0, -1, fn_1_2448);
}

void fn_1_21F8(s32 arg0, s32 arg1, float arg8)
{
    CZoom = lbl_1_data_0[arg0].unk_00 + (arg8 * (lbl_1_data_0[arg1].unk_00 - lbl_1_data_0[arg0].unk_00));
    Center.x = lbl_1_data_0[arg0].unk_04 + (arg8 * (lbl_1_data_0[arg1].unk_04 - lbl_1_data_0[arg0].unk_04));
    Center.y = lbl_1_data_0[arg0].unk_08 + (arg8 * (lbl_1_data_0[arg1].unk_08 - lbl_1_data_0[arg0].unk_08));
    Center.z = lbl_1_data_0[arg0].unk_0C + (arg8 * (lbl_1_data_0[arg1].unk_0C - lbl_1_data_0[arg0].unk_0C));
    CRot.x = lbl_1_data_0[arg0].unk_10 + (arg8 * (lbl_1_data_0[arg1].unk_10 - lbl_1_data_0[arg0].unk_10));
    CRot.y = lbl_1_data_0[arg0].unk_14 + (arg8 * (lbl_1_data_0[arg1].unk_14 - lbl_1_data_0[arg0].unk_14));
    CRot.z = lbl_1_data_0[arg0].unk_18 + (arg8 * (lbl_1_data_0[arg1].unk_18 - lbl_1_data_0[arg0].unk_18));
}

float lbl_1_data_1A8[2] = { 0.0f, 0.0f };

void fn_1_2448(omObjData *object)
{
    CameraData *sp8 = Hu3DCamera;

    switch (fn_1_3B0()) {
        case 1:
            fn_1_21F8(0, 1, sind((90.0f * lbl_1_data_1A8[0])));
            if (lbl_1_data_1A8[0] < 1.0f) {
                lbl_1_data_1A8[0] += 1.0f / REFRESH_RATE;
                if (lbl_1_data_1A8[0] > 1.0f) {
                    lbl_1_data_1A8[0] = 1.0f;
                    break;
                }
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        case 8:
            fn_1_21F8(1, 1, 0.0f);
            break;
        case 9:
            break;
    }
}

M456DllData1B0Struct lbl_1_data_1B0[0x10] = {
    { DATA_MAKE_NUM(DATADIR_M456, 0x44), 0x10E },
    { 0x610037, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610030, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
    { 0x610031, 0xFA },
};

Vec2f lbl_1_data_230[0x17] = {
    { 0.0f, 0.0f },
    { -52.0f, -9.0f },
    { 53.0f, -8.0f },
    { 35.0f, -8.0f },
    { 9.0f, -8.0f },
    { -9.0f, -8.0f },
    { -31.0f, -8.0f },
    { 23.0f, -8.0f },
    { -17.0f, -8.0f },
    { 53.0f, 8.0f },
    { 35.0f, 8.0f },
    { 9.0f, 8.0f },
    { -9.0f, 8.0f },
    { -31.0f, 8.0f },
    { 23.0f, 8.0f },
    { -17.0f, 8.0f },
    { 355.0f, 0.0f },
    { 0.0f, 0.0f },
    { 275.0f, 128.0f },
    { 950.0f, 6.0f },
    { 0.0f, 0.0f },
    { 0.0f, 190.0f },
    { 0.0f, 550.0f },
};

void fn_1_2918(Process *sp8)
{
    M456DllBss18Struct *var_r31;
    s32 var_r30;
    omObjData *var_r29;

    var_r29 = omAddObjEx(sp8, 0x7FD9, 0, 0, -1, fn_1_2AC4);
    var_r31 = &lbl_1_bss_18;
    var_r29->data = var_r31;
    memset(var_r31, 0, sizeof(M456DllBss18Struct));
    var_r31->unk_14 = 60 * REFRESH_RATE;
    var_r31->unk_0C = 320.0f;
    var_r31->unk_10 = 64.0f;
    var_r31->unk_1C = 1.0f;
    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        var_r31->unk_20[var_r30] = -1;
        if (lbl_1_data_1B0[var_r30].unk_00 != 0) {
            var_r31->unk_20[var_r30] = espEntry(lbl_1_data_1B0[var_r30].unk_00, lbl_1_data_1B0[var_r30].unk_04, 0);
            espAttrSet(var_r31->unk_20[var_r30], HUSPR_ATTR_LINEAR);
            espDispOff(var_r31->unk_20[var_r30]);
        }
    }
    espColorSet(var_r31->unk_20[0], 0, 0, 0);
    espTPLvlSet(var_r31->unk_20[0], 0.699999988079071);
    espBankSet(var_r31->unk_20[7], 0xB);
    espBankSet(var_r31->unk_20[8], 0xA);
    espBankSet(var_r31->unk_20[14], 0xB);
    espBankSet(var_r31->unk_20[15], 0xA);
}

void fn_1_2AC4(omObjData *var_r26)
{
    u32 sp8[3];

    M456DllBss18Struct *var_r31;
    s32 var_r30;
    u32 var_r29;
    s32 var_r28;
    s32 var_r27;

    var_r31 = var_r26->data;
    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        if (var_r31->unk_20[var_r30] >= 0) {
            if (var_r31->unk_00 == 0) {
                espDispOff(var_r31->unk_20[var_r30]);
            }
            else {
                espDispOn(var_r31->unk_20[var_r30]);
                espPosSet(
                    var_r31->unk_20[var_r30], 0.9f * (var_r31->unk_0C + lbl_1_data_230[var_r30].x), var_r31->unk_10 + lbl_1_data_230[var_r30].y);
            }
        }
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        if (var_r30 != 0) {
            var_r29 = var_r31->unk_18;
            var_r27 = 9;
        }
        else {
            var_r29 = var_r31->unk_14;
            var_r27 = 2;
        }
        sp8[0] = var_r29 % REFRESH_RATE;
        var_r29 = (var_r29 - sp8[0]) / REFRESH_RATE;
#if VERSION_PAL
        sp8[0] = 100.0f * (sp8[0] / (float)REFRESH_RATE);
#else
        sp8[0] = 100.0f * (1.0f / REFRESH_RATE * sp8[0]);
#endif
        sp8[1] = var_r29 % 60;
        var_r29 = (var_r29 - sp8[1]) / 60;
        sp8[2] = var_r29;
        for (var_r28 = 0; var_r28 < 3; var_r28++) {
            espBankSet(var_r31->unk_20[var_r27++], sp8[var_r28] % 10);
            if (var_r28 < 2) {
                espBankSet(var_r31->unk_20[var_r27++], sp8[var_r28] / 10);
            }
        }
    }
    if (var_r31->unk_04 != 0) {
        if (var_r31->unk_08 == 0) {
            if ((var_r31->unk_1C += 0.02f) >= 1.2f) {
                var_r31->unk_1C = 1.2f;
                var_r31->unk_08 = 1;
            }
        }
        else {
            if ((var_r31->unk_1C -= 0.04f) <= 1.0f) {
                var_r31->unk_1C = 1.0f;
                var_r31->unk_08 = 0;
            }
        }
        for (var_r30 = 1; var_r30 < 9; var_r30++) {
            espScaleSet(var_r31->unk_20[var_r30], var_r31->unk_1C, var_r31->unk_1C);
        }
    }
}
