#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/objsub.h"

#include "game/hsfmotion.h"

#include "game/pad.h"

#include "game/audio.h"
#include "game/chrman.h"
#include "game/window.h"

#include "game/gamework_data.h"

#include "REL/m444dll.h"
#include "ext_math.h"
#include "version.h"

#ifndef __MWERKS__
#include "game/frand.h"
#endif

s16 lbl_1_bss_198F0[5][2];
Vec lbl_1_bss_D8F0[4096];
Vec lbl_1_bss_18F0[4096];
Vec lbl_1_bss_18B4[5];
s32 lbl_1_bss_18A0[5];
Vec lbl_1_bss_1894;
Vec lbl_1_bss_1888;
u16 lbl_1_bss_1884;
u8 lbl_1_bss_884[4096];
Vec lbl_1_bss_860[3];
Vec lbl_1_bss_824[5];
Mtx lbl_1_bss_794[3];
float lbl_1_bss_788[3];
Vec lbl_1_bss_77C;
Vec lbl_1_bss_770;
float lbl_1_bss_370[256];
Vec lbl_1_bss_34C[3];
Vec lbl_1_bss_328[3];
s16 lbl_1_bss_320[4];
Vec lbl_1_bss_314;
s16 lbl_1_bss_312;
u8 lbl_1_bss_310;

float lbl_1_data_258[3] = { 90, 250, 420 };

Vec lbl_1_data_264[5] = { { -75, -300, 0 }, { 25, -300, 0 }, { -75, -300, 0 }, { 25, -300, 0 }, { -25, -400, 0 } };

float lbl_1_data_2A0[5 * 2] = { -100, -60, 10, 50, -100, -60, 10, 50, -50, 0 };

s16 lbl_1_data_2C8[5] = {
    1,
    1,
    2,
    2,
    2,
};

void fn_1_8424(void)
{
    s16 i;
    for (i = 0; i < 5; i++) {
        lbl_1_bss_18B4[i] = lbl_1_data_264[i];
        lbl_1_bss_824[i].x = lbl_1_bss_18B4[i].x;
        lbl_1_bss_824[i].y = 215;
        lbl_1_bss_824[i].z = lbl_1_bss_18B4[i].y;
        lbl_1_bss_198F0[i][0] = 10;
        lbl_1_bss_198F0[i][1] = 0;
    }
    for (i = 0; i < 3; i++) {
        lbl_1_bss_860[i].x = 128;
        lbl_1_bss_860[i].y = 230;
        lbl_1_bss_860[i].z = -100;
        MTXIdentity(lbl_1_bss_794[i]);
        lbl_1_bss_788[i] = 0;
    }
}

void fn_1_861C(s16 arg0)
{
    s16 temp_r31;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    lbl_1_bss_312 = 0;
    for (temp_r31 = 0; temp_r31 < 256; temp_r31++) {
        lbl_1_bss_370[temp_r31] = 1000000.0f;
    }
    lbl_1_bss_1894.x = 128;
    lbl_1_bss_1894.y = -100;
    lbl_1_bss_1894.z = 0;
    lbl_1_bss_1888.x = lbl_1_bss_1888.z = 0;
    lbl_1_bss_1888.y = -30;
    lbl_1_bss_860[arg0].x = lbl_1_bss_1894.x;
    lbl_1_bss_860[arg0].y = 230;
    lbl_1_bss_860[arg0].z = lbl_1_bss_1894.y;
    fn_1_D1E0(lbl_1_bss_199C2[(arg0 * 2) + 4]);
    if (arg0 == 0) {
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            lbl_1_bss_320[temp_r31] = temp_r31;
        }
        for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
            temp_r29 = frandmod(4);
            temp_r28 = frandmod(4);
            temp_r27 = lbl_1_bss_320[temp_r29];
            lbl_1_bss_320[temp_r29] = lbl_1_bss_320[temp_r28];
            lbl_1_bss_320[temp_r28] = temp_r27;
        }
        Hu3DModelHookSet(lbl_1_bss_199C2[3], "d1_itemhook1", lbl_1_bss_199C2[lbl_1_bss_320[0] + 47]);
        Hu3DModelHookSet(lbl_1_bss_199C2[3], "d1_itemhook2", lbl_1_bss_199C2[lbl_1_bss_320[1] + 47]);
        Hu3DModelHookSet(lbl_1_bss_199C2[3], "d1_itemhook3", lbl_1_bss_199C2[lbl_1_bss_320[2] + 47]);
        Hu3DModelHookSet(lbl_1_bss_199C2[3], "d1_itemhook4", lbl_1_bss_199C2[lbl_1_bss_320[3] + 47]);
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            Hu3DModelAttrSet(lbl_1_bss_199C2[temp_r31 + 51], HU3D_ATTR_DISPOFF);
        }
    }
    else if (arg0 == 1) {
        for (temp_r31 = temp_r29 = 0; temp_r31 < 4; temp_r31++) {
            if (temp_r31 != lbl_1_bss_2D6) {
                lbl_1_bss_320[temp_r29] = temp_r31;
                temp_r29++;
            }
        }
        for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
            temp_r29 = frandmod(3);
            temp_r28 = frandmod(3);
            temp_r27 = lbl_1_bss_320[temp_r29];
            lbl_1_bss_320[temp_r29] = lbl_1_bss_320[temp_r28];
            lbl_1_bss_320[temp_r28] = temp_r27;
        }
        Hu3DModelAttrReset(lbl_1_bss_199C2[lbl_1_bss_320[0] + 51], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_199C2[lbl_1_bss_320[1] + 51], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_199C2[lbl_1_bss_320[2] + 51], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_199C2[lbl_1_bss_2D6 + 51], HU3D_ATTR_DISPOFF);
        Hu3DModelHookSet(lbl_1_bss_199C2[5], "d2_itemhook1", lbl_1_bss_199C2[lbl_1_bss_320[0] + 51]);
        Hu3DModelHookSet(lbl_1_bss_199C2[5], "d2_itemhook2", lbl_1_bss_199C2[lbl_1_bss_320[1] + 51]);
        Hu3DModelHookSet(lbl_1_bss_199C2[5], "d2_itemhook3", lbl_1_bss_199C2[lbl_1_bss_320[2] + 51]);
    }
    Hu3DModelAttrSet(lbl_1_bss_199C2[arg0 + 65], HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(lbl_1_bss_199C2[arg0 + 65], 0);
    Hu3DModelAttrSet(lbl_1_bss_199C2[arg0 + 55], HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(lbl_1_bss_199C2[arg0 + 55], 0);
    Hu3DMotionSpeedSet(lbl_1_bss_199C2[arg0 + 55], 2);
    Hu3DMotionSet(lbl_1_bss_199C2[arg0 + 58], lbl_1_bss_1990E[61]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[arg0 + 58], HU3D_MOTATTR_LOOP);
    for (temp_r31 = 0; temp_r31 < 5; temp_r31++) {
        if (arg0 == lbl_1_data_2C8[temp_r31]) {
            lbl_1_bss_18A0[temp_r31] = 1;
        }
        else {
            lbl_1_bss_18A0[temp_r31] = 0;
        }
        lbl_1_bss_198F0[temp_r31][0] = 10;
        lbl_1_bss_198F0[temp_r31][1] = 0;
    }
}

void fn_1_ABD0(s16 arg0, s16 arg1);
s16 fn_1_B1E8(Vec *arg0, Vec *arg1, s16 arg2);

s16 fn_1_8DD0(s16 arg0)
{
    s16 temp_r30;
    s16 temp_r29;
    s32 temp_r28;
    s16 temp_r27;
    Mtx sp24;
    Vec sp18;
    Vec spC;
    float sp8 = 0;
    Hu3DMotionTimeSet(lbl_1_bss_199C2[9], lbl_1_data_258[arg0]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[9], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_199C2[arg0 + 65], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(lbl_1_bss_199C2[arg0 + 65], 0.1 * (-lbl_1_bss_1888.y - 14.0f) + 1.0);
    temp_r28 = 0;
    spC.z = spC.y = spC.x = 0;
    fn_1_8180(1);
    while (1) {
        temp_r27 = fn_1_B1E8(&lbl_1_bss_1894, &lbl_1_bss_1888, arg0);
        lbl_1_bss_860[arg0].x = lbl_1_bss_1894.x;
        lbl_1_bss_860[arg0].y = 230;
        lbl_1_bss_860[arg0].z = lbl_1_bss_1894.y;
        if (VECMag(&lbl_1_bss_1888)) {
            sp18.x = 0;
            sp18.y = 0;
            sp18.z = 1;
            VECCrossProduct(&sp18, &lbl_1_bss_1888, &sp18);
            sp18.z = sp18.y;
            sp18.y = 0;
            MTXRotAxisDeg(sp24, &sp18, 360.0 * (VECMag(&lbl_1_bss_1888) / 81.68140899333463));
            MTXConcat(lbl_1_bss_794[arg0], sp24, lbl_1_bss_794[arg0]);
        }
        lbl_1_bss_2E4.z = lbl_1_bss_860[arg0].z;
        for (temp_r30 = temp_r29 = 0; temp_r30 < 5; temp_r30++) {
            if (arg0 == lbl_1_data_2C8[temp_r30]) {
                fn_1_ABD0(temp_r30, arg0);
                if (lbl_1_bss_198F0[temp_r30][1] & 0x2) {
                    temp_r29++;
                }
            }
        }
        if (temp_r29) {
            if (Hu3DMotionIDGet(lbl_1_bss_199C2[arg0 + 58]) != lbl_1_bss_1990E[62]) {
                Hu3DMotionSet(lbl_1_bss_199C2[arg0 + 58], lbl_1_bss_1990E[62]);
            }
        }
        else {
            if (Hu3DMotionIDGet(lbl_1_bss_199C2[arg0 + 58]) != lbl_1_bss_1990E[61]) {
                Hu3DMotionSet(lbl_1_bss_199C2[arg0 + 58], lbl_1_bss_1990E[61]);
            }
        }
        if (temp_r27 != -1) {
            break;
        }
        if (lbl_1_bss_1894.x < 85.0f && temp_r28 == 0) {
            lbl_1_bss_D8F0[lbl_1_bss_1884].x = 100;
            lbl_1_bss_D8F0[lbl_1_bss_1884].y = 100;
            lbl_1_bss_D8F0[lbl_1_bss_1884].z = 0;
            lbl_1_bss_18F0[lbl_1_bss_1884].x = 100;
            lbl_1_bss_18F0[lbl_1_bss_1884].y = -500;
            lbl_1_bss_18F0[lbl_1_bss_1884].z = 0;
            lbl_1_bss_1884++;
            Hu3DModelAttrReset(lbl_1_bss_199C2[arg0 + 55], HU3D_MOTATTR_PAUSE);
            Hu3DMotionTimeSet(lbl_1_bss_199C2[arg0 + 55], 0);
            temp_r28 = 1;
        }
        HuPrcVSleep();
    }
    for (temp_r30 = 0; temp_r30 < 5; temp_r30++) {
        if (arg0 == lbl_1_data_2C8[temp_r30]) {
            lbl_1_bss_198F0[temp_r30][1] = 4;
            fn_1_ABD0(temp_r30, arg0);
        }
    }
    HuAudFXPlay(1851);
    return temp_r27;
}

void fn_1_9418(s16 arg0)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;

    s16 temp_r31;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    s16 temp_r24;
    s16 temp_r23;
    float sp8[2];
    temp_f31 = 0;
    fn_1_8180(0);
    Hu3DModelPosSet(lbl_1_bss_2D0, 124, 0, 70);
    Hu3DModelRotSet(lbl_1_bss_2D0, 0, 180, 0);
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[3], 0, 4, HU3D_MOTATTR_SHIFT_REV);
    HuPrcSleep(12);
    HuWinMesMaxSizeGet(1, sp8, MAKE_MESSID(0x1C, 0x0F));
    temp_r29 = HuWinCreate(-10000, 340, sp8[0], sp8[1], 1);
    HuWinMesSpeedSet(temp_r29, 0);
    HuWinBGTPLvlSet(temp_r29, 0);
    HuWinMesSet(temp_r29, MAKE_MESSID(0x1C, 0x0F));
    CharModelMotionSet(lbl_1_bss_2DA, lbl_1_bss_2C0[2]);
    Hu3DModelAttrSet(lbl_1_bss_2D0, HU3D_MOTATTR_PAUSE);
    temp_f29 = Hu3DMotionTimeGet(lbl_1_bss_2D0);
    temp_f28 = Hu3DMotionMaxTimeGet(lbl_1_bss_2D0);
    if (GWPlayerCfg[lbl_1_bss_2DC].iscom) {
        temp_r27 = frandmod(100) + 20;
    }
    while (1) {
        temp_r26 = HuPadBtnDown[lbl_1_bss_2D8];
        temp_r23 = HuPadBtn[lbl_1_bss_2D8];
        temp_r25 = HuPadStkY[lbl_1_bss_2D8];
        if (GWPlayerCfg[lbl_1_bss_2DC].iscom) {
            temp_r23 = 0;
            if (temp_r27 != 0) {
                temp_r27--;
                temp_r25 = -72;
            }
            else {
                temp_r26 = PAD_BUTTON_A;
            }
        }
        if ((temp_r26 & PAD_BUTTON_A) && lbl_1_bss_788[arg0] > 0) {
            break;
        }
        if (HuPadTrigR[lbl_1_bss_2D8] > 10) {
            if (temp_f31 < 90.0f) {
                temp_f31 += 5.0f;
            }
            fn_1_8180(arg0 + 2);
        }
        else {
            fn_1_8180(0);
            if (temp_f31 > 0.0f) {
                temp_f31 -= 5.0f;
            }
        }
        for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
            lbl_1_bss_34C[temp_r31].y = 80.0 - (150.0 * sind(temp_f31));
        }
        temp_f30 = -(temp_r25 >> 3);
        temp_f30 /= 20.0f;
        if (temp_f30) {
            if (temp_f30 + lbl_1_bss_788[arg0] < 0.0f) {
                temp_f30 = -lbl_1_bss_788[arg0];
            }
            else {
                if (temp_f30 + lbl_1_bss_788[arg0] > 50.0f) {
                    temp_f30 = 50.0f - lbl_1_bss_788[arg0];
                }
            }
            temp_f29 += temp_f30;
            if (temp_f29 >= temp_f28) {
                temp_f29 -= temp_f28;
            }
        }
        else {
            temp_f30 = -0.3f;
            if (temp_f30 + lbl_1_bss_788[arg0] < 0.0f) {
                temp_f30 = -lbl_1_bss_788[arg0];
            }
        }
        Hu3DMotionTimeSet(lbl_1_bss_2D0, temp_f29);
        lbl_1_bss_788[arg0] += temp_f30;
        Hu3DModelPosSet(lbl_1_bss_2D0, 124, 0, 70 + lbl_1_bss_788[arg0]);
        for (temp_r31 = 0; temp_r31 < 5; temp_r31++) {
            if (arg0 == lbl_1_data_2C8[temp_r31]) {
                fn_1_ABD0(temp_r31, arg0);
            }
        }
        HuPrcVSleep();
    }
    if (temp_f31 > 0) {
        fn_1_8180(0);
        for (temp_r28 = 0; temp_r28 < 10; temp_r28++) {
            temp_f31 -= 10.0f;
            if (temp_f31 < 0.0f) {
                temp_f31 = 0.0f;
            }
            for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
                lbl_1_bss_34C[temp_r31].y = 80.0 - (150.0 * sind(temp_f31));
            }
            if (temp_f31 == 0.0f) {
                break;
            }
            HuPrcVSleep();
        }
    }
    CharModelMotionShiftSet(lbl_1_bss_2DA, lbl_1_bss_2C0[3], 0, 8, HU3D_MOTATTR_NONE);
    HuPrcSleep(4);
    temp_r24 = lbl_1_bss_788[arg0] / 4;
    lbl_1_bss_1888.y = (-15 - temp_r24) + (0.1 * (float)frandmod(10));
    lbl_1_bss_788[arg0] = 0;
    HuWinExCleanup(temp_r29);
    HuAudFXPlay(1852);
}

void fn_1_9CAC(s16 arg0, s16 arg1)
{
    Mtx sp38;
    Mtx sp8;
    ModelData *temp_r29;

    Hu3DMotionSet(lbl_1_bss_199C2[arg0 + 58], lbl_1_bss_1990E[63]);
    Hu3DModelAttrSet(lbl_1_bss_199C2[arg0 + 58], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(lbl_1_bss_199C2[64], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_199C2[64], HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(lbl_1_bss_199C2[64], 0);
    MTXTrans(sp8, 0, -150, 0);
    if (arg0 == 0) {
        switch (arg1) {
            case 0:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[3], "d1_itemhook1", sp38);
                break;

            case 1:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[3], "d1_itemhook2", sp38);
                break;

            case 2:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[3], "d1_itemhook3", sp38);
                break;

            case 3:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[3], "d1_itemhook4", sp38);
                break;
        }
    }
    else if (arg0 == 1) {
        switch (arg1) {
            case 0:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[5], "d2_itemhook1", sp38);
                break;

            case 1:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[5], "d2_itemhook2", sp38);
                break;

            case 2:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[5], "d2_itemhook3", sp38);
                break;
        }
    }
    else {
        switch (arg1) {
            case 0:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[7], "d3_itemhook1", sp38);
                break;

            case 1:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[7], "d3_itemhook4", sp38);
                break;

            case 2:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[7], "d3_itemhook2", sp38);
                break;

            case 3:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[7], "d3_itemhook7", sp38);
                break;

            case 4:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[7], "d3_itemhook6", sp38);
                break;

            case 5:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[7], "d3_itemhook3", sp38);
                break;

            case 6:
                Hu3DModelObjMtxGet(lbl_1_bss_199C2[7], "d3_itemhook5", sp38);
                break;
        }
        mtxScaleCat(sp8, 0.8, 1, 0.8);
    }
    temp_r29 = &Hu3DData[lbl_1_bss_199C2[64]];
    MTXConcat(sp38, sp8, sp38);
    MTXCopy(sp38, temp_r29->unk_F0);
}

void fn_1_A060(void)
{
    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    Vec sp20;
    Vec sp14;
    float sp8[3] = { 0, 40, 60 };
    for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
        lbl_1_bss_34C[temp_r30].y = -100;
        lbl_1_bss_34C[temp_r30].z = 200;
        lbl_1_bss_328[temp_r30].x = lbl_1_bss_328[temp_r30].y = lbl_1_bss_328[temp_r30].z = 0.3f;
        Hu3DModelAttrReset(lbl_1_bss_199C2[temp_r30 + 71], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_199C2[temp_r30 + 71], HU3D_MOTATTR_LOOP);
    }
    lbl_1_bss_34C[0].x = 188;
    lbl_1_bss_34C[1].x = 388;
    lbl_1_bss_34C[2].x = 288;
    temp_r29 = temp_r27 = 0;
    while (1) {
        for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
            sp14 = lbl_1_bss_34C[temp_r30];
            sp14.y += 5.0 * sind(sp8[temp_r30]);
            Hu3D2Dto3D(&sp14, 1, &sp20);
            Hu3DModelPosSet(lbl_1_bss_199C2[temp_r30 + 71], sp20.x, sp20.y, sp20.z);
            Hu3DModelRotSet(lbl_1_bss_199C2[temp_r30 + 71], lbl_1_bss_2A8[0].x, lbl_1_bss_2A8[0].y, lbl_1_bss_2A8[0].z);
            Hu3DModelScaleSet(
                lbl_1_bss_199C2[temp_r30 + 71], lbl_1_bss_328[temp_r30].x / 2.0, lbl_1_bss_328[temp_r30].y / 2.0, lbl_1_bss_328[temp_r30].z / 2.0);
            switch (temp_r30) {
                case 0:
                    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                        Hu3DModelScaleSet(lbl_1_bss_199C2[temp_r31 + 74], lbl_1_bss_328[temp_r30].x * 1.2, lbl_1_bss_328[temp_r30].y * 1.2,
                            lbl_1_bss_328[temp_r30].z * 1.2);
                    }
                    if (lbl_1_bss_2D6 != -2) {
                        if (lbl_1_bss_2D6 == -1) {
                            if ((temp_r27 & 0x7) == 0 && (++temp_r29) >= 4) {
                                temp_r29 = 0;
                            }
                            temp_r27++;
                            temp_r28 = lbl_1_bss_199C2[temp_r29 + 74];
                            for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                                Hu3DModelAttrSet(lbl_1_bss_199C2[temp_r31 + 74], HU3D_ATTR_DISPOFF);
                            }
                            Hu3DModelAttrReset(temp_r28, HU3D_ATTR_DISPOFF);
                        }
                        else {
                            temp_r28 = lbl_1_bss_199C2[lbl_1_bss_2D6 + 74];
                            for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                                Hu3DModelAttrSet(lbl_1_bss_199C2[temp_r31 + 74], HU3D_ATTR_DISPOFF);
                            }
                            Hu3DModelAttrReset(temp_r28, HU3D_ATTR_DISPOFF);
                        }
                        Hu3DModelPosSet(temp_r28, sp20.x, sp20.y, sp20.z);
                        Hu3DModelRotSet(temp_r28, 90.0f + lbl_1_bss_2A8[0].x, lbl_1_bss_2A8[0].y, lbl_1_bss_2A8[0].z);
                    }
                    break;

                case 1:
                    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                        if (temp_r31 == lbl_1_bss_2D6) {
                            continue;
                        }
                        Hu3DModelScaleSet(lbl_1_bss_199C2[temp_r31 + 74], lbl_1_bss_328[temp_r30].x * 1.2, lbl_1_bss_328[temp_r30].y * 1.2,
                            lbl_1_bss_328[temp_r30].z * 1.2);
                    }
                    if (lbl_1_bss_2D4 != -2) {
                        if (lbl_1_bss_2D4 == -1) {
                            if ((temp_r27 & 0x7) == 0) {
                                temp_r29++;
                                if (temp_r29 == lbl_1_bss_2D6) {
                                    temp_r29++;
                                }
                                if (temp_r29 >= 4) {
                                    temp_r29 = 0;
                                    if (lbl_1_bss_2D6 == 0) {
                                        temp_r29++;
                                    }
                                }
                            }
                            else {
                                if (temp_r29 == lbl_1_bss_2D6) {
                                    temp_r29++;
                                    if (temp_r29 >= 4) {
                                        temp_r29 = 0;
                                    }
                                }
                            }
                            temp_r27++;
                            temp_r28 = lbl_1_bss_199C2[temp_r29 + 74];
                            for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                                if (temp_r31 != lbl_1_bss_2D6) {
                                    Hu3DModelAttrSet(lbl_1_bss_199C2[temp_r31 + 74], HU3D_ATTR_DISPOFF);
                                }
                            }
                            Hu3DModelAttrReset(temp_r28, HU3D_ATTR_DISPOFF);
                        }
                        else {
                            temp_r28 = lbl_1_bss_199C2[lbl_1_bss_2D4 + 74];
                            for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                                if (temp_r31 != lbl_1_bss_2D6) {
                                    Hu3DModelAttrSet(lbl_1_bss_199C2[temp_r31 + 74], HU3D_ATTR_DISPOFF);
                                }
                            }
                            Hu3DModelAttrReset(temp_r28, HU3D_ATTR_DISPOFF);
                        }
                        Hu3DModelPosSet(temp_r28, sp20.x, sp20.y, sp20.z);
                        Hu3DModelRotSet(temp_r28, 90.0f + lbl_1_bss_2A8[0].x, lbl_1_bss_2A8[0].y, lbl_1_bss_2A8[0].z);
                    }
                    break;

                case 2:
                    for (temp_r31 = 0; temp_r31 < 7; temp_r31++) {
                        Hu3DModelScaleSet(lbl_1_bss_199C2[temp_r31 + 78], lbl_1_bss_328[temp_r30].x * 1.2, lbl_1_bss_328[temp_r30].y * 1.2,
                            lbl_1_bss_328[temp_r30].z * 1.2);
                    }
                    if (lbl_1_bss_2D2 != -2) {
                        if (lbl_1_bss_2D2 == -1) {
                            if ((temp_r27 & 0x7) == 0 && (++temp_r29) >= 7) {
                                temp_r29 = 0;
                            }
                            temp_r27++;
                            temp_r28 = lbl_1_bss_199C2[temp_r29 + 78];
                            for (temp_r31 = 0; temp_r31 < 7; temp_r31++) {
                                Hu3DModelAttrSet(lbl_1_bss_199C2[temp_r31 + 78], HU3D_ATTR_DISPOFF);
                            }
                            Hu3DModelAttrReset(temp_r28, HU3D_ATTR_DISPOFF);
                        }
                        else {
                            temp_r28 = lbl_1_bss_199C2[lbl_1_bss_2D2 + 78];
                            for (temp_r31 = 0; temp_r31 < 7; temp_r31++) {
                                Hu3DModelAttrSet(lbl_1_bss_199C2[temp_r31 + 78], HU3D_ATTR_DISPOFF);
                            }
                            Hu3DModelAttrReset(temp_r28, HU3D_ATTR_DISPOFF);
                        }
                        Hu3DModelPosSet(temp_r28, sp20.x, sp20.y, sp20.z);
                        Hu3DModelRotSet(temp_r28, 90.0f + lbl_1_bss_2A8[0].x, lbl_1_bss_2A8[0].y, lbl_1_bss_2A8[0].z);
                    }
                    break;
            }
            sp8[temp_r30] += 4.0 * (1.0 + (temp_r30 * 0.05));
            if (sp8[temp_r30] > 360.0f) {
                sp8[temp_r30] -= 360.0f;
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_ABD0(s16 arg0, s16 arg1)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    s16 *temp_r31;
    s16 temp_r29;
    s16 temp_r28;
    Vec sp14;
    Vec sp8;
    temp_r31 = &lbl_1_bss_198F0[arg0][0];
    temp_r29 = lbl_1_bss_199C2[arg0 + 38];
    if (temp_r31[1] & 0x2) {
        if (temp_r31[0] == 85) {
            if (Hu3DMotionIDGet(temp_r29) != lbl_1_bss_1990E[45] && Hu3DMotionShiftIDGet(temp_r29) != lbl_1_bss_1990E[45]) {
                Hu3DMotionShiftSet(temp_r29, lbl_1_bss_1990E[45], 0, 8, HU3D_MOTATTR_NONE);
            }
        }
        else {
            if (Hu3DMotionIDGet(temp_r29) != lbl_1_bss_1990E[46] && Hu3DMotionShiftIDGet(temp_r29) != lbl_1_bss_1990E[46]) {
                Hu3DMotionShiftSet(temp_r29, lbl_1_bss_1990E[46], 0, 8, HU3D_MOTATTR_LOOP);
            }
        }
        temp_r31[0]--;
        if (temp_r31[0] <= 0) {
            temp_r31[1] &= ~0x2;
            temp_r31[1] |= 0x4;
            temp_r31[0] = 20;
        }
    }
    else {
        if (temp_r31[1] & 0x4) {
            if (Hu3DMotionIDGet(temp_r29) != lbl_1_bss_1990E[43] && Hu3DMotionShiftIDGet(temp_r29) != lbl_1_bss_1990E[43]) {
                Hu3DMotionShiftSet(temp_r29, lbl_1_bss_1990E[43], 0, 16, HU3D_MOTATTR_LOOP);
            }
            temp_r31[0]--;
            if (temp_r31[0] <= 0) {
                temp_r31[1] &= ~0x4;
                temp_r31[0] = frandmod(30) + 30;
            }
        }
        else {
            temp_r31[0]--;
            if (temp_r31[0] <= 0) {
                temp_r31[1] |= 4;
                temp_r31[0] = 60;
            }
            else {
                if (Hu3DMotionIDGet(temp_r29) != lbl_1_bss_1990E[44]) {
                    Hu3DMotionSet(temp_r29, lbl_1_bss_1990E[44]);
                }
                if (temp_r31[1] & 0x1) {
                    temp_f31 = -1;
                    temp_f30 = -90;
                }
                else {
                    temp_f31 = 1;
                    temp_f30 = 90;
                }
                sp8 = lbl_1_bss_18B4[arg0];
                sp8.x += temp_f31;
                for (temp_r28 = 0; temp_r28 < 5; temp_r28++) {
                    if (temp_r28 == arg0 || lbl_1_bss_18A0[temp_r28] == 0) {
                        continue;
                    }
                    VECSubtract(&sp8, &lbl_1_bss_18B4[temp_r28], &sp14);
                    if (VECMag(&sp14) < 55.0f) {
                        break;
                    }
                }
                if (temp_r28 == 5) {
                    lbl_1_bss_18B4[arg0].x += temp_f31;
                    if (lbl_1_bss_18B4[arg0].x < lbl_1_data_2A0[(arg0 * 2)]) {
                        lbl_1_bss_18B4[arg0].x = lbl_1_data_2A0[(arg0 * 2)];
                        temp_r31[1] ^= 0x1;
                        temp_r31[1] |= 0x4;
                        temp_r31[0] = 60;
                    }
                    if (lbl_1_bss_18B4[arg0].x > lbl_1_data_2A0[(arg0 * 2) + 1]) {
                        lbl_1_bss_18B4[arg0].x = lbl_1_data_2A0[(arg0 * 2) + 1];
                        temp_r31[1] ^= 0x1;
                        temp_r31[1] |= 0x4;
                        temp_r31[0] = 60;
                    }
                }
                else {
                    temp_r31[1] ^= 0x1;
                    temp_r31[1] |= 0x4;
                    temp_r31[0] = 60;
                }
            }
        }
    }
    lbl_1_bss_824[arg0].x = lbl_1_bss_18B4[arg0].x;
    lbl_1_bss_824[arg0].y = 215;
    lbl_1_bss_824[arg0].z = lbl_1_bss_18B4[arg0].y;
}

s16 lbl_1_data_3A4[] = { 4, 3, 7 };

Vec lbl_1_data_3AC[] = { { -118.75, -70, 0 }, { -56.25, -70, 0 }, { 6.25, -70, 0 }, { 68.75, -70, 0 } };

Vec lbl_1_data_3DC[] = {
    { -108.35, -70, 0 },
    { -25.05, -70, 0 },
    { 58.25, -70, 0 },
};

Vec lbl_1_data_400[] = { { -125, -70, 0 }, { -75, -70, 0 }, { -25, -70, 0 }, { 25, -70, 0 }, { 75, -70, 0 }, { -85, -190, 0 }, { 35, -190, 0 } };

Vec *lbl_1_data_454[] = { lbl_1_data_3AC, lbl_1_data_3DC, lbl_1_data_400 };

Vec *fn_1_CA30(Vec *arg0, Vec *arg1, Vec *arg2);

float fn_1_CB70(Vec *arg0, Vec *arg1, Vec *arg2);

s16 fn_1_B1E8(Vec *arg0, Vec *arg1, s16 arg2)
{
    Vec sp4C;
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    s32 spC;

    float temp_f31;
    float temp_f30;
    float temp_f28;
    float temp_f27;

    s16 temp_r30;
    Vec *temp_r28;
    s32 temp_r27;
    Vec *temp_r25;
    u8 temp_r24;

    s16 temp_r23 = -1;
    spC = 1;
    temp_f28 = VECMag(arg1);
    sp1C = *arg1;
    temp_r27 = 0;
    sp10 = *arg0;
    temp_r24 = lbl_1_bss_310 - 120;
    for (temp_r30 = temp_f30 = 0; temp_r30 < 120; temp_r30++, temp_r24++) {
        temp_f30 += lbl_1_bss_370[temp_r24];
    }
    if (temp_f30 < 120.0f * sqrtf(6.0f)) {
        lbl_1_bss_312 = 10;
    }
    while (temp_f28 > 0.0f) {
        if (temp_f28 > 3.0f) {
            temp_f28 -= 3.0f;
            temp_f31 = 3.0f;
        }
        else {
            temp_f31 = temp_f28;
            temp_f28 = 0;
        }
        VECNormalize(&sp1C, &sp1C);
        VECScale(&sp1C, &sp1C, temp_f31);
        VECAdd(arg0, &sp1C, &sp4C);
        temp_f31 = VECMag(&sp1C);
        if (lbl_1_bss_312 == 0) {
            for (temp_r30 = 0; temp_r30 < 5; temp_r30++) {
                if (lbl_1_bss_18A0[temp_r30] == 0) {
                    continue;
                }
                VECSubtract(&sp4C, &lbl_1_bss_18B4[temp_r30], &sp34);
                temp_f30 = VECMag(&sp34);
                if (temp_f30 < 33.0) {
                    VECNormalize(&sp34, &sp34);
                    VECScale(&sp34, &sp28, 33.0f);
                    VECAdd(&lbl_1_bss_18B4[temp_r30], &sp28, &sp4C);
                    VECScale(&sp1C, &sp28, -1.0f);
                    temp_f27 = (sp28.x * sp34.x) + (sp28.y * sp34.y);
                    sp34.x = (2.0 * sp34.x * temp_f27) - sp28.x;
                    sp34.y = (2.0 * sp34.y * temp_f27) - sp28.y;
                    sp34.z = 0;
                    VECNormalize(&sp34, &sp34);
                    VECScale(&sp34, &sp1C, temp_f31);
                    VECAdd(&sp4C, &sp1C, &sp34);
                    temp_f30 = VECSquareDistance(&sp34, &lbl_1_bss_18B4[temp_r30]);
                    if (temp_f30 < 1089.0) {
                        VECScale(&sp1C, &sp1C, -1.0f);
                    }
                    lbl_1_bss_198F0[temp_r30][1] = 2;
                    lbl_1_bss_198F0[temp_r30][0] = 100;
                    temp_r27 = 1;
                }
            }
        }
        else {
            lbl_1_bss_312--;
        }
        for (temp_r30 = 0; temp_r30 < lbl_1_bss_1884; temp_r30++) {
            if (VECSquareDistance(&lbl_1_bss_D8F0[temp_r30], &sp4C) <= 169.0f) {
                VECSubtract(&sp4C, &lbl_1_bss_D8F0[temp_r30], &sp34);
                VECNormalize(&sp34, &sp34);
                VECScale(&sp34, &sp34, 13.05f);
                VECAdd(&lbl_1_bss_D8F0[temp_r30], &sp34, &sp4C);
                VECScale(arg1, arg1, 0.96f);
                temp_r27 = 1;
            }
            else {
                if (VECSquareDistance(&lbl_1_bss_18F0[temp_r30], &sp4C) <= 169.0f) {
                    VECSubtract(&sp4C, &lbl_1_bss_18F0[temp_r30], &sp34);
                    VECNormalize(&sp34, &sp34);
                    VECScale(&sp34, &sp34, 13.05f);
                    VECAdd(&lbl_1_bss_18F0[temp_r30], &sp34, &sp4C);
                    VECScale(arg1, arg1, 0.96f);
                    temp_r27 = 1;
                }
                else {
                    continue;
                }
            }
            *arg0 = sp4C;
            break;
        }
        if (temp_f31 == 0.0) {
            continue;
        }
        for (temp_r30 = 0; temp_r30 < lbl_1_bss_1884; temp_r30++) {
            VECSubtract(&lbl_1_bss_18F0[temp_r30], &lbl_1_bss_D8F0[temp_r30], &sp40);
            temp_f30 = fn_1_CB70(&sp4C, &lbl_1_bss_D8F0[temp_r30], &sp40);
            if (temp_f30 < 13.0f) {
                temp_r25 = fn_1_CA30(&sp4C, &lbl_1_bss_D8F0[temp_r30], &sp40);
                if (VECSquareDistance(&lbl_1_bss_D8F0[temp_r30], &sp4C) >= 169.0f && VECSquareDistance(&lbl_1_bss_18F0[temp_r30], &sp4C) >= 169.0f) {
                    VECSubtract(temp_r25, &lbl_1_bss_D8F0[temp_r30], &sp34);
                    if (VECMag2Point(&sp34) > VECMag2Point(&sp40)) {
                        continue;
                    }
                    VECSubtract(temp_r25, &lbl_1_bss_18F0[temp_r30], &sp34);
                    if (VECMag2Point(&sp34) > VECMag2Point(&sp40)) {
                        continue;
                    }
                }
                VECSubtract(&sp4C, temp_r25, &sp34);
                VECNormalize(&sp34, &sp34);
                VECScale(&sp34, &sp34, 13.0f);
                VECAdd(temp_r25, &sp34, &sp4C);
                VECSubtract(arg0, &sp4C, &sp34);
                *arg0 = sp4C;
                temp_f31 -= VECMag(&sp34);
                if (temp_f31 < 0.0f) {
                    temp_f28 -= temp_f31;
                    temp_f31 = ABS(temp_f31);
#if VERSION_REV1
                    if (temp_f31 == 0.0) {
                        sp1C.x = sp1C.y = sp1C.z = 0.0f;
                        break;
                    }
#endif
                }
                sp34 = sp40;
                sp34.z = 1;
                VECCrossProduct(&sp34, &sp40, &sp34);
                VECNormalize(&sp34, &sp34);
                VECScale(&sp1C, &sp28, -1.0f);
                temp_f27 = (sp28.x * sp34.x) + (sp28.y * sp34.y);
                sp34.x = (1.5 * sp34.x * temp_f27) - sp28.x;
                sp34.y = (1.5 * sp34.y * temp_f27) - sp28.y;
                sp34.z = 0;
                VECNormalize(&sp34, &sp34);
                VECScale(&sp34, &sp1C, temp_f31);
                lbl_1_bss_884[temp_r30] = 10;
                VECScale(arg1, arg1, 0.96f);
                VECNormalize(&sp1C, &sp34);
                VECNormalize(arg1, &sp28);
                if (VECDotProduct(&sp34, &sp28) < 0.5) {
                    temp_r27 = 1;
                }
            }
        }
        VECAdd(arg0, &sp1C, arg0);
        if (arg0->x >= lbl_1_bss_77C.x - 13.0f) {
            arg0->x = lbl_1_bss_77C.x - 13.0f - 1.0f;
        }
        if (arg0->y >= lbl_1_bss_77C.y - 13.0f) {
            arg0->y = lbl_1_bss_77C.y - 13.0f - 1.0f;
        }
        if (arg0->x <= lbl_1_bss_770.x + 13.0f) {
            arg0->x = lbl_1_bss_770.x + 13.0f + 1.0f;
        }
        if (arg0->y <= lbl_1_bss_770.y + 13.0f) {
            arg0->y = lbl_1_bss_770.y + 13.0f + 1.0f;
        }
    }
    temp_f31 = VECMag(arg1);
#if VERSION_REV1
    if (VECMag(&sp1C) == 0.0) {
        sp1C.x = 0.0f;
        sp1C.y = 1.0f;
        sp1C.z = 0.0f;
    }
#endif
    VECNormalize(&sp1C, &sp1C);
    VECScale(&sp1C, arg1, temp_f31);
    if (temp_r27 != 0) {
        HuAudFXPlay(1853);
    }
    if (arg2 < 0 || arg2 >= 3) {
        arg2 = 0;
    }
    temp_r28 = lbl_1_data_454[arg2];
    for (temp_r30 = 0; temp_r30 < lbl_1_data_3A4[arg2]; temp_r30++, temp_r28++) {
        VECSubtract(temp_r28, arg0, &sp34);
        temp_f30 = VECMag(&sp34);
        if (temp_f30 < 3.0f && VECMag(arg1) < 1.0f) {
            arg1->x = arg1->y = arg1->z = 0.0f;
            *arg0 = *temp_r28;
            temp_r23 = temp_r30;
            break;
        }
        if (temp_f30 < 20.0f
#if VERSION_REV1
            && !(temp_f30 < 0.000001)
#endif
        ) {
            VECScale(arg1, arg1, 0.9f);
            VECNormalize(&sp34, &sp34);
            VECScale(&sp34, &sp34, 0.1 * (20.0f - temp_f30));
            VECAdd(arg1, &sp34, arg1);
            break;
        }
    }
    if (temp_r30 == lbl_1_data_3A4[arg2]) {
        arg1->y += 0.3;
#if VERSION_REV1
        if (VECMag((Vec *)&arg1) < 0.000001) {
            arg1->y += 0.3;
        }
#endif
    }
    if (arg0->x >= lbl_1_bss_77C.x - 13.0f) {
        arg0->x = lbl_1_bss_77C.x - 13.0f - 1.0f;
    }
    if (arg0->y >= lbl_1_bss_77C.y - 13.0f) {
        arg0->y = lbl_1_bss_77C.y - 13.0f - 1.0f;
    }
    if (arg0->x <= lbl_1_bss_770.x + 13.0f) {
        arg0->x = lbl_1_bss_770.x + 13.0f + 1.0f;
    }
    if (arg0->y <= lbl_1_bss_770.y + 13.0f) {
        arg0->y = lbl_1_bss_770.y + 13.0f + 1.0f;
    }
    VECSubtract(arg0, &sp10, &sp34);
    lbl_1_bss_370[lbl_1_bss_310++] = VECMag(&sp34);
    return temp_r23;
}

void fn_1_C214(void)
{
    Mtx sp98;
    Mtx sp68;
    Mtx sp38;
    Mtx sp8;
    ModelData *temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    MTXRotDeg(sp8, 'z', 120);
    while (1) {
        temp_r31 = &Hu3DData[lbl_1_bss_199C2[9]];
        Hu3DMotionExec(lbl_1_bss_199C2[9], temp_r31->unk_08, temp_r31->unk_64, 0);
        Hu3DModelObjMtxGet(lbl_1_bss_199C2[9], "kaitendai-r_dai", sp38);
        for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
            temp_r31 = &Hu3DData[lbl_1_bss_199C2[temp_r30]];
            MTXTrans(sp68, lbl_1_bss_860[temp_r30].x, lbl_1_bss_860[temp_r30].y, lbl_1_bss_860[temp_r30].z);
            MTXConcat(sp68, lbl_1_bss_794[temp_r30], sp68);
            MTXConcat(sp38, sp68, sp98);
            MTXCopy(sp98, temp_r31->unk_F0);
            temp_r31 = &Hu3DData[lbl_1_bss_199C2[temp_r30 + 55]];
            MTXTrans(sp68, 0, 150, 0);
            MTXConcat(sp38, sp68, sp98);
            MTXCopy(sp98, temp_r31->unk_F0);
            temp_r31 = &Hu3DData[lbl_1_bss_199C2[temp_r30 + 58]];
            MTXTrans(sp68, 0, 150, 0);
            MTXConcat(sp38, sp68, sp98);
            MTXCopy(sp98, temp_r31->unk_F0);
            temp_r31 = &Hu3DData[lbl_1_bss_199C2[temp_r30 + 65]];
            MTXTrans(sp68, 0, 150, 0);
            MTXConcat(sp38, sp68, sp98);
            MTXCopy(sp98, temp_r31->unk_F0);
            temp_r31 = &Hu3DData[lbl_1_bss_199C2[temp_r30 + 68]];
            MTXTrans(sp68, 0, 150, lbl_1_bss_788[temp_r30] - 5.0f);
            MTXConcat(sp38, sp68, sp98);
            MTXCopy(sp98, temp_r31->unk_F0);
            for (temp_r29 = 0; temp_r29 < 5; temp_r29++) {
                if (temp_r30 != lbl_1_data_2C8[temp_r29]) {
                    continue;
                }
                temp_r31 = &Hu3DData[lbl_1_bss_199C2[temp_r29 + 38]];
                MTXTrans(sp68, lbl_1_bss_824[temp_r29].x, lbl_1_bss_824[temp_r29].y, lbl_1_bss_824[temp_r29].z);
                mtxScaleCat(sp68, 0.35f, 0.35f, 0.35f);
                MTXConcat(sp38, sp68, sp98);
                MTXCopy(sp98, temp_r31->unk_F0);
                temp_r31 = &Hu3DData[lbl_1_bss_199C2[temp_r29 + 85]];
                MTXTrans(sp68, lbl_1_bss_824[temp_r29].x, lbl_1_bss_824[temp_r29].y + 1.0f, lbl_1_bss_824[temp_r29].z);
                mtxScaleCat(sp68, 0.5f, 0.5f, 0.5f);
                MTXConcat(sp38, sp68, sp98);
                MTXCopy(sp98, temp_r31->unk_F0);
            }
            MTXConcat(sp38, sp8, sp38);
        }
        HuPrcVSleep();
    }
}

void fn_1_C73C(ModelData *model, Mtx matrix)
{
    s16 temp_r31;
    u8 temp_r30;
    u8 temp_r29;
    u8 temp_r28;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_S8, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXLoadPosMtxImm(matrix, GX_PNMTX0);
    temp_r30 = temp_r29 = temp_r28 = 255;
    for (temp_r31 = 0; temp_r31 < lbl_1_bss_1884; temp_r31++) {
        if (lbl_1_bss_884[temp_r31]) {
            temp_r30 = 255;
            temp_r29 = temp_r28 = 0;
        }
        else {
            temp_r30 = temp_r29 = temp_r28 = 255;
        }
        GXBegin(GX_LINES, GX_VTXFMT0, 2);
        GXPosition3f32(lbl_1_bss_D8F0[temp_r31].x, 150, lbl_1_bss_D8F0[temp_r31].y);
        GXColor3u8(temp_r30, temp_r29, temp_r28);
        GXPosition3f32(lbl_1_bss_18F0[temp_r31].x, 150, lbl_1_bss_18F0[temp_r31].y);
        GXColor3u8(temp_r30, temp_r29, temp_r28);
        GXEnd();
    }
}

#define VECDistance2XYZ3(a, b, c)                                                                                                                    \
    ((((a)->x * (b)->x) - ((a)->x * (c)->x)) + (((a)->y * (b)->y) - ((a)->y * (c)->y)) + (((a)->z * (b)->z) - ((a)->z * (c)->z)))

Vec *fn_1_CA30(Vec *arg0, Vec *arg1, Vec *arg2)
{
    float temp_f31;
    Vec spC;
    VECNormalize(arg2, &spC);
    temp_f31 = -VECDistance2XYZ3(&spC, arg1, arg0);
    temp_f31 /= VECMag2Point(&spC);
    lbl_1_bss_314.x = (arg1->x + (spC.x * temp_f31));
    lbl_1_bss_314.y = (arg1->y + (spC.y * temp_f31));
    lbl_1_bss_314.z = (arg1->z + (spC.z * temp_f31));
    return &lbl_1_bss_314;
}

float fn_1_CB70(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Vec *temp_r31 = fn_1_CA30(arg0, arg1, arg2);
    temp_r31->x -= arg0->x;
    temp_r31->y -= arg0->y;
    temp_r31->z -= arg0->z;
    return sqrtf(VECMag2Point(temp_r31));
}

s32 fn_1_CE08(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4)
{
    float temp_f31;
    float temp_f30;
    s32 sp8 = 1;
    temp_f31 = (arg1->x * (arg2->y - arg0->y)) - (arg1->y * (arg2->x - arg0->x));
    if (0.0f != (arg3->x * arg1->y) - (arg3->y * arg1->x)) {
        temp_f31 /= (arg3->x * arg1->y) - (arg3->y * arg1->x);
    }
    else {
        return 0;
    }
    if (arg1->x != 0.0) {
        temp_f30 = (((temp_f31 * arg3->x) + arg2->x) - arg0->x) / arg1->x;
    }
    else if (arg1->y != 0.0) {
        temp_f30 = (((temp_f31 * arg3->y) + arg2->y) - arg0->y) / arg1->y;
    }
    else {
        temp_f30 = (((temp_f31 * arg3->z) + arg2->z) - arg0->z) / arg1->z;
    }
    arg4->x = (temp_f30 * arg1->x) + arg0->x;
    arg4->y = (temp_f30 * arg1->y) + arg0->y;
    arg4->z = (temp_f30 * arg1->z) + arg0->z;
    return 1;
}

s32 fn_1_CF9C(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4)
{
    float temp_f31;
    float temp_f30;
    Vec sp14;
    Vec sp8;
    sp14.x = arg1->x - arg0->x;
    sp14.y = arg1->y - arg0->y;
    sp14.z = arg1->z - arg0->z;
    sp8.x = arg3->x - arg2->x;
    sp8.y = arg3->y - arg2->y;
    sp8.z = arg3->z - arg2->z;
    temp_f31 = (sp14.x * (arg2->y - arg0->y)) - (sp14.y * (arg2->x - arg0->x));
    if (0.0f != (sp8.x * sp14.y) - (sp8.y * sp14.x)) {
        temp_f31 /= (sp8.x * sp14.y) - (sp8.y * sp14.x);
    }
    else {
        return 0;
    }
    if (sp14.x != 0.0) {
        temp_f30 = (((temp_f31 * sp8.x) + arg2->x) - arg0->x) / sp14.x;
    }
    else if (sp14.y != 0.0) {
        temp_f30 = (((temp_f31 * sp8.y) + arg2->y) - arg0->y) / sp14.y;
    }
    else {
        temp_f30 = (((temp_f31 * sp8.z) + arg2->z) - arg0->z) / sp14.z;
    }
    if (temp_f30 < 0.0f || temp_f30 > 1.0f || temp_f31 < 0.0f || temp_f31 > 1.0f) {
        return 0;
    }
    arg4->x = (temp_f30 * sp14.x) + arg0->x;
    arg4->y = (temp_f30 * sp14.y) + arg0->y;
    arg4->z = (temp_f30 * sp14.z) + arg0->z;
    return 1;
}

void fn_1_D1E0(s16 model)
{
    Vec sp14[4];
    Vec sp8;
    s32 temp_r31;
    s32 temp_r30;
    HsfData *temp_r29;
    HsfBuffer *temp_r28;
    HsfFace *temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    s32 temp_r24;
    s32 temp_r23;
    HsfBuffer *temp_r22;
    temp_r29 = Hu3DData[model].hsfData;
    lbl_1_bss_77C.x = lbl_1_bss_77C.y = -100000;
    lbl_1_bss_770.x = lbl_1_bss_770.y = 100000;
    temp_r28 = temp_r29->face;
    for (temp_r24 = temp_r31 = 0; temp_r24 < temp_r29->faceCnt; temp_r24++, temp_r28++) {
        temp_r27 = temp_r28->data;
        for (temp_r23 = 0; temp_r23 < temp_r28->count; temp_r23++, temp_r27++) {
            switch (temp_r27->type & 0x7) {
                case 0:
                case 1:
                case 2:
                    break;

                case 3:
                    temp_r22 = temp_r29->vertex;
                    for (temp_r26 = temp_r25 = 0; temp_r26 < 4; temp_r26++) {
                        sp8 = ((Vec *)temp_r22->data)[temp_r27->indices[temp_r26][0]];
                        for (temp_r30 = 0; temp_r30 < temp_r25; temp_r30++) {
                            if (sp8.y != sp14[temp_r30].y) {
                                break;
                            }
                        }
                        if (temp_r30 == temp_r25) {
                            sp14[temp_r30].x = sp8.x;
                            sp14[temp_r30].y = sp8.y;
                            sp14[temp_r30].z = sp8.z;
                            temp_r25++;
                        }
                    }
                    lbl_1_bss_D8F0[temp_r31].x = sp14[0].x;
                    lbl_1_bss_D8F0[temp_r31].y = sp14[0].z;
                    lbl_1_bss_D8F0[temp_r31].z = 0;
                    if (sp14[0].x > lbl_1_bss_77C.x) {
                        lbl_1_bss_77C.x = sp14[0].x;
                    }
                    if (sp14[0].z > lbl_1_bss_77C.y) {
                        lbl_1_bss_77C.y = sp14[0].z;
                    }
                    if (sp14[0].x < lbl_1_bss_770.x) {
                        lbl_1_bss_770.x = sp14[0].x;
                    }
                    if (sp14[0].z < lbl_1_bss_770.y) {
                        lbl_1_bss_770.y = sp14[0].z;
                    }
                    lbl_1_bss_18F0[temp_r31].x = sp14[1].x;
                    lbl_1_bss_18F0[temp_r31].y = sp14[1].z;
                    lbl_1_bss_18F0[temp_r31].z = 0;

                    if (sp14[1].x > lbl_1_bss_77C.x) {
                        lbl_1_bss_77C.x = sp14[1].x;
                    }
                    if (sp14[1].z > lbl_1_bss_77C.y) {
                        lbl_1_bss_77C.y = sp14[1].z;
                    }
                    if (sp14[1].x < lbl_1_bss_770.x) {
                        lbl_1_bss_770.x = sp14[1].x;
                    }
                    if (sp14[1].z < lbl_1_bss_770.y) {
                        lbl_1_bss_770.y = sp14[1].z;
                    }
                    temp_r31++;
                    break;

                case 4:
                    break;

                default:
                    break;
            }
        }
    }
    lbl_1_bss_1884 = temp_r31;
}
