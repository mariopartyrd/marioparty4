#include "ext_math.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/msm.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "string.h"
#include "version.h"

#ifndef __MWERKS__
#include "game/audio.h"
#include "game/esprite.h"
#endif

typedef struct UnkM404Struct {
    s16 unk_00;
    s16 unk_02[6];
    s16 unk0E[10];
} UnkM404Struct;

typedef struct UnkM404Struct2 {
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
} UnkM404Struct2;

typedef struct UnkM404Struct3 {
    struct {
        u8 unk_00_field0 : 1;
        u8 unk_00_field1 : 1;
        u8 unk_00_field2 : 1;
    };
    s8 unk01;
    s16 unk_02;
    s16 unk_04;
    s8 unk_06;
    s8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    float unk_14;
    s32 unk18[2];
    float unk_20;
    float unk_24;
    float unk_28;
    s32 unk_2C;
    s32 unk30[2];
    s16 unk_38;
    s16 unk3A;
    AnimData *unk_3C;
    AnimData *unk_40;
    void *unk_44;
    s32 unk_48;
    AnimData *unk_4C;
    AnimData *unk_50;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    float unk_60;
    float unk_64;
    float unk_68;
    u16 unk_6C;
    float (*unk_70)[2];
    s32 unk_74;
    s32 unk78[91];
} UnkM404Struct3; // size 0x1E4

omObjData *lbl_1_bss_58;
omObjData *lbl_1_bss_54;
omObjData *lbl_1_bss_50;
omObjData *lbl_1_bss_4C;
s32 lbl_1_bss_48;
s32 lbl_1_bss_38[4];
s32 lbl_1_bss_28[4];
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C;
Vec lbl_1_bss_10;
s16 lbl_1_bss_C;
s32 lbl_1_bss_8;
float lbl_1_bss_4;
s32 lbl_1_bss_0;

float lbl_1_data_0[][2] = {
    { -0.00026f, 0.51953f },
    { 0.02825f, 0.51563f },
    { 0.04108f, 0.5166f },
    { 0.05996f, 0.5166f },
    { 0.07878f, 0.39063f },
    { 0.08437f, 0.35254f },
    { 0.09284f, 0.2998f },
    { 0.10234f, 0.2998f },
    { 0.11283f, 0.2998f },
    { 0.1319f, 0.2959f },
    { 0.1373f, 0.40918f },
    { 0.15072f, 0.38574f },
    { 0.17747f, 0.38183f },
    { 0.19753f, 0.47168f },
    { 0.20098f, 0.74902f },
    { 0.2235f, 0.73438f },
    { 0.26048f, 0.71094f },
    { 0.27695f, 0.27344f },
    { 0.30872f, 0.29883f },
    { 0.32409f, 0.30566f },
    { 0.3291f, 0.56738f },
    { 0.34388f, 0.58594f },
    { 0.36296f, 0.58789f },
    { 0.3653f, 0.33984f },
    { 0.38112f, 0.32227f },
    { 0.38717f, 0.31543f },
    { 0.40221f, 0.4541f },
    { 0.42044f, 0.44433f },
    { 0.4375f, 0.43555f },
    { 0.46302f, 0.13281f },
    { 0.48229f, 0.13965f },
    { 0.50013f, 0.14844f },
    { 0.51406f, 0.14844f },
    { 0.52493f, 0.29394f },
    { 0.53854f, 0.5166f },
    { 0.53105f, 0.86816f },
    { 0.50755f, 0.87207f },
    { 0.48893f, 0.85254f },
    { 0.47923f, 0.64258f },
    { 0.48828f, 0.35156f },
    { 0.49401f, 0.19238f },
    { 0.50228f, 0.16797f },
    { 0.52454f, 0.1709f },
    { 0.54518f, 0.17188f },
    { 0.55547f, 0.1748f },
    { 0.57611f, 0.16992f },
    { 0.5916f, 0.16797f },
    { 0.61471f, 0.56543f },
    { 0.62467f, 0.76367f },
    { 0.65156f, 0.76465f },
    { 0.65742f, 0.75488f },
    { 0.69544f, 0.75488f },
    { 0.69544f, 0.63477f },
    { 0.69538f, 0.33203f },
    { 0.69544f, 0.22949f },
    { 0.7028f, 0.22558f },
    { 0.73079f, 0.2207f },
    { 0.76628f, 0.22558f },
    { 0.78555f, 0.22754f },
    { 0.79388f, 0.72949f },
    { 0.81113f, 0.73047f },
    { 0.83034f, 0.72949f },
    { 0.83789f, 0.33789f },
    { 0.86953f, 0.35449f },
    { 0.88047f, 0.36035f },
    { 0.88242f, 0.60058f },
    { 0.89479f, 0.63672f },
    { 0.93939f, 0.68555f },
    { 0.9252f, 0.52051f },
    { 0.94284f, 0.51758f },
    { 0.96113f, 0.51367f },
    { 0.99303f, 0.50977f },
    { 1.0f, 0.50683f },
};
float lbl_1_data_248[][2] = { { -0.00026f, 0.51953f }, { 0.02825f, 0.51563f }, { 0.0541f, 0.78222f }, { 0.07298f, 0.78222f }, { 0.0918f, 0.65625f },
    { 0.0724f, 0.16504f }, { 0.08607f, 0.15918f }, { 0.09928f, 0.15918f }, { 0.11615f, 0.47852f }, { 0.1248f, 0.60156f }, { 0.13379f, 0.73144f },
    { 0.15592f, 0.66602f }, { 0.17044f, 0.66308f }, { 0.18418f, 0.64355f }, { 0.19603f, 0.1748f }, { 0.22279f, 0.1709f }, { 0.26087f, 0.17383f },
    { 0.27507f, 0.16308f }, { 0.30443f, 0.16602f }, { 0.32142f, 0.16992f }, { 0.26738f, 0.70019f }, { 0.27487f, 0.70996f }, { 0.29395f, 0.71191f },
    { 0.35384f, 0.70703f }, { 0.36966f, 0.71289f }, { 0.37565f, 0.71582f }, { 0.37122f, 0.36523f }, { 0.38763f, 0.36621f }, { 0.40117f, 0.36719f },
    { 0.42135f, 0.16406f }, { 0.44062f, 0.1709f }, { 0.45846f, 0.17969f }, { 0.5099f, 0.07813f }, { 0.52077f, 0.22363f }, { 0.53437f, 0.44629f },
    { 0.53262f, 0.90722f }, { 0.50911f, 0.91113f }, { 0.49049f, 0.8916f }, { 0.48496f, 0.76758f }, { 0.48984f, 0.5f }, { 0.49557f, 0.34082f },
    { 0.5127f, 0.40234f }, { 0.53496f, 0.40527f }, { 0.55605f, 0.40625f }, { 0.56322f, 0.20801f }, { 0.58118f, 0.21387f }, { 0.59499f, 0.21875f },
    { 0.60208f, 0.35644f }, { 0.61634f, 0.37305f }, { 0.62865f, 0.37305f }, { 0.63242f, 0.30566f }, { 0.64707f, 0.30957f }, { 0.66439f, 0.31348f },
    { 0.67487f, 0.6084f }, { 0.69551f, 0.6084f }, { 0.69499f, 0.44922f }, { 0.69486f, 0.30078f }, { 0.69492f, 0.19824f }, { 0.70228f, 0.19433f },
    { 0.74681f, 0.18945f }, { 0.78229f, 0.19433f }, { 0.80156f, 0.19629f }, { 0.8194f, 0.76074f }, { 0.83665f, 0.76172f }, { 0.85586f, 0.76074f },
    { 0.85488f, 0.30859f }, { 0.88132f, 0.30469f }, { 0.89225f, 0.31055f }, { 0.89076f, 0.74902f }, { 0.90312f, 0.78516f }, { 0.94772f, 0.83398f },
    { 0.93092f, 0.52832f }, { 0.94857f, 0.52539f }, { 0.96686f, 0.52148f }, { 0.99303f, 0.50977f }, { 1.0f, 0.50683f } };
float lbl_1_data_4A8[][2] = { { -0.00026f, 0.51953f }, { 0.02825f, 0.51563f }, { 0.0332f, 0.55176f }, { 0.04759f, 0.4375f }, { 0.05775f, 0.2959f },
    { 0.06413f, 0.19629f }, { 0.08991f, 0.19531f }, { 0.10723f, 0.19531f }, { 0.11543f, 0.49707f }, { 0.12305f, 0.65918f }, { 0.13607f, 0.94336f },
    { 0.14779f, 0.68945f }, { 0.15514f, 0.53222f }, { 0.16204f, 0.4043f }, { 0.18034f, 0.49512f }, { 0.1847f, 0.35449f }, { 0.19095f, 0.15625f },
    { 0.20742f, 0.17285f }, { 0.22279f, 0.1709f }, { 0.24108f, 0.16894f }, { 0.24896f, 0.08887f }, { 0.2569f, 0.36328f }, { 0.26159f, 0.53125f },
    { 0.2679f, 0.69922f }, { 0.28079f, 0.80859f }, { 0.29987f, 0.89941f }, { 0.31224f, 0.7334f }, { 0.32246f, 0.55664f }, { 0.33112f, 0.41016f },
    { 0.36022f, 0.43164f }, { 0.37207f, 0.60058f }, { 0.38906f, 0.8457f }, { 0.40573f, 0.64844f }, { 0.42227f, 0.39941f }, { 0.43411f, 0.23926f },
    { 0.46732f, 0.79199f }, { 0.4875f, 0.82813f }, { 0.51387f, 0.83496f }, { 0.52324f, 0.13574f }, { 0.48893f, 0.12988f }, { 0.46237f, 0.16699f },
    { 0.46589f, 0.63086f }, { 0.48184f, 0.72266f }, { 0.49629f, 0.81836f }, { 0.50579f, 0.82422f }, { 0.52806f, 0.82715f }, { 0.54915f, 0.82813f },
    { 0.54974f, 0.19433f }, { 0.56764f, 0.17773f }, { 0.57936f, 0.16699f }, { 0.59199f, 0.16894f }, { 0.60111f, 0.16992f }, { 0.60124f, 0.4668f },
    { 0.60124f, 0.45996f }, { 0.60124f, 0.63183f }, { 0.61302f, 0.62695f }, { 0.6321f, 0.63477f }, { 0.65273f, 0.63477f }, { 0.65254f, 0.55176f },
    { 0.65254f, 0.49121f }, { 0.6526f, 0.39551f }, { 0.69297f, 0.39844f }, { 0.69642f, 0.62402f }, { 0.71595f, 0.61621f }, { 0.73451f, 0.61035f },
    { 0.74297f, 0.22266f }, { 0.77773f, 0.21484f }, { 0.79701f, 0.20898f }, { 0.79167f, 0.79102f }, { 0.80892f, 0.79785f }, { 0.83607f, 0.80762f },
    { 0.8487f, 0.4707f }, { 0.87995f, 0.47168f }, { 0.89089f, 0.47754f }, { 0.88796f, 0.14453f }, { 0.90833f, 0.13379f }, { 0.95078f, 0.18066f },
    { 0.95039f, 0.38183f }, { 0.95169f, 0.50977f }, { 0.96999f, 0.50488f }, { 0.99303f, 0.50977f }, { 1.0f, 0.50683f } };

UnkM404Struct2 lbl_1_data_738[] = { { 11000.0f, 450.0f, 0.0f, -87.5f, 323.2f, 42.7f, 0.0f }, { 6175.0f, 100.0f, 0.0f, -87.5f, 323.2f, 0.0f, 0.0f } };

Vec lbl_1_data_770 = { 700.0f, 2500.0f, -700.0f };
Vec lbl_1_data_77C = { 0 };
GXColor lbl_1_data_788 = { 255, 255, 255, 255 };
Vec lbl_1_data_78C = { 1500.0f, 3000.0f, -200.0f };
Vec lbl_1_data_798 = { 0.0f, 1.0f, 0.0f };

s32 fn_1_E48(void);
void fn_1_39C(omObjData *object);
void fn_1_400(omObjData *object);
void fn_1_784(omObjData *object);
void fn_1_7E0(omObjData *object);
void fn_1_A9C(omObjData *object);
void fn_1_D00(Process *arg0);
void fn_1_DEC(void);
void fn_1_1160(void);
void fn_1_1344(omObjData *object);
void fn_1_1AFC(omObjData *object);
float fn_1_2EBC(float arg0[], float arg8);
void fn_1_4C7C(omObjData *object);
void fn_1_44A0(omObjData *object);
void fn_1_4F4C(omObjData *object);
void fn_1_5278(omObjData *object);
void fn_1_5598(Process *arg0);
void fn_1_553C(omObjData *object);
void fn_1_55F0(void);
void fn_1_55F4(omObjData *object);
void fn_1_57A0(omObjData *object);
void fn_1_58E4(ModelData *modelData, Mtx arg1);
AnimData *fn_1_5D64(u16 arg0, u16 arg1, s32 arg2);
void fn_1_5E74(AnimData *arg0, u16 arg1, u16 arg2, u16 arg3);
u16 fn_1_607C(AnimData *arg0, u16 arg1, u16 arg2);
s32 fn_1_6248(void *arg0, s32 arg1);
void fn_1_6440(omObjData *object);
void fn_1_648C(s32 arg0, s32 arg1, float arg8);
void fn_1_66DC(omObjData *object);

void ObjectSetup(void)
{
    CameraData *var_r30;
    Process *var_r31;
    s16 var_r29;

    var_r30 = Hu3DCamera;
    OSReport("******* M404ObjectSetup *********\n");
    var_r31 = omInitObjMan(50, 8192);
    omGameSysInit(var_r31);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 10.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lbl_1_bss_50 = omAddObjEx(var_r31, 32730, 0, 0, -1, omOutView);
    lbl_1_bss_10.x = lbl_1_data_77C.x - lbl_1_data_770.x;
    lbl_1_bss_10.y = lbl_1_data_77C.y - lbl_1_data_770.y;
    lbl_1_bss_10.z = lbl_1_data_77C.z - lbl_1_data_770.z;
    VECNormalize(&lbl_1_bss_10, &lbl_1_bss_10);
    var_r29 = Hu3DGLightCreateV(&lbl_1_data_770, &lbl_1_bss_10, &lbl_1_data_788);
    Hu3DGLightInfinitytSet(var_r29);
    Hu3DGLightStaticSet(var_r29, 1);
    Hu3DShadowCreate(45.0f, var_r30->nnear, var_r30->ffar);
    Hu3DShadowTPLvlSet(0.625f);
    Hu3DShadowPosSet(&lbl_1_data_78C, &lbl_1_data_798, &lbl_1_data_77C);
    HuAudSndGrpSet(29);
    lbl_1_bss_1C = ((s32)(frand() & 0xFF) * 3) >> 8;
    lbl_1_bss_58 = omAddObjEx(var_r31, 0, 0, 0, -1, fn_1_39C);
    lbl_1_bss_54 = omAddObjEx(var_r31, 0xA, 0, 0, -1, fn_1_6440);
    lbl_1_bss_4C = omAddObjEx(var_r31, 0xB, 0, 0, -1, fn_1_7E0);
    fn_1_D00(var_r31);
    fn_1_5598(var_r31);
}

s32 lbl_1_data_7C8 = 0xFFFFFFFFF;

void fn_1_37C(s32 arg0)
{
    lbl_1_bss_48 = arg0;
}

s32 fn_1_38C(void)
{
    return lbl_1_bss_48;
}

void fn_1_39C(omObjData *object)
{
    fn_1_37C(0);
    lbl_1_bss_24 = REFRESH_RATE;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    object->func = fn_1_400;
}

void fn_1_400(omObjData *object)
{
    switch (fn_1_38C()) {
        case 0:
            if (--lbl_1_bss_24) {
                break;
            }
            fn_1_37C(1);
            lbl_1_bss_24 = 3 * REFRESH_RATE;
            break;
        case 1:
            if (--lbl_1_bss_24) {
                break;
            }
            fn_1_37C(2);
            lbl_1_bss_C = MGSeqCreate(3, 0);
            break;
        case 2:
            if (!MGSeqStatGet(lbl_1_bss_C)) {
                fn_1_37C(3);
            }
            if (lbl_1_data_7C8 >= 0) {
                break;
            }
            if (!(MGSeqStatGet(lbl_1_bss_C) & 16)) {
                break;
            }
            lbl_1_data_7C8 = HuAudSeqPlay(69);
            break;
        case 3:
            if (!fn_1_E48()) {
                break;
            }
            fn_1_37C(4);
            lbl_1_bss_C = MGSeqCreate(3, 1);
            HuAudSeqFadeOut(lbl_1_data_7C8, 100);
            break;
        case 4:
            if (!MGSeqStatGet(lbl_1_bss_C)) {
                fn_1_37C(5);
                WipeColorSet(255, 255, 255);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, REFRESH_RATE / 2);
                lbl_1_bss_24 = REFRESH_RATE;
            }
        case 5:
            if (--lbl_1_bss_24) {
                break;
            }
            fn_1_37C(6);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, REFRESH_RATE);
            break;
        case 6:
            if (WipeStatGet()) {
                break;
            }
            fn_1_37C(7);
            lbl_1_bss_24 = 3 * REFRESH_RATE;
            break;
        case 7:
            if (--lbl_1_bss_24) {
                break;
            }
            fn_1_37C(9);
            fn_1_1160();
            if (lbl_1_bss_38[0] >= 0) {
                HuAudSStreamPlay(1);
            }
            else {
                HuAudSStreamPlay(4);
            }
            lbl_1_bss_24 = 3.5 * REFRESH_RATE;
            break;
        case 8:
            break;
        case 9:
            if (--lbl_1_bss_24) {
                break;
            }
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            object->func = fn_1_784;
            break;
        default:
            break;
    }
    if (omSysExitReq && !WipeStatGet()) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_784;
    }
}

void fn_1_784(omObjData *object)
{
    if (!WipeStatGet()) {
        fn_1_DEC();
        fn_1_55F0();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
        OSReport("******* M404Exit *********\n");
    }
}

u16 lbl_1_data_810[] = { 0, 1, 2, 3, 3, 3 };

float lbl_1_data_81C[][2] = { { 0.0f, 0.0f }, { 0.0f, 0.0f }, { -46.0f, -2.0f }, { -8.0f, 2.0f }, { 10.0f, 2.0f }, { 28.0f, 2.0f } };

float lbl_1_data_84C[][2] = { { 472.0f, 128.0f }, { 472.0f, 208.0f }, { 472.0f, 288.0f }, { 472.0f, 368.0f } };

s32 lbl_1_data_86C[] = {
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x00),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x01),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x02),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x03),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x04),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x05),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x06),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x07),
};

s32 lbl_1_data_88C = 0xFFFFFFFF;

u32 lbl_1_data_890[][2] = {
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00), 0x00000000 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02), 0x00000000 },
    { DATA_MAKE_NUM(DATADIR_M404, 0x22), 0x00000001 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17), 0x00000000 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18), 0x00000000 },
};

s32 lbl_1_data_8B8[] = {
    DATA_MAKE_NUM(DATADIR_M404, 0x01),
    DATA_MAKE_NUM(DATADIR_M404, 0x02),
    DATA_MAKE_NUM(DATADIR_M404, 0x03),
    DATA_MAKE_NUM(DATADIR_M404, 0x04),
    DATA_MAKE_NUM(DATADIR_M404, 0x05),
    DATA_MAKE_NUM(DATADIR_M404, 0x06),
    DATA_MAKE_NUM(DATADIR_M404, 0x07),
    DATA_MAKE_NUM(DATADIR_M404, 0x08),
};

float lbl_1_data_8D8[] = { 35.0f, 30.000002f, 25.0f, 20.0f };

float (*lbl_1_data_8E8[])[2] = { lbl_1_data_0, lbl_1_data_248, lbl_1_data_4A8 };

u16 lbl_1_data_8F4[] = { 73, 76, 82, 0 };

s32 lbl_1_data_8FC[][2] = {
    { DATA_MAKE_NUM(DATADIR_M404, 0x13), DATA_MAKE_NUM(DATADIR_M404, 0x14) },
    { DATA_MAKE_NUM(DATADIR_M404, 0x15), DATA_MAKE_NUM(DATADIR_M404, 0x16) },
    { DATA_MAKE_NUM(DATADIR_M404, 0x17), DATA_MAKE_NUM(DATADIR_M404, 0x18) },
};

void fn_1_7E0(omObjData *object)
{
    UnkM404Struct *var_r31;
    u32 var_r30;
    s32 var_r29;
    UnkM404Struct *var_r27;
    omObjData **var_r26;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM404Struct) * 4, MEMORY_DEFAULT_NUM);
    object->data = var_r31;
    memset(object->data, 0, 136);
    var_r26 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);

    for (var_r29 = 0; var_r29 < 4; var_r31++, var_r29++) {
        for (var_r27 = var_r26[var_r29]->data, var_r30 = 0; var_r30 < 6; var_r30++) {
            switch (lbl_1_data_810[var_r30]) {
                case 0:
                    var_r31->unk_02[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x14), 1, 0);
                    espPriSet(var_r31->unk_02[var_r30], 256);
                    break;
                case 1:
                    var_r31->unk_02[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x15), 0, 0);
                    espPriSet(var_r31->unk_02[var_r30], 257);
                    espColorSet(var_r31->unk_02[var_r30], 0, 0, 0);
                    espTPLvlSet(var_r31->unk_02[var_r30], 0.5f);
                    break;
                case 2:
                    var_r31->unk_02[var_r30] = espEntry(lbl_1_data_86C[var_r27->unk_02[5]]);
                    espPriSet(var_r31->unk_02[var_r30], 255);
                    break;
                case 3:
                    var_r31->unk_02[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 0x33), 1, 0);
                    espPriSet(var_r31->unk_02[var_r30], 255);
                    break;
                default:
                    break;
            }
            espDispOff(var_r31->unk_02[var_r30]);
            espDrawNoSet(var_r31->unk_02[var_r30], 0);
            espAttrSet(var_r31->unk_02[var_r30], HUSPR_ATTR_NOANIM);
            espPosSet(var_r31->unk_02[var_r30], lbl_1_data_84C[var_r29][0] + lbl_1_data_81C[var_r30][0],
                lbl_1_data_84C[var_r29][1] + lbl_1_data_81C[var_r30][1]);
        }
    }

    HuDataDirClose(DATADIR_MGCONST);
    object->func = fn_1_A9C;
}

void fn_1_A9C(omObjData *object)
{
    s32 var_r31;
    UnkM404Struct *var_r30;
    s32 var_r29;
    UnkM404Struct3 *var_r28;
    omObjData **var_r27;

    var_r30 = object->data;
    switch (fn_1_38C()) {
        case 6:
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                for (var_r29 = 0; var_r29 < 6; var_r29++) {
                    espDispOn(var_r30[var_r31].unk_02[var_r29]);
                }
            }
            break;
        case 7:
            var_r27 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
            for (var_r29 = 0, var_r31 = 0; var_r31 < 4; var_r31++) {
                var_r28 = var_r27[var_r31]->data;
                var_r30[var_r31].unk_00 = var_r28->unk_58;
                if (var_r28->unk_00_field1) {
                    var_r29++;
                }
            }
            if ((var_r29 >= 4) && (lbl_1_bss_0 == 0)) {
                HuAudFXPlay(1325);
                lbl_1_bss_0 = 1;
            }
            if ((lbl_1_bss_0 == 0) && (lbl_1_data_88C < 0)) {
                lbl_1_data_88C = HuAudFXPlay(1324);
            }
            break;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        espBankSet(var_r30[var_r31].unk_02[3], var_r30[var_r31].unk_00 / 100);
        espBankSet(var_r30[var_r31].unk_02[4], (var_r30[var_r31].unk_00 / 10) % 10);
        espBankSet(var_r30[var_r31].unk_02[5], var_r30[var_r31].unk_00 % 10);
    }
}

void fn_1_CD0(void)
{
    HuMemDirectFree(lbl_1_bss_4C->data);
}

void fn_1_D00(Process *process)
{
    s32 var_r31;

    lbl_1_bss_38[0] = lbl_1_bss_38[1] = lbl_1_bss_38[2] = lbl_1_bss_38[3] = -1;
    lbl_1_bss_28[0] = lbl_1_bss_28[1] = lbl_1_bss_28[2] = lbl_1_bss_28[3] = -1;
    lbl_1_bss_20 = 0;
    omMakeGroupEx(process, 0, 4);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        omAddObjEx(process, 5, 10, 50, 0, fn_1_1344);
    }
}

void fn_1_DEC(void)
{
    s32 var_r31;
    omObjData **var_r30;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_1_553C(var_r30[var_r31]);
    }
}

s32 fn_1_E48(void)
{
    s32 var_r31;
    omObjData **var_r30;
    UnkM404Struct3 *var_r29;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = var_r30[var_r31]->data;
        if (!var_r29->unk_00_field0) {
            break;
        }
    }
    if (var_r31 < 4) {
        return 0;
    }
    return 1;
}

u16 fn_1_ED4(omObjData *object)
{
    UnkM404Struct3 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r31 = object->data;

    for (var_r28 = 0, var_r30 = 0; var_r30 < var_r31->unk_3C->bmp->sizeY; var_r30++) {
        for (var_r29 = 0; var_r29 < var_r31->unk_3C->bmp->sizeX; var_r29++) {
            if (!fn_1_607C(var_r31->unk_3C, var_r29, var_r30)) {
                var_r28++;
            }
        }
    }
    return var_r28;
}

s32 fn_1_F70(omObjData *object, float arg8)
{
    UnkM404Struct3 *var_r31;
    s32 var_r30;
    s32 var_r29;
    u16 var_r28;
    u16 var_r27;
    s32 var_r26;
    u16 var_r25;
    u16 var_r24;

    var_r31 = object->data;
    var_r26 = var_r31->unk_3C->bmp->sizeX * arg8;

    for (var_r30 = 0; var_r30 < var_r31->unk_3C->bmp->sizeY; var_r30++) {
        for (var_r29 = var_r31->unk_5A; var_r29 < var_r26; var_r29++) {
            if (!fn_1_607C(var_r31->unk_3C, var_r29, var_r30)) {
                for (var_r27 = 0; var_r27 < (var_r31->unk_4C->bmp->sizeY / var_r31->unk_3C->bmp->sizeY); var_r27++) {
                    for (var_r28 = 0; var_r28 < (var_r31->unk_4C->bmp->sizeX / var_r31->unk_3C->bmp->sizeX); var_r28++) {
                        var_r25 = ((s32)var_r28) + var_r31->unk_4C->bmp->sizeX * var_r29 / var_r31->unk_3C->bmp->sizeX;
                        var_r24 = ((s32)var_r27) + var_r31->unk_4C->bmp->sizeY * var_r30 / var_r31->unk_3C->bmp->sizeY;
                        if (fn_1_607C(var_r31->unk_4C, var_r25, var_r24)) {
                            var_r31->unk_54++;
                            break;
                        }
                    }
                    if (var_r28 < var_r31->unk_4C->bmp->sizeX / var_r31->unk_3C->bmp->sizeX) {
                        break;
                    }
                }
            }
        }
    }
    var_r31->unk_5A = var_r26;
    return (var_r31->unk_54 * 100) / var_r31->unk_56;
}

void fn_1_1160(void)
{
    s32 sp10[4];
    u16 sp8[3] = { 28, 18, 29 };
    s32 var_r31;
    s32 var_r30;
    UnkM404Struct3 *var_r29;
    omObjData **var_r28;
    s32 var_r27;
    s32 var_r26;
    UnkM404Struct3 *var_r25;
    s16 var_r24;

    var_r26 = 0;
    var_r28 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r29 = var_r28[var_r31]->data;
        for (var_r27 = 0, var_r30 = 0; var_r30 < 4; var_r30++) {
            if (var_r31 != var_r30) {
                var_r25 = var_r28[var_r30]->data;
                if (var_r29->unk_58 < var_r25->unk_58) {
                    var_r27++;
                }
            }
        }
        sp10[var_r31] = var_r27;
        if (var_r29->unk_58 > var_r26) {
            var_r26 = var_r29->unk_58;
        }
    }
    if (var_r26 > 30) {
        for (var_r30 = 0, var_r31 = 0; var_r31 < 4; var_r31++) {
            if (!sp10[var_r31]) {
                lbl_1_bss_38[var_r30] = var_r31;
                lbl_1_bss_28[var_r30] = GWPlayerCfg[lbl_1_bss_38[var_r30]].character;
                var_r30++;
            }
            var_r24 = sp10[var_r31];
            GWPlayerCoinWinSet(var_r31, var_r24);
        }
        return;
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        GWPlayerCoinWinSet(var_r31, 3);
    }
}

void fn_1_1344(omObjData *object)
{
    UnkM404Struct3 *var_r31;
    s32 var_r29;
    float(*var_r28)[2];
    s32 var_r24;
    ModelData *var_r22;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM404Struct3), MEMORY_DEFAULT_NUM);
    object->data = var_r31;
    memset(var_r31, 0, 484);
    var_r31->unk_02 = lbl_1_bss_20++;
    var_r31->unk_04 = GWPlayerCfg[var_r31->unk_02].pad_idx;

    var_r31->unk_0C = var_r24 = GWPlayerCfg[var_r31->unk_02].character;
    var_r31->unk_0E = GWPlayerCfg[var_r31->unk_02].diff;
    var_r31->unk_10 = GWPlayerCfg[var_r31->unk_02].group;
    object->model[0] = CharModelCreate(var_r24, 2);
    Hu3DModelShadowSet(object->model[0]);
    object->model[1] = Hu3DModelCreateFile(lbl_1_data_8B8[var_r24]);
    Hu3DModelHookSet(object->model[0], "test11_tex_we-itemhook-r", object->model[1]);
    var_r31->unk_2C = 0;

    for (var_r29 = 0; var_r29 < (u32)5; var_r29++) {
        if (!lbl_1_data_890[var_r29][1]) {
            object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_0C, lbl_1_data_890[var_r29][0]);
        }
        else {
            object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_0C, var_r31->unk_0C + lbl_1_data_890[var_r29][0]);
        }
    }
    Hu3DMotionSet(object->model[0], object->motion[0]);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_OVL_LOOP | HU3D_MOTATTR_OVL_PAUSE);
    CharModelVoiceEnableSet(var_r24, object->motion[1], 0);
    object->trans.x = -90.0f;
    object->trans.y = 0.0f;
    object->trans.z = -450.0f + (300.0f * var_r31->unk_02);
    object->rot.y = 90.0f;
    object->model[2] = Hu3DHookFuncCreate(fn_1_58E4);
    Hu3DModelPosSet(object->model[2], 0.0f, object->trans.y, object->trans.z);
    var_r22 = &Hu3DData[object->model[2]];
    var_r22->unk_120 = object;
    var_r31->unk_4C = fn_1_5D64(960, 64, 1);
    var_r31->unk_48 = 4096;
    var_r31->unk_44 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk_48, MEMORY_DEFAULT_NUM);
    DCInvalidateRange(var_r31->unk_44, var_r31->unk_48);
    var_r31->unk_48 = fn_1_6248(var_r31->unk_44, var_r31->unk_48);
    var_r31->unk_3C = HuSprAnimReadFile(lbl_1_data_8FC[lbl_1_bss_1C][0]);
    DCFlushRangeNoSync(var_r31->unk_3C->bmp->data, (var_r31->unk_3C->bmp->pixSize * (var_r31->unk_3C->bmp->sizeX * var_r31->unk_3C->bmp->sizeY)) / 8);
    var_r31->unk_54 = 0;
    var_r31->unk_56 = fn_1_ED4(object);
    var_r31->unk_40 = HuSprAnimReadFile(lbl_1_data_8FC[lbl_1_bss_1C][1]);
    var_r31->unk_50 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M404, 0x19));
    DCFlushRangeNoSync(var_r31->unk_50->bmp->data, (var_r31->unk_50->bmp->pixSize * (var_r31->unk_50->bmp->sizeX * var_r31->unk_50->bmp->sizeY)) / 8);
    Hu3DMotionOverlaySet(object->model[0], object->motion[2]);
    object->trans.y = 1500.0f;
    var_r31->unk_38 = var_r31->unk_02 * REFRESH_RATE / 2;
    CharModelDataClose(var_r31->unk_0C);
    if (GWPlayerCfg[var_r31->unk_02].iscom == 1) {
        var_r28 = lbl_1_data_8E8[lbl_1_bss_1C];
        var_r31->unk_6C = lbl_1_data_8F4[lbl_1_bss_1C];
        var_r31->unk_70 = HuMemDirectMallocNum(HEAP_SYSTEM, (var_r31->unk_6C + 3) * 8, MEMORY_DEFAULT_NUM);

        for (var_r29 = 0; var_r29 < var_r31->unk_6C; var_r29++, var_r28++) {
            var_r31->unk_70[var_r29][0] = 3000.0f * var_r28[0][0];
            var_r31->unk_70[var_r29][1] = object->trans.z - (200.0f * (var_r28[0][1] - 0.5f));
            if (var_r29 && var_r29 < (var_r31->unk_6C - 1)) {
                var_r31->unk_70[var_r29][0] += lbl_1_data_8D8[var_r31->unk_0E] * (s32)(frand() % 512 - 256) / 256;
                var_r31->unk_70[var_r29][1] += lbl_1_data_8D8[var_r31->unk_0E] * (s32)(frand() % 512 - 256) / 256;
            }
        }

        while (var_r29 < (var_r31->unk_6C + 3)) {
            var_r31->unk_70[var_r29][0] = var_r31->unk_70[var_r31->unk_6C - 1][0];
            var_r31->unk_70[var_r29][1] = var_r31->unk_70[var_r31->unk_6C - 1][1];
            var_r29++;
        }
        var_r31->unk_64 = 0.0f;
        var_r31->unk_68 = fn_1_2EBC(var_r31->unk_70[var_r31->unk_5E], 1.0f);
    }
    var_r31->unk_14 = 90.0f;
    var_r31->unk_74 = -1;
    object->func = fn_1_1AFC;
}

void fn_1_1AFC(omObjData *object)
{
    UnkM404Struct3 *var_r31;

    var_r31 = object->data;
    if (fn_1_38C() >= 1) {
        if (var_r31->unk_00_field2) {
            if (var_r31->unk_38 != 0) {
                if (--var_r31->unk_38 == 0) {
                    HuAudFXPlay(1327);
                }
            }
            if (object->trans.y > 0.0f) {
                var_r31->unk_24 = var_r31->unk_24 - (VERSION_NTSC ? 1.0000001f : 1.2f);
                object->trans.y += var_r31->unk_24;
                if (object->trans.y < 0.0f) {
                    object->trans.y = 0.0f;
                    omVibrate(var_r31->unk_02, 12, 6, 6);
                    HuAudFXPlay(1326);
                }
            }
            if (fn_1_38C() != 2) {
                return;
            }
            var_r31->unk_24 = 0.0f;
            object->func = fn_1_44A0;
            return;
        }
        if (var_r31->unk_38 == 0) {
            var_r31->unk_00_field2 = 1;
            var_r31->unk_38 = REFRESH_RATE / 2;
            return;
        }
        var_r31->unk_38--;
    }
}

float fn_1_1C80(float arg8, float arg9, float argA, float argB, float argC)
{
    float var_f31;
    float var_f30;
    float var_f29;

    var_f31 = 1.0f - arg8;
    var_f30 = var_f31 * var_f31;
    var_f29 = var_f31 * var_f31 * var_f31;
    return (arg8 * arg8 * arg8 * argC) + (3.0f * var_f31 * arg8 * arg8 * argB + (var_f29 * arg9 + 3.0f * var_f30 * arg8 * argA));
}

float fn_1_1D28(float arg8, float arg9, float argA, float argB, float argC)
{
    float var_f31;
    float var_f30;
    float var_f29;

    var_f31 = 3.0f * (-arg9 + argC + (3.0f * (argA - argB)));
    var_f30 = 2.0f * ((3.0f * (arg9 + argB)) - (6.0f * argA));
    var_f29 = 3.0f * (-arg9 + argA);
    return var_f31 * arg8 * arg8 + var_f30 * arg8 + var_f29;
}

float fn_1_1DF8(float arg0[], float arg8)
{
    float var_f31;
    float var_f30;

    var_f31 = fn_1_1D28(arg8, arg0[0], arg0[2], arg0[4], arg0[6]);
    var_f30 = fn_1_1D28(arg8, arg0[1], arg0[3], arg0[7], arg0[7]);

    return sqrtf(var_f31 * var_f31 + var_f30 * var_f30);
}

float fn_1_2184(float arg0[], float arg8)
{
    float sp158[1];
    float var_f31;
    float var_f26;
    float var_f21;
    float var_f20;
    float var_f19;
    s32 var_r31;

    var_f26 = 0.0f;
    var_f19 = 16.0f;
    var_f20 = (arg8 - var_f26) / var_f19;
    sp158[0] = var_f20 + var_f20;

    var_f21 = fn_1_1DF8(arg0, var_f26) + fn_1_1DF8(arg0, arg8);

    for (var_r31 = 1, var_f31 = var_f26 + var_f20; var_r31 < var_f19; var_r31 += 2, var_f31 += sp158[0]) {
        var_f21 += 4.0f * fn_1_1DF8(arg0, var_f31);
    }

    for (var_r31 = 2, var_f31 = var_f26 + sp158[0]; var_r31 < var_f19; var_r31 += 2, var_f31 += sp158[0]) {
        var_f21 += 2.0f * fn_1_1DF8(arg0, var_f31);
    }
    return (var_f20 / 3.0f) * var_f21;
}

float fn_1_2EBC(float arg0[], float arg8)
{
    float spF8;
    float var_f31;
    float var_f27;
    float var_f22;
    float var_f23;

    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r29 = 32;
    var_f31 = 0.0f;
    spF8 = 0.0f;

    var_f27 = arg8 - var_f31;
    var_f22 = var_f27 * (fn_1_1DF8(arg0, var_f31) + fn_1_1DF8(arg0, arg8)) / 2;

    for (var_r30 = 1; var_r30 <= var_r29; var_r30 *= 2) {
        for (var_f23 = 0.0f, var_r31 = 1; var_r31 <= var_r30; var_r31++) {
            var_f23 += fn_1_1DF8(arg0, var_f31 + var_f27 * (var_r31 - 0.5f));
        }
        var_f23 *= var_f27;
        spF8 = (var_f22 + (2.0f * var_f23)) / 3.0f;
        var_f27 /= 2;
        var_f22 = (var_f22 + var_f23) / 2;
    }
    return spF8;
}

float fn_1_3A38(float arg0[], float arg8, float arg9)
{
    volatile float sp40;
    volatile float sp3C;
    float var_f24;
    float var_f18;
    s32 var_r30;

    sp3C = 0.00001f;
    var_r30 = 0;
    do {
        var_f18 = fn_1_2EBC(arg0, arg8) - arg9;
        if (fabs(var_f24 = fn_1_1DF8(arg0, arg8)) < sp3C) {
            var_f24 = 1.0f;
        }
        sp40 = arg8;
        arg8 -= var_f18 / var_f24;
        var_r30++;
    } while (arg8 != sp40 && var_r30 < 16);
    return arg8;
}

float fn_1_3E2C(float arg8, float arg9, float argA) // same as in REL/m402Dll
{
    float var_f30;
    float var_f31;

    var_f31 = fmod(arg9 - arg8, 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f30 = fmod(arg8 + (argA * var_f31), 360.0);
    if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

void fn_1_3F30(omObjData *object)
{
    float var_f24;
    float var_f23;

    UnkM404Struct3 *var_r31;
    float *var_r30;

    var_r31 = object->data;
    if (var_r31->unk_5E < (var_r31->unk_6C - 1)) {
        if ((180.0f / REFRESH_RATE + var_r31->unk_64) >= var_r31->unk_68) {
            var_r31->unk_64 = 180.0f / REFRESH_RATE - (var_r31->unk_68 - var_r31->unk_64);
            var_r31->unk_5E += 3;
            var_r31->unk_68 = fn_1_2EBC(var_r31->unk_70[var_r31->unk_5E], 1.0f);
        }
        else {
            var_r31->unk_64 += 180.0f / REFRESH_RATE;
        }
        var_r31->unk_60 = fn_1_3A38(var_r31->unk_70[var_r31->unk_5E], var_r31->unk_60, var_r31->unk_64);
        var_r30 = var_r31->unk_70[var_r31->unk_5E];
        var_f24 = fn_1_1C80(var_r31->unk_60, var_r30[0], var_r30[2], var_r30[4], var_r30[6]) - 90.0f;
        var_f23 = fn_1_1C80(var_r31->unk_60, var_r30[1], var_r30[3], var_r30[5], var_r30[7]);
        var_r31->unk_14 = fn_1_3E2C(var_r31->unk_14, atan2d(var_f24 - object->trans.x, -(var_f23 - object->trans.z)), 0.1f);
        var_r31->unk_06 = (u8)(20.0 * sind(var_r31->unk_14));
        var_r31->unk_07 = (u8)(20.0 * cosd(var_r31->unk_14));
    }
    else {
        var_r31->unk_06 = 20;
        var_r31->unk_07 = 0;
    }
}

void fn_1_445C(int seId, s16 vol)
{
    MSM_SEPARAM param;

    param.flag = MSM_SEPARAM_VOL;
    param.vol = vol;
    msmSeSetParam(seId, &param);
}

void fn_1_44A0(omObjData *object)
{
    Vec sp8;
    float var_f31;

    UnkM404Struct3 *var_r31;
    ModelData *var_r29;
    s32 var_r28;
    s16 var_r27;

    var_r31 = object->data;
    var_r28 = -1;
    if (fn_1_38C() == 6) {
        object->func = fn_1_4C7C;
    }
    if (fn_1_38C() == 3 && !var_r31->unk_00_field0) {
        switch (var_r31->unk_12) {
            case 0:
                if (GWPlayerCfg[var_r31->unk_02].iscom == 0) {
                    var_r31->unk_06 = HuPadStkX[var_r31->unk_04];
                    var_r31->unk_07 = HuPadStkY[var_r31->unk_04];
                    var_r31->unk_08 = HuPadBtn[var_r31->unk_04];
                    var_r31->unk_0A = HuPadBtnDown[var_r31->unk_04];
                }
                else {
                    var_r31->unk_08 = var_r31->unk_0A = 0;
                    var_r31->unk_06 = var_r31->unk_07 = 0;
                    fn_1_3F30(object);
                }
                if (((var_r31->unk_06 * var_r31->unk_06) + (var_r31->unk_07 * var_r31->unk_07)) > 16.0f) {
                    var_f31 = atan2d(var_r31->unk_06, -var_r31->unk_07);
                    var_r31->unk_20 = (VERSION_NTSC ? 3.0 : 3.5999999046325684) * sind(var_f31);
                    var_r31->unk_28 = (VERSION_NTSC ? 3.0 : 3.5999999046325684) * cosd(var_f31);
                    var_r28 = 1;
                    if (var_r31->unk_20 > 0.0f) {
                        CharModelMotionSpeedSet(var_r31->unk_0C, 0.5f);
                    }
                    else {
                        CharModelMotionSpeedSet(var_r31->unk_0C, -0.5f);
                    }
                    Hu3DMotionOverlaySpeedSet(object->model[0], Hu3DData[object->model[0]].unk_68);
                    if (var_r31->unk_2C == 0) {
                        Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_OVL_PAUSE);
                        Hu3DMotionOverlayTimeSet(object->model[0], 0.0f);
                    }
                }
                else {
                    var_r31->unk_20 = var_r31->unk_28 = 0.0f;
                    var_r28 = 0;
                    CharModelMotionSpeedSet(var_r31->unk_0C, 1.0f);
                    Hu3DMotionOverlayTimeSet(object->model[0], 0.0f);
                    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_OVL_PAUSE);
                }
                sp8.x = object->trans.x;
                sp8.z = object->trans.z;
                object->trans.x += var_r31->unk_20;
                object->trans.z += var_r31->unk_28;
                if (object->trans.x < -90.0f) {
                    object->trans.x = -90.0f;
                }
                if (object->trans.x < (Center.x - 500.0f)) {
                    object->trans.x = Center.x - 500.0f;
                }
                else if (object->trans.x > (550.0f + Center.x)) {
                    object->trans.x = 550.0f + Center.x;
                }
                if ((object->trans.x != sp8.x) || (object->trans.z != sp8.z)) {
                    if (var_r31->unk_74 < 0) {
                        var_r31->unk_74 = HuAudFXPlay(0x52B);
                    }
                }
                else if (var_r31->unk_74 >= 0) {
                    HuAudFXStop(var_r31->unk_74);
                    var_r31->unk_74 = -1;
                }
                var_r29 = &Hu3DData[object->model[2]];
                if (object->trans.z < (var_r29->pos.z - 100.0f)) {
                    object->trans.z = var_r29->pos.z - 100.0f;
                }
                else if (object->trans.z > ((100.0f + var_r29->pos.z) - 1.0f)) {
                    object->trans.z = (100.0f + var_r29->pos.z) - 1.0f;
                }
                if ((90.0f + object->trans.x) > 3000.0f) {
                    object->trans.x = 2910.0f;
                    var_r31->unk_12++;
                    var_r31->unk_2C = -1;
                    var_r28 = 1;
                    CharModelMotionSpeedSet(var_r31->unk_0C, 1.0f);
                    Hu3DMotionOverlayReset(object->model[0]);
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
                    if (var_r31->unk_74 >= 0) {
                        HuAudFXStop(var_r31->unk_74);
                        var_r31->unk_74 = -1;
                    }
                }
                fn_1_5278(object);
                if (var_r31->unk_74 >= 0) {
                    var_r27 = 64.0f + ((64.0f * (object->trans.x - Center.x)) / 500.0f);
                    if (var_r27 < 0) {
                        var_r27 = 0;
                    }
                    else if (var_r27 > 127) {
                        var_r27 = 127;
                    }
                    HuAudFXPanning(var_r31->unk_74, var_r27);
                }
                break;
            case 1:
                var_r28 = 1;
                object->trans.x += VERSION_NTSC ? 4.0000005f : 4.8f;
                if (object->trans.x >= 3200.0f) {
                    var_r31->unk_12++;
                    var_r31->unk_38 = 0x3C;
                }
                break;
            case 2:
                var_r28 = 0;
                object->rot.y += 0.1f * -object->rot.y;
                if (--var_r31->unk_38 == 0) {
                    var_r31->unk_00_field0 = 1;
                }
                break;
        }
        if (var_r28 >= 0 && var_r28 != var_r31->unk_2C) {
            var_r31->unk_2C = var_r28;
            CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_2C], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        }
    }
}

void fn_1_4C7C(omObjData *object)
{
    UnkM404Struct3 *var_r30;

    var_r30 = object->data;
    object->trans.x = 3200.0f;
    object->trans.z = -450.0f + (300.0f * var_r30->unk_02);
    object->rot.y = 0.0f;
    var_r30->unk_2C = -1;
    CharModelMotionShiftSet(var_r30->unk_0C, *object->motion, 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    var_r30->unk_5A = 0;
    var_r30->unk_5C = fn_1_F70(object, 1.0f);
    var_r30->unk_5A = 0;
    var_r30->unk_54 = 0;
    var_r30->unk_74 = -1;
    object->func = fn_1_4F4C;
}

void fn_1_4F4C(omObjData *object)
{
    UnkM404Struct3 *var_r30;
    s32 var_r29;
    u16 var_r23;

    var_r30 = object->data;
    if (fn_1_38C() == 7) {
        var_r23 = fn_1_F70(object, (Center.x - lbl_1_data_738[1].unk_04) / (3000.0f - lbl_1_data_738[1].unk_04));
        if (!var_r30->unk_00_field1 && var_r23 == var_r30->unk_5C) {
            var_r30->unk_00_field1 = 1;
        }
        var_r30->unk_58 = var_r23;
    }
    if (fn_1_38C() == 9 && var_r30->unk_2C < 0) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if (var_r30->unk_02 == lbl_1_bss_38[var_r29]) {
                break;
            }
        }
        if (var_r29 < 4) {
            var_r30->unk_2C = 3;
        }
        else {
            var_r30->unk_2C = 4;
        }
        CharModelMotionShiftSet(var_r30->unk_0C, object->motion[var_r30->unk_2C], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
    }
}

void fn_1_5278(omObjData *object)
{
    float var_f31;
    UnkM404Struct3 *var_r31;
    float var_f30;
    ModelData *var_r27;
    s32 var_r29;
    s32 var_r28;
    u16 var_r26;
    u16 var_r25;

    var_r31 = object->data;
    var_r27 = &Hu3DData[object->model[2]];
    var_f31 = ((90.0f + object->trans.x) - var_r27->pos.x) / 3000.0f;
    var_f30 = (object->trans.z - (var_r27->pos.z - 100.0f)) / 200.0f;

    for (var_r29 = 0; var_r29 < var_r31->unk_50->bmp->sizeY; var_r29++) {
        for (var_r28 = 0; var_r28 < var_r31->unk_50->bmp->sizeX; var_r28++) {
            var_r26 = (var_r28 + (var_f31 * var_r31->unk_4C->bmp->sizeX)) - var_r31->unk_50->bmp->sizeX / 2;
            var_r25 = (var_r29 + (var_f30 * var_r31->unk_4C->bmp->sizeY)) - var_r31->unk_50->bmp->sizeY / 2;
            if (var_r26 < var_r31->unk_4C->bmp->sizeX && var_r25 < var_r31->unk_4C->bmp->sizeY) {
                fn_1_5E74(var_r31->unk_4C, var_r26, var_r25, fn_1_607C(var_r31->unk_50, var_r28, var_r29));
            }
        }
    }
    DCFlushRangeNoSync(var_r31->unk_4C->bmp->data, var_r31->unk_4C->bmp->dataSize);
}

void fn_1_553C(omObjData *object)
{
    UnkM404Struct3 *var_r30;

    var_r30 = object->data;
    if (object->data != NULL) {
        HuMemDirectFree(var_r30->unk_44);
        HuMemDirectFree(object->data);
        object->data = NULL;
    }
}

void fn_1_5598(Process *arg0)
{
    omMakeGroupEx(arg0, 1, 1);
    omAddObjEx(arg0, 10, 7, 0, 1, fn_1_55F4);
}

void fn_1_55F0(void) { }

s32 lbl_1_data_930[] = { DATA_MAKE_NUM(DATADIR_M404, 0x0B), DATA_MAKE_NUM(DATADIR_M404, 0x0C), DATA_MAKE_NUM(DATADIR_M404, 0x0D),
    DATA_MAKE_NUM(DATADIR_M404, 0x0E), DATA_MAKE_NUM(DATADIR_M404, 0x0F), DATA_MAKE_NUM(DATADIR_M404, 0x10), DATA_MAKE_NUM(DATADIR_M404, 0x11),
    DATA_MAKE_NUM(DATADIR_M404, 0x12) };

s32 lbl_1_data_950[] = { DATA_MAKE_NUM(DATADIR_M404, 0x1A), DATA_MAKE_NUM(DATADIR_M404, 0x1B), DATA_MAKE_NUM(DATADIR_M404, 0x1C),
    DATA_MAKE_NUM(DATADIR_M404, 0x1D), DATA_MAKE_NUM(DATADIR_M404, 0x1E), DATA_MAKE_NUM(DATADIR_M404, 0x1F), DATA_MAKE_NUM(DATADIR_M404, 0x20),
    DATA_MAKE_NUM(DATADIR_M404, 0x21) };

char *lbl_1_data_98C[] = { "kari00", "kari01", "kari02", "kari03" };

float lbl_1_data_99C[] = { -450, -150, 150, 450 };

s32 lbl_1_data_9AC[][2] = { { 8, 4 }, { 7, 8 }, { 6, 8 }, { 5, 16 }, { 2, 16 }, { 2, 16 } };

s32 lbl_1_data_9DC[] = { 8, 8, 8, 4, 4, 4 };
s32 lbl_1_data_9F4[] = { 8, 8, 8, 4, 4, 4 };

void fn_1_55F4(omObjData *object)
{
    s32 var_r30;

    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M404, 0x09));
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M404, 0x0A));
    Hu3DModelAttrSet(object->model[1], HU3D_MOTATTR_LOOP);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M404, 0x00));
    Hu3DModelShadowMapSet(object->model[2]);

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        object->model[var_r30 + 3] = Hu3DModelCreateFile(lbl_1_data_930[GWPlayerCfg[var_r30].character]);
        Hu3DModelPosSet(object->model[var_r30 + 3], 0.0f, 0.0f, lbl_1_data_99C[var_r30]);
        Hu3DAnimCreate(HuSprAnimReadFile(lbl_1_data_950[GWPlayerCfg[var_r30].character]), object->model[2], lbl_1_data_98C[var_r30]);
    }
    object->func = fn_1_57A0;
}

void fn_1_57A0(omObjData *object) { }

void fn_1_57A4(s32 arg0, GXColor *arg1)
{
    GXColor sp8[8] = { { 227, 67, 67, 255 }, { 68, 67, 227, 255 }, { 241, 158, 220, 255 }, { 67, 228, 68, 255 }, { 138, 60, 180, 255 },
        { 146, 85, 55, 255 }, { 227, 200, 20, 255 }, { 40, 40, 40, 255 } };

    *arg1 = sp8[arg0];
}

void fn_1_58E4(ModelData *modelData, Mtx arg1)
{
    GXTexObj sp3C;
    UnkM404Struct3 *var_r31;
    omObjData *var_r30;
    s32 var_r29;

    var_r30 = modelData->unk_120;
    var_r31 = var_r30->data;
    {
        GXColor sp18 = { 255, 0, 0, 255 };
        GXColor sp14 = { 255, 255, 255, 192 };
        GXLoadPosMtxImm(arg1, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
        HuSprTexLoad(var_r31->unk_40, 0, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_DIVIDE_2, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        var_r29 = var_r31->unk_0C;
        fn_1_57A4(var_r29, &sp18);

        GXSetChanMatColor(GX_COLOR0A0, sp18);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
        GXSetBlendMode(GX_DECAL, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetCullMode(GX_CULL_BACK);
        GXCallDisplayList(var_r31->unk_44, var_r31->unk_48);
        GXInitTexObj(&sp3C, var_r31->unk_4C->bmp->data, var_r31->unk_4C->bmp->sizeX, var_r31->unk_4C->bmp->sizeY, 1, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXLoadTexObj(&sp3C, GX_TEXMAP0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevColor(GX_TEVREG0, sp14);
        GXCallDisplayList(var_r31->unk_44, var_r31->unk_48);
    }
#ifdef TARGET_PC
    GXDestroyTexObj(&sp3C);
#endif
}

AnimData *fn_1_5D64(u16 sizeX, u16 sizeY, s32 arg2)
{
    AnimBmpData *bmp;
    AnimData *anim;

    anim = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(AnimBmpData), MEMORY_DEFAULT_NUM);
    bmp = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(AnimData), MEMORY_DEFAULT_NUM);
    anim->bmp = bmp;
    bmp->sizeX = sizeX;
    bmp->sizeY = sizeY;
    bmp->dataFmt = lbl_1_data_9AC[arg2][0];
    bmp->pixSize = lbl_1_data_9AC[arg2][1];
    bmp->dataSize = (bmp->pixSize * (bmp->sizeX * bmp->sizeY)) / 8;
    bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, bmp->dataSize, MEMORY_DEFAULT_NUM);
    memset(bmp->data, 0, bmp->dataSize);
    DCFlushRangeNoSync(bmp->data, bmp->dataSize);
    return anim;
}

void fn_1_5E74(AnimData *arg0, u16 arg1, u16 arg2, u16 arg3)
{
    u8 *var_r31;
    u16 var_r30;
    u16 var_r29;
    s32 var_r28;
    s32 temp_r0_2;
    s32 temp_r7;
    u8 temp_r0;

    switch (arg0->bmp->pixSize) {
        case 4:
            var_r30 = lbl_1_data_9DC[0]; // 8
            var_r29 = lbl_1_data_9DC[1]; // 8
            break;
        case 8:
            var_r30 = lbl_1_data_9DC[2]; // 8
            var_r29 = lbl_1_data_9DC[3]; // 4
            break;
        case 16:
            var_r30 = lbl_1_data_9DC[4]; // 4
            var_r29 = lbl_1_data_9DC[5]; // 4
            break;
    }

    var_r31 = (void *)(((arg1 / var_r30) * 32) + (((arg1 % 8) * arg0->bmp->pixSize) / 8)
        + (((arg0->bmp->sizeX / var_r30) * ((arg2 / var_r29) << 5)) + ((u32)arg0->bmp->data) + ((arg0->bmp->pixSize * ((arg2 % var_r29) * 8)) / 8)));

    switch (arg0->bmp->pixSize) {
        case 4:
            if ((arg1 & 1) == 0) {
                *var_r31 &= 0xF;
                *var_r31 |= arg3 << 4;
                break;
            }
            *var_r31 &= 0xF0;
            *var_r31 |= arg3;
            break;
        case 8:
            *var_r31 |= arg3;
            break;
        case 16:
            *((u16 *)var_r31) = arg3;
            break;
    }
}

u16 fn_1_607C(AnimData *arg0, u16 arg1, u16 arg2)
{
    u16 var_r31;
    u16 var_r30;
    u8 *var_r29;
    s32 var_r28;
    u32 temp_r0_2;
    u32 temp_r6;
    u8 temp_r0;
    u8 temp_r0_3;

    switch (arg0->bmp->pixSize) {
        case 4:
            var_r31 = lbl_1_data_9F4[0];
            var_r30 = lbl_1_data_9F4[1];
            break;
        case 8:
            var_r31 = lbl_1_data_9F4[2];
            var_r30 = lbl_1_data_9F4[3];
            break;
        case 16:
            var_r31 = lbl_1_data_9F4[4];
            var_r30 = lbl_1_data_9F4[5];
            break;
    }
    var_r29 = (void *)(((arg1 / var_r31) * 32) + (((arg1 % 8) * arg0->bmp->pixSize) / 8)
        + (((arg0->bmp->sizeX / var_r31) * ((arg2 / var_r30) << 5)) + ((u32)arg0->bmp->data) + ((arg0->bmp->pixSize * ((arg2 % var_r30) * 8)) / 8)));

    (void)var_r31;
    (void)var_r31;
    (void)var_r31;
    (void)var_r30;
    (void)var_r30;
    (void)var_r30;

    switch (arg0->bmp->pixSize) {
        case 4:
            if ((arg1 & 1) == 0) {
                var_r28 = *var_r29 >> 4;
            }
            else {
                var_r28 = *var_r29 & 0xF;
            }
            return var_r28;
        case 8:
            return *var_r29;
        case 16:
            return *((u16 *)var_r29);
    }
}

s32 fn_1_6248(void *arg0, s32 arg1)
{
    s32 var_r31;

    GXBeginDisplayList(arg0, arg1);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);

    GXPosition3f32(0.0f, 1.5f, 100.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(0.0f, 1.5f, -100.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(3000.0f, 1.5f, 100.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(3000.0f, 1.5f, -100.0f);
    GXTexCoord2f32(1.0f, 0.0f);

    var_r31 = GXEndDisplayList();
    DCFlushRangeNoSync(arg0, var_r31);
    return var_r31;
}

void fn_1_6440(omObjData *object)
{
    fn_1_648C(0, 0, 0.0f);
    object->func = fn_1_66DC;
}

void fn_1_648C(s32 arg0, s32 arg1, float arg8)
{
    CZoom = lbl_1_data_738[arg0].unk_00 + arg8 * (lbl_1_data_738[arg1].unk_00 - lbl_1_data_738[arg0].unk_00);
    Center.x = lbl_1_data_738[arg0].unk_04 + arg8 * (lbl_1_data_738[arg1].unk_04 - lbl_1_data_738[arg0].unk_04);
    Center.y = lbl_1_data_738[arg0].unk_08 + arg8 * (lbl_1_data_738[arg1].unk_08 - lbl_1_data_738[arg0].unk_08);
    Center.z = lbl_1_data_738[arg0].unk_0C + arg8 * (lbl_1_data_738[arg1].unk_0C - lbl_1_data_738[arg0].unk_0C);
    CRot.x = lbl_1_data_738[arg0].unk_10 + arg8 * (lbl_1_data_738[arg1].unk_10 - lbl_1_data_738[arg0].unk_10);
    CRot.y = lbl_1_data_738[arg0].unk_14 + arg8 * (lbl_1_data_738[arg1].unk_14 - lbl_1_data_738[arg0].unk_14);
    CRot.z = lbl_1_data_738[arg0].unk_18 + arg8 * (lbl_1_data_738[arg1].unk_18 - lbl_1_data_738[arg0].unk_18);
}

void fn_1_66DC(omObjData *object)
{
    CameraData *var_r31;

    var_r31 = Hu3DCamera;
    switch (fn_1_38C()) {
        case 1:
            fn_1_648C(0, 1, 1.0 - cosd(90.0f * lbl_1_bss_4));
            if (lbl_1_bss_4 < 1.0f) {
                lbl_1_bss_4 += VERSION_NTSC ? 0.007999999f : 0.0095999995f;
                if (lbl_1_bss_4 > 1.0f) {
                    lbl_1_bss_4 = 1.0f;
                }
            }
            break;
        case 3:
            Center.x += VERSION_NTSC ? 2.0000002f : 2.4f;
            Hu3DShadowData.unk_14.x = 1000.0f + var_r31->pos.x;
            Hu3DShadowData.unk_20.x = Hu3DShadowData.unk_14.x - 1500.0f;
            break;
        case 6:
            fn_1_648C(1, 1, 0.0f);
            break;
        case 7:
            if (Center.x < 3000.0f) {
                Center.x += VERSION_NTSC ? 25.0f : 30.0f;
            }
        default:
            break;
    }
}
