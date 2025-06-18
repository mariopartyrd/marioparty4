#include "REL/mgmodedll.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/saveload.h"
#include "game/wipe.h"

#include "ext_math.h"
#include <string.h>

#ifndef __MWERKS__
#include "game/hsfex.h"
#endif

typedef struct camera_view_params {
    Vec rot;
    Vec pos;
    float zoom;
} CameraViewParams;

CameraViewParams lbl_1_data_0[1] = { { { -5, 0, 0 }, { 0, 125, 0 }, 1750 } };

omObjData *outViewObj;
Process *objman;
s32 lbl_1_bss_2D4;
s32 lbl_1_bss_2D0;
s16 lbl_1_bss_2CE;
s16 lbl_1_bss_2CC;
Vec lbl_1_bss_2C0;
Vec lbl_1_bss_2B4;
float lbl_1_bss_2B0;
s16 lbl_1_bss_2A8[4];
s16 lbl_1_bss_2A6;
s16 lbl_1_bss_2A4;
Vec lbl_1_bss_28C[2];
Vec lbl_1_bss_274[2];
float lbl_1_bss_26C[2];
StructBss8 lbl_1_bss_8;
s16 mgModeEvtNo;
s32 lbl_1_bss_0;

void fn_1_464(void);
void fn_1_54F4(void);

void ObjectSetup(void)
{
    s32 glight;

    OSReport("******* MG ObjectSetup *********\n");
    objman = omInitObjMan(50, 8192);
    lbl_1_bss_28C[0].x = -70;
    lbl_1_bss_28C[0].y = 0;
    lbl_1_bss_28C[0].z = 0;
    lbl_1_bss_274[0].x = 0;
    lbl_1_bss_274[0].y = 130;
    lbl_1_bss_274[0].z = -186;
    lbl_1_bss_26C[0] = 1360;
    lbl_1_bss_2C0 = lbl_1_bss_28C[0];
    lbl_1_bss_2B4 = lbl_1_bss_274[0];
    lbl_1_bss_2B0 = lbl_1_bss_26C[0];
    lbl_1_bss_2D0 = 0;
    _ClearFlag(0x10000);
    _ClearFlag(0x10008);
    GWSystem.mg_type = -1;
    GWSystem.player_curr = 0;
    mgModeEvtNo = omovlevtno;
    if (mgModeEvtNo == 0) {
        mgGameStatBackup = GWGameStat;
    }
    lbl_1_bss_2CE = -1;
    mgBoardHostEnableF = 1;
    mgPracticeEnableF = 0;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 42, 20, 15000, 1.2f);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    glight = Hu3DGLightCreate(0, 100, 1000, 0, -0.5, -1, 255, 255, 255);
    Hu3DGLightInfinitytSet(glight);
    HuPrcChildCreate(fn_1_464, 100, 12288, 0, objman);
    HuPrcChildCreate(fn_1_54F4, 200, 4096, 0, objman);
    outViewObj = omAddObjEx(objman, 32730, 0, 0, -1, omOutView);
    Hu3DBGColorSet(0, 0, 0);
    HuWinInit(1);
    fn_1_279FC(0);
}

void fn_1_52DC(void);

void fn_1_6F8(void);

void fn_1_464(void)
{
    s16 i;
    fn_1_52DC();
    if (mgModeEvtNo == 0) {
        HuAudSStreamPlay(12);
        fn_1_19018();
    }
    else {
        HuAudSeqPlay(44);
        for (i = 0; i < 4; i++) {
            lbl_1_bss_8.unk24[i].unk68 = GWPlayerCfg[i].character;
            lbl_1_bss_8.unk24[i].unk60 = GWPlayerCfg[i].iscom;
            lbl_1_bss_8.unk24[i].unk6C = GWPlayerCfg[i].pad_idx;
            lbl_1_bss_8.unk24[i].unk64 = GWPlayerCfg[i].diff;
        }
        CZoom = 1600;
        Center.x = Center.z = 0;
        Center.y = 215;
        CRot.x = 0;
        CRot.y = CRot.z = 0;
        if (mgModeEvtNo == 1 || mgModeEvtNo == 2 || mgModeEvtNo == 3 || mgModeEvtNo == 4) {
            Hu3DModelPosSet(lbl_1_bss_2C80[5], 0, 0, 640);
            Hu3DMotionSet(lbl_1_bss_2C80[5], lbl_1_bss_2C66[6]);
            Hu3DModelAttrSet(lbl_1_bss_2C80[5], HU3D_MOTATTR_LOOP);
            HuPrcVSleep();
        }
    }
    fn_1_6F8();
    fn_1_2592C(0x1E0035, 3, 0);
    fn_1_25584(lbl_1_bss_2CE);
    while (1) {
        HuPrcVSleep();
    }
}

Vec lbl_1_data_40[4] = {
    { 108, 190, 0 },
    { 228, 190, 0 },
    { 348, 190, 0 },
    { 468, 190, 0 },
};

void fn_1_DF0(void);
void fn_1_38D8(void);
void fn_1_4010(void);

s32 fn_1_487C(void);
void fn_1_4ADC(void);

void fn_1_6F8(void)
{
    s16 i;
    s16 time;
    if (mgModeEvtNo == 1 || mgModeEvtNo == 2 || mgModeEvtNo == 3 || mgModeEvtNo == 4) {
        lbl_1_bss_2A6 = 0;
        goto freeplay;
    }
    Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(lbl_1_bss_2C80[9], 0);
    for (time = 0; time <= 30; time++) {
        for (i = 0; i < 4; i++) {
            if (time > i * 2 && time < (i * 2) + 20) {
                float weight = (time - (i * 2)) / 20.0;
                Vec pos2D = lbl_1_data_40[i];
                Vec pos3D;
                pos2D.z = 800;
                pos2D.y -= (1.0 - sind(weight * 90.0f)) * 300.0;
                Hu3D2Dto3D(&pos2D, 1, &pos3D);
                pos3D.z -= 50.0f;
                Hu3DModelPosSetV(lbl_1_bss_2C80[i + 9], &pos3D);
                Hu3DModelAttrReset(lbl_1_bss_2C80[i + 9], HU3D_ATTR_DISPOFF);
            }
        }
        HuPrcVSleep();
    }
    while (1) {
        if (lbl_1_bss_2CE == -1) {
            lbl_1_bss_2CE = fn_1_2530C(0, 0, 0);
        }
        HuWinPushKeySet(lbl_1_bss_2CE, PAD_BUTTON_A | PAD_BUTTON_B);
        HuWinMesSpeedSet(lbl_1_bss_2CE, 1);
        HuAudFXPlay(68);
        fn_1_25838(lbl_1_bss_2CE, 0x280001, -1, -1);
        lbl_1_bss_2CC = fn_1_25CA8(0x280018);
        lbl_1_bss_2A6 = 0;
        espPosSet(lbl_1_bss_2C2C[0], -20 + lbl_1_data_40[lbl_1_bss_2A6].x, -10 + lbl_1_data_40[lbl_1_bss_2A6].y);
        espAttrReset(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
        HuWinMesSpeedSet(lbl_1_bss_2CE, 0);
        fn_1_25838(lbl_1_bss_2CE, lbl_1_bss_2A6 + 0x280002, -1, -999);
        while (1) {
            s16 delta = 0;
            if ((HuPadDStkRep[0] & PAD_BUTTON_LEFT) && lbl_1_bss_2A6 > 0) {
                delta = -1;
            }
            else if ((HuPadDStkRep[0] & PAD_BUTTON_RIGHT) && lbl_1_bss_2A6 < 3) {
                delta = 1;
            }
            if (delta != 0) {
                HuAudFXPlay(0);
                lbl_1_bss_2A6 += delta;
                espPosSet(lbl_1_bss_2C2C[0], -20 + lbl_1_data_40[lbl_1_bss_2A6].x, -10 + lbl_1_data_40[lbl_1_bss_2A6].y);
                fn_1_25838(lbl_1_bss_2CE, lbl_1_bss_2A6 + 0x280002, -1, -999);
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                HuAudFXPlay(2);
                if (lbl_1_bss_2A6 != 2) {
                    break;
                }
                if (fn_1_487C() == 0) {
                    continue;
                }
                break;
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                s16 choice;
                espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
                fn_1_25838(lbl_1_bss_2CE, 0x280006, -1, -1);
                choice = HuWinChoiceGet(lbl_1_bss_2CE, 1);
                if (choice != 0) {
                    fn_1_25838(lbl_1_bss_2CE, lbl_1_bss_2A6 + 0x280002, -1, -999);
                    espAttrReset(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
                    continue;
                }
                else {
                    fn_1_25E74(lbl_1_bss_2CC);
                    fn_1_25584(lbl_1_bss_2CE);
                    lbl_1_bss_2D0 = 1;
                    while (1) {
                        HuPrcVSleep();
                    }
                }
            }
            HuPrcVSleep();
        }
        fn_1_25E74(lbl_1_bss_2CC);
        mgModeEvtNo = 0;
        espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
        if (lbl_1_bss_2A6 == 0) {
        freeplay:
            fn_1_DF0();
        }
        else if (lbl_1_bss_2A6 == 1) {
            fn_1_38D8();
        }
        else if (lbl_1_bss_2A6 == 2) {
            fn_1_4010();
        }
        else if (lbl_1_bss_2A6 == 3) {
            fn_1_4ADC();
        }
    }
}

s32 fn_1_1B0C(void);
s32 fn_1_21C4(void);
s32 fn_1_2940(void);
s32 fn_1_3150(void);

void fn_1_DF0(void)
{
    s16 exitF = 0;
    s16 time;
    s16 i;
    ModelData *modelP;
    Vec pos2D;
    Vec pos3D;

    Vec posModel;
    float weight;

    if (mgModeEvtNo == 1) {
        lbl_1_bss_2A4 = 0;
        goto freeplay;
    }
    if (mgModeEvtNo == 2) {
        lbl_1_bss_2A4 = 1;
        goto teamplay;
    }
    if (mgModeEvtNo == 3) {
        lbl_1_bss_2A4 = 2;
        goto battle;
    }
    if (mgModeEvtNo == 4) {
        lbl_1_bss_2A4 = 3;
        goto tictactoe;
    }
    pos2D.x = 168;
    pos2D.y = 190;
    pos2D.z = 800;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50;
    modelP = &Hu3DData[lbl_1_bss_2C80[9]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    for (time = 0; time <= 30; time++) {
        for (i = 1; i < 4; i++) {
            if (time > i * 2 && time < (i * 2) + 10) {
                Vec pos;
                weight = (time - (i * 2)) / 10.0;
                pos = lbl_1_data_40[i];
                pos.z = 800;
                pos.x += (1.0 - cosd(weight * 90.0f)) * 500.0;
                Hu3D2Dto3D(&pos, 1, &pos3D);
                pos3D.z -= 50.0f;
                Hu3DModelPosSetV(lbl_1_bss_2C80[i + 9], &pos3D);
                Hu3DModelAttrReset(lbl_1_bss_2C80[i + 9], HU3D_ATTR_DISPOFF);
            }
        }
        if (time > 10) {
            weight = (time - 10) / 20.0;
            VECScale(&pos2D, &pos3D, sind(weight * 90.0f));
            VECAdd(&posModel, &pos3D, &pos3D);
            Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        }
        if (time == 20) {
            HuAudFXPlay(2173);
            Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
        }
        HuPrcVSleep();
    }
    while (Hu3DMotionEndCheck(lbl_1_bss_2C80[9]) == 0) {
        HuPrcVSleep();
    }
    while (1) {
        HuWinMesSpeedSet(lbl_1_bss_2CE, 1);
        HuAudFXPlay(68);
        fn_1_25838(lbl_1_bss_2CE, 0x280007, -1, -1);
        lbl_1_bss_2CC = fn_1_25CA8(0x1A0020);
        fn_1_25838(lbl_1_bss_2CE, 0x280008, -1, -999);
        espAttrReset(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
        lbl_1_bss_2A4 = 0;
        espPosSet(lbl_1_bss_2C2C[0], -20 + (168.0f + (lbl_1_bss_2A4 * 80)), 180);
        while (1) {
            s16 delta = 0;
            if ((HuPadDStkRep[0] & PAD_BUTTON_LEFT) && lbl_1_bss_2A4 > 0) {
                delta = -1;
            }
            else if ((HuPadDStkRep[0] & PAD_BUTTON_RIGHT) && lbl_1_bss_2A4 < 3) {
                delta = 1;
            }
            if (delta != 0) {
                HuAudFXPlay(0);
                lbl_1_bss_2A4 += delta;
                espPosSet(lbl_1_bss_2C2C[0], -20 + (168.0f + (lbl_1_bss_2A4 * 80)), 180);
                fn_1_25838(lbl_1_bss_2CE, lbl_1_bss_2A4 + 0x280008, -1, -999);
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                HuAudFXPlay(2);
                if (lbl_1_bss_2A4 == 0 && lbl_1_bss_20AC[0] == 0 && lbl_1_bss_20AC[1] == 0 && lbl_1_bss_20AC[2] == 0 && lbl_1_bss_20AC[3] == 0
                    && lbl_1_bss_20AC[4] == 0) {
                    fn_1_25838(lbl_1_bss_2CE, 0x280031, -1, -1);
                    fn_1_25838(lbl_1_bss_2CE, lbl_1_bss_2A4 + 0x280008, -1, -999);
                    continue;
                }
                if (lbl_1_bss_2A4 == 2 && lbl_1_bss_20AC[0] == 0 && lbl_1_bss_20AC[1] == 0 && lbl_1_bss_20AC[2] == 0 && lbl_1_bss_20AC[4] == 0) {
                    fn_1_25838(lbl_1_bss_2CE, 0x280033, -1, -1);
                    fn_1_25838(lbl_1_bss_2CE, lbl_1_bss_2A4 + 0x280008, -1, -999);
                    continue;
                }
                if ((lbl_1_bss_2A4 == 1 || lbl_1_bss_2A4 == 3) && lbl_1_bss_20AC[2] == 0) {
                    if (lbl_1_bss_2A4 == 1) {
                        fn_1_25838(lbl_1_bss_2CE, 0x280032, -1, -1);
                    }
                    else {
                        fn_1_25838(lbl_1_bss_2CE, 0x28002F, -1, -1);
                    }
                    fn_1_25838(lbl_1_bss_2CE, lbl_1_bss_2A4 + 0x280008, -1, -999);
                    continue;
                }
                break;
            }
            if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                exitF = 1;
                break;
            }
            HuPrcVSleep();
        }
        fn_1_25E74(lbl_1_bss_2CC);
        if (exitF != 0) {
            break;
        }
        if (lbl_1_bss_2A4 == 0) {
        freeplay:
            fn_1_1B0C();
        }
        else if (lbl_1_bss_2A4 == 1) {
        teamplay:
            fn_1_21C4();
        }
        else if (lbl_1_bss_2A4 == 2) {
        battle:
            fn_1_2940();
        }
        else if (lbl_1_bss_2A4 == 3) {
        tictactoe:
            fn_1_3150();
        }
        if (lbl_1_bss_2CE == -1) {
            lbl_1_bss_2CE = fn_1_2530C(0, 0, 0);
        }
        HuWinPushKeySet(lbl_1_bss_2CE, PAD_BUTTON_A | PAD_BUTTON_B);
    }
    mgModeEvtNo = 0;
    pos2D = lbl_1_data_40[0];
    pos2D.z = 800;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50;
    modelP = &Hu3DData[lbl_1_bss_2C80[9]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_REV);
    espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
    HuAudFXPlay(2174);
    for (time = 0; time <= 20; time++) {
        VECScale(&pos2D, &pos3D, sind(time * 4.5));
        VECAdd(&posModel, &pos3D, &pos3D);
        Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        HuPrcVSleep();
    }
    for (time = 0; time <= 20; time++) {
        for (i = 1; i < 4; i++) {
            if (time > i * 2 && time < (i * 2) + 10) {
                weight = (time - (i * 2)) / 10.0;
                pos2D = lbl_1_data_40[i];
                pos2D.z = 800;
                pos2D.x += (1.0 - sind(weight * 90.0f)) * 500.0;
                Hu3D2Dto3D(&pos2D, 1, &pos3D);
                pos3D.z -= 50.0f;
                Hu3DModelPosSetV(lbl_1_bss_2C80[i + 9], &pos3D);
                Hu3DModelAttrReset(lbl_1_bss_2C80[i + 9], HU3D_ATTR_DISPOFF);
            }
        }
        HuPrcVSleep();
    }
}

s32 fn_1_1B0C(void)
{
    Vec pos2D;
    Vec posModel;
    Vec pos3D;
    s16 i;
    ModelData *modelP;
    s16 temp_r29 = 0;

    if (mgModeEvtNo == 1) {
        pos2D.x = 60;
        pos2D.y = 70;
        pos2D.z = 1000;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        pos3D.z -= 50.0f;
        Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        Hu3DModelRotSet(lbl_1_bss_2C80[9], -90, 0, 0);
        Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_REV);
        Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE);
        espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
        fn_1_25E74(lbl_1_bss_2CC);
        fn_1_25584(lbl_1_bss_2CE);
        lbl_1_bss_2CE = lbl_1_bss_2CC = -1;
        HuAudFXPlay(2174);
        HuPrcSleep(40);
        pos2D.x = 60;
        pos2D.y = 70;
        pos2D.z = 1000;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        pos3D.z -= 50.0f;
        modelP = &Hu3DData[lbl_1_bss_2C80[9]];
        posModel = modelP->pos;
        VECSubtract(&pos3D, &posModel, &pos2D);
        for (i = 0; i <= 20; i++) {
            VECScale(&pos2D, &pos3D, sind(i * 4.5));
            VECAdd(&posModel, &pos3D, &pos3D);
            Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
            Hu3DModelRotSet(lbl_1_bss_2C80[9], -90.0 * (i / 20.0), 0, 0);
            HuPrcVSleep();
        }
        while (!Hu3DMotionEndCheck(lbl_1_bss_2C80[9])) {
            HuPrcVSleep();
        }
    charsel:
        if (fn_1_194C8(temp_r29) == 0) {
            goto exit;
        }
        temp_r29 = 4;
        for (i = 0; i < 4; i++) {
            GWPlayerCfg[i].character = lbl_1_bss_8.unk24[i].unk68;
            GWPlayerCfg[i].iscom = lbl_1_bss_8.unk24[i].unk60;
            GWPlayerCfg[i].diff = lbl_1_bss_8.unk24[i].unk64;
        }
    }
    mgPracticeEnableF = 1;
    if (fn_1_6D28()) {
        mgModeEvtNo = 0;
        goto charsel;
    }
exit:
    mgPracticeEnableF = 0;
    mgModeEvtNo = 0;
    pos2D.x = 168;
    pos2D.y = 190;
    pos2D.z = 800;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50;
    modelP = &Hu3DData[lbl_1_bss_2C80[9]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
    for (i = 0; i <= 20; i++) {
        if (i == 10) {
            HuAudFXPlay(2173);
        }
        VECScale(&pos2D, &pos3D, sind(i * 4.5));
        VECAdd(&posModel, &pos3D, &pos3D);
        Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        Hu3DModelRotSet(lbl_1_bss_2C80[9], -90.0 * (1 - (i / 20.0)), 0, 0);
        HuPrcVSleep();
    }
    while (!Hu3DMotionEndCheck(lbl_1_bss_2C80[9])) {
        HuPrcVSleep();
    }
}

s32 fn_1_21C4(void)
{
    Vec pos2D;
    Vec posModel;
    Vec pos3D;
    s16 i;
    ModelData *modelP;
    s16 temp_r29 = 1;
    if (mgModeEvtNo == 2) {
        pos2D.x = 60;
        pos2D.y = 70;
        pos2D.z = 1000;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        pos3D.z -= 50.0f;
        Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        Hu3DModelRotSet(lbl_1_bss_2C80[9], 0, -90, 90);
        Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_REV);
        Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE);
        espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
        fn_1_25E74(lbl_1_bss_2CC);
        fn_1_25584(lbl_1_bss_2CE);
        lbl_1_bss_2CE = lbl_1_bss_2CC = -1;
        HuAudFXPlay(2174);
        HuPrcSleep(40);
        pos2D.x = 60;
        pos2D.y = 70;
        pos2D.z = 1000;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        pos3D.z -= 50.0f;
        modelP = &Hu3DData[lbl_1_bss_2C80[9]];
        posModel = modelP->pos;
        VECSubtract(&pos3D, &posModel, &pos2D);
        for (i = 0; i <= 20; i++) {
            VECScale(&pos2D, &pos3D, sind(i * 4.5));
            VECAdd(&posModel, &pos3D, &pos3D);
            Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
            Hu3DModelRotSet(lbl_1_bss_2C80[9], 0, -90.0 * (i / 20.0), 90.0 * (i / 20.0));
            HuPrcVSleep();
        }
        while (!Hu3DMotionEndCheck(lbl_1_bss_2C80[9])) {
            HuPrcVSleep();
        }
    charsel:
        if (fn_1_194C8(temp_r29) == 0) {
            goto exit;
        }
        temp_r29 = 4;
        for (i = 0; i < 4; i++) {
            GWPlayerCfg[i].character = lbl_1_bss_8.unk24[i].unk68;
            GWPlayerCfg[i].group = lbl_1_bss_8.unk24[i].unk5C;
            GWPlayerCfg[i].diff = lbl_1_bss_8.unk24[i].unk64;
            GWPlayerCfg[i].iscom = lbl_1_bss_8.unk24[i].unk60;
        }
    }
    mgPracticeEnableF = 1;
    if (fn_1_6D28()) {
        mgModeEvtNo = 0;
        goto charsel;
    }
exit:
    mgPracticeEnableF = 0;
    mgModeEvtNo = 0;
    pos2D.x = 168;
    pos2D.y = 190;
    pos2D.z = 800;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50;
    modelP = &Hu3DData[lbl_1_bss_2C80[9]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
    for (i = 0; i <= 20; i++) {
        if (i == 10) {
            HuAudFXPlay(2173);
        }
        VECScale(&pos2D, &pos3D, sind(i * 4.5));
        VECAdd(&posModel, &pos3D, &pos3D);
        Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        Hu3DModelRotSet(lbl_1_bss_2C80[9], 0, -90.0 * (1.0 - (i / 20.0)), 90.0 * (1.0 - (i / 20.0)));
        HuPrcVSleep();
    }
    while (!Hu3DMotionEndCheck(lbl_1_bss_2C80[9])) {
        HuPrcVSleep();
    }
}

s32 fn_1_2940(void)
{
    Vec pos2D;
    Vec posModel;
    Vec pos3D;
    s16 temp_r29 = 2;
    s16 i;
    ModelData *modelP;
    for (i = 0; i < 4; i++) {
        Hu3DModelLayerSet(lbl_1_bss_2C80[i + 9], 2);
    }
    if (mgModeEvtNo == 3) {
        OSReport("Eliminate Play STart\n");
        pos2D.x = 50;
        pos2D.y = 70;
        pos2D.z = 1000;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        pos3D.z -= 50.0f;
        Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        Hu3DModelRotSet(lbl_1_bss_2C80[9], -90, 180, 0);
        Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_REV);
        Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE);
        espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
        fn_1_25E74(lbl_1_bss_2CC);
        fn_1_25584(lbl_1_bss_2CE);
        lbl_1_bss_2CE = lbl_1_bss_2CC = -1;
        HuAudFXPlay(2174);
        HuPrcSleep(40);
        pos2D.x = 50;
        pos2D.y = 70;
        pos2D.z = 1000;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        pos3D.z -= 50.0f;
        modelP = &Hu3DData[lbl_1_bss_2C80[9]];
        posModel = modelP->pos;
        VECSubtract(&pos3D, &posModel, &pos2D);
        for (i = 0; i <= 20; i++) {
            VECScale(&pos2D, &pos3D, sind(i * 4.5));
            VECAdd(&posModel, &pos3D, &pos3D);
            Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
            Hu3DModelRotSet(lbl_1_bss_2C80[9], 90.0 * -(i / 20.0), 180.0 * (i / 20.0), 0);
            HuPrcVSleep();
        }
        while (!Hu3DMotionEndCheck(lbl_1_bss_2C80[9])) {
            HuPrcVSleep();
        }
    charsel:
        if (fn_1_194C8(temp_r29) == 0) {
            goto exit;
        }
        temp_r29 = 4;
        for (i = 0; i < 4; i++) {
            GWPlayerCfg[i].character = lbl_1_bss_8.unk24[i].unk68;
            GWPlayerCfg[i].group = lbl_1_bss_8.unk24[i].unk5C;
            GWPlayerCfg[i].iscom = lbl_1_bss_8.unk24[i].unk60;
            GWPlayerCfg[i].diff = lbl_1_bss_8.unk24[i].unk64;
        }
        mgBattleStarMax = lbl_1_bss_8.unk20;
    }

    if (fn_1_E72C() == 0) {
        mgModeEvtNo = 0;
        goto charsel;
    }
exit:
    HuDataDirClose(DATADIR_INSTPIC);
    for (i = 0; i < 4; i++) {
        Hu3DModelLayerSet(lbl_1_bss_2C80[i + 9], 3);
    }
    mgModeEvtNo = 0;
    pos2D.x = 168;
    pos2D.y = 190;
    pos2D.z = 800;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50;
    modelP = &Hu3DData[lbl_1_bss_2C80[9]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
    for (i = 0; i <= 20; i++) {
        if (i == 10) {
            HuAudFXPlay(2173);
        }
        VECScale(&pos2D, &pos3D, sind(i * 4.5));
        VECAdd(&posModel, &pos3D, &pos3D);
        Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        Hu3DModelRotSet(lbl_1_bss_2C80[9], 90.0 * -(1 - (i / 20.0)), 180.0 * (1 - (i / 20.0)), 0);
        HuPrcVSleep();
    }
    while (!Hu3DMotionEndCheck(lbl_1_bss_2C80[9])) {
        HuPrcVSleep();
    }
}

s32 fn_1_3150(void)
{
    Vec pos2D;
    Vec posModel;
    Vec pos3D;
    s16 i;
    ModelData *modelP;
    s16 temp_r29 = 1;
    if (mgModeEvtNo == 4) {
        pos2D.x = 60;
        pos2D.y = 70;
        pos2D.z = 1000;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        pos3D.z -= 50.0f;
        Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        Hu3DModelRotSet(lbl_1_bss_2C80[9], -90, 90, 0);
        Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(lbl_1_bss_2C80[9], HU3D_MOTATTR_REV);
        Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE);
        espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
        fn_1_25E74(lbl_1_bss_2CC);
        fn_1_25584(lbl_1_bss_2CE);
        lbl_1_bss_2CE = lbl_1_bss_2CC = -1;
        HuAudFXPlay(2174);
        HuPrcSleep(40);
        pos2D.x = 60;
        pos2D.y = 70;
        pos2D.z = 1000;
        Hu3D2Dto3D(&pos2D, 1, &pos3D);
        pos3D.z -= 50.0f;
        modelP = &Hu3DData[lbl_1_bss_2C80[9]];
        posModel = modelP->pos;
        VECSubtract(&pos3D, &posModel, &pos2D);
        for (i = 0; i <= 20; i++) {
            VECScale(&pos2D, &pos3D, sind(i * 4.5));
            VECAdd(&posModel, &pos3D, &pos3D);
            Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
            Hu3DModelRotSet(lbl_1_bss_2C80[9], 90.0 * -(i / 20.0), 90.0 * (i / 20.0), 0);
            HuPrcVSleep();
        }
        while (!Hu3DMotionEndCheck(lbl_1_bss_2C80[9])) {
            HuPrcVSleep();
        }
    charsel:
        if (fn_1_194C8(temp_r29) == 0) {
            goto exit;
        }
        temp_r29 = 4;
        for (i = 0; i < 4; i++) {
            GWPlayerCfg[i].character = lbl_1_bss_8.unk24[i].unk68;
            GWPlayerCfg[i].group = lbl_1_bss_8.unk24[i].unk5C;
            GWPlayerCfg[i].iscom = lbl_1_bss_8.unk24[i].unk60;
            GWPlayerCfg[i].diff = lbl_1_bss_8.unk24[i].unk64;
        }
        mgBattleStarMax = lbl_1_bss_8.unk20;
    }

    if (fn_1_13418() == 0) {
        mgModeEvtNo = 0;
        goto charsel;
    }
exit:
    HuDataDirClose(DATADIR_INSTPIC);
    mgModeEvtNo = 0;
    pos2D.x = 168;
    pos2D.y = 190;
    pos2D.z = 800;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50;
    modelP = &Hu3DData[lbl_1_bss_2C80[9]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    Hu3DModelAttrReset(lbl_1_bss_2C80[9], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_REV);
    for (i = 0; i <= 20; i++) {
        if (i == 10) {
            HuAudFXPlay(2173);
        }
        VECScale(&pos2D, &pos3D, sind(i * 4.5));
        VECAdd(&posModel, &pos3D, &pos3D);
        Hu3DModelPosSetV(lbl_1_bss_2C80[9], &pos3D);
        Hu3DModelRotSet(lbl_1_bss_2C80[9], 90.0 * -(1 - (i / 20.0)), 90.0 * (1 - (i / 20.0)), 0);
        HuPrcVSleep();
    }
    while (!Hu3DMotionEndCheck(lbl_1_bss_2C80[9])) {
        HuPrcVSleep();
    }
}

void fn_1_38D8(void)
{
    Vec pos2D;
    Vec pos3D;
    Vec posModel;

    s16 sp8 = 0;
    s16 time;
    s16 i;
    float weight;
    ModelData *modelP;

    fn_1_25E74(lbl_1_bss_2CC);
    fn_1_25584(lbl_1_bss_2CE);
    lbl_1_bss_2CE = lbl_1_bss_2CC = -1;
    pos2D.x = 60;
    pos2D.y = 70;
    pos2D.z = 1000;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50.0f;
    modelP = &Hu3DData[lbl_1_bss_2C80[10]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    for (time = 0; time <= 30; time++) {
        for (i = 0; i < 4; i++) {
            if (i == 1) {
                continue;
            }
            if (time > i * 2 && time < (i * 2) + 10) {
                Vec posBox;
                weight = (time - (i * 2)) / 10.0;
                posBox = lbl_1_data_40[i];
                posBox.z = 800;
                posBox.x += ((i < 2) ? -1 : 1) * (500.0 * (1.0 - cosd(90.0f * weight)));
                Hu3D2Dto3D(&posBox, 1, &pos3D);
                pos3D.z -= 50.0f;
                Hu3DModelPosSetV(lbl_1_bss_2C80[i + 9], &pos3D);
                Hu3DModelAttrReset(lbl_1_bss_2C80[i + 9], HU3D_ATTR_DISPOFF);
            }
        }
        if (time > 10) {
            weight = (time - 10) / 20.0;
            VECScale(&pos2D, &pos3D, sind(weight * 90.0f));
            VECAdd(&posModel, &pos3D, &pos3D);
            Hu3DModelPosSetV(lbl_1_bss_2C80[10], &pos3D);
        }
        HuPrcVSleep();
    }
    fn_1_6D28();
    pos2D = lbl_1_data_40[1];
    pos2D.z = 800;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50.0f;
    modelP = &Hu3DData[lbl_1_bss_2C80[10]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
    for (time = 0; time <= 20; time++) {
        VECScale(&pos2D, &pos3D, sind(time * 4.5));
        VECAdd(&posModel, &pos3D, &pos3D);
        Hu3DModelPosSetV(lbl_1_bss_2C80[10], &pos3D);
        HuPrcVSleep();
    }
    for (time = 0; time <= 20; time++) {
        for (i = 0; i < 4; i++) {
            if (i == 1) {
                continue;
            }
            if (time > i * 2 && time < (i * 2) + 10) {
                weight = (time - (i * 2)) / 10.0;
                pos2D = lbl_1_data_40[i];
                pos2D.z = 800;
                pos2D.x += ((i < 2) ? -1 : 1) * ((1.0 - sind(weight * 90.0f)) * 500.0);
                Hu3D2Dto3D(&pos2D, 1, &pos3D);
                pos3D.z -= 50.0f;
                Hu3DModelPosSetV(lbl_1_bss_2C80[i + 9], &pos3D);
                Hu3DModelAttrReset(lbl_1_bss_2C80[i + 9], HU3D_ATTR_DISPOFF);
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_4010(void)
{
    Vec pos2D;
    Vec pos3D;
    Vec posModel;

    s16 spA[4];
    s16 sp8 = 0;
    s16 time;
    s16 i;
    float weight;
    ModelData *modelP;
    fn_1_25E74(lbl_1_bss_2CC);
    fn_1_25584(lbl_1_bss_2CE);
    lbl_1_bss_2CE = lbl_1_bss_2CC = -1;
    pos2D.x = 60;
    pos2D.y = 70;
    pos2D.z = 1000;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50.0f;
    modelP = &Hu3DData[lbl_1_bss_2C80[11]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    for (time = 0; time <= 30; time++) {
        for (i = 0; i < 4; i++) {
            if (i == 2) {
                continue;
            }
            if (time > i * 2 && time < (i * 2) + 10) {
                Vec posBox;
                weight = (time - (i * 2)) / 10.0;
                posBox = lbl_1_data_40[i];
                posBox.z = 800;
                posBox.x += ((i < 3) ? -1 : 1) * (500.0 * (1.0 - cosd(90.0f * weight)));
                Hu3D2Dto3D(&posBox, 1, &pos3D);
                pos3D.z -= 50.0f;
                Hu3DModelPosSetV(lbl_1_bss_2C80[i + 9], &pos3D);
                Hu3DModelAttrReset(lbl_1_bss_2C80[i + 9], HU3D_ATTR_DISPOFF);
            }
        }
        if (time > 10) {
            weight = (time - 10) / 20.0;
            VECScale(&pos2D, &pos3D, sind(weight * 90.0f));
            VECAdd(&posModel, &pos3D, &pos3D);
            Hu3DModelPosSetV(lbl_1_bss_2C80[11], &pos3D);
        }
        HuPrcVSleep();
    }
    fn_1_6D28();
    for (i = 0; i < 4; i++) {
        spA[i] = 0;
        for (time = 0; time < lbl_1_bss_20AC[lbl_1_data_A2[i]]; time++) {
            if (GWMGCustomGet(lbl_1_bss_20C0[lbl_1_data_A2[i]][time] + 401)) {
                spA[i]++;
            }
        }
    }
    if (spA[0] >= 4 && spA[1] >= 3 && spA[2] >= 3 && spA[3] >= 2) {
        GWGameStat.customPackEnable = 1;
    }
    else {
        GWGameStat.customPackEnable = 0;
    }
    pos2D = lbl_1_data_40[2];
    pos2D.z = 800;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50.0f;
    modelP = &Hu3DData[lbl_1_bss_2C80[11]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
    for (time = 0; time <= 20; time++) {
        VECScale(&pos2D, &pos3D, sind(time * 4.5));
        VECAdd(&posModel, &pos3D, &pos3D);
        Hu3DModelPosSetV(lbl_1_bss_2C80[11], &pos3D);
        HuPrcVSleep();
    }
    for (time = 0; time <= 20; time++) {
        for (i = 0; i < 4; i++) {
            if (i == 2) {
                continue;
            }
            if (time > i * 2 && time < (i * 2) + 10) {
                weight = (time - (i * 2)) / 10.0;
                pos2D = lbl_1_data_40[i];
                pos2D.z = 800;
                pos2D.x += ((i < 3) ? -1 : 1) * ((1.0 - sind(weight * 90.0f)) * 500.0);
                Hu3D2Dto3D(&pos2D, 1, &pos3D);
                pos3D.z -= 50.0f;
                Hu3DModelPosSetV(lbl_1_bss_2C80[i + 9], &pos3D);
                Hu3DModelAttrReset(lbl_1_bss_2C80[i + 9], HU3D_ATTR_DISPOFF);
            }
        }
        HuPrcVSleep();
    }
}

s32 fn_1_487C(void)
{
    s16 i;
    char str[4][6];

    for (i = 0; i < 4; i++) {
        strcpy(&str[i][0],
            "\x1E\x03"
            "0"
            "\x1E\x08");
    }
    if (lbl_1_bss_20AC[0] >= 4 && lbl_1_bss_20AC[1] >= 3 && lbl_1_bss_20AC[2] >= 3 && lbl_1_bss_20AC[4] >= 2) {
        return 1;
    }
    if (lbl_1_bss_20AC[0] >= 4) {
        str[0][1] = 5;
    }
    else {
        str[0][2] = '4' - lbl_1_bss_20AC[0];
    }
    HuWinInsertMesSet(lbl_1_bss_2CE, MAKE_MESSID_PTR(&str[0][0]), 0);
    if (lbl_1_bss_20AC[1] >= 3) {
        str[1][1] = 5;
    }
    else {
        str[1][2] = '3' - lbl_1_bss_20AC[1];
    }
    HuWinInsertMesSet(lbl_1_bss_2CE, MAKE_MESSID_PTR(&str[1][0]), 1);
    if (lbl_1_bss_20AC[2] >= 3) {
        str[2][1] = 5;
    }
    else {
        str[2][2] = '3' - lbl_1_bss_20AC[2];
    }
    HuWinInsertMesSet(lbl_1_bss_2CE, MAKE_MESSID_PTR(&str[2][0]), 2);
    if (lbl_1_bss_20AC[4] >= 2) {
        str[3][1] = 5;
    }
    else {
        str[3][2] = '2' - lbl_1_bss_20AC[4];
    }
    HuWinInsertMesSet(lbl_1_bss_2CE, MAKE_MESSID_PTR(&str[3][0]), 3);
    fn_1_25838(lbl_1_bss_2CE, 0x28002A, -1, -1);
    fn_1_25838(lbl_1_bss_2CE, 0x28002B, -1, -1);
    fn_1_25838(lbl_1_bss_2CE, 0x280002 + lbl_1_bss_2A6, -1, -999);
    return 0;
}

void fn_1_4ADC(void)
{
    Vec pos2D;
    Vec pos3D;
    Vec posModel;

    s16 spA[4];
    s16 sp8 = 0;
    s16 time;
    s16 i;
    float weight;
    ModelData *modelP;
    fn_1_25E74(lbl_1_bss_2CC);
    fn_1_25584(lbl_1_bss_2CE);
    lbl_1_bss_2CE = lbl_1_bss_2CC = -1;
    pos2D.x = 50;
    pos2D.y = 64;
    pos2D.z = 1000;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50.0f;
    modelP = &Hu3DData[lbl_1_bss_2C80[11]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    for (time = 0; time <= 30; time++) {
        for (i = 0; i < 4; i++) {
            if (i == 3) {
                continue;
            }
            if (time > i * 2 && time < (i * 2) + 10) {
                Vec posBox;
                weight = (time - (i * 2)) / 10.0;
                posBox = lbl_1_data_40[i];
                posBox.z = 800;
                posBox.x += ((i < 3) ? -1 : 1) * (500.0 * (1.0 - cosd(90.0f * weight)));
                Hu3D2Dto3D(&posBox, 1, &pos3D);
                pos3D.z -= 50.0f;
                Hu3DModelPosSetV(lbl_1_bss_2C80[i + 9], &pos3D);
                Hu3DModelAttrReset(lbl_1_bss_2C80[i + 9], HU3D_ATTR_DISPOFF);
            }
        }
        if (time > 10) {
            weight = (time - 10) / 20.0;
            VECScale(&pos2D, &pos3D, sind(weight * 90.0f));
            VECAdd(&posModel, &pos3D, &pos3D);
            Hu3DModelPosSetV(lbl_1_bss_2C80[12], &pos3D);
            weight = (1.0 - (weight * 0.1));
            Hu3DModelScaleSet(lbl_1_bss_2C80[12], weight, weight, weight);
        }
        HuPrcVSleep();
    }
    fn_1_D8D0();
    pos2D = lbl_1_data_40[3];
    pos2D.z = 800;
    Hu3D2Dto3D(&pos2D, 1, &pos3D);
    pos3D.z -= 50.0f;
    modelP = &Hu3DData[lbl_1_bss_2C80[12]];
    posModel = modelP->pos;
    VECSubtract(&pos3D, &posModel, &pos2D);
    espAttrSet(lbl_1_bss_2C2C[0], HUSPR_ATTR_DISPOFF);
    for (time = 0; time <= 20; time++) {
        VECScale(&pos2D, &pos3D, sind(time * 4.5));
        VECAdd(&posModel, &pos3D, &pos3D);
        Hu3DModelPosSetV(lbl_1_bss_2C80[12], &pos3D);
        weight = 1.0 - (0.1 * (1.0 - (time / 20.0)));
        Hu3DModelScaleSet(lbl_1_bss_2C80[12], weight, weight, weight);
        HuPrcVSleep();
    }
    for (time = 0; time <= 20; time++) {
        for (i = 0; i < 4; i++) {
            if (i == 3) {
                continue;
            }
            if (time > i * 2 && time < (i * 2) + 10) {
                weight = (time - (i * 2)) / 10.0;
                pos2D = lbl_1_data_40[i];
                pos2D.z = 800;
                pos2D.x += ((i < 3) ? -1 : 1) * ((1.0 - sind(weight * 90.0f)) * 500.0);
                Hu3D2Dto3D(&pos2D, 1, &pos3D);
                pos3D.z -= 50.0f;
                Hu3DModelPosSetV(lbl_1_bss_2C80[i + 9], &pos3D);
                Hu3DModelAttrReset(lbl_1_bss_2C80[i + 9], HU3D_ATTR_DISPOFF);
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_65EC(void);

void fn_1_52DC(void)
{
    s16 i;
    fn_1_65EC();
    fn_1_267E8(lbl_1_data_490);
    fn_1_26A78(lbl_1_data_768);
    Hu3DMotionSet(lbl_1_bss_2C80[2], lbl_1_bss_2C66[4]);
    Hu3DMotionTimeSet(lbl_1_bss_2C80[0], 0);
    Hu3DModelAttrSet(lbl_1_bss_2C80[0], HU3D_MOTATTR_PAUSE);
    HuSprExecLayerSet(64, 3);
    espDrawNoSet(lbl_1_bss_2C2C[3], 64);
    for (i = 0; i < 4; i++) {
        Hu3DModelLayerSet(lbl_1_bss_2C80[i + 9], 3);
    }
    fn_1_26C28();
    espDrawNoSet(lbl_1_bss_2C2C[28], 64);
    Hu3DModelPosSet(lbl_1_bss_2C80[5], 0, 0, 500);
    lbl_1_bss_8.unk0 = lbl_1_bss_2C80[2];
    lbl_1_bss_8.unk8 = lbl_1_bss_2C66[4];
    lbl_1_bss_8.unk4 = lbl_1_bss_2C66[3];
    lbl_1_bss_8.unkC = lbl_1_bss_2C80[5];
    lbl_1_bss_8.unk10 = lbl_1_bss_2C66[6];
    lbl_1_bss_8.unk14 = lbl_1_bss_2C66[7];
    lbl_1_bss_8.unk18 = lbl_1_bss_2C66[6];
    fn_1_18DF8(objman, &lbl_1_bss_8);
    Hu3DModelShadowSet(lbl_1_bss_2C80[5]);
    Hu3DModelShadowMapSet(lbl_1_bss_2C80[0]);
}

void fn_1_6C18(void);

void fn_1_54F4(void)
{
    while (1) {
        if (lbl_1_bss_2D0) {
            break;
        }
        if (omSysExitReq) {
            break;
        }
        HuPrcVSleep();
    }
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudSeqAllFadeOut(1000);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATADIR_INSTPIC);
    if (memcmp(&mgGameStatBackup, &GWGameStat, sizeof(GWGameStat))) {
        fn_1_6C18();
    }
    BoardStatusKill();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

static u16 lbl_1_data_8C[2] = { 1, 2 };

void fn_1_55C0(omObjData *object)
{
    s16 i;
    for (i = 0; i < 1; i++) {
        Vec pos, target, up;
        float x, y, z;

        x = lbl_1_bss_28C[i].x;
        y = lbl_1_bss_28C[i].y;
        z = lbl_1_bss_28C[i].z;

        pos.x = (((sind(y) * cosd(x)) * lbl_1_bss_26C[i]) + lbl_1_bss_274[i].x);
        pos.y = (-sind(x) * lbl_1_bss_26C[i]) + lbl_1_bss_274[i].y;
        pos.z = ((cosd(y) * cosd(x)) * lbl_1_bss_26C[i]) + lbl_1_bss_274[i].z;
        target.x = lbl_1_bss_274[i].x;
        target.y = lbl_1_bss_274[i].y;
        target.z = lbl_1_bss_274[i].z;
        up.x = sind(y) * sind(x);
        up.y = cosd(x);
        up.z = cosd(y) * sind(x);
        Hu3DCameraPosSet(lbl_1_data_8C[i], pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
    }
}

void fn_1_66B0(void);

void fn_1_5974(omObjData *object)
{
    Vec pos;
    Vec offset;
    Vec dir;
    Vec y_offset;

    f32 z_rot;
    s8 stick_pos;
    if (HuPadBtnDown[0] & PAD_BUTTON_Y) {
        lbl_1_bss_0 = (lbl_1_bss_0) ? 0 : 1;
    }
    if (lbl_1_bss_0 == 0) {
        fn_1_66B0();
        return;
    }
    lbl_1_bss_28C[0].y += 0.1f * HuPadStkX[0];
    lbl_1_bss_28C[0].x += 0.1f * HuPadStkY[0];
    lbl_1_bss_26C[0] += HuPadTrigL[0] / 2;
    lbl_1_bss_26C[0] -= HuPadTrigR[0] / 2;
    if (HuPadBtnDown[0] & PAD_BUTTON_B) {
        OSReport("%f,%f,%f\n", lbl_1_bss_28C[0].x, lbl_1_bss_28C[0].y, lbl_1_bss_28C[0].z);
        OSReport("%f,%f,%f\n", lbl_1_bss_274[0].x, lbl_1_bss_274[0].y, lbl_1_bss_274[0].z);
        OSReport("%f\n", lbl_1_bss_26C[0]);
    }
    if (lbl_1_bss_26C[0] < 100.0f) {
        lbl_1_bss_26C[0] = 100.0f;
    }
    pos.x = lbl_1_bss_274[0].x + (lbl_1_bss_26C[0] * (sind(lbl_1_bss_28C[0].y) * cosd(lbl_1_bss_28C[0].x)));
    pos.y = (lbl_1_bss_274[0].y + (lbl_1_bss_26C[0] * -sind(lbl_1_bss_28C[0].x)));
    pos.z = (lbl_1_bss_274[0].z + (lbl_1_bss_26C[0] * (cosd(lbl_1_bss_28C[0].y) * cosd(lbl_1_bss_28C[0].x))));
    offset.x = lbl_1_bss_274[0].x - pos.x;
    offset.y = lbl_1_bss_274[0].y - pos.y;
    offset.z = lbl_1_bss_274[0].z - pos.z;
    dir.x = (sind(lbl_1_bss_28C[0].y) * sind(lbl_1_bss_28C[0].x));
    dir.y = cosd(lbl_1_bss_28C[0].x);
    dir.z = (cosd(lbl_1_bss_28C[0].y) * sind(lbl_1_bss_28C[0].x));
    z_rot = lbl_1_bss_28C[0].z;
    y_offset.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * cosd(z_rot))
        + dir.y * (offset.x * offset.y * (1.0f - cosd(z_rot)) - offset.z * sind(z_rot))
        + dir.z * (offset.x * offset.z * (1.0f - cosd(z_rot)) + offset.y * sind(z_rot));

    y_offset.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * cosd(z_rot))
        + dir.x * (offset.x * offset.y * (1.0f - cosd(z_rot)) + offset.z * sind(z_rot))
        + dir.z * (offset.y * offset.z * (1.0f - cosd(z_rot)) - offset.x * sind(z_rot));

    y_offset.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * cosd(z_rot))
        + (dir.x * (offset.x * offset.z * (1.0 - cosd(z_rot)) - offset.y * sind(z_rot))
            + dir.y * (offset.y * offset.z * (1.0 - cosd(z_rot)) + offset.x * sind(z_rot)));

    VECCrossProduct(&dir, &offset, &offset);
    VECNormalize(&offset, &offset);
    stick_pos = (HuPadSubStkX[0] & 0xF8);
    if (stick_pos != 0) {
        lbl_1_bss_274[0].x += 0.05f * (offset.x * stick_pos);
        lbl_1_bss_274[0].y += 0.05f * (offset.y * stick_pos);
        lbl_1_bss_274[0].z += 0.05f * (offset.z * stick_pos);
    }
    VECNormalize(&y_offset, &offset);
    stick_pos = -(HuPadSubStkY[0] & 0xF8);
    if (stick_pos != 0) {
        lbl_1_bss_274[0].x += 0.05f * (offset.x * stick_pos);
        lbl_1_bss_274[0].y += 0.05f * (offset.y * stick_pos);
        lbl_1_bss_274[0].z += 0.05f * (offset.z * stick_pos);
    }
}

void fn_1_65EC(void)
{
    Vec pos = { 0, 3000, 800 };
    Vec target = { 0, 0, 640 };
    Vec up = { 0, 1, 0 };
    Hu3DShadowCreate(45, 2000, 25000);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&pos, &up, &target);
}

void fn_1_66B0(void)
{
    Vec deltaVec;
    float delta;

    if (lbl_1_bss_2D0) {
        return;
    }
    VECSubtract(&lbl_1_bss_2C0, &lbl_1_bss_28C[0], &deltaVec);
    if (VECMag(&deltaVec) > 0.2) {
        VECScale(&deltaVec, &deltaVec, 0.05f);
        VECAdd(&lbl_1_bss_28C[0], &deltaVec, &lbl_1_bss_28C[0]);
    }
    else {
        lbl_1_bss_28C[0] = lbl_1_bss_2C0;
    }
    VECSubtract(&lbl_1_bss_2B4, &lbl_1_bss_274[0], &deltaVec);
    if (VECMag(&deltaVec) > 0.2) {
        VECScale(&deltaVec, &deltaVec, 0.05f);
        VECAdd(&lbl_1_bss_274[0], &deltaVec, &lbl_1_bss_274[0]);
    }
    else {
        lbl_1_bss_274[0] = lbl_1_bss_2B4;
    }
    delta = lbl_1_bss_2B0 - lbl_1_bss_26C[0];
    if (sqrtf(delta * delta) > 0.2) {
        delta *= 0.05f;
        lbl_1_bss_26C[0] += delta;
    }
    else {
        lbl_1_bss_26C[0] = lbl_1_bss_2B0;
    }
}

void fn_1_6974(s16 arg0)
{
    lbl_1_bss_2C0 = lbl_1_data_0[arg0].rot;
    lbl_1_bss_2B4 = lbl_1_data_0[arg0].pos;
    lbl_1_bss_2B0 = lbl_1_data_0[arg0].zoom;
}

void fn_1_6A04(s16 arg0)
{
    lbl_1_bss_2C0 = lbl_1_bss_28C[0] = lbl_1_data_0[arg0].rot;
    lbl_1_bss_2B4 = lbl_1_bss_274[0] = lbl_1_data_0[arg0].pos;
    lbl_1_bss_2B0 = lbl_1_bss_26C[0] = lbl_1_data_0[arg0].zoom;
}

float fn_1_6AF0(void)
{
    float delta = lbl_1_bss_2B0 - lbl_1_bss_26C[0];
    return sqrtf(delta * delta);
}

void fn_1_6C18(void)
{
    s16 sprite;
    if (!SLSaveFlagGet()) {
        return;
    }
    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    espInit();
    HuPrcVSleep();
    sprite = espEntry(DATA_MAKE_NUM(DATADIR_WIN, 0x20), 5000, 0);
    espPosSet(sprite, 288.0, 240.0);
    espAttrReset(sprite, HUSPR_ATTR_DISPOFF);
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    SLCommonSet();
    if (!SLSave()) {
        GWSaveModeSet(1);
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
}
