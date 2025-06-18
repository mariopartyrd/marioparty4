#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfload.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"

#include "REL/m406Dll.h"
#include <string.h>

#ifndef __MWERKS__
#include "game/frand.h"
#include "game/hsfex.h"
#endif

typedef struct UnkM406PlayerStruct {
    /* 0x00 */ float unk_00;
    /* 0x04 */ float unk_04;
} UnkM406PlayerStruct; /* size = 0x08 */

typedef struct UnkM406PlayerStruct2 {
    /* 0x00 */ Vec *unk_00;
    /* 0x04 */ HsfFace *unk_04;
    /* 0x08 */ s16 unk_08;
} UnkM406PlayerStruct2; /* size = 0x0C */

typedef struct M406PlayerWork {
    /* 0x00 */ union {
        struct {
            u8 unk_00_field0 : 1;
            u8 unk_00_field1 : 1;
            u8 unk_00_field2 : 1;
            u8 unk_00_field3 : 1;
            u8 unk_00_field4 : 1;
            u8 unk_00_field5 : 1;
        };
        s16 unk_00;
    };
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s8 unk_06;
    /* 0x07 */ s8 unk_07;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ Vec unk_14;
    /* 0x20 */ char unk20[0xC];
    /* 0x2C */ Vec unk_2C;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ u32 unk_3C;
    /* 0x40 */ float unk_40;
    /* 0x44 */ UnkM406PlayerStruct2 unk_44;
    /* 0x50 */ float unk_50;
    /* 0x54 */ float unk_54;
    /* 0x58 */ s16 unk_58;
    /* 0x5A */ s16 unk_5A;
    /* 0x5C */ s16 unk_5C;
    /* 0x5E */ s16 unk_5E;
    /* 0x60 */ s16 unk_60;
    /* 0x62 */ s16 unk_62;
    /* 0x64 */ s16 unk_64;
    /* 0x68 */ float unk_68;
    /* 0x6C */ float unk_6C;
    /* 0x70 */ float unk_70;
    /* 0x74 */ float unk_74;
    /* 0x78 */ float unk_78;
    /* 0x7C */ s32 unk_7C[2];
} M406PlayerWork; /* size = 0x84 */

void fn_1_1065C(omObjData *object);
void fn_1_10744(omObjData *object);
void fn_1_11058(omObjData *object);
void fn_1_114A0(omObjData *object);
void fn_1_117BC(float arg8, float arg9, UnkM406PlayerStruct2 *arg0, Vec *arg1);
float fn_1_12194(Vec *arg0);
void fn_1_12270(omObjData *object);
void fn_1_1275C();
s32 fn_1_127B8();
s32 fn_1_129E4(omObjData *object);
void fn_1_12AB8(omObjData *object);
void fn_1_12B00(omObjData *object);
void fn_1_12B38(Vec *arg0);
void fn_1_12BC4(omObjData *object);
void fn_1_13A88(s16 arg0, char *arg1, Mtx arg2);
float fn_1_13AF4(float arg8, float arg9, float argA);
s32 fn_1_13C10(Vec *arg0, Vec *arg1);
float fn_1_143F4(Vec *arg0, UnkM406PlayerStruct2 *arg1);
void fn_1_D90C(omObjData *object);
void fn_1_DD7C(omObjData *object, s32 arg1, float arg8, u32 arg2);
void fn_1_DE60(omObjData *object);
void fn_1_E214(omObjData *object);
void fn_1_F194(omObjData *object);
void fn_1_F694(omObjData *object);
void fn_1_FA50(ModelData *model, Mtx mtx);

Vec lbl_1_data_960[70] = {
    { -495.876f, 50.005f, -0.0f },
    { -500.023f, -2841.226f, -5007.74f },
    { -502.015f, -7170.411f, -12506.11f },
    { -515.622f, -8314.231f, -14487.27f },
    { -515.6f, -8761.908f, -15262.67f },
    { -508.661f, -9195.703f, -16014.02f },
    { -494.762f, -9629.499f, -16765.38f },
    { -473.947f, -10063.294f, -17516.73f },
    { -471.378f, -10495.727f, -18265.73f },
    { -495.719f, -10915.74f, -18993.21f },
    { -552.519f, -11337.781f, -19724.21f },
    { -621.485f, -11611.703f, -20198.66f },
    { -731.018f, -11887.653f, -20676.62f },
    { -950.131f, -12303.607f, -21397.07f },
    { -1209.766f, -12735.795f, -22145.64f },
    { -1469.474f, -13170.012f, -22897.73f },
    { -1627.69f, -13466.252f, -23410.83f },
    { -1757.595f, -13772.641f, -23941.51f },
    { -1838.731f, -14079.026f, -24472.19f },
    { -1871.186f, -14393.528f, -25016.92f },
    { -1834.734f, -14703.97f, -25554.62f },
    { -1749.541f, -15014.414f, -26092.33f },
    { -1623.78f, -15312.685f, -26608.94f },
    { -1384.433f, -15761.101f, -27385.62f },
    { -1124.798f, -16191.259f, -28130.68f },
    { -775.859f, -16769.535f, -29132.28f },
    { -568.923f, -17183.457f, -29849.22f },
    { -398.537f, -17621.73f, -30608.33f },
    { -187.485f, -18055.945f, -31360.41f },
    { 96.491f, -18634.223f, -32362.02f },
    { 254.886f, -19042.057f, -33068.41f },
    { 315.738f, -19315.977f, -33542.85f },
    { 331.965f, -19581.783f, -34003.24f },
    { 291.397f, -19839.473f, -34449.57f },
    { 189.969f, -20091.07f, -34885.35f },
    { -12.871f, -20340.645f, -35317.62f },
    { -325.245f, -20598.332f, -35763.96f },
    { -747.265f, -20870.219f, -36234.88f },
    { -1230.024f, -21152.258f, -36723.38f },
    { -2276.853f, -21730.535f, -37724.99f },
    { -2759.968f, -22028.799f, -38241.6f },
    { -3189.989f, -22343.3f, -38786.33f },
    { -3514.533f, -22669.979f, -39352.15f },
    { -3620.335f, -22840.408f, -39647.35f },
    { -3693.358f, -23018.965f, -39956.61f },
    { -3705.528f, -23193.463f, -40258.85f },
    { -3693.358f, -23367.96f, -40561.09f },
    { -3551.37f, -23698.695f, -41133.94f },
    { -3307.945f, -24019.275f, -41689.2f },
    { -2995.571f, -24323.633f, -42216.36f },
    { -2646.686f, -24621.904f, -42732.99f },
    { -1920.124f, -25200.174f, -43734.58f },
    { -1457.648f, -25612.07f, -44448.0f },
    { -1238.474f, -25871.78f, -44897.83f },
    { -1084.316f, -26137.584f, -45358.22f },
    { -958.555f, -26417.594f, -45843.21f },
    { -861.049f, -26697.596f, -46328.19f },
    { -783.97f, -26979.635f, -46816.69f },
    { -715.004f, -27261.672f, -47305.2f },
    { -617.584f, -27979.957f, -48549.3f },
    { -548.553f, -28700.271f, -49796.93f },
    { -491.712f, -29278.535f, -50798.51f },
    { -475.485f, -29856.814f, -51800.12f },
    { -479.514f, -30433.059f, -52798.2f },
    { -505.531f, -34619.363f, -60049.28f },
    { -513.632f, -34659.062f, -60100.39f },
    { -509.573f, -34721.215f, -60151.54f },
    { -509.589f, -34805.496f, -60191.15f },
    { -509.587f, -34970.055f, -60233.17f },
    { -509.591f, -45195.266f, -61377.84f },
};

Vec lbl_1_data_CA8[70] = {
    { 497.979f, 49.997f, 0.0f },
    { 501.235f, -2841.251f, -5007.79f },
    { 497.983f, -7170.06f, -12505.5f },
    { 479.876f, -8314.231f, -14487.27f },
    { 479.899f, -8761.908f, -15262.67f },
    { 486.837f, -9195.703f, -16014.02f },
    { 500.736f, -9629.499f, -16765.38f },
    { 521.552f, -10063.294f, -17516.73f },
    { 524.121f, -10495.727f, -18265.73f },
    { 503.13f, -10936.027f, -19028.35f },
    { 446.486f, -11379.887f, -19797.14f },
    { 364.665f, -11685.236f, -20326.02f },
    { 245.082f, -11987.438f, -20849.45f },
    { 18.48f, -12434.451f, -21623.7f },
    { -252.156f, -12875.162f, -22387.03f },
    { -497.617f, -13300.134f, -23123.1f },
    { -655.129f, -13580.305f, -23608.37f },
    { -768.419f, -13847.879f, -24071.83f },
    { -843.945f, -14131.193f, -24562.54f },
    { -875.687f, -14393.528f, -25016.92f },
    { -850.353f, -14653.739f, -25467.62f },
    { -768.533f, -14927.61f, -25941.98f },
    { -642.655f, -15201.48f, -26416.33f },
    { -428.664f, -15620.156f, -27141.5f },
    { -170.569f, -16051.424f, -27888.48f },
    { 188.182f, -16636.941f, -28902.62f },
    { 408.467f, -17083.947f, -29676.86f },
    { 572.186f, -17512.059f, -30418.37f },
    { 786.178f, -17940.18f, -31159.9f },
    { 1075.696f, -18525.695f, -32174.04f },
    { 1245.631f, -18972.703f, -32948.28f },
    { 1315.06f, -19274.898f, -33471.7f },
    { 1327.648f, -19592.842f, -34022.39f },
    { 1283.591f, -19907.637f, -34567.64f },
    { 1157.714f, -20235.021f, -35134.68f },
    { 887.077f, -20562.406f, -35701.73f },
    { 496.857f, -20883.496f, -36257.87f },
    { 31.029f, -21188.842f, -36786.75f },
    { -491.693f, -21487.889f, -37304.71f },
    { -1517.594f, -22057.664f, -38291.59f },
    { -1958.808f, -22331.527f, -38765.94f },
    { -2323.853f, -22595.953f, -39223.93f },
    { -2588.195f, -22850.938f, -39665.58f },
    { -2651.134f, -22964.264f, -39861.87f },
    { -2695.42f, -23074.441f, -40052.7f },
    { -2714.302f, -23187.768f, -40248.99f },
    { -2689.126f, -23316.832f, -40472.53f },
    { -2594.718f, -23552.928f, -40881.46f },
    { -2393.337f, -23814.195f, -41334.0f },
    { -2116.406f, -24081.771f, -41797.45f },
    { -1782.831f, -24371.38f, -42299.07f },
    { -1059.036f, -24941.158f, -43285.95f },
    { -561.404f, -25391.299f, -44065.62f },
    { -290.767f, -25709.24f, -44616.31f },
    { -108.245f, -26024.033f, -45161.55f },
    { 23.926f, -26323.088f, -45679.52f },
    { 130.922f, -26625.29f, -46202.95f },
    { 212.947f, -26918.023f, -46709.98f },
    { 275.886f, -27213.93f, -47222.51f },
    { 376.588f, -27941.104f, -48482.01f },
    { 452.187f, -28658.824f, -49725.14f },
    { 508.832f, -29241.193f, -50733.83f },
    { 521.5f, -29814.105f, -51726.14f },
    { 515.985f, -30433.059f, -52798.2f },
    { 503.81f, -34617.785f, -60046.38f },
    { 495.709f, -34657.49f, -60097.48f },
    { 499.768f, -34719.64f, -60148.64f },
    { 499.752f, -34803.92f, -60188.25f },
    { 499.754f, -34968.48f, -60230.3f },
    { 499.75f, -45193.69f, -61374.92f },
};

float lbl_1_data_FF0[4] = { -300.0f, -100.0f, 100.0f, 300.0f };

char *lbl_1_data_1068[4] = {
    "test11_tex_we-itemhook-l",
    "test11_tex_we-itemhook-r",
    "test11_tex_we-itemhook-fl",
    "test11_tex_we-itemhook-fr",
};

s32 lbl_1_data_1078[10] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x37),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x55),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x39),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x54),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x41),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x56),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x50),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x16),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x53),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x23),
};

s32 lbl_1_data_10A0[8][4] = {
    { DATA_MAKE_NUM(DATADIR_M406, 0), DATA_MAKE_NUM(DATADIR_M406, 1), DATA_MAKE_NUM(DATADIR_M406, 16), DATA_MAKE_NUM(DATADIR_M406, 17) },
    { DATA_MAKE_NUM(DATADIR_M406, 2), DATA_MAKE_NUM(DATADIR_M406, 3), DATA_MAKE_NUM(DATADIR_M406, 18), DATA_MAKE_NUM(DATADIR_M406, 19) },
    { DATA_MAKE_NUM(DATADIR_M406, 4), DATA_MAKE_NUM(DATADIR_M406, 5), DATA_MAKE_NUM(DATADIR_M406, 20), DATA_MAKE_NUM(DATADIR_M406, 21) },
    { DATA_MAKE_NUM(DATADIR_M406, 6), DATA_MAKE_NUM(DATADIR_M406, 7), DATA_MAKE_NUM(DATADIR_M406, 22), DATA_MAKE_NUM(DATADIR_M406, 23) },
    { DATA_MAKE_NUM(DATADIR_M406, 8), DATA_MAKE_NUM(DATADIR_M406, 9), DATA_MAKE_NUM(DATADIR_M406, 24), DATA_MAKE_NUM(DATADIR_M406, 25) },
    { DATA_MAKE_NUM(DATADIR_M406, 10), DATA_MAKE_NUM(DATADIR_M406, 11), DATA_MAKE_NUM(DATADIR_M406, 26), DATA_MAKE_NUM(DATADIR_M406, 27) },
    { DATA_MAKE_NUM(DATADIR_M406, 12), DATA_MAKE_NUM(DATADIR_M406, 13), DATA_MAKE_NUM(DATADIR_M406, 28), DATA_MAKE_NUM(DATADIR_M406, 29) },
    { DATA_MAKE_NUM(DATADIR_M406, 14), DATA_MAKE_NUM(DATADIR_M406, 15), DATA_MAKE_NUM(DATADIR_M406, 30), DATA_MAKE_NUM(DATADIR_M406, 31) },
};

s32 lbl_1_data_1120[8] = {
    DATA_MAKE_NUM(DATADIR_M406, 69),
    DATA_MAKE_NUM(DATADIR_M406, 70),
    DATA_MAKE_NUM(DATADIR_M406, 71),
    DATA_MAKE_NUM(DATADIR_M406, 72),
    DATA_MAKE_NUM(DATADIR_M406, 73),
    DATA_MAKE_NUM(DATADIR_M406, 74),
    DATA_MAKE_NUM(DATADIR_M406, 75),
    DATA_MAKE_NUM(DATADIR_M406, 76),
};

s16 lbl_1_data_1140[4] = { 0, 40, 20, 90 };

omObjData *lbl_1_bss_1F8;
s16 lbl_1_bss_1F6;
s16 lbl_1_bss_1F4;
s16 lbl_1_bss_1E8[6];
s16 lbl_1_bss_1DC[6];
s16 lbl_1_bss_1D0[6];
s32 lbl_1_bss_1CC;
Process *lbl_1_bss_1C8;
s32 lbl_1_bss_1C4;
Vec lbl_1_bss_104[16];
float lbl_1_bss_100;
s32 lbl_1_bss_F8[2];
Vec lbl_1_bss_E0[2];
s32 lbl_1_bss_DC;
s32 lbl_1_bss_D8;

void fn_1_D65C(Process *arg0)
{
    HsfMaterial *var_r31;
    s32 var_r30;
    s32 var_r29;
    HsfData *var_r28;
    omObjData **var_r26;
    ModelData *var_r25;
    s16 var_r24;

    lbl_1_bss_1CC = -1;
    lbl_1_bss_1F6 = lbl_1_bss_1F4 = 0;
    lbl_1_bss_1C8 = arg0;
    omMakeGroupEx(arg0, 0, 4);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        omAddObjEx(arg0, 0x40, 0xA, 0x32, 0, fn_1_D90C);
    }
    var_r24 = Hu3DHookFuncCreate(fn_1_FA50);
    Hu3DModelLayerSet(var_r24, 7);
    lbl_1_bss_1F8 = omAddObjEx(arg0, 0x45, 0, 0, -1, fn_1_12B00);
    var_r26 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
    for (var_r30 = 0; var_r30 < 6; var_r30++) {
        lbl_1_bss_1E8[var_r30] = lbl_1_bss_1DC[var_r30] = lbl_1_bss_1D0[var_r30] = -1;
        var_r25 = &Hu3DData[(*var_r26)->model[var_r30]];
        var_r28 = var_r25->hsfData;
        for (var_r29 = 0; var_r29 < var_r28->materialCnt; var_r29++) {
            var_r31 = &var_r28->material[var_r29];
            if (var_r31->color[0] == 0xFF && var_r31->color[1] == 0 && var_r31->color[2] == 0) {
                lbl_1_bss_1E8[var_r30] = var_r29;
            }
            if (var_r31->color[0] == 0 && var_r31->color[1] == 0xFF && var_r31->color[2] == 0) {
                lbl_1_bss_1D0[var_r30] = var_r29;
            }
            if (var_r31->color[0] == 0 && var_r31->color[1] == 0 && var_r31->color[2] == 0xFF) {
                lbl_1_bss_1DC[var_r30] = var_r29;
            }
        }
    }
}

void fn_1_D8B0(void)
{
    s32 var_r31;
    omObjData **var_r30;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_1_12AB8(var_r30[var_r31]);
    }
}

void fn_1_D90C(omObjData *object)
{
    Mtx sp8;

    M406PlayerWork *var_r31;
    s32 var_r29;
    s32 var_r28;

    object->data = var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M406PlayerWork), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(M406PlayerWork));
    var_r31->unk_02 = lbl_1_bss_1F6++;
    var_r31->unk_00_field0 = 0;
    var_r31->unk_00_field1 = 1;
    var_r31->unk_04 = GWPlayerCfg[var_r31->unk_02].pad_idx;
    var_r28 = var_r31->unk_0C = GWPlayerCfg[var_r31->unk_02].character;
    var_r31->unk_0E = GWPlayerCfg[var_r31->unk_02].diff;
    var_r31->unk_10 = GWPlayerCfg[var_r31->unk_02].group;
    object->model[0] = CharModelCreate(var_r28, 8);
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        object->model[var_r29 + 1] = Hu3DModelCreateFile(lbl_1_data_10A0[var_r28][var_r29]);
        Hu3DModelHookSet(object->model[0], lbl_1_data_1068[var_r29], object->model[var_r29 + 1]);
    }
    Hu3DModelShadowSet(object->model[0]);
    CharModelLayerSetAll(Hu3DData[object->model[0]].layer + 1);
    object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 32));
    Hu3DModelHookSet(object->model[0], "test11_tex_we-itemhook-body", object->model[5]);
    Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF);
    fn_1_13A88(object->model[0], "test11_tex_we-itemhook-body", sp8);
    var_r31->unk_68 = sp8[0][3];
    var_r31->unk_6C = sp8[1][3];
    var_r31->unk_70 = sp8[2][3];
    object->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 33));
    Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF);
    object->model[7] = Hu3DModelCreateFile(lbl_1_data_1120[var_r31->unk_0C]);
    Hu3DModelAttrSet(object->model[7], HU3D_ATTR_DISPOFF);
    for (var_r29 = 0; var_r29 < 10U; var_r29++) {
        object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_0C, lbl_1_data_1078[var_r29]);
    }
    var_r31->unk_38 = -1;
    var_r31->unk_58 = 0;
    var_r31->unk_14.y = 0.0f;
    var_r31->unk_14.z = 45.0f;
    fn_1_DD7C(object, 0, 1.0f, HU3D_MOTATTR_LOOP);
    object->trans.x = lbl_1_data_FF0[var_r31->unk_02];
    object->trans.z = -500.0f;
    object->trans.y = fn_1_143F4(&object->trans, &var_r31->unk_44);
    fn_1_117BC(var_r31->unk_14.x, 50.0f, &var_r31->unk_44, &var_r31->unk_2C);
    object->rot.x = 30.0f;
    object->rot.y = 180.0f;
    object->work[3] = lbl_1_data_1140[var_r31->unk_02];
    CharModelDataClose(var_r31->unk_0C);
    var_r31->unk_7C[0] = var_r31->unk_7C[1] = -1;
    var_r31->unk_78 = 600.0f * ((frand() & 0x1FF) - 256.0f) / 256.0f;
    object->func = fn_1_DE60;
}

Vec lbl_1_data_1164[12] = {
    { -100.0f, 0.0f, -1000.0f },
    { -200.0f, 0.0f, -2000.0f },
    { -100.0f, 0.0f, -3000.0f },
    { -50.0f, 0.0f, -1000.0f },
    { 100.0f, 0.0f, -1500.0f },
    { 0.0f, 0.0f, -3000.0f },
    { 100.0f, 0.0f, -1000.0f },
    { -100.0f, 0.0f, -2000.0f },
    { 200.0f, 0.0f, -3000.0f },
    { 200.0f, 0.0f, -1000.0f },
    { 300.0f, 0.0f, -1500.0f },
    { -100.0f, 0.0f, -3000.0f },
};

s32 lbl_1_data_11F4 = 0xC0;

UnkM406PlayerStruct lbl_1_data_11F8[4] = {
    { -300.0f, -600.0f },
    { -100.0f, -400.0f },
    { 100.0f, -300.0f },
    { 450.0f, -900.0f },
};

UnkM406PlayerStruct lbl_1_data_1218[3] = {
    { -320.0f, -700.0f },
    { 250.0f, -1000.0f },
    { 380.0f, -500.0f },
};

void fn_1_DD7C(omObjData *object, s32 arg1, float arg8, u32 arg2)
{
    ModelData *spC;
    M406PlayerWork *var_r31;

    var_r31 = object->data;
    spC = &Hu3DData[object->model[0]];
    if (arg1 != var_r31->unk_38) {
        CharModelMotionShiftSet(var_r31->unk_0C, object->motion[arg1], 0.0f, 10.0f, arg2);
        var_r31->unk_40 = -1.0f;
        var_r31->unk_38 = arg1;
        var_r31->unk_3C = arg2;
    }
    if (arg8 != var_r31->unk_40) {
        CharModelMotionSpeedSet(var_r31->unk_0C, 1.0f);
    }
}

void fn_1_DE60(omObjData *object)
{
    float sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;

    M406PlayerWork *var_r30;
    Vec *var_r29;

    var_r30 = object->data;
    if (var_r30->unk_00_field4 == 0) {
        if (fn_1_122C() <= 1 && var_r30->unk_7C[0] < 0) {
            var_r30->unk_7C[0] = HuAudFXEmiterPlay(0x53A, &object->trans);
        }
        if (object->work[3] != 0) {
            object->work[3] -= 1;
            return;
        }
        var_r29 = &lbl_1_data_1164[object->work[0] + (var_r30->unk_02 * 3)];
        var_f31 = var_r29->x - object->trans.x;
        var_f30 = var_r29->z - object->trans.z;
        var_f27 = atan2d(-var_f31, -var_f30);
        var_r30->unk_14.x += 0.1f * (var_f27 - var_r30->unk_14.x);
        var_f26 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
        if (var_f26 < 100.0f) {
            object->work[0]++;
            if (object->work[0] > 2) {
                var_r30->unk_00_field4 = 1;
                var_r30->unk_14.x = 0.0f;
                object->trans.x = lbl_1_data_FF0[var_r30->unk_02];
                object->trans.z = -3000.0f;
                object->trans.y = fn_1_143F4(&object->trans, &var_r30->unk_44);
                fn_1_117BC(var_r30->unk_14.x, 50.0f, &var_r30->unk_44, &var_r30->unk_2C);
                object->func = fn_1_E214;
            }
        }
        fn_1_F694(object);
        object->trans.x += var_r30->unk_2C.x;
        object->trans.y += var_r30->unk_2C.y;
        object->trans.z += var_r30->unk_2C.z;
        object->trans.y = fn_1_143F4(&object->trans, &var_r30->unk_44);
        object->rot.x = 30.0f;
        object->rot.y = 180.0f + var_r30->unk_14.x;
        HuAudFXEmiterUpDate(var_r30->unk_7C[0], &object->trans);
    }
}

void fn_1_E214(omObjData *object)
{
    Mtx sp94;
    Mtx sp64;
    Mtx sp34;
    Vec sp28;
    Vec sp1C;

    float var_f31;
    float var_f30;
    float var_f29;
    double var_f28;

    M406PlayerWork *var_r31;
    u16 var_r27;
    ModelData *var_r26;
    u16 var_r25;
    s32 var_r24;
    s16 var_r23;
    s16 var_r22;

    var_r31 = object->data;
    var_r27 = 0xFFFF;
    var_r25 = 0;
    var_r26 = &Hu3DData[object->model[0]];

    if (fn_1_122C() >= 2) {
        if (var_r31->unk_00_field0 != 0) {
            fn_1_DD7C(object, 9, 1.0f, HU3D_MOTATTR_NONE);
            if ((var_r26->attr & 1) == 0) {
                Hu3D3Dto2D(&object->trans, 1, &sp28);
                if (sp28.x < 0.0 || sp28.x >= 576.0f || sp28.y < 0.0 || sp28.y >= 480.0f) {
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
                }
            }
            return;
        }
        if (fn_1_122C() != 4) {
            var_r31->unk_08 = var_r31->unk_0A = 0;
            var_r31->unk_06 = var_r31->unk_07 = 0;
        }
        else if (!GWPlayerCfg[var_r31->unk_02].iscom) {
            var_r31->unk_06 = HuPadStkX[var_r31->unk_04];
            var_r31->unk_07 = HuPadStkY[var_r31->unk_04];
            var_r31->unk_08 = HuPadBtn[var_r31->unk_04];
            var_r31->unk_0A = HuPadBtnDown[var_r31->unk_04];
        }
        else {
            var_r31->unk_08 = var_r31->unk_0A = 0;
            var_r31->unk_06 = var_r31->unk_07 = 0;
            fn_1_12270(object);
        }
        switch (var_r31->unk_12) {
            case 0:
                var_r23 = (var_r31->unk_06 * cosd(CRot.y)) - var_r31->unk_07 * sind(CRot.y);
                var_r22 = (var_r31->unk_06 * sind(CRot.y)) + var_r31->unk_07 * cosd(CRot.y);
                if (((var_r23 * var_r23) + (var_r22 * var_r22)) > 16.0f) {
                    var_f29 = 180.0 + (atan2d(var_r23, -var_r22));
                    var_r31->unk_14.x = fn_1_13AF4(var_r31->unk_14.x, var_f29, 0.05f);
                    if (var_r31->unk_14.x >= 180.0f) {
                        var_r31->unk_14.x -= 360.0f;
                    }
                    if (var_r31->unk_14.x < -60.0f) {
                        var_r31->unk_14.x = -60.0f;
                    }
                    else if (var_r31->unk_14.x > 60.0f) {
                        var_r31->unk_14.x = 60.0f;
                    }
                }
                var_r27 = 0;
                var_f31 = 1.0f;
                var_r25 = 1;
                if (var_r31->unk_00_field2 == 0 && var_r31->unk_58 == 0 && var_r31->unk_0A & 0x100) {
                    var_r31->unk_58 = 0x1E;
                    var_r31->unk_38 = -1;
                    var_r31->unk_62 = 0;
                }
                if (var_r31->unk_58 != 0) {
                    var_r27 = 1;
                    var_f31 = 1.0f;
                    var_r25 = 0;
                    var_r31->unk_58--;
                    if (var_r31->unk_58 == 5) {
                        HuAudFXPlay(0x540);
                        fn_1_117BC(var_r31->unk_14.x, 10.0f, &var_r31->unk_44, &sp1C);
                        VECAdd(&var_r31->unk_2C, &sp1C, &var_r31->unk_2C);
                    }
                }
                if (var_r31->unk_00_field2 == 0) {
                    if (var_r31->unk_44.unk_08 == 1) {
                        var_r31->unk_00_field2 = 1;
                        var_r31->unk_60 = 0x14;
                        VECScale(&var_r31->unk_2C, &var_r31->unk_2C, 1.5f);
                        if (VECMag(&var_r31->unk_2C) > 50.0f) {
                            VECNormalize(&var_r31->unk_2C, &var_r31->unk_2C);
                            VECScale(&var_r31->unk_2C, &var_r31->unk_2C, 50.0f);
                        }
                        HuAudFXPlay(0x53E);
                        HuAudFXVolSet(var_r31->unk_7C[0], 0);
                        HuAudCharVoicePlay(var_r31->unk_0C, 0x125);
                    }
                    if (fn_1_122C() == 4) {
                        var_r31->unk_62++;
                        if (var_r31->unk_62 > 240.0f) {
                            var_r31->unk_62 = 240;
                        }
                    }
                }
                else {
                    var_r27 = 4;
                    var_f31 = 2.0f;
                    var_r25 = 0;
                    if (var_r31->unk_60 == 0 && var_r31->unk_00_field1 != 0) {
                        var_r31->unk_00_field2 = 0;
                        HuAudFXPlay(0x53D);
                        HuAudFXVolSet(var_r31->unk_7C[0], 127);
                    }
                    if (var_r31->unk_60 != 0) {
                        var_r31->unk_60--;
                    }
                }
                if (fn_1_129E4(object) != 0) {
                    var_r31->unk_00_field3 = 1;
                    var_r31->unk_12 = 1;
                    var_r31->unk_5A = 10;
                    var_r31->unk_54 = 1.0f;
                    var_r31->unk_78 = 0.0f;
                    var_r31->unk_62 = 0;
                    fn_1_117BC(var_r31->unk_14.x, 50.0f, &var_r31->unk_44, &var_r31->unk_2C);
                    omVibrate(var_r31->unk_02, 12, 6, 6);
                    var_r31->unk_7C[1] = HuAudFXPlay(0x53C);
                }
                break;
            case 1:
                var_r27 = 6;
                var_f31 = 1.0f;
                var_r25 = 0;
                if (--var_r31->unk_5A == 0) {
                    var_r31->unk_12 = 2;
                    var_r31->unk_5A = 60;
                }
                break;
            case 2:
                Hu3DModelAttrReset(object->model[5], HU3D_ATTR_DISPOFF);
                if (var_r31->unk_5A < 20) {
                    var_r31->unk_54 = var_r31->unk_5A / 20.0f;
                }
                else {
                    var_r31->unk_54 = 1.0f;
                }
                var_f30 = (0x3C - var_r31->unk_5A) / 10.0f;
                if (var_f30 > 1.0f) {
                    var_f30 = 1.0f;
                }
                Hu3DModelScaleSet(object->model[5], var_f30, var_f30, var_f30);
                var_r31->unk_50 += VECMag(&var_r31->unk_2C) / 3.125f;
                MTXTrans(sp94, -var_r31->unk_68, -var_r31->unk_6C, -var_r31->unk_70);
                MTXRotRad(sp64, 0x78, 0.017453292f * var_r31->unk_50);
                MTXConcat(sp64, sp94, sp34);
                MTXTrans(sp94, var_r31->unk_68, var_r31->unk_6C, var_r31->unk_70);
                MTXConcat(sp94, sp34, var_r26->unk_F0);
                var_r27 = 6;
                var_f31 = 2.0f;
                var_r25 = 0;
                if (--var_r31->unk_5A == 0) {
                    var_r31->unk_12 = 3;
                    if (var_r31->unk_7C[1] >= 0) {
                        HuAudFXStop(var_r31->unk_7C[1]);
                        var_r31->unk_7C[1] = -1;
                    }
                }
                break;
            case 3:
                if (var_r31->unk_5E == 0 && var_r31->unk_0A & 0x100) {
                    var_r31->unk_5E = 8;
                }
                if (var_r31->unk_00_field1) {
                    var_r31->unk_2C.x = var_r31->unk_2C.y = var_r31->unk_2C.z = 0.0f;
                }
                var_r31->unk_50 = fn_1_13AF4(var_r31->unk_50, 0.0f, 0.5f);
                MTXTrans(sp94, -var_r31->unk_68, -var_r31->unk_6C, -var_r31->unk_70);
                MTXRotRad(sp64, 0x78, 0.017453292f * var_r31->unk_50);
                MTXConcat(sp64, sp94, sp34);
                MTXTrans(sp94, var_r31->unk_68, var_r31->unk_6C, var_r31->unk_70);
                MTXConcat(sp94, sp34, var_r26->unk_F0);
                if (var_r31->unk_5E != 0) {
                    MTXTrans(sp94, 100.0f * (0.2f * (((var_r31->unk_5E & 1) * 2) - 1)), 0.0f, 0.0f);
                    MTXConcat(sp94, var_r26->unk_F0, var_r26->unk_F0);
                    if (--var_r31->unk_5E == 0) {
                        if (++var_r31->unk_5C >= 4) {
                            var_r31->unk_00_field3 = 0;
                            var_r31->unk_12 = 0;
                            var_r31->unk_5C = 0;
                            Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF);
                            Hu3DData[object->model[6]].unk_64 = 0.0f;
                            Hu3DModelPosSet(object->model[6], object->trans.x + var_r31->unk_68, object->trans.y + var_r31->unk_6C,
                                object->trans.z + var_r31->unk_70);
                            Hu3DModelAttrReset(object->model[6], HU3D_ATTR_DISPOFF);
                            MTXIdentity(var_r26->unk_F0);
                            fn_1_117BC(var_r31->unk_14.x, 25.0f, &var_r31->unk_44, &var_r31->unk_2C);
                        }
                    }
                }
                var_r27 = 7;
                var_f31 = 1.0f;
                var_r25 = 1;
                break;
        }
        if (Hu3DMotionEndCheck(object->model[6])) {
            Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF);
        }
        fn_1_DD7C(object, var_r27, var_f31, var_r25);
        fn_1_F194(object);
        if (object->trans.z + var_r31->unk_2C.z < -60000.0f) {
            lbl_1_bss_1CC = var_r31->unk_02;
            return;
        }
        sp28.x = object->trans.x;
        sp28.y = object->trans.y;
        sp28.z = object->trans.z;
        if (fn_1_6A44(sp28) == 1) {
            var_r31->unk_00_field0 = 1;
            var_r26 = &Hu3DData[object->model[0]];
            MTXIdentity(var_r26->unk_F0);
            omVibrate(var_r31->unk_02, 0xC, 4, 2);
            HuAudCharVoicePlayPos(var_r31->unk_0C, 0x123, &object->trans);
            for (var_r24 = 0; var_r24 < 2; var_r24++) {
                if (var_r31->unk_7C[var_r24] >= 0) {
                    HuAudFXStop(var_r31->unk_7C[var_r24]);
                    var_r31->unk_7C[var_r24] = -1;
                }
            }
        }
        object->rot.y = 180.0f + var_r31->unk_14.x;
    }
}

void fn_1_F194(omObjData *object)
{
    Mtx sp80;
    Mtx sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    M406PlayerWork *var_r31;
    ModelData *var_r30;

    var_r31 = object->data;
    var_r30 = &Hu3DData[object->model[0]];
    if (var_r31->unk_00_field1 && var_r31->unk_44.unk_00 != NULL) {
        var_f27 = !var_r31->unk_00_field3 ? 0.7f : 3.5f;
        sp44.x = 0.0f;
        sp44.y = -0.27222222f;
        sp44.z = 0.0f;
        var_f28 = 0.27222222f * var_r31->unk_44.unk_00[3].y;
        VECScale(&var_r31->unk_44.unk_00[3], &sp38, var_f28);
        VECAdd(&sp44, &sp38, &sp2C);
        VECAdd(&var_r31->unk_2C, &sp2C, &var_r31->unk_2C);
        sp20.x = sp20.y = sp20.z = 0.0f;
        sp14.x = sp14.y = sp14.z = 0.0f;
        var_f29 = VECMag(&var_r31->unk_2C);
        if (var_f29 > 0.0f && fn_1_122C() == 4) {
            VECNormalize(&var_r31->unk_2C, &sp8);
            sp20.x = -sp8.x;
            sp20.y = -sp8.y;
            sp20.z = -sp8.z;
            if (var_r31->unk_62 < 120.0f) {
                VECScale(&sp20, &sp20, var_f28 * var_f27);
            }
            else {
                VECScale(&sp20, &sp20, (0.15f * (var_r31->unk_62 / 240.0f)) + (var_f28 * var_f27));
            }
            if (!var_r31->unk_00_field3) {
                fn_1_117BC(var_r31->unk_14.x, 1.0f, &var_r31->unk_44, &sp44);
                var_f30 = VECDotProduct(&sp44, &sp8);
                var_f31 = 0.02f * var_f29;
                sp14.x = (-sp8.x * var_f31) - (var_f30 * (-sp44.x * var_f31));
                sp14.y = (-sp8.y * var_f31) - (var_f30 * (-sp44.y * var_f31));
                sp14.z = (-sp8.z * var_f31) - (var_f30 * (-sp44.z * var_f31));
                if ((var_f30 < 0.9f) && (var_f29 >= 20.0f)) {
                    mtxRot(sp80, var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
                    mtxTransCat(sp80, var_r30->pos.x, var_r30->pos.y, var_r30->pos.z);
                    VECCrossProduct(&sp44, &sp8, &sp44);
                    if (sp44.y >= 0.0f) {
                        MTXTrans(sp50, -10.0f, 0.0f, 0.0f);
                        MTXConcat(sp50, sp80, sp80);
                        fn_1_94C0(sp80, 10, 0);
                    }
                    else {
                        MTXTrans(sp50, 10.0f, 0.0f, 0.0f);
                        MTXConcat(sp50, sp80, sp80);
                        fn_1_94C0(sp80, 10, 1);
                    }
                }
            }
        }
        VECAdd(&sp20, &sp14, &sp2C);
        if (VECMag(&sp2C) > var_f29) {
            var_r31->unk_2C.x = var_r31->unk_2C.y = var_r31->unk_2C.z = 0.0f;
            return;
        }
        VECAdd(&var_r31->unk_2C, &sp2C, &var_r31->unk_2C);
        return;
    }
    var_r31->unk_2C.y += -0.27222222f;
}

void fn_1_F694(omObjData *object)
{
    Mtx sp68;
    Mtx sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    M406PlayerWork *var_r31;
    ModelData *var_r30;

    var_r31 = object->data;
    var_r30 = &Hu3DData[object->model[0]];
    var_r31->unk_2C.y += -1.0f;
    if (var_r31->unk_00_field1 && var_r31->unk_44.unk_00 != NULL) {
        sp2C.x = var_r31->unk_2C.x;
        sp2C.y = var_r31->unk_2C.y;
        sp2C.z = var_r31->unk_2C.z;

        var_f30 = -((var_r31->unk_44.unk_00[3].z * sp2C.z) + ((var_r31->unk_44.unk_00[3].x * sp2C.x) + (var_r31->unk_44.unk_00[3].y * sp2C.y)));

        sp2C.x += var_f30 * var_r31->unk_44.unk_00[3].x;
        sp2C.y += var_f30 * var_r31->unk_44.unk_00[3].y;
        sp2C.z += var_f30 * var_r31->unk_44.unk_00[3].z;
        if (!var_r31->unk_00_field3) {
            fn_1_117BC(var_r31->unk_14.x, 1.0f, &var_r31->unk_44, &sp20);
            VECNormalize(&sp2C, &sp14);
            var_f29 = VECDotProduct(&sp20, &sp14);
            var_f31 = var_f29 * var_f29;
            var_f31 *= var_f31;
            if (var_f31 < 0.999f && VECMag(&var_r31->unk_2C) >= 10.0f) {
                mtxRot(sp68, var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
                mtxTransCat(sp68, var_r30->pos.x, var_r30->pos.y, var_r30->pos.z);
                VECCrossProduct(&sp20, &sp14, &sp8);
                if (sp8.y >= 0.0f) {
                    MTXTrans(sp38, -10.0f, 0.0f, 0.0f);
                    MTXConcat(sp38, sp68, sp68);
                    fn_1_94C0(sp68, 10, 0);
                }
                else {
                    MTXTrans(sp38, 10.0f, 0.0f, 0.0f);
                    MTXConcat(sp38, sp68, sp68);
                    fn_1_94C0(sp68, 10, 1);
                }
            }
            var_f28 = VECMag(&sp2C);
            VECScale(&sp20, &sp20, var_f28);
            var_r31->unk_2C.x = sp2C.x + (0.9f * (sp20.x - sp2C.x));
            var_r31->unk_2C.y = sp2C.y + (0.9f * (sp20.y - sp2C.y));
            var_r31->unk_2C.z = sp2C.z + (0.9f * (sp20.z - sp2C.z));
        }
        else {
            var_r31->unk_2C.x = sp2C.x;
            var_r31->unk_2C.y = sp2C.y;
            var_r31->unk_2C.z = sp2C.z;
            VECScale(&var_r31->unk_2C, &var_r31->unk_2C, var_r31->unk_54);
        }
        VECScale(&var_r31->unk_2C, &var_r31->unk_2C, 0.98f);
    }
}

void fn_1_FA50(ModelData *model, Mtx mtx)
{
    omObjData *sp2C[4];
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;

    M406PlayerWork *var_r31;
    omObjData *var_r30;
    s32 var_r29;
    omObjData **var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    omObjData *var_r24;
    omObjData *var_r23;
    M406PlayerWork *var_r22;
    M406PlayerWork *var_r21;

    if (omPauseChk() == 0) {
        var_r28 = omGetGroupMemberListEx(lbl_1_bss_1C8, 0);
        switch (lbl_1_bss_D8) {
            case 0:
                if (--lbl_1_data_11F4 == 0) {
                    fn_1_123C();
                    lbl_1_bss_D8++;
                    lbl_1_bss_F8[0] = lbl_1_bss_F8[1] = 0;
                }
                if ((lbl_1_data_11F4 % 6) == 0) {
                    for (var_r29 = 0; var_r29 < 4; var_r29++) {
                        var_r31 = var_r28[var_r29]->data;
                        omVibrate(var_r31->unk_02, 6, 2, 4);
                    }
                    return;
                }
                break;
            case 1:
                if (lbl_1_bss_1CC >= 0) {
                    fn_1_1274(lbl_1_bss_1CC);
                    for (var_r29 = 0; var_r29 < 4; var_r29++) {
                        var_r30 = var_r28[var_r29];
                        var_r31 = var_r30->data;
                        if (var_r29 == lbl_1_bss_1CC) {
                            var_r30->func = fn_1_1065C;
                        }
                        else {
                            var_r30->func = fn_1_11058;
                        }
                        Hu3DModelAttrSet(*var_r30->model, HU3D_ATTR_DISPOFF);
                        for (var_r26 = 0; var_r26 < 2; var_r26++) {
                            if (var_r31->unk_7C[var_r26] >= 0) {
                                HuAudFXStop(var_r31->unk_7C[var_r26]);
                                var_r31->unk_7C[var_r26] = -1;
                            }
                        }
                    }
                    lbl_1_bss_D8++;
                    return;
                }
                for (var_r29 = 0; var_r29 < 4; var_r29++) {
                    var_r31 = var_r28[var_r29]->data;
                    if (!var_r31->unk_00_field0) {
                        break;
                    }
                }
                if (var_r29 >= 4) {
                    fn_1_1274(0x63);
                    for (var_r29 = 0; var_r29 < 4; var_r29++) {
                        var_r28[var_r29]->func = fn_1_11058;
                    }
                    lbl_1_bss_D8++;
                    return;
                }
                fn_1_1275C();
                for (var_r29 = 0; var_r29 < 4; var_r29++) {
                    var_r30 = var_r28[var_r29];
                    var_r31 = var_r28[var_r29]->data;
                    if (!var_r31->unk_00_field0) {
                        var_r31->unk_14.y = VECMag(&var_r31->unk_2C);
                        if (!var_r31->unk_00_field3 && !var_r31->unk_00_field2 && (var_r31->unk_14.y > var_r31->unk_14.z)) {
                            var_r31->unk_14.y = var_r31->unk_14.z;
                            VECNormalize(&var_r31->unk_2C, &var_r31->unk_2C);
                            VECScale(&var_r31->unk_2C, &var_r31->unk_2C, var_r31->unk_14.y);
                        }
                        var_f31 = var_r31->unk_14.y;
                        VECNormalize(&var_r31->unk_2C, &sp14);

                        while (var_f31 > 0.0f) {
                            if (var_f31 < 50.0f) {
                                var_r30->trans.x += sp14.x * var_f31;
                                var_r30->trans.y += sp14.y * var_f31;
                                var_r30->trans.z += sp14.z * var_f31;
                            }
                            else {
                                var_r30->trans.x += 50.0f * sp14.x;
                                var_r30->trans.y += 50.0f * sp14.y;
                                var_r30->trans.z += 50.0f * sp14.z;
                            }
                            sp8.x = var_r30->trans.x;
                            sp8.y = 10.0f + var_r30->trans.y;
                            sp8.z = var_r30->trans.z;
                            if (fn_1_13C10(&sp8, &sp20)) {
                                var_r30->trans.x = sp8.x;
                                var_r30->trans.z = sp8.z;
                                if (var_r31->unk_00_field2 == 0) {
                                    VECNormalize(&var_r31->unk_2C, &sp14);
                                    var_f26 = VECDotProduct(&sp14, &sp20);
                                    if (var_f26 < -0.2f && var_r31->unk_14.y >= 10.0f) {
                                        omVibrate(var_r31->unk_02, 12, 6, 6);
                                    }
                                    if (var_f26 < 0.0f) {
                                        var_f28
                                            = 0.8f * (((-var_r31->unk_2C.x * sp20.x) - (var_r31->unk_2C.y * sp20.y)) - (var_r31->unk_2C.z * sp20.z));
                                        var_r31->unk_2C.x += (2.0f * sp20.x * var_f28);
                                        var_r31->unk_2C.y += (2.0f * sp20.y * var_f28);
                                        var_r31->unk_2C.z += (2.0f * sp20.z * var_f28);
                                    }
                                }
                            }
                            var_f31 -= 50.0f;
                        }
                        var_f25 = fn_1_143F4(&var_r30->trans, &var_r31->unk_44);
                        if (var_r31->unk_44.unk_00 != NULL && var_r30->trans.y < (0.01f + var_f25)) {
                            var_r30->trans.y = var_f25;
                            var_r31->unk_00_field1 = 1;
                        }
                        else {
                            var_r31->unk_00_field1 = 0;
                        }
                        fn_1_12B38(&var_r30->trans);
                        if (var_r31->unk_7C[0] >= 0) {
                            HuAudFXEmiterUpDate(var_r31->unk_7C[0], &var_r30->trans);
                        }
                    }
                }
                for (var_r29 = 0; var_r29 < 4; var_r29++) {
                    sp2C[var_r29] = NULL;
                }
                for (var_r27 = 0, var_r29 = 0; var_r29 < 4; var_r29++) {
                    var_r24 = var_r28[var_r29];
                    var_r22 = var_r24->data;
                    if (!var_r22->unk_00_field0) {
                        for (var_r25 = 0, var_r26 = 0; var_r26 < 4; var_r26++) {
                            var_r23 = var_r28[var_r26];
                            var_r21 = var_r23->data;
                            if (var_r24 != var_r23 && (!var_r21->unk_00_field0 && var_r24->trans.z > var_r23->trans.z)) {
                                var_r25++;
                            }
                        }
                        while (sp2C[var_r25] != NULL) {
                            var_r25++;
                        }
                        sp2C[var_r25] = var_r24;
                        var_r27++;
                    }
                }
                if (var_r27 != 0) {
                    var_f29 = fn_1_12194(&sp2C[0]->trans) - 1500.0f;
                    if (var_f29 >= 0.0f) {
                        fn_1_696C(30.000002f + (0.005f * var_f29));
                    }
                    else {
                        fn_1_696C(30.000002f);
                    }
                    lbl_1_bss_E0[0].x = sp2C[0]->trans.x;
                    lbl_1_bss_E0[0].y = sp2C[0]->trans.y;
                    lbl_1_bss_E0[0].z = sp2C[0]->trans.z - 1000.0f;
                    fn_1_12B38(&lbl_1_bss_E0[0]);
                    if (lbl_1_bss_F8[1] == 0) {
                        lbl_1_bss_E0[1].x = sp2C[var_r27 - 1]->trans.x;
                        lbl_1_bss_E0[1].y = sp2C[var_r27 - 1]->trans.y;
                        lbl_1_bss_E0[1].z = sp2C[var_r27 - 1]->trans.z;
                        lbl_1_bss_F8[1] = 1;
                    }
                    sp20.x = sp2C[var_r27 - 1]->trans.x - lbl_1_bss_E0[1].x;
                    sp20.y = sp2C[var_r27 - 1]->trans.y - lbl_1_bss_E0[1].y;
                    sp20.z = sp2C[var_r27 - 1]->trans.z - lbl_1_bss_E0[1].z;
                    var_f29 = VECMag(&sp20);
                    VECNormalize(&sp20, &sp20);
                    if (var_f29 < 100.0f) {
                        lbl_1_bss_E0[1].x = sp2C[var_r27 - 1]->trans.x;
                        lbl_1_bss_E0[1].y = sp2C[var_r27 - 1]->trans.y;
                        lbl_1_bss_E0[1].z = sp2C[var_r27 - 1]->trans.z;
                    }
                    else {
                        lbl_1_bss_E0[1].x += (100.0f * sp20.x);
                        lbl_1_bss_E0[1].y += (100.0f * sp20.y);
                        lbl_1_bss_E0[1].z += (100.0f * sp20.z);
                    }
                    fn_1_12B38(&lbl_1_bss_E0[1]);
                    if (fn_1_122C() == 2 || fn_1_122C() == 3) {
                        return;
                    }
                    for (var_r29 = 0; var_r29 < var_r27; var_r29++) {
                        var_r30 = sp2C[var_r29];
                        var_r31 = var_r30->data;
                        if (!var_r31->unk_00_field0) {
                            var_f30 = sp2C[var_r27 - 1]->trans.z - var_r30->trans.z;
                            if (var_f30 > 3000.0f) {
                                if (var_f30 > 5000.0f) {
                                    var_f30 = 5000.0f;
                                }
                                var_f27 = 45.0f - (9.0f * (var_f30 / 5000.0f));
                            }
                            else {
                                var_f27 = 45.0f;
                            }
                            var_r31->unk_14.z += (0.2f * (var_f27 - var_r31->unk_14.z));
                        }
                    }
                    return;
                }
                break;
            case 2:
                if (fn_1_122C() == 8 || fn_1_122C() == 10) {
                    lbl_1_bss_D8++;
                    lbl_1_data_11F4 = 210;
                    return;
                }
                break;
            case 3:
                if (--lbl_1_data_11F4 == 0) {
                    fn_1_12BC();
                }
                break;
        }
    }
}

void fn_1_1065C(omObjData *object)
{
    M406PlayerWork *var_r31 = object->data;

    var_r31->unk_12 = 0;
    var_r31->unk_00 = 0;
    var_r31->unk_54 = 1.0f;
    var_r31->unk_14.x = 0.0f;
    var_r31->unk_64 = 60;
    object->trans.z = -60000.0f;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    var_r31->unk_2C.x = var_r31->unk_2C.y = 0.0f;
    var_r31->unk_2C.z = -20.0f;
    Hu3DModelShadowReset(object->model[0]);
    fn_1_6BB4(&object->trans);
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    object->func = fn_1_10744;
}

void fn_1_10744(omObjData *object)
{
    Mtx sp48;
    Mtx sp18;

    float var_f31;

    M406PlayerWork *var_r31;
    ModelData *var_r29;
    s32 var_r24;

    var_r31 = object->data;
    var_r29 = &Hu3DData[object->model[0]];
    switch (var_r31->unk_12) {
        case 0:
            fn_1_DD7C(object, 0, 1.0f, HU3D_MOTATTR_NONE);
            if (--var_r31->unk_64 == 0) {
                fn_1_1284();
                var_r31->unk_12++;
            }
            if (var_r31->unk_64 == 54.0f) {
                HuAudFXPlay(0x541);
            }
            mtxRot(sp48, var_r29->rot.x, var_r29->rot.y, var_r29->rot.z);
            mtxTransCat(sp48, var_r29->pos.x, var_r29->pos.y, var_r29->pos.z);
            if (var_r31->unk_64 < 0x1E) {
                var_f31 = 0.0f;
            }
            else {
                var_f31 = (255.0f * (var_r31->unk_64 - 0x1E)) / 30.0f;
            }
            fn_1_82C8(sp48, frand() & 0xF, var_f31);
            break;
        case 1:
            if (fn_1_122C() == 8) {
                var_r31->unk_12++;
                var_r31->unk_14.x = 180.0f;
                var_r31->unk_64 = 90;
                var_r31->unk_2C.x = 100.0 * (0.10000000149011612 * sind(180.0f + var_r31->unk_14.x));
                var_r31->unk_2C.y = 0.0f;
                var_r31->unk_2C.z = 100.0 * (0.10000000149011612 * cosd(180.0f + var_r31->unk_14.x));
                object->trans.x = 300.0f;
                object->trans.z = -1000.0f;
                object->trans.y = 1000.0f;
                CharModelKill(var_r31->unk_0C);
                object->model[0] = CharModelCreate(var_r31->unk_0C, 2);
                for (var_r24 = 0; var_r24 < 4; var_r24++) {
                    Hu3DModelHookSet(object->model[0], lbl_1_data_1068[var_r24], object->model[var_r24 + 1]);
                }
                for (var_r24 = 0; var_r24 < 10U; var_r24++) {
                    object->motion[var_r24] = CharModelMotionCreate(var_r31->unk_0C, lbl_1_data_1078[var_r24]);
                }
                var_r31->unk_38 = -1;
                fn_1_DD7C(object, 0, 1.0f, HU3D_MOTATTR_NONE);
                Hu3DModelShadowSet(object->model[0]);
                return;
            }
            break;
        case 2:
            var_r31->unk_2C.y += -2.0f;
            if (object->trans.y < 0.0f) {
                object->trans.y = 0.0f;
                var_r31->unk_12++;
                var_r31->unk_2C.y = 0.0f;
                fn_1_DD7C(object, 2, 1.0f, HU3D_MOTATTR_NONE);
                omVibrate(var_r31->unk_02, 0xC, 6, 6);
                var_r31->unk_7C[0] = HuAudFXPlay(0x53B);
            }
            break;
        case 3:
            var_r31->unk_14.x -= 0.5f;
            var_r31->unk_54 = 1.0f;
            if (var_r31->unk_64 < 0x14) {
                var_r31->unk_54 = var_r31->unk_64 / 20.0f;
            }
            if ((var_r31->unk_64 < 0x50) && (var_r31->unk_64 > 0x1E)) {
                mtxRot(sp48, var_r29->rot.x, var_r29->rot.y, var_r29->rot.z);
                mtxTransCat(sp48, var_r29->pos.x, var_r29->pos.y, var_r29->pos.z);
                MTXTrans(sp18, 10.0f, 0.0f, 0.0f);
                MTXConcat(sp18, sp48, sp48);
                fn_1_94C0(sp48, 10, 0);
            }
            var_r31->unk_2C.x = var_r31->unk_54 * (100.0 * (0.10000000149011612 * sind(180.0f + var_r31->unk_14.x)));
            var_r31->unk_2C.z = var_r31->unk_54 * (100.0 * (0.10000000149011612 * cosd(180.0f + var_r31->unk_14.x)));
            if (var_r31->unk_64 == 48.0f) {
                fn_1_DD7C(object, 8, 1.0f, HU3D_MOTATTR_NONE);
            }
            if (--var_r31->unk_64 == 0) {
                var_r31->unk_12 = -1;
                var_r31->unk_2C.x = var_r31->unk_2C.z = 0.0f;
            }
            break;
        default:
            break;
    }
    object->trans.x += var_r31->unk_2C.x;
    object->trans.y += var_r31->unk_2C.y;
    object->trans.z += var_r31->unk_2C.z;
    object->rot.y = 180.0f + var_r31->unk_14.x;
}

void fn_1_11058(omObjData *object)
{
    ModelData *sp8;

    M406PlayerWork *var_r30;
    void *var_r29;
    s32 var_r28;

    var_r30 = object->data;
    if (lbl_1_bss_1CC < 0) {
        object->trans.x = lbl_1_data_11F8[lbl_1_bss_1F4].unk_00;
        object->trans.z = lbl_1_data_11F8[lbl_1_bss_1F4].unk_04;
        var_r30->unk_64 = 30.0f + (frand() & 0x1F);
    }
    else {
        object->trans.x = lbl_1_data_1218[lbl_1_bss_1F4].unk_00;
        object->trans.z = lbl_1_data_1218[lbl_1_bss_1F4].unk_04;
        var_r30->unk_64 = 90.0f + (frand() & 0x1F);
    }
    for (var_r28 = 0; var_r28 < 8; var_r28++) {
        Hu3DModelAttrSet(object->model[var_r28], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(object->model[var_r28], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(object->model[var_r28], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[var_r28], 1.0f, 1.0f, 1.0f);
    }
    Hu3DModelHookReset(object->model[0]);
    fn_1_DD7C(object, 0, 1.0f, HU3D_MOTATTR_NONE);
    var_r30->unk_00 = 0;
    var_r30->unk_12 = 0;
    var_r30->unk_00_field3 = 1;
    var_r30->unk_50 = 360.0f * frandf();
    var_r30->unk_50 = 160.0f + ((frand() & 0x3F) - 0x20);
    var_r30->unk_54 = 30.0f;
    var_r30->unk_5A = 3;
    object->trans.y = 1000.0f;
    object->rot.x = object->rot.y = 0.0f;
    object->rot.z = (frand() & 0x3F) - 0x20;
    var_r30->unk_2C.x = var_r30->unk_2C.y = var_r30->unk_2C.z = 0.0f;
    lbl_1_bss_1F4++;
    object->func = fn_1_114A0;
}

void fn_1_114A0(omObjData *object)
{
    Mtx sp9C;
    Mtx sp6C;
    Mtx sp3C;
    Mtx spC;
    ModelData *sp8;
    M406PlayerWork *var_r31;

    var_r31 = object->data;
    sp8 = &Hu3DData[object->model[0]];
    switch (var_r31->unk_12) {
        case 0:
            if (fn_1_122C() == 8 || fn_1_122C() == 10) {
                var_r31->unk_12++;
            }
            return;
        case 1:
            if (var_r31->unk_64 != 0) {
                if (--var_r31->unk_64 == 0) {
                    Hu3DModelAttrReset(object->model[5], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(object->model[7], HU3D_ATTR_DISPOFF);
                }
                else {
                    return;
                }
            }
            var_r31->unk_50 += var_r31->unk_54;
            var_r31->unk_54 -= 0.5f;
            if (var_r31->unk_54 < 0.0f) {
                var_r31->unk_54 = 0.0f;
            }
            if (var_r31->unk_5A != 0) {
                var_r31->unk_2C.y += -2.0f;
                object->trans.y += var_r31->unk_2C.y;
                if (object->trans.y < 0.0f) {
                    object->trans.y = 0.0f;
                    var_r31->unk_2C.y = 0.5f * -var_r31->unk_2C.y;
                    var_r31->unk_5A--;
                    if (!var_r31->unk_00_field5) {
                        omVibrate(var_r31->unk_02, 12, 4, 2);
                        var_r31->unk_00_field5 = 1;
                        HuAudFXPlay(0x53F);
                    }
                }
            }
            break;
        default:
            break;
    }
    mtxRot(sp9C, object->rot.x, object->rot.y, object->trans.z);
    mtxScaleCat(sp9C, object->scale.x, object->scale.y, object->scale.z);
    MTXTrans(sp9C, object->trans.x, object->trans.y, object->trans.z);
    MTXRotRad(sp6C, 0x78, 0.017453292f * var_r31->unk_50);
    MTXConcat(sp9C, sp6C, sp9C);
    MTXCopy(sp9C, spC);
    mtxScaleCat(spC, 2.0f, 2.0f, 2.0f);
    MTXCopy(spC, Hu3DData[object->model[5]].unk_F0);
    MTXTrans(sp3C, 0.0f, 110.0f, 0.0f);
    MTXConcat(sp9C, sp3C, spC);
    MTXCopy(spC, Hu3DData[object->model[7]].unk_F0);
}

void fn_1_117BC(float arg8, float arg9, UnkM406PlayerStruct2 *arg0, Vec *arg1)
{
    Vec sp10;
    float spC;

    float var_f30;
    Vec *var_r31;

    if (arg0->unk_00 == NULL) {
        arg1->x = arg1->y = arg1->z = 0.0f;
        return;
    }
    var_r31 = &arg0->unk_00[3];
    sp10.x = var_r31->y * sind((180.0f + arg8));
    sp10.z = var_r31->y * cosd((180.0f + arg8));
    var_f30 = 1.0f - (var_r31->y * var_r31->y);
    sp10.y = -sqrtf(var_f30);
    VECScale(&sp10, arg1, arg9);
}
s32 fn_1_119E4(Vec *arg0, UnkM406PlayerStruct *arg1)
{
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f20;
    float var_f19;
    float var_f18;

    s32 var_r31;
    s32 var_r30;

    for (var_r31 = 0; var_r31 < lbl_1_bss_B4 - 1; var_r31++) {
        var_r30 = var_r31 + 1;
        var_f31 = lbl_1_data_960[var_r30].x - lbl_1_data_CA8[var_r31].x;
        var_f30 = lbl_1_data_960[var_r30].z - lbl_1_data_CA8[var_r31].z;
        if (((var_f31 * (arg0->z - lbl_1_data_CA8[var_r31].z)) - (var_f30 * (arg0->x - lbl_1_data_CA8[var_r31].x))) < 0.0f) {
            var_f31 = lbl_1_data_960[var_r30].x - lbl_1_data_960[var_r31].x;
            var_f28 = lbl_1_data_CA8[var_r31].x - lbl_1_data_960[var_r31].x;
            var_f30 = lbl_1_data_960[var_r30].z - lbl_1_data_960[var_r31].z;
            var_f27 = lbl_1_data_CA8[var_r31].z - lbl_1_data_960[var_r31].z;
            var_f26 = 0.0f;
            var_f25 = 1.0f;
            var_f24 = 1.0f;
            var_f23 = 0.0f;
            var_f29 = (var_f31 * var_f27) - (var_f28 * var_f30);
            var_f22 = ((var_f26 * var_f27) - (var_f25 * var_f30)) / var_f29;
            var_f21 = ((var_f25 * var_f31) - (var_f26 * var_f28)) / var_f29;
            var_f20 = ((var_f24 * var_f27) - (var_f23 * var_f30)) / var_f29;
            var_f19 = ((var_f23 * var_f31) - (var_f24 * var_f28)) / var_f29;
            sp8.z = -(var_f22 * lbl_1_data_960[var_r31].x) - (var_f21 * lbl_1_data_960[var_r31].z);
            sp8.y = -(var_f20 * lbl_1_data_960[var_r31].x) - (var_f19 * lbl_1_data_960[var_r31].z);
        }
        else {
            var_f31 = lbl_1_data_CA8[var_r30].x - lbl_1_data_960[var_r30].x;
            var_f28 = lbl_1_data_CA8[var_r31].x - lbl_1_data_960[var_r30].x;
            var_f30 = lbl_1_data_CA8[var_r30].z - lbl_1_data_960[var_r30].z;
            var_f27 = lbl_1_data_CA8[var_r31].z - lbl_1_data_960[var_r30].z;
            var_f26 = 1.0f;
            var_f25 = 1.0f;
            var_f24 = 0.0f;
            var_f23 = -1.0f;
            var_f29 = (var_f31 * var_f27) - (var_f28 * var_f30);
            var_f22 = ((var_f26 * var_f27) - (var_f25 * var_f30)) / var_f29;
            var_f21 = ((var_f25 * var_f31) - (var_f26 * var_f28)) / var_f29;
            var_f20 = ((var_f24 * var_f27) - (var_f23 * var_f30)) / var_f29;
            var_f19 = ((var_f23 * var_f31) - (var_f24 * var_f28)) / var_f29;
            sp8.z = -(var_f22 * lbl_1_data_960[var_r30].x) - (var_f21 * lbl_1_data_960[var_r30].z);
            sp8.y = (1.0f - (var_f20 * lbl_1_data_960[var_r30].x)) - (var_f19 * lbl_1_data_960[var_r30].z);
        }
        var_f18 = sp8.z + ((var_f22 * arg0->x) + (var_f21 * arg0->z));
        sp8.x = sp8.y + ((var_f20 * arg0->x) + (var_f19 * arg0->z));
        if ((var_f18 >= 0.0f) && (var_f18 < 1.0f) && (sp8.x >= 0.0f) && (sp8.x < 1.0f)) {
            arg1->unk_00 = var_f18;
            arg1->unk_04 = sp8.x;
            return var_r31;
        }
    }
    return -1;
}

void fn_1_11FC4(Vec *arg0, float arg8, Vec *arg1)
{
    UnkM406PlayerStruct spC;

    float var_f30;
    float var_f31;
    float var_f29;
    float var_f28;

    UnkM406Struct2 *var_r31;
    s32 var_r29;
    s32 var_r28;

    var_r29 = -1;
    var_r29 = fn_1_119E4(arg0, &spC);
    if (var_r29 >= 0) {
        var_r31 = &lbl_1_bss_B8[var_r29];
        var_f31 = 0.0f;
        var_f30 = var_r31->unk_00 * spC.unk_04;
        var_f29 = var_r31->unk_00 - var_f30;

        for (var_r28 = var_r29; var_r28 < lbl_1_bss_B4 - 1; var_r28++) {
            if (var_f31 + var_f29 >= 3000.0f) {
                var_f28 = (3000.0f + var_f30) - var_f31;
                arg1->x = (var_r31->unk_14.x + (var_r31->unk_08.x * var_f28)) - (var_r31->unk_08.z * arg8);
                arg1->y = var_r31->unk_14.y + (var_r31->unk_08.y * var_f28);
                arg1->z = var_r31->unk_14.z + (var_r31->unk_08.z * var_f28) + (var_r31->unk_08.x * arg8);
                return;
            }
            var_f31 += var_f29;
            var_f30 = 0.0f;
            var_r31++;
            var_f29 = var_r31->unk_00;
        }
    }
    arg1->x = arg1->y = 0.0f;
    arg1->z = -61000.0f;
}

float fn_1_12194(Vec *arg0)
{
    Vec sp1C;
    UnkM406PlayerStruct sp14;
    UnkM406PlayerStruct spC;

    UnkM406Struct2 *var_r31;
    UnkM406Struct2 *var_r30;
    s32 var_r29;
    s32 var_r28;

    fn_1_69C0(&sp1C);
    var_r28 = fn_1_119E4(&sp1C, &sp14);
    var_r29 = fn_1_119E4(arg0, &spC);
    if (var_r28 < 0 || var_r29 < 0) {
        return -1.0f;
    }
    var_r31 = &lbl_1_bss_B8[var_r28];
    var_r30 = &lbl_1_bss_B8[var_r29];
    return (var_r30->unk_04 + (var_r30->unk_00 * spC.unk_04)) - (var_r31->unk_04 + (var_r31->unk_00 * sp14.unk_04));
}

void fn_1_12270(omObjData *object)
{
    Vec sp1C;
    Vec sp10;
    UnkM406PlayerStruct sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    M406PlayerWork *var_r31;
    UnkM406Struct2 *var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r31 = object->data;
    if (!var_r31->unk_00_field3) {
        if (var_r31->unk_14.y < 30.000002f) {
            var_r31->unk_0A = 0x100;
        }
        else if ((frand() & 0x1FF) < (var_r31->unk_0E + 6)) {
            var_r31->unk_0A = 0x100;
        }
        if ((frand() & 0xFF) == 0) {
            var_r31->unk_78 = (400.0f + (100.0f * (4 - GWPlayerCfg[var_r31->unk_02].diff))) * ((frand() & 0x1FF) - 256.0f) / 256;
        }
        if (fabs(var_r31->unk_74 - var_r31->unk_78) > 10.0) {
            var_r31->unk_74 = var_r31->unk_74 + (0.05f * (var_r31->unk_78 - var_r31->unk_74));
        }
        var_f27 = var_r31->unk_74;
        var_r29 = -1;
        var_r29 = fn_1_119E4(&object->trans, &sp8);
        if (var_r29 >= 0) {
            var_r30 = &lbl_1_bss_B8[var_r29];
            var_f31 = 0.0f;
            var_f28 = var_r30->unk_00 * sp8.unk_04;
            var_f29 = var_r30->unk_00 - var_f28;
            for (var_r28 = var_r29; var_r28 < lbl_1_bss_B4 - 1; var_r28++) {
                if (var_f31 + var_f29 >= 3000.0f) {
                    var_f30 = (3000.0f + var_f28) - var_f31;
                    sp1C.x = (var_r30->unk_14.x + (var_r30->unk_08.x * var_f30)) - (var_r30->unk_08.z * var_f27);
                    sp1C.y = var_r30->unk_14.y + (var_r30->unk_08.y * var_f30);
                    sp1C.z = var_r30->unk_14.z + (var_r30->unk_08.z * var_f30) + (var_r30->unk_08.x * var_f27);
                    goto block_12270; // TODO
                }
                else {
                    var_f31 += var_f29;
                    var_f28 = 0.0f;
                    var_r30++;
                    var_f29 = var_r30->unk_00;
                }
            }
        }
        sp1C.x = sp1C.y = 0.0f;
        sp1C.z = -61000.0f;

    block_12270:
        VECSubtract(&sp1C, &object->trans, &sp10);
        if (VECMag(&sp10) > 0.0f) {
            VECNormalize(&sp10, &sp10);
            var_r31->unk_06 = 72.0 * ((sp10.x * cosd(CRot.y)) - sp10.z * sind(CRot.y));
            var_r31->unk_07 = 72.0 * -((sp10.x * sind(CRot.y)) + sp10.z * cosd(CRot.y));
        }
    }
    else if ((frand() & 3) == 0) {
        var_r31->unk_0A = 256;
    }
}

void fn_1_1275C(void)
{
    omObjData **sp8;
    s32 var_r31;

    var_r31 = 0;
    sp8 = omGetGroupMemberListEx(lbl_1_bss_1C8, 0);

    while (fn_1_127B8() != 0 && var_r31 < 10) {
        var_r31++;
    }
}

s32 fn_1_127B8(void)
{
    Vec sp14[4];
    Vec sp8;

    float var_f31;
    float var_f30;

    s32 var_r31;
    s32 var_r30;
    omObjData **var_r29;
    omObjData *var_r28;
    s32 var_r27;
    omObjData *var_r26;
    omObjData *var_r25;
    M406PlayerWork *var_r24;
    M406PlayerWork *var_r23;
    M406PlayerWork *var_r22;

    var_r27 = 0;
    var_r29 = omGetGroupMemberListEx(lbl_1_bss_1C8, 0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp14[var_r31].x = sp14[var_r31].y = sp14[var_r31].z = 0.0f;
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        var_r26 = var_r29[var_r31];
        var_r23 = var_r26->data;
        if (!var_r23->unk_00_field0) {
            for (var_r30 = var_r31 + 1; var_r30 < 4; var_r30++) {
                var_r25 = var_r29[var_r30];
                var_r22 = var_r25->data;
                if (!var_r22->unk_00_field0) {
                    VECSubtract(&var_r26->trans, &var_r25->trans, &sp8);
                    var_f31 = VECMag(&sp8);
                    if (var_f31 < 100.0f) {
                        VECNormalize(&sp8, &sp8);
                        var_f30 = 0.01f + (0.5f * (100.0f - var_f31));
                        VECScale(&sp8, &sp8, var_f30);
                        VECAdd(&sp14[var_r31], &sp8, &sp14[var_r31]);
                        VECSubtract(&sp14[var_r30], &sp8, &sp14[var_r30]);
                        var_r27++;
                    }
                }
            }
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r28 = var_r29[var_r31];
        var_r24 = var_r28->data;
        if (!var_r24->unk_00_field0) {
            VECAdd(&var_r28->trans, &sp14[var_r31], &var_r28->trans);
        }
    }
    return var_r27;
}

s32 fn_1_129E4(omObjData *object)
{
    Vec spC;

    float var_f31;

    s32 var_r31;
    omObjData **var_r30;
    ModelData *var_r29;

    var_r30 = omGetGroupMemberListEx(HuPrcCurrentGet(), 3);
    for (var_r31 = 0; var_r31 < var_r30[0]->mdlcnt; var_r31++) {
        var_r29 = &Hu3DData[(*var_r30)->model[var_r31]];
        VECSubtract(&var_r29->pos, &object->trans, &spC);
        var_f31 = VECMag(&spC);
        if (var_f31 < 100.0f) {
            return 1;
        }
    }
    return 0;
}

void fn_1_12AB8(omObjData *object)
{
    if (object->data != NULL) {
        HuMemDirectFree(object->data);
        object->data = NULL;
    }
}

void fn_1_12B00(omObjData *object)
{
    lbl_1_bss_1C4 = 0;
    lbl_1_bss_100 = -1.0f;
    object->func = fn_1_12BC4;
}

void fn_1_12B38(Vec *arg0)
{
    lbl_1_bss_104[lbl_1_bss_1C4].x = arg0->x;
    lbl_1_bss_104[lbl_1_bss_1C4].y = arg0->y;
    lbl_1_bss_104[lbl_1_bss_1C4].z = arg0->z;
    lbl_1_bss_1C4++;
}

void fn_1_12BC4(omObjData *object)
{
    Vec sp198[16];
    Vec spD8[16];
    Mtx spA8;
    Vec sp9C;
    Vec sp90;
    Vec sp84;
    Vec sp78;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    s32 var_r31;
    CameraData *var_r30 = Hu3DCamera;

    if (lbl_1_bss_1C4 != 0) {
        if (fn_1_122C() == 4) {
            var_f30 = 0.4f;
        }
        else {
            var_f30 = 0.05f;
        }
        var_f31 = var_f30;
        for (var_r31 = 0; var_r31 < lbl_1_bss_1C4; var_r31++) {
            if (var_r31 == 0) {
                sp9C = sp90 = lbl_1_bss_104[var_r31];
            }
            else {
                if (lbl_1_bss_104[var_r31].x < sp9C.x) {
                    sp9C.x = lbl_1_bss_104[var_r31].x;
                }
                else if (lbl_1_bss_104[var_r31].x > sp90.x) {
                    sp90.x = lbl_1_bss_104[var_r31].x;
                }
                if (lbl_1_bss_104[var_r31].y < sp9C.y) {
                    sp9C.y = lbl_1_bss_104[var_r31].y;
                }
                else if (lbl_1_bss_104[var_r31].y > sp90.y) {
                    sp90.y = lbl_1_bss_104[var_r31].y;
                }
                if (lbl_1_bss_104[var_r31].z < sp9C.z) {
                    sp9C.z = lbl_1_bss_104[var_r31].z;
                }
                else if (lbl_1_bss_104[var_r31].z > sp90.z) {
                    sp90.z = lbl_1_bss_104[var_r31].z;
                }
            }
        }
        var_f31 = 0.4f;
        Center.x += var_f31 * ((0.5f * (sp9C.x + sp90.x)) - Center.x);
        Center.y += var_f31 * ((0.5f * (sp9C.y + sp90.y)) - Center.y);
        Center.z += var_f31 * ((0.5f * (sp9C.z + sp90.z)) - Center.z);

        var_r30->target.x = Center.x;
        var_r30->target.y = Center.y;
        var_r30->target.z = Center.z;
        C_MTXLookAt(spA8, &var_r30->pos, &var_r30->up, &var_r30->target);
        for (var_r31 = 0; var_r31 < lbl_1_bss_1C4; var_r31++) {
            MTXMultVec(spA8, &lbl_1_bss_104[var_r31], &sp198[var_r31]);
            spD8[var_r31].x = sp198[var_r31].x / (sp198[var_r31].z * (sind((var_r30->fov / 2)) / cosd((var_r30->fov / 2))));
            spD8[var_r31].y = sp198[var_r31].y / (sp198[var_r31].z * (sind((var_r30->fov / 2)) / cosd((var_r30->fov / 2))));
        }
        sp90.x = 0.0f;
        for (var_r31 = 0; var_r31 < lbl_1_bss_1C4; var_r31++) {
            if (fabs(spD8[var_r31].x) > fabs(spD8[var_r31].y)) {
                if (fabs(spD8[var_r31].x) > sp90.x) {
                    sp90.x = fabs(spD8[var_r31].x);
                    sp90.y = fabs(sp198[var_r31].x);
                    sp90.z = sp198[var_r31].z;
                }
            }
            else {
                if (fabs(spD8[var_r31].y) > sp90.x) {
                    sp90.x = fabs(spD8[var_r31].y);
                    sp90.y = fabs(sp198[var_r31].y);
                    sp90.z = sp198[var_r31].z;
                }
            }
        }
        var_f29 = -sp90.y / (sind((var_r30->fov / 2)) / cosd((var_r30->fov / 2)));
        var_f28 = CZoom - (var_f29 - sp90.z);
        var_f31 = 0.05f;
        if (lbl_1_bss_100 >= 0.0f) {
            lbl_1_bss_100 += var_f31 * (var_f28 - lbl_1_bss_100);
        }
        else {
            lbl_1_bss_100 = CZoom - 500.0f;
        }
        CZoom = 500.0f + lbl_1_bss_100;
        if (CZoom < 1500.0f) {
            CZoom = 1500.0f;
        }
        lbl_1_bss_1C4 = 0;
        if (fn_1_122C() >= 3) {
            sp84.x = Center.x + (CZoom * (sind(CRot.y) * cosd(CRot.x)));
            sp84.y = Center.y + (CZoom * -sind(CRot.x));
            sp84.z = Center.z + (CZoom * (cosd(CRot.y) * cosd(CRot.x)));
            VECSubtract(&Center, &sp84, &sp78);
            VECNormalize(&sp78, &sp78);
            HuAudFXListnerUpdate(&sp84, &sp78);
        }
    }
}

void fn_1_136A8(void) { }

s32 fn_1_136AC(HsfObject *arg0, Mtx arg1, char *arg2, Mtx arg3)
{
    char sp4A4[256];
    Mtx sp174;
    Mtx sp144;
    u32 var_r23;

    HsfTransform *var_r31 = &arg0->data.curr;

    mtxRot(sp144, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
    MTXScale(sp174, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
    MTXConcat(sp144, sp174, sp174);
    mtxTransCat(sp174, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
    MTXConcat(arg1, sp174, sp174);
    strcpy(sp4A4, MakeObjectName(arg2));
    if (strcmp(sp4A4, arg0->name) == 0) {
        MTXCopy(sp174, arg3);
        return 1;
    }
    for (var_r23 = 0; var_r23 < arg0->data.childrenCount; var_r23++) {
        s32 sp20 = fn_1_136AC(arg0->data.children[var_r23], sp174, arg2, arg3);
        if (sp20) {
            return 1;
        }
    }
    return 0;
}

void fn_1_13A88(s16 arg0, char *arg1, Mtx arg2)
{
    Mtx sp14;

    ModelData *var_r31;
    HsfData *var_r30;

    var_r31 = &Hu3DData[arg0];
    var_r30 = var_r31->hsfData;
    MTXIdentity(sp14);
    fn_1_136AC(var_r30->root, sp14, arg1, arg2);
}

float fn_1_13AF4(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;
    float var_f29;

    var_f30 = fmod(arg9 - arg8, 360.0);
    var_f31 = var_f30;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f29 = fmod(arg8 + (argA * var_f31), 360.0);
    var_f31 = var_f29;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    return var_f31;
}

s32 fn_1_13C10(Vec *arg0, Vec *arg1)
{
    Vec *sp48[3];
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    HsfBuffer *sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    HsfFace *var_r31;
    s32 var_r29;
    HsfFace *var_r28;
    HsfObject *var_r27;
    HsfBuffer *var_r26;
    HsfBuffer *var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21;
    omObjData **var_r20;
    ModelData *var_r19;

    var_r20 = omGetGroupMemberListEx(lbl_1_bss_1C8, 2);
    var_r21 = arg0->z / -10000.0f;
    if (var_r21 >= 6) {
        return;
    }
    var_r19 = &Hu3DData[(*var_r20)->model[var_r21]];
    var_f29 = 100000.0f;
    var_r27 = var_r19->hsfData->root;
    if (var_r27->type != 2) {
        return;
    }
    var_r24 = var_r27->data.face;
    var_r26 = var_r27->data.vertex;
    sp8 = var_r27->data.normal;
    var_r31 = var_r24->data;
    for (var_r23 = 0; var_r23 < var_r24->count; var_r23++, var_r31++) {
        if ((var_r31->type == 2) && ((var_r31->mat & 0xFFF) == lbl_1_bss_1E8[var_r21])) {
            sp48[0] = &((Vec *)var_r26->data)[var_r31->indices[0][0]];
            sp48[1] = &((Vec *)var_r26->data)[var_r31->indices[1][0]];
            sp48[2] = &((Vec *)var_r26->data)[var_r31->indices[2][0]];

            var_f28 = (var_r31->nbt.z * sp48[0]->z) + ((var_r31->nbt.x * sp48[0]->x) + (var_r31->nbt.y * sp48[0]->y));
            sp24.x = -var_r31->nbt.x;
            sp24.y = 0.0f;
            sp24.z = -var_r31->nbt.z;
            VECNormalize(&sp24, &sp24);
            var_f31 = (var_f28 + (((-var_r31->nbt.x * arg0->x) - (var_r31->nbt.y * arg0->y)) - (var_r31->nbt.z * arg0->z)))
                / ((var_r31->nbt.x * sp24.x) + (var_r31->nbt.z * sp24.z));
            if (var_f31 <= 0.0) {
                continue;
            }
            spC.x = arg0->x + (sp24.x * var_f31);
            spC.y = arg0->y;
            spC.z = arg0->z + (sp24.z * var_f31);
            VECSubtract(sp48[1], sp48[0], &sp3C);
            VECSubtract(&spC, sp48[1], &sp30);
            VECCrossProduct(&sp3C, &sp30, &sp24);
            if (!(VECDotProduct(&var_r31->nbt, &sp24) < 0.0f)) {
                VECSubtract(sp48[2], sp48[1], &sp3C);
                VECSubtract(&spC, sp48[2], &sp30);
                VECCrossProduct(&sp3C, &sp30, &sp24);
                if (!(VECDotProduct(&var_r31->nbt, &sp24) < 0.0f)) {
                    VECSubtract(sp48[0], sp48[2], &sp3C);
                    VECSubtract(&spC, sp48[0], &sp30);
                    VECCrossProduct(&sp3C, &sp30, &sp24);
                    if (!(VECDotProduct(&var_r31->nbt, &sp24) < 0.0f) && (var_f31 < var_f29)) {
                        var_f29 = var_f31;
                        sp18 = spC;
                        var_r28 = var_r31;
                    }
                }
            }
            for (var_r29 = 0; var_r29 < 3; var_r29++) {
                var_r22 = var_r29 + 1;
                if (var_r22 > 2) {
                    var_r22 = 0;
                }
                VECSubtract(sp48[var_r22], sp48[var_r29], &sp3C);
                if (sp3C.y != 0.0f) {
                    var_f30 = (arg0->y - sp48[var_r29]->y) / sp3C.y;
                    if ((var_f30 >= 0.0f) && (var_f30 < 1.0f)) {
                        spC.x = sp48[var_r29]->x + (var_f30 * sp3C.x);
                        spC.z = sp48[var_r29]->z + (var_f30 * sp3C.z);
                        VECSubtract(&spC, arg0, &sp3C);
                        sp3C.y = 0.0f;
                        var_f31 = VECMag(&sp3C);
                        if (var_f31 < var_f29) {
                            var_f29 = var_f31;
                            sp18 = spC;
                            var_r28 = var_r31;
                        }
                    }
                }
                var_f31 = (sp3C.x * sp3C.x) + (sp3C.z * sp3C.z);
                if (var_f31 != 0.0f) {
                    var_f30 = (((arg0->z * sp3C.z) + ((arg0->x * sp3C.x) - (sp3C.x * sp48[var_r29]->x))) - (sp3C.z * sp48[var_r29]->z)) / var_f31;
                    if ((var_f30 >= 0.0f) && (var_f30 < 1.0f)) {
                        sp30.y = sp48[var_r29]->y + (var_f30 * sp3C.y);
                        if ((sp30.y >= arg0->y) && (sp30.y < (150.0f + arg0->y))) {
                            sp30.x = sp48[var_r29]->x + (var_f30 * sp3C.x);
                            sp30.z = sp48[var_r29]->z + (var_f30 * sp3C.z);
                            VECSubtract(&sp30, arg0, &sp3C);
                            sp3C.y = 0.0f;
                            var_f31 = VECMag(&sp3C);
                            if (var_f31 < var_f29) {
                                var_f29 = var_f31;
                                sp18 = sp30;
                                var_r28 = var_r31;
                            }
                        }
                    }
                }
                if ((sp48[var_r29]->y >= arg0->y) && (sp48[var_r29]->y < (150.0f + arg0->y))) {
                    VECSubtract(arg0, sp48[var_r29], &sp3C);
                    sp3C.y = 0.0f;
                    var_f31 = VECMag(&sp3C);
                    if (var_f31 < var_f29) {
                        var_f29 = var_f31;
                        sp18.x = sp48[var_r29]->x;
                        sp18.z = sp48[var_r29]->z;
                        var_r28 = var_r31;
                    }
                }
            }
        }
    }
    if (var_f29 < 100.0f) {
        VECSubtract(arg0, &sp18, &sp3C);
        sp3C.y = 0.0f;
        VECNormalize(&sp3C, &sp3C);
        arg0->x = sp18.x + (100.001f * sp3C.x);
        arg0->z = sp18.z + (100.001f * sp3C.z);
        arg1->x = var_r28->nbt.x;
        arg1->y = var_r28->nbt.y;
        arg1->z = var_r28->nbt.z;
        return 1;
    }
    return 0;
}

float fn_1_143F4(Vec *arg0, UnkM406PlayerStruct2 *arg1)
{
    Vec *sp34[3];
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    HsfBuffer *spC;
    float sp8; // ! - uninitialized

    float var_f31;
    float var_f30;

    HsfFace *var_r31;
    HsfObject *var_r30;
    HsfBuffer *var_r28;
    s32 var_r27;
    HsfBuffer *var_r25;
    s32 var_r24;
    omObjData **var_r23;
    ModelData *var_r22;
    s32 var_r21;

    arg1->unk_00 = NULL;
    var_r23 = omGetGroupMemberListEx(lbl_1_bss_1C8, 2);
    var_r27 = arg0->z / -10000.0f;
    if (var_r27 >= 6) {
        return sp8;
    }
    var_r22 = &Hu3DData[var_r23[0]->model[var_r27]];
    var_r30 = var_r22->hsfData->root;
    if (var_r30->type != 2) {
        return -100000.0f;
    }
    var_r25 = var_r30->data.face;
    var_r28 = var_r30->data.vertex;
    spC = var_r30->data.normal;
    for (var_r31 = var_r25->data, var_r24 = 0; var_r24 < var_r25->count; var_r24++, var_r31++) {
        if (var_r31->type == 2 && (((var_r31->mat & 0xFFF) == lbl_1_bss_1DC[var_r27]) || ((var_r31->mat & 0xFFF) == lbl_1_bss_1D0[var_r27]))) {
            sp34[0] = &((Vec *)var_r28->data)[var_r31->indices[0][0]];
            sp34[1] = &((Vec *)var_r28->data)[var_r31->indices[1][0]];
            sp34[2] = &((Vec *)var_r28->data)[var_r31->indices[2][0]];
            VECSubtract(sp34[1], sp34[0], &sp28);
            VECSubtract(arg0, sp34[1], &sp1C);
            VECCrossProduct(&sp28, &sp1C, &sp10);
            if (sp10.y < 0.0f) {
                continue;
            }
            VECSubtract(sp34[2], sp34[1], &sp28);
            VECSubtract(arg0, sp34[2], &sp1C);
            VECCrossProduct(&sp28, &sp1C, &sp10);
            if (sp10.y < 0.0f) {
                continue;
            }
            VECSubtract(sp34[0], sp34[2], &sp28);
            VECSubtract(arg0, sp34[0], &sp1C);
            VECCrossProduct(&sp28, &sp1C, &sp10);
            if (sp10.y < 0.0f) {
                continue;
            }
            var_f30 = (var_r31->nbt.z * sp34[0]->z) + ((var_r31->nbt.x * sp34[0]->x) + (var_r31->nbt.y * sp34[0]->y));
            var_f31 = ((var_f30 - (var_r31->nbt.x * arg0->x)) - (var_r31->nbt.z * arg0->z)) / var_r31->nbt.y;
            arg1->unk_00 = (Vec *)var_r31;
            arg1->unk_08 = (var_r31->mat & 0xFFF) == lbl_1_bss_1D0[var_r27] ? 1 : 0;
            return var_f31;
        }
    }
    return -100000.0f;
}
