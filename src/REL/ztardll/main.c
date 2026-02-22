#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "REL/ztardll.h"
#include "game/frand.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#endif

extern s32 charVoiceGroupStat[8];

void fn_1_1774(void);
void fn_1_1CF0(void);
void fn_1_1DA0(void);
void fn_1_2350(void);
void fn_1_33B0(void);
void fn_1_40E4(void);
void fn_1_424(void);
void fn_1_4374(void);
void fn_1_4948(void);
void fn_1_51BC(s16 arg0);
s32 fn_1_524C(s32 arg0);
void fn_1_66F8(void);
void fn_1_7414(ModelData *model, Mtx matrix);

omObjData *lbl_1_bss_6C;
Process *lbl_1_bss_68;
s32 lbl_1_bss_64;
s32 lbl_1_bss_60;
s16 lbl_1_bss_5E;
s16 lbl_1_bss_5C;

s16 lbl_1_bss_5A;
s16 lbl_1_bss_58;
s32 lbl_1_bss_54;
s16 lbl_1_bss_52;
s16 lbl_1_bss_50;
s16 lbl_1_bss_4C[2];
s16 lbl_1_bss_4A;
s16 lbl_1_bss_48;
s16 lbl_1_bss_46;
s16 lbl_1_bss_44;
s16 lbl_1_bss_42;
s16 lbl_1_bss_3E[2];
s16 lbl_1_bss_36[4];
s16 lbl_1_bss_E[4][5];
s16 lbl_1_bss_C;
Process *lbl_1_bss_8;
s16 lbl_1_bss_4;
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    s32 var_r31;
    s32 var_r30;

    OSReport("******* ZP ObjectSetup *********\n");
    lbl_1_bss_68 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_60 = 0;
    lbl_1_bss_58 = omovlevtno;
    _ClearFlag(0x10000);
    _ClearFlag(0x10008);
    GWSystem.mg_type = -1;
    GWSystem.player_curr = 0;
    lbl_1_bss_5E = -1;
    mgBoardHostEnableF = 1;
    var_r30 = omMgIndexGet(0x29);
    lbl_1_bss_54 = GWMGAvailGet(var_r30 + 0x191);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 90.0f;
    Center.z = 30.0f;
    CZoom = 1220.0f;
    var_r31 = Hu3DGLightCreate(0.0f, 100.0f, 1000.0f, 0.0f, -0.5f, -1.0f, 0xFF, 0xFF, 0xFF);
    Hu3DGLightInfinitytSet(var_r31);
    HuPrcChildCreate(fn_1_424, 0x64, 0x3000, 0, lbl_1_bss_68);
    HuPrcChildCreate(fn_1_66F8, 0xC8, 0x1000, 0, lbl_1_bss_68);
    lbl_1_bss_6C = omAddObjEx(lbl_1_bss_68, 0x7FDA, 0, 0, -1, omOutView);
    Hu3DBGColorSet(0, 0, 0);
    HuWinInit(1);
    if (lbl_1_bss_58 == 1) {
        HuAudVoiceInit(-1);
    }
    if (lbl_1_bss_58 != 0) {
        HuAudSndGrpSetSet(4);
        HuAudSeqPlay(0x2E);
    }
    GWSystem.mg_type = -1;
    mgPracticeEnableF = 1;
}

s16 lbl_1_data_22[4] = { 0x3A, 0xC8, 0x166, 0xC8 };

void fn_1_424(void)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    s16 var_r31;
    s16 var_r30;
    s16 var_r29;
    s16 var_r28;
    s16 var_r27;
    s16 var_r26;

    var_r26 = 0;
    var_r27 = 0;
    fn_1_7D6C(lbl_1_bss_68);
    HuPrcVSleep();
    HuDataDirClose(DATADIR_MPEX);
    lbl_1_bss_5A = 0;
    if (mgQuitExtraF != 0) {
        mgQuitExtraF = 0;
        var_r26 = 1;
        lbl_1_bss_58 = 0;
    }
    else {
        if (lbl_1_bss_58 == 1) {
            lbl_1_bss_5A = 0;
            goto block_92;
        }
        if (lbl_1_bss_58 == 2) {
            lbl_1_bss_5A = 1;
            goto block_93;
        }
        GWPlayerCfg[0].group = GWPlayerCfg[1].group = 0;
        GWPlayerCfg[2].group = GWPlayerCfg[3].group = 1;
    }
block_7:
    fn_1_1774();
    if (lbl_1_bss_54 == 0) {
        HuSprTPLvlSet(lbl_1_bss_4C[1], 0, 0.5f);
        HuSprTPLvlSet(lbl_1_bss_4C[1], 2, 0.5f);
    }
    if (var_r26 == 0) {
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
        HuPrcSleep(0xA);
        sp2C.x = 510.0f;
        sp2C.y = 80.0f;
        sp2C.z = 1500.0f;
        Hu3D2Dto3D(&sp2C, 1, &sp8);
        sp2C.x = 200.0f;
        sp2C.y = 400.0f;
        sp2C.z = 100.0f;
        Hu3D2Dto3D(&sp2C, 1, &sp20);
        VECSubtract(&sp8, &sp20, &sp14);
        for (var_r31 = 0; var_r31 <= 0x1E; var_r31++) {
            if (var_r31 <= 0x14) {
                var_f31 = var_r31 / 20.0;
                HuSprGrpPosSet(lbl_1_bss_52, 288.0f, 80.0 - (180.0 * (1.0 - sind((90.0f * var_f31)))));
                HuSprGrpPosSet(lbl_1_bss_50, 288.0f, 80.0 - (180.0 * (1.0 - sind((90.0f * var_f31)))));
                HuSprGrpPosSet(lbl_1_bss_4C[0], 138.0 - (300.0 * (1.0 - sind((90.0f * var_f31)))), 240.0f);
                HuSprGrpPosSet(lbl_1_bss_4C[1], 438.0 + (300.0 * (1.0 - sind((90.0f * var_f31)))), 240.0f);
            }
            var_f31 = var_r31 / 30.0;
            VECScale(&sp14, &sp2C, var_f31);
            VECAdd(&sp2C, &sp20, &sp2C);
            Hu3DModelRotSet(lbl_1_bss_42, 0.0f, -10.0f, -15.0f);
            Hu3DModelPosSetV(lbl_1_bss_42, &sp2C);
            HuPrcVSleep();
        }
    }
    else {
        sp2C.x = 510.0f;
        sp2C.y = 80.0f;
        sp2C.z = 1500.0f;
        Hu3D2Dto3D(&sp2C, 1, &sp20);
        Hu3DModelRotSet(lbl_1_bss_42, 0.0f, -10.0f, -15.0f);
        Hu3DModelPosSetV(lbl_1_bss_42, &sp20);
        var_f31 = var_r31 / 20.0;
        HuSprGrpPosSet(lbl_1_bss_52, 288.0f, 80.0f);
        HuSprGrpPosSet(lbl_1_bss_50, 288.0f, 80.0f);
        HuSprGrpPosSet(lbl_1_bss_4C[0], 138.0f, 240.0f);
        HuSprGrpPosSet(lbl_1_bss_4C[1], 438.0f, 240.0f);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
    }
loop_19:
    fn_1_11020();
    fn_1_11264(MAKE_MESSID(0x33, 0x24), 0, 0);
    if (lbl_1_bss_5A == 0) {
        fn_1_11264(MAKE_MESSID(0x33, 0x25), 0, 1);
    }
    else {
        fn_1_11264(MAKE_MESSID(0x33, 0x2A), 0, 1);
    }
    fn_1_11708(MAKE_MESSID(0x33, 0x8D));
    for (var_r31 = 0; var_r31 <= 0x0A; var_r31++) {
        var_f31 = var_r31 / 10.0;

        HuSprTPLvlSet(lbl_1_bss_4A, 0, var_f31);
        HuSprGrpPosSet(lbl_1_bss_4A, lbl_1_data_22[lbl_1_bss_5A * 2], lbl_1_data_22[(lbl_1_bss_5A * 2) + 1]);
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
        if ((HuPadStkX[0] / 10) != 0) {
            var_r29 = lbl_1_bss_5A;
            if (HuPadStkX[0] < 0 && lbl_1_bss_5A > 0) {
                lbl_1_bss_5A--;
            }
            if (HuPadStkX[0] > 0 && lbl_1_bss_5A < 1) {
                lbl_1_bss_5A++;
            }
            if (lbl_1_bss_5A != var_r29) {
                HuAudFXPlay(0);
                for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
                    var_f31 = sind((90.0 * (var_r31 / 10.0)));
                    var_f30 = lbl_1_data_22[var_r29 * 2] + (var_f31 * (lbl_1_data_22[lbl_1_bss_5A * 2] - lbl_1_data_22[var_r29 * 2]));
                    HuSprGrpPosSet(lbl_1_bss_4A, var_f30, lbl_1_data_22[(lbl_1_bss_5A * 2) + 1]);
                    HuPrcVSleep();
                }
                if (lbl_1_bss_5A == 0) {
                    fn_1_11264(MAKE_MESSID(0x33, 0x25), 0, 1);
                }
                else {
                    fn_1_11264(MAKE_MESSID(0x33, 0x2A), 0, 1);
                }
            }
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            fn_1_111E0();
            fn_1_1190C();
            lbl_1_bss_60 = 1;
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            if (lbl_1_bss_5A != 1 || lbl_1_bss_54 != 0) {
                break;
            }
            HuAudFXPlay(4);
        }
    }
    HuAudFXPlay(2);
    fn_1_111E0();
    fn_1_1190C();
    lbl_1_bss_5E = -1;
    var_r29 = lbl_1_bss_5A ^ 1;
    for (var_r31 = 0; var_r31 <= 0x14; var_r31++) {
        if (var_r31 <= 0xA) {
            var_f31 = var_r31 / 10.0;
            HuSprTPLvlSet(lbl_1_bss_4A, 0, 1.0 - var_f31);
        }
        var_f31 = 1.0 - (var_r31 / 20.0);

        HuSprGrpScaleSet(lbl_1_bss_4C[var_r29], var_f31, var_f31);
        if (lbl_1_bss_5A == 0) {
            var_f31 = -var_f31;
        }
        HuSprGrpPosSet(lbl_1_bss_4C[lbl_1_bss_5A], 288.0f + (150.0f * var_f31), 240.0f);
        HuPrcVSleep();
    }
    for (var_r27 = 0;;) {
        if (lbl_1_bss_5A == 0) {
            var_r30 = fn_1_97D0(2, var_r27);
        }
        else {
            var_r30 = fn_1_97D0(3, var_r27);
            if (var_r30 != 0) {
                mgTypeCurr = 2;
                var_r30 = fn_1_524C(1);
                if (var_r30 == 0) {
                    var_r27 = 1;
                    continue;
                }
            }
        }
        if (var_r30 == 0) {
            for (var_r31 = 0; var_r31 <= 0x14; var_r31++) {
                var_f31 = var_r31 / 20.0;
                HuSprGrpScaleSet(lbl_1_bss_4C[var_r29], var_f31, var_f31);
                if (lbl_1_bss_5A != 0) {
                    var_f31 = -var_f31;
                }
                HuSprGrpPosSet(lbl_1_bss_4C[lbl_1_bss_5A], 288.0f - (150.0f * var_f31), 240.0f);
                var_f31 = var_r31 / 20.0;
                if (lbl_1_bss_5A == 0) {
                    var_r28 = -1;
                }
                else {
                    var_r28 = 1;
                }
                HuSprGrpPosSet(lbl_1_bss_46, 288.0 + (var_r28 * (400.0 * (1.0 - cosd((90.0f * var_f31))))), 340.0f);
                HuPrcVSleep();
            }
            goto loop_19;
        }
        var_r27 = 1;
        fn_1_1DA0();
        for (var_r31 = 0; var_r31 <= 0x14; var_r31++) {
            var_f31 = var_r31 / 20.0;
            if (lbl_1_bss_5A == 0) {
                var_r28 = -1;
            }
            else {
                var_r28 = 1;
            }
            HuSprGrpPosSet(lbl_1_bss_46, 288.0 + (var_r28 * (400.0 * (1.0 - sind((90.0f * var_f31))))), 340.0f);
            HuPrcVSleep();
        }
        if (lbl_1_bss_5A == 0) {
            fn_1_40E4();
        }
        if (lbl_1_bss_4 == 0) {
            lbl_1_bss_4 = 1;
            HuPrcChildCreate(fn_1_7C00, 0x64, 0x2000, 0, lbl_1_bss_68);
        }
        fn_1_11020();
        fn_1_11264(MAKE_MESSID(0x33, 0x2C), 0, 0);
        var_r30 = fn_1_11390(0);
        if (var_r30 != -1) {
            if (var_r30 != 1) {
                break;
            }
        }
        fn_1_111E0();
        for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
            var_f31 = cosd((90.0 * (var_r31 / 10.0)));
            HuSprGrpScaleSet(lbl_1_bss_46, 1.0f, var_f31);
            HuPrcVSleep();
        }
        HuSprGrpKill(lbl_1_bss_46);
    }
    fn_1_111E0();
    fn_1_1190C();
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    mgBattleStarMax = 0;
    HuSprGrpKill(lbl_1_bss_48);
    HuSprGrpKill(lbl_1_bss_52);
    HuSprGrpKill(lbl_1_bss_50);
    HuSprGrpKill(lbl_1_bss_4C[0]);
    HuSprGrpKill(lbl_1_bss_4C[1]);
    HuSprGrpKill(lbl_1_bss_4A);
    HuSprGrpKill(lbl_1_bss_46);
    Hu3DModelKill(lbl_1_bss_42);
    HuPrcKill(lbl_1_bss_8);
    while (lbl_1_bss_4 != 0) {
        HuPrcVSleep();
    }
    if (lbl_1_bss_5A == 0) {
    block_92:
        fn_1_2350();
    }
    else {
    block_93:
        fn_1_4374();
    }
    var_r26 = 1;
    goto block_7;
}

void fn_1_1774(void)
{
    SeqWork work;
    s16 var_r31;
    s16 var_r30;
    char *var_r29;
    s16 var_r28;
    AnimData *var_r27;
    char *var_r26;
    AnimData *var_r25;
    AnimData *var_r24;
    AnimData *var_r23;

    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 3));
    lbl_1_bss_48 = HuSprGrpCreate(1);
    var_r31 = HuSprCreate(var_r27, 0xC8, 0);
    HuSprGrpMemberSet(lbl_1_bss_48, 0, var_r31);
    HuSprGrpDrawNoSet(lbl_1_bss_48, 0x7F);
    HuSprGrpPosSet(lbl_1_bss_48, 288.0f, 240.0f);
    for (var_r30 = 0; var_r30 < 0x10; var_r30++) {
        work.sprite[var_r30] = work.spr_grp[var_r30] = -1;
    }
    var_r29 = MessData_MesPtrGet(messDataPtr, MAKE_MESSID(0x17, 0x21));
    for (var_r26 = var_r29; *var_r29 != 0; var_r29++) {
        if (*var_r29 == 0xA) {
            *var_r29 = 0x10;
        }
    }
    lbl_1_bss_52 = work.spr_grp[fn_1_7754(&work, var_r26)];
    HuSprGrpPosSet(lbl_1_bss_52, 288.0f, -300.0f);
    HuSprGrpDrawNoSet(lbl_1_bss_52, 0x7F);
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 4));
    lbl_1_bss_50 = HuSprGrpCreate(1);
    var_r31 = HuSprCreate(var_r27, 0x64, 0);
    HuSprGrpMemberSet(lbl_1_bss_50, 0, var_r31);
    HuSprGrpPosSet(lbl_1_bss_50, 288.0f, -300.0f);
    HuSprGrpDrawNoSet(lbl_1_bss_50, 0x7F);
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 5));
    var_r25 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 14));
    var_r24 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 64));
    var_r23 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 15));
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r28 = HuSprGrpCreate(4);
        lbl_1_bss_4C[var_r30] = var_r28;
        var_r31 = HuSprCreate(var_r27, 0x64, var_r30);
        HuSprGrpMemberSet(var_r28, 0, var_r31);
        var_r31 = HuSprCreate(var_r25, 0x6E, 0);
        HuSprGrpMemberSet(var_r28, 1, var_r31);
        var_r31 = HuSprCreate(var_r24, 0x78, 0);
        HuSprGrpMemberSet(var_r28, 2, var_r31);
        HuSprScaleSet(var_r28, 2, 0.5f, 0.5f);
        var_r31 = HuSprCreate(var_r23, 0x82, 0);
        HuSprGrpMemberSet(var_r28, 3, var_r31);
        HuSprGrpPosSet(var_r28, 288.0f, -300.0f);
        HuSprGrpDrawNoSet(var_r28, 0x7F);
    }
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 6));
    lbl_1_bss_4A = HuSprGrpCreate(1);
    var_r31 = HuSprCreate(var_r27, 0x32, 0);
    HuSprGrpMemberSet(lbl_1_bss_4A, 0, var_r31);
    HuSprGrpPosSet(lbl_1_bss_4A, 288.0f, -300.0f);
    lbl_1_bss_42 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_ZTAR, 0));
    lbl_1_bss_3E[0] = Hu3DJointMotionFile(lbl_1_bss_42, DATA_MAKE_NUM(DATADIR_ZTAR, 1));
    lbl_1_bss_3E[1] = Hu3DJointMotionFile(lbl_1_bss_42, DATA_MAKE_NUM(DATADIR_ZTAR, 2));
    Hu3DMotionSet(lbl_1_bss_42, lbl_1_bss_3E[0]);
    Hu3DModelAttrSet(lbl_1_bss_42, HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(lbl_1_bss_42, 0.0f, 1000.0f, 0.0f);
    lbl_1_bss_8 = HuPrcChildCreate(fn_1_1CF0, 0x64, 0x2000, 0, lbl_1_bss_68);
}

void fn_1_1CF0(void)
{
    float var_f31 = 0.0f;
    ModelData *var_r31 = &Hu3DData[lbl_1_bss_42];

    while (TRUE) {
        var_r31->pos.y += sind(var_f31);
        var_f31 += 3.0f;
        if (var_f31 > 360.0f) {
            var_f31 -= 360.0f;
        }
        HuPrcVSleep();
    }
}

void fn_1_1DA0(void)
{
    s16 spC[4];
    s16 sp8[2];
    s16 var_r31;
    AnimData *var_r30;
    s16 var_r29;
    s16 var_r28;
    s16 var_r27;

    sp8[0] = 0;
    sp8[1] = 2;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        spC[sp8[GWPlayerCfg[var_r31].group]++] = var_r31;
    }
    if (lbl_1_bss_5A == 0) {
        var_r28 = HuSprGrpCreate(5);
        lbl_1_bss_46 = var_r28;
        var_r30 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 17));
        var_r29 = HuSprCreate(var_r30, 0x78, 0);
        HuSprGrpMemberSet(var_r28, 0, var_r29);
        for (var_r31 = 0; var_r31 < 2; var_r31++) {
            var_r30 = HuSprAnimReadFile(GWPlayerCfg[spC[var_r31]].character + DATA_MAKE_NUM(DATADIR_ZTAR, 18));
            var_r29 = HuSprCreate(var_r30, 0x6E, 0);
            HuSprGrpMemberSet(var_r28, (var_r31 * 2) + 1, var_r29);
            HuSprPosSet(var_r28, (var_r31 * 2) + 1, (var_r31 * 0x30) - 0x18, -4.0f);
            if (GWPlayerCfg[spC[var_r31]].iscom == 0) {
                var_r30 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 32));
                var_r29 = HuSprCreate(var_r30, 0x64, spC[var_r31]);
            }
            else {
                var_r30 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 33));
                var_r29 = HuSprCreate(var_r30, 0x64, GWPlayerCfg[spC[var_r31]].diff);
            }
            HuSprGrpMemberSet(var_r28, (var_r31 * 2) + 2, var_r29);
            HuSprPosSet(var_r28, (var_r31 * 2) + 2, (var_r31 * 0x30) - 0x18, 20.0f);
        }
    }
    else {
        var_r28 = HuSprGrpCreate(0xA);
        lbl_1_bss_46 = var_r28;
        var_r30 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 16));
        var_r29 = HuSprCreate(var_r30, 0x78, 0);
        HuSprGrpMemberSet(var_r28, 0, var_r29);
        var_r27 = -0x4B;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            var_r30 = HuSprAnimReadFile(GWPlayerCfg[spC[var_r31]].character + DATA_MAKE_NUM(DATADIR_ZTAR, 18));
            var_r29 = HuSprCreate(var_r30, 0x6E, 0);
            HuSprGrpMemberSet(var_r28, (var_r31 * 2) + 1, var_r29);
            HuSprPosSet(var_r28, (var_r31 * 2) + 1, var_r27, 0.0f);
            if (GWPlayerCfg[spC[var_r31]].iscom == 0) {
                var_r30 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 32));
                var_r29 = HuSprCreate(var_r30, 0x64, spC[var_r31]);
            }
            else {
                var_r30 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 33));
                var_r29 = HuSprCreate(var_r30, 0x64, GWPlayerCfg[spC[var_r31]].diff);
            }
            HuSprGrpMemberSet(var_r28, (var_r31 * 2) + 2, var_r29);
            HuSprPosSet(var_r28, (var_r31 * 2) + 2, var_r27, 22.0f);
            var_r27 += 0x2A;
            if (var_r31 == 1) {
                var_r27 += 0x18;
            }
        }
        var_r30 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 10));
        var_r29 = HuSprCreate(var_r30, 0x5A, 0);
        HuSprGrpMemberSet(var_r28, 9, var_r29);
    }
    HuSprGrpPosSet(var_r28, 0.0f, -100.0f);
}

void fn_1_2350(void)
{
    s16 spC[4];
    s16 sp8[2];
    float var_f31;
    s16 var_r31;

    sp8[0] = 0;
    sp8[1] = 2;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        spC[sp8[GWPlayerCfg[var_r31].group]++] = var_r31;
    }
    if (lbl_1_bss_58 != 0) {
        if (GWPlayerCoinWinGet(spC[0]) > 0) {
            mgBattleStarMax++;
        }
    }
    fn_1_33B0();
    Hu3DModelPosSet(lbl_1_bss_36[2], 500.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_36[3], 500.0f, 0.0f, 0.0f);
    HuSprScaleSet(lbl_1_bss_50, 2, 0.0f, 0.0f);
    if (lbl_1_bss_58 != 0) {
        if (GWPlayerCoinWinGet(spC[0]) == 0) {
            mgBattleStarMax++;
        }
        HuSprBankSet(lbl_1_bss_50, 1, mgBattleStarMax);
        HuSprScaleSet(lbl_1_bss_50, 1, 1.0f, 1.0f);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        HuPrcSleep(0x1E);
        if (GWPlayerCoinWinGet(spC[0]) > 0) {
            HuSprAttrReset(lbl_1_bss_44, 6, 4);
            HuSprPosSet(lbl_1_bss_44, 6, ((mgBattleStarMax - 1) << 5) + 0x46, 340.0f);
            for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
                var_f31 = var_r31 / 60.0;
                HuSprTPLvlSet(lbl_1_bss_44, 6, var_f31);
                var_f31 = 1.0 + (5.0 * cosd((90.0f * var_f31)));
                HuSprScaleSet(lbl_1_bss_44, 6, var_f31, var_f31);
                if (var_r31 == 0x14) {
                    HuAudFXPlay(0x9A);
                    if (mgBattleStarMax < 6) {
                        Hu3DMotionShiftSet(lbl_1_bss_36[0], lbl_1_bss_E[0][2], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                        Hu3DMotionShiftSet(lbl_1_bss_36[1], lbl_1_bss_E[1][2], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    }
                    else {
                        Hu3DMotionShiftSet(lbl_1_bss_36[0], lbl_1_bss_E[0][3], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                        Hu3DMotionShiftSet(lbl_1_bss_36[1], lbl_1_bss_E[1][3], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    }
                }
                HuPrcVSleep();
            }
            HuAudFXPlay(8);
            if (mgBattleStarMax >= 6) {
                HuPrcSleep(0x3C);
                var_r31 = omMgIndexGet(0x29);
                lbl_1_bss_54 = 1;
                fn_1_11020();
                fn_1_11338(GWPlayerCfg[spC[0]].character, 0);
                fn_1_11338(GWPlayerCfg[spC[1]].character, 1);
                fn_1_11264(MAKE_MESSID(0x33, 0xA0), 0, 0);
                if (GWMGAvailGet(var_r31 + 0x191) == 0) {
                    GWMGAvailSet(var_r31 + 0x191);
                    GWGameStat.present[0x37] = 1;
                    fn_1_11264(MAKE_MESSID(0x33, 0x29), 0, 0);
                }
                fn_1_111E0();
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                while (WipeStatGet() != 0) {
                    HuPrcVSleep();
                }
            }
            else {
                Hu3DMotionShiftSet(lbl_1_bss_36[0], lbl_1_bss_E[0][0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                Hu3DMotionShiftSet(lbl_1_bss_36[1], lbl_1_bss_E[1][0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
                    var_f31 = 1.0 - (var_r31 / 10.0);
                    HuSprScaleSet(lbl_1_bss_50, 1, var_f31, var_f31);
                    HuPrcVSleep();
                }
                HuPrcSleep(0x3C);
                goto block_39;
            }
        }
        else {
            Hu3DMotionShiftSet(lbl_1_bss_36[0], lbl_1_bss_E[0][4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            Hu3DMotionShiftSet(lbl_1_bss_36[1], lbl_1_bss_E[1][4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            HuPrcSleep(0xB4);
            WipeColorSet(0, 0, 0);
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
            while (WipeStatGet() != 0) {
                HuPrcVSleep();
            }
        }
    }
    else {
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        HuPrcSleep(0x1E);
    block_39:
        Hu3DMotionSet(lbl_1_bss_36[2], lbl_1_bss_E[2][1]);
        Hu3DMotionSet(lbl_1_bss_36[3], lbl_1_bss_E[3][1]);
        Hu3DModelRotSet(lbl_1_bss_36[2], 0.0f, -90.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_36[3], 0.0f, -90.0f, 0.0f);
        HuSprBankSet(lbl_1_bss_50, 1, mgBattleStarMax + 1);
        for (var_r31 = 0; var_r31 <= 0x1E; var_r31++) {
            var_f31 = 1.0 - sind((90.0 * (var_r31 / 30.0)));
            Hu3DModelPosSet(lbl_1_bss_36[2], 125.0f + (400.0f * var_f31), 0.0f, 0.0f);
            Hu3DModelPosSet(lbl_1_bss_36[3], 275.0f + (400.0f * var_f31), 0.0f, 0.0f);
            if (var_r31 == 0x19) {
                Hu3DMotionShiftSet(lbl_1_bss_36[2], lbl_1_bss_E[2][0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                Hu3DMotionShiftSet(lbl_1_bss_36[3], lbl_1_bss_E[3][0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
            }
            if ((GWPlayerCfg[2].character < 8) && ((var_r31 % 5) == 0)) {
                HuAudFXPlay(GWPlayerCfg[2].character + 0xD5);
            }
            if ((GWPlayerCfg[3].character < 8) && (((var_r31 + 3) % 5) == 0)) {
                HuAudFXPlay(GWPlayerCfg[3].character + 0xD5);
            }
            if (var_r31 > 0x14) {
                var_f31 = 1.0 - ((var_r31 - 0x14) / 10.0);
                Hu3DModelRotSet(lbl_1_bss_36[2], 0.0f, 90.0f * -var_f31, 0.0f);
                Hu3DModelRotSet(lbl_1_bss_36[3], 0.0f, 90.0f * -var_f31, 0.0f);
            }
            if (var_r31 <= 0x14) {
                var_f31 = 1.2 * sind((90.0 * (var_r31 / 20.0)));
                HuSprScaleSet(lbl_1_bss_50, 1, var_f31, var_f31);
            }
            else if (var_r31 > 0x14) {
                var_f31 = 1.0 + (0.2 * cosd((90.0 * ((var_r31 - 0x14) / 10.0))));
                HuSprScaleSet(lbl_1_bss_50, 1, var_f31, var_f31);
            }
            HuPrcVSleep();
        }
        HuAudFXPlay(0x355);
        for (var_r31 = 0; var_r31 <= 0x14; var_r31++) {
            var_f31 = 1.0 + (5.0 * cosd((90.0 * (var_r31 / 20.0))));
            HuSprScaleSet(lbl_1_bss_50, 2, var_f31, var_f31);
            HuSprTPLvlSet(lbl_1_bss_50, 2, var_r31 / 20.0);
            HuPrcVSleep();
        }
        fn_1_114EC(MAKE_MESSID(0x33, 0x4F), 1);
        while (TRUE) {
            if ((*HuPadBtnDown & 0x100) != 0) {
                HuAudFXPlay(2);
                if (mgBattleStarMax >= 5) {
                    GWSystem.mg_type = 0;
                }
                fn_1_51BC(1);
            }
            if ((*HuPadBtnDown & 0x200) != 0) {
                break;
            }
            HuPrcVSleep();
        }
        HuAudFXPlay(3);
        fn_1_1190C();
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
    }
    HuSprGrpKill(lbl_1_bss_48);
    HuSprGrpKill(lbl_1_bss_50);
    HuSprGrpKill(lbl_1_bss_44);
    Hu3DModelKill(lbl_1_bss_42);
    HuPrcKill(lbl_1_bss_8);
    Hu3DModelKill(lbl_1_bss_C);
    CharModelKill(-1);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayerCfg[spC[var_r31]].character >= 8) {
            Hu3DModelKill(lbl_1_bss_36[var_r31]);
            Hu3DMotionKill(lbl_1_bss_E[var_r31][0]);
            Hu3DMotionKill(lbl_1_bss_E[var_r31][1]);
        }
    }
    lbl_1_bss_58 = 0;
    lbl_1_bss_5A = 0;
}

s32 lbl_1_data_2C[6] = {
    DATA_MAKE_NUM(DATADIR_ZTAR, 59),
    DATA_MAKE_NUM(DATADIR_ZTAR, 34),
    DATA_MAKE_NUM(DATADIR_ZTAR, 39),
    DATA_MAKE_NUM(DATADIR_ZTAR, 44),
    DATA_MAKE_NUM(DATADIR_ZTAR, 49),
    DATA_MAKE_NUM(DATADIR_ZTAR, 54),
};

u8 lbl_1_data_44[6] = { 0, 1, 1, 2, 2, 3 };

void fn_1_33B0(void)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    s16 spC[4];
    s16 sp8[2];
    s16 var_r31;
    s16 var_r30;
    AnimData *var_r29;
    s16 var_r28;
    s16 var_r27;
    s16 var_r26;
    s16 var_r25;
    s16 var_r24;
    AnimData *var_r23;

    sp8[0] = 0;
    sp8[1] = 2;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        spC[sp8[GWPlayerCfg[var_r31].group]++] = var_r31;
    }
    var_r29 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 3));
    lbl_1_bss_48 = HuSprGrpCreate(1);
    var_r30 = HuSprCreate(var_r29, 0xC8, 0);
    HuSprGrpMemberSet(lbl_1_bss_48, 0, var_r30);
    HuSprGrpDrawNoSet(lbl_1_bss_48, 0x7F);
    HuSprGrpPosSet(lbl_1_bss_48, 288.0f, 240.0f);
    lbl_1_bss_50 = HuSprGrpCreate(3);
    var_r29 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 12));
    var_r30 = HuSprCreate(var_r29, 0x78, 0);
    HuSprGrpMemberSet(lbl_1_bss_50, 0, var_r30);
    HuSprPosSet(lbl_1_bss_50, 0, 288.0f, 80.0f);
    var_r29 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 11));
    if ((mgBattleStarMax + 1) >= 7) {
        var_r30 = HuSprCreate(var_r29, 0x64, 6);
    }
    else {
        var_r30 = HuSprCreate(var_r29, 0x64, mgBattleStarMax + 1);
    }
    HuSprGrpMemberSet(lbl_1_bss_50, 1, var_r30);
    HuSprPosSet(lbl_1_bss_50, 1, VERSION_JP ? 234.0f : 342.0f, 80.0f);
    HuSprScaleSet(lbl_1_bss_50, 1, 0.0f, 0.0f);
    HuSprGrpDrawNoSet(lbl_1_bss_50, 0x7F);
    var_r29 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 9));
    var_r30 = HuSprCreate(var_r29, 0x64, 0);
    HuSprGrpMemberSet(lbl_1_bss_50, 2, var_r30);
    HuSprPosSet(lbl_1_bss_50, 2, 288.0f, 240.0f);
    HuSprDrawNoSet(lbl_1_bss_50, 2, 0);
    HuSprGrpPosSet(lbl_1_bss_50, 0.0f, 0.0f);
    var_r27 = HuSprGrpCreate(7);
    lbl_1_bss_44 = var_r27;
    var_r29 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 8));
    var_r23 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 7));
    var_r24 = mgBattleStarMax;
    if (GWPlayerCoinWinGet(spC[0]) > 0) {
        var_r24--;
    }
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (var_r31 >= var_r24) {
            var_r30 = HuSprCreate(var_r23, 0x64, 0);
        }
        else {
            var_r30 = HuSprCreate(var_r29, 0x64, 0);
        }
        HuSprGrpMemberSet(var_r27, var_r31, var_r30);
        HuSprPosSet(var_r27, var_r31, (var_r31 << 5) + 0x46, 340.0f);
    }
    var_r30 = HuSprCreate(var_r29, 0x5A, 0);
    HuSprGrpMemberSet(var_r27, 6, var_r30);
    HuSprAttrSet(var_r27, 6, 4);
    HuSprGrpPosSet(var_r27, 0.0f, 0.0f);
    sp38.x = 510.0f;
    sp38.y = 80.0f;
    sp38.z = 1500.0f;
    Hu3D2Dto3D(&sp38, 1, &sp2C);
    lbl_1_bss_42 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_ZTAR, 0));
    lbl_1_bss_3E[0] = Hu3DJointMotionFile(lbl_1_bss_42, DATA_MAKE_NUM(DATADIR_ZTAR, 1));
    lbl_1_bss_3E[1] = Hu3DJointMotionFile(lbl_1_bss_42, DATA_MAKE_NUM(DATADIR_ZTAR, 2));
    Hu3DModelAttrSet(lbl_1_bss_42, HU3D_MOTATTR_LOOP);
    Hu3DModelPosSetV(lbl_1_bss_42, &sp2C);
    Hu3DModelRotSet(lbl_1_bss_42, 0.0f, -10.0f, -15.0f);
    Hu3DMotionSet(lbl_1_bss_42, lbl_1_bss_3E[0]);
    lbl_1_bss_8 = HuPrcChildCreate(fn_1_1CF0, 0x64, 0x2000, 0, lbl_1_bss_68);
    GWPlayerCfg[spC[2]].character = mgIndexList[mgBattleStarMax * 2];
    GWPlayerCfg[spC[3]].character = mgIndexList[mgBattleStarMax * 2 + 1];
    GWPlayerCfg[spC[0]].group = GWPlayerCfg[spC[1]].group = 0;
    GWPlayerCfg[spC[2]].group = GWPlayerCfg[spC[3]].group = 1;
    GWPlayerCfg[spC[2]].iscom = GWPlayerCfg[spC[3]].iscom = 1;
    GWPlayerCfg[spC[2]].diff = GWPlayerCfg[spC[3]].diff = lbl_1_data_44[mgBattleStarMax];
    var_r26 = -0x113;
    if (lbl_1_bss_58 != 0) {
        CharKill(-1);
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (GWPlayerCfg[spC[var_r31]].character < 8) {
                CharARAMOpen(GWPlayerCfg[spC[var_r31]].character);
            }
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r28 = GWPlayerCfg[spC[var_r31]].character;
        if (var_r28 != 0xFF) {
            if (var_r28 < 8) {
                lbl_1_bss_36[var_r31] = CharModelCreate(var_r28, 2);
                lbl_1_bss_E[var_r31][0] = CharModelMotionCreate(var_r28, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
                lbl_1_bss_E[var_r31][1] = CharModelMotionCreate(var_r28, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03));
                if (var_r31 < 2) {
                    lbl_1_bss_E[var_r31][2] = CharModelMotionCreate(var_r28, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x48));
                    lbl_1_bss_E[var_r31][3] = CharModelMotionCreate(var_r28, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17));
                    lbl_1_bss_E[var_r31][4] = CharModelMotionCreate(var_r28, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18));
                }
                CharModelVoiceEnableSet(GWPlayerCfg[spC[var_r31]].character, lbl_1_bss_E[var_r31][1], 0);
                Hu3DModelScaleSet(lbl_1_bss_36[var_r31], 0.8f, 0.8f, 0.8f);
            }
            else {
                var_r25 = var_r28 - 8;
                lbl_1_bss_36[var_r31] = Hu3DModelCreateFile(lbl_1_data_2C[var_r25]);
                lbl_1_bss_E[var_r31][0] = Hu3DJointMotionFile(lbl_1_bss_36[var_r31], lbl_1_data_2C[var_r25] + 1);
                lbl_1_bss_E[var_r31][1] = Hu3DJointMotionFile(lbl_1_bss_36[var_r31], lbl_1_data_2C[var_r25] + 2);
                Hu3DModelScaleSet(lbl_1_bss_36[var_r31], 0.8f, 0.8f, 0.8f);
            }
            Hu3DMotionSet(lbl_1_bss_36[var_r31], lbl_1_bss_E[var_r31][0]);
            Hu3DModelAttrSet(lbl_1_bss_36[var_r31], HU3D_MOTATTR_LOOP);
            Hu3DModelPosSet(lbl_1_bss_36[var_r31], var_r26, 0.0f, 0.0f);
            Hu3DModelShadowSet(lbl_1_bss_36[var_r31]);
            var_r26 += 0x96;
            if (var_r31 == 1) {
                var_r26 += 0x64;
            }
        }
    }
    CharModelDataClose(-1);
    Hu3DShadowCreate(20.0f, 500.0f, 8000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowSizeSet(0xC0);
    sp20.x = sp20.y = sp20.z = 0.0f;
    sp38.x = sp38.z = 100.0f;
    sp38.y = 2000.0f;
    sp14.x = sp14.y = 0.0f;
    sp14.z = 1.0f;
    Hu3DShadowPosSet(&sp38, &sp14, &sp20);
    lbl_1_bss_C = Hu3DHookFuncCreate(fn_1_7414);
    Hu3DModelLayerSet(lbl_1_bss_C, 1);
}

void fn_1_40E4(void)
{
    s16 sp14[4];
    s16 spC[4];
    s16 sp8[2];
    s16 var_r31;
    s16 var_r30;
    s16 var_r29;
    s16 var_r28;

    sp8[0] = 0;
    sp8[1] = 2;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        spC[sp8[GWPlayerCfg[var_r31].group]++] = var_r31;
    }
    var_r30 = 0;
    for (var_r31 = var_r30; var_r31 < 8; var_r31++) {
        if ((var_r31 != GWPlayerCfg[spC[0]].character) && (var_r31 != GWPlayerCfg[spC[1]].character)) {
            sp14[var_r30++] = var_r31;
        }
    }
    for (var_r31 = 0; var_r31 < 0x1E; var_r31++) {
        var_r30 = frandmod(6);
        var_r29 = frandmod(6);
        var_r28 = sp14[var_r30];
        sp14[var_r30] = sp14[var_r29];
        sp14[var_r29] = var_r28;
    }
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        mgIndexList[var_r31] = sp14[var_r31];
    }
    mgIndexList[6] = 0xC;
    mgIndexList[7] = 9;
    mgIndexList[8] = 0xB;
    mgIndexList[9] = 0xA;
    mgIndexList[0xA] = 8;
    mgIndexList[0xB] = 0xD;
    mgIndexList[0xC] = mgIndexList[0xD] = 0xFF;
    GWPlayerCfg[spC[2]].character = mgIndexList[0];
    GWPlayerCfg[spC[3]].character = mgIndexList[1];
}

s16 lbl_1_data_4A[6] = { 0x3A, 0x36, 0x40, 0x4B, 0x46, 0x3E };
s16 lbl_1_data_56[7] = { 0x3B, 0x38, 0x42, 0x4D, 0x48, 0x3F, 0 };

void fn_1_4374(void)
{
    s16 spC[4];
    s16 sp8[2];
    float var_f31;
    s16 var_r31;
    s16 var_r30;

    sp8[0] = 0;
    sp8[1] = 2;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        spC[sp8[GWPlayerCfg[var_r31].group]++] = var_r31;
    }
    fn_1_4948();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);
    if (lbl_1_bss_58 != 0) {
        var_r30 = 0;
        for (var_r31 = var_r30; var_r31 < 4; var_r31++) {
            if (GWPlayerCoinWinGet(spC[var_r31]) > 0) {
                if (var_r30 == 0) {
                    HuAudFXPlay(0x9A);
                }
                if (GWPlayerCfg[spC[var_r31]].character >= 8) {
                    HuAudFXPlay(lbl_1_data_4A[GWPlayerCfg[spC[var_r31]].character - 8]);
                }
                Hu3DMotionShiftSet(lbl_1_bss_36[var_r31], lbl_1_bss_E[var_r31][3], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                var_r30++;
            }
            else {
                if (GWPlayerCfg[spC[var_r31]].character >= 8) {
                    HuAudFXPlay(lbl_1_data_56[GWPlayerCfg[spC[var_r31]].character - 8]);
                }
                Hu3DMotionShiftSet(lbl_1_bss_36[var_r31], lbl_1_bss_E[var_r31][4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            }
        }
        HuSprAttrReset(lbl_1_bss_50, 1, 4);
        HuPrcSleep(0x78);
    }
    else {
        HuAudFXPlay(0x355);
        HuSprAttrReset(lbl_1_bss_50, 1, 4);
        for (var_r31 = 0; var_r31 <= 0x14; var_r31++) {
            var_f31 = 1.0 + (5.0 * cosd((90.0 * (var_r31 / 20.0))));

            HuSprScaleSet(lbl_1_bss_50, 1, var_f31, var_f31);
            HuSprTPLvlSet(lbl_1_bss_50, 1, var_r31 / 20.0);
            HuPrcVSleep();
        }
    }
    fn_1_114EC(MAKE_MESSID(0x33, 0x4F), 1);
    while (TRUE) {
        if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            HuAudFXPlay(2);
            fn_1_51BC(2);
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            break;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(3);
    fn_1_1190C();
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuSprGrpKill(lbl_1_bss_48);
    HuSprGrpKill(lbl_1_bss_50);
    Hu3DModelKill(lbl_1_bss_42);
    HuPrcKill(lbl_1_bss_8);
    Hu3DModelKill(lbl_1_bss_C);
    CharModelKill(-1);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayerCfg[spC[var_r31]].character >= 8) {
            Hu3DModelKill(lbl_1_bss_36[var_r31]);
            Hu3DMotionKill(lbl_1_bss_E[var_r31][0]);
            Hu3DMotionKill(lbl_1_bss_E[var_r31][1]);
        }
    }
    lbl_1_bss_58 = 0;
    lbl_1_bss_5A = 0;
}

void fn_1_4948(void)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    s16 spC[4];
    s16 sp8[2];
    s16 var_r31;
    s16 var_r30;
    s16 var_r29;
    s16 var_r28;
    AnimData *var_r27;
    s16 var_r26;
    s16 var_r25;

    sp8[0] = 0;
    sp8[1] = 2;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        spC[sp8[GWPlayerCfg[var_r31].group]++] = var_r31;
    }
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 3));
    lbl_1_bss_48 = HuSprGrpCreate(1);
    var_r29 = HuSprCreate(var_r27, 0xC8, 0);
    HuSprGrpMemberSet(lbl_1_bss_48, 0, var_r29);
    HuSprGrpDrawNoSet(lbl_1_bss_48, 0x7F);
    HuSprGrpPosSet(lbl_1_bss_48, 288.0f, 240.0f);
    lbl_1_bss_50 = HuSprGrpCreate(2);
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 13));
    var_r29 = HuSprCreate(var_r27, 0x78, 0);
    HuSprGrpMemberSet(lbl_1_bss_50, 0, var_r29);
    HuSprPosSet(lbl_1_bss_50, 0, 288.0f, 80.0f);
    HuSprGrpPosSet(lbl_1_bss_50, 0.0f, 0.0f);
    HuSprGrpDrawNoSet(lbl_1_bss_50, 0x7F);
    var_r27 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 9));
    var_r29 = HuSprCreate(var_r27, 0x64, 0);
    HuSprGrpMemberSet(lbl_1_bss_50, 1, var_r29);
    HuSprPosSet(lbl_1_bss_50, 1, 288.0f, 240.0f);
    HuSprAttrSet(lbl_1_bss_50, 1, 4);
    HuSprDrawNoSet(lbl_1_bss_50, 1, 0);
    sp38.x = 510.0f;
    sp38.y = 80.0f;
    sp38.z = 1500.0f;
    Hu3D2Dto3D(&sp38, 1, &sp2C);
    lbl_1_bss_42 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_ZTAR, 0));
    lbl_1_bss_3E[0] = Hu3DJointMotionFile(lbl_1_bss_42, DATA_MAKE_NUM(DATADIR_ZTAR, 1));
    lbl_1_bss_3E[1] = Hu3DJointMotionFile(lbl_1_bss_42, DATA_MAKE_NUM(DATADIR_ZTAR, 2));
    Hu3DModelAttrSet(lbl_1_bss_42, HU3D_MOTATTR_LOOP);
    Hu3DModelPosSetV(lbl_1_bss_42, &sp2C);
    Hu3DModelRotSet(lbl_1_bss_42, 0.0f, -10.0f, -15.0f);
    Hu3DMotionSet(lbl_1_bss_42, lbl_1_bss_3E[0]);
    lbl_1_bss_8 = HuPrcChildCreate(fn_1_1CF0, 0x64, 0x2000, 0, lbl_1_bss_68);
    var_r28 = -0x113;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = GWPlayerCfg[spC[var_r31]].character;
        if (var_r30 < 8) {
            lbl_1_bss_36[var_r31] = CharModelCreate(var_r30, 2);
            lbl_1_bss_E[var_r31][0] = CharModelMotionCreate(var_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
            lbl_1_bss_E[var_r31][3] = CharModelMotionCreate(var_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17));
            lbl_1_bss_E[var_r31][4] = CharModelMotionCreate(var_r30, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18));
            Hu3DModelScaleSet(lbl_1_bss_36[var_r31], 0.8f, 0.8f, 0.8f);
        }
        else {
            var_r26 = var_r30 - 8;
            var_r25 = Hu3DModelCreateFile(lbl_1_data_2C[var_r26]);
            lbl_1_bss_36[var_r31] = var_r25;
            lbl_1_bss_E[var_r31][0] = Hu3DJointMotionFile(var_r25, lbl_1_data_2C[var_r26] + 1);
            lbl_1_bss_E[var_r31][3] = Hu3DJointMotionFile(var_r25, lbl_1_data_2C[var_r26] + 3);
            lbl_1_bss_E[var_r31][4] = Hu3DJointMotionFile(var_r25, lbl_1_data_2C[var_r26] + 4);
            Hu3DModelScaleSet(lbl_1_bss_36[var_r31], 0.8f, 0.8f, 0.8f);
        }
        Hu3DMotionSet(lbl_1_bss_36[var_r31], lbl_1_bss_E[var_r31][0]);
        Hu3DModelAttrSet(lbl_1_bss_36[var_r31], HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(lbl_1_bss_36[var_r31], var_r28, 0.0f, 0.0f);
        Hu3DModelShadowSet(lbl_1_bss_36[var_r31]);
        var_r28 += 0x96;
        if (var_r31 == 1) {
            var_r28 += 0x64;
        }
    }
    CharModelDataClose(-1);
    Hu3DShadowCreate(20.0f, 500.0f, 8000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowSizeSet(0xC0);
    sp20.x = sp20.y = sp20.z = 0.0f;
    sp38.x = sp38.z = 100.0f;
    sp38.y = 2000.0f;
    sp14.x = sp14.y = 0.0f;
    sp14.z = 1.0f;
    Hu3DShadowPosSet(&sp38, &sp14, &sp20);
    lbl_1_bss_C = Hu3DHookFuncCreate(fn_1_7414);
    Hu3DModelLayerSet(lbl_1_bss_C, 1);
}

void fn_1_51BC(s16 arg0)
{
    s16 var_r31;
    omOvlHisData *var_r30;
    u32 var_r29;

    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
    HuAudSeqAllFadeOut(0x3E8);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
#if !VERSION_ENG
    if ((GWPlayerCfg->character >= 8) && (GWPlayerCfg->character >= 8) && (GWPlayerCfg->character >= 8) && (GWPlayerCfg->character >= 8)) {
        msmMusStopAll(1, 0);
        msmSeStopAll(1, 0);
        var_r29 = OSGetTick();
        while (TRUE) {
            if ((msmMusGetNumPlay(1) != 0) || (msmSeGetNumPlay(1) != 0)) {
                if (((OSGetTick() - var_r29) / (*((u32 *)0x800000F8) / 4 / 1000)) >= 0x1F4) {
                    break;
                }
            }
            else {
                break;
            }
        }
        msmSysDelGroupBase(0);
#if VERSION_PAL
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            charVoiceGroupStat[var_r31] = 0;
        }
#endif
    }
#endif
    var_r30 = omOvlHisGet(0);
    omOvlHisChg(0, OVL_ZTAR, arg0, var_r30->stat);
    omOvlCallEx(OVL_M433, 1, 0, 0);
    while (TRUE) {
        HuPrcVSleep();
    }
}

float lbl_1_data_64[8] = {
    -132.0f,
    -12.0f,
    60.0f,
    132.0f,
    -132.0f,
    -60.0f,
    60.0f,
    132.0f,
};

u8 lbl_1_data_84[16] = { 0, 1, 2, 3, 1, 0, 2, 3, 2, 0, 1, 3, 3, 0, 1, 2 };
u8 lbl_1_data_94[12] = { 0, 1, 2, 3, 0, 2, 1, 3, 0, 3, 1, 2 };

s32 fn_1_524C(s32 arg0)
{
    s16 spC;
    float var_f31;
    float var_f30;
    float var_f29;
    s16 var_r31;
    s16 var_r30;
    float *var_r29;
    s16 var_r28;
    s16 var_r27;
    AnimData *var_r26;
    s16 var_r25;
    s16 var_r24;
    s16 var_r23;
    WindowData *var_r22;

    if (mgTypeCurr == 1) {
        var_r29 = lbl_1_data_64;
        var_f29 = 216.0f;
    }
    else {
        var_r29 = &lbl_1_data_64[4];
        var_f29 = 288.0f;
    }
    var_r28 = HuSprGrpCreate(0x10);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r26 = HuSprAnimReadFile(GWPlayerCfg[var_r31].character + DATA_MAKE_NUM(DATADIR_ZTAR, 69));
        var_r25 = HuSprCreate(var_r26, 4, 0);
        HuSprGrpMemberSet(var_r28, var_r31 * 4, var_r25);
        HuSprPosSet(var_r28, var_r31 * 4, var_r29[var_r31], 0.0f);
        if (mgTypeCurr == 1) {
            if (var_r31 == 0) {
                var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 89));
            }
            else {
                var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 90));
            }
        }
        else if (var_r31 < 2) {
            var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 89));
        }
        else {
            var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 90));
        }
        var_r25 = HuSprCreate(var_r26, 3, 0);
        HuSprGrpMemberSet(var_r28, (var_r31 * 4) + 1, var_r25);
        HuSprPosSet(var_r28, (var_r31 * 4) + 1, var_r29[var_r31], 0.0f);
        if (GWPlayerCfg[var_r31].iscom != 0) {
            var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 87));
        }
        else {
            var_r26 = HuSprAnimReadFile(GWPlayerCfg[var_r31].pad_idx + DATA_MAKE_NUM(DATADIR_ZTAR, 83));
        }
        var_r25 = HuSprCreate(var_r26, 2, 1);
        HuSprGrpMemberSet(var_r28, (var_r31 * 4) + 2, var_r25);
        HuSprPosSet(var_r28, (var_r31 * 4) + 2, var_r29[var_r31], 0.0f);
        var_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_ZTAR, 88));
        var_r25 = HuSprCreate(var_r26, 2, GWPlayerCfg[var_r31].diff);
        HuSprGrpMemberSet(var_r28, (var_r31 * 4) + 3, var_r25);
        HuSprPosSet(var_r28, (var_r31 * 4) + 3, var_r29[var_r31], 38.0f);
        if (GWPlayerCfg[var_r31].iscom == 0) {
            HuSprAttrSet(var_r28, (var_r31 * 4) + 3, 4);
        }
    }
    var_r27 = HuSprGrpCreate(5);
    var_r26 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_ZTAR, 67), MEMORY_DEFAULT_NUM));
    var_r25 = HuSprCreate(var_r26, 0x32, 0);
    HuSprGrpMemberSet(var_r27, 0, var_r25);
    HuSprTPLvlSet(var_r27, 0, 0.9f);
    HuSprPosSet(var_r27, 0, 0.0f, 0.0f);
    HuSprScaleSet(var_r27, 0, 1.1f, 1.0f);
    var_r26 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_ZTAR, 65), MEMORY_DEFAULT_NUM));
    var_r25 = HuSprCreate(var_r26, 0x28, 0);
    HuSprGrpMemberSet(var_r27, 1, var_r25);
    HuSprPosSet(var_r27, 1, 0.0f, -90.0f);
    var_r26 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_ZTAR, 66), MEMORY_DEFAULT_NUM));
    var_r25 = HuSprCreate(var_r26, 0x28, 0);
    HuSprGrpMemberSet(var_r27, 2, var_r25);
    HuSprPosSet(var_r27, 2, 0.0f, 0.0f);
    var_r26 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_ZTAR, 68), MEMORY_DEFAULT_NUM));
    var_r25 = HuSprCreate(var_r26, 0x28, 1);
    HuSprGrpMemberSet(var_r27, 3, var_r25);
    HuSprPosSet(var_r27, 3, 180.0f, 0.0f);
    var_r26 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_ZTAR, 68), MEMORY_DEFAULT_NUM));
    var_r25 = HuSprCreate(var_r26, 0x28, 0);
    HuSprGrpMemberSet(var_r27, 4, var_r25);
    HuSprPosSet(var_r27, 4, -180.0f, 0.0f);
    HuSprGrpPosSet(var_r27, 288.0f, 240.0f);
    for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
        if (var_r31 <= 0x32) {
            var_f31 = var_r31 / 50.0;
            var_f30 = -300.0 + (560.0 * sind((90.0f * var_f31)));
            HuSprGrpPosSet(var_r27, 288.0f, var_f30);
            HuSprGrpPosSet(var_r28, 288.0f, var_f30);
        }
        else {
            var_f31 = (var_r31 - 0x32) / 10.0;
            var_f30 = 240.0 + (20.0 * cosd((90.0f * var_f31)));
            var_f30 = var_f30;
            HuSprGrpPosSet(var_r27, 288.0f, var_f30);
            HuSprGrpPosSet(var_r28, 288.0f, var_f30);
        }
        HuPrcVSleep();
    }
    var_r24 = HuWinCreate(0.0f, 0.0f, 0x1E0, 0x28, 0);
    HuWinMesSpeedSet(var_r24, 0);
    HuWinBGTPLvlSet(var_r24, 0.0f);
    HuWinMesSet(var_r24, MAKE_MESSID(0x1A, 0x20));
    var_r22 = &winData[var_r24];
    HuWinPriSet(var_r24, 5);
    HuWinPosSet(var_r24, (576.0f - var_r22->w) / 2, 300.0f);
#if VERSION_PAL
    HuWinScaleSet(var_r24, 0.95f, 1.0f);
#endif
    HuWinAttrSet(var_r24, 0x800);
    var_r30 = 0;
    var_r23 = 0;
    while (TRUE) {
        HuPrcVSleep();
        if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            goto block_89;
        }
        spC = 0;
        if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
            HuAudFXPlay(0x304);
            for (var_r31 = 0; var_r31 <= 5; var_r31++) {
                var_f31 = var_r31 / 5.0;
                HuSprPosSet(var_r27, 4, -180.0 - (10.0 * sind((90.0f * var_f31))), 0.0f);
                HuPrcVSleep();
            }
            var_r30--;
            if (mgTypeCurr == 1) {
                if (var_r30 < 0) {
                    var_r30 = 3;
                }
                if (var_r30 >= 4) {
                    var_r30 = 0;
                }
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    HuSprPosSet(var_r28, lbl_1_data_84[var_r30 * 4 + var_r31] * 4, var_r29[var_r31], 0.0f);
                    HuSprPosSet(var_r28, lbl_1_data_84[var_r30 * 4 + var_r31] * 4 + 2, var_r29[var_r31], 0.0f);
                    HuSprPosSet(var_r28, lbl_1_data_84[var_r30 * 4 + var_r31] * 4 + 3, var_r29[var_r31], 38.0f);
                }
            }
            else {
                if (var_r30 < 0) {
                    var_r30 = 2;
                }
                if (var_r30 >= 3) {
                    var_r30 = 0;
                }
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    HuSprPosSet(var_r28, lbl_1_data_94[var_r30 * 4 + var_r31] * 4, var_r29[var_r31], 0.0f);
                    HuSprPosSet(var_r28, lbl_1_data_94[var_r30 * 4 + var_r31] * 4 + 2, var_r29[var_r31], 0.0f);
                    HuSprPosSet(var_r28, lbl_1_data_94[var_r30 * 4 + var_r31] * 4 + 3, var_r29[var_r31], 38.0f);
                }
            }
            for (var_r31 = 0; var_r31 <= 5; var_r31++) {
                var_f31 = var_r31 / 5.0;
                HuSprPosSet(var_r27, 4, -180.0 - (10.0 * cosd((90.0f * var_f31))), 0.0f);
                HuPrcVSleep();
            }
        }
        else {
            if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
                HuAudFXPlay(0x304);
                for (var_r31 = 0; var_r31 <= 5; var_r31++) {
                    var_f31 = var_r31 / 5.0;
                    HuSprPosSet(var_r27, 3, 180.0 - (10.0 * sind((90.0f * var_f31))), 0.0f);
                    HuPrcVSleep();
                }
                var_r30++;
                if (mgTypeCurr == 1) {
                    if (var_r30 < 0) {
                        var_r30 = 3;
                    }
                    if (var_r30 >= 4) {
                        var_r30 = 0;
                    }
                    for (var_r31 = 0; var_r31 < 4; var_r31++) {
                        HuSprPosSet(var_r28, lbl_1_data_84[var_r30 * 4 + var_r31] * 4, var_r29[var_r31], 0.0f);
                        HuSprPosSet(var_r28, (lbl_1_data_84[var_r30 * 4 + var_r31] * 4) + 2, var_r29[var_r31], 0.0f);
                        HuSprPosSet(var_r28, (lbl_1_data_84[var_r30 * 4 + var_r31] * 4) + 3, var_r29[var_r31], 38.0f);
                    }
                }
                else {
                    if (var_r30 < 0) {
                        var_r30 = 2;
                    }
                    if (var_r30 >= 3) {
                        var_r30 = 0;
                    }
                    for (var_r31 = 0; var_r31 < 4; var_r31++) {
                        HuSprPosSet(var_r28, lbl_1_data_94[var_r30 * 4 + var_r31] * 4, var_r29[var_r31], 0.0f);
                        HuSprPosSet(var_r28, (lbl_1_data_94[var_r30 * 4 + var_r31] * 4) + 2, var_r29[var_r31], 0.0f);
                        HuSprPosSet(var_r28, (lbl_1_data_94[var_r30 * 4 + var_r31] * 4) + 3, var_r29[var_r31], 38.0f);
                    }
                }
                for (var_r31 = 0; var_r31 <= 5; var_r31++) {
                    var_f31 = var_r31 / 5.0;
                    HuSprPosSet(var_r27, 3, 180.0 + (10.0 * cosd((90.0f * var_f31))), 0.0f);
                    HuPrcVSleep();
                }
            }
        }
        if (HuPadBtnDown[0] & (PAD_BUTTON_START | PAD_BUTTON_A)) {
            HuAudFXPlay(0x305);
            if (mgTypeCurr == 1) {
                GWPlayerCfg[lbl_1_data_84[var_r30 * 4]].group = 0;
                for (var_r31 = 1; var_r31 < 4; var_r31++) {
                    GWPlayerCfg[lbl_1_data_84[var_r30 * 4 + var_r31]].group = 1;
                }
            }
            else {
                for (var_r31 = 0; var_r31 < 2; var_r31++) {
                    GWPlayerCfg[lbl_1_data_94[var_r30 * 4 + var_r31]].group = 0;
                }
                for (var_r31 = 2; var_r31 < 4; var_r31++) {
                    GWPlayerCfg[lbl_1_data_94[var_r30 * 4 + var_r31]].group = 1;
                }
            }
            if (arg0 != 0) {
                var_r23 = 1;
            }
            else {
                return 1;
            }
        block_89:
            HuWinKill(var_r24);
            for (var_r31 = 0; var_r31 <= 0x3C; var_r31++) {
                if (var_r31 <= 0xA) {
                    var_f31 = var_r31 / 10.0;
                    var_f30 = 240.0 + (20.0 * sind((90.0f * var_f31)));
                    HuSprGrpPosSet(var_r27, 288.0f, var_f30);
                    HuSprGrpPosSet(var_r28, 288.0f, var_f30);
                }
                else {
                    var_f31 = (var_r31 - 0xA) / 50.0;
                    var_f30 = -300.0 + (560.0 * cosd(90.0f * var_f31));
                    HuSprGrpPosSet(var_r27, 288.0f, var_f30);
                    HuSprGrpPosSet(var_r28, 288.0f, var_f30);
                }
                HuPrcVSleep();
            }
            HuSprGrpKill(var_r28);
            HuSprGrpKill(var_r27);
            return var_r23;
        }
    }
}

void fn_1_66F8(void)
{
    s16 var_r31;

    while (TRUE) {
        if (lbl_1_bss_60 != 0 || omSysExitReq) {
            break;
        }
        HuPrcVSleep();
    }
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATADIR_INSTPIC);
    while (lbl_1_bss_4 != 0) {
        HuPrcVSleep();
    }
    CharModelDataClose(-1);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GWPlayerCfg[var_r31].character = -1;
    }
#if VERSION_PAL
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        charVoiceGroupStat[var_r31] = 0;
    }
#endif
    mgPracticeEnableF = 0;
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

void fn_1_6804(void)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    s8 var_r31;

    CRot.y += 0.1f * HuPadStkX[0];
    CRot.x += 0.1f * HuPadStkY[0];
    CZoom += HuPadTrigL[0] / 2;
    CZoom -= HuPadTrigR[0] / 2;
    if (HuPadBtnDown[0] & PAD_BUTTON_B) {
        OSReport("%f,%f,%f\n", CRot.x, CRot.y, CRot.z);
        OSReport("%f,%f,%f\n", Center.x, Center.y, Center.z);
        OSReport("%f\n", CZoom);
    }
    if (CZoom < 100.0f) {
        CZoom = 100.0f;
    }
    sp2C.x = Center.x + (CZoom * (sind(CRot.y) * cosd(CRot.x)));
    sp2C.y = Center.y + (CZoom * -sind(CRot.x));
    sp2C.z = Center.z + (CZoom * (cosd(CRot.y) * cosd(CRot.x)));
    sp20.x = Center.x - sp2C.x;
    sp20.y = Center.y - sp2C.y;
    sp20.z = Center.z - sp2C.z;
    sp14.x = sind(CRot.y) * sind(CRot.x);
    sp14.y = cosd(CRot.x);
    sp14.z = cosd(CRot.y) * sind(CRot.x);
    var_f31 = CRot.z;
    sp8.x = sp14.x * ((sp20.x * sp20.x) + ((1.0f - (sp20.x * sp20.x)) * cosd(var_f31)))
        + sp14.y * (((sp20.x * sp20.y) * (1.0 - cosd(var_f31))) - sp20.z * sind(var_f31))
        + sp14.z * (((sp20.x * sp20.z) * (1.0 - cosd(var_f31))) + sp20.y * sind(var_f31));

    sp8.y = sp14.y * ((sp20.y * sp20.y) + ((1.0f - (sp20.y * sp20.y)) * cosd(var_f31)))
        + sp14.x * (((sp20.x * sp20.y) * (1.0 - cosd(var_f31))) + sp20.z * sind(var_f31))
        + sp14.z * (((sp20.y * sp20.z) * (1.0 - cosd(var_f31))) - sp20.x * sind(var_f31));

    sp8.z = sp14.z * ((sp20.z * sp20.z) + ((1.0f - (sp20.z * sp20.z)) * cosd(var_f31)))
        + (sp14.x * (((sp20.x * sp20.z) * (1.0 - cosd(var_f31))) - sp20.y * sind(var_f31))
            + sp14.y * (((sp20.y * sp20.z) * (1.0 - cosd(var_f31))) + sp20.x * sind(var_f31)));
    VECCrossProduct(&sp14, &sp20, &sp20);
    VECNormalize(&sp20, &sp20);
    var_r31 = HuPadSubStkX[0] & 0xF8;
    if (var_r31 != 0) {
        Center.x += 0.05f * (sp20.x * var_r31);
        Center.y += 0.05f * (sp20.y * var_r31);
        Center.z += 0.05f * (sp20.z * var_r31);
    }
    VECNormalize(&sp8, &sp20);
    var_r31 = -(HuPadSubStkY[0] & 0xF8);
    if (var_r31 != 0) {
        Center.x += 0.05f * (sp20.x * var_r31);
        Center.y += 0.05f * (sp20.y * var_r31);
        Center.z += 0.05f * (sp20.z * var_r31);
    }
}

void fn_1_7414(ModelData *model, Mtx matrix)
{
    Mtx sp8C;
    Mtx sp5C;
    Mtx sp2C;
    GXTexObj spC;
    s32 sp8;

    sp8 = 0;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXInitTexObj(&spC, Hu3DShadowData.unk_04, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, 1, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&spC, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&spC, GX_TEXMAP0);
    MTXInverse(Hu3DCameraMtx, sp5C);
    MTXConcat(sp5C, matrix, sp8C);
    MTXConcat(Hu3DShadowData.unk_68, Hu3DShadowData.unk_38, sp2C);
    MTXConcat(sp2C, sp8C, sp8C);
    GXLoadTexMtxImm(sp8C, 0x39, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, 0x39, GX_FALSE, 0x7D);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, 1, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
    GXSetZMode(1, GX_LEQUAL, GX_FALSE);
    GXLoadPosMtxImm(matrix, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-500.0f, 0.0f, -500.0f);
    GXPosition3f32(500.0f, 0.0f, -500.0f);
    GXPosition3f32(500.0f, 0.0f, 500.0f);
    GXPosition3f32(-500.0f, 0.0f, 500.0f);
    GXEnd();
#ifdef TARGET_PC
    GXDestroyTexObj(&spC);
#endif
}
