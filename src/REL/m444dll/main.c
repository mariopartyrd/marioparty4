#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"

#include "game/pad.h"

#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/window.h"
#include "game/wipe.h"

#include "game/board/ui.h"
#include "game/gamework.h"
#include "game/gamework_data.h"

#include "REL/m444dll.h"
#include "ext_math.h"
#include "math.h"

typedef struct camera_view_params {
    Vec rot;
    Vec pos;
    float zoom;
} CameraViewParams;

CameraViewParams lbl_1_data_0[] = {
    { { -55, 0, 0 }, { 0, 60, -57 }, 806 },
    { { -71, 0, 0 }, { 0, 100, -131 }, 900 },
    { { -87, 0, 0 }, { 0, 46, -117 }, 566 },
    { { -87, 0, 0 }, { 0, 46, -117 }, 566 },
    { { -90, 0, 0 }, { -22, 39, -153 }, 432 },
    { { -40, 0, 0 }, { 0, 130, -186 }, 6530 },
    { { -23, 0, 0 }, { -9, 1, -70 }, 1318 },
    { { -25, 0, 0 }, { 0, 242, 90 }, 343 },
    { { -30, 0, 0 }, { 0, 223, -60 }, 505 },
    { { -23, 0, 0 }, { 0, 65, -97 }, 1318 },
};

DataListSprite lbl_1_data_118[] = {
    { DATA_MAKE_NUM(DATADIR_M444, 0x22), 0, 10, 288, -200, { 255, 255, 255, 255 } },
    { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } },
};

float lbl_1_data_140[] = { 90, 250, 420 };

Vec lbl_1_data_14C[] = {
    { -75, -300, 0 },
    { 25, -300, 0 },
    { -75, -300, 0 },
    { 25, -300, 0 },
    { -25, -400, 0 },
};

s16 lbl_1_data_188[] = { 1, 1, 2, 2, 2 };

s32 lbl_1_data_194[] = {
    DATA_MAKE_NUM(DATADIR_M444, 0x24),
    DATA_MAKE_NUM(DATADIR_M444, 0x25),
    DATA_MAKE_NUM(DATADIR_M444, 0x26),
    DATA_MAKE_NUM(DATADIR_M444, 0x27),
    DATA_MAKE_NUM(DATADIR_M444, 0x28),
    DATA_MAKE_NUM(DATADIR_M444, 0x29),
    DATA_MAKE_NUM(DATADIR_M444, 0x2A),
    DATA_MAKE_NUM(DATADIR_M444, 0x2B),
};

omObjData *lbl_1_bss_30C;
Process *lbl_1_bss_308;
s32 lbl_1_bss_300[2];
s32 lbl_1_bss_2FC;
Vec lbl_1_bss_2F0;
Vec lbl_1_bss_2E4;
float lbl_1_bss_2E0;
s16 lbl_1_bss_2DC;
s16 lbl_1_bss_2DA;
s16 lbl_1_bss_2D8;
s16 lbl_1_bss_2D6;
s16 lbl_1_bss_2D4;
s16 lbl_1_bss_2D2;
s16 lbl_1_bss_2D0;
s16 lbl_1_bss_2C0[8];
Vec lbl_1_bss_2A8[2];
Vec lbl_1_bss_290[2];
float lbl_1_bss_288[2];
s16 lbl_1_bss_148[20][8];
s16 lbl_1_bss_8[20][8];
s16 lbl_1_bss_6;
s16 lbl_1_bss_4;
s32 lbl_1_bss_0;

void fn_1_470(void);
void fn_1_6E3C(void);
void fn_1_6EDC(omObjData *object);
void fn_1_7290(omObjData *object);

void ObjectSetup(void)
{
    s32 light;
    OSReport("******* M444 ObjectSetup *********\n");
    lbl_1_bss_308 = omInitObjMan(50, 8192);
    omGameSysInit(lbl_1_bss_308);
    lbl_1_bss_2A8[0].x = -70;
    lbl_1_bss_2A8[0].y = 0;
    lbl_1_bss_2A8[0].z = 0;
    lbl_1_bss_290[0].x = 0;
    lbl_1_bss_290[0].y = 130;
    lbl_1_bss_290[0].z = -186;
    lbl_1_bss_288[0] = 1360;
    lbl_1_bss_2F0 = lbl_1_bss_2A8[0];
    lbl_1_bss_2E4 = lbl_1_bss_290[0];
    lbl_1_bss_2E0 = lbl_1_bss_288[0];
    lbl_1_bss_2FC = 0;
    lbl_1_bss_2D6 = -2;
    lbl_1_bss_2D4 = -2;
    lbl_1_bss_2D2 = -2;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30, 20, 15000, 1.2f);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    light = Hu3DGLightCreate(-1000, 1000, 0, 1, -1, 0, 255, 255, 255);
    Hu3DGLightInfinitytSet(light);
    Hu3DGLightStaticSet(light, 1);
    light = Hu3DGLightCreate(0, 50, 1000, 0, -0.05f, -1, 96, 96, 96);
    Hu3DGLightInfinitytSet(light);
    HuPrcChildCreate(fn_1_470, 100, 12288, 0, lbl_1_bss_308);
    HuPrcChildCreate(fn_1_6E3C, 200, 4096, 0, lbl_1_bss_308);
    lbl_1_bss_30C = omAddObjEx(lbl_1_bss_308, 32730, 0, 0, -1, fn_1_6EDC);
    omAddObjEx(lbl_1_bss_308, 0, 32, 32, -1, fn_1_7290);
    Hu3DBGColorSet(0, 0, 0);
#if VERSION_JP
    GWGameStat.language = 0;
#endif
    HuWinInit(1);
    BoardStatusCreate();
}

void fn_1_3B7C(void);

void fn_1_4DEC(void);

void fn_1_655C(void);
void fn_1_6D80(s16 window);

void fn_1_8180(s16 view);
void fn_1_8210(s16 view);
float fn_1_82FC(void);

void fn_1_470(void)
{
    float temp_f31;
    float temp_f30;

    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    u32 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    u32 temp_r24;
    ModelData *temp_r23;

    Vec sp1C;
    Vec sp10;
    float sp8[2];

    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        if (GWPlayerCfg[temp_r31].group == 0) {
            break;
        }
    }
    lbl_1_bss_2DC = temp_r31;
    lbl_1_bss_2D8 = GWPlayerCfg[temp_r31].pad_idx;
    lbl_1_bss_2DA = GWPlayerCfg[temp_r31].character;
    fn_1_655C();
    fn_1_8210(5);
    fn_1_8180(6);
    Hu3DModelPosSet(lbl_1_bss_2D0, 0, 0, 250);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    HuAudSeqPlay(76);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    while (fn_1_82FC() > 10.0f) {
        HuPrcVSleep();
    }
    Hu3DModelAttrReset(lbl_1_bss_199C2[18], HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(lbl_1_bss_199C2[18], lbl_1_bss_1990E[20]);
    Hu3DModelRotSet(lbl_1_bss_199C2[18], 0, 90, 0);
    for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
        if (temp_r31 <= 30) {
            espPosSet(lbl_1_bss_1990A[0], 288, (200.0 * sind(3.0 * temp_r31)) - 100.0);
        }
        Hu3DModelPosSet(lbl_1_bss_199C2[18], (-300.0 * cosd(1.5 * temp_r31)) + (-160.0), 0, 155);
        HuPrcVSleep();
    }
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        if (temp_r31 <= 20) {
            Hu3DModelRotSet(lbl_1_bss_199C2[18], 0, (30.0 * (1.0 - (temp_r31 / 20.0f))) + 60.0, 0);
        }
        if (temp_r31 > 10) {
            temp_r29 = temp_r31 - 10;
            Hu3DModelRotSet(lbl_1_bss_2D0, 0, (-(temp_r29 / 20.0f)) * 120.0f, 0);
        }
        if (temp_r31 == 10) {
            Hu3DMotionShiftSet(lbl_1_bss_199C2[18], lbl_1_bss_1990E[19], 0, 16, HU3D_MOTATTR_LOOP);
            CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[1], 0, 8, HU3D_MOTATTR_LOOP);
        }
        HuPrcVSleep();
    }
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[0], 0, 8, HU3D_MOTATTR_LOOP);
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x1C, 0x00));
    temp_r30 = HuWinExCreateStyled(-10000, 340, sp8[0], sp8[1], -1, 1);
    HuWinExAnimIn(temp_r30);
    HuWinMesPalSet(temp_r30, 7, 0, 0, 0);
    fn_1_6D80(temp_r30);
    HuWinMesSet(temp_r30, MAKE_MESSID(0x1C, 0x00));
    HuWinMesWait(temp_r30);
    HuWinExAnimOut(temp_r30);
    HuWinExCleanup(temp_r30);
    HuWinComKeyReset();
    Hu3DMotionShiftSet(lbl_1_bss_199C2[18], lbl_1_bss_1990E[20], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 <= 20; temp_r31++) {
        HuPrcVSleep();
    }
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        if (temp_r31 <= 10) {
            Hu3DModelRotSet(lbl_1_bss_199C2[18], 0, 30.0f - ((temp_r31 / 10.0f) * 120.0f), 0);
        }
        if (temp_r31 <= 20) {
            espPosSet(lbl_1_bss_1990A[0], 288, (200.0 * cosd(temp_r31 * 4.5)) - 100.0);
        }
        Hu3DModelPosSet(lbl_1_bss_199C2[18], ((1.0 - cosd(temp_r31 * 3.0)) * -200.0) + -160.0, 0, 155);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(lbl_1_bss_199C2[18], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_199C2[22], HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(lbl_1_bss_199C2[22], lbl_1_bss_1990E[24]);
    Hu3DModelRotSet(lbl_1_bss_199C2[22], 0, 90, 0);
    for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
        Hu3DModelPosSet(lbl_1_bss_199C2[22], (-300.0 * cosd(1.5 * temp_r31)) + (-160.0), 0, 155);
        if (temp_r31 > 20) {
            temp_r29 = temp_r31 - 40;
            Hu3DModelRotSet(lbl_1_bss_199C2[22], 0, (30.0 * (1.0 - (temp_r29 / 20.0f))) + 60.0, 0);
        }
        if (temp_r31 == 50) {
            Hu3DMotionShiftSet(lbl_1_bss_199C2[22], lbl_1_bss_1990E[23], 0, 10, HU3D_MOTATTR_LOOP);
        }
        if (temp_r31 > 40) {
            temp_r29 = temp_r31 - 40;
            for (temp_r27 = 0; temp_r27 < 3; temp_r27++) {
                lbl_1_bss_34C[temp_r27].y = (180.0 * sind(4.5 * temp_r29)) - 100.0;
            }
        }
        HuPrcVSleep();
    }
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x1C, 0x01));
    temp_r30 = HuWinExCreateStyled(-10000, 340, sp8[0], sp8[1], -1, 1);
    HuWinExAnimIn(temp_r30);
    HuWinMesPalSet(temp_r30, 7, 0, 0, 0);
    fn_1_6D80(temp_r30);
    HuWinMesSet(temp_r30, MAKE_MESSID(0x1C, 0x01));
    HuWinMesWait(temp_r30);
    HuWinExAnimOut(temp_r30);
    HuWinExCleanup(temp_r30);
    HuWinComKeyReset();
    Hu3DModelAttrReset(lbl_1_bss_199C2[11], HU3D_MOTATTR_PAUSE);
    HuAudFXPlay(1854);
    Hu3DMotionShiftSet(lbl_1_bss_199C2[22], lbl_1_bss_1990E[24], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
        temp_f31 = temp_r31 / 20.0f;
        Hu3DModelRotSet(lbl_1_bss_199C2[22], 0, (150.0f * temp_f31) + 30.0f, 0);
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(lbl_1_bss_199C2[22], lbl_1_bss_1990E[23], 0, 10, HU3D_MOTATTR_LOOP);
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[1], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
        temp_f31 = temp_r31 / 20.0f;
        Hu3DModelRotSet(lbl_1_bss_2D0, 0, -120.0f - (60.0f * temp_f31), 0);
        HuPrcVSleep();
    }
    HuAudFXPlay(1855);
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[0], 0, 10, HU3D_MOTATTR_LOOP);
    while (Hu3DMotionEndCheck(lbl_1_bss_199C2[11]) == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(1856);
    fn_1_861C(0);
    Hu3DModelAttrReset(lbl_1_bss_199C2[9], HU3D_MOTATTR_PAUSE);
    HuAudFXPlay(1863);
    while (Hu3DMotionTimeGet(lbl_1_bss_199C2[9]) < lbl_1_data_140[0]) {
        HuPrcVSleep();
    }
    HuAudFXPlay(1857);
    Hu3DMotionTimeSet(lbl_1_bss_199C2[9], lbl_1_data_140[0]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[9], HU3D_MOTATTR_PAUSE);
    HuPrcSleep(20);
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[1], 0, 8, HU3D_MOTATTR_LOOP);
    sp1C.x = 124;
    sp1C.y = 0;
    sp1C.z = -180;
    for (temp_r31 = 0; temp_r31 <= 40; temp_r31++) {
        temp_f31 = temp_r31 / 40.0f;
        Hu3DModelPosSet(lbl_1_bss_2D0, temp_f31 * sp1C.x, temp_f31 * sp1C.y, (temp_f31 * sp1C.z) + 250.0f);
        if (temp_r31 <= 20) {
            temp_f30 = atan2d(sp1C.x, sp1C.z) - 180.0;
            Hu3DModelRotSet(lbl_1_bss_2D0, 0, (temp_f30 * (temp_r31 / 20.0)) + 180.0, 0);
        }
        if (temp_r31 > 30) {
            temp_r29 = temp_r31 - 30;
            temp_f30 = atan2d(sp1C.x, sp1C.z) - 180.0;
            Hu3DModelRotSet(lbl_1_bss_2D0, 0, (temp_f30 * (1.0 - (temp_r29 / 10.0))) + 180.0, 0);
        }
        HuPrcVSleep();
    }
    lbl_1_bss_2D6 = -1;
    fn_1_9418(0);
    temp_r26 = fn_1_8DD0(0);
    lbl_1_bss_2D6 = lbl_1_bss_320[temp_r26];
    HuAudFXPlay(1859);
    fn_1_9CAC(0, temp_r26);
    for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
        lbl_1_bss_328[0].x = lbl_1_bss_328[0].y = lbl_1_bss_328[0].z = (0.1 * sind(temp_r31 * 18.0)) + 0.3;
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    Hu3DModelAttrSet(lbl_1_bss_199C2[64], HU3D_ATTR_DISPOFF);
    fn_1_8180(9);
    Hu3DMotionShiftSet(lbl_1_bss_199C2[22], lbl_1_bss_1990E[24], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        if (temp_r31 <= 10) {
            Hu3DModelRotSet(lbl_1_bss_199C2[22], 0, (90.0 * (temp_r31 / 10.0)) + 180.0, 0);
        }
        if (temp_r31 == 10) {
            CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[1], 0, 10, HU3D_MOTATTR_LOOP);
        }
        if (temp_r31 > 10 && temp_r31 <= 25) {
            temp_r29 = temp_r31 - 10;
            Hu3DModelRotSet(lbl_1_bss_2D0, 0, (90.0 * (temp_r29 / 15.0)) + 180.0, 0);
        }
        if (temp_r31 == 25) {
            CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[0], 0, 10, HU3D_MOTATTR_LOOP);
        }
        Hu3DModelPosSet(lbl_1_bss_199C2[22], (-300.0 * (1.0 - cosd(3.0 * temp_r31))) + (-160.0), 0, 155);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(lbl_1_bss_199C2[22], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_199C2[26], HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(lbl_1_bss_199C2[26], lbl_1_bss_1990E[28]);
    Hu3DModelRotSet(lbl_1_bss_199C2[26], 0, 90, 0);
    for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
        Hu3DModelPosSet(lbl_1_bss_199C2[26], (-300.0 * cosd(1.5 * temp_r31)) + (-160.0), 0, 155);
        if (temp_r31 == 50) {
            Hu3DMotionShiftSet(lbl_1_bss_199C2[26], lbl_1_bss_1990E[27], 0, 10, HU3D_MOTATTR_LOOP);
        }
        HuPrcVSleep();
    }
    #if VERSION_PAL
    HuWinInsertMesSizeGet((GWPlayerCfg[lbl_1_bss_2D6].character+1)-1, 0);
    #endif
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x1C, 0x02));
    temp_r30 = HuWinExCreateStyled(-10000, 340, sp8[0], sp8[1], -1, 1);
    HuWinExAnimIn(temp_r30);
    HuWinMesPalSet(temp_r30, 7, 0, 0, 0);
    fn_1_6D80(temp_r30);
    HuWinInsertMesSet(temp_r30, GWPlayerCfg[lbl_1_bss_2D6].character, 0);
    HuWinMesSet(temp_r30, MAKE_MESSID(0x1C, 0x02));
    HuWinMesWait(temp_r30);
    HuWinExAnimOut(temp_r30);
    HuWinExCleanup(temp_r30);
    HuWinComKeyReset();
    Hu3DMotionShiftSet(lbl_1_bss_199C2[26], lbl_1_bss_1990E[28], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
        temp_f31 = temp_r31 / 20.0f;
        Hu3DModelRotSet(lbl_1_bss_199C2[26], 0, (temp_f31 * 90.0f) + 90.0f, 0);
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(lbl_1_bss_199C2[26], lbl_1_bss_1990E[27], 0, 10, HU3D_MOTATTR_LOOP);
    fn_1_861C(1);
    Hu3DModelAttrReset(lbl_1_bss_199C2[9], HU3D_MOTATTR_PAUSE);
    HuAudFXPlay(1862);
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[1], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
        temp_f31 = 1.0 - (temp_r31 / 20.0f);
        Hu3DModelRotSet(lbl_1_bss_2D0, 0, (temp_f31 * 90.0f) + 180.0f, 0);
        HuPrcVSleep();
    }
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[0], 0, 10, HU3D_MOTATTR_LOOP);
    while (Hu3DMotionTimeGet(lbl_1_bss_199C2[9]) < lbl_1_data_140[1]) {
        if (Hu3DMotionTimeGet(lbl_1_bss_199C2[9]) == 128.0f) {
            HuAudFXPlay(1850);
        }
        if (Hu3DMotionTimeGet(lbl_1_bss_199C2[9]) == 200.0f) {
            HuAudFXPlay(1863);
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1857);
    Hu3DMotionTimeSet(lbl_1_bss_199C2[9], lbl_1_data_140[1]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[9], HU3D_MOTATTR_PAUSE);
    HuPrcSleep(20);
    lbl_1_bss_2D4 = -1;
    fn_1_9418(1);
    temp_r26 = fn_1_8DD0(1);
    lbl_1_bss_2D4 = lbl_1_bss_320[temp_r26];
    HuAudFXPlay(1860);
    fn_1_9CAC(1, temp_r26);
    for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
        lbl_1_bss_328[1].x = lbl_1_bss_328[1].y = lbl_1_bss_328[1].z = (0.1 * sind(temp_r31 * 18.0)) + 0.3;
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    Hu3DModelAttrSet(lbl_1_bss_199C2[64], HU3D_ATTR_DISPOFF);
    fn_1_8180(9);
    Hu3DMotionShiftSet(lbl_1_bss_199C2[26], lbl_1_bss_1990E[28], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        if (temp_r31 <= 10) {
            Hu3DModelRotSet(lbl_1_bss_199C2[26], 0, (90.0 * (temp_r31 / 10.0)) + 180.0, 0);
        }
        if (temp_r31 == 10) {
            CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[1], 0, 10, HU3D_MOTATTR_LOOP);
        }
        if (temp_r31 > 10 && temp_r31 <= 25) {
            temp_r29 = temp_r31 - 10;
            Hu3DModelRotSet(lbl_1_bss_2D0, 0, (90.0 * (temp_r29 / 15.0)) + 180.0, 0);
        }
        if (temp_r31 == 25) {
            CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[0], 0, 10, HU3D_MOTATTR_LOOP);
        }
        Hu3DModelPosSet(lbl_1_bss_199C2[26], (-400.0 * (1.0 - cosd(3.0 * temp_r31))) + (-160.0), 0, 155);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(lbl_1_bss_199C2[26], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_199C2[30], HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(lbl_1_bss_199C2[30], lbl_1_bss_1990E[32]);
    Hu3DModelRotSet(lbl_1_bss_199C2[30], 0, 90, 0);
    for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
        Hu3DModelPosSet(lbl_1_bss_199C2[30], (-400.0 * cosd(1.5 * temp_r31)) + (-160.0), 100, 155);
        if (temp_r31 == 50) {
            Hu3DMotionShiftSet(lbl_1_bss_199C2[30], lbl_1_bss_1990E[31], 0, 10, HU3D_MOTATTR_LOOP);
        }
        HuPrcVSleep();
    }
    #if VERSION_PAL
    HuWinInsertMesSizeGet((GWPlayerCfg[lbl_1_bss_2D6].character+1)-1, 0);
    HuWinInsertMesSizeGet((GWPlayerCfg[lbl_1_bss_2D4].character+1)-1, 2);
    #endif
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x1C, 0x03));
    temp_r30 = HuWinExCreateStyled(-10000, 340, sp8[0], sp8[1], -1, 1);
    HuWinExAnimIn(temp_r30);
    HuWinMesPalSet(temp_r30, 7, 0, 0, 0);
    fn_1_6D80(temp_r30);
    HuWinInsertMesSet(temp_r30, GWPlayerCfg[lbl_1_bss_2D6].character, 0);
    HuWinInsertMesSet(temp_r30, GWPlayerCfg[lbl_1_bss_2D4].character, 2);
    HuWinMesSet(temp_r30, MAKE_MESSID(0x1C, 0x03));
    HuWinMesWait(temp_r30);
    HuWinExAnimOut(temp_r30);
    HuWinExCleanup(temp_r30);
    HuWinComKeyReset();
    Hu3DMotionShiftSet(lbl_1_bss_199C2[30], lbl_1_bss_1990E[32], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
        temp_f31 = temp_r31 / 20.0f;
        Hu3DModelRotSet(lbl_1_bss_199C2[30], 0, (temp_f31 * 90.0f) + 90.0f, 0);
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(lbl_1_bss_199C2[30], lbl_1_bss_1990E[31], 0, 10, HU3D_MOTATTR_LOOP);
    fn_1_861C(2);
    Hu3DModelAttrReset(lbl_1_bss_199C2[9], HU3D_MOTATTR_PAUSE);
    HuAudFXPlay(1862);
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[1], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
        temp_f31 = 1.0 - (temp_r31 / 20.0f);
        Hu3DModelRotSet(lbl_1_bss_2D0, 0, (temp_f31 * 90.0f) + 180.0f, 0);
        HuPrcVSleep();
    }
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[0], 0, 10, HU3D_MOTATTR_LOOP);
    while (Hu3DMotionTimeGet(lbl_1_bss_199C2[9]) < lbl_1_data_140[2]) {
        if (Hu3DMotionTimeGet(lbl_1_bss_199C2[9]) == 300.0f) {
            HuAudFXPlay(1850);
        }
        if (Hu3DMotionTimeGet(lbl_1_bss_199C2[9]) == 372.0f) {
            HuAudFXPlay(1863);
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1857);
    Hu3DMotionTimeSet(lbl_1_bss_199C2[9], lbl_1_data_140[2]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[9], HU3D_MOTATTR_PAUSE);
    HuPrcSleep(20);
    lbl_1_bss_2D2 = -1;
    fn_1_9418(2);
    temp_r26 = fn_1_8DD0(2);
    lbl_1_bss_2D2 = temp_r26;
    HuAudFXPlay(1861);
    fn_1_9CAC(2, temp_r26);
    for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
        lbl_1_bss_328[2].x = lbl_1_bss_328[2].y = lbl_1_bss_328[2].z = (0.1 * sind(temp_r31 * 18.0)) + 0.3;
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    Hu3DModelAttrSet(lbl_1_bss_199C2[64], HU3D_ATTR_DISPOFF);
    fn_1_8180(9);
    Hu3DMotionShiftSet(lbl_1_bss_199C2[30], lbl_1_bss_1990E[32], 0, 10, HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        if (temp_r31 <= 10) {
            Hu3DModelRotSet(lbl_1_bss_199C2[30], 0, (90.0 * (temp_r31 / 10.0)) + 180.0, 0);
        }
        if (temp_r31 == 10) {
            CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[1], 0, 10, HU3D_MOTATTR_LOOP);
        }
        if (temp_r31 > 10 && temp_r31 <= 25) {
            temp_r29 = temp_r31 - 10;
            Hu3DModelRotSet(lbl_1_bss_2D0, 0, (90.0 * (temp_r29 / 15.0)) + 180.0, 0);
        }
        if (temp_r31 == 25) {
            CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[0], 0, 10, HU3D_MOTATTR_LOOP);
        }
        Hu3DModelPosSet(lbl_1_bss_199C2[30], (-400.0 * (1.0 - cosd(3.0 * temp_r31))) + (-160.0), 100, 155);
        HuPrcVSleep();
    }
    HuAudFXPlay(1862);
    Hu3DModelAttrReset(lbl_1_bss_199C2[9], HU3D_MOTATTR_PAUSE);
    while (Hu3DMotionEndCheck(lbl_1_bss_199C2[9]) == 0) {
        HuPrcVSleep();
    }
    Hu3DModelAttrReset(lbl_1_bss_199C2[11], HU3D_MOTATTR_PAUSE);
    HuAudFXPlay(1855);
    Hu3DModelAttrSet(lbl_1_bss_199C2[11], HU3D_MOTATTR_REV);
    while (Hu3DMotionTimeGet(lbl_1_bss_199C2[11]) > 0.0f) {
        if (Hu3DMotionTimeGet(lbl_1_bss_199C2[11]) == 25.0f) {
            HuAudFXPlay(1854);
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1856);
    Hu3DModelAttrReset(lbl_1_bss_199C2[34], HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(lbl_1_bss_199C2[34], lbl_1_bss_1990E[36]);
    Hu3DModelRotSet(lbl_1_bss_199C2[34], 0, 90, 0);
    for (temp_r31 = 0; temp_r31 <= 60; temp_r31++) {
        Hu3DModelPosSet(lbl_1_bss_199C2[34], -154.0 + (-500.0 * (1.0 - (temp_r31 / 60.0f))), 0, -403);
        if (temp_r31 > 20) {
            temp_r29 = temp_r31 - 40;
            Hu3DModelRotSet(lbl_1_bss_199C2[34], 0, (30.0 * (1.0 - (temp_r29 / 20.0f))) + 60.0, 0);
        }
        if (temp_r31 == 50) {
            Hu3DMotionShiftSet(lbl_1_bss_199C2[34], lbl_1_bss_1990E[35], 0, 10, HU3D_MOTATTR_LOOP);
        }
        if (temp_r31 == 40) {
            CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[1], 0, 10, HU3D_MOTATTR_LOOP);
        }
        if (temp_r31 >= 40) {
            temp_r29 = temp_r31 - 40;
            Hu3DModelRotSet(lbl_1_bss_2D0, 0, -90.0 - (45.0 * (temp_r29 / 20.0)), 0);
        }
        HuPrcVSleep();
    }
    fn_1_8180(7);
    temp_r23 = &Hu3DData[lbl_1_bss_2D0];
    sp1C.x = 0;
    sp1C.y = 0;
    sp1C.z = -200;
    sp10 = temp_r23->pos;
    VECSubtract(&sp1C, &sp10, &sp1C);
    for (temp_r31 = 0; temp_r31 <= 30; temp_r31++) {
        temp_f31 = temp_r31 / 30.0;
        Hu3DModelPosSet(lbl_1_bss_2D0, (temp_f31 * sp1C.x) + sp10.x, (temp_f31 * sp1C.y) + sp10.y, (temp_f31 * sp1C.z) + sp10.z);
        HuPrcVSleep();
    }
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[0], 0, 10, HU3D_MOTATTR_LOOP);
    BoardStatusShowSet(lbl_1_bss_2D6, 1);
    BoardStatusShowSet(lbl_1_bss_2D4, 1);
    sp1C.x = -112;
    sp1C.y = 200;
    sp1C.z = 0;
    BoardStatusPosSet(lbl_1_bss_2D6, &sp1C);
    sp1C.x = 688;
    sp1C.y = 200;
    sp1C.z = 0;
    BoardStatusPosSet(lbl_1_bss_2D4, &sp1C);
    for (temp_r31 = 0; temp_r31 <= 20; temp_r31++) {
        if (temp_r31 > 10) {
            temp_r29 = temp_r31 - 10;
            sp1C.x = 138.0 - (250.0 * cosd(temp_r29 * 9.0));
            sp1C.y = 200;
            sp1C.z = 0;
            BoardStatusTargetPosSet(lbl_1_bss_2D6, &sp1C);
            sp1C.x = 438.0 + (250.0 * cosd(temp_r29 * 9.0));
            sp1C.y = 200;
            sp1C.z = 0;
            BoardStatusTargetPosSet(lbl_1_bss_2D4, &sp1C);
        }
        HuPrcVSleep();
    }
    temp_r25 = 1;
    switch (lbl_1_bss_2D2) {
        case 0:
            if (GWPlayer[lbl_1_bss_2D6].coins <= 0 && GWPlayer[lbl_1_bss_2D4].coins <= 0) {
                temp_r28 = MAKE_MESSID(0x1C, 0x16);
                temp_r25 = 0;
            }
            else {
                temp_r28 = MAKE_MESSID(0x1C, 0x06);
            }
            temp_r24 = MAKE_MESSID(0x1C, 0x09);
            break;

        case 1:
            if (GWPlayer[lbl_1_bss_2D6].coins <= 0 && GWPlayer[lbl_1_bss_2D4].coins <= 0 && GWPlayer[lbl_1_bss_2D6].stars <= 0
                && GWPlayer[lbl_1_bss_2D4].stars <= 0) {
                temp_r25 = 0;
                temp_r28 = MAKE_MESSID(0x1C, 0x17);
            }
            else {
                temp_r28 = MAKE_MESSID(0x1C, 0x06);
            }
            temp_r24 = MAKE_MESSID(0x1C, 0x0D);
            break;

        case 2:
            if (GWPlayer[lbl_1_bss_2D6].stars > 0) {
                temp_r28 = MAKE_MESSID(0x1C, 0x04);
            }
            else {
                temp_r28 = MAKE_MESSID(0x1C, 0x08);
                temp_r25 = 0;
            }
            temp_r24 = MAKE_MESSID(0x1C, 0x0A);
            break;

        case 3:
            if (GWPlayer[lbl_1_bss_2D6].stars <= 0 && GWPlayer[lbl_1_bss_2D4].stars <= 0) {
                temp_r25 = 0;
                temp_r28 = MAKE_MESSID(0x1C, 0x15);
            }
            else {
                temp_r28 = MAKE_MESSID(0x1C, 0x06);
            }
            temp_r24 = MAKE_MESSID(0x1C, 0x0E);
            break;

        case 4:
            if (GWPlayer[lbl_1_bss_2D6].stars > 0) {
                temp_r28 = MAKE_MESSID(0x1C, 0x04);
            }
            else {
                temp_r28 = MAKE_MESSID(0x1C, 0x08);
                temp_r25 = 0;
            }
            temp_r24 = MAKE_MESSID(0x1C, 0x0C);
            break;

        case 5:
        case 6:
            if (GWPlayer[lbl_1_bss_2D6].coins > 0) {
                temp_r28 = MAKE_MESSID(0x1C, 0x04);
            }
            else {
                temp_r28 = MAKE_MESSID(0x1C, 0x07);
                temp_r25 = 0;
            }
            temp_r24 = MAKE_MESSID(0x1C, 0x0B);
            break;

        default:
            break;
    }
    HuWinInsertMesSizeGet((8 + GWPlayerCfg[lbl_1_bss_2D6].character) - 8, 0);
    HuWinInsertMesSizeGet(temp_r24, 1);
    HuWinInsertMesSizeGet((8 + GWPlayerCfg[lbl_1_bss_2D4].character) - 8, 2);
    HuWinMesMaxSizeGet(1, sp8, temp_r28);
    temp_r30 = HuWinExCreateStyled(-10000, 340, sp8[0], sp8[1], -1, 1);
    HuWinExAnimIn(temp_r30);
    HuWinMesPalSet(temp_r30, 7, 0, 0, 0);
    HuWinInsertMesSet(temp_r30, GWPlayerCfg[lbl_1_bss_2D6].character, 0);
    HuWinInsertMesSet(temp_r30, temp_r24, 1);
    HuWinInsertMesSet(temp_r30, GWPlayerCfg[lbl_1_bss_2D4].character, 2);
    fn_1_6D80(temp_r30);
    HuWinMesSet(temp_r30, temp_r28);
    HuWinMesWait(temp_r30);
    HuWinExAnimOut(temp_r30);
    HuWinExCleanup(temp_r30);
    HuWinComKeyReset();
    if (temp_r25) {
        fn_1_4DEC();
        HuPrcSleep(60);
    }
    else {
        HuPrcSleep(30);
    }
    sp1C.x = -112;
    sp1C.y = 200;
    sp1C.z = 0;
    BoardStatusTargetPosSet(lbl_1_bss_2D6, &sp1C);
    sp1C.x = 688;
    sp1C.y = 200;
    sp1C.z = 0;
    BoardStatusTargetPosSet(lbl_1_bss_2D4, &sp1C);
    while (!BoardStatusStopCheck(lbl_1_bss_2D6)) {
        HuPrcVSleep();
    }
    for (temp_r31 = 0; temp_r31 <= 20; temp_r31++) {
        for (temp_r27 = 0; temp_r27 < 3; temp_r27++) {
            lbl_1_bss_34C[temp_r27].y = (180.0 * cosd(4.5 * temp_r31)) - 100.0;
        }
        HuPrcVSleep();
    }
    fn_1_3B7C();
    lbl_1_bss_2FC = 1;
    while (1) {
        lbl_1_bss_288[0] += 10.0f;
        HuPrcVSleep();
    }
}

void fn_1_3B7C(void)
{
    float temp_f31;
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    float sp8[2];
    fn_1_8180(8);
    for (temp_r30 = 0; temp_r30 < 100; temp_r30++) {
        temp_r31 = temp_r30;
        if (temp_r31 == 0) {
            Hu3DMotionShiftSet(lbl_1_bss_199C2[34], lbl_1_bss_1990E[36], 0, 10, HU3D_MOTATTR_LOOP);
        }
        if (temp_r31 <= 20) {
            Hu3DModelRotSet(lbl_1_bss_199C2[34], 0, (30.0 * (temp_r31 / 20.0)) + 60.0, 0);
        }
        if (temp_r31 > 10 && temp_r31 <= 60) {
            temp_r29 = temp_r31 - 10;
            Hu3DModelPosSet(lbl_1_bss_199C2[34], -154.0f + (354.0 * (temp_r29 / 50.0)), 0, -403);
        }
        if (temp_r31 > 50 && temp_r31 <= 70) {
            temp_r29 = temp_r31 - 50;
            Hu3DModelRotSet(lbl_1_bss_199C2[34], 0, (110.0 * (1.0 - (temp_r29 / 20.0))) + -20.0, 0);
        }
        if (temp_r31 == 70) {
            Hu3DMotionShiftSet(lbl_1_bss_199C2[34], lbl_1_bss_1990E[35], 0, 10, HU3D_MOTATTR_LOOP);
        }
        temp_r31 = temp_r30;
        if (temp_r31 == 0) {
            Hu3DMotionSet(lbl_1_bss_199C2[18], lbl_1_bss_1990E[20]);
            temp_f31 = atan2d(400.0, 200.0) + 180.0;
            Hu3DModelRotSet(lbl_1_bss_199C2[18], 0, temp_f31, 0);
            Hu3DModelAttrReset(lbl_1_bss_199C2[18], HU3D_ATTR_DISPOFF);
        }
        if (temp_r31 <= 50) {
            Hu3DModelPosSet(lbl_1_bss_199C2[18], 400.0 * (1.0 - (temp_r31 / 50.0)), 0, -553.0 + (200.0 * (1.0 - (temp_r31 / 50.0))));
        }
        if (temp_r31 > 40 && temp_r31 <= 60) {
            temp_r29 = temp_r31 - 40;
            temp_f31 = atan2d(400.0, 200.0) + 180.0;
            Hu3DModelRotSet(lbl_1_bss_199C2[18], 0, temp_f31 * (1.0 - (temp_r29 / 20.0)), 0);
        }
        if (temp_r31 == 60) {
            Hu3DMotionShiftSet(lbl_1_bss_199C2[18], lbl_1_bss_1990E[19], 0, 10, HU3D_MOTATTR_LOOP);
        }
        if (temp_r30 >= 20) {
            temp_r31 = temp_r30 - 20;
            if (temp_r31 == 0) {
                Hu3DMotionSet(lbl_1_bss_199C2[26], lbl_1_bss_1990E[28]);
                temp_f31 = atan2d(-300.0, 200.0) + 180.0;
                Hu3DModelRotSet(lbl_1_bss_199C2[26], 0, temp_f31, 0);
                Hu3DModelAttrReset(lbl_1_bss_199C2[26], HU3D_ATTR_DISPOFF);
            }
            if (temp_r31 <= 40) {
                Hu3DModelPosSet(lbl_1_bss_199C2[26], -100.0 + (-300.0 * (1.0 - (temp_r31 / 40.0))), 0, -478.0 + (200.0 * (1.0 - (temp_r31 / 40.0))));
            }
            if (temp_r31 > 30 && temp_r31 <= 50) {
                temp_r29 = temp_r31 - 30;
                temp_f31 = atan2d(-300.0, 200.0) + 180.0;
                Hu3DModelRotSet(lbl_1_bss_199C2[26], 0, (temp_f31 - 10.0f) * (1.0 - (temp_r29 / 20.0)) + 10.0, 0);
            }
            if (temp_r31 == 50) {
                Hu3DMotionShiftSet(lbl_1_bss_199C2[26], lbl_1_bss_1990E[27], 0, 10, HU3D_MOTATTR_LOOP);
            }
        }
        if (temp_r30 >= 30) {
            temp_r31 = temp_r30 - 30;
            if (temp_r31 == 0) {
                Hu3DMotionSet(lbl_1_bss_199C2[30], lbl_1_bss_1990E[32]);
                temp_f31 = atan2d(200.0, 500.0) + 180.0;
                Hu3DModelRotSet(lbl_1_bss_199C2[30], 0, temp_f31, 0);
                Hu3DModelAttrReset(lbl_1_bss_199C2[30], HU3D_ATTR_DISPOFF);
            }
            if (temp_r31 <= 40) {
                Hu3DModelPosSet(lbl_1_bss_199C2[30], 100.0 + (200.0 * (1.0 - (temp_r31 / 40.0))), 100, -478.0 + (500.0 * (1.0 - (temp_r31 / 40.0))));
            }
            if (temp_r31 > 30 && temp_r31 <= 50) {
                temp_r29 = temp_r31 - 30;
                temp_f31 = atan2d(200.0, 500.0) + 180.0;
                Hu3DModelRotSet(lbl_1_bss_199C2[30], 0, (temp_f31 - -10.0f) * (1.0 - (temp_r29 / 20.0)) + -10.0, 0);
            }
            if (temp_r31 == 50) {
                Hu3DMotionShiftSet(lbl_1_bss_199C2[30], lbl_1_bss_1990E[31], 0, 10, HU3D_MOTATTR_LOOP);
            }
        }
        if (temp_r30 >= 40) {
            temp_r31 = temp_r30 - 40;
            if (temp_r31 == 0) {
                Hu3DMotionSet(lbl_1_bss_199C2[22], lbl_1_bss_1990E[24]);
                temp_f31 = atan2d(-300.0, 100.0) + 180.0;
                Hu3DModelRotSet(lbl_1_bss_199C2[22], 0, temp_f31, 0);
                Hu3DModelAttrReset(lbl_1_bss_199C2[22], HU3D_ATTR_DISPOFF);
            }
            if (temp_r31 <= 40) {
                Hu3DModelPosSet(lbl_1_bss_199C2[22], -200.0 + (-300.0 * (1.0 - (temp_r31 / 40.0))), 0, -403.0 + (100.0 * (1.0 - (temp_r31 / 40.0))));
            }
            if (temp_r31 > 30 && temp_r31 <= 50) {
                temp_r29 = temp_r31 - 30;
                temp_f31 = atan2d(-300.0, 100.0) + 180.0;
                Hu3DModelRotSet(lbl_1_bss_199C2[22], 0, (temp_f31 - 20.0f) * (1.0 - (temp_r29 / 20.0)) + 20.0, 0);
            }
            if (temp_r31 == 50) {
                Hu3DMotionShiftSet(lbl_1_bss_199C2[22], lbl_1_bss_1990E[23], 0, 10, HU3D_MOTATTR_LOOP);
            }
        }
        if (temp_r30 >= 30) {
            temp_r31 = temp_r30 - 30;
            if (temp_r31 == 0) {
                Hu3DMotionShiftSet(lbl_1_bss_2D0, lbl_1_bss_2C0[1], 0, 10, HU3D_MOTATTR_LOOP);
            }
            if (temp_r31 <= 20) {
                Hu3DModelRotSet(lbl_1_bss_2D0, 0, -135.0 - (45.0 * (temp_r31 / 20.0)), 0);
            }
            if (temp_r31 == 20) {
                Hu3DMotionShiftSet(lbl_1_bss_2D0, lbl_1_bss_2C0[0], 0, 10, HU3D_MOTATTR_LOOP);
            }
        }
        HuPrcVSleep();
    }
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x1C, 0x05));
    temp_r28 = HuWinExCreateStyled(-10000, 340, sp8[0], sp8[1], -1, 1);
    HuWinExAnimIn(temp_r28);
    HuWinMesPalSet(temp_r28, 7, 0, 0, 0);
    fn_1_6D80(temp_r28);
    HuAudFXPlay(55);
    HuAudFXPlay(64);
    HuAudFXPlay(67);
    HuAudFXPlay(70);
    HuAudFXPlay(75);
    HuWinMesSet(temp_r28, MAKE_MESSID(0x1C, 0x05));
    HuWinMesWait(temp_r28);
    HuWinExAnimOut(temp_r28);
    HuWinExCleanup(temp_r28);
    HuWinComKeyReset();
    Hu3DMotionShiftSet(lbl_1_bss_199C2[18], lbl_1_bss_1990E[21], 0, 10, HU3D_MOTATTR_LOOP);
    HuPrcSleep(5);
    Hu3DMotionShiftSet(lbl_1_bss_199C2[22], lbl_1_bss_1990E[25], 0, 10, HU3D_MOTATTR_LOOP);
    Hu3DMotionShiftSet(lbl_1_bss_199C2[26], lbl_1_bss_1990E[29], 0, 10, HU3D_MOTATTR_LOOP);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(lbl_1_bss_199C2[30], lbl_1_bss_1990E[33], 0, 10, HU3D_MOTATTR_LOOP);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(lbl_1_bss_199C2[34], lbl_1_bss_1990E[37], 0, 10, HU3D_MOTATTR_LOOP);
}

void fn_1_55B0(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4);

void fn_1_4DEC(void)
{
    s16 coins;
    s16 stars;
    switch (lbl_1_bss_2D2) {
        case 0:
            lbl_1_bss_4 = 2;
            if (GWPlayer[lbl_1_bss_2D6].coins >= GWPlayer[lbl_1_bss_2D4].coins) {
                fn_1_55B0(2, lbl_1_bss_2D6, lbl_1_bss_2D4, GWPlayer[lbl_1_bss_2D6].coins, 1);
                fn_1_55B0(3, lbl_1_bss_2D4, lbl_1_bss_2D6, GWPlayer[lbl_1_bss_2D4].coins, 0);
            }
            else {
                fn_1_55B0(2, lbl_1_bss_2D6, lbl_1_bss_2D4, GWPlayer[lbl_1_bss_2D6].coins, 0);
                fn_1_55B0(3, lbl_1_bss_2D4, lbl_1_bss_2D6, GWPlayer[lbl_1_bss_2D4].coins, 1);
            }
            break;

        case 1:
            lbl_1_bss_4 = 2;
            if (GWPlayer[lbl_1_bss_2D6].coins >= GWPlayer[lbl_1_bss_2D4].coins) {
                fn_1_55B0(2, lbl_1_bss_2D6, lbl_1_bss_2D4, GWPlayer[lbl_1_bss_2D6].coins, 1);
                fn_1_55B0(3, lbl_1_bss_2D4, lbl_1_bss_2D6, GWPlayer[lbl_1_bss_2D4].coins, 0);
            }
            else {
                fn_1_55B0(2, lbl_1_bss_2D6, lbl_1_bss_2D4, GWPlayer[lbl_1_bss_2D6].coins, 0);
                fn_1_55B0(3, lbl_1_bss_2D4, lbl_1_bss_2D6, GWPlayer[lbl_1_bss_2D4].coins, 1);
            }
            while (lbl_1_bss_4 != 0) {
                HuPrcVSleep();
            }
            lbl_1_bss_4 = 2;
            if (GWPlayer[lbl_1_bss_2D6].stars >= GWPlayer[lbl_1_bss_2D4].stars) {
                fn_1_55B0(0, lbl_1_bss_2D6, lbl_1_bss_2D4, GWPlayer[lbl_1_bss_2D6].stars, 1);
                fn_1_55B0(1, lbl_1_bss_2D4, lbl_1_bss_2D6, GWPlayer[lbl_1_bss_2D4].stars, 0);
            }
            else {
                fn_1_55B0(0, lbl_1_bss_2D6, lbl_1_bss_2D4, GWPlayer[lbl_1_bss_2D6].stars, 0);
                fn_1_55B0(1, lbl_1_bss_2D4, lbl_1_bss_2D6, GWPlayer[lbl_1_bss_2D4].stars, 1);
            }
            break;

        case 2:
            lbl_1_bss_4 = 1;
            fn_1_55B0(0, lbl_1_bss_2D6, lbl_1_bss_2D4, 1, 1);
            break;

        case 3:
            lbl_1_bss_4 = 2;
            if (GWPlayer[lbl_1_bss_2D6].stars >= GWPlayer[lbl_1_bss_2D4].stars) {
                fn_1_55B0(0, lbl_1_bss_2D6, lbl_1_bss_2D4, GWPlayer[lbl_1_bss_2D6].stars, 1);
                fn_1_55B0(1, lbl_1_bss_2D4, lbl_1_bss_2D6, GWPlayer[lbl_1_bss_2D4].stars, 0);
            }
            else {
                fn_1_55B0(0, lbl_1_bss_2D6, lbl_1_bss_2D4, GWPlayer[lbl_1_bss_2D6].stars, 0);
                fn_1_55B0(1, lbl_1_bss_2D4, lbl_1_bss_2D6, GWPlayer[lbl_1_bss_2D4].stars, 1);
            }
            break;

        case 4:
            lbl_1_bss_4 = 1;
            if (GWPlayer[lbl_1_bss_2D6].stars < 2) {
                stars = GWPlayer[lbl_1_bss_2D6].stars;
            }
            else {
                stars = 2;
            }
            fn_1_55B0(1, lbl_1_bss_2D6, lbl_1_bss_2D4, stars, 1);
            break;

        case 5:
        case 6:
            lbl_1_bss_4 = 1;
            if (GWPlayer[lbl_1_bss_2D6].coins < 20) {
                coins = GWPlayer[lbl_1_bss_2D6].coins;
            }
            else {
                coins = 20;
            }
            fn_1_55B0(2, lbl_1_bss_2D6, lbl_1_bss_2D4, coins, 1);
            break;

        default:
            break;
    }
    while (lbl_1_bss_4 > 0) {
        HuPrcVSleep();
    }
}

typedef struct work_5774 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6[20];
    s16 unk2E[20];
    float unk58;
    s32 unk5C;
} Work5774;

void fn_1_5774(void);
void fn_1_5E68(void);

void fn_1_55B0(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4)
{
    Work5774 *work;
    Process *newProcess;
    float temp_f31;

    if (arg3 == 0) {
        lbl_1_bss_4--;
        return;
    }
    switch (arg0) {
        case 0:
            newProcess = HuPrcChildCreate(fn_1_5774, 100, 8192, 0, lbl_1_bss_308);
            temp_f31 = -100;
            break;

        case 1:
            newProcess = HuPrcChildCreate(fn_1_5774, 100, 8192, 0, lbl_1_bss_308);
            temp_f31 = -50;
            break;

        case 2:
            newProcess = HuPrcChildCreate(fn_1_5E68, 100, 8192, 0, lbl_1_bss_308);
            temp_f31 = -100;
            break;

        case 3:
            newProcess = HuPrcChildCreate(fn_1_5E68, 100, 8192, 0, lbl_1_bss_308);
            temp_f31 = -50;
            break;
    }
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work5774), MEMORY_DEFAULT_NUM);
    newProcess->user_data = work;
    work->unk0 = arg1;
    work->unk2 = arg2;
    work->unk4 = arg3;
    work->unk58 = temp_f31;
    work->unk5C = arg4;
}

void fn_1_5774(void)
{
    float temp_f31;
    float temp_f30;

    Work5774 *temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    Process *temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r23;
    s32 temp_r22;
    s32 temp_r21;

    Vec sp20;
    Vec sp14;
    Vec sp8;

    temp_r28 = HuPrcCurrentGet();
    temp_r31 = temp_r28->user_data;
    temp_r23 = 0;
    BoardStatusPosGet(temp_r31->unk0, &sp20);
    BoardStatusPosGet(temp_r31->unk2, &sp14);
    for (temp_r30 = 0; temp_r30 < 20; temp_r30++) {
        temp_r31->unk6[temp_r30] = -1;
    }
    temp_r25 = temp_r31->unk4;
    temp_r27 = temp_r25;
    temp_f31 = 300 / temp_r27;
    if (temp_f31 < 15.0f) {
        temp_r24 = 1;
    }
    else {
        temp_r24 = 3;
    }
    temp_f31 -= temp_r24 + 1;
    if (temp_f31 < 15.0f) {
        temp_f31 = 15.0f;
    }
    if (temp_f31 > 40.0f) {
        temp_f31 = 40.0f;
    }
    if (temp_r31->unk5C) {
        temp_r22 = HuAudFXPlay(1864);
        temp_r21 = HuAudFXPlay(24);
    }
    while (1) {
        if (temp_r25 > 0) {
            if (((temp_r23++) & temp_r24) == 0) {
                for (temp_r30 = 0; temp_r30 < 20; temp_r30++) {
                    if (lbl_1_bss_148[temp_r30][1] == 0) {
                        break;
                    }
                }
                if (temp_r30 != 20) {
                    for (temp_r29 = 0; temp_r29 < 20; temp_r29++) {
                        if (temp_r31->unk6[temp_r29] == -1) {
                            lbl_1_bss_148[temp_r30][1] = 1;
                            temp_r31->unk6[temp_r29] = temp_r30;
                            temp_r31->unk2E[temp_r29] = 0;
                            GWStarsSet(temp_r31->unk0, GWPlayer[temp_r31->unk0].stars - 1);
                            temp_r25--;
                            break;
                        }
                    }
                }
            }
        }
        for (temp_r30 = 0; temp_r30 < 20; temp_r30++) {
            if (temp_r31->unk6[temp_r30] == -1) {
                continue;
            }
            temp_r26 = lbl_1_bss_148[temp_r31->unk6[temp_r30]][0];
            Hu3DModelAttrReset(temp_r26, HU3D_ATTR_DISPOFF);
            temp_r31->unk2E[temp_r30]++;
            if (temp_r31->unk2E[temp_r30] > temp_f31) {
                Hu3DModelAttrSet(temp_r26, HU3D_ATTR_DISPOFF);
                lbl_1_bss_148[temp_r31->unk6[temp_r30]][1] = 0;
                temp_r31->unk6[temp_r30] = -1;
                GWStarsSet(temp_r31->unk2, GWPlayer[temp_r31->unk2].stars + 1);
                temp_r27--;
            }
            else {
                temp_f30 = 0.1f;
                if (temp_r31->unk2E[temp_r30] < temp_f31 / 2.0f) {
                    temp_f30 = 0.1 * sind((90.0 / (temp_f31 / 2.0f)) * temp_r31->unk2E[temp_r30]);
                }
                if (temp_r31->unk2E[temp_r30] > temp_f31 / 2.0f) {
                    temp_f30 = 0.1 * cosd((90.0 / (temp_f31 / 2.0f)) * (temp_r31->unk2E[temp_r30] - (temp_f31 / 2.0f)));
                }
                Hu3DModelScaleSet(temp_r26, temp_f30, temp_f30, temp_f30);
                sp8.x = (sp14.x - sp20.x) * (temp_r31->unk2E[temp_r30] / temp_f31) + sp20.x;
                sp8.y = sp20.y + (temp_r31->unk58 * sind((180.0 / temp_f31) * temp_r31->unk2E[temp_r30]));
                sp8.z = 200;
                Hu3D2Dto3D(&sp8, 1, &sp8);
                Hu3DModelPosSetV(temp_r26, &sp8);
            }
        }
        if (temp_r27 <= 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(8);
    if (temp_r31->unk5C) {
        HuAudFXStop(temp_r22);
        HuAudFXStop(temp_r21);
    }
    lbl_1_bss_4--;
    HuMemDirectFree(temp_r28->user_data);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_5E68(void)
{
    float temp_f31;
    float temp_f30;

    Work5774 *temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    Process *temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r23;
    s32 temp_r22;
    s32 temp_r21;

    Vec sp20;
    Vec sp14;
    Vec sp8;

    temp_r28 = HuPrcCurrentGet();
    temp_r31 = temp_r28->user_data;
    temp_r23 = 0;
    BoardStatusPosGet(temp_r31->unk0, &sp20);
    BoardStatusPosGet(temp_r31->unk2, &sp14);
    for (temp_r30 = 0; temp_r30 < 20; temp_r30++) {
        temp_r31->unk6[temp_r30] = -1;
    }
    temp_r25 = temp_r31->unk4;
    temp_r27 = temp_r25;
    temp_f31 = 300 / temp_r27;
    if (temp_f31 < 15.0f) {
        temp_r24 = 1;
    }
    else {
        temp_r24 = 3;
    }
    temp_f31 -= temp_r24 + 1;
    if (temp_f31 < 15.0f) {
        temp_f31 = 15.0f;
    }
    if (temp_f31 > 40.0f) {
        temp_f31 = 40.0f;
    }
    if (temp_r31->unk5C) {
        temp_r22 = HuAudFXPlay(1864);
        temp_r21 = HuAudFXPlay(23);
    }
    while (1) {
        if (temp_r25 > 0) {
            if (((temp_r23++) & temp_r24) == 0) {
                for (temp_r30 = 0; temp_r30 < 20; temp_r30++) {
                    if (lbl_1_bss_8[temp_r30][1] == 0) {
                        break;
                    }
                }
                if (temp_r30 != 20) {
                    for (temp_r29 = 0; temp_r29 < 20; temp_r29++) {
                        if (temp_r31->unk6[temp_r29] == -1) {
                            lbl_1_bss_8[temp_r30][1] = 1;
                            temp_r31->unk6[temp_r29] = temp_r30;
                            temp_r31->unk2E[temp_r29] = 0;
                            GWCoinsSet(temp_r31->unk0, GWPlayer[temp_r31->unk0].coins - 1);
                            temp_r25--;
                            break;
                        }
                    }
                }
            }
        }
        for (temp_r30 = 0; temp_r30 < 20; temp_r30++) {
            if (temp_r31->unk6[temp_r30] == -1) {
                continue;
            }
            temp_r26 = lbl_1_bss_8[temp_r31->unk6[temp_r30]][0];
            Hu3DModelAttrReset(temp_r26, HU3D_ATTR_DISPOFF);
            temp_r31->unk2E[temp_r30]++;
            if (temp_r31->unk2E[temp_r30] > temp_f31) {
                Hu3DModelAttrSet(temp_r26, HU3D_ATTR_DISPOFF);
                lbl_1_bss_8[temp_r31->unk6[temp_r30]][1] = 0;
                temp_r31->unk6[temp_r30] = -1;
                GWCoinsSet(temp_r31->unk2, GWPlayer[temp_r31->unk2].coins + 1);
                temp_r27--;
            }
            else {
                temp_f30 = 0.1f;
                if (temp_r31->unk2E[temp_r30] < temp_f31 / 2.0f) {
                    temp_f30 = 0.1 * sind((90.0 / (temp_f31 / 2.0f)) * temp_r31->unk2E[temp_r30]);
                }
                if (temp_r31->unk2E[temp_r30] > temp_f31 / 2.0f) {
                    temp_f30 = 0.1 * cosd((90.0 / (temp_f31 / 2.0f)) * (temp_r31->unk2E[temp_r30] - (temp_f31 / 2.0f)));
                }
                Hu3DModelScaleSet(temp_r26, temp_f30, temp_f30, temp_f30);
                sp8.x = (sp14.x - sp20.x) * (temp_r31->unk2E[temp_r30] / temp_f31) + sp20.x;
                sp8.y = sp20.y + (temp_r31->unk58 * sind((180.0 / temp_f31) * temp_r31->unk2E[temp_r30]));
                sp8.z = 200;
                Hu3D2Dto3D(&sp8, 1, &sp8);
                Hu3DModelPosSetV(temp_r26, &sp8);
            }
        }
        if (temp_r27 <= 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(7);
    if (temp_r31->unk5C) {
        HuAudFXStop(temp_r22);
        HuAudFXStop(temp_r21);
    }
    lbl_1_bss_4--;
    HuMemDirectFree(temp_r28->user_data);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_655C(void)
{
    s16 i;
    s16 model;

    Vec pos;
    Vec target;
    Vec up;
    Hu3DShadowCreate(20, 100, 5000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowSizeSet(192);
    target.x = target.y = target.z = 0;
    pos.x = -800;
    pos.z = 1600;
    pos.y = 3200;
    up.x = 0;
    up.y = 1;
    up.z = 0;
    Hu3DShadowPosSet(&pos, &up, &target);
    Hu3DReflectMapSet(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M444, 0x23), MEMORY_DEFAULT_NUM, HEAP_DATA));
    for (i = 0; i < 4; i++) {
        lbl_1_data_470[i + 47].datanum = lbl_1_data_470[i + 51].datanum = lbl_1_data_194[GWPlayerCfg[i].character];
    }
    fn_1_D588(lbl_1_data_470);
    fn_1_D818(lbl_1_data_118);
    Hu3DModelHookSet(lbl_1_bss_199C2[9], "itemhook1", lbl_1_bss_199C2[3]);
    Hu3DModelHookSet(lbl_1_bss_199C2[9], "itemhook2", lbl_1_bss_199C2[5]);
    Hu3DModelHookSet(lbl_1_bss_199C2[9], "itemhook3", lbl_1_bss_199C2[7]);
    Hu3DModelHookSet(lbl_1_bss_199C2[3], "d1_itemhook1", lbl_1_bss_199C2[47]);
    Hu3DModelHookSet(lbl_1_bss_199C2[3], "d1_itemhook2", lbl_1_bss_199C2[48]);
    Hu3DModelHookSet(lbl_1_bss_199C2[3], "d1_itemhook3", lbl_1_bss_199C2[49]);
    Hu3DModelHookSet(lbl_1_bss_199C2[3], "d1_itemhook4", lbl_1_bss_199C2[50]);
    Hu3DModelHookSet(lbl_1_bss_199C2[11], "L_itemhook", lbl_1_bss_199C2[13]);
    Hu3DModelHookSet(lbl_1_bss_199C2[11], "R_itemhook", lbl_1_bss_199C2[14]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[13], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_199C2[14], HU3D_MOTATTR_LOOP);
    for (i = 0; i < 4; i++) {
        Hu3DModelAttrSet(lbl_1_bss_199C2[i + 51], HU3D_ATTR_DISPOFF);
    }
    fn_1_D1E0(lbl_1_bss_199C2[4]);
    model = CharModelCreate(lbl_1_bss_2DA, 2);
    lbl_1_bss_2D0 = model;
    lbl_1_bss_2C0[0] = CharModelMotionCreate(lbl_1_bss_2DA, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
    lbl_1_bss_2C0[1] = CharModelMotionCreate(lbl_1_bss_2DA, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02));
    lbl_1_bss_2C0[2] = CharModelMotionCreate(lbl_1_bss_2DA, lbl_1_bss_2DA + DATA_MAKE_NUM(DATADIR_M444, 0x45));
    lbl_1_bss_2C0[3] = CharModelMotionCreate(lbl_1_bss_2DA, lbl_1_bss_2DA + DATA_MAKE_NUM(DATADIR_M444, 0x4D));
    CharModelMotionSet(lbl_1_bss_2DA, lbl_1_bss_2C0[0]);
    Hu3DModelPosSet(model, 0, 0, 200);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(model);
    HuPrcChildCreate(fn_1_C214, 50, 12288, 0, lbl_1_bss_308);
    HuPrcChildCreate(fn_1_A060, 50, 12288, 0, lbl_1_bss_308);
    Hu3DModelAttrSet(lbl_1_bss_199C2[18], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(lbl_1_bss_199C2[18]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[26], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(lbl_1_bss_199C2[26]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[30], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(lbl_1_bss_199C2[30]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[22], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(lbl_1_bss_199C2[22]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[34], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(lbl_1_bss_199C2[34]);
    Hu3DModelShadowMapSet(lbl_1_bss_199C2[15]);
    Hu3DModelShadowMapSet(lbl_1_bss_199C2[9]);
    Hu3DModelShadowMapSet(lbl_1_bss_199C2[11]);
    Hu3DModelShadowMapSet(lbl_1_bss_199C2[3]);
    Hu3DModelShadowMapSet(lbl_1_bss_199C2[5]);
    Hu3DModelShadowMapSet(lbl_1_bss_199C2[7]);
    CharModelLayerSetAll(1);
    CharModelEffectNpcInit(lbl_1_bss_199C2[18], lbl_1_bss_1990E[20], 0, 9);
    CharModelEffectNpcInit(lbl_1_bss_199C2[26], lbl_1_bss_1990E[28], 0, 10);
    CharModelEffectNpcInit(lbl_1_bss_199C2[22], lbl_1_bss_1990E[24], 0, 14);
    CharModelEffectNpcInit(lbl_1_bss_199C2[34], lbl_1_bss_1990E[36], 0, 12);
    fn_1_8424();
    for (i = 0; i < 20; i++) {
        if (i == 0) {
            model = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M444, 0x13));
        }
        else {
            model = Hu3DModelLink(lbl_1_bss_148[0][0]);
        }
        lbl_1_bss_148[i][0] = model;
        lbl_1_bss_148[i][1] = 0;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelScaleSet(model, 0.2, 0.2, 0.2);
        Hu3DModelLayerSet(model, 7);
    }
    for (i = 0; i < 20; i++) {
        if (i == 0) {
            model = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M444, 0x12));
        }
        else {
            model = Hu3DModelLink(lbl_1_bss_8[0][0]);
        }
        lbl_1_bss_8[i][0] = model;
        lbl_1_bss_8[i][1] = 0;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelScaleSet(model, 0.2, 0.2, 0.2);
        Hu3DModelLayerSet(model, 7);
    }
    fn_1_D9C8();
}

void fn_1_6D80(s16 window)
{
    s16 i;
    WindowData *winPtr = &winData[window];
    winPtr->active_pad = 1 << lbl_1_bss_2D8;
    if (GWPlayerCfg[lbl_1_bss_2DC].iscom) {
        for (i = 0; i < 10; i++) {
            HuWinComKeyWait(256, 256, 256, 256, GWMessDelayGet());
        }
    }
}

void fn_1_6E3C(void)
{
    while (1) {
        if (lbl_1_bss_2FC || omSysExitReq) {
            break;
        }
        HuPrcVSleep();
    }
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudFadeOut(1000);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    BoardStatusKill();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

u16 lbl_1_data_240[] = { 1, 2 };

void fn_1_6EDC(omObjData *object)
{
    s16 i;
    for (i = 0; i < 1; i++) {
        Vec pos, target, up;
        float x, y, z;

        x = lbl_1_bss_2A8[i].x;
        y = lbl_1_bss_2A8[i].y;
        z = lbl_1_bss_2A8[i].z;

        pos.x = (((sind(y) * cosd(x)) * lbl_1_bss_288[i]) + lbl_1_bss_290[i].x);
        pos.y = (-sind(x) * lbl_1_bss_288[i]) + lbl_1_bss_290[i].y;
        pos.z = ((cosd(y) * cosd(x)) * lbl_1_bss_288[i]) + lbl_1_bss_290[i].z;
        target.x = lbl_1_bss_290[i].x;
        target.y = lbl_1_bss_290[i].y;
        target.z = lbl_1_bss_290[i].z;
        up.x = sind(y) * sind(x);
        up.y = cosd(x);
        up.z = cosd(y) * sind(x);
        Hu3DCameraPosSet(lbl_1_data_240[i], pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
    }
}

void fn_1_7EBC(void);
void fn_1_7290(omObjData *object)
{
    Vec pos;
    Vec offset;
    Vec dir;
    Vec y_offset;

    f32 z_rot;
    s8 stick_pos;
    if (lbl_1_bss_0 == 0) {
        fn_1_7EBC();
        return;
    }
    lbl_1_bss_2A8[0].y += 0.1f * HuPadStkX[0];
    lbl_1_bss_2A8[0].x += 0.1f * HuPadStkY[0];
    lbl_1_bss_288[0] += HuPadTrigL[0] / 2;
    lbl_1_bss_288[0] -= HuPadTrigR[0] / 2;
    if (HuPadBtnDown[0] & PAD_BUTTON_B) {
        OSReport("%f,%f,%f\n", lbl_1_bss_2A8[0].x, lbl_1_bss_2A8[0].y, lbl_1_bss_2A8[0].z);
        OSReport("%f,%f,%f\n", lbl_1_bss_290[0].x, lbl_1_bss_290[0].y, lbl_1_bss_290[0].z);
        OSReport("%f\n", lbl_1_bss_288[0]);
    }
    if (lbl_1_bss_288[0] < 100.0f) {
        lbl_1_bss_288[0] = 100.0f;
    }
    pos.x = lbl_1_bss_290[0].x + (lbl_1_bss_288[0] * (sind(lbl_1_bss_2A8[0].y) * cosd(lbl_1_bss_2A8[0].x)));
    pos.y = (lbl_1_bss_290[0].y + (lbl_1_bss_288[0] * -sind(lbl_1_bss_2A8[0].x)));
    pos.z = (lbl_1_bss_290[0].z + (lbl_1_bss_288[0] * (cosd(lbl_1_bss_2A8[0].y) * cosd(lbl_1_bss_2A8[0].x))));
    offset.x = lbl_1_bss_290[0].x - pos.x;
    offset.y = lbl_1_bss_290[0].y - pos.y;
    offset.z = lbl_1_bss_290[0].z - pos.z;
    dir.x = (sind(lbl_1_bss_2A8[0].y) * sind(lbl_1_bss_2A8[0].x));
    dir.y = cosd(lbl_1_bss_2A8[0].x);
    dir.z = (cosd(lbl_1_bss_2A8[0].y) * sind(lbl_1_bss_2A8[0].x));
    z_rot = lbl_1_bss_2A8[0].z;
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
        lbl_1_bss_290[0].x += 0.05f * (offset.x * stick_pos);
        lbl_1_bss_290[0].y += 0.05f * (offset.y * stick_pos);
        lbl_1_bss_290[0].z += 0.05f * (offset.z * stick_pos);
    }
    VECNormalize(&y_offset, &offset);
    stick_pos = -(HuPadSubStkY[0] & 0xF8);
    if (stick_pos != 0) {
        lbl_1_bss_290[0].x += 0.05f * (offset.x * stick_pos);
        lbl_1_bss_290[0].y += 0.05f * (offset.y * stick_pos);
        lbl_1_bss_290[0].z += 0.05f * (offset.z * stick_pos);
    }
}

void fn_1_7EBC(void)
{
    Vec dist;
    float dist_zoom;
    if (lbl_1_bss_2FC != 0) {
        return;
    }
    VECSubtract(&lbl_1_bss_2F0, &lbl_1_bss_2A8[0], &dist);
    if (VECMag(&dist) > 0.2) {
        VECScale(&dist, &dist, 0.05f);
        VECAdd(&lbl_1_bss_2A8[0], &dist, &lbl_1_bss_2A8[0]);
    }
    else {
        lbl_1_bss_2A8[0] = lbl_1_bss_2F0;
    }
    VECSubtract(&lbl_1_bss_2E4, &lbl_1_bss_290[0], &dist);
    if (VECMag(&dist) > 0.2) {
        VECScale(&dist, &dist, 0.05f);
        VECAdd(&lbl_1_bss_290[0], &dist, &lbl_1_bss_290[0]);
    }
    else {
        lbl_1_bss_290[0] = lbl_1_bss_2E4;
    }
    dist_zoom = lbl_1_bss_2E0 - lbl_1_bss_288[0];
    if (sqrtf(dist_zoom * dist_zoom) > 0.2) {
        dist_zoom *= 0.05f;
        lbl_1_bss_288[0] += dist_zoom;
    }
    else {
        lbl_1_bss_288[0] = lbl_1_bss_2E0;
    }
}

void fn_1_8180(s16 view)
{
    lbl_1_bss_2F0 = lbl_1_data_0[view].rot;
    lbl_1_bss_2E4 = lbl_1_data_0[view].pos;
    lbl_1_bss_2E0 = lbl_1_data_0[view].zoom;
}

void fn_1_8210(s16 view)
{
    lbl_1_bss_2A8[0] = lbl_1_data_0[view].rot;
    lbl_1_bss_2F0 = lbl_1_bss_2A8[0];
    lbl_1_bss_290[0] = lbl_1_data_0[view].pos;
    lbl_1_bss_2E4 = lbl_1_bss_290[0];
    lbl_1_bss_2E0 = lbl_1_bss_288[0] = lbl_1_data_0[view].zoom;
}

float fn_1_82FC(void)
{
    float zoom = lbl_1_bss_2E0 - lbl_1_bss_288[0];
    return sqrtf(zoom * zoom);
}
