#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/objsub.h"

#include "game/hsfmotion.h"
#include "game/pad.h"

#include "REL/m455Dll.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/minigame_seq.h"
#include "game/wipe.h"

#include "ext_math.h"
#include "math.h"
#include <string.h>

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/hsfex.h"
#endif

typedef struct camera_view_params {
    float zoom;
    Vec pos;
    Vec rot;
} CameraViewParams;

CameraViewParams lbl_1_data_0[2] = { { 500, { 0, 1000, 0 }, { 40, 0, 0 } }, { 1985, { 0, 300, 0 }, { -6, 0, 0 } } };
Vec lbl_1_data_38 = { 700, 2500, -700 };
Vec lbl_1_data_44 = { 0, 0, 0 };
GXColor lbl_1_data_50 = { 255, 255, 255, 255 };
Vec lbl_1_data_54 = { 200, 15000, -200 };
Vec lbl_1_data_60 = { 0, 1, 0 };

omObjData *lbl_1_bss_40;
omObjData *lbl_1_bss_3C;
omObjData *lbl_1_bss_38;
s32 lbl_1_bss_34;
s32 lbl_1_bss_30;
s32 lbl_1_bss_2C;
s32 lbl_1_bss_28;
s16 lbl_1_bss_26;
s16 lbl_1_bss_24;
s16 lbl_1_bss_22;
s16 lbl_1_bss_20;
s16 lbl_1_bss_18[4];
s16 lbl_1_bss_16;
s16 lbl_1_bss_14;
Vec lbl_1_bss_8;
s16 lbl_1_bss_4;
s32 lbl_1_bss_0;

void fn_1_330(omObjData *object);
void fn_1_B94(Process *objman);
void fn_1_2A90(Process *objman);

void ObjectSetup(void)
{
    Process *objman;
    CameraData *camera = &Hu3DCamera[0];
    s16 light;
    OSReport("******* M455ObjectSetup *********\n");
    objman = omInitObjMan(50, 8192);
    omGameSysInit(objman);
    Hu3DCameraCreate(HU3D_CAM0);
    Hu3DCameraPerspectiveSet(HU3D_CAM0, -1, 20, 25000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM0, 0, 0, 640, 480, 0, 1);
    lbl_1_bss_3C = omAddObjEx(objman, 32730, 0, 0, -1, omOutView);
    lbl_1_bss_8.x = lbl_1_data_44.x - lbl_1_data_38.x;
    lbl_1_bss_8.y = lbl_1_data_44.y - lbl_1_data_38.y;
    lbl_1_bss_8.z = lbl_1_data_44.z - lbl_1_data_38.z;
    VECNormalize(&lbl_1_bss_8, &lbl_1_bss_8);
    light = Hu3DGLightCreateV(&lbl_1_data_38, &lbl_1_bss_8, &lbl_1_data_50);
    Hu3DGLightInfinitytSet(light);
    Hu3DGLightStaticSet(light, 1);
    Hu3DShadowCreate(10, camera->nnear, camera->ffar);
    Hu3DShadowTPLvlSet(0.7f);
    Hu3DShadowPosSet(&lbl_1_data_54, &lbl_1_data_60, &lbl_1_data_44);
    HuAudSndGrpSet(77);
    lbl_1_bss_38 = omAddObjEx(objman, 0, 0, 0, -1, fn_1_330);
    fn_1_2A90(objman);
    fn_1_B94(objman);
    fn_1_32C4(objman);
}

void fn_1_310(s32 arg0)
{
    lbl_1_bss_34 = arg0;
}

s32 fn_1_320(void)
{
    return lbl_1_bss_34;
}

void fn_1_478(omObjData *object);

void fn_1_330(omObjData *object)
{
    CameraData *camera = &Hu3DCamera[0];
    lbl_1_bss_34 = 0;
    lbl_1_bss_2C = 60;
    lbl_1_bss_30 = -1;
    lbl_1_bss_26 = 30;
    lbl_1_bss_24 = 60;
    lbl_1_bss_22 = -1;
    lbl_1_bss_20 = 0;
    lbl_1_bss_16 = ((frand16() * 270.0f) / 65536.0f) + 30.0f;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    camera->fov = 30.0f;
    object->func = fn_1_478;
}

void fn_1_B38(omObjData *object);
void fn_1_C28(void);
s32 fn_1_C90(void);

typedef struct m455_player {
    u8 field0 : 1;
    u8 field1 : 1;
    u8 field2 : 1;
    s16 unk2;
    s16 unk4;
    s8 unk6;
    s8 unk7;
    u16 unk8;
    u16 unkA;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s32 unk18;
    s32 unk1C;
    u32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    Vec unk34[2];
    Vec unk4C;
    s16 unk58;
    s32 unk5C[4];
} M455Player;

s16 lbl_1_data_90 = -1;
s32 lbl_1_data_94 = -1;
s32 lbl_1_data_98 = -1;

void fn_1_478(omObjData *object)
{
    s32 i;
    omObjData **playerList;
    M455Player *player;

    switch (fn_1_320()) {
        case 0:
            if (lbl_1_data_98 < 0) {
                lbl_1_data_98 = HuAudFXPlay(1985);
            }
            if (--lbl_1_bss_2C == 0) {
                fn_1_310(1);
                lbl_1_bss_2C = 120;
            }
            break;

        case 1:
            if (--lbl_1_bss_2C == 0) {
                fn_1_310(2);
                lbl_1_bss_4 = MGSeqStartCreate();
            }
            break;

        case 2:
            if (!MGSeqStatGet(lbl_1_bss_4)) {
                fn_1_310(3);
            }
            if (lbl_1_data_94 < 0 && (MGSeqStatGet(lbl_1_bss_4) & 0x10)) {
                lbl_1_data_94 = HuAudSeqPlay(60);
            }
            break;

        case 3:
            if (--lbl_1_bss_24 == 0) {
                lbl_1_bss_26--;
                if (lbl_1_data_90 >= 0) {
                    MGSeqParamSet(lbl_1_data_90, 1, lbl_1_bss_26);
                }
                lbl_1_bss_24 = 60;
                if (lbl_1_bss_26 == 10) {
                    lbl_1_data_90 = MGSeqTimerCreate(10);
                }
            }
            if (lbl_1_bss_16 >= 0) {
                lbl_1_bss_16--;
            }
            if (lbl_1_bss_26 == 0 || fn_1_C90()) {
                fn_1_310(4);
                lbl_1_bss_4 = MGSeqFinishCreate();
                HuAudSeqFadeOut(lbl_1_data_94, 100);
            }
            break;

        case 4:
            if (lbl_1_data_90 >= 0) {
                MGSeqParamSet(lbl_1_data_90, 2, -1);
                lbl_1_data_90 = -1;
            }
            if (!MGSeqStatGet(lbl_1_bss_4)) {
                fn_1_310(7);
                lbl_1_bss_2C = 120;
            }
            break;

        case 7:
            if (--lbl_1_bss_2C == 0) {
                fn_1_310(9);
                if (lbl_1_bss_30 >= 0) {
                    HuAudSStreamPlay(1);
                    playerList = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
                    for (i = 0; i < 4; i++) {
                        player = playerList[i]->data;
                        if (player->unk28 < 0) {
                            GWPlayerCoinWinSet(i, lbl_1_bss_22 + 1);
                        }
                    }
                }
                else {
                    HuAudSStreamPlay(4);
                    for (i = 0; i < 4; i++) {
                        GWPlayerCoinWinSet(i, 3);
                    }
                }
                lbl_1_bss_2C = 210;
            }
            break;

        case 9:
            if (--lbl_1_bss_2C == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                HuAudFXStop(lbl_1_data_98);
                object->func = fn_1_B38;
            }
            break;
    }
    if (lbl_1_bss_20) {
        if (lbl_1_bss_20 >= 2) {
            for (i = 0; i < 100; i++) {
                s32 srcIdx = (frand8() * lbl_1_bss_20) >> 8;
                s32 dstIdx = (frand8() * lbl_1_bss_20) >> 8;
                s32 temp = lbl_1_bss_18[srcIdx];
                lbl_1_bss_18[srcIdx] = lbl_1_bss_18[dstIdx];
                lbl_1_bss_18[dstIdx] = temp;
            }
        }
        playerList = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
        for (i = 0; i < lbl_1_bss_20; i++) {
            lbl_1_bss_22++;
            GWPlayerCoinWinSet(lbl_1_bss_18[i], lbl_1_bss_22);
            player = playerList[lbl_1_bss_18[i]]->data;
            player->unk28 = lbl_1_bss_22;
        }
        lbl_1_bss_20 = 0;
    }
    if (omSysExitReq && !WipeStatGet()) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_B38;
    }
}

void fn_1_B38(omObjData *object)
{
    if (WipeStatGet()) {
        return;
    }
    fn_1_C28();
    fn_1_340C();
    MGSeqKillAll();
    HuAudFadeOut(1);
    omOvlReturnEx(1, 1);
    OSReport("******* M455Exit *********\n");
}

void fn_1_D14(omObjData *object);

void fn_1_B94(Process *objman)
{
    s32 i;
    lbl_1_bss_28 = 0;
    lbl_1_bss_14 = 3;
    omMakeGroupEx(objman, 0, 4);
    for (i = 0; i < 4; i++) {
        omAddObjEx(objman, 5, 10, 50, 0, fn_1_D14);
    }
}

void fn_1_2010(omObjData *object);

void fn_1_C28(void)
{
    s32 i;
    omObjData **playerList;
    playerList = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    if (playerList == NULL) {
        return;
    }
    for (i = 0; i < 4; i++) {
        fn_1_2010(playerList[i]);
    }
}

s32 fn_1_C90(void)
{
    s32 i;
    omObjData **playerList;
    playerList = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    for (i = 0; i < 4; i++) {
        M455Player *player = playerList[i]->data;
        if (!player->field1) {
            return 0;
        }
    }
    return 1;
}

s32 fn_1_3214(void);

u32 lbl_1_data_E0[5][2] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    0,
    0x540024,
    1,
    0x54001C,
    1,
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
    0,
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18),
    0,
};

Vec lbl_1_data_108[4] = {
    { -300, 0, -100 },
    { -100, 0, -100 },
    { 100, 0, -100 },
    { 300, 0, -100 },
};

void fn_1_1444(omObjData *object);

void fn_1_2060(ModelData *arg0, Mtx arg1);

void fn_1_D14(omObjData *object)
{
    M455Player *player;
    s32 charNo;
    u32 i;
    player = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M455Player), MEMORY_DEFAULT_NUM);
    object->data = player;
    memset(player, 0, sizeof(M455Player));
    player->unk2 = lbl_1_bss_28++;
    player->unk4 = GWPlayerCfg[player->unk2].pad_idx;
    player->unkC = fn_1_3214();
    charNo = GWPlayerCfg[player->unk2].character;
    player->unk10 = charNo;
    player->unk12 = GWPlayerCfg[player->unk2].diff;
    player->unk14 = GWPlayerCfg[player->unk2].group;
    object->model[0] = CharModelCreate(charNo, 8);
    Hu3DModelShadowSet(object->model[0]);
    Hu3DModelLayerSet(object->model[0], 3);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    object->model[1] = Hu3DModelCreateFile(0x540002);
    Hu3DModelHookSet(object->model[0], "test11_tex_we-itemhook-r", object->model[1]);
    Hu3DModelAttrSet(object->model[1], HU3D_MOTATTR_SHAPE_PAUSE | HU3D_MOTATTR_PAUSE);
    player->unk1C = 1;
    for (i = 0; i < 5; i++) {
        if (lbl_1_data_E0[i][1] == 0) {
            object->motion[i] = CharModelMotionCreate(player->unk10, lbl_1_data_E0[i][0]);
        }
        else {
            object->motion[i] = CharModelMotionCreate(player->unk10, player->unk10 + lbl_1_data_E0[i][0]);
        }
    }
    Hu3DMotionSet(object->model[0], object->motion[player->unk1C]);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    object->trans.x = lbl_1_data_108[player->unk2].x;
    object->trans.y = lbl_1_data_108[player->unk2].y;
    object->trans.z = lbl_1_data_108[player->unk2].z;
    player->unk2A = espEntry(0x54000C, 0x8000, 0);
    espDispOff(player->unk2A);
    object->model[3] = Hu3DHookFuncCreate(fn_1_2060);
    Hu3DModelLayerSet(object->model[3], 3);
    Hu3DModelCameraSet(object->model[3], HU3D_CAM0);
    Hu3DData[object->model[3]].unk_120 = object;
    object->model[4] = Hu3DModelCreateFile(0x54000A);
    Hu3DModelLayerSet(object->model[4], 3);
    Hu3DModelCameraSet(object->model[4], HU3D_CAM0);
    Hu3DModelShadowSet(object->model[4]);
    i = Hu3DMotionCreateFile(0x54000B);
    Hu3DMotionSet(object->model[4], i);
    Hu3DModelAttrSet(object->model[4], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->model[4], HU3D_MOTATTR_PAUSE);
    player->unk4C.x = object->trans.x + (50.0f * ((((s32)frand() & 0x1FF) - 256.0f) / 256.0f));
    player->unk4C.y = -200;
    player->unk4C.z = -1500;
    Hu3DModelPosSetV(object->model[4], &player->unk4C);
    Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF);
    player->unk34[0].x = object->trans.x;
    player->unk34[0].y = 0;
    player->unk34[0].z = -500;
    player->unk34[1].x = object->trans.x;
    player->unk34[1].y = -200;
    player->unk34[1].z = -1000;
    CharModelDataClose(player->unk10);
    object->rot.y = 180;
    if (((s32)frand() & 0x1F) < 4 - player->unk12) {
        player->unk58 = lbl_1_bss_16 - (60.0f * (0.05f * (4 - player->unk12))) - ((frand8() / 256.0f) * 6.0f);
        if (player->unk58 < 0) {
            player->unk58 = 0;
        }
    }
    else {
        player->unk58 = lbl_1_bss_16 + (60.0f * (0.1f * (4 - player->unk12))) + ((frand8() / 256.0f) * 30.0f) + 6.0f;
    }
    player->unk28 = -1;
    object->func = fn_1_1444;
}

void fn_1_1400(omObjData *object)
{
    M455Player *player = object->data;
    if (player->unk58 != 0) {
        player->unk58--;
    }
    else {
        player->unkA |= PAD_BUTTON_A;
    }
}

float lbl_1_data_154[4] = { -350, -170, 170, 350 };

float lbl_1_data_164[3] = { 1.5f, 1.0f, 0.5f };

float fn_1_2390(float arg0, float arg1, float arg2);
s32 fn_1_24F0(Vec *arg0, Vec *arg1, float arg2);

void fn_1_1444(omObjData *object)
{
    M455Player *temp_r31;
    s32 temp_r29;
    u32 temp_r28;
    Vec sp24[3];
    Vec sp18;
    Vec spC;
    float temp_f31;

    temp_r31 = object->data;
    temp_r29 = temp_r31->unk1C;
    temp_r28 = temp_r31->unk20;
    object->trans.y = fn_1_687C();
    if (fn_1_320() < 3) {
        return;
    }
    switch (temp_r31->unk16) {
        case 0:
            if (fn_1_320() == 4 || lbl_1_bss_14 == 0) {
                temp_r31->field1 = 1;
                temp_r31->unk16 = 2;
                espDispOff(temp_r31->unk2A);
                return;
            }
            if (!GWPlayerCfg[temp_r31->unk2].iscom) {
                temp_r31->unk6 = HuPadStkX[temp_r31->unk4];
                temp_r31->unk7 = HuPadStkY[temp_r31->unk4];
                temp_r31->unk8 = HuPadBtn[temp_r31->unk4];
                temp_r31->unkA = HuPadBtnDown[temp_r31->unk4];
            }
            else {
                temp_r31->unk8 = temp_r31->unkA = 0;
                temp_r31->unk6 = temp_r31->unk7 = 0;
                fn_1_1400(object);
            }
            if (lbl_1_bss_16 == 0) {
                if (temp_r31->unkC) {
                    omVibrate(temp_r31->unk2, 12, 12, 0);
                }
                else {
                    sp18.x = object->trans.x;
                    sp18.y = object->trans.y + 300;
                    sp18.z = object->trans.z;
                    Hu3D3Dto2D(&sp18, HU3D_CAM0, &sp18);
                    espPosSet(temp_r31->unk2A, sp18.x, sp18.y);
                    espDispOn(temp_r31->unk2A);
                    temp_r31->unk30 = 0;
                }
                temp_r31->unk2C = temp_r31->unk2E = 30;
            }

            if (temp_r31->unkA & PAD_BUTTON_A) {
                temp_r31->unk16 = 1;
                temp_r31->unk24 = temp_r31->unk26 = 90;
                temp_r31->unk2C = -1;
                if (lbl_1_bss_16 <= 0) {
                    lbl_1_bss_18[lbl_1_bss_20++] = temp_r31->unk2;
                }
                Hu3DModelAttrReset(object->model[1], HU3D_MOTATTR_SHAPE_PAUSE | HU3D_MOTATTR_PAUSE);
                Hu3DMotionSpeedSet(object->model[1], 1.2f);
                Hu3DMotionShapeSpeedSet(object->model[1], 1.2f);
                HuAudFXPlay(1986);
            }
            temp_r29 = 1;
            temp_r28 = HU3D_MOTATTR_LOOP;
            break;

        case 1:
            temp_r29 = 2;
            temp_r28 = HU3D_MOTATTR_NONE;
            if (!temp_r31->field0) {
                if (temp_r31->unk28 >= 0 && temp_r31->unk28 < 3) {
                    temp_r31->field0 = 1;
                    if (temp_r31->unk28 == 0) {
                        lbl_1_bss_30 = temp_r31->unk2;
                    }
                    temp_f31 = lbl_1_data_164[temp_r31->unk28];
                    Hu3DModelScaleSet(object->model[4], temp_f31, temp_f31, temp_f31);
                    Hu3DModelAttrReset(object->model[4], HU3D_ATTR_DISPOFF);
                }
            }
            temp_f31 = 1.0f - ((float)temp_r31->unk24 / temp_r31->unk26);
            sp24[0].x = temp_r31->unk4C.x;
            sp24[0].y = temp_r31->unk4C.y;
            sp24[0].z = temp_r31->unk4C.z;
            sp24[1].x = object->trans.x;
            sp24[1].y = object->trans.y + 1500;
            sp24[1].z = object->trans.z - 200;
            sp24[2].x = lbl_1_data_154[temp_r31->unk2];
            sp24[2].y = 0;
            sp24[2].z = 150;
            fn_1_24F0(sp24, &sp18, temp_f31);
            VECSubtract(&sp18, &Hu3DData[object->model[4]].pos, &spC);
            Hu3DModelRotSet(object->model[4], atan2d(-spC.y, VECMagXZ(&spC)), atan2d(spC.x, spC.z), 0);
            Hu3DModelPosSetV(object->model[4], &sp18);
            if (sp18.y > 0.0f) {
                if (!temp_r31->field2 && temp_r31->field0) {
                    fn_1_6CB0(&sp18, -1);
                    fn_1_6698(&sp18, -1, -1, -1);
                    temp_r31->field2 = 1;
                }
            }
            temp_r31->unk34[0].x = temp_f31 * (2.0f * lbl_1_data_154[temp_r31->unk2]);
            temp_r31->unk34[0].y = -200.0f + (-400.0f * temp_f31);
            temp_r31->unk34[0].z = -500.0f + (-1500.0f * temp_f31);
            temp_r31->unk34[1].x = temp_f31 * lbl_1_data_154[temp_r31->unk2];
            temp_r31->unk34[1].y = -200.0f + (400.0f * temp_f31);
            temp_r31->unk34[1].z = -1000.0f + (750.0f * temp_f31);
            if (--temp_r31->unk24 == 0) {
                temp_r31->unk16 = 2;
                temp_r31->field1 = 1;
                if (temp_r31->field0) {
                    Hu3DModelAttrReset(object->model[4], HU3D_MOTATTR_PAUSE);
                    Hu3DModelRotSet(object->model[4], 0, 0, 0);
                    lbl_1_bss_14--;
                }
            }
            break;

        case 2:
            if (fn_1_320() == 7) {
                temp_r31->unk16 = 3;
                Hu3DModelObjPosGet(object->model[0], "test11_tex_we-itemhook-r", &sp18);
                CharModelEffectCreate(1, &sp18);
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
            }
            break;

        case 3:
            if (fn_1_320() < 9) {
                temp_r29 = 0;
                temp_r28 = HU3D_MOTATTR_LOOP;
            }
            else {
                object->rot.y = fn_1_2390(object->rot.y, 0, 0.2f);
                if (temp_r31->unk2 == lbl_1_bss_30) {
                    temp_r29 = 3;
                    temp_r28 = HU3D_MOTATTR_NONE;
                }
                else {
                    temp_r29 = 4;
                    temp_r28 = HU3D_MOTATTR_NONE;
                }
            }
            break;

        default:
            break;
    }
    if (temp_r31->unk2C) {
        if (temp_r31->unk2C >= 0) {
            temp_f31 = (0.5 * sind((90.0f * (float)temp_r31->unk2C) / (float)temp_r31->unk2E)) + 0.5;
            espScaleSet(temp_r31->unk2A, temp_f31, temp_f31);
            if (--temp_r31->unk2C == 0) {
                temp_r31->unk2C = temp_r31->unk2E;
            }
            temp_r31->unk30++;
        }
        else {
            if (temp_r31->unk30 > 30.0f) {
                espDispOff(temp_r31->unk2A);
                temp_r31->unk2C = 0;
            }
            else {
                temp_r31->unk30++;
            }
        }
    }
    if (temp_r31->unk16 >= 2 && temp_r31->unk16 <= 3 && temp_r31->field0) {
        Hu3DData[object->model[4]].rot.y += 2.0f;
        if (0.0f == Hu3DData[object->model[4]].unk_64) {
            HuAudFXPlay(1987);
        }
    }
    if ((temp_r29 >= 0 && temp_r29 != temp_r31->unk1C) || temp_r28 != temp_r31->unk20) {
        temp_r31->unk1C = temp_r29;
        temp_r31->unk20 = temp_r28;
        CharModelMotionShiftSet(temp_r31->unk10, object->motion[temp_r31->unk1C], 0, 8, temp_r28);
    }
}

void fn_1_2010(omObjData *object)
{
    M455Player *player = object->data;
    if (object->data != NULL) {
        HuMemDirectFree(object->data);
        object->data = NULL;
    }
}

GXColor lbl_1_data_170 = { 255, 255, 255, 255 };

void fn_1_27A0(Vec *arg0, Vec *arg1, float arg2);

void fn_1_2060(ModelData *arg0, Mtx arg1)
{
    Vec vtxPos[4];
    Mtx mtxHook;

    Vec pos;
    Vec itemHookPos;
    s32 i;
    omObjData *object = arg0->unk_120;
    M455Player *player = object->data;
    ModelData *modelPuku = &Hu3DData[object->model[4]];
    GXLoadPosMtxImm(arg1, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_170);
    GXSetNumTexGens(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    Hu3DModelObjMtxGet(object->model[0], "test11_tex_we-itemhook-r", mtxHook);
    Hu3DModelObjPosGet(object->model[1], "hook", &pos);
    MTXMultVec(mtxHook, &pos, &vtxPos[0]);
    for (i = 0; i < 2; i++) {
        vtxPos[i + 1].x = player->unk34[i].x;
        vtxPos[i + 1].y = player->unk34[i].y;
        vtxPos[i + 1].z = player->unk34[i].z;
    }
    if (player->field0) {
        Mtx hookMtx;
        Vec hookPos;
        Hu3DModelObjMtxGet(object->model[4], "itemhook_C", hookMtx);
        hookPos.x = 0;
        hookPos.y = -60.000004f;
        hookPos.z = 35.0f;
        MTXMultVec(hookMtx, &hookPos, &vtxPos[3]);
    }
    else {
        vtxPos[3].x = modelPuku->pos.x;
        vtxPos[3].y = modelPuku->pos.y;
        vtxPos[3].z = modelPuku->pos.z;
    }
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 20);
    for (i = 0; i < 20; i++) {
        fn_1_27A0(vtxPos, &pos, i / 19.0f);
        GXPosition3f32(pos.x, pos.y, pos.z);
    }
    GXEnd();
}

float fn_1_2390(float arg0, float arg1, float arg2)
{
    float temp_f31 = fmod(arg1 - arg0, 360);
    float temp_f30;
    if (temp_f31 < 0) {
        temp_f31 += 360.0f;
    }
    if (temp_f31 > 180) {
        temp_f31 -= 360.0f;
    }
    temp_f30 = fmod(arg0 + (arg2 * temp_f31), 360);
    if (temp_f30 < 0) {
        temp_f30 += 360.0f;
    }
    return temp_f30;
}

float fn_1_2494(float arg0, float arg1, float arg2, float arg3)
{
    float temp_f31 = 1.0f - arg3;
    return (arg0 * (temp_f31 * temp_f31)) + ((2.0f * temp_f31) * arg3 * arg1) + (arg2 * (arg3 * arg3));
}

s32 fn_1_24F0(Vec *arg0, Vec *arg1, float arg2)
{
    arg1->x = fn_1_2494(arg0[0].x, arg0[1].x, arg0[2].x, arg2);
    arg1->y = fn_1_2494(arg0[0].y, arg0[1].y, arg0[2].y, arg2);
    arg1->z = fn_1_2494(arg0[0].z, arg0[1].z, arg0[2].z, arg2);
}

float fn_1_26F8(float arg0, float arg1, float arg2, float arg3, float arg4)
{
    float temp_f31 = 1.0f - arg0;
    float temp_f30 = temp_f31 * temp_f31;
    float temp_f29 = temp_f31 * temp_f31 * temp_f31;
    return (arg4 * (arg0 * (arg0 * arg0))) + ((arg3 * (arg0 * (3.0f * temp_f31 * arg0))) + ((temp_f29 * arg1) + (arg2 * (3.0f * temp_f30 * arg0))));
}

void fn_1_27A0(Vec *arg0, Vec *arg1, float arg2)
{
    arg1->x = fn_1_26F8(arg2, arg0[0].x, arg0[1].x, arg0[2].x, arg0[3].x);
    arg1->y = fn_1_26F8(arg2, arg0[0].y, arg0[1].y, arg0[2].y, arg0[3].y);
    arg1->z = fn_1_26F8(arg2, arg0[0].z, arg0[1].z, arg0[2].z, arg0[3].z);
}

float lbl_1_data_184[2] = {0.0f, 0.0f};

void fn_1_2AF4(s32 arg0, s32 arg1, float arg2);

void fn_1_2D44(omObjData *object);

void fn_1_2A90(Process *objman)
{
    fn_1_2AF4(0, 0, 0);
    lbl_1_bss_40 = omAddObjEx(objman, 10, 0, 0, -1, fn_1_2D44);
}

void fn_1_2AF4(s32 arg0, s32 arg1, float arg2)
{
    CZoom = lbl_1_data_0[arg0].zoom + (arg2 * (lbl_1_data_0[arg1].zoom - lbl_1_data_0[arg0].zoom));
    Center.x = lbl_1_data_0[arg0].pos.x + (arg2 * (lbl_1_data_0[arg1].pos.x - lbl_1_data_0[arg0].pos.x));
    Center.y = lbl_1_data_0[arg0].pos.y + (arg2 * (lbl_1_data_0[arg1].pos.y - lbl_1_data_0[arg0].pos.y));
    Center.z = lbl_1_data_0[arg0].pos.z + (arg2 * (lbl_1_data_0[arg1].pos.z - lbl_1_data_0[arg0].pos.z));
    CRot.x = lbl_1_data_0[arg0].rot.x + (arg2 * (lbl_1_data_0[arg1].rot.x - lbl_1_data_0[arg0].rot.x));
    CRot.y = lbl_1_data_0[arg0].rot.y + (arg2 * (lbl_1_data_0[arg1].rot.y - lbl_1_data_0[arg0].rot.y));
    CRot.z = lbl_1_data_0[arg0].rot.z + (arg2 * (lbl_1_data_0[arg1].rot.z - lbl_1_data_0[arg0].rot.z));
}

void fn_1_2D44(omObjData *object)
{
    CameraData *camera = &Hu3DCamera[0];
    switch (fn_1_320()) {
        case 1:
            fn_1_2AF4(0, 1, sind(lbl_1_data_184[0] * 90.0f));
            if (lbl_1_data_184[0] < 1.0f) {
                lbl_1_data_184[0] += 1.0f / 60.0f;
                if (lbl_1_data_184[0] > 1.0f) {
                    lbl_1_data_184[0] = 1.0f;
                }
            }
            break;

        case 6:
            fn_1_2AF4(1, 1, 0);
            break;

        case 4:
        case 5:
        case 7:
            break;
    }
}

u32 lbl_1_data_18C[4] = { PAD_CHAN0_BIT, PAD_CHAN1_BIT, PAD_CHAN2_BIT, PAD_CHAN3_BIT };
s32 fn_1_3214(void)
{
    s32 rumble = HuPadRumbleGet();
    s32 i;
    for (i = 0; i < 4; i++) {
        if (!GWPlayerCfg[i].iscom) {
            if ((rumble & lbl_1_data_18C[GWPlayerCfg[i].pad_idx]) == 0) {
                return 0;
            }
        }
    }
    return GWGameStat.rumble;
}

float lbl_1_data_19C[] = { 0, 355, 0, 0, 0, 275, 128, 950, 6, 0, 0, 0, 190, 0, 550 };
