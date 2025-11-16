#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/msm.h"

#include "game/audio.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/wipe.h"

#include "game/gamework_data.h"
#include "game/minigame_seq.h"
#include "game/sprite.h"

#include "ext_math.h"

#include "REL/m431Dll.h"
#include "version.h"

typedef struct bss_5C_struct {
    s16 unk0[6];
    s16 unkC[2];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    float unk18;
    float unk1C;
    float unk20;
    float unk24;
    float unk28[2];
    float unk30;
    float unk34;
} Bss5CStruct;

typedef struct camera_view_params {
    float zoom;
    Vec pos;
    Vec rot;
} CameraViewParams;

Bss5CStruct lbl_1_bss_5C;
s16 lbl_1_bss_34[20];
omObjData *lbl_1_bss_30;
omObjData *lbl_1_bss_2C;
s16 lbl_1_bss_28;
float lbl_1_bss_20[2];
float lbl_1_bss_18[2];
s16 lbl_1_bss_14;
s8 lbl_1_bss_12;
s16 lbl_1_bss_10;
s8 lbl_1_bss_E;
s16 lbl_1_bss_C;
s16 lbl_1_bss_A;
s16 lbl_1_bss_8;
s32 lbl_1_bss_4;
s8 lbl_1_bss_0;

Vec lbl_1_data_0 = { 800, 1300, 1000 };
Vec lbl_1_data_C = { 0, 0, 0 };
GXColor lbl_1_data_18 = { 255, 255, 255, 255 };
Vec lbl_1_data_1C = { 10, 45, 0 };
Vec lbl_1_data_28 = { 1300, 2500, 1300 };
Vec lbl_1_data_34 = { 0, 1, 0 };
Vec lbl_1_data_40 = { 0, 0, -1200 };

CameraViewParams lbl_1_data_4C[4] = { { 760, { -324, -97, 0 }, { -43, 0, 0 } }, { 800, { 325, -64, 0 }, { -43, -20, 0 } },
    { 1460, { 0, 57, 0 }, { -37, 0, 0 } }, { 880, { -381, 25, 0 }, { -14, 10, 0 } } };

s32 lbl_1_data_BC[3] = { -32, -2, 28 };

s32 lbl_1_data_C8[2] = { 90, 486 };

void fn_1_424(omObjData *object);
void fn_1_A44(omObjData *object);
void fn_1_2110(omObjData *object);

void ObjectSetup(void)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Process *temp_r31;
    LightData *temp_r30;
    CameraData *temp_r29;

    Hu3DLightAllKill();
    lbl_1_bss_28 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_18);
    Hu3DGLightInfinitytSet(lbl_1_bss_28);
    temp_r30 = &Hu3DGlobalLight[lbl_1_bss_28];
    temp_r30->unk_00 |= 0x8000;
    sp2C.x = sp2C.y = sp2C.z = 0;
    Hu3DGLightPosAimSetV(lbl_1_bss_28, &lbl_1_data_0, &sp2C);
    Hu3DShadowCreate(45, 20, 10000);
    Hu3DShadowTPLvlSet(0.425f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    temp_r31 = omInitObjMan(50, 8192);
    omGameSysInit(temp_r31);
    HuAudSndGrpSet(56);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 41.5, 5, 5000, 1.2f);
    omAddObjEx(temp_r31, 32730, 0, 0, -1, omOutView);
    temp_r29 = &Hu3DCamera[0];
    temp_r29->fov = -1;
    sp14.x = 0;
    sp14.y = 374;
    sp14.z = 1086;
    sp20.x = 0;
    sp20.y = 568;
    sp20.z = -1316;
    sp8.z = sp20.x - sp14.x;
    sp8.y = sp20.y - sp14.y;
    sp8.x = sp20.z - sp14.z;
    CRot.x = lbl_1_data_4C[0].rot.x;
    CRot.y = lbl_1_data_4C[0].rot.y;
    CRot.z = lbl_1_data_4C[0].rot.z;
    Center.x = lbl_1_data_4C[0].pos.x;
    Center.y = lbl_1_data_4C[0].pos.y;
    Center.z = lbl_1_data_4C[0].pos.z;
    CZoom = lbl_1_data_4C[0].zoom;
    omAddObjEx(temp_r31, 1000, 0, 0, -1, fn_1_424);
    lbl_1_bss_30 = omAddObjEx(temp_r31, 10, 9, 0, -1, fn_1_A44);
    lbl_1_bss_2C = omAddObjEx(temp_r31, 50, 9, 9, -1, fn_1_2110);
    Hu3DBGColorSet(0, 0, 0);
    fn_1_7ABC(temp_r31);
}

void fn_1_49C(omObjData *object);

void fn_1_424(omObjData *object)
{
    if (omSysExitReq || lbl_1_bss_0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        HuAudSeqAllFadeOut(100);
        object->func = fn_1_49C;
    }
}

void fn_1_71B8(s16 arg0);

void fn_1_49C(omObjData *object)
{
    s16 i;
    if (WipeStatGet()) {
        return;
    }
    fn_1_71B8(lbl_1_bss_30->model[0]);
    for (i = 0; i < 6; i++) {
        fn_1_71B8(lbl_1_bss_5C.unk0[i]);
    }
    HuSprGrpKill(lbl_1_bss_30->model[1]);
    HuSprGrpKill(lbl_1_bss_30->model[2]);
    HuSprGrpKill(lbl_1_bss_30->model[3]);
    MGSeqKillAll();
    HuAudFadeOut(1);
    omOvlReturnEx(1, 1);
}

float fn_1_65CC(float arg0, float arg1, float arg2);

u8 fn_1_57C(void)
{
    float temp_f31;
    float temp_f30;
    CameraViewParams *temp_r31;
    s32 temp_r30;
    temp_r31 = &lbl_1_data_4C[0];
    temp_r30 = 0;
    lbl_1_bss_8++;
    temp_f30 = lbl_1_bss_8 / (1.5f * REFRESH_RATE);
    if (lbl_1_bss_8 > (s32)(1.5f * REFRESH_RATE)) {
        lbl_1_bss_8 = 0;
        temp_f30 = 1;
        temp_r30 = 1;
    }
    temp_f31 = sind(90 * temp_f30) * sind(90 * temp_f30);
    CZoom = fn_1_65CC(temp_r31[0].zoom, temp_r31[2].zoom, temp_f31);
    Center.x = fn_1_65CC(temp_r31[0].pos.x, temp_r31[2].pos.x, temp_f31);
    Center.y = fn_1_65CC(temp_r31[0].pos.y, temp_r31[2].pos.y, temp_f31);
    Center.z = fn_1_65CC(temp_r31[0].pos.z, temp_r31[2].pos.z, temp_f31);
    CRot.x = fn_1_65CC(temp_r31[0].rot.x, temp_r31[2].rot.x, temp_f31);
    CRot.y = fn_1_65CC(temp_r31[0].rot.y, temp_r31[2].rot.y, temp_f31);
    CRot.z = fn_1_65CC(temp_r31[0].rot.z, temp_r31[2].rot.z, temp_f31);
    return temp_r30;
}

typedef struct work_a44 {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6[2];
    s16 unkA;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} WorkA44;

s32 fn_1_7B0(void)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    CameraViewParams *temp_r31;
    WorkA44 *temp_r30;
    s32 temp_r29;
    temp_r30 = lbl_1_bss_30->data;
    temp_r31 = &lbl_1_data_4C[0];
    temp_r29 = 0;
    lbl_1_bss_8++;
    temp_f30 = lbl_1_bss_8 / (2.0f * REFRESH_RATE);
    if (lbl_1_bss_8 > (2 * REFRESH_RATE)) {
        lbl_1_bss_8 = 2 * REFRESH_RATE;
        temp_f30 = 1;
        temp_r29 = 1;
    }
    temp_f31 = sind(90 * temp_f30) * sind(90 * temp_f30);
    if (temp_r30->unk4 == 0) {
        temp_f29 = temp_r31[3].pos.x;
        temp_f28 = temp_r31[3].rot.y;
    }
    else {
        temp_f29 = -temp_r31[3].pos.x;
        temp_f28 = -temp_r31[3].rot.y;
    }
    CZoom = fn_1_65CC(temp_r31[2].zoom, temp_r31[3].zoom, temp_f31);
    Center.x = fn_1_65CC(temp_r31[2].pos.x, temp_f29, temp_f31);
    Center.y = fn_1_65CC(temp_r31[2].pos.y, temp_r31[3].pos.y, temp_f31);
    Center.z = fn_1_65CC(temp_r31[2].pos.z, temp_r31[3].pos.z, temp_f31);
    CRot.x = fn_1_65CC(temp_r31[2].rot.x, temp_r31[3].rot.x, temp_f31);
    CRot.y = fn_1_65CC(temp_r31[2].rot.y, temp_f28, temp_f31);
    CRot.z = fn_1_65CC(temp_r31[2].rot.z, temp_r31[3].rot.z, temp_f31);
    return temp_r29;
}

void fn_1_6030(ModelData *arg0, Work72B4 *arg1, Mtx arg2);
s16 fn_1_6C74(AnimData *arg0, s16 arg1, float arg2, s16 arg3, s16 arg4);
void fn_1_7244(s16 arg0, unkHook72B4 arg1);

void fn_1_10A4(omObjData *object);

void fn_1_A44(omObjData *object)
{
    float temp_f31;

    s16 temp_r31;
    s16 temp_r30;
    s16 temp_r28;

    AnimData *temp_r27;
    WorkA44 *temp_r26;
    s16 temp_r25;

    AnimData *temp_r24;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkA44), MEMORY_DEFAULT_NUM);
    temp_r26 = object->data;
    temp_r26->unk0 = 4;
    temp_r26->unk6[0] = 0;
    temp_r26->unkA = 15 * REFRESH_RATE;
    temp_r26->unk10 = -1;
    temp_r27 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M431, 0x1A), MEMORY_DEFAULT_NUM));
    object->model[0] = fn_1_6C74(temp_r27, 1024, 25, 64, 64);
    fn_1_7244(object->model[0], fn_1_6030);
    Hu3DModelLayerSet(object->model[0], 7);
    temp_r30 = HuSprGrpCreate(4);
    object->model[3] = temp_r30;
    temp_r27 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x1B), MEMORY_DEFAULT_NUM));
    temp_r28 = HuSprCreate(temp_r27, 16, 0);
    HuSprGrpMemberSet(temp_r30, 0, temp_r28);
    HuSprAttrSet(temp_r30, 0, HUSPR_ATTR_DISPOFF);
    temp_r27 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x1D), MEMORY_DEFAULT_NUM));
    temp_r28 = HuSprCreate(temp_r27, 32, 0);
    HuSprGrpMemberSet(temp_r30, 2, temp_r28);
    HuSprAttrSet(temp_r30, 2, HUSPR_ATTR_DISPOFF);
    temp_r27 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x1C), MEMORY_DEFAULT_NUM));
    temp_r28 = HuSprCreate(temp_r27, 16, 0);
    HuSprGrpMemberSet(temp_r30, 1, temp_r28);
    HuSprAttrSet(temp_r30, 1, HUSPR_ATTR_DISPOFF);
    temp_r27 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x1D), MEMORY_DEFAULT_NUM));
    temp_r28 = HuSprCreate(temp_r27, 32, 0);
    HuSprGrpMemberSet(temp_r30, 3, temp_r28);
    HuSprAttrSet(temp_r30, 3, HUSPR_ATTR_DISPOFF);
    temp_f31 = 288;
    HuSprPosSet(temp_r30, 0, temp_f31 - 198, 64);
    HuSprPosSet(temp_r30, 1, temp_f31 + 198, 64);
    HuSprPosSet(temp_r30, 2, temp_f31 - 198, 64);
    HuSprTPLvlSet(temp_r30, 2, 88);
    HuSprColorSet(temp_r30, 2, 0, 0, 0);
    HuSprPosSet(temp_r30, 3, temp_f31 + 198, 64);
    HuSprTPLvlSet(temp_r30, 3, 88);
    HuSprColorSet(temp_r30, 3, 0, 0, 0);
    temp_r27 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x0B), MEMORY_DEFAULT_NUM));
    temp_r24 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x0A), MEMORY_DEFAULT_NUM));
    temp_r30 = HuSprGrpCreate(6);
    object->model[1] = temp_r30;
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        temp_r28 = HuSprCreate(temp_r27, 0, 0);
        HuSprGrpMemberSet(temp_r30, temp_r31, temp_r28);
        HuSprPosSet(temp_r30, temp_r31, lbl_1_data_C8[0] + lbl_1_data_BC[temp_r31], 63);
        HuSprAttrSet(temp_r30, temp_r31, HUSPR_ATTR_DISPOFF);
    }
    for (temp_r31 = 3; temp_r31 < 6; temp_r31++) {
        temp_r25 = temp_r31 - 3;
        temp_r28 = HuSprCreate(temp_r24, 8, 0);
        HuSprGrpMemberSet(temp_r30, temp_r31, temp_r28);
        HuSprPosSet(temp_r30, temp_r31, lbl_1_data_C8[0] + lbl_1_data_BC[temp_r25], 63);
        HuSprAttrSet(temp_r30, temp_r31, HUSPR_ATTR_DISPOFF);
    }
    temp_r30 = HuSprGrpCreate(6);
    object->model[2] = temp_r30;
    for (temp_r31 = 0; temp_r31 < 3; temp_r31++) {
        temp_r28 = HuSprCreate(temp_r27, 0, 0);
        HuSprGrpMemberSet(temp_r30, temp_r31, temp_r28);
        HuSprPosSet(temp_r30, temp_r31, lbl_1_data_C8[1] + lbl_1_data_BC[temp_r31], 63);
        HuSprAttrSet(temp_r30, temp_r31, HUSPR_ATTR_DISPOFF);
    }
    for (temp_r31 = 3; temp_r31 < 6; temp_r31++) {
        temp_r25 = temp_r31 - 3;
        temp_r28 = HuSprCreate(temp_r24, 8, 0);
        HuSprGrpMemberSet(temp_r30, temp_r31, temp_r28);
        HuSprPosSet(temp_r30, temp_r31, lbl_1_data_C8[1] + lbl_1_data_BC[temp_r25], 63);
        HuSprAttrSet(temp_r30, temp_r31, HUSPR_ATTR_DISPOFF);
    }
    (void)temp_r31;
    (void)temp_r31;
    object->func = fn_1_10A4;
}

void fn_1_140C(omObjData *object);
u8 fn_1_1634(omObjData *object);
u8 fn_1_1A40(omObjData *object);

void fn_1_5480(void);

void fn_1_10A4(omObjData *object)
{
    WorkA44 *temp_r31;
    s16 temp_r30;
    s16 temp_r28;
    CameraData *temp_r27;
    temp_r31 = object->data;
    temp_r30 = 99;
    switch (fn_1_2090(28)) {
        case 4:
            if (lbl_1_bss_E == 0) {
                lbl_1_bss_E = 1;
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                temp_r27 = &Hu3DCamera[0];
                temp_r27->fov = 41.5f;
            }
            if (!WipeStatGet()) {
                fn_1_2050(28, 8);
                fn_1_2050(224, 32);
            }
            break;

        case 8:
            if (fn_1_1634(object)) {
                fn_1_2050(1, 0);
                fn_1_2050(28, 12);
            }
            break;

        case 12:
            if (temp_r31->unk10 != -1) {
                temp_r28 = (temp_r31->unkA + REFRESH_RATE - 1) / REFRESH_RATE;
                if (temp_r28 < 0) {
                    temp_r28 = 0;
                }
                MGSeqParamSet(temp_r31->unk10, 1, temp_r28);
            }
            fn_1_140C(object);
            if (fn_1_2090(224) == 128) {
                if (lbl_1_bss_12C[0].unk138[0] == 3) {
                    temp_r30 = 0;
                }
                else if (lbl_1_bss_12C[1].unk138[0] == 3) {
                    temp_r30 = 1;
                }
                else {
                    if (temp_r31->unk6[0] == 5) {
                        if (lbl_1_bss_12C[0].unk138[0] == lbl_1_bss_12C[1].unk138[0]) {
                            temp_r30 = -1;
                        }
                        else {
                            if (lbl_1_bss_12C[0].unk138[0] > lbl_1_bss_12C[1].unk138[0]) {
                                temp_r30 = 0;
                            }
                            else {
                                temp_r30 = 1;
                            }
                        }
                    }
                }
            }
            if (temp_r30 != 99) {
                if (fn_1_2090(1) == 0) {
                    temp_r31->unk2 = MGSeqFinishCreate();
                    HuAudSeqAllFadeOut(100);
                }
                fn_1_5480();
                fn_1_2000(temp_r30);
                fn_1_2050(1, 1);
                if (temp_r31->unk0 & 0x2) {
                    if (temp_r30 == -1) {
                        lbl_1_bss_A = 1;
                    }
                    fn_1_2050(28, 16);
                }
                if (temp_r30 != -1) {
                    fn_1_8474(temp_r30 ^ 1);
                }
                else {
                    fn_1_8474(0);
                    fn_1_8474(1);
                }
            }
            break;

        case 16:
            if (fn_1_1A40(object)) {
                fn_1_2050(28, 20);
            }
            break;

        case 20:
            if (++lbl_1_bss_C > (3.5f * REFRESH_RATE)) {
                lbl_1_bss_0 = 1;
            }
            break;
    }
}

void fn_1_140C(omObjData *object)
{
    float temp_f31;
    float temp_f30;
    WorkA44 *temp_r31 = object->data;
    if ((temp_r31->unk0 & 0x300) == 0) {
        return;
    }
    temp_r31->unk12++;
    temp_f31 = temp_r31->unk12 / (3.0f / 10 * REFRESH_RATE);
    if (temp_r31->unk12 > (3.0f / 10 * REFRESH_RATE)) {
        temp_r31->unk12 = 0;
        temp_f31 = 1.0f;
        temp_r31->unk12 = 0.3f * REFRESH_RATE;
        temp_r31->unk0 &= ~0x300;
    }
    temp_f30 = 1.0 - cosd(90.0f * temp_f31);

    temp_f31 = 1.0 + sind(180.0f * temp_f31);
    HuSprAttrReset(lbl_1_bss_30->model[temp_r31->unk6[1] + 1], temp_r31->unk16, HUSPR_ATTR_DISPOFF);
    HuSprScaleSet(lbl_1_bss_30->model[temp_r31->unk6[1] + 1], temp_r31->unk16, temp_f31, temp_f31);
    HuSprTPLvlSet(lbl_1_bss_30->model[temp_r31->unk6[1] + 1], temp_r31->unk16, temp_f30);
}

void fn_1_2AB0(s16 arg0);

u8 fn_1_1634(omObjData *object)
{
    WorkA44 *temp_r30 = object->data;
    s32 temp_r29;
    s32 temp_r27;
    s32 temp_r26;
    switch (lbl_1_bss_A) {
        case 0:
            if (fn_1_2090(224) == 64) {
                fn_1_2050(1, 1);
                lbl_1_bss_A++;
            }
            break;

        case 1:
            if (fn_1_57C()) {
                lbl_1_bss_A++;
            }
            break;

        case 2:
            temp_r30->unk2 = MGSeqStartCreate();
            temp_r30->unkC = -1;
            lbl_1_bss_A++;
            break;

        case 3:
            if (temp_r30->unk2 != -1) {
                temp_r26 = MGSeqStatGet(temp_r30->unk2);
                if ((temp_r26 & 0x10) && temp_r30->unkC == -1) {
                    temp_r30->unkC = HuAudSeqPlay(72);
                }
            }
            if (temp_r30->unk2 == -1 || temp_r26 == 0) {
                temp_r27 = object->model[1];
                for (temp_r29 = 3; temp_r29 < 6; temp_r29++) {
                    HuSprAttrReset(temp_r27, temp_r29, HUSPR_ATTR_DISPOFF);
                }
                temp_r27 = object->model[2];
                for (temp_r29 = 3; temp_r29 < 6; temp_r29++) {
                    HuSprAttrReset(temp_r27, temp_r29, HUSPR_ATTR_DISPOFF);
                }
                temp_r27 = object->model[3];
                for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                    HuSprAttrReset(temp_r27, temp_r29, HUSPR_ATTR_DISPOFF);
                }
                fn_1_2AB0(999);
                lbl_1_bss_A = 0;

                return 1;
            }
            break;
    }
    return 0;
}

u8 fn_1_1A40(omObjData *object)
{
    WorkA44 *temp_r30;
    Bss12CStruct *temp_r29;
    s32 temp_r28;
    s32 temp_r25;
    temp_r30 = object->data;
    switch (lbl_1_bss_A) {
        case 0:
            temp_r28 = fn_1_7FB8(temp_r30->unk4);
            fn_1_8474(temp_r30->unk4 ^ 1);
            temp_r28 &= fn_1_7B0();
            if ((u8)temp_r28) {
                lbl_1_bss_4 = 1;
                fn_1_A7D0(temp_r30->unk4);
                HuAudSStreamPlay(1);
                lbl_1_bss_C = 0;
                lbl_1_bss_A++;
            }
            break;

        case 1:
            if (temp_r30->unk4 == -1) {
                temp_r28 = fn_1_8474(0);
                temp_r25 = fn_1_8474(1);
                if ((u8)temp_r28 == 0 || (u8)temp_r25 == 0) {
                    return 0;
                }
                if (temp_r30->unk2 == -1 || !MGSeqStatGet(temp_r30->unk2)) {
                    temp_r30->unk2 = -1;
                    lbl_1_bss_4 = 1;
                    fn_1_A904(0);
                    fn_1_A904(1);
                    HuAudSStreamPlay(4);
                    lbl_1_bss_A++;
                }
            }
            else {
                if (++lbl_1_bss_C > 1) {
                    lbl_1_bss_A++;
                }
            }
            break;

        case 2:
            if (temp_r30->unk4 != -1) {
                temp_r29 = &lbl_1_bss_12C[temp_r30->unk4];
                temp_r30->unk2 = MGSeqWinCreate(GWPlayerCfg[temp_r29->unk0[0]].character, GWPlayerCfg[temp_r29->unk0[1]].character, -1, -1);
                GWPlayerCoinWinAdd(temp_r29->unk0[0], 10);
                GWPlayerCoinWinAdd(temp_r29->unk0[1], 10);
            }
            else {
                temp_r30->unk2 = MGSeqDrawCreate();
            }
            lbl_1_bss_A++;
            break;

        case 3:
            lbl_1_bss_A = lbl_1_bss_C = 0;
            return 1;

        default:
            break;
    }
    return 0;
}

void fn_1_2000(s16 arg0)
{
    WorkA44 *temp_r31 = lbl_1_bss_30->data;
    if (arg0 == -1 || temp_r31->unk6[1] == -1) {
        temp_r31->unk0 |= 0x2;
    }
    temp_r31->unk4 = arg0;
}

void fn_1_2050(u16 arg0, u16 arg1)
{
    WorkA44 *temp_r31 = lbl_1_bss_30->data;
    temp_r31->unk0 &= ~arg0;
    temp_r31->unk0 |= arg1;
}

u16 fn_1_2090(u16 arg0)
{
    WorkA44 *temp_r31 = lbl_1_bss_30->data;
    if (!temp_r31) {
        return 0;
    }
    return temp_r31->unk0 & arg0;
}

void fn_1_20D0(s16 arg0)
{
    WorkA44 *temp_r31 = lbl_1_bss_30->data;
    temp_r31->unk0 |= 0x100;
    temp_r31->unk12 = 0;
    temp_r31->unk16 = arg0;
}

s32 lbl_1_data_114[2][2] = {
    DATA_MAKE_NUM(DATADIR_M431, 0x01),
    DATA_MAKE_NUM(DATADIR_M431, 0x03),
    DATA_MAKE_NUM(DATADIR_M431, 0x05),
    DATA_MAKE_NUM(DATADIR_M431, 0x06),
};

s32 lbl_1_data_124[2][2] = {
    DATA_MAKE_NUM(DATADIR_M431, 0x07),
    DATA_MAKE_NUM(DATADIR_M431, 0x08),
    DATA_MAKE_NUM(DATADIR_M431, 0x09),
    DATA_MAKE_NUM(DATADIR_M431, 0x0A),
};

s32 lbl_1_data_134[5] = {
    DATA_MAKE_NUM(DATADIR_M431, 0x0C),
    DATA_MAKE_NUM(DATADIR_M431, 0x0D),
    DATA_MAKE_NUM(DATADIR_M431, 0x0E),
    DATA_MAKE_NUM(DATADIR_M431, 0x0F),
    DATA_MAKE_NUM(DATADIR_M431, 0x10),
};

s32 lbl_1_data_148[5] = {
    DATA_MAKE_NUM(DATADIR_M431, 0x1C),
    DATA_MAKE_NUM(DATADIR_M431, 0x1D),
    DATA_MAKE_NUM(DATADIR_M431, 0x1E),
    DATA_MAKE_NUM(DATADIR_M431, 0x1F),
    DATA_MAKE_NUM(DATADIR_M431, 0x20),
};

typedef struct unk2110_obj {
    u32 unk0;
    float unk4;
    float unk8;
    Vec unkC;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    float unk20;
} Unk2110Obj;

typedef struct work_2110 {
    float unk0;
    Unk2110Obj unk4[10];
    s16 unk16C[10];
} Work2110;

void fn_1_2AC0(omObjData *object);

void fn_1_48D0(Work2110 *arg0);
void fn_1_498C(s16 arg0, Work2110 *arg1);

void fn_1_2110(omObjData *object)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    s16 temp_r31;
    Unk2110Obj *temp_r29;
    Work2110 *temp_r28;
    s16 temp_r27;
    AnimData *temp_r26;
    s16 temp_r25;

    object->stat |= 0x100;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 2 * sizeof(Work2110), MEMORY_DEFAULT_NUM);
    temp_r28 = object->data;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M431, 0x00));
    Hu3DModelLayerSet(object->model[0], 0);
    Hu3DModelScaleSet(object->model[0], 1.2f, 1.2f, 1.2f);
    temp_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M431, 0x11));
    Hu3DModelAttrSet(temp_r31, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(temp_r31, 0);
    Hu3DMotionSpeedSet(temp_r31, 0.25f);
    temp_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M431, 0x12));
    Hu3DModelAttrSet(temp_r31, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(temp_r31, 0);
    Hu3DMotionSpeedSet(temp_r31, 0.25f);
    temp_r31 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M431, 0x13));
    object->model[5] = temp_r31;
    object->motion[0] = Hu3DJointMotionFile(temp_r31, DATA_MAKE_NUM(DATADIR_M431, 0x14));
    object->motion[1] = Hu3DJointMotionFile(temp_r31, DATA_MAKE_NUM(DATADIR_M431, 0x15));
    object->motion[2] = Hu3DJointMotionFile(temp_r31, DATA_MAKE_NUM(DATADIR_M431, 0x16));
    object->motion[3] = Hu3DJointMotionFile(temp_r31, DATA_MAKE_NUM(DATADIR_M431, 0x17));
    object->motion[4] = Hu3DJointMotionFile(temp_r31, DATA_MAKE_NUM(DATADIR_M431, 0x14));
    object->motion[5] = Hu3DJointMotionFile(temp_r31, DATA_MAKE_NUM(DATADIR_M431, 0x18));
    object->motion[6] = Hu3DJointMotionFile(temp_r31, DATA_MAKE_NUM(DATADIR_M431, 0x19));
    Hu3DModelPosSet(temp_r31, 0, 0, -230);
    Hu3DModelShadowSet(temp_r31);
    Hu3DModelAttrSet(temp_r31, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(temp_r31, object->motion[0]);
    for (temp_r31 = 0; temp_r31 < 2; temp_r31++, temp_r28++) {
        temp_r25 = Hu3DModelCreateFile(lbl_1_data_114[0][temp_r31]);
        temp_f30 = (temp_r31 == 0) ? -317.0f : 317.0f;
        temp_f31 = 0;
        temp_f29 = 100;
        Hu3DModelPosSet(temp_r25, temp_f30, temp_f31, temp_f29);
        object->model[temp_r31 + 1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M431, 0x02));
        temp_f30 = (temp_r31 == 0) ? -317.0f : 317.0f;
        temp_f31 = 0;
        temp_f29 = 100;
        Hu3DModelPosSet(object->model[temp_r31 + 1], temp_f30, temp_f31, temp_f29);
        Hu3DModelAttrSet(object->model[temp_r31 + 1], HU3D_MOTATTR_PAUSE);

        object->model[temp_r31 + 3] = Hu3DModelCreateFile(lbl_1_data_114[1][temp_r31]);
        temp_f31 = 45;
        Hu3DModelPosSet(object->model[temp_r31 + 3], temp_f30, temp_f31, temp_f29);
        Hu3DModelRotSet(object->model[temp_r31 + 3], 0, lbl_1_data_1D0, 0);
        for (temp_r27 = 0, temp_r29 = &temp_r28->unk4[0]; temp_r27 < 10; temp_r27++, temp_r29++) {
            if (fmod((float)temp_r27, 2)) {
                if (temp_r27 == 1) {
                    temp_r29->unk1E = Hu3DModelCreateFile(lbl_1_data_124[temp_r31][0]);
                }
                else {
                    temp_r29->unk1E = Hu3DModelLink(temp_r28->unk4[1].unk1E);
                }
            }
            else {
                if (temp_r27 == 0) {
                    temp_r29->unk1E = Hu3DModelCreateFile(lbl_1_data_124[temp_r31][1]);
                }
                else {
                    temp_r29->unk1E = Hu3DModelLink(temp_r28->unk4[0].unk1E);
                }
            }
            Hu3DModelPosSet(temp_r29->unk1E, 0, -500, 0);
            if (temp_r27 == 0) {
                temp_r29->unk1C = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M431, 0x0B));
            }
            else {
                temp_r29->unk1C = Hu3DModelLink(temp_r28->unk4[0].unk1C);
            }
            Hu3DData[temp_r29->unk1C].pos.y = 1000;
            Hu3DModelAttrSet(temp_r29->unk1C, HU3D_ATTR_DISPOFF);
            temp_r29->unk0 = 0;
            temp_r29->unk4 = lbl_1_data_1D0 + (36.0f * temp_r27);
        }
        temp_r28->unk0 = 0;
        fn_1_48D0(temp_r28);
        fn_1_498C(temp_r31, temp_r28);
    }
    for (temp_r31 = 0; temp_r31 < 20; temp_r31++) {
        if (temp_r31 < 5) {
            lbl_1_bss_34[temp_r31] = Hu3DModelCreateFile(lbl_1_data_134[temp_r31]);
        }
        else {
            temp_r27 = fmod((float)temp_r31, 5);
            lbl_1_bss_34[temp_r31] = Hu3DModelLink(lbl_1_bss_34[temp_r27]);
        }
        Hu3DModelPosSet(lbl_1_bss_34[temp_r31], 0, -500, 0);
    }
    Hu3DModelShadowMapObjSet(object->model[0], "field");
    Hu3DModelShadowMapSet(object->model[1]);
    Hu3DModelShadowMapSet(object->model[2]);
    temp_r26 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M431, 0x1B), MEMORY_DEFAULT_NUM));
    lbl_1_bss_5C.unk0[0] = fn_1_6C74(temp_r26, 1, 140, 0, 0);
    Hu3DModelLayerSet(lbl_1_bss_5C.unk0[0], 7);
    for (temp_r31 = 0; temp_r31 < 5; temp_r31++) {
        temp_r26 = HuSprAnimRead(HuDataReadNum(lbl_1_data_148[temp_r31], MEMORY_DEFAULT_NUM));
        lbl_1_bss_5C.unk0[temp_r31 + 1] = fn_1_6C74(temp_r26, 2, 45, 0, 0);
        Hu3DModelLayerSet(lbl_1_bss_5C.unk0[temp_r31 + 1], 7);
    }
    object->func = fn_1_2AC0;
}

void fn_1_2AB0(s16 arg0)
{
    lbl_1_bss_10 = arg0;
}

void fn_1_2C94(Work2110 *arg0);
void fn_1_30E0(Work2110 *arg0);
void fn_1_3540(Work2110 *arg0);
void fn_1_3D7C(Work2110 *arg0);
void fn_1_4028(Work2110 *arg0);
void fn_1_5708(void);

void fn_1_2AC0(omObjData *object)
{
    Work2110 *temp_r31 = object->data;
    if (!fn_1_2090(1)) {
        if (fn_1_2090(28) == 12 || fn_1_2090(28) == 8) {
            switch (fn_1_2090(224)) {
                case 32:
                    fn_1_2C94(temp_r31);
                    break;

                case 64:
                    fn_1_30E0(temp_r31);
                    break;

                case 96:
                    fn_1_3540(temp_r31);
                    break;

                case 128:
                    if (fn_1_2090(28) == 12) {
                        fn_1_3D7C(temp_r31);
                    }
                    break;

                case 0:
                    fn_1_4028(temp_r31);
                    break;
            }
            fn_1_498C(0, &temp_r31[0]);
            fn_1_498C(1, &temp_r31[1]);
        }
    }
    fn_1_5708();
}

u16 lbl_1_data_162 = 1;

void fn_1_4798(Work2110 *arg0);

void fn_1_2C94(Work2110 *arg0)
{
    float temp_f31;
    float temp_f30;
    Unk2110Obj *temp_r31;
    s16 temp_r29;
    s16 temp_r28;
    WorkA44 *temp_r26;
    temp_r26 = lbl_1_bss_30->data;

    switch (lbl_1_data_162) {
        case 0:
            if (lbl_1_bss_10 == 1) {
                HuAudFXPlay(1670);
            }
            lbl_1_bss_10++;
            temp_f31 = lbl_1_bss_10 / (1.0f * REFRESH_RATE);
            if (temp_f31 >= 1.0f) {
                temp_r26->unkA = 15 * REFRESH_RATE;
                lbl_1_bss_10 = 0;
                temp_f31 = 1;
                lbl_1_data_162++;
            }
            temp_f31 = cosd(temp_f31 * 90.0f);
            temp_f30 = -50 + (95 * temp_f31);
            break;

        case 1:
            temp_f30 = -50;
            fn_1_4798(arg0);
            lbl_1_data_162++;
            break;

        case 2:
            if (lbl_1_bss_10 == 1) {
                HuAudFXPlay(1663);
            }
            lbl_1_bss_10++;
            temp_f31 = lbl_1_bss_10 / (1.0f * REFRESH_RATE);
            if (temp_f31 >= 1.0f) {
                lbl_1_bss_10 = 0;
                temp_f31 = 1.0f;
                lbl_1_data_162++;
            }
            temp_f31 = sind(temp_f31 * 90.0f);
            temp_f30 = -50 + (95 * temp_f31);
            break;

        case 3:
            temp_f30 = 45;
            fn_1_2050(224, 64);
            lbl_1_data_162 = 0;
            break;
    }
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++, arg0++) {
        temp_r31 = &arg0->unk4[0];
        for (temp_r28 = 0; temp_r28 < 10; temp_r28++, temp_r31++) {
            if (lbl_1_data_162 || -50.0f != Hu3DData[temp_r31->unk1A].pos.y) {
                Hu3DModelPosSet(temp_r31->unk1A, temp_r31->unkC.x, temp_f30, temp_r31->unkC.z);
                Hu3DModelRotSet(temp_r31->unk1A, 0, temp_r31->unk8, 0);
                Hu3DModelPosSet(temp_r31->unk1E, temp_r31->unkC.x, temp_f30, temp_r31->unkC.z);
                Hu3DModelRotSet(temp_r31->unk1E, 0, temp_r31->unk8, 0);
            }
        }
    }
}

void fn_1_30E0(Work2110 *arg0)
{
    float temp_f31;
    s16 sp8[2];
    Unk2110Obj *temp_r31;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r25;
    u32 temp_r22;
    switch (lbl_1_data_162) {
        case 0:
            lbl_1_bss_10++;
            if (lbl_1_bss_10 > REFRESH_RATE) {
                lbl_1_bss_10 = 0;
                lbl_1_data_162++;
            }
            return;

        case 1:
            temp_r28 = arg0[0].unk16C[4];
            arg0[0].unk4[temp_r28].unk0 = 4;
            temp_r28 = arg0[1].unk16C[4];
            arg0[1].unk4[temp_r28].unk0 = 4;
            lbl_1_bss_10 = 999;
            lbl_1_data_162++;
            break;

        case 2:
            temp_r31 = &arg0[0].unk4[arg0[0].unk16C[5]];
            if ((temp_r31->unk0 & 0x1C) == 0x10) {
                lbl_1_bss_10 = 0;
                fn_1_2050(224, 96);
                lbl_1_data_162 = 0;
                return;
            }
            break;
    }
    temp_r25 = 0;
    sp8[0] = sp8[1] = ++lbl_1_bss_10;
    for (temp_r27 = 0; temp_r27 < 2; temp_r27++, arg0++) {
        for (temp_r29 = 4; temp_r29 > -6; temp_r29--) {
            temp_r28 = (temp_r29 < 0) ? arg0->unk16C[temp_r29 + 10] : arg0->unk16C[temp_r29];
            temp_r31 = &arg0[0].unk4[temp_r28];
            switch (temp_r22 = temp_r31->unk0 & 0x1C) {
                case 4:
                    if (sp8[temp_r27] > (REFRESH_RATE/4)) {
                        sp8[temp_r27] = 0;
                        temp_r25 = 1;
                        if (temp_r29 - 1 > -6) {
                            temp_r28 = ((temp_r29 - 1) < 0) ? arg0->unk16C[(temp_r29 - 1) + 10] : arg0->unk16C[(temp_r29 - 1)];
                            arg0[0].unk4[temp_r28].unk0 &= ~0x1C;
                            arg0[0].unk4[temp_r28].unk0 |= 0x4;
                        }
                        temp_r31->unk0 &= ~0x1C;
                        temp_r31->unk0 |= 8;
                        temp_r31->unk20 = 0;
                        Hu3DModelAttrReset(temp_r31->unk1C, HU3D_ATTR_DISPOFF);
                    }
                    break;

                case 8:
                case 12:
                    temp_f31 = Hu3DData[temp_r31->unk1C].pos.y;
                    temp_r31->unk20 -= 0.98f;
                    temp_f31 += temp_r31->unk20;
                    if (temp_f31 <= 50.0f) {
                        temp_f31 = 50.0f;
                        temp_r31->unk0 &= ~0x1C;
                        if (temp_r22 == 8) {
                            temp_r31->unk20 = 6.0f;
                            temp_r31->unk0 |= 12;
                            HuAudFXPlay(1664);
                        }
                        else {
                            temp_r31->unk20 = 0;
                            temp_r31->unk0 |= 16;
                        }
                    }
                    Hu3DModelPosSet(temp_r31->unk1C, temp_r31->unkC.x, temp_f31, temp_r31->unkC.z);
                    Hu3DModelRotSet(temp_r31->unk1C, 0, temp_r31->unk8, 0);
                    break;

                default:
                    break;
            }
        }
    }
    if (temp_r25) {
        lbl_1_bss_10 = 0;
    }
}

s32 lbl_1_data_164 = -1;
Vec lbl_1_data_168 = { -150, 150, 0 };
void fn_1_4D4C(void);
void fn_1_4E30(s16 arg0, Bss61CWork *arg1);
void fn_1_52D8(void);
void fn_1_566C(s16 arg0);
s32 fn_1_7A78(s32 arg0, s16 arg1);

void fn_1_3540(Work2110 *arg0)
{
    float sp8[2];
    float temp_f31;
    float temp_f30;
    Unk2110Obj *temp_r30;
    s16 temp_r29;
    Bss61CWork *temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    temp_r25 = 0;
    switch (lbl_1_data_162) {
        case 0:
            lbl_1_bss_20[0] = arg0[0].unk0;
            lbl_1_bss_20[1] = arg0[1].unk0;
            temp_r29 = rand16() % 11;
            temp_f31 = (temp_r29 < 5) ? 360.0f : 180.0f;
            temp_f31 += temp_r29 * 36.0f;
            lbl_1_bss_18[0] = lbl_1_bss_20[0] + temp_f31;
            lbl_1_bss_18[1] = lbl_1_bss_20[1] - temp_f31;
            lbl_1_bss_14 = (0.01f * temp_f31) * REFRESH_RATE;
            lbl_1_data_162++;
            lbl_1_data_164 = HuAudFXPlay(1665);
            break;

        case 1:
            if (lbl_1_bss_10 == lbl_1_bss_14) {
                arg0[0].unk0 = fmod(arg0[0].unk0, 360);
                arg0[1].unk0 = fmod(arg0[1].unk0, 360);
                if (arg0[0].unk0 < 0.0f) {
                    arg0[0].unk0 += 360.0f;
                }
                if (arg0[1].unk0 < 0.0f) {
                    arg0[1].unk0 += 360.0f;
                }
                fn_1_48D0(&arg0[0]);
                fn_1_48D0(&arg0[1]);
                lbl_1_data_162++;
                lbl_1_bss_10 = 0;
                temp_r25 = 1;
            }
            break;

        case 2:
            temp_r25 = 1;
            fn_1_4D4C();
            fn_1_52D8();
            fn_1_566C(1);
            for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                temp_r27 = lbl_1_bss_61C[temp_r29]->data;
                fn_1_4E30(temp_r27->unkA, temp_r27);
            }
            lbl_1_data_162 = 0;
            fn_1_2050(224, 0);
            break;
    }
    sp8[0] = lbl_1_data_1D0 + arg0[0].unk0;
    sp8[1] = lbl_1_data_1D0 + arg0[1].unk0;
    if (temp_r25 == 0) {
        lbl_1_bss_10++;
        temp_f31 = lbl_1_bss_10 / (float)lbl_1_bss_14;
        temp_f31 = sind(temp_f31 * 90.0f);
        if (lbl_1_bss_10 > lbl_1_bss_14 - 120) {
            temp_f30 = (lbl_1_bss_10 - (lbl_1_bss_14 - 120)) / 120.0f;
            if (temp_f30 < 0.0f) {
                temp_f30 = 0.0f;
            }
            else {
                if (temp_f30 > 1.0f) {
                    temp_f30 = 1.0f;
                }
            }
            if (lbl_1_data_164 != -1) {
                HuAudFXPitchSet(lbl_1_data_164, -8191.0f * temp_f30);
                fn_1_7A78(lbl_1_data_164, (1.0f - temp_f30) * 127);
            }
            if (lbl_1_bss_10 >= lbl_1_bss_14) {
                if (lbl_1_data_164 != -1) {
                    HuAudFXStop(lbl_1_data_164);
                    lbl_1_data_164 = -1;
                    HuAudFXPlay(1675);
                }
            }
        }
        if (lbl_1_bss_10 > lbl_1_bss_14) {
            lbl_1_bss_10 = lbl_1_bss_14;
            temp_f31 = 1;
        }
        arg0[0].unk0 = lbl_1_bss_20[0] + (temp_f31 * (lbl_1_bss_18[0] - lbl_1_bss_20[0]));
        arg0[1].unk0 = lbl_1_bss_20[1] + (temp_f31 * (lbl_1_bss_18[1] - lbl_1_bss_20[1]));
    }
    Hu3DData[lbl_1_bss_2C->model[3]].rot.y = sp8[0];
    Hu3DData[lbl_1_bss_2C->model[4]].rot.y = sp8[1];
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++, arg0++) {
        temp_r30 = &arg0->unk4[0];
        for (temp_r26 = 0; temp_r26 < 10; temp_r26++, temp_r30++) {
            float temp_f29 = temp_r30->unkC.x;
            float temp_f28 = temp_r30->unkC.z;
            Hu3DModelPosSet(temp_r30->unk1A, temp_f29, 45, temp_f28);
            Hu3DModelRotSet(temp_r30->unk1A, 0, temp_r30->unk8, 0);
            Hu3DModelPosSet(temp_r30->unk1E, temp_f29, 45, temp_f28);
            Hu3DModelRotSet(temp_r30->unk1E, 0, temp_r30->unk8, 0);
            Hu3DModelPosSet(temp_r30->unk1C, temp_f29, 50, temp_f28);
            Hu3DModelRotSet(temp_r30->unk1C, 0, temp_r30->unk8, 0);
        }
    }
}

void fn_1_3FD0(Unk72B4Data18 *arg0);

void fn_1_3D7C(Work2110 *arg0)
{
    Unk2110Obj *temp_r31;
    ModelData *temp_r30;
    s16 temp_r29;
    WorkA44 *temp_r28;
    s16 temp_r27;
    switch (lbl_1_data_162) {
        case 0:
            if (++lbl_1_bss_10 > REFRESH_RATE) {
                lbl_1_bss_10 = 0;
                lbl_1_data_162++;
            }
            break;

        case 1:
            for (temp_r29 = 0; temp_r29 < 2; temp_r29++, arg0++) {
                temp_r31 = &arg0->unk4[0];
                for (temp_r27 = 0; temp_r27 < 10; temp_r27++, temp_r31++) {
                    temp_r30 = &Hu3DData[temp_r31->unk1C];
                    temp_r31->unk0 &= ~0x1C;
                    if (!(temp_r31->unk0 & 0x1)) {
                        fn_1_5B70(temp_r30->pos.x, 20 + temp_r30->pos.y, temp_r30->pos.z, 20, fn_1_3FD0, temp_r31->unk1C);
                        if (temp_r29 == 0) {
                            HuAudFXPlay(1669);
                        }
                        else {
                            HuAudFXPlay(1674);
                        }
                    }
                    else {
                        temp_r30->pos.y = 1000;
                    }
                    temp_r31->unk0 &= ~0x3;
                    Hu3DModelScaleSet(temp_r31->unk1A, 1, 1, 1);
                }
            }
            lbl_1_data_162++;
            break;

        case 2:
            if (++lbl_1_bss_10 > REFRESH_RATE) {
                lbl_1_bss_10 = lbl_1_data_162 = 0;
                fn_1_2050(224, 32);
            }
            break;
    }
}

void fn_1_3FD0(Unk72B4Data18 *arg0)
{
    Hu3DData[arg0->unk2C].pos.y = 1000;
    Hu3DModelAttrSet(arg0->unk2C, HU3D_ATTR_DISPOFF);
}

void fn_1_4028(Work2110 *arg0)
{
    float temp_f31;
    float temp_f30;
    Unk2110Obj *temp_r31;
    WorkA44 *temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    Bss61CWork *temp_r24;
    temp_r30 = lbl_1_bss_30->data;
    temp_r27 = -1;
    switch (lbl_1_data_162) {
        case 0:
            temp_r30->unk10 = MGSeqTimerCreate(15);
            lbl_1_data_162++;
            break;

        case 1:
            if (lbl_1_bss_12C[0].unk134[0] && lbl_1_bss_12C[0].unk134[1]) {
                temp_r27 = 0;
            }
            if (lbl_1_bss_12C[1].unk134[0] && lbl_1_bss_12C[1].unk134[1]) {
                if (temp_r27 == 0) {
                    temp_r27 = (rand16() % 2) ? 0 : 1;
                }
                else {
                    temp_r27 = 1;
                }
            }
            temp_r30->unk6[1] = temp_r27;
            if (temp_r27 != -1) {
                fn_1_A7D0(temp_r30->unk6[1]);
                fn_1_20D0(lbl_1_bss_12C[temp_r27].unk138[0]);
                fn_1_5480();
                fn_1_566C(3);
                lbl_1_bss_12C[temp_r27].unk138[0]++;
                MGSeqParamSet(temp_r30->unk10, 2, -1);
                temp_r30->unk10 = -1;
                temp_r30->unk6[0]++;
                lbl_1_bss_10 = 0;
                lbl_1_data_162++;
            }
            else {
                if (--temp_r30->unkA < -1) {
                    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
                        temp_r24 = lbl_1_bss_61C[temp_r29]->data;
                        for (temp_r28 = 0; temp_r28 < 8; temp_r28++) {
                            temp_r24->unk5E[temp_r28] = -1;
                        }
                    }
                    fn_1_5480();
                    fn_1_566C(4);
                    temp_r30->unkA = 0;
                    MGSeqParamSet(temp_r30->unk10, 2, -1);

                    temp_r30->unk10 = -1;
                    temp_r30->unk6[0]++;
                    lbl_1_bss_10 = 0;
                    lbl_1_data_162++;
                }
            }
            if (temp_r30->unk6[0] >= 5) {
                if (lbl_1_bss_12C[0].unk138[0] == lbl_1_bss_12C[1].unk138[0]) {
                    HuAudFXPlay(11);
                }
            }
            break;

        case 2:
            if (++lbl_1_bss_10 > (1.5f * REFRESH_RATE)) {
                lbl_1_bss_10 = 0;
                lbl_1_data_162 = 1;
                fn_1_2050(224, 128);
            }
            break;
    }
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++, arg0++) {
        temp_r31 = &arg0->unk4[0];
        for (temp_r28 = 0; temp_r28 < 10; temp_r28++, temp_r31++) {
            if (!(temp_r31->unk0 & 0x1)) {
                continue;
            }
            if (temp_r31->unk0 & 0x2) {
                temp_r31->unk18++;
                temp_f31 = temp_r31->unk18 / (0.5f * REFRESH_RATE);
                if (temp_f31 >= 1.0f) {
                    temp_r31->unk20 -= 1.0f;
                    if (temp_r31->unk20 < 0.4f) {
                        temp_r31->unk20 = 0.4f;
                    }
                    temp_r31->unk18 = 0;
                    temp_f31 = 1.0f;
                }
                temp_f31 = (temp_r31->unk20 * 0.7f) * sind(180.0f * temp_f31) + 1.0f;
                Hu3DModelScaleSet(temp_r31->unk1A, temp_f31, temp_f31, temp_f31);
            }
            else {
                if (!temp_r31->unk20) {
                    if (++temp_r31->unk18 > (0.5f * REFRESH_RATE)) {
                        temp_r31->unk20 = 1;
                        temp_r31->unk18 = 0;
                    }
                }
                else {
                    temp_r31->unk18++;
                    temp_f31 = temp_r31->unk18 / (REFRESH_RATE*0.9f);
                    if (temp_f31 >= 1.0f) {
                        temp_r31->unk18 = (REFRESH_RATE*0.9f);
                        temp_f31 = 1.0f;
                    }
                    temp_f31 = cosd(temp_f31 * 90.0f);
                    temp_f30 = -50 + (95 * temp_f31);
                    Hu3DModelPosSet(temp_r31->unk1A, temp_r31->unkC.x, temp_f30, temp_r31->unkC.z);
                    Hu3DModelPosSet(temp_r31->unk1E, temp_r31->unkC.x, temp_f30, temp_r31->unkC.z);
                }
            }
        }
    }
}

s16 fn_1_4724(void)
{
    return lbl_1_data_162;
}

u32 fn_1_4738(s16 arg0, s16 arg1)
{
    Work2110 *temp_r31;
    temp_r31 = lbl_1_bss_2C->data;
    temp_r31 += arg0;
    if (arg1 == -1) {
        return 0;
    }
    return temp_r31->unk4[temp_r31->unk16C[arg1]].unk0;
}

void fn_1_66DC(s16 *arg0, s16 arg1, s16 arg2);

void fn_1_4798(Work2110 *arg0)
{
    s16 temp_r31;
    s16 sp10[10];
    Unk2110Obj *sp8[2];
    fn_1_66DC(sp10, 0, 10);
    sp8[0] = &arg0[0].unk4[0];
    sp8[1] = &arg0[1].unk4[0];
    for (temp_r31 = 0; temp_r31 < 10; temp_r31++, sp8[0]++, sp8[1]++) {
        sp8[0]->unk1A = lbl_1_bss_34[sp10[temp_r31]];
        sp8[1]->unk1A = lbl_1_bss_34[sp10[temp_r31] + 10];
        sp8[0]->unk18 = sp8[1]->unk18 = (sp10[temp_r31] < 5) ? sp10[temp_r31] : sp10[temp_r31] - 5;
    }
}

void fn_1_48D0(Work2110 *arg0)
{
    float temp_f31;
    s16 temp_r31;
    s16 temp_r30;
    for (temp_r30 = 0; temp_r30 < 10; temp_r30++) {
        temp_f31 = arg0->unk0 + arg0->unk4[temp_r30].unk4;
        temp_r31 = (temp_f31 / 360.0f) * 10.0f;
        if (temp_r31 >= 10) {
            temp_r31 -= 10;
        }
        else if (temp_r31 < 0) {
            temp_r31 += 10;
        }
        arg0->unk16C[temp_r31] = temp_r30;
    }
}

void fn_1_498C(s16 arg0, Work2110 *arg1)
{
    float temp_f31;
    Unk2110Obj *temp_r31;
    Bss12CStruct *temp_r30;
    s16 temp_r29;
    temp_r31 = &arg1->unk4[0];
    temp_r30 = &lbl_1_bss_12C[arg0];
    for (temp_r29 = 0; temp_r29 < 10; temp_r29++, temp_r31++) {
        temp_f31 = arg1->unk0 + temp_r31->unk4;
        if (temp_f31 >= 360.0f) {
            temp_f31 -= 360.0f;
        }
        temp_r31->unkC.x = temp_r30->unkC.x + (153.0 * sind(temp_f31));
        temp_r31->unkC.z = temp_r30->unkC.z + (153.0 * cosd(temp_f31));
        temp_r31->unk8 = atan2d(temp_r30->unkC.x - temp_r31->unkC.x, temp_r30->unkC.z - temp_r31->unkC.z);
    }
}

s16 fn_1_4B14(s16 arg0, s16 arg1, s16 *arg2)
{
    Unk2110Obj *temp_r31;
    s16 temp_r30;
    Work2110 *temp_r29;
    temp_r29 = lbl_1_bss_2C->data;
    *arg2 = 0;
    temp_r29 += arg0;
    temp_r31 = &temp_r29->unk4[temp_r29->unk16C[arg1]];
    if (temp_r31->unk0 & 0x1) {
        return -1;
    }
    temp_r31->unk0 |= 0x1;
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        if (!lbl_1_bss_12C[arg0].unk134[temp_r30] && lbl_1_bss_5C.unkC[temp_r30] == temp_r31->unk18) {
            *arg2 = 1;
            lbl_1_bss_12C[arg0].unk134[temp_r30] = 1;
            temp_r31->unk0 |= 0x2;
            temp_r31->unk18 = 0;
            temp_r31->unk20 = 1;
            Hu3DMotionTimeSet(lbl_1_bss_2C->model[arg0 + 1], 0);
            Hu3DModelAttrReset(lbl_1_bss_2C->model[arg0 + 1], HU3D_MOTATTR_PAUSE);
            HuAudFXPlay(9);
            break;
        }
    }
    return temp_r31->unk1C;
}

s16 fn_1_4CDC(s16 arg0, s16 arg1)
{
    Work2110 *temp_r31;
    Unk2110Obj *temp_r30;
    temp_r31 = lbl_1_bss_2C->data;
    temp_r31 += arg0;
    temp_r30 = &temp_r31->unk4[temp_r31->unk16C[arg1]];
    if (temp_r30->unk0 & 0x1) {
        return 0;
    }
    else {
        return 1;
    }
}

void fn_1_4D4C(void)
{
    lbl_1_bss_5C.unkC[0] = rand16() % 5;
    lbl_1_bss_5C.unkC[1] = rand16() % 5;
    lbl_1_bss_12C[0].unk134[0] = lbl_1_bss_12C[0].unk134[1] = 0;
    lbl_1_bss_12C[1].unk134[0] = lbl_1_bss_12C[1].unk134[1] = 0;
}

void fn_1_6638(s16 *arg0, s16 arg1);

void fn_1_4E30(s16 arg0, Bss61CWork *arg1)
{
    s16 sp1E[10];
    s16 spA[10];
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    Work2110 *temp_r27;
    Unk2110Obj *temp_r26;
    temp_r27 = lbl_1_bss_2C->data;
    for (temp_r30 = 0; temp_r30 < 10; temp_r30++) {
        sp1E[temp_r30] = spA[temp_r30] = 0;
    }
    for (temp_r30 = 0; temp_r30 < 8; temp_r30++) {
        arg1->unk5E[temp_r30] = -1;
    }
    temp_r27 += arg0;
    for (temp_r28 = 0, temp_r29 = 0; temp_r28 < 2; temp_r28++) {
        for (temp_r30 = 0; temp_r30 < 10; temp_r30++) {
            temp_r26 = &temp_r27->unk4[temp_r27->unk16C[temp_r30]];
            if (temp_r26->unk18 == lbl_1_bss_5C.unkC[temp_r28] && !sp1E[temp_r30]) {
                arg1->unk5E[temp_r29++] = temp_r30;
                sp1E[temp_r30] = 1;
            }
        }
    }
    for (temp_r28 = 0, temp_r30 = 0; temp_r28 < 10; temp_r28++) {
        if (!sp1E[temp_r28]) {
            spA[temp_r30++] = temp_r28;
        }
    }
    fn_1_6638(spA, temp_r30);
    temp_r30 = 0;
    if (temp_r29 == 2) {
        temp_r29 += 2;
    }

    while (1) {
        if (temp_r29 >= 8) {
            break;
        }
        arg1->unk5E[temp_r29++] = spA[temp_r30++];
    }
    arg1->unk70 = 0;
    temp_r29 = arg1->unk14->unk4;
    switch (GWPlayerCfg[arg1->unk4].diff) {
        case 0:
            arg1->unk72 = (GWPlayerCfg[temp_r29].iscom) ? ((rand16() % 3) + 2) : ((rand16() % 3) + 1);
            arg1->unk6E = 8;
            break;

        case 1:
            arg1->unk72 = (GWPlayerCfg[temp_r29].iscom) ? ((rand16() % 3) + 1) : ((rand16() % 3) + 0);
            arg1->unk6E = 7;
            break;

        case 2:
            arg1->unk72 = (GWPlayerCfg[temp_r29].iscom) ? ((rand16() % 3) + 0) : ((rand16() % 2) + 0);
            arg1->unk6E = 6;
            break;

        case 3:
            arg1->unk72 = (GWPlayerCfg[temp_r29].iscom) ? ((rand16() % 2) + 0) : 0;
            arg1->unk6E = 5;
            break;
    }
    if (arg1->unk6E < 4) {
        arg1->unk6E = 4;
    }
}

void fn_1_5524(void);

Unk72B4Data18 *fn_1_6B34(s16 arg0, Vec *arg1, Vec *arg2, float arg3, GXColor *arg4);

void fn_1_52D8(void)
{
    Bss5CStruct *temp_r31;
    s16 temp_r30;
    Unk72B4Data18 *temp_r29;
    Vec sp18;
    Vec spC;
    GXColor sp8 = { 255, 255, 255, 255 };
    temp_r31 = &lbl_1_bss_5C;
    sp18.x = 0;
    sp18.y = 200;
    sp18.z = -300;
    spC.x = spC.z = 1;
    spC.y = 0.5f;
    fn_1_6B34(temp_r31->unk0[0], &sp18, &spC, 0, &sp8);
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        sp18.x = (temp_r30 == 0) ? -60.0f : 60.0f;
        sp18.y = 220;
        sp18.z = -290;
        spC.x = spC.y = spC.z = 1;
        temp_r29 = fn_1_6B34(temp_r31->unk0[temp_r31->unkC[temp_r30] + 1], &sp18, &spC, 0, &sp8);
        temp_r29->unk28 = temp_r30;
    }
    fn_1_5524();
}

Work72B4 *fn_1_7218(s16 arg0);

void fn_1_5480(void)
{
    Work72B4 *temp_r31;
    Bss5CStruct *temp_r30 = &lbl_1_bss_5C;
    s16 temp_r29;
    temp_r31 = fn_1_7218(temp_r30->unk0[0]);
    temp_r31->unk18[0].unk56 = 0;
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
        temp_r31 = fn_1_7218(temp_r30->unk0[temp_r30->unkC[temp_r29] + 1]);
        temp_r31->unk18[0].unk56 = temp_r31->unk18[1].unk56 = 0;
    }
}

void fn_1_5524(void)
{
    float temp_f30;
    Bss5CStruct *temp_r31;
    Work72B4 *temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    temp_r31 = &lbl_1_bss_5C;
    temp_r30 = fn_1_7218(temp_r31->unk0[0]);
    temp_r30->unk18[0].unk48.x = temp_r31->unk18;
    for (temp_r28 = 0; temp_r28 < 2; temp_r28++) {
        temp_r30 = fn_1_7218(temp_r31->unk0[temp_r31->unkC[temp_r28] + 1]);
        for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
            if (temp_r30->unk18[temp_r29].unk56) {
                temp_f30 = (temp_r30->unk18[temp_r29].unk28 == 0) ? -60.0f : 60.0f;
                temp_r30->unk18[temp_r29].unk48.x = temp_f30 + temp_r31->unk18;
            }
        }
    }
}

void fn_1_566C(s16 arg0)
{
    ModelData *sp8 = &Hu3DData[lbl_1_bss_2C->model[5]];
    lbl_1_bss_5C.unk14 = 0;
    lbl_1_bss_5C.unk12 = 0;
    lbl_1_bss_5C.unk10 = arg0;
    lbl_1_bss_5C.unk20 = lbl_1_bss_5C.unk34 = 0;
    lbl_1_bss_5C.unk28[1] = lbl_1_bss_5C.unk28[0];
}

void fn_1_5708(void)
{
    Bss5CStruct *temp_r31;
    ModelData *temp_r30;
    WorkA44 *temp_r29;
    temp_r30 = &Hu3DData[lbl_1_bss_2C->model[5]];
    temp_r29 = lbl_1_bss_30->data;
    temp_r31 = &lbl_1_bss_5C;
    switch (temp_r31->unk10) {
        case 0:
            if (temp_r30->unk_08 != lbl_1_bss_2C->motion[0]) {
                Hu3DMotionShiftSet(lbl_1_bss_2C->model[5], lbl_1_bss_2C->motion[0], 0, 8, HU3D_MOTATTR_LOOP);
            }
            break;

        case 1:
            if (temp_r31->unk12 == 0) {
                temp_r31->unk12 = 1;
                Hu3DMotionShiftSet(lbl_1_bss_2C->model[5], lbl_1_bss_2C->motion[1], 0, 8, HU3D_MOTATTR_NONE);
            }
            else {
                if (temp_r30->unk_0C == -1) {
                    if (temp_r30->unk_64 >= Hu3DMotionMaxTimeGet(lbl_1_bss_2C->model[5])) {
                        temp_r31->unk16 = rand16() % 2;
                        temp_r31->unk12 = 0;
                        temp_r31->unk10 = 2;
                    }
                }
            }
            break;

        case 2:
            if (temp_r31->unk12 == 0) {
                temp_r31->unk12 = 1;
                Hu3DMotionShiftSet(lbl_1_bss_2C->model[5], lbl_1_bss_2C->motion[5], 0, 8, HU3D_MOTATTR_LOOP);
            }
            else {
                if (temp_r29->unkA < (3 * REFRESH_RATE)) {
                    temp_r31->unk12 = 0;
                    temp_r31->unk10 = 5;
                }
            }
            break;

        case 3:
            if (temp_r31->unk12 == 0) {
                temp_r31->unk12 = 1;
                Hu3DMotionShiftSet(lbl_1_bss_2C->model[5], lbl_1_bss_2C->motion[2], 0, 8, HU3D_MOTATTR_LOOP);
            }
            else {
                if (temp_r30->unk_0C == -1) {
                    if (temp_r30->unk_64 >= Hu3DMotionMaxTimeGet(lbl_1_bss_2C->model[5]) - 1.0f) {
                        if (++temp_r31->unk14 > 1) {
                            temp_r31->unk12 = 0;
                            temp_r31->unk10 = 0;
                        }
                    }
                }
            }
            break;

        case 4:
            if (temp_r31->unk12 == 0) {
                temp_r31->unk12 = 1;
                Hu3DMotionShiftSet(lbl_1_bss_2C->model[5], lbl_1_bss_2C->motion[3], 0, 8, HU3D_MOTATTR_NONE);
            }
            else {
                if (temp_r30->unk_0C == -1) {
                    if (temp_r30->unk_64 >= Hu3DMotionMaxTimeGet(lbl_1_bss_2C->model[5])) {
                        temp_r31->unk12 = 0;
                        temp_r31->unk10 = 0;
                    }
                }
            }
            break;

        case 5:
            if (temp_r31->unk12 == 0) {
                temp_r31->unk12 = 1;
                Hu3DMotionShiftSet(lbl_1_bss_2C->model[5], lbl_1_bss_2C->motion[6], 0, 8, HU3D_MOTATTR_LOOP);
            }
            break;
    }
    temp_r30->pos.x = temp_r31->unk18;
    temp_r30->rot.y = temp_r31->unk28[0];
}

void fn_1_5B70(float arg0, float arg1, float arg2, s16 arg3, unkHook72B4Data18 arg4, s16 arg5)
{
    Vec sp2C;
    Vec sp20;
    GXColor sp1A;
    float temp_f31;
    float temp_f30;

    Unk72B4Data18 *temp_r31;
    s16 temp_r30;
    temp_f30 = 360.0f / arg3;
    temp_f31 = rand16() % 361;
    for (temp_r30 = 0; temp_r30 < arg3; temp_r30++, temp_f31 += temp_f30) {
        sp2C.x = arg0 + ((rand16() % 21) - 10);
        sp2C.y = arg1 + ((rand16() % 21) - 10);
        sp2C.z = arg2 + ((rand16() % 21) - 10);
        sp20.x = sp20.y = sp20.z = 0.1f * ((rand16() % 11) + 15);
        sp1A.r = sp1A.g = sp1A.b = (rand16() % 128) + 128;
        sp1A.a = 128;
        temp_r31 = fn_1_6B34(lbl_1_bss_30->model[0], &sp2C, &sp20, 0, &sp1A);
        if (!temp_r31) {
            break;
        }
        temp_r31->unk30 = arg4;
        temp_r31->unk2C = arg5;
        temp_r31->unk28 = 0;
        temp_r31->unk2A = (rand16() % 2) + 2;
        temp_r31->unk0.x = 3.5 * sind(temp_f31);
        temp_r31->unk0.y = 0.01f * ((rand16() % 16) + 20);
        temp_r31->unk0.z = 3.5 * cosd(temp_f31);
        temp_r31->unkC.x = temp_r31->unk0.x * 0.03f;
        temp_r31->unkC.y = temp_r31->unk0.y * 0.03f;
        temp_r31->unkC.z = temp_r31->unk0.z * 0.03f;
    }
}

void fn_1_6030(ModelData *arg0, Work72B4 *arg1, Mtx arg2)
{
    Unk72B4Data18 *temp_r31;
    s16 temp_r29;
    GXColor *temp_r28;
    unkHook72B4Data18 temp_r27;
    temp_r31 = arg1->unk18;
    temp_r28 = arg1->unk24;
    for (temp_r29 = 0; temp_r29 < arg1->unk0; temp_r29++, temp_r31++, temp_r28++) {
        if (temp_r31->unk56 == 0) {
            continue;
        }
        temp_r31->unk48.x += temp_r31->unk0.x;
        temp_r31->unk48.y += temp_r31->unk0.y;
        temp_r31->unk48.z += temp_r31->unk0.z;
        temp_r31->unk0.x -= temp_r31->unkC.x;
        temp_r31->unk0.y -= temp_r31->unkC.y;
        temp_r31->unk0.z -= temp_r31->unkC.z;
        temp_r31->unk28++;
        if (temp_r31->unk28 >= temp_r31->unk2A) {
            temp_r31->unk28 = 0;
            temp_r31->unk54++;
        }
        if (temp_r31->unk54 >= arg1->unk14) {
            temp_r31->unk30 = NULL;
            temp_r31->unk56 = 0;
        }
        else {
            if (temp_r31->unk54 == 2 && temp_r31->unk30) {
                temp_r27 = temp_r31->unk30;
                temp_r27(temp_r31);
            }
        }
    }
}

void fn_1_6184(Vec *arg0, Bss12CInner *arg1)
{
    s16 temp_r31;
    s16 temp_r30;
    float spC[3];
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    float temp_f24;
    float temp_f23;
    temp_f28 = arg0[1].x - arg0[0].x;
    temp_f27 = arg0[1].y - arg0[0].y;
    temp_f26 = arg0[1].z - arg0[0].z;
    temp_f25 = arg0[2].x - arg0[0].x;
    temp_f24 = arg0[2].y - arg0[0].y;
    temp_f23 = arg0[2].z - arg0[0].z;
    spC[0] = (temp_f27 * temp_f23) - (temp_f26 * temp_f24);
    spC[1] = (temp_f26 * temp_f25) - (temp_f28 * temp_f23);
    spC[2] = (temp_f28 * temp_f24) - (temp_f27 * temp_f25);
    temp_f29 = VECMagPoint(spC[0], spC[1], spC[2]);
    if (0.0f != temp_f29) {
        spC[0] /= temp_f29;
        spC[1] /= temp_f29;
        spC[2] /= temp_f29;
    }
    arg1->unkC = (spC[0] * arg0[0].x) + (spC[1] * arg0[0].y) + (spC[2] * arg0[0].z);
    temp_r30 = 0;
    for (temp_r31 = 1; temp_r31 < 3; temp_r31++) {
        if (ABS(spC[temp_r30]) < ABS(spC[temp_r31])) {
            temp_r30 = temp_r31;
        }
    }
    arg1->unk0.x = spC[0];
    arg1->unk0.y = spC[1];
    arg1->unk0.z = spC[2];
    arg1->unk10 = temp_r30;
}

float fn_1_6504(float arg0, float arg1, float arg2)
{
    float temp_f31 = arg1 - arg0;
    if (temp_f31 > 180.0f) {
        temp_f31 -= 360.0f;
    }
    else if (temp_f31 < -180.0f) {
        temp_f31 += 360.0f;
    }
    temp_f31 = arg0 + (temp_f31 * arg2);
    if (temp_f31 >= 360.0f) {
        temp_f31 -= 360.0f;
    }
    else if (temp_f31 < 0.0f) {
        temp_f31 += 360.0f;
    }
    return temp_f31;
}

float fn_1_65CC(float arg0, float arg1, float arg2)
{
    return arg0 + (arg2 * (arg1 - arg0));
}

float fn_1_65DC(float arg0, float arg1, float arg2, float arg3)
{
    float temp_f31 = 1.0f - arg3;
    return (arg0 * (temp_f31 * temp_f31)) + ((2.0f * temp_f31) * arg3 * arg1) + (arg2 * (arg3 * arg3));
}

void fn_1_6638(s16 *arg0, s16 arg1)
{
    s16 temp_r31;
    s16 spCE[99];
    s16 sp8[99];
    memcpy(sp8, arg0, arg1 * sizeof(s16));
    fn_1_66DC(spCE, 0, arg1);
    for (temp_r31 = 0; temp_r31 < arg1; temp_r31++) {
        arg0[temp_r31] = sp8[spCE[temp_r31]];
    }
}

void fn_1_66DC(s16 *arg0, s16 arg1, s16 arg2)
{
    s16 temp_r31;
    s16 temp_r29;
    s16 temp_r28;
    for (temp_r31 = 0; temp_r31 < arg2; temp_r31++) {
        arg0[temp_r31] = arg1 + temp_r31;
    }
    for (temp_r31 = arg2 - 1; temp_r31 >= 0; temp_r31--) {
        temp_r29 = rand16() % (s16)(temp_r31 + 1);
        temp_r28 = arg0[temp_r31];
        arg0[temp_r31] = arg0[temp_r29];
        arg0[temp_r29] = temp_r28;
    }
}

void fn_1_67C0(void)
{
    if (HuPadBtnDown[0] & PAD_TRIGGER_L) {
        lbl_1_bss_12 ^= 1;
    }
    if (lbl_1_bss_12 == 0) {
        return;
    }
    if (HuPadBtn[0] & PAD_BUTTON_LEFT) {
        CRot.y++;
    }
    if (HuPadBtn[0] & PAD_BUTTON_RIGHT) {
        CRot.y--;
    }
    if (HuPadBtn[0] & PAD_BUTTON_UP) {
        CRot.x--;
    }
    if (HuPadBtn[0] & PAD_BUTTON_DOWN) {
        CRot.x++;
    }
    Center.x += HuPadSubStkX[0];
    if (HuPadBtn[0] & PAD_TRIGGER_R) {
        Center.y += HuPadSubStkY[0];
    }
    else {
        Center.z += HuPadSubStkY[0];
    }
    if (HuPadBtn[0] & PAD_BUTTON_X) {
        CZoom += 10;
    }
    if (HuPadBtn[0] & PAD_BUTTON_Y) {
        CZoom -= 10;
    }
    if (HuPadBtnDown[0] & PAD_BUTTON_A) {
        OSReport("\nCZoom = %.2f \n", CZoom);
        OSReport("Center x = %.2f: y = %.2f: z = %.2f \n", Center.x, Center.y, Center.z);
        OSReport("CRot x = %.2f: y = %.2f: z = %.2f \n", CRot.x, CRot.y, CRot.z);
    }
}

Unk72B4Data18 *fn_1_6B34(s16 arg0, Vec *arg1, Vec *arg2, float arg3, GXColor *arg4)
{
    Unk72B4Data18 *temp_r31;
    Work72B4 *temp_r30;
    s16 temp_r29;
    ModelData *temp_r28;
    temp_r28 = &Hu3DData[arg0];
    temp_r30 = temp_r28->unk_120;
    for (temp_r29 = 0, temp_r31 = temp_r30->unk18; temp_r29 < temp_r30->unk0; temp_r29++, temp_r31++) {
        if (!temp_r31->unk56) {
            break;
        }
    }
    if (temp_r29 == temp_r30->unk0) {
        return NULL;
    }
    temp_r30->unk24[temp_r29].r = arg4->r;
    temp_r30->unk24[temp_r29].g = arg4->g;
    temp_r30->unk24[temp_r29].b = arg4->b;
    temp_r30->unk24[temp_r29].a = arg4->a;
    temp_r31->unk34 = temp_r29;
    temp_r31->unk38 = arg3;
    temp_r31->unk3C = *arg2;
    temp_r31->unk48 = *arg1;
    temp_r31->unk54 = 0;
    temp_r31->unk30 = NULL;
    temp_r31->unk56 = 1;
    return temp_r31;
}

void fn_1_72B4(ModelData *model, Mtx mtx);
void fn_1_7824(HsfVector2f *arg0, s16 arg1, s16 arg2, float arg3, float arg4);

s16 fn_1_6C74(AnimData *arg0, s16 arg1, float arg2, s16 arg3, s16 arg4)
{
    Work72B4 *temp_r31;
    s16 temp_r30;
    HsfVector2f *temp_r29;
    ModelData *temp_r28;
    GXColor *temp_r27;
    Vec *temp_r25;
    Unk72B4Data18 *temp_r24;
    s16 temp_r22;
    void *temp_r21;
    s16 temp_r20;
    s16 temp_r19;
    void *temp_r18;
    temp_r20 = Hu3DHookFuncCreate(fn_1_72B4);
    temp_r28 = &Hu3DData[temp_r20];
    temp_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(Work72B4), temp_r28->unk_48);
    temp_r28->unk_120 = temp_r31;
    arg0->useNum++;
    temp_r31->unk10 = arg0;
    temp_r31->unk0 = arg1;
    temp_r31->unk8 = 0;
    temp_r31->unkC = 0;
    temp_r24 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Unk72B4Data18), temp_r28->unk_48);
    temp_r31->unk18 = temp_r24;
    for (temp_r30 = 0; temp_r30 < arg1; temp_r30++, temp_r24++) {
        temp_r24->unk54 = -1;
        temp_r24->unk56 = 0;
    }
    temp_r25 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec) * 4, temp_r28->unk_48);
    temp_r31->unk1C = temp_r25;
    for (temp_r30 = 0; temp_r30 < arg1 * 4; temp_r30++, temp_r25++) {
        temp_r25->x = temp_r25->y = temp_r25->z = 0;
    }
    temp_r27 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(GXColor), temp_r28->unk_48);
    temp_r31->unk24 = temp_r27;
    for (temp_r30 = 0; temp_r30 < arg1; temp_r30++, temp_r27++) {
        temp_r27->r = temp_r27->g = temp_r27->b = temp_r27->a = 255;
    }
    temp_r29 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(HsfVector2f) * 4, temp_r28->unk_48);
    temp_r31->unk20 = temp_r29;
    for (temp_r30 = 0; temp_r30 < arg1; temp_r30++) {
        temp_r29->x = 0;
        temp_r29->y = 0;
        temp_r29++;
        temp_r29->x = 1;
        temp_r29->y = 0;
        temp_r29++;
        temp_r29->x = 1;
        temp_r29->y = 1;
        temp_r29++;
        temp_r29->x = 0;
        temp_r29->y = 1;
        temp_r29++;
    }
    if (arg3 != 0 || arg4 != 0) {
        temp_r22 = arg0->bmp->sizeX / arg3;
        temp_r19 = arg0->bmp->sizeY / arg4;
        temp_r31->unk14 = temp_r22 * temp_r19;
        temp_r31->unk60 = 1.0f / temp_r22;
        temp_r31->unk64 = 1.0f / temp_r19;
    }
    else {
        temp_r22 = 1;
        temp_r31->unk14 = 1;
        temp_r31->unk60 = 1;
        temp_r31->unk64 = 1;
    }
    temp_r31->unk5C = HuMemDirectMallocNum(HEAP_DATA, temp_r31->unk14 * sizeof(HsfVector2f), temp_r28->unk_48);
    fn_1_7824(temp_r31->unk5C, temp_r31->unk14, temp_r22, temp_r31->unk60, temp_r31->unk64);
    temp_r31->unk2C[0].x = temp_r31->unk2C[3].x = temp_r31->unk2C[2].y = temp_r31->unk2C[3].y = -arg2;
    temp_r31->unk2C[1].x = temp_r31->unk2C[2].x = temp_r31->unk2C[0].y = temp_r31->unk2C[1].y = arg2;
    temp_r31->unk2C[0].z = temp_r31->unk2C[1].z = temp_r31->unk2C[2].z = temp_r31->unk2C[3].z = 0;
    temp_r21 = HuMemDirectMallocNum(HEAP_DATA, 0x20000, temp_r28->unk_48);
    temp_r18 = temp_r21;
    DCFlushRange(temp_r21, 0x20000);
    GXBeginDisplayList(temp_r18, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4 * arg1);
    for (temp_r30 = 0; temp_r30 < arg1; temp_r30++) {
        GXPosition1x16(temp_r30 * 4);
        GXColor1x16(temp_r30);
        GXTexCoord1x16(temp_r30 * 4);
        GXPosition1x16((temp_r30 * 4) + 1);
        GXColor1x16(temp_r30);
        GXTexCoord1x16((temp_r30 * 4) + 1);
        GXPosition1x16((temp_r30 * 4) + 2);
        GXColor1x16(temp_r30);
        GXTexCoord1x16((temp_r30 * 4) + 2);
        GXPosition1x16((temp_r30 * 4) + 3);
        GXColor1x16(temp_r30);
        GXTexCoord1x16((temp_r30 * 4) + 3);
    }
    temp_r31->unk4 = GXEndDisplayList();
    temp_r31->unk28 = HuMemDirectMallocNum(HEAP_DATA, temp_r31->unk4, temp_r28->unk_48);
    memcpy(temp_r31->unk28, temp_r21, temp_r31->unk4);
    DCFlushRange(temp_r31->unk28, temp_r31->unk4);
    HuMemDirectFree(temp_r21);
    return temp_r20;
}

void fn_1_71B8(s16 arg0)
{
    ModelData *temp_r31;
    Work72B4 *temp_r30;
    temp_r31 = &Hu3DData[arg0];
    temp_r30 = temp_r31->unk_120;
    HuSprAnimKill(temp_r30->unk10);
    Hu3DModelKill(arg0);
}

Work72B4 *fn_1_7218(s16 arg0)
{
    ModelData *temp_r31;
    temp_r31 = &Hu3DData[arg0];
    return temp_r31->unk_120;
}

void fn_1_7244(s16 arg0, unkHook72B4 arg1)
{
    ModelData *temp_r31;
    Work72B4 *temp_r30;
    temp_r31 = &Hu3DData[arg0];
    temp_r30 = temp_r31->unk_120;
    temp_r30->unkC = arg1;
}

void fn_1_727C(s16 arg0, u8 arg1)
{
    ModelData *temp_r31;
    Work72B4 *temp_r30;
    temp_r31 = &Hu3DData[arg0];
    temp_r30 = temp_r31->unk_120;
    temp_r30->unk8 = arg1;
}

void fn_1_78F0(HsfVector2f *arg0, HsfVector2f *arg1, s16 arg2, float arg3, float arg4);
void fn_1_7994(Vec *arg0, Vec *arg1, Vec *arg2, s16 arg3);

void fn_1_79FC(Mtx arg0, Mtx arg1);

void fn_1_72B4(ModelData *model, Mtx mtx)
{
    Mtx sp128;
    ROMtx spF8;
    Mtx spC8;
    Mtx sp98;
    Vec sp68[4];
    Vec sp38[4];
    Vec sp8[4];
    Vec *temp_r31;
    Work72B4 *temp_r30;
    Unk72B4Data18 *temp_r29;
    HsfVector2f *temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    unkHook72B4 temp_r23;
    temp_r30 = model->unk_120;
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    temp_r25 = temp_r30->unk10->bmp->dataFmt & ANIM_BMP_FMTMASK;
    if (temp_r25 == ANIM_BMP_I8 || temp_r25 == ANIM_BMP_I4) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
    }
    else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    }
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    if (model->attr & 0x2) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
    else {
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    }
    HuSprTexLoad(temp_r30->unk10, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    switch (temp_r30->unk8) {
        case 0:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            break;

        case 1:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
            break;

        case 2:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVSRCCLR, GX_LO_NOOP);
            break;
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, temp_r30->unk1C, sizeof(Vec));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, temp_r30->unk24, sizeof(GXColor));
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, temp_r30->unk20, sizeof(HsfVector2f));
    fn_1_79FC(mtx, sp128);
    PSMTXReorder(sp128, spF8);
    if (!omPauseChk() && temp_r30->unkC) {
        temp_r23 = temp_r30->unkC;
        temp_r23(model, temp_r30, mtx);
    }
    temp_r29 = temp_r30->unk18;
    temp_r31 = temp_r30->unk1C;
    temp_r27 = temp_r30->unk20;
    PSMTXROMultVecArray(spF8, temp_r30->unk2C, sp68, 4);
    for (temp_r26 = 0; temp_r26 < temp_r30->unk0; temp_r26++, temp_r29++, temp_r27 += 4) {
        if (temp_r29->unk56 == 0) {
            temp_r31->x = temp_r31->y = temp_r31->z = 0;
            temp_r31++;
            temp_r31->x = temp_r31->y = temp_r31->z = 0;
            temp_r31++;
            temp_r31->x = temp_r31->y = temp_r31->z = 0;
            temp_r31++;
            temp_r31->x = temp_r31->y = temp_r31->z = 0;
            temp_r31++;
        }
        else {
            if (0.0f == temp_r29->unk38) {
                fn_1_7994(sp68, sp38, &temp_r29->unk3C, 4);
                VECAdd(&sp38[0], &temp_r29->unk48, temp_r31++);
                VECAdd(&sp38[1], &temp_r29->unk48, temp_r31++);
                VECAdd(&sp38[2], &temp_r29->unk48, temp_r31++);
                VECAdd(&sp38[3], &temp_r29->unk48, temp_r31++);
            }
            else {
                fn_1_7994(temp_r30->unk2C, sp38, &temp_r29->unk3C, 4);
                MTXRotDeg(spC8, 'Z', temp_r29->unk38);
                MTXConcat(sp128, spC8, sp98);
                MTXMultVecArray(sp98, sp38, sp8, 4);
                VECAdd(&sp8[0], &temp_r29->unk48, temp_r31++);
                VECAdd(&sp8[1], &temp_r29->unk48, temp_r31++);
                VECAdd(&sp8[2], &temp_r29->unk48, temp_r31++);
                VECAdd(&sp8[3], &temp_r29->unk48, temp_r31++);
            }
            if (temp_r29->unk54 != -1) {
                fn_1_78F0(temp_r27, temp_r30->unk5C, temp_r29->unk54, temp_r30->unk60, temp_r30->unk64);
            }
        }
    }
    DCFlushRangeNoSync(temp_r30->unk1C, (temp_r30->unk0 * sizeof(Vec)) * 4);
    DCFlushRangeNoSync(temp_r30->unk20, (temp_r30->unk0 * sizeof(HsfVector2f)) * 4);
    PPCSync();
    GXCallDisplayList(temp_r30->unk28, temp_r30->unk4);
}

void fn_1_7824(HsfVector2f *arg0, s16 arg1, s16 arg2, float arg3, float arg4)
{
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r31;
    for (temp_r31 = 0; temp_r31 < arg1; temp_r31++, arg0++) {
        temp_r30 = temp_r31 % arg2;
        temp_r29 = temp_r31 / arg2;
        arg0->x = temp_r30 * arg3;
        arg0->y = temp_r29 * arg4;
    }
}

void fn_1_78F0(HsfVector2f *arg0, HsfVector2f *arg1, s16 arg2, float arg3, float arg4)
{
    arg0[0].x = arg1[arg2].x;
    arg0[0].y = arg1[arg2].y;
    arg0[1].x = arg3 + arg1[arg2].x;
    arg0[1].y = arg1[arg2].y;
    arg0[2].x = arg3 + arg1[arg2].x;
    arg0[2].y = arg4 + arg1[arg2].y;
    arg0[3].x = arg1[arg2].x;
    arg0[3].y = arg4 + arg1[arg2].y;
}

void fn_1_7994(Vec *arg0, Vec *arg1, Vec *arg2, s16 arg3)
{
    s16 temp_r31;
    for (temp_r31 = 0; temp_r31 < arg3; temp_r31++, arg0++, arg1++) {
        arg1->x = arg0->x * arg2->x;
        arg1->y = arg0->y * arg2->y;
        arg1->z = arg0->z * arg2->z;
    }
}

void fn_1_79FC(Mtx arg0, Mtx arg1)
{
    arg1[0][0] = arg0[0][0];
    arg1[1][0] = arg0[0][1];
    arg1[2][0] = arg0[0][2];
    arg1[0][1] = arg0[1][0];
    arg1[1][1] = arg0[1][1];
    arg1[2][1] = arg0[1][2];
    arg1[0][2] = arg0[2][0];
    arg1[1][2] = arg0[2][1];
    arg1[2][2] = arg0[2][2];
    arg1[0][3] = 0;
    arg1[1][3] = 0;
    arg1[2][3] = 0;
}

s32 fn_1_7A78(s32 arg0, s16 vol)
{
    MSM_SEPARAM seParam;
    seParam.flag = MSM_SEPARAM_VOL;
    seParam.vol = vol;
    return msmSeSetParam(arg0, &seParam);
}
