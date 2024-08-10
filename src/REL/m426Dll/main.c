#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "rel_sqrt_consts.h"

typedef struct UnkM426Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ omObjData *unk_04[2];
    /* 0x0C */ u8 unk_0C[2];
    /* 0x0E */ u8 unk_0E[6];
} UnkM426Struct; /* size = 0x14 */

typedef struct UnkM426Struct3 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ char unk2C[8];
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ float unk_38;
} UnkM426Struct3; /* size = 0x3C */

typedef struct UnkM426Struct2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ float unk_40;
    /* 0x44 */ float unk_44;
    /* 0x48 */ omObjData *unk_48;
    /* 0x4C */ omObjData *unk_4C;
    /* 0x50 */ float unk_50[15];
    /* 0x8C */ s32 unk_8C;
    /* 0x90 */ s32 unk_90;
    /* 0x94 */ s32 unk_94;
    /* 0x98 */ float unk_98;
    /* 0x9C */ Vec unk_9C;
    /* 0xA8 */ s32 unk_A8;
    /* 0xAC */ s32 unk_AC;
    /* 0xB0 */ s32 unk_B0;
    /* 0xB4 */ s32 unk_B4;
    /* 0xB8 */ s32 unk_B8;
    /* 0xBC */ s32 unk_BC;
} UnkM426Struct2; /* size = 0xC0 */

typedef struct UnkM426Struct4 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[8];
    /* 0x18 */ s32 unk_18;
    /* 0x0C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ float unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ float unk_3C;
    /* 0x40 */ float unk_40;
    /* 0x44 */ float unk_44;
    /* 0x48 */ float unk_48;
    /* 0x4C */ float unk_4C;
} UnkM426Struct4; /* size = 0x50 */

typedef struct UnkM426Struct5 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ AnimData *unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ Vec unk_14;
    /* 0x20 */ float unk_20;
} UnkM426Struct5; /* size = 0x24 */

typedef struct UnkM426Struct6 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
    /* 0x18 */ float unk_18;
} UnkM426Struct6; /* size = 0x1C */

typedef struct UnkM426Struct7 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14[6];
    /* 0x2C */ s32 unk_2C[6][3];
    /* 0x74 */ s32 unk_74[6][3];
    /* 0xBC */ s32 unk_BC;
    /* 0xC0 */ s32 unk_C0;
} UnkM426Struct7; /* size = 0xC4 */

typedef struct UnkM426Struct8 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec unk_04;
    /* 0x10 */ char unk10[0x18];
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ Vec unk_30;
    /* 0x3C */ GXColor unk_3C;
    /* 0x40 */ s32 unk_40;
} UnkM426Struct8; /* size = 0x44 */

typedef struct UnkM426Struct9 {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ s32 unk_14;
} UnkM426Struct9; /* size = unknown */

typedef void (*UnkModelDataUnk120Hook)(struct model_data *, struct UnkModelDataUnk120Struct *, Mtx);

typedef struct UnkModelDataUnk120Struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ char unk04[0x1C];
    /* 0x20 */ u8 unk_20;
    /* 0x21 */ u8 unk_21;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ char unk26[2];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ u32 unk_30;
    /* 0x34 */ u32 unk_34;
    /* 0x38 */ AnimData *unk_38;
    /* 0x3C */ UnkM426Struct8 *unk_3C;
    /* 0x40 */ Vec *unk_40;
    /* 0x44 */ Vec2f *unk_44;
    /* 0x48 */ void *unk_48;
    /* 0x4C */ UnkModelDataUnk120Hook unk_4C;
    /* 0x50 */ ModelData *unk_50;
} UnkModelDataUnk120Struct; /* size = 0x54 */

typedef struct UnkM426Struct10 {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk08[4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[4];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ struct UnkM426Struct10 **unk_18;
    /* 0x1C */ char unk1C[0x48];
    /* 0x64 */ struct UnkM426Struct10 *unk_64;
} UnkM426Struct10; /* size = unknown */

typedef struct UnkM426Struct11 {
    /* 0x00 */ u16 unk_00;
    /* 0x04 */ u16 unk_04;
    /* 0x08 */ u16 unk_08;
    /* 0x0C */ u16 unk_0C;
} UnkM426Struct11; /* size = 0x10 */

typedef struct UnkM426Struct12 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk02[0x0A];
    /* 0x0C */ UnkM426Struct11 unk_0C;
    /* 0x14 */ UnkM426Struct11 unk_14;
    /* 0x1C */ char unk1C[0x14];
} UnkM426Struct12; /* size = 0x30 */

typedef struct UnkM426Struct13 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u32 unk_04;
} UnkM426Struct13; /* size = 0x08 */

void fn_1_1004(omObjData *object);
void fn_1_117C(omObjData *object);
void fn_1_125C(omObjData *object);
void fn_1_16F8(omObjData *object);
void fn_1_20C(omObjData *object);
void fn_1_2AC8(omObjData *object);
void fn_1_2ADC(void);
s32 fn_1_2EDC(void);
void fn_1_2F5C(omObjData *object, float *arg1, float *arg2, s32 *arg3);
void fn_1_330(omObjData *object);
void fn_1_36C4(void);
void fn_1_3714(omObjData *object);
void fn_1_3EFC(omObjData *object);
void fn_1_4644(void);
void fn_1_4738(s32 arg0, s32 arg1);
s32 fn_1_4894(s32 arg0);
s32 fn_1_48F0(float arg8);
float fn_1_4A68(s32 arg0);
s32 fn_1_4AF4(Vec *arg0, float arg8, s32 arg1);
void fn_1_4EC4(void);
void fn_1_4F14(omObjData *object);
void fn_1_5134(omObjData *object);
void fn_1_5B48(void);
s32 fn_1_5C6C(s32 arg0, s32 arg1, Vec *arg2);
s32 fn_1_5D3C(void);
void fn_1_5E6C(void);
void fn_1_5EBC(omObjData *object);
void fn_1_6008(omObjData *object);
void fn_1_61E0(void);
s32 fn_1_6248(Vec *arg0);
void fn_1_6310(s32 arg0, Vec *arg1);
s32 fn_1_63B8(s32 arg0, Vec *arg1, Vec *arg2, float arg8, GXColor arg3);
void fn_1_6594(void);
void fn_1_65E4(omObjData *object);
void fn_1_6704(omObjData *object);
void fn_1_6844(void);
s32 fn_1_6888(Vec *arg0);
void fn_1_69E4(void);
void fn_1_6A34(omObjData *object);
void fn_1_6DC0(omObjData *object);
void fn_1_7278(void);
void fn_1_7328(s32 arg0);
void fn_1_73DC(void);
void fn_1_758C(omObjData *object);
void fn_1_75AC(omObjData *object);
void fn_1_75BC(void);
float fn_1_75F4(float arg8, float arg9);
float fn_1_770C(float arg8, float arg9, float argA);
s16 fn_1_795C(AnimData *arg0, s16 arg1);
s16 fn_1_7DC8(s16 arg0);
void fn_1_80DC(ModelData *arg0, Mtx arg1);
void fn_1_88B4(ModelData *arg0, Mtx arg1);
void fn_1_8E10(AnimData *arg0);
void fn_1_8E48(ModelData *arg0, Mtx arg1);
void fn_1_9230(s32 arg0, UnkM426Struct10 *arg1, s32 arg2);
void fn_1_9544(s32 arg0, UnkM426Struct10 *arg1, s32 arg2);
void fn_1_971C(s32 arg0, UnkM426Struct10 *arg1, s32 arg2);
void fn_1_9798(s32 arg0, UnkM426Struct10 *arg1, s32 arg2);
void fn_1_97EC(s32 arg0, UnkM426Struct10 *arg1, s32 arg2);
void fn_1_9868(s32 arg0, UnkM426Struct10 *arg1, s32 arg2);
float fn_1_98E4(float arg8, float arg9, float argA, float argB);
void fn_1_DB8(omObjData *object);
void fn_1_E18(omObjData *object);
void fn_1_EB8(void);

extern u32 GlobalCounter;

Vec lbl_1_data_0[4] = {
    { -600.0f, 0.0f, -285.0f },
    { -600.0f, 0.0f, 135.0f },
    { 600.0f, 0.0f, -285.0f },
    { 600.0f, 0.0f, 135.0f },
};

Vec lbl_1_data_30 = { -200.0f, 2500.0f, 1200.0f };

Vec lbl_1_data_3C = { 0.2f, -0.8f, -0.2f };

GXColor lbl_1_data_48 = { 143, 143, 143, 143 };

float lbl_1_data_4C[3][7] = {
    { 315.0f, 0.0f, 0.0f, 0.0f, 130.0f, -180.0f, 1625.0f },
    { 339.0f, 0.0f, 0.0f, 0.0f, 5.0f, -1446.0f, 1625.0f },
    { 339.0f, 0.0f, 0.0f, 0.0f, 5.0f, -380.0f, 1625.0f },
};

Vec lbl_1_data_A0 = { 0.0f, 2500.0f, -500.0f };

Vec lbl_1_data_AC = { 0.0f, 1.0f, 0.0f };

Vec lbl_1_data_B8 = { 0.0f, 0.0f, 0.0f };

Process *lbl_1_bss_98;
omObjData *lbl_1_bss_94;
omObjData *lbl_1_bss_8C[2];
omObjData *lbl_1_bss_7C[4];
omObjData *lbl_1_bss_78;
omObjData *lbl_1_bss_74;
omObjData *lbl_1_bss_70;
omObjData *lbl_1_bss_6C;
omObjData *lbl_1_bss_68;
omObjData *lbl_1_bss_64;
s32 lbl_1_bss_60;
s32 lbl_1_bss_5C;
s32 lbl_1_bss_58;
s32 lbl_1_bss_54;
s32 lbl_1_bss_50;
s32 lbl_1_bss_4C;
s32 lbl_1_bss_48;
s32 lbl_1_bss_44;
s32 lbl_1_bss_40;
s32 lbl_1_bss_3C;
s32 lbl_1_bss_38;
float lbl_1_bss_34;
s32 lbl_1_bss_30;
s32 lbl_1_bss_2C;
float lbl_1_bss_28;
AnimData *lbl_1_bss_24;
s32 lbl_1_bss_1C[2];
u8 lbl_1_bss_18[4];
Vec lbl_1_bss_C;
Vec lbl_1_bss_0;

void ObjectSetup(void)
{
    Process *var_r31;
    LightData *var_r30;
    s32 var_r29;

    OSReport("******* M426ObjectSetup *********\n");
    Hu3DLighInit();
    var_r29 = Hu3DGLightCreateV(&lbl_1_data_30, &lbl_1_data_3C, &lbl_1_data_48);
    lbl_1_bss_2C = var_r29;
    Hu3DGLightInfinitytSet(var_r29);
    var_r30 = Hu3DGlobalLight;
    var_r30->unk_00 |= 32768;
    lbl_1_bss_28 = 0.0f;
    var_r31 = omInitObjMan(50, 8192);
    lbl_1_bss_98 = var_r31;
    omGameSysInit(var_r31);
    HuAudSndGrpSet(51);
    fn_1_73DC();
    lbl_1_bss_94 = omAddObjEx(var_r31, 255, 2, 0, -1, fn_1_20C);
    Hu3DShadowCreate(35.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_data_A0, &lbl_1_data_AC, &lbl_1_data_B8);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
}

void fn_1_20C(omObjData *object)
{
    object->model[0] = Hu3DHookFuncCreate(fn_1_8E48);
    Hu3DModelLayerSet(object->model[0], 1);
    fn_1_EB8();
    fn_1_4EC4();
    fn_1_36C4();
    fn_1_5E6C();
    fn_1_6594();
    fn_1_69E4();
    lbl_1_bss_5C = 0;
    lbl_1_bss_58 = 0;
    lbl_1_bss_54 = 0;
    lbl_1_bss_48 = -1;
    lbl_1_bss_44 = 1;
    lbl_1_bss_40 = 0;
    lbl_1_bss_3C = 0;
    lbl_1_bss_38 = 0;
    lbl_1_bss_34 = 2.0f;
    lbl_1_bss_1C[0] = lbl_1_bss_1C[1] = 10;
    object->func = fn_1_330;
}

void fn_1_330(omObjData *object)
{
    float sp10[16];

    float var_f31;

    s32 var_r31;
    UnkM426Struct *var_r30;
    UnkM426Struct2 *var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    var_r28 = -1;
    {
        s32 sp8[2] = { 0, 1 };
        switch (lbl_1_bss_54) {
            case 0:
                if (!WipeStatGet()) {
                    lbl_1_bss_54 = 1;
                    lbl_1_bss_58 = 0;
                    lbl_1_bss_30 = 120;
                }
                break;
            case 1:
                if (++lbl_1_bss_58 >= 15.0f) {
                    lbl_1_bss_54 = 2;
                    lbl_1_bss_58 = 0;
                    lbl_1_bss_38 = 1;
                }
                break;
            case 2:
                var_f31 = 0.007246377f * lbl_1_bss_58;
                var_f31 = sind(90.0f * var_f31);
                var_f31 *= var_f31;
                for (var_r31 = 0; var_r31 < 7; var_r31++) {
                    sp10[var_r31] = fn_1_98E4(var_f31, lbl_1_data_4C[1][var_r31], lbl_1_data_4C[2][var_r31], lbl_1_data_4C[0][var_r31]);
                }
                CRot.x = sp10[0];
                CRot.y = sp10[1];
                CRot.z = sp10[2];
                Center.x = sp10[3];
                Center.y = sp10[4];
                Center.z = sp10[5];
                CZoom = sp10[6];
                if (++lbl_1_bss_58 >= 138.0f) {
                    CRot.x = lbl_1_data_4C[0][0];
                    CRot.y = lbl_1_data_4C[0][1];
                    CRot.z = lbl_1_data_4C[0][2];
                    Center.x = lbl_1_data_4C[0][3];
                    Center.y = lbl_1_data_4C[0][4];
                    Center.z = lbl_1_data_4C[0][5];
                    CZoom = lbl_1_data_4C[1][6];
                    lbl_1_bss_54 = 3;
                    lbl_1_bss_58 = 0;
                }
                break;
            case 3:
                if (++lbl_1_bss_58 >= 30.0f) {
                    lbl_1_bss_50 = MGSeqCreate(3, 0);
                    lbl_1_bss_54 = 4;
                    lbl_1_bss_58 = 0;
                }
                break;
            case 4:
                if (lbl_1_bss_50 != -1) {
                    var_r26 = MGSeqStatGet(lbl_1_bss_50);
                    if ((var_r26 & 16) && lbl_1_bss_48 == -1) {
                        lbl_1_bss_48 = HuAudSeqPlay(70);
                    }
                } else {
                    var_r26 = 0;
                }
                if (lbl_1_bss_50 == -1 || !var_r26) {
                    lbl_1_bss_50 = -1;
                    lbl_1_bss_40 = 1;
                    lbl_1_bss_3C = 1;
                    lbl_1_bss_54 = 5;
                    lbl_1_bss_58 = 1800;
                    fn_1_7328(1);
                    lbl_1_bss_4C = MGSeqCreate(1, lbl_1_bss_58 / 60, -1, -1);
                }
                break;
            case 5:
                var_r25 = (lbl_1_bss_58 + 59) / 60;
                if (var_r25 < 0) {
                    var_r25 = 0;
                }
                MGSeqParamSet(lbl_1_bss_4C, 1, var_r25);
                if (lbl_1_bss_58 == 600) {
                    lbl_1_bss_34 = 3.0f;
                } else if (lbl_1_bss_58 == 1200) {
                    lbl_1_bss_34 = 2.5f;
                }
                if (--lbl_1_bss_58 < -1 || lbl_1_bss_1C[0] <= 0 || lbl_1_bss_1C[1] <= 0) {
                    MGSeqParamSet(lbl_1_bss_4C, 2, -1);
                    lbl_1_bss_4C = -1;
                    HuAudSeqAllFadeOut(100);
                    lbl_1_bss_50 = MGSeqCreate(3, 1);
                    lbl_1_bss_40 = 0;
                    lbl_1_bss_3C = 0;
                    lbl_1_bss_54 = 6;
                    lbl_1_bss_58 = 0;
                }
                break;
            case 6:
                if (lbl_1_bss_50 == -1 || !MGSeqStatGet(lbl_1_bss_50)) {
                    lbl_1_bss_50 = -1;
                    var_r28 = fn_1_5D3C();
                    if (var_r28 >= 0) {
                        if (fn_1_2EDC()) {
                            if (lbl_1_bss_1C[0] == lbl_1_bss_1C[1]) {
                                var_r28 = 2;
                            } else if (lbl_1_bss_1C[0] > lbl_1_bss_1C[1]) {
                                var_r28 = 0;
                            } else {
                                var_r28 = 1;
                            }
                            if (var_r28 < 2) {
                                var_r30 = lbl_1_bss_8C[var_r28]->data;
                                for (var_r31 = 0; var_r31 < 2; var_r31++) {
                                    GWPlayerCoinWinAdd(var_r30->unk_0C[var_r31], 10);
                                    var_r29 = var_r30->unk_04[var_r31]->data;
                                    sp8[var_r31] = var_r29->unk_0C;
                                    var_r29->unk_24 = 8;
                                }
                                var_r30 = lbl_1_bss_8C[~var_r28 & 1]->data;
                                for (var_r31 = 0; var_r31 < 2; var_r31++) {
                                    var_r29 = var_r30->unk_04[var_r31]->data;
                                    var_r29->unk_24 = 9;
                                }
                                lbl_1_bss_50 = MGSeqCreate(5, 3, sp8[0], sp8[1], -1, -1);
                                HuAudSStreamPlay(1);
                            } else {
                                for (var_r27 = 0; var_r27 < 2; var_r27++) {
                                    var_r30 = lbl_1_bss_8C[var_r27]->data;
                                    for (var_r31 = 0; var_r31 < 2; var_r31++) {
                                        var_r29 = var_r30->unk_04[var_r31]->data;
                                        var_r29->unk_24 = 9;
                                    }
                                }
                                lbl_1_bss_50 = MGSeqCreate(3, 2);
                                HuAudSStreamPlay(4);
                            }
                            lbl_1_bss_54 = 7;
                            lbl_1_bss_58 = 0;
                        }
                    }
                }
                break;
            case 7:
                if (++lbl_1_bss_58 > 210.0f) {
                    lbl_1_bss_50 = -1;
                    lbl_1_bss_54 = 8;
                    lbl_1_bss_58 = 0;
                }
                break;
            case 8:
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                object->func = fn_1_DB8;
                break;
            default:
                break;
        }
    }
    lbl_1_bss_5C++;
    fn_1_E18(object);
}

s32 lbl_1_data_10C = 66051;

s32 lbl_1_data_110[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s32 lbl_1_data_150[8] = {
    6225920,
    1703936,
    7143424,
    9043968,
    1114112,
    8716288,
    8454144,
    851968,
};

UnkM426Struct13 lbl_1_data_170[12] = {
    { 6225920, 0xFFFFFFFF },
    { 6225922, 0xFFFFFFFF },
    { 6225923, 0xFFFFFFFF },
    { 6225925, 0xFFFFFFFF },
    { 6225926, 0xFFFFFFFF },
    { 6225940, 0xFFFFFFFF },
    { 6225942, 0xFFFFFFFF },
    { 6225945, 0xFFFFFFFF },
    { 0, 0 },
    { 0, 1 },
    { 6225943, 0xFFFFFFFF },
    { 6226034, 0xFFFFFFFF },
};

s32 lbl_1_data_1D0[2] = { 3735584, 3735592 };

void fn_1_DB8(omObjData *arg0)
{
    if (!WipeStatGet()) {
        fn_1_7278();
        fn_1_6844();
        fn_1_61E0();
        fn_1_4644();
        fn_1_5B48();
        fn_1_2ADC();
        fn_1_75BC();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_E18(omObjData *object)
{
    s32 var_r30;

    var_r30 = 0;
    if (WipeStatGet() || object->func == fn_1_DB8) {
        return;
    }
    if (omSysExitReq) {
        var_r30 = 1;
    }
    if (var_r30) {
        WipeCreate(2, 0, 60);
        HuAudSeqAllFadeOut(100);
        object->func = fn_1_DB8;
    }
}

void fn_1_EB8(void)
{
    s32 var_r31;
    s32 var_r30;

    for (var_r31 = 0, var_r30 = 0; var_r31 < 4; var_r31++) {
        if (!GWPlayerCfg[var_r31].group) {
            lbl_1_bss_18[var_r30] = var_r31;
            var_r30++;
        }
    }
    if (var_r30 != 2) {
        memcpy(&lbl_1_bss_18, &lbl_1_data_10C, 4);
    } else {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (GWPlayerCfg[var_r31].group) {
                lbl_1_bss_18[var_r30] = var_r31;
                var_r30++;
            }
        }
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_8C[var_r31] = omAddObjEx(lbl_1_bss_98, 32, 0, 0, -1, fn_1_1004);
        lbl_1_bss_8C[var_r31]->work[0] = var_r31;
    }
}

void fn_1_1004(omObjData *object)
{
    UnkM426Struct *var_r31;
    s32 var_r30;

    var_r31 = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM426Struct), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(UnkM426Struct));
    var_r31->unk_00 = object->work[0];
    var_r31->unk_0C[0] = lbl_1_bss_18[var_r31->unk_00 * 2];
    var_r31->unk_0C[1] = lbl_1_bss_18[var_r31->unk_00 * 2 + 1];
    for (var_r30 = 0; var_r30 < 6; var_r30++) {
        var_r31->unk_0E[var_r30] = 255;
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31->unk_04[var_r30] = lbl_1_bss_7C[var_r31->unk_0C[var_r30]] = omAddObjEx(lbl_1_bss_98, 36, 1, 12, -1, fn_1_125C);
        var_r31->unk_04[var_r30]->work[0] = var_r31->unk_0C[var_r30];
        var_r31->unk_04[var_r30]->work[1] = var_r31->unk_00;
        var_r31->unk_04[var_r30]->work[2] = var_r30;
    }
    omSetStatBit(object, 160);
    object->func = fn_1_117C;
}

void fn_1_117C(omObjData *object)
{
    UnkM426Struct *var_r31;

    var_r31 = object->data;
    if (lbl_1_bss_5C & 1) {
        fn_1_16F8(var_r31->unk_04[0]);
        fn_1_16F8(var_r31->unk_04[1]);
        return;
    }
    fn_1_16F8(var_r31->unk_04[1]);
    fn_1_16F8(var_r31->unk_04[0]);
}

void fn_1_11EC(omObjData *object) // TODO this probably gets inlined
{
    s32 var_r30;
    UnkM426Struct *var_r29;

    var_r29 = object->data;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        fn_1_2AC8(var_r29->unk_04[var_r30]);
    }
    object->data = NULL;
    object->func = NULL;
}

void fn_1_125C(omObjData *object)
{
    UnkM426Struct2 *var_r31;
    s32 var_r29;
    UnkM426Struct *var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    var_r31 = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM426Struct2), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(UnkM426Struct2));
    var_r31->unk_00 = object->work[1];
    var_r31->unk_04 = object->work[0];
    var_r31->unk_08 = object->work[2];
    var_r26 = GWPlayerCfg[var_r31->unk_04].character;
    var_r31->unk_0C = var_r26;
    var_r31->unk_10 = GWPlayerCfg[var_r31->unk_04].pad_idx;
    var_r31->unk_14 = GWPlayerCfg[var_r31->unk_04].iscom;
    var_r31->unk_18 = GWPlayerCfg[var_r31->unk_04].diff;
    var_r26 = 0;
    var_r27 = var_r31->unk_08 + (var_r31->unk_00 * 2);
    var_r31->unk_B0 = -1;
    var_r31->unk_B4 = 0;
    var_r31->unk_B8 = frand() % 15;
    var_r31->unk_BC = 0;
    var_r31->unk_1C = 0;
    var_r31->unk_20 = 0;
    var_r31->unk_24 = 0;
    var_r31->unk_28 = 0;
    var_r31->unk_2C = 0;
    var_r31->unk_30 = 0;
    var_r31->unk_34 = 0;
    var_r31->unk_38 = 0;
    var_r31->unk_3C = 0;
    var_r31->unk_40 = lbl_1_data_0[var_r27].x;
    if (var_r31->unk_40 < 0.0f) {
        var_r31->unk_44 = 90.0f;
    } else {
        var_r31->unk_44 = -90.0f;
    }
    var_r31->unk_48 = lbl_1_bss_8C[var_r31->unk_00];
    var_r28 = var_r31->unk_48->data;
    if (object != var_r28->unk_04[0]) {
        var_r31->unk_4C = var_r28->unk_04[0];
    } else {
        var_r31->unk_4C = var_r28->unk_04[1];
    }
    memset(&var_r31->unk_50, 0, 0x3C);
    var_r31->unk_8C = 0;
    var_r31->unk_90 = fn_1_48F0(lbl_1_data_0[var_r27].z);
    var_r31->unk_94 = -1;
    var_r31->unk_98 = 0.0f;
    var_r28->unk_0E[var_r31->unk_90] = var_r31->unk_04;
    var_r31->unk_A8 = fn_1_6248(&lbl_1_data_0[var_r27]);
    var_r31->unk_AC = 0;
    object->trans.x = lbl_1_data_0[var_r27].x;
    object->trans.y = lbl_1_data_0[var_r27].y;
    object->trans.z = lbl_1_data_0[var_r27].z;
    var_r25 = CharModelCreate(var_r31->unk_0C, 4);
    object->model[0] = var_r25;
    Hu3DModelLayerSet(object->model[0], 2);
    Hu3DModelShadowSet(object->model[0]);
    CharModelStepTypeSet(var_r31->unk_0C, 0);
    for (var_r29 = 0; var_r29 < 12; var_r29++) {
        if (lbl_1_data_170[var_r29].unk_04 == -1) {
            if ((var_r29 == 11) && (var_r31->unk_0C == 4)) {
                object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_0C, DATA_MAKE_NUM(DATADIR_MARIOMOT, 114));
            } else {
                object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_0C, lbl_1_data_170[var_r29].unk_00);
            }
            if (var_r29 == 5) {
                CharModelVoiceEnableSet(var_r31->unk_0C, object->motion[var_r29], 0);
            }
        } else {
            object->motion[var_r29] = Hu3DJointMotion(
                object->model[0], HuDataSelHeapReadNum(var_r31->unk_0C + lbl_1_data_1D0[lbl_1_data_170[var_r29].unk_04], 268435456, HEAP_DATA));
        }
    }
    CharModelMotionDataClose(var_r31->unk_0C);
    CharModelMotionSet(var_r31->unk_0C, object->motion[var_r31->unk_28]);
    Hu3DModelAttrSet(var_r25, 0x40000001);
    HuDataDirClose(lbl_1_data_110[var_r26] & 0xFFFF0000);
    object->func = NULL;
}

void fn_1_16F8(omObjData *object)
{
    s32 spA8[3];
    void *sp28;
    GXColor sp24;
    float sp20;
    float sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    GXColor spC;

    float var_f31;
    float var_f30;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f22;
    float var_f21;

    UnkM426Struct2 *var_r31;
    s32 var_r29;
    UnkM426Struct2 *var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21; // this is weird, used as a temporary

    sp18 = 0;
    sp14 = 0;
    var_r31 = object->data;
    var_r28 = var_r31->unk_4C->data;
    sp28 = lbl_1_bss_8C[var_r31->unk_00]->data;
    var_r24 = object->model[0];
    if (omPauseChk()) {
        Hu3DModelTPLvlSet(var_r24, 1.0f);
        return;
    }
    if (var_r31->unk_14) {
        sp20 = sp1C = 0.0f;
        sp10 = var_r21 = 0;
        fn_1_2F5C(object, &sp20, &sp1C, &sp10);
    } else {
        sp20 = HuPadStkX[var_r31->unk_10];
        sp1C = HuPadStkY[var_r31->unk_10];
        var_r21 = HuPadBtn[var_r31->unk_10];
        sp10 = HuPadBtnDown[var_r31->unk_10];
    }
    var_f30 = var_f31 = 0.0f;
    var_r27 = var_r25 = -1;
    var_f22 = object->trans.x;
    var_f21 = object->trans.z;
    if (!lbl_1_bss_60) {
        switch (var_r31->unk_24) {
            case 0:
            case 1:
                if (var_r31->unk_90 == -1) {
                    var_r31->unk_90 = fn_1_48F0(object->trans.z);
                } else {
                    if (!lbl_1_bss_40) {
                        sp20 = sp1C = 0.0f;
						
                        sp10 = var_r21 = 0;
                    }
                    if (fabs(sp20) > 8.0) {
                        var_f30 = 0.25f * sp20;
                    }
                    if (fabs(sp1C) > 8.0) {
                        var_f31 = -(0.25f * sp1C);
                    }
                    if (var_r31->unk_3C) {
                        var_r31->unk_3C--;
                    }
                    if (var_r31->unk_94 != -1) {
                        var_f27 = 16.0f;
                    } else {
                        var_f27 = 0.0f;
                    }
                    var_r31->unk_50[var_r31->unk_8C] = var_f27;
                    if (++var_r31->unk_8C >= 15) {
                        var_r31->unk_8C = 0;
                    }
                    for (var_r29 = 0, var_f28 = 0.0f; var_r29 < 15; var_r29++) {
                        var_f28 += var_r31->unk_50[var_r29];
                    }
                    var_f28 *= 0.06666667f;
                    if (var_r31->unk_98 != 0.0f) {
                        var_r26 = 3;
                    } else if (var_f28 <= 0.0f) {
                        if (lbl_1_bss_54 == 5) {
                            var_r26 = 8;
                        } else {
                            var_r26 = 0;
                        }
                    } else if (var_f28 < 10.0f) {
                        var_r26 = 1;
                    } else {
                        var_r26 = 2;
                    }
                    if (var_r26 != var_r31->unk_28) {
                        var_r31->unk_28 = var_r26;
                        if (var_r26 == 3) {
                            CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_28], 0.0f, 8.0f, 0);
                        } else {
                            CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_28], 0.0f, 8.0f, 0x40000001);
                        }
                    }
                    if (var_r31->unk_94 == -1) {
                        if (fabs(var_f31) > 2.0) {
                            if (var_f31 < 0.0f) {
                                var_r27 = var_r31->unk_90 - 1;
                                var_r25 = var_r31->unk_90 - 2;
                            } else {
                                var_r27 = var_r31->unk_90 + 1;
                                var_r25 = var_r31->unk_90 + 2;
                            }
                            if ((var_r27 >= 0) && (var_r27 < 6)
                                && (((var_r28->unk_90 != var_r27) && (var_r28->unk_94 != var_r27))
                                    || ((var_r28->unk_90 == var_r27) && (var_r28->unk_94 == var_r25) && (var_r25 >= 0) && (var_r25 < 6))
                                    || ((var_r28->unk_98 != 0.0f) && (var_r28->unk_90 == var_r27)))) {
                                var_r31->unk_94 = var_r27;
                            }
                        }
                    }
                    if (var_r31->unk_98 != 0.0f) {
                        object->trans.y = object->trans.y + var_r31->unk_98;
                        var_r31->unk_98 -= 3.103333333333333;
                        if (object->trans.y <= 0.0f) {
                            var_r31->unk_98 = 0.0f;
                            object->trans.y = 0.0f;
                        }
                    }
                    if (var_r31->unk_94 != -1) {
                        var_f25 = var_r31->unk_40;
                        var_f24 = fn_1_4A68(var_r31->unk_94);
                        var_f30 = var_f25 - object->trans.x;
                        var_f31 = var_f24 - object->trans.z;

                        var_f27 = sqrtf((var_f30 * var_f30) + (var_f31 * var_f31));

                        if (var_f27 <= var_f28) {
                            var_r31->unk_90 = var_r31->unk_94;
                            var_r31->unk_94 = -1;
                            if (var_r31->unk_3C) {
                                sp10 |= 256;
                            }
                            var_r31->unk_3C = 0;
                            object->trans.x = var_f25;
                            object->trans.z = var_f24;
                        } else if (var_f27 != 0.0f) {
                            var_f27 = 1.0f / var_f27;
                            object->trans.x += var_f28 * (var_f30 * var_f27);
                            object->trans.z += var_f28 * (var_f31 * var_f27);
                        }
                    }
                    var_f30 = object->trans.x - var_f22;
                    var_f31 = object->trans.z - var_f21;
                    if (fabs(var_f30) > 8.0 || fabs(var_f31) > 8.0) {
                        var_f26 = atan2d(var_f30, var_f31);
                    } else {
                        if (fabs(sp20) > 8.0 || fabs(sp1C) > 8.0) {
                            var_f26 = atan2d(sp20, -sp1C);
                            var_f26 = var_f26;
                        } else {
                            var_f26 = object->rot.y;
                        }
                    }
                    object->rot.y = fn_1_770C(var_f26, object->rot.y, 20.0f);
                    if (var_r31->unk_94 == -1 && var_r31->unk_98 == 0.0f) {
                        if (sp10 & 256) {
                            var_r31->unk_2C = 0;
                            var_r31->unk_24 = 2;
                            var_r31->unk_28 = 9;
                            CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_28], 8.0f, 8.0f, 0);
                        }
                    } else if (sp10 & 256) {
                        var_r31->unk_3C = 20;
                    }
                }
                break;
            case 2:
                object->rot.y = fn_1_770C(var_r31->unk_44, object->rot.y, 20.0f);
                var_r31->unk_2C++;
                if (var_r31->unk_2C == 17) {
                    lbl_1_bss_C.x = object->trans.x;
                    lbl_1_bss_C.y = object->trans.y;
                    lbl_1_bss_C.z = object->trans.z;
                    if (fn_1_4AF4(&lbl_1_bss_C, object->rot.y, 1)) {
                        if (!var_r31->unk_00) {
                            HuAudFXPlay(1601);
                        } else {
                            HuAudFXPlay(1602);
                        }
                    }
                } else if (var_r31->unk_2C >= 20) {
                    var_r31->unk_24 = 0;
                    var_r31->unk_2C = 0;
                    var_r31->unk_28 = 8;
                    CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_28], 0.0f, 8.0f, 0x40000001);
                }
                break;
            case 3:
                object->rot.y = fn_1_770C(var_r31->unk_44, object->rot.y, 20.0f);
                object->trans.x += 4.0f * var_r31->unk_9C.x;
                object->trans.z += 4.0f * var_r31->unk_9C.z;
                object->trans.y += var_r31->unk_9C.y;
                var_r31->unk_9C.y -= 3.103333333333333;
                if ((object->rot.x -= 30.0f) <= 0.0f) {
                    object->rot.y += 360.0f;
                }
                if (fabs(object->trans.x) > 750.0) {
                    if (object->trans.x > 0.0f) {
                        object->trans.x = 750.0f;
                    } else {
                        object->trans.x = -750.0f;
                    }
                }
                if (object->trans.y <= 0.0f) {
                    HuAudCharVoicePlay(var_r31->unk_0C, 281);
                    var_r31->unk_9C.x = var_r31->unk_9C.z = 0.0f;
                    var_r31->unk_9C.y = 28.0f;
                    object->trans.y = 0.0f;
                    object->rot.x = 0.0f;
                    var_r31->unk_24 = 5;
                }
                break;
            case 5:
                object->trans.y += var_r31->unk_9C.y;
                var_r31->unk_9C.y -= 3.103333333333333;
                if (object->trans.y <= 0.0f) {
                    object->trans.y = 0.0f;
                    var_r31->unk_9C.y = 0.0f;
                    var_r31->unk_24 = 6;
                    var_r31->unk_2C = 0;
                    HuAudCharVoicePlay(var_r31->unk_0C, 281);
                    var_r31->unk_28 = 6;
                    CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_28], 0.0f, 8.0f, 0x40000001);
                }
                break;
            case 6:
                var_r31->unk_2C++;
                if (var_r31->unk_2C < 60.0f) {
                    if (lbl_1_bss_40 == 0) {
                        var_r31->unk_2C = 59;
                    }
                } else if (var_r31->unk_2C == 60.0f) {
                    var_r31->unk_28 = 7;
                    CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_28], 0.0f, 8.0f, 0);
                } else if (var_r31->unk_2C >= 90.0f) {
                    var_r31->unk_24 = 7;
                    var_r31->unk_28 = 8;
                    CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_28], 0.0f, 8.0f, 0x40000001);
                }
                break;
            case 7:
                var_r27 = fn_1_48F0(object->trans.z);
                spA8[0] = var_r27;
                spA8[1] = var_r27 + 1;
                spA8[2] = var_r27 - 1;
                if (spA8[1] >= 6) {
                    spA8[1] = var_r27 - 2;
                }
                if (spA8[2] < 0) {
                    spA8[2] = var_r27 + 2;
                }
                for (var_r29 = 0, var_r31->unk_94 = -1; var_r29 < 3; var_r29++) {
                    if (var_r28->unk_90 != spA8[var_r29] && var_r28->unk_94 != spA8[var_r29] && spA8[var_r29] >= 0 && spA8[var_r29] < 6) {
                        var_r31->unk_94 = spA8[var_r29];
                        break;
                    }
                }
                if (var_r31->unk_94 != -1) {
                    var_r31->unk_24 = 1;
                    var_r31->unk_2C = 0;
                }
                break;
            case 8:
            case 9:
                object->rot.y = fn_1_770C(0.0f, object->rot.y, 10.0f);
                if (var_r31->unk_24 == 8) {
                    var_r26 = 10;
                } else {
                    var_r26 = 11;
                }
                if (var_r26 != var_r31->unk_28) {
                    var_r31->unk_28 = var_r26;
                    CharModelMotionShiftSet(var_r31->unk_0C, object->motion[var_r31->unk_28], 0.0f, 8.0f, 0);
                }
                break;
        }
        if (var_r31->unk_AC) {
            var_r31->unk_AC--;
        }
        var_r22 = var_r31->unk_AC / 2;
        if (var_r22 > 16) {
            var_r22 = 16;
        }
        for (var_r29 = 0; var_r29 < var_r22; var_r29++) {
            lbl_1_bss_C.y = object->trans.y + ((frand() % 70) + 35);
            lbl_1_bss_C.x = object->trans.x + ((frand() % 50) + 25);
            lbl_1_bss_C.z = object->trans.z + ((frand() % 50) + 25);
            lbl_1_bss_0.x = 0.0f;
            lbl_1_bss_0.z = 0.0f;
            lbl_1_bss_0.y = 0.0f;

            var_r23 = (frand() & 63) + 128;

            sp24.r = var_r23;
            sp24.g = var_r23;
            sp24.b = var_r23;
            sp24.a = 64;

            fn_1_63B8(var_r31->unk_A8, &lbl_1_bss_C, NULL, 100.0f, sp24);
        }
        if (var_r31->unk_30) {
            if (++var_r31->unk_38 > 1) {
                var_r31->unk_38 = 0;
                var_r31->unk_34 = var_r31->unk_34 ^ 1;
            }
        }
        if (((var_r21 = var_r31->unk_24) == 0 || var_r31->unk_24 == 1 || var_r31->unk_24 == 2) && var_r31->unk_30) {
            if (var_r31->unk_30) {
                var_r31->unk_30 = var_r31->unk_30 - 1;
            }
            if (var_r31->unk_34) {
                Hu3DModelTPLvlSet(var_r24, 0.25f);
                return;
            }
            Hu3DModelTPLvlSet(var_r24, 1.0f);
            return;
        }
        Hu3DModelTPLvlSet(var_r24, 1.0f);
    }
}

Vec lbl_1_data_200[2] = {
    { -473.71, 432.536, -569.82 },
    { 473.71, 432.536, -569.82 },
};

s32 lbl_1_data_218[2] = { 6357019, 6357020 };

s16 lbl_1_data_220[6] = { 11, 31, 0, 0, -33, -9 };

Vec lbl_1_data_22C[4] = {
    { -0.5f, 0.5f, 0.0f },
    { 0.5f, 0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f },
};

Vec2f lbl_1_data_25C[4] = {
    { 0.0f, 0.0f },
    { 0.25f, 0.0f },
    { 0.25f, 0.25f },
    { 0.0f, 0.25f },
};

s32 lbl_1_data_27C[] = {
    0xC2480000,
    0x42480000,
    0x00000000,
    0x42480000,
    0x42480000,
    0x00000000,
    0x42480000,
    0xC2480000,
    0x00000000,
    0xC2480000,
    0xC2480000,
    0x00000000,
};

s32 lbl_1_data_2AC[] = {
    0xFFFFA080,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
};

s32 lbl_1_data_2BC[] = {
    0x00000000,
    0x00000000,
    0x3F800000,
    0x00000000,
    0x3F800000,
    0x3F800000,
    0x00000000,
    0x3F800000,
};

void fn_1_2AC8(omObjData *object)
{
    object->data = NULL;
    object->func = NULL;
}

void fn_1_2ADC(void)
{
    omObjData *var_r31;
    s32 var_r30;
    s32 var_r29;
    UnkM426Struct *var_r27;
    omObjData *var_r28;

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        var_r31 = lbl_1_bss_8C[var_r30];
        var_r27 = var_r31->data;
        for (var_r29 = 0; var_r29 < 2; var_r29++) {
            var_r28 = var_r27->unk_04[var_r29];
            var_r28->data = 0;
            var_r28->func = 0;
        }
        var_r31->data = NULL;
        var_r31->func = NULL;
    }
}

void fn_1_2B74(Vec *arg0)
{
    Vec spC;
    void *sp8;

    UnkM426Struct2 *var_r31;
    omObjData *var_r30;
    UnkM426Struct *var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    if (arg0->x < 0.0f) {
        var_r26 = 0;
    } else {
        var_r26 = 1;
    }
    if (lbl_1_bss_8C[var_r26]) {
        var_r29 = lbl_1_bss_8C[var_r26]->data;
        if (var_r29) {
            for (var_r28 = 0; var_r28 < 2; var_r28++) {
                var_r30 = var_r29->unk_04[var_r28];
                var_r31 = var_r30->data;
                sp8 = var_r31->unk_4C->data;
                if (var_r31 && var_r31->unk_24 <= 2) {
                    if (fabs(var_r30->trans.z - arg0->z) < 140.0 && !var_r31->unk_30) {
                        var_r31->unk_2C = 0;
                        var_r31->unk_24 = 3;
                        var_r31->unk_AC = 32;
                        var_r31->unk_30 = 90;
                        var_r31->unk_90 = var_r31->unk_94 = -1;
                        if (!var_r29->unk_00) {
                            var_r31->unk_9C.x = -1.0f;
                        } else {
                            var_r31->unk_9C.x = 1.0f;
                        }
                        if (fabs(var_r31->unk_4C->trans.z - var_r30->trans.z) < 100.0) {
                            var_r31->unk_90 = fn_1_48F0(var_r30->trans.z);
                            if (var_r31->unk_90 == 5) {
                                var_r31->unk_9C.z = -1.0f;
                            } else if (!var_r31->unk_90) {
                                var_r31->unk_9C.z = 1.0f;
                            } else if ((var_r31->unk_4C->trans.z - var_r30->trans.z) < 0.0f) {
                                var_r31->unk_9C.z = 1.0f;
                            } else {
                                var_r31->unk_9C.z = -1.0f;
                            }
                        } else {
                            var_r31->unk_9C.z = 0.0f;
                        }
                        var_r31->unk_9C.y = 45.5f;
                        var_r31->unk_28 = 5;
                        CharModelMotionShiftSet(var_r31->unk_0C, var_r30->motion[var_r31->unk_28], 0.0f, 8.0f, 0);
                        spC.x = var_r30->trans.x;
                        spC.y = var_r30->trans.y;
                        spC.z = var_r30->trans.z;
                        fn_1_6310(var_r31->unk_A8, &spC);
                        var_r27 = HuAudFXPlay(1606);
                        if (var_r27 != -1) {
                            HuAudFXPanning(var_r27, var_r29->unk_00 * 64 + 32);
                        }
                        HuAudCharVoicePlay(var_r31->unk_0C, 291);
                        if (var_r27 != -1) {
                            HuAudFXPanning(var_r27, var_r29->unk_00 * 64 + 32);
                        }
                    }
                }
            }
        }
    }
}

s32 fn_1_2EDC(void)
{
    UnkM426Struct2 *var_r31;
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r31 = lbl_1_bss_7C[var_r30]->data;
        if ((var_r31->unk_24 != 0 && var_r31->unk_24 != 1) || var_r31->unk_94 != -1) {
            break;
        }
    }
    if (var_r30 < 4) {
        return 0;
    }
    return 1;
}

void fn_1_2F5C(omObjData *object, float *arg1, float *arg2, s32 *arg3)
{
    s32 sp14[6];
    s32 spC[2];
    UnkM426Struct *sp8;

    float var_f31;

    UnkM426Struct2 *var_r31;
    s32 var_r30;
    s32 var_r29;
    UnkM426Struct2 *var_r28;
    s32 var_r27;
    s32 var_r26;
    omObjData *var_r24;
    UnkM426Struct *var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;

    var_r27 = 0;
    var_r22 = 0;
    var_r31 = object->data;
    var_r28 = var_r31->unk_4C->data;
    sp8 = lbl_1_bss_8C[var_r31->unk_00]->data;

    var_r23 = lbl_1_bss_8C[var_r31->unk_00 ^ 1]->data;
    var_r24 = var_r23->unk_04[0];
    spC[0] = fn_1_48F0(var_r24->trans.z);
    var_r24 = var_r23->unk_04[1];
    spC[1] = fn_1_48F0(var_r24->trans.z);
    var_r29 = var_r28->unk_90;

    if (var_r29 == -1) {
        var_r29 = var_r28->unk_94;
    }
    if (lbl_1_bss_54 == 5) {
        if (var_r31->unk_24 != 0 && var_r31->unk_24 != 1 && var_r31->unk_24 != 2) {
            var_r22 = 1;
        }
        if (var_r31->unk_B0 != -1 && var_r29 != -1
            && ((var_r29 <= var_r31->unk_90 && var_r31->unk_B0 <= var_r29) || (var_r29 >= var_r31->unk_90 && var_r31->unk_B0 >= var_r29))) {
            var_r22 = 1;
        }
        if (var_r22) {
            var_r31->unk_B0 = -1;
            var_r31->unk_B8 = 0;
            var_r31->unk_B4 = 0;
            var_r31->unk_BC = 3;
            return;
        }
        switch (var_r31->unk_BC) {
            case 0:
                if (var_r31->unk_24 != 0 && var_r31->unk_24 != 1 && var_r31->unk_24 != 2) {
                    var_r31->unk_B8 = 0;
                }
                if (--var_r31->unk_B8 <= 0) {
                    var_r31->unk_B8 = 0;
                    var_r31->unk_B4 = 0;
                    var_r31->unk_BC = 3;
                    return;
                }
                break;
            case 1:
                if (var_r31->unk_B0 != -1) {
                    if (++var_r31->unk_B4 < 120.0f) {
                        if (var_r31->unk_90 == var_r31->unk_B0) {
                            var_r31->unk_B0 = -1;
                            return;
                        }
                        if (var_r31->unk_90 < var_r31->unk_B0) {
                            *arg2 = -64.0f;
                            return;
                        }
                        *arg2 = 64.0f;
                        return;
                    }
                }
                var_r31->unk_B8 = 0;
                var_r31->unk_B4 = 0;
                var_r31->unk_BC = 3;
                return;
            case 2:
                if (var_r31->unk_B0 != -1) {
                    if (++var_r31->unk_B4 < 120.0f && var_r31->unk_B0 != var_r28->unk_B0) {
                        if (var_r31->unk_90 == var_r31->unk_B0) {
                            *arg3 |= 256;
                            var_r31->unk_B0 = -1;
                            var_r31->unk_B4 = 0;
                            var_r31->unk_B8 = (50.0f + (frand() % 15)) - (var_r31->unk_18 * 10);
                            var_r31->unk_BC = 0;
                            return;
                        }
                        if (var_r31->unk_90 < var_r31->unk_B0) {
                            *arg2 = -64.0f;
                            return;
                        }
                        *arg2 = 64.0f;
                        return;
                    }
                    var_r31->unk_B0 = -1;
                    var_r31->unk_B4 = 0;
                    return;
                }
                var_r31->unk_B8 = 0;
                var_r31->unk_B4 = 0;
                var_r31->unk_BC = 3;
                return;
            case 3:
                var_r31->unk_B0 = -1;
                if (var_r29 == -1) {
                    for (var_r30 = 0; var_r30 < 6; var_r27++, var_r30++) {
                        sp14[var_r27] = var_r30;
                    }
                } else {
                    if (var_r31->unk_90 < var_r29) {
                        for (var_r30 = 0; var_r30 < 3; var_r27++, var_r30++) {
                            sp14[var_r27] = var_r30;
                        }
                    } else {
                        for (var_r30 = 3; var_r30 < 6; var_r27++, var_r30++) {
                            sp14[var_r27] = var_r30;
                        }
                    }
                    if (var_r31->unk_18 < var_r28->unk_18) {
                        for (var_r30 = 0; var_r30 < 6; var_r30++) {
                            if (sp14[var_r30] == 3) {
                                sp14[var_r30] = -1;
                            }
                        }
                    }
                }
                for (var_r30 = 0, var_r21 = 256; var_r30 < var_r27; var_r30++) {
                    if (sp14[var_r30] >= 0) {
                        var_r20 = fn_1_4894(sp14[var_r30]);
                        if (var_r20 != var_r31->unk_00) {
                            var_r26 = (frand() % 5) - var_r31->unk_18;
                            if (var_r26 < 0) {
                                var_r26 = 0;
                            }
                            var_r26 += (s32)fabs(var_r28->unk_90 - var_r31->unk_B0);
                            if (spC[0] == sp14[var_r30] || spC[1] == sp14[var_r30]) {
                                var_r26 += var_r31->unk_18 * 2;
                            }
                            if (var_r21 > var_r26) {
                                var_r31->unk_B0 = sp14[var_r30];
                                var_r21 = var_r26;
                            }
                        }
                    }
                }
                if (var_r31->unk_B0 == -1) {
                    if (var_r29 == -1) {
                        if (var_r31->unk_90 < 3) {
                            var_r31->unk_B0 = 1;
                        } else {
                            var_r31->unk_B0 = 4;
                        }
                    } else if (var_r29 > var_r31->unk_90) {
                        var_r31->unk_B0 = 1;
                    } else {
                        var_r31->unk_B0 = 4;
                    }
                    var_r31->unk_BC = 1;
                } else {
                    var_r31->unk_BC = 2;
                }
                var_r31->unk_B8 = 0;
                var_r31->unk_B4 = 0;
                break;
        }
    }
}

void fn_1_3654(s32 arg0)
{
    omVibrate(lbl_1_bss_18[arg0 * 2], 12, 6, 6);
    omVibrate(lbl_1_bss_18[arg0 * 2 + 1], 12, 6, 6);
}

void fn_1_36C4(void)
{
    lbl_1_bss_78 = omAddObjEx(lbl_1_bss_98, 64, 14, 0, -1, fn_1_3714);
}

void fn_1_3714(omObjData *object)
{
    Vec sp8;

    UnkM426Struct3 *var_r31;
    s32 var_r29;
    UnkM426Struct3 *var_r28;
    s32 var_r27;
    ModelData *var_r26;
    s32 var_r25;

    var_r31 = var_r28 = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 6 * sizeof(UnkM426Struct3), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 6 * sizeof(UnkM426Struct3));
    lbl_1_bss_30 = 0;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 2));
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 3));
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 20));
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 21));
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 11));
    object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 12));
    object->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 13));
    object->model[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 22));
    object->model[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 14));
    object->model[9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 15));
    object->model[10] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 16));
    object->model[11] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 17));
    object->model[12] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 18));
    object->model[13] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 19));
    Hu3DModelAttrSet(object->model[4], 1);
    Hu3DModelAttrSet(object->model[5], 1);
    Hu3DModelAttrSet(object->model[6], 1);
    Hu3DModelAttrSet(object->model[8], 1);
    Hu3DModelAttrSet(object->model[9], 1);
    Hu3DModelAttrSet(object->model[11], 1);
    Hu3DModelAttrSet(object->model[13], 1);
    for (var_r29 = 0; var_r29 < 14; var_r29++) {
        Hu3DModelLayerSet(object->model[var_r29], 2);
    }
    Hu3DModelShadowMapSet(object->model[0]);
    Hu3DModelShadowMapSet(object->model[1]);
    object->work[0] = 0;
    object->work[1] = 0;
    object->work[2] = 0;
    object->work[3] = 0;
    for (var_r29 = 0; var_r29 < 6; var_r29++, var_r31++) {
        var_r31->unk_00 = var_r29;
        var_r31->unk_04 = -1;
        var_r31->unk_08 = var_r29 & 1;
        var_r31->unk_0C = 0;
        if (var_r29 == 0) {
            var_r31->unk_10 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 23));
            Hu3DModelShadowMapSet(var_r31->unk_10);
            var_r31->unk_14 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 5));
            var_r31->unk_18 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 4));
            var_r31->unk_1C = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 7));
            var_r31->unk_20 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 6));
            var_r31->unk_24 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 8));
            var_r31->unk_28 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 9));
        } else {
            var_r31->unk_10 = Hu3DModelLink(var_r28->unk_10);
            Hu3DModelShadowMapSet(var_r31->unk_10);
            var_r31->unk_14 = Hu3DModelLink(var_r28->unk_14);
            var_r31->unk_18 = Hu3DModelLink(var_r28->unk_18);
            var_r31->unk_1C = Hu3DModelLink(var_r28->unk_1C);
            var_r31->unk_20 = Hu3DModelLink(var_r28->unk_20);
            var_r31->unk_24 = Hu3DModelLink(var_r28->unk_24);
            var_r31->unk_28 = Hu3DModelLink(var_r28->unk_28);
        }
        Hu3DModelLayerSet(var_r31->unk_10, 2);
        Hu3DModelLayerSet(var_r31->unk_14, 4);
        Hu3DModelLayerSet(var_r31->unk_18, 4);
        Hu3DModelLayerSet(var_r31->unk_1C, 2);
        Hu3DModelLayerSet(var_r31->unk_20, 2);
        Hu3DModelLayerSet(var_r31->unk_24, 2);
        Hu3DModelLayerSet(var_r31->unk_28, 2);
        var_r31->unk_34 = -1;
        var_r31->unk_38 = -425.0f + (140.0f * var_r29);
        Hu3DModelPosSet(var_r31->unk_10, 0.0f, 50.0f, var_r31->unk_38);
        Hu3DModelPosSet(var_r31->unk_14, 0.0f, 50.0f, var_r31->unk_38);
        Hu3DModelPosSet(var_r31->unk_18, 0.0f, 50.0f, var_r31->unk_38);
        Hu3DModelPosSet(var_r31->unk_1C, -500.0f, 30.000002f, var_r31->unk_38);
        Hu3DModelPosSet(var_r31->unk_20, -500.0f, 50.0f, var_r31->unk_38);
        Hu3DModelPosSet(var_r31->unk_24, 500.0f, 50.0f, var_r31->unk_38);
        Hu3DModelPosSet(var_r31->unk_28, 500.0f, 30.000002f, var_r31->unk_38);
        fn_1_4738(var_r29, var_r31->unk_08);
        sp8.x = 0.0f;
        sp8.y = 500.0f;
        sp8.z = var_r31->unk_38;
        var_r25 = 0.3f * (var_r31->unk_00 * 60);
        var_r31->unk_34 = fn_1_5C6C(var_r31->unk_00, var_r25, &sp8);
    }
    lbl_1_bss_24 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M426, 1), MEMORY_DEFAULT_NUM));
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        var_r27 = Hu3DHookFuncCreate(fn_1_88B4);
        var_r26 = &Hu3DData[var_r27];
        var_r26->unk_120 = lbl_1_bss_24;
        Hu3DModelPosSetV(var_r27, &lbl_1_data_200[var_r29]);
        Hu3DModelScaleSet(var_r27, 4.0f, 4.0f, 4.0f);
        Hu3DModelLayerSet(var_r27, 4);
    }
    object->func = fn_1_3EFC;
}

void fn_1_3EFC(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f29;

    UnkM426Struct3 *var_r30;
    LightData *var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    var_r30 = object->data;
    for (var_r28 = 0; var_r28 < 6; var_r28++, var_r30++) {
        if (var_r30->unk_04 != -1) {
            var_r30->unk_0C++;
            var_f31 = 0.5f * var_r30->unk_0C;
            if (!var_r30->unk_04) {
                var_f29 = 30.000002f + (19.999998f * var_f31);
                var_f30 = 50.0f + (-19.999998f * var_f31);
                Hu3DModelPosSet(var_r30->unk_20, -500.0f, var_f30, var_r30->unk_38);
                Hu3DModelPosSet(var_r30->unk_28, 500.0f, var_f29, var_r30->unk_38);
            } else {
                var_f29 = 50.0f + (-19.999998f * var_f31);
                var_f30 = 30.000002f + (19.999998f * var_f31);
                Hu3DModelPosSet(var_r30->unk_1C, -500.0f, var_f30, var_r30->unk_38);
                Hu3DModelPosSet(var_r30->unk_24, 500.0f, var_f29, var_r30->unk_38);
            }
            if (var_r30->unk_0C >= 2) {
                if (var_r30->unk_04 == 0) {
                    HuAudFXPlay(1600);
                } else {
                    HuAudFXPlay(1599);
                }
                fn_1_4738(var_r28, var_r30->unk_04);
                var_r30->unk_04 = -1;
                var_r30->unk_0C = 0;
                Hu3DModelPosSet(var_r30->unk_1C, -500.0f, 30.000002f, var_r30->unk_38);
                Hu3DModelPosSet(var_r30->unk_20, -500.0f, 50.0f, var_r30->unk_38);
                Hu3DModelPosSet(var_r30->unk_24, 500.0f, 50.0f, var_r30->unk_38);
                Hu3DModelPosSet(var_r30->unk_28, 500.0f, 30.000002f, var_r30->unk_38);
            }
        }
    }
    Hu3DModelAttrSet(object->model[3], 1);
    Hu3DModelAttrSet(object->model[4], 1);
    Hu3DModelAttrSet(object->model[5], 1);
    Hu3DModelAttrSet(object->model[6], 1);
    Hu3DModelAttrSet(object->model[7], 1);
    Hu3DModelAttrSet(object->model[8], 1);
    Hu3DModelAttrSet(object->model[9], 1);
    Hu3DModelAttrSet(object->model[10], 1);
    Hu3DModelAttrSet(object->model[11], 1);
    Hu3DModelAttrSet(object->model[12], 1);
    Hu3DModelAttrSet(object->model[13], 1);

    if (lbl_1_bss_30) {
        if (++object->work[0] >= 20) {
            object->work[0] = 0;
        }
        if (++object->work[1] >= 15) {
            object->work[1] = 0;
        }
        if (++object->work[2] >= 20) {
            object->work[2] = 0;
        }
        lbl_1_bss_30--;
    } else {
        if (object->work[0]) {
            if (++object->work[0] >= 20) {
                object->work[0] = 0;
            }
        }
        if (object->work[1]) {
            if (++object->work[1] >= 15) {
                object->work[1] = 0;
            }
        }
        if (object->work[2]) {
            if (++object->work[2] >= 20) {
                object->work[2] = 0;
            }
        }
    }
    if (++object->work[3] >= 20) {
        object->work[3] = 0;
    }
    Hu3DModelAttrReset(object->model[(object->work[0] / 5) + 3], 1);
    Hu3DModelAttrReset(object->model[(object->work[1] / 5) + 7], 1);
    Hu3DModelAttrReset(object->model[(object->work[2] / 10) + 10], 1);
    Hu3DModelAttrReset(object->model[(object->work[3] / 10) + 12], 1);

    var_r29 = &Hu3DGlobalLight[lbl_1_bss_2C];
    var_r27 = lbl_1_data_48.r + (s32)(255.0f * lbl_1_bss_28);
    if (var_r27 > 255) {
        var_r27 = 255;
    }
    var_r26 = lbl_1_data_48.g + (s32)(255.0f * lbl_1_bss_28);
    if (var_r26 > 255) {
        var_r26 = 255;
    }
    var_r25 = lbl_1_data_48.b + (s32)(255.0f * lbl_1_bss_28);
    if (var_r25 > 255) {
        var_r25 = 255;
    }
    var_r24 = lbl_1_data_48.a + (s32)(255.0f * lbl_1_bss_28);
    if (var_r24 > 255) {
        var_r24 = 255;
    }

    var_r29->color.r = var_r27;
    var_r29->color.g = var_r26;
    var_r29->color.b = var_r25;
    var_r29->color.a = var_r24;

    if (lbl_1_bss_28 > 0.0f) {
        if ((lbl_1_bss_28 -= 0.05f) < 0.0f) {
            lbl_1_bss_28 = 0.0f;
        }
    }
}

void fn_1_45FC(omObjData *object)
{
    fn_1_8E10(lbl_1_bss_24);
    object->data = NULL;
    object->func = NULL;
}

void fn_1_4644(void)
{
    omObjData *var_r31;

    var_r31 = lbl_1_bss_78;
    fn_1_45FC(var_r31);
    lbl_1_bss_78 = NULL;
}

void fn_1_46A4(s32 arg0, s32 arg1)
{
    UnkM426Struct3 *var_r31;

    if (!lbl_1_bss_78 || arg0 < 0 || arg0 >= 6) {
        return;
    }
    var_r31 = lbl_1_bss_78->data;
    var_r31 = &var_r31[arg0];
    if (var_r31->unk_04 == -1) {
        if (var_r31->unk_08 != arg1) {
            var_r31->unk_04 = arg1;
        }
        var_r31->unk_0C = 0;
        return;
    }
    if (var_r31->unk_04 != arg1) {
        var_r31->unk_04 = arg1;
        var_r31->unk_0C = 0;
    }
}

void fn_1_4738(s32 arg0, s32 arg1)
{
    UnkM426Struct3 *var_r31;

    if (!lbl_1_bss_78 || arg0 < 0 || arg0 >= 6) {
        return;
    }
    var_r31 = lbl_1_bss_78->data;
    var_r31 = &var_r31[arg0];
    var_r31->unk_08 = arg1;
    switch (arg1) {
        case 0:
            Hu3DModelAttrReset(var_r31->unk_14, 1);
            Hu3DModelAttrReset(var_r31->unk_1C, 1);
            Hu3DModelAttrReset(var_r31->unk_24, 1);
            Hu3DModelAttrSet(var_r31->unk_18, 1);
            Hu3DModelAttrSet(var_r31->unk_20, 1);
            Hu3DModelAttrSet(var_r31->unk_28, 1);
            break;
        case 1:
            Hu3DModelAttrSet(var_r31->unk_14, 1);
            Hu3DModelAttrSet(var_r31->unk_1C, 1);
            Hu3DModelAttrSet(var_r31->unk_24, 1);
            Hu3DModelAttrReset(var_r31->unk_18, 1);
            Hu3DModelAttrReset(var_r31->unk_20, 1);
            Hu3DModelAttrReset(var_r31->unk_28, 1);
            break;
        default:
            break;
    }
}

s32 fn_1_4894(s32 arg0)
{
    UnkM426Struct3 *var_r31;

    if (!lbl_1_bss_78 || arg0 < 0 || arg0 >= 6) {
        return 0;
    }
    var_r31 = lbl_1_bss_78->data;
    var_r31 = &var_r31[arg0];
    return var_r31->unk_08;
}

s32 fn_1_48F0(float arg8)
{
    float var_f31;

    UnkM426Struct3 *var_r31;
    s32 var_r30;
    s32 var_r29;

    if (!lbl_1_bss_78) {
        return -1;
    }
    var_r31 = lbl_1_bss_78->data;
    if (!lbl_1_bss_78->data) {
        return -1;
    }
    var_f31 = fabs(var_r31->unk_38 - arg8);
    var_r29 = 0;
    var_r31++;
    for (var_r30 = 1; var_r30 < 6; var_r30++, var_r31++) {
        if (var_f31 > fabs(var_r31->unk_38 - arg8)) {
            var_f31 = fabs(var_r31->unk_38 - arg8);
            var_r29 = var_r30;
        }
    }
    return var_r29;
}

float fn_1_4A68(s32 arg0)
{
    UnkM426Struct3 *var_r31;

    if (!lbl_1_bss_78 || arg0 < 0 || arg0 >= 6) {
        return 0.0f;
    }
    var_r31 = lbl_1_bss_78->data;
    if (!lbl_1_bss_78->data) {
        return 0.0f;
    }
    return var_r31[arg0].unk_38;
}

s32 fn_1_4AF4(Vec *arg0, float arg8, s32 arg1)
{
    float var_f31;
    float var_f30;
    float var_f28;
    float var_f26;
    float var_f25;
    float var_f24;

    UnkM426Struct3 *var_r30;
    s32 var_r29;

    if (!lbl_1_bss_78) {
        return 0;
    }
    var_r30 = lbl_1_bss_78->data;
    if (arg0->x < 0.0f) {
        var_f28 = -500.0f;
    } else {
        var_f28 = 500.0f;
    }
    for (var_r29 = 0; var_r29 < 6; var_r29++, var_r30++) {
        var_f24 = var_r30->unk_38;
        var_f31 = var_f28 - arg0->x;
        var_f30 = var_f24 - arg0->z;

        var_f25 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
        var_f26 = atan2d(var_f31, var_f30);
        if (var_f25 < 150.0f && (fabs(fn_1_75F4(var_f26, arg8)) < 30.0f)) {
            break;
        }
    }
    if (var_r29 >= 6) {
        return 0;
    }
    if (arg0->x < 0.0f) {
        if (!var_r30->unk_08) {
            return 0;
        }
    } else if (var_r30->unk_08 == 1) {
        return 0;
    }
    if (arg1) {
        fn_1_46A4(var_r29, var_r30->unk_08 ^ 1);
    }
    return 1;
}

void fn_1_4EC4(void)
{
    lbl_1_bss_74 = omAddObjEx(lbl_1_bss_98, 64, 0, 0, -1, fn_1_4F14);
}

void fn_1_4F14(omObjData *object)
{
    UnkM426Struct4 *var_r31;
    UnkM426Struct4 *var_r30;
    s32 var_r29;

    var_r31 = var_r30 = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 6 * sizeof(UnkM426Struct4), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 6 * sizeof(UnkM426Struct4));
    for (var_r29 = 0; var_r29 < 6; var_r29++, var_r31++) {
        if (var_r29 == 0) {
            var_r31->unk_00 = Hu3DModelCreateFile(3735579);
        } else {
            var_r31->unk_00 = Hu3DModelLink(var_r30->unk_00);
        }
        Hu3DModelShadowSet(var_r31->unk_00);
        Hu3DModelLayerSet(var_r31->unk_00, 2);
        if (var_r29 == 0) {
            var_r31->unk_08 = Hu3DJointMotion(var_r31->unk_00, HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M426, 28), MEMORY_DEFAULT_NUM, HEAP_DATA));
            var_r31->unk_0C = Hu3DJointMotion(var_r31->unk_00, HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M426, 29), MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            var_r31->unk_08 = var_r30->unk_08;
            var_r31->unk_0C = var_r30->unk_0C;
        }
        var_r31->unk_18 = var_r31->unk_1C = 2;
        var_r31->unk_38 = 0;
        var_r31->unk_20 = var_r29;
        var_r31->unk_24 = -1;
        var_r31->unk_28 = 5;
        var_r31->unk_2C = 0;
        var_r31->unk_30 = 0;
        var_r31->unk_34 = 0.0f;
        var_r31->unk_3C = var_r31->unk_40 = var_r31->unk_44 = 0.0f;
        var_r31->unk_48 = 0.0f;
        var_r31->unk_4C = 0.0f;
        Hu3DModelAttrSet(var_r31->unk_00, 1);
        Hu3DModelScaleSet(var_r31->unk_00, 0.8f, 0.8f, 0.8f);
    }
    object->func = fn_1_5134;
}

void fn_1_5134(omObjData *object)
{
    Vec sp8;

    float var_f31;

    UnkM426Struct4 *var_r31;
    s32 var_r27;
    s32 var_r26;

    var_r31 = object->data;
    for (var_r27 = 0; var_r27 < 6; var_r27++, var_r31++) {
        var_r26 = fn_1_4894(var_r31->unk_24);
        switch (var_r31->unk_28) {
            case 0:
                if (lbl_1_bss_38) {
                    if (--var_r31->unk_2C <= 0) {
                        if (!var_r31->unk_38) {
                            Hu3DModelAttrReset(var_r31->unk_00, 1);
                        }
                        Hu3DMotionSet(var_r31->unk_00, var_r31->unk_08);
                        Hu3DModelAttrSet(var_r31->unk_00, 1073741825);
                        HuAudFXPlay(1607);
                        var_r31->unk_2C = 0;
                        var_r31->unk_28 = 1;
                    }
                }
                break;
            case 1:
                if ((var_r31->unk_40 -= 50.0f) <= 50.0f) {
                    if (lbl_1_bss_54 <= 4) {
                        fn_1_3654(0);
                        fn_1_3654(1);
                    }
                    HuAudFXPlay(1598);
                    var_r31->unk_40 = 50.0f;
                    var_r31->unk_30 = 0;
                    var_r31->unk_28 = 2;
                }
                break;
            case 2:
                if (lbl_1_bss_3C) {
                    var_r31->unk_30 = 0;
                    var_r31->unk_28 = 3;
                    Hu3DMotionShiftSet(var_r31->unk_00, var_r31->unk_0C, 0.0f, 8.0f, 0x40000001);
                } else {
                    var_r31->unk_48 = fn_1_770C(0.0f, var_r31->unk_48, 10.0f);
                }
                break;
            case 3:
                if (!var_r26) {
                    var_f31 = 90.0f;
                } else {
                    var_f31 = 270.0f;
                }
                if (fabs(fn_1_75F4(var_f31, var_r31->unk_48)) < 5.0) {
                    var_r31->unk_48 = var_f31;
                    if ((var_r31->unk_34 += 0.1f) > lbl_1_bss_34) {
                        var_r31->unk_34 = lbl_1_bss_34;
                    }
                } else {
                    var_r31->unk_48 = fn_1_770C(var_f31, var_r31->unk_48, 10.0f);
                    if ((var_r31->unk_34 -= 0.1f) < 0.0f) {
                        var_r31->unk_34 = 0.0f;
                    }
                }
                if (var_r31->unk_34 > 0.0f) {
                    var_r31->unk_3C = var_r31->unk_3C + (var_r31->unk_34 * sind(var_r31->unk_48));
                }
                Hu3DMotionSpeedSet(var_r31->unk_00, 1.4f * (0.33333334f * var_r31->unk_34));
                if (lbl_1_bss_3C == 0) {
                    Hu3DMotionShiftSet(var_r31->unk_00, var_r31->unk_08, 0.0f, 8.0f, 1073741825);
                    var_r31->unk_2C = 0;
                    var_r31->unk_30 = 0;
                    var_r31->unk_28 = 2;
                }
                if (fabs(var_r31->unk_3C) >= 400.0) {
                    var_r31->unk_34 = 0.0f;
                    if (var_r31->unk_3C > 0.0f) {
                        var_r31->unk_3C = 399.0f;
                    } else {
                        var_r31->unk_3C = -399.0f;
                    }
                    var_r31->unk_18 = 0;
                    sp8.x = var_r31->unk_3C;
                    sp8.y = var_r31->unk_40;
                    sp8.z = var_r31->unk_44;
                    fn_1_6888(&sp8);
                    if (var_r31->unk_3C < 0.0f) {
                        lbl_1_bss_1C[0]--;
                        fn_1_3654(0);
                        HuAudFXPlay(1603);
                    } else {
                        lbl_1_bss_1C[1]--;
                        fn_1_3654(1);
                        HuAudFXPlay(1604);
                    }
                    if (lbl_1_bss_1C[0] < 0) {
                        lbl_1_bss_1C[0] = 0;
                    }
                    if (lbl_1_bss_1C[1] < 0) {
                        lbl_1_bss_1C[1] = 0;
                    }
                    lbl_1_bss_30 = 60;
                    lbl_1_bss_28 = 1.0f;
                    var_r31->unk_30 = 0;
                    var_r31->unk_28 = 4;
                }
                break;
            case 4:
                if (++var_r31->unk_30 >= 20) {
                    sp8.x = var_r31->unk_3C;
                    sp8.y = var_r31->unk_40;
                    sp8.z = var_r31->unk_44;

                    fn_1_2B74(&sp8);
                    if (var_r31->unk_3C < 0.0f) {
                        fn_1_46A4(var_r31->unk_24, 0);
                    } else {
                        fn_1_46A4(var_r31->unk_24, 1);
                    }
                    var_r31->unk_28 = 5;

                    if (var_r26 == 0) {
                        var_r31->unk_4C += 30.000002f;
                    } else {
                        var_r31->unk_4C -= 30.000002f;
                    }
                    if (fabs(var_r31->unk_4C) > 150.0) {
                        if (!var_r26) {
                            var_r31->unk_4C = 150.0f;
                        } else {
                            var_r31->unk_4C = -150.0f;
                        }
                    }
                    sp8.x = var_r31->unk_4C;
                    sp8.y = 500.0f;
                    sp8.z = var_r31->unk_44;
                    fn_1_5C6C(var_r31->unk_24, 0, &sp8);
                }
                break;
            case 5:
                break;
            default:
                break;
        }
        if (var_r31->unk_18 != var_r31->unk_1C) {
            if (var_r31->unk_18 < 0 || var_r31->unk_18 > 7) {
                var_r31->unk_18 = 2;
            }
            Hu3DModelLayerSet(var_r31->unk_00, var_r31->unk_18);
            var_r31->unk_1C = var_r31->unk_18;
        }
        if (var_r31->unk_28 != 5 && var_r31->unk_28) {
            if (!var_r31->unk_38) {
                Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_3C, var_r31->unk_40, var_r31->unk_44);
                Hu3DModelRotSet(var_r31->unk_00, 0.0f, var_r31->unk_48, 0.0f);
            } else {
                Hu3DModelAttrSet(var_r31->unk_00, 1);
            }
        }
    }
}

void fn_1_5B34(omObjData *object)
{
    object->data = NULL;
    object->func = NULL;
}

void fn_1_5B48(void)
{
    omObjData *var_r31;

    var_r31 = lbl_1_bss_74;
    fn_1_5B34(var_r31);
    lbl_1_bss_74 = NULL;
}

void fn_1_5B88(s32 arg0) // probably gets inlined
{
    UnkM426Struct4 *var_r31;
    s32 var_r28;
    s32 var_r30;

    if (lbl_1_bss_74) {
        var_r31 = lbl_1_bss_74->data;
        for (var_r30 = 0; var_r30 < 6; var_r30++, var_r31++) {
            var_r28 = var_r31->unk_38;
            var_r31->unk_38 = arg0;
            if (var_r28 != arg0 && !arg0) {
                Hu3DModelAttrReset(var_r31->unk_00, 1);
                Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_3C, var_r31->unk_40, var_r31->unk_44);
                Hu3DModelRotSet(var_r31->unk_00, 0.0f, var_r31->unk_48, 0.0f);
            }
        }
    }
}

s32 fn_1_5C6C(s32 arg0, s32 arg1, Vec *arg2)
{
    UnkM426Struct4 *var_r31;
    s32 var_r30;

    if (!lbl_1_bss_74) {
        return -1;
    }
    var_r31 = lbl_1_bss_74->data;
    for (var_r30 = 0; var_r30 < 6; var_r30++, var_r31++) {
        if (var_r31->unk_28 == 5) {
            break;
        }
    }
    if (var_r30 >= 6) {
        return -1;
    }
    var_r31->unk_24 = arg0;
    var_r31->unk_28 = 0;
    var_r31->unk_2C = arg1;
    var_r31->unk_34 = 0.0f;
    var_r31->unk_3C = arg2->x;
    var_r31->unk_40 = arg2->y;
    var_r31->unk_44 = arg2->z;
    var_r31->unk_48 = 0.0f;
    var_r31->unk_18 = 2;
    return var_r30;
}

s32 fn_1_5D3C(void)
{
    UnkM426Struct4 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    if (!lbl_1_bss_74) {
        return -1;
    }
    var_r31 = lbl_1_bss_74->data;
    for (var_r28 = 0, var_r30 = var_r29 = 0; var_r28 < 6; var_r28++, var_r31++) {
        if (var_r31->unk_28 != 2 && var_r31->unk_28 != 3) {
            break;
        }
        if (var_r31->unk_3C < 0.0f) {
            var_r30++;
        } else if (var_r31->unk_3C > 0.0f) {
            var_r29++;
        } else if (frand() & 1) {
            var_r30++;
        } else {
            var_r29++;
        }
    }
    if (var_r28 < 6) {
        return -1;
    }
    if (var_r30 > var_r29) {
        return 1;
    }
    if (var_r30 < var_r29) {
        return 0;
    }
    return 2;
}

void fn_1_5E6C(void)
{
    lbl_1_bss_70 = omAddObjEx(lbl_1_bss_98, 0, 0, 0, -1, fn_1_5EBC);
}

void fn_1_5EBC(omObjData *object)
{
    UnkM426Struct5 *var_r31;
    s32 var_r30;
    UnkM426Struct5 *var_r29;
    UnkModelDataUnk120Struct *var_r27;
    ModelData *var_r26;

    var_r29 = var_r31 = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 4 * sizeof(UnkM426Struct5), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 4 * sizeof(UnkM426Struct5));
    for (var_r30 = 0; var_r30 < 4; var_r30++, var_r31++) {
        if (var_r30 == 0) {
            var_r31->unk_08 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M426, 0), MEMORY_DEFAULT_NUM));
            var_r31->unk_04 = fn_1_795C(var_r31->unk_08, 512);
        } else {
            var_r31->unk_08 = var_r29->unk_08;
            var_r31->unk_04 = fn_1_7DC8(var_r29->unk_04);
        }
        Hu3DModelLayerSet(var_r31->unk_04, 5);
        var_r26 = &Hu3DData[var_r31->unk_04];
        var_r27 = var_r26->unk_120;
        var_r27->unk_20 = 0;
        Hu3DModelAttrSet(var_r31->unk_04, 1);
        var_r31->unk_00 = var_r30;
        var_r31->unk_0C = 0;
        var_r31->unk_10 = 0;
        var_r31->unk_14.x = var_r31->unk_14.y = var_r31->unk_14.z = 0.0f;
        var_r31->unk_20 = 1.0f;
    }
    object->func = fn_1_6008;
}

void fn_1_6008(omObjData *object)
{
    UnkM426Struct8 *var_r31;
    UnkM426Struct5 *var_r30;
    UnkModelDataUnk120Struct *var_r29;
    s32 var_r28;
    s32 var_r27;
    ModelData *var_r26;
    s32 var_r25;

    var_r30 = object->data;
    if (var_r30) {
        for (var_r28 = 0; var_r28 < 4; var_r28++, var_r30++) {
            if (!var_r30->unk_0C) {
                continue;
            }
            if (var_r30->unk_10 <= 0) {
                Hu3DModelAttrSet(var_r30->unk_04, 1);
            } else {
                Hu3DModelAttrReset(var_r30->unk_04, 1);
                var_r26 = &Hu3DData[var_r30->unk_04];
                var_r29 = var_r26->unk_120;
                var_r31 = var_r29->unk_3C;
                for (var_r27 = var_r25 = 0; var_r27 < var_r29->unk_24; var_r27++, var_r31++) {
                    if (var_r31->unk_28 <= 0.0f) {
                        continue;
                    }
                    var_r31->unk_30.x += var_r31->unk_04.x;
                    var_r31->unk_30.y += var_r31->unk_04.y;
                    var_r31->unk_30.z += var_r31->unk_04.z;
                    var_r25++;
                    var_r31->unk_00++;
                    var_r31->unk_40 = var_r31->unk_00;
                    if (var_r31->unk_40 >= 16) {
                        var_r31->unk_40 = 0;
                        var_r31->unk_28 = 0.0f;
                        var_r30->unk_10--;
                    }
                }
                Hu3DModelPosSet(var_r30->unk_04, var_r30->unk_14.x, var_r30->unk_14.y, var_r30->unk_14.z);
            }
        }
    }
}

void fn_1_6180(omObjData *object)
{
    UnkM426Struct5 *var_r30;

    if (object && object->data) {
        var_r30 = object->data;
        fn_1_8E10(var_r30->unk_08);
        fn_1_5B34(object);
    }
}

void fn_1_61E0(void)
{
    fn_1_6180(lbl_1_bss_70);
}

s32 fn_1_6248(Vec *arg0)
{
    UnkM426Struct5 *var_r31;
    s32 var_r30;

    if (!lbl_1_bss_70) {
        return -1;
    }
    var_r31 = lbl_1_bss_70->data;
    if (!var_r31) {
        return;
    }
    for (var_r30 = 0; var_r30 < 4; var_r30++, var_r31++) {
        if (!var_r31->unk_0C) {
            break;
        }
    }
    if (var_r30 >= 4) {
        return -1;
    }
    var_r31->unk_0C = 1;
    var_r31->unk_10 = 0;
    fn_1_6310(var_r31->unk_00, arg0);
    var_r31->unk_20 = 1.0f;
    return var_r31->unk_00;
}

void fn_1_6310(s32 arg0, Vec *arg1)
{
    UnkM426Struct5 *var_r31;

    if (lbl_1_bss_70) {
        var_r31 = lbl_1_bss_70->data;
        if (!var_r31) {
            return;
        }
        var_r31 = &var_r31[arg0];
        if (var_r31->unk_0C) {
            var_r31->unk_14.x = arg1->x;
            var_r31->unk_14.y = arg1->y;
            var_r31->unk_14.z = arg1->z;
            Hu3DModelPosSet(var_r31->unk_04, var_r31->unk_14.x, var_r31->unk_14.y, var_r31->unk_14.z);
        }
    }
}

s32 fn_1_63B8(s32 arg0, Vec *arg1, Vec *arg2, float arg8, GXColor arg3)
{
    UnkM426Struct8 *var_r31;
    UnkM426Struct5 *var_r30;
    UnkModelDataUnk120Struct *var_r29;
    s32 var_r28;
    ModelData *var_r27;

    if (!lbl_1_bss_70) {
        return -1;
    }

    var_r30 = lbl_1_bss_70->data;
    if (!var_r30) {
        return -1;
    }

    var_r30 = &var_r30[arg0];
    if (!var_r30->unk_0C) {
        return -1;
    }
    var_r27 = &Hu3DData[var_r30->unk_04];
    var_r29 = var_r27->unk_120;
    var_r31 = var_r29->unk_3C;

    for (var_r28 = 0; var_r28 < var_r29->unk_24; var_r28++, var_r31++) {
        if (var_r31->unk_28 <= 0.0f) {
            break;
        }
    }
    if (var_r28 >= var_r29->unk_24) {
        return -1;
    }
    var_r31->unk_00 = var_r31->unk_02 = 0;

    if (arg1) {
        var_r31->unk_30.x = arg1->x - var_r30->unk_14.x;
        var_r31->unk_30.y = arg1->y - var_r30->unk_14.y;
        var_r31->unk_30.z = arg1->z - var_r30->unk_14.z;
    } else {
        var_r31->unk_30.x = var_r30->unk_14.x;
        var_r31->unk_30.y = var_r30->unk_14.y;
        var_r31->unk_30.z = var_r30->unk_14.z;
    }

    if (arg2) {
        var_r31->unk_04.x = arg2->x;
        var_r31->unk_04.y = arg2->y;
        var_r31->unk_04.z = arg2->z;
    } else {
        var_r31->unk_04.x = var_r31->unk_04.y = var_r31->unk_04.z = 0.0f;
    }

    var_r31->unk_28 = arg8;
    var_r31->unk_3C.r = arg3.r;
    var_r31->unk_3C.g = arg3.g;
    var_r31->unk_3C.b = arg3.b;
    var_r31->unk_3C.a = arg3.a;
    var_r31->unk_2C = 0.0f;
    var_r31->unk_40 = 0;
    var_r31->unk_00 = 0;
    var_r30->unk_10++;

    return var_r28;
}

void fn_1_6594(void)
{
    lbl_1_bss_6C = omAddObjEx(lbl_1_bss_98, 0, 0, 0, -1, fn_1_65E4);
}

void fn_1_65E4(omObjData *object)
{
    HsfData *sp8;

    UnkM426Struct6 *var_r31;
    s32 var_r30;
    ModelData *var_r28;

    var_r31 = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 16 * sizeof(UnkM426Struct6), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 16 * sizeof(UnkM426Struct6));
    for (var_r30 = 0; var_r30 < 16; var_r30++, var_r31++) {
        var_r31->unk_00 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M426, 30));
        var_r28 = &Hu3DData[var_r31->unk_00];
        sp8 = var_r28->hsfData;
        Hu3DModelLayerSet(var_r31->unk_00, 5);
        Hu3DModelAttrSet(var_r31->unk_00, 1);
        var_r31->unk_04 = 0;
        var_r31->unk_08 = 0;
        var_r31->unk_0C = var_r31->unk_10 = var_r31->unk_14 = 0.0f;
        var_r31->unk_18 = 1.0f;
    }
    object->func = fn_1_6704;
}

void fn_1_6704(omObjData *object)
{
    UnkM426Struct6 *var_r31;
    s32 var_r30;

    var_r31 = object->data;
    if (!var_r31) {
        return;
    }
    for (var_r30 = 0; var_r30 < 16; var_r30++, var_r31++) {
        if (var_r31->unk_04) {
            Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_0C, var_r31->unk_10, var_r31->unk_14);
            Hu3DModelRotSet(var_r31->unk_00, CRot.x, CRot.y, CRot.z);
            if (++var_r31->unk_08 >= 120.0f) {
                Hu3DModelAttrSet(var_r31->unk_00, 1);
                var_r31->unk_04 = 0;
                var_r31->unk_08 = 0;
            }
        }
    }
}

void fn_1_681C(omObjData *object)
{
    if (object && object->data) {
        fn_1_5B34(object);
    }
}

void fn_1_6844(void)
{
    fn_1_681C(lbl_1_bss_6C);
}

s32 fn_1_6888(Vec *arg0)
{
    UnkM426Struct6 *var_r31;
    s32 var_r30;

    if (!lbl_1_bss_6C) {
        return;
    }
    var_r31 = lbl_1_bss_6C->data;
    if (!var_r31) {
        return;
    }
    for (var_r30 = 0; var_r30 < 16; var_r30++, var_r31++) {
        if (!var_r31->unk_04) {
            break;
        }
    }
    if (var_r30 >= 16) {
        return -1;
    }
    var_r31->unk_04 = 1;
    var_r31->unk_08 = 0;
    var_r31->unk_0C = arg0->x;
    var_r31->unk_10 = arg0->y;
    var_r31->unk_14 = arg0->z;
    Hu3DMotionTimeSet(var_r31->unk_00, 0.0f);
    Hu3DMotionSpeedSet(var_r31->unk_00, 0.5f);
    Hu3DModelAttrSet(var_r31->unk_00, 0);
    Hu3DModelPosSet(var_r31->unk_00, var_r31->unk_0C, var_r31->unk_10, var_r31->unk_14);
    Hu3DModelScaleSet(var_r31->unk_00, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(var_r31->unk_00, 1);
    return var_r30;
}

void fn_1_69E4(void)
{
    lbl_1_bss_68 = omAddObjEx(lbl_1_bss_98, 254, 0, 0, -1, fn_1_6A34);
}

void fn_1_6A34(omObjData *object)
{
    UnkM426Struct7 *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 2 * sizeof(UnkM426Struct7), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 2 * sizeof(UnkM426Struct7));
    for (var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        if (var_r29 == 0) {
            var_r31->unk_00 = 100;
        } else {
            var_r31->unk_00 = 490;
        }
        var_r31->unk_04 = 65;
        var_r31->unk_08 = 10;
        var_r31->unk_0C = 0;
        var_r31->unk_BC = 21;
        var_r31->unk_C0 = 0;
        var_r31->unk_10 = 1;
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            var_r31->unk_2C[var_r30][0] = lbl_1_data_220[var_r30];
            var_r31->unk_2C[var_r30][1] = 0;
            switch (var_r30) {
                case 0:
                case 1:
                    var_r31->unk_14[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 51), 64, 0);
                    var_r31->unk_74[var_r30][0] = var_r31->unk_2C[var_r30][0] - var_r31->unk_BC;
                    var_r31->unk_74[var_r30][1] = var_r31->unk_2C[var_r30][1] - var_r31->unk_C0;
                    break;
                case 2:
                    var_r31->unk_14[var_r30] = espEntry(lbl_1_data_218[var_r29], 255, 0);
                    break;
                case 3:
                    var_r31->unk_14[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 29), 256, 0);
                    espTPLvlSet(var_r31->unk_14[var_r30], 0.6f);
                    espColorSet(var_r31->unk_14[var_r30], 0, 0, 0);
                    break;
                case 4:
                    var_r31->unk_14[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 9), 128, 0);
                    break;
                case 5:
                    var_r31->unk_14[var_r30] = espEntry(DATA_MAKE_NUM(DATADIR_M426, 31), 128, 0);
                    espZRotSet(var_r31->unk_14[var_r30], 45.0f);
                    break;
                default:
                    break;
            }
            espDispOn(var_r31->unk_14[var_r30]);
            espDrawNoSet(var_r31->unk_14[var_r30], 0);
            espAttrSet(var_r31->unk_14[var_r30], 1);
            espPosSet(var_r31->unk_14[var_r30], var_r31->unk_00 + var_r31->unk_2C[var_r30][0], var_r31->unk_04 + var_r31->unk_2C[var_r30][1]);
        }
    }
    fn_1_7328(0);
    object->func = fn_1_6DC0;
}

void fn_1_6DC0(omObjData *object)
{
    s32 sp8[3];

    float var_f31;
    float var_f30;
    float var_f29;

    UnkM426Struct7 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    var_r31 = object->data;
    for (var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        if (!var_r31->unk_10) {
            continue;
        }
        if (var_r31->unk_08 != lbl_1_bss_1C[var_r29]) {
            var_r31->unk_08 = lbl_1_bss_1C[var_r29];
            var_r31->unk_0C = 20;
        }
        if (var_r31->unk_0C) {
            var_f31 = 1.0 + (0.8f * sind((180.0f * (var_r31->unk_0C / 20.0f))));
            var_r31->unk_0C--;
        } else {
            var_f31 = 1.0f;
        }
		var_r28 = lbl_1_bss_1C[var_r29];
        if ((sp8[0] = var_r28 / 10) > 9) {
            sp8[0] = 9;
        }
        var_r28 -= sp8[0] * 10;
        sp8[1] = var_r28;
        if (var_r28 > 9) {
            sp8[1] = 9;
        }
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            var_f30 = (var_r31->unk_00 + var_r31->unk_BC) + (var_r31->unk_74[var_r30][0] * var_f31);
            var_f29 = (var_r31->unk_04 + var_r31->unk_C0) + (var_r31->unk_74[var_r30][1] * var_f31);
            if (sp8[var_r30] < 0) {
                sp8[var_r30] = 0;
            }
            espPosSet(var_r31->unk_14[var_r30], var_f30, var_f29);
            espScaleSet(var_r31->unk_14[var_r30], var_f31, var_f31);
            espBankSet(var_r31->unk_14[var_r30], sp8[var_r30]);
        }
        for (var_r30 = 2; var_r30 < 6; var_r30++) {
            var_f30 = var_r31->unk_00 + var_r31->unk_2C[var_r30][0];
            var_f29 = var_r31->unk_04 + var_r31->unk_2C[var_r30][1];
            espPosSet(var_r31->unk_14[var_r30], var_f30, var_f29);
            espScaleSet(var_r31->unk_14[var_r30], 1.0f, 1.0f);
        }
    }
}

void fn_1_71D0(omObjData *object)
{
    UnkM426Struct7 *var_r30;
    s32 var_r29;
    s32 var_r28;

    if (object && object->data) {
        var_r30 = object->data;
        for (var_r28 = 0; var_r28 < 2; var_r28++, var_r30++) {
            for (var_r29 = 0; var_r29 < 6; var_r29++) {
                espKill(var_r30->unk_14[var_r29]);
            }
        }
        fn_1_5B34(object);
    }
}

void fn_1_7278(void)
{
    fn_1_71D0(lbl_1_bss_68);
}

void fn_1_7328(s32 arg0)
{
    UnkM426Struct7 *var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r31 = lbl_1_bss_68->data;
    for (var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        var_r31->unk_10 = arg0;
        for (var_r30 = 0; var_r30 < 6; var_r30++) {
            if (arg0) {
                espDispOn(var_r31->unk_14[var_r30]);
            } else {
                espDispOff(var_r31->unk_14[var_r30]);
            }
        }
    }
}

void fn_1_73DC(void)
{
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omAddObjEx(lbl_1_bss_98, 32730, 0, 0, -1, omOutView);
    CRot.x = lbl_1_data_4C[1][0];
    CRot.y = lbl_1_data_4C[1][1];
    CRot.z = lbl_1_data_4C[1][2];
    Center.x = lbl_1_data_4C[1][3];
    Center.y = lbl_1_data_4C[1][4];
    Center.z = lbl_1_data_4C[1][5];
    CZoom = lbl_1_data_4C[1][6];
    lbl_1_bss_64 = omAddObjEx(lbl_1_bss_98, 254, 0, 0, -1, fn_1_758C);
}

void fn_1_758C(omObjData *object)
{
    lbl_1_bss_60 = 0;
    object->func = fn_1_75AC;
}

void fn_1_75AC(omObjData *arg0) { }

void fn_1_75B0(UnkM426Struct9 *arg0)
{
    arg0->unk_14 = 0;
}

void fn_1_75BC(void)
{
    omObjData *var_r31;

    var_r31 = lbl_1_bss_64;
    var_r31->func = NULL;
    lbl_1_bss_64 = NULL;
}

float fn_1_75F4(float arg8, float arg9)
{
    float var_f31;

    if (arg8 >= 360.0f) {
        arg8 -= 360.0f;
    } else if (arg8 < 0.0f) {
        arg8 += 360.0f;
    }
    if (arg9 >= 360.0f) {
        arg9 -= 360.0f;
    } else if (arg9 < 0.0f) {
        arg9 += 360.0f;
    }
    var_f31 = arg8 - arg9;
    if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    } else if (var_f31 >= 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}

float fn_1_770C(float arg8, float arg9, float argA)
{
    float var_f31;
    float var_f30;

    if (arg8 >= 360.0) {
        arg8 -= 360.0;
    } else if (arg8 < 0.0) {
        arg8 += 360.0;
    }
    if (arg9 >= 360.0) {
        arg9 -= 360.0;
    } else if (arg9 < 0.0) {
        arg9 += 360.0;
    }
    var_f30 = 360.0 + (arg8 - arg9);
    if (fabs(var_f30) >= 360.0) {
        var_f30 = fmod(var_f30, 360.0);
    }
    if (var_f30 < 180.0) {
        if (var_f30 <= argA) {
            var_f31 = var_f30;
        } else {
            var_f31 = argA;
        }
    } else if ((360.0 - var_f30) <= argA) {
        var_f31 = -(360.0 - var_f30);
    } else {
        var_f31 = -argA;
    }
    var_f31 += arg9;
    if (var_f31 >= 360.0) {
        var_f31 -= 360.0;
        var_f31 = var_f31;
    } else if (var_f31 < 0.0) {
        var_f31 += 360.0;
        var_f31 = var_f31;
    }
    return var_f31;
}

s16 fn_1_795C(AnimData *arg0, s16 arg1)
{
    UnkModelDataUnk120Struct *var_r31;
    s16 var_r30;
    Vec2f *var_r29;
    UnkM426Struct8 *var_r28;
    ModelData *var_r27;
    Vec *var_r26;
    void *var_r24;
    s16 var_r23;
    void *var_r22;

    var_r23 = Hu3DHookFuncCreate(fn_1_80DC);
    var_r27 = &Hu3DData[var_r23];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkModelDataUnk120Struct), var_r27->unk_48);
    var_r27->unk_120 = var_r31;
    var_r31->unk_38 = arg0;
    var_r31->unk_24 = arg1;
    var_r31->unk_20 = 0;
    var_r31->unk_4C = NULL;
    var_r31->unk_50 = NULL;
    var_r31->unk_28 = 0.0f;
    var_r31->unk_21 = 0;
    var_r31->unk_30 = 0;
    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r28 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(UnkM426Struct8), var_r27->unk_48);
    var_r31->unk_3C = var_r28;
    for (var_r30 = 0; var_r30 < arg1; var_r30++, var_r28++) {
        var_r28->unk_28 = 0.0f;
        var_r28->unk_2C = 0.0f;
        var_r28->unk_30.x = ((frand() & 127) - 64) * 20;
        var_r28->unk_30.y = ((frand() & 127) - 64) * 30;
        var_r28->unk_30.z = ((frand() & 127) - 64) * 20;
        var_r28->unk_3C.r = var_r28->unk_3C.g = var_r28->unk_3C.b = var_r28->unk_3C.a = 255;
        var_r28->unk_40 = 0;
    }
    var_r26 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec) * 4, var_r27->unk_48);
    var_r31->unk_40 = var_r26;
    for (var_r30 = 0; var_r30 < arg1 * 4; var_r30++, var_r26++) {
        var_r26->x = var_r26->y = var_r26->z = 0.0f;
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
    var_r24 = HuMemDirectMallocNum(HEAP_DATA, 0x4000, var_r27->unk_48);
    var_r22 = var_r24;
    DCFlushRange(var_r24, 0x4000);
    GXBeginDisplayList(var_r22, 0x4000);
    GXBegin(GX_QUADS, GX_VTXFMT0, arg1 * 4);
    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        GXPosition1x16(var_r30 * 4);
        GXColor1x16(var_r30);
        GXTexCoord1x16(var_r30 * 4);

        GXPosition1x16(var_r30 * 4 + 1);
        GXColor1x16(var_r30);
        GXTexCoord1x16(var_r30 * 4 + 1);

        GXPosition1x16(var_r30 * 4 + 2);
        GXColor1x16(var_r30);
        GXTexCoord1x16(var_r30 * 4 + 2);

        GXPosition1x16(var_r30 * 4 + 3);
        GXColor1x16(var_r30);
        GXTexCoord1x16(var_r30 * 4 + 3);
    }
    var_r31->unk_34 = GXEndDisplayList();
    var_r31->unk_48 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_34, var_r27->unk_48);
    memcpy(var_r31->unk_48, var_r24, var_r31->unk_34);
    DCFlushRange(var_r31->unk_48, var_r31->unk_34);
    HuMemDirectFree(var_r24);
    return var_r23;
}

s16 fn_1_7DC8(s16 arg0)
{
    UnkModelDataUnk120Struct *var_r31;
    Vec2f *var_r30;
    UnkM426Struct8 *var_r29;
    s16 var_r28;
    ModelData *var_r27;
    UnkModelDataUnk120Struct *var_r26;
    Vec *var_r25;
    s32 var_r24;
    ModelData *var_r23;
    s16 var_r22;

    var_r23 = &Hu3DData[arg0];
    var_r26 = var_r23->unk_120;
    var_r22 = Hu3DHookFuncCreate(var_r23->hook);
    var_r27 = &Hu3DData[var_r22];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(UnkModelDataUnk120Struct), var_r27->unk_48);
    var_r27->unk_120 = var_r31;
    var_r31->unk_38 = var_r26->unk_38;
    var_r31->unk_24 = var_r26->unk_24;
    var_r24 = var_r31->unk_24;
    var_r31->unk_20 = 0;
    var_r31->unk_4C = NULL;
    var_r31->unk_50 = NULL;
    var_r31->unk_28 = 0;
    var_r31->unk_21 = 0;
    var_r31->unk_30 = 0;
    var_r31->unk_00 = var_r31->unk_02 = 0;
    var_r29 = HuMemDirectMallocNum(HEAP_DATA, var_r24 * sizeof(UnkM426Struct8), var_r27->unk_48);
    var_r31->unk_3C = var_r29;
    for (var_r28 = 0; var_r28 < var_r24; var_r28++, var_r29++) {
        var_r29->unk_28 = 0.0f;
        var_r29->unk_2C = 0.0f;
        var_r29->unk_30.x = ((frand() & 127) - 64) * 20;
        var_r29->unk_30.y = ((frand() & 127) - 64) * 30;
        var_r29->unk_30.z = ((frand() & 127) - 64) * 20;
        var_r29->unk_3C.r = var_r29->unk_3C.g = var_r29->unk_3C.b = var_r29->unk_3C.a = 255;
        var_r29->unk_40 = 0;
    }

    var_r25 = HuMemDirectMallocNum(HEAP_DATA, var_r24 * sizeof(Vec) * 4, var_r27->unk_48);
    var_r31->unk_40 = var_r25;
    for (var_r28 = 0; var_r28 < (4 * var_r24); var_r28++, var_r25++) {
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
    (void)var_r26;

    return var_r22;
}

void fn_1_80DC(ModelData *arg0, Mtx arg1)
{
    Mtx sp128;
    Mtx spF8;
    Mtx spC8;
    Vec sp98[4];
    Vec sp68[4];
    Vec sp38[4];
    ROMtx sp8;

    UnkModelDataUnk120Struct *var_r31;
    Vec *var_r30;
    UnkM426Struct8 *var_r29;
    Vec *var_r28;
    Vec *var_r27;
    Vec2f *var_r26;
    s16 var_r25;
    s16 var_r23;
    s16 var_r21;
    s16 var_r20;
    s16 var_r19;
    UnkModelDataUnk120Hook var_r18;

    var_r31 = arg0->unk_120;
    if ((var_r31->unk_2C != GlobalCounter) || shadowModelDrawF) {
        if ((var_r31->unk_50) && (var_r31->unk_50 != arg0)) {
            fn_1_80DC(var_r31->unk_50, arg1);
        }
        GXLoadPosMtxImm(arg1, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        if (shadowModelDrawF != 0) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        } else {
            var_r21 = var_r31->unk_38->bmp->dataFmt & 15;
            if (var_r21 == 7 || var_r21 == 8) {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            } else {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            }
            if (arg0->attr & 2) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            } else {
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
        GXSetArray(GX_VA_POS, var_r31->unk_40, 12);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetArray(GX_VA_CLR0, &var_r31->unk_3C->unk_3C, 68);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetArray(GX_VA_TEX0, var_r31->unk_44, 8);
        if (!HmfInverseMtxF3X3(arg1, sp128)) {
            PSMTXIdentity(sp128);
        }
        PSMTXReorder(sp128, sp8);
        if (var_r31->unk_4C) {
            var_r18 = var_r31->unk_4C;
            var_r18(arg0, var_r31, arg1);
        }
        var_r29 = var_r31->unk_3C;
        var_r30 = var_r31->unk_40;
        var_r26 = var_r31->unk_44;
        PSMTXROMultVecArray(sp8, lbl_1_data_22C, &sp38[0], 4);
        for (var_r23 = 0; var_r23 < var_r31->unk_24; var_r23++, var_r29++) {
            if (!var_r29->unk_28) {
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
                var_r30->x = var_r30->y = var_r30->z = 0.0f;
                var_r30++;
            } else {
                if (!var_r29->unk_2C) {
                    var_r28 = sp98;
                    var_r27 = sp38;
                    PSVECScale(var_r27++, var_r28, var_r29->unk_28);
                    PSVECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                    PSVECScale(var_r27++, var_r28, var_r29->unk_28);
                    PSVECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                    PSVECScale(var_r27++, var_r28, var_r29->unk_28);
                    PSVECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                    PSVECScale(var_r27++, var_r28, var_r29->unk_28);
                    PSVECAdd(var_r28++, &var_r29->unk_30, var_r30++);
                } else {
                    PSVECScale(&lbl_1_data_22C[0], &sp98[0], var_r29->unk_28);
                    PSVECScale(&lbl_1_data_22C[1], &sp98[1], var_r29->unk_28);
                    PSVECScale(&lbl_1_data_22C[2], &sp98[2], var_r29->unk_28);
                    PSVECScale(&lbl_1_data_22C[3], &sp98[3], var_r29->unk_28);
                    PSMTXRotRad(spC8, 90, var_r29->unk_2C);
                    PSMTXConcat(sp128, spC8, &spF8[0]);
                    PSMTXMultVecArray(spF8, &sp98[0], &sp68[0], 4);
                    PSVECAdd(&sp68[0], &var_r29->unk_30, var_r30++);
                    PSVECAdd(&sp68[1], &var_r29->unk_30, var_r30++);
                    PSVECAdd(&sp68[2], &var_r29->unk_30, var_r30++);
                    PSVECAdd(&sp68[3], &var_r29->unk_30, var_r30++);
                }
                var_r20 = var_r29->unk_40 & 3;
                var_r19 = (var_r29->unk_40 >> 2) & 3;
                for (var_r25 = 0; var_r25 < 4; var_r25++, var_r26++) {
                    var_r26->x = (0.25f * var_r20) + lbl_1_data_25C[var_r25].x;
                    var_r26->y = (0.25f * var_r19) + lbl_1_data_25C[var_r25].y;
                }
            }
        }
        DCFlushRangeNoSync(var_r31->unk_40, var_r31->unk_24 * sizeof(Vec) * 4);
        DCFlushRangeNoSync(var_r31->unk_44, var_r31->unk_24 * sizeof(Vec2f) * 4);
        PPCSync();
        GXCallDisplayList(var_r31->unk_48, var_r31->unk_34);
        if (!shadowModelDrawF) {
            if ((var_r31->unk_21 & 2) == 0) {
                var_r31->unk_28++;
            }
            if (var_r31->unk_30 && (var_r31->unk_30 <= var_r31->unk_28)) {
                if (var_r31->unk_21 & 1) {
                    var_r31->unk_28 = 0.0f;
                }
                var_r31->unk_28 = var_r31->unk_30;
            }
            var_r31->unk_2C = GlobalCounter;
        }
    }
}

void fn_1_88B4(ModelData *arg0, Mtx arg1)
{
    float var_f31;
    float var_f30;
    float var_f28;
    float var_f27;
    float var_f26;

    CameraData *var_r30;
    AnimData *var_r29;
    s16 var_r28;

    var_r30 = Hu3DCamera;
    var_f31 = var_r30->pos.x - arg0->pos.x;
    var_f27 = var_r30->pos.y - arg0->pos.y;
    var_f30 = var_r30->pos.z - arg0->pos.z;
    var_f26 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
    arg0->rot.x = (atan2d(var_f26, var_f27)) - 90.0;
    arg0->rot.y = atan2d(var_f31, var_f30);
    var_r29 = arg0->unk_120;
    GXLoadPosMtxImm(arg1, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    if (shadowModelDrawF) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    } else {
        var_r28 = var_r29->bmp->dataFmt & 15;
        if (var_r28 == 7 || var_r28 == 8) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
        } else {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
        }
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    }
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    HuSprTexLoad(var_r29, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_POS, lbl_1_data_27C, 12);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, lbl_1_data_2AC, 4);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, lbl_1_data_2BC, 8);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition1x16(0);
    GXColor1x16(0);
    GXTexCoord1x16(0);

    GXPosition1x16(1);
    GXColor1x16(0);
    GXTexCoord1x16(1);

    GXPosition1x16(2);
    GXColor1x16(0);
    GXTexCoord1x16(2);

    GXPosition1x16(3);
    GXColor1x16(0);
    GXTexCoord1x16(3);
}

void fn_1_8E10(AnimData *arg0)
{
    arg0->useNum = 0;
    HuSprAnimKill(arg0);
}

void fn_1_8E48(ModelData *arg0, Mtx arg1)
{
    CameraData *var_r31;

    Mtx sp50;
    Mtx44 sp10;
    GXColor spC = { 255, 0, 0, 128 };

    var_r31 = Hu3DCamera;
    GXSetScissor(var_r31->scissor_x, var_r31->scissor_y, var_r31->scissor_w, var_r31->scissor_h);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    C_MTXOrtho(sp10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    GXSetProjection(sp10, GX_ORTHOGRAPHIC);
    GXSetTevColor(GX_TEVREG0, spC);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    PSMTXIdentity(sp50);
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
#pragma dont_inline on
void fn_1_9130(s32 arg0, UnkM426Struct10 *arg1, s32 arg2)
{
    switch (arg1->unk_04) {
        case 0:
            fn_1_9544(arg0, arg1, arg2);
            return;
        case 1:
            fn_1_9798(arg0, arg1, arg2);
            return;
        case 2:
            fn_1_9868(arg0, arg1, arg2);
            return;
        case 3:
            fn_1_9230(arg0, arg1, arg2);
            return;
        case 4:
            fn_1_97EC(arg0, arg1, arg2);
            return;
        case 5:
            fn_1_971C(arg0, arg1, arg2);
            return;
        case 6:
            fn_1_9544(arg0, arg1, arg2);
            return;
        default:
            fn_1_9544(arg0, arg1, arg2);
            return;
    }
}
#pragma dont_inline reset

void fn_1_9230(s32 arg0, UnkM426Struct10 *arg1, s32 arg2)
{
    UnkM426Struct10 *var_r29;
    UnkM426Struct10 *var_r28;
    UnkM426Struct10 *var_r27;
    u32 var_r25;
    u32 var_r24;
    u32 var_r23;
    u32 var_r22;

    arg1->unk_0C &= ~arg2;
    for (var_r25 = 0; var_r25 < arg1->unk_14; var_r25++) {
        var_r29 = arg1->unk_18[var_r25];
        switch (var_r29->unk_04) {
            case 0:
                fn_1_9544(arg0, var_r29, arg2);
                break;
            case 1:
                fn_1_9798(arg0, var_r29, arg2);
                break;
            case 2:
                fn_1_9868(arg0, var_r29, arg2);
                break;
            case 3:
                var_r29->unk_0C &= ~arg2;
                for (var_r24 = 0; var_r24 < var_r29->unk_14; var_r24++) {
                    var_r28 = var_r29->unk_18[var_r24];
                    switch (var_r28->unk_04) {
                        case 0:
                            fn_1_9544(arg0, var_r28, arg2);
                            break;
                        case 1:
                            fn_1_9798(arg0, var_r28, arg2);
                            break;
                        case 2:
                            fn_1_9868(arg0, var_r28, arg2);
                            break;
                        case 3:
                            var_r28->unk_0C &= ~arg2;
                            for (var_r23 = 0; var_r23 < var_r28->unk_14; var_r23++) {
                                var_r27 = var_r28->unk_18[var_r23];
                                switch (var_r27->unk_04) {
                                    case 0:
                                        fn_1_9544(arg0, var_r27, arg2);
                                        break;
                                    case 1:
                                        fn_1_9798(arg0, var_r27, arg2);
                                        break;
                                    case 2:
                                        fn_1_9868(arg0, var_r27, arg2);
                                        break;
                                    case 3:
                                        var_r27->unk_0C &= ~arg2;
                                        for (var_r22 = 0; var_r22 < var_r27->unk_14; var_r22++) {
                                            fn_1_9130(arg0, var_r27->unk_18[var_r22], arg2);
                                        }
                                        break;
                                    case 4:
                                        fn_1_97EC(arg0, var_r27, arg2);
                                        break;
                                    case 5:
                                        fn_1_971C(arg0, var_r27, arg2);
                                        break;
                                    case 6:
                                        fn_1_9544(arg0, var_r27, arg2);
                                        break;
                                    default:
                                        fn_1_9544(arg0, var_r27, arg2);
                                        break;
                                }
                            }
                            break;
                        case 4:
                            fn_1_97EC(arg0, var_r28, arg2);
                            break;
                        case 5:
                            fn_1_971C(arg0, var_r28, arg2);
                            break;
                        case 6:
                            fn_1_9544(arg0, var_r28, arg2);
                            break;
                        default:
                            fn_1_9544(arg0, var_r28, arg2);
                            break;
                    }
                }
                break;
            case 4:
                fn_1_97EC(arg0, var_r29, arg2);
                break;
            case 5:
                fn_1_971C(arg0, var_r29, arg2);
                break;
            case 6:
                fn_1_9544(arg0, var_r29, arg2);
                break;
            default:
                fn_1_9544(arg0, var_r29, arg2);
                break;
        }
    }
}

void fn_1_9544(s32 arg0, UnkM426Struct10 *arg1, s32 arg2)
{
    UnkM426Struct10 *var_r31;
    u32 var_r27;
    u32 var_r26;
    u32 var_r25;
    u32 var_r24;
    u32 var_r23;

    arg1->unk_0C &= ~arg2;
    for (var_r27 = 0; var_r27 < arg1->unk_14; var_r27++) {
        var_r31 = arg1->unk_18[var_r27];
        switch (var_r31->unk_04) {
            case 0:
                var_r31->unk_0C = var_r31->unk_0C & ~arg2;
                for (var_r26 = 0; var_r26 < var_r31->unk_14; var_r26++) {
                    fn_1_9130(arg0, var_r31->unk_18[var_r26], arg2);
                }
                break;
            case 1:
                fn_1_9798(arg0, var_r31, arg2);
                break;
            case 2:
                fn_1_9868(arg0, var_r31, arg2);
                break;
            case 3:
                var_r31->unk_0C = var_r31->unk_0C & ~arg2;
                for (var_r25 = 0; var_r25 < var_r31->unk_14; var_r25++) {
                    fn_1_9130(arg0, var_r31->unk_18[var_r25], arg2);
                }
                break;
            case 4:
                fn_1_97EC(arg0, var_r31, arg2);
                break;
            case 5:
                fn_1_971C(arg0, var_r31, arg2);
                break;
            case 6:
                var_r31->unk_0C = var_r31->unk_0C & ~arg2;
                for (var_r24 = 0; var_r24 < var_r31->unk_14; var_r24++) {
                    fn_1_9130(arg0, var_r31->unk_18[var_r24], arg2);
                }
                break;
            default:
                var_r31->unk_0C = var_r31->unk_0C & ~arg2;
                for (var_r23 = 0; var_r23 < var_r31->unk_14; var_r23++) {
                    fn_1_9130(arg0, var_r31->unk_18[var_r23], arg2);
                }
                break;
        }
    }
}

void fn_1_971C(s32 arg0, UnkM426Struct10 *arg1, s32 arg2)
{
    u32 var_r30;

    arg1->unk_0C = arg1->unk_0C & ~arg2;
    for (var_r30 = 0; var_r30 < arg1->unk_14; var_r30++) {
        fn_1_9130(arg0, arg1->unk_18[var_r30], arg2);
    }
}

void fn_1_9798(s32 arg0, UnkM426Struct10 *arg1, s32 arg2)
{
    arg1->unk_0C = arg1->unk_0C & ~arg2;
    fn_1_9130(arg0, arg1->unk_64, arg2);
}

void fn_1_97EC(s32 arg0, UnkM426Struct10 *arg1, s32 arg2)
{
    u32 var_r30;

    arg1->unk_0C &= ~arg2;
    for (var_r30 = 0; var_r30 < arg1->unk_14; var_r30++) {
        fn_1_9130(arg0, arg1->unk_18[var_r30], arg2);
    }
}

void fn_1_9868(s32 arg0, UnkM426Struct10 *arg1, s32 arg2)
{
    u32 var_r30;

    arg1->unk_0C &= ~arg2;
    for (var_r30 = 0; var_r30 < arg1->unk_14; var_r30++) {
        fn_1_9130(arg0, arg1->unk_18[var_r30], arg2);
    }
}

float fn_1_98E4(float arg8, float arg9, float argA, float argB)
{
    float var_f31;
    float var_f30;

    var_f31 = 1.0 - arg8;
    var_f30 = (argB * (arg8 * arg8)) + ((arg9 * (var_f31 * var_f31)) + (2.0 * (argA * (var_f31 * arg8))));

    return var_f30;
}

void fn_1_995C(s16 arg0)
{
    UnkM426Struct11 sp8;

    UnkM426Struct12 *var_r31;
    HsfBuffer *var_r30;
    ModelData *var_r29;
    HsfData *var_r28;
    s32 var_r27;
    s32 var_r26;

    var_r29 = &Hu3DData[arg0];
    var_r28 = var_r29->hsfData;
    var_r30 = var_r28->face;
    for (var_r27 = 0; var_r27 < var_r28->faceCnt; var_r27++, var_r30++) {
        var_r31 = var_r30->data;
        for (var_r26 = 0; var_r26 < var_r30->count; var_r26++, var_r31++) {
            switch (var_r31->unk_00 & 7) {
                case 2:
                case 3:
                    sp8 = var_r31->unk_0C;
                    var_r31->unk_0C = var_r31->unk_14;
                    var_r31->unk_14 = sp8;
                    break;
                default:
                    break;
            }
        }
        DCStoreRangeNoSync(var_r30->data, var_r30->count * sizeof(UnkM426Struct12));
    }
    HuMemDirectFreeNum(HEAP_DATA, var_r29->unk_48);
    MakeDisplayList(arg0, var_r29->unk_48);
}
