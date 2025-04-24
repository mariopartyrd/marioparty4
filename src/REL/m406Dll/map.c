#include "ext_math.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/sprite.h"

#include "REL/m406Dll.h"

#ifndef __MWERKS__
#include <game/frand.h>
#endif

typedef struct UnkM406Struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ Vec unk_10;
    /* 0x1C */ Vec unk_1C;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
} UnkM406Struct; /* size = 0x30 */

typedef struct UnkM406Struct3 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ struct UnkM406Struct5 *unk_24;
} UnkM406Struct3; /* size = 0x28 */

typedef struct UnkM406Struct4 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
    /* 0x1C */ float unk_1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ Vec unk_30;
    /* 0x3C */ Vec unk_3C;
} UnkM406Struct4; /* size = 0x48 */

typedef struct UnkM406Unk120Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
    /* 0x1C */ float unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ UnkM406Struct3 *unk_2C;
    /* 0x30 */ UnkM406Struct4 *unk_30;
    /* 0x34 */ Vec unk_34;
    /* 0x40 */ Vec unk_40;
    /* 0x4C */ Mtx unk_4C;
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ s32 unk_80;
    /* 0x84 */ Vec *unk_84;
    /* 0x88 */ Vec *unk_88;
    /* 0x8C */ Vec2f *unk_8C;
    /* 0x90 */ GXColor *unk_90;
    /* 0x94 */ UnkM406Struct *unk_94;
    /* 0x98 */ s32 unk_98;
    /* 0x9C */ s16 (*unk_9C)[4];
    /* 0xA0 */ u32 unk_A0;
    /* 0xA4 */ void *unk_A4;
    /* 0xA8 */ u8 *unk_A8;
    /* 0xAC */ s32 unk_AC;
    /* 0xB0 */ s32 unk_B0;
    /* 0xB4 */ float unk_B4;
    /* 0xB8 */ float unk_B8;
    /* 0xBC */ u8 *unk_BC;
    /* 0xC0 */ s32 unk_C0;
    /* 0xC4 */ s32 unk_C4;
    /* 0xC8 */ float unk_C8;
    /* 0xCC */ float unk_CC;
} UnkM406Unk120Struct; /* size = 0xD0 */

typedef struct UnkM406Struct5 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec unk_04;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
    /* 0x1C */ char unk1C[0xC];
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ Vec unk_30;
    /* 0x3C */ GXColor unk_3C;
    /* 0x40 */ s32 unk_40;
} UnkM406Struct5; /* size = 0x44 */ // most likely UnkM426Struct8

typedef struct UnkM406Struct9 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ char unk06[2];
} UnkM406Struct9; /* size = 0x08 */

typedef void (*UnkM406Unk120Struct2Hook)(struct model_data *, struct UnkM406Unk120Struct2 *, Mtx);

typedef struct UnkM406Unk120Struct2 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ char unk04[0x18];
    /* 0x1C */ UnkM406Struct9 *unk_1C;
    /* 0x20 */ u8 unk_20;
    /* 0x21 */ u8 unk_21;
    /* 0x22 */ u8 unk_22;
    /* 0x23 */ char unk23;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ u32 unk_30;
    /* 0x34 */ u32 unk_34;
    /* 0x38 */ AnimData *unk_38;
    /* 0x3C */ UnkM406Struct5 *unk_3C;
    /* 0x40 */ Vec *unk_40;
    /* 0x44 */ Vec2f *unk_44;
    /* 0x48 */ void *unk_48;
    /* 0x4C */ UnkM406Unk120Struct2Hook unk_4C;
    /* 0x50 */ ModelData *unk_50;
} UnkM406Unk120Struct2; /* size = 0x54 */ // strongly assumed to be a copy of UnkModelDataUnk120Struct

typedef struct UnkM406Struct6 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} UnkM406Struct6; /* size = 0x08 */ // probably the same as UnkM426Struct13

typedef struct UnkM406Struct7 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
    /* 0x1C */ Mtx unk_1C;
} UnkM406Struct7; /* size = 0x4C */

typedef struct UnkM406Struct8 {
    /* 0x00 */ AnimData *unk_00;
    /* 0x04 */ AnimData *unk_04;
    /* 0x08 */ AnimData *unk_08;
    /* 0x0C */ AnimData *unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
} UnkM406Struct8; /* size = 0x2C */

typedef struct UnkM406Struct10 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ AnimData *unk_08;
} UnkM406Struct10; /* size = 0x0C */

void fn_1_292C(omObjData *object);
void fn_1_2C24(omObjData *object);
void fn_1_3158(void);
void fn_1_4568(void);
void fn_1_45BC(ModelData *arg0, Mtx arg1);
void fn_1_6304(ModelData *arg0, Mtx arg1);
void fn_1_64F8(UnkM406Struct2 *arg0);
s32 fn_1_66F4(float arg8, float *arg0);
void fn_1_67CC(ModelData *arg0);
void fn_1_6F24(void);
void fn_1_6FFC(void);
void fn_1_717C(void);
s32 fn_1_71C4(Vec arg0, Vec arg1, float arg8, float arg9, GXColor arg2);
void fn_1_7718(void);
void fn_1_77F0(void);
void fn_1_79B0(void);
s32 fn_1_79F8(Vec arg0, Vec arg1, float arg8, float arg9, GXColor arg2);
UnkM406Struct5 *fn_1_7B2C(s32 arg0);
void fn_1_7B9C(void);
void fn_1_7C4C(void);
void fn_1_7DAC(void);
s32 fn_1_7DB0(Vec arg0, Vec arg1, float arg8, GXColor arg2);
void fn_1_7ED0(void);
void fn_1_7F80(void);
void fn_1_8100(void);
s32 fn_1_8104(Vec arg0, Vec arg1, float arg8, GXColor arg2);
void fn_1_8244(s32 arg0, s32 arg1, float arg8, float arg9);
void fn_1_8F98(void);
void fn_1_91E0(void);
void fn_1_94BC(void);
void fn_1_9F78(void);
void fn_1_A278(void);
void fn_1_A2C8(ModelData *arg0, UnkM406Unk120Struct2 *arg1, Mtx arg2);
void fn_1_ADB4(ModelData *arg0, Mtx arg1);
void fn_1_B1E0(float arg8);
s16 fn_1_B474(AnimData *arg0, s16 arg1);
void fn_1_BC18(ModelData *arg0, Mtx arg1);
s16 fn_1_C4F4(s16 arg0);
void fn_1_C86C(ModelData *arg0, Mtx arg1);
void fn_1_CDD8(s32 arg0, float arg8, float arg9, float argA, float argB);
void fn_1_CF24(s32 arg0, u8 arg1, u8 arg2, u8 arg3);
s16 fn_1_D06C(ModelData *arg0, Mtx arg1, Mtx arg2, float arg8);
void fn_1_D13C(LightData *arg0, s16 arg1, Mtx arg2, Mtx arg3, float arg8);
void fn_1_D488(float arg8, Vec *arg0, Vec *arg1, Vec *arg2);
void fn_1_D518(Mtx arg0, Vec *arg1);
float fn_1_D5CC(Vec *arg0, Vec *arg1, float arg8, float arg9);

SHARED_SYM extern u32 GlobalCounter;

Vec lbl_1_data_F0[0x46] = {
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

Vec lbl_1_data_438[0x46] = {
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

Vec lbl_1_data_780[3] = {
    { 725.7116f, -20607.168f, -35686.844f },
    { -3135.352f, -23367.234f, -40490.824f },
    { -282.94498f, -26285.674f, -45528.754f },
};

s16 lbl_1_data_7A4 = -1;

s32 lbl_1_data_7A8[7] = {
    DATA_MAKE_NUM(DATADIR_M406, 35),
    DATA_MAKE_NUM(DATADIR_M406, 36),
    DATA_MAKE_NUM(DATADIR_M406, 37),
    DATA_MAKE_NUM(DATADIR_M406, 38),
    DATA_MAKE_NUM(DATADIR_M406, 39),
    DATA_MAKE_NUM(DATADIR_M406, 40),
    DATA_MAKE_NUM(DATADIR_M406, 41),
};

s32 lbl_1_data_7C4[7] = {
    DATA_MAKE_NUM(DATADIR_M406, 48),
    DATA_MAKE_NUM(DATADIR_M406, 49),
    DATA_MAKE_NUM(DATADIR_M406, 50),
    DATA_MAKE_NUM(DATADIR_M406, 51),
    DATA_MAKE_NUM(DATADIR_M406, 52),
    DATA_MAKE_NUM(DATADIR_M406, 53),
    0,
};

s32 lbl_1_data_7E0[6] = {
    DATA_MAKE_NUM(DATADIR_M406, 42),
    DATA_MAKE_NUM(DATADIR_M406, 43),
    DATA_MAKE_NUM(DATADIR_M406, 44),
    DATA_MAKE_NUM(DATADIR_M406, 45),
    DATA_MAKE_NUM(DATADIR_M406, 46),
    DATA_MAKE_NUM(DATADIR_M406, 47),
};

Vec lbl_1_data_7F8 = { 0.0f, 0.0f, 0.0f };

Vec lbl_1_data_804 = { -1.0f, -2.0f, -1.0f };

GXColor lbl_1_data_810 = { 0xFF, 0xFF, 0xFF, 0xFF };

Vec lbl_1_data_814 = { 0.0f, 2500.0f, -500.0f };

Vec lbl_1_data_820 = { 0.0f, 1.0f, 0.0f };

Vec lbl_1_data_82C = { 0.0f, 0.0f, 0.0f };

Vec lbl_1_data_838 = { 0.0f, 0.0f, 0.0f };

Vec lbl_1_data_844 = { 0.0f, 1.0f, -1.0f };

GXColor lbl_1_data_850[8] = {
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xC4, 0x2F, 0, 0 },
    { 0x45, 0x1C, 0x40, 0 },
    { 0xC4, 0x2F, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0x80, 0x80, 0x80, 0xFF },
};

Process *lbl_1_bss_D4;
omObjData *lbl_1_bss_D0;
omObjData *lbl_1_bss_CC;
omObjData *lbl_1_bss_C8;
omObjData *lbl_1_bss_C4;
s32 lbl_1_bss_C0;
s32 lbl_1_bss_BC;
UnkM406Struct2 *lbl_1_bss_B8;
s32 lbl_1_bss_B4;
UnkM406Struct10 *lbl_1_bss_B0;
UnkM406Struct10 *lbl_1_bss_AC;
UnkM406Struct6 *lbl_1_bss_A8;
UnkM406Struct6 *lbl_1_bss_A4;
UnkM406Struct7 *lbl_1_bss_A0;
UnkM406Struct8 *lbl_1_bss_9C;
s32 lbl_1_bss_98;
char lbl_1_bss_8C[0xC];
UnkM406Struct5 lbl_1_bss_48;
Vec lbl_1_bss_3C;
s32 lbl_1_bss_30[3];

SHARED_SYM extern LightData Hu3DLocalLight[0x20];

omObjData *fn_1_2308(Process *arg0)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r28;

    lbl_1_bss_D4 = arg0;
    lbl_1_bss_C0 = 0;
    lbl_1_bss_BC = 1;
    lbl_1_bss_98 = -1;
    omMakeGroupEx(arg0, 1, 1);
    omMakeGroupEx(arg0, 2, 1);
    omMakeGroupEx(arg0, 3, 1);
    lbl_1_bss_D0 = omAddObjEx(arg0, 127, 0, 0, -1, fn_1_292C);
    var_r28 = Hu3DGLightCreateV(&lbl_1_data_7F8, &lbl_1_data_804, &lbl_1_data_810);
    Hu3DGLightStaticSet(var_r28, 1);
    Hu3DGLightInfinitytSet(var_r28);
    lbl_1_bss_CC = omAddObjEx(arg0, 0x7E, 0x15, 0, 1, fn_1_2C24);
    for (var_r31 = 0; var_r31 < 7; var_r31++) {
        var_r30 = lbl_1_bss_CC->model[var_r31] = Hu3DModelCreateFile(lbl_1_data_7A8[var_r31]);
        Hu3DModelShadowMapSet(var_r30);
        Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
        if (var_r31 < 6) {
            fn_1_CDD8(var_r30, 1.25f, 1.05f, 1.0f, 1.0f);
        }
        if (var_r31 < 6) {
            var_r30 = Hu3DModelCreateFile(lbl_1_data_7C4[var_r31]);
            lbl_1_bss_CC->model[var_r31 + 7] = var_r30;
        }
        else {
            var_r30 = -1;
            lbl_1_bss_CC->model[var_r31 + 7] = var_r30;
        }
        if (var_r30 != -1) {
            Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(var_r30, 5);
        }
    }
    var_r30 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 54));
    lbl_1_bss_CC->model[14] = var_r30;
    Hu3DModelPosSet(var_r30, 0.0f, 10.0f, 0.0f);
    Hu3DModelAttrSet(var_r30, HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(var_r30, 5);
    lbl_1_bss_C8 = omAddObjEx(arg0, 0x7D, 6, 0, 2, NULL);
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        lbl_1_bss_C8->model[var_r31] = Hu3DModelCreateFile(lbl_1_data_7E0[var_r31]);
        Hu3DModelAttrSet(lbl_1_bss_C8->model[var_r31], HU3D_ATTR_DISPOFF);
    }
    lbl_1_bss_C4 = omAddObjEx(arg0, 0x7D, 3, 0, 3, NULL);
    lbl_1_bss_C4->trans.x = lbl_1_data_780->x;
    lbl_1_bss_C4->trans.y = lbl_1_data_780->y;
    lbl_1_bss_C4->trans.z = lbl_1_data_780->z;
    lbl_1_bss_C4->scale.x = lbl_1_bss_C4->scale.y = lbl_1_bss_C4->scale.z = 3.0f;
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        if (var_r31 == 0) {
            lbl_1_bss_C4->model[var_r31] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 34));
        }
        else {
            lbl_1_bss_C4->model[var_r31] = Hu3DModelLink(*lbl_1_bss_C4->model);
        }
        Hu3DModelShadowSet(lbl_1_bss_C4->model[var_r31]);
        Hu3DModelScaleSet(lbl_1_bss_C4->model[var_r31], lbl_1_bss_C4->scale.x, lbl_1_bss_C4->scale.y, lbl_1_bss_C4->scale.z);
        Hu3DModelPosSet(lbl_1_bss_C4->model[var_r31], lbl_1_data_780[var_r31].x, lbl_1_data_780[var_r31].y, lbl_1_data_780[var_r31].z);
    }
    fn_1_3158();
    fn_1_6F24();
    fn_1_7718();
    fn_1_7B9C();
    fn_1_7ED0();
    fn_1_8F98();
    lbl_1_bss_30[0] = 1;
    fn_1_9F78();
    fn_1_B104(0.0f);
    fn_1_B1E0(0.0f);
    Hu3DShadowCreate(45.0f, 1000.0f, 250000.0f);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowPosSet(&lbl_1_data_814, &lbl_1_data_820, &lbl_1_data_82C);
    return lbl_1_bss_D0;
}

void fn_1_292C(omObjData *object)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    float sp8;

    float var_f31;
    float var_f30;
    float var_f29;

    var_f29 = 1000.0f + CZoom;
    var_f31 = -65.0f;
    var_f30 = 110.0f;
    sp8 = 0.0f;
    spC.x = Center.x;
    spC.y = Center.y;
    spC.z = Center.z;

    sp18.x = spC.x + (var_f29 * (sind(var_f30) * cosd(var_f31)));
    sp18.y = spC.y + (var_f29 * -sind(var_f31));
    sp18.z = spC.z + (var_f29 * (cosd(var_f30) * cosd(var_f31)));
    sp24.x = sind(var_f30) * sind(var_f31);
    sp24.y = cosd(var_f31);
    sp24.z = cosd(var_f30) * sind(var_f31);
    Hu3DShadowPosSet(&sp18, &sp24, &spC);
}

void fn_1_2BEC(void)
{
    fn_1_4568();
    fn_1_717C();
    fn_1_79B0();
    fn_1_7DAC();
    fn_1_8100();
    fn_1_94BC();
    fn_1_A278();
}

void fn_1_2C24(omObjData *object)
{
    float var_f31;

    s32 var_r30;
    s32 var_r29;

    if (!lbl_1_bss_C0) {
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            var_f31 = -(5000.0f + (10000.0f * var_r30));
            if (fabs(Center.z - var_f31) > 10000.0 || !lbl_1_bss_BC) {
                if (object->model[var_r30] != -1) {
                    Hu3DModelAttrSet(object->model[var_r30], HU3D_ATTR_DISPOFF);
                }
                var_r29 = var_r30 + 7;
                if (object->model[var_r29] != -1) {
                    Hu3DModelAttrSet(object->model[var_r29], HU3D_ATTR_DISPOFF);
                }
            }
            else {
                if (object->model[var_r30] != -1) {
                    Hu3DModelAttrReset(object->model[var_r30], HU3D_ATTR_DISPOFF);
                }
                var_r29 = var_r30 + 7;
                if (object->model[var_r29] != -1) {
                    Hu3DModelAttrReset(object->model[var_r29], HU3D_ATTR_DISPOFF);
                }
            }
        }
        var_r29 = 14;
        if (object->model[var_r29] != -1) {
            var_f31 = 25000.0f;
            if (fabs(Center.z - var_f31) < 15000.0) {
                Hu3DModelAttrSet(object->model[var_r29], HU3D_ATTR_DISPOFF);
            }
            else {
                Hu3DModelAttrReset(object->model[var_r29], HU3D_ATTR_DISPOFF);
            }
        }
        var_r29 = 6;
        if (object->model[var_r29] != -1) {
            Hu3DModelAttrSet(object->model[var_r29], HU3D_ATTR_DISPOFF);
        }
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            if (fabs(Center.z - lbl_1_data_780[var_r30].z) > 10000.0) {
                Hu3DModelAttrSet(lbl_1_bss_C4->model[var_r30], HU3D_ATTR_DISPOFF);
            }
            else {
                Hu3DModelAttrReset(lbl_1_bss_C4->model[var_r30], HU3D_ATTR_DISPOFF);
            }
        }
        return;
    }
    for (var_r30 = 0; var_r30 < 6; var_r30++) {
        if (object->model[var_r30] != -1) {
            Hu3DModelAttrSet(object->model[var_r30], HU3D_ATTR_DISPOFF);
        }
        var_r29 = var_r30 + 7;
        if (object->model[var_r29] != -1) {
            Hu3DModelAttrSet(object->model[var_r29], HU3D_ATTR_DISPOFF);
        }
    }
    var_r29 = 6;
    if (object->model[var_r29] != -1) {
        Hu3DModelAttrReset(object->model[var_r29], HU3D_ATTR_DISPOFF);
    }
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        Hu3DModelAttrSet(lbl_1_bss_C4->model[var_r30], HU3D_ATTR_DISPOFF);
    }
}

void fn_1_3064(s32 arg0)
{
    s32 var_r31;

    if (lbl_1_bss_C0 = arg0) {
        for (var_r31 = 0; var_r31 < 6; var_r31++) {
            if (lbl_1_bss_CC->model[var_r31] != -1) {
                Hu3DModelKill(lbl_1_bss_CC->model[var_r31]);
            }
            lbl_1_bss_CC->model[var_r31] = -1;
        }
        if (lbl_1_bss_CC->model[6] == -1) {
            lbl_1_bss_CC->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 41));
        }
    }
}

void fn_1_3158(void)
{
    UnkM406Struct2 *sp10[2]; // TODO sp10 should probably be a void*
    s32 sp8[2];

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    UnkM406Unk120Struct *var_r31;
    UnkM406Struct *var_r30;
    s32 var_r29;
    UnkM406Struct4 *var_r28;
    UnkM406Struct3 *var_r27;
    ModelData *var_r26;
    s32 var_r25;
    Vec *var_r24;
    GXColor *var_r23;
    s16(*var_r22)[4];
    Vec *var_r21;
    Vec2f *var_r20;
    s32 var_r19;
    void *var_r18;
    ModelData *var_r17;

    var_r19 = lbl_1_data_7A4 = Hu3DHookFuncCreate(fn_1_45BC);
    var_r26 = &Hu3DData[var_r19];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkM406Unk120Struct), var_r26->unk_48);
    var_r26->unk_120 = var_r31;
    memset(var_r31, 0, sizeof(UnkM406Unk120Struct));

    sp8[0] = Hu3DHookFuncCreate(fn_1_6304);
    Hu3DModelLayerSet(sp8[0], 7);
    var_r17 = &Hu3DData[sp8[0]];
    var_r17->unk_120 = var_r31;

    sp8[1] = Hu3DLLightCreateV(var_r19, &lbl_1_data_838, &lbl_1_data_844, lbl_1_data_850);
    Hu3DLLightStaticSet(var_r19, sp8[1], 1);
    Hu3DLLightInfinitytSet(var_r19, sp8[1]);

    var_r31->unk_00 = 0;
    var_r31->unk_04 = var_r19;
    var_r31->unk_08 = 0;
    var_r31->unk_0C = 0.0f;
    var_r31->unk_10 = 0.0f;
    var_r31->unk_14 = 2000.0f;
    var_r31->unk_28 = 0;
    var_r31->unk_A8 = HuDataReadNum(DATA_MAKE_NUM(DATADIR_M406, 61), MEMORY_DEFAULT_NUM);
    var_r31->unk_AC = 0x80;
    var_r31->unk_B0 = 0x80;
    var_r31->unk_B4 = 0.0f;
    var_r31->unk_B8 = 0.0f;
    var_r31->unk_BC = HuDataReadNum(DATA_MAKE_NUM(DATADIR_M406, 62), MEMORY_DEFAULT_NUM);
    var_r31->unk_C0 = 0x80;
    var_r31->unk_C4 = 0x80;
    var_r31->unk_C8 = 0.0f;
    var_r31->unk_CC = 0.0f;
    var_r31->unk_2C = HuMemDirectMallocNum(HEAP_DATA, 105 * sizeof(UnkM406Struct3), var_r26->unk_48);
    memset(var_r31->unk_2C, 0, 105 * sizeof(UnkM406Struct3));
    var_r27 = var_r31->unk_2C;

    for (var_r29 = 0; var_r29 < 105; var_r29++, var_r27++) {
        var_r27->unk_00 = var_r29 / 3;
        var_r27->unk_04 = 0.33333334f * (var_r29 % 3);
        switch (var_r29 % 4) {
            case 0:
                var_r25 = var_r27->unk_08 = frand() & 0x1F;
                break;
            case 1:
                var_r27->unk_08 = var_r25 + 10;
                break;
            default:
                var_r27->unk_08 = var_r25 + 20;
                break;
        }
        var_r27->unk_0C = -1;
        var_r27->unk_10 = 0.0f;
        if (var_r29 == 0 || var_r29 == 104) {
            var_r27->unk_14 = 0.3f;
        }
        if (var_r29 == 1 || var_r29 == 103) {
            var_r27->unk_14 = 0.6f;
        }
        else {
            var_r27->unk_14 = 1.0f;
        }
        var_r27->unk_18.x = var_r27->unk_18.y = var_r27->unk_18.z = 0.0f;
        var_r27->unk_24 = 0;
    }
    var_r31->unk_30 = HuMemDirectMallocNum(HEAP_DATA, 12 * sizeof(UnkM406Struct4), var_r26->unk_48);
    memset(var_r31->unk_30, 0, 12 * sizeof(UnkM406Struct4));
    var_r28 = var_r31->unk_30;

    for (var_r29 = 0; var_r29 < 12; var_r29++, var_r28++) {
        switch (var_r29) {
            case 0:
                var_r28->unk_00 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 56));
                break;
            case 1:
                var_r28->unk_00 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 57));
                break;
            case 2:
                var_r28->unk_00 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 58));
                break;
            default:
                var_r28->unk_00 = Hu3DModelLink(var_r31->unk_30[var_r29 % 3].unk_00);
                break;
        }
        if (var_r29 < 3) {
            fn_1_CF24(var_r28->unk_00, 184, 207, 214);
        }
        var_r28->unk_04 = frand() & 1;
        var_r28->unk_08 = 0;
        var_r28->unk_0C = frand() % 60;
        var_r28->unk_10 = 0.2f + (0.6f * (0.007874016f * (frand() & 0x7F)));
        var_r28->unk_14 = var_r28->unk_18 = 0.0f;
        var_r28->unk_1C = 0.0f;
        var_r28->unk_20 = var_r28->unk_24 = 0.0f;
        var_r28->unk_28 = 0.0f;
        var_r28->unk_2C = 0.0f;
        var_r28->unk_3C.x = var_r28->unk_3C.y = var_r28->unk_3C.z = 0.0f;
    }

    var_r31->unk_34.x = var_r31->unk_34.y = var_r31->unk_34.z = 0.0f;
    var_r31->unk_40.x = var_r31->unk_40.y = var_r31->unk_40.z = 0.0f;
    var_r31->unk_7C = 0;

    var_r31->unk_80 = 1050;
    var_r31->unk_84 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_80 * sizeof(Vec), var_r26->unk_48);
    memset(var_r31->unk_84, 0, var_r31->unk_80 * sizeof(Vec));

    var_r31->unk_88 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_80 * sizeof(Vec), var_r26->unk_48);
    memset(var_r31->unk_88, 0, var_r31->unk_80 * sizeof(Vec));

    var_r31->unk_8C = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_80 * sizeof(Vec2f), var_r26->unk_48);
    memset(var_r31->unk_8C, 0, var_r31->unk_80 * sizeof(Vec2f));

    var_r31->unk_90 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_80 * sizeof(GXColor), var_r26->unk_48);
    memset(var_r31->unk_90, 0, var_r31->unk_80 * sizeof(GXColor));

    var_r31->unk_94 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_80 * sizeof(UnkM406Struct), var_r26->unk_48);
    memset(var_r31->unk_94, 0, var_r31->unk_80 * sizeof(UnkM406Struct));

    var_r31->unk_98 = 986;
    var_r31->unk_9C = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_98 * 8, var_r26->unk_48);
    memset(var_r31->unk_9C, 0, var_r31->unk_98 * 8);

    var_r24 = var_r31->unk_84;
    var_r21 = var_r31->unk_88;
    var_r20 = var_r31->unk_8C;
    var_r23 = var_r31->unk_90;
    var_r30 = var_r31->unk_94;
    var_f30 = -500.0f;
    var_f29 = -1000.0f;
    var_f28 = 0.0f;
    for (var_r29 = 0; var_r29 < 30; var_r29++) {
        for (var_r25 = 0; var_r25 < 35; var_r25++) {
            var_r24->x = var_f30;
            var_r24->y = var_f28;
            var_r24->z = var_f29;

            var_f30 += 29.411764f;
            var_f28 = 0.0f;

            var_r21->x = 0.0f;
            var_r21->z = 0.0f;
            var_r21->y = 1.0f;

            var_r20->x = 0.0f;
            var_r20->y = 0.0f;

            var_r23->r = var_r23->g = var_r23->b = var_r23->a = 0xFF;
            if (var_r29 == 0) {
                var_r30->unk_01 = 1;
                if (var_r29 < 6) {
                    var_r30->unk_08 = (6 - var_r29) / 6.0f;
                }
                else {
                    var_r30->unk_08 = 1.0f;
                }
            }
            else {
                var_r30->unk_01 = 0;
                var_r30->unk_08 = 0.0f;
            }
            if (!var_r25 || var_r25 == 34 || !var_r29) {
                var_r30->unk_00 = 0;
                var_r30->unk_04 = 0.0f;
            }
            else {
                var_r30->unk_00 = 1;
                if (var_r29 < 3) {
                    var_r30->unk_04 = 0.5f + (0.5f * (var_r29 / 3.0f));
                    var_r30->unk_04 = sind(90.0f * var_r30->unk_04);
                }
                else {
                    var_r30->unk_04 = 1.0f;
                }
            }
            var_r30->unk_10.x = var_r24->x;
            var_r30->unk_10.y = var_r24->y;
            var_r30->unk_10.z = var_r24->z;
            var_r30->unk_1C.x = var_r30->unk_1C.y = var_r30->unk_1C.z = 0.0f;
            var_r30->unk_0C = 200.0 * sind(90.0f * (var_r29 / 29.0f));
            if (var_r25 < 6) {
                var_f31 = var_r25 / 6.0f;
                var_r30->unk_04 = var_r30->unk_04 * sind(90.0f * var_f31);
                var_r30->unk_0C = var_r30->unk_0C * sind(90.0f * var_f31);
            }
            else if (var_r25 > 28) {
                var_f31 = (var_r25 - 28) / 6.0f;
                var_r30->unk_04 = var_r30->unk_04 * cosd(90.0f * var_f31);
                var_r30->unk_0C = var_r30->unk_0C * cosd(90.0f * var_f31);
            }
            var_r30->unk_28 = var_r25 / 34.0f;
            var_r30->unk_2C = (var_r29 * 2) / 29.0f;
            if (var_r30->unk_28 > 1.0f) {
                var_r30->unk_28 = fmod(var_r30->unk_28, 1.0);
            }
            if (var_r30->unk_2C > 1.0f) {
                var_r30->unk_2C = fmod(var_r30->unk_2C, 1.0);
            }
            var_r24++;
            var_r21++;
            var_r20++;
            var_r23++;
            var_r30++;
        }
        var_f30 = -500.0f;
        var_f29 += 68.965515f;
    }
    var_r22 = var_r31->unk_9C;
    for (var_r29 = 0; var_r29 < 29; var_r29++) {
        for (var_r25 = 0; var_r25 < 34; var_r22++, var_r25++) {
            (*var_r22)[0] = var_r25 + (var_r29 * 35);
            (*var_r22)[1] = var_r25 + 1 + (var_r29 * 35);
            (*var_r22)[2] = var_r25 + 1 + ((var_r29 + 1) * 35);
            (*var_r22)[3] = var_r25 + ((var_r29 + 1) * 35);
        }
    }
    var_r18 = HuMemDirectMallocNum(HEAP_DATA, 0x10000, var_r26->unk_48);
    sp10[0] = var_r18;
    DCFlushRange(var_r18, 0x10000);
    GXBeginDisplayList(sp10[0], 0x10000);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 70);
    for (var_r29 = 0; var_r29 < 35; var_r29++) {
        // TODO fix up
        GXUnknownu16(var_r29 + 35);
        GXUnknownu16(var_r29 + 35);
        GXUnknownu16(var_r29 + 35);
        GXUnknownu16(var_r29);
        GXUnknownu16(var_r29);
        GXUnknownu16(var_r29);
    }
    var_r31->unk_A0 = GXEndDisplayList();
    if (var_r31->unk_A0 >= 0x10000) {
        OSReport("ERROR! GList test size over! \n");
    }
    var_r31->unk_A4 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_A0, var_r26->unk_48);
    memcpy(var_r31->unk_A4, var_r18, var_r31->unk_A0);
    DCFlushRange(var_r31->unk_A4, var_r31->unk_A0);
    HuMemDirectFree(var_r18);
    lbl_1_bss_B4 = 70;
    lbl_1_bss_B8 = HuMemDirectMallocNum(HEAP_DATA, lbl_1_bss_B4 * 32, var_r26->unk_48);
    memset(lbl_1_bss_B8, 0, lbl_1_bss_B4 * 32);
    fn_1_64F8(lbl_1_bss_B8);
    sp10[1] = &lbl_1_bss_B8[lbl_1_bss_B4 - 1];
    var_r31->unk_18 = sp10[1]->unk_04;
    var_r31->unk_1C = 0.0f;
    var_r31->unk_20 = -1;
    var_r31->unk_24 = 0;
}

GXColor lbl_1_data_88F = { 0xFF, 0xFF, 0xFF, 0xFF };
GXColor lbl_1_data_893 = { 0xB3, 0xBB, 0xC2, 0xFF };
GXColor lbl_1_data_897 = { 0xFF, 0xFF, 0xFF, 0xFF };
GXColor lbl_1_data_89B = { 0xFF, 0xFF, 0xFF, 0x40 };
GXColor lbl_1_data_89F = { 0xFF, 0xFF, 0xFF, 0xFF };

float lbl_1_data_8A4[4] = { 1000.0f, 200.0f, 600.0f, 1200.0f };

float lbl_1_data_8B4[4] = { 1.0f, 0.6f, 0.3f, 0.425f };

Vec lbl_1_data_8C4 = { 0.0f, -34700.0f, -62094.0f };

Vec lbl_1_data_8D0 = { 0.0f, 1.0f, 0.0f };

GXColor lbl_1_data_8DC = { 0xFF, 0xFF, 0xFF, 0xFF };

Vec lbl_1_data_8E0[4] = {
    { -0.5f, 0.5f, 0.0f },
    { 0.5f, 0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f },
};

Vec2f lbl_1_data_910[4] = { { 0.0f, 0.0f }, { 0.25f, 0.0f }, { 0.25f, 0.25f }, { 0.0f, 0.25f } };

Vec lbl_1_data_930[4] = {
    { 0.0f, 0.5f, 0.0f },
    { 0.5f, 0.0f, 0.0f },
    { 0.0f, -0.5f, 0.0f },
    { -0.5f, 0.0f, 0.0f },
};

void fn_1_4084(void)
{
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    void *spC;
    float sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    UnkM406Unk120Struct *var_r31;
    s32 var_r30;
    UnkM406Struct *var_r29;
    Vec *var_r28;
    s32 var_r27;
    s32 var_r26;
    ModelData *var_r25;

    spC = lbl_1_bss_B8;
    var_r25 = &Hu3DData[lbl_1_data_7A4];
    var_r31 = var_r25->unk_120;
    if (!var_r31->unk_28) {
        if (++var_r31->unk_24 >= 1 && var_r31->unk_20 == -1) {
            sp28.x = 0.5f * (var_r31->unk_34.x + var_r31->unk_40.x);
            sp28.y = 0.5f * (var_r31->unk_34.y + var_r31->unk_40.y);
            sp28.z = 0.5f * (var_r31->unk_34.z + var_r31->unk_40.z);
            var_r31->unk_20 = HuAudFXEmiterPlay(1337, &sp28);
        }
        else if (var_r31->unk_20 != -1) {
            sp28.x = 0.5f * (var_r31->unk_34.x + var_r31->unk_40.x);
            sp28.y = 0.5f * (var_r31->unk_34.y + var_r31->unk_40.y);
            sp28.z = 0.5f * (var_r31->unk_34.z + var_r31->unk_40.z);
            HuAudFXEmiterUpDate(var_r31->unk_20, &sp28);
        }
    }
    else if (var_r31->unk_20 != -1) {
        HuAudFXStop(var_r31->unk_20);
        var_r31->unk_20 = -1;
    }
    var_r31->unk_0C = var_r31->unk_0C + var_r31->unk_10;
    if (var_r31->unk_0C > var_r31->unk_18) {
        var_r31->unk_1C = var_r31->unk_0C - var_r31->unk_18;
        var_r31->unk_0C = var_r31->unk_18;
    }
    else {
        var_r31->unk_1C = 0.0f;
    }
    var_r28 = var_r31->unk_84;
    var_r29 = var_r31->unk_94;
    var_f30 = 0.0f;
    var_f28 = var_r31->unk_14 / 29.0f;

    for (var_r27 = 0; var_r27 < 30; var_r27++) {
        var_r30 = fn_1_66F4(var_r31->unk_0C - var_f30, &sp8);
        var_f30 += var_f28;
        if (var_r30 < 0) {
            var_r30 = 0;
            sp1C = lbl_1_data_F0[var_r30];
            sp10 = lbl_1_data_438[var_r30];
        }
        else if (var_r30 < (lbl_1_bss_B4 - 1)) {
            fn_1_D488(sp8, &lbl_1_data_F0[var_r30], &lbl_1_data_F0[var_r30 + 1], &sp1C);
            fn_1_D488(sp8, &lbl_1_data_438[var_r30], &lbl_1_data_438[var_r30 + 1], &sp10);
        }
        else {
            var_r30 = lbl_1_bss_B4 - 1;
            sp1C = lbl_1_data_F0[var_r30];
            sp10 = lbl_1_data_438[var_r30];
        }
        if (var_r27 == 0) {
            var_r31->unk_34 = sp1C;
            var_r31->unk_40 = sp10;
            var_r31->unk_7C = var_r30;
            var_f29 = atan2d(var_r31->unk_40.x - var_r31->unk_34.x, var_r31->unk_40.z - var_r31->unk_34.z);
            mtxRot(var_r31->unk_4C, 0.0f, var_f29, 0.0f);
        }
        for (var_r26 = 0, var_f31 = 0.0f; var_r26 < 35; var_r28++, var_r29++, var_r26++) {
            fn_1_D488(var_f31, &sp1C, &sp10, var_r28);
            var_r29->unk_10 = *var_r28;
            var_f31 += 0.029411765f;
            var_r29->unk_1C = lbl_1_bss_B8[var_r30].unk_08;
        }
    }
}

void fn_1_4568(void)
{
    UnkM406Unk120Struct *var_r31;
    ModelData *var_r30;

    var_r30 = &Hu3DData[lbl_1_data_7A4];
    var_r31 = var_r30->unk_120;
    HuMemDirectFree(var_r31->unk_A8);
}

void fn_1_45BC(ModelData *arg0, Mtx arg1)
{
    Mtx sp10;

    UnkM406Unk120Struct *var_r31;
    s16 var_r30;
    s16 var_r29;
    s16 var_r26;

    var_r31 = arg0->unk_120;
    if (!var_r31->unk_08) {
        fn_1_6304(arg0, arg1);
    }
    if (!var_r31->unk_28) {
        GXLoadPosMtxImm(arg1, 0);
        MTXInvXpose(arg1, sp10);
        GXLoadNrmMtxImm(sp10, 0);
        var_r26 = fn_1_D06C(arg0, Hu3DCameraMtx, Hu3DCameraMtxXPose, 2.0f);
        GXSetNumTevStages(1);
        GXSetNumTexGens(0);
        GXSetNumChans(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_NRM, 0x36, GX_FALSE, 125);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, var_r26, GX_DF_CLAMP, GX_AF_SPEC);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXSetZCompLoc(GX_TRUE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXSetChanAmbColor(GX_COLOR0A0, lbl_1_data_893);
        GXSetChanMatColor(GX_COLOR0A0, lbl_1_data_88F);
        DCFlushRangeNoSync(var_r31->unk_84, var_r31->unk_80 * sizeof(Vec));
        DCFlushRangeNoSync(var_r31->unk_88, var_r31->unk_80 * sizeof(Vec));
        DCFlushRangeNoSync(var_r31->unk_8C, var_r31->unk_80 * sizeof(Vec2f));
        DCFlushRangeNoSync(var_r31->unk_90, var_r31->unk_80 * sizeof(GXColor));
        PPCSync();
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSETARRAY(GX_VA_POS, var_r31->unk_84, var_r31->unk_80 * sizeof(Vec), sizeof(Vec));
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
        GXSETARRAY(GX_VA_NRM, var_r31->unk_88, var_r31->unk_80 * sizeof(Vec), sizeof(Vec));
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSETARRAY(GX_VA_CLR0, var_r31->unk_90, var_r31->unk_80 * sizeof(GXColor), sizeof(GXColor));
        GXCallDisplayListNative(var_r31->unk_A4, var_r31->unk_A0);
        for (var_r30 = 1; var_r30 < 29; var_r30++) {
            var_r29 = var_r30 * 35;
            GXSETARRAY(GX_VA_POS, &var_r31->unk_84[var_r29], 35 * sizeof(Vec), sizeof(Vec));
            GXSETARRAY(GX_VA_NRM, &var_r31->unk_88[var_r29], 35 * sizeof(Vec), sizeof(Vec));
            GXSETARRAY(GX_VA_CLR0, &var_r31->unk_90[var_r29], 35 * sizeof(GXColor), sizeof(GXColor));
            GXCallDisplayListNative(var_r31->unk_A4, var_r31->unk_A0);
        }
    }
}

void fn_1_4964(ModelData *arg0)
{
    UnkM406Struct5 spD0;
    Vec spC4;
    Vec spB8;
    Vec spAC;
    Vec spA0;
    Vec2f sp50;
    Vec2f sp48;
    GXColor sp3C;
    float sp38;

    float var_f31;
    float var_f30;
    float var_f29;

    UnkM406Struct4 *var_r31;
    UnkM406Unk120Struct *var_r30;
    UnkM406Struct3 *var_r29;
    UnkM406Struct *var_r28;
    s32 var_r27;
    s32 var_r26;
    Vec *var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    Vec *var_r21;
    Vec2f *var_r20;
    GXColor *var_r19;

    var_r30 = arg0->unk_120;

    if (var_r30->unk_28) {
        if (!omPauseChk()) {
            fn_1_67CC(arg0);
        }
        return;
    }
    if (!omPauseChk()) {
        var_r30->unk_B4 += 0.005f;
        var_r30->unk_B8 += (0.007499999832361937 + (0.001 * var_r30->unk_1C));
        if (fabs(var_r30->unk_B4) > 1.0) { // 1.0 or 1.0f?
            var_r30->unk_B4 = fmod(var_r30->unk_B4, 1.0);
        }
        if (var_r30->unk_B4 < 0.0f) {
            var_r30->unk_B4 += 1.0f;
        }
        if (fabs(var_r30->unk_B8) > 1.0) {
            var_r30->unk_B8 = fmod(var_r30->unk_B8, 1.0);
        }
        if (var_r30->unk_B8 < 0.0f) {
            var_r30->unk_B8 += 1.0f;
        }
        var_r30->unk_C8 += -0.005f;
        var_r30->unk_CC += (-0.007499999832361937 + (0.001 * var_r30->unk_1C));
        if (fabs(var_r30->unk_C8) > 1.0) {
            var_r30->unk_C8 = fmod(var_r30->unk_C8, 1.0);
        }
        if (var_r30->unk_C8 < 0.0f) {
            var_r30->unk_C8 += 1.0f;
        }
        if (fabs(var_r30->unk_CC) > 1.0) {
            var_r30->unk_CC = fmod(var_r30->unk_CC, 1.0);
        }
        if (var_r30->unk_CC < 0.0f) {
            var_r30->unk_CC += 1.0f;
        }
    }
    var_r25 = var_r30->unk_84;
    var_r21 = var_r30->unk_88;
    var_r20 = var_r30->unk_8C;
    var_r19 = var_r30->unk_90;
    var_r28 = var_r30->unk_94;
    sp50.x = var_r30->unk_AC - 1;
    sp50.y = var_r30->unk_B0 - 1;
    sp48.x = var_r30->unk_C0 - 1;
    sp48.y = var_r30->unk_C4 - 1;
    for (var_r27 = 0; var_r27 < var_r30->unk_80; var_r27++) {
        *var_r25 = var_r28->unk_10;
        if (var_r28->unk_00 || var_r28->unk_01) {
            var_r23 = (s32)(sp50.x * (var_r28->unk_28 + var_r30->unk_B4)) & 0x7F;
            var_r22 = (s32)(sp50.y * (var_r28->unk_2C + var_r30->unk_B8)) & 0x7F;
            var_f31 = var_r30->unk_A8[(var_r22 * var_r30->unk_AC) + var_r23];
            var_r23 = (s32)(sp48.x * (var_r28->unk_28 + var_r30->unk_C8)) & 0x7F;
            var_r22 = (s32)(sp48.y * (var_r28->unk_2C + var_r30->unk_CC)) & 0x7F;
            var_f31 += var_r30->unk_BC[(var_r22 * var_r30->unk_C0) + var_r23];
            if (var_r28->unk_00) {
                var_r25->y = var_r28->unk_10.y + var_r28->unk_0C + (100.0f * (0.003921569f * (var_r28->unk_04 * var_f31)));
            }
            if (var_r28->unk_01) {
                var_r25->z = var_r28->unk_10.z - (50.0f * (0.003921569f * (var_r28->unk_08 * var_f31)));
            }
            (void)var_f31;
            (void)var_f31;
            (void)var_f31;
            (void)var_f31;
        }
        var_r25++;
        var_r21++;
        var_r20++;
        var_r19++;
        var_r28++;
    }
    if (omPauseChk()) {
        return;
    }
    for (var_r27 = 0; var_r27 < 5; var_r27++) {
        var_r26 = (u32)frand() % 34;
        fn_1_D488(0.007874016f * (frand() & 0x7F), &var_r30->unk_84[var_r26], &var_r30->unk_84[var_r26 + 1], &spC4);
        spC4.x += 10.0f * var_r30->unk_94->unk_1C.x;
        spC4.z += 10.0f * var_r30->unk_94->unk_1C.z;
        spA0.y = 5.0f + (5.0f * (0.007874016f * (frand() & 0x7F)));
        spA0.x = spA0.z = 0.0f;
        var_r26 = (frand() & 0x1F) + 0xE0;
        sp3C.r = 0.96f * var_r26;
        sp3C.g = 0.98f * var_r26;
        sp3C.b = (float)var_r26;
        sp3C.a = 0xC8;
        fn_1_71C4(spC4, spA0, 100.0f + (50.0f * (0.007874016f * (frand() & 0x7F))), -0.1f, sp3C);
    }
    var_r29 = var_r30->unk_2C;
#ifdef NON_MATCHING
    memset(&lbl_1_bss_48, 0, sizeof(UnkM406Struct5));
#else
    memset(lbl_1_bss_48, 0, sizeof(UnkM406Struct5));
#endif
    for (var_r27 = 0; var_r27 < 105; var_r27++, var_r29++) {
        fn_1_D488(var_r29->unk_04, &var_r30->unk_84[var_r29->unk_00], &var_r30->unk_84[var_r29->unk_00 + 1], &var_r29->unk_18);
        if (var_r29->unk_08 >= 0) {
            var_r29->unk_08--;
        }
        else {
            var_r29->unk_24 = fn_1_7B2C(var_r29->unk_0C);
            if (var_r29->unk_24 == NULL) {
                var_r29->unk_24 = &lbl_1_bss_48;
            }
            if (var_r29->unk_24->unk_28 <= 0.0f) {
                spC4 = var_r29->unk_18;
                spA0.x = spA0.y = spA0.z = 0.0f;
                var_r26 = (frand() & 0x1F) + 0xE0;
                sp3C.r = 0.96f * var_r26;
                sp3C.g = 0.98f * var_r26;
                sp3C.b = (float)var_r26;
                sp3C.a = 0xFF;
                if (frand() & 1) {
                    var_f31 = 0.05f;
                }
                else {
                    var_f31 = -0.05f;
                }
                var_r29->unk_10 = 0.01f * (100.0f * (0.007874016f * (frand() & 0x7F)));
                var_r29->unk_0C = fn_1_79F8(spC4, spA0, 75.0f + (var_r29->unk_14 * (75.0f * (0.007874016f * (frand() & 0x7F)))), var_f31, sp3C);
            }
            else {
                var_r29->unk_18.y += var_r29->unk_10;
                var_r29->unk_24->unk_30 = var_r29->unk_18;
            }
        }
    }
    sp3C.r = sp3C.g = sp3C.b = sp3C.a = 0xFF;
    fn_1_D488(0.007874016f * (frand() & 0x7F), &var_r30->unk_84[0], &var_r30->unk_84[34], &spC4);
    if ((frand() & 3) == 0) {
        var_f31 = 45.0f + (30.0f * (0.007874016f * (frand() & 0x7F)));
        var_f29 = 0.75f + (0.75f * (0.007874016f * (frand() & 0x7F)));
    }
    else {
        var_f31 = -(15.0f * (0.007874016f * (frand() & 0x7F)));
        var_f29 = 1.75f + (0.75f * (0.007874016f * (frand() & 0x7F)));
    }
    if (var_r30->unk_10 != 0.0f) {
        var_f30 = 15.000001f / var_r30->unk_10;
    }
    else {
        var_f30 = 1.0f;
    }
    spA0.y = var_f30 * ((7.5000005f * var_f29) * sind(var_f31));
    var_f30 = (0.75f * var_r30->unk_10) + (7.5000005f * var_f29) * cosd(var_f31);
    var_f30 = var_f30;
    spA0.x = var_r30->unk_94->unk_1C.x * var_f30;
    spA0.z = var_r30->unk_94->unk_1C.z * var_f30;

    fn_1_7DB0(spC4, spA0, 7.5f, sp3C);
    var_r31 = var_r30->unk_30;
    for (var_r27 = 0; var_r27 < 12; var_r27++, var_r31++) {
        if (var_r31->unk_08 == 0) {
            if (var_r31->unk_0C <= 0) {
                var_f30 = 0.5f + (0.75f * (0.007874016f * (frand() & 0x7F)));
                Hu3DModelScaleSet(var_r31->unk_00, var_f30, var_f30, var_f30);
                var_r31->unk_04 = frand() & 1;
                switch (var_r31->unk_04) {
                    case 0:
                        var_r31->unk_10 = 0.1f + (0.8f * (0.007874016f * (frand() & 0x7F)));
                        var_r31->unk_14 = var_r31->unk_18 = 0.0f;
                        var_r31->unk_20 = var_r31->unk_24 = 0.0f;
                        var_r31->unk_08 = 0;
                        var_r31->unk_0C = 0;
                        var_r31->unk_1C = 100.0f * (0.5f + (0.75f * (0.007874016f * (frand() & 0x7F))));
                        var_r31->unk_28 = 0.0f;
                        var_r31->unk_2C = 15.0f + (15.0f * (0.007874016f * (frand() & 0x7F)));
                        break;
                    case 1:
                        var_r31->unk_10 = 0.1f + (0.8f * (0.007874016f * (frand() & 0x7F)));
                        var_r31->unk_14 = var_r31->unk_18 = 0.0f;
                        var_r31->unk_20 = var_r31->unk_24 = 0.0f;
                        var_r31->unk_08 = 0;
                        var_r31->unk_0C = 0;
                        var_r31->unk_1C = 100.0f * (0.5f + (0.007874016f * (frand() & 0x7F)));
                        var_r31->unk_28 = 100.0f * (0.07f + (0.03f * (0.007874016f * (frand() & 0x7F))));
                        var_r31->unk_2C = 15.0f + (15.0f * (0.007874016f * (frand() & 0x7F)));
                        break;
                    default:
                        break;
                }
            }
            else {
                Hu3DModelAttrSet(var_r31->unk_00, HU3D_ATTR_DISPOFF);
                var_r31->unk_08 = -1;
                var_r31->unk_0C--;
            }
        }
        else if (var_r31->unk_08 >= 0) {
            var_r24 = fn_1_66F4(var_r30->unk_0C + var_r31->unk_18, &sp38);
            if (var_r24 >= 0 && var_r24 < (lbl_1_bss_B4 - 1)) {
                fn_1_D488(sp38, &lbl_1_data_F0[var_r24], &lbl_1_data_F0[var_r24 + 1], &spB8);
                fn_1_D488(sp38, &lbl_1_data_438[var_r24], &lbl_1_data_438[var_r24 + 1], &spAC);
                fn_1_D488(var_r31->unk_10, &spB8, &spAC, &var_r31->unk_3C);
                Hu3DModelAttrReset(var_r31->unk_00, HU3D_ATTR_DISPOFF);
            }
            else {
                Hu3DModelAttrSet(var_r31->unk_00, HU3D_ATTR_DISPOFF);
                var_r31->unk_08 = -1;
                continue;
            }

            switch (var_r31->unk_04) {
                case 0:
                    var_r31->unk_18 = var_r31->unk_1C * sind(5.0f * var_r31->unk_08);
                    var_r31->unk_20 = var_r31->unk_20 - var_r31->unk_2C;
                    Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_3C.x, var_r31->unk_3C.y, var_r31->unk_3C.z);
                    Hu3DModelRotSet(var_r31->unk_00, var_r31->unk_20, var_r31->unk_24, 0.0f);
                    break;
                case 1:
                    var_r31->unk_18 = var_r31->unk_1C * sind((float)var_r31->unk_08);
                    var_r31->unk_20 = var_r31->unk_20 - var_r31->unk_2C;
                    var_r31->unk_14 = var_r31->unk_14 + var_r31->unk_28;
                    if (var_r31->unk_14 < 0.0f) {
                        var_f30 = 0.65 + (0.15 * (0.007874016f * (frand() & 0x7F)));
                        var_f30 = var_f30;
                        var_r31->unk_14 = 0.0f;
                        var_r31->unk_28 = var_r31->unk_28 * -var_f30;
                    }
                    var_r31->unk_28 = var_r31->unk_28 - 0.32666668f;
                    var_r31->unk_3C.y += var_r31->unk_14;
                    Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_3C.x, var_r31->unk_3C.y, var_r31->unk_3C.z);
                    Hu3DModelRotSet(var_r31->unk_00, var_r31->unk_20, var_r31->unk_24, 0.0f);
                    break;
                default:
                    break;
            }
        }
        if (var_r31->unk_18 < (-0.1f * var_r31->unk_1C)) {
            var_r31->unk_08 = -1;
            var_r31->unk_0C = frand() & 0x1F;
        }
        var_r31->unk_08++;
    }
    var_r30->unk_00++;
}

void fn_1_6174(ModelData *arg0)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;

    UnkM406Unk120Struct *var_r31;
    s16(*var_r30)[4];
    s32 var_r29;
    Vec *var_r28;

    var_r31 = arg0->unk_120;
    memset(var_r31->unk_88, 0, var_r31->unk_80 * sizeof(Vec));
    for (var_r29 = 0, var_r30 = var_r31->unk_9C; var_r29 < var_r31->unk_98; var_r29++, var_r30++) {
        VECSubtract(&var_r31->unk_84[(*var_r30)[1]], &var_r31->unk_84[(*var_r30)[0]], &sp14);
        VECSubtract(&var_r31->unk_84[(*var_r30)[2]], &var_r31->unk_84[(*var_r30)[1]], &sp8);
        VECCrossProduct(&sp14, &sp8, &sp20);

        VECAdd(&var_r31->unk_88[(*var_r30)[0]], &sp20, &var_r31->unk_88[(*var_r30)[0]]);
        VECAdd(&var_r31->unk_88[(*var_r30)[1]], &sp20, &var_r31->unk_88[(*var_r30)[1]]);
        VECAdd(&var_r31->unk_88[(*var_r30)[2]], &sp20, &var_r31->unk_88[(*var_r30)[2]]);
        VECAdd(&var_r31->unk_88[(*var_r30)[3]], &sp20, &var_r31->unk_88[(*var_r30)[3]]);
    }
    for (var_r29 = 0, var_r28 = var_r31->unk_88; var_r29 < var_r31->unk_80; var_r29++) {
        VECNormalize(var_r28, var_r28);
    }
}

void fn_1_6304(ModelData *arg0, Mtx arg1)
{
    UnkM406Unk120Struct *var_r28;
    ModelData *var_r27;

    var_r28 = arg0->unk_120;
    var_r27 = &Hu3DData[var_r28->unk_04];
    if (!omPauseChk() && lbl_1_bss_30[0]) {
        fn_1_4084();
        fn_1_6FFC();
        fn_1_77F0();
        fn_1_7C4C();
        fn_1_7F80();
        fn_1_91E0();
    }
    fn_1_4964(var_r27);
    fn_1_6174(var_r27);
    var_r28->unk_08 = 1;
}

void fn_1_64F8(UnkM406Struct2 *arg0)
{
    float var_f31; // ! - uninitialized

    UnkM406Struct2 *var_r31;
    s32 var_r30;
    UnkM406Struct2 *var_r28;

    for (var_r30 = 0, var_r31 = arg0; var_r30 < lbl_1_bss_B4; var_r30++, var_r31++) {
        var_r31->unk_14.x = 0.5f * (lbl_1_data_F0[var_r30].x + lbl_1_data_438[var_r30].x);
        var_r31->unk_14.y = 0.5f * (lbl_1_data_F0[var_r30].y + lbl_1_data_438[var_r30].y);
        var_r31->unk_14.z = 0.5f * (lbl_1_data_F0[var_r30].z + lbl_1_data_438[var_r30].z);
    }
    for (var_r30 = 0, var_r31 = arg0; var_r30 < lbl_1_bss_B4; var_r30++, var_r31++) {
        if (var_r30 < lbl_1_bss_B4 - 1) {
            var_r28 = &arg0[var_r30 + 1];
            VECSubtract(&var_r28->unk_14, &var_r31->unk_14, &var_r31->unk_08);
            var_r31->unk_00 = VECMag(&var_r31->unk_08);
            VECNormalize(&var_r31->unk_08, &var_r31->unk_08);
        }
        else {
            var_r31->unk_00 = 100000.0f;
            var_r31->unk_08.x = 0.0f;
            var_r31->unk_08.y = 0.0f;
            var_r31->unk_08.z = -1.0f;
        }
        var_r31->unk_04 = var_f31;
        var_f31 += var_r31->unk_00;
    }
}

s32 fn_1_66F4(float arg8, float *arg0)
{
    UnkM406Struct2 *var_r31;
    s32 var_r30;

    for (var_r30 = 0, var_r31 = lbl_1_bss_B8; var_r30 < lbl_1_bss_B4; var_r30++, var_r31++) {
        if (arg8 < (var_r31->unk_04 + var_r31->unk_00)) {
            *arg0 = (arg8 - var_r31->unk_04) / var_r31->unk_00;
            if (*arg0 < 0.0f) {
                *arg0 = 0.0f;
            }
            break;
        }
    }
    if (var_r30 >= lbl_1_bss_B4) {
        if (arg0) {
            *arg0 = 0.0f;
        }
        return -1;
    }
    return var_r30;
}

void fn_1_67CC(ModelData *arg0)
{
    UnkM406Struct4 *var_r31;
    s32 var_r30;
    UnkM406Unk120Struct *var_r29;

    var_r29 = arg0->unk_120;
    var_r31 = var_r29->unk_30;
    for (var_r30 = 0; var_r30 < 12; var_r30++, var_r31++) {
        if (var_r31->unk_04 != 3 || var_r31->unk_0C > 0) {
            Hu3DModelAttrSet(var_r31->unk_00, HU3D_ATTR_DISPOFF);
            var_r31->unk_0C--;
        }
        else {
            var_r31->unk_20 = var_r31->unk_20 - var_r31->unk_2C;
            var_r31->unk_3C.x += var_r31->unk_30.x;
            var_r31->unk_3C.y += var_r31->unk_30.y;
            var_r31->unk_3C.z += var_r31->unk_30.z;
            var_r31->unk_30.y -= 0.49f;
            Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_3C.x, var_r31->unk_3C.y, var_r31->unk_3C.z);
            Hu3DModelRotSet(var_r31->unk_00, var_r31->unk_20, var_r31->unk_24, 0.0f);
            Hu3DModelAttrReset(var_r31->unk_00, HU3D_ATTR_DISPOFF);
            if (++var_r31->unk_08 >= 600.0f) {
                Hu3DModelAttrSet(var_r31->unk_00, HU3D_ATTR_DISPOFF);
                var_r31->unk_04 = 0;
                var_r31->unk_08 = 0;
            }
        }
    }
}

void fn_1_696C(float arg8)
{
    UnkM406Unk120Struct *var_r31;
    ModelData *var_r30;

    if (lbl_1_data_7A4 >= 0) {
        var_r30 = &Hu3DData[lbl_1_data_7A4];
        var_r31 = var_r30->unk_120;
        var_r31->unk_10 = arg8;
    }
}

void fn_1_69C0(Vec *arg0)
{
    UnkM406Unk120Struct *var_r31;
    ModelData *var_r30;

    arg0->x = arg0->y = arg0->z = 0.0f;
    if (lbl_1_data_7A4 >= 0) {
        var_r30 = &Hu3DData[lbl_1_data_7A4];
        var_r31 = var_r30->unk_120;
        *arg0 = var_r31->unk_94[17].unk_10;
    }
}

s32 fn_1_6A44(Vec arg0)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;

    UnkM406Unk120Struct *var_r31;
    ModelData *var_r29;

    if (lbl_1_data_7A4 < 0) {
        return 0;
    }
    var_r29 = &Hu3DData[lbl_1_data_7A4];
    var_r31 = var_r29->unk_120;
    VECAdd(&var_r31->unk_34, &var_r31->unk_40, &sp8);
    VECScale(&sp8, &sp8, 0.5f);
    VECSubtract(&var_r31->unk_34, &sp8, &sp20);
    VECSubtract(&var_r31->unk_40, &sp8, &sp14);
    var_f31 = fn_1_D5CC(&sp20, &sp14, arg0.x - sp8.x, arg0.z - sp8.z);
    if (var_f31 <= 0.0f) {
        return 0;
    }
    return 1;
}

void fn_1_6B5C(void)
{
    UnkM406Unk120Struct *var_r31;
    ModelData *var_r30;

    if (lbl_1_data_7A4 >= 0) {
        var_r30 = &Hu3DData[lbl_1_data_7A4];
        var_r31 = var_r30->unk_120;
        var_r31->unk_28 = 1;
    }
}

void fn_1_6BB4(Vec *arg0)
{
    Vec sp30;
    Vec sp24;

    float var_f31;

    s32 var_r30;
    s32 var_r29;

    for (var_r30 = 0; var_r30 < 32; var_r30++) {
        sp30.x = arg0->x + (100.0f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
        sp30.y = arg0->y;
        sp30.z = arg0->z - 100.0f;
        sp24.x = 2.0f * (0.5f - (0.007874016f * (frand() & 0x7F)));
        sp24.z = -2.0f * (1.0f + (1.2f * (0.007874016f * (frand() & 0x7F))));
        sp24.y = 7.5000005f * (1.0f + (0.7f * (0.007874016f * (frand() & 0x7F))));
        var_f31 = 5.5f + (5.5f * (0.007874016f * (frand() & 0x7F)));

        var_r29 = fn_1_8104(sp30, sp24, var_f31, lbl_1_data_897);
        fn_1_8244(var_r29, (s32)(60.0f * (0.007874016f * (frand() & 0x7F))) + 60, 0.32666668f, 0.99f);
    }
}

void fn_1_6F24(void)
{
    s32 sp8;

    UnkM406Struct10 *var_r31;
    UnkM406Unk120Struct2 *var_r30;
    ModelData *var_r29;
    AnimData *var_r28;

    var_r31 = lbl_1_bss_B0 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM406Struct10), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(UnkM406Struct10));
    var_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M406, 63), MEMORY_DEFAULT_NUM));
    var_r31->unk_08 = var_r28;
    var_r31->unk_00 = sp8 = fn_1_B474(var_r28, 0x800);
    Hu3DModelLayerSet(var_r31->unk_00, 2);
    var_r31->unk_04 = 0;
    var_r29 = &Hu3DData[var_r31->unk_00];
    var_r30 = var_r29->unk_120;
    var_r30->unk_20 = 0;
}

void fn_1_6FFC(void)
{
    UnkM406Struct5 *var_r31;
    UnkM406Struct10 *var_r30;
    UnkM406Unk120Struct2 *var_r29;
    s32 var_r28;
    ModelData *var_r27;

    var_r30 = lbl_1_bss_B0;
    if (var_r30->unk_04 <= 0) {
        Hu3DModelAttrSet(var_r30->unk_00, HU3D_ATTR_DISPOFF);
        return;
    }
    Hu3DModelAttrReset(var_r30->unk_00, HU3D_ATTR_DISPOFF);
    var_r27 = &Hu3DData[var_r30->unk_00];
    var_r29 = var_r27->unk_120;
    var_r31 = var_r29->unk_3C;
    for (var_r28 = 0; var_r28 < var_r29->unk_26; var_r28++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {
            continue;
        }
        var_r31->unk_30.x += var_r31->unk_04.x;
        var_r31->unk_30.y += var_r31->unk_04.y;
        var_r31->unk_30.z += var_r31->unk_04.z;
        var_r31->unk_2C += var_r31->unk_18;
        if (var_r31->unk_2C >= 360.0f) {
            var_r31->unk_2C -= 360.0f;
        }
        var_r31->unk_40 = var_r31->unk_00 >> 1;
        var_r31->unk_00++;
        if (var_r31->unk_40 >= 16) {
            var_r31->unk_40 = 0;
            var_r31->unk_00 = 0;
            var_r31->unk_28 = 0.0f;
            var_r30->unk_04--;
        }
    }
}

void fn_1_717C(void)
{
    UnkM406Struct10 *var_r31;

    var_r31 = lbl_1_bss_B0;
    Hu3DModelAttrSet(var_r31->unk_00, HU3D_ATTR_DISPOFF);
    HuSprAnimKill(var_r31->unk_08);
}

s32 fn_1_71C4(Vec arg0, Vec arg1, float arg8, float arg9, GXColor arg2)
{
    UnkM406Struct5 *var_r31;
    UnkM406Unk120Struct2 *var_r30;
    s32 var_r29;
    UnkM406Struct10 *var_r28;
    ModelData *var_r27;

    var_r28 = lbl_1_bss_B0;
    var_r27 = &Hu3DData[var_r28->unk_00];
    var_r30 = var_r27->unk_120;
    var_r31 = var_r30->unk_3C;
    for (var_r29 = 0; var_r29 < var_r30->unk_26; var_r29++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {
            break;
        }
    }
    if (var_r29 >= var_r30->unk_26) {
        return -1;
    }
    var_r31->unk_00 = var_r31->unk_02 = 0;

    var_r31->unk_30.x = arg0.x;
    var_r31->unk_30.y = arg0.y;
    var_r31->unk_30.z = arg0.z;

    var_r31->unk_04.x = arg1.x;
    var_r31->unk_04.y = arg1.y;
    var_r31->unk_04.z = arg1.z;

    var_r31->unk_18 = arg9;
    var_r31->unk_28 = arg8;

    var_r31->unk_3C.r = arg2.r;
    var_r31->unk_3C.g = arg2.g;
    var_r31->unk_3C.b = arg2.b;
    var_r31->unk_3C.a = arg2.a;

    var_r31->unk_2C = 0.0f;
    var_r31->unk_40 = 0;
    var_r31->unk_00 = 0;
    var_r28->unk_04++;

    return var_r29;
}

// TODO maybe pass struct by value
s32 fn_1_72F8(Vec *arg0, Vec *arg1, GXColor *arg2, float arg8, float arg9, float argA)
{
    Vec sp54;
    Vec sp48;
    s32 sp14;
    s32 sp10;

    float var_f31;

    sp48.x = arg1->z;
    sp48.z = arg1->x;
    sp48.y = 0.0f;

    var_f31 = 0.5f * argA;

    sp54.x = arg0->x + (sp48.x * var_f31);
    sp54.y = arg0->y + (sp48.y * var_f31);
    sp54.z = arg0->z + (sp48.z * var_f31);
    sp14 = fn_1_71C4(sp54, *arg1, arg8, arg9, *arg2);

    sp54.x = arg0->x - (sp48.x * var_f31);
    sp54.y = arg0->y - (sp48.y * var_f31);
    sp54.z = arg0->z - (sp48.z * var_f31);

    sp10 = fn_1_71C4(sp54, *arg1, arg8, -arg9, *arg2);
    return (sp14 << 16) | sp10;
}

UnkM406Struct5 *fn_1_76A8(s32 arg0)
{
    UnkM406Unk120Struct2 *var_r31;
    UnkM406Struct10 *var_r30;
    ModelData *var_r29;

    var_r30 = lbl_1_bss_B0;
    var_r29 = &Hu3DData[var_r30->unk_00];
    var_r31 = var_r29->unk_120;
    if (arg0 < 0 || arg0 >= var_r31->unk_26) {
        return 0;
    }
    return &var_r31->unk_3C[arg0];
}

void fn_1_7718(void)
{
    s32 sp8;

    UnkM406Struct10 *var_r31;
    UnkM406Unk120Struct2 *var_r30;
    ModelData *var_r29;
    AnimData *var_r28;

    var_r31 = lbl_1_bss_AC = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM406Struct10), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(UnkM406Struct10));
    var_r28 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M406, 63), MEMORY_DEFAULT_NUM));
    var_r31->unk_08 = var_r28;
    var_r31->unk_00 = sp8 = fn_1_B474(var_r28, 105);
    Hu3DModelLayerSet(var_r31->unk_00, 2);
    var_r31->unk_04 = 0;
    var_r29 = &Hu3DData[var_r31->unk_00];
    var_r30 = var_r29->unk_120;
    var_r30->unk_20 = 0;
}

void fn_1_77F0(void)
{
    UnkM406Struct5 *var_r31;
    UnkM406Struct10 *var_r30;
    UnkM406Unk120Struct2 *var_r29;
    s32 var_r28;
    ModelData *var_r27;

    var_r30 = lbl_1_bss_AC;
    if (var_r30->unk_04 <= 0) {
        Hu3DModelAttrSet(var_r30->unk_00, HU3D_ATTR_DISPOFF);
        return;
    }
    Hu3DModelAttrReset(var_r30->unk_00, HU3D_ATTR_DISPOFF);
    var_r27 = &Hu3DData[var_r30->unk_00];
    var_r29 = var_r27->unk_120;
    var_r31 = var_r29->unk_3C;
    if (fn_1_122C() < 3) {
        var_r29->unk_22 |= 1;
    }
    else {
        var_r29->unk_22 &= 0xFFFFFFFE;
    }
    for (var_r28 = 0; var_r28 < var_r29->unk_26; var_r28++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {
            continue;
        }
        var_r31->unk_30.x += var_r31->unk_04.x;
        var_r31->unk_30.y += var_r31->unk_04.y;
        var_r31->unk_30.z += var_r31->unk_04.z;
        var_r31->unk_2C += var_r31->unk_18;
        if (var_r31->unk_2C >= 360.0f) {
            var_r31->unk_2C = var_r31->unk_2C - 360.0f;
        }
        var_r31->unk_40 = var_r31->unk_00 / 2;
        var_r31->unk_00++;
        if (var_r31->unk_40 >= 0x10) {
            var_r31->unk_40 = 0;
            var_r31->unk_00 = 0;
            var_r31->unk_02 = 0;
            var_r31->unk_28 = 0.0f;
            var_r30->unk_04--;
        }
    }
}

void fn_1_79B0(void)
{
    UnkM406Struct10 *var_r31;

    var_r31 = lbl_1_bss_AC;
    Hu3DModelAttrSet(var_r31->unk_00, HU3D_ATTR_DISPOFF);
    HuSprAnimKill(var_r31->unk_08);
}

s32 fn_1_79F8(Vec arg0, Vec arg1, float arg8, float arg9, GXColor arg2)
{
    UnkM406Struct5 *var_r31;
    UnkM406Unk120Struct2 *var_r30;
    s32 var_r29;
    UnkM406Struct10 *var_r28;
    ModelData *var_r27;

    var_r28 = lbl_1_bss_AC;
    var_r27 = &Hu3DData[var_r28->unk_00];
    var_r30 = var_r27->unk_120;
    var_r31 = var_r30->unk_3C;
    for (var_r29 = 0; var_r29 < var_r30->unk_26; var_r29++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {
            break;
        }
    }
    if (var_r29 >= var_r30->unk_26) {
        return -1;
    }
    var_r31->unk_00 = var_r31->unk_02 = 0;

    var_r31->unk_30.x = arg0.x;
    var_r31->unk_30.y = arg0.y;
    var_r31->unk_30.z = arg0.z;

    var_r31->unk_04.x = arg1.x;
    var_r31->unk_04.y = arg1.y;
    var_r31->unk_04.z = arg1.z;

    var_r31->unk_18 = arg9;
    var_r31->unk_28 = arg8;

    var_r31->unk_3C.r = arg2.r;
    var_r31->unk_3C.g = arg2.g;
    var_r31->unk_3C.b = arg2.b;
    var_r31->unk_3C.a = arg2.a;

    var_r31->unk_2C = 0.0f;
    var_r31->unk_40 = 0;
    var_r31->unk_00 = 0;
    var_r28->unk_04++;

    return var_r29;
}

UnkM406Struct5 *fn_1_7B2C(s32 arg0)
{
    UnkM406Unk120Struct2 *var_r31;
    UnkM406Struct10 *var_r30;
    ModelData *var_r29;

    var_r30 = lbl_1_bss_AC;
    var_r29 = &Hu3DData[var_r30->unk_00];
    var_r31 = var_r29->unk_120;
    if (arg0 < 0 || arg0 >= var_r31->unk_26) {
        return NULL;
    }
    return &var_r31->unk_3C[arg0];
}

void fn_1_7B9C(void)
{
    s32 sp8;

    UnkM406Struct6 *var_r31;
    UnkM406Unk120Struct2 *var_r30;
    ModelData *var_r29;

    var_r31 = lbl_1_bss_A8 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM406Struct6), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(UnkM406Struct6));
    var_r31->unk_00 = sp8 = fn_1_C4F4(512);
    Hu3DModelLayerSet(var_r31->unk_00, 3);
    var_r31->unk_04 = 0;
    var_r29 = &Hu3DData[var_r31->unk_00];
    var_r30 = var_r29->unk_120;
    var_r30->unk_20 = 0;
}

void fn_1_7C4C(void)
{
    UnkM406Struct5 *var_r31;
    UnkM406Struct6 *var_r30;
    UnkM406Unk120Struct2 *var_r29;
    s32 var_r28;
    ModelData *var_r27;

    var_r30 = lbl_1_bss_A8;
    if (var_r30->unk_04 <= 0) {
        Hu3DModelAttrSet(var_r30->unk_00, HU3D_ATTR_DISPOFF);
        return;
    }
    Hu3DModelAttrReset(var_r30->unk_00, HU3D_ATTR_DISPOFF);
    var_r27 = &Hu3DData[var_r30->unk_00];
    var_r29 = var_r27->unk_120;
    var_r31 = var_r29->unk_3C;
    for (var_r28 = 0; var_r28 < var_r29->unk_26; var_r28++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {
            continue;
        }
        var_r31->unk_30.x += var_r31->unk_04.x;
        var_r31->unk_30.y += var_r31->unk_04.y;
        var_r31->unk_30.z += var_r31->unk_04.z;
        var_r31->unk_04.y -= 0.32666668f;
        if (++var_r31->unk_00 > 60 || var_r31->unk_30.y < var_r31->unk_14 - 200.0f) {
            var_r31->unk_00 = 0;
            var_r31->unk_28 = 0.0f;
            var_r30->unk_04--;
        }
    }
}

void fn_1_7DAC(void) { }

s32 fn_1_7DB0(Vec arg0, Vec arg1, float arg8, GXColor arg2)
{
    UnkM406Struct5 *var_r31;
    UnkM406Unk120Struct2 *var_r30;
    s32 var_r29;
    UnkM406Struct6 *var_r28;
    ModelData *var_r27;

    var_r28 = lbl_1_bss_A8;
    var_r27 = &Hu3DData[var_r28->unk_00];
    var_r30 = var_r27->unk_120;
    var_r31 = var_r30->unk_3C;
    for (var_r29 = 0; var_r29 < var_r30->unk_26; var_r29++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {
            break;
        }
    }
    if (var_r29 >= var_r30->unk_26) {
        return -1;
    }
    var_r31->unk_00 = var_r31->unk_02 = 0;

    var_r31->unk_30.x = arg0.x;
    var_r31->unk_30.y = arg0.y;
    var_r31->unk_30.z = arg0.z;

    var_r31->unk_04.x = arg1.x;
    var_r31->unk_04.y = arg1.y;
    var_r31->unk_04.z = arg1.z;

    var_r31->unk_14 = arg0.y;
    var_r31->unk_28 = arg8;
    var_r31->unk_3C = arg2;
    var_r31->unk_00 = 0;
    var_r28->unk_04++;

    return var_r29;
}

void fn_1_7ED0(void)
{
    s32 sp8;

    UnkM406Struct6 *var_r31;
    UnkM406Unk120Struct2 *var_r30;
    ModelData *var_r29;

    var_r31 = lbl_1_bss_A4 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM406Struct6), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(UnkM406Struct6));
    var_r31->unk_00 = sp8 = fn_1_C4F4(512);
    Hu3DModelLayerSet(var_r31->unk_00, 3);
    var_r31->unk_04 = 0;
    var_r29 = &Hu3DData[var_r31->unk_00];
    var_r30 = var_r29->unk_120;
    var_r30->unk_20 = 0;
}

void fn_1_7F80(void)
{
    UnkM406Struct5 *var_r31;
    UnkM406Struct6 *var_r30;
    UnkM406Unk120Struct2 *var_r29;
    s32 var_r28;
    ModelData *var_r27;

    var_r30 = lbl_1_bss_A4;
    if (var_r30->unk_04 <= 0) {
        Hu3DModelAttrSet(var_r30->unk_00, HU3D_ATTR_DISPOFF);
        return;
    }
    Hu3DModelAttrReset(var_r30->unk_00, HU3D_ATTR_DISPOFF);
    var_r27 = &Hu3DData[var_r30->unk_00];
    var_r29 = var_r27->unk_120;
    var_r31 = var_r29->unk_3C;
    for (var_r28 = 0; var_r28 < var_r29->unk_26; var_r28++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {
            continue;
        }
        var_r31->unk_30.x += var_r31->unk_04.x;
        var_r31->unk_30.y += var_r31->unk_04.y;
        var_r31->unk_30.z += var_r31->unk_04.z;
        var_r31->unk_04.y -= var_r31->unk_14;
        if (var_r31->unk_10 != 0.0f) {
            var_r31->unk_28 *= var_r31->unk_10;
        }
        if (++var_r31->unk_00 > var_r31->unk_02 || var_r31->unk_04.y <= 0.0f) {
            var_r31->unk_00 = 0;
            var_r31->unk_28 = 0.0f;
            var_r30->unk_04 = var_r30->unk_04 - 1;
        }
    }
}

void fn_1_8100(void) { }

s32 fn_1_8104(Vec arg0, Vec arg1, float arg8, GXColor arg2)
{
    UnkM406Struct5 *var_r31;
    UnkM406Unk120Struct2 *var_r30;
    UnkM406Struct6 *var_r28;
    s32 var_r29;

    ModelData *var_r27;

    var_r28 = lbl_1_bss_A4;

    var_r27 = &Hu3DData[var_r28->unk_00];
    var_r30 = var_r27->unk_120;
    var_r31 = var_r30->unk_3C;
    for (var_r29 = 0; var_r29 < var_r30->unk_26; var_r29++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {

            break;
        }
    }

    if (var_r29 >= var_r30->unk_26) {
        return -1;
    }
    var_r31->unk_00 = var_r31->unk_02 = 0;

    var_r31->unk_30.x = arg0.x;
    var_r31->unk_30.y = arg0.y;
    var_r31->unk_30.z = arg0.z;

    var_r31->unk_04.x = arg1.x;
    var_r31->unk_04.y = arg1.y;
    var_r31->unk_04.z = arg1.z;

    var_r31->unk_14 = 0.49f;
    var_r31->unk_10 = 0.0f;
    var_r31->unk_02 = 30;

    var_r31->unk_28 = arg8;

    var_r31->unk_3C.r = arg2.r;
    var_r31->unk_3C.g = arg2.g;
    var_r31->unk_3C.b = arg2.b;
    var_r31->unk_3C.a = arg2.a;

    var_r31->unk_00 = 0;
    var_r28->unk_04++;
    return var_r29;
}

void fn_1_8244(s32 arg0, s32 arg1, float arg8, float arg9)
{
    UnkM406Struct5 *var_r31;
    UnkM406Unk120Struct2 *var_r30;
    UnkM406Struct6 *var_r29;
    ModelData *var_r28;

    var_r29 = lbl_1_bss_A4;
    var_r28 = &Hu3DData[var_r29->unk_00];
    var_r30 = var_r28->unk_120;
    if (arg0 < 0 || arg0 >= var_r30->unk_26) {
        return;
    }
    var_r31 = &var_r30->unk_3C[arg0];
    var_r31->unk_10 = arg9;
    var_r31->unk_14 = arg8;
    var_r31->unk_02 = arg1;
}

void fn_1_82C8(Mtx arg0, s32 arg1, float arg8)
{
    Mtx sp8C;
    Vec sp80;
    Vec sp74;
    Vec sp68;
    Vec sp5C;
    Vec sp50;
    Vec sp44;

    float var_f31;
    float var_f30;
    float var_f29;

    s32 var_r28;

    sp80.x = arg0[0][3];
    sp80.y = arg0[1][3];
    sp80.z = arg0[2][3];
    sp74.x = sp74.z = 0.0f;
    sp74.y = atan2d(arg0[0][0], arg0[2][0]);
    MTXCopy(arg0, sp8C);
    sp8C[0][3] = sp8C[1][3] = sp8C[2][3] = sp8C[3][3] = 0.0f;
    sp68.x = -25.0f;
    sp68.z = -50.0f;
    sp68.y = 0.0f;
    fn_1_D518(sp8C, &sp68);
    sp68.x += sp80.x;
    sp68.y += sp80.y;
    sp68.z += sp80.z;

    sp5C.x = -25.0f;
    sp5C.z = 50.0f;
    sp5C.y = 0.0f;
    fn_1_D518(sp8C, &sp5C);
    sp5C.x += sp80.x;
    sp5C.y += sp80.y;
    sp5C.z += sp80.z;
    mtxRotCat(sp8C, 0.0f, 180.0f + (90.0f - (45.0f * (0.007874016f * (frand() & 0x7F)))), 0.0f);
    lbl_1_data_89B.a = arg8;
    var_f30 = sp8C[0][2];
    var_f29 = sp8C[2][2];
    for (var_r28 = 0; var_r28 < (arg1 >> 1); var_r28++) {
        fn_1_D488(0.007874016f * (frand() & 0x7F), &sp68, &sp5C, &sp50);
        sp50.x += 100.0f * (0.1f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
        sp50.y += 100.0f * (0.1f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
        sp50.z += 100.0f * (0.1f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));

        sp44.x = 2.0f * var_f30 * (1.0f + (0.007874016f * (frand() & 0x7F)));
        sp44.z = 2.0f * var_f29 * (1.0f + (0.007874016f * (frand() & 0x7F)));
        sp44.y = 5.0f * (1.0f + (0.7f * (0.007874016f * (frand() & 0x7F))));
        var_f31 = 5.0f + (15.0f * (0.007874016f * (frand() & 0x7F)));

        fn_1_8104(sp50, sp44, var_f31, lbl_1_data_89B);
    }
    sp68.x = -25.0f;
    sp68.z = -50.0f;
    sp68.y = 0.0f;
    fn_1_D518(sp8C, &sp68);
    sp68.x += sp80.x;
    sp68.y += sp80.y;
    sp68.z = sp68.z + sp80.z;
    sp5C.x = -25.0f;
    sp5C.z = 50.0f;
    sp5C.y = 0.0f;
    fn_1_D518(sp8C, &sp5C);
    sp5C.x += sp80.x;
    sp5C.y += sp80.y;
    sp5C.z += sp80.z;
    for (var_r28 = 0; var_r28 < (arg1 >> 1); var_r28++) {
        fn_1_D488(0.007874016f * (frand() & 0x7F), &sp68, &sp5C, &sp50);
        sp50.x += 100.0f * (0.1f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
        sp50.y += 100.0f * (0.1f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
        sp50.z += 100.0f * (0.1f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));

        sp44.x = 2.0f * var_f30 * (1.0f + (0.007874016f * (frand() & 0x7F)));
        sp44.z = 2.0f * var_f29 * (1.0f + (0.007874016f * (frand() & 0x7F)));
        sp44.y = 5.0f * (1.0f + (0.7f * (0.007874016f * (frand() & 0x7F))));
        var_f31 = 5.0f + (15.0f * (0.007874016f * (frand() & 0x7F)));

        fn_1_8104(sp50, sp44, var_f31, lbl_1_data_89B);
    }
}

void fn_1_8F98(void)
{
    UnkM406Struct7 *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_A0 = HuMemDirectMallocNum(HEAP_SYSTEM, 128 * sizeof(UnkM406Struct7), MEMORY_DEFAULT_NUM);
    memset(lbl_1_bss_A0, 0, 128 * sizeof(UnkM406Struct7));
    for (var_r30 = 0, var_r31 = lbl_1_bss_A0; var_r30 < 64; var_r30++, var_r31++) {
        var_r31->unk_00 = 0;
        var_r31->unk_01 = 0;
        var_r31->unk_08 = 0;
        var_r31->unk_0C = 0.0f;
        var_r31->unk_10 = 0.0f;
        var_r31->unk_14 = 6.0f;
        var_r31->unk_18 = 1.0f;
        MTXIdentity(var_r31->unk_1C);
        if (var_r30 == 0) {
            var_r31->unk_04 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 59));
        }
        else {
            var_r31->unk_04 = Hu3DModelLink(lbl_1_bss_A0->unk_04);
        }
        Hu3DModelLayerSet(var_r31->unk_04, 3);
        Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
    }

    for (var_r30 = 0, var_r31 = &lbl_1_bss_A0[64]; var_r30 < 64; var_r30++, var_r31++) {
        var_r31->unk_00 = 0;
        var_r31->unk_01 = 0;
        var_r31->unk_08 = 0;
        var_r31->unk_0C = 0.0f;
        var_r31->unk_10 = 0.0f;
        var_r31->unk_14 = 6.0f;
        var_r31->unk_18 = 1.0f;
        MTXIdentity(var_r31->unk_1C);
        if (var_r30 == 0) {
            var_r31->unk_04 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 60));
        }
        else {
            var_r31->unk_04 = Hu3DModelLink(lbl_1_bss_A0[64].unk_04);
        }
        Hu3DModelLayerSet(var_r31->unk_04, 3);
        Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
    }
}

void fn_1_91E0(void)
{
    Mtx sp8;

    float var_f31;
    float var_f30;

    UnkM406Struct7 *var_r31;
    ModelData *var_r30;
    s32 var_r29;

    var_r31 = lbl_1_bss_A0;
    for (var_r29 = 0, var_r31 = lbl_1_bss_A0; var_r29 < 64; var_r29++, var_r31++) {
        if (!var_r31->unk_00) {
            continue;
        }
        var_f30 = var_r31->unk_0C / var_r31->unk_14;
        var_f31 = var_r31->unk_18 * cosd((90.0f * var_f30));
        var_f31 = var_f31;
        var_r30 = &Hu3DData[var_r31->unk_04];
        MTXScale(sp8, var_f31, var_f31, var_f31);
        MTXConcat(var_r31->unk_1C, sp8, var_r30->unk_F0);
        var_r30->unk_F0[0][3] = var_r31->unk_1C[0][3];
        var_r30->unk_F0[1][3] = var_r31->unk_1C[1][3];
        var_r30->unk_F0[2][3] = var_r31->unk_1C[2][3];
        Hu3DModelTPLvlSet(var_r31->unk_04, 1.0f - var_f30);
        if ((var_r31->unk_0C += var_r31->unk_10) >= var_r31->unk_14) {
            Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
            var_r31->unk_00 = 0;
            var_r31->unk_0C = 0.0f;
        }
        var_r31->unk_08++;
    }
    for (var_r29 = 0, var_r31 = &lbl_1_bss_A0[64]; var_r29 < 64; var_r29++, var_r31++) {
        if (!var_r31->unk_00) {
            continue;
        }
        var_f30 = var_r31->unk_0C / var_r31->unk_14;
        var_f31 = var_r31->unk_18 * cosd((90.0f * var_f30));
        var_f31 = var_f31;
        var_r30 = &Hu3DData[var_r31->unk_04];
        MTXScale(sp8, var_f31, var_f31, var_f31);
        MTXConcat(var_r31->unk_1C, sp8, var_r30->unk_F0);
        var_r30->unk_F0[0][3] = var_r31->unk_1C[0][3];
        var_r30->unk_F0[1][3] = var_r31->unk_1C[1][3];
        var_r30->unk_F0[2][3] = var_r31->unk_1C[2][3];
        Hu3DModelTPLvlSet(var_r31->unk_04, 1.0f - var_f30);
        if ((var_r31->unk_0C += var_r31->unk_10) >= var_r31->unk_14) {
            Hu3DModelAttrSet(var_r31->unk_04, HU3D_ATTR_DISPOFF);
            var_r31->unk_00 = 0;
            var_r31->unk_0C = 0.0f;
        }
        var_r31->unk_08++;
    }
}

void fn_1_94BC(void) { }

s32 fn_1_94C0(Mtx arg0, s32 arg1, s32 arg2)
{
    Mtx spA0;
    Mtx sp70;
    Vec sp64;
    Vec sp58;
    Vec sp4C;
    Vec sp40;
    Vec sp34;
    Vec sp28;

    float var_f31;
    float var_f30;
    float var_f29;

    UnkM406Struct7 *var_r31;
    s32 var_r28;
    ModelData *var_r27;

    sp64.x = arg0[0][3];
    sp64.y = arg0[1][3];
    sp64.z = arg0[2][3];
    sp58.x = sp58.z = 0.0f;
    sp58.y = atan2d(arg0[0][0], arg0[2][0]);
    MTXCopy(arg0, spA0);
    spA0[0][3] = spA0[1][3] = spA0[2][3] = spA0[3][3] = 0.0f;
    if (!arg2) {
        sp4C.x = 25.0f;
        sp4C.z = -50.0f;
        sp4C.y = 0.0f;
        fn_1_D518(spA0, &sp4C);
        sp4C.x += sp64.x;
        sp4C.y += sp64.y;
        sp4C.z += sp64.z;
        sp40.x = 25.0f;
        sp40.z = 50.0f;
        sp40.y = 0.0f;
        fn_1_D518(spA0, &sp40);
        sp40.x += sp64.x;
        sp40.y += sp64.y;
        sp40.z += sp64.z;
        mtxRotCat(spA0, 0.0f, 180.0f + (45.0f * (0.007874016f * (frand() & 0x7F))), 0.0f);
    }
    else {
        sp4C = sp64;
        sp4C.x = -25.0f;
        sp4C.z = -50.0f;
        sp4C.y = 0.0f;
        fn_1_D518(spA0, &sp4C);
        sp4C.x += sp64.x;
        sp4C.y += sp64.y;
        sp4C.z += sp64.z;
        sp40 = sp64;
        sp40.x = -25.0f;
        sp40.z = 50.0f;
        sp40.y = 0.0f;
        fn_1_D518(spA0, &sp40);
        sp40.x += sp64.x;
        sp40.y += sp64.y;
        sp40.z += sp64.z;
        mtxRotCat(spA0, 0.0f, 180.0f - (45.0f * (0.007874016f * (frand() & 0x7F))), 0.0f);
    }
    var_f30 = spA0[0][2];
    var_f29 = spA0[2][2];
    for (var_r28 = 0; var_r28 < arg1; var_r28++) {
        fn_1_D488(0.007874016f * (frand() & 0x7F), &sp4C, &sp40, &sp34);
        sp34.x += 100.0f * (0.1f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
        sp34.y += 100.0f * (0.1f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
        sp34.z += 100.0f * (0.1f * ((0.007874016f * (frand() & 0x7F)) - 0.5f));
        sp28.x = 2.0f * var_f30 * (1.0f + (0.007874016f * (frand() & 0x7F)));
        sp28.z = 2.0f * var_f29 * (1.0f + (0.007874016f * (frand() & 0x7F)));
        sp28.y = 5.0f * (1.0f + (0.7f * (0.007874016f * (frand() & 0x7F))));

        fn_1_8104(sp34, sp28, 7.5f, lbl_1_data_89F);
    }
    var_r31 = lbl_1_bss_A0;
    if (!arg2) {
        for (var_r28 = 0, var_r31 = lbl_1_bss_A0; var_r28 < 64; var_r28++, var_r31++) {
            if (!var_r31->unk_00) {
                break;
            }
        }
        if (var_r28 >= 64) {
            return -1;
        }
    }
    else {
        for (var_r28 = 0, var_r31 = &lbl_1_bss_A0[64]; var_r28 < 64; var_r28++, var_r31++) {
            if (!var_r31->unk_00) {
                break;
            }
        }
        if (var_r28 >= 64) {
            return -1;
        }
    }
    var_f31 = 1.2f * (2.0f + (0.007874016f * (frand() & 0x7F)));
    var_r31->unk_00 = 1;
    var_r31->unk_08 = 0;
    var_r31->unk_0C = 0.0f;
    var_r31->unk_10 = 1.0f;
    var_r31->unk_14 = 6.0f;
    var_r31->unk_18 = var_f31;
    MTXCopy(arg0, var_r31->unk_1C);
    Hu3DMotionTimeSet(var_r31->unk_04, 0.0f);
    Hu3DMotionSpeedSet(var_r31->unk_04, 0.0f);
    var_r27 = &Hu3DData[var_r31->unk_04];
    MTXScale(sp70, var_f31, var_f31, var_f31);
    MTXConcat(arg0, sp70, var_r27->unk_F0);
    var_r27->unk_F0[0][3] = arg0[0][3];
    var_r27->unk_F0[1][3] = arg0[1][3];
    var_r27->unk_F0[2][3] = arg0[2][3];
    Hu3DModelPosSet(var_r31->unk_04, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31->unk_04, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(var_r31->unk_04, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(var_r31->unk_04, HU3D_ATTR_DISPOFF);
    (void)var_r31;
    return var_r28;
}

void fn_1_9F78(void)
{
    UnkM406Unk120Struct2 *var_r31;
    UnkM406Struct8 *var_r30;
    ModelData *var_r29;
    UnkM406Struct9 *var_r28;
    s32 var_r27;

    var_r30 = lbl_1_bss_9C = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM406Struct8), MEMORY_DEFAULT_NUM);
    memset(var_r30, 0, sizeof(UnkM406Struct8));
    var_r30->unk_00 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M406, 0x40), MEMORY_DEFAULT_NUM));
    var_r30->unk_04 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M406, 0x41), MEMORY_DEFAULT_NUM));
    var_r30->unk_08 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M406, 0x42), MEMORY_DEFAULT_NUM));
    var_r30->unk_0C = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M406, 0x43), MEMORY_DEFAULT_NUM));
    var_r30->unk_24 = 0.0f;
    var_r30->unk_28 = 0.0f;
    var_r27 = fn_1_B474(var_r30->unk_00, 1);
    var_r30->unk_10 = var_r27;
    Hu3DModelLayerSet(var_r27, 6);
    var_r29 = &Hu3DData[var_r27];
    var_r31 = var_r29->unk_120;
    var_r31->unk_20 = 1;
    var_r31->unk_22 = 2;
    var_r31->unk_4C = fn_1_A2C8;
    var_r28 = var_r31->unk_1C = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkM406Struct9), var_r29->unk_48);
    memset(var_r28, 0, 8);
    var_r28->unk_02 = 0;
    var_r27 = fn_1_B474(var_r30->unk_0C, 0xA);
    var_r30->unk_14 = var_r27;
    Hu3DModelLayerSet(var_r27, 6);
    var_r29 = &Hu3DData[var_r27];
    var_r31 = var_r29->unk_120;
    var_r31->unk_20 = 1;
    var_r31->unk_22 = 3;
    var_r31->unk_4C = fn_1_A2C8;
    var_r28 = var_r31->unk_1C = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkM406Struct9), var_r29->unk_48);
    memset(var_r28, 0, 8);
    var_r28->unk_02 = 1;
    var_r27 = fn_1_B474(var_r30->unk_08, 4);
    var_r30->unk_18 = var_r27;
    Hu3DModelLayerSet(var_r27, 6);
    var_r29 = &Hu3DData[var_r27];
    var_r31 = var_r29->unk_120;
    var_r31->unk_20 = 1;
    var_r31->unk_22 = 3;
    var_r31->unk_4C = fn_1_A2C8;
    var_r28 = var_r31->unk_1C = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkM406Struct9), var_r29->unk_48);
    memset(var_r28, 0, 8);
    var_r28->unk_02 = 2;
    var_r27 = fn_1_B474(var_r30->unk_04, 6);
    var_r30->unk_1C = var_r27;
    Hu3DModelLayerSet(var_r27, 6);
    var_r29 = &Hu3DData[var_r27];
    var_r31 = var_r29->unk_120;
    var_r31->unk_20 = 1;
    var_r31->unk_22 = 3;
    var_r31->unk_4C = fn_1_A2C8;
    var_r28 = var_r31->unk_1C = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkM406Struct9), var_r29->unk_48);
    memset(var_r28, 0, 8);
    var_r28->unk_02 = 3;
    var_r30->unk_20 = Hu3DHookFuncCreate(fn_1_ADB4);
    Hu3DModelLayerSet(var_r30->unk_20, 7);
}

void fn_1_A278(void)
{
    UnkM406Struct8 *var_r31;

    var_r31 = lbl_1_bss_9C;
    HuSprAnimKill(var_r31->unk_00);
    HuSprAnimKill(var_r31->unk_04);
    HuSprAnimKill(var_r31->unk_08);
    HuSprAnimKill(var_r31->unk_0C);
}

void fn_1_A2C8(ModelData *arg0, UnkM406Unk120Struct2 *arg1, Mtx arg2)
{
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    void *sp14;
    s16 sp8;

    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;

    UnkM406Struct5 *var_r31;
    UnkM406Struct9 *var_r29;
    s32 var_r28;

    sp8 = 0;
    sp14 = lbl_1_bss_9C;
    var_r29 = arg1->unk_1C;
    switch (var_r29->unk_04) {
        case 0:
            var_r31 = arg1->unk_3C;
            if (var_r29->unk_02) {
                sp18.x = 10000.0f;
                sp18.y = -20000.0f;
                sp18.z = -20000.0f;
                var_f28 = (sp18.z * sp18.z) + ((sp18.x * sp18.x) + (sp18.y * sp18.y));
                var_f29 = 1.0f / sqrtf(var_f28);
                sp18.x *= var_f29;
                sp18.y *= var_f29;
                sp18.z *= var_f29;
                var_f24 = 6500.0f / arg1->unk_26;
                for (var_r28 = 0; var_r28 < arg1->unk_26; var_r28++, var_r31++) {
                    var_f26 = 500.0 + ((var_f24 * var_r28) + ((0.25f * var_f24) * (1.52587890625e-05 * (float)(frand() & 0xFFFF))));
                    var_f25 = var_f26 / 6500.0f;
                    var_r31->unk_10 = var_f26;
                    var_r31->unk_30.x = var_f26 * sp18.x;
                    var_r31->unk_30.y = -27000.0f + (var_f26 * sp18.y);
                    var_r31->unk_30.z = -63000.0f + (var_f26 * sp18.z);
                    var_r31->unk_28 = (0.3f + (0.7f * (var_f25 * var_f25)))
                        * (lbl_1_data_8A4[var_r29->unk_02]
                            * (0.699999988079071 + (0.30000001192092896 * (1.52587890625e-05 * (float)(frand() & 0xFFFF)))));
                    var_r31->unk_3C.r = (s32)(160.0 * (1.52587890625e-05 * (float)(frand() & 0xFFFF))) + 0x20;
                    var_r31->unk_3C.g = (s32)(96.0 * (1.52587890625e-05 * (float)(frand() & 0xFFFF))) + 0x20;
                    var_r31->unk_3C.b = (s32)(128.0 * (1.52587890625e-05 * (float)(frand() & 0xFFFF))) + 0x20;
                    var_r31->unk_3C.a = ((1.0 - (0.4 * var_f25)) * (255.0f * lbl_1_data_8B4[var_r29->unk_02]))
                        - (int)(16.0 * (1.52587890625e-05 * (float)(frand() & 0xFFFF)));
                }
                var_r29->unk_04++;
            }
            else {
                var_r31->unk_30.x = 0.0f;
                var_r31->unk_30.y = -27000.0f;
                var_r31->unk_30.z = -63000.0f;
                var_r31->unk_28 = 1000.0f;
            }
            break;
        case 1:
            sp3C.x = sind(CRot.y) * cosd(CRot.x);
            sp3C.y = -sind(CRot.x);
            sp3C.z = cosd(CRot.y) * cosd(CRot.x);
            sp30.x = -(Center.x + (1.25f * (sp3C.x * CZoom)));
            sp30.y = -27000.0f - (Center.y + (sp3C.y * CZoom));
            sp30.z = -63000.0f - (Center.z + (1.25f * (sp3C.z * CZoom)));
            var_f27 = (sp30.z * sp30.z) + ((sp30.x * sp30.x) + (sp30.y * sp30.y));
            var_f29 = 1.0f / sqrtf(var_f27);
            sp30.x *= var_f29;
            sp30.y *= var_f29;
            sp30.z *= var_f29;
            var_f29 = -((-sp30.z * -sp3C.z) + ((-sp30.x * -sp3C.x) + (-sp30.y * -sp3C.y)));
            sp24.x = -sp3C.x + (-2.0f * sp30.x * var_f29);
            sp24.y = -sp3C.y + (-2.0f * sp30.y * var_f29);
            sp24.z = -sp3C.z + (-2.0f * sp30.z * var_f29);
            var_r31 = arg1->unk_3C;
            for (var_r28 = 0; var_r28 < arg1->unk_26; var_r28++, var_r31++) {
                var_r31->unk_30.x = sp24.x * var_r31->unk_10;
                var_r31->unk_30.y = -27000.0f + (sp24.y * var_r31->unk_10);
                var_r31->unk_30.z = -63000.0f + (sp24.z * var_r31->unk_10);
            }
            break;
        default:
            break;
    }
    DCFlushRange(arg1->unk_3C, arg1->unk_26 * sizeof(UnkM406Struct5));
    PPCSync();
}

void fn_1_ADB4(ModelData *arg0, float (*arg1)[4])
{
    Mtx sp50;
    Mtx44 sp10;

    CameraData *var_r31;
    UnkM406Struct8 *var_r30;

    GXColor spC = { 0xFF, 0xFF, 0xFF, 0xFF };
    var_r31 = &Hu3DCamera[0];
    var_r30 = lbl_1_bss_9C;
    if (var_r30->unk_28 <= 0.0f) {
        Hu3DModelAttrSet(var_r30->unk_20, HU3D_ATTR_DISPOFF);
        return;
    }
    GXSetScissor(var_r31->scissor_x, var_r31->scissor_y, var_r31->scissor_w, var_r31->scissor_h);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    C_MTXOrtho(sp10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    GXSetProjection(sp10, GX_ORTHOGRAPHIC);
    spC.a = 255.0f * var_r30->unk_28;
    GXSetTevColor(GX_TEVREG0, spC);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    MTXIdentity(sp50);
    GXLoadPosMtxImm(sp50, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_U8, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3u8(0, 0, 0);
    GXPosition3u8(1, 0, 0);
    GXPosition3u8(1, 1, 0);
    GXPosition3u8(0, 1, 0);
}

void fn_1_B104(float arg8)
{

    UnkM406Struct8 *var_r31;

    var_r31 = lbl_1_bss_9C;
    var_r31->unk_24 = arg8;
    if (var_r31->unk_24 <= 0.0f) {
        Hu3DModelAttrSet(var_r31->unk_10, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(var_r31->unk_14, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(var_r31->unk_18, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(var_r31->unk_1C, HU3D_ATTR_DISPOFF);
        return;
    }
    Hu3DModelAttrReset(var_r31->unk_10, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(var_r31->unk_14, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(var_r31->unk_18, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(var_r31->unk_1C, HU3D_ATTR_DISPOFF);
}

void fn_1_B1E0(float arg8)
{
    UnkM406Struct8 *var_r31;

    var_r31 = lbl_1_bss_9C;
    var_r31->unk_28 = arg8;
    if (var_r31->unk_28 <= 0.0f) {
        Hu3DModelAttrSet(var_r31->unk_20, HU3D_ATTR_DISPOFF);
        return;
    }
    Hu3DModelAttrReset(var_r31->unk_20, HU3D_ATTR_DISPOFF);
}

void fn_1_B25C(void)
{
    s32 var_r31;
    s32 var_r30;

    if (lbl_1_bss_98 == -1) {
        lbl_1_bss_98 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 68));
        Hu3DModelLayerSet(lbl_1_bss_98, 0);
        Hu3DModelPosSet(lbl_1_bss_98, 0.0f, -26500.0f, -63000.0f);
        Hu3DModelRotSet(lbl_1_bss_98, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(lbl_1_bss_98, 2.75f, 2.75f, 2.75f);
        var_r30 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M406, 55));
        Hu3DModelLayerSet(var_r30, 0);
        var_r31 = Hu3DGLightCreateV(&lbl_1_data_8C4, &lbl_1_data_8D0, &lbl_1_data_8DC);
        Hu3DGLightStaticSet(var_r31, 1);
        Hu3DGLightPointSet(var_r31, 100.0f, 1.0f, 3);
        lbl_1_bss_BC = 0;
        fn_1_2C24(lbl_1_bss_CC);
    }
}

void fn_1_B41C(void)
{
    if (lbl_1_bss_98 != -1) {
        Hu3DModelKill(lbl_1_bss_98);
    }
    lbl_1_bss_98 = -1;
}

void fn_1_B470(void) { }

s16 fn_1_B474(AnimData *arg0, s16 arg1)
{
    UnkM406Unk120Struct2 *var_r31;
    s16 var_r30;
    Vec2f *var_r29;
    UnkM406Struct5 *var_r28;
    ModelData *var_r27;
    Vec *var_r25;
    void *var_r24;
    s16 var_r23;
    void *var_r22;

    var_r23 = Hu3DHookFuncCreate(fn_1_BC18);
    var_r27 = &Hu3DData[var_r23];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkM406Unk120Struct2), var_r27->unk_48);
    var_r27->unk_120 = var_r31;
    var_r31->unk_38 = arg0;
    var_r31->unk_26 = arg1;
    var_r31->unk_20 = 0;
    var_r31->unk_22 = 0;
    var_r31->unk_4C = 0;
    var_r31->unk_50 = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_21 = 0;
    var_r31->unk_30 = 0;

    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r28 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(UnkM406Struct5), var_r27->unk_48);
    var_r31->unk_3C = var_r28;
    memset(var_r28, 0, arg1 * sizeof(UnkM406Struct5));
    for (var_r30 = 0; var_r30 < arg1; var_r30++, var_r28++) {
        var_r28->unk_28 = 0.0f;
        var_r28->unk_2C = 0.0f;
        var_r28->unk_30.x = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r28->unk_30.y = ((frand() & 0x7F) - 0x40) * 0x1E;
        var_r28->unk_30.z = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r28->unk_3C.r = var_r28->unk_3C.g = var_r28->unk_3C.b = var_r28->unk_3C.a = 0xFF;
        var_r28->unk_40 = 0;
    }
    var_r25 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec) * 4, var_r27->unk_48);
    var_r31->unk_40 = var_r25;
    for (var_r30 = 0; var_r30 < (arg1 * 4); var_r30++, var_r25++) {
        var_r25->x = var_r25->y = var_r25->z = 0.0f;
    }
    var_r29 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec2f) * 4, var_r27->unk_48);
    var_r31->unk_44 = var_r29;
    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        var_r29->x = 0.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 0.0f;
        var_r29++;
        var_r29->x = 1.0f;
        var_r29->y = 1.0f;
        var_r29++;
        var_r29->x = 0.0f;
        var_r29->y = 1.0f;
        var_r29++;
    }
    var_r24 = HuMemDirectMallocNum(HEAP_DATA, 0x10000, var_r27->unk_48);
    var_r22 = var_r24;
    DCFlushRange(var_r24, 0x10000);
    GXBeginDisplayList(var_r22, 0x10000);
    GXBegin(GX_QUADS, GX_VTXFMT0, arg1 * 4);
    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        // TODO
        GXUnknownu16(var_r30 * 4);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4);

        GXUnknownu16(var_r30 * 4 + 1);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4 + 1);

        GXUnknownu16(var_r30 * 4 + 2);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4 + 2);

        GXUnknownu16(var_r30 * 4 + 3);
        GXUnknownu16(var_r30);
        GXUnknownu16(var_r30 * 4 + 3);
    }
    var_r31->unk_34 = GXEndDisplayList();
    var_r31->unk_48 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_34, var_r27->unk_48);
    memcpy(var_r31->unk_48, var_r24, var_r31->unk_34);
    DCFlushRange(var_r31->unk_48, var_r31->unk_34);
    HuMemDirectFree(var_r24);
    (void)arg1;
    return var_r23;
}

s16 fn_1_B8FC(s16 arg0)
{
    UnkM406Unk120Struct2 *var_r31;
    Vec2f *var_r30;
    UnkM406Struct5 *var_r29;
    ModelData *var_r27;
    s16 var_r28;
    UnkM406Unk120Struct2 *var_r26;
    Vec *var_r25;
    s32 var_r24;
    ModelData *var_r23;
    s16 var_r22;

    var_r23 = &Hu3DData[arg0];
    var_r26 = var_r23->unk_120;
    var_r22 = Hu3DHookFuncCreate(var_r23->hook);
    var_r27 = &Hu3DData[var_r22];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkM406Unk120Struct2), var_r27->unk_48);
    var_r27->unk_120 = var_r31;
    var_r31->unk_38 = var_r26->unk_38;
    var_r31->unk_26 = var_r26->unk_26;
    var_r24 = var_r31->unk_26;
    var_r31->unk_20 = 0;
    var_r31->unk_22 = var_r26->unk_22;
    var_r31->unk_4C = 0;
    var_r31->unk_50 = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_21 = 0;
    var_r31->unk_30 = 0;

    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r29 = HuMemDirectMallocNum(HEAP_DATA, var_r24 * sizeof(UnkM406Struct5), var_r27->unk_48);
    var_r31->unk_3C = var_r29;
    for (var_r28 = 0; var_r28 < var_r24; var_r28++, var_r29++) {
        var_r29->unk_28 = 0.0f;
        var_r29->unk_2C = 0.0f;
        var_r29->unk_30.x = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r29->unk_30.y = ((frand() & 0x7F) - 0x40) * 0x1E;
        var_r29->unk_30.z = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r29->unk_3C.r = var_r29->unk_3C.g = var_r29->unk_3C.b = var_r29->unk_3C.a = 0xFF;
        var_r29->unk_40 = 0;
    }
    var_r25 = HuMemDirectMallocNum(HEAP_DATA, var_r24 * sizeof(Vec) * 4, var_r27->unk_48);
    var_r31->unk_40 = var_r25;
    for (var_r28 = 0; var_r28 < (var_r24 * 4); var_r28++, var_r25++) {
        var_r25->x = var_r25->y = var_r25->z = 0.0f;
    }
    var_r30 = HuMemDirectMallocNum(HEAP_DATA, var_r24 * sizeof(Vec2f) * 4, var_r27->unk_48);
    var_r31->unk_44 = var_r30;
    for (var_r28 = 0; var_r28 < var_r24; var_r28++) {
        var_r30->x = 0.0f;
        var_r30->y = 0.0f;
        var_r30++;
        var_r30->x = 1.0f;
        var_r30->y = 0.0f;
        var_r30++;
        var_r30->x = 1.0f;
        var_r30->y = 1.0f;
        var_r30++;
        var_r30->x = 0.0f;
        var_r30->y = 1.0f;
        var_r30++;
    }
    var_r31->unk_34 = var_r26->unk_34;
    var_r31->unk_48 = var_r26->unk_48;
    return var_r22;
}

void fn_1_BC18(ModelData *arg0, float (*arg1)[4])
{
    Mtx sp128;
    Mtx spF8;
    Mtx spC8;
    Vec sp98[4];
    Vec sp68[4];
    Vec sp38[4];
    ROMtx sp8;

    UnkM406Unk120Struct2 *var_r31;
    Vec *var_r30;
    UnkM406Struct5 *var_r29;
    Vec2f *var_r28;
    Vec *var_r27;
    s16 var_r26;
    s16 var_r25;
    Vec *var_r24;
    s16 var_r21;
    s16 var_r20;
    s16 var_r19;
    UnkM406Unk120Struct2Hook var_r18;

    var_r31 = arg0->unk_120;
    if (var_r31->unk_2C != GlobalCounter || shadowModelDrawF) {
        if (var_r31->unk_50 && var_r31->unk_50 != arg0) {
            fn_1_BC18(var_r31->unk_50, arg1);
        }
        GXLoadPosMtxImm(arg1, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        if (shadowModelDrawF) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        }
        else {
            var_r21 = var_r31->unk_38->bmp->dataFmt & 0xF;
            if (var_r21 == 7 || var_r21 == 8) {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            }
            else {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            }
            if (var_r31->unk_22 & 1) {
                GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
            }
            else if (arg0->attr & 2) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            }
            else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            }
        }
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
        HuSprTexLoad(var_r31->unk_38, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(GX_FALSE);
        switch (var_r31->unk_20) {
            case 0:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
                break;
            case 1:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
                break;
            case 2:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
                break;
        }
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSETARRAY(GX_VA_POS, var_r31->unk_40, var_r31->unk_26 * sizeof(Vec) * 4, sizeof(Vec));
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSETARRAY(GX_VA_CLR0, &var_r31->unk_3C->unk_3C, sizeof(GXColor), 0x44);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSETARRAY(GX_VA_TEX0, var_r31->unk_44, var_r31->unk_26 * sizeof(Vec2f) * 4, sizeof(Vec2f));
        if (HmfInverseMtxF3X3(arg1, sp128) == 0) {
            MTXIdentity(sp128);
        }
        MTXReorder(sp128, sp8);
        if (var_r31->unk_4C) {
            var_r18 = var_r31->unk_4C;
            var_r18(arg0, var_r31, arg1);
        }
        var_r29 = var_r31->unk_3C;
        var_r30 = var_r31->unk_40;
        var_r28 = var_r31->unk_44;
        MTXROMultVecArray(sp8, lbl_1_data_8E0, &sp38[0], 4);
        for (var_r26 = 0; var_r26 < var_r31->unk_26; var_r26++, var_r29++) {
            if (!var_r29->unk_28) {
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
            }
            else if (!var_r29->unk_2C) {
                var_r27 = &sp98[0];
                var_r24 = &sp38[0];
                VECScale(var_r24++, var_r27, var_r29->unk_28);
                VECAdd(var_r27++, &var_r29->unk_30, var_r30++);
                VECScale(var_r24++, var_r27, var_r29->unk_28);
                VECAdd(var_r27++, &var_r29->unk_30, var_r30++);
                VECScale(var_r24++, var_r27, var_r29->unk_28);
                VECAdd(var_r27++, &var_r29->unk_30, var_r30++);
                VECScale(var_r24++, var_r27, var_r29->unk_28);
                VECAdd(var_r27++, &var_r29->unk_30, var_r30++);
            }
            else {
                VECScale(lbl_1_data_8E0, &sp98[0], var_r29->unk_28);
                VECScale(&lbl_1_data_8E0[1], &sp98[1], var_r29->unk_28);
                VECScale(&lbl_1_data_8E0[2], &sp98[2], var_r29->unk_28);
                VECScale(&lbl_1_data_8E0[3], &sp98[3], var_r29->unk_28);
                MTXRotRad(spC8, 90, var_r29->unk_2C);
                MTXConcat(sp128, spC8, spF8);
                MTXMultVecArray(spF8, &sp98[0], &sp68[0], 4);
                VECAdd(&sp68[0], &var_r29->unk_30, var_r30++);
                VECAdd(&sp68[1], &var_r29->unk_30, var_r30++);
                VECAdd(&sp68[2], &var_r29->unk_30, var_r30++);
                VECAdd(&sp68[3], &var_r29->unk_30, var_r30++);
            }
        }
        var_r29 = var_r31->unk_3C;
        var_r28 = var_r31->unk_44;
        if ((var_r31->unk_22 & 2) == 0) {
            for (var_r26 = 0; var_r26 < var_r31->unk_26; var_r26++, var_r29++) {
                var_r20 = var_r29->unk_40 & 3;
                var_r19 = (var_r29->unk_40 >> 2) & 3;
                for (var_r25 = 0; var_r25 < 4; var_r25++, var_r28++) {
                    var_r28->x = (0.25f * var_r20) + lbl_1_data_910[var_r25].x;
                    var_r28->y = (0.25f * var_r19) + lbl_1_data_910[var_r25].y;
                }
            }
        }
        else {
            for (var_r26 = 0; var_r26 < var_r31->unk_26; var_r26++, var_r29++) {
                for (var_r25 = 0; var_r25 < 4; var_r25++, var_r28++) {
                    var_r28->x = 4.0f * lbl_1_data_910[var_r25].x;
                    var_r28->y = 4.0f * lbl_1_data_910[var_r25].y;
                }
            }
        }
        DCFlushRangeNoSync(var_r31->unk_40, var_r31->unk_26 * 0xC * 4);
        DCFlushRangeNoSync(var_r31->unk_44, var_r31->unk_26 * 8 * 4);
        DCFlushRangeNoSync(var_r31->unk_3C, var_r31->unk_26 * 0x44);
        PPCSync();
        GXCallDisplayListNative(var_r31->unk_48, var_r31->unk_34);
        if (!shadowModelDrawF) {
            if ((var_r31->unk_21 & 2) == 0) {
                var_r31->unk_28++;
            }
            if ((var_r31->unk_30 != 0) && (var_r31->unk_30 <= var_r31->unk_28)) {
                if (var_r31->unk_21 & 1) {
                    var_r31->unk_28 = 0;
                }
                var_r31->unk_28 = var_r31->unk_30;
            }
            var_r31->unk_2C = GlobalCounter;
        }
    }
}

s16 fn_1_C4F4(s16 arg0)
{
    Vec2f *sp8;

    UnkM406Unk120Struct2 *var_r31;
    UnkM406Struct5 *var_r30;
    s16 var_r29;
    ModelData *var_r28;
    Vec *var_r27;
    void *var_r25;
    s16 var_r24;
    void *var_r23;

    var_r24 = Hu3DHookFuncCreate(fn_1_C86C);
    var_r28 = &Hu3DData[var_r24];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkM406Unk120Struct2), var_r28->unk_48);
    var_r28->unk_120 = var_r31;
    var_r31->unk_38 = 0;
    var_r31->unk_26 = arg0;
    var_r31->unk_20 = 0;
    var_r31->unk_22 = 0;
    var_r31->unk_4C = 0;
    var_r31->unk_50 = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_21 = 0;
    var_r31->unk_30 = 0;

    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r30 = HuMemDirectMallocNum(HEAP_DATA, arg0 * sizeof(UnkM406Struct5), var_r28->unk_48);
    var_r31->unk_3C = var_r30;
    memset(var_r30, 0, arg0 * sizeof(UnkM406Struct5));
    for (var_r29 = 0; var_r29 < arg0; var_r29++, var_r30++) {
        var_r30->unk_28 = 0.0f;
        var_r30->unk_2C = 0.0f;
        var_r30->unk_30.x = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r30->unk_30.y = ((frand() & 0x7F) - 0x40) * 0x1E;
        var_r30->unk_30.z = ((frand() & 0x7F) - 0x40) * 0x14;
        var_r30->unk_3C.r = var_r30->unk_3C.g = var_r30->unk_3C.b = var_r30->unk_3C.a = 0xFF;
        var_r30->unk_40 = 0;
    }
    var_r27 = HuMemDirectMallocNum(HEAP_DATA, arg0 * sizeof(Vec) * 4, var_r28->unk_48);
    var_r31->unk_40 = var_r27;
    for (var_r29 = 0; var_r29 < (arg0 * 4); var_r29++, var_r27++) {
        var_r27->x = var_r27->y = var_r27->z = 0.0f;
    }
    var_r31->unk_44 = sp8 = NULL;
    var_r25 = HuMemDirectMallocNum(HEAP_DATA, 0x10000, var_r28->unk_48);
    var_r23 = var_r25;
    DCFlushRange(var_r25, 0x10000);
    GXBeginDisplayList(var_r23, 0x10000);
    GXBegin(GX_QUADS, GX_VTXFMT0, arg0 * 4);
    for (var_r29 = 0; var_r29 < arg0; var_r29++) {
        GXUnknownu16(var_r29 * 4);
        GXUnknownu16(var_r29);
        GXUnknownu16(var_r29 * 4 + 1);
        GXUnknownu16(var_r29);
        GXUnknownu16(var_r29 * 4 + 2);
        GXUnknownu16(var_r29);
        GXUnknownu16(var_r29 * 4 + 3);
        GXUnknownu16(var_r29);
    }
    var_r31->unk_34 = GXEndDisplayList();
    var_r31->unk_48 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_34, var_r28->unk_48);
    memcpy(var_r31->unk_48, var_r25, var_r31->unk_34);
    DCFlushRange(var_r31->unk_48, var_r31->unk_34);
    HuMemDirectFree(var_r25);
    return var_r24;
}

void fn_1_C86C(ModelData *arg0, Mtx arg1)
{
    Mtx sp9C;
    ROMtx sp6C;
    ROMtx sp3C;
    ROMtx spC;
    Vec2f *sp8;

    UnkM406Unk120Struct2 *var_r31;
    Vec *var_r30;
    UnkM406Struct5 *var_r29;
    Vec *var_r28;
    Vec *var_r27;
    s16 var_r25;
    UnkM406Unk120Struct2Hook var_r23;

    var_r31 = arg0->unk_120;
    if (var_r31->unk_2C != GlobalCounter || shadowModelDrawF) {
        if (var_r31->unk_50 && var_r31->unk_50 != arg0) {
            fn_1_C86C(var_r31->unk_50, arg1);
        }
        GXLoadPosMtxImm(arg1, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(GX_FALSE);
        if (arg0->attr & 2) {
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        }
        else {
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        }
        switch (var_r31->unk_20) {
            case 0:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
                break;
            case 1:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
                break;
            case 2:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
                break;
        }
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSETARRAY(GX_VA_POS, var_r31->unk_40, var_r31->unk_26 * sizeof(Vec) * 4, sizeof(Vec));
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSETARRAY(GX_VA_CLR0, &var_r31->unk_3C->unk_3C, sizeof(GXColor), 0x44);
        if (HmfInverseMtxF3X3(arg1, sp9C) == 0) {
            MTXIdentity(sp9C);
        }
        MTXReorder(sp9C, spC);
        if (var_r31->unk_4C) {
            var_r23 = var_r31->unk_4C;
            var_r23(arg0, var_r31, arg1);
        }
        var_r29 = var_r31->unk_3C;
        var_r30 = var_r31->unk_40;
        sp8 = var_r31->unk_44;
        MTXROMultVecArray(spC, lbl_1_data_930, (Vec *)sp3C, 4);
        for (var_r25 = 0; var_r25 < var_r31->unk_26; var_r25++, var_r29++) {
            if (!var_r29->unk_28) {
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
            }
            else {
                var_r28 = (Vec *)&sp6C;
                var_r27 = (Vec *)&sp3C;
                VECScale(var_r27++, var_r28, var_r29->unk_28);
                VECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                VECScale(var_r27++, var_r28, var_r29->unk_28);
                VECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                VECScale(var_r27++, var_r28, var_r29->unk_28);
                VECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                VECScale(var_r27++, var_r28, var_r29->unk_28);
                VECAdd(var_r28++, &var_r29->unk_30, var_r30++);
            }
        }
        DCFlushRangeNoSync(var_r31->unk_40, var_r31->unk_26 * 0xC * 4);
        DCFlushRangeNoSync(var_r31->unk_3C, var_r31->unk_26 * 0x44);
        PPCSync();
        GXCallDisplayListNative(var_r31->unk_48, var_r31->unk_34);
        if (!shadowModelDrawF) {
            if ((var_r31->unk_21 & 2) == 0) {
                var_r31->unk_28++;
            }
            if ((var_r31->unk_30 != 0) && (var_r31->unk_30 <= var_r31->unk_28)) {
                if (var_r31->unk_21 & 1) {
                    var_r31->unk_28 = 0;
                }
                var_r31->unk_28 = var_r31->unk_30;
            }
            var_r31->unk_2C = GlobalCounter;
        }
    }
}

s32 fn_1_CD34(s32 arg0, s32 arg1, s32 arg2)
{
    ModelData *var_r29;
    ModelData *var_r30;
    s32 var_r31;

    var_r29 = &Hu3DData[arg0];
    var_r30 = &Hu3DData[arg2];
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        if (var_r30->unk_38[var_r31] == -1) {
            break;
        }
    }
    if (var_r31 == 8) {
        return -1;
    }
    var_r30->unk_38[var_r31] = var_r29->unk_38[arg1];
    var_r30->attr |= 0x1000;
    return var_r31;
}

void fn_1_CDD8(s32 arg0, float arg8, float arg9, float argA, float argB)
{
    HsfMaterial *var_r31;
    s32 var_r30;
    HsfData *var_r29;
    s32 var_r28;
    ModelData *var_r27;
    s32 var_r26;

    var_r27 = &Hu3DData[arg0];
    var_r29 = var_r27->hsfData;
    var_r31 = var_r29->material;
    var_r26 = var_r29->materialCnt;
    for (var_r28 = 0; var_r28 < var_r26; var_r28++, var_r31++) {
        var_r31->vtxMode = 1;
        var_r30 = arg9 * (var_r31->litColor[0] * arg8);
        if (var_r30 > 0xFF) {
            var_r30 = 0xFF;
        }
        var_r31->litColor[0] = var_r30;
        var_r30 = argA * (var_r31->litColor[1] * arg8);
        if (var_r30 > 0xFF) {
            var_r30 = 0xFF;
        }
        var_r31->litColor[1] = var_r30;
        var_r30 = argB * (var_r31->litColor[2] * arg8);
        if (var_r30 > 0xFF) {
            var_r30 = 0xFF;
        }
        var_r31->litColor[2] = var_r30;
    }
}

void fn_1_CF24(s32 arg0, u8 arg1, u8 arg2, u8 arg3)
{
    HsfMaterial *var_r31;
    HsfData *var_r30;
    s32 var_r29;
    ModelData *var_r28;
    s32 var_r27;

    var_r28 = &Hu3DData[arg0];
    var_r30 = var_r28->hsfData;
    var_r31 = var_r30->material;
    var_r27 = var_r30->materialCnt;
    for (var_r29 = 0; var_r29 < var_r27; var_r29++, var_r31++) {
        var_r31->vtxMode = 1;
        var_r31->litColor[0] = arg1;
        var_r31->litColor[1] = arg2;
        var_r31->litColor[2] = arg3;
    }
}

void fn_1_CF98(s32 arg0, s32 arg1)
{
    s32 var_r31;
    HsfData *var_r30;
    HsfData *var_r29;
    ModelData *var_r28;
    ModelData *var_r27;

    var_r28 = &Hu3DData[arg0];
    var_r27 = &Hu3DData[arg1];
    var_r29 = var_r28->hsfData;
    var_r30 = var_r27->hsfData;
    for (var_r31 = 0; var_r31 < var_r30->bitmapCnt; var_r31++) {
        memcpy(&var_r30->bitmap[var_r31], &var_r29->bitmap[var_r31], 0x20);
    }
    for (var_r31 = 0; var_r31 < var_r30->attributeCnt; var_r31++) {
        memcpy(&var_r30->attribute[var_r31], &var_r29->attribute[var_r31], 0x84);
    }
}

s16 fn_1_D06C(ModelData *arg0, Mtx arg1, Mtx arg2, float arg8)
{
    s16 var_r31;
    s16 var_r29;
    s16 var_r28;
    LightData *var_r27;

    var_r28 = 0;
    var_r29 = 1;
    if (arg0->attr & 0x1000) {
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            if (arg0->unk_38[var_r31] != -1) {
                var_r27 = &Hu3DLocalLight[arg0->unk_38[var_r31]];
                fn_1_D13C(var_r27, var_r29, arg2, arg1, arg8);
                var_r28 |= var_r29;
                var_r29 <<= 1;
            }
        }
    }
    return var_r28;
}

void fn_1_D13C(LightData *arg0, s16 arg1, Mtx arg2, Mtx arg3, float arg8)
{
    GXLightObj sp30;
    Vec sp24;
    Vec sp18;

    switch ((u8)arg0->unk_00) {
        case 0:
            GXInitLightAttn(&sp30, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            GXInitLightSpot(&sp30, arg0->unk_04, arg0->unk_02);
            break;
        case 1:
            GXInitLightAttn(&sp30, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            GXInitLightSpot(&sp30, 20.0f, GX_SP_COS);
            GXInitLightAttnK(&sp30, 1.0f, 0.0f, 0.0f);
            VECScale(&arg0->unk_28, &arg0->unk_1C, -1000000.0f);
            break;
        case 2:
            GXInitLightAttn(&sp30, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            GXInitLightDistAttn(&sp30, arg0->unk_04, arg0->unk_08, arg0->unk_02);
            break;
        default:
            break;
    }
    if (arg0->unk_00 & 0x8000) {
        MTXMultVec(arg2, &arg0->unk_28, &sp24);
        MTXMultVec(arg3, &arg0->unk_1C, &sp18);
        GXInitLightPos(&sp30, sp18.x, sp18.y, sp18.z);
    }
    else {
        GXInitLightPos(&sp30, arg0->unk_1C.x, arg0->unk_1C.y, arg0->unk_1C.z);
        sp24 = arg0->unk_28;
    }
    if (arg8 == 0.0f) {
        GXInitLightDir(&sp30, sp24.x, sp24.y, sp24.z);
    }
    else {
        GXInitSpecularDir(&sp30, sp24.x, sp24.y, sp24.z);
        GXInitLightAttn(&sp30, 0.0f, 0.0f, 1.0f, arg8 / 2, 0.0f, 1.0f - (arg8 / 2));
    }
    GXInitLightColor(&sp30, arg0->color);
    GXLoadLightObjImm(&sp30, arg1);
}

void fn_1_D488(float arg8, Vec *arg0, Vec *arg1, Vec *arg2)
{
    lbl_1_bss_3C.x = arg0->x + (arg8 * (arg1->x - arg0->x));
    lbl_1_bss_3C.y = arg0->y + (arg8 * (arg1->y - arg0->y));
    lbl_1_bss_3C.z = arg0->z + (arg8 * (arg1->z - arg0->z));
    *arg2 = lbl_1_bss_3C;
}

void fn_1_D518(Mtx arg0, Vec *arg1)
{
    Vec sp8;

    sp8.x = (arg0[0][2] * arg1->z) + ((arg0[0][0] * arg1->x) + (arg0[0][1] * arg1->y));
    sp8.y = (arg0[1][2] * arg1->z) + ((arg0[1][0] * arg1->x) + (arg0[1][1] * arg1->y));
    sp8.z = (arg0[2][2] * arg1->z) + ((arg0[2][0] * arg1->x) + (arg0[2][1] * arg1->y));
    *arg1 = sp8;
}

float fn_1_D5CC(Vec *arg0, Vec *arg1, float arg8, float arg9)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    var_f31 = arg0->x - arg8;
    var_f30 = arg0->z - arg9;
    var_f29 = arg1->x - arg8;
    var_f28 = arg1->z - arg9;

    var_f27 = -((var_f30 * var_f29) - (var_f31 * var_f28));
    return var_f27;
}
