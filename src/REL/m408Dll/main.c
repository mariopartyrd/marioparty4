#include "game/chrman.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/wipe.h"

#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/sprite.h"

#include "game/audio.h"
#include "game/gamework_data.h"

#include "REL/m408Dll.h"

#include "ext_math.h"
#include "math.h"

s32 lbl_1_data_0[] = {
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x00),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x01),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x02),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x03),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x04),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x05),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x06),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x07),
};

Vec lbl_1_data_20 = { 150, 1250, 150 };
Vec lbl_1_data_2C = { -0.1, -0.8, 0.1 };
GXColor lbl_1_data_38 = { 255, 255, 255, 255 };
Vec lbl_1_data_3C[] = { { 0, -2000, 0 }, { 0, 1, 0 } };
GXColor lbl_1_data_54 = { 255, 255, 255, 255 };
Vec lbl_1_data_58 = { 50, 15000, 50 };
Vec lbl_1_data_64 = { 0, 1, 0 };
Vec lbl_1_data_70 = { 0, 0, 0 };

omObjData *lbl_1_bss_78;
omObjData *lbl_1_bss_74;
omObjData *lbl_1_bss_70;
omObjData **lbl_1_bss_6C;
omObjData *lbl_1_bss_68;
s16 lbl_1_bss_66;
s16 lbl_1_bss_64;
u16 lbl_1_bss_62;
u16 lbl_1_bss_60;
s32 lbl_1_bss_5C;
s32 lbl_1_bss_58;
float lbl_1_bss_54;
float lbl_1_bss_50;
u32 lbl_1_bss_4C;
s32 lbl_1_bss_48;
s32 lbl_1_bss_44;
s32 lbl_1_bss_40;
u32 lbl_1_bss_3C;
s32 lbl_1_bss_28[5];
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
omObjData *lbl_1_bss_8;
float lbl_1_bss_4;
s32 lbl_1_bss_0;

void fn_1_51C(omObjData *object);
void fn_1_9F0(omObjData *object);

void fn_1_25D4(Process *objman);

void ObjectSetup(void)
{
    s32 temp_r31;
    Process *temp_r30;
    s16 temp_r29;
    LightData *temp_r28;
    Vec sp14 = { 0, 0, 0 };
    Vec sp8 = { 0, 0, -1 };
    HuAudSndGrpSet(33);
    HuAudFXListnerSetEX(&sp14, &sp8, 6000, 3656.6667f, 0, 300, 300);
    lbl_1_bss_1C = lbl_1_bss_18 = lbl_1_bss_14 = lbl_1_bss_10 = -1;
    lbl_1_bss_C = 0;
    lbl_1_bss_44 = 1;
    lbl_1_bss_40 = 0;
    temp_r29 = Hu3DGLightCreateV(&lbl_1_data_20, &lbl_1_data_2C, &lbl_1_data_38);
    Hu3DGLightInfinitytSet(temp_r29);
    temp_r28 = &Hu3DGlobalLight[temp_r29];
    temp_r28->unk_00 |= 0x8000;
    Hu3DShadowCreate(30, 100, 25000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowPosSet(&lbl_1_data_58, &lbl_1_data_64, &lbl_1_data_70);
    temp_r30 = omInitObjMan(50, 8192);
    omGameSysInit(temp_r30);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        CRotM[temp_r31].x = 324.3f;
        CRotM[temp_r31].y = 0;
        CRotM[temp_r31].z = 0;
        CenterM[temp_r31].x = 0;
        CenterM[temp_r31].y = 130;
        CenterM[temp_r31].z = 224;
        CZoomM[temp_r31] = 220;
    }
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, -1, 5, 25000, (4.0f / 3.0f));
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    lbl_1_bss_70 = omAddObjEx(temp_r30, 32730, 0, 0, -1, omOutView);
    lbl_1_bss_62 = 0;
    lbl_1_bss_60 = 0;
    lbl_1_bss_48 = 0;
    lbl_1_bss_78 = omAddObjEx(temp_r30, 10, 0, 0, -1, fn_1_51C);
    lbl_1_bss_3C = 0;
    for (temp_r31 = 0; temp_r31 < 5; temp_r31++) {
        lbl_1_bss_28[temp_r31] = -1;
    }
    lbl_1_bss_74 = omAddObjEx(temp_r30, 50, 0, 0, -1, fn_1_9F0);
    fn_1_25D4(temp_r30);
    fn_1_C44C(temp_r30);
    fn_1_118D0(temp_r30);
    fn_1_8958(temp_r30);
}

void fn_1_56C(omObjData *object);
void fn_1_9A4(omObjData *object);

void fn_1_51C(omObjData *object)
{
    lbl_1_bss_66 = 30;
    lbl_1_bss_64 = 60;
    lbl_1_bss_4C = 4;
    lbl_1_bss_62 = 0;
    object->func = fn_1_56C;
}

void fn_1_56C(omObjData *object)
{
    s32 temp_r30 = 0;
    Vec sp14;
    Vec sp8;
    switch (lbl_1_bss_62) {
        case 0:
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            lbl_1_bss_44 = 0;
            Hu3DCameraPerspectiveSet(1, 50, 5, 25000, (4.0f / 3.0f));
            lbl_1_bss_62 = 1;
            break;

        case 1:
            if (fn_1_C43C() == 5) {
                lbl_1_bss_62 = 2;
            }
            break;

        case 2:
            if (fn_1_6878() == 5) {
                object->work[0] = 0;
                lbl_1_bss_62 = 3;
            }
            break;

        case 3:
            if (lbl_1_bss_4C == 0 || WipeStatGet() == 0) {
                if (++object->work[0] >= 210.0f) {
                    lbl_1_bss_62 = 4;
                }
            }
            break;

        case 4:
            lbl_1_bss_62 = 5;
            break;

        case 5:
            if (fn_1_C43C() == 5) {
                temp_r30 = 1;
                lbl_1_bss_62 = 5;
            }
            break;
    }
    sp8.x = -(sind(CRot.y) * cosd(CRot.x));
    sp8.y = -(-sind(CRot.x));
    sp8.z = -(cosd(CRot.y) * cosd(CRot.x));
    sp14.x = Center.x - (sp8.x * CZoom);
    sp14.y = Center.y - (sp8.y * CZoom);
    sp14.z = Center.z - (sp8.z * CZoom);
    HuAudFXListnerUpdate(&sp14, &sp8);
    if ((omSysExitReq && !WipeStatGet()) && !lbl_1_bss_44 || temp_r30) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        lbl_1_bss_44 = 1;
        lbl_1_bss_40 = 1;
        if (lbl_1_bss_10 >= 0) {
            HuAudFXFadeOut(lbl_1_bss_10, 30);
        }
        object->func = fn_1_9A4;
    }
}

void fn_1_9A4(omObjData *object)
{
    if (!WipeStatGet()) {
        CharModelKill(-1);
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_A40(omObjData *object);

void fn_1_9F0(omObjData *object)
{
    lbl_1_bss_54 = 12000;
    lbl_1_bss_50 = 0;
    lbl_1_bss_60 = 0;
    object->func = fn_1_A40;
}

void fn_1_CD8(omObjData *object);

u32 fn_1_6868(void);

void fn_1_A40(omObjData *object)
{
    if (fn_1_6868() != 2) {
        return;
    }
    switch (lbl_1_bss_60) {
        case 0:
            Hu3DCameraPerspectiveSet(1, 35, 5, 25000, (4.0f / 3.0f));
            CRot.x = -80.5f;
            CRot.y = CRot.z = 0;
            Center.x = 0;
            Center.y = lbl_1_bss_54;
            Center.z = 0;
            CZoom = 260;
            lbl_1_bss_60 = 1;
            break;

        case 1:
            lbl_1_bss_24 = MGSeqStartCreate();
            MGSeqPosSet(lbl_1_bss_24, 320, 240);
            lbl_1_bss_60 = 2;

        case 2:
            Center.y = lbl_1_bss_54;
            lbl_1_bss_50 = -400.0f;
            ;
            lbl_1_bss_54 += lbl_1_bss_50 * (1.0f / 60.0f);
            if (lbl_1_bss_1C < 0 && (MGSeqStatGet(lbl_1_bss_24) & 0x10)) {
                lbl_1_bss_1C = HuAudSeqPlay(74);
            }
            if (MGSeqStatGet(lbl_1_bss_24) == 0) {
                lbl_1_bss_60 = 3;
                object->func = fn_1_CD8;
            }

            break;
    }
}

void fn_1_8020(void);

void fn_1_EF8(omObjData *object);

void fn_1_12A0(omObjData *object);

void fn_1_CD8(omObjData *object)
{
    Center.y = lbl_1_bss_54;
    lbl_1_bss_50 = -400.0f;
    lbl_1_bss_54 += lbl_1_bss_50 * (1.0f / 60.0f);
    fn_1_8020();
    if (lbl_1_bss_4C == 0) {
        lbl_1_bss_48 = 1;
        lbl_1_bss_20 = MGSeqFinishCreate();
        MGSeqPosSet(lbl_1_bss_20, 320, 240);
        HuAudSeqFadeOut(lbl_1_bss_1C, 100);
        object->func = fn_1_12A0;
    }
    else {
        if (lbl_1_bss_54 <= (-lbl_1_bss_50 * 0.5f)) {
            lbl_1_bss_20 = MGSeqFinishCreate();
            MGSeqPosSet(lbl_1_bss_20, 320, 240);
            HuAudSeqFadeOut(lbl_1_bss_1C, 100);
            lbl_1_bss_50 = -120.00001f;
            lbl_1_bss_54 = -lbl_1_bss_50 * 2.0f;
            lbl_1_bss_60 = 4;
            object->func = fn_1_EF8;
        }
    }
}

void fn_1_18C0(omObjData *object);

void fn_1_EF8(omObjData *object)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f29;
    if (lbl_1_bss_10 < 0) {
        lbl_1_bss_10 = HuAudFXPlay(1360);
    }
    sp30.x = 0;
    sp30.y = 50;
    sp30.z = 230;
    temp_f29 = atan2d(lbl_1_bss_54 - sp30.y, sp30.z);
    if (temp_f29 < 0.0f) {
        temp_f29 += 360.0f;
    }
    Center.x = 0;
    Center.y = lbl_1_bss_54;
    Center.z = 0;
    CRot.x = temp_f29;
    CZoom = sqrtf((sp30.z * sp30.z) + ((lbl_1_bss_54 - sp30.y) * (lbl_1_bss_54 - sp30.y)));
    spC.x = 0;
    spC.z = 0;
    sp24.x = 200;
    sp24.z = 200;
    sp24.y = 800;
    spC.y = 20;
    sp18.x = sp18.y = 0;
    sp18.z = 1;
    Hu3DShadowPosSet(&sp24, &sp18, &spC);
    Hu3DShadowTPLvlSet(0.5f);
    lbl_1_bss_54 += lbl_1_bss_50 * (1.0f / 60.0f);
    if (lbl_1_bss_54 <= 0.0f) {
        lbl_1_bss_54 = 0;
        lbl_1_bss_60 = 5;
        object->func = fn_1_18C0;
    }
}

void fn_1_148C(omObjData *object);

void fn_1_12A0(omObjData *object)
{
    if (lbl_1_bss_54 > (-lbl_1_bss_50 * 0.8f)) {
        Center.y = lbl_1_bss_54;
        lbl_1_bss_50 = -400;
        lbl_1_bss_54 += lbl_1_bss_50 * (1.0f / 60.0f);
    }
    if (MGSeqStatGet(lbl_1_bss_20)) {
        return;
    }
    switch (fn_1_CE68()) {
        case 0:
            OSReport("Map 0\n");
        case 1:
            OSReport("Map 1\n");
            if (lbl_1_bss_40 == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                lbl_1_bss_44 = 1;
            }
            object->func = fn_1_148C;
            break;

        case 2:
            OSReport("Map 2\n");
        case 3:
            OSReport("Map 3\n");
            break;

        case 4:
            OSReport("Map 4\n");
            if (lbl_1_bss_40 == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                lbl_1_bss_44 = 1;
            }
            object->func = fn_1_148C;
            break;
    }
}

void fn_1_148C(omObjData *object)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f29;
    if (!WipeStatGet()) {
        lbl_1_bss_54 = 0;
        sp30.x = 0;
        sp30.y = 50;
        sp30.z = 230;
        temp_f29 = atan2d(lbl_1_bss_54 - sp30.y, sp30.z);
        if (temp_f29 < 0.0f) {
            temp_f29 += 360.0f;
        }
        Center.x = 0;
        Center.y = lbl_1_bss_54;
        Center.z = 0;
        CRot.x = temp_f29;
        CZoom = sqrtf((sp30.z * sp30.z) + ((lbl_1_bss_54 - sp30.y) * (lbl_1_bss_54 - sp30.y)));
        spC.x = 0;
        spC.z = 0;
        sp24.x = 200;
        sp24.z = 200;
        sp24.y = 800;
        spC.y = 20;
        sp18.x = sp18.y = 0;
        sp18.z = 1;
        Hu3DShadowPosSet(&sp24, &sp18, &spC);
        Hu3DShadowTPLvlSet(0.5f);
        fn_1_CEEC();
        if (lbl_1_bss_10 < 0) {
            lbl_1_bss_10 = HuAudFXPlay(1360);
        }
        if (lbl_1_bss_40 == 0) {
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            lbl_1_bss_44 = 0;
        }
        lbl_1_bss_60 = 5;
        object->func = fn_1_18C0;
    }
    else {
        if (lbl_1_bss_54 > (-lbl_1_bss_50 * 0.8f)) {
            Center.y = lbl_1_bss_54;
            lbl_1_bss_50 = -400;
            lbl_1_bss_54 += lbl_1_bss_50 * (1.0f / 60.0f);
        }
    }
}

void fn_1_18C0(omObjData *object)
{
    if (!WipeStatGet() && lbl_1_bss_14 < 0) {
        if (lbl_1_bss_C) {
            lbl_1_bss_14 = HuAudSStreamPlay(1);
        }
        else {
            lbl_1_bss_14 = HuAudSStreamPlay(4);
        }
    }
}

float lbl_1_data_A0[] = { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 };

void fn_1_1940(Work2FAC *arg0, Vec *arg1)
{
    Mtx sp18;
    Vec spC;
    spC.x = sind(arg0->unk58.x + 90.0f);
    spC.y = 0;
    spC.z = cosd(arg0->unk58.x + 90.0f);
    MTXRotAxisDeg(sp18, &spC, arg0->unk58.y);
    spC.x = spC.z = 0;
    spC.y = -lbl_1_data_A0[arg0->unk2];
    MTXMultVec(sp18, &spC, arg1);
}

void fn_1_1A60(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    Mtx spC;
    mtxRot(spC, arg1->x, arg1->y, arg1->z);
    MTXMultVec(spC, arg2, arg3);
    arg3->x += arg0->x;
    arg3->y += arg0->y;
    arg3->z += arg0->z;
}

void fn_1_1AF8(Work2FAC *arg0, s32 arg1, Vec *arg2)
{
    float temp_f31;
    float temp_f30;
    temp_f30 = temp_f31 = 0;
    arg2->x = (temp_f31 * sind(temp_f30)) + arg0->unk1C.x;
    arg2->y = 15.0f + arg0->unk1C.y + temp_f31;
    arg2->z = (temp_f31 * cosd(temp_f30)) + arg0->unk1C.z;
}

void fn_1_1BE8(omObjData *arg0, float arg1)
{
    Vec sp8;
    Work2FAC *temp_r31 = arg0->data;
    float temp_f31 = 1.0f - arg1;
    float temp_f29;
    if (!temp_r31->unk8) {
        return;
    }
    fn_1_1AF8(temp_r31, 1, &sp8);
    if (fn_1_6878() >= 4) {
        sp8.z += -5.0f;
    }
    temp_r31->unk94.x = (temp_r31->unk94.x * temp_f31) + (sp8.x * arg1);
    temp_r31->unk94.y = (temp_r31->unk94.y * temp_f31) + (sp8.y * arg1);
    temp_r31->unk94.z = (temp_r31->unk94.z * temp_f31) + (sp8.z * arg1);
    temp_f29 = (0.1f * ((temp_r31->unk8 * 0.5f) + 0.5f)) * arg1;
    temp_r31->unkA0.x = temp_r31->unkC * (temp_f29 + (temp_r31->unkA0.x * temp_f31));
    temp_r31->unkA0.y = temp_r31->unkC * (temp_f29 + (temp_r31->unkA0.y * temp_f31));
    temp_r31->unkA0.z = temp_r31->unkC * (temp_f29 + (temp_r31->unkA0.z * temp_f31));
    Hu3DModelPosSetV(arg0->model[1], &temp_r31->unk94);
    Hu3DModelScaleSetV(arg0->model[1], &temp_r31->unkA0);
}

void fn_1_1E54(omObjData *object)
{
    Work2FAC *work = object->data;
    if (work->unk8) {
        work->unk94.y += 0.5f;
        Hu3DModelPosSetV(object->model[1], &work->unk94);
    }
}

s32 fn_1_1EBC(omObjData *object)
{
    float temp_f31;
    float temp_f22;
    float temp_f21;
    Vec sp3C;
    Vec sp30;
    Vec sp24;

    Work2FAC *temp_r31 = object->data;
    temp_f31 = (temp_r31->unk1C.x * temp_r31->unk1C.x) + ((10.0f / 7.0f) * ((10.0f / 7.0f) * temp_r31->unk1C.z * temp_r31->unk1C.z));
    if (temp_f31 > 6400) {
        temp_f22 = 80.0f / sqrtf(temp_f31);
        sp3C.x = temp_r31->unk1C.x * temp_f22;
        sp3C.z = temp_r31->unk1C.z * temp_f22;
        temp_r31->unk34.x = sp3C.x - temp_r31->unk1C.x;
        temp_r31->unk34.z = sp3C.z - temp_r31->unk1C.z;
        temp_f21 = 80.0f * sqrtf(0.51f);
        sp30.x = temp_f21 - sp3C.x;
        sp30.z = -sp3C.z;
        sp24.x = -temp_f21 - sp3C.x;
        sp24.z = -sp3C.z;
        temp_f31 = 1.0f / VECMagXZ(&sp30);
        sp30.x *= temp_f31;
        sp30.z *= temp_f31;
        temp_f31 = 1.0f / VECMagXZ(&sp24);
        sp24.x *= temp_f31;
        sp24.z *= temp_f31;
        sp30.x += sp24.x;
        sp30.z += sp24.z;
        temp_f31 = 1.0f / VECMagXZ(&sp30);
        sp30.x *= temp_f31;
        sp30.z *= temp_f31;
        temp_f22 = -((sp30.x * temp_r31->unk28.x) + (sp30.z * temp_r31->unk28.z));
        temp_r31->unk28.x += (sp30.x * 20.0f) + (sp30.x * 2.0f * temp_f22);
        temp_r31->unk28.z += (sp30.z * 20.0f) + (sp30.z * 2.0f * temp_f22);
        return 1;
    }
    else {
        return 0;
    }
}

void fn_1_26E4(omObjData *object);
void fn_1_61FC(omObjData *object);

void fn_1_25D4(Process *objman)
{
    s32 i;
    omMakeGroupEx(objman, 0, 4);
    lbl_1_bss_6C = omGetGroupMemberListEx(objman, 0);
    lbl_1_bss_58 = 0;
    for (i = 0; i < 4; i++) {
        omObjData *object = omAddObjEx(objman, 40, 5, 7, 0, fn_1_26E4);
        if (!GWPlayerCfg[i].iscom) {
            lbl_1_bss_58++;
        }
        object->work[0] = i;
    }
    lbl_1_bss_8 = omAddObjEx(objman, 10, 0, 0, -1, fn_1_61FC);
}

s32 lbl_1_data_C8[] = {
    DATA_MAKE_NUM(DATADIR_M408, 0x02),
    DATA_MAKE_NUM(DATADIR_M408, 0x03),
    DATA_MAKE_NUM(DATADIR_M408, 0x04),
    DATA_MAKE_NUM(DATADIR_M408, 0x05),
    DATA_MAKE_NUM(DATADIR_M408, 0x06),
    DATA_MAKE_NUM(DATADIR_M408, 0x07),
    DATA_MAKE_NUM(DATADIR_M408, 0x08),
    DATA_MAKE_NUM(DATADIR_M408, 0x09),
};

u32 lbl_1_data_E8[] = {
    0,
    23,
    24,
    DATA_MAKE_NUM(DATADIR_M408, 0x2C),
    DATA_MAKE_NUM(DATADIR_M408, 0x3C),
    DATA_MAKE_NUM(DATADIR_M408, 0x34),
    22,
};

float lbl_1_data_104[][2] = { -40, -30, 40, -30, -40, 30, 40, 30 };

float lbl_1_data_124[][2] = { 0, -56, 0, 56, -80, 0, 80, 0 };

void fn_1_2FAC(omObjData *object);
void fn_1_5AB4(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_1_26E4(omObjData *object)
{
    Work2FAC *temp_r31;
    s32 temp_r28;
    s32 temp_r27;

    float sp20[4] = { 0.25, 0.5, 0.75, 1.0 };
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work2FAC), MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    memset(temp_r31, 0, sizeof(Work2FAC));
    temp_r31->unk0 = object->work[0];
    temp_r31->unk2 = GWPlayerCfg[temp_r31->unk0].character;
    temp_r31->unk2 &= 0x7;
    temp_r31->unk4 = 0;
    temp_r31->unk90 = sp20[GWPlayerCfg[object->work[0]].diff & 0x3];
    temp_r31->unk1C.x = lbl_1_data_104[temp_r31->unk0][0];
    temp_r31->unk1C.y = lbl_1_bss_54;
    temp_r31->unk1C.z = lbl_1_data_104[temp_r31->unk0][1];
    temp_r31->unk28.x = temp_r31->unk28.y = temp_r31->unk28.z = 0;
    temp_r31->unk34.x = temp_r31->unk34.y = temp_r31->unk34.z = 0;
    temp_r31->unk58.y = 0;
    temp_r31->unk58.x = 0;
    temp_r31->unk4C.x = temp_r31->unk4C.y = temp_r31->unk4C.z = 0;
    temp_r31->unk58.z = 9.0f;
    temp_r31->unk40.x = temp_r31->unk40.y = temp_r31->unk40.z = 0;
    temp_r31->unk8 = 4;
    temp_r31->unkC = 0;
    fn_1_1940(temp_r31, &temp_r31->unk68);
    omSetTra(object, temp_r31->unk1C.x + temp_r31->unk68.x, temp_r31->unk1C.y + temp_r31->unk68.y, temp_r31->unk1C.z + temp_r31->unk68.z);
    omSetSca(object, 0.075f, 0.075f, 0.075f);
    object->model[0] = CharModelCreate(temp_r31->unk2, 4);
    for (temp_r28 = 0; temp_r28 < 7; temp_r28++) {
        if (lbl_1_data_E8[temp_r28] < 0x10000) {
            object->motion[temp_r28] = CharModelMotionCreate(temp_r31->unk2, lbl_1_data_E8[temp_r28]);
        }
        else {
            object->motion[temp_r28] = Hu3DJointMotionFile(object->model[0], temp_r31->unk2 + lbl_1_data_E8[temp_r28]);
        }
    }
    CharModelVoiceEnableSet(temp_r31->unk2, object->motion[1], 0);
    CharModelMotionShiftSet(temp_r31->unk2, object->motion[0], 0, 0.2, HU3D_MOTATTR_LOOP);
    CharModelLayerSetAll(2);
    CharModelMotionDataClose(temp_r31->unk2);
    object->model[1] = Hu3DModelCreateFile(lbl_1_data_C8[temp_r31->unk2]);
    Hu3DModelLayerSet(object->model[1], 6);
    Hu3DModelScaleSet(object->model[1], 0.1f * temp_r31->unk8, 0.1f * temp_r31->unk8, 0.1f * temp_r31->unk8);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
    temp_r31->unk94.x = temp_r31->unk94.y = temp_r31->unk94.z = 0;
    temp_r31->unkA0.x = temp_r31->unkA0.y = temp_r31->unkA0.z = 0;
    fn_1_1BE8(object, 1.0f);
    temp_r27 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M408, 0x24)), 256);
    object->model[2] = temp_r27;
    Hu3DModelLayerSet(temp_r27, 6);
    Hu3DParticleColSet(temp_r27, 255, 255, 255);
    Hu3DParticleHookSet(temp_r27, fn_1_5AB4);
    Hu3DModelPosSet(temp_r27, 0, 0, 0);
    ((ParticleData *)Hu3DData[temp_r27].unk_120)->unk_00 = 0;
    temp_r31->unk74 = temp_r31->unk78 = 0;
    temp_r31->unk7C[0] = temp_r31->unk7C[1] = 0;
    temp_r31->unk8C = -1;
    temp_r31->unk8E = 0;
    temp_r31->unk84[0] = temp_r31->unk84[1] = 0;
    object->work[1] = 0;
    object->func = fn_1_2FAC;
}

void fn_1_5DCC(s32 arg0, Vec *arg1, u32 arg2);
void fn_1_3E80(omObjData *object);

void fn_1_2FAC(omObjData *object)
{
    Work2FAC *temp_r31 = object->data;
    Vec sp78[] = { { 8, -25, -18 }, { 2, -25, -10 }, { 2, -25, -24 }, { -3, -25, -15 } };
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    float sp14[] = { 45, 135, 225, 315 };
    float temp_f27;
    switch (object->work[1]) {
        case 0:
            fn_1_C3C0(&sp3C, &sp30);
            fn_1_1A60(&sp3C, &sp30, &sp78[temp_r31->unk0], &sp24);
            omSetRot(object, 0, 90, 0);
            omSetTra(object, sp24.x, sp24.y, sp24.z);
            if (fn_1_C43C() != 1) {
                object->work[1]++;
                temp_r31->unk58.y = 60;
                temp_r31->unk58.x = sp14[temp_r31->unk0];
                temp_r31->unk28.x = temp_r31->unk28.y = temp_r31->unk28.z = 0;
                object->trans.x -= 10.0 * (2.0 * sind(temp_r31->unk58.x));
                object->trans.z -= 10.0 * (2.0 * cosd(temp_r31->unk58.x));
                CharModelMotionShiftSet(temp_r31->unk2, object->motion[4], 0, 0.2, HU3D_MOTATTR_LOOP);
                temp_r31->unk1C.x = temp_r31->unk94.x = object->trans.x;
                temp_r31->unk1C.y = temp_r31->unk94.y = object->trans.y;
                temp_r31->unk1C.z = temp_r31->unk94.z = object->trans.z;
            }
            break;

        case 1:
            temp_r31->unk28.y += -98.0f;
            if (temp_r31->unk28.y < -400.0f) {
                temp_r31->unk28.y = -400.0f;
            }
            temp_f27 = object->trans.y;
            object->trans.y += temp_r31->unk28.y * (1.0f / 60.0f);
            temp_r31->unk58.x += 1.5000001f;
            if (temp_r31->unk58.x >= 360.0f) {
                temp_r31->unk58.x -= 360.0f;
            }
            object->trans.x += (3.141590118408203f * (10.0 * sind(temp_r31->unk58.x - 90.0f))) * (1.0f / 60.0f);
            object->trans.z += (3.141590118408203f * (10.0 * cosd(temp_r31->unk58.x - 90.0f))) * (1.0f / 60.0f);
            if (temp_f27 > 12000 && object->trans.y <= 12000) {
                sp3C.x = object->trans.x;
                sp3C.y = object->trans.y;
                sp3C.z = object->trans.z;
                fn_1_5DCC(object->model[2], &sp3C, 100);
            }
            temp_r31->unk4C.x = temp_r31->unk58.y;
            temp_r31->unk4C.y = temp_r31->unk58.x;
            temp_r31->unk4C.z = 0;
            temp_r31->unk1C.x = object->trans.x;
            temp_r31->unk1C.y = object->trans.y;
            temp_r31->unk1C.z = object->trans.z;
            omSetRot(object, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
            Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
            temp_r31->unkC += 0.2f * (1.0f - temp_r31->unkC);
            if (object->trans.y < 11940) {
                object->work[1]++;
            }
            break;
    }
    fn_1_1BE8(object, 1.0f);
    if (fn_1_6878() == 1) {
        omSetSca(object, 0.15f, 0.15f, 0.15f);
        object->trans.x = temp_r31->unk1C.x = temp_r31->unk94.x = lbl_1_data_104[temp_r31->unk0][0];
        object->trans.y = temp_r31->unk1C.y = temp_r31->unk94.y = lbl_1_bss_54;
        object->trans.z = temp_r31->unk1C.z = temp_r31->unk94.z = lbl_1_data_104[temp_r31->unk0][1];
        object->rot.y = temp_r31->unk58.x = atan2d(object->trans.x, object->trans.z) + 180.0;
        Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
        ((ParticleData *)Hu3DData[object->model[2]].unk_120)->unk_00 = 0;
        object->func = fn_1_3E80;
    }
}

void fn_1_38D0(omObjData *arg0, s8 *arg1, s8 *arg2)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    Work2FAC *temp_r31;
    Work2FAC *temp_r30;
    s8 temp_r29;
    s32 temp_r28;
    s32 temp_r25;
    Vec sp18;
    Vec spC;
    s8 sp8[4];

    temp_r31 = arg0->data;
    *arg1 = temp_r31->unk7C[0];
    *arg2 = temp_r31->unk7C[1];
    sp18.x = temp_r31->unk1C.x;
    sp18.y = temp_r31->unk1C.y;
    sp18.z = temp_r31->unk1C.z;
    temp_r25 = fn_1_162CC(&sp18, &spC);
    temp_r29 = 0;
    sp8[0] = -1;
    for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
        if (temp_r28 != temp_r31->unk0) {
            temp_r30 = fn_1_68A8(temp_r28);
            if ((temp_r30->unk4 & 0x12) == 0) {
                sp8[temp_r29++] = temp_r28;
            }
        }
    }
    switch (temp_r31->unk8E) {
        case 0:
            if (temp_r29 > 0 || temp_r25) {
                if (temp_r29 > 0) {
                    temp_r31->unk8C = sp8[frandmod(temp_r29)];
                }
                temp_r31->unk74 = frandmod(180) + 120.0f;
                temp_r31->unk78 = 0;
                temp_r31->unk8E = 1;
            }
            else {
                temp_r31->unk78 = 0;
                temp_r31->unk8E = 2;
            }
            break;

        case 1:
            if ((temp_r31->unk78 & 0x3) == 0) {
                if (temp_r25) {
                    temp_f31 = atan2d(spC.x - temp_r31->unk1C.x, spC.z - temp_r31->unk1C.z);
                }
                else {
                    temp_r30 = fn_1_68A8(temp_r31->unk8C);
                    temp_f31 = atan2d(temp_r30->unk1C.x - temp_r31->unk1C.x, temp_r30->unk1C.z - temp_r31->unk1C.z);
                }
                temp_r31->unk84[1] = fn_1_883C(temp_r31->unk84[0], temp_f31, (0.3f * temp_r31->unk90) + 0.15f);
            }
            temp_r31->unk78++;
            temp_r31->unk84[0] = fn_1_883C(temp_r31->unk84[0], temp_r31->unk84[1], 0.2f);
            temp_r31->unk7C[0] = sind(temp_r31->unk84[0]) * 80.0;
            temp_r31->unk7C[1] = -cosd(temp_r31->unk84[0]) * 80.0;
            *arg1 = temp_r31->unk7C[0];
            *arg2 = temp_r31->unk7C[1];
            temp_r31->unk74--;
            if (temp_r25 == 0 && (temp_r30->unk4 & 0x12)) {
                temp_r31->unk74 = 0;
            }
            if (temp_r31->unk74 == 0) {
                temp_r31->unk8E = 0;
            }
            break;

        case 2:
            if ((temp_r31->unk78 & 0xF) == 0) {
                temp_f30 = (0.04f * frandmod(1000)) - 20.0f;
                temp_f29 = (0.04f * frandmod(1000)) - 20.0f;
                temp_r31->unk84[1] = temp_f31 = atan2d(temp_f30 - temp_r31->unk1C.x, temp_f29 - temp_r31->unk1C.z);
            }
            temp_r31->unk78++;
            temp_r31->unk84[0] = fn_1_883C(temp_r31->unk84[0], temp_r31->unk84[1], 0.2f);
            temp_r31->unk7C[0] = sind(temp_r31->unk84[0]) * 80.0;
            temp_r31->unk7C[1] = -cosd(temp_r31->unk84[0]) * 80.0;
            *arg1 = temp_r31->unk7C[0];
            *arg2 = temp_r31->unk7C[1];
            if (temp_r29 > 0 || temp_r25) {
                temp_r31->unk8E = 0;
            }
            break;
    }
}

#define CHECK_IDLE(pos) (((pos) < 0) ? -(pos) : ((pos) > 15))

void fn_1_4A58(omObjData *object);
void fn_1_5098(omObjData *object);
void fn_1_5684(omObjData *object);

void fn_1_3E80(omObjData *object)
{
    Work2FAC *temp_r31;
    s32 temp_r27;

    float temp_f29;
    float temp_f28;
    float temp_f22;
    float temp_f21;
    float temp_f20;
    s8 sp9;
    s8 sp8;

    temp_r31 = object->data;
    temp_r27 = GWPlayerCfg[temp_r31->unk0].pad_idx;
    sp9 = sp8 = 0;
    if (lbl_1_bss_60 == 3) {
        if (!GWPlayerCfg[temp_r31->unk0].iscom) {
            sp9 = HuPadStkX[temp_r27];
            sp8 = HuPadStkY[temp_r27];
        }
        else {
            fn_1_38D0(object, &sp9, &sp8);
        }
    }
    temp_r31->unk1C.y = lbl_1_bss_54;
    temp_f21 = temp_f20 = 0;
    temp_f28 = temp_r31->unk58.x;
    temp_f22 = -20;
    if (CHECK_IDLE(sp9) || CHECK_IDLE(sp8)) {
        temp_f28 = atan2d(sp9, -sp8);
        if (temp_f28 < 0) {
            temp_f28 += 360;
        }
        temp_f21 = 70 * sind(temp_f28);
        temp_f20 = 70 * cosd(temp_f28);
        temp_f22 = 30;
    }
    fn_1_1EBC(object);
    temp_r31->unk28.x = ((28.0f / 30.0f) * temp_r31->unk28.x) + ((2.0f / 30.0f) * temp_f21);
    temp_r31->unk28.z = ((28.0f / 30.0f) * temp_r31->unk28.z) + ((2.0f / 30.0f) * temp_f20);
    temp_f29 = VECMagXZ(&temp_r31->unk28);
    if (temp_f29 > 200.0f) {
        temp_f29 = 200.0f / temp_f29;
        temp_r31->unk28.x *= temp_f29;
        temp_r31->unk28.z *= temp_f29;
    }
    temp_r31->unk34.x += (temp_r31->unk28.x * (1.0f / 60.0f));
    temp_r31->unk34.y = 0;
    temp_r31->unk34.z += (temp_r31->unk28.z * (1.0f / 60.0f));
    temp_r31->unk58.x = temp_f28;
    temp_r31->unk58.y = (0.9f * temp_r31->unk58.y) + (0.1f * temp_f22);
    temp_r31->unk4C.x = temp_r31->unk58.y;
    temp_r31->unk4C.y = fn_1_883C(temp_r31->unk4C.y, temp_r31->unk58.x, 0.2f);
    temp_r31->unk4C.z = 0;
    omSetRot(object, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
    fn_1_1940(temp_r31, &temp_r31->unk68);
    omSetTra(object, temp_r31->unk1C.x + temp_r31->unk68.x, temp_r31->unk1C.y + temp_r31->unk68.y, temp_r31->unk1C.z + temp_r31->unk68.z);
    temp_r31->unkC += (1.0f - temp_r31->unkC) * 0.2f;
    fn_1_1BE8(object, 0.3f);
    if (temp_r31->unk4 & 0x1) {
        temp_r31->unk8--;
        temp_r31->unk10 = 0;
        temp_r31->unk4 |= 2;
        temp_f29 = VECMagXZ(&temp_r31->unk40);
        if (temp_f29 > 0.0f) {
            temp_f29 = 150.0f / temp_f29;
        }
        temp_r31->unk28.x = temp_r31->unk40.x * temp_f29;
        temp_r31->unk28.z = temp_r31->unk40.z * temp_f29;
        temp_r31->unk34.x = temp_r31->unk28.x * (1.0f / 60.0f);
        temp_r31->unk34.z = temp_r31->unk28.z * (1.0f / 60.0f);
        CharModelMotionShiftSet(temp_r31->unk2, object->motion[5], 0, 0.2f, HU3D_MOTATTR_NONE);
        HuAudFXPlay(1358);
        omVibrate(object->work[0], 12, 4, 2);
        if (temp_r31->unk8) {
            HuAudCharVoicePlay(temp_r31->unk2, 296);
            object->func = fn_1_4A58;
        }
        else {
            temp_r31->unk4 |= 0x30;
            lbl_1_bss_4C--;
            HuAudCharVoicePlay(temp_r31->unk2, 291);
            object->func = fn_1_5684;
        }
    }
    if (fn_1_6878() == 4 && (temp_r31->unk4 & 0x20) == 0) {
        CharModelMotionShiftSet(temp_r31->unk2, object->motion[3], 0, 0.2f, HU3D_MOTATTR_NONE);
        Hu3DModelShadowSet(object->model[0]);
        object->work[1] = 0;
        object->func = fn_1_5098;
    }
}
#undef CHECK_IDLE

void fn_1_4A58(omObjData *object)
{
    Work2FAC *temp_r31;
    s32 temp_r28;
    s32 temp_r26;
    s32 sp8;
    temp_r31 = object->data;
    sp8 = temp_r31->unk0;
    temp_r31->unk4 |= 2;
    temp_r31->unk1C.y = lbl_1_bss_54;
    fn_1_1EBC(object);
    temp_r31->unk28.x = (29.0f / 30.0f) * temp_r31->unk28.x;
    temp_r31->unk28.z = (29.0f / 30.0f) * temp_r31->unk28.z;
    temp_r31->unk34.x += temp_r31->unk28.x * (1.0f / 60.0f);
    temp_r31->unk34.y = 0;
    temp_r31->unk34.z += temp_r31->unk28.z * (1.0f / 60.0f);

    temp_r31->unk58.x += 9.0f;
    if (temp_r31->unk58.x >= 360.0f) {
        temp_r31->unk58.x -= 360.0f;
    }
    temp_r31->unk58.y = 0.9f * temp_r31->unk58.y;
    temp_r31->unk4C.x = temp_r31->unk58.y;
    temp_r31->unk4C.y = temp_r31->unk58.x;
    temp_r31->unk4C.z = 0;
    omSetRot(object, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
    fn_1_1940(temp_r31, &temp_r31->unk68);
    omSetTra(object, temp_r31->unk1C.x + temp_r31->unk68.x, temp_r31->unk1C.y + temp_r31->unk68.y, temp_r31->unk1C.z + temp_r31->unk68.z);
    fn_1_1BE8(object, 0.8f);
    temp_r26 = temp_r31->unk10 & 0x1;
    temp_r31->unk10++;
    if (fn_1_6878() == 4) {
        temp_r26 = 0;
        CharModelMotionShiftSet(temp_r31->unk2, object->motion[3], 0, 0.2f, HU3D_MOTATTR_NONE);
        Hu3DModelShadowSet(object->model[0]);
        object->work[1] = 0;
        object->func = fn_1_5098;
    }
    else if (temp_r31->unk10 > 60) {
        temp_r26 = 0;
        temp_r31->unk4 &= ~0x3;
        CharModelMotionShiftSet(temp_r31->unk2, object->motion[4], 0, 0.2f, HU3D_MOTATTR_LOOP);
        object->func = fn_1_3E80;
    }
    if (temp_r26) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        for (temp_r28 = 0; temp_r28 < temp_r31->unk8; temp_r28++) {
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
        }
    }
    else {
        Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
        for (temp_r28 = 0; temp_r28 < temp_r31->unk8; temp_r28++) {
            Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
        }
    }
}

Vec lbl_1_data_144[] = { { -50, 0, 0 }, { -16, 0, 0 }, { 16, 0, 0 }, { 50, 0, 0 } };

Vec lbl_1_data_174[] = { { 0, 1500, 2500 }, { 1500, 0, 1 }, { 0, 0, 0 } };

void fn_1_54E4(omObjData *object);

void fn_1_5098(omObjData *object)
{
    Work2FAC *temp_r29;
    s32 temp_r27;

    temp_r29 = object->data;
    object->trans.x = lbl_1_data_144[object->work[0]].x;
    object->trans.z = lbl_1_data_144[object->work[0]].z;
    if (object->work[1] == 0) {
        if (lbl_1_bss_3C < temp_r29->unk8) {
            lbl_1_bss_3C = temp_r29->unk8;
        }
    }
    else if (object->work[1] == 10 && lbl_1_bss_3C == temp_r29->unk8) {
        for (temp_r27 = 0; lbl_1_bss_28[temp_r27] >= 0; temp_r27++)
            ;
        lbl_1_bss_28[temp_r27] = temp_r29->unk2;
    }
    object->work[1]++;
    temp_r29->unk1C.y = lbl_1_bss_54;
    temp_r29->unk58.y = 0;
    temp_r29->unk58.x = 0;
    object->rot.x = object->rot.y = object->rot.z = 0;
    object->trans.y = temp_r29->unk1C.y;
    temp_r29->unk1C.x = object->trans.x;
    temp_r29->unk1C.z = object->trans.z;
    temp_r29->unk1C.y += lbl_1_data_A0[temp_r29->unk2];
    if (object->trans.y < 0) {
        object->trans.y = 0;
    }
    fn_1_1BE8(object, 1.0f);
    if (fn_1_6878() == 5) {
        object->func = fn_1_54E4;
        if (temp_r29->unk14) {
            lbl_1_bss_C = 1;
        }
    }
}

void fn_1_54E4(omObjData *object)
{
    Work2FAC *temp_r30 = object->data;
    fn_1_1E54(object);
    if (!(temp_r30->unk4 & 0x8)) {
        temp_r30->unk4 |= 0x8;
        if (temp_r30->unk14 != 0) {
            CharModelMotionShiftSet(temp_r30->unk2, object->motion[1], 0, 0.2f, HU3D_MOTATTR_NONE);
            HuAudCharVoicePlay(temp_r30->unk2, 290);
            GWPlayerCoinCollectAdd(object->work[0], temp_r30->unk14);
        }
        else {
            CharModelMotionShiftSet(temp_r30->unk2, object->motion[2], 0, 0.2f, HU3D_MOTATTR_NONE);
        }
        object->work[1] = 0;
    }
    else if (object->work[1] == 0 && Hu3DMotionEndCheck(object->model[0])) {
        lbl_1_bss_4C--;
        object->work[1]++;
    }
}

void fn_1_5AA0(omObjData *object);

void fn_1_5684(omObjData *object)
{
    Work2FAC *temp_r31;
    s32 temp_r29;
    temp_r31 = object->data;
    if (fabs(object->trans.x) < 160.0 || fabs(object->trans.z) < 160.0) {
        temp_r31->unk1C.x += temp_r31->unk28.x * (1.0f / 60.0f);
        temp_r31->unk1C.z += temp_r31->unk28.z * (1.0f / 60.0f);
        temp_r31->unk58.x += 9.0f;
        if (temp_r31->unk58.x >= 360.0f) {
            temp_r31->unk58.x -= 360.0f;
        }
        temp_r31->unk58.y = 0.9f * temp_r31->unk58.y;
        temp_r31->unk4C.x = 90.0f + temp_r31->unk58.y;
        temp_r31->unk4C.y = temp_r31->unk58.x;
        temp_r31->unk4C.z = 0;
        omSetRot(object, temp_r31->unk4C.x, temp_r31->unk4C.y, temp_r31->unk4C.z);
        fn_1_1940(temp_r31, &temp_r31->unk68);
        omSetTra(object, temp_r31->unk1C.x + temp_r31->unk68.x, temp_r31->unk1C.y + temp_r31->unk68.y, temp_r31->unk1C.z + temp_r31->unk68.z);
    }
    if (fn_1_6878() >= 4) {
        GWPlayerCoinCollectAdd(object->work[0], temp_r31->unk14);
        if (lbl_1_bss_48) {
            Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
            CharModelMotionSet(temp_r31->unk2, object->motion[6]);
            Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
            object->trans.x = lbl_1_data_144[object->work[0]].x;
            object->trans.y = 0;
            object->trans.z = lbl_1_data_144[object->work[0]].z;
            object->rot.x = object->rot.y = object->rot.z = 0;
        }
        else {
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        }

        for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
        }
        object->func = fn_1_5AA0;
    }
}

void fn_1_5AA0(omObjData *object)
{
    Work2FAC *sp8 = object->data;
}

void fn_1_5AB4(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    float temp_f31;
    if (particle->unk_00 == 0) {
        particle->unk_00++;
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk00 = 0;
            temp_r31->unk2C = 0;
            temp_r31->unk40.a = 0;
        }
        return;
    }
    temp_r31 = particle->unk_48;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk00 == 0 || temp_r31->unk00 != 1) {
            continue;
        }
        temp_r31->unk02++;
        temp_f31 = temp_r31->unk02 - 10.2f;
        if (temp_f31 < 0.0f) {
            temp_r31->unk34.x += (temp_r31->unk08.x - temp_r31->unk34.x) * 0.2f;
            temp_r31->unk34.y += (temp_r31->unk08.y - temp_r31->unk34.y) * 0.15f;
            temp_r31->unk34.z += (temp_r31->unk08.z - temp_r31->unk34.z) * 0.2f;
            temp_r31->unk2C += (temp_r31->unk14.x - temp_r31->unk2C) * 0.2f;
            temp_r31->unk14.y += (temp_r31->unk14.z - temp_r31->unk14.y) * 0.2f;
            temp_r31->unk40.a = temp_r31->unk14.y;
        }
        else {
            temp_r31->unk34.x += (temp_r31->unk20 * 1.5f) * (1.0f / 60.0f);
            temp_r31->unk34.y += (temp_r31->unk24 * 1.5f) * (1.0f / 60.0f);
            temp_r31->unk34.z += (temp_r31->unk28 * 1.5f) * (1.0f / 60.0f);
            temp_r31->unk2C += (temp_r31->unk14.x * 0.01f);
            temp_r31->unk40.a = 0.92f * temp_r31->unk40.a;
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_5DCC(s32 arg0, Vec *arg1, u32 arg2)
{
    float temp_f31;
    float temp_f30;

    HsfanimStruct01 *temp_r31;
    ParticleData *temp_r29;
    s32 temp_r28;
    temp_r29 = Hu3DData[arg0].unk_120;
    if (temp_r29->unk_00 != 0) {
        temp_r31 = temp_r29->unk_48;
        for (temp_r28 = 0; temp_r28 < temp_r29->unk_30; temp_r28++, temp_r31++) {
            if (temp_r31->unk00) {
                continue;
            }
            temp_r31->unk00 = 1;
            temp_r31->unk02 = 0;
            temp_r31->unk34.x = arg1->x;
            temp_r31->unk34.y = 11990;
            temp_r31->unk34.z = arg1->z;
            temp_f31 = frandmod(1000) * (1.0f / 1000.0f);
            temp_f30 = frandmod(1000) * (360.0f / 1000.0f);
            temp_r31->unk20 = 10 * (0.8f * (temp_f31 * sind(temp_f30)));
            temp_r31->unk24 = 10.0f * (5.0f * (1.0f - (temp_f31 * temp_f31)));
            temp_r31->unk28 = 10 * (0.8f * (temp_f31 * cosd(temp_f30)));
            temp_r31->unk08.x = temp_r31->unk20 + arg1->x;
            temp_r31->unk08.y = temp_r31->unk24 + temp_r31->unk34.y;
            temp_r31->unk08.z = temp_r31->unk28 + arg1->z;
            temp_r31->unk14.x = (6.0f + (0.012f * frandmod(1000)));
            temp_r31->unk2C = 2.0f;
            temp_r31->unk14.y = temp_r31->unk40.a = 10;
            temp_r31->unk14.z = frandmod(100) + 64;
            temp_f31 = 0.00040000002f * frandmod(1000);
            temp_f31 += 0.6f * cosd(temp_f30);
            temp_r31->unk40.r = (55 * temp_f31) + 200;
            temp_r31->unk40.g = (50 * temp_f31) + 205;
            temp_r31->unk40.b = (5 * temp_f31) + 250;
            if (--arg2 == 0) {
                break;
            }
        }
    }
}

typedef struct work_61FC {
    s32 unk0;
    s32 unk4;
    u32 unk8;
    float unkC[2];
    s32 unk14;
    s32 unk18;
    s32 unk1C[7];
    float unk38[7];
    s16 unk54[7];
} Work61FC;

void fn_1_6540(omObjData *object);

void fn_1_61FC(omObjData *object)
{
    Work61FC *temp_r31;
    s32 temp_r30;
    s32 temp_r28;
    s32 temp_r26;

    Work61FC *temp_r27;

    float sp8[][2] = { 96, 64, 486, 64, 96, 416, 486, 416 };
    float sp28[][2] = { 0, 0, 0, 0, -54, -1, 2, 1, -20, 0, 42, 2, 22, 2 };

    object->stat |= 0x100;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 4 * sizeof(Work61FC), MEMORY_DEFAULT_NUM);
    temp_r27 = object->data;
    memset(temp_r27, 0, 4 * sizeof(Work61FC));
    temp_r31 = temp_r27;
    for (temp_r28 = 0; temp_r28 < 4; temp_r28++, temp_r31++) {
        for (temp_r30 = 0; temp_r30 < 7; temp_r30++) {
            temp_r31->unk54[temp_r30] = -1;
            temp_r31->unk38[temp_r30] = 1;
        }
        temp_r31->unkC[0] = sp8[temp_r28][0];
        temp_r31->unkC[1] = sp8[temp_r28][1];
        temp_r26 = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x29), 4, 0);
        temp_r31->unk54[0] = temp_r26;
        espColorSet(temp_r26, 0, 0, 0);
        espTPLvlSet(temp_r26, 0.5);
        temp_r31->unk54[1] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x28), 3, 0);
        temp_r31->unk54[2] = espEntry(lbl_1_data_0[GWPlayerCfg[temp_r28].character], 2, 0);
        temp_r31->unk54[3] = espEntry(DATA_MAKE_NUM(DATADIR_M408, 0x2B), 2, 0);
        temp_r31->unk54[4] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x08), 2, 0);
        temp_r31->unk54[6] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x33), 2, 0);
        temp_r31->unk54[5] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x33), 2, 0);
        for (temp_r30 = 0; temp_r30 < 7; temp_r30++) {
            if (temp_r31->unk54[temp_r30] >= 0) {
                espPosSet(temp_r31->unk54[temp_r30], temp_r31->unkC[0] + sp28[temp_r30][0], temp_r31->unkC[1] + sp28[temp_r30][1]);
                espDispOff(temp_r31->unk54[temp_r30]);
            }
        }
        temp_r31->unk0 = 0;
    }
    HuDataDirClose(DATADIR_MGCONST);
    object->func = fn_1_6540;
    (void)temp_r27;
    (void)temp_r27;
}

void fn_1_6540(omObjData *object)
{
    float temp_f31;
    Work61FC *temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    Work61FC *temp_r28 = object->data;
    temp_r31 = temp_r28;
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++, temp_r31++) {
        switch (temp_r31->unk14) {
            case 0:
                if (fn_1_6878() == 3) {
                    temp_r31->unk14 = 1;
                }
                break;

            case 1:
                temp_r31->unk18 = 0;
                temp_r31->unk1C[5] = temp_r31->unk8 % 10;
                temp_r31->unk1C[6] = (temp_r31->unk8 / 10) % 10;
                for (temp_r30 = 0; temp_r30 < 7; temp_r30++) {
                    if (temp_r31->unk54[temp_r30] >= 0) {
                        espDispOn(temp_r31->unk54[temp_r30]);
                    }
                }
                if (temp_r31->unk0) {
                    temp_r31->unk38[5] = temp_r31->unk38[6] = 0.5f;
                    temp_r31->unk14++;
                }
                else {
                    temp_r31->unk0 = 1;
                    temp_r31->unk38[5] = temp_r31->unk38[6] = 1.0f;
                    temp_r31->unk14 += 3;
                    break;
                }

            case 2:
                temp_f31 = temp_r31->unk38[5];
                temp_f31 += 0.10000001f;
                if (temp_f31 >= 1.5f) {
                    temp_r31->unk14++;
                }
                temp_r31->unk38[5] = temp_r31->unk38[6] = temp_f31;
                break;

            case 3:
                temp_f31 = temp_r31->unk38[5];
                temp_f31 -= 0.10000001f;
                if (temp_f31 <= 1.0f) {
                    temp_f31 = 1.0f;
                    temp_r31->unk14++;
                }
                temp_r31->unk38[5] = temp_r31->unk38[6] = temp_f31;
                break;

            default:
                break;
        }
        temp_r31->unk18++;
        for (temp_r30 = 0; temp_r30 < 7; temp_r30++) {
            espBankSet(temp_r31->unk54[temp_r30], temp_r31->unk1C[temp_r30]);
            espScaleSet(temp_r31->unk54[temp_r30], temp_r31->unk38[temp_r30], temp_r31->unk38[temp_r30]);
        }
    }
}

void fn_1_67C4(u16 arg0, u16 arg1)
{
    Work61FC *temp_r31;
    temp_r31 = lbl_1_bss_8->data;
    if (fn_1_6878() == 3) {
        temp_r31[arg0].unk4 += arg1;
        temp_r31[arg0].unk8 += arg1;
        temp_r31[arg0].unk14 = 1;
    }
}

u32 fn_1_6868(void)
{
    return lbl_1_bss_62;
}

u32 fn_1_6878(void)
{
    return lbl_1_bss_60;
}

float fn_1_6888(void)
{
    return lbl_1_bss_54;
}

void fn_1_6898(void) { }

s32 fn_1_689C(void)
{
    return 0;
}

void fn_1_68A4(void) { }

Work2FAC *fn_1_68A8(s32 arg0)
{
    return lbl_1_bss_6C[arg0]->data;
}

float fn_1_68C4(float arg8, float arg9, float argA, float argB, float argC, float argD, float argE, float argF, float arg2, float arg3)
{
    float temp_f30;
    float sp14;
    float temp_f29;
    float temp_f28;

    float temp_f27;
    float temp_f26;

    float sp10;

    sp14 = (argC + arg3) * (argC + arg3);
    temp_f27 = (arg2 * arg2) + (((argB * argB) + ((argF * argF) + ((argA * argA) - (2.0f * argA * argF)))) - (2.0f * argB * arg2));
    temp_f26 = 2.0f
        * ((argE * arg2) + ((((arg9 * argB) + ((argD * argF) + (((arg8 * argA) - (arg8 * argF)) - (argD * argA)))) - (arg9 * arg2)) - (argE * argB)));
    sp10 = ((argE * argE) + (((arg9 * arg9) + ((argD * argD) + ((arg8 * arg8) - (2.0f * arg8 * argD)))) - (2.0f * arg9 * argE))) - sp14;
    if (0.0f == temp_f27) {
        return -1;
    }
    temp_f30 = (temp_f26 * temp_f26) - (4.0f * temp_f27 * sp10);
    if (temp_f30 <= 0.0) {
        return -1;
    }
    temp_f30 = sqrtf(temp_f30);
    temp_f29 = (-temp_f26 + temp_f30) / (2.0f * temp_f27);
    temp_f28 = (-temp_f26 - temp_f30) / (2.0f * temp_f27);
    if (temp_f29 >= 0.0f && temp_f28 >= 0.0f) {
        if (temp_f29 < temp_f28) {
            if (temp_f29 < 1.0f) {
                return temp_f29;
            }
        }
        if (temp_f28 < 1.0f) {
            return temp_f28;
        }
    }
    return -1;
}

void fn_1_6C28(float *arg0, float arg1, float arg2, float arg3, float arg4, float arg5, float arg6)
{
    float temp_f24;
    float temp_f29;
    float temp_f28;
    float temp_f31;
    float temp_f30;

    float temp_f25;

    temp_f29 = arg3;
    temp_f28 = arg4;
    temp_f24 = sqrtf((temp_f29 * temp_f29) + (temp_f28 * temp_f28));
    if (temp_f24 != 0.0) {
        temp_f25 = 1.0f / temp_f24;
        temp_f29 *= temp_f25;
        temp_f28 *= temp_f25;
    }
    temp_f31 = arg5 - arg1;
    temp_f30 = arg6 - arg2;
    temp_f25 = 1.0f / sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
    temp_f31 *= temp_f25;
    temp_f30 *= temp_f25;
    temp_f25 = (temp_f29 * temp_f31) + (temp_f28 * temp_f30);
    arg0[0] = temp_f25 * (temp_f31 * temp_f24);
    arg0[1] = temp_f25 * (temp_f30 * temp_f24);
}

void fn_1_6F4C(float arg8, float arg9, float argA, float argB, float argC, float argD, float argE, float argF, float *arg0, float *arg1, float *arg2,
    float *arg3)
{
    float sp70[2];
    float sp68[2];
    float sp64;
    float sp60;
    sp64 = arg8 + (0.5f * (argC - arg8));
    sp60 = arg9 + (0.5f * (argD - arg9));
    fn_1_6C28(sp70, arg8, arg9, argA, argB, sp64, sp60);
    fn_1_6C28(sp68, argC, argD, argE, argF, sp64, sp60);
    *arg0 = sp68[0] - sp70[0];
    *arg1 = sp68[1] - sp70[1];
    *arg2 = sp70[0] - sp68[0];
    *arg3 = sp70[1] - sp68[1];
}

void fn_1_75B8(float *arg0, float *arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7)
{
    float temp_f26 = arg2 + (0.5f * (arg6 - arg2));
    float temp_f25 = arg3 + (0.5f * (arg7 - arg3));
    float temp_f31 = arg2 - temp_f26;
    float temp_f30 = arg3 - temp_f25;
    float temp_f28;
    if (temp_f31 == 0.0f || temp_f30 == 0.0f) {
        *arg0 = *arg1 = 0.0f;
        return;
    }
    temp_f28 = 1.0f / sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
    temp_f31 *= temp_f28;
    temp_f30 *= temp_f28;
    *arg0 = (2.0f * temp_f31) * ((-arg4 * temp_f31) - (arg5 * temp_f30));
    *arg1 = (2.0f * temp_f30) * ((-arg4 * temp_f31) - (arg5 * temp_f30));
}

void fn_1_7818(omObjData *arg0, omObjData *arg1)
{
    Work2FAC *temp_r31 = arg0->data;
    Work2FAC *temp_r30 = arg1->data;

    float sp14;
    float sp10;
    float spC;
    float sp8;
    fn_1_6F4C(temp_r31->unk1C.x, temp_r31->unk1C.z, temp_r31->unk34.x, temp_r31->unk34.z, temp_r30->unk1C.x, temp_r30->unk1C.z, temp_r30->unk34.x,
        temp_r30->unk34.z, &sp14, &sp10, &spC, &sp8);
    temp_r31->unk34.x += sp14;
    temp_r31->unk34.z += sp10;
    temp_r30->unk34.x += spC;
    temp_r30->unk34.z += sp8;
}

s32 fn_1_78D8(void)
{
    float temp_f29;
    float temp_f18;

    Work2FAC *temp_r31;
    s32 temp_r30;
    Work2FAC *temp_r29;
    Work2FAC *temp_r28;
    s32 temp_r27;
    s32 temp_r26;
    omObjData *temp_r25;
    omObjData *temp_r24;
    omObjData *temp_r23;

    omObjData *sp30[2];
    temp_r26 = -1;
    temp_f18 = 0;
    temp_f29 = 9999;
    for (temp_r27 = 0; temp_r27 < 3; temp_r27++) {
        temp_r25 = lbl_1_bss_6C[temp_r27];
        temp_r29 = temp_r25->data;
        if (temp_r29->unk4 & 0x10) {
            continue;
        }
        for (temp_r30 = temp_r27 + 1; temp_r30 < 4; temp_r30++) {
            temp_r24 = lbl_1_bss_6C[temp_r30];
            temp_r28 = temp_r24->data;
            if (temp_r28->unk4 & 0x10) {
                continue;
            }
            temp_f18
                = fn_1_68C4(temp_r29->unk1C.x, temp_r29->unk1C.z, temp_r29->unk34.x * lbl_1_bss_4, temp_r29->unk34.z * lbl_1_bss_4, temp_r29->unk58.z,
                    temp_r28->unk1C.x, temp_r28->unk1C.z, temp_r28->unk34.x * lbl_1_bss_4, temp_r28->unk34.z * lbl_1_bss_4, temp_r28->unk58.z);
            if (temp_f18 >= 0.0 && temp_f18 <= temp_f29) {
                temp_f29 = temp_f18;
                temp_r26 = 1;
                sp30[0] = temp_r25;
                sp30[1] = temp_r24;
            }
        }
    }
    if (temp_r26 < 0) {
        return 0;
    }
    if (temp_f29 > 0.0f) {
        for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
            temp_r31 = lbl_1_bss_6C[temp_r30]->data;
            temp_r31->unk64 = 0;
        }
    }
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        temp_r23 = lbl_1_bss_6C[temp_r30];
        temp_r31 = temp_r23->data;
        if (!(temp_r31->unk4 & 0x10)) {
            temp_r31->unk1C.x += lbl_1_bss_4 * (temp_r31->unk34.x * temp_f29);
            temp_r31->unk1C.z += lbl_1_bss_4 * (temp_r31->unk34.z * temp_f29);
        }
    }
    if (temp_r26 != 1) {
        (void)temp_r26;
    }
    else {
        fn_1_7818(sp30[0], sp30[1]);
        for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
            temp_r31 = sp30[temp_r30]->data;
            if (temp_r31->unk4 & 0x10) {
                continue;
            }
            temp_r31->unk64++;
            if (temp_r31->unk18 == 0) {
                lbl_1_bss_0 = 1;
            }
            temp_r31->unk18 = 18;
            if (temp_r31->unk64 > 2.0f) {
                temp_r31->unk34.x = temp_r31->unk34.z = 0;
            }
        }
    }
    lbl_1_bss_4 *= (1.0f - temp_f29);
    return 1;
}

void fn_1_8020(void)
{
    Work2FAC *temp_r31;
    s32 temp_r30;
    omObjData *temp_r29;
    lbl_1_bss_4 = 1.0f;
    lbl_1_bss_0 = 0;
    while (fn_1_78D8())
        ;
    if (lbl_1_bss_0) {
        HuAudFXPlay(1359);
    }
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        temp_r29 = lbl_1_bss_6C[temp_r30];
        temp_r31 = temp_r29->data;
        if (temp_r31->unk18 != 0) {
            temp_r31->unk18--;
        }
        if (temp_r31->unk4 & 0x10) {
            continue;
        }
        temp_r31->unk1C.x += temp_r31->unk34.x * lbl_1_bss_4;
        temp_r31->unk1C.z += temp_r31->unk34.z * lbl_1_bss_4;
        temp_r31->unk28.x = temp_r31->unk34.x * 60.0f;
        temp_r31->unk28.z = temp_r31->unk34.z * 60.0f;
        temp_r31->unk34.x = temp_r31->unk34.z = 0;
    }
}

void fn_1_817C(Vec *arg0, Vec *arg1)
{
    Vec sp10;
    sp10.x = arg1->x - arg0->x;
    sp10.y = arg1->y - arg0->y;
    sp10.z = arg1->z - arg0->z;
    Center.x = arg1->x;
    Center.y = arg1->y;
    Center.z = arg1->z;
    CRot.x = atan2d(sp10.y, VECMagXZ(&sp10));
    CRot.y = atan2d(-sp10.x, -sp10.z);
    CRot.z = 0;
    CZoom = sqrtf(VECMag2Point(&sp10));
}

void fn_1_84C4(float arg0, float arg1, float arg2, float arg3, float arg4, float arg5)
{
    Vec sp40;
    Vec sp34;
    sp40.x = arg0;
    sp40.y = arg1;
    sp40.z = arg2;
    sp34.x = arg3;
    sp34.y = arg4;
    sp34.z = arg5;
    fn_1_817C(&sp40, &sp34);
}

float fn_1_883C(float arg0, float arg1, float arg2)
{
    float temp_f31;
    temp_f31 = fmodf(arg1 - arg0, 360);
    if (temp_f31 < 0.0f) {
        temp_f31 += 360.0f;
    }
    if (temp_f31 > 180.0f) {
        temp_f31 -= 360.0f;
    }
    temp_f31 = fmodf((arg2 * temp_f31) + arg0, 360);
    if (temp_f31 < 0.0f) {
        temp_f31 += 360.0f;
    }
    return temp_f31;
}
