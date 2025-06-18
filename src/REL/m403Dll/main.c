#include "REL/executor.h"
#include "REL/m403Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "ext_math.h"
#include <string.h>

#ifndef __MWERKS__
#include "game/esprite.h"
#endif

typedef struct {
    /* 0x000 */ u8 unk00;
    /* 0x001 */ char unk01[3];
    /* 0x004 */ Vec unk04;
    /* 0x010 */ Vec unk10;
    /* 0x01C */ Vec unk1C;
    /* 0x028 */ Vec unk28;
    /* 0x034 */ Vec unk34;
    /* 0x040 */ Vec unk40;
    /* 0x04C */ Vec unk4C;
    /* 0x058 */ Vec unk58;
    /* 0x064 */ Vec unk64;
    /* 0x070 */ Vec unk70;
    /* 0x07C */ Vec unk7C;
    /* 0x088 */ float unk88[3][3];
    /* 0x0AC */ Vec unkAC;
    /* 0x0B8 */ Vec unkB8;
    /* 0x0C4 */ Vec unkC4;
    /* 0x0D0 */ float unkD0[3][3];
    /* 0x0F4 */ float unkF4[3];
    /* 0x100 */ float unk100[3];
    /* 0x10C */ float unk10C[3];
    /* 0x118 */ float unk118[3];
    /* 0x124 */ float unk124[3];
    /* 0x130 */ float unk130;
    /* 0x134 */ float unk134;
    /* 0x138 */ float unk138;
    /* 0x13C */ float unk13C;
    /* 0x140 */ float unk140;
    /* 0x144 */ float unk144;
    /* 0x148 */ float unk148;
} Unkm403Struct_00; // Size 0x14C

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ char unk08[2];
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ char unk0B[1];
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 unk0D;
    /* 0x0E */ u8 unk0E;
    /* 0x0F */ char unk0F[1];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ Vec unk2C;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ float unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ s16 unk5C; // Start of a struct of size 0x40 (memset)?
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ float unk60;
    /* 0x64 */ float unk64;
    /* 0x68 */ char unk68[0x34];
    /* 0x9C */ u8 unk9C;
    /* 0x9D */ char unk9D[3];
    /* 0xA0 */ s32 unkA0;
} Unkm403Struct_01; // Size 0xA4

static void fn_1_424(omObjData *arg0);
static void fn_1_444(omObjData *arg0);
static void fn_1_82C(omObjData *arg0);
static void fn_1_1214(omObjData *arg0);
static void fn_1_1274(omObjData *arg0);
static void fn_1_1460(omObjData *arg0);
static void fn_1_16D8(omObjData *arg0);
static void fn_1_17DC(omObjData *arg0);
static void fn_1_1A50(float arg0, Vec *arg1, Vec *arg2, float arg3);
static void fn_1_1AF0(float arg0, Vec *arg1, Vec *arg2, float arg3, Vec *arg4, Vec *arg5, float arg6);
static void fn_1_1DA8(float arg0);
static void fn_1_1DD0(omObjData *arg0);
static void fn_1_2158(omObjData *arg0);
static void fn_1_22A4(omObjData *arg0);
static void fn_1_2598(omObjData *arg0);
static void fn_1_2FDC(omObjData *arg0);
static void fn_1_3800(void);
static s32 fn_1_3894(void);
static void fn_1_3B80(omObjData *arg0);
static void fn_1_3D6C(Vec *arg0, Vec *arg1);
static void fn_1_3E4C(omObjData *arg0);
static s16 fn_1_400C(s32 arg0, s16 arg1, ParticleHook arg2);
static void fn_1_40A8(ModelData *model, ParticleData *particle, Mtx matrix);
static s32 fn_1_4528(void);
static float fn_1_457C(float arg0, float arg1, float arg2);
static void fn_1_46E4(Mtx arg0, float arg1, float arg2, float arg3);
static void fn_1_4804(float *arg0, float *arg1);
static float fn_1_4B10(float arg0, float arg1, float arg2, float arg3);
static void fn_1_4B88(float *arg0, float *arg1, float *arg2, float *arg3, float arg4);
static float fn_1_4CA4(float arg0, float arg1, float arg2, float arg3);
static void fn_1_4D1C(float *arg0, float *arg1, float *arg2, float *arg3, float arg4);
static void fn_1_4FF4(float *arg0, float *arg1, float *arg2, s32 arg3);
static float fn_1_52AC(float arg0, float *arg1, float *arg2, float *arg3, s32 arg4);
static void fn_1_5400(float *arg0, Vec *arg1, float arg2[][3], s32 arg3);
static void fn_1_57E0(float arg0, Vec *arg1, float *arg2, Vec *arg3, float arg4[][3], s32 arg5);
static float fn_1_59F4(Vec *arg0);
static void fn_1_5B8C(Vec arg0, Vec arg1, Vec *arg2, float arg3);
static float fn_1_5C64(Vec arg0, Vec arg1, Vec arg2);
static float fn_1_5D20(Vec *arg0, Vec *arg1, Vec *arg2);
static float fn_1_605C(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4);

static omObjData *lbl_1_bss_50;
static omObjData *lbl_1_bss_4C;
static omObjData *lbl_1_bss_48;
static omObjData *lbl_1_bss_44;
static omObjData *lbl_1_bss_34[4];
static u16 lbl_1_bss_30;
static s16 lbl_1_bss_2E;
static s16 lbl_1_bss_2C;
static s16 lbl_1_bss_2A;
static s16 lbl_1_bss_28;
static s16 lbl_1_bss_1C[6];
static s16 lbl_1_bss_18[2];
static u8 lbl_1_bss_10_unused[8];
static s32 lbl_1_bss_C;
static u8 lbl_1_bss_6_unused[6];
static s16 lbl_1_bss_4;
static s16 lbl_1_bss_2;
static s16 lbl_1_bss_0;

static s16 lbl_1_data_0 = -1;
static Vec lbl_1_data_4 = { 0.0f, 4000.0f, 4000.0f };
static Vec lbl_1_data_10 = { 0.0f, -0.7f, -0.6f };
static GXColor lbl_1_data_1C = { 0xFF, 0xFF, 0xFF, 0xFF };

static Vec lbl_1_data_20_unused = { 0.0f, 4000.0f, -2000.0f };
static Vec lbl_1_data_2C_unused = { 0.0f, 1.0f, 0.0f };
static u8 lbl_1_data_38_unused[0xC] = { 0 };

void ObjectSetup(void)
{
    LightData *var_r28;
    Process *temp_r31;
    omObjData *var_r29;
    s32 temp_r27;
    s32 var_r26;
    s32 i;

    OSReport("******* M403ObjectSetup *********\n");
    Hu3DLighInit();
    var_r26 = Hu3DGLightCreateV(&lbl_1_data_4, &lbl_1_data_10, &lbl_1_data_1C);
    Hu3DGLightInfinitytSet(var_r26);
    var_r28 = &Hu3DGlobalLight[0];
    var_r28->unk_00 |= 0x8000;
    temp_r31 = omInitObjMan(50, 0x2000);
    temp_r27 = frand() & 0x1F;
    for (i = 0; i < temp_r27; i++) {
        fn_1_4528();
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
    lbl_1_bss_4C = omAddObjEx(temp_r31, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_50 = omAddObjEx(temp_r31, 0x10, 8, 0, -1, fn_1_424);
    lbl_1_bss_44 = omAddObjEx(temp_r31, 0x20, 16, 0, -1, fn_1_1274);
    lbl_1_bss_48 = omAddObjEx(temp_r31, 0x50, 16, 0, -1, fn_1_16D8);
    omAddObjEx(temp_r31, 0x60, 0, 0, -1, fn_1_3B80);
    fn_1_650C(temp_r31);
    fn_1_7C50(3);
    omMakeGroupEx(temp_r31, 0, 4);
    omGetGroupMemberListEx(temp_r31, 0);
    for (i = 0; i < 4; i++) {
        var_r29 = omAddObjEx(temp_r31, 0x30, 2, 8, 0, fn_1_1DD0);
        lbl_1_bss_34[i] = var_r29;
        var_r29->work[0] = i;
        var_r29->work[1] = i;
    }
    omGameSysInit(temp_r31);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    HuAudSndGrpSet(0x1C);
    lbl_1_bss_2 = 0;
    if (GWMGRecordGet(9) == 0) {
        GWMGRecordSet(9, 5);
    }
}

static void fn_1_424(omObjData *arg0)
{
    lbl_1_bss_30 = 0;
    arg0->func = fn_1_444;
}

static void fn_1_444(omObjData *arg0)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;

    switch (lbl_1_bss_30) {
        case 0:
            sp2C.x = 0.0f;
            sp2C.y = 0.0f;
            sp2C.z = -50.0f;
            sp20.x = -90.0f;
            sp20.y = 90.0f;
            sp20.z = 0.0f;
            var_f31 = 2200.0f;
            fn_1_1A50(1.0f, &sp2C, &sp20, var_f31);
            lbl_1_bss_28 = 60;
            lbl_1_bss_30++;
            break;
        case 1:
            if (--lbl_1_bss_28 == 0) {
                lbl_1_bss_30++;
            }
            break;
        case 2:
            if (lbl_1_bss_28 == 0) {
                fn_1_7C60();
                lbl_1_bss_28 = 90;
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
                fn_1_1AF0(180.0f, &sp14, &sp8, var_f30, &sp2C, &sp20, var_f31);
            }
            if (--lbl_1_bss_28 == 0) {
                lbl_1_bss_30++;
            }
            break;
        case 3:
            if (lbl_1_bss_28 == 0) {
                lbl_1_bss_28 = 90;
            }
            if (--lbl_1_bss_28 == 0) {
                lbl_1_bss_30++;
            }
            break;
        case 4:
            lbl_1_bss_30 = 5;
            lbl_1_bss_2E = lbl_1_bss_2C = -1;
            arg0->func = fn_1_82C;
            HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M403, 19), MEMORY_DEFAULT_NUM));
            break;
    }
    if (omSysExitReq != 0 && WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        arg0->func = fn_1_1214;
    }
}

static s32 lbl_1_data_68 = -1;

s32 lbl_1_data_6C[] = { DATA_MAKE_NUM(DATADIR_MGCONST, 0), DATA_MAKE_NUM(DATADIR_MGCONST, 1), DATA_MAKE_NUM(DATADIR_MGCONST, 2),
    DATA_MAKE_NUM(DATADIR_MGCONST, 3), DATA_MAKE_NUM(DATADIR_MGCONST, 4), DATA_MAKE_NUM(DATADIR_MGCONST, 5), DATA_MAKE_NUM(DATADIR_MGCONST, 6),
    DATA_MAKE_NUM(DATADIR_MGCONST, 7) };

static void fn_1_82C(omObjData *arg0)
{
    Vec sp1C;
    Vec sp10;
    float var_f31;
    s16 sp8[4];
    s32 var_r30;
    s32 var_r27;
    s32 var_r29;
    s32 i;

    switch (lbl_1_bss_30) {
        case 5:
            if (lbl_1_bss_2C == -1) {
                lbl_1_bss_2A = 1800;
                lbl_1_bss_2C = MGSeqStartCreate();
                MGSeqPosSet(lbl_1_bss_2C, 320.0f, 240.0f);
            }
            else if (MGSeqStatGet(lbl_1_bss_2C) == 0) {
                lbl_1_bss_2C = -1;
                lbl_1_bss_30++;
                lbl_1_bss_28 = 0;
                lbl_1_data_0 = 4;
                if (lbl_1_bss_2 != 0) {
                    sp1C.x = 476.0f;
                    sp1C.y = 64.0f;
                    var_r30 = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 51), 2, 0);
                    lbl_1_bss_1C[0] = var_r30;
                    espPosSet(var_r30, sp1C.x + 32.0f, sp1C.y);
                    var_r30 = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 51), 2, 0);
                    lbl_1_bss_1C[1] = var_r30;
                    espPosSet(var_r30, sp1C.x + 56.0f, sp1C.y);
                    var_r30 = espEntry(lbl_1_data_6C[GWPlayerCfg[lbl_1_bss_4].character], 1, 0);
                    lbl_1_bss_1C[2] = var_r30;
                    espPosSet(var_r30, sp1C.x, sp1C.y);
                    var_r30 = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 22), 3, 0);
                    lbl_1_bss_1C[3] = var_r30;
                    espPosSet(var_r30, sp1C.x + 36.0f, sp1C.y);
                    var_r30 = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 23), 4, 0);
                    lbl_1_bss_1C[4] = var_r30;
                    espColorSet(var_r30, 0, 0, 0);
                    espTPLvlSet(var_r30, 0.5);
                    espPosSet(var_r30, sp1C.x + 36.0f, sp1C.y);
                }
            }
            if (lbl_1_data_68 == -1 && (MGSeqStatGet(lbl_1_bss_2C) & 0x10)) {
                lbl_1_data_68 = HuAudSeqPlay(0x48);
            }
            break;
        case 6:
            var_r29 = 0;
            if (lbl_1_bss_2 != 0) {
                if (((Unkm403Struct_01 *)lbl_1_bss_34[lbl_1_bss_4]->data)->unk07 == 0 && fn_1_8264() == 0) {
                    var_r29++;
                }
            }
            else if (lbl_1_data_0 <= 1 && fn_1_8264() == 0) {
                var_r29++;
            }
            if (lbl_1_bss_2 != 0) {
                espBankSet(lbl_1_bss_1C[0], lbl_1_bss_0 / 10);
                espBankSet(lbl_1_bss_1C[1], lbl_1_bss_0 % 10);
            }
            if (var_r29 != 0) {
                lbl_1_bss_30++;
            }
            break;
        case 7:
            if (lbl_1_bss_2C == -1) {
                lbl_1_bss_2C = MGSeqFinishCreate();
                MGSeqPosSet(lbl_1_bss_2C, 320.0f, 240.0f);
                MGSeqKill(lbl_1_bss_2E);
                HuAudSeqFadeOut(lbl_1_data_68, 100);
                break;
            }
            if (MGSeqStatGet(lbl_1_bss_2C) == 0) {
                lbl_1_bss_2C = -1;
                if (lbl_1_bss_2 == 0) {
                    if (lbl_1_data_0 != 0) {
                        for (i = 0; i < 4; i++) {
                            if (((Unkm403Struct_01 *)lbl_1_bss_34[i]->data)->unk07 != 0) {
                                break;
                            }
                        }
                        sp1C.x = lbl_1_bss_34[i]->trans.x;
                        sp1C.y = 100.0f;
                        sp1C.z = lbl_1_bss_34[i]->trans.z;
                        sp10.x = -18.0f;
                        sp10.y = 0.0f;
                        sp10.z = 0.0f;
                        var_f31 = 600.0f;
                        fn_1_1A50(45.0f, &sp1C, &sp10, var_f31);
                    }
                    lbl_1_bss_30 = 9;
                    lbl_1_bss_28 = 90;
                    break;
                }
                if ((s32)GWMGRecordGet(9) < lbl_1_bss_0 - 1) {
                    GWMGRecordSet(9, lbl_1_bss_0 - 1);
                    lbl_1_bss_30 = 8;
                    break;
                }
                lbl_1_bss_2C = -1;
                lbl_1_bss_30 = 11;
                lbl_1_bss_28 = 150;
            }
            break;
        case 8:
            if (lbl_1_bss_2C == -1) {
                lbl_1_bss_2C = MGSeqRecordCreate(lbl_1_bss_0 - 1);
                break;
            }
            if (MGSeqStatGet(lbl_1_bss_2C) == 0) {
                lbl_1_bss_2C = -1;
                lbl_1_bss_28 = 150;
                lbl_1_bss_30 = 11;
            }
            break;
        case 9:
            if (--lbl_1_bss_28 == 0) {
                lbl_1_bss_30++;
            }
            break;
        case 10:
            if (lbl_1_bss_2C == -1) {
                if (lbl_1_data_0 == 0) {
                    lbl_1_bss_2C = MGSeqDrawCreate();
                    HuAudSStreamPlay(4);
                }
                else {
                    for (i = 0; i < 4; i++) {
                        sp8[i] = -1;
                    }
                    for (i = 0, var_r27 = 0; i < 4; i++) {
                        if (((Unkm403Struct_01 *)lbl_1_bss_34[i]->data)->unk07 != 0) {
                            GWPlayerCoinWinAdd(i, 10);
                            sp8[var_r27++] = GWPlayerCfg[i].character;
                        }
                    }
                    lbl_1_bss_2C = MGSeqWinCreate(sp8[0], sp8[1], sp8[2], sp8[3]);
                    HuAudSStreamPlay(1);
                }
            }
            lbl_1_bss_2C = -1;
            lbl_1_bss_28 = 210;
            lbl_1_bss_30++;
            break;
        case 11:
            if (--lbl_1_bss_28 == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                arg0->func = fn_1_1214;
            }
            break;
    }
    if (omSysExitReq != 0 && WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        arg0->func = fn_1_1214;
    }
}

static void fn_1_1214(omObjData *arg0)
{
    if (WipeStatGet() == 0) {
        fn_1_676C();
        CharModelKill(-1);
        MGSeqKill(lbl_1_bss_2E);
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

static void fn_1_1274(omObjData *arg0)
{
    Hu3DLightAllKill();
    lbl_1_bss_18[0] = Hu3DGLightCreateV(&lbl_1_data_4, &lbl_1_data_10, &lbl_1_data_1C);
    Hu3DGLightStaticSet(lbl_1_bss_18[0], 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_18[0]);
    lbl_1_bss_18[1] = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0, 0, 0);
    Hu3DGLightStaticSet(lbl_1_bss_18[1], 1);
    Hu3DGLightPointSet(lbl_1_bss_18[1], 0.0f, 0.0f, 3);
    Hu3DGLightColorSet(lbl_1_bss_18[0], 0, 0, 0, 0xFF);
    Hu3DGLightPosSet(lbl_1_bss_18[1], -1470.0f, 800.0f, -2000.0f, 0.0f, -1.0f, 0.0f);
    Hu3DGLightColorSet(lbl_1_bss_18[1], 0, 0, 0, 0xFF);
    Hu3DGLightPointSet(lbl_1_bss_18[1], 1200.0f, 0.6f, 3);
    arg0->func = fn_1_1460;
}

static void fn_1_1460(omObjData *arg0)
{
    s8 sp11[] = { 1, 0, 2, 1, 0, 3, 2, 1, 0 };
    s8 sp8[] = { 1, 1, 2, 2, 2, 3, 3, 3, 3 };
    s32 var_r30;

    switch (lbl_1_bss_30) {
        case 0:
            break;
        case 1:
            Hu3DGLightColorSet(lbl_1_bss_18[0], 0xF0, 0xF0, 0xF0, 0xFF);
            break;
        case 2:
            break;
        case 3:
            Hu3DGLightColorSet(lbl_1_bss_18[1], 0xFF, 0xE0, 0xD0, 0xFF);
            break;
        case 4:
            break;
        case 5:
            arg0->work[0] = 30;
            arg0->work[1] = 17;
            lbl_1_bss_C = 1;
            break;
        case 6:
            if (fn_1_8264() != 0) {
                break;
            }
            if (lbl_1_bss_C == 0) {
                lbl_1_bss_C = 30;
                lbl_1_bss_0++;
            }
            lbl_1_bss_C--;
            if (lbl_1_bss_C == 0) {
                var_r30 = (arg0->work[1] - 2) / 2;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
                fn_1_8670(sp11[var_r30]);
                fn_1_7C50(sp8[var_r30]);
                fn_1_7C30(0.01f * arg0->work[0]);
                arg0->work[0] += 5;
                if (arg0->work[1] > 2) {
                    arg0->work[1]--;
                }
            }
            break;
    }
}

static void fn_1_16D8(omObjData *arg0)
{
    Unkm403Struct_00 *temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r3), MEMORY_DEFAULT_NUM);
    arg0->data = temp_r3;
    temp_r3->unk148 = temp_r3->unk144 = 0.0f;
    temp_r3->unk140 = 1.0f;
    temp_r3->unk10.x = temp_r3->unk28.x = -23.5f;
    temp_r3->unk10.y = temp_r3->unk28.y = 0.0f;
    temp_r3->unk10.z = temp_r3->unk28.z = 0.0f;
    temp_r3->unk04.x = temp_r3->unk1C.x = 0.0f;
    temp_r3->unk04.y = temp_r3->unk1C.y = 320.0f;
    temp_r3->unk04.z = temp_r3->unk1C.z = 147.0f;
    temp_r3->unk130 = temp_r3->unk134 = 1720.0f;
    arg0->func = fn_1_17DC;
}

static void fn_1_17DC(omObjData *arg0)
{
    Unkm403Struct_00 *temp_r31;
    float temp_f31;

    temp_r31 = arg0->data;
    if (temp_r31->unk148 > 0.0f) {
        temp_r31->unk148 -= temp_r31->unk140;
        temp_f31 = (temp_r31->unk144 - temp_r31->unk148) / temp_r31->unk144;
        temp_f31 = sind(90.0f * temp_f31);
        if (temp_r31->unk00 == 0) {
            temp_r31->unk04.x = temp_r31->unk1C.x + temp_f31 * (temp_r31->unk34.x - temp_r31->unk1C.x);
            temp_r31->unk04.y = temp_r31->unk1C.y + temp_f31 * (temp_r31->unk34.y - temp_r31->unk1C.y);
            temp_r31->unk04.z = temp_r31->unk1C.z + temp_f31 * (temp_r31->unk34.z - temp_r31->unk1C.z);
            temp_r31->unk10.x = temp_r31->unk28.x + temp_f31 * (temp_r31->unk40.x - temp_r31->unk28.x);
            temp_r31->unk10.y = temp_r31->unk28.y + temp_f31 * (temp_r31->unk40.y - temp_r31->unk28.y);
            temp_r31->unk10.z = temp_r31->unk28.z + temp_f31 * (temp_r31->unk40.z - temp_r31->unk28.z);
            temp_r31->unk130 = temp_r31->unk134 + temp_f31 * (temp_r31->unk138 - temp_r31->unk134);
        }
        else {
            fn_1_57E0(2.0f * temp_f31, &temp_r31->unk04, temp_r31->unkF4, &temp_r31->unk64, temp_r31->unk88, 3);
            fn_1_57E0(2.0f * temp_f31, &temp_r31->unk10, temp_r31->unk100, &temp_r31->unkAC, temp_r31->unkD0, 3);
            temp_r31->unk130 = fn_1_52AC(2.0f * temp_f31, temp_r31->unk124, temp_r31->unk10C, temp_r31->unk118, 3);
        }
    }
    CRot.x = temp_r31->unk10.x;
    CRot.y = temp_r31->unk10.y;
    CRot.z = temp_r31->unk10.z;
    Center.x = temp_r31->unk04.x;
    Center.y = temp_r31->unk04.y;
    Center.z = temp_r31->unk04.z;
    CZoom = temp_r31->unk130;
}

static void fn_1_1A50(float arg0, Vec *arg1, Vec *arg2, float arg3)
{
    Unkm403Struct_00 *temp_r31;

    temp_r31 = lbl_1_bss_48->data;
    temp_r31->unk00 = 0;
    temp_r31->unk144 = arg0;
    temp_r31->unk148 = arg0;
    temp_r31->unk1C = temp_r31->unk04;
    temp_r31->unk34.x = arg1->x;
    temp_r31->unk34.y = arg1->y;
    temp_r31->unk34.z = arg1->z;
    temp_r31->unk28 = temp_r31->unk10;
    temp_r31->unk40.x = arg2->x;
    temp_r31->unk40.y = arg2->y;
    temp_r31->unk40.z = arg2->z;
    temp_r31->unk134 = temp_r31->unk130;
    temp_r31->unk138 = arg3;
}

static void fn_1_1AF0(float arg0, Vec *arg1, Vec *arg2, float arg3, Vec *arg4, Vec *arg5, float arg6)
{
    Unkm403Struct_00 *temp_r31;

    temp_r31 = lbl_1_bss_48->data;
    temp_r31->unk00 = 1;
    temp_r31->unk148 = temp_r31->unk144 = arg0;
    temp_r31->unk1C = temp_r31->unk04;
    temp_r31->unk34.x = arg1->x;
    temp_r31->unk34.y = arg1->y;
    temp_r31->unk34.z = arg1->z;
    temp_r31->unk4C.x = arg4->x;
    temp_r31->unk4C.y = arg4->y;
    temp_r31->unk4C.z = arg4->z;
    temp_r31->unk28 = temp_r31->unk10;
    temp_r31->unk40.x = arg2->x;
    temp_r31->unk40.y = arg2->y;
    temp_r31->unk40.z = arg2->z;
    temp_r31->unk58.x = arg5->x;
    temp_r31->unk58.y = arg5->y;
    temp_r31->unk58.z = arg5->z;
    temp_r31->unk134 = temp_r31->unk130;
    temp_r31->unk138 = arg3;
    temp_r31->unk13C = arg6;
    temp_r31->unk64 = temp_r31->unk1C;
    temp_r31->unk70 = temp_r31->unk4C;
    temp_r31->unk7C = temp_r31->unk34;
    temp_r31->unkAC = temp_r31->unk28;
    temp_r31->unkB8 = temp_r31->unk58;
    temp_r31->unkC4 = temp_r31->unk40;
    temp_r31->unk10C[0] = temp_r31->unk134;
    temp_r31->unk10C[1] = temp_r31->unk13C;
    temp_r31->unk10C[2] = temp_r31->unk138;
    temp_r31->unk124[0] = 0.0f;
    temp_r31->unk124[1] = ABS(temp_r31->unk10C[1] - temp_r31->unk10C[0]);
    temp_r31->unk124[2] = ABS(temp_r31->unk10C[2] - temp_r31->unk10C[1]) + temp_r31->unk124[1];
    fn_1_5400(temp_r31->unkF4, &temp_r31->unk64, temp_r31->unk88, 3);
    fn_1_5400(temp_r31->unk100, &temp_r31->unkAC, temp_r31->unkD0, 3);
    fn_1_4FF4(temp_r31->unk124, temp_r31->unk10C, temp_r31->unk118, 3);
}

static void fn_1_1DA8(float arg0)
{
    Unkm403Struct_00 *temp_r31;

    temp_r31 = lbl_1_bss_48->data;
    temp_r31->unk140 = arg0;
}

static s32 lbl_1_data_C4[] = { 0, 2, 3, 8, 10, 9, 23, 24 };

static Vec lbl_1_data_E4[] = { { -300.0f, 2200.0f, 0.0f }, { -100.0f, 2200.0f, 0.0f }, { 100.0f, 2200.0f, 0.0f }, { 300.0f, 2200.0f, 0.0f } };

static float lbl_1_data_114[] = { 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 100.0f, 40.0f, 80.0f };

static float lbl_1_data_134[] = { 160.0f, 160.0f, 180.0f, 160.0f, 160.0f, 180.0f, 180.0f, 200.0f };

static u32 lbl_1_data_154 = 0x41C64E6D;

static void fn_1_1DD0(omObjData *arg0)
{
    Unkm403Struct_01 *temp_r3;
    s32 temp_r27;
    s32 i;
    s32 temp_r28;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r3), MEMORY_DEFAULT_NUM);
    arg0->data = temp_r3;
    temp_r3->unk00 = arg0->work[0];
    temp_r3->unk01 = GWPlayerCfg[temp_r3->unk00].character;
    temp_r3->unk02 = temp_r3->unk00 >> 1;
    temp_r3->unk03 = temp_r3->unk00 & 1;
    temp_r3->unk04 = GWPlayerCfg[temp_r3->unk00].pad_idx;
    temp_r3->unk05 = GWPlayerCfg[temp_r3->unk00].iscom;
    temp_r3->unk06 = GWPlayerCfg[temp_r3->unk00].diff;
    temp_r3->unk18 = temp_r3->unk1A = 0;
    temp_r3->unk07 = 1;
    temp_r3->unk0C = 1;
    temp_r3->unk0D = 0;
    temp_r3->unk0E = 0;
    temp_r3->unk0A = 0;
    temp_r3->unk9C = 0;
    temp_r27 = arg0->work[1];
    temp_r3->unk2C.x = lbl_1_data_E4[temp_r27].x;
    temp_r3->unk2C.y = lbl_1_data_E4[temp_r27].y + 100.0f * ((fn_1_4528() - 0x8000) / 32768.0f);
    temp_r3->unk2C.z = lbl_1_data_E4[temp_r27].z;
    temp_r3->unk44 = temp_r3->unk48 = temp_r3->unk4C = 0.0f;
    temp_r3->unk38 = temp_r3->unk3C = temp_r3->unk40 = 0.0f;
    temp_r3->unk20 = temp_r3->unk3C;
    temp_r3->unk24 = 0.0f;
    temp_r3->unk1C = 0.0f;
    temp_r3->unk28 = 1.0f;
    memset(&temp_r3->unk5C, 0, 0x40);
    temp_r3->unkA0 = 1;
    if (lbl_1_bss_2 != 0 && temp_r3->unk05 == 0) {
        lbl_1_bss_4 = temp_r3->unk00;
    }
    temp_r28 = CharModelCreate(temp_r3->unk01, 4);
    arg0->model[0] = temp_r28;
    Hu3DModelAttrSet(temp_r28, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(temp_r28);
    for (i = 0; i < 8; i++) {
        arg0->motion[i] = CharModelMotionCreate(temp_r3->unk01, lbl_1_data_C4[i]);
    }
    CharModelMotionDataClose(temp_r3->unk01);
    CharModelMotionSet(temp_r3->unk01, arg0->motion[temp_r3->unk18]);
    omSetTra(arg0, temp_r3->unk2C.x, temp_r3->unk2C.y, temp_r3->unk2C.z);
    Hu3DModelPosSet(temp_r28, temp_r3->unk2C.x, temp_r3->unk2C.y, temp_r3->unk2C.z);
    Hu3DModelRotSet(temp_r28, 0.0f, 30.0f, 0.0f);
    CharModelStepTypeSet(temp_r3->unk01, 1);
    CharModelVoiceEnableSet(temp_r3->unk01, arg0->motion[3], 0);
    arg0->func = fn_1_2158;
}

static void fn_1_2158(omObjData *arg0)
{
    Unkm403Struct_01 *temp_r31;
    s32 sp8;

    sp8 = arg0->model[0];
    temp_r31 = arg0->data;
    temp_r31->unk10 = temp_r31->unk12 = 0;
    temp_r31->unk14 = temp_r31->unk16 = 0;
    switch (lbl_1_bss_30) {
        case 3:
            break;
        case 2:
            if (lbl_1_bss_28 < 60.0f) {
                break;
            }
            /* fallthrough */
        case 1:
            temp_r31->unk18 = 3;
            temp_r31->unk48 = 0.0f;
            temp_r31->unk0C = 0;
            break;
        case 5:
            arg0->func = fn_1_22A4;
            break;
    }
    if (temp_r31->unk2C.y < 10.0f) {
        omVibrate(temp_r31->unk00, 12, 6, 6);
        temp_r31->unk2C.y = 10.0f;
        temp_r31->unk0C = 1;
    }
    fn_1_2FDC(arg0);
}

static void fn_1_22A4(omObjData *arg0)
{
    Unkm403Struct_01 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;

    temp_r29 = arg0->model[0];
    temp_r31 = arg0->data;
    if (temp_r31->unk07 != 0) {
        if (lbl_1_bss_30 == 6 && !(temp_r31->unk07 & 2)) {
            if (temp_r31->unk05 != 0) {
                fn_1_2598(arg0);
            }
            else {
                temp_r31->unk10 = HuPadStkX[temp_r31->unk04];
                temp_r31->unk12 = HuPadStkY[temp_r31->unk04];
                temp_r31->unk14 = HuPadBtnDown[temp_r31->unk04];
                temp_r31->unk16 = HuPadBtn[temp_r31->unk04];
            }
        }
        else {
            temp_r31->unk10 = temp_r31->unk12 = 0;
            temp_r31->unk14 = temp_r31->unk16 = 0;
        }
        switch (lbl_1_bss_30) {
            case 5:
            case 6:
                break;
            case 7:
            case 9:
                arg0->scale.y += 0.2f * (1.0f - arg0->scale.y);
                temp_r31->unk3C = fn_1_457C(temp_r31->unk3C, 0.0f, 0.9f);
                break;
            case 10:
                if (temp_r31->unk18 != 6) {
                    temp_r31->unk18 = 6;
                }
                break;
        }
        if (temp_r31->unk07 & 2) {
            temp_r31->unk10 = temp_r31->unk12 = 0;
            temp_r31->unk14 = temp_r31->unk16 = 0;
            if (arg0->scale.y < 0.2f) {
                omVibrate(temp_r31->unk00, 12, 4, 2);
                HuAudFXPlay(0x523);
                temp_r31->unk07 = 0;
                Hu3DModelShadowReset(temp_r29);
                Hu3DModelAttrSet(temp_r29, HU3D_ATTR_DISPOFF);
                lbl_1_data_0--;
                temp_r28 = fn_1_400C(DATA_MAKE_NUM(DATADIR_M403, 19), 100, fn_1_40A8);
                Hu3DModelPosSet(temp_r28, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
                Hu3DModelLayerSet(temp_r28, 2);
            }
        }
        if (fn_1_8264() != 0) {
            temp_r31->unkA0 = 0;
        }
        else if (!(temp_r31->unk07 & 2) && temp_r31->unkA0 == 0) {
            omVibrate(temp_r31->unk00, 12, 6, 6);
            temp_r31->unkA0 = 1;
        }
        fn_1_2FDC(arg0);
    }
}

static void fn_1_2598(omObjData *arg0)
{
    Vec sp38[6];
    Vec sp14;
    Vec sp8;
    float sp20[6];
    float var_f31;
    float var_f30;
    float temp_f29;
    float var_f28;
    Unkm403Struct_01 *temp_r31;
    s16 var_r27;
    s16 var_r26;
    s16 var_r21;
    s16 var_r20;
    s16 temp_r28;
    s32 var_r23;
    s32 var_r22;
    s32 var_r25;
    s32 temp_r24;
    s32 var_r29;
    s32 i;

    var_r22 = 0;
    for (i = 0, var_r29 = 0; i < 4; i++) {
        temp_r31 = lbl_1_bss_34[i]->data;
        if (temp_r31->unk05 == 0 && temp_r31->unk07 != 0) {
            break;
        }
    }
    temp_r31 = arg0->data;
    if (i >= 4 && temp_r31->unk9C == 0) {
        var_r22 = 1;
    }
    temp_r28 = temp_r31->unk06;
    var_r27 = var_r26 = var_r21 = var_r20 = 0;
    switch (temp_r31->unk5C) {
        case 0:
            if (fn_1_8264() != 0) {
                temp_r31->unk5C = 1;
            }
            break;
        case 1:
            temp_r31->unk5C = 2;
            temp_r31->unk5E = (s32)(60.0f * (1.2f - 0.2f * temp_r28) * (fn_1_4528() / 65536.0f));
            temp_r31->unk60 = 500.0f * ((fn_1_4528() - 0x8000) / 32768.0f);
            temp_r31->unk64 = 200.0f * ((fn_1_4528() - 0x8000) / 32768.0f);
            var_r27 = temp_r31->unk10;
            var_r26 = temp_r31->unk12;
            break;
        case 2:
            sp8.x = temp_r31->unk60 - temp_r31->unk2C.x;
            sp8.y = 0.0f;
            sp8.z = temp_r31->unk64 - temp_r31->unk2C.z;
            var_f31 = fn_1_59F4(&sp8);
            if (var_f31 < 20.0f) {
                temp_r31->unk5C = 3;
            }
            else {
                if (var_f31 >= 100.0f) {
                    var_f28 = 0.8f;
                }
                else {
                    var_f28 = 0.4f;
                }
                var_f30 = fn_1_457C(temp_r31->unk3C, atan2d(sp8.x, sp8.z), var_f28);
                temp_f29 = 48.0f + 4.0f * temp_r28;
                var_r27 = temp_f29 * sind(var_f30);
                var_r26 = temp_f29 * -cosd(var_f30);
                if (fn_1_8264() == 0) {
                    temp_r31->unk5C = 0;
                    if (temp_r31->unk5E == 0) {
                        temp_r31->unk5E = -1;
                    }
                }
                else if (temp_r31->unk5E >= 0) {
                    if (temp_r31->unk5E == 0) {
                        if (var_f31 < 150.0f && temp_r31->unk0E != 0) {
                            temp_r31->unk5C = 3;
                        }
                        else if ((s32)((temp_r28 + 2) * (fn_1_4528() / 65536.0f)) != 0 && var_r22 == 0) {
                            temp_r31->unk5C = 4;
                        }
                        else {
                            temp_r31->unk5C = 1;
                        }
                    }
                    else {
                        temp_r31->unk5E--;
                    }
                }
            }
            break;
        case 3:
            sp8.x = temp_r31->unk60 - temp_r31->unk2C.x;
            sp8.y = 0.0f;
            sp8.z = temp_r31->unk64 - temp_r31->unk2C.z;
            if (fn_1_59F4(&sp8) >= 30.000002f && temp_r31->unk0E == 0) {
                temp_r31->unk5C = 2;
            }
            else if (fn_1_8264() == 0) {
                temp_r31->unk5C = 0;
            }
            else {
                if (temp_r31->unk5E > 0) {
                    temp_r31->unk5E--;
                }
                if (temp_r31->unk5E == 0) {
                    if ((s32)((temp_r28 + 2) * (fn_1_4528() / 65536.0f)) != 0 && var_r22 == 0) {
                        temp_r31->unk5C = 4;
                    }
                    else {
                        temp_r31->unk5C = 1;
                    }
                }
            }
            break;
        case 4:
            temp_r24 = fn_1_82D0(&sp38[0]);
            for (i = 0; i < temp_r24; i++) {
                VECSubtract(&sp38[i], &temp_r31->unk2C, &sp8);
                sp20[i] = VECMag(&sp8);
            }
            for (i = 0; i < temp_r24 - 1; i++) {
                for (var_r29 = i + 1; var_r29 < temp_r24; var_r29++) {
                    if (sp20[i] > sp20[var_r29]) {
                        sp14 = sp38[i];
                        sp38[i] = sp38[var_r29];
                        sp38[var_r29] = sp14;
                        var_f31 = sp20[i];
                        sp20[i] = sp20[var_r29];
                        sp20[var_r29] = var_f31;
                    }
                }
            }
            var_r25 = 1000;
            var_r23 = var_r25 * (fn_1_4528() / 65536.0f);
            for (i = 0; i < temp_r24 - 1; i++) {
                var_r25 = var_r25 * (5.0f + temp_r28) * 0.1f;
                var_r23 -= var_r25;
                if (var_r23 < 0) {
                    break;
                }
            }
            temp_r31->unk60 = sp38[i].x + 100.0f * (0.5f - 0.15f * temp_r28) * ((fn_1_4528() - 0x8000) / 32768.0f);
            temp_r31->unk64 = sp38[i].z + 100.0f * (0.5f - 0.15f * temp_r28) * ((fn_1_4528() - 0x8000) / 32768.0f);
            temp_r31->unk5C = 2;
            temp_r31->unk5E = -1;
            var_r27 = temp_r31->unk10;
            var_r26 = temp_r31->unk12;
            break;
    }
    temp_r31->unk10 = var_r27;
    temp_r31->unk12 = var_r26;
    temp_r31->unk14 = var_r21;
    temp_r31->unk16 = var_r20;
}

static void fn_1_2FDC(omObjData *arg0)
{
    float var_f29;
    Unkm403Struct_01 *temp_r31;
    s32 temp_r25;
    s16 var_r27;
    s16 var_r28;
    s16 temp_r30;
    s16 temp_r29;
    s16 spA;
    s16 sp8;

    temp_r31 = arg0->data;
    temp_r25 = arg0->model[0];
    var_r28 = temp_r31->unk18;
    temp_r31->unk50 = temp_r31->unk2C;
    temp_r30 = temp_r31->unk10;
    temp_r29 = temp_r31->unk12;
    spA = temp_r31->unk14;
    sp8 = temp_r31->unk16;
    switch (temp_r31->unk18) {
        case 0:
        case 1:
        case 2:
            temp_r31->unk1C = 0.14f * sqrtf(temp_r30 * temp_r30 + temp_r29 * temp_r29);
            if (temp_r31->unk1C > 0.1f) {
                if (temp_r31->unk1C >= 6.0f) {
                    var_r28 = 2;
                    var_r27 = 1;
                }
                else {
                    var_r28 = 1;
                    var_r27 = 1;
                }
                var_f29 = atan2d(temp_r30, -temp_r29);
                temp_r31->unk3C = fn_1_457C(temp_r31->unk3C, var_f29, 0.5f);
                temp_r31->unk20 = temp_r31->unk3C;
                temp_r31->unk24 += 1.0f;
                if (temp_r31->unk24 >= 0.5f * temp_r31->unk28) {
                    temp_r31->unk24 -= 0.5f * temp_r31->unk28;
                }
                temp_r31->unk1C *= 1.0 + 0.25 * cosd(90.0f * (temp_r31->unk24 / (0.5f * temp_r31->unk28)));
            }
            else {
                temp_r31->unk24 = 0.0f;
                temp_r31->unk1C = 0.0f;
                var_r28 = 0;
                var_r27 = 1;
            }
            temp_r31->unk48 = -2.4333334f;
            break;
        case 3:
            var_r27 = 0;
            if (Hu3DData[temp_r25].unk_0C == -1 && CharModelMotionEndCheck(temp_r31->unk01)) {
                temp_r31->unk48 += -2.4333334f;
            }
            else {
                temp_r31->unk48 = 0.0f;
            }
            if (temp_r31->unk0C != 0) {
                if (temp_r31->unk0D != 0) {
                    temp_r31->unk48 = 0.0f;
                    temp_r31->unk0D = 0;
                    var_r28 = 5;
                    var_r27 = 0;
                }
                else {
                    temp_r31->unk48 *= -0.1f;
                    temp_r31->unk0C = 0;
                    var_r28 = 4;
                    var_r27 = 0;
                }
            }
            break;
        case 4:
            temp_r31->unk48 += -2.4333334f;
            if (temp_r31->unk0C != 0 && CharModelMotionEndCheck(temp_r31->unk01)) {
                var_r28 = 5;
                var_r27 = 0;
            }
            break;
        case 5:
            if (CharModelMotionEndCheck(temp_r31->unk01)) {
                var_r28 = 0;
                var_r27 = 1;
            }
            break;
        case 6:
        case 7:
            var_r27 = 0;
            temp_r31->unk48 = -2.4333334f;
            break;
    }
    if (temp_r31->unk07 & 4) {
        if (temp_r31->unk0A & 2) {
            Hu3DModelAttrSet(temp_r25, HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(temp_r25, HU3D_ATTR_DISPOFF);
        }
        if (--temp_r31->unk0A == 0) {
            temp_r31->unk07 &= ~4;
        }
    }
    temp_r31->unk44 = temp_r31->unk1C * sind(temp_r31->unk20);
    temp_r31->unk4C = temp_r31->unk1C * cosd(temp_r31->unk20);
    temp_r31->unk2C.x += temp_r31->unk44;
    if (temp_r31->unk0C == 0) {
        temp_r31->unk2C.y += temp_r31->unk48;
    }
    temp_r31->unk2C.z += temp_r31->unk4C;
    if (var_r28 != temp_r31->unk1A) {
        temp_r31->unk1A = var_r28;
        temp_r31->unk18 = var_r28;
        CharModelMotionShiftSet(temp_r31->unk01, arg0->motion[temp_r31->unk18], 0.0f, 8.0f, var_r27);
        temp_r31->unk28 = CharModelMotionMaxTimeGet(temp_r31->unk01);
    }
    omSetTra(arg0, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
    omSetRot(arg0, temp_r31->unk38, temp_r31->unk3C, temp_r31->unk40);
}

static void fn_1_3800(void)
{
    s32 var_r29;
    s32 i;
    Unkm403Struct_01 *temp_r30;

    var_r29 = 0;
    for (i = 0; i < 4; i++) {
        temp_r30 = lbl_1_bss_34[i]->data;
        if (temp_r30->unk07 != 0) {
            temp_r30->unk0E = 0;
        }
    }
    while (fn_1_3894() != 0 && var_r29 < 50) {
        var_r29++;
    }
}

static s32 fn_1_3894(void)
{
    Vec sp14[4];
    Vec sp8;
    float var_f31;
    float var_f30;
    s32 var_r26;
    omObjData *temp_r25;
    Unkm403Struct_01 *temp_r28;
    Unkm403Struct_01 *temp_r27;
    Unkm403Struct_01 *temp_r31;
    s32 i;
    s32 j;

    var_r26 = 0;
    for (i = 0; i < 4; i++) {
        sp14[i].x = sp14[i].y = sp14[i].z = 0.0f;
    }
    for (i = 0; i < 3; i++) {
        temp_r28 = lbl_1_bss_34[i]->data;
        if (temp_r28->unk07 != 0) {
            for (j = i + 1; j < 4; j++) {
                temp_r27 = lbl_1_bss_34[j]->data;
                if (temp_r27->unk07 != 0) {
                    VECSubtract(&temp_r28->unk2C, &temp_r27->unk2C, &sp8);
                    var_f31 = VECMag(&sp8);
                    if (var_f31 < 80.0f) {
                        VECNormalize(&sp8, &sp8);
                        var_f30 = 0.0001f + 0.5f * (80.0f - var_f31);
                        VECScale(&sp8, &sp8, var_f30);
                        VECAdd(&sp14[i], &sp8, &sp14[i]);
                        VECSubtract(&sp14[j], &sp8, &sp14[j]);
                        temp_r28->unk0E++;
                        temp_r27->unk0E++;
                        var_r26++;
                    }
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        temp_r25 = lbl_1_bss_34[i];
        temp_r31 = temp_r25->data;
        if (temp_r31->unk07 != 0) {
            VECAdd(&temp_r31->unk2C, &sp14[i], &temp_r31->unk2C);
            if (temp_r31->unk2C.x > 660.0f) {
                temp_r31->unk2C.x = 660.0f;
            }
            if (temp_r31->unk2C.x < -660.0f) {
                temp_r31->unk2C.x = -660.0f;
            }
            if (temp_r31->unk2C.z > 360.0f) {
                temp_r31->unk2C.z = 360.0f;
            }
            if (temp_r31->unk2C.z < -360.0f) {
                temp_r31->unk2C.z = -360.0f;
            }
            omSetTra(temp_r25, temp_r31->unk2C.x, temp_r31->unk2C.y, temp_r31->unk2C.z);
        }
    }
    return var_r26;
}

static void fn_1_3B80(omObjData *arg0)
{
    s32 sp8[4];
    s32 var_r30;
    s32 i;

    if (lbl_1_bss_30 < 6) {
        return;
    }
    if (fn_1_8264() != 0) {
        for (i = 0; i < 4; i++) {
            fn_1_3E4C(lbl_1_bss_34[i]);
        }
    }
    else {
        for (i = 0, var_r30 = 0; i < 4; i++) {
            ((Unkm403Struct_01 *)lbl_1_bss_34[i]->data)->unk9C = 0;
            if (((Unkm403Struct_01 *)lbl_1_bss_34[i]->data)->unk07 != 0) {
                sp8[var_r30++] = i;
            }
        }
        if (var_r30 != 0) {
            i = sp8[(s32)(var_r30 * (fn_1_4528() / 65536.0f))];
            ((Unkm403Struct_01 *)lbl_1_bss_34[i]->data)->unk9C = 1;
        }
    }
    fn_1_3800();
}

static void fn_1_3D6C(Vec *arg0, Vec *arg1)
{
    Vec sp18[6];
    Vec spC;
    float var_f31;
    float var_f30;
    s32 temp_r30;
    s32 i;

    temp_r30 = fn_1_8470(sp18);
    var_f31 = 2000.0f;
    for (i = 0; i < temp_r30; i++) {
        VECSubtract(&sp18[i], arg0, &spC);
        var_f30 = VECMag(&spC);
        if (var_f30 >= var_f31) {
            continue;
        }
        var_f31 = var_f30;
        *arg1 = sp18[i];
    }
}

static void fn_1_3E4C(omObjData *arg0)
{
    Vec sp8;
    float var_f30;
    float var_f31;
    Unkm403Struct_01 *temp_r31;

    temp_r31 = arg0->data;
    if (temp_r31->unk07 != 0) {
        var_f30 = fn_1_80D4(&temp_r31->unk2C, lbl_1_data_114[temp_r31->unk01]) - 10.0f;
        if (var_f30 < 0.0f) {
            var_f30 = 0.0f;
        }
        if (!(temp_r31->unk07 & 2)) {
            var_f31 = 1.0f;
            if (var_f30 < lbl_1_data_134[temp_r31->unk01]) {
                if (fn_1_86A0(&temp_r31->unk2C, &sp8) != 0) {
                    temp_r31->unk2C.x = sp8.x;
                    temp_r31->unk2C.z = sp8.z;
                }
                else {
                    if (fn_1_7F78(temp_r31->unk2C.x, temp_r31->unk2C.z) - 10.0f < 100.0f) {
                        temp_r31->unk07 |= 2;
                    }
                    var_f31 = var_f30 / lbl_1_data_134[temp_r31->unk01];
                }
            }
        }
        else {
            var_f31 = var_f30 / lbl_1_data_134[temp_r31->unk01];
        }
        if (arg0->scale.y < var_f31) {
            var_f31 = arg0->scale.y + 0.2f * (var_f31 - arg0->scale.y);
        }
        arg0->scale.y = var_f31;
    }
}

static s16 fn_1_400C(s32 arg0, s16 arg1, ParticleHook arg2)
{
    AnimData *var_r29;
    ParticleData *temp_r31;
    s32 temp_r30;

    var_r29 = HuSprAnimRead(HuDataReadNum(arg0, MEMORY_DEFAULT_NUM));
    temp_r30 = Hu3DParticleCreate(var_r29, arg1);
    Hu3DParticleHookSet(temp_r30, arg2);
    temp_r31 = Hu3DData[temp_r30].unk_120;
    temp_r31->unk_2E = temp_r30;
    temp_r31->unk_00 = temp_r31->unk_02 = 0;
    return temp_r30;
}

static void fn_1_40A8(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    HsfanimStruct01 *var_r31;
    s16 sp8;
    s32 i;

    sp8 = 0;
    switch (particle->unk_00) {
        case 0:
            temp_f29 = 360.0f / particle->unk_30;
            var_r31 = particle->unk_48;
            for (i = 0; i < particle->unk_30; i++, var_r31++) {
                var_r31->unk08.x = sind(temp_f29 * i) * (1.0f + 6.0f * ((fn_1_4528() - 0x8000) / 32768.0f) * 0.1f);
                var_r31->unk08.y = 0.0f;
                var_r31->unk08.z = cosd(temp_f29 * i) * (1.0f + 6.0f * ((fn_1_4528() - 0x8000) / 32768.0f) * 0.1f);
                var_r31->unk34.x = 0.0f;
                var_r31->unk34.y = 0.0f;
                var_r31->unk34.z = 0.0f;
            }
            particle->unk_02 = 30;
            particle->unk_00++;
            /* fallthrough */
        case 1:
            particle->unk_02--;
            temp_f31 = (30.0f - particle->unk_02) / 30.0f;
            temp_f30 = particle->unk_02 / 30.0f;
            var_r31 = particle->unk_48;
            for (i = 0; i < particle->unk_30; i++, var_r31++) {
                var_r31->unk34.x += 5.0f * temp_f30 * var_r31->unk08.x;
                var_r31->unk34.y = 20.0f;
                var_r31->unk34.z += 5.0f * temp_f30 * var_r31->unk08.z;
                var_r31->unk2C = 20.0f + 60.0f * temp_f31;
                var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = 0xFF;
                var_r31->unk40.a = 64.0f * (1.0f - temp_f31 * temp_f31);
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

static s32 fn_1_4528(void)
{
    lbl_1_data_154 *= 0x41C64E6D;
    lbl_1_data_154 += 0x3039;
    return lbl_1_data_154 >> 16;
}

static float fn_1_457C(float arg0, float arg1, float arg2)
{
    float var_f31;

    if (arg0 > 180.0f) {
        arg0 -= 360.0f;
    }
    else if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    }
    if (arg1 > 180.0f) {
        arg1 -= 360.0f;
    }
    else if (arg1 <= -180.0f) {
        arg1 += 360.0f;
    }
    var_f31 = arg0 - arg1;
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    else if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    }
    arg0 = arg1 + var_f31 * arg2;
    if (arg0 > 180.0f) {
        arg0 -= 360.0f;
    }
    else if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    }
    return arg0;
}

static void fn_1_46E4(Mtx arg0, float arg1, float arg2, float arg3)
{
    Mtx sp38;
    Mtx sp8;

    if (arg3 != 0.0f) {
        MTXRotRad(arg0, 'Z', MTXDegToRad(arg3));
    }
    else {
        MTXIdentity(arg0);
    }
    if (arg1 != 0.0f) {
        MTXRotRad(sp38, 'X', MTXDegToRad(arg1));
        MTXConcat(sp38, arg0, arg0);
    }
    if (arg2 != 0.0f) {
        MTXRotRad(sp8, 'Y', MTXDegToRad(arg2));
        MTXConcat(sp8, arg0, arg0);
    }
}

static void fn_1_4804(float *arg0, float *arg1)
{
    float temp_f29;
    float var_f28;
    double var_f30;

    arg1[0] = atan2d(arg0[10], arg0[6]);
    arg1[2] = atan2d(arg0[0], arg0[1]);
    temp_f29 = -arg0[2];
    if (1.0 - temp_f29 * temp_f29 < 0.0) {
        var_f30 = -(1.0 - temp_f29 * temp_f29);
    }
    else {
        var_f30 = 1.0 - temp_f29 * temp_f29;
    }
    var_f28 = sqrtf(var_f30);
    if (arg1[0] > 90.0f && arg1[0] < 270.0f && arg1[2] > 90.0f && arg1[2] < 270.0f) {
        arg1[0] = fmod(180.0f + arg1[0], 360.0);
        arg1[2] = fmod(180.0f + arg1[2], 360.0);
        var_f28 = -var_f28;
    }
    arg1[1] = atan2d(var_f28, temp_f29);
}

static float fn_1_4B10(float arg0, float arg1, float arg2, float arg3)
{
    float temp_f31;
    float var_f30;

    temp_f31 = 1.0 - arg0;
    var_f30 = temp_f31 * temp_f31 * arg1 + temp_f31 * arg0 * arg2 * 2.0 + arg0 * arg0 * arg3;
    return var_f30;
}

static void fn_1_4B88(float *arg0, float *arg1, float *arg2, float *arg3, float arg4)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        *(arg3++) = fn_1_4B10(arg4, *(arg0++), *(arg1++), *(arg2++));
    }
}

static float fn_1_4CA4(float arg0, float arg1, float arg2, float arg3)
{
    float var_f31 = 2.0 * ((arg0 - 1.0) * arg1 + (1.0 - 2.0 * arg0) * arg2 + arg0 * arg3);
    return var_f31;
}

static void fn_1_4D1C(float *arg0, float *arg1, float *arg2, float *arg3, float arg4)
{
    float spC[3];
    float var_f29;
    s32 i;

    for (i = 0; i < 3; i++) {
        spC[i] = fn_1_4CA4(arg4, *(arg0++), *(arg1++), *(arg2++));
    }
    var_f29 = VECMagPoint(spC[0], spC[1], spC[2]);
    if (var_f29) {
        var_f29 = 1.0 / var_f29;
        for (i = 0; i < 3; i++) {
            *(arg3++) = var_f29 * spC[i];
        }
    }
    else {
        *(arg3++) = 0.0f;
        *(arg3++) = 0.0f;
        *(arg3++) = 1.0f;
    }
}

static void fn_1_4FF4(float *arg0, float *arg1, float *arg2, s32 arg3)
{
    float sp48[16];
    float sp8[16];
    double temp_f31;
    s32 i;

    arg2[0] = 0.0f;
    arg2[arg3 - 1] = 0.0f;
    for (i = 0; i < arg3 - 1; i++) {
        sp48[i] = arg0[i + 1] - arg0[i];
        if (sp48[i] == 0.0f) {
            sp8[i + 1] = 0.0f;
        }
        else {
            sp8[i + 1] = (arg1[i + 1] - arg1[i]) / sp48[i];
        }
    }
    arg2[1] = sp8[2] - sp8[1];
    sp8[1] = 2.0f * (arg0[2] - arg0[0]);
    for (i = 1; i < arg3 - 2; i++) {
        temp_f31 = sp48[i] / sp8[i];
        arg2[i + 1] = sp8[i + 2] - sp8[i + 1] - temp_f31 * arg2[i];
        sp8[i + 1] = 2.0f * (arg0[i + 2] - arg0[i]) - temp_f31 * sp48[i];
    }
    arg2[arg3 - 2] -= sp48[arg3 - 2] * arg2[arg3 - 1];
    for (i = arg3 - 2; i > 0; i--) {
        if (sp8[i] == 0.0f) {
            arg2[i] = 0.0f;
        }
        else {
            arg2[i] = (arg2[i] - sp48[i] * arg2[i + 1]) / sp8[i];
        }
    }
}

static float fn_1_52AC(float arg0, float *arg1, float *arg2, float *arg3, s32 arg4)
{
    float temp_f31;
    float temp_f30;
    float var_f29;
    s32 temp_r31;

    temp_r31 = arg0;
    arg0 -= temp_r31;
    temp_f31 = arg1[temp_r31 + 1] - arg1[temp_r31];
    temp_f30 = temp_f31 * arg0;
    var_f29 = arg2[temp_r31]
        + temp_f30
            * (temp_f30 * (3.0f * arg3[temp_r31] + temp_f30 * (arg3[temp_r31 + 1] - arg3[temp_r31]) / temp_f31)
                + ((arg2[temp_r31 + 1] - arg2[temp_r31]) / temp_f31 - temp_f31 * (2.0f * arg3[temp_r31] + arg3[temp_r31 + 1])));
    if (temp_f31 == 0.0f) {
        var_f29 = arg2[temp_r31];
    }
    return var_f29;
}

static void fn_1_5400(float *arg0, Vec *arg1, float arg2[][3], s32 arg3)
{
    Vec sp8;
    float temp_f31;
    float spD4[16];
    float sp94[16];
    s32 j;
    s32 i;

    arg0[0] = 0.0f;
    for (i = 1; i < arg3; i++) {
        VECSubtract(&arg1[i], &arg1[i - 1], &sp8);
        arg0[i] = arg0[i - 1] + VECMag(&sp8);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < arg3; i++) {
            spD4[i] = ((float *)&arg1[i])[j];
        }
        fn_1_4FF4(arg0, spD4, sp94, arg3);
        for (i = 0; i < arg3; i++) {
            arg2[i][j] = sp94[i];
        }
    }
}

static void fn_1_57E0(float arg0, Vec *arg1, float *arg2, Vec *arg3, float arg4[][3], s32 arg5)
{
    float sp48[16];
    float sp8[16];
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < arg5; j++) {
            sp48[j] = ((float *)&arg3[j])[i];
            sp8[j] = arg4[j][i];
        }
        ((float *)arg1)[i] = fn_1_52AC(arg0, arg2, sp48, sp8, arg5);
    }
}

static float fn_1_59F4(Vec *arg0)
{
    float var_f30;
    float var_f29;

    var_f30 = arg0->x * arg0->x + arg0->y * arg0->y + arg0->z * arg0->z;
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

static void fn_1_5B8C(Vec arg0, Vec arg1, Vec *arg2, float arg3)
{
    if (arg3 <= 0.0f) {
        arg2->x = arg0.x;
        arg2->y = arg0.y;
        arg2->z = arg0.z;
        arg3 = 0.0f;
    }
    else if (arg3 >= 1.0f) {
        arg2->x = arg0.x + arg1.x;
        arg2->y = arg0.y + arg1.y;
        arg2->z = arg0.z + arg1.z;
        arg3 = 1.0f;
    }
    else {
        arg2->x = arg0.x + arg3 * arg1.x;
        arg2->y = arg0.y + arg3 * arg1.y;
        arg2->z = arg0.z + arg3 * arg1.z;
    }
}

static float fn_1_5C64(Vec arg0, Vec arg1, Vec arg2)
{
    float var_f31;
    float temp_f30;

    var_f31 = arg2.x * (arg1.x - arg0.x) + arg2.y * (arg1.y - arg0.y) + arg2.z * (arg1.z - arg0.z);
    temp_f30 = -(arg2.x * arg2.x + arg2.y * arg2.y + arg2.z * arg2.z);
    if (temp_f30 != 0.0f) {
        var_f31 /= temp_f30;
    }
    return var_f31;
}

static float fn_1_5D20(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Vec sp44;
    float var_f31;

    if (arg2->x * arg2->x + arg2->y * arg2->y + arg2->z * arg2->z == 0.0f) {
        return (arg0->x - arg1->x) * (arg0->x - arg1->x) + (arg0->y - arg1->y) * (arg0->y - arg1->y) + (arg0->z - arg1->z) * (arg0->z - arg1->z);
    }
    var_f31 = fn_1_5C64(*arg0, *arg1, *arg2);
    fn_1_5B8C(*arg1, *arg2, &sp44, var_f31);
    return (arg0->x - sp44.x) * (arg0->x - sp44.x) + (arg0->y - sp44.y) * (arg0->y - sp44.y) + (arg0->z - sp44.z) * (arg0->z - sp44.z);
}

static float fn_1_605C(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4)
{
    float var_f27;

    if (arg2->x * arg2->x + arg2->y * arg2->y + arg2->z * arg2->z == 0.0f) {
        return (arg0->x - arg1->x) * (arg0->x - arg1->x) + (arg0->y - arg1->y) * (arg0->y - arg1->y) + (arg0->z - arg1->z) * (arg0->z - arg1->z);
    }
    var_f27 = fn_1_5C64(*arg0, *arg1, *arg2);
    fn_1_5B8C(*arg1, *arg2, arg3, var_f27);
    arg4->x = arg3->x - arg0->x;
    arg4->y = arg3->y - arg0->y;
    arg4->z = arg3->z - arg0->z;
    return fn_1_59F4(arg4);
}
